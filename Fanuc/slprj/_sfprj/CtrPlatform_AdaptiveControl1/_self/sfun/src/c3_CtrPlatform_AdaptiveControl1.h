#ifndef __c3_CtrPlatform_AdaptiveControl1_h__
#define __c3_CtrPlatform_AdaptiveControl1_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c3_ResolvedFunctionInfo;

typedef struct {
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_CtrPlatform_AdaptiveControl1;
  real_T c3_L[9];
  real_T c3_Cen[18];
  real_T c3_Ma[6];
  real_T c3_Ie1[9];
  real_T c3_Ie2[9];
  real_T c3_Ie3[9];
  real_T c3_Ie4[9];
  real_T c3_Ie5[9];
  real_T c3_Ie6[9];
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
} SFc3_CtrPlatform_AdaptiveControl1InstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c3_CtrPlatform_AdaptiveControl1_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_CtrPlatform_AdaptiveControl1_get_check_sum(mxArray *plhs[]);
extern void c3_CtrPlatform_AdaptiveControl1_method_dispatcher(SimStruct *S,
  int_T method, void *data);

#endif