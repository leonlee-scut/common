/** @file iq_pid.c
  * @brief IQ PID controller implementation.
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2026/06/29
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
  * 	2026/06/29	0.1			Leon Lee		Preliminary version.
  */

#include "iq_pid.h"

/** 
  * @brief Initialize the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param init Pointer to the initialization structure.
  *
  */
void iqPID_init(iqPID_t *pid, const iqPID_PARAM_t *init)
{
    pid->target    = init->target;
    pid->Kp        = init->Kp;
    pid->Ki        = init->Ki;
    pid->Kd        = init->Kd;
    pid->Kb        = init->Kb;
    pid->maxout    = init->maxout;
    pid->minout    = init->minout;
    pid->threshold = init->threshold;
    pid->prev_err  = 0;
    pid->integral  = 0;

    if (pid->maxout < pid->minout)
    {
        // Swap maxout and minout if they are in the wrong order
        _IQswap(&pid->maxout, &pid->minout);
    }
}


/** 
  * @brief Calculate the output of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param measurement The measured value.
  * @return The calculated output.
  *
  */
_iq iqPID_calculate(iqPID_t* pid, _iq measurement)
{
        // 1. Calculate error
    _iq err   = pid->target - measurement;

    // 2. Calculate proportional term and derivative term
    _iq p_term = _IQmpy(pid->Kp, err); // p_term = pid->Kp * err;
    _iq d_term = _IQmpy(pid->Kd, (err - pid->prev_err)); // d_term = pid->Kd * (err - pid->prev_err);

    // 3. Calculate integral term with anti-windup and integral separation
    _iq i_term = _IQmpy(pid->Ki, err) + pid->integral;
    
    if (_IQabs(err) > pid->threshold)
    {
        pid->integral = 0; // Reset integral term if error exceeds threshold
        i_term = 0; // Reset integral term if error exceeds threshold
    }

    // 4. Calculate the output before saturation
    _iq v_output = p_term + i_term + d_term;
    _iq u_output = v_output;

    // 5. Apply output saturation
    _IQsat(u_output, pid->maxout, pid->minout);

    // 6. Update integral term with anti-windup
    _iq sat_err = u_output - v_output; 
    pid->integral = i_term + _IQmpy(pid->Kb, sat_err); 

    // 7. Update previous error
    pid->prev_err = err;

    return u_output;
}


/** 
  * @brief Reset the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  *
  */
void iqPID_reset(iqPID_t* pid)
{
    pid->prev_err = 0;
    pid->integral = 0;
}


/** 
  * @brief Get the parameters of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param param Pointer to the IQ PID parameter structure to be filled.
  *
  */
void iqPID_getParameters(const iqPID_t* pid, iqPID_PARAM_t* param)
{
    param->target    = pid->target;
    param->Kp        = pid->Kp;
    param->Ki        = pid->Ki;
    param->Kd        = pid->Kd;
    param->Kb        = pid->Kb;
    param->maxout    = pid->maxout;
    param->minout    = pid->minout;
    param->threshold = pid->threshold;
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
