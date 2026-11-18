/**
  * @file rtt_log.h
  * @brief Colorful log output based on SEGGER RTT.
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2026/11/17
  * 
  * @copyright Copyright (c) 2026 South China University of Technology.
  * All rights reserved.
  * 
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * 
  * @par History:
  * 	Date		Version		Author			Description
  * 	2026/11/17	0.1			Leon Lee		Preliminary version.
  */

#ifndef __RTT_LOG_H__
#define __RTT_LOG_H__

#include <string.h>
#include "SEGGER_RTT.h"

// Define log print function
#define LOG_PRINT(format, ...)  SEGGER_RTT_printf(format, ##__VA_ARGS__)   

// Define current log level
#define CURRENT_LOG_LEVEL   LOG_LEVEL_DEBUG

// Define path separator for different platforms
// For Windows, use '\\', for Unix/Linux, use '/'
#define PATH_SEPARATOR      '\'

// Define log levels
typedef enum{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERR,
}LOG_LEVEL;

// Define log colors
#define LOG_COLOUR_BLACK           "\x1B[2;30m"
#define LOG_COLOUR_RED             "\x1B[2;31m"
#define LOG_COLOUR_GREEN           "\x1B[2;32m"
#define LOG_COLOUR_YELLOW          "\x1B[2;33m"
#define LOG_COLOUR_BLUE            "\x1B[2;34m"
#define LOG_COLOUR_MAGENTA         "\x1B[2;35m"
#define LOG_COLOUR_CYAN            "\x1B[2;36m"
#define LOG_COLOUR_WHITE           "\x1B[2;37m"

#define LOG_COLOUR_RESET           "\x1B[0m" 

// Define macro to get file name from path
#define GET_FILE_NAME(path) strrchr(path, PATH_SEPARATOR)?strrchr(path, PATH_SEPARATOR)+1:path

// Define log macros for debug levels with color CYAN
#define LOG_DEBUG(format, ...)                                                                                              \
if (CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG)                                                                                   \
{                                                                                                                           \
    LOG_PRINT(LOG_COLOUR_CYAN "[DEBUG %s %d]" LOG_COLOUR_RESET format, GET_FILE_NAME(__FILE__), __LINE__, ##__VA_ARGS__);   \
} 

// Define log macro for info level with color GREEN
#define LOG_INFO(format, ...)                                                                                               \
if (CURRENT_LOG_LEVEL <= LOG_LEVEL_INFO)                                                                                    \
{                                                                                                                           \
    LOG_PRINT(LOG_COLOUR_GREEN "[INFO %s %d]" LOG_COLOUR_RESET format, GET_FILE_NAME(__FILE__), __LINE__, ##__VA_ARGS__);   \
} 

// Define log macro for warning level with color YELLOW
#define LOG_WARN(format, ...)                                                                                               \
if (CURRENT_LOG_LEVEL <= LOG_LEVEL_WARN)                                                                                    \
{                                                                                                                           \
    LOG_PRINT(LOG_COLOUR_YELLOW "[WARN %s %d]" LOG_COLOUR_RESET format, GET_FILE_NAME(__FILE__), __LINE__, ##__VA_ARGS__);  \
} 

// Define log macro for error level with color MAGENTA
#define LOG_ERR(format, ...)                                                                                                \
if (CURRENT_LOG_LEVEL <= LOG_LEVEL_ERR)                                                                                     \
{                                                                                                                           \
    LOG_PRINT(LOG_COLOUR_MAGENTA "[ERR %s %d]" LOG_COLOUR_RESET format, GET_FILE_NAME(__FILE__), __LINE__, ##__VA_ARGS__);  \
} 


#endif // __RTT_LOG_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
