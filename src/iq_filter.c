/**
  * @file iq_filter.c
  * @brief Implementation of IQ filter functions.
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2026/07/03
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
  * 	2026/07/03	0.1			Leon Lee		Preliminary version.
  */

#include "iq_filter.h"


/**
  * @brief Initialize the IQ IIR filter.
  * 
  * @param filter Pointer to the IQ IIR filter instance.
  * @param alpha The filter coefficient, should be in the range [0, 1].
  *
  */
void iqIIR_init(iqIIR_t* filter, _iq alpha)
{
    alpha = _IQsat(alpha, _IQ(1.0), _IQ(0.0)); // Ensure alpha is in [0, 1]

    filter->alpha = alpha;
    filter->filtered_value = 0;
}


/**
  * @brief Apply IIR filtering to the input value.
  *
  * @param filter Pointer to the IQ IIR filter instance.
  * @param input The input value to be filtered.
  * @return The filtered output value.
  *
  * @note This function applies an First-order Lag Filter (IIR filter) to the 
  *       input value and returns the filtered output.
  *      
  *       The IIR filter is defined by the following difference equation:
  *
  *             y[n] = alpha * (x[n] - y[n-1]) + y[n-1]
  *
  *       where y[n] is the filtered output at time n,
  *             y[n-1] is the previous filtered output,
  *             x[n] is the input at time n,
  *             alpha is the filter coefficient, and is in the range [0, 1]. 
  *       
  *       The filter coefficient @c alpha controls the filter's response to the input. 
  *       When alpha is close to 0, the filter has a slower response and more 
  *       smoothing effect. 
  *       When alpha is close to 1, the filter has a faster response and less
  *       smoothing effect.
  *
  *       If target cut-off frequency is desired, the filter coefficient can be
  *       calculated as:
  *
  *             alpha = 1 - exp(-2 * pi * fc / fs)
  *
  *       where fc is the cut-off frequency and fs is the sampling frequency.
  *
  *       If applying the filter to simulate a RC low-pass filter, the filter 
  *       coefficient can be calculated as:
  *
  *             alpha = Ts / (RC + Ts)
  *
  *       where Ts is the sampling period and RC is the RC time constant.
  *
  *       The filter cut-off frequency can be calculated by the coefficient as:
  *
  *            fc = -fs / (2 * pi) * ln(1 - alpha)
  *
  */
_iq iqIIR_filter(iqIIR_t* filter, _iq input)
{
    _iq output = input - filter->filtered_value;
    output = _IQmpy(output, filter->alpha);
    output += filter->filtered_value;

    filter->filtered_value = output; 

    return output;
}


/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
