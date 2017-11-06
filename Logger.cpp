//
// Created by Gerwa on 2017/11/6.
//

#include "Logger.h"
#include <iostream>

void Logger::log(const String &str) {
#ifdef DEBUG
    m_log.open(m_logFileName.c_str(), std::ios::app);
    m_log << str << std::endl;
    m_log.close();
#endif
}

void Logger::slog(const String &str) {
    logger()->log(str);
}

Logger *Logger::s_instance;