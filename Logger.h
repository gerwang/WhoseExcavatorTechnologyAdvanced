//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_LOGGER_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_LOGGER_H

#include <fstream>

#include "BasicString.h"

#define DEBUG

class Logger {
private:
    ByteArray m_logFileName;
    std::ofstream m_log;
    static Logger *s_instance;

    explicit Logger(ByteArray logFileName = "debug.log") : m_logFileName(std::move(logFileName)) {}

public:
    static Logger *logger() {
        if (s_instance == nullptr) {
            s_instance = new Logger();
        }
        return s_instance;
    }

    void log(const String &str);

    static void slog(const String &str);
};



#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_LOGGER_H
