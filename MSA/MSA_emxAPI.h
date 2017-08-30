/*
 * File: MSA_emxAPI.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

#ifndef __MSA_EMXAPI_H__
#define __MSA_EMXAPI_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "MSA_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern emxArray_int32_T *emxCreateND_int32_T(int numDimensions, int *size);
  extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
  extern emxArray_int32_T *emxCreateWrapperND_int32_T(int *data, int
    numDimensions, int *size);
  extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
    numDimensions, int *size);
  extern emxArray_int32_T *emxCreateWrapper_int32_T(int *data, int rows, int
    cols);
  extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int
    cols);
  extern emxArray_int32_T *emxCreate_int32_T(int rows, int cols);
  extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
  extern void emxDestroyArray_int32_T(emxArray_int32_T *emxArray);
  extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for MSA_emxAPI.h
 *
 * [EOF]
 */
