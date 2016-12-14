#ifndef __c7_DynJointVerify_h__
#define __c7_DynJointVerify_h__

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
} c7_ResolvedFunctionInfo;

typedef struct {
  SimStruct *S;
  real_T c7_L[9];
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c7_doneDoubleBufferReInit;
  boolean_T c7_isStable;
  uint8_T c7_is_active_c7_DynJointVerify;
  ChartInfoStruct chartInfo;
} SFc7_DynJointVerifyInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c7_DynJointVerify_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c7_DynJointVerify_get_check_sum(mxArray *plhs[]);
extern void c7_DynJointVerify_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
