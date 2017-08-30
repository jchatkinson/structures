/*
 * File: cart2sph.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

#ifndef __CART2SPH_H__
#define __CART2SPH_H__

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

  extern void cart2sph(double x, double y, double z, double *az, double *elev,
                       double *r);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for cart2sph.h
 *
 * [EOF]
 */
