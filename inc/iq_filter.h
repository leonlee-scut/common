/**
  * @file iq_filter.h
  * @brief IQ filter interface for digital signal processing.
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

#ifndef __IQ_FILTER_H__
#define __IQ_FILTER_H__

#include "cmsis_compiler.h"
#include "IQmathLib.h"

/**
  * @brief IIR filter structure for IQ math.
  * 
  */
typedef struct
{
    _iq alpha;            //!< filter coefficient
    _iq filtered_value;   //!< filtered value
} iqIIR_t;

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

void iqIIR_init(iqIIR_t *filter, _iq alpha);
_iq iqIIR_filter(iqIIR_t *filter, _iq input);

/**
  * @brief Reset the IQ IIR filter.
  * 
  * @param filter Pointer to the IQ IIR filter instance.
  *
  */
__STATIC_INLINE void iqIIR_reset(iqIIR_t* filter)
{
    filter->filtered_value = 0;
}


/**
  * @brief Set the filter coefficient of the IQ IIR filter.
  * 
  * @param filter Pointer to the IQ IIR filter instance.
  * @param alpha The filter coefficient, should be in the range [0.0, 1.0].
  *
  */
__STATIC_INLINE void iqIIR_setCoefficient(iqIIR_t* filter, _iq alpha)
{
    alpha = _IQsat(alpha, _IQ(1.0), _IQ(0.0)); // Ensure alpha is in [0.0, 1.0]
    filter->alpha = alpha;
}


/**
  * @brief Get the filter coefficient of the IQ IIR filter.
  * 
  * @param filter Pointer to the IQ IIR filter instance.
  * @return The filter coefficient.
  *
  */
__STATIC_INLINE _iq iqIIR_getCoefficient(const iqIIR_t* filter)
{
    return filter->alpha;
}


/**
  * @brief Get the filtered value of the IQ IIR filter.
  * 
  * @param filter Pointer to the IQ IIR filter instance.
  * @return The filtered value.
  *
  */
__STATIC_INLINE _iq iqIIR_getFilteredValue(const iqIIR_t* filter)
{
    return filter->filtered_value;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __IQ_FILTER_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
