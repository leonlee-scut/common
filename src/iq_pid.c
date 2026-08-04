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

/**
  * @note 
  *  1. This implementation of the IQ PID controller is based on Texas Instruments'
  *     PID_REG3 anti-windup PID controller, Version 3.20, 04-15-2005.
  *
  *  2. 代码中的 Kp, Ki, Kd 参数与传统 PID 算法中的参数 (如Ziegler-Nichols法整定的参数)
  *     是有区别的:
  *
  *     ① Kp（比例增益）
  *        区别： 无区别。代码中的 Kp 与传统 PID 中的 Kp 完全一致。 
  * 
  *     ② Ki（积分增益）—— 主要差异点 1
  *        传统 PID： 积分步进量直接作用于误差 Err。
  *        代码 PID： 积分步进量作用于比例输出 p_term。  
  *        参数转换关系：
  *
  *                     Ki_trad 
  *              Ki = -----------,    其中，Ki_trad 为传统 PID 中的 Ki
  *                       Kp
  *
  *        工程影响：
  *          在代码的写法中，Ki 本质上是一个相对比例系数（比例项的百分之多少累加进积分）。
  *          当你修改 Kp 时，代码中的积分作用会自动随 Kp 缩放，这在调参时有利于保持系统的
  *          相对阻尼特性。
  *
  *     ③ Kd（微分增益）—— 主要差异点 2
  *        传统 PID： 微分项直接对误差变化量作差：Kd_trad * (e[k] - e[k-1])。
  *        代码 PID： 微分项对比例输出变化量作差：Kd * (p_term[k] - p_term1[k-1])。  
  *        参数转换关系：
  *
  *                     Kd_trad
  *              Kd = -----------,    其中，Kd_trad 为传统 PID 中的 Kd
  *                       Kp
  *
  *        工程影响： 
  *          同样地，代码中的 Kd 也被 Kp 归一化了。
  *
  *     ④ Kc（积分抗饱和矫正增益）—— 传统 PID 所没有
  *        传统 PID： 通常没有此项，或采用硬限幅（停止积分）。
  *        代码 PID： Kc 用于控制抗饱和回退（Back-Calculation）的强度。  
  *        工程经验值： 通常 Kc 的取值在 Ki 附近，或设置为 1/Kp 到 1 之间，用于快速拉回
  *        饱和超出量。
  *   
  */  

#include <string.h>
#include "assert.h"
#include "iq_pid.h"

/** 
  * @brief Initialize the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param init Pointer to the initialization structure.
  *
  */
void iqPID_init(iqPID_t *pid, const iqPID_PARAM_t *init)
{
    assert(pid != NULL);
    assert(init != NULL);

    // Initialize the PID controller
    memset(pid, 0, sizeof(iqPID_t));

    pid->Kp        = init->Kp;
    pid->Ki        = init->Ki;
    pid->Kd        = init->Kd;
    pid->Kc        = init->Kc;
    pid->maxout    = init->maxout;
    pid->minout    = init->minout;

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
    assert(pid != NULL);

    pid->feedback = measurement;

    // 1. Calculate error
    pid->err   = pid->target - measurement;

    // 2. Calculate proportional term 
    pid->p_term = _IQmpy(pid->Kp, pid->err); 

    // 3. Calculate integral term with anti-windup and integral separation
    pid->i_term += _IQmpy(pid->Ki, pid->p_term1) + _IQmpy(pid->Kc, pid->sat_err);

    // 4. Calculate derivative term
    pid->d_term = _IQmpy(pid->Kd, (pid->p_term - pid->p_term1));

    // 5. Calculate the output before saturation
    pid->pre_sat = pid->p_term + pid->i_term + pid->d_term;

    // 6. Apply output saturation
    pid->output = _IQsat(pid->pre_sat, pid->maxout, pid->minout);

    // 7. Update the saturate difference
    pid->sat_err = pid->output - pid->pre_sat; 

    // 8. Update previous proportional term for next derivative calculation
    pid->p_term1 = pid->p_term;

    return pid->output;
}

/** 
  * @brief Calculate the output of the IQ PI controller.
  * @param pid Pointer to the IQ PI controller instance.
  * @param measurement The measured value.
  * @return The calculated output.
  *
  */
_iq iqPI_calculate(iqPID_t* pid, _iq measurement)
{
    assert(pid != NULL);

    pid->feedback = measurement;

    // 1. Calculate error
    pid->err   = pid->target - measurement;

    // 2. Calculate proportional term 
    pid->p_term = _IQmpy(pid->Kp, pid->err); 

    // 3. Calculate integral term with anti-windup and integral separation
    pid->i_term += _IQmpy(pid->Ki, pid->p_term) + _IQmpy(pid->Kc, pid->sat_err);

    // 4. Calculate the output before saturation
    pid->pre_sat = pid->p_term + pid->i_term;

    // 5. Apply output saturation
    pid->output = _IQsat(pid->pre_sat, pid->maxout, pid->minout);

    // 6. Update the saturate difference
    pid->sat_err = pid->output - pid->pre_sat; 

    // 7. Update previous proportional term for next derivative calculation
    pid->p_term1 = pid->p_term;

    return pid->output;
}


/** 
  * @brief Reset the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  *
  */
void iqPID_reset(iqPID_t* pid)
{
    assert(pid != NULL);
    
    pid->target   = 0;
    pid->feedback = 0;
    pid->err      = 0;
    pid->p_term   = 0;
    pid->i_term   = 0;
    pid->d_term   = 0;
    pid->sat_err  = 0;
    pid->pre_sat  = 0;
    pid->p_term1  = 0;
    pid->output   = 0;
}


/** 
  * @brief Get the parameters of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param param Pointer to the IQ PID parameter structure to be filled.
  *
  */
void iqPID_getParameters(const iqPID_t* pid, iqPID_PARAM_t* param)
{
    assert(pid != NULL);
    assert(param != NULL);

    param->Kp        = pid->Kp;
    param->Ki        = pid->Ki;
    param->Kd        = pid->Kd;
    param->Kc        = pid->Kc;
    param->maxout    = pid->maxout;
    param->minout    = pid->minout;
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
