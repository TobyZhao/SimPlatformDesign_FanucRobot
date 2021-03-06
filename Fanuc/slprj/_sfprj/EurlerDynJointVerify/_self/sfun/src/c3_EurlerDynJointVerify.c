/* Include files */

#include "blascompat32.h"
#include "EurlerDynJointVerify_sfun.h"
#include "c3_EurlerDynJointVerify.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "EurlerDynJointVerify_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c3_debug_family_names[14] = { "nargin", "nargout", "Pos",
  "Vel", "Acc", "DH_EU", "Ma_EU", "Cen_EU", "Ie_EU", "Ft_EU", "Torque", "JntVel",
  "JntAcc", "JntF" };

static const char *c3_b_debug_family_names[4] = { "nargin", "nargout", "w", "W"
};

static const char *c3_c_debug_family_names[6] = { "n", "nargin", "nargout", "w",
  "theta", "R" };

static const char *c3_d_debug_family_names[10] = { "v", "w", "n", "R", "P",
  "nargin", "nargout", "xi", "theta", "g" };

static const char *c3_e_debug_family_names[7] = { "R", "P", "P_hat", "nargin",
  "nargout", "g", "Adg" };

static const char *c3_f_debug_family_names[6] = { "w", "v", "nargin", "nargout",
  "xi", "adx" };

static const char *c3_g_debug_family_names[93] = { "w_o", "w_z", "kxi1", "kxi2",
  "kxi3", "kxi4", "kxi5", "kxi6", "ez", "ex", "eo", "g01_0", "g12_0", "g23_0",
  "g34_0", "g45_0", "g56_0", "g67_0", "m1", "I1", "m2", "I2", "m3", "I3", "m4",
  "I4", "m5", "I5", "m6", "I6", "g", "r1", "r2", "R", "r3", "r4", "r5", "r6",
  "M1", "M2", "M3", "M4", "M5", "M6", "V0", "dV0", "g01", "Adinvg01", "V1",
  "dV1", "g12", "Adinvg12", "V2", "dV2", "g23", "Adinvg23", "V3", "dV3", "g34",
  "Adinvg34", "V4", "dV4", "g45", "Adinvg45", "V5", "dV5", "g56", "Adinvg56",
  "V6", "dV6", "Tau", "F7", "Adinvg67", "F6", "F5", "F4", "F3", "F2", "F1",
  "nargin", "nargout", "DH", "Ma", "Cen", "Ie", "Ft", "Pos", "Vel", "Acc",
  "Torque", "JntVel", "JntAcc", "JntF" };

/* Function Declarations */
static void initialize_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void initialize_params_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void enable_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void disable_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void set_sim_state_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance, const mxArray *c3_st);
static void finalize_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void sf_c3_EurlerDynJointVerify(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void compInitSubchartSimstructsFcn_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static void c3_DynEuler(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_DH[28], real_T c3_Ma[6], real_T c3_Cen[18], real_T c3_Ie[54], real_T
  c3_Ft[6], real_T c3_Pos[6], real_T c3_Vel[6], real_T c3_Acc[6], real_T
  c3_Torque[6], real_T c3_JntVel[36], real_T c3_JntAcc[36], real_T c3_JntF[36]);
static void c3_expg(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                    real_T c3_xi[6], real_T c3_theta, real_T c3_g[16]);
static real_T c3_norm(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c3_x[3]);
static real_T c3_ceval_xnrm2(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[3], int32_T c3_ix0, int32_T c3_incx);
static void c3_eps(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void c3_isVariableSizing(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_eye(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                   real_T c3_I[9]);
static void c3_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_expr(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                    real_T c3_w[3], real_T c3_theta, real_T c3_R[9]);
static void c3_hat(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                   real_T c3_w[3], real_T c3_W[9]);
static void c3_matrix_to_integer_power(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c3_a[9], real_T c3_b, real_T c3_c[9]);
static void c3_b_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_c_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_inv3x3(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c3_x[9], real_T c3_y[9]);
static real_T c3_b_norm(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_x[9]);
static void c3_eml_warning(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_b_eps(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void c3_b_eml_warning(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c3_varargin_3);
static real_T c3_power(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_a, real_T c3_b);
static void c3_eml_error(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void c3_d_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_e_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_mldivide(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[4], real_T c3_Y[4]);
static void c3_eml_matlab_zgetrf(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c3_A[16], real_T c3_b_A[16], int32_T c3_ipiv[4],
  int32_T *c3_info);
static int32_T c3_eml_ixamax(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0);
static int32_T c3_ceval_ixamax(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0, int32_T c3_incx);
static void c3_ceval_xswap(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0, int32_T c3_incx,
  int32_T c3_iy0, int32_T c3_incy, real_T c3_b_x[16]);
static void c3_ceval_xger(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, real_T c3_alpha1, int32_T c3_ix0, int32_T c3_incx,
  int32_T c3_iy0, int32_T c3_incy, real_T c3_A[16], int32_T c3_ia0, int32_T
  c3_lda, real_T c3_b_A[16]);
static void c3_eml_xtrsm(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[4], real_T c3_b_B[4]);
static void c3_f_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_eml_blas_xtrsm(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, real_T c3_alpha1, real_T c3_A[16],
  int32_T c3_ia0, int32_T c3_lda, real_T c3_B[4], int32_T c3_ib0, int32_T c3_ldb,
  real_T c3_b_B[4]);
static void c3_b_mldivide(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[16], real_T c3_Y[16]);
static void c3_b_eml_xtrsm(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c3_A[16], real_T c3_B[16], real_T c3_b_B[16]);
static void c3_g_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_b_eml_blas_xtrsm(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, real_T c3_alpha1, real_T c3_A[16],
  int32_T c3_ia0, int32_T c3_lda, real_T c3_B[16], int32_T c3_ib0, int32_T
  c3_ldb, real_T c3_b_B[16]);
static void c3_Adj(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                   real_T c3_g[16], real_T c3_Adg[36]);
static void c3_h_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_eml_xgemm(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_A[36], real_T c3_B[6], real_T c3_C[6], real_T c3_b_C[6]);
static void c3_ad(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance, real_T
                  c3_xi[6], real_T c3_adx[36]);
static void c3_i_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c3_ceval_xgemm(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, int32_T c3_k, real_T c3_alpha1,
  real_T c3_A[36], int32_T c3_ia0, int32_T c3_lda, real_T c3_B[36], int32_T
  c3_ib0, int32_T c3_ldb, real_T c3_beta1, real_T c3_C[36], int32_T c3_ic0,
  int32_T c3_ldc, real_T c3_b_C[36]);
static void c3_j_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static real_T c3_ceval_xdot(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[6], int32_T c3_ix0, int32_T c3_incx,
  real_T c3_y[6], int32_T c3_iy0, int32_T c3_incy);
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
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[111]);
static void c3_b_info_helper(c3_ResolvedFunctionInfo c3_info[111]);
static const mxArray *c3_l_sf_marshall(void *chartInstanceVoid, void *c3_u);
static void c3_emlrt_marshallIn(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *c3_JntAcc, const char_T *c3_name, real_T c3_y
  [36]);
static void c3_b_emlrt_marshallIn(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *c3_Torque, const char_T *c3_name, real_T c3_y[6]);
static uint8_T c3_c_emlrt_marshallIn(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_EurlerDynJointVerify, const
  char_T *c3_name);
static void init_dsm_address_info(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_EurlerDynJointVerify = 0U;
}

static void initialize_params_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
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

static void enable_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
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
  c3_e_hoistedGlobal = chartInstance->c3_is_active_c3_EurlerDynJointVerify;
  c3_e_u = c3_e_hoistedGlobal;
  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 4, c3_f_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance, const mxArray *c3_st)
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

  chartInstance->c3_is_active_c3_EurlerDynJointVerify = c3_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 4)),
     "is_active_c3_EurlerDynJointVerify");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_EurlerDynJointVerify(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static void sf_c3_EurlerDynJointVerify(SFc3_EurlerDynJointVerifyInstanceStruct
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
  int32_T c3_previousEvent;
  int32_T c3_i29;
  real_T c3_hoistedGlobal[6];
  int32_T c3_i30;
  real_T c3_b_hoistedGlobal[6];
  int32_T c3_i31;
  real_T c3_c_hoistedGlobal[6];
  int32_T c3_i32;
  real_T c3_d_hoistedGlobal[28];
  int32_T c3_i33;
  real_T c3_e_hoistedGlobal[6];
  int32_T c3_i34;
  real_T c3_f_hoistedGlobal[18];
  int32_T c3_i35;
  real_T c3_g_hoistedGlobal[54];
  int32_T c3_i36;
  real_T c3_h_hoistedGlobal[6];
  int32_T c3_i37;
  real_T c3_Pos[6];
  int32_T c3_i38;
  real_T c3_Vel[6];
  int32_T c3_i39;
  real_T c3_Acc[6];
  int32_T c3_i40;
  real_T c3_b_DH_EU[28];
  int32_T c3_i41;
  real_T c3_b_Ma_EU[6];
  int32_T c3_i42;
  real_T c3_b_Cen_EU[18];
  int32_T c3_i43;
  real_T c3_b_Ie_EU[54];
  int32_T c3_i44;
  real_T c3_b_Ft_EU[6];
  uint32_T c3_debug_family_var_map[14];
  static const char *c3_sv0[14] = { "nargin", "nargout", "Pos", "Vel", "Acc",
    "DH_EU", "Ma_EU", "Cen_EU", "Ie_EU", "Ft_EU", "Torque",
    "JntVel", "JntAcc", "JntF" };

  real_T c3_nargin = 8.0;
  real_T c3_nargout = 4.0;
  real_T c3_Torque[6];
  real_T c3_JntVel[36];
  real_T c3_JntAcc[36];
  real_T c3_JntF[36];
  int32_T c3_i45;
  int32_T c3_i46;
  int32_T c3_i47;
  int32_T c3_i48;
  int32_T c3_i49;
  real_T c3_c_DH_EU[28];
  int32_T c3_i50;
  real_T c3_c_Ma_EU[6];
  int32_T c3_i51;
  real_T c3_c_Cen_EU[18];
  int32_T c3_i52;
  real_T c3_c_Ie_EU[54];
  int32_T c3_i53;
  real_T c3_c_Ft_EU[6];
  int32_T c3_i54;
  real_T c3_b_Pos[6];
  int32_T c3_i55;
  real_T c3_b_Vel[6];
  int32_T c3_i56;
  real_T c3_b_Acc[6];
  real_T c3_b_JntF[36];
  real_T c3_b_JntAcc[36];
  real_T c3_b_JntVel[36];
  real_T c3_b_Torque[6];
  int32_T c3_i57;
  int32_T c3_i58;
  int32_T c3_i59;
  int32_T c3_i60;
  int32_T c3_i61;
  int32_T c3_i62;
  int32_T c3_i63;
  int32_T c3_i64;
  real_T (*c3_c_Torque)[6];
  real_T (*c3_c_JntVel)[36];
  real_T (*c3_c_JntAcc)[36];
  real_T (*c3_c_JntF)[36];
  real_T (*c3_c_Acc)[6];
  real_T (*c3_c_Vel)[6];
  real_T (*c3_c_Pos)[6];
  c3_c_JntF = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
  c3_c_JntAcc = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_c_JntVel = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_c_Acc = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
  c3_c_Vel = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c3_c_Torque = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_c_Pos = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2);
  for (c3_i17 = 0; c3_i17 < 6; c3_i17 = c3_i17 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_Pos)[c3_i17], 0U);
  }

  for (c3_i18 = 0; c3_i18 < 6; c3_i18 = c3_i18 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_Torque)[c3_i18], 1U);
  }

  for (c3_i19 = 0; c3_i19 < 6; c3_i19 = c3_i19 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_Vel)[c3_i19], 2U);
  }

  for (c3_i20 = 0; c3_i20 < 6; c3_i20 = c3_i20 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_Acc)[c3_i20], 3U);
  }

  for (c3_i21 = 0; c3_i21 < 28; c3_i21 = c3_i21 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_DH_EU[c3_i21], 4U);
  }

  for (c3_i22 = 0; c3_i22 < 6; c3_i22 = c3_i22 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ma_EU[c3_i22], 5U);
  }

  for (c3_i23 = 0; c3_i23 < 18; c3_i23 = c3_i23 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Cen_EU[c3_i23], 6U);
  }

  for (c3_i24 = 0; c3_i24 < 54; c3_i24 = c3_i24 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ie_EU[c3_i24], 7U);
  }

  for (c3_i25 = 0; c3_i25 < 6; c3_i25 = c3_i25 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ft_EU[c3_i25], 8U);
  }

  for (c3_i26 = 0; c3_i26 < 36; c3_i26 = c3_i26 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_JntVel)[c3_i26], 9U);
  }

  for (c3_i27 = 0; c3_i27 < 36; c3_i27 = c3_i27 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_JntAcc)[c3_i27], 10U);
  }

  for (c3_i28 = 0; c3_i28 < 36; c3_i28 = c3_i28 + 1) {
    _SFD_DATA_RANGE_CHECK((*c3_c_JntF)[c3_i28], 11U);
  }

  c3_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2);
  for (c3_i29 = 0; c3_i29 < 6; c3_i29 = c3_i29 + 1) {
    c3_hoistedGlobal[c3_i29] = (*c3_c_Pos)[c3_i29];
  }

  for (c3_i30 = 0; c3_i30 < 6; c3_i30 = c3_i30 + 1) {
    c3_b_hoistedGlobal[c3_i30] = (*c3_c_Vel)[c3_i30];
  }

  for (c3_i31 = 0; c3_i31 < 6; c3_i31 = c3_i31 + 1) {
    c3_c_hoistedGlobal[c3_i31] = (*c3_c_Acc)[c3_i31];
  }

  for (c3_i32 = 0; c3_i32 < 28; c3_i32 = c3_i32 + 1) {
    c3_d_hoistedGlobal[c3_i32] = chartInstance->c3_DH_EU[c3_i32];
  }

  for (c3_i33 = 0; c3_i33 < 6; c3_i33 = c3_i33 + 1) {
    c3_e_hoistedGlobal[c3_i33] = chartInstance->c3_Ma_EU[c3_i33];
  }

  for (c3_i34 = 0; c3_i34 < 18; c3_i34 = c3_i34 + 1) {
    c3_f_hoistedGlobal[c3_i34] = chartInstance->c3_Cen_EU[c3_i34];
  }

  for (c3_i35 = 0; c3_i35 < 54; c3_i35 = c3_i35 + 1) {
    c3_g_hoistedGlobal[c3_i35] = chartInstance->c3_Ie_EU[c3_i35];
  }

  for (c3_i36 = 0; c3_i36 < 6; c3_i36 = c3_i36 + 1) {
    c3_h_hoistedGlobal[c3_i36] = chartInstance->c3_Ft_EU[c3_i36];
  }

  for (c3_i37 = 0; c3_i37 < 6; c3_i37 = c3_i37 + 1) {
    c3_Pos[c3_i37] = c3_hoistedGlobal[c3_i37];
  }

  for (c3_i38 = 0; c3_i38 < 6; c3_i38 = c3_i38 + 1) {
    c3_Vel[c3_i38] = c3_b_hoistedGlobal[c3_i38];
  }

  for (c3_i39 = 0; c3_i39 < 6; c3_i39 = c3_i39 + 1) {
    c3_Acc[c3_i39] = c3_c_hoistedGlobal[c3_i39];
  }

  for (c3_i40 = 0; c3_i40 < 28; c3_i40 = c3_i40 + 1) {
    c3_b_DH_EU[c3_i40] = c3_d_hoistedGlobal[c3_i40];
  }

  for (c3_i41 = 0; c3_i41 < 6; c3_i41 = c3_i41 + 1) {
    c3_b_Ma_EU[c3_i41] = c3_e_hoistedGlobal[c3_i41];
  }

  for (c3_i42 = 0; c3_i42 < 18; c3_i42 = c3_i42 + 1) {
    c3_b_Cen_EU[c3_i42] = c3_f_hoistedGlobal[c3_i42];
  }

  for (c3_i43 = 0; c3_i43 < 54; c3_i43 = c3_i43 + 1) {
    c3_b_Ie_EU[c3_i43] = c3_g_hoistedGlobal[c3_i43];
  }

  for (c3_i44 = 0; c3_i44 < 6; c3_i44 = c3_i44 + 1) {
    c3_b_Ft_EU[c3_i44] = c3_h_hoistedGlobal[c3_i44];
  }

  sf_debug_symbol_scope_push_eml(0U, 14U, 14U, c3_sv0, c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_Pos, c3_b_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_Vel, c3_b_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c3_Acc, c3_b_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c3_b_DH_EU, c3_e_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c3_b_Ma_EU, c3_b_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c3_b_Cen_EU, c3_d_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c3_b_Ie_EU, c3_c_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c3_b_Ft_EU, c3_b_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(c3_Torque, c3_b_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(c3_JntVel, c3_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(c3_JntAcc, c3_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(c3_JntF, c3_sf_marshall, 13U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0, 3);
  for (c3_i45 = 0; c3_i45 < 6; c3_i45 = c3_i45 + 1) {
    c3_Torque[c3_i45] = 0.0;
  }

  _SFD_EML_CALL(0, 4);
  for (c3_i46 = 0; c3_i46 < 36; c3_i46 = c3_i46 + 1) {
    c3_JntVel[c3_i46] = 0.0;
  }

  _SFD_EML_CALL(0, 5);
  for (c3_i47 = 0; c3_i47 < 36; c3_i47 = c3_i47 + 1) {
    c3_JntAcc[c3_i47] = 0.0;
  }

  _SFD_EML_CALL(0, 6);
  for (c3_i48 = 0; c3_i48 < 36; c3_i48 = c3_i48 + 1) {
    c3_JntF[c3_i48] = 0.0;
  }

  _SFD_EML_CALL(0, 7);
  for (c3_i49 = 0; c3_i49 < 28; c3_i49 = c3_i49 + 1) {
    c3_c_DH_EU[c3_i49] = c3_b_DH_EU[c3_i49];
  }

  for (c3_i50 = 0; c3_i50 < 6; c3_i50 = c3_i50 + 1) {
    c3_c_Ma_EU[c3_i50] = c3_b_Ma_EU[c3_i50];
  }

  for (c3_i51 = 0; c3_i51 < 18; c3_i51 = c3_i51 + 1) {
    c3_c_Cen_EU[c3_i51] = c3_b_Cen_EU[c3_i51];
  }

  for (c3_i52 = 0; c3_i52 < 54; c3_i52 = c3_i52 + 1) {
    c3_c_Ie_EU[c3_i52] = c3_b_Ie_EU[c3_i52];
  }

  for (c3_i53 = 0; c3_i53 < 6; c3_i53 = c3_i53 + 1) {
    c3_c_Ft_EU[c3_i53] = c3_b_Ft_EU[c3_i53];
  }

  for (c3_i54 = 0; c3_i54 < 6; c3_i54 = c3_i54 + 1) {
    c3_b_Pos[c3_i54] = c3_Pos[c3_i54];
  }

  for (c3_i55 = 0; c3_i55 < 6; c3_i55 = c3_i55 + 1) {
    c3_b_Vel[c3_i55] = c3_Vel[c3_i55];
  }

  for (c3_i56 = 0; c3_i56 < 6; c3_i56 = c3_i56 + 1) {
    c3_b_Acc[c3_i56] = c3_Acc[c3_i56];
  }

  c3_DynEuler(chartInstance, c3_c_DH_EU, c3_c_Ma_EU, c3_c_Cen_EU, c3_c_Ie_EU,
              c3_c_Ft_EU, c3_b_Pos, c3_b_Vel, c3_b_Acc, c3_b_Torque,
              c3_b_JntVel, c3_b_JntAcc, c3_b_JntF);
  for (c3_i57 = 0; c3_i57 < 6; c3_i57 = c3_i57 + 1) {
    c3_Torque[c3_i57] = c3_b_Torque[c3_i57];
  }

  for (c3_i58 = 0; c3_i58 < 36; c3_i58 = c3_i58 + 1) {
    c3_JntVel[c3_i58] = c3_b_JntVel[c3_i58];
  }

  for (c3_i59 = 0; c3_i59 < 36; c3_i59 = c3_i59 + 1) {
    c3_JntAcc[c3_i59] = c3_b_JntAcc[c3_i59];
  }

  for (c3_i60 = 0; c3_i60 < 36; c3_i60 = c3_i60 + 1) {
    c3_JntF[c3_i60] = c3_b_JntF[c3_i60];
  }

  /* [Torque,JntVel,JntAcc,JntF] = DynEulerSci(DH_EU,Ma_EU,Cen_EU,Ie_EU,Ft_EU,Pos,Vel,Acc); */
  _SFD_EML_CALL(0, -7);
  sf_debug_symbol_scope_pop();
  for (c3_i61 = 0; c3_i61 < 6; c3_i61 = c3_i61 + 1) {
    (*c3_c_Torque)[c3_i61] = c3_Torque[c3_i61];
  }

  for (c3_i62 = 0; c3_i62 < 36; c3_i62 = c3_i62 + 1) {
    (*c3_c_JntVel)[c3_i62] = c3_JntVel[c3_i62];
  }

  for (c3_i63 = 0; c3_i63 < 36; c3_i63 = c3_i63 + 1) {
    (*c3_c_JntAcc)[c3_i63] = c3_JntAcc[c3_i63];
  }

  for (c3_i64 = 0; c3_i64 < 36; c3_i64 = c3_i64 + 1) {
    (*c3_c_JntF)[c3_i64] = c3_JntF[c3_i64];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2);
  _sfEvent_ = c3_previousEvent;
  sf_debug_check_for_state_inconsistency(_EurlerDynJointVerifyMachineNumber_,
    chartInstance->chartNumber, chartInstance->
    instanceNumber);
}

static void compInitSubchartSimstructsFcn_c3_EurlerDynJointVerify
  (SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 0U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/DynEuler.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 1U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expg.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 2U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/GoogolTraj/basicfunction/expr.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 3U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/GoogolTraj/basicfunction/hat.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 4U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/basicfunction/Adj.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 5U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/GoogolTraj/basicfunction/ad.m"));
}

static void c3_DynEuler(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_DH[28], real_T c3_Ma[6], real_T c3_Cen[18]
  , real_T c3_Ie[54], real_T c3_Ft[6], real_T c3_Pos[6], real_T c3_Vel[6],
  real_T c3_Acc[6], real_T c3_Torque[6], real_T c3_JntVel[36]
  , real_T c3_JntAcc[36], real_T c3_JntF[36])
{
  uint32_T c3_debug_family_var_map[93];
  static const char *c3_sv1[93] = { "w_o", "w_z", "kxi1", "kxi2", "kxi3", "kxi4",
    "kxi5", "kxi6", "ez", "ex", "eo", "g01_0", "g12_0",
    "g23_0", "g34_0", "g45_0", "g56_0", "g67_0", "m1", "I1", "m2", "I2", "m3",
    "I3", "m4", "I4", "m5"
    , "I5", "m6", "I6", "g", "r1", "r2", "R", "r3", "r4", "r5", "r6", "M1", "M2",
    "M3", "M4", "M5",
    "M6", "V0", "dV0", "g01", "Adinvg01", "V1", "dV1", "g12", "Adinvg12", "V2",
    "dV2", "g23",
    "Adinvg23", "V3", "dV3", "g34", "Adinvg34", "V4", "dV4", "g45", "Adinvg45",
    "V5", "dV5", "g56",
    "Adinvg56", "V6", "dV6", "Tau", "F7", "Adinvg67", "F6", "F5", "F4", "F3",
    "F2", "F1", "nargin",
    "nargout", "DH", "Ma", "Cen", "Ie", "Ft", "Pos", "Vel", "Acc", "Torque",
    "JntVel", "JntAcc",
    "JntF" };

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
  real_T c3_m1;
  real_T c3_I1[9];
  real_T c3_m2;
  real_T c3_I2[9];
  real_T c3_m3;
  real_T c3_I3[9];
  real_T c3_m4;
  real_T c3_I4[9];
  real_T c3_m5;
  real_T c3_I5[9];
  real_T c3_m6;
  real_T c3_I6[9];
  real_T c3_g[16];
  real_T c3_r1[4];
  real_T c3_r2[4];
  real_T c3_R[9];
  real_T c3_r3[4];
  real_T c3_r4[4];
  real_T c3_r5[4];
  real_T c3_r6[4];
  real_T c3_M1[36];
  real_T c3_M2[36];
  real_T c3_M3[36];
  real_T c3_M4[36];
  real_T c3_M5[36];
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
  real_T c3_nargin = 8.0;
  real_T c3_nargout = 4.0;
  int32_T c3_i65;
  int32_T c3_i66;
  int32_T c3_i67;
  int32_T c3_i68;
  int32_T c3_i69;
  int32_T c3_i70;
  static real_T c3_dv9[3] = { 0.0, 0.0, 1.0 };

  int32_T c3_i71;
  static real_T c3_dv10[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c3_i72;
  int32_T c3_i73;
  int32_T c3_i74;
  int32_T c3_i75;
  int32_T c3_i76;
  int32_T c3_i77;
  int32_T c3_i78;
  static real_T c3_dv11[3] = { 1.0, 0.0, 0.0 };

  int32_T c3_i79;
  int32_T c3_i80;
  real_T c3_dv12[6];
  real_T c3_a[16];
  int32_T c3_i81;
  static real_T c3_dv13[6] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };

  real_T c3_dv14[6];
  real_T c3_b[16];
  int32_T c3_i82;
  real_T c3_A[16];
  int32_T c3_i83;
  real_T c3_B[16];
  int32_T c3_i84;
  real_T c3_b_A[16];
  int32_T c3_i85;
  real_T c3_b_B[16];
  int32_T c3_i86;
  real_T c3_c_A[16];
  int32_T c3_i87;
  real_T c3_c_B[16];
  int32_T c3_i88;
  int32_T c3_i89;
  int32_T c3_i90;
  real_T c3_y[16];
  int32_T c3_i91;
  int32_T c3_i92;
  int32_T c3_i93;
  real_T c3_b_a[16];
  int32_T c3_i94;
  static real_T c3_dv15[6] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };

  real_T c3_dv16[6];
  real_T c3_b_b[16];
  int32_T c3_i95;
  real_T c3_d_A[16];
  int32_T c3_i96;
  real_T c3_d_B[16];
  int32_T c3_i97;
  real_T c3_e_A[16];
  int32_T c3_i98;
  real_T c3_e_B[16];
  int32_T c3_i99;
  real_T c3_f_A[16];
  int32_T c3_i100;
  real_T c3_f_B[16];
  int32_T c3_i101;
  int32_T c3_i102;
  int32_T c3_i103;
  real_T c3_b_y[16];
  int32_T c3_i104;
  int32_T c3_i105;
  int32_T c3_i106;
  real_T c3_c_a[16];
  int32_T c3_i107;
  static real_T c3_dv17[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  real_T c3_dv18[6];
  real_T c3_c_b[16];
  int32_T c3_i108;
  real_T c3_g_A[16];
  int32_T c3_i109;
  real_T c3_g_B[16];
  int32_T c3_i110;
  int32_T c3_i111;
  real_T c3_h_A[16];
  int32_T c3_i112;
  real_T c3_h_B[16];
  int32_T c3_i113;
  real_T c3_i_A[16];
  int32_T c3_i114;
  real_T c3_i_B[16];
  int32_T c3_i115;
  int32_T c3_i116;
  int32_T c3_i117;
  int32_T c3_i118;
  int32_T c3_i119;
  int32_T c3_i120;
  real_T c3_dv19[6];
  real_T c3_d_a[16];
  int32_T c3_i121;
  real_T c3_dv20[6];
  real_T c3_d_b[16];
  int32_T c3_i122;
  real_T c3_j_A[16];
  int32_T c3_i123;
  real_T c3_j_B[16];
  int32_T c3_i124;
  real_T c3_k_A[16];
  int32_T c3_i125;
  real_T c3_k_B[16];
  int32_T c3_i126;
  real_T c3_l_A[16];
  int32_T c3_i127;
  real_T c3_l_B[16];
  int32_T c3_i128;
  int32_T c3_i129;
  int32_T c3_i130;
  real_T c3_c_y[16];
  int32_T c3_i131;
  int32_T c3_i132;
  int32_T c3_i133;
  real_T c3_e_a[16];
  int32_T c3_i134;
  real_T c3_dv21[6];
  real_T c3_e_b[16];
  int32_T c3_i135;
  real_T c3_m_A[16];
  int32_T c3_i136;
  real_T c3_m_B[16];
  int32_T c3_i137;
  real_T c3_n_A[16];
  int32_T c3_i138;
  real_T c3_n_B[16];
  int32_T c3_i139;
  real_T c3_o_A[16];
  int32_T c3_i140;
  real_T c3_o_B[16];
  int32_T c3_i141;
  int32_T c3_i142;
  int32_T c3_i143;
  real_T c3_d_y[16];
  int32_T c3_i144;
  int32_T c3_i145;
  int32_T c3_i146;
  real_T c3_f_a[16];
  int32_T c3_i147;
  real_T c3_dv22[6];
  real_T c3_f_b[16];
  int32_T c3_i148;
  real_T c3_p_A[16];
  int32_T c3_i149;
  real_T c3_p_B[16];
  int32_T c3_i150;
  int32_T c3_i151;
  real_T c3_q_A[16];
  int32_T c3_i152;
  real_T c3_q_B[16];
  int32_T c3_i153;
  real_T c3_r_A[16];
  int32_T c3_i154;
  real_T c3_r_B[16];
  int32_T c3_i155;
  int32_T c3_i156;
  int32_T c3_i157;
  int32_T c3_i158;
  int32_T c3_i159;
  int32_T c3_i160;
  real_T c3_dv23[6];
  real_T c3_g_a[16];
  int32_T c3_i161;
  real_T c3_dv24[6];
  real_T c3_g_b[16];
  int32_T c3_i162;
  real_T c3_s_A[16];
  int32_T c3_i163;
  real_T c3_s_B[16];
  int32_T c3_i164;
  real_T c3_t_A[16];
  int32_T c3_i165;
  real_T c3_t_B[16];
  int32_T c3_i166;
  real_T c3_u_A[16];
  int32_T c3_i167;
  real_T c3_u_B[16];
  int32_T c3_i168;
  int32_T c3_i169;
  int32_T c3_i170;
  real_T c3_e_y[16];
  int32_T c3_i171;
  int32_T c3_i172;
  int32_T c3_i173;
  real_T c3_h_a[16];
  int32_T c3_i174;
  real_T c3_dv25[6];
  real_T c3_h_b[16];
  int32_T c3_i175;
  real_T c3_v_A[16];
  int32_T c3_i176;
  real_T c3_v_B[16];
  int32_T c3_i177;
  real_T c3_w_A[16];
  int32_T c3_i178;
  real_T c3_w_B[16];
  int32_T c3_i179;
  real_T c3_x_A[16];
  int32_T c3_i180;
  real_T c3_x_B[16];
  int32_T c3_i181;
  int32_T c3_i182;
  int32_T c3_i183;
  real_T c3_f_y[16];
  int32_T c3_i184;
  int32_T c3_i185;
  int32_T c3_i186;
  real_T c3_i_a[16];
  int32_T c3_i187;
  real_T c3_dv26[6];
  real_T c3_i_b[16];
  int32_T c3_i188;
  real_T c3_y_A[16];
  int32_T c3_i189;
  real_T c3_y_B[16];
  int32_T c3_i190;
  int32_T c3_i191;
  real_T c3_ab_A[16];
  int32_T c3_i192;
  real_T c3_ab_B[16];
  int32_T c3_i193;
  real_T c3_bb_A[16];
  int32_T c3_i194;
  real_T c3_bb_B[16];
  int32_T c3_i195;
  int32_T c3_i196;
  int32_T c3_i197;
  int32_T c3_i198;
  int32_T c3_i199;
  int32_T c3_i200;
  real_T c3_dv27[6];
  real_T c3_j_a[16];
  int32_T c3_i201;
  real_T c3_dv28[6];
  real_T c3_j_b[16];
  int32_T c3_i202;
  real_T c3_cb_A[16];
  int32_T c3_i203;
  real_T c3_cb_B[16];
  int32_T c3_i204;
  real_T c3_db_A[16];
  int32_T c3_i205;
  real_T c3_db_B[16];
  int32_T c3_i206;
  real_T c3_eb_A[16];
  int32_T c3_i207;
  real_T c3_eb_B[16];
  int32_T c3_i208;
  int32_T c3_i209;
  int32_T c3_i210;
  real_T c3_g_y[16];
  int32_T c3_i211;
  int32_T c3_i212;
  int32_T c3_i213;
  real_T c3_k_a[16];
  int32_T c3_i214;
  real_T c3_dv29[6];
  real_T c3_k_b[16];
  int32_T c3_i215;
  real_T c3_fb_A[16];
  int32_T c3_i216;
  real_T c3_fb_B[16];
  int32_T c3_i217;
  real_T c3_gb_A[16];
  int32_T c3_i218;
  real_T c3_gb_B[16];
  int32_T c3_i219;
  real_T c3_hb_A[16];
  int32_T c3_i220;
  real_T c3_hb_B[16];
  int32_T c3_i221;
  int32_T c3_i222;
  int32_T c3_i223;
  real_T c3_h_y[16];
  int32_T c3_i224;
  int32_T c3_i225;
  int32_T c3_i226;
  real_T c3_l_a[16];
  int32_T c3_i227;
  real_T c3_dv30[6];
  real_T c3_l_b[16];
  int32_T c3_i228;
  real_T c3_ib_A[16];
  int32_T c3_i229;
  real_T c3_ib_B[16];
  int32_T c3_i230;
  int32_T c3_i231;
  real_T c3_jb_A[16];
  int32_T c3_i232;
  real_T c3_jb_B[16];
  int32_T c3_i233;
  real_T c3_kb_A[16];
  int32_T c3_i234;
  real_T c3_kb_B[16];
  int32_T c3_i235;
  int32_T c3_i236;
  int32_T c3_i237;
  int32_T c3_i238;
  int32_T c3_i239;
  int32_T c3_i240;
  real_T c3_dv31[6];
  real_T c3_m_a[16];
  int32_T c3_i241;
  real_T c3_dv32[6];
  real_T c3_m_b[16];
  int32_T c3_i242;
  real_T c3_lb_A[16];
  int32_T c3_i243;
  real_T c3_lb_B[16];
  int32_T c3_i244;
  real_T c3_mb_A[16];
  int32_T c3_i245;
  real_T c3_mb_B[16];
  int32_T c3_i246;
  real_T c3_nb_A[16];
  int32_T c3_i247;
  real_T c3_nb_B[16];
  int32_T c3_i248;
  int32_T c3_i249;
  int32_T c3_i250;
  real_T c3_i_y[16];
  int32_T c3_i251;
  int32_T c3_i252;
  int32_T c3_i253;
  real_T c3_n_a[16];
  int32_T c3_i254;
  real_T c3_dv33[6];
  real_T c3_n_b[16];
  int32_T c3_i255;
  real_T c3_ob_A[16];
  int32_T c3_i256;
  real_T c3_ob_B[16];
  int32_T c3_i257;
  real_T c3_pb_A[16];
  int32_T c3_i258;
  real_T c3_pb_B[16];
  int32_T c3_i259;
  real_T c3_qb_A[16];
  int32_T c3_i260;
  real_T c3_qb_B[16];
  int32_T c3_i261;
  int32_T c3_i262;
  int32_T c3_i263;
  real_T c3_j_y[16];
  int32_T c3_i264;
  int32_T c3_i265;
  int32_T c3_i266;
  real_T c3_o_a[16];
  int32_T c3_i267;
  real_T c3_dv34[6];
  real_T c3_o_b[16];
  int32_T c3_i268;
  real_T c3_rb_A[16];
  int32_T c3_i269;
  real_T c3_rb_B[16];
  int32_T c3_i270;
  int32_T c3_i271;
  real_T c3_sb_A[16];
  int32_T c3_i272;
  real_T c3_sb_B[16];
  int32_T c3_i273;
  real_T c3_tb_A[16];
  int32_T c3_i274;
  real_T c3_tb_B[16];
  int32_T c3_i275;
  int32_T c3_i276;
  int32_T c3_i277;
  int32_T c3_i278;
  int32_T c3_i279;
  int32_T c3_i280;
  real_T c3_dv35[6];
  real_T c3_p_a[16];
  int32_T c3_i281;
  real_T c3_dv36[6];
  real_T c3_p_b[16];
  int32_T c3_i282;
  real_T c3_ub_A[16];
  int32_T c3_i283;
  real_T c3_ub_B[16];
  int32_T c3_i284;
  real_T c3_vb_A[16];
  int32_T c3_i285;
  real_T c3_vb_B[16];
  int32_T c3_i286;
  real_T c3_wb_A[16];
  int32_T c3_i287;
  real_T c3_wb_B[16];
  int32_T c3_i288;
  int32_T c3_i289;
  int32_T c3_i290;
  real_T c3_k_y[16];
  int32_T c3_i291;
  int32_T c3_i292;
  int32_T c3_i293;
  real_T c3_q_a[16];
  int32_T c3_i294;
  real_T c3_dv37[6];
  real_T c3_q_b[16];
  int32_T c3_i295;
  real_T c3_xb_A[16];
  int32_T c3_i296;
  real_T c3_xb_B[16];
  int32_T c3_i297;
  real_T c3_yb_A[16];
  int32_T c3_i298;
  real_T c3_yb_B[16];
  int32_T c3_i299;
  real_T c3_ac_A[16];
  int32_T c3_i300;
  real_T c3_ac_B[16];
  int32_T c3_i301;
  int32_T c3_i302;
  int32_T c3_i303;
  real_T c3_l_y[16];
  int32_T c3_i304;
  int32_T c3_i305;
  int32_T c3_i306;
  real_T c3_r_a[16];
  int32_T c3_i307;
  real_T c3_dv38[6];
  real_T c3_r_b[16];
  int32_T c3_i308;
  real_T c3_bc_A[16];
  int32_T c3_i309;
  real_T c3_bc_B[16];
  int32_T c3_i310;
  int32_T c3_i311;
  real_T c3_cc_A[16];
  int32_T c3_i312;
  real_T c3_cc_B[16];
  int32_T c3_i313;
  real_T c3_dc_A[16];
  int32_T c3_i314;
  real_T c3_dc_B[16];
  int32_T c3_i315;
  int32_T c3_i316;
  int32_T c3_i317;
  int32_T c3_i318;
  int32_T c3_i319;
  int32_T c3_i320;
  real_T c3_dv39[6];
  real_T c3_s_a[16];
  int32_T c3_i321;
  real_T c3_dv40[6];
  real_T c3_s_b[16];
  int32_T c3_i322;
  real_T c3_ec_A[16];
  int32_T c3_i323;
  real_T c3_ec_B[16];
  int32_T c3_i324;
  real_T c3_fc_A[16];
  int32_T c3_i325;
  real_T c3_fc_B[16];
  int32_T c3_i326;
  real_T c3_gc_A[16];
  int32_T c3_i327;
  real_T c3_gc_B[16];
  int32_T c3_i328;
  int32_T c3_i329;
  int32_T c3_i330;
  real_T c3_m_y[16];
  int32_T c3_i331;
  int32_T c3_i332;
  int32_T c3_i333;
  real_T c3_t_a[16];
  int32_T c3_i334;
  real_T c3_dv41[6];
  real_T c3_t_b[16];
  int32_T c3_i335;
  real_T c3_hc_A[16];
  int32_T c3_i336;
  real_T c3_hc_B[16];
  int32_T c3_i337;
  real_T c3_ic_A[16];
  int32_T c3_i338;
  real_T c3_ic_B[16];
  int32_T c3_i339;
  real_T c3_jc_A[16];
  int32_T c3_i340;
  real_T c3_jc_B[16];
  int32_T c3_i341;
  int32_T c3_i342;
  int32_T c3_i343;
  real_T c3_n_y[16];
  int32_T c3_i344;
  int32_T c3_i345;
  int32_T c3_i346;
  real_T c3_u_a[16];
  int32_T c3_i347;
  real_T c3_dv42[6];
  real_T c3_u_b[16];
  int32_T c3_i348;
  real_T c3_kc_A[16];
  int32_T c3_i349;
  real_T c3_kc_B[16];
  int32_T c3_i350;
  int32_T c3_i351;
  real_T c3_lc_A[16];
  int32_T c3_i352;
  real_T c3_lc_B[16];
  int32_T c3_i353;
  real_T c3_mc_A[16];
  int32_T c3_i354;
  real_T c3_mc_B[16];
  int32_T c3_i355;
  int32_T c3_i356;
  int32_T c3_i357;
  int32_T c3_i358;
  int32_T c3_i359;
  int32_T c3_i360;
  real_T c3_x[9];
  int32_T c3_k;
  int32_T c3_b_k;
  int32_T c3_i361;
  real_T c3_b_x[9];
  int32_T c3_c_k;
  int32_T c3_d_k;
  int32_T c3_i362;
  real_T c3_c_x[9];
  int32_T c3_e_k;
  int32_T c3_f_k;
  int32_T c3_i363;
  real_T c3_d_x[9];
  int32_T c3_g_k;
  int32_T c3_h_k;
  int32_T c3_i364;
  real_T c3_e_x[9];
  int32_T c3_i_k;
  int32_T c3_j_k;
  int32_T c3_i365;
  real_T c3_f_x[9];
  int32_T c3_k_k;
  int32_T c3_l_k;
  int32_T c3_i366;
  int32_T c3_i367;
  real_T c3_b_g[16];
  int32_T c3_i368;
  real_T c3_b_Cen[4];
  real_T c3_dv43[4];
  int32_T c3_i369;
  int32_T c3_i370;
  int32_T c3_i371;
  real_T c3_v_a[16];
  int32_T c3_i372;
  real_T c3_v_b[16];
  int32_T c3_i373;
  real_T c3_nc_A[16];
  int32_T c3_i374;
  real_T c3_nc_B[16];
  int32_T c3_i375;
  int32_T c3_i376;
  real_T c3_oc_A[16];
  int32_T c3_i377;
  real_T c3_oc_B[16];
  int32_T c3_i378;
  real_T c3_pc_A[16];
  int32_T c3_i379;
  real_T c3_pc_B[16];
  int32_T c3_i380;
  int32_T c3_i381;
  int32_T c3_i382;
  int32_T c3_i383;
  int32_T c3_i384;
  int32_T c3_i385;
  real_T c3_c_g[16];
  int32_T c3_i386;
  real_T c3_c_Cen[4];
  real_T c3_dv44[4];
  int32_T c3_i387;
  int32_T c3_i388;
  int32_T c3_i389;
  int32_T c3_i390;
  int32_T c3_i391;
  int32_T c3_i392;
  int32_T c3_i393;
  int32_T c3_i394;
  int32_T c3_i395;
  int32_T c3_i396;
  real_T c3_w_a[9];
  int32_T c3_i397;
  real_T c3_w_b[9];
  int32_T c3_i398;
  real_T c3_qc_A[9];
  int32_T c3_i399;
  real_T c3_qc_B[9];
  int32_T c3_i400;
  real_T c3_rc_A[9];
  int32_T c3_i401;
  real_T c3_rc_B[9];
  int32_T c3_i402;
  real_T c3_sc_A[9];
  int32_T c3_i403;
  real_T c3_sc_B[9];
  int32_T c3_i404;
  int32_T c3_i405;
  int32_T c3_i406;
  real_T c3_o_y[9];
  int32_T c3_i407;
  int32_T c3_i408;
  int32_T c3_i409;
  real_T c3_x_a[9];
  int32_T c3_i410;
  real_T c3_x_b[9];
  int32_T c3_i411;
  real_T c3_tc_A[9];
  int32_T c3_i412;
  real_T c3_tc_B[9];
  int32_T c3_i413;
  int32_T c3_i414;
  real_T c3_uc_A[9];
  int32_T c3_i415;
  real_T c3_uc_B[9];
  int32_T c3_i416;
  real_T c3_vc_A[9];
  int32_T c3_i417;
  real_T c3_vc_B[9];
  int32_T c3_i418;
  int32_T c3_i419;
  int32_T c3_i420;
  int32_T c3_i421;
  int32_T c3_i422;
  int32_T c3_i423;
  real_T c3_y_a[16];
  int32_T c3_i424;
  real_T c3_y_b[16];
  int32_T c3_i425;
  real_T c3_wc_A[16];
  int32_T c3_i426;
  real_T c3_wc_B[16];
  int32_T c3_i427;
  int32_T c3_i428;
  real_T c3_xc_A[16];
  int32_T c3_i429;
  real_T c3_xc_B[16];
  int32_T c3_i430;
  real_T c3_yc_A[16];
  int32_T c3_i431;
  real_T c3_yc_B[16];
  int32_T c3_i432;
  int32_T c3_i433;
  int32_T c3_i434;
  int32_T c3_i435;
  int32_T c3_i436;
  int32_T c3_i437;
  real_T c3_d_g[16];
  int32_T c3_i438;
  real_T c3_d_Cen[4];
  real_T c3_dv45[4];
  int32_T c3_i439;
  int32_T c3_i440;
  int32_T c3_i441;
  int32_T c3_i442;
  int32_T c3_i443;
  int32_T c3_i444;
  int32_T c3_i445;
  int32_T c3_i446;
  int32_T c3_i447;
  int32_T c3_i448;
  real_T c3_ab_a[9];
  int32_T c3_i449;
  real_T c3_ab_b[9];
  int32_T c3_i450;
  real_T c3_ad_A[9];
  int32_T c3_i451;
  real_T c3_ad_B[9];
  int32_T c3_i452;
  real_T c3_bd_A[9];
  int32_T c3_i453;
  real_T c3_bd_B[9];
  int32_T c3_i454;
  real_T c3_cd_A[9];
  int32_T c3_i455;
  real_T c3_cd_B[9];
  int32_T c3_i456;
  int32_T c3_i457;
  int32_T c3_i458;
  real_T c3_p_y[9];
  int32_T c3_i459;
  int32_T c3_i460;
  int32_T c3_i461;
  real_T c3_bb_a[9];
  int32_T c3_i462;
  real_T c3_bb_b[9];
  int32_T c3_i463;
  real_T c3_dd_A[9];
  int32_T c3_i464;
  real_T c3_dd_B[9];
  int32_T c3_i465;
  int32_T c3_i466;
  real_T c3_ed_A[9];
  int32_T c3_i467;
  real_T c3_ed_B[9];
  int32_T c3_i468;
  real_T c3_fd_A[9];
  int32_T c3_i469;
  real_T c3_fd_B[9];
  int32_T c3_i470;
  int32_T c3_i471;
  int32_T c3_i472;
  int32_T c3_i473;
  int32_T c3_i474;
  int32_T c3_i475;
  real_T c3_cb_a[16];
  int32_T c3_i476;
  real_T c3_cb_b[16];
  int32_T c3_i477;
  real_T c3_gd_A[16];
  int32_T c3_i478;
  real_T c3_gd_B[16];
  int32_T c3_i479;
  int32_T c3_i480;
  real_T c3_hd_A[16];
  int32_T c3_i481;
  real_T c3_hd_B[16];
  int32_T c3_i482;
  real_T c3_id_A[16];
  int32_T c3_i483;
  real_T c3_id_B[16];
  int32_T c3_i484;
  int32_T c3_i485;
  int32_T c3_i486;
  int32_T c3_i487;
  int32_T c3_i488;
  int32_T c3_i489;
  real_T c3_e_g[16];
  int32_T c3_i490;
  real_T c3_e_Cen[4];
  real_T c3_dv46[4];
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
  real_T c3_db_a[9];
  int32_T c3_i501;
  real_T c3_db_b[9];
  int32_T c3_i502;
  real_T c3_jd_A[9];
  int32_T c3_i503;
  real_T c3_jd_B[9];
  int32_T c3_i504;
  real_T c3_kd_A[9];
  int32_T c3_i505;
  real_T c3_kd_B[9];
  int32_T c3_i506;
  real_T c3_ld_A[9];
  int32_T c3_i507;
  real_T c3_ld_B[9];
  int32_T c3_i508;
  int32_T c3_i509;
  int32_T c3_i510;
  real_T c3_q_y[9];
  int32_T c3_i511;
  int32_T c3_i512;
  int32_T c3_i513;
  real_T c3_eb_a[9];
  int32_T c3_i514;
  real_T c3_eb_b[9];
  int32_T c3_i515;
  real_T c3_md_A[9];
  int32_T c3_i516;
  real_T c3_md_B[9];
  int32_T c3_i517;
  int32_T c3_i518;
  real_T c3_nd_A[9];
  int32_T c3_i519;
  real_T c3_nd_B[9];
  int32_T c3_i520;
  real_T c3_od_A[9];
  int32_T c3_i521;
  real_T c3_od_B[9];
  int32_T c3_i522;
  int32_T c3_i523;
  int32_T c3_i524;
  int32_T c3_i525;
  int32_T c3_i526;
  int32_T c3_i527;
  real_T c3_fb_a[16];
  int32_T c3_i528;
  real_T c3_fb_b[16];
  int32_T c3_i529;
  real_T c3_pd_A[16];
  int32_T c3_i530;
  real_T c3_pd_B[16];
  int32_T c3_i531;
  int32_T c3_i532;
  real_T c3_qd_A[16];
  int32_T c3_i533;
  real_T c3_qd_B[16];
  int32_T c3_i534;
  real_T c3_rd_A[16];
  int32_T c3_i535;
  real_T c3_rd_B[16];
  int32_T c3_i536;
  int32_T c3_i537;
  int32_T c3_i538;
  int32_T c3_i539;
  int32_T c3_i540;
  int32_T c3_i541;
  real_T c3_f_g[16];
  int32_T c3_i542;
  real_T c3_f_Cen[4];
  real_T c3_dv47[4];
  int32_T c3_i543;
  int32_T c3_i544;
  int32_T c3_i545;
  int32_T c3_i546;
  int32_T c3_i547;
  int32_T c3_i548;
  int32_T c3_i549;
  int32_T c3_i550;
  int32_T c3_i551;
  int32_T c3_i552;
  real_T c3_gb_a[9];
  int32_T c3_i553;
  real_T c3_gb_b[9];
  int32_T c3_i554;
  real_T c3_sd_A[9];
  int32_T c3_i555;
  real_T c3_sd_B[9];
  int32_T c3_i556;
  real_T c3_td_A[9];
  int32_T c3_i557;
  real_T c3_td_B[9];
  int32_T c3_i558;
  real_T c3_ud_A[9];
  int32_T c3_i559;
  real_T c3_ud_B[9];
  int32_T c3_i560;
  int32_T c3_i561;
  int32_T c3_i562;
  real_T c3_r_y[9];
  int32_T c3_i563;
  int32_T c3_i564;
  int32_T c3_i565;
  real_T c3_hb_a[9];
  int32_T c3_i566;
  real_T c3_hb_b[9];
  int32_T c3_i567;
  real_T c3_vd_A[9];
  int32_T c3_i568;
  real_T c3_vd_B[9];
  int32_T c3_i569;
  int32_T c3_i570;
  real_T c3_wd_A[9];
  int32_T c3_i571;
  real_T c3_wd_B[9];
  int32_T c3_i572;
  real_T c3_xd_A[9];
  int32_T c3_i573;
  real_T c3_xd_B[9];
  int32_T c3_i574;
  int32_T c3_i575;
  int32_T c3_i576;
  int32_T c3_i577;
  int32_T c3_i578;
  int32_T c3_i579;
  real_T c3_ib_a[16];
  int32_T c3_i580;
  real_T c3_ib_b[16];
  int32_T c3_i581;
  real_T c3_yd_A[16];
  int32_T c3_i582;
  real_T c3_yd_B[16];
  int32_T c3_i583;
  int32_T c3_i584;
  real_T c3_ae_A[16];
  int32_T c3_i585;
  real_T c3_ae_B[16];
  int32_T c3_i586;
  real_T c3_be_A[16];
  int32_T c3_i587;
  real_T c3_be_B[16];
  int32_T c3_i588;
  int32_T c3_i589;
  int32_T c3_i590;
  int32_T c3_i591;
  int32_T c3_i592;
  int32_T c3_i593;
  real_T c3_g_g[16];
  int32_T c3_i594;
  real_T c3_g_Cen[4];
  real_T c3_dv48[4];
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
  real_T c3_jb_a[9];
  int32_T c3_i605;
  real_T c3_jb_b[9];
  int32_T c3_i606;
  real_T c3_ce_A[9];
  int32_T c3_i607;
  real_T c3_ce_B[9];
  int32_T c3_i608;
  real_T c3_de_A[9];
  int32_T c3_i609;
  real_T c3_de_B[9];
  int32_T c3_i610;
  real_T c3_ee_A[9];
  int32_T c3_i611;
  real_T c3_ee_B[9];
  int32_T c3_i612;
  int32_T c3_i613;
  int32_T c3_i614;
  real_T c3_s_y[9];
  int32_T c3_i615;
  int32_T c3_i616;
  int32_T c3_i617;
  real_T c3_kb_a[9];
  int32_T c3_i618;
  real_T c3_kb_b[9];
  int32_T c3_i619;
  real_T c3_fe_A[9];
  int32_T c3_i620;
  real_T c3_fe_B[9];
  int32_T c3_i621;
  int32_T c3_i622;
  real_T c3_ge_A[9];
  int32_T c3_i623;
  real_T c3_ge_B[9];
  int32_T c3_i624;
  real_T c3_he_A[9];
  int32_T c3_i625;
  real_T c3_he_B[9];
  int32_T c3_i626;
  int32_T c3_i627;
  int32_T c3_i628;
  int32_T c3_i629;
  int32_T c3_i630;
  real_T c3_lb_a;
  int32_T c3_i631;
  static real_T c3_dv49[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c3_t_y[9];
  real_T c3_mb_a;
  int32_T c3_i632;
  real_T c3_c_r1[3];
  real_T c3_lb_b[9];
  int32_T c3_i633;
  real_T c3_u_y[9];
  real_T c3_nb_a;
  int32_T c3_i634;
  real_T c3_d_r1[3];
  real_T c3_mb_b[9];
  int32_T c3_i635;
  real_T c3_v_y[9];
  real_T c3_ob_a;
  int32_T c3_i636;
  real_T c3_e_r1[3];
  real_T c3_nb_b[9];
  int32_T c3_i637;
  real_T c3_w_y[9];
  int32_T c3_i638;
  real_T c3_pb_a[9];
  int32_T c3_i639;
  real_T c3_f_r1[3];
  real_T c3_ob_b[9];
  int32_T c3_i640;
  real_T c3_ie_A[9];
  int32_T c3_i641;
  real_T c3_ie_B[9];
  int32_T c3_i642;
  real_T c3_je_A[9];
  int32_T c3_i643;
  real_T c3_je_B[9];
  int32_T c3_i644;
  real_T c3_ke_A[9];
  int32_T c3_i645;
  real_T c3_ke_B[9];
  int32_T c3_i646;
  int32_T c3_i647;
  int32_T c3_i648;
  real_T c3_x_y[9];
  int32_T c3_i649;
  int32_T c3_i650;
  int32_T c3_i651;
  int32_T c3_i652;
  int32_T c3_i653;
  int32_T c3_i654;
  int32_T c3_i655;
  int32_T c3_i656;
  int32_T c3_i657;
  int32_T c3_i658;
  int32_T c3_i659;
  int32_T c3_i660;
  int32_T c3_i661;
  int32_T c3_i662;
  int32_T c3_i663;
  int32_T c3_i664;
  int32_T c3_i665;
  int32_T c3_i666;
  real_T c3_qb_a;
  int32_T c3_i667;
  real_T c3_y_y[9];
  real_T c3_rb_a;
  int32_T c3_i668;
  real_T c3_c_r2[3];
  real_T c3_pb_b[9];
  int32_T c3_i669;
  real_T c3_ab_y[9];
  real_T c3_sb_a;
  int32_T c3_i670;
  real_T c3_d_r2[3];
  real_T c3_qb_b[9];
  int32_T c3_i671;
  real_T c3_bb_y[9];
  real_T c3_tb_a;
  int32_T c3_i672;
  real_T c3_e_r2[3];
  real_T c3_rb_b[9];
  int32_T c3_i673;
  real_T c3_cb_y[9];
  int32_T c3_i674;
  real_T c3_ub_a[9];
  int32_T c3_i675;
  real_T c3_f_r2[3];
  real_T c3_sb_b[9];
  int32_T c3_i676;
  real_T c3_le_A[9];
  int32_T c3_i677;
  real_T c3_le_B[9];
  int32_T c3_i678;
  real_T c3_me_A[9];
  int32_T c3_i679;
  real_T c3_me_B[9];
  int32_T c3_i680;
  real_T c3_ne_A[9];
  int32_T c3_i681;
  real_T c3_ne_B[9];
  int32_T c3_i682;
  int32_T c3_i683;
  int32_T c3_i684;
  real_T c3_db_y[9];
  int32_T c3_i685;
  int32_T c3_i686;
  int32_T c3_i687;
  int32_T c3_i688;
  int32_T c3_i689;
  int32_T c3_i690;
  int32_T c3_i691;
  int32_T c3_i692;
  int32_T c3_i693;
  int32_T c3_i694;
  int32_T c3_i695;
  int32_T c3_i696;
  int32_T c3_i697;
  int32_T c3_i698;
  int32_T c3_i699;
  int32_T c3_i700;
  int32_T c3_i701;
  int32_T c3_i702;
  real_T c3_vb_a;
  int32_T c3_i703;
  real_T c3_eb_y[9];
  real_T c3_wb_a;
  int32_T c3_i704;
  real_T c3_c_r3[3];
  real_T c3_tb_b[9];
  int32_T c3_i705;
  real_T c3_fb_y[9];
  real_T c3_xb_a;
  int32_T c3_i706;
  real_T c3_d_r3[3];
  real_T c3_ub_b[9];
  int32_T c3_i707;
  real_T c3_gb_y[9];
  real_T c3_yb_a;
  int32_T c3_i708;
  real_T c3_e_r3[3];
  real_T c3_vb_b[9];
  int32_T c3_i709;
  real_T c3_hb_y[9];
  int32_T c3_i710;
  real_T c3_ac_a[9];
  int32_T c3_i711;
  real_T c3_f_r3[3];
  real_T c3_wb_b[9];
  int32_T c3_i712;
  real_T c3_oe_A[9];
  int32_T c3_i713;
  real_T c3_oe_B[9];
  int32_T c3_i714;
  real_T c3_pe_A[9];
  int32_T c3_i715;
  real_T c3_pe_B[9];
  int32_T c3_i716;
  real_T c3_qe_A[9];
  int32_T c3_i717;
  real_T c3_qe_B[9];
  int32_T c3_i718;
  int32_T c3_i719;
  int32_T c3_i720;
  real_T c3_ib_y[9];
  int32_T c3_i721;
  int32_T c3_i722;
  int32_T c3_i723;
  int32_T c3_i724;
  int32_T c3_i725;
  int32_T c3_i726;
  int32_T c3_i727;
  int32_T c3_i728;
  int32_T c3_i729;
  int32_T c3_i730;
  int32_T c3_i731;
  int32_T c3_i732;
  int32_T c3_i733;
  int32_T c3_i734;
  int32_T c3_i735;
  int32_T c3_i736;
  int32_T c3_i737;
  int32_T c3_i738;
  real_T c3_bc_a;
  int32_T c3_i739;
  real_T c3_jb_y[9];
  real_T c3_cc_a;
  int32_T c3_i740;
  real_T c3_c_r4[3];
  real_T c3_xb_b[9];
  int32_T c3_i741;
  real_T c3_kb_y[9];
  real_T c3_dc_a;
  int32_T c3_i742;
  real_T c3_d_r4[3];
  real_T c3_yb_b[9];
  int32_T c3_i743;
  real_T c3_lb_y[9];
  real_T c3_ec_a;
  int32_T c3_i744;
  real_T c3_e_r4[3];
  real_T c3_ac_b[9];
  int32_T c3_i745;
  real_T c3_mb_y[9];
  int32_T c3_i746;
  real_T c3_fc_a[9];
  int32_T c3_i747;
  real_T c3_f_r4[3];
  real_T c3_bc_b[9];
  int32_T c3_i748;
  real_T c3_re_A[9];
  int32_T c3_i749;
  real_T c3_re_B[9];
  int32_T c3_i750;
  real_T c3_se_A[9];
  int32_T c3_i751;
  real_T c3_se_B[9];
  int32_T c3_i752;
  real_T c3_te_A[9];
  int32_T c3_i753;
  real_T c3_te_B[9];
  int32_T c3_i754;
  int32_T c3_i755;
  int32_T c3_i756;
  real_T c3_nb_y[9];
  int32_T c3_i757;
  int32_T c3_i758;
  int32_T c3_i759;
  int32_T c3_i760;
  int32_T c3_i761;
  int32_T c3_i762;
  int32_T c3_i763;
  int32_T c3_i764;
  int32_T c3_i765;
  int32_T c3_i766;
  int32_T c3_i767;
  int32_T c3_i768;
  int32_T c3_i769;
  int32_T c3_i770;
  int32_T c3_i771;
  int32_T c3_i772;
  int32_T c3_i773;
  int32_T c3_i774;
  real_T c3_gc_a;
  int32_T c3_i775;
  real_T c3_ob_y[9];
  real_T c3_hc_a;
  int32_T c3_i776;
  real_T c3_c_r5[3];
  real_T c3_cc_b[9];
  int32_T c3_i777;
  real_T c3_pb_y[9];
  real_T c3_ic_a;
  int32_T c3_i778;
  real_T c3_d_r5[3];
  real_T c3_dc_b[9];
  int32_T c3_i779;
  real_T c3_qb_y[9];
  real_T c3_jc_a;
  int32_T c3_i780;
  real_T c3_e_r5[3];
  real_T c3_ec_b[9];
  int32_T c3_i781;
  real_T c3_rb_y[9];
  int32_T c3_i782;
  real_T c3_kc_a[9];
  int32_T c3_i783;
  real_T c3_f_r5[3];
  real_T c3_fc_b[9];
  int32_T c3_i784;
  real_T c3_ue_A[9];
  int32_T c3_i785;
  real_T c3_ue_B[9];
  int32_T c3_i786;
  real_T c3_ve_A[9];
  int32_T c3_i787;
  real_T c3_ve_B[9];
  int32_T c3_i788;
  real_T c3_we_A[9];
  int32_T c3_i789;
  real_T c3_we_B[9];
  int32_T c3_i790;
  int32_T c3_i791;
  int32_T c3_i792;
  real_T c3_sb_y[9];
  int32_T c3_i793;
  int32_T c3_i794;
  int32_T c3_i795;
  int32_T c3_i796;
  int32_T c3_i797;
  int32_T c3_i798;
  int32_T c3_i799;
  int32_T c3_i800;
  int32_T c3_i801;
  int32_T c3_i802;
  int32_T c3_i803;
  int32_T c3_i804;
  int32_T c3_i805;
  int32_T c3_i806;
  int32_T c3_i807;
  int32_T c3_i808;
  int32_T c3_i809;
  int32_T c3_i810;
  real_T c3_lc_a;
  int32_T c3_i811;
  real_T c3_tb_y[9];
  real_T c3_mc_a;
  int32_T c3_i812;
  real_T c3_c_r6[3];
  real_T c3_gc_b[9];
  int32_T c3_i813;
  real_T c3_ub_y[9];
  real_T c3_nc_a;
  int32_T c3_i814;
  real_T c3_d_r6[3];
  real_T c3_hc_b[9];
  int32_T c3_i815;
  real_T c3_vb_y[9];
  real_T c3_oc_a;
  int32_T c3_i816;
  real_T c3_e_r6[3];
  real_T c3_ic_b[9];
  int32_T c3_i817;
  real_T c3_wb_y[9];
  int32_T c3_i818;
  real_T c3_pc_a[9];
  int32_T c3_i819;
  real_T c3_f_r6[3];
  real_T c3_jc_b[9];
  int32_T c3_i820;
  real_T c3_xe_A[9];
  int32_T c3_i821;
  real_T c3_xe_B[9];
  int32_T c3_i822;
  real_T c3_ye_A[9];
  int32_T c3_i823;
  real_T c3_ye_B[9];
  int32_T c3_i824;
  real_T c3_af_A[9];
  int32_T c3_i825;
  real_T c3_af_B[9];
  int32_T c3_i826;
  int32_T c3_i827;
  int32_T c3_i828;
  real_T c3_xb_y[9];
  int32_T c3_i829;
  int32_T c3_i830;
  int32_T c3_i831;
  int32_T c3_i832;
  int32_T c3_i833;
  int32_T c3_i834;
  int32_T c3_i835;
  int32_T c3_i836;
  int32_T c3_i837;
  int32_T c3_i838;
  int32_T c3_i839;
  int32_T c3_i840;
  int32_T c3_i841;
  int32_T c3_i842;
  int32_T c3_i843;
  int32_T c3_i844;
  int32_T c3_i845;
  int32_T c3_i846;
  int32_T c3_i847;
  int32_T c3_i848;
  static real_T c3_dv50[6] = { 0.0, 0.0, 9.8, 0.0, 0.0, 0.0 };

  int32_T c3_i849;
  real_T c3_qc_a[16];
  int32_T c3_i850;
  real_T c3_dv51[6];
  real_T c3_kc_b[16];
  int32_T c3_i851;
  real_T c3_bf_A[16];
  int32_T c3_i852;
  real_T c3_bf_B[16];
  int32_T c3_i853;
  int32_T c3_i854;
  real_T c3_cf_A[16];
  int32_T c3_i855;
  real_T c3_cf_B[16];
  int32_T c3_i856;
  real_T c3_df_A[16];
  int32_T c3_i857;
  real_T c3_df_B[16];
  int32_T c3_i858;
  int32_T c3_i859;
  int32_T c3_i860;
  int32_T c3_i861;
  int32_T c3_i862;
  int32_T c3_i863;
  real_T c3_b_g01[16];
  int32_T c3_i864;
  static real_T c3_dv52[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c3_dv53[16];
  real_T c3_dv54[16];
  int32_T c3_i865;
  real_T c3_dv55[16];
  real_T c3_dv56[36];
  int32_T c3_i866;
  int32_T c3_i867;
  real_T c3_rc_a[36];
  int32_T c3_i868;
  real_T c3_sc_a[36];
  int32_T c3_i869;
  real_T c3_dv57[6];
  int32_T c3_i870;
  real_T c3_dv58[6];
  real_T c3_yb_y[6];
  real_T c3_lc_b;
  int32_T c3_i871;
  real_T c3_ac_y[6];
  int32_T c3_i872;
  real_T c3_mc_b;
  int32_T c3_i873;
  real_T c3_bc_y[6];
  int32_T c3_i874;
  real_T c3_tc_a[36];
  int32_T c3_i875;
  real_T c3_uc_a[36];
  int32_T c3_i876;
  real_T c3_dv59[6];
  int32_T c3_i877;
  real_T c3_dv60[6];
  real_T c3_cc_y[6];
  real_T c3_nc_b;
  int32_T c3_i878;
  real_T c3_dc_y[6];
  int32_T c3_i879;
  real_T c3_vc_a[36];
  int32_T c3_i880;
  real_T c3_wc_a[36];
  int32_T c3_i881;
  real_T c3_dv61[6];
  int32_T c3_i882;
  real_T c3_dv62[6];
  real_T c3_ec_y[6];
  int32_T c3_i883;
  real_T c3_fc_y[6];
  real_T c3_xc_a[36];
  int32_T c3_i884;
  real_T c3_oc_b[6];
  int32_T c3_i885;
  real_T c3_yc_a[36];
  int32_T c3_i886;
  real_T c3_pc_b[6];
  int32_T c3_i887;
  real_T c3_dv63[6];
  real_T c3_gc_y[6];
  int32_T c3_i888;
  int32_T c3_i889;
  int32_T c3_i890;
  int32_T c3_i891;
  real_T c3_ad_a[16];
  int32_T c3_i892;
  real_T c3_dv64[6];
  real_T c3_qc_b[16];
  int32_T c3_i893;
  real_T c3_ef_A[16];
  int32_T c3_i894;
  real_T c3_ef_B[16];
  int32_T c3_i895;
  int32_T c3_i896;
  real_T c3_ff_A[16];
  int32_T c3_i897;
  real_T c3_ff_B[16];
  int32_T c3_i898;
  real_T c3_gf_A[16];
  int32_T c3_i899;
  real_T c3_gf_B[16];
  int32_T c3_i900;
  int32_T c3_i901;
  int32_T c3_i902;
  int32_T c3_i903;
  int32_T c3_i904;
  int32_T c3_i905;
  real_T c3_b_g12[16];
  int32_T c3_i906;
  real_T c3_dv65[16];
  real_T c3_dv66[16];
  int32_T c3_i907;
  real_T c3_dv67[16];
  real_T c3_dv68[36];
  int32_T c3_i908;
  int32_T c3_i909;
  real_T c3_bd_a[36];
  int32_T c3_i910;
  real_T c3_rc_b[6];
  int32_T c3_i911;
  real_T c3_cd_a[36];
  int32_T c3_i912;
  real_T c3_sc_b[6];
  int32_T c3_i913;
  real_T c3_dv69[6];
  real_T c3_hc_y[6];
  real_T c3_tc_b;
  int32_T c3_i914;
  real_T c3_ic_y[6];
  int32_T c3_i915;
  real_T c3_uc_b;
  int32_T c3_i916;
  real_T c3_jc_y[6];
  int32_T c3_i917;
  real_T c3_dd_a[36];
  int32_T c3_i918;
  real_T c3_vc_b[6];
  int32_T c3_i919;
  real_T c3_ed_a[36];
  int32_T c3_i920;
  real_T c3_wc_b[6];
  int32_T c3_i921;
  real_T c3_dv70[6];
  real_T c3_kc_y[6];
  real_T c3_xc_b;
  int32_T c3_i922;
  real_T c3_lc_y[6];
  int32_T c3_i923;
  real_T c3_fd_a[36];
  int32_T c3_i924;
  real_T c3_yc_b[6];
  int32_T c3_i925;
  real_T c3_gd_a[36];
  int32_T c3_i926;
  real_T c3_ad_b[6];
  int32_T c3_i927;
  real_T c3_dv71[6];
  real_T c3_mc_y[6];
  int32_T c3_i928;
  real_T c3_nc_y[6];
  real_T c3_hd_a[36];
  int32_T c3_i929;
  real_T c3_bd_b[6];
  int32_T c3_i930;
  real_T c3_id_a[36];
  int32_T c3_i931;
  real_T c3_cd_b[6];
  int32_T c3_i932;
  real_T c3_dv72[6];
  real_T c3_oc_y[6];
  int32_T c3_i933;
  int32_T c3_i934;
  int32_T c3_i935;
  int32_T c3_i936;
  real_T c3_jd_a[16];
  int32_T c3_i937;
  real_T c3_dv73[6];
  real_T c3_dd_b[16];
  int32_T c3_i938;
  real_T c3_hf_A[16];
  int32_T c3_i939;
  real_T c3_hf_B[16];
  int32_T c3_i940;
  int32_T c3_i941;
  real_T c3_if_A[16];
  int32_T c3_i942;
  real_T c3_if_B[16];
  int32_T c3_i943;
  real_T c3_jf_A[16];
  int32_T c3_i944;
  real_T c3_jf_B[16];
  int32_T c3_i945;
  int32_T c3_i946;
  int32_T c3_i947;
  int32_T c3_i948;
  int32_T c3_i949;
  int32_T c3_i950;
  real_T c3_b_g23[16];
  int32_T c3_i951;
  real_T c3_dv74[16];
  real_T c3_dv75[16];
  int32_T c3_i952;
  real_T c3_dv76[16];
  real_T c3_dv77[36];
  int32_T c3_i953;
  int32_T c3_i954;
  real_T c3_kd_a[36];
  int32_T c3_i955;
  real_T c3_ed_b[6];
  int32_T c3_i956;
  real_T c3_ld_a[36];
  int32_T c3_i957;
  real_T c3_fd_b[6];
  int32_T c3_i958;
  real_T c3_dv78[6];
  real_T c3_pc_y[6];
  real_T c3_gd_b;
  int32_T c3_i959;
  real_T c3_qc_y[6];
  int32_T c3_i960;
  real_T c3_hd_b;
  int32_T c3_i961;
  real_T c3_rc_y[6];
  int32_T c3_i962;
  real_T c3_md_a[36];
  int32_T c3_i963;
  real_T c3_id_b[6];
  int32_T c3_i964;
  real_T c3_nd_a[36];
  int32_T c3_i965;
  real_T c3_jd_b[6];
  int32_T c3_i966;
  real_T c3_dv79[6];
  real_T c3_sc_y[6];
  real_T c3_kd_b;
  int32_T c3_i967;
  real_T c3_tc_y[6];
  int32_T c3_i968;
  real_T c3_od_a[36];
  int32_T c3_i969;
  real_T c3_ld_b[6];
  int32_T c3_i970;
  real_T c3_pd_a[36];
  int32_T c3_i971;
  real_T c3_md_b[6];
  int32_T c3_i972;
  real_T c3_dv80[6];
  real_T c3_uc_y[6];
  int32_T c3_i973;
  real_T c3_vc_y[6];
  real_T c3_qd_a[36];
  int32_T c3_i974;
  real_T c3_nd_b[6];
  int32_T c3_i975;
  real_T c3_rd_a[36];
  int32_T c3_i976;
  real_T c3_od_b[6];
  int32_T c3_i977;
  real_T c3_dv81[6];
  real_T c3_wc_y[6];
  int32_T c3_i978;
  int32_T c3_i979;
  int32_T c3_i980;
  int32_T c3_i981;
  real_T c3_sd_a[16];
  int32_T c3_i982;
  real_T c3_dv82[6];
  real_T c3_pd_b[16];
  int32_T c3_i983;
  real_T c3_kf_A[16];
  int32_T c3_i984;
  real_T c3_kf_B[16];
  int32_T c3_i985;
  int32_T c3_i986;
  real_T c3_lf_A[16];
  int32_T c3_i987;
  real_T c3_lf_B[16];
  int32_T c3_i988;
  real_T c3_mf_A[16];
  int32_T c3_i989;
  real_T c3_mf_B[16];
  int32_T c3_i990;
  int32_T c3_i991;
  int32_T c3_i992;
  int32_T c3_i993;
  int32_T c3_i994;
  int32_T c3_i995;
  real_T c3_b_g34[16];
  int32_T c3_i996;
  real_T c3_dv83[16];
  real_T c3_dv84[16];
  int32_T c3_i997;
  real_T c3_dv85[16];
  real_T c3_dv86[36];
  int32_T c3_i998;
  int32_T c3_i999;
  real_T c3_td_a[36];
  int32_T c3_i1000;
  real_T c3_qd_b[6];
  int32_T c3_i1001;
  real_T c3_ud_a[36];
  int32_T c3_i1002;
  real_T c3_rd_b[6];
  int32_T c3_i1003;
  real_T c3_dv87[6];
  real_T c3_xc_y[6];
  real_T c3_sd_b;
  int32_T c3_i1004;
  real_T c3_yc_y[6];
  int32_T c3_i1005;
  real_T c3_td_b;
  int32_T c3_i1006;
  real_T c3_ad_y[6];
  int32_T c3_i1007;
  real_T c3_vd_a[36];
  int32_T c3_i1008;
  real_T c3_ud_b[6];
  int32_T c3_i1009;
  real_T c3_wd_a[36];
  int32_T c3_i1010;
  real_T c3_vd_b[6];
  int32_T c3_i1011;
  real_T c3_dv88[6];
  real_T c3_bd_y[6];
  real_T c3_wd_b;
  int32_T c3_i1012;
  real_T c3_cd_y[6];
  int32_T c3_i1013;
  real_T c3_xd_a[36];
  int32_T c3_i1014;
  real_T c3_xd_b[6];
  int32_T c3_i1015;
  real_T c3_yd_a[36];
  int32_T c3_i1016;
  real_T c3_yd_b[6];
  int32_T c3_i1017;
  real_T c3_dv89[6];
  real_T c3_dd_y[6];
  int32_T c3_i1018;
  real_T c3_ed_y[6];
  real_T c3_ae_a[36];
  int32_T c3_i1019;
  real_T c3_ae_b[6];
  int32_T c3_i1020;
  real_T c3_be_a[36];
  int32_T c3_i1021;
  real_T c3_be_b[6];
  int32_T c3_i1022;
  real_T c3_dv90[6];
  real_T c3_fd_y[6];
  int32_T c3_i1023;
  int32_T c3_i1024;
  int32_T c3_i1025;
  int32_T c3_i1026;
  real_T c3_ce_a[16];
  int32_T c3_i1027;
  real_T c3_dv91[6];
  real_T c3_ce_b[16];
  int32_T c3_i1028;
  real_T c3_nf_A[16];
  int32_T c3_i1029;
  real_T c3_nf_B[16];
  int32_T c3_i1030;
  int32_T c3_i1031;
  real_T c3_of_A[16];
  int32_T c3_i1032;
  real_T c3_of_B[16];
  int32_T c3_i1033;
  real_T c3_pf_A[16];
  int32_T c3_i1034;
  real_T c3_pf_B[16];
  int32_T c3_i1035;
  int32_T c3_i1036;
  int32_T c3_i1037;
  int32_T c3_i1038;
  int32_T c3_i1039;
  int32_T c3_i1040;
  real_T c3_b_g45[16];
  int32_T c3_i1041;
  real_T c3_dv92[16];
  real_T c3_dv93[16];
  int32_T c3_i1042;
  real_T c3_dv94[16];
  real_T c3_dv95[36];
  int32_T c3_i1043;
  int32_T c3_i1044;
  real_T c3_de_a[36];
  int32_T c3_i1045;
  real_T c3_de_b[6];
  int32_T c3_i1046;
  real_T c3_ee_a[36];
  int32_T c3_i1047;
  real_T c3_ee_b[6];
  int32_T c3_i1048;
  real_T c3_dv96[6];
  real_T c3_gd_y[6];
  real_T c3_fe_b;
  int32_T c3_i1049;
  real_T c3_hd_y[6];
  int32_T c3_i1050;
  real_T c3_ge_b;
  int32_T c3_i1051;
  real_T c3_id_y[6];
  int32_T c3_i1052;
  real_T c3_fe_a[36];
  int32_T c3_i1053;
  real_T c3_he_b[6];
  int32_T c3_i1054;
  real_T c3_ge_a[36];
  int32_T c3_i1055;
  real_T c3_ie_b[6];
  int32_T c3_i1056;
  real_T c3_dv97[6];
  real_T c3_jd_y[6];
  real_T c3_je_b;
  int32_T c3_i1057;
  real_T c3_kd_y[6];
  int32_T c3_i1058;
  real_T c3_he_a[36];
  int32_T c3_i1059;
  real_T c3_ke_b[6];
  int32_T c3_i1060;
  real_T c3_ie_a[36];
  int32_T c3_i1061;
  real_T c3_le_b[6];
  int32_T c3_i1062;
  real_T c3_dv98[6];
  real_T c3_ld_y[6];
  int32_T c3_i1063;
  real_T c3_md_y[6];
  real_T c3_je_a[36];
  int32_T c3_i1064;
  real_T c3_me_b[6];
  int32_T c3_i1065;
  real_T c3_ke_a[36];
  int32_T c3_i1066;
  real_T c3_ne_b[6];
  int32_T c3_i1067;
  real_T c3_dv99[6];
  real_T c3_nd_y[6];
  int32_T c3_i1068;
  int32_T c3_i1069;
  int32_T c3_i1070;
  int32_T c3_i1071;
  real_T c3_le_a[16];
  int32_T c3_i1072;
  real_T c3_dv100[6];
  real_T c3_oe_b[16];
  int32_T c3_i1073;
  real_T c3_qf_A[16];
  int32_T c3_i1074;
  real_T c3_qf_B[16];
  int32_T c3_i1075;
  int32_T c3_i1076;
  real_T c3_rf_A[16];
  int32_T c3_i1077;
  real_T c3_rf_B[16];
  int32_T c3_i1078;
  real_T c3_sf_A[16];
  int32_T c3_i1079;
  real_T c3_sf_B[16];
  int32_T c3_i1080;
  int32_T c3_i1081;
  int32_T c3_i1082;
  int32_T c3_i1083;
  int32_T c3_i1084;
  int32_T c3_i1085;
  real_T c3_b_g56[16];
  int32_T c3_i1086;
  real_T c3_dv101[16];
  real_T c3_dv102[16];
  int32_T c3_i1087;
  real_T c3_dv103[16];
  real_T c3_dv104[36];
  int32_T c3_i1088;
  int32_T c3_i1089;
  real_T c3_me_a[36];
  int32_T c3_i1090;
  real_T c3_pe_b[6];
  int32_T c3_i1091;
  real_T c3_ne_a[36];
  int32_T c3_i1092;
  real_T c3_qe_b[6];
  int32_T c3_i1093;
  real_T c3_dv105[6];
  real_T c3_od_y[6];
  real_T c3_re_b;
  int32_T c3_i1094;
  real_T c3_pd_y[6];
  int32_T c3_i1095;
  real_T c3_se_b;
  int32_T c3_i1096;
  real_T c3_qd_y[6];
  int32_T c3_i1097;
  real_T c3_oe_a[36];
  int32_T c3_i1098;
  real_T c3_te_b[6];
  int32_T c3_i1099;
  real_T c3_pe_a[36];
  int32_T c3_i1100;
  real_T c3_ue_b[6];
  int32_T c3_i1101;
  real_T c3_dv106[6];
  real_T c3_rd_y[6];
  real_T c3_ve_b;
  int32_T c3_i1102;
  real_T c3_sd_y[6];
  int32_T c3_i1103;
  real_T c3_qe_a[36];
  int32_T c3_i1104;
  real_T c3_we_b[6];
  int32_T c3_i1105;
  real_T c3_re_a[36];
  int32_T c3_i1106;
  real_T c3_xe_b[6];
  int32_T c3_i1107;
  real_T c3_dv107[6];
  real_T c3_td_y[6];
  int32_T c3_i1108;
  real_T c3_ud_y[6];
  real_T c3_se_a[36];
  int32_T c3_i1109;
  real_T c3_ye_b[6];
  int32_T c3_i1110;
  real_T c3_te_a[36];
  int32_T c3_i1111;
  real_T c3_af_b[6];
  int32_T c3_i1112;
  real_T c3_dv108[6];
  real_T c3_vd_y[6];
  int32_T c3_i1113;
  int32_T c3_i1114;
  int32_T c3_i1115;
  int32_T c3_i1116;
  int32_T c3_i1117;
  int32_T c3_i1118;
  real_T c3_b_g67_0[16];
  int32_T c3_i1119;
  real_T c3_dv109[16];
  real_T c3_dv110[16];
  int32_T c3_i1120;
  real_T c3_dv111[16];
  real_T c3_dv112[36];
  int32_T c3_i1121;
  int32_T c3_i1122;
  int32_T c3_i1123;
  int32_T c3_i1124;
  int32_T c3_i1125;
  real_T c3_ue_a[36];
  int32_T c3_i1126;
  real_T c3_bf_b[6];
  int32_T c3_i1127;
  real_T c3_ve_a[36];
  int32_T c3_i1128;
  real_T c3_cf_b[6];
  int32_T c3_i1129;
  real_T c3_dv113[6];
  real_T c3_wd_y[6];
  int32_T c3_i1130;
  real_T c3_we_a[36];
  int32_T c3_i1131;
  real_T c3_df_b[6];
  int32_T c3_i1132;
  real_T c3_xe_a[36];
  int32_T c3_i1133;
  real_T c3_ef_b[6];
  int32_T c3_i1134;
  real_T c3_dv114[6];
  real_T c3_xd_y[6];
  int32_T c3_i1135;
  real_T c3_b_V6[6];
  real_T c3_dv115[36];
  int32_T c3_i1136;
  int32_T c3_i1137;
  int32_T c3_i1138;
  int32_T c3_i1139;
  real_T c3_ye_a[36];
  int32_T c3_i1140;
  real_T c3_ff_b[36];
  int32_T c3_i1141;
  real_T c3_tf_A[36];
  int32_T c3_i1142;
  real_T c3_tf_B[36];
  int32_T c3_i1143;
  real_T c3_uf_A[36];
  int32_T c3_i1144;
  real_T c3_uf_B[36];
  int32_T c3_i1145;
  real_T c3_vf_A[36];
  int32_T c3_i1146;
  real_T c3_vf_B[36];
  int32_T c3_i1147;
  real_T c3_dv116[36];
  real_T c3_yd_y[36];
  int32_T c3_i1148;
  real_T c3_af_a[36];
  int32_T c3_i1149;
  real_T c3_gf_b[6];
  int32_T c3_i1150;
  real_T c3_bf_a[36];
  int32_T c3_i1151;
  real_T c3_hf_b[6];
  int32_T c3_i1152;
  real_T c3_dv117[6];
  real_T c3_ae_y[6];
  int32_T c3_i1153;
  int32_T c3_i1154;
  real_T c3_if_b[6];
  int32_T c3_i1155;
  real_T c3_be_y[6];
  int32_T c3_i1156;
  real_T c3_ce_y[6];
  int32_T c3_i1157;
  real_T c3_de_y[6];
  int32_T c3_i1158;
  real_T c3_dv118[6];
  int32_T c3_i1159;
  real_T c3_ee_y[6];
  real_T c3_fe_y;
  int32_T c3_i1160;
  int32_T c3_i1161;
  int32_T c3_i1162;
  int32_T c3_i1163;
  int32_T c3_i1164;
  real_T c3_cf_a[36];
  int32_T c3_i1165;
  real_T c3_jf_b[6];
  int32_T c3_i1166;
  real_T c3_df_a[36];
  int32_T c3_i1167;
  real_T c3_kf_b[6];
  int32_T c3_i1168;
  real_T c3_dv119[6];
  real_T c3_ge_y[6];
  int32_T c3_i1169;
  real_T c3_ef_a[36];
  int32_T c3_i1170;
  real_T c3_lf_b[6];
  int32_T c3_i1171;
  real_T c3_ff_a[36];
  int32_T c3_i1172;
  real_T c3_mf_b[6];
  int32_T c3_i1173;
  real_T c3_dv120[6];
  real_T c3_he_y[6];
  int32_T c3_i1174;
  real_T c3_b_V5[6];
  real_T c3_dv121[36];
  int32_T c3_i1175;
  int32_T c3_i1176;
  int32_T c3_i1177;
  int32_T c3_i1178;
  real_T c3_gf_a[36];
  int32_T c3_i1179;
  real_T c3_nf_b[36];
  int32_T c3_i1180;
  real_T c3_wf_A[36];
  int32_T c3_i1181;
  real_T c3_wf_B[36];
  int32_T c3_i1182;
  real_T c3_xf_A[36];
  int32_T c3_i1183;
  real_T c3_xf_B[36];
  int32_T c3_i1184;
  real_T c3_yf_A[36];
  int32_T c3_i1185;
  real_T c3_yf_B[36];
  int32_T c3_i1186;
  real_T c3_dv122[36];
  real_T c3_ie_y[36];
  int32_T c3_i1187;
  real_T c3_hf_a[36];
  int32_T c3_i1188;
  real_T c3_of_b[6];
  int32_T c3_i1189;
  real_T c3_if_a[36];
  int32_T c3_i1190;
  real_T c3_pf_b[6];
  int32_T c3_i1191;
  real_T c3_dv123[6];
  real_T c3_je_y[6];
  int32_T c3_i1192;
  int32_T c3_i1193;
  real_T c3_qf_b[6];
  int32_T c3_i1194;
  real_T c3_ke_y[6];
  int32_T c3_i1195;
  real_T c3_le_y[6];
  int32_T c3_i1196;
  real_T c3_me_y[6];
  int32_T c3_i1197;
  real_T c3_dv124[6];
  int32_T c3_i1198;
  real_T c3_ne_y[6];
  real_T c3_oe_y;
  int32_T c3_i1199;
  int32_T c3_i1200;
  int32_T c3_i1201;
  int32_T c3_i1202;
  int32_T c3_i1203;
  real_T c3_jf_a[36];
  int32_T c3_i1204;
  real_T c3_rf_b[6];
  int32_T c3_i1205;
  real_T c3_kf_a[36];
  int32_T c3_i1206;
  real_T c3_sf_b[6];
  int32_T c3_i1207;
  real_T c3_dv125[6];
  real_T c3_pe_y[6];
  int32_T c3_i1208;
  real_T c3_lf_a[36];
  int32_T c3_i1209;
  real_T c3_tf_b[6];
  int32_T c3_i1210;
  real_T c3_mf_a[36];
  int32_T c3_i1211;
  real_T c3_uf_b[6];
  int32_T c3_i1212;
  real_T c3_dv126[6];
  real_T c3_qe_y[6];
  int32_T c3_i1213;
  real_T c3_b_V4[6];
  real_T c3_dv127[36];
  int32_T c3_i1214;
  int32_T c3_i1215;
  int32_T c3_i1216;
  int32_T c3_i1217;
  real_T c3_nf_a[36];
  int32_T c3_i1218;
  real_T c3_vf_b[36];
  int32_T c3_i1219;
  real_T c3_ag_A[36];
  int32_T c3_i1220;
  real_T c3_ag_B[36];
  int32_T c3_i1221;
  real_T c3_bg_A[36];
  int32_T c3_i1222;
  real_T c3_bg_B[36];
  int32_T c3_i1223;
  real_T c3_cg_A[36];
  int32_T c3_i1224;
  real_T c3_cg_B[36];
  int32_T c3_i1225;
  real_T c3_dv128[36];
  real_T c3_re_y[36];
  int32_T c3_i1226;
  real_T c3_of_a[36];
  int32_T c3_i1227;
  real_T c3_wf_b[6];
  int32_T c3_i1228;
  real_T c3_pf_a[36];
  int32_T c3_i1229;
  real_T c3_xf_b[6];
  int32_T c3_i1230;
  real_T c3_dv129[6];
  real_T c3_se_y[6];
  int32_T c3_i1231;
  int32_T c3_i1232;
  real_T c3_yf_b[6];
  int32_T c3_i1233;
  real_T c3_te_y[6];
  int32_T c3_i1234;
  real_T c3_ue_y[6];
  int32_T c3_i1235;
  real_T c3_ve_y[6];
  int32_T c3_i1236;
  real_T c3_dv130[6];
  int32_T c3_i1237;
  real_T c3_we_y[6];
  real_T c3_xe_y;
  int32_T c3_i1238;
  int32_T c3_i1239;
  int32_T c3_i1240;
  int32_T c3_i1241;
  int32_T c3_i1242;
  real_T c3_qf_a[36];
  int32_T c3_i1243;
  real_T c3_ag_b[6];
  int32_T c3_i1244;
  real_T c3_rf_a[36];
  int32_T c3_i1245;
  real_T c3_bg_b[6];
  int32_T c3_i1246;
  real_T c3_dv131[6];
  real_T c3_ye_y[6];
  int32_T c3_i1247;
  real_T c3_sf_a[36];
  int32_T c3_i1248;
  real_T c3_cg_b[6];
  int32_T c3_i1249;
  real_T c3_tf_a[36];
  int32_T c3_i1250;
  real_T c3_dg_b[6];
  int32_T c3_i1251;
  real_T c3_dv132[6];
  real_T c3_af_y[6];
  int32_T c3_i1252;
  real_T c3_b_V3[6];
  real_T c3_dv133[36];
  int32_T c3_i1253;
  int32_T c3_i1254;
  int32_T c3_i1255;
  int32_T c3_i1256;
  real_T c3_uf_a[36];
  int32_T c3_i1257;
  real_T c3_eg_b[36];
  int32_T c3_i1258;
  real_T c3_dg_A[36];
  int32_T c3_i1259;
  real_T c3_dg_B[36];
  int32_T c3_i1260;
  real_T c3_eg_A[36];
  int32_T c3_i1261;
  real_T c3_eg_B[36];
  int32_T c3_i1262;
  real_T c3_fg_A[36];
  int32_T c3_i1263;
  real_T c3_fg_B[36];
  int32_T c3_i1264;
  real_T c3_dv134[36];
  real_T c3_bf_y[36];
  int32_T c3_i1265;
  real_T c3_vf_a[36];
  int32_T c3_i1266;
  real_T c3_fg_b[6];
  int32_T c3_i1267;
  real_T c3_wf_a[36];
  int32_T c3_i1268;
  real_T c3_gg_b[6];
  int32_T c3_i1269;
  real_T c3_dv135[6];
  real_T c3_cf_y[6];
  int32_T c3_i1270;
  int32_T c3_i1271;
  real_T c3_hg_b[6];
  int32_T c3_i1272;
  real_T c3_df_y[6];
  int32_T c3_i1273;
  real_T c3_ef_y[6];
  int32_T c3_i1274;
  real_T c3_ff_y[6];
  int32_T c3_i1275;
  real_T c3_dv136[6];
  int32_T c3_i1276;
  real_T c3_gf_y[6];
  real_T c3_hf_y;
  int32_T c3_i1277;
  int32_T c3_i1278;
  int32_T c3_i1279;
  int32_T c3_i1280;
  int32_T c3_i1281;
  real_T c3_xf_a[36];
  int32_T c3_i1282;
  real_T c3_ig_b[6];
  int32_T c3_i1283;
  real_T c3_yf_a[36];
  int32_T c3_i1284;
  real_T c3_jg_b[6];
  int32_T c3_i1285;
  real_T c3_dv137[6];
  real_T c3_if_y[6];
  int32_T c3_i1286;
  real_T c3_ag_a[36];
  int32_T c3_i1287;
  real_T c3_kg_b[6];
  int32_T c3_i1288;
  real_T c3_bg_a[36];
  int32_T c3_i1289;
  real_T c3_lg_b[6];
  int32_T c3_i1290;
  real_T c3_dv138[6];
  real_T c3_jf_y[6];
  int32_T c3_i1291;
  real_T c3_b_V2[6];
  real_T c3_dv139[36];
  int32_T c3_i1292;
  int32_T c3_i1293;
  int32_T c3_i1294;
  int32_T c3_i1295;
  real_T c3_cg_a[36];
  int32_T c3_i1296;
  real_T c3_mg_b[36];
  int32_T c3_i1297;
  real_T c3_gg_A[36];
  int32_T c3_i1298;
  real_T c3_gg_B[36];
  int32_T c3_i1299;
  real_T c3_hg_A[36];
  int32_T c3_i1300;
  real_T c3_hg_B[36];
  int32_T c3_i1301;
  real_T c3_ig_A[36];
  int32_T c3_i1302;
  real_T c3_ig_B[36];
  int32_T c3_i1303;
  real_T c3_dv140[36];
  real_T c3_kf_y[36];
  int32_T c3_i1304;
  real_T c3_dg_a[36];
  int32_T c3_i1305;
  real_T c3_ng_b[6];
  int32_T c3_i1306;
  real_T c3_eg_a[36];
  int32_T c3_i1307;
  real_T c3_og_b[6];
  int32_T c3_i1308;
  real_T c3_dv141[6];
  real_T c3_lf_y[6];
  int32_T c3_i1309;
  int32_T c3_i1310;
  real_T c3_pg_b[6];
  int32_T c3_i1311;
  real_T c3_mf_y[6];
  int32_T c3_i1312;
  real_T c3_nf_y[6];
  int32_T c3_i1313;
  real_T c3_of_y[6];
  int32_T c3_i1314;
  real_T c3_dv142[6];
  int32_T c3_i1315;
  real_T c3_pf_y[6];
  real_T c3_qf_y;
  int32_T c3_i1316;
  int32_T c3_i1317;
  int32_T c3_i1318;
  int32_T c3_i1319;
  int32_T c3_i1320;
  real_T c3_fg_a[36];
  int32_T c3_i1321;
  real_T c3_qg_b[6];
  int32_T c3_i1322;
  real_T c3_gg_a[36];
  int32_T c3_i1323;
  real_T c3_rg_b[6];
  int32_T c3_i1324;
  real_T c3_dv143[6];
  real_T c3_rf_y[6];
  int32_T c3_i1325;
  real_T c3_hg_a[36];
  int32_T c3_i1326;
  real_T c3_sg_b[6];
  int32_T c3_i1327;
  real_T c3_ig_a[36];
  int32_T c3_i1328;
  real_T c3_tg_b[6];
  int32_T c3_i1329;
  real_T c3_dv144[6];
  real_T c3_sf_y[6];
  int32_T c3_i1330;
  real_T c3_b_V1[6];
  real_T c3_dv145[36];
  int32_T c3_i1331;
  int32_T c3_i1332;
  int32_T c3_i1333;
  int32_T c3_i1334;
  real_T c3_jg_a[36];
  int32_T c3_i1335;
  real_T c3_ug_b[36];
  int32_T c3_i1336;
  real_T c3_jg_A[36];
  int32_T c3_i1337;
  real_T c3_jg_B[36];
  int32_T c3_i1338;
  real_T c3_kg_A[36];
  int32_T c3_i1339;
  real_T c3_kg_B[36];
  int32_T c3_i1340;
  real_T c3_lg_A[36];
  int32_T c3_i1341;
  real_T c3_lg_B[36];
  int32_T c3_i1342;
  real_T c3_dv146[36];
  real_T c3_tf_y[36];
  int32_T c3_i1343;
  real_T c3_kg_a[36];
  int32_T c3_i1344;
  real_T c3_vg_b[6];
  int32_T c3_i1345;
  real_T c3_lg_a[36];
  int32_T c3_i1346;
  real_T c3_wg_b[6];
  int32_T c3_i1347;
  real_T c3_dv147[6];
  real_T c3_uf_y[6];
  int32_T c3_i1348;
  int32_T c3_i1349;
  real_T c3_xg_b[6];
  int32_T c3_i1350;
  real_T c3_vf_y[6];
  int32_T c3_i1351;
  real_T c3_wf_y[6];
  int32_T c3_i1352;
  real_T c3_xf_y[6];
  int32_T c3_i1353;
  real_T c3_dv148[6];
  int32_T c3_i1354;
  real_T c3_yf_y[6];
  real_T c3_ag_y;
  int32_T c3_i1355;
  int32_T c3_i1356;
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
  sf_debug_symbol_scope_add_eml(&c3_m1, c3_f_sf_marshall, 18U);
  sf_debug_symbol_scope_add_eml(c3_I1, c3_g_sf_marshall, 19U);
  sf_debug_symbol_scope_add_eml(&c3_m2, c3_f_sf_marshall, 20U);
  sf_debug_symbol_scope_add_eml(c3_I2, c3_g_sf_marshall, 21U);
  sf_debug_symbol_scope_add_eml(&c3_m3, c3_f_sf_marshall, 22U);
  sf_debug_symbol_scope_add_eml(c3_I3, c3_g_sf_marshall, 23U);
  sf_debug_symbol_scope_add_eml(&c3_m4, c3_f_sf_marshall, 24U);
  sf_debug_symbol_scope_add_eml(c3_I4, c3_g_sf_marshall, 25U);
  sf_debug_symbol_scope_add_eml(&c3_m5, c3_f_sf_marshall, 26U);
  sf_debug_symbol_scope_add_eml(c3_I5, c3_g_sf_marshall, 27U);
  sf_debug_symbol_scope_add_eml(&c3_m6, c3_f_sf_marshall, 28U);
  sf_debug_symbol_scope_add_eml(c3_I6, c3_g_sf_marshall, 29U);
  sf_debug_symbol_scope_add_eml(c3_g, c3_i_sf_marshall, 30U);
  sf_debug_symbol_scope_add_eml(c3_r1, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r2, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_R, c3_g_sf_marshall, 33U);
  sf_debug_symbol_scope_add_eml(c3_r3, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r4, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r5, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_r6, c3_k_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_M1, c3_j_sf_marshall, 38U);
  sf_debug_symbol_scope_add_eml(c3_M2, c3_j_sf_marshall, 39U);
  sf_debug_symbol_scope_add_eml(c3_M3, c3_j_sf_marshall, 40U);
  sf_debug_symbol_scope_add_eml(c3_M4, c3_j_sf_marshall, 41U);
  sf_debug_symbol_scope_add_eml(c3_M5, c3_j_sf_marshall, 42U);
  sf_debug_symbol_scope_add_eml(c3_M6, c3_j_sf_marshall, 43U);
  sf_debug_symbol_scope_add_eml(c3_V0, c3_b_sf_marshall, 44U);
  sf_debug_symbol_scope_add_eml(c3_dV0, c3_b_sf_marshall, 45U);
  sf_debug_symbol_scope_add_eml(c3_g01, c3_i_sf_marshall, 46U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg01, c3_j_sf_marshall, 47U);
  sf_debug_symbol_scope_add_eml(c3_V1, c3_b_sf_marshall, 48U);
  sf_debug_symbol_scope_add_eml(c3_dV1, c3_b_sf_marshall, 49U);
  sf_debug_symbol_scope_add_eml(c3_g12, c3_i_sf_marshall, 50U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg12, c3_j_sf_marshall, 51U);
  sf_debug_symbol_scope_add_eml(c3_V2, c3_b_sf_marshall, 52U);
  sf_debug_symbol_scope_add_eml(c3_dV2, c3_b_sf_marshall, 53U);
  sf_debug_symbol_scope_add_eml(c3_g23, c3_i_sf_marshall, 54U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg23, c3_j_sf_marshall, 55U);
  sf_debug_symbol_scope_add_eml(c3_V3, c3_b_sf_marshall, 56U);
  sf_debug_symbol_scope_add_eml(c3_dV3, c3_b_sf_marshall, 57U);
  sf_debug_symbol_scope_add_eml(c3_g34, c3_i_sf_marshall, 58U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg34, c3_j_sf_marshall, 59U);
  sf_debug_symbol_scope_add_eml(c3_V4, c3_b_sf_marshall, 60U);
  sf_debug_symbol_scope_add_eml(c3_dV4, c3_b_sf_marshall, 61U);
  sf_debug_symbol_scope_add_eml(c3_g45, c3_i_sf_marshall, 62U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg45, c3_j_sf_marshall, 63U);
  sf_debug_symbol_scope_add_eml(c3_V5, c3_b_sf_marshall, 64U);
  sf_debug_symbol_scope_add_eml(c3_dV5, c3_b_sf_marshall, 65U);
  sf_debug_symbol_scope_add_eml(c3_g56, c3_i_sf_marshall, 66U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg56, c3_j_sf_marshall, 67U);
  sf_debug_symbol_scope_add_eml(c3_V6, c3_b_sf_marshall, 68U);
  sf_debug_symbol_scope_add_eml(c3_dV6, c3_b_sf_marshall, 69U);
  sf_debug_symbol_scope_add_eml(c3_Tau, c3_b_sf_marshall, 70U);
  sf_debug_symbol_scope_add_eml(c3_F7, c3_b_sf_marshall, 71U);
  sf_debug_symbol_scope_add_eml(c3_Adinvg67, c3_j_sf_marshall, 72U);
  sf_debug_symbol_scope_add_eml(c3_F6, c3_b_sf_marshall, 73U);
  sf_debug_symbol_scope_add_eml(c3_F5, c3_b_sf_marshall, 74U);
  sf_debug_symbol_scope_add_eml(c3_F4, c3_b_sf_marshall, 75U);
  sf_debug_symbol_scope_add_eml(c3_F3, c3_b_sf_marshall, 76U);
  sf_debug_symbol_scope_add_eml(c3_F2, c3_b_sf_marshall, 77U);
  sf_debug_symbol_scope_add_eml(c3_F1, c3_b_sf_marshall, 78U);
  sf_debug_symbol_scope_add_eml(c3_b_r1, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r2, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r3, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r4, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r5, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c3_b_r6, c3_h_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 79U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 80U);
  sf_debug_symbol_scope_add_eml(c3_DH, c3_e_sf_marshall, 81U);
  sf_debug_symbol_scope_add_eml(c3_Ma, c3_b_sf_marshall, 82U);
  sf_debug_symbol_scope_add_eml(c3_Cen, c3_d_sf_marshall, 83U);
  sf_debug_symbol_scope_add_eml(c3_Ie, c3_c_sf_marshall, 84U);
  sf_debug_symbol_scope_add_eml(c3_Ft, c3_b_sf_marshall, 85U);
  sf_debug_symbol_scope_add_eml(c3_Pos, c3_b_sf_marshall, 86U);
  sf_debug_symbol_scope_add_eml(c3_Vel, c3_b_sf_marshall, 87U);
  sf_debug_symbol_scope_add_eml(c3_Acc, c3_b_sf_marshall, 88U);
  sf_debug_symbol_scope_add_eml(c3_Torque, c3_b_sf_marshall, 89U);
  sf_debug_symbol_scope_add_eml(c3_JntVel, c3_sf_marshall, 90U);
  sf_debug_symbol_scope_add_eml(c3_JntAcc, c3_sf_marshall, 91U);
  sf_debug_symbol_scope_add_eml(c3_JntF, c3_sf_marshall, 92U);
  CV_SCRIPT_FCN(0, 0);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* @Copyright(c),Googol Shenzhen Tech. Ltd */
  /* @File Name: DynEuler.m */
  /* @Author: Dai Dan */
  /* @Version: 1.0 */
  /* @Date: 05/5/2014 */
  /*  */
  /* @Function: DynEuler */
  /* @Description: Implementing Newton-Euler Recursion Algorithm(Classic Type) to get computed torque */
  /* @Input: */
  /* DH: DH parameters */
  /* Ma: link mass */
  /* Cen: link masss center */
  /* Ie: link inertial */
  /* Ft: generalized force exerted on endeffetor  */
  /* Pos: joint angle */
  /* Vel: joint velocity */
  /* Acc: joint acceleration */
  /* @Output: */
  /* Tau: Torque */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  _SFD_SCRIPT_CALL(0, 24);
  for (c3_i65 = 0; c3_i65 < 36; c3_i65 = c3_i65 + 1) {
    c3_JntVel[c3_i65] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 25);
  for (c3_i66 = 0; c3_i66 < 36; c3_i66 = c3_i66 + 1) {
    c3_JntAcc[c3_i66] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 26);
  for (c3_i67 = 0; c3_i67 < 36; c3_i67 = c3_i67 + 1) {
    c3_JntF[c3_i67] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 27);
  for (c3_i68 = 0; c3_i68 < 6; c3_i68 = c3_i68 + 1) {
    c3_Torque[c3_i68] = 0.0;
  }

  /*  %% Calculate kxi in corresponding joint frame, different from in base frame */
  _SFD_SCRIPT_CALL(0, 30);
  for (c3_i69 = 0; c3_i69 < 3; c3_i69 = c3_i69 + 1) {
    c3_w_o[c3_i69] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 31);
  for (c3_i70 = 0; c3_i70 < 3; c3_i70 = c3_i70 + 1) {
    c3_w_z[c3_i70] = c3_dv9[c3_i70];
  }

  _SFD_SCRIPT_CALL(0, 33);
  for (c3_i71 = 0; c3_i71 < 6; c3_i71 = c3_i71 + 1) {
    c3_kxi1[c3_i71] = c3_dv10[c3_i71];
  }

  _SFD_SCRIPT_CALL(0, 34);
  for (c3_i72 = 0; c3_i72 < 6; c3_i72 = c3_i72 + 1) {
    c3_kxi2[c3_i72] = c3_dv10[c3_i72];
  }

  _SFD_SCRIPT_CALL(0, 35);
  for (c3_i73 = 0; c3_i73 < 6; c3_i73 = c3_i73 + 1) {
    c3_kxi3[c3_i73] = c3_dv10[c3_i73];
  }

  _SFD_SCRIPT_CALL(0, 36);
  for (c3_i74 = 0; c3_i74 < 6; c3_i74 = c3_i74 + 1) {
    c3_kxi4[c3_i74] = c3_dv10[c3_i74];
  }

  _SFD_SCRIPT_CALL(0, 37);
  for (c3_i75 = 0; c3_i75 < 6; c3_i75 = c3_i75 + 1) {
    c3_kxi5[c3_i75] = c3_dv10[c3_i75];
  }

  _SFD_SCRIPT_CALL(0, 38);
  for (c3_i76 = 0; c3_i76 < 6; c3_i76 = c3_i76 + 1) {
    c3_kxi6[c3_i76] = c3_dv10[c3_i76];
  }

  /*  %% Calculate initial configuration matrix g_{i-1,i} */
  /*  0: means base frame; */
  /*  1,2,3,4,5,6: means i-th joint frame, Ci */
  /*  7: means endeffector frame */
  /*  DH=[266     300     0       0       1016     0      174; */
  /*      0       0       -pi/2   0       pi      pi       0; */
  /*      0       150     870     170     0       0        0; */
  /*      0       -pi/2   0       -pi/2   -pi/2    -pi/2   0;]; */
  _SFD_SCRIPT_CALL(0, 49);
  for (c3_i77 = 0; c3_i77 < 3; c3_i77 = c3_i77 + 1) {
    c3_ez[c3_i77] = c3_dv9[c3_i77];
  }

  _SFD_SCRIPT_CALL(0, 50);
  for (c3_i78 = 0; c3_i78 < 3; c3_i78 = c3_i78 + 1) {
    c3_ex[c3_i78] = c3_dv11[c3_i78];
  }

  _SFD_SCRIPT_CALL(0, 51);
  for (c3_i79 = 0; c3_i79 < 3; c3_i79 = c3_i79 + 1) {
    c3_eo[c3_i79] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 53);
  for (c3_i80 = 0; c3_i80 < 6; c3_i80 = c3_i80 + 1) {
    c3_dv12[c3_i80] = c3_dv10[c3_i80];
  }

  c3_expg(chartInstance, c3_dv12, c3_DH[1], c3_a);
  for (c3_i81 = 0; c3_i81 < 6; c3_i81 = c3_i81 + 1) {
    c3_dv14[c3_i81] = c3_dv13[c3_i81];
  }

  c3_expg(chartInstance, c3_dv14, c3_DH[0], c3_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i82 = 0; c3_i82 < 16; c3_i82 = c3_i82 + 1) {
    c3_A[c3_i82] = c3_a[c3_i82];
  }

  for (c3_i83 = 0; c3_i83 < 16; c3_i83 = c3_i83 + 1) {
    c3_B[c3_i83] = c3_b[c3_i83];
  }

  for (c3_i84 = 0; c3_i84 < 16; c3_i84 = c3_i84 + 1) {
    c3_b_A[c3_i84] = c3_A[c3_i84];
  }

  for (c3_i85 = 0; c3_i85 < 16; c3_i85 = c3_i85 + 1) {
    c3_b_B[c3_i85] = c3_B[c3_i85];
  }

  for (c3_i86 = 0; c3_i86 < 16; c3_i86 = c3_i86 + 1) {
    c3_c_A[c3_i86] = c3_b_A[c3_i86];
  }

  for (c3_i87 = 0; c3_i87 < 16; c3_i87 = c3_i87 + 1) {
    c3_c_B[c3_i87] = c3_b_B[c3_i87];
  }

  for (c3_i88 = 0; c3_i88 < 4; c3_i88 = c3_i88 + 1) {
    c3_i89 = 0;
    for (c3_i90 = 0; c3_i90 < 4; c3_i90 = c3_i90 + 1) {
      c3_y[c3_i89 + c3_i88] = 0.0;
      c3_i91 = 0;
      for (c3_i92 = 0; c3_i92 < 4; c3_i92 = c3_i92 + 1) {
        c3_y[c3_i89 + c3_i88] = c3_y[c3_i89 + c3_i88] + c3_c_A[c3_i91 + c3_i88] *
          c3_c_B[c3_i92 + c3_i89];
        c3_i91 = c3_i91 + 4;
      }

      c3_i89 = c3_i89 + 4;
    }
  }

  for (c3_i93 = 0; c3_i93 < 16; c3_i93 = c3_i93 + 1) {
    c3_b_a[c3_i93] = c3_y[c3_i93];
  }

  for (c3_i94 = 0; c3_i94 < 6; c3_i94 = c3_i94 + 1) {
    c3_dv16[c3_i94] = c3_dv15[c3_i94];
  }

  c3_expg(chartInstance, c3_dv16, c3_DH[3], c3_b_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i95 = 0; c3_i95 < 16; c3_i95 = c3_i95 + 1) {
    c3_d_A[c3_i95] = c3_b_a[c3_i95];
  }

  for (c3_i96 = 0; c3_i96 < 16; c3_i96 = c3_i96 + 1) {
    c3_d_B[c3_i96] = c3_b_b[c3_i96];
  }

  for (c3_i97 = 0; c3_i97 < 16; c3_i97 = c3_i97 + 1) {
    c3_e_A[c3_i97] = c3_d_A[c3_i97];
  }

  for (c3_i98 = 0; c3_i98 < 16; c3_i98 = c3_i98 + 1) {
    c3_e_B[c3_i98] = c3_d_B[c3_i98];
  }

  for (c3_i99 = 0; c3_i99 < 16; c3_i99 = c3_i99 + 1) {
    c3_f_A[c3_i99] = c3_e_A[c3_i99];
  }

  for (c3_i100 = 0; c3_i100 < 16; c3_i100 = c3_i100 + 1) {
    c3_f_B[c3_i100] = c3_e_B[c3_i100];
  }

  for (c3_i101 = 0; c3_i101 < 4; c3_i101 = c3_i101 + 1) {
    c3_i102 = 0;
    for (c3_i103 = 0; c3_i103 < 4; c3_i103 = c3_i103 + 1) {
      c3_b_y[c3_i102 + c3_i101] = 0.0;
      c3_i104 = 0;
      for (c3_i105 = 0; c3_i105 < 4; c3_i105 = c3_i105 + 1) {
        c3_b_y[c3_i102 + c3_i101] = c3_b_y[c3_i102 + c3_i101] + c3_f_A[c3_i104 +
          c3_i101] * c3_f_B[c3_i105 + c3_i102];
        c3_i104 = c3_i104 + 4;
      }

      c3_i102 = c3_i102 + 4;
    }
  }

  for (c3_i106 = 0; c3_i106 < 16; c3_i106 = c3_i106 + 1) {
    c3_c_a[c3_i106] = c3_b_y[c3_i106];
  }

  for (c3_i107 = 0; c3_i107 < 6; c3_i107 = c3_i107 + 1) {
    c3_dv18[c3_i107] = c3_dv17[c3_i107];
  }

  c3_expg(chartInstance, c3_dv18, c3_DH[2], c3_c_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i108 = 0; c3_i108 < 16; c3_i108 = c3_i108 + 1) {
    c3_g_A[c3_i108] = c3_c_a[c3_i108];
  }

  for (c3_i109 = 0; c3_i109 < 16; c3_i109 = c3_i109 + 1) {
    c3_g_B[c3_i109] = c3_c_b[c3_i109];
  }

  for (c3_i110 = 0; c3_i110 < 16; c3_i110 = c3_i110 + 1) {
    c3_g01_0[c3_i110] = 0.0;
  }

  for (c3_i111 = 0; c3_i111 < 16; c3_i111 = c3_i111 + 1) {
    c3_h_A[c3_i111] = c3_g_A[c3_i111];
  }

  for (c3_i112 = 0; c3_i112 < 16; c3_i112 = c3_i112 + 1) {
    c3_h_B[c3_i112] = c3_g_B[c3_i112];
  }

  for (c3_i113 = 0; c3_i113 < 16; c3_i113 = c3_i113 + 1) {
    c3_i_A[c3_i113] = c3_h_A[c3_i113];
  }

  for (c3_i114 = 0; c3_i114 < 16; c3_i114 = c3_i114 + 1) {
    c3_i_B[c3_i114] = c3_h_B[c3_i114];
  }

  for (c3_i115 = 0; c3_i115 < 4; c3_i115 = c3_i115 + 1) {
    c3_i116 = 0;
    for (c3_i117 = 0; c3_i117 < 4; c3_i117 = c3_i117 + 1) {
      c3_g01_0[c3_i116 + c3_i115] = 0.0;
      c3_i118 = 0;
      for (c3_i119 = 0; c3_i119 < 4; c3_i119 = c3_i119 + 1) {
        c3_g01_0[c3_i116 + c3_i115] = c3_g01_0[c3_i116 + c3_i115] +
          c3_i_A[c3_i118 + c3_i115] * c3_i_B[c3_i119 + c3_i116];
        c3_i118 = c3_i118 + 4;
      }

      c3_i116 = c3_i116 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 54);
  for (c3_i120 = 0; c3_i120 < 6; c3_i120 = c3_i120 + 1) {
    c3_dv19[c3_i120] = c3_dv10[c3_i120];
  }

  c3_expg(chartInstance, c3_dv19, c3_DH[5], c3_d_a);
  for (c3_i121 = 0; c3_i121 < 6; c3_i121 = c3_i121 + 1) {
    c3_dv20[c3_i121] = c3_dv13[c3_i121];
  }

  c3_expg(chartInstance, c3_dv20, c3_DH[4], c3_d_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i122 = 0; c3_i122 < 16; c3_i122 = c3_i122 + 1) {
    c3_j_A[c3_i122] = c3_d_a[c3_i122];
  }

  for (c3_i123 = 0; c3_i123 < 16; c3_i123 = c3_i123 + 1) {
    c3_j_B[c3_i123] = c3_d_b[c3_i123];
  }

  for (c3_i124 = 0; c3_i124 < 16; c3_i124 = c3_i124 + 1) {
    c3_k_A[c3_i124] = c3_j_A[c3_i124];
  }

  for (c3_i125 = 0; c3_i125 < 16; c3_i125 = c3_i125 + 1) {
    c3_k_B[c3_i125] = c3_j_B[c3_i125];
  }

  for (c3_i126 = 0; c3_i126 < 16; c3_i126 = c3_i126 + 1) {
    c3_l_A[c3_i126] = c3_k_A[c3_i126];
  }

  for (c3_i127 = 0; c3_i127 < 16; c3_i127 = c3_i127 + 1) {
    c3_l_B[c3_i127] = c3_k_B[c3_i127];
  }

  for (c3_i128 = 0; c3_i128 < 4; c3_i128 = c3_i128 + 1) {
    c3_i129 = 0;
    for (c3_i130 = 0; c3_i130 < 4; c3_i130 = c3_i130 + 1) {
      c3_c_y[c3_i129 + c3_i128] = 0.0;
      c3_i131 = 0;
      for (c3_i132 = 0; c3_i132 < 4; c3_i132 = c3_i132 + 1) {
        c3_c_y[c3_i129 + c3_i128] = c3_c_y[c3_i129 + c3_i128] + c3_l_A[c3_i131 +
          c3_i128] * c3_l_B[c3_i132 + c3_i129];
        c3_i131 = c3_i131 + 4;
      }

      c3_i129 = c3_i129 + 4;
    }
  }

  for (c3_i133 = 0; c3_i133 < 16; c3_i133 = c3_i133 + 1) {
    c3_e_a[c3_i133] = c3_c_y[c3_i133];
  }

  for (c3_i134 = 0; c3_i134 < 6; c3_i134 = c3_i134 + 1) {
    c3_dv21[c3_i134] = c3_dv15[c3_i134];
  }

  c3_expg(chartInstance, c3_dv21, c3_DH[7], c3_e_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i135 = 0; c3_i135 < 16; c3_i135 = c3_i135 + 1) {
    c3_m_A[c3_i135] = c3_e_a[c3_i135];
  }

  for (c3_i136 = 0; c3_i136 < 16; c3_i136 = c3_i136 + 1) {
    c3_m_B[c3_i136] = c3_e_b[c3_i136];
  }

  for (c3_i137 = 0; c3_i137 < 16; c3_i137 = c3_i137 + 1) {
    c3_n_A[c3_i137] = c3_m_A[c3_i137];
  }

  for (c3_i138 = 0; c3_i138 < 16; c3_i138 = c3_i138 + 1) {
    c3_n_B[c3_i138] = c3_m_B[c3_i138];
  }

  for (c3_i139 = 0; c3_i139 < 16; c3_i139 = c3_i139 + 1) {
    c3_o_A[c3_i139] = c3_n_A[c3_i139];
  }

  for (c3_i140 = 0; c3_i140 < 16; c3_i140 = c3_i140 + 1) {
    c3_o_B[c3_i140] = c3_n_B[c3_i140];
  }

  for (c3_i141 = 0; c3_i141 < 4; c3_i141 = c3_i141 + 1) {
    c3_i142 = 0;
    for (c3_i143 = 0; c3_i143 < 4; c3_i143 = c3_i143 + 1) {
      c3_d_y[c3_i142 + c3_i141] = 0.0;
      c3_i144 = 0;
      for (c3_i145 = 0; c3_i145 < 4; c3_i145 = c3_i145 + 1) {
        c3_d_y[c3_i142 + c3_i141] = c3_d_y[c3_i142 + c3_i141] + c3_o_A[c3_i144 +
          c3_i141] * c3_o_B[c3_i145 + c3_i142];
        c3_i144 = c3_i144 + 4;
      }

      c3_i142 = c3_i142 + 4;
    }
  }

  for (c3_i146 = 0; c3_i146 < 16; c3_i146 = c3_i146 + 1) {
    c3_f_a[c3_i146] = c3_d_y[c3_i146];
  }

  for (c3_i147 = 0; c3_i147 < 6; c3_i147 = c3_i147 + 1) {
    c3_dv22[c3_i147] = c3_dv17[c3_i147];
  }

  c3_expg(chartInstance, c3_dv22, c3_DH[6], c3_f_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i148 = 0; c3_i148 < 16; c3_i148 = c3_i148 + 1) {
    c3_p_A[c3_i148] = c3_f_a[c3_i148];
  }

  for (c3_i149 = 0; c3_i149 < 16; c3_i149 = c3_i149 + 1) {
    c3_p_B[c3_i149] = c3_f_b[c3_i149];
  }

  for (c3_i150 = 0; c3_i150 < 16; c3_i150 = c3_i150 + 1) {
    c3_g12_0[c3_i150] = 0.0;
  }

  for (c3_i151 = 0; c3_i151 < 16; c3_i151 = c3_i151 + 1) {
    c3_q_A[c3_i151] = c3_p_A[c3_i151];
  }

  for (c3_i152 = 0; c3_i152 < 16; c3_i152 = c3_i152 + 1) {
    c3_q_B[c3_i152] = c3_p_B[c3_i152];
  }

  for (c3_i153 = 0; c3_i153 < 16; c3_i153 = c3_i153 + 1) {
    c3_r_A[c3_i153] = c3_q_A[c3_i153];
  }

  for (c3_i154 = 0; c3_i154 < 16; c3_i154 = c3_i154 + 1) {
    c3_r_B[c3_i154] = c3_q_B[c3_i154];
  }

  for (c3_i155 = 0; c3_i155 < 4; c3_i155 = c3_i155 + 1) {
    c3_i156 = 0;
    for (c3_i157 = 0; c3_i157 < 4; c3_i157 = c3_i157 + 1) {
      c3_g12_0[c3_i156 + c3_i155] = 0.0;
      c3_i158 = 0;
      for (c3_i159 = 0; c3_i159 < 4; c3_i159 = c3_i159 + 1) {
        c3_g12_0[c3_i156 + c3_i155] = c3_g12_0[c3_i156 + c3_i155] +
          c3_r_A[c3_i158 + c3_i155] * c3_r_B[c3_i159 + c3_i156];
        c3_i158 = c3_i158 + 4;
      }

      c3_i156 = c3_i156 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 55);
  for (c3_i160 = 0; c3_i160 < 6; c3_i160 = c3_i160 + 1) {
    c3_dv23[c3_i160] = c3_dv10[c3_i160];
  }

  c3_expg(chartInstance, c3_dv23, c3_DH[9], c3_g_a);
  for (c3_i161 = 0; c3_i161 < 6; c3_i161 = c3_i161 + 1) {
    c3_dv24[c3_i161] = c3_dv13[c3_i161];
  }

  c3_expg(chartInstance, c3_dv24, c3_DH[8], c3_g_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i162 = 0; c3_i162 < 16; c3_i162 = c3_i162 + 1) {
    c3_s_A[c3_i162] = c3_g_a[c3_i162];
  }

  for (c3_i163 = 0; c3_i163 < 16; c3_i163 = c3_i163 + 1) {
    c3_s_B[c3_i163] = c3_g_b[c3_i163];
  }

  for (c3_i164 = 0; c3_i164 < 16; c3_i164 = c3_i164 + 1) {
    c3_t_A[c3_i164] = c3_s_A[c3_i164];
  }

  for (c3_i165 = 0; c3_i165 < 16; c3_i165 = c3_i165 + 1) {
    c3_t_B[c3_i165] = c3_s_B[c3_i165];
  }

  for (c3_i166 = 0; c3_i166 < 16; c3_i166 = c3_i166 + 1) {
    c3_u_A[c3_i166] = c3_t_A[c3_i166];
  }

  for (c3_i167 = 0; c3_i167 < 16; c3_i167 = c3_i167 + 1) {
    c3_u_B[c3_i167] = c3_t_B[c3_i167];
  }

  for (c3_i168 = 0; c3_i168 < 4; c3_i168 = c3_i168 + 1) {
    c3_i169 = 0;
    for (c3_i170 = 0; c3_i170 < 4; c3_i170 = c3_i170 + 1) {
      c3_e_y[c3_i169 + c3_i168] = 0.0;
      c3_i171 = 0;
      for (c3_i172 = 0; c3_i172 < 4; c3_i172 = c3_i172 + 1) {
        c3_e_y[c3_i169 + c3_i168] = c3_e_y[c3_i169 + c3_i168] + c3_u_A[c3_i171 +
          c3_i168] * c3_u_B[c3_i172 + c3_i169];
        c3_i171 = c3_i171 + 4;
      }

      c3_i169 = c3_i169 + 4;
    }
  }

  for (c3_i173 = 0; c3_i173 < 16; c3_i173 = c3_i173 + 1) {
    c3_h_a[c3_i173] = c3_e_y[c3_i173];
  }

  for (c3_i174 = 0; c3_i174 < 6; c3_i174 = c3_i174 + 1) {
    c3_dv25[c3_i174] = c3_dv15[c3_i174];
  }

  c3_expg(chartInstance, c3_dv25, c3_DH[11], c3_h_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i175 = 0; c3_i175 < 16; c3_i175 = c3_i175 + 1) {
    c3_v_A[c3_i175] = c3_h_a[c3_i175];
  }

  for (c3_i176 = 0; c3_i176 < 16; c3_i176 = c3_i176 + 1) {
    c3_v_B[c3_i176] = c3_h_b[c3_i176];
  }

  for (c3_i177 = 0; c3_i177 < 16; c3_i177 = c3_i177 + 1) {
    c3_w_A[c3_i177] = c3_v_A[c3_i177];
  }

  for (c3_i178 = 0; c3_i178 < 16; c3_i178 = c3_i178 + 1) {
    c3_w_B[c3_i178] = c3_v_B[c3_i178];
  }

  for (c3_i179 = 0; c3_i179 < 16; c3_i179 = c3_i179 + 1) {
    c3_x_A[c3_i179] = c3_w_A[c3_i179];
  }

  for (c3_i180 = 0; c3_i180 < 16; c3_i180 = c3_i180 + 1) {
    c3_x_B[c3_i180] = c3_w_B[c3_i180];
  }

  for (c3_i181 = 0; c3_i181 < 4; c3_i181 = c3_i181 + 1) {
    c3_i182 = 0;
    for (c3_i183 = 0; c3_i183 < 4; c3_i183 = c3_i183 + 1) {
      c3_f_y[c3_i182 + c3_i181] = 0.0;
      c3_i184 = 0;
      for (c3_i185 = 0; c3_i185 < 4; c3_i185 = c3_i185 + 1) {
        c3_f_y[c3_i182 + c3_i181] = c3_f_y[c3_i182 + c3_i181] + c3_x_A[c3_i184 +
          c3_i181] * c3_x_B[c3_i185 + c3_i182];
        c3_i184 = c3_i184 + 4;
      }

      c3_i182 = c3_i182 + 4;
    }
  }

  for (c3_i186 = 0; c3_i186 < 16; c3_i186 = c3_i186 + 1) {
    c3_i_a[c3_i186] = c3_f_y[c3_i186];
  }

  for (c3_i187 = 0; c3_i187 < 6; c3_i187 = c3_i187 + 1) {
    c3_dv26[c3_i187] = c3_dv17[c3_i187];
  }

  c3_expg(chartInstance, c3_dv26, c3_DH[10], c3_i_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i188 = 0; c3_i188 < 16; c3_i188 = c3_i188 + 1) {
    c3_y_A[c3_i188] = c3_i_a[c3_i188];
  }

  for (c3_i189 = 0; c3_i189 < 16; c3_i189 = c3_i189 + 1) {
    c3_y_B[c3_i189] = c3_i_b[c3_i189];
  }

  for (c3_i190 = 0; c3_i190 < 16; c3_i190 = c3_i190 + 1) {
    c3_g23_0[c3_i190] = 0.0;
  }

  for (c3_i191 = 0; c3_i191 < 16; c3_i191 = c3_i191 + 1) {
    c3_ab_A[c3_i191] = c3_y_A[c3_i191];
  }

  for (c3_i192 = 0; c3_i192 < 16; c3_i192 = c3_i192 + 1) {
    c3_ab_B[c3_i192] = c3_y_B[c3_i192];
  }

  for (c3_i193 = 0; c3_i193 < 16; c3_i193 = c3_i193 + 1) {
    c3_bb_A[c3_i193] = c3_ab_A[c3_i193];
  }

  for (c3_i194 = 0; c3_i194 < 16; c3_i194 = c3_i194 + 1) {
    c3_bb_B[c3_i194] = c3_ab_B[c3_i194];
  }

  for (c3_i195 = 0; c3_i195 < 4; c3_i195 = c3_i195 + 1) {
    c3_i196 = 0;
    for (c3_i197 = 0; c3_i197 < 4; c3_i197 = c3_i197 + 1) {
      c3_g23_0[c3_i196 + c3_i195] = 0.0;
      c3_i198 = 0;
      for (c3_i199 = 0; c3_i199 < 4; c3_i199 = c3_i199 + 1) {
        c3_g23_0[c3_i196 + c3_i195] = c3_g23_0[c3_i196 + c3_i195] +
          c3_bb_A[c3_i198 + c3_i195] * c3_bb_B[c3_i199 + c3_i196];
        c3_i198 = c3_i198 + 4;
      }

      c3_i196 = c3_i196 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 56);
  for (c3_i200 = 0; c3_i200 < 6; c3_i200 = c3_i200 + 1) {
    c3_dv27[c3_i200] = c3_dv10[c3_i200];
  }

  c3_expg(chartInstance, c3_dv27, c3_DH[13], c3_j_a);
  for (c3_i201 = 0; c3_i201 < 6; c3_i201 = c3_i201 + 1) {
    c3_dv28[c3_i201] = c3_dv13[c3_i201];
  }

  c3_expg(chartInstance, c3_dv28, c3_DH[12], c3_j_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i202 = 0; c3_i202 < 16; c3_i202 = c3_i202 + 1) {
    c3_cb_A[c3_i202] = c3_j_a[c3_i202];
  }

  for (c3_i203 = 0; c3_i203 < 16; c3_i203 = c3_i203 + 1) {
    c3_cb_B[c3_i203] = c3_j_b[c3_i203];
  }

  for (c3_i204 = 0; c3_i204 < 16; c3_i204 = c3_i204 + 1) {
    c3_db_A[c3_i204] = c3_cb_A[c3_i204];
  }

  for (c3_i205 = 0; c3_i205 < 16; c3_i205 = c3_i205 + 1) {
    c3_db_B[c3_i205] = c3_cb_B[c3_i205];
  }

  for (c3_i206 = 0; c3_i206 < 16; c3_i206 = c3_i206 + 1) {
    c3_eb_A[c3_i206] = c3_db_A[c3_i206];
  }

  for (c3_i207 = 0; c3_i207 < 16; c3_i207 = c3_i207 + 1) {
    c3_eb_B[c3_i207] = c3_db_B[c3_i207];
  }

  for (c3_i208 = 0; c3_i208 < 4; c3_i208 = c3_i208 + 1) {
    c3_i209 = 0;
    for (c3_i210 = 0; c3_i210 < 4; c3_i210 = c3_i210 + 1) {
      c3_g_y[c3_i209 + c3_i208] = 0.0;
      c3_i211 = 0;
      for (c3_i212 = 0; c3_i212 < 4; c3_i212 = c3_i212 + 1) {
        c3_g_y[c3_i209 + c3_i208] = c3_g_y[c3_i209 + c3_i208] + c3_eb_A[c3_i211
          + c3_i208] * c3_eb_B[c3_i212 + c3_i209];
        c3_i211 = c3_i211 + 4;
      }

      c3_i209 = c3_i209 + 4;
    }
  }

  for (c3_i213 = 0; c3_i213 < 16; c3_i213 = c3_i213 + 1) {
    c3_k_a[c3_i213] = c3_g_y[c3_i213];
  }

  for (c3_i214 = 0; c3_i214 < 6; c3_i214 = c3_i214 + 1) {
    c3_dv29[c3_i214] = c3_dv15[c3_i214];
  }

  c3_expg(chartInstance, c3_dv29, c3_DH[15], c3_k_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i215 = 0; c3_i215 < 16; c3_i215 = c3_i215 + 1) {
    c3_fb_A[c3_i215] = c3_k_a[c3_i215];
  }

  for (c3_i216 = 0; c3_i216 < 16; c3_i216 = c3_i216 + 1) {
    c3_fb_B[c3_i216] = c3_k_b[c3_i216];
  }

  for (c3_i217 = 0; c3_i217 < 16; c3_i217 = c3_i217 + 1) {
    c3_gb_A[c3_i217] = c3_fb_A[c3_i217];
  }

  for (c3_i218 = 0; c3_i218 < 16; c3_i218 = c3_i218 + 1) {
    c3_gb_B[c3_i218] = c3_fb_B[c3_i218];
  }

  for (c3_i219 = 0; c3_i219 < 16; c3_i219 = c3_i219 + 1) {
    c3_hb_A[c3_i219] = c3_gb_A[c3_i219];
  }

  for (c3_i220 = 0; c3_i220 < 16; c3_i220 = c3_i220 + 1) {
    c3_hb_B[c3_i220] = c3_gb_B[c3_i220];
  }

  for (c3_i221 = 0; c3_i221 < 4; c3_i221 = c3_i221 + 1) {
    c3_i222 = 0;
    for (c3_i223 = 0; c3_i223 < 4; c3_i223 = c3_i223 + 1) {
      c3_h_y[c3_i222 + c3_i221] = 0.0;
      c3_i224 = 0;
      for (c3_i225 = 0; c3_i225 < 4; c3_i225 = c3_i225 + 1) {
        c3_h_y[c3_i222 + c3_i221] = c3_h_y[c3_i222 + c3_i221] + c3_hb_A[c3_i224
          + c3_i221] * c3_hb_B[c3_i225 + c3_i222];
        c3_i224 = c3_i224 + 4;
      }

      c3_i222 = c3_i222 + 4;
    }
  }

  for (c3_i226 = 0; c3_i226 < 16; c3_i226 = c3_i226 + 1) {
    c3_l_a[c3_i226] = c3_h_y[c3_i226];
  }

  for (c3_i227 = 0; c3_i227 < 6; c3_i227 = c3_i227 + 1) {
    c3_dv30[c3_i227] = c3_dv17[c3_i227];
  }

  c3_expg(chartInstance, c3_dv30, c3_DH[14], c3_l_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i228 = 0; c3_i228 < 16; c3_i228 = c3_i228 + 1) {
    c3_ib_A[c3_i228] = c3_l_a[c3_i228];
  }

  for (c3_i229 = 0; c3_i229 < 16; c3_i229 = c3_i229 + 1) {
    c3_ib_B[c3_i229] = c3_l_b[c3_i229];
  }

  for (c3_i230 = 0; c3_i230 < 16; c3_i230 = c3_i230 + 1) {
    c3_g34_0[c3_i230] = 0.0;
  }

  for (c3_i231 = 0; c3_i231 < 16; c3_i231 = c3_i231 + 1) {
    c3_jb_A[c3_i231] = c3_ib_A[c3_i231];
  }

  for (c3_i232 = 0; c3_i232 < 16; c3_i232 = c3_i232 + 1) {
    c3_jb_B[c3_i232] = c3_ib_B[c3_i232];
  }

  for (c3_i233 = 0; c3_i233 < 16; c3_i233 = c3_i233 + 1) {
    c3_kb_A[c3_i233] = c3_jb_A[c3_i233];
  }

  for (c3_i234 = 0; c3_i234 < 16; c3_i234 = c3_i234 + 1) {
    c3_kb_B[c3_i234] = c3_jb_B[c3_i234];
  }

  for (c3_i235 = 0; c3_i235 < 4; c3_i235 = c3_i235 + 1) {
    c3_i236 = 0;
    for (c3_i237 = 0; c3_i237 < 4; c3_i237 = c3_i237 + 1) {
      c3_g34_0[c3_i236 + c3_i235] = 0.0;
      c3_i238 = 0;
      for (c3_i239 = 0; c3_i239 < 4; c3_i239 = c3_i239 + 1) {
        c3_g34_0[c3_i236 + c3_i235] = c3_g34_0[c3_i236 + c3_i235] +
          c3_kb_A[c3_i238 + c3_i235] * c3_kb_B[c3_i239 + c3_i236];
        c3_i238 = c3_i238 + 4;
      }

      c3_i236 = c3_i236 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 57);
  for (c3_i240 = 0; c3_i240 < 6; c3_i240 = c3_i240 + 1) {
    c3_dv31[c3_i240] = c3_dv10[c3_i240];
  }

  c3_expg(chartInstance, c3_dv31, c3_DH[17], c3_m_a);
  for (c3_i241 = 0; c3_i241 < 6; c3_i241 = c3_i241 + 1) {
    c3_dv32[c3_i241] = c3_dv13[c3_i241];
  }

  c3_expg(chartInstance, c3_dv32, c3_DH[16], c3_m_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i242 = 0; c3_i242 < 16; c3_i242 = c3_i242 + 1) {
    c3_lb_A[c3_i242] = c3_m_a[c3_i242];
  }

  for (c3_i243 = 0; c3_i243 < 16; c3_i243 = c3_i243 + 1) {
    c3_lb_B[c3_i243] = c3_m_b[c3_i243];
  }

  for (c3_i244 = 0; c3_i244 < 16; c3_i244 = c3_i244 + 1) {
    c3_mb_A[c3_i244] = c3_lb_A[c3_i244];
  }

  for (c3_i245 = 0; c3_i245 < 16; c3_i245 = c3_i245 + 1) {
    c3_mb_B[c3_i245] = c3_lb_B[c3_i245];
  }

  for (c3_i246 = 0; c3_i246 < 16; c3_i246 = c3_i246 + 1) {
    c3_nb_A[c3_i246] = c3_mb_A[c3_i246];
  }

  for (c3_i247 = 0; c3_i247 < 16; c3_i247 = c3_i247 + 1) {
    c3_nb_B[c3_i247] = c3_mb_B[c3_i247];
  }

  for (c3_i248 = 0; c3_i248 < 4; c3_i248 = c3_i248 + 1) {
    c3_i249 = 0;
    for (c3_i250 = 0; c3_i250 < 4; c3_i250 = c3_i250 + 1) {
      c3_i_y[c3_i249 + c3_i248] = 0.0;
      c3_i251 = 0;
      for (c3_i252 = 0; c3_i252 < 4; c3_i252 = c3_i252 + 1) {
        c3_i_y[c3_i249 + c3_i248] = c3_i_y[c3_i249 + c3_i248] + c3_nb_A[c3_i251
          + c3_i248] * c3_nb_B[c3_i252 + c3_i249];
        c3_i251 = c3_i251 + 4;
      }

      c3_i249 = c3_i249 + 4;
    }
  }

  for (c3_i253 = 0; c3_i253 < 16; c3_i253 = c3_i253 + 1) {
    c3_n_a[c3_i253] = c3_i_y[c3_i253];
  }

  for (c3_i254 = 0; c3_i254 < 6; c3_i254 = c3_i254 + 1) {
    c3_dv33[c3_i254] = c3_dv15[c3_i254];
  }

  c3_expg(chartInstance, c3_dv33, c3_DH[19], c3_n_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i255 = 0; c3_i255 < 16; c3_i255 = c3_i255 + 1) {
    c3_ob_A[c3_i255] = c3_n_a[c3_i255];
  }

  for (c3_i256 = 0; c3_i256 < 16; c3_i256 = c3_i256 + 1) {
    c3_ob_B[c3_i256] = c3_n_b[c3_i256];
  }

  for (c3_i257 = 0; c3_i257 < 16; c3_i257 = c3_i257 + 1) {
    c3_pb_A[c3_i257] = c3_ob_A[c3_i257];
  }

  for (c3_i258 = 0; c3_i258 < 16; c3_i258 = c3_i258 + 1) {
    c3_pb_B[c3_i258] = c3_ob_B[c3_i258];
  }

  for (c3_i259 = 0; c3_i259 < 16; c3_i259 = c3_i259 + 1) {
    c3_qb_A[c3_i259] = c3_pb_A[c3_i259];
  }

  for (c3_i260 = 0; c3_i260 < 16; c3_i260 = c3_i260 + 1) {
    c3_qb_B[c3_i260] = c3_pb_B[c3_i260];
  }

  for (c3_i261 = 0; c3_i261 < 4; c3_i261 = c3_i261 + 1) {
    c3_i262 = 0;
    for (c3_i263 = 0; c3_i263 < 4; c3_i263 = c3_i263 + 1) {
      c3_j_y[c3_i262 + c3_i261] = 0.0;
      c3_i264 = 0;
      for (c3_i265 = 0; c3_i265 < 4; c3_i265 = c3_i265 + 1) {
        c3_j_y[c3_i262 + c3_i261] = c3_j_y[c3_i262 + c3_i261] + c3_qb_A[c3_i264
          + c3_i261] * c3_qb_B[c3_i265 + c3_i262];
        c3_i264 = c3_i264 + 4;
      }

      c3_i262 = c3_i262 + 4;
    }
  }

  for (c3_i266 = 0; c3_i266 < 16; c3_i266 = c3_i266 + 1) {
    c3_o_a[c3_i266] = c3_j_y[c3_i266];
  }

  for (c3_i267 = 0; c3_i267 < 6; c3_i267 = c3_i267 + 1) {
    c3_dv34[c3_i267] = c3_dv17[c3_i267];
  }

  c3_expg(chartInstance, c3_dv34, c3_DH[18], c3_o_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i268 = 0; c3_i268 < 16; c3_i268 = c3_i268 + 1) {
    c3_rb_A[c3_i268] = c3_o_a[c3_i268];
  }

  for (c3_i269 = 0; c3_i269 < 16; c3_i269 = c3_i269 + 1) {
    c3_rb_B[c3_i269] = c3_o_b[c3_i269];
  }

  for (c3_i270 = 0; c3_i270 < 16; c3_i270 = c3_i270 + 1) {
    c3_g45_0[c3_i270] = 0.0;
  }

  for (c3_i271 = 0; c3_i271 < 16; c3_i271 = c3_i271 + 1) {
    c3_sb_A[c3_i271] = c3_rb_A[c3_i271];
  }

  for (c3_i272 = 0; c3_i272 < 16; c3_i272 = c3_i272 + 1) {
    c3_sb_B[c3_i272] = c3_rb_B[c3_i272];
  }

  for (c3_i273 = 0; c3_i273 < 16; c3_i273 = c3_i273 + 1) {
    c3_tb_A[c3_i273] = c3_sb_A[c3_i273];
  }

  for (c3_i274 = 0; c3_i274 < 16; c3_i274 = c3_i274 + 1) {
    c3_tb_B[c3_i274] = c3_sb_B[c3_i274];
  }

  for (c3_i275 = 0; c3_i275 < 4; c3_i275 = c3_i275 + 1) {
    c3_i276 = 0;
    for (c3_i277 = 0; c3_i277 < 4; c3_i277 = c3_i277 + 1) {
      c3_g45_0[c3_i276 + c3_i275] = 0.0;
      c3_i278 = 0;
      for (c3_i279 = 0; c3_i279 < 4; c3_i279 = c3_i279 + 1) {
        c3_g45_0[c3_i276 + c3_i275] = c3_g45_0[c3_i276 + c3_i275] +
          c3_tb_A[c3_i278 + c3_i275] * c3_tb_B[c3_i279 + c3_i276];
        c3_i278 = c3_i278 + 4;
      }

      c3_i276 = c3_i276 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 58);
  for (c3_i280 = 0; c3_i280 < 6; c3_i280 = c3_i280 + 1) {
    c3_dv35[c3_i280] = c3_dv10[c3_i280];
  }

  c3_expg(chartInstance, c3_dv35, c3_DH[21], c3_p_a);
  for (c3_i281 = 0; c3_i281 < 6; c3_i281 = c3_i281 + 1) {
    c3_dv36[c3_i281] = c3_dv13[c3_i281];
  }

  c3_expg(chartInstance, c3_dv36, c3_DH[20], c3_p_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i282 = 0; c3_i282 < 16; c3_i282 = c3_i282 + 1) {
    c3_ub_A[c3_i282] = c3_p_a[c3_i282];
  }

  for (c3_i283 = 0; c3_i283 < 16; c3_i283 = c3_i283 + 1) {
    c3_ub_B[c3_i283] = c3_p_b[c3_i283];
  }

  for (c3_i284 = 0; c3_i284 < 16; c3_i284 = c3_i284 + 1) {
    c3_vb_A[c3_i284] = c3_ub_A[c3_i284];
  }

  for (c3_i285 = 0; c3_i285 < 16; c3_i285 = c3_i285 + 1) {
    c3_vb_B[c3_i285] = c3_ub_B[c3_i285];
  }

  for (c3_i286 = 0; c3_i286 < 16; c3_i286 = c3_i286 + 1) {
    c3_wb_A[c3_i286] = c3_vb_A[c3_i286];
  }

  for (c3_i287 = 0; c3_i287 < 16; c3_i287 = c3_i287 + 1) {
    c3_wb_B[c3_i287] = c3_vb_B[c3_i287];
  }

  for (c3_i288 = 0; c3_i288 < 4; c3_i288 = c3_i288 + 1) {
    c3_i289 = 0;
    for (c3_i290 = 0; c3_i290 < 4; c3_i290 = c3_i290 + 1) {
      c3_k_y[c3_i289 + c3_i288] = 0.0;
      c3_i291 = 0;
      for (c3_i292 = 0; c3_i292 < 4; c3_i292 = c3_i292 + 1) {
        c3_k_y[c3_i289 + c3_i288] = c3_k_y[c3_i289 + c3_i288] + c3_wb_A[c3_i291
          + c3_i288] * c3_wb_B[c3_i292 + c3_i289];
        c3_i291 = c3_i291 + 4;
      }

      c3_i289 = c3_i289 + 4;
    }
  }

  for (c3_i293 = 0; c3_i293 < 16; c3_i293 = c3_i293 + 1) {
    c3_q_a[c3_i293] = c3_k_y[c3_i293];
  }

  for (c3_i294 = 0; c3_i294 < 6; c3_i294 = c3_i294 + 1) {
    c3_dv37[c3_i294] = c3_dv15[c3_i294];
  }

  c3_expg(chartInstance, c3_dv37, c3_DH[23], c3_q_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i295 = 0; c3_i295 < 16; c3_i295 = c3_i295 + 1) {
    c3_xb_A[c3_i295] = c3_q_a[c3_i295];
  }

  for (c3_i296 = 0; c3_i296 < 16; c3_i296 = c3_i296 + 1) {
    c3_xb_B[c3_i296] = c3_q_b[c3_i296];
  }

  for (c3_i297 = 0; c3_i297 < 16; c3_i297 = c3_i297 + 1) {
    c3_yb_A[c3_i297] = c3_xb_A[c3_i297];
  }

  for (c3_i298 = 0; c3_i298 < 16; c3_i298 = c3_i298 + 1) {
    c3_yb_B[c3_i298] = c3_xb_B[c3_i298];
  }

  for (c3_i299 = 0; c3_i299 < 16; c3_i299 = c3_i299 + 1) {
    c3_ac_A[c3_i299] = c3_yb_A[c3_i299];
  }

  for (c3_i300 = 0; c3_i300 < 16; c3_i300 = c3_i300 + 1) {
    c3_ac_B[c3_i300] = c3_yb_B[c3_i300];
  }

  for (c3_i301 = 0; c3_i301 < 4; c3_i301 = c3_i301 + 1) {
    c3_i302 = 0;
    for (c3_i303 = 0; c3_i303 < 4; c3_i303 = c3_i303 + 1) {
      c3_l_y[c3_i302 + c3_i301] = 0.0;
      c3_i304 = 0;
      for (c3_i305 = 0; c3_i305 < 4; c3_i305 = c3_i305 + 1) {
        c3_l_y[c3_i302 + c3_i301] = c3_l_y[c3_i302 + c3_i301] + c3_ac_A[c3_i304
          + c3_i301] * c3_ac_B[c3_i305 + c3_i302];
        c3_i304 = c3_i304 + 4;
      }

      c3_i302 = c3_i302 + 4;
    }
  }

  for (c3_i306 = 0; c3_i306 < 16; c3_i306 = c3_i306 + 1) {
    c3_r_a[c3_i306] = c3_l_y[c3_i306];
  }

  for (c3_i307 = 0; c3_i307 < 6; c3_i307 = c3_i307 + 1) {
    c3_dv38[c3_i307] = c3_dv17[c3_i307];
  }

  c3_expg(chartInstance, c3_dv38, c3_DH[22], c3_r_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i308 = 0; c3_i308 < 16; c3_i308 = c3_i308 + 1) {
    c3_bc_A[c3_i308] = c3_r_a[c3_i308];
  }

  for (c3_i309 = 0; c3_i309 < 16; c3_i309 = c3_i309 + 1) {
    c3_bc_B[c3_i309] = c3_r_b[c3_i309];
  }

  for (c3_i310 = 0; c3_i310 < 16; c3_i310 = c3_i310 + 1) {
    c3_g56_0[c3_i310] = 0.0;
  }

  for (c3_i311 = 0; c3_i311 < 16; c3_i311 = c3_i311 + 1) {
    c3_cc_A[c3_i311] = c3_bc_A[c3_i311];
  }

  for (c3_i312 = 0; c3_i312 < 16; c3_i312 = c3_i312 + 1) {
    c3_cc_B[c3_i312] = c3_bc_B[c3_i312];
  }

  for (c3_i313 = 0; c3_i313 < 16; c3_i313 = c3_i313 + 1) {
    c3_dc_A[c3_i313] = c3_cc_A[c3_i313];
  }

  for (c3_i314 = 0; c3_i314 < 16; c3_i314 = c3_i314 + 1) {
    c3_dc_B[c3_i314] = c3_cc_B[c3_i314];
  }

  for (c3_i315 = 0; c3_i315 < 4; c3_i315 = c3_i315 + 1) {
    c3_i316 = 0;
    for (c3_i317 = 0; c3_i317 < 4; c3_i317 = c3_i317 + 1) {
      c3_g56_0[c3_i316 + c3_i315] = 0.0;
      c3_i318 = 0;
      for (c3_i319 = 0; c3_i319 < 4; c3_i319 = c3_i319 + 1) {
        c3_g56_0[c3_i316 + c3_i315] = c3_g56_0[c3_i316 + c3_i315] +
          c3_dc_A[c3_i318 + c3_i315] * c3_dc_B[c3_i319 + c3_i316];
        c3_i318 = c3_i318 + 4;
      }

      c3_i316 = c3_i316 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 59);
  for (c3_i320 = 0; c3_i320 < 6; c3_i320 = c3_i320 + 1) {
    c3_dv39[c3_i320] = c3_dv10[c3_i320];
  }

  c3_expg(chartInstance, c3_dv39, c3_DH[25], c3_s_a);
  for (c3_i321 = 0; c3_i321 < 6; c3_i321 = c3_i321 + 1) {
    c3_dv40[c3_i321] = c3_dv13[c3_i321];
  }

  c3_expg(chartInstance, c3_dv40, c3_DH[24], c3_s_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i322 = 0; c3_i322 < 16; c3_i322 = c3_i322 + 1) {
    c3_ec_A[c3_i322] = c3_s_a[c3_i322];
  }

  for (c3_i323 = 0; c3_i323 < 16; c3_i323 = c3_i323 + 1) {
    c3_ec_B[c3_i323] = c3_s_b[c3_i323];
  }

  for (c3_i324 = 0; c3_i324 < 16; c3_i324 = c3_i324 + 1) {
    c3_fc_A[c3_i324] = c3_ec_A[c3_i324];
  }

  for (c3_i325 = 0; c3_i325 < 16; c3_i325 = c3_i325 + 1) {
    c3_fc_B[c3_i325] = c3_ec_B[c3_i325];
  }

  for (c3_i326 = 0; c3_i326 < 16; c3_i326 = c3_i326 + 1) {
    c3_gc_A[c3_i326] = c3_fc_A[c3_i326];
  }

  for (c3_i327 = 0; c3_i327 < 16; c3_i327 = c3_i327 + 1) {
    c3_gc_B[c3_i327] = c3_fc_B[c3_i327];
  }

  for (c3_i328 = 0; c3_i328 < 4; c3_i328 = c3_i328 + 1) {
    c3_i329 = 0;
    for (c3_i330 = 0; c3_i330 < 4; c3_i330 = c3_i330 + 1) {
      c3_m_y[c3_i329 + c3_i328] = 0.0;
      c3_i331 = 0;
      for (c3_i332 = 0; c3_i332 < 4; c3_i332 = c3_i332 + 1) {
        c3_m_y[c3_i329 + c3_i328] = c3_m_y[c3_i329 + c3_i328] + c3_gc_A[c3_i331
          + c3_i328] * c3_gc_B[c3_i332 + c3_i329];
        c3_i331 = c3_i331 + 4;
      }

      c3_i329 = c3_i329 + 4;
    }
  }

  for (c3_i333 = 0; c3_i333 < 16; c3_i333 = c3_i333 + 1) {
    c3_t_a[c3_i333] = c3_m_y[c3_i333];
  }

  for (c3_i334 = 0; c3_i334 < 6; c3_i334 = c3_i334 + 1) {
    c3_dv41[c3_i334] = c3_dv15[c3_i334];
  }

  c3_expg(chartInstance, c3_dv41, c3_DH[27], c3_t_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i335 = 0; c3_i335 < 16; c3_i335 = c3_i335 + 1) {
    c3_hc_A[c3_i335] = c3_t_a[c3_i335];
  }

  for (c3_i336 = 0; c3_i336 < 16; c3_i336 = c3_i336 + 1) {
    c3_hc_B[c3_i336] = c3_t_b[c3_i336];
  }

  for (c3_i337 = 0; c3_i337 < 16; c3_i337 = c3_i337 + 1) {
    c3_ic_A[c3_i337] = c3_hc_A[c3_i337];
  }

  for (c3_i338 = 0; c3_i338 < 16; c3_i338 = c3_i338 + 1) {
    c3_ic_B[c3_i338] = c3_hc_B[c3_i338];
  }

  for (c3_i339 = 0; c3_i339 < 16; c3_i339 = c3_i339 + 1) {
    c3_jc_A[c3_i339] = c3_ic_A[c3_i339];
  }

  for (c3_i340 = 0; c3_i340 < 16; c3_i340 = c3_i340 + 1) {
    c3_jc_B[c3_i340] = c3_ic_B[c3_i340];
  }

  for (c3_i341 = 0; c3_i341 < 4; c3_i341 = c3_i341 + 1) {
    c3_i342 = 0;
    for (c3_i343 = 0; c3_i343 < 4; c3_i343 = c3_i343 + 1) {
      c3_n_y[c3_i342 + c3_i341] = 0.0;
      c3_i344 = 0;
      for (c3_i345 = 0; c3_i345 < 4; c3_i345 = c3_i345 + 1) {
        c3_n_y[c3_i342 + c3_i341] = c3_n_y[c3_i342 + c3_i341] + c3_jc_A[c3_i344
          + c3_i341] * c3_jc_B[c3_i345 + c3_i342];
        c3_i344 = c3_i344 + 4;
      }

      c3_i342 = c3_i342 + 4;
    }
  }

  for (c3_i346 = 0; c3_i346 < 16; c3_i346 = c3_i346 + 1) {
    c3_u_a[c3_i346] = c3_n_y[c3_i346];
  }

  for (c3_i347 = 0; c3_i347 < 6; c3_i347 = c3_i347 + 1) {
    c3_dv42[c3_i347] = c3_dv17[c3_i347];
  }

  c3_expg(chartInstance, c3_dv42, c3_DH[26], c3_u_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i348 = 0; c3_i348 < 16; c3_i348 = c3_i348 + 1) {
    c3_kc_A[c3_i348] = c3_u_a[c3_i348];
  }

  for (c3_i349 = 0; c3_i349 < 16; c3_i349 = c3_i349 + 1) {
    c3_kc_B[c3_i349] = c3_u_b[c3_i349];
  }

  for (c3_i350 = 0; c3_i350 < 16; c3_i350 = c3_i350 + 1) {
    c3_g67_0[c3_i350] = 0.0;
  }

  for (c3_i351 = 0; c3_i351 < 16; c3_i351 = c3_i351 + 1) {
    c3_lc_A[c3_i351] = c3_kc_A[c3_i351];
  }

  for (c3_i352 = 0; c3_i352 < 16; c3_i352 = c3_i352 + 1) {
    c3_lc_B[c3_i352] = c3_kc_B[c3_i352];
  }

  for (c3_i353 = 0; c3_i353 < 16; c3_i353 = c3_i353 + 1) {
    c3_mc_A[c3_i353] = c3_lc_A[c3_i353];
  }

  for (c3_i354 = 0; c3_i354 < 16; c3_i354 = c3_i354 + 1) {
    c3_mc_B[c3_i354] = c3_lc_B[c3_i354];
  }

  for (c3_i355 = 0; c3_i355 < 4; c3_i355 = c3_i355 + 1) {
    c3_i356 = 0;
    for (c3_i357 = 0; c3_i357 < 4; c3_i357 = c3_i357 + 1) {
      c3_g67_0[c3_i356 + c3_i355] = 0.0;
      c3_i358 = 0;
      for (c3_i359 = 0; c3_i359 < 4; c3_i359 = c3_i359 + 1) {
        c3_g67_0[c3_i356 + c3_i355] = c3_g67_0[c3_i356 + c3_i355] +
          c3_mc_A[c3_i358 + c3_i355] * c3_mc_B[c3_i359 + c3_i356];
        c3_i358 = c3_i358 + 4;
      }

      c3_i356 = c3_i356 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 61);
  c3_m1 = c3_Ma[0];
  _SFD_SCRIPT_CALL(0, 62);
  for (c3_i360 = 0; c3_i360 < 9; c3_i360 = c3_i360 + 1) {
    c3_x[c3_i360] = c3_Ie[c3_i360];
  }

  for (c3_k = 1; c3_k < 10; c3_k = c3_k + 1) {
    c3_b_k = c3_k;
    c3_I1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_b_k), 1, 9, 1, 0) - 1] = c3_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_b_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 63);
  c3_m2 = c3_Ma[1];
  _SFD_SCRIPT_CALL(0, 64);
  for (c3_i361 = 0; c3_i361 < 9; c3_i361 = c3_i361 + 1) {
    c3_b_x[c3_i361] = c3_Ie[c3_i361 + 9];
  }

  for (c3_c_k = 1; c3_c_k < 10; c3_c_k = c3_c_k + 1) {
    c3_d_k = c3_c_k;
    c3_I2[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_d_k), 1, 9, 1, 0) - 1] = c3_b_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_d_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 65);
  c3_m3 = c3_Ma[2];
  _SFD_SCRIPT_CALL(0, 66);
  for (c3_i362 = 0; c3_i362 < 9; c3_i362 = c3_i362 + 1) {
    c3_c_x[c3_i362] = c3_Ie[c3_i362 + 18];
  }

  for (c3_e_k = 1; c3_e_k < 10; c3_e_k = c3_e_k + 1) {
    c3_f_k = c3_e_k;
    c3_I3[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_f_k), 1, 9, 1, 0) - 1] = c3_c_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_f_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 67);
  c3_m4 = c3_Ma[3];
  _SFD_SCRIPT_CALL(0, 68);
  for (c3_i363 = 0; c3_i363 < 9; c3_i363 = c3_i363 + 1) {
    c3_d_x[c3_i363] = c3_Ie[c3_i363 + 27];
  }

  for (c3_g_k = 1; c3_g_k < 10; c3_g_k = c3_g_k + 1) {
    c3_h_k = c3_g_k;
    c3_I4[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_h_k), 1, 9, 1, 0) - 1] = c3_d_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_h_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 69);
  c3_m5 = c3_Ma[4];
  _SFD_SCRIPT_CALL(0, 70);
  for (c3_i364 = 0; c3_i364 < 9; c3_i364 = c3_i364 + 1) {
    c3_e_x[c3_i364] = c3_Ie[c3_i364 + 36];
  }

  for (c3_i_k = 1; c3_i_k < 10; c3_i_k = c3_i_k + 1) {
    c3_j_k = c3_i_k;
    c3_I5[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_j_k), 1, 9, 1, 0) - 1] = c3_e_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_j_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0, 71);
  c3_m6 = c3_Ma[5];
  _SFD_SCRIPT_CALL(0, 72);
  for (c3_i365 = 0; c3_i365 < 9; c3_i365 = c3_i365 + 1) {
    c3_f_x[c3_i365] = c3_Ie[c3_i365 + 45];
  }

  for (c3_k_k = 1; c3_k_k < 10; c3_k_k = c3_k_k + 1) {
    c3_l_k = c3_k_k;
    c3_I6[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c3_l_k), 1, 9, 1, 0) - 1] = c3_f_x[
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_l_k), 1, 9, 1, 0) - 1];
  }

  /*  %% calculate ri: ith link mass center offset relative to ith joint frame,i=1,2,3,4,5,6 */
  _SFD_SCRIPT_CALL(0, 75);
  for (c3_i366 = 0; c3_i366 < 16; c3_i366 = c3_i366 + 1) {
    c3_g[c3_i366] = c3_g01_0[c3_i366];
  }

  _SFD_SCRIPT_CALL(0, 76);
  for (c3_i367 = 0; c3_i367 < 16; c3_i367 = c3_i367 + 1) {
    c3_b_g[c3_i367] = c3_g[c3_i367];
  }

  for (c3_i368 = 0; c3_i368 < 3; c3_i368 = c3_i368 + 1) {
    c3_b_Cen[c3_i368] = c3_Cen[c3_i368];
  }

  c3_b_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_b_g, c3_b_Cen, c3_dv43);
  for (c3_i369 = 0; c3_i369 < 4; c3_i369 = c3_i369 + 1) {
    c3_r1[c3_i369] = c3_dv43[c3_i369];
  }

  sf_debug_symbol_switch(31U, 31U);
  _SFD_SCRIPT_CALL(0, 77);
  for (c3_i370 = 0; c3_i370 < 3; c3_i370 = c3_i370 + 1) {
    c3_b_r1[c3_i370] = c3_r1[c3_i370];
  }

  sf_debug_symbol_switch(31U, 79U);
  _SFD_SCRIPT_CALL(0, 78);
  for (c3_i371 = 0; c3_i371 < 16; c3_i371 = c3_i371 + 1) {
    c3_v_a[c3_i371] = c3_g[c3_i371];
  }

  for (c3_i372 = 0; c3_i372 < 16; c3_i372 = c3_i372 + 1) {
    c3_v_b[c3_i372] = c3_g12_0[c3_i372];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i373 = 0; c3_i373 < 16; c3_i373 = c3_i373 + 1) {
    c3_nc_A[c3_i373] = c3_v_a[c3_i373];
  }

  for (c3_i374 = 0; c3_i374 < 16; c3_i374 = c3_i374 + 1) {
    c3_nc_B[c3_i374] = c3_v_b[c3_i374];
  }

  for (c3_i375 = 0; c3_i375 < 16; c3_i375 = c3_i375 + 1) {
    c3_g[c3_i375] = 0.0;
  }

  for (c3_i376 = 0; c3_i376 < 16; c3_i376 = c3_i376 + 1) {
    c3_oc_A[c3_i376] = c3_nc_A[c3_i376];
  }

  for (c3_i377 = 0; c3_i377 < 16; c3_i377 = c3_i377 + 1) {
    c3_oc_B[c3_i377] = c3_nc_B[c3_i377];
  }

  for (c3_i378 = 0; c3_i378 < 16; c3_i378 = c3_i378 + 1) {
    c3_pc_A[c3_i378] = c3_oc_A[c3_i378];
  }

  for (c3_i379 = 0; c3_i379 < 16; c3_i379 = c3_i379 + 1) {
    c3_pc_B[c3_i379] = c3_oc_B[c3_i379];
  }

  for (c3_i380 = 0; c3_i380 < 4; c3_i380 = c3_i380 + 1) {
    c3_i381 = 0;
    for (c3_i382 = 0; c3_i382 < 4; c3_i382 = c3_i382 + 1) {
      c3_g[c3_i381 + c3_i380] = 0.0;
      c3_i383 = 0;
      for (c3_i384 = 0; c3_i384 < 4; c3_i384 = c3_i384 + 1) {
        c3_g[c3_i381 + c3_i380] = c3_g[c3_i381 + c3_i380] + c3_pc_A[c3_i383 +
          c3_i380] * c3_pc_B[c3_i384 + c3_i381];
        c3_i383 = c3_i383 + 4;
      }

      c3_i381 = c3_i381 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 79);
  for (c3_i385 = 0; c3_i385 < 16; c3_i385 = c3_i385 + 1) {
    c3_c_g[c3_i385] = c3_g[c3_i385];
  }

  for (c3_i386 = 0; c3_i386 < 3; c3_i386 = c3_i386 + 1) {
    c3_c_Cen[c3_i386] = c3_Cen[c3_i386 + 3];
  }

  c3_c_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_c_g, c3_c_Cen, c3_dv44);
  for (c3_i387 = 0; c3_i387 < 4; c3_i387 = c3_i387 + 1) {
    c3_r2[c3_i387] = c3_dv44[c3_i387];
  }

  sf_debug_symbol_switch(32U, 32U);
  _SFD_SCRIPT_CALL(0, 80);
  for (c3_i388 = 0; c3_i388 < 3; c3_i388 = c3_i388 + 1) {
    c3_b_r2[c3_i388] = c3_r2[c3_i388];
  }

  sf_debug_symbol_switch(32U, 80U);
  _SFD_SCRIPT_CALL(0, 81);
  c3_i389 = 0;
  c3_i390 = 0;
  for (c3_i391 = 0; c3_i391 < 3; c3_i391 = c3_i391 + 1) {
    for (c3_i392 = 0; c3_i392 < 3; c3_i392 = c3_i392 + 1) {
      c3_R[c3_i392 + c3_i389] = c3_g[c3_i392 + c3_i390];
    }

    c3_i389 = c3_i389 + 3;
    c3_i390 = c3_i390 + 4;
  }

  _SFD_SCRIPT_CALL(0, 82);
  c3_i393 = 0;
  for (c3_i394 = 0; c3_i394 < 3; c3_i394 = c3_i394 + 1) {
    c3_i395 = 0;
    for (c3_i396 = 0; c3_i396 < 3; c3_i396 = c3_i396 + 1) {
      c3_w_a[c3_i396 + c3_i393] = c3_R[c3_i395 + c3_i394];
      c3_i395 = c3_i395 + 3;
    }

    c3_i393 = c3_i393 + 3;
  }

  for (c3_i397 = 0; c3_i397 < 9; c3_i397 = c3_i397 + 1) {
    c3_w_b[c3_i397] = c3_I2[c3_i397];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i398 = 0; c3_i398 < 9; c3_i398 = c3_i398 + 1) {
    c3_qc_A[c3_i398] = c3_w_a[c3_i398];
  }

  for (c3_i399 = 0; c3_i399 < 9; c3_i399 = c3_i399 + 1) {
    c3_qc_B[c3_i399] = c3_w_b[c3_i399];
  }

  for (c3_i400 = 0; c3_i400 < 9; c3_i400 = c3_i400 + 1) {
    c3_rc_A[c3_i400] = c3_qc_A[c3_i400];
  }

  for (c3_i401 = 0; c3_i401 < 9; c3_i401 = c3_i401 + 1) {
    c3_rc_B[c3_i401] = c3_qc_B[c3_i401];
  }

  for (c3_i402 = 0; c3_i402 < 9; c3_i402 = c3_i402 + 1) {
    c3_sc_A[c3_i402] = c3_rc_A[c3_i402];
  }

  for (c3_i403 = 0; c3_i403 < 9; c3_i403 = c3_i403 + 1) {
    c3_sc_B[c3_i403] = c3_rc_B[c3_i403];
  }

  for (c3_i404 = 0; c3_i404 < 3; c3_i404 = c3_i404 + 1) {
    c3_i405 = 0;
    for (c3_i406 = 0; c3_i406 < 3; c3_i406 = c3_i406 + 1) {
      c3_o_y[c3_i405 + c3_i404] = 0.0;
      c3_i407 = 0;
      for (c3_i408 = 0; c3_i408 < 3; c3_i408 = c3_i408 + 1) {
        c3_o_y[c3_i405 + c3_i404] = c3_o_y[c3_i405 + c3_i404] + c3_sc_A[c3_i407
          + c3_i404] * c3_sc_B[c3_i408 + c3_i405];
        c3_i407 = c3_i407 + 3;
      }

      c3_i405 = c3_i405 + 3;
    }
  }

  for (c3_i409 = 0; c3_i409 < 9; c3_i409 = c3_i409 + 1) {
    c3_x_a[c3_i409] = c3_o_y[c3_i409];
  }

  for (c3_i410 = 0; c3_i410 < 9; c3_i410 = c3_i410 + 1) {
    c3_x_b[c3_i410] = c3_R[c3_i410];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i411 = 0; c3_i411 < 9; c3_i411 = c3_i411 + 1) {
    c3_tc_A[c3_i411] = c3_x_a[c3_i411];
  }

  for (c3_i412 = 0; c3_i412 < 9; c3_i412 = c3_i412 + 1) {
    c3_tc_B[c3_i412] = c3_x_b[c3_i412];
  }

  for (c3_i413 = 0; c3_i413 < 9; c3_i413 = c3_i413 + 1) {
    c3_I2[c3_i413] = 0.0;
  }

  for (c3_i414 = 0; c3_i414 < 9; c3_i414 = c3_i414 + 1) {
    c3_uc_A[c3_i414] = c3_tc_A[c3_i414];
  }

  for (c3_i415 = 0; c3_i415 < 9; c3_i415 = c3_i415 + 1) {
    c3_uc_B[c3_i415] = c3_tc_B[c3_i415];
  }

  for (c3_i416 = 0; c3_i416 < 9; c3_i416 = c3_i416 + 1) {
    c3_vc_A[c3_i416] = c3_uc_A[c3_i416];
  }

  for (c3_i417 = 0; c3_i417 < 9; c3_i417 = c3_i417 + 1) {
    c3_vc_B[c3_i417] = c3_uc_B[c3_i417];
  }

  for (c3_i418 = 0; c3_i418 < 3; c3_i418 = c3_i418 + 1) {
    c3_i419 = 0;
    for (c3_i420 = 0; c3_i420 < 3; c3_i420 = c3_i420 + 1) {
      c3_I2[c3_i419 + c3_i418] = 0.0;
      c3_i421 = 0;
      for (c3_i422 = 0; c3_i422 < 3; c3_i422 = c3_i422 + 1) {
        c3_I2[c3_i419 + c3_i418] = c3_I2[c3_i419 + c3_i418] + c3_vc_A[c3_i421 +
          c3_i418] * c3_vc_B[c3_i422 + c3_i419];
        c3_i421 = c3_i421 + 3;
      }

      c3_i419 = c3_i419 + 3;
    }
  }

  _SFD_SCRIPT_CALL(0, 83);
  for (c3_i423 = 0; c3_i423 < 16; c3_i423 = c3_i423 + 1) {
    c3_y_a[c3_i423] = c3_g[c3_i423];
  }

  for (c3_i424 = 0; c3_i424 < 16; c3_i424 = c3_i424 + 1) {
    c3_y_b[c3_i424] = c3_g23_0[c3_i424];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i425 = 0; c3_i425 < 16; c3_i425 = c3_i425 + 1) {
    c3_wc_A[c3_i425] = c3_y_a[c3_i425];
  }

  for (c3_i426 = 0; c3_i426 < 16; c3_i426 = c3_i426 + 1) {
    c3_wc_B[c3_i426] = c3_y_b[c3_i426];
  }

  for (c3_i427 = 0; c3_i427 < 16; c3_i427 = c3_i427 + 1) {
    c3_g[c3_i427] = 0.0;
  }

  for (c3_i428 = 0; c3_i428 < 16; c3_i428 = c3_i428 + 1) {
    c3_xc_A[c3_i428] = c3_wc_A[c3_i428];
  }

  for (c3_i429 = 0; c3_i429 < 16; c3_i429 = c3_i429 + 1) {
    c3_xc_B[c3_i429] = c3_wc_B[c3_i429];
  }

  for (c3_i430 = 0; c3_i430 < 16; c3_i430 = c3_i430 + 1) {
    c3_yc_A[c3_i430] = c3_xc_A[c3_i430];
  }

  for (c3_i431 = 0; c3_i431 < 16; c3_i431 = c3_i431 + 1) {
    c3_yc_B[c3_i431] = c3_xc_B[c3_i431];
  }

  for (c3_i432 = 0; c3_i432 < 4; c3_i432 = c3_i432 + 1) {
    c3_i433 = 0;
    for (c3_i434 = 0; c3_i434 < 4; c3_i434 = c3_i434 + 1) {
      c3_g[c3_i433 + c3_i432] = 0.0;
      c3_i435 = 0;
      for (c3_i436 = 0; c3_i436 < 4; c3_i436 = c3_i436 + 1) {
        c3_g[c3_i433 + c3_i432] = c3_g[c3_i433 + c3_i432] + c3_yc_A[c3_i435 +
          c3_i432] * c3_yc_B[c3_i436 + c3_i433];
        c3_i435 = c3_i435 + 4;
      }

      c3_i433 = c3_i433 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 84);
  for (c3_i437 = 0; c3_i437 < 16; c3_i437 = c3_i437 + 1) {
    c3_d_g[c3_i437] = c3_g[c3_i437];
  }

  for (c3_i438 = 0; c3_i438 < 3; c3_i438 = c3_i438 + 1) {
    c3_d_Cen[c3_i438] = c3_Cen[c3_i438 + 6];
  }

  c3_d_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_d_g, c3_d_Cen, c3_dv45);
  for (c3_i439 = 0; c3_i439 < 4; c3_i439 = c3_i439 + 1) {
    c3_r3[c3_i439] = c3_dv45[c3_i439];
  }

  sf_debug_symbol_switch(34U, 34U);
  _SFD_SCRIPT_CALL(0, 85);
  for (c3_i440 = 0; c3_i440 < 3; c3_i440 = c3_i440 + 1) {
    c3_b_r3[c3_i440] = c3_r3[c3_i440];
  }

  sf_debug_symbol_switch(34U, 81U);
  _SFD_SCRIPT_CALL(0, 86);
  c3_i441 = 0;
  c3_i442 = 0;
  for (c3_i443 = 0; c3_i443 < 3; c3_i443 = c3_i443 + 1) {
    for (c3_i444 = 0; c3_i444 < 3; c3_i444 = c3_i444 + 1) {
      c3_R[c3_i444 + c3_i441] = c3_g[c3_i444 + c3_i442];
    }

    c3_i441 = c3_i441 + 3;
    c3_i442 = c3_i442 + 4;
  }

  _SFD_SCRIPT_CALL(0, 87);
  c3_i445 = 0;
  for (c3_i446 = 0; c3_i446 < 3; c3_i446 = c3_i446 + 1) {
    c3_i447 = 0;
    for (c3_i448 = 0; c3_i448 < 3; c3_i448 = c3_i448 + 1) {
      c3_ab_a[c3_i448 + c3_i445] = c3_R[c3_i447 + c3_i446];
      c3_i447 = c3_i447 + 3;
    }

    c3_i445 = c3_i445 + 3;
  }

  for (c3_i449 = 0; c3_i449 < 9; c3_i449 = c3_i449 + 1) {
    c3_ab_b[c3_i449] = c3_I3[c3_i449];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i450 = 0; c3_i450 < 9; c3_i450 = c3_i450 + 1) {
    c3_ad_A[c3_i450] = c3_ab_a[c3_i450];
  }

  for (c3_i451 = 0; c3_i451 < 9; c3_i451 = c3_i451 + 1) {
    c3_ad_B[c3_i451] = c3_ab_b[c3_i451];
  }

  for (c3_i452 = 0; c3_i452 < 9; c3_i452 = c3_i452 + 1) {
    c3_bd_A[c3_i452] = c3_ad_A[c3_i452];
  }

  for (c3_i453 = 0; c3_i453 < 9; c3_i453 = c3_i453 + 1) {
    c3_bd_B[c3_i453] = c3_ad_B[c3_i453];
  }

  for (c3_i454 = 0; c3_i454 < 9; c3_i454 = c3_i454 + 1) {
    c3_cd_A[c3_i454] = c3_bd_A[c3_i454];
  }

  for (c3_i455 = 0; c3_i455 < 9; c3_i455 = c3_i455 + 1) {
    c3_cd_B[c3_i455] = c3_bd_B[c3_i455];
  }

  for (c3_i456 = 0; c3_i456 < 3; c3_i456 = c3_i456 + 1) {
    c3_i457 = 0;
    for (c3_i458 = 0; c3_i458 < 3; c3_i458 = c3_i458 + 1) {
      c3_p_y[c3_i457 + c3_i456] = 0.0;
      c3_i459 = 0;
      for (c3_i460 = 0; c3_i460 < 3; c3_i460 = c3_i460 + 1) {
        c3_p_y[c3_i457 + c3_i456] = c3_p_y[c3_i457 + c3_i456] + c3_cd_A[c3_i459
          + c3_i456] * c3_cd_B[c3_i460 + c3_i457];
        c3_i459 = c3_i459 + 3;
      }

      c3_i457 = c3_i457 + 3;
    }
  }

  for (c3_i461 = 0; c3_i461 < 9; c3_i461 = c3_i461 + 1) {
    c3_bb_a[c3_i461] = c3_p_y[c3_i461];
  }

  for (c3_i462 = 0; c3_i462 < 9; c3_i462 = c3_i462 + 1) {
    c3_bb_b[c3_i462] = c3_R[c3_i462];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i463 = 0; c3_i463 < 9; c3_i463 = c3_i463 + 1) {
    c3_dd_A[c3_i463] = c3_bb_a[c3_i463];
  }

  for (c3_i464 = 0; c3_i464 < 9; c3_i464 = c3_i464 + 1) {
    c3_dd_B[c3_i464] = c3_bb_b[c3_i464];
  }

  for (c3_i465 = 0; c3_i465 < 9; c3_i465 = c3_i465 + 1) {
    c3_I3[c3_i465] = 0.0;
  }

  for (c3_i466 = 0; c3_i466 < 9; c3_i466 = c3_i466 + 1) {
    c3_ed_A[c3_i466] = c3_dd_A[c3_i466];
  }

  for (c3_i467 = 0; c3_i467 < 9; c3_i467 = c3_i467 + 1) {
    c3_ed_B[c3_i467] = c3_dd_B[c3_i467];
  }

  for (c3_i468 = 0; c3_i468 < 9; c3_i468 = c3_i468 + 1) {
    c3_fd_A[c3_i468] = c3_ed_A[c3_i468];
  }

  for (c3_i469 = 0; c3_i469 < 9; c3_i469 = c3_i469 + 1) {
    c3_fd_B[c3_i469] = c3_ed_B[c3_i469];
  }

  for (c3_i470 = 0; c3_i470 < 3; c3_i470 = c3_i470 + 1) {
    c3_i471 = 0;
    for (c3_i472 = 0; c3_i472 < 3; c3_i472 = c3_i472 + 1) {
      c3_I3[c3_i471 + c3_i470] = 0.0;
      c3_i473 = 0;
      for (c3_i474 = 0; c3_i474 < 3; c3_i474 = c3_i474 + 1) {
        c3_I3[c3_i471 + c3_i470] = c3_I3[c3_i471 + c3_i470] + c3_fd_A[c3_i473 +
          c3_i470] * c3_fd_B[c3_i474 + c3_i471];
        c3_i473 = c3_i473 + 3;
      }

      c3_i471 = c3_i471 + 3;
    }
  }

  _SFD_SCRIPT_CALL(0, 88);
  for (c3_i475 = 0; c3_i475 < 16; c3_i475 = c3_i475 + 1) {
    c3_cb_a[c3_i475] = c3_g[c3_i475];
  }

  for (c3_i476 = 0; c3_i476 < 16; c3_i476 = c3_i476 + 1) {
    c3_cb_b[c3_i476] = c3_g34_0[c3_i476];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i477 = 0; c3_i477 < 16; c3_i477 = c3_i477 + 1) {
    c3_gd_A[c3_i477] = c3_cb_a[c3_i477];
  }

  for (c3_i478 = 0; c3_i478 < 16; c3_i478 = c3_i478 + 1) {
    c3_gd_B[c3_i478] = c3_cb_b[c3_i478];
  }

  for (c3_i479 = 0; c3_i479 < 16; c3_i479 = c3_i479 + 1) {
    c3_g[c3_i479] = 0.0;
  }

  for (c3_i480 = 0; c3_i480 < 16; c3_i480 = c3_i480 + 1) {
    c3_hd_A[c3_i480] = c3_gd_A[c3_i480];
  }

  for (c3_i481 = 0; c3_i481 < 16; c3_i481 = c3_i481 + 1) {
    c3_hd_B[c3_i481] = c3_gd_B[c3_i481];
  }

  for (c3_i482 = 0; c3_i482 < 16; c3_i482 = c3_i482 + 1) {
    c3_id_A[c3_i482] = c3_hd_A[c3_i482];
  }

  for (c3_i483 = 0; c3_i483 < 16; c3_i483 = c3_i483 + 1) {
    c3_id_B[c3_i483] = c3_hd_B[c3_i483];
  }

  for (c3_i484 = 0; c3_i484 < 4; c3_i484 = c3_i484 + 1) {
    c3_i485 = 0;
    for (c3_i486 = 0; c3_i486 < 4; c3_i486 = c3_i486 + 1) {
      c3_g[c3_i485 + c3_i484] = 0.0;
      c3_i487 = 0;
      for (c3_i488 = 0; c3_i488 < 4; c3_i488 = c3_i488 + 1) {
        c3_g[c3_i485 + c3_i484] = c3_g[c3_i485 + c3_i484] + c3_id_A[c3_i487 +
          c3_i484] * c3_id_B[c3_i488 + c3_i485];
        c3_i487 = c3_i487 + 4;
      }

      c3_i485 = c3_i485 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 89);
  for (c3_i489 = 0; c3_i489 < 16; c3_i489 = c3_i489 + 1) {
    c3_e_g[c3_i489] = c3_g[c3_i489];
  }

  for (c3_i490 = 0; c3_i490 < 3; c3_i490 = c3_i490 + 1) {
    c3_e_Cen[c3_i490] = c3_Cen[c3_i490 + 9];
  }

  c3_e_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_e_g, c3_e_Cen, c3_dv46);
  for (c3_i491 = 0; c3_i491 < 4; c3_i491 = c3_i491 + 1) {
    c3_r4[c3_i491] = c3_dv46[c3_i491];
  }

  sf_debug_symbol_switch(35U, 35U);
  _SFD_SCRIPT_CALL(0, 90);
  for (c3_i492 = 0; c3_i492 < 3; c3_i492 = c3_i492 + 1) {
    c3_b_r4[c3_i492] = c3_r4[c3_i492];
  }

  sf_debug_symbol_switch(35U, 82U);
  _SFD_SCRIPT_CALL(0, 91);
  c3_i493 = 0;
  c3_i494 = 0;
  for (c3_i495 = 0; c3_i495 < 3; c3_i495 = c3_i495 + 1) {
    for (c3_i496 = 0; c3_i496 < 3; c3_i496 = c3_i496 + 1) {
      c3_R[c3_i496 + c3_i493] = c3_g[c3_i496 + c3_i494];
    }

    c3_i493 = c3_i493 + 3;
    c3_i494 = c3_i494 + 4;
  }

  _SFD_SCRIPT_CALL(0, 92);
  c3_i497 = 0;
  for (c3_i498 = 0; c3_i498 < 3; c3_i498 = c3_i498 + 1) {
    c3_i499 = 0;
    for (c3_i500 = 0; c3_i500 < 3; c3_i500 = c3_i500 + 1) {
      c3_db_a[c3_i500 + c3_i497] = c3_R[c3_i499 + c3_i498];
      c3_i499 = c3_i499 + 3;
    }

    c3_i497 = c3_i497 + 3;
  }

  for (c3_i501 = 0; c3_i501 < 9; c3_i501 = c3_i501 + 1) {
    c3_db_b[c3_i501] = c3_I4[c3_i501];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i502 = 0; c3_i502 < 9; c3_i502 = c3_i502 + 1) {
    c3_jd_A[c3_i502] = c3_db_a[c3_i502];
  }

  for (c3_i503 = 0; c3_i503 < 9; c3_i503 = c3_i503 + 1) {
    c3_jd_B[c3_i503] = c3_db_b[c3_i503];
  }

  for (c3_i504 = 0; c3_i504 < 9; c3_i504 = c3_i504 + 1) {
    c3_kd_A[c3_i504] = c3_jd_A[c3_i504];
  }

  for (c3_i505 = 0; c3_i505 < 9; c3_i505 = c3_i505 + 1) {
    c3_kd_B[c3_i505] = c3_jd_B[c3_i505];
  }

  for (c3_i506 = 0; c3_i506 < 9; c3_i506 = c3_i506 + 1) {
    c3_ld_A[c3_i506] = c3_kd_A[c3_i506];
  }

  for (c3_i507 = 0; c3_i507 < 9; c3_i507 = c3_i507 + 1) {
    c3_ld_B[c3_i507] = c3_kd_B[c3_i507];
  }

  for (c3_i508 = 0; c3_i508 < 3; c3_i508 = c3_i508 + 1) {
    c3_i509 = 0;
    for (c3_i510 = 0; c3_i510 < 3; c3_i510 = c3_i510 + 1) {
      c3_q_y[c3_i509 + c3_i508] = 0.0;
      c3_i511 = 0;
      for (c3_i512 = 0; c3_i512 < 3; c3_i512 = c3_i512 + 1) {
        c3_q_y[c3_i509 + c3_i508] = c3_q_y[c3_i509 + c3_i508] + c3_ld_A[c3_i511
          + c3_i508] * c3_ld_B[c3_i512 + c3_i509];
        c3_i511 = c3_i511 + 3;
      }

      c3_i509 = c3_i509 + 3;
    }
  }

  for (c3_i513 = 0; c3_i513 < 9; c3_i513 = c3_i513 + 1) {
    c3_eb_a[c3_i513] = c3_q_y[c3_i513];
  }

  for (c3_i514 = 0; c3_i514 < 9; c3_i514 = c3_i514 + 1) {
    c3_eb_b[c3_i514] = c3_R[c3_i514];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i515 = 0; c3_i515 < 9; c3_i515 = c3_i515 + 1) {
    c3_md_A[c3_i515] = c3_eb_a[c3_i515];
  }

  for (c3_i516 = 0; c3_i516 < 9; c3_i516 = c3_i516 + 1) {
    c3_md_B[c3_i516] = c3_eb_b[c3_i516];
  }

  for (c3_i517 = 0; c3_i517 < 9; c3_i517 = c3_i517 + 1) {
    c3_I4[c3_i517] = 0.0;
  }

  for (c3_i518 = 0; c3_i518 < 9; c3_i518 = c3_i518 + 1) {
    c3_nd_A[c3_i518] = c3_md_A[c3_i518];
  }

  for (c3_i519 = 0; c3_i519 < 9; c3_i519 = c3_i519 + 1) {
    c3_nd_B[c3_i519] = c3_md_B[c3_i519];
  }

  for (c3_i520 = 0; c3_i520 < 9; c3_i520 = c3_i520 + 1) {
    c3_od_A[c3_i520] = c3_nd_A[c3_i520];
  }

  for (c3_i521 = 0; c3_i521 < 9; c3_i521 = c3_i521 + 1) {
    c3_od_B[c3_i521] = c3_nd_B[c3_i521];
  }

  for (c3_i522 = 0; c3_i522 < 3; c3_i522 = c3_i522 + 1) {
    c3_i523 = 0;
    for (c3_i524 = 0; c3_i524 < 3; c3_i524 = c3_i524 + 1) {
      c3_I4[c3_i523 + c3_i522] = 0.0;
      c3_i525 = 0;
      for (c3_i526 = 0; c3_i526 < 3; c3_i526 = c3_i526 + 1) {
        c3_I4[c3_i523 + c3_i522] = c3_I4[c3_i523 + c3_i522] + c3_od_A[c3_i525 +
          c3_i522] * c3_od_B[c3_i526 + c3_i523];
        c3_i525 = c3_i525 + 3;
      }

      c3_i523 = c3_i523 + 3;
    }
  }

  _SFD_SCRIPT_CALL(0, 93);
  for (c3_i527 = 0; c3_i527 < 16; c3_i527 = c3_i527 + 1) {
    c3_fb_a[c3_i527] = c3_g[c3_i527];
  }

  for (c3_i528 = 0; c3_i528 < 16; c3_i528 = c3_i528 + 1) {
    c3_fb_b[c3_i528] = c3_g45_0[c3_i528];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i529 = 0; c3_i529 < 16; c3_i529 = c3_i529 + 1) {
    c3_pd_A[c3_i529] = c3_fb_a[c3_i529];
  }

  for (c3_i530 = 0; c3_i530 < 16; c3_i530 = c3_i530 + 1) {
    c3_pd_B[c3_i530] = c3_fb_b[c3_i530];
  }

  for (c3_i531 = 0; c3_i531 < 16; c3_i531 = c3_i531 + 1) {
    c3_g[c3_i531] = 0.0;
  }

  for (c3_i532 = 0; c3_i532 < 16; c3_i532 = c3_i532 + 1) {
    c3_qd_A[c3_i532] = c3_pd_A[c3_i532];
  }

  for (c3_i533 = 0; c3_i533 < 16; c3_i533 = c3_i533 + 1) {
    c3_qd_B[c3_i533] = c3_pd_B[c3_i533];
  }

  for (c3_i534 = 0; c3_i534 < 16; c3_i534 = c3_i534 + 1) {
    c3_rd_A[c3_i534] = c3_qd_A[c3_i534];
  }

  for (c3_i535 = 0; c3_i535 < 16; c3_i535 = c3_i535 + 1) {
    c3_rd_B[c3_i535] = c3_qd_B[c3_i535];
  }

  for (c3_i536 = 0; c3_i536 < 4; c3_i536 = c3_i536 + 1) {
    c3_i537 = 0;
    for (c3_i538 = 0; c3_i538 < 4; c3_i538 = c3_i538 + 1) {
      c3_g[c3_i537 + c3_i536] = 0.0;
      c3_i539 = 0;
      for (c3_i540 = 0; c3_i540 < 4; c3_i540 = c3_i540 + 1) {
        c3_g[c3_i537 + c3_i536] = c3_g[c3_i537 + c3_i536] + c3_rd_A[c3_i539 +
          c3_i536] * c3_rd_B[c3_i540 + c3_i537];
        c3_i539 = c3_i539 + 4;
      }

      c3_i537 = c3_i537 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 94);
  for (c3_i541 = 0; c3_i541 < 16; c3_i541 = c3_i541 + 1) {
    c3_f_g[c3_i541] = c3_g[c3_i541];
  }

  for (c3_i542 = 0; c3_i542 < 3; c3_i542 = c3_i542 + 1) {
    c3_f_Cen[c3_i542] = c3_Cen[c3_i542 + 12];
  }

  c3_f_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_f_g, c3_f_Cen, c3_dv47);
  for (c3_i543 = 0; c3_i543 < 4; c3_i543 = c3_i543 + 1) {
    c3_r5[c3_i543] = c3_dv47[c3_i543];
  }

  sf_debug_symbol_switch(36U, 36U);
  _SFD_SCRIPT_CALL(0, 95);
  for (c3_i544 = 0; c3_i544 < 3; c3_i544 = c3_i544 + 1) {
    c3_b_r5[c3_i544] = c3_r5[c3_i544];
  }

  sf_debug_symbol_switch(36U, 83U);
  _SFD_SCRIPT_CALL(0, 96);
  c3_i545 = 0;
  c3_i546 = 0;
  for (c3_i547 = 0; c3_i547 < 3; c3_i547 = c3_i547 + 1) {
    for (c3_i548 = 0; c3_i548 < 3; c3_i548 = c3_i548 + 1) {
      c3_R[c3_i548 + c3_i545] = c3_g[c3_i548 + c3_i546];
    }

    c3_i545 = c3_i545 + 3;
    c3_i546 = c3_i546 + 4;
  }

  _SFD_SCRIPT_CALL(0, 97);
  c3_i549 = 0;
  for (c3_i550 = 0; c3_i550 < 3; c3_i550 = c3_i550 + 1) {
    c3_i551 = 0;
    for (c3_i552 = 0; c3_i552 < 3; c3_i552 = c3_i552 + 1) {
      c3_gb_a[c3_i552 + c3_i549] = c3_R[c3_i551 + c3_i550];
      c3_i551 = c3_i551 + 3;
    }

    c3_i549 = c3_i549 + 3;
  }

  for (c3_i553 = 0; c3_i553 < 9; c3_i553 = c3_i553 + 1) {
    c3_gb_b[c3_i553] = c3_I5[c3_i553];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i554 = 0; c3_i554 < 9; c3_i554 = c3_i554 + 1) {
    c3_sd_A[c3_i554] = c3_gb_a[c3_i554];
  }

  for (c3_i555 = 0; c3_i555 < 9; c3_i555 = c3_i555 + 1) {
    c3_sd_B[c3_i555] = c3_gb_b[c3_i555];
  }

  for (c3_i556 = 0; c3_i556 < 9; c3_i556 = c3_i556 + 1) {
    c3_td_A[c3_i556] = c3_sd_A[c3_i556];
  }

  for (c3_i557 = 0; c3_i557 < 9; c3_i557 = c3_i557 + 1) {
    c3_td_B[c3_i557] = c3_sd_B[c3_i557];
  }

  for (c3_i558 = 0; c3_i558 < 9; c3_i558 = c3_i558 + 1) {
    c3_ud_A[c3_i558] = c3_td_A[c3_i558];
  }

  for (c3_i559 = 0; c3_i559 < 9; c3_i559 = c3_i559 + 1) {
    c3_ud_B[c3_i559] = c3_td_B[c3_i559];
  }

  for (c3_i560 = 0; c3_i560 < 3; c3_i560 = c3_i560 + 1) {
    c3_i561 = 0;
    for (c3_i562 = 0; c3_i562 < 3; c3_i562 = c3_i562 + 1) {
      c3_r_y[c3_i561 + c3_i560] = 0.0;
      c3_i563 = 0;
      for (c3_i564 = 0; c3_i564 < 3; c3_i564 = c3_i564 + 1) {
        c3_r_y[c3_i561 + c3_i560] = c3_r_y[c3_i561 + c3_i560] + c3_ud_A[c3_i563
          + c3_i560] * c3_ud_B[c3_i564 + c3_i561];
        c3_i563 = c3_i563 + 3;
      }

      c3_i561 = c3_i561 + 3;
    }
  }

  for (c3_i565 = 0; c3_i565 < 9; c3_i565 = c3_i565 + 1) {
    c3_hb_a[c3_i565] = c3_r_y[c3_i565];
  }

  for (c3_i566 = 0; c3_i566 < 9; c3_i566 = c3_i566 + 1) {
    c3_hb_b[c3_i566] = c3_R[c3_i566];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i567 = 0; c3_i567 < 9; c3_i567 = c3_i567 + 1) {
    c3_vd_A[c3_i567] = c3_hb_a[c3_i567];
  }

  for (c3_i568 = 0; c3_i568 < 9; c3_i568 = c3_i568 + 1) {
    c3_vd_B[c3_i568] = c3_hb_b[c3_i568];
  }

  for (c3_i569 = 0; c3_i569 < 9; c3_i569 = c3_i569 + 1) {
    c3_I5[c3_i569] = 0.0;
  }

  for (c3_i570 = 0; c3_i570 < 9; c3_i570 = c3_i570 + 1) {
    c3_wd_A[c3_i570] = c3_vd_A[c3_i570];
  }

  for (c3_i571 = 0; c3_i571 < 9; c3_i571 = c3_i571 + 1) {
    c3_wd_B[c3_i571] = c3_vd_B[c3_i571];
  }

  for (c3_i572 = 0; c3_i572 < 9; c3_i572 = c3_i572 + 1) {
    c3_xd_A[c3_i572] = c3_wd_A[c3_i572];
  }

  for (c3_i573 = 0; c3_i573 < 9; c3_i573 = c3_i573 + 1) {
    c3_xd_B[c3_i573] = c3_wd_B[c3_i573];
  }

  for (c3_i574 = 0; c3_i574 < 3; c3_i574 = c3_i574 + 1) {
    c3_i575 = 0;
    for (c3_i576 = 0; c3_i576 < 3; c3_i576 = c3_i576 + 1) {
      c3_I5[c3_i575 + c3_i574] = 0.0;
      c3_i577 = 0;
      for (c3_i578 = 0; c3_i578 < 3; c3_i578 = c3_i578 + 1) {
        c3_I5[c3_i575 + c3_i574] = c3_I5[c3_i575 + c3_i574] + c3_xd_A[c3_i577 +
          c3_i574] * c3_xd_B[c3_i578 + c3_i575];
        c3_i577 = c3_i577 + 3;
      }

      c3_i575 = c3_i575 + 3;
    }
  }

  _SFD_SCRIPT_CALL(0, 98);
  for (c3_i579 = 0; c3_i579 < 16; c3_i579 = c3_i579 + 1) {
    c3_ib_a[c3_i579] = c3_g[c3_i579];
  }

  for (c3_i580 = 0; c3_i580 < 16; c3_i580 = c3_i580 + 1) {
    c3_ib_b[c3_i580] = c3_g56_0[c3_i580];
  }

  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i581 = 0; c3_i581 < 16; c3_i581 = c3_i581 + 1) {
    c3_yd_A[c3_i581] = c3_ib_a[c3_i581];
  }

  for (c3_i582 = 0; c3_i582 < 16; c3_i582 = c3_i582 + 1) {
    c3_yd_B[c3_i582] = c3_ib_b[c3_i582];
  }

  for (c3_i583 = 0; c3_i583 < 16; c3_i583 = c3_i583 + 1) {
    c3_g[c3_i583] = 0.0;
  }

  for (c3_i584 = 0; c3_i584 < 16; c3_i584 = c3_i584 + 1) {
    c3_ae_A[c3_i584] = c3_yd_A[c3_i584];
  }

  for (c3_i585 = 0; c3_i585 < 16; c3_i585 = c3_i585 + 1) {
    c3_ae_B[c3_i585] = c3_yd_B[c3_i585];
  }

  for (c3_i586 = 0; c3_i586 < 16; c3_i586 = c3_i586 + 1) {
    c3_be_A[c3_i586] = c3_ae_A[c3_i586];
  }

  for (c3_i587 = 0; c3_i587 < 16; c3_i587 = c3_i587 + 1) {
    c3_be_B[c3_i587] = c3_ae_B[c3_i587];
  }

  for (c3_i588 = 0; c3_i588 < 4; c3_i588 = c3_i588 + 1) {
    c3_i589 = 0;
    for (c3_i590 = 0; c3_i590 < 4; c3_i590 = c3_i590 + 1) {
      c3_g[c3_i589 + c3_i588] = 0.0;
      c3_i591 = 0;
      for (c3_i592 = 0; c3_i592 < 4; c3_i592 = c3_i592 + 1) {
        c3_g[c3_i589 + c3_i588] = c3_g[c3_i589 + c3_i588] + c3_be_A[c3_i591 +
          c3_i588] * c3_be_B[c3_i592 + c3_i589];
        c3_i591 = c3_i591 + 4;
      }

      c3_i589 = c3_i589 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 99);
  for (c3_i593 = 0; c3_i593 < 16; c3_i593 = c3_i593 + 1) {
    c3_g_g[c3_i593] = c3_g[c3_i593];
  }

  for (c3_i594 = 0; c3_i594 < 3; c3_i594 = c3_i594 + 1) {
    c3_g_Cen[c3_i594] = c3_Cen[c3_i594 + 15];
  }

  c3_g_Cen[3] = 1.0;
  c3_mldivide(chartInstance, c3_g_g, c3_g_Cen, c3_dv48);
  for (c3_i595 = 0; c3_i595 < 4; c3_i595 = c3_i595 + 1) {
    c3_r6[c3_i595] = c3_dv48[c3_i595];
  }

  sf_debug_symbol_switch(37U, 37U);
  _SFD_SCRIPT_CALL(0, 100);
  for (c3_i596 = 0; c3_i596 < 3; c3_i596 = c3_i596 + 1) {
    c3_b_r6[c3_i596] = c3_r6[c3_i596];
  }

  sf_debug_symbol_switch(37U, 84U);
  _SFD_SCRIPT_CALL(0, 101);
  c3_i597 = 0;
  c3_i598 = 0;
  for (c3_i599 = 0; c3_i599 < 3; c3_i599 = c3_i599 + 1) {
    for (c3_i600 = 0; c3_i600 < 3; c3_i600 = c3_i600 + 1) {
      c3_R[c3_i600 + c3_i597] = c3_g[c3_i600 + c3_i598];
    }

    c3_i597 = c3_i597 + 3;
    c3_i598 = c3_i598 + 4;
  }

  _SFD_SCRIPT_CALL(0, 102);
  c3_i601 = 0;
  for (c3_i602 = 0; c3_i602 < 3; c3_i602 = c3_i602 + 1) {
    c3_i603 = 0;
    for (c3_i604 = 0; c3_i604 < 3; c3_i604 = c3_i604 + 1) {
      c3_jb_a[c3_i604 + c3_i601] = c3_R[c3_i603 + c3_i602];
      c3_i603 = c3_i603 + 3;
    }

    c3_i601 = c3_i601 + 3;
  }

  for (c3_i605 = 0; c3_i605 < 9; c3_i605 = c3_i605 + 1) {
    c3_jb_b[c3_i605] = c3_I6[c3_i605];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i606 = 0; c3_i606 < 9; c3_i606 = c3_i606 + 1) {
    c3_ce_A[c3_i606] = c3_jb_a[c3_i606];
  }

  for (c3_i607 = 0; c3_i607 < 9; c3_i607 = c3_i607 + 1) {
    c3_ce_B[c3_i607] = c3_jb_b[c3_i607];
  }

  for (c3_i608 = 0; c3_i608 < 9; c3_i608 = c3_i608 + 1) {
    c3_de_A[c3_i608] = c3_ce_A[c3_i608];
  }

  for (c3_i609 = 0; c3_i609 < 9; c3_i609 = c3_i609 + 1) {
    c3_de_B[c3_i609] = c3_ce_B[c3_i609];
  }

  for (c3_i610 = 0; c3_i610 < 9; c3_i610 = c3_i610 + 1) {
    c3_ee_A[c3_i610] = c3_de_A[c3_i610];
  }

  for (c3_i611 = 0; c3_i611 < 9; c3_i611 = c3_i611 + 1) {
    c3_ee_B[c3_i611] = c3_de_B[c3_i611];
  }

  for (c3_i612 = 0; c3_i612 < 3; c3_i612 = c3_i612 + 1) {
    c3_i613 = 0;
    for (c3_i614 = 0; c3_i614 < 3; c3_i614 = c3_i614 + 1) {
      c3_s_y[c3_i613 + c3_i612] = 0.0;
      c3_i615 = 0;
      for (c3_i616 = 0; c3_i616 < 3; c3_i616 = c3_i616 + 1) {
        c3_s_y[c3_i613 + c3_i612] = c3_s_y[c3_i613 + c3_i612] + c3_ee_A[c3_i615
          + c3_i612] * c3_ee_B[c3_i616 + c3_i613];
        c3_i615 = c3_i615 + 3;
      }

      c3_i613 = c3_i613 + 3;
    }
  }

  for (c3_i617 = 0; c3_i617 < 9; c3_i617 = c3_i617 + 1) {
    c3_kb_a[c3_i617] = c3_s_y[c3_i617];
  }

  for (c3_i618 = 0; c3_i618 < 9; c3_i618 = c3_i618 + 1) {
    c3_kb_b[c3_i618] = c3_R[c3_i618];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i619 = 0; c3_i619 < 9; c3_i619 = c3_i619 + 1) {
    c3_fe_A[c3_i619] = c3_kb_a[c3_i619];
  }

  for (c3_i620 = 0; c3_i620 < 9; c3_i620 = c3_i620 + 1) {
    c3_fe_B[c3_i620] = c3_kb_b[c3_i620];
  }

  for (c3_i621 = 0; c3_i621 < 9; c3_i621 = c3_i621 + 1) {
    c3_I6[c3_i621] = 0.0;
  }

  for (c3_i622 = 0; c3_i622 < 9; c3_i622 = c3_i622 + 1) {
    c3_ge_A[c3_i622] = c3_fe_A[c3_i622];
  }

  for (c3_i623 = 0; c3_i623 < 9; c3_i623 = c3_i623 + 1) {
    c3_ge_B[c3_i623] = c3_fe_B[c3_i623];
  }

  for (c3_i624 = 0; c3_i624 < 9; c3_i624 = c3_i624 + 1) {
    c3_he_A[c3_i624] = c3_ge_A[c3_i624];
  }

  for (c3_i625 = 0; c3_i625 < 9; c3_i625 = c3_i625 + 1) {
    c3_he_B[c3_i625] = c3_ge_B[c3_i625];
  }

  for (c3_i626 = 0; c3_i626 < 3; c3_i626 = c3_i626 + 1) {
    c3_i627 = 0;
    for (c3_i628 = 0; c3_i628 < 3; c3_i628 = c3_i628 + 1) {
      c3_I6[c3_i627 + c3_i626] = 0.0;
      c3_i629 = 0;
      for (c3_i630 = 0; c3_i630 < 3; c3_i630 = c3_i630 + 1) {
        c3_I6[c3_i627 + c3_i626] = c3_I6[c3_i627 + c3_i626] + c3_he_A[c3_i629 +
          c3_i626] * c3_he_B[c3_i630 + c3_i627];
        c3_i629 = c3_i629 + 3;
      }

      c3_i627 = c3_i627 + 3;
    }
  }

  /*  %% calculate momentt of inertia in Ci,i=1,2,3,4,5,6 */
  _SFD_SCRIPT_CALL(0, 107);
  c3_lb_a = c3_m1;
  for (c3_i631 = 0; c3_i631 < 9; c3_i631 = c3_i631 + 1) {
    c3_t_y[c3_i631] = c3_lb_a * c3_dv49[c3_i631];
  }

  c3_mb_a = -c3_m1;
  for (c3_i632 = 0; c3_i632 < 3; c3_i632 = c3_i632 + 1) {
    c3_c_r1[c3_i632] = c3_b_r1[c3_i632];
  }

  c3_hat(chartInstance, c3_c_r1, c3_lb_b);
  for (c3_i633 = 0; c3_i633 < 9; c3_i633 = c3_i633 + 1) {
    c3_u_y[c3_i633] = c3_mb_a * c3_lb_b[c3_i633];
  }

  c3_nb_a = c3_m1;
  for (c3_i634 = 0; c3_i634 < 3; c3_i634 = c3_i634 + 1) {
    c3_d_r1[c3_i634] = c3_b_r1[c3_i634];
  }

  c3_hat(chartInstance, c3_d_r1, c3_mb_b);
  for (c3_i635 = 0; c3_i635 < 9; c3_i635 = c3_i635 + 1) {
    c3_v_y[c3_i635] = c3_nb_a * c3_mb_b[c3_i635];
  }

  c3_ob_a = c3_m1;
  for (c3_i636 = 0; c3_i636 < 3; c3_i636 = c3_i636 + 1) {
    c3_e_r1[c3_i636] = c3_b_r1[c3_i636];
  }

  c3_hat(chartInstance, c3_e_r1, c3_nb_b);
  for (c3_i637 = 0; c3_i637 < 9; c3_i637 = c3_i637 + 1) {
    c3_w_y[c3_i637] = c3_ob_a * c3_nb_b[c3_i637];
  }

  for (c3_i638 = 0; c3_i638 < 9; c3_i638 = c3_i638 + 1) {
    c3_pb_a[c3_i638] = c3_w_y[c3_i638];
  }

  for (c3_i639 = 0; c3_i639 < 3; c3_i639 = c3_i639 + 1) {
    c3_f_r1[c3_i639] = c3_b_r1[c3_i639];
  }

  c3_hat(chartInstance, c3_f_r1, c3_ob_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i640 = 0; c3_i640 < 9; c3_i640 = c3_i640 + 1) {
    c3_ie_A[c3_i640] = c3_pb_a[c3_i640];
  }

  for (c3_i641 = 0; c3_i641 < 9; c3_i641 = c3_i641 + 1) {
    c3_ie_B[c3_i641] = c3_ob_b[c3_i641];
  }

  for (c3_i642 = 0; c3_i642 < 9; c3_i642 = c3_i642 + 1) {
    c3_je_A[c3_i642] = c3_ie_A[c3_i642];
  }

  for (c3_i643 = 0; c3_i643 < 9; c3_i643 = c3_i643 + 1) {
    c3_je_B[c3_i643] = c3_ie_B[c3_i643];
  }

  for (c3_i644 = 0; c3_i644 < 9; c3_i644 = c3_i644 + 1) {
    c3_ke_A[c3_i644] = c3_je_A[c3_i644];
  }

  for (c3_i645 = 0; c3_i645 < 9; c3_i645 = c3_i645 + 1) {
    c3_ke_B[c3_i645] = c3_je_B[c3_i645];
  }

  for (c3_i646 = 0; c3_i646 < 3; c3_i646 = c3_i646 + 1) {
    c3_i647 = 0;
    for (c3_i648 = 0; c3_i648 < 3; c3_i648 = c3_i648 + 1) {
      c3_x_y[c3_i647 + c3_i646] = 0.0;
      c3_i649 = 0;
      for (c3_i650 = 0; c3_i650 < 3; c3_i650 = c3_i650 + 1) {
        c3_x_y[c3_i647 + c3_i646] = c3_x_y[c3_i647 + c3_i646] + c3_ke_A[c3_i649
          + c3_i646] * c3_ke_B[c3_i650 + c3_i647];
        c3_i649 = c3_i649 + 3;
      }

      c3_i647 = c3_i647 + 3;
    }
  }

  c3_i651 = 0;
  c3_i652 = 0;
  for (c3_i653 = 0; c3_i653 < 3; c3_i653 = c3_i653 + 1) {
    for (c3_i654 = 0; c3_i654 < 3; c3_i654 = c3_i654 + 1) {
      c3_M1[c3_i654 + c3_i651] = c3_t_y[c3_i654 + c3_i652];
    }

    c3_i651 = c3_i651 + 6;
    c3_i652 = c3_i652 + 3;
  }

  c3_i655 = 0;
  c3_i656 = 0;
  for (c3_i657 = 0; c3_i657 < 3; c3_i657 = c3_i657 + 1) {
    for (c3_i658 = 0; c3_i658 < 3; c3_i658 = c3_i658 + 1) {
      c3_M1[(c3_i658 + c3_i655) + 18] = c3_u_y[c3_i658 + c3_i656];
    }

    c3_i655 = c3_i655 + 6;
    c3_i656 = c3_i656 + 3;
  }

  c3_i659 = 0;
  c3_i660 = 0;
  for (c3_i661 = 0; c3_i661 < 3; c3_i661 = c3_i661 + 1) {
    for (c3_i662 = 0; c3_i662 < 3; c3_i662 = c3_i662 + 1) {
      c3_M1[(c3_i662 + c3_i659) + 3] = c3_v_y[c3_i662 + c3_i660];
    }

    c3_i659 = c3_i659 + 6;
    c3_i660 = c3_i660 + 3;
  }

  c3_i663 = 0;
  c3_i664 = 0;
  for (c3_i665 = 0; c3_i665 < 3; c3_i665 = c3_i665 + 1) {
    for (c3_i666 = 0; c3_i666 < 3; c3_i666 = c3_i666 + 1) {
      c3_M1[(c3_i666 + c3_i663) + 21] = c3_I1[c3_i666 + c3_i664] -
        c3_x_y[c3_i666 + c3_i664];
    }

    c3_i663 = c3_i663 + 6;
    c3_i664 = c3_i664 + 3;
  }

  _SFD_SCRIPT_CALL(0, 110);
  c3_qb_a = c3_m2;
  for (c3_i667 = 0; c3_i667 < 9; c3_i667 = c3_i667 + 1) {
    c3_y_y[c3_i667] = c3_qb_a * c3_dv49[c3_i667];
  }

  c3_rb_a = -c3_m2;
  for (c3_i668 = 0; c3_i668 < 3; c3_i668 = c3_i668 + 1) {
    c3_c_r2[c3_i668] = c3_b_r2[c3_i668];
  }

  c3_hat(chartInstance, c3_c_r2, c3_pb_b);
  for (c3_i669 = 0; c3_i669 < 9; c3_i669 = c3_i669 + 1) {
    c3_ab_y[c3_i669] = c3_rb_a * c3_pb_b[c3_i669];
  }

  c3_sb_a = c3_m2;
  for (c3_i670 = 0; c3_i670 < 3; c3_i670 = c3_i670 + 1) {
    c3_d_r2[c3_i670] = c3_b_r2[c3_i670];
  }

  c3_hat(chartInstance, c3_d_r2, c3_qb_b);
  for (c3_i671 = 0; c3_i671 < 9; c3_i671 = c3_i671 + 1) {
    c3_bb_y[c3_i671] = c3_sb_a * c3_qb_b[c3_i671];
  }

  c3_tb_a = c3_m2;
  for (c3_i672 = 0; c3_i672 < 3; c3_i672 = c3_i672 + 1) {
    c3_e_r2[c3_i672] = c3_b_r2[c3_i672];
  }

  c3_hat(chartInstance, c3_e_r2, c3_rb_b);
  for (c3_i673 = 0; c3_i673 < 9; c3_i673 = c3_i673 + 1) {
    c3_cb_y[c3_i673] = c3_tb_a * c3_rb_b[c3_i673];
  }

  for (c3_i674 = 0; c3_i674 < 9; c3_i674 = c3_i674 + 1) {
    c3_ub_a[c3_i674] = c3_cb_y[c3_i674];
  }

  for (c3_i675 = 0; c3_i675 < 3; c3_i675 = c3_i675 + 1) {
    c3_f_r2[c3_i675] = c3_b_r2[c3_i675];
  }

  c3_hat(chartInstance, c3_f_r2, c3_sb_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i676 = 0; c3_i676 < 9; c3_i676 = c3_i676 + 1) {
    c3_le_A[c3_i676] = c3_ub_a[c3_i676];
  }

  for (c3_i677 = 0; c3_i677 < 9; c3_i677 = c3_i677 + 1) {
    c3_le_B[c3_i677] = c3_sb_b[c3_i677];
  }

  for (c3_i678 = 0; c3_i678 < 9; c3_i678 = c3_i678 + 1) {
    c3_me_A[c3_i678] = c3_le_A[c3_i678];
  }

  for (c3_i679 = 0; c3_i679 < 9; c3_i679 = c3_i679 + 1) {
    c3_me_B[c3_i679] = c3_le_B[c3_i679];
  }

  for (c3_i680 = 0; c3_i680 < 9; c3_i680 = c3_i680 + 1) {
    c3_ne_A[c3_i680] = c3_me_A[c3_i680];
  }

  for (c3_i681 = 0; c3_i681 < 9; c3_i681 = c3_i681 + 1) {
    c3_ne_B[c3_i681] = c3_me_B[c3_i681];
  }

  for (c3_i682 = 0; c3_i682 < 3; c3_i682 = c3_i682 + 1) {
    c3_i683 = 0;
    for (c3_i684 = 0; c3_i684 < 3; c3_i684 = c3_i684 + 1) {
      c3_db_y[c3_i683 + c3_i682] = 0.0;
      c3_i685 = 0;
      for (c3_i686 = 0; c3_i686 < 3; c3_i686 = c3_i686 + 1) {
        c3_db_y[c3_i683 + c3_i682] = c3_db_y[c3_i683 + c3_i682] +
          c3_ne_A[c3_i685 + c3_i682] * c3_ne_B[c3_i686 + c3_i683];
        c3_i685 = c3_i685 + 3;
      }

      c3_i683 = c3_i683 + 3;
    }
  }

  c3_i687 = 0;
  c3_i688 = 0;
  for (c3_i689 = 0; c3_i689 < 3; c3_i689 = c3_i689 + 1) {
    for (c3_i690 = 0; c3_i690 < 3; c3_i690 = c3_i690 + 1) {
      c3_M2[c3_i690 + c3_i687] = c3_y_y[c3_i690 + c3_i688];
    }

    c3_i687 = c3_i687 + 6;
    c3_i688 = c3_i688 + 3;
  }

  c3_i691 = 0;
  c3_i692 = 0;
  for (c3_i693 = 0; c3_i693 < 3; c3_i693 = c3_i693 + 1) {
    for (c3_i694 = 0; c3_i694 < 3; c3_i694 = c3_i694 + 1) {
      c3_M2[(c3_i694 + c3_i691) + 18] = c3_ab_y[c3_i694 + c3_i692];
    }

    c3_i691 = c3_i691 + 6;
    c3_i692 = c3_i692 + 3;
  }

  c3_i695 = 0;
  c3_i696 = 0;
  for (c3_i697 = 0; c3_i697 < 3; c3_i697 = c3_i697 + 1) {
    for (c3_i698 = 0; c3_i698 < 3; c3_i698 = c3_i698 + 1) {
      c3_M2[(c3_i698 + c3_i695) + 3] = c3_bb_y[c3_i698 + c3_i696];
    }

    c3_i695 = c3_i695 + 6;
    c3_i696 = c3_i696 + 3;
  }

  c3_i699 = 0;
  c3_i700 = 0;
  for (c3_i701 = 0; c3_i701 < 3; c3_i701 = c3_i701 + 1) {
    for (c3_i702 = 0; c3_i702 < 3; c3_i702 = c3_i702 + 1) {
      c3_M2[(c3_i702 + c3_i699) + 21] = c3_I2[c3_i702 + c3_i700] -
        c3_db_y[c3_i702 + c3_i700];
    }

    c3_i699 = c3_i699 + 6;
    c3_i700 = c3_i700 + 3;
  }

  _SFD_SCRIPT_CALL(0, 113);
  c3_vb_a = c3_m3;
  for (c3_i703 = 0; c3_i703 < 9; c3_i703 = c3_i703 + 1) {
    c3_eb_y[c3_i703] = c3_vb_a * c3_dv49[c3_i703];
  }

  c3_wb_a = -c3_m3;
  for (c3_i704 = 0; c3_i704 < 3; c3_i704 = c3_i704 + 1) {
    c3_c_r3[c3_i704] = c3_b_r3[c3_i704];
  }

  c3_hat(chartInstance, c3_c_r3, c3_tb_b);
  for (c3_i705 = 0; c3_i705 < 9; c3_i705 = c3_i705 + 1) {
    c3_fb_y[c3_i705] = c3_wb_a * c3_tb_b[c3_i705];
  }

  c3_xb_a = c3_m3;
  for (c3_i706 = 0; c3_i706 < 3; c3_i706 = c3_i706 + 1) {
    c3_d_r3[c3_i706] = c3_b_r3[c3_i706];
  }

  c3_hat(chartInstance, c3_d_r3, c3_ub_b);
  for (c3_i707 = 0; c3_i707 < 9; c3_i707 = c3_i707 + 1) {
    c3_gb_y[c3_i707] = c3_xb_a * c3_ub_b[c3_i707];
  }

  c3_yb_a = c3_m3;
  for (c3_i708 = 0; c3_i708 < 3; c3_i708 = c3_i708 + 1) {
    c3_e_r3[c3_i708] = c3_b_r3[c3_i708];
  }

  c3_hat(chartInstance, c3_e_r3, c3_vb_b);
  for (c3_i709 = 0; c3_i709 < 9; c3_i709 = c3_i709 + 1) {
    c3_hb_y[c3_i709] = c3_yb_a * c3_vb_b[c3_i709];
  }

  for (c3_i710 = 0; c3_i710 < 9; c3_i710 = c3_i710 + 1) {
    c3_ac_a[c3_i710] = c3_hb_y[c3_i710];
  }

  for (c3_i711 = 0; c3_i711 < 3; c3_i711 = c3_i711 + 1) {
    c3_f_r3[c3_i711] = c3_b_r3[c3_i711];
  }

  c3_hat(chartInstance, c3_f_r3, c3_wb_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i712 = 0; c3_i712 < 9; c3_i712 = c3_i712 + 1) {
    c3_oe_A[c3_i712] = c3_ac_a[c3_i712];
  }

  for (c3_i713 = 0; c3_i713 < 9; c3_i713 = c3_i713 + 1) {
    c3_oe_B[c3_i713] = c3_wb_b[c3_i713];
  }

  for (c3_i714 = 0; c3_i714 < 9; c3_i714 = c3_i714 + 1) {
    c3_pe_A[c3_i714] = c3_oe_A[c3_i714];
  }

  for (c3_i715 = 0; c3_i715 < 9; c3_i715 = c3_i715 + 1) {
    c3_pe_B[c3_i715] = c3_oe_B[c3_i715];
  }

  for (c3_i716 = 0; c3_i716 < 9; c3_i716 = c3_i716 + 1) {
    c3_qe_A[c3_i716] = c3_pe_A[c3_i716];
  }

  for (c3_i717 = 0; c3_i717 < 9; c3_i717 = c3_i717 + 1) {
    c3_qe_B[c3_i717] = c3_pe_B[c3_i717];
  }

  for (c3_i718 = 0; c3_i718 < 3; c3_i718 = c3_i718 + 1) {
    c3_i719 = 0;
    for (c3_i720 = 0; c3_i720 < 3; c3_i720 = c3_i720 + 1) {
      c3_ib_y[c3_i719 + c3_i718] = 0.0;
      c3_i721 = 0;
      for (c3_i722 = 0; c3_i722 < 3; c3_i722 = c3_i722 + 1) {
        c3_ib_y[c3_i719 + c3_i718] = c3_ib_y[c3_i719 + c3_i718] +
          c3_qe_A[c3_i721 + c3_i718] * c3_qe_B[c3_i722 + c3_i719];
        c3_i721 = c3_i721 + 3;
      }

      c3_i719 = c3_i719 + 3;
    }
  }

  c3_i723 = 0;
  c3_i724 = 0;
  for (c3_i725 = 0; c3_i725 < 3; c3_i725 = c3_i725 + 1) {
    for (c3_i726 = 0; c3_i726 < 3; c3_i726 = c3_i726 + 1) {
      c3_M3[c3_i726 + c3_i723] = c3_eb_y[c3_i726 + c3_i724];
    }

    c3_i723 = c3_i723 + 6;
    c3_i724 = c3_i724 + 3;
  }

  c3_i727 = 0;
  c3_i728 = 0;
  for (c3_i729 = 0; c3_i729 < 3; c3_i729 = c3_i729 + 1) {
    for (c3_i730 = 0; c3_i730 < 3; c3_i730 = c3_i730 + 1) {
      c3_M3[(c3_i730 + c3_i727) + 18] = c3_fb_y[c3_i730 + c3_i728];
    }

    c3_i727 = c3_i727 + 6;
    c3_i728 = c3_i728 + 3;
  }

  c3_i731 = 0;
  c3_i732 = 0;
  for (c3_i733 = 0; c3_i733 < 3; c3_i733 = c3_i733 + 1) {
    for (c3_i734 = 0; c3_i734 < 3; c3_i734 = c3_i734 + 1) {
      c3_M3[(c3_i734 + c3_i731) + 3] = c3_gb_y[c3_i734 + c3_i732];
    }

    c3_i731 = c3_i731 + 6;
    c3_i732 = c3_i732 + 3;
  }

  c3_i735 = 0;
  c3_i736 = 0;
  for (c3_i737 = 0; c3_i737 < 3; c3_i737 = c3_i737 + 1) {
    for (c3_i738 = 0; c3_i738 < 3; c3_i738 = c3_i738 + 1) {
      c3_M3[(c3_i738 + c3_i735) + 21] = c3_I3[c3_i738 + c3_i736] -
        c3_ib_y[c3_i738 + c3_i736];
    }

    c3_i735 = c3_i735 + 6;
    c3_i736 = c3_i736 + 3;
  }

  _SFD_SCRIPT_CALL(0, 116);
  c3_bc_a = c3_m4;
  for (c3_i739 = 0; c3_i739 < 9; c3_i739 = c3_i739 + 1) {
    c3_jb_y[c3_i739] = c3_bc_a * c3_dv49[c3_i739];
  }

  c3_cc_a = -c3_m4;
  for (c3_i740 = 0; c3_i740 < 3; c3_i740 = c3_i740 + 1) {
    c3_c_r4[c3_i740] = c3_b_r4[c3_i740];
  }

  c3_hat(chartInstance, c3_c_r4, c3_xb_b);
  for (c3_i741 = 0; c3_i741 < 9; c3_i741 = c3_i741 + 1) {
    c3_kb_y[c3_i741] = c3_cc_a * c3_xb_b[c3_i741];
  }

  c3_dc_a = c3_m4;
  for (c3_i742 = 0; c3_i742 < 3; c3_i742 = c3_i742 + 1) {
    c3_d_r4[c3_i742] = c3_b_r4[c3_i742];
  }

  c3_hat(chartInstance, c3_d_r4, c3_yb_b);
  for (c3_i743 = 0; c3_i743 < 9; c3_i743 = c3_i743 + 1) {
    c3_lb_y[c3_i743] = c3_dc_a * c3_yb_b[c3_i743];
  }

  c3_ec_a = c3_m4;
  for (c3_i744 = 0; c3_i744 < 3; c3_i744 = c3_i744 + 1) {
    c3_e_r4[c3_i744] = c3_b_r4[c3_i744];
  }

  c3_hat(chartInstance, c3_e_r4, c3_ac_b);
  for (c3_i745 = 0; c3_i745 < 9; c3_i745 = c3_i745 + 1) {
    c3_mb_y[c3_i745] = c3_ec_a * c3_ac_b[c3_i745];
  }

  for (c3_i746 = 0; c3_i746 < 9; c3_i746 = c3_i746 + 1) {
    c3_fc_a[c3_i746] = c3_mb_y[c3_i746];
  }

  for (c3_i747 = 0; c3_i747 < 3; c3_i747 = c3_i747 + 1) {
    c3_f_r4[c3_i747] = c3_b_r4[c3_i747];
  }

  c3_hat(chartInstance, c3_f_r4, c3_bc_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i748 = 0; c3_i748 < 9; c3_i748 = c3_i748 + 1) {
    c3_re_A[c3_i748] = c3_fc_a[c3_i748];
  }

  for (c3_i749 = 0; c3_i749 < 9; c3_i749 = c3_i749 + 1) {
    c3_re_B[c3_i749] = c3_bc_b[c3_i749];
  }

  for (c3_i750 = 0; c3_i750 < 9; c3_i750 = c3_i750 + 1) {
    c3_se_A[c3_i750] = c3_re_A[c3_i750];
  }

  for (c3_i751 = 0; c3_i751 < 9; c3_i751 = c3_i751 + 1) {
    c3_se_B[c3_i751] = c3_re_B[c3_i751];
  }

  for (c3_i752 = 0; c3_i752 < 9; c3_i752 = c3_i752 + 1) {
    c3_te_A[c3_i752] = c3_se_A[c3_i752];
  }

  for (c3_i753 = 0; c3_i753 < 9; c3_i753 = c3_i753 + 1) {
    c3_te_B[c3_i753] = c3_se_B[c3_i753];
  }

  for (c3_i754 = 0; c3_i754 < 3; c3_i754 = c3_i754 + 1) {
    c3_i755 = 0;
    for (c3_i756 = 0; c3_i756 < 3; c3_i756 = c3_i756 + 1) {
      c3_nb_y[c3_i755 + c3_i754] = 0.0;
      c3_i757 = 0;
      for (c3_i758 = 0; c3_i758 < 3; c3_i758 = c3_i758 + 1) {
        c3_nb_y[c3_i755 + c3_i754] = c3_nb_y[c3_i755 + c3_i754] +
          c3_te_A[c3_i757 + c3_i754] * c3_te_B[c3_i758 + c3_i755];
        c3_i757 = c3_i757 + 3;
      }

      c3_i755 = c3_i755 + 3;
    }
  }

  c3_i759 = 0;
  c3_i760 = 0;
  for (c3_i761 = 0; c3_i761 < 3; c3_i761 = c3_i761 + 1) {
    for (c3_i762 = 0; c3_i762 < 3; c3_i762 = c3_i762 + 1) {
      c3_M4[c3_i762 + c3_i759] = c3_jb_y[c3_i762 + c3_i760];
    }

    c3_i759 = c3_i759 + 6;
    c3_i760 = c3_i760 + 3;
  }

  c3_i763 = 0;
  c3_i764 = 0;
  for (c3_i765 = 0; c3_i765 < 3; c3_i765 = c3_i765 + 1) {
    for (c3_i766 = 0; c3_i766 < 3; c3_i766 = c3_i766 + 1) {
      c3_M4[(c3_i766 + c3_i763) + 18] = c3_kb_y[c3_i766 + c3_i764];
    }

    c3_i763 = c3_i763 + 6;
    c3_i764 = c3_i764 + 3;
  }

  c3_i767 = 0;
  c3_i768 = 0;
  for (c3_i769 = 0; c3_i769 < 3; c3_i769 = c3_i769 + 1) {
    for (c3_i770 = 0; c3_i770 < 3; c3_i770 = c3_i770 + 1) {
      c3_M4[(c3_i770 + c3_i767) + 3] = c3_lb_y[c3_i770 + c3_i768];
    }

    c3_i767 = c3_i767 + 6;
    c3_i768 = c3_i768 + 3;
  }

  c3_i771 = 0;
  c3_i772 = 0;
  for (c3_i773 = 0; c3_i773 < 3; c3_i773 = c3_i773 + 1) {
    for (c3_i774 = 0; c3_i774 < 3; c3_i774 = c3_i774 + 1) {
      c3_M4[(c3_i774 + c3_i771) + 21] = c3_I4[c3_i774 + c3_i772] -
        c3_nb_y[c3_i774 + c3_i772];
    }

    c3_i771 = c3_i771 + 6;
    c3_i772 = c3_i772 + 3;
  }

  _SFD_SCRIPT_CALL(0, 119);
  c3_gc_a = c3_m5;
  for (c3_i775 = 0; c3_i775 < 9; c3_i775 = c3_i775 + 1) {
    c3_ob_y[c3_i775] = c3_gc_a * c3_dv49[c3_i775];
  }

  c3_hc_a = -c3_m5;
  for (c3_i776 = 0; c3_i776 < 3; c3_i776 = c3_i776 + 1) {
    c3_c_r5[c3_i776] = c3_b_r5[c3_i776];
  }

  c3_hat(chartInstance, c3_c_r5, c3_cc_b);
  for (c3_i777 = 0; c3_i777 < 9; c3_i777 = c3_i777 + 1) {
    c3_pb_y[c3_i777] = c3_hc_a * c3_cc_b[c3_i777];
  }

  c3_ic_a = c3_m5;
  for (c3_i778 = 0; c3_i778 < 3; c3_i778 = c3_i778 + 1) {
    c3_d_r5[c3_i778] = c3_b_r5[c3_i778];
  }

  c3_hat(chartInstance, c3_d_r5, c3_dc_b);
  for (c3_i779 = 0; c3_i779 < 9; c3_i779 = c3_i779 + 1) {
    c3_qb_y[c3_i779] = c3_ic_a * c3_dc_b[c3_i779];
  }

  c3_jc_a = c3_m5;
  for (c3_i780 = 0; c3_i780 < 3; c3_i780 = c3_i780 + 1) {
    c3_e_r5[c3_i780] = c3_b_r5[c3_i780];
  }

  c3_hat(chartInstance, c3_e_r5, c3_ec_b);
  for (c3_i781 = 0; c3_i781 < 9; c3_i781 = c3_i781 + 1) {
    c3_rb_y[c3_i781] = c3_jc_a * c3_ec_b[c3_i781];
  }

  for (c3_i782 = 0; c3_i782 < 9; c3_i782 = c3_i782 + 1) {
    c3_kc_a[c3_i782] = c3_rb_y[c3_i782];
  }

  for (c3_i783 = 0; c3_i783 < 3; c3_i783 = c3_i783 + 1) {
    c3_f_r5[c3_i783] = c3_b_r5[c3_i783];
  }

  c3_hat(chartInstance, c3_f_r5, c3_fc_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i784 = 0; c3_i784 < 9; c3_i784 = c3_i784 + 1) {
    c3_ue_A[c3_i784] = c3_kc_a[c3_i784];
  }

  for (c3_i785 = 0; c3_i785 < 9; c3_i785 = c3_i785 + 1) {
    c3_ue_B[c3_i785] = c3_fc_b[c3_i785];
  }

  for (c3_i786 = 0; c3_i786 < 9; c3_i786 = c3_i786 + 1) {
    c3_ve_A[c3_i786] = c3_ue_A[c3_i786];
  }

  for (c3_i787 = 0; c3_i787 < 9; c3_i787 = c3_i787 + 1) {
    c3_ve_B[c3_i787] = c3_ue_B[c3_i787];
  }

  for (c3_i788 = 0; c3_i788 < 9; c3_i788 = c3_i788 + 1) {
    c3_we_A[c3_i788] = c3_ve_A[c3_i788];
  }

  for (c3_i789 = 0; c3_i789 < 9; c3_i789 = c3_i789 + 1) {
    c3_we_B[c3_i789] = c3_ve_B[c3_i789];
  }

  for (c3_i790 = 0; c3_i790 < 3; c3_i790 = c3_i790 + 1) {
    c3_i791 = 0;
    for (c3_i792 = 0; c3_i792 < 3; c3_i792 = c3_i792 + 1) {
      c3_sb_y[c3_i791 + c3_i790] = 0.0;
      c3_i793 = 0;
      for (c3_i794 = 0; c3_i794 < 3; c3_i794 = c3_i794 + 1) {
        c3_sb_y[c3_i791 + c3_i790] = c3_sb_y[c3_i791 + c3_i790] +
          c3_we_A[c3_i793 + c3_i790] * c3_we_B[c3_i794 + c3_i791];
        c3_i793 = c3_i793 + 3;
      }

      c3_i791 = c3_i791 + 3;
    }
  }

  c3_i795 = 0;
  c3_i796 = 0;
  for (c3_i797 = 0; c3_i797 < 3; c3_i797 = c3_i797 + 1) {
    for (c3_i798 = 0; c3_i798 < 3; c3_i798 = c3_i798 + 1) {
      c3_M5[c3_i798 + c3_i795] = c3_ob_y[c3_i798 + c3_i796];
    }

    c3_i795 = c3_i795 + 6;
    c3_i796 = c3_i796 + 3;
  }

  c3_i799 = 0;
  c3_i800 = 0;
  for (c3_i801 = 0; c3_i801 < 3; c3_i801 = c3_i801 + 1) {
    for (c3_i802 = 0; c3_i802 < 3; c3_i802 = c3_i802 + 1) {
      c3_M5[(c3_i802 + c3_i799) + 18] = c3_pb_y[c3_i802 + c3_i800];
    }

    c3_i799 = c3_i799 + 6;
    c3_i800 = c3_i800 + 3;
  }

  c3_i803 = 0;
  c3_i804 = 0;
  for (c3_i805 = 0; c3_i805 < 3; c3_i805 = c3_i805 + 1) {
    for (c3_i806 = 0; c3_i806 < 3; c3_i806 = c3_i806 + 1) {
      c3_M5[(c3_i806 + c3_i803) + 3] = c3_qb_y[c3_i806 + c3_i804];
    }

    c3_i803 = c3_i803 + 6;
    c3_i804 = c3_i804 + 3;
  }

  c3_i807 = 0;
  c3_i808 = 0;
  for (c3_i809 = 0; c3_i809 < 3; c3_i809 = c3_i809 + 1) {
    for (c3_i810 = 0; c3_i810 < 3; c3_i810 = c3_i810 + 1) {
      c3_M5[(c3_i810 + c3_i807) + 21] = c3_I5[c3_i810 + c3_i808] -
        c3_sb_y[c3_i810 + c3_i808];
    }

    c3_i807 = c3_i807 + 6;
    c3_i808 = c3_i808 + 3;
  }

  _SFD_SCRIPT_CALL(0, 122);
  c3_lc_a = c3_m6;
  for (c3_i811 = 0; c3_i811 < 9; c3_i811 = c3_i811 + 1) {
    c3_tb_y[c3_i811] = c3_lc_a * c3_dv49[c3_i811];
  }

  c3_mc_a = -c3_m6;
  for (c3_i812 = 0; c3_i812 < 3; c3_i812 = c3_i812 + 1) {
    c3_c_r6[c3_i812] = c3_b_r6[c3_i812];
  }

  c3_hat(chartInstance, c3_c_r6, c3_gc_b);
  for (c3_i813 = 0; c3_i813 < 9; c3_i813 = c3_i813 + 1) {
    c3_ub_y[c3_i813] = c3_mc_a * c3_gc_b[c3_i813];
  }

  c3_nc_a = c3_m6;
  for (c3_i814 = 0; c3_i814 < 3; c3_i814 = c3_i814 + 1) {
    c3_d_r6[c3_i814] = c3_b_r6[c3_i814];
  }

  c3_hat(chartInstance, c3_d_r6, c3_hc_b);
  for (c3_i815 = 0; c3_i815 < 9; c3_i815 = c3_i815 + 1) {
    c3_vb_y[c3_i815] = c3_nc_a * c3_hc_b[c3_i815];
  }

  c3_oc_a = c3_m6;
  for (c3_i816 = 0; c3_i816 < 3; c3_i816 = c3_i816 + 1) {
    c3_e_r6[c3_i816] = c3_b_r6[c3_i816];
  }

  c3_hat(chartInstance, c3_e_r6, c3_ic_b);
  for (c3_i817 = 0; c3_i817 < 9; c3_i817 = c3_i817 + 1) {
    c3_wb_y[c3_i817] = c3_oc_a * c3_ic_b[c3_i817];
  }

  for (c3_i818 = 0; c3_i818 < 9; c3_i818 = c3_i818 + 1) {
    c3_pc_a[c3_i818] = c3_wb_y[c3_i818];
  }

  for (c3_i819 = 0; c3_i819 < 3; c3_i819 = c3_i819 + 1) {
    c3_f_r6[c3_i819] = c3_b_r6[c3_i819];
  }

  c3_hat(chartInstance, c3_f_r6, c3_jc_b);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i820 = 0; c3_i820 < 9; c3_i820 = c3_i820 + 1) {
    c3_xe_A[c3_i820] = c3_pc_a[c3_i820];
  }

  for (c3_i821 = 0; c3_i821 < 9; c3_i821 = c3_i821 + 1) {
    c3_xe_B[c3_i821] = c3_jc_b[c3_i821];
  }

  for (c3_i822 = 0; c3_i822 < 9; c3_i822 = c3_i822 + 1) {
    c3_ye_A[c3_i822] = c3_xe_A[c3_i822];
  }

  for (c3_i823 = 0; c3_i823 < 9; c3_i823 = c3_i823 + 1) {
    c3_ye_B[c3_i823] = c3_xe_B[c3_i823];
  }

  for (c3_i824 = 0; c3_i824 < 9; c3_i824 = c3_i824 + 1) {
    c3_af_A[c3_i824] = c3_ye_A[c3_i824];
  }

  for (c3_i825 = 0; c3_i825 < 9; c3_i825 = c3_i825 + 1) {
    c3_af_B[c3_i825] = c3_ye_B[c3_i825];
  }

  for (c3_i826 = 0; c3_i826 < 3; c3_i826 = c3_i826 + 1) {
    c3_i827 = 0;
    for (c3_i828 = 0; c3_i828 < 3; c3_i828 = c3_i828 + 1) {
      c3_xb_y[c3_i827 + c3_i826] = 0.0;
      c3_i829 = 0;
      for (c3_i830 = 0; c3_i830 < 3; c3_i830 = c3_i830 + 1) {
        c3_xb_y[c3_i827 + c3_i826] = c3_xb_y[c3_i827 + c3_i826] +
          c3_af_A[c3_i829 + c3_i826] * c3_af_B[c3_i830 + c3_i827];
        c3_i829 = c3_i829 + 3;
      }

      c3_i827 = c3_i827 + 3;
    }
  }

  c3_i831 = 0;
  c3_i832 = 0;
  for (c3_i833 = 0; c3_i833 < 3; c3_i833 = c3_i833 + 1) {
    for (c3_i834 = 0; c3_i834 < 3; c3_i834 = c3_i834 + 1) {
      c3_M6[c3_i834 + c3_i831] = c3_tb_y[c3_i834 + c3_i832];
    }

    c3_i831 = c3_i831 + 6;
    c3_i832 = c3_i832 + 3;
  }

  c3_i835 = 0;
  c3_i836 = 0;
  for (c3_i837 = 0; c3_i837 < 3; c3_i837 = c3_i837 + 1) {
    for (c3_i838 = 0; c3_i838 < 3; c3_i838 = c3_i838 + 1) {
      c3_M6[(c3_i838 + c3_i835) + 18] = c3_ub_y[c3_i838 + c3_i836];
    }

    c3_i835 = c3_i835 + 6;
    c3_i836 = c3_i836 + 3;
  }

  c3_i839 = 0;
  c3_i840 = 0;
  for (c3_i841 = 0; c3_i841 < 3; c3_i841 = c3_i841 + 1) {
    for (c3_i842 = 0; c3_i842 < 3; c3_i842 = c3_i842 + 1) {
      c3_M6[(c3_i842 + c3_i839) + 3] = c3_vb_y[c3_i842 + c3_i840];
    }

    c3_i839 = c3_i839 + 6;
    c3_i840 = c3_i840 + 3;
  }

  c3_i843 = 0;
  c3_i844 = 0;
  for (c3_i845 = 0; c3_i845 < 3; c3_i845 = c3_i845 + 1) {
    for (c3_i846 = 0; c3_i846 < 3; c3_i846 = c3_i846 + 1) {
      c3_M6[(c3_i846 + c3_i843) + 21] = c3_I6[c3_i846 + c3_i844] -
        c3_xb_y[c3_i846 + c3_i844];
    }

    c3_i843 = c3_i843 + 6;
    c3_i844 = c3_i844 + 3;
  }

  /*  %% Forward Recursion (kinematic) */
  /*  Initial State */
  _SFD_SCRIPT_CALL(0, 127);
  for (c3_i847 = 0; c3_i847 < 6; c3_i847 = c3_i847 + 1) {
    c3_V0[c3_i847] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 128);
  for (c3_i848 = 0; c3_i848 < 6; c3_i848 = c3_i848 + 1) {
    c3_dV0[c3_i848] = c3_dv50[c3_i848];
  }

  /*  Joint 1: */
  _SFD_SCRIPT_CALL(0, 131);
  for (c3_i849 = 0; c3_i849 < 16; c3_i849 = c3_i849 + 1) {
    c3_qc_a[c3_i849] = c3_g01_0[c3_i849];
  }

  for (c3_i850 = 0; c3_i850 < 6; c3_i850 = c3_i850 + 1) {
    c3_dv51[c3_i850] = c3_dv10[c3_i850];
  }

  c3_expg(chartInstance, c3_dv51, c3_Pos[0], c3_kc_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i851 = 0; c3_i851 < 16; c3_i851 = c3_i851 + 1) {
    c3_bf_A[c3_i851] = c3_qc_a[c3_i851];
  }

  for (c3_i852 = 0; c3_i852 < 16; c3_i852 = c3_i852 + 1) {
    c3_bf_B[c3_i852] = c3_kc_b[c3_i852];
  }

  for (c3_i853 = 0; c3_i853 < 16; c3_i853 = c3_i853 + 1) {
    c3_g01[c3_i853] = 0.0;
  }

  for (c3_i854 = 0; c3_i854 < 16; c3_i854 = c3_i854 + 1) {
    c3_cf_A[c3_i854] = c3_bf_A[c3_i854];
  }

  for (c3_i855 = 0; c3_i855 < 16; c3_i855 = c3_i855 + 1) {
    c3_cf_B[c3_i855] = c3_bf_B[c3_i855];
  }

  for (c3_i856 = 0; c3_i856 < 16; c3_i856 = c3_i856 + 1) {
    c3_df_A[c3_i856] = c3_cf_A[c3_i856];
  }

  for (c3_i857 = 0; c3_i857 < 16; c3_i857 = c3_i857 + 1) {
    c3_df_B[c3_i857] = c3_cf_B[c3_i857];
  }

  for (c3_i858 = 0; c3_i858 < 4; c3_i858 = c3_i858 + 1) {
    c3_i859 = 0;
    for (c3_i860 = 0; c3_i860 < 4; c3_i860 = c3_i860 + 1) {
      c3_g01[c3_i859 + c3_i858] = 0.0;
      c3_i861 = 0;
      for (c3_i862 = 0; c3_i862 < 4; c3_i862 = c3_i862 + 1) {
        c3_g01[c3_i859 + c3_i858] = c3_g01[c3_i859 + c3_i858] + c3_df_A[c3_i861
          + c3_i858] * c3_df_B[c3_i862 + c3_i859];
        c3_i861 = c3_i861 + 4;
      }

      c3_i859 = c3_i859 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 132);
  for (c3_i863 = 0; c3_i863 < 16; c3_i863 = c3_i863 + 1) {
    c3_b_g01[c3_i863] = c3_g01[c3_i863];
  }

  for (c3_i864 = 0; c3_i864 < 16; c3_i864 = c3_i864 + 1) {
    c3_dv53[c3_i864] = c3_dv52[c3_i864];
  }

  c3_b_mldivide(chartInstance, c3_b_g01, c3_dv53, c3_dv54);
  for (c3_i865 = 0; c3_i865 < 16; c3_i865 = c3_i865 + 1) {
    c3_dv55[c3_i865] = c3_dv54[c3_i865];
  }

  c3_Adj(chartInstance, c3_dv55, c3_dv56);
  for (c3_i866 = 0; c3_i866 < 36; c3_i866 = c3_i866 + 1) {
    c3_Adinvg01[c3_i866] = c3_dv56[c3_i866];
  }

  _SFD_SCRIPT_CALL(0, 133);
  for (c3_i867 = 0; c3_i867 < 36; c3_i867 = c3_i867 + 1) {
    c3_rc_a[c3_i867] = c3_Adinvg01[c3_i867];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i868 = 0; c3_i868 < 36; c3_i868 = c3_i868 + 1) {
    c3_sc_a[c3_i868] = c3_rc_a[c3_i868];
  }

  for (c3_i869 = 0; c3_i869 < 6; c3_i869 = c3_i869 + 1) {
    c3_dv57[c3_i869] = 0.0;
  }

  for (c3_i870 = 0; c3_i870 < 6; c3_i870 = c3_i870 + 1) {
    c3_dv58[c3_i870] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_sc_a, c3_dv57, c3_dv58, c3_yb_y);
  c3_lc_b = c3_Vel[0];
  for (c3_i871 = 0; c3_i871 < 6; c3_i871 = c3_i871 + 1) {
    c3_ac_y[c3_i871] = c3_dv10[c3_i871] * c3_lc_b;
  }

  for (c3_i872 = 0; c3_i872 < 6; c3_i872 = c3_i872 + 1) {
    c3_V1[c3_i872] = c3_yb_y[c3_i872] + c3_ac_y[c3_i872];
  }

  _SFD_SCRIPT_CALL(0, 134);
  c3_mc_b = c3_Acc[0];
  for (c3_i873 = 0; c3_i873 < 6; c3_i873 = c3_i873 + 1) {
    c3_bc_y[c3_i873] = c3_dv10[c3_i873] * c3_mc_b;
  }

  for (c3_i874 = 0; c3_i874 < 36; c3_i874 = c3_i874 + 1) {
    c3_tc_a[c3_i874] = c3_Adinvg01[c3_i874];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i875 = 0; c3_i875 < 36; c3_i875 = c3_i875 + 1) {
    c3_uc_a[c3_i875] = c3_tc_a[c3_i875];
  }

  for (c3_i876 = 0; c3_i876 < 6; c3_i876 = c3_i876 + 1) {
    c3_dv59[c3_i876] = c3_dv50[c3_i876];
  }

  for (c3_i877 = 0; c3_i877 < 6; c3_i877 = c3_i877 + 1) {
    c3_dv60[c3_i877] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_uc_a, c3_dv59, c3_dv60, c3_cc_y);
  c3_nc_b = c3_Vel[0];
  for (c3_i878 = 0; c3_i878 < 6; c3_i878 = c3_i878 + 1) {
    c3_dc_y[c3_i878] = c3_dv10[c3_i878] * c3_nc_b;
  }

  for (c3_i879 = 0; c3_i879 < 36; c3_i879 = c3_i879 + 1) {
    c3_vc_a[c3_i879] = c3_Adinvg01[c3_i879];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i880 = 0; c3_i880 < 36; c3_i880 = c3_i880 + 1) {
    c3_wc_a[c3_i880] = c3_vc_a[c3_i880];
  }

  for (c3_i881 = 0; c3_i881 < 6; c3_i881 = c3_i881 + 1) {
    c3_dv61[c3_i881] = 0.0;
  }

  for (c3_i882 = 0; c3_i882 < 6; c3_i882 = c3_i882 + 1) {
    c3_dv62[c3_i882] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_wc_a, c3_dv61, c3_dv62, c3_ec_y);
  for (c3_i883 = 0; c3_i883 < 6; c3_i883 = c3_i883 + 1) {
    c3_fc_y[c3_i883] = c3_dc_y[c3_i883];
  }

  c3_ad(chartInstance, c3_fc_y, c3_xc_a);
  for (c3_i884 = 0; c3_i884 < 6; c3_i884 = c3_i884 + 1) {
    c3_oc_b[c3_i884] = c3_ec_y[c3_i884];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i885 = 0; c3_i885 < 36; c3_i885 = c3_i885 + 1) {
    c3_yc_a[c3_i885] = c3_xc_a[c3_i885];
  }

  for (c3_i886 = 0; c3_i886 < 6; c3_i886 = c3_i886 + 1) {
    c3_pc_b[c3_i886] = c3_oc_b[c3_i886];
  }

  for (c3_i887 = 0; c3_i887 < 6; c3_i887 = c3_i887 + 1) {
    c3_dv63[c3_i887] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_yc_a, c3_pc_b, c3_dv63, c3_gc_y);
  for (c3_i888 = 0; c3_i888 < 6; c3_i888 = c3_i888 + 1) {
    c3_dV1[c3_i888] = (c3_bc_y[c3_i888] + c3_cc_y[c3_i888]) - c3_gc_y[c3_i888];
  }

  /*  dV1 = kxi1*Acc(1) + Adinvg01 * dV0; */
  /*  dV1(1:3) = dV1(1:3) + g01(1:3,1:3)'*cross(V0(4:6),cross(V0(4:6),g01(1:3,4))); */
  /*  dV1(4:6) = dV1(4:6) + g01(1:3,1:3)'*Vel(1)*cross(V0(4:6),g01(1:3,1:3)*kxi1(4:6)); */
  /* JntVel(1) =[0;0;0;0;0;1]'*(Adj(g01)*V1); */
  _SFD_SCRIPT_CALL(0, 140);
  for (c3_i889 = 0; c3_i889 < 6; c3_i889 = c3_i889 + 1) {
    c3_JntVel[c3_i889] = c3_V1[c3_i889];
  }

  _SFD_SCRIPT_CALL(0, 141);
  for (c3_i890 = 0; c3_i890 < 6; c3_i890 = c3_i890 + 1) {
    c3_JntAcc[c3_i890] = c3_dV1[c3_i890];
  }

  /*  Joint 2: */
  _SFD_SCRIPT_CALL(0, 145);
  for (c3_i891 = 0; c3_i891 < 16; c3_i891 = c3_i891 + 1) {
    c3_ad_a[c3_i891] = c3_g12_0[c3_i891];
  }

  for (c3_i892 = 0; c3_i892 < 6; c3_i892 = c3_i892 + 1) {
    c3_dv64[c3_i892] = c3_dv10[c3_i892];
  }

  c3_expg(chartInstance, c3_dv64, c3_Pos[1], c3_qc_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i893 = 0; c3_i893 < 16; c3_i893 = c3_i893 + 1) {
    c3_ef_A[c3_i893] = c3_ad_a[c3_i893];
  }

  for (c3_i894 = 0; c3_i894 < 16; c3_i894 = c3_i894 + 1) {
    c3_ef_B[c3_i894] = c3_qc_b[c3_i894];
  }

  for (c3_i895 = 0; c3_i895 < 16; c3_i895 = c3_i895 + 1) {
    c3_g12[c3_i895] = 0.0;
  }

  for (c3_i896 = 0; c3_i896 < 16; c3_i896 = c3_i896 + 1) {
    c3_ff_A[c3_i896] = c3_ef_A[c3_i896];
  }

  for (c3_i897 = 0; c3_i897 < 16; c3_i897 = c3_i897 + 1) {
    c3_ff_B[c3_i897] = c3_ef_B[c3_i897];
  }

  for (c3_i898 = 0; c3_i898 < 16; c3_i898 = c3_i898 + 1) {
    c3_gf_A[c3_i898] = c3_ff_A[c3_i898];
  }

  for (c3_i899 = 0; c3_i899 < 16; c3_i899 = c3_i899 + 1) {
    c3_gf_B[c3_i899] = c3_ff_B[c3_i899];
  }

  for (c3_i900 = 0; c3_i900 < 4; c3_i900 = c3_i900 + 1) {
    c3_i901 = 0;
    for (c3_i902 = 0; c3_i902 < 4; c3_i902 = c3_i902 + 1) {
      c3_g12[c3_i901 + c3_i900] = 0.0;
      c3_i903 = 0;
      for (c3_i904 = 0; c3_i904 < 4; c3_i904 = c3_i904 + 1) {
        c3_g12[c3_i901 + c3_i900] = c3_g12[c3_i901 + c3_i900] + c3_gf_A[c3_i903
          + c3_i900] * c3_gf_B[c3_i904 + c3_i901];
        c3_i903 = c3_i903 + 4;
      }

      c3_i901 = c3_i901 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 146);
  for (c3_i905 = 0; c3_i905 < 16; c3_i905 = c3_i905 + 1) {
    c3_b_g12[c3_i905] = c3_g12[c3_i905];
  }

  for (c3_i906 = 0; c3_i906 < 16; c3_i906 = c3_i906 + 1) {
    c3_dv65[c3_i906] = c3_dv52[c3_i906];
  }

  c3_b_mldivide(chartInstance, c3_b_g12, c3_dv65, c3_dv66);
  for (c3_i907 = 0; c3_i907 < 16; c3_i907 = c3_i907 + 1) {
    c3_dv67[c3_i907] = c3_dv66[c3_i907];
  }

  c3_Adj(chartInstance, c3_dv67, c3_dv68);
  for (c3_i908 = 0; c3_i908 < 36; c3_i908 = c3_i908 + 1) {
    c3_Adinvg12[c3_i908] = c3_dv68[c3_i908];
  }

  _SFD_SCRIPT_CALL(0, 147);
  for (c3_i909 = 0; c3_i909 < 36; c3_i909 = c3_i909 + 1) {
    c3_bd_a[c3_i909] = c3_Adinvg12[c3_i909];
  }

  for (c3_i910 = 0; c3_i910 < 6; c3_i910 = c3_i910 + 1) {
    c3_rc_b[c3_i910] = c3_V1[c3_i910];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i911 = 0; c3_i911 < 36; c3_i911 = c3_i911 + 1) {
    c3_cd_a[c3_i911] = c3_bd_a[c3_i911];
  }

  for (c3_i912 = 0; c3_i912 < 6; c3_i912 = c3_i912 + 1) {
    c3_sc_b[c3_i912] = c3_rc_b[c3_i912];
  }

  for (c3_i913 = 0; c3_i913 < 6; c3_i913 = c3_i913 + 1) {
    c3_dv69[c3_i913] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_cd_a, c3_sc_b, c3_dv69, c3_hc_y);
  c3_tc_b = c3_Vel[1];
  for (c3_i914 = 0; c3_i914 < 6; c3_i914 = c3_i914 + 1) {
    c3_ic_y[c3_i914] = c3_dv10[c3_i914] * c3_tc_b;
  }

  for (c3_i915 = 0; c3_i915 < 6; c3_i915 = c3_i915 + 1) {
    c3_V2[c3_i915] = c3_hc_y[c3_i915] + c3_ic_y[c3_i915];
  }

  _SFD_SCRIPT_CALL(0, 148);
  c3_uc_b = c3_Acc[1];
  for (c3_i916 = 0; c3_i916 < 6; c3_i916 = c3_i916 + 1) {
    c3_jc_y[c3_i916] = c3_dv10[c3_i916] * c3_uc_b;
  }

  for (c3_i917 = 0; c3_i917 < 36; c3_i917 = c3_i917 + 1) {
    c3_dd_a[c3_i917] = c3_Adinvg12[c3_i917];
  }

  for (c3_i918 = 0; c3_i918 < 6; c3_i918 = c3_i918 + 1) {
    c3_vc_b[c3_i918] = c3_dV1[c3_i918];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i919 = 0; c3_i919 < 36; c3_i919 = c3_i919 + 1) {
    c3_ed_a[c3_i919] = c3_dd_a[c3_i919];
  }

  for (c3_i920 = 0; c3_i920 < 6; c3_i920 = c3_i920 + 1) {
    c3_wc_b[c3_i920] = c3_vc_b[c3_i920];
  }

  for (c3_i921 = 0; c3_i921 < 6; c3_i921 = c3_i921 + 1) {
    c3_dv70[c3_i921] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ed_a, c3_wc_b, c3_dv70, c3_kc_y);
  c3_xc_b = c3_Vel[1];
  for (c3_i922 = 0; c3_i922 < 6; c3_i922 = c3_i922 + 1) {
    c3_lc_y[c3_i922] = c3_dv10[c3_i922] * c3_xc_b;
  }

  for (c3_i923 = 0; c3_i923 < 36; c3_i923 = c3_i923 + 1) {
    c3_fd_a[c3_i923] = c3_Adinvg12[c3_i923];
  }

  for (c3_i924 = 0; c3_i924 < 6; c3_i924 = c3_i924 + 1) {
    c3_yc_b[c3_i924] = c3_V1[c3_i924];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i925 = 0; c3_i925 < 36; c3_i925 = c3_i925 + 1) {
    c3_gd_a[c3_i925] = c3_fd_a[c3_i925];
  }

  for (c3_i926 = 0; c3_i926 < 6; c3_i926 = c3_i926 + 1) {
    c3_ad_b[c3_i926] = c3_yc_b[c3_i926];
  }

  for (c3_i927 = 0; c3_i927 < 6; c3_i927 = c3_i927 + 1) {
    c3_dv71[c3_i927] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_gd_a, c3_ad_b, c3_dv71, c3_mc_y);
  for (c3_i928 = 0; c3_i928 < 6; c3_i928 = c3_i928 + 1) {
    c3_nc_y[c3_i928] = c3_lc_y[c3_i928];
  }

  c3_ad(chartInstance, c3_nc_y, c3_hd_a);
  for (c3_i929 = 0; c3_i929 < 6; c3_i929 = c3_i929 + 1) {
    c3_bd_b[c3_i929] = c3_mc_y[c3_i929];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i930 = 0; c3_i930 < 36; c3_i930 = c3_i930 + 1) {
    c3_id_a[c3_i930] = c3_hd_a[c3_i930];
  }

  for (c3_i931 = 0; c3_i931 < 6; c3_i931 = c3_i931 + 1) {
    c3_cd_b[c3_i931] = c3_bd_b[c3_i931];
  }

  for (c3_i932 = 0; c3_i932 < 6; c3_i932 = c3_i932 + 1) {
    c3_dv72[c3_i932] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_id_a, c3_cd_b, c3_dv72, c3_oc_y);
  for (c3_i933 = 0; c3_i933 < 6; c3_i933 = c3_i933 + 1) {
    c3_dV2[c3_i933] = (c3_jc_y[c3_i933] + c3_kc_y[c3_i933]) - c3_oc_y[c3_i933];
  }

  /*  dV2 = kxi2*Acc(2) + Adinvg12 * dV1; */
  /*  dV2(1:3) = dV2(1:3) + g12(1:3,1:3)'*cross(V1(4:6),cross(V1(4:6),g12(1:3,4))); */
  /*  dV2(4:6) = dV2(4:6) + g12(1:3,1:3)'*Vel(2)*cross(V1(4:6),g12(1:3,1:3)*kxi2(4:6)); */
  /* JntVel(2) = [0;0;0;0;1;0]'*(Adj(g01*g12)*V2); */
  _SFD_SCRIPT_CALL(0, 155);
  for (c3_i934 = 0; c3_i934 < 6; c3_i934 = c3_i934 + 1) {
    c3_JntVel[c3_i934 + 6] = c3_V2[c3_i934];
  }

  _SFD_SCRIPT_CALL(0, 156);
  for (c3_i935 = 0; c3_i935 < 6; c3_i935 = c3_i935 + 1) {
    c3_JntAcc[c3_i935 + 6] = c3_dV2[c3_i935];
  }

  /*  Joint 3: */
  _SFD_SCRIPT_CALL(0, 159);
  for (c3_i936 = 0; c3_i936 < 16; c3_i936 = c3_i936 + 1) {
    c3_jd_a[c3_i936] = c3_g23_0[c3_i936];
  }

  for (c3_i937 = 0; c3_i937 < 6; c3_i937 = c3_i937 + 1) {
    c3_dv73[c3_i937] = c3_dv10[c3_i937];
  }

  c3_expg(chartInstance, c3_dv73, c3_Pos[2], c3_dd_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i938 = 0; c3_i938 < 16; c3_i938 = c3_i938 + 1) {
    c3_hf_A[c3_i938] = c3_jd_a[c3_i938];
  }

  for (c3_i939 = 0; c3_i939 < 16; c3_i939 = c3_i939 + 1) {
    c3_hf_B[c3_i939] = c3_dd_b[c3_i939];
  }

  for (c3_i940 = 0; c3_i940 < 16; c3_i940 = c3_i940 + 1) {
    c3_g23[c3_i940] = 0.0;
  }

  for (c3_i941 = 0; c3_i941 < 16; c3_i941 = c3_i941 + 1) {
    c3_if_A[c3_i941] = c3_hf_A[c3_i941];
  }

  for (c3_i942 = 0; c3_i942 < 16; c3_i942 = c3_i942 + 1) {
    c3_if_B[c3_i942] = c3_hf_B[c3_i942];
  }

  for (c3_i943 = 0; c3_i943 < 16; c3_i943 = c3_i943 + 1) {
    c3_jf_A[c3_i943] = c3_if_A[c3_i943];
  }

  for (c3_i944 = 0; c3_i944 < 16; c3_i944 = c3_i944 + 1) {
    c3_jf_B[c3_i944] = c3_if_B[c3_i944];
  }

  for (c3_i945 = 0; c3_i945 < 4; c3_i945 = c3_i945 + 1) {
    c3_i946 = 0;
    for (c3_i947 = 0; c3_i947 < 4; c3_i947 = c3_i947 + 1) {
      c3_g23[c3_i946 + c3_i945] = 0.0;
      c3_i948 = 0;
      for (c3_i949 = 0; c3_i949 < 4; c3_i949 = c3_i949 + 1) {
        c3_g23[c3_i946 + c3_i945] = c3_g23[c3_i946 + c3_i945] + c3_jf_A[c3_i948
          + c3_i945] * c3_jf_B[c3_i949 + c3_i946];
        c3_i948 = c3_i948 + 4;
      }

      c3_i946 = c3_i946 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 160);
  for (c3_i950 = 0; c3_i950 < 16; c3_i950 = c3_i950 + 1) {
    c3_b_g23[c3_i950] = c3_g23[c3_i950];
  }

  for (c3_i951 = 0; c3_i951 < 16; c3_i951 = c3_i951 + 1) {
    c3_dv74[c3_i951] = c3_dv52[c3_i951];
  }

  c3_b_mldivide(chartInstance, c3_b_g23, c3_dv74, c3_dv75);
  for (c3_i952 = 0; c3_i952 < 16; c3_i952 = c3_i952 + 1) {
    c3_dv76[c3_i952] = c3_dv75[c3_i952];
  }

  c3_Adj(chartInstance, c3_dv76, c3_dv77);
  for (c3_i953 = 0; c3_i953 < 36; c3_i953 = c3_i953 + 1) {
    c3_Adinvg23[c3_i953] = c3_dv77[c3_i953];
  }

  _SFD_SCRIPT_CALL(0, 161);
  for (c3_i954 = 0; c3_i954 < 36; c3_i954 = c3_i954 + 1) {
    c3_kd_a[c3_i954] = c3_Adinvg23[c3_i954];
  }

  for (c3_i955 = 0; c3_i955 < 6; c3_i955 = c3_i955 + 1) {
    c3_ed_b[c3_i955] = c3_V2[c3_i955];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i956 = 0; c3_i956 < 36; c3_i956 = c3_i956 + 1) {
    c3_ld_a[c3_i956] = c3_kd_a[c3_i956];
  }

  for (c3_i957 = 0; c3_i957 < 6; c3_i957 = c3_i957 + 1) {
    c3_fd_b[c3_i957] = c3_ed_b[c3_i957];
  }

  for (c3_i958 = 0; c3_i958 < 6; c3_i958 = c3_i958 + 1) {
    c3_dv78[c3_i958] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ld_a, c3_fd_b, c3_dv78, c3_pc_y);
  c3_gd_b = c3_Vel[2];
  for (c3_i959 = 0; c3_i959 < 6; c3_i959 = c3_i959 + 1) {
    c3_qc_y[c3_i959] = c3_dv10[c3_i959] * c3_gd_b;
  }

  for (c3_i960 = 0; c3_i960 < 6; c3_i960 = c3_i960 + 1) {
    c3_V3[c3_i960] = c3_pc_y[c3_i960] + c3_qc_y[c3_i960];
  }

  _SFD_SCRIPT_CALL(0, 162);
  c3_hd_b = c3_Acc[2];
  for (c3_i961 = 0; c3_i961 < 6; c3_i961 = c3_i961 + 1) {
    c3_rc_y[c3_i961] = c3_dv10[c3_i961] * c3_hd_b;
  }

  for (c3_i962 = 0; c3_i962 < 36; c3_i962 = c3_i962 + 1) {
    c3_md_a[c3_i962] = c3_Adinvg23[c3_i962];
  }

  for (c3_i963 = 0; c3_i963 < 6; c3_i963 = c3_i963 + 1) {
    c3_id_b[c3_i963] = c3_dV2[c3_i963];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i964 = 0; c3_i964 < 36; c3_i964 = c3_i964 + 1) {
    c3_nd_a[c3_i964] = c3_md_a[c3_i964];
  }

  for (c3_i965 = 0; c3_i965 < 6; c3_i965 = c3_i965 + 1) {
    c3_jd_b[c3_i965] = c3_id_b[c3_i965];
  }

  for (c3_i966 = 0; c3_i966 < 6; c3_i966 = c3_i966 + 1) {
    c3_dv79[c3_i966] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_nd_a, c3_jd_b, c3_dv79, c3_sc_y);
  c3_kd_b = c3_Vel[2];
  for (c3_i967 = 0; c3_i967 < 6; c3_i967 = c3_i967 + 1) {
    c3_tc_y[c3_i967] = c3_dv10[c3_i967] * c3_kd_b;
  }

  for (c3_i968 = 0; c3_i968 < 36; c3_i968 = c3_i968 + 1) {
    c3_od_a[c3_i968] = c3_Adinvg23[c3_i968];
  }

  for (c3_i969 = 0; c3_i969 < 6; c3_i969 = c3_i969 + 1) {
    c3_ld_b[c3_i969] = c3_V2[c3_i969];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i970 = 0; c3_i970 < 36; c3_i970 = c3_i970 + 1) {
    c3_pd_a[c3_i970] = c3_od_a[c3_i970];
  }

  for (c3_i971 = 0; c3_i971 < 6; c3_i971 = c3_i971 + 1) {
    c3_md_b[c3_i971] = c3_ld_b[c3_i971];
  }

  for (c3_i972 = 0; c3_i972 < 6; c3_i972 = c3_i972 + 1) {
    c3_dv80[c3_i972] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_pd_a, c3_md_b, c3_dv80, c3_uc_y);
  for (c3_i973 = 0; c3_i973 < 6; c3_i973 = c3_i973 + 1) {
    c3_vc_y[c3_i973] = c3_tc_y[c3_i973];
  }

  c3_ad(chartInstance, c3_vc_y, c3_qd_a);
  for (c3_i974 = 0; c3_i974 < 6; c3_i974 = c3_i974 + 1) {
    c3_nd_b[c3_i974] = c3_uc_y[c3_i974];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i975 = 0; c3_i975 < 36; c3_i975 = c3_i975 + 1) {
    c3_rd_a[c3_i975] = c3_qd_a[c3_i975];
  }

  for (c3_i976 = 0; c3_i976 < 6; c3_i976 = c3_i976 + 1) {
    c3_od_b[c3_i976] = c3_nd_b[c3_i976];
  }

  for (c3_i977 = 0; c3_i977 < 6; c3_i977 = c3_i977 + 1) {
    c3_dv81[c3_i977] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_rd_a, c3_od_b, c3_dv81, c3_wc_y);
  for (c3_i978 = 0; c3_i978 < 6; c3_i978 = c3_i978 + 1) {
    c3_dV3[c3_i978] = (c3_rc_y[c3_i978] + c3_sc_y[c3_i978]) - c3_wc_y[c3_i978];
  }

  /*  dV3 = kxi3*Acc(3) + Adinvg23 * dV2; */
  /*  dV3(1:3) = dV3(1:3) + g23(1:3,1:3)'*cross(V2(4:6),cross(V2(4:6),g23(1:3,4))); */
  /*  dV3(4:6) = dV3(4:6) + g23(1:3,1:3)'*Vel(3)*cross(V2(4:6),g23(1:3,1:3)*kxi3(4:6)); */
  /* JntVel(3) = [0;0;0;0;1;0]'*(Adj(g01*g12*g23)*V3); */
  _SFD_SCRIPT_CALL(0, 168);
  for (c3_i979 = 0; c3_i979 < 6; c3_i979 = c3_i979 + 1) {
    c3_JntVel[c3_i979 + 12] = c3_V3[c3_i979];
  }

  _SFD_SCRIPT_CALL(0, 169);
  for (c3_i980 = 0; c3_i980 < 6; c3_i980 = c3_i980 + 1) {
    c3_JntAcc[c3_i980 + 12] = c3_dV3[c3_i980];
  }

  /*  Joint 4: */
  _SFD_SCRIPT_CALL(0, 172);
  for (c3_i981 = 0; c3_i981 < 16; c3_i981 = c3_i981 + 1) {
    c3_sd_a[c3_i981] = c3_g34_0[c3_i981];
  }

  for (c3_i982 = 0; c3_i982 < 6; c3_i982 = c3_i982 + 1) {
    c3_dv82[c3_i982] = c3_dv10[c3_i982];
  }

  c3_expg(chartInstance, c3_dv82, c3_Pos[3], c3_pd_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i983 = 0; c3_i983 < 16; c3_i983 = c3_i983 + 1) {
    c3_kf_A[c3_i983] = c3_sd_a[c3_i983];
  }

  for (c3_i984 = 0; c3_i984 < 16; c3_i984 = c3_i984 + 1) {
    c3_kf_B[c3_i984] = c3_pd_b[c3_i984];
  }

  for (c3_i985 = 0; c3_i985 < 16; c3_i985 = c3_i985 + 1) {
    c3_g34[c3_i985] = 0.0;
  }

  for (c3_i986 = 0; c3_i986 < 16; c3_i986 = c3_i986 + 1) {
    c3_lf_A[c3_i986] = c3_kf_A[c3_i986];
  }

  for (c3_i987 = 0; c3_i987 < 16; c3_i987 = c3_i987 + 1) {
    c3_lf_B[c3_i987] = c3_kf_B[c3_i987];
  }

  for (c3_i988 = 0; c3_i988 < 16; c3_i988 = c3_i988 + 1) {
    c3_mf_A[c3_i988] = c3_lf_A[c3_i988];
  }

  for (c3_i989 = 0; c3_i989 < 16; c3_i989 = c3_i989 + 1) {
    c3_mf_B[c3_i989] = c3_lf_B[c3_i989];
  }

  for (c3_i990 = 0; c3_i990 < 4; c3_i990 = c3_i990 + 1) {
    c3_i991 = 0;
    for (c3_i992 = 0; c3_i992 < 4; c3_i992 = c3_i992 + 1) {
      c3_g34[c3_i991 + c3_i990] = 0.0;
      c3_i993 = 0;
      for (c3_i994 = 0; c3_i994 < 4; c3_i994 = c3_i994 + 1) {
        c3_g34[c3_i991 + c3_i990] = c3_g34[c3_i991 + c3_i990] + c3_mf_A[c3_i993
          + c3_i990] * c3_mf_B[c3_i994 + c3_i991];
        c3_i993 = c3_i993 + 4;
      }

      c3_i991 = c3_i991 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 173);
  for (c3_i995 = 0; c3_i995 < 16; c3_i995 = c3_i995 + 1) {
    c3_b_g34[c3_i995] = c3_g34[c3_i995];
  }

  for (c3_i996 = 0; c3_i996 < 16; c3_i996 = c3_i996 + 1) {
    c3_dv83[c3_i996] = c3_dv52[c3_i996];
  }

  c3_b_mldivide(chartInstance, c3_b_g34, c3_dv83, c3_dv84);
  for (c3_i997 = 0; c3_i997 < 16; c3_i997 = c3_i997 + 1) {
    c3_dv85[c3_i997] = c3_dv84[c3_i997];
  }

  c3_Adj(chartInstance, c3_dv85, c3_dv86);
  for (c3_i998 = 0; c3_i998 < 36; c3_i998 = c3_i998 + 1) {
    c3_Adinvg34[c3_i998] = c3_dv86[c3_i998];
  }

  _SFD_SCRIPT_CALL(0, 174);
  for (c3_i999 = 0; c3_i999 < 36; c3_i999 = c3_i999 + 1) {
    c3_td_a[c3_i999] = c3_Adinvg34[c3_i999];
  }

  for (c3_i1000 = 0; c3_i1000 < 6; c3_i1000 = c3_i1000 + 1) {
    c3_qd_b[c3_i1000] = c3_V3[c3_i1000];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1001 = 0; c3_i1001 < 36; c3_i1001 = c3_i1001 + 1) {
    c3_ud_a[c3_i1001] = c3_td_a[c3_i1001];
  }

  for (c3_i1002 = 0; c3_i1002 < 6; c3_i1002 = c3_i1002 + 1) {
    c3_rd_b[c3_i1002] = c3_qd_b[c3_i1002];
  }

  for (c3_i1003 = 0; c3_i1003 < 6; c3_i1003 = c3_i1003 + 1) {
    c3_dv87[c3_i1003] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ud_a, c3_rd_b, c3_dv87, c3_xc_y);
  c3_sd_b = c3_Vel[3];
  for (c3_i1004 = 0; c3_i1004 < 6; c3_i1004 = c3_i1004 + 1) {
    c3_yc_y[c3_i1004] = c3_dv10[c3_i1004] * c3_sd_b;
  }

  for (c3_i1005 = 0; c3_i1005 < 6; c3_i1005 = c3_i1005 + 1) {
    c3_V4[c3_i1005] = c3_xc_y[c3_i1005] + c3_yc_y[c3_i1005];
  }

  _SFD_SCRIPT_CALL(0, 175);
  c3_td_b = c3_Acc[3];
  for (c3_i1006 = 0; c3_i1006 < 6; c3_i1006 = c3_i1006 + 1) {
    c3_ad_y[c3_i1006] = c3_dv10[c3_i1006] * c3_td_b;
  }

  for (c3_i1007 = 0; c3_i1007 < 36; c3_i1007 = c3_i1007 + 1) {
    c3_vd_a[c3_i1007] = c3_Adinvg34[c3_i1007];
  }

  for (c3_i1008 = 0; c3_i1008 < 6; c3_i1008 = c3_i1008 + 1) {
    c3_ud_b[c3_i1008] = c3_dV3[c3_i1008];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1009 = 0; c3_i1009 < 36; c3_i1009 = c3_i1009 + 1) {
    c3_wd_a[c3_i1009] = c3_vd_a[c3_i1009];
  }

  for (c3_i1010 = 0; c3_i1010 < 6; c3_i1010 = c3_i1010 + 1) {
    c3_vd_b[c3_i1010] = c3_ud_b[c3_i1010];
  }

  for (c3_i1011 = 0; c3_i1011 < 6; c3_i1011 = c3_i1011 + 1) {
    c3_dv88[c3_i1011] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_wd_a, c3_vd_b, c3_dv88, c3_bd_y);
  c3_wd_b = c3_Vel[3];
  for (c3_i1012 = 0; c3_i1012 < 6; c3_i1012 = c3_i1012 + 1) {
    c3_cd_y[c3_i1012] = c3_dv10[c3_i1012] * c3_wd_b;
  }

  for (c3_i1013 = 0; c3_i1013 < 36; c3_i1013 = c3_i1013 + 1) {
    c3_xd_a[c3_i1013] = c3_Adinvg34[c3_i1013];
  }

  for (c3_i1014 = 0; c3_i1014 < 6; c3_i1014 = c3_i1014 + 1) {
    c3_xd_b[c3_i1014] = c3_V3[c3_i1014];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1015 = 0; c3_i1015 < 36; c3_i1015 = c3_i1015 + 1) {
    c3_yd_a[c3_i1015] = c3_xd_a[c3_i1015];
  }

  for (c3_i1016 = 0; c3_i1016 < 6; c3_i1016 = c3_i1016 + 1) {
    c3_yd_b[c3_i1016] = c3_xd_b[c3_i1016];
  }

  for (c3_i1017 = 0; c3_i1017 < 6; c3_i1017 = c3_i1017 + 1) {
    c3_dv89[c3_i1017] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_yd_a, c3_yd_b, c3_dv89, c3_dd_y);
  for (c3_i1018 = 0; c3_i1018 < 6; c3_i1018 = c3_i1018 + 1) {
    c3_ed_y[c3_i1018] = c3_cd_y[c3_i1018];
  }

  c3_ad(chartInstance, c3_ed_y, c3_ae_a);
  for (c3_i1019 = 0; c3_i1019 < 6; c3_i1019 = c3_i1019 + 1) {
    c3_ae_b[c3_i1019] = c3_dd_y[c3_i1019];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1020 = 0; c3_i1020 < 36; c3_i1020 = c3_i1020 + 1) {
    c3_be_a[c3_i1020] = c3_ae_a[c3_i1020];
  }

  for (c3_i1021 = 0; c3_i1021 < 6; c3_i1021 = c3_i1021 + 1) {
    c3_be_b[c3_i1021] = c3_ae_b[c3_i1021];
  }

  for (c3_i1022 = 0; c3_i1022 < 6; c3_i1022 = c3_i1022 + 1) {
    c3_dv90[c3_i1022] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_be_a, c3_be_b, c3_dv90, c3_fd_y);
  for (c3_i1023 = 0; c3_i1023 < 6; c3_i1023 = c3_i1023 + 1) {
    c3_dV4[c3_i1023] = (c3_ad_y[c3_i1023] + c3_bd_y[c3_i1023]) -
      c3_fd_y[c3_i1023];
  }

  /*  dV4 = kxi4*Acc(4) + Adinvg34 * dV3; */
  /*  dV4(1:3) = dV4(1:3) + g34(1:3,1:3)'*cross(V3(4:6),cross(V3(4:6),g34(1:3,4))); */
  /*  dV4(4:6) = dV4(4:6) + g34(1:3,1:3)'*Vel(4)*cross(V3(4:6),g34(1:3,1:3)*kxi4(4:6)); */
  /* JntVel(4) = [0;0;0;1;0;0]'*(Adj(g01*g12*g23*g34)*V4); */
  _SFD_SCRIPT_CALL(0, 181);
  for (c3_i1024 = 0; c3_i1024 < 6; c3_i1024 = c3_i1024 + 1) {
    c3_JntVel[c3_i1024 + 18] = c3_V4[c3_i1024];
  }

  _SFD_SCRIPT_CALL(0, 182);
  for (c3_i1025 = 0; c3_i1025 < 6; c3_i1025 = c3_i1025 + 1) {
    c3_JntAcc[c3_i1025 + 18] = c3_dV4[c3_i1025];
  }

  /*  Joint 5: */
  _SFD_SCRIPT_CALL(0, 185);
  for (c3_i1026 = 0; c3_i1026 < 16; c3_i1026 = c3_i1026 + 1) {
    c3_ce_a[c3_i1026] = c3_g45_0[c3_i1026];
  }

  for (c3_i1027 = 0; c3_i1027 < 6; c3_i1027 = c3_i1027 + 1) {
    c3_dv91[c3_i1027] = c3_dv10[c3_i1027];
  }

  c3_expg(chartInstance, c3_dv91, c3_Pos[4], c3_ce_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i1028 = 0; c3_i1028 < 16; c3_i1028 = c3_i1028 + 1) {
    c3_nf_A[c3_i1028] = c3_ce_a[c3_i1028];
  }

  for (c3_i1029 = 0; c3_i1029 < 16; c3_i1029 = c3_i1029 + 1) {
    c3_nf_B[c3_i1029] = c3_ce_b[c3_i1029];
  }

  for (c3_i1030 = 0; c3_i1030 < 16; c3_i1030 = c3_i1030 + 1) {
    c3_g45[c3_i1030] = 0.0;
  }

  for (c3_i1031 = 0; c3_i1031 < 16; c3_i1031 = c3_i1031 + 1) {
    c3_of_A[c3_i1031] = c3_nf_A[c3_i1031];
  }

  for (c3_i1032 = 0; c3_i1032 < 16; c3_i1032 = c3_i1032 + 1) {
    c3_of_B[c3_i1032] = c3_nf_B[c3_i1032];
  }

  for (c3_i1033 = 0; c3_i1033 < 16; c3_i1033 = c3_i1033 + 1) {
    c3_pf_A[c3_i1033] = c3_of_A[c3_i1033];
  }

  for (c3_i1034 = 0; c3_i1034 < 16; c3_i1034 = c3_i1034 + 1) {
    c3_pf_B[c3_i1034] = c3_of_B[c3_i1034];
  }

  for (c3_i1035 = 0; c3_i1035 < 4; c3_i1035 = c3_i1035 + 1) {
    c3_i1036 = 0;
    for (c3_i1037 = 0; c3_i1037 < 4; c3_i1037 = c3_i1037 + 1) {
      c3_g45[c3_i1036 + c3_i1035] = 0.0;
      c3_i1038 = 0;
      for (c3_i1039 = 0; c3_i1039 < 4; c3_i1039 = c3_i1039 + 1) {
        c3_g45[c3_i1036 + c3_i1035] = c3_g45[c3_i1036 + c3_i1035] +
          c3_pf_A[c3_i1038 + c3_i1035] * c3_pf_B[c3_i1039 + c3_i1036];
        c3_i1038 = c3_i1038 + 4;
      }

      c3_i1036 = c3_i1036 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 186);
  for (c3_i1040 = 0; c3_i1040 < 16; c3_i1040 = c3_i1040 + 1) {
    c3_b_g45[c3_i1040] = c3_g45[c3_i1040];
  }

  for (c3_i1041 = 0; c3_i1041 < 16; c3_i1041 = c3_i1041 + 1) {
    c3_dv92[c3_i1041] = c3_dv52[c3_i1041];
  }

  c3_b_mldivide(chartInstance, c3_b_g45, c3_dv92, c3_dv93);
  for (c3_i1042 = 0; c3_i1042 < 16; c3_i1042 = c3_i1042 + 1) {
    c3_dv94[c3_i1042] = c3_dv93[c3_i1042];
  }

  c3_Adj(chartInstance, c3_dv94, c3_dv95);
  for (c3_i1043 = 0; c3_i1043 < 36; c3_i1043 = c3_i1043 + 1) {
    c3_Adinvg45[c3_i1043] = c3_dv95[c3_i1043];
  }

  _SFD_SCRIPT_CALL(0, 187);
  for (c3_i1044 = 0; c3_i1044 < 36; c3_i1044 = c3_i1044 + 1) {
    c3_de_a[c3_i1044] = c3_Adinvg45[c3_i1044];
  }

  for (c3_i1045 = 0; c3_i1045 < 6; c3_i1045 = c3_i1045 + 1) {
    c3_de_b[c3_i1045] = c3_V4[c3_i1045];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1046 = 0; c3_i1046 < 36; c3_i1046 = c3_i1046 + 1) {
    c3_ee_a[c3_i1046] = c3_de_a[c3_i1046];
  }

  for (c3_i1047 = 0; c3_i1047 < 6; c3_i1047 = c3_i1047 + 1) {
    c3_ee_b[c3_i1047] = c3_de_b[c3_i1047];
  }

  for (c3_i1048 = 0; c3_i1048 < 6; c3_i1048 = c3_i1048 + 1) {
    c3_dv96[c3_i1048] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ee_a, c3_ee_b, c3_dv96, c3_gd_y);
  c3_fe_b = c3_Vel[4];
  for (c3_i1049 = 0; c3_i1049 < 6; c3_i1049 = c3_i1049 + 1) {
    c3_hd_y[c3_i1049] = c3_dv10[c3_i1049] * c3_fe_b;
  }

  for (c3_i1050 = 0; c3_i1050 < 6; c3_i1050 = c3_i1050 + 1) {
    c3_V5[c3_i1050] = c3_gd_y[c3_i1050] + c3_hd_y[c3_i1050];
  }

  _SFD_SCRIPT_CALL(0, 188);
  c3_ge_b = c3_Acc[4];
  for (c3_i1051 = 0; c3_i1051 < 6; c3_i1051 = c3_i1051 + 1) {
    c3_id_y[c3_i1051] = c3_dv10[c3_i1051] * c3_ge_b;
  }

  for (c3_i1052 = 0; c3_i1052 < 36; c3_i1052 = c3_i1052 + 1) {
    c3_fe_a[c3_i1052] = c3_Adinvg45[c3_i1052];
  }

  for (c3_i1053 = 0; c3_i1053 < 6; c3_i1053 = c3_i1053 + 1) {
    c3_he_b[c3_i1053] = c3_dV4[c3_i1053];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1054 = 0; c3_i1054 < 36; c3_i1054 = c3_i1054 + 1) {
    c3_ge_a[c3_i1054] = c3_fe_a[c3_i1054];
  }

  for (c3_i1055 = 0; c3_i1055 < 6; c3_i1055 = c3_i1055 + 1) {
    c3_ie_b[c3_i1055] = c3_he_b[c3_i1055];
  }

  for (c3_i1056 = 0; c3_i1056 < 6; c3_i1056 = c3_i1056 + 1) {
    c3_dv97[c3_i1056] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ge_a, c3_ie_b, c3_dv97, c3_jd_y);
  c3_je_b = c3_Vel[4];
  for (c3_i1057 = 0; c3_i1057 < 6; c3_i1057 = c3_i1057 + 1) {
    c3_kd_y[c3_i1057] = c3_dv10[c3_i1057] * c3_je_b;
  }

  for (c3_i1058 = 0; c3_i1058 < 36; c3_i1058 = c3_i1058 + 1) {
    c3_he_a[c3_i1058] = c3_Adinvg45[c3_i1058];
  }

  for (c3_i1059 = 0; c3_i1059 < 6; c3_i1059 = c3_i1059 + 1) {
    c3_ke_b[c3_i1059] = c3_V4[c3_i1059];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1060 = 0; c3_i1060 < 36; c3_i1060 = c3_i1060 + 1) {
    c3_ie_a[c3_i1060] = c3_he_a[c3_i1060];
  }

  for (c3_i1061 = 0; c3_i1061 < 6; c3_i1061 = c3_i1061 + 1) {
    c3_le_b[c3_i1061] = c3_ke_b[c3_i1061];
  }

  for (c3_i1062 = 0; c3_i1062 < 6; c3_i1062 = c3_i1062 + 1) {
    c3_dv98[c3_i1062] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ie_a, c3_le_b, c3_dv98, c3_ld_y);
  for (c3_i1063 = 0; c3_i1063 < 6; c3_i1063 = c3_i1063 + 1) {
    c3_md_y[c3_i1063] = c3_kd_y[c3_i1063];
  }

  c3_ad(chartInstance, c3_md_y, c3_je_a);
  for (c3_i1064 = 0; c3_i1064 < 6; c3_i1064 = c3_i1064 + 1) {
    c3_me_b[c3_i1064] = c3_ld_y[c3_i1064];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1065 = 0; c3_i1065 < 36; c3_i1065 = c3_i1065 + 1) {
    c3_ke_a[c3_i1065] = c3_je_a[c3_i1065];
  }

  for (c3_i1066 = 0; c3_i1066 < 6; c3_i1066 = c3_i1066 + 1) {
    c3_ne_b[c3_i1066] = c3_me_b[c3_i1066];
  }

  for (c3_i1067 = 0; c3_i1067 < 6; c3_i1067 = c3_i1067 + 1) {
    c3_dv99[c3_i1067] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ke_a, c3_ne_b, c3_dv99, c3_nd_y);
  for (c3_i1068 = 0; c3_i1068 < 6; c3_i1068 = c3_i1068 + 1) {
    c3_dV5[c3_i1068] = (c3_id_y[c3_i1068] + c3_jd_y[c3_i1068]) -
      c3_nd_y[c3_i1068];
  }

  /*  dV5 = kxi5*Acc(5) + Adinvg45 * dV4; */
  /*  dV5(1:3) = dV5(1:3) + g45(1:3,1:3)'*cross(V4(4:6),cross(V4(4:6),g45(1:3,4))); */
  /*  dV5(4:6) = dV5(4:6) + g45(1:3,1:3)'*Vel(5)*cross(V4(4:6),g45(1:3,1:3)*kxi5(4:6)); */
  /* JntVel(5) = [0;0;0;0;1;0]'*(Adj(g01*g12*g23*g34*g45)*V5); */
  _SFD_SCRIPT_CALL(0, 194);
  for (c3_i1069 = 0; c3_i1069 < 6; c3_i1069 = c3_i1069 + 1) {
    c3_JntVel[c3_i1069 + 24] = c3_V5[c3_i1069];
  }

  _SFD_SCRIPT_CALL(0, 195);
  for (c3_i1070 = 0; c3_i1070 < 6; c3_i1070 = c3_i1070 + 1) {
    c3_JntAcc[c3_i1070 + 24] = c3_dV5[c3_i1070];
  }

  /*  Joint 6: */
  _SFD_SCRIPT_CALL(0, 198);
  for (c3_i1071 = 0; c3_i1071 < 16; c3_i1071 = c3_i1071 + 1) {
    c3_le_a[c3_i1071] = c3_g56_0[c3_i1071];
  }

  for (c3_i1072 = 0; c3_i1072 < 6; c3_i1072 = c3_i1072 + 1) {
    c3_dv100[c3_i1072] = c3_dv10[c3_i1072];
  }

  c3_expg(chartInstance, c3_dv100, c3_Pos[5], c3_oe_b);
  c3_e_eml_scalar_eg(chartInstance);
  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i1073 = 0; c3_i1073 < 16; c3_i1073 = c3_i1073 + 1) {
    c3_qf_A[c3_i1073] = c3_le_a[c3_i1073];
  }

  for (c3_i1074 = 0; c3_i1074 < 16; c3_i1074 = c3_i1074 + 1) {
    c3_qf_B[c3_i1074] = c3_oe_b[c3_i1074];
  }

  for (c3_i1075 = 0; c3_i1075 < 16; c3_i1075 = c3_i1075 + 1) {
    c3_g56[c3_i1075] = 0.0;
  }

  for (c3_i1076 = 0; c3_i1076 < 16; c3_i1076 = c3_i1076 + 1) {
    c3_rf_A[c3_i1076] = c3_qf_A[c3_i1076];
  }

  for (c3_i1077 = 0; c3_i1077 < 16; c3_i1077 = c3_i1077 + 1) {
    c3_rf_B[c3_i1077] = c3_qf_B[c3_i1077];
  }

  for (c3_i1078 = 0; c3_i1078 < 16; c3_i1078 = c3_i1078 + 1) {
    c3_sf_A[c3_i1078] = c3_rf_A[c3_i1078];
  }

  for (c3_i1079 = 0; c3_i1079 < 16; c3_i1079 = c3_i1079 + 1) {
    c3_sf_B[c3_i1079] = c3_rf_B[c3_i1079];
  }

  for (c3_i1080 = 0; c3_i1080 < 4; c3_i1080 = c3_i1080 + 1) {
    c3_i1081 = 0;
    for (c3_i1082 = 0; c3_i1082 < 4; c3_i1082 = c3_i1082 + 1) {
      c3_g56[c3_i1081 + c3_i1080] = 0.0;
      c3_i1083 = 0;
      for (c3_i1084 = 0; c3_i1084 < 4; c3_i1084 = c3_i1084 + 1) {
        c3_g56[c3_i1081 + c3_i1080] = c3_g56[c3_i1081 + c3_i1080] +
          c3_sf_A[c3_i1083 + c3_i1080] * c3_sf_B[c3_i1084 + c3_i1081];
        c3_i1083 = c3_i1083 + 4;
      }

      c3_i1081 = c3_i1081 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 199);
  for (c3_i1085 = 0; c3_i1085 < 16; c3_i1085 = c3_i1085 + 1) {
    c3_b_g56[c3_i1085] = c3_g56[c3_i1085];
  }

  for (c3_i1086 = 0; c3_i1086 < 16; c3_i1086 = c3_i1086 + 1) {
    c3_dv101[c3_i1086] = c3_dv52[c3_i1086];
  }

  c3_b_mldivide(chartInstance, c3_b_g56, c3_dv101, c3_dv102);
  for (c3_i1087 = 0; c3_i1087 < 16; c3_i1087 = c3_i1087 + 1) {
    c3_dv103[c3_i1087] = c3_dv102[c3_i1087];
  }

  c3_Adj(chartInstance, c3_dv103, c3_dv104);
  for (c3_i1088 = 0; c3_i1088 < 36; c3_i1088 = c3_i1088 + 1) {
    c3_Adinvg56[c3_i1088] = c3_dv104[c3_i1088];
  }

  _SFD_SCRIPT_CALL(0, 200);
  for (c3_i1089 = 0; c3_i1089 < 36; c3_i1089 = c3_i1089 + 1) {
    c3_me_a[c3_i1089] = c3_Adinvg56[c3_i1089];
  }

  for (c3_i1090 = 0; c3_i1090 < 6; c3_i1090 = c3_i1090 + 1) {
    c3_pe_b[c3_i1090] = c3_V5[c3_i1090];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1091 = 0; c3_i1091 < 36; c3_i1091 = c3_i1091 + 1) {
    c3_ne_a[c3_i1091] = c3_me_a[c3_i1091];
  }

  for (c3_i1092 = 0; c3_i1092 < 6; c3_i1092 = c3_i1092 + 1) {
    c3_qe_b[c3_i1092] = c3_pe_b[c3_i1092];
  }

  for (c3_i1093 = 0; c3_i1093 < 6; c3_i1093 = c3_i1093 + 1) {
    c3_dv105[c3_i1093] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ne_a, c3_qe_b, c3_dv105, c3_od_y);
  c3_re_b = c3_Vel[5];
  for (c3_i1094 = 0; c3_i1094 < 6; c3_i1094 = c3_i1094 + 1) {
    c3_pd_y[c3_i1094] = c3_dv10[c3_i1094] * c3_re_b;
  }

  for (c3_i1095 = 0; c3_i1095 < 6; c3_i1095 = c3_i1095 + 1) {
    c3_V6[c3_i1095] = c3_od_y[c3_i1095] + c3_pd_y[c3_i1095];
  }

  _SFD_SCRIPT_CALL(0, 201);
  c3_se_b = c3_Acc[5];
  for (c3_i1096 = 0; c3_i1096 < 6; c3_i1096 = c3_i1096 + 1) {
    c3_qd_y[c3_i1096] = c3_dv10[c3_i1096] * c3_se_b;
  }

  for (c3_i1097 = 0; c3_i1097 < 36; c3_i1097 = c3_i1097 + 1) {
    c3_oe_a[c3_i1097] = c3_Adinvg56[c3_i1097];
  }

  for (c3_i1098 = 0; c3_i1098 < 6; c3_i1098 = c3_i1098 + 1) {
    c3_te_b[c3_i1098] = c3_dV5[c3_i1098];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1099 = 0; c3_i1099 < 36; c3_i1099 = c3_i1099 + 1) {
    c3_pe_a[c3_i1099] = c3_oe_a[c3_i1099];
  }

  for (c3_i1100 = 0; c3_i1100 < 6; c3_i1100 = c3_i1100 + 1) {
    c3_ue_b[c3_i1100] = c3_te_b[c3_i1100];
  }

  for (c3_i1101 = 0; c3_i1101 < 6; c3_i1101 = c3_i1101 + 1) {
    c3_dv106[c3_i1101] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_pe_a, c3_ue_b, c3_dv106, c3_rd_y);
  c3_ve_b = c3_Vel[5];
  for (c3_i1102 = 0; c3_i1102 < 6; c3_i1102 = c3_i1102 + 1) {
    c3_sd_y[c3_i1102] = c3_dv10[c3_i1102] * c3_ve_b;
  }

  for (c3_i1103 = 0; c3_i1103 < 36; c3_i1103 = c3_i1103 + 1) {
    c3_qe_a[c3_i1103] = c3_Adinvg56[c3_i1103];
  }

  for (c3_i1104 = 0; c3_i1104 < 6; c3_i1104 = c3_i1104 + 1) {
    c3_we_b[c3_i1104] = c3_V5[c3_i1104];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1105 = 0; c3_i1105 < 36; c3_i1105 = c3_i1105 + 1) {
    c3_re_a[c3_i1105] = c3_qe_a[c3_i1105];
  }

  for (c3_i1106 = 0; c3_i1106 < 6; c3_i1106 = c3_i1106 + 1) {
    c3_xe_b[c3_i1106] = c3_we_b[c3_i1106];
  }

  for (c3_i1107 = 0; c3_i1107 < 6; c3_i1107 = c3_i1107 + 1) {
    c3_dv107[c3_i1107] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_re_a, c3_xe_b, c3_dv107, c3_td_y);
  for (c3_i1108 = 0; c3_i1108 < 6; c3_i1108 = c3_i1108 + 1) {
    c3_ud_y[c3_i1108] = c3_sd_y[c3_i1108];
  }

  c3_ad(chartInstance, c3_ud_y, c3_se_a);
  for (c3_i1109 = 0; c3_i1109 < 6; c3_i1109 = c3_i1109 + 1) {
    c3_ye_b[c3_i1109] = c3_td_y[c3_i1109];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1110 = 0; c3_i1110 < 36; c3_i1110 = c3_i1110 + 1) {
    c3_te_a[c3_i1110] = c3_se_a[c3_i1110];
  }

  for (c3_i1111 = 0; c3_i1111 < 6; c3_i1111 = c3_i1111 + 1) {
    c3_af_b[c3_i1111] = c3_ye_b[c3_i1111];
  }

  for (c3_i1112 = 0; c3_i1112 < 6; c3_i1112 = c3_i1112 + 1) {
    c3_dv108[c3_i1112] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_te_a, c3_af_b, c3_dv108, c3_vd_y);
  for (c3_i1113 = 0; c3_i1113 < 6; c3_i1113 = c3_i1113 + 1) {
    c3_dV6[c3_i1113] = (c3_qd_y[c3_i1113] + c3_rd_y[c3_i1113]) -
      c3_vd_y[c3_i1113];
  }

  /*  dV6 = kxi6*Acc(6) + Adinvg56 * dV5; */
  /*  dV6(1:3) = dV6(1:3) + g56(1:3,1:3)'*cross(V5(4:6),cross(V5(4:6),g56(1:3,4))); */
  /*  dV6(4:6) = dV6(4:6) + g56(1:3,1:3)'*Vel(5)*cross(V5(4:6),g56(1:3,1:3)*kxi6(4:6)); */
  /* JntVel(6) = [0;0;0;1;0;0]'*(Adj(g01*g12*g23*g34*g45*g56)*V6); */
  _SFD_SCRIPT_CALL(0, 207);
  for (c3_i1114 = 0; c3_i1114 < 6; c3_i1114 = c3_i1114 + 1) {
    c3_JntVel[c3_i1114 + 30] = c3_V6[c3_i1114];
  }

  _SFD_SCRIPT_CALL(0, 208);
  for (c3_i1115 = 0; c3_i1115 < 6; c3_i1115 = c3_i1115 + 1) {
    c3_JntAcc[c3_i1115 + 30] = c3_dV6[c3_i1115];
  }

  /* %%%% */
  /*  g6e =[eye(3),[0; 0;  154];0 0 0 1]; */
  /*  g5e =[eye(3),[0; 0;  -113];0 0 0 1]; */
  /*  g4e =[eye(3),[0; 0;  302.5];0 0 0 1]; */
  /*  g3e =[eye(3),[0; 0;  227];0 0 0 1]; */
  /*  g2e =[eye(3),[0; 0;  62];0 0 0 1]; */
  /*  g1e =[eye(3),[0; 0;  1];0 0 0 1]; */
  /*  %% Backward Recursion (inverse dynamic) */
  /*  Initial State */
  _SFD_SCRIPT_CALL(0, 223);
  for (c3_i1116 = 0; c3_i1116 < 6; c3_i1116 = c3_i1116 + 1) {
    c3_Tau[c3_i1116] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 224);
  for (c3_i1117 = 0; c3_i1117 < 6; c3_i1117 = c3_i1117 + 1) {
    c3_F7[c3_i1117] = c3_Ft[c3_i1117];
  }

  _SFD_SCRIPT_CALL(0, 225);
  for (c3_i1118 = 0; c3_i1118 < 16; c3_i1118 = c3_i1118 + 1) {
    c3_b_g67_0[c3_i1118] = c3_g67_0[c3_i1118];
  }

  for (c3_i1119 = 0; c3_i1119 < 16; c3_i1119 = c3_i1119 + 1) {
    c3_dv109[c3_i1119] = c3_dv52[c3_i1119];
  }

  c3_b_mldivide(chartInstance, c3_b_g67_0, c3_dv109, c3_dv110);
  for (c3_i1120 = 0; c3_i1120 < 16; c3_i1120 = c3_i1120 + 1) {
    c3_dv111[c3_i1120] = c3_dv110[c3_i1120];
  }

  c3_Adj(chartInstance, c3_dv111, c3_dv112);
  for (c3_i1121 = 0; c3_i1121 < 36; c3_i1121 = c3_i1121 + 1) {
    c3_Adinvg67[c3_i1121] = c3_dv112[c3_i1121];
  }

  /*  Joint 6 */
  _SFD_SCRIPT_CALL(0, 228);
  c3_i1122 = 0;
  for (c3_i1123 = 0; c3_i1123 < 6; c3_i1123 = c3_i1123 + 1) {
    c3_i1124 = 0;
    for (c3_i1125 = 0; c3_i1125 < 6; c3_i1125 = c3_i1125 + 1) {
      c3_ue_a[c3_i1125 + c3_i1122] = c3_Adinvg67[c3_i1124 + c3_i1123];
      c3_i1124 = c3_i1124 + 6;
    }

    c3_i1122 = c3_i1122 + 6;
  }

  for (c3_i1126 = 0; c3_i1126 < 6; c3_i1126 = c3_i1126 + 1) {
    c3_bf_b[c3_i1126] = c3_F7[c3_i1126];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1127 = 0; c3_i1127 < 36; c3_i1127 = c3_i1127 + 1) {
    c3_ve_a[c3_i1127] = c3_ue_a[c3_i1127];
  }

  for (c3_i1128 = 0; c3_i1128 < 6; c3_i1128 = c3_i1128 + 1) {
    c3_cf_b[c3_i1128] = c3_bf_b[c3_i1128];
  }

  for (c3_i1129 = 0; c3_i1129 < 6; c3_i1129 = c3_i1129 + 1) {
    c3_dv113[c3_i1129] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ve_a, c3_cf_b, c3_dv113, c3_wd_y);
  for (c3_i1130 = 0; c3_i1130 < 36; c3_i1130 = c3_i1130 + 1) {
    c3_we_a[c3_i1130] = c3_M6[c3_i1130];
  }

  for (c3_i1131 = 0; c3_i1131 < 6; c3_i1131 = c3_i1131 + 1) {
    c3_df_b[c3_i1131] = c3_dV6[c3_i1131];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1132 = 0; c3_i1132 < 36; c3_i1132 = c3_i1132 + 1) {
    c3_xe_a[c3_i1132] = c3_we_a[c3_i1132];
  }

  for (c3_i1133 = 0; c3_i1133 < 6; c3_i1133 = c3_i1133 + 1) {
    c3_ef_b[c3_i1133] = c3_df_b[c3_i1133];
  }

  for (c3_i1134 = 0; c3_i1134 < 6; c3_i1134 = c3_i1134 + 1) {
    c3_dv114[c3_i1134] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_xe_a, c3_ef_b, c3_dv114, c3_xd_y);
  for (c3_i1135 = 0; c3_i1135 < 6; c3_i1135 = c3_i1135 + 1) {
    c3_b_V6[c3_i1135] = c3_V6[c3_i1135];
  }

  c3_ad(chartInstance, c3_b_V6, c3_dv115);
  c3_i1136 = 0;
  for (c3_i1137 = 0; c3_i1137 < 6; c3_i1137 = c3_i1137 + 1) {
    c3_i1138 = 0;
    for (c3_i1139 = 0; c3_i1139 < 6; c3_i1139 = c3_i1139 + 1) {
      c3_ye_a[c3_i1139 + c3_i1136] = c3_dv115[c3_i1138 + c3_i1137];
      c3_i1138 = c3_i1138 + 6;
    }

    c3_i1136 = c3_i1136 + 6;
  }

  for (c3_i1140 = 0; c3_i1140 < 36; c3_i1140 = c3_i1140 + 1) {
    c3_ff_b[c3_i1140] = c3_M6[c3_i1140];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1141 = 0; c3_i1141 < 36; c3_i1141 = c3_i1141 + 1) {
    c3_tf_A[c3_i1141] = c3_ye_a[c3_i1141];
  }

  for (c3_i1142 = 0; c3_i1142 < 36; c3_i1142 = c3_i1142 + 1) {
    c3_tf_B[c3_i1142] = c3_ff_b[c3_i1142];
  }

  for (c3_i1143 = 0; c3_i1143 < 36; c3_i1143 = c3_i1143 + 1) {
    c3_uf_A[c3_i1143] = c3_tf_A[c3_i1143];
  }

  for (c3_i1144 = 0; c3_i1144 < 36; c3_i1144 = c3_i1144 + 1) {
    c3_uf_B[c3_i1144] = c3_tf_B[c3_i1144];
  }

  for (c3_i1145 = 0; c3_i1145 < 36; c3_i1145 = c3_i1145 + 1) {
    c3_vf_A[c3_i1145] = c3_uf_A[c3_i1145];
  }

  for (c3_i1146 = 0; c3_i1146 < 36; c3_i1146 = c3_i1146 + 1) {
    c3_vf_B[c3_i1146] = c3_uf_B[c3_i1146];
  }

  for (c3_i1147 = 0; c3_i1147 < 36; c3_i1147 = c3_i1147 + 1) {
    c3_dv116[c3_i1147] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_vf_A, 1, 6, c3_vf_B, 1, 6, 0.0,
                 c3_dv116, 1, 6, c3_yd_y);
  for (c3_i1148 = 0; c3_i1148 < 36; c3_i1148 = c3_i1148 + 1) {
    c3_af_a[c3_i1148] = c3_yd_y[c3_i1148];
  }

  for (c3_i1149 = 0; c3_i1149 < 6; c3_i1149 = c3_i1149 + 1) {
    c3_gf_b[c3_i1149] = c3_V6[c3_i1149];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1150 = 0; c3_i1150 < 36; c3_i1150 = c3_i1150 + 1) {
    c3_bf_a[c3_i1150] = c3_af_a[c3_i1150];
  }

  for (c3_i1151 = 0; c3_i1151 < 6; c3_i1151 = c3_i1151 + 1) {
    c3_hf_b[c3_i1151] = c3_gf_b[c3_i1151];
  }

  for (c3_i1152 = 0; c3_i1152 < 6; c3_i1152 = c3_i1152 + 1) {
    c3_dv117[c3_i1152] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_bf_a, c3_hf_b, c3_dv117, c3_ae_y);
  for (c3_i1153 = 0; c3_i1153 < 6; c3_i1153 = c3_i1153 + 1) {
    c3_F6[c3_i1153] = (c3_wd_y[c3_i1153] + c3_xd_y[c3_i1153]) - c3_ae_y[c3_i1153];
  }

  _SFD_SCRIPT_CALL(0, 229);
  for (c3_i1154 = 0; c3_i1154 < 6; c3_i1154 = c3_i1154 + 1) {
    c3_if_b[c3_i1154] = c3_F6[c3_i1154];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1155 = 0; c3_i1155 < 6; c3_i1155 = c3_i1155 + 1) {
    c3_be_y[c3_i1155] = c3_if_b[c3_i1155];
  }

  for (c3_i1156 = 0; c3_i1156 < 6; c3_i1156 = c3_i1156 + 1) {
    c3_ce_y[c3_i1156] = c3_be_y[c3_i1156];
  }

  for (c3_i1157 = 0; c3_i1157 < 6; c3_i1157 = c3_i1157 + 1) {
    c3_de_y[c3_i1157] = c3_ce_y[c3_i1157];
  }

  for (c3_i1158 = 0; c3_i1158 < 6; c3_i1158 = c3_i1158 + 1) {
    c3_dv118[c3_i1158] = c3_dv10[c3_i1158];
  }

  for (c3_i1159 = 0; c3_i1159 < 6; c3_i1159 = c3_i1159 + 1) {
    c3_ee_y[c3_i1159] = c3_de_y[c3_i1159];
  }

  c3_fe_y = c3_ceval_xdot(chartInstance, 6, c3_dv118, 1, 1, c3_ee_y, 1, 1);
  c3_Tau[5] = c3_fe_y;
  _SFD_SCRIPT_CALL(0, 230);
  for (c3_i1160 = 0; c3_i1160 < 6; c3_i1160 = c3_i1160 + 1) {
    c3_JntF[c3_i1160 + 30] = c3_F6[c3_i1160];
  }

  /* Tau(6) = kxi6'*(Adj(g6e)'* F6); */
  /*  Joint 5 */
  _SFD_SCRIPT_CALL(0, 234);
  c3_i1161 = 0;
  for (c3_i1162 = 0; c3_i1162 < 6; c3_i1162 = c3_i1162 + 1) {
    c3_i1163 = 0;
    for (c3_i1164 = 0; c3_i1164 < 6; c3_i1164 = c3_i1164 + 1) {
      c3_cf_a[c3_i1164 + c3_i1161] = c3_Adinvg56[c3_i1163 + c3_i1162];
      c3_i1163 = c3_i1163 + 6;
    }

    c3_i1161 = c3_i1161 + 6;
  }

  for (c3_i1165 = 0; c3_i1165 < 6; c3_i1165 = c3_i1165 + 1) {
    c3_jf_b[c3_i1165] = c3_F6[c3_i1165];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1166 = 0; c3_i1166 < 36; c3_i1166 = c3_i1166 + 1) {
    c3_df_a[c3_i1166] = c3_cf_a[c3_i1166];
  }

  for (c3_i1167 = 0; c3_i1167 < 6; c3_i1167 = c3_i1167 + 1) {
    c3_kf_b[c3_i1167] = c3_jf_b[c3_i1167];
  }

  for (c3_i1168 = 0; c3_i1168 < 6; c3_i1168 = c3_i1168 + 1) {
    c3_dv119[c3_i1168] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_df_a, c3_kf_b, c3_dv119, c3_ge_y);
  for (c3_i1169 = 0; c3_i1169 < 36; c3_i1169 = c3_i1169 + 1) {
    c3_ef_a[c3_i1169] = c3_M5[c3_i1169];
  }

  for (c3_i1170 = 0; c3_i1170 < 6; c3_i1170 = c3_i1170 + 1) {
    c3_lf_b[c3_i1170] = c3_dV5[c3_i1170];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1171 = 0; c3_i1171 < 36; c3_i1171 = c3_i1171 + 1) {
    c3_ff_a[c3_i1171] = c3_ef_a[c3_i1171];
  }

  for (c3_i1172 = 0; c3_i1172 < 6; c3_i1172 = c3_i1172 + 1) {
    c3_mf_b[c3_i1172] = c3_lf_b[c3_i1172];
  }

  for (c3_i1173 = 0; c3_i1173 < 6; c3_i1173 = c3_i1173 + 1) {
    c3_dv120[c3_i1173] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ff_a, c3_mf_b, c3_dv120, c3_he_y);
  for (c3_i1174 = 0; c3_i1174 < 6; c3_i1174 = c3_i1174 + 1) {
    c3_b_V5[c3_i1174] = c3_V5[c3_i1174];
  }

  c3_ad(chartInstance, c3_b_V5, c3_dv121);
  c3_i1175 = 0;
  for (c3_i1176 = 0; c3_i1176 < 6; c3_i1176 = c3_i1176 + 1) {
    c3_i1177 = 0;
    for (c3_i1178 = 0; c3_i1178 < 6; c3_i1178 = c3_i1178 + 1) {
      c3_gf_a[c3_i1178 + c3_i1175] = c3_dv121[c3_i1177 + c3_i1176];
      c3_i1177 = c3_i1177 + 6;
    }

    c3_i1175 = c3_i1175 + 6;
  }

  for (c3_i1179 = 0; c3_i1179 < 36; c3_i1179 = c3_i1179 + 1) {
    c3_nf_b[c3_i1179] = c3_M5[c3_i1179];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1180 = 0; c3_i1180 < 36; c3_i1180 = c3_i1180 + 1) {
    c3_wf_A[c3_i1180] = c3_gf_a[c3_i1180];
  }

  for (c3_i1181 = 0; c3_i1181 < 36; c3_i1181 = c3_i1181 + 1) {
    c3_wf_B[c3_i1181] = c3_nf_b[c3_i1181];
  }

  for (c3_i1182 = 0; c3_i1182 < 36; c3_i1182 = c3_i1182 + 1) {
    c3_xf_A[c3_i1182] = c3_wf_A[c3_i1182];
  }

  for (c3_i1183 = 0; c3_i1183 < 36; c3_i1183 = c3_i1183 + 1) {
    c3_xf_B[c3_i1183] = c3_wf_B[c3_i1183];
  }

  for (c3_i1184 = 0; c3_i1184 < 36; c3_i1184 = c3_i1184 + 1) {
    c3_yf_A[c3_i1184] = c3_xf_A[c3_i1184];
  }

  for (c3_i1185 = 0; c3_i1185 < 36; c3_i1185 = c3_i1185 + 1) {
    c3_yf_B[c3_i1185] = c3_xf_B[c3_i1185];
  }

  for (c3_i1186 = 0; c3_i1186 < 36; c3_i1186 = c3_i1186 + 1) {
    c3_dv122[c3_i1186] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_yf_A, 1, 6, c3_yf_B, 1, 6, 0.0,
                 c3_dv122, 1, 6, c3_ie_y);
  for (c3_i1187 = 0; c3_i1187 < 36; c3_i1187 = c3_i1187 + 1) {
    c3_hf_a[c3_i1187] = c3_ie_y[c3_i1187];
  }

  for (c3_i1188 = 0; c3_i1188 < 6; c3_i1188 = c3_i1188 + 1) {
    c3_of_b[c3_i1188] = c3_V5[c3_i1188];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1189 = 0; c3_i1189 < 36; c3_i1189 = c3_i1189 + 1) {
    c3_if_a[c3_i1189] = c3_hf_a[c3_i1189];
  }

  for (c3_i1190 = 0; c3_i1190 < 6; c3_i1190 = c3_i1190 + 1) {
    c3_pf_b[c3_i1190] = c3_of_b[c3_i1190];
  }

  for (c3_i1191 = 0; c3_i1191 < 6; c3_i1191 = c3_i1191 + 1) {
    c3_dv123[c3_i1191] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_if_a, c3_pf_b, c3_dv123, c3_je_y);
  for (c3_i1192 = 0; c3_i1192 < 6; c3_i1192 = c3_i1192 + 1) {
    c3_F5[c3_i1192] = (c3_ge_y[c3_i1192] + c3_he_y[c3_i1192]) - c3_je_y[c3_i1192];
  }

  _SFD_SCRIPT_CALL(0, 235);
  for (c3_i1193 = 0; c3_i1193 < 6; c3_i1193 = c3_i1193 + 1) {
    c3_qf_b[c3_i1193] = c3_F5[c3_i1193];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1194 = 0; c3_i1194 < 6; c3_i1194 = c3_i1194 + 1) {
    c3_ke_y[c3_i1194] = c3_qf_b[c3_i1194];
  }

  for (c3_i1195 = 0; c3_i1195 < 6; c3_i1195 = c3_i1195 + 1) {
    c3_le_y[c3_i1195] = c3_ke_y[c3_i1195];
  }

  for (c3_i1196 = 0; c3_i1196 < 6; c3_i1196 = c3_i1196 + 1) {
    c3_me_y[c3_i1196] = c3_le_y[c3_i1196];
  }

  for (c3_i1197 = 0; c3_i1197 < 6; c3_i1197 = c3_i1197 + 1) {
    c3_dv124[c3_i1197] = c3_dv10[c3_i1197];
  }

  for (c3_i1198 = 0; c3_i1198 < 6; c3_i1198 = c3_i1198 + 1) {
    c3_ne_y[c3_i1198] = c3_me_y[c3_i1198];
  }

  c3_oe_y = c3_ceval_xdot(chartInstance, 6, c3_dv124, 1, 1, c3_ne_y, 1, 1);
  c3_Tau[4] = c3_oe_y;
  _SFD_SCRIPT_CALL(0, 236);
  for (c3_i1199 = 0; c3_i1199 < 6; c3_i1199 = c3_i1199 + 1) {
    c3_JntF[c3_i1199 + 24] = c3_F5[c3_i1199];
  }

  /* Tau(5) = kxi5'* (Adj(g5e)'*F5); */
  /*  Joint 4 */
  _SFD_SCRIPT_CALL(0, 240);
  c3_i1200 = 0;
  for (c3_i1201 = 0; c3_i1201 < 6; c3_i1201 = c3_i1201 + 1) {
    c3_i1202 = 0;
    for (c3_i1203 = 0; c3_i1203 < 6; c3_i1203 = c3_i1203 + 1) {
      c3_jf_a[c3_i1203 + c3_i1200] = c3_Adinvg45[c3_i1202 + c3_i1201];
      c3_i1202 = c3_i1202 + 6;
    }

    c3_i1200 = c3_i1200 + 6;
  }

  for (c3_i1204 = 0; c3_i1204 < 6; c3_i1204 = c3_i1204 + 1) {
    c3_rf_b[c3_i1204] = c3_F5[c3_i1204];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1205 = 0; c3_i1205 < 36; c3_i1205 = c3_i1205 + 1) {
    c3_kf_a[c3_i1205] = c3_jf_a[c3_i1205];
  }

  for (c3_i1206 = 0; c3_i1206 < 6; c3_i1206 = c3_i1206 + 1) {
    c3_sf_b[c3_i1206] = c3_rf_b[c3_i1206];
  }

  for (c3_i1207 = 0; c3_i1207 < 6; c3_i1207 = c3_i1207 + 1) {
    c3_dv125[c3_i1207] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_kf_a, c3_sf_b, c3_dv125, c3_pe_y);
  for (c3_i1208 = 0; c3_i1208 < 36; c3_i1208 = c3_i1208 + 1) {
    c3_lf_a[c3_i1208] = c3_M4[c3_i1208];
  }

  for (c3_i1209 = 0; c3_i1209 < 6; c3_i1209 = c3_i1209 + 1) {
    c3_tf_b[c3_i1209] = c3_dV4[c3_i1209];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1210 = 0; c3_i1210 < 36; c3_i1210 = c3_i1210 + 1) {
    c3_mf_a[c3_i1210] = c3_lf_a[c3_i1210];
  }

  for (c3_i1211 = 0; c3_i1211 < 6; c3_i1211 = c3_i1211 + 1) {
    c3_uf_b[c3_i1211] = c3_tf_b[c3_i1211];
  }

  for (c3_i1212 = 0; c3_i1212 < 6; c3_i1212 = c3_i1212 + 1) {
    c3_dv126[c3_i1212] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_mf_a, c3_uf_b, c3_dv126, c3_qe_y);
  for (c3_i1213 = 0; c3_i1213 < 6; c3_i1213 = c3_i1213 + 1) {
    c3_b_V4[c3_i1213] = c3_V4[c3_i1213];
  }

  c3_ad(chartInstance, c3_b_V4, c3_dv127);
  c3_i1214 = 0;
  for (c3_i1215 = 0; c3_i1215 < 6; c3_i1215 = c3_i1215 + 1) {
    c3_i1216 = 0;
    for (c3_i1217 = 0; c3_i1217 < 6; c3_i1217 = c3_i1217 + 1) {
      c3_nf_a[c3_i1217 + c3_i1214] = c3_dv127[c3_i1216 + c3_i1215];
      c3_i1216 = c3_i1216 + 6;
    }

    c3_i1214 = c3_i1214 + 6;
  }

  for (c3_i1218 = 0; c3_i1218 < 36; c3_i1218 = c3_i1218 + 1) {
    c3_vf_b[c3_i1218] = c3_M4[c3_i1218];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1219 = 0; c3_i1219 < 36; c3_i1219 = c3_i1219 + 1) {
    c3_ag_A[c3_i1219] = c3_nf_a[c3_i1219];
  }

  for (c3_i1220 = 0; c3_i1220 < 36; c3_i1220 = c3_i1220 + 1) {
    c3_ag_B[c3_i1220] = c3_vf_b[c3_i1220];
  }

  for (c3_i1221 = 0; c3_i1221 < 36; c3_i1221 = c3_i1221 + 1) {
    c3_bg_A[c3_i1221] = c3_ag_A[c3_i1221];
  }

  for (c3_i1222 = 0; c3_i1222 < 36; c3_i1222 = c3_i1222 + 1) {
    c3_bg_B[c3_i1222] = c3_ag_B[c3_i1222];
  }

  for (c3_i1223 = 0; c3_i1223 < 36; c3_i1223 = c3_i1223 + 1) {
    c3_cg_A[c3_i1223] = c3_bg_A[c3_i1223];
  }

  for (c3_i1224 = 0; c3_i1224 < 36; c3_i1224 = c3_i1224 + 1) {
    c3_cg_B[c3_i1224] = c3_bg_B[c3_i1224];
  }

  for (c3_i1225 = 0; c3_i1225 < 36; c3_i1225 = c3_i1225 + 1) {
    c3_dv128[c3_i1225] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_cg_A, 1, 6, c3_cg_B, 1, 6, 0.0,
                 c3_dv128, 1, 6, c3_re_y);
  for (c3_i1226 = 0; c3_i1226 < 36; c3_i1226 = c3_i1226 + 1) {
    c3_of_a[c3_i1226] = c3_re_y[c3_i1226];
  }

  for (c3_i1227 = 0; c3_i1227 < 6; c3_i1227 = c3_i1227 + 1) {
    c3_wf_b[c3_i1227] = c3_V4[c3_i1227];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1228 = 0; c3_i1228 < 36; c3_i1228 = c3_i1228 + 1) {
    c3_pf_a[c3_i1228] = c3_of_a[c3_i1228];
  }

  for (c3_i1229 = 0; c3_i1229 < 6; c3_i1229 = c3_i1229 + 1) {
    c3_xf_b[c3_i1229] = c3_wf_b[c3_i1229];
  }

  for (c3_i1230 = 0; c3_i1230 < 6; c3_i1230 = c3_i1230 + 1) {
    c3_dv129[c3_i1230] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_pf_a, c3_xf_b, c3_dv129, c3_se_y);
  for (c3_i1231 = 0; c3_i1231 < 6; c3_i1231 = c3_i1231 + 1) {
    c3_F4[c3_i1231] = (c3_pe_y[c3_i1231] + c3_qe_y[c3_i1231]) - c3_se_y[c3_i1231];
  }

  _SFD_SCRIPT_CALL(0, 241);
  for (c3_i1232 = 0; c3_i1232 < 6; c3_i1232 = c3_i1232 + 1) {
    c3_yf_b[c3_i1232] = c3_F4[c3_i1232];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1233 = 0; c3_i1233 < 6; c3_i1233 = c3_i1233 + 1) {
    c3_te_y[c3_i1233] = c3_yf_b[c3_i1233];
  }

  for (c3_i1234 = 0; c3_i1234 < 6; c3_i1234 = c3_i1234 + 1) {
    c3_ue_y[c3_i1234] = c3_te_y[c3_i1234];
  }

  for (c3_i1235 = 0; c3_i1235 < 6; c3_i1235 = c3_i1235 + 1) {
    c3_ve_y[c3_i1235] = c3_ue_y[c3_i1235];
  }

  for (c3_i1236 = 0; c3_i1236 < 6; c3_i1236 = c3_i1236 + 1) {
    c3_dv130[c3_i1236] = c3_dv10[c3_i1236];
  }

  for (c3_i1237 = 0; c3_i1237 < 6; c3_i1237 = c3_i1237 + 1) {
    c3_we_y[c3_i1237] = c3_ve_y[c3_i1237];
  }

  c3_xe_y = c3_ceval_xdot(chartInstance, 6, c3_dv130, 1, 1, c3_we_y, 1, 1);
  c3_Tau[3] = c3_xe_y;
  _SFD_SCRIPT_CALL(0, 242);
  for (c3_i1238 = 0; c3_i1238 < 6; c3_i1238 = c3_i1238 + 1) {
    c3_JntF[c3_i1238 + 18] = c3_F4[c3_i1238];
  }

  /* Tau(4) = kxi4'* (Adj(g4e)'*F4); */
  /*  Joint 3 */
  _SFD_SCRIPT_CALL(0, 247);
  c3_i1239 = 0;
  for (c3_i1240 = 0; c3_i1240 < 6; c3_i1240 = c3_i1240 + 1) {
    c3_i1241 = 0;
    for (c3_i1242 = 0; c3_i1242 < 6; c3_i1242 = c3_i1242 + 1) {
      c3_qf_a[c3_i1242 + c3_i1239] = c3_Adinvg34[c3_i1241 + c3_i1240];
      c3_i1241 = c3_i1241 + 6;
    }

    c3_i1239 = c3_i1239 + 6;
  }

  for (c3_i1243 = 0; c3_i1243 < 6; c3_i1243 = c3_i1243 + 1) {
    c3_ag_b[c3_i1243] = c3_F4[c3_i1243];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1244 = 0; c3_i1244 < 36; c3_i1244 = c3_i1244 + 1) {
    c3_rf_a[c3_i1244] = c3_qf_a[c3_i1244];
  }

  for (c3_i1245 = 0; c3_i1245 < 6; c3_i1245 = c3_i1245 + 1) {
    c3_bg_b[c3_i1245] = c3_ag_b[c3_i1245];
  }

  for (c3_i1246 = 0; c3_i1246 < 6; c3_i1246 = c3_i1246 + 1) {
    c3_dv131[c3_i1246] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_rf_a, c3_bg_b, c3_dv131, c3_ye_y);
  for (c3_i1247 = 0; c3_i1247 < 36; c3_i1247 = c3_i1247 + 1) {
    c3_sf_a[c3_i1247] = c3_M3[c3_i1247];
  }

  for (c3_i1248 = 0; c3_i1248 < 6; c3_i1248 = c3_i1248 + 1) {
    c3_cg_b[c3_i1248] = c3_dV3[c3_i1248];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1249 = 0; c3_i1249 < 36; c3_i1249 = c3_i1249 + 1) {
    c3_tf_a[c3_i1249] = c3_sf_a[c3_i1249];
  }

  for (c3_i1250 = 0; c3_i1250 < 6; c3_i1250 = c3_i1250 + 1) {
    c3_dg_b[c3_i1250] = c3_cg_b[c3_i1250];
  }

  for (c3_i1251 = 0; c3_i1251 < 6; c3_i1251 = c3_i1251 + 1) {
    c3_dv132[c3_i1251] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_tf_a, c3_dg_b, c3_dv132, c3_af_y);
  for (c3_i1252 = 0; c3_i1252 < 6; c3_i1252 = c3_i1252 + 1) {
    c3_b_V3[c3_i1252] = c3_V3[c3_i1252];
  }

  c3_ad(chartInstance, c3_b_V3, c3_dv133);
  c3_i1253 = 0;
  for (c3_i1254 = 0; c3_i1254 < 6; c3_i1254 = c3_i1254 + 1) {
    c3_i1255 = 0;
    for (c3_i1256 = 0; c3_i1256 < 6; c3_i1256 = c3_i1256 + 1) {
      c3_uf_a[c3_i1256 + c3_i1253] = c3_dv133[c3_i1255 + c3_i1254];
      c3_i1255 = c3_i1255 + 6;
    }

    c3_i1253 = c3_i1253 + 6;
  }

  for (c3_i1257 = 0; c3_i1257 < 36; c3_i1257 = c3_i1257 + 1) {
    c3_eg_b[c3_i1257] = c3_M3[c3_i1257];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1258 = 0; c3_i1258 < 36; c3_i1258 = c3_i1258 + 1) {
    c3_dg_A[c3_i1258] = c3_uf_a[c3_i1258];
  }

  for (c3_i1259 = 0; c3_i1259 < 36; c3_i1259 = c3_i1259 + 1) {
    c3_dg_B[c3_i1259] = c3_eg_b[c3_i1259];
  }

  for (c3_i1260 = 0; c3_i1260 < 36; c3_i1260 = c3_i1260 + 1) {
    c3_eg_A[c3_i1260] = c3_dg_A[c3_i1260];
  }

  for (c3_i1261 = 0; c3_i1261 < 36; c3_i1261 = c3_i1261 + 1) {
    c3_eg_B[c3_i1261] = c3_dg_B[c3_i1261];
  }

  for (c3_i1262 = 0; c3_i1262 < 36; c3_i1262 = c3_i1262 + 1) {
    c3_fg_A[c3_i1262] = c3_eg_A[c3_i1262];
  }

  for (c3_i1263 = 0; c3_i1263 < 36; c3_i1263 = c3_i1263 + 1) {
    c3_fg_B[c3_i1263] = c3_eg_B[c3_i1263];
  }

  for (c3_i1264 = 0; c3_i1264 < 36; c3_i1264 = c3_i1264 + 1) {
    c3_dv134[c3_i1264] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_fg_A, 1, 6, c3_fg_B, 1, 6, 0.0,
                 c3_dv134, 1, 6, c3_bf_y);
  for (c3_i1265 = 0; c3_i1265 < 36; c3_i1265 = c3_i1265 + 1) {
    c3_vf_a[c3_i1265] = c3_bf_y[c3_i1265];
  }

  for (c3_i1266 = 0; c3_i1266 < 6; c3_i1266 = c3_i1266 + 1) {
    c3_fg_b[c3_i1266] = c3_V3[c3_i1266];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1267 = 0; c3_i1267 < 36; c3_i1267 = c3_i1267 + 1) {
    c3_wf_a[c3_i1267] = c3_vf_a[c3_i1267];
  }

  for (c3_i1268 = 0; c3_i1268 < 6; c3_i1268 = c3_i1268 + 1) {
    c3_gg_b[c3_i1268] = c3_fg_b[c3_i1268];
  }

  for (c3_i1269 = 0; c3_i1269 < 6; c3_i1269 = c3_i1269 + 1) {
    c3_dv135[c3_i1269] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_wf_a, c3_gg_b, c3_dv135, c3_cf_y);
  for (c3_i1270 = 0; c3_i1270 < 6; c3_i1270 = c3_i1270 + 1) {
    c3_F3[c3_i1270] = (c3_ye_y[c3_i1270] + c3_af_y[c3_i1270]) - c3_cf_y[c3_i1270];
  }

  _SFD_SCRIPT_CALL(0, 248);
  for (c3_i1271 = 0; c3_i1271 < 6; c3_i1271 = c3_i1271 + 1) {
    c3_hg_b[c3_i1271] = c3_F3[c3_i1271];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1272 = 0; c3_i1272 < 6; c3_i1272 = c3_i1272 + 1) {
    c3_df_y[c3_i1272] = c3_hg_b[c3_i1272];
  }

  for (c3_i1273 = 0; c3_i1273 < 6; c3_i1273 = c3_i1273 + 1) {
    c3_ef_y[c3_i1273] = c3_df_y[c3_i1273];
  }

  for (c3_i1274 = 0; c3_i1274 < 6; c3_i1274 = c3_i1274 + 1) {
    c3_ff_y[c3_i1274] = c3_ef_y[c3_i1274];
  }

  for (c3_i1275 = 0; c3_i1275 < 6; c3_i1275 = c3_i1275 + 1) {
    c3_dv136[c3_i1275] = c3_dv10[c3_i1275];
  }

  for (c3_i1276 = 0; c3_i1276 < 6; c3_i1276 = c3_i1276 + 1) {
    c3_gf_y[c3_i1276] = c3_ff_y[c3_i1276];
  }

  c3_hf_y = c3_ceval_xdot(chartInstance, 6, c3_dv136, 1, 1, c3_gf_y, 1, 1);
  c3_Tau[2] = c3_hf_y;
  _SFD_SCRIPT_CALL(0, 249);
  for (c3_i1277 = 0; c3_i1277 < 6; c3_i1277 = c3_i1277 + 1) {
    c3_JntF[c3_i1277 + 12] = c3_F3[c3_i1277];
  }

  /* Tau(3) = kxi3'* (Adj(g3e)'*F3); */
  /*  Joint 2 */
  _SFD_SCRIPT_CALL(0, 253);
  c3_i1278 = 0;
  for (c3_i1279 = 0; c3_i1279 < 6; c3_i1279 = c3_i1279 + 1) {
    c3_i1280 = 0;
    for (c3_i1281 = 0; c3_i1281 < 6; c3_i1281 = c3_i1281 + 1) {
      c3_xf_a[c3_i1281 + c3_i1278] = c3_Adinvg23[c3_i1280 + c3_i1279];
      c3_i1280 = c3_i1280 + 6;
    }

    c3_i1278 = c3_i1278 + 6;
  }

  for (c3_i1282 = 0; c3_i1282 < 6; c3_i1282 = c3_i1282 + 1) {
    c3_ig_b[c3_i1282] = c3_F3[c3_i1282];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1283 = 0; c3_i1283 < 36; c3_i1283 = c3_i1283 + 1) {
    c3_yf_a[c3_i1283] = c3_xf_a[c3_i1283];
  }

  for (c3_i1284 = 0; c3_i1284 < 6; c3_i1284 = c3_i1284 + 1) {
    c3_jg_b[c3_i1284] = c3_ig_b[c3_i1284];
  }

  for (c3_i1285 = 0; c3_i1285 < 6; c3_i1285 = c3_i1285 + 1) {
    c3_dv137[c3_i1285] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_yf_a, c3_jg_b, c3_dv137, c3_if_y);
  for (c3_i1286 = 0; c3_i1286 < 36; c3_i1286 = c3_i1286 + 1) {
    c3_ag_a[c3_i1286] = c3_M2[c3_i1286];
  }

  for (c3_i1287 = 0; c3_i1287 < 6; c3_i1287 = c3_i1287 + 1) {
    c3_kg_b[c3_i1287] = c3_dV2[c3_i1287];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1288 = 0; c3_i1288 < 36; c3_i1288 = c3_i1288 + 1) {
    c3_bg_a[c3_i1288] = c3_ag_a[c3_i1288];
  }

  for (c3_i1289 = 0; c3_i1289 < 6; c3_i1289 = c3_i1289 + 1) {
    c3_lg_b[c3_i1289] = c3_kg_b[c3_i1289];
  }

  for (c3_i1290 = 0; c3_i1290 < 6; c3_i1290 = c3_i1290 + 1) {
    c3_dv138[c3_i1290] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_bg_a, c3_lg_b, c3_dv138, c3_jf_y);
  for (c3_i1291 = 0; c3_i1291 < 6; c3_i1291 = c3_i1291 + 1) {
    c3_b_V2[c3_i1291] = c3_V2[c3_i1291];
  }

  c3_ad(chartInstance, c3_b_V2, c3_dv139);
  c3_i1292 = 0;
  for (c3_i1293 = 0; c3_i1293 < 6; c3_i1293 = c3_i1293 + 1) {
    c3_i1294 = 0;
    for (c3_i1295 = 0; c3_i1295 < 6; c3_i1295 = c3_i1295 + 1) {
      c3_cg_a[c3_i1295 + c3_i1292] = c3_dv139[c3_i1294 + c3_i1293];
      c3_i1294 = c3_i1294 + 6;
    }

    c3_i1292 = c3_i1292 + 6;
  }

  for (c3_i1296 = 0; c3_i1296 < 36; c3_i1296 = c3_i1296 + 1) {
    c3_mg_b[c3_i1296] = c3_M2[c3_i1296];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1297 = 0; c3_i1297 < 36; c3_i1297 = c3_i1297 + 1) {
    c3_gg_A[c3_i1297] = c3_cg_a[c3_i1297];
  }

  for (c3_i1298 = 0; c3_i1298 < 36; c3_i1298 = c3_i1298 + 1) {
    c3_gg_B[c3_i1298] = c3_mg_b[c3_i1298];
  }

  for (c3_i1299 = 0; c3_i1299 < 36; c3_i1299 = c3_i1299 + 1) {
    c3_hg_A[c3_i1299] = c3_gg_A[c3_i1299];
  }

  for (c3_i1300 = 0; c3_i1300 < 36; c3_i1300 = c3_i1300 + 1) {
    c3_hg_B[c3_i1300] = c3_gg_B[c3_i1300];
  }

  for (c3_i1301 = 0; c3_i1301 < 36; c3_i1301 = c3_i1301 + 1) {
    c3_ig_A[c3_i1301] = c3_hg_A[c3_i1301];
  }

  for (c3_i1302 = 0; c3_i1302 < 36; c3_i1302 = c3_i1302 + 1) {
    c3_ig_B[c3_i1302] = c3_hg_B[c3_i1302];
  }

  for (c3_i1303 = 0; c3_i1303 < 36; c3_i1303 = c3_i1303 + 1) {
    c3_dv140[c3_i1303] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_ig_A, 1, 6, c3_ig_B, 1, 6, 0.0,
                 c3_dv140, 1, 6, c3_kf_y);
  for (c3_i1304 = 0; c3_i1304 < 36; c3_i1304 = c3_i1304 + 1) {
    c3_dg_a[c3_i1304] = c3_kf_y[c3_i1304];
  }

  for (c3_i1305 = 0; c3_i1305 < 6; c3_i1305 = c3_i1305 + 1) {
    c3_ng_b[c3_i1305] = c3_V2[c3_i1305];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1306 = 0; c3_i1306 < 36; c3_i1306 = c3_i1306 + 1) {
    c3_eg_a[c3_i1306] = c3_dg_a[c3_i1306];
  }

  for (c3_i1307 = 0; c3_i1307 < 6; c3_i1307 = c3_i1307 + 1) {
    c3_og_b[c3_i1307] = c3_ng_b[c3_i1307];
  }

  for (c3_i1308 = 0; c3_i1308 < 6; c3_i1308 = c3_i1308 + 1) {
    c3_dv141[c3_i1308] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_eg_a, c3_og_b, c3_dv141, c3_lf_y);
  for (c3_i1309 = 0; c3_i1309 < 6; c3_i1309 = c3_i1309 + 1) {
    c3_F2[c3_i1309] = (c3_if_y[c3_i1309] + c3_jf_y[c3_i1309]) - c3_lf_y[c3_i1309];
  }

  _SFD_SCRIPT_CALL(0, 254);
  for (c3_i1310 = 0; c3_i1310 < 6; c3_i1310 = c3_i1310 + 1) {
    c3_pg_b[c3_i1310] = c3_F2[c3_i1310];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1311 = 0; c3_i1311 < 6; c3_i1311 = c3_i1311 + 1) {
    c3_mf_y[c3_i1311] = c3_pg_b[c3_i1311];
  }

  for (c3_i1312 = 0; c3_i1312 < 6; c3_i1312 = c3_i1312 + 1) {
    c3_nf_y[c3_i1312] = c3_mf_y[c3_i1312];
  }

  for (c3_i1313 = 0; c3_i1313 < 6; c3_i1313 = c3_i1313 + 1) {
    c3_of_y[c3_i1313] = c3_nf_y[c3_i1313];
  }

  for (c3_i1314 = 0; c3_i1314 < 6; c3_i1314 = c3_i1314 + 1) {
    c3_dv142[c3_i1314] = c3_dv10[c3_i1314];
  }

  for (c3_i1315 = 0; c3_i1315 < 6; c3_i1315 = c3_i1315 + 1) {
    c3_pf_y[c3_i1315] = c3_of_y[c3_i1315];
  }

  c3_qf_y = c3_ceval_xdot(chartInstance, 6, c3_dv142, 1, 1, c3_pf_y, 1, 1);
  c3_Tau[1] = c3_qf_y;
  _SFD_SCRIPT_CALL(0, 255);
  for (c3_i1316 = 0; c3_i1316 < 6; c3_i1316 = c3_i1316 + 1) {
    c3_JntF[c3_i1316 + 6] = c3_F2[c3_i1316];
  }

  /* Tau(2) = kxi2'* (Adj(g2e)'*F2); */
  /*  Joint 1 */
  _SFD_SCRIPT_CALL(0, 259);
  c3_i1317 = 0;
  for (c3_i1318 = 0; c3_i1318 < 6; c3_i1318 = c3_i1318 + 1) {
    c3_i1319 = 0;
    for (c3_i1320 = 0; c3_i1320 < 6; c3_i1320 = c3_i1320 + 1) {
      c3_fg_a[c3_i1320 + c3_i1317] = c3_Adinvg12[c3_i1319 + c3_i1318];
      c3_i1319 = c3_i1319 + 6;
    }

    c3_i1317 = c3_i1317 + 6;
  }

  for (c3_i1321 = 0; c3_i1321 < 6; c3_i1321 = c3_i1321 + 1) {
    c3_qg_b[c3_i1321] = c3_F2[c3_i1321];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1322 = 0; c3_i1322 < 36; c3_i1322 = c3_i1322 + 1) {
    c3_gg_a[c3_i1322] = c3_fg_a[c3_i1322];
  }

  for (c3_i1323 = 0; c3_i1323 < 6; c3_i1323 = c3_i1323 + 1) {
    c3_rg_b[c3_i1323] = c3_qg_b[c3_i1323];
  }

  for (c3_i1324 = 0; c3_i1324 < 6; c3_i1324 = c3_i1324 + 1) {
    c3_dv143[c3_i1324] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_gg_a, c3_rg_b, c3_dv143, c3_rf_y);
  for (c3_i1325 = 0; c3_i1325 < 36; c3_i1325 = c3_i1325 + 1) {
    c3_hg_a[c3_i1325] = c3_M1[c3_i1325];
  }

  for (c3_i1326 = 0; c3_i1326 < 6; c3_i1326 = c3_i1326 + 1) {
    c3_sg_b[c3_i1326] = c3_dV1[c3_i1326];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1327 = 0; c3_i1327 < 36; c3_i1327 = c3_i1327 + 1) {
    c3_ig_a[c3_i1327] = c3_hg_a[c3_i1327];
  }

  for (c3_i1328 = 0; c3_i1328 < 6; c3_i1328 = c3_i1328 + 1) {
    c3_tg_b[c3_i1328] = c3_sg_b[c3_i1328];
  }

  for (c3_i1329 = 0; c3_i1329 < 6; c3_i1329 = c3_i1329 + 1) {
    c3_dv144[c3_i1329] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_ig_a, c3_tg_b, c3_dv144, c3_sf_y);
  for (c3_i1330 = 0; c3_i1330 < 6; c3_i1330 = c3_i1330 + 1) {
    c3_b_V1[c3_i1330] = c3_V1[c3_i1330];
  }

  c3_ad(chartInstance, c3_b_V1, c3_dv145);
  c3_i1331 = 0;
  for (c3_i1332 = 0; c3_i1332 < 6; c3_i1332 = c3_i1332 + 1) {
    c3_i1333 = 0;
    for (c3_i1334 = 0; c3_i1334 < 6; c3_i1334 = c3_i1334 + 1) {
      c3_jg_a[c3_i1334 + c3_i1331] = c3_dv145[c3_i1333 + c3_i1332];
      c3_i1333 = c3_i1333 + 6;
    }

    c3_i1331 = c3_i1331 + 6;
  }

  for (c3_i1335 = 0; c3_i1335 < 36; c3_i1335 = c3_i1335 + 1) {
    c3_ug_b[c3_i1335] = c3_M1[c3_i1335];
  }

  c3_i_eml_scalar_eg(chartInstance);
  c3_i_eml_scalar_eg(chartInstance);
  for (c3_i1336 = 0; c3_i1336 < 36; c3_i1336 = c3_i1336 + 1) {
    c3_jg_A[c3_i1336] = c3_jg_a[c3_i1336];
  }

  for (c3_i1337 = 0; c3_i1337 < 36; c3_i1337 = c3_i1337 + 1) {
    c3_jg_B[c3_i1337] = c3_ug_b[c3_i1337];
  }

  for (c3_i1338 = 0; c3_i1338 < 36; c3_i1338 = c3_i1338 + 1) {
    c3_kg_A[c3_i1338] = c3_jg_A[c3_i1338];
  }

  for (c3_i1339 = 0; c3_i1339 < 36; c3_i1339 = c3_i1339 + 1) {
    c3_kg_B[c3_i1339] = c3_jg_B[c3_i1339];
  }

  for (c3_i1340 = 0; c3_i1340 < 36; c3_i1340 = c3_i1340 + 1) {
    c3_lg_A[c3_i1340] = c3_kg_A[c3_i1340];
  }

  for (c3_i1341 = 0; c3_i1341 < 36; c3_i1341 = c3_i1341 + 1) {
    c3_lg_B[c3_i1341] = c3_kg_B[c3_i1341];
  }

  for (c3_i1342 = 0; c3_i1342 < 36; c3_i1342 = c3_i1342 + 1) {
    c3_dv146[c3_i1342] = 0.0;
  }

  c3_ceval_xgemm(chartInstance, 6, 6, 6, 1.0, c3_lg_A, 1, 6, c3_lg_B, 1, 6, 0.0,
                 c3_dv146, 1, 6, c3_tf_y);
  for (c3_i1343 = 0; c3_i1343 < 36; c3_i1343 = c3_i1343 + 1) {
    c3_kg_a[c3_i1343] = c3_tf_y[c3_i1343];
  }

  for (c3_i1344 = 0; c3_i1344 < 6; c3_i1344 = c3_i1344 + 1) {
    c3_vg_b[c3_i1344] = c3_V1[c3_i1344];
  }

  c3_h_eml_scalar_eg(chartInstance);
  c3_h_eml_scalar_eg(chartInstance);
  for (c3_i1345 = 0; c3_i1345 < 36; c3_i1345 = c3_i1345 + 1) {
    c3_lg_a[c3_i1345] = c3_kg_a[c3_i1345];
  }

  for (c3_i1346 = 0; c3_i1346 < 6; c3_i1346 = c3_i1346 + 1) {
    c3_wg_b[c3_i1346] = c3_vg_b[c3_i1346];
  }

  for (c3_i1347 = 0; c3_i1347 < 6; c3_i1347 = c3_i1347 + 1) {
    c3_dv147[c3_i1347] = 0.0;
  }

  c3_eml_xgemm(chartInstance, c3_lg_a, c3_wg_b, c3_dv147, c3_uf_y);
  for (c3_i1348 = 0; c3_i1348 < 6; c3_i1348 = c3_i1348 + 1) {
    c3_F1[c3_i1348] = (c3_rf_y[c3_i1348] + c3_sf_y[c3_i1348]) - c3_uf_y[c3_i1348];
  }

  _SFD_SCRIPT_CALL(0, 260);
  for (c3_i1349 = 0; c3_i1349 < 6; c3_i1349 = c3_i1349 + 1) {
    c3_xg_b[c3_i1349] = c3_F1[c3_i1349];
  }

  c3_j_eml_scalar_eg(chartInstance);
  for (c3_i1350 = 0; c3_i1350 < 6; c3_i1350 = c3_i1350 + 1) {
    c3_vf_y[c3_i1350] = c3_xg_b[c3_i1350];
  }

  for (c3_i1351 = 0; c3_i1351 < 6; c3_i1351 = c3_i1351 + 1) {
    c3_wf_y[c3_i1351] = c3_vf_y[c3_i1351];
  }

  for (c3_i1352 = 0; c3_i1352 < 6; c3_i1352 = c3_i1352 + 1) {
    c3_xf_y[c3_i1352] = c3_wf_y[c3_i1352];
  }

  for (c3_i1353 = 0; c3_i1353 < 6; c3_i1353 = c3_i1353 + 1) {
    c3_dv148[c3_i1353] = c3_dv10[c3_i1353];
  }

  for (c3_i1354 = 0; c3_i1354 < 6; c3_i1354 = c3_i1354 + 1) {
    c3_yf_y[c3_i1354] = c3_xf_y[c3_i1354];
  }

  c3_ag_y = c3_ceval_xdot(chartInstance, 6, c3_dv148, 1, 1, c3_yf_y, 1, 1);
  c3_Tau[0] = c3_ag_y;
  _SFD_SCRIPT_CALL(0, 261);
  for (c3_i1355 = 0; c3_i1355 < 6; c3_i1355 = c3_i1355 + 1) {
    c3_JntF[c3_i1355] = c3_F1[c3_i1355];
  }

  /* Tau(1) = kxi1'* (Adj(g1e)'*F1); */
  _SFD_SCRIPT_CALL(0, 264);
  for (c3_i1356 = 0; c3_i1356 < 6; c3_i1356 = c3_i1356 + 1) {
    c3_Torque[c3_i1356] = c3_Tau[c3_i1356];
  }

  _SFD_SCRIPT_CALL(0, -264);
  sf_debug_symbol_scope_pop();
}

static void c3_expg(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                    real_T c3_xi[6], real_T c3_theta, real_T c3_g[16])
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
  int32_T c3_i1357;
  int32_T c3_i1358;
  int32_T c3_i1359;
  real_T c3_b_w[3];
  real_T c3_dv149[9];
  int32_T c3_i1360;
  int32_T c3_i1361;
  real_T c3_a[3];
  real_T c3_b;
  int32_T c3_i1362;
  real_T c3_b_a;
  real_T c3_b_b;
  int32_T c3_i1363;
  real_T c3_A[3];
  real_T c3_B;
  int32_T c3_i1364;
  real_T c3_x[3];
  real_T c3_y;
  int32_T c3_i1365;
  real_T c3_b_x[3];
  real_T c3_b_y;
  int32_T c3_i1366;
  real_T c3_c_x[3];
  real_T c3_c_y;
  int32_T c3_i1367;
  int32_T c3_i1368;
  real_T c3_b_A[3];
  real_T c3_b_B;
  int32_T c3_i1369;
  real_T c3_d_x[3];
  real_T c3_d_y;
  int32_T c3_i1370;
  real_T c3_e_x[3];
  real_T c3_e_y;
  int32_T c3_i1371;
  real_T c3_f_x[3];
  real_T c3_f_y;
  int32_T c3_i1372;
  int32_T c3_i1373;
  real_T c3_c_w[3];
  real_T c3_dv150[9];
  int32_T c3_i1374;
  real_T c3_dv151[9];
  int32_T c3_i1375;
  real_T c3_c_a[9];
  int32_T c3_i1376;
  real_T c3_d_w[3];
  real_T c3_c_b[9];
  int32_T c3_i1377;
  real_T c3_c_A[9];
  int32_T c3_i1378;
  real_T c3_c_B[9];
  int32_T c3_i1379;
  real_T c3_d_A[9];
  int32_T c3_i1380;
  real_T c3_d_B[9];
  int32_T c3_i1381;
  real_T c3_e_A[9];
  int32_T c3_i1382;
  real_T c3_e_B[9];
  int32_T c3_i1383;
  int32_T c3_i1384;
  int32_T c3_i1385;
  real_T c3_g_y[9];
  int32_T c3_i1386;
  int32_T c3_i1387;
  int32_T c3_i1388;
  real_T c3_d_a[9];
  int32_T c3_i1389;
  real_T c3_d_b[3];
  int32_T c3_i1390;
  real_T c3_f_A[9];
  int32_T c3_i1391;
  real_T c3_f_B[3];
  int32_T c3_i1392;
  real_T c3_g_A[9];
  int32_T c3_i1393;
  real_T c3_g_B[3];
  int32_T c3_i1394;
  real_T c3_h_A[9];
  int32_T c3_i1395;
  real_T c3_h_B[3];
  int32_T c3_i1396;
  real_T c3_h_y[3];
  int32_T c3_i1397;
  int32_T c3_i1398;
  int32_T c3_i1399;
  real_T c3_e_a[3];
  int32_T c3_i1400;
  real_T c3_e_b[3];
  int32_T c3_i1401;
  int32_T c3_i1402;
  int32_T c3_i1403;
  real_T c3_i_y[9];
  int32_T c3_i1404;
  real_T c3_f_a[9];
  real_T c3_f_b;
  int32_T c3_i1405;
  real_T c3_j_y[9];
  int32_T c3_i1406;
  real_T c3_g_a[9];
  int32_T c3_i1407;
  real_T c3_g_b[3];
  int32_T c3_i1408;
  real_T c3_i_A[9];
  int32_T c3_i1409;
  real_T c3_i_B[3];
  int32_T c3_i1410;
  real_T c3_j_A[9];
  int32_T c3_i1411;
  real_T c3_j_B[3];
  int32_T c3_i1412;
  real_T c3_k_A[9];
  int32_T c3_i1413;
  real_T c3_k_B[3];
  int32_T c3_i1414;
  real_T c3_k_y[3];
  int32_T c3_i1415;
  int32_T c3_i1416;
  int32_T c3_i1417;
  int32_T c3_i1418;
  int32_T c3_i1419;
  int32_T c3_i1420;
  int32_T c3_i1421;
  int32_T c3_i1422;
  int32_T c3_i1423;
  int32_T c3_i1424;
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
  for (c3_i1357 = 0; c3_i1357 < 3; c3_i1357 = c3_i1357 + 1) {
    c3_v[c3_i1357] = c3_xi[c3_i1357];
  }

  _SFD_SCRIPT_CALL(1, 3);
  for (c3_i1358 = 0; c3_i1358 < 3; c3_i1358 = c3_i1358 + 1) {
    c3_w[c3_i1358] = c3_xi[c3_i1358 + 3];
  }

  _SFD_SCRIPT_CALL(1, 4);
  for (c3_i1359 = 0; c3_i1359 < 3; c3_i1359 = c3_i1359 + 1) {
    c3_b_w[c3_i1359] = c3_w[c3_i1359];
  }

  c3_n = c3_norm(chartInstance, c3_b_w);
  _SFD_SCRIPT_CALL(1, 6);
  c3_eps(chartInstance);
  if (CV_SCRIPT_IF(1, 0, c3_n < 2.2204460492503131E-16)) {
    _SFD_SCRIPT_CALL(1, 7);
    c3_eye(chartInstance, c3_dv149);
    for (c3_i1360 = 0; c3_i1360 < 9; c3_i1360 = c3_i1360 + 1) {
      c3_R[c3_i1360] = c3_dv149[c3_i1360];
    }

    _SFD_SCRIPT_CALL(1, 8);
    for (c3_i1361 = 0; c3_i1361 < 3; c3_i1361 = c3_i1361 + 1) {
      c3_a[c3_i1361] = c3_v[c3_i1361];
    }

    c3_b = c3_theta;
    for (c3_i1362 = 0; c3_i1362 < 3; c3_i1362 = c3_i1362 + 1) {
      c3_P[c3_i1362] = c3_a[c3_i1362] * c3_b;
    }
  } else {
    _SFD_SCRIPT_CALL(1, 10);
    c3_b_a = c3_theta;
    c3_b_b = c3_n;
    c3_theta = c3_b_a * c3_b_b;
    _SFD_SCRIPT_CALL(1, 11);
    for (c3_i1363 = 0; c3_i1363 < 3; c3_i1363 = c3_i1363 + 1) {
      c3_A[c3_i1363] = c3_w[c3_i1363];
    }

    c3_B = c3_n;
    for (c3_i1364 = 0; c3_i1364 < 3; c3_i1364 = c3_i1364 + 1) {
      c3_x[c3_i1364] = c3_A[c3_i1364];
    }

    c3_y = c3_B;
    for (c3_i1365 = 0; c3_i1365 < 3; c3_i1365 = c3_i1365 + 1) {
      c3_b_x[c3_i1365] = c3_x[c3_i1365];
    }

    c3_b_y = c3_y;
    for (c3_i1366 = 0; c3_i1366 < 3; c3_i1366 = c3_i1366 + 1) {
      c3_c_x[c3_i1366] = c3_b_x[c3_i1366];
    }

    c3_c_y = c3_b_y;
    for (c3_i1367 = 0; c3_i1367 < 3; c3_i1367 = c3_i1367 + 1) {
      c3_w[c3_i1367] = c3_c_x[c3_i1367] / c3_c_y;
    }

    _SFD_SCRIPT_CALL(1, 12);
    for (c3_i1368 = 0; c3_i1368 < 3; c3_i1368 = c3_i1368 + 1) {
      c3_b_A[c3_i1368] = c3_v[c3_i1368];
    }

    c3_b_B = c3_n;
    for (c3_i1369 = 0; c3_i1369 < 3; c3_i1369 = c3_i1369 + 1) {
      c3_d_x[c3_i1369] = c3_b_A[c3_i1369];
    }

    c3_d_y = c3_b_B;
    for (c3_i1370 = 0; c3_i1370 < 3; c3_i1370 = c3_i1370 + 1) {
      c3_e_x[c3_i1370] = c3_d_x[c3_i1370];
    }

    c3_e_y = c3_d_y;
    for (c3_i1371 = 0; c3_i1371 < 3; c3_i1371 = c3_i1371 + 1) {
      c3_f_x[c3_i1371] = c3_e_x[c3_i1371];
    }

    c3_f_y = c3_e_y;
    for (c3_i1372 = 0; c3_i1372 < 3; c3_i1372 = c3_i1372 + 1) {
      c3_v[c3_i1372] = c3_f_x[c3_i1372] / c3_f_y;
    }

    _SFD_SCRIPT_CALL(1, 13);
    for (c3_i1373 = 0; c3_i1373 < 3; c3_i1373 = c3_i1373 + 1) {
      c3_c_w[c3_i1373] = c3_w[c3_i1373];
    }

    c3_expr(chartInstance, c3_c_w, c3_theta, c3_dv150);
    for (c3_i1374 = 0; c3_i1374 < 9; c3_i1374 = c3_i1374 + 1) {
      c3_R[c3_i1374] = c3_dv150[c3_i1374];
    }

    _SFD_SCRIPT_CALL(1, 14);
    c3_eye(chartInstance, c3_dv151);
    for (c3_i1375 = 0; c3_i1375 < 9; c3_i1375 = c3_i1375 + 1) {
      c3_c_a[c3_i1375] = c3_dv151[c3_i1375] - c3_R[c3_i1375];
    }

    for (c3_i1376 = 0; c3_i1376 < 3; c3_i1376 = c3_i1376 + 1) {
      c3_d_w[c3_i1376] = c3_w[c3_i1376];
    }

    c3_hat(chartInstance, c3_d_w, c3_c_b);
    c3_c_eml_scalar_eg(chartInstance);
    c3_c_eml_scalar_eg(chartInstance);
    for (c3_i1377 = 0; c3_i1377 < 9; c3_i1377 = c3_i1377 + 1) {
      c3_c_A[c3_i1377] = c3_c_a[c3_i1377];
    }

    for (c3_i1378 = 0; c3_i1378 < 9; c3_i1378 = c3_i1378 + 1) {
      c3_c_B[c3_i1378] = c3_c_b[c3_i1378];
    }

    for (c3_i1379 = 0; c3_i1379 < 9; c3_i1379 = c3_i1379 + 1) {
      c3_d_A[c3_i1379] = c3_c_A[c3_i1379];
    }

    for (c3_i1380 = 0; c3_i1380 < 9; c3_i1380 = c3_i1380 + 1) {
      c3_d_B[c3_i1380] = c3_c_B[c3_i1380];
    }

    for (c3_i1381 = 0; c3_i1381 < 9; c3_i1381 = c3_i1381 + 1) {
      c3_e_A[c3_i1381] = c3_d_A[c3_i1381];
    }

    for (c3_i1382 = 0; c3_i1382 < 9; c3_i1382 = c3_i1382 + 1) {
      c3_e_B[c3_i1382] = c3_d_B[c3_i1382];
    }

    for (c3_i1383 = 0; c3_i1383 < 3; c3_i1383 = c3_i1383 + 1) {
      c3_i1384 = 0;
      for (c3_i1385 = 0; c3_i1385 < 3; c3_i1385 = c3_i1385 + 1) {
        c3_g_y[c3_i1384 + c3_i1383] = 0.0;
        c3_i1386 = 0;
        for (c3_i1387 = 0; c3_i1387 < 3; c3_i1387 = c3_i1387 + 1) {
          c3_g_y[c3_i1384 + c3_i1383] = c3_g_y[c3_i1384 + c3_i1383] +
            c3_e_A[c3_i1386 + c3_i1383] * c3_e_B[c3_i1387 + c3_i1384];
          c3_i1386 = c3_i1386 + 3;
        }

        c3_i1384 = c3_i1384 + 3;
      }
    }

    for (c3_i1388 = 0; c3_i1388 < 9; c3_i1388 = c3_i1388 + 1) {
      c3_d_a[c3_i1388] = c3_g_y[c3_i1388];
    }

    for (c3_i1389 = 0; c3_i1389 < 3; c3_i1389 = c3_i1389 + 1) {
      c3_d_b[c3_i1389] = c3_v[c3_i1389];
    }

    c3_d_eml_scalar_eg(chartInstance);
    c3_d_eml_scalar_eg(chartInstance);
    for (c3_i1390 = 0; c3_i1390 < 9; c3_i1390 = c3_i1390 + 1) {
      c3_f_A[c3_i1390] = c3_d_a[c3_i1390];
    }

    for (c3_i1391 = 0; c3_i1391 < 3; c3_i1391 = c3_i1391 + 1) {
      c3_f_B[c3_i1391] = c3_d_b[c3_i1391];
    }

    for (c3_i1392 = 0; c3_i1392 < 9; c3_i1392 = c3_i1392 + 1) {
      c3_g_A[c3_i1392] = c3_f_A[c3_i1392];
    }

    for (c3_i1393 = 0; c3_i1393 < 3; c3_i1393 = c3_i1393 + 1) {
      c3_g_B[c3_i1393] = c3_f_B[c3_i1393];
    }

    for (c3_i1394 = 0; c3_i1394 < 9; c3_i1394 = c3_i1394 + 1) {
      c3_h_A[c3_i1394] = c3_g_A[c3_i1394];
    }

    for (c3_i1395 = 0; c3_i1395 < 3; c3_i1395 = c3_i1395 + 1) {
      c3_h_B[c3_i1395] = c3_g_B[c3_i1395];
    }

    for (c3_i1396 = 0; c3_i1396 < 3; c3_i1396 = c3_i1396 + 1) {
      c3_h_y[c3_i1396] = 0.0;
      c3_i1397 = 0;
      for (c3_i1398 = 0; c3_i1398 < 3; c3_i1398 = c3_i1398 + 1) {
        c3_h_y[c3_i1396] = c3_h_y[c3_i1396] + c3_h_A[c3_i1397 + c3_i1396] *
          c3_h_B[c3_i1398];
        c3_i1397 = c3_i1397 + 3;
      }
    }

    for (c3_i1399 = 0; c3_i1399 < 3; c3_i1399 = c3_i1399 + 1) {
      c3_e_a[c3_i1399] = c3_w[c3_i1399];
    }

    for (c3_i1400 = 0; c3_i1400 < 3; c3_i1400 = c3_i1400 + 1) {
      c3_e_b[c3_i1400] = c3_w[c3_i1400];
    }

    c3_i1401 = 0;
    for (c3_i1402 = 0; c3_i1402 < 3; c3_i1402 = c3_i1402 + 1) {
      for (c3_i1403 = 0; c3_i1403 < 3; c3_i1403 = c3_i1403 + 1) {
        c3_i_y[c3_i1403 + c3_i1401] = c3_e_a[c3_i1403] * c3_e_b[c3_i1402];
      }

      c3_i1401 = c3_i1401 + 3;
    }

    for (c3_i1404 = 0; c3_i1404 < 9; c3_i1404 = c3_i1404 + 1) {
      c3_f_a[c3_i1404] = c3_i_y[c3_i1404];
    }

    c3_f_b = c3_theta;
    for (c3_i1405 = 0; c3_i1405 < 9; c3_i1405 = c3_i1405 + 1) {
      c3_j_y[c3_i1405] = c3_f_a[c3_i1405] * c3_f_b;
    }

    for (c3_i1406 = 0; c3_i1406 < 9; c3_i1406 = c3_i1406 + 1) {
      c3_g_a[c3_i1406] = c3_j_y[c3_i1406];
    }

    for (c3_i1407 = 0; c3_i1407 < 3; c3_i1407 = c3_i1407 + 1) {
      c3_g_b[c3_i1407] = c3_v[c3_i1407];
    }

    c3_d_eml_scalar_eg(chartInstance);
    c3_d_eml_scalar_eg(chartInstance);
    for (c3_i1408 = 0; c3_i1408 < 9; c3_i1408 = c3_i1408 + 1) {
      c3_i_A[c3_i1408] = c3_g_a[c3_i1408];
    }

    for (c3_i1409 = 0; c3_i1409 < 3; c3_i1409 = c3_i1409 + 1) {
      c3_i_B[c3_i1409] = c3_g_b[c3_i1409];
    }

    for (c3_i1410 = 0; c3_i1410 < 9; c3_i1410 = c3_i1410 + 1) {
      c3_j_A[c3_i1410] = c3_i_A[c3_i1410];
    }

    for (c3_i1411 = 0; c3_i1411 < 3; c3_i1411 = c3_i1411 + 1) {
      c3_j_B[c3_i1411] = c3_i_B[c3_i1411];
    }

    for (c3_i1412 = 0; c3_i1412 < 9; c3_i1412 = c3_i1412 + 1) {
      c3_k_A[c3_i1412] = c3_j_A[c3_i1412];
    }

    for (c3_i1413 = 0; c3_i1413 < 3; c3_i1413 = c3_i1413 + 1) {
      c3_k_B[c3_i1413] = c3_j_B[c3_i1413];
    }

    for (c3_i1414 = 0; c3_i1414 < 3; c3_i1414 = c3_i1414 + 1) {
      c3_k_y[c3_i1414] = 0.0;
      c3_i1415 = 0;
      for (c3_i1416 = 0; c3_i1416 < 3; c3_i1416 = c3_i1416 + 1) {
        c3_k_y[c3_i1414] = c3_k_y[c3_i1414] + c3_k_A[c3_i1415 + c3_i1414] *
          c3_k_B[c3_i1416];
        c3_i1415 = c3_i1415 + 3;
      }
    }

    for (c3_i1417 = 0; c3_i1417 < 3; c3_i1417 = c3_i1417 + 1) {
      c3_P[c3_i1417] = c3_h_y[c3_i1417] + c3_k_y[c3_i1417];
    }
  }

  _SFD_SCRIPT_CALL(1, 17);
  c3_i1418 = 0;
  c3_i1419 = 0;
  for (c3_i1420 = 0; c3_i1420 < 3; c3_i1420 = c3_i1420 + 1) {
    for (c3_i1421 = 0; c3_i1421 < 3; c3_i1421 = c3_i1421 + 1) {
      c3_g[c3_i1421 + c3_i1418] = c3_R[c3_i1421 + c3_i1419];
    }

    c3_i1418 = c3_i1418 + 4;
    c3_i1419 = c3_i1419 + 3;
  }

  for (c3_i1422 = 0; c3_i1422 < 3; c3_i1422 = c3_i1422 + 1) {
    c3_g[c3_i1422 + 12] = c3_P[c3_i1422];
  }

  c3_i1423 = 0;
  for (c3_i1424 = 0; c3_i1424 < 4; c3_i1424 = c3_i1424 + 1) {
    c3_g[c3_i1423 + 3] = c3_dv152[c3_i1424];
    c3_i1423 = c3_i1423 + 4;
  }

  _SFD_SCRIPT_CALL(1, -17);
  sf_debug_symbol_scope_pop();
}

static real_T c3_norm(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c3_x[3])
{
  int32_T c3_i1425;
  real_T c3_b_x[3];
  int32_T c3_i1426;
  real_T c3_c_x[3];
  int32_T c3_i1427;
  real_T c3_d_x[3];
  int32_T c3_i1428;
  real_T c3_e_x[3];
  for (c3_i1425 = 0; c3_i1425 < 3; c3_i1425 = c3_i1425 + 1) {
    c3_b_x[c3_i1425] = c3_x[c3_i1425];
  }

  for (c3_i1426 = 0; c3_i1426 < 3; c3_i1426 = c3_i1426 + 1) {
    c3_c_x[c3_i1426] = c3_b_x[c3_i1426];
  }

  for (c3_i1427 = 0; c3_i1427 < 3; c3_i1427 = c3_i1427 + 1) {
    c3_d_x[c3_i1427] = c3_c_x[c3_i1427];
  }

  for (c3_i1428 = 0; c3_i1428 < 3; c3_i1428 = c3_i1428 + 1) {
    c3_e_x[c3_i1428] = c3_d_x[c3_i1428];
  }

  return c3_ceval_xnrm2(chartInstance, 3, c3_e_x, 1, 1);
}

static real_T c3_ceval_xnrm2(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[3], int32_T c3_ix0,
  int32_T c3_incx)
{
  return dnrm232(&c3_n, &c3_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 3, 1, 0) - 1], &
                 c3_incx);
}

static void c3_eps(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static void c3_isVariableSizing(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_eye(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                   real_T c3_I[9])
{
  int32_T c3_i1429;
  int32_T c3_i;
  int32_T c3_b_i;
  c3_isVariableSizing(chartInstance);
  for (c3_i1429 = 0; c3_i1429 < 9; c3_i1429 = c3_i1429 + 1) {
    c3_I[c3_i1429] = 0.0;
  }

  for (c3_i = 1; c3_i < 4; c3_i = c3_i + 1) {
    c3_b_i = c3_i;
    c3_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_b_i), 1, 3, 1, 0) - 1) + 3 * (
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_b_i), 1, 3, 2, 0) - 1)] = 1.0;
  }
}

static void c3_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_expr(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                    real_T c3_w[3], real_T c3_theta, real_T c3_R[9])
{
  uint32_T c3_debug_family_var_map[6];
  real_T c3_n;
  real_T c3_nargin = 2.0;
  real_T c3_nargout = 1.0;
  int32_T c3_i1430;
  real_T c3_b_w[3];
  real_T c3_dv153[9];
  int32_T c3_i1431;
  int32_T c3_i1432;
  real_T c3_c_w[3];
  uint32_T c3_b_debug_family_var_map[4];
  real_T c3_b_nargin = 1.0;
  real_T c3_b_nargout = 1.0;
  real_T c3_W[9];
  int32_T c3_i1433;
  real_T c3_A[9];
  real_T c3_B;
  int32_T c3_i1434;
  real_T c3_x[9];
  real_T c3_y;
  int32_T c3_i1435;
  real_T c3_b_x[9];
  real_T c3_b_y;
  int32_T c3_i1436;
  real_T c3_c_x[9];
  real_T c3_c_y;
  int32_T c3_i1437;
  real_T c3_d_y[9];
  real_T c3_a;
  real_T c3_b;
  real_T c3_e_y;
  real_T c3_d_x;
  real_T c3_e_x;
  real_T c3_f_x;
  int32_T c3_i1438;
  real_T c3_b_a[9];
  real_T c3_b_b;
  int32_T c3_i1439;
  real_T c3_f_y[9];
  int32_T c3_i1440;
  real_T c3_d_w[3];
  uint32_T c3_c_debug_family_var_map[4];
  real_T c3_c_nargin = 1.0;
  real_T c3_c_nargout = 1.0;
  real_T c3_b_W[9];
  int32_T c3_i1441;
  real_T c3_c_a[9];
  int32_T c3_i1442;
  real_T c3_d_a[9];
  real_T c3_c[9];
  real_T c3_e_a;
  real_T c3_b_c;
  int32_T c3_i1443;
  real_T c3_b_A[9];
  real_T c3_b_B;
  int32_T c3_i1444;
  real_T c3_g_x[9];
  real_T c3_g_y;
  int32_T c3_i1445;
  real_T c3_h_x[9];
  real_T c3_h_y;
  int32_T c3_i1446;
  real_T c3_i_x[9];
  real_T c3_i_y;
  int32_T c3_i1447;
  real_T c3_j_y[9];
  real_T c3_f_a;
  real_T c3_c_b;
  real_T c3_k_y;
  real_T c3_j_x;
  real_T c3_k_x;
  real_T c3_l_x;
  int32_T c3_i1448;
  real_T c3_g_a[9];
  real_T c3_d_b;
  int32_T c3_i1449;
  real_T c3_l_y[9];
  real_T c3_dv154[9];
  int32_T c3_i1450;
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
  for (c3_i1430 = 0; c3_i1430 < 3; c3_i1430 = c3_i1430 + 1) {
    c3_b_w[c3_i1430] = c3_w[c3_i1430];
  }

  c3_n = c3_norm(chartInstance, c3_b_w);
  _SFD_SCRIPT_CALL(2, 4);
  if (CV_SCRIPT_IF(2, 0, c3_n < 2.2204460492503131E-16)) {
    _SFD_SCRIPT_CALL(2, 5);
    c3_eye(chartInstance, c3_dv153);
    for (c3_i1431 = 0; c3_i1431 < 9; c3_i1431 = c3_i1431 + 1) {
      c3_R[c3_i1431] = c3_dv153[c3_i1431];
    }
  } else {
    /* theta = theta*n; */
    /* w = w/n; */
    _SFD_SCRIPT_CALL(2, 9);
    for (c3_i1432 = 0; c3_i1432 < 3; c3_i1432 = c3_i1432 + 1) {
      c3_c_w[c3_i1432] = c3_w[c3_i1432];
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
    for (c3_i1433 = 0; c3_i1433 < 9; c3_i1433 = c3_i1433 + 1) {
      c3_A[c3_i1433] = c3_W[c3_i1433];
    }

    c3_B = c3_n;
    for (c3_i1434 = 0; c3_i1434 < 9; c3_i1434 = c3_i1434 + 1) {
      c3_x[c3_i1434] = c3_A[c3_i1434];
    }

    c3_y = c3_B;
    for (c3_i1435 = 0; c3_i1435 < 9; c3_i1435 = c3_i1435 + 1) {
      c3_b_x[c3_i1435] = c3_x[c3_i1435];
    }

    c3_b_y = c3_y;
    for (c3_i1436 = 0; c3_i1436 < 9; c3_i1436 = c3_i1436 + 1) {
      c3_c_x[c3_i1436] = c3_b_x[c3_i1436];
    }

    c3_c_y = c3_b_y;
    for (c3_i1437 = 0; c3_i1437 < 9; c3_i1437 = c3_i1437 + 1) {
      c3_d_y[c3_i1437] = c3_c_x[c3_i1437] / c3_c_y;
    }

    c3_a = c3_n;
    c3_b = c3_theta;
    c3_e_y = c3_a * c3_b;
    c3_d_x = c3_e_y;
    c3_e_x = c3_d_x;
    c3_f_x = c3_e_x;
    c3_e_x = c3_f_x;
    c3_e_x = muDoubleScalarSin(c3_e_x);
    for (c3_i1438 = 0; c3_i1438 < 9; c3_i1438 = c3_i1438 + 1) {
      c3_b_a[c3_i1438] = c3_d_y[c3_i1438];
    }

    c3_b_b = c3_e_x;
    for (c3_i1439 = 0; c3_i1439 < 9; c3_i1439 = c3_i1439 + 1) {
      c3_f_y[c3_i1439] = c3_b_a[c3_i1439] * c3_b_b;
    }

    for (c3_i1440 = 0; c3_i1440 < 3; c3_i1440 = c3_i1440 + 1) {
      c3_d_w[c3_i1440] = c3_w[c3_i1440];
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
    for (c3_i1441 = 0; c3_i1441 < 9; c3_i1441 = c3_i1441 + 1) {
      c3_c_a[c3_i1441] = c3_b_W[c3_i1441];
    }

    for (c3_i1442 = 0; c3_i1442 < 9; c3_i1442 = c3_i1442 + 1) {
      c3_d_a[c3_i1442] = c3_c_a[c3_i1442];
    }

    c3_matrix_to_integer_power(chartInstance, c3_d_a, 2.0, c3_c);
    c3_e_a = c3_n;
    c3_b_c = c3_power(chartInstance, c3_e_a, 2.0);
    for (c3_i1443 = 0; c3_i1443 < 9; c3_i1443 = c3_i1443 + 1) {
      c3_b_A[c3_i1443] = c3_c[c3_i1443];
    }

    c3_b_B = c3_b_c;
    for (c3_i1444 = 0; c3_i1444 < 9; c3_i1444 = c3_i1444 + 1) {
      c3_g_x[c3_i1444] = c3_b_A[c3_i1444];
    }

    c3_g_y = c3_b_B;
    for (c3_i1445 = 0; c3_i1445 < 9; c3_i1445 = c3_i1445 + 1) {
      c3_h_x[c3_i1445] = c3_g_x[c3_i1445];
    }

    c3_h_y = c3_g_y;
    for (c3_i1446 = 0; c3_i1446 < 9; c3_i1446 = c3_i1446 + 1) {
      c3_i_x[c3_i1446] = c3_h_x[c3_i1446];
    }

    c3_i_y = c3_h_y;
    for (c3_i1447 = 0; c3_i1447 < 9; c3_i1447 = c3_i1447 + 1) {
      c3_j_y[c3_i1447] = c3_i_x[c3_i1447] / c3_i_y;
    }

    c3_f_a = c3_n;
    c3_c_b = c3_theta;
    c3_k_y = c3_f_a * c3_c_b;
    c3_j_x = c3_k_y;
    c3_k_x = c3_j_x;
    c3_l_x = c3_k_x;
    c3_k_x = c3_l_x;
    c3_k_x = muDoubleScalarCos(c3_k_x);
    for (c3_i1448 = 0; c3_i1448 < 9; c3_i1448 = c3_i1448 + 1) {
      c3_g_a[c3_i1448] = c3_j_y[c3_i1448];
    }

    c3_d_b = 1.0 - c3_k_x;
    for (c3_i1449 = 0; c3_i1449 < 9; c3_i1449 = c3_i1449 + 1) {
      c3_l_y[c3_i1449] = c3_g_a[c3_i1449] * c3_d_b;
    }

    c3_eye(chartInstance, c3_dv154);
    for (c3_i1450 = 0; c3_i1450 < 9; c3_i1450 = c3_i1450 + 1) {
      c3_R[c3_i1450] = (c3_dv154[c3_i1450] + c3_f_y[c3_i1450]) + c3_l_y[c3_i1450];
    }
  }

  _SFD_SCRIPT_CALL(2, -9);
  sf_debug_symbol_scope_pop();
}

static void c3_hat(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                   real_T c3_w[3], real_T c3_W[9])
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

static void c3_matrix_to_integer_power(SFc3_EurlerDynJointVerifyInstanceStruct
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
  int32_T c3_i1451;
  int32_T c3_i1452;
  real_T c3_b_a[9];
  int32_T c3_i1453;
  real_T c3_c_b[9];
  int32_T c3_i1454;
  real_T c3_A[9];
  int32_T c3_i1455;
  real_T c3_B[9];
  int32_T c3_i1456;
  real_T c3_b_A[9];
  int32_T c3_i1457;
  real_T c3_b_B[9];
  int32_T c3_i1458;
  real_T c3_c_A[9];
  int32_T c3_i1459;
  real_T c3_c_B[9];
  int32_T c3_i1460;
  int32_T c3_i1461;
  int32_T c3_i1462;
  int32_T c3_i1463;
  int32_T c3_i1464;
  int32_T c3_i1465;
  real_T c3_c_x[9];
  int32_T c3_i1466;
  real_T c3_d_x[9];
  int32_T c3_i1467;
  real_T c3_e_x[9];
  int32_T c3_i1468;
  real_T c3_xinv[9];
  int32_T c3_i1469;
  real_T c3_f_x[9];
  real_T c3_n1x;
  int32_T c3_i1470;
  real_T c3_b_xinv[9];
  real_T c3_n1xinv;
  real_T c3_c_a;
  real_T c3_d_b;
  real_T c3_b_y;
  real_T c3_rc;
  real_T c3_g_x;
  boolean_T c3_e_b;
  int32_T c3_i1471;
  real_T c3_d_a[9];
  int32_T c3_i1472;
  real_T c3_f_b[9];
  int32_T c3_i1473;
  real_T c3_d_A[9];
  int32_T c3_i1474;
  real_T c3_d_B[9];
  int32_T c3_i1475;
  real_T c3_e_A[9];
  int32_T c3_i1476;
  real_T c3_e_B[9];
  int32_T c3_i1477;
  real_T c3_f_A[9];
  int32_T c3_i1478;
  real_T c3_f_B[9];
  int32_T c3_i1479;
  int32_T c3_i1480;
  int32_T c3_i1481;
  int32_T c3_i1482;
  int32_T c3_i1483;
  int32_T c3_i1484;
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
        for (c3_i1451 = 0; c3_i1451 < 9; c3_i1451 = c3_i1451 + 1) {
          c3_c[c3_i1451] = c3_a[c3_i1451];
        }

        c3_firstmult = FALSE;
      } else {
        for (c3_i1452 = 0; c3_i1452 < 9; c3_i1452 = c3_i1452 + 1) {
          c3_b_a[c3_i1452] = c3_c[c3_i1452];
        }

        for (c3_i1453 = 0; c3_i1453 < 9; c3_i1453 = c3_i1453 + 1) {
          c3_c_b[c3_i1453] = c3_a[c3_i1453];
        }

        c3_c_eml_scalar_eg(chartInstance);
        c3_c_eml_scalar_eg(chartInstance);
        for (c3_i1454 = 0; c3_i1454 < 9; c3_i1454 = c3_i1454 + 1) {
          c3_A[c3_i1454] = c3_b_a[c3_i1454];
        }

        for (c3_i1455 = 0; c3_i1455 < 9; c3_i1455 = c3_i1455 + 1) {
          c3_B[c3_i1455] = c3_c_b[c3_i1455];
        }

        for (c3_i1456 = 0; c3_i1456 < 9; c3_i1456 = c3_i1456 + 1) {
          c3_b_A[c3_i1456] = c3_A[c3_i1456];
        }

        for (c3_i1457 = 0; c3_i1457 < 9; c3_i1457 = c3_i1457 + 1) {
          c3_b_B[c3_i1457] = c3_B[c3_i1457];
        }

        for (c3_i1458 = 0; c3_i1458 < 9; c3_i1458 = c3_i1458 + 1) {
          c3_c_A[c3_i1458] = c3_b_A[c3_i1458];
        }

        for (c3_i1459 = 0; c3_i1459 < 9; c3_i1459 = c3_i1459 + 1) {
          c3_c_B[c3_i1459] = c3_b_B[c3_i1459];
        }

        for (c3_i1460 = 0; c3_i1460 < 3; c3_i1460 = c3_i1460 + 1) {
          c3_i1461 = 0;
          for (c3_i1462 = 0; c3_i1462 < 3; c3_i1462 = c3_i1462 + 1) {
            c3_c[c3_i1461 + c3_i1460] = 0.0;
            c3_i1463 = 0;
            for (c3_i1464 = 0; c3_i1464 < 3; c3_i1464 = c3_i1464 + 1) {
              c3_c[c3_i1461 + c3_i1460] = c3_c[c3_i1461 + c3_i1460] +
                c3_c_A[c3_i1463 + c3_i1460] * c3_c_B[c3_i1464 + c3_i1461];
              c3_i1463 = c3_i1463 + 3;
            }

            c3_i1461 = c3_i1461 + 3;
          }
        }
      }
    }

    if (c3_ed2 == 0.0) {
    } else {
      c3_e = c3_ed2;
      for (c3_i1471 = 0; c3_i1471 < 9; c3_i1471 = c3_i1471 + 1) {
        c3_d_a[c3_i1471] = c3_a[c3_i1471];
      }

      for (c3_i1472 = 0; c3_i1472 < 9; c3_i1472 = c3_i1472 + 1) {
        c3_f_b[c3_i1472] = c3_a[c3_i1472];
      }

      c3_c_eml_scalar_eg(chartInstance);
      c3_c_eml_scalar_eg(chartInstance);
      for (c3_i1473 = 0; c3_i1473 < 9; c3_i1473 = c3_i1473 + 1) {
        c3_d_A[c3_i1473] = c3_d_a[c3_i1473];
      }

      for (c3_i1474 = 0; c3_i1474 < 9; c3_i1474 = c3_i1474 + 1) {
        c3_d_B[c3_i1474] = c3_f_b[c3_i1474];
      }

      for (c3_i1475 = 0; c3_i1475 < 9; c3_i1475 = c3_i1475 + 1) {
        c3_e_A[c3_i1475] = c3_d_A[c3_i1475];
      }

      for (c3_i1476 = 0; c3_i1476 < 9; c3_i1476 = c3_i1476 + 1) {
        c3_e_B[c3_i1476] = c3_d_B[c3_i1476];
      }

      for (c3_i1477 = 0; c3_i1477 < 9; c3_i1477 = c3_i1477 + 1) {
        c3_f_A[c3_i1477] = c3_e_A[c3_i1477];
      }

      for (c3_i1478 = 0; c3_i1478 < 9; c3_i1478 = c3_i1478 + 1) {
        c3_f_B[c3_i1478] = c3_e_B[c3_i1478];
      }

      for (c3_i1479 = 0; c3_i1479 < 3; c3_i1479 = c3_i1479 + 1) {
        c3_i1480 = 0;
        for (c3_i1481 = 0; c3_i1481 < 3; c3_i1481 = c3_i1481 + 1) {
          c3_a[c3_i1480 + c3_i1479] = 0.0;
          c3_i1482 = 0;
          for (c3_i1483 = 0; c3_i1483 < 3; c3_i1483 = c3_i1483 + 1) {
            c3_a[c3_i1480 + c3_i1479] = c3_a[c3_i1480 + c3_i1479] +
              c3_f_A[c3_i1482 + c3_i1479] * c3_f_B[c3_i1483 + c3_i1480];
            c3_i1482 = c3_i1482 + 3;
          }

          c3_i1480 = c3_i1480 + 3;
        }
      }

      goto label_1;
    }

    if (c3_b < 0.0) {
      for (c3_i1465 = 0; c3_i1465 < 9; c3_i1465 = c3_i1465 + 1) {
        c3_c_x[c3_i1465] = c3_c[c3_i1465];
      }

      for (c3_i1466 = 0; c3_i1466 < 9; c3_i1466 = c3_i1466 + 1) {
        c3_d_x[c3_i1466] = c3_c_x[c3_i1466];
      }

      c3_inv3x3(chartInstance, c3_d_x, c3_c);
      for (c3_i1467 = 0; c3_i1467 < 9; c3_i1467 = c3_i1467 + 1) {
        c3_e_x[c3_i1467] = c3_c_x[c3_i1467];
      }

      for (c3_i1468 = 0; c3_i1468 < 9; c3_i1468 = c3_i1468 + 1) {
        c3_xinv[c3_i1468] = c3_c[c3_i1468];
      }

      for (c3_i1469 = 0; c3_i1469 < 9; c3_i1469 = c3_i1469 + 1) {
        c3_f_x[c3_i1469] = c3_e_x[c3_i1469];
      }

      c3_n1x = c3_b_norm(chartInstance, c3_f_x);
      for (c3_i1470 = 0; c3_i1470 < 9; c3_i1470 = c3_i1470 + 1) {
        c3_b_xinv[c3_i1470] = c3_xinv[c3_i1470];
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
    for (c3_i1484 = 0; c3_i1484 < 9; c3_i1484 = c3_i1484 + 1) {
      c3_c[c3_i1484] = 0.0;
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

static void c3_b_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_c_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_inv3x3(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
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

static real_T c3_b_norm(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_x[9])
{
  real_T c3_y;
  int32_T c3_i1485;
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
  for (c3_i1485 = 0; c3_i1485 < 9; c3_i1485 = c3_i1485 + 1) {
    c3_b_x[c3_i1485] = c3_x[c3_i1485];
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

static void c3_eml_warning(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
  int32_T c3_i1486;
  static char_T c3_cv0[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 's', 'i', 'n',
    'g', 'u', 'l', 'a', 'r', 'M', 'a', 't', 'r', 'i', 'x'
  };

  char_T c3_u[21];
  const mxArray *c3_y = NULL;
  int32_T c3_i1487;
  static char_T c3_cv1[40] = { 'M', 'a', 't', 'r', 'i', 'x', ' ', 'i', 's', ' ',
    's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', ' ', 't', 'o'
    , ' ', 'w', 'o', 'r', 'k', 'i', 'n', 'g', ' ', 'p', 'r', 'e', 'c', 'i', 's',
    'i', 'o', 'n', '.' };

  char_T c3_b_u[40];
  const mxArray *c3_b_y = NULL;
  for (c3_i1486 = 0; c3_i1486 < 21; c3_i1486 = c3_i1486 + 1) {
    c3_u[c3_i1486] = c3_cv0[c3_i1486];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 21));
  for (c3_i1487 = 0; c3_i1487 < 40; c3_i1487 = c3_i1487 + 1) {
    c3_b_u[c3_i1487] = c3_cv1[c3_i1487];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
  sf_mex_call_debug("warning", 0U, 2U, 14, c3_y, 14, c3_b_y);
}

static void c3_b_eps(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static void c3_b_eml_warning(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c3_varargin_3)
{
  int32_T c3_i1488;
  static char_T c3_cv2[27] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'l', 'l',
    'C', 'o', 'n', 'd', 'i', 't', 'i', 'o', 'n', 'e', 'd'
    , 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c3_u[27];
  const mxArray *c3_y = NULL;
  int32_T c3_i1489;
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
  for (c3_i1488 = 0; c3_i1488 < 27; c3_i1488 = c3_i1488 + 1) {
    c3_u[c3_i1488] = c3_cv2[c3_i1488];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 27));
  for (c3_i1489 = 0; c3_i1489 < 103; c3_i1489 = c3_i1489 + 1) {
    c3_b_u[c3_i1489] = c3_cv3[c3_i1489];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 103));
  c3_c_u = c3_varargin_3;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_c_u, 0, 0U, 0U, 0U, 0));
  sf_mex_call_debug("warning", 0U, 3U, 14, c3_y, 14, c3_b_y, 14, c3_c_y);
}

static real_T c3_power(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
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

static void c3_eml_error(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  int32_T c3_i1490;
  static char_T c3_cv4[32] = { 'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'p', 'o', 'w', 'e', 'r', ':'
    , 'd', 'o', 'm', 'a', 'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c3_u[32];
  const mxArray *c3_y = NULL;
  int32_T c3_i1491;
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
  for (c3_i1490 = 0; c3_i1490 < 32; c3_i1490 = c3_i1490 + 1) {
    c3_u[c3_i1490] = c3_cv4[c3_i1490];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 32));
  for (c3_i1491 = 0; c3_i1491 < 102; c3_i1491 = c3_i1491 + 1) {
    c3_b_u[c3_i1491] = c3_cv5[c3_i1491];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 102));
  sf_mex_call_debug("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
}

static void c3_d_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_e_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_mldivide(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[4], real_T c3_Y[4])
{
  int32_T c3_i1492;
  real_T c3_b_A[16];
  int32_T c3_i1493;
  real_T c3_b_B[4];
  int32_T c3_i1494;
  real_T c3_c_A[16];
  int32_T c3_i1495;
  real_T c3_c_B[4];
  int32_T c3_i1496;
  real_T c3_d_A[16];
  int32_T c3_i1497;
  real_T c3_e_A[16];
  int32_T c3_i1498;
  real_T c3_f_A[16];
  int32_T c3_i1499;
  real_T c3_g_A[16];
  int32_T c3_i1500;
  real_T c3_h_A[16];
  int32_T c3_info;
  int32_T c3_ipiv[4];
  real_T c3_i_A[16];
  int32_T c3_i1501;
  int32_T c3_i1502;
  int32_T c3_b_ipiv[4];
  int32_T c3_b_info;
  int32_T c3_i1503;
  int32_T c3_i1504;
  int32_T c3_c_ipiv[4];
  int32_T c3_c_info;
  int32_T c3_i1505;
  int32_T c3_i1506;
  int32_T c3_d_ipiv[4];
  int32_T c3_d_info;
  int32_T c3_i1507;
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_ip;
  real_T c3_temp;
  int32_T c3_i1508;
  real_T c3_j_A[16];
  int32_T c3_i1509;
  real_T c3_b_Y[4];
  int32_T c3_i1510;
  real_T c3_k_A[16];
  int32_T c3_i1511;
  real_T c3_d_B[4];
  int32_T c3_i1512;
  int32_T c3_i1513;
  real_T c3_l_A[16];
  int32_T c3_i1514;
  real_T c3_c_Y[4];
  for (c3_i1492 = 0; c3_i1492 < 16; c3_i1492 = c3_i1492 + 1) {
    c3_b_A[c3_i1492] = c3_A[c3_i1492];
  }

  for (c3_i1493 = 0; c3_i1493 < 4; c3_i1493 = c3_i1493 + 1) {
    c3_b_B[c3_i1493] = c3_B[c3_i1493];
  }

  for (c3_i1494 = 0; c3_i1494 < 16; c3_i1494 = c3_i1494 + 1) {
    c3_c_A[c3_i1494] = c3_b_A[c3_i1494];
  }

  for (c3_i1495 = 0; c3_i1495 < 4; c3_i1495 = c3_i1495 + 1) {
    c3_c_B[c3_i1495] = c3_b_B[c3_i1495];
  }

  for (c3_i1496 = 0; c3_i1496 < 16; c3_i1496 = c3_i1496 + 1) {
    c3_d_A[c3_i1496] = c3_c_A[c3_i1496];
  }

  for (c3_i1497 = 0; c3_i1497 < 16; c3_i1497 = c3_i1497 + 1) {
    c3_e_A[c3_i1497] = c3_d_A[c3_i1497];
  }

  for (c3_i1498 = 0; c3_i1498 < 16; c3_i1498 = c3_i1498 + 1) {
    c3_f_A[c3_i1498] = c3_e_A[c3_i1498];
  }

  for (c3_i1499 = 0; c3_i1499 < 16; c3_i1499 = c3_i1499 + 1) {
    c3_g_A[c3_i1499] = c3_f_A[c3_i1499];
  }

  for (c3_i1500 = 0; c3_i1500 < 16; c3_i1500 = c3_i1500 + 1) {
    c3_h_A[c3_i1500] = c3_g_A[c3_i1500];
  }

  c3_eml_matlab_zgetrf(chartInstance, c3_h_A, c3_i_A, c3_ipiv, &c3_info);
  for (c3_i1501 = 0; c3_i1501 < 16; c3_i1501 = c3_i1501 + 1) {
    c3_g_A[c3_i1501] = c3_i_A[c3_i1501];
  }

  for (c3_i1502 = 0; c3_i1502 < 4; c3_i1502 = c3_i1502 + 1) {
    c3_b_ipiv[c3_i1502] = c3_ipiv[c3_i1502];
  }

  c3_b_info = c3_info;
  for (c3_i1503 = 0; c3_i1503 < 16; c3_i1503 = c3_i1503 + 1) {
    c3_e_A[c3_i1503] = c3_g_A[c3_i1503];
  }

  for (c3_i1504 = 0; c3_i1504 < 4; c3_i1504 = c3_i1504 + 1) {
    c3_c_ipiv[c3_i1504] = c3_b_ipiv[c3_i1504];
  }

  c3_c_info = c3_b_info;
  for (c3_i1505 = 0; c3_i1505 < 16; c3_i1505 = c3_i1505 + 1) {
    c3_c_A[c3_i1505] = c3_e_A[c3_i1505];
  }

  for (c3_i1506 = 0; c3_i1506 < 4; c3_i1506 = c3_i1506 + 1) {
    c3_d_ipiv[c3_i1506] = c3_c_ipiv[c3_i1506];
  }

  c3_d_info = c3_c_info;
  if ((real_T)c3_d_info > 0.0) {
    c3_eml_warning(chartInstance);
  }

  for (c3_i1507 = 0; c3_i1507 < 4; c3_i1507 = c3_i1507 + 1) {
    c3_Y[c3_i1507] = c3_c_B[c3_i1507];
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

  for (c3_i1508 = 0; c3_i1508 < 16; c3_i1508 = c3_i1508 + 1) {
    c3_j_A[c3_i1508] = c3_c_A[c3_i1508];
  }

  for (c3_i1509 = 0; c3_i1509 < 4; c3_i1509 = c3_i1509 + 1) {
    c3_b_Y[c3_i1509] = c3_Y[c3_i1509];
  }

  c3_eml_xtrsm(chartInstance, c3_j_A, c3_b_Y, c3_Y);
  for (c3_i1510 = 0; c3_i1510 < 16; c3_i1510 = c3_i1510 + 1) {
    c3_k_A[c3_i1510] = c3_c_A[c3_i1510];
  }

  for (c3_i1511 = 0; c3_i1511 < 4; c3_i1511 = c3_i1511 + 1) {
    c3_d_B[c3_i1511] = c3_Y[c3_i1511];
  }

  for (c3_i1512 = 0; c3_i1512 < 4; c3_i1512 = c3_i1512 + 1) {
    c3_Y[c3_i1512] = c3_d_B[c3_i1512];
  }

  for (c3_i1513 = 0; c3_i1513 < 16; c3_i1513 = c3_i1513 + 1) {
    c3_l_A[c3_i1513] = c3_k_A[c3_i1513];
  }

  for (c3_i1514 = 0; c3_i1514 < 4; c3_i1514 = c3_i1514 + 1) {
    c3_c_Y[c3_i1514] = c3_Y[c3_i1514];
  }

  c3_eml_blas_xtrsm(chartInstance, 4, 1, 1.0, c3_l_A, 1, 4, c3_c_Y, 1, 4, c3_Y);
}

static void c3_eml_matlab_zgetrf(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c3_A[16], real_T c3_b_A[16], int32_T
  c3_ipiv[4], int32_T *c3_info)
{
  int32_T c3_i1515;
  int32_T c3_i1516;
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
  int32_T c3_i1517;
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
  int32_T c3_i1518;
  real_T c3_x[16];
  int32_T c3_ix0;
  int32_T c3_iy0;
  int32_T c3_i1519;
  int32_T c3_i1520;
  real_T c3_b_x[16];
  int32_T c3_b_ix0;
  int32_T c3_b_iy0;
  int32_T c3_i1521;
  real_T c3_c_x[16];
  int32_T c3_i1522;
  real_T c3_d_x[16];
  real_T c3_e_x[16];
  int32_T c3_i1523;
  int32_T c3_i1524;
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
  int32_T c3_i1525;
  real_T c3_d_A[16];
  int32_T c3_ia0;
  int32_T c3_i1526;
  int32_T c3_b_m;
  int32_T c3_b_n;
  int32_T c3_d_ix0;
  int32_T c3_d_iy0;
  int32_T c3_i1527;
  real_T c3_e_A[16];
  int32_T c3_b_ia0;
  int32_T c3_i1528;
  int32_T c3_c_m;
  int32_T c3_c_n;
  int32_T c3_e_ix0;
  int32_T c3_e_iy0;
  int32_T c3_i1529;
  real_T c3_f_A[16];
  int32_T c3_c_ia0;
  int32_T c3_i1530;
  int32_T c3_i1531;
  real_T c3_g_A[16];
  for (c3_i1515 = 0; c3_i1515 < 16; c3_i1515 = c3_i1515 + 1) {
    c3_b_A[c3_i1515] = c3_A[c3_i1515];
  }

  c3_b_eps(chartInstance);
  for (c3_i1516 = 0; c3_i1516 < 4; c3_i1516 = c3_i1516 + 1) {
    c3_ipiv[c3_i1516] = 1 + c3_i1516;
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
    for (c3_i1517 = 0; c3_i1517 < 16; c3_i1517 = c3_i1517 + 1) {
      c3_c_A[c3_i1517] = c3_b_A[c3_i1517];
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
        for (c3_i1518 = 0; c3_i1518 < 16; c3_i1518 = c3_i1518 + 1) {
          c3_x[c3_i1518] = c3_b_A[c3_i1518];
        }

        c3_ix0 = c3_jrow;
        c3_iy0 = c3_jprow;
        for (c3_i1519 = 0; c3_i1519 < 16; c3_i1519 = c3_i1519 + 1) {
          c3_b_A[c3_i1519] = c3_x[c3_i1519];
        }

        for (c3_i1520 = 0; c3_i1520 < 16; c3_i1520 = c3_i1520 + 1) {
          c3_b_x[c3_i1520] = c3_b_A[c3_i1520];
        }

        c3_b_ix0 = c3_ix0;
        c3_b_iy0 = c3_iy0;
        for (c3_i1521 = 0; c3_i1521 < 16; c3_i1521 = c3_i1521 + 1) {
          c3_c_x[c3_i1521] = c3_b_x[c3_i1521];
        }

        for (c3_i1522 = 0; c3_i1522 < 16; c3_i1522 = c3_i1522 + 1) {
          c3_d_x[c3_i1522] = c3_c_x[c3_i1522];
        }

        c3_ceval_xswap(chartInstance, 4, c3_d_x, c3_b_ix0, 4, c3_b_iy0, 4,
                       c3_e_x);
        for (c3_i1523 = 0; c3_i1523 < 16; c3_i1523 = c3_i1523 + 1) {
          c3_c_x[c3_i1523] = c3_e_x[c3_i1523];
        }

        for (c3_i1524 = 0; c3_i1524 < 16; c3_i1524 = c3_i1524 + 1) {
          c3_b_A[c3_i1524] = c3_c_x[c3_i1524];
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
    for (c3_i1525 = 0; c3_i1525 < 16; c3_i1525 = c3_i1525 + 1) {
      c3_d_A[c3_i1525] = c3_b_A[c3_i1525];
    }

    c3_ia0 = c3_g_c;
    for (c3_i1526 = 0; c3_i1526 < 16; c3_i1526 = c3_i1526 + 1) {
      c3_b_A[c3_i1526] = c3_d_A[c3_i1526];
    }

    c3_b_m = c3_m;
    c3_b_n = c3_n;
    c3_d_ix0 = c3_c_ix0;
    c3_d_iy0 = c3_c_iy0;
    for (c3_i1527 = 0; c3_i1527 < 16; c3_i1527 = c3_i1527 + 1) {
      c3_e_A[c3_i1527] = c3_b_A[c3_i1527];
    }

    c3_b_ia0 = c3_ia0;
    for (c3_i1528 = 0; c3_i1528 < 16; c3_i1528 = c3_i1528 + 1) {
      c3_b_A[c3_i1528] = c3_e_A[c3_i1528];
    }

    c3_c_m = c3_b_m;
    c3_c_n = c3_b_n;
    c3_e_ix0 = c3_d_ix0;
    c3_e_iy0 = c3_d_iy0;
    for (c3_i1529 = 0; c3_i1529 < 16; c3_i1529 = c3_i1529 + 1) {
      c3_f_A[c3_i1529] = c3_b_A[c3_i1529];
    }

    c3_c_ia0 = c3_b_ia0;
    for (c3_i1530 = 0; c3_i1530 < 16; c3_i1530 = c3_i1530 + 1) {
      c3_b_A[c3_i1530] = c3_f_A[c3_i1530];
    }

    if ((real_T)c3_c_m < 1.0) {
    } else if ((real_T)c3_c_n < 1.0) {
    } else {
      for (c3_i1531 = 0; c3_i1531 < 16; c3_i1531 = c3_i1531 + 1) {
        c3_g_A[c3_i1531] = c3_b_A[c3_i1531];
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

static int32_T c3_eml_ixamax(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0)
{
  int32_T c3_b_n;
  int32_T c3_i1532;
  real_T c3_b_x[16];
  int32_T c3_b_ix0;
  int32_T c3_i1533;
  real_T c3_c_x[16];
  c3_b_n = c3_n;
  for (c3_i1532 = 0; c3_i1532 < 16; c3_i1532 = c3_i1532 + 1) {
    c3_b_x[c3_i1532] = c3_x[c3_i1532];
  }

  c3_b_ix0 = c3_ix0;
  for (c3_i1533 = 0; c3_i1533 < 16; c3_i1533 = c3_i1533 + 1) {
    c3_c_x[c3_i1533] = c3_b_x[c3_i1533];
  }

  return c3_ceval_ixamax(chartInstance, c3_b_n, c3_c_x, c3_b_ix0, 1);
}

static int32_T c3_ceval_ixamax(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0
  , int32_T c3_incx)
{
  return idamax32(&c3_n, &c3_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 16, 1, 0) - 1], &
                  c3_incx);
}

static void c3_ceval_xswap(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[16], int32_T c3_ix0,
  int32_T c3_incx, int32_T c3_iy0, int32_T c3_incy, real_T c3_b_x[16])
{
  int32_T c3_i1534;

  /* Empty Loop. */
  for (c3_i1534 = 0; c3_i1534 < 16; c3_i1534 = c3_i1534 + 1) {
    c3_b_x[c3_i1534] = c3_x[c3_i1534];
  }

  dswap32(&c3_n, &c3_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 16, 1, 0) - 1], &c3_incx
          , &c3_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
            "", (real_T)c3_iy0), 1, 16, 1, 0) - 1], &c3_incy);
}

static void c3_ceval_xger(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, real_T c3_alpha1,
  int32_T c3_ix0, int32_T c3_incx, int32_T c3_iy0, int32_T c3_incy, real_T c3_A
  [16], int32_T c3_ia0, int32_T c3_lda, real_T c3_b_A[16]
  )
{
  int32_T c3_i1535;
  for (c3_i1535 = 0; c3_i1535 < 16; c3_i1535 = c3_i1535 + 1) {
    c3_b_A[c3_i1535] = c3_A[c3_i1535];
  }

  dger32(&c3_m, &c3_n, &c3_alpha1, &c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c3_ix0), 1, 16, 1,
          0) - 1], &c3_incx, &c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_iy0), 1, 16, 1, 0) - 1], &
         c3_incy, &c3_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_ia0), 1, 16, 1, 0) - 1], &c3_lda);
}

static void c3_eml_xtrsm(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[4], real_T c3_b_B[4])
{
  int32_T c3_i1536;
  int32_T c3_i1537;
  real_T c3_b_A[16];
  int32_T c3_i1538;
  real_T c3_c_B[4];
  int32_T c3_i1539;
  int32_T c3_i1540;
  real_T c3_c_A[16];
  int32_T c3_i1541;
  real_T c3_d_B[4];
  int32_T c3_i1542;
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
  int32_T c3_i1543;
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
  for (c3_i1536 = 0; c3_i1536 < 4; c3_i1536 = c3_i1536 + 1) {
    c3_b_B[c3_i1536] = c3_B[c3_i1536];
  }

  for (c3_i1537 = 0; c3_i1537 < 16; c3_i1537 = c3_i1537 + 1) {
    c3_b_A[c3_i1537] = c3_A[c3_i1537];
  }

  for (c3_i1538 = 0; c3_i1538 < 4; c3_i1538 = c3_i1538 + 1) {
    c3_c_B[c3_i1538] = c3_b_B[c3_i1538];
  }

  for (c3_i1539 = 0; c3_i1539 < 4; c3_i1539 = c3_i1539 + 1) {
    c3_b_B[c3_i1539] = c3_c_B[c3_i1539];
  }

  for (c3_i1540 = 0; c3_i1540 < 16; c3_i1540 = c3_i1540 + 1) {
    c3_c_A[c3_i1540] = c3_b_A[c3_i1540];
  }

  for (c3_i1541 = 0; c3_i1541 < 4; c3_i1541 = c3_i1541 + 1) {
    c3_d_B[c3_i1541] = c3_b_B[c3_i1541];
  }

  for (c3_i1542 = 0; c3_i1542 < 4; c3_i1542 = c3_i1542 + 1) {
    c3_b_B[c3_i1542] = c3_d_B[c3_i1542];
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
        c3_i1543 = c3_d_a + 1;
        for (c3_i = c3_i1543; c3_i <= 4; c3_i = c3_i + 1) {
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

static void c3_f_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_eml_blas_xtrsm(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, real_T c3_alpha1,
  real_T c3_A[16], int32_T c3_ia0, int32_T c3_lda, real_T c3_B[4], int32_T
  c3_ib0, int32_T c3_ldb, real_T c3_b_B[4])
{
  int32_T c3_i1544;
  int32_T c3_b_m;
  int32_T c3_b_n;
  real_T c3_b_alpha1;
  int32_T c3_i1545;
  real_T c3_b_A[16];
  int32_T c3_b_ia0;
  int32_T c3_b_lda;
  int32_T c3_i1546;
  real_T c3_c_B[4];
  int32_T c3_b_ib0;
  int32_T c3_b_ldb;
  int32_T c3_i1547;
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
  for (c3_i1544 = 0; c3_i1544 < 4; c3_i1544 = c3_i1544 + 1) {
    c3_b_B[c3_i1544] = c3_B[c3_i1544];
  }

  c3_b_m = c3_m;
  c3_b_n = c3_n;
  c3_b_alpha1 = c3_alpha1;
  for (c3_i1545 = 0; c3_i1545 < 16; c3_i1545 = c3_i1545 + 1) {
    c3_b_A[c3_i1545] = c3_A[c3_i1545];
  }

  c3_b_ia0 = c3_ia0;
  c3_b_lda = c3_lda;
  for (c3_i1546 = 0; c3_i1546 < 4; c3_i1546 = c3_i1546 + 1) {
    c3_c_B[c3_i1546] = c3_b_B[c3_i1546];
  }

  c3_b_ib0 = c3_ib0;
  c3_b_ldb = c3_ldb;
  for (c3_i1547 = 0; c3_i1547 < 4; c3_i1547 = c3_i1547 + 1) {
    c3_b_B[c3_i1547] = c3_c_B[c3_i1547];
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

static void c3_b_mldivide(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_A[16], real_T c3_B[16], real_T c3_Y[16])
{
  int32_T c3_i1548;
  real_T c3_b_A[16];
  int32_T c3_i1549;
  real_T c3_b_B[16];
  int32_T c3_i1550;
  real_T c3_c_A[16];
  int32_T c3_i1551;
  real_T c3_c_B[16];
  int32_T c3_i1552;
  real_T c3_d_A[16];
  int32_T c3_i1553;
  real_T c3_e_A[16];
  int32_T c3_i1554;
  real_T c3_f_A[16];
  int32_T c3_i1555;
  real_T c3_g_A[16];
  int32_T c3_i1556;
  real_T c3_h_A[16];
  int32_T c3_info;
  int32_T c3_ipiv[4];
  real_T c3_i_A[16];
  int32_T c3_i1557;
  int32_T c3_i1558;
  int32_T c3_b_ipiv[4];
  int32_T c3_b_info;
  int32_T c3_i1559;
  int32_T c3_i1560;
  int32_T c3_c_ipiv[4];
  int32_T c3_c_info;
  int32_T c3_i1561;
  int32_T c3_i1562;
  int32_T c3_d_ipiv[4];
  int32_T c3_d_info;
  int32_T c3_i1563;
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_ip;
  int32_T c3_j;
  int32_T c3_b_j;
  real_T c3_temp;
  int32_T c3_i1564;
  real_T c3_j_A[16];
  int32_T c3_i1565;
  real_T c3_b_Y[16];
  int32_T c3_i1566;
  real_T c3_k_A[16];
  int32_T c3_i1567;
  real_T c3_d_B[16];
  int32_T c3_i1568;
  int32_T c3_i1569;
  real_T c3_l_A[16];
  int32_T c3_i1570;
  real_T c3_c_Y[16];
  for (c3_i1548 = 0; c3_i1548 < 16; c3_i1548 = c3_i1548 + 1) {
    c3_b_A[c3_i1548] = c3_A[c3_i1548];
  }

  for (c3_i1549 = 0; c3_i1549 < 16; c3_i1549 = c3_i1549 + 1) {
    c3_b_B[c3_i1549] = c3_B[c3_i1549];
  }

  for (c3_i1550 = 0; c3_i1550 < 16; c3_i1550 = c3_i1550 + 1) {
    c3_c_A[c3_i1550] = c3_b_A[c3_i1550];
  }

  for (c3_i1551 = 0; c3_i1551 < 16; c3_i1551 = c3_i1551 + 1) {
    c3_c_B[c3_i1551] = c3_b_B[c3_i1551];
  }

  for (c3_i1552 = 0; c3_i1552 < 16; c3_i1552 = c3_i1552 + 1) {
    c3_d_A[c3_i1552] = c3_c_A[c3_i1552];
  }

  for (c3_i1553 = 0; c3_i1553 < 16; c3_i1553 = c3_i1553 + 1) {
    c3_e_A[c3_i1553] = c3_d_A[c3_i1553];
  }

  for (c3_i1554 = 0; c3_i1554 < 16; c3_i1554 = c3_i1554 + 1) {
    c3_f_A[c3_i1554] = c3_e_A[c3_i1554];
  }

  for (c3_i1555 = 0; c3_i1555 < 16; c3_i1555 = c3_i1555 + 1) {
    c3_g_A[c3_i1555] = c3_f_A[c3_i1555];
  }

  for (c3_i1556 = 0; c3_i1556 < 16; c3_i1556 = c3_i1556 + 1) {
    c3_h_A[c3_i1556] = c3_g_A[c3_i1556];
  }

  c3_eml_matlab_zgetrf(chartInstance, c3_h_A, c3_i_A, c3_ipiv, &c3_info);
  for (c3_i1557 = 0; c3_i1557 < 16; c3_i1557 = c3_i1557 + 1) {
    c3_g_A[c3_i1557] = c3_i_A[c3_i1557];
  }

  for (c3_i1558 = 0; c3_i1558 < 4; c3_i1558 = c3_i1558 + 1) {
    c3_b_ipiv[c3_i1558] = c3_ipiv[c3_i1558];
  }

  c3_b_info = c3_info;
  for (c3_i1559 = 0; c3_i1559 < 16; c3_i1559 = c3_i1559 + 1) {
    c3_e_A[c3_i1559] = c3_g_A[c3_i1559];
  }

  for (c3_i1560 = 0; c3_i1560 < 4; c3_i1560 = c3_i1560 + 1) {
    c3_c_ipiv[c3_i1560] = c3_b_ipiv[c3_i1560];
  }

  c3_c_info = c3_b_info;
  for (c3_i1561 = 0; c3_i1561 < 16; c3_i1561 = c3_i1561 + 1) {
    c3_c_A[c3_i1561] = c3_e_A[c3_i1561];
  }

  for (c3_i1562 = 0; c3_i1562 < 4; c3_i1562 = c3_i1562 + 1) {
    c3_d_ipiv[c3_i1562] = c3_c_ipiv[c3_i1562];
  }

  c3_d_info = c3_c_info;
  if ((real_T)c3_d_info > 0.0) {
    c3_eml_warning(chartInstance);
  }

  c3_e_eml_scalar_eg(chartInstance);
  for (c3_i1563 = 0; c3_i1563 < 16; c3_i1563 = c3_i1563 + 1) {
    c3_Y[c3_i1563] = c3_c_B[c3_i1563];
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

  for (c3_i1564 = 0; c3_i1564 < 16; c3_i1564 = c3_i1564 + 1) {
    c3_j_A[c3_i1564] = c3_c_A[c3_i1564];
  }

  for (c3_i1565 = 0; c3_i1565 < 16; c3_i1565 = c3_i1565 + 1) {
    c3_b_Y[c3_i1565] = c3_Y[c3_i1565];
  }

  c3_b_eml_xtrsm(chartInstance, c3_j_A, c3_b_Y, c3_Y);
  for (c3_i1566 = 0; c3_i1566 < 16; c3_i1566 = c3_i1566 + 1) {
    c3_k_A[c3_i1566] = c3_c_A[c3_i1566];
  }

  for (c3_i1567 = 0; c3_i1567 < 16; c3_i1567 = c3_i1567 + 1) {
    c3_d_B[c3_i1567] = c3_Y[c3_i1567];
  }

  for (c3_i1568 = 0; c3_i1568 < 16; c3_i1568 = c3_i1568 + 1) {
    c3_Y[c3_i1568] = c3_d_B[c3_i1568];
  }

  for (c3_i1569 = 0; c3_i1569 < 16; c3_i1569 = c3_i1569 + 1) {
    c3_l_A[c3_i1569] = c3_k_A[c3_i1569];
  }

  for (c3_i1570 = 0; c3_i1570 < 16; c3_i1570 = c3_i1570 + 1) {
    c3_c_Y[c3_i1570] = c3_Y[c3_i1570];
  }

  c3_b_eml_blas_xtrsm(chartInstance, 4, 4, 1.0, c3_l_A, 1, 4, c3_c_Y, 1, 4, c3_Y);
}

static void c3_b_eml_xtrsm(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c3_A[16], real_T c3_B[16], real_T c3_b_B[
  16])
{
  int32_T c3_i1571;
  int32_T c3_i1572;
  real_T c3_b_A[16];
  int32_T c3_i1573;
  real_T c3_c_B[16];
  int32_T c3_i1574;
  int32_T c3_i1575;
  real_T c3_c_A[16];
  int32_T c3_i1576;
  real_T c3_d_B[16];
  int32_T c3_i1577;
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
  int32_T c3_i1578;
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
  for (c3_i1571 = 0; c3_i1571 < 16; c3_i1571 = c3_i1571 + 1) {
    c3_b_B[c3_i1571] = c3_B[c3_i1571];
  }

  for (c3_i1572 = 0; c3_i1572 < 16; c3_i1572 = c3_i1572 + 1) {
    c3_b_A[c3_i1572] = c3_A[c3_i1572];
  }

  for (c3_i1573 = 0; c3_i1573 < 16; c3_i1573 = c3_i1573 + 1) {
    c3_c_B[c3_i1573] = c3_b_B[c3_i1573];
  }

  for (c3_i1574 = 0; c3_i1574 < 16; c3_i1574 = c3_i1574 + 1) {
    c3_b_B[c3_i1574] = c3_c_B[c3_i1574];
  }

  for (c3_i1575 = 0; c3_i1575 < 16; c3_i1575 = c3_i1575 + 1) {
    c3_c_A[c3_i1575] = c3_b_A[c3_i1575];
  }

  for (c3_i1576 = 0; c3_i1576 < 16; c3_i1576 = c3_i1576 + 1) {
    c3_d_B[c3_i1576] = c3_b_B[c3_i1576];
  }

  for (c3_i1577 = 0; c3_i1577 < 16; c3_i1577 = c3_i1577 + 1) {
    c3_b_B[c3_i1577] = c3_d_B[c3_i1577];
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
        c3_i1578 = c3_d_a + 1;
        for (c3_i = c3_i1578; c3_i <= 4; c3_i = c3_i + 1) {
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

static void c3_g_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_b_eml_blas_xtrsm(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, real_T c3_alpha1
  , real_T c3_A[16], int32_T c3_ia0, int32_T c3_lda, real_T c3_B[16], int32_T
  c3_ib0, int32_T c3_ldb, real_T c3_b_B[16])
{
  int32_T c3_i1579;
  int32_T c3_b_m;
  int32_T c3_b_n;
  real_T c3_b_alpha1;
  int32_T c3_i1580;
  real_T c3_b_A[16];
  int32_T c3_b_ia0;
  int32_T c3_b_lda;
  int32_T c3_i1581;
  real_T c3_c_B[16];
  int32_T c3_b_ib0;
  int32_T c3_b_ldb;
  int32_T c3_i1582;
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
  for (c3_i1579 = 0; c3_i1579 < 16; c3_i1579 = c3_i1579 + 1) {
    c3_b_B[c3_i1579] = c3_B[c3_i1579];
  }

  c3_b_m = c3_m;
  c3_b_n = c3_n;
  c3_b_alpha1 = c3_alpha1;
  for (c3_i1580 = 0; c3_i1580 < 16; c3_i1580 = c3_i1580 + 1) {
    c3_b_A[c3_i1580] = c3_A[c3_i1580];
  }

  c3_b_ia0 = c3_ia0;
  c3_b_lda = c3_lda;
  for (c3_i1581 = 0; c3_i1581 < 16; c3_i1581 = c3_i1581 + 1) {
    c3_c_B[c3_i1581] = c3_b_B[c3_i1581];
  }

  c3_b_ib0 = c3_ib0;
  c3_b_ldb = c3_ldb;
  for (c3_i1582 = 0; c3_i1582 < 16; c3_i1582 = c3_i1582 + 1) {
    c3_b_B[c3_i1582] = c3_c_B[c3_i1582];
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

static void c3_Adj(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
                   real_T c3_g[16], real_T c3_Adg[36])
{
  uint32_T c3_debug_family_var_map[7];
  static const char *c3_sv3[7] = { "R", "P", "P_hat", "nargin", "nargout", "g",
    "Adg" };

  real_T c3_R[9];
  real_T c3_P[3];
  real_T c3_P_hat[9];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  int32_T c3_i1583;
  int32_T c3_i1584;
  int32_T c3_i1585;
  int32_T c3_i1586;
  int32_T c3_i1587;
  int32_T c3_i1588;
  real_T c3_w[3];
  uint32_T c3_b_debug_family_var_map[4];
  static const char *c3_sv4[4] = { "nargin", "nargout", "w", "W" };

  real_T c3_b_nargin = 1.0;
  real_T c3_b_nargout = 1.0;
  int32_T c3_i1589;
  real_T c3_a[9];
  int32_T c3_i1590;
  real_T c3_b[9];
  int32_T c3_i1591;
  real_T c3_A[9];
  int32_T c3_i1592;
  real_T c3_B[9];
  int32_T c3_i1593;
  real_T c3_b_A[9];
  int32_T c3_i1594;
  real_T c3_b_B[9];
  int32_T c3_i1595;
  real_T c3_c_A[9];
  int32_T c3_i1596;
  real_T c3_c_B[9];
  int32_T c3_i1597;
  int32_T c3_i1598;
  int32_T c3_i1599;
  real_T c3_y[9];
  int32_T c3_i1600;
  int32_T c3_i1601;
  int32_T c3_i1602;
  int32_T c3_i1603;
  int32_T c3_i1604;
  int32_T c3_i1605;
  int32_T c3_i1606;
  int32_T c3_i1607;
  int32_T c3_i1608;
  int32_T c3_i1609;
  int32_T c3_i1610;
  int32_T c3_i1611;
  int32_T c3_i1612;
  int32_T c3_i1613;
  int32_T c3_i1614;
  int32_T c3_i1615;
  int32_T c3_i1616;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c3_sv3, c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c3_R, c3_g_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c3_P, c3_h_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_P_hat, c3_g_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c3_g, c3_i_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c3_Adg, c3_j_sf_marshall, 6U);
  CV_SCRIPT_FCN(4, 0);

  /*  Adjoint transformation matrix Adg of transform g */
  _SFD_SCRIPT_CALL(4, 3);
  c3_i1583 = 0;
  c3_i1584 = 0;
  for (c3_i1585 = 0; c3_i1585 < 3; c3_i1585 = c3_i1585 + 1) {
    for (c3_i1586 = 0; c3_i1586 < 3; c3_i1586 = c3_i1586 + 1) {
      c3_R[c3_i1586 + c3_i1583] = c3_g[c3_i1586 + c3_i1584];
    }

    c3_i1583 = c3_i1583 + 3;
    c3_i1584 = c3_i1584 + 4;
  }

  _SFD_SCRIPT_CALL(4, 4);
  for (c3_i1587 = 0; c3_i1587 < 3; c3_i1587 = c3_i1587 + 1) {
    c3_P[c3_i1587] = c3_g[c3_i1587 + 12];
  }

  _SFD_SCRIPT_CALL(4, 5);
  for (c3_i1588 = 0; c3_i1588 < 3; c3_i1588 = c3_i1588 + 1) {
    c3_w[c3_i1588] = c3_P[c3_i1588];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_sv4, c3_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_b_nargin, c3_f_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_b_nargout, c3_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c3_w, c3_h_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c3_P_hat, c3_g_sf_marshall, 3U);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3, 2);
  c3_P_hat[0] = 0.0;
  c3_P_hat[3] = -c3_w[2];
  c3_P_hat[6] = c3_w[1];
  c3_P_hat[1] = c3_w[2];
  c3_P_hat[4] = 0.0;
  c3_P_hat[7] = -c3_w[0];
  c3_P_hat[2] = -c3_w[1];
  c3_P_hat[5] = c3_w[0];
  c3_P_hat[8] = 0.0;
  _SFD_SCRIPT_CALL(3, -2);
  sf_debug_symbol_scope_pop();
  _SFD_SCRIPT_CALL(4, 7);
  for (c3_i1589 = 0; c3_i1589 < 9; c3_i1589 = c3_i1589 + 1) {
    c3_a[c3_i1589] = c3_P_hat[c3_i1589];
  }

  for (c3_i1590 = 0; c3_i1590 < 9; c3_i1590 = c3_i1590 + 1) {
    c3_b[c3_i1590] = c3_R[c3_i1590];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  for (c3_i1591 = 0; c3_i1591 < 9; c3_i1591 = c3_i1591 + 1) {
    c3_A[c3_i1591] = c3_a[c3_i1591];
  }

  for (c3_i1592 = 0; c3_i1592 < 9; c3_i1592 = c3_i1592 + 1) {
    c3_B[c3_i1592] = c3_b[c3_i1592];
  }

  for (c3_i1593 = 0; c3_i1593 < 9; c3_i1593 = c3_i1593 + 1) {
    c3_b_A[c3_i1593] = c3_A[c3_i1593];
  }

  for (c3_i1594 = 0; c3_i1594 < 9; c3_i1594 = c3_i1594 + 1) {
    c3_b_B[c3_i1594] = c3_B[c3_i1594];
  }

  for (c3_i1595 = 0; c3_i1595 < 9; c3_i1595 = c3_i1595 + 1) {
    c3_c_A[c3_i1595] = c3_b_A[c3_i1595];
  }

  for (c3_i1596 = 0; c3_i1596 < 9; c3_i1596 = c3_i1596 + 1) {
    c3_c_B[c3_i1596] = c3_b_B[c3_i1596];
  }

  for (c3_i1597 = 0; c3_i1597 < 3; c3_i1597 = c3_i1597 + 1) {
    c3_i1598 = 0;
    for (c3_i1599 = 0; c3_i1599 < 3; c3_i1599 = c3_i1599 + 1) {
      c3_y[c3_i1598 + c3_i1597] = 0.0;
      c3_i1600 = 0;
      for (c3_i1601 = 0; c3_i1601 < 3; c3_i1601 = c3_i1601 + 1) {
        c3_y[c3_i1598 + c3_i1597] = c3_y[c3_i1598 + c3_i1597] + c3_c_A[c3_i1600
          + c3_i1597] * c3_c_B[c3_i1601 + c3_i1598];
        c3_i1600 = c3_i1600 + 3;
      }

      c3_i1598 = c3_i1598 + 3;
    }
  }

  c3_i1602 = 0;
  c3_i1603 = 0;
  for (c3_i1604 = 0; c3_i1604 < 3; c3_i1604 = c3_i1604 + 1) {
    for (c3_i1605 = 0; c3_i1605 < 3; c3_i1605 = c3_i1605 + 1) {
      c3_Adg[c3_i1605 + c3_i1602] = c3_R[c3_i1605 + c3_i1603];
    }

    c3_i1602 = c3_i1602 + 6;
    c3_i1603 = c3_i1603 + 3;
  }

  c3_i1606 = 0;
  c3_i1607 = 0;
  for (c3_i1608 = 0; c3_i1608 < 3; c3_i1608 = c3_i1608 + 1) {
    for (c3_i1609 = 0; c3_i1609 < 3; c3_i1609 = c3_i1609 + 1) {
      c3_Adg[(c3_i1609 + c3_i1606) + 18] = c3_y[c3_i1609 + c3_i1607];
    }

    c3_i1606 = c3_i1606 + 6;
    c3_i1607 = c3_i1607 + 3;
  }

  c3_i1610 = 0;
  for (c3_i1611 = 0; c3_i1611 < 3; c3_i1611 = c3_i1611 + 1) {
    for (c3_i1612 = 0; c3_i1612 < 3; c3_i1612 = c3_i1612 + 1) {
      c3_Adg[(c3_i1612 + c3_i1610) + 3] = 0.0;
    }

    c3_i1610 = c3_i1610 + 6;
  }

  c3_i1613 = 0;
  c3_i1614 = 0;
  for (c3_i1615 = 0; c3_i1615 < 3; c3_i1615 = c3_i1615 + 1) {
    for (c3_i1616 = 0; c3_i1616 < 3; c3_i1616 = c3_i1616 + 1) {
      c3_Adg[(c3_i1616 + c3_i1613) + 21] = c3_R[c3_i1616 + c3_i1614];
    }

    c3_i1613 = c3_i1613 + 6;
    c3_i1614 = c3_i1614 + 3;
  }

  _SFD_SCRIPT_CALL(4, -7);
  sf_debug_symbol_scope_pop();
}

static void c3_h_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_eml_xgemm(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c3_A[36], real_T c3_B[6], real_T c3_C[6],
  real_T c3_b_C[6])
{
  int32_T c3_i1617;
  real_T c3_b_A[36];
  int32_T c3_i1618;
  real_T c3_b_B[6];
  int32_T c3_i1619;
  real_T c3_c_A[36];
  int32_T c3_i1620;
  real_T c3_c_B[6];
  int32_T c3_i1621;
  int32_T c3_i1622;
  int32_T c3_i1623;
  for (c3_i1617 = 0; c3_i1617 < 36; c3_i1617 = c3_i1617 + 1) {
    c3_b_A[c3_i1617] = c3_A[c3_i1617];
  }

  for (c3_i1618 = 0; c3_i1618 < 6; c3_i1618 = c3_i1618 + 1) {
    c3_b_B[c3_i1618] = c3_B[c3_i1618];
  }

  for (c3_i1619 = 0; c3_i1619 < 36; c3_i1619 = c3_i1619 + 1) {
    c3_c_A[c3_i1619] = c3_b_A[c3_i1619];
  }

  for (c3_i1620 = 0; c3_i1620 < 6; c3_i1620 = c3_i1620 + 1) {
    c3_c_B[c3_i1620] = c3_b_B[c3_i1620];
  }

  for (c3_i1621 = 0; c3_i1621 < 6; c3_i1621 = c3_i1621 + 1) {
    c3_b_C[c3_i1621] = 0.0;
    c3_i1622 = 0;
    for (c3_i1623 = 0; c3_i1623 < 6; c3_i1623 = c3_i1623 + 1) {
      c3_b_C[c3_i1621] = c3_b_C[c3_i1621] + c3_c_A[c3_i1622 + c3_i1621] *
        c3_c_B[c3_i1623];
      c3_i1622 = c3_i1622 + 6;
    }
  }
}

static void c3_ad(SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance, real_T
                  c3_xi[6], real_T c3_adx[36])
{
  uint32_T c3_debug_family_var_map[6];
  static const char *c3_sv5[6] = { "w", "v", "nargin", "nargout", "xi", "adx" };

  real_T c3_w[3];
  real_T c3_v[3];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  int32_T c3_i1624;
  int32_T c3_i1625;
  int32_T c3_i1626;
  real_T c3_b_w[3];
  uint32_T c3_b_debug_family_var_map[4];
  static const char *c3_sv6[4] = { "nargin", "nargout", "w", "W" };

  real_T c3_b_nargin = 1.0;
  real_T c3_b_nargout = 1.0;
  real_T c3_W[9];
  int32_T c3_i1627;
  real_T c3_c_w[3];
  uint32_T c3_c_debug_family_var_map[4];
  real_T c3_c_nargin = 1.0;
  real_T c3_c_nargout = 1.0;
  real_T c3_b_W[9];
  int32_T c3_i1628;
  real_T c3_d_w[3];
  uint32_T c3_d_debug_family_var_map[4];
  real_T c3_d_nargin = 1.0;
  real_T c3_d_nargout = 1.0;
  real_T c3_c_W[9];
  int32_T c3_i1629;
  int32_T c3_i1630;
  int32_T c3_i1631;
  int32_T c3_i1632;
  int32_T c3_i1633;
  int32_T c3_i1634;
  int32_T c3_i1635;
  int32_T c3_i1636;
  int32_T c3_i1637;
  int32_T c3_i1638;
  int32_T c3_i1639;
  int32_T c3_i1640;
  int32_T c3_i1641;
  int32_T c3_i1642;
  int32_T c3_i1643;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c3_sv5, c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c3_w, c3_h_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c3_v, c3_h_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_f_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_f_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c3_xi, c3_b_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c3_adx, c3_j_sf_marshall, 5U);
  CV_SCRIPT_FCN(5, 0);
  _SFD_SCRIPT_CALL(5, 2);
  for (c3_i1624 = 0; c3_i1624 < 3; c3_i1624 = c3_i1624 + 1) {
    c3_w[c3_i1624] = c3_xi[c3_i1624 + 3];
  }

  _SFD_SCRIPT_CALL(5, 3);
  for (c3_i1625 = 0; c3_i1625 < 3; c3_i1625 = c3_i1625 + 1) {
    c3_v[c3_i1625] = c3_xi[c3_i1625];
  }

  _SFD_SCRIPT_CALL(5, 5);
  for (c3_i1626 = 0; c3_i1626 < 3; c3_i1626 = c3_i1626 + 1) {
    c3_b_w[c3_i1626] = c3_w[c3_i1626];
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
  for (c3_i1627 = 0; c3_i1627 < 3; c3_i1627 = c3_i1627 + 1) {
    c3_c_w[c3_i1627] = c3_v[c3_i1627];
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
  for (c3_i1628 = 0; c3_i1628 < 3; c3_i1628 = c3_i1628 + 1) {
    c3_d_w[c3_i1628] = c3_w[c3_i1628];
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
  c3_i1629 = 0;
  c3_i1630 = 0;
  for (c3_i1631 = 0; c3_i1631 < 3; c3_i1631 = c3_i1631 + 1) {
    for (c3_i1632 = 0; c3_i1632 < 3; c3_i1632 = c3_i1632 + 1) {
      c3_adx[c3_i1632 + c3_i1629] = c3_W[c3_i1632 + c3_i1630];
    }

    c3_i1629 = c3_i1629 + 6;
    c3_i1630 = c3_i1630 + 3;
  }

  c3_i1633 = 0;
  c3_i1634 = 0;
  for (c3_i1635 = 0; c3_i1635 < 3; c3_i1635 = c3_i1635 + 1) {
    for (c3_i1636 = 0; c3_i1636 < 3; c3_i1636 = c3_i1636 + 1) {
      c3_adx[(c3_i1636 + c3_i1633) + 18] = c3_b_W[c3_i1636 + c3_i1634];
    }

    c3_i1633 = c3_i1633 + 6;
    c3_i1634 = c3_i1634 + 3;
  }

  c3_i1637 = 0;
  for (c3_i1638 = 0; c3_i1638 < 3; c3_i1638 = c3_i1638 + 1) {
    for (c3_i1639 = 0; c3_i1639 < 3; c3_i1639 = c3_i1639 + 1) {
      c3_adx[(c3_i1639 + c3_i1637) + 3] = 0.0;
    }

    c3_i1637 = c3_i1637 + 6;
  }

  c3_i1640 = 0;
  c3_i1641 = 0;
  for (c3_i1642 = 0; c3_i1642 < 3; c3_i1642 = c3_i1642 + 1) {
    for (c3_i1643 = 0; c3_i1643 < 3; c3_i1643 = c3_i1643 + 1) {
      c3_adx[(c3_i1643 + c3_i1640) + 21] = c3_c_W[c3_i1643 + c3_i1641];
    }

    c3_i1640 = c3_i1640 + 6;
    c3_i1641 = c3_i1641 + 3;
  }

  _SFD_SCRIPT_CALL(5, -5);
  sf_debug_symbol_scope_pop();
}

static void c3_i_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c3_ceval_xgemm(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_m, int32_T c3_n, int32_T c3_k, real_T
  c3_alpha1, real_T c3_A[36], int32_T c3_ia0, int32_T c3_lda, real_T c3_B[36],
  int32_T c3_ib0, int32_T c3_ldb, real_T c3_beta1, real_T
  c3_C[36], int32_T c3_ic0, int32_T c3_ldc, real_T c3_b_C[36])
{
  char_T c3_TRANSA;
  char_T c3_TRANSB;
  int32_T c3_i1644;
  c3_TRANSA = 'N';
  c3_TRANSB = 'N';
  for (c3_i1644 = 0; c3_i1644 < 36; c3_i1644 = c3_i1644 + 1) {
    c3_b_C[c3_i1644] = c3_C[c3_i1644];
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

static void c3_j_eml_scalar_eg(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static real_T c3_ceval_xdot(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c3_n, real_T c3_x[6], int32_T c3_ix0,
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
  int32_T c3_i1645;
  real_T c3_b_u[36];
  int32_T c3_i1646;
  real_T c3_c_u[36];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1645 = 0; c3_i1645 < 36; c3_i1645 = c3_i1645 + 1) {
    c3_b_u[c3_i1645] = (*((real_T (*)[36])c3_u))[c3_i1645];
  }

  for (c3_i1646 = 0; c3_i1646 < 36; c3_i1646 = c3_i1646 + 1) {
    c3_c_u[c3_i1646] = c3_b_u[c3_i1646];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 36));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_b_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1647;
  real_T c3_b_u[6];
  int32_T c3_i1648;
  real_T c3_c_u[6];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1647 = 0; c3_i1647 < 6; c3_i1647 = c3_i1647 + 1) {
    c3_b_u[c3_i1647] = (*((real_T (*)[6])c3_u))[c3_i1647];
  }

  for (c3_i1648 = 0; c3_i1648 < 6; c3_i1648 = c3_i1648 + 1) {
    c3_c_u[c3_i1648] = c3_b_u[c3_i1648];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 6));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_c_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1649;
  real_T c3_b_u[54];
  int32_T c3_i1650;
  real_T c3_c_u[54];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1649 = 0; c3_i1649 < 54; c3_i1649 = c3_i1649 + 1) {
    c3_b_u[c3_i1649] = (*((real_T (*)[54])c3_u))[c3_i1649];
  }

  for (c3_i1650 = 0; c3_i1650 < 54; c3_i1650 = c3_i1650 + 1) {
    c3_c_u[c3_i1650] = c3_b_u[c3_i1650];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 54));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_d_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1651;
  real_T c3_b_u[18];
  int32_T c3_i1652;
  real_T c3_c_u[18];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1651 = 0; c3_i1651 < 18; c3_i1651 = c3_i1651 + 1) {
    c3_b_u[c3_i1651] = (*((real_T (*)[18])c3_u))[c3_i1651];
  }

  for (c3_i1652 = 0; c3_i1652 < 18; c3_i1652 = c3_i1652 + 1) {
    c3_c_u[c3_i1652] = c3_b_u[c3_i1652];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 18));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_e_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1653;
  int32_T c3_i1654;
  int32_T c3_i1655;
  real_T c3_b_u[28];
  int32_T c3_i1656;
  int32_T c3_i1657;
  int32_T c3_i1658;
  real_T c3_c_u[28];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_i1653 = 0;
  for (c3_i1654 = 0; c3_i1654 < 7; c3_i1654 = c3_i1654 + 1) {
    for (c3_i1655 = 0; c3_i1655 < 4; c3_i1655 = c3_i1655 + 1) {
      c3_b_u[c3_i1655 + c3_i1653] = (*((real_T (*)[28])c3_u))[c3_i1655 +
        c3_i1653];
    }

    c3_i1653 = c3_i1653 + 4;
  }

  c3_i1656 = 0;
  for (c3_i1657 = 0; c3_i1657 < 7; c3_i1657 = c3_i1657 + 1) {
    for (c3_i1658 = 0; c3_i1658 < 4; c3_i1658 = c3_i1658 + 1) {
      c3_c_u[c3_i1658 + c3_i1656] = c3_b_u[c3_i1658 + c3_i1656];
    }

    c3_i1656 = c3_i1656 + 4;
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
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
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
  int32_T c3_i1659;
  int32_T c3_i1660;
  int32_T c3_i1661;
  real_T c3_b_u[9];
  int32_T c3_i1662;
  int32_T c3_i1663;
  int32_T c3_i1664;
  real_T c3_c_u[9];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_i1659 = 0;
  for (c3_i1660 = 0; c3_i1660 < 3; c3_i1660 = c3_i1660 + 1) {
    for (c3_i1661 = 0; c3_i1661 < 3; c3_i1661 = c3_i1661 + 1) {
      c3_b_u[c3_i1661 + c3_i1659] = (*((real_T (*)[9])c3_u))[c3_i1661 + c3_i1659];
    }

    c3_i1659 = c3_i1659 + 3;
  }

  c3_i1662 = 0;
  for (c3_i1663 = 0; c3_i1663 < 3; c3_i1663 = c3_i1663 + 1) {
    for (c3_i1664 = 0; c3_i1664 < 3; c3_i1664 = c3_i1664 + 1) {
      c3_c_u[c3_i1664 + c3_i1662] = c3_b_u[c3_i1664 + c3_i1662];
    }

    c3_i1662 = c3_i1662 + 3;
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 2, 3, 3));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_h_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1665;
  real_T c3_b_u[3];
  int32_T c3_i1666;
  real_T c3_c_u[3];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1665 = 0; c3_i1665 < 3; c3_i1665 = c3_i1665 + 1) {
    c3_b_u[c3_i1665] = (*((real_T (*)[3])c3_u))[c3_i1665];
  }

  for (c3_i1666 = 0; c3_i1666 < 3; c3_i1666 = c3_i1666 + 1) {
    c3_c_u[c3_i1666] = c3_b_u[c3_i1666];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 3));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_i_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1667;
  int32_T c3_i1668;
  int32_T c3_i1669;
  real_T c3_b_u[16];
  int32_T c3_i1670;
  int32_T c3_i1671;
  int32_T c3_i1672;
  real_T c3_c_u[16];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_i1667 = 0;
  for (c3_i1668 = 0; c3_i1668 < 4; c3_i1668 = c3_i1668 + 1) {
    for (c3_i1669 = 0; c3_i1669 < 4; c3_i1669 = c3_i1669 + 1) {
      c3_b_u[c3_i1669 + c3_i1667] = (*((real_T (*)[16])c3_u))[c3_i1669 +
        c3_i1667];
    }

    c3_i1667 = c3_i1667 + 4;
  }

  c3_i1670 = 0;
  for (c3_i1671 = 0; c3_i1671 < 4; c3_i1671 = c3_i1671 + 1) {
    for (c3_i1672 = 0; c3_i1672 < 4; c3_i1672 = c3_i1672 + 1) {
      c3_c_u[c3_i1672 + c3_i1670] = c3_b_u[c3_i1672 + c3_i1670];
    }

    c3_i1670 = c3_i1670 + 4;
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 2, 4, 4));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_j_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1673;
  int32_T c3_i1674;
  int32_T c3_i1675;
  real_T c3_b_u[36];
  int32_T c3_i1676;
  int32_T c3_i1677;
  int32_T c3_i1678;
  real_T c3_c_u[36];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_i1673 = 0;
  for (c3_i1674 = 0; c3_i1674 < 6; c3_i1674 = c3_i1674 + 1) {
    for (c3_i1675 = 0; c3_i1675 < 6; c3_i1675 = c3_i1675 + 1) {
      c3_b_u[c3_i1675 + c3_i1673] = (*((real_T (*)[36])c3_u))[c3_i1675 +
        c3_i1673];
    }

    c3_i1673 = c3_i1673 + 6;
  }

  c3_i1676 = 0;
  for (c3_i1677 = 0; c3_i1677 < 6; c3_i1677 = c3_i1677 + 1) {
    for (c3_i1678 = 0; c3_i1678 < 6; c3_i1678 = c3_i1678 + 1) {
      c3_c_u[c3_i1678 + c3_i1676] = c3_b_u[c3_i1678 + c3_i1676];
    }

    c3_i1676 = c3_i1676 + 6;
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 2, 6, 6));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static const mxArray *c3_k_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  int32_T c3_i1679;
  real_T c3_b_u[4];
  int32_T c3_i1680;
  real_T c3_c_u[4];
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  for (c3_i1679 = 0; c3_i1679 < 4; c3_i1679 = c3_i1679 + 1) {
    c3_b_u[c3_i1679] = (*((real_T (*)[4])c3_u))[c3_i1679];
  }

  for (c3_i1680 = 0; c3_i1680 < 4; c3_i1680 = c3_i1680 + 1) {
    c3_c_u[c3_i1680] = c3_b_u[c3_i1680];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 4));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

const mxArray *sf_c3_EurlerDynJointVerify_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_ResolvedFunctionInfo c3_info[111];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i1681;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  c3_b_info_helper(c3_info);
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 111));
  for (c3_i1681 = 0; c3_i1681 < 111; c3_i1681 = c3_i1681 + 1) {
    c3_r0 = &c3_info[c3_i1681];
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context",
                    "nameCaptureInfo", c3_i1681);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name",
                    "nameCaptureInfo", c3_i1681);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c3_i1681);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c3_i1681);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c3_i1681);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo",
                    c3_i1681);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo",
                    c3_i1681);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m0);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[111])
{
  c3_info[0].context = "";
  c3_info[0].name = "zeros";
  c3_info[0].dominantType = "double";
  c3_info[0].resolved = "[B]zeros";
  c3_info[0].fileLength = 0U;
  c3_info[0].fileTime1 = 0U;
  c3_info[0].fileTime2 = 0U;
  c3_info[1].context = "";
  c3_info[1].name = "DynEuler";
  c3_info[1].dominantType = "double";
  c3_info[1].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/DynEuler.m";
  c3_info[1].fileLength = 7407U;
  c3_info[1].fileTime1 = 1407920718U;
  c3_info[1].fileTime2 = 0U;
  c3_info[2].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEuler.m";
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

static void c3_b_info_helper(c3_ResolvedFunctionInfo c3_info[111])
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
  c3_info[80].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEuler.m";
  c3_info[80].name = "reshape";
  c3_info[80].dominantType = "double";
  c3_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c3_info[80].fileLength = 4857U;
  c3_info[80].fileTime1 = 1242276774U;
  c3_info[80].fileTime2 = 0U;
  c3_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size";
  c3_info[81].name = "eml_index_prod";
  c3_info[81].dominantType = "int32";
  c3_info[81].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_prod.m";
  c3_info[81].fileLength = 547U;
  c3_info[81].fileTime1 = 1211194426U;
  c3_info[81].fileTime2 = 0U;
  c3_info[82].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEuler.m";
  c3_info[82].name = "mldivide";
  c3_info[82].dominantType = "double";
  c3_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c3_info[82].fileLength = 494U;
  c3_info[82].fileTime1 = 1277726622U;
  c3_info[82].fileTime2 = 0U;
  c3_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c3_info[83].name = "eml_lusolve";
  c3_info[83].dominantType = "double";
  c3_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c3_info[83].fileLength = 5239U;
  c3_info[83].fileTime1 = 1264408552U;
  c3_info[83].fileTime2 = 0U;
  c3_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c3_info[84].name = "eml_xgetrf";
  c3_info[84].dominantType = "int32";
  c3_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c3_info[84].fileLength = 204U;
  c3_info[84].fileTime1 = 1271383994U;
  c3_info[84].fileTime2 = 0U;
  c3_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c3_info[85].name = "eml_lapack_xgetrf";
  c3_info[85].dominantType = "int32";
  c3_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c3_info[85].fileLength = 211U;
  c3_info[85].fileTime1 = 1271383994U;
  c3_info[85].fileTime2 = 0U;
  c3_info[86].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c3_info[86].name = "eml_matlab_zgetrf";
  c3_info[86].dominantType = "int32";
  c3_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[86].fileLength = 2193U;
  c3_info[86].fileTime1 = 1271383998U;
  c3_info[86].fileTime2 = 0U;
  c3_info[87].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[87].name = "realmin";
  c3_info[87].dominantType = "char";
  c3_info[87].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c3_info[87].fileLength = 749U;
  c3_info[87].fileTime1 = 1226552078U;
  c3_info[87].fileTime2 = 0U;
  c3_info[88].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[88].name = "colon";
  c3_info[88].dominantType = "int32";
  c3_info[88].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c3_info[88].fileLength = 8633U;
  c3_info[88].fileTime1 = 1273822662U;
  c3_info[88].fileTime2 = 0U;
  c3_info[89].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c3_info[89].name = "floor";
  c3_info[89].dominantType = "double";
  c3_info[89].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c3_info[89].fileLength = 332U;
  c3_info[89].fileTime1 = 1203422822U;
  c3_info[89].fileTime2 = 0U;
  c3_info[90].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c3_info[90].name = "intmin";
  c3_info[90].dominantType = "char";
  c3_info[90].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c3_info[90].fileLength = 1505U;
  c3_info[90].fileTime1 = 1192445128U;
  c3_info[90].fileTime2 = 0U;
  c3_info[91].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon";
  c3_info[91].name = "transpose";
  c3_info[91].dominantType = "int32";
  c3_info[91].resolved = "[B]transpose";
  c3_info[91].fileLength = 0U;
  c3_info[91].fileTime1 = 0U;
  c3_info[91].fileTime2 = 0U;
  c3_info[92].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[92].name = "eml_ixamax";
  c3_info[92].dominantType = "int32";
  c3_info[92].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c3_info[92].fileLength = 731U;
  c3_info[92].fileTime1 = 1209309244U;
  c3_info[92].fileTime2 = 0U;
  c3_info[93].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c3_info[93].name = "eml_refblas_ixamax";
  c3_info[93].dominantType = "int32";
  c3_info[93].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[93].fileLength = 740U;
  c3_info[93].fileTime1 = 1192445266U;
  c3_info[93].fileTime2 = 0U;
  c3_info[94].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[94].name = "eml_xcabs1";
  c3_info[94].dominantType = "double";
  c3_info[94].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c3_info[94].fileLength = 419U;
  c3_info[94].fileTime1 = 1209309246U;
  c3_info[94].fileTime2 = 0U;
  c3_info[95].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[95].name = "eml_xswap";
  c3_info[95].dominantType = "int32";
  c3_info[95].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c3_info[95].fileLength = 1330U;
  c3_info[95].fileTime1 = 1209309260U;
  c3_info[95].fileTime2 = 0U;
  c3_info[96].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c3_info[96].name = "eml_refblas_xswap";
  c3_info[96].dominantType = "int32";
  c3_info[96].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c3_info[96].fileLength = 905U;
  c3_info[96].fileTime1 = 1238412670U;
  c3_info[96].fileTime2 = 0U;
  c3_info[97].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[97].name = "eml_xgeru";
  c3_info[97].dominantType = "int32";
  c3_info[97].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c3_info[97].fileLength = 2462U;
  c3_info[97].fileTime1 = 1209309256U;
  c3_info[97].fileTime2 = 0U;
  c3_info[98].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c3_info[98].name = "eml_xger";
  c3_info[98].dominantType = "int32";
  c3_info[98].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c3_info[98].fileLength = 2168U;
  c3_info[98].fileTime1 = 1209309254U;
  c3_info[98].fileTime2 = 0U;
  c3_info[99].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c3_info[99].name = "eml_refblas_xger";
  c3_info[99].dominantType = "int32";
  c3_info[99].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c3_info[99].fileLength = 411U;
  c3_info[99].fileTime1 = 1211194448U;
  c3_info[99].fileTime2 = 0U;
  c3_info[100].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c3_info[100].name = "eml_refblas_xgerx";
  c3_info[100].dominantType = "int32";
  c3_info[100].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[100].fileLength = 2231U;
  c3_info[100].fileTime1 = 1238412668U;
  c3_info[100].fileTime2 = 0U;
  c3_info[101].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c3_info[101].name = "eml_xtrsm";
  c3_info[101].dominantType = "int32";
  c3_info[101].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c3_info[101].fileLength = 2383U;
  c3_info[101].fileTime1 = 1209309262U;
  c3_info[101].fileTime2 = 0U;
  c3_info[102].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c3_info[102].name = "eml_refblas_xtrsm";
  c3_info[102].dominantType = "int32";
  c3_info[102].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c3_info[102].fileLength = 13101U;
  c3_info[102].fileTime1 = 1252487206U;
  c3_info[102].fileTime2 = 0U;
  c3_info[103].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEuler.m";
  c3_info[103].name = "Adj";
  c3_info[103].dominantType = "double";
  c3_info[103].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/basicfunction/Adj.m";
  c3_info[103].fileLength = 187U;
  c3_info[103].fileTime1 = 1399862722U;
  c3_info[103].fileTime2 = 0U;
  c3_info[104].context = "[E]D:/Learn/Project_Matlab/Fanuc/DynEuler.m";
  c3_info[104].name = "ad";
  c3_info[104].dominantType = "double";
  c3_info[104].resolved =
    "[E]D:/Learn/Project_Matlab/GoogolTraj/basicfunction/ad.m";
  c3_info[104].fileLength = 112U;
  c3_info[104].fileTime1 = 1365307014U;
  c3_info[104].fileTime2 = 0U;
  c3_info[105].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[105].name = "eml_xdotu";
  c3_info[105].dominantType = "int32";
  c3_info[105].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c3_info[105].fileLength = 1453U;
  c3_info[105].fileTime1 = 1209309250U;
  c3_info[105].fileTime2 = 0U;
  c3_info[106].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c3_info[106].name = "eml_xdot";
  c3_info[106].dominantType = "int32";
  c3_info[106].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c3_info[106].fileLength = 1330U;
  c3_info[106].fileTime1 = 1209309248U;
  c3_info[106].fileTime2 = 0U;
  c3_info[107].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c3_info[107].name = "eml_refblas_xdot";
  c3_info[107].dominantType = "int32";
  c3_info[107].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c3_info[107].fileLength = 343U;
  c3_info[107].fileTime1 = 1211194442U;
  c3_info[107].fileTime2 = 0U;
  c3_info[108].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c3_info[108].name = "eml_refblas_xdotx";
  c3_info[108].dominantType = "int32";
  c3_info[108].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[108].fileLength = 1605U;
  c3_info[108].fileTime1 = 1236232078U;
  c3_info[108].fileTime2 = 0U;
  c3_info[109].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[109].name = "isequal";
  c3_info[109].dominantType = "char";
  c3_info[109].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c3_info[109].fileLength = 180U;
  c3_info[109].fileTime1 = 1226552070U;
  c3_info[109].fileTime2 = 0U;
  c3_info[110].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c3_info[110].name = "eml_isequal_core";
  c3_info[110].dominantType = "char";
  c3_info[110].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c3_info[110].fileLength = 4192U;
  c3_info[110].fileTime1 = 1258039010U;
  c3_info[110].fileTime2 = 0U;
}

static const mxArray *c3_l_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  boolean_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_b_u = *((boolean_T *)c3_u);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static void c3_emlrt_marshallIn(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *c3_JntAcc, const char_T *
  c3_name, real_T c3_y[36])
{
  real_T c3_dv155[36];
  int32_T c3_i1682;
  sf_mex_import(c3_name, sf_mex_dup(c3_JntAcc), c3_dv155, 1, 0, 0U, 1, 0U, 1, 36);
  for (c3_i1682 = 0; c3_i1682 < 36; c3_i1682 = c3_i1682 + 1) {
    c3_y[c3_i1682] = c3_dv155[c3_i1682];
  }

  sf_mex_destroy(&c3_JntAcc);
}

static void c3_b_emlrt_marshallIn(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *c3_Torque, const char_T *
  c3_name, real_T c3_y[6])
{
  real_T c3_dv156[6];
  int32_T c3_i1683;
  sf_mex_import(c3_name, sf_mex_dup(c3_Torque), c3_dv156, 1, 0, 0U, 1, 0U, 1, 6);
  for (c3_i1683 = 0; c3_i1683 < 6; c3_i1683 = c3_i1683 + 1) {
    c3_y[c3_i1683] = c3_dv156[c3_i1683];
  }

  sf_mex_destroy(&c3_Torque);
}

static uint8_T c3_c_emlrt_marshallIn(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *
  c3_b_is_active_c3_EurlerDynJointVerify, const char_T *c3_name)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_name, sf_mex_dup(c3_b_is_active_c3_EurlerDynJointVerify),
                &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_b_is_active_c3_EurlerDynJointVerify);
  return c3_y;
}

static void init_dsm_address_info(SFc3_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_EurlerDynJointVerify_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3247120120U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1837240913U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2473955269U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3717063645U);
}

mxArray *sf_c3_EurlerDynJointVerify_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(113771871U);
    pr[1] = (double)(2927184310U);
    pr[2] = (double)(1098685041U);
    pr[3] = (double)(2457699446U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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

static mxArray *sf_get_sim_state_info_c3_EurlerDynJointVerify(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[17],T\"JntAcc\",},{M[1],M[18],T\"JntF\",},{M[1],M[16],T\"JntVel\",},{M[1],M[5],T\"Torque\",},{M[8],M[0],T\"is_active_c3_EurlerDynJointVerify\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_EurlerDynJointVerify_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
    chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_EurlerDynJointVerifyMachineNumber_,
           3,
           1,
           1,
           12,
           0,
           0,
           0,
           0,
           6,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_EurlerDynJointVerifyMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_EurlerDynJointVerifyMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds
            (_EurlerDynJointVerifyMachineNumber_,
             chartInstance->chartNumber,
             0,
             0,
             0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Pos");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Torque");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Vel");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Acc");
          _SFD_SET_DATA_PROPS(4,10,0,0,"DH_EU");
          _SFD_SET_DATA_PROPS(5,10,0,0,"Ma_EU");
          _SFD_SET_DATA_PROPS(6,10,0,0,"Cen_EU");
          _SFD_SET_DATA_PROPS(7,10,0,0,"Ie_EU");
          _SFD_SET_DATA_PROPS(8,10,0,0,"Ft_EU");
          _SFD_SET_DATA_PROPS(9,2,0,1,"JntVel");
          _SFD_SET_DATA_PROPS(10,2,0,1,"JntAcc");
          _SFD_SET_DATA_PROPS(11,2,0,1,"JntF");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,265);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"DynEuler",531,-1,7407);
        _SFD_CV_INIT_SCRIPT(1,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"expg",0,-1,280);
        _SFD_CV_INIT_SCRIPT_IF(1,0,68,76,110,232);
        _SFD_CV_INIT_SCRIPT(2,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"expr",0,-1,182);
        _SFD_CV_INIT_SCRIPT_IF(2,0,41,49,66,182);
        _SFD_CV_INIT_SCRIPT(3,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(3,0,"hat",0,-1,85);
        _SFD_CV_INIT_SCRIPT(4,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(4,0,"Adj",0,-1,180);
        _SFD_CV_INIT_SCRIPT(5,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(5,0,"ad",0,-1,106);
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
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 18;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 54;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 36;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 36;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 36;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshall);
        }

        {
          real_T (*c3_Pos)[6];
          real_T (*c3_Torque)[6];
          real_T (*c3_Vel)[6];
          real_T (*c3_Acc)[6];
          real_T (*c3_JntVel)[36];
          real_T (*c3_JntAcc)[36];
          real_T (*c3_JntF)[36];
          c3_JntF = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
          c3_JntAcc = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
          c3_JntVel = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 2);
          c3_Acc = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
          c3_Vel = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
          c3_Torque = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c3_Pos = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_Pos);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_Torque);
          _SFD_SET_DATA_VALUE_PTR(2U, *c3_Vel);
          _SFD_SET_DATA_VALUE_PTR(3U, *c3_Acc);
          _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c3_DH_EU);
          _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c3_Ma_EU);
          _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c3_Cen_EU);
          _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c3_Ie_EU);
          _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c3_Ft_EU);
          _SFD_SET_DATA_VALUE_PTR(9U, *c3_JntVel);
          _SFD_SET_DATA_VALUE_PTR(10U, *c3_JntAcc);
          _SFD_SET_DATA_VALUE_PTR(11U, *c3_JntF);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration
        (_EurlerDynJointVerifyMachineNumber_,chartInstance->chartNumber,
         chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c3_EurlerDynJointVerify(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_EurlerDynJointVerify
    ((SFc3_EurlerDynJointVerifyInstanceStruct*) chartInstanceVar);
  initialize_c3_EurlerDynJointVerify((SFc3_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_EurlerDynJointVerify(void *chartInstanceVar)
{
  enable_c3_EurlerDynJointVerify((SFc3_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c3_EurlerDynJointVerify(void *chartInstanceVar)
{
  disable_c3_EurlerDynJointVerify((SFc3_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c3_EurlerDynJointVerify(void *chartInstanceVar)
{
  sf_c3_EurlerDynJointVerify((SFc3_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c3_EurlerDynJointVerify(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_EurlerDynJointVerify
    ((SFc3_EurlerDynJointVerifyInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c3_EurlerDynJointVerify();/* state var info */
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

static void sf_internal_set_sim_state_c3_EurlerDynJointVerify(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_EurlerDynJointVerify();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_EurlerDynJointVerify((SFc3_EurlerDynJointVerifyInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c3_EurlerDynJointVerify(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_EurlerDynJointVerify(S);
}

static void sf_opaque_set_sim_state_c3_EurlerDynJointVerify(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c3_EurlerDynJointVerify(S, st);
}

static void sf_opaque_terminate_c3_EurlerDynJointVerify(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_EurlerDynJointVerifyInstanceStruct*) chartInstanceVar
      )->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_EurlerDynJointVerify((SFc3_EurlerDynJointVerifyInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c3_EurlerDynJointVerify
    ((SFc3_EurlerDynJointVerifyInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_EurlerDynJointVerify(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_EurlerDynJointVerify
      ((SFc3_EurlerDynJointVerifyInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_EurlerDynJointVerify(SimStruct *S)
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
      (int_T)sf_is_chart_inlinable(S,"EurlerDynJointVerify",
      "EurlerDynJointVerify",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"EurlerDynJointVerify",
                "EurlerDynJointVerify",3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"EurlerDynJointVerify",
      "EurlerDynJointVerify",3,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"EurlerDynJointVerify",
        "EurlerDynJointVerify",3,3);
      sf_mark_chart_reusable_outputs(S,"EurlerDynJointVerify",
        "EurlerDynJointVerify",3,4);
    }

    sf_set_rtw_dwork_info(S,"EurlerDynJointVerify","EurlerDynJointVerify",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2814025573U));
  ssSetChecksum1(S,(146709070U));
  ssSetChecksum2(S,(4212635116U));
  ssSetChecksum3(S,(3893566582U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_EurlerDynJointVerify(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "EurlerDynJointVerify", "EurlerDynJointVerify",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_EurlerDynJointVerify(SimStruct *S)
{
  SFc3_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc3_EurlerDynJointVerifyInstanceStruct *)malloc(sizeof
    (SFc3_EurlerDynJointVerifyInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_EurlerDynJointVerifyInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_EurlerDynJointVerify;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c3_EurlerDynJointVerify;
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

void c3_EurlerDynJointVerify_method_dispatcher(SimStruct *S, int_T method, void *
  data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_EurlerDynJointVerify(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_EurlerDynJointVerify(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_EurlerDynJointVerify(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_EurlerDynJointVerify_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
