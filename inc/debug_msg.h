/**
  * @file debug_msg.h
  * @brief Debug message output procedure header file
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/07/02
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
  * 	2024/07/02	0.1			Leon Lee		Preliminary version.
  */

#ifndef __DEBUG_MSG_H__
#define __DEBUG_MSG_H__

#include "RTE_Components.h"

#if defined(RTE_CMSIS_Compiler_STDERR)
#include <stdio.h>
#include <stdarg.h>
#endif

#include "cmsis_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

/**
  * @brief Output a debug message.
  *
  * @param[in] printf-style format string, followed by variables
  */
__STATIC_INLINE void debug(const char *format, ...)
{
#if defined(RTE_CMSIS_Compiler_STDERR) && !defined(NDEBUG)
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
#endif
}


/**
  * @brief Conditionally output a debug message
  * 
  *     NOTE: If the condition is constant false (== 0) and the compiler 
  *           optimization level is greater than 0, then the whole function will
  *           be compiled away.
  *
  * @param condition output only if condition is true (!= 0)
  * @param format printf-style format string, followed by variables
  *
  */
__STATIC_INLINE void debug_if(int condition, const char *format, ...)
{
#if defined(RTE_CMSIS_Compiler_STDERR) && !defined(NDEBUG)
    if (condition) {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
#endif
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __DEBUG_MSG_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
