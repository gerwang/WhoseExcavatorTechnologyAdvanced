//
// Created by Gerwa on 2017/11/6.
//

#include "Logger.h"
#include "StringConvert.h"
#include <mutex>

std::mutex logMutex;

void Logger::log(const String &str) {
#ifdef DEBUG
    std::unique_lock<std::mutex> lock(logMutex);
    m_log.open(m_logFileName.c_str(), std::ios::app);
    m_log << StringConvert::toStdString(str) << std::endl;
    m_log.close();
#endif
}

void Logger::slog(const String &str) {
#ifdef DEBUG
    logger()->log(str);
#endif
}

Logger *Logger::s_instance;