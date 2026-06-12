/*
 **************** (C) COPYRIGHT 2012 South China Univ. of Tech. ****************
 ** File Name     : fxn.h
 ** Author        : Leon
 ** Version       : V1.0
 ** Date          : 2012-2-15-上午9:27:40
 ** Description   :
 *******************************************************************************
 ** History:
 **   2012-2-15 上午9:27:40  ver 1.00    Prelimnary version, first Release
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FXN_H__
#define __FXN_H__

#ifdef __cplusplus
extern "C"
{
#endif /* extern "C" */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
typedef void *Ptr;

typedef void *Arg;

typedef int32_t (*Fxn)(Arg arg0, Arg arg1);

typedef Fxn FXN_Handle;

/*
 * CALL BACK FUNCTIONs
 */
typedef struct
{
	Fxn cbFxn;
	Arg arg0;
	Arg arg1;
} CBFXN_t;

/* Exported constants --------------------------------------------------------*/
#define ARG_NOT_USE     (void)

/* Exported variables --------------------------------------------------------*/
extern CBFXN_t CbFxn_nop;

/* Exported macros -----------------------------------------------------------*/
/*
 * These macros are used to cast 'Arg' types to 'Int' or 'Ptr'.
 */
#define ArgToInt(A)                 ((int32_t)(A))
#define ArgToPtr(A)                 ((Ptr)(A))

#define NO_USE_ARGUMENT(arg)        (void)(arg)

/* Exported functions --------------------------------------------------------*/
int32_t FXN_nop(Arg arg0, Arg arg1);

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /* __FXN_H__ */
/**************************************************** End of file: fxn.h ******/
