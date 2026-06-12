/**
  * @file c_log.h
  * @brief Console logger header file
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/07/19
  * 
  * @copyright Copyright (c) 2024 South China University of Technology.
  * All rights reserved.
  * 
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * 
  * @par History:
  * 	Date		Version		Author			Description
  * 	2024/07/19	0.1			Leon Lee		Preliminary version.
  */

/**
  * @note Logger format: 
  *    TIMESTAMP [LEVEL] FILE:LINE -> MSG
  *       TIMESTAMP: unit in seconds, precision in 0.000001s
  *       LEVEL:     V for verbose, D for debug, I for info, W for warning, E for error, F for fatal
  *       FILE:LINE: file name and line number
  *       MSG:       message
  */

#ifndef __C_LOG_H__
#define __C_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// #define LOG_TRACE(fmt, ...) clog_log(LogLevel_VERBOSE, __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) clog_log(LogLevel_DEBUG, __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  clog_log(LogLevel_INFO , __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  clog_log(LogLevel_WARN , __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) clog_log(LogLevel_ERROR, __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)
// #define LOG_FATAL(fmt, ...) clog_log(LogLevel_FATAL, __FILENAME__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_LEVEL_ALL()     clog_setLevel(LogLevel_VERBOSE)
#define LOG_LEVEL_DEBUG()   clog_setLevel(LogLevel_DEBUG)
#define LOG_LEVEL_INFO()    clog_setLevel(LogLevel_INFO)
#define LOG_LEVEL_WARN()    clog_setLevel(LogLevel_WARN)
#define LOG_LEVEL_ERROR()   clog_setLevel(LogLevel_ERROR)
#define LOG_LEVEL_SILENT()  clog_setLevel(LogLevel_SILENT)
#define LOG_LEVEL_OFF()     clog_setLevel(LogLevel_OFF)

/*
 * Logger Level
 * 主要使用的有以下四个等级：
 *  DEBUG
 *      该级别的主要输出调试性质的内容，该级别日志主要用于在开发、测试阶段输出。该级别的日志
 *      应尽可能地详尽，开发人员可以将各类详细信息记录到 DEBUG 里，起到调试的作用，包括参数
 *      信息，调试细节信息，返回值信息等等，便于在开发、测试阶段出现问题或者异常时，对其进行
 *      分析。
 *  
 *  INFO
 *      该级别的主要记录系统关键信息，旨在保留系统正常工作期间关键运行指标，开发人员可以将初
 *      始化系统配置、业务状态变化信息，或者用户业务流程中的核心处理记录到 INFO 日志中，方便
 *      日常运维工作以及错误回溯时上下文场景复现。建议在项目完成后，在测试环境将日志级别调成 
 *      INFO，然后通过 INFO 级别的信息看看是否能了解这个应用的运用情况，如果出现问题后是否
 *      这些日志能否提供有用的排查问题的信息。
 *  
 *  WARN
 *      该级别的主要输出警告性质的内容，这些内容是可以预知且是有规划的，比如，某个方法入参为
 *      空或者该参数的值不满足运行该方法的条件时。在 WARN 级别的时应输出较为详尽的信息，以
 *      便于事后对日志进行分析。
 *  
 *  ERROR
 *      该级别主要针对于一些不可预知的信息，诸如：错误、异常等，比如，在 catch 块中抓获的网
 *      络通信、数据库连接等异常，若异常对系统的整个流程影响不大，可以使用 WARN 级别日志输出。
 *      在输出 ERROR 级别的日志时，尽量多地输出方法入参数、方法执行过程中产生的对象等数据，
 *      在带有错误、异常对象的数据时，需要将该对象一并输出。
 * 
 * 
 * 原文链接： https://xie.infoq.cn/article/c7e46aa4bd7de3edb855c1f29
 */
enum LogLevel
{
    LogLevel_VERBOSE,   // Verbose, full details
    LogLevel_DEBUG,     // Debug, 代码调试信息
    LogLevel_INFO,      // Info, default logger level
    LogLevel_WARN,      // Warning, 可能会出现潜在的错误
    LogLevel_ERROR,     // Error, 虽然发生错误事件, 但仍然不影响系统的正常运行
    LogLevel_SILENT,    // Silent, 关闭所有日志
    LogLevel_OFF = LogLevel_SILENT,       
};

/**
  * Initialize the logger as a console logger.
  * If the file pointer is NULL, stdout will be used.
  *
  * @param[in] output A file pointer. Make sure to set stdout or stderr.
  * @return Non-zero value upon success or 0 on error
  */
int clog_init(FILE* output);


/**
  * Set the log level.
  * Message levels lower than this value will be discarded.
  * The default log level is INFO.
  *
  * @param[in] level A log level
  */
void clog_setLevel(enum LogLevel level);


/**
  * Get the log level that has been set.
  * The default log level is INFO.
  *
  * @return The log level
  */
enum LogLevel clog_getLevel(void);


/**
  * Check if a message of the level would actually be logged.
  *
  * @return true if the log level is enabled, false otherwise. 
  */
bool clog_isEnabled(enum LogLevel level);


/**
  * Flush automatically.
  * Auto flush is off in default.
  *
  * @param[in] interval A flush interval in milliseconds. Switch off if 0 or a negative integer.
  */
void clog_autoFlush(long interval);


/**
  * Flush buffered log messages.
  */
void clog_flush(void);

/**
  * Log a message.
  * Make sure to call one of the following initialize functions before starting logging.
  * - clog_init()
  *
  * @param[in] level A log level
  * @param[in] file A file name string
  * @param[in] line A line number
  * @param[in] fmt A format string
  * @param[in] ... Additional arguments
  */
void clog_log(enum LogLevel level, const char* file, int line, const char* fmt, ...);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __C_LOG_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
