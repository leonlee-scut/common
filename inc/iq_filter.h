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

#include "IQmathLib.h"

/**
  * @brief IIR filter structure for IQ math.
  * 
  */
typedef struct
{
    _iq coeff;            //!< filter coefficient
    _iq filtered_value;   //!< filtered value
} iqIIR_FILTER_t;

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

void iqIIR_init(iqIIR_FILTER_t *filter, _iq coeff);
void iqIIR_reset(iqIIR_FILTER_t *filter);
void iqIIR_setCoefficient(iqIIR_FILTER_t *filter, _iq coeff);
_iq iqIIR_getCoefficient(const iqIIR_FILTER_t *filter);
_iq iqIIR_getFilteredValue(const iqIIR_FILTER_t *filter);
_iq iqIIR_filter(iqIIR_FILTER_t *filter, _iq input);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __IQ_FILTER_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
