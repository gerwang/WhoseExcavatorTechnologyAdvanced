//
// Created by Gerwa on 2017/11/6.
//

#include <winsock2.h>
#include "HttpRequest.h"
#include "StringConvert.h"
#include "Logger.h"
#include <cstring>


#ifdef _MSC_VER //msvc compiler
#pragma comment("Ws2_32.lib")
#endif

int parseHttp(const String &url, int index) {
    if (url.match("http://", static_cast<size_t>(index))) {
        index += 7;
    } else if (url.match("https://", static_cast<size_t>(index))) {
        index += 8;
    }
    return index;
}

int parseHost(const String &url, int index, String &host) {
    int end_index = index;
    while (end_index < url.size() && url[end_index] != '/' && url[end_index] != ':') {
        end_index++;
    }
    host = url.substr(static_cast<unsigned int>(index), static_cast<unsigned int>(end_index));
    return end_index;
}

int parsePort(const String &url, int index, int &port) {
    index++;
    port = 0;
    while (iswdigit((wint_t) url[index])) {
        port = port * 10 + url[index] - '0';
        index++;
    }
    return index;
}

int parsePath(const String &url, int index, String &path) {
    int end_index = index;
    while (end_index < url.size() && url[end_index] != '#') {
        end_index++;
    }
    path = url.substr(static_cast<unsigned int>(index), static_cast<unsigned int>(end_index));
    return end_index;
}

void parseUrl(const String &url, String &host, String &path, int &port) {
    int index = 0;
    index = parseHttp(url, index);
    index = parseHost(url, index, host);
    if (index < url.size() && url[index] == ':') {
        index = parsePort(url, index, port);
    } else {
        port = 80;
    }
    if (index < url.size()) {
        index = parsePath(url, index, path);
    } else {
        path = "/";
    }
}

String HttpRequest::get(const String &url) {
    String host, path;
    int port;
    parseUrl(url, host, path, port);
    String request = "GET " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Connection: close\r\n";
    request += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36\r\n";
    request += "\r\n";

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


    hostent *hostInfo = gethostbyname(StringConvert::toStdString(host).c_str());
    if (hostInfo == nullptr) {
        Logger::slog("cannot resolve host name: " + host);
        return String();
    }
    sockaddr_in sockAddr{};
    memcpy(&sockAddr.sin_addr, hostInfo->h_addr_list[0], static_cast<size_t>(hostInfo->h_length));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(static_cast<u_short>(port));

    if (connect(sock, (SOCKADDR *) &sockAddr, sizeof(SOCKADDR)) != 0) {
        Logger::slog("cannot connect to: " + host + " WSAGetLastError: " + String::number(WSAGetLastError()));
        return String();
    }

    std::string stdstr = StringConvert::toStdString(request);
    if (send(sock, stdstr.c_str(), stdstr.length(), 0) == SOCKET_ERROR) {
        Logger::slog("cannot send " + request);
        return String();
    }

    std::string response;
    char buffer[1010];
    int bytesReceived;
    while ((bytesReceived = recv(sock, buffer, 1000, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        response += buffer;
    }
    String converted = StringConvert::fromStdString(response);
    int index = 0;
    while (index < converted.size() && !converted.match("\r\n\r\n", static_cast<size_t>(index))) {
        index++;
    }
    index += 4;

    //handle chunk
    while (index < converted.size() && converted[index] != '<') {
        index++;
    }
    int end_index = converted.size();
    while (index < end_index && converted[end_index - 1] != '>') {
        end_index--;
    }

    return converted.substr(static_cast<unsigned int>(index), static_cast<unsigned int>(end_index));
}

void HttpRequest::startUp() {
    WSADATA wsadata{};
    WSAStartup(MAKEWORD(2, 2), &wsadata);
}

void HttpRequest::tearDown() {
    WSACleanup();
}
