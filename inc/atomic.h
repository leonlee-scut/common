/*
 * Copyright (c) 2011, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */

/*
 *
 * 在TI公司的ATM.H文件基础上修改移植，适合ARM Cortex M系列机器MCU使用。
 *     注意：
 *   ==========
 *		   1. ATM模块中所有函数适合在thread模式或handler模式中调用；
 *         2. 在thread模式下，占用SVC 1软件中断；
 */

/*
 *  ======== atm.h ========
 *
 *  Atomic processor operations:
 *      atomic_and()   	atomic_clear() 	atomic_dec()
 *      atomic_inc()   	atomic_or()    	atomic_set()
 *		atomic_inc_and()	atomic_inc_or()
 *      atomic_dec_and()	atomic_dec_or()
 *		atomic_add()		atomic_sub()
 *
 */

#ifndef __ATOMIC__
#define __ATOMIC__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported macros -----------------------------------------------------------*/
// #define IS_CPU_IN_HANDLER_MODE()        (__get_IPSR() != 0)
// #define IS_CPU_IN_THREAD_MODE()         (__get_IPSR() == 0)

// #define CRITICAL_SECTION_BEGIN()        uint32_t primask = __get_PRIMASK();\
//                                         __disable_irq()
// #define CRITICAL_SECTION_END()          __set_PRIMASK(primask)

/* Exported functions --------------------------------------------------------*/

/*--------------------------------------------------------------- 32-bit -----*/
/*
 *  ======== atomic_and ========
 *  atomically and integer or unsigned with mask and return its old value
 */
extern int32_t atomic_andi( volatile int32_t *dst, int32_t mask );
extern uint32_t atomic_andu( volatile uint32_t *dst, uint32_t mask );

/*
 *  ======== atomic_add ========
 *  atomically add two integer or unsigned  and return its new value
 */
extern int32_t atomic_addi( volatile int32_t *dst, int32_t *x, int32_t *y);
extern uint32_t atomic_addu( volatile uint32_t *dst, uint32_t *x, uint32_t *y);

/*
 *  ======== atomic_clear ========
 *  atomically clear integer or unsigned and return its old value
 */
extern int32_t atomic_cleari( volatile int32_t *dst );
extern uint32_t atomic_clearu( volatile uint32_t *dst );

/*
 *  ======== atomic_dec ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int32_t atomic_deci( volatile int32_t *dst );
extern uint32_t atomic_decu( volatile uint32_t *dst );

/*
 *  ======== atomic_dec_and ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int32_t atomic_dec_andi( volatile int32_t *dst, int32_t mask );
extern uint32_t atomic_dec_andu( volatile uint32_t *dst, uint32_t mask );

/*
 *  ======== atomic_dec_or ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int32_t atomic_dec_ori( volatile int32_t *dst, int32_t mask );
extern uint32_t atomic_dec_oru( volatile uint32_t *dst, uint32_t mask );

/*
 *  ======== atomic_inc ========
 *  atomically increment integer or unsigned and return new value
 */
extern int32_t atomic_inci( volatile int32_t *dst );
extern uint32_t atomic_incu( volatile uint32_t *dst );

/*
 *  ======== atomic_inc_and ========
 *  atomically increment integer or unsigned and return new value
 */
extern int32_t atomic_inc_andi( volatile int32_t *dst, int32_t mask);
extern uint32_t atomic_inc_andu( volatile uint32_t *dst, uint32_t mask);

/*
 *  ======== atomic_inc_or ========
 *  atomically increment integer or unsigned and return new value
 */
extern int32_t atomic_inc_ori( volatile int32_t *dst, int32_t mask);
extern uint32_t atomic_inc_oru( volatile uint32_t *dst, uint32_t mask);

/*
 *  ======== atomic_or ========
 *  atomically or integer or unsigned with mask and return its old value
 */
extern int32_t atomic_ori( volatile int32_t *dst, int32_t mask );
extern uint32_t atomic_oru( volatile uint32_t *dst, uint32_t mask );

