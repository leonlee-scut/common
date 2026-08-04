/** @file iq_pid.h
  * @brief IQ PID controller interface for Dynamic Anti-Windup PID.
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

#ifndef __IQ_PID_H__
#define __IQ_PID_H__

#include "cmsis_compiler.h"
#include "IQmathLib.h"

#define iqPID_SET_TARGET(pid, target)       ((pid)->target = (target))
#define iqPID_SET_FEEDBACK(pid, feedback)   ((pid)->feedback = (feedback))
#define iqPID_SET_Kp(pid, Kp)               ((pid)->Kp = (Kp))
#define iqPID_SET_Ki(pid, Ki)               ((pid)->Ki = (Ki))
#define iqPID_SET_Kd(pid, Kd)               ((pid)->Kd = (Kd))
#define iqPID_SET_Kc(pid, Kc)               ((pid)->Kc = (Kc))

#define iqPID_GET_TARGET(pid)               ((pid)->target)
#define iqPID_GET_FEEDBACK(pid)             ((pid)->feedback)
#define iqPID_GET_Kp(pid)                   ((pid)->Kp)
#define iqPID_GET_Ki(pid)                   ((pid)->Ki)
#define iqPID_GET_Kd(pid)                   ((pid)->Kd)
#define iqPID_GET_Kc(pid)                   ((pid)->Kc)

#define iqPI_MARCO(pid)     do { \
                                (pid)->err = (pid)->target - (pid)->feedback; \
                                (pid)->p_term = _IQmpy((pid)->Kp, (pid)->err); \
                                (pid)->i_term += _IQmpy((pid)->Ki, (pid)->p_term) + _IQmpy((pid)->Kc, (pid)->sat_err); \
                                (pid)->pre_sat = (pid)->p_term + (pid)->i_term; \
                                (pid)->output = _IQsat((pid)->pre_sat, (pid)->maxout, (pid)->minout); \
                                (pid)->sat_err = (pid)->output - (pid)->pre_sat; \
                                (pid)->p_term1 = (pid)->p_term; \
                            } while(0)

#define iqPID_MARCO(pid)    do {\
                                (pid)->err = (pid)->target - (pid)->feedback; \
                                (pid)->p_term = _IQmpy((pid)->Kp, (pid)->err); \
                                (pid)->i_term += _IQmpy((pid)->Ki, (pid)->p_term) + _IQmpy((pid)->Kc, (pid)->sat_err); \
                                (pid)->d_term = _IQmpy((pid)->Kd, ((pid)->p_term - (pid)->p_term1)); \
                                (pid)->pre_sat = (pid)->p_term + (pid)->i_term + (pid)->d_term; \
                                (pid)->output = _IQsat((pid)->pre_sat, (pid)->maxout, (pid)->minout); \
                                (pid)->sat_err = (pid)->output - (pid)->pre_sat; \
                                (pid)->p_term1 = (pid)->p_term; \
                            } while(0)
/**
  * @brief Struct of Dynamic Anti-Windup PID controller parameters and state variables.
  */
typedef struct
{
    _iq target;        //!< Input:     Target value (setpoint)
    _iq feedback;      //!< Input:     Measured value
    _iq Kp;            //!< Parameter: Proportional gain
    _iq Ki;            //!< Parameter: Integral gain
    _iq Kd;            //!< Parameter: Derivative gain
    _iq Kc;            //!< Parameter: Anti-windup gain, normally, Kc = 1 / Kp or 1 / sqrt(Kp * Ki)
    _iq maxout;        //!< Parameter: Maximum output limit
    _iq minout;        //!< Parameter: Minimum output limit
    _iq err;           //!< Variable:  Error
    _iq p_term;        //!< Variable:  Proportional output
    _iq i_term;        //!< Variable:  Integral output 
    _iq d_term;        //!< Variable:  Derivative output 
    _iq sat_err;       //!< Variable:  Saturation difference
    _iq pre_sat;       //!< Variable:  Pre-saturation output
    _iq p_term1;       //!< History:   Previous proportional output
    _iq output;        //!< Output:    Output value of the PID controller
} iqPID_t;

typedef iqPID_t *iqPID_Handle_t;

/** 
  * @brief Struct for initializing or getting parameters of the IQ PID controller.
  */
typedef struct
{
    _iq Kp;            //!< Proportional gain
    _iq Ki;            //!< Integral gain
    _iq Kd;            //!< Derivative gain
    _iq Kc;            //!< Anti-windup gain, normally, Kc = 1 / Kp or 1 / sqrt(Kp * Ki)
    _iq maxout;        //!< Maximum output limit
    _iq minout;        //!< Minimum output limit
} iqPID_PARAM_t;

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

void iqPID_init(iqPID_t *pid, const iqPID_PARAM_t *init);
_iq  iqPID_calculate(iqPID_t *pid, _iq measurement);
_iq  iqPI_calculate(iqPID_t *pid, _iq measurement);
void iqPID_reset(iqPID_t *pid);
void iqPID_getParameters(const iqPID_t *pid, iqPID_PARAM_t *param);


/** 
  * @brief Swap two _iq values.
  * @param a Pointer to the first _iq value.
  * @param b Pointer to the second _iq value.
  *
  */
