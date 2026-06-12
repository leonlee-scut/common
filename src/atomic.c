/*
 **************** (C) COPYRIGHT 2012 South China Univ. of Tech. ****************
 ** File Name     : atomic.c
 ** Author        : Leon
 ** Version       : V1.0
 ** Date          : 2012-4-24-下午4:57:41
 ** Description   : Atomic processor operations:
 **                     ATM_and()   ATM_clear() ATM_dec()
 **                     ATM_inc()   ATM_or()    ATM_set()
 **
 **                 Can be used under RTX OS only!!!
 *******************************************************************************
 ** History:
 **   2012-4-24  PM4:57:41  ver 1.00    Prelimnary version, first Release
 **   2020-2-26             ver 2.00    屏弃SVC调用方式，改为屏蔽中断，更加通用
 **
 *******************************************************************************
 ** SVN CONTROL
 **=====================
 **  File name    : $HeadURL$
 **  Revision     : $Revison$
 **  Last modified: $Date$
 **             by: $Author$
 *******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "critical_section.h"

/* Public variables ----------------------------------------------------------*/
/* Private typedefs ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/*--------------------------------------------------------------- 32-bit -----*/
/*
 *  ======== atomic_and ========
 *  atomically and integer or unsigned with mask and return its old value
 */
int32_t atomic_andi(volatile int32_t *dst, int32_t mask)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* andi                 */
    ival = *dst;
    *dst = ival & mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_andu(volatile uint32_t *dst, uint32_t mask)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* andu                 */
    uval = *dst;
    *dst = uval & mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_add ========
 *  atomically add two integer or unsigned and return the new value
 */
int32_t atomic_addi(volatile int32_t *dst, int32_t *x, int32_t *y)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* addi                 */
    ival = *x + *y;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_addu(volatile uint32_t *dst, uint32_t *x, uint32_t *y)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* addu                 */
    uval = *x + *y;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_clear ========
 *  atomically clear integer or unsigned and return its old value
 */

 int32_t atomic_cleari(volatile int32_t *dst)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* clear                */
    ival = *dst;
    *dst = 0;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_clearu(volatile uint32_t *dst)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* clear                */
    uval = *dst;
    *dst = 0;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_dec ========
 *  atomically decrement integer or unsigned and return new value
 */
int32_t atomic_deci(volatile int32_t *dst)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = *dst - 1;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_decu(volatile uint32_t *dst)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = *dst - 1;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_dec_and ========
 *  atomically decrement integer or unsigned, and with the mask, then return
 *  new value
 */
int32_t atomic_dec_andi(volatile int32_t *dst, int32_t mask)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst - 1) & mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_dec_andu(volatile uint32_t *dst, uint32_t mask)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst - 1) & mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_dec_or ========
 *  atomically decrement integer or unsigned, or with the mask, then return the
 *  new value
 */
int32_t atomic_dec_ori(volatile int32_t *dst, int32_t mask)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst - 1) | mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_dec_oru(volatile uint32_t *dst, uint32_t mask)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst - 1) | mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc ========
 *  atomically increment integer or unsigned and return new value
 */
int32_t atomic_inci(volatile int32_t *dst)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* ++                   */
    ival = *dst + 1;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_incu(volatile uint32_t *dst)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* ++                   */
    uval = *dst + 1;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc_and ========
 *  atomically increment integer or unsigned, and with the mask, then return
 *  new value
 */
int32_t atomic_inc_andi(volatile int32_t *dst, int32_t mask)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst + 1) & mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_inc_andu(volatile uint32_t *dst, uint32_t mask)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst + 1) & mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc_or ========
 *  atomically decrement integer or unsigned, or with the mask, then return the
 *  new value
 */
int32_t atomic_inc_ori(volatile int32_t *dst, int32_t mask)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst + 1) | mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_inc_oru(volatile uint32_t *dst, uint32_t mask)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst + 1) | mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_or ========
 *  atomically or integer or unsigned with mask and return its old value
 */
int32_t atomic_ori(volatile int32_t *dst, int32_t mask)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* or                   */
    ival = *dst;
    *dst = ival | mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_oru(volatile uint32_t *dst, uint32_t mask)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* or                   */
    uval = *dst;
    *dst = uval | mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_set ========
 *  atomically set integer or unsigned and return its old value
 */
int32_t atomic_seti(volatile int32_t *dst, int32_t x)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* set                  */
    ival = *dst;
    *dst = x;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_setu(volatile uint32_t *dst, uint32_t x)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* set                  */
    uval = *dst;
    *dst = x;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_get ========
 *  atomically get integer or unsigned and return its old value
 */