/*
 *  ======== atomic_set ========
 *  atomically set integer or unsigned and return its old value
 */
extern int32_t atomic_seti( volatile int32_t *dst, int32_t x );
extern uint32_t atomic_setu( volatile uint32_t *dst, uint32_t x );

/*
 *  ======== atomic_get ========
 *  atomically get integer or unsigned and return its old value
 */
extern int32_t atomic_geti( volatile int32_t *dst );
extern uint32_t atomic_getu( volatile uint32_t *dst );

/*
 *  ======== atomic_sub ========
 *  atomically sub two integer or unsigned  and return its new value
 */
extern int32_t atomic_subi( volatile int32_t *dst, int32_t *x, int32_t *y);
extern uint32_t atomic_subu( volatile uint32_t *dst, uint32_t *x, uint32_t *y);

/*--------------------------------------------------------------- 16-bit -----*/
/*
 *  ======== atomic_and ========
 *  atomically and integer or unsigned with mask and return its old value
 */
extern int16_t atomic_andi16( volatile int16_t *dst, int16_t mask );
extern uint16_t atomic_andu16( volatile uint16_t *dst, uint16_t mask );

/*
 *  ======== atomic_add ========
 *  atomically add two integer or unsigned  and return its new value
 */
extern int16_t atomic_addi16( volatile int16_t *dst, int16_t *x, int16_t *y);
extern uint16_t atomic_addu16( volatile uint16_t *dst, uint16_t *x, uint16_t *y);

/*
 *  ======== atomic_clear ========
 *  atomically clear integer or unsigned and return its old value
 */
extern int16_t atomic_cleari16( volatile int16_t *dst );
extern uint16_t atomic_clearu16( volatile uint16_t *dst );

/*
 *  ======== atomic_dec ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int16_t atomic_deci16( volatile int16_t *dst );
extern uint16_t atomic_decu16( volatile uint16_t *dst );

/*
 *  ======== atomic_dec_and ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int16_t atomic_dec_andi16( volatile int16_t *dst, int16_t mask );
extern uint16_t atomic_dec_andu16( volatile uint16_t *dst, uint16_t mask );

/*
 *  ======== atomic_dec_or ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int16_t atomic_dec_ori16( volatile int16_t *dst, int16_t mask );
extern uint16_t atomic_dec_oru16( volatile uint16_t *dst, uint16_t mask );

/*
 *  ======== atomic_inc ========
 *  atomically increment integer or unsigned and return new value
 */
extern int16_t atomic_inci16( volatile int16_t *dst );
extern uint16_t atomic_incu16( volatile uint16_t *dst );

/*
 *  ======== atomic_inc_and ========
 *  atomically increment integer or unsigned and return new value
 */
extern int16_t atomic_inc_andi16( volatile int16_t *dst, int16_t mask);
extern uint16_t atomic_inc_andu16( volatile uint16_t *dst, uint16_t mask);

/*
 *  ======== atomic_inc_or ========
 *  atomically increment integer or unsigned and return new value
 */
extern int16_t atomic_inc_ori16( volatile int16_t *dst, int16_t mask);
extern uint16_t atomic_inc_oru16( volatile uint16_t *dst, uint16_t mask);

/*
 *  ======== atomic_or ========
 *  atomically or integer or unsigned with mask and return its old value
 */
extern int16_t atomic_ori16( volatile int16_t *dst, int16_t mask );
extern uint16_t atomic_oru16( volatile uint16_t *dst, uint16_t mask );

/*
 *  ======== atomic_set ========
 *  atomically set integer or unsigned and return its old value
 */
extern int16_t atomic_seti16( volatile int16_t *dst, int16_t x );
extern uint16_t atomic_setu16( volatile uint16_t *dst, uint16_t x );

/*
 *  ======== atomic_get ========
 *  atomically get integer or unsigned and return its old value
 */
extern int16_t atomic_geti16( volatile int16_t *dst );
extern uint16_t atomic_getu16( volatile uint16_t *dst );

/*
 *  ======== atomic_sub ========
 *  atomically sub two integer or unsigned  and return its new value
 */
