/**
  * @file hsm_event.c
  * @brief Source file for Hierarchical State Machine (HSM) event handling functions.
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2026/04/28
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
  * 	2026/04/28	0.1			Leon Lee		Preliminary version.
  */

#include "hsm_event.h"
#include "assert.h"


/**
  * @brief Initializes an HSM event queue with the specified parameters.
  * 
  * @param queue_id Pointer to the event queue identifier to be initialized
  * @param queue_length Length of the event queue
  * @param item_size Size of each event item
  * @param queue_name Name of the event queue
  * @return HSM_EventQStatus_t Status code indicating success or failure of the operation
  */
HSM_EventQStatus_t HSM_event_queue_init(HSM_EventQ_t* const queue_id, 
                                        uint32_t            queue_length, 
                                        uint32_t            item_size, 
                                        char const*         queue_name)
{
    assert(queue_id != NULL);

    HSM_EventQStatus_t ret = HSM_EventQ_SUCCESS;
    osMessageQueueId_t msg_q_id;
    const osMessageQueueAttr_t attr = { .name = queue_name };

    msg_q_id = osMessageQueueNew(queue_length, item_size, &attr);

    if (msg_q_id == NULL)
    {
        ret = HSM_EventQ_ERROR;
    }

    *queue_id = msg_q_id;

    return ret;
}


/**
  * @brief Resets an HSM event queue.
  * 
  * @param queue_id The identifier of the event queue to reset
  * @return HSM_EventQStatus_t Status code indicating success or failure of the operation
  */
HSM_EventQStatus_t HSM_event_queue_reset(HSM_EventQ_t queue_id)
{
    if (osMessageQueueReset(queue_id) == osOK)
    {
        return HSM_EventQ_SUCCESS;
    }
    else
    {
        return HSM_EventQ_ERROR;
    }
}


/**
  * @brief Posts an event to an HSM event queue.
  * 
  * @param queue_id The identifier of the event queue to post the event to
  * @param e Pointer to the event to be posted
  * @param timeout_ms Timeout value in milliseconds for posting the event
  * @return HSM_EventQStatus_t Status code indicating success or failure of the operation
  */
HSM_EventQStatus_t HSM_event_post(HSM_EventQ_t             queue_id, 
                                  const HSM_Event_t* const e, 
                                  uint32_t                 timeout_ms)
{
    assert(e != NULL);

    if (osMessageQueuePut(queue_id, e, 0u, timeout_ms) == osOK)
    {
        return HSM_EventQ_SUCCESS;
    }
    else
    {
        return HSM_EventQ_FULL;
    }
}


/**
  * @brief Posts an event to an HSM event queue from within an interrupt service routine.
  * 
  * @param queue_id The identifier of the event queue to post the event to
  * @param e Pointer to the event to be posted
  * @return HSM_EventQStatus_t Status code indicating success or failure of the operation
  */
HSM_EventQStatus_t HSM_event_post_from_isr(HSM_EventQ_t             queue_id, 
                                           const HSM_Event_t* const e)
{
    assert(e != NULL);

    if (osMessageQueuePut(queue_id, e, 0u, 0u) == osOK)
    {
        return HSM_EventQ_SUCCESS;
    }
    else
    {
        return HSM_EventQ_FULL;
    }
}


/**
  * @brief Retrieves an event from an HSM event queue.
  * 
  * @param queue_id The identifier of the event queue to retrieve the event from
  * @param e Pointer to the event to be retrieved
  * @param timeout_ms Timeout value in milliseconds for retrieving the event
  * @return HSM_EventQStatus_t Status code indicating success or failure of the operation
  */
HSM_EventQStatus_t HSM_event_get(HSM_EventQ_t             queue_id, 
                                 HSM_Event_t* const       e, 
                                 uint32_t                 timeout_ms)
{
    assert(e != NULL);

    if (osMessageQueueGet(queue_id, e, NULL, timeout_ms) == osOK)
    {
        return HSM_EventQ_SUCCESS;
    }
    else
    {
        return HSM_EventQ_ERROR;
    }
}


/**
  * @brief Retrieves an event from an HSM event queue from within an interrupt service routine.
  * 
  * @param queue_id The identifier of the event queue to retrieve the event from
  * @param e Pointer to the event to be retrieved
  * @return HSM_EventQStatus_t Status code indicating success or failure of the operation
  */
HSM_EventQStatus_t HSM_event_get_from_isr(HSM_EventQ_t             queue_id, 
                                          HSM_Event_t* const       e)
{
    assert(e != NULL);

    if (osMessageQueueGet(queue_id, e, NULL, 0u) == osOK)
    {
        return HSM_EventQ_SUCCESS;
    }
    else
    {
        return HSM_EventQ_ERROR;
    }
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
