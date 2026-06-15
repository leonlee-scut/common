/**
  * @file hsm.c
  * @brief Hierarchical State Machine (HSM) framework source file.
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

#include "hsm.h"
#include "assert.h"

/* Private variables */
static HSM_Event_t const ENTRY_EVENT = { .sig = HSM_SIG_ENTRY, .data = NULL };
static HSM_Event_t const INIT_EVENT  = { .sig = HSM_SIG_INIT,  .data = NULL };
static HSM_Event_t const EXIT_EVENT  = { .sig = HSM_SIG_EXIT,  .data = NULL };


/* Private functions prototypes */
static void __state_transition(HSM_t* const me, const HSM_State_t* const target);
static void __state_exit(HSM_t* const me, const HSM_State_t* const top_super);


/* Private functions */
/**
  * @brief Performs a target transition to the specified new target. 
  *        This function handles the exit of the current state, 
  *        entry of the new state, and initialization of the new state.
  * 
  * @param me HSM instance pointer
  * @param target New state pointer to transition to
  */
static void __state_transition(HSM_t* const me, const HSM_State_t* const target)
{
    me->current = target;
    me->next = NULL;

    // Trigger entry action for the new state
    me->current->handler(me, &ENTRY_EVENT);

    // Trigger initialization action for the new state
    if (me->current->handler(me, &INIT_EVENT) == HSM_RET_TRANSITION)
    {
        // Handle state transition during initialization
        if (me->next != NULL)
        {
            // Enter and initialize next state recursively without exit event.
            __state_transition(me, me->next);
        }
    }
}


/**
  * @brief Recursively exits the current state and all its super states up to 
  *        the specified top_super state.
  *
  * @param me HSM instance pointer 
  * @param top_super Top-most super state to stop exiting at (inclusive)
  */
static void __state_exit(HSM_t* const me, const HSM_State_t* const top_super)
{
    /*
     * From current state to its super state, trigger exit action for each 
     * state until the specified Top-most super state (top_super) is reached
     */
    me->current->handler(me, &EXIT_EVENT);  // Trigger exit action for current state
    
    if (me->current != top_super && me->current->super != NULL)
    {
        me->current = me->current->super;   // Move up to super state
        __state_exit(me, top_super);        // Recursively exit super states
    }
}


/* Public functions */
/**
  * @brief Initializes the HSM with the initial state. 
  *        This function should be called before dispatching any events.
  * 
  * @param me HSM instance pointer
  * @param initial Initial state pointer
  */
void HSM_init(HSM_t* const me, const HSM_State_t* const initial)
{
    assert(me != NULL);
    assert(initial != NULL);
    
    // Initialize user-defined data pointer to NULL
    me->data = NULL; 

    // Transition to the initial state
    __state_transition(me, initial);
}


/**
  * @brief Dispatches an event to the current state.
  * 
  * @param me HSM instance pointer
  * @param e Event pointer
  */
void HSM_dispatch(HSM_t* const me, const HSM_Event_t* const e)
{
    assert(me != NULL);
    assert(e != NULL);
    
    const HSM_State_t* state = me->current;
    HSM_Ret_t ret;

    while (state != NULL)
    {
        ret = state->handler(me, e);
        
        if (ret == HSM_RET_HANDLED || ret == HSM_RET_IGNORED)
        {
            break; // Event was handled or ignored, stop processing
        }
        else if (ret == HSM_RET_SUPER || ret == HSM_RET_UNHANDLED)
        {
            state = state->super; // Pass event to super state
        }
        else if (ret == HSM_RET_TRANSITION)
        {
            // Handle state transition
            if (me->next != NULL)
            {
                // Exit current state and all its super states up to the 
                // specified top-most super state recursively 
                __state_exit(me, state);

                // Transition to the next state recursively without exit event.
                __state_transition(me, me->next);
            }

            break; // Transition handled, stop processing
        }
        else if (ret == HSM_RET_ERROR)
        {
            // Handle error (could log or assert here)
            assert(0 && "Error occurred during event processing");
            break; // Stop processing on error
        }
    }
}

/**
  * @brief Initiate a state transition to the target state. 
  *        The actual transition will occur on the next call to HSM_dispatch().
  * 
  * @param me HSM instance pointer
  * @param target Target state pointer
  * @param arg Argument pointer for the transition (optional, can be NULL)
  */
void HSM_transition(HSM_t* const me, const HSM_State_t* const target, void *arg)
{
    assert(me != NULL);
    assert(target != NULL);

    me->next = target;
    me->data = arg;
}


/**
  * @brief Retrieves the user-defined data pointer associated with the HSM instance.
  * 
  * @param me HSM instance pointer
  * @return Pointer to the user-defined data (or NULL if not set)
  */
void* HSM_getData(HSM_t* const me)
{
    return me->data;
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