extern int16_t atomic_subi16( volatile int16_t *dst, int16_t *x, int16_t *y);
extern uint16_t atomic_subu16( volatile uint16_t *dst, uint16_t *x, uint16_t *y);

/*---------------------------------------------------------------  8-bit -----*/
/*
 *  ======== atomic_and ========
 *  atomically and integer or unsigned with mask and return its old value
 */
extern int8_t atomic_andi8( volatile int8_t *dst, int8_t mask );
extern uint8_t atomic_andu8( volatile uint8_t *dst, uint8_t mask );

/*
 *  ======== atomic_clear ========
 *  atomically clear integer or unsigned and return its old value
 */
extern int8_t atomic_cleari8( volatile int8_t *dst );
extern uint8_t atomic_clearu8( volatile uint8_t *dst );

/*
 *  ======== atomic_dec ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int8_t atomic_deci8( volatile int8_t *dst );
extern uint8_t atomic_decu8( volatile uint8_t *dst );

/*
 *  ======== atomic_add ========
 *  atomically add two integer or unsigned  and return its new value
 */
extern int8_t atomic_addi8( volatile int8_t *dst, int8_t *x, int8_t *y);
extern uint8_t atomic_addu8( volatile uint8_t *dst, uint8_t *x, uint8_t *y);

/*
 *  ======== atomic_dec_and ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int8_t atomic_dec_andi8( volatile int8_t *dst, int8_t mask );
extern uint8_t atomic_dec_andu8( volatile uint8_t *dst, uint8_t mask );

/*
 *  ======== atomic_dec_or ========
 *  atomically decrement integer or unsigned and return new value
 */
extern int8_t atomic_dec_ori8( volatile int8_t *dst, int8_t mask );
extern uint8_t atomic_dec_oru8( volatile uint8_t *dst, uint8_t mask );

/*
 *  ======== atomic_inc ========
 *  atomically increment integer or unsigned and return new value
 */
extern int8_t atomic_inci8( volatile int8_t *dst );
extern uint8_t atomic_incu8( volatile uint8_t *dst );

/*
 *  ======== atomic_inc_and ========
 *  atomically increment integer or unsigned and return new value
 */
extern int8_t atomic_inc_andi8( volatile int8_t *dst, int8_t mask);
extern uint8_t atomic_inc_andu8( volatile uint8_t *dst, uint8_t mask);

/*
 *  ======== atomic_inc_or ========
 *  atomically increment integer or unsigned and return new value
 */
extern int8_t atomic_inc_ori8( volatile int8_t *dst, int8_t mask);
extern uint8_t atomic_inc_oru8( volatile uint8_t *dst, uint8_t mask);

/*
 *  ======== atomic_or ========
 *  atomically or integer or unsigned with mask and return its old value
 */
extern int8_t atomic_ori8( volatile int8_t *dst, int8_t mask );
extern uint8_t atomic_oru8( volatile uint8_t *dst, uint8_t mask );

/*
 *  ======== atomic_set ========
 *  atomically set integer or unsigned and return its old value
 */
extern int8_t atomic_seti8( volatile int8_t *dst, int8_t x );
extern uint8_t atomic_setu8( volatile uint8_t *dst, uint8_t x );

/*
 *  ======== atomic_get ========
 *  atomically get integer or unsigned and return its old value
 */
extern int8_t atomic_geti8( volatile int8_t *dst );
extern uint8_t atomic_getu8( volatile uint8_t *dst );

/*
 *  ======== atomic_sub ========
 *  atomically sub two integer or unsigned  and return its new value
 */
extern int8_t atomic_subi8( volatile int8_t *dst, int8_t *x, int8_t *y);
extern uint8_t atomic_subu8( volatile uint8_t *dst, uint8_t *x, uint8_t *y);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __atomic__ */
/*
 *  @(#) ti.bios; 5, 6, 0,505; 10-7-2011 13:48:13; /db/vtree/library/trees/avala/avala-p52x/src/ xlibrary

 */

