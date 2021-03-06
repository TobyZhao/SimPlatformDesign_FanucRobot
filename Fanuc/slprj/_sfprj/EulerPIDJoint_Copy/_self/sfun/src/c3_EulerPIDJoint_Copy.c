/* Include files */

#include "blascompat32.h"
#include "EulerPIDJoint_Copy_sfun.h"
#include "c3_EulerPIDJoint_Copy.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "EulerPIDJoint_Copy_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c3_debug_family_names[17] = { "nargin", "nargout", "RefPos",
  "RefVel", "RefAcc", "EnPos", "EnVel", "EnAcc", "DH_EU", "Ma_EU", "Cen_EU",
  "Ie_EU", "Ft_EU", "Torque", "JntVel", "JntAcc", "JntF" };

static const char *c3_b_debug_family_names[4] = { "nargin", "nargout", "w", "W"
};

static const char *c3_c_debug_family_names[6] = { "n", "nargin", "nargout", "w",
  "theta", "R" };

static const char *c3_d_debug_family_names[10] = { "v", "w", "n", "R", "P",
  "nargin", "nargout", "xi", "theta", "g" };

static const char *c3_e_debug_family_names[4] = { "nargin", "nargout", "w", "wh"
};

static const char *c3_f_debug_family_names[6] = { "R", "p", "nargin", "nargout",
  "g", "Adg" };

static const char *c3_g_debug_family_names[6] = { "w", "v", "nargin", "nargout",
  "xi", "adx" };

static const char *c3_h_debug_family_names[93] = { "w_o", "w_z", "kxi1", "kxi2",
  "kxi3", "kxi4", "kxi5", "kxi6", "ez", "ex", "eo", "g01_0", "g12_0", "g23_0",
  "g34_0", "g45_0", "g56_0", "g67_0", "g", "r1", "r2", "r3", "r4", "r5", "r6",
  "m1", "I1", "M1", "m2", "I2", "M2", "m3", "I3", "M3", "m4", "I4", "M4", "m5",
  "I5", "M5", "m6", "I6", "M6", "V0", "dV0", "g01", "Adinvg01", "V1", "dV1",
  "g12", "Adinvg12", "V2", "dV2", "g23", "Adinvg23", "V3", "dV3", "g34",
  "Adinvg34", "V4", "dV4", "g45", "Adinvg45", "V5", "dV5", "g56", "Adinvg56",
  "V6", "dV6", "Tau", "F7", "Adinvg67", "F6", "F5", "F4", "F3", "F2", "F1",
  "nargin", "nargout", "DH", "Ma", "Cen", "Ie", "Ft", "RefVel", "RefAcc",
  "EnPos", "EnVel", "Torque", "JntVel", "JntAcc", "JntF" };

/* Function Declarations */
static void initialize_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void initialize_params_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void enable_c3_EulerPIDJoint_Copy(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void disable_c3_EulerPIDJoint_Copy(SFc3_EulerPIDJoint_CopyInstanceStruct *
  chartInstance);
static void c3_update_debugger_state_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void set_sim_state_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, const mxArray *c3_st);
static void finalize_c3_EulerPIDJoint_Copy(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void sf_c3_EulerPIDJoint_Copy(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void compInitSubchartSimstructsFcn_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static void c3_DynEulerCon(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_DH[28], real_T c3_Ma[6], real_T c3_Cen[18], real_T c3_Ie[54], real_T
  c3_Ft[6], real_T c3_RefVel[6], real_T c3_RefAcc[6], real_T c3_EnPos[6], real_T
  c3_EnVel[6], real_T c3_Torque[6], real_T c3_JntVel[36], real_T c3_JntAcc[36],
  real_T c3_JntF[36]);
static void c3_expg(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                    c3_xi[6], real_T c3_theta, real_T c3_g[16]);
static real_T c3_norm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
                      real_T c3_x[3]);
static real_T c3_ceval_xnrm2(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[3], int32_T c3_ix0, int32_T c3_incx);
static void c3_eps(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void c3_isVariableSizing(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_eye(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                   c3_I[9]);
static void c3_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_expr(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                    c3_w[3], real_T c3_theta, real_T c3_R[9]);
static void c3_hat(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                   c3_w[3], real_T c3_W[9]);
static void c3_matrix_to_integer_power(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c3_a[9], real_T c3_b, real_T c3_c[9]);
static void c3_b_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_c_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_inv3x3(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
                      real_T c3_x[9], real_T c3_y[9]);
static real_T c3_b_norm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_x[9]);
static void c3_eml_warning(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void c3_b_eps(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void c3_b_eml_warning(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c3_varargin_3);
static real_T c3_power(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_a, real_T c3_b);
static void c3_eml_error(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance);
static void c3_d_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_e_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_mldivide(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[4], real_T c3_Y[4]);
static void c3_eml_matlab_zgetrf(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c3_A[16], real_T c3_b_A[16], int32_T c3_ipiv[4],
  int32_T *c3_info);
static int32_T c3_eml_ixamax(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0);
static int32_T c3_ceval_ixamax(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0, int32_T c3_incx);
static void c3_ceval_xswap(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c3_n, real_T c3_x[16], int32_T c3_ix0, int32_T c3_incx, int32_T c3_iy0,
  int32_T c3_incy, real_T c3_b_x[16]);
static void c3_ceval_xger(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, real_T c3_alpha1, int32_T c3_ix0, int32_T c3_incx,
  int32_T c3_iy0, int32_T c3_incy, real_T c3_A[16], int32_T c3_ia0, int32_T
  c3_lda, real_T c3_b_A[16]);
static void c3_eml_xtrsm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[4], real_T c3_b_B[4]);
static void c3_f_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_eml_blas_xtrsm(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, real_T c3_alpha1, real_T c3_A[16],
  int32_T c3_ia0, int32_T c3_lda, real_T c3_B[4], int32_T c3_ib0, int32_T c3_ldb,
  real_T c3_b_B[4]);
static void c3_b_mldivide(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[16], real_T c3_Y[16]);
static void c3_b_eml_xtrsm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[16], real_T c3_b_B[16]);
static void c3_g_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_b_eml_blas_xtrsm(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, real_T c3_alpha1, real_T c3_A[16],
  int32_T c3_ia0, int32_T c3_lda, real_T c3_B[16], int32_T c3_ib0, int32_T
  c3_ldb, real_T c3_b_B[16]);
static void c3_Adjoint(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_g[16], real_T c3_Adg[36]);
static void c3_h_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_eml_xgemm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[36], real_T c3_B[6], real_T c3_C[6], real_T c3_b_C[6]);
static void c3_ad(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                  c3_xi[6], real_T c3_adx[36]);
static void c3_i_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static void c3_ceval_xgemm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, int32_T c3_k, real_T c3_alpha1, real_T c3_A[36],
  int32_T c3_ia0, int32_T c3_lda, real_T c3_B[36], int32_T c3_ib0, int32_T
  c3_ldb, real_T c3_beta1, real_T c3_C[36], int32_T c3_ic0, int32_T c3_ldc,
  real_T c3_b_C[36]);
static void c3_j_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);
static real_T c3_ceval_xdot(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c3_n, real_T c3_x[6], int32_T c3_ix0, int32_T c3_incx, real_T c3_y[6],
  int32_T c3_iy0, int32_T c3_incy);
static const mxArray *c3_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_b_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_c_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_d_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_e_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_f_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_g_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_h_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_i_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_j_sf_marshall(void *chartInstanceVoid, void *c3_u);
static const mxArray *c3_k_sf_marshall(void *chartInstanceVoid, void *c3_u);
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[115]);
static void c3_b_info_helper(c3_ResolvedFunctionInfo c3_info[115]);
static const mxArray *c3_l_sf_marshall(void *chartInstanceVoid, void *c3_u);
static void c3_emlrt_marshallIn(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *c3_JntAcc, const char_T *c3_name, real_T c3_y
  [36]);
static void c3_b_emlrt_marshallIn(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *c3_Torque, const char_T *c3_name, real_T c3_y[6]);
static uint8_T c3_c_emlrt_marshallIn(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_EulerPIDJoint_Copy, const
  char_T *c3_name);
static void init_dsm_address_info(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_EulerPIDJoint_Copy = 0U;
}

static void initialize_params_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  real_T c3_dv0[28];
  int32_T c3_i0;
  real_T c3_dv1[6];
  int32_T c3_i1;
  real_T c3_dv2[18];
  int32_T c3_i2;
  real_T c3_dv3[54];
  int32_T c3_i3;
  real_T c3_dv4[6];
  int32_T c3_i4;
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'DH_EU' in the parent workspace.\n");
  sf_mex_import("DH_EU", sf_mex_get_sfun_param(chartInstance->S, 1, 0), c3_dv0,
                0, 0, 0U, 1, 0U, 2, 4, 7);
  for (c3_i0 = 0; c3_i0 < 28; c3_i0 = c3_i0 + 1) {
    chartInstance->c3_DH_EU[c3_i0] = c3_dv0[c3_i0];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'Ma_EU' in the parent workspace.\n");
  sf_mex_import("Ma_EU", sf_mex_get_sfun_param(chartInstance->S, 4, 0), c3_dv1,
                0, 0, 0U, 1, 0U, 1, 6);
  for (c3_i1 = 0; c3_i1 < 6; c3_i1 = c3_i1 + 1) {
    chartInstance->c3_Ma_EU[c3_i1] = c3_dv1[c3_i1];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'Cen_EU' in the parent workspace.\n");
  sf_mex_import("Cen_EU", sf_mex_get_sfun_param(chartInstance->S, 0, 0), c3_dv2,
                0, 0, 0U, 1, 0U, 1, 18);
  for (c3_i2 = 0; c3_i2 < 18; c3_i2 = c3_i2 + 1) {
    chartInstance->c3_Cen_EU[c3_i2] = c3_dv2[c3_i2];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'Ie_EU' in the parent workspace.\n");
  sf_mex_import("Ie_EU", sf_mex_get_sfun_param(chartInstance->S, 3, 0), c3_dv3,
                0, 0, 0U, 1, 0U, 1, 54);
  for (c3_i3 = 0; c3_i3 < 54; c3_i3 = c3_i3 + 1) {
    chartInstance->c3_Ie_EU[c3_i3] = c3_dv3[c3_i3];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'Ft_EU' in the parent workspace.\n");
  sf_mex_import("Ft_EU", sf_mex_get_sfun_param(chartInstance->S, 2, 0), c3_dv4,
                0, 0, 0U, 1, 0U, 1, 6);
  for (c3_i4 = 0; c3_i4 < 6; c3_i4 = c3_i4 + 1) {
    chartInstance->c3_Ft_EU[c3_i4] = c3_dv4[c3_i4];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c3_EulerPIDJoint_Copy(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_EulerPIDJoint_Copy(SFc3_EulerPIDJoint_CopyInstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  const mxArray *c3_st = NULL;
  const mxArray *c3_y = NULL;
  int32_T c3_i5;
  real_T c3_hoistedGlobal[36];
  int32_T c3_i6;
  real_T c3_u[36];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i7;
  real_T c3_b_hoistedGlobal[36];
  int32_T c3_i8;
  real_T c3_b_u[36];
  const mxArray *c3_c_y = NULL;
  int32_T c3_i9;
  real_T c3_c_hoistedGlobal[36];
  int32_T c3_i10;
  real_T c3_c_u[36];
  const mxArray *c3_d_y = NULL;
  int32_T c3_i11;
  real_T c3_d_hoistedGlobal[6];
  int32_T c3_i12;
  real_T c3_d_u[6];
  const mxArray *c3_e_y = NULL;
  uint8_T c3_e_hoistedGlobal;
  uint8_T c3_e_u;
  const mxArray *c3_f_y = NULL;
  real_T (*c3_Torque)[6];
  real_T (*c3_JntVel)[36];
  real_T (*c3_JntF)[36];
  real_T (*c3_JntAcc)[36];
  c3_JntF = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
  c3_JntAcc = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_JntVel = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_Torque = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(5));
  for (c3_i5 = 0; c3_i5 < 36; c3_i5 = c3_i5 + 1) {
    c3_hoistedGlobal[c3_i5] = (*c3_JntAcc)[c3_i5];
  }

  for (c3_i6 = 0; c3_i6 < 36; c3_i6 = c3_i6 + 1) {
    c3_u[c3_i6] = c3_hoistedGlobal[c3_i6];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 36));
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i7 = 0; c3_i7 < 36; c3_i7 = c3_i7 + 1) {
    c3_b_hoistedGlobal[c3_i7] = (*c3_JntF)[c3_i7];
  }

  for (c3_i8 = 0; c3_i8 < 36; c3_i8 = c3_i8 + 1) {
    c3_b_u[c3_i8] = c3_b_hoistedGlobal[c3_i8];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 1, 36));
  sf_mex_setcell(c3_y, 1, c3_c_y);
  for (c3_i9 = 0; c3_i9 < 36; c3_i9 = c3_i9 + 1) {
    c3_c_hoistedGlobal[c3_i9] = (*c3_JntVel)[c3_i9];
  }

  for (c3_i10 = 0; c3_i10 < 36; c3_i10 = c3_i10 + 1) {
    c3_c_u[c3_i10] = c3_c_hoistedGlobal[c3_i10];
  }

  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 36));
  sf_mex_setcell(c3_y, 2, c3_d_y);
  for (c3_i11 = 0; c3_i11 < 6; c3_i11 = c3_i11 + 1) {
    c3_d_hoistedGlobal[c3_i11] = (*c3_Torque)[c3_i11];
  }

  for (c3_i12 = 0; c3_i12 < 6; c3_i12 = c3_i12 + 1) {
    c3_d_u[c3_i12] = c3_d_hoistedGlobal[c3_i12];
  }

  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_d_u, 0, 0U, 1U, 0U, 1, 6));
  sf_mex_setcell(c3_y, 3, c3_e_y);
  c3_e_hoistedGlobal = chartInstance->c3_is_active_c3_EulerPIDJoint_Copy;
  c3_e_u = c3_e_hoistedGlobal;
  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 4, c3_f_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv5[36];
  int32_T c3_i13;
  real_T c3_dv6[36];
  int32_T c3_i14;
  real_T c3_dv7[36];
  int32_T c3_i15;
  real_T c3_dv8[6];
  int32_T c3_i16;
  real_T (*c3_JntAcc)[36];
  real_T (*c3_JntF)[36];
  real_T (*c3_JntVel)[36];
  real_T (*c3_Torque)[6];
  c3_JntF = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
  c3_JntAcc = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_JntVel = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_Torque = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                      "JntAcc", c3_dv5);
  for (c3_i13 = 0; c3_i13 < 36; c3_i13 = c3_i13 + 1) {
    (*c3_JntAcc)[c3_i13] = c3_dv5[c3_i13];
  }

  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)), "JntF",
                      c3_dv6);
  for (c3_i14 = 0; c3_i14 < 36; c3_i14 = c3_i14 + 1) {
    (*c3_JntF)[c3_i14] = c3_dv6[c3_i14];
  }

  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 2)),
                      "JntVel", c3_dv7);
  for (c3_i15 = 0; c3_i15 < 36; c3_i15 = c3_i15 + 1) {
    (*c3_JntVel)[c3_i15] = c3_dv7[c3_i15];
  }

  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 3)),
                        "Torque", c3_dv8);
  for (c3_i16 = 0; c3_i16 < 6; c3_i16 = c3_i16 + 1) {
    (*c3_Torque)[c3_i16] = c3_dv8[c3_i16];
  }

  chartInstance->c3_is_active_c3_EulerPIDJoint_Copy = c3_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 4)),
     "is_active_c3_EulerPIDJoint_Copy");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_EulerPIDJoint_Copy(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_EulerPIDJoint_Copy(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void sf_c3_EulerPIDJoint_Copy(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
  int32_T c3_i17;
  int32_T c3_i18;
  int32_T c3_i19;
  int32_T c3_i20;
  int32_T c3_i21;
  int32_T c3_i22;
  int32_T c3_i23;
  int32_T c3_i24;
  int32_T c3_i25;
  int32_T c3_i26;
  int32_T c3_i27;
  int32_T c3_i28;
  int32_T c3_i29;
  int32_T c3_i30;
  int32_T c3_i31;
  int32_T c3_previousEvent;
  int32_T c3_i32;
  real_T c3_hoistedGlobal[6];
  int32_T c3_i33;
  real_T c3_b_hoistedGlobal[6];
  int32_T c3_i34;
  real_T c3_c_hoistedGlobal[6];
  int32_T c3_i35;
  real_T c3_d_hoistedGlobal[6];
  int32_T c3_i36;
  real_T c3_e_hoistedGlobal[6];
  int32_T c3_i37;
  real_T c3_f_hoistedGlobal[6];
  int32_T c3_i38;
  real_T c3_g_hoistedGlobal[28];
  int32_T c3_i39;
  real_T c3_h_hoistedGlobal[6];
  int32_T c3_i40;
  real_T c3_i_hoistedGlobal[18];
  int32_T c3_i41;
  real_T c3_j_hoistedGlobal[54];
  int32_T c3_i42;
  real_T c3_k_hoistedGlobal[6];
  int32_T c3_i43;
  real_T c3_RefPos[6];
  int32_T c3_i44;
  real_T c3_RefVel[6];
  int32_T c3_i45;
  real_T c3_RefAcc[6];
  int32_T c3_i46;
  real_T c3_EnPos[6];
  int32_T c3_i47;
  real_T c3_EnVel[6];
  int32_T c3_i48;
  real_T c3_EnAcc[6];
  int32_T c3_i49;
  real_T c3_b_DH_EU[28];
  int32_T c3_i50;
  real_T c3_b_Ma_EU[6];
  int32_T c3_i51;
  real_T c3_b_Cen_EU[18];
  int32_T c3_i52;
  real_T c3_b_Ie_EU[54];
  int32_T c3_i53;
  real_T c3_b_Ft_EU[6];
  uint32_T c3_debug_family_var_map[17];
  static const char *c3_sv0[17] = { "nargin", "nargout", "RefPos", "RefVel",
    "RefAcc", "EnPos", "EnVel", "EnAcc", "DH_EU", "Ma_EU",
    "Cen_EU", "Ie_EU", "Ft_EU", "Torque", "JntVel", "JntAcc", "JntF" };

  real_T c3_nargin = 11.0;
  real_T c3_nargout = 4.0;
  real_T c3_Torque[6];
  real_T c3_JntVel[36];
  real_T c3_JntAcc[36];
  real_T c3_JntF[36];
  int32_T c3_i54;
  int32_T c3_i55;
  int32_T c3_i56;
  int32_T c3_i57;
  int32_T c3_i58;
  real_T c3_c_DH_EU[28];
  int32_T c3_i59;
  real_T c3_c_Ma_EU[6];
  int32_T c3_i60;
  real_T c3_c_Cen_EU[18];
  int32_T c3_i61;
  real_T c3_c_Ie_EU[54];
  int32_T c3_i62;
  real_T c3_c_Ft_EU[6];
  int32_T c3_i63;
  real_T c3_b_RefVel[6];
  int32_T c3_i64;
  real_T c3_b_RefAcc[6];
  int32_T c3_i65;
  real_T c3_b_EnPos[6];
  int32_T c3_i66;
  real_T c3_b_EnVel[6];
  real_T c3_b_JntF[36];
  real_T c3_b_JntAcc[36];
  real_T c3_b_JntVel[36];
  real_T c3_b_Torque[6];
  int32_T c3_i67;
  int32_T c3_i68;
  int32_T c3_i69;
  int32_T c3_i70;
  int32_T c3_i71;
  int32_T c3_i72;
  int32_T c3_i73;
  int32_T c3_i74;
  real_T (*c3_c_Torque)[6];
  real_T (*c3_c_JntVel)[36];
  real_T (*c3_c_JntAcc)[36];
  real_T (*c3_c_JntF)[36];
  real_T (*c3_b_EnAcc)[6];
  real_T (*c3_c_EnVel)[6];
  real_T (*c3_c_EnPos)[6];
  real_T (*c3_c_RefAcc)[6];
  real_T (*c3_c_RefVel)[6];
  real_T (*c3_b_RefPos)[6];
  c3_c_JntF = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
  c3_c_JntAcc = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_c_JntVel = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_EnAcc = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 5);
  c3_c_EnVel = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 4);
  c3_c_EnPos = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 3);
  c3_c_RefAcc = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
  c3_c_RefVel = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c3_c_Torque = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_RefPos = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2);
  for (c3_i17 = 0; c3_i17 < 6; c3_i17 = c3_i17 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_b_RefPos)[c3_i17], 0U);
  }

  for (c3_i18 = 0; c3_i18 < 6; c3_i18 = c3_i18 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_Torque)[c3_i18], 1U);
  }

  for (c3_i19 = 0; c3_i19 < 6; c3_i19 = c3_i19 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_RefVel)[c3_i19], 2U);
  }

  for (c3_i20 = 0; c3_i20 < 6; c3_i20 = c3_i20 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_RefAcc)[c3_i20], 3U);
  }

  for (c3_i21 = 0; c3_i21 < 6; c3_i21 = c3_i21 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_EnPos)[c3_i21], 4U);
  }

  for (c3_i22 = 0; c3_i22 < 6; c3_i22 = c3_i22 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_EnVel)[c3_i22], 5U);
  }

  for (c3_i23 = 0; c3_i23 < 6; c3_i23 = c3_i23 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_b_EnAcc)[c3_i23], 6U);
  }

  for (c3_i24 = 0; c3_i24 < 28; c3_i24 = c3_i24 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_DH_EU[c3_i24], 7U);
  }

  for (c3_i25 = 0; c3_i25 < 6; c3_i25 = c3_i25 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ma_EU[c3_i25], 8U);
  }

  for (c3_i26 = 0; c3_i26 < 18; c3_i26 = c3_i26 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Cen_EU[c3_i26], 9U);
  }

  for (c3_i27 = 0; c3_i27 < 54; c3_i27 = c3_i27 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ie_EU[c3_i27], 10U);
  }

  for (c3_i28 = 0; c3_i28 < 6; c3_i28 = c3_i28 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ft_EU[c3_i28], 11U);
  }

  for (c3_i29 = 0; c3_i29 < 36; c3_i29 = c3_i29 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_JntVel)[c3_i29], 12U);
  }

  for (c3_i30 = 0; c3_i30 < 36; c3_i30 = c3_i30 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_JntAcc)[c3_i30], 13U);
  }

  for (c3_i31 = 0; c3_i31 < 36; c3_i31 = c3_i31 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_JntF)[c3_i31], 14U);
  }

  c3_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2);
  for (c3_i32 = 0; c3_i32 < 6; c3_i32 = c3_i32 + 1) {
    c3_hoistedGlobal[c3_i32] = (*c3_b_RefPos)[c3_i32];
  }

  for (c3_i33 = 0; c3_i33 < 6; c3_i33 = c3_i33 + 1) {
    c3_b_hoistedGlobal[c3_i33] = (*c3_c_RefVel)[c3_i33];
  }

  for (c3_i34 = 0; c3_i34 < 6; c3_i34 = c3_i34 + 1) {
    c3_c_hoistedGlobal[c3_i34] = (*c3_c_RefAcc)[c3_i34];
  }

  for (c3_i35 = 0; c3_i35 < 6; c3_i35 = c3_i35 + 1) {
    c3_d_hoistedGlobal[c3_i35] = (*c3_c_EnPos)[c3_i35];
  }

  for (c3_i36 = 0; c3_i36 < 6; c3_i36 = c3_i36 + 1) {
    c3_e_hoistedGlobal[c3_i36] = (*c3_c_EnVel)[c3_i36];
  }

  for (c3_i37 = 0; c3_i37 < 6; c3_i37 = c3_i37 + 1) {
    c3_f_hoistedGlobal[c3_i37] = (*c3_b_EnAcc)[c3_i37];
  }

  for (c3_i38 = 0; c3_i38 < 28; c3_i38 = c3_i38 + 1) {
    c3_g_hoistedGlobal[c3_i38] = chartInstance->c3_DH_EU[c3_i38];
  }

  for (c3_i39 = 0; c3_i39 < 6; c3_i39 = c3_i39 + 1) {
    c3_h_hoistedGlobal[c3_i39] = chartInstance->c3_Ma_EU[c3_i39];
  }

  for (c3_i40 = 0; c3_i40 < 18; c3_i40 = c3_i40 + 1) {
    c3_i_hoistedGlobal[c3_i40] = chartInstance->c3_Cen_EU[c3_i40];
  }

  for (c3_i41 = 0; c3_i41 < 54; c3_i41 = c3_i41 + 1) {
    c3_j_hoistedGlobal[c3_i41] = chartInstance->c3_Ie_EU[c3_i41];
  }

  for (c3_i42 = 0; c3_i42 < 6; c3_i42 = c3_i42 + 1) {
    c3_k_hoistedGlobal[c3_i42] = chartInstance->c3_Ft_EU[c3_i42];
  }

  for (c3_i43 = 0; c3_i43 < 6; c3_i43 = c3_i43 + 1) {
    c3_RefPos[c3_i43] = c3_hoistedGlobal[c3_i43];
  }

  for (c3_i44 = 0; c3_i44 < 6; c3_i44 = c3_i44 + 1) {
    c3_RefVel[c3_i44] = c3_b_hoistedGlobal[c3_i44];
  }

  for (c3_i45 = 0; c3_i45 < 6; c3_i45 = c3_i45 + 1) {
    c3_RefAcc[c3_i45] = c3_c_hoistedGlobal[c3_i45];
  }

  for (c3_i46 = 0; c3_i46 < 6; c3_i46 = c3_i46 + 1) {
    c3_EnPos[c3_i46] = c3_d_hoistedGlobal[c3_i46];
  }

  for (c3_i47 = 0; c3_i47 < 6; c3_i47 = c3_i47 + 1) {
    c3_EnVel[c3_i47] = c3_e_hoistedGlobal[c3_i47];
  }

  for (c3_i48 = 0; c3_i48 < 6; c3_i48 = c3_i48 + 1) {
    c3_EnAcc[c3_i48] = c3_f_hoistedGlobal[c3_i48];
  }

  for (c3_i49 = 0; c3_i49 < 28; c3_i49 = c3_i49 + 1) {
    c3_b_DH_EU[c3_i49] = c3_g_hoistedGlobal[c3_i49];
  }

  for (c3_i50 = 0; c3_i50 < 6; c3_i50 = c3_i50 + 1) {
    c3_b_Ma_EU[c3_i50] = c3_h_hoistedGlobal[c3_i50];
  }

  for (c3_i51 = 0; c3_i51 < 18; c3_i51 = c3_i51 + 1) {
    c3_b_Cen_EU[c3_i51] = c3_i_hoistedGlobal[c3_i51];
  }

  for (c3_i52 = 0; c3_i52 < 54; c3_i52 = c3_i52 + 1) {
    c3_b_Ie_EU[c3_i52] = c3_j_hoistedGlobal[c3_i52];
  }

  for (c3_i53 = 0; c3_i53 < 6; c3_i53 = c3_i53 + 1) {
    c3_b_Ft_EU[c3_i53] = c3_k_hoistedGlobal[c3_i53];
  }

  sf_debug_symbol_scope_push_eml(0U, 17U, 17U, c3_sv0, c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_RefPos, c3_b_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_RefVel, c3_b_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c3_RefAcc, c3_b_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c3_EnPos, c3_b_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c3_EnVel, c3_b_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c3_EnAcc, c3_b_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c3_b_DH_EU, c3_e_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c3_b_Ma_EU, c3_b_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(c3_b_Cen_EU, c3_d_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(c3_b_Ie_EU, c3_c_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(c3_b_Ft_EU, c3_b_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(c3_Torque, c3_b_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(c3_JntVel, c3_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(c3_JntAcc, c3_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(c3_JntF, c3_sf_marshall, 16U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0, 3);
  for (c3_i54 = 0; c3_i54 < 36; c3_i54 = c3_i54 + 1) {
    c3_JntVel[c3_i54] = 0.0;
  }

  _SFD_EML_CALL(0, 4);
  for (c3_i55 = 0; c3_i55 < 36; c3_i55 = c3_i55 + 1) {
    c3_JntAcc[c3_i55] = 0.0;
  }

  _SFD_EML_CALL(0, 5);
  for (c3_i56 = 0; c3_i56 < 36; c3_i56 = c3_i56 + 1) {
    c3_JntF[c3_i56] = 0.0;
  }

  _SFD_EML_CALL(0, 6);
  for (c3_i57 = 0; c3_i57 < 6; c3_i57 = c3_i57 + 1) {
    c3_Torque[c3_i57] = 0.0;
  }

  /* %%%%%%%%%Make use of encoder feedback information%%%%%%%%%%%%% */
  _SFD_EML_CALL(0, 8);
  for (c3_i58 = 0; c3_i58 < 28; c3_i58 = c3_i58 + 1) {
    c3_c_DH_EU[c3_i58] = c3_b_DH_EU[c3_i58];
  }

  for (c3_i59 = 0; c3_i59 < 6; c3_i59 = c3_i59 + 1) {
    c3_c_Ma_EU[c3_i59] = c3_b_Ma_EU[c3_i59];
  }

  for (c3_i60 = 0; c3_i60 < 18; c3_i60 = c3_i60 + 1) {
    c3_c_Cen_EU[c3_i60] = c3_b_Cen_EU[c3_i60];
  }

  for (c3_i61 = 0; c3_i61 < 54; c3_i61 = c3_i61 + 1) {
    c3_c_Ie_EU[c3_i61] = c3_b_Ie_EU[c3_i61];
  }

  for (c3_i62 = 0; c3_i62 < 6; c3_i62 = c3_i62 + 1) {
    c3_c_Ft_EU[c3_i62] = c3_b_Ft_EU[c3_i62];
  }

  for (c3_i63 = 0; c3_i63 < 6; c3_i63 = c3_i63 + 1) {
    c3_b_RefVel[c3_i63] = c3_RefVel[c3_i63];
  }

  for (c3_i64 = 0; c3_i64 < 6; c3_i64 = c3_i64 + 1) {
    c3_b_RefAcc[c3_i64] = c3_RefAcc[c3_i64];
  }

  for (c3_i65 = 0; c3_i65 < 6; c3_i65 = c3_i65 + 1) {
    c3_b_EnPos[c3_i65] = c3_EnPos[c3_i65];
  }

  for (c3_i66 = 0; c3_i66 < 6; c3_i66 = c3_i66 + 1) {
    c3_b_EnVel[c3_i66] = c3_EnVel[c3_i66];
  }

  c3_DynEulerCon(chartInstance, c3_c_DH_EU, c3_c_Ma_EU, c3_c_Cen_EU, c3_c_Ie_EU,
                 c3_c_Ft_EU, c3_b_RefVel, c3_b_RefAcc, c3_b_EnPos,
                 c3_b_EnVel, c3_b_Torque, c3_b_JntVel, c3_b_JntAcc, c3_b_JntF);
  for (c3_i67 = 0; c3_i67 < 6; c3_i67 = c3_i67 + 1) {
    c3_Torque[c3_i67] = c3_b_Torque[c3_i67];
  }

  for (c3_i68 = 0; c3_i68 < 36; c3_i68 = c3_i68 + 1) {
    c3_JntVel[c3_i68] = c3_b_JntVel[c3_i68];
  }

  for (c3_i69 = 0; c3_i69 < 36; c3_i69 = c3_i69 + 1) {
    c3_JntAcc[c3_i69] = c3_b_JntAcc[c3_i69];
  }

  for (c3_i70 = 0; c3_i70 < 36; c3_i70 = c3_i70 + 1) {
    c3_JntF[c3_i70] = c3_b_JntF[c3_i70];
  }

  /* %%%%%%%%%Not use encoder feedback information%%%%%%%%%%%%%%%%% */
  /* [Torque,JntVel,JntAcc,JntF] = DynEuler(DH_EU,Ma_EU,Cen_EU,Ie_EU,Ft_EU,RefPos,RefVel,RefAcc); */
  _SFD_EML_CALL(0, -8);
  sf_debug_symbol_scope_pop();
  for (c3_i71 = 0; c3_i71 < 6; c3_i71 = c3_i71 + 1) {
    (*c3_c_Torque)[c3_i71] = c3_Torque[c3_i71];
  }

  for (c3_i72 = 0; c3_i72 < 36; c3_i72 = c3_i72 + 1) {
    (*c3_c_JntVel)[c3_i72] = c3_JntVel[c3_i72];
  }

  for (c3_i73 = 0; c3_i73 < 36; c3_i73 = c3_i73 + 1) {
    (*c3_c_JntAcc)[c3_i73] = c3_JntAcc[c3_i73];
  }

  for (c3_i74 = 0; c3_i74 < 36; c3_i74 = c3_i74 + 1) {
    (*c3_c_JntF)[c3_i74] = c3_JntF[c3_i74];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2);
  _sfEvent_ = c3_previousEvent;
  sf_debug_check_for_state_inconsistency(_EulerPIDJoint_CopyMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void compInitSubchartSimstructsFcn_c3_EulerPIDJoint_Copy
  (SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 0U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/DynEulerCon.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 1U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 2U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expr.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 3U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/GoogolTraj/basicfunction/hat.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 4U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/Adjoint.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 5U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/skew.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 6U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/GoogolTraj/basicfunction/ad.m"));
}

static void c3_DynEulerCon(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_DH[28], real_T c3_Ma[6], real_T c3_Cen[18
  ], real_T c3_Ie[54], real_T c3_Ft[6], real_T c3_RefVel[6], real_T c3_RefAcc[6],
  real_T c3_EnPos[6], real_T c3_EnVel[6], real_T
  c3_Torque[6], real_T c3_JntVel[36], real_T c3_JntAcc[36], real_T c3_JntF[36])
{
  uint32_T c3_debug_family_var_map[93];
  static const char *c3_sv1[93] = { "w_o", "w_z", "kxi1", "kxi2", "kxi3", "kxi4",
    "kxi5", "kxi6", "ez", "ex", "eo", "g01_0", "g12_0",
    "g23_0", "g34_0", "g45_0", "g56_0", "g67_0", "g", "r1", "r2", "r3", "r4",
    "r5", "r6", "m1", "I1",
    "M1", "m2", "I2", "M2", "m3", "I3", "M3", "m4", "I4", "M4", "m5", "I5", "M5",
    "m6", "I6", "M6",
    "V0", "dV0", "g01", "Adinvg01", "V1", "dV1", "g12", "Adinvg12", "V2", "dV2",
    "g23", "Adinvg23",
    "V3", "dV3", "g34", "Adinvg34", "V4", "dV4", "g45", "Adinvg45", "V5", "dV5",
    "g56", "Adinvg56",
    "V6", "dV6", "Tau", "F7", "Adinvg67", "F6", "F5", "F4", "F3", "F2", "F1",
    "nargin", "nargout",
    "DH", "Ma", "Cen", "Ie", "Ft", "RefVel", "RefAcc", "EnPos", "EnVel",
    "Torque", "JntVel", "JntAcc"
    , "JntF" };

  real_T c3_w_o[3];
  real_T c3_w_z[3];
  real_T c3_kxi1[6];
  real_T c3_kxi2[6];
  real_T c3_kxi3[6];
  real_T c3_kxi4[6];
  real_T c3_kxi5[6];
  real_T c3_kxi6[6];
  real_T c3_ez[3];
  real_T c3_ex[3];
  real_T c3_eo[3];
  real_T c3_g01_0[16];
  real_T c3_g12_0[16];
  real_T c3_g23_0[16];
  real_T c3_g34_0[16];
  real_T c3_g45_0[16];
  real_T c3_g56_0[16];
  real_T c3_g67_0[16];
  real_T c3_g[16];
  real_T c3_r1[4];
  real_T c3_r2[4];
  real_T c3_r3[4];
  real_T c3_r4[4];
  real_T c3_r5[4];
  real_T c3_r6[4];
  real_T c3_m1;
  real_T c3_I1[9];
  real_T c3_M1[36];
  real_T c3_m2;
  real_T c3_I2[9];
  real_T c3_M2[36];
  real_T c3_m3;
  real_T c3_I3[9];
  real_T c3_M3[36];
  real_T c3_m4;
  real_T c3_I4[9];
  real_T c3_M4[36];
  real_T c3_m5;
  real_T c3_I5[9];
  real_T c3_M5[36];
  real_T c3_m6;
  real_T c3_I6[9];
  real_T c3_M6[36];
  real_T c3_V0[6];
  real_T c3_dV0[6];
  real_T c3_g01[16];
  real_T c3_Adinvg01[36];
  real_T c3_V1[6];
  real_T c3_dV1[6];
  real_T c3_g12[16];
  real_T c3_Adinvg12[36];
  real_T c3_V2[6];
  real_T c3_dV2[6];
  real_T c3_g23[16];
  real_T c3_Adinvg23[36];
  real_T c3_V3[6];
  real_T c3_dV3[6];
  real_T c3_g34[16];
  real_T c3_Adinvg34[36];
  real_T c3_V4[6];
  real_T c3_dV4[6];
  real_T c3_g45[16];
  real_T c3_Adinvg45[36];
  real_T c3_V5[6];
  real_T c3_dV5[6];
  real_T c3_g56[16];
  real_T c3_Adinvg56[36];
  real_T c3_V6[6];
  real_T c3_dV6[6];
  real_T c3_Tau[6];
  real_T c3_F7[6];
  real_T c3_Adinvg67[36];
  real_T c3_F6[6];
  real_T c3_F5[6];
  real_T c3_F4[6];
  real_T c3_F3[6];
  real_T c3_F2[6];
  real_T c3_F1[6];
  real_T c3_b_r1[3];
  real_T c3_b_r2[3];
  real_T c3_b_r3[3];
  real_T c3_b_r4[3];
  real_T c3_b_r5[3];
  real_T c3_b_r6[3];
  real_T c3_nargin = 11.0;
  real_T c3_nargout = 4.0;
  int32_T c3_i75;
  int32_T c3_i76;
  int32_T c3_i77;
  int32_T c3_i78;
  int32_T c3_i79;
  int32_T c3_i80;
  static real_T c3_dv9[3] = { 0.0, 0.0, 1.0 };

  int32_T c3_i81;
  static real_T c3_dv10[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c3_i82;
  int32_T c3_i83;
  int32_T c3_i84;
  int32_T c3_i85;
  int32_T c3_i86;
  int32_T c3_i87;
  int32_T c3_i88;
  static real_T c3_dv11[3] = { 1.0, 0.0, 0.0 };

  int32_T c3_i89;
  int32_T c3_i90;
  real_T c3_dv12[6];
  real_T c3_a[16];
  int32_T c3_i91;
  static real_T c3_dv13[6] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };

  real_T c3_dv14[6];
  real_T c3_b[16];
  int32_T c3_i92;
  real_T c3_A[16];
  int32_T c3_i93;
  real_T c3_B[16];
  int32_T c3_i94;
  real_T c3_b_A[16];
  int32_T c3_i95;
  real_T c3_b_B[16];
  int32_T c3_i96;
  real_T c3_c_A[16];
  int32_T c3_i97;
  real_T c3_c_B[16];
  int32_T c3_i98;
  int32_T c3_i99;
  int32_T c3_i100;
  real_T c3_y[16];
  int32_T c3_i101;
  int32_T c3_i102;
  int32_T c3_i103;
  real_T c3_b_a[16];
  int32_T c3_i104;
  static real_T c3_dv15[6] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };

  real_T c3_dv16[6];
  real_T c3_b_b[16];
  int32_T c3_i105;
  real_T c3_d_A[16];
  int32_T c3_i106;
  real_T c3_d_B[16];
  int32_T c3_i107;
  real_T c3_e_A[16];
  int32_T c3_i108;
  real_T c3_e_B[16];
  int32_T c3_i109;
  real_T c3_f_A[16];
  int32_T c3_i110;
  real_T c3_f_B[16];
  int32_T c3_i111;
  int32_T c3_i112;
  int32_T c3_i113;
  real_T c3_b_y[16];
  int32_T c3_i114;
  int32_T c3_i115;
  int32_T c3_i116;
  real_T c3_c_a[16];
  int32_T c3_i117;
  static real_T c3_dv17[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  real_T c3_dv18[6];
  real_T c3_c_b[16];
  int32_T c3_i118;
  real_T c3_g_A[16];
  int32_T c3_i119;
  real_T c3_g_B[16];
  int32_T c3_i120;
  int32_T c3_i121;
  real_T c3_h_A[16];
  int32_T c3_i122;
  real_T c3_h_B[16];
  int32_T c3_i123;
  real_T c3_i_A[16];
  int32_T c3_i124;
  real_T c3_i_B[16];
  int32_T c3_i125;
  int32_T c3_i126;
  int32_T c3_i127;
  int32_T c3_i128;
  int32_T c3_i129;
  int32_T c3_i130;
  real_T c3_dv19[6];
  real_T c3_d_a[16];
  int32_T c3_i131;
  real_T c3_dv20[6];
  real_T c3_d_b[16];
  int32_T c3_i132;
  real_T c3_j_A[16];
  int32_T c3_i133;
  real_T c3_j_B[16];
  int32_T c3_i134;
  real_T c3_k_A[16];
  int32_T c3_i135;
  real_T c3_k_B[16];
  int32_T c3_i136;
  real_T c3_l_A[16];
  int32_T c3_i137;
  real_T c3_l_B[16];
  int32_T c3_i138;
  int32_T c3_i139;
  int32_T c3_i140;
  real_T c3_c_y[16];
  int32_T c3_i141;
  int32_T c3_i142;
  int32_T c3_i143;
  real_T c3_e_a[16];
  int32_T c3_i144;
  real_T c3_dv21[6];
  real_T c3_e_b[16];
  int32_T c3_i145;
  real_T c3_m_A[16];
  int32_T c3_i146;
  real_T c3_m_B[16];
  int32_T c3_i147;
  real_T c3_n_A[16];
  int32_T c3_i148;
  real_T c3_n_B[16];
  int32_T c3_i149;
  real_T c3_o_A[16];
  int32_T c3_i150;
  real_T c3_o_B[16];
  int32_T c3_i151;
  int32_T c3_i152;
  int32_T c3_i153;
  real_T c3_d_y[16];
  int32_T c3_i154;
  int32_T c3_i155;
  int32_T c3_i156;
  real_T c3_f_a[16];
  int32_T c3_i157;
  real_T c3_dv22[6];
  real_T c3_f_b[16];
  int32_T c3_i158;
  real_T c3_p_A[16];
  int32_T c3_i159;
  real_T c3_p_B[16];
  int32_T c3_i160;
  int32_T c3_i161;
  real_T c3_q_A[16];
  int32_T c3_i162;
  real_T c3_q_B[16];
  int32_T c3_i163;
  real_T c3_r_A[16];
  int32_T c3_i164;
  real_T c3_r_B[16];
  int32_T c3_i165;
  int32_T c3_i166;
  int32_T c3_i167;
  int32_T c3_i168;
  int32_T c3_i169;
  int32_T c3_i170;
  real_T c3_dv23[6];
  real_T c3_g_a[16];
  int32_T c3_i171;
  real_T c3_dv24[6];
  real_T c3_g_b[16];
  int32_T c3_i172;
  real_T c3_s_A[16];
  int32_T c3_i173;
  real_T c3_s_B[16];
  int32_T c3_i174;
  real_T c3_t_A[16];
  int32_T c3_i175;
  real_T c3_t_B[16];
  int32_T c3_i176;
  real_T c3_u_A[16];
  int32_T c3_i177;
  real_T c3_u_B[16];
  int32_T c3_i178;
  int32_T c3_i179;
  int32_T c3_i180;
  real_T c3_e_y[16];
  int32_T c3_i181;
  int32_T c3_i182;
  int32_T c3_i183;
  real_T c3_h_a[16];
  int32_T c3_i184;
  real_T c3_dv25[6];
  real_T c3_h_b[16];
  int32_T c3_i185;
  real_T c3_v_A[16];
  int32_T c3_i186;
  real_T c3_v_B[16];
  int32_T c3_i187;
  real_T c3_w_A[16];
  int32_T c3_i188;
  real_T c3_w_B[16];
  int32_T c3_i189;
  real_T c3_x_A[16];
  int32_T c3_i190;
  real_T c3_x_B[16];
  int32_T c3_i191;
  int32_T c3_i192;
  int32_T c3_i193;
  real_T c3_f_y[16];
  int32_T c3_i194;
  int32_T c3_i195;
  int32_T c3_i196;
  real_T c3_i_a[16];
  int32_T c3_i197;
  real_T c3_dv26[6];
  real_T c3_i_b[16];
  int32_T c3_i198;
  real_T c3_y_A[16];
  int32_T c3_i199;
  real_T c3_y_B[16];
  int32_T c3_i200;
  int32_T c3_i201;
  real_T c3_ab_A[16];
  int32_T c3_i202;
  real_T c3_ab_B[16];
  int32_T c3_i203;
  real_T c3_bb_A[16];
  int32_T c3_i204;
  real_T c3_bb_B[16];
  int32_T c3_i205;
  int32_T c3_i206;
  int32_T c3_i207;
  int32_T c3_i208;
  int32_T c3_i209;
  int32_T c3_i210;
  real_T c3_dv27[6];
  real_T c3_j_a[16];
  int32_T c3_i211;
  real_T c3_dv28[6];
  real_T c3_j_b[16];
  int32_T c3_i212;
  real_T c3_cb_A[16];
  int32_T c3_i213;
  real_T c3_cb_B[16];
  int32_T c3_i214;
  real_T c3_db_A[16];
  int32_T c3_i215;
  real_T c3_db_B[16];
  int32_T c3_i216;
  real_T c3_eb_A[16];
  int32_T c3_i217;
  real_T c3_eb_B[16];
  int32_T c3_i218;
  int32_T c3_i219;
  int32_T c3_i220;
  real_T c3_g_y[16];
  int32_T c3_i221;
  int32_T c3_i222;
  int32_T c3_i223;
  real_T c3_k_a[16];
  int32_T c3_i224;
  real_T c3_dv29[6];
  real_T c3_k_b[16];
  int32_T c3_i225;
  real_T c3_fb_A[16];
  int32_T c3_i226;
  real_T c3_fb_B[16];
  int32_T c3_i227;
  real_T c3_gb_A[16];
  int32_T c3_i228;
  real_T c3_gb_B[16];
  int32_T c3_i229;
  real_T c3_hb_A[16];
  int32_T c3_i230;
  real_T c3_hb_B[16];
  int32_T c3_i231;
  int32_T c3_i232;
  int32_T c3_i233;
  real_T c3_h_y[16];
  int32_T c3_i234;
  int32_T c3_i235;
  int32_T c3_i236;
  real_T c3_l_a[16];
  int32_T c3_i237;
  real_T c3_dv30[6];
  real_T c3_l_b[16];
  int32_T c3_i238;
  real_T c3_ib_A[16];
  int32_T c3_i239;
  real_T c3_ib_B[16];
  int32_T c3_i240;
  int32_T c3_i241;
  real_T c3_jb_A[16];
  int32_T c3_i242;
  real_T c3_jb_B[16];
  int32_T c3_i243;
  real_T c3_kb_A[16];
  int32_T c3_i244;
  real_T c3_kb_B[16];
  int32_T c3_i245;
  int32_T c3_i246;
  int32_T c3_i247;
  int32_T c3_i248;
  int32_T c3_i249;
  int32_T c3_i250;
  real_T c3_dv31[6];
  real_T c3_m_a[16];
  int32_T c3_i251;
  real_T c3_dv32[6];
  real_T c3_m_b[16];
  int32_T c3_i252;
  real_T c3_lb_A[16];
  int32_T c3_i253;
  real_T c3_lb_B[16];
  int32_T c3_i254;
  real_T c3_mb_A[16];
  int32_T c3_i255;
  real_T c3_mb_B[16];
  int32_T c3_i256;
  real_T c3_nb_A[16];
  int32_T c3_i257;
  real_T c3_nb_B[16];
  int32_T c3_i258;
  int32_T c3_i259;
  int32_T c3_i260;
  real_T c3_i_y[16];
  int32_T c3_i261;
  int32_T c3_i262;
  int32_T c3_i263;
  real_T c3_n_a[16];
  int32_T c3_i264;
  real_T c3_dv33[6];
  real_T c3_n_b[16];
  int32_T c3_i265;
  real_T c3_ob_A[16];
  int32_T c3_i266;
  real_T c3_ob_B[16];
  int32_T c3_i267;
  real_T c3_pb_A[16];
  int32_T c3_i268;
  real_T c3_pb_B[16];
  int32_T c3_i269;
  real_T c3_qb_A[16];
  int32_T c3_i270;
  real_T c3_qb_B[16];
  int32_T c3_i271;
  int32_T c3_i272;
  int32_T c3_i273;
  real_T c3_j_y[16];
  int32_T c3_i274;
  int32_T c3_i275;
  int32_T c3_i276;
  real_T c3_o_a[16];
  int32_T c3_i277;
  real_T c3_dv34[6];
  real_T c3_o_b[16];
  int32_T c3_i278;
  real_T c3_rb_A[16];
  int32_T c3_i279;
  real_T c3_rb_B[16];
  int32_T c3_i280;
  int32_T c3_i281;
  real_T c3_sb_A[16];
  int32_T c3_i282;
  real_T c3_sb_B[16];
  int32_T c3_i283;
  real_T c3_tb_A[16];
  int32_T c3_i284;
  real_T c3_tb_B[16];
  int32_T c3_i285;
  int32_T c3_i286;
  int32_T c3_i287;
  int32_T c3_i288;
  int32_T c3_i289;
  int32_T c3_i290;
  real_T c3_dv35[6];
  real_T c3_p_a[16];
  int32_T c3_i291;
  real_T c3_dv36[6];
  real_T c3_p_b[16];
  int32_T c3_i292;
  real_T c3_ub_A[16];
  int32_T c3_i293;
  real_T c3_ub_B[16];
  int32_T c3_i294;
  real_T c3_vb_A[16];
  int32_T c3_i295;
  real_T c3_vb_B[16];
  int32_T c3_i296;
  real_T c3_wb_A[16];
  int32_T c3_i297;
  real_T c3_wb_B[16];
  int32_T c3_i298;
  int32_T c3_i299;
  int32_T c3_i300;
  real_T c3_k_y[16];
  int32_T c3_i301;
  int32_T c3_i302;
  int32_T c3_i303;
  real_T c3_q_a[16];
  int32_T c3_i304;
  real_T c3_dv37[6];
  real_T c3_q_b[16];
  int32_T c3_i305;
  real_T c3_xb_A[16];
  int32_T c3_i306;
  real_T c3_xb_B[16];
  int32_T c3_i307;
  real_T c3_yb_A[16];
  int32_T c3_i308;
  real_T c3_yb_B[16];
  int32_T c3_i309;
  real_T c3_ac_A[16];
  int32_T c3_i310;
  real_T c3_ac_B[16];
  int32_T c3_i311;
  int32_T c3_i312;
  int32_T c3_i313;
  real_T c3_l_y[16];
  int32_T c3_i314;
  int32_T c3_i315;
  int32_T c3_i316;
  real_T c3_r_a[16];
  int32_T c3_i317;
  real_T c3_dv38[6];
  real_T c3_r_b[16];
  int32_T c3_i318;
  real_T c3_bc_A[16];
  int32_T c3_i319;
  real_T c3_bc_B[16];
  int32_T c3_i320;
  int32_T c3_i321;
  real_T c3_cc_A[16];
  int32_T c3_i322;
  real_T c3_cc_B[16];
  int32_T c3_i323;
  real_T c3_dc_A[16];
  int32_T c3_i324;
  real_T c3_dc_B[16];
  int32_T c3_i325;
  int32_T c3_i326;
  int32_T c3_i327;
  int32_T c3_i328;
  int32_T c3_i329;
  int32_T c3_i330;
  real_T c3_dv39[6];
  real_T c3_s_a[16];
  int32_T c3_i331;
  real_T c3_dv40[6];
  real_T c3_s_b[16];
  int32_T c3_i332;
  real_T c3_ec_A[16];
  int32_T c3_i333;
  real_T c3_ec_B[16];
  int32_T c3_i334;
  real_T c3_fc_A[16];
  int32_T c3_i335;
  real_T c3_fc_B[16];
  int32_T c3_i336;
  real_T c3_gc_A[16];
  int32_T c3_i337;
  real_T c3_gc_B[16];
  int32_T c3_i338;
  int32_T c3_i339;
  int32_T c3_i340;
  real_T c3_m_y[16];
  int32_T c3_i341;
  int32_T c3_i342;
  int32_T c3_i343;
  real_T c3_t_a[16];
  int32_T c3_i344;
  real_T c3_dv41[6];
  real_T c3_t_b[16];
  int32_T c3_i345;
  real_T c3_hc_A[16];
  int32_T c3_i346;
  real_T c3_hc_B[16];
  int32_T c3_i347;
  real_T c3_ic_A[16];
  int32_T c3_i348;
  real_T c3_ic_B[16];
  int32_T c3_i349;
  real_T c3_jc_A[16];
  int32_T c3_i350;
  real_T c3_jc_B[16];
  int32_T c3_i351;
  int32_T c3_i352;
  int32_T c3_i353;
  real_T c3_n_y[16];
  int32_T c3_i354;
  int32_T c3_i355;
  int32_T c3_i356;
  real_T c3_u_a[16];
  int32_T c3_i357;
  real_T c3_dv42[6];
  real_T c3_u_b[16];
  int32_T c3_i358;
  real_T c3_kc_A[16];
  int32_T c3_i359;
  real_T c3_kc_B[16];
  int32_T c3_i360;
  int32_T c3_i361;
  real_T c3_lc_A[16];
  int32_T c3_i362;
  real_T c3_lc_B[16];
  int32_T c3_i363;
  real_T c3_mc_A[16];
  int32_T c3_i364;
  real_T c3_mc_B[16];
  int32_T c3_i365;
  int32_T c3_i366;
  int32_T c3_i367;
  int32_T c3_i368;
  int32_T c3_i369;
  int32_T c3_i370;
  int32_T c3_i371;
  real_T c3_b_g[16];
  int32_T c3_i372;
  real_T c3_b_Cen[4];
  real_T c3_dv43[4];
  int32_T c3_i373;
  int32_T c3_i374;
  int32_T c3_i375;
  real_T c3_v_a[16];
  int32_T c3_i376;
  real_T c3_v_b[16];
  int32_T c3_i377;
  real_T c3_nc_A[16];
  int32_T c3_i378;
  real_T c3_nc_B[16];
  int32_T c3_i379;
  int32_T c3_i380;
  real_T c3_oc_A[16];
  int32_T c3_i381;
  real_T c3_oc_B[16];
  int32_T c3_i382;
  real_T c3_pc_A[16];
  int32_T c3_i383;
  real_T c3_pc_B[16];
  int32_T c3_i384;
  int32_T c3_i385;
  int32_T c3_i386;
  int32_T c3_i387;
  int32_T c3_i388;
  int32_T c3_i389;
  real_T c3_c_g[16];
  int32_T c3_i390;
  real_T c3_c_Cen[4];
  real_T c3_dv44[4];
  int32_T c3_i391;
  int32_T c3_i392;
  int32_T c3_i393;
  real_T c3_w_a[16];
  int32_T c3_i394;
  real_T c3_w_b[16];
  int32_T c3_i395;
  real_T c3_qc_A[16];
  int32_T c3_i396;
  real_T c3_qc_B[16];
  int32_T c3_i397;
  int32_T c3_i398;
  real_T c3_rc_A[16];
  int32_T c3_i399;
  real_T c3_rc_B[16];
  int32_T c3_i400;
  real_T c3_sc_A[16];
  int32_T c3_i401;
  real_T c3_sc_B[16];
  int32_T c3_i402;
  int32_T c3_i403;
  int32_T c3_i404;
  int32_T c3_i405;
  int32_T c3_i406;
  int32_T c3_i407;
  real_T c3_d_g[16];
  int32_T c3_i408;
  real_T c3_d_Cen[4];
  real_T c3_dv45[4];
  int32_T c3_i409;
  int32_T c3_i410;
  int32_T c3_i411;
  real_T c3_x_a[16];
  int32_T c3_i412;
  real_T c3_x_b[16];
  int32_T c3_i413;
  real_T c3_tc_A[16];
  int32_T c3_i414;
  real_T c3_tc_B[16];
  int32_T c3_i415;
  int32_T c3_i416;
  real_T c3_uc_A[16];
  int32_T c3_i417;
  real_T c3_uc_B[16];
  int32_T c3_i418;
  real_T c3_vc_A[16];
  int32_T c3_i419;
  real_T c3_vc_B[16];
  int32_T c3_i420;
  int32_T c3_i421;
  int32_T c3_i422;
  int32_T c3_i423;
  int32_T c3_i424;
  int32_T c3_i425;
  real_T c3_e_g[16];
  int32_T c3_i426;
  real_T c3_e_Cen[4];
  real_T c3_dv46[4];
  int32_T c3_i427;
  int32_T c3_i428;
  int32_T c3_i429;
  real_T c3_y_a[16];
  int32_T c3_i430;
  real_T c3_y_b[16];
  int32_T c3_i431;
  real_T c3_wc_A[16];
  int32_T c3_i432;
  real_T c3_wc_B[16];
  int32_T c3_i433;
  int32_T c3_i434;
  real_T c3_xc_A[16];
  int32_T c3_i435;
  real_T c3_xc_B[16];
  int32_T c3_i436;
  real_T c3_yc_A[16];
  int32_T c3_i437;
  real_T c3_yc_B[16];
  int32_T c3_i438;
  int32_T c3_i439;
  int32_T c3_i440;
  int32_T c3_i441;
  int32_T c3_i442;
  int32_T c3_i443;
  real_T c3_f_g[16];
  int32_T c3_i444;
  real_T c3_f_Cen[4];
  real_T c3_dv47[4];
  int32_T c3_i445;
  int32_T c3_i446;
  int32_T c3_i447;
  real_T c3_ab_a[16];
  int32_T c3_i448;
  real_T c3_ab_b[16];
  int32_T c3_i449;
  real_T c3_ad_A[16];
  int32_T c3_i450;
  real_T c3_ad_B[16];
  int32_T c3_i451;
  int32_T c3_i452;
  real_T c3_bd_A[16];
  int32_T c3_i453;
  real_T c3_bd_B[16];
  int32_T c3_i454;
  real_T c3_cd_A[16];
  int32_T c3_i455;
  real_T c3_cd_B[16];
  int32_T c3_i456;
  int32_T c3_i457;
  int32_T c3_i458;
  int32_T c3_i459;
  int32_T c3_i460;
  int32_T c3_i461;
  real_T c3_g_g[16];
  int32_T c3_i462;
  real_T c3_g_Cen[4];
  real_T c3_dv48[4];
  int32_T c3_i463;
  int32_T c3_i464;
  int32_T c3_i465;
  real_T c3_x[9];
  int32_T c3_k;
  int32_T c3_b_k;
  real_T c3_bb_a;
  int32_T c3_i466;
  static real_T c3_dv49[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c3_o_y[9];
  real_T c3_cb_a;
  int32_T c3_i467;
  real_T c3_c_r1[3];
  real_T c3_bb_b[9];
  int32_T c3_i468;
  real_T c3_p_y[9];
  real_T c3_db_a;
  int32_T c3_i469;
  real_T c3_d_r1[3];
  real_T c3_cb_b[9];
  int32_T c3_i470;
  real_T c3_q_y[9];
  real_T c3_eb_a;
  int32_T c3_i471;
  real_T c3_e_r1[3];
  real_T c3_db_b[9];
  int32_T c3_i472;
  real_T c3_r_y[9];
  int32_T c3_i473;
  real_T c3_fb_a[9];
  int32_T c3_i474;
  real_T c3_f_r1[3];
  real_T c3_eb_b[9];
  int32_T c3_i475;
  real_T c3_dd_A[9];
  int32_T c3_i476;
  real_T c3_dd_B[9];
  int32_T c3_i477;
  real_T c3_ed_A[9];
  int32_T c3_i478;
  real_T c3_ed_B[9];
  int32_T c3_i479;
  real_T c3_fd_A[9];
  int32_T c3_i480;
  real_T c3_fd_B[9];
  int32_T c3_i481;
  int32_T c3_i482;
  int32_T c3_i483;
  real_T c3_s_y[9];
  int32_T c3_i484;
  int32_T c3_i485;
  int32_T c3_i486;
  int32_T c3_i487;
  int32_T c3_i488;
  int32_T c3_i489;
  int32_T c3_i490;
  int32_T c3_i491;
  int32_T c3_i492;
  int32_T c3_i493;
  int32_T c3_i494;
  int32_T c3_i495;
  int32_T c3_i496;
  int32_T c3_i497;
  int32_T c3_i498;
  int32_T c3_i499;
  int32_T c3_i500;
  int32_T c3_i501;
  int32_T c3_i502;
  real_T c3_b_x[9];
  int32_T c3_c_k;
  int32_T c3_d_k;
  real_T c3_gb_a;
  int32_T c3_i503;
  real_T c3_t_y[9];
  real_T c3_hb_a;
  int32_T c3_i504;
  real_T c3_c_r2[3];
  real_T c3_fb_b[9];
  int32_T c3_i505;
  real_T c3_u_y[9];
  real_T c3_ib_a;
  int32_T c3_i506;
  real_T c3_d_r2[3];
  real_T c3_gb_b[9];
  int32_T c3_i507;
  real_T c3_v_y[9];
  real_T c3_jb_a;
  int32_T c3_i508;
  real_T c3_e_r2[3];
  real_T c3_hb_b[9];
  int32_T c3_i509;
  real_T c3_w_y[9];
  int32_T c3_i510;
  real_T c3_kb_a[9];
  int32_T c3_i511;
  real_T c3_f_r2[3];
  real_T c3_ib_b[9];
  int32_T c3_i512;
  real_T c3_gd_A[9];
  int32_T c3_i513;
  real_T c3_gd_B[9];
  int32_T c3_i514;
  real_T c3_hd_A[9];
  int32_T c3_i515;
  real_T c3_hd_B[9];
  int32_T c3_i516;
  real_T c3_id_A[9];
  int32_T c3_i517;
  real_T c3_id_B[9];
  int32_T c3_i518;
  int32_T c3_i519;
  int32_T c3_i520;
  real_T c3_x_y[9];
  int32_T c3_i521;
  int32_T c3_i522;
  int32_T c3_i523;
  int32_T c3_i524;
  int32_T c3_i525;
  int32_T c3_i526;
  int32_T c3_i527;
  int32_T c3_i528;
  int32_T c3_i529;
  int32_T c3_i530;
  int32_T c3_i531;
  int32_T c3_i532;
  int32_T c3_i533;
  int32_T c3_i534;
  int32_T c3_i535;
  int32_T c3_i536;
  int32_T c3_i537;
  int32_T c3_i538;
  int32_T c3_i539;
  real_T c3_c_x[9];
  int32_T c3_e_k;
  int32_T c3_f_k;
  real_T c3_lb_a;
  int32_T c3_i540;
  real_T c3_y_y[9];
  real_T c3_mb_a;
  int32_T c3_i541;
  real_T c3_c_r3[3];
  real_T c3_jb_b[9];
  int32_T c3_i542;
  real_T c3_ab_y[9];
  real_T c3_nb_a;
  int32_T c3_i543;
  real_T c3_d_r3[3];
  real_T c3_kb_b[9];
  int32_T c3_i544;
  real_T c3_bb_y[9];
  real_T c3_ob_a;
  int32_T c3_i545;
  real_T c3_e_r3[3];
  real_T c3_lb_b[9];
  int32_T c3_i546;
  real_T c3_cb_y[9];
  int32_T c3_i547;
  real_T c3_pb_a[9];
  int32_T c3_i548;
  real_T c3_f_r3[3];
  real_T c3_mb_b[9];
  int32_T c3_i549;
  real_T c3_jd_A[9];
  int32_T c3_i550;
  real_T c3_jd_B[9];
  int32_T c3_i551;
  real_T c3_kd_A[9];
  int32_T c3_i552;
  real_T c3_kd_B[9];
  int32_T c3_i553;
  real_T c3_ld_A[9];
  int32_T c3_i554;
  real_T c3_ld_B[9];
  int32_T c3_i555;
  int32_T c3_i556;
  int32_T c3_i557;
  real_T c3_db_y[9];
  int32_T c3_i558;
  int32_T c3_i559;
  int32_T c3_i560;
  int32_T c3_i561;
  int32_T c3_i562;
  int32_T c3_i563;
  int32_T c3_i564;
  int32_T c3_i565;
  int32_T c3_i566;
  int32_T c3_i567;
  int32_T c3_i568;
  int32_T c3_i569;
  int32_T c3_i570;
  int32_T c3_i571;
  int32_T c3_i572;
  int32_T c3_i573;
  int32_T c3_i574;
  int32_T c3_i575;
  int32_T c3_i576;
  real_T c3_d_x[9];
  int32_T c3_g_k;
  int32_T c3_h_k;
  real_T c3_qb_a;
  int32_T c3_i577;
  real_T c3_eb_y[9];
  real_T c3_rb_a;
  int32_T c3_i578;
  real_T c3_c_r4[3];
  real_T c3_nb_b[9];
  int32_T c3_i579;
  real_T c3_fb_y[9];
  real_T c3_sb_a;
  int32_T c3_i580;
  real_T c3_d_r4[3];
  real_T c3_ob_b[9];
  int32_T c3_i581;
  real_T c3_gb_y[9];
  real_T c3_tb_a;
  int32_T c3_i582;
  real_T c3_e_r4[3];
  real_T c3_pb_b[9];
  int32_T c3_i583;
  real_T c3_hb_y[9];
  int32_T c3_i584;
  real_T c3_ub_a[9];
  int32_T c3_i585;
  real_T c3_f_r4[3];
  real_T c3_qb_b[9];
  int32_T c3_i586;
  real_T c3_md_A[9];
  int32_T c3_i587;
  real_T c3_md_B[9];
  int32_T c3_i588;
  real_T c3_nd_A[9];
  int32_T c3_i589;
  real_T c3_nd_B[9];
  int32_T c3_i590;
  real_T c3_od_A[9];
  int32_T c3_i591;
  real_T c3_od_B[9];
  int32_T c3_i592;
  int32_T c3_i593;
  int32_T c3_i594;
  real_T c3_ib_y[9];
  int32_T c3_i595;
  int32_T c3_i596;
  int32_T c3_i597;
  int32_T c3_i598;
  int32_T c3_i599;
  int32_T c3_i600;
  int32_T c3_i601;
  int32_T c3_i602;
  int32_T c3_i603;
  int32_T c3_i604;
  int32_T c3_i605;
  int32_T c3_i606;
  int32_T c3_i607;
  int32_T c3_i608;
  int32_T c3_i609;
  int32_T c3_i610;
  int32_T c3_i611;
  int32_T c3_i612;
  int32_T c3_i613;
  real_T c3_e_x[9];
  int32_T c3_i_k;
  int32_T c3_j_k;
  real_T c3_vb_a;
  int32_T c3_i614;
  real_T c3_jb_y[9];
  real_T c3_wb_a;
  int32_T c3_i615;
  real_T c3_c_r5[3];
  real_T c3_rb_b[9];
  int32_T c3_i616;
  real_T c3_kb_y[9];
  real_T c3_xb_a;
  int32_T c3_i617;
  real_T c3_d_r5[3];
  real_T c3_sb_b[9];
  int32_T c3_i618;
  real_T c3_lb_y[9];
  real_T c3_yb_a;
  int32_T c3_i619;
  real_T c3_e_r5[3];
  real_T c3_tb_b[9];
  int32_T c3_i620;
  real_T c3_mb_y[9];
  int32_T c3_i621;
  real_T c3_ac_a[9];
  int32_T c3_i622;
  real_T c3_f_r5[3];
  real_T c3_ub_b[9];
  int32_T c3_i623;
  real_T c3_pd_A[9];
  int32_T c3_i624;
  real_T c3_pd_B[9];
  int32_T c3_i625;
  real_T c3_qd_A[9];
  int32_T c3_i626;
  real_T c3_qd_B[9];
  int32_T c3_i627;
  real_T c3_rd_A[9];
  int32_T c3_i628;
  real_T c3_rd_B[9];
  int32_T c3_i629;
  int32_T c3_i630;
  int32_T c3_i631;
  real_T c3_nb_y[9];
  int32_T c3_i632;
  int32_T c3_i633;
  int32_T c3_i634;
  int32_T c3_i635;
  int32_T c3_i636;
  int32_T c3_i637;
  int32_T c3_i638;
  int32_T c3_i639;
  int32_T c3_i640;
  int32_T c3_i641;
  int32_T c3_i642;
  int32_T c3_i643;
  int32_T c3_i644;
  int32_T c3_i645;
  int32_T c3_i646;
  int32_T c3_i647;
  int32_T c3_i648;
  int32_T c3_i649;
  int32_T c3_i650;
  real_T c3_f_x[9];
  int32_T c3_k_k;
  int32_T c3_l_k;
  real_T c3_bc_a;
  int32_T c3_i651;
  real_T c3_ob_y[9];
  real_T c3_cc_a;
  int32_T c3_i652;
  real_T c3_c_r6[3];
  real_T c3_vb_b[9];
  int32_T c3_i653;
  real_T c3_pb_y[9];
  real_T c3_dc_a;
  int32_T c3_i654;
  real_T c3_d_r6[3];
  real_T c3_wb_b[9];
  int32_T c3_i655;
  real_T c3_qb_y[9];
  real_T c3_ec_a;
  int32_T c3_i656;
  real_T c3_e_r6[3];
  real_T c3_xb_b[9];
  int32_T c3_i657;
  real_T c3_rb_y[9];
  int32_T c3_i658;
  real_T c3_fc_a[9];
  int32_T c3_i659;
  real_T c3_f_r6[3];
  real_T c3_yb_b[9];
  int32_T c3_i660;
  real_T c3_sd_A[9];
  int32_T c3_i661;
  real_T c3_sd_B[9];
  int32_T c3_i662;
  real_T c3_td_A[9];
  int32_T c3_i663;
  real_T c3_td_B[9];
  int32_T c3_i664;
  real_T c3_ud_A[9];
  int32_T c3_i665;
  real_T c3_ud_B[9];
  int32_T c3_i666;
  int32_T c3_i667;
  int32_T c3_i668;
  real_T c3_sb_y[9];
  int32_T c3_i669;
  int32_T c3_i670;
  int32_T c3_i671;
  int32_T c3_i672;
  int32_T c3_i673;
  int32_T c3_i674;
  int32_T c3_i675;
  int32_T c3_i676;
  int32_T c3_i677;
  int32_T c3_i678;
  int32_T c3_i679;
  int32_T c3_i680;
  int32_T c3_i681;
  int32_T c3_i682;
  int32_T c3_i683;
  int32_T c3_i684;
  int32_T c3_i685;
  int32_T c3_i686;
  int32_T c3_i687;
  int32_T c3_i688;
  static real_T c3_dv50[6] = { 0.0, 0.0, 9.8, 0.0, 0.0, 0.0 };

  int32_T c3_i689;
  real_T c3_gc_a[16];
  int32_T c3_i690;
  real_T c3_dv51[6];
  real_T c3_ac_b[16];
  int32_T c3_i691;
  real_T c3_vd_A[16];
  int32_T c3_i692;
  real_T c3_vd_B[16];
  int32_T c3_i693;
  int32_T c3_i694;
  real_T c3_wd_A[16];
  int32_T c3_i695;
  real_T c3_wd_B[16];
  int32_T c3_i696;
  real_T c3_xd_A[16];
  int32_T c3_i697;
  real_T c3_xd_B[16];
  int32_T c3_i698;
  int32_T c3_i699;
  int32_T c3_i700;
  int32_T c3_i701;
  int32_T c3_i702;
  int32_T c3_i703;
  real_T c3_b_g01[16];
  int32_T c3_i704;
  static real_T c3_dv52[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c3_dv53[16];
  real_T c3_dv54[16];
  int32_T c3_i705;
  real_T c3_dv55[16];
  real_T c3_dv56[36];
  int32_T c3_i706;
  int32_T c3_i707;
  real_T c3_hc_a[36];
  int32_T c3_i708;
  real_T c3_ic_a[36];
  int32_T c3_i709;
  real_T c3_dv57[6];
  int32_T c3_i710;
  real_T c3_dv58[6];
  real_T c3_tb_y[6];
  real_T c3_bc_b;
  int32_T c3_i711;
  real_T c3_ub_y[6];
  int32_T c3_i712;
  real_T c3_cc_b;
  int32_T c3_i713;
  real_T c3_vb_y[6];
  int32_T c3_i714;
  real_T c3_jc_a[36];
  int32_T c3_i715;
  real_T c3_kc_a[36];
  int32_T c3_i716;
  real_T c3_dv59[6];
  int32_T c3_i717;
  real_T c3_dv60[6];
  real_T c3_wb_y[6];
  real_T c3_dc_b;
  int32_T c3_i718;
  real_T c3_xb_y[6];
  int32_T c3_i719;
  real_T c3_lc_a[36];
  int32_T c3_i720;
  real_T c3_mc_a[36];
  int32_T c3_i721;
  real_T c3_dv61[6];
  int32_T c3_i722;
  real_T c3_dv62[6];
  real_T c3_yb_y[6];
  int32_T c3_i723;
  real_T c3_ac_y[6];
  real_T c3_nc_a[36];
  int32_T c3_i724;
  real_T c3_ec_b[6];
  int32_T c3_i725;
  real_T c3_oc_a[36];
  int32_T c3_i726;
  real_T c3_fc_b[6];
  int32_T c3_i727;
  real_T c3_dv63[6];
  real_T c3_bc_y[6];
  int32_T c3_i728;
  int32_T c3_i729;
  int32_T c3_i730;
  int32_T c3_i731;
  real_T c3_pc_a[16];
  int32_T c3_i732;
  real_T c3_dv64[6];
  real_T c3_gc_b[16];
  int32_T c3_i733;
  real_T c3_yd_A[16];
  int32_T c3_i734;
  real_T c3_yd_B[16];
  int32_T c3_i735;
  int32_T c3_i736;
  real_T c3_ae_A[16];
  int32_T c3_i737;
  real_T c3_ae_B[16];
  int32_T c3_i738;
  real_T c3_be_A[16];
  int32_T c3_i739;
  real_T c3_be_B[16];
  int32_T c3_i740;
  int32_T c3_i741;
  int32_T c3_i742;
  int32_T c3_i743;
  int32_T c3_i744;
  int32_T c3_i745;
  real_T c3_b_g12[16];
  int32_T c3_i746;
  real_T c3_dv65[16];
  real_T c3_dv66[16];
  int32_T c3_i747;
  real_T c3_dv67[16];
  real_T c3_dv68[36];
  int32_T c3_i748;
  int32_T c3_i749;
  real_T c3_qc_a[36];
  int32_T c3_i750;
  real_T c3_hc_b[6];
  int32_T c3_i751;
  real_T c3_rc_a[36];
  int32_T c3_i752;
  real_T c3_ic_b[6];
  int32_T c3_i753;
  real_T c3_dv69[6];
  real_T c3_cc_y[6];
  real_T c3_jc_b;
  int32_T c3_i754;
  real_T c3_dc_y[6];
  int32_T c3_i755;
  real_T c3_kc_b;
  int32_T c3_i756;
  real_T c3_ec_y[6];
  int32_T c3_i757;
  real_T c3_sc_a[36];
  int32_T c3_i758;
  real_T c3_lc_b[6];
  int32_T c3_i759;
  real_T c3_tc_a[36];
  int32_T c3_i760;
  real_T c3_mc_b[6];
  int32_T c3_i761;
  real_T c3_dv70[6];
  real_T c3_fc_y[6];
  real_T c3_nc_b;
  int32_T c3_i762;
  real_T c3_gc_y[6];
  int32_T c3_i763;
  real_T c3_uc_a[36];
  int32_T c3_i764;
  real_T c3_oc_b[6];
  int32_T c3_i765;
  real_T c3_vc_a[36];
  int32_T c3_i766;
  real_T c3_pc_b[6];
  int32_T c3_i767;
  real_T c3_dv71[6];
  real_T c3_hc_y[6];
  int32_T c3_i768;
  real_T c3_ic_y[6];
  real_T c3_wc_a[36];
  int32_T c3_i769;
  real_T c3_qc_b[6];
  int32_T c3_i770;
  real_T c3_xc_a[36];
  int32_T c3_i771;
  real_T c3_rc_b[6];
  int32_T c3_i772;
  real_T c3_dv72[6];
  real_T c3_jc_y[6];
  int32_T c3_i773;
  int32_T c3_i774;
  int32_T c3_i775;
  int32_T c3_i776;
  real_T c3_yc_a[16];
  int32_T c3_i777;
  real_T c3_dv73[6];
  real_T c3_sc_b[16];
  int32_T c3_i778;
  real_T c3_ce_A[16];
  int32_T c3_i779;
  real_T c3_ce_B[16];
  int32_T c3_i780;
  int32_T c3_i781;
  real_T c3_de_A[16];
  int32_T c3_i782;
  real_T c3_de_B[16];
  int32_T c3_i783;
  real_T c3_ee_A[16];
  int32_T c3_i784;
  real_T c3_ee_B[16];
  int32_T c3_i785;
  int32_T c3_i786;
  int32_T c3_i787;
  int32_T c3_i788;
  int32_T c3_i789;
  int32_T c3_i790;
  real_T c3_b_g23[16];
  int32_T c3_i791;
  real_T c3_dv74[16];
  real_T c3_dv75[16];
  int32_T c3_i792;
  real_T c3_dv76[16];
  real_T c3_dv77[36];
  int32_T c3_i793;
  int32_T c3_i794;
  real_T c3_ad_a[36];
  int32_T c3_i795;
  real_T c3_tc_b[6];
  int32_T c3_i796;
  real_T c3_bd_a[36];
  int32_T c3_i797;
  real_T c3_uc_b[6];
  int32_T c3_i798;
  real_T c3_dv78[6];
  real_T c3_kc_y[6];
  real_T c3_vc_b;
  int32_T c3_i799;
  real_T c3_lc_y[6];
  int32_T c3_i800;
  real_T c3_wc_b;
  int32_T c3_i801;
  real_T c3_mc_y[6];
  int32_T c3_i802;
  real_T c3_cd_a[36];
  int32_T c3_i803;
  real_T c3_xc_b[6];
  int32_T c3_i804;
  real_T c3_dd_a[36];
  int32_T c3_i805;
  real_T c3_yc_b[6];
  int32_T c3_i806;
  real_T c3_dv79[6];
  real_T c3_nc_y[6];
  real_T c3_ad_b;
  int32_T c3_i807;
  real_T c3_oc_y[6];
  int32_T c3_i808;
  real_T c3_ed_a[36];
  int32_T c3_i809;
  real_T c3_bd_b[6];
  int32_T c3_i810;
  real_T c3_fd_a[36];
  int32_T c3_i811;
  real_T c3_cd_b[6];
  int32_T c3_i812;
  real_T c3_dv80[6];
  real_T c3_pc_y[6];
  int32_T c3_i813;
  real_T c3_qc_y[6];
  real_T c3_gd_a[36];
  int32_T c3_i814;
  real_T c3_dd_b[6];
  int32_T c3_i815;
  real_T c3_hd_a[36];
  int32_T c3_i816;
  real_T c3_ed_b[6];
  int32_T c3_i817;
  real_T c3_dv81[6];
  real_T c3_rc_y[6];
  int32_T c3_i818;
  int32_T c3_i819;
  int32_T c3_i820;
  int32_T c3_i821;
  real_T c3_id_a[16];
  int32_T c3_i822;
  real_T c3_dv82[6];
  real_T c3_fd_b[16];
  int32_T c3_i823;
  real_T c3_fe_A[16];
  int32_T c3_i824;
  real_T c3_fe_B[16];
  int32_T c3_i825;
  int32_T c3_i826;
  real_T c3_ge_A[16];
  int32_T c3_i827;
  real_T c3_ge_B[16];
  int32_T c3_i828;
  real_T c3_he_A[16];
  int32_T c3_i829;
  real_T c3_he_B[16];
  int32_T c3_i830;
  int32_T c3_i831;
  int32_T c3_i832;
  int32_T c3_i833;
  int32_T c3_i834;
  int32_T c3_i835;
  real_T c3_b_g34[16];
  int32_T c3_i836;
  real_T c3_dv83[16];
  real_T c3_dv84[16];
  int32_T c3_i837;
  real_T c3_dv85[16];
  real_T c3_dv86[36];
  int32_T c3_i838;
  int32_T c3_i839;
  real_T c3_jd_a[36];
  int32_T c3_i840;
  real_T c3_gd_b[6];
  int32_T c3_i841;
  real_T c3_kd_a[36];
  int32_T c3_i842;
  real_T c3_hd_b[6];
  int32_T c3_i843;
  real_T c3_dv87[6];
  real_T c3_sc_y[6];
  real_T c3_id_b;
  int32_T c3_i844;
  real_T c3_tc_y[6];
  int32_T c3_i845;
  real_T c3_jd_b;
  int32_T c3_i846;
  real_T c3_uc_y[6];
  int32_T c3_i847;
  real_T c3_ld_a[36];
  int32_T c3_i848;
  real_T c3_kd_b[6];
  int32_T c3_i849;
  real_T c3_md_a[36];
  int32_T c3_i850;
  real_T c3_ld_b[6];
  int32_T c3_i851;
  real_T c3_dv88[6];
  real_T c3_vc_y[6];
  real_T c3_md_b;
  int32_T c3_i852;
  real_T c3_wc_y[6];
  int32_T c3_i853;
  real_T c3_nd_a[36];
  int32_T c3_i854;
  real_T c3_nd_b[6];
  int32_T c3_i855;
  real_T c3_od_a[36];
  int32_T c3_i856;
  real_T c3_od_b[6];
  int32_T c3_i857;
  real_T c3_dv89[6];
  real_T c3_xc_y[6];
  int32_T c3_i858;
  real_T c3_yc_y[6];
  real_T c3_pd_a[36];
  int32_T c3_i859;
  real_T c3_pd_b[6];
  int32_T c3_i860;
  real_T c3_qd_a[36];
  int32_T c3_i861;
  real_T c3_qd_b[6];
  int32_T c3_i862;
  real_T c3_dv90[6];
  real_T c3_ad_y[6];
  int32_T c3_i863;
  int32_T c3_i864;
  int32_T c3_i865;
  int32_T c3_i866;
  real_T c3_rd_a[16];
  int32_T c3_i867;
  real_T c3_dv91[6];
  real_T c3_rd_b[16];
  int32_T c3_i868;
  real_T c3_ie_A[16];
  int32_T c3_i869;
  real_T c3_ie_B[16];
  int32_T c3_i870;
  int32_T c3_i871;
  real_T c3_je_A[16];
  int32_T c3_i872;
  real_T c3_je_B[16];
  int32_T c3_i873;
  real_T c3_ke_A[16];
  int32_T c3_i874;
  real_T c3_ke_B[16];
  int32_T c3_i875;
  int32_T c3_i876;
  int32_T c3_i877;
  int32_T c3_i878;
  int32_T c3_i879;
  int32_T c3_i880;
  real_T c3_b_g45[16];
  int32_T c3_i881;
  real_T c3_dv92[16];
  real_T c3_dv93[16];
  int32_T c3_i882;
  real_T c3_dv94[16];
  real_T c3_dv95[36];
  int32_T c3_i883;
  int32_T c3_i884;
  real_T c3_sd_a[36];
  int32_T c3_i885;
  real_T c3_sd_b[6];
  int32_T c3_i886;
  real_T c3_td_a[36];
  int32_T c3_i887;
  real_T c3_td_b[6];
  int32_T c3_i888;
  real_T c3_dv96[6];
  real_T c3_bd_y[6];
  real_T c3_ud_b;
  int32_T c3_i889;
  real_T c3_cd_y[6];
  int32_T c3_i890;
  real_T c3_vd_b;
  int32_T c3_i891;
  real_T c3_dd_y[6];
  int32_T c3_i892;
  real_T c3_ud_a[36];
  int32_T c3_i893;
  real_T c3_wd_b[6];
  int32_T c3_i894;
  real_T c3_vd_a[36];
  int32_T c3_i895;
  real_T c3_xd_b[6];
  int32_T c3_i896;
  real_T c3_dv97[6];
  real_T c3_ed_y[6];
  real_T c3_yd_b;
  int32_T c3_i897;
  real_T c3_fd_y[6];
  int32_T c3_i898;
  real_T c3_wd_a[36];
  int32_T c3_i899;
  real_T c3_ae_b[6];
  int32_T c3_i900;
  real_T c3_xd_a[36];
  int32_T c3_i901;
  real_T c3_be_b[6];
  int32_T c3_i902;
  real_T c3_dv98[6];
  real_T c3_gd_y[6];
  int32_T c3_i903;
  real_T c3_hd_y[6];
  real_T c3_yd_a[36];
  int32_T c3_i904;
  real_T c3_ce_b[6];
  int32_T c3_i905;
  real_T c3_ae_a[36];
  int32_T c3_i906;
  real_T c3_de_b[6];
  int32_T c3_i907;
  real_T c3_dv99[6];
  real_T c3_id_y[6];
  int32_T c3_i908;
  int32_T c3_i909;
  int32_T c3_i910;
  int32_T c3_i911;
  real_T c3_be_a[16];
  int32_T c3_i912;
  real_T c3_dv100[6];
  real_T c3_ee_b[16];
  int32_T c3_i913;
  real_T c3_le_A[16];
  int32_T c3_i914;
  real_T c3_le_B[16];
  int32_T c3_i915;
  int32_T c3_i916;
  real_T c3_me_A[16];
  int32_T c3_i917;
  real_T c3_me_B[16];
  int32_T c3_i918;
  real_T c3_ne_A[16];
  int32_T c3_i919;
  real_T c3_ne_B[16];
  int32_T c3_i920;
  int32_T c3_i921;
  int32_T c3_i922;
  int32_T c3_i923;
  int32_T c3_i924;
  int32_T c3_i925;
  real_T c3_b_g56[16];
  int32_T c3_i926;
  real_T c3_dv101[16];
  real_T c3_dv102[16];
  int32_T c3_i927;
  real_T c3_dv103[16];
  real_T c3_dv104[36];
  int32_T c3_i928;
  int32_T c3_i929;
  real_T c3_ce_a[36];
  int32_T c3_i930;
  real_T c3_fe_b[6];
  int32_T c3_i931;
  real_T c3_de_a[36];
  int32_T c3_i932;
  real_T c3_ge_b[6];
  int32_T c3_i933;
  real_T c3_dv105[6];
  real_T c3_jd_y[6];
  real_T c3_he_b;
  int32_T c3_i934;
  real_T c3_kd_y[6];
  int32_T c3_i935;
  real_T c3_ie_b;
  int32_T c3_i936;
  real_T c3_ld_y[6];
  int32_T c3_i937;
  real_T c3_ee_a[36];
  int32_T c3_i938;
  real_T c3_je_b[6];
  int32_T c3_i939;
  real_T c3_fe_a[36];
  int32_T c3_i940;
  real_T c3_ke_b[6];
  int32_T c3_i941;
  real_T c3_dv106[6];
  real_T c3_md_y[6];
  real_T c3_le_b;
  int32_T c3_i942;
  real_T c3_nd_y[6];
  int32_T c3_i943;
  real_T c3_ge_a[36];
  int32_T c3_i944;
  real_T c3_me_b[6];
  int32_T c3_i945;
  real_T c3_he_a[36];
  int32_T c3_i946;
  real_T c3_ne_b[6];
  int32_T c3_i947;
  real_T c3_dv107[6];
  real_T c3_od_y[6];
  int32_T c3_i948;
  real_T c3_pd_y[6];
  real_T c3_ie_a[36];
  int32_T c3_i949;
  real_T c3_oe_b[6];
  int32_T c3_i950;
  real_T c3_je_a[36];
  int32_T c3_i951;
  real_T c3_pe_b[6];
  int32_T c3_i952;
  real_T c3_dv108[6];
  real_T c3_qd_y[6];
  int32_T c3_i953;
  int32_T c3_i954;
  int32_T c3_i955;
  int32_T c3_i956;
  int32_T c3_i957;
  int32_T c3_i958;
  real_T c3_b_g67_0[16];
  int32_T c3_i959;
  real_T c3_dv109[16];
  real_T c3_dv110[16];
  int32_T c3_i960;
  real_T c3_dv111[16];
  real_T c3_dv112[36];
  int32_T c3_i961;
  int32_T c3_i962;
  int32_T c3_i963;
  int32_T c3_i964;
  int32_T c3_i965;
  real_T c3_ke_a[36];
  int32_T c3_i966;
  real_T c3_qe_b[6];
  int32_T c3_i967;
  real_T c3_le_a[36];
  int32_T c3_i968;
  real_T c3_re_b[6];
  int32_T c3_i969;
  real_T c3_dv113[6];
  real_T c3_rd_y[6];
  int32_T c3_i970;
  real_T c3_me_a[36];
  int32_T c3_i971;
  real_T c3_se_b[6];
  int32_T c3_i972;
  real_T c3_ne_a[36];
  int32_T c3_i973;
  real_T c3_te_b[6];
  int32_T c3_i974;
  real_T c3_dv114[6];
  real_T c3_sd_y[6];
  int32_T c3_i975;
  real_T c3_b_V6[6];
  real_T c3_dv115[36];
  int32_T c3_i976;
  int32_T c3_i977;
  int32_T c3_i978;
  int32_T c3_i979;
  real_T c3_oe_a[36];
  int32_T c3_i980;
  real_T c3_ue_b[36];
  int32_T c3_i981;
  real_T c3_oe_A[36];
  int32_T c3_i982;
  real_T c3_oe_B[36];
  int32_T c3_i983;
  real_T c3_pe_A[36];
  int32_T c3_i984;
  real_T c3_pe_B[36];
  int32_T c3_i985;
  real_T c3_qe_A[36];
  int32_T c3_i986;
  real_T c3_qe_B[36];
  int32_T c3_i987;
  real_T c3_dv116[36];
  real_T c3_td_y[36];
  int32_T c3_i988;
  real_T c3_pe_a[36];
  int32_T c3_i989;
  real_T c3_ve_b[6];
  int32_T c3_i990;
  real_T c3_qe_a[36];
  int32_T c3_i991;
  real_T c3_we_b[6];
  int32_T c3_i992;
  real_T c3_dv117[6];
  real_T c3_ud_y[6];
  int32_T c3_i993;
  int32_T c3_i994;
  real_T c3_xe_b[6];
  int32_T c3_i995;
  real_T c3_vd_y[6];
  int32_T c3_i996;
  real_T c3_wd_y[6];
  int32_T c3_i997;
  real_T c3_xd_y[6];
  int32_T c3_i998;
  real_T c3_dv118[6];
  int32_T c3_i999;
  real_T c3_yd_y[6];
  real_T c3_ae_y;
  int32_T c3_i1000;
  int32_T c3_i1001;
  int32_T c3_i1002;
  int32_T c3_i1003;
  int32_T c3_i1004;
  real_T c3_re_a[36];
  int32_T c3_i1005;
  real_T c3_ye_b[6];
  int32_T c3_i1006;
  real_T c3_se_a[36];
  int32_T c3_i1007;
  real_T c3_af_b[6];
  int32_T c3_i1008;
  real_T c3_dv119[6];
  real_T c3_be_y[6];
  int32_T c3_i1009;
  real_T c3_te_a[36];
  int32_T c3_i1010;
  real_T c3_bf_b[6];
  int32_T c3_i1011;
  real_T c3_ue_a[36];
  int32_T c3_i1012;
  real_T c3_cf_b[6];
  int32_T c3_i1013;
  real_T c3_dv120[6];
  real_T c3_ce_y[6];
  int32_T c3_i1014;
  real_T c3_b_V5[6];
  real_T c3_dv121[36];
  int32_T c3_i1015;
  int32_T c3_i1016;
  int32_T c3_i1017;
  int32_T c3_i1018;
  real_T c3_ve_a[36];
  int32_T c3_i1019;
  real_T c3_df_b[36];
  int32_T c3_i1020;
  real_T c3_re_A[36];
  int32_T c3_i1021;
  real_T c3_re_B[36];
  int32_T c3_i1022;
  real_T c3_se_A[36];
  int32_T c3_i1023;
  real_T c3_se_B[36];
  int32_T c3_i1024;
  real_T c3_te_A[36];
  int32_T c3_i1025;
  real_T c3_te_B[36];
  int32_T c3_i1026;
  real_T c3_dv122[36];
  real_T c3_de_y[36];
  int32_T c3_i1027;
  real_T c3_we_a[36];
  int32_T c3_i1028;
  real_T c3_ef_b[6];
  int32_T c3_i1029;
  real_T c3_xe_a[36];
  int32_T c3_i1030;
  real_T c3_ff_b[6];
  int32_T c3_i1031;
  real_T c3_dv123[6];
  real_T c3_ee_y[6];
  int32_T c3_i1032;
  int32_T c3_i1033;
  real_T c3_gf_b[6];
  int32_T c3_i1034;
  real_T c3_fe_y[6];
  int32_T c3_i1035;
  real_T c3_ge_y[6];
  int32_T c3_i1036;
  real_T c3_he_y[6];
  int32_T c3_i1037;
  real_T c3_dv124[6];
  int32_T c3_i1038;
  real_T c3_ie_y[6];
  real_T c3_je_y;
  int32_T c3_i1039;
  int32_T c3_i1040;
  int32_T c3_i1041;
  int32_T c3_i1042;
  int32_T c3_i1043;
  real_T c3_ye_a[36];
  int32_T c3_i1044;
  real_T c3_hf_b[6];
  int32_T c3_i1045;
  real_T c3_af_a[36];
  int32_T c3_i1046;
  real_T c3_if_b[6];
  int32_T c3_i1047;
  real_T c3_dv125[6];
  real_T c3_ke_y[6];
  int32_T c3_i1048;
  real_T c3_bf_a[36];
  int32_T c3_i1049;
  real_T c3_jf_b[6];
  int32_T c3_i1050;
  real_T c3_cf_a[36];
  int32_T c3_i1051;
  real_T c3_kf_b[6];
  int32_T c3_i1052;
  real_T c3_dv126[6];
  real_T c3_le_y[6];
  int32_T c3_i1053;
  real_T c3_b_V4[6];
  real_T c3_dv127[36];
  int32_T c3_i1054;
  int32_T c3_i1055;
  int32_T c3_i1056;
  int32_T c3_i1057;
  real_T c3_df_a[36];
  int32_T c3_i1058;
  real_T c3_lf_b[36];
  int32_T c3_i1059;
  real_T c3_ue_A[36];
  int32_T c3_i1060;
  real_T c3_ue_B[36];
  int32_T c3_i1061;
  real_T c3_ve_A[36];
  int32_T c3_i1062;
  real_T c3_ve_B[36];
  int32_T c3_i1063;
  real_T c3_we_A[36];
  int32_T c3_i1064;
  real_T c3_we_B[36];
  int32_T c3_i1065;
  real_T c3_dv128[36];
  real_T c3_me_y[36];
  int32_T c3_i1066;
  real_T c3_ef_a[36];
  int32_T c3_i1067;
  real_T c3_mf_b[6];
  int32_T c3_i1068;
  real_T c3_ff_a[36];
  int32_T c3_i1069;
  real_T c3_nf_b[6];
  int32_T c3_i1070;
  real_T c3_dv129[6];
  real_T c3_ne_y[6];
  int32_T c3_i1071;
  int32_T c3_i1072;
  real_T c3_of_b[6];
  int32_T c3_i1073;
  real_T c3_oe_y[6];
  int32_T c3_i1074;
  real_T c3_pe_y[6];
  int32_T c3_i1075;
  real_T c3_qe_y[6];
  int32_T c3_i1076;
  real_T c3_dv130[6];
  int32_T c3_i1077;
  real_T c3_re_y[6];
  real_T c3_se_y;
  int32_T c3_i1078;
  int32_T c3_i1079;
  int32_T c3_i1080;
  int32_T c3_i1081;
  int32_T c3_i1082;
  real_T c3_gf_a[36];
  int32_T c3_i1083;
  real_T c3_pf_b[6];
  int32_T c3_i1084;
  real_T c3_hf_a[36];
  int32_T c3_i1085;
  real_T c3_qf_b[6];
  int32_T c3_i1086;
  real_T c3_dv131[6];
  real_T c3_te_y[6];
  int32_T c3_i1087;
  real_T c3_if_a[36];
  int32_T c3_i1088;
  real_T c3_rf_b[6];
  int32_T c3_i1089;
  real_T c3_jf_a[36];
  int32_T c3_i1090;
  real_T c3_sf_b[6];
  int32_T c3_i1091;
  real_T c3_dv132[6];
  real_T c3_ue_y[6];
  int32_T c3_i1092;
  real_T c3_b_V3[6];
  real_T c3_dv133[36];
  int32_T c3_i1093;
  int32_T c3_i1094;
  int32_T c3_i1095;
  int32_T c3_i1096;
  real_T c3_kf_a[36];
  int32_T c3_i1097;
  real_T c3_tf_b[36];
  int32_T c3_i1098;
  real_T c3_xe_A[36];
  int32_T c3_i1099;
  real_T c3_xe_B[36];
  int32_T c3_i1100;
  real_T c3_ye_A[36];
  int32_T c3_i1101;
  real_T c3_ye_B[36];
  int32_T c3_i1102;
  real_T c3_af_A[36];
  int32_T c3_i1103;
  real_T c3_af_B[36];
  int32_T c3_i1104;
  real_T c3_dv134[36];
  real_T c3_ve_y[36];
  int32_T c3_i1105;
  real_T c3_lf_a[36];
  int32_T c3_i1106;
  real_T c3_uf_b[6];
  int32_T c3_i1107;
  real_T c3_mf_a[36];
  int32_T c3_i1108;
  real_T c3_vf_b[6];
  int32_T c3_i1109;
  real_T c3_dv135[6];
  real_T c3_we_y[6];
  int32_T c3_i1110;
  int32_T c3_i1111;
  real_T c3_wf_b[6];
  int32_T c3_i1112;
  real_T c3_xe_y[6];
  int32_T c3_i1113;
  real_T c3_ye_y[6];
  int32_T c3_i1114;
  real_T c3_af_y[6];
  int32_T c3_i1115;
  real_T c3_dv136[6];
  int32_T c3_i1116;
  real_T c3_bf_y[6];
  real_T c3_cf_y;
  int32_T c3_i1117;
  int32_T c3_i1118;
  int32_T c3_i1119;
  int32_T c3_i1120;
  int32_T c3_i1121;
  real_T c3_nf_a[36];
  int32_T c3_i1122;
  real_T c3_xf_b[6];
  int32_T c3_i1123;
  real_T c3_of_a[36];
  int32_T c3_i1124;
  real_T c3_yf_b[6];
  int32_T c3_i1125;
  real_T c3_dv137[6];
  real_T c3_df_y[6];
  int32_T c3_i1126;
  real_T c3_pf_a[36];
  int32_T c3_i1127;
  real_T c3_ag_b[6];
  int32_T c3_i1128;
  real_T c3_qf_a[36];
  int32_T c3_i1129;
  real_T c3_bg_b[6];
  int32_T c3_i1130;
  real_T c3_dv138[6];
  real_T c3_ef_y[6];
  int32_T c3_i1131;
  real_T c3_b_V2[6];
  real_T c3_dv139[36];
  int32_T c3_i1132;
  int32_T c3_i1133;
  int32_T c3_i1134;
  int32_T c3_i1135;
  real_T c3_rf_a[36];
  int32_T c3_i1136;
  real_T c3_cg_b[36];
  int32_T c3_i1137;
  real_T c3_bf_A[36];
  int32_T c3_i1138;
  real_T c3_bf_B[36];
  int32_T c3_i1139;
  real_T c3_cf_A[36];
  int32_T c3_i1140;
  real_T c3_cf_B[36];
  int32_T c3_i1141;
  real_T c3_df_A[36];
  int32_T c3_i1142;
  real_T c3_df_B[36];
  int32_T c3_i1143;
  real_T c3_dv140[36];
  real_T c3_ff_y[36];
  int32_T c3_i1144;
  real_T c3_sf_a[36];
  int32_T c3_i1145;
  real_T c3_dg_b[6];
  int32_T c3_i1146;
  real_T c3_tf_a[36];
  int32_T c3_i1147;
  real_T c3_eg_b[6];
  int32_T c3_i1148;
  real_T c3_dv141[6];
  real_T c3_gf_y[6];
  int32_T c3_i1149;
  int32_T c3_i1150;
  real_T c3_fg_b[6];
  int32_T c3_i1151;
  real_T c3_hf_y[6];
  int32_T c3_i1152;
  real_T c3_if_y[6];
  int32_T c3_i1153;
  real_T c3_jf_y[6];
  int32_T c3_i1154;
  real_T c3_dv142[6];
  int32_T c3_i1155;
  real_T c3_kf_y[6];
  real_T c3_lf_y;
  int32_T c3_i1156;
  int32_T c3_i1157;
  int32_T c3_i1158;
  int32_T c3_i1159;
  int32_T c3_i1160;
  real_T c3_uf_a[36];
  int32_T c3_i1161;
  real_T c3_gg_b[6];
  int32_T c3_i1162;
  real_T c3_vf_a[36];
  int32_T c3_i1163;
  real_T c3_hg_b[6];
  int32_T c3_i1164;
  real_T c3_dv143[6];
  real_T c3_mf_y[6];
  int32_T c3_i1165;
  real_T c3_wf_a[36];
  int32_T c3_i1166;
  real_T c3_ig_b[6];
  int32_T c3_i1167;
  real_T c3_xf_a[36];
  int32_T c3_i1168;
  real_T c3_jg_b[6];
  int32_T c3_i1169;
  real_T c3_dv144[6];
  real_T c3_nf_y[6];
  int32_T c3_i1170;
  real_T c3_b_V1[6];
  real_T c3_dv145[36];
  int32_T c3_i1171;
  int32_T c3_i1172;
  int32_T c3_i1173;
  int32_T c3_i1174;
  real_T c3_yf_a[36];
  int32_T c3_i1175;
  real_T c3_kg_b[36];
  int32_T c3_i1176;
  real_T c3_ef_A[36];
  int32_T c3_i1177;
  real_T c3_ef_B[36];
  int32_T c3_i1178;
  real_T c3_ff_A[36];
  int32_T c3_i1179;
  real_T c3_ff_B[36];
  int32_T c3_i1180;
  real_T c3_gf_A[36];
  int32_T c3_i1181;
  real_T c3_gf_B[36];
  int32_T c3_i1182;
  real_T c3_dv146[36];
  real_T c3_of_y[36];
  int32_T c3_i1183;
  real_T c3_ag_a[36];
  int32_T c3_i1184;
  real_T c3_lg_b[6];
  int32_T c3_i1185;
  real_T c3_bg_a[36];
  int32_T c3_i1186;
  real_T c3_mg_b[6];
  int32_T c3_i1187;
  real_T c3_dv147[6];
  real_T c3_pf_y[6];
  int32_T c3_i1188;
  int32_T c3_i1189;
  real_T c3_ng_b[6];
  int32_T c3_i1190;
  real_T c3_qf_y[6];
  int32_T c3_i1191;
  real_T c3_rf_y[6];
  int32_T c3_i1192;
  real_T c3_sf_y[6];
  int32_T c3_i1193;
  real_T c3_dv148[6];
  int32_T c3_i1194;
  real_T c3_tf_y[6];
  real_T c3_uf_y;
  int32_T c3_i1195;
  int32_T c3_i1196;
  sf_debug_symbol_scope_push_eml(0U, 93U, 99U, c3_sv1, c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c3_w_o, c3_h_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c3_w_z, c3_h_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_kxi1, c3_b_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_kxi2, c3_b_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c3_kxi3, c3_b_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c3_kxi4, c3_b_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c3_kxi5, c3_b_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c3_kxi6, c3_b_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c3_ez, c3_h_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c3_ex, c3_h_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(c3_eo, c3_h_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(c3_g01_0, c3_i_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(c3_g12_0, c3_i_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(c3_g23_0, c3_i_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(c3_g34_0, c3_i_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(c3_g45_0, c3_i_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(c3_g56_0, c3_i_sf_marshall, 16U);
  sf_debug_symbol_scope_add_eml(c3_g67_0, c3_i_sf_marshall, 17U);
  sf_debug_symbol_scope_add_eml(c3_g, c3_i_sf_marshall, 18U);
  sf_debug_symbol_scope_add_eml(c3_r1, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r2, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r3, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r4, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r5, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r6, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(&c3_m1, c3_f_sf_marshall, 25U);
  sf_debug_symbol_scope_add_eml(c3_I1, c3_g_sf_marshall, 26U);
  sf_debug_symbol_scope_add_eml(c3_M1, c3_j_sf_marshall, 27U);
  sf_debug_symbol_scope_add_eml(&c3_m2, c3_f_sf_marshall, 28U);
  sf_debug_symbol_scope_add_eml(c3_I2, c3_g_sf_marshall, 29U);
  sf_debug_symbol_scope_add_eml(c3_M2, c3_j_sf_marshall, 30U);
  sf_debug_symbol_scope_add_eml(&c3_m3, c3_f_sf_marshall, 31U);
  sf_debug_symbol_scope_add_eml(c3_I3, c3_g_sf_marshall, 32U);
  sf_debug_symbol_scope_add_eml(c3_M3, c3_j_sf_marshall, 33U);
  sf_debug_symbol_scope_add_eml(&c3_m4, c3_f_sf_marshall, 34U);
  sf_debug_symbol_scope_add_eml(c3_I4, c3_g_sf_marshall, 35U);
  sf_debug_symbol_scope_add_eml(c3_M4, c3_j_sf_marshall, 36U);
  sf_debug_symbol_scope_add_eml(&c3_m5, c3_f_sf_marshall, 37U);
  sf_debug_symbol_scope_add_eml(c3_I5, c3_g_sf_marshall, 38U);
  sf_debug_symbol_scope_add_eml(c3_M5, c3_j_sf_marshall, 39U);
  sf_debug_symbol_scope_add_eml(&c3_m6, c3_f_sf_marshall, 40U);
  sf_debug_symbol_scope_add_eml(c3_I6, c3_g_sf_marshall, 41U);
  sf_debug_symbol_scope_add_eml(c3_M6, c3_j_sf_marshall, 42U);
  sf_debug_symbol_scope_add_eml(c3_V0, c3_b_sf_marshall, 43U);
  sf_debug_symbol_scope_add_eml(c3_dV0, c3_b_sf_marshall, 44U);
  sf_debug_symbol_scope_add_eml(c3_g01, c3_i_sf_marshall, 45U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg01, c3_j_sf_marshall, 46U);
  sf_debug_symbol_scope_add_eml(c3_V1, c3_b_sf_marshall, 47U);
  sf_debug_symbol_scope_add_eml(c3_dV1, c3_b_sf_marshall, 48U);
  sf_debug_symbol_scope_add_eml(c3_g12, c3_i_sf_marshall, 49U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg12, c3_j_sf_marshall, 50U);
  sf_debug_symbol_scope_add_eml(c3_V2, c3_b_sf_marshall, 51U);
  sf_debug_symbol_scope_add_eml(c3_dV2, c3_b_sf_marshall, 52U);
  sf_debug_symbol_scope_add_eml(c3_g23, c3_i_sf_marshall, 53U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg23, c3_j_sf_marshall, 54U);
  sf_debug_symbol_scope_add_eml(c3_V3, c3_b_sf_marshall, 55U);
  sf_debug_symbol_scope_add_eml(c3_dV3, c3_b_sf_marshall, 56U);
  sf_debug_symbol_scope_add_eml(c3_g34, c3_i_sf_marshall, 57U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg34, c3_j_sf_marshall, 58U);
  sf_debug_symbol_scope_add_eml(c3_V4, c3_b_sf_marshall, 59U);
  sf_debug_symbol_scope_add_eml(c3_dV4, c3_b_sf_marshall, 60U);
  sf_debug_symbol_scope_add_eml(c3_g45, c3_i_sf_marshall, 61U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg45, c3_j_sf_marshall, 62U);
  sf_debug_symbol_scope_add_eml(c3_V5, c3_b_sf_marshall, 63U);
  sf_debug_symbol_scope_add_eml(c3_dV5, c3_b_sf_marshall, 64U);
  sf_debug_symbol_scope_add_eml(c3_g56, c3_i_sf_marshall, 65U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg56, c3_j_sf_marshall, 66U);
  sf_debug_symbol_scope_add_eml(c3_V6, c3_b_sf_marshall, 67U);
  sf_debug_symbol_scope_add_eml(c3_dV6, c3_b_sf_marshall, 68U);
  sf_debug_symbol_scope_add_eml(c3_Tau, c3_b_sf_marshall, 69U);
  sf_debug_symbol_scope_add_eml(c3_F7, c3_b_sf_marshall, 70U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg67, c3_j_sf_marshall, 71U);
  sf_debug_symbol_scope_add_eml(c3_F6, c3_b_sf_marshall, 72U);
  sf_debug_symbol_scope_add_eml(c3_F5, c3_b_sf_marshall, 73U);
  sf_debug_symbol_scope_add_eml(c3_F4, c3_b_sf_marshall, 74U);
  sf_debug_symbol_scope_add_eml(c3_F3, c3_b_sf_marshall, 75U);
  sf_debug_symbol_scope_add_eml(c3_F2, c3_b_sf_marshall, 76U);
  sf_debug_symbol_scope_add_eml(c3_F1, c3_b_sf_marshall, 77U);
  sf_debug_symbol_scope_add_eml(c3_b_r1, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r2, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r3, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r4, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r5, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r6, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 78U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 79U);
  sf_debug_symbol_scope_add_eml(c3_DH, c3_e_sf_marshall, 80U);
  sf_debug_symbol_scope_add_eml(c3_Ma, c3_b_sf_marshall, 81U);
  sf_debug_symbol_scope_add_eml(c3_Cen, c3_d_sf_marshall, 82U);
  sf_debug_symbol_scope_add_eml(c3_Ie, c3_c_sf_marshall, 83U);
  sf_debug_symbol_scope_add_eml(c3_Ft, c3_b_sf_marshall, 84U);
  sf_debug_symbol_scope_add_eml(c3_RefVel, c3_b_sf_marshall, 85U);
  sf_debug_symbol_scope_add_eml(c3_RefAcc, c3_b_sf_marshall, 86U);
  sf_debug_symbol_scope_add_eml(c3_EnPos, c3_b_sf_marshall, 87U);
  sf_debug_symbol_scope_add_eml(c3_EnVel, c3_b_sf_marshall, 88U);
  sf_debug_symbol_scope_add_eml(c3_Torque, c3_b_sf_marshall, 89U);
  sf_debug_symbol_scope_add_eml(c3_JntVel, c3_sf_marshall, 90U);
  sf_debug_symbol_scope_add_eml(c3_JntAcc, c3_sf_marshall, 91U);
  sf_debug_symbol_scope_add_eml(c3_JntF, c3_sf_marshall, 92U);
  CV_SCRIPT_FCN(0, 0);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* @Copyright(c),Googol Shenzhen Tech. Ltd */
  /* @File Name: DynEulerCon.m */
  /* @Author: Dai Dan */
  /* @Version: 1.0 */
  /* @Date: 05/5/2014 */
  /*  */
  /* @Function: DynEulerCon */
  /* @Description: Implementing Newton-Euler Recursion Algorithm(Classic Type) for contorl purpose */
  /* It also makes use of feedback information from encoder */
  /* @Input: */
  /* DH: DH parameters */
  /* Ma: link mass */
  /* Cen: link masss center */
  /* Ie: link inertial */
  /* Ft: generalized force exerted on endeffetor */
  /* RefPos: joint angle frome trajectory generator */
  /* RefVel: joint velocity from trajectory generator */
  /* RefAcc: joint acceleration from trajectory generator */
  /* EnPos: joint angle from encoder */
  /* EnVel: joint velocity from encoder */
  /* EnAcc: joint acceleration from encoder */
  /* @Output: */
  /* Tau: Torque */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  _SFD_SCRIPT_CALL(0, 28);
  for (c3_i75 = 0; c3_i75 < 36; c3_i75 = c3_i75 + 1) {
    c3_JntVel[c3_i75] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 29);
  for (c3_i76 = 0; c3_i76 < 36; c3_i76 = c3_i76 + 1) {
    c3_JntAcc[c3_i76] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 30);
  for (c3_i77 = 0; c3_i77 < 36; c3_i77 = c3_i77 + 1) {
    c3_JntF[c3_i77] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 31);
  for (c3_i78 = 0; c3_i78 < 6; c3_i78 = c3_i78 + 1) {
    c3_Torque[c3_i78] = 0.0;
  }

  /*  %% Calculate kxi in corresponding joint frame, different from in base frame */
  _SFD_SCRIPT_CALL(0, 34);
  for (c3_i79 = 0; c3_i79 < 3; c3_i79 = c3_i79 + 1) {
    c3_w_o[c3_i79] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 35);
  for (c3_i80 = 0; c3_i80 < 3; c3_i80 = c3_i80 + 1) {
    c3_w_z[c3_i80] = c3_dv9[c3_i80];
  }

  _SFD_SCRIPT_CALL(0, 37);
  for (c3_i81 = 0; c3_i81 < 6; c3_i81 = c3_i81 + 1) {
    c3_kxi1[c3_i81] = c3_dv10[c3_i81];
  }

  _SFD_SCRIPT_CALL(0, 38);
  for (c3_i82 = 0; c3_i82 < 6; c3_i82 = c3_i82 + 1) {
    c3_kxi2[c3_i82] = c3_dv10[c3_i82];
  }

  _SFD_SCRIPT_CALL(0, 39);
  for (c3_i83 = 0; c3_i83 < 6; c3_i83 = c3_i83 + 1) {
    c3_kxi3[c3_i83] = c3_dv10[c3_i83];
  }

  _SFD_SCRIPT_CALL(0, 40);
  for (c3_i84 = 0; c3_i84 < 6; c3_i84 = c3_i84 + 1) {
    c3_kxi4[c3_i84] = c3_dv10[c3_i84];
  }

  _SFD_SCRIPT_CALL(0, 41);
  for (c3_i85 = 0; c3_i85 < 6; c3_i85 = c3_i85 + 1) {
    c3_kxi5[c3_i85] = c3_dv10[c3_i85];
  }

  _SFD_SCRIPT_CALL(0, 42);
  for (c3_i86 = 0; c3_i86 < 6; c3_i86 = c3_i86 + 1) {
    c3_kxi6[c3_i86] = c3_dv10[c3_i86];
  }

  /*  %% Calculate initial configuration matrix g_{i-1,i} */
  /*  0: means base frame; */
  /*  1,2,3,4,5,6: means i-th joint frame, Ci */
  /*  7: means endeffector frame */
  /*  DH=[266     300     0       0       1016     0      174; */
  /*      0       0       -pi/2   0       pi      pi       0; */
  /*      0       150     870     170     0       0        0; */
  /*      0       -pi/2   0       -pi/2   -pi/2    -pi/2   0;]; */
  _SFD_SCRIPT_CALL(0, 53);
  for (c3_i87 = 0; c3_i87 < 3; c3_i87 = c3_i87 + 1) {
    c3_ez[c3_i87] = c3_dv9[c3_i87];
  }

  _SFD_SCRIPT_CALL(0, 54);
  for (c3_i88 = 0; c3_i88 < 3; c3_i88 = c3_i88 + 1) {
    c3_ex[c3_i88] = c3_dv11[c3_i88];
  }

  _SFD_SCRIPT_CALL(0, 55);
  for (c3_i89 = 0; c3_i89 < 3; c3_i89 = c3_i89 + 1) {
    c3_eo[c3_i89] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 57);
  for (c3_i90 = 0; c3_i90 < 6; c3_i90 = c3_i90 + 1) {
    c3_dv12[c3_i90] = c3_dv10[c3_i90];
  }

  c3_expg(chartInstance, c3_dv12, c3_DH[1], c3_a);
  for (c3_i91 = 0; c3_i91 < 6; c3_i91 = c3_i91 + 1) {
    c3_dv14[c3_i91] = c3_dv13[c3_i91];
  }

  c3_expg(chartInstance, c3_dv14, c3_DH[0], c3_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i92 = 0; c3_i92 < 16; c3_i92 = c3_i92 + 1) {
    c3_A[c3_i92] = c3_a[c3_i92];
  }

  for (c3_i93 = 0; c3_i93 < 16; c3_i93 = c3_i93 + 1) {
    c3_B[c3_i93] = c3_b[c3_i93];
  }

  for (c3_i94 = 0; c3_i94 < 16; c3_i94 = c3_i94 + 1) {
    c3_b_A[c3_i94] = c3_A[c3_i94];
  }

  for (c3_i95 = 0; c3_i95 < 16; c3_i95 = c3_i95 + 1) {
    c3_b_B[c3_i95] = c3_B[c3_i95];
  }

  for (c3_i96 = 0; c3_i96 < 16; c3_i96 = c3_i96 + 1) {
    c3_c_A[c3_i96] = c3_b_A[c3_i96];
  }

  for (c3_i97 = 0; c3_i97 < 16; c3_i97 = c3_i97 + 1) {
    c3_c_B[c3_i97] = c3_b_B[c3_i97];
  }

  for (c3_i98 = 0; c3_i98 < 4; c3_i98 = c3_i98 + 1) {
    c3_i99 = 0;
    for (c3_i100 = 0; c3_i100 < 4; c3_i100 = c3_i100 + 1) {
      c3_y[c3_i99 + c3_i98] = 0.0;
      c3_i101 = 0;
      for (c3_i102 = 0; c3_i102 < 4; c3_i102 = c3_i102 + 1) {
        c3_y[c3_i99 + c3_i98] = c3_y[c3_i99 + c3_i98] + c3_c_A[c3_i101 + c3_i98]
          * c3_c_B[c3_i102 + c3_i99];
        c3_i101 = c3_i101 + 4;
      }

      c3_i99 = c3_i99 + 4;
    }
  }

  for (c3_i103 = 0; c3_i103 < 16; c3_i103 = c3_i103 + 1) {
    c3_b_a[c3_i103] = c3_y[c3_i103];
  }

  for (c3_i104 = 0; c3_i104 < 6; c3_i104 = c3_i104 + 1) {
    c3_dv16[c3_i104] = c3_dv15[c3_i104];
  }

  c3_expg(chartInstance, c3_dv16, c3_DH[3], c3_b_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i105 = 0; c3_i105 < 16; c3_i105 = c3_i105 + 1) {
    c3_d_A[c3_i105] = c3_b_a[c3_i105];
  }

  for (c3_i106 = 0; c3_i106 < 16; c3_i106 = c3_i106 + 1) {
    c3_d_B[c3_i106] = c3_b_b[c3_i106];
  }

  for (c3_i107 = 0; c3_i107 < 16; c3_i107 = c3_i107 + 1) {
    c3_e_A[c3_i107] = c3_d_A[c3_i107];
  }

  for (c3_i108 = 0; c3_i108 < 16; c3_i108 = c3_i108 + 1) {
    c3_e_B[c3_i108] = c3_d_B[c3_i108];
  }

  for (c3_i109 = 0; c3_i109 < 16; c3_i109 = c3_i109 + 1) {
    c3_f_A[c3_i109] = c3_e_A[c3_i109];
  }

  for (c3_i110 = 0; c3_i110 < 16; c3_i110 = c3_i110 + 1) {
    c3_f_B[c3_i110] = c3_e_B[c3_i110];
  }

  for (c3_i111 = 0; c3_i111 < 4; c3_i111 = c3_i111 + 1) {
    c3_i112 = 0;
    for (c3_i113 = 0; c3_i113 < 4; c3_i113 = c3_i113 + 1) {
      c3_b_y[c3_i112 + c3_i111] = 0.0;
      c3_i114 = 0;
      for (c3_i115 = 0; c3_i115 < 4; c3_i115 = c3_i115 + 1) {
        c3_b_y[c3_i112 + c3_i111] = c3_b_y[c3_i112 + c3_i111] + c3_f_A[c3_i114 +
          c3_i111] * c3_f_B[c3_i115 + c3_i112];
        c3_i114 = c3_i114 + 4;
      }

      c3_i112 = c3_i112 + 4;
    }
  }

  for (c3_i116 = 0; c3_i116 < 16; c3_i116 = c3_i116 + 1) {
    c3_c_a[c3_i116] = c3_b_y[c3_i116];
  }

  for (c3_i117 = 0; c3_i117 < 6; c3_i117 = c3_i117 + 1) {
    c3_dv18[c3_i117] = c3_dv17[c3_i117];
  }

  c3_expg(chartInstance, c3_dv18, c3_DH[2], c3_c_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i118 = 0; c3_i118 < 16; c3_i118 = c3_i118 + 1) {
    c3_g_A[c3_i118] = c3_c_a[c3_i118];
  }

  for (c3_i119 = 0; c3_i119 < 16; c3_i119 = c3_i119 + 1) {
    c3_g_B[c3_i119] = c3_c_b[c3_i119];
  }

  for (c3_i120 = 0; c3_i120 < 16; c3_i120 = c3_i120 + 1) {
    c3_g01_0[c3_i120] = 0.0;
  }

  for (c3_i121 = 0; c3_i121 < 16; c3_i121 = c3_i121 + 1) {
    c3_h_A[c3_i121] = c3_g_A[c3_i121];
  }

  for (c3_i122 = 0; c3_i122 < 16; c3_i122 = c3_i122 + 1) {
    c3_h_B[c3_i122] = c3_g_B[c3_i122];
  }

  for (c3_i123 = 0; c3_i123 < 16; c3_i123 = c3_i123 + 1) {
    c3_i_A[c3_i123] = c3_h_A[c3_i123];
  }

  for (c3_i124 = 0; c3_i124 < 16; c3_i124 = c3_i124 + 1) {
    c3_i_B[c3_i124] = c3_h_B[c3_i124];
  }

  for (c3_i125 = 0; c3_i125 < 4; c3_i125 = c3_i125 + 1) {
    c3_i126 = 0;
    for (c3_i127 = 0; c3_i127 < 4; c3_i127 = c3_i127 + 1) {
      c3_g01_0[c3_i126 + c3_i125] = 0.0;
      c3_i128 = 0;
      for (c3_i129 = 0; c3_i129 < 4; c3_i129 = c3_i129 + 1) {
        c3_g01_0[c3_i126 + c3_i125] = c3_g01_0[c3_i126 + c3_i125] +
          c3_i_A[c3_i128 + c3_i125] * c3_i_B[c3_i129 + c3_i126];
        c3_i128 = c3_i128 + 4;
      }

      c3_i126 = c3_i126 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 58);
  for (c3_i130 = 0; c3_i130 < 6; c3_i130 = c3_i130 + 1) {
    c3_dv19[c3_i130] = c3_dv10[c3_i130];
  }

  c3_expg(chartInstance, c3_dv19, c3_DH[5], c3_d_a);
  for (c3_i131 = 0; c3_i131 < 6; c3_i131 = c3_i131 + 1) {
    c3_dv20[c3_i131] = c3_dv13[c3_i131];
  }

  c3_expg(chartInstance, c3_dv20, c3_DH[4], c3_d_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i132 = 0; c3_i132 < 16; c3_i132 = c3_i132 + 1) {
    c3_j_A[c3_i132] = c3_d_a[c3_i132];
  }

  for (c3_i133 = 0; c3_i133 < 16; c3_i133 = c3_i133 + 1) {
    c3_j_B[c3_i133] = c3_d_b[c3_i133];
  }

  for (c3_i134 = 0; c3_i134 < 16; c3_i134 = c3_i134 + 1) {
    c3_k_A[c3_i134] = c3_j_A[c3_i134];
  }

  for (c3_i135 = 0; c3_i135 < 16; c3_i135 = c3_i135 + 1) {
    c3_k_B[c3_i135] = c3_j_B[c3_i135];
  }

  for (c3_i136 = 0; c3_i136 < 16; c3_i136 = c3_i136 + 1) {
    c3_l_A[c3_i136] = c3_k_A[c3_i136];
  }

  for (c3_i137 = 0; c3_i137 < 16; c3_i137 = c3_i137 + 1) {
    c3_l_B[c3_i137] = c3_k_B[c3_i137];
  }

  for (c3_i138 = 0; c3_i138 < 4; c3_i138 = c3_i138 + 1) {
    c3_i139 = 0;
    for (c3_i140 = 0; c3_i140 < 4; c3_i140 = c3_i140 + 1) {
      c3_c_y[c3_i139 + c3_i138] = 0.0;
      c3_i141 = 0;
      for (c3_i142 = 0; c3_i142 < 4; c3_i142 = c3_i142 + 1) {
        c3_c_y[c3_i139 + c3_i138] = c3_c_y[c3_i139 + c3_i138] + c3_l_A[c3_i141 +
          c3_i138] * c3_l_B[c3_i142 + c3_i139];
        c3_i141 = c3_i141 + 4;
      }

      c3_i139 = c3_i139 + 4;
    }
  }

  for (c3_i143 = 0; c3_i143 < 16; c3_i143 = c3_i143 + 1) {
    c3_e_a[c3_i143] = c3_c_y[c3_i143];
  }

  for (c3_i144 = 0; c3_i144 < 6; c3_i144 = c3_i144 + 1) {
    c3_dv21[c3_i144] = c3_dv15[c3_i144];
  }

  c3_expg(chartInstance, c3_dv21, c3_DH[7], c3_e_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i145 = 0; c3_i145 < 16; c3_i145 = c3_i145 + 1) {
    c3_m_A[c3_i145] = c3_e_a[c3_i145];
  }

  for (c3_i146 = 0; c3_i146 < 16; c3_i146 = c3_i146 + 1) {
    c3_m_B[c3_i146] = c3_e_b[c3_i146];
  }

  for (c3_i147 = 0; c3_i147 < 16; c3_i147 = c3_i147 + 1) {
    c3_n_A[c3_i147] = c3_m_A[c3_i147];
  }

  for (c3_i148 = 0; c3_i148 < 16; c3_i148 = c3_i148 + 1) {
    c3_n_B[c3_i148] = c3_m_B[c3_i148];
  }

  for (c3_i149 = 0; c3_i149 < 16; c3_i149 = c3_i149 + 1) {
    c3_o_A[c3_i149] = c3_n_A[c3_i149];
  }

  for (c3_i150 = 0; c3_i150 < 16; c3_i150 = c3_i150 + 1) {
    c3_o_B[c3_i150] = c3_n_B[c3_i150];
  }

  for (c3_i151 = 0; c3_i151 < 4; c3_i151 = c3_i151 + 1) {
    c3_i152 = 0;
    for (c3_i153 = 0; c3_i153 < 4; c3_i153 = c3_i153 + 1) {
      c3_d_y[c3_i152 + c3_i151] = 0.0;
      c3_i154 = 0;
      for (c3_i155 = 0; c3_i155 < 4; c3_i155 = c3_i155 + 1) {
        c3_d_y[c3_i152 + c3_i151] = c3_d_y[c3_i152 + c3_i151] + c3_o_A[c3_i154 +
          c3_i151] * c3_o_B[c3_i155 + c3_i152];
        c3_i154 = c3_i154 + 4;
      }

      c3_i152 = c3_i152 + 4;
    }
  }

  for (c3_i156 = 0; c3_i156 < 16; c3_i156 = c3_i156 + 1) {
    c3_f_a[c3_i156] = c3_d_y[c3_i156];
  }

  for (c3_i157 = 0; c3_i157 < 6; c3_i157 = c3_i157 + 1) {
    c3_dv22[c3_i157] = c3_dv17[c3_i157];
  }

  c3_expg(chartInstance, c3_dv22, c3_DH[6], c3_f_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i158 = 0; c3_i158 < 16; c3_i158 = c3_i158 + 1) {
    c3_p_A[c3_i158] = c3_f_a[c3_i158];
  }

  for (c3_i159 = 0; c3_i159 < 16; c3_i159 = c3_i159 + 1) {
    c3_p_B[c3_i159] = c3_f_b[c3_i159];
  }

  for (c3_i160 = 0; c3_i160 < 16; c3_i160 = c3_i160 + 1) {
    c3_g12_0[c3_i160] = 0.0;
  }

  for (c3_i161 = 0; c3_i161 < 16; c3_i161 = c3_i161 + 1) {
    c3_q_A[c3_i161] = c3_p_A[c3_i161];
  }

  for (c3_i162 = 0; c3_i162 < 16; c3_i162 = c3_i162 + 1) {
    c3_q_B[c3_i162] = c3_p_B[c3_i162];
  }

  for (c3_i163 = 0; c3_i163 < 16; c3_i163 = c3_i163 + 1) {
    c3_r_A[c3_i163] = c3_q_A[c3_i163];
  }

  for (c3_i164 = 0; c3_i164 < 16; c3_i164 = c3_i164 + 1) {
    c3_r_B[c3_i164] = c3_q_B[c3_i164];
  }

  for (c3_i165 = 0; c3_i165 < 4; c3_i165 = c3_i165 + 1) {
    c3_i166 = 0;
    for (c3_i167 = 0; c3_i167 < 4; c3_i167 = c3_i167 + 1) {
      c3_g12_0[c3_i166 + c3_i165] = 0.0;
      c3_i168 = 0;
      for (c3_i169 = 0; c3_i169 < 4; c3_i169 = c3_i169 + 1) {
        c3_g12_0[c3_i166 + c3_i165] = c3_g12_0[c3_i166 + c3_i165] +
          c3_r_A[c3_i168 + c3_i165] * c3_r_B[c3_i169 + c3_i166];
        c3_i168 = c3_i168 + 4;
      }

      c3_i166 = c3_i166 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 59);
  for (c3_i170 = 0; c3_i170 < 6; c3_i170 = c3_i170 + 1) {
    c3_dv23[c3_i170] = c3_dv10[c3_i170];
  }

  c3_expg(chartInstance, c3_dv23, c3_DH[9], c3_g_a);
  for (c3_i171 = 0; c3_i171 < 6; c3_i171 = c3_i171 + 1) {
    c3_dv24[c3_i171] = c3_dv13[c3_i171];
  }

  c3_expg(chartInstance, c3_dv24, c3_DH[8], c3_g_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i172 = 0; c3_i172 < 16; c3_i172 = c3_i172 + 1) {
    c3_s_A[c3_i172] = c3_g_a[c3_i172];
  }

  for (c3_i173 = 0; c3_i173 < 16; c3_i173 = c3_i173 + 1) {
    c3_s_B[c3_i173] = c3_g_b[c3_i173];
  }

  for (c3_i174 = 0; c3_i174 < 16; c3_i174 = c3_i174 + 1) {
    c3_t_A[c3_i174] = c3_s_A[c3_i174];
  }

  for (c3_i175 = 0; c3_i175 < 16; c3_i175 = c3_i175 + 1) {
    c3_t_B[c3_i175] = c3_s_B[c3_i175];
  }

  for (c3_i176 = 0; c3_i176 < 16; c3_i176 = c3_i176 + 1) {
    c3_u_A[c3_i176] = c3_t_A[c3_i176];
  }

  for (c3_i177 = 0; c3_i177 < 16; c3_i177 = c3_i177 + 1) {
    c3_u_B[c3_i177] = c3_t_B[c3_i177];
  }

  for (c3_i178 = 0; c3_i178 < 4; c3_i178 = c3_i178 + 1) {
    c3_i179 = 0;
    for (c3_i180 = 0; c3_i180 < 4; c3_i180 = c3_i180 + 1) {
      c3_e_y[c3_i179 + c3_i178] = 0.0;
      c3_i181 = 0;
      for (c3_i182 = 0; c3_i182 < 4; c3_i182 = c3_i182 + 1) {
        c3_e_y[c3_i179 + c3_i178] = c3_e_y[c3_i179 + c3_i178] + c3_u_A[c3_i181 +
          c3_i178] * c3_u_B[c3_i182 + c3_i179];
        c3_i181 = c3_i181 + 4;
      }

      c3_i179 = c3_i179 + 4;
    }
  }

  for (c3_i183 = 0; c3_i183 < 16; c3_i183 = c3_i183 + 1) {
    c3_h_a[c3_i183] = c3_e_y[c3_i183];
  }

  for (c3_i184 = 0; c3_i184 < 6; c3_i184 = c3_i184 + 1) {
    c3_dv25[c3_i184] = c3_dv15[c3_i184];
  }

  c3_expg(chartInstance, c3_dv25, c3_DH[11], c3_h_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i185 = 0; c3_i185 < 16; c3_i185 = c3_i185 + 1) {
    c3_v_A[c3_i185] = c3_h_a[c3_i185];
  }

  for (c3_i186 = 0; c3_i186 < 16; c3_i186 = c3_i186 + 1) {
    c3_v_B[c3_i186] = c3_h_b[c3_i186];
  }

  for (c3_i187 = 0; c3_i187 < 16; c3_i187 = c3_i187 + 1) {
    c3_w_A[c3_i187] = c3_v_A[c3_i187];
  }

  for (c3_i188 = 0; c3_i188 < 16; c3_i188 = c3_i188 + 1) {
    c3_w_B[c3_i188] = c3_v_B[c3_i188];
  }

  for (c3_i189 = 0; c3_i189 < 16; c3_i189 = c3_i189 + 1) {
    c3_x_A[c3_i189] = c3_w_A[c3_i189];
  }

  for (c3_i190 = 0; c3_i190 < 16; c3_i190 = c3_i190 + 1) {
    c3_x_B[c3_i190] = c3_w_B[c3_i190];
  }

  for (c3_i191 = 0; c3_i191 < 4; c3_i191 = c3_i191 + 1) {
    c3_i192 = 0;
    for (c3_i193 = 0; c3_i193 < 4; c3_i193 = c3_i193 + 1) {
      c3_f_y[c3_i192 + c3_i191] = 0.0;
      c3_i194 = 0;
      for (c3_i195 = 0; c3_i195 < 4; c3_i195 = c3_i195 + 1) {
        c3_f_y[c3_i192 + c3_i191] = c3_f_y[c3_i192 + c3_i191] + c3_x_A[c3_i194 +
          c3_i191] * c3_x_B[c3_i195 + c3_i192];
        c3_i194 = c3_i194 + 4;
      }

      c3_i192 = c3_i192 + 4;
    }
  }

  for (c3_i196 = 0; c3_i196 < 16; c3_i196 = c3_i196 + 1) {
    c3_i_a[c3_i196] = c3_f_y[c3_i196];
  }

  for (c3_i197 = 0; c3_i197 < 6; c3_i197 = c3_i197 + 1) {
    c3_dv26[c3_i197] = c3_dv17[c3_i197];
  }

  c3_expg(chartInstance, c3_dv26, c3_DH[10], c3_i_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i198 = 0; c3_i198 < 16; c3_i198 = c3_i198 + 1) {
    c3_y_A[c3_i198] = c3_i_a[c3_i198];
  }

  for (c3_i199 = 0; c3_i199 < 16; c3_i199 = c3_i199 + 1) {
    c3_y_B[c3_i199] = c3_i_b[c3_i199];
  }

  for (c3_i200 = 0; c3_i200 < 16; c3_i200 = c3_i200 + 1) {
    c3_g23_0[c3_i200] = 0.0;
  }

  for (c3_i201 = 0; c3_i201 < 16; c3_i201 = c3_i201 + 1) {
    c3_ab_A[c3_i201] = c3_y_A[c3_i201];
  }

  for (c3_i202 = 0; c3_i202 < 16; c3_i202 = c3_i202 + 1) {
    c3_ab_B[c3_i202] = c3_y_B[c3_i202];
  }

  for (c3_i203 = 0; c3_i203 < 16; c3_i203 = c3_i203 + 1) {
    c3_bb_A[c3_i203] = c3_ab_A[c3_i203];
  }

  for (c3_i204 = 0; c3_i204 < 16; c3_i204 = c3_i204 + 1) {
    c3_bb_B[c3_i204] = c3_ab_B[c3_i204];
  }

  for (c3_i205 = 0; c3_i205 < 4; c3_i205 = c3_i205 + 1) {
    c3_i206 = 0;
    for (c3_i207 = 0; c3_i207 < 4; c3_i207 = c3_i207 + 1) {
      c3_g23_0[c3_i206 + c3_i205] = 0.0;
      c3_i208 = 0;
      for (c3_i209 = 0; c3_i209 < 4; c3_i209 = c3_i209 + 1) {
        c3_g23_0[c3_i206 + c3_i205] = c3_g23_0[c3_i206 + c3_i205] +
          c3_bb_A[c3_i208 + c3_i205] * c3_bb_B[c3_i209 + c3_i206];
        c3_i208 = c3_i208 + 4;
      }

      c3_i206 = c3_i206 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 60);
  for (c3_i210 = 0; c3_i210 < 6; c3_i210 = c3_i210 + 1) {
    c3_dv27[c3_i210] = c3_dv10[c3_i210];
  }

  c3_expg(chartInstance, c3_dv27, c3_DH[13], c3_j_a);
  for (c3_i211 = 0; c3_i211 < 6; c3_i211 = c3_i211 + 1) {
    c3_dv28[c3_i211] = c3_dv13[c3_i211];
  }

  c3_expg(chartInstance, c3_dv28, c3_DH[12], c3_j_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i212 = 0; c3_i212 < 16; c3_i212 = c3_i212 + 1) {
    c3_cb_A[c3_i212] = c3_j_a[c3_i212];
  }

  for (c3_i213 = 0; c3_i213 < 16; c3_i213 = c3_i213 + 1) {
    c3_cb_B[c3_i213] = c3_j_b[c3_i213];
  }

  for (c3_i214 = 0; c3_i214 < 16; c3_i214 = c3_i214 + 1) {
    c3_db_A[c3_i214] = c3_cb_A[c3_i214];
  }

  for (c3_i215 = 0; c3_i215 < 16; c3_i215 = c3_i215 + 1) {
    c3_db_B[c3_i215] = c3_cb_B[c3_i215];
  }

  for (c3_i216 = 0; c3_i216 < 16; c3_i216 = c3_i216 + 1) {
    c3_eb_A[c3_i216] = c3_db_A[c3_i216];
  }

  for (c3_i217 = 0; c3_i217 < 16; c3_i217 = c3_i217 + 1) {
    c3_eb_B[c3_i217] = c3_db_B[c3_i217];
  }

  for (c3_i218 = 0; c3_i218 < 4; c3_i218 = c3_i218 + 1) {
    c3_i219 = 0;
    for (c3_i220 = 0; c3_i220 < 4; c3_i220 = c3_i220 + 1) {
      c3_g_y[c3_i219 + c3_i218] = 0.0;
      c3_i221 = 0;
      for (c3_i222 = 0; c3_i222 < 4; c3_i222 = c3_i222 + 1) {
        c3_g_y[c3_i219 + c3_i218] = c3_g_y[c3_i219 + c3_i218] + c3_eb_A[c3_i221
          + c3_i218] * c3_eb_B[c3_i222 + c3_i219];
        c3_i221 = c3_i221 + 4;
      }

      c3_i219 = c3_i219 + 4;
    }
  }

  for (c3_i223 = 0; c3_i223 < 16; c3_i223 = c3_i223 + 1) {
    c3_k_a[c3_i223] = c3_g_y[c3_i223];
  }

  for (c3_i224 = 0; c3_i224 < 6; c3_i224 = c3_i224 + 1) {
    c3_dv29[c3_i224] = c3_dv15[c3_i224];
  }

  c3_expg(chartInstance, c3_dv29, c3_DH[15], c3_k_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i225 = 0; c3_i225 < 16; c3_i225 = c3_i225 + 1) {
    c3_fb_A[c3_i225] = c3_k_a[c3_i225];
  }

  for (c3_i226 = 0; c3_i226 < 16; c3_i226 = c3_i226 + 1) {
    c3_fb_B[c3_i226] = c3_k_b[c3_i226];
  }

  for (c3_i227 = 0; c3_i227 < 16; c3_i227 = c3_i227 + 1) {
    c3_gb_A[c3_i227] = c3_fb_A[c3_i227];
  }

  for (c3_i228 = 0; c3_i228 < 16; c3_i228 = c3_i228 + 1) {
    c3_gb_B[c3_i228] = c3_fb_B[c3_i228];
  }

  for (c3_i229 = 0; c3_i229 < 16; c3_i229 = c3_i229 + 1) {
    c3_hb_A[c3_i229] = c3_gb_A[c3_i229];
  }

  for (c3_i230 = 0; c3_i230 < 16; c3_i230 = c3_i230 + 1) {
    c3_hb_B[c3_i230] = c3_gb_B[c3_i230];
  }

  for (c3_i231 = 0; c3_i231 < 4; c3_i231 = c3_i231 + 1) {
    c3_i232 = 0;
    for (c3_i233 = 0; c3_i233 < 4; c3_i233 = c3_i233 + 1) {
      c3_h_y[c3_i232 + c3_i231] = 0.0;
      c3_i234 = 0;
      for (c3_i235 = 0; c3_i235 < 4; c3_i235 = c3_i235 + 1) {
        c3_h_y[c3_i232 + c3_i231] = c3_h_y[c3_i232 + c3_i231] + c3_hb_A[c3_i234
          + c3_i231] * c3_hb_B[c3_i235 + c3_i232];
        c3_i234 = c3_i234 + 4;
      }

      c3_i232 = c3_i232 + 4;
    }
  }

  for (c3_i236 = 0; c3_i236 < 16; c3_i236 = c3_i236 + 1) {
    c3_l_a[c3_i236] = c3_h_y[c3_i236];
  }

  for (c3_i237 = 0; c3_i237 < 6; c3_i237 = c3_i237 + 1) {
    c3_dv30[c3_i237] = c3_dv17[c3_i237];
  }

  c3_expg(chartInstance, c3_dv30, c3_DH[14], c3_l_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i238 = 0; c3_i238 < 16; c3_i238 = c3_i238 + 1) {
    c3_ib_A[c3_i238] = c3_l_a[c3_i238];
  }

  for (c3_i239 = 0; c3_i239 < 16; c3_i239 = c3_i239 + 1) {
    c3_ib_B[c3_i239] = c3_l_b[c3_i239];
  }

  for (c3_i240 = 0; c3_i240 < 16; c3_i240 = c3_i240 + 1) {
    c3_g34_0[c3_i240] = 0.0;
  }

  for (c3_i241 = 0; c3_i241 < 16; c3_i241 = c3_i241 + 1) {
    c3_jb_A[c3_i241] = c3_ib_A[c3_i241];
  }

  for (c3_i242 = 0; c3_i242 < 16; c3_i242 = c3_i242 + 1) {
    c3_jb_B[c3_i242] = c3_ib_B[c3_i242];
  }

  for (c3_i243 = 0; c3_i243 < 16; c3_i243 = c3_i243 + 1) {
    c3_kb_A[c3_i243] = c3_jb_A[c3_i243];
  }

  for (c3_i244 = 0; c3_i244 < 16; c3_i244 = c3_i244 + 1) {
    c3_kb_B[c3_i244] = c3_jb_B[c3_i244];
  }

  for (c3_i245 = 0; c3_i245 < 4; c3_i245 = c3_i245 + 1) {
    c3_i246 = 0;
    for (c3_i247 = 0; c3_i247 < 4; c3_i247 = c3_i247 + 1) {
      c3_g34_0[c3_i246 + c3_i245] = 0.0;
      c3_i248 = 0;
      for (c3_i249 = 0; c3_i249 < 4; c3_i249 = c3_i249 + 1) {
        c3_g34_0[c3_i246 + c3_i245] = c3_g34_0[c3_i246 + c3_i245] +
          c3_kb_A[c3_i248 + c3_i245] * c3_kb_B[c3_i249 + c3_i246];
        c3_i248 = c3_i248 + 4;
      }

      c3_i246 = c3_i246 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 61);
  for (c3_i250 = 0; c3_i250 < 6; c3_i250 = c3_i250 + 1) {
    c3_dv31[c3_i250] = c3_dv10[c3_i250];
  }

  c3_expg(chartInstance, c3_dv31, c3_DH[17], c3_m_a);
  for (c3_i251 = 0; c3_i251 < 6; c3_i251 = c3_i251 + 1) {
    c3_dv32[c3_i251] = c3_dv13[c3_i251];
  }

  c3_expg(chartInstance, c3_dv32, c3_DH[16], c3_m_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i252 = 0; c3_i252 < 16; c3_i252 = c3_i252 + 1) {
    c3_lb_A[c3_i252] = c3_m_a[c3_i252];
  }

  for (c3_i253 = 0; c3_i253 < 16; c3_i253 = c3_i253 + 1) {
    c3_lb_B[c3_i253] = c3_m_b[c3_i253];
  }

  for (c3_i254 = 0; c3_i254 < 16; c3_i254 = c3_i254 + 1) {
    c3_mb_A[c3_i254] = c3_lb_A[c3_i254];
  }

  for (c3_i255 = 0; c3_i255 < 16; c3_i255 = c3_i255 + 1) {
    c3_mb_B[c3_i255] = c3_lb_B[c3_i255];
  }

  for (c3_i256 = 0; c3_i256 < 16; c3_i256 = c3_i256 + 1) {
    c3_nb_A[c3_i256] = c3_mb_A[c3_i256];
  }

  for (c3_i257 = 0; c3_i257 < 16; c3_i257 = c3_i257 + 1) {
    c3_nb_B[c3_i257] = c3_mb_B[c3_i257];
  }

  for (c3_i258 = 0; c3_i258 < 4; c3_i258 = c3_i258 + 1) {
    c3_i259 = 0;
    for (c3_i260 = 0; c3_i260 < 4; c3_i260 = c3_i260 + 1) {
      c3_i_y[c3_i259 + c3_i258] = 0.0;
      c3_i261 = 0;
      for (c3_i262 = 0; c3_i262 < 4; c3_i262 = c3_i262 + 1) {
        c3_i_y[c3_i259 + c3_i258] = c3_i_y[c3_i259 + c3_i258] + c3_nb_A[c3_i261
          + c3_i258] * c3_nb_B[c3_i262 + c3_i259];
        c3_i261 = c3_i261 + 4;
      }

      c3_i259 = c3_i259 + 4;
    }
  }

  for (c3_i263 = 0; c3_i263 < 16; c3_i263 = c3_i263 + 1) {
    c3_n_a[c3_i263] = c3_i_y[c3_i263];
  }

  for (c3_i264 = 0; c3_i264 < 6; c3_i264 = c3_i264 + 1) {
    c3_dv33[c3_i264] = c3_dv15[c3_i264];
  }

  c3_expg(chartInstance, c3_dv33, c3_DH[19], c3_n_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i265 = 0; c3_i265 < 16; c3_i265 = c3_i265 + 1) {
    c3_ob_A[c3_i265] = c3_n_a[c3_i265];
  }

  for (c3_i266 = 0; c3_i266 < 16; c3_i266 = c3_i266 + 1) {
    c3_ob_B[c3_i266] = c3_n_b[c3_i266];
  }

  for (c3_i267 = 0; c3_i267 < 16; c3_i267 = c3_i267 + 1) {
    c3_pb_A[c3_i267] = c3_ob_A[c3_i267];
  }

  for (c3_i268 = 0; c3_i268 < 16; c3_i268 = c3_i268 + 1) {
    c3_pb_B[c3_i268] = c3_ob_B[c3_i268];
  }

  for (c3_i269 = 0; c3_i269 < 16; c3_i269 = c3_i269 + 1) {
    c3_qb_A[c3_i269] = c3_pb_A[c3_i269];
  }

  for (c3_i270 = 0; c3_i270 < 16; c3_i270 = c3_i270 + 1) {
    c3_qb_B[c3_i270] = c3_pb_B[c3_i270];
  }

  for (c3_i271 = 0; c3_i271 < 4; c3_i271 = c3_i271 + 1) {
    c3_i272 = 0;
    for (c3_i273 = 0; c3_i273 < 4; c3_i273 = c3_i273 + 1) {
      c3_j_y[c3_i272 + c3_i271] = 0.0;
      c3_i274 = 0;
      for (c3_i275 = 0; c3_i275 < 4; c3_i275 = c3_i275 + 1) {
        c3_j_y[c3_i272 + c3_i271] = c3_j_y[c3_i272 + c3_i271] + c3_qb_A[c3_i274
          + c3_i271] * c3_qb_B[c3_i275 + c3_i272];
        c3_i274 = c3_i274 + 4;
      }

      c3_i272 = c3_i272 + 4;
    }
  }

  for (c3_i276 = 0; c3_i276 < 16; c3_i276 = c3_i276 + 1) {
    c3_o_a[c3_i276] = c3_j_y[c3_i276];
  }

  for (c3_i277 = 0; c3_i277 < 6; c3_i277 = c3_i277 + 1) {
    c3_dv34[c3_i277] = c3_dv17[c3_i277];
  }

  c3_expg(chartInstance, c3_dv34, c3_DH[18], c3_o_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i278 = 0; c3_i278 < 16; c3_i278 = c3_i278 + 1) {
    c3_rb_A[c3_i278] = c3_o_a[c3_i278];
  }

  for (c3_i279 = 0; c3_i279 < 16; c3_i279 = c3_i279 + 1) {
    c3_rb_B[c3_i279] = c3_o_b[c3_i279];
  }

  for (c3_i280 = 0; c3_i280 < 16; c3_i280 = c3_i280 + 1) {
    c3_g45_0[c3_i280] = 0.0;
  }

  for (c3_i281 = 0; c3_i281 < 16; c3_i281 = c3_i281 + 1) {
    c3_sb_A[c3_i281] = c3_rb_A[c3_i281];
  }

  for (c3_i282 = 0; c3_i282 < 16; c3_i282 = c3_i282 + 1) {
    c3_sb_B[c3_i282] = c3_rb_B[c3_i282];
  }

  for (c3_i283 = 0; c3_i283 < 16; c3_i283 = c3_i283 + 1) {
    c3_tb_A[c3_i283] = c3_sb_A[c3_i283];
  }

  for (c3_i284 = 0; c3_i284 < 16; c3_i284 = c3_i284 + 1) {
    c3_tb_B[c3_i284] = c3_sb_B[c3_i284];
  }

  for (c3_i285 = 0; c3_i285 < 4; c3_i285 = c3_i285 + 1) {
    c3_i286 = 0;
    for (c3_i287 = 0; c3_i287 < 4; c3_i287 = c3_i287 + 1) {
      c3_g45_0[c3_i286 + c3_i285] = 0.0;
      c3_i288 = 0;
      for (c3_i289 = 0; c3_i289 < 4; c3_i289 = c3_i289 + 1) {
        c3_g45_0[c3_i286 + c3_i285] = c3_g45_0[c3_i286 + c3_i285] +
          c3_tb_A[c3_i288 + c3_i285] * c3_tb_B[c3_i289 + c3_i286];
        c3_i288 = c3_i288 + 4;
      }

      c3_i286 = c3_i286 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 62);
  for (c3_i290 = 0; c3_i290 < 6; c3_i290 = c3_i290 + 1) {
    c3_dv35[c3_i290] = c3_dv10[c3_i290];
  }

  c3_expg(chartInstance, c3_dv35, c3_DH[21], c3_p_a);
  for (c3_i291 = 0; c3_i291 < 6; c3_i291 = c3_i291 + 1) {
    c3_dv36[c3_i291] = c3_dv13[c3_i291];
  }

  c3_expg(chartInstance, c3_dv36, c3_DH[20], c3_p_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i292 = 0; c3_i292 < 16; c3_i292 = c3_i292 + 1) {
    c3_ub_A[c3_i292] = c3_p_a[c3_i292];
  }

  for (c3_i293 = 0; c3_i293 < 16; c3_i293 = c3_i293 + 1) {
    c3_ub_B[c3_i293] = c3_p_b[c3_i293];
  }

  for (c3_i294 = 0; c3_i294 < 16; c3_i294 = c3_i294 + 1) {
    c3_vb_A[c3_i294] = c3_ub_A[c3_i294];
  }

  for (c3_i295 = 0; c3_i295 < 16; c3_i295 = c3_i295 + 1) {
    c3_vb_B[c3_i295] = c3_ub_B[c3_i295];
  }

  for (c3_i296 = 0; c3_i296 < 16; c3_i296 = c3_i296 + 1) {
    c3_wb_A[c3_i296] = c3_vb_A[c3_i296];
  }

  for (c3_i297 = 0; c3_i297 < 16; c3_i297 = c3_i297 + 1) {
    c3_wb_B[c3_i297] = c3_vb_B[c3_i297];
  }

  for (c3_i298 = 0; c3_i298 < 4; c3_i298 = c3_i298 + 1) {
    c3_i299 = 0;
    for (c3_i300 = 0; c3_i300 < 4; c3_i300 = c3_i300 + 1) {
      c3_k_y[c3_i299 + c3_i298] = 0.0;
      c3_i301 = 0;
      for (c3_i302 = 0; c3_i302 < 4; c3_i302 = c3_i302 + 1) {
        c3_k_y[c3_i299 + c3_i298] = c3_k_y[c3_i299 + c3_i298] + c3_wb_A[c3_i301
          + c3_i298] * c3_wb_B[c3_i302 + c3_i299];
        c3_i301 = c3_i301 + 4;
      }

      c3_i299 = c3_i299 + 4;
    }
  }

  for (c3_i303 = 0; c3_i303 < 16; c3_i303 = c3_i303 + 1) {
    c3_q_a[c3_i303] = c3_k_y[c3_i303];
  }

  for (c3_i304 = 0; c3_i304 < 6; c3_i304 = c3_i304 + 1) {
    c3_dv37[c3_i304] = c3_dv15[c3_i304];
  }

  c3_expg(chartInstance, c3_dv37, c3_DH[23], c3_q_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i305 = 0; c3_i305 < 16; c3_i305 = c3_i305 + 1) {
    c3_xb_A[c3_i305] = c3_q_a[c3_i305];
  }

  for (c3_i306 = 0; c3_i306 < 16; c3_i306 = c3_i306 + 1) {
    c3_xb_B[c3_i306] = c3_q_b[c3_i306];
  }

  for (c3_i307 = 0; c3_i307 < 16; c3_i307 = c3_i307 + 1) {
    c3_yb_A[c3_i307] = c3_xb_A[c3_i307];
  }

  for (c3_i308 = 0; c3_i308 < 16; c3_i308 = c3_i308 + 1) {
    c3_yb_B[c3_i308] = c3_xb_B[c3_i308];
  }

  for (c3_i309 = 0; c3_i309 < 16; c3_i309 = c3_i309 + 1) {
    c3_ac_A[c3_i309] = c3_yb_A[c3_i309];
  }

  for (c3_i310 = 0; c3_i310 < 16; c3_i310 = c3_i310 + 1) {
    c3_ac_B[c3_i310] = c3_yb_B[c3_i310];
  }

  for (c3_i311 = 0; c3_i311 < 4; c3_i311 = c3_i311 + 1) {
    c3_i312 = 0;
    for (c3_i313 = 0; c3_i313 < 4; c3_i313 = c3_i313 + 1) {
      c3_l_y[c3_i312 + c3_i311] = 0.0;
      c3_i314 = 0;
      for (c3_i315 = 0; c3_i315 < 4; c3_i315 = c3_i315 + 1) {
        c3_l_y[c3_i312 + c3_i311] = c3_l_y[c3_i312 + c3_i311] + c3_ac_A[c3_i314
          + c3_i311] * c3_ac_B[c3_i315 + c3_i312];
        c3_i314 = c3_i314 + 4;
      }

      c3_i312 = c3_i312 + 4;
    }
  }

  for (c3_i316 = 0; c3_i316 < 16; c3_i316 = c3_i316 + 1) {
    c3_r_a[c3_i316] = c3_l_y[c3_i316];
  }

  for (c3_i317 = 0; c3_i317 < 6; c3_i317 = c3_i317 + 1) {
    c3_dv38[c3_i317] = c3_dv17[c3_i317];
  }

  c3_expg(chartInstance, c3_dv38, c3_DH[22], c3_r_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i318 = 0; c3_i318 < 16; c3_i318 = c3_i318 + 1) {
    c3_bc_A[c3_i318] = c3_r_a[c3_i318];
  }

  for (c3_i319 = 0; c3_i319 < 16; c3_i319 = c3_i319 + 1) {
    c3_bc_B[c3_i319] = c3_r_b[c3_i319];
  }

  for (c3_i320 = 0; c3_i320 < 16; c3_i320 = c3_i320 + 1) {
    c3_g56_0[c3_i320] = 0.0;
  }

  for (c3_i321 = 0; c3_i321 < 16; c3_i321 = c3_i321 + 1) {
    c3_cc_A[c3_i321] = c3_bc_A[c3_i321];
  }

  for (c3_i322 = 0; c3_i322 < 16; c3_i322 = c3_i322 + 1) {
    c3_cc_B[c3_i322] = c3_bc_B[c3_i322];
  }

  for (c3_i323 = 0; c3_i323 < 16; c3_i323 = c3_i323 + 1) {
    c3_dc_A[c3_i323] = c3_cc_A[c3_i323];
  }

  for (c3_i324 = 0; c3_i324 < 16; c3_i324 = c3_i324 + 1) {
    c3_dc_B[c3_i324] = c3_cc_B[c3_i324];
  }

  for (c3_i325 = 0; c3_i325 < 4; c3_i325 = c3_i325 + 1) {
    c3_i326 = 0;
    for (c3_i327 = 0; c3_i327 < 4; c3_i327 = c3_i327 + 1) {
      c3_g56_0[c3_i326 + c3_i325] = 0.0;
      c3_i328 = 0;
      for (c3_i329 = 0; c3_i329 < 4; c3_i329 = c3_i329 + 1) {
        c3_g56_0[c3_i326 + c3_i325] = c3_g56_0[c3_i326 + c3_i325] +
          c3_dc_A[c3_i328 + c3_i325] * c3_dc_B[c3_i329 + c3_i326];
        c3_i328 = c3_i328 + 4;
      }

      c3_i326 = c3_i326 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 63);
  for (c3_i330 = 0; c3_i330 < 6; c3_i330 = c3_i330 + 1) {
    c3_dv39[c3_i330] = c3_dv10[c3_i330];
  }

  c3_expg(chartInstance, c3_dv39, c3_DH[25], c3_s_a);
  for (c3_i331 = 0; c3_i331 < 6; c3_i331 = c3_i331 + 1) {
    c3_dv40[c3_i331] = c3_dv13[c3_i331];
  }

  c3_expg(chartInstance, c3_dv40, c3_DH[24], c3_s_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i332 = 0; c3_i332 < 16; c3_i332 = c3_i332 + 1) {
    c3_ec_A[c3_i332] = c3_s_a[c3_i332];
  }

  for (c3_i333 = 0; c3_i333 < 16; c3_i333 = c3_i333 + 1) {
    c3_ec_B[c3_i333] = c3_s_b[c3_i333];
  }

  for (c3_i334 = 0; c3_i334 < 16; c3_i334 = c3_i334 + 1) {
    c3_fc_A[c3_i334] = c3_ec_A[c3_i334];
  }

  for (c3_i335 = 0; c3_i335 < 16; c3_i335 = c3_i335 + 1) {
    c3_fc_B[c3_i335] = c3_ec_B[c3_i335];
  }

  for (c3_i336 = 0; c3_i336 < 16; c3_i336 = c3_i336 + 1) {
    c3_gc_A[c3_i336] = c3_fc_A[c3_i336];
  }

  for (c3_i337 = 0; c3_i337 < 16; c3_i337 = c3_i337 + 1) {
    c3_gc_B[c3_i337] = c3_fc_B[c3_i337];
  }

  for (c3_i338 = 0; c3_i338 < 4; c3_i338 = c3_i338 + 1) {
    c3_i339 = 0;
    for (c3_i340 = 0; c3_i340 < 4; c3_i340 = c3_i340 + 1) {
      c3_m_y[c3_i339 + c3_i338] = 0.0;
      c3_i341 = 0;
      for (c3_i342 = 0; c3_i342 < 4; c3_i342 = c3_i342 + 1) {
        c3_m_y[c3_i339 + c3_i338] = c3_m_y[c3_i339 + c3_i338] + c3_gc_A[c3_i341
          + c3_i338] * c3_gc_B[c3_i342 + c3_i339];
        c3_i341 = c3_i341 + 4;
      }

      c3_i339 = c3_i339 + 4;
    }
  }

  for (c3_i343 = 0; c3_i343 < 16; c3_i343 = c3_i343 + 1) {
    c3_t_a[c3_i343] = c3_m_y[c3_i343];
  }

  for (c3_i344 = 0; c3_i344 < 6; c3_i344 = c3_i344 + 1) {
    c3_dv41[c3_i344] = c3_dv15[c3_i344];
  }

  c3_expg(chartInstance, c3_dv41, c3_DH[27], c3_t_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i345 = 0; c3_i345 < 16; c3_i345 = c3_i345 + 1) {
    c3_hc_A[c3_i345] = c3_t_a[c3_i345];
  }

  for (c3_i346 = 0; c3_i346 < 16; c3_i346 = c3_i346 + 1) {
    c3_hc_B[c3_i346] = c3_t_b[c3_i346];
  }

  for (c3_i347 = 0; c3_i347 < 16; c3_i347 = c3_i347 + 1) {
    c3_ic_A[c3_i347] = c3_hc_A[c3_i347];
  }

  for (c3_i348 = 0; c3_i348 < 16; c3_i348 = c3_i348 + 1) {
    c3_ic_B[c3_i348] = c3_hc_B[c3_i348];
  }

  for (c3_i349 = 0; c3_i349 < 16; c3_i349 = c3_i349 + 1) {
    c3_jc_A[c3_i349] = c3_ic_A[c3_i349];
  }

  for (c3_i350 = 0; c3_i350 < 16; c3_i350 = c3_i350 + 1) {
    c3_jc_B[c3_i350] = c3_ic_B[c3_i350];
  }

  for (c3_i351 = 0; c3_i351 < 4; c3_i351 = c3_i351 + 1) {
    c3_i352 = 0;
    for (c3_i353 = 0; c3_i353 < 4; c3_i353 = c3_i353 + 1) {
      c3_n_y[c3_i352 + c3_i351] = 0.0;
      c3_i354 = 0;
      for (c3_i355 = 0; c3_i355 < 4; c3_i355 = c3_i355 + 1) {
        c3_n_y[c3_i352 + c3_i351] = c3_n_y[c3_i352 + c3_i351] + c3_jc_A[c3_i354
          + c3_i351] * c3_jc_B[c3_i355 + c3_i352];
        c3_i354 = c3_i354 + 4;
      }

      c3_i352 = c3_i352 + 4;
    }
  }

  for (c3_i356 = 0; c3_i356 < 16; c3_i356 = c3_i356 + 1) {
    c3_u_a[c3_i356] = c3_n_y[c3_i356];
  }

  for (c3_i357 = 0; c3_i357 < 6; c3_i357 = c3_i357 + 1) {
    c3_dv42[c3_i357] = c3_dv17[c3_i357];
  }

  c3_expg(chartInstance, c3_dv42, c3_DH[26], c3_u_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i358 = 0; c3_i358 < 16; c3_i358 = c3_i358 + 1) {
    c3_kc_A[c3_i358] = c3_u_a[c3_i358];
  }

  for (c3_i359 = 0; c3_i359 < 16; c3_i359 = c3_i359 + 1) {
    c3_kc_B[c3_i359] = c3_u_b[c3_i359];
  }

  for (c3_i360 = 0; c3_i360 < 16; c3_i360 = c3_i360 + 1) {
    c3_g67_0[c3_i360] = 0.0;
  }

  for (c3_i361 = 0; c3_i361 < 16; c3_i361 = c3_i361 + 1) {
    c3_lc_A[c3_i361] = c3_kc_A[c3_i361];
  }

  for (c3_i362 = 0; c3_i362 < 16; c3_i362 = c3_i362 + 1) {
    c3_lc_B[c3_i362] = c3_kc_B[c3_i362];
  }

  for (c3_i363 = 0; c3_i363 < 16; c3_i363 = c3_i363 + 1) {
    c3_mc_A[c3_i363] = c3_lc_A[c3_i363];
  }

  for (c3_i364 = 0; c3_i364 < 16; c3_i364 = c3_i364 + 1) {
    c3_mc_B[c3_i364] = c3_lc_B[c3_i364];
  }

  for (c3_i365 = 0; c3_i365 < 4; c3_i365 = c3_i365 + 1) {
    c3_i366 = 0;
    for (c3_i367 = 0; c3_i367 < 4; c3_i367 = c3_i367 + 1) {
      c3_g67_0[c3_i366 + c3_i365] = 0.0;
      c3_i368 = 0;
      for (c3_i369 = 0; c3_i369 < 4; c3_i369 = c3_i369 + 1) {
        c3_g67_0[c3_i366 + c3_i365] = c3_g67_0[c3_i366 + c3_i365] +
          c3_mc_A[c3_i368 + c3_i365] * c3_mc_B[c3_i369 + c3_i366];
        c3_i368 = c3_i368 + 4;
      }

      c3_i366 = c3_i366 + 4;
    }
  }

  /*  %% calculate ri: ith link mass center offset relative to ith joint frame,i=1,2,3,4,5,6 */
  _SFD_SCRIPT_CALL(0, 67);
  for (c3_i370 = 0; c3_i370 < 16; c3_i370 = c3_i370 + 1) {
    c3_g[c3_i370] = c3_g01_0[c3_i370];
  }

  _SFD_SCRIPT_CALL(0, 68);
  for (c3_i371 = 0; c3_i371 < 16; c3_i371 = c3_i371 + 1) {
    c3_b_g[c3_i371] = c3_g[c3_i371];
  }

  for (c3_i372 = 0; c3_i372 < 3; c3_i372 = c3_i372 + 1) {
    c3_b_Cen[c3_i372] = c3_Cen[c3_i372];
  }

  c3_b_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_b_g, c3_b_Cen, c3_dv43);
  for (c3_i373 = 0; c3_i373 < 4; c3_i373 = c3_i373 + 1) {
    c3_r1[c3_i373] = c3_dv43[c3_i373];
  }

  sf_debug_symbol_switch(19U, 19U);
  _SFD_SCRIPT_CALL(0, 69);
  for (c3_i374 = 0; c3_i374 < 3; c3_i374 = c3_i374 + 1) {
    c3_b_r1[c3_i374] = c3_r1[c3_i374];
  }

  sf_debug_symbol_switch(19U, 78U);
  _SFD_SCRIPT_CALL(0, 70);
  for (c3_i375 = 0; c3_i375 < 16; c3_i375 = c3_i375 + 1) {
    c3_v_a[c3_i375] = c3_g[c3_i375];
  }

  for (c3_i376 = 0; c3_i376 < 16; c3_i376 = c3_i376 + 1) {
    c3_v_b[c3_i376] = c3_g12_0[c3_i376];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i377 = 0; c3_i377 < 16; c3_i377 = c3_i377 + 1) {
    c3_nc_A[c3_i377] = c3_v_a[c3_i377];
  }

  for (c3_i378 = 0; c3_i378 < 16; c3_i378 = c3_i378 + 1) {
    c3_nc_B[c3_i378] = c3_v_b[c3_i378];
  }

  for (c3_i379 = 0; c3_i379 < 16; c3_i379 = c3_i379 + 1) {
    c3_g[c3_i379] = 0.0;
  }

  for (c3_i380 = 0; c3_i380 < 16; c3_i380 = c3_i380 + 1) {
    c3_oc_A[c3_i380] = c3_nc_A[c3_i380];
  }

  for (c3_i381 = 0; c3_i381 < 16; c3_i381 = c3_i381 + 1) {
    c3_oc_B[c3_i381] = c3_nc_B[c3_i381];
  }

  for (c3_i382 = 0; c3_i382 < 16; c3_i382 = c3_i382 + 1) {
    c3_pc_A[c3_i382] = c3_oc_A[c3_i382];
  }

  for (c3_i383 = 0; c3_i383 < 16; c3_i383 = c3_i383 + 1) {
    c3_pc_B[c3_i383] = c3_oc_B[c3_i383];
  }

  for (c3_i384 = 0; c3_i384 < 4; c3_i384 = c3_i384 + 1) {
    c3_i385 = 0;
    for (c3_i386 = 0; c3_i386 < 4; c3_i386 = c3_i386 + 1) {
      c3_g[c3_i385 + c3_i384] = 0.0;
      c3_i387 = 0;
      for (c3_i388 = 0; c3_i388 < 4; c3_i388 = c3_i388 + 1) {
        c3_g[c3_i385 + c3_i384] = c3_g[c3_i385 + c3_i384] + c3_pc_A[c3_i387 +
          c3_i384] * c3_pc_B[c3_i388 + c3_i385];
        c3_i387 = c3_i387 + 4;
      }

      c3_i385 = c3_i385 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 71);
  for (c3_i389 = 0; c3_i389 < 16; c3_i389 = c3_i389 + 1) {
    c3_c_g[c3_i389] = c3_g[c3_i389];
  }

  for (c3_i390 = 0; c3_i390 < 3; c3_i390 = c3_i390 + 1) {
    c3_c_Cen[c3_i390] = c3_Cen[c3_i390 + 3];
  }

  c3_c_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_c_g, c3_c_Cen, c3_dv44);
  for (c3_i391 = 0; c3_i391 < 4; c3_i391 = c3_i391 + 1) {
    c3_r2[c3_i391] = c3_dv44[c3_i391];
  }

  sf_debug_symbol_switch(20U, 20U);
  _SFD_SCRIPT_CALL(0, 72);
  for (c3_i392 = 0; c3_i392 < 3; c3_i392 = c3_i392 + 1) {
    c3_b_r2[c3_i392] = c3_r2[c3_i392];
  }

  sf_debug_symbol_switch(20U, 79U);
  _SFD_SCRIPT_CALL(0, 73);
  for (c3_i393 = 0; c3_i393 < 16; c3_i393 = c3_i393 + 1) {
    c3_w_a[c3_i393] = c3_g[c3_i393];
  }

  for (c3_i394 = 0; c3_i394 < 16; c3_i394 = c3_i394 + 1) {
    c3_w_b[c3_i394] = c3_g23_0[c3_i394];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i395 = 0; c3_i395 < 16; c3_i395 = c3_i395 + 1) {
    c3_qc_A[c3_i395] = c3_w_a[c3_i395];
  }

  for (c3_i396 = 0; c3_i396 < 16; c3_i396 = c3_i396 + 1) {
    c3_qc_B[c3_i396] = c3_w_b[c3_i396];
  }

  for (c3_i397 = 0; c3_i397 < 16; c3_i397 = c3_i397 + 1) {
    c3_g[c3_i397] = 0.0;
  }

  for (c3_i398 = 0; c3_i398 < 16; c3_i398 = c3_i398 + 1) {
    c3_rc_A[c3_i398] = c3_qc_A[c3_i398];
  }

  for (c3_i399 = 0; c3_i399 < 16; c3_i399 = c3_i399 + 1) {
    c3_rc_B[c3_i399] = c3_qc_B[c3_i399];
  }

  for (c3_i400 = 0; c3_i400 < 16; c3_i400 = c3_i400 + 1) {
    c3_sc_A[c3_i400] = c3_rc_A[c3_i400];
  }

  for (c3_i401 = 0; c3_i401 < 16; c3_i401 = c3_i401 + 1) {
    c3_sc_B[c3_i401] = c3_rc_B[c3_i401];
  }

  for (c3_i402 = 0; c3_i402 < 4; c3_i402 = c3_i402 + 1) {
    c3_i403 = 0;
    for (c3_i404 = 0; c3_i404 < 4; c3_i404 = c3_i404 + 1) {
      c3_g[c3_i403 + c3_i402] = 0.0;
      c3_i405 = 0;
      for (c3_i406 = 0; c3_i406 < 4; c3_i406 = c3_i406 + 1) {
        c3_g[c3_i403 + c3_i402] = c3_g[c3_i403 + c3_i402] + c3_sc_A[c3_i405 +
          c3_i402] * c3_sc_B[c3_i406 + c3_i403];
        c3_i405 = c3_i405 + 4;
      }

      c3_i403 = c3_i403 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 74);
  for (c3_i407 = 0; c3_i407 < 16; c3_i407 = c3_i407 + 1) {
    c3_d_g[c3_i407] = c3_g[c3_i407];
  }

  for (c3_i408 = 0; c3_i408 < 3; c3_i408 = c3_i408 + 1) {
    c3_d_Cen[c3_i408] = c3_Cen[c3_i408 + 6];
  }

  c3_d_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_d_g, c3_d_Cen, c3_dv45);
  for (c3_i409 = 0; c3_i409 < 4; c3_i409 = c3_i409 + 1) {
    c3_r3[c3_i409] = c3_dv45[c3_i409];
  }

  sf_debug_symbol_switch(21U, 21U);
  _SFD_SCRIPT_CALL(0, 75);
  for (c3_i410 = 0; c3_i410 < 3; c3_i410 = c3_i410 + 1) {
    c3_b_r3[c3_i410] = c3_r3[c3_i410];
  }

  sf_debug_symbol_switch(21U, 80U);
  _SFD_SCRIPT_CALL(0, 76);
  for (c3_i411 = 0; c3_i411 < 16; c3_i411 = c3_i411 + 1) {
    c3_x_a[c3_i411] = c3_g[c3_i411];
  }

  for (c3_i412 = 0; c3_i412 < 16; c3_i412 = c3_i412 + 1) {
    c3_x_b[c3_i412] = c3_g34_0[c3_i412];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i413 = 0; c3_i413 < 16; c3_i413 = c3_i413 + 1) {
    c3_tc_A[c3_i413] = c3_x_a[c3_i413];
  }

  for (c3_i414 = 0; c3_i414 < 16; c3_i414 = c3_i414 + 1) {
    c3_tc_B[c3_i414] = c3_x_b[c3_i414];
  }

  for (c3_i415 = 0; c3_i415 < 16; c3_i415 = c3_i415 + 1) {
    c3_g[c3_i415] = 0.0;
  }

  for (c3_i416 = 0; c3_i416 < 16; c3_i416 = c3_i416 + 1) {
    c3_uc_A[c3_i416] = c3_tc_A[c3_i416];
  }

  for (c3_i417 = 0; c3_i417 < 16; c3_i417 = c3_i417 + 1) {
    c3_uc_B[c3_i417] = c3_tc_B[c3_i417];
  }

  for (c3_i418 = 0; c3_i418 < 16; c3_i418 = c3_i418 + 1) {
    c3_vc_A[c3_i418] = c3_uc_A[c3_i418];
  }

  for (c3_i419 = 0; c3_i419 < 16; c3_i419 = c3_i419 + 1) {
    c3_vc_B[c3_i419] = c3_uc_B[c3_i419];
  }

  for (c3_i420 = 0; c3_i420 < 4; c3_i420 = c3_i420 + 1) {
    c3_i421 = 0;
    for (c3_i422 = 0; c3_i422 < 4; c3_i422 = c3_i422 + 1) {
      c3_g[c3_i421 + c3_i420] = 0.0;
      c3_i423 = 0;
      for (c3_i424 = 0; c3_i424 < 4; c3_i424 = c3_i424 + 1) {
        c3_g[c3_i421 + c3_i420] = c3_g[c3_i421 + c3_i420] + c3_vc_A[c3_i423 +
          c3_i420] * c3_vc_B[c3_i424 + c3_i421];
        c3_i423 = c3_i423 + 4;
      }

      c3_i421 = c3_i421 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 77);
  for (c3_i425 = 0; c3_i425 < 16; c3_i425 = c3_i425 + 1) {
    c3_e_g[c3_i425] = c3_g[c3_i425];
  }

  for (c3_i426 = 0; c3_i426 < 3; c3_i426 = c3_i426 + 1) {
    c3_e_Cen[c3_i426] = c3_Cen[c3_i426 + 9];
  }

  c3_e_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_e_g, c3_e_Cen, c3_dv46);
  for (c3_i427 = 0; c3_i427 < 4; c3_i427 = c3_i427 + 1) {
    c3_r4[c3_i427] = c3_dv46[c3_i427];
  }

  sf_debug_symbol_switch(22U, 22U);
  _SFD_SCRIPT_CALL(0, 78);
  for (c3_i428 = 0; c3_i428 < 3; c3_i428 = c3_i428 + 1) {
    c3_b_r4[c3_i428] = c3_r4[c3_i428];
  }

  sf_debug_symbol_switch(22U, 81U);
  _SFD_SCRIPT_CALL(0, 79);
  for (c3_i429 = 0; c3_i429 < 16; c3_i429 = c3_i429 + 1) {
    c3_y_a[c3_i429] = c3_g[c3_i429];
  }

  for (c3_i430 = 0; c3_i430 < 16; c3_i430 = c3_i430 + 1) {
    c3_y_b[c3_i430] = c3_g45_0[c3_i430];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i431 = 0; c3_i431 < 16; c3_i431 = c3_i431 + 1) {
    c3_wc_A[c3_i431] = c3_y_a[c3_i431];
  }

  for (c3_i432 = 0; c3_i432 < 16; c3_i432 = c3_i432 + 1) {
    c3_wc_B[c3_i432] = c3_y_b[c3_i432];
  }

  for (c3_i433 = 0; c3_i433 < 16; c3_i433 = c3_i433 + 1) {
    c3_g[c3_i433] = 0.0;
  }

  for (c3_i434 = 0; c3_i434 < 16; c3_i434 = c3_i434 + 1) {
    c3_xc_A[c3_i434] = c3_wc_A[c3_i434];
  }

  for (c3_i435 = 0; c3_i435 < 16; c3_i435 = c3_i435 + 1) {
    c3_xc_B[c3_i435] = c3_wc_B[c3_i435];
  }

  for (c3_i436 = 0; c3_i436 < 16; c3_i436 = c3_i436 + 1) {
    c3_yc_A[c3_i436] = c3_xc_A[c3_i436];
  }

  for (c3_i437 = 0; c3_i437 < 16; c3_i437 = c3_i437 + 1) {
    c3_yc_B[c3_i437] = c3_xc_B[c3_i437];
  }

  for (c3_i438 = 0; c3_i438 < 4; c3_i438 = c3_i438 + 1) {
    c3_i439 = 0;
    for (c3_i440 = 0; c3_i440 < 4; c3_i440 = c3_i440 + 1) {
      c3_g[c3_i439 + c3_i438] = 0.0;
      c3_i441 = 0;
      for (c3_i442 = 0; c3_i442 < 4; c3_i442 = c3_i442 + 1) {
        c3_g[c3_i439 + c3_i438] = c3_g[c3_i439 + c3_i438] + c3_yc_A[c3_i441 +
          c3_i438] * c3_yc_B[c3_i442 + c3_i439];
        c3_i441 = c3_i441 + 4;
      }

      c3_i439 = c3_i439 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 80);
  for (c3_i443 = 0; c3_i443 < 16; c3_i443 = c3_i443 + 1) {
    c3_f_g[c3_i443] = c3_g[c3_i443];
  }

  for (c3_i444 = 0; c3_i444 < 3; c3_i444 = c3_i444 + 1) {
    c3_f_Cen[c3_i444] = c3_Cen[c3_i444 + 12];
  }

  c3_f_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_f_g, c3_f_Cen, c3_dv47);
  for (c3_i445 = 0; c3_i445 < 4; c3_i445 = c3_i445 + 1) {
    c3_r5[c3_i445] = c3_dv47[c3_i445];
  }

  sf_debug_symbol_switch(23U, 23U);
  _SFD_SCRIPT_CALL(0, 81);
  for (c3_i446 = 0; c3_i446 < 3; c3_i446 = c3_i446 + 1) {
    c3_b_r5[c3_i446] = c3_r5[c3_i446];
  }

  sf_debug_symbol_switch(23U, 82U);
  _SFD_SCRIPT_CALL(0, 82);
  for (c3_i447 = 0; c3_i447 < 16; c3_i447 = c3_i447 + 1) {
    c3_ab_a[c3_i447] = c3_g[c3_i447];
  }

  for (c3_i448 = 0; c3_i448 < 16; c3_i448 = c3_i448 + 1) {
    c3_ab_b[c3_i448] = c3_g56_0[c3_i448];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i449 = 0; c3_i449 < 16; c3_i449 = c3_i449 + 1) {
    c3_ad_A[c3_i449] = c3_ab_a[c3_i449];
  }

  for (c3_i450 = 0; c3_i450 < 16; c3_i450 = c3_i450 + 1) {
    c3_ad_B[c3_i450] = c3_ab_b[c3_i450];
  }

  for (c3_i451 = 0; c3_i451 < 16; c3_i451 = c3_i451 + 1) {
    c3_g[c3_i451] = 0.0;
  }

  for (c3_i452 = 0; c3_i452 < 16; c3_i452 = c3_i452 + 1) {
    c3_bd_A[c3_i452] = c3_ad_A[c3_i452];
  }

  for (c3_i453 = 0; c3_i453 < 16; c3_i453 = c3_i453 + 1) {
    c3_bd_B[c3_i453] = c3_ad_B[c3_i453];
  }

  for (c3_i454 = 0; c3_i454 < 16; c3_i454 = c3_i454 + 1) {
    c3_cd_A[c3_i454] = c3_bd_A[c3_i454];
  }

  for (c3_i455 = 0; c3_i455 < 16; c3_i455 = c3_i455 + 1) {
    c3_cd_B[c3_i455] = c3_bd_B[c3_i455];
  }

  for (c3_i456 = 0; c3_i456 < 4; c3_i456 = c3_i456 + 1) {
    c3_i457 = 0;
    for (c3_i458 = 0; c3_i458 < 4; c3_i458 = c3_i458 + 1) {
      c3_g[c3_i457 + c3_i456] = 0.0;
      c3_i459 = 0;
      for (c3_i460 = 0; c3_i460 < 4; c3_i460 = c3_i460 + 1) {
        c3_g[c3_i457 + c3_i456] = c3_g[c3_i457 + c3_i456] + c3_cd_A[c3_i459 +
          c3_i456] * c3_cd_B[c3_i460 + c3_i457];
        c3_i459 = c3_i459 + 4;
      }

      c3_i457 = c3_i457 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 83);
  for (c3_i461 = 0; c3_i461 < 16; c3_i461 = c3_i461 + 1) {
    c3_g_g[c3_i461] = c3_g[c3_i461];
  }

  for (c3_i462 = 0; c3_i462 < 3; c3_i462 = c3_i462 + 1) {
    c3_g_Cen[c3_i462] = c3_Cen[c3_i462 + 15];
  }

  c3_g_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_g_g, c3_g_Cen, c3_dv48);
  for (c3_i463 = 0; c3_i463 < 4; c3_i463 = c3_i463 + 1) {
    c3_r6[c3_i463] = c3_dv48[c3_i463];
  }

  sf_debug_symbol_switch(24U, 24U);
  _SFD_SCRIPT_CALL(0, 84);
  for (c3_i464 = 0; c3_i464 < 3; c3_i464 = c3_i464 + 1) {
    c3_b_r6[c3_i464] = c3_r6[c3_i464];
  }

  sf_debug_symbol_switch(24U, 83U);

  /*  %% calculate momentt of inertia in Ci,i=1,2,3,4,5,6 */
  _SFD_SCRIPT_CALL(0, 87);
  c3_m1 = c3_Ma[0];
  _SFD_SCRIPT_CALL(0, 88);
  for (c3_i465 = 0; c3_i465 < 9; c3_i465 = c3_i465 + 1) {
    c3_x[c3_i465] = c3_Ie[c3_i465];
  }

  for (c3_k = 1; c3_k < 10; c3_k = c3_k + 1) {
    c3_b_k = c3_k;
    c3_I1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_b_k), 1, 9, 1, 0) - 1] = c3_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_b_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 89);
  c3_bb_a = c3_m1;
  for (c3_i466 = 0; c3_i466 < 9; c3_i466 = c3_i466 + 1) {
    c3_o_y[c3_i466] = c3_bb_a * c3_dv49[c3_i466];
  }

  c3_cb_a = -c3_m1;
  for (c3_i467 = 0; c3_i467 < 3; c3_i467 = c3_i467 + 1) {
    c3_c_r1[c3_i467] = c3_b_r1[c3_i467];
  }

  c3_hat(chartInstance, c3_c_r1, c3_bb_b);
  for (c3_i468 = 0; c3_i468 < 9; c3_i468 = c3_i468 + 1) {
    c3_p_y[c3_i468] = c3_cb_a * c3_bb_b[c3_i468];
  }

  c3_db_a = c3_m1;
  for (c3_i469 = 0; c3_i469 < 3; c3_i469 = c3_i469 + 1) {
    c3_d_r1[c3_i469] = c3_b_r1[c3_i469];
  }

  c3_hat(chartInstance, c3_d_r1, c3_cb_b);
  for (c3_i470 = 0; c3_i470 < 9; c3_i470 = c3_i470 + 1) {
    c3_q_y[c3_i470] = c3_db_a * c3_cb_b[c3_i470];
  }

  c3_eb_a = c3_m1;
  for (c3_i471 = 0; c3_i471 < 3; c3_i471 = c3_i471 + 1) {
    c3_e_r1[c3_i471] = c3_b_r1[c3_i471];
  }

  c3_hat(chartInstance, c3_e_r1, c3_db_b);
  for (c3_i472 = 0; c3_i472 < 9; c3_i472 = c3_i472 + 1) {
    c3_r_y[c3_i472] = c3_eb_a * c3_db_b[c3_i472];
  }

  for (c3_i473 = 0; c3_i473 < 9; c3_i473 = c3_i473 + 1) {
    c3_fb_a[c3_i473] = c3_r_y[c3_i473];
  }

  for (c3_i474 = 0; c3_i474 < 3; c3_i474 = c3_i474 + 1) {
    c3_f_r1[c3_i474] = c3_b_r1[c3_i474];
  }

  c3_hat(chartInstance, c3_f_r1, c3_eb_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i475 = 0; c3_i475 < 9; c3_i475 = c3_i475 + 1) {
    c3_dd_A[c3_i475] = c3_fb_a[c3_i475];
  }

  for (c3_i476 = 0; c3_i476 < 9; c3_i476 = c3_i476 + 1) {
    c3_dd_B[c3_i476] = c3_eb_b[c3_i476];
  }

  for (c3_i477 = 0; c3_i477 < 9; c3_i477 = c3_i477 + 1) {
    c3_ed_A[c3_i477] = c3_dd_A[c3_i477];
  }

  for (c3_i478 = 0; c3_i478 < 9; c3_i478 = c3_i478 + 1) {
    c3_ed_B[c3_i478] = c3_dd_B[c3_i478];
  }

  for (c3_i479 = 0; c3_i479 < 9; c3_i479 = c3_i479 + 1) {
    c3_fd_A[c3_i479] = c3_ed_A[c3_i479];
  }

  for (c3_i480 = 0; c3_i480 < 9; c3_i480 = c3_i480 + 1) {
    c3_fd_B[c3_i480] = c3_ed_B[c3_i480];
  }

  for (c3_i481 = 0; c3_i481 < 3; c3_i481 = c3_i481 + 1) {
    c3_i482 = 0;
    for (c3_i483 = 0; c3_i483 < 3; c3_i483 = c3_i483 + 1) {
      c3_s_y[c3_i482 + c3_i481] = 0.0;
      c3_i484 = 0;
      for (c3_i485 = 0; c3_i485 < 3; c3_i485 = c3_i485 + 1) {
        c3_s_y[c3_i482 + c3_i481] = c3_s_y[c3_i482 + c3_i481] + c3_fd_A[c3_i484
          + c3_i481] * c3_fd_B[c3_i485 + c3_i482];
        c3_i484 = c3_i484 + 3;
      }

      c3_i482 = c3_i482 + 3;
    }
  }

  c3_i486 = 0;
  c3_i487 = 0;
  for (c3_i488 = 0; c3_i488 < 3; c3_i488 = c3_i488 + 1) {
    for (c3_i489 = 0; c3_i489 < 3; c3_i489 = c3_i489 + 1) {
      c3_M1[c3_i489 + c3_i486] = c3_o_y[c3_i489 + c3_i487];
    }

    c3_i486 = c3_i486 + 6;
    c3_i487 = c3_i487 + 3;
  }

  c3_i490 = 0;
  c3_i491 = 0;
  for (c3_i492 = 0; c3_i492 < 3; c3_i492 = c3_i492 + 1) {
    for (c3_i493 = 0; c3_i493 < 3; c3_i493 = c3_i493 + 1) {
      c3_M1[(c3_i493 + c3_i490) + 18] = c3_p_y[c3_i493 + c3_i491];
    }

    c3_i490 = c3_i490 + 6;
    c3_i491 = c3_i491 + 3;
  }

  c3_i494 = 0;
  c3_i495 = 0;
  for (c3_i496 = 0; c3_i496 < 3; c3_i496 = c3_i496 + 1) {
    for (c3_i497 = 0; c3_i497 < 3; c3_i497 = c3_i497 + 1) {
      c3_M1[(c3_i497 + c3_i494) + 3] = c3_q_y[c3_i497 + c3_i495];
    }

    c3_i494 = c3_i494 + 6;
    c3_i495 = c3_i495 + 3;
  }

  c3_i498 = 0;
  c3_i499 = 0;
  for (c3_i500 = 0; c3_i500 < 3; c3_i500 = c3_i500 + 1) {
    for (c3_i501 = 0; c3_i501 < 3; c3_i501 = c3_i501 + 1) {
      c3_M1[(c3_i501 + c3_i498) + 21] = c3_I1[c3_i501 + c3_i499] -
        c3_s_y[c3_i501 + c3_i499];
    }

    c3_i498 = c3_i498 + 6;
    c3_i499 = c3_i499 + 3;
  }

  _SFD_SCRIPT_CALL(0, 92);
  c3_m2 = c3_Ma[1];
  _SFD_SCRIPT_CALL(0, 93);
  for (c3_i502 = 0; c3_i502 < 9; c3_i502 = c3_i502 + 1) {
    c3_b_x[c3_i502] = c3_Ie[c3_i502 + 9];
  }

  for (c3_c_k = 1; c3_c_k < 10; c3_c_k = c3_c_k + 1) {
    c3_d_k = c3_c_k;
    c3_I2[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_d_k), 1, 9, 1, 0) - 1] = c3_b_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_d_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 94);
  c3_gb_a = c3_m2;
  for (c3_i503 = 0; c3_i503 < 9; c3_i503 = c3_i503 + 1) {
    c3_t_y[c3_i503] = c3_gb_a * c3_dv49[c3_i503];
  }

  c3_hb_a = -c3_m2;
  for (c3_i504 = 0; c3_i504 < 3; c3_i504 = c3_i504 + 1) {
    c3_c_r2[c3_i504] = c3_b_r2[c3_i504];
  }

  c3_hat(chartInstance, c3_c_r2, c3_fb_b);
  for (c3_i505 = 0; c3_i505 < 9; c3_i505 = c3_i505 + 1) {
    c3_u_y[c3_i505] = c3_hb_a * c3_fb_b[c3_i505];
  }

  c3_ib_a = c3_m2;
  for (c3_i506 = 0; c3_i506 < 3; c3_i506 = c3_i506 + 1) {
    c3_d_r2[c3_i506] = c3_b_r2[c3_i506];
  }

  c3_hat(chartInstance, c3_d_r2, c3_gb_b);
  for (c3_i507 = 0; c3_i507 < 9; c3_i507 = c3_i507 + 1) {
    c3_v_y[c3_i507] = c3_ib_a * c3_gb_b[c3_i507];
  }

  c3_jb_a = c3_m2;
  for (c3_i508 = 0; c3_i508 < 3; c3_i508 = c3_i508 + 1) {
    c3_e_r2[c3_i508] = c3_b_r2[c3_i508];
  }

  c3_hat(chartInstance, c3_e_r2, c3_hb_b);
  for (c3_i509 = 0; c3_i509 < 9; c3_i509 = c3_i509 + 1) {
    c3_w_y[c3_i509] = c3_jb_a * c3_hb_b[c3_i509];
  }

  for (c3_i510 = 0; c3_i510 < 9; c3_i510 = c3_i510 + 1) {
    c3_kb_a[c3_i510] = c3_w_y[c3_i510];
  }

  for (c3_i511 = 0; c3_i511 < 3; c3_i511 = c3_i511 + 1) {
    c3_f_r2[c3_i511] = c3_b_r2[c3_i511];
  }

  c3_hat(chartInstance, c3_f_r2, c3_ib_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i512 = 0; c3_i512 < 9; c3_i512 = c3_i512 + 1) {
    c3_gd_A[c3_i512] = c3_kb_a[c3_i512];
  }

  for (c3_i513 = 0; c3_i513 < 9; c3_i513 = c3_i513 + 1) {
    c3_gd_B[c3_i513] = c3_ib_b[c3_i513];
  }

  for (c3_i514 = 0; c3_i514 < 9; c3_i514 = c3_i514 + 1) {
    c3_hd_A[c3_i514] = c3_gd_A[c3_i514];
  }

  for (c3_i515 = 0; c3_i515 < 9; c3_i515 = c3_i515 + 1) {
    c3_hd_B[c3_i515] = c3_gd_B[c3_i515];
  }

  for (c3_i516 = 0; c3_i516 < 9; c3_i516 = c3_i516 + 1) {
    c3_id_A[c3_i516] = c3_hd_A[c3_i516];
  }

  for (c3_i517 = 0; c3_i517 < 9; c3_i517 = c3_i517 + 1) {
    c3_id_B[c3_i517] = c3_hd_B[c3_i517];
  }

  for (c3_i518 = 0; c3_i518 < 3; c3_i518 = c3_i518 + 1) {
    c3_i519 = 0;
    for (c3_i520 = 0; c3_i520 < 3; c3_i520 = c3_i520 + 1) {
      c3_x_y[c3_i519 + c3_i518] = 0.0;
      c3_i521 = 0;
      for (c3_i522 = 0; c3_i522 < 3; c3_i522 = c3_i522 + 1) {
        c3_x_y[c3_i519 + c3_i518] = c3_x_y[c3_i519 + c3_i518] + c3_id_A[c3_i521
          + c3_i518] * c3_id_B[c3_i522 + c3_i519];
        c3_i521 = c3_i521 + 3;
      }

      c3_i519 = c3_i519 + 3;
    }
  }

  c3_i523 = 0;
  c3_i524 = 0;
  for (c3_i525 = 0; c3_i525 < 3; c3_i525 = c3_i525 + 1) {
    for (c3_i526 = 0; c3_i526 < 3; c3_i526 = c3_i526 + 1) {
      c3_M2[c3_i526 + c3_i523] = c3_t_y[c3_i526 + c3_i524];
    }

    c3_i523 = c3_i523 + 6;
    c3_i524 = c3_i524 + 3;
  }

  c3_i527 = 0;
  c3_i528 = 0;
  for (c3_i529 = 0; c3_i529 < 3; c3_i529 = c3_i529 + 1) {
    for (c3_i530 = 0; c3_i530 < 3; c3_i530 = c3_i530 + 1) {
      c3_M2[(c3_i530 + c3_i527) + 18] = c3_u_y[c3_i530 + c3_i528];
    }

    c3_i527 = c3_i527 + 6;
    c3_i528 = c3_i528 + 3;
  }

  c3_i531 = 0;
  c3_i532 = 0;
  for (c3_i533 = 0; c3_i533 < 3; c3_i533 = c3_i533 + 1) {
    for (c3_i534 = 0; c3_i534 < 3; c3_i534 = c3_i534 + 1) {
      c3_M2[(c3_i534 + c3_i531) + 3] = c3_v_y[c3_i534 + c3_i532];
    }

    c3_i531 = c3_i531 + 6;
    c3_i532 = c3_i532 + 3;
  }

  c3_i535 = 0;
  c3_i536 = 0;
  for (c3_i537 = 0; c3_i537 < 3; c3_i537 = c3_i537 + 1) {
    for (c3_i538 = 0; c3_i538 < 3; c3_i538 = c3_i538 + 1) {
      c3_M2[(c3_i538 + c3_i535) + 21] = c3_I2[c3_i538 + c3_i536] -
        c3_x_y[c3_i538 + c3_i536];
    }

    c3_i535 = c3_i535 + 6;
    c3_i536 = c3_i536 + 3;
  }

  _SFD_SCRIPT_CALL(0, 97);
  c3_m3 = c3_Ma[2];
  _SFD_SCRIPT_CALL(0, 98);
  for (c3_i539 = 0; c3_i539 < 9; c3_i539 = c3_i539 + 1) {
    c3_c_x[c3_i539] = c3_Ie[c3_i539 + 18];
  }

  for (c3_e_k = 1; c3_e_k < 10; c3_e_k = c3_e_k + 1) {
    c3_f_k = c3_e_k;
    c3_I3[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_f_k), 1, 9, 1, 0) - 1] = c3_c_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_f_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 99);
  c3_lb_a = c3_m3;
  for (c3_i540 = 0; c3_i540 < 9; c3_i540 = c3_i540 + 1) {
    c3_y_y[c3_i540] = c3_lb_a * c3_dv49[c3_i540];
  }

  c3_mb_a = -c3_m3;
  for (c3_i541 = 0; c3_i541 < 3; c3_i541 = c3_i541 + 1) {
    c3_c_r3[c3_i541] = c3_b_r3[c3_i541];
  }

  c3_hat(chartInstance, c3_c_r3, c3_jb_b);
  for (c3_i542 = 0; c3_i542 < 9; c3_i542 = c3_i542 + 1) {
    c3_ab_y[c3_i542] = c3_mb_a * c3_jb_b[c3_i542];
  }

  c3_nb_a = c3_m3;
  for (c3_i543 = 0; c3_i543 < 3; c3_i543 = c3_i543 + 1) {
    c3_d_r3[c3_i543] = c3_b_r3[c3_i543];
  }

  c3_hat(chartInstance, c3_d_r3, c3_kb_b);
  for (c3_i544 = 0; c3_i544 < 9; c3_i544 = c3_i544 + 1) {
    c3_bb_y[c3_i544] = c3_nb_a * c3_kb_b[c3_i544];
  }

  c3_ob_a = c3_m3;
  for (c3_i545 = 0; c3_i545 < 3; c3_i545 = c3_i545 + 1) {
    c3_e_r3[c3_i545] = c3_b_r3[c3_i545];
  }

  c3_hat(chartInstance, c3_e_r3, c3_lb_b);
  for (c3_i546 = 0; c3_i546 < 9; c3_i546 = c3_i546 + 1) {
    c3_cb_y[c3_i546] = c3_ob_a * c3_lb_b[c3_i546];
  }

  for (c3_i547 = 0; c3_i547 < 9; c3_i547 = c3_i547 + 1) {
    c3_pb_a[c3_i547] = c3_cb_y[c3_i547];
  }

  for (c3_i548 = 0; c3_i548 < 3; c3_i548 = c3_i548 + 1) {
    c3_f_r3[c3_i548] = c3_b_r3[c3_i548];
  }

  c3_hat(chartInstance, c3_f_r3, c3_mb_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i549 = 0; c3_i549 < 9; c3_i549 = c3_i549 + 1) {
    c3_jd_A[c3_i549] = c3_pb_a[c3_i549];
  }

  for (c3_i550 = 0; c3_i550 < 9; c3_i550 = c3_i550 + 1) {
    c3_jd_B[c3_i550] = c3_mb_b[c3_i550];
  }

  for (c3_i551 = 0; c3_i551 < 9; c3_i551 = c3_i551 + 1) {
    c3_kd_A[c3_i551] = c3_jd_A[c3_i551];
  }

  for (c3_i552 = 0; c3_i552 < 9; c3_i552 = c3_i552 + 1) {
    c3_kd_B[c3_i552] = c3_jd_B[c3_i552];
  }

  for (c3_i553 = 0; c3_i553 < 9; c3_i553 = c3_i553 + 1) {
    c3_ld_A[c3_i553] = c3_kd_A[c3_i553];
  }

  for (c3_i554 = 0; c3_i554 < 9; c3_i554 = c3_i554 + 1) {
    c3_ld_B[c3_i554] = c3_kd_B[c3_i554];
  }

  for (c3_i555 = 0; c3_i555 < 3; c3_i555 = c3_i555 + 1) {
    c3_i556 = 0;
    for (c3_i557 = 0; c3_i557 < 3; c3_i557 = c3_i557 + 1) {
      c3_db_y[c3_i556 + c3_i555] = 0.0;
      c3_i558 = 0;
      for (c3_i559 = 0; c3_i559 < 3; c3_i559 = c3_i559 + 1) {
        c3_db_y[c3_i556 + c3_i555] = c3_db_y[c3_i556 + c3_i555] +
          c3_ld_A[c3_i558 + c3_i555] * c3_ld_B[c3_i559 + c3_i556];
        c3_i558 = c3_i558 + 3;
      }

      c3_i556 = c3_i556 + 3;
    }
  }

  c3_i560 = 0;
  c3_i561 = 0;
  for (c3_i562 = 0; c3_i562 < 3; c3_i562 = c3_i562 + 1) {
    for (c3_i563 = 0; c3_i563 < 3; c3_i563 = c3_i563 + 1) {
      c3_M3[c3_i563 + c3_i560] = c3_y_y[c3_i563 + c3_i561];
    }

    c3_i560 = c3_i560 + 6;
    c3_i561 = c3_i561 + 3;
  }

  c3_i564 = 0;
  c3_i565 = 0;
  for (c3_i566 = 0; c3_i566 < 3; c3_i566 = c3_i566 + 1) {
    for (c3_i567 = 0; c3_i567 < 3; c3_i567 = c3_i567 + 1) {
      c3_M3[(c3_i567 + c3_i564) + 18] = c3_ab_y[c3_i567 + c3_i565];
    }

    c3_i564 = c3_i564 + 6;
    c3_i565 = c3_i565 + 3;
  }

  c3_i568 = 0;
  c3_i569 = 0;
  for (c3_i570 = 0; c3_i570 < 3; c3_i570 = c3_i570 + 1) {
    for (c3_i571 = 0; c3_i571 < 3; c3_i571 = c3_i571 + 1) {
      c3_M3[(c3_i571 + c3_i568) + 3] = c3_bb_y[c3_i571 + c3_i569];
    }

    c3_i568 = c3_i568 + 6;
    c3_i569 = c3_i569 + 3;
  }

  c3_i572 = 0;
  c3_i573 = 0;
  for (c3_i574 = 0; c3_i574 < 3; c3_i574 = c3_i574 + 1) {
    for (c3_i575 = 0; c3_i575 < 3; c3_i575 = c3_i575 + 1) {
      c3_M3[(c3_i575 + c3_i572) + 21] = c3_I3[c3_i575 + c3_i573] -
        c3_db_y[c3_i575 + c3_i573];
    }

    c3_i572 = c3_i572 + 6;
    c3_i573 = c3_i573 + 3;
  }

  _SFD_SCRIPT_CALL(0, 102);
  c3_m4 = c3_Ma[3];
  _SFD_SCRIPT_CALL(0, 103);
  for (c3_i576 = 0; c3_i576 < 9; c3_i576 = c3_i576 + 1) {
    c3_d_x[c3_i576] = c3_Ie[c3_i576 + 27];
  }

  for (c3_g_k = 1; c3_g_k < 10; c3_g_k = c3_g_k + 1) {
    c3_h_k = c3_g_k;
    c3_I4[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_h_k), 1, 9, 1, 0) - 1] = c3_d_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_h_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 104);
  c3_qb_a = c3_m4;
  for (c3_i577 = 0; c3_i577 < 9; c3_i577 = c3_i577 + 1) {
    c3_eb_y[c3_i577] = c3_qb_a * c3_dv49[c3_i577];
  }

  c3_rb_a = -c3_m4;
  for (c3_i578 = 0; c3_i578 < 3; c3_i578 = c3_i578 + 1) {
    c3_c_r4[c3_i578] = c3_b_r4[c3_i578];
  }

  c3_hat(chartInstance, c3_c_r4, c3_nb_b);
  for (c3_i579 = 0; c3_i579 < 9; c3_i579 = c3_i579 + 1) {
    c3_fb_y[c3_i579] = c3_rb_a * c3_nb_b[c3_i579];
  }

  c3_sb_a = c3_m4;
  for (c3_i580 = 0; c3_i580 < 3; c3_i580 = c3_i580 + 1) {
    c3_d_r4[c3_i580] = c3_b_r4[c3_i580];
  }

  c3_hat(chartInstance, c3_d_r4, c3_ob_b);
  for (c3_i581 = 0; c3_i581 < 9; c3_i581 = c3_i581 + 1) {
    c3_gb_y[c3_i581] = c3_sb_a * c3_ob_b[c3_i581];
  }

  c3_tb_a = c3_m4;
  for (c3_i582 = 0; c3_i582 < 3; c3_i582 = c3_i582 + 1) {
    c3_e_r4[c3_i582] = c3_b_r4[c3_i582];
  }

  c3_hat(chartInstance, c3_e_r4, c3_pb_b);
  for (c3_i583 = 0; c3_i583 < 9; c3_i583 = c3_i583 + 1) {
    c3_hb_y[c3_i583] = c3_tb_a * c3_pb_b[c3_i583];
  }

  for (c3_i584 = 0; c3_i584 < 9; c3_i584 = c3_i584 + 1) {
    c3_ub_a[c3_i584] = c3_hb_y[c3_i584];
  }

  for (c3_i585 = 0; c3_i585 < 3; c3_i585 = c3_i585 + 1) {
    c3_f_r4[c3_i585] = c3_b_r4[c3_i585];
  }

  c3_hat(chartInstance, c3_f_r4, c3_qb_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i586 = 0; c3_i586 < 9; c3_i586 = c3_i586 + 1) {
    c3_md_A[c3_i586] = c3_ub_a[c3_i586];
  }

  for (c3_i587 = 0; c3_i587 < 9; c3_i587 = c3_i587 + 1) {
    c3_md_B[c3_i587] = c3_qb_b[c3_i587];
  }

  for (c3_i588 = 0; c3_i588 < 9; c3_i588 = c3_i588 + 1) {
    c3_nd_A[c3_i588] = c3_md_A[c3_i588];
  }

  for (c3_i589 = 0; c3_i589 < 9; c3_i589 = c3_i589 + 1) {
    c3_nd_B[c3_i589] = c3_md_B[c3_i589];
  }

  for (c3_i590 = 0; c3_i590 < 9; c3_i590 = c3_i590 + 1) {
    c3_od_A[c3_i590] = c3_nd_A[c3_i590];
  }

  for (c3_i591 = 0; c3_i591 < 9; c3_i591 = c3_i591 + 1) {
    c3_od_B[c3_i591] = c3_nd_B[c3_i591];
  }

  for (c3_i592 = 0; c3_i592 < 3; c3_i592 = c3_i592 + 1) {
    c3_i593 = 0;
    for (c3_i594 = 0; c3_i594 < 3; c3_i594 = c3_i594 + 1) {
      c3_ib_y[c3_i593 + c3_i592] = 0.0;
      c3_i595 = 0;
      for (c3_i596 = 0; c3_i596 < 3; c3_i596 = c3_i596 + 1) {
        c3_ib_y[c3_i593 + c3_i592] = c3_ib_y[c3_i593 + c3_i592] +
          c3_od_A[c3_i595 + c3_i592] * c3_od_B[c3_i596 + c3_i593];
        c3_i595 = c3_i595 + 3;
      }

      c3_i593 = c3_i593 + 3;
    }
  }

  c3_i597 = 0;
  c3_i598 = 0;
  for (c3_i599 = 0; c3_i599 < 3; c3_i599 = c3_i599 + 1) {
    for (c3_i600 = 0; c3_i600 < 3; c3_i600 = c3_i600 + 1) {
      c3_M4[c3_i600 + c3_i597] = c3_eb_y[c3_i600 + c3_i598];
    }

    c3_i597 = c3_i597 + 6;
    c3_i598 = c3_i598 + 3;
  }

  c3_i601 = 0;
  c3_i602 = 0;
  for (c3_i603 = 0; c3_i603 < 3; c3_i603 = c3_i603 + 1) {
    for (c3_i604 = 0; c3_i604 < 3; c3_i604 = c3_i604 + 1) {
      c3_M4[(c3_i604 + c3_i601) + 18] = c3_fb_y[c3_i604 + c3_i602];
    }

    c3_i601 = c3_i601 + 6;
    c3_i602 = c3_i602 + 3;
  }

  c3_i605 = 0;
  c3_i606 = 0;
  for (c3_i607 = 0; c3_i607 < 3; c3_i607 = c3_i607 + 1) {
    for (c3_i608 = 0; c3_i608 < 3; c3_i608 = c3_i608 + 1) {
      c3_M4[(c3_i608 + c3_i605) + 3] = c3_gb_y[c3_i608 + c3_i606];
    }

    c3_i605 = c3_i605 + 6;
    c3_i606 = c3_i606 + 3;
  }

  c3_i609 = 0;
  c3_i610 = 0;
  for (c3_i611 = 0; c3_i611 < 3; c3_i611 = c3_i611 + 1) {
    for (c3_i612 = 0; c3_i612 < 3; c3_i612 = c3_i612 + 1) {
      c3_M4[(c3_i612 + c3_i609) + 21] = c3_I4[c3_i612 + c3_i610] -
        c3_ib_y[c3_i612 + c3_i610];
    }

    c3_i609 = c3_i609 + 6;
    c3_i610 = c3_i610 + 3;
  }

  _SFD_SCRIPT_CALL(0, 107);
  c3_m5 = c3_Ma[4];
  _SFD_SCRIPT_CALL(0, 108);
  for (c3_i613 = 0; c3_i613 < 9; c3_i613 = c3_i613 + 1) {
    c3_e_x[c3_i613] = c3_Ie[c3_i613 + 36];
  }

  for (c3_i_k = 1; c3_i_k < 10; c3_i_k = c3_i_k + 1) {
    c3_j_k = c3_i_k;
    c3_I5[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_j_k), 1, 9, 1, 0) - 1] = c3_e_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_j_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 109);
  c3_vb_a = c3_m5;
  for (c3_i614 = 0; c3_i614 < 9; c3_i614 = c3_i614 + 1) {
    c3_jb_y[c3_i614] = c3_vb_a * c3_dv49[c3_i614];
  }

  c3_wb_a = -c3_m5;
  for (c3_i615 = 0; c3_i615 < 3; c3_i615 = c3_i615 + 1) {
    c3_c_r5[c3_i615] = c3_b_r5[c3_i615];
  }

  c3_hat(chartInstance, c3_c_r5, c3_rb_b);
  for (c3_i616 = 0; c3_i616 < 9; c3_i616 = c3_i616 + 1) {
    c3_kb_y[c3_i616] = c3_wb_a * c3_rb_b[c3_i616];
  }

  c3_xb_a = c3_m5;
  for (c3_i617 = 0; c3_i617 < 3; c3_i617 = c3_i617 + 1) {
    c3_d_r5[c3_i617] = c3_b_r5[c3_i617];
  }

  c3_hat(chartInstance, c3_d_r5, c3_sb_b);
  for (c3_i618 = 0; c3_i618 < 9; c3_i618 = c3_i618 + 1) {
    c3_lb_y[c3_i618] = c3_xb_a * c3_sb_b[c3_i618];
  }

  c3_yb_a = c3_m5;
  for (c3_i619 = 0; c3_i619 < 3; c3_i619 = c3_i619 + 1) {
    c3_e_r5[c3_i619] = c3_b_r5[c3_i619];
  }

  c3_hat(chartInstance, c3_e_r5, c3_tb_b);
  for (c3_i620 = 0; c3_i620 < 9; c3_i620 = c3_i620 + 1) {
    c3_mb_y[c3_i620] = c3_yb_a * c3_tb_b[c3_i620];
  }

  for (c3_i621 = 0; c3_i621 < 9; c3_i621 = c3_i621 + 1) {
    c3_ac_a[c3_i621] = c3_mb_y[c3_i621];
  }

  for (c3_i622 = 0; c3_i622 < 3; c3_i622 = c3_i622 + 1) {
    c3_f_r5[c3_i622] = c3_b_r5[c3_i622];
  }

  c3_hat(chartInstance, c3_f_r5, c3_ub_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i623 = 0; c3_i623 < 9; c3_i623 = c3_i623 + 1) {
    c3_pd_A[c3_i623] = c3_ac_a[c3_i623];
  }

  for (c3_i624 = 0; c3_i624 < 9; c3_i624 = c3_i624 + 1) {
    c3_pd_B[c3_i624] = c3_ub_b[c3_i624];
  }

  for (c3_i625 = 0; c3_i625 < 9; c3_i625 = c3_i625 + 1) {
    c3_qd_A[c3_i625] = c3_pd_A[c3_i625];
  }

  for (c3_i626 = 0; c3_i626 < 9; c3_i626 = c3_i626 + 1) {
    c3_qd_B[c3_i626] = c3_pd_B[c3_i626];
  }

  for (c3_i627 = 0; c3_i627 < 9; c3_i627 = c3_i627 + 1) {
    c3_rd_A[c3_i627] = c3_qd_A[c3_i627];
  }

  for (c3_i628 = 0; c3_i628 < 9; c3_i628 = c3_i628 + 1) {
    c3_rd_B[c3_i628] = c3_qd_B[c3_i628];
  }

  for (c3_i629 = 0; c3_i629 < 3; c3_i629 = c3_i629 + 1) {
    c3_i630 = 0;
    for (c3_i631 = 0; c3_i631 < 3; c3_i631 = c3_i631 + 1) {
      c3_nb_y[c3_i630 + c3_i629] = 0.0;
      c3_i632 = 0;
      for (c3_i633 = 0; c3_i633 < 3; c3_i633 = c3_i633 + 1) {
        c3_nb_y[c3_i630 + c3_i629] = c3_nb_y[c3_i630 + c3_i629] +
          c3_rd_A[c3_i632 + c3_i629] * c3_rd_B[c3_i633 + c3_i630];
        c3_i632 = c3_i632 + 3;
      }

      c3_i630 = c3_i630 + 3;
    }
  }

  c3_i634 = 0;
  c3_i635 = 0;
  for (c3_i636 = 0; c3_i636 < 3; c3_i636 = c3_i636 + 1) {
    for (c3_i637 = 0; c3_i637 < 3; c3_i637 = c3_i637 + 1) {
      c3_M5[c3_i637 + c3_i634] = c3_jb_y[c3_i637 + c3_i635];
    }

    c3_i634 = c3_i634 + 6;
    c3_i635 = c3_i635 + 3;
  }

  c3_i638 = 0;
  c3_i639 = 0;
  for (c3_i640 = 0; c3_i640 < 3; c3_i640 = c3_i640 + 1) {
    for (c3_i641 = 0; c3_i641 < 3; c3_i641 = c3_i641 + 1) {
      c3_M5[(c3_i641 + c3_i638) + 18] = c3_kb_y[c3_i641 + c3_i639];
    }

    c3_i638 = c3_i638 + 6;
    c3_i639 = c3_i639 + 3;
  }

  c3_i642 = 0;
  c3_i643 = 0;
  for (c3_i644 = 0; c3_i644 < 3; c3_i644 = c3_i644 + 1) {
    for (c3_i645 = 0; c3_i645 < 3; c3_i645 = c3_i645 + 1) {
      c3_M5[(c3_i645 + c3_i642) + 3] = c3_lb_y[c3_i645 + c3_i643];
    }

    c3_i642 = c3_i642 + 6;
    c3_i643 = c3_i643 + 3;
  }

  c3_i646 = 0;
  c3_i647 = 0;
  for (c3_i648 = 0; c3_i648 < 3; c3_i648 = c3_i648 + 1) {
    for (c3_i649 = 0; c3_i649 < 3; c3_i649 = c3_i649 + 1) {
      c3_M5[(c3_i649 + c3_i646) + 21] = c3_I5[c3_i649 + c3_i647] -
        c3_nb_y[c3_i649 + c3_i647];
    }

    c3_i646 = c3_i646 + 6;
    c3_i647 = c3_i647 + 3;
  }

  _SFD_SCRIPT_CALL(0, 112);
  c3_m6 = c3_Ma[5];
  _SFD_SCRIPT_CALL(0, 113);
  for (c3_i650 = 0; c3_i650 < 9; c3_i650 = c3_i650 + 1) {
    c3_f_x[c3_i650] = c3_Ie[c3_i650 + 45];
  }

  for (c3_k_k = 1; c3_k_k < 10; c3_k_k = c3_k_k + 1) {
    c3_l_k = c3_k_k;
    c3_I6[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_l_k), 1, 9, 1, 0) - 1] = c3_f_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_l_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 114);
  c3_bc_a = c3_m6;
  for (c3_i651 = 0; c3_i651 < 9; c3_i651 = c3_i651 + 1) {
    c3_ob_y[c3_i651] = c3_bc_a * c3_dv49[c3_i651];
  }

  c3_cc_a = -c3_m6;
  for (c3_i652 = 0; c3_i652 < 3; c3_i652 = c3_i652 + 1) {
    c3_c_r6[c3_i652] = c3_b_r6[c3_i652];
  }

  c3_hat(chartInstance, c3_c_r6, c3_vb_b);
  for (c3_i653 = 0; c3_i653 < 9; c3_i653 = c3_i653 + 1) {
    c3_pb_y[c3_i653] = c3_cc_a * c3_vb_b[c3_i653];
  }

  c3_dc_a = c3_m6;
  for (c3_i654 = 0; c3_i654 < 3; c3_i654 = c3_i654 + 1) {
    c3_d_r6[c3_i654] = c3_b_r6[c3_i654];
  }

  c3_hat(chartInstance, c3_d_r6, c3_wb_b);
  for (c3_i655 = 0; c3_i655 < 9; c3_i655 = c3_i655 + 1) {
    c3_qb_y[c3_i655] = c3_dc_a * c3_wb_b[c3_i655];
  }

  c3_ec_a = c3_m6;
  for (c3_i656 = 0; c3_i656 < 3; c3_i656 = c3_i656 + 1) {
    c3_e_r6[c3_i656] = c3_b_r6[c3_i656];
  }

  c3_hat(chartInstance, c3_e_r6, c3_xb_b);
  for (c3_i657 = 0; c3_i657 < 9; c3_i657 = c3_i657 + 1) {
    c3_rb_y[c3_i657] = c3_ec_a * c3_xb_b[c3_i657];
  }

  for (c3_i658 = 0; c3_i658 < 9; c3_i658 = c3_i658 + 1) {
    c3_fc_a[c3_i658] = c3_rb_y[c3_i658];
  }

  for (c3_i659 = 0; c3_i659 < 3; c3_i659 = c3_i659 + 1) {
    c3_f_r6[c3_i659] = c3_b_r6[c3_i659];
  }

  c3_hat(chartInstance, c3_f_r6, c3_yb_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i660 = 0; c3_i660 < 9; c3_i660 = c3_i660 + 1) {
    c3_sd_A[c3_i660] = c3_fc_a[c3_i660];
  }

  for (c3_i661 = 0; c3_i661 < 9; c3_i661 = c3_i661 + 1) {
    c3_sd_B[c3_i661] = c3_yb_b[c3_i661];
  }

  for (c3_i662 = 0; c3_i662 < 9; c3_i662 = c3_i662 + 1) {
    c3_td_A[c3_i662] = c3_sd_A[c3_i662];
  }

  for (c3_i663 = 0; c3_i663 < 9; c3_i663 = c3_i663 + 1) {
    c3_td_B[c3_i663] = c3_sd_B[c3_i663];
  }

  for (c3_i664 = 0; c3_i664 < 9; c3_i664 = c3_i664 + 1) {
    c3_ud_A[c3_i664] = c3_td_A[c3_i664];
  }

  for (c3_i665 = 0; c3_i665 < 9; c3_i665 = c3_i665 + 1) {
    c3_ud_B[c3_i665] = c3_td_B[c3_i665];
  }

  for (c3_i666 = 0; c3_i666 < 3; c3_i666 = c3_i666 + 1) {
    c3_i667 = 0;
    for (c3_i668 = 0; c3_i668 < 3; c3_i668 = c3_i668 + 1) {
      c3_sb_y[c3_i667 + c3_i666] = 0.0;
      c3_i669 = 0;
      for (c3_i670 = 0; c3_i670 < 3; c3_i670 = c3_i670 + 1) {
        c3_sb_y[c3_i667 + c3_i666] = c3_sb_y[c3_i667 + c3_i666] +
          c3_ud_A[c3_i669 + c3_i666] * c3_ud_B[c3_i670 + c3_i667];
        c3_i669 = c3_i669 + 3;
      }

      c3_i667 = c3_i667 + 3;
    }
  }

  c3_i671 = 0;
  c3_i672 = 0;
  for (c3_i673 = 0; c3_i673 < 3; c3_i673 = c3_i673 + 1) {
    for (c3_i674 = 0; c3_i674 < 3; c3_i674 = c3_i674 + 1) {
      c3_M6[c3_i674 + c3_i671] = c3_ob_y[c3_i674 + c3_i672];
    }

    c3_i671 = c3_i671 + 6;
    c3_i672 = c3_i672 + 3;
  }

  c3_i675 = 0;
  c3_i676 = 0;
  for (c3_i677 = 0; c3_i677 < 3; c3_i677 = c3_i677 + 1) {
    for (c3_i678 = 0; c3_i678 < 3; c3_i678 = c3_i678 + 1) {
      c3_M6[(c3_i678 + c3_i675) + 18] = c3_pb_y[c3_i678 + c3_i676];
    }

    c3_i675 = c3_i675 + 6;
    c3_i676 = c3_i676 + 3;
  }

  c3_i679 = 0;
  c3_i680 = 0;
  for (c3_i681 = 0; c3_i681 < 3; c3_i681 = c3_i681 + 1) {
    for (c3_i682 = 0; c3_i682 < 3; c3_i682 = c3_i682 + 1) {
      c3_M6[(c3_i682 + c3_i679) + 3] = c3_qb_y[c3_i682 + c3_i680];
    }

    c3_i679 = c3_i679 + 6;
    c3_i680 = c3_i680 + 3;
  }

  c3_i683 = 0;
  c3_i684 = 0;
  for (c3_i685 = 0; c3_i685 < 3; c3_i685 = c3_i685 + 1) {
    for (c3_i686 = 0; c3_i686 < 3; c3_i686 = c3_i686 + 1) {
      c3_M6[(c3_i686 + c3_i683) + 21] = c3_I6[c3_i686 + c3_i684] -
        c3_sb_y[c3_i686 + c3_i684];
    }

    c3_i683 = c3_i683 + 6;
    c3_i684 = c3_i684 + 3;
  }

  /*  %% Forward Recursion (kinematic) */
  /*  Initial State */
  _SFD_SCRIPT_CALL(0, 119);
  for (c3_i687 = 0; c3_i687 < 6; c3_i687 = c3_i687 + 1) {
    c3_V0[c3_i687] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 120);
  for (c3_i688 = 0; c3_i688 < 6; c3_i688 = c3_i688 + 1) {
    c3_dV0[c3_i688] = c3_dv50[c3_i688];
  }

  /*  Joint 1: */
  _SFD_SCRIPT_CALL(0, 123);
  for (c3_i689 = 0; c3_i689 < 16; c3_i689 = c3_i689 + 1) {
    c3_gc_a[c3_i689] = c3_g01_0[c3_i689];
  }

  for (c3_i690 = 0; c3_i690 < 6; c3_i690 = c3_i690 + 1) {
    c3_dv51[c3_i690] = c3_dv10[c3_i690];
  }

  c3_expg(chartInstance, c3_dv51, c3_EnPos[0], c3_ac_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i691 = 0; c3_i691 < 16; c3_i691 = c3_i691 + 1) {
    c3_vd_A[c3_i691] = c3_gc_a[c3_i691];
  }

  for (c3_i692 = 0; c3_i692 < 16; c3_i692 = c3_i692 + 1) {
    c3_vd_B[c3_i692] = c3_ac_b[c3_i692];
  }

  for (c3_i693 = 0; c3_i693 < 16; c3_i693 = c3_i693 + 1) {
    c3_g01[c3_i693] = 0.0;
  }

  for (c3_i694 = 0; c3_i694 < 16; c3_i694 = c3_i694 + 1) {
    c3_wd_A[c3_i694] = c3_vd_A[c3_i694];
  }

  for (c3_i695 = 0; c3_i695 < 16; c3_i695 = c3_i695 + 1) {
    c3_wd_B[c3_i695] = c3_vd_B[c3_i695];
  }

  for (c3_i696 = 0; c3_i696 < 16; c3_i696 = c3_i696 + 1) {
    c3_xd_A[c3_i696] = c3_wd_A[c3_i696];
  }

  for (c3_i697 = 0; c3_i697 < 16; c3_i697 = c3_i697 + 1) {
    c3_xd_B[c3_i697] = c3_wd_B[c3_i697];
  }

  for (c3_i698 = 0; c3_i698 < 4; c3_i698 = c3_i698 + 1) {
    c3_i699 = 0;
    for (c3_i700 = 0; c3_i700 < 4; c3_i700 = c3_i700 + 1) {
      c3_g01[c3_i699 + c3_i698] = 0.0;
      c3_i701 = 0;
      for (c3_i702 = 0; c3_i702 < 4; c3_i702 = c3_i702 + 1) {
        c3_g01[c3_i699 + c3_i698] = c3_g01[c3_i699 + c3_i698] + c3_xd_A[c3_i701
          + c3_i698] * c3_xd_B[c3_i702 + c3_i699];
        c3_i701 = c3_i701 + 4;
      }

      c3_i699 = c3_i699 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 124);
  for (c3_i703 = 0; c3_i703 < 16; c3_i703 = c3_i703 + 1) {
    c3_b_g01[c3_i703] = c3_g01[c3_i703];
  }

  for (c3_i704 = 0; c3_i704 < 16; c3_i704 = c3_i704 + 1) {
    c3_dv53[c3_i704] = c3_dv52[c3_i704];
  }

  c3_b_mldivide(chartInstance, c3_b_g01, c3_dv53, c3_dv54);
  for (c3_i705 = 0; c3_i705 < 16; c3_i705 = c3_i705 + 1) {
    c3_dv55[c3_i705] = c3_dv54[c3_i705];
  }

  c3_Adjoint(chartInstance, c3_dv55, c3_dv56);
  for (c3_i706 = 0; c3_i706 < 36; c3_i706 = c3_i706 + 1) {
    c3_Adinvg01[c3_i706] = c3_dv56[c3_i706];
  }

  _SFD_SCRIPT_CALL(0, 125);
  for (c3_i707 = 0; c3_i707 < 36; c3_i707 = c3_i707 + 1) {
    c3_hc_a[c3_i707] = c3_Adinvg01[c3_i707];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i708 = 0; c3_i708 < 36; c3_i708 = c3_i708 + 1) {
    c3_ic_a[c3_i708] = c3_hc_a[c3_i708];
  }

  for (c3_i709 = 0; c3_i709 < 6; c3_i709 = c3_i709 + 1) {
    c3_dv57[c3_i709] = 0.0;
  }

  for (c3_i710 = 0; c3_i710 < 6; c3_i710 = c3_i710 + 1) {
    c3_dv58[c3_i710] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ic_a, c3_dv57, c3_dv58, c3_tb_y);
  c3_bc_b = c3_RefVel[0];
  for (c3_i711 = 0; c3_i711 < 6; c3_i711 = c3_i711 + 1) {
    c3_ub_y[c3_i711] = c3_dv10[c3_i711] * c3_bc_b;
  }

  for (c3_i712 = 0; c3_i712 < 6; c3_i712 = c3_i712 + 1) {
    c3_V1[c3_i712] = c3_tb_y[c3_i712] + c3_ub_y[c3_i712];
  }

  _SFD_SCRIPT_CALL(0, 126);
  c3_cc_b = c3_RefAcc[0];
  for (c3_i713 = 0; c3_i713 < 6; c3_i713 = c3_i713 + 1) {
    c3_vb_y[c3_i713] = c3_dv10[c3_i713] * c3_cc_b;
  }

  for (c3_i714 = 0; c3_i714 < 36; c3_i714 = c3_i714 + 1) {
    c3_jc_a[c3_i714] = c3_Adinvg01[c3_i714];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i715 = 0; c3_i715 < 36; c3_i715 = c3_i715 + 1) {
    c3_kc_a[c3_i715] = c3_jc_a[c3_i715];
  }

  for (c3_i716 = 0; c3_i716 < 6; c3_i716 = c3_i716 + 1) {
    c3_dv59[c3_i716] = c3_dv50[c3_i716];
  }

  for (c3_i717 = 0; c3_i717 < 6; c3_i717 = c3_i717 + 1) {
    c3_dv60[c3_i717] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_kc_a, c3_dv59, c3_dv60, c3_wb_y);
  c3_dc_b = c3_EnVel[0];
  for (c3_i718 = 0; c3_i718 < 6; c3_i718 = c3_i718 + 1) {
    c3_xb_y[c3_i718] = c3_dv10[c3_i718] * c3_dc_b;
  }

  for (c3_i719 = 0; c3_i719 < 36; c3_i719 = c3_i719 + 1) {
    c3_lc_a[c3_i719] = c3_Adinvg01[c3_i719];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i720 = 0; c3_i720 < 36; c3_i720 = c3_i720 + 1) {
    c3_mc_a[c3_i720] = c3_lc_a[c3_i720];
  }

  for (c3_i721 = 0; c3_i721 < 6; c3_i721 = c3_i721 + 1) {
    c3_dv61[c3_i721] = 0.0;
  }

  for (c3_i722 = 0; c3_i722 < 6; c3_i722 = c3_i722 + 1) {
    c3_dv62[c3_i722] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_mc_a, c3_dv61, c3_dv62, c3_yb_y);
  for (c3_i723 = 0; c3_i723 < 6; c3_i723 = c3_i723 + 1) {
    c3_ac_y[c3_i723] = c3_xb_y[c3_i723];
  }

  c3_ad(chartInstance, c3_ac_y, c3_nc_a);
  for (c3_i724 = 0; c3_i724 < 6; c3_i724 = c3_i724 + 1) {
    c3_ec_b[c3_i724] = c3_yb_y[c3_i724];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i725 = 0; c3_i725 < 36; c3_i725 = c3_i725 + 1) {
    c3_oc_a[c3_i725] = c3_nc_a[c3_i725];
  }

  for (c3_i726 = 0; c3_i726 < 6; c3_i726 = c3_i726 + 1) {
    c3_fc_b[c3_i726] = c3_ec_b[c3_i726];
  }

  for (c3_i727 = 0; c3_i727 < 6; c3_i727 = c3_i727 + 1) {
    c3_dv63[c3_i727] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_oc_a, c3_fc_b, c3_dv63, c3_bc_y);
  for (c3_i728 = 0; c3_i728 < 6; c3_i728 = c3_i728 + 1) {
    c3_dV1[c3_i728] = (c3_vb_y[c3_i728] + c3_wb_y[c3_i728]) - c3_bc_y[c3_i728];
  }

  _SFD_SCRIPT_CALL(0, 128);
  for (c3_i729 = 0; c3_i729 < 6; c3_i729 = c3_i729 + 1) {
    c3_JntVel[c3_i729] = c3_V1[c3_i729];
  }

  _SFD_SCRIPT_CALL(0, 129);
  for (c3_i730 = 0; c3_i730 < 6; c3_i730 = c3_i730 + 1) {
    c3_JntAcc[c3_i730] = c3_dV1[c3_i730];
  }

  /*  Joint 2: */
  _SFD_SCRIPT_CALL(0, 132);
  for (c3_i731 = 0; c3_i731 < 16; c3_i731 = c3_i731 + 1) {
    c3_pc_a[c3_i731] = c3_g12_0[c3_i731];
  }

  for (c3_i732 = 0; c3_i732 < 6; c3_i732 = c3_i732 + 1) {
    c3_dv64[c3_i732] = c3_dv10[c3_i732];
  }

  c3_expg(chartInstance, c3_dv64, c3_EnPos[1], c3_gc_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i733 = 0; c3_i733 < 16; c3_i733 = c3_i733 + 1) {
    c3_yd_A[c3_i733] = c3_pc_a[c3_i733];
  }

  for (c3_i734 = 0; c3_i734 < 16; c3_i734 = c3_i734 + 1) {
    c3_yd_B[c3_i734] = c3_gc_b[c3_i734];
  }

  for (c3_i735 = 0; c3_i735 < 16; c3_i735 = c3_i735 + 1) {
    c3_g12[c3_i735] = 0.0;
  }

  for (c3_i736 = 0; c3_i736 < 16; c3_i736 = c3_i736 + 1) {
    c3_ae_A[c3_i736] = c3_yd_A[c3_i736];
  }

  for (c3_i737 = 0; c3_i737 < 16; c3_i737 = c3_i737 + 1) {
    c3_ae_B[c3_i737] = c3_yd_B[c3_i737];
  }

  for (c3_i738 = 0; c3_i738 < 16; c3_i738 = c3_i738 + 1) {
    c3_be_A[c3_i738] = c3_ae_A[c3_i738];
  }

  for (c3_i739 = 0; c3_i739 < 16; c3_i739 = c3_i739 + 1) {
    c3_be_B[c3_i739] = c3_ae_B[c3_i739];
  }

  for (c3_i740 = 0; c3_i740 < 4; c3_i740 = c3_i740 + 1) {
    c3_i741 = 0;
    for (c3_i742 = 0; c3_i742 < 4; c3_i742 = c3_i742 + 1) {
      c3_g12[c3_i741 + c3_i740] = 0.0;
      c3_i743 = 0;
      for (c3_i744 = 0; c3_i744 < 4; c3_i744 = c3_i744 + 1) {
        c3_g12[c3_i741 + c3_i740] = c3_g12[c3_i741 + c3_i740] + c3_be_A[c3_i743
          + c3_i740] * c3_be_B[c3_i744 + c3_i741];
        c3_i743 = c3_i743 + 4;
      }

      c3_i741 = c3_i741 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 133);
  for (c3_i745 = 0; c3_i745 < 16; c3_i745 = c3_i745 + 1) {
    c3_b_g12[c3_i745] = c3_g12[c3_i745];
  }

  for (c3_i746 = 0; c3_i746 < 16; c3_i746 = c3_i746 + 1) {
    c3_dv65[c3_i746] = c3_dv52[c3_i746];
  }

  c3_b_mldivide(chartInstance, c3_b_g12, c3_dv65, c3_dv66);
  for (c3_i747 = 0; c3_i747 < 16; c3_i747 = c3_i747 + 1) {
    c3_dv67[c3_i747] = c3_dv66[c3_i747];
  }

  c3_Adjoint(chartInstance, c3_dv67, c3_dv68);
  for (c3_i748 = 0; c3_i748 < 36; c3_i748 = c3_i748 + 1) {
    c3_Adinvg12[c3_i748] = c3_dv68[c3_i748];
  }

  _SFD_SCRIPT_CALL(0, 134);
  for (c3_i749 = 0; c3_i749 < 36; c3_i749 = c3_i749 + 1) {
    c3_qc_a[c3_i749] = c3_Adinvg12[c3_i749];
  }

  for (c3_i750 = 0; c3_i750 < 6; c3_i750 = c3_i750 + 1) {
    c3_hc_b[c3_i750] = c3_V1[c3_i750];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i751 = 0; c3_i751 < 36; c3_i751 = c3_i751 + 1) {
    c3_rc_a[c3_i751] = c3_qc_a[c3_i751];
  }

  for (c3_i752 = 0; c3_i752 < 6; c3_i752 = c3_i752 + 1) {
    c3_ic_b[c3_i752] = c3_hc_b[c3_i752];
  }

  for (c3_i753 = 0; c3_i753 < 6; c3_i753 = c3_i753 + 1) {
    c3_dv69[c3_i753] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_rc_a, c3_ic_b, c3_dv69, c3_cc_y);
  c3_jc_b = c3_RefVel[1];
  for (c3_i754 = 0; c3_i754 < 6; c3_i754 = c3_i754 + 1) {
    c3_dc_y[c3_i754] = c3_dv10[c3_i754] * c3_jc_b;
  }

  for (c3_i755 = 0; c3_i755 < 6; c3_i755 = c3_i755 + 1) {
    c3_V2[c3_i755] = c3_cc_y[c3_i755] + c3_dc_y[c3_i755];
  }

  _SFD_SCRIPT_CALL(0, 135);
  c3_kc_b = c3_RefAcc[1];
  for (c3_i756 = 0; c3_i756 < 6; c3_i756 = c3_i756 + 1) {
    c3_ec_y[c3_i756] = c3_dv10[c3_i756] * c3_kc_b;
  }

  for (c3_i757 = 0; c3_i757 < 36; c3_i757 = c3_i757 + 1) {
    c3_sc_a[c3_i757] = c3_Adinvg12[c3_i757];
  }

  for (c3_i758 = 0; c3_i758 < 6; c3_i758 = c3_i758 + 1) {
    c3_lc_b[c3_i758] = c3_dV1[c3_i758];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i759 = 0; c3_i759 < 36; c3_i759 = c3_i759 + 1) {
    c3_tc_a[c3_i759] = c3_sc_a[c3_i759];
  }

  for (c3_i760 = 0; c3_i760 < 6; c3_i760 = c3_i760 + 1) {
    c3_mc_b[c3_i760] = c3_lc_b[c3_i760];
  }

  for (c3_i761 = 0; c3_i761 < 6; c3_i761 = c3_i761 + 1) {
    c3_dv70[c3_i761] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_tc_a, c3_mc_b, c3_dv70, c3_fc_y);
  c3_nc_b = c3_EnVel[1];
  for (c3_i762 = 0; c3_i762 < 6; c3_i762 = c3_i762 + 1) {
    c3_gc_y[c3_i762] = c3_dv10[c3_i762] * c3_nc_b;
  }

  for (c3_i763 = 0; c3_i763 < 36; c3_i763 = c3_i763 + 1) {
    c3_uc_a[c3_i763] = c3_Adinvg12[c3_i763];
  }

  for (c3_i764 = 0; c3_i764 < 6; c3_i764 = c3_i764 + 1) {
    c3_oc_b[c3_i764] = c3_V1[c3_i764];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i765 = 0; c3_i765 < 36; c3_i765 = c3_i765 + 1) {
    c3_vc_a[c3_i765] = c3_uc_a[c3_i765];
  }

  for (c3_i766 = 0; c3_i766 < 6; c3_i766 = c3_i766 + 1) {
    c3_pc_b[c3_i766] = c3_oc_b[c3_i766];
  }

  for (c3_i767 = 0; c3_i767 < 6; c3_i767 = c3_i767 + 1) {
    c3_dv71[c3_i767] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_vc_a, c3_pc_b, c3_dv71, c3_hc_y);
  for (c3_i768 = 0; c3_i768 < 6; c3_i768 = c3_i768 + 1) {
    c3_ic_y[c3_i768] = c3_gc_y[c3_i768];
  }

  c3_ad(chartInstance, c3_ic_y, c3_wc_a);
  for (c3_i769 = 0; c3_i769 < 6; c3_i769 = c3_i769 + 1) {
    c3_qc_b[c3_i769] = c3_hc_y[c3_i769];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i770 = 0; c3_i770 < 36; c3_i770 = c3_i770 + 1) {
    c3_xc_a[c3_i770] = c3_wc_a[c3_i770];
  }

  for (c3_i771 = 0; c3_i771 < 6; c3_i771 = c3_i771 + 1) {
    c3_rc_b[c3_i771] = c3_qc_b[c3_i771];
  }

  for (c3_i772 = 0; c3_i772 < 6; c3_i772 = c3_i772 + 1) {
    c3_dv72[c3_i772] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_xc_a, c3_rc_b, c3_dv72, c3_jc_y);
  for (c3_i773 = 0; c3_i773 < 6; c3_i773 = c3_i773 + 1) {
    c3_dV2[c3_i773] = (c3_ec_y[c3_i773] + c3_fc_y[c3_i773]) - c3_jc_y[c3_i773];
  }

  _SFD_SCRIPT_CALL(0, 137);
  for (c3_i774 = 0; c3_i774 < 6; c3_i774 = c3_i774 + 1) {
    c3_JntVel[c3_i774 + 6] = c3_V2[c3_i774];
  }

  _SFD_SCRIPT_CALL(0, 138);
  for (c3_i775 = 0; c3_i775 < 6; c3_i775 = c3_i775 + 1) {
    c3_JntAcc[c3_i775 + 6] = c3_dV2[c3_i775];
  }

  /*  Joint 3: */
  _SFD_SCRIPT_CALL(0, 141);
  for (c3_i776 = 0; c3_i776 < 16; c3_i776 = c3_i776 + 1) {
    c3_yc_a[c3_i776] = c3_g23_0[c3_i776];
  }

  for (c3_i777 = 0; c3_i777 < 6; c3_i777 = c3_i777 + 1) {
    c3_dv73[c3_i777] = c3_dv10[c3_i777];
  }

  c3_expg(chartInstance, c3_dv73, c3_EnPos[2], c3_sc_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i778 = 0; c3_i778 < 16; c3_i778 = c3_i778 + 1) {
    c3_ce_A[c3_i778] = c3_yc_a[c3_i778];
  }

  for (c3_i779 = 0; c3_i779 < 16; c3_i779 = c3_i779 + 1) {
    c3_ce_B[c3_i779] = c3_sc_b[c3_i779];
  }

  for (c3_i780 = 0; c3_i780 < 16; c3_i780 = c3_i780 + 1) {
    c3_g23[c3_i780] = 0.0;
  }

  for (c3_i781 = 0; c3_i781 < 16; c3_i781 = c3_i781 + 1) {
    c3_de_A[c3_i781] = c3_ce_A[c3_i781];
  }

  for (c3_i782 = 0; c3_i782 < 16; c3_i782 = c3_i782 + 1) {
    c3_de_B[c3_i782] = c3_ce_B[c3_i782];
  }

  for (c3_i783 = 0; c3_i783 < 16; c3_i783 = c3_i783 + 1) {
    c3_ee_A[c3_i783] = c3_de_A[c3_i783];
  }

  for (c3_i784 = 0; c3_i784 < 16; c3_i784 = c3_i784 + 1) {
    c3_ee_B[c3_i784] = c3_de_B[c3_i784];
  }

  for (c3_i785 = 0; c3_i785 < 4; c3_i785 = c3_i785 + 1) {
    c3_i786 = 0;
    for (c3_i787 = 0; c3_i787 < 4; c3_i787 = c3_i787 + 1) {
      c3_g23[c3_i786 + c3_i785] = 0.0;
      c3_i788 = 0;
      for (c3_i789 = 0; c3_i789 < 4; c3_i789 = c3_i789 + 1) {
        c3_g23[c3_i786 + c3_i785] = c3_g23[c3_i786 + c3_i785] + c3_ee_A[c3_i788
          + c3_i785] * c3_ee_B[c3_i789 + c3_i786];
        c3_i788 = c3_i788 + 4;
      }

      c3_i786 = c3_i786 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 142);
  for (c3_i790 = 0; c3_i790 < 16; c3_i790 = c3_i790 + 1) {
    c3_b_g23[c3_i790] = c3_g23[c3_i790];
  }

  for (c3_i791 = 0; c3_i791 < 16; c3_i791 = c3_i791 + 1) {
    c3_dv74[c3_i791] = c3_dv52[c3_i791];
  }

  c3_b_mldivide(chartInstance, c3_b_g23, c3_dv74, c3_dv75);
  for (c3_i792 = 0; c3_i792 < 16; c3_i792 = c3_i792 + 1) {
    c3_dv76[c3_i792] = c3_dv75[c3_i792];
  }

  c3_Adjoint(chartInstance, c3_dv76, c3_dv77);
  for (c3_i793 = 0; c3_i793 < 36; c3_i793 = c3_i793 + 1) {
    c3_Adinvg23[c3_i793] = c3_dv77[c3_i793];
  }

  _SFD_SCRIPT_CALL(0, 143);
  for (c3_i794 = 0; c3_i794 < 36; c3_i794 = c3_i794 + 1) {
    c3_ad_a[c3_i794] = c3_Adinvg23[c3_i794];
  }

  for (c3_i795 = 0; c3_i795 < 6; c3_i795 = c3_i795 + 1) {
    c3_tc_b[c3_i795] = c3_V2[c3_i795];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i796 = 0; c3_i796 < 36; c3_i796 = c3_i796 + 1) {
    c3_bd_a[c3_i796] = c3_ad_a[c3_i796];
  }

  for (c3_i797 = 0; c3_i797 < 6; c3_i797 = c3_i797 + 1) {
    c3_uc_b[c3_i797] = c3_tc_b[c3_i797];
  }

  for (c3_i798 = 0; c3_i798 < 6; c3_i798 = c3_i798 + 1) {
    c3_dv78[c3_i798] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_bd_a, c3_uc_b, c3_dv78, c3_kc_y);
  c3_vc_b = c3_RefVel[2];
  for (c3_i799 = 0; c3_i799 < 6; c3_i799 = c3_i799 + 1) {
    c3_lc_y[c3_i799] = c3_dv10[c3_i799] * c3_vc_b;
  }

  for (c3_i800 = 0; c3_i800 < 6; c3_i800 = c3_i800 + 1) {
    c3_V3[c3_i800] = c3_kc_y[c3_i800] + c3_lc_y[c3_i800];
  }

  _SFD_SCRIPT_CALL(0, 144);
  c3_wc_b = c3_RefAcc[2];
  for (c3_i801 = 0; c3_i801 < 6; c3_i801 = c3_i801 + 1) {
    c3_mc_y[c3_i801] = c3_dv10[c3_i801] * c3_wc_b;
  }

  for (c3_i802 = 0; c3_i802 < 36; c3_i802 = c3_i802 + 1) {
    c3_cd_a[c3_i802] = c3_Adinvg23[c3_i802];
  }

  for (c3_i803 = 0; c3_i803 < 6; c3_i803 = c3_i803 + 1) {
    c3_xc_b[c3_i803] = c3_dV2[c3_i803];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i804 = 0; c3_i804 < 36; c3_i804 = c3_i804 + 1) {
    c3_dd_a[c3_i804] = c3_cd_a[c3_i804];
  }

  for (c3_i805 = 0; c3_i805 < 6; c3_i805 = c3_i805 + 1) {
    c3_yc_b[c3_i805] = c3_xc_b[c3_i805];
  }

  for (c3_i806 = 0; c3_i806 < 6; c3_i806 = c3_i806 + 1) {
    c3_dv79[c3_i806] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_dd_a, c3_yc_b, c3_dv79, c3_nc_y);
  c3_ad_b = c3_EnVel[2];
  for (c3_i807 = 0; c3_i807 < 6; c3_i807 = c3_i807 + 1) {
    c3_oc_y[c3_i807] = c3_dv10[c3_i807] * c3_ad_b;
  }

  for (c3_i808 = 0; c3_i808 < 36; c3_i808 = c3_i808 + 1) {
    c3_ed_a[c3_i808] = c3_Adinvg23[c3_i808];
  }

  for (c3_i809 = 0; c3_i809 < 6; c3_i809 = c3_i809 + 1) {
    c3_bd_b[c3_i809] = c3_V2[c3_i809];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i810 = 0; c3_i810 < 36; c3_i810 = c3_i810 + 1) {
    c3_fd_a[c3_i810] = c3_ed_a[c3_i810];
  }

  for (c3_i811 = 0; c3_i811 < 6; c3_i811 = c3_i811 + 1) {
    c3_cd_b[c3_i811] = c3_bd_b[c3_i811];
  }

  for (c3_i812 = 0; c3_i812 < 6; c3_i812 = c3_i812 + 1) {
    c3_dv80[c3_i812] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_fd_a, c3_cd_b, c3_dv80, c3_pc_y);
  for (c3_i813 = 0; c3_i813 < 6; c3_i813 = c3_i813 + 1) {
    c3_qc_y[c3_i813] = c3_oc_y[c3_i813];
  }

  c3_ad(chartInstance, c3_qc_y, c3_gd_a);
  for (c3_i814 = 0; c3_i814 < 6; c3_i814 = c3_i814 + 1) {
    c3_dd_b[c3_i814] = c3_pc_y[c3_i814];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i815 = 0; c3_i815 < 36; c3_i815 = c3_i815 + 1) {
    c3_hd_a[c3_i815] = c3_gd_a[c3_i815];
  }

  for (c3_i816 = 0; c3_i816 < 6; c3_i816 = c3_i816 + 1) {
    c3_ed_b[c3_i816] = c3_dd_b[c3_i816];
  }

  for (c3_i817 = 0; c3_i817 < 6; c3_i817 = c3_i817 + 1) {
    c3_dv81[c3_i817] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_hd_a, c3_ed_b, c3_dv81, c3_rc_y);
  for (c3_i818 = 0; c3_i818 < 6; c3_i818 = c3_i818 + 1) {
    c3_dV3[c3_i818] = (c3_mc_y[c3_i818] + c3_nc_y[c3_i818]) - c3_rc_y[c3_i818];
  }

  _SFD_SCRIPT_CALL(0, 146);
  for (c3_i819 = 0; c3_i819 < 6; c3_i819 = c3_i819 + 1) {
    c3_JntVel[c3_i819 + 12] = c3_V3[c3_i819];
  }

  _SFD_SCRIPT_CALL(0, 147);
  for (c3_i820 = 0; c3_i820 < 6; c3_i820 = c3_i820 + 1) {
    c3_JntAcc[c3_i820 + 12] = c3_dV3[c3_i820];
  }

  /*  Joint 4: */
  _SFD_SCRIPT_CALL(0, 150);
  for (c3_i821 = 0; c3_i821 < 16; c3_i821 = c3_i821 + 1) {
    c3_id_a[c3_i821] = c3_g34_0[c3_i821];
  }

  for (c3_i822 = 0; c3_i822 < 6; c3_i822 = c3_i822 + 1) {
    c3_dv82[c3_i822] = c3_dv10[c3_i822];
  }

  c3_expg(chartInstance, c3_dv82, c3_EnPos[3], c3_fd_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i823 = 0; c3_i823 < 16; c3_i823 = c3_i823 + 1) {
    c3_fe_A[c3_i823] = c3_id_a[c3_i823];
  }

  for (c3_i824 = 0; c3_i824 < 16; c3_i824 = c3_i824 + 1) {
    c3_fe_B[c3_i824] = c3_fd_b[c3_i824];
  }

  for (c3_i825 = 0; c3_i825 < 16; c3_i825 = c3_i825 + 1) {
    c3_g34[c3_i825] = 0.0;
  }

  for (c3_i826 = 0; c3_i826 < 16; c3_i826 = c3_i826 + 1) {
    c3_ge_A[c3_i826] = c3_fe_A[c3_i826];
  }

  for (c3_i827 = 0; c3_i827 < 16; c3_i827 = c3_i827 + 1) {
    c3_ge_B[c3_i827] = c3_fe_B[c3_i827];
  }

  for (c3_i828 = 0; c3_i828 < 16; c3_i828 = c3_i828 + 1) {
    c3_he_A[c3_i828] = c3_ge_A[c3_i828];
  }

  for (c3_i829 = 0; c3_i829 < 16; c3_i829 = c3_i829 + 1) {
    c3_he_B[c3_i829] = c3_ge_B[c3_i829];
  }

  for (c3_i830 = 0; c3_i830 < 4; c3_i830 = c3_i830 + 1) {
    c3_i831 = 0;
    for (c3_i832 = 0; c3_i832 < 4; c3_i832 = c3_i832 + 1) {
      c3_g34[c3_i831 + c3_i830] = 0.0;
      c3_i833 = 0;
      for (c3_i834 = 0; c3_i834 < 4; c3_i834 = c3_i834 + 1) {
        c3_g34[c3_i831 + c3_i830] = c3_g34[c3_i831 + c3_i830] + c3_he_A[c3_i833
          + c3_i830] * c3_he_B[c3_i834 + c3_i831];
        c3_i833 = c3_i833 + 4;
      }

      c3_i831 = c3_i831 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 151);
  for (c3_i835 = 0; c3_i835 < 16; c3_i835 = c3_i835 + 1) {
    c3_b_g34[c3_i835] = c3_g34[c3_i835];
  }

  for (c3_i836 = 0; c3_i836 < 16; c3_i836 = c3_i836 + 1) {
    c3_dv83[c3_i836] = c3_dv52[c3_i836];
  }

  c3_b_mldivide(chartInstance, c3_b_g34, c3_dv83, c3_dv84);
  for (c3_i837 = 0; c3_i837 < 16; c3_i837 = c3_i837 + 1) {
    c3_dv85[c3_i837] = c3_dv84[c3_i837];
  }

  c3_Adjoint(chartInstance, c3_dv85, c3_dv86);
  for (c3_i838 = 0; c3_i838 < 36; c3_i838 = c3_i838 + 1) {
    c3_Adinvg34[c3_i838] = c3_dv86[c3_i838];
  }

  _SFD_SCRIPT_CALL(0, 152);
  for (c3_i839 = 0; c3_i839 < 36; c3_i839 = c3_i839 + 1) {
    c3_jd_a[c3_i839] = c3_Adinvg34[c3_i839];
  }

  for (c3_i840 = 0; c3_i840 < 6; c3_i840 = c3_i840 + 1) {
    c3_gd_b[c3_i840] = c3_V3[c3_i840];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i841 = 0; c3_i841 < 36; c3_i841 = c3_i841 + 1) {
    c3_kd_a[c3_i841] = c3_jd_a[c3_i841];
  }

  for (c3_i842 = 0; c3_i842 < 6; c3_i842 = c3_i842 + 1) {
    c3_hd_b[c3_i842] = c3_gd_b[c3_i842];
  }

  for (c3_i843 = 0; c3_i843 < 6; c3_i843 = c3_i843 + 1) {
    c3_dv87[c3_i843] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_kd_a, c3_hd_b, c3_dv87, c3_sc_y);
  c3_id_b = c3_RefVel[3];
  for (c3_i844 = 0; c3_i844 < 6; c3_i844 = c3_i844 + 1) {
    c3_tc_y[c3_i844] = c3_dv10[c3_i844] * c3_id_b;
  }

  for (c3_i845 = 0; c3_i845 < 6; c3_i845 = c3_i845 + 1) {
    c3_V4[c3_i845] = c3_sc_y[c3_i845] + c3_tc_y[c3_i845];
  }

  _SFD_SCRIPT_CALL(0, 153);
  c3_jd_b = c3_RefAcc[3];
  for (c3_i846 = 0; c3_i846 < 6; c3_i846 = c3_i846 + 1) {
    c3_uc_y[c3_i846] = c3_dv10[c3_i846] * c3_jd_b;
  }

  for (c3_i847 = 0; c3_i847 < 36; c3_i847 = c3_i847 + 1) {
    c3_ld_a[c3_i847] = c3_Adinvg34[c3_i847];
  }

  for (c3_i848 = 0; c3_i848 < 6; c3_i848 = c3_i848 + 1) {
    c3_kd_b[c3_i848] = c3_dV3[c3_i848];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i849 = 0; c3_i849 < 36; c3_i849 = c3_i849 + 1) {
    c3_md_a[c3_i849] = c3_ld_a[c3_i849];
  }

  for (c3_i850 = 0; c3_i850 < 6; c3_i850 = c3_i850 + 1) {
    c3_ld_b[c3_i850] = c3_kd_b[c3_i850];
  }

  for (c3_i851 = 0; c3_i851 < 6; c3_i851 = c3_i851 + 1) {
    c3_dv88[c3_i851] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_md_a, c3_ld_b, c3_dv88, c3_vc_y);
  c3_md_b = c3_EnVel[3];
  for (c3_i852 = 0; c3_i852 < 6; c3_i852 = c3_i852 + 1) {
    c3_wc_y[c3_i852] = c3_dv10[c3_i852] * c3_md_b;
  }

  for (c3_i853 = 0; c3_i853 < 36; c3_i853 = c3_i853 + 1) {
    c3_nd_a[c3_i853] = c3_Adinvg34[c3_i853];
  }

  for (c3_i854 = 0; c3_i854 < 6; c3_i854 = c3_i854 + 1) {
    c3_nd_b[c3_i854] = c3_V3[c3_i854];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i855 = 0; c3_i855 < 36; c3_i855 = c3_i855 + 1) {
    c3_od_a[c3_i855] = c3_nd_a[c3_i855];
  }

  for (c3_i856 = 0; c3_i856 < 6; c3_i856 = c3_i856 + 1) {
    c3_od_b[c3_i856] = c3_nd_b[c3_i856];
  }

  for (c3_i857 = 0; c3_i857 < 6; c3_i857 = c3_i857 + 1) {
    c3_dv89[c3_i857] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_od_a, c3_od_b, c3_dv89, c3_xc_y);
  for (c3_i858 = 0; c3_i858 < 6; c3_i858 = c3_i858 + 1) {
    c3_yc_y[c3_i858] = c3_wc_y[c3_i858];
  }

  c3_ad(chartInstance, c3_yc_y, c3_pd_a);
  for (c3_i859 = 0; c3_i859 < 6; c3_i859 = c3_i859 + 1) {
    c3_pd_b[c3_i859] = c3_xc_y[c3_i859];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i860 = 0; c3_i860 < 36; c3_i860 = c3_i860 + 1) {
    c3_qd_a[c3_i860] = c3_pd_a[c3_i860];
  }

  for (c3_i861 = 0; c3_i861 < 6; c3_i861 = c3_i861 + 1) {
    c3_qd_b[c3_i861] = c3_pd_b[c3_i861];
  }

  for (c3_i862 = 0; c3_i862 < 6; c3_i862 = c3_i862 + 1) {
    c3_dv90[c3_i862] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_qd_a, c3_qd_b, c3_dv90, c3_ad_y);
  for (c3_i863 = 0; c3_i863 < 6; c3_i863 = c3_i863 + 1) {
    c3_dV4[c3_i863] = (c3_uc_y[c3_i863] + c3_vc_y[c3_i863]) - c3_ad_y[c3_i863];
  }

  _SFD_SCRIPT_CALL(0, 155);
  for (c3_i864 = 0; c3_i864 < 6; c3_i864 = c3_i864 + 1) {
    c3_JntVel[c3_i864 + 18] = c3_V4[c3_i864];
  }

  _SFD_SCRIPT_CALL(0, 156);
  for (c3_i865 = 0; c3_i865 < 6; c3_i865 = c3_i865 + 1) {
    c3_JntAcc[c3_i865 + 18] = c3_dV4[c3_i865];
  }

  /*  Joint 5: */
  _SFD_SCRIPT_CALL(0, 159);
  for (c3_i866 = 0; c3_i866 < 16; c3_i866 = c3_i866 + 1) {
    c3_rd_a[c3_i866] = c3_g45_0[c3_i866];
  }

  for (c3_i867 = 0; c3_i867 < 6; c3_i867 = c3_i867 + 1) {
    c3_dv91[c3_i867] = c3_dv10[c3_i867];
  }

  c3_expg(chartInstance, c3_dv91, c3_EnPos[4], c3_rd_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i868 = 0; c3_i868 < 16; c3_i868 = c3_i868 + 1) {
    c3_ie_A[c3_i868] = c3_rd_a[c3_i868];
  }

  for (c3_i869 = 0; c3_i869 < 16; c3_i869 = c3_i869 + 1) {
    c3_ie_B[c3_i869] = c3_rd_b[c3_i869];
  }

  for (c3_i870 = 0; c3_i870 < 16; c3_i870 = c3_i870 + 1) {
    c3_g45[c3_i870] = 0.0;
  }

  for (c3_i871 = 0; c3_i871 < 16; c3_i871 = c3_i871 + 1) {
    c3_je_A[c3_i871] = c3_ie_A[c3_i871];
  }

  for (c3_i872 = 0; c3_i872 < 16; c3_i872 = c3_i872 + 1) {
    c3_je_B[c3_i872] = c3_ie_B[c3_i872];
  }

  for (c3_i873 = 0; c3_i873 < 16; c3_i873 = c3_i873 + 1) {
    c3_ke_A[c3_i873] = c3_je_A[c3_i873];
  }

  for (c3_i874 = 0; c3_i874 < 16; c3_i874 = c3_i874 + 1) {
    c3_ke_B[c3_i874] = c3_je_B[c3_i874];
  }

  for (c3_i875 = 0; c3_i875 < 4; c3_i875 = c3_i875 + 1) {
    c3_i876 = 0;
    for (c3_i877 = 0; c3_i877 < 4; c3_i877 = c3_i877 + 1) {
      c3_g45[c3_i876 + c3_i875] = 0.0;
      c3_i878 = 0;
      for (c3_i879 = 0; c3_i879 < 4; c3_i879 = c3_i879 + 1) {
        c3_g45[c3_i876 + c3_i875] = c3_g45[c3_i876 + c3_i875] + c3_ke_A[c3_i878
          + c3_i875] * c3_ke_B[c3_i879 + c3_i876];
        c3_i878 = c3_i878 + 4;
      }

      c3_i876 = c3_i876 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 160);
  for (c3_i880 = 0; c3_i880 < 16; c3_i880 = c3_i880 + 1) {
    c3_b_g45[c3_i880] = c3_g45[c3_i880];
  }

  for (c3_i881 = 0; c3_i881 < 16; c3_i881 = c3_i881 + 1) {
    c3_dv92[c3_i881] = c3_dv52[c3_i881];
  }

  c3_b_mldivide(chartInstance, c3_b_g45, c3_dv92, c3_dv93);
  for (c3_i882 = 0; c3_i882 < 16; c3_i882 = c3_i882 + 1) {
    c3_dv94[c3_i882] = c3_dv93[c3_i882];
  }

  c3_Adjoint(chartInstance, c3_dv94, c3_dv95);
  for (c3_i883 = 0; c3_i883 < 36; c3_i883 = c3_i883 + 1) {
    c3_Adinvg45[c3_i883] = c3_dv95[c3_i883];
  }

  _SFD_SCRIPT_CALL(0, 161);
  for (c3_i884 = 0; c3_i884 < 36; c3_i884 = c3_i884 + 1) {
    c3_sd_a[c3_i884] = c3_Adinvg45[c3_i884];
  }

  for (c3_i885 = 0; c3_i885 < 6; c3_i885 = c3_i885 + 1) {
    c3_sd_b[c3_i885] = c3_V4[c3_i885];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i886 = 0; c3_i886 < 36; c3_i886 = c3_i886 + 1) {
    c3_td_a[c3_i886] = c3_sd_a[c3_i886];
  }

  for (c3_i887 = 0; c3_i887 < 6; c3_i887 = c3_i887 + 1) {
    c3_td_b[c3_i887] = c3_sd_b[c3_i887];
  }

  for (c3_i888 = 0; c3_i888 < 6; c3_i888 = c3_i888 + 1) {
    c3_dv96[c3_i888] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_td_a, c3_td_b, c3_dv96, c3_bd_y);
  c3_ud_b = c3_RefVel[4];
  for (c3_i889 = 0; c3_i889 < 6; c3_i889 = c3_i889 + 1) {
    c3_cd_y[c3_i889] = c3_dv10[c3_i889] * c3_ud_b;
  }

  for (c3_i890 = 0; c3_i890 < 6; c3_i890 = c3_i890 + 1) {
    c3_V5[c3_i890] = c3_bd_y[c3_i890] + c3_cd_y[c3_i890];
  }

  _SFD_SCRIPT_CALL(0, 162);
  c3_vd_b = c3_RefAcc[4];
  for (c3_i891 = 0; c3_i891 < 6; c3_i891 = c3_i891 + 1) {
    c3_dd_y[c3_i891] = c3_dv10[c3_i891] * c3_vd_b;
  }

  for (c3_i892 = 0; c3_i892 < 36; c3_i892 = c3_i892 + 1) {
    c3_ud_a[c3_i892] = c3_Adinvg45[c3_i892];
  }

  for (c3_i893 = 0; c3_i893 < 6; c3_i893 = c3_i893 + 1) {
    c3_wd_b[c3_i893] = c3_dV4[c3_i893];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i894 = 0; c3_i894 < 36; c3_i894 = c3_i894 + 1) {
    c3_vd_a[c3_i894] = c3_ud_a[c3_i894];
  }

  for (c3_i895 = 0; c3_i895 < 6; c3_i895 = c3_i895 + 1) {
    c3_xd_b[c3_i895] = c3_wd_b[c3_i895];
  }

  for (c3_i896 = 0; c3_i896 < 6; c3_i896 = c3_i896 + 1) {
    c3_dv97[c3_i896] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_vd_a, c3_xd_b, c3_dv97, c3_ed_y);
  c3_yd_b = c3_EnVel[4];
  for (c3_i897 = 0; c3_i897 < 6; c3_i897 = c3_i897 + 1) {
    c3_fd_y[c3_i897] = c3_dv10[c3_i897] * c3_yd_b;
  }

  for (c3_i898 = 0; c3_i898 < 36; c3_i898 = c3_i898 + 1) {
    c3_wd_a[c3_i898] = c3_Adinvg45[c3_i898];
  }

  for (c3_i899 = 0; c3_i899 < 6; c3_i899 = c3_i899 + 1) {
    c3_ae_b[c3_i899] = c3_V4[c3_i899];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i900 = 0; c3_i900 < 36; c3_i900 = c3_i900 + 1) {
    c3_xd_a[c3_i900] = c3_wd_a[c3_i900];
  }

  for (c3_i901 = 0; c3_i901 < 6; c3_i901 = c3_i901 + 1) {
    c3_be_b[c3_i901] = c3_ae_b[c3_i901];
  }

  for (c3_i902 = 0; c3_i902 < 6; c3_i902 = c3_i902 + 1) {
    c3_dv98[c3_i902] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_xd_a, c3_be_b, c3_dv98, c3_gd_y);
  for (c3_i903 = 0; c3_i903 < 6; c3_i903 = c3_i903 + 1) {
    c3_hd_y[c3_i903] = c3_fd_y[c3_i903];
  }

  c3_ad(chartInstance, c3_hd_y, c3_yd_a);
  for (c3_i904 = 0; c3_i904 < 6; c3_i904 = c3_i904 + 1) {
    c3_ce_b[c3_i904] = c3_gd_y[c3_i904];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i905 = 0; c3_i905 < 36; c3_i905 = c3_i905 + 1) {
    c3_ae_a[c3_i905] = c3_yd_a[c3_i905];
  }

  for (c3_i906 = 0; c3_i906 < 6; c3_i906 = c3_i906 + 1) {
    c3_de_b[c3_i906] = c3_ce_b[c3_i906];
  }

  for (c3_i907 = 0; c3_i907 < 6; c3_i907 = c3_i907 + 1) {
    c3_dv99[c3_i907] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ae_a, c3_de_b, c3_dv99, c3_id_y);
  for (c3_i908 = 0; c3_i908 < 6; c3_i908 = c3_i908 + 1) {
    c3_dV5[c3_i908] = (c3_dd_y[c3_i908] + c3_ed_y[c3_i908]) - c3_id_y[c3_i908];
  }

  _SFD_SCRIPT_CALL(0, 164);
  for (c3_i909 = 0; c3_i909 < 6; c3_i909 = c3_i909 + 1) {
    c3_JntVel[c3_i909 + 24] = c3_V5[c3_i909];
  }

  _SFD_SCRIPT_CALL(0, 165);
  for (c3_i910 = 0; c3_i910 < 6; c3_i910 = c3_i910 + 1) {
    c3_JntAcc[c3_i910 + 24] = c3_dV5[c3_i910];
  }

  /*  Joint 6: */
  _SFD_SCRIPT_CALL(0, 168);
  for (c3_i911 = 0; c3_i911 < 16; c3_i911 = c3_i911 + 1) {
    c3_be_a[c3_i911] = c3_g56_0[c3_i911];
  }

  for (c3_i912 = 0; c3_i912 < 6; c3_i912 = c3_i912 + 1) {
    c3_dv100[c3_i912] = c3_dv10[c3_i912];
  }

  c3_expg(chartInstance, c3_dv100, c3_EnPos[5], c3_ee_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i913 = 0; c3_i913 < 16; c3_i913 = c3_i913 + 1) {
    c3_le_A[c3_i913] = c3_be_a[c3_i913];
  }

  for (c3_i914 = 0; c3_i914 < 16; c3_i914 = c3_i914 + 1) {
    c3_le_B[c3_i914] = c3_ee_b[c3_i914];
  }

  for (c3_i915 = 0; c3_i915 < 16; c3_i915 = c3_i915 + 1) {
    c3_g56[c3_i915] = 0.0;
  }

  for (c3_i916 = 0; c3_i916 < 16; c3_i916 = c3_i916 + 1) {
    c3_me_A[c3_i916] = c3_le_A[c3_i916];
  }

  for (c3_i917 = 0; c3_i917 < 16; c3_i917 = c3_i917 + 1) {
    c3_me_B[c3_i917] = c3_le_B[c3_i917];
  }

  for (c3_i918 = 0; c3_i918 < 16; c3_i918 = c3_i918 + 1) {
    c3_ne_A[c3_i918] = c3_me_A[c3_i918];
  }

  for (c3_i919 = 0; c3_i919 < 16; c3_i919 = c3_i919 + 1) {
    c3_ne_B[c3_i919] = c3_me_B[c3_i919];
  }

  for (c3_i920 = 0; c3_i920 < 4; c3_i920 = c3_i920 + 1) {
    c3_i921 = 0;
    for (c3_i922 = 0; c3_i922 < 4; c3_i922 = c3_i922 + 1) {
      c3_g56[c3_i921 + c3_i920] = 0.0;
      c3_i923 = 0;
      for (c3_i924 = 0; c3_i924 < 4; c3_i924 = c3_i924 + 1) {
        c3_g56[c3_i921 + c3_i920] = c3_g56[c3_i921 + c3_i920] + c3_ne_A[c3_i923
          + c3_i920] * c3_ne_B[c3_i924 + c3_i921];
        c3_i923 = c3_i923 + 4;
      }

      c3_i921 = c3_i921 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 169);
  for (c3_i925 = 0; c3_i925 < 16; c3_i925 = c3_i925 + 1) {
    c3_b_g56[c3_i925] = c3_g56[c3_i925];
  }

  for (c3_i926 = 0; c3_i926 < 16; c3_i926 = c3_i926 + 1) {
    c3_dv101[c3_i926] = c3_dv52[c3_i926];
  }

  c3_b_mldivide(chartInstance, c3_b_g56, c3_dv101, c3_dv102);
  for (c3_i927 = 0; c3_i927 < 16; c3_i927 = c3_i927 + 1) {
    c3_dv103[c3_i927] = c3_dv102[c3_i927];
  }

  c3_Adjoint(chartInstance, c3_dv103, c3_dv104);
  for (c3_i928 = 0; c3_i928 < 36; c3_i928 = c3_i928 + 1) {
    c3_Adinvg56[c3_i928] = c3_dv104[c3_i928];
  }

  _SFD_SCRIPT_CALL(0, 170);
  for (c3_i929 = 0; c3_i929 < 36; c3_i929 = c3_i929 + 1) {
    c3_ce_a[c3_i929] = c3_Adinvg56[c3_i929];
  }

  for (c3_i930 = 0; c3_i930 < 6; c3_i930 = c3_i930 + 1) {
    c3_fe_b[c3_i930] = c3_V5[c3_i930];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i931 = 0; c3_i931 < 36; c3_i931 = c3_i931 + 1) {
    c3_de_a[c3_i931] = c3_ce_a[c3_i931];
  }

  for (c3_i932 = 0; c3_i932 < 6; c3_i932 = c3_i932 + 1) {
    c3_ge_b[c3_i932] = c3_fe_b[c3_i932];
  }

  for (c3_i933 = 0; c3_i933 < 6; c3_i933 = c3_i933 + 1) {
    c3_dv105[c3_i933] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_de_a, c3_ge_b, c3_dv105, c3_jd_y);
  c3_he_b = c3_RefVel[5];
  for (c3_i934 = 0; c3_i934 < 6; c3_i934 = c3_i934 + 1) {
    c3_kd_y[c3_i934] = c3_dv10[c3_i934] * c3_he_b;
  }

  for (c3_i935 = 0; c3_i935 < 6; c3_i935 = c3_i935 + 1) {
    c3_V6[c3_i935] = c3_jd_y[c3_i935] + c3_kd_y[c3_i935];
  }

  _SFD_SCRIPT_CALL(0, 171);
  c3_ie_b = c3_RefAcc[5];
  for (c3_i936 = 0; c3_i936 < 6; c3_i936 = c3_i936 + 1) {
    c3_ld_y[c3_i936] = c3_dv10[c3_i936] * c3_ie_b;
  }

  for (c3_i937 = 0; c3_i937 < 36; c3_i937 = c3_i937 + 1) {
    c3_ee_a[c3_i937] = c3_Adinvg56[c3_i937];
  }

  for (c3_i938 = 0; c3_i938 < 6; c3_i938 = c3_i938 + 1) {
    c3_je_b[c3_i938] = c3_dV5[c3_i938];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i939 = 0; c3_i939 < 36; c3_i939 = c3_i939 + 1) {
    c3_fe_a[c3_i939] = c3_ee_a[c3_i939];
  }

  for (c3_i940 = 0; c3_i940 < 6; c3_i940 = c3_i940 + 1) {
    c3_ke_b[c3_i940] = c3_je_b[c3_i940];
  }

  for (c3_i941 = 0; c3_i941 < 6; c3_i941 = c3_i941 + 1) {
    c3_dv106[c3_i941] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_fe_a, c3_ke_b, c3_dv106, c3_md_y);
  c3_le_b = c3_EnVel[5];
  for (c3_i942 = 0; c3_i942 < 6; c3_i942 = c3_i942 + 1) {
    c3_nd_y[c3_i942] = c3_dv10[c3_i942] * c3_le_b;
  }

  for (c3_i943 = 0; c3_i943 < 36; c3_i943 = c3_i943 + 1) {
    c3_ge_a[c3_i943] = c3_Adinvg56[c3_i943];
  }

  for (c3_i944 = 0; c3_i944 < 6; c3_i944 = c3_i944 + 1) {
    c3_me_b[c3_i944] = c3_V5[c3_i944];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i945 = 0; c3_i945 < 36; c3_i945 = c3_i945 + 1) {
    c3_he_a[c3_i945] = c3_ge_a[c3_i945];
  }

  for (c3_i946 = 0; c3_i946 < 6; c3_i946 = c3_i946 + 1) {
    c3_ne_b[c3_i946] = c3_me_b[c3_i946];
  }

  for (c3_i947 = 0; c3_i947 < 6; c3_i947 = c3_i947 + 1) {
    c3_dv107[c3_i947] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_he_a, c3_ne_b, c3_dv107, c3_od_y);
  for (c3_i948 = 0; c3_i948 < 6; c3_i948 = c3_i948 + 1) {
    c3_pd_y[c3_i948] = c3_nd_y[c3_i948];
  }

  c3_ad(chartInstance, c3_pd_y, c3_ie_a);
  for (c3_i949 = 0; c3_i949 < 6; c3_i949 = c3_i949 + 1) {
    c3_oe_b[c3_i949] = c3_od_y[c3_i949];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i950 = 0; c3_i950 < 36; c3_i950 = c3_i950 + 1) {
    c3_je_a[c3_i950] = c3_ie_a[c3_i950];
  }

  for (c3_i951 = 0; c3_i951 < 6; c3_i951 = c3_i951 + 1) {
    c3_pe_b[c3_i951] = c3_oe_b[c3_i951];
  }

  for (c3_i952 = 0; c3_i952 < 6; c3_i952 = c3_i952 + 1) {
    c3_dv108[c3_i952] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_je_a, c3_pe_b, c3_dv108, c3_qd_y);
  for (c3_i953 = 0; c3_i953 < 6; c3_i953 = c3_i953 + 1) {
    c3_dV6[c3_i953] = (c3_ld_y[c3_i953] + c3_md_y[c3_i953]) - c3_qd_y[c3_i953];
  }

  _SFD_SCRIPT_CALL(0, 173);
  for (c3_i954 = 0; c3_i954 < 6; c3_i954 = c3_i954 + 1) {
    c3_JntVel[c3_i954 + 30] = c3_V6[c3_i954];
  }

  _SFD_SCRIPT_CALL(0, 174);
  for (c3_i955 = 0; c3_i955 < 6; c3_i955 = c3_i955 + 1) {
    c3_JntAcc[c3_i955 + 30] = c3_dV6[c3_i955];
  }

  /*  %% Backward Recursion (inverse dynamic) */
  /*  Initial State */
  _SFD_SCRIPT_CALL(0, 178);
  for (c3_i956 = 0; c3_i956 < 6; c3_i956 = c3_i956 + 1) {
    c3_Tau[c3_i956] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 179);
  for (c3_i957 = 0; c3_i957 < 6; c3_i957 = c3_i957 + 1) {
    c3_F7[c3_i957] = c3_Ft[c3_i957];
  }

  _SFD_SCRIPT_CALL(0, 180);
  for (c3_i958 = 0; c3_i958 < 16; c3_i958 = c3_i958 + 1) {
    c3_b_g67_0[c3_i958] = c3_g67_0[c3_i958];
  }

  for (c3_i959 = 0; c3_i959 < 16; c3_i959 = c3_i959 + 1) {
    c3_dv109[c3_i959] = c3_dv52[c3_i959];
  }

  c3_b_mldivide(chartInstance, c3_b_g67_0, c3_dv109, c3_dv110);
  for (c3_i960 = 0; c3_i960 < 16; c3_i960 = c3_i960 + 1) {
    c3_dv111[c3_i960] = c3_dv110[c3_i960];
  }

  c3_Adjoint(chartInstance, c3_dv111, c3_dv112);
  for (c3_i961 = 0; c3_i961 < 36; c3_i961 = c3_i961 + 1) {
    c3_Adinvg67[c3_i961] = c3_dv112[c3_i961];
  }

  /*  Joint 6 */
  _SFD_SCRIPT_CALL(0, 183);
  c3_i962 = 0;
  for (c3_i963 = 0; c3_i963 < 6; c3_i963 = c3_i963 + 1) {
    c3_i964 = 0;
    for (c3_i965 = 0; c3_i965 < 6; c3_i965 = c3_i965 + 1) {
      c3_ke_a[c3_i965 + c3_i962] = c3_Adinvg67[c3_i964 + c3_i963];
      c3_i964 = c3_i964 + 6;
    }

    c3_i962 = c3_i962 + 6;
  }

  for (c3_i966 = 0; c3_i966 < 6; c3_i966 = c3_i966 + 1) {
    c3_qe_b[c3_i966] = c3_F7[c3_i966];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i967 = 0; c3_i967 < 36; c3_i967 = c3_i967 + 1) {
    c3_le_a[c3_i967] = c3_ke_a[c3_i967];
  }

  for (c3_i968 = 0; c3_i968 < 6; c3_i968 = c3_i968 + 1) {
    c3_re_b[c3_i968] = c3_qe_b[c3_i968];
  }

  for (c3_i969 = 0; c3_i969 < 6; c3_i969 = c3_i969 + 1) {
    c3_dv113[c3_i969] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_le_a, c3_re_b, c3_dv113, c3_rd_y);
  for (c3_i970 = 0; c3_i970 < 36; c3_i970 = c3_i970 + 1) {
    c3_me_a[c3_i970] = c3_M6[c3_i970];
  }

  for (c3_i971 = 0; c3_i971 < 6; c3_i971 = c3_i971 + 1) {
    c3_se_b[c3_i971] = c3_dV6[c3_i971];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i972 = 0; c3_i972 < 36; c3_i972 = c3_i972 + 1) {
    c3_ne_a[c3_i972] = c3_me_a[c3_i972];
  }

  for (c3_i973 = 0; c3_i973 < 6; c3_i973 = c3_i973 + 1) {
    c3_te_b[c3_i973] = c3_se_b[c3_i973];
  }

  for (c3_i974 = 0; c3_i974 < 6; c3_i974 = c3_i974 + 1) {
    c3_dv114[c3_i974] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ne_a, c3_te_b, c3_dv114, c3_sd_y);
  for (c3_i975 = 0; c3_i975 < 6; c3_i975 = c3_i975 + 1) {
    c3_b_V6[c3_i975] = c3_V6[c3_i975];
  }

  c3_ad(chartInstance, c3_b_V6, c3_dv115);
  c3_i976 = 0;
  for (c3_i977 = 0; c3_i977 < 6; c3_i977 = c3_i977 + 1) {
    c3_i978 = 0;
    for (c3_i979 = 0; c3_i979 < 6; c3_i979 = c3_i979 + 1) {
      c3_oe_a[c3_i979 + c3_i976] = c3_dv115[c3_i978 + c3_i977];
      c3_i978 = c3_i978 + 6;
    }

    c3_i976 = c3_i976 + 6;
  }

  for (c3_i980 = 0; c3_i980 < 36; c3_i980 = c3_i980 + 1) {
    c3_ue_b[c3_i980] = c3_M6[c3_i980];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i981 = 0; c3_i981 < 36; c3_i981 = c3_i981 + 1) {
    c3_oe_A[c3_i981] = c3_oe_a[c3_i981];
  }

  for (c3_i982 = 0; c3_i982 < 36; c3_i982 = c3_i982 + 1) {
    c3_oe_B[c3_i982] = c3_ue_b[c3_i982];
  }

  for (c3_i983 = 0; c3_i983 < 36; c3_i983 = c3_i983 + 1) {
    c3_pe_A[c3_i983] = c3_oe_A[c3_i983];
  }

  for (c3_i984 = 0; c3_i984 < 36; c3_i984 = c3_i984 + 1) {
    c3_pe_B[c3_i984] = c3_oe_B[c3_i984];
  }

  for (c3_i985 = 0; c3_i985 < 36; c3_i985 = c3_i985 + 1) {
    c3_qe_A[c3_i985] = c3_pe_A[c3_i985];
  }

  for (c3_i986 = 0; c3_i986 < 36; c3_i986 = c3_i986 + 1) {
    c3_qe_B[c3_i986] = c3_pe_B[c3_i986];
  }

  for (c3_i987 = 0; c3_i987 < 36; c3_i987 = c3_i987 + 1) {
    c3_dv116[c3_i987] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_qe_A, 1, 6, c3_qe_B, 1, 6, 0.0,
                 c3_dv116, 1, 6, c3_td_y);
  for (c3_i988 = 0; c3_i988 < 36; c3_i988 = c3_i988 + 1) {
    c3_pe_a[c3_i988] = c3_td_y[c3_i988];
  }

  for (c3_i989 = 0; c3_i989 < 6; c3_i989 = c3_i989 + 1) {
    c3_ve_b[c3_i989] = c3_V6[c3_i989];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i990 = 0; c3_i990 < 36; c3_i990 = c3_i990 + 1) {
    c3_qe_a[c3_i990] = c3_pe_a[c3_i990];
  }

  for (c3_i991 = 0; c3_i991 < 6; c3_i991 = c3_i991 + 1) {
    c3_we_b[c3_i991] = c3_ve_b[c3_i991];
  }

  for (c3_i992 = 0; c3_i992 < 6; c3_i992 = c3_i992 + 1) {
    c3_dv117[c3_i992] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_qe_a, c3_we_b, c3_dv117, c3_ud_y);
  for (c3_i993 = 0; c3_i993 < 6; c3_i993 = c3_i993 + 1) {
    c3_F6[c3_i993] = (c3_rd_y[c3_i993] + c3_sd_y[c3_i993]) - c3_ud_y[c3_i993];
  }

  _SFD_SCRIPT_CALL(0, 184);
  for (c3_i994 = 0; c3_i994 < 6; c3_i994 = c3_i994 + 1) {
    c3_xe_b[c3_i994] = c3_F6[c3_i994];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i995 = 0; c3_i995 < 6; c3_i995 = c3_i995 + 1) {
    c3_vd_y[c3_i995] = c3_xe_b[c3_i995];
  }

  for (c3_i996 = 0; c3_i996 < 6; c3_i996 = c3_i996 + 1) {
    c3_wd_y[c3_i996] = c3_vd_y[c3_i996];
  }

  for (c3_i997 = 0; c3_i997 < 6; c3_i997 = c3_i997 + 1) {
    c3_xd_y[c3_i997] = c3_wd_y[c3_i997];
  }

  for (c3_i998 = 0; c3_i998 < 6; c3_i998 = c3_i998 + 1) {
    c3_dv118[c3_i998] = c3_dv10[c3_i998];
  }

  for (c3_i999 = 0; c3_i999 < 6; c3_i999 = c3_i999 + 1) {
    c3_yd_y[c3_i999] = c3_xd_y[c3_i999];
  }

  c3_ae_y = c3_ceval_xdot(chartInstance, 6, c3_dv118, 1, 1, c3_yd_y, 1, 1);
  c3_Tau[5] = c3_ae_y;
  _SFD_SCRIPT_CALL(0, 185);
  for (c3_i1000 = 0; c3_i1000 < 6; c3_i1000 = c3_i1000 + 1) {
    c3_JntF[c3_i1000 + 30] = c3_F6[c3_i1000];
  }

  /*  Joint 5 */
  _SFD_SCRIPT_CALL(0, 188);
  c3_i1001 = 0;
  for (c3_i1002 = 0; c3_i1002 < 6; c3_i1002 = c3_i1002 + 1) {
    c3_i1003 = 0;
    for (c3_i1004 = 0; c3_i1004 < 6; c3_i1004 = c3_i1004 + 1) {
      c3_re_a[c3_i1004 + c3_i1001] = c3_Adinvg56[c3_i1003 + c3_i1002];
      c3_i1003 = c3_i1003 + 6;
    }

    c3_i1001 = c3_i1001 + 6;
  }

  for (c3_i1005 = 0; c3_i1005 < 6; c3_i1005 = c3_i1005 + 1) {
    c3_ye_b[c3_i1005] = c3_F6[c3_i1005];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1006 = 0; c3_i1006 < 36; c3_i1006 = c3_i1006 + 1) {
    c3_se_a[c3_i1006] = c3_re_a[c3_i1006];
  }

  for (c3_i1007 = 0; c3_i1007 < 6; c3_i1007 = c3_i1007 + 1) {
    c3_af_b[c3_i1007] = c3_ye_b[c3_i1007];
  }

  for (c3_i1008 = 0; c3_i1008 < 6; c3_i1008 = c3_i1008 + 1) {
    c3_dv119[c3_i1008] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_se_a, c3_af_b, c3_dv119, c3_be_y);
  for (c3_i1009 = 0; c3_i1009 < 36; c3_i1009 = c3_i1009 + 1) {
    c3_te_a[c3_i1009] = c3_M5[c3_i1009];
  }

  for (c3_i1010 = 0; c3_i1010 < 6; c3_i1010 = c3_i1010 + 1) {
    c3_bf_b[c3_i1010] = c3_dV5[c3_i1010];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1011 = 0; c3_i1011 < 36; c3_i1011 = c3_i1011 + 1) {
    c3_ue_a[c3_i1011] = c3_te_a[c3_i1011];
  }

  for (c3_i1012 = 0; c3_i1012 < 6; c3_i1012 = c3_i1012 + 1) {
    c3_cf_b[c3_i1012] = c3_bf_b[c3_i1012];
  }

  for (c3_i1013 = 0; c3_i1013 < 6; c3_i1013 = c3_i1013 + 1) {
    c3_dv120[c3_i1013] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ue_a, c3_cf_b, c3_dv120, c3_ce_y);
  for (c3_i1014 = 0; c3_i1014 < 6; c3_i1014 = c3_i1014 + 1) {
    c3_b_V5[c3_i1014] = c3_V5[c3_i1014];
  }

  c3_ad(chartInstance, c3_b_V5, c3_dv121);
  c3_i1015 = 0;
  for (c3_i1016 = 0; c3_i1016 < 6; c3_i1016 = c3_i1016 + 1) {
    c3_i1017 = 0;
    for (c3_i1018 = 0; c3_i1018 < 6; c3_i1018 = c3_i1018 + 1) {
      c3_ve_a[c3_i1018 + c3_i1015] = c3_dv121[c3_i1017 + c3_i1016];
      c3_i1017 = c3_i1017 + 6;
    }

    c3_i1015 = c3_i1015 + 6;
  }

  for (c3_i1019 = 0; c3_i1019 < 36; c3_i1019 = c3_i1019 + 1) {
    c3_df_b[c3_i1019] = c3_M5[c3_i1019];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1020 = 0; c3_i1020 < 36; c3_i1020 = c3_i1020 + 1) {
    c3_re_A[c3_i1020] = c3_ve_a[c3_i1020];
  }

  for (c3_i1021 = 0; c3_i1021 < 36; c3_i1021 = c3_i1021 + 1) {
    c3_re_B[c3_i1021] = c3_df_b[c3_i1021];
  }

  for (c3_i1022 = 0; c3_i1022 < 36; c3_i1022 = c3_i1022 + 1) {
    c3_se_A[c3_i1022] = c3_re_A[c3_i1022];
  }

  for (c3_i1023 = 0; c3_i1023 < 36; c3_i1023 = c3_i1023 + 1) {
    c3_se_B[c3_i1023] = c3_re_B[c3_i1023];
  }

  for (c3_i1024 = 0; c3_i1024 < 36; c3_i1024 = c3_i1024 + 1) {
    c3_te_A[c3_i1024] = c3_se_A[c3_i1024];
  }

  for (c3_i1025 = 0; c3_i1025 < 36; c3_i1025 = c3_i1025 + 1) {
    c3_te_B[c3_i1025] = c3_se_B[c3_i1025];
  }

  for (c3_i1026 = 0; c3_i1026 < 36; c3_i1026 = c3_i1026 + 1) {
    c3_dv122[c3_i1026] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_te_A, 1, 6, c3_te_B, 1, 6, 0.0,
                 c3_dv122, 1, 6, c3_de_y);
  for (c3_i1027 = 0; c3_i1027 < 36; c3_i1027 = c3_i1027 + 1) {
    c3_we_a[c3_i1027] = c3_de_y[c3_i1027];
  }

  for (c3_i1028 = 0; c3_i1028 < 6; c3_i1028 = c3_i1028 + 1) {
    c3_ef_b[c3_i1028] = c3_V5[c3_i1028];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1029 = 0; c3_i1029 < 36; c3_i1029 = c3_i1029 + 1) {
    c3_xe_a[c3_i1029] = c3_we_a[c3_i1029];
  }

  for (c3_i1030 = 0; c3_i1030 < 6; c3_i1030 = c3_i1030 + 1) {
    c3_ff_b[c3_i1030] = c3_ef_b[c3_i1030];
  }

  for (c3_i1031 = 0; c3_i1031 < 6; c3_i1031 = c3_i1031 + 1) {
    c3_dv123[c3_i1031] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_xe_a, c3_ff_b, c3_dv123, c3_ee_y);
  for (c3_i1032 = 0; c3_i1032 < 6; c3_i1032 = c3_i1032 + 1) {
    c3_F5[c3_i1032] = (c3_be_y[c3_i1032] + c3_ce_y[c3_i1032]) - c3_ee_y[c3_i1032];
  }

  _SFD_SCRIPT_CALL(0, 189);
  for (c3_i1033 = 0; c3_i1033 < 6; c3_i1033 = c3_i1033 + 1) {
    c3_gf_b[c3_i1033] = c3_F5[c3_i1033];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1034 = 0; c3_i1034 < 6; c3_i1034 = c3_i1034 + 1) {
    c3_fe_y[c3_i1034] = c3_gf_b[c3_i1034];
  }

  for (c3_i1035 = 0; c3_i1035 < 6; c3_i1035 = c3_i1035 + 1) {
    c3_ge_y[c3_i1035] = c3_fe_y[c3_i1035];
  }

  for (c3_i1036 = 0; c3_i1036 < 6; c3_i1036 = c3_i1036 + 1) {
    c3_he_y[c3_i1036] = c3_ge_y[c3_i1036];
  }

  for (c3_i1037 = 0; c3_i1037 < 6; c3_i1037 = c3_i1037 + 1) {
    c3_dv124[c3_i1037] = c3_dv10[c3_i1037];
  }

  for (c3_i1038 = 0; c3_i1038 < 6; c3_i1038 = c3_i1038 + 1) {
    c3_ie_y[c3_i1038] = c3_he_y[c3_i1038];
  }

  c3_je_y = c3_ceval_xdot(chartInstance, 6, c3_dv124, 1, 1, c3_ie_y, 1, 1);
  c3_Tau[4] = c3_je_y;
  _SFD_SCRIPT_CALL(0, 190);
  for (c3_i1039 = 0; c3_i1039 < 6; c3_i1039 = c3_i1039 + 1) {
    c3_JntF[c3_i1039 + 24] = c3_F5[c3_i1039];
  }

  /*  Joint 4 */
  _SFD_SCRIPT_CALL(0, 193);
  c3_i1040 = 0;
  for (c3_i1041 = 0; c3_i1041 < 6; c3_i1041 = c3_i1041 + 1) {
    c3_i1042 = 0;
    for (c3_i1043 = 0; c3_i1043 < 6; c3_i1043 = c3_i1043 + 1) {
      c3_ye_a[c3_i1043 + c3_i1040] = c3_Adinvg45[c3_i1042 + c3_i1041];
      c3_i1042 = c3_i1042 + 6;
    }

    c3_i1040 = c3_i1040 + 6;
  }

  for (c3_i1044 = 0; c3_i1044 < 6; c3_i1044 = c3_i1044 + 1) {
    c3_hf_b[c3_i1044] = c3_F5[c3_i1044];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1045 = 0; c3_i1045 < 36; c3_i1045 = c3_i1045 + 1) {
    c3_af_a[c3_i1045] = c3_ye_a[c3_i1045];
  }

  for (c3_i1046 = 0; c3_i1046 < 6; c3_i1046 = c3_i1046 + 1) {
    c3_if_b[c3_i1046] = c3_hf_b[c3_i1046];
  }

  for (c3_i1047 = 0; c3_i1047 < 6; c3_i1047 = c3_i1047 + 1) {
    c3_dv125[c3_i1047] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_af_a, c3_if_b, c3_dv125, c3_ke_y);
  for (c3_i1048 = 0; c3_i1048 < 36; c3_i1048 = c3_i1048 + 1) {
    c3_bf_a[c3_i1048] = c3_M4[c3_i1048];
  }

  for (c3_i1049 = 0; c3_i1049 < 6; c3_i1049 = c3_i1049 + 1) {
    c3_jf_b[c3_i1049] = c3_dV4[c3_i1049];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1050 = 0; c3_i1050 < 36; c3_i1050 = c3_i1050 + 1) {
    c3_cf_a[c3_i1050] = c3_bf_a[c3_i1050];
  }

  for (c3_i1051 = 0; c3_i1051 < 6; c3_i1051 = c3_i1051 + 1) {
    c3_kf_b[c3_i1051] = c3_jf_b[c3_i1051];
  }

  for (c3_i1052 = 0; c3_i1052 < 6; c3_i1052 = c3_i1052 + 1) {
    c3_dv126[c3_i1052] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_cf_a, c3_kf_b, c3_dv126, c3_le_y);
  for (c3_i1053 = 0; c3_i1053 < 6; c3_i1053 = c3_i1053 + 1) {
    c3_b_V4[c3_i1053] = c3_V4[c3_i1053];
  }

  c3_ad(chartInstance, c3_b_V4, c3_dv127);
  c3_i1054 = 0;
  for (c3_i1055 = 0; c3_i1055 < 6; c3_i1055 = c3_i1055 + 1) {
    c3_i1056 = 0;
    for (c3_i1057 = 0; c3_i1057 < 6; c3_i1057 = c3_i1057 + 1) {
      c3_df_a[c3_i1057 + c3_i1054] = c3_dv127[c3_i1056 + c3_i1055];
      c3_i1056 = c3_i1056 + 6;
    }

    c3_i1054 = c3_i1054 + 6;
  }

  for (c3_i1058 = 0; c3_i1058 < 36; c3_i1058 = c3_i1058 + 1) {
    c3_lf_b[c3_i1058] = c3_M4[c3_i1058];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1059 = 0; c3_i1059 < 36; c3_i1059 = c3_i1059 + 1) {
    c3_ue_A[c3_i1059] = c3_df_a[c3_i1059];
  }

  for (c3_i1060 = 0; c3_i1060 < 36; c3_i1060 = c3_i1060 + 1) {
    c3_ue_B[c3_i1060] = c3_lf_b[c3_i1060];
  }

  for (c3_i1061 = 0; c3_i1061 < 36; c3_i1061 = c3_i1061 + 1) {
    c3_ve_A[c3_i1061] = c3_ue_A[c3_i1061];
  }

  for (c3_i1062 = 0; c3_i1062 < 36; c3_i1062 = c3_i1062 + 1) {
    c3_ve_B[c3_i1062] = c3_ue_B[c3_i1062];
  }

  for (c3_i1063 = 0; c3_i1063 < 36; c3_i1063 = c3_i1063 + 1) {
    c3_we_A[c3_i1063] = c3_ve_A[c3_i1063];
  }

  for (c3_i1064 = 0; c3_i1064 < 36; c3_i1064 = c3_i1064 + 1) {
    c3_we_B[c3_i1064] = c3_ve_B[c3_i1064];
  }

  for (c3_i1065 = 0; c3_i1065 < 36; c3_i1065 = c3_i1065 + 1) {
    c3_dv128[c3_i1065] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_we_A, 1, 6, c3_we_B, 1, 6, 0.0,
                 c3_dv128, 1, 6, c3_me_y);
  for (c3_i1066 = 0; c3_i1066 < 36; c3_i1066 = c3_i1066 + 1) {
    c3_ef_a[c3_i1066] = c3_me_y[c3_i1066];
  }

  for (c3_i1067 = 0; c3_i1067 < 6; c3_i1067 = c3_i1067 + 1) {
    c3_mf_b[c3_i1067] = c3_V4[c3_i1067];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1068 = 0; c3_i1068 < 36; c3_i1068 = c3_i1068 + 1) {
    c3_ff_a[c3_i1068] = c3_ef_a[c3_i1068];
  }

  for (c3_i1069 = 0; c3_i1069 < 6; c3_i1069 = c3_i1069 + 1) {
    c3_nf_b[c3_i1069] = c3_mf_b[c3_i1069];
  }

  for (c3_i1070 = 0; c3_i1070 < 6; c3_i1070 = c3_i1070 + 1) {
    c3_dv129[c3_i1070] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ff_a, c3_nf_b, c3_dv129, c3_ne_y);
  for (c3_i1071 = 0; c3_i1071 < 6; c3_i1071 = c3_i1071 + 1) {
    c3_F4[c3_i1071] = (c3_ke_y[c3_i1071] + c3_le_y[c3_i1071]) - c3_ne_y[c3_i1071];
  }

  _SFD_SCRIPT_CALL(0, 194);
  for (c3_i1072 = 0; c3_i1072 < 6; c3_i1072 = c3_i1072 + 1) {
    c3_of_b[c3_i1072] = c3_F4[c3_i1072];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1073 = 0; c3_i1073 < 6; c3_i1073 = c3_i1073 + 1) {
    c3_oe_y[c3_i1073] = c3_of_b[c3_i1073];
  }

  for (c3_i1074 = 0; c3_i1074 < 6; c3_i1074 = c3_i1074 + 1) {
    c3_pe_y[c3_i1074] = c3_oe_y[c3_i1074];
  }

  for (c3_i1075 = 0; c3_i1075 < 6; c3_i1075 = c3_i1075 + 1) {
    c3_qe_y[c3_i1075] = c3_pe_y[c3_i1075];
  }

  for (c3_i1076 = 0; c3_i1076 < 6; c3_i1076 = c3_i1076 + 1) {
    c3_dv130[c3_i1076] = c3_dv10[c3_i1076];
  }

  for (c3_i1077 = 0; c3_i1077 < 6; c3_i1077 = c3_i1077 + 1) {
    c3_re_y[c3_i1077] = c3_qe_y[c3_i1077];
  }

  c3_se_y = c3_ceval_xdot(chartInstance, 6, c3_dv130, 1, 1, c3_re_y, 1, 1);
  c3_Tau[3] = c3_se_y;
  _SFD_SCRIPT_CALL(0, 195);
  for (c3_i1078 = 0; c3_i1078 < 6; c3_i1078 = c3_i1078 + 1) {
    c3_JntF[c3_i1078 + 18] = c3_F4[c3_i1078];
  }

  /*  Joint 3 */
  _SFD_SCRIPT_CALL(0, 198);
  c3_i1079 = 0;
  for (c3_i1080 = 0; c3_i1080 < 6; c3_i1080 = c3_i1080 + 1) {
    c3_i1081 = 0;
    for (c3_i1082 = 0; c3_i1082 < 6; c3_i1082 = c3_i1082 + 1) {
      c3_gf_a[c3_i1082 + c3_i1079] = c3_Adinvg34[c3_i1081 + c3_i1080];
      c3_i1081 = c3_i1081 + 6;
    }

    c3_i1079 = c3_i1079 + 6;
  }

  for (c3_i1083 = 0; c3_i1083 < 6; c3_i1083 = c3_i1083 + 1) {
    c3_pf_b[c3_i1083] = c3_F4[c3_i1083];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1084 = 0; c3_i1084 < 36; c3_i1084 = c3_i1084 + 1) {
    c3_hf_a[c3_i1084] = c3_gf_a[c3_i1084];
  }

  for (c3_i1085 = 0; c3_i1085 < 6; c3_i1085 = c3_i1085 + 1) {
    c3_qf_b[c3_i1085] = c3_pf_b[c3_i1085];
  }

  for (c3_i1086 = 0; c3_i1086 < 6; c3_i1086 = c3_i1086 + 1) {
    c3_dv131[c3_i1086] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_hf_a, c3_qf_b, c3_dv131, c3_te_y);
  for (c3_i1087 = 0; c3_i1087 < 36; c3_i1087 = c3_i1087 + 1) {
    c3_if_a[c3_i1087] = c3_M3[c3_i1087];
  }

  for (c3_i1088 = 0; c3_i1088 < 6; c3_i1088 = c3_i1088 + 1) {
    c3_rf_b[c3_i1088] = c3_dV3[c3_i1088];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1089 = 0; c3_i1089 < 36; c3_i1089 = c3_i1089 + 1) {
    c3_jf_a[c3_i1089] = c3_if_a[c3_i1089];
  }

  for (c3_i1090 = 0; c3_i1090 < 6; c3_i1090 = c3_i1090 + 1) {
    c3_sf_b[c3_i1090] = c3_rf_b[c3_i1090];
  }

  for (c3_i1091 = 0; c3_i1091 < 6; c3_i1091 = c3_i1091 + 1) {
    c3_dv132[c3_i1091] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_jf_a, c3_sf_b, c3_dv132, c3_ue_y);
  for (c3_i1092 = 0; c3_i1092 < 6; c3_i1092 = c3_i1092 + 1) {
    c3_b_V3[c3_i1092] = c3_V3[c3_i1092];
  }

  c3_ad(chartInstance, c3_b_V3, c3_dv133);
  c3_i1093 = 0;
  for (c3_i1094 = 0; c3_i1094 < 6; c3_i1094 = c3_i1094 + 1) {
    c3_i1095 = 0;
    for (c3_i1096 = 0; c3_i1096 < 6; c3_i1096 = c3_i1096 + 1) {
      c3_kf_a[c3_i1096 + c3_i1093] = c3_dv133[c3_i1095 + c3_i1094];
      c3_i1095 = c3_i1095 + 6;
    }

    c3_i1093 = c3_i1093 + 6;
  }

  for (c3_i1097 = 0; c3_i1097 < 36; c3_i1097 = c3_i1097 + 1) {
    c3_tf_b[c3_i1097] = c3_M3[c3_i1097];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1098 = 0; c3_i1098 < 36; c3_i1098 = c3_i1098 + 1) {
    c3_xe_A[c3_i1098] = c3_kf_a[c3_i1098];
  }

  for (c3_i1099 = 0; c3_i1099 < 36; c3_i1099 = c3_i1099 + 1) {
    c3_xe_B[c3_i1099] = c3_tf_b[c3_i1099];
  }

  for (c3_i1100 = 0; c3_i1100 < 36; c3_i1100 = c3_i1100 + 1) {
    c3_ye_A[c3_i1100] = c3_xe_A[c3_i1100];
  }

  for (c3_i1101 = 0; c3_i1101 < 36; c3_i1101 = c3_i1101 + 1) {
    c3_ye_B[c3_i1101] = c3_xe_B[c3_i1101];
  }

  for (c3_i1102 = 0; c3_i1102 < 36; c3_i1102 = c3_i1102 + 1) {
    c3_af_A[c3_i1102] = c3_ye_A[c3_i1102];
  }

  for (c3_i1103 = 0; c3_i1103 < 36; c3_i1103 = c3_i1103 + 1) {
    c3_af_B[c3_i1103] = c3_ye_B[c3_i1103];
  }

  for (c3_i1104 = 0; c3_i1104 < 36; c3_i1104 = c3_i1104 + 1) {
    c3_dv134[c3_i1104] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_af_A, 1, 6, c3_af_B, 1, 6, 0.0,
                 c3_dv134, 1, 6, c3_ve_y);
  for (c3_i1105 = 0; c3_i1105 < 36; c3_i1105 = c3_i1105 + 1) {
    c3_lf_a[c3_i1105] = c3_ve_y[c3_i1105];
  }

  for (c3_i1106 = 0; c3_i1106 < 6; c3_i1106 = c3_i1106 + 1) {
    c3_uf_b[c3_i1106] = c3_V3[c3_i1106];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1107 = 0; c3_i1107 < 36; c3_i1107 = c3_i1107 + 1) {
    c3_mf_a[c3_i1107] = c3_lf_a[c3_i1107];
  }

  for (c3_i1108 = 0; c3_i1108 < 6; c3_i1108 = c3_i1108 + 1) {
    c3_vf_b[c3_i1108] = c3_uf_b[c3_i1108];
  }

  for (c3_i1109 = 0; c3_i1109 < 6; c3_i1109 = c3_i1109 + 1) {
    c3_dv135[c3_i1109] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_mf_a, c3_vf_b, c3_dv135, c3_we_y);
  for (c3_i1110 = 0; c3_i1110 < 6; c3_i1110 = c3_i1110 + 1) {
    c3_F3[c3_i1110] = (c3_te_y[c3_i1110] + c3_ue_y[c3_i1110]) - c3_we_y[c3_i1110];
  }

  _SFD_SCRIPT_CALL(0, 199);
  for (c3_i1111 = 0; c3_i1111 < 6; c3_i1111 = c3_i1111 + 1) {
    c3_wf_b[c3_i1111] = c3_F3[c3_i1111];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1112 = 0; c3_i1112 < 6; c3_i1112 = c3_i1112 + 1) {
    c3_xe_y[c3_i1112] = c3_wf_b[c3_i1112];
  }

  for (c3_i1113 = 0; c3_i1113 < 6; c3_i1113 = c3_i1113 + 1) {
    c3_ye_y[c3_i1113] = c3_xe_y[c3_i1113];
  }

  for (c3_i1114 = 0; c3_i1114 < 6; c3_i1114 = c3_i1114 + 1) {
    c3_af_y[c3_i1114] = c3_ye_y[c3_i1114];
  }

  for (c3_i1115 = 0; c3_i1115 < 6; c3_i1115 = c3_i1115 + 1) {
    c3_dv136[c3_i1115] = c3_dv10[c3_i1115];
  }

  for (c3_i1116 = 0; c3_i1116 < 6; c3_i1116 = c3_i1116 + 1) {
    c3_bf_y[c3_i1116] = c3_af_y[c3_i1116];
  }

  c3_cf_y = c3_ceval_xdot(chartInstance, 6, c3_dv136, 1, 1, c3_bf_y, 1, 1);
  c3_Tau[2] = c3_cf_y;
  _SFD_SCRIPT_CALL(0, 200);
  for (c3_i1117 = 0; c3_i1117 < 6; c3_i1117 = c3_i1117 + 1) {
    c3_JntF[c3_i1117 + 12] = c3_F3[c3_i1117];
  }

  /*  Joint 2 */
  _SFD_SCRIPT_CALL(0, 203);
  c3_i1118 = 0;
  for (c3_i1119 = 0; c3_i1119 < 6; c3_i1119 = c3_i1119 + 1) {
    c3_i1120 = 0;
    for (c3_i1121 = 0; c3_i1121 < 6; c3_i1121 = c3_i1121 + 1) {
      c3_nf_a[c3_i1121 + c3_i1118] = c3_Adinvg23[c3_i1120 + c3_i1119];
      c3_i1120 = c3_i1120 + 6;
    }

    c3_i1118 = c3_i1118 + 6;
  }

  for (c3_i1122 = 0; c3_i1122 < 6; c3_i1122 = c3_i1122 + 1) {
    c3_xf_b[c3_i1122] = c3_F3[c3_i1122];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1123 = 0; c3_i1123 < 36; c3_i1123 = c3_i1123 + 1) {
    c3_of_a[c3_i1123] = c3_nf_a[c3_i1123];
  }

  for (c3_i1124 = 0; c3_i1124 < 6; c3_i1124 = c3_i1124 + 1) {
    c3_yf_b[c3_i1124] = c3_xf_b[c3_i1124];
  }

  for (c3_i1125 = 0; c3_i1125 < 6; c3_i1125 = c3_i1125 + 1) {
    c3_dv137[c3_i1125] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_of_a, c3_yf_b, c3_dv137, c3_df_y);
  for (c3_i1126 = 0; c3_i1126 < 36; c3_i1126 = c3_i1126 + 1) {
    c3_pf_a[c3_i1126] = c3_M2[c3_i1126];
  }

  for (c3_i1127 = 0; c3_i1127 < 6; c3_i1127 = c3_i1127 + 1) {
    c3_ag_b[c3_i1127] = c3_dV2[c3_i1127];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1128 = 0; c3_i1128 < 36; c3_i1128 = c3_i1128 + 1) {
    c3_qf_a[c3_i1128] = c3_pf_a[c3_i1128];
  }

  for (c3_i1129 = 0; c3_i1129 < 6; c3_i1129 = c3_i1129 + 1) {
    c3_bg_b[c3_i1129] = c3_ag_b[c3_i1129];
  }

  for (c3_i1130 = 0; c3_i1130 < 6; c3_i1130 = c3_i1130 + 1) {
    c3_dv138[c3_i1130] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_qf_a, c3_bg_b, c3_dv138, c3_ef_y);
  for (c3_i1131 = 0; c3_i1131 < 6; c3_i1131 = c3_i1131 + 1) {
    c3_b_V2[c3_i1131] = c3_V2[c3_i1131];
  }

  c3_ad(chartInstance, c3_b_V2, c3_dv139);
  c3_i1132 = 0;
  for (c3_i1133 = 0; c3_i1133 < 6; c3_i1133 = c3_i1133 + 1) {
    c3_i1134 = 0;
    for (c3_i1135 = 0; c3_i1135 < 6; c3_i1135 = c3_i1135 + 1) {
      c3_rf_a[c3_i1135 + c3_i1132] = c3_dv139[c3_i1134 + c3_i1133];
      c3_i1134 = c3_i1134 + 6;
    }

    c3_i1132 = c3_i1132 + 6;
  }

  for (c3_i1136 = 0; c3_i1136 < 36; c3_i1136 = c3_i1136 + 1) {
    c3_cg_b[c3_i1136] = c3_M2[c3_i1136];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1137 = 0; c3_i1137 < 36; c3_i1137 = c3_i1137 + 1) {
    c3_bf_A[c3_i1137] = c3_rf_a[c3_i1137];
  }

  for (c3_i1138 = 0; c3_i1138 < 36; c3_i1138 = c3_i1138 + 1) {
    c3_bf_B[c3_i1138] = c3_cg_b[c3_i1138];
  }

  for (c3_i1139 = 0; c3_i1139 < 36; c3_i1139 = c3_i1139 + 1) {
    c3_cf_A[c3_i1139] = c3_bf_A[c3_i1139];
  }

  for (c3_i1140 = 0; c3_i1140 < 36; c3_i1140 = c3_i1140 + 1) {
    c3_cf_B[c3_i1140] = c3_bf_B[c3_i1140];
  }

  for (c3_i1141 = 0; c3_i1141 < 36; c3_i1141 = c3_i1141 + 1) {
    c3_df_A[c3_i1141] = c3_cf_A[c3_i1141];
  }

  for (c3_i1142 = 0; c3_i1142 < 36; c3_i1142 = c3_i1142 + 1) {
    c3_df_B[c3_i1142] = c3_cf_B[c3_i1142];
  }

  for (c3_i1143 = 0; c3_i1143 < 36; c3_i1143 = c3_i1143 + 1) {
    c3_dv140[c3_i1143] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_df_A, 1, 6, c3_df_B, 1, 6, 0.0,
                 c3_dv140, 1, 6, c3_ff_y);
  for (c3_i1144 = 0; c3_i1144 < 36; c3_i1144 = c3_i1144 + 1) {
    c3_sf_a[c3_i1144] = c3_ff_y[c3_i1144];
  }

  for (c3_i1145 = 0; c3_i1145 < 6; c3_i1145 = c3_i1145 + 1) {
    c3_dg_b[c3_i1145] = c3_V2[c3_i1145];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1146 = 0; c3_i1146 < 36; c3_i1146 = c3_i1146 + 1) {
    c3_tf_a[c3_i1146] = c3_sf_a[c3_i1146];
  }

  for (c3_i1147 = 0; c3_i1147 < 6; c3_i1147 = c3_i1147 + 1) {
    c3_eg_b[c3_i1147] = c3_dg_b[c3_i1147];
  }

  for (c3_i1148 = 0; c3_i1148 < 6; c3_i1148 = c3_i1148 + 1) {
    c3_dv141[c3_i1148] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_tf_a, c3_eg_b, c3_dv141, c3_gf_y);
  for (c3_i1149 = 0; c3_i1149 < 6; c3_i1149 = c3_i1149 + 1) {
    c3_F2[c3_i1149] = (c3_df_y[c3_i1149] + c3_ef_y[c3_i1149]) - c3_gf_y[c3_i1149];
  }

  _SFD_SCRIPT_CALL(0, 204);
  for (c3_i1150 = 0; c3_i1150 < 6; c3_i1150 = c3_i1150 + 1) {
    c3_fg_b[c3_i1150] = c3_F2[c3_i1150];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1151 = 0; c3_i1151 < 6; c3_i1151 = c3_i1151 + 1) {
    c3_hf_y[c3_i1151] = c3_fg_b[c3_i1151];
  }

  for (c3_i1152 = 0; c3_i1152 < 6; c3_i1152 = c3_i1152 + 1) {
    c3_if_y[c3_i1152] = c3_hf_y[c3_i1152];
  }

  for (c3_i1153 = 0; c3_i1153 < 6; c3_i1153 = c3_i1153 + 1) {
    c3_jf_y[c3_i1153] = c3_if_y[c3_i1153];
  }

  for (c3_i1154 = 0; c3_i1154 < 6; c3_i1154 = c3_i1154 + 1) {
    c3_dv142[c3_i1154] = c3_dv10[c3_i1154];
  }

  for (c3_i1155 = 0; c3_i1155 < 6; c3_i1155 = c3_i1155 + 1) {
    c3_kf_y[c3_i1155] = c3_jf_y[c3_i1155];
  }

  c3_lf_y = c3_ceval_xdot(chartInstance, 6, c3_dv142, 1, 1, c3_kf_y, 1, 1);
  c3_Tau[1] = c3_lf_y;
  _SFD_SCRIPT_CALL(0, 205);
  for (c3_i1156 = 0; c3_i1156 < 6; c3_i1156 = c3_i1156 + 1) {
    c3_JntF[c3_i1156 + 6] = c3_F2[c3_i1156];
  }

  /*  Joint 1 */
  _SFD_SCRIPT_CALL(0, 208);
  c3_i1157 = 0;
  for (c3_i1158 = 0; c3_i1158 < 6; c3_i1158 = c3_i1158 + 1) {
    c3_i1159 = 0;
    for (c3_i1160 = 0; c3_i1160 < 6; c3_i1160 = c3_i1160 + 1) {
      c3_uf_a[c3_i1160 + c3_i1157] = c3_Adinvg12[c3_i1159 + c3_i1158];
      c3_i1159 = c3_i1159 + 6;
    }

    c3_i1157 = c3_i1157 + 6;
  }

  for (c3_i1161 = 0; c3_i1161 < 6; c3_i1161 = c3_i1161 + 1) {
    c3_gg_b[c3_i1161] = c3_F2[c3_i1161];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1162 = 0; c3_i1162 < 36; c3_i1162 = c3_i1162 + 1) {
    c3_vf_a[c3_i1162] = c3_uf_a[c3_i1162];
  }

  for (c3_i1163 = 0; c3_i1163 < 6; c3_i1163 = c3_i1163 + 1) {
    c3_hg_b[c3_i1163] = c3_gg_b[c3_i1163];
  }

  for (c3_i1164 = 0; c3_i1164 < 6; c3_i1164 = c3_i1164 + 1) {
    c3_dv143[c3_i1164] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_vf_a, c3_hg_b, c3_dv143, c3_mf_y);
  for (c3_i1165 = 0; c3_i1165 < 36; c3_i1165 = c3_i1165 + 1) {
    c3_wf_a[c3_i1165] = c3_M1[c3_i1165];
  }

  for (c3_i1166 = 0; c3_i1166 < 6; c3_i1166 = c3_i1166 + 1) {
    c3_ig_b[c3_i1166] = c3_dV1[c3_i1166];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1167 = 0; c3_i1167 < 36; c3_i1167 = c3_i1167 + 1) {
    c3_xf_a[c3_i1167] = c3_wf_a[c3_i1167];
  }

  for (c3_i1168 = 0; c3_i1168 < 6; c3_i1168 = c3_i1168 + 1) {
    c3_jg_b[c3_i1168] = c3_ig_b[c3_i1168];
  }

  for (c3_i1169 = 0; c3_i1169 < 6; c3_i1169 = c3_i1169 + 1) {
    c3_dv144[c3_i1169] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_xf_a, c3_jg_b, c3_dv144, c3_nf_y);
  for (c3_i1170 = 0; c3_i1170 < 6; c3_i1170 = c3_i1170 + 1) {
    c3_b_V1[c3_i1170] = c3_V1[c3_i1170];
  }

  c3_ad(chartInstance, c3_b_V1, c3_dv145);
  c3_i1171 = 0;
  for (c3_i1172 = 0; c3_i1172 < 6; c3_i1172 = c3_i1172 + 1) {
    c3_i1173 = 0;
    for (c3_i1174 = 0; c3_i1174 < 6; c3_i1174 = c3_i1174 + 1) {
      c3_yf_a[c3_i1174 + c3_i1171] = c3_dv145[c3_i1173 + c3_i1172];
      c3_i1173 = c3_i1173 + 6;
    }

    c3_i1171 = c3_i1171 + 6;
  }

  for (c3_i1175 = 0; c3_i1175 < 36; c3_i1175 = c3_i1175 + 1) {
    c3_kg_b[c3_i1175] = c3_M1[c3_i1175];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1176 = 0; c3_i1176 < 36; c3_i1176 = c3_i1176 + 1) {
    c3_ef_A[c3_i1176] = c3_yf_a[c3_i1176];
  }

  for (c3_i1177 = 0; c3_i1177 < 36; c3_i1177 = c3_i1177 + 1) {
    c3_ef_B[c3_i1177] = c3_kg_b[c3_i1177];
  }

  for (c3_i1178 = 0; c3_i1178 < 36; c3_i1178 = c3_i1178 + 1) {
    c3_ff_A[c3_i1178] = c3_ef_A[c3_i1178];
  }

  for (c3_i1179 = 0; c3_i1179 < 36; c3_i1179 = c3_i1179 + 1) {
    c3_ff_B[c3_i1179] = c3_ef_B[c3_i1179];
  }

  for (c3_i1180 = 0; c3_i1180 < 36; c3_i1180 = c3_i1180 + 1) {
    c3_gf_A[c3_i1180] = c3_ff_A[c3_i1180];
  }

  for (c3_i1181 = 0; c3_i1181 < 36; c3_i1181 = c3_i1181 + 1) {
    c3_gf_B[c3_i1181] = c3_ff_B[c3_i1181];
  }

  for (c3_i1182 = 0; c3_i1182 < 36; c3_i1182 = c3_i1182 + 1) {
    c3_dv146[c3_i1182] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_gf_A, 1, 6, c3_gf_B, 1, 6, 0.0,
                 c3_dv146, 1, 6, c3_of_y);
  for (c3_i1183 = 0; c3_i1183 < 36; c3_i1183 = c3_i1183 + 1) {
    c3_ag_a[c3_i1183] = c3_of_y[c3_i1183];
  }

  for (c3_i1184 = 0; c3_i1184 < 6; c3_i1184 = c3_i1184 + 1) {
    c3_lg_b[c3_i1184] = c3_V1[c3_i1184];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1185 = 0; c3_i1185 < 36; c3_i1185 = c3_i1185 + 1) {
    c3_bg_a[c3_i1185] = c3_ag_a[c3_i1185];
  }

  for (c3_i1186 = 0; c3_i1186 < 6; c3_i1186 = c3_i1186 + 1) {
    c3_mg_b[c3_i1186] = c3_lg_b[c3_i1186];
  }

  for (c3_i1187 = 0; c3_i1187 < 6; c3_i1187 = c3_i1187 + 1) {
    c3_dv147[c3_i1187] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_bg_a, c3_mg_b, c3_dv147, c3_pf_y);
  for (c3_i1188 = 0; c3_i1188 < 6; c3_i1188 = c3_i1188 + 1) {
    c3_F1[c3_i1188] = (c3_mf_y[c3_i1188] + c3_nf_y[c3_i1188]) - c3_pf_y[c3_i1188];
  }

  _SFD_SCRIPT_CALL(0, 209);
  for (c3_i1189 = 0; c3_i1189 < 6; c3_i1189 = c3_i1189 + 1) {
    c3_ng_b[c3_i1189] = c3_F1[c3_i1189];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1190 = 0; c3_i1190 < 6; c3_i1190 = c3_i1190 + 1) {
    c3_qf_y[c3_i1190] = c3_ng_b[c3_i1190];
  }

  for (c3_i1191 = 0; c3_i1191 < 6; c3_i1191 = c3_i1191 + 1) {
    c3_rf_y[c3_i1191] = c3_qf_y[c3_i1191];
  }

  for (c3_i1192 = 0; c3_i1192 < 6; c3_i1192 = c3_i1192 + 1) {
    c3_sf_y[c3_i1192] = c3_rf_y[c3_i1192];
  }

  for (c3_i1193 = 0; c3_i1193 < 6; c3_i1193 = c3_i1193 + 1) {
    c3_dv148[c3_i1193] = c3_dv10[c3_i1193];
  }

  for (c3_i1194 = 0; c3_i1194 < 6; c3_i1194 = c3_i1194 + 1) {
    c3_tf_y[c3_i1194] = c3_sf_y[c3_i1194];
  }

  c3_uf_y = c3_ceval_xdot(chartInstance, 6, c3_dv148, 1, 1, c3_tf_y, 1, 1);
  c3_Tau[0] = c3_uf_y;
  _SFD_SCRIPT_CALL(0, 210);
  for (c3_i1195 = 0; c3_i1195 < 6; c3_i1195 = c3_i1195 + 1) {
    c3_JntF[c3_i1195] = c3_F1[c3_i1195];
  }

  _SFD_SCRIPT_CALL(0, 213);
  for (c3_i1196 = 0; c3_i1196 < 6; c3_i1196 = c3_i1196 + 1) {
    c3_Torque[c3_i1196] = c3_Tau[c3_i1196];
  }

  _SFD_SCRIPT_CALL(0, -213);
  sf_debug_symbol_scope_pop();
}

static void c3_expg(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                    c3_xi[6], real_T c3_theta, real_T c3_g[16])
{
  uint32_T c3_debug_family_var_map[10];
  static const char *c3_sv2[10] = { "v", "w", "n", "R", "P", "nargin", "nargout",
    "xi", "theta", "g" };

  real_T c3_v[3];
  real_T c3_w[3];
  real_T c3_n;
  real_T c3_R[9];
  real_T c3_P[3];
  real_T c3_nargin = 2.0;
  real_T c3_nargout = 1.0;
  int32_T c3_i1197;
  int32_T c3_i1198;
  int32_T c3_i1199;
  real_T c3_b_w[3];
  real_T c3_dv149[9];
  int32_T c3_i1200;
  int32_T c3_i1201;
  real_T c3_a[3];
  real_T c3_b;
  int32_T c3_i1202;
  real_T c3_b_a;
  real_T c3_b_b;
  int32_T c3_i1203;
  real_T c3_A[3];
  real_T c3_B;
  int32_T c3_i1204;
  real_T c3_x[3];
  real_T c3_y;
  int32_T c3_i1205;
  real_T c3_b_x[3];
  real_T c3_b_y;
  int32_T c3_i1206;
  real_T c3_c_x[3];
  real_T c3_c_y;
  int32_T c3_i1207;
  int32_T c3_i1208;
  real_T c3_b_A[3];
  real_T c3_b_B;
  int32_T c3_i1209;
  real_T c3_d_x[3];
  real_T c3_d_y;
  int32_T c3_i1210;
  real_T c3_e_x[3];
  real_T c3_e_y;
  int32_T c3_i1211;
  real_T c3_f_x[3];
  real_T c3_f_y;
  int32_T c3_i1212;
  int32_T c3_i1213;
  real_T c3_c_w[3];
  real_T c3_dv150[9];
  int32_T c3_i1214;
  real_T c3_dv151[9];
  int32_T c3_i1215;
  real_T c3_c_a[9];
  int32_T c3_i1216;
  real_T c3_d_w[3];
  real_T c3_c_b[9];
  int32_T c3_i1217;
  real_T c3_c_A[9];
  int32_T c3_i1218;
  real_T c3_c_B[9];
  int32_T c3_i1219;
  real_T c3_d_A[9];
  int32_T c3_i1220;
  real_T c3_d_B[9];
  int32_T c3_i1221;
  real_T c3_e_A[9];
  int32_T c3_i1222;
  real_T c3_e_B[9];
  int32_T c3_i1223;
  int32_T c3_i1224;
  int32_T c3_i1225;
  real_T c3_g_y[9];
  int32_T c3_i1226;
  int32_T c3_i1227;
  int32_T c3_i1228;
  real_T c3_d_a[9];
  int32_T c3_i1229;
  real_T c3_d_b[3];
  int32_T c3_i1230;
  real_T c3_f_A[9];
  int32_T c3_i1231;
  real_T c3_f_B[3];
  int32_T c3_i1232;
  real_T c3_g_A[9];
  int32_T c3_i1233;
  real_T c3_g_B[3];
  int32_T c3_i1234;
  real_T c3_h_A[9];
  int32_T c3_i1235;
  real_T c3_h_B[3];
  int32_T c3_i1236;
  real_T c3_h_y[3];
  int32_T c3_i1237;
  int32_T c3_i1238;
  int32_T c3_i1239;
  real_T c3_e_a[3];
  int32_T c3_i1240;
  real_T c3_e_b[3];
  int32_T c3_i1241;
  int32_T c3_i1242;
  int32_T c3_i1243;
  real_T c3_i_y[9];
  int32_T c3_i1244;
  real_T c3_f_a[9];
  real_T c3_f_b;
  int32_T c3_i1245;
  real_T c3_j_y[9];
  int32_T c3_i1246;
  real_T c3_g_a[9];
  int32_T c3_i1247;
  real_T c3_g_b[3];
  int32_T c3_i1248;
  real_T c3_i_A[9];
  int32_T c3_i1249;
  real_T c3_i_B[3];
  int32_T c3_i1250;
  real_T c3_j_A[9];
  int32_T c3_i1251;
  real_T c3_j_B[3];
  int32_T c3_i1252;
  real_T c3_k_A[9];
  int32_T c3_i1253;
  real_T c3_k_B[3];
  int32_T c3_i1254;
  real_T c3_k_y[3];
  int32_T c3_i1255;
  int32_T c3_i1256;
  int32_T c3_i1257;
  int32_T c3_i1258;
  int32_T c3_i1259;
  int32_T c3_i1260;
  int32_T c3_i1261;
  int32_T c3_i1262;
  int32_T c3_i1263;
  int32_T c3_i1264;
  static real_T c3_dv152[4] = { 0.0, 0.0, 0.0, 1.0 };

  sf_debug_symbol_scope_push_eml(0U, 10U, 10U, c3_sv2, c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c3_v, c3_h_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c3_w, c3_h_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c3_n, c3_f_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_R, c3_g_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c3_P, c3_h_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c3_xi, c3_b_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c3_theta, c3_f_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c3_g, c3_i_sf_marshall, 9U);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1, 2);
  for (c3_i1197 = 0; c3_i1197 < 3; c3_i1197 = c3_i1197 + 1) {
    c3_v[c3_i1197] = c3_xi[c3_i1197];
  }

  _SFD_SCRIPT_CALL(1, 3);
  for (c3_i1198 = 0; c3_i1198 < 3; c3_i1198 = c3_i1198 + 1) {
    c3_w[c3_i1198] = c3_xi[c3_i1198 + 3];
  }

  _SFD_SCRIPT_CALL(1, 4);
  for (c3_i1199 = 0; c3_i1199 < 3; c3_i1199 = c3_i1199 + 1) {
    c3_b_w[c3_i1199] = c3_w[c3_i1199];
  }

  c3_n = c3_norm(chartInstance, c3_b_w);
  _SFD_SCRIPT_CALL(1, 6);
  c3_eps(chartInstance);
  if (CV_SCRIPT_IF(1, 0, c3_n < 2.2204460492503131E-16)) {
    _SFD_SCRIPT_CALL(1, 7);
    c3_eye(chartInstance, c3_dv149);
    for (c3_i1200 = 0; c3_i1200 < 9; c3_i1200 = c3_i1200 + 1) {
      c3_R[c3_i1200] = c3_dv149[c3_i1200];
    }

    _SFD_SCRIPT_CALL(1, 8);
    for (c3_i1201 = 0; c3_i1201 < 3; c3_i1201 = c3_i1201 + 1) {
      c3_a[c3_i1201] = c3_v[c3_i1201];
    }

    c3_b = c3_theta;
    for (c3_i1202 = 0; c3_i1202 < 3; c3_i1202 = c3_i1202 + 1) {
      c3_P[c3_i1202] = c3_a[c3_i1202] * c3_b;
    }
  } else {
    _SFD_SCRIPT_CALL(1, 10);
    c3_b_a = c3_theta;
    c3_b_b = c3_n;
    c3_theta = c3_b_a * c3_b_b;
    _SFD_SCRIPT_CALL(1, 11);
    for (c3_i1203 = 0; c3_i1203 < 3; c3_i1203 = c3_i1203 + 1) {
      c3_A[c3_i1203] = c3_w[c3_i1203];
    }

    c3_B = c3_n;
    for (c3_i1204 = 0; c3_i1204 < 3; c3_i1204 = c3_i1204 + 1) {
      c3_x[c3_i1204] = c3_A[c3_i1204];
    }

    c3_y = c3_B;
    for (c3_i1205 = 0; c3_i1205 < 3; c3_i1205 = c3_i1205 + 1) {
      c3_b_x[c3_i1205] = c3_x[c3_i1205];
    }

    c3_b_y = c3_y;
    for (c3_i1206 = 0; c3_i1206 < 3; c3_i1206 = c3_i1206 + 1) {
      c3_c_x[c3_i1206] = c3_b_x[c3_i1206];
    }

    c3_c_y = c3_b_y;
    for (c3_i1207 = 0; c3_i1207 < 3; c3_i1207 = c3_i1207 + 1) {
      c3_w[c3_i1207] = c3_c_x[c3_i1207] / c3_c_y;
    }

    _SFD_SCRIPT_CALL(1, 12);
    for (c3_i1208 = 0; c3_i1208 < 3; c3_i1208 = c3_i1208 + 1) {
      c3_b_A[c3_i1208] = c3_v[c3_i1208];
    }

    c3_b_B = c3_n;
    for (c3_i1209 = 0; c3_i1209 < 3; c3_i1209 = c3_i1209 + 1) {
      c3_d_x[c3_i1209] = c3_b_A[c3_i1209];
    }

    c3_d_y = c3_b_B;
    for (c3_i1210 = 0; c3_i1210 < 3; c3_i1210 = c3_i1210 + 1) {
      c3_e_x[c3_i1210] = c3_d_x[c3_i1210];
    }

    c3_e_y = c3_d_y;
    for (c3_i1211 = 0; c3_i1211 < 3; c3_i1211 = c3_i1211 + 1) {
      c3_f_x[c3_i1211] = c3_e_x[c3_i1211];
    }

    c3_f_y = c3_e_y;
    for (c3_i1212 = 0; c3_i1212 < 3; c3_i1212 = c3_i1212 + 1) {
      c3_v[c3_i1212] = c3_f_x[c3_i1212] / c3_f_y;
    }

    _SFD_SCRIPT_CALL(1, 13);
    for (c3_i1213 = 0; c3_i1213 < 3; c3_i1213 = c3_i1213 + 1) {
      c3_c_w[c3_i1213] = c3_w[c3_i1213];
    }

    c3_expr(chartInstance, c3_c_w, c3_theta, c3_dv150);
    for (c3_i1214 = 0; c3_i1214 < 9; c3_i1214 = c3_i1214 + 1) {
      c3_R[c3_i1214] = c3_dv150[c3_i1214];
    }

    _SFD_SCRIPT_CALL(1, 14);
    c3_eye(chartInstance, c3_dv151);
    for (c3_i1215 = 0; c3_i1215 < 9; c3_i1215 = c3_i1215 + 1) {
      c3_c_a[c3_i1215] = c3_dv151[c3_i1215] - c3_R[c3_i1215];
    }

    for (c3_i1216 = 0; c3_i1216 < 3; c3_i1216 = c3_i1216 + 1) {
      c3_d_w[c3_i1216] = c3_w[c3_i1216];
    }

    c3_hat(chartInstance, c3_d_w, c3_c_b);
    c3_c_eml_scalar_eg(chartInstance);
    c3_c_eml_scalar_eg(chartInstance);
    for (c3_i1217 = 0; c3_i1217 < 9; c3_i1217 = c3_i1217 + 1) {
      c3_c_A[c3_i1217] = c3_c_a[c3_i1217];
    }

    for (c3_i1218 = 0; c3_i1218 < 9; c3_i1218 = c3_i1218 + 1) {
      c3_c_B[c3_i1218] = c3_c_b[c3_i1218];
    }

    for (c3_i1219 = 0; c3_i1219 < 9; c3_i1219 = c3_i1219 + 1) {
      c3_d_A[c3_i1219] = c3_c_A[c3_i1219];
    }

    for (c3_i1220 = 0; c3_i1220 < 9; c3_i1220 = c3_i1220 + 1) {
      c3_d_B[c3_i1220] = c3_c_B[c3_i1220];
    }

    for (c3_i1221 = 0; c3_i1221 < 9; c3_i1221 = c3_i1221 + 1) {
      c3_e_A[c3_i1221] = c3_d_A[c3_i1221];
    }

    for (c3_i1222 = 0; c3_i1222 < 9; c3_i1222 = c3_i1222 + 1) {
      c3_e_B[c3_i1222] = c3_d_B[c3_i1222];
    }

    for (c3_i1223 = 0; c3_i1223 < 3; c3_i1223 = c3_i1223 + 1) {
      c3_i1224 = 0;
      for (c3_i1225 = 0; c3_i1225 < 3; c3_i1225 = c3_i1225 + 1) {
        c3_g_y[c3_i1224 + c3_i1223] = 0.0;
        c3_i1226 = 0;
        for (c3_i1227 = 0; c3_i1227 < 3; c3_i1227 = c3_i1227 + 1) {
          c3_g_y[c3_i1224 + c3_i1223] = c3_g_y[c3_i1224 + c3_i1223] +
            c3_e_A[c3_i1226 + c3_i1223] * c3_e_B[c3_i1227 + c3_i1224];
          c3_i1226 = c3_i1226 + 3;
        }

        c3_i1224 = c3_i1224 + 3;
      }
    }

    for (c3_i1228 = 0; c3_i1228 < 9; c3_i1228 = c3_i1228 + 1) {
      c3_d_a[c3_i1228] = c3_g_y[c3_i1228];
    }

    for (c3_i1229 = 0; c3_i1229 < 3; c3_i1229 = c3_i1229 + 1) {
      c3_d_b[c3_i1229] = c3_v[c3_i1229];
    }

    c3_d_eml_scalar_eg(chartInstance);
    c3_d_eml_scalar_eg(chartInstance);
    for (c3_i1230 = 0; c3_i1230 < 9; c3_i1230 = c3_i1230 + 1) {
      c3_f_A[c3_i1230] = c3_d_a[c3_i1230];
    }

    for (c3_i1231 = 0; c3_i1231 < 3; c3_i1231 = c3_i1231 + 1) {
      c3_f_B[c3_i1231] = c3_d_b[c3_i1231];
    }

    for (c3_i1232 = 0; c3_i1232 < 9; c3_i1232 = c3_i1232 + 1) {
      c3_g_A[c3_i1232] = c3_f_A[c3_i1232];
    }

    for (c3_i1233 = 0; c3_i1233 < 3; c3_i1233 = c3_i1233 + 1) {
      c3_g_B[c3_i1233] = c3_f_B[c3_i1233];
    }

    for (c3_i1234 = 0; c3_i1234 < 9; c3_i1234 = c3_i1234 + 1) {
      c3_h_A[c3_i1234] = c3_g_A[c3_i1234];
    }

    for (c3_i1235 = 0; c3_i1235 < 3; c3_i1235 = c3_i1235 + 1) {
      c3_h_B[c3_i1235] = c3_g_B[c3_i1235];
    }

    for (c3_i1236 = 0; c3_i1236 < 3; c3_i1236 = c3_i1236 + 1) {
      c3_h_y[c3_i1236] = 0.0;
      c3_i1237 = 0;
      for (c3_i1238 = 0; c3_i1238 < 3; c3_i1238 = c3_i1238 + 1) {
        c3_h_y[c3_i1236] = c3_h_y[c3_i1236] + c3_h_A[c3_i1237 + c3_i1236] *
          c3_h_B[c3_i1238];
        c3_i1237 = c3_i1237 + 3;
      }
    }

    for (c3_i1239 = 0; c3_i1239 < 3; c3_i1239 = c3_i1239 + 1) {
      c3_e_a[c3_i1239] = c3_w[c3_i1239];
    }

    for (c3_i1240 = 0; c3_i1240 < 3; c3_i1240 = c3_i1240 + 1) {
      c3_e_b[c3_i1240] = c3_w[c3_i1240];
    }

    c3_i1241 = 0;
    for (c3_i1242 = 0; c3_i1242 < 3; c3_i1242 = c3_i1242 + 1) {
      for (c3_i1243 = 0; c3_i1243 < 3; c3_i1243 = c3_i1243 + 1) {
        c3_i_y[c3_i1243 + c3_i1241] = c3_e_a[c3_i1243] * c3_e_b[c3_i1242];
      }

      c3_i1241 = c3_i1241 + 3;
    }

    for (c3_i1244 = 0; c3_i1244 < 9; c3_i1244 = c3_i1244 + 1) {
      c3_f_a[c3_i1244] = c3_i_y[c3_i1244];
    }

    c3_f_b = c3_theta;
    for (c3_i1245 = 0; c3_i1245 < 9; c3_i1245 = c3_i1245 + 1) {
      c3_j_y[c3_i1245] = c3_f_a[c3_i1245] * c3_f_b;
    }

    for (c3_i1246 = 0; c3_i1246 < 9; c3_i1246 = c3_i1246 + 1) {
      c3_g_a[c3_i1246] = c3_j_y[c3_i1246];
    }

    for (c3_i1247 = 0; c3_i1247 < 3; c3_i1247 = c3_i1247 + 1) {
      c3_g_b[c3_i1247] = c3_v[c3_i1247];
    }

    c3_d_eml_scalar_eg(chartInstance);
    c3_d_eml_scalar_eg(chartInstance);
    for (c3_i1248 = 0; c3_i1248 < 9; c3_i1248 = c3_i1248 + 1) {
      c3_i_A[c3_i1248] = c3_g_a[c3_i1248];
    }

    for (c3_i1249 = 0; c3_i1249 < 3; c3_i1249 = c3_i1249 + 1) {
      c3_i_B[c3_i1249] = c3_g_b[c3_i1249];
    }

    for (c3_i1250 = 0; c3_i1250 < 9; c3_i1250 = c3_i1250 + 1) {
      c3_j_A[c3_i1250] = c3_i_A[c3_i1250];
    }

    for (c3_i1251 = 0; c3_i1251 < 3; c3_i1251 = c3_i1251 + 1) {
      c3_j_B[c3_i1251] = c3_i_B[c3_i1251];
    }

    for (c3_i1252 = 0; c3_i1252 < 9; c3_i1252 = c3_i1252 + 1) {
      c3_k_A[c3_i1252] = c3_j_A[c3_i1252];
    }

    for (c3_i1253 = 0; c3_i1253 < 3; c3_i1253 = c3_i1253 + 1) {
      c3_k_B[c3_i1253] = c3_j_B[c3_i1253];
    }

    for (c3_i1254 = 0; c3_i1254 < 3; c3_i1254 = c3_i1254 + 1) {
      c3_k_y[c3_i1254] = 0.0;
      c3_i1255 = 0;
      for (c3_i1256 = 0; c3_i1256 < 3; c3_i1256 = c3_i1256 + 1) {
        c3_k_y[c3_i1254] = c3_k_y[c3_i1254] + c3_k_A[c3_i1255 + c3_i1254] *
          c3_k_B[c3_i1256];
        c3_i1255 = c3_i1255 + 3;
      }
    }

    for (c3_i1257 = 0; c3_i1257 < 3; c3_i1257 = c3_i1257 + 1) {
      c3_P[c3_i1257] = c3_h_y[c3_i1257] + c3_k_y[c3_i1257];
    }
  }

  _SFD_SCRIPT_CALL(1, 17);
  c3_i1258 = 0;
  c3_i1259 = 0;
  for (c3_i1260 = 0; c3_i1260 < 3; c3_i1260 = c3_i1260 + 1) {
    for (c3_i1261 = 0; c3_i1261 < 3; c3_i1261 = c3_i1261 + 1) {
      c3_g[c3_i1261 + c3_i1258] = c3_R[c3_i1261 + c3_i1259];
    }

    c3_i1258 = c3_i1258 + 4;
    c3_i1259 = c3_i1259 + 3;
  }

  for (c3_i1262 = 0; c3_i1262 < 3; c3_i1262 = c3_i1262 + 1) {
    c3_g[c3_i1262 + 12] = c3_P[c3_i1262];
  }

  c3_i1263 = 0;
  for (c3_i1264 = 0; c3_i1264 < 4; c3_i1264 = c3_i1264 + 1) {
    c3_g[c3_i1263 + 3] = c3_dv152[c3_i1264];
    c3_i1263 = c3_i1263 + 4;
  }

  _SFD_SCRIPT_CALL(1, -17);
  sf_debug_symbol_scope_pop();
}

static real_T c3_norm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
                      real_T c3_x[3])
{
  int32_T c3_i1265;
  real_T c3_b_x[3];
  int32_T c3_i1266;
  real_T c3_c_x[3];
  int32_T c3_i1267;
  real_T c3_d_x[3];
  int32_T c3_i1268;
  real_T c3_e_x[3];
  for (c3_i1265 = 0; c3_i1265 < 3; c3_i1265 = c3_i1265 + 1) {
    c3_b_x[c3_i1265] = c3_x[c3_i1265];
  }

  for (c3_i1266 = 0; c3_i1266 < 3; c3_i1266 = c3_i1266 + 1) {
    c3_c_x[c3_i1266] = c3_b_x[c3_i1266];
  }

  for (c3_i1267 = 0; c3_i1267 < 3; c3_i1267 = c3_i1267 + 1) {
    c3_d_x[c3_i1267] = c3_c_x[c3_i1267];
  }

  for (c3_i1268 = 0; c3_i1268 < 3; c3_i1268 = c3_i1268 + 1) {
    c3_e_x[c3_i1268] = c3_d_x[c3_i1268];
  }

  return c3_ceval_xnrm2(chartInstance, 3, c3_e_x, 1, 1);
}

static real_T c3_ceval_xnrm2(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[3], int32_T c3_ix0,
  int32_T c3_incx)
{
  return dnrm232(&c3_n, &c3_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 3, 1, 0) - 1], &
                 c3_incx);
}

static void c3_eps(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
}

static void c3_isVariableSizing(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_eye(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                   c3_I[9])
{
  int32_T c3_i1269;
  int32_T c3_i;
  int32_T c3_b_i;
  c3_isVariableSizing(chartInstance);
  for (c3_i1269 = 0; c3_i1269 < 9; c3_i1269 = c3_i1269 + 1) {
    c3_I[c3_i1269] = 0.0;
  }

  for (c3_i = 1; c3_i < 4; c3_i = c3_i + 1) {
    c3_b_i = c3_i;
    c3_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_b_i), 1, 3, 1, 0) - 1) + 3 * (
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_b_i), 1, 3, 2, 0) - 1)] = 1.0;
  }
}

static void c3_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_expr(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                    c3_w[3], real_T c3_theta, real_T c3_R[9])
{
  uint32_T c3_debug_family_var_map[6];
  real_T c3_n;
  real_T c3_nargin = 2.0;
  real_T c3_nargout = 1.0;
  int32_T c3_i1270;
  real_T c3_b_w[3];
  real_T c3_dv153[9];
  int32_T c3_i1271;
  int32_T c3_i1272;
  real_T c3_c_w[3];
  uint32_T c3_b_debug_family_var_map[4];
  real_T c3_b_nargin = 1.0;
  real_T c3_b_nargout = 1.0;
  real_T c3_W[9];
  int32_T c3_i1273;
  real_T c3_A[9];
  real_T c3_B;
  int32_T c3_i1274;
  real_T c3_x[9];
  real_T c3_y;
  int32_T c3_i1275;
  real_T c3_b_x[9];
  real_T c3_b_y;
  int32_T c3_i1276;
  real_T c3_c_x[9];
  real_T c3_c_y;
  int32_T c3_i1277;
  real_T c3_d_y[9];
  real_T c3_a;
  real_T c3_b;
  real_T c3_e_y;
  real_T c3_d_x;
  real_T c3_e_x;
  real_T c3_f_x;
  int32_T c3_i1278;
  real_T c3_b_a[9];
  real_T c3_b_b;
  int32_T c3_i1279;
  real_T c3_f_y[9];
  int32_T c3_i1280;
  real_T c3_d_w[3];
  uint32_T c3_c_debug_family_var_map[4];
  real_T c3_c_nargin = 1.0;
  real_T c3_c_nargout = 1.0;
  real_T c3_b_W[9];
  int32_T c3_i1281;
  real_T c3_c_a[9];
  int32_T c3_i1282;
  real_T c3_d_a[9];
  real_T c3_c[9];
  real_T c3_e_a;
  real_T c3_b_c;
  int32_T c3_i1283;
  real_T c3_b_A[9];
  real_T c3_b_B;
  int32_T c3_i1284;
  real_T c3_g_x[9];
  real_T c3_g_y;
  int32_T c3_i1285;
  real_T c3_h_x[9];
  real_T c3_h_y;
  int32_T c3_i1286;
  real_T c3_i_x[9];
  real_T c3_i_y;
  int32_T c3_i1287;
  real_T c3_j_y[9];
  real_T c3_f_a;
  real_T c3_c_b;
  real_T c3_k_y;
  real_T c3_j_x;
  real_T c3_k_x;
  real_T c3_l_x;
  int32_T c3_i1288;
  real_T c3_g_a[9];
  real_T c3_d_b;
  int32_T c3_i1289;
  real_T c3_l_y[9];
  real_T c3_dv154[9];
  int32_T c3_i1290;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c3_c_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_n, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_w, c3_h_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c3_theta, c3_f_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c3_R, c3_g_sf_marshall, 5U);
  CV_SCRIPT_FCN(2, 0);
  _SFD_SCRIPT_CALL(2, 2);
  for (c3_i1270 = 0; c3_i1270 < 3; c3_i1270 = c3_i1270 + 1) {
    c3_b_w[c3_i1270] = c3_w[c3_i1270];
  }

  c3_n = c3_norm(chartInstance, c3_b_w);
  _SFD_SCRIPT_CALL(2, 4);
  if (CV_SCRIPT_IF(2, 0, c3_n < 2.2204460492503131E-16)) {
    _SFD_SCRIPT_CALL(2, 5);
    c3_eye(chartInstance, c3_dv153);
    for (c3_i1271 = 0; c3_i1271 < 9; c3_i1271 = c3_i1271 + 1) {
      c3_R[c3_i1271] = c3_dv153[c3_i1271];
    }
  } else {
    /* theta = theta*n; */
    /* w = w/n; */
    _SFD_SCRIPT_CALL(2, 9);
    for (c3_i1272 = 0; c3_i1272 < 3; c3_i1272 = c3_i1272 + 1) {
      c3_c_w[c3_i1272] = c3_w[c3_i1272];
    }

    sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_b_debug_family_names,
      c3_b_debug_family_var_map);
    sf_debug_symbol_scope_add_eml(&c3_b_nargin, c3_f_sf_marshall, 0U);
    sf_debug_symbol_scope_add_eml(&c3_b_nargout, c3_f_sf_marshall, 1U);
    sf_debug_symbol_scope_add_eml(c3_c_w, c3_h_sf_marshall, 2U);
    sf_debug_symbol_scope_add_eml(c3_W, c3_g_sf_marshall, 3U);
    CV_SCRIPT_FCN(3, 0);
    _SFD_SCRIPT_CALL(3, 2);
    c3_W[0] = 0.0;
    c3_W[3] = -c3_c_w[2];
    c3_W[6] = c3_c_w[1];
    c3_W[1] = c3_c_w[2];
    c3_W[4] = 0.0;
    c3_W[7] = -c3_c_w[0];
    c3_W[2] = -c3_c_w[1];
    c3_W[5] = c3_c_w[0];
    c3_W[8] = 0.0;
    _SFD_SCRIPT_CALL(3, -2);
    sf_debug_symbol_scope_pop();
    for (c3_i1273 = 0; c3_i1273 < 9; c3_i1273 = c3_i1273 + 1) {
      c3_A[c3_i1273] = c3_W[c3_i1273];
    }

    c3_B = c3_n;
    for (c3_i1274 = 0; c3_i1274 < 9; c3_i1274 = c3_i1274 + 1) {
      c3_x[c3_i1274] = c3_A[c3_i1274];
    }

    c3_y = c3_B;
    for (c3_i1275 = 0; c3_i1275 < 9; c3_i1275 = c3_i1275 + 1) {
      c3_b_x[c3_i1275] = c3_x[c3_i1275];
    }

    c3_b_y = c3_y;
    for (c3_i1276 = 0; c3_i1276 < 9; c3_i1276 = c3_i1276 + 1) {
      c3_c_x[c3_i1276] = c3_b_x[c3_i1276];
    }

    c3_c_y = c3_b_y;
    for (c3_i1277 = 0; c3_i1277 < 9; c3_i1277 = c3_i1277 + 1) {
      c3_d_y[c3_i1277] = c3_c_x[c3_i1277] / c3_c_y;
    }

    c3_a = c3_n;
    c3_b = c3_theta;
    c3_e_y = c3_a * c3_b;
    c3_d_x = c3_e_y;
    c3_e_x = c3_d_x;
    c3_f_x = c3_e_x;
    c3_e_x = c3_f_x;
    c3_e_x = muDoubleScalarSin(c3_e_x);
    for (c3_i1278 = 0; c3_i1278 < 9; c3_i1278 = c3_i1278 + 1) {
      c3_b_a[c3_i1278] = c3_d_y[c3_i1278];
    }

    c3_b_b = c3_e_x;
    for (c3_i1279 = 0; c3_i1279 < 9; c3_i1279 = c3_i1279 + 1) {
      c3_f_y[c3_i1279] = c3_b_a[c3_i1279] * c3_b_b;
    }

    for (c3_i1280 = 0; c3_i1280 < 3; c3_i1280 = c3_i1280 + 1) {
      c3_d_w[c3_i1280] = c3_w[c3_i1280];
    }

    sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_b_debug_family_names,
      c3_c_debug_family_var_map);
    sf_debug_symbol_scope_add_eml(&c3_c_nargin, c3_f_sf_marshall, 0U);
    sf_debug_symbol_scope_add_eml(&c3_c_nargout, c3_f_sf_marshall, 1U);
    sf_debug_symbol_scope_add_eml(c3_d_w, c3_h_sf_marshall, 2U);
    sf_debug_symbol_scope_add_eml(c3_b_W, c3_g_sf_marshall, 3U);
    CV_SCRIPT_FCN(3, 0);
    _SFD_SCRIPT_CALL(3, 2);
    c3_b_W[0] = 0.0;
    c3_b_W[3] = -c3_d_w[2];
    c3_b_W[6] = c3_d_w[1];
    c3_b_W[1] = c3_d_w[2];
    c3_b_W[4] = 0.0;
    c3_b_W[7] = -c3_d_w[0];
    c3_b_W[2] = -c3_d_w[1];
    c3_b_W[5] = c3_d_w[0];
    c3_b_W[8] = 0.0;
    _SFD_SCRIPT_CALL(3, -2);
    sf_debug_symbol_scope_pop();
    for (c3_i1281 = 0; c3_i1281 < 9; c3_i1281 = c3_i1281 + 1) {
      c3_c_a[c3_i1281] = c3_b_W[c3_i1281];
    }

    for (c3_i1282 = 0; c3_i1282 < 9; c3_i1282 = c3_i1282 + 1) {
      c3_d_a[c3_i1282] = c3_c_a[c3_i1282];
    }

    c3_matrix_to_integer_power(chartInstance, c3_d_a, 2.0, c3_c);
    c3_e_a = c3_n;
    c3_b_c = c3_power(chartInstance, c3_e_a, 2.0);
    for (c3_i1283 = 0; c3_i1283 < 9; c3_i1283 = c3_i1283 + 1) {
      c3_b_A[c3_i1283] = c3_c[c3_i1283];
    }

    c3_b_B = c3_b_c;
    for (c3_i1284 = 0; c3_i1284 < 9; c3_i1284 = c3_i1284 + 1) {
      c3_g_x[c3_i1284] = c3_b_A[c3_i1284];
    }

    c3_g_y = c3_b_B;
    for (c3_i1285 = 0; c3_i1285 < 9; c3_i1285 = c3_i1285 + 1) {
      c3_h_x[c3_i1285] = c3_g_x[c3_i1285];
    }

    c3_h_y = c3_g_y;
    for (c3_i1286 = 0; c3_i1286 < 9; c3_i1286 = c3_i1286 + 1) {
      c3_i_x[c3_i1286] = c3_h_x[c3_i1286];
    }

    c3_i_y = c3_h_y;
    for (c3_i1287 = 0; c3_i1287 < 9; c3_i1287 = c3_i1287 + 1) {
      c3_j_y[c3_i1287] = c3_i_x[c3_i1287] / c3_i_y;
    }

    c3_f_a = c3_n;
    c3_c_b = c3_theta;
    c3_k_y = c3_f_a * c3_c_b;
    c3_j_x = c3_k_y;
    c3_k_x = c3_j_x;
    c3_l_x = c3_k_x;
    c3_k_x = c3_l_x;
    c3_k_x = muDoubleScalarCos(c3_k_x);
    for (c3_i1288 = 0; c3_i1288 < 9; c3_i1288 = c3_i1288 + 1) {
      c3_g_a[c3_i1288] = c3_j_y[c3_i1288];
    }

    c3_d_b = 1.0 - c3_k_x;
    for (c3_i1289 = 0; c3_i1289 < 9; c3_i1289 = c3_i1289 + 1) {
      c3_l_y[c3_i1289] = c3_g_a[c3_i1289] * c3_d_b;
    }

    c3_eye(chartInstance, c3_dv154);
    for (c3_i1290 = 0; c3_i1290 < 9; c3_i1290 = c3_i1290 + 1) {
      c3_R[c3_i1290] = (c3_dv154[c3_i1290] + c3_f_y[c3_i1290]) + c3_l_y[c3_i1290];
    }
  }

  _SFD_SCRIPT_CALL(2, -9);
  sf_debug_symbol_scope_pop();
}

static void c3_hat(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                   c3_w[3], real_T c3_W[9])
{
  uint32_T c3_debug_family_var_map[4];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_b_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_w, c3_h_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_W, c3_g_sf_marshall, 3U);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3, 2);
  c3_W[0] = 0.0;
  c3_W[3] = -c3_w[2];
  c3_W[6] = c3_w[1];
  c3_W[1] = c3_w[2];
  c3_W[4] = 0.0;
  c3_W[7] = -c3_w[0];
  c3_W[2] = -c3_w[1];
  c3_W[5] = c3_w[0];
  c3_W[8] = 0.0;
  _SFD_SCRIPT_CALL(3, -2);
  sf_debug_symbol_scope_pop();
}

static void c3_matrix_to_integer_power(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c3_a[9], real_T c3_b, real_T
  c3_c[9])
{
  real_T c3_x;
  real_T c3_e;
  boolean_T c3_firstmult;
  real_T c3_b_x;
  real_T c3_ed2;
  real_T c3_b_b;
  real_T c3_y;
  int32_T c3_i1291;
  int32_T c3_i1292;
  real_T c3_b_a[9];
  int32_T c3_i1293;
  real_T c3_c_b[9];
  int32_T c3_i1294;
  real_T c3_A[9];
  int32_T c3_i1295;
  real_T c3_B[9];
  int32_T c3_i1296;
  real_T c3_b_A[9];
  int32_T c3_i1297;
  real_T c3_b_B[9];
  int32_T c3_i1298;
  real_T c3_c_A[9];
  int32_T c3_i1299;
  real_T c3_c_B[9];
  int32_T c3_i1300;
  int32_T c3_i1301;
  int32_T c3_i1302;
  int32_T c3_i1303;
  int32_T c3_i1304;
  int32_T c3_i1305;
  real_T c3_c_x[9];
  int32_T c3_i1306;
  real_T c3_d_x[9];
  int32_T c3_i1307;
  real_T c3_e_x[9];
  int32_T c3_i1308;
  real_T c3_xinv[9];
  int32_T c3_i1309;
  real_T c3_f_x[9];
  real_T c3_n1x;
  int32_T c3_i1310;
  real_T c3_b_xinv[9];
  real_T c3_n1xinv;
  real_T c3_c_a;
  real_T c3_d_b;
  real_T c3_b_y;
  real_T c3_rc;
  real_T c3_g_x;
  boolean_T c3_e_b;
  int32_T c3_i1311;
  real_T c3_d_a[9];
  int32_T c3_i1312;
  real_T c3_f_b[9];
  int32_T c3_i1313;
  real_T c3_d_A[9];
  int32_T c3_i1314;
  real_T c3_d_B[9];
  int32_T c3_i1315;
  real_T c3_e_A[9];
  int32_T c3_i1316;
  real_T c3_e_B[9];
  int32_T c3_i1317;
  real_T c3_f_A[9];
  int32_T c3_i1318;
  real_T c3_f_B[9];
  int32_T c3_i1319;
  int32_T c3_i1320;
  int32_T c3_i1321;
  int32_T c3_i1322;
  int32_T c3_i1323;
  int32_T c3_i1324;
  int32_T c3_k;
  int32_T c3_b_k;
  c3_b_eml_scalar_eg(chartInstance);
  c3_x = c3_b;
  c3_e = muDoubleScalarAbs(c3_x);
  if (c3_e > 0.0) {
    c3_firstmult = TRUE;
   label_1:
    ;
    c3_b_x = c3_e / 2.0;
    c3_ed2 = c3_b_x;
    c3_ed2 = muDoubleScalarFloor(c3_ed2);
    c3_b_b = c3_ed2;
    c3_y = 2.0 * c3_b_b;
    if (c3_y != c3_e) {
      if (c3_firstmult) {
        for (c3_i1291 = 0; c3_i1291 < 9; c3_i1291 = c3_i1291 + 1) {
          c3_c[c3_i1291] = c3_a[c3_i1291];
        }

        c3_firstmult = FALSE;
      } else {
        for (c3_i1292 = 0; c3_i1292 < 9; c3_i1292 = c3_i1292 + 1) {
          c3_b_a[c3_i1292] = c3_c[c3_i1292];
        }

        for (c3_i1293 = 0; c3_i1293 < 9; c3_i1293 = c3_i1293 + 1) {
          c3_c_b[c3_i1293] = c3_a[c3_i1293];
        }

        c3_c_eml_scalar_eg(chartInstance);
        c3_c_eml_scalar_eg(chartInstance);
        for (c3_i1294 = 0; c3_i1294 < 9; c3_i1294 = c3_i1294 + 1) {
          c3_A[c3_i1294] = c3_b_a[c3_i1294];
        }

        for (c3_i1295 = 0; c3_i1295 < 9; c3_i1295 = c3_i1295 + 1) {
          c3_B[c3_i1295] = c3_c_b[c3_i1295];
        }

        for (c3_i1296 = 0; c3_i1296 < 9; c3_i1296 = c3_i1296 + 1) {
          c3_b_A[c3_i1296] = c3_A[c3_i1296];
        }

        for (c3_i1297 = 0; c3_i1297 < 9; c3_i1297 = c3_i1297 + 1) {
          c3_b_B[c3_i1297] = c3_B[c3_i1297];
        }

        for (c3_i1298 = 0; c3_i1298 < 9; c3_i1298 = c3_i1298 + 1) {
          c3_c_A[c3_i1298] = c3_b_A[c3_i1298];
        }

        for (c3_i1299 = 0; c3_i1299 < 9; c3_i1299 = c3_i1299 + 1) {
          c3_c_B[c3_i1299] = c3_b_B[c3_i1299];
        }

        for (c3_i1300 = 0; c3_i1300 < 3; c3_i1300 = c3_i1300 + 1) {
          c3_i1301 = 0;
          for (c3_i1302 = 0; c3_i1302 < 3; c3_i1302 = c3_i1302 + 1) {
            c3_c[c3_i1301 + c3_i1300] = 0.0;
            c3_i1303 = 0;
            for (c3_i1304 = 0; c3_i1304 < 3; c3_i1304 = c3_i1304 + 1) {
              c3_c[c3_i1301 + c3_i1300] = c3_c[c3_i1301 + c3_i1300] +
                c3_c_A[c3_i1303 + c3_i1300] * c3_c_B[c3_i1304 + c3_i1301];
              c3_i1303 = c3_i1303 + 3;
            }

            c3_i1301 = c3_i1301 + 3;
          }
        }
      }
    }

    if (c3_ed2 == 0.0) {
    } else {
      c3_e = c3_ed2;
      for (c3_i1311 = 0; c3_i1311 < 9; c3_i1311 = c3_i1311 + 1) {
        c3_d_a[c3_i1311] = c3_a[c3_i1311];
      }

      for (c3_i1312 = 0; c3_i1312 < 9; c3_i1312 = c3_i1312 + 1) {
        c3_f_b[c3_i1312] = c3_a[c3_i1312];
      }

      c3_c_eml_scalar_eg(chartInstance);
      c3_c_eml_scalar_eg(chartInstance);
      for (c3_i1313 = 0; c3_i1313 < 9; c3_i1313 = c3_i1313 + 1) {
        c3_d_A[c3_i1313] = c3_d_a[c3_i1313];
      }

      for (c3_i1314 = 0; c3_i1314 < 9; c3_i1314 = c3_i1314 + 1) {
        c3_d_B[c3_i1314] = c3_f_b[c3_i1314];
      }

      for (c3_i1315 = 0; c3_i1315 < 9; c3_i1315 = c3_i1315 + 1) {
        c3_e_A[c3_i1315] = c3_d_A[c3_i1315];
      }

      for (c3_i1316 = 0; c3_i1316 < 9; c3_i1316 = c3_i1316 + 1) {
        c3_e_B[c3_i1316] = c3_d_B[c3_i1316];
      }

      for (c3_i1317 = 0; c3_i1317 < 9; c3_i1317 = c3_i1317 + 1) {
        c3_f_A[c3_i1317] = c3_e_A[c3_i1317];
      }

      for (c3_i1318 = 0; c3_i1318 < 9; c3_i1318 = c3_i1318 + 1) {
        c3_f_B[c3_i1318] = c3_e_B[c3_i1318];
      }

      for (c3_i1319 = 0; c3_i1319 < 3; c3_i1319 = c3_i1319 + 1) {
        c3_i1320 = 0;
        for (c3_i1321 = 0; c3_i1321 < 3; c3_i1321 = c3_i1321 + 1) {
          c3_a[c3_i1320 + c3_i1319] = 0.0;
          c3_i1322 = 0;
          for (c3_i1323 = 0; c3_i1323 < 3; c3_i1323 = c3_i1323 + 1) {
            c3_a[c3_i1320 + c3_i1319] = c3_a[c3_i1320 + c3_i1319] +
              c3_f_A[c3_i1322 + c3_i1319] * c3_f_B[c3_i1323 + c3_i1320];
            c3_i1322 = c3_i1322 + 3;
          }

          c3_i1320 = c3_i1320 + 3;
        }
      }

      goto label_1;
    }

    if (c3_b < 0.0) {
      for (c3_i1305 = 0; c3_i1305 < 9; c3_i1305 = c3_i1305 + 1) {
        c3_c_x[c3_i1305] = c3_c[c3_i1305];
      }

      for (c3_i1306 = 0; c3_i1306 < 9; c3_i1306 = c3_i1306 + 1) {
        c3_d_x[c3_i1306] = c3_c_x[c3_i1306];
      }

      c3_inv3x3(chartInstance, c3_d_x, c3_c);
      for (c3_i1307 = 0; c3_i1307 < 9; c3_i1307 = c3_i1307 + 1) {
        c3_e_x[c3_i1307] = c3_c_x[c3_i1307];
      }

      for (c3_i1308 = 0; c3_i1308 < 9; c3_i1308 = c3_i1308 + 1) {
        c3_xinv[c3_i1308] = c3_c[c3_i1308];
      }

      for (c3_i1309 = 0; c3_i1309 < 9; c3_i1309 = c3_i1309 + 1) {
        c3_f_x[c3_i1309] = c3_e_x[c3_i1309];
      }

      c3_n1x = c3_b_norm(chartInstance, c3_f_x);
      for (c3_i1310 = 0; c3_i1310 < 9; c3_i1310 = c3_i1310 + 1) {
        c3_b_xinv[c3_i1310] = c3_xinv[c3_i1310];
      }

      c3_n1xinv = c3_b_norm(chartInstance, c3_b_xinv);
      c3_c_a = c3_n1x;
      c3_d_b = c3_n1xinv;
      c3_b_y = c3_c_a * c3_d_b;
      c3_rc = 1.0 / c3_b_y;
      if (c3_n1x == 0.0) {
      } else if (c3_n1xinv == 0.0) {
      } else if (c3_rc == 0.0) {
        goto label_2;
      } else {
        c3_g_x = c3_rc;
        c3_e_b = muDoubleScalarIsNaN(c3_g_x);
        if (c3_e_b) {
        } else if (c3_rc < 2.2204460492503131E-16) {
        } else {
          return;
        }

        c3_b_eml_warning(chartInstance, c3_rc);
        return;
      }

     label_2:
      ;
      c3_eml_warning(chartInstance);
    }
  } else {
    for (c3_i1324 = 0; c3_i1324 < 9; c3_i1324 = c3_i1324 + 1) {
      c3_c[c3_i1324] = 0.0;
    }

    for (c3_k = 1; c3_k < 4; c3_k = c3_k + 1) {
      c3_b_k = c3_k;
      c3_c[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c3_b_k), 1, 3, 1, 0) - 1) + 3 * (
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
        c3_b_k), 1, 3, 2, 0) - 1)] = 1.0;
    }
  }
}

static void c3_b_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_c_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_inv3x3(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
                      real_T c3_x[9], real_T c3_y[9])
{
  int32_T c3_p1;
  int32_T c3_p2;
  int32_T c3_p3;
  real_T c3_b_x;
  real_T c3_c_x;
  real_T c3_absx11;
  real_T c3_d_x;
  real_T c3_e_x;
  real_T c3_absx21;
  real_T c3_f_x;
  real_T c3_g_x;
  real_T c3_absx31;
  real_T c3_t1;
  real_T c3_h_x;
  real_T c3_b_y;
  real_T c3_i_x;
  real_T c3_c_y;
  real_T c3_z;
  real_T c3_j_x;
  real_T c3_d_y;
  real_T c3_k_x;
  real_T c3_e_y;
  real_T c3_b_z;
  real_T c3_a;
  real_T c3_b;
  real_T c3_f_y;
  real_T c3_b_a;
  real_T c3_b_b;
  real_T c3_g_y;
  real_T c3_c_a;
  real_T c3_c_b;
  real_T c3_h_y;
  real_T c3_d_a;
  real_T c3_d_b;
  real_T c3_i_y;
  real_T c3_l_x;
  real_T c3_m_x;
  real_T c3_j_y;
  real_T c3_n_x;
  real_T c3_o_x;
  real_T c3_k_y;
  int32_T c3_itmp;
  real_T c3_p_x;
  real_T c3_l_y;
  real_T c3_q_x;
  real_T c3_m_y;
  real_T c3_c_z;
  real_T c3_e_a;
  real_T c3_e_b;
  real_T c3_n_y;
  real_T c3_f_a;
  real_T c3_f_b;
  real_T c3_o_y;
  real_T c3_r_x;
  real_T c3_p_y;
  real_T c3_s_x;
  real_T c3_q_y;
  real_T c3_t3;
  real_T c3_g_a;
  real_T c3_g_b;
  real_T c3_r_y;
  real_T c3_t_x;
  real_T c3_s_y;
  real_T c3_u_x;
  real_T c3_t_y;
  real_T c3_t2;
  int32_T c3_h_a;
  int32_T c3_c;
  real_T c3_i_a;
  real_T c3_h_b;
  real_T c3_u_y;
  real_T c3_j_a;
  real_T c3_i_b;
  real_T c3_v_y;
  real_T c3_v_x;
  real_T c3_w_y;
  real_T c3_w_x;
  real_T c3_x_y;
  real_T c3_d_z;
  int32_T c3_k_a;
  int32_T c3_b_c;
  int32_T c3_l_a;
  int32_T c3_c_c;
  real_T c3_x_x;
  real_T c3_y_y;
  real_T c3_y_x;
  real_T c3_ab_y;
  real_T c3_m_a;
  real_T c3_j_b;
  real_T c3_bb_y;
  real_T c3_ab_x;
  real_T c3_cb_y;
  real_T c3_bb_x;
  real_T c3_db_y;
  int32_T c3_n_a;
  int32_T c3_d_c;
  real_T c3_o_a;
  real_T c3_k_b;
  real_T c3_eb_y;
  real_T c3_p_a;
  real_T c3_l_b;
  real_T c3_fb_y;
  real_T c3_cb_x;
  real_T c3_gb_y;
  real_T c3_db_x;
  real_T c3_hb_y;
  real_T c3_e_z;
  int32_T c3_q_a;
  int32_T c3_e_c;
  int32_T c3_r_a;
  int32_T c3_f_c;
  real_T c3_ib_y;
  real_T c3_jb_y;
  real_T c3_s_a;
  real_T c3_m_b;
  real_T c3_kb_y;
  real_T c3_eb_x;
  real_T c3_lb_y;
  real_T c3_fb_x;
  real_T c3_mb_y;
  int32_T c3_t_a;
  int32_T c3_g_c;
  real_T c3_u_a;
  real_T c3_n_b;
  real_T c3_nb_y;
  real_T c3_v_a;
  real_T c3_o_b;
  real_T c3_ob_y;
  real_T c3_gb_x;
  real_T c3_pb_y;
  real_T c3_hb_x;
  real_T c3_qb_y;
  real_T c3_f_z;
  int32_T c3_w_a;
  int32_T c3_h_c;
  int32_T c3_x_a;
  int32_T c3_i_c;
  c3_p1 = 0;
  c3_p2 = 3;
  c3_p3 = 6;
  c3_b_x = c3_x[0];
  c3_c_x = c3_b_x;
  c3_absx11 = muDoubleScalarAbs(c3_c_x);
  c3_d_x = c3_x[1];
  c3_e_x = c3_d_x;
  c3_absx21 = muDoubleScalarAbs(c3_e_x);
  c3_f_x = c3_x[2];
  c3_g_x = c3_f_x;
  c3_absx31 = muDoubleScalarAbs(c3_g_x);
  if (c3_absx21 > c3_absx11) {
    if (c3_absx21 > c3_absx31) {
      c3_p1 = 3;
      c3_p2 = 0;
      c3_t1 = c3_x[0];
      c3_x[0] = c3_x[1];
      c3_x[1] = c3_t1;
      c3_t1 = c3_x[3];
      c3_x[3] = c3_x[4];
      c3_x[4] = c3_t1;
      c3_t1 = c3_x[6];
      c3_x[6] = c3_x[7];
      c3_x[7] = c3_t1;
      goto label_1;
    }
  }

  if (c3_absx31 > c3_absx11) {
    c3_p1 = 6;
    c3_p3 = 0;
    c3_t1 = c3_x[0];
    c3_x[0] = c3_x[2];
    c3_x[2] = c3_t1;
    c3_t1 = c3_x[3];
    c3_x[3] = c3_x[5];
    c3_x[5] = c3_t1;
    c3_t1 = c3_x[6];
    c3_x[6] = c3_x[8];
    c3_x[8] = c3_t1;
  }

 label_1:
  ;
  c3_h_x = c3_x[1];
  c3_b_y = c3_x[0];
  c3_i_x = c3_h_x;
  c3_c_y = c3_b_y;
  c3_z = c3_i_x / c3_c_y;
  c3_x[1] = c3_z;
  c3_j_x = c3_x[2];
  c3_d_y = c3_x[0];
  c3_k_x = c3_j_x;
  c3_e_y = c3_d_y;
  c3_b_z = c3_k_x / c3_e_y;
  c3_x[2] = c3_b_z;
  c3_a = c3_x[1];
  c3_b = c3_x[3];
  c3_f_y = c3_a * c3_b;
  c3_x[4] = c3_x[4] - c3_f_y;
  c3_b_a = c3_x[2];
  c3_b_b = c3_x[3];
  c3_g_y = c3_b_a * c3_b_b;
  c3_x[5] = c3_x[5] - c3_g_y;
  c3_c_a = c3_x[1];
  c3_c_b = c3_x[6];
  c3_h_y = c3_c_a * c3_c_b;
  c3_x[7] = c3_x[7] - c3_h_y;
  c3_d_a = c3_x[2];
  c3_d_b = c3_x[6];
  c3_i_y = c3_d_a * c3_d_b;
  c3_x[8] = c3_x[8] - c3_i_y;
  c3_l_x = c3_x[5];
  c3_m_x = c3_l_x;
  c3_j_y = muDoubleScalarAbs(c3_m_x);
  c3_n_x = c3_x[4];
  c3_o_x = c3_n_x;
  c3_k_y = muDoubleScalarAbs(c3_o_x);
  if (c3_j_y > c3_k_y) {
    c3_itmp = c3_p2;
    c3_p2 = c3_p3;
    c3_p3 = c3_itmp;
    c3_t1 = c3_x[1];
    c3_x[1] = c3_x[2];
    c3_x[2] = c3_t1;
    c3_t1 = c3_x[4];
    c3_x[4] = c3_x[5];
    c3_x[5] = c3_t1;
    c3_t1 = c3_x[7];
    c3_x[7] = c3_x[8];
    c3_x[8] = c3_t1;
  }

  c3_p_x = c3_x[5];
  c3_l_y = c3_x[4];
  c3_q_x = c3_p_x;
  c3_m_y = c3_l_y;
  c3_c_z = c3_q_x / c3_m_y;
  c3_x[5] = c3_c_z;
  c3_e_a = c3_x[5];
  c3_e_b = c3_x[7];
  c3_n_y = c3_e_a * c3_e_b;
  c3_x[8] = c3_x[8] - c3_n_y;
  c3_f_a = c3_x[5];
  c3_f_b = c3_x[1];
  c3_o_y = c3_f_a * c3_f_b;
  c3_r_x = c3_o_y - c3_x[2];
  c3_p_y = c3_x[8];
  c3_s_x = c3_r_x;
  c3_q_y = c3_p_y;
  c3_t3 = c3_s_x / c3_q_y;
  c3_g_a = c3_x[7];
  c3_g_b = c3_t3;
  c3_r_y = c3_g_a * c3_g_b;
  c3_t_x = -(c3_x[1] + c3_r_y);
  c3_s_y = c3_x[4];
  c3_u_x = c3_t_x;
  c3_t_y = c3_s_y;
  c3_t2 = c3_u_x / c3_t_y;
  c3_h_a = c3_p1;
  c3_c = c3_h_a + 1;
  c3_i_a = c3_x[3];
  c3_h_b = c3_t2;
  c3_u_y = c3_i_a * c3_h_b;
  c3_j_a = c3_x[6];
  c3_i_b = c3_t3;
  c3_v_y = c3_j_a * c3_i_b;
  c3_v_x = (1.0 - c3_u_y) - c3_v_y;
  c3_w_y = c3_x[0];
  c3_w_x = c3_v_x;
  c3_x_y = c3_w_y;
  c3_d_z = c3_w_x / c3_x_y;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_c), 1, 9, 1, 0) - 1] = c3_d_z;
  c3_k_a = c3_p1;
  c3_b_c = c3_k_a + 2;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_b_c), 1, 9, 1, 0) - 1] = c3_t2;
  c3_l_a = c3_p1;
  c3_c_c = c3_l_a + 3;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_c_c), 1, 9, 1, 0) - 1] = c3_t3;
  c3_x_x = -c3_x[5];
  c3_y_y = c3_x[8];
  c3_y_x = c3_x_x;
  c3_ab_y = c3_y_y;
  c3_t3 = c3_y_x / c3_ab_y;
  c3_m_a = c3_x[7];
  c3_j_b = c3_t3;
  c3_bb_y = c3_m_a * c3_j_b;
  c3_ab_x = 1.0 - c3_bb_y;
  c3_cb_y = c3_x[4];
  c3_bb_x = c3_ab_x;
  c3_db_y = c3_cb_y;
  c3_t2 = c3_bb_x / c3_db_y;
  c3_n_a = c3_p2;
  c3_d_c = c3_n_a + 1;
  c3_o_a = c3_x[3];
  c3_k_b = c3_t2;
  c3_eb_y = c3_o_a * c3_k_b;
  c3_p_a = c3_x[6];
  c3_l_b = c3_t3;
  c3_fb_y = c3_p_a * c3_l_b;
  c3_cb_x = -(c3_eb_y + c3_fb_y);
  c3_gb_y = c3_x[0];
  c3_db_x = c3_cb_x;
  c3_hb_y = c3_gb_y;
  c3_e_z = c3_db_x / c3_hb_y;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_d_c), 1, 9, 1, 0) - 1] = c3_e_z;
  c3_q_a = c3_p2;
  c3_e_c = c3_q_a + 2;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_e_c), 1, 9, 1, 0) - 1] = c3_t2;
  c3_r_a = c3_p2;
  c3_f_c = c3_r_a + 3;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_f_c), 1, 9, 1, 0) - 1] = c3_t3;
  c3_ib_y = c3_x[8];
  c3_jb_y = c3_ib_y;
  c3_t3 = 1.0 / c3_jb_y;
  c3_s_a = -c3_x[7];
  c3_m_b = c3_t3;
  c3_kb_y = c3_s_a * c3_m_b;
  c3_eb_x = c3_kb_y;
  c3_lb_y = c3_x[4];
  c3_fb_x = c3_eb_x;
  c3_mb_y = c3_lb_y;
  c3_t2 = c3_fb_x / c3_mb_y;
  c3_t_a = c3_p3;
  c3_g_c = c3_t_a + 1;
  c3_u_a = c3_x[3];
  c3_n_b = c3_t2;
  c3_nb_y = c3_u_a * c3_n_b;
  c3_v_a = c3_x[6];
  c3_o_b = c3_t3;
  c3_ob_y = c3_v_a * c3_o_b;
  c3_gb_x = -(c3_nb_y + c3_ob_y);
  c3_pb_y = c3_x[0];
  c3_hb_x = c3_gb_x;
  c3_qb_y = c3_pb_y;
  c3_f_z = c3_hb_x / c3_qb_y;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_g_c), 1, 9, 1, 0) - 1] = c3_f_z;
  c3_w_a = c3_p3;
  c3_h_c = c3_w_a + 2;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_h_c), 1, 9, 1, 0) - 1] = c3_t2;
  c3_x_a = c3_p3;
  c3_i_c = c3_x_a + 3;
  c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c3_i_c), 1, 9, 1, 0) - 1] = c3_t3;
}

static real_T c3_b_norm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_x[9])
{
  real_T c3_y;
  int32_T c3_i1325;
  real_T c3_b_x[9];
  real_T c3_j;
  real_T c3_b_j;
  real_T c3_s;
  real_T c3_i;
  real_T c3_b_i;
  real_T c3_c_x;
  real_T c3_d_x;
  real_T c3_b_y;
  real_T c3_e_x;
  boolean_T c3_b;
  for (c3_i1325 = 0; c3_i1325 < 9; c3_i1325 = c3_i1325 + 1) {
    c3_b_x[c3_i1325] = c3_x[c3_i1325];
  }

  c3_y = 0.0;
  c3_j = 1.0;
 label_1:
  ;
  if (c3_j <= 3.0) {
    c3_b_j = c3_j;
    c3_s = 0.0;
    for (c3_i = 1.0; c3_i <= 3.0; c3_i = c3_i + 1.0) {
      c3_b_i = c3_i;
      c3_c_x = c3_b_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c3_b_i), 1, 3, 1, 0) - 1) + 3 * (
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c3_b_j),
        1, 3, 2, 0) - 1)];
      c3_d_x = c3_c_x;
      c3_b_y = muDoubleScalarAbs(c3_d_x);
      c3_s = c3_s + c3_b_y;
    }

    c3_e_x = c3_s;
    c3_b = muDoubleScalarIsNaN(c3_e_x);
    if (c3_b) {
      return rtNaN;
    } else {
      if (c3_s > c3_y) {
        c3_y = c3_s;
      }

      c3_j = c3_j + 1.0;
      goto label_1;
    }
  }

  return c3_y;
}

static void c3_eml_warning(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  int32_T c3_i1326;
  static char_T c3_cv0[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 's', 'i', 'n',
    'g', 'u', 'l', 'a', 'r', 'M', 'a', 't', 'r', 'i', 'x'
  };

  char_T c3_u[21];
  const mxArray *c3_y = NULL;
  int32_T c3_i1327;
  static char_T c3_cv1[40] = { 'M', 'a', 't', 'r', 'i', 'x', ' ', 'i', 's', ' ',
    's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', ' ', 't', 'o'
    , ' ', 'w', 'o', 'r', 'k', 'i', 'n', 'g', ' ', 'p', 'r', 'e', 'c', 'i', 's',
    'i', 'o', 'n', '.' };

  char_T c3_b_u[40];
  const mxArray *c3_b_y = NULL;
  for (c3_i1326 = 0; c3_i1326 < 21; c3_i1326 = c3_i1326 + 1) {
    c3_u[c3_i1326] = c3_cv0[c3_i1326];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 21));
  for (c3_i1327 = 0; c3_i1327 < 40; c3_i1327 = c3_i1327 + 1) {
    c3_b_u[c3_i1327] = c3_cv1[c3_i1327];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
  sf_mex_call_debug("warning", 0U, 2U, 14, c3_y, 14, c3_b_y);
}

static void c3_b_eps(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
}

static void c3_b_eml_warning(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c3_varargin_3)
{
  int32_T c3_i1328;
  static char_T c3_cv2[27] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'l', 'l',
    'C', 'o', 'n', 'd', 'i', 't', 'i', 'o', 'n', 'e', 'd'
    , 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c3_u[27];
  const mxArray *c3_y = NULL;
  int32_T c3_i1329;
  static char_T c3_cv3[103] = { 'M', 'a', 't', 'r', 'i', 'x', ' ', 'i', 's', ' ',
    's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', ',', ' ',
    'c', 'l', 'o', 's', 'e', ' ', 't', 'o', ' ', 's', 'i', 'n', 'g', 'u', 'l',
    'a', 'r', ' ', 'o', 'r',
    ' ', 'b', 'a', 'd', 'l', 'y', ' ', 's', 'c', 'a', 'l', 'e', 'd', '.', '\\',
    'n', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', 'R', 'e', 's', 'u', 'l', 't', 's', ' ', 'm', 'a',
    'y', ' ', 'b', 'e', ' ',
    'i', 'n', 'a', 'c', 'c', 'u', 'r', 'a', 't', 'e', '.', ' ', 'R', 'C', 'O',
    'N', 'D', ' ', '=', ' ',
    '%', 'e', '.' };

  char_T c3_b_u[103];
  const mxArray *c3_b_y = NULL;
  real_T c3_c_u;
  const mxArray *c3_c_y = NULL;
  for (c3_i1328 = 0; c3_i1328 < 27; c3_i1328 = c3_i1328 + 1) {
    c3_u[c3_i1328] = c3_cv2[c3_i1328];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 27));
  for (c3_i1329 = 0; c3_i1329 < 103; c3_i1329 = c3_i1329 + 1) {
    c3_b_u[c3_i1329] = c3_cv3[c3_i1329];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 103));
  c3_c_u = c3_varargin_3;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_c_u, 0, 0U, 0U, 0U, 0));
  sf_mex_call_debug("warning", 0U, 3U, 14, c3_y, 14, c3_b_y, 14, c3_c_y);
}

static real_T c3_power(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_a, real_T c3_b)
{
  real_T c3_ak;
  real_T c3_bk;
  real_T c3_x;
  real_T c3_b_x;
  c3_eml_scalar_eg(chartInstance);
  c3_ak = c3_a;
  c3_bk = c3_b;
  if (c3_ak < 0.0) {
    c3_x = c3_bk;
    c3_b_x = c3_x;
    c3_b_x = muDoubleScalarFloor(c3_b_x);
    if (c3_b_x != c3_bk) {
      c3_eml_error(chartInstance);
      goto label_1;
    }
  }

 label_1:
  ;
  return muDoubleScalarPower(c3_ak, c3_bk);
}

static void c3_eml_error(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance)
{
  int32_T c3_i1330;
  static char_T c3_cv4[32] = { 'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'p', 'o', 'w', 'e', 'r', ':'
    , 'd', 'o', 'm', 'a', 'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c3_u[32];
  const mxArray *c3_y = NULL;
  int32_T c3_i1331;
  static char_T c3_cv5[102] = { 'D', 'o', 'm', 'a', 'i', 'n', ' ', 'e', 'r', 'r',
    'o', 'r', '.', ' ', 'T', 'o', ' ', 'c', 'o', 'm',
    'p', 'u', 't', 'e', ' ', 'c', 'o', 'm', 'p', 'l', 'e', 'x', ' ', 'r', 'e',
    's', 'u', 'l', 't', 's',
    ',', ' ', 'm', 'a', 'k', 'e', ' ', 'a', 't', ' ', 'l', 'e', 'a', 's', 't',
    ' ', 'o', 'n', 'e', ' ',
    'i', 'n', 'p', 'u', 't', ' ', 'c', 'o', 'm', 'p', 'l', 'e', 'x', ',', ' ',
    'e', '.', 'g', '.', ' ',
    '\'', 'p', 'o', 'w', 'e', 'r', '(', 'c', 'o', 'm', 'p', 'l', 'e', 'x', '(',
    'a', ')', ',', 'b', ')',
    '\'', '.' };

  char_T c3_b_u[102];
  const mxArray *c3_b_y = NULL;
  for (c3_i1330 = 0; c3_i1330 < 32; c3_i1330 = c3_i1330 + 1) {
    c3_u[c3_i1330] = c3_cv4[c3_i1330];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 32));
  for (c3_i1331 = 0; c3_i1331 < 102; c3_i1331 = c3_i1331 + 1) {
    c3_b_u[c3_i1331] = c3_cv5[c3_i1331];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 102));
  sf_mex_call_debug("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
}

static void c3_d_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_e_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_mldivide(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[4], real_T c3_Y[4])
{
  int32_T c3_i1332;
  real_T c3_b_A[16];
  int32_T c3_i1333;
  real_T c3_b_B[4];
  int32_T c3_i1334;
  real_T c3_c_A[16];
  int32_T c3_i1335;
  real_T c3_c_B[4];
  int32_T c3_i1336;
  real_T c3_d_A[16];
  int32_T c3_i1337;
  real_T c3_e_A[16];
  int32_T c3_i1338;
  real_T c3_f_A[16];
  int32_T c3_i1339;
  real_T c3_g_A[16];
  int32_T c3_i1340;
  real_T c3_h_A[16];
  int32_T c3_info;
  int32_T c3_ipiv[4];
  real_T c3_i_A[16];
  int32_T c3_i1341;
  int32_T c3_i1342;
  int32_T c3_b_ipiv[4];
  int32_T c3_b_info;
  int32_T c3_i1343;
  int32_T c3_i1344;
  int32_T c3_c_ipiv[4];
  int32_T c3_c_info;
  int32_T c3_i1345;
  int32_T c3_i1346;
  int32_T c3_d_ipiv[4];
  int32_T c3_d_info;
  int32_T c3_i1347;
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_ip;
  real_T c3_temp;
  int32_T c3_i1348;
  real_T c3_j_A[16];
  int32_T c3_i1349;
  real_T c3_b_Y[4];
  int32_T c3_i1350;
  real_T c3_k_A[16];
  int32_T c3_i1351;
  real_T c3_d_B[4];
  int32_T c3_i1352;
  int32_T c3_i1353;
  real_T c3_l_A[16];
  int32_T c3_i1354;
  real_T c3_c_Y[4];
  for (c3_i1332 = 0; c3_i1332 < 16; c3_i1332 = c3_i1332 + 1) {
    c3_b_A[c3_i1332] = c3_A[c3_i1332];
  }

  for (c3_i1333 = 0; c3_i1333 < 4; c3_i1333 = c3_i1333 + 1) {
    c3_b_B[c3_i1333] = c3_B[c3_i1333];
  }

  for (c3_i1334 = 0; c3_i1334 < 16; c3_i1334 = c3_i1334 + 1) {
    c3_c_A[c3_i1334] = c3_b_A[c3_i1334];
  }

  for (c3_i1335 = 0; c3_i1335 < 4; c3_i1335 = c3_i1335 + 1) {
    c3_c_B[c3_i1335] = c3_b_B[c3_i1335];
  }

  for (c3_i1336 = 0; c3_i1336 < 16; c3_i1336 = c3_i1336 + 1) {
    c3_d_A[c3_i1336] = c3_c_A[c3_i1336];
  }

  for (c3_i1337 = 0; c3_i1337 < 16; c3_i1337 = c3_i1337 + 1) {
    c3_e_A[c3_i1337] = c3_d_A[c3_i1337];
  }

  for (c3_i1338 = 0; c3_i1338 < 16; c3_i1338 = c3_i1338 + 1) {
    c3_f_A[c3_i1338] = c3_e_A[c3_i1338];
  }

  for (c3_i1339 = 0; c3_i1339 < 16; c3_i1339 = c3_i1339 + 1) {
    c3_g_A[c3_i1339] = c3_f_A[c3_i1339];
  }

  for (c3_i1340 = 0; c3_i1340 < 16; c3_i1340 = c3_i1340 + 1) {
    c3_h_A[c3_i1340] = c3_g_A[c3_i1340];
  }

  c3_eml_matlab_zgetrf(chartInstance, c3_h_A, c3_i_A, c3_ipiv, &c3_info);
  for (c3_i1341 = 0; c3_i1341 < 16; c3_i1341 = c3_i1341 + 1) {
    c3_g_A[c3_i1341] = c3_i_A[c3_i1341];
  }

  for (c3_i1342 = 0; c3_i1342 < 4; c3_i1342 = c3_i1342 + 1) {
    c3_b_ipiv[c3_i1342] = c3_ipiv[c3_i1342];
  }

  c3_b_info = c3_info;
  for (c3_i1343 = 0; c3_i1343 < 16; c3_i1343 = c3_i1343 + 1) {
    c3_e_A[c3_i1343] = c3_g_A[c3_i1343];
  }

  for (c3_i1344 = 0; c3_i1344 < 4; c3_i1344 = c3_i1344 + 1) {
    c3_c_ipiv[c3_i1344] = c3_b_ipiv[c3_i1344];
  }

  c3_c_info = c3_b_info;
  for (c3_i1345 = 0; c3_i1345 < 16; c3_i1345 = c3_i1345 + 1) {
    c3_c_A[c3_i1345] = c3_e_A[c3_i1345];
  }

  for (c3_i1346 = 0; c3_i1346 < 4; c3_i1346 = c3_i1346 + 1) {
    c3_d_ipiv[c3_i1346] = c3_c_ipiv[c3_i1346];
  }

  c3_d_info = c3_c_info;
  if ((real_T)c3_d_info > 0.0) {
    c3_eml_warning(chartInstance);
  }

  for (c3_i1347 = 0; c3_i1347 < 4; c3_i1347 = c3_i1347 + 1) {
    c3_Y[c3_i1347] = c3_c_B[c3_i1347];
  }

  for (c3_i = 1; c3_i < 5; c3_i = c3_i + 1) {
    c3_b_i = c3_i;
    if (c3_d_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_i), 1, 4, 1, 0) - 1] != c3_b_i) {
      c3_ip = c3_d_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c3_b_i), 1, 4, 1, 0) - 1];
      c3_temp = c3_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", (real_T)c3_b_i), 1, 4, 1, 0) - 1];
      c3_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c3_b_i), 1, 4, 1, 0) - 1] = c3_Y[
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
        c3_ip), 1, 4, 1, 0) - 1];
      c3_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c3_ip), 1, 4, 1, 0) - 1] = c3_temp;
    }
  }

  for (c3_i1348 = 0; c3_i1348 < 16; c3_i1348 = c3_i1348 + 1) {
    c3_j_A[c3_i1348] = c3_c_A[c3_i1348];
  }

  for (c3_i1349 = 0; c3_i1349 < 4; c3_i1349 = c3_i1349 + 1) {
    c3_b_Y[c3_i1349] = c3_Y[c3_i1349];
  }

  c3_eml_xtrsm(chartInstance, c3_j_A, c3_b_Y, c3_Y);
  for (c3_i1350 = 0; c3_i1350 < 16; c3_i1350 = c3_i1350 + 1) {
    c3_k_A[c3_i1350] = c3_c_A[c3_i1350];
  }

  for (c3_i1351 = 0; c3_i1351 < 4; c3_i1351 = c3_i1351 + 1) {
    c3_d_B[c3_i1351] = c3_Y[c3_i1351];
  }

  for (c3_i1352 = 0; c3_i1352 < 4; c3_i1352 = c3_i1352 + 1) {
    c3_Y[c3_i1352] = c3_d_B[c3_i1352];
  }

  for (c3_i1353 = 0; c3_i1353 < 16; c3_i1353 = c3_i1353 + 1) {
    c3_l_A[c3_i1353] = c3_k_A[c3_i1353];
  }

  for (c3_i1354 = 0; c3_i1354 < 4; c3_i1354 = c3_i1354 + 1) {
    c3_c_Y[c3_i1354] = c3_Y[c3_i1354];
  }

  c3_eml_blas_xtrsm(chartInstance, 4, 1, 1.0, c3_l_A, 1, 4, c3_c_Y, 1, 4, c3_Y);
}

static void c3_eml_matlab_zgetrf(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, real_T c3_A[16], real_T c3_b_A[16], int32_T
  c3_ipiv[4], int32_T *c3_info)
{
  int32_T c3_i1355;
  int32_T c3_i1356;
  int32_T c3_j;
  int32_T c3_b_j;
  int32_T c3_a;
  int32_T c3_jm1;
  int32_T c3_b;
  int32_T c3_mmj;
  int32_T c3_b_a;
  int32_T c3_c;
  int32_T c3_b_b;
  int32_T c3_jj;
  int32_T c3_c_a;
  int32_T c3_jp1j;
  int32_T c3_d_a;
  int32_T c3_b_c;
  int32_T c3_i1357;
  real_T c3_c_A[16];
  int32_T c3_e_a;
  int32_T c3_jpiv_offset;
  int32_T c3_f_a;
  int32_T c3_c_b;
  int32_T c3_jpiv;
  int32_T c3_g_a;
  int32_T c3_d_b;
  int32_T c3_c_c;
  int32_T c3_e_b;
  int32_T c3_jrow;
  int32_T c3_h_a;
  int32_T c3_f_b;
  int32_T c3_jprow;
  int32_T c3_i1358;
  real_T c3_x[16];
  int32_T c3_ix0;
  int32_T c3_iy0;
  int32_T c3_i1359;
  int32_T c3_i1360;
  real_T c3_b_x[16];
  int32_T c3_b_ix0;
  int32_T c3_b_iy0;
  int32_T c3_i1361;
  real_T c3_c_x[16];
  int32_T c3_i1362;
  real_T c3_d_x[16];
  real_T c3_e_x[16];
  int32_T c3_i1363;
  int32_T c3_i1364;
  int32_T c3_b_jp1j;
  int32_T c3_i_a;
  int32_T c3_d_c;
  int32_T c3_j_a;
  int32_T c3_g_b;
  int32_T c3_loop_ub;
  int32_T c3_i;
  int32_T c3_b_i;
  real_T c3_f_x;
  real_T c3_y;
  real_T c3_g_x;
  real_T c3_b_y;
  real_T c3_z;
  int32_T c3_h_b;
  int32_T c3_e_c;
  int32_T c3_k_a;
  int32_T c3_f_c;
  int32_T c3_l_a;
  int32_T c3_g_c;
  int32_T c3_m;
  int32_T c3_n;
  int32_T c3_c_ix0;
  int32_T c3_c_iy0;
  int32_T c3_i1365;
  real_T c3_d_A[16];
  int32_T c3_ia0;
  int32_T c3_i1366;
  int32_T c3_b_m;
  int32_T c3_b_n;
  int32_T c3_d_ix0;
  int32_T c3_d_iy0;
  int32_T c3_i1367;
  real_T c3_e_A[16];
  int32_T c3_b_ia0;
  int32_T c3_i1368;
  int32_T c3_c_m;
  int32_T c3_c_n;
  int32_T c3_e_ix0;
  int32_T c3_e_iy0;
  int32_T c3_i1369;
  real_T c3_f_A[16];
  int32_T c3_c_ia0;
  int32_T c3_i1370;
  int32_T c3_i1371;
  real_T c3_g_A[16];
  for (c3_i1355 = 0; c3_i1355 < 16; c3_i1355 = c3_i1355 + 1) {
    c3_b_A[c3_i1355] = c3_A[c3_i1355];
  }

  c3_b_eps(chartInstance);
  for (c3_i1356 = 0; c3_i1356 < 4; c3_i1356 = c3_i1356 + 1) {
    c3_ipiv[c3_i1356] = 1 + c3_i1356;
  }

  *c3_info = 0;
  for (c3_j = 1; c3_j < 4; c3_j = c3_j + 1) {
    c3_b_j = c3_j;
    c3_a = c3_b_j;
    c3_jm1 = c3_a - 1;
    c3_b = c3_b_j;
    c3_mmj = 4 - c3_b;
    c3_b_a = c3_jm1;
    c3_c = c3_b_a * 5;
    c3_b_b = c3_c;
    c3_jj = 1 + c3_b_b;
    c3_c_a = c3_jj;
    c3_jp1j = c3_c_a + 1;
    c3_d_a = c3_mmj;
    c3_b_c = c3_d_a + 1;
    for (c3_i1357 = 0; c3_i1357 < 16; c3_i1357 = c3_i1357 + 1) {
      c3_c_A[c3_i1357] = c3_b_A[c3_i1357];
    }

    c3_e_a = c3_eml_ixamax(chartInstance, c3_b_c, c3_c_A, c3_jj);
    c3_jpiv_offset = c3_e_a - 1;
    c3_f_a = c3_jj;
    c3_c_b = c3_jpiv_offset;
    c3_jpiv = c3_f_a + c3_c_b;
    if (c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_jpiv), 1, 16, 1, 0) - 1] != 0.0) {
      if ((real_T)c3_jpiv_offset != 0.0) {
        c3_g_a = c3_b_j;
        c3_d_b = c3_jpiv_offset;
        c3_c_c = c3_g_a + c3_d_b;
        c3_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_j), 1, 4, 1, 0) - 1] = c3_c_c;
        c3_e_b = c3_jm1;
        c3_jrow = 1 + c3_e_b;
        c3_h_a = c3_jrow;
        c3_f_b = c3_jpiv_offset;
        c3_jprow = c3_h_a + c3_f_b;
        for (c3_i1358 = 0; c3_i1358 < 16; c3_i1358 = c3_i1358 + 1) {
          c3_x[c3_i1358] = c3_b_A[c3_i1358];
        }

        c3_ix0 = c3_jrow;
        c3_iy0 = c3_jprow;
        for (c3_i1359 = 0; c3_i1359 < 16; c3_i1359 = c3_i1359 + 1) {
          c3_b_A[c3_i1359] = c3_x[c3_i1359];
        }

        for (c3_i1360 = 0; c3_i1360 < 16; c3_i1360 = c3_i1360 + 1) {
          c3_b_x[c3_i1360] = c3_b_A[c3_i1360];
        }

        c3_b_ix0 = c3_ix0;
        c3_b_iy0 = c3_iy0;
        for (c3_i1361 = 0; c3_i1361 < 16; c3_i1361 = c3_i1361 + 1) {
          c3_c_x[c3_i1361] = c3_b_x[c3_i1361];
        }

        for (c3_i1362 = 0; c3_i1362 < 16; c3_i1362 = c3_i1362 + 1) {
          c3_d_x[c3_i1362] = c3_c_x[c3_i1362];
        }

        c3_ceval_xswap(chartInstance, 4, c3_d_x, c3_b_ix0, 4, c3_b_iy0, 4,
                       c3_e_x);
        for (c3_i1363 = 0; c3_i1363 < 16; c3_i1363 = c3_i1363 + 1) {
          c3_c_x[c3_i1363] = c3_e_x[c3_i1363];
        }

        for (c3_i1364 = 0; c3_i1364 < 16; c3_i1364 = c3_i1364 + 1) {
          c3_b_A[c3_i1364] = c3_c_x[c3_i1364];
        }
      }

      c3_b_jp1j = c3_jp1j;
      c3_i_a = c3_mmj;
      c3_d_c = c3_i_a - 1;
      c3_j_a = c3_jp1j;
      c3_g_b = c3_d_c;
      c3_loop_ub = c3_j_a + c3_g_b;
      for (c3_i = c3_b_jp1j; c3_i <= c3_loop_ub; c3_i = c3_i + 1) {
        c3_b_i = c3_i;
        c3_f_x = c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_b_i), 1, 16, 1, 0) - 1];
        c3_y = c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_jj), 1, 16, 1, 0) - 1];
        c3_g_x = c3_f_x;
        c3_b_y = c3_y;
        c3_z = c3_g_x / c3_b_y;
        c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_i), 1, 16, 1, 0) - 1] = c3_z;
      }
    } else {
      *c3_info = c3_b_j;
    }

    c3_h_b = c3_b_j;
    c3_e_c = 4 - c3_h_b;
    c3_k_a = c3_jj;
    c3_f_c = c3_k_a + 4;
    c3_l_a = c3_jj;
    c3_g_c = c3_l_a + 5;
    c3_m = c3_mmj;
    c3_n = c3_e_c;
    c3_c_ix0 = c3_jp1j;
    c3_c_iy0 = c3_f_c;
    for (c3_i1365 = 0; c3_i1365 < 16; c3_i1365 = c3_i1365 + 1) {
      c3_d_A[c3_i1365] = c3_b_A[c3_i1365];
    }

    c3_ia0 = c3_g_c;
    for (c3_i1366 = 0; c3_i1366 < 16; c3_i1366 = c3_i1366 + 1) {
      c3_b_A[c3_i1366] = c3_d_A[c3_i1366];
    }

    c3_b_m = c3_m;
    c3_b_n = c3_n;
    c3_d_ix0 = c3_c_ix0;
    c3_d_iy0 = c3_c_iy0;
    for (c3_i1367 = 0; c3_i1367 < 16; c3_i1367 = c3_i1367 + 1) {
      c3_e_A[c3_i1367] = c3_b_A[c3_i1367];
    }

    c3_b_ia0 = c3_ia0;
    for (c3_i1368 = 0; c3_i1368 < 16; c3_i1368 = c3_i1368 + 1) {
      c3_b_A[c3_i1368] = c3_e_A[c3_i1368];
    }

    c3_c_m = c3_b_m;
    c3_c_n = c3_b_n;
    c3_e_ix0 = c3_d_ix0;
    c3_e_iy0 = c3_d_iy0;
    for (c3_i1369 = 0; c3_i1369 < 16; c3_i1369 = c3_i1369 + 1) {
      c3_f_A[c3_i1369] = c3_b_A[c3_i1369];
    }

    c3_c_ia0 = c3_b_ia0;
    for (c3_i1370 = 0; c3_i1370 < 16; c3_i1370 = c3_i1370 + 1) {
      c3_b_A[c3_i1370] = c3_f_A[c3_i1370];
    }

    if ((real_T)c3_c_m < 1.0) {
    } else if ((real_T)c3_c_n < 1.0) {
    } else {
      for (c3_i1371 = 0; c3_i1371 < 16; c3_i1371 = c3_i1371 + 1) {
        c3_g_A[c3_i1371] = c3_b_A[c3_i1371];
      }

      c3_ceval_xger(chartInstance, c3_c_m, c3_c_n, -1.0, c3_e_ix0, 1, c3_e_iy0,
                    4, c3_g_A, c3_c_ia0, 4, c3_b_A);
      goto label_1;
    }

   label_1:
    ;
  }

  if ((real_T)*c3_info == 0.0) {
    if (!(c3_b_A[15] != 0.0)) {
      *c3_info = 4;
      return;
    }
  }
}

static int32_T c3_eml_ixamax(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0)
{
  int32_T c3_b_n;
  int32_T c3_i1372;
  real_T c3_b_x[16];
  int32_T c3_b_ix0;
  int32_T c3_i1373;
  real_T c3_c_x[16];
  c3_b_n = c3_n;
  for (c3_i1372 = 0; c3_i1372 < 16; c3_i1372 = c3_i1372 + 1) {
    c3_b_x[c3_i1372] = c3_x[c3_i1372];
  }

  c3_b_ix0 = c3_ix0;
  for (c3_i1373 = 0; c3_i1373 < 16; c3_i1373 = c3_i1373 + 1) {
    c3_c_x[c3_i1373] = c3_b_x[c3_i1373];
  }

  return c3_ceval_ixamax(chartInstance, c3_b_n, c3_c_x, c3_b_ix0, 1);
}

static int32_T c3_ceval_ixamax(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0,
  int32_T c3_incx)
{
  return idamax32(&c3_n, &c3_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 16, 1, 0) - 1], &
                  c3_incx);
}

static void c3_ceval_xswap(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c3_n, real_T c3_x[16], int32_T c3_ix0,
  int32_T c3_incx, int32_T c3_iy0, int32_T c3_incy, real_T c3_b_x[16])
{
  int32_T c3_i1374;

  /* Empty Loop. */
  for (c3_i1374 = 0; c3_i1374 < 16; c3_i1374 = c3_i1374 + 1) {
    c3_b_x[c3_i1374] = c3_x[c3_i1374];
  }

  dswap32(&c3_n, &c3_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 16, 1, 0) - 1], &c3_incx
          , &c3_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
            "", (real_T)c3_iy0), 1, 16, 1, 0) - 1], &c3_incy);
}

static void c3_ceval_xger(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, real_T c3_alpha1,
  int32_T c3_ix0, int32_T c3_incx, int32_T c3_iy0, int32_T c3_incy, real_T c3_A
  [16], int32_T c3_ia0, int32_T c3_lda, real_T c3_b_A[16]
  )
{
  int32_T c3_i1375;
  for (c3_i1375 = 0; c3_i1375 < 16; c3_i1375 = c3_i1375 + 1) {
    c3_b_A[c3_i1375] = c3_A[c3_i1375];
  }

  dger32(&c3_m, &c3_n, &c3_alpha1, &c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 16, 1,
          0) - 1], &c3_incx, &c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_iy0), 1, 16, 1, 0) - 1], &
         c3_incy, &c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_ia0), 1, 16, 1, 0) - 1], &c3_lda);
}

static void c3_eml_xtrsm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[4], real_T c3_b_B[4])
{
  int32_T c3_i1376;
  int32_T c3_i1377;
  real_T c3_b_A[16];
  int32_T c3_i1378;
  real_T c3_c_B[4];
  int32_T c3_i1379;
  int32_T c3_i1380;
  real_T c3_c_A[16];
  int32_T c3_i1381;
  real_T c3_d_B[4];
  int32_T c3_i1382;
  int32_T c3_j;
  int32_T c3_b_j;
  int32_T c3_a;
  int32_T c3_c;
  int32_T c3_b;
  int32_T c3_b_c;
  int32_T c3_b_b;
  int32_T c3_jBcol;
  int32_T c3_k;
  int32_T c3_b_k;
  int32_T c3_b_a;
  int32_T c3_c_c;
  int32_T c3_c_b;
  int32_T c3_d_c;
  int32_T c3_d_b;
  int32_T c3_kAcol;
  int32_T c3_c_a;
  int32_T c3_e_b;
  int32_T c3_e_c;
  int32_T c3_d_a;
  int32_T c3_i1383;
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_e_a;
  int32_T c3_f_b;
  int32_T c3_f_c;
  int32_T c3_f_a;
  int32_T c3_g_b;
  int32_T c3_g_c;
  int32_T c3_g_a;
  int32_T c3_h_b;
  int32_T c3_h_c;
  int32_T c3_h_a;
  int32_T c3_i_b;
  int32_T c3_i_c;
  for (c3_i1376 = 0; c3_i1376 < 4; c3_i1376 = c3_i1376 + 1) {
    c3_b_B[c3_i1376] = c3_B[c3_i1376];
  }

  for (c3_i1377 = 0; c3_i1377 < 16; c3_i1377 = c3_i1377 + 1) {
    c3_b_A[c3_i1377] = c3_A[c3_i1377];
  }

  for (c3_i1378 = 0; c3_i1378 < 4; c3_i1378 = c3_i1378 + 1) {
    c3_c_B[c3_i1378] = c3_b_B[c3_i1378];
  }

  for (c3_i1379 = 0; c3_i1379 < 4; c3_i1379 = c3_i1379 + 1) {
    c3_b_B[c3_i1379] = c3_c_B[c3_i1379];
  }

  for (c3_i1380 = 0; c3_i1380 < 16; c3_i1380 = c3_i1380 + 1) {
    c3_c_A[c3_i1380] = c3_b_A[c3_i1380];
  }

  for (c3_i1381 = 0; c3_i1381 < 4; c3_i1381 = c3_i1381 + 1) {
    c3_d_B[c3_i1381] = c3_b_B[c3_i1381];
  }

  for (c3_i1382 = 0; c3_i1382 < 4; c3_i1382 = c3_i1382 + 1) {
    c3_b_B[c3_i1382] = c3_d_B[c3_i1382];
  }

  c3_f_eml_scalar_eg(chartInstance);
  for (c3_j = 1; c3_j <= 1; c3_j = c3_j + 1) {
    c3_b_j = c3_j;
    c3_a = c3_b_j;
    c3_c = c3_a - 1;
    c3_b = c3_c;
    c3_b_c = c3_b << 2;
    c3_b_b = c3_b_c;
    c3_jBcol = c3_b_b;
    for (c3_k = 1; c3_k <= 4; c3_k = c3_k + 1) {
      c3_b_k = c3_k;
      c3_b_a = c3_b_k;
      c3_c_c = c3_b_a - 1;
      c3_c_b = c3_c_c;
      c3_d_c = c3_c_b << 2;
      c3_d_b = c3_d_c;
      c3_kAcol = c3_d_b;
      c3_c_a = c3_b_k;
      c3_e_b = c3_jBcol;
      c3_e_c = c3_c_a + c3_e_b;
      if (c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_e_c), 1, 4, 1, 0) - 1] != 0.0) {
        c3_d_a = c3_b_k;
        c3_i1383 = c3_d_a + 1;
        for (c3_i = c3_i1383; c3_i <= 4; c3_i = c3_i + 1) {
          c3_b_i = c3_i;
          c3_e_a = c3_b_i;
          c3_f_b = c3_jBcol;
          c3_f_c = c3_e_a + c3_f_b;
          c3_f_a = c3_b_i;
          c3_g_b = c3_jBcol;
          c3_g_c = c3_f_a + c3_g_b;
          c3_g_a = c3_b_k;
          c3_h_b = c3_jBcol;
          c3_h_c = c3_g_a + c3_h_b;
          c3_h_a = c3_b_i;
          c3_i_b = c3_kAcol;
          c3_i_c = c3_h_a + c3_i_b;
          c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_f_c), 1, 4, 1, 0) - 1] = c3_b_B[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_g_c), 1, 4, 1, 0) - 1] - c3_b_B[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_h_c), 1, 4, 1, 0) - 1] * c3_c_A[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_i_c), 1, 16, 1, 0) - 1];
        }
      }
    }
  }
}

static void c3_f_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_eml_blas_xtrsm(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, real_T c3_alpha1,
  real_T c3_A[16], int32_T c3_ia0, int32_T c3_lda, real_T c3_B[4], int32_T
  c3_ib0, int32_T c3_ldb, real_T c3_b_B[4])
{
  int32_T c3_i1384;
  int32_T c3_b_m;
  int32_T c3_b_n;
  real_T c3_b_alpha1;
  int32_T c3_i1385;
  real_T c3_b_A[16];
  int32_T c3_b_ia0;
  int32_T c3_b_lda;
  int32_T c3_i1386;
  real_T c3_c_B[4];
  int32_T c3_b_ib0;
  int32_T c3_b_ldb;
  int32_T c3_i1387;
  boolean_T c3_NON_UNIT_ALPHA;
  int32_T c3_a;
  int32_T c3_Aoffset;
  int32_T c3_b_a;
  int32_T c3_Boffset;
  int32_T c3_loop_ub;
  int32_T c3_j;
  int32_T c3_b_j;
  int32_T c3_c_a;
  int32_T c3_c;
  int32_T c3_d_a;
  int32_T c3_b;
  int32_T c3_b_c;
  int32_T c3_e_a;
  int32_T c3_b_b;
  int32_T c3_jBcol;
  int32_T c3_b_loop_ub;
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_f_a;
  int32_T c3_c_b;
  int32_T c3_c_c;
  int32_T c3_c_loop_ub;
  int32_T c3_c_j;
  int32_T c3_g_a;
  int32_T c3_d_c;
  int32_T c3_h_a;
  int32_T c3_d_b;
  int32_T c3_e_c;
  int32_T c3_i_a;
  int32_T c3_e_b;
  int32_T c3_d_loop_ub;
  int32_T c3_c_i;
  int32_T c3_j_a;
  int32_T c3_f_b;
  int32_T c3_f_c;
  int32_T c3_k_a;
  int32_T c3_g_b;
  int32_T c3_g_c;
  int32_T c3_c_m;
  int32_T c3_k;
  int32_T c3_b_k;
  int32_T c3_l_a;
  int32_T c3_h_c;
  int32_T c3_m_a;
  int32_T c3_h_b;
  int32_T c3_i_c;
  int32_T c3_n_a;
  int32_T c3_i_b;
  int32_T c3_kAcol;
  int32_T c3_o_a;
  int32_T c3_j_b;
  int32_T c3_j_c;
  int32_T c3_p_a;
  int32_T c3_k_b;
  int32_T c3_k_c;
  int32_T c3_q_a;
  int32_T c3_l_b;
  int32_T c3_l_c;
  int32_T c3_r_a;
  int32_T c3_m_b;
  int32_T c3_m_c;
  real_T c3_x;
  real_T c3_y;
  real_T c3_b_x;
  real_T c3_b_y;
  real_T c3_z;
  int32_T c3_s_a;
  int32_T c3_e_loop_ub;
  int32_T c3_d_i;
  int32_T c3_t_a;
  int32_T c3_n_b;
  int32_T c3_n_c;
  int32_T c3_u_a;
  int32_T c3_o_b;
  int32_T c3_o_c;
  int32_T c3_v_a;
  int32_T c3_p_b;
  int32_T c3_p_c;
  int32_T c3_w_a;
  int32_T c3_q_b;
  int32_T c3_q_c;
  for (c3_i1384 = 0; c3_i1384 < 4; c3_i1384 = c3_i1384 + 1) {
    c3_b_B[c3_i1384] = c3_B[c3_i1384];
  }

  c3_b_m = c3_m;
  c3_b_n = c3_n;
  c3_b_alpha1 = c3_alpha1;
  for (c3_i1385 = 0; c3_i1385 < 16; c3_i1385 = c3_i1385 + 1) {
    c3_b_A[c3_i1385] = c3_A[c3_i1385];
  }

  c3_b_ia0 = c3_ia0;
  c3_b_lda = c3_lda;
  for (c3_i1386 = 0; c3_i1386 < 4; c3_i1386 = c3_i1386 + 1) {
    c3_c_B[c3_i1386] = c3_b_B[c3_i1386];
  }

  c3_b_ib0 = c3_ib0;
  c3_b_ldb = c3_ldb;
  for (c3_i1387 = 0; c3_i1387 < 4; c3_i1387 = c3_i1387 + 1) {
    c3_b_B[c3_i1387] = c3_c_B[c3_i1387];
  }

  c3_NON_UNIT_ALPHA = (c3_b_alpha1 != 1.0);
  if ((real_T)c3_b_n == 0.0) {
  } else {
    c3_f_eml_scalar_eg(chartInstance);
    c3_a = c3_b_ia0;
    c3_Aoffset = c3_a - 1;
    c3_b_a = c3_b_ib0;
    c3_Boffset = c3_b_a - 1;
    if (c3_b_alpha1 == 0.0) {
      c3_loop_ub = c3_b_n;
      for (c3_j = 1; c3_j <= c3_loop_ub; c3_j = c3_j + 1) {
        c3_b_j = c3_j;
        c3_c_a = c3_b_j;
        c3_c = c3_c_a - 1;
        c3_d_a = c3_b_ldb;
        c3_b = c3_c;
        c3_b_c = c3_d_a * c3_b;
        c3_e_a = c3_Boffset;
        c3_b_b = c3_b_c;
        c3_jBcol = c3_e_a + c3_b_b;
        c3_b_loop_ub = c3_b_m;
        for (c3_i = 1; c3_i <= c3_b_loop_ub; c3_i = c3_i + 1) {
          c3_b_i = c3_i;
          c3_f_a = c3_b_i;
          c3_c_b = c3_jBcol;
          c3_c_c = c3_f_a + c3_c_b;
          c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_c_c), 1, 4, 1, 0) - 1] = 0.0;
        }
      }
    } else {
      c3_c_loop_ub = c3_b_n;
      for (c3_c_j = 1; c3_c_j <= c3_c_loop_ub; c3_c_j = c3_c_j + 1) {
        c3_b_j = c3_c_j;
        c3_g_a = c3_b_j;
        c3_d_c = c3_g_a - 1;
        c3_h_a = c3_b_ldb;
        c3_d_b = c3_d_c;
        c3_e_c = c3_h_a * c3_d_b;
        c3_i_a = c3_Boffset;
        c3_e_b = c3_e_c;
        c3_jBcol = c3_i_a + c3_e_b;
        if (c3_NON_UNIT_ALPHA) {
          c3_d_loop_ub = c3_b_m;
          for (c3_c_i = 1; c3_c_i <= c3_d_loop_ub; c3_c_i = c3_c_i + 1) {
            c3_b_i = c3_c_i;
            c3_j_a = c3_b_i;
            c3_f_b = c3_jBcol;
            c3_f_c = c3_j_a + c3_f_b;
            c3_k_a = c3_b_i;
            c3_g_b = c3_jBcol;
            c3_g_c = c3_k_a + c3_g_b;
            c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c3_f_c), 1, 4, 1, 0) - 1] = c3_b_alpha1 * c3_b_B[
              _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c3_g_c), 1, 4, 1, 0) - 1];
          }
        }

        c3_c_m = c3_b_m;
        for (c3_k = c3_c_m; c3_k > 0; c3_k = c3_k + -1) {
          c3_b_k = c3_k;
          c3_l_a = c3_b_k;
          c3_h_c = c3_l_a - 1;
          c3_m_a = c3_b_lda;
          c3_h_b = c3_h_c;
          c3_i_c = c3_m_a * c3_h_b;
          c3_n_a = c3_Aoffset;
          c3_i_b = c3_i_c;
          c3_kAcol = c3_n_a + c3_i_b;
          c3_o_a = c3_b_k;
          c3_j_b = c3_jBcol;
          c3_j_c = c3_o_a + c3_j_b;
          if (c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
               ("", (real_T)c3_j_c), 1, 4, 1, 0) - 1] != 0.0) {
            c3_p_a = c3_b_k;
            c3_k_b = c3_jBcol;
            c3_k_c = c3_p_a + c3_k_b;
            c3_q_a = c3_b_k;
            c3_l_b = c3_jBcol;
            c3_l_c = c3_q_a + c3_l_b;
            c3_r_a = c3_b_k;
            c3_m_b = c3_kAcol;
            c3_m_c = c3_r_a + c3_m_b;
            c3_x = c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c3_l_c), 1, 4, 1, 0) - 1];
            c3_y = c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c3_m_c), 1, 16, 1, 0) - 1];
            c3_b_x = c3_x;
            c3_b_y = c3_y;
            c3_z = c3_b_x / c3_b_y;
            c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c3_k_c), 1, 4, 1, 0) - 1] = c3_z;
            c3_s_a = c3_b_k;
            c3_e_loop_ub = c3_s_a - 1;
            for (c3_d_i = 1; c3_d_i <= c3_e_loop_ub; c3_d_i = c3_d_i + 1) {
              c3_b_i = c3_d_i;
              c3_t_a = c3_b_i;
              c3_n_b = c3_jBcol;
              c3_n_c = c3_t_a + c3_n_b;
              c3_u_a = c3_b_i;
              c3_o_b = c3_jBcol;
              c3_o_c = c3_u_a + c3_o_b;
              c3_v_a = c3_b_k;
              c3_p_b = c3_jBcol;
              c3_p_c = c3_v_a + c3_p_b;
              c3_w_a = c3_b_i;
              c3_q_b = c3_kAcol;
              c3_q_c = c3_w_a + c3_q_b;
              c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                ("", (real_T)c3_n_c), 1, 4, 1, 0) - 1] = c3_b_B[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c3_o_c), 1, 4, 1, 0) - 1] - c3_b_B[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c3_p_c), 1, 4, 1, 0) - 1] * c3_b_A[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c3_q_c), 1, 16, 1, 0) - 1];
            }
          }
        }
      }
    }
  }
}

static void c3_b_mldivide(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[16], real_T c3_Y[16])
{
  int32_T c3_i1388;
  real_T c3_b_A[16];
  int32_T c3_i1389;
  real_T c3_b_B[16];
  int32_T c3_i1390;
  real_T c3_c_A[16];
  int32_T c3_i1391;
  real_T c3_c_B[16];
  int32_T c3_i1392;
  real_T c3_d_A[16];
  int32_T c3_i1393;
  real_T c3_e_A[16];
  int32_T c3_i1394;
  real_T c3_f_A[16];
  int32_T c3_i1395;
  real_T c3_g_A[16];
  int32_T c3_i1396;
  real_T c3_h_A[16];
  int32_T c3_info;
  int32_T c3_ipiv[4];
  real_T c3_i_A[16];
  int32_T c3_i1397;
  int32_T c3_i1398;
  int32_T c3_b_ipiv[4];
  int32_T c3_b_info;
  int32_T c3_i1399;
  int32_T c3_i1400;
  int32_T c3_c_ipiv[4];
  int32_T c3_c_info;
  int32_T c3_i1401;
  int32_T c3_i1402;
  int32_T c3_d_ipiv[4];
  int32_T c3_d_info;
  int32_T c3_i1403;
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_ip;
  int32_T c3_j;
  int32_T c3_b_j;
  real_T c3_temp;
  int32_T c3_i1404;
  real_T c3_j_A[16];
  int32_T c3_i1405;
  real_T c3_b_Y[16];
  int32_T c3_i1406;
  real_T c3_k_A[16];
  int32_T c3_i1407;
  real_T c3_d_B[16];
  int32_T c3_i1408;
  int32_T c3_i1409;
  real_T c3_l_A[16];
  int32_T c3_i1410;
  real_T c3_c_Y[16];
  for (c3_i1388 = 0; c3_i1388 < 16; c3_i1388 = c3_i1388 + 1) {
    c3_b_A[c3_i1388] = c3_A[c3_i1388];
  }

  for (c3_i1389 = 0; c3_i1389 < 16; c3_i1389 = c3_i1389 + 1) {
    c3_b_B[c3_i1389] = c3_B[c3_i1389];
  }

  for (c3_i1390 = 0; c3_i1390 < 16; c3_i1390 = c3_i1390 + 1) {
    c3_c_A[c3_i1390] = c3_b_A[c3_i1390];
  }

  for (c3_i1391 = 0; c3_i1391 < 16; c3_i1391 = c3_i1391 + 1) {
    c3_c_B[c3_i1391] = c3_b_B[c3_i1391];
  }

  for (c3_i1392 = 0; c3_i1392 < 16; c3_i1392 = c3_i1392 + 1) {
    c3_d_A[c3_i1392] = c3_c_A[c3_i1392];
  }

  for (c3_i1393 = 0; c3_i1393 < 16; c3_i1393 = c3_i1393 + 1) {
    c3_e_A[c3_i1393] = c3_d_A[c3_i1393];
  }

  for (c3_i1394 = 0; c3_i1394 < 16; c3_i1394 = c3_i1394 + 1) {
    c3_f_A[c3_i1394] = c3_e_A[c3_i1394];
  }

  for (c3_i1395 = 0; c3_i1395 < 16; c3_i1395 = c3_i1395 + 1) {
    c3_g_A[c3_i1395] = c3_f_A[c3_i1395];
  }

  for (c3_i1396 = 0; c3_i1396 < 16; c3_i1396 = c3_i1396 + 1) {
    c3_h_A[c3_i1396] = c3_g_A[c3_i1396];
  }

  c3_eml_matlab_zgetrf(chartInstance, c3_h_A, c3_i_A, c3_ipiv, &c3_info);
  for (c3_i1397 = 0; c3_i1397 < 16; c3_i1397 = c3_i1397 + 1) {
    c3_g_A[c3_i1397] = c3_i_A[c3_i1397];
  }

  for (c3_i1398 = 0; c3_i1398 < 4; c3_i1398 = c3_i1398 + 1) {
    c3_b_ipiv[c3_i1398] = c3_ipiv[c3_i1398];
  }

  c3_b_info = c3_info;
  for (c3_i1399 = 0; c3_i1399 < 16; c3_i1399 = c3_i1399 + 1) {
    c3_e_A[c3_i1399] = c3_g_A[c3_i1399];
  }

  for (c3_i1400 = 0; c3_i1400 < 4; c3_i1400 = c3_i1400 + 1) {
    c3_c_ipiv[c3_i1400] = c3_b_ipiv[c3_i1400];
  }

  c3_c_info = c3_b_info;
  for (c3_i1401 = 0; c3_i1401 < 16; c3_i1401 = c3_i1401 + 1) {
    c3_c_A[c3_i1401] = c3_e_A[c3_i1401];
  }

  for (c3_i1402 = 0; c3_i1402 < 4; c3_i1402 = c3_i1402 + 1) {
    c3_d_ipiv[c3_i1402] = c3_c_ipiv[c3_i1402];
  }

  c3_d_info = c3_c_info;
  if ((real_T)c3_d_info > 0.0) {
    c3_eml_warning(chartInstance);
  }

  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i1403 = 0; c3_i1403 < 16; c3_i1403 = c3_i1403 + 1) {
    c3_Y[c3_i1403] = c3_c_B[c3_i1403];
  }

  for (c3_i = 1; c3_i < 5; c3_i = c3_i + 1) {
    c3_b_i = c3_i;
    if (c3_d_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_i), 1, 4, 1, 0) - 1] != c3_b_i) {
      c3_ip = c3_d_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c3_b_i), 1, 4, 1, 0) - 1];
      for (c3_j = 1; c3_j < 5; c3_j = c3_j + 1) {
        c3_b_j = c3_j;
        c3_temp = c3_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_b_i), 1, 4, 1, 0) - 1) + ((
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_j), 1, 4, 2, 0) - 1) << 2)];
        c3_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c3_b_i), 1, 4, 1, 0) - 1) + ((
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_j), 1, 4, 2, 0) - 1) << 2)] = c3_Y[(
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_ip), 1, 4, 1, 0) - 1) + ((_SFD_EML_ARRAY_BOUNDS_CHECK(""
          , (int32_T)_SFD_INTEGER_CHECK("", (real_T)c3_b_j), 1, 4, 2, 0) - 1) <<
          2)];
        c3_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c3_ip), 1, 4, 1, 0) - 1) + ((
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_j), 1, 4, 2, 0) - 1) << 2)] = c3_temp;
      }
    }
  }

  for (c3_i1404 = 0; c3_i1404 < 16; c3_i1404 = c3_i1404 + 1) {
    c3_j_A[c3_i1404] = c3_c_A[c3_i1404];
  }

  for (c3_i1405 = 0; c3_i1405 < 16; c3_i1405 = c3_i1405 + 1) {
    c3_b_Y[c3_i1405] = c3_Y[c3_i1405];
  }

  c3_b_eml_xtrsm(chartInstance, c3_j_A, c3_b_Y, c3_Y);
  for (c3_i1406 = 0; c3_i1406 < 16; c3_i1406 = c3_i1406 + 1) {
    c3_k_A[c3_i1406] = c3_c_A[c3_i1406];
  }

  for (c3_i1407 = 0; c3_i1407 < 16; c3_i1407 = c3_i1407 + 1) {
    c3_d_B[c3_i1407] = c3_Y[c3_i1407];
  }

  for (c3_i1408 = 0; c3_i1408 < 16; c3_i1408 = c3_i1408 + 1) {
    c3_Y[c3_i1408] = c3_d_B[c3_i1408];
  }

  for (c3_i1409 = 0; c3_i1409 < 16; c3_i1409 = c3_i1409 + 1) {
    c3_l_A[c3_i1409] = c3_k_A[c3_i1409];
  }

  for (c3_i1410 = 0; c3_i1410 < 16; c3_i1410 = c3_i1410 + 1) {
    c3_c_Y[c3_i1410] = c3_Y[c3_i1410];
  }

  c3_b_eml_blas_xtrsm(chartInstance, 4, 4, 1.0, c3_l_A, 1, 4, c3_c_Y, 1, 4, c3_Y);
}

static void c3_b_eml_xtrsm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[16], real_T c3_b_B[16]
  )
{
  int32_T c3_i1411;
  int32_T c3_i1412;
  real_T c3_b_A[16];
  int32_T c3_i1413;
  real_T c3_c_B[16];
  int32_T c3_i1414;
  int32_T c3_i1415;
  real_T c3_c_A[16];
  int32_T c3_i1416;
  real_T c3_d_B[16];
  int32_T c3_i1417;
  int32_T c3_j;
  int32_T c3_b_j;
  int32_T c3_a;
  int32_T c3_c;
  int32_T c3_b;
  int32_T c3_b_c;
  int32_T c3_b_b;
  int32_T c3_jBcol;
  int32_T c3_k;
  int32_T c3_b_k;
  int32_T c3_b_a;
  int32_T c3_c_c;
  int32_T c3_c_b;
  int32_T c3_d_c;
  int32_T c3_d_b;
  int32_T c3_kAcol;
  int32_T c3_c_a;
  int32_T c3_e_b;
  int32_T c3_e_c;
  int32_T c3_d_a;
  int32_T c3_i1418;
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_e_a;
  int32_T c3_f_b;
  int32_T c3_f_c;
  int32_T c3_f_a;
  int32_T c3_g_b;
  int32_T c3_g_c;
  int32_T c3_g_a;
  int32_T c3_h_b;
  int32_T c3_h_c;
  int32_T c3_h_a;
  int32_T c3_i_b;
  int32_T c3_i_c;
  for (c3_i1411 = 0; c3_i1411 < 16; c3_i1411 = c3_i1411 + 1) {
    c3_b_B[c3_i1411] = c3_B[c3_i1411];
  }

  for (c3_i1412 = 0; c3_i1412 < 16; c3_i1412 = c3_i1412 + 1) {
    c3_b_A[c3_i1412] = c3_A[c3_i1412];
  }

  for (c3_i1413 = 0; c3_i1413 < 16; c3_i1413 = c3_i1413 + 1) {
    c3_c_B[c3_i1413] = c3_b_B[c3_i1413];
  }

  for (c3_i1414 = 0; c3_i1414 < 16; c3_i1414 = c3_i1414 + 1) {
    c3_b_B[c3_i1414] = c3_c_B[c3_i1414];
  }

  for (c3_i1415 = 0; c3_i1415 < 16; c3_i1415 = c3_i1415 + 1) {
    c3_c_A[c3_i1415] = c3_b_A[c3_i1415];
  }

  for (c3_i1416 = 0; c3_i1416 < 16; c3_i1416 = c3_i1416 + 1) {
    c3_d_B[c3_i1416] = c3_b_B[c3_i1416];
  }

  for (c3_i1417 = 0; c3_i1417 < 16; c3_i1417 = c3_i1417 + 1) {
    c3_b_B[c3_i1417] = c3_d_B[c3_i1417];
  }

  c3_g_eml_scalar_eg(chartInstance);
  for (c3_j = 1; c3_j <= 4; c3_j = c3_j + 1) {
    c3_b_j = c3_j;
    c3_a = c3_b_j;
    c3_c = c3_a - 1;
    c3_b = c3_c;
    c3_b_c = c3_b << 2;
    c3_b_b = c3_b_c;
    c3_jBcol = c3_b_b;
    for (c3_k = 1; c3_k <= 4; c3_k = c3_k + 1) {
      c3_b_k = c3_k;
      c3_b_a = c3_b_k;
      c3_c_c = c3_b_a - 1;
      c3_c_b = c3_c_c;
      c3_d_c = c3_c_b << 2;
      c3_d_b = c3_d_c;
      c3_kAcol = c3_d_b;
      c3_c_a = c3_b_k;
      c3_e_b = c3_jBcol;
      c3_e_c = c3_c_a + c3_e_b;
      if (c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_e_c), 1, 16, 1, 0) - 1] != 0.0) {
        c3_d_a = c3_b_k;
        c3_i1418 = c3_d_a + 1;
        for (c3_i = c3_i1418; c3_i <= 4; c3_i = c3_i + 1) {
          c3_b_i = c3_i;
          c3_e_a = c3_b_i;
          c3_f_b = c3_jBcol;
          c3_f_c = c3_e_a + c3_f_b;
          c3_f_a = c3_b_i;
          c3_g_b = c3_jBcol;
          c3_g_c = c3_f_a + c3_g_b;
          c3_g_a = c3_b_k;
          c3_h_b = c3_jBcol;
          c3_h_c = c3_g_a + c3_h_b;
          c3_h_a = c3_b_i;
          c3_i_b = c3_kAcol;
          c3_i_c = c3_h_a + c3_i_b;
          c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_f_c), 1, 16, 1, 0) - 1] = c3_b_B[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_g_c), 1, 16, 1, 0) - 1] - c3_b_B[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_h_c), 1, 16, 1, 0) - 1] * c3_c_A[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_i_c), 1, 16, 1, 0) - 1];
        }
      }
    }
  }
}

static void c3_g_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_b_eml_blas_xtrsm(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, real_T c3_alpha1,
  real_T c3_A[16], int32_T c3_ia0, int32_T c3_lda, real_T c3_B[16], int32_T
  c3_ib0, int32_T c3_ldb, real_T c3_b_B[16])
{
  int32_T c3_i1419;
  int32_T c3_b_m;
  int32_T c3_b_n;
  real_T c3_b_alpha1;
  int32_T c3_i1420;
  real_T c3_b_A[16];
  int32_T c3_b_ia0;
  int32_T c3_b_lda;
  int32_T c3_i1421;
  real_T c3_c_B[16];
  int32_T c3_b_ib0;
  int32_T c3_b_ldb;
  int32_T c3_i1422;
  boolean_T c3_NON_UNIT_ALPHA;
  int32_T c3_a;
  int32_T c3_Aoffset;
  int32_T c3_b_a;
  int32_T c3_Boffset;
  int32_T c3_loop_ub;
  int32_T c3_j;
  int32_T c3_b_j;
  int32_T c3_c_a;
  int32_T c3_c;
  int32_T c3_d_a;
  int32_T c3_b;
  int32_T c3_b_c;
  int32_T c3_e_a;
  int32_T c3_b_b;
  int32_T c3_jBcol;
  int32_T c3_b_loop_ub;
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_f_a;
  int32_T c3_c_b;
  int32_T c3_c_c;
  int32_T c3_c_loop_ub;
  int32_T c3_c_j;
  int32_T c3_g_a;
  int32_T c3_d_c;
  int32_T c3_h_a;
  int32_T c3_d_b;
  int32_T c3_e_c;
  int32_T c3_i_a;
  int32_T c3_e_b;
  int32_T c3_d_loop_ub;
  int32_T c3_c_i;
  int32_T c3_j_a;
  int32_T c3_f_b;
  int32_T c3_f_c;
  int32_T c3_k_a;
  int32_T c3_g_b;
  int32_T c3_g_c;
  int32_T c3_c_m;
  int32_T c3_k;
  int32_T c3_b_k;
  int32_T c3_l_a;
  int32_T c3_h_c;
  int32_T c3_m_a;
  int32_T c3_h_b;
  int32_T c3_i_c;
  int32_T c3_n_a;
  int32_T c3_i_b;
  int32_T c3_kAcol;
  int32_T c3_o_a;
  int32_T c3_j_b;
  int32_T c3_j_c;
  int32_T c3_p_a;
  int32_T c3_k_b;
  int32_T c3_k_c;
  int32_T c3_q_a;
  int32_T c3_l_b;
  int32_T c3_l_c;
  int32_T c3_r_a;
  int32_T c3_m_b;
  int32_T c3_m_c;
  real_T c3_x;
  real_T c3_y;
  real_T c3_b_x;
  real_T c3_b_y;
  real_T c3_z;
  int32_T c3_s_a;
  int32_T c3_e_loop_ub;
  int32_T c3_d_i;
  int32_T c3_t_a;
  int32_T c3_n_b;
  int32_T c3_n_c;
  int32_T c3_u_a;
  int32_T c3_o_b;
  int32_T c3_o_c;
  int32_T c3_v_a;
  int32_T c3_p_b;
  int32_T c3_p_c;
  int32_T c3_w_a;
  int32_T c3_q_b;
  int32_T c3_q_c;
  for (c3_i1419 = 0; c3_i1419 < 16; c3_i1419 = c3_i1419 + 1) {
    c3_b_B[c3_i1419] = c3_B[c3_i1419];
  }

  c3_b_m = c3_m;
  c3_b_n = c3_n;
  c3_b_alpha1 = c3_alpha1;
  for (c3_i1420 = 0; c3_i1420 < 16; c3_i1420 = c3_i1420 + 1) {
    c3_b_A[c3_i1420] = c3_A[c3_i1420];
  }

  c3_b_ia0 = c3_ia0;
  c3_b_lda = c3_lda;
  for (c3_i1421 = 0; c3_i1421 < 16; c3_i1421 = c3_i1421 + 1) {
    c3_c_B[c3_i1421] = c3_b_B[c3_i1421];
  }

  c3_b_ib0 = c3_ib0;
  c3_b_ldb = c3_ldb;
  for (c3_i1422 = 0; c3_i1422 < 16; c3_i1422 = c3_i1422 + 1) {
    c3_b_B[c3_i1422] = c3_c_B[c3_i1422];
  }

  c3_NON_UNIT_ALPHA = (c3_b_alpha1 != 1.0);
  if ((real_T)c3_b_n == 0.0) {
  } else {
    c3_g_eml_scalar_eg(chartInstance);
    c3_a = c3_b_ia0;
    c3_Aoffset = c3_a - 1;
    c3_b_a = c3_b_ib0;
    c3_Boffset = c3_b_a - 1;
    if (c3_b_alpha1 == 0.0) {
      c3_loop_ub = c3_b_n;
      for (c3_j = 1; c3_j <= c3_loop_ub; c3_j = c3_j + 1) {
        c3_b_j = c3_j;
        c3_c_a = c3_b_j;
        c3_c = c3_c_a - 1;
        c3_d_a = c3_b_ldb;
        c3_b = c3_c;
        c3_b_c = c3_d_a * c3_b;
        c3_e_a = c3_Boffset;
        c3_b_b = c3_b_c;
        c3_jBcol = c3_e_a + c3_b_b;
        c3_b_loop_ub = c3_b_m;
        for (c3_i = 1; c3_i <= c3_b_loop_ub; c3_i = c3_i + 1) {
          c3_b_i = c3_i;
          c3_f_a = c3_b_i;
          c3_c_b = c3_jBcol;
          c3_c_c = c3_f_a + c3_c_b;
          c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_c_c), 1, 16, 1, 0) - 1] = 0.0;
        }
      }
    } else {
      c3_c_loop_ub = c3_b_n;
      for (c3_c_j = 1; c3_c_j <= c3_c_loop_ub; c3_c_j = c3_c_j + 1) {
        c3_b_j = c3_c_j;
        c3_g_a = c3_b_j;
        c3_d_c = c3_g_a - 1;
        c3_h_a = c3_b_ldb;
        c3_d_b = c3_d_c;
        c3_e_c = c3_h_a * c3_d_b;
        c3_i_a = c3_Boffset;
        c3_e_b = c3_e_c;
        c3_jBcol = c3_i_a + c3_e_b;
        if (c3_NON_UNIT_ALPHA) {
          c3_d_loop_ub = c3_b_m;
          for (c3_c_i = 1; c3_c_i <= c3_d_loop_ub; c3_c_i = c3_c_i + 1) {
            c3_b_i = c3_c_i;
            c3_j_a = c3_b_i;
            c3_f_b = c3_jBcol;
            c3_f_c = c3_j_a + c3_f_b;
            c3_k_a = c3_b_i;
            c3_g_b = c3_jBcol;
            c3_g_c = c3_k_a + c3_g_b;
            c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c3_f_c), 1, 16, 1, 0) - 1] = c3_b_alpha1 * c3_b_B[
              _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c3_g_c), 1, 16, 1, 0) - 1];
          }
        }

        c3_c_m = c3_b_m;
        for (c3_k = c3_c_m; c3_k > 0; c3_k = c3_k + -1) {
          c3_b_k = c3_k;
          c3_l_a = c3_b_k;
          c3_h_c = c3_l_a - 1;
          c3_m_a = c3_b_lda;
          c3_h_b = c3_h_c;
          c3_i_c = c3_m_a * c3_h_b;
          c3_n_a = c3_Aoffset;
          c3_i_b = c3_i_c;
          c3_kAcol = c3_n_a + c3_i_b;
          c3_o_a = c3_b_k;
          c3_j_b = c3_jBcol;
          c3_j_c = c3_o_a + c3_j_b;
          if (c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
               ("", (real_T)c3_j_c), 1, 16, 1, 0) - 1] != 0.0) {
            c3_p_a = c3_b_k;
            c3_k_b = c3_jBcol;
            c3_k_c = c3_p_a + c3_k_b;
            c3_q_a = c3_b_k;
            c3_l_b = c3_jBcol;
            c3_l_c = c3_q_a + c3_l_b;
            c3_r_a = c3_b_k;
            c3_m_b = c3_kAcol;
            c3_m_c = c3_r_a + c3_m_b;
            c3_x = c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c3_l_c), 1, 16, 1, 0) - 1];
            c3_y = c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c3_m_c), 1, 16, 1, 0) - 1];
            c3_b_x = c3_x;
            c3_b_y = c3_y;
            c3_z = c3_b_x / c3_b_y;
            c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c3_k_c), 1, 16, 1, 0) - 1] = c3_z;
            c3_s_a = c3_b_k;
            c3_e_loop_ub = c3_s_a - 1;
            for (c3_d_i = 1; c3_d_i <= c3_e_loop_ub; c3_d_i = c3_d_i + 1) {
              c3_b_i = c3_d_i;
              c3_t_a = c3_b_i;
              c3_n_b = c3_jBcol;
              c3_n_c = c3_t_a + c3_n_b;
              c3_u_a = c3_b_i;
              c3_o_b = c3_jBcol;
              c3_o_c = c3_u_a + c3_o_b;
              c3_v_a = c3_b_k;
              c3_p_b = c3_jBcol;
              c3_p_c = c3_v_a + c3_p_b;
              c3_w_a = c3_b_i;
              c3_q_b = c3_kAcol;
              c3_q_c = c3_w_a + c3_q_b;
              c3_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                ("", (real_T)c3_n_c), 1, 16, 1, 0) - 1] = c3_b_B[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c3_o_c), 1, 16, 1, 0) - 1] - c3_b_B[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c3_p_c), 1, 16, 1, 0) - 1] * c3_b_A[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c3_q_c), 1, 16, 1, 0) - 1];
            }
          }
        }
      }
    }
  }
}

static void c3_Adjoint(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_g[16], real_T c3_Adg[36])
{
  uint32_T c3_debug_family_var_map[6];
  static const char *c3_sv3[6] = { "R", "p", "nargin", "nargout", "g", "Adg" };

  real_T c3_R[9];
  real_T c3_p[3];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_y;
  real_T c3_k;
  real_T c3_b_k;
  boolean_T c3_b0;
  int32_T c3_i1423;
  int32_T c3_i1424;
  int32_T c3_i1425;
  int32_T c3_i1426;
  int32_T c3_i1427;
  int32_T c3_i1428;
  int32_T c3_i1429;
  real_T c3_w[3];
  uint32_T c3_b_debug_family_var_map[4];
  static const char *c3_sv4[4] = { "nargin", "nargout", "w", "wh" };

  real_T c3_b_nargin = 1.0;
  real_T c3_b_nargout = 1.0;
  real_T c3_wh[9];
  real_T c3_n;
  real_T c3_c_k;
  real_T c3_d_k;
  int32_T c3_i1430;
  real_T c3_a[9];
  int32_T c3_i1431;
  real_T c3_b[9];
  int32_T c3_i1432;
  real_T c3_A[9];
  int32_T c3_i1433;
  real_T c3_B[9];
  int32_T c3_i1434;
  real_T c3_b_A[9];
  int32_T c3_i1435;
  real_T c3_b_B[9];
  int32_T c3_i1436;
  real_T c3_c_A[9];
  int32_T c3_i1437;
  real_T c3_c_B[9];
  int32_T c3_i1438;
  int32_T c3_i1439;
  int32_T c3_i1440;
  real_T c3_b_y[9];
  int32_T c3_i1441;
  int32_T c3_i1442;
  int32_T c3_i1443;
  int32_T c3_i1444;
  int32_T c3_i1445;
  int32_T c3_i1446;
  int32_T c3_i1447;
  int32_T c3_i1448;
  int32_T c3_i1449;
  int32_T c3_i1450;
  int32_T c3_i1451;
  int32_T c3_i1452;
  int32_T c3_i1453;
  int32_T c3_i1454;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c3_sv3, c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c3_R, c3_g_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c3_p, c3_h_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c3_g, c3_i_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c3_Adg, c3_j_sf_marshall, 5U);
  CV_SCRIPT_FCN(4, 0);
  _SFD_SCRIPT_CALL(4, 2);
  c3_y = FALSE;
  c3_k = 1.0;
 label_1:
  ;
  if (c3_k <= 2.0) {
    c3_b_k = c3_k;
    c3_b0 = TRUE;
    if (!c3_b0) {
      c3_y = TRUE;
    } else {
      c3_k = c3_k + 1.0;
      goto label_1;
    }
  }

  CV_SCRIPT_IF(4, 0, c3_y);
  _SFD_SCRIPT_CALL(4, 5);
  for (c3_i1423 = 0; c3_i1423 < 36; c3_i1423 = c3_i1423 + 1) {
    c3_Adg[c3_i1423] = 0.0;
  }

  /* %%%%%%For embedded function, we should firstly define and initilize it */
  _SFD_SCRIPT_CALL(4, 7);
  c3_i1424 = 0;
  c3_i1425 = 0;
  for (c3_i1426 = 0; c3_i1426 < 3; c3_i1426 = c3_i1426 + 1) {
    for (c3_i1427 = 0; c3_i1427 < 3; c3_i1427 = c3_i1427 + 1) {
      c3_R[c3_i1427 + c3_i1424] = c3_g[c3_i1427 + c3_i1425];
    }

    c3_i1424 = c3_i1424 + 3;
    c3_i1425 = c3_i1425 + 4;
  }

  _SFD_SCRIPT_CALL(4, 8);
  for (c3_i1428 = 0; c3_i1428 < 3; c3_i1428 = c3_i1428 + 1) {
    c3_p[c3_i1428] = c3_g[c3_i1428 + 12];
  }

  _SFD_SCRIPT_CALL(4, 10);
  for (c3_i1429 = 0; c3_i1429 < 3; c3_i1429 = c3_i1429 + 1) {
    c3_w[c3_i1429] = c3_p[c3_i1429];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_sv4, c3_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_b_nargin, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_b_nargout, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_w, c3_h_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_wh, c3_g_sf_marshall, 3U);
  CV_SCRIPT_FCN(5, 0);
  _SFD_SCRIPT_CALL(5, 3);
  c3_n = 0.0;
  c3_c_k = 1.0;
 label_2:
  ;
  if (c3_c_k <= 2.0) {
    c3_d_k = c3_c_k;
    if (3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c3_d_k), 1, 2, 1, 0) - 1) == 0.0) {
      c3_n = 0.0;
    } else {
      if (3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c3_d_k), 1, 2, 1, 0) - 1) > c3_n) {
        c3_n = 3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c3_d_k), 1, 2, 1, 0) - 1);
      }

      c3_c_k = c3_c_k + 1.0;
      goto label_2;
    }
  }

  CV_SCRIPT_IF(5, 0, c3_n != 3.0);

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
  _SFD_SCRIPT_CALL(5, 20);
  c3_wh[0] = 0.0;
  c3_wh[3] = -c3_w[2];
  c3_wh[6] = c3_w[1];
  c3_wh[1] = c3_w[2];
  c3_wh[4] = 0.0;
  c3_wh[7] = -c3_w[0];
  c3_wh[2] = -c3_w[1];
  c3_wh[5] = c3_w[0];
  c3_wh[8] = 0.0;
  _SFD_SCRIPT_CALL(5, -20);
  sf_debug_symbol_scope_pop();
  for (c3_i1430 = 0; c3_i1430 < 9; c3_i1430 = c3_i1430 + 1) {
    c3_a[c3_i1430] = c3_wh[c3_i1430];
  }

  for (c3_i1431 = 0; c3_i1431 < 9; c3_i1431 = c3_i1431 + 1) {
    c3_b[c3_i1431] = c3_R[c3_i1431];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i1432 = 0; c3_i1432 < 9; c3_i1432 = c3_i1432 + 1) {
    c3_A[c3_i1432] = c3_a[c3_i1432];
  }

  for (c3_i1433 = 0; c3_i1433 < 9; c3_i1433 = c3_i1433 + 1) {
    c3_B[c3_i1433] = c3_b[c3_i1433];
  }

  for (c3_i1434 = 0; c3_i1434 < 9; c3_i1434 = c3_i1434 + 1) {
    c3_b_A[c3_i1434] = c3_A[c3_i1434];
  }

  for (c3_i1435 = 0; c3_i1435 < 9; c3_i1435 = c3_i1435 + 1) {
    c3_b_B[c3_i1435] = c3_B[c3_i1435];
  }

  for (c3_i1436 = 0; c3_i1436 < 9; c3_i1436 = c3_i1436 + 1) {
    c3_c_A[c3_i1436] = c3_b_A[c3_i1436];
  }

  for (c3_i1437 = 0; c3_i1437 < 9; c3_i1437 = c3_i1437 + 1) {
    c3_c_B[c3_i1437] = c3_b_B[c3_i1437];
  }

  for (c3_i1438 = 0; c3_i1438 < 3; c3_i1438 = c3_i1438 + 1) {
    c3_i1439 = 0;
    for (c3_i1440 = 0; c3_i1440 < 3; c3_i1440 = c3_i1440 + 1) {
      c3_b_y[c3_i1439 + c3_i1438] = 0.0;
      c3_i1441 = 0;
      for (c3_i1442 = 0; c3_i1442 < 3; c3_i1442 = c3_i1442 + 1) {
        c3_b_y[c3_i1439 + c3_i1438] = c3_b_y[c3_i1439 + c3_i1438] +
          c3_c_A[c3_i1441 + c3_i1438] * c3_c_B[c3_i1442 + c3_i1439];
        c3_i1441 = c3_i1441 + 3;
      }

      c3_i1439 = c3_i1439 + 3;
    }
  }

  c3_i1443 = 0;
  c3_i1444 = 0;
  for (c3_i1445 = 0; c3_i1445 < 3; c3_i1445 = c3_i1445 + 1) {
    for (c3_i1446 = 0; c3_i1446 < 3; c3_i1446 = c3_i1446 + 1) {
      c3_Adg[c3_i1446 + c3_i1443] = c3_R[c3_i1446 + c3_i1444];
    }

    c3_i1443 = c3_i1443 + 6;
    c3_i1444 = c3_i1444 + 3;
  }

  c3_i1447 = 0;
  c3_i1448 = 0;
  for (c3_i1449 = 0; c3_i1449 < 3; c3_i1449 = c3_i1449 + 1) {
    for (c3_i1450 = 0; c3_i1450 < 3; c3_i1450 = c3_i1450 + 1) {
      c3_Adg[(c3_i1450 + c3_i1447) + 18] = c3_b_y[c3_i1450 + c3_i1448];
    }

    c3_i1447 = c3_i1447 + 6;
    c3_i1448 = c3_i1448 + 3;
  }

  /* Adg = [R, skew(p)*R]; */
  _SFD_SCRIPT_CALL(4, 12);
  c3_i1451 = 0;
  c3_i1452 = 0;
  for (c3_i1453 = 0; c3_i1453 < 3; c3_i1453 = c3_i1453 + 1) {
    for (c3_i1454 = 0; c3_i1454 < 3; c3_i1454 = c3_i1454 + 1) {
      c3_Adg[(c3_i1454 + c3_i1451) + 21] = c3_R[c3_i1454 + c3_i1452];
    }

    c3_i1451 = c3_i1451 + 6;
    c3_i1452 = c3_i1452 + 3;
  }

  _SFD_SCRIPT_CALL(4, -12);
  sf_debug_symbol_scope_pop();
}

static void c3_h_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_eml_xgemm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  real_T c3_A[36], real_T c3_B[6], real_T c3_C[6],
  real_T c3_b_C[6])
{
  int32_T c3_i1455;
  real_T c3_b_A[36];
  int32_T c3_i1456;
  real_T c3_b_B[6];
  int32_T c3_i1457;
  real_T c3_c_A[36];
  int32_T c3_i1458;
  real_T c3_c_B[6];
  int32_T c3_i1459;
  int32_T c3_i1460;
  int32_T c3_i1461;
  for (c3_i1455 = 0; c3_i1455 < 36; c3_i1455 = c3_i1455 + 1) {
    c3_b_A[c3_i1455] = c3_A[c3_i1455];
  }

  for (c3_i1456 = 0; c3_i1456 < 6; c3_i1456 = c3_i1456 + 1) {
    c3_b_B[c3_i1456] = c3_B[c3_i1456];
  }

  for (c3_i1457 = 0; c3_i1457 < 36; c3_i1457 = c3_i1457 + 1) {
    c3_c_A[c3_i1457] = c3_b_A[c3_i1457];
  }

  for (c3_i1458 = 0; c3_i1458 < 6; c3_i1458 = c3_i1458 + 1) {
    c3_c_B[c3_i1458] = c3_b_B[c3_i1458];
  }

  for (c3_i1459 = 0; c3_i1459 < 6; c3_i1459 = c3_i1459 + 1) {
    c3_b_C[c3_i1459] = 0.0;
    c3_i1460 = 0;
    for (c3_i1461 = 0; c3_i1461 < 6; c3_i1461 = c3_i1461 + 1) {
      c3_b_C[c3_i1459] = c3_b_C[c3_i1459] + c3_c_A[c3_i1460 + c3_i1459] *
        c3_c_B[c3_i1461];
      c3_i1460 = c3_i1460 + 6;
    }
  }
}

static void c3_ad(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance, real_T
                  c3_xi[6], real_T c3_adx[36])
{
  uint32_T c3_debug_family_var_map[6];
  static const char *c3_sv5[6] = { "w", "v", "nargin", "nargout", "xi", "adx" };

  real_T c3_w[3];
  real_T c3_v[3];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  int32_T c3_i1462;
  int32_T c3_i1463;
  int32_T c3_i1464;
  real_T c3_b_w[3];
  uint32_T c3_b_debug_family_var_map[4];
  static const char *c3_sv6[4] = { "nargin", "nargout", "w", "W" };

  real_T c3_b_nargin = 1.0;
  real_T c3_b_nargout = 1.0;
  real_T c3_W[9];
  int32_T c3_i1465;
  real_T c3_c_w[3];
  uint32_T c3_c_debug_family_var_map[4];
  real_T c3_c_nargin = 1.0;
  real_T c3_c_nargout = 1.0;
  real_T c3_b_W[9];
  int32_T c3_i1466;
  real_T c3_d_w[3];
  uint32_T c3_d_debug_family_var_map[4];
  real_T c3_d_nargin = 1.0;
  real_T c3_d_nargout = 1.0;
  real_T c3_c_W[9];
  int32_T c3_i1467;
  int32_T c3_i1468;
  int32_T c3_i1469;
  int32_T c3_i1470;
  int32_T c3_i1471;
  int32_T c3_i1472;
  int32_T c3_i1473;
  int32_T c3_i1474;
  int32_T c3_i1475;
  int32_T c3_i1476;
  int32_T c3_i1477;
  int32_T c3_i1478;
  int32_T c3_i1479;
  int32_T c3_i1480;
  int32_T c3_i1481;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c3_sv5, c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c3_w, c3_h_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c3_v, c3_h_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c3_xi, c3_b_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c3_adx, c3_j_sf_marshall, 5U);
  CV_SCRIPT_FCN(6, 0);
  _SFD_SCRIPT_CALL(6, 2);
  for (c3_i1462 = 0; c3_i1462 < 3; c3_i1462 = c3_i1462 + 1) {
    c3_w[c3_i1462] = c3_xi[c3_i1462 + 3];
  }

  _SFD_SCRIPT_CALL(6, 3);
  for (c3_i1463 = 0; c3_i1463 < 3; c3_i1463 = c3_i1463 + 1) {
    c3_v[c3_i1463] = c3_xi[c3_i1463];
  }

  _SFD_SCRIPT_CALL(6, 5);
  for (c3_i1464 = 0; c3_i1464 < 3; c3_i1464 = c3_i1464 + 1) {
    c3_b_w[c3_i1464] = c3_w[c3_i1464];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_sv6, c3_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_b_nargin, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_b_nargout, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_b_w, c3_h_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_W, c3_g_sf_marshall, 3U);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3, 2);
  c3_W[0] = 0.0;
  c3_W[3] = -c3_b_w[2];
  c3_W[6] = c3_b_w[1];
  c3_W[1] = c3_b_w[2];
  c3_W[4] = 0.0;
  c3_W[7] = -c3_b_w[0];
  c3_W[2] = -c3_b_w[1];
  c3_W[5] = c3_b_w[0];
  c3_W[8] = 0.0;
  _SFD_SCRIPT_CALL(3, -2);
  sf_debug_symbol_scope_pop();
  for (c3_i1465 = 0; c3_i1465 < 3; c3_i1465 = c3_i1465 + 1) {
    c3_c_w[c3_i1465] = c3_v[c3_i1465];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_sv6, c3_c_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_c_nargin, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_c_nargout, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_c_w, c3_h_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_b_W, c3_g_sf_marshall, 3U);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3, 2);
  c3_b_W[0] = 0.0;
  c3_b_W[3] = -c3_c_w[2];
  c3_b_W[6] = c3_c_w[1];
  c3_b_W[1] = c3_c_w[2];
  c3_b_W[4] = 0.0;
  c3_b_W[7] = -c3_c_w[0];
  c3_b_W[2] = -c3_c_w[1];
  c3_b_W[5] = c3_c_w[0];
  c3_b_W[8] = 0.0;
  _SFD_SCRIPT_CALL(3, -2);
  sf_debug_symbol_scope_pop();
  for (c3_i1466 = 0; c3_i1466 < 3; c3_i1466 = c3_i1466 + 1) {
    c3_d_w[c3_i1466] = c3_w[c3_i1466];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_sv6, c3_d_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_d_nargin, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_d_nargout, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_d_w, c3_h_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_c_W, c3_g_sf_marshall, 3U);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3, 2);
  c3_c_W[0] = 0.0;
  c3_c_W[3] = -c3_d_w[2];
  c3_c_W[6] = c3_d_w[1];
  c3_c_W[1] = c3_d_w[2];
  c3_c_W[4] = 0.0;
  c3_c_W[7] = -c3_d_w[0];
  c3_c_W[2] = -c3_d_w[1];
  c3_c_W[5] = c3_d_w[0];
  c3_c_W[8] = 0.0;
  _SFD_SCRIPT_CALL(3, -2);
  sf_debug_symbol_scope_pop();
  c3_i1467 = 0;
  c3_i1468 = 0;
  for (c3_i1469 = 0; c3_i1469 < 3; c3_i1469 = c3_i1469 + 1) {
    for (c3_i1470 = 0; c3_i1470 < 3; c3_i1470 = c3_i1470 + 1) {
      c3_adx[c3_i1470 + c3_i1467] = c3_W[c3_i1470 + c3_i1468];
    }

    c3_i1467 = c3_i1467 + 6;
    c3_i1468 = c3_i1468 + 3;
  }

  c3_i1471 = 0;
  c3_i1472 = 0;
  for (c3_i1473 = 0; c3_i1473 < 3; c3_i1473 = c3_i1473 + 1) {
    for (c3_i1474 = 0; c3_i1474 < 3; c3_i1474 = c3_i1474 + 1) {
      c3_adx[(c3_i1474 + c3_i1471) + 18] = c3_b_W[c3_i1474 + c3_i1472];
    }

    c3_i1471 = c3_i1471 + 6;
    c3_i1472 = c3_i1472 + 3;
  }

  c3_i1475 = 0;
  for (c3_i1476 = 0; c3_i1476 < 3; c3_i1476 = c3_i1476 + 1) {
    for (c3_i1477 = 0; c3_i1477 < 3; c3_i1477 = c3_i1477 + 1) {
      c3_adx[(c3_i1477 + c3_i1475) + 3] = 0.0;
    }

    c3_i1475 = c3_i1475 + 6;
  }

  c3_i1478 = 0;
  c3_i1479 = 0;
  for (c3_i1480 = 0; c3_i1480 < 3; c3_i1480 = c3_i1480 + 1) {
    for (c3_i1481 = 0; c3_i1481 < 3; c3_i1481 = c3_i1481 + 1) {
      c3_adx[(c3_i1481 + c3_i1478) + 21] = c3_c_W[c3_i1481 + c3_i1479];
    }

    c3_i1478 = c3_i1478 + 6;
    c3_i1479 = c3_i1479 + 3;
  }

  _SFD_SCRIPT_CALL(6, -5);
  sf_debug_symbol_scope_pop();
}

static void c3_i_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static void c3_ceval_xgemm(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, int32_T c3_k, real_T
  c3_alpha1, real_T c3_A[36], int32_T c3_ia0, int32_T c3_lda, real_T c3_B[36],
  int32_T c3_ib0, int32_T c3_ldb, real_T c3_beta1, real_T
  c3_C[36], int32_T c3_ic0, int32_T c3_ldc, real_T c3_b_C[36])
{
  char_T c3_TRANSA;
  char_T c3_TRANSB;
  int32_T c3_i1482;
  c3_TRANSA = 'N';
  c3_TRANSB = 'N';
  for (c3_i1482 = 0; c3_i1482 < 36; c3_i1482 = c3_i1482 + 1) {
    c3_b_C[c3_i1482] = c3_C[c3_i1482];
  }

  dgemm32(&c3_TRANSA, &c3_TRANSB, &c3_m, &c3_n, &c3_k, &c3_alpha1,
          &c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
            "", (real_T)c3_ia0), 1, 36, 1, 0) - 1], &c3_lda,
          &c3_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)
            c3_ib0), 1, 36, 1, 0) - 1], &c3_ldb, &c3_beta1,
          &c3_b_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)
            c3_ic0), 1, 36, 1, 0) - 1], &c3_ldc);
}

static void c3_j_eml_scalar_eg(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

static real_T c3_ceval_xdot(SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance,
  int32_T c3_n, real_T c3_x[6], int32_T c3_ix0,
  int32_T c3_incx, real_T c3_y[6], int32_T c3_iy0, int32_T c3_incy)
{
  real_T c3_d;
  c3_d = 0.0;
  if ((real_T)c3_n > 0.0) {
    return ddot32(&c3_n, &c3_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 6, 1, 0) - 1], &
                  c3_incx, &c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c3_iy0), 1, 6, 1, 0) - 1], &c3_incy);
  }

  return c3_d;
}

static const mxArray *c3_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1483;
  real_T c3_b_u[36];
  int32_T c3_i1484;
  real_T c3_c_u[36];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1483 = 0; c3_i1483 < 36; c3_i1483 = c3_i1483 + 1) {
    c3_b_u[c3_i1483] = (*((real_T (*)[36])c3_u))[c3_i1483];
  }

  for (c3_i1484 = 0; c3_i1484 < 36; c3_i1484 = c3_i1484 + 1) {
    c3_c_u[c3_i1484] = c3_b_u[c3_i1484];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 36));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_b_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1485;
  real_T c3_b_u[6];
  int32_T c3_i1486;
  real_T c3_c_u[6];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1485 = 0; c3_i1485 < 6; c3_i1485 = c3_i1485 + 1) {
    c3_b_u[c3_i1485] = (*((real_T (*)[6])c3_u))[c3_i1485];
  }

  for (c3_i1486 = 0; c3_i1486 < 6; c3_i1486 = c3_i1486 + 1) {
    c3_c_u[c3_i1486] = c3_b_u[c3_i1486];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 6));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_c_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1487;
  real_T c3_b_u[54];
  int32_T c3_i1488;
  real_T c3_c_u[54];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1487 = 0; c3_i1487 < 54; c3_i1487 = c3_i1487 + 1) {
    c3_b_u[c3_i1487] = (*((real_T (*)[54])c3_u))[c3_i1487];
  }

  for (c3_i1488 = 0; c3_i1488 < 54; c3_i1488 = c3_i1488 + 1) {
    c3_c_u[c3_i1488] = c3_b_u[c3_i1488];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 54));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_d_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1489;
  real_T c3_b_u[18];
  int32_T c3_i1490;
  real_T c3_c_u[18];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1489 = 0; c3_i1489 < 18; c3_i1489 = c3_i1489 + 1) {
    c3_b_u[c3_i1489] = (*((real_T (*)[18])c3_u))[c3_i1489];
  }

  for (c3_i1490 = 0; c3_i1490 < 18; c3_i1490 = c3_i1490 + 1) {
    c3_c_u[c3_i1490] = c3_b_u[c3_i1490];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 18));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_e_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1491;
  int32_T c3_i1492;
  int32_T c3_i1493;
  real_T c3_b_u[28];
  int32_T c3_i1494;
  int32_T c3_i1495;
  int32_T c3_i1496;
  real_T c3_c_u[28];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_i1491 = 0;
  for (c3_i1492 = 0; c3_i1492 < 7; c3_i1492 = c3_i1492 + 1) {
    for (c3_i1493 = 0; c3_i1493 < 4; c3_i1493 = c3_i1493 + 1) {
      c3_b_u[c3_i1493 + c3_i1491] = (*((real_T (*)[28])c3_u))[c3_i1493 +
        c3_i1491];
    }

    c3_i1491 = c3_i1491 + 4;
  }

  c3_i1494 = 0;
  for (c3_i1495 = 0; c3_i1495 < 7; c3_i1495 = c3_i1495 + 1) {
    for (c3_i1496 = 0; c3_i1496 < 4; c3_i1496 = c3_i1496 + 1) {
      c3_c_u[c3_i1496 + c3_i1494] = c3_b_u[c3_i1496 + c3_i1494];
    }

    c3_i1494 = c3_i1494 + 4;
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 2, 4, 7));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_f_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  real_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_b_u = *((real_T *)c3_u);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_g_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1497;
  int32_T c3_i1498;
  int32_T c3_i1499;
  real_T c3_b_u[9];
  int32_T c3_i1500;
  int32_T c3_i1501;
  int32_T c3_i1502;
  real_T c3_c_u[9];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_i1497 = 0;
  for (c3_i1498 = 0; c3_i1498 < 3; c3_i1498 = c3_i1498 + 1) {
    for (c3_i1499 = 0; c3_i1499 < 3; c3_i1499 = c3_i1499 + 1) {
      c3_b_u[c3_i1499 + c3_i1497] = (*((real_T (*)[9])c3_u))[c3_i1499 + c3_i1497];
    }

    c3_i1497 = c3_i1497 + 3;
  }

  c3_i1500 = 0;
  for (c3_i1501 = 0; c3_i1501 < 3; c3_i1501 = c3_i1501 + 1) {
    for (c3_i1502 = 0; c3_i1502 < 3; c3_i1502 = c3_i1502 + 1) {
      c3_c_u[c3_i1502 + c3_i1500] = c3_b_u[c3_i1502 + c3_i1500];
    }

    c3_i1500 = c3_i1500 + 3;
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 2, 3, 3));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_h_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1503;
  real_T c3_b_u[3];
  int32_T c3_i1504;
  real_T c3_c_u[3];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1503 = 0; c3_i1503 < 3; c3_i1503 = c3_i1503 + 1) {
    c3_b_u[c3_i1503] = (*((real_T (*)[3])c3_u))[c3_i1503];
  }

  for (c3_i1504 = 0; c3_i1504 < 3; c3_i1504 = c3_i1504 + 1) {
    c3_c_u[c3_i1504] = c3_b_u[c3_i1504];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 3));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_i_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1505;
  int32_T c3_i1506;
  int32_T c3_i1507;
  real_T c3_b_u[16];
  int32_T c3_i1508;
  int32_T c3_i1509;
  int32_T c3_i1510;
  real_T c3_c_u[16];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_i1505 = 0;
  for (c3_i1506 = 0; c3_i1506 < 4; c3_i1506 = c3_i1506 + 1) {
    for (c3_i1507 = 0; c3_i1507 < 4; c3_i1507 = c3_i1507 + 1) {
      c3_b_u[c3_i1507 + c3_i1505] = (*((real_T (*)[16])c3_u))[c3_i1507 +
        c3_i1505];
    }

    c3_i1505 = c3_i1505 + 4;
  }

  c3_i1508 = 0;
  for (c3_i1509 = 0; c3_i1509 < 4; c3_i1509 = c3_i1509 + 1) {
    for (c3_i1510 = 0; c3_i1510 < 4; c3_i1510 = c3_i1510 + 1) {
      c3_c_u[c3_i1510 + c3_i1508] = c3_b_u[c3_i1510 + c3_i1508];
    }

    c3_i1508 = c3_i1508 + 4;
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 2, 4, 4));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_j_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1511;
  int32_T c3_i1512;
  int32_T c3_i1513;
  real_T c3_b_u[36];
  int32_T c3_i1514;
  int32_T c3_i1515;
  int32_T c3_i1516;
  real_T c3_c_u[36];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_i1511 = 0;
  for (c3_i1512 = 0; c3_i1512 < 6; c3_i1512 = c3_i1512 + 1) {
    for (c3_i1513 = 0; c3_i1513 < 6; c3_i1513 = c3_i1513 + 1) {
      c3_b_u[c3_i1513 + c3_i1511] = (*((real_T (*)[36])c3_u))[c3_i1513 +
        c3_i1511];
    }

    c3_i1511 = c3_i1511 + 6;
  }

  c3_i1514 = 0;
  for (c3_i1515 = 0; c3_i1515 < 6; c3_i1515 = c3_i1515 + 1) {
    for (c3_i1516 = 0; c3_i1516 < 6; c3_i1516 = c3_i1516 + 1) {
      c3_c_u[c3_i1516 + c3_i1514] = c3_b_u[c3_i1516 + c3_i1514];
    }

    c3_i1514 = c3_i1514 + 6;
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 2, 6, 6));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_k_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1517;
  real_T c3_b_u[4];
  int32_T c3_i1518;
  real_T c3_c_u[4];
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1517 = 0; c3_i1517 < 4; c3_i1517 = c3_i1517 + 1) {
    c3_b_u[c3_i1517] = (*((real_T (*)[4])c3_u))[c3_i1517];
  }

  for (c3_i1518 = 0; c3_i1518 < 4; c3_i1518 = c3_i1518 + 1) {
    c3_c_u[c3_i1518] = c3_b_u[c3_i1518];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 4));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

const mxArray *sf_c3_EulerPIDJoint_Copy_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_ResolvedFunctionInfo c3_info[115];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i1519;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  c3_b_info_helper(c3_info);
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 115));
  for (c3_i1519 = 0; c3_i1519 < 115; c3_i1519 = c3_i1519 + 1) {
    c3_r0 = &c3_info[c3_i1519];
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context",
                    "nameCaptureInfo", c3_i1519);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name",
                    "nameCaptureInfo", c3_i1519);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c3_i1519);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c3_i1519);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c3_i1519);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo",
                    c3_i1519);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo",
                    c3_i1519);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m0);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[115])
{
  c3_info[0].context = "";
  c3_info[0].name = "zeros";
  c3_info[0].dominantType = "double";
  c3_info[0].resolved = "[B]zeros";
  c3_info[0].fileLength = 0U;
  c3_info[0].fileTime1 = 0U;
  c3_info[0].fileTime2 = 0U;
  c3_info[1].context = "";
  c3_info[1].name = "DynEulerCon";
  c3_info[1].dominantType = "double";
  c3_info[1].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/DynEulerCon.m";
  c3_info[1].fileLength = 5871U;
  c3_info[1].fileTime1 = 1420090649U;
  c3_info[1].fileTime2 = 0U;
  c3_info[2].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEulerCon.m";
  c3_info[2].name = "expg";
  c3_info[2].dominantType = "double";
  c3_info[2].resolved =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m";
  c3_info[2].fileLength = 297U;
  c3_info[2].fileTime1 = 1365051648U;
  c3_info[2].fileTime2 = 0U;
  c3_info[3].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m";
  c3_info[3].name = "norm";
  c3_info[3].dominantType = "double";
  c3_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[3].fileLength = 5453U;
  c3_info[3].fileTime1 = 1271384008U;
  c3_info[3].fileTime2 = 0U;
  c3_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[4].name = "nargin";
  c3_info[4].dominantType = "";
  c3_info[4].resolved = "[B]nargin";
  c3_info[4].fileLength = 0U;
  c3_info[4].fileTime1 = 0U;
  c3_info[4].fileTime2 = 0U;
  c3_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[5].name = "gt";
  c3_info[5].dominantType = "double";
  c3_info[5].resolved = "[B]gt";
  c3_info[5].fileLength = 0U;
  c3_info[5].fileTime1 = 0U;
  c3_info[5].fileTime2 = 0U;
  c3_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[6].name = "isa";
  c3_info[6].dominantType = "double";
  c3_info[6].resolved = "[B]isa";
  c3_info[6].fileLength = 0U;
  c3_info[6].fileTime1 = 0U;
  c3_info[6].fileTime2 = 0U;
  c3_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[7].name = "ndims";
  c3_info[7].dominantType = "double";
  c3_info[7].resolved = "[B]ndims";
  c3_info[7].fileLength = 0U;
  c3_info[7].fileTime1 = 0U;
  c3_info[7].fileTime2 = 0U;
  c3_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[8].name = "le";
  c3_info[8].dominantType = "double";
  c3_info[8].resolved = "[B]le";
  c3_info[8].fileLength = 0U;
  c3_info[8].fileTime1 = 0U;
  c3_info[8].fileTime2 = 0U;
  c3_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[9].name = "eq";
  c3_info[9].dominantType = "double";
  c3_info[9].resolved = "[B]eq";
  c3_info[9].fileLength = 0U;
  c3_info[9].fileTime1 = 0U;
  c3_info[9].fileTime2 = 0U;
  c3_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[10].name = "lt";
  c3_info[10].dominantType = "double";
  c3_info[10].resolved = "[B]lt";
  c3_info[10].fileLength = 0U;
  c3_info[10].fileTime1 = 0U;
  c3_info[10].fileTime2 = 0U;
  c3_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[11].name = "size";
  c3_info[11].dominantType = "double";
  c3_info[11].resolved = "[B]size";
  c3_info[11].fileLength = 0U;
  c3_info[11].fileTime1 = 0U;
  c3_info[11].fileTime2 = 0U;
  c3_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[12].name = "isempty";
  c3_info[12].dominantType = "double";
  c3_info[12].resolved = "[B]isempty";
  c3_info[12].fileLength = 0U;
  c3_info[12].fileTime1 = 0U;
  c3_info[12].fileTime2 = 0U;
  c3_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[13].name = "isscalar";
  c3_info[13].dominantType = "double";
  c3_info[13].resolved = "[B]isscalar";
  c3_info[13].fileLength = 0U;
  c3_info[13].fileTime1 = 0U;
  c3_info[13].fileTime2 = 0U;
  c3_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[14].name = "isvector";
  c3_info[14].dominantType = "double";
  c3_info[14].resolved = "[B]isvector";
  c3_info[14].fileLength = 0U;
  c3_info[14].fileTime1 = 0U;
  c3_info[14].fileTime2 = 0U;
  c3_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c3_info[15].name = "eml_index_class";
  c3_info[15].dominantType = "";
  c3_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[15].fileLength = 909U;
  c3_info[15].fileTime1 = 1192445182U;
  c3_info[15].fileTime2 = 0U;
  c3_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c3_info[16].name = "ones";
  c3_info[16].dominantType = "char";
  c3_info[16].resolved = "[B]ones";
  c3_info[16].fileLength = 0U;
  c3_info[16].fileTime1 = 0U;
  c3_info[16].fileTime2 = 0U;
  c3_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c3_info[17].name = "ischar";
  c3_info[17].dominantType = "double";
  c3_info[17].resolved = "[B]ischar";
  c3_info[17].fileLength = 0U;
  c3_info[17].fileTime1 = 0U;
  c3_info[17].fileTime2 = 0U;
  c3_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c3_info[18].name = "eml_xnrm2";
  c3_info[18].dominantType = "int32";
  c3_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c3_info[18].fileLength = 718U;
  c3_info[18].fileTime1 = 1209309256U;
  c3_info[18].fileTime2 = 0U;
  c3_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_use_refblas.m";
  c3_info[19].name = "strcmp";
  c3_info[19].dominantType = "char";
  c3_info[19].resolved = "[B]strcmp";
  c3_info[19].fileLength = 0U;
  c3_info[19].fileTime1 = 0U;
  c3_info[19].fileTime2 = 0U;
  c3_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c3_info[20].name = "cast";
  c3_info[20].dominantType = "double";
  c3_info[20].resolved = "[B]cast";
  c3_info[20].fileLength = 0U;
  c3_info[20].fileTime1 = 0U;
  c3_info[20].fileTime2 = 0U;
  c3_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c3_info[21].name = "eml_refblas_xnrm2";
  c3_info[21].dominantType = "int32";
  c3_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[21].fileLength = 1433U;
  c3_info[21].fileTime1 = 1240240442U;
  c3_info[21].fileTime2 = 0U;
  c3_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[22].name = "class";
  c3_info[22].dominantType = "double";
  c3_info[22].resolved = "[B]class";
  c3_info[22].fileLength = 0U;
  c3_info[22].fileTime1 = 0U;
  c3_info[22].fileTime2 = 0U;
  c3_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[23].name = "true";
  c3_info[23].dominantType = "";
  c3_info[23].resolved = "[B]true";
  c3_info[23].fileLength = 0U;
  c3_info[23].fileTime1 = 0U;
  c3_info[23].fileTime2 = 0U;
  c3_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[24].name = "eml_index_minus";
  c3_info[24].dominantType = "int32";
  c3_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[24].fileLength = 277U;
  c3_info[24].fileTime1 = 1192445184U;
  c3_info[24].fileTime2 = 0U;
  c3_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[25].name = "eml_index_times";
  c3_info[25].dominantType = "int32";
  c3_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c3_info[25].fileLength = 280U;
  c3_info[25].fileTime1 = 1192445186U;
  c3_info[25].fileTime2 = 0U;
  c3_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[26].name = "eml_index_plus";
  c3_info[26].dominantType = "int32";
  c3_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[26].fileLength = 272U;
  c3_info[26].fileTime1 = 1192445184U;
  c3_info[26].fileTime2 = 0U;
  c3_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[27].name = "real";
  c3_info[27].dominantType = "double";
  c3_info[27].resolved = "[B]real";
  c3_info[27].fileLength = 0U;
  c3_info[27].fileTime1 = 0U;
  c3_info[27].fileTime2 = 0U;
  c3_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[28].name = "ne";
  c3_info[28].dominantType = "double";
  c3_info[28].resolved = "[B]ne";
  c3_info[28].fileLength = 0U;
  c3_info[28].fileTime1 = 0U;
  c3_info[28].fileTime2 = 0U;
  c3_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[29].name = "abs";
  c3_info[29].dominantType = "double";
  c3_info[29].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[29].fileLength = 566U;
  c3_info[29].fileTime1 = 1221245532U;
  c3_info[29].fileTime2 = 0U;
  c3_info[30].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[30].name = "islogical";
  c3_info[30].dominantType = "double";
  c3_info[30].resolved = "[B]islogical";
  c3_info[30].fileLength = 0U;
  c3_info[30].fileTime1 = 0U;
  c3_info[30].fileTime2 = 0U;
  c3_info[31].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[31].name = "eml_scalar_abs";
  c3_info[31].dominantType = "double";
  c3_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[31].fileLength = 461U;
  c3_info[31].fileTime1 = 1203422760U;
  c3_info[31].fileTime2 = 0U;
  c3_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[32].name = "isinteger";
  c3_info[32].dominantType = "double";
  c3_info[32].resolved = "[B]isinteger";
  c3_info[32].fileLength = 0U;
  c3_info[32].fileTime1 = 0U;
  c3_info[32].fileTime2 = 0U;
  c3_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[33].name = "isreal";
  c3_info[33].dominantType = "double";
  c3_info[33].resolved = "[B]isreal";
  c3_info[33].fileLength = 0U;
  c3_info[33].fileTime1 = 0U;
  c3_info[33].fileTime2 = 0U;
  c3_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[34].name = "false";
  c3_info[34].dominantType = "";
  c3_info[34].resolved = "[B]false";
  c3_info[34].fileLength = 0U;
  c3_info[34].fileTime1 = 0U;
  c3_info[34].fileTime2 = 0U;
  c3_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[35].name = "times";
  c3_info[35].dominantType = "double";
  c3_info[35].resolved = "[B]times";
  c3_info[35].fileLength = 0U;
  c3_info[35].fileTime1 = 0U;
  c3_info[35].fileTime2 = 0U;
  c3_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[36].name = "plus";
  c3_info[36].dominantType = "double";
  c3_info[36].resolved = "[B]plus";
  c3_info[36].fileLength = 0U;
  c3_info[36].fileTime1 = 0U;
  c3_info[36].fileTime2 = 0U;
  c3_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c3_info[37].name = "imag";
  c3_info[37].dominantType = "double";
  c3_info[37].resolved = "[B]imag";
  c3_info[37].fileLength = 0U;
  c3_info[37].fileTime1 = 0U;
  c3_info[37].fileTime2 = 0U;
  c3_info[38].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m";
  c3_info[38].name = "eps";
  c3_info[38].dominantType = "";
  c3_info[38].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[38].fileLength = 1331U;
  c3_info[38].fileTime1 = 1246588112U;
  c3_info[38].fileTime2 = 0U;
  c3_info[39].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[39].name = "eml_is_float_class";
  c3_info[39].dominantType = "char";
  c3_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c3_info[39].fileLength = 226U;
  c3_info[39].fileTime1 = 1197825240U;
  c3_info[39].fileTime2 = 0U;
  c3_info[40].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[40].name = "uminus";
  c3_info[40].dominantType = "double";
  c3_info[40].resolved = "[B]uminus";
  c3_info[40].fileLength = 0U;
  c3_info[40].fileTime1 = 0U;
  c3_info[40].fileTime2 = 0U;
  c3_info[41].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m";
  c3_info[41].name = "eye";
  c3_info[41].dominantType = "double";
  c3_info[41].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c3_info[41].fileLength = 1765U;
  c3_info[41].fileTime1 = 1219731288U;
  c3_info[41].fileTime2 = 0U;
  c3_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c3_info[42].name = "eml_assert_valid_size_arg";
  c3_info[42].dominantType = "double";
  c3_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[42].fileLength = 3315U;
  c3_info[42].fileTime1 = 1256367816U;
  c3_info[42].fileTime2 = 0U;
  c3_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isVariableSizing";
  c3_info[43].name = "not";
  c3_info[43].dominantType = "logical";
  c3_info[43].resolved = "[B]not";
  c3_info[43].fileLength = 0U;
  c3_info[43].fileTime1 = 0U;
  c3_info[43].fileTime2 = 0U;
  c3_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c3_info[44].name = "isinf";
  c3_info[44].dominantType = "double";
  c3_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c3_info[44].fileLength = 541U;
  c3_info[44].fileTime1 = 1271383988U;
  c3_info[44].fileTime2 = 0U;
  c3_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c3_info[45].name = "double";
  c3_info[45].dominantType = "double";
  c3_info[45].resolved = "[B]double";
  c3_info[45].fileLength = 0U;
  c3_info[45].fileTime1 = 0U;
  c3_info[45].fileTime2 = 0U;
  c3_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c3_info[46].name = "mtimes";
  c3_info[46].dominantType = "double";
  c3_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[46].fileLength = 3425U;
  c3_info[46].fileTime1 = 1251010272U;
  c3_info[46].fileTime2 = 0U;
  c3_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[47].name = "intmax";
  c3_info[47].dominantType = "char";
  c3_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[47].fileLength = 1535U;
  c3_info[47].fileTime1 = 1192445128U;
  c3_info[47].fileTime2 = 0U;
  c3_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[48].name = "int32";
  c3_info[48].dominantType = "double";
  c3_info[48].resolved = "[B]int32";
  c3_info[48].fileLength = 0U;
  c3_info[48].fileTime1 = 0U;
  c3_info[48].fileTime2 = 0U;
  c3_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c3_info[49].name = "min";
  c3_info[49].dominantType = "double";
  c3_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[49].fileLength = 362U;
  c3_info[49].fileTime1 = 1245080764U;
  c3_info[49].fileTime2 = 0U;
  c3_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[50].name = "nargout";
  c3_info[50].dominantType = "";
  c3_info[50].resolved = "[B]nargout";
  c3_info[50].fileLength = 0U;
  c3_info[50].fileTime1 = 0U;
  c3_info[50].fileTime2 = 0U;
  c3_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[51].name = "eml_min_or_max";
  c3_info[51].dominantType = "char";
  c3_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c3_info[51].fileLength = 9967U;
  c3_info[51].fileTime1 = 1261926670U;
  c3_info[51].fileTime2 = 0U;
  c3_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c3_info[52].name = "isnumeric";
  c3_info[52].dominantType = "double";
  c3_info[52].resolved = "[B]isnumeric";
  c3_info[52].fileLength = 0U;
  c3_info[52].fileTime1 = 0U;
  c3_info[52].fileTime2 = 0U;
  c3_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[53].name = "eml_scalar_eg";
  c3_info[53].dominantType = "double";
  c3_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[53].fileLength = 3068U;
  c3_info[53].fileTime1 = 1240240410U;
  c3_info[53].fileTime2 = 0U;
  c3_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[54].name = "isstruct";
  c3_info[54].dominantType = "double";
  c3_info[54].resolved = "[B]isstruct";
  c3_info[54].fileLength = 0U;
  c3_info[54].fileTime1 = 0U;
  c3_info[54].fileTime2 = 0U;
  c3_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[55].name = "eml_scalexp_alloc";
  c3_info[55].dominantType = "double";
  c3_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c3_info[55].fileLength = 932U;
  c3_info[55].fileTime1 = 1261926670U;
  c3_info[55].fileTime2 = 0U;
  c3_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c3_info[56].name = "minus";
  c3_info[56].dominantType = "double";
  c3_info[56].resolved = "[B]minus";
  c3_info[56].fileLength = 0U;
  c3_info[56].fileTime1 = 0U;
  c3_info[56].fileTime2 = 0U;
  c3_info[57].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m";
  c3_info[57].name = "mrdivide";
  c3_info[57].dominantType = "double";
  c3_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[57].fileLength = 432U;
  c3_info[57].fileTime1 = 1277726622U;
  c3_info[57].fileTime2 = 0U;
  c3_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[58].name = "ge";
  c3_info[58].dominantType = "double";
  c3_info[58].resolved = "[B]ge";
  c3_info[58].fileLength = 0U;
  c3_info[58].fileTime1 = 0U;
  c3_info[58].fileTime2 = 0U;
  c3_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[59].name = "rdivide";
  c3_info[59].dominantType = "double";
  c3_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[59].fileLength = 403U;
  c3_info[59].fileTime1 = 1245080820U;
  c3_info[59].fileTime2 = 0U;
  c3_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[60].name = "eml_div";
  c3_info[60].dominantType = "double";
  c3_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c3_info[60].fileLength = 4918U;
  c3_info[60].fileTime1 = 1267038210U;
  c3_info[60].fileTime2 = 0U;
  c3_info[61].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m";
  c3_info[61].name = "expr";
  c3_info[61].dominantType = "double";
  c3_info[61].resolved =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expr.m";
  c3_info[61].fileLength = 191U;
  c3_info[61].fileTime1 = 1386474448U;
  c3_info[61].fileTime2 = 0U;
  c3_info[62].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expr.m";
  c3_info[62].name = "hat";
  c3_info[62].dominantType = "double";
  c3_info[62].resolved =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/hat.m";
  c3_info[62].fileLength = 88U;
  c3_info[62].fileTime1 = 1346208402U;
  c3_info[62].fileTime2 = 0U;
  c3_info[63].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expr.m";
  c3_info[63].name = "sin";
  c3_info[63].dominantType = "double";
  c3_info[63].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c3_info[63].fileLength = 324U;
  c3_info[63].fileTime1 = 1203422842U;
  c3_info[63].fileTime2 = 0U;
}

static void c3_b_info_helper(c3_ResolvedFunctionInfo c3_info[115])
{
  c3_info[64].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c3_info[64].name = "eml_scalar_sin";
  c3_info[64].dominantType = "double";
  c3_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c3_info[64].fileLength = 601U;
  c3_info[64].fileTime1 = 1209309190U;
  c3_info[64].fileTime2 = 0U;
  c3_info[65].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expr.m";
  c3_info[65].name = "mpower";
  c3_info[65].dominantType = "double";
  c3_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c3_info[65].fileLength = 3710U;
  c3_info[65].fileTime1 = 1238412688U;
  c3_info[65].fileTime2 = 0U;
  c3_info[66].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c3_info[66].name = "eml_scalar_floor";
  c3_info[66].dominantType = "double";
  c3_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c3_info[66].fileLength = 260U;
  c3_info[66].fileTime1 = 1209309190U;
  c3_info[66].fileTime2 = 0U;
  c3_info[67].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[67].name = "eml_xgemm";
  c3_info[67].dominantType = "int32";
  c3_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c3_info[67].fileLength = 3184U;
  c3_info[67].fileTime1 = 1209309252U;
  c3_info[67].fileTime2 = 0U;
  c3_info[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!itcount";
  c3_info[68].name = "length";
  c3_info[68].dominantType = "double";
  c3_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c3_info[68].fileLength = 326U;
  c3_info[68].fileTime1 = 1226552074U;
  c3_info[68].fileTime2 = 0U;
  c3_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c3_info[69].name = "eml_refblas_xgemm";
  c3_info[69].dominantType = "int32";
  c3_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c3_info[69].fileLength = 5748U;
  c3_info[69].fileTime1 = 1228068672U;
  c3_info[69].fileTime2 = 0U;
  c3_info[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m!matrix_to_integer_power";
  c3_info[70].name = "inv";
  c3_info[70].dominantType = "double";
  c3_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c3_info[70].fileLength = 4757U;
  c3_info[70].fileTime1 = 1252487208U;
  c3_info[70].fileTime2 = 0U;
  c3_info[71].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c3_info[71].name = "isnan";
  c3_info[71].dominantType = "double";
  c3_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c3_info[71].fileLength = 541U;
  c3_info[71].fileTime1 = 1271383988U;
  c3_info[71].fileTime2 = 0U;
  c3_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c3_info[72].name = "eml_guarded_nan";
  c3_info[72].dominantType = "char";
  c3_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c3_info[72].fileLength = 485U;
  c3_info[72].fileTime1 = 1192445180U;
  c3_info[72].fileTime2 = 0U;
  c3_info[73].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c3_info[73].name = "nan";
  c3_info[73].dominantType = "char";
  c3_info[73].resolved = "[B]nan";
  c3_info[73].fileLength = 0U;
  c3_info[73].fileTime1 = 0U;
  c3_info[73].fileTime2 = 0U;
  c3_info[74].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c3_info[74].name = "eml_warning";
  c3_info[74].dominantType = "char";
  c3_info[74].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c3_info[74].fileLength = 262U;
  c3_info[74].fileTime1 = 1236232078U;
  c3_info[74].fileTime2 = 0U;
  c3_info[75].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c3_info[75].name = "power";
  c3_info[75].dominantType = "double";
  c3_info[75].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c3_info[75].fileLength = 5380U;
  c3_info[75].fileTime1 = 1228068698U;
  c3_info[75].fileTime2 = 0U;
  c3_info[76].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c3_info[76].name = "eml_error";
  c3_info[76].dominantType = "char";
  c3_info[76].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c3_info[76].fileLength = 315U;
  c3_info[76].fileTime1 = 1213905144U;
  c3_info[76].fileTime2 = 0U;
  c3_info[77].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expr.m";
  c3_info[77].name = "cos";
  c3_info[77].dominantType = "double";
  c3_info[77].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c3_info[77].fileLength = 324U;
  c3_info[77].fileTime1 = 1203422750U;
  c3_info[77].fileTime2 = 0U;
  c3_info[78].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c3_info[78].name = "eml_scalar_cos";
  c3_info[78].dominantType = "double";
  c3_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c3_info[78].fileLength = 602U;
  c3_info[78].fileTime1 = 1209309186U;
  c3_info[78].fileTime2 = 0U;
  c3_info[79].context =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m";
  c3_info[79].name = "ctranspose";
  c3_info[79].dominantType = "double";
  c3_info[79].resolved = "[B]ctranspose";
  c3_info[79].fileLength = 0U;
  c3_info[79].fileTime1 = 0U;
  c3_info[79].fileTime2 = 0U;
  c3_info[80].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEulerCon.m";
  c3_info[80].name = "mldivide";
  c3_info[80].dominantType = "double";
  c3_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c3_info[80].fileLength = 494U;
  c3_info[80].fileTime1 = 1277726622U;
  c3_info[80].fileTime2 = 0U;
  c3_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c3_info[81].name = "eml_lusolve";
  c3_info[81].dominantType = "double";
  c3_info[81].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c3_info[81].fileLength = 5239U;
  c3_info[81].fileTime1 = 1264408552U;
  c3_info[81].fileTime2 = 0U;
  c3_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c3_info[82].name = "eml_xgetrf";
  c3_info[82].dominantType = "int32";
  c3_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c3_info[82].fileLength = 204U;
  c3_info[82].fileTime1 = 1271383994U;
  c3_info[82].fileTime2 = 0U;
  c3_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c3_info[83].name = "eml_lapack_xgetrf";
  c3_info[83].dominantType = "int32";
  c3_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c3_info[83].fileLength = 211U;
  c3_info[83].fileTime1 = 1271383994U;
  c3_info[83].fileTime2 = 0U;
  c3_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c3_info[84].name = "eml_matlab_zgetrf";
  c3_info[84].dominantType = "int32";
  c3_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[84].fileLength = 2193U;
  c3_info[84].fileTime1 = 1271383998U;
  c3_info[84].fileTime2 = 0U;
  c3_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[85].name = "realmin";
  c3_info[85].dominantType = "char";
  c3_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c3_info[85].fileLength = 749U;
  c3_info[85].fileTime1 = 1226552078U;
  c3_info[85].fileTime2 = 0U;
  c3_info[86].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[86].name = "colon";
  c3_info[86].dominantType = "int32";
  c3_info[86].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c3_info[86].fileLength = 8633U;
  c3_info[86].fileTime1 = 1273822662U;
  c3_info[86].fileTime2 = 0U;
  c3_info[87].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c3_info[87].name = "floor";
  c3_info[87].dominantType = "double";
  c3_info[87].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c3_info[87].fileLength = 332U;
  c3_info[87].fileTime1 = 1203422822U;
  c3_info[87].fileTime2 = 0U;
  c3_info[88].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c3_info[88].name = "intmin";
  c3_info[88].dominantType = "char";
  c3_info[88].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c3_info[88].fileLength = 1505U;
  c3_info[88].fileTime1 = 1192445128U;
  c3_info[88].fileTime2 = 0U;
  c3_info[89].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon";
  c3_info[89].name = "transpose";
  c3_info[89].dominantType = "int32";
  c3_info[89].resolved = "[B]transpose";
  c3_info[89].fileLength = 0U;
  c3_info[89].fileTime1 = 0U;
  c3_info[89].fileTime2 = 0U;
  c3_info[90].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[90].name = "eml_ixamax";
  c3_info[90].dominantType = "int32";
  c3_info[90].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c3_info[90].fileLength = 731U;
  c3_info[90].fileTime1 = 1209309244U;
  c3_info[90].fileTime2 = 0U;
  c3_info[91].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c3_info[91].name = "eml_refblas_ixamax";
  c3_info[91].dominantType = "int32";
  c3_info[91].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[91].fileLength = 740U;
  c3_info[91].fileTime1 = 1192445266U;
  c3_info[91].fileTime2 = 0U;
  c3_info[92].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[92].name = "eml_xcabs1";
  c3_info[92].dominantType = "double";
  c3_info[92].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c3_info[92].fileLength = 419U;
  c3_info[92].fileTime1 = 1209309246U;
  c3_info[92].fileTime2 = 0U;
  c3_info[93].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[93].name = "eml_xswap";
  c3_info[93].dominantType = "int32";
  c3_info[93].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c3_info[93].fileLength = 1330U;
  c3_info[93].fileTime1 = 1209309260U;
  c3_info[93].fileTime2 = 0U;
  c3_info[94].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c3_info[94].name = "eml_refblas_xswap";
  c3_info[94].dominantType = "int32";
  c3_info[94].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c3_info[94].fileLength = 905U;
  c3_info[94].fileTime1 = 1238412670U;
  c3_info[94].fileTime2 = 0U;
  c3_info[95].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[95].name = "eml_xgeru";
  c3_info[95].dominantType = "int32";
  c3_info[95].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c3_info[95].fileLength = 2462U;
  c3_info[95].fileTime1 = 1209309256U;
  c3_info[95].fileTime2 = 0U;
  c3_info[96].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c3_info[96].name = "eml_xger";
  c3_info[96].dominantType = "int32";
  c3_info[96].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c3_info[96].fileLength = 2168U;
  c3_info[96].fileTime1 = 1209309254U;
  c3_info[96].fileTime2 = 0U;
  c3_info[97].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c3_info[97].name = "eml_refblas_xger";
  c3_info[97].dominantType = "int32";
  c3_info[97].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c3_info[97].fileLength = 411U;
  c3_info[97].fileTime1 = 1211194448U;
  c3_info[97].fileTime2 = 0U;
  c3_info[98].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c3_info[98].name = "eml_refblas_xgerx";
  c3_info[98].dominantType = "int32";
  c3_info[98].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[98].fileLength = 2231U;
  c3_info[98].fileTime1 = 1238412668U;
  c3_info[98].fileTime2 = 0U;
  c3_info[99].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c3_info[99].name = "eml_xtrsm";
  c3_info[99].dominantType = "int32";
  c3_info[99].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c3_info[99].fileLength = 2383U;
  c3_info[99].fileTime1 = 1209309262U;
  c3_info[99].fileTime2 = 0U;
  c3_info[100].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c3_info[100].name = "eml_refblas_xtrsm";
  c3_info[100].dominantType = "int32";
  c3_info[100].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c3_info[100].fileLength = 13101U;
  c3_info[100].fileTime1 = 1252487206U;
  c3_info[100].fileTime2 = 0U;
  c3_info[101].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEulerCon.m";
  c3_info[101].name = "reshape";
  c3_info[101].dominantType = "double";
  c3_info[101].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c3_info[101].fileLength = 4857U;
  c3_info[101].fileTime1 = 1242276774U;
  c3_info[101].fileTime2 = 0U;
  c3_info[102].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c3_info[102].name = "eml_index_prod";
  c3_info[102].dominantType = "int32";
  c3_info[102].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_prod.m";
  c3_info[102].fileLength = 547U;
  c3_info[102].fileTime1 = 1211194426U;
  c3_info[102].fileTime2 = 0U;
  c3_info[103].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEulerCon.m";
  c3_info[103].name = "Adjoint";
  c3_info[103].dominantType = "double";
  c3_info[103].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/Adjoint.m";
  c3_info[103].fileLength = 338U;
  c3_info[103].fileTime1 = 1419992576U;
  c3_info[103].fileTime2 = 0U;
  c3_info[104].context = "[E]D:/Learn/Project_Matlab/Fanuc/Adjoint.m";
  c3_info[104].name = "any";
  c3_info[104].dominantType = "logical";
  c3_info[104].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c3_info[104].fileLength = 427U;
  c3_info[104].fileTime1 = 1221245538U;
  c3_info[104].fileTime2 = 0U;
  c3_info[105].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c3_info[105].name = "eml_all_or_any";
  c3_info[105].dominantType = "char";
  c3_info[105].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c3_info[105].fileLength = 3914U;
  c3_info[105].fileTime1 = 1271383994U;
  c3_info[105].fileTime2 = 0U;
  c3_info[106].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c3_info[106].name = "isequal";
  c3_info[106].dominantType = "double";
  c3_info[106].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c3_info[106].fileLength = 180U;
  c3_info[106].fileTime1 = 1226552070U;
  c3_info[106].fileTime2 = 0U;
  c3_info[107].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c3_info[107].name = "eml_isequal_core";
  c3_info[107].dominantType = "double";
  c3_info[107].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c3_info[107].fileLength = 4192U;
  c3_info[107].fileTime1 = 1258039010U;
  c3_info[107].fileTime2 = 0U;
  c3_info[108].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c3_info[108].name = "eml_const_nonsingleton_dim";
  c3_info[108].dominantType = "logical";
  c3_info[108].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c3_info[108].fileLength = 1473U;
  c3_info[108].fileTime1 = 1240240402U;
  c3_info[108].fileTime2 = 0U;
  c3_info[109].context = "[E]D:/Learn/Project_Matlab/Fanuc/Adjoint.m";
  c3_info[109].name = "skew";
  c3_info[109].dominantType = "double";
  c3_info[109].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/skew.m";
  c3_info[109].fileLength = 450U;
  c3_info[109].fileTime1 = 1399884445U;
  c3_info[109].fileTime2 = 0U;
  c3_info[110].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEulerCon.m";
  c3_info[110].name = "ad";
  c3_info[110].dominantType = "double";
  c3_info[110].resolved =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/ad.m";
  c3_info[110].fileLength = 112U;
  c3_info[110].fileTime1 = 1365307014U;
  c3_info[110].fileTime2 = 0U;
  c3_info[111].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[111].name = "eml_xdotu";
  c3_info[111].dominantType = "int32";
  c3_info[111].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c3_info[111].fileLength = 1453U;
  c3_info[111].fileTime1 = 1209309250U;
  c3_info[111].fileTime2 = 0U;
  c3_info[112].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c3_info[112].name = "eml_xdot";
  c3_info[112].dominantType = "int32";
  c3_info[112].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c3_info[112].fileLength = 1330U;
  c3_info[112].fileTime1 = 1209309248U;
  c3_info[112].fileTime2 = 0U;
  c3_info[113].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c3_info[113].name = "eml_refblas_xdot";
  c3_info[113].dominantType = "int32";
  c3_info[113].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c3_info[113].fileLength = 343U;
  c3_info[113].fileTime1 = 1211194442U;
  c3_info[113].fileTime2 = 0U;
  c3_info[114].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c3_info[114].name = "eml_refblas_xdotx";
  c3_info[114].dominantType = "int32";
  c3_info[114].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[114].fileLength = 1605U;
  c3_info[114].fileTime1 = 1236232078U;
  c3_info[114].fileTime2 = 0U;
}

static const mxArray *c3_l_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  boolean_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_b_u = *((boolean_T *)c3_u);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static void c3_emlrt_marshallIn(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *c3_JntAcc, const char_T *
  c3_name, real_T c3_y[36])
{
  real_T c3_dv155[36];
  int32_T c3_i1520;
  sf_mex_import(c3_name, sf_mex_dup(c3_JntAcc), c3_dv155, 1, 0, 0U, 1, 0U, 1, 36);
  for (c3_i1520 = 0; c3_i1520 < 36; c3_i1520 = c3_i1520 + 1) {
    c3_y[c3_i1520] = c3_dv155[c3_i1520];
  }

  sf_mex_destroy(&c3_JntAcc);
}

static void c3_b_emlrt_marshallIn(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *c3_Torque, const char_T *
  c3_name, real_T c3_y[6])
{
  real_T c3_dv156[6];
  int32_T c3_i1521;
  sf_mex_import(c3_name, sf_mex_dup(c3_Torque), c3_dv156, 1, 0, 0U, 1, 0U, 1, 6);
  for (c3_i1521 = 0; c3_i1521 < 6; c3_i1521 = c3_i1521 + 1) {
    c3_y[c3_i1521] = c3_dv156[c3_i1521];
  }

  sf_mex_destroy(&c3_Torque);
}

static uint8_T c3_c_emlrt_marshallIn(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance, const mxArray *
  c3_b_is_active_c3_EulerPIDJoint_Copy, const char_T *c3_name)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_name, sf_mex_dup(c3_b_is_active_c3_EulerPIDJoint_Copy),
                &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_b_is_active_c3_EulerPIDJoint_Copy);
  return c3_y;
}

static void init_dsm_address_info(SFc3_EulerPIDJoint_CopyInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_EulerPIDJoint_Copy_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2270181771U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2378682606U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1809422804U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(130819199U);
}

mxArray *sf_c3_EulerPIDJoint_Copy_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2787690156U);
    pr[1] = (double)(2801496750U);
    pr[2] = (double)(2568722575U);
    pr[3] = (double)(3516537751U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(18);
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
      pr[0] = (double)(4);
      pr[1] = (double)(7);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(54);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      pr[0] = (double)(36);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(36);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(36);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  return(mxAutoinheritanceInfo);
}

static mxArray *sf_get_sim_state_info_c3_EulerPIDJoint_Copy(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[17],T\"JntAcc\",},{M[1],M[18],T\"JntF\",},{M[1],M[16],T\"JntVel\",},{M[1],M[5],T\"Torque\",},{M[8],M[0],T\"is_active_c3_EulerPIDJoint_Copy\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_EulerPIDJoint_Copy_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
    chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_EulerPIDJoint_CopyMachineNumber_,
           3,
           1,
           1,
           15,
           0,
           0,
           0,
           0,
           7,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"RefPos");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Torque");
          _SFD_SET_DATA_PROPS(2,1,1,0,"RefVel");
          _SFD_SET_DATA_PROPS(3,1,1,0,"RefAcc");
          _SFD_SET_DATA_PROPS(4,1,1,0,"EnPos");
          _SFD_SET_DATA_PROPS(5,1,1,0,"EnVel");
          _SFD_SET_DATA_PROPS(6,1,1,0,"EnAcc");
          _SFD_SET_DATA_PROPS(7,10,0,0,"DH_EU");
          _SFD_SET_DATA_PROPS(8,10,0,0,"Ma_EU");
          _SFD_SET_DATA_PROPS(9,10,0,0,"Cen_EU");
          _SFD_SET_DATA_PROPS(10,10,0,0,"Ie_EU");
          _SFD_SET_DATA_PROPS(11,10,0,0,"Ft_EU");
          _SFD_SET_DATA_PROPS(12,2,0,1,"JntVel");
          _SFD_SET_DATA_PROPS(13,2,0,1,"JntAcc");
          _SFD_SET_DATA_PROPS(14,2,0,1,"JntF");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,443);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"DynEulerCon",786,-1,5658);
        _SFD_CV_INIT_SCRIPT(1,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"expg",0,-1,280);
        _SFD_CV_INIT_SCRIPT_IF(1,0,68,76,110,232);
        _SFD_CV_INIT_SCRIPT(2,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"expr",0,-1,182);
        _SFD_CV_INIT_SCRIPT_IF(2,0,41,49,66,182);
        _SFD_CV_INIT_SCRIPT(3,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(3,0,"hat",0,-1,85);
        _SFD_CV_INIT_SCRIPT(4,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(4,0,"Adjoint",0,-1,338);
        _SFD_CV_INIT_SCRIPT_IF(4,0,30,55,-1,109);
        _SFD_CV_INIT_SCRIPT(5,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(5,0,"skew",0,-1,450);
        _SFD_CV_INIT_SCRIPT_IF(5,0,27,44,-1,92);
        _SFD_CV_INIT_SCRIPT(6,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(6,0,"ad",0,-1,106);
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
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 18;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 54;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 36;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 36;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 36;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshall);
        }

        {
          real_T (*c3_RefPos)[6];
          real_T (*c3_Torque)[6];
          real_T (*c3_RefVel)[6];
          real_T (*c3_RefAcc)[6];
          real_T (*c3_EnPos)[6];
          real_T (*c3_EnVel)[6];
          real_T (*c3_EnAcc)[6];
          real_T (*c3_JntVel)[36];
          real_T (*c3_JntAcc)[36];
          real_T (*c3_JntF)[36];
          c3_JntF = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
          c3_JntAcc = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
          c3_JntVel = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
          c3_EnAcc = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 5);
          c3_EnVel = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 4);
          c3_EnPos = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 3);
          c3_RefAcc = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
          c3_RefVel = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
          c3_Torque = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c3_RefPos = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_RefPos);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_Torque);
          _SFD_SET_DATA_VALUE_PTR(2U, *c3_RefVel);
          _SFD_SET_DATA_VALUE_PTR(3U, *c3_RefAcc);
          _SFD_SET_DATA_VALUE_PTR(4U, *c3_EnPos);
          _SFD_SET_DATA_VALUE_PTR(5U, *c3_EnVel);
          _SFD_SET_DATA_VALUE_PTR(6U, *c3_EnAcc);
          _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c3_DH_EU);
          _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c3_Ma_EU);
          _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c3_Cen_EU);
          _SFD_SET_DATA_VALUE_PTR(10U, chartInstance->c3_Ie_EU);
          _SFD_SET_DATA_VALUE_PTR(11U, chartInstance->c3_Ft_EU);
          _SFD_SET_DATA_VALUE_PTR(12U, *c3_JntVel);
          _SFD_SET_DATA_VALUE_PTR(13U, *c3_JntAcc);
          _SFD_SET_DATA_VALUE_PTR(14U, *c3_JntF);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration
        (_EulerPIDJoint_CopyMachineNumber_,chartInstance->chartNumber,
         chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c3_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_EulerPIDJoint_Copy((SFc3_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
  initialize_c3_EulerPIDJoint_Copy((SFc3_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  enable_c3_EulerPIDJoint_Copy((SFc3_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c3_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  disable_c3_EulerPIDJoint_Copy((SFc3_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c3_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  sf_c3_EulerPIDJoint_Copy((SFc3_EulerPIDJoint_CopyInstanceStruct*)
    chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c3_EulerPIDJoint_Copy(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_EulerPIDJoint_Copy
    ((SFc3_EulerPIDJoint_CopyInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c3_EulerPIDJoint_Copy();/* state var info */
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

static void sf_internal_set_sim_state_c3_EulerPIDJoint_Copy(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_EulerPIDJoint_Copy();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_EulerPIDJoint_Copy((SFc3_EulerPIDJoint_CopyInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c3_EulerPIDJoint_Copy(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_EulerPIDJoint_Copy(S);
}

static void sf_opaque_set_sim_state_c3_EulerPIDJoint_Copy(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c3_EulerPIDJoint_Copy(S, st);
}

static void sf_opaque_terminate_c3_EulerPIDJoint_Copy(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_EulerPIDJoint_CopyInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_EulerPIDJoint_Copy((SFc3_EulerPIDJoint_CopyInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c3_EulerPIDJoint_Copy
    ((SFc3_EulerPIDJoint_CopyInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_EulerPIDJoint_Copy(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_EulerPIDJoint_Copy
      ((SFc3_EulerPIDJoint_CopyInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_EulerPIDJoint_Copy(SimStruct *S)
{
  /* Actual parameters from chart:
     Cen_EU DH_EU Ft_EU Ie_EU Ma_EU
   */
  const char_T *rtParamNames[] = { "p1", "p2", "p3", "p4", "p5" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for Cen_EU*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for DH_EU*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for Ft_EU*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);

  /* registration for Ie_EU*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_DOUBLE);

  /* registration for Ma_EU*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"EulerPIDJoint_Copy","EulerPIDJoint_Copy",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"EulerPIDJoint_Copy",
                "EulerPIDJoint_Copy",3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"EulerPIDJoint_Copy",
      "EulerPIDJoint_Copy",3,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"EulerPIDJoint_Copy",
        "EulerPIDJoint_Copy",3,6);
      sf_mark_chart_reusable_outputs(S,"EulerPIDJoint_Copy","EulerPIDJoint_Copy",
        3,4);
    }

    sf_set_rtw_dwork_info(S,"EulerPIDJoint_Copy","EulerPIDJoint_Copy",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(269046231U));
  ssSetChecksum1(S,(888337175U));
  ssSetChecksum2(S,(521574786U));
  ssSetChecksum3(S,(1917474972U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_EulerPIDJoint_Copy(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "EulerPIDJoint_Copy", "EulerPIDJoint_Copy",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_EulerPIDJoint_Copy(SimStruct *S)
{
  SFc3_EulerPIDJoint_CopyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EulerPIDJoint_CopyInstanceStruct *)malloc(sizeof
    (SFc3_EulerPIDJoint_CopyInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_EulerPIDJoint_CopyInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_EulerPIDJoint_Copy;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c3_EulerPIDJoint_Copy;
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

void c3_EulerPIDJoint_Copy_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_EulerPIDJoint_Copy(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_EulerPIDJoint_Copy(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_EulerPIDJoint_Copy(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_EulerPIDJoint_Copy_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
