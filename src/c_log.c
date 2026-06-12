/**
  * @file c_log.c
  * @brief Console logger implement file.
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

#include "RTE_Components.h"
#include CMSIS_device_header

#include <stdarg.h>
#include "assert.h"
#include "critical_section.h"
#include "c_log.h"


#if (__CORTEX_M >= 3U)
#include <stdatomic.h>
__STATIC_INLINE uint32_t atomic_cmp_xch_32 (uint32_t *mem, uint32_t *expected, uint32_t desired) {
  return((uint32_t)atomic_compare_exchange_weak_explicit((_Atomic uint32_t *)mem,
                                                          expected,
                                                          desired,
                                                          memory_order_acq_rel,
                                                          memory_order_relaxed));
}
#endif

#define uS_PER_S                1000000u   // Microseconds per second

/* Console logger */
typedef struct 
{
    FILE* output;
    enum LogLevel level;
    uint32_t ts_freq;
    uint32_t ts_overflow;
    uint32_t ts_last;
    bool initialized;
}CLog_t;

static CLog_t _log;
const char* _log_level_char[] = {"[V] ", "[D] ", "[I] ", "[W] ", "[E] ", "[S] "};

void clog_setLevel(enum LogLevel level)
{
    _log.level = level;
}


enum LogLevel clog_getLevel(void)
{
    return _log.level;
}


bool clog_isEnabled(enum LogLevel level)
{
    return _log.level <= level;
}


__STATIC_INLINE int __clog_setupTimer(void)
{
#if ((__CORTEX_M >= 3U) && (__CORTEX_M != 23U))
    DCB->DEMCR |= DCB_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL  |= DWT_CTRL_CYCCNTENA_Msk;
    return 0;
#else
    return -1;
#endif 
}


__STATIC_INLINE uint32_t __clog_getTimerCount(void)
{
#if ((__CORTEX_M >= 3U) && (__CORTEX_M != 23U))
    return DWT->CYCCNT;
#else
    return 0;
#endif 
}


/**
 * Retrieves the current timestamp with overflow handling.
 * This function uses the DWT cycle counter for time measurement, taking into account
 * the possibility of overflow and ensuring atomicity where necessary to maintain
 * accurate timing across system runtime.
 *
 * @return uint64_t The current timestamp, accounting for potential overflow.
 */
static uint64_t clog_getTimeStamp(void)
{
#if ((__CORTEX_M >= 3U) && (__CORTEX_M != 23U))
    uint32_t ts;                // Current timestamp from the DWT cycle counter.
    uint32_t ts_last;           // Last recorded timestamp to detect overflow.
    uint32_t ts_overflow;       // Counter for the number of overflows.

    // Load last timestamp and enforce memory ordering to prevent read reordering.
    ts_last = *((volatile uint32_t *)&_log.ts_last);
    __DMB();

    do
    {
        // Load the current overflow count atomically.
        ts_overflow = *((volatile uint32_t*)&_log.ts_overflow);
        // Retrieve the current cycle count.
        ts = __clog_getTimerCount();

        // Check for timestamp overflow by comparing current and last timestamps.
        if (ts < ts_last)
        {
            uint32_t primask = __get_PRIMASK(); // Store current interrupt state.
            uint32_t ts_latest;
            uint32_t ts_updated;

            // Disable interrupts to ensure atomic update of overflow and last timestamp.
            __disable_irq();
            ts_latest = *((volatile uint32_t*)&_log.ts_last);

            // Update overflow and last timestamp if no other update occurred.
            if (ts_latest == ts_last)
            {
                _log.ts_last = ts;
                _log.ts_overflow++;
                __DMB();        // Ensure memory ordering for the update.
                ts_updated = 1U;
            }
            else
            {
                ts_updated = 0U;
            }

            // Restore interrupt state if previously enabled.
            if (primask == 0U)
            {
                __enable_irq();
            }

            // If timestamp was not updated, retry the loop to handle race conditions.
            if (ts_updated == 0U)
            {
                continue;
            }

            ts_overflow++; // Increment the overflow count for this update.
            break;
        }
        // Continue updating the last timestamp in a loop until successful.
    } while (atomic_cmp_xch_32(&_log.ts_last, &ts_last, ts) == 0U);
    
    // Combine the current timestamp with the overflow count to get a 64-bit timestamp.
    return (ts | ((uint64_t)ts_overflow << 32));
#else
    return 0;
#endif /* (__CORTEX_M < 3U) */
}


int clog_init(FILE* output)
{
    output = (output != NULL) ? output : stdout;
    if (output != stdout && output != stderr) 
    {
        ASSERT(0 && "output must be stdout or stderr");
        return -1;
    }

    __clog_setupTimer();

    _log.output = output;
    _log.level = LogLevel_INFO;
    _log.ts_freq = SystemCoreClock;
    _log.ts_overflow = 0;
    _log.ts_last = 0;
    _log.initialized = true;

    return 0;
}

void clog_log(enum LogLevel level, const char* file, int line, const char* fmt, ...)
{
    uint64_t ts;
    uint32_t ts_int, ts_frac;
    const char *level_str;

    va_list args;
    
    if (IS_HANDLER_MODE())      // do not log when in interrupt service routine 
    {
        return;
    }   

    if (!_log.initialized)
    {
        ASSERT(0 && "Console logger is not initialized!");
        return;
    }
    if (!clog_isEnabled(level))
    {
        return;
    }

    ts = clog_getTimeStamp() / (_log.ts_freq / uS_PER_S);       // ts in microseconds
    ts_int = (uint32_t)(ts / uS_PER_S);                         // ts in seconds  
    ts_frac = (uint32_t)(ts - ((uint64_t)ts_int * uS_PER_S));   // ts in microseconds

    level_str = _log_level_char[level];

    // lock()

    fprintf(_log.output, "%u.%06u %s%s:%d -> ", ts_int, ts_frac, level_str, file, line);
    va_start(args, fmt);
    vfprintf(_log.output, fmt, args);
    va_end(args);

    // unlock() 
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
