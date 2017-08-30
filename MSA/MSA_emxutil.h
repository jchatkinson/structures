/*
 * File: MSA_emxutil.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

#ifndef __MSA_EMXUTIL_H__
#define __MSA_EMXUTIL_H__

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

  extern void b_emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
  extern void b_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
  extern void c_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
  extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
    elementSize);
  extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
  extern void emxFree_real_T(emxArray_real_T **pEmxArray);
  extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
  extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for MSA_emxutil.h
 *
 * [EOF]
 */
