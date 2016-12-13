#ifndef __c1_CtrPlatform_gravity_compensation_h__
#define __c1_CtrPlatform_gravity_compensation_h__

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
} c1_ResolvedFunctionInfo;

typedef struct {
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_CtrPlatform_gravity_compensation;
  real_T c1_init_Rot[9];
  real_T c1_L[9];
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
} SFc1_CtrPlatform_gravity_compensationInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c1_CtrPlatform_gravity_compensation_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_CtrPlatform_gravity_compensation_get_check_sum(mxArray *plhs[]);
extern void c1_CtrPlatform_gravity_compensation_method_dispatcher(SimStruct *S,
  int_T method, void *data);

#endif