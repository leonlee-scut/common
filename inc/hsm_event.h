/**
  * @file hsm_event.h
  * @brief Header file for Hierarchical State Machine (HSM) event definitions.
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2026/04/27
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
  * 	2026/04/27	0.1			Leon Lee		Preliminary version.
  */

#ifndef __HSM_EVENT_H__
#define __HSM_EVENT_H__

#include <stdint.h>
#include <stddef.h>
#include "cmsis_os2.h"

/**
  * @brief HSM signal identifiers
  * @note User-defined signals should start from HSM_SIG_USER to avoid conflicts 
  *       with reserved signals.
  */
#define HSM_SIG_ENTRY   (uint16_t)(-3)  /*!< Signal for state entry action */
#define HSM_SIG_INIT    (uint16_t)(-2)  /*!< Signal for state initialization */
#define HSM_SIG_EXIT    (uint16_t)(-1)  /*!< Signal for state exit action */
#define HSM_SIG_USER    (uint16_t)( 1)  /*!< User-defined signals start from this value */


/**
  * @brief HSM event structure
  */
typedef struct HSM_Event_t      
{
    uint16_t sig;               /*!< Signal identifier */
    void *data;                 /*!< Pointer to event-specific data (optional) */
} HSM_Event_t;


typedef osMessageQueueId_t      HSM_EventQ_t;


typedef enum 
{
    HSM_EventQ_SUCCESS = 0,  /*!< Event was successfully posted to the queue */
    HSM_EventQ_FULL,         /*!< Event queue is full, event was not posted */
    HSM_EventQ_ERROR         /*!< An error occurred while posting the event */
} HSM_EventQStatus_t;

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

HSM_EventQStatus_t HSM_event_queue_init(HSM_EventQ_t* const queue_id, 
                                        uint32_t            queue_length, 
                                        uint32_t            item_size, 
                                        char const*         queue_name);
HSM_EventQStatus_t HSM_event_queue_reset(HSM_EventQ_t queue_id);
HSM_EventQStatus_t HSM_event_post(HSM_EventQ_t             queue_id, 
                                  const HSM_Event_t* const e, 
                                  uint32_t                 timeout_ms);
HSM_EventQStatus_t HSM_event_post_from_isr(HSM_EventQ_t             queue_id, 
                                           const HSM_Event_t* const e);
HSM_EventQStatus_t HSM_event_get(HSM_EventQ_t             queue_id, 
                                 HSM_Event_t* const       e, 
                                 uint32_t                 timeout_ms);
HSM_EventQStatus_t HSM_event_get_from_isr(HSM_EventQ_t             queue_id, 
                                          HSM_Event_t* const       e);                                 

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __HSM_EVENT_H__ */        
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
