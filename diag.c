/*
 * File: diag.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

/* Include files */
#include "rt_nonfinite.h"
#include "MSA.h"
#include "diag.h"

/* Function Definitions */

/*
 * Arguments    : const double v[3]
 *                double d[9]
 * Return Type  : void
 */
void diag(const double v[3], double d[9])
{
  int j;
  memset(&d[0], 0, 9U * sizeof(double));
  for (j = 0; j < 3; j++) {
    d[j + 3 * j] = v[j];
  }
}

/*
 * File trailer for diag.c
 *
 * [EOF]
 */
