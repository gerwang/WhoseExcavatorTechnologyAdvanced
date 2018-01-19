//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_LOGGER_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_LOGGER_H

/*!
 * @brief 日志记录模块，用于调试
 */

#include <fstream>

#include "BasicString.h"

#define DEBUG

class Logger {
private:
    ByteArray m_logFileName;
    std::ofstream m_log;
    static Logger *s_instance;

    explicit Logger(ByteArray logFileName = "debug.log") : m_logFileName(std::move(logFileName)) {
        std::ofstream(m_logFileName.c_str());
    }

public:
    /*!
     * 得到日志记录器的单体
     * @return 单体实例
     */
    static Logger *logger() {
        if (s_instance == nullptr) {
            s_instance = new Logger();
        }
        return s_instance;
    }

    void log(const String &str);

    /*!
     * 静态的log调用方式
     * @param str
     */
    static void slog(const String &str);
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_LOGGER_H
