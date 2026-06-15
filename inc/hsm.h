/**
  * @file hsm.h
  * @brief Hierarchical State Machine (HSM) framework header file.
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2026/04/22
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
  * 	2026/04/22	0.1			Leon Lee		Preliminary version.
  */

#ifndef __HSM_H__
#define __HSM_H__

#include <stdint.h>
#include <stddef.h>
#include "hsm_event.h"

/**
  * @brief HSM return status codes
  */
typedef enum 
{
    HSM_RET_HANDLED = 0,        /*!< Event was handled in the current state  */ 
    HSM_RET_UNHANDLED,          /*!< Event was not handled in the current state */
    HSM_RET_SUPER,              /*!< Event was not handled, but should be passed to the super state */
    HSM_RET_IGNORED,            /*!< Event was not handled, and should be ignored */
    HSM_RET_TRANSITION,         /*!< State transition should occur to a new state */
    HSM_RET_ERROR               /*!< An error occurred during event processing */
} HSM_Ret_t;    


struct  HSM_State_t;
struct  HSM_t;

typedef HSM_Ret_t (*HSM_StateHandler_t)(struct HSM_t* const me, const HSM_Event_t* const e);


/**
  * @brief HSM state structure
  */
typedef struct HSM_State_t
{
    char const *tag;                        /*!< State name */
    HSM_StateHandler_t handler;             /*!< State handler function pointer */
    struct HSM_State_t const *super;        /*!< Pointer to the super state (parent state) */
} HSM_State_t;


/**
  * @brief HSM context structure
  */
typedef struct HSM_t
{
    const HSM_State_t *current;             /*!< Pointer to the current active state */
    const HSM_State_t *next;                /*!< Pointer to the next state during a transition */
    void *data;                             /*!< Pointer to user-defined data (optional) 
                                                 for data transfer between states */
} HSM_t;

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

void HSM_init(HSM_t* const me, const HSM_State_t* const initial);
void HSM_dispatch(HSM_t* const me, const HSM_Event_t* const e);
void HSM_transition(HSM_t* const me, const HSM_State_t* const target, void *arg);
void *HSM_getData(HSM_t* const me);

#ifdef __cplusplus
}
#endif /* extern "C" */ 

#endif /* __HSM_H__ */      
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
