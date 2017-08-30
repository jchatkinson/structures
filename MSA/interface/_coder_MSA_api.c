/*
 * File: _coder_MSA_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29
 */

/* Include files */
#include "_coder_MSA_api.h"

/* Function Declarations */
static int emlrt_marshallIn(const emlrtStack *sp, const mxArray *m, const char
  *identifier);
static int b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *DCon, const
  char *identifier, emxArray_int32_T *y);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_int32_T *y);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *DCoord,
  const char *identifier, emxArray_real_T *y);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Dbe, const
  char *identifier, emxArray_real_T *y);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Dw, const
  char *identifier, emxArray_real_T *y);
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *DSt, const
  char *identifier, emxArray_real_T *y);
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);
static const mxArray *b_emlrt_marshallOut(const emxArray_real_T *u);
static int m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_int32_T *ret);
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray,
  int numDimensions, boolean_T doPush);
static void emxFree_int32_T(emxArray_int32_T **pEmxArray);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int numDimensions, boolean_T doPush);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void b_emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int numDimensions, boolean_T doPush);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void MSA_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void MSA_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void MSA_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  MSA_xil_terminate();
}

/*
 * Arguments    : const mxArray *prhs[15]
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void MSA_api(const mxArray *prhs[15], const mxArray *plhs[3])
{
  emxArray_int32_T *DCon;
  emxArray_real_T *DCoord;
  emxArray_real_T *Dbe;
  emxArray_real_T *DA;
  emxArray_real_T *DIy;
  emxArray_real_T *DIz;
  emxArray_real_T *DG;
  emxArray_real_T *DJ;
  emxArray_real_T *DE;
  emxArray_real_T *Dw;
  emxArray_real_T *DSt;
  emxArray_real_T *DRe;
  emxArray_real_T *DLoad;
  emxArray_real_T *Q;
  emxArray_real_T *V;
  emxArray_real_T *R;
  int m;
  int n;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_int32_T(&st, &DCon, 2, true);
  emxInit_real_T(&st, &DCoord, 2, true);
  b_emxInit_real_T(&st, &Dbe, 1, true);
  b_emxInit_real_T(&st, &DA, 1, true);
  b_emxInit_real_T(&st, &DIy, 1, true);
  b_emxInit_real_T(&st, &DIz, 1, true);
  b_emxInit_real_T(&st, &DG, 1, true);
  b_emxInit_real_T(&st, &DJ, 1, true);
  b_emxInit_real_T(&st, &DE, 1, true);
  emxInit_real_T(&st, &Dw, 2, true);
  emxInit_real_T(&st, &DSt, 2, true);
  emxInit_real_T(&st, &DRe, 2, true);
  emxInit_real_T(&st, &DLoad, 2, true);
  emxInit_real_T(&st, &Q, 2, true);
  emxInit_real_T(&st, &V, 2, true);
  emxInit_real_T(&st, &R, 2, true);
  prhs[2] = emlrtProtectR2012b(prhs[2], 2, false, -1);
  prhs[3] = emlrtProtectR2012b(prhs[3], 3, false, -1);
  prhs[4] = emlrtProtectR2012b(prhs[4], 4, false, -1);
  prhs[5] = emlrtProtectR2012b(prhs[5], 5, false, -1);
  prhs[6] = emlrtProtectR2012b(prhs[6], 6, false, -1);
  prhs[7] = emlrtProtectR2012b(prhs[7], 7, false, -1);
  prhs[8] = emlrtProtectR2012b(prhs[8], 8, false, -1);
  prhs[9] = emlrtProtectR2012b(prhs[9], 9, false, -1);
  prhs[10] = emlrtProtectR2012b(prhs[10], 10, false, -1);
  prhs[11] = emlrtProtectR2012b(prhs[11], 11, false, -1);
  prhs[12] = emlrtProtectR2012b(prhs[12], 12, false, -1);
  prhs[13] = emlrtProtectR2012b(prhs[13], 13, false, -1);
  prhs[14] = emlrtProtectR2012b(prhs[14], 14, false, -1);

  /* Marshall function inputs */
  m = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "m");
  n = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "n");
  c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "DCon", DCon);
  e_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "DCoord", DCoord);
  g_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "Dbe", Dbe);
  g_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "DA", DA);
  g_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "DIy", DIy);
  g_emlrt_marshallIn(&st, emlrtAlias(prhs[7]), "DIz", DIz);
  g_emlrt_marshallIn(&st, emlrtAlias(prhs[8]), "DG", DG);
  g_emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "DJ", DJ);
  g_emlrt_marshallIn(&st, emlrtAlias(prhs[10]), "DE", DE);
  i_emlrt_marshallIn(&st, emlrtAlias(prhs[11]), "Dw", Dw);
  k_emlrt_marshallIn(&st, emlrtAlias(prhs[12]), "DSt", DSt);
  k_emlrt_marshallIn(&st, emlrtAlias(prhs[13]), "DRe", DRe);
  k_emlrt_marshallIn(&st, emlrtAlias(prhs[14]), "DLoad", DLoad);

  /* Invoke the target function */
  MSA(m, n, DCon, DCoord, Dbe, DA, DIy, DIz, DG, DJ, DE, Dw, DSt, DRe, DLoad, Q,
      V, R);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(Q);
  plhs[1] = b_emlrt_marshallOut(V);
  plhs[2] = b_emlrt_marshallOut(R);
  R->canFreeData = false;
  emxFree_real_T(&R);
  V->canFreeData = false;
  emxFree_real_T(&V);
  Q->canFreeData = false;
  emxFree_real_T(&Q);
  DLoad->canFreeData = false;
  emxFree_real_T(&DLoad);
  DRe->canFreeData = false;
  emxFree_real_T(&DRe);
  DSt->canFreeData = false;
  emxFree_real_T(&DSt);
  Dw->canFreeData = false;
  emxFree_real_T(&Dw);
  DE->canFreeData = false;
  emxFree_real_T(&DE);
  DJ->canFreeData = false;
  emxFree_real_T(&DJ);
  DG->canFreeData = false;
  emxFree_real_T(&DG);
  DIz->canFreeData = false;
  emxFree_real_T(&DIz);
  DIy->canFreeData = false;
  emxFree_real_T(&DIy);
  DA->canFreeData = false;
  emxFree_real_T(&DA);
  Dbe->canFreeData = false;
  emxFree_real_T(&Dbe);
  DCoord->canFreeData = false;
  emxFree_real_T(&DCoord);
  DCon->canFreeData = false;
  emxFree_int32_T(&DCon);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *m
 *                const char *identifier
 * Return Type  : int
 */
