/*
 * File: cart2sph.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

/* Include files */
#include "rt_nonfinite.h"
#include "MSA.h"
#include "cart2sph.h"
#include "MSA_rtwutil.h"

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(double)(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * Arguments    : double x
 *                double y
 *                double z
 *                double *az
 *                double *elev
 *                double *r
 * Return Type  : void
 */
void cart2sph(double x, double y, double z, double *az, double *elev, double *r)
{
  double hypotxy;
  hypotxy = rt_hypotd_snf(x, y);
  *r = rt_hypotd_snf(hypotxy, z);
  *elev = rt_atan2d_snf(z, hypotxy);
  *az = rt_atan2d_snf(y, x);
}

/*
 * File trailer for cart2sph.c
 *
 * [EOF]
 */
