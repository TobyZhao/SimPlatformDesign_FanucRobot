#ifndef __c15_DynTaskVerify_h__
#define __c15_DynTaskVerify_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  const char *context;
  const char *name;
  const char *dominantType;
  const char *resolved;
  uint32_T fileLength;
  uint32_T fileTime1;
  uint32_T fileTime2;
} c15_ResolvedFunctionInfo;

typedef struct {
  SimStruct *S;
  real_T c15_Cen[18];
  real_T c15_L[9];
  real_T c15_Ma[6];
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c15_doneDoubleBufferReInit;
  boolean_T c15_isStable;
  uint8_T c15_is_active_c15_DynTaskVerify;
  ChartInfoStruct chartInfo;
} SFc15_DynTaskVerifyInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c15_DynTaskVerify_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c15_DynTaskVerify_get_check_sum(mxArray *plhs[]);
extern void c15_DynTaskVerify_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
