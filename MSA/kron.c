/*
 * File: kron.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

/* Include files */
#include "rt_nonfinite.h"
#include "MSA.h"
#include "kron.h"

/* Function Definitions */

/*
 * Arguments    : const double A[16]
 *                const double B[9]
 *                double K[144]
 * Return Type  : void
 */
void kron(const double A[16], const double B[9], double K[144])
{
  int kidx;
  int b_j1;
  int j2;
  int i1;
  int i2;
  kidx = -1;
  for (b_j1 = 0; b_j1 < 4; b_j1++) {
    for (j2 = 0; j2 < 3; j2++) {
      for (i1 = 0; i1 < 4; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          kidx++;
          K[kidx] = A[i1 + (b_j1 << 2)] * B[i2 + 3 * j2];
        }
      }
    }
  }
}

/*
 * File trailer for kron.c
 *
 * [EOF]
 */
