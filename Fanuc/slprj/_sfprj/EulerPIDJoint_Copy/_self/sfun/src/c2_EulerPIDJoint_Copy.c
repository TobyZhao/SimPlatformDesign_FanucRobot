/* Include files */

#include "blascompat32.h"
#include "EulerPIDJoint_Copy_sfun.h"
#include "c2_EulerPIDJoint_Copy.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "EulerPIDJoint_Copy_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c2_debug_family_names[10] = { "V", "g", "Jb", "Adg_inv",
  "nargin", "nargout", "Theta", "EndVel", "L", "Omega" };

static const char *c2_b_debug_family_names[68] = { "A1", "A2", "A3", "A4", "A5",
  "A6", "L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9", "t2", "t3", "t4",
  "t5", "t6", "t7", "t8", "t9", "t10", "t11", "t12", "t13", "t14", "t23", "t15",
  "t16", "t17", "t18", "t19", "t20", "t21", "t22", "t24", "t25", "t26", "t27",
  "t34", "t28", "t29", "t30", "t31", "t32", "t36", "t33", "t35", "t37", "t38",
  "t39", "t40", "t41", "t42", "t43", "t44", "t45", "t47", "t46", "t48", "t49",
  "nargin", "nargout", "in1", "in2", "gst" };

static const char *c2_c_debug_family_names[49] = { "A2", "A3", "A4", "A5", "A6",
  "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9", "t52", "t53", "t54", "t55",
  "t56", "t57", "t58", "t59", "t60", "t61", "t62", "t63", "t64", "t65", "t66",
  "t67", "t68", "t69", "t70", "t71", "t72", "t73", "t74", "t75", "t76", "t77",
  "t78", "t79", "t80", "t81", "t82", "nargin", "nargout", "in1", "in2",
  "body_Jacobian" };

static const char *c2_d_debug_family_names[4] = { "nargin", "nargout", "w", "wh"
};

static const char *c2_e_debug_family_names[7] = { "RT", "p", "ze", "nargin",
  "nargout", "g", "Adg_inv" };

/* Function Declarations */
static void initialize_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void initialize_params_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void enable_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void disable_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct *
  chartInstance);
static void c2_update_debugger_state_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void set_sim_state_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void sf_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c2_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void compInitSubchartSimstructsFcn_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static void c2_fwd_kin(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c2_in1[9], real_T c2_in2[6], real_T c2_gst[16]);
static void c2_body_Jacobian(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c2_in1[9], real_T c2_in2[6], real_T c2_b_body_Jacobian
  [36]);
static void c2_AdjointInv(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c2_g[16], real_T c2_Adg_inv[36]);
static void c2_eml_scalar_eg(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c2_eps(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void c2_eml_matlab_zgetrf(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c2_A[36], real_T c2_b_A[36], int32_T c2_ipiv[6],
  int32_T *c2_info);
static int32_T c2_eml_ixamax(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[36], int32_T c2_ix0);
static int32_T c2_ceval_ixamax(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[36], int32_T c2_ix0, int32_T c2_incx);
static void c2_ceval_xswap(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[36], int32_T c2_ix0, int32_T c2_incx, int32_T c2_iy0,
  int32_T c2_incy, real_T c2_b_x[36]);
static void c2_ceval_xger(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_alpha1, int32_T c2_ix0, int32_T c2_incx,
  int32_T c2_iy0, int32_T c2_incy, real_T c2_A[36], int32_T c2_ia0, int32_T
  c2_lda, real_T c2_b_A[36]);
static void c2_eml_warning(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void c2_eml_blas_xtrsm(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_alpha1, real_T c2_A[36],
  int32_T c2_ia0, int32_T c2_lda, real_T c2_B[36], int32_T c2_ib0, int32_T
  c2_ldb, real_T c2_b_B[36]);
static void c2_ceval_xtrsm(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_alpha1, real_T c2_A[36], int32_T c2_ia0,
  int32_T c2_lda, real_T c2_B[36], int32_T c2_ib0, int32_T c2_ldb, real_T
  c2_b_B[36]);
static void c2_b_eml_blas_xtrsm(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_alpha1, real_T c2_A[36],
  int32_T c2_ia0, int32_T c2_lda, real_T c2_B[36], int32_T c2_ib0, int32_T
  c2_ldb, real_T c2_b_B[36]);
static void c2_b_ceval_xtrsm(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_alpha1, real_T c2_A[36],
  int32_T c2_ia0, int32_T c2_lda, real_T c2_B[36], int32_T c2_ib0, int32_T
  c2_ldb, real_T c2_b_B[36]);
static void c2_b_eml_scalar_eg(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static const mxArray *c2_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_b_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_c_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_d_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_e_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_f_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_g_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_h_sf_marshall(void *chartInstanceVoid, void *c2_u);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[100]);
static void c2_b_info_helper(c2_ResolvedFunctionInfo c2_info[100]);
static const mxArray *c2_i_sf_marshall(void *chartInstanceVoid, void *c2_u);
static void c2_emlrt_marshallIn(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *c2_Omega, const char_T *c2_name, real_T c2_y[6]);
static uint8_T c2_b_emlrt_marshallIn(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_EulerPIDJoint_Copy, const
  char_T *c2_name);
static void init_dsm_address_info(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_EulerPIDJoint_Copy = 0U;
}

static void initialize_params_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  real_T c2_dv0[9];
  int32_T c2_i0;
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'L' in the parent workspace.\n");
  sf_mex_import("L", sf_mex_get_sfun_param(chartInstance->S, 0, 0), c2_dv0, 0, 0,
                0U, 1, 0U, 2, 1, 9);
  for (c2_i0 = 0; c2_i0 < 9; c2_i0 = c2_i0 + 1) {
    chartInstance->c2_L[c2_i0] = c2_dv0[c2_i0];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  const mxArray *c2_st = NULL;
  const mxArray *c2_y = NULL;
  int32_T c2_i1;
  real_T c2_hoistedGlobal[6];
  int32_T c2_i2;
  real_T c2_u[6];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T (*c2_Omega)[6];
  c2_Omega = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2));
  for (c2_i1 = 0; c2_i1 < 6; c2_i1 = c2_i1 + 1) {
    c2_hoistedGlobal[c2_i1] = (*c2_Omega)[c2_i1];
  }

  for (c2_i2 = 0; c2_i2 < 6; c2_i2 = c2_i2 + 1) {
    c2_u[c2_i2] = c2_hoistedGlobal[c2_i2];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 6));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_active_c2_EulerPIDJoint_Copy;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv1[6];
  int32_T c2_i3;
  real_T (*c2_Omega)[6];
  c2_Omega = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "Omega", c2_dv1);
  for (c2_i3 = 0; c2_i3 < 6; c2_i3 = c2_i3 + 1) {
    (*c2_Omega)[c2_i3] = c2_dv1[c2_i3];
  }

  chartInstance->c2_is_active_c2_EulerPIDJoint_Copy = c2_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_EulerPIDJoint_Copy");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_EulerPIDJoint_Copy(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void sf_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_previousEvent;
  real_T (*c2_EndVel)[3];
  real_T (*c2_Omega)[6];
  real_T (*c2_Theta)[6];
  c2_EndVel = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c2_Omega = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_Theta = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1);
  for (c2_i4 = 0; c2_i4 < 6; c2_i4 = c2_i4 + 1) {
    _SFD_DATA_RANGE_CHECK((*c2_Theta)[c2_i4], 0U);
  }

  for (c2_i5 = 0; c2_i5 < 6; c2_i5 = c2_i5 + 1) {
    _SFD_DATA_RANGE_CHECK((*c2_Omega)[c2_i5], 1U);
  }

  for (c2_i6 = 0; c2_i6 < 3; c2_i6 = c2_i6 + 1) {
    _SFD_DATA_RANGE_CHECK((*c2_EndVel)[c2_i6], 2U);
  }

  for (c2_i7 = 0; c2_i7 < 9; c2_i7 = c2_i7 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c2_L[c2_i7], 3U);
  }

  c2_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  c2_c2_EulerPIDJoint_Copy(chartInstance);
  _sfEvent_ = c2_previousEvent;
  sf_debug_check_for_state_inconsistency(_EulerPIDJoint_CopyMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_c2_EulerPIDJoint_Copy(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
  int32_T c2_i8;
  real_T c2_hoistedGlobal[6];
  int32_T c2_i9;
  real_T c2_b_hoistedGlobal[3];
  int32_T c2_i10;
  real_T c2_c_hoistedGlobal[9];
  int32_T c2_i11;
  real_T c2_Theta[6];
  int32_T c2_i12;
  real_T c2_EndVel[3];
  int32_T c2_i13;
  real_T c2_b_L[9];
  uint32_T c2_debug_family_var_map[10];
  static const char *c2_sv0[10] = { "V", "g", "Jb", "Adg_inv", "nargin",
    "nargout", "Theta", "EndVel", "L", "Omega" };

  real_T c2_V[6];
  real_T c2_g[16];
  real_T c2_Jb[36];
  real_T c2_Adg_inv[36];
  real_T c2_nargin = 3.0;
  real_T c2_nargout = 1.0;
  real_T c2_Omega[6];
  int32_T c2_i14;
  int32_T c2_i15;
  int32_T c2_i16;
  real_T c2_c_L[9];
  int32_T c2_i17;
  real_T c2_b_Theta[6];
  real_T c2_dv2[16];
  int32_T c2_i18;
  int32_T c2_i19;
  real_T c2_d_L[9];
  int32_T c2_i20;
  real_T c2_c_Theta[6];
  real_T c2_dv3[36];
  int32_T c2_i21;
  int32_T c2_i22;
  real_T c2_b_g[16];
  real_T c2_dv4[36];
  int32_T c2_i23;
  int32_T c2_i24;
  real_T c2_A[36];
  int32_T c2_i25;
  real_T c2_B[36];
  int32_T c2_i26;
  real_T c2_b_A[36];
  int32_T c2_i27;
  real_T c2_b_B[36];
  int32_T c2_i28;
  real_T c2_c_A[36];
  int32_T c2_i29;
  real_T c2_c_B[36];
  int32_T c2_i30;
  real_T c2_d_A[36];
  int32_T c2_i31;
  real_T c2_e_A[36];
  int32_T c2_i32;
  real_T c2_f_A[36];
  int32_T c2_i33;
  real_T c2_g_A[36];
  int32_T c2_i34;
  real_T c2_h_A[36];
  int32_T c2_info;
  int32_T c2_ipiv[6];
  real_T c2_i_A[36];
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_b_ipiv[6];
  int32_T c2_b_info;
  int32_T c2_i37;
  int32_T c2_i38;
  int32_T c2_c_ipiv[6];
  int32_T c2_c_info;
  int32_T c2_i39;
  int32_T c2_i40;
  int32_T c2_d_ipiv[6];
  int32_T c2_d_info;
  int32_T c2_i41;
  real_T c2_Y[36];
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_ip;
  int32_T c2_j;
  int32_T c2_b_j;
  real_T c2_temp;
  int32_T c2_i42;
  real_T c2_j_A[36];
  int32_T c2_i43;
  real_T c2_d_B[36];
  int32_T c2_i44;
  int32_T c2_i45;
  real_T c2_k_A[36];
  int32_T c2_i46;
  real_T c2_b_Y[36];
  int32_T c2_i47;
  real_T c2_l_A[36];
  int32_T c2_i48;
  real_T c2_e_B[36];
  int32_T c2_i49;
  int32_T c2_i50;
  real_T c2_m_A[36];
  int32_T c2_i51;
  real_T c2_c_Y[36];
  int32_T c2_i52;
  real_T c2_a[36];
  int32_T c2_i53;
  real_T c2_b[6];
  int32_T c2_i54;
  real_T c2_n_A[36];
  int32_T c2_i55;
  real_T c2_f_B[6];
  int32_T c2_i56;
  real_T c2_o_A[36];
  int32_T c2_i57;
  real_T c2_g_B[6];
  int32_T c2_i58;
  real_T c2_p_A[36];
  int32_T c2_i59;
  real_T c2_h_B[6];
  int32_T c2_i60;
  real_T c2_y[6];
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_i64;
  real_T (*c2_b_Omega)[6];
  real_T (*c2_b_EndVel)[3];
  real_T (*c2_d_Theta)[6];
  c2_b_EndVel = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_Omega = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_d_Theta = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1);
  for (c2_i8 = 0; c2_i8 < 6; c2_i8 = c2_i8 + 1) {
    c2_hoistedGlobal[c2_i8] = (*c2_d_Theta)[c2_i8];
  }

  for (c2_i9 = 0; c2_i9 < 3; c2_i9 = c2_i9 + 1) {
    c2_b_hoistedGlobal[c2_i9] = (*c2_b_EndVel)[c2_i9];
  }

  for (c2_i10 = 0; c2_i10 < 9; c2_i10 = c2_i10 + 1) {
    c2_c_hoistedGlobal[c2_i10] = chartInstance->c2_L[c2_i10];
  }

  for (c2_i11 = 0; c2_i11 < 6; c2_i11 = c2_i11 + 1) {
    c2_Theta[c2_i11] = c2_hoistedGlobal[c2_i11];
  }

  for (c2_i12 = 0; c2_i12 < 3; c2_i12 = c2_i12 + 1) {
    c2_EndVel[c2_i12] = c2_b_hoistedGlobal[c2_i12];
  }

  for (c2_i13 = 0; c2_i13 < 9; c2_i13 = c2_i13 + 1) {
    c2_b_L[c2_i13] = c2_c_hoistedGlobal[c2_i13];
  }

  sf_debug_symbol_scope_push_eml(0U, 10U, 10U, c2_sv0, c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c2_V, c2_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c2_g, c2_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c2_Jb, c2_e_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c2_Adg_inv, c2_e_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c2_nargin, c2_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c2_nargout, c2_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c2_Theta, c2_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c2_EndVel, c2_c_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c2_b_L, c2_b_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c2_Omega, c2_sf_marshall, 9U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0, 4);
  for (c2_i14 = 0; c2_i14 < 6; c2_i14 = c2_i14 + 1) {
    c2_Omega[c2_i14] = 0.0;
  }

  _SFD_EML_CALL(0, 5);
  for (c2_i15 = 0; c2_i15 < 3; c2_i15 = c2_i15 + 1) {
    c2_V[c2_i15] = c2_EndVel[c2_i15];
  }

  c2_V[3] = 0.0;
  c2_V[4] = 0.0;
  c2_V[5] = 0.0;
  _SFD_EML_CALL(0, 6);
  for (c2_i16 = 0; c2_i16 < 9; c2_i16 = c2_i16 + 1) {
    c2_c_L[c2_i16] = c2_b_L[c2_i16];
  }

  for (c2_i17 = 0; c2_i17 < 6; c2_i17 = c2_i17 + 1) {
    c2_b_Theta[c2_i17] = c2_Theta[c2_i17];
  }

  c2_fwd_kin(chartInstance, c2_c_L, c2_b_Theta, c2_dv2);
  for (c2_i18 = 0; c2_i18 < 16; c2_i18 = c2_i18 + 1) {
    c2_g[c2_i18] = c2_dv2[c2_i18];
  }

  _SFD_EML_CALL(0, 7);
  for (c2_i19 = 0; c2_i19 < 9; c2_i19 = c2_i19 + 1) {
    c2_d_L[c2_i19] = c2_b_L[c2_i19];
  }

  for (c2_i20 = 0; c2_i20 < 6; c2_i20 = c2_i20 + 1) {
    c2_c_Theta[c2_i20] = c2_Theta[c2_i20];
  }

  c2_body_Jacobian(chartInstance, c2_d_L, c2_c_Theta, c2_dv3);
  for (c2_i21 = 0; c2_i21 < 36; c2_i21 = c2_i21 + 1) {
    c2_Jb[c2_i21] = c2_dv3[c2_i21];
  }

  _SFD_EML_CALL(0, 8);
  for (c2_i22 = 0; c2_i22 < 16; c2_i22 = c2_i22 + 1) {
    c2_b_g[c2_i22] = c2_g[c2_i22];
  }

  c2_AdjointInv(chartInstance, c2_b_g, c2_dv4);
  for (c2_i23 = 0; c2_i23 < 36; c2_i23 = c2_i23 + 1) {
    c2_Adg_inv[c2_i23] = c2_dv4[c2_i23];
  }

  _SFD_EML_CALL(0, 9);
  for (c2_i24 = 0; c2_i24 < 36; c2_i24 = c2_i24 + 1) {
    c2_A[c2_i24] = c2_Jb[c2_i24];
  }

  for (c2_i25 = 0; c2_i25 < 36; c2_i25 = c2_i25 + 1) {
    c2_B[c2_i25] = c2_Adg_inv[c2_i25];
  }

  for (c2_i26 = 0; c2_i26 < 36; c2_i26 = c2_i26 + 1) {
    c2_b_A[c2_i26] = c2_A[c2_i26];
  }

  for (c2_i27 = 0; c2_i27 < 36; c2_i27 = c2_i27 + 1) {
    c2_b_B[c2_i27] = c2_B[c2_i27];
  }

  for (c2_i28 = 0; c2_i28 < 36; c2_i28 = c2_i28 + 1) {
    c2_c_A[c2_i28] = c2_b_A[c2_i28];
  }

  for (c2_i29 = 0; c2_i29 < 36; c2_i29 = c2_i29 + 1) {
    c2_c_B[c2_i29] = c2_b_B[c2_i29];
  }

  for (c2_i30 = 0; c2_i30 < 36; c2_i30 = c2_i30 + 1) {
    c2_d_A[c2_i30] = c2_c_A[c2_i30];
  }

  for (c2_i31 = 0; c2_i31 < 36; c2_i31 = c2_i31 + 1) {
    c2_e_A[c2_i31] = c2_d_A[c2_i31];
  }

  for (c2_i32 = 0; c2_i32 < 36; c2_i32 = c2_i32 + 1) {
    c2_f_A[c2_i32] = c2_e_A[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 36; c2_i33 = c2_i33 + 1) {
    c2_g_A[c2_i33] = c2_f_A[c2_i33];
  }

  for (c2_i34 = 0; c2_i34 < 36; c2_i34 = c2_i34 + 1) {
    c2_h_A[c2_i34] = c2_g_A[c2_i34];
  }

  c2_eml_matlab_zgetrf(chartInstance, c2_h_A, c2_i_A, c2_ipiv, &c2_info);
  for (c2_i35 = 0; c2_i35 < 36; c2_i35 = c2_i35 + 1) {
    c2_g_A[c2_i35] = c2_i_A[c2_i35];
  }

  for (c2_i36 = 0; c2_i36 < 6; c2_i36 = c2_i36 + 1) {
    c2_b_ipiv[c2_i36] = c2_ipiv[c2_i36];
  }

  c2_b_info = c2_info;
  for (c2_i37 = 0; c2_i37 < 36; c2_i37 = c2_i37 + 1) {
    c2_e_A[c2_i37] = c2_g_A[c2_i37];
  }

  for (c2_i38 = 0; c2_i38 < 6; c2_i38 = c2_i38 + 1) {
    c2_c_ipiv[c2_i38] = c2_b_ipiv[c2_i38];
  }

  c2_c_info = c2_b_info;
  for (c2_i39 = 0; c2_i39 < 36; c2_i39 = c2_i39 + 1) {
    c2_c_A[c2_i39] = c2_e_A[c2_i39];
  }

  for (c2_i40 = 0; c2_i40 < 6; c2_i40 = c2_i40 + 1) {
    c2_d_ipiv[c2_i40] = c2_c_ipiv[c2_i40];
  }

  c2_d_info = c2_c_info;
  if ((real_T)c2_d_info > 0.0) {
    c2_eml_warning(chartInstance);
  }

  for (c2_i41 = 0; c2_i41 < 36; c2_i41 = c2_i41 + 1) {
    c2_Y[c2_i41] = c2_c_B[c2_i41];
  }

  for (c2_i = 1; c2_i < 7; c2_i = c2_i + 1) {
    c2_b_i = c2_i;
    if (c2_d_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_i), 1, 6, 1, 0) - 1] != c2_b_i) {
      c2_ip = c2_d_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 6, 1, 0) - 1];
      for (c2_j = 1; c2_j < 7; c2_j = c2_j + 1) {
        c2_b_j = c2_j;
        c2_temp = c2_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 6, 1, 0) - 1) + 6 * (
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_j), 1, 6, 2, 0) - 1)];
        c2_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 6, 1, 0) - 1) + 6 * (
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_j), 1, 6, 2, 0) - 1)] = c2_Y[(
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_ip), 1, 6, 1, 0) - 1) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 6, 2, 0) - 1)];
        c2_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_ip), 1, 6, 1, 0) - 1) + 6 * (
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_j), 1, 6, 2, 0) - 1)] = c2_temp;
      }
    }
  }

  for (c2_i42 = 0; c2_i42 < 36; c2_i42 = c2_i42 + 1) {
    c2_j_A[c2_i42] = c2_c_A[c2_i42];
  }

  for (c2_i43 = 0; c2_i43 < 36; c2_i43 = c2_i43 + 1) {
    c2_d_B[c2_i43] = c2_Y[c2_i43];
  }

  for (c2_i44 = 0; c2_i44 < 36; c2_i44 = c2_i44 + 1) {
    c2_Y[c2_i44] = c2_d_B[c2_i44];
  }

  for (c2_i45 = 0; c2_i45 < 36; c2_i45 = c2_i45 + 1) {
    c2_k_A[c2_i45] = c2_j_A[c2_i45];
  }

  for (c2_i46 = 0; c2_i46 < 36; c2_i46 = c2_i46 + 1) {
    c2_b_Y[c2_i46] = c2_Y[c2_i46];
  }

  c2_eml_blas_xtrsm(chartInstance, 6, 6, 1.0, c2_k_A, 1, 6, c2_b_Y, 1, 6, c2_Y);
  for (c2_i47 = 0; c2_i47 < 36; c2_i47 = c2_i47 + 1) {
    c2_l_A[c2_i47] = c2_c_A[c2_i47];
  }

  for (c2_i48 = 0; c2_i48 < 36; c2_i48 = c2_i48 + 1) {
    c2_e_B[c2_i48] = c2_Y[c2_i48];
  }

  for (c2_i49 = 0; c2_i49 < 36; c2_i49 = c2_i49 + 1) {
    c2_Y[c2_i49] = c2_e_B[c2_i49];
  }

  for (c2_i50 = 0; c2_i50 < 36; c2_i50 = c2_i50 + 1) {
    c2_m_A[c2_i50] = c2_l_A[c2_i50];
  }

  for (c2_i51 = 0; c2_i51 < 36; c2_i51 = c2_i51 + 1) {
    c2_c_Y[c2_i51] = c2_Y[c2_i51];
  }

  c2_b_eml_blas_xtrsm(chartInstance, 6, 6, 1.0, c2_m_A, 1, 6, c2_c_Y, 1, 6, c2_Y);
  for (c2_i52 = 0; c2_i52 < 36; c2_i52 = c2_i52 + 1) {
    c2_a[c2_i52] = c2_Y[c2_i52];
  }

  for (c2_i53 = 0; c2_i53 < 6; c2_i53 = c2_i53 + 1) {
    c2_b[c2_i53] = c2_V[c2_i53];
  }

  c2_b_eml_scalar_eg(chartInstance);
  c2_b_eml_scalar_eg(chartInstance);
  for (c2_i54 = 0; c2_i54 < 36; c2_i54 = c2_i54 + 1) {
    c2_n_A[c2_i54] = c2_a[c2_i54];
  }

  for (c2_i55 = 0; c2_i55 < 6; c2_i55 = c2_i55 + 1) {
    c2_f_B[c2_i55] = c2_b[c2_i55];
  }

  for (c2_i56 = 0; c2_i56 < 36; c2_i56 = c2_i56 + 1) {
    c2_o_A[c2_i56] = c2_n_A[c2_i56];
  }

  for (c2_i57 = 0; c2_i57 < 6; c2_i57 = c2_i57 + 1) {
    c2_g_B[c2_i57] = c2_f_B[c2_i57];
  }

  for (c2_i58 = 0; c2_i58 < 36; c2_i58 = c2_i58 + 1) {
    c2_p_A[c2_i58] = c2_o_A[c2_i58];
  }

  for (c2_i59 = 0; c2_i59 < 6; c2_i59 = c2_i59 + 1) {
    c2_h_B[c2_i59] = c2_g_B[c2_i59];
  }

  for (c2_i60 = 0; c2_i60 < 6; c2_i60 = c2_i60 + 1) {
    c2_y[c2_i60] = 0.0;
    c2_i61 = 0;
    for (c2_i62 = 0; c2_i62 < 6; c2_i62 = c2_i62 + 1) {
      c2_y[c2_i60] = c2_y[c2_i60] + c2_p_A[c2_i61 + c2_i60] * c2_h_B[c2_i62];
      c2_i61 = c2_i61 + 6;
    }
  }

  for (c2_i63 = 0; c2_i63 < 6; c2_i63 = c2_i63 + 1) {
    c2_Omega[c2_i63] = c2_y[c2_i63];
  }

  _SFD_EML_CALL(0, -9);
  sf_debug_symbol_scope_pop();
  for (c2_i64 = 0; c2_i64 < 6; c2_i64 = c2_i64 + 1) {
    (*c2_b_Omega)[c2_i64] = c2_Omega[c2_i64];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1);
}

static void compInitSubchartSimstructsFcn_c2_EulerPIDJoint_Copy
  (SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 0U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/fwd_kin.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 1U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/body_Jacobian.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 2U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/AdjointInv.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 3U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/skew.m"));
}

static void c2_fwd_kin(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c2_in1[9], real_T c2_in2[6], real_T c2_gst[16])
{
  uint32_T c2_debug_family_var_map[68];
  real_T c2_A1;
  real_T c2_A2;
  real_T c2_A3;
  real_T c2_A4;
  real_T c2_A5;
  real_T c2_A6;
  real_T c2_L1;
  real_T c2_L2;
  real_T c2_L3;
  real_T c2_L4;
  real_T c2_L5;
  real_T c2_L6;
  real_T c2_L7;
  real_T c2_L8;
  real_T c2_L9;
  real_T c2_t2;
  real_T c2_t3;
  real_T c2_t4;
  real_T c2_t5;
  real_T c2_t6;
  real_T c2_t7;
  real_T c2_t8;
  real_T c2_t9;
  real_T c2_t10;
  real_T c2_t11;
  real_T c2_t12;
  real_T c2_t13;
  real_T c2_t14;
  real_T c2_t23;
  real_T c2_t15;
  real_T c2_t16;
  real_T c2_t17;
  real_T c2_t18;
  real_T c2_t19;
  real_T c2_t20;
  real_T c2_t21;
  real_T c2_t22;
  real_T c2_t24;
  real_T c2_t25;
  real_T c2_t26;
  real_T c2_t27;
  real_T c2_t34;
  real_T c2_t28;
  real_T c2_t29;
  real_T c2_t30;
  real_T c2_t31;
  real_T c2_t32;
  real_T c2_t36;
  real_T c2_t33;
  real_T c2_t35;
  real_T c2_t37;
  real_T c2_t38;
  real_T c2_t39;
  real_T c2_t40;
  real_T c2_t41;
  real_T c2_t42;
  real_T c2_t43;
  real_T c2_t44;
  real_T c2_t45;
  real_T c2_t47;
  real_T c2_t46;
  real_T c2_t48;
  real_T c2_t49;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_v_x;
  real_T c2_w_x;
  real_T c2_x_x;
  real_T c2_y_x[16];
  int32_T c2_k;
  int32_T c2_b_k;
  sf_debug_symbol_scope_push_eml(0U, 68U, 68U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_A1, c2_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c2_A2, c2_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c2_A3, c2_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c2_A4, c2_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c2_A5, c2_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c2_A6, c2_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c2_L1, c2_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c2_L2, c2_d_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c2_L3, c2_d_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c2_L4, c2_d_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&c2_L5, c2_d_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&c2_L6, c2_d_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c2_L7, c2_d_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(&c2_L8, c2_d_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(&c2_L9, c2_d_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(&c2_t2, c2_d_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(&c2_t3, c2_d_sf_marshall, 16U);
  sf_debug_symbol_scope_add_eml(&c2_t4, c2_d_sf_marshall, 17U);
  sf_debug_symbol_scope_add_eml(&c2_t5, c2_d_sf_marshall, 18U);
  sf_debug_symbol_scope_add_eml(&c2_t6, c2_d_sf_marshall, 19U);
  sf_debug_symbol_scope_add_eml(&c2_t7, c2_d_sf_marshall, 20U);
  sf_debug_symbol_scope_add_eml(&c2_t8, c2_d_sf_marshall, 21U);
  sf_debug_symbol_scope_add_eml(&c2_t9, c2_d_sf_marshall, 22U);
  sf_debug_symbol_scope_add_eml(&c2_t10, c2_d_sf_marshall, 23U);
  sf_debug_symbol_scope_add_eml(&c2_t11, c2_d_sf_marshall, 24U);
  sf_debug_symbol_scope_add_eml(&c2_t12, c2_d_sf_marshall, 25U);
  sf_debug_symbol_scope_add_eml(&c2_t13, c2_d_sf_marshall, 26U);
  sf_debug_symbol_scope_add_eml(&c2_t14, c2_d_sf_marshall, 27U);
  sf_debug_symbol_scope_add_eml(&c2_t23, c2_d_sf_marshall, 28U);
  sf_debug_symbol_scope_add_eml(&c2_t15, c2_d_sf_marshall, 29U);
  sf_debug_symbol_scope_add_eml(&c2_t16, c2_d_sf_marshall, 30U);
  sf_debug_symbol_scope_add_eml(&c2_t17, c2_d_sf_marshall, 31U);
  sf_debug_symbol_scope_add_eml(&c2_t18, c2_d_sf_marshall, 32U);
  sf_debug_symbol_scope_add_eml(&c2_t19, c2_d_sf_marshall, 33U);
  sf_debug_symbol_scope_add_eml(&c2_t20, c2_d_sf_marshall, 34U);
  sf_debug_symbol_scope_add_eml(&c2_t21, c2_d_sf_marshall, 35U);
  sf_debug_symbol_scope_add_eml(&c2_t22, c2_d_sf_marshall, 36U);
  sf_debug_symbol_scope_add_eml(&c2_t24, c2_d_sf_marshall, 37U);
  sf_debug_symbol_scope_add_eml(&c2_t25, c2_d_sf_marshall, 38U);
  sf_debug_symbol_scope_add_eml(&c2_t26, c2_d_sf_marshall, 39U);
  sf_debug_symbol_scope_add_eml(&c2_t27, c2_d_sf_marshall, 40U);
  sf_debug_symbol_scope_add_eml(&c2_t34, c2_d_sf_marshall, 41U);
  sf_debug_symbol_scope_add_eml(&c2_t28, c2_d_sf_marshall, 42U);
  sf_debug_symbol_scope_add_eml(&c2_t29, c2_d_sf_marshall, 43U);
  sf_debug_symbol_scope_add_eml(&c2_t30, c2_d_sf_marshall, 44U);
  sf_debug_symbol_scope_add_eml(&c2_t31, c2_d_sf_marshall, 45U);
  sf_debug_symbol_scope_add_eml(&c2_t32, c2_d_sf_marshall, 46U);
  sf_debug_symbol_scope_add_eml(&c2_t36, c2_d_sf_marshall, 47U);
  sf_debug_symbol_scope_add_eml(&c2_t33, c2_d_sf_marshall, 48U);
  sf_debug_symbol_scope_add_eml(&c2_t35, c2_d_sf_marshall, 49U);
  sf_debug_symbol_scope_add_eml(&c2_t37, c2_d_sf_marshall, 50U);
  sf_debug_symbol_scope_add_eml(&c2_t38, c2_d_sf_marshall, 51U);
  sf_debug_symbol_scope_add_eml(&c2_t39, c2_d_sf_marshall, 52U);
  sf_debug_symbol_scope_add_eml(&c2_t40, c2_d_sf_marshall, 53U);
  sf_debug_symbol_scope_add_eml(&c2_t41, c2_d_sf_marshall, 54U);
  sf_debug_symbol_scope_add_eml(&c2_t42, c2_d_sf_marshall, 55U);
  sf_debug_symbol_scope_add_eml(&c2_t43, c2_d_sf_marshall, 56U);
  sf_debug_symbol_scope_add_eml(&c2_t44, c2_d_sf_marshall, 57U);
  sf_debug_symbol_scope_add_eml(&c2_t45, c2_d_sf_marshall, 58U);
  sf_debug_symbol_scope_add_eml(&c2_t47, c2_d_sf_marshall, 59U);
  sf_debug_symbol_scope_add_eml(&c2_t46, c2_d_sf_marshall, 60U);
  sf_debug_symbol_scope_add_eml(&c2_t48, c2_d_sf_marshall, 61U);
  sf_debug_symbol_scope_add_eml(&c2_t49, c2_d_sf_marshall, 62U);
  sf_debug_symbol_scope_add_eml(&c2_nargin, c2_d_sf_marshall, 63U);
  sf_debug_symbol_scope_add_eml(&c2_nargout, c2_d_sf_marshall, 64U);
  sf_debug_symbol_scope_add_eml(c2_in1, c2_b_sf_marshall, 65U);
  sf_debug_symbol_scope_add_eml(c2_in2, c2_g_sf_marshall, 66U);
  sf_debug_symbol_scope_add_eml(c2_gst, c2_f_sf_marshall, 67U);
  CV_SCRIPT_FCN(0, 0);

  /* FWD_KIN */
  /*     GST = FWD_KIN(IN1,IN2) */
  /*     This function was generated by the Symbolic Math Toolbox version 5.5. */
  /*     24-Apr-2013 12:49:18 */
  _SFD_SCRIPT_CALL(0, 8);
  c2_A1 = c2_in2[0];
  _SFD_SCRIPT_CALL(0, 9);
  c2_A2 = c2_in2[1];
  _SFD_SCRIPT_CALL(0, 10);
  c2_A3 = c2_in2[2];
  _SFD_SCRIPT_CALL(0, 11);
  c2_A4 = c2_in2[3];
  _SFD_SCRIPT_CALL(0, 12);
  c2_A5 = c2_in2[4];
  _SFD_SCRIPT_CALL(0, 13);
  c2_A6 = c2_in2[5];
  _SFD_SCRIPT_CALL(0, 14);
  c2_L1 = c2_in1[0];
  _SFD_SCRIPT_CALL(0, 15);
  c2_L2 = c2_in1[1];
  _SFD_SCRIPT_CALL(0, 16);
  c2_L3 = c2_in1[2];
  _SFD_SCRIPT_CALL(0, 17);
  c2_L4 = c2_in1[3];
  _SFD_SCRIPT_CALL(0, 18);
  c2_L5 = c2_in1[4];
  _SFD_SCRIPT_CALL(0, 19);
  c2_L6 = c2_in1[5];
  _SFD_SCRIPT_CALL(0, 20);
  c2_L7 = c2_in1[6];
  _SFD_SCRIPT_CALL(0, 21);
  c2_L8 = c2_in1[7];
  _SFD_SCRIPT_CALL(0, 22);
  c2_L9 = c2_in1[8];
  _SFD_SCRIPT_CALL(0, 23);
  c2_x = c2_A1;
  c2_t2 = c2_x;
  c2_b_x = c2_t2;
  c2_t2 = c2_b_x;
  c2_t2 = muDoubleScalarCos(c2_t2);
  _SFD_SCRIPT_CALL(0, 24);
  c2_c_x = c2_A2;
  c2_t3 = c2_c_x;
  c2_d_x = c2_t3;
  c2_t3 = c2_d_x;
  c2_t3 = muDoubleScalarCos(c2_t3);
  _SFD_SCRIPT_CALL(0, 25);
  c2_e_x = c2_A3;
  c2_t4 = c2_e_x;
  c2_f_x = c2_t4;
  c2_t4 = c2_f_x;
  c2_t4 = muDoubleScalarSin(c2_t4);
  _SFD_SCRIPT_CALL(0, 26);
  c2_g_x = c2_A3;
  c2_t5 = c2_g_x;
  c2_h_x = c2_t5;
  c2_t5 = c2_h_x;
  c2_t5 = muDoubleScalarCos(c2_t5);
  _SFD_SCRIPT_CALL(0, 27);
  c2_i_x = c2_A2;
  c2_t6 = c2_i_x;
  c2_j_x = c2_t6;
  c2_t6 = c2_j_x;
  c2_t6 = muDoubleScalarSin(c2_t6);
  _SFD_SCRIPT_CALL(0, 28);
  c2_k_x = c2_A4;
  c2_t7 = c2_k_x;
  c2_l_x = c2_t7;
  c2_t7 = c2_l_x;
  c2_t7 = muDoubleScalarSin(c2_t7);
  _SFD_SCRIPT_CALL(0, 29);
  c2_t8 = c2_t2 * c2_t3 * c2_t4;
  _SFD_SCRIPT_CALL(0, 30);
  c2_t9 = c2_t2 * c2_t5 * c2_t6;
  _SFD_SCRIPT_CALL(0, 31);
  c2_t10 = c2_t8 + c2_t9;
  _SFD_SCRIPT_CALL(0, 32);
  c2_m_x = c2_A4;
  c2_t11 = c2_m_x;
  c2_n_x = c2_t11;
  c2_t11 = c2_n_x;
  c2_t11 = muDoubleScalarCos(c2_t11);
  _SFD_SCRIPT_CALL(0, 33);
  c2_o_x = c2_A1;
  c2_t12 = c2_o_x;
  c2_p_x = c2_t12;
  c2_t12 = c2_p_x;
  c2_t12 = muDoubleScalarSin(c2_t12);
  _SFD_SCRIPT_CALL(0, 34);
  c2_q_x = c2_A5;
  c2_t13 = c2_q_x;
  c2_r_x = c2_t13;
  c2_t13 = c2_r_x;
  c2_t13 = muDoubleScalarSin(c2_t13);
  _SFD_SCRIPT_CALL(0, 35);
  c2_t14 = c2_t2 * c2_t3 * c2_t5;
  _SFD_SCRIPT_CALL(0, 36);
  c2_t23 = c2_t2 * c2_t4 * c2_t6;
  _SFD_SCRIPT_CALL(0, 37);
  c2_t15 = c2_t14 - c2_t23;
  _SFD_SCRIPT_CALL(0, 38);
  c2_s_x = c2_A5;
  c2_t16 = c2_s_x;
  c2_t_x = c2_t16;
  c2_t16 = c2_t_x;
  c2_t16 = muDoubleScalarCos(c2_t16);
  _SFD_SCRIPT_CALL(0, 39);
  c2_t17 = c2_t10 * c2_t11;
  _SFD_SCRIPT_CALL(0, 40);
  c2_t18 = c2_t12 * c2_t7;
  _SFD_SCRIPT_CALL(0, 41);
  c2_t19 = c2_t17 + c2_t18;
  _SFD_SCRIPT_CALL(0, 42);
  c2_u_x = c2_A6;
  c2_t20 = c2_u_x;
  c2_v_x = c2_t20;
  c2_t20 = c2_v_x;
  c2_t20 = muDoubleScalarSin(c2_t20);
  _SFD_SCRIPT_CALL(0, 43);
  c2_t21 = c2_t11 * c2_t12;
  _SFD_SCRIPT_CALL(0, 44);
  c2_w_x = c2_A6;
  c2_t22 = c2_w_x;
  c2_x_x = c2_t22;
  c2_t22 = c2_x_x;
  c2_t22 = muDoubleScalarCos(c2_t22);
  _SFD_SCRIPT_CALL(0, 45);
  c2_t24 = c2_t13 * c2_t15;
  _SFD_SCRIPT_CALL(0, 46);
  c2_t25 = c2_t16 * c2_t19;
  _SFD_SCRIPT_CALL(0, 47);
  c2_t26 = c2_t24 + c2_t25;
  _SFD_SCRIPT_CALL(0, 48);
  c2_t27 = c2_t12 * c2_t3 * c2_t5;
  _SFD_SCRIPT_CALL(0, 49);
  c2_t34 = c2_t12 * c2_t4 * c2_t6;
  _SFD_SCRIPT_CALL(0, 50);
  c2_t28 = c2_t27 - c2_t34;
  _SFD_SCRIPT_CALL(0, 51);
  c2_t29 = c2_t12 * c2_t3 * c2_t4;
  _SFD_SCRIPT_CALL(0, 52);
  c2_t30 = c2_t12 * c2_t5 * c2_t6;
  _SFD_SCRIPT_CALL(0, 53);
  c2_t31 = c2_t29 + c2_t30;
  _SFD_SCRIPT_CALL(0, 54);
  c2_t32 = c2_t11 * c2_t31;
  _SFD_SCRIPT_CALL(0, 55);
  c2_t36 = c2_t2 * c2_t7;
  _SFD_SCRIPT_CALL(0, 56);
  c2_t33 = c2_t32 - c2_t36;
  _SFD_SCRIPT_CALL(0, 57);
  c2_t35 = c2_t13 * c2_t28;
  _SFD_SCRIPT_CALL(0, 58);
  c2_t37 = c2_t16 * c2_t33;
  _SFD_SCRIPT_CALL(0, 59);
  c2_t38 = c2_t35 + c2_t37;
  _SFD_SCRIPT_CALL(0, 60);
  c2_t39 = c2_t31 * c2_t7;
  _SFD_SCRIPT_CALL(0, 61);
  c2_t40 = c2_t11 * c2_t2;
  _SFD_SCRIPT_CALL(0, 62);
  c2_t41 = c2_t39 + c2_t40;
  _SFD_SCRIPT_CALL(0, 63);
  c2_t42 = c2_t3 * c2_t4;
  _SFD_SCRIPT_CALL(0, 64);
  c2_t43 = c2_t5 * c2_t6;
  _SFD_SCRIPT_CALL(0, 65);
  c2_t44 = c2_t42 + c2_t43;
  _SFD_SCRIPT_CALL(0, 66);
  c2_t45 = c2_t3 * c2_t5;
  _SFD_SCRIPT_CALL(0, 67);
  c2_t47 = c2_t4 * c2_t6;
  _SFD_SCRIPT_CALL(0, 68);
  c2_t46 = c2_t45 - c2_t47;
  _SFD_SCRIPT_CALL(0, 69);
  c2_t48 = c2_t13 * c2_t44;
  _SFD_SCRIPT_CALL(0, 70);
  c2_t49 = c2_t48 - c2_t11 * c2_t16 * c2_t46;
  _SFD_SCRIPT_CALL(0, 71);
  c2_y_x[0] = c2_t15 * c2_t16 - c2_t13 * c2_t19;
  c2_y_x[1] = c2_t16 * c2_t28 - c2_t13 * c2_t33;
  c2_y_x[2] = (-c2_t16) * c2_t44 - c2_t11 * c2_t13 * c2_t46;
  c2_y_x[3] = 0.0;
  c2_y_x[4] = c2_t20 * c2_t26 - c2_t22 * (c2_t21 - c2_t10 * c2_t7);
  c2_y_x[5] = c2_t20 * c2_t38 + c2_t22 * c2_t41;
  c2_y_x[6] = (-c2_t20) * c2_t49 + c2_t22 * c2_t46 * c2_t7;
  c2_y_x[7] = 0.0;
  c2_y_x[8] = c2_t22 * c2_t26 + c2_t20 * (c2_t21 - c2_t10 * c2_t7);
  c2_y_x[9] = c2_t22 * c2_t38 - c2_t20 * c2_t41;
  c2_y_x[10] = (-c2_t22) * c2_t49 - c2_t20 * c2_t46 * c2_t7;
  c2_y_x[11] = 0.0;
  c2_y_x[12] = ((((((((((((((((((((((((((((((c2_L2 * c2_t2 + c2_L3 * c2_t2 *
    c2_t6) - c2_L8 * c2_t11 * c2_t12 * c2_t22) + c2_L4 *
    c2_t2 * c2_t3 * c2_t4) + c2_L9 * c2_t11 * c2_t12 * c2_t20) + c2_L5 * c2_t2 *
    c2_t3 * c2_t5) - c2_L6 * c2_t12 * c2_t13 * c2_t7) -
    c2_L7 * c2_t12 * c2_t13 * c2_t7) + c2_L4 * c2_t2 * c2_t5 * c2_t6) - c2_L5 *
    c2_t2 * c2_t4 * c2_t6) + c2_L6 * c2_t16 * c2_t2 * c2_t3
    * c2_t5) + c2_L7 * c2_t16 * c2_t2 * c2_t3 * c2_t5) - c2_L6 * c2_t16 * c2_t2 *
    c2_t4 * c2_t6) + c2_L8 * c2_t12 * c2_t16 * c2_t20 *
    c2_t7) - c2_L7 * c2_t16 * c2_t2 * c2_t4 * c2_t6) + c2_L9 * c2_t12 * c2_t16 *
    c2_t22 * c2_t7) - c2_L6 * c2_t11 * c2_t13 * c2_t2 *
    c2_t3 * c2_t4) - c2_L7 * c2_t11 * c2_t13 * c2_t2 * c2_t3 * c2_t4) + c2_L8 *
    c2_t13 * c2_t2 * c2_t20 * c2_t3 * c2_t5) - c2_L6 *
    c2_t11 * c2_t13 * c2_t2 * c2_t5 * c2_t6) - c2_L7 * c2_t11 * c2_t13 * c2_t2 *
    c2_t5 * c2_t6) + c2_L9 * c2_t13 * c2_t2 * c2_t22 *
    c2_t3 * c2_t5) - c2_L8 * c2_t13 * c2_t2 * c2_t20 * c2_t4 * c2_t6) - c2_L9 *
                       c2_t13 * c2_t2 * c2_t22 * c2_t4 * c2_t6) + c2_L8 * c2_t2
                      * c2_t22 * c2_t3 * c2_t4 * c2_t7) - c2_L9 * c2_t2 * c2_t20
                     * c2_t3 * c2_t4 * c2_t7) + c2_L8 * c2_t2 * c2_t22 * c2_t5 *
                    c2_t6 *
                    c2_t7) - c2_L9 * c2_t2 * c2_t20 * c2_t5 * c2_t6 * c2_t7) +
                  c2_L8 * c2_t11 * c2_t16 * c2_t2 * c2_t20 * c2_t3 * c2_t4) +
                 c2_L9 *
                 c2_t11 * c2_t16 * c2_t2 * c2_t22 * c2_t3 * c2_t4) + c2_L8 *
                c2_t11 * c2_t16 * c2_t2 * c2_t20 * c2_t5 * c2_t6) + c2_L9 *
    c2_t11 *
    c2_t16 * c2_t2 * c2_t22 * c2_t5 * c2_t6;
  c2_y_x[13] = ((((((((((((((((((((((((((((((c2_L2 * c2_t12 + c2_L3 * c2_t12 *
    c2_t6) + c2_L4 * c2_t12 * c2_t3 * c2_t4) + c2_L8 *
    c2_t11 * c2_t2 * c2_t22) + c2_L5 * c2_t12 * c2_t3 * c2_t5) - c2_L9 * c2_t11 *
    c2_t2 * c2_t20) + c2_L4 * c2_t12 * c2_t5 * c2_t6) -
    c2_L5 * c2_t12 * c2_t4 * c2_t6) + c2_L6 * c2_t13 * c2_t2 * c2_t7) + c2_L7 *
    c2_t13 * c2_t2 * c2_t7) + c2_L6 * c2_t12 * c2_t16 *
    c2_t3 * c2_t5) + c2_L7 * c2_t12 * c2_t16 * c2_t3 * c2_t5) - c2_L6 * c2_t12 *
    c2_t16 * c2_t4 * c2_t6) - c2_L7 * c2_t12 * c2_t16 *
    c2_t4 * c2_t6) - c2_L8 * c2_t16 * c2_t2 * c2_t20 * c2_t7) - c2_L9 * c2_t16 *
    c2_t2 * c2_t22 * c2_t7) - c2_L6 * c2_t11 * c2_t12 *
    c2_t13 * c2_t3 * c2_t4) - c2_L7 * c2_t11 * c2_t12 * c2_t13 * c2_t3 * c2_t4)
    + c2_L8 * c2_t12 * c2_t13 * c2_t20 * c2_t3 * c2_t5) -
    c2_L6 * c2_t11 * c2_t12 * c2_t13 * c2_t5 * c2_t6) - c2_L7 * c2_t11 * c2_t12 *
    c2_t13 * c2_t5 * c2_t6) + c2_L9 * c2_t12 * c2_t13 *
    c2_t22 * c2_t3 * c2_t5) - c2_L8 * c2_t12 * c2_t13 * c2_t20 * c2_t4 * c2_t6)
                       - c2_L9 * c2_t12 * c2_t13 * c2_t22 * c2_t4 * c2_t6) +
                      c2_L8 * c2_t12 * c2_t22 * c2_t3 * c2_t4 * c2_t7) - c2_L9 *
                     c2_t12 * c2_t20 * c2_t3 * c2_t4 * c2_t7) + c2_L8 * c2_t12 *
                    c2_t22 *
                    c2_t5 * c2_t6 * c2_t7) - c2_L9 * c2_t12 * c2_t20 * c2_t5 *
                   c2_t6 * c2_t7) + c2_L8 * c2_t11 * c2_t12 * c2_t16 * c2_t20 *
                  c2_t3 *
                  c2_t4) + c2_L9 * c2_t11 * c2_t12 * c2_t16 * c2_t22 * c2_t3 *
                 c2_t4) + c2_L8 * c2_t11 * c2_t12 * c2_t16 * c2_t20 * c2_t5 *
                c2_t6) +
    c2_L9 * c2_t11 * c2_t12 * c2_t16 * c2_t22 * c2_t5 * c2_t6;
  c2_y_x[14] = ((((((((((((((((((((((((c2_L1 + c2_L3 * c2_t3) + c2_L4 * c2_t3 *
    c2_t5) - c2_L5 * c2_t3 * c2_t4) - c2_L4 * c2_t4 *
    c2_t6) - c2_L5 * c2_t5 * c2_t6) - c2_L6 * c2_t16 * c2_t3 * c2_t4) - c2_L7 *
    c2_t16 * c2_t3 * c2_t4) - c2_L6 * c2_t16 * c2_t5 * c2_t6
    ) - c2_L7 * c2_t16 * c2_t5 * c2_t6) - c2_L6 * c2_t11 * c2_t13 * c2_t3 *
    c2_t5) - c2_L7 * c2_t11 * c2_t13 * c2_t3 * c2_t5) - c2_L8 *
    c2_t13 * c2_t20 * c2_t3 * c2_t4) + c2_L6 * c2_t11 * c2_t13 * c2_t4 * c2_t6)
    + c2_L7 * c2_t11 * c2_t13 * c2_t4 * c2_t6) - c2_L9 *
    c2_t13 * c2_t22 * c2_t3 * c2_t4) - c2_L8 * c2_t13 * c2_t20 * c2_t5 * c2_t6)
                       - c2_L9 * c2_t13 * c2_t22 * c2_t5 * c2_t6) + c2_L8 *
                      c2_t22 * c2_t3 * c2_t5 * c2_t7) - c2_L9 * c2_t20 * c2_t3 *
                     c2_t5 * c2_t7) - c2_L8 * c2_t22 * c2_t4 * c2_t6 * c2_t7) +
                   c2_L9 * c2_t20
                   * c2_t4 * c2_t6 * c2_t7) + c2_L8 * c2_t11 * c2_t16 * c2_t20 *
                  c2_t3 * c2_t5) + c2_L9 * c2_t11 * c2_t16 * c2_t22 * c2_t3 *
                 c2_t5) -
                c2_L8 * c2_t11 * c2_t16 * c2_t20 * c2_t4 * c2_t6) - c2_L9 *
    c2_t11 * c2_t16 * c2_t22 * c2_t4 * c2_t6;
  c2_y_x[15] = 1.0;
  for (c2_k = 1; c2_k < 17; c2_k = c2_k + 1) {
    c2_b_k = c2_k;
    c2_gst[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 16, 1, 0) - 1] = c2_y_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_k), 1, 16, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, -71);
  sf_debug_symbol_scope_pop();
}

static void c2_body_Jacobian(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c2_in1[9], real_T c2_in2[6], real_T
  c2_b_body_Jacobian[36])
{
  uint32_T c2_debug_family_var_map[49];
  real_T c2_A2;
  real_T c2_A3;
  real_T c2_A4;
  real_T c2_A5;
  real_T c2_A6;
  real_T c2_L2;
  real_T c2_L3;
  real_T c2_L4;
  real_T c2_L5;
  real_T c2_L6;
  real_T c2_L7;
  real_T c2_L8;
  real_T c2_L9;
  real_T c2_t52;
  real_T c2_t53;
  real_T c2_t54;
  real_T c2_t55;
  real_T c2_t56;
  real_T c2_t57;
  real_T c2_t58;
  real_T c2_t59;
  real_T c2_t60;
  real_T c2_t61;
  real_T c2_t62;
  real_T c2_t63;
  real_T c2_t64;
  real_T c2_t65;
  real_T c2_t66;
  real_T c2_t67;
  real_T c2_t68;
  real_T c2_t69;
  real_T c2_t70;
  real_T c2_t71;
  real_T c2_t72;
  real_T c2_t73;
  real_T c2_t74;
  real_T c2_t75;
  real_T c2_t76;
  real_T c2_t77;
  real_T c2_t78;
  real_T c2_t79;
  real_T c2_t80;
  real_T c2_t81;
  real_T c2_t82;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x[36];
  int32_T c2_k;
  int32_T c2_b_k;
  sf_debug_symbol_scope_push_eml(0U, 49U, 49U, c2_c_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_A2, c2_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c2_A3, c2_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c2_A4, c2_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c2_A5, c2_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c2_A6, c2_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c2_L2, c2_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c2_L3, c2_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c2_L4, c2_d_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c2_L5, c2_d_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c2_L6, c2_d_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&c2_L7, c2_d_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&c2_L8, c2_d_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c2_L9, c2_d_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(&c2_t52, c2_d_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(&c2_t53, c2_d_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(&c2_t54, c2_d_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(&c2_t55, c2_d_sf_marshall, 16U);
  sf_debug_symbol_scope_add_eml(&c2_t56, c2_d_sf_marshall, 17U);
  sf_debug_symbol_scope_add_eml(&c2_t57, c2_d_sf_marshall, 18U);
  sf_debug_symbol_scope_add_eml(&c2_t58, c2_d_sf_marshall, 19U);
  sf_debug_symbol_scope_add_eml(&c2_t59, c2_d_sf_marshall, 20U);
  sf_debug_symbol_scope_add_eml(&c2_t60, c2_d_sf_marshall, 21U);
  sf_debug_symbol_scope_add_eml(&c2_t61, c2_d_sf_marshall, 22U);
  sf_debug_symbol_scope_add_eml(&c2_t62, c2_d_sf_marshall, 23U);
  sf_debug_symbol_scope_add_eml(&c2_t63, c2_d_sf_marshall, 24U);
  sf_debug_symbol_scope_add_eml(&c2_t64, c2_d_sf_marshall, 25U);
  sf_debug_symbol_scope_add_eml(&c2_t65, c2_d_sf_marshall, 26U);
  sf_debug_symbol_scope_add_eml(&c2_t66, c2_d_sf_marshall, 27U);
  sf_debug_symbol_scope_add_eml(&c2_t67, c2_d_sf_marshall, 28U);
  sf_debug_symbol_scope_add_eml(&c2_t68, c2_d_sf_marshall, 29U);
  sf_debug_symbol_scope_add_eml(&c2_t69, c2_d_sf_marshall, 30U);
  sf_debug_symbol_scope_add_eml(&c2_t70, c2_d_sf_marshall, 31U);
  sf_debug_symbol_scope_add_eml(&c2_t71, c2_d_sf_marshall, 32U);
  sf_debug_symbol_scope_add_eml(&c2_t72, c2_d_sf_marshall, 33U);
  sf_debug_symbol_scope_add_eml(&c2_t73, c2_d_sf_marshall, 34U);
  sf_debug_symbol_scope_add_eml(&c2_t74, c2_d_sf_marshall, 35U);
  sf_debug_symbol_scope_add_eml(&c2_t75, c2_d_sf_marshall, 36U);
  sf_debug_symbol_scope_add_eml(&c2_t76, c2_d_sf_marshall, 37U);
  sf_debug_symbol_scope_add_eml(&c2_t77, c2_d_sf_marshall, 38U);
  sf_debug_symbol_scope_add_eml(&c2_t78, c2_d_sf_marshall, 39U);
  sf_debug_symbol_scope_add_eml(&c2_t79, c2_d_sf_marshall, 40U);
  sf_debug_symbol_scope_add_eml(&c2_t80, c2_d_sf_marshall, 41U);
  sf_debug_symbol_scope_add_eml(&c2_t81, c2_d_sf_marshall, 42U);
  sf_debug_symbol_scope_add_eml(&c2_t82, c2_d_sf_marshall, 43U);
  sf_debug_symbol_scope_add_eml(&c2_nargin, c2_d_sf_marshall, 44U);
  sf_debug_symbol_scope_add_eml(&c2_nargout, c2_d_sf_marshall, 45U);
  sf_debug_symbol_scope_add_eml(c2_in1, c2_b_sf_marshall, 46U);
  sf_debug_symbol_scope_add_eml(c2_in2, c2_g_sf_marshall, 47U);
  sf_debug_symbol_scope_add_eml(c2_b_body_Jacobian, c2_e_sf_marshall, 48U);
  CV_SCRIPT_FCN(1, 0);

  /* BODY_JACOBIAN */
  /*     BODY_JACOBIAN = BODY_JACOBIAN(IN1,IN2) */
  /*     This function was generated by the Symbolic Math Toolbox version 5.5. */
  /*     24-Apr-2013 20:43:25 */
  _SFD_SCRIPT_CALL(1, 8);
  c2_A2 = c2_in2[1];
  _SFD_SCRIPT_CALL(1, 9);
  c2_A3 = c2_in2[2];
  _SFD_SCRIPT_CALL(1, 10);
  c2_A4 = c2_in2[3];
  _SFD_SCRIPT_CALL(1, 11);
  c2_A5 = c2_in2[4];
  _SFD_SCRIPT_CALL(1, 12);
  c2_A6 = c2_in2[5];
  _SFD_SCRIPT_CALL(1, 13);
  c2_L2 = c2_in1[1];
  _SFD_SCRIPT_CALL(1, 14);
  c2_L3 = c2_in1[2];
  _SFD_SCRIPT_CALL(1, 15);
  c2_L4 = c2_in1[3];
  _SFD_SCRIPT_CALL(1, 16);
  c2_L5 = c2_in1[4];
  _SFD_SCRIPT_CALL(1, 17);
  c2_L6 = c2_in1[5];
  _SFD_SCRIPT_CALL(1, 18);
  c2_L7 = c2_in1[6];
  _SFD_SCRIPT_CALL(1, 19);
  c2_L8 = c2_in1[7];
  _SFD_SCRIPT_CALL(1, 20);
  c2_L9 = c2_in1[8];
  _SFD_SCRIPT_CALL(1, 21);
  c2_x = c2_A4;
  c2_t52 = c2_x;
  c2_b_x = c2_t52;
  c2_t52 = c2_b_x;
  c2_t52 = muDoubleScalarSin(c2_t52);
  _SFD_SCRIPT_CALL(1, 22);
  c2_c_x = c2_A5;
  c2_t53 = c2_c_x;
  c2_d_x = c2_t53;
  c2_t53 = c2_d_x;
  c2_t53 = muDoubleScalarSin(c2_t53);
  _SFD_SCRIPT_CALL(1, 23);
  c2_e_x = c2_A2;
  c2_t54 = c2_e_x;
  c2_f_x = c2_t54;
  c2_t54 = c2_f_x;
  c2_t54 = muDoubleScalarCos(c2_t54);
  _SFD_SCRIPT_CALL(1, 24);
  c2_g_x = c2_A3;
  c2_t55 = c2_g_x;
  c2_h_x = c2_t55;
  c2_t55 = c2_h_x;
  c2_t55 = muDoubleScalarCos(c2_t55);
  _SFD_SCRIPT_CALL(1, 25);
  c2_i_x = c2_A6;
  c2_t56 = c2_i_x;
  c2_j_x = c2_t56;
  c2_t56 = c2_j_x;
  c2_t56 = muDoubleScalarCos(c2_t56);
  _SFD_SCRIPT_CALL(1, 26);
  c2_k_x = c2_A2;
  c2_t57 = c2_k_x;
  c2_l_x = c2_t57;
  c2_t57 = c2_l_x;
  c2_t57 = muDoubleScalarSin(c2_t57);
  _SFD_SCRIPT_CALL(1, 27);
  c2_m_x = c2_A3;
  c2_t58 = c2_m_x;
  c2_n_x = c2_t58;
  c2_t58 = c2_n_x;
  c2_t58 = muDoubleScalarSin(c2_t58);
  _SFD_SCRIPT_CALL(1, 28);
  c2_o_x = c2_A6;
  c2_t59 = c2_o_x;
  c2_p_x = c2_t59;
  c2_t59 = c2_p_x;
  c2_t59 = muDoubleScalarSin(c2_t59);
  _SFD_SCRIPT_CALL(1, 29);
  c2_q_x = c2_A4;
  c2_t60 = c2_q_x;
  c2_r_x = c2_t60;
  c2_t60 = c2_r_x;
  c2_t60 = muDoubleScalarCos(c2_t60);
  _SFD_SCRIPT_CALL(1, 30);
  c2_s_x = c2_A5;
  c2_t61 = c2_s_x;
  c2_t_x = c2_t61;
  c2_t61 = c2_t_x;
  c2_t61 = muDoubleScalarCos(c2_t61);
  _SFD_SCRIPT_CALL(1, 31);
  c2_t62 = c2_L4 * c2_t61;
  _SFD_SCRIPT_CALL(1, 32);
  c2_t63 = c2_L5 * c2_t53 * c2_t60;
  _SFD_SCRIPT_CALL(1, 33);
  c2_t64 = c2_L8 * c2_t59 * c2_t60;
  _SFD_SCRIPT_CALL(1, 34);
  c2_t65 = c2_L9 * c2_t56 * c2_t60;
  _SFD_SCRIPT_CALL(1, 35);
  c2_t66 = c2_L8 * c2_t52 * c2_t56 * c2_t61;
  _SFD_SCRIPT_CALL(1, 36);
  c2_t67 = c2_L4 * c2_t53 * c2_t59;
  _SFD_SCRIPT_CALL(1, 37);
  c2_t68 = c2_L4 * c2_t53 * c2_t56;
  _SFD_SCRIPT_CALL(1, 38);
  c2_t69 = c2_L5 * c2_t52 * c2_t59;
  _SFD_SCRIPT_CALL(1, 39);
  c2_t70 = c2_L8 * c2_t52 * c2_t53;
  _SFD_SCRIPT_CALL(1, 40);
  c2_t71 = c2_L6 * c2_t52 * c2_t59 * c2_t61;
  _SFD_SCRIPT_CALL(1, 41);
  c2_t72 = c2_L7 * c2_t52 * c2_t59 * c2_t61;
  _SFD_SCRIPT_CALL(1, 42);
  c2_t73 = c2_L6 + c2_L7;
  _SFD_SCRIPT_CALL(1, 43);
  c2_t74 = c2_t52 * c2_t53;
  _SFD_SCRIPT_CALL(1, 44);
  c2_t75 = c2_t52 * c2_t56;
  _SFD_SCRIPT_CALL(1, 45);
  c2_t76 = c2_t59 * c2_t60 * c2_t61;
  _SFD_SCRIPT_CALL(1, 46);
  c2_t77 = c2_t75 + c2_t76;
  _SFD_SCRIPT_CALL(1, 47);
  c2_t78 = c2_t56 * c2_t60;
  _SFD_SCRIPT_CALL(1, 48);
  c2_t79 = c2_t78 - c2_t52 * c2_t59 * c2_t61;
  _SFD_SCRIPT_CALL(1, 49);
  c2_t80 = c2_t52 * c2_t59;
  _SFD_SCRIPT_CALL(1, 50);
  c2_t81 = c2_t80 - c2_t56 * c2_t60 * c2_t61;
  _SFD_SCRIPT_CALL(1, 51);
  c2_t82 = (-c2_t59) * c2_t60 - c2_t52 * c2_t56 * c2_t61;
  _SFD_SCRIPT_CALL(1, 52);
  c2_u_x[0] = ((((((((((((((((c2_L2 * c2_t52 * c2_t53 + c2_L3 * c2_t52 * c2_t53 *
    c2_t57) + c2_L4 * c2_t52 * c2_t53 * c2_t54 * c2_t58)
    + c2_L4 * c2_t52 * c2_t53 * c2_t55 * c2_t57) + c2_L5 * c2_t52 * c2_t53 *
    c2_t54 * c2_t55) - c2_L5 * c2_t52 * c2_t53 * c2_t57 *
    c2_t58) + c2_L8 * c2_t52 * c2_t54 * c2_t55 * c2_t59) + c2_L8 * c2_t53 *
                        c2_t54 * c2_t56 * c2_t58) + c2_L8 * c2_t53 * c2_t55 *
                       c2_t56
                       * c2_t57) - c2_L8 * c2_t52 * c2_t57 * c2_t58 * c2_t59) +
                     c2_L9 * c2_t52 * c2_t54 * c2_t55 * c2_t56) - c2_L9 * c2_t52
                    * c2_t56 *
                    c2_t57 * c2_t58) - c2_L9 * c2_t53 * c2_t54 * c2_t58 * c2_t59)
                  - c2_L9 * c2_t53 * c2_t55 * c2_t57 * c2_t59) - c2_L8 * c2_t54 *
                 c2_t55
                 * c2_t56 * c2_t60 * c2_t61) + c2_L8 * c2_t56 * c2_t57 * c2_t58 *
                c2_t60 * c2_t61) + c2_L9 * c2_t54 * c2_t55 * c2_t59 * c2_t60 *
               c2_t61) - c2_L9 * c2_t57 * c2_t58 * c2_t59 * c2_t60 * c2_t61;
  c2_u_x[1] = ((((((((((((((((((((((((((c2_L2 * c2_t56 * c2_t60 - c2_L2 * c2_t52
    * c2_t59 * c2_t61) + c2_L3 * c2_t56 * c2_t57 * c2_t60
    ) + c2_L9 * c2_t54 * c2_t58 * c2_t61) + c2_L9 * c2_t55 * c2_t57 * c2_t61) -
    c2_L3 * c2_t52 * c2_t57 * c2_t59 * c2_t61) + c2_L4 *
    c2_t54 * c2_t56 * c2_t58 * c2_t60) + c2_L4 * c2_t55 * c2_t56 * c2_t57 *
    c2_t60) + c2_L5 * c2_t54 * c2_t55 * c2_t56 * c2_t60) - c2_L6
    * c2_t52 * c2_t54 * c2_t55 * c2_t59) - c2_L5 * c2_t56 * c2_t57 * c2_t58 *
    c2_t60) - c2_L6 * c2_t53 * c2_t54 * c2_t56 * c2_t58) -
    c2_L6 * c2_t53 * c2_t55 * c2_t56 * c2_t57) + c2_L6 * c2_t52 * c2_t57 *
    c2_t58 * c2_t59) - c2_L7 * c2_t52 * c2_t54 * c2_t55 * c2_t59)
    - c2_L7 * c2_t53 * c2_t54 * c2_t56 * c2_t58) - c2_L7 * c2_t53 * c2_t55 *
    c2_t56 * c2_t57) + c2_L7 * c2_t52 * c2_t57 * c2_t58 *
                        c2_t59) + c2_L9 * c2_t53 * c2_t54 * c2_t55 * c2_t60) -
                      c2_L9 * c2_t53 * c2_t57 * c2_t58 * c2_t60) - c2_L4 *
                     c2_t52 * c2_t54 * c2_t58
                     * c2_t59 * c2_t61) - c2_L4 * c2_t52 * c2_t55 * c2_t57 *
                    c2_t59 * c2_t61) - c2_L5 * c2_t52 * c2_t54 * c2_t55 * c2_t59
                   * c2_t61) +
                  c2_L5 * c2_t52 * c2_t57 * c2_t58 * c2_t59 * c2_t61) + c2_L6 *
                 c2_t54 * c2_t55 * c2_t56 * c2_t60 * c2_t61) - c2_L6 * c2_t56 *
                c2_t57
                * c2_t58 * c2_t60 * c2_t61) + c2_L7 * c2_t54 * c2_t55 * c2_t56 *
               c2_t60 * c2_t61) - c2_L7 * c2_t56 * c2_t57 * c2_t58 * c2_t60 *
    c2_t61;
  c2_u_x[2] = (((((((((((((((((((((((((((-c2_L2) * c2_t59 * c2_t60 - c2_L2 *
    c2_t52 * c2_t56 * c2_t61) - c2_L3 * c2_t57 * c2_t59 *
    c2_t60) - c2_L8 * c2_t54 * c2_t58 * c2_t61) - c2_L8 * c2_t55 * c2_t57 *
    c2_t61) - c2_L3 * c2_t52 * c2_t56 * c2_t57 * c2_t61) - c2_L4
    * c2_t54 * c2_t58 * c2_t59 * c2_t60) - c2_L4 * c2_t55 * c2_t57 * c2_t59 *
    c2_t60) - c2_L6 * c2_t52 * c2_t54 * c2_t55 * c2_t56) -
    c2_L5 * c2_t54 * c2_t55 * c2_t59 * c2_t60) + c2_L6 * c2_t52 * c2_t56 *
    c2_t57 * c2_t58) + c2_L5 * c2_t57 * c2_t58 * c2_t59 * c2_t60)
    + c2_L6 * c2_t53 * c2_t54 * c2_t58 * c2_t59) + c2_L6 * c2_t53 * c2_t55 *
    c2_t57 * c2_t59) - c2_L7 * c2_t52 * c2_t54 * c2_t55 *
    c2_t56) + c2_L7 * c2_t52 * c2_t56 * c2_t57 * c2_t58) + c2_L7 * c2_t53 *
    c2_t54 * c2_t58 * c2_t59) + c2_L7 * c2_t53 * c2_t55 * c2_t57
                        * c2_t59) - c2_L8 * c2_t53 * c2_t54 * c2_t55 * c2_t60) +
                      c2_L8 * c2_t53 * c2_t57 * c2_t58 * c2_t60) - c2_L4 *
                     c2_t52 * c2_t54 *
                     c2_t56 * c2_t58 * c2_t61) - c2_L4 * c2_t52 * c2_t55 *
                    c2_t56 * c2_t57 * c2_t61) - c2_L5 * c2_t52 * c2_t54 * c2_t55
                   * c2_t56 * c2_t61
                   ) + c2_L5 * c2_t52 * c2_t56 * c2_t57 * c2_t58 * c2_t61) -
                 c2_L6 * c2_t54 * c2_t55 * c2_t59 * c2_t60 * c2_t61) + c2_L6 *
                c2_t57 *
                c2_t58 * c2_t59 * c2_t60 * c2_t61) - c2_L7 * c2_t54 * c2_t55 *
               c2_t59 * c2_t60 * c2_t61) + c2_L7 * c2_t57 * c2_t58 * c2_t59 *
    c2_t60
    * c2_t61;
  c2_u_x[3] = (-c2_t54) * (c2_t58 * c2_t61 + c2_t53 * c2_t55 * c2_t60) - c2_t57 *
    (c2_t55 * c2_t61 - c2_t53 * c2_t58 * c2_t60);
  c2_u_x[4] = c2_t54 * (c2_t55 * c2_t77 - c2_t53 * c2_t58 * c2_t59) - c2_t57 *
    (c2_t58 * c2_t77 + c2_t53 * c2_t55 * c2_t59);
  c2_u_x[5] = (-c2_t54) * (c2_t55 * c2_t81 + c2_t53 * c2_t56 * c2_t58) + c2_t57 *
    (c2_t58 * c2_t81 - c2_t53 * c2_t55 * c2_t56);
  c2_u_x[6] = ((((((c2_t62 + c2_t63) + c2_t64) + c2_t65) + c2_t66) + c2_L3 *
                c2_t55 * c2_t61) - c2_L3 * c2_t53 * c2_t58 * c2_t60) -
    c2_L9 * c2_t52 * c2_t59 * c2_t61;
  c2_u_x[7] = (((((((((c2_t67 - c2_L5 * c2_t52 * c2_t56) - c2_L6 * c2_t59 *
                      c2_t60) - c2_L7 * c2_t59 * c2_t60) - c2_L9 * c2_t52 *
                    c2_t53) + c2_L3 * c2_t52 * c2_t56 * c2_t58) + c2_L3 * c2_t53
                  * c2_t55 * c2_t59) - c2_L6 * c2_t52 * c2_t56 * c2_t61) - c2_L5
                * c2_t59
                * c2_t60 * c2_t61) - c2_L7 * c2_t52 * c2_t56 * c2_t61) + c2_L3 *
    c2_t58 * c2_t59 * c2_t60 * c2_t61;
  c2_u_x[8] = (((((((((c2_t68 + c2_t69) + c2_t70) + c2_t71) + c2_t72) - c2_L6 *
                   c2_t56 * c2_t60) - c2_L7 * c2_t56 * c2_t60) + c2_L3 *
                 c2_t53 * c2_t55 * c2_t56) - c2_L3 * c2_t52 * c2_t58 * c2_t59) -
               c2_L5 * c2_t56 * c2_t60 * c2_t61) + c2_L3 * c2_t56 * c2_t58 *
    c2_t60
    * c2_t61;
  c2_u_x[9] = c2_t74;
  c2_u_x[10] = c2_t79;
  c2_u_x[11] = c2_t82;
  c2_u_x[12] = ((((c2_t62 + c2_t63) + c2_t64) + c2_t65) + c2_t66) - c2_L9 *
    c2_t52 * c2_t59 * c2_t61;
  c2_u_x[13] = ((((((c2_t67 - c2_L5 * c2_t52 * c2_t56) - c2_L6 * c2_t59 * c2_t60)
                   - c2_L7 * c2_t59 * c2_t60) - c2_L9 * c2_t52 * c2_t53
                  ) - c2_L6 * c2_t52 * c2_t56 * c2_t61) - c2_L5 * c2_t59 *
                c2_t60 * c2_t61) - c2_L7 * c2_t52 * c2_t56 * c2_t61;
  c2_u_x[14] = ((((((c2_t68 + c2_t69) + c2_t70) + c2_t71) + c2_t72) - c2_L6 *
                 c2_t56 * c2_t60) - c2_L7 * c2_t56 * c2_t60) - c2_L5 *
    c2_t56 * c2_t60 * c2_t61;
  c2_u_x[15] = c2_t74;
  c2_u_x[16] = c2_t79;
  c2_u_x[17] = c2_t82;
  c2_u_x[18] = (-c2_t53) * (c2_L8 * c2_t56 - c2_L9 * c2_t59);
  c2_u_x[19] = ((-c2_L9) * c2_t61 + c2_L6 * c2_t53 * c2_t56) + c2_L7 * c2_t53 *
    c2_t56;
  c2_u_x[20] = (c2_L8 * c2_t61 - c2_L6 * c2_t53 * c2_t59) - c2_L7 * c2_t53 *
    c2_t59;
  c2_u_x[21] = c2_t61;
  c2_u_x[22] = c2_t53 * c2_t59;
  c2_u_x[23] = c2_t53 * c2_t56;
  c2_u_x[24] = c2_L8 * c2_t59 + c2_L9 * c2_t56;
  c2_u_x[25] = (-c2_t59) * c2_t73;
  c2_u_x[26] = (-c2_t56) * c2_t73;
  c2_u_x[27] = 0.0;
  c2_u_x[28] = c2_t56;
  c2_u_x[29] = -c2_t59;
  c2_u_x[30] = 0.0;
  c2_u_x[31] = -c2_L9;
  c2_u_x[32] = c2_L8;
  c2_u_x[33] = 1.0;
  c2_u_x[34] = 0.0;
  c2_u_x[35] = 0.0;
  for (c2_k = 1; c2_k < 37; c2_k = c2_k + 1) {
    c2_b_k = c2_k;
    c2_b_body_Jacobian[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 36, 1, 0) - 1] = c2_u_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_k), 1, 36, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(1, -52);
  sf_debug_symbol_scope_pop();
}

static void c2_AdjointInv(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c2_g[16], real_T c2_Adg_inv[36])
{
  uint32_T c2_debug_family_var_map[7];
  static const char *c2_sv1[7] = { "RT", "p", "ze", "nargin", "nargout", "g",
    "Adg_inv" };

  real_T c2_RT[9];
  real_T c2_p[3];
  real_T c2_ze[9];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  boolean_T c2_y;
  real_T c2_k;
  real_T c2_b_k;
  boolean_T c2_b0;
  int32_T c2_i65;
  int32_T c2_i66;
  int32_T c2_i67;
  int32_T c2_i68;
  int32_T c2_i69;
  int32_T c2_i70;
  int32_T c2_i71;
  real_T c2_w[3];
  uint32_T c2_b_debug_family_var_map[4];
  static const char *c2_sv2[4] = { "nargin", "nargout", "w", "wh" };

  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_wh[9];
  real_T c2_n;
  real_T c2_c_k;
  real_T c2_d_k;
  int32_T c2_i72;
  real_T c2_a[9];
  int32_T c2_i73;
  real_T c2_b[9];
  int32_T c2_i74;
  real_T c2_A[9];
  int32_T c2_i75;
  real_T c2_B[9];
  int32_T c2_i76;
  real_T c2_b_A[9];
  int32_T c2_i77;
  real_T c2_b_B[9];
  int32_T c2_i78;
  real_T c2_c_A[9];
  int32_T c2_i79;
  real_T c2_c_B[9];
  int32_T c2_i80;
  int32_T c2_i81;
  int32_T c2_i82;
  real_T c2_b_y[9];
  int32_T c2_i83;
  int32_T c2_i84;
  int32_T c2_i85;
  int32_T c2_i86;
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  int32_T c2_i90;
  int32_T c2_i91;
  int32_T c2_i92;
  int32_T c2_i93;
  int32_T c2_i94;
  int32_T c2_i95;
  int32_T c2_i96;
  int32_T c2_i97;
  int32_T c2_i98;
  int32_T c2_i99;
  int32_T c2_i100;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_sv1, c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c2_RT, c2_h_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c2_p, c2_c_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c2_ze, c2_h_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c2_nargin, c2_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c2_nargout, c2_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c2_g, c2_f_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c2_Adg_inv, c2_e_sf_marshall, 6U);
  CV_SCRIPT_FCN(2, 0);
  _SFD_SCRIPT_CALL(2, 3);
  c2_y = FALSE;
  c2_k = 1.0;
 label_1:
  ;
  if (c2_k <= 2.0) {
    c2_b_k = c2_k;
    c2_b0 = TRUE;
    if (!c2_b0) {
      c2_y = TRUE;
    } else {
      c2_k = c2_k + 1.0;
      goto label_1;
    }
  }

  CV_SCRIPT_IF(2, 0, c2_y);
  _SFD_SCRIPT_CALL(2, 7);
  c2_i65 = 0;
  for (c2_i66 = 0; c2_i66 < 3; c2_i66 = c2_i66 + 1) {
    c2_i67 = 0;
    for (c2_i68 = 0; c2_i68 < 3; c2_i68 = c2_i68 + 1) {
      c2_RT[c2_i68 + c2_i65] = c2_g[c2_i67 + c2_i66];
      c2_i67 = c2_i67 + 4;
    }

    c2_i65 = c2_i65 + 3;
  }

  _SFD_SCRIPT_CALL(2, 8);
  for (c2_i69 = 0; c2_i69 < 3; c2_i69 = c2_i69 + 1) {
    c2_p[c2_i69] = c2_g[c2_i69 + 12];
  }

  _SFD_SCRIPT_CALL(2, 9);
  for (c2_i70 = 0; c2_i70 < 9; c2_i70 = c2_i70 + 1) {
    c2_ze[c2_i70] = 0.0;
  }

  _SFD_SCRIPT_CALL(2, 10);
  for (c2_i71 = 0; c2_i71 < 3; c2_i71 = c2_i71 + 1) {
    c2_w[c2_i71] = c2_p[c2_i71];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c2_sv2, c2_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_b_nargin, c2_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c2_b_nargout, c2_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c2_w, c2_c_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c2_wh, c2_h_sf_marshall, 3U);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3, 3);
  c2_n = 0.0;
  c2_c_k = 1.0;
 label_2:
  ;
  if (c2_c_k <= 2.0) {
    c2_d_k = c2_c_k;
    if (3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c2_d_k), 1, 2, 1, 0) - 1) == 0.0) {
      c2_n = 0.0;
    } else {
      if (3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c2_d_k), 1, 2, 1, 0) - 1) > c2_n) {
        c2_n = 3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c2_d_k), 1, 2, 1, 0) - 1);
      }

      c2_c_k = c2_c_k + 1.0;
      goto label_2;
    }
  }

  CV_SCRIPT_IF(3, 0, c2_n != 3.0);

  /*      wh = diag(sym('wh',[1,3])); */
  /*      %wh=zeros(3); */
  /*      wh(1,1) = 0; */
  /*      wh(2,2) = 0; */
  /*      wh(3,3) = 0; */
  /*       */
  /*      wh(1,2) = -w(3); */
  /*      wh(1,3) = w(2); */
  /*      wh(2,1) = w(3); */
  /*      wh(2,3) = -w(1); */
  /*      wh(3,1) = -w(2); */
  /*      wh(3,2) = w(1); */
  _SFD_SCRIPT_CALL(3, 20);
  c2_wh[0] = 0.0;
  c2_wh[3] = -c2_w[2];
  c2_wh[6] = c2_w[1];
  c2_wh[1] = c2_w[2];
  c2_wh[4] = 0.0;
  c2_wh[7] = -c2_w[0];
  c2_wh[2] = -c2_w[1];
  c2_wh[5] = c2_w[0];
  c2_wh[8] = 0.0;
  _SFD_SCRIPT_CALL(3, -20);
  sf_debug_symbol_scope_pop();
  for (c2_i72 = 0; c2_i72 < 9; c2_i72 = c2_i72 + 1) {
    c2_a[c2_i72] = -c2_RT[c2_i72];
  }

  for (c2_i73 = 0; c2_i73 < 9; c2_i73 = c2_i73 + 1) {
    c2_b[c2_i73] = c2_wh[c2_i73];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i74 = 0; c2_i74 < 9; c2_i74 = c2_i74 + 1) {
    c2_A[c2_i74] = c2_a[c2_i74];
  }

  for (c2_i75 = 0; c2_i75 < 9; c2_i75 = c2_i75 + 1) {
    c2_B[c2_i75] = c2_b[c2_i75];
  }

  for (c2_i76 = 0; c2_i76 < 9; c2_i76 = c2_i76 + 1) {
    c2_b_A[c2_i76] = c2_A[c2_i76];
  }

  for (c2_i77 = 0; c2_i77 < 9; c2_i77 = c2_i77 + 1) {
    c2_b_B[c2_i77] = c2_B[c2_i77];
  }

  for (c2_i78 = 0; c2_i78 < 9; c2_i78 = c2_i78 + 1) {
    c2_c_A[c2_i78] = c2_b_A[c2_i78];
  }

  for (c2_i79 = 0; c2_i79 < 9; c2_i79 = c2_i79 + 1) {
    c2_c_B[c2_i79] = c2_b_B[c2_i79];
  }

  for (c2_i80 = 0; c2_i80 < 3; c2_i80 = c2_i80 + 1) {
    c2_i81 = 0;
    for (c2_i82 = 0; c2_i82 < 3; c2_i82 = c2_i82 + 1) {
      c2_b_y[c2_i81 + c2_i80] = 0.0;
      c2_i83 = 0;
      for (c2_i84 = 0; c2_i84 < 3; c2_i84 = c2_i84 + 1) {
        c2_b_y[c2_i81 + c2_i80] = c2_b_y[c2_i81 + c2_i80] + c2_c_A[c2_i83 +
          c2_i80] * c2_c_B[c2_i84 + c2_i81];
        c2_i83 = c2_i83 + 3;
      }

      c2_i81 = c2_i81 + 3;
    }
  }

  c2_i85 = 0;
  c2_i86 = 0;
  for (c2_i87 = 0; c2_i87 < 3; c2_i87 = c2_i87 + 1) {
    for (c2_i88 = 0; c2_i88 < 3; c2_i88 = c2_i88 + 1) {
      c2_Adg_inv[c2_i88 + c2_i85] = c2_RT[c2_i88 + c2_i86];
    }

    c2_i85 = c2_i85 + 6;
    c2_i86 = c2_i86 + 3;
  }

  c2_i89 = 0;
  c2_i90 = 0;
  for (c2_i91 = 0; c2_i91 < 3; c2_i91 = c2_i91 + 1) {
    for (c2_i92 = 0; c2_i92 < 3; c2_i92 = c2_i92 + 1) {
      c2_Adg_inv[(c2_i92 + c2_i89) + 18] = c2_b_y[c2_i92 + c2_i90];
    }

    c2_i89 = c2_i89 + 6;
    c2_i90 = c2_i90 + 3;
  }

  c2_i93 = 0;
  c2_i94 = 0;
  for (c2_i95 = 0; c2_i95 < 3; c2_i95 = c2_i95 + 1) {
    for (c2_i96 = 0; c2_i96 < 3; c2_i96 = c2_i96 + 1) {
      c2_Adg_inv[(c2_i96 + c2_i93) + 3] = c2_ze[c2_i96 + c2_i94];
    }

    c2_i93 = c2_i93 + 6;
    c2_i94 = c2_i94 + 3;
  }

  c2_i97 = 0;
  c2_i98 = 0;
  for (c2_i99 = 0; c2_i99 < 3; c2_i99 = c2_i99 + 1) {
    for (c2_i100 = 0; c2_i100 < 3; c2_i100 = c2_i100 + 1) {
      c2_Adg_inv[(c2_i100 + c2_i97) + 21] = c2_RT[c2_i100 + c2_i98];
    }

    c2_i97 = c2_i97 + 6;
    c2_i98 = c2_i98 + 3;
  }

  /* Adg_inv(4:6,4:6) = RT; */
  _SFD_SCRIPT_CALL(2, -10);
  sf_debug_symbol_scope_pop();
}

static void c2_eml_scalar_eg(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c2_eps(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
}

static void c2_eml_matlab_zgetrf(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c2_A[36], real_T c2_b_A[36], int32_T
  c2_ipiv[6], int32_T *c2_info)
{
  int32_T c2_i101;
  int32_T c2_i102;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_jm1;
  int32_T c2_b;
  int32_T c2_mmj;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_b_b;
  int32_T c2_jj;
  int32_T c2_c_a;
  int32_T c2_jp1j;
  int32_T c2_d_a;
  int32_T c2_b_c;
  int32_T c2_i103;
  real_T c2_c_A[36];
  int32_T c2_e_a;
  int32_T c2_jpiv_offset;
  int32_T c2_f_a;
  int32_T c2_c_b;
  int32_T c2_jpiv;
  int32_T c2_g_a;
  int32_T c2_d_b;
  int32_T c2_c_c;
  int32_T c2_e_b;
  int32_T c2_jrow;
  int32_T c2_h_a;
  int32_T c2_f_b;
  int32_T c2_jprow;
  int32_T c2_i104;
  real_T c2_x[36];
  int32_T c2_ix0;
  int32_T c2_iy0;
  int32_T c2_i105;
  int32_T c2_i106;
  real_T c2_b_x[36];
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_i107;
  real_T c2_c_x[36];
  int32_T c2_i108;
  real_T c2_d_x[36];
  real_T c2_e_x[36];
  int32_T c2_i109;
  int32_T c2_i110;
  int32_T c2_b_jp1j;
  int32_T c2_i_a;
  int32_T c2_d_c;
  int32_T c2_j_a;
  int32_T c2_g_b;
  int32_T c2_loop_ub;
  int32_T c2_i;
  int32_T c2_b_i;
  real_T c2_f_x;
  real_T c2_y;
  real_T c2_g_x;
  real_T c2_b_y;
  real_T c2_z;
  int32_T c2_h_b;
  int32_T c2_e_c;
  int32_T c2_k_a;
  int32_T c2_f_c;
  int32_T c2_l_a;
  int32_T c2_g_c;
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_i111;
  real_T c2_d_A[36];
  int32_T c2_ia0;
  int32_T c2_i112;
  int32_T c2_b_m;
  int32_T c2_b_n;
  int32_T c2_d_ix0;
  int32_T c2_d_iy0;
  int32_T c2_i113;
  real_T c2_e_A[36];
  int32_T c2_b_ia0;
  int32_T c2_i114;
  int32_T c2_c_m;
  int32_T c2_c_n;
  int32_T c2_e_ix0;
  int32_T c2_e_iy0;
  int32_T c2_i115;
  real_T c2_f_A[36];
  int32_T c2_c_ia0;
  int32_T c2_i116;
  int32_T c2_i117;
  real_T c2_g_A[36];
  for (c2_i101 = 0; c2_i101 < 36; c2_i101 = c2_i101 + 1) {
    c2_b_A[c2_i101] = c2_A[c2_i101];
  }

  c2_eps(chartInstance);
  for (c2_i102 = 0; c2_i102 < 6; c2_i102 = c2_i102 + 1) {
    c2_ipiv[c2_i102] = 1 + c2_i102;
  }

  *c2_info = 0;
  for (c2_j = 1; c2_j < 6; c2_j = c2_j + 1) {
    c2_b_j = c2_j;
    c2_a = c2_b_j;
    c2_jm1 = c2_a - 1;
    c2_b = c2_b_j;
    c2_mmj = 6 - c2_b;
    c2_b_a = c2_jm1;
    c2_c = c2_b_a * 7;
    c2_b_b = c2_c;
    c2_jj = 1 + c2_b_b;
    c2_c_a = c2_jj;
    c2_jp1j = c2_c_a + 1;
    c2_d_a = c2_mmj;
    c2_b_c = c2_d_a + 1;
    for (c2_i103 = 0; c2_i103 < 36; c2_i103 = c2_i103 + 1) {
      c2_c_A[c2_i103] = c2_b_A[c2_i103];
    }

    c2_e_a = c2_eml_ixamax(chartInstance, c2_b_c, c2_c_A, c2_jj);
    c2_jpiv_offset = c2_e_a - 1;
    c2_f_a = c2_jj;
    c2_c_b = c2_jpiv_offset;
    c2_jpiv = c2_f_a + c2_c_b;
    if (c2_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_jpiv), 1, 36, 1, 0) - 1] != 0.0) {
      if ((real_T)c2_jpiv_offset != 0.0) {
        c2_g_a = c2_b_j;
        c2_d_b = c2_jpiv_offset;
        c2_c_c = c2_g_a + c2_d_b;
        c2_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_j), 1, 6, 1, 0) - 1] = c2_c_c;
        c2_e_b = c2_jm1;
        c2_jrow = 1 + c2_e_b;
        c2_h_a = c2_jrow;
        c2_f_b = c2_jpiv_offset;
        c2_jprow = c2_h_a + c2_f_b;
        for (c2_i104 = 0; c2_i104 < 36; c2_i104 = c2_i104 + 1) {
          c2_x[c2_i104] = c2_b_A[c2_i104];
        }

        c2_ix0 = c2_jrow;
        c2_iy0 = c2_jprow;
        for (c2_i105 = 0; c2_i105 < 36; c2_i105 = c2_i105 + 1) {
          c2_b_A[c2_i105] = c2_x[c2_i105];
        }

        for (c2_i106 = 0; c2_i106 < 36; c2_i106 = c2_i106 + 1) {
          c2_b_x[c2_i106] = c2_b_A[c2_i106];
        }

        c2_b_ix0 = c2_ix0;
        c2_b_iy0 = c2_iy0;
        for (c2_i107 = 0; c2_i107 < 36; c2_i107 = c2_i107 + 1) {
          c2_c_x[c2_i107] = c2_b_x[c2_i107];
        }

        for (c2_i108 = 0; c2_i108 < 36; c2_i108 = c2_i108 + 1) {
          c2_d_x[c2_i108] = c2_c_x[c2_i108];
        }

        c2_ceval_xswap(chartInstance, 6, c2_d_x, c2_b_ix0, 6, c2_b_iy0, 6,
                       c2_e_x);
        for (c2_i109 = 0; c2_i109 < 36; c2_i109 = c2_i109 + 1) {
          c2_c_x[c2_i109] = c2_e_x[c2_i109];
        }

        for (c2_i110 = 0; c2_i110 < 36; c2_i110 = c2_i110 + 1) {
          c2_b_A[c2_i110] = c2_c_x[c2_i110];
        }
      }

      c2_b_jp1j = c2_jp1j;
      c2_i_a = c2_mmj;
      c2_d_c = c2_i_a - 1;
      c2_j_a = c2_jp1j;
      c2_g_b = c2_d_c;
      c2_loop_ub = c2_j_a + c2_g_b;
      for (c2_i = c2_b_jp1j; c2_i <= c2_loop_ub; c2_i = c2_i + 1) {
        c2_b_i = c2_i;
        c2_f_x = c2_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 36, 1, 0) - 1];
        c2_y = c2_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_jj), 1, 36, 1, 0) - 1];
        c2_g_x = c2_f_x;
        c2_b_y = c2_y;
        c2_z = c2_g_x / c2_b_y;
        c2_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_i), 1, 36, 1, 0) - 1] = c2_z;
      }
    } else {
      *c2_info = c2_b_j;
    }

    c2_h_b = c2_b_j;
    c2_e_c = 6 - c2_h_b;
    c2_k_a = c2_jj;
    c2_f_c = c2_k_a + 6;
    c2_l_a = c2_jj;
    c2_g_c = c2_l_a + 7;
    c2_m = c2_mmj;
    c2_n = c2_e_c;
    c2_c_ix0 = c2_jp1j;
    c2_c_iy0 = c2_f_c;
    for (c2_i111 = 0; c2_i111 < 36; c2_i111 = c2_i111 + 1) {
      c2_d_A[c2_i111] = c2_b_A[c2_i111];
    }

    c2_ia0 = c2_g_c;
    for (c2_i112 = 0; c2_i112 < 36; c2_i112 = c2_i112 + 1) {
      c2_b_A[c2_i112] = c2_d_A[c2_i112];
    }

    c2_b_m = c2_m;
    c2_b_n = c2_n;
    c2_d_ix0 = c2_c_ix0;
    c2_d_iy0 = c2_c_iy0;
    for (c2_i113 = 0; c2_i113 < 36; c2_i113 = c2_i113 + 1) {
      c2_e_A[c2_i113] = c2_b_A[c2_i113];
    }

    c2_b_ia0 = c2_ia0;
    for (c2_i114 = 0; c2_i114 < 36; c2_i114 = c2_i114 + 1) {
      c2_b_A[c2_i114] = c2_e_A[c2_i114];
    }

    c2_c_m = c2_b_m;
    c2_c_n = c2_b_n;
    c2_e_ix0 = c2_d_ix0;
    c2_e_iy0 = c2_d_iy0;
    for (c2_i115 = 0; c2_i115 < 36; c2_i115 = c2_i115 + 1) {
      c2_f_A[c2_i115] = c2_b_A[c2_i115];
    }

    c2_c_ia0 = c2_b_ia0;
    for (c2_i116 = 0; c2_i116 < 36; c2_i116 = c2_i116 + 1) {
      c2_b_A[c2_i116] = c2_f_A[c2_i116];
    }

    if ((real_T)c2_c_m < 1.0) {
    } else if ((real_T)c2_c_n < 1.0) {
    } else {
      for (c2_i117 = 0; c2_i117 < 36; c2_i117 = c2_i117 + 1) {
        c2_g_A[c2_i117] = c2_b_A[c2_i117];
      }

      c2_ceval_xger(chartInstance, c2_c_m, c2_c_n, -1.0, c2_e_ix0, 1, c2_e_iy0,
                    6, c2_g_A, c2_c_ia0, 6, c2_b_A);
      goto label_1;
    }

   label_1:
    ;
  }

  if ((real_T)*c2_info == 0.0) {
    if (!(c2_b_A[35] != 0.0)) {
      *c2_info = 6;
      return;
    }
  }
}

static int32_T c2_eml_ixamax(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[36], int32_T c2_ix0)
{
  int32_T c2_b_n;
  int32_T c2_i118;
  real_T c2_b_x[36];
  int32_T c2_b_ix0;
  int32_T c2_i119;
  real_T c2_c_x[36];
  c2_b_n = c2_n;
  for (c2_i118 = 0; c2_i118 < 36; c2_i118 = c2_i118 + 1) {
    c2_b_x[c2_i118] = c2_x[c2_i118];
  }

  c2_b_ix0 = c2_ix0;
  for (c2_i119 = 0; c2_i119 < 36; c2_i119 = c2_i119 + 1) {
    c2_c_x[c2_i119] = c2_b_x[c2_i119];
  }

  return c2_ceval_ixamax(chartInstance, c2_b_n, c2_c_x, c2_b_ix0, 1);
}

static int32_T c2_ceval_ixamax(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[36], int32_T c2_ix0,
  int32_T c2_incx)
{
  return idamax32(&c2_n, &c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c2_ix0), 1, 36, 1, 0) - 1], &
                  c2_incx);
}

static void c2_ceval_xswap(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[36], int32_T c2_ix0,
  int32_T c2_incx, int32_T c2_iy0, int32_T c2_incy, real_T c2_b_x[36])
{
  int32_T c2_i120;

  /* Empty Loop. */
  for (c2_i120 = 0; c2_i120 < 36; c2_i120 = c2_i120 + 1) {
    c2_b_x[c2_i120] = c2_x[c2_i120];
  }

  dswap32(&c2_n, &c2_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c2_ix0), 1, 36, 1, 0) - 1], &c2_incx
          , &c2_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
            "", (real_T)c2_iy0), 1, 36, 1, 0) - 1], &c2_incy);
}

static void c2_ceval_xger(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_alpha1,
  int32_T c2_ix0, int32_T c2_incx, int32_T c2_iy0, int32_T c2_incy, real_T c2_A
  [36], int32_T c2_ia0, int32_T c2_lda, real_T c2_b_A[36]
  )
{
  int32_T c2_i121;
  for (c2_i121 = 0; c2_i121 < 36; c2_i121 = c2_i121 + 1) {
    c2_b_A[c2_i121] = c2_A[c2_i121];
  }

  dger32(&c2_m, &c2_n, &c2_alpha1, &c2_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_ix0), 1, 36, 1,
          0) - 1], &c2_incx, &c2_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_iy0), 1, 36, 1, 0) - 1], &
         c2_incy, &c2_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_ia0), 1, 36, 1, 0) - 1], &c2_lda);
}

static void c2_eml_warning(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  int32_T c2_i122;
  static char_T c2_cv0[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 's', 'i', 'n',
    'g', 'u', 'l', 'a', 'r', 'M', 'a', 't', 'r', 'i', 'x'
  };

  char_T c2_u[21];
  const mxArray *c2_y = NULL;
  int32_T c2_i123;
  static char_T c2_cv1[40] = { 'M', 'a', 't', 'r', 'i', 'x', ' ', 'i', 's', ' ',
    's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', ' ', 't', 'o'
    , ' ', 'w', 'o', 'r', 'k', 'i', 'n', 'g', ' ', 'p', 'r', 'e', 'c', 'i', 's',
    'i', 'o', 'n', '.' };

  char_T c2_b_u[40];
  const mxArray *c2_b_y = NULL;
  for (c2_i122 = 0; c2_i122 < 21; c2_i122 = c2_i122 + 1) {
    c2_u[c2_i122] = c2_cv0[c2_i122];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 21));
  for (c2_i123 = 0; c2_i123 < 40; c2_i123 = c2_i123 + 1) {
    c2_b_u[c2_i123] = c2_cv1[c2_i123];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
  sf_mex_call_debug("warning", 0U, 2U, 14, c2_y, 14, c2_b_y);
}

static void c2_eml_blas_xtrsm(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_alpha1,
  real_T c2_A[36], int32_T c2_ia0, int32_T c2_lda, real_T c2_B[36], int32_T
  c2_ib0, int32_T c2_ldb, real_T c2_b_B[36])
{
  int32_T c2_i124;
  int32_T c2_i125;
  real_T c2_b_A[36];
  int32_T c2_i126;
  real_T c2_c_B[36];
  for (c2_i124 = 0; c2_i124 < 36; c2_i124 = c2_i124 + 1) {
    c2_b_B[c2_i124] = c2_B[c2_i124];
  }

  for (c2_i125 = 0; c2_i125 < 36; c2_i125 = c2_i125 + 1) {
    c2_b_A[c2_i125] = c2_A[c2_i125];
  }

  for (c2_i126 = 0; c2_i126 < 36; c2_i126 = c2_i126 + 1) {
    c2_c_B[c2_i126] = c2_b_B[c2_i126];
  }

  c2_ceval_xtrsm(chartInstance, c2_m, c2_n, c2_alpha1, c2_b_A, c2_ia0, c2_lda,
                 c2_c_B, c2_ib0, c2_ldb, c2_b_B);
}

static void c2_ceval_xtrsm(SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_alpha1,
  real_T c2_A[36], int32_T c2_ia0, int32_T c2_lda, real_T c2_B[36], int32_T
  c2_ib0, int32_T c2_ldb, real_T c2_b_B[36])
{
  char_T c2_SIDE;
  char_T c2_UPLO;
  char_T c2_TRANSA;
  char_T c2_DIAGA;
  int32_T c2_i127;
  c2_SIDE = 'L';
  c2_UPLO = 'L';
  c2_TRANSA = 'N';
  c2_DIAGA = 'U';
  for (c2_i127 = 0; c2_i127 < 36; c2_i127 = c2_i127 + 1) {
    c2_b_B[c2_i127] = c2_B[c2_i127];
  }

  dtrsm32(&c2_SIDE, &c2_UPLO, &c2_TRANSA, &c2_DIAGA, &c2_m, &c2_n, &c2_alpha1,
          &c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c2_ia0), 1, 36, 1, 0) - 1], &c2_lda,
          &c2_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c2_ib0), 1, 36, 1, 0) - 1], &c2_ldb);
}

static void c2_b_eml_blas_xtrsm(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_alpha1,
  real_T c2_A[36], int32_T c2_ia0, int32_T c2_lda, real_T c2_B[36], int32_T
  c2_ib0, int32_T c2_ldb, real_T c2_b_B[36])
{
  int32_T c2_i128;
  int32_T c2_i129;
  real_T c2_b_A[36];
  int32_T c2_i130;
  real_T c2_c_B[36];
  for (c2_i128 = 0; c2_i128 < 36; c2_i128 = c2_i128 + 1) {
    c2_b_B[c2_i128] = c2_B[c2_i128];
  }

  for (c2_i129 = 0; c2_i129 < 36; c2_i129 = c2_i129 + 1) {
    c2_b_A[c2_i129] = c2_A[c2_i129];
  }

  for (c2_i130 = 0; c2_i130 < 36; c2_i130 = c2_i130 + 1) {
    c2_c_B[c2_i130] = c2_b_B[c2_i130];
  }

  c2_b_ceval_xtrsm(chartInstance, c2_m, c2_n, c2_alpha1, c2_b_A, c2_ia0, c2_lda,
                   c2_c_B, c2_ib0, c2_ldb, c2_b_B);
}

static void c2_b_ceval_xtrsm(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_alpha1,
  real_T c2_A[36], int32_T c2_ia0, int32_T c2_lda, real_T c2_B[36], int32_T
  c2_ib0, int32_T c2_ldb, real_T c2_b_B[36])
{
  char_T c2_SIDE;
  char_T c2_UPLO;
  char_T c2_TRANSA;
  char_T c2_DIAGA;
  int32_T c2_i131;
  c2_SIDE = 'L';
  c2_UPLO = 'U';
  c2_TRANSA = 'N';
  c2_DIAGA = 'N';
  for (c2_i131 = 0; c2_i131 < 36; c2_i131 = c2_i131 + 1) {
    c2_b_B[c2_i131] = c2_B[c2_i131];
  }

  dtrsm32(&c2_SIDE, &c2_UPLO, &c2_TRANSA, &c2_DIAGA, &c2_m, &c2_n, &c2_alpha1,
          &c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c2_ia0), 1, 36, 1, 0) - 1], &c2_lda,
          &c2_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c2_ib0), 1, 36, 1, 0) - 1], &c2_ldb);
}

static void c2_b_eml_scalar_eg(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static const mxArray *c2_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  int32_T c2_i132;
  real_T c2_b_u[6];
  int32_T c2_i133;
  real_T c2_c_u[6];
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  for (c2_i132 = 0; c2_i132 < 6; c2_i132 = c2_i132 + 1) {
    c2_b_u[c2_i132] = (*((real_T (*)[6])c2_u))[c2_i132];
  }

  for (c2_i133 = 0; c2_i133 < 6; c2_i133 = c2_i133 + 1) {
    c2_c_u[c2_i133] = c2_b_u[c2_i133];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 1, 6));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static const mxArray *c2_b_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  int32_T c2_i134;
  real_T c2_b_u[9];
  int32_T c2_i135;
  real_T c2_c_u[9];
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  for (c2_i134 = 0; c2_i134 < 9; c2_i134 = c2_i134 + 1) {
    c2_b_u[c2_i134] = (*((real_T (*)[9])c2_u))[c2_i134];
  }

  for (c2_i135 = 0; c2_i135 < 9; c2_i135 = c2_i135 + 1) {
    c2_c_u[c2_i135] = c2_b_u[c2_i135];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 1, 9));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static const mxArray *c2_c_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  int32_T c2_i136;
  real_T c2_b_u[3];
  int32_T c2_i137;
  real_T c2_c_u[3];
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  for (c2_i136 = 0; c2_i136 < 3; c2_i136 = c2_i136 + 1) {
    c2_b_u[c2_i136] = (*((real_T (*)[3])c2_u))[c2_i136];
  }

  for (c2_i137 = 0; c2_i137 < 3; c2_i137 = c2_i137 + 1) {
    c2_c_u[c2_i137] = c2_b_u[c2_i137];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 1, 3));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static const mxArray *c2_d_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_b_u = *((real_T *)c2_u);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static const mxArray *c2_e_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  int32_T c2_i138;
  int32_T c2_i139;
  int32_T c2_i140;
  real_T c2_b_u[36];
  int32_T c2_i141;
  int32_T c2_i142;
  int32_T c2_i143;
  real_T c2_c_u[36];
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_i138 = 0;
  for (c2_i139 = 0; c2_i139 < 6; c2_i139 = c2_i139 + 1) {
    for (c2_i140 = 0; c2_i140 < 6; c2_i140 = c2_i140 + 1) {
      c2_b_u[c2_i140 + c2_i138] = (*((real_T (*)[36])c2_u))[c2_i140 + c2_i138];
    }

    c2_i138 = c2_i138 + 6;
  }

  c2_i141 = 0;
  for (c2_i142 = 0; c2_i142 < 6; c2_i142 = c2_i142 + 1) {
    for (c2_i143 = 0; c2_i143 < 6; c2_i143 = c2_i143 + 1) {
      c2_c_u[c2_i143 + c2_i141] = c2_b_u[c2_i143 + c2_i141];
    }

    c2_i141 = c2_i141 + 6;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 6, 6));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static const mxArray *c2_f_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  int32_T c2_i144;
  int32_T c2_i145;
  int32_T c2_i146;
  real_T c2_b_u[16];
  int32_T c2_i147;
  int32_T c2_i148;
  int32_T c2_i149;
  real_T c2_c_u[16];
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_i144 = 0;
  for (c2_i145 = 0; c2_i145 < 4; c2_i145 = c2_i145 + 1) {
    for (c2_i146 = 0; c2_i146 < 4; c2_i146 = c2_i146 + 1) {
      c2_b_u[c2_i146 + c2_i144] = (*((real_T (*)[16])c2_u))[c2_i146 + c2_i144];
    }

    c2_i144 = c2_i144 + 4;
  }

  c2_i147 = 0;
  for (c2_i148 = 0; c2_i148 < 4; c2_i148 = c2_i148 + 1) {
    for (c2_i149 = 0; c2_i149 < 4; c2_i149 = c2_i149 + 1) {
      c2_c_u[c2_i149 + c2_i147] = c2_b_u[c2_i149 + c2_i147];
    }

    c2_i147 = c2_i147 + 4;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 4, 4));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static const mxArray *c2_g_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  int32_T c2_i150;
  real_T c2_b_u[6];
  int32_T c2_i151;
  real_T c2_c_u[6];
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  for (c2_i150 = 0; c2_i150 < 6; c2_i150 = c2_i150 + 1) {
    c2_b_u[c2_i150] = (*((real_T (*)[6])c2_u))[c2_i150];
  }

  for (c2_i151 = 0; c2_i151 < 6; c2_i151 = c2_i151 + 1) {
    c2_c_u[c2_i151] = c2_b_u[c2_i151];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 1, 6));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static const mxArray *c2_h_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  int32_T c2_i152;
  int32_T c2_i153;
  int32_T c2_i154;
  real_T c2_b_u[9];
  int32_T c2_i155;
  int32_T c2_i156;
  int32_T c2_i157;
  real_T c2_c_u[9];
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_i152 = 0;
  for (c2_i153 = 0; c2_i153 < 3; c2_i153 = c2_i153 + 1) {
    for (c2_i154 = 0; c2_i154 < 3; c2_i154 = c2_i154 + 1) {
      c2_b_u[c2_i154 + c2_i152] = (*((real_T (*)[9])c2_u))[c2_i154 + c2_i152];
    }

    c2_i152 = c2_i152 + 3;
  }

  c2_i155 = 0;
  for (c2_i156 = 0; c2_i156 < 3; c2_i156 = c2_i156 + 1) {
    for (c2_i157 = 0; c2_i157 < 3; c2_i157 = c2_i157 + 1) {
      c2_c_u[c2_i157 + c2_i155] = c2_b_u[c2_i157 + c2_i155];
    }

    c2_i155 = c2_i155 + 3;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 3, 3));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

const mxArray *sf_c2_EulerPIDJoint_Copy_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_ResolvedFunctionInfo c2_info[100];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i158;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  c2_b_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 100));
  for (c2_i158 = 0; c2_i158 < 100; c2_i158 = c2_i158 + 1) {
    c2_r0 = &c2_info[c2_i158];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context",
                    "nameCaptureInfo", c2_i158);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name",
                    "nameCaptureInfo", c2_i158);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c2_i158);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c2_i158);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c2_i158);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo",
                    c2_i158);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo",
                    c2_i158);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[100])
{
  c2_info[0].context = "";
  c2_info[0].name = "zeros";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved = "[B]zeros";
  c2_info[0].fileLength = 0U;
  c2_info[0].fileTime1 = 0U;
  c2_info[0].fileTime2 = 0U;
  c2_info[1].context = "";
  c2_info[1].name = "ctranspose";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved = "[B]ctranspose";
  c2_info[1].fileLength = 0U;
  c2_info[1].fileTime1 = 0U;
  c2_info[1].fileTime2 = 0U;
  c2_info[2].context = "";
  c2_info[2].name = "fwd_kin";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c2_info[2].fileLength = 3324U;
  c2_info[2].fileTime1 = 1366778959U;
  c2_info[2].fileTime2 = 0U;
  c2_info[3].context = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c2_info[3].name = "cos";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[3].fileLength = 324U;
  c2_info[3].fileTime1 = 1203422750U;
  c2_info[3].fileTime2 = 0U;
  c2_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[4].name = "nargin";
  c2_info[4].dominantType = "";
  c2_info[4].resolved = "[B]nargin";
  c2_info[4].fileLength = 0U;
  c2_info[4].fileTime1 = 0U;
  c2_info[4].fileTime2 = 0U;
  c2_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[5].name = "gt";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved = "[B]gt";
  c2_info[5].fileLength = 0U;
  c2_info[5].fileTime1 = 0U;
  c2_info[5].fileTime2 = 0U;
  c2_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[6].name = "isa";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved = "[B]isa";
  c2_info[6].fileLength = 0U;
  c2_info[6].fileTime1 = 0U;
  c2_info[6].fileTime2 = 0U;
  c2_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[7].name = "eml_scalar_cos";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c2_info[7].fileLength = 602U;
  c2_info[7].fileTime1 = 1209309186U;
  c2_info[7].fileTime2 = 0U;
  c2_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c2_info[8].name = "isreal";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved = "[B]isreal";
  c2_info[8].fileLength = 0U;
  c2_info[8].fileTime1 = 0U;
  c2_info[8].fileTime2 = 0U;
  c2_info[9].context = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c2_info[9].name = "sin";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c2_info[9].fileLength = 324U;
  c2_info[9].fileTime1 = 1203422842U;
  c2_info[9].fileTime2 = 0U;
  c2_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c2_info[10].name = "eml_scalar_sin";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c2_info[10].fileLength = 601U;
  c2_info[10].fileTime1 = 1209309190U;
  c2_info[10].fileTime2 = 0U;
  c2_info[11].context = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c2_info[11].name = "times";
  c2_info[11].dominantType = "double";
  c2_info[11].resolved = "[B]times";
  c2_info[11].fileLength = 0U;
  c2_info[11].fileTime1 = 0U;
  c2_info[11].fileTime2 = 0U;
  c2_info[12].context = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c2_info[12].name = "plus";
  c2_info[12].dominantType = "double";
  c2_info[12].resolved = "[B]plus";
  c2_info[12].fileLength = 0U;
  c2_info[12].fileTime1 = 0U;
  c2_info[12].fileTime2 = 0U;
  c2_info[13].context = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c2_info[13].name = "minus";
  c2_info[13].dominantType = "double";
  c2_info[13].resolved = "[B]minus";
  c2_info[13].fileLength = 0U;
  c2_info[13].fileTime1 = 0U;
  c2_info[13].fileTime2 = 0U;
  c2_info[14].context = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c2_info[14].name = "uminus";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved = "[B]uminus";
  c2_info[14].fileLength = 0U;
  c2_info[14].fileTime1 = 0U;
  c2_info[14].fileTime2 = 0U;
  c2_info[15].context = "[E]D:/Learn/Project_Matlab/Fanuc/fwd_kin.m";
  c2_info[15].name = "reshape";
  c2_info[15].dominantType = "double";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c2_info[15].fileLength = 4857U;
  c2_info[15].fileTime1 = 1242276774U;
  c2_info[15].fileTime2 = 0U;
  c2_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c2_info[16].name = "eml_index_class";
  c2_info[16].dominantType = "";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[16].fileLength = 909U;
  c2_info[16].fileTime1 = 1192445182U;
  c2_info[16].fileTime2 = 0U;
  c2_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c2_info[17].name = "cast";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved = "[B]cast";
  c2_info[17].fileLength = 0U;
  c2_info[17].fileTime1 = 0U;
  c2_info[17].fileTime2 = 0U;
  c2_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c2_info[18].name = "size";
  c2_info[18].dominantType = "double";
  c2_info[18].resolved = "[B]size";
  c2_info[18].fileLength = 0U;
  c2_info[18].fileTime1 = 0U;
  c2_info[18].fileTime2 = 0U;
  c2_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c2_info[19].name = "eq";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved = "[B]eq";
  c2_info[19].fileLength = 0U;
  c2_info[19].fileTime1 = 0U;
  c2_info[19].fileTime2 = 0U;
  c2_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c2_info[20].name = "eml_assert_valid_size_arg";
  c2_info[20].dominantType = "double";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[20].fileLength = 3315U;
  c2_info[20].fileTime1 = 1256367816U;
  c2_info[20].fileTime2 = 0U;
  c2_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isVariableSizing";
  c2_info[21].name = "false";
  c2_info[21].dominantType = "";
  c2_info[21].resolved = "[B]false";
  c2_info[21].fileLength = 0U;
  c2_info[21].fileTime1 = 0U;
  c2_info[21].fileTime2 = 0U;
  c2_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isVariableSizing";
  c2_info[22].name = "not";
  c2_info[22].dominantType = "logical";
  c2_info[22].resolved = "[B]not";
  c2_info[22].fileLength = 0U;
  c2_info[22].fileTime1 = 0U;
  c2_info[22].fileTime2 = 0U;
  c2_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[23].name = "isvector";
  c2_info[23].dominantType = "double";
  c2_info[23].resolved = "[B]isvector";
  c2_info[23].fileLength = 0U;
  c2_info[23].fileTime1 = 0U;
  c2_info[23].fileTime2 = 0U;
  c2_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c2_info[24].name = "isinteger";
  c2_info[24].dominantType = "double";
  c2_info[24].resolved = "[B]isinteger";
  c2_info[24].fileLength = 0U;
  c2_info[24].fileTime1 = 0U;
  c2_info[24].fileTime2 = 0U;
  c2_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c2_info[25].name = "ne";
  c2_info[25].dominantType = "double";
  c2_info[25].resolved = "[B]ne";
  c2_info[25].fileLength = 0U;
  c2_info[25].fileTime1 = 0U;
  c2_info[25].fileTime2 = 0U;
  c2_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c2_info[26].name = "isinf";
  c2_info[26].dominantType = "double";
  c2_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c2_info[26].fileLength = 541U;
  c2_info[26].fileTime1 = 1271383988U;
  c2_info[26].fileTime2 = 0U;
  c2_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c2_info[27].name = "true";
  c2_info[27].dominantType = "";
  c2_info[27].resolved = "[B]true";
  c2_info[27].fileLength = 0U;
  c2_info[27].fileTime1 = 0U;
  c2_info[27].fileTime2 = 0U;
  c2_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c2_info[28].name = "le";
  c2_info[28].dominantType = "double";
  c2_info[28].resolved = "[B]le";
  c2_info[28].fileLength = 0U;
  c2_info[28].fileTime1 = 0U;
  c2_info[28].fileTime2 = 0U;
  c2_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c2_info[29].name = "double";
  c2_info[29].dominantType = "double";
  c2_info[29].resolved = "[B]double";
  c2_info[29].fileLength = 0U;
  c2_info[29].fileTime1 = 0U;
  c2_info[29].fileTime2 = 0U;
  c2_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c2_info[30].name = "mtimes";
  c2_info[30].dominantType = "double";
  c2_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[30].fileLength = 3425U;
  c2_info[30].fileTime1 = 1251010272U;
  c2_info[30].fileTime2 = 0U;
  c2_info[31].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[31].name = "isscalar";
  c2_info[31].dominantType = "double";
  c2_info[31].resolved = "[B]isscalar";
  c2_info[31].fileLength = 0U;
  c2_info[31].fileTime1 = 0U;
  c2_info[31].fileTime2 = 0U;
  c2_info[32].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[32].name = "strcmp";
  c2_info[32].dominantType = "char";
  c2_info[32].resolved = "[B]strcmp";
  c2_info[32].fileLength = 0U;
  c2_info[32].fileTime1 = 0U;
  c2_info[32].fileTime2 = 0U;
  c2_info[33].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[33].name = "class";
  c2_info[33].dominantType = "double";
  c2_info[33].resolved = "[B]class";
  c2_info[33].fileLength = 0U;
  c2_info[33].fileTime1 = 0U;
  c2_info[33].fileTime2 = 0U;
  c2_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[34].name = "intmax";
  c2_info[34].dominantType = "char";
  c2_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[34].fileLength = 1535U;
  c2_info[34].fileTime1 = 1192445128U;
  c2_info[34].fileTime2 = 0U;
  c2_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[35].name = "ischar";
  c2_info[35].dominantType = "char";
  c2_info[35].resolved = "[B]ischar";
  c2_info[35].fileLength = 0U;
  c2_info[35].fileTime1 = 0U;
  c2_info[35].fileTime2 = 0U;
  c2_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[36].name = "int32";
  c2_info[36].dominantType = "double";
  c2_info[36].resolved = "[B]int32";
  c2_info[36].fileLength = 0U;
  c2_info[36].fileTime1 = 0U;
  c2_info[36].fileTime2 = 0U;
  c2_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c2_info[37].name = "eml_scalar_eg";
  c2_info[37].dominantType = "double";
  c2_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[37].fileLength = 3068U;
  c2_info[37].fileTime1 = 1240240410U;
  c2_info[37].fileTime2 = 0U;
  c2_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[38].name = "isstruct";
  c2_info[38].dominantType = "double";
  c2_info[38].resolved = "[B]isstruct";
  c2_info[38].fileLength = 0U;
  c2_info[38].fileTime1 = 0U;
  c2_info[38].fileTime2 = 0U;
  c2_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c2_info[39].name = "ones";
  c2_info[39].dominantType = "char";
  c2_info[39].resolved = "[B]ones";
  c2_info[39].fileLength = 0U;
  c2_info[39].fileTime1 = 0U;
  c2_info[39].fileTime2 = 0U;
  c2_info[40].context = "";
  c2_info[40].name = "body_Jacobian";
  c2_info[40].dominantType = "double";
  c2_info[40].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/body_Jacobian.m";
  c2_info[40].fileLength = 3760U;
  c2_info[40].fileTime1 = 1366807405U;
  c2_info[40].fileTime2 = 0U;
  c2_info[41].context = "";
  c2_info[41].name = "AdjointInv";
  c2_info[41].dominantType = "double";
  c2_info[41].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/AdjointInv.m";
  c2_info[41].fileLength = 289U;
  c2_info[41].fileTime1 = 1367252826U;
  c2_info[41].fileTime2 = 0U;
  c2_info[42].context = "[E]D:/Learn/Project_Matlab/Fanuc/AdjointInv.m";
  c2_info[42].name = "any";
  c2_info[42].dominantType = "logical";
  c2_info[42].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c2_info[42].fileLength = 427U;
  c2_info[42].fileTime1 = 1221245538U;
  c2_info[42].fileTime2 = 0U;
  c2_info[43].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c2_info[43].name = "islogical";
  c2_info[43].dominantType = "logical";
  c2_info[43].resolved = "[B]islogical";
  c2_info[43].fileLength = 0U;
  c2_info[43].fileTime1 = 0U;
  c2_info[43].fileTime2 = 0U;
  c2_info[44].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c2_info[44].name = "lt";
  c2_info[44].dominantType = "double";
  c2_info[44].resolved = "[B]lt";
  c2_info[44].fileLength = 0U;
  c2_info[44].fileTime1 = 0U;
  c2_info[44].fileTime2 = 0U;
  c2_info[45].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c2_info[45].name = "eml_all_or_any";
  c2_info[45].dominantType = "char";
  c2_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[45].fileLength = 3914U;
  c2_info[45].fileTime1 = 1271383994U;
  c2_info[45].fileTime2 = 0U;
  c2_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[46].name = "isequal";
  c2_info[46].dominantType = "double";
  c2_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[46].fileLength = 180U;
  c2_info[46].fileTime1 = 1226552070U;
  c2_info[46].fileTime2 = 0U;
  c2_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[47].name = "eml_isequal_core";
  c2_info[47].dominantType = "double";
  c2_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[47].fileLength = 4192U;
  c2_info[47].fileTime1 = 1258039010U;
  c2_info[47].fileTime2 = 0U;
  c2_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[48].name = "ge";
  c2_info[48].dominantType = "double";
  c2_info[48].resolved = "[B]ge";
  c2_info[48].fileLength = 0U;
  c2_info[48].fileTime1 = 0U;
  c2_info[48].fileTime2 = 0U;
  c2_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[49].name = "isnumeric";
  c2_info[49].dominantType = "logical";
  c2_info[49].resolved = "[B]isnumeric";
  c2_info[49].fileLength = 0U;
  c2_info[49].fileTime1 = 0U;
  c2_info[49].fileTime2 = 0U;
  c2_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!same_size";
  c2_info[50].name = "ndims";
  c2_info[50].dominantType = "logical";
  c2_info[50].resolved = "[B]ndims";
  c2_info[50].fileLength = 0U;
  c2_info[50].fileTime1 = 0U;
  c2_info[50].fileTime2 = 0U;
  c2_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[51].name = "eml_const_nonsingleton_dim";
  c2_info[51].dominantType = "logical";
  c2_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c2_info[51].fileLength = 1473U;
  c2_info[51].fileTime1 = 1240240402U;
  c2_info[51].fileTime2 = 0U;
  c2_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[52].name = "isempty";
  c2_info[52].dominantType = "logical";
  c2_info[52].resolved = "[B]isempty";
  c2_info[52].fileLength = 0U;
  c2_info[52].fileTime1 = 0U;
  c2_info[52].fileTime2 = 0U;
  c2_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[53].name = "isnan";
  c2_info[53].dominantType = "logical";
  c2_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[53].fileLength = 541U;
  c2_info[53].fileTime1 = 1271383988U;
  c2_info[53].fileTime2 = 0U;
  c2_info[54].context = "[E]D:/Learn/Project_Matlab/Fanuc/AdjointInv.m";
  c2_info[54].name = "transpose";
  c2_info[54].dominantType = "double";
  c2_info[54].resolved = "[B]transpose";
  c2_info[54].fileLength = 0U;
  c2_info[54].fileTime1 = 0U;
  c2_info[54].fileTime2 = 0U;
  c2_info[55].context = "[E]D:/Learn/Project_Matlab/Fanuc/AdjointInv.m";
  c2_info[55].name = "skew";
  c2_info[55].dominantType = "double";
  c2_info[55].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/skew.m";
  c2_info[55].fileLength = 450U;
  c2_info[55].fileTime1 = 1399884445U;
  c2_info[55].fileTime2 = 0U;
  c2_info[56].context = "[E]D:/Learn/Project_Matlab/Fanuc/skew.m";
  c2_info[56].name = "length";
  c2_info[56].dominantType = "double";
  c2_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[56].fileLength = 326U;
  c2_info[56].fileTime1 = 1226552074U;
  c2_info[56].fileTime2 = 0U;
  c2_info[57].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[57].name = "eml_xgemm";
  c2_info[57].dominantType = "int32";
  c2_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[57].fileLength = 3184U;
  c2_info[57].fileTime1 = 1209309252U;
  c2_info[57].fileTime2 = 0U;
  c2_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!itcount";
  c2_info[58].name = "min";
  c2_info[58].dominantType = "double";
  c2_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[58].fileLength = 362U;
  c2_info[58].fileTime1 = 1245080764U;
  c2_info[58].fileTime2 = 0U;
  c2_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[59].name = "nargout";
  c2_info[59].dominantType = "";
  c2_info[59].resolved = "[B]nargout";
  c2_info[59].fileLength = 0U;
  c2_info[59].fileTime1 = 0U;
  c2_info[59].fileTime2 = 0U;
  c2_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[60].name = "eml_min_or_max";
  c2_info[60].dominantType = "char";
  c2_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c2_info[60].fileLength = 9967U;
  c2_info[60].fileTime1 = 1261926670U;
  c2_info[60].fileTime2 = 0U;
  c2_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[61].name = "eml_scalexp_alloc";
  c2_info[61].dominantType = "double";
  c2_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[61].fileLength = 932U;
  c2_info[61].fileTime1 = 1261926670U;
  c2_info[61].fileTime2 = 0U;
  c2_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[62].name = "eml_refblas_xgemm";
  c2_info[62].dominantType = "int32";
  c2_info[62].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[62].fileLength = 5748U;
  c2_info[62].fileTime1 = 1228068672U;
  c2_info[62].fileTime2 = 0U;
  c2_info[63].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[63].name = "eml_index_minus";
  c2_info[63].dominantType = "int32";
  c2_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[63].fileLength = 277U;
  c2_info[63].fileTime1 = 1192445184U;
  c2_info[63].fileTime2 = 0U;
}

static void c2_b_info_helper(c2_ResolvedFunctionInfo c2_info[100])
{
  c2_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[64].name = "eml_index_times";
  c2_info[64].dominantType = "int32";
  c2_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[64].fileLength = 280U;
  c2_info[64].fileTime1 = 1192445186U;
  c2_info[64].fileTime2 = 0U;
  c2_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[65].name = "eml_index_plus";
  c2_info[65].dominantType = "int32";
  c2_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[65].fileLength = 272U;
  c2_info[65].fileTime1 = 1192445184U;
  c2_info[65].fileTime2 = 0U;
  c2_info[66].context = "";
  c2_info[66].name = "mldivide";
  c2_info[66].dominantType = "double";
  c2_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c2_info[66].fileLength = 494U;
  c2_info[66].fileTime1 = 1277726622U;
  c2_info[66].fileTime2 = 0U;
  c2_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c2_info[67].name = "eml_lusolve";
  c2_info[67].dominantType = "double";
  c2_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c2_info[67].fileLength = 5239U;
  c2_info[67].fileTime1 = 1264408552U;
  c2_info[67].fileTime2 = 0U;
  c2_info[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c2_info[68].name = "eml_xgetrf";
  c2_info[68].dominantType = "int32";
  c2_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c2_info[68].fileLength = 204U;
  c2_info[68].fileTime1 = 1271383994U;
  c2_info[68].fileTime2 = 0U;
  c2_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c2_info[69].name = "eml_lapack_xgetrf";
  c2_info[69].dominantType = "int32";
  c2_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c2_info[69].fileLength = 211U;
  c2_info[69].fileTime1 = 1271383994U;
  c2_info[69].fileTime2 = 0U;
  c2_info[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c2_info[70].name = "eml_matlab_zgetrf";
  c2_info[70].dominantType = "int32";
  c2_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[70].fileLength = 2193U;
  c2_info[70].fileTime1 = 1271383998U;
  c2_info[70].fileTime2 = 0U;
  c2_info[71].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[71].name = "realmin";
  c2_info[71].dominantType = "char";
  c2_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[71].fileLength = 749U;
  c2_info[71].fileTime1 = 1226552078U;
  c2_info[71].fileTime2 = 0U;
  c2_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[72].name = "mpower";
  c2_info[72].dominantType = "double";
  c2_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[72].fileLength = 3710U;
  c2_info[72].fileTime1 = 1238412688U;
  c2_info[72].fileTime2 = 0U;
  c2_info[73].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[73].name = "power";
  c2_info[73].dominantType = "double";
  c2_info[73].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[73].fileLength = 5380U;
  c2_info[73].fileTime1 = 1228068698U;
  c2_info[73].fileTime2 = 0U;
  c2_info[74].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[74].name = "eml_scalar_floor";
  c2_info[74].dominantType = "double";
  c2_info[74].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[74].fileLength = 260U;
  c2_info[74].fileTime1 = 1209309190U;
  c2_info[74].fileTime2 = 0U;
  c2_info[75].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[75].name = "eml_error";
  c2_info[75].dominantType = "char";
  c2_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[75].fileLength = 315U;
  c2_info[75].fileTime1 = 1213905144U;
  c2_info[75].fileTime2 = 0U;
  c2_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[76].name = "eps";
  c2_info[76].dominantType = "char";
  c2_info[76].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[76].fileLength = 1331U;
  c2_info[76].fileTime1 = 1246588112U;
  c2_info[76].fileTime2 = 0U;
  c2_info[77].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[77].name = "eml_is_float_class";
  c2_info[77].dominantType = "char";
  c2_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c2_info[77].fileLength = 226U;
  c2_info[77].fileTime1 = 1197825240U;
  c2_info[77].fileTime2 = 0U;
  c2_info[78].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[78].name = "colon";
  c2_info[78].dominantType = "int32";
  c2_info[78].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[78].fileLength = 8633U;
  c2_info[78].fileTime1 = 1273822662U;
  c2_info[78].fileTime2 = 0U;
  c2_info[79].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[79].name = "floor";
  c2_info[79].dominantType = "double";
  c2_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[79].fileLength = 332U;
  c2_info[79].fileTime1 = 1203422822U;
  c2_info[79].fileTime2 = 0U;
  c2_info[80].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c2_info[80].name = "intmin";
  c2_info[80].dominantType = "char";
  c2_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c2_info[80].fileLength = 1505U;
  c2_info[80].fileTime1 = 1192445128U;
  c2_info[80].fileTime2 = 0U;
  c2_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon";
  c2_info[81].name = "mrdivide";
  c2_info[81].dominantType = "double";
  c2_info[81].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[81].fileLength = 432U;
  c2_info[81].fileTime1 = 1277726622U;
  c2_info[81].fileTime2 = 0U;
  c2_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[82].name = "rdivide";
  c2_info[82].dominantType = "double";
  c2_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[82].fileLength = 403U;
  c2_info[82].fileTime1 = 1245080820U;
  c2_info[82].fileTime2 = 0U;
  c2_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[83].name = "eml_div";
  c2_info[83].dominantType = "double";
  c2_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[83].fileLength = 4918U;
  c2_info[83].fileTime1 = 1267038210U;
  c2_info[83].fileTime2 = 0U;
  c2_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[84].name = "eml_ixamax";
  c2_info[84].dominantType = "int32";
  c2_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c2_info[84].fileLength = 731U;
  c2_info[84].fileTime1 = 1209309244U;
  c2_info[84].fileTime2 = 0U;
  c2_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c2_info[85].name = "eml_refblas_ixamax";
  c2_info[85].dominantType = "int32";
  c2_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c2_info[85].fileLength = 740U;
  c2_info[85].fileTime1 = 1192445266U;
  c2_info[85].fileTime2 = 0U;
  c2_info[86].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c2_info[86].name = "eml_xcabs1";
  c2_info[86].dominantType = "double";
  c2_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c2_info[86].fileLength = 419U;
  c2_info[86].fileTime1 = 1209309246U;
  c2_info[86].fileTime2 = 0U;
  c2_info[87].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c2_info[87].name = "real";
  c2_info[87].dominantType = "double";
  c2_info[87].resolved = "[B]real";
  c2_info[87].fileLength = 0U;
  c2_info[87].fileTime1 = 0U;
  c2_info[87].fileTime2 = 0U;
  c2_info[88].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c2_info[88].name = "abs";
  c2_info[88].dominantType = "double";
  c2_info[88].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[88].fileLength = 566U;
  c2_info[88].fileTime1 = 1221245532U;
  c2_info[88].fileTime2 = 0U;
  c2_info[89].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[89].name = "eml_scalar_abs";
  c2_info[89].dominantType = "double";
  c2_info[89].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[89].fileLength = 461U;
  c2_info[89].fileTime1 = 1203422760U;
  c2_info[89].fileTime2 = 0U;
  c2_info[90].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c2_info[90].name = "imag";
  c2_info[90].dominantType = "double";
  c2_info[90].resolved = "[B]imag";
  c2_info[90].fileLength = 0U;
  c2_info[90].fileTime1 = 0U;
  c2_info[90].fileTime2 = 0U;
  c2_info[91].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[91].name = "eml_xswap";
  c2_info[91].dominantType = "int32";
  c2_info[91].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c2_info[91].fileLength = 1330U;
  c2_info[91].fileTime1 = 1209309260U;
  c2_info[91].fileTime2 = 0U;
  c2_info[92].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c2_info[92].name = "eml_refblas_xswap";
  c2_info[92].dominantType = "int32";
  c2_info[92].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c2_info[92].fileLength = 905U;
  c2_info[92].fileTime1 = 1238412670U;
  c2_info[92].fileTime2 = 0U;
  c2_info[93].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[93].name = "eml_xgeru";
  c2_info[93].dominantType = "int32";
  c2_info[93].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c2_info[93].fileLength = 2462U;
  c2_info[93].fileTime1 = 1209309256U;
  c2_info[93].fileTime2 = 0U;
  c2_info[94].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c2_info[94].name = "eml_xger";
  c2_info[94].dominantType = "int32";
  c2_info[94].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c2_info[94].fileLength = 2168U;
  c2_info[94].fileTime1 = 1209309254U;
  c2_info[94].fileTime2 = 0U;
  c2_info[95].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c2_info[95].name = "eml_refblas_xger";
  c2_info[95].dominantType = "int32";
  c2_info[95].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c2_info[95].fileLength = 411U;
  c2_info[95].fileTime1 = 1211194448U;
  c2_info[95].fileTime2 = 0U;
  c2_info[96].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c2_info[96].name = "eml_refblas_xgerx";
  c2_info[96].dominantType = "int32";
  c2_info[96].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c2_info[96].fileLength = 2231U;
  c2_info[96].fileTime1 = 1238412668U;
  c2_info[96].fileTime2 = 0U;
  c2_info[97].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!warn_singular";
  c2_info[97].name = "eml_warning";
  c2_info[97].dominantType = "char";
  c2_info[97].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c2_info[97].fileLength = 262U;
  c2_info[97].fileTime1 = 1236232078U;
  c2_info[97].fileTime2 = 0U;
  c2_info[98].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c2_info[98].name = "eml_xtrsm";
  c2_info[98].dominantType = "int32";
  c2_info[98].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c2_info[98].fileLength = 2383U;
  c2_info[98].fileTime1 = 1209309262U;
  c2_info[98].fileTime2 = 0U;
  c2_info[99].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c2_info[99].name = "eml_refblas_xtrsm";
  c2_info[99].dominantType = "int32";
  c2_info[99].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[99].fileLength = 13101U;
  c2_info[99].fileTime1 = 1252487206U;
  c2_info[99].fileTime2 = 0U;
}

static const mxArray *c2_i_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  boolean_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_b_u = *((boolean_T *)c2_u);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static void c2_emlrt_marshallIn(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *c2_Omega, const char_T *c2_name
  , real_T c2_y[6])
{
  real_T c2_dv5[6];
  int32_T c2_i159;
  sf_mex_import(c2_name, sf_mex_dup(c2_Omega), c2_dv5, 1, 0, 0U, 1, 0U, 1, 6);
  for (c2_i159 = 0; c2_i159 < 6; c2_i159 = c2_i159 + 1) {
    c2_y[c2_i159] = c2_dv5[c2_i159];
  }

  sf_mex_destroy(&c2_Omega);
}

static uint8_T c2_b_emlrt_marshallIn(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *
  c2_b_is_active_c2_EulerPIDJoint_Copy, const char_T *c2_name)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_name, sf_mex_dup(c2_b_is_active_c2_EulerPIDJoint_Copy),
                &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_b_is_active_c2_EulerPIDJoint_Copy);
  return c2_y;
}

static void init_dsm_address_info(SFc2_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_EulerPIDJoint_Copy_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2446082782U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3408488653U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1216593306U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3907021174U);
}

mxArray *sf_c2_EulerPIDJoint_Copy_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3541636129U);
    pr[1] = (double)(3403558919U);
    pr[2] = (double)(461000511U);
    pr[3] = (double)(2211005044U);
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
      pr[0] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  return(mxAutoinheritanceInfo);
}

static mxArray *sf_get_sim_state_info_c2_EulerPIDJoint_Copy(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"Omega\",},{M[8],M[0],T\"is_active_c2_EulerPIDJoint_Copy\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_EulerPIDJoint_Copy_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
    chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_EulerPIDJoint_CopyMachineNumber_,
           2,
           1,
           1,
           4,
           0,
           0,
           0,
           0,
           4,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_EulerPIDJoint_CopyMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_EulerPIDJoint_CopyMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_EulerPIDJoint_CopyMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Theta");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Omega");
          _SFD_SET_DATA_PROPS(2,1,1,0,"EndVel");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,212);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"fwd_kin",0,-1,3253);
        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"body_Jacobian",0,-1,3708);
        _SFD_CV_INIT_SCRIPT(2,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"AdjointInv",0,-1,276);
        _SFD_CV_INIT_SCRIPT_IF(2,0,38,63,-1,117);
        _SFD_CV_INIT_SCRIPT(3,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(3,0,"skew",0,-1,450);
        _SFD_CV_INIT_SCRIPT_IF(3,0,27,44,-1,92);
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
            1.0,0,0,(MexFcnForType)c2_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshall);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 9;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshall);
        }

        {
          real_T (*c2_Theta)[6];
          real_T (*c2_Omega)[6];
          real_T (*c2_EndVel)[3];
          c2_EndVel = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c2_Omega = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_Theta = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_Theta);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_Omega);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_EndVel);
          _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c2_L);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration
        (_EulerPIDJoint_CopyMachineNumber_,chartInstance->chartNumber,
         chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c2_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_EulerPIDJoint_Copy((SFc2_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
  initialize_c2_EulerPIDJoint_Copy((SFc2_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  enable_c2_EulerPIDJoint_Copy((SFc2_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  disable_c2_EulerPIDJoint_Copy((SFc2_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  sf_c2_EulerPIDJoint_Copy((SFc2_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c2_EulerPIDJoint_Copy(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_EulerPIDJoint_Copy
    ((SFc2_EulerPIDJoint_CopyInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c2_EulerPIDJoint_Copy();/* state var info */
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

static void sf_internal_set_sim_state_c2_EulerPIDJoint_Copy(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_EulerPIDJoint_Copy();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_EulerPIDJoint_Copy((SFc2_EulerPIDJoint_CopyInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c2_EulerPIDJoint_Copy(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_EulerPIDJoint_Copy(S);
}

static void sf_opaque_set_sim_state_c2_EulerPIDJoint_Copy(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_EulerPIDJoint_Copy(S, st);
}

static void sf_opaque_terminate_c2_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_EulerPIDJoint_CopyInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_EulerPIDJoint_Copy((SFc2_EulerPIDJoint_CopyInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c2_EulerPIDJoint_Copy
    ((SFc2_EulerPIDJoint_CopyInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_EulerPIDJoint_Copy(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_EulerPIDJoint_Copy
      ((SFc2_EulerPIDJoint_CopyInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_EulerPIDJoint_Copy(SimStruct *S)
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
      (int_T)sf_is_chart_inlinable(S,"EulerPIDJoint_Copy","EulerPIDJoint_Copy",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"EulerPIDJoint_Copy",
                "EulerPIDJoint_Copy",2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"EulerPIDJoint_Copy",
      "EulerPIDJoint_Copy",2,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"EulerPIDJoint_Copy",
        "EulerPIDJoint_Copy",2,2);
      sf_mark_chart_reusable_outputs(S,"EulerPIDJoint_Copy","EulerPIDJoint_Copy",
        2,1);
    }

    sf_set_rtw_dwork_info(S,"EulerPIDJoint_Copy","EulerPIDJoint_Copy",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1815832783U));
  ssSetChecksum1(S,(1357856867U));
  ssSetChecksum2(S,(3746900374U));
  ssSetChecksum3(S,(995516454U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_EulerPIDJoint_Copy(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "EulerPIDJoint_Copy", "EulerPIDJoint_Copy",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_EulerPIDJoint_Copy(SimStruct *S)
{
  SFc2_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc2_EulerPIDJoint_CopyInstanceStruct *)malloc(sizeof
    (SFc2_EulerPIDJoint_CopyInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_EulerPIDJoint_CopyInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_EulerPIDJoint_Copy;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_EulerPIDJoint_Copy;
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

void c2_EulerPIDJoint_Copy_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_EulerPIDJoint_Copy(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_EulerPIDJoint_Copy(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_EulerPIDJoint_Copy(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_EulerPIDJoint_Copy_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