__STATIC_INLINE void _IQswap(_iq *a, _iq *b)
{
    _iq temp = *a;
    *a = *b;
    *b = temp;
}


/** 
  * @brief Set the target value of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param target The target value.
  *
  */
__STATIC_INLINE void iqPID_setTarget(iqPID_t *pid, _iq target)
{
    pid->target = target;
}


/** 
  * @brief Set the feedback value of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param feedback The feedback value.
  *
  */
__STATIC_INLINE void iqPID_setFeedback(iqPID_t *pid, _iq feedback)
{
    pid->feedback = feedback;
}


/** 
  * @brief Set the gains of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param Kp The proportional gain.
  * @param Ki The integral gain.
  * @param Kd The derivative gain.
  * @param Kc The anti-windup gain.
  *
  */
__STATIC_INLINE void iqPID_setGains(iqPID_t *pid, _iq Kp, _iq Ki, _iq Kd, _iq Kc)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->Kc = Kc;
}


/** 
  * @brief Set the output limits of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param minout The minimum output limit.
  * @param maxout The maximum output limit.
  *
  */
__STATIC_INLINE void iqPID_setOutputLimits(iqPID_t *pid, _iq minout, _iq maxout)
{
    pid->maxout = maxout;
    pid->minout = minout;

    if (maxout < minout)
    {
        _IQswap(&pid->maxout, &pid->minout);
    }
}



/** 
  * @brief Set the proportional gain of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param Kp The proportional gain.
  *
  */
__STATIC_INLINE void iqPID_setProportionalGain(iqPID_t *pid, _iq Kp)
{
    pid->Kp = Kp;
}


/** 
  * @brief Set the integral gain of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param Ki The integral gain.
  *
  */
__STATIC_INLINE void iqPID_setIntegralGain(iqPID_t *pid, _iq Ki)
{
    pid->Ki = Ki;
}


/** 
  * @brief Set the derivative gain of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param Kd The derivative gain.
  *
  */
__STATIC_INLINE void iqPID_setDerivativeGain(iqPID_t *pid, _iq Kd)
{
    pid->Kd = Kd;
}


/** 
  * @brief Set the anti-windup gain of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param Kc The anti-windup gain.
  *
  */
__STATIC_INLINE void iqPID_setAntiwindupGain(iqPID_t *pid, _iq Kc)
{
    pid->Kc = Kc;
}


/** 
  * @brief Set the maximum output of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param maxout The maximum output limit.
  *
  */
__STATIC_INLINE void iqPID_setMaxOutput(iqPID_t *pid, _iq maxout)
{
    pid->maxout = maxout;

    if (pid->maxout < pid->minout)
    {
        _IQswap(&pid->maxout, &pid->minout);
    }
}


/** 
  * @brief Set the minimum output of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @param minout The minimum output limit.
  *
  */
__STATIC_INLINE void iqPID_setMinOutput(iqPID_t *pid, _iq minout)
{
    pid->minout = minout;

    if (pid->maxout < pid->minout)
    {
        _IQswap(&pid->maxout, &pid->minout);
    }
}


/**
  * @brief Get the parameters of the IQ PID controller.
  * 
  * @param pid Pointer to the IQ PID controller instance.
  * @param Kp Pointer to store the proportional gain.
  * @param Ki Pointer to store the integral gain.
  * @param Kd Pointer to store the derivative gain.
  * @param Kc Pointer to store the anti-windup gain.
  */
__STATIC_INLINE void iqPID_getGains(const iqPID_t *pid, _iq *Kp, _iq *Ki, _iq *Kd, _iq *Kc)
{
    *Kp = pid->Kp;
    *Ki = pid->Ki;
    *Kd = pid->Kd;
    *Kc = pid->Kc;
}


/** 
  * @brief Get the target value of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @return The target value.
  *
  */
__STATIC_INLINE _iq iqPID_getTarget(const iqPID_t *pid)
{
    return pid->target;
}


/** 
  * @brief Get the proportional gain of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @return The proportional gain.
  *
  */
__STATIC_INLINE _iq iqPID_getProportionalGain(const iqPID_t *pid)
{
    return pid->Kp;
}


/** 
  * @brief Get the integral gain of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @return The integral gain.
  *
  */
__STATIC_INLINE _iq iqPID_getIntegralGain(const iqPID_t *pid)
{
    return pid->Ki;
}


/** 
  * @brief Get the derivative gain of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @return The derivative gain.
  *
  */
__STATIC_INLINE _iq iqPID_getDerivativeGain(const iqPID_t *pid)
{
    return pid->Kd;
}


/** 
  * @brief Get the anti-windup gain of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @return The anti-windup gain.
  *
  */
__STATIC_INLINE _iq iqPID_getAntiwindupGain(const iqPID_t *pid)
{
    return pid->Kc;
}


/** 
  * @brief Get the maximum output of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @return The maximum output limit.
  *
  */
__STATIC_INLINE _iq iqPID_getMaxOutput(const iqPID_t *pid)
{
    return pid->maxout;
}


/** 
  * @brief Get the minimum output of the IQ PID controller.
  * @param pid Pointer to the IQ PID controller instance.
  * @return The minimum output limit.
  *
  */
__STATIC_INLINE _iq iqPID_getMinOutput(const iqPID_t *pid)
{
    return pid->minout;
}


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __IQ_PID_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
