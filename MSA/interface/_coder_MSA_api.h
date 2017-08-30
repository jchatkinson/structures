/* 
 * File: _coder_MSA_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 28-Aug-2017 21:55:29 
 */

#ifndef ___CODER_MSA_API_H__
#define ___CODER_MSA_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T
struct emxArray_int32_T
{
    int *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_int32_T*/
#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T
typedef struct emxArray_int32_T emxArray_int32_T;
#endif /*typedef_emxArray_int32_T*/
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T
{
    double *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real_T*/
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /*typedef_emxArray_real_T*/

/* Function Declarations */
extern void MSA_initialize(emlrtContext *aContext);
extern void MSA_terminate(void);
extern void MSA_atexit(void);
extern void MSA_api(const mxArray *prhs[15], const mxArray *plhs[3]);
extern void MSA(int m, int n, emxArray_int32_T *DCon, emxArray_real_T *DCoord, emxArray_real_T *Dbe, emxArray_real_T *DA, emxArray_real_T *DIy, emxArray_real_T *DIz, emxArray_real_T *DG, emxArray_real_T *DJ, emxArray_real_T *DE, emxArray_real_T *Dw, emxArray_real_T *DSt, emxArray_real_T *DRe, emxArray_real_T *DLoad, emxArray_real_T *Q, emxArray_real_T *V, emxArray_real_T *R);
extern void MSA_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_MSA_api.h 
 *  
 * [EOF] 
 */
