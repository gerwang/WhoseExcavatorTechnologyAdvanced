//
// Created by Gerwa on 2017/11/6.
//

#include "CSVHandler.h"
#include "StringConvert.h"
#include <cwchar>
#include "Logger.h"

String stripQuote(const String &str, int start, int end) {
    while (start < end && iswspace((wint_t) str[start]) || str[start] == '"') {
        start++;
    }
    while (start < end && iswspace((wint_t) str[end - 1]) || str[end - 1] == '"') {
        end--;
    }
    return str.substr(static_cast<unsigned int>(start), static_cast<unsigned int>(end));
}

void CSVHandler::load(const ByteArray &fileName) {
    csv.clear();
    String input = StringConvert::fromFile(fileName);
    int index = 0;
    int row = 0;
    while (index < input.size()) {
        int end_index = index;
        while (end_index < input.size() && input[end_index] != ',' && input[end_index] != '\n') {
            end_index++;
        }
        String element = stripQuote(input, index, end_index);

        if (row == csv.size()) {
            csv.push_back(ArrayList<String>());
        }
        csv[row].push_back(std::move(element));

        if (end_index < input.size()) {

            if (input[end_index] == ',') {//comma
                //pass
            } else if (input[end_index] == '\n') {//newline
                row++;
            } else {
                Logger::slog("unexecpted seperate value at " + fileName + " at line " + String::number(row + 1));
            }
        }

        index = end_index + 1;
    }
}

void CSVHandler::save(String fileName) {
    String output;
    for (int row = 0; row < csv.size(); row++) {
        for (int column = 0; column < csv[row].size(); column++) {
            output.push_back('"');
            output += csv[row][column];
            output.push_back('"');
            if (column + 1 < csv[row].size()) {
                output.push_back(',');
            }
        }
        output.push_back('\n');
    }
    StringConvert::toFile(output, fileName);
}

ArrayList<ArrayList<String>> &CSVHandler::getCSV() {
    return csv;
}