static int emlrt_marshallIn(const emlrtStack *sp, const mxArray *m, const char
  *identifier)
{
  int y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(m), &thisId);
  emlrtDestroyArray(&m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : int
 */
static int b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  int y;
  y = m_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *DCon
 *                const char *identifier
 *                emxArray_int32_T *y
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *DCon, const
  char *identifier, emxArray_int32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  d_emlrt_marshallIn(sp, emlrtAlias(DCon), &thisId, y);
  emlrtDestroyArray(&DCon);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_int32_T *y
 * Return Type  : void
 */
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_int32_T *y)
{
  n_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *DCoord
 *                const char *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *DCoord,
  const char *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  f_emlrt_marshallIn(sp, emlrtAlias(DCoord), &thisId, y);
  emlrtDestroyArray(&DCoord);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  o_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *Dbe
 *                const char *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Dbe, const
  char *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  h_emlrt_marshallIn(sp, emlrtAlias(Dbe), &thisId, y);
  emlrtDestroyArray(&Dbe);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  p_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *Dw
 *                const char *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Dw, const
  char *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  j_emlrt_marshallIn(sp, emlrtAlias(Dw), &thisId, y);
  emlrtDestroyArray(&Dw);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  q_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *DSt
 *                const char *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *DSt, const
  char *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  l_emlrt_marshallIn(sp, emlrtAlias(DSt), &thisId, y);
  emlrtDestroyArray(&DSt);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  r_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  static const int iv0[2] = { 0, 0 };

  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)u->data);
  emlrtSetDimensions((mxArray *)m0, u->size, 2);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  static const int iv1[2] = { 0, 0 };

  const mxArray *m1;
  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv1, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m1, (void *)u->data);
  emlrtSetDimensions((mxArray *)m1, u->size, 2);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : int
 */
static int m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  int ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "int32", false, 0U, 0);
  ret = *(int *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_int32_T *ret
 * Return Type  : void
 */
static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_int32_T *ret)
{
  int iv2[2];
  boolean_T bv0[2];
  int i0;
  static const boolean_T bv1[2] = { false, true };

  int iv3[2];
  for (i0 = 0; i0 < 2; i0++) {
    iv2[i0] = 4 + -5 * i0;
    bv0[i0] = bv1[i0];
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "int32", false, 2U, iv2, bv0, iv3);
  ret->size[0] = iv3[0];
  ret->size[1] = iv3[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (int *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int iv4[2];
  boolean_T bv2[2];
  int i1;
  static const boolean_T bv3[2] = { false, true };

  int iv5[2];
  for (i1 = 0; i1 < 2; i1++) {
    iv4[i1] = 3 + -4 * i1;
    bv2[i1] = bv3[i1];
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv4, bv2, iv5);
  ret->size[0] = iv5[0];
  ret->size[1] = iv5[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (double *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int iv6[1];
  boolean_T bv4[1];
  int iv7[1];
  iv6[0] = -1;
  bv4[0] = true;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 1U, iv6, bv4, iv7);
  ret->size[0] = iv7[0];
  ret->allocatedSize = ret->size[0];
  ret->data = (double *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int iv8[2];
  boolean_T bv5[2];
  int i2;
  static const boolean_T bv6[2] = { true, false };

  int iv9[2];
  for (i2 = 0; i2 < 2; i2++) {
    iv8[i2] = (i2 << 2) - 1;
    bv5[i2] = bv6[i2];
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv8, bv5, iv9);
  ret->size[0] = iv9[0];
  ret->size[1] = iv9[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (double *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int iv10[2];
  boolean_T bv7[2];
  int i3;
  static const boolean_T bv8[2] = { false, true };

  int iv11[2];
  for (i3 = 0; i3 < 2; i3++) {
    iv10[i3] = 6 + -7 * i3;
    bv7[i3] = bv8[i3];
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv10, bv7, iv11);
  ret->size[0] = iv11[0];
  ret->size[1] = iv11[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (double *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                emxArray_int32_T **pEmxArray
 *                int numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray,
  int numDimensions, boolean_T doPush)
{
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *)emlrtMallocMex(sizeof(emxArray_int32_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_int32_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)emlrtMallocMex((unsigned int)(sizeof(int) *
    numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_int32_T **pEmxArray
 * Return Type  : void
 */
static void emxFree_int32_T(emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if (((*pEmxArray)->data != (int *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

/*
 * Arguments    : const emlrtStack *sp
 *                emxArray_real_T **pEmxArray
 *                int numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)emlrtMallocMex((unsigned int)(sizeof(int) *
    numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 * Return Type  : void
 */
static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (double *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

/*
 * Arguments    : const emlrtStack *sp
 *                emxArray_real_T **pEmxArray
 *                int numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void b_emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)emlrtMallocMex((unsigned int)(sizeof(int) *
    numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * File trailer for _coder_MSA_api.c
 *
 * [EOF]
 */
