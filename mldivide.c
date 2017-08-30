/*
 * File: mldivide.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

/* Include files */
#include "rt_nonfinite.h"
#include "MSA.h"
#include "mldivide.h"
#include "MSA_emxutil.h"
#include "colon.h"
#include "cart2sph.h"
#include "MSA_rtwutil.h"

/* Function Declarations */
static double eml_matlab_zlarfg(int n, double *alpha1, emxArray_real_T *x, int
  ix0);
static void eml_qrsolve(const emxArray_real_T *A, emxArray_real_T *B,
  emxArray_real_T *Y);
static double eml_xnrm2(int n, const emxArray_real_T *x, int ix0);
static void eml_xscal(int n, double a, emxArray_real_T *x, int ix0);

/* Function Definitions */

/*
 * Arguments    : int n
 *                double *alpha1
 *                emxArray_real_T *x
 *                int ix0
 * Return Type  : double
 */
static double eml_matlab_zlarfg(int n, double *alpha1, emxArray_real_T *x, int
  ix0)
{
  double tau;
  double xnorm;
  int knt;
  double d2;
  int k;
  tau = 0.0;
  if (n <= 0) {
  } else {
    xnorm = eml_xnrm2(n - 1, x, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        do {
          knt++;
          eml_xscal(n - 1, 9.9792015476736E+291, x, ix0);
          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

        xnorm = eml_xnrm2(n - 1, x, ix0);
        xnorm = rt_hypotd_snf(*alpha1, xnorm);
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        d2 = 1.0 / (*alpha1 - xnorm);
        eml_xscal(n - 1, d2, x, ix0);
        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        d2 = 1.0 / (*alpha1 - xnorm);
        eml_xscal(n - 1, d2, x, ix0);
        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

/*
 * Arguments    : const emxArray_real_T *A
 *                emxArray_real_T *B
 *                emxArray_real_T *Y
 * Return Type  : void
 */
static void eml_qrsolve(const emxArray_real_T *A, emxArray_real_T *B,
  emxArray_real_T *Y)
{
  int mn;
  emxArray_real_T *b_A;
  int i3;
  int k;
  int b_mn;
  emxArray_real_T *tau;
  emxArray_int32_T *jpvt;
  emxArray_real_T *work;
  emxArray_real_T *vn1;
  emxArray_real_T *vn2;
  int nmi;
  int i;
  int i_i;
  int mmi;
  int pvt;
  int ix;
  double smax;
  double s;
  int iy;
  int i_ip1;
  int lastv;
  int lastc;
  boolean_T exitg2;
  int32_T exitg1;
  double absxk;
  double t;
  unsigned int unnamed_idx_0;
  if (A->size[0] <= A->size[1]) {
    mn = A->size[0];
  } else {
    mn = A->size[1];
  }

  b_emxInit_real_T(&b_A, 2);
  i3 = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity((emxArray__common *)b_A, i3, (int)sizeof(double));
  k = A->size[0] * A->size[1];
  for (i3 = 0; i3 < k; i3++) {
    b_A->data[i3] = A->data[i3];
  }

  if (A->size[0] <= A->size[1]) {
    b_mn = A->size[0];
  } else {
    b_mn = A->size[1];
  }

  c_emxInit_real_T(&tau, 1);
  emxInit_int32_T(&jpvt, 2);
  i3 = tau->size[0];
  tau->size[0] = b_mn;
  emxEnsureCapacity((emxArray__common *)tau, i3, (int)sizeof(double));
  eml_signed_integer_colon(A->size[1], jpvt);
  if ((A->size[0] == 0) || (A->size[1] == 0)) {
  } else {
    c_emxInit_real_T(&work, 1);
    k = A->size[1];
    i3 = work->size[0];
    work->size[0] = k;
    emxEnsureCapacity((emxArray__common *)work, i3, (int)sizeof(double));
    for (i3 = 0; i3 < k; i3++) {
      work->data[i3] = 0.0;
    }

    c_emxInit_real_T(&vn1, 1);
    c_emxInit_real_T(&vn2, 1);
    k = A->size[1];
    i3 = vn1->size[0];
    vn1->size[0] = k;
    emxEnsureCapacity((emxArray__common *)vn1, i3, (int)sizeof(double));
    i3 = vn2->size[0];
    vn2->size[0] = k;
    emxEnsureCapacity((emxArray__common *)vn2, i3, (int)sizeof(double));
    k = 1;
    for (nmi = 0; nmi + 1 <= A->size[1]; nmi++) {
      vn1->data[nmi] = eml_xnrm2(A->size[0], A, k);
      vn2->data[nmi] = vn1->data[nmi];
      k += A->size[0];
    }

    for (i = 0; i + 1 <= b_mn; i++) {
      i_i = i + i * A->size[0];
      nmi = A->size[1] - i;
      mmi = (A->size[0] - i) - 1;
      if (nmi < 1) {
        pvt = -1;
      } else {
        pvt = 0;
        if (nmi > 1) {
          ix = i;
          smax = fabs(vn1->data[i]);
          for (k = 0; k + 2 <= nmi; k++) {
            ix++;
            s = fabs(vn1->data[ix]);
            if (s > smax) {
              pvt = k + 1;
              smax = s;
            }
          }
        }
      }

      pvt += i;
      if (pvt + 1 != i + 1) {
        ix = A->size[0] * pvt;
        iy = A->size[0] * i;
        for (k = 1; k <= A->size[0]; k++) {
          smax = b_A->data[ix];
          b_A->data[ix] = b_A->data[iy];
          b_A->data[iy] = smax;
          ix++;
          iy++;
        }

        k = jpvt->data[pvt];
        jpvt->data[pvt] = jpvt->data[i];
        jpvt->data[i] = k;
        vn1->data[pvt] = vn1->data[i];
        vn2->data[pvt] = vn2->data[i];
      }

      if (i + 1 < A->size[0]) {
        s = b_A->data[i_i];
        tau->data[i] = eml_matlab_zlarfg(mmi + 1, &s, b_A, i_i + 2);
      } else {
        smax = b_A->data[i_i];
        s = b_A->data[i_i];
        b_A->data[i_i] = smax;
        tau->data[i] = 0.0;
      }

      b_A->data[i_i] = s;
      if (i + 1 < A->size[1]) {
        s = b_A->data[i_i];
        b_A->data[i_i] = 1.0;
        i_ip1 = (i + (i + 1) * A->size[0]) + 1;
        if (tau->data[i] != 0.0) {
          lastv = mmi;
          pvt = i_i + mmi;
          while ((lastv + 1 > 0) && (b_A->data[pvt] == 0.0)) {
            lastv--;
            pvt--;
          }

          lastc = nmi - 1;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            k = i_ip1 + (lastc - 1) * A->size[0];
            nmi = k;
            do {
              exitg1 = 0;
              if (nmi <= k + lastv) {
                if (b_A->data[nmi - 1] != 0.0) {
                  exitg1 = 1;
                } else {
                  nmi++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = -1;
          lastc = 0;
        }

        if (lastv + 1 > 0) {
          if (lastc == 0) {
          } else {
            for (iy = 1; iy <= lastc; iy++) {
              work->data[iy - 1] = 0.0;
            }

            iy = 0;
            i3 = i_ip1 + A->size[0] * (lastc - 1);
            for (pvt = i_ip1; pvt <= i3; pvt += A->size[0]) {
              ix = i_i;
              smax = 0.0;
              k = pvt + lastv;
              for (nmi = pvt; nmi <= k; nmi++) {
                smax += b_A->data[nmi - 1] * b_A->data[ix];
                ix++;
              }

              work->data[iy] += smax;
              iy++;
            }
          }

          if (-tau->data[i] == 0.0) {
          } else {
            pvt = 0;
            for (nmi = 1; nmi <= lastc; nmi++) {
              if (work->data[pvt] != 0.0) {
                smax = work->data[pvt] * -tau->data[i];
                ix = i_i;
                i3 = lastv + i_ip1;
                for (k = i_ip1; k <= i3; k++) {
                  b_A->data[k - 1] += b_A->data[ix] * smax;
                  ix++;
                }
              }

              pvt++;
              i_ip1 += A->size[0];
            }
          }
        }

        b_A->data[i_i] = s;
      }

      for (nmi = i + 1; nmi + 1 <= A->size[1]; nmi++) {
        k = (i + A->size[0] * nmi) + 1;
        if (vn1->data[nmi] != 0.0) {
          smax = fabs(b_A->data[i + b_A->size[0] * nmi]) / vn1->data[nmi];
          smax = 1.0 - smax * smax;
          if (smax < 0.0) {
            smax = 0.0;
          }

          s = vn1->data[nmi] / vn2->data[nmi];
          s = smax * (s * s);
          if (s <= 1.4901161193847656E-8) {
            if (i + 1 < A->size[0]) {
              smax = 0.0;
              if (mmi < 1) {
              } else if (mmi == 1) {
                smax = fabs(b_A->data[k]);
              } else {
                s = 2.2250738585072014E-308;
                pvt = k + mmi;
                while (k + 1 <= pvt) {
                  absxk = fabs(b_A->data[k]);
                  if (absxk > s) {
                    t = s / absxk;
                    smax = 1.0 + smax * t * t;
                    s = absxk;
                  } else {
                    t = absxk / s;
                    smax += t * t;
                  }

                  k++;
                }

                smax = s * sqrt(smax);
              }

              vn1->data[nmi] = smax;
              vn2->data[nmi] = vn1->data[nmi];
            } else {
              vn1->data[nmi] = 0.0;
              vn2->data[nmi] = 0.0;
            }
          } else {
            vn1->data[nmi] *= sqrt(smax);
          }
        }
      }
    }

    emxFree_real_T(&vn2);
    emxFree_real_T(&vn1);
    emxFree_real_T(&work);
  }

  s = 0.0;
  if (mn > 0) {
    if (A->size[0] >= A->size[1]) {
      k = A->size[0];
    } else {
      k = A->size[1];
    }

    smax = (double)k * fabs(b_A->data[0]) * 2.2204460492503131E-16;
    k = 0;
    while ((k <= mn - 1) && (!(fabs(b_A->data[k + b_A->size[0] * k]) <= smax)))
    {
      s++;
      k++;
    }
  }

  unnamed_idx_0 = (unsigned int)A->size[1];
  i3 = Y->size[0];
  Y->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)Y, i3, (int)sizeof(double));
  k = (int)unnamed_idx_0;
  for (i3 = 0; i3 < k; i3++) {
    Y->data[i3] = 0.0;
  }

  for (nmi = 0; nmi < mn; nmi++) {
    if (tau->data[nmi] != 0.0) {
      smax = B->data[nmi];
      i3 = A->size[0] + (int)(1.0 - ((1.0 + (double)nmi) + 1.0));
      for (i = 0; i < i3; i++) {
        unnamed_idx_0 = ((unsigned int)nmi + i) + 2U;
        smax += b_A->data[((int)unnamed_idx_0 + b_A->size[0] * nmi) - 1] *
          B->data[(int)unnamed_idx_0 - 1];
      }

      smax *= tau->data[nmi];
      if (smax != 0.0) {
        B->data[nmi] -= smax;
        i3 = A->size[0] + (int)(1.0 - ((1.0 + (double)nmi) + 1.0));
        for (i = 0; i < i3; i++) {
          unnamed_idx_0 = ((unsigned int)nmi + i) + 2U;
          B->data[(int)unnamed_idx_0 - 1] -= b_A->data[((int)unnamed_idx_0 +
            b_A->size[0] * nmi) - 1] * smax;
        }
      }
    }
  }

  emxFree_real_T(&tau);
  for (i = 0; i < (int)s; i++) {
    Y->data[jpvt->data[i] - 1] = B->data[i];
  }

  for (nmi = 0; nmi < (int)-(1.0 + (-1.0 - s)); nmi++) {
    smax = s + -(double)nmi;
    Y->data[jpvt->data[(int)smax - 1] - 1] /= b_A->data[((int)smax + b_A->size[0]
      * ((int)smax - 1)) - 1];
    for (i = 0; i <= (int)smax - 2; i++) {
      Y->data[jpvt->data[i] - 1] -= Y->data[jpvt->data[(int)smax - 1] - 1] *
        b_A->data[i + b_A->size[0] * ((int)smax - 1)];
    }
  }

  emxFree_int32_T(&jpvt);
  emxFree_real_T(&b_A);
}

/*
 * Arguments    : int n
 *                const emxArray_real_T *x
 *                int ix0
 * Return Type  : double
 */
static double eml_xnrm2(int n, const emxArray_real_T *x, int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x->data[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x->data[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * Arguments    : int n
 *                double a
 *                emxArray_real_T *x
 *                int ix0
 * Return Type  : void
 */
static void eml_xscal(int n, double a, emxArray_real_T *x, int ix0)
{
  int i6;
  int k;
  i6 = (ix0 + n) - 1;
  for (k = ix0; k <= i6; k++) {
    x->data[k - 1] *= a;
  }
}

/*
 * Arguments    : const emxArray_real_T *A
 *                emxArray_real_T *B
 * Return Type  : void
 */
void mldivide(const emxArray_real_T *A, emxArray_real_T *B)
{
  emxArray_real_T *b_A;
  emxArray_int32_T *ipiv;
  emxArray_real_T *b_B;
  emxArray_real_T *r2;
  unsigned int unnamed_idx_0;
  int i4;
  int kAcol;
  int j;
  int mmj;
  int c;
  int ix;
  double temp;
  int jy;
  double s;
  int i5;
  int jA;
  int b_j;
  int ijA;
  b_emxInit_real_T(&b_A, 2);
  emxInit_int32_T(&ipiv, 2);
  c_emxInit_real_T(&b_B, 1);
  c_emxInit_real_T(&r2, 1);
  if ((A->size[0] == 0) || (A->size[1] == 0) || (B->size[0] == 0)) {
    unnamed_idx_0 = (unsigned int)A->size[1];
    i4 = B->size[0];
    B->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)B, i4, (int)sizeof(double));
    kAcol = (int)unnamed_idx_0;
    for (i4 = 0; i4 < kAcol; i4++) {
      B->data[i4] = 0.0;
    }
  } else if (A->size[0] == A->size[1]) {
    i4 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, i4, (int)sizeof(double));
    kAcol = A->size[0] * A->size[1];
    for (i4 = 0; i4 < kAcol; i4++) {
      b_A->data[i4] = A->data[i4];
    }

    kAcol = A->size[1];
    eml_signed_integer_colon(kAcol, ipiv);
    if (A->size[1] - 1 <= A->size[1]) {
      i4 = A->size[1] - 1;
    } else {
      i4 = A->size[1];
    }

    for (j = 0; j + 1 <= i4; j++) {
      mmj = A->size[1] - j;
      c = j * (A->size[1] + 1);
      if (mmj < 1) {
        kAcol = -1;
      } else {
        kAcol = 0;
        if (mmj > 1) {
          ix = c;
          temp = fabs(b_A->data[c]);
          for (jy = 1; jy + 1 <= mmj; jy++) {
            ix++;
            s = fabs(b_A->data[ix]);
            if (s > temp) {
              kAcol = jy;
              temp = s;
            }
          }
        }
      }

      if (b_A->data[c + kAcol] != 0.0) {
        if (kAcol != 0) {
          ipiv->data[j] = (j + kAcol) + 1;
          ix = j;
          kAcol += j;
          for (jy = 1; jy <= A->size[1]; jy++) {
            temp = b_A->data[ix];
            b_A->data[ix] = b_A->data[kAcol];
            b_A->data[kAcol] = temp;
            ix += A->size[1];
            kAcol += A->size[1];
          }
        }

        i5 = c + mmj;
        for (jA = c + 1; jA + 1 <= i5; jA++) {
          b_A->data[jA] /= b_A->data[c];
        }
      }

      kAcol = (A->size[1] - j) - 1;
      jA = c + A->size[1];
      jy = c + A->size[1];
      for (b_j = 1; b_j <= kAcol; b_j++) {
        temp = b_A->data[jy];
        if (b_A->data[jy] != 0.0) {
          ix = c + 1;
          i5 = mmj + jA;
          for (ijA = 1 + jA; ijA + 1 <= i5; ijA++) {
            b_A->data[ijA] += b_A->data[ix] * -temp;
            ix++;
          }
        }

        jy += A->size[1];
        jA += A->size[1];
      }
    }

    for (kAcol = 0; kAcol + 1 < A->size[1]; kAcol++) {
      if (ipiv->data[kAcol] != kAcol + 1) {
        temp = B->data[kAcol];
        B->data[kAcol] = B->data[ipiv->data[kAcol] - 1];
        B->data[ipiv->data[kAcol] - 1] = temp;
      }
    }

    for (jy = 0; jy + 1 <= A->size[1]; jy++) {
      kAcol = A->size[1] * jy;
      if (B->data[jy] != 0.0) {
        for (jA = jy + 1; jA + 1 <= A->size[1]; jA++) {
          B->data[jA] -= B->data[jy] * b_A->data[jA + kAcol];
        }
      }
    }

    for (jy = A->size[1] - 1; jy + 1 > 0; jy--) {
      kAcol = A->size[1] * jy;
      if (B->data[jy] != 0.0) {
        temp = b_A->data[jy + kAcol];
        B->data[jy] /= temp;
        for (jA = 0; jA + 1 <= jy; jA++) {
          B->data[jA] -= B->data[jy] * b_A->data[jA + kAcol];
        }
      }
    }
  } else {
    i4 = b_B->size[0];
    b_B->size[0] = B->size[0];
    emxEnsureCapacity((emxArray__common *)b_B, i4, (int)sizeof(double));
    kAcol = B->size[0];
    for (i4 = 0; i4 < kAcol; i4++) {
      b_B->data[i4] = B->data[i4];
    }

    eml_qrsolve(A, b_B, r2);
    i4 = B->size[0];
    B->size[0] = r2->size[0];
    emxEnsureCapacity((emxArray__common *)B, i4, (int)sizeof(double));
    kAcol = r2->size[0];
    for (i4 = 0; i4 < kAcol; i4++) {
      B->data[i4] = r2->data[i4];
    }
  }

  emxFree_real_T(&r2);
  emxFree_real_T(&b_B);
  emxFree_int32_T(&ipiv);
  emxFree_real_T(&b_A);
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */
