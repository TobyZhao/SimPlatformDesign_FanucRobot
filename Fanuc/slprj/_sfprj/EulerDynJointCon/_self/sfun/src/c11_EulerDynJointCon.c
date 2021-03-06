/* Include files */

#include "blascompat32.h"
#include "EulerDynJointCon_sfun.h"
#include "c11_EulerDynJointCon.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "EulerDynJointCon_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c11_debug_family_names[10] = { "EndVW", "gd", "EndW",
  "gd_pos", "nargin", "nargout", "Theta", "Omega", "L", "EndVel" };

static const char *c11_b_debug_family_names[64] = { "A1", "A2", "A3", "A4", "A5",
  "L1", "L2", "L3", "L4", "L5", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
  "t10", "t11", "t12", "t13", "t14", "t15", "t16", "t17", "t18", "t19", "t20",
  "t21", "t22", "t23", "t24", "t25", "t26", "t27", "t28", "t29", "t30", "t31",
  "t32", "t33", "t34", "t35", "t36", "t37", "t38", "t47", "t39", "t40", "t41",
  "t42", "t43", "t44", "t45", "t46", "t48", "t49", "t50", "nargin", "nargout",
  "in1", "in2", "spat_Jacobian" };

static const char *c11_c_debug_family_names[68] = { "A1", "A2", "A3", "A4", "A5",
  "A6", "L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9", "t2", "t3", "t4",
  "t5", "t6", "t7", "t8", "t9", "t10", "t11", "t12", "t13", "t14", "t23", "t15",
  "t16", "t17", "t18", "t19", "t20", "t21", "t22", "t24", "t25", "t26", "t27",
  "t34", "t28", "t29", "t30", "t31", "t32", "t36", "t33", "t35", "t37", "t38",
  "t39", "t40", "t41", "t42", "t43", "t44", "t45", "t47", "t46", "t48", "t49",
  "nargin", "nargout", "in1", "in2", "gst" };

/* Function Declarations */
static void initialize_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);
static void initialize_params_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance);
static void enable_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);
static void disable_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);
static void c11_update_debugger_state_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance);
static void set_sim_state_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance, const mxArray *c11_st);
static void finalize_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);
static void sf_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);
static void c11_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);
static void compInitSubchartSimstructsFcn_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber);
static void c11_spat_Jacobian(SFc11_EulerDynJointConInstanceStruct
  *chartInstance, real_T c11_in1[9], real_T c11_in2[6], real_T
  c11_b_spat_Jacobian[36]);
static void c11_eml_scalar_eg(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);
static void c11_b_eml_scalar_eg(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);
static void c11_fwd_kin(SFc11_EulerDynJointConInstanceStruct *chartInstance,
  real_T c11_in1[9], real_T c11_in2[6], real_T c11_gst[16]);
static const mxArray *c11_sf_marshall(void *chartInstanceVoid, void *c11_u);
static const mxArray *c11_b_sf_marshall(void *chartInstanceVoid, void *c11_u);
static const mxArray *c11_c_sf_marshall(void *chartInstanceVoid, void *c11_u);
static const mxArray *c11_d_sf_marshall(void *chartInstanceVoid, void *c11_u);
static const mxArray *c11_e_sf_marshall(void *chartInstanceVoid, void *c11_u);
static const mxArray *c11_f_sf_marshall(void *chartInstanceVoid, void *c11_u);
static const mxArray *c11_g_sf_marshall(void *chartInstanceVoid, void *c11_u);
static void c11_info_helper(c11_ResolvedFunctionInfo c11_info[59]);
static const mxArray *c11_h_sf_marshall(void *chartInstanceVoid, void *c11_u);
static void c11_emlrt_marshallIn(SFc11_EulerDynJointConInstanceStruct
  *chartInstance, const mxArray *c11_EndVel, const char_T *c11_name, real_T
  c11_y[3]);
static uint8_T c11_b_emlrt_marshallIn(SFc11_EulerDynJointConInstanceStruct
  *chartInstance, const mxArray *c11_b_is_active_c11_EulerDynJointCon, const
  char_T *c11_name);
static void init_dsm_address_info(SFc11_EulerDynJointConInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c11_is_active_c11_EulerDynJointCon = 0U;
}

static void initialize_params_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance)
{
  real_T c11_dv0[9];
  int32_T c11_i0;
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'L' in the parent workspace.\n");
  sf_mex_import("L", sf_mex_get_sfun_param(chartInstance->S, 0, 0), c11_dv0, 0,
                0, 0U, 1, 0U, 2, 1, 9);
  for (c11_i0 = 0; c11_i0 < 9; c11_i0 = c11_i0 + 1) {
    chartInstance->c11_L[c11_i0] = c11_dv0[c11_i0];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c11_update_debugger_state_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance)
{
  const mxArray *c11_st = NULL;
  const mxArray *c11_y = NULL;
  int32_T c11_i1;
  real_T c11_hoistedGlobal[3];
  int32_T c11_i2;
  real_T c11_u[3];
  const mxArray *c11_b_y = NULL;
  uint8_T c11_b_hoistedGlobal;
  uint8_T c11_b_u;
  const mxArray *c11_c_y = NULL;
  real_T (*c11_EndVel)[3];
  c11_EndVel = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c11_st = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_createcellarray(2));
  for (c11_i1 = 0; c11_i1 < 3; c11_i1 = c11_i1 + 1) {
    c11_hoistedGlobal[c11_i1] = (*c11_EndVel)[c11_i1];
  }

  for (c11_i2 = 0; c11_i2 < 3; c11_i2 = c11_i2 + 1) {
    c11_u[c11_i2] = c11_hoistedGlobal[c11_i2];
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 1, 3));
  sf_mex_setcell(c11_y, 0, c11_b_y);
  c11_b_hoistedGlobal = chartInstance->c11_is_active_c11_EulerDynJointCon;
  c11_b_u = c11_b_hoistedGlobal;
  c11_c_y = NULL;
  sf_mex_assign(&c11_c_y, sf_mex_create("y", &c11_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c11_y, 1, c11_c_y);
  sf_mex_assign(&c11_st, c11_y);
  return c11_st;
}

static void set_sim_state_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance, const mxArray *c11_st)
{
  const mxArray *c11_u;
  real_T c11_dv1[3];
  int32_T c11_i3;
  real_T (*c11_EndVel)[3];
  c11_EndVel = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c11_doneDoubleBufferReInit = TRUE;
  c11_u = sf_mex_dup(c11_st);
  c11_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c11_u, 0)),
                       "EndVel", c11_dv1);
  for (c11_i3 = 0; c11_i3 < 3; c11_i3 = c11_i3 + 1) {
    (*c11_EndVel)[c11_i3] = c11_dv1[c11_i3];
  }

  chartInstance->c11_is_active_c11_EulerDynJointCon = c11_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c11_u, 1)),
     "is_active_c11_EulerDynJointCon");
  sf_mex_destroy(&c11_u);
  c11_update_debugger_state_c11_EulerDynJointCon(chartInstance);
  sf_mex_destroy(&c11_st);
}

static void finalize_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
}

static void sf_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
  int32_T c11_i4;
  int32_T c11_i5;
  int32_T c11_i6;
  int32_T c11_i7;
  int32_T c11_previousEvent;
  real_T (*c11_EndVel)[3];
  real_T (*c11_Omega)[6];
  real_T (*c11_Theta)[6];
  c11_EndVel = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c11_Omega = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c11_Theta = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 10);
  for (c11_i4 = 0; c11_i4 < 6; c11_i4 = c11_i4 + 1) {
    _SFD_DATA_RANGE_CHECK((*c11_Theta)[c11_i4], 0U);
  }

  for (c11_i5 = 0; c11_i5 < 6; c11_i5 = c11_i5 + 1) {
    _SFD_DATA_RANGE_CHECK((*c11_Omega)[c11_i5], 1U);
  }

  for (c11_i6 = 0; c11_i6 < 3; c11_i6 = c11_i6 + 1) {
    _SFD_DATA_RANGE_CHECK((*c11_EndVel)[c11_i6], 2U);
  }

  for (c11_i7 = 0; c11_i7 < 9; c11_i7 = c11_i7 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c11_L[c11_i7], 3U);
  }

  c11_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  c11_c11_EulerDynJointCon(chartInstance);
  _sfEvent_ = c11_previousEvent;
  sf_debug_check_for_state_inconsistency(_EulerDynJointConMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c11_c11_EulerDynJointCon(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
  int32_T c11_i8;
  real_T c11_hoistedGlobal[6];
  int32_T c11_i9;
  real_T c11_b_hoistedGlobal[6];
  int32_T c11_i10;
  real_T c11_c_hoistedGlobal[9];
  int32_T c11_i11;
  real_T c11_Theta[6];
  int32_T c11_i12;
  real_T c11_Omega[6];
  int32_T c11_i13;
  real_T c11_b_L[9];
  uint32_T c11_debug_family_var_map[10];
  static const char *c11_sv0[10] = { "EndVW", "gd", "EndW", "gd_pos", "nargin",
    "nargout", "Theta", "Omega", "L", "EndVel" };

  real_T c11_EndVW[6];
  real_T c11_gd[16];
  real_T c11_EndW[3];
  real_T c11_gd_pos[3];
  real_T c11_nargin = 3.0;
  real_T c11_nargout = 1.0;
  real_T c11_EndVel[3];
  int32_T c11_i14;
  real_T c11_c_L[9];
  int32_T c11_i15;
  real_T c11_b_Theta[6];
  real_T c11_a[36];
  int32_T c11_i16;
  real_T c11_b[6];
  int32_T c11_i17;
  real_T c11_A[36];
  int32_T c11_i18;
  real_T c11_B[6];
  int32_T c11_i19;
  int32_T c11_i20;
  real_T c11_b_A[36];
  int32_T c11_i21;
  real_T c11_b_B[6];
  int32_T c11_i22;
  real_T c11_c_A[36];
  int32_T c11_i23;
  real_T c11_c_B[6];
  int32_T c11_i24;
  int32_T c11_i25;
  int32_T c11_i26;
  int32_T c11_i27;
  real_T c11_d_L[9];
  int32_T c11_i28;
  real_T c11_c_Theta[6];
  real_T c11_dv2[16];
  int32_T c11_i29;
  int32_T c11_i30;
  int32_T c11_i31;
  int32_T c11_i32;
  real_T c11_b_a[3];
  int32_T c11_i33;
  real_T c11_b_b[3];
  real_T c11_c_a;
  real_T c11_c_b;
  real_T c11_y;
  real_T c11_d_a;
  real_T c11_d_b;
  real_T c11_b_y;
  real_T c11_c1;
  real_T c11_e_a;
  real_T c11_e_b;
  real_T c11_c_y;
  real_T c11_f_a;
  real_T c11_f_b;
  real_T c11_d_y;
  real_T c11_c2;
  real_T c11_g_a;
  real_T c11_g_b;
  real_T c11_e_y;
  real_T c11_h_a;
  real_T c11_h_b;
  real_T c11_f_y;
  real_T c11_c3;
  int32_T c11_i34;
  real_T (*c11_b_EndVel)[3];
  real_T (*c11_b_Omega)[6];
  real_T (*c11_d_Theta)[6];
  c11_b_EndVel = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c11_b_Omega = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c11_d_Theta = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 10);
  for (c11_i8 = 0; c11_i8 < 6; c11_i8 = c11_i8 + 1) {
    c11_hoistedGlobal[c11_i8] = (*c11_d_Theta)[c11_i8];
  }

  for (c11_i9 = 0; c11_i9 < 6; c11_i9 = c11_i9 + 1) {
    c11_b_hoistedGlobal[c11_i9] = (*c11_b_Omega)[c11_i9];
  }

  for (c11_i10 = 0; c11_i10 < 9; c11_i10 = c11_i10 + 1) {
    c11_c_hoistedGlobal[c11_i10] = chartInstance->c11_L[c11_i10];
  }

  for (c11_i11 = 0; c11_i11 < 6; c11_i11 = c11_i11 + 1) {
    c11_Theta[c11_i11] = c11_hoistedGlobal[c11_i11];
  }

  for (c11_i12 = 0; c11_i12 < 6; c11_i12 = c11_i12 + 1) {
    c11_Omega[c11_i12] = c11_b_hoistedGlobal[c11_i12];
  }

  for (c11_i13 = 0; c11_i13 < 9; c11_i13 = c11_i13 + 1) {
    c11_b_L[c11_i13] = c11_c_hoistedGlobal[c11_i13];
  }

  sf_debug_symbol_scope_push_eml(0U, 10U, 10U, c11_sv0, c11_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c11_EndVW, c11_c_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c11_gd, c11_e_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c11_EndW, c11_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c11_gd_pos, c11_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c11_nargin, c11_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c11_nargout, c11_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c11_Theta, c11_c_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c11_Omega, c11_c_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c11_b_L, c11_b_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c11_EndVel, c11_sf_marshall, 9U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0, 5);
  for (c11_i14 = 0; c11_i14 < 9; c11_i14 = c11_i14 + 1) {
    c11_c_L[c11_i14] = c11_b_L[c11_i14];
  }

  for (c11_i15 = 0; c11_i15 < 6; c11_i15 = c11_i15 + 1) {
    c11_b_Theta[c11_i15] = c11_Theta[c11_i15];
  }

  c11_spat_Jacobian(chartInstance, c11_c_L, c11_b_Theta, c11_a);
  for (c11_i16 = 0; c11_i16 < 6; c11_i16 = c11_i16 + 1) {
    c11_b[c11_i16] = c11_Omega[c11_i16];
  }

  c11_b_eml_scalar_eg(chartInstance);
  c11_b_eml_scalar_eg(chartInstance);
  for (c11_i17 = 0; c11_i17 < 36; c11_i17 = c11_i17 + 1) {
    c11_A[c11_i17] = c11_a[c11_i17];
  }

  for (c11_i18 = 0; c11_i18 < 6; c11_i18 = c11_i18 + 1) {
    c11_B[c11_i18] = c11_b[c11_i18];
  }

  for (c11_i19 = 0; c11_i19 < 6; c11_i19 = c11_i19 + 1) {
    c11_EndVW[c11_i19] = 0.0;
  }

  for (c11_i20 = 0; c11_i20 < 36; c11_i20 = c11_i20 + 1) {
    c11_b_A[c11_i20] = c11_A[c11_i20];
  }

  for (c11_i21 = 0; c11_i21 < 6; c11_i21 = c11_i21 + 1) {
    c11_b_B[c11_i21] = c11_B[c11_i21];
  }

  for (c11_i22 = 0; c11_i22 < 36; c11_i22 = c11_i22 + 1) {
    c11_c_A[c11_i22] = c11_b_A[c11_i22];
  }

  for (c11_i23 = 0; c11_i23 < 6; c11_i23 = c11_i23 + 1) {
    c11_c_B[c11_i23] = c11_b_B[c11_i23];
  }

  for (c11_i24 = 0; c11_i24 < 6; c11_i24 = c11_i24 + 1) {
    c11_EndVW[c11_i24] = 0.0;
    c11_i25 = 0;
    for (c11_i26 = 0; c11_i26 < 6; c11_i26 = c11_i26 + 1) {
      c11_EndVW[c11_i24] = c11_EndVW[c11_i24] + c11_c_A[c11_i25 + c11_i24] *
        c11_c_B[c11_i26];
      c11_i25 = c11_i25 + 6;
    }
  }

  _SFD_EML_CALL(0, 6);
  for (c11_i27 = 0; c11_i27 < 9; c11_i27 = c11_i27 + 1) {
    c11_d_L[c11_i27] = c11_b_L[c11_i27];
  }

  for (c11_i28 = 0; c11_i28 < 6; c11_i28 = c11_i28 + 1) {
    c11_c_Theta[c11_i28] = c11_Theta[c11_i28];
  }

  c11_fwd_kin(chartInstance, c11_d_L, c11_c_Theta, c11_dv2);
  for (c11_i29 = 0; c11_i29 < 16; c11_i29 = c11_i29 + 1) {
    c11_gd[c11_i29] = c11_dv2[c11_i29];
  }

  _SFD_EML_CALL(0, 7);
  for (c11_i30 = 0; c11_i30 < 3; c11_i30 = c11_i30 + 1) {
    c11_EndW[c11_i30] = c11_EndVW[c11_i30 + 3];
  }

  _SFD_EML_CALL(0, 8);
  for (c11_i31 = 0; c11_i31 < 3; c11_i31 = c11_i31 + 1) {
    c11_gd_pos[c11_i31] = c11_gd[c11_i31 + 12];
  }

  _SFD_EML_CALL(0, 9);
  for (c11_i32 = 0; c11_i32 < 3; c11_i32 = c11_i32 + 1) {
    c11_b_a[c11_i32] = c11_EndW[c11_i32];
  }

  for (c11_i33 = 0; c11_i33 < 3; c11_i33 = c11_i33 + 1) {
    c11_b_b[c11_i33] = c11_gd_pos[c11_i33];
  }

  c11_c_a = c11_b_a[1];
  c11_c_b = c11_b_b[2];
  c11_y = c11_c_a * c11_c_b;
  c11_d_a = c11_b_a[2];
  c11_d_b = c11_b_b[1];
  c11_b_y = c11_d_a * c11_d_b;
  c11_c1 = c11_y - c11_b_y;
  c11_e_a = c11_b_a[2];
  c11_e_b = c11_b_b[0];
  c11_c_y = c11_e_a * c11_e_b;
  c11_f_a = c11_b_a[0];
  c11_f_b = c11_b_b[2];
  c11_d_y = c11_f_a * c11_f_b;
  c11_c2 = c11_c_y - c11_d_y;
  c11_g_a = c11_b_a[0];
  c11_g_b = c11_b_b[1];
  c11_e_y = c11_g_a * c11_g_b;
  c11_h_a = c11_b_a[1];
  c11_h_b = c11_b_b[0];
  c11_f_y = c11_h_a * c11_h_b;
  c11_c3 = c11_e_y - c11_f_y;
  c11_EndVel[0] = c11_c1;
  c11_EndVel[1] = c11_c2;
  c11_EndVel[2] = c11_c3;
  _SFD_EML_CALL(0, -9);
  sf_debug_symbol_scope_pop();
  for (c11_i34 = 0; c11_i34 < 3; c11_i34 = c11_i34 + 1) {
    (*c11_b_EndVel)[c11_i34] = c11_EndVel[c11_i34];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10);
}

static void compInitSubchartSimstructsFcn_c11_EulerDynJointCon
  (SFc11_EulerDynJointConInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c11_chartNumber, 0U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m"));
  _SFD_SCRIPT_TRANSLATION(c11_chartNumber, 1U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/fwd_kin.m"));
}

static void c11_spat_Jacobian(SFc11_EulerDynJointConInstanceStruct
  *chartInstance, real_T c11_in1[9], real_T c11_in2[6], real_T
  c11_b_spat_Jacobian[36])
{
  uint32_T c11_debug_family_var_map[64];
  real_T c11_A1;
  real_T c11_A2;
  real_T c11_A3;
  real_T c11_A4;
  real_T c11_A5;
  real_T c11_L1;
  real_T c11_L2;
  real_T c11_L3;
  real_T c11_L4;
  real_T c11_L5;
  real_T c11_t2;
  real_T c11_t3;
  real_T c11_t4;
  real_T c11_t5;
  real_T c11_t6;
  real_T c11_t7;
  real_T c11_t8;
  real_T c11_t9;
  real_T c11_t10;
  real_T c11_t11;
  real_T c11_t12;
  real_T c11_t13;
  real_T c11_t14;
  real_T c11_t15;
  real_T c11_t16;
  real_T c11_t17;
  real_T c11_t18;
  real_T c11_t19;
  real_T c11_t20;
  real_T c11_t21;
  real_T c11_t22;
  real_T c11_t23;
  real_T c11_t24;
  real_T c11_t25;
  real_T c11_t26;
  real_T c11_t27;
  real_T c11_t28;
  real_T c11_t29;
  real_T c11_t30;
  real_T c11_t31;
  real_T c11_t32;
  real_T c11_t33;
  real_T c11_t34;
  real_T c11_t35;
  real_T c11_t36;
  real_T c11_t37;
  real_T c11_t38;
  real_T c11_t47;
  real_T c11_t39;
  real_T c11_t40;
  real_T c11_t41;
  real_T c11_t42;
  real_T c11_t43;
  real_T c11_t44;
  real_T c11_t45;
  real_T c11_t46;
  real_T c11_t48;
  real_T c11_t49;
  real_T c11_t50;
  real_T c11_nargin = 2.0;
  real_T c11_nargout = 1.0;
  real_T c11_x;
  real_T c11_b_x;
  real_T c11_c_x;
  real_T c11_d_x;
  real_T c11_e_x;
  real_T c11_f_x;
  real_T c11_g_x;
  real_T c11_h_x;
  real_T c11_i_x;
  real_T c11_j_x;
  real_T c11_k_x;
  real_T c11_l_x;
  real_T c11_m_x;
  real_T c11_n_x;
  real_T c11_o_x;
  real_T c11_p_x;
  real_T c11_q_x;
  real_T c11_r_x;
  real_T c11_s_x;
  real_T c11_t_x;
  real_T c11_u_x;
  real_T c11_v_x;
  real_T c11_w_x;
  real_T c11_x_x;
  real_T c11_a;
  real_T c11_ak;
  real_T c11_y;
  real_T c11_y_x[36];
  int32_T c11_k;
  int32_T c11_b_k;
  sf_debug_symbol_scope_push_eml(0U, 64U, 64U, c11_b_debug_family_names,
    c11_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c11_A1, c11_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c11_A2, c11_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c11_A3, c11_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c11_A4, c11_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c11_A5, c11_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c11_L1, c11_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c11_L2, c11_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c11_L3, c11_d_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c11_L4, c11_d_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c11_L5, c11_d_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&c11_t2, c11_d_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&c11_t3, c11_d_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c11_t4, c11_d_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(&c11_t5, c11_d_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(&c11_t6, c11_d_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(&c11_t7, c11_d_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(&c11_t8, c11_d_sf_marshall, 16U);
  sf_debug_symbol_scope_add_eml(&c11_t9, c11_d_sf_marshall, 17U);
  sf_debug_symbol_scope_add_eml(&c11_t10, c11_d_sf_marshall, 18U);
  sf_debug_symbol_scope_add_eml(&c11_t11, c11_d_sf_marshall, 19U);
  sf_debug_symbol_scope_add_eml(&c11_t12, c11_d_sf_marshall, 20U);
  sf_debug_symbol_scope_add_eml(&c11_t13, c11_d_sf_marshall, 21U);
  sf_debug_symbol_scope_add_eml(&c11_t14, c11_d_sf_marshall, 22U);
  sf_debug_symbol_scope_add_eml(&c11_t15, c11_d_sf_marshall, 23U);
  sf_debug_symbol_scope_add_eml(&c11_t16, c11_d_sf_marshall, 24U);
  sf_debug_symbol_scope_add_eml(&c11_t17, c11_d_sf_marshall, 25U);
  sf_debug_symbol_scope_add_eml(&c11_t18, c11_d_sf_marshall, 26U);
  sf_debug_symbol_scope_add_eml(&c11_t19, c11_d_sf_marshall, 27U);
  sf_debug_symbol_scope_add_eml(&c11_t20, c11_d_sf_marshall, 28U);
  sf_debug_symbol_scope_add_eml(&c11_t21, c11_d_sf_marshall, 29U);
  sf_debug_symbol_scope_add_eml(&c11_t22, c11_d_sf_marshall, 30U);
  sf_debug_symbol_scope_add_eml(&c11_t23, c11_d_sf_marshall, 31U);
  sf_debug_symbol_scope_add_eml(&c11_t24, c11_d_sf_marshall, 32U);
  sf_debug_symbol_scope_add_eml(&c11_t25, c11_d_sf_marshall, 33U);
  sf_debug_symbol_scope_add_eml(&c11_t26, c11_d_sf_marshall, 34U);
  sf_debug_symbol_scope_add_eml(&c11_t27, c11_d_sf_marshall, 35U);
  sf_debug_symbol_scope_add_eml(&c11_t28, c11_d_sf_marshall, 36U);
  sf_debug_symbol_scope_add_eml(&c11_t29, c11_d_sf_marshall, 37U);
  sf_debug_symbol_scope_add_eml(&c11_t30, c11_d_sf_marshall, 38U);
  sf_debug_symbol_scope_add_eml(&c11_t31, c11_d_sf_marshall, 39U);
  sf_debug_symbol_scope_add_eml(&c11_t32, c11_d_sf_marshall, 40U);
  sf_debug_symbol_scope_add_eml(&c11_t33, c11_d_sf_marshall, 41U);
  sf_debug_symbol_scope_add_eml(&c11_t34, c11_d_sf_marshall, 42U);
  sf_debug_symbol_scope_add_eml(&c11_t35, c11_d_sf_marshall, 43U);
  sf_debug_symbol_scope_add_eml(&c11_t36, c11_d_sf_marshall, 44U);
  sf_debug_symbol_scope_add_eml(&c11_t37, c11_d_sf_marshall, 45U);
  sf_debug_symbol_scope_add_eml(&c11_t38, c11_d_sf_marshall, 46U);
  sf_debug_symbol_scope_add_eml(&c11_t47, c11_d_sf_marshall, 47U);
  sf_debug_symbol_scope_add_eml(&c11_t39, c11_d_sf_marshall, 48U);
  sf_debug_symbol_scope_add_eml(&c11_t40, c11_d_sf_marshall, 49U);
  sf_debug_symbol_scope_add_eml(&c11_t41, c11_d_sf_marshall, 50U);
  sf_debug_symbol_scope_add_eml(&c11_t42, c11_d_sf_marshall, 51U);
  sf_debug_symbol_scope_add_eml(&c11_t43, c11_d_sf_marshall, 52U);
  sf_debug_symbol_scope_add_eml(&c11_t44, c11_d_sf_marshall, 53U);
  sf_debug_symbol_scope_add_eml(&c11_t45, c11_d_sf_marshall, 54U);
  sf_debug_symbol_scope_add_eml(&c11_t46, c11_d_sf_marshall, 55U);
  sf_debug_symbol_scope_add_eml(&c11_t48, c11_d_sf_marshall, 56U);
  sf_debug_symbol_scope_add_eml(&c11_t49, c11_d_sf_marshall, 57U);
  sf_debug_symbol_scope_add_eml(&c11_t50, c11_d_sf_marshall, 58U);
  sf_debug_symbol_scope_add_eml(&c11_nargin, c11_d_sf_marshall, 59U);
  sf_debug_symbol_scope_add_eml(&c11_nargout, c11_d_sf_marshall, 60U);
  sf_debug_symbol_scope_add_eml(c11_in1, c11_b_sf_marshall, 61U);
  sf_debug_symbol_scope_add_eml(c11_in2, c11_g_sf_marshall, 62U);
  sf_debug_symbol_scope_add_eml(c11_b_spat_Jacobian, c11_f_sf_marshall, 63U);
  CV_SCRIPT_FCN(0, 0);

  /* SPAT_JACOBIAN */
  /*     SPAT_JACOBIAN = SPAT_JACOBIAN(IN1,IN2) */
  /*     This function was generated by the Symbolic Math Toolbox version 5.5. */
  /*     24-Apr-2013 20:41:43 */
  _SFD_SCRIPT_CALL(0, 8);
  c11_A1 = c11_in2[0];
  _SFD_SCRIPT_CALL(0, 9);
  c11_A2 = c11_in2[1];
  _SFD_SCRIPT_CALL(0, 10);
  c11_A3 = c11_in2[2];
  _SFD_SCRIPT_CALL(0, 11);
  c11_A4 = c11_in2[3];
  _SFD_SCRIPT_CALL(0, 12);
  c11_A5 = c11_in2[4];
  _SFD_SCRIPT_CALL(0, 13);
  c11_L1 = c11_in1[0];
  _SFD_SCRIPT_CALL(0, 14);
  c11_L2 = c11_in1[1];
  _SFD_SCRIPT_CALL(0, 15);
  c11_L3 = c11_in1[2];
  _SFD_SCRIPT_CALL(0, 16);
  c11_L4 = c11_in1[3];
  _SFD_SCRIPT_CALL(0, 17);
  c11_L5 = c11_in1[4];
  _SFD_SCRIPT_CALL(0, 18);
  c11_x = c11_A1;
  c11_t2 = c11_x;
  c11_b_x = c11_t2;
  c11_t2 = c11_b_x;
  c11_t2 = muDoubleScalarCos(c11_t2);
  _SFD_SCRIPT_CALL(0, 19);
  c11_t3 = c11_A2 + c11_A3;
  _SFD_SCRIPT_CALL(0, 20);
  c11_c_x = c11_A2;
  c11_t4 = c11_c_x;
  c11_d_x = c11_t4;
  c11_t4 = c11_d_x;
  c11_t4 = muDoubleScalarCos(c11_t4);
  _SFD_SCRIPT_CALL(0, 21);
  c11_e_x = c11_A3;
  c11_t5 = c11_e_x;
  c11_f_x = c11_t5;
  c11_t5 = c11_f_x;
  c11_t5 = muDoubleScalarCos(c11_t5);
  _SFD_SCRIPT_CALL(0, 22);
  c11_g_x = c11_A2;
  c11_t6 = c11_g_x;
  c11_h_x = c11_t6;
  c11_t6 = c11_h_x;
  c11_t6 = muDoubleScalarSin(c11_t6);
  _SFD_SCRIPT_CALL(0, 23);
  c11_i_x = c11_A3;
  c11_t7 = c11_i_x;
  c11_j_x = c11_t7;
  c11_t7 = c11_j_x;
  c11_t7 = muDoubleScalarSin(c11_t7);
  _SFD_SCRIPT_CALL(0, 24);
  c11_t8 = c11_L1 + c11_L3;
  _SFD_SCRIPT_CALL(0, 25);
  c11_t9 = c11_t5 - 1.0;
  _SFD_SCRIPT_CALL(0, 26);
  c11_k_x = c11_A1;
  c11_t10 = c11_k_x;
  c11_l_x = c11_t10;
  c11_t10 = c11_l_x;
  c11_t10 = muDoubleScalarSin(c11_t10);
  _SFD_SCRIPT_CALL(0, 27);
  c11_m_x = c11_t3;
  c11_t11 = c11_m_x;
  c11_n_x = c11_t11;
  c11_t11 = c11_n_x;
  c11_t11 = muDoubleScalarSin(c11_t11);
  _SFD_SCRIPT_CALL(0, 28);
  c11_o_x = c11_A4;
  c11_t12 = c11_o_x;
  c11_p_x = c11_t12;
  c11_t12 = c11_p_x;
  c11_t12 = muDoubleScalarCos(c11_t12);
  _SFD_SCRIPT_CALL(0, 29);
  c11_q_x = c11_t3;
  c11_t13 = c11_q_x;
  c11_r_x = c11_t13;
  c11_t13 = c11_r_x;
  c11_t13 = muDoubleScalarCos(c11_t13);
  _SFD_SCRIPT_CALL(0, 30);
  c11_s_x = c11_A4;
  c11_t14 = c11_s_x;
  c11_t_x = c11_t14;
  c11_t14 = c11_t_x;
  c11_t14 = muDoubleScalarSin(c11_t14);
  _SFD_SCRIPT_CALL(0, 31);
  c11_t15 = (c11_L1 + c11_L3) + c11_L4;
  _SFD_SCRIPT_CALL(0, 32);
  c11_t16 = c11_L2 * c11_t11;
  _SFD_SCRIPT_CALL(0, 33);
  c11_t17 = c11_L3 * c11_t5;
  _SFD_SCRIPT_CALL(0, 34);
  c11_t18 = c11_L1 * c11_t13;
  _SFD_SCRIPT_CALL(0, 35);
  c11_t19 = c11_t12 - 1.0;
  _SFD_SCRIPT_CALL(0, 36);
  c11_u_x = c11_A5;
  c11_t20 = c11_u_x;
  c11_v_x = c11_t20;
  c11_t20 = c11_v_x;
  c11_t20 = muDoubleScalarCos(c11_t20);
  _SFD_SCRIPT_CALL(0, 37);
  c11_t21 = c11_L2 + c11_L5;
  _SFD_SCRIPT_CALL(0, 38);
  c11_w_x = c11_A5;
  c11_t22 = c11_w_x;
  c11_x_x = c11_t22;
  c11_t22 = c11_x_x;
  c11_t22 = muDoubleScalarSin(c11_t22);
  _SFD_SCRIPT_CALL(0, 39);
  c11_t23 = c11_t20 - 1.0;
  _SFD_SCRIPT_CALL(0, 40);
  c11_t24 = c11_L2 * c11_t6;
  _SFD_SCRIPT_CALL(0, 41);
  c11_t25 = c11_t4 - 1.0;
  _SFD_SCRIPT_CALL(0, 42);
  c11_t26 = c11_t24 - c11_L1 * c11_t25;
  _SFD_SCRIPT_CALL(0, 43);
  c11_t27 = c11_t2 * c11_t26;
  _SFD_SCRIPT_CALL(0, 44);
  c11_t28 = c11_L2 * c11_t7;
  _SFD_SCRIPT_CALL(0, 45);
  c11_t29 = c11_t2 * c11_t4 * (c11_t28 - c11_t8 * c11_t9);
  _SFD_SCRIPT_CALL(0, 46);
  c11_t30 = c11_t7 * c11_t8;
  _SFD_SCRIPT_CALL(0, 47);
  c11_t31 = c11_L2 * c11_t9;
  _SFD_SCRIPT_CALL(0, 48);
  c11_t32 = c11_t30 + c11_t31;
  _SFD_SCRIPT_CALL(0, 49);
  c11_t33 = c11_t2 * c11_t32 * c11_t6;
  _SFD_SCRIPT_CALL(0, 50);
  c11_t34 = (c11_t27 + c11_t29) + c11_t33;
  _SFD_SCRIPT_CALL(0, 51);
  c11_t35 = c11_L1 * c11_t11;
  _SFD_SCRIPT_CALL(0, 52);
  c11_t36 = c11_L3 * c11_t7;
  _SFD_SCRIPT_CALL(0, 53);
  c11_t37 = ((c11_L2 + c11_t35) + c11_t36) - c11_L2 * c11_t13;
  _SFD_SCRIPT_CALL(0, 54);
  c11_t38 = c11_t10 * c11_t12;
  _SFD_SCRIPT_CALL(0, 55);
  c11_t47 = c11_t11 * c11_t14 * c11_t2;
  _SFD_SCRIPT_CALL(0, 56);
  c11_t39 = c11_t38 - c11_t47;
  _SFD_SCRIPT_CALL(0, 57);
  c11_t40 = c11_L3 * c11_t4;
  _SFD_SCRIPT_CALL(0, 58);
  c11_t41 = c11_L1 + c11_t40;
  _SFD_SCRIPT_CALL(0, 59);
  c11_t42 = ((c11_L4 + c11_t16) + c11_t17) + c11_t18;
  _SFD_SCRIPT_CALL(0, 60);
  c11_t43 = c11_L3 * c11_t6;
  _SFD_SCRIPT_CALL(0, 61);
  c11_t44 = c11_L4 * c11_t11;
  _SFD_SCRIPT_CALL(0, 62);
  c11_t45 = c11_L5 * c11_t13;
  _SFD_SCRIPT_CALL(0, 63);
  c11_t46 = ((c11_L2 + c11_t43) + c11_t44) + c11_t45;
  _SFD_SCRIPT_CALL(0, 64);
  c11_t48 = c11_t10 * c11_t14;
  _SFD_SCRIPT_CALL(0, 65);
  c11_t49 = c11_t11 * c11_t12 * c11_t2;
  _SFD_SCRIPT_CALL(0, 66);
  c11_t50 = c11_t48 + c11_t49;
  _SFD_SCRIPT_CALL(0, 67);
  c11_a = c11_t14;
  c11_eml_scalar_eg(chartInstance);
  c11_ak = c11_a;
  c11_y = muDoubleScalarPower(c11_ak, 2.0);
  c11_y_x[0] = 0.0;
  c11_y_x[1] = 0.0;
  c11_y_x[2] = 0.0;
  c11_y_x[3] = 0.0;
  c11_y_x[4] = 0.0;
  c11_y_x[5] = 1.0;
  c11_y_x[6] = (-c11_L1) * c11_t2;
  c11_y_x[7] = (-c11_L1) * c11_t10;
  c11_y_x[8] = c11_L2;
  c11_y_x[9] = -c11_t10;
  c11_y_x[10] = c11_t2;
  c11_y_x[11] = 0.0;
  c11_y_x[12] = (-c11_t2) * c11_t41;
  c11_y_x[13] = (-c11_t10) * c11_t41;
  c11_y_x[14] = c11_L2 + c11_t43;
  c11_y_x[15] = -c11_t10;
  c11_y_x[16] = c11_t2;
  c11_y_x[17] = 0.0;
  c11_y_x[18] = (-c11_t10) * c11_t42;
  c11_y_x[19] = c11_t2 * c11_t42;
  c11_y_x[20] = 0.0;
  c11_y_x[21] = c11_t13 * c11_t2;
  c11_y_x[22] = c11_t10 * c11_t13;
  c11_y_x[23] = -c11_t11;
  c11_y_x[24] = ((((-c11_t12) * c11_t34 + c11_t21 * c11_t50) + c11_t13 * c11_t2 *
                  (c11_y * c11_t15 + c11_t12 * c11_t15 * c11_t19)) -
                 c11_t13 * c11_t15 * c11_t2) - c11_t10 * c11_t14 * c11_t37;
  c11_y_x[25] = (((((((-c11_L1) * c11_t10 * c11_t12 - c11_L5 * c11_t14 * c11_t2)
                     + c11_L1 * c11_t11 * c11_t14 * c11_t2) - c11_L2 *
                    c11_t13 * c11_t14 * c11_t2) - c11_L4 * c11_t10 * c11_t12 *
                   c11_t13) + c11_L5 * c11_t10 * c11_t11 * c11_t12) - c11_L3 *
                 c11_t10 *
                 c11_t12 * c11_t4) + c11_L3 * c11_t14 * c11_t2 * c11_t7;
  c11_y_x[26] = c11_t12 * c11_t46;
  c11_y_x[27] = (-c11_t38) + c11_t47;
  c11_y_x[28] = c11_t12 * c11_t2 + c11_t10 * c11_t11 * c11_t14;
  c11_y_x[29] = c11_t13 * c11_t14;
  c11_y_x[30] = (((-c11_t20) * ((c11_t10 * (((((-c11_L1) - c11_L3) + c11_t16) +
    c11_t17) + c11_t18) - c11_t10 * c11_t15 * c11_t19) +
    c11_t11 * c11_t14 * c11_t15 * c11_t2) - c11_t15 * c11_t39) - c11_t22 *
                 ((c11_t14 * c11_t34 + c11_t13 * c11_t2 * (c11_t12 * c11_t14
    * c11_t15 - c11_t14 * c11_t15 * c11_t19)) - c11_t10 * c11_t12 * c11_t37)) +
    c11_t39 * (c11_t20 * (c11_t15 * c11_t23 - c11_t21 *
    c11_t22) + c11_t22 * (c11_t15 * c11_t22 + c11_t21 * c11_t23));
  c11_y_x[31] = ((((((((((c11_L4 * c11_t2 * c11_t20 - c11_L1 * c11_t10 * c11_t14
    * c11_t22) + c11_L1 * c11_t13 * c11_t2 * c11_t20) +
                        c11_L2 * c11_t11 * c11_t2 * c11_t20) + c11_L5 * c11_t12 *
                       c11_t2 * c11_t22) + c11_L3 * c11_t2 * c11_t20 * c11_t5) -
                     c11_L1 * c11_t11
                     * c11_t12 * c11_t2 * c11_t22) + c11_L2 * c11_t12 * c11_t13 *
                    c11_t2 * c11_t22) - c11_L4 * c11_t10 * c11_t13 * c11_t14 *
                   c11_t22) +
                  c11_L5 * c11_t10 * c11_t11 * c11_t14 * c11_t22) - c11_L3 *
                 c11_t10 * c11_t14 * c11_t22 * c11_t4) - c11_L3 * c11_t12 *
    c11_t2 *
    c11_t22 * c11_t7;
  c11_y_x[32] = c11_t14 * c11_t22 * c11_t46;
  c11_y_x[33] = (-c11_t22) * c11_t50 + c11_t13 * c11_t2 * c11_t20;
  c11_y_x[34] = c11_t22 * (c11_t14 * c11_t2 - c11_t10 * c11_t11 * c11_t12) +
    c11_t10 * c11_t13 * c11_t20;
  c11_y_x[35] = (-c11_t11) * c11_t20 - c11_t12 * c11_t13 * c11_t22;
  for (c11_k = 1; c11_k < 37; c11_k = c11_k + 1) {
    c11_b_k = c11_k;
    c11_b_spat_Jacobian[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c11_b_k), 1, 36, 1, 0) - 1] = c11_y_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c11_b_k), 1, 36, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, -67);
  sf_debug_symbol_scope_pop();
}

static void c11_eml_scalar_eg(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
}

static void c11_b_eml_scalar_eg(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
}

static void c11_fwd_kin(SFc11_EulerDynJointConInstanceStruct *chartInstance,
  real_T c11_in1[9], real_T c11_in2[6], real_T c11_gst[16
  ])
{
  uint32_T c11_debug_family_var_map[68];
  real_T c11_A1;
  real_T c11_A2;
  real_T c11_A3;
  real_T c11_A4;
  real_T c11_A5;
  real_T c11_A6;
  real_T c11_L1;
  real_T c11_L2;
  real_T c11_L3;
  real_T c11_L4;
  real_T c11_L5;
  real_T c11_L6;
  real_T c11_L7;
  real_T c11_L8;
  real_T c11_L9;
  real_T c11_t2;
  real_T c11_t3;
  real_T c11_t4;
  real_T c11_t5;
  real_T c11_t6;
  real_T c11_t7;
  real_T c11_t8;
  real_T c11_t9;
  real_T c11_t10;
  real_T c11_t11;
  real_T c11_t12;
  real_T c11_t13;
  real_T c11_t14;
  real_T c11_t23;
  real_T c11_t15;
  real_T c11_t16;
  real_T c11_t17;
  real_T c11_t18;
  real_T c11_t19;
  real_T c11_t20;
  real_T c11_t21;
  real_T c11_t22;
  real_T c11_t24;
  real_T c11_t25;
  real_T c11_t26;
  real_T c11_t27;
  real_T c11_t34;
  real_T c11_t28;
  real_T c11_t29;
  real_T c11_t30;
  real_T c11_t31;
  real_T c11_t32;
  real_T c11_t36;
  real_T c11_t33;
  real_T c11_t35;
  real_T c11_t37;
  real_T c11_t38;
  real_T c11_t39;
  real_T c11_t40;
  real_T c11_t41;
  real_T c11_t42;
  real_T c11_t43;
  real_T c11_t44;
  real_T c11_t45;
  real_T c11_t47;
  real_T c11_t46;
  real_T c11_t48;
  real_T c11_t49;
  real_T c11_nargin = 2.0;
  real_T c11_nargout = 1.0;
  real_T c11_x;
  real_T c11_b_x;
  real_T c11_c_x;
  real_T c11_d_x;
  real_T c11_e_x;
  real_T c11_f_x;
  real_T c11_g_x;
  real_T c11_h_x;
  real_T c11_i_x;
  real_T c11_j_x;
  real_T c11_k_x;
  real_T c11_l_x;
  real_T c11_m_x;
  real_T c11_n_x;
  real_T c11_o_x;
  real_T c11_p_x;
  real_T c11_q_x;
  real_T c11_r_x;
  real_T c11_s_x;
  real_T c11_t_x;
  real_T c11_u_x;
  real_T c11_v_x;
  real_T c11_w_x;
  real_T c11_x_x;
  real_T c11_y_x[16];
  int32_T c11_k;
  int32_T c11_b_k;
  sf_debug_symbol_scope_push_eml(0U, 68U, 68U, c11_c_debug_family_names,
    c11_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c11_A1, c11_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c11_A2, c11_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c11_A3, c11_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c11_A4, c11_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c11_A5, c11_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c11_A6, c11_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c11_L1, c11_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c11_L2, c11_d_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c11_L3, c11_d_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c11_L4, c11_d_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&c11_L5, c11_d_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&c11_L6, c11_d_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c11_L7, c11_d_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(&c11_L8, c11_d_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(&c11_L9, c11_d_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(&c11_t2, c11_d_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(&c11_t3, c11_d_sf_marshall, 16U);
  sf_debug_symbol_scope_add_eml(&c11_t4, c11_d_sf_marshall, 17U);
  sf_debug_symbol_scope_add_eml(&c11_t5, c11_d_sf_marshall, 18U);
  sf_debug_symbol_scope_add_eml(&c11_t6, c11_d_sf_marshall, 19U);
  sf_debug_symbol_scope_add_eml(&c11_t7, c11_d_sf_marshall, 20U);
  sf_debug_symbol_scope_add_eml(&c11_t8, c11_d_sf_marshall, 21U);
  sf_debug_symbol_scope_add_eml(&c11_t9, c11_d_sf_marshall, 22U);
  sf_debug_symbol_scope_add_eml(&c11_t10, c11_d_sf_marshall, 23U);
  sf_debug_symbol_scope_add_eml(&c11_t11, c11_d_sf_marshall, 24U);
  sf_debug_symbol_scope_add_eml(&c11_t12, c11_d_sf_marshall, 25U);
  sf_debug_symbol_scope_add_eml(&c11_t13, c11_d_sf_marshall, 26U);
  sf_debug_symbol_scope_add_eml(&c11_t14, c11_d_sf_marshall, 27U);
  sf_debug_symbol_scope_add_eml(&c11_t23, c11_d_sf_marshall, 28U);
  sf_debug_symbol_scope_add_eml(&c11_t15, c11_d_sf_marshall, 29U);
  sf_debug_symbol_scope_add_eml(&c11_t16, c11_d_sf_marshall, 30U);
  sf_debug_symbol_scope_add_eml(&c11_t17, c11_d_sf_marshall, 31U);
  sf_debug_symbol_scope_add_eml(&c11_t18, c11_d_sf_marshall, 32U);
  sf_debug_symbol_scope_add_eml(&c11_t19, c11_d_sf_marshall, 33U);
  sf_debug_symbol_scope_add_eml(&c11_t20, c11_d_sf_marshall, 34U);
  sf_debug_symbol_scope_add_eml(&c11_t21, c11_d_sf_marshall, 35U);
  sf_debug_symbol_scope_add_eml(&c11_t22, c11_d_sf_marshall, 36U);
  sf_debug_symbol_scope_add_eml(&c11_t24, c11_d_sf_marshall, 37U);
  sf_debug_symbol_scope_add_eml(&c11_t25, c11_d_sf_marshall, 38U);
  sf_debug_symbol_scope_add_eml(&c11_t26, c11_d_sf_marshall, 39U);
  sf_debug_symbol_scope_add_eml(&c11_t27, c11_d_sf_marshall, 40U);
  sf_debug_symbol_scope_add_eml(&c11_t34, c11_d_sf_marshall, 41U);
  sf_debug_symbol_scope_add_eml(&c11_t28, c11_d_sf_marshall, 42U);
  sf_debug_symbol_scope_add_eml(&c11_t29, c11_d_sf_marshall, 43U);
  sf_debug_symbol_scope_add_eml(&c11_t30, c11_d_sf_marshall, 44U);
  sf_debug_symbol_scope_add_eml(&c11_t31, c11_d_sf_marshall, 45U);
  sf_debug_symbol_scope_add_eml(&c11_t32, c11_d_sf_marshall, 46U);
  sf_debug_symbol_scope_add_eml(&c11_t36, c11_d_sf_marshall, 47U);
  sf_debug_symbol_scope_add_eml(&c11_t33, c11_d_sf_marshall, 48U);
  sf_debug_symbol_scope_add_eml(&c11_t35, c11_d_sf_marshall, 49U);
  sf_debug_symbol_scope_add_eml(&c11_t37, c11_d_sf_marshall, 50U);
  sf_debug_symbol_scope_add_eml(&c11_t38, c11_d_sf_marshall, 51U);
  sf_debug_symbol_scope_add_eml(&c11_t39, c11_d_sf_marshall, 52U);
  sf_debug_symbol_scope_add_eml(&c11_t40, c11_d_sf_marshall, 53U);
  sf_debug_symbol_scope_add_eml(&c11_t41, c11_d_sf_marshall, 54U);
  sf_debug_symbol_scope_add_eml(&c11_t42, c11_d_sf_marshall, 55U);
  sf_debug_symbol_scope_add_eml(&c11_t43, c11_d_sf_marshall, 56U);
  sf_debug_symbol_scope_add_eml(&c11_t44, c11_d_sf_marshall, 57U);
  sf_debug_symbol_scope_add_eml(&c11_t45, c11_d_sf_marshall, 58U);
  sf_debug_symbol_scope_add_eml(&c11_t47, c11_d_sf_marshall, 59U);
  sf_debug_symbol_scope_add_eml(&c11_t46, c11_d_sf_marshall, 60U);
  sf_debug_symbol_scope_add_eml(&c11_t48, c11_d_sf_marshall, 61U);
  sf_debug_symbol_scope_add_eml(&c11_t49, c11_d_sf_marshall, 62U);
  sf_debug_symbol_scope_add_eml(&c11_nargin, c11_d_sf_marshall, 63U);
  sf_debug_symbol_scope_add_eml(&c11_nargout, c11_d_sf_marshall, 64U);
  sf_debug_symbol_scope_add_eml(c11_in1, c11_b_sf_marshall, 65U);
  sf_debug_symbol_scope_add_eml(c11_in2, c11_g_sf_marshall, 66U);
  sf_debug_symbol_scope_add_eml(c11_gst, c11_e_sf_marshall, 67U);
  CV_SCRIPT_FCN(1, 0);

  /* FWD_KIN */
  /*     GST = FWD_KIN(IN1,IN2) */
  /*     This function was generated by the Symbolic Math Toolbox version 5.5. */
  /*     24-Apr-2013 12:49:18 */
  _SFD_SCRIPT_CALL(1, 8);
  c11_A1 = c11_in2[0];
  _SFD_SCRIPT_CALL(1, 9);
  c11_A2 = c11_in2[1];
  _SFD_SCRIPT_CALL(1, 10);
  c11_A3 = c11_in2[2];
  _SFD_SCRIPT_CALL(1, 11);
  c11_A4 = c11_in2[3];
  _SFD_SCRIPT_CALL(1, 12);
  c11_A5 = c11_in2[4];
  _SFD_SCRIPT_CALL(1, 13);
  c11_A6 = c11_in2[5];
  _SFD_SCRIPT_CALL(1, 14);
  c11_L1 = c11_in1[0];
  _SFD_SCRIPT_CALL(1, 15);
  c11_L2 = c11_in1[1];
  _SFD_SCRIPT_CALL(1, 16);
  c11_L3 = c11_in1[2];
  _SFD_SCRIPT_CALL(1, 17);
  c11_L4 = c11_in1[3];
  _SFD_SCRIPT_CALL(1, 18);
  c11_L5 = c11_in1[4];
  _SFD_SCRIPT_CALL(1, 19);
  c11_L6 = c11_in1[5];
  _SFD_SCRIPT_CALL(1, 20);
  c11_L7 = c11_in1[6];
  _SFD_SCRIPT_CALL(1, 21);
  c11_L8 = c11_in1[7];
  _SFD_SCRIPT_CALL(1, 22);
  c11_L9 = c11_in1[8];
  _SFD_SCRIPT_CALL(1, 23);
  c11_x = c11_A1;
  c11_t2 = c11_x;
  c11_b_x = c11_t2;
  c11_t2 = c11_b_x;
  c11_t2 = muDoubleScalarCos(c11_t2);
  _SFD_SCRIPT_CALL(1, 24);
  c11_c_x = c11_A2;
  c11_t3 = c11_c_x;
  c11_d_x = c11_t3;
  c11_t3 = c11_d_x;
  c11_t3 = muDoubleScalarCos(c11_t3);
  _SFD_SCRIPT_CALL(1, 25);
  c11_e_x = c11_A3;
  c11_t4 = c11_e_x;
  c11_f_x = c11_t4;
  c11_t4 = c11_f_x;
  c11_t4 = muDoubleScalarSin(c11_t4);
  _SFD_SCRIPT_CALL(1, 26);
  c11_g_x = c11_A3;
  c11_t5 = c11_g_x;
  c11_h_x = c11_t5;
  c11_t5 = c11_h_x;
  c11_t5 = muDoubleScalarCos(c11_t5);
  _SFD_SCRIPT_CALL(1, 27);
  c11_i_x = c11_A2;
  c11_t6 = c11_i_x;
  c11_j_x = c11_t6;
  c11_t6 = c11_j_x;
  c11_t6 = muDoubleScalarSin(c11_t6);
  _SFD_SCRIPT_CALL(1, 28);
  c11_k_x = c11_A4;
  c11_t7 = c11_k_x;
  c11_l_x = c11_t7;
  c11_t7 = c11_l_x;
  c11_t7 = muDoubleScalarSin(c11_t7);
  _SFD_SCRIPT_CALL(1, 29);
  c11_t8 = c11_t2 * c11_t3 * c11_t4;
  _SFD_SCRIPT_CALL(1, 30);
  c11_t9 = c11_t2 * c11_t5 * c11_t6;
  _SFD_SCRIPT_CALL(1, 31);
  c11_t10 = c11_t8 + c11_t9;
  _SFD_SCRIPT_CALL(1, 32);
  c11_m_x = c11_A4;
  c11_t11 = c11_m_x;
  c11_n_x = c11_t11;
  c11_t11 = c11_n_x;
  c11_t11 = muDoubleScalarCos(c11_t11);
  _SFD_SCRIPT_CALL(1, 33);
  c11_o_x = c11_A1;
  c11_t12 = c11_o_x;
  c11_p_x = c11_t12;
  c11_t12 = c11_p_x;
  c11_t12 = muDoubleScalarSin(c11_t12);
  _SFD_SCRIPT_CALL(1, 34);
  c11_q_x = c11_A5;
  c11_t13 = c11_q_x;
  c11_r_x = c11_t13;
  c11_t13 = c11_r_x;
  c11_t13 = muDoubleScalarSin(c11_t13);
  _SFD_SCRIPT_CALL(1, 35);
  c11_t14 = c11_t2 * c11_t3 * c11_t5;
  _SFD_SCRIPT_CALL(1, 36);
  c11_t23 = c11_t2 * c11_t4 * c11_t6;
  _SFD_SCRIPT_CALL(1, 37);
  c11_t15 = c11_t14 - c11_t23;
  _SFD_SCRIPT_CALL(1, 38);
  c11_s_x = c11_A5;
  c11_t16 = c11_s_x;
  c11_t_x = c11_t16;
  c11_t16 = c11_t_x;
  c11_t16 = muDoubleScalarCos(c11_t16);
  _SFD_SCRIPT_CALL(1, 39);
  c11_t17 = c11_t10 * c11_t11;
  _SFD_SCRIPT_CALL(1, 40);
  c11_t18 = c11_t12 * c11_t7;
  _SFD_SCRIPT_CALL(1, 41);
  c11_t19 = c11_t17 + c11_t18;
  _SFD_SCRIPT_CALL(1, 42);
  c11_u_x = c11_A6;
  c11_t20 = c11_u_x;
  c11_v_x = c11_t20;
  c11_t20 = c11_v_x;
  c11_t20 = muDoubleScalarSin(c11_t20);
  _SFD_SCRIPT_CALL(1, 43);
  c11_t21 = c11_t11 * c11_t12;
  _SFD_SCRIPT_CALL(1, 44);
  c11_w_x = c11_A6;
  c11_t22 = c11_w_x;
  c11_x_x = c11_t22;
  c11_t22 = c11_x_x;
  c11_t22 = muDoubleScalarCos(c11_t22);
  _SFD_SCRIPT_CALL(1, 45);
  c11_t24 = c11_t13 * c11_t15;
  _SFD_SCRIPT_CALL(1, 46);
  c11_t25 = c11_t16 * c11_t19;
  _SFD_SCRIPT_CALL(1, 47);
  c11_t26 = c11_t24 + c11_t25;
  _SFD_SCRIPT_CALL(1, 48);
  c11_t27 = c11_t12 * c11_t3 * c11_t5;
  _SFD_SCRIPT_CALL(1, 49);
  c11_t34 = c11_t12 * c11_t4 * c11_t6;
  _SFD_SCRIPT_CALL(1, 50);
  c11_t28 = c11_t27 - c11_t34;
  _SFD_SCRIPT_CALL(1, 51);
  c11_t29 = c11_t12 * c11_t3 * c11_t4;
  _SFD_SCRIPT_CALL(1, 52);
  c11_t30 = c11_t12 * c11_t5 * c11_t6;
  _SFD_SCRIPT_CALL(1, 53);
  c11_t31 = c11_t29 + c11_t30;
  _SFD_SCRIPT_CALL(1, 54);
  c11_t32 = c11_t11 * c11_t31;
  _SFD_SCRIPT_CALL(1, 55);
  c11_t36 = c11_t2 * c11_t7;
  _SFD_SCRIPT_CALL(1, 56);
  c11_t33 = c11_t32 - c11_t36;
  _SFD_SCRIPT_CALL(1, 57);
  c11_t35 = c11_t13 * c11_t28;
  _SFD_SCRIPT_CALL(1, 58);
  c11_t37 = c11_t16 * c11_t33;
  _SFD_SCRIPT_CALL(1, 59);
  c11_t38 = c11_t35 + c11_t37;
  _SFD_SCRIPT_CALL(1, 60);
  c11_t39 = c11_t31 * c11_t7;
  _SFD_SCRIPT_CALL(1, 61);
  c11_t40 = c11_t11 * c11_t2;
  _SFD_SCRIPT_CALL(1, 62);
  c11_t41 = c11_t39 + c11_t40;
  _SFD_SCRIPT_CALL(1, 63);
  c11_t42 = c11_t3 * c11_t4;
  _SFD_SCRIPT_CALL(1, 64);
  c11_t43 = c11_t5 * c11_t6;
  _SFD_SCRIPT_CALL(1, 65);
  c11_t44 = c11_t42 + c11_t43;
  _SFD_SCRIPT_CALL(1, 66);
  c11_t45 = c11_t3 * c11_t5;
  _SFD_SCRIPT_CALL(1, 67);
  c11_t47 = c11_t4 * c11_t6;
  _SFD_SCRIPT_CALL(1, 68);
  c11_t46 = c11_t45 - c11_t47;
  _SFD_SCRIPT_CALL(1, 69);
  c11_t48 = c11_t13 * c11_t44;
  _SFD_SCRIPT_CALL(1, 70);
  c11_t49 = c11_t48 - c11_t11 * c11_t16 * c11_t46;
  _SFD_SCRIPT_CALL(1, 71);
  c11_y_x[0] = c11_t15 * c11_t16 - c11_t13 * c11_t19;
  c11_y_x[1] = c11_t16 * c11_t28 - c11_t13 * c11_t33;
  c11_y_x[2] = (-c11_t16) * c11_t44 - c11_t11 * c11_t13 * c11_t46;
  c11_y_x[3] = 0.0;
  c11_y_x[4] = c11_t20 * c11_t26 - c11_t22 * (c11_t21 - c11_t10 * c11_t7);
  c11_y_x[5] = c11_t20 * c11_t38 + c11_t22 * c11_t41;
  c11_y_x[6] = (-c11_t20) * c11_t49 + c11_t22 * c11_t46 * c11_t7;
  c11_y_x[7] = 0.0;
  c11_y_x[8] = c11_t22 * c11_t26 + c11_t20 * (c11_t21 - c11_t10 * c11_t7);
  c11_y_x[9] = c11_t22 * c11_t38 - c11_t20 * c11_t41;
  c11_y_x[10] = (-c11_t22) * c11_t49 - c11_t20 * c11_t46 * c11_t7;
  c11_y_x[11] = 0.0;
  c11_y_x[12] = ((((((((((((((((((((((((((((((c11_L2 * c11_t2 + c11_L3 * c11_t2 *
    c11_t6) - c11_L8 * c11_t11 * c11_t12 * c11_t22) +
    c11_L4 * c11_t2 * c11_t3 * c11_t4) + c11_L9 * c11_t11 * c11_t12 * c11_t20) +
    c11_L5 * c11_t2 * c11_t3 * c11_t5) - c11_L6 * c11_t12
    * c11_t13 * c11_t7) - c11_L7 * c11_t12 * c11_t13 * c11_t7) + c11_L4 * c11_t2
    * c11_t5 * c11_t6) - c11_L5 * c11_t2 * c11_t4 * c11_t6
    ) + c11_L6 * c11_t16 * c11_t2 * c11_t3 * c11_t5) + c11_L7 * c11_t16 * c11_t2
    * c11_t3 * c11_t5) - c11_L6 * c11_t16 * c11_t2 * c11_t4
    * c11_t6) + c11_L8 * c11_t12 * c11_t16 * c11_t20 * c11_t7) - c11_L7 *
    c11_t16 * c11_t2 * c11_t4 * c11_t6) + c11_L9 * c11_t12 *
    c11_t16 * c11_t22 * c11_t7) - c11_L6 * c11_t11 * c11_t13 * c11_t2 * c11_t3 *
    c11_t4) - c11_L7 * c11_t11 * c11_t13 * c11_t2 * c11_t3
    * c11_t4) + c11_L8 * c11_t13 * c11_t2 * c11_t20 * c11_t3 * c11_t5) - c11_L6 *
    c11_t11 * c11_t13 * c11_t2 * c11_t5 * c11_t6) -
    c11_L7 * c11_t11 * c11_t13 * c11_t2 * c11_t5 * c11_t6) + c11_L9 * c11_t13 *
    c11_t2 * c11_t22 * c11_t3 * c11_t5) - c11_L8 * c11_t13
    * c11_t2 * c11_t20 * c11_t4 * c11_t6) - c11_L9 * c11_t13 * c11_t2 * c11_t22 *
                        c11_t4 * c11_t6) + c11_L8 * c11_t2 * c11_t22 * c11_t3
                       * c11_t4 * c11_t7) - c11_L9 * c11_t2 * c11_t20 * c11_t3 *
                      c11_t4 * c11_t7) + c11_L8 * c11_t2 * c11_t22 * c11_t5 *
                     c11_t6 * c11_t7)
                    - c11_L9 * c11_t2 * c11_t20 * c11_t5 * c11_t6 * c11_t7) +
                   c11_L8 * c11_t11 * c11_t16 * c11_t2 * c11_t20 * c11_t3 *
                   c11_t4) + c11_L9
                  * c11_t11 * c11_t16 * c11_t2 * c11_t22 * c11_t3 * c11_t4) +
                 c11_L8 * c11_t11 * c11_t16 * c11_t2 * c11_t20 * c11_t5 * c11_t6)
    +
    c11_L9 * c11_t11 * c11_t16 * c11_t2 * c11_t22 * c11_t5 * c11_t6;
  c11_y_x[13] = ((((((((((((((((((((((((((((((c11_L2 * c11_t12 + c11_L3 *
    c11_t12 * c11_t6) + c11_L4 * c11_t12 * c11_t3 * c11_t4) +
    c11_L8 * c11_t11 * c11_t2 * c11_t22) + c11_L5 * c11_t12 * c11_t3 * c11_t5) -
    c11_L9 * c11_t11 * c11_t2 * c11_t20) + c11_L4 * c11_t12
    * c11_t5 * c11_t6) - c11_L5 * c11_t12 * c11_t4 * c11_t6) + c11_L6 * c11_t13 *
    c11_t2 * c11_t7) + c11_L7 * c11_t13 * c11_t2 * c11_t7
    ) + c11_L6 * c11_t12 * c11_t16 * c11_t3 * c11_t5) + c11_L7 * c11_t12 *
    c11_t16 * c11_t3 * c11_t5) - c11_L6 * c11_t12 * c11_t16 *
    c11_t4 * c11_t6) - c11_L7 * c11_t12 * c11_t16 * c11_t4 * c11_t6) - c11_L8 *
    c11_t16 * c11_t2 * c11_t20 * c11_t7) - c11_L9 * c11_t16
    * c11_t2 * c11_t22 * c11_t7) - c11_L6 * c11_t11 * c11_t12 * c11_t13 * c11_t3
    * c11_t4) - c11_L7 * c11_t11 * c11_t12 * c11_t13 *
    c11_t3 * c11_t4) + c11_L8 * c11_t12 * c11_t13 * c11_t20 * c11_t3 * c11_t5) -
    c11_L6 * c11_t11 * c11_t12 * c11_t13 * c11_t5 * c11_t6)
    - c11_L7 * c11_t11 * c11_t12 * c11_t13 * c11_t5 * c11_t6) + c11_L9 * c11_t12
    * c11_t13 * c11_t22 * c11_t3 * c11_t5) - c11_L8 *
    c11_t12 * c11_t13 * c11_t20 * c11_t4 * c11_t6) - c11_L9 * c11_t12 * c11_t13 *
                        c11_t22 * c11_t4 * c11_t6) + c11_L8 * c11_t12 *
                       c11_t22 * c11_t3 * c11_t4 * c11_t7) - c11_L9 * c11_t12 *
                      c11_t20 * c11_t3 * c11_t4 * c11_t7) + c11_L8 * c11_t12 *
                     c11_t22 * c11_t5
                     * c11_t6 * c11_t7) - c11_L9 * c11_t12 * c11_t20 * c11_t5 *
                    c11_t6 * c11_t7) + c11_L8 * c11_t11 * c11_t12 * c11_t16 *
                   c11_t20 *
                   c11_t3 * c11_t4) + c11_L9 * c11_t11 * c11_t12 * c11_t16 *
                  c11_t22 * c11_t3 * c11_t4) + c11_L8 * c11_t11 * c11_t12 *
                 c11_t16 *
                 c11_t20 * c11_t5 * c11_t6) + c11_L9 * c11_t11 * c11_t12 *
    c11_t16 * c11_t22 * c11_t5 * c11_t6;
  c11_y_x[14] = ((((((((((((((((((((((((c11_L1 + c11_L3 * c11_t3) + c11_L4 *
    c11_t3 * c11_t5) - c11_L5 * c11_t3 * c11_t4) - c11_L4 *
    c11_t4 * c11_t6) - c11_L5 * c11_t5 * c11_t6) - c11_L6 * c11_t16 * c11_t3 *
    c11_t4) - c11_L7 * c11_t16 * c11_t3 * c11_t4) - c11_L6 *
    c11_t16 * c11_t5 * c11_t6) - c11_L7 * c11_t16 * c11_t5 * c11_t6) - c11_L6 *
    c11_t11 * c11_t13 * c11_t3 * c11_t5) - c11_L7 * c11_t11
    * c11_t13 * c11_t3 * c11_t5) - c11_L8 * c11_t13 * c11_t20 * c11_t3 * c11_t4)
    + c11_L6 * c11_t11 * c11_t13 * c11_t4 * c11_t6) +
    c11_L7 * c11_t11 * c11_t13 * c11_t4 * c11_t6) - c11_L9 * c11_t13 * c11_t22 *
    c11_t3 * c11_t4) - c11_L8 * c11_t13 * c11_t20 * c11_t5
    * c11_t6) - c11_L9 * c11_t13 * c11_t22 * c11_t5 * c11_t6) + c11_L8 * c11_t22
                       * c11_t3 * c11_t5 * c11_t7) - c11_L9 * c11_t20 *
                      c11_t3 * c11_t5 * c11_t7) - c11_L8 * c11_t22 * c11_t4 *
                     c11_t6 * c11_t7) + c11_L9 * c11_t20 * c11_t4 * c11_t6 *
                    c11_t7) + c11_L8 *
                   c11_t11 * c11_t16 * c11_t20 * c11_t3 * c11_t5) + c11_L9 *
                  c11_t11 * c11_t16 * c11_t22 * c11_t3 * c11_t5) - c11_L8 *
                 c11_t11 *
                 c11_t16 * c11_t20 * c11_t4 * c11_t6) - c11_L9 * c11_t11 *
    c11_t16 * c11_t22 * c11_t4 * c11_t6;
  c11_y_x[15] = 1.0;
  for (c11_k = 1; c11_k < 17; c11_k = c11_k + 1) {
    c11_b_k = c11_k;
    c11_gst[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c11_b_k), 1, 16, 1, 0) - 1] = c11_y_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c11_b_k), 1, 16, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(1, -71);
  sf_debug_symbol_scope_pop();
}

static const mxArray *c11_sf_marshall(void *chartInstanceVoid, void *c11_u)
{
  const mxArray *c11_y = NULL;
  int32_T c11_i35;
  real_T c11_b_u[3];
  int32_T c11_i36;
  real_T c11_c_u[3];
  const mxArray *c11_b_y = NULL;
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)chartInstanceVoid;
  c11_y = NULL;
  for (c11_i35 = 0; c11_i35 < 3; c11_i35 = c11_i35 + 1) {
    c11_b_u[c11_i35] = (*((real_T (*)[3])c11_u))[c11_i35];
  }

  for (c11_i36 = 0; c11_i36 < 3; c11_i36 = c11_i36 + 1) {
    c11_c_u[c11_i36] = c11_b_u[c11_i36];
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_c_u, 0, 0U, 1U, 0U, 1, 3));
  sf_mex_assign(&c11_y, c11_b_y);
  return c11_y;
}

static const mxArray *c11_b_sf_marshall(void *chartInstanceVoid, void *c11_u)
{
  const mxArray *c11_y = NULL;
  int32_T c11_i37;
  real_T c11_b_u[9];
  int32_T c11_i38;
  real_T c11_c_u[9];
  const mxArray *c11_b_y = NULL;
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)chartInstanceVoid;
  c11_y = NULL;
  for (c11_i37 = 0; c11_i37 < 9; c11_i37 = c11_i37 + 1) {
    c11_b_u[c11_i37] = (*((real_T (*)[9])c11_u))[c11_i37];
  }

  for (c11_i38 = 0; c11_i38 < 9; c11_i38 = c11_i38 + 1) {
    c11_c_u[c11_i38] = c11_b_u[c11_i38];
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_c_u, 0, 0U, 1U, 0U, 2, 1, 9));
  sf_mex_assign(&c11_y, c11_b_y);
  return c11_y;
}

static const mxArray *c11_c_sf_marshall(void *chartInstanceVoid, void *c11_u)
{
  const mxArray *c11_y = NULL;
  int32_T c11_i39;
  real_T c11_b_u[6];
  int32_T c11_i40;
  real_T c11_c_u[6];
  const mxArray *c11_b_y = NULL;
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)chartInstanceVoid;
  c11_y = NULL;
  for (c11_i39 = 0; c11_i39 < 6; c11_i39 = c11_i39 + 1) {
    c11_b_u[c11_i39] = (*((real_T (*)[6])c11_u))[c11_i39];
  }

  for (c11_i40 = 0; c11_i40 < 6; c11_i40 = c11_i40 + 1) {
    c11_c_u[c11_i40] = c11_b_u[c11_i40];
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_c_u, 0, 0U, 1U, 0U, 1, 6));
  sf_mex_assign(&c11_y, c11_b_y);
  return c11_y;
}

static const mxArray *c11_d_sf_marshall(void *chartInstanceVoid, void *c11_u)
{
  const mxArray *c11_y = NULL;
  real_T c11_b_u;
  const mxArray *c11_b_y = NULL;
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)chartInstanceVoid;
  c11_y = NULL;
  c11_b_u = *((real_T *)c11_u);
  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", &c11_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c11_y, c11_b_y);
  return c11_y;
}

static const mxArray *c11_e_sf_marshall(void *chartInstanceVoid, void *c11_u)
{
  const mxArray *c11_y = NULL;
  int32_T c11_i41;
  int32_T c11_i42;
  int32_T c11_i43;
  real_T c11_b_u[16];
  int32_T c11_i44;
  int32_T c11_i45;
  int32_T c11_i46;
  real_T c11_c_u[16];
  const mxArray *c11_b_y = NULL;
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)chartInstanceVoid;
  c11_y = NULL;
  c11_i41 = 0;
  for (c11_i42 = 0; c11_i42 < 4; c11_i42 = c11_i42 + 1) {
    for (c11_i43 = 0; c11_i43 < 4; c11_i43 = c11_i43 + 1) {
      c11_b_u[c11_i43 + c11_i41] = (*((real_T (*)[16])c11_u))[c11_i43 + c11_i41];
    }

    c11_i41 = c11_i41 + 4;
  }

  c11_i44 = 0;
  for (c11_i45 = 0; c11_i45 < 4; c11_i45 = c11_i45 + 1) {
    for (c11_i46 = 0; c11_i46 < 4; c11_i46 = c11_i46 + 1) {
      c11_c_u[c11_i46 + c11_i44] = c11_b_u[c11_i46 + c11_i44];
    }

    c11_i44 = c11_i44 + 4;
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_c_u, 0, 0U, 1U, 0U, 2, 4, 4));
  sf_mex_assign(&c11_y, c11_b_y);
  return c11_y;
}

static const mxArray *c11_f_sf_marshall(void *chartInstanceVoid, void *c11_u)
{
  const mxArray *c11_y = NULL;
  int32_T c11_i47;
  int32_T c11_i48;
  int32_T c11_i49;
  real_T c11_b_u[36];
  int32_T c11_i50;
  int32_T c11_i51;
  int32_T c11_i52;
  real_T c11_c_u[36];
  const mxArray *c11_b_y = NULL;
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)chartInstanceVoid;
  c11_y = NULL;
  c11_i47 = 0;
  for (c11_i48 = 0; c11_i48 < 6; c11_i48 = c11_i48 + 1) {
    for (c11_i49 = 0; c11_i49 < 6; c11_i49 = c11_i49 + 1) {
      c11_b_u[c11_i49 + c11_i47] = (*((real_T (*)[36])c11_u))[c11_i49 + c11_i47];
    }

    c11_i47 = c11_i47 + 6;
  }

  c11_i50 = 0;
  for (c11_i51 = 0; c11_i51 < 6; c11_i51 = c11_i51 + 1) {
    for (c11_i52 = 0; c11_i52 < 6; c11_i52 = c11_i52 + 1) {
      c11_c_u[c11_i52 + c11_i50] = c11_b_u[c11_i52 + c11_i50];
    }

    c11_i50 = c11_i50 + 6;
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_c_u, 0, 0U, 1U, 0U, 2, 6, 6));
  sf_mex_assign(&c11_y, c11_b_y);
  return c11_y;
}

static const mxArray *c11_g_sf_marshall(void *chartInstanceVoid, void *c11_u)
{
  const mxArray *c11_y = NULL;
  int32_T c11_i53;
  real_T c11_b_u[6];
  int32_T c11_i54;
  real_T c11_c_u[6];
  const mxArray *c11_b_y = NULL;
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)chartInstanceVoid;
  c11_y = NULL;
  for (c11_i53 = 0; c11_i53 < 6; c11_i53 = c11_i53 + 1) {
    c11_b_u[c11_i53] = (*((real_T (*)[6])c11_u))[c11_i53];
  }

  for (c11_i54 = 0; c11_i54 < 6; c11_i54 = c11_i54 + 1) {
    c11_c_u[c11_i54] = c11_b_u[c11_i54];
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_c_u, 0, 0U, 1U, 0U, 2, 1, 6));
  sf_mex_assign(&c11_y, c11_b_y);
  return c11_y;
}

const mxArray *sf_c11_EulerDynJointCon_get_eml_resolved_functions_info(void)
{
  const mxArray *c11_nameCaptureInfo = NULL;
  c11_ResolvedFunctionInfo c11_info[59];
  const mxArray *c11_m0 = NULL;
  int32_T c11_i55;
  c11_ResolvedFunctionInfo *c11_r0;
  c11_nameCaptureInfo = NULL;
  c11_info_helper(c11_info);
  sf_mex_assign(&c11_m0, sf_mex_createstruct("nameCaptureInfo", 1, 59));
  for (c11_i55 = 0; c11_i55 < 59; c11_i55 = c11_i55 + 1) {
    c11_r0 = &c11_info[c11_i55];
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", c11_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c11_r0->context)), "context"
                    , "nameCaptureInfo", c11_i55);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", c11_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c11_r0->name)), "name",
                    "nameCaptureInfo", c11_i55);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo",
      c11_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c11_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c11_i55);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", c11_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c11_r0->resolved)),
                    "resolved", "nameCaptureInfo", c11_i55);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", &c11_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c11_i55);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", &c11_r0->fileTime1,
      7, 0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo",
                    c11_i55);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", &c11_r0->fileTime2,
      7, 0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo",
                    c11_i55);
  }

  sf_mex_assign(&c11_nameCaptureInfo, c11_m0);
  return c11_nameCaptureInfo;
}

static void c11_info_helper(c11_ResolvedFunctionInfo c11_info[59])
{
  c11_info[0].context = "";
  c11_info[0].name = "ctranspose";
  c11_info[0].dominantType = "double";
  c11_info[0].resolved = "[B]ctranspose";
  c11_info[0].fileLength = 0U;
  c11_info[0].fileTime1 = 0U;
  c11_info[0].fileTime2 = 0U;
  c11_info[1].context = "";
  c11_info[1].name = "spat_Jacobian";
  c11_info[1].dominantType = "double";
  c11_info[1].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[1].fileLength = 2169U;
  c11_info[1].fileTime1 = 1366807304U;
  c11_info[1].fileTime2 = 0U;
  c11_info[2].context = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[2].name = "cos";
  c11_info[2].dominantType = "double";
  c11_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c11_info[2].fileLength = 324U;
  c11_info[2].fileTime1 = 1203422750U;
  c11_info[2].fileTime2 = 0U;
  c11_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c11_info[3].name = "nargin";
  c11_info[3].dominantType = "";
  c11_info[3].resolved = "[B]nargin";
  c11_info[3].fileLength = 0U;
  c11_info[3].fileTime1 = 0U;
  c11_info[3].fileTime2 = 0U;
  c11_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c11_info[4].name = "gt";
  c11_info[4].dominantType = "double";
  c11_info[4].resolved = "[B]gt";
  c11_info[4].fileLength = 0U;
  c11_info[4].fileTime1 = 0U;
  c11_info[4].fileTime2 = 0U;
  c11_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c11_info[5].name = "isa";
  c11_info[5].dominantType = "double";
  c11_info[5].resolved = "[B]isa";
  c11_info[5].fileLength = 0U;
  c11_info[5].fileTime1 = 0U;
  c11_info[5].fileTime2 = 0U;
  c11_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c11_info[6].name = "eml_scalar_cos";
  c11_info[6].dominantType = "double";
  c11_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c11_info[6].fileLength = 602U;
  c11_info[6].fileTime1 = 1209309186U;
  c11_info[6].fileTime2 = 0U;
  c11_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c11_info[7].name = "isreal";
  c11_info[7].dominantType = "double";
  c11_info[7].resolved = "[B]isreal";
  c11_info[7].fileLength = 0U;
  c11_info[7].fileTime1 = 0U;
  c11_info[7].fileTime2 = 0U;
  c11_info[8].context = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[8].name = "plus";
  c11_info[8].dominantType = "double";
  c11_info[8].resolved = "[B]plus";
  c11_info[8].fileLength = 0U;
  c11_info[8].fileTime1 = 0U;
  c11_info[8].fileTime2 = 0U;
  c11_info[9].context = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[9].name = "sin";
  c11_info[9].dominantType = "double";
  c11_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c11_info[9].fileLength = 324U;
  c11_info[9].fileTime1 = 1203422842U;
  c11_info[9].fileTime2 = 0U;
  c11_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c11_info[10].name = "eml_scalar_sin";
  c11_info[10].dominantType = "double";
  c11_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c11_info[10].fileLength = 601U;
  c11_info[10].fileTime1 = 1209309190U;
  c11_info[10].fileTime2 = 0U;
  c11_info[11].context = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[11].name = "minus";
  c11_info[11].dominantType = "double";
  c11_info[11].resolved = "[B]minus";
  c11_info[11].fileLength = 0U;
  c11_info[11].fileTime1 = 0U;
  c11_info[11].fileTime2 = 0U;
  c11_info[12].context = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[12].name = "times";
  c11_info[12].dominantType = "double";
  c11_info[12].resolved = "[B]times";
  c11_info[12].fileLength = 0U;
  c11_info[12].fileTime1 = 0U;
  c11_info[12].fileTime2 = 0U;
  c11_info[13].context = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[13].name = "uminus";
  c11_info[13].dominantType = "double";
  c11_info[13].resolved = "[B]uminus";
  c11_info[13].fileLength = 0U;
  c11_info[13].fileTime1 = 0U;
  c11_info[13].fileTime2 = 0U;
  c11_info[14].context = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[14].name = "power";
  c11_info[14].dominantType = "double";
  c11_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c11_info[14].fileLength = 5380U;
  c11_info[14].fileTime1 = 1228068698U;
  c11_info[14].fileTime2 = 0U;
  c11_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c11_info[15].name = "isinteger";
  c11_info[15].dominantType = "double";
  c11_info[15].resolved = "[B]isinteger";
  c11_info[15].fileLength = 0U;
  c11_info[15].fileTime1 = 0U;
  c11_info[15].fileTime2 = 0U;
  c11_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c11_info[16].name = "eml_scalar_eg";
  c11_info[16].dominantType = "double";
  c11_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c11_info[16].fileLength = 3068U;
  c11_info[16].fileTime1 = 1240240410U;
  c11_info[16].fileTime2 = 0U;
  c11_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m!any_enums";
  c11_info[17].name = "false";
  c11_info[17].dominantType = "";
  c11_info[17].resolved = "[B]false";
  c11_info[17].fileLength = 0U;
  c11_info[17].fileTime1 = 0U;
  c11_info[17].fileTime2 = 0U;
  c11_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c11_info[18].name = "isstruct";
  c11_info[18].dominantType = "double";
  c11_info[18].resolved = "[B]isstruct";
  c11_info[18].fileLength = 0U;
  c11_info[18].fileTime1 = 0U;
  c11_info[18].fileTime2 = 0U;
  c11_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m!zerosum";
  c11_info[19].name = "eq";
  c11_info[19].dominantType = "double";
  c11_info[19].resolved = "[B]eq";
  c11_info[19].fileLength = 0U;
  c11_info[19].fileTime1 = 0U;
  c11_info[19].fileTime2 = 0U;
  c11_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m!zerosum";
  c11_info[20].name = "class";
  c11_info[20].dominantType = "double";
  c11_info[20].resolved = "[B]class";
  c11_info[20].fileLength = 0U;
  c11_info[20].fileTime1 = 0U;
  c11_info[20].fileTime2 = 0U;
  c11_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m!zerosum";
  c11_info[21].name = "cast";
  c11_info[21].dominantType = "double";
  c11_info[21].resolved = "[B]cast";
  c11_info[21].fileLength = 0U;
  c11_info[21].fileTime1 = 0U;
  c11_info[21].fileTime2 = 0U;
  c11_info[22].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c11_info[22].name = "eml_scalexp_alloc";
  c11_info[22].dominantType = "double";
  c11_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c11_info[22].fileLength = 932U;
  c11_info[22].fileTime1 = 1261926670U;
  c11_info[22].fileTime2 = 0U;
  c11_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c11_info[23].name = "isscalar";
  c11_info[23].dominantType = "double";
  c11_info[23].resolved = "[B]isscalar";
  c11_info[23].fileLength = 0U;
  c11_info[23].fileTime1 = 0U;
  c11_info[23].fileTime2 = 0U;
  c11_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c11_info[24].name = "not";
  c11_info[24].dominantType = "logical";
  c11_info[24].resolved = "[B]not";
  c11_info[24].fileLength = 0U;
  c11_info[24].fileTime1 = 0U;
  c11_info[24].fileTime2 = 0U;
  c11_info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c11_info[25].name = "lt";
  c11_info[25].dominantType = "double";
  c11_info[25].resolved = "[B]lt";
  c11_info[25].fileLength = 0U;
  c11_info[25].fileTime1 = 0U;
  c11_info[25].fileTime2 = 0U;
  c11_info[26].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c11_info[26].name = "eml_scalar_floor";
  c11_info[26].dominantType = "double";
  c11_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c11_info[26].fileLength = 260U;
  c11_info[26].fileTime1 = 1209309190U;
  c11_info[26].fileTime2 = 0U;
  c11_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c11_info[27].name = "ne";
  c11_info[27].dominantType = "double";
  c11_info[27].resolved = "[B]ne";
  c11_info[27].fileLength = 0U;
  c11_info[27].fileTime1 = 0U;
  c11_info[27].fileTime2 = 0U;
  c11_info[28].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c11_info[28].name = "eml_error";
  c11_info[28].dominantType = "char";
  c11_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c11_info[28].fileLength = 315U;
  c11_info[28].fileTime1 = 1213905144U;
  c11_info[28].fileTime2 = 0U;
  c11_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c11_info[29].name = "strcmp";
  c11_info[29].dominantType = "char";
  c11_info[29].resolved = "[B]strcmp";
  c11_info[29].fileLength = 0U;
  c11_info[29].fileTime1 = 0U;
  c11_info[29].fileTime2 = 0U;
  c11_info[30].context = "[E]D:/Learn/Project_Matlab/Fanuc/spat_Jacobian.m";
  c11_info[30].name = "reshape";
  c11_info[30].dominantType = "double";
  c11_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c11_info[30].fileLength = 4857U;
  c11_info[30].fileTime1 = 1242276774U;
  c11_info[30].fileTime2 = 0U;
  c11_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c11_info[31].name = "eml_index_class";
  c11_info[31].dominantType = "";
  c11_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c11_info[31].fileLength = 909U;
  c11_info[31].fileTime1 = 1192445182U;
  c11_info[31].fileTime2 = 0U;
  c11_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c11_info[32].name = "size";
  c11_info[32].dominantType = "double";
  c11_info[32].resolved = "[B]size";
  c11_info[32].fileLength = 0U;
  c11_info[32].fileTime1 = 0U;
  c11_info[32].fileTime2 = 0U;
  c11_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c11_info[33].name = "eml_assert_valid_size_arg";
  c11_info[33].dominantType = "double";
  c11_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c11_info[33].fileLength = 3315U;
  c11_info[33].fileTime1 = 1256367816U;
  c11_info[33].fileTime2 = 0U;
  c11_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c11_info[34].name = "isvector";
  c11_info[34].dominantType = "double";
  c11_info[34].resolved = "[B]isvector";
  c11_info[34].fileLength = 0U;
  c11_info[34].fileTime1 = 0U;
  c11_info[34].fileTime2 = 0U;
  c11_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c11_info[35].name = "isinf";
  c11_info[35].dominantType = "double";
  c11_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c11_info[35].fileLength = 541U;
  c11_info[35].fileTime1 = 1271383988U;
  c11_info[35].fileTime2 = 0U;
  c11_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c11_info[36].name = "true";
  c11_info[36].dominantType = "";
  c11_info[36].resolved = "[B]true";
  c11_info[36].fileLength = 0U;
  c11_info[36].fileTime1 = 0U;
  c11_info[36].fileTime2 = 0U;
  c11_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c11_info[37].name = "le";
  c11_info[37].dominantType = "double";
  c11_info[37].resolved = "[B]le";
  c11_info[37].fileLength = 0U;
  c11_info[37].fileTime1 = 0U;
  c11_info[37].fileTime2 = 0U;
  c11_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c11_info[38].name = "double";
  c11_info[38].dominantType = "double";
  c11_info[38].resolved = "[B]double";
  c11_info[38].fileLength = 0U;
  c11_info[38].fileTime1 = 0U;
  c11_info[38].fileTime2 = 0U;
  c11_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c11_info[39].name = "mtimes";
  c11_info[39].dominantType = "double";
  c11_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c11_info[39].fileLength = 3425U;
  c11_info[39].fileTime1 = 1251010272U;
  c11_info[39].fileTime2 = 0U;
  c11_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c11_info[40].name = "intmax";
  c11_info[40].dominantType = "char";
  c11_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c11_info[40].fileLength = 1535U;
  c11_info[40].fileTime1 = 1192445128U;
  c11_info[40].fileTime2 = 0U;
  c11_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c11_info[41].name = "ischar";
  c11_info[41].dominantType = "char";
  c11_info[41].resolved = "[B]ischar";
  c11_info[41].fileLength = 0U;
  c11_info[41].fileTime1 = 0U;
  c11_info[41].fileTime2 = 0U;
  c11_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c11_info[42].name = "int32";
  c11_info[42].dominantType = "double";
  c11_info[42].resolved = "[B]int32";
  c11_info[42].fileLength = 0U;
  c11_info[42].fileTime1 = 0U;
  c11_info[42].fileTime2 = 0U;
  c11_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c11_info[43].name = "ones";
  c11_info[43].dominantType = "char";
  c11_info[43].resolved = "[B]ones";
  c11_info[43].fileLength = 0U;
  c11_info[43].fileTime1 = 0U;
  c11_info[43].fileTime2 = 0U;
  c11_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c11_info[44].name = "ndims";
  c11_info[44].dominantType = "double";
  c11_info[44].resolved = "[B]ndims";
  c11_info[44].fileLength = 0U;
  c11_info[44].fileTime1 = 0U;
  c11_info[44].fileTime2 = 0U;
  c11_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c11_info[45].name = "isempty";
  c11_info[45].dominantType = "double";
  c11_info[45].resolved = "[B]isempty";
  c11_info[45].fileLength = 0U;
  c11_info[45].fileTime1 = 0U;
  c11_info[45].fileTime2 = 0U;
  c11_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c11_info[46].name = "eml_xgemm";
  c11_info[46].dominantType = "int32";
  c11_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c11_info[46].fileLength = 3184U;
  c11_info[46].fileTime1 = 1209309252U;
  c11_info[46].fileTime2 = 0U;
  c11_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!itcount";
  c11_info[47].name = "length";
  c11_info[47].dominantType = "double";
  c11_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c11_info[47].fileLength = 326U;
  c11_info[47].fileTime1 = 1226552074U;
  c11_info[47].fileTime2 = 0U;
  c11_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!itcount";
  c11_info[48].name = "min";
  c11_info[48].dominantType = "double";
  c11_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c11_info[48].fileLength = 362U;
  c11_info[48].fileTime1 = 1245080764U;
  c11_info[48].fileTime2 = 0U;
  c11_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c11_info[49].name = "nargout";
  c11_info[49].dominantType = "";
  c11_info[49].resolved = "[B]nargout";
  c11_info[49].fileLength = 0U;
  c11_info[49].fileTime1 = 0U;
  c11_info[49].fileTime2 = 0U;
  c11_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c11_info[50].name = "eml_min_or_max";
  c11_info[50].dominantType = "char";
  c11_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c11_info[50].fileLength = 9967U;
  c11_info[50].fileTime1 = 1261926670U;
  c11_info[50].fileTime2 = 0U;
  c11_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c11_info[51].name = "isnumeric";
  c11_info[51].dominantType = "double";
  c11_info[51].resolved = "[B]isnumeric";
  c11_info[51].fileLength = 0U;
  c11_info[51].fileTime1 = 0U;
  c11_info[51].fileTime2 = 0U;
  c11_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c11_info[52].name = "islogical";
  c11_info[52].dominantType = "double";
  c11_info[52].resolved = "[B]islogical";
  c11_info[52].fileLength = 0U;
  c11_info[52].fileTime1 = 0U;
  c11_info[52].fileTime2 = 0U;
  c11_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c11_info[53].name = "eml_refblas_xgemm";
  c11_info[53].dominantType = "int32";
  c11_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c11_info[53].fileLength = 5748U;
  c11_info[53].fileTime1 = 1228068672U;
  c11_info[53].fileTime2 = 0U;
  c11_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c11_info[54].name = "eml_index_minus";
  c11_info[54].dominantType = "int32";
  c11_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c11_info[54].fileLength = 277U;
  c11_info[54].fileTime1 = 1192445184U;
  c11_info[54].fileTime2 = 0U;
  c11_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c11_info[55].name = "eml_index_times";
  c11_info[55].dominantType = "int32";
  c11_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c11_info[55].fileLength = 280U;
  c11_info[55].fileTime1 = 1192445186U;
  c11_info[55].fileTime2 = 0U;
  c11_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c11_info[56].name = "eml_index_plus";
  c11_info[56].dominantType = "int32";
  c11_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c11_info[56].fileLength = 272U;
  c11_info[56].fileTime1 = 1192445184U;
  c11_info[56].fileTime2 = 0U;
  c11_info[57].context = "";
  c11_info[57].name = "fwd_kin";
  c11_info[57].dominantType = "double";
  c11_info[57].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c11_info[57].fileLength = 3324U;
  c11_info[57].fileTime1 = 1366778959U;
  c11_info[57].fileTime2 = 0U;
  c11_info[58].context = "";
  c11_info[58].name = "cross";
  c11_info[58].dominantType = "double";
  c11_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c11_info[58].fileLength = 3157U;
  c11_info[58].fileTime1 = 1240240462U;
  c11_info[58].fileTime2 = 0U;
}

