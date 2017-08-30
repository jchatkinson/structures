/*
 * File: MSA.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

/* Include files */
#include "rt_nonfinite.h"
#include "MSA.h"
#include "MSA_emxutil.h"
#include "diag.h"
#include "kron.h"
#include "cart2sph.h"
#include "mldivide.h"

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = rtNaN;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * Arguments    : int m
 *                int n
 *                const emxArray_int32_T *DCon
 *                const emxArray_real_T *DCoord
 *                const emxArray_real_T *Dbe
 *                const emxArray_real_T *DA
 *                const emxArray_real_T *DIy
 *                const emxArray_real_T *DIz
 *                const emxArray_real_T *DG
 *                const emxArray_real_T *DJ
 *                const emxArray_real_T *DE
 *                const emxArray_real_T *Dw
 *                const emxArray_real_T *DSt
 *                const emxArray_real_T *DRe
 *                const emxArray_real_T *DLoad
 *                emxArray_real_T *Q
 *                emxArray_real_T *V
 *                emxArray_real_T *R
 * Return Type  : void
 */
void MSA(int m, int n, const emxArray_int32_T *DCon, const emxArray_real_T
         *DCoord, const emxArray_real_T *Dbe, const emxArray_real_T *DA, const
         emxArray_real_T *DIy, const emxArray_real_T *DIz, const emxArray_real_T
         *DG, const emxArray_real_T *DJ, const emxArray_real_T *DE, const
         emxArray_real_T *Dw, const emxArray_real_T *DSt, const emxArray_real_T *
         DRe, const emxArray_real_T *DLoad, emxArray_real_T *Q, emxArray_real_T *
         V, emxArray_real_T *R)
{
  emxArray_real_T *Ni;
  int i0;
  int loop_ub;
  emxArray_real_T *S;
  long long i1;
  int i2;
  emxArray_real_T *Pf;
  emxArray_real_T *Qfi;
  emxArray_real_T *Ei;
  int i;
  emxArray_int32_T *e;
  emxArray_real_T *w;
  emxArray_real_T *Qf;
  emxArray_real_T *f;
  emxArray_int32_T *r0;
  emxArray_int32_T *y;
  emxArray_int32_T *b_y;
  emxArray_int32_T *ii;
  emxArray_real_T *r1;
  emxArray_int32_T *b_e;
  emxArray_int32_T *c_e;
  emxArray_int32_T *d_e;
  emxArray_real_T *b_S;
  emxArray_real_T *b_Pf;
  emxArray_real_T *e_e;
  int nx;
  double C[3];
  int idx;
  unsigned int span;
  double L;
  double sb;
  double sa;
  double ca;
  double cb;
  double cc;
  double sc;
  double K3[9];
  double K4[9];
  double b_cb[9];
  static const signed char v[3] = { 1, 0, 0 };

  static const signed char iv0[3] = { 0, 0, 1 };

  double b_v[9];
  double b_ca[9];
  static const signed char iv1[3] = { 0, 1, 0 };

  double T[144];
  static const double dv0[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  double dv1[4];
  double co[4];
  double c_y[4];
  double b_DA[3];
  double K1[9];
  double K2[9];
  double b_K1[144];
  double g[3];
  double b_g[3];
  double K[144];
  double M[144];
  double Qfs[12];
  boolean_T guard2 = false;
  int ia;
  int ic;
  static const double dv2[3] = { 0.0, -0.5, -0.5 };

  static const signed char iv2[3] = { 1, 0, 0 };

  static const signed char iv3[6] = { 3, 4, 5, 9, 10, 11 };

  double b_M[144];
  double c_S[144];
  double d_y[12];
  double b_V[12];
  double c_Pf[12];
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_int32_T *b_ii;
  emxArray_real_T *d_S;
  boolean_T b_guard1 = false;
  emxInit_real_T(&Ni, 3);
  i0 = Ni->size[0] * Ni->size[1] * Ni->size[2];
  Ni->size[0] = 12;
  Ni->size[1] = 12;
  Ni->size[2] = m;
  emxEnsureCapacity((emxArray__common *)Ni, i0, (int)sizeof(double));
  loop_ub = 144 * m;
  for (i0 = 0; i0 < loop_ub; i0++) {
    Ni->data[i0] = 0.0;
  }

  b_emxInit_real_T(&S, 2);
  i1 = 6LL * n;
  if (i1 > 2147483647LL) {
    i1 = 2147483647LL;
  } else {
    if (i1 < -2147483648LL) {
      i1 = -2147483648LL;
    }
  }

  i0 = (int)i1;
  i2 = S->size[0] * S->size[1];
  S->size[0] = i0;
  S->size[1] = i0;
  emxEnsureCapacity((emxArray__common *)S, i2, (int)sizeof(double));
  loop_ub = i0 * i0;
  for (i0 = 0; i0 < loop_ub; i0++) {
    S->data[i0] = 0.0;
  }

  c_emxInit_real_T(&Pf, 1);
  i1 = 6LL * n;
  if (i1 > 2147483647LL) {
    i1 = 2147483647LL;
  } else {
    if (i1 < -2147483648LL) {
      i1 = -2147483648LL;
    }
  }

  loop_ub = (int)i1;
  i0 = Pf->size[0];
  i1 = 6LL * n;
  if (i1 > 2147483647LL) {
    i1 = 2147483647LL;
  } else {
    if (i1 < -2147483648LL) {
      i1 = -2147483648LL;
    }
  }

  Pf->size[0] = (int)i1;
  emxEnsureCapacity((emxArray__common *)Pf, i0, (int)sizeof(double));
  for (i0 = 0; i0 < loop_ub; i0++) {
    Pf->data[i0] = 0.0;
  }

  i0 = Q->size[0] * Q->size[1];
  Q->size[0] = 12;
  Q->size[1] = m;
  emxEnsureCapacity((emxArray__common *)Q, i0, (int)sizeof(double));
  loop_ub = 12 * m;
  for (i0 = 0; i0 < loop_ub; i0++) {
    Q->data[i0] = 0.0;
  }

  b_emxInit_real_T(&Qfi, 2);
  i0 = Qfi->size[0] * Qfi->size[1];
  Qfi->size[0] = 12;
  Qfi->size[1] = m;
  emxEnsureCapacity((emxArray__common *)Qfi, i0, (int)sizeof(double));
  loop_ub = 12 * m;
  for (i0 = 0; i0 < loop_ub; i0++) {
    Qfi->data[i0] = 0.0;
  }

  b_emxInit_real_T(&Ei, 2);
  i0 = Ei->size[0] * Ei->size[1];
  Ei->size[0] = 12;
  Ei->size[1] = m;
  emxEnsureCapacity((emxArray__common *)Ei, i0, (int)sizeof(double));
  loop_ub = 12 * m;
  for (i0 = 0; i0 < loop_ub; i0++) {
    Ei->data[i0] = 0.0;
  }

  i = 0;
  emxInit_int32_T(&e, 2);
  b_emxInit_real_T(&w, 2);
  c_emxInit_real_T(&Qf, 1);
  c_emxInit_real_T(&f, 1);
  b_emxInit_int32_T(&r0, 1);
  emxInit_int32_T(&y, 2);
  emxInit_int32_T(&b_y, 2);
  b_emxInit_int32_T(&ii, 1);
  c_emxInit_real_T(&r1, 1);
  b_emxInit_int32_T(&b_e, 1);
  b_emxInit_int32_T(&c_e, 1);
  b_emxInit_int32_T(&d_e, 1);
  b_emxInit_real_T(&b_S, 2);
  c_emxInit_real_T(&b_Pf, 1);
  b_emxInit_real_T(&e_e, 2);
  while (i + 1 <= m) {
    loop_ub = DCon->data[1 + DCon->size[0] * i];
    nx = DCon->data[DCon->size[0] * i];
    for (i0 = 0; i0 < 3; i0++) {
      C[i0] = DCoord->data[i0 + DCoord->size[0] * (loop_ub - 1)] - DCoord->
        data[i0 + DCoord->size[0] * (nx - 1)];
    }

    i1 = 6LL * DCon->data[DCon->size[0] * i];
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    nx = (int)i1;
    i1 = 6LL * DCon->data[DCon->size[0] * i];
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    i1 = (int)i1 - 5LL;
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    idx = (int)i1;
    if (nx < idx) {
      nx = 0;
    } else {
      if ((idx < 0) && (nx >= 0)) {
        span = ((unsigned int)nx + -(idx + 1)) + 1U;
      } else {
        span = (unsigned int)(nx - idx);
      }

      nx = (int)span + 1;
    }

    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = nx;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(int));
    if (nx > 0) {
      y->data[0] = idx;
      for (loop_ub = 2; loop_ub <= nx; loop_ub++) {
        idx++;
        y->data[loop_ub - 1] = idx;
      }
    }

    i1 = 6LL * DCon->data[1 + DCon->size[0] * i];
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    nx = (int)i1;
    i1 = 6LL * DCon->data[1 + DCon->size[0] * i];
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    i1 = (int)i1 - 5LL;
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    idx = (int)i1;
    if (nx < idx) {
      nx = 0;
    } else {
      if ((idx < 0) && (nx >= 0)) {
        span = ((unsigned int)nx + -(idx + 1)) + 1U;
      } else {
        span = (unsigned int)(nx - idx);
      }

      nx = (int)span + 1;
    }

    i0 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = nx;
    emxEnsureCapacity((emxArray__common *)b_y, i0, (int)sizeof(int));
    if (nx > 0) {
      b_y->data[0] = idx;
      for (loop_ub = 2; loop_ub <= nx; loop_ub++) {
        idx++;
        b_y->data[loop_ub - 1] = idx;
      }
    }

    i0 = e->size[0] * e->size[1];
    e->size[0] = 1;
    e->size[1] = y->size[1] + b_y->size[1];
    emxEnsureCapacity((emxArray__common *)e, i0, (int)sizeof(int));
    loop_ub = y->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      e->data[e->size[0] * i0] = y->data[y->size[0] * i0];
    }

    loop_ub = b_y->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      e->data[e->size[0] * (i0 + y->size[1])] = b_y->data[b_y->size[0] * i0];
    }

    cart2sph(C[0], C[2], C[1], &sa, &sb, &L);
    ca = cos(sa);
    sa = sin(sa);
    cb = cos(sb);
    sb = sin(sb);
    cc = cos(Dbe->data[i]);
    sc = sin(Dbe->data[i]);
    for (i0 = 0; i0 < 3; i0++) {
      K4[3 * i0] = v[i0];
    }

    K4[1] = 0.0;
    K4[4] = cc;
    K4[7] = sc;
    K4[2] = 0.0;
    K4[5] = -sc;
    K4[8] = cc;
    b_cb[0] = cb;
    b_cb[3] = sb;
    b_cb[6] = 0.0;
    b_cb[1] = -sb;
    b_cb[4] = cb;
    b_cb[7] = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      b_cb[2 + 3 * i0] = iv0[i0];
    }

    b_ca[0] = ca;
    b_ca[3] = 0.0;
    b_ca[6] = sa;
    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_v[i0 + 3 * i2] = 0.0;
        for (loop_ub = 0; loop_ub < 3; loop_ub++) {
          b_v[i0 + 3 * i2] += K4[i0 + 3 * loop_ub] * b_cb[loop_ub + 3 * i2];
        }
      }

      b_ca[1 + 3 * i0] = iv1[i0];
    }

    b_ca[2] = -sa;
    b_ca[5] = 0.0;
    b_ca[8] = ca;
    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        K3[i0 + 3 * i2] = 0.0;
        for (loop_ub = 0; loop_ub < 3; loop_ub++) {
          K3[i0 + 3 * i2] += b_v[i0 + 3 * loop_ub] * b_ca[loop_ub + 3 * i2];
        }
      }
    }

    kron(dv0, K3, T);
    sa = 2.0 * L;
    dv1[0] = 6.0 / L;
    dv1[1] = 3.0;
    dv1[2] = 2.0 * L;
    dv1[3] = L;
    sb = DIy->data[i];
    cc = DIz->data[i];
    for (i0 = 0; i0 < 4; i0++) {
      sc = sa * dv1[i0];
      c_y[i0] = sb * sc;
      sc *= cc;
      co[i0] = sc;
    }

    sb = DG->data[i] * DJ->data[i] * (L * L) / DE->data[i];
    b_DA[0] = DA->data[i] * (L * L);
    b_DA[1] = co[0];
    b_DA[2] = c_y[0];
    diag(b_DA, K1);
    for (i0 = 0; i0 < 3; i0++) {
      K2[3 * i0] = 0.0;
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[i2 + 12 * i0] = K1[i2 + 3 * i0];
      }
    }

    K2[1] = 0.0;
    K2[4] = 0.0;
    K2[7] = co[1];
    K2[2] = 0.0;
    K2[5] = -c_y[1];
    K2[8] = 0.0;
    g[0] = sb;
    g[1] = c_y[2];
    g[2] = co[2];
    diag(g, K3);
    b_g[0] = -sb;
    b_g[1] = c_y[3];
    b_g[2] = co[3];
    diag(b_g, K4);
    sb = DE->data[i] / rt_powd_snf(L, 3.0);
    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[i2 + 12 * (i0 + 3)] = K2[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[i2 + 12 * (i0 + 6)] = -K1[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[i2 + 12 * (i0 + 9)] = K2[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * i0) + 3] = K2[i0 + 3 * i2];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 3)) + 3] = K3[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 6)) + 3] = -K2[i0 + 3 * i2];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 9)) + 3] = K4[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * i0) + 6] = -K1[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 3)) + 6] = -K2[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 6)) + 6] = K1[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 9)) + 6] = -K2[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * i0) + 9] = K2[i0 + 3 * i2];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 3)) + 9] = K4[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 6)) + 9] = -K2[i0 + 3 * i2];
      }
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_K1[(i2 + 12 * (i0 + 9)) + 9] = K3[i2 + 3 * i0];
      }
    }

    for (i0 = 0; i0 < 12; i0++) {
      for (i2 = 0; i2 < 12; i2++) {
        K[i2 + 12 * i0] = sb * b_K1[i2 + 12 * i0];
      }
    }

    loop_ub = Dw->size[0];
    i0 = w->size[0] * w->size[1];
    w->size[0] = 1;
    w->size[1] = loop_ub;
    emxEnsureCapacity((emxArray__common *)w, i0, (int)sizeof(double));
    for (i0 = 0; i0 < loop_ub; i0++) {
      w->data[w->size[0] * i0] = Dw->data[i0 + Dw->size[0] * i];
    }

    sb = -(L * L) / 12.0;
    i0 = r1->size[0];
    r1->size[0] = (w->size[1] + w->size[1]) + 6;
    emxEnsureCapacity((emxArray__common *)r1, i0, (int)sizeof(double));
    loop_ub = w->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      r1->data[i0] = 6.0 * w->data[w->size[0] * i0] / L;
    }

    r1->data[w->size[1]] = 0.0;
    r1->data[w->size[1] + 1] = -w->data[2];
    r1->data[w->size[1] + 2] = w->data[1];
    loop_ub = w->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      r1->data[(i0 + w->size[1]) + 3] = 6.0 * w->data[w->size[0] * i0] / L;
    }

    r1->data[(w->size[1] + w->size[1]) + 3] = 0.0;
    r1->data[(w->size[1] + w->size[1]) + 4] = w->data[2];
    r1->data[(w->size[1] + w->size[1]) + 5] = -w->data[1];
    i0 = Qf->size[0];
    Qf->size[0] = r1->size[0];
    emxEnsureCapacity((emxArray__common *)Qf, i0, (int)sizeof(double));
    loop_ub = r1->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      Qf->data[i0] = sb * r1->data[i0];
    }

    for (i0 = 0; i0 < 12; i0++) {
      for (i2 = 0; i2 < 12; i2++) {
        M[i0 + 12 * i2] = 0.0;
        for (loop_ub = 0; loop_ub < 12; loop_ub++) {
          M[i0 + 12 * i2] += K[i0 + 12 * loop_ub] * T[loop_ub + 12 * i2];
        }
      }
    }

    i0 = f->size[0];
    f->size[0] = e->size[1];
    emxEnsureCapacity((emxArray__common *)f, i0, (int)sizeof(double));
    loop_ub = e->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      f->data[i0] = DSt->data[e->data[e->size[0] * i0] - 1];
    }

    i0 = b_e->size[0];
    b_e->size[0] = e->size[1];
    emxEnsureCapacity((emxArray__common *)b_e, i0, (int)sizeof(int));
    loop_ub = e->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_e->data[i0] = e->data[e->size[0] * i0];
    }

    if (b_e->size[0] == 1) {
      for (i0 = 0; i0 < 12; i0++) {
        Qfs[i0] = 0.0;
        for (i2 = 0; i2 < 12; i2++) {
          sb = Qfs[i0] + M[i0 + 12 * i2] * f->data[i2];
          Qfs[i0] = sb;
        }
      }
    } else {
      memset(&Qfs[0], 0, 12U * sizeof(double));
      i0 = c_e->size[0];
      c_e->size[0] = e->size[1];
      emxEnsureCapacity((emxArray__common *)c_e, i0, (int)sizeof(int));
      loop_ub = e->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        c_e->data[i0] = e->data[e->size[0] * i0];
      }

      guard2 = false;
      if (12 == c_e->size[0]) {
        i0 = d_e->size[0];
        d_e->size[0] = e->size[1];
        emxEnsureCapacity((emxArray__common *)d_e, i0, (int)sizeof(int));
        loop_ub = e->size[1];
        for (i0 = 0; i0 < loop_ub; i0++) {
          d_e->data[i0] = e->data[e->size[0] * i0];
        }

        if (12 == d_e->size[0]) {
          for (i0 = 0; i0 < 12; i0++) {
            Qfs[i0] = 0.0;
            for (i2 = 0; i2 < 12; i2++) {
              sb = Qfs[i0] + M[i0 + 12 * i2] * f->data[i2];
              Qfs[i0] = sb;
            }
          }
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }

      if (guard2) {
        memset(&Qfs[0], 0, 12U * sizeof(double));
        idx = 0;
        for (loop_ub = 0; loop_ub < 12; loop_ub++) {
          if (DSt->data[e->data[e->size[0] * loop_ub] - 1] != 0.0) {
            ia = idx;
            for (ic = 0; ic < 12; ic++) {
              ia++;
              sb = Qfs[ic] + DSt->data[e->data[e->size[0] * loop_ub] - 1] * M[ia
                - 1];
              Qfs[ic] = sb;
            }
          }

          idx += 12;
        }
      }
    }

    memset(&K1[0], 0, 9U * sizeof(double));
    for (loop_ub = 0; loop_ub < 3; loop_ub++) {
      K1[loop_ub + 3 * loop_ub] = dv2[loop_ub];
    }

    for (i0 = 0; i0 < 9; i0++) {
      K2[i0] = 0.0;
      K3[i0] = 0.0;
    }

    K2[7] = 1.5 / L;
    K2[5] = -1.5 / L;
    for (loop_ub = 0; loop_ub < 3; loop_ub++) {
      K3[loop_ub + 3 * loop_ub] = iv2[loop_ub];
    }

    memset(&M[0], 0, 144U * sizeof(double));
    for (loop_ub = 0; loop_ub < 12; loop_ub++) {
      M[loop_ub + 12 * loop_ub] = 1.0;
    }

    i0 = DCon->data[2 + DCon->size[0] * i];
    if (i0 > 1073741823) {
      i0 = MAX_int32_T;
    } else if (i0 <= -1073741824) {
      i0 = MIN_int32_T;
    } else {
      i0 <<= 1;
    }

    i1 = (long long)i0 + DCon->data[3 + DCon->size[0] * i];
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    switch ((int)i1) {
     case 0:
      for (i0 = 0; i0 < 9; i0++) {
        K2[i0] = 2.0 * K2[i0] / 3.0;
      }

      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[i2 + 12 * iv3[i0]] = -K2[i2 + 3 * i0];
        }
      }

      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[i2 + 12 * iv3[i0 + 3]] = -K2[i2 + 3 * i0];
        }
      }

      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * iv3[i0]) + 3] = K3[i2 + 3 * i0];
        }
      }

      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * iv3[i0 + 3]) + 3] = 0.0;
        }
      }

      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * iv3[i0]) + 6] = K2[i2 + 3 * i0];
        }
      }

      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * iv3[i0 + 3]) + 6] = K2[i2 + 3 * i0];
        }
      }

      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * iv3[i0]) + 9] = 0.0;
        }
      }

      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * iv3[i0 + 3]) + 9] = K3[i2 + 3 * i0];
        }
      }
      break;

     case 1:
      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[i2 + 12 * (i0 + 3)] = -K2[i2 + 3 * i0];
        }

        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * (i0 + 3)) + 3] = K3[i2 + 3 * i0];
        }

        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * (i0 + 3)) + 6] = K2[i2 + 3 * i0];
        }

        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * (i0 + 3)) + 9] = K1[i2 + 3 * i0];
        }
      }
      break;

     case 2:
      for (i0 = 0; i0 < 3; i0++) {
        for (i2 = 0; i2 < 3; i2++) {
          M[i2 + 12 * (i0 + 9)] = -K2[i2 + 3 * i0];
        }

        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * (i0 + 9)) + 3] = K1[i2 + 3 * i0];
        }

        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * (i0 + 9)) + 6] = K2[i2 + 3 * i0];
        }

        for (i2 = 0; i2 < 3; i2++) {
          M[(i2 + 12 * (i0 + 9)) + 9] = K3[i2 + 3 * i0];
        }
      }
      break;
    }

    for (i0 = 0; i0 < 12; i0++) {
      for (i2 = 0; i2 < 12; i2++) {
        b_M[i0 + 12 * i2] = 0.0;
        for (loop_ub = 0; loop_ub < 12; loop_ub++) {
          b_M[i0 + 12 * i2] += M[i0 + 12 * loop_ub] * K[loop_ub + 12 * i2];
        }
      }
    }

    for (i0 = 0; i0 < 12; i0++) {
      memcpy(&K[12 * i0], &b_M[12 * i0], 12U * sizeof(double));
    }

    for (i0 = 0; i0 < 12; i0++) {
      for (i2 = 0; i2 < 12; i2++) {
        Ni->data[(i0 + Ni->size[0] * i2) + Ni->size[0] * Ni->size[1] * i] = 0.0;
        for (loop_ub = 0; loop_ub < 12; loop_ub++) {
          Ni->data[(i0 + Ni->size[0] * i2) + Ni->size[0] * Ni->size[1] * i] +=
            K[i0 + 12 * loop_ub] * T[loop_ub + 12 * i2];
        }
      }
    }

    i0 = ii->size[0];
    ii->size[0] = e->size[1];
    emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
    loop_ub = e->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      ii->data[i0] = e->data[e->size[0] * i0] - 1;
    }

    i0 = r0->size[0];
    r0->size[0] = e->size[1];
    emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(int));
    loop_ub = e->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      r0->data[i0] = e->data[e->size[0] * i0] - 1;
    }

    i0 = b_S->size[0] * b_S->size[1];
    b_S->size[0] = e->size[1];
    b_S->size[1] = e->size[1];
    emxEnsureCapacity((emxArray__common *)b_S, i0, (int)sizeof(double));
    loop_ub = e->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      nx = e->size[1];
      for (i2 = 0; i2 < nx; i2++) {
        b_S->data[i2 + b_S->size[0] * i0] = S->data[(e->data[e->size[0] * i2] +
          S->size[0] * (e->data[e->size[0] * i0] - 1)) - 1];
      }
    }

    for (i0 = 0; i0 < 12; i0++) {
      for (i2 = 0; i2 < 12; i2++) {
        sb = 0.0;
        for (loop_ub = 0; loop_ub < 12; loop_ub++) {
          sb += T[loop_ub + 12 * i0] * Ni->data[(loop_ub + Ni->size[0] * i2) +
            Ni->size[0] * Ni->size[1] * i];
        }

        c_S[i0 + 12 * i2] = b_S->data[i0 + 12 * i2] + sb;
      }
    }

    nx = ii->size[0];
    idx = r0->size[0];
    for (i0 = 0; i0 < idx; i0++) {
      for (i2 = 0; i2 < nx; i2++) {
        S->data[ii->data[i2] + S->size[0] * r0->data[i0]] = c_S[i2 + nx * i0];
      }
    }

    memset(&d_y[0], 0, 12U * sizeof(double));
    if (12 == Qf->size[0]) {
      for (i0 = 0; i0 < 12; i0++) {
        d_y[i0] = 0.0;
        for (i2 = 0; i2 < 12; i2++) {
          sb = d_y[i0] + M[i0 + 12 * i2] * Qf->data[i2];
          d_y[i0] = sb;
        }
      }
    } else {
      memset(&d_y[0], 0, 12U * sizeof(double));
      idx = 0;
      for (loop_ub = 0; loop_ub < 12; loop_ub++) {
        if (Qf->data[loop_ub] != 0.0) {
          ia = idx;
          for (ic = 0; ic < 12; ic++) {
            ia++;
            sb = d_y[ic] + Qf->data[loop_ub] * M[ia - 1];
            d_y[ic] = sb;
          }
        }

        idx += 12;
      }
    }

    for (i0 = 0; i0 < 12; i0++) {
      Qfi->data[i0 + Qfi->size[0] * i] = d_y[i0];
    }

    i0 = b_Pf->size[0];
    b_Pf->size[0] = e->size[1];
    emxEnsureCapacity((emxArray__common *)b_Pf, i0, (int)sizeof(double));
    loop_ub = e->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_Pf->data[i0] = Pf->data[e->data[e->size[0] * i0] - 1];
    }

    for (i0 = 0; i0 < 12; i0++) {
      for (i2 = 0; i2 < 12; i2++) {
        c_S[i0 + 12 * i2] = 0.0;
        for (loop_ub = 0; loop_ub < 12; loop_ub++) {
          c_S[i0 + 12 * i2] += T[loop_ub + 12 * i0] * M[loop_ub + 12 * i2];
        }
      }
    }

    for (i0 = 0; i0 < 12; i0++) {
      b_V[i0] = Qf->data[i0] + Qfs[i0];
    }

    for (i0 = 0; i0 < 12; i0++) {
      sb = 0.0;
      for (i2 = 0; i2 < 12; i2++) {
        sb += c_S[i0 + 12 * i2] * b_V[i2];
      }

      c_Pf[i0] = b_Pf->data[i0] + sb;
    }

    loop_ub = e->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      Pf->data[e->data[e->size[0] * i0] - 1] = c_Pf[(*(int (*)[2])e->size)[0] *
        i0];
    }

    i0 = e_e->size[0] * e_e->size[1];
    e_e->size[0] = 1;
    e_e->size[1] = e->size[1];
    emxEnsureCapacity((emxArray__common *)e_e, i0, (int)sizeof(double));
    loop_ub = e->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      e_e->data[e_e->size[0] * i0] = e->data[e->size[0] * i0];
    }

    for (i0 = 0; i0 < 12; i0++) {
      Ei->data[i0 + Ei->size[0] * i] = e_e->data[i0];
    }

    i++;
  }

  emxFree_real_T(&e_e);
  emxFree_real_T(&b_Pf);
  emxFree_real_T(&b_S);
  emxFree_int32_T(&d_e);
  emxFree_int32_T(&c_e);
  emxFree_int32_T(&b_e);
  emxFree_real_T(&r1);
  emxFree_int32_T(&b_y);
  emxFree_int32_T(&y);
  emxFree_int32_T(&r0);
  emxFree_real_T(&w);
  emxFree_int32_T(&e);
  i0 = V->size[0] * V->size[1];
  V->size[0] = 6;
  V->size[1] = DRe->size[1];
  emxEnsureCapacity((emxArray__common *)V, i0, (int)sizeof(double));
  loop_ub = DRe->size[0] * DRe->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    V->data[i0] = 1.0 - (double)((DRe->data[i0] != 0.0) || (DSt->data[i0] != 0.0));
  }

  nx = 6 * V->size[1];
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= nx)) {
    guard1 = false;
    if (V->data[loop_ub - 1] != 0.0) {
      idx++;
      ii->data[idx - 1] = loop_ub;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      loop_ub++;
    }
  }

  if (nx == 1) {
    if (idx == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
    }
  } else {
    if (1 > idx) {
      loop_ub = 0;
    } else {
      loop_ub = idx;
    }

    b_emxInit_int32_T(&b_ii, 1);
    i0 = b_ii->size[0];
    b_ii->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)b_ii, i0, (int)sizeof(int));
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_ii->data[i0] = ii->data[i0];
    }

    i0 = ii->size[0];
    ii->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
    loop_ub = b_ii->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      ii->data[i0] = b_ii->data[i0];
    }

    emxFree_int32_T(&b_ii);
  }

  i0 = f->size[0];
  f->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)f, i0, (int)sizeof(double));
  loop_ub = ii->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    f->data[i0] = ii->data[i0];
  }

  i0 = Qf->size[0];
  Qf->size[0] = f->size[0];
  emxEnsureCapacity((emxArray__common *)Qf, i0, (int)sizeof(double));
  loop_ub = f->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    Qf->data[i0] = DLoad->data[(int)f->data[i0] - 1] - Pf->data[(int)f->data[i0]
      - 1];
  }

  b_emxInit_real_T(&d_S, 2);
  i0 = d_S->size[0] * d_S->size[1];
  d_S->size[0] = f->size[0];
  d_S->size[1] = f->size[0];
  emxEnsureCapacity((emxArray__common *)d_S, i0, (int)sizeof(double));
  loop_ub = f->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    nx = f->size[0];
    for (i2 = 0; i2 < nx; i2++) {
      d_S->data[i2 + d_S->size[0] * i0] = S->data[((int)f->data[i2] + S->size[0]
        * ((int)f->data[i0] - 1)) - 1];
    }
  }

  mldivide(d_S, Qf);
  loop_ub = Qf->size[0];
  emxFree_real_T(&d_S);
  for (i0 = 0; i0 < loop_ub; i0++) {
    V->data[(int)f->data[i0] - 1] = Qf->data[i0];
  }

  b_guard1 = false;
  if (S->size[1] == 1) {
    b_guard1 = true;
  } else {
    loop_ub = 6 * V->size[1];
    if (loop_ub == 1) {
      b_guard1 = true;
    } else {
      span = (unsigned int)S->size[0];
      i0 = Qf->size[0];
      Qf->size[0] = (int)span;
      emxEnsureCapacity((emxArray__common *)Qf, i0, (int)sizeof(double));
      loop_ub = (int)span;
      for (i0 = 0; i0 < loop_ub; i0++) {
        Qf->data[i0] = 0.0;
      }

      if (S->size[0] == 0) {
      } else {
        loop_ub = 0;
        while (loop_ub <= 0) {
          i0 = S->size[0];
          for (ic = 1; ic <= i0; ic++) {
            Qf->data[ic - 1] = 0.0;
          }

          loop_ub = S->size[0];
        }

        nx = 0;
        loop_ub = 0;
        while (loop_ub <= 0) {
          idx = 0;
          i0 = nx + S->size[1];
          for (loop_ub = nx; loop_ub + 1 <= i0; loop_ub++) {
            if (V->data[loop_ub] != 0.0) {
              ia = idx;
              i2 = S->size[0];
              for (ic = 0; ic + 1 <= i2; ic++) {
                ia++;
                Qf->data[ic] += V->data[loop_ub] * S->data[ia - 1];
              }
            }

            idx += S->size[0];
          }

          nx += S->size[1];
          loop_ub = S->size[0];
        }
      }
    }
  }

  if (b_guard1) {
    i0 = Qf->size[0];
    Qf->size[0] = S->size[0];
    emxEnsureCapacity((emxArray__common *)Qf, i0, (int)sizeof(double));
    loop_ub = S->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      Qf->data[i0] = 0.0;
      nx = S->size[1];
      for (i2 = 0; i2 < nx; i2++) {
        Qf->data[i0] += S->data[i0 + S->size[0] * i2] * V->data[i2];
      }
    }
  }

  emxFree_real_T(&S);
  i0 = Qf->size[0];
  emxEnsureCapacity((emxArray__common *)Qf, i0, (int)sizeof(double));
  loop_ub = Qf->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    Qf->data[i0] += Pf->data[i0];
  }

  emxFree_real_T(&Pf);
  i0 = R->size[0] * R->size[1];
  R->size[0] = 6;
  R->size[1] = n;
  emxEnsureCapacity((emxArray__common *)R, i0, (int)sizeof(double));
  for (loop_ub = 0; loop_ub + 1 <= Qf->size[0]; loop_ub++) {
    R->data[loop_ub] = Qf->data[loop_ub];
  }

  emxFree_real_T(&Qf);
  i0 = ii->size[0];
  ii->size[0] = f->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
  loop_ub = f->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    ii->data[i0] = (int)f->data[i0];
  }

  emxFree_real_T(&f);
  loop_ub = ii->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    R->data[ii->data[i0] - 1] = 0.0;
  }

  emxFree_int32_T(&ii);
  i0 = V->size[0] * V->size[1];
  V->size[0] = 6;
  emxEnsureCapacity((emxArray__common *)V, i0, (int)sizeof(double));
  loop_ub = V->size[0];
  nx = V->size[1];
  loop_ub *= nx;
  for (i0 = 0; i0 < loop_ub; i0++) {
    V->data[i0] += DSt->data[i0];
  }

  for (i = 0; i + 1 <= m; i++) {
    for (i0 = 0; i0 < 12; i0++) {
      b_V[i0] = V->data[(int)Ei->data[i0 + Ei->size[0] * i] - 1];
    }

    for (i0 = 0; i0 < 12; i0++) {
      sb = 0.0;
      for (i2 = 0; i2 < 12; i2++) {
        sb += Ni->data[(i0 + Ni->size[0] * i2) + Ni->size[0] * Ni->size[1] * i] *
          b_V[i2];
      }

      Q->data[i0 + Q->size[0] * i] = sb + Qfi->data[i0 + Qfi->size[0] * i];
    }
  }

  emxFree_real_T(&Ei);
  emxFree_real_T(&Qfi);
  emxFree_real_T(&Ni);
}

/*
 * File trailer for MSA.c
 *
 * [EOF]
 */