int32_t atomic_geti(volatile int32_t *dst)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* get                  */
    ival = *dst;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_getu(volatile uint32_t *dst)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* get                  */
    uval = *dst;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_sub ========
 *  atomically sub two integer or unsigned and return the new value
 */
int32_t atomic_subi(volatile int32_t *dst, int32_t *x, int32_t *y)
{
    int32_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* subi                 */
    ival = *x - *y;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint32_t atomic_subu(volatile uint32_t *dst, uint32_t *x, uint32_t *y)
{
    uint32_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* subu                 */
    uval = *x - *y;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*--------------------------------------------------------------- 16-bit -----*/
/*
 *  ======== atomic_and ========
 *  atomically and integer or unsigned with mask and return its old value
 */
int16_t atomic_andi16(volatile int16_t *dst, int16_t mask)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* andi                 */
    ival = *dst;
    *dst = ival & mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_andu16(volatile uint16_t *dst, uint16_t mask)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* andu                 */
    uval = *dst;
    *dst = uval & mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_add ========
 *  atomically add two integer or unsigned and return the new value
 */
int16_t atomic_addi16(volatile int16_t *dst, int16_t *x, int16_t *y)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* addi16                 */
    ival = *x + *y;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_addu16(volatile uint16_t *dst, uint16_t *x, uint16_t *y)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* addu16                 */
    uval = *x + *y;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_clear ========
 *  atomically clear integer or unsigned and return its old value
 */
int16_t atomic_cleari16(volatile int16_t *dst)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* clear                */
    ival = *dst;
    *dst = 0;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_clearu16(volatile uint16_t *dst)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* clear                */
    uval = *dst;
    *dst = 0;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_dec ========
 *  atomically decrement integer or unsigned and return new value
 */
int16_t atomic_deci16(volatile int16_t *dst)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = *dst - 1;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_decu16(volatile uint16_t *dst)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = *dst - 1;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_dec_and ========
 *  atomically decrement integer or unsigned, and with the mask, then return
 *  new value
 */
int16_t atomic_dec_andi16(volatile int16_t *dst, int16_t mask)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst - 1) & mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_dec_andu16(volatile uint16_t *dst, uint16_t mask)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst - 1) & mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_dec_or ========
 *  atomically decrement integer or unsigned, or with the mask, then return the
 *  new value
 */
int16_t atomic_dec_ori16(volatile int16_t *dst, int16_t mask)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst - 1) | mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_dec_oru16(volatile uint16_t *dst, uint16_t mask)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst - 1) | mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc ========
 *  atomically increment integer or unsigned and return new value
 */
int16_t atomic_inci16(volatile int16_t *dst)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* ++                   */
    ival = *dst + 1;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_incu16(volatile uint16_t *dst)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* ++                   */
    uval = *dst + 1;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc_and ========
 *  atomically increment integer or unsigned, and with the mask, then return
 *  new value
 */
int16_t atomic_inc_andi16(volatile int16_t *dst, int16_t mask)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst + 1) & mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_inc_andu16(volatile uint16_t *dst, uint16_t mask)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst + 1) & mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc_or ========
 *  atomically decrement integer or unsigned, or with the mask, then return the
 *  new value
 */
int16_t atomic_inc_ori16(volatile int16_t *dst, int16_t mask)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst + 1) | mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_inc_oru16(volatile uint16_t *dst, uint16_t mask)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst + 1) | mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_or ========
 *  atomically or integer or unsigned with mask and return its old value
 */
int16_t atomic_ori16(volatile int16_t *dst, int16_t mask)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* or                   */
    ival = *dst;
    *dst = ival | mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_oru16(volatile uint16_t *dst, uint16_t mask)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* or                   */
    uval = *dst;
    *dst = uval | mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_set ========
 *  atomically set integer or unsigned and return its old value
 */
int16_t atomic_seti16(volatile int16_t *dst, int16_t x)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* set                  */
    ival = *dst;
    *dst = x;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_setu16(volatile uint16_t *dst, uint16_t x)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* set                  */
    uval = *dst;
    *dst = x;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_get ========
 *  atomically get integer or unsigned and return its old value
 */
int16_t atomic_geti16(volatile int16_t *dst)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* get                  */
    ival = *dst;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_getu16(volatile uint16_t *dst)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* get                  */
    uval = *dst;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_sub ========
 *  atomically sub two integer or unsigned and return the new value
 */