static const mxArray *c11_h_sf_marshall(void *chartInstanceVoid, void *c11_u)
{
  const mxArray *c11_y = NULL;
  boolean_T c11_b_u;
  const mxArray *c11_b_y = NULL;
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)chartInstanceVoid;
  c11_y = NULL;
  c11_b_u = *((boolean_T *)c11_u);
  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", &c11_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c11_y, c11_b_y);
  return c11_y;
}

static void c11_emlrt_marshallIn(SFc11_EulerDynJointConInstanceStruct
  *chartInstance, const mxArray *c11_EndVel, const char_T *
  c11_name, real_T c11_y[3])
{
  real_T c11_dv3[3];
  int32_T c11_i56;
  sf_mex_import(c11_name, sf_mex_dup(c11_EndVel), c11_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c11_i56 = 0; c11_i56 < 3; c11_i56 = c11_i56 + 1) {
    c11_y[c11_i56] = c11_dv3[c11_i56];
  }

  sf_mex_destroy(&c11_EndVel);
}

static uint8_T c11_b_emlrt_marshallIn(SFc11_EulerDynJointConInstanceStruct
  *chartInstance, const mxArray *
  c11_b_is_active_c11_EulerDynJointCon, const char_T *c11_name)
{
  uint8_T c11_y;
  uint8_T c11_u0;
  sf_mex_import(c11_name, sf_mex_dup(c11_b_is_active_c11_EulerDynJointCon),
                &c11_u0, 1, 3, 0U, 0, 0U, 0);
  c11_y = c11_u0;
  sf_mex_destroy(&c11_b_is_active_c11_EulerDynJointCon);
  return c11_y;
}

static void init_dsm_address_info(SFc11_EulerDynJointConInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c11_EulerDynJointCon_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1368292848U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3886685817U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4265428258U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1477677016U);
}

mxArray *sf_c11_EulerDynJointCon_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3855017101U);
    pr[1] = (double)(1724681295U);
    pr[2] = (double)(1404928264U);
    pr[3] = (double)(66417986U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(9);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  return(mxAutoinheritanceInfo);
}

static mxArray *sf_get_sim_state_info_c11_EulerDynJointCon(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"EndVel\",},{M[8],M[0],T\"is_active_c11_EulerDynJointCon\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c11_EulerDynJointCon_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc11_EulerDynJointConInstanceStruct *chartInstance;
    chartInstance = (SFc11_EulerDynJointConInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_EulerDynJointConMachineNumber_,
           11,
           1,
           1,
           4,
           0,
           0,
           0,
           0,
           2,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_EulerDynJointConMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_EulerDynJointConMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_EulerDynJointConMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Theta");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Omega");
          _SFD_SET_DATA_PROPS(2,2,0,1,"EndVel");
          _SFD_SET_DATA_PROPS(3,10,0,0,"L");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of EML Model Coverage */
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,176);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"spat_Jacobian",0,-1,2102);
        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"fwd_kin",0,-1,3253);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_c_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_c_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshall);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 9;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_b_sf_marshall);
        }

        {
          real_T (*c11_Theta)[6];
          real_T (*c11_Omega)[6];
          real_T (*c11_EndVel)[3];
          c11_EndVel = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c11_Omega = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
          c11_Theta = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c11_Theta);
          _SFD_SET_DATA_VALUE_PTR(1U, *c11_Omega);
          _SFD_SET_DATA_VALUE_PTR(2U, *c11_EndVel);
          _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c11_L);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_EulerDynJointConMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c11_EulerDynJointCon(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc11_EulerDynJointConInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c11_EulerDynJointCon((SFc11_EulerDynJointConInstanceStruct*)
    chartInstanceVar);
  initialize_c11_EulerDynJointCon((SFc11_EulerDynJointConInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c11_EulerDynJointCon(void *chartInstanceVar)
{
  enable_c11_EulerDynJointCon((SFc11_EulerDynJointConInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c11_EulerDynJointCon(void *chartInstanceVar)
{
  disable_c11_EulerDynJointCon((SFc11_EulerDynJointConInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c11_EulerDynJointCon(void *chartInstanceVar)
{
  sf_c11_EulerDynJointCon((SFc11_EulerDynJointConInstanceStruct*)
    chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c11_EulerDynJointCon(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c11_EulerDynJointCon
    ((SFc11_EulerDynJointConInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c11_EulerDynJointCon();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

static void sf_internal_set_sim_state_c11_EulerDynJointCon(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c11_EulerDynJointCon();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c11_EulerDynJointCon((SFc11_EulerDynJointConInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c11_EulerDynJointCon(SimStruct* S)
{
  return sf_internal_get_sim_state_c11_EulerDynJointCon(S);
}

static void sf_opaque_set_sim_state_c11_EulerDynJointCon(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c11_EulerDynJointCon(S, st);
}

static void sf_opaque_terminate_c11_EulerDynJointCon(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc11_EulerDynJointConInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c11_EulerDynJointCon((SFc11_EulerDynJointConInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c11_EulerDynJointCon
    ((SFc11_EulerDynJointConInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c11_EulerDynJointCon(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c11_EulerDynJointCon((SFc11_EulerDynJointConInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c11_EulerDynJointCon(SimStruct *S)
{
  /* Actual parameters from chart:
     L
   */
  const char_T *rtParamNames[] = { "p1" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for L*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"EulerDynJointCon","EulerDynJointCon",11);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"EulerDynJointCon","EulerDynJointCon",
                11,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"EulerDynJointCon",
      "EulerDynJointCon",11,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"EulerDynJointCon",
        "EulerDynJointCon",11,2);
      sf_mark_chart_reusable_outputs(S,"EulerDynJointCon","EulerDynJointCon",11,
        1);
    }

    sf_set_rtw_dwork_info(S,"EulerDynJointCon","EulerDynJointCon",11);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3016433681U));
  ssSetChecksum1(S,(807741612U));
  ssSetChecksum2(S,(1213539575U));
  ssSetChecksum3(S,(607555972U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c11_EulerDynJointCon(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "EulerDynJointCon", "EulerDynJointCon",11);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c11_EulerDynJointCon(SimStruct *S)
{
  SFc11_EulerDynJointConInstanceStruct *chartInstance;
  chartInstance = (SFc11_EulerDynJointConInstanceStruct *)malloc(sizeof
    (SFc11_EulerDynJointConInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc11_EulerDynJointConInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c11_EulerDynJointCon;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c11_EulerDynJointCon;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c11_EulerDynJointCon;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c11_EulerDynJointCon;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c11_EulerDynJointCon;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c11_EulerDynJointCon;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c11_EulerDynJointCon;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c11_EulerDynJointCon;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c11_EulerDynJointCon;
  chartInstance->chartInfo.mdlStart = mdlStart_c11_EulerDynJointCon;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c11_EulerDynJointCon;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c11_EulerDynJointCon_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c11_EulerDynJointCon(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c11_EulerDynJointCon(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c11_EulerDynJointCon(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c11_EulerDynJointCon_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