int16_t atomic_subi16(volatile int16_t *dst, int16_t *x, int16_t *y)
{
    int16_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* subi16                 */
    ival = *x - *y;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint16_t atomic_subu16(volatile uint16_t *dst, uint16_t *x, uint16_t *y)
{
    uint16_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* subu16                 */
    uval = *x - *y;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*---------------------------------------------------------------  8-bit -----*/
/*
 *  ======== atomic_and ========
 *  atomically and integer or unsigned with mask and return its old value
 */
int8_t atomic_andi8(volatile int8_t *dst, int8_t mask)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* andi                 */
    ival = *dst;
    *dst = ival & mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_andu8(volatile uint8_t *dst, uint8_t mask)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* andu                 */
    uval = *dst;
    *dst = uval & mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_add ========
 *  atomically add two integer or unsigned and return the new value
 */
int8_t atomic_addi8(volatile int8_t *dst, int8_t *x, int8_t *y)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* addi8                 */
    ival = *x + *y;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_addu8(volatile uint8_t *dst, uint8_t *x, uint8_t *y)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* addu8                 */
    uval = *x + *y;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_clear ========
 *  atomically clear integer or unsigned and return its old value
 */
int8_t atomic_cleari8(volatile int8_t *dst)
{

    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* clear                */
    ival = *dst;
    *dst = 0;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

 uint8_t atomic_clearu8(volatile uint8_t *dst)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* clear                */
    uval = *dst;
    *dst = 0;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_dec ========
 *  atomically decrement integer or unsigned and return new value
 */
int8_t atomic_deci8(volatile int8_t *dst)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = *dst - 1;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_decu8(volatile uint8_t *dst)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = *dst - 1;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}



/*
 *  ======== atomic_dec_and ========
 *  atomically decrement integer or unsigned, and with the mask, then return
 *  new value
 */
int8_t atomic_dec_andi8(volatile int8_t *dst, int8_t mask)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst - 1) & mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_dec_andu8(volatile uint8_t *dst, uint8_t mask)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst - 1) & mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_dec_or ========
 *  atomically decrement integer or unsigned, or with the mask, then return the
 *  new value
 */
int8_t atomic_dec_ori8(volatile int8_t *dst, int8_t mask)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst - 1) | mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_dec_oru8(volatile uint8_t *dst, uint8_t mask)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst - 1) | mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc ========
 *  atomically increment integer or unsigned and return new value
 */
int8_t atomic_inci8(volatile int8_t *dst)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* ++                   */
    ival = *dst + 1;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_incu8(volatile uint8_t *dst)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* ++                   */
    uval = *dst + 1;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc_and ========
 *  atomically increment integer or unsigned, and with the mask, then return
 *  new value
 */
int8_t atomic_inc_andi8(volatile int8_t *dst, int8_t mask)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst + 1) & mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_inc_andu8(volatile uint8_t *dst, uint8_t mask)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst + 1) & mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_inc_or ========
 *  atomically decrement integer or unsigned, or with the mask, then return the
 *  new value
 */
int8_t atomic_inc_ori8(volatile int8_t *dst, int8_t mask)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    ival = (*dst + 1) | mask;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_inc_oru8(volatile uint8_t *dst, uint8_t mask)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* --                   */
    uval = (*dst + 1) | mask;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_or ========
 *  atomically or integer or unsigned with mask and return its old value
 */
int8_t atomic_ori8(volatile int8_t *dst, int8_t mask)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* or                   */
    ival = *dst;
    *dst = ival | mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_oru8(volatile uint8_t *dst, uint8_t mask)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* or                   */
    uval = *dst;
    *dst = uval | mask;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_set ========
 *  atomically set integer or unsigned and return its old value
 */
int8_t atomic_seti8(volatile int8_t *dst, int8_t x)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* set                  */
    ival = *dst;
    *dst = x;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_setu8(volatile uint8_t *dst, uint8_t x)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* set                  */
    uval = *dst;
    *dst = x;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_get ========
 *  atomically get integer or unsigned and return its old value
 */
int8_t atomic_geti8(volatile int8_t *dst)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* get                  */
    ival = *dst;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_getu8(volatile uint8_t *dst)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* get                  */
    uval = *dst;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}


/*
 *  ======== atomic_sub ========
 *  atomically sub two integer or unsigned and return the new value
 */
int8_t atomic_subi8(volatile int8_t *dst, int8_t *x, int8_t *y)
{
    int8_t ival;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* subi8                 */
    ival = *x - *y;
    *dst = ival;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return ival;
}

uint8_t atomic_subu8(volatile uint8_t *dst, uint8_t *x, uint8_t *y)
{
    uint8_t uval;

    /* Disable interrupt    */

    CRITICAL_SECTION_BEGIN();

    /* subu8                 */
    uval = *x - *y;
    *dst = uval;

    /* Restore interrupt    */

    CRITICAL_SECTION_END();

    /* return value         */
    return uval;
}

/************************************************** End of file: atomic.c *****/
