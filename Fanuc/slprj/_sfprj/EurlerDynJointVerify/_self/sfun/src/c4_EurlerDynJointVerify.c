/* Include files */

#include "blascompat32.h"
#include "EurlerDynJointVerify_sfun.h"
#include "c4_EurlerDynJointVerify.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "EurlerDynJointVerify_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c4_debug_family_names[9] = { "gd", "theta_total", "num_total",
  "nargin", "nargout", "EndPos", "init_Rot", "L", "theta" };

static const char *c4_b_debug_family_names[6] = { "nargin", "nargout", "x",
  "xmin", "xmax", "isIn" };

static const char *c4_c_debug_family_names[4] = { "nargin", "nargout", "w", "wh"
};

static const char *c4_d_debug_family_names[6] = { "wh", "nargin", "nargout", "w",
  "theta", "R" };

static const char *c4_e_debug_family_names[9] = { "v", "w", "R", "p", "nargin",
  "nargout", "kx", "theta", "g" };

static const char *c4_f_debug_family_names[18] = { "velociy", "w", "r", "u", "v",
  "up", "vp", "dp2", "theta0", "phi", "p", "q", "d", "nargin", "nargout", "kx",
  "theta", "Nsol" };

static const char *c4_g_debug_family_names[6] = { "nargin", "nargout", "x",
  "xmin", "xmax", "isIn" };

static const char *c4_h_debug_family_names[13] = { "velociy", "w", "r", "u", "v",
  "up", "vp", "nargin", "nargout", "kx", "p", "q", "theta" };

static const char *c4_i_debug_family_names[10] = { "A", "vec", "cof", "nargin",
  "nargout", "w1", "w2", "r1", "r2", "r" };

static const char *c4_j_debug_family_names[13] = { "velociy", "w", "r", "u", "v",
  "up", "vp", "nargin", "nargout", "kx", "p", "q", "theta" };

static const char *c4_k_debug_family_names[13] = { "velociy", "w", "r", "u", "v",
  "up", "vp", "nargin", "nargout", "kx", "p", "q", "theta" };

static const char *c4_l_debug_family_names[25] = { "velociy1", "w1", "r1",
  "velociy2", "w2", "r2", "r", "u", "v", "alpha", "beta", "ySqu", "i", "y", "z",
  "c", "nargin", "nargout", "kx1", "kx2", "p", "q", "theta1", "theta2", "Nsol" };

static const char *c4_m_debug_family_names[71] = { "Min1", "Max1", "Min2",
  "Max2", "Min3", "Max3", "Min4", "Max4", "Min5", "Max5", "Min6", "Max6", "L1",
  "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9", "s_origin", "w_x", "w_y",
  "w_z", "w1", "q1", "kx1", "w2", "q2", "kx2", "w3", "q3", "kx3", "pw", "w4",
  "q4", "kx4", "w5", "q5", "kx5", "w6", "q6", "kx6", "q7", "gst0", "g1", "p1",
  "theta_1", "p2", "d", "theta_3", "Num_3", "c3", "p3", "theta_2", "g2", "p4",
  "theta_4", "theta_5", "Num_45", "c45", "g3", "p5", "theta_6", "nargin",
  "nargout", "gd", "L", "theta", "Num" };

/* Function Declarations */
static void initialize_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void initialize_params_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void enable_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void disable_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void set_sim_state_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance, const mxArray *c4_st);
static void finalize_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void sf_c4_EurlerDynJointVerify(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void compInitSubchartSimstructsFcn_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static void c4_inv_kin(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_gd[16], real_T c4_b_L[9], real_T c4_theta[24], real_T *c4_Num);
static void c4_cross(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                     real_T c4_a[3], real_T c4_b[3], real_T c4_c[3]);
static boolean_T c4_all(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  boolean_T c4_x[2]);
static void c4_mrdivide(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_A[16], real_T c4_B[16], real_T c4_y[16]);
static real_T c4_power(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_a, real_T c4_b);
static void c4_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c4_eml_error(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void c4_eps(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void c4_eml_matlab_zgetrf(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_A[16], real_T c4_b_A[16], int32_T c4_ipiv[4],
  int32_T *c4_info);
static int32_T c4_eml_ixamax(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[16], int32_T c4_ix0);
static int32_T c4_ceval_ixamax(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[16], int32_T c4_ix0, int32_T c4_incx);
static void c4_ceval_xswap(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[16], int32_T c4_ix0, int32_T c4_incx,
  int32_T c4_iy0, int32_T c4_incy, real_T c4_b_x[16]);
static void c4_ceval_xger(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  int32_T c4_m, int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_incx,
  int32_T c4_iy0, int32_T c4_incy, real_T c4_A[16], int32_T c4_ia0, int32_T
  c4_lda, real_T c4_b_A[16]);
static void c4_eml_warning(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c4_b_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c4_eml_xtrsm(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_A[16], real_T c4_B[16], real_T c4_b_B[16]);
static void c4_c_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c4_eml_blas_xtrsm(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_m, int32_T c4_n, real_T c4_alpha1, real_T c4_A[16],
  int32_T c4_ia0, int32_T c4_lda, real_T c4_B[16], int32_T c4_ib0, int32_T
  c4_ldb, real_T c4_b_B[16]);
static void c4_d_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static real_T c4_atan2(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_y, real_T c4_x);
static boolean_T c4_isInRange(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_x, real_T c4_xmin, real_T c4_xmax);
static void c4_expWre(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c4_kx[6], real_T c4_theta, real_T c4_g[16]);
static real_T c4_length(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance);
static void c4_eye(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                   real_T c4_I[9]);
static void c4_expRot(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c4_w[3], real_T c4_theta, real_T c4_R[9]);
static void c4_e_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c4_f_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c4_subPro3(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_kx[6], real_T c4_p[4], real_T c4_q[4], real_T c4_d[4], real_T
  c4_theta[2], real_T *c4_Nsol);
static void c4_g_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static real_T c4_ceval_xdot(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[3], int32_T c4_ix0, int32_T c4_incx,
  real_T c4_y[3], int32_T c4_iy0, int32_T c4_incy);
static real_T c4_mpower(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_a);
static real_T c4_norm(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c4_x[3]);
static real_T c4_ceval_xnrm2(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[3], int32_T c4_ix0, int32_T c4_incx);
static void c4_b_eml_error(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static void c4_b_isInRange(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_x[2], real_T c4_xmin, real_T c4_xmax, boolean_T
  c4_isIn[2]);
static boolean_T c4_any(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  boolean_T c4_x[2]);
static real_T c4_subPro1(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_kx[6], real_T c4_p[4], real_T c4_q[4]);
static void c4_subPro2(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_kx1[6], real_T c4_kx2[6], real_T c4_p[4], real_T c4_q[4], real_T
  c4_theta1[2], real_T c4_theta2[2], real_T *c4_Nsol);
static void c4_findCommon(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_w1[3], real_T c4_w2[3], real_T c4_r1[3], real_T c4_r2[3], real_T
  c4_r[3]);
static real_T c4_det(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                     real_T c4_x[4]);
static void c4_b_eml_matlab_zgetrf(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_A[4], real_T c4_b_A[4], int32_T c4_ipiv[2], int32_T *
  c4_info);
static int32_T c4_b_eml_ixamax(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_x[4]);
static int32_T c4_b_ceval_ixamax(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[4], int32_T c4_ix0, int32_T c4_incx);
static void c4_b_ceval_xswap(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[4], int32_T c4_ix0, int32_T c4_incx,
  int32_T c4_iy0, int32_T c4_incy, real_T c4_b_x[4]);
static void c4_b_ceval_xger(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_m, int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0,
  int32_T c4_incx, int32_T c4_iy0, int32_T c4_incy, real_T c4_A[4], int32_T
  c4_ia0, int32_T c4_lda, real_T c4_b_A[4]);
static void c4_c_eml_error(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);
static real_T c4_b_subPro1(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_kx[6], real_T c4_p[4], real_T c4_q[3]);
static real_T c4_c_subPro1(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_kx[6], real_T c4_p[3], real_T c4_q[4]);
static const mxArray *c4_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_b_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_c_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_d_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_e_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_f_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_g_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_h_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_i_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_j_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_k_sf_marshall(void *chartInstanceVoid, void *c4_u);
static const mxArray *c4_l_sf_marshall(void *chartInstanceVoid, void *c4_u);
static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[121]);
static void c4_b_info_helper(c4_ResolvedFunctionInfo c4_info[121]);
static void c4_emlrt_marshallIn(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *c4_theta, const char_T *c4_name, real_T c4_y[6]);
static uint8_T c4_b_emlrt_marshallIn(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_EurlerDynJointVerify, const
  char_T *c4_name);
static void init_dsm_address_info(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_is_active_c4_EurlerDynJointVerify = 0U;
}

static void initialize_params_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  real_T c4_dv0[9];
  int32_T c4_i0;
  real_T c4_dv1[9];
  int32_T c4_i1;
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'init_Rot' in the parent workspace.\n");
  sf_mex_import("init_Rot", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                c4_dv0, 0, 0, 0U, 1, 0U, 2, 3, 3);
  for (c4_i0 = 0; c4_i0 < 9; c4_i0 = c4_i0 + 1) {
    chartInstance->c4_init_Rot[c4_i0] = c4_dv0[c4_i0];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Embedded MATLAB Runtime Error (chart): Error evaluating data 'L' in the parent workspace.\n");
  sf_mex_import("L", sf_mex_get_sfun_param(chartInstance->S, 0, 0), c4_dv1, 0, 0,
                0U, 1, 0U, 2, 1, 9);
  for (c4_i1 = 0; c4_i1 < 9; c4_i1 = c4_i1 + 1) {
    chartInstance->c4_L[c4_i1] = c4_dv1[c4_i1];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c4_update_debugger_state_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  const mxArray *c4_st = NULL;
  const mxArray *c4_y = NULL;
  int32_T c4_i2;
  real_T c4_hoistedGlobal[6];
  int32_T c4_i3;
  real_T c4_u[6];
  const mxArray *c4_b_y = NULL;
  uint8_T c4_b_hoistedGlobal;
  uint8_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  real_T (*c4_theta)[6];
  c4_theta = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(2));
  for (c4_i2 = 0; c4_i2 < 6; c4_i2 = c4_i2 + 1) {
    c4_hoistedGlobal[c4_i2] = (*c4_theta)[c4_i2];
  }

  for (c4_i3 = 0; c4_i3 < 6; c4_i3 = c4_i3 + 1) {
    c4_u[c4_i3] = c4_hoistedGlobal[c4_i3];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 6));
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_b_hoistedGlobal = chartInstance->c4_is_active_c4_EurlerDynJointVerify;
  c4_b_u = c4_b_hoistedGlobal;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c4_y, 1, c4_c_y);
  sf_mex_assign(&c4_st, c4_y);
  return c4_st;
}

static void set_sim_state_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv2[6];
  int32_T c4_i4;
  real_T (*c4_theta)[6];
  c4_theta = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = TRUE;
  c4_u = sf_mex_dup(c4_st);
  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)),
                      "theta", c4_dv2);
  for (c4_i4 = 0; c4_i4 < 6; c4_i4 = c4_i4 + 1) {
    (*c4_theta)[c4_i4] = c4_dv2[c4_i4];
  }

  chartInstance->c4_is_active_c4_EurlerDynJointVerify = c4_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
     "is_active_c4_EurlerDynJointVerify");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_EurlerDynJointVerify(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static void sf_c4_EurlerDynJointVerify(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
  int32_T c4_i5;
  int32_T c4_i6;
  int32_T c4_i7;
  int32_T c4_i8;
  int32_T c4_previousEvent;
  int32_T c4_i9;
  real_T c4_hoistedGlobal[3];
  int32_T c4_i10;
  real_T c4_b_hoistedGlobal[9];
  int32_T c4_i11;
  real_T c4_c_hoistedGlobal[9];
  int32_T c4_i12;
  real_T c4_EndPos[3];
  int32_T c4_i13;
  real_T c4_b_init_Rot[9];
  int32_T c4_i14;
  real_T c4_b_L[9];
  uint32_T c4_debug_family_var_map[9];
  static const char *c4_sv0[9] = { "gd", "theta_total", "num_total", "nargin",
    "nargout", "EndPos", "init_Rot", "L", "theta" };

  real_T c4_gd[16];
  real_T c4_theta_total[24];
  real_T c4_num_total;
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 1.0;
  real_T c4_theta[6];
  int32_T c4_i15;
  int32_T c4_i16;
  int32_T c4_i17;
  int32_T c4_i18;
  int32_T c4_i19;
  int32_T c4_i20;
  int32_T c4_i21;
  int32_T c4_i22;
  static real_T c4_dv3[4] = { 0.0, 0.0, 0.0, 1.0 };

  int32_T c4_i23;
  real_T c4_b_gd[16];
  int32_T c4_i24;
  real_T c4_c_L[9];
  real_T c4_b_num_total;
  real_T c4_b_theta_total[24];
  int32_T c4_i25;
  int32_T c4_i26;
  int32_T c4_i27;
  real_T (*c4_b_theta)[6];
  real_T (*c4_b_EndPos)[3];
  c4_b_theta = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_EndPos = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3);
  for (c4_i5 = 0; c4_i5 < 3; c4_i5 = c4_i5 + 1) {
    _SFD_DATA_RANGE_CHECK((*c4_b_EndPos)[c4_i5], 0U);
  }

  for (c4_i6 = 0; c4_i6 < 9; c4_i6 = c4_i6 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c4_init_Rot[c4_i6], 1U);
  }

  for (c4_i7 = 0; c4_i7 < 6; c4_i7 = c4_i7 + 1) {
    _SFD_DATA_RANGE_CHECK((*c4_b_theta)[c4_i7], 2U);
  }

  for (c4_i8 = 0; c4_i8 < 9; c4_i8 = c4_i8 + 1) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c4_L[c4_i8], 3U);
  }

  c4_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3);
  for (c4_i9 = 0; c4_i9 < 3; c4_i9 = c4_i9 + 1) {
    c4_hoistedGlobal[c4_i9] = (*c4_b_EndPos)[c4_i9];
  }

  for (c4_i10 = 0; c4_i10 < 9; c4_i10 = c4_i10 + 1) {
    c4_b_hoistedGlobal[c4_i10] = chartInstance->c4_init_Rot[c4_i10];
  }

  for (c4_i11 = 0; c4_i11 < 9; c4_i11 = c4_i11 + 1) {
    c4_c_hoistedGlobal[c4_i11] = chartInstance->c4_L[c4_i11];
  }

  for (c4_i12 = 0; c4_i12 < 3; c4_i12 = c4_i12 + 1) {
    c4_EndPos[c4_i12] = c4_hoistedGlobal[c4_i12];
  }

  for (c4_i13 = 0; c4_i13 < 9; c4_i13 = c4_i13 + 1) {
    c4_b_init_Rot[c4_i13] = c4_b_hoistedGlobal[c4_i13];
  }

  for (c4_i14 = 0; c4_i14 < 9; c4_i14 = c4_i14 + 1) {
    c4_b_L[c4_i14] = c4_c_hoistedGlobal[c4_i14];
  }

  sf_debug_symbol_scope_push_eml(0U, 9U, 9U, c4_sv0, c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_gd, c4_g_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c4_theta_total, c4_f_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c4_num_total, c4_e_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_EndPos, c4_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c4_b_init_Rot, c4_c_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c4_b_L, c4_b_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c4_theta, c4_sf_marshall, 8U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0, 3);
  for (c4_i15 = 0; c4_i15 < 6; c4_i15 = c4_i15 + 1) {
    c4_theta[c4_i15] = 0.0;
  }

  _SFD_EML_CALL(0, 4);
  c4_i16 = 0;
  c4_i17 = 0;
  for (c4_i18 = 0; c4_i18 < 3; c4_i18 = c4_i18 + 1) {
    for (c4_i19 = 0; c4_i19 < 3; c4_i19 = c4_i19 + 1) {
      c4_gd[c4_i19 + c4_i16] = c4_b_init_Rot[c4_i19 + c4_i17];
    }

    c4_i16 = c4_i16 + 4;
    c4_i17 = c4_i17 + 3;
  }

  for (c4_i20 = 0; c4_i20 < 3; c4_i20 = c4_i20 + 1) {
    c4_gd[c4_i20 + 12] = c4_EndPos[c4_i20];
  }

  c4_i21 = 0;
  for (c4_i22 = 0; c4_i22 < 4; c4_i22 = c4_i22 + 1) {
    c4_gd[c4_i21 + 3] = c4_dv3[c4_i22];
    c4_i21 = c4_i21 + 4;
  }

  _SFD_EML_CALL(0, 5);
  for (c4_i23 = 0; c4_i23 < 16; c4_i23 = c4_i23 + 1) {
    c4_b_gd[c4_i23] = c4_gd[c4_i23];
  }

  for (c4_i24 = 0; c4_i24 < 9; c4_i24 = c4_i24 + 1) {
    c4_c_L[c4_i24] = c4_b_L[c4_i24];
  }

  c4_inv_kin(chartInstance, c4_b_gd, c4_c_L, c4_b_theta_total, &c4_b_num_total);
  for (c4_i25 = 0; c4_i25 < 24; c4_i25 = c4_i25 + 1) {
    c4_theta_total[c4_i25] = c4_b_theta_total[c4_i25];
  }

  c4_num_total = c4_b_num_total;
  _SFD_EML_CALL(0, 6);
  for (c4_i26 = 0; c4_i26 < 6; c4_i26 = c4_i26 + 1) {
    c4_theta[c4_i26] = c4_theta_total[c4_i26 + 6];
  }

  _SFD_EML_CALL(0, -6);
  sf_debug_symbol_scope_pop();
  for (c4_i27 = 0; c4_i27 < 6; c4_i27 = c4_i27 + 1) {
    (*c4_b_theta)[c4_i27] = c4_theta[c4_i27];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3);
  _sfEvent_ = c4_previousEvent;
  sf_debug_check_for_state_inconsistency(_EurlerDynJointVerifyMachineNumber_,
    chartInstance->chartNumber, chartInstance->
    instanceNumber);
}

static void compInitSubchartSimstructsFcn_c4_EurlerDynJointVerify
  (SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c4_chartNumber, 0U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/inv_kin.m"));
  _SFD_SCRIPT_TRANSLATION(c4_chartNumber, 1U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/expWre.m"));
  _SFD_SCRIPT_TRANSLATION(c4_chartNumber, 2U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/expRot.m"));
  _SFD_SCRIPT_TRANSLATION(c4_chartNumber, 3U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/skew.m"));
  _SFD_SCRIPT_TRANSLATION(c4_chartNumber, 4U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/subPro3.m"));
  _SFD_SCRIPT_TRANSLATION(c4_chartNumber, 5U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/subPro1.m"));
  _SFD_SCRIPT_TRANSLATION(c4_chartNumber, 6U, sf_debug_get_script_id(
    "D:/Learn/Project_Matlab/Fanuc/subPro2.m"));
}

static void c4_inv_kin(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_gd[16], real_T c4_b_L[9], real_T c4_theta[
  24], real_T *c4_Num)
{
  uint32_T c4_debug_family_var_map[71];
  static const char *c4_sv1[71] = { "Min1", "Max1", "Min2", "Max2", "Min3",
    "Max3", "Min4", "Max4", "Min5", "Max5", "Min6", "Max6",
    "L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9", "s_origin", "w_x",
    "w_y", "w_z", "w1", "q1"
    , "kx1", "w2", "q2", "kx2", "w3", "q3", "kx3", "pw", "w4", "q4", "kx4", "w5",
    "q5", "kx5", "w6",
    "q6", "kx6", "q7", "gst0", "g1", "p1", "theta_1", "p2", "d", "theta_3",
    "Num_3", "c3", "p3",
    "theta_2", "g2", "p4", "theta_4", "theta_5", "Num_45", "c45", "g3", "p5",
    "theta_6", "nargin",
    "nargout", "gd", "L", "theta", "Num" };

  real_T c4_Min1;
  real_T c4_Max1;
  real_T c4_Min2;
  real_T c4_Max2;
  real_T c4_Min3;
  real_T c4_Max3;
  real_T c4_Min4;
  real_T c4_Max4;
  real_T c4_Min5;
  real_T c4_Max5;
  real_T c4_Min6;
  real_T c4_Max6;
  real_T c4_L1;
  real_T c4_L2;
  real_T c4_L3;
  real_T c4_L4;
  real_T c4_L5;
  real_T c4_L6;
  real_T c4_L7;
  real_T c4_L8;
  real_T c4_L9;
  real_T c4_s_origin[3];
  real_T c4_w_x[3];
  real_T c4_w_y[3];
  real_T c4_w_z[3];
  real_T c4_w1[3];
  real_T c4_q1[3];
  real_T c4_kx1[6];
  real_T c4_w2[3];
  real_T c4_q2[3];
  real_T c4_kx2[6];
  real_T c4_w3[3];
  real_T c4_q3[3];
  real_T c4_kx3[6];
  real_T c4_pw[3];
  real_T c4_w4[3];
  real_T c4_q4[3];
  real_T c4_kx4[6];
  real_T c4_w5[3];
  real_T c4_q5[3];
  real_T c4_kx5[6];
  real_T c4_w6[3];
  real_T c4_q6[3];
  real_T c4_kx6[6];
  real_T c4_q7[3];
  real_T c4_gst0[16];
  real_T c4_g1[16];
  real_T c4_p1[4];
  real_T c4_theta_1;
  real_T c4_p2[4];
  real_T c4_d[4];
  real_T c4_theta_3[2];
  real_T c4_Num_3;
  real_T c4_c3;
  real_T c4_p3[4];
  real_T c4_theta_2;
  real_T c4_g2[16];
  real_T c4_p4[4];
  real_T c4_theta_4[2];
  real_T c4_theta_5[2];
  real_T c4_Num_45;
  real_T c4_c45;
  real_T c4_g3[16];
  real_T c4_p5[4];
  real_T c4_theta_6;
  real_T c4_b_q1[4];
  real_T c4_b_q2[4];
  real_T c4_b_q3[4];
  real_T c4_b_q4[4];
  real_T c4_b_q5[4];
  real_T c4_b_q6[4];
  real_T c4_b_q7[4];
  real_T c4_b_pw[4];
  real_T c4_nargin = 2.0;
  real_T c4_nargout = 2.0;
  int32_T c4_i28;
  int32_T c4_i29;
  int32_T c4_i30;
  static real_T c4_dv4[3] = { 1.0, 0.0, 0.0 };

  int32_T c4_i31;
  static real_T c4_dv5[3] = { 0.0, 1.0, 0.0 };

  int32_T c4_i32;
  static real_T c4_dv6[3] = { 0.0, 0.0, 1.0 };

  int32_T c4_i33;
  int32_T c4_i34;
  int32_T c4_i35;
  static real_T c4_dv7[6] = { -0.0, -0.0, -0.0, 0.0, 0.0, 1.0 };

  int32_T c4_i36;
  int32_T c4_i37;
  real_T c4_dv8[3];
  int32_T c4_i38;
  real_T c4_c_q2[3];
  real_T c4_dv9[3];
  int32_T c4_i39;
  int32_T c4_i40;
  int32_T c4_i41;
  int32_T c4_i42;
  real_T c4_dv10[3];
  int32_T c4_i43;
  real_T c4_c_q3[3];
  real_T c4_dv11[3];
  int32_T c4_i44;
  int32_T c4_i45;
  int32_T c4_i46;
  int32_T c4_i47;
  int32_T c4_i48;
  real_T c4_dv12[3];
  int32_T c4_i49;
  real_T c4_c_q4[3];
  real_T c4_dv13[3];
  int32_T c4_i50;
  int32_T c4_i51;
  int32_T c4_i52;
  int32_T c4_i53;
  int32_T c4_i54;
  real_T c4_dv14[3];
  int32_T c4_i55;
  real_T c4_c_q5[3];
  real_T c4_dv15[3];
  int32_T c4_i56;
  int32_T c4_i57;
  int32_T c4_i58;
  int32_T c4_i59;
  int32_T c4_i60;
  real_T c4_dv16[3];
  int32_T c4_i61;
  real_T c4_c_q6[3];
  real_T c4_dv17[3];
  int32_T c4_i62;
  int32_T c4_i63;
  int32_T c4_i64;
  int32_T c4_i65;
  int32_T c4_i66;
  int32_T c4_i67;
  int32_T c4_i68;
  int32_T c4_i69;
  int32_T c4_i70;
  int32_T c4_i71;
  int32_T c4_i72;
  int32_T c4_i73;
  static real_T c4_dv18[4] = { 0.0, 0.0, 0.0, 1.0 };

  int32_T c4_i74;
  boolean_T c4_bv0[2];
  int32_T c4_i75;
  real_T c4_b_gd[16];
  int32_T c4_i76;
  real_T c4_b_gst0[16];
  real_T c4_dv19[16];
  int32_T c4_i77;
  int32_T c4_i78;
  real_T c4_a[16];
  int32_T c4_i79;
  real_T c4_b[4];
  int32_T c4_i80;
  real_T c4_A[16];
  int32_T c4_i81;
  real_T c4_B[4];
  int32_T c4_i82;
  int32_T c4_i83;
  real_T c4_b_A[16];
  int32_T c4_i84;
  real_T c4_b_B[4];
  int32_T c4_i85;
  real_T c4_c_A[16];
  int32_T c4_i86;
  real_T c4_c_B[4];
  int32_T c4_i87;
  int32_T c4_i88;
  int32_T c4_i89;
  int32_T c4_i90;
  static real_T c4_dv20[6] = { 0.0, 0.0, 0.0, -0.0, -0.0, -1.0 };

  real_T c4_dv21[6];
  real_T c4_b_a[16];
  int32_T c4_i91;
  real_T c4_b_b[4];
  int32_T c4_i92;
  real_T c4_d_A[16];
  int32_T c4_i93;
  real_T c4_d_B[4];
  int32_T c4_i94;
  int32_T c4_i95;
  real_T c4_e_A[16];
  int32_T c4_i96;
  real_T c4_e_B[4];
  int32_T c4_i97;
  real_T c4_f_A[16];
  int32_T c4_i98;
  real_T c4_f_B[4];
  int32_T c4_i99;
  int32_T c4_i100;
  int32_T c4_i101;
  int32_T c4_i102;
  int32_T c4_i103;
  real_T c4_b_kx3[6];
  int32_T c4_i104;
  real_T c4_c_pw[4];
  int32_T c4_i105;
  real_T c4_d_q2[4];
  int32_T c4_i106;
  real_T c4_b_d[4];
  real_T c4_b_Num_3;
  real_T c4_b_theta_3[2];
  int32_T c4_i107;
  int32_T c4_i108;
  real_T c4_c_theta_3[2];
  boolean_T c4_bv1[2];
  int32_T c4_i109;
  boolean_T c4_bv2[2];
  real_T c4_b_c3;
  int32_T c4_i110;
  real_T c4_c_kx3[6];
  real_T c4_c_a[16];
  int32_T c4_i111;
  real_T c4_c_b[4];
  int32_T c4_i112;
  real_T c4_g_A[16];
  int32_T c4_i113;
  real_T c4_g_B[4];
  int32_T c4_i114;
  int32_T c4_i115;
  real_T c4_h_A[16];
  int32_T c4_i116;
  real_T c4_h_B[4];
  int32_T c4_i117;
  real_T c4_i_A[16];
  int32_T c4_i118;
  real_T c4_i_B[4];
  int32_T c4_i119;
  int32_T c4_i120;
  int32_T c4_i121;
  int32_T c4_i122;
  real_T c4_b_kx2[6];
  int32_T c4_i123;
  real_T c4_b_p3[4];
  int32_T c4_i124;
  real_T c4_b_p2[4];
  int32_T c4_i125;
  real_T c4_d_kx3[6];
  real_T c4_d_a[16];
  int32_T c4_i126;
  real_T c4_c_kx2[6];
  real_T c4_d_b[16];
  int32_T c4_i127;
  real_T c4_j_A[16];
  int32_T c4_i128;
  real_T c4_j_B[16];
  int32_T c4_i129;
  real_T c4_k_A[16];
  int32_T c4_i130;
  real_T c4_k_B[16];
  int32_T c4_i131;
  real_T c4_l_A[16];
  int32_T c4_i132;
  real_T c4_l_B[16];
  int32_T c4_i133;
  int32_T c4_i134;
  int32_T c4_i135;
  real_T c4_y[16];
  int32_T c4_i136;
  int32_T c4_i137;
  int32_T c4_i138;
  real_T c4_e_a[16];
  int32_T c4_i139;
  real_T c4_dv22[6];
  real_T c4_e_b[16];
  int32_T c4_i140;
  real_T c4_m_A[16];
  int32_T c4_i141;
  real_T c4_m_B[16];
  int32_T c4_i142;
  real_T c4_n_A[16];
  int32_T c4_i143;
  real_T c4_n_B[16];
  int32_T c4_i144;
  real_T c4_o_A[16];
  int32_T c4_i145;
  real_T c4_o_B[16];
  int32_T c4_i146;
  int32_T c4_i147;
  int32_T c4_i148;
  real_T c4_b_y[16];
  int32_T c4_i149;
  int32_T c4_i150;
  int32_T c4_i151;
  real_T c4_f_a[16];
  int32_T c4_i152;
  real_T c4_f_b[16];
  int32_T c4_i153;
  real_T c4_p_A[16];
  int32_T c4_i154;
  real_T c4_p_B[16];
  int32_T c4_i155;
  int32_T c4_i156;
  real_T c4_q_A[16];
  int32_T c4_i157;
  real_T c4_q_B[16];
  int32_T c4_i158;
  real_T c4_r_A[16];
  int32_T c4_i159;
  real_T c4_r_B[16];
  int32_T c4_i160;
  int32_T c4_i161;
  int32_T c4_i162;
  int32_T c4_i163;
  int32_T c4_i164;
  int32_T c4_i165;
  real_T c4_g_a[16];
  int32_T c4_i166;
  real_T c4_g_b[4];
  int32_T c4_i167;
  real_T c4_s_A[16];
  int32_T c4_i168;
  real_T c4_s_B[4];
  int32_T c4_i169;
  int32_T c4_i170;
  real_T c4_t_A[16];
  int32_T c4_i171;
  real_T c4_t_B[4];
  int32_T c4_i172;
  real_T c4_u_A[16];
  int32_T c4_i173;
  real_T c4_u_B[4];
  int32_T c4_i174;
  int32_T c4_i175;
  int32_T c4_i176;
  int32_T c4_i177;
  real_T c4_b_kx4[6];
  int32_T c4_i178;
  real_T c4_b_kx5[6];
  int32_T c4_i179;
  real_T c4_c_q7[4];
  int32_T c4_i180;
  real_T c4_b_p4[4];
  real_T c4_b_Num_45;
  real_T c4_b_theta_5[2];
  real_T c4_b_theta_4[2];
  int32_T c4_i181;
  int32_T c4_i182;
  int32_T c4_i183;
  real_T c4_c_theta_5[2];
  boolean_T c4_bv3[2];
  int32_T c4_i184;
  boolean_T c4_bv4[2];
  real_T c4_b_c45;
  int32_T c4_i185;
  real_T c4_c_kx5[6];
  real_T c4_h_a[16];
  int32_T c4_i186;
  real_T c4_c_kx4[6];
  real_T c4_h_b[16];
  int32_T c4_i187;
  real_T c4_v_A[16];
  int32_T c4_i188;
  real_T c4_v_B[16];
  int32_T c4_i189;
  real_T c4_w_A[16];
  int32_T c4_i190;
  real_T c4_w_B[16];
  int32_T c4_i191;
  real_T c4_x_A[16];
  int32_T c4_i192;
  real_T c4_x_B[16];
  int32_T c4_i193;
  int32_T c4_i194;
  int32_T c4_i195;
  real_T c4_c_y[16];
  int32_T c4_i196;
  int32_T c4_i197;
  int32_T c4_i198;
  real_T c4_i_a[16];
  int32_T c4_i199;
  real_T c4_i_b[16];
  int32_T c4_i200;
  real_T c4_y_A[16];
  int32_T c4_i201;
  real_T c4_y_B[16];
  int32_T c4_i202;
  int32_T c4_i203;
  real_T c4_ab_A[16];
  int32_T c4_i204;
  real_T c4_ab_B[16];
  int32_T c4_i205;
  real_T c4_bb_A[16];
  int32_T c4_i206;
  real_T c4_bb_B[16];
  int32_T c4_i207;
  int32_T c4_i208;
  int32_T c4_i209;
  int32_T c4_i210;
  int32_T c4_i211;
  int32_T c4_i212;
  real_T c4_j_a[16];
  int32_T c4_i213;
  real_T c4_j_b[4];
  int32_T c4_i214;
  real_T c4_cb_A[16];
  int32_T c4_i215;
  real_T c4_cb_B[4];
  int32_T c4_i216;
  int32_T c4_i217;
  real_T c4_db_A[16];
  int32_T c4_i218;
  real_T c4_db_B[4];
  int32_T c4_i219;
  real_T c4_eb_A[16];
  int32_T c4_i220;
  real_T c4_eb_B[4];
  int32_T c4_i221;
  int32_T c4_i222;
  int32_T c4_i223;
  int32_T c4_i224;
  real_T c4_b_kx6[6];
  int32_T c4_i225;
  real_T c4_d_q3[4];
  int32_T c4_i226;
  real_T c4_b_p5[4];
  int32_T c4_b_Num;
  real_T c4_b_theta_1[6];
  int32_T c4_i227;
  sf_debug_symbol_scope_push_eml(0U, 71U, 79U, c4_sv1, c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c4_Min1, c4_e_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c4_Max1, c4_e_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c4_Min2, c4_e_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c4_Max2, c4_e_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c4_Min3, c4_e_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c4_Max3, c4_e_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c4_Min4, c4_e_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c4_Max4, c4_e_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c4_Min5, c4_e_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c4_Max5, c4_e_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&c4_Min6, c4_e_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&c4_Max6, c4_e_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c4_L1, c4_e_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(&c4_L2, c4_e_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(&c4_L3, c4_e_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(&c4_L4, c4_e_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(&c4_L5, c4_e_sf_marshall, 16U);
  sf_debug_symbol_scope_add_eml(&c4_L6, c4_e_sf_marshall, 17U);
  sf_debug_symbol_scope_add_eml(&c4_L7, c4_e_sf_marshall, 18U);
  sf_debug_symbol_scope_add_eml(&c4_L8, c4_e_sf_marshall, 19U);
  sf_debug_symbol_scope_add_eml(&c4_L9, c4_e_sf_marshall, 20U);
  sf_debug_symbol_scope_add_eml(c4_s_origin, c4_d_sf_marshall, 21U);
  sf_debug_symbol_scope_add_eml(c4_w_x, c4_d_sf_marshall, 22U);
  sf_debug_symbol_scope_add_eml(c4_w_y, c4_d_sf_marshall, 23U);
  sf_debug_symbol_scope_add_eml(c4_w_z, c4_d_sf_marshall, 24U);
  sf_debug_symbol_scope_add_eml(c4_w1, c4_d_sf_marshall, 25U);
  sf_debug_symbol_scope_add_eml(c4_q1, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_kx1, c4_sf_marshall, 27U);
  sf_debug_symbol_scope_add_eml(c4_w2, c4_d_sf_marshall, 28U);
  sf_debug_symbol_scope_add_eml(c4_q2, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_kx2, c4_sf_marshall, 30U);
  sf_debug_symbol_scope_add_eml(c4_w3, c4_d_sf_marshall, 31U);
  sf_debug_symbol_scope_add_eml(c4_q3, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_kx3, c4_sf_marshall, 33U);
  sf_debug_symbol_scope_add_eml(c4_pw, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_w4, c4_d_sf_marshall, 35U);
  sf_debug_symbol_scope_add_eml(c4_q4, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_kx4, c4_sf_marshall, 37U);
  sf_debug_symbol_scope_add_eml(c4_w5, c4_d_sf_marshall, 38U);
  sf_debug_symbol_scope_add_eml(c4_q5, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_kx5, c4_sf_marshall, 40U);
  sf_debug_symbol_scope_add_eml(c4_w6, c4_d_sf_marshall, 41U);
  sf_debug_symbol_scope_add_eml(c4_q6, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_kx6, c4_sf_marshall, 43U);
  sf_debug_symbol_scope_add_eml(c4_q7, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_gst0, c4_g_sf_marshall, 45U);
  sf_debug_symbol_scope_add_eml(c4_g1, c4_g_sf_marshall, 46U);
  sf_debug_symbol_scope_add_eml(c4_p1, c4_j_sf_marshall, 47U);
  sf_debug_symbol_scope_add_eml(&c4_theta_1, c4_e_sf_marshall, 48U);
  sf_debug_symbol_scope_add_eml(c4_p2, c4_j_sf_marshall, 49U);
  sf_debug_symbol_scope_add_eml(c4_d, c4_j_sf_marshall, 50U);
  sf_debug_symbol_scope_add_eml(c4_theta_3, c4_i_sf_marshall, 51U);
  sf_debug_symbol_scope_add_eml(&c4_Num_3, c4_e_sf_marshall, 52U);
  sf_debug_symbol_scope_add_eml(&c4_c3, c4_e_sf_marshall, 53U);
  sf_debug_symbol_scope_add_eml(c4_p3, c4_j_sf_marshall, 54U);
  sf_debug_symbol_scope_add_eml(&c4_theta_2, c4_e_sf_marshall, 55U);
  sf_debug_symbol_scope_add_eml(c4_g2, c4_g_sf_marshall, 56U);
  sf_debug_symbol_scope_add_eml(c4_p4, c4_j_sf_marshall, 57U);
  sf_debug_symbol_scope_add_eml(c4_theta_4, c4_i_sf_marshall, 58U);
  sf_debug_symbol_scope_add_eml(c4_theta_5, c4_i_sf_marshall, 59U);
  sf_debug_symbol_scope_add_eml(&c4_Num_45, c4_e_sf_marshall, 60U);
  sf_debug_symbol_scope_add_eml(&c4_c45, c4_e_sf_marshall, 61U);
  sf_debug_symbol_scope_add_eml(c4_g3, c4_g_sf_marshall, 62U);
  sf_debug_symbol_scope_add_eml(c4_p5, c4_j_sf_marshall, 63U);
  sf_debug_symbol_scope_add_eml(&c4_theta_6, c4_e_sf_marshall, 64U);
  sf_debug_symbol_scope_add_eml(c4_b_q1, c4_j_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_q2, c4_j_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_q3, c4_j_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_q4, c4_j_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_q5, c4_j_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_q6, c4_j_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_q7, c4_j_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_pw, c4_j_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 65U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 66U);
  sf_debug_symbol_scope_add_eml(c4_gd, c4_g_sf_marshall, 67U);
  sf_debug_symbol_scope_add_eml(c4_b_L, c4_b_sf_marshall, 68U);
  sf_debug_symbol_scope_add_eml(c4_theta, c4_f_sf_marshall, 69U);
  sf_debug_symbol_scope_add_eml(c4_Num, c4_e_sf_marshall, 70U);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0, 2);
  for (c4_i28 = 0; c4_i28 < 24; c4_i28 = c4_i28 + 1) {
    c4_theta[c4_i28] = 0.0;
  }

  /*  at most 4 pairs of solution */
  _SFD_SCRIPT_CALL(0, 3);
  *c4_Num = 0.0;
  _SFD_SCRIPT_CALL(0, 5);
  c4_Min1 = -165.0;
  _SFD_SCRIPT_CALL(0, 5);
  c4_Max1 = 165.0;
  _SFD_SCRIPT_CALL(0, 6);
  c4_Min2 = -150.0;
  _SFD_SCRIPT_CALL(0, 6);
  c4_Max2 = 60.0;
  _SFD_SCRIPT_CALL(0, 7);
  c4_Min3 = -210.0;
  _SFD_SCRIPT_CALL(0, 7);
  c4_Max3 = 90.0;
  _SFD_SCRIPT_CALL(0, 8);
  c4_Min4 = -180.0;
  _SFD_SCRIPT_CALL(0, 8);
  c4_Max4 = 180.0;
  _SFD_SCRIPT_CALL(0, 9);
  c4_Min5 = -140.0;
  _SFD_SCRIPT_CALL(0, 9);
  c4_Max5 = 140.0;
  _SFD_SCRIPT_CALL(0, 10);
  c4_Min6 = -180.0;
  _SFD_SCRIPT_CALL(0, 10);
  c4_Max6 = 180.0;
  _SFD_SCRIPT_CALL(0, 12);
  c4_L1 = c4_b_L[0];
  _SFD_SCRIPT_CALL(0, 13);
  c4_L2 = c4_b_L[1];
  _SFD_SCRIPT_CALL(0, 14);
  c4_L3 = c4_b_L[2];
  _SFD_SCRIPT_CALL(0, 15);
  c4_L4 = c4_b_L[3];
  _SFD_SCRIPT_CALL(0, 16);
  c4_L5 = c4_b_L[4];
  _SFD_SCRIPT_CALL(0, 17);
  c4_L6 = c4_b_L[5];
  _SFD_SCRIPT_CALL(0, 18);
  c4_L7 = c4_b_L[6];
  _SFD_SCRIPT_CALL(0, 19);
  c4_L8 = c4_b_L[7];
  _SFD_SCRIPT_CALL(0, 20);
  c4_L9 = c4_b_L[8];
  _SFD_SCRIPT_CALL(0, 22);
  for (c4_i29 = 0; c4_i29 < 3; c4_i29 = c4_i29 + 1) {
    c4_s_origin[c4_i29] = 0.0;
  }

  _SFD_SCRIPT_CALL(0, 23);
  for (c4_i30 = 0; c4_i30 < 3; c4_i30 = c4_i30 + 1) {
    c4_w_x[c4_i30] = c4_dv4[c4_i30];
  }

  _SFD_SCRIPT_CALL(0, 24);
  for (c4_i31 = 0; c4_i31 < 3; c4_i31 = c4_i31 + 1) {
    c4_w_y[c4_i31] = c4_dv5[c4_i31];
  }

  _SFD_SCRIPT_CALL(0, 25);
  for (c4_i32 = 0; c4_i32 < 3; c4_i32 = c4_i32 + 1) {
    c4_w_z[c4_i32] = c4_dv6[c4_i32];
  }

  _SFD_SCRIPT_CALL(0, 27);
  for (c4_i33 = 0; c4_i33 < 3; c4_i33 = c4_i33 + 1) {
    c4_w1[c4_i33] = c4_dv6[c4_i33];
  }

  _SFD_SCRIPT_CALL(0, 28);
  for (c4_i34 = 0; c4_i34 < 3; c4_i34 = c4_i34 + 1) {
    c4_q1[c4_i34] = 0.0;
  }

  sf_debug_symbol_switch(26U, 26U);
  _SFD_SCRIPT_CALL(0, 29);
  for (c4_i35 = 0; c4_i35 < 6; c4_i35 = c4_i35 + 1) {
    c4_kx1[c4_i35] = c4_dv7[c4_i35];
  }

  _SFD_SCRIPT_CALL(0, 31);
  for (c4_i36 = 0; c4_i36 < 3; c4_i36 = c4_i36 + 1) {
    c4_w2[c4_i36] = c4_dv5[c4_i36];
  }

  _SFD_SCRIPT_CALL(0, 32);
  c4_q2[0] = c4_L2;
  c4_q2[1] = 0.0;
  c4_q2[2] = c4_L1;
  sf_debug_symbol_switch(29U, 29U);
  _SFD_SCRIPT_CALL(0, 33);
  for (c4_i37 = 0; c4_i37 < 3; c4_i37 = c4_i37 + 1) {
    c4_dv8[c4_i37] = c4_dv5[c4_i37];
  }

  for (c4_i38 = 0; c4_i38 < 3; c4_i38 = c4_i38 + 1) {
    c4_c_q2[c4_i38] = c4_q2[c4_i38];
  }

  c4_cross(chartInstance, c4_dv8, c4_c_q2, c4_dv9);
  for (c4_i39 = 0; c4_i39 < 3; c4_i39 = c4_i39 + 1) {
    c4_kx2[c4_i39] = -c4_dv9[c4_i39];
  }

  for (c4_i40 = 0; c4_i40 < 3; c4_i40 = c4_i40 + 1) {
    c4_kx2[c4_i40 + 3] = c4_w2[c4_i40];
  }

  _SFD_SCRIPT_CALL(0, 35);
  for (c4_i41 = 0; c4_i41 < 3; c4_i41 = c4_i41 + 1) {
    c4_w3[c4_i41] = c4_dv5[c4_i41];
  }

  _SFD_SCRIPT_CALL(0, 36);
  c4_q3[0] = c4_L2;
  c4_q3[1] = 0.0;
  c4_q3[2] = c4_L1 + c4_L3;
  sf_debug_symbol_switch(32U, 32U);
  _SFD_SCRIPT_CALL(0, 37);
  for (c4_i42 = 0; c4_i42 < 3; c4_i42 = c4_i42 + 1) {
    c4_dv10[c4_i42] = c4_dv5[c4_i42];
  }

  for (c4_i43 = 0; c4_i43 < 3; c4_i43 = c4_i43 + 1) {
    c4_c_q3[c4_i43] = c4_q3[c4_i43];
  }

  c4_cross(chartInstance, c4_dv10, c4_c_q3, c4_dv11);
  for (c4_i44 = 0; c4_i44 < 3; c4_i44 = c4_i44 + 1) {
    c4_kx3[c4_i44] = -c4_dv11[c4_i44];
  }

  for (c4_i45 = 0; c4_i45 < 3; c4_i45 = c4_i45 + 1) {
    c4_kx3[c4_i45 + 3] = c4_w3[c4_i45];
  }

  _SFD_SCRIPT_CALL(0, 39);
  c4_pw[0] = c4_L2 + c4_L5;
  c4_pw[1] = 0.0;
  c4_pw[2] = (c4_L1 + c4_L3) + c4_L4;
  sf_debug_symbol_switch(34U, 34U);
  _SFD_SCRIPT_CALL(0, 41);
  for (c4_i46 = 0; c4_i46 < 3; c4_i46 = c4_i46 + 1) {
    c4_w4[c4_i46] = c4_dv4[c4_i46];
  }

  _SFD_SCRIPT_CALL(0, 42);
  for (c4_i47 = 0; c4_i47 < 3; c4_i47 = c4_i47 + 1) {
    c4_q4[c4_i47] = c4_pw[c4_i47];
  }

  sf_debug_symbol_switch(36U, 36U);
  _SFD_SCRIPT_CALL(0, 43);
  for (c4_i48 = 0; c4_i48 < 3; c4_i48 = c4_i48 + 1) {
    c4_dv12[c4_i48] = c4_dv4[c4_i48];
  }

  for (c4_i49 = 0; c4_i49 < 3; c4_i49 = c4_i49 + 1) {
    c4_c_q4[c4_i49] = c4_q4[c4_i49];
  }

  c4_cross(chartInstance, c4_dv12, c4_c_q4, c4_dv13);
  for (c4_i50 = 0; c4_i50 < 3; c4_i50 = c4_i50 + 1) {
    c4_kx4[c4_i50] = -c4_dv13[c4_i50];
  }

  for (c4_i51 = 0; c4_i51 < 3; c4_i51 = c4_i51 + 1) {
    c4_kx4[c4_i51 + 3] = c4_w4[c4_i51];
  }

  _SFD_SCRIPT_CALL(0, 45);
  for (c4_i52 = 0; c4_i52 < 3; c4_i52 = c4_i52 + 1) {
    c4_w5[c4_i52] = c4_dv5[c4_i52];
  }

  _SFD_SCRIPT_CALL(0, 46);
  for (c4_i53 = 0; c4_i53 < 3; c4_i53 = c4_i53 + 1) {
    c4_q5[c4_i53] = c4_pw[c4_i53];
  }

  sf_debug_symbol_switch(39U, 39U);
  _SFD_SCRIPT_CALL(0, 47);
  for (c4_i54 = 0; c4_i54 < 3; c4_i54 = c4_i54 + 1) {
    c4_dv14[c4_i54] = c4_dv5[c4_i54];
  }

  for (c4_i55 = 0; c4_i55 < 3; c4_i55 = c4_i55 + 1) {
    c4_c_q5[c4_i55] = c4_q5[c4_i55];
  }

  c4_cross(chartInstance, c4_dv14, c4_c_q5, c4_dv15);
  for (c4_i56 = 0; c4_i56 < 3; c4_i56 = c4_i56 + 1) {
    c4_kx5[c4_i56] = -c4_dv15[c4_i56];
  }

  for (c4_i57 = 0; c4_i57 < 3; c4_i57 = c4_i57 + 1) {
    c4_kx5[c4_i57 + 3] = c4_w5[c4_i57];
  }

  _SFD_SCRIPT_CALL(0, 49);
  for (c4_i58 = 0; c4_i58 < 3; c4_i58 = c4_i58 + 1) {
    c4_w6[c4_i58] = c4_dv4[c4_i58];
  }

  _SFD_SCRIPT_CALL(0, 50);
  for (c4_i59 = 0; c4_i59 < 3; c4_i59 = c4_i59 + 1) {
    c4_q6[c4_i59] = c4_pw[c4_i59];
  }

  sf_debug_symbol_switch(42U, 42U);
  _SFD_SCRIPT_CALL(0, 51);
  for (c4_i60 = 0; c4_i60 < 3; c4_i60 = c4_i60 + 1) {
    c4_dv16[c4_i60] = c4_dv4[c4_i60];
  }

  for (c4_i61 = 0; c4_i61 < 3; c4_i61 = c4_i61 + 1) {
    c4_c_q6[c4_i61] = c4_q6[c4_i61];
  }

  c4_cross(chartInstance, c4_dv16, c4_c_q6, c4_dv17);
  for (c4_i62 = 0; c4_i62 < 3; c4_i62 = c4_i62 + 1) {
    c4_kx6[c4_i62] = -c4_dv17[c4_i62];
  }

  for (c4_i63 = 0; c4_i63 < 3; c4_i63 = c4_i63 + 1) {
    c4_kx6[c4_i63 + 3] = c4_w6[c4_i63];
  }

  _SFD_SCRIPT_CALL(0, 53);
  c4_q7[0] = (c4_L2 + c4_L5) + c4_L6;
  c4_q7[1] = 0.0;
  c4_q7[2] = (c4_L1 + c4_L3) + c4_L4;
  sf_debug_symbol_switch(44U, 44U);
  _SFD_SCRIPT_CALL(0, 55);
  for (c4_i64 = 0; c4_i64 < 3; c4_i64 = c4_i64 + 1) {
    c4_b_q1[c4_i64] = c4_q1[c4_i64];
  }

  c4_b_q1[3] = 1.0;
  sf_debug_symbol_switch(26U, 65U);
  _SFD_SCRIPT_CALL(0, 56);
  for (c4_i65 = 0; c4_i65 < 3; c4_i65 = c4_i65 + 1) {
    c4_b_q2[c4_i65] = c4_q2[c4_i65];
  }

  c4_b_q2[3] = 1.0;
  sf_debug_symbol_switch(29U, 66U);
  _SFD_SCRIPT_CALL(0, 57);
  for (c4_i66 = 0; c4_i66 < 3; c4_i66 = c4_i66 + 1) {
    c4_b_q3[c4_i66] = c4_q3[c4_i66];
  }

  c4_b_q3[3] = 1.0;
  sf_debug_symbol_switch(32U, 67U);
  _SFD_SCRIPT_CALL(0, 58);
  for (c4_i67 = 0; c4_i67 < 3; c4_i67 = c4_i67 + 1) {
    c4_b_q4[c4_i67] = c4_q4[c4_i67];
  }

  c4_b_q4[3] = 1.0;
  sf_debug_symbol_switch(36U, 68U);
  _SFD_SCRIPT_CALL(0, 59);
  for (c4_i68 = 0; c4_i68 < 3; c4_i68 = c4_i68 + 1) {
    c4_b_q5[c4_i68] = c4_q5[c4_i68];
  }

  c4_b_q5[3] = 1.0;
  sf_debug_symbol_switch(39U, 69U);
  _SFD_SCRIPT_CALL(0, 60);
  for (c4_i69 = 0; c4_i69 < 3; c4_i69 = c4_i69 + 1) {
    c4_b_q6[c4_i69] = c4_q6[c4_i69];
  }

  c4_b_q6[3] = 1.0;
  sf_debug_symbol_switch(42U, 70U);
  _SFD_SCRIPT_CALL(0, 61);
  for (c4_i70 = 0; c4_i70 < 3; c4_i70 = c4_i70 + 1) {
    c4_b_q7[c4_i70] = c4_q7[c4_i70];
  }

  c4_b_q7[3] = 1.0;
  sf_debug_symbol_switch(44U, 71U);
  _SFD_SCRIPT_CALL(0, 62);
  for (c4_i71 = 0; c4_i71 < 3; c4_i71 = c4_i71 + 1) {
    c4_b_pw[c4_i71] = c4_pw[c4_i71];
  }

  c4_b_pw[3] = 1.0;
  sf_debug_symbol_switch(34U, 72U);
  _SFD_SCRIPT_CALL(0, 65);
  c4_gst0[0] = 1.0;
  c4_gst0[4] = 0.0;
  c4_gst0[8] = 0.0;
  c4_gst0[12] = ((c4_L2 + c4_L5) + c4_L6) + c4_L7;
  c4_gst0[1] = 0.0;
  c4_gst0[5] = 1.0;
  c4_gst0[9] = 0.0;
  c4_gst0[13] = c4_L8;
  c4_gst0[2] = 0.0;
  c4_gst0[6] = 0.0;
  c4_gst0[10] = 1.0;
  c4_gst0[14] = ((c4_L1 + c4_L3) + c4_L4) + c4_L9;
  c4_i72 = 0;
  for (c4_i73 = 0; c4_i73 < 4; c4_i73 = c4_i73 + 1) {
    c4_gst0[c4_i72 + 3] = c4_dv18[c4_i73];
    c4_i72 = c4_i72 + 4;
  }

  _SFD_SCRIPT_CALL(0, 67);
  for (c4_i74 = 0; c4_i74 < 2; c4_i74 = c4_i74 + 1) {
    c4_bv0[c4_i74] = TRUE;
  }

  CV_SCRIPT_IF(0, 0, c4_all(chartInstance, c4_bv0));
  _SFD_SCRIPT_CALL(0, 68);
  for (c4_i75 = 0; c4_i75 < 16; c4_i75 = c4_i75 + 1) {
    c4_b_gd[c4_i75] = c4_gd[c4_i75];
  }

  for (c4_i76 = 0; c4_i76 < 16; c4_i76 = c4_i76 + 1) {
    c4_b_gst0[c4_i76] = c4_gst0[c4_i76];
  }

  c4_mrdivide(chartInstance, c4_b_gd, c4_b_gst0, c4_dv19);
  for (c4_i77 = 0; c4_i77 < 16; c4_i77 = c4_i77 + 1) {
    c4_g1[c4_i77] = c4_dv19[c4_i77];
  }

  /*  gd*inv(gst0) */
  /*  select pw = [L2+L5;0;L1+L3+L4] */
  _SFD_SCRIPT_CALL(0, 83);
  for (c4_i78 = 0; c4_i78 < 16; c4_i78 = c4_i78 + 1) {
    c4_a[c4_i78] = c4_g1[c4_i78];
  }

  for (c4_i79 = 0; c4_i79 < 4; c4_i79 = c4_i79 + 1) {
    c4_b[c4_i79] = c4_b_pw[c4_i79];
  }

  c4_d_eml_scalar_eg(chartInstance);
  c4_d_eml_scalar_eg(chartInstance);
  for (c4_i80 = 0; c4_i80 < 16; c4_i80 = c4_i80 + 1) {
    c4_A[c4_i80] = c4_a[c4_i80];
  }

  for (c4_i81 = 0; c4_i81 < 4; c4_i81 = c4_i81 + 1) {
    c4_B[c4_i81] = c4_b[c4_i81];
  }

  for (c4_i82 = 0; c4_i82 < 4; c4_i82 = c4_i82 + 1) {
    c4_p1[c4_i82] = 0.0;
  }

  for (c4_i83 = 0; c4_i83 < 16; c4_i83 = c4_i83 + 1) {
    c4_b_A[c4_i83] = c4_A[c4_i83];
  }

  for (c4_i84 = 0; c4_i84 < 4; c4_i84 = c4_i84 + 1) {
    c4_b_B[c4_i84] = c4_B[c4_i84];
  }

  for (c4_i85 = 0; c4_i85 < 16; c4_i85 = c4_i85 + 1) {
    c4_c_A[c4_i85] = c4_b_A[c4_i85];
  }

  for (c4_i86 = 0; c4_i86 < 4; c4_i86 = c4_i86 + 1) {
    c4_c_B[c4_i86] = c4_b_B[c4_i86];
  }

  for (c4_i87 = 0; c4_i87 < 4; c4_i87 = c4_i87 + 1) {
    c4_p1[c4_i87] = 0.0;
    c4_i88 = 0;
    for (c4_i89 = 0; c4_i89 < 4; c4_i89 = c4_i89 + 1) {
      c4_p1[c4_i87] = c4_p1[c4_i87] + c4_c_A[c4_i88 + c4_i87] * c4_c_B[c4_i89];
      c4_i88 = c4_i88 + 4;
    }
  }

  _SFD_SCRIPT_CALL(0, 84);
  c4_theta_1 = c4_atan2(chartInstance, c4_p1[1], c4_p1[0]);

  /*  only one solution */
  _SFD_SCRIPT_CALL(0, 85);
  if (CV_SCRIPT_IF(0, 2, (real_T)c4_isInRange(chartInstance, c4_theta_1, -165.0,
        165.0) == 0.0)) {
    /* disp('Cannot find appropriate theta_1'); */
  } else {
    /*  select q2 = [L2;0;L1], subproblem3 */
    _SFD_SCRIPT_CALL(0, 91);
    for (c4_i90 = 0; c4_i90 < 6; c4_i90 = c4_i90 + 1) {
      c4_dv21[c4_i90] = c4_dv20[c4_i90];
    }

    c4_expWre(chartInstance, c4_dv21, c4_theta_1, c4_b_a);
    for (c4_i91 = 0; c4_i91 < 4; c4_i91 = c4_i91 + 1) {
      c4_b_b[c4_i91] = c4_p1[c4_i91];
    }

    c4_d_eml_scalar_eg(chartInstance);
    c4_d_eml_scalar_eg(chartInstance);
    for (c4_i92 = 0; c4_i92 < 16; c4_i92 = c4_i92 + 1) {
      c4_d_A[c4_i92] = c4_b_a[c4_i92];
    }

    for (c4_i93 = 0; c4_i93 < 4; c4_i93 = c4_i93 + 1) {
      c4_d_B[c4_i93] = c4_b_b[c4_i93];
    }

    for (c4_i94 = 0; c4_i94 < 4; c4_i94 = c4_i94 + 1) {
      c4_p2[c4_i94] = 0.0;
    }

    for (c4_i95 = 0; c4_i95 < 16; c4_i95 = c4_i95 + 1) {
      c4_e_A[c4_i95] = c4_d_A[c4_i95];
    }

    for (c4_i96 = 0; c4_i96 < 4; c4_i96 = c4_i96 + 1) {
      c4_e_B[c4_i96] = c4_d_B[c4_i96];
    }

    for (c4_i97 = 0; c4_i97 < 16; c4_i97 = c4_i97 + 1) {
      c4_f_A[c4_i97] = c4_e_A[c4_i97];
    }

    for (c4_i98 = 0; c4_i98 < 4; c4_i98 = c4_i98 + 1) {
      c4_f_B[c4_i98] = c4_e_B[c4_i98];
    }

    for (c4_i99 = 0; c4_i99 < 4; c4_i99 = c4_i99 + 1) {
      c4_p2[c4_i99] = 0.0;
      c4_i100 = 0;
      for (c4_i101 = 0; c4_i101 < 4; c4_i101 = c4_i101 + 1) {
        c4_p2[c4_i99] = c4_p2[c4_i99] + c4_f_A[c4_i100 + c4_i99] *
          c4_f_B[c4_i101];
        c4_i100 = c4_i100 + 4;
      }
    }

    _SFD_SCRIPT_CALL(0, 92);
    for (c4_i102 = 0; c4_i102 < 4; c4_i102 = c4_i102 + 1) {
      c4_d[c4_i102] = c4_p2[c4_i102] - c4_b_q2[c4_i102];
    }

    _SFD_SCRIPT_CALL(0, 93);
    for (c4_i103 = 0; c4_i103 < 6; c4_i103 = c4_i103 + 1) {
      c4_b_kx3[c4_i103] = c4_kx3[c4_i103];
    }

    for (c4_i104 = 0; c4_i104 < 4; c4_i104 = c4_i104 + 1) {
      c4_c_pw[c4_i104] = c4_b_pw[c4_i104];
    }

    for (c4_i105 = 0; c4_i105 < 4; c4_i105 = c4_i105 + 1) {
      c4_d_q2[c4_i105] = c4_b_q2[c4_i105];
    }

    for (c4_i106 = 0; c4_i106 < 4; c4_i106 = c4_i106 + 1) {
      c4_b_d[c4_i106] = c4_d[c4_i106];
    }

    c4_subPro3(chartInstance, c4_b_kx3, c4_c_pw, c4_d_q2, c4_b_d, c4_b_theta_3,
               &c4_b_Num_3);
    for (c4_i107 = 0; c4_i107 < 2; c4_i107 = c4_i107 + 1) {
      c4_theta_3[c4_i107] = c4_b_theta_3[c4_i107];
    }

    c4_Num_3 = c4_b_Num_3;

    /*  at most 2 solutions */
    _SFD_SCRIPT_CALL(0, 94);
    for (c4_i108 = 0; c4_i108 < 2; c4_i108 = c4_i108 + 1) {
      c4_c_theta_3[c4_i108] = c4_theta_3[c4_i108];
    }

    c4_b_isInRange(chartInstance, c4_c_theta_3, -210.0, 90.0, c4_bv1);
    for (c4_i109 = 0; c4_i109 < 2; c4_i109 = c4_i109 + 1) {
      c4_bv2[c4_i109] = ((real_T)c4_bv1[c4_i109] == 1.0);
    }

    if (CV_SCRIPT_IF(0, 3, (real_T)c4_any(chartInstance, c4_bv2) == 0.0)) {
      /* disp('Cannot find appropriate theta_3'); */
    } else {
      /*   */
      c4_c3 = 1.0;
      c4_b_c3 = 1.0;
     label_2:
      ;
      if (c4_b_c3 <= c4_Num_3) {
        c4_c3 = c4_b_c3;
        CV_SCRIPT_FOR(0, 0, 1);
        _SFD_SCRIPT_CALL(0, 102);
        if (CV_SCRIPT_IF(0, 4, (real_T)c4_isInRange(chartInstance,
              c4_theta_3[_SFD_EML_ARRAY_BOUNDS_CHECK("theta_3", (int32_T)
               _SFD_INTEGER_CHECK("c3", c4_c3), 1, 2, 1, 0) - 1], -210.0, 90.0) ==
                         1.0)) {
          _SFD_SCRIPT_CALL(0, 103);
          for (c4_i110 = 0; c4_i110 < 6; c4_i110 = c4_i110 + 1) {
            c4_c_kx3[c4_i110] = c4_kx3[c4_i110];
          }

          c4_expWre(chartInstance, c4_c_kx3,
                    c4_theta_3[_SFD_EML_ARRAY_BOUNDS_CHECK("theta_3", (int32_T)
                     _SFD_INTEGER_CHECK("c3", c4_c3), 1, 2
                     , 1, 0) - 1], c4_c_a);
          for (c4_i111 = 0; c4_i111 < 4; c4_i111 = c4_i111 + 1) {
            c4_c_b[c4_i111] = c4_b_pw[c4_i111];
          }

          c4_d_eml_scalar_eg(chartInstance);
          c4_d_eml_scalar_eg(chartInstance);
          for (c4_i112 = 0; c4_i112 < 16; c4_i112 = c4_i112 + 1) {
            c4_g_A[c4_i112] = c4_c_a[c4_i112];
          }

          for (c4_i113 = 0; c4_i113 < 4; c4_i113 = c4_i113 + 1) {
            c4_g_B[c4_i113] = c4_c_b[c4_i113];
          }

          for (c4_i114 = 0; c4_i114 < 4; c4_i114 = c4_i114 + 1) {
            c4_p3[c4_i114] = 0.0;
          }

          for (c4_i115 = 0; c4_i115 < 16; c4_i115 = c4_i115 + 1) {
            c4_h_A[c4_i115] = c4_g_A[c4_i115];
          }

          for (c4_i116 = 0; c4_i116 < 4; c4_i116 = c4_i116 + 1) {
            c4_h_B[c4_i116] = c4_g_B[c4_i116];
          }

          for (c4_i117 = 0; c4_i117 < 16; c4_i117 = c4_i117 + 1) {
            c4_i_A[c4_i117] = c4_h_A[c4_i117];
          }

          for (c4_i118 = 0; c4_i118 < 4; c4_i118 = c4_i118 + 1) {
            c4_i_B[c4_i118] = c4_h_B[c4_i118];
          }

          for (c4_i119 = 0; c4_i119 < 4; c4_i119 = c4_i119 + 1) {
            c4_p3[c4_i119] = 0.0;
            c4_i120 = 0;
            for (c4_i121 = 0; c4_i121 < 4; c4_i121 = c4_i121 + 1) {
              c4_p3[c4_i119] = c4_p3[c4_i119] + c4_i_A[c4_i120 + c4_i119] *
                c4_i_B[c4_i121];
              c4_i120 = c4_i120 + 4;
            }
          }

          _SFD_SCRIPT_CALL(0, 104);
          for (c4_i122 = 0; c4_i122 < 6; c4_i122 = c4_i122 + 1) {
            c4_b_kx2[c4_i122] = c4_kx2[c4_i122];
          }

          for (c4_i123 = 0; c4_i123 < 4; c4_i123 = c4_i123 + 1) {
            c4_b_p3[c4_i123] = c4_p3[c4_i123];
          }

          for (c4_i124 = 0; c4_i124 < 4; c4_i124 = c4_i124 + 1) {
            c4_b_p2[c4_i124] = c4_p2[c4_i124];
          }

          c4_theta_2 = c4_subPro1(chartInstance, c4_b_kx2, c4_b_p3, c4_b_p2);

          /*  only one solution */
          _SFD_SCRIPT_CALL(0, 105);
          if (CV_SCRIPT_IF(0, 5, (real_T)c4_isInRange(chartInstance, c4_theta_2,
                -150.0, 60.0) == 0.0)) {
            /* disp('Cannot find appropriate theta_2'); */
            goto label_1;
          } else {
            _SFD_SCRIPT_CALL(0, 110);
            for (c4_i125 = 0; c4_i125 < 6; c4_i125 = c4_i125 + 1) {
              c4_d_kx3[c4_i125] = -c4_kx3[c4_i125];
            }

            c4_expWre(chartInstance, c4_d_kx3,
                      c4_theta_3[_SFD_EML_ARRAY_BOUNDS_CHECK("theta_3", (int32_T)
                       _SFD_INTEGER_CHECK("c3", c4_c3), 1, 2
                       , 1, 0) - 1], c4_d_a);
            for (c4_i126 = 0; c4_i126 < 6; c4_i126 = c4_i126 + 1) {
              c4_c_kx2[c4_i126] = -c4_kx2[c4_i126];
            }

            c4_expWre(chartInstance, c4_c_kx2, c4_theta_2, c4_d_b);
            c4_b_eml_scalar_eg(chartInstance);
            c4_b_eml_scalar_eg(chartInstance);
            for (c4_i127 = 0; c4_i127 < 16; c4_i127 = c4_i127 + 1) {
              c4_j_A[c4_i127] = c4_d_a[c4_i127];
            }

            for (c4_i128 = 0; c4_i128 < 16; c4_i128 = c4_i128 + 1) {
              c4_j_B[c4_i128] = c4_d_b[c4_i128];
            }

            for (c4_i129 = 0; c4_i129 < 16; c4_i129 = c4_i129 + 1) {
              c4_k_A[c4_i129] = c4_j_A[c4_i129];
            }

            for (c4_i130 = 0; c4_i130 < 16; c4_i130 = c4_i130 + 1) {
              c4_k_B[c4_i130] = c4_j_B[c4_i130];
            }

            for (c4_i131 = 0; c4_i131 < 16; c4_i131 = c4_i131 + 1) {
              c4_l_A[c4_i131] = c4_k_A[c4_i131];
            }

            for (c4_i132 = 0; c4_i132 < 16; c4_i132 = c4_i132 + 1) {
              c4_l_B[c4_i132] = c4_k_B[c4_i132];
            }

            for (c4_i133 = 0; c4_i133 < 4; c4_i133 = c4_i133 + 1) {
              c4_i134 = 0;
              for (c4_i135 = 0; c4_i135 < 4; c4_i135 = c4_i135 + 1) {
                c4_y[c4_i134 + c4_i133] = 0.0;
                c4_i136 = 0;
                for (c4_i137 = 0; c4_i137 < 4; c4_i137 = c4_i137 + 1) {
                  c4_y[c4_i134 + c4_i133] = c4_y[c4_i134 + c4_i133] +
                    c4_l_A[c4_i136 + c4_i133] * c4_l_B[c4_i137 + c4_i134];
                  c4_i136 = c4_i136 + 4;
                }

                c4_i134 = c4_i134 + 4;
              }
            }

            for (c4_i138 = 0; c4_i138 < 16; c4_i138 = c4_i138 + 1) {
              c4_e_a[c4_i138] = c4_y[c4_i138];
            }

            for (c4_i139 = 0; c4_i139 < 6; c4_i139 = c4_i139 + 1) {
              c4_dv22[c4_i139] = c4_dv20[c4_i139];
            }

            c4_expWre(chartInstance, c4_dv22, c4_theta_1, c4_e_b);
            c4_b_eml_scalar_eg(chartInstance);
            c4_b_eml_scalar_eg(chartInstance);
            for (c4_i140 = 0; c4_i140 < 16; c4_i140 = c4_i140 + 1) {
              c4_m_A[c4_i140] = c4_e_a[c4_i140];
            }

            for (c4_i141 = 0; c4_i141 < 16; c4_i141 = c4_i141 + 1) {
              c4_m_B[c4_i141] = c4_e_b[c4_i141];
            }

            for (c4_i142 = 0; c4_i142 < 16; c4_i142 = c4_i142 + 1) {
              c4_n_A[c4_i142] = c4_m_A[c4_i142];
            }

            for (c4_i143 = 0; c4_i143 < 16; c4_i143 = c4_i143 + 1) {
              c4_n_B[c4_i143] = c4_m_B[c4_i143];
            }

            for (c4_i144 = 0; c4_i144 < 16; c4_i144 = c4_i144 + 1) {
              c4_o_A[c4_i144] = c4_n_A[c4_i144];
            }

            for (c4_i145 = 0; c4_i145 < 16; c4_i145 = c4_i145 + 1) {
              c4_o_B[c4_i145] = c4_n_B[c4_i145];
            }

            for (c4_i146 = 0; c4_i146 < 4; c4_i146 = c4_i146 + 1) {
              c4_i147 = 0;
              for (c4_i148 = 0; c4_i148 < 4; c4_i148 = c4_i148 + 1) {
                c4_b_y[c4_i147 + c4_i146] = 0.0;
                c4_i149 = 0;
                for (c4_i150 = 0; c4_i150 < 4; c4_i150 = c4_i150 + 1) {
                  c4_b_y[c4_i147 + c4_i146] = c4_b_y[c4_i147 + c4_i146] +
                    c4_o_A[c4_i149 + c4_i146] * c4_o_B[c4_i150 + c4_i147];
                  c4_i149 = c4_i149 + 4;
                }

                c4_i147 = c4_i147 + 4;
              }
            }

            for (c4_i151 = 0; c4_i151 < 16; c4_i151 = c4_i151 + 1) {
              c4_f_a[c4_i151] = c4_b_y[c4_i151];
            }

            for (c4_i152 = 0; c4_i152 < 16; c4_i152 = c4_i152 + 1) {
              c4_f_b[c4_i152] = c4_g1[c4_i152];
            }

            c4_b_eml_scalar_eg(chartInstance);
            c4_b_eml_scalar_eg(chartInstance);
            for (c4_i153 = 0; c4_i153 < 16; c4_i153 = c4_i153 + 1) {
              c4_p_A[c4_i153] = c4_f_a[c4_i153];
            }

            for (c4_i154 = 0; c4_i154 < 16; c4_i154 = c4_i154 + 1) {
              c4_p_B[c4_i154] = c4_f_b[c4_i154];
            }

            for (c4_i155 = 0; c4_i155 < 16; c4_i155 = c4_i155 + 1) {
              c4_g2[c4_i155] = 0.0;
            }

            for (c4_i156 = 0; c4_i156 < 16; c4_i156 = c4_i156 + 1) {
              c4_q_A[c4_i156] = c4_p_A[c4_i156];
            }

            for (c4_i157 = 0; c4_i157 < 16; c4_i157 = c4_i157 + 1) {
              c4_q_B[c4_i157] = c4_p_B[c4_i157];
            }

            for (c4_i158 = 0; c4_i158 < 16; c4_i158 = c4_i158 + 1) {
              c4_r_A[c4_i158] = c4_q_A[c4_i158];
            }

            for (c4_i159 = 0; c4_i159 < 16; c4_i159 = c4_i159 + 1) {
              c4_r_B[c4_i159] = c4_q_B[c4_i159];
            }

            for (c4_i160 = 0; c4_i160 < 4; c4_i160 = c4_i160 + 1) {
              c4_i161 = 0;
              for (c4_i162 = 0; c4_i162 < 4; c4_i162 = c4_i162 + 1) {
                c4_g2[c4_i161 + c4_i160] = 0.0;
                c4_i163 = 0;
                for (c4_i164 = 0; c4_i164 < 4; c4_i164 = c4_i164 + 1) {
                  c4_g2[c4_i161 + c4_i160] = c4_g2[c4_i161 + c4_i160] +
                    c4_r_A[c4_i163 + c4_i160] * c4_r_B[c4_i164 + c4_i161];
                  c4_i163 = c4_i163 + 4;
                }

                c4_i161 = c4_i161 + 4;
              }
            }

            /* select q7 */
            _SFD_SCRIPT_CALL(0, 113);
            for (c4_i165 = 0; c4_i165 < 16; c4_i165 = c4_i165 + 1) {
              c4_g_a[c4_i165] = c4_g2[c4_i165];
            }

            for (c4_i166 = 0; c4_i166 < 4; c4_i166 = c4_i166 + 1) {
              c4_g_b[c4_i166] = c4_b_q7[c4_i166];
            }

            c4_d_eml_scalar_eg(chartInstance);
            c4_d_eml_scalar_eg(chartInstance);
            for (c4_i167 = 0; c4_i167 < 16; c4_i167 = c4_i167 + 1) {
              c4_s_A[c4_i167] = c4_g_a[c4_i167];
            }

            for (c4_i168 = 0; c4_i168 < 4; c4_i168 = c4_i168 + 1) {
              c4_s_B[c4_i168] = c4_g_b[c4_i168];
            }

            for (c4_i169 = 0; c4_i169 < 4; c4_i169 = c4_i169 + 1) {
              c4_p4[c4_i169] = 0.0;
            }

            for (c4_i170 = 0; c4_i170 < 16; c4_i170 = c4_i170 + 1) {
              c4_t_A[c4_i170] = c4_s_A[c4_i170];
            }

            for (c4_i171 = 0; c4_i171 < 4; c4_i171 = c4_i171 + 1) {
              c4_t_B[c4_i171] = c4_s_B[c4_i171];
            }

            for (c4_i172 = 0; c4_i172 < 16; c4_i172 = c4_i172 + 1) {
              c4_u_A[c4_i172] = c4_t_A[c4_i172];
            }

            for (c4_i173 = 0; c4_i173 < 4; c4_i173 = c4_i173 + 1) {
              c4_u_B[c4_i173] = c4_t_B[c4_i173];
            }

            for (c4_i174 = 0; c4_i174 < 4; c4_i174 = c4_i174 + 1) {
              c4_p4[c4_i174] = 0.0;
              c4_i175 = 0;
              for (c4_i176 = 0; c4_i176 < 4; c4_i176 = c4_i176 + 1) {
                c4_p4[c4_i174] = c4_p4[c4_i174] + c4_u_A[c4_i175 + c4_i174] *
                  c4_u_B[c4_i176];
                c4_i175 = c4_i175 + 4;
              }
            }

            _SFD_SCRIPT_CALL(0, 114);
            for (c4_i177 = 0; c4_i177 < 6; c4_i177 = c4_i177 + 1) {
              c4_b_kx4[c4_i177] = c4_kx4[c4_i177];
            }

            for (c4_i178 = 0; c4_i178 < 6; c4_i178 = c4_i178 + 1) {
              c4_b_kx5[c4_i178] = c4_kx5[c4_i178];
            }

            for (c4_i179 = 0; c4_i179 < 4; c4_i179 = c4_i179 + 1) {
              c4_c_q7[c4_i179] = c4_b_q7[c4_i179];
            }

            for (c4_i180 = 0; c4_i180 < 4; c4_i180 = c4_i180 + 1) {
              c4_b_p4[c4_i180] = c4_p4[c4_i180];
            }

            c4_subPro2(chartInstance, c4_b_kx4, c4_b_kx5, c4_c_q7, c4_b_p4,
                       c4_b_theta_4, c4_b_theta_5, &c4_b_Num_45);
            for (c4_i181 = 0; c4_i181 < 2; c4_i181 = c4_i181 + 1) {
              c4_theta_4[c4_i181] = c4_b_theta_4[c4_i181];
            }

            for (c4_i182 = 0; c4_i182 < 2; c4_i182 = c4_i182 + 1) {
              c4_theta_5[c4_i182] = c4_b_theta_5[c4_i182];
            }

            c4_Num_45 = c4_b_Num_45;

            /*  at most 2 pairs of solution */
            _SFD_SCRIPT_CALL(0, 116);
            for (c4_i183 = 0; c4_i183 < 2; c4_i183 = c4_i183 + 1) {
              c4_c_theta_5[c4_i183] = c4_theta_5[c4_i183];
            }

            c4_b_isInRange(chartInstance, c4_c_theta_5, -140.0, 140.0, c4_bv3);
            for (c4_i184 = 0; c4_i184 < 2; c4_i184 = c4_i184 + 1) {
              c4_bv4[c4_i184] = ((real_T)c4_bv3[c4_i184] == 1.0);
            }

            if (CV_SCRIPT_IF(0, 6, (real_T)c4_any(chartInstance, c4_bv4) == 0.0))
            {
              /* disp('Cannot find appropriate theta_5'); */
              goto label_1;
            } else {
              c4_c45 = 1.0;
              c4_b_c45 = 1.0;
              while (c4_b_c45 <= c4_Num_45) {
                c4_c45 = c4_b_c45;
                CV_SCRIPT_FOR(0, 1, 1);
                _SFD_SCRIPT_CALL(0, 122);
                if (CV_SCRIPT_IF(0, 7, (real_T)c4_isInRange(chartInstance,
                      c4_theta_5[_SFD_EML_ARRAY_BOUNDS_CHECK("theta_5", (int32_T)
                       _SFD_INTEGER_CHECK("c45", c4_c45), 1, 2, 1, 0) - 1],
                      -140.0, 140.0) == 1.0)) {
                  _SFD_SCRIPT_CALL(0, 123);
                  for (c4_i185 = 0; c4_i185 < 6; c4_i185 = c4_i185 + 1) {
                    c4_c_kx5[c4_i185] = -c4_kx5[c4_i185];
                  }

                  c4_expWre(chartInstance, c4_c_kx5,
                            c4_theta_5[_SFD_EML_ARRAY_BOUNDS_CHECK("theta_5",
                             (int32_T)_SFD_INTEGER_CHECK("c45", c4_c45), 1,
                             2, 1, 0) - 1], c4_h_a);
                  for (c4_i186 = 0; c4_i186 < 6; c4_i186 = c4_i186 + 1) {
                    c4_c_kx4[c4_i186] = -c4_kx4[c4_i186];
                  }

                  c4_expWre(chartInstance, c4_c_kx4,
                            c4_theta_4[_SFD_EML_ARRAY_BOUNDS_CHECK("theta_4",
                             (int32_T)_SFD_INTEGER_CHECK("c45", c4_c45), 1,
                             2, 1, 0) - 1], c4_h_b);
                  c4_b_eml_scalar_eg(chartInstance);
                  c4_b_eml_scalar_eg(chartInstance);
                  for (c4_i187 = 0; c4_i187 < 16; c4_i187 = c4_i187 + 1) {
                    c4_v_A[c4_i187] = c4_h_a[c4_i187];
                  }

                  for (c4_i188 = 0; c4_i188 < 16; c4_i188 = c4_i188 + 1) {
                    c4_v_B[c4_i188] = c4_h_b[c4_i188];
                  }

                  for (c4_i189 = 0; c4_i189 < 16; c4_i189 = c4_i189 + 1) {
                    c4_w_A[c4_i189] = c4_v_A[c4_i189];
                  }

                  for (c4_i190 = 0; c4_i190 < 16; c4_i190 = c4_i190 + 1) {
                    c4_w_B[c4_i190] = c4_v_B[c4_i190];
                  }

                  for (c4_i191 = 0; c4_i191 < 16; c4_i191 = c4_i191 + 1) {
                    c4_x_A[c4_i191] = c4_w_A[c4_i191];
                  }

                  for (c4_i192 = 0; c4_i192 < 16; c4_i192 = c4_i192 + 1) {
                    c4_x_B[c4_i192] = c4_w_B[c4_i192];
                  }

                  for (c4_i193 = 0; c4_i193 < 4; c4_i193 = c4_i193 + 1) {
                    c4_i194 = 0;
                    for (c4_i195 = 0; c4_i195 < 4; c4_i195 = c4_i195 + 1) {
                      c4_c_y[c4_i194 + c4_i193] = 0.0;
                      c4_i196 = 0;
                      for (c4_i197 = 0; c4_i197 < 4; c4_i197 = c4_i197 + 1) {
                        c4_c_y[c4_i194 + c4_i193] = c4_c_y[c4_i194 + c4_i193] +
                          c4_x_A[c4_i196 + c4_i193] * c4_x_B[c4_i197 + c4_i194];
                        c4_i196 = c4_i196 + 4;
                      }

                      c4_i194 = c4_i194 + 4;
                    }
                  }

                  for (c4_i198 = 0; c4_i198 < 16; c4_i198 = c4_i198 + 1) {
                    c4_i_a[c4_i198] = c4_c_y[c4_i198];
                  }

                  for (c4_i199 = 0; c4_i199 < 16; c4_i199 = c4_i199 + 1) {
                    c4_i_b[c4_i199] = c4_g2[c4_i199];
                  }

                  c4_b_eml_scalar_eg(chartInstance);
                  c4_b_eml_scalar_eg(chartInstance);
                  for (c4_i200 = 0; c4_i200 < 16; c4_i200 = c4_i200 + 1) {
                    c4_y_A[c4_i200] = c4_i_a[c4_i200];
                  }

                  for (c4_i201 = 0; c4_i201 < 16; c4_i201 = c4_i201 + 1) {
                    c4_y_B[c4_i201] = c4_i_b[c4_i201];
                  }

                  for (c4_i202 = 0; c4_i202 < 16; c4_i202 = c4_i202 + 1) {
                    c4_g3[c4_i202] = 0.0;
                  }

                  for (c4_i203 = 0; c4_i203 < 16; c4_i203 = c4_i203 + 1) {
                    c4_ab_A[c4_i203] = c4_y_A[c4_i203];
                  }

                  for (c4_i204 = 0; c4_i204 < 16; c4_i204 = c4_i204 + 1) {
                    c4_ab_B[c4_i204] = c4_y_B[c4_i204];
                  }

                  for (c4_i205 = 0; c4_i205 < 16; c4_i205 = c4_i205 + 1) {
                    c4_bb_A[c4_i205] = c4_ab_A[c4_i205];
                  }

                  for (c4_i206 = 0; c4_i206 < 16; c4_i206 = c4_i206 + 1) {
                    c4_bb_B[c4_i206] = c4_ab_B[c4_i206];
                  }

                  for (c4_i207 = 0; c4_i207 < 4; c4_i207 = c4_i207 + 1) {
                    c4_i208 = 0;
                    for (c4_i209 = 0; c4_i209 < 4; c4_i209 = c4_i209 + 1) {
                      c4_g3[c4_i208 + c4_i207] = 0.0;
                      c4_i210 = 0;
                      for (c4_i211 = 0; c4_i211 < 4; c4_i211 = c4_i211 + 1) {
                        c4_g3[c4_i208 + c4_i207] = c4_g3[c4_i208 + c4_i207] +
                          c4_bb_A[c4_i210 + c4_i207] * c4_bb_B[c4_i211 + c4_i208];
                        c4_i210 = c4_i210 + 4;
                      }

                      c4_i208 = c4_i208 + 4;
                    }
                  }

                  /* selcet q3 */
                  _SFD_SCRIPT_CALL(0, 125);
                  for (c4_i212 = 0; c4_i212 < 16; c4_i212 = c4_i212 + 1) {
                    c4_j_a[c4_i212] = c4_g3[c4_i212];
                  }

                  for (c4_i213 = 0; c4_i213 < 4; c4_i213 = c4_i213 + 1) {
                    c4_j_b[c4_i213] = c4_b_q3[c4_i213];
                  }

                  c4_d_eml_scalar_eg(chartInstance);
                  c4_d_eml_scalar_eg(chartInstance);
                  for (c4_i214 = 0; c4_i214 < 16; c4_i214 = c4_i214 + 1) {
                    c4_cb_A[c4_i214] = c4_j_a[c4_i214];
                  }

                  for (c4_i215 = 0; c4_i215 < 4; c4_i215 = c4_i215 + 1) {
                    c4_cb_B[c4_i215] = c4_j_b[c4_i215];
                  }

                  for (c4_i216 = 0; c4_i216 < 4; c4_i216 = c4_i216 + 1) {
                    c4_p5[c4_i216] = 0.0;
                  }

                  for (c4_i217 = 0; c4_i217 < 16; c4_i217 = c4_i217 + 1) {
                    c4_db_A[c4_i217] = c4_cb_A[c4_i217];
                  }

                  for (c4_i218 = 0; c4_i218 < 4; c4_i218 = c4_i218 + 1) {
                    c4_db_B[c4_i218] = c4_cb_B[c4_i218];
                  }

                  for (c4_i219 = 0; c4_i219 < 16; c4_i219 = c4_i219 + 1) {
                    c4_eb_A[c4_i219] = c4_db_A[c4_i219];
                  }

                  for (c4_i220 = 0; c4_i220 < 4; c4_i220 = c4_i220 + 1) {
                    c4_eb_B[c4_i220] = c4_db_B[c4_i220];
                  }

                  for (c4_i221 = 0; c4_i221 < 4; c4_i221 = c4_i221 + 1) {
                    c4_p5[c4_i221] = 0.0;
                    c4_i222 = 0;
                    for (c4_i223 = 0; c4_i223 < 4; c4_i223 = c4_i223 + 1) {
                      c4_p5[c4_i221] = c4_p5[c4_i221] + c4_eb_A[c4_i222 +
                        c4_i221] * c4_eb_B[c4_i223];
                      c4_i222 = c4_i222 + 4;
                    }
                  }

                  _SFD_SCRIPT_CALL(0, 126);
                  for (c4_i224 = 0; c4_i224 < 6; c4_i224 = c4_i224 + 1) {
                    c4_b_kx6[c4_i224] = c4_kx6[c4_i224];
                  }

                  for (c4_i225 = 0; c4_i225 < 4; c4_i225 = c4_i225 + 1) {
                    c4_d_q3[c4_i225] = c4_b_q3[c4_i225];
                  }

                  for (c4_i226 = 0; c4_i226 < 4; c4_i226 = c4_i226 + 1) {
                    c4_b_p5[c4_i226] = c4_p5[c4_i226];
                  }

                  c4_theta_6 = c4_subPro1(chartInstance, c4_b_kx6, c4_d_q3,
                    c4_b_p5);

                  /*  only one solution */
                  _SFD_SCRIPT_CALL(0, 128);
                  *c4_Num = *c4_Num + 1.0;
                  _SFD_SCRIPT_CALL(0, 129);
                  c4_b_Num = _SFD_EML_ARRAY_BOUNDS_CHECK("theta", (int32_T)
                    _SFD_INTEGER_CHECK("Num", *c4_Num), 1, 4, 2, 0) - 1;
                  c4_b_theta_1[0] = c4_theta_1;
                  c4_b_theta_1[1] = c4_theta_2;
                  c4_b_theta_1[2] = c4_theta_3[_SFD_EML_ARRAY_BOUNDS_CHECK(
                    "theta_3", (int32_T)_SFD_INTEGER_CHECK("c3", c4_c3), 1, 2, 1,
                    0) - 1];
                  c4_b_theta_1[3] = c4_theta_4[_SFD_EML_ARRAY_BOUNDS_CHECK(
                    "theta_4", (int32_T)_SFD_INTEGER_CHECK("c45", c4_c45), 1, 2,
                    1, 0) - 1];
                  c4_b_theta_1[4] = c4_theta_5[_SFD_EML_ARRAY_BOUNDS_CHECK(
                    "theta_5", (int32_T)_SFD_INTEGER_CHECK("c45", c4_c45), 1, 2,
                    1, 0) - 1];
                  c4_b_theta_1[5] = c4_theta_6;
                  for (c4_i227 = 0; c4_i227 < 6; c4_i227 = c4_i227 + 1) {
                    c4_theta[c4_i227 + 6 * c4_b_Num] = c4_b_theta_1[c4_i227];
                  }
                }

                c4_b_c45 = c4_b_c45 + 1.0;
                sf_mex_listen_for_ctrl_c(chartInstance->S);
              }

              CV_SCRIPT_FOR(0, 1, 0);
            }
          }
        }
      } else {
        CV_SCRIPT_FOR(0, 0, 0);

        /*  check range */
        /* disp(theta*180/pi);   */
        goto label_1;
      }

      c4_b_c3 = c4_b_c3 + 1.0;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
      goto label_2;
     label_1:
      ;
    }
  }

  _SFD_SCRIPT_CALL(0, -129);
  sf_debug_symbol_scope_pop();
}

static void c4_cross(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                     real_T c4_a[3], real_T c4_b[3], real_T c4_c[3])
{
  real_T c4_b_a;
  real_T c4_b_b;
  real_T c4_y;
  real_T c4_c_a;
  real_T c4_c_b;
  real_T c4_b_y;
  real_T c4_c1;
  real_T c4_d_a;
  real_T c4_d_b;
  real_T c4_c_y;
  real_T c4_e_a;
  real_T c4_e_b;
  real_T c4_d_y;
  real_T c4_c2;
  real_T c4_f_a;
  real_T c4_f_b;
  real_T c4_e_y;
  real_T c4_g_a;
  real_T c4_g_b;
  real_T c4_f_y;
  real_T c4_c3;
  c4_b_a = c4_a[1];
  c4_b_b = c4_b[2];
  c4_y = c4_b_a * c4_b_b;
  c4_c_a = c4_a[2];
  c4_c_b = c4_b[1];
  c4_b_y = c4_c_a * c4_c_b;
  c4_c1 = c4_y - c4_b_y;
  c4_d_a = c4_a[2];
  c4_d_b = c4_b[0];
  c4_c_y = c4_d_a * c4_d_b;
  c4_e_a = c4_a[0];
  c4_e_b = c4_b[2];
  c4_d_y = c4_e_a * c4_e_b;
  c4_c2 = c4_c_y - c4_d_y;
  c4_f_a = c4_a[0];
  c4_f_b = c4_b[1];
  c4_e_y = c4_f_a * c4_f_b;
  c4_g_a = c4_a[1];
  c4_g_b = c4_b[0];
  c4_f_y = c4_g_a * c4_g_b;
  c4_c3 = c4_e_y - c4_f_y;
  c4_c[0] = c4_c1;
  c4_c[1] = c4_c2;
  c4_c[2] = c4_c3;
}

static boolean_T c4_all(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  boolean_T c4_x[2])
{
  boolean_T c4_y;
  int32_T c4_i228;
  boolean_T c4_b_x[2];
  real_T c4_k;
  real_T c4_b_k;
  for (c4_i228 = 0; c4_i228 < 2; c4_i228 = c4_i228 + 1) {
    c4_b_x[c4_i228] = c4_x[c4_i228];
  }

  c4_y = TRUE;
  c4_k = 1.0;
 label_1:
  ;
  if (c4_k <= 2.0) {
    c4_b_k = c4_k;
    if ((real_T)c4_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
         _SFD_INTEGER_CHECK("", c4_b_k), 1, 2, 1, 0) - 1] == 0.0) {
      return FALSE;
    } else {
      c4_k = c4_k + 1.0;
      goto label_1;
    }
  }

  return c4_y;
}

static void c4_mrdivide(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_A[16], real_T c4_B[16], real_T c4_y[16])
{
  int32_T c4_i229;
  int32_T c4_i230;
  int32_T c4_i231;
  int32_T c4_i232;
  real_T c4_b_A[16];
  int32_T c4_i233;
  int32_T c4_i234;
  int32_T c4_i235;
  int32_T c4_i236;
  real_T c4_b_B[16];
  int32_T c4_i237;
  real_T c4_c_A[16];
  int32_T c4_i238;
  real_T c4_c_B[16];
  int32_T c4_i239;
  real_T c4_d_A[16];
  int32_T c4_i240;
  real_T c4_d_B[16];
  int32_T c4_i241;
  real_T c4_e_A[16];
  int32_T c4_i242;
  real_T c4_f_A[16];
  int32_T c4_i243;
  real_T c4_g_A[16];
  int32_T c4_i244;
  real_T c4_h_A[16];
  int32_T c4_i245;
  real_T c4_i_A[16];
  int32_T c4_info;
  int32_T c4_ipiv[4];
  real_T c4_j_A[16];
  int32_T c4_i246;
  int32_T c4_i247;
  int32_T c4_b_ipiv[4];
  int32_T c4_b_info;
  int32_T c4_i248;
  int32_T c4_i249;
  int32_T c4_c_ipiv[4];
  int32_T c4_c_info;
  int32_T c4_i250;
  int32_T c4_i251;
  int32_T c4_d_ipiv[4];
  int32_T c4_d_info;
  int32_T c4_i252;
  real_T c4_Y[16];
  int32_T c4_i;
  int32_T c4_b_i;
  int32_T c4_ip;
  int32_T c4_j;
  int32_T c4_b_j;
  real_T c4_temp;
  int32_T c4_i253;
  real_T c4_k_A[16];
  int32_T c4_i254;
  real_T c4_b_Y[16];
  int32_T c4_i255;
  real_T c4_l_A[16];
  int32_T c4_i256;
  real_T c4_e_B[16];
  int32_T c4_i257;
  int32_T c4_i258;
  real_T c4_m_A[16];
  int32_T c4_i259;
  real_T c4_c_Y[16];
  int32_T c4_i260;
  int32_T c4_i261;
  int32_T c4_i262;
  int32_T c4_i263;
  c4_i229 = 0;
  for (c4_i230 = 0; c4_i230 < 4; c4_i230 = c4_i230 + 1) {
    c4_i231 = 0;
    for (c4_i232 = 0; c4_i232 < 4; c4_i232 = c4_i232 + 1) {
      c4_b_A[c4_i232 + c4_i229] = c4_B[c4_i231 + c4_i230];
      c4_i231 = c4_i231 + 4;
    }

    c4_i229 = c4_i229 + 4;
  }

  c4_i233 = 0;
  for (c4_i234 = 0; c4_i234 < 4; c4_i234 = c4_i234 + 1) {
    c4_i235 = 0;
    for (c4_i236 = 0; c4_i236 < 4; c4_i236 = c4_i236 + 1) {
      c4_b_B[c4_i236 + c4_i233] = c4_A[c4_i235 + c4_i234];
      c4_i235 = c4_i235 + 4;
    }

    c4_i233 = c4_i233 + 4;
  }

  for (c4_i237 = 0; c4_i237 < 16; c4_i237 = c4_i237 + 1) {
    c4_c_A[c4_i237] = c4_b_A[c4_i237];
  }

  for (c4_i238 = 0; c4_i238 < 16; c4_i238 = c4_i238 + 1) {
    c4_c_B[c4_i238] = c4_b_B[c4_i238];
  }

  for (c4_i239 = 0; c4_i239 < 16; c4_i239 = c4_i239 + 1) {
    c4_d_A[c4_i239] = c4_c_A[c4_i239];
  }

  for (c4_i240 = 0; c4_i240 < 16; c4_i240 = c4_i240 + 1) {
    c4_d_B[c4_i240] = c4_c_B[c4_i240];
  }

  for (c4_i241 = 0; c4_i241 < 16; c4_i241 = c4_i241 + 1) {
    c4_e_A[c4_i241] = c4_d_A[c4_i241];
  }

  for (c4_i242 = 0; c4_i242 < 16; c4_i242 = c4_i242 + 1) {
    c4_f_A[c4_i242] = c4_e_A[c4_i242];
  }

  for (c4_i243 = 0; c4_i243 < 16; c4_i243 = c4_i243 + 1) {
    c4_g_A[c4_i243] = c4_f_A[c4_i243];
  }

  for (c4_i244 = 0; c4_i244 < 16; c4_i244 = c4_i244 + 1) {
    c4_h_A[c4_i244] = c4_g_A[c4_i244];
  }

  for (c4_i245 = 0; c4_i245 < 16; c4_i245 = c4_i245 + 1) {
    c4_i_A[c4_i245] = c4_h_A[c4_i245];
  }

  c4_eml_matlab_zgetrf(chartInstance, c4_i_A, c4_j_A, c4_ipiv, &c4_info);
  for (c4_i246 = 0; c4_i246 < 16; c4_i246 = c4_i246 + 1) {
    c4_h_A[c4_i246] = c4_j_A[c4_i246];
  }

  for (c4_i247 = 0; c4_i247 < 4; c4_i247 = c4_i247 + 1) {
    c4_b_ipiv[c4_i247] = c4_ipiv[c4_i247];
  }

  c4_b_info = c4_info;
  for (c4_i248 = 0; c4_i248 < 16; c4_i248 = c4_i248 + 1) {
    c4_f_A[c4_i248] = c4_h_A[c4_i248];
  }

  for (c4_i249 = 0; c4_i249 < 4; c4_i249 = c4_i249 + 1) {
    c4_c_ipiv[c4_i249] = c4_b_ipiv[c4_i249];
  }

  c4_c_info = c4_b_info;
  for (c4_i250 = 0; c4_i250 < 16; c4_i250 = c4_i250 + 1) {
    c4_d_A[c4_i250] = c4_f_A[c4_i250];
  }

  for (c4_i251 = 0; c4_i251 < 4; c4_i251 = c4_i251 + 1) {
    c4_d_ipiv[c4_i251] = c4_c_ipiv[c4_i251];
  }

  c4_d_info = c4_c_info;
  if ((real_T)c4_d_info > 0.0) {
    c4_eml_warning(chartInstance);
  }

  c4_b_eml_scalar_eg(chartInstance);
  for (c4_i252 = 0; c4_i252 < 16; c4_i252 = c4_i252 + 1) {
    c4_Y[c4_i252] = c4_d_B[c4_i252];
  }

  for (c4_i = 1; c4_i < 5; c4_i = c4_i + 1) {
    c4_b_i = c4_i;
    if (c4_d_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_b_i), 1, 4, 1, 0) - 1] != c4_b_i) {
      c4_ip = c4_d_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c4_b_i), 1, 4, 1, 0) - 1];
      for (c4_j = 1; c4_j < 5; c4_j = c4_j + 1) {
        c4_b_j = c4_j;
        c4_temp = c4_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_b_i), 1, 4, 1, 0) - 1) + ((
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_b_j), 1, 4, 2, 0) - 1) << 2)];
        c4_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c4_b_i), 1, 4, 1, 0) - 1) + ((
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_b_j), 1, 4, 2, 0) - 1) << 2)] = c4_Y[(
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_ip), 1, 4, 1, 0) - 1) + ((_SFD_EML_ARRAY_BOUNDS_CHECK(""
          , (int32_T)_SFD_INTEGER_CHECK("", (real_T)c4_b_j), 1, 4, 2, 0) - 1) <<
          2)];
        c4_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c4_ip), 1, 4, 1, 0) - 1) + ((
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_b_j), 1, 4, 2, 0) - 1) << 2)] = c4_temp;
      }
    }
  }

  for (c4_i253 = 0; c4_i253 < 16; c4_i253 = c4_i253 + 1) {
    c4_k_A[c4_i253] = c4_d_A[c4_i253];
  }

  for (c4_i254 = 0; c4_i254 < 16; c4_i254 = c4_i254 + 1) {
    c4_b_Y[c4_i254] = c4_Y[c4_i254];
  }

  c4_eml_xtrsm(chartInstance, c4_k_A, c4_b_Y, c4_Y);
  for (c4_i255 = 0; c4_i255 < 16; c4_i255 = c4_i255 + 1) {
    c4_l_A[c4_i255] = c4_d_A[c4_i255];
  }

  for (c4_i256 = 0; c4_i256 < 16; c4_i256 = c4_i256 + 1) {
    c4_e_B[c4_i256] = c4_Y[c4_i256];
  }

  for (c4_i257 = 0; c4_i257 < 16; c4_i257 = c4_i257 + 1) {
    c4_Y[c4_i257] = c4_e_B[c4_i257];
  }

  for (c4_i258 = 0; c4_i258 < 16; c4_i258 = c4_i258 + 1) {
    c4_m_A[c4_i258] = c4_l_A[c4_i258];
  }

  for (c4_i259 = 0; c4_i259 < 16; c4_i259 = c4_i259 + 1) {
    c4_c_Y[c4_i259] = c4_Y[c4_i259];
  }

  c4_eml_blas_xtrsm(chartInstance, 4, 4, 1.0, c4_m_A, 1, 4, c4_c_Y, 1, 4, c4_Y);
  c4_i260 = 0;
  for (c4_i261 = 0; c4_i261 < 4; c4_i261 = c4_i261 + 1) {
    c4_i262 = 0;
    for (c4_i263 = 0; c4_i263 < 4; c4_i263 = c4_i263 + 1) {
      c4_y[c4_i263 + c4_i260] = c4_Y[c4_i262 + c4_i261];
      c4_i262 = c4_i262 + 4;
    }

    c4_i260 = c4_i260 + 4;
  }
}

static real_T c4_power(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_a, real_T c4_b)
{
  real_T c4_ak;
  real_T c4_bk;
  real_T c4_x;
  real_T c4_b_x;
  c4_eml_scalar_eg(chartInstance);
  c4_ak = c4_a;
  c4_bk = c4_b;
  if (c4_ak < 0.0) {
    c4_x = c4_bk;
    c4_b_x = c4_x;
    c4_b_x = muDoubleScalarFloor(c4_b_x);
    if (c4_b_x != c4_bk) {
      c4_eml_error(chartInstance);
      goto label_1;
    }
  }

 label_1:
  ;
  return muDoubleScalarPower(c4_ak, c4_bk);
}

static void c4_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c4_eml_error(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  int32_T c4_i264;
  static char_T c4_cv0[32] = { 'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'p', 'o', 'w', 'e', 'r', ':'
    , 'd', 'o', 'm', 'a', 'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c4_u[32];
  const mxArray *c4_y = NULL;
  int32_T c4_i265;
  static char_T c4_cv1[102] = { 'D', 'o', 'm', 'a', 'i', 'n', ' ', 'e', 'r', 'r',
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

  char_T c4_b_u[102];
  const mxArray *c4_b_y = NULL;
  for (c4_i264 = 0; c4_i264 < 32; c4_i264 = c4_i264 + 1) {
    c4_u[c4_i264] = c4_cv0[c4_i264];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 32));
  for (c4_i265 = 0; c4_i265 < 102; c4_i265 = c4_i265 + 1) {
    c4_b_u[c4_i265] = c4_cv1[c4_i265];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 102));
  sf_mex_call_debug("error", 0U, 2U, 14, c4_y, 14, c4_b_y);
}

static void c4_eps(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
}

static void c4_eml_matlab_zgetrf(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_A[16], real_T c4_b_A[16], int32_T
  c4_ipiv[4], int32_T *c4_info)
{
  int32_T c4_i266;
  int32_T c4_i267;
  int32_T c4_j;
  int32_T c4_b_j;
  int32_T c4_a;
  int32_T c4_jm1;
  int32_T c4_b;
  int32_T c4_mmj;
  int32_T c4_b_a;
  int32_T c4_c;
  int32_T c4_b_b;
  int32_T c4_jj;
  int32_T c4_c_a;
  int32_T c4_jp1j;
  int32_T c4_d_a;
  int32_T c4_b_c;
  int32_T c4_i268;
  real_T c4_c_A[16];
  int32_T c4_e_a;
  int32_T c4_jpiv_offset;
  int32_T c4_f_a;
  int32_T c4_c_b;
  int32_T c4_jpiv;
  int32_T c4_g_a;
  int32_T c4_d_b;
  int32_T c4_c_c;
  int32_T c4_e_b;
  int32_T c4_jrow;
  int32_T c4_h_a;
  int32_T c4_f_b;
  int32_T c4_jprow;
  int32_T c4_i269;
  real_T c4_x[16];
  int32_T c4_ix0;
  int32_T c4_iy0;
  int32_T c4_i270;
  int32_T c4_i271;
  real_T c4_b_x[16];
  int32_T c4_b_ix0;
  int32_T c4_b_iy0;
  int32_T c4_i272;
  real_T c4_c_x[16];
  int32_T c4_i273;
  real_T c4_d_x[16];
  real_T c4_e_x[16];
  int32_T c4_i274;
  int32_T c4_i275;
  int32_T c4_b_jp1j;
  int32_T c4_i_a;
  int32_T c4_d_c;
  int32_T c4_j_a;
  int32_T c4_g_b;
  int32_T c4_loop_ub;
  int32_T c4_i;
  int32_T c4_b_i;
  real_T c4_f_x;
  real_T c4_y;
  real_T c4_g_x;
  real_T c4_b_y;
  real_T c4_z;
  int32_T c4_h_b;
  int32_T c4_e_c;
  int32_T c4_k_a;
  int32_T c4_f_c;
  int32_T c4_l_a;
  int32_T c4_g_c;
  int32_T c4_m;
  int32_T c4_n;
  int32_T c4_c_ix0;
  int32_T c4_c_iy0;
  int32_T c4_i276;
  real_T c4_d_A[16];
  int32_T c4_ia0;
  int32_T c4_i277;
  int32_T c4_b_m;
  int32_T c4_b_n;
  int32_T c4_d_ix0;
  int32_T c4_d_iy0;
  int32_T c4_i278;
  real_T c4_e_A[16];
  int32_T c4_b_ia0;
  int32_T c4_i279;
  int32_T c4_c_m;
  int32_T c4_c_n;
  int32_T c4_e_ix0;
  int32_T c4_e_iy0;
  int32_T c4_i280;
  real_T c4_f_A[16];
  int32_T c4_c_ia0;
  int32_T c4_i281;
  int32_T c4_i282;
  real_T c4_g_A[16];
  for (c4_i266 = 0; c4_i266 < 16; c4_i266 = c4_i266 + 1) {
    c4_b_A[c4_i266] = c4_A[c4_i266];
  }

  c4_eps(chartInstance);
  for (c4_i267 = 0; c4_i267 < 4; c4_i267 = c4_i267 + 1) {
    c4_ipiv[c4_i267] = 1 + c4_i267;
  }

  *c4_info = 0;
  for (c4_j = 1; c4_j < 4; c4_j = c4_j + 1) {
    c4_b_j = c4_j;
    c4_a = c4_b_j;
    c4_jm1 = c4_a - 1;
    c4_b = c4_b_j;
    c4_mmj = 4 - c4_b;
    c4_b_a = c4_jm1;
    c4_c = c4_b_a * 5;
    c4_b_b = c4_c;
    c4_jj = 1 + c4_b_b;
    c4_c_a = c4_jj;
    c4_jp1j = c4_c_a + 1;
    c4_d_a = c4_mmj;
    c4_b_c = c4_d_a + 1;
    for (c4_i268 = 0; c4_i268 < 16; c4_i268 = c4_i268 + 1) {
      c4_c_A[c4_i268] = c4_b_A[c4_i268];
    }

    c4_e_a = c4_eml_ixamax(chartInstance, c4_b_c, c4_c_A, c4_jj);
    c4_jpiv_offset = c4_e_a - 1;
    c4_f_a = c4_jj;
    c4_c_b = c4_jpiv_offset;
    c4_jpiv = c4_f_a + c4_c_b;
    if (c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_jpiv), 1, 16, 1, 0) - 1] != 0.0) {
      if ((real_T)c4_jpiv_offset != 0.0) {
        c4_g_a = c4_b_j;
        c4_d_b = c4_jpiv_offset;
        c4_c_c = c4_g_a + c4_d_b;
        c4_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_b_j), 1, 4, 1, 0) - 1] = c4_c_c;
        c4_e_b = c4_jm1;
        c4_jrow = 1 + c4_e_b;
        c4_h_a = c4_jrow;
        c4_f_b = c4_jpiv_offset;
        c4_jprow = c4_h_a + c4_f_b;
        for (c4_i269 = 0; c4_i269 < 16; c4_i269 = c4_i269 + 1) {
          c4_x[c4_i269] = c4_b_A[c4_i269];
        }

        c4_ix0 = c4_jrow;
        c4_iy0 = c4_jprow;
        for (c4_i270 = 0; c4_i270 < 16; c4_i270 = c4_i270 + 1) {
          c4_b_A[c4_i270] = c4_x[c4_i270];
        }

        for (c4_i271 = 0; c4_i271 < 16; c4_i271 = c4_i271 + 1) {
          c4_b_x[c4_i271] = c4_b_A[c4_i271];
        }

        c4_b_ix0 = c4_ix0;
        c4_b_iy0 = c4_iy0;
        for (c4_i272 = 0; c4_i272 < 16; c4_i272 = c4_i272 + 1) {
          c4_c_x[c4_i272] = c4_b_x[c4_i272];
        }

        for (c4_i273 = 0; c4_i273 < 16; c4_i273 = c4_i273 + 1) {
          c4_d_x[c4_i273] = c4_c_x[c4_i273];
        }

        c4_ceval_xswap(chartInstance, 4, c4_d_x, c4_b_ix0, 4, c4_b_iy0, 4,
                       c4_e_x);
        for (c4_i274 = 0; c4_i274 < 16; c4_i274 = c4_i274 + 1) {
          c4_c_x[c4_i274] = c4_e_x[c4_i274];
        }

        for (c4_i275 = 0; c4_i275 < 16; c4_i275 = c4_i275 + 1) {
          c4_b_A[c4_i275] = c4_c_x[c4_i275];
        }
      }

      c4_b_jp1j = c4_jp1j;
      c4_i_a = c4_mmj;
      c4_d_c = c4_i_a - 1;
      c4_j_a = c4_jp1j;
      c4_g_b = c4_d_c;
      c4_loop_ub = c4_j_a + c4_g_b;
      for (c4_i = c4_b_jp1j; c4_i <= c4_loop_ub; c4_i = c4_i + 1) {
        c4_b_i = c4_i;
        c4_f_x = c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_b_i), 1, 16, 1, 0) - 1];
        c4_y = c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_jj), 1, 16, 1, 0) - 1];
        c4_g_x = c4_f_x;
        c4_b_y = c4_y;
        c4_z = c4_g_x / c4_b_y;
        c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_b_i), 1, 16, 1, 0) - 1] = c4_z;
      }
    } else {
      *c4_info = c4_b_j;
    }

    c4_h_b = c4_b_j;
    c4_e_c = 4 - c4_h_b;
    c4_k_a = c4_jj;
    c4_f_c = c4_k_a + 4;
    c4_l_a = c4_jj;
    c4_g_c = c4_l_a + 5;
    c4_m = c4_mmj;
    c4_n = c4_e_c;
    c4_c_ix0 = c4_jp1j;
    c4_c_iy0 = c4_f_c;
    for (c4_i276 = 0; c4_i276 < 16; c4_i276 = c4_i276 + 1) {
      c4_d_A[c4_i276] = c4_b_A[c4_i276];
    }

    c4_ia0 = c4_g_c;
    for (c4_i277 = 0; c4_i277 < 16; c4_i277 = c4_i277 + 1) {
      c4_b_A[c4_i277] = c4_d_A[c4_i277];
    }

    c4_b_m = c4_m;
    c4_b_n = c4_n;
    c4_d_ix0 = c4_c_ix0;
    c4_d_iy0 = c4_c_iy0;
    for (c4_i278 = 0; c4_i278 < 16; c4_i278 = c4_i278 + 1) {
      c4_e_A[c4_i278] = c4_b_A[c4_i278];
    }

    c4_b_ia0 = c4_ia0;
    for (c4_i279 = 0; c4_i279 < 16; c4_i279 = c4_i279 + 1) {
      c4_b_A[c4_i279] = c4_e_A[c4_i279];
    }

    c4_c_m = c4_b_m;
    c4_c_n = c4_b_n;
    c4_e_ix0 = c4_d_ix0;
    c4_e_iy0 = c4_d_iy0;
    for (c4_i280 = 0; c4_i280 < 16; c4_i280 = c4_i280 + 1) {
      c4_f_A[c4_i280] = c4_b_A[c4_i280];
    }

    c4_c_ia0 = c4_b_ia0;
    for (c4_i281 = 0; c4_i281 < 16; c4_i281 = c4_i281 + 1) {
      c4_b_A[c4_i281] = c4_f_A[c4_i281];
    }

    if ((real_T)c4_c_m < 1.0) {
    } else if ((real_T)c4_c_n < 1.0) {
    } else {
      for (c4_i282 = 0; c4_i282 < 16; c4_i282 = c4_i282 + 1) {
        c4_g_A[c4_i282] = c4_b_A[c4_i282];
      }

      c4_ceval_xger(chartInstance, c4_c_m, c4_c_n, -1.0, c4_e_ix0, 1, c4_e_iy0,
                    4, c4_g_A, c4_c_ia0, 4, c4_b_A);
      goto label_1;
    }

   label_1:
    ;
  }

  if ((real_T)*c4_info == 0.0) {
    if (!(c4_b_A[15] != 0.0)) {
      *c4_info = 4;
      return;
    }
  }
}

static int32_T c4_eml_ixamax(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[16], int32_T c4_ix0)
{
  int32_T c4_b_n;
  int32_T c4_i283;
  real_T c4_b_x[16];
  int32_T c4_b_ix0;
  int32_T c4_i284;
  real_T c4_c_x[16];
  c4_b_n = c4_n;
  for (c4_i283 = 0; c4_i283 < 16; c4_i283 = c4_i283 + 1) {
    c4_b_x[c4_i283] = c4_x[c4_i283];
  }

  c4_b_ix0 = c4_ix0;
  for (c4_i284 = 0; c4_i284 < 16; c4_i284 = c4_i284 + 1) {
    c4_c_x[c4_i284] = c4_b_x[c4_i284];
  }

  return c4_ceval_ixamax(chartInstance, c4_b_n, c4_c_x, c4_b_ix0, 1);
}

static int32_T c4_ceval_ixamax(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[16], int32_T c4_ix0
  , int32_T c4_incx)
{
  return idamax32(&c4_n, &c4_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c4_ix0), 1, 16, 1, 0) - 1], &
                  c4_incx);
}

static void c4_ceval_xswap(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[16], int32_T c4_ix0,
  int32_T c4_incx, int32_T c4_iy0, int32_T c4_incy, real_T c4_b_x[16])
{
  int32_T c4_i285;

  /* Empty Loop. */
  for (c4_i285 = 0; c4_i285 < 16; c4_i285 = c4_i285 + 1) {
    c4_b_x[c4_i285] = c4_x[c4_i285];
  }

  dswap32(&c4_n, &c4_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c4_ix0), 1, 16, 1, 0) - 1], &c4_incx
          , &c4_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
            "", (real_T)c4_iy0), 1, 16, 1, 0) - 1], &c4_incy);
}

static void c4_ceval_xger(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  int32_T c4_m, int32_T c4_n, real_T c4_alpha1,
  int32_T c4_ix0, int32_T c4_incx, int32_T c4_iy0, int32_T c4_incy, real_T c4_A
  [16], int32_T c4_ia0, int32_T c4_lda, real_T c4_b_A[16]
  )
{
  int32_T c4_i286;
  for (c4_i286 = 0; c4_i286 < 16; c4_i286 = c4_i286 + 1) {
    c4_b_A[c4_i286] = c4_A[c4_i286];
  }

  dger32(&c4_m, &c4_n, &c4_alpha1, &c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c4_ix0), 1, 16, 1,
          0) - 1], &c4_incx, &c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_iy0), 1, 16, 1, 0) - 1], &
         c4_incy, &c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_ia0), 1, 16, 1, 0) - 1], &c4_lda);
}

static void c4_eml_warning(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
  int32_T c4_i287;
  static char_T c4_cv2[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 's', 'i', 'n',
    'g', 'u', 'l', 'a', 'r', 'M', 'a', 't', 'r', 'i', 'x'
  };

  char_T c4_u[21];
  const mxArray *c4_y = NULL;
  int32_T c4_i288;
  static char_T c4_cv3[40] = { 'M', 'a', 't', 'r', 'i', 'x', ' ', 'i', 's', ' ',
    's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', ' ', 't', 'o'
    , ' ', 'w', 'o', 'r', 'k', 'i', 'n', 'g', ' ', 'p', 'r', 'e', 'c', 'i', 's',
    'i', 'o', 'n', '.' };

  char_T c4_b_u[40];
  const mxArray *c4_b_y = NULL;
  for (c4_i287 = 0; c4_i287 < 21; c4_i287 = c4_i287 + 1) {
    c4_u[c4_i287] = c4_cv2[c4_i287];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 21));
  for (c4_i288 = 0; c4_i288 < 40; c4_i288 = c4_i288 + 1) {
    c4_b_u[c4_i288] = c4_cv3[c4_i288];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
  sf_mex_call_debug("warning", 0U, 2U, 14, c4_y, 14, c4_b_y);
}

static void c4_b_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c4_eml_xtrsm(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_A[16], real_T c4_B[16], real_T c4_b_B[16]
  )
{
  int32_T c4_i289;
  int32_T c4_i290;
  real_T c4_b_A[16];
  int32_T c4_i291;
  real_T c4_c_B[16];
  int32_T c4_i292;
  int32_T c4_i293;
  real_T c4_c_A[16];
  int32_T c4_i294;
  real_T c4_d_B[16];
  int32_T c4_i295;
  int32_T c4_j;
  int32_T c4_b_j;
  int32_T c4_a;
  int32_T c4_c;
  int32_T c4_b;
  int32_T c4_b_c;
  int32_T c4_b_b;
  int32_T c4_jBcol;
  int32_T c4_k;
  int32_T c4_b_k;
  int32_T c4_b_a;
  int32_T c4_c_c;
  int32_T c4_c_b;
  int32_T c4_d_c;
  int32_T c4_d_b;
  int32_T c4_kAcol;
  int32_T c4_c_a;
  int32_T c4_e_b;
  int32_T c4_e_c;
  int32_T c4_d_a;
  int32_T c4_i296;
  int32_T c4_i;
  int32_T c4_b_i;
  int32_T c4_e_a;
  int32_T c4_f_b;
  int32_T c4_f_c;
  int32_T c4_f_a;
  int32_T c4_g_b;
  int32_T c4_g_c;
  int32_T c4_g_a;
  int32_T c4_h_b;
  int32_T c4_h_c;
  int32_T c4_h_a;
  int32_T c4_i_b;
  int32_T c4_i_c;
  for (c4_i289 = 0; c4_i289 < 16; c4_i289 = c4_i289 + 1) {
    c4_b_B[c4_i289] = c4_B[c4_i289];
  }

  for (c4_i290 = 0; c4_i290 < 16; c4_i290 = c4_i290 + 1) {
    c4_b_A[c4_i290] = c4_A[c4_i290];
  }

  for (c4_i291 = 0; c4_i291 < 16; c4_i291 = c4_i291 + 1) {
    c4_c_B[c4_i291] = c4_b_B[c4_i291];
  }

  for (c4_i292 = 0; c4_i292 < 16; c4_i292 = c4_i292 + 1) {
    c4_b_B[c4_i292] = c4_c_B[c4_i292];
  }

  for (c4_i293 = 0; c4_i293 < 16; c4_i293 = c4_i293 + 1) {
    c4_c_A[c4_i293] = c4_b_A[c4_i293];
  }

  for (c4_i294 = 0; c4_i294 < 16; c4_i294 = c4_i294 + 1) {
    c4_d_B[c4_i294] = c4_b_B[c4_i294];
  }

  for (c4_i295 = 0; c4_i295 < 16; c4_i295 = c4_i295 + 1) {
    c4_b_B[c4_i295] = c4_d_B[c4_i295];
  }

  c4_c_eml_scalar_eg(chartInstance);
  for (c4_j = 1; c4_j <= 4; c4_j = c4_j + 1) {
    c4_b_j = c4_j;
    c4_a = c4_b_j;
    c4_c = c4_a - 1;
    c4_b = c4_c;
    c4_b_c = c4_b << 2;
    c4_b_b = c4_b_c;
    c4_jBcol = c4_b_b;
    for (c4_k = 1; c4_k <= 4; c4_k = c4_k + 1) {
      c4_b_k = c4_k;
      c4_b_a = c4_b_k;
      c4_c_c = c4_b_a - 1;
      c4_c_b = c4_c_c;
      c4_d_c = c4_c_b << 2;
      c4_d_b = c4_d_c;
      c4_kAcol = c4_d_b;
      c4_c_a = c4_b_k;
      c4_e_b = c4_jBcol;
      c4_e_c = c4_c_a + c4_e_b;
      if (c4_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_e_c), 1, 16, 1, 0) - 1] != 0.0) {
        c4_d_a = c4_b_k;
        c4_i296 = c4_d_a + 1;
        for (c4_i = c4_i296; c4_i <= 4; c4_i = c4_i + 1) {
          c4_b_i = c4_i;
          c4_e_a = c4_b_i;
          c4_f_b = c4_jBcol;
          c4_f_c = c4_e_a + c4_f_b;
          c4_f_a = c4_b_i;
          c4_g_b = c4_jBcol;
          c4_g_c = c4_f_a + c4_g_b;
          c4_g_a = c4_b_k;
          c4_h_b = c4_jBcol;
          c4_h_c = c4_g_a + c4_h_b;
          c4_h_a = c4_b_i;
          c4_i_b = c4_kAcol;
          c4_i_c = c4_h_a + c4_i_b;
          c4_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_f_c), 1, 16, 1, 0) - 1] = c4_b_B[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_g_c), 1, 16, 1, 0) - 1] - c4_b_B[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_h_c), 1, 16, 1, 0) - 1] * c4_c_A[
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_i_c), 1, 16, 1, 0) - 1];
        }
      }
    }
  }
}

static void c4_c_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c4_eml_blas_xtrsm(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_m, int32_T c4_n, real_T c4_alpha1,
  real_T c4_A[16], int32_T c4_ia0, int32_T c4_lda, real_T c4_B[16], int32_T
  c4_ib0, int32_T c4_ldb, real_T c4_b_B[16])
{
  int32_T c4_i297;
  int32_T c4_b_m;
  int32_T c4_b_n;
  real_T c4_b_alpha1;
  int32_T c4_i298;
  real_T c4_b_A[16];
  int32_T c4_b_ia0;
  int32_T c4_b_lda;
  int32_T c4_i299;
  real_T c4_c_B[16];
  int32_T c4_b_ib0;
  int32_T c4_b_ldb;
  int32_T c4_i300;
  boolean_T c4_NON_UNIT_ALPHA;
  int32_T c4_a;
  int32_T c4_Aoffset;
  int32_T c4_b_a;
  int32_T c4_Boffset;
  int32_T c4_loop_ub;
  int32_T c4_j;
  int32_T c4_b_j;
  int32_T c4_c_a;
  int32_T c4_c;
  int32_T c4_d_a;
  int32_T c4_b;
  int32_T c4_b_c;
  int32_T c4_e_a;
  int32_T c4_b_b;
  int32_T c4_jBcol;
  int32_T c4_b_loop_ub;
  int32_T c4_i;
  int32_T c4_b_i;
  int32_T c4_f_a;
  int32_T c4_c_b;
  int32_T c4_c_c;
  int32_T c4_c_loop_ub;
  int32_T c4_c_j;
  int32_T c4_g_a;
  int32_T c4_d_c;
  int32_T c4_h_a;
  int32_T c4_d_b;
  int32_T c4_e_c;
  int32_T c4_i_a;
  int32_T c4_e_b;
  int32_T c4_d_loop_ub;
  int32_T c4_c_i;
  int32_T c4_j_a;
  int32_T c4_f_b;
  int32_T c4_f_c;
  int32_T c4_k_a;
  int32_T c4_g_b;
  int32_T c4_g_c;
  int32_T c4_c_m;
  int32_T c4_k;
  int32_T c4_b_k;
  int32_T c4_l_a;
  int32_T c4_h_c;
  int32_T c4_m_a;
  int32_T c4_h_b;
  int32_T c4_i_c;
  int32_T c4_n_a;
  int32_T c4_i_b;
  int32_T c4_kAcol;
  int32_T c4_o_a;
  int32_T c4_j_b;
  int32_T c4_j_c;
  int32_T c4_p_a;
  int32_T c4_k_b;
  int32_T c4_k_c;
  int32_T c4_q_a;
  int32_T c4_l_b;
  int32_T c4_l_c;
  int32_T c4_r_a;
  int32_T c4_m_b;
  int32_T c4_m_c;
  real_T c4_x;
  real_T c4_y;
  real_T c4_b_x;
  real_T c4_b_y;
  real_T c4_z;
  int32_T c4_s_a;
  int32_T c4_e_loop_ub;
  int32_T c4_d_i;
  int32_T c4_t_a;
  int32_T c4_n_b;
  int32_T c4_n_c;
  int32_T c4_u_a;
  int32_T c4_o_b;
  int32_T c4_o_c;
  int32_T c4_v_a;
  int32_T c4_p_b;
  int32_T c4_p_c;
  int32_T c4_w_a;
  int32_T c4_q_b;
  int32_T c4_q_c;
  for (c4_i297 = 0; c4_i297 < 16; c4_i297 = c4_i297 + 1) {
    c4_b_B[c4_i297] = c4_B[c4_i297];
  }

  c4_b_m = c4_m;
  c4_b_n = c4_n;
  c4_b_alpha1 = c4_alpha1;
  for (c4_i298 = 0; c4_i298 < 16; c4_i298 = c4_i298 + 1) {
    c4_b_A[c4_i298] = c4_A[c4_i298];
  }

  c4_b_ia0 = c4_ia0;
  c4_b_lda = c4_lda;
  for (c4_i299 = 0; c4_i299 < 16; c4_i299 = c4_i299 + 1) {
    c4_c_B[c4_i299] = c4_b_B[c4_i299];
  }

  c4_b_ib0 = c4_ib0;
  c4_b_ldb = c4_ldb;
  for (c4_i300 = 0; c4_i300 < 16; c4_i300 = c4_i300 + 1) {
    c4_b_B[c4_i300] = c4_c_B[c4_i300];
  }

  c4_NON_UNIT_ALPHA = (c4_b_alpha1 != 1.0);
  if ((real_T)c4_b_n == 0.0) {
  } else {
    c4_c_eml_scalar_eg(chartInstance);
    c4_a = c4_b_ia0;
    c4_Aoffset = c4_a - 1;
    c4_b_a = c4_b_ib0;
    c4_Boffset = c4_b_a - 1;
    if (c4_b_alpha1 == 0.0) {
      c4_loop_ub = c4_b_n;
      for (c4_j = 1; c4_j <= c4_loop_ub; c4_j = c4_j + 1) {
        c4_b_j = c4_j;
        c4_c_a = c4_b_j;
        c4_c = c4_c_a - 1;
        c4_d_a = c4_b_ldb;
        c4_b = c4_c;
        c4_b_c = c4_d_a * c4_b;
        c4_e_a = c4_Boffset;
        c4_b_b = c4_b_c;
        c4_jBcol = c4_e_a + c4_b_b;
        c4_b_loop_ub = c4_b_m;
        for (c4_i = 1; c4_i <= c4_b_loop_ub; c4_i = c4_i + 1) {
          c4_b_i = c4_i;
          c4_f_a = c4_b_i;
          c4_c_b = c4_jBcol;
          c4_c_c = c4_f_a + c4_c_b;
          c4_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_c_c), 1, 16, 1, 0) - 1] = 0.0;
        }
      }
    } else {
      c4_c_loop_ub = c4_b_n;
      for (c4_c_j = 1; c4_c_j <= c4_c_loop_ub; c4_c_j = c4_c_j + 1) {
        c4_b_j = c4_c_j;
        c4_g_a = c4_b_j;
        c4_d_c = c4_g_a - 1;
        c4_h_a = c4_b_ldb;
        c4_d_b = c4_d_c;
        c4_e_c = c4_h_a * c4_d_b;
        c4_i_a = c4_Boffset;
        c4_e_b = c4_e_c;
        c4_jBcol = c4_i_a + c4_e_b;
        if (c4_NON_UNIT_ALPHA) {
          c4_d_loop_ub = c4_b_m;
          for (c4_c_i = 1; c4_c_i <= c4_d_loop_ub; c4_c_i = c4_c_i + 1) {
            c4_b_i = c4_c_i;
            c4_j_a = c4_b_i;
            c4_f_b = c4_jBcol;
            c4_f_c = c4_j_a + c4_f_b;
            c4_k_a = c4_b_i;
            c4_g_b = c4_jBcol;
            c4_g_c = c4_k_a + c4_g_b;
            c4_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c4_f_c), 1, 16, 1, 0) - 1] = c4_b_alpha1 * c4_b_B[
              _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c4_g_c), 1, 16, 1, 0) - 1];
          }
        }

        c4_c_m = c4_b_m;
        for (c4_k = c4_c_m; c4_k > 0; c4_k = c4_k + -1) {
          c4_b_k = c4_k;
          c4_l_a = c4_b_k;
          c4_h_c = c4_l_a - 1;
          c4_m_a = c4_b_lda;
          c4_h_b = c4_h_c;
          c4_i_c = c4_m_a * c4_h_b;
          c4_n_a = c4_Aoffset;
          c4_i_b = c4_i_c;
          c4_kAcol = c4_n_a + c4_i_b;
          c4_o_a = c4_b_k;
          c4_j_b = c4_jBcol;
          c4_j_c = c4_o_a + c4_j_b;
          if (c4_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
               ("", (real_T)c4_j_c), 1, 16, 1, 0) - 1] != 0.0) {
            c4_p_a = c4_b_k;
            c4_k_b = c4_jBcol;
            c4_k_c = c4_p_a + c4_k_b;
            c4_q_a = c4_b_k;
            c4_l_b = c4_jBcol;
            c4_l_c = c4_q_a + c4_l_b;
            c4_r_a = c4_b_k;
            c4_m_b = c4_kAcol;
            c4_m_c = c4_r_a + c4_m_b;
            c4_x = c4_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c4_l_c), 1, 16, 1, 0) - 1];
            c4_y = c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c4_m_c), 1, 16, 1, 0) - 1];
            c4_b_x = c4_x;
            c4_b_y = c4_y;
            c4_z = c4_b_x / c4_b_y;
            c4_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c4_k_c), 1, 16, 1, 0) - 1] = c4_z;
            c4_s_a = c4_b_k;
            c4_e_loop_ub = c4_s_a - 1;
            for (c4_d_i = 1; c4_d_i <= c4_e_loop_ub; c4_d_i = c4_d_i + 1) {
              c4_b_i = c4_d_i;
              c4_t_a = c4_b_i;
              c4_n_b = c4_jBcol;
              c4_n_c = c4_t_a + c4_n_b;
              c4_u_a = c4_b_i;
              c4_o_b = c4_jBcol;
              c4_o_c = c4_u_a + c4_o_b;
              c4_v_a = c4_b_k;
              c4_p_b = c4_jBcol;
              c4_p_c = c4_v_a + c4_p_b;
              c4_w_a = c4_b_i;
              c4_q_b = c4_kAcol;
              c4_q_c = c4_w_a + c4_q_b;
              c4_b_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                ("", (real_T)c4_n_c), 1, 16, 1, 0) - 1] = c4_b_B[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c4_o_c), 1, 16, 1, 0) - 1] - c4_b_B[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c4_p_c), 1, 16, 1, 0) - 1] * c4_b_A[
                _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c4_q_c), 1, 16, 1, 0) - 1];
            }
          }
        }
      }
    }
  }
}

static void c4_d_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static real_T c4_atan2(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_y, real_T c4_x)
{
  real_T c4_b_y;
  real_T c4_b_x;
  c4_eml_scalar_eg(chartInstance);
  c4_b_y = c4_y;
  c4_b_x = c4_x;
  return muDoubleScalarAtan2(c4_b_y, c4_b_x);
}

static boolean_T c4_isInRange(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_x, real_T c4_xmin, real_T c4_xmax)
{
  boolean_T c4_isIn;
  uint32_T c4_debug_family_var_map[6];
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 1.0;
  real_T c4_A;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_d_x;
  real_T c4_y;
  real_T c4_a;
  boolean_T c4_b0;
  boolean_T c4_b1;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c4_b_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c4_x, c4_e_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c4_xmin, c4_e_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c4_xmax, c4_e_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c4_isIn, c4_h_sf_marshall, 5U);
  CV_SCRIPT_FCN(0, 1);
  _SFD_SCRIPT_CALL(0, 141);
  c4_A = c4_x;
  c4_b_x = c4_A;
  c4_c_x = c4_b_x;
  c4_d_x = c4_c_x;
  c4_y = c4_d_x / 3.1415926535897931;
  c4_a = c4_y;
  c4_x = c4_a * 180.0;
  _SFD_SCRIPT_CALL(0, 142);
  c4_b0 = (c4_x >= c4_xmin);
  c4_b1 = (c4_x <= c4_xmax);
  c4_isIn = (c4_b0 && c4_b1);
  _SFD_SCRIPT_CALL(0, -142);
  sf_debug_symbol_scope_pop();
  return c4_isIn;
}

static void c4_expWre(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c4_kx[6], real_T c4_theta, real_T c4_g[16])
{
  uint32_T c4_debug_family_var_map[9];
  static const char *c4_sv2[9] = { "v", "w", "R", "p", "nargin", "nargout", "kx",
    "theta", "g" };

  real_T c4_v[3];
  real_T c4_w[3];
  real_T c4_R[9];
  real_T c4_p[3];
  real_T c4_nargin = 2.0;
  real_T c4_nargout = 1.0;
  int32_T c4_i301;
  int32_T c4_i302;
  real_T c4_dv23[9];
  int32_T c4_i303;
  int32_T c4_i304;
  real_T c4_a[3];
  real_T c4_b;
  int32_T c4_i305;
  int32_T c4_i306;
  real_T c4_b_w[3];
  real_T c4_dv24[9];
  int32_T c4_i307;
  real_T c4_dv25[9];
  int32_T c4_i308;
  real_T c4_b_a[9];
  int32_T c4_i309;
  real_T c4_c_w[3];
  int32_T c4_i310;
  real_T c4_b_v[3];
  real_T c4_b_b[3];
  int32_T c4_i311;
  real_T c4_A[9];
  int32_T c4_i312;
  real_T c4_B[3];
  int32_T c4_i313;
  real_T c4_b_A[9];
  int32_T c4_i314;
  real_T c4_b_B[3];
  int32_T c4_i315;
  real_T c4_c_A[9];
  int32_T c4_i316;
  real_T c4_c_B[3];
  int32_T c4_i317;
  real_T c4_y[3];
  int32_T c4_i318;
  int32_T c4_i319;
  int32_T c4_i320;
  real_T c4_c_a[3];
  int32_T c4_i321;
  real_T c4_c_b[3];
  int32_T c4_i322;
  int32_T c4_i323;
  int32_T c4_i324;
  real_T c4_b_y[9];
  int32_T c4_i325;
  real_T c4_d_a[9];
  int32_T c4_i326;
  real_T c4_d_b[3];
  int32_T c4_i327;
  real_T c4_d_A[9];
  int32_T c4_i328;
  real_T c4_d_B[3];
  int32_T c4_i329;
  real_T c4_e_A[9];
  int32_T c4_i330;
  real_T c4_e_B[3];
  int32_T c4_i331;
  real_T c4_f_A[9];
  int32_T c4_i332;
  real_T c4_f_B[3];
  int32_T c4_i333;
  real_T c4_c_y[3];
  int32_T c4_i334;
  int32_T c4_i335;
  int32_T c4_i336;
  real_T c4_e_a[3];
  real_T c4_e_b;
  int32_T c4_i337;
  real_T c4_d_y[3];
  int32_T c4_i338;
  int32_T c4_i339;
  int32_T c4_i340;
  int32_T c4_i341;
  int32_T c4_i342;
  int32_T c4_i343;
  int32_T c4_i344;
  int32_T c4_i345;
  static real_T c4_dv26[4] = { 0.0, 0.0, 0.0, 1.0 };

  sf_debug_symbol_scope_push_eml(0U, 9U, 9U, c4_sv2, c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_v, c4_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c4_w, c4_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_R, c4_c_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c4_p, c4_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c4_kx, c4_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c4_theta, c4_e_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c4_g, c4_g_sf_marshall, 8U);
  CV_SCRIPT_FCN(1, 0);

  /*  exponential of the wrench  */
  _SFD_SCRIPT_CALL(1, 5);
  CV_SCRIPT_IF(1, 0, c4_length(chartInstance) != 6.0);
  _SFD_SCRIPT_CALL(1, 9);
  for (c4_i301 = 0; c4_i301 < 3; c4_i301 = c4_i301 + 1) {
    c4_v[c4_i301] = c4_kx[c4_i301];
  }

  _SFD_SCRIPT_CALL(1, 10);
  for (c4_i302 = 0; c4_i302 < 3; c4_i302 = c4_i302 + 1) {
    c4_w[c4_i302] = c4_kx[c4_i302 + 3];
  }

  _SFD_SCRIPT_CALL(1, 12);
  if (CV_SCRIPT_COND(1, 0, c4_w[0] == 0.0)) {
    if (CV_SCRIPT_COND(1, 1, c4_w[1] == 0.0)) {
      if (CV_SCRIPT_COND(1, 2, c4_w[2] == 0.0)) {
        CV_SCRIPT_MCDC(1, 0, TRUE);
        CV_SCRIPT_IF(1, 1, TRUE);
        _SFD_SCRIPT_CALL(1, 13);
        c4_eye(chartInstance, c4_dv23);
        for (c4_i303 = 0; c4_i303 < 9; c4_i303 = c4_i303 + 1) {
          c4_R[c4_i303] = c4_dv23[c4_i303];
        }

        _SFD_SCRIPT_CALL(1, 14);
        for (c4_i304 = 0; c4_i304 < 3; c4_i304 = c4_i304 + 1) {
          c4_a[c4_i304] = c4_v[c4_i304];
        }

        c4_b = c4_theta;
        for (c4_i305 = 0; c4_i305 < 3; c4_i305 = c4_i305 + 1) {
          c4_p[c4_i305] = c4_a[c4_i305] * c4_b;
        }

        goto label_1;
      } else {
        goto label_2;
      }
    }
  }

 label_2:
  ;
  CV_SCRIPT_MCDC(1, 0, FALSE);
  CV_SCRIPT_IF(1, 1, FALSE);
  _SFD_SCRIPT_CALL(1, 16);
  for (c4_i306 = 0; c4_i306 < 3; c4_i306 = c4_i306 + 1) {
    c4_b_w[c4_i306] = c4_w[c4_i306];
  }

  c4_expRot(chartInstance, c4_b_w, c4_theta, c4_dv24);
  for (c4_i307 = 0; c4_i307 < 9; c4_i307 = c4_i307 + 1) {
    c4_R[c4_i307] = c4_dv24[c4_i307];
  }

  _SFD_SCRIPT_CALL(1, 17);
  c4_eye(chartInstance, c4_dv25);
  for (c4_i308 = 0; c4_i308 < 9; c4_i308 = c4_i308 + 1) {
    c4_b_a[c4_i308] = c4_dv25[c4_i308] - c4_R[c4_i308];
  }

  for (c4_i309 = 0; c4_i309 < 3; c4_i309 = c4_i309 + 1) {
    c4_c_w[c4_i309] = c4_w[c4_i309];
  }

  for (c4_i310 = 0; c4_i310 < 3; c4_i310 = c4_i310 + 1) {
    c4_b_v[c4_i310] = c4_v[c4_i310];
  }

  c4_cross(chartInstance, c4_c_w, c4_b_v, c4_b_b);
  c4_f_eml_scalar_eg(chartInstance);
  c4_f_eml_scalar_eg(chartInstance);
  for (c4_i311 = 0; c4_i311 < 9; c4_i311 = c4_i311 + 1) {
    c4_A[c4_i311] = c4_b_a[c4_i311];
  }

  for (c4_i312 = 0; c4_i312 < 3; c4_i312 = c4_i312 + 1) {
    c4_B[c4_i312] = c4_b_b[c4_i312];
  }

  for (c4_i313 = 0; c4_i313 < 9; c4_i313 = c4_i313 + 1) {
    c4_b_A[c4_i313] = c4_A[c4_i313];
  }

  for (c4_i314 = 0; c4_i314 < 3; c4_i314 = c4_i314 + 1) {
    c4_b_B[c4_i314] = c4_B[c4_i314];
  }

  for (c4_i315 = 0; c4_i315 < 9; c4_i315 = c4_i315 + 1) {
    c4_c_A[c4_i315] = c4_b_A[c4_i315];
  }

  for (c4_i316 = 0; c4_i316 < 3; c4_i316 = c4_i316 + 1) {
    c4_c_B[c4_i316] = c4_b_B[c4_i316];
  }

  for (c4_i317 = 0; c4_i317 < 3; c4_i317 = c4_i317 + 1) {
    c4_y[c4_i317] = 0.0;
    c4_i318 = 0;
    for (c4_i319 = 0; c4_i319 < 3; c4_i319 = c4_i319 + 1) {
      c4_y[c4_i317] = c4_y[c4_i317] + c4_c_A[c4_i318 + c4_i317] * c4_c_B[c4_i319];
      c4_i318 = c4_i318 + 3;
    }
  }

  for (c4_i320 = 0; c4_i320 < 3; c4_i320 = c4_i320 + 1) {
    c4_c_a[c4_i320] = c4_w[c4_i320];
  }

  for (c4_i321 = 0; c4_i321 < 3; c4_i321 = c4_i321 + 1) {
    c4_c_b[c4_i321] = c4_w[c4_i321];
  }

  c4_i322 = 0;
  for (c4_i323 = 0; c4_i323 < 3; c4_i323 = c4_i323 + 1) {
    for (c4_i324 = 0; c4_i324 < 3; c4_i324 = c4_i324 + 1) {
      c4_b_y[c4_i324 + c4_i322] = c4_c_a[c4_i324] * c4_c_b[c4_i323];
    }

    c4_i322 = c4_i322 + 3;
  }

  for (c4_i325 = 0; c4_i325 < 9; c4_i325 = c4_i325 + 1) {
    c4_d_a[c4_i325] = c4_b_y[c4_i325];
  }

  for (c4_i326 = 0; c4_i326 < 3; c4_i326 = c4_i326 + 1) {
    c4_d_b[c4_i326] = c4_v[c4_i326];
  }

  c4_f_eml_scalar_eg(chartInstance);
  c4_f_eml_scalar_eg(chartInstance);
  for (c4_i327 = 0; c4_i327 < 9; c4_i327 = c4_i327 + 1) {
    c4_d_A[c4_i327] = c4_d_a[c4_i327];
  }

  for (c4_i328 = 0; c4_i328 < 3; c4_i328 = c4_i328 + 1) {
    c4_d_B[c4_i328] = c4_d_b[c4_i328];
  }

  for (c4_i329 = 0; c4_i329 < 9; c4_i329 = c4_i329 + 1) {
    c4_e_A[c4_i329] = c4_d_A[c4_i329];
  }

  for (c4_i330 = 0; c4_i330 < 3; c4_i330 = c4_i330 + 1) {
    c4_e_B[c4_i330] = c4_d_B[c4_i330];
  }

  for (c4_i331 = 0; c4_i331 < 9; c4_i331 = c4_i331 + 1) {
    c4_f_A[c4_i331] = c4_e_A[c4_i331];
  }

  for (c4_i332 = 0; c4_i332 < 3; c4_i332 = c4_i332 + 1) {
    c4_f_B[c4_i332] = c4_e_B[c4_i332];
  }

  for (c4_i333 = 0; c4_i333 < 3; c4_i333 = c4_i333 + 1) {
    c4_c_y[c4_i333] = 0.0;
    c4_i334 = 0;
    for (c4_i335 = 0; c4_i335 < 3; c4_i335 = c4_i335 + 1) {
      c4_c_y[c4_i333] = c4_c_y[c4_i333] + c4_f_A[c4_i334 + c4_i333] *
        c4_f_B[c4_i335];
      c4_i334 = c4_i334 + 3;
    }
  }

  for (c4_i336 = 0; c4_i336 < 3; c4_i336 = c4_i336 + 1) {
    c4_e_a[c4_i336] = c4_c_y[c4_i336];
  }

  c4_e_b = c4_theta;
  for (c4_i337 = 0; c4_i337 < 3; c4_i337 = c4_i337 + 1) {
    c4_d_y[c4_i337] = c4_e_a[c4_i337] * c4_e_b;
  }

  for (c4_i338 = 0; c4_i338 < 3; c4_i338 = c4_i338 + 1) {
    c4_p[c4_i338] = c4_y[c4_i338] + c4_d_y[c4_i338];
  }

 label_1:
  ;
  _SFD_SCRIPT_CALL(1, 19);
  c4_i339 = 0;
  c4_i340 = 0;
  for (c4_i341 = 0; c4_i341 < 3; c4_i341 = c4_i341 + 1) {
    for (c4_i342 = 0; c4_i342 < 3; c4_i342 = c4_i342 + 1) {
      c4_g[c4_i342 + c4_i339] = c4_R[c4_i342 + c4_i340];
    }

    c4_i339 = c4_i339 + 4;
    c4_i340 = c4_i340 + 3;
  }

  for (c4_i343 = 0; c4_i343 < 3; c4_i343 = c4_i343 + 1) {
    c4_g[c4_i343 + 12] = c4_p[c4_i343];
  }

  c4_i344 = 0;
  for (c4_i345 = 0; c4_i345 < 4; c4_i345 = c4_i345 + 1) {
    c4_g[c4_i344 + 3] = c4_dv26[c4_i345];
    c4_i344 = c4_i344 + 4;
  }

  _SFD_SCRIPT_CALL(1, -19);
  sf_debug_symbol_scope_pop();
}

static real_T c4_length(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance)
{
  real_T c4_n;
  real_T c4_k;
  real_T c4_b_k;
  c4_n = 0.0;
  c4_k = 1.0;
 label_1:
  ;
  if (c4_k <= 2.0) {
    c4_b_k = c4_k;
    if (6.0 + -5.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c4_b_k), 1, 2, 1, 0) - 1) == 0.0) {
      return 0.0;
    } else {
      if (6.0 + -5.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c4_b_k), 1, 2, 1, 0) - 1) > c4_n) {
        c4_n = 6.0 + -5.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c4_b_k), 1, 2, 1, 0) - 1);
      }

      c4_k = c4_k + 1.0;
      goto label_1;
    }
  }

  return c4_n;
}

static void c4_eye(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                   real_T c4_I[9])
{
  int32_T c4_i346;
  int32_T c4_i;
  int32_T c4_b_i;
  for (c4_i346 = 0; c4_i346 < 9; c4_i346 = c4_i346 + 1) {
    c4_I[c4_i346] = 0.0;
  }

  for (c4_i = 1; c4_i < 4; c4_i = c4_i + 1) {
    c4_b_i = c4_i;
    c4_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_b_i), 1, 3, 1, 0) - 1) + 3 * (
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c4_b_i), 1, 3, 2, 0) - 1)] = 1.0;
  }
}

static void c4_expRot(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c4_w[3], real_T c4_theta, real_T c4_R[9])
{
  uint32_T c4_debug_family_var_map[6];
  real_T c4_wh[9];
  real_T c4_nargin = 2.0;
  real_T c4_nargout = 1.0;
  int32_T c4_i347;
  real_T c4_b_w[3];
  uint32_T c4_b_debug_family_var_map[4];
  real_T c4_b_nargin = 1.0;
  real_T c4_b_nargout = 1.0;
  real_T c4_n;
  real_T c4_k;
  real_T c4_b_k;
  real_T c4_x;
  real_T c4_b_x;
  real_T c4_c_x;
  int32_T c4_i348;
  real_T c4_a[9];
  real_T c4_b;
  int32_T c4_i349;
  real_T c4_y[9];
  int32_T c4_i350;
  real_T c4_b_a[9];
  int32_T c4_i351;
  real_T c4_b_b[9];
  int32_T c4_i352;
  real_T c4_A[9];
  int32_T c4_i353;
  real_T c4_B[9];
  int32_T c4_i354;
  real_T c4_b_A[9];
  int32_T c4_i355;
  real_T c4_b_B[9];
  int32_T c4_i356;
  real_T c4_c_A[9];
  int32_T c4_i357;
  real_T c4_c_B[9];
  int32_T c4_i358;
  int32_T c4_i359;
  int32_T c4_i360;
  real_T c4_b_y[9];
  int32_T c4_i361;
  int32_T c4_i362;
  real_T c4_d_x;
  real_T c4_e_x;
  real_T c4_f_x;
  int32_T c4_i363;
  real_T c4_c_a[9];
  real_T c4_c_b;
  int32_T c4_i364;
  real_T c4_c_y[9];
  real_T c4_dv27[9];
  int32_T c4_i365;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c4_d_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_wh, c4_c_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c4_w, c4_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c4_theta, c4_e_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_R, c4_c_sf_marshall, 5U);
  CV_SCRIPT_FCN(2, 0);

  /*  exponential of the skew matrix */
  /*      if(norm(w)~=1) */
  /*          error('Norm of w must be 1'); */
  /*      end */
  _SFD_SCRIPT_CALL(2, 9);
  for (c4_i347 = 0; c4_i347 < 3; c4_i347 = c4_i347 + 1) {
    c4_b_w[c4_i347] = c4_w[c4_i347];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c4_c_debug_family_names,
    c4_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c4_b_nargin, c4_e_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c4_b_nargout, c4_e_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_b_w, c4_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c4_wh, c4_c_sf_marshall, 3U);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3, 3);
  c4_n = 0.0;
  c4_k = 1.0;
 label_1:
  ;
  if (c4_k <= 2.0) {
    c4_b_k = c4_k;
    if (3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c4_b_k), 1, 2, 1, 0) - 1) == 0.0) {
      c4_n = 0.0;
    } else {
      if (3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c4_b_k), 1, 2, 1, 0) - 1) > c4_n) {
        c4_n = 3.0 + -2.0 * (real_T)(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", c4_b_k), 1, 2, 1, 0) - 1);
      }

      c4_k = c4_k + 1.0;
      goto label_1;
    }
  }

  CV_SCRIPT_IF(3, 0, c4_n != 3.0);

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
  c4_wh[0] = 0.0;
  c4_wh[3] = -c4_b_w[2];
  c4_wh[6] = c4_b_w[1];
  c4_wh[1] = c4_b_w[2];
  c4_wh[4] = 0.0;
  c4_wh[7] = -c4_b_w[0];
  c4_wh[2] = -c4_b_w[1];
  c4_wh[5] = c4_b_w[0];
  c4_wh[8] = 0.0;
  _SFD_SCRIPT_CALL(3, -20);
  sf_debug_symbol_scope_pop();
  _SFD_SCRIPT_CALL(2, 10);
  c4_x = c4_theta;
  c4_b_x = c4_x;
  c4_c_x = c4_b_x;
  c4_b_x = c4_c_x;
  c4_b_x = muDoubleScalarSin(c4_b_x);
  for (c4_i348 = 0; c4_i348 < 9; c4_i348 = c4_i348 + 1) {
    c4_a[c4_i348] = c4_wh[c4_i348];
  }

  c4_b = c4_b_x;
  for (c4_i349 = 0; c4_i349 < 9; c4_i349 = c4_i349 + 1) {
    c4_y[c4_i349] = c4_a[c4_i349] * c4_b;
  }

  for (c4_i350 = 0; c4_i350 < 9; c4_i350 = c4_i350 + 1) {
    c4_b_a[c4_i350] = c4_wh[c4_i350];
  }

  for (c4_i351 = 0; c4_i351 < 9; c4_i351 = c4_i351 + 1) {
    c4_b_b[c4_i351] = c4_wh[c4_i351];
  }

  c4_e_eml_scalar_eg(chartInstance);
  c4_e_eml_scalar_eg(chartInstance);
  for (c4_i352 = 0; c4_i352 < 9; c4_i352 = c4_i352 + 1) {
    c4_A[c4_i352] = c4_b_a[c4_i352];
  }

  for (c4_i353 = 0; c4_i353 < 9; c4_i353 = c4_i353 + 1) {
    c4_B[c4_i353] = c4_b_b[c4_i353];
  }

  for (c4_i354 = 0; c4_i354 < 9; c4_i354 = c4_i354 + 1) {
    c4_b_A[c4_i354] = c4_A[c4_i354];
  }

  for (c4_i355 = 0; c4_i355 < 9; c4_i355 = c4_i355 + 1) {
    c4_b_B[c4_i355] = c4_B[c4_i355];
  }

  for (c4_i356 = 0; c4_i356 < 9; c4_i356 = c4_i356 + 1) {
    c4_c_A[c4_i356] = c4_b_A[c4_i356];
  }

  for (c4_i357 = 0; c4_i357 < 9; c4_i357 = c4_i357 + 1) {
    c4_c_B[c4_i357] = c4_b_B[c4_i357];
  }

  for (c4_i358 = 0; c4_i358 < 3; c4_i358 = c4_i358 + 1) {
    c4_i359 = 0;
    for (c4_i360 = 0; c4_i360 < 3; c4_i360 = c4_i360 + 1) {
      c4_b_y[c4_i359 + c4_i358] = 0.0;
      c4_i361 = 0;
      for (c4_i362 = 0; c4_i362 < 3; c4_i362 = c4_i362 + 1) {
        c4_b_y[c4_i359 + c4_i358] = c4_b_y[c4_i359 + c4_i358] + c4_c_A[c4_i361 +
          c4_i358] * c4_c_B[c4_i362 + c4_i359];
        c4_i361 = c4_i361 + 3;
      }

      c4_i359 = c4_i359 + 3;
    }
  }

  c4_d_x = c4_theta;
  c4_e_x = c4_d_x;
  c4_f_x = c4_e_x;
  c4_e_x = c4_f_x;
  c4_e_x = muDoubleScalarCos(c4_e_x);
  for (c4_i363 = 0; c4_i363 < 9; c4_i363 = c4_i363 + 1) {
    c4_c_a[c4_i363] = c4_b_y[c4_i363];
  }

  c4_c_b = 1.0 - c4_e_x;
  for (c4_i364 = 0; c4_i364 < 9; c4_i364 = c4_i364 + 1) {
    c4_c_y[c4_i364] = c4_c_a[c4_i364] * c4_c_b;
  }

  c4_eye(chartInstance, c4_dv27);
  for (c4_i365 = 0; c4_i365 < 9; c4_i365 = c4_i365 + 1) {
    c4_R[c4_i365] = (c4_dv27[c4_i365] + c4_y[c4_i365]) + c4_c_y[c4_i365];
  }

  _SFD_SCRIPT_CALL(2, -10);
  sf_debug_symbol_scope_pop();
}

static void c4_e_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c4_f_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static void c4_subPro3(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_kx[6], real_T c4_p[4], real_T c4_q[4],
  real_T c4_d[4], real_T c4_theta[2], real_T *c4_Nsol)
{
  uint32_T c4_debug_family_var_map[18];
  static const char *c4_sv3[18] = { "velociy", "w", "r", "u", "v", "up", "vp",
    "dp2", "theta0", "phi", "p", "q", "d", "nargin",
    "nargout", "kx", "theta", "Nsol" };

  real_T c4_velociy[3];
  real_T c4_w[3];
  real_T c4_r[3];
  real_T c4_u[3];
  real_T c4_v[3];
  real_T c4_up[3];
  real_T c4_vp[3];
  real_T c4_dp2;
  real_T c4_theta0;
  real_T c4_phi;
  real_T c4_b_p[3];
  real_T c4_b_q[3];
  real_T c4_b_d[3];
  real_T c4_nargin = 4.0;
  real_T c4_nargout = 2.0;
  int32_T c4_i366;
  int32_T c4_i367;
  int32_T c4_i368;
  int32_T c4_i369;
  int32_T c4_i370;
  int32_T c4_i371;
  int32_T c4_i372;
  real_T c4_b_velociy[3];
  int32_T c4_i373;
  real_T c4_b_w[3];
  real_T c4_dv28[3];
  int32_T c4_i374;
  int32_T c4_i375;
  int32_T c4_i376;
  int32_T c4_i377;
  real_T c4_a[3];
  int32_T c4_i378;
  real_T c4_b[3];
  int32_T c4_i379;
  real_T c4_x[3];
  int32_T c4_i380;
  real_T c4_y[3];
  int32_T c4_i381;
  real_T c4_b_x[3];
  int32_T c4_i382;
  real_T c4_b_y[3];
  int32_T c4_i383;
  real_T c4_c_x[3];
  int32_T c4_i384;
  real_T c4_c_y[3];
  int32_T c4_i385;
  real_T c4_d_x[3];
  int32_T c4_i386;
  real_T c4_d_y[3];
  real_T c4_e_y;
  int32_T c4_i387;
  real_T c4_b_a[3];
  real_T c4_b_b;
  int32_T c4_i388;
  real_T c4_f_y[3];
  int32_T c4_i389;
  int32_T c4_i390;
  real_T c4_c_a[3];
  int32_T c4_i391;
  real_T c4_c_b[3];
  int32_T c4_i392;
  real_T c4_e_x[3];
  int32_T c4_i393;
  real_T c4_g_y[3];
  int32_T c4_i394;
  real_T c4_f_x[3];
  int32_T c4_i395;
  real_T c4_h_y[3];
  int32_T c4_i396;
  real_T c4_g_x[3];
  int32_T c4_i397;
  real_T c4_i_y[3];
  int32_T c4_i398;
  real_T c4_h_x[3];
  int32_T c4_i399;
  real_T c4_j_y[3];
  real_T c4_k_y;
  int32_T c4_i400;
  real_T c4_d_a[3];
  real_T c4_d_b;
  int32_T c4_i401;
  real_T c4_l_y[3];
  int32_T c4_i402;
  int32_T c4_i403;
  real_T c4_e_a[3];
  int32_T c4_i404;
  real_T c4_e_b[3];
  int32_T c4_i405;
  real_T c4_i_x[3];
  int32_T c4_i406;
  real_T c4_m_y[3];
  int32_T c4_i407;
  real_T c4_j_x[3];
  int32_T c4_i408;
  real_T c4_n_y[3];
  int32_T c4_i409;
  real_T c4_k_x[3];
  int32_T c4_i410;
  real_T c4_o_y[3];
  int32_T c4_i411;
  real_T c4_l_x[3];
  int32_T c4_i412;
  real_T c4_p_y[3];
  real_T c4_q_y;
  int32_T c4_i413;
  real_T c4_f_a[3];
  int32_T c4_i414;
  real_T c4_f_b[3];
  int32_T c4_i415;
  real_T c4_m_x[3];
  int32_T c4_i416;
  real_T c4_r_y[3];
  int32_T c4_i417;
  real_T c4_n_x[3];
  int32_T c4_i418;
  real_T c4_s_y[3];
  int32_T c4_i419;
  real_T c4_o_x[3];
  int32_T c4_i420;
  real_T c4_t_y[3];
  int32_T c4_i421;
  real_T c4_p_x[3];
  int32_T c4_i422;
  real_T c4_u_y[3];
  real_T c4_v_y;
  int32_T c4_i423;
  real_T c4_g_a[3];
  int32_T c4_i424;
  real_T c4_b_up[3];
  int32_T c4_i425;
  real_T c4_b_vp[3];
  real_T c4_g_b[3];
  int32_T c4_i426;
  real_T c4_q_x[3];
  int32_T c4_i427;
  real_T c4_w_y[3];
  int32_T c4_i428;
  real_T c4_r_x[3];
  int32_T c4_i429;
  real_T c4_x_y[3];
  int32_T c4_i430;
  real_T c4_s_x[3];
  int32_T c4_i431;
  real_T c4_y_y[3];
  int32_T c4_i432;
  real_T c4_t_x[3];
  int32_T c4_i433;
  real_T c4_ab_y[3];
  real_T c4_bb_y;
  int32_T c4_i434;
  real_T c4_h_a[3];
  int32_T c4_i435;
  real_T c4_h_b[3];
  int32_T c4_i436;
  real_T c4_u_x[3];
  int32_T c4_i437;
  real_T c4_cb_y[3];
  int32_T c4_i438;
  real_T c4_v_x[3];
  int32_T c4_i439;
  real_T c4_db_y[3];
  int32_T c4_i440;
  real_T c4_w_x[3];
  int32_T c4_i441;
  real_T c4_eb_y[3];
  int32_T c4_i442;
  real_T c4_x_x[3];
  int32_T c4_i443;
  real_T c4_fb_y[3];
  real_T c4_gb_y;
  int32_T c4_i444;
  real_T c4_i_a[3];
  int32_T c4_i445;
  real_T c4_i_b[3];
  int32_T c4_i446;
  real_T c4_y_x[3];
  int32_T c4_i447;
  real_T c4_hb_y[3];
  int32_T c4_i448;
  real_T c4_ab_x[3];
  int32_T c4_i449;
  real_T c4_ib_y[3];
  int32_T c4_i450;
  real_T c4_bb_x[3];
  int32_T c4_i451;
  real_T c4_jb_y[3];
  int32_T c4_i452;
  real_T c4_cb_x[3];
  int32_T c4_i453;
  real_T c4_kb_y[3];
  real_T c4_lb_y;
  int32_T c4_i454;
  real_T c4_j_a[3];
  int32_T c4_i455;
  real_T c4_j_b[3];
  int32_T c4_i456;
  real_T c4_db_x[3];
  int32_T c4_i457;
  real_T c4_mb_y[3];
  int32_T c4_i458;
  real_T c4_eb_x[3];
  int32_T c4_i459;
  real_T c4_nb_y[3];
  int32_T c4_i460;
  real_T c4_fb_x[3];
  int32_T c4_i461;
  real_T c4_ob_y[3];
  int32_T c4_i462;
  real_T c4_gb_x[3];
  int32_T c4_i463;
  real_T c4_pb_y[3];
  real_T c4_qb_y;
  int32_T c4_i464;
  real_T c4_c_up[3];
  real_T c4_k_b;
  real_T c4_rb_y;
  real_T c4_k_a;
  int32_T c4_i465;
  real_T c4_c_vp[3];
  real_T c4_l_b;
  real_T c4_sb_y;
  real_T c4_A;
  real_T c4_B;
  real_T c4_hb_x;
  real_T c4_tb_y;
  real_T c4_ib_x;
  real_T c4_ub_y;
  real_T c4_jb_x;
  real_T c4_vb_y;
  real_T c4_wb_y;
  real_T c4_kb_x;
  real_T c4_lb_x;
  sf_debug_symbol_scope_push_eml(0U, 18U, 21U, c4_sv3, c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_velociy, c4_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c4_w, c4_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_r, c4_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c4_u, c4_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c4_v, c4_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_up, c4_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c4_vp, c4_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c4_dp2, c4_e_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c4_theta0, c4_e_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c4_phi, c4_e_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(c4_b_p, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_q, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(c4_b_d, c4_d_sf_marshall, MAX_uint32_T);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(c4_kx, c4_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(c4_p, c4_j_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(c4_q, c4_j_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(c4_d, c4_j_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(c4_theta, c4_i_sf_marshall, 16U);
  sf_debug_symbol_scope_add_eml(c4_Nsol, c4_e_sf_marshall, 17U);
  CV_SCRIPT_FCN(4, 0);
  _SFD_SCRIPT_CALL(4, 2);
  for (c4_i366 = 0; c4_i366 < 2; c4_i366 = c4_i366 + 1) {
    c4_theta[c4_i366] = 0.0;
  }

  _SFD_SCRIPT_CALL(4, 3);
  for (c4_i367 = 0; c4_i367 < 3; c4_i367 = c4_i367 + 1) {
    c4_b_p[c4_i367] = c4_p[c4_i367];
  }

  sf_debug_symbol_switch(10U, 10U);

  /*  col vector */
  _SFD_SCRIPT_CALL(4, 4);
  for (c4_i368 = 0; c4_i368 < 3; c4_i368 = c4_i368 + 1) {
    c4_b_q[c4_i368] = c4_q[c4_i368];
  }

  sf_debug_symbol_switch(11U, 11U);

  /*  col vector */
  _SFD_SCRIPT_CALL(4, 5);
  for (c4_i369 = 0; c4_i369 < 3; c4_i369 = c4_i369 + 1) {
    c4_b_d[c4_i369] = c4_d[c4_i369];
  }

  sf_debug_symbol_switch(12U, 12U);

  /*  col vector. */
  _SFD_SCRIPT_CALL(4, 7);
  for (c4_i370 = 0; c4_i370 < 3; c4_i370 = c4_i370 + 1) {
    c4_velociy[c4_i370] = c4_kx[c4_i370];
  }

  _SFD_SCRIPT_CALL(4, 8);
  for (c4_i371 = 0; c4_i371 < 3; c4_i371 = c4_i371 + 1) {
    c4_w[c4_i371] = c4_kx[c4_i371 + 3];
  }

  /*  rotation axis */
  _SFD_SCRIPT_CALL(4, 9);
  for (c4_i372 = 0; c4_i372 < 3; c4_i372 = c4_i372 + 1) {
    c4_b_velociy[c4_i372] = c4_velociy[c4_i372];
  }

  for (c4_i373 = 0; c4_i373 < 3; c4_i373 = c4_i373 + 1) {
    c4_b_w[c4_i373] = c4_w[c4_i373];
  }

  c4_cross(chartInstance, c4_b_velociy, c4_b_w, c4_dv28);
  for (c4_i374 = 0; c4_i374 < 3; c4_i374 = c4_i374 + 1) {
    c4_r[c4_i374] = -c4_dv28[c4_i374];
  }

  _SFD_SCRIPT_CALL(4, 11);
  for (c4_i375 = 0; c4_i375 < 3; c4_i375 = c4_i375 + 1) {
    c4_u[c4_i375] = c4_b_p[c4_i375] - c4_r[c4_i375];
  }

  _SFD_SCRIPT_CALL(4, 12);
  for (c4_i376 = 0; c4_i376 < 3; c4_i376 = c4_i376 + 1) {
    c4_v[c4_i376] = c4_b_q[c4_i376] - c4_r[c4_i376];
  }

  _SFD_SCRIPT_CALL(4, 14);
  for (c4_i377 = 0; c4_i377 < 3; c4_i377 = c4_i377 + 1) {
    c4_a[c4_i377] = c4_w[c4_i377];
  }

  for (c4_i378 = 0; c4_i378 < 3; c4_i378 = c4_i378 + 1) {
    c4_b[c4_i378] = c4_u[c4_i378];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i379 = 0; c4_i379 < 3; c4_i379 = c4_i379 + 1) {
    c4_x[c4_i379] = c4_a[c4_i379];
  }

  for (c4_i380 = 0; c4_i380 < 3; c4_i380 = c4_i380 + 1) {
    c4_y[c4_i380] = c4_b[c4_i380];
  }

  for (c4_i381 = 0; c4_i381 < 3; c4_i381 = c4_i381 + 1) {
    c4_b_x[c4_i381] = c4_x[c4_i381];
  }

  for (c4_i382 = 0; c4_i382 < 3; c4_i382 = c4_i382 + 1) {
    c4_b_y[c4_i382] = c4_y[c4_i382];
  }

  for (c4_i383 = 0; c4_i383 < 3; c4_i383 = c4_i383 + 1) {
    c4_c_x[c4_i383] = c4_b_x[c4_i383];
  }

  for (c4_i384 = 0; c4_i384 < 3; c4_i384 = c4_i384 + 1) {
    c4_c_y[c4_i384] = c4_b_y[c4_i384];
  }

  for (c4_i385 = 0; c4_i385 < 3; c4_i385 = c4_i385 + 1) {
    c4_d_x[c4_i385] = c4_c_x[c4_i385];
  }

  for (c4_i386 = 0; c4_i386 < 3; c4_i386 = c4_i386 + 1) {
    c4_d_y[c4_i386] = c4_c_y[c4_i386];
  }

  c4_e_y = c4_ceval_xdot(chartInstance, 3, c4_d_x, 1, 1, c4_d_y, 1, 1);
  for (c4_i387 = 0; c4_i387 < 3; c4_i387 = c4_i387 + 1) {
    c4_b_a[c4_i387] = c4_w[c4_i387];
  }

  c4_b_b = c4_e_y;
  for (c4_i388 = 0; c4_i388 < 3; c4_i388 = c4_i388 + 1) {
    c4_f_y[c4_i388] = c4_b_a[c4_i388] * c4_b_b;
  }

  for (c4_i389 = 0; c4_i389 < 3; c4_i389 = c4_i389 + 1) {
    c4_up[c4_i389] = c4_u[c4_i389] - c4_f_y[c4_i389];
  }

  _SFD_SCRIPT_CALL(4, 15);
  for (c4_i390 = 0; c4_i390 < 3; c4_i390 = c4_i390 + 1) {
    c4_c_a[c4_i390] = c4_w[c4_i390];
  }

  for (c4_i391 = 0; c4_i391 < 3; c4_i391 = c4_i391 + 1) {
    c4_c_b[c4_i391] = c4_v[c4_i391];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i392 = 0; c4_i392 < 3; c4_i392 = c4_i392 + 1) {
    c4_e_x[c4_i392] = c4_c_a[c4_i392];
  }

  for (c4_i393 = 0; c4_i393 < 3; c4_i393 = c4_i393 + 1) {
    c4_g_y[c4_i393] = c4_c_b[c4_i393];
  }

  for (c4_i394 = 0; c4_i394 < 3; c4_i394 = c4_i394 + 1) {
    c4_f_x[c4_i394] = c4_e_x[c4_i394];
  }

  for (c4_i395 = 0; c4_i395 < 3; c4_i395 = c4_i395 + 1) {
    c4_h_y[c4_i395] = c4_g_y[c4_i395];
  }

  for (c4_i396 = 0; c4_i396 < 3; c4_i396 = c4_i396 + 1) {
    c4_g_x[c4_i396] = c4_f_x[c4_i396];
  }

  for (c4_i397 = 0; c4_i397 < 3; c4_i397 = c4_i397 + 1) {
    c4_i_y[c4_i397] = c4_h_y[c4_i397];
  }

  for (c4_i398 = 0; c4_i398 < 3; c4_i398 = c4_i398 + 1) {
    c4_h_x[c4_i398] = c4_g_x[c4_i398];
  }

  for (c4_i399 = 0; c4_i399 < 3; c4_i399 = c4_i399 + 1) {
    c4_j_y[c4_i399] = c4_i_y[c4_i399];
  }

  c4_k_y = c4_ceval_xdot(chartInstance, 3, c4_h_x, 1, 1, c4_j_y, 1, 1);
  for (c4_i400 = 0; c4_i400 < 3; c4_i400 = c4_i400 + 1) {
    c4_d_a[c4_i400] = c4_w[c4_i400];
  }

  c4_d_b = c4_k_y;
  for (c4_i401 = 0; c4_i401 < 3; c4_i401 = c4_i401 + 1) {
    c4_l_y[c4_i401] = c4_d_a[c4_i401] * c4_d_b;
  }

  for (c4_i402 = 0; c4_i402 < 3; c4_i402 = c4_i402 + 1) {
    c4_vp[c4_i402] = c4_v[c4_i402] - c4_l_y[c4_i402];
  }

  _SFD_SCRIPT_CALL(4, 17);
  for (c4_i403 = 0; c4_i403 < 3; c4_i403 = c4_i403 + 1) {
    c4_e_a[c4_i403] = c4_b_d[c4_i403];
  }

  for (c4_i404 = 0; c4_i404 < 3; c4_i404 = c4_i404 + 1) {
    c4_e_b[c4_i404] = c4_b_d[c4_i404];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i405 = 0; c4_i405 < 3; c4_i405 = c4_i405 + 1) {
    c4_i_x[c4_i405] = c4_e_a[c4_i405];
  }

  for (c4_i406 = 0; c4_i406 < 3; c4_i406 = c4_i406 + 1) {
    c4_m_y[c4_i406] = c4_e_b[c4_i406];
  }

  for (c4_i407 = 0; c4_i407 < 3; c4_i407 = c4_i407 + 1) {
    c4_j_x[c4_i407] = c4_i_x[c4_i407];
  }

  for (c4_i408 = 0; c4_i408 < 3; c4_i408 = c4_i408 + 1) {
    c4_n_y[c4_i408] = c4_m_y[c4_i408];
  }

  for (c4_i409 = 0; c4_i409 < 3; c4_i409 = c4_i409 + 1) {
    c4_k_x[c4_i409] = c4_j_x[c4_i409];
  }

  for (c4_i410 = 0; c4_i410 < 3; c4_i410 = c4_i410 + 1) {
    c4_o_y[c4_i410] = c4_n_y[c4_i410];
  }

  for (c4_i411 = 0; c4_i411 < 3; c4_i411 = c4_i411 + 1) {
    c4_l_x[c4_i411] = c4_k_x[c4_i411];
  }

  for (c4_i412 = 0; c4_i412 < 3; c4_i412 = c4_i412 + 1) {
    c4_p_y[c4_i412] = c4_o_y[c4_i412];
  }

  c4_q_y = c4_ceval_xdot(chartInstance, 3, c4_l_x, 1, 1, c4_p_y, 1, 1);
  for (c4_i413 = 0; c4_i413 < 3; c4_i413 = c4_i413 + 1) {
    c4_f_a[c4_i413] = c4_w[c4_i413];
  }

  for (c4_i414 = 0; c4_i414 < 3; c4_i414 = c4_i414 + 1) {
    c4_f_b[c4_i414] = c4_b_p[c4_i414] - c4_b_q[c4_i414];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i415 = 0; c4_i415 < 3; c4_i415 = c4_i415 + 1) {
    c4_m_x[c4_i415] = c4_f_a[c4_i415];
  }

  for (c4_i416 = 0; c4_i416 < 3; c4_i416 = c4_i416 + 1) {
    c4_r_y[c4_i416] = c4_f_b[c4_i416];
  }

  for (c4_i417 = 0; c4_i417 < 3; c4_i417 = c4_i417 + 1) {
    c4_n_x[c4_i417] = c4_m_x[c4_i417];
  }

  for (c4_i418 = 0; c4_i418 < 3; c4_i418 = c4_i418 + 1) {
    c4_s_y[c4_i418] = c4_r_y[c4_i418];
  }

  for (c4_i419 = 0; c4_i419 < 3; c4_i419 = c4_i419 + 1) {
    c4_o_x[c4_i419] = c4_n_x[c4_i419];
  }

  for (c4_i420 = 0; c4_i420 < 3; c4_i420 = c4_i420 + 1) {
    c4_t_y[c4_i420] = c4_s_y[c4_i420];
  }

  for (c4_i421 = 0; c4_i421 < 3; c4_i421 = c4_i421 + 1) {
    c4_p_x[c4_i421] = c4_o_x[c4_i421];
  }

  for (c4_i422 = 0; c4_i422 < 3; c4_i422 = c4_i422 + 1) {
    c4_u_y[c4_i422] = c4_t_y[c4_i422];
  }

  c4_v_y = c4_ceval_xdot(chartInstance, 3, c4_p_x, 1, 1, c4_u_y, 1, 1);
  c4_dp2 = c4_q_y - c4_mpower(chartInstance, c4_v_y);
  _SFD_SCRIPT_CALL(4, 19);
  for (c4_i423 = 0; c4_i423 < 3; c4_i423 = c4_i423 + 1) {
    c4_g_a[c4_i423] = c4_w[c4_i423];
  }

  for (c4_i424 = 0; c4_i424 < 3; c4_i424 = c4_i424 + 1) {
    c4_b_up[c4_i424] = c4_up[c4_i424];
  }

  for (c4_i425 = 0; c4_i425 < 3; c4_i425 = c4_i425 + 1) {
    c4_b_vp[c4_i425] = c4_vp[c4_i425];
  }

  c4_cross(chartInstance, c4_b_up, c4_b_vp, c4_g_b);
  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i426 = 0; c4_i426 < 3; c4_i426 = c4_i426 + 1) {
    c4_q_x[c4_i426] = c4_g_a[c4_i426];
  }

  for (c4_i427 = 0; c4_i427 < 3; c4_i427 = c4_i427 + 1) {
    c4_w_y[c4_i427] = c4_g_b[c4_i427];
  }

  for (c4_i428 = 0; c4_i428 < 3; c4_i428 = c4_i428 + 1) {
    c4_r_x[c4_i428] = c4_q_x[c4_i428];
  }

  for (c4_i429 = 0; c4_i429 < 3; c4_i429 = c4_i429 + 1) {
    c4_x_y[c4_i429] = c4_w_y[c4_i429];
  }

  for (c4_i430 = 0; c4_i430 < 3; c4_i430 = c4_i430 + 1) {
    c4_s_x[c4_i430] = c4_r_x[c4_i430];
  }

  for (c4_i431 = 0; c4_i431 < 3; c4_i431 = c4_i431 + 1) {
    c4_y_y[c4_i431] = c4_x_y[c4_i431];
  }

  for (c4_i432 = 0; c4_i432 < 3; c4_i432 = c4_i432 + 1) {
    c4_t_x[c4_i432] = c4_s_x[c4_i432];
  }

  for (c4_i433 = 0; c4_i433 < 3; c4_i433 = c4_i433 + 1) {
    c4_ab_y[c4_i433] = c4_y_y[c4_i433];
  }

  c4_bb_y = c4_ceval_xdot(chartInstance, 3, c4_t_x, 1, 1, c4_ab_y, 1, 1);
  for (c4_i434 = 0; c4_i434 < 3; c4_i434 = c4_i434 + 1) {
    c4_h_a[c4_i434] = c4_up[c4_i434];
  }

  for (c4_i435 = 0; c4_i435 < 3; c4_i435 = c4_i435 + 1) {
    c4_h_b[c4_i435] = c4_vp[c4_i435];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i436 = 0; c4_i436 < 3; c4_i436 = c4_i436 + 1) {
    c4_u_x[c4_i436] = c4_h_a[c4_i436];
  }

  for (c4_i437 = 0; c4_i437 < 3; c4_i437 = c4_i437 + 1) {
    c4_cb_y[c4_i437] = c4_h_b[c4_i437];
  }

  for (c4_i438 = 0; c4_i438 < 3; c4_i438 = c4_i438 + 1) {
    c4_v_x[c4_i438] = c4_u_x[c4_i438];
  }

  for (c4_i439 = 0; c4_i439 < 3; c4_i439 = c4_i439 + 1) {
    c4_db_y[c4_i439] = c4_cb_y[c4_i439];
  }

  for (c4_i440 = 0; c4_i440 < 3; c4_i440 = c4_i440 + 1) {
    c4_w_x[c4_i440] = c4_v_x[c4_i440];
  }

  for (c4_i441 = 0; c4_i441 < 3; c4_i441 = c4_i441 + 1) {
    c4_eb_y[c4_i441] = c4_db_y[c4_i441];
  }

  for (c4_i442 = 0; c4_i442 < 3; c4_i442 = c4_i442 + 1) {
    c4_x_x[c4_i442] = c4_w_x[c4_i442];
  }

  for (c4_i443 = 0; c4_i443 < 3; c4_i443 = c4_i443 + 1) {
    c4_fb_y[c4_i443] = c4_eb_y[c4_i443];
  }

  c4_gb_y = c4_ceval_xdot(chartInstance, 3, c4_x_x, 1, 1, c4_fb_y, 1, 1);
  c4_theta0 = c4_atan2(chartInstance, c4_bb_y, c4_gb_y);
  _SFD_SCRIPT_CALL(4, 21);
  for (c4_i444 = 0; c4_i444 < 3; c4_i444 = c4_i444 + 1) {
    c4_i_a[c4_i444] = c4_up[c4_i444];
  }

  for (c4_i445 = 0; c4_i445 < 3; c4_i445 = c4_i445 + 1) {
    c4_i_b[c4_i445] = c4_up[c4_i445];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i446 = 0; c4_i446 < 3; c4_i446 = c4_i446 + 1) {
    c4_y_x[c4_i446] = c4_i_a[c4_i446];
  }

  for (c4_i447 = 0; c4_i447 < 3; c4_i447 = c4_i447 + 1) {
    c4_hb_y[c4_i447] = c4_i_b[c4_i447];
  }

  for (c4_i448 = 0; c4_i448 < 3; c4_i448 = c4_i448 + 1) {
    c4_ab_x[c4_i448] = c4_y_x[c4_i448];
  }

  for (c4_i449 = 0; c4_i449 < 3; c4_i449 = c4_i449 + 1) {
    c4_ib_y[c4_i449] = c4_hb_y[c4_i449];
  }

  for (c4_i450 = 0; c4_i450 < 3; c4_i450 = c4_i450 + 1) {
    c4_bb_x[c4_i450] = c4_ab_x[c4_i450];
  }

  for (c4_i451 = 0; c4_i451 < 3; c4_i451 = c4_i451 + 1) {
    c4_jb_y[c4_i451] = c4_ib_y[c4_i451];
  }

  for (c4_i452 = 0; c4_i452 < 3; c4_i452 = c4_i452 + 1) {
    c4_cb_x[c4_i452] = c4_bb_x[c4_i452];
  }

  for (c4_i453 = 0; c4_i453 < 3; c4_i453 = c4_i453 + 1) {
    c4_kb_y[c4_i453] = c4_jb_y[c4_i453];
  }

  c4_lb_y = c4_ceval_xdot(chartInstance, 3, c4_cb_x, 1, 1, c4_kb_y, 1, 1);
  for (c4_i454 = 0; c4_i454 < 3; c4_i454 = c4_i454 + 1) {
    c4_j_a[c4_i454] = c4_vp[c4_i454];
  }

  for (c4_i455 = 0; c4_i455 < 3; c4_i455 = c4_i455 + 1) {
    c4_j_b[c4_i455] = c4_vp[c4_i455];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i456 = 0; c4_i456 < 3; c4_i456 = c4_i456 + 1) {
    c4_db_x[c4_i456] = c4_j_a[c4_i456];
  }

  for (c4_i457 = 0; c4_i457 < 3; c4_i457 = c4_i457 + 1) {
    c4_mb_y[c4_i457] = c4_j_b[c4_i457];
  }

  for (c4_i458 = 0; c4_i458 < 3; c4_i458 = c4_i458 + 1) {
    c4_eb_x[c4_i458] = c4_db_x[c4_i458];
  }

  for (c4_i459 = 0; c4_i459 < 3; c4_i459 = c4_i459 + 1) {
    c4_nb_y[c4_i459] = c4_mb_y[c4_i459];
  }

  for (c4_i460 = 0; c4_i460 < 3; c4_i460 = c4_i460 + 1) {
    c4_fb_x[c4_i460] = c4_eb_x[c4_i460];
  }

  for (c4_i461 = 0; c4_i461 < 3; c4_i461 = c4_i461 + 1) {
    c4_ob_y[c4_i461] = c4_nb_y[c4_i461];
  }

  for (c4_i462 = 0; c4_i462 < 3; c4_i462 = c4_i462 + 1) {
    c4_gb_x[c4_i462] = c4_fb_x[c4_i462];
  }

  for (c4_i463 = 0; c4_i463 < 3; c4_i463 = c4_i463 + 1) {
    c4_pb_y[c4_i463] = c4_ob_y[c4_i463];
  }

  c4_qb_y = c4_ceval_xdot(chartInstance, 3, c4_gb_x, 1, 1, c4_pb_y, 1, 1);
  for (c4_i464 = 0; c4_i464 < 3; c4_i464 = c4_i464 + 1) {
    c4_c_up[c4_i464] = c4_up[c4_i464];
  }

  c4_k_b = c4_norm(chartInstance, c4_c_up);
  c4_rb_y = 2.0 * c4_k_b;
  c4_k_a = c4_rb_y;
  for (c4_i465 = 0; c4_i465 < 3; c4_i465 = c4_i465 + 1) {
    c4_c_vp[c4_i465] = c4_vp[c4_i465];
  }

  c4_l_b = c4_norm(chartInstance, c4_c_vp);
  c4_sb_y = c4_k_a * c4_l_b;
  c4_A = (c4_lb_y + c4_qb_y) - c4_dp2;
  c4_B = c4_sb_y;
  c4_hb_x = c4_A;
  c4_tb_y = c4_B;
  c4_ib_x = c4_hb_x;
  c4_ub_y = c4_tb_y;
  c4_jb_x = c4_ib_x;
  c4_vb_y = c4_ub_y;
  c4_wb_y = c4_jb_x / c4_vb_y;
  c4_kb_x = c4_wb_y;
  c4_phi = c4_kb_x;
  if (c4_phi < -1.0) {
  } else if (1.0 < c4_phi) {
  } else {
    goto label_1;
  }

  c4_b_eml_error(chartInstance);
 label_1:
  ;
  c4_lb_x = c4_phi;
  c4_phi = c4_lb_x;
  c4_phi = muDoubleScalarAcos(c4_phi);
  _SFD_SCRIPT_CALL(4, 23);
  c4_theta[0] = c4_theta0 - c4_phi;
  _SFD_SCRIPT_CALL(4, 24);
  c4_theta[1] = c4_theta0 + c4_phi;

  /*      check1 = (sol1 >= -45/180*pi) && (sol1 <= 115/180*pi); */
  /*      check2 = (sol2 >= -45/180*pi) && (sol2 <= 115/180*pi); */
  /*       */
  /*      if check1 && check2 */
  /*           */
  /*          if abs(sol1) > abs(sol2) */
  /*              theta = sol2; */
  /*          else */
  /*              theta = sol1; */
  /*          end */
  /*           */
  /*      elseif check1 */
  /*          theta = sol1; */
  /*      elseif check2 */
  /*          theta = sol2; */
  /*      end  */
  /*      Nsol = check1+check2; */
  _SFD_SCRIPT_CALL(4, 44);
  if (CV_SCRIPT_IF(4, 0, c4_phi != 0.0)) {
    _SFD_SCRIPT_CALL(4, 45);
    *c4_Nsol = 2.0;
  } else {
    /*          theta = theta0; */
    _SFD_SCRIPT_CALL(4, 48);
    *c4_Nsol = 1.0;
  }

  _SFD_SCRIPT_CALL(4, -48);
  sf_debug_symbol_scope_pop();
}

static void c4_g_eml_scalar_eg(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

static real_T c4_ceval_xdot(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[3], int32_T c4_ix0,
  int32_T c4_incx, real_T c4_y[3], int32_T c4_iy0, int32_T c4_incy)
{
  real_T c4_d;
  c4_d = 0.0;
  if ((real_T)c4_n > 0.0) {
    return ddot32(&c4_n, &c4_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c4_ix0), 1, 3, 1, 0) - 1], &
                  c4_incx, &c4_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c4_iy0), 1, 3, 1, 0) - 1], &c4_incy);
  }

  return c4_d;
}

static real_T c4_mpower(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_a)
{
  return c4_power(chartInstance, c4_a, 2.0);
}

static real_T c4_norm(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                      real_T c4_x[3])
{
  int32_T c4_i466;
  real_T c4_b_x[3];
  int32_T c4_i467;
  real_T c4_c_x[3];
  int32_T c4_i468;
  real_T c4_d_x[3];
  int32_T c4_i469;
  real_T c4_e_x[3];
  for (c4_i466 = 0; c4_i466 < 3; c4_i466 = c4_i466 + 1) {
    c4_b_x[c4_i466] = c4_x[c4_i466];
  }

  for (c4_i467 = 0; c4_i467 < 3; c4_i467 = c4_i467 + 1) {
    c4_c_x[c4_i467] = c4_b_x[c4_i467];
  }

  for (c4_i468 = 0; c4_i468 < 3; c4_i468 = c4_i468 + 1) {
    c4_d_x[c4_i468] = c4_c_x[c4_i468];
  }

  for (c4_i469 = 0; c4_i469 < 3; c4_i469 = c4_i469 + 1) {
    c4_e_x[c4_i469] = c4_d_x[c4_i469];
  }

  return c4_ceval_xnrm2(chartInstance, 3, c4_e_x, 1, 1);
}

static real_T c4_ceval_xnrm2(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[3], int32_T c4_ix0,
  int32_T c4_incx)
{
  return dnrm232(&c4_n, &c4_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c4_ix0), 1, 3, 1, 0) - 1], &
                 c4_incx);
}

static void c4_b_eml_error(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
  int32_T c4_i470;
  static char_T c4_cv4[31] = { 'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'a', 'c', 'o', 's', ':', 'd'
    , 'o', 'm', 'a', 'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c4_u[31];
  const mxArray *c4_y = NULL;
  int32_T c4_i471;
  static char_T c4_cv5[77] = { 'D', 'o', 'm', 'a', 'i', 'n', ' ', 'e', 'r', 'r',
    'o', 'r', '.', ' ', 'T', 'o', ' ', 'c', 'o', 'm', 'p'
    , 'u', 't', 'e', ' ', 'c', 'o', 'm', 'p', 'l', 'e', 'x', ' ', 'r', 'e', 's',
    'u', 'l', 't', 's', ' ',
    'f', 'r', 'o', 'm', ' ', 'r', 'e', 'a', 'l', ' ', 'x', ',', ' ', 'u', 's',
    'e', ' ', '\'', 'a', 'c',
    'o', 's', '(', 'c', 'o', 'm', 'p', 'l', 'e', 'x', '(', 'x', ')', ')', '\'',
    '.' };

  char_T c4_b_u[77];
  const mxArray *c4_b_y = NULL;
  for (c4_i470 = 0; c4_i470 < 31; c4_i470 = c4_i470 + 1) {
    c4_u[c4_i470] = c4_cv4[c4_i470];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 31));
  for (c4_i471 = 0; c4_i471 < 77; c4_i471 = c4_i471 + 1) {
    c4_b_u[c4_i471] = c4_cv5[c4_i471];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 77));
  sf_mex_call_debug("error", 0U, 2U, 14, c4_y, 14, c4_b_y);
}

static void c4_b_isInRange(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_x[2], real_T c4_xmin, real_T c4_xmax,
  boolean_T c4_isIn[2])
{
  uint32_T c4_debug_family_var_map[6];
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 1.0;
  int32_T c4_i472;
  real_T c4_A[2];
  int32_T c4_i473;
  real_T c4_b_x[2];
  int32_T c4_i474;
  real_T c4_c_x[2];
  int32_T c4_i475;
  real_T c4_d_x[2];
  int32_T c4_i476;
  real_T c4_y[2];
  int32_T c4_i477;
  real_T c4_a[2];
  int32_T c4_i478;
  int32_T c4_i479;
  boolean_T c4_bv5[2];
  int32_T c4_i480;
  boolean_T c4_bv6[2];
  int32_T c4_i481;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c4_g_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_x, c4_i_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c4_xmin, c4_e_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c4_xmax, c4_e_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_isIn, c4_k_sf_marshall, 5U);
  CV_SCRIPT_FCN(0, 1);
  _SFD_SCRIPT_CALL(0, 141);
  for (c4_i472 = 0; c4_i472 < 2; c4_i472 = c4_i472 + 1) {
    c4_A[c4_i472] = c4_x[c4_i472];
  }

  for (c4_i473 = 0; c4_i473 < 2; c4_i473 = c4_i473 + 1) {
    c4_b_x[c4_i473] = c4_A[c4_i473];
  }

  for (c4_i474 = 0; c4_i474 < 2; c4_i474 = c4_i474 + 1) {
    c4_c_x[c4_i474] = c4_b_x[c4_i474];
  }

  for (c4_i475 = 0; c4_i475 < 2; c4_i475 = c4_i475 + 1) {
    c4_d_x[c4_i475] = c4_c_x[c4_i475];
  }

  for (c4_i476 = 0; c4_i476 < 2; c4_i476 = c4_i476 + 1) {
    c4_y[c4_i476] = c4_d_x[c4_i476] / 3.1415926535897931;
  }

  for (c4_i477 = 0; c4_i477 < 2; c4_i477 = c4_i477 + 1) {
    c4_a[c4_i477] = c4_y[c4_i477];
  }

  for (c4_i478 = 0; c4_i478 < 2; c4_i478 = c4_i478 + 1) {
    c4_x[c4_i478] = c4_a[c4_i478] * 180.0;
  }

  _SFD_SCRIPT_CALL(0, 142);
  for (c4_i479 = 0; c4_i479 < 2; c4_i479 = c4_i479 + 1) {
    c4_bv5[c4_i479] = (c4_x[c4_i479] >= c4_xmin);
  }

  for (c4_i480 = 0; c4_i480 < 2; c4_i480 = c4_i480 + 1) {
    c4_bv6[c4_i480] = (c4_x[c4_i480] <= c4_xmax);
  }

  for (c4_i481 = 0; c4_i481 < 2; c4_i481 = c4_i481 + 1) {
    c4_isIn[c4_i481] = (c4_bv5[c4_i481] && c4_bv6[c4_i481]);
  }

  _SFD_SCRIPT_CALL(0, -142);
  sf_debug_symbol_scope_pop();
}

static boolean_T c4_any(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  boolean_T c4_x[2])
{
  boolean_T c4_y;
  int32_T c4_i482;
  boolean_T c4_b_x[2];
  real_T c4_k;
  real_T c4_b_k;
  boolean_T c4_b2;
  for (c4_i482 = 0; c4_i482 < 2; c4_i482 = c4_i482 + 1) {
    c4_b_x[c4_i482] = c4_x[c4_i482];
  }

  c4_y = FALSE;
  c4_k = 1.0;
 label_1:
  ;
  if (c4_k <= 2.0) {
    c4_b_k = c4_k;
    if ((real_T)c4_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
         _SFD_INTEGER_CHECK("", c4_b_k), 1, 2, 1, 0) - 1] == 0.0) {
      c4_b2 = TRUE;
    } else {
      (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        c4_b_k), 1, 2, 1, 0);
      c4_b2 = FALSE;
    }

    if (!c4_b2) {
      return TRUE;
    } else {
      c4_k = c4_k + 1.0;
      goto label_1;
    }
  }

  return c4_y;
}

static real_T c4_subPro1(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_kx[6], real_T c4_p[4], real_T c4_q[4])
{
  real_T c4_theta;
  uint32_T c4_debug_family_var_map[13];
  real_T c4_velociy[3];
  real_T c4_w[3];
  real_T c4_r[3];
  real_T c4_u[3];
  real_T c4_v[3];
  real_T c4_up[3];
  real_T c4_vp[3];
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 1.0;
  int32_T c4_i483;
  int32_T c4_i484;
  int32_T c4_i485;
  real_T c4_b_velociy[3];
  int32_T c4_i486;
  real_T c4_b_w[3];
  real_T c4_dv29[3];
  int32_T c4_i487;
  int32_T c4_i488;
  int32_T c4_i489;
  int32_T c4_i490;
  real_T c4_a[3];
  int32_T c4_i491;
  real_T c4_b[3];
  int32_T c4_i492;
  real_T c4_x[3];
  int32_T c4_i493;
  real_T c4_y[3];
  int32_T c4_i494;
  real_T c4_b_x[3];
  int32_T c4_i495;
  real_T c4_b_y[3];
  int32_T c4_i496;
  real_T c4_c_x[3];
  int32_T c4_i497;
  real_T c4_c_y[3];
  int32_T c4_i498;
  real_T c4_d_x[3];
  int32_T c4_i499;
  real_T c4_d_y[3];
  real_T c4_e_y;
  int32_T c4_i500;
  real_T c4_b_a[3];
  real_T c4_b_b;
  int32_T c4_i501;
  real_T c4_f_y[3];
  int32_T c4_i502;
  int32_T c4_i503;
  real_T c4_c_a[3];
  int32_T c4_i504;
  real_T c4_c_b[3];
  int32_T c4_i505;
  real_T c4_e_x[3];
  int32_T c4_i506;
  real_T c4_g_y[3];
  int32_T c4_i507;
  real_T c4_f_x[3];
  int32_T c4_i508;
  real_T c4_h_y[3];
  int32_T c4_i509;
  real_T c4_g_x[3];
  int32_T c4_i510;
  real_T c4_i_y[3];
  int32_T c4_i511;
  real_T c4_h_x[3];
  int32_T c4_i512;
  real_T c4_j_y[3];
  real_T c4_k_y;
  int32_T c4_i513;
  real_T c4_d_a[3];
  real_T c4_d_b;
  int32_T c4_i514;
  real_T c4_l_y[3];
  int32_T c4_i515;
  int32_T c4_i516;
  real_T c4_e_a[3];
  int32_T c4_i517;
  real_T c4_b_up[3];
  int32_T c4_i518;
  real_T c4_b_vp[3];
  real_T c4_e_b[3];
  int32_T c4_i519;
  real_T c4_i_x[3];
  int32_T c4_i520;
  real_T c4_m_y[3];
  int32_T c4_i521;
  real_T c4_j_x[3];
  int32_T c4_i522;
  real_T c4_n_y[3];
  int32_T c4_i523;
  real_T c4_k_x[3];
  int32_T c4_i524;
  real_T c4_o_y[3];
  int32_T c4_i525;
  real_T c4_l_x[3];
  int32_T c4_i526;
  real_T c4_p_y[3];
  real_T c4_q_y;
  int32_T c4_i527;
  real_T c4_f_a[3];
  int32_T c4_i528;
  real_T c4_f_b[3];
  int32_T c4_i529;
  real_T c4_m_x[3];
  int32_T c4_i530;
  real_T c4_r_y[3];
  int32_T c4_i531;
  real_T c4_n_x[3];
  int32_T c4_i532;
  real_T c4_s_y[3];
  int32_T c4_i533;
  real_T c4_o_x[3];
  int32_T c4_i534;
  real_T c4_t_y[3];
  int32_T c4_i535;
  real_T c4_p_x[3];
  int32_T c4_i536;
  real_T c4_u_y[3];
  real_T c4_v_y;
  sf_debug_symbol_scope_push_eml(0U, 13U, 13U, c4_h_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_velociy, c4_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c4_w, c4_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_r, c4_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c4_u, c4_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c4_v, c4_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_up, c4_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c4_vp, c4_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c4_kx, c4_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(c4_p, c4_j_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(c4_q, c4_j_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c4_theta, c4_e_sf_marshall, 12U);
  CV_SCRIPT_FCN(5, 0);
  _SFD_SCRIPT_CALL(5, 4);
  for (c4_i483 = 0; c4_i483 < 3; c4_i483 = c4_i483 + 1) {
    c4_velociy[c4_i483] = c4_kx[c4_i483];
  }

  _SFD_SCRIPT_CALL(5, 5);
  for (c4_i484 = 0; c4_i484 < 3; c4_i484 = c4_i484 + 1) {
    c4_w[c4_i484] = c4_kx[c4_i484 + 3];
  }

  /*  rotation axis */
  _SFD_SCRIPT_CALL(5, 6);
  for (c4_i485 = 0; c4_i485 < 3; c4_i485 = c4_i485 + 1) {
    c4_b_velociy[c4_i485] = c4_velociy[c4_i485];
  }

  for (c4_i486 = 0; c4_i486 < 3; c4_i486 = c4_i486 + 1) {
    c4_b_w[c4_i486] = c4_w[c4_i486];
  }

  c4_cross(chartInstance, c4_b_velociy, c4_b_w, c4_dv29);
  for (c4_i487 = 0; c4_i487 < 3; c4_i487 = c4_i487 + 1) {
    c4_r[c4_i487] = -c4_dv29[c4_i487];
  }

  _SFD_SCRIPT_CALL(5, 8);
  for (c4_i488 = 0; c4_i488 < 3; c4_i488 = c4_i488 + 1) {
    c4_u[c4_i488] = c4_p[c4_i488] - c4_r[c4_i488];
  }

  _SFD_SCRIPT_CALL(5, 9);
  for (c4_i489 = 0; c4_i489 < 3; c4_i489 = c4_i489 + 1) {
    c4_v[c4_i489] = c4_q[c4_i489] - c4_r[c4_i489];
  }

  _SFD_SCRIPT_CALL(5, 12);
  for (c4_i490 = 0; c4_i490 < 3; c4_i490 = c4_i490 + 1) {
    c4_a[c4_i490] = c4_w[c4_i490];
  }

  for (c4_i491 = 0; c4_i491 < 3; c4_i491 = c4_i491 + 1) {
    c4_b[c4_i491] = c4_u[c4_i491];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i492 = 0; c4_i492 < 3; c4_i492 = c4_i492 + 1) {
    c4_x[c4_i492] = c4_a[c4_i492];
  }

  for (c4_i493 = 0; c4_i493 < 3; c4_i493 = c4_i493 + 1) {
    c4_y[c4_i493] = c4_b[c4_i493];
  }

  for (c4_i494 = 0; c4_i494 < 3; c4_i494 = c4_i494 + 1) {
    c4_b_x[c4_i494] = c4_x[c4_i494];
  }

  for (c4_i495 = 0; c4_i495 < 3; c4_i495 = c4_i495 + 1) {
    c4_b_y[c4_i495] = c4_y[c4_i495];
  }

  for (c4_i496 = 0; c4_i496 < 3; c4_i496 = c4_i496 + 1) {
    c4_c_x[c4_i496] = c4_b_x[c4_i496];
  }

  for (c4_i497 = 0; c4_i497 < 3; c4_i497 = c4_i497 + 1) {
    c4_c_y[c4_i497] = c4_b_y[c4_i497];
  }

  for (c4_i498 = 0; c4_i498 < 3; c4_i498 = c4_i498 + 1) {
    c4_d_x[c4_i498] = c4_c_x[c4_i498];
  }

  for (c4_i499 = 0; c4_i499 < 3; c4_i499 = c4_i499 + 1) {
    c4_d_y[c4_i499] = c4_c_y[c4_i499];
  }

  c4_e_y = c4_ceval_xdot(chartInstance, 3, c4_d_x, 1, 1, c4_d_y, 1, 1);
  for (c4_i500 = 0; c4_i500 < 3; c4_i500 = c4_i500 + 1) {
    c4_b_a[c4_i500] = c4_w[c4_i500];
  }

  c4_b_b = c4_e_y;
  for (c4_i501 = 0; c4_i501 < 3; c4_i501 = c4_i501 + 1) {
    c4_f_y[c4_i501] = c4_b_a[c4_i501] * c4_b_b;
  }

  for (c4_i502 = 0; c4_i502 < 3; c4_i502 = c4_i502 + 1) {
    c4_up[c4_i502] = c4_u[c4_i502] - c4_f_y[c4_i502];
  }

  _SFD_SCRIPT_CALL(5, 13);
  for (c4_i503 = 0; c4_i503 < 3; c4_i503 = c4_i503 + 1) {
    c4_c_a[c4_i503] = c4_w[c4_i503];
  }

  for (c4_i504 = 0; c4_i504 < 3; c4_i504 = c4_i504 + 1) {
    c4_c_b[c4_i504] = c4_u[c4_i504];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i505 = 0; c4_i505 < 3; c4_i505 = c4_i505 + 1) {
    c4_e_x[c4_i505] = c4_c_a[c4_i505];
  }

  for (c4_i506 = 0; c4_i506 < 3; c4_i506 = c4_i506 + 1) {
    c4_g_y[c4_i506] = c4_c_b[c4_i506];
  }

  for (c4_i507 = 0; c4_i507 < 3; c4_i507 = c4_i507 + 1) {
    c4_f_x[c4_i507] = c4_e_x[c4_i507];
  }

  for (c4_i508 = 0; c4_i508 < 3; c4_i508 = c4_i508 + 1) {
    c4_h_y[c4_i508] = c4_g_y[c4_i508];
  }

  for (c4_i509 = 0; c4_i509 < 3; c4_i509 = c4_i509 + 1) {
    c4_g_x[c4_i509] = c4_f_x[c4_i509];
  }

  for (c4_i510 = 0; c4_i510 < 3; c4_i510 = c4_i510 + 1) {
    c4_i_y[c4_i510] = c4_h_y[c4_i510];
  }

  for (c4_i511 = 0; c4_i511 < 3; c4_i511 = c4_i511 + 1) {
    c4_h_x[c4_i511] = c4_g_x[c4_i511];
  }

  for (c4_i512 = 0; c4_i512 < 3; c4_i512 = c4_i512 + 1) {
    c4_j_y[c4_i512] = c4_i_y[c4_i512];
  }

  c4_k_y = c4_ceval_xdot(chartInstance, 3, c4_h_x, 1, 1, c4_j_y, 1, 1);
  for (c4_i513 = 0; c4_i513 < 3; c4_i513 = c4_i513 + 1) {
    c4_d_a[c4_i513] = c4_w[c4_i513];
  }

  c4_d_b = c4_k_y;
  for (c4_i514 = 0; c4_i514 < 3; c4_i514 = c4_i514 + 1) {
    c4_l_y[c4_i514] = c4_d_a[c4_i514] * c4_d_b;
  }

  for (c4_i515 = 0; c4_i515 < 3; c4_i515 = c4_i515 + 1) {
    c4_vp[c4_i515] = c4_v[c4_i515] - c4_l_y[c4_i515];
  }

  /*      if norm(up) == 0 */
  /*          error('SubPro1: up = 0, Infinite number of solutions!'); */
  /*      end */
  _SFD_SCRIPT_CALL(5, 19);
  for (c4_i516 = 0; c4_i516 < 3; c4_i516 = c4_i516 + 1) {
    c4_e_a[c4_i516] = c4_w[c4_i516];
  }

  for (c4_i517 = 0; c4_i517 < 3; c4_i517 = c4_i517 + 1) {
    c4_b_up[c4_i517] = c4_up[c4_i517];
  }

  for (c4_i518 = 0; c4_i518 < 3; c4_i518 = c4_i518 + 1) {
    c4_b_vp[c4_i518] = c4_vp[c4_i518];
  }

  c4_cross(chartInstance, c4_b_up, c4_b_vp, c4_e_b);
  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i519 = 0; c4_i519 < 3; c4_i519 = c4_i519 + 1) {
    c4_i_x[c4_i519] = c4_e_a[c4_i519];
  }

  for (c4_i520 = 0; c4_i520 < 3; c4_i520 = c4_i520 + 1) {
    c4_m_y[c4_i520] = c4_e_b[c4_i520];
  }

  for (c4_i521 = 0; c4_i521 < 3; c4_i521 = c4_i521 + 1) {
    c4_j_x[c4_i521] = c4_i_x[c4_i521];
  }

  for (c4_i522 = 0; c4_i522 < 3; c4_i522 = c4_i522 + 1) {
    c4_n_y[c4_i522] = c4_m_y[c4_i522];
  }

  for (c4_i523 = 0; c4_i523 < 3; c4_i523 = c4_i523 + 1) {
    c4_k_x[c4_i523] = c4_j_x[c4_i523];
  }

  for (c4_i524 = 0; c4_i524 < 3; c4_i524 = c4_i524 + 1) {
    c4_o_y[c4_i524] = c4_n_y[c4_i524];
  }

  for (c4_i525 = 0; c4_i525 < 3; c4_i525 = c4_i525 + 1) {
    c4_l_x[c4_i525] = c4_k_x[c4_i525];
  }

  for (c4_i526 = 0; c4_i526 < 3; c4_i526 = c4_i526 + 1) {
    c4_p_y[c4_i526] = c4_o_y[c4_i526];
  }

  c4_q_y = c4_ceval_xdot(chartInstance, 3, c4_l_x, 1, 1, c4_p_y, 1, 1);
  for (c4_i527 = 0; c4_i527 < 3; c4_i527 = c4_i527 + 1) {
    c4_f_a[c4_i527] = c4_up[c4_i527];
  }

  for (c4_i528 = 0; c4_i528 < 3; c4_i528 = c4_i528 + 1) {
    c4_f_b[c4_i528] = c4_vp[c4_i528];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i529 = 0; c4_i529 < 3; c4_i529 = c4_i529 + 1) {
    c4_m_x[c4_i529] = c4_f_a[c4_i529];
  }

  for (c4_i530 = 0; c4_i530 < 3; c4_i530 = c4_i530 + 1) {
    c4_r_y[c4_i530] = c4_f_b[c4_i530];
  }

  for (c4_i531 = 0; c4_i531 < 3; c4_i531 = c4_i531 + 1) {
    c4_n_x[c4_i531] = c4_m_x[c4_i531];
  }

  for (c4_i532 = 0; c4_i532 < 3; c4_i532 = c4_i532 + 1) {
    c4_s_y[c4_i532] = c4_r_y[c4_i532];
  }

  for (c4_i533 = 0; c4_i533 < 3; c4_i533 = c4_i533 + 1) {
    c4_o_x[c4_i533] = c4_n_x[c4_i533];
  }

  for (c4_i534 = 0; c4_i534 < 3; c4_i534 = c4_i534 + 1) {
    c4_t_y[c4_i534] = c4_s_y[c4_i534];
  }

  for (c4_i535 = 0; c4_i535 < 3; c4_i535 = c4_i535 + 1) {
    c4_p_x[c4_i535] = c4_o_x[c4_i535];
  }

  for (c4_i536 = 0; c4_i536 < 3; c4_i536 = c4_i536 + 1) {
    c4_u_y[c4_i536] = c4_t_y[c4_i536];
  }

  c4_v_y = c4_ceval_xdot(chartInstance, 3, c4_p_x, 1, 1, c4_u_y, 1, 1);
  c4_theta = c4_atan2(chartInstance, c4_q_y, c4_v_y);
  _SFD_SCRIPT_CALL(5, -19);
  sf_debug_symbol_scope_pop();
  return c4_theta;
}

static void c4_subPro2(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_kx1[6], real_T c4_kx2[6], real_T c4_p[4],
  real_T c4_q[4], real_T c4_theta1[2], real_T c4_theta2[2], real_T *c4_Nsol)
{
  uint32_T c4_debug_family_var_map[25];
  static const char *c4_sv4[25] = { "velociy1", "w1", "r1", "velociy2", "w2",
    "r2", "r", "u", "v", "alpha", "beta", "ySqu", "i", "y",
    "z", "c", "nargin", "nargout", "kx1", "kx2", "p", "q", "theta1", "theta2",
    "Nsol" };

  real_T c4_velociy1[3];
  real_T c4_w1[3];
  real_T c4_r1[3];
  real_T c4_velociy2[3];
  real_T c4_w2[3];
  real_T c4_r2[3];
  real_T c4_r[3];
  real_T c4_u[3];
  real_T c4_v[3];
  real_T c4_alpha;
  real_T c4_beta;
  real_T c4_ySqu;
  real_T c4_i;
  real_T c4_y;
  real_T c4_z[3];
  real_T c4_c[3];
  real_T c4_nargin = 4.0;
  real_T c4_nargout = 3.0;
  int32_T c4_i537;
  int32_T c4_i538;
  int32_T c4_i539;
  int32_T c4_i540;
  int32_T c4_i541;
  real_T c4_b_velociy1[3];
  int32_T c4_i542;
  real_T c4_b_w1[3];
  real_T c4_dv30[3];
  int32_T c4_i543;
  int32_T c4_i544;
  int32_T c4_i545;
  int32_T c4_i546;
  real_T c4_b_velociy2[3];
  int32_T c4_i547;
  real_T c4_b_w2[3];
  real_T c4_dv31[3];
  int32_T c4_i548;
  int32_T c4_i549;
  real_T c4_c_w1[3];
  int32_T c4_i550;
  real_T c4_c_w2[3];
  int32_T c4_i551;
  real_T c4_b_r1[3];
  int32_T c4_i552;
  real_T c4_b_r2[3];
  real_T c4_dv32[3];
  int32_T c4_i553;
  int32_T c4_i554;
  int32_T c4_i555;
  int32_T c4_i556;
  real_T c4_a[3];
  int32_T c4_i557;
  real_T c4_b[3];
  int32_T c4_i558;
  real_T c4_x[3];
  int32_T c4_i559;
  real_T c4_b_y[3];
  int32_T c4_i560;
  real_T c4_b_x[3];
  int32_T c4_i561;
  real_T c4_c_y[3];
  int32_T c4_i562;
  real_T c4_c_x[3];
  int32_T c4_i563;
  real_T c4_d_y[3];
  int32_T c4_i564;
  real_T c4_d_x[3];
  int32_T c4_i565;
  real_T c4_e_y[3];
  real_T c4_f_y;
  real_T c4_b_a;
  int32_T c4_i566;
  real_T c4_b_b[3];
  int32_T c4_i567;
  real_T c4_g_y[3];
  int32_T c4_i568;
  real_T c4_c_a[3];
  int32_T c4_i569;
  real_T c4_c_b[3];
  int32_T c4_i570;
  real_T c4_e_x[3];
  int32_T c4_i571;
  real_T c4_h_y[3];
  int32_T c4_i572;
  real_T c4_f_x[3];
  int32_T c4_i573;
  real_T c4_i_y[3];
  int32_T c4_i574;
  real_T c4_g_x[3];
  int32_T c4_i575;
  real_T c4_j_y[3];
  int32_T c4_i576;
  real_T c4_h_x[3];
  int32_T c4_i577;
  real_T c4_k_y[3];
  real_T c4_l_y;
  int32_T c4_i578;
  real_T c4_d_a[3];
  int32_T c4_i579;
  real_T c4_d_b[3];
  int32_T c4_i580;
  real_T c4_i_x[3];
  int32_T c4_i581;
  real_T c4_m_y[3];
  int32_T c4_i582;
  real_T c4_j_x[3];
  int32_T c4_i583;
  real_T c4_n_y[3];
  int32_T c4_i584;
  real_T c4_k_x[3];
  int32_T c4_i585;
  real_T c4_o_y[3];
  int32_T c4_i586;
  real_T c4_l_x[3];
  int32_T c4_i587;
  real_T c4_p_y[3];
  real_T c4_q_y;
  int32_T c4_i588;
  real_T c4_e_a[3];
  int32_T c4_i589;
  real_T c4_e_b[3];
  int32_T c4_i590;
  real_T c4_m_x[3];
  int32_T c4_i591;
  real_T c4_r_y[3];
  int32_T c4_i592;
  real_T c4_n_x[3];
  int32_T c4_i593;
  real_T c4_s_y[3];
  int32_T c4_i594;
  real_T c4_o_x[3];
  int32_T c4_i595;
  real_T c4_t_y[3];
  int32_T c4_i596;
  real_T c4_p_x[3];
  int32_T c4_i597;
  real_T c4_u_y[3];
  real_T c4_v_y;
  int32_T c4_i598;
  real_T c4_f_a[3];
  int32_T c4_i599;
  real_T c4_f_b[3];
  int32_T c4_i600;
  real_T c4_q_x[3];
  int32_T c4_i601;
  real_T c4_w_y[3];
  int32_T c4_i602;
  real_T c4_r_x[3];
  int32_T c4_i603;
  real_T c4_x_y[3];
  int32_T c4_i604;
  real_T c4_s_x[3];
  int32_T c4_i605;
  real_T c4_y_y[3];
  int32_T c4_i606;
  real_T c4_t_x[3];
  int32_T c4_i607;
  real_T c4_ab_y[3];
  real_T c4_bb_y;
  real_T c4_g_a;
  real_T c4_g_b;
  real_T c4_cb_y;
  real_T c4_A;
  real_T c4_B;
  real_T c4_u_x;
  real_T c4_db_y;
  real_T c4_v_x;
  real_T c4_eb_y;
  real_T c4_w_x;
  real_T c4_fb_y;
  int32_T c4_i608;
  real_T c4_h_a[3];
  int32_T c4_i609;
  real_T c4_h_b[3];
  int32_T c4_i610;
  real_T c4_x_x[3];
  int32_T c4_i611;
  real_T c4_gb_y[3];
  int32_T c4_i612;
  real_T c4_y_x[3];
  int32_T c4_i613;
  real_T c4_hb_y[3];
  int32_T c4_i614;
  real_T c4_ab_x[3];
  int32_T c4_i615;
  real_T c4_ib_y[3];
  int32_T c4_i616;
  real_T c4_bb_x[3];
  int32_T c4_i617;
  real_T c4_jb_y[3];
  real_T c4_kb_y;
  real_T c4_i_a;
  int32_T c4_i618;
  real_T c4_i_b[3];
  int32_T c4_i619;
  real_T c4_lb_y[3];
  int32_T c4_i620;
  real_T c4_j_a[3];
  int32_T c4_i621;
  real_T c4_j_b[3];
  int32_T c4_i622;
  real_T c4_cb_x[3];
  int32_T c4_i623;
  real_T c4_mb_y[3];
  int32_T c4_i624;
  real_T c4_db_x[3];
  int32_T c4_i625;
  real_T c4_nb_y[3];
  int32_T c4_i626;
  real_T c4_eb_x[3];
  int32_T c4_i627;
  real_T c4_ob_y[3];
  int32_T c4_i628;
  real_T c4_fb_x[3];
  int32_T c4_i629;
  real_T c4_pb_y[3];
  real_T c4_qb_y;
  int32_T c4_i630;
  real_T c4_k_a[3];
  int32_T c4_i631;
  real_T c4_k_b[3];
  int32_T c4_i632;
  real_T c4_gb_x[3];
  int32_T c4_i633;
  real_T c4_rb_y[3];
  int32_T c4_i634;
  real_T c4_hb_x[3];
  int32_T c4_i635;
  real_T c4_sb_y[3];
  int32_T c4_i636;
  real_T c4_ib_x[3];
  int32_T c4_i637;
  real_T c4_tb_y[3];
  int32_T c4_i638;
  real_T c4_jb_x[3];
  int32_T c4_i639;
  real_T c4_ub_y[3];
  real_T c4_vb_y;
  int32_T c4_i640;
  real_T c4_l_a[3];
  int32_T c4_i641;
  real_T c4_l_b[3];
  int32_T c4_i642;
  real_T c4_kb_x[3];
  int32_T c4_i643;
  real_T c4_wb_y[3];
  int32_T c4_i644;
  real_T c4_lb_x[3];
  int32_T c4_i645;
  real_T c4_xb_y[3];
  int32_T c4_i646;
  real_T c4_mb_x[3];
  int32_T c4_i647;
  real_T c4_yb_y[3];
  int32_T c4_i648;
  real_T c4_nb_x[3];
  int32_T c4_i649;
  real_T c4_ac_y[3];
  real_T c4_bc_y;
  int32_T c4_i650;
  real_T c4_m_a[3];
  int32_T c4_i651;
  real_T c4_m_b[3];
  int32_T c4_i652;
  real_T c4_ob_x[3];
  int32_T c4_i653;
  real_T c4_cc_y[3];
  int32_T c4_i654;
  real_T c4_pb_x[3];
  int32_T c4_i655;
  real_T c4_dc_y[3];
  int32_T c4_i656;
  real_T c4_qb_x[3];
  int32_T c4_i657;
  real_T c4_ec_y[3];
  int32_T c4_i658;
  real_T c4_rb_x[3];
  int32_T c4_i659;
  real_T c4_fc_y[3];
  real_T c4_gc_y;
  real_T c4_n_a;
  real_T c4_n_b;
  real_T c4_hc_y;
  real_T c4_b_A;
  real_T c4_b_B;
  real_T c4_sb_x;
  real_T c4_ic_y;
  real_T c4_tb_x;
  real_T c4_jc_y;
  real_T c4_ub_x;
  real_T c4_kc_y;
  int32_T c4_i660;
  real_T c4_o_a[3];
  int32_T c4_i661;
  real_T c4_o_b[3];
  int32_T c4_i662;
  real_T c4_vb_x[3];
  int32_T c4_i663;
  real_T c4_lc_y[3];
  int32_T c4_i664;
  real_T c4_wb_x[3];
  int32_T c4_i665;
  real_T c4_mc_y[3];
  int32_T c4_i666;
  real_T c4_xb_x[3];
  int32_T c4_i667;
  real_T c4_nc_y[3];
  int32_T c4_i668;
  real_T c4_yb_x[3];
  int32_T c4_i669;
  real_T c4_oc_y[3];
  real_T c4_pc_y;
  real_T c4_p_a;
  real_T c4_p_b;
  real_T c4_qc_y;
  real_T c4_q_a;
  real_T c4_q_b;
  real_T c4_rc_y;
  real_T c4_r_b;
  real_T c4_sc_y;
  real_T c4_r_a;
  real_T c4_s_b;
  real_T c4_tc_y;
  real_T c4_s_a;
  int32_T c4_i670;
  real_T c4_t_b[3];
  int32_T c4_i671;
  real_T c4_uc_y[3];
  int32_T c4_i672;
  real_T c4_t_a[3];
  int32_T c4_i673;
  real_T c4_u_b[3];
  int32_T c4_i674;
  real_T c4_ac_x[3];
  int32_T c4_i675;
  real_T c4_vc_y[3];
  int32_T c4_i676;
  real_T c4_bc_x[3];
  int32_T c4_i677;
  real_T c4_wc_y[3];
  int32_T c4_i678;
  real_T c4_cc_x[3];
  int32_T c4_i679;
  real_T c4_xc_y[3];
  int32_T c4_i680;
  real_T c4_dc_x[3];
  int32_T c4_i681;
  real_T c4_yc_y[3];
  real_T c4_ad_y;
  int32_T c4_i682;
  real_T c4_d_w1[3];
  int32_T c4_i683;
  real_T c4_d_w2[3];
  real_T c4_dv33[3];
  int32_T c4_i684;
  real_T c4_u_a[3];
  int32_T c4_i685;
  real_T c4_e_w1[3];
  int32_T c4_i686;
  real_T c4_e_w2[3];
  real_T c4_v_b[3];
  int32_T c4_i687;
  real_T c4_ec_x[3];
  int32_T c4_i688;
  real_T c4_bd_y[3];
  int32_T c4_i689;
  real_T c4_fc_x[3];
  int32_T c4_i690;
  real_T c4_cd_y[3];
  int32_T c4_i691;
  real_T c4_gc_x[3];
  int32_T c4_i692;
  real_T c4_dd_y[3];
  int32_T c4_i693;
  real_T c4_hc_x[3];
  int32_T c4_i694;
  real_T c4_ed_y[3];
  real_T c4_fd_y;
  real_T c4_c_A;
  real_T c4_c_B;
  real_T c4_ic_x;
  real_T c4_gd_y;
  real_T c4_jc_x;
  real_T c4_hd_y;
  real_T c4_kc_x;
  real_T c4_id_y;
  real_T c4_b_i;
  real_T c4_w_b;
  real_T c4_jd_y;
  real_T c4_lc_x;
  real_T c4_mc_x;
  real_T c4_nc_x;
  real_T c4_v_a;
  real_T c4_x_b;
  real_T c4_w_a;
  int32_T c4_i695;
  real_T c4_y_b[3];
  int32_T c4_i696;
  real_T c4_kd_y[3];
  real_T c4_x_a;
  int32_T c4_i697;
  real_T c4_ab_b[3];
  int32_T c4_i698;
  real_T c4_ld_y[3];
  real_T c4_y_a;
  int32_T c4_i699;
  real_T c4_f_w1[3];
  int32_T c4_i700;
  real_T c4_f_w2[3];
  real_T c4_bb_b[3];
  int32_T c4_i701;
  real_T c4_md_y[3];
  int32_T c4_i702;
  int32_T c4_i703;
  int32_T c4_i704;
  real_T c4_b_kx2[6];
  int32_T c4_i705;
  real_T c4_b_p[4];
  int32_T c4_i706;
  real_T c4_b_c[3];
  int32_T c4_i707;
  real_T c4_b_kx1[6];
  int32_T c4_i708;
  real_T c4_c_c[3];
  int32_T c4_i709;
  real_T c4_b_q[4];
  sf_debug_symbol_scope_push_eml(0U, 25U, 25U, c4_sv4, c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_velociy1, c4_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c4_w1, c4_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_r1, c4_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c4_velociy2, c4_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c4_w2, c4_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_r2, c4_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c4_r, c4_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c4_u, c4_d_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c4_v, c4_d_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c4_alpha, c4_e_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&c4_beta, c4_e_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&c4_ySqu, c4_e_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c4_i, c4_e_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(&c4_y, c4_e_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(c4_z, c4_d_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(c4_c, c4_d_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 16U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 17U);
  sf_debug_symbol_scope_add_eml(c4_kx1, c4_sf_marshall, 18U);
  sf_debug_symbol_scope_add_eml(c4_kx2, c4_sf_marshall, 19U);
  sf_debug_symbol_scope_add_eml(c4_p, c4_j_sf_marshall, 20U);
  sf_debug_symbol_scope_add_eml(c4_q, c4_j_sf_marshall, 21U);
  sf_debug_symbol_scope_add_eml(c4_theta1, c4_i_sf_marshall, 22U);
  sf_debug_symbol_scope_add_eml(c4_theta2, c4_i_sf_marshall, 23U);
  sf_debug_symbol_scope_add_eml(c4_Nsol, c4_e_sf_marshall, 24U);
  CV_SCRIPT_FCN(6, 0);
  _SFD_SCRIPT_CALL(6, 3);
  for (c4_i537 = 0; c4_i537 < 2; c4_i537 = c4_i537 + 1) {
    c4_theta1[c4_i537] = 0.0;
  }

  _SFD_SCRIPT_CALL(6, 4);
  for (c4_i538 = 0; c4_i538 < 2; c4_i538 = c4_i538 + 1) {
    c4_theta2[c4_i538] = 0.0;
  }

  /*  ============================================= %     */
  /*  Twist 2 is the one that rotation happens first */
  /*  ============================================= % */
  _SFD_SCRIPT_CALL(6, 9);
  for (c4_i539 = 0; c4_i539 < 3; c4_i539 = c4_i539 + 1) {
    c4_velociy1[c4_i539] = c4_kx1[c4_i539];
  }

  _SFD_SCRIPT_CALL(6, 10);
  for (c4_i540 = 0; c4_i540 < 3; c4_i540 = c4_i540 + 1) {
    c4_w1[c4_i540] = c4_kx1[c4_i540 + 3];
  }

  /*  rotation axis for twist1 */
  _SFD_SCRIPT_CALL(6, 11);
  for (c4_i541 = 0; c4_i541 < 3; c4_i541 = c4_i541 + 1) {
    c4_b_velociy1[c4_i541] = c4_velociy1[c4_i541];
  }

  for (c4_i542 = 0; c4_i542 < 3; c4_i542 = c4_i542 + 1) {
    c4_b_w1[c4_i542] = c4_w1[c4_i542];
  }

  c4_cross(chartInstance, c4_b_velociy1, c4_b_w1, c4_dv30);
  for (c4_i543 = 0; c4_i543 < 3; c4_i543 = c4_i543 + 1) {
    c4_r1[c4_i543] = -c4_dv30[c4_i543];
  }

  /*  one point in w1 axis */
  _SFD_SCRIPT_CALL(6, 13);
  for (c4_i544 = 0; c4_i544 < 3; c4_i544 = c4_i544 + 1) {
    c4_velociy2[c4_i544] = c4_kx2[c4_i544];
  }

  _SFD_SCRIPT_CALL(6, 14);
  for (c4_i545 = 0; c4_i545 < 3; c4_i545 = c4_i545 + 1) {
    c4_w2[c4_i545] = c4_kx2[c4_i545 + 3];
  }

  /*  rotation axis for twist2 */
  _SFD_SCRIPT_CALL(6, 15);
  for (c4_i546 = 0; c4_i546 < 3; c4_i546 = c4_i546 + 1) {
    c4_b_velociy2[c4_i546] = c4_velociy2[c4_i546];
  }

  for (c4_i547 = 0; c4_i547 < 3; c4_i547 = c4_i547 + 1) {
    c4_b_w2[c4_i547] = c4_w2[c4_i547];
  }

  c4_cross(chartInstance, c4_b_velociy2, c4_b_w2, c4_dv31);
  for (c4_i548 = 0; c4_i548 < 3; c4_i548 = c4_i548 + 1) {
    c4_r2[c4_i548] = -c4_dv31[c4_i548];
  }

  /*  one point in w2 axis */
  /* find the common point of two axis */
  _SFD_SCRIPT_CALL(6, 18);
  for (c4_i549 = 0; c4_i549 < 3; c4_i549 = c4_i549 + 1) {
    c4_c_w1[c4_i549] = c4_w1[c4_i549];
  }

  for (c4_i550 = 0; c4_i550 < 3; c4_i550 = c4_i550 + 1) {
    c4_c_w2[c4_i550] = c4_w2[c4_i550];
  }

  for (c4_i551 = 0; c4_i551 < 3; c4_i551 = c4_i551 + 1) {
    c4_b_r1[c4_i551] = c4_r1[c4_i551];
  }

  for (c4_i552 = 0; c4_i552 < 3; c4_i552 = c4_i552 + 1) {
    c4_b_r2[c4_i552] = c4_r2[c4_i552];
  }

  c4_findCommon(chartInstance, c4_c_w1, c4_c_w2, c4_b_r1, c4_b_r2, c4_dv32);
  for (c4_i553 = 0; c4_i553 < 3; c4_i553 = c4_i553 + 1) {
    c4_r[c4_i553] = c4_dv32[c4_i553];
  }

  _SFD_SCRIPT_CALL(6, 20);
  for (c4_i554 = 0; c4_i554 < 3; c4_i554 = c4_i554 + 1) {
    c4_u[c4_i554] = c4_p[c4_i554] - c4_r[c4_i554];
  }

  _SFD_SCRIPT_CALL(6, 21);
  for (c4_i555 = 0; c4_i555 < 3; c4_i555 = c4_i555 + 1) {
    c4_v[c4_i555] = c4_q[c4_i555] - c4_r[c4_i555];
  }

  _SFD_SCRIPT_CALL(6, 23);
  for (c4_i556 = 0; c4_i556 < 3; c4_i556 = c4_i556 + 1) {
    c4_a[c4_i556] = c4_w1[c4_i556];
  }

  for (c4_i557 = 0; c4_i557 < 3; c4_i557 = c4_i557 + 1) {
    c4_b[c4_i557] = c4_w2[c4_i557];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i558 = 0; c4_i558 < 3; c4_i558 = c4_i558 + 1) {
    c4_x[c4_i558] = c4_a[c4_i558];
  }

  for (c4_i559 = 0; c4_i559 < 3; c4_i559 = c4_i559 + 1) {
    c4_b_y[c4_i559] = c4_b[c4_i559];
  }

  for (c4_i560 = 0; c4_i560 < 3; c4_i560 = c4_i560 + 1) {
    c4_b_x[c4_i560] = c4_x[c4_i560];
  }

  for (c4_i561 = 0; c4_i561 < 3; c4_i561 = c4_i561 + 1) {
    c4_c_y[c4_i561] = c4_b_y[c4_i561];
  }

  for (c4_i562 = 0; c4_i562 < 3; c4_i562 = c4_i562 + 1) {
    c4_c_x[c4_i562] = c4_b_x[c4_i562];
  }

  for (c4_i563 = 0; c4_i563 < 3; c4_i563 = c4_i563 + 1) {
    c4_d_y[c4_i563] = c4_c_y[c4_i563];
  }

  for (c4_i564 = 0; c4_i564 < 3; c4_i564 = c4_i564 + 1) {
    c4_d_x[c4_i564] = c4_c_x[c4_i564];
  }

  for (c4_i565 = 0; c4_i565 < 3; c4_i565 = c4_i565 + 1) {
    c4_e_y[c4_i565] = c4_d_y[c4_i565];
  }

  c4_f_y = c4_ceval_xdot(chartInstance, 3, c4_d_x, 1, 1, c4_e_y, 1, 1);
  c4_b_a = c4_f_y;
  for (c4_i566 = 0; c4_i566 < 3; c4_i566 = c4_i566 + 1) {
    c4_b_b[c4_i566] = c4_w2[c4_i566];
  }

  for (c4_i567 = 0; c4_i567 < 3; c4_i567 = c4_i567 + 1) {
    c4_g_y[c4_i567] = c4_b_a * c4_b_b[c4_i567];
  }

  for (c4_i568 = 0; c4_i568 < 3; c4_i568 = c4_i568 + 1) {
    c4_c_a[c4_i568] = c4_g_y[c4_i568];
  }

  for (c4_i569 = 0; c4_i569 < 3; c4_i569 = c4_i569 + 1) {
    c4_c_b[c4_i569] = c4_u[c4_i569];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i570 = 0; c4_i570 < 3; c4_i570 = c4_i570 + 1) {
    c4_e_x[c4_i570] = c4_c_a[c4_i570];
  }

  for (c4_i571 = 0; c4_i571 < 3; c4_i571 = c4_i571 + 1) {
    c4_h_y[c4_i571] = c4_c_b[c4_i571];
  }

  for (c4_i572 = 0; c4_i572 < 3; c4_i572 = c4_i572 + 1) {
    c4_f_x[c4_i572] = c4_e_x[c4_i572];
  }

  for (c4_i573 = 0; c4_i573 < 3; c4_i573 = c4_i573 + 1) {
    c4_i_y[c4_i573] = c4_h_y[c4_i573];
  }

  for (c4_i574 = 0; c4_i574 < 3; c4_i574 = c4_i574 + 1) {
    c4_g_x[c4_i574] = c4_f_x[c4_i574];
  }

  for (c4_i575 = 0; c4_i575 < 3; c4_i575 = c4_i575 + 1) {
    c4_j_y[c4_i575] = c4_i_y[c4_i575];
  }

  for (c4_i576 = 0; c4_i576 < 3; c4_i576 = c4_i576 + 1) {
    c4_h_x[c4_i576] = c4_g_x[c4_i576];
  }

  for (c4_i577 = 0; c4_i577 < 3; c4_i577 = c4_i577 + 1) {
    c4_k_y[c4_i577] = c4_j_y[c4_i577];
  }

  c4_l_y = c4_ceval_xdot(chartInstance, 3, c4_h_x, 1, 1, c4_k_y, 1, 1);
  for (c4_i578 = 0; c4_i578 < 3; c4_i578 = c4_i578 + 1) {
    c4_d_a[c4_i578] = c4_w1[c4_i578];
  }

  for (c4_i579 = 0; c4_i579 < 3; c4_i579 = c4_i579 + 1) {
    c4_d_b[c4_i579] = c4_v[c4_i579];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i580 = 0; c4_i580 < 3; c4_i580 = c4_i580 + 1) {
    c4_i_x[c4_i580] = c4_d_a[c4_i580];
  }

  for (c4_i581 = 0; c4_i581 < 3; c4_i581 = c4_i581 + 1) {
    c4_m_y[c4_i581] = c4_d_b[c4_i581];
  }

  for (c4_i582 = 0; c4_i582 < 3; c4_i582 = c4_i582 + 1) {
    c4_j_x[c4_i582] = c4_i_x[c4_i582];
  }

  for (c4_i583 = 0; c4_i583 < 3; c4_i583 = c4_i583 + 1) {
    c4_n_y[c4_i583] = c4_m_y[c4_i583];
  }

  for (c4_i584 = 0; c4_i584 < 3; c4_i584 = c4_i584 + 1) {
    c4_k_x[c4_i584] = c4_j_x[c4_i584];
  }

  for (c4_i585 = 0; c4_i585 < 3; c4_i585 = c4_i585 + 1) {
    c4_o_y[c4_i585] = c4_n_y[c4_i585];
  }

  for (c4_i586 = 0; c4_i586 < 3; c4_i586 = c4_i586 + 1) {
    c4_l_x[c4_i586] = c4_k_x[c4_i586];
  }

  for (c4_i587 = 0; c4_i587 < 3; c4_i587 = c4_i587 + 1) {
    c4_p_y[c4_i587] = c4_o_y[c4_i587];
  }

  c4_q_y = c4_ceval_xdot(chartInstance, 3, c4_l_x, 1, 1, c4_p_y, 1, 1);
  for (c4_i588 = 0; c4_i588 < 3; c4_i588 = c4_i588 + 1) {
    c4_e_a[c4_i588] = c4_w1[c4_i588];
  }

  for (c4_i589 = 0; c4_i589 < 3; c4_i589 = c4_i589 + 1) {
    c4_e_b[c4_i589] = c4_w2[c4_i589];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i590 = 0; c4_i590 < 3; c4_i590 = c4_i590 + 1) {
    c4_m_x[c4_i590] = c4_e_a[c4_i590];
  }

  for (c4_i591 = 0; c4_i591 < 3; c4_i591 = c4_i591 + 1) {
    c4_r_y[c4_i591] = c4_e_b[c4_i591];
  }

  for (c4_i592 = 0; c4_i592 < 3; c4_i592 = c4_i592 + 1) {
    c4_n_x[c4_i592] = c4_m_x[c4_i592];
  }

  for (c4_i593 = 0; c4_i593 < 3; c4_i593 = c4_i593 + 1) {
    c4_s_y[c4_i593] = c4_r_y[c4_i593];
  }

  for (c4_i594 = 0; c4_i594 < 3; c4_i594 = c4_i594 + 1) {
    c4_o_x[c4_i594] = c4_n_x[c4_i594];
  }

  for (c4_i595 = 0; c4_i595 < 3; c4_i595 = c4_i595 + 1) {
    c4_t_y[c4_i595] = c4_s_y[c4_i595];
  }

  for (c4_i596 = 0; c4_i596 < 3; c4_i596 = c4_i596 + 1) {
    c4_p_x[c4_i596] = c4_o_x[c4_i596];
  }

  for (c4_i597 = 0; c4_i597 < 3; c4_i597 = c4_i597 + 1) {
    c4_u_y[c4_i597] = c4_t_y[c4_i597];
  }

  c4_v_y = c4_ceval_xdot(chartInstance, 3, c4_p_x, 1, 1, c4_u_y, 1, 1);
  for (c4_i598 = 0; c4_i598 < 3; c4_i598 = c4_i598 + 1) {
    c4_f_a[c4_i598] = c4_w1[c4_i598];
  }

  for (c4_i599 = 0; c4_i599 < 3; c4_i599 = c4_i599 + 1) {
    c4_f_b[c4_i599] = c4_w2[c4_i599];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i600 = 0; c4_i600 < 3; c4_i600 = c4_i600 + 1) {
    c4_q_x[c4_i600] = c4_f_a[c4_i600];
  }

  for (c4_i601 = 0; c4_i601 < 3; c4_i601 = c4_i601 + 1) {
    c4_w_y[c4_i601] = c4_f_b[c4_i601];
  }

  for (c4_i602 = 0; c4_i602 < 3; c4_i602 = c4_i602 + 1) {
    c4_r_x[c4_i602] = c4_q_x[c4_i602];
  }

  for (c4_i603 = 0; c4_i603 < 3; c4_i603 = c4_i603 + 1) {
    c4_x_y[c4_i603] = c4_w_y[c4_i603];
  }

  for (c4_i604 = 0; c4_i604 < 3; c4_i604 = c4_i604 + 1) {
    c4_s_x[c4_i604] = c4_r_x[c4_i604];
  }

  for (c4_i605 = 0; c4_i605 < 3; c4_i605 = c4_i605 + 1) {
    c4_y_y[c4_i605] = c4_x_y[c4_i605];
  }

  for (c4_i606 = 0; c4_i606 < 3; c4_i606 = c4_i606 + 1) {
    c4_t_x[c4_i606] = c4_s_x[c4_i606];
  }

  for (c4_i607 = 0; c4_i607 < 3; c4_i607 = c4_i607 + 1) {
    c4_ab_y[c4_i607] = c4_y_y[c4_i607];
  }

  c4_bb_y = c4_ceval_xdot(chartInstance, 3, c4_t_x, 1, 1, c4_ab_y, 1, 1);
  c4_g_a = c4_v_y;
  c4_g_b = c4_bb_y;
  c4_cb_y = c4_g_a * c4_g_b;
  c4_A = c4_l_y - c4_q_y;
  c4_B = c4_cb_y - 1.0;
  c4_u_x = c4_A;
  c4_db_y = c4_B;
  c4_v_x = c4_u_x;
  c4_eb_y = c4_db_y;
  c4_w_x = c4_v_x;
  c4_fb_y = c4_eb_y;
  c4_alpha = c4_w_x / c4_fb_y;
  _SFD_SCRIPT_CALL(6, 24);
  for (c4_i608 = 0; c4_i608 < 3; c4_i608 = c4_i608 + 1) {
    c4_h_a[c4_i608] = c4_w1[c4_i608];
  }

  for (c4_i609 = 0; c4_i609 < 3; c4_i609 = c4_i609 + 1) {
    c4_h_b[c4_i609] = c4_w2[c4_i609];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i610 = 0; c4_i610 < 3; c4_i610 = c4_i610 + 1) {
    c4_x_x[c4_i610] = c4_h_a[c4_i610];
  }

  for (c4_i611 = 0; c4_i611 < 3; c4_i611 = c4_i611 + 1) {
    c4_gb_y[c4_i611] = c4_h_b[c4_i611];
  }

  for (c4_i612 = 0; c4_i612 < 3; c4_i612 = c4_i612 + 1) {
    c4_y_x[c4_i612] = c4_x_x[c4_i612];
  }

  for (c4_i613 = 0; c4_i613 < 3; c4_i613 = c4_i613 + 1) {
    c4_hb_y[c4_i613] = c4_gb_y[c4_i613];
  }

  for (c4_i614 = 0; c4_i614 < 3; c4_i614 = c4_i614 + 1) {
    c4_ab_x[c4_i614] = c4_y_x[c4_i614];
  }

  for (c4_i615 = 0; c4_i615 < 3; c4_i615 = c4_i615 + 1) {
    c4_ib_y[c4_i615] = c4_hb_y[c4_i615];
  }

  for (c4_i616 = 0; c4_i616 < 3; c4_i616 = c4_i616 + 1) {
    c4_bb_x[c4_i616] = c4_ab_x[c4_i616];
  }

  for (c4_i617 = 0; c4_i617 < 3; c4_i617 = c4_i617 + 1) {
    c4_jb_y[c4_i617] = c4_ib_y[c4_i617];
  }

  c4_kb_y = c4_ceval_xdot(chartInstance, 3, c4_bb_x, 1, 1, c4_jb_y, 1, 1);
  c4_i_a = c4_kb_y;
  for (c4_i618 = 0; c4_i618 < 3; c4_i618 = c4_i618 + 1) {
    c4_i_b[c4_i618] = c4_w1[c4_i618];
  }

  for (c4_i619 = 0; c4_i619 < 3; c4_i619 = c4_i619 + 1) {
    c4_lb_y[c4_i619] = c4_i_a * c4_i_b[c4_i619];
  }

  for (c4_i620 = 0; c4_i620 < 3; c4_i620 = c4_i620 + 1) {
    c4_j_a[c4_i620] = c4_lb_y[c4_i620];
  }

  for (c4_i621 = 0; c4_i621 < 3; c4_i621 = c4_i621 + 1) {
    c4_j_b[c4_i621] = c4_v[c4_i621];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i622 = 0; c4_i622 < 3; c4_i622 = c4_i622 + 1) {
    c4_cb_x[c4_i622] = c4_j_a[c4_i622];
  }

  for (c4_i623 = 0; c4_i623 < 3; c4_i623 = c4_i623 + 1) {
    c4_mb_y[c4_i623] = c4_j_b[c4_i623];
  }

  for (c4_i624 = 0; c4_i624 < 3; c4_i624 = c4_i624 + 1) {
    c4_db_x[c4_i624] = c4_cb_x[c4_i624];
  }

  for (c4_i625 = 0; c4_i625 < 3; c4_i625 = c4_i625 + 1) {
    c4_nb_y[c4_i625] = c4_mb_y[c4_i625];
  }

  for (c4_i626 = 0; c4_i626 < 3; c4_i626 = c4_i626 + 1) {
    c4_eb_x[c4_i626] = c4_db_x[c4_i626];
  }

  for (c4_i627 = 0; c4_i627 < 3; c4_i627 = c4_i627 + 1) {
    c4_ob_y[c4_i627] = c4_nb_y[c4_i627];
  }

  for (c4_i628 = 0; c4_i628 < 3; c4_i628 = c4_i628 + 1) {
    c4_fb_x[c4_i628] = c4_eb_x[c4_i628];
  }

  for (c4_i629 = 0; c4_i629 < 3; c4_i629 = c4_i629 + 1) {
    c4_pb_y[c4_i629] = c4_ob_y[c4_i629];
  }

  c4_qb_y = c4_ceval_xdot(chartInstance, 3, c4_fb_x, 1, 1, c4_pb_y, 1, 1);
  for (c4_i630 = 0; c4_i630 < 3; c4_i630 = c4_i630 + 1) {
    c4_k_a[c4_i630] = c4_w2[c4_i630];
  }

  for (c4_i631 = 0; c4_i631 < 3; c4_i631 = c4_i631 + 1) {
    c4_k_b[c4_i631] = c4_u[c4_i631];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i632 = 0; c4_i632 < 3; c4_i632 = c4_i632 + 1) {
    c4_gb_x[c4_i632] = c4_k_a[c4_i632];
  }

  for (c4_i633 = 0; c4_i633 < 3; c4_i633 = c4_i633 + 1) {
    c4_rb_y[c4_i633] = c4_k_b[c4_i633];
  }

  for (c4_i634 = 0; c4_i634 < 3; c4_i634 = c4_i634 + 1) {
    c4_hb_x[c4_i634] = c4_gb_x[c4_i634];
  }

  for (c4_i635 = 0; c4_i635 < 3; c4_i635 = c4_i635 + 1) {
    c4_sb_y[c4_i635] = c4_rb_y[c4_i635];
  }

  for (c4_i636 = 0; c4_i636 < 3; c4_i636 = c4_i636 + 1) {
    c4_ib_x[c4_i636] = c4_hb_x[c4_i636];
  }

  for (c4_i637 = 0; c4_i637 < 3; c4_i637 = c4_i637 + 1) {
    c4_tb_y[c4_i637] = c4_sb_y[c4_i637];
  }

  for (c4_i638 = 0; c4_i638 < 3; c4_i638 = c4_i638 + 1) {
    c4_jb_x[c4_i638] = c4_ib_x[c4_i638];
  }

  for (c4_i639 = 0; c4_i639 < 3; c4_i639 = c4_i639 + 1) {
    c4_ub_y[c4_i639] = c4_tb_y[c4_i639];
  }

  c4_vb_y = c4_ceval_xdot(chartInstance, 3, c4_jb_x, 1, 1, c4_ub_y, 1, 1);
  for (c4_i640 = 0; c4_i640 < 3; c4_i640 = c4_i640 + 1) {
    c4_l_a[c4_i640] = c4_w1[c4_i640];
  }

  for (c4_i641 = 0; c4_i641 < 3; c4_i641 = c4_i641 + 1) {
    c4_l_b[c4_i641] = c4_w2[c4_i641];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i642 = 0; c4_i642 < 3; c4_i642 = c4_i642 + 1) {
    c4_kb_x[c4_i642] = c4_l_a[c4_i642];
  }

  for (c4_i643 = 0; c4_i643 < 3; c4_i643 = c4_i643 + 1) {
    c4_wb_y[c4_i643] = c4_l_b[c4_i643];
  }

  for (c4_i644 = 0; c4_i644 < 3; c4_i644 = c4_i644 + 1) {
    c4_lb_x[c4_i644] = c4_kb_x[c4_i644];
  }

  for (c4_i645 = 0; c4_i645 < 3; c4_i645 = c4_i645 + 1) {
    c4_xb_y[c4_i645] = c4_wb_y[c4_i645];
  }

  for (c4_i646 = 0; c4_i646 < 3; c4_i646 = c4_i646 + 1) {
    c4_mb_x[c4_i646] = c4_lb_x[c4_i646];
  }

  for (c4_i647 = 0; c4_i647 < 3; c4_i647 = c4_i647 + 1) {
    c4_yb_y[c4_i647] = c4_xb_y[c4_i647];
  }

  for (c4_i648 = 0; c4_i648 < 3; c4_i648 = c4_i648 + 1) {
    c4_nb_x[c4_i648] = c4_mb_x[c4_i648];
  }

  for (c4_i649 = 0; c4_i649 < 3; c4_i649 = c4_i649 + 1) {
    c4_ac_y[c4_i649] = c4_yb_y[c4_i649];
  }

  c4_bc_y = c4_ceval_xdot(chartInstance, 3, c4_nb_x, 1, 1, c4_ac_y, 1, 1);
  for (c4_i650 = 0; c4_i650 < 3; c4_i650 = c4_i650 + 1) {
    c4_m_a[c4_i650] = c4_w1[c4_i650];
  }

  for (c4_i651 = 0; c4_i651 < 3; c4_i651 = c4_i651 + 1) {
    c4_m_b[c4_i651] = c4_w2[c4_i651];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i652 = 0; c4_i652 < 3; c4_i652 = c4_i652 + 1) {
    c4_ob_x[c4_i652] = c4_m_a[c4_i652];
  }

  for (c4_i653 = 0; c4_i653 < 3; c4_i653 = c4_i653 + 1) {
    c4_cc_y[c4_i653] = c4_m_b[c4_i653];
  }

  for (c4_i654 = 0; c4_i654 < 3; c4_i654 = c4_i654 + 1) {
    c4_pb_x[c4_i654] = c4_ob_x[c4_i654];
  }

  for (c4_i655 = 0; c4_i655 < 3; c4_i655 = c4_i655 + 1) {
    c4_dc_y[c4_i655] = c4_cc_y[c4_i655];
  }

  for (c4_i656 = 0; c4_i656 < 3; c4_i656 = c4_i656 + 1) {
    c4_qb_x[c4_i656] = c4_pb_x[c4_i656];
  }

  for (c4_i657 = 0; c4_i657 < 3; c4_i657 = c4_i657 + 1) {
    c4_ec_y[c4_i657] = c4_dc_y[c4_i657];
  }

  for (c4_i658 = 0; c4_i658 < 3; c4_i658 = c4_i658 + 1) {
    c4_rb_x[c4_i658] = c4_qb_x[c4_i658];
  }

  for (c4_i659 = 0; c4_i659 < 3; c4_i659 = c4_i659 + 1) {
    c4_fc_y[c4_i659] = c4_ec_y[c4_i659];
  }

  c4_gc_y = c4_ceval_xdot(chartInstance, 3, c4_rb_x, 1, 1, c4_fc_y, 1, 1);
  c4_n_a = c4_bc_y;
  c4_n_b = c4_gc_y;
  c4_hc_y = c4_n_a * c4_n_b;
  c4_b_A = c4_qb_y - c4_vb_y;
  c4_b_B = c4_hc_y - 1.0;
  c4_sb_x = c4_b_A;
  c4_ic_y = c4_b_B;
  c4_tb_x = c4_sb_x;
  c4_jc_y = c4_ic_y;
  c4_ub_x = c4_tb_x;
  c4_kc_y = c4_jc_y;
  c4_beta = c4_ub_x / c4_kc_y;
  _SFD_SCRIPT_CALL(6, 26);
  for (c4_i660 = 0; c4_i660 < 3; c4_i660 = c4_i660 + 1) {
    c4_o_a[c4_i660] = c4_u[c4_i660];
  }

  for (c4_i661 = 0; c4_i661 < 3; c4_i661 = c4_i661 + 1) {
    c4_o_b[c4_i661] = c4_u[c4_i661];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i662 = 0; c4_i662 < 3; c4_i662 = c4_i662 + 1) {
    c4_vb_x[c4_i662] = c4_o_a[c4_i662];
  }

  for (c4_i663 = 0; c4_i663 < 3; c4_i663 = c4_i663 + 1) {
    c4_lc_y[c4_i663] = c4_o_b[c4_i663];
  }

  for (c4_i664 = 0; c4_i664 < 3; c4_i664 = c4_i664 + 1) {
    c4_wb_x[c4_i664] = c4_vb_x[c4_i664];
  }

  for (c4_i665 = 0; c4_i665 < 3; c4_i665 = c4_i665 + 1) {
    c4_mc_y[c4_i665] = c4_lc_y[c4_i665];
  }

  for (c4_i666 = 0; c4_i666 < 3; c4_i666 = c4_i666 + 1) {
    c4_xb_x[c4_i666] = c4_wb_x[c4_i666];
  }

  for (c4_i667 = 0; c4_i667 < 3; c4_i667 = c4_i667 + 1) {
    c4_nc_y[c4_i667] = c4_mc_y[c4_i667];
  }

  for (c4_i668 = 0; c4_i668 < 3; c4_i668 = c4_i668 + 1) {
    c4_yb_x[c4_i668] = c4_xb_x[c4_i668];
  }

  for (c4_i669 = 0; c4_i669 < 3; c4_i669 = c4_i669 + 1) {
    c4_oc_y[c4_i669] = c4_nc_y[c4_i669];
  }

  c4_pc_y = c4_ceval_xdot(chartInstance, 3, c4_yb_x, 1, 1, c4_oc_y, 1, 1);
  c4_p_a = c4_alpha;
  c4_p_b = c4_alpha;
  c4_qc_y = c4_p_a * c4_p_b;
  c4_q_a = c4_beta;
  c4_q_b = c4_beta;
  c4_rc_y = c4_q_a * c4_q_b;
  c4_r_b = c4_beta;
  c4_sc_y = 2.0 * c4_r_b;
  c4_r_a = c4_sc_y;
  c4_s_b = c4_alpha;
  c4_tc_y = c4_r_a * c4_s_b;
  c4_s_a = c4_tc_y;
  for (c4_i670 = 0; c4_i670 < 3; c4_i670 = c4_i670 + 1) {
    c4_t_b[c4_i670] = c4_w1[c4_i670];
  }

  for (c4_i671 = 0; c4_i671 < 3; c4_i671 = c4_i671 + 1) {
    c4_uc_y[c4_i671] = c4_s_a * c4_t_b[c4_i671];
  }

  for (c4_i672 = 0; c4_i672 < 3; c4_i672 = c4_i672 + 1) {
    c4_t_a[c4_i672] = c4_uc_y[c4_i672];
  }

  for (c4_i673 = 0; c4_i673 < 3; c4_i673 = c4_i673 + 1) {
    c4_u_b[c4_i673] = c4_w2[c4_i673];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i674 = 0; c4_i674 < 3; c4_i674 = c4_i674 + 1) {
    c4_ac_x[c4_i674] = c4_t_a[c4_i674];
  }

  for (c4_i675 = 0; c4_i675 < 3; c4_i675 = c4_i675 + 1) {
    c4_vc_y[c4_i675] = c4_u_b[c4_i675];
  }

  for (c4_i676 = 0; c4_i676 < 3; c4_i676 = c4_i676 + 1) {
    c4_bc_x[c4_i676] = c4_ac_x[c4_i676];
  }

  for (c4_i677 = 0; c4_i677 < 3; c4_i677 = c4_i677 + 1) {
    c4_wc_y[c4_i677] = c4_vc_y[c4_i677];
  }

  for (c4_i678 = 0; c4_i678 < 3; c4_i678 = c4_i678 + 1) {
    c4_cc_x[c4_i678] = c4_bc_x[c4_i678];
  }

  for (c4_i679 = 0; c4_i679 < 3; c4_i679 = c4_i679 + 1) {
    c4_xc_y[c4_i679] = c4_wc_y[c4_i679];
  }

  for (c4_i680 = 0; c4_i680 < 3; c4_i680 = c4_i680 + 1) {
    c4_dc_x[c4_i680] = c4_cc_x[c4_i680];
  }

  for (c4_i681 = 0; c4_i681 < 3; c4_i681 = c4_i681 + 1) {
    c4_yc_y[c4_i681] = c4_xc_y[c4_i681];
  }

  c4_ad_y = c4_ceval_xdot(chartInstance, 3, c4_dc_x, 1, 1, c4_yc_y, 1, 1);
  for (c4_i682 = 0; c4_i682 < 3; c4_i682 = c4_i682 + 1) {
    c4_d_w1[c4_i682] = c4_w1[c4_i682];
  }

  for (c4_i683 = 0; c4_i683 < 3; c4_i683 = c4_i683 + 1) {
    c4_d_w2[c4_i683] = c4_w2[c4_i683];
  }

  c4_cross(chartInstance, c4_d_w1, c4_d_w2, c4_dv33);
  for (c4_i684 = 0; c4_i684 < 3; c4_i684 = c4_i684 + 1) {
    c4_u_a[c4_i684] = c4_dv33[c4_i684];
  }

  for (c4_i685 = 0; c4_i685 < 3; c4_i685 = c4_i685 + 1) {
    c4_e_w1[c4_i685] = c4_w1[c4_i685];
  }

  for (c4_i686 = 0; c4_i686 < 3; c4_i686 = c4_i686 + 1) {
    c4_e_w2[c4_i686] = c4_w2[c4_i686];
  }

  c4_cross(chartInstance, c4_e_w1, c4_e_w2, c4_v_b);
  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i687 = 0; c4_i687 < 3; c4_i687 = c4_i687 + 1) {
    c4_ec_x[c4_i687] = c4_u_a[c4_i687];
  }

  for (c4_i688 = 0; c4_i688 < 3; c4_i688 = c4_i688 + 1) {
    c4_bd_y[c4_i688] = c4_v_b[c4_i688];
  }

  for (c4_i689 = 0; c4_i689 < 3; c4_i689 = c4_i689 + 1) {
    c4_fc_x[c4_i689] = c4_ec_x[c4_i689];
  }

  for (c4_i690 = 0; c4_i690 < 3; c4_i690 = c4_i690 + 1) {
    c4_cd_y[c4_i690] = c4_bd_y[c4_i690];
  }

  for (c4_i691 = 0; c4_i691 < 3; c4_i691 = c4_i691 + 1) {
    c4_gc_x[c4_i691] = c4_fc_x[c4_i691];
  }

  for (c4_i692 = 0; c4_i692 < 3; c4_i692 = c4_i692 + 1) {
    c4_dd_y[c4_i692] = c4_cd_y[c4_i692];
  }

  for (c4_i693 = 0; c4_i693 < 3; c4_i693 = c4_i693 + 1) {
    c4_hc_x[c4_i693] = c4_gc_x[c4_i693];
  }

  for (c4_i694 = 0; c4_i694 < 3; c4_i694 = c4_i694 + 1) {
    c4_ed_y[c4_i694] = c4_dd_y[c4_i694];
  }

  c4_fd_y = c4_ceval_xdot(chartInstance, 3, c4_hc_x, 1, 1, c4_ed_y, 1, 1);
  c4_c_A = ((c4_pc_y - c4_qc_y) - c4_rc_y) - c4_ad_y;
  c4_c_B = c4_fd_y;
  c4_ic_x = c4_c_A;
  c4_gd_y = c4_c_B;
  c4_jc_x = c4_ic_x;
  c4_hd_y = c4_gd_y;
  c4_kc_x = c4_jc_x;
  c4_id_y = c4_hd_y;
  c4_ySqu = c4_kc_x / c4_id_y;
  _SFD_SCRIPT_CALL(6, 28);
  if (CV_SCRIPT_IF(6, 0, c4_ySqu > 0.0)) {
    _SFD_SCRIPT_CALL(6, 29);
    *c4_Nsol = 2.0;
  } else {
    _SFD_SCRIPT_CALL(6, 30);
    if (CV_SCRIPT_IF(6, 1, c4_ySqu == 0.0)) {
      _SFD_SCRIPT_CALL(6, 31);
      *c4_Nsol = 1.0;
    } else {
      _SFD_SCRIPT_CALL(6, 33);
      *c4_Nsol = 0.0;
    }
  }

  _SFD_SCRIPT_CALL(6, 36);
  if (CV_SCRIPT_IF(6, 2, c4_ySqu >= 0.0)) {
    c4_i = 1.0;
    c4_b_i = 1.0;
    while (c4_b_i <= 2.0) {
      c4_i = c4_b_i;
      CV_SCRIPT_FOR(6, 0, 1);
      _SFD_SCRIPT_CALL(6, 39);
      c4_w_b = c4_i;
      c4_jd_y = 2.0 * c4_w_b;
      c4_lc_x = c4_ySqu;
      c4_mc_x = c4_lc_x;
      if (c4_mc_x < 0.0) {
        c4_c_eml_error(chartInstance);
      }

      c4_nc_x = c4_mc_x;
      c4_mc_x = c4_nc_x;
      c4_mc_x = muDoubleScalarSqrt(c4_mc_x);
      c4_v_a = c4_jd_y - 3.0;
      c4_x_b = c4_mc_x;
      c4_y = c4_v_a * c4_x_b;

      /*  could have two solutions in this step */
      _SFD_SCRIPT_CALL(6, 41);
      c4_w_a = c4_alpha;
      for (c4_i695 = 0; c4_i695 < 3; c4_i695 = c4_i695 + 1) {
        c4_y_b[c4_i695] = c4_w1[c4_i695];
      }

      for (c4_i696 = 0; c4_i696 < 3; c4_i696 = c4_i696 + 1) {
        c4_kd_y[c4_i696] = c4_w_a * c4_y_b[c4_i696];
      }

      c4_x_a = c4_beta;
      for (c4_i697 = 0; c4_i697 < 3; c4_i697 = c4_i697 + 1) {
        c4_ab_b[c4_i697] = c4_w2[c4_i697];
      }

      for (c4_i698 = 0; c4_i698 < 3; c4_i698 = c4_i698 + 1) {
        c4_ld_y[c4_i698] = c4_x_a * c4_ab_b[c4_i698];
      }

      c4_y_a = c4_y;
      for (c4_i699 = 0; c4_i699 < 3; c4_i699 = c4_i699 + 1) {
        c4_f_w1[c4_i699] = c4_w1[c4_i699];
      }

      for (c4_i700 = 0; c4_i700 < 3; c4_i700 = c4_i700 + 1) {
        c4_f_w2[c4_i700] = c4_w2[c4_i700];
      }

      c4_cross(chartInstance, c4_f_w1, c4_f_w2, c4_bb_b);
      for (c4_i701 = 0; c4_i701 < 3; c4_i701 = c4_i701 + 1) {
        c4_md_y[c4_i701] = c4_y_a * c4_bb_b[c4_i701];
      }

      for (c4_i702 = 0; c4_i702 < 3; c4_i702 = c4_i702 + 1) {
        c4_z[c4_i702] = (c4_kd_y[c4_i702] + c4_ld_y[c4_i702]) - c4_md_y[c4_i702];
      }

      _SFD_SCRIPT_CALL(6, 43);
      for (c4_i703 = 0; c4_i703 < 3; c4_i703 = c4_i703 + 1) {
        c4_c[c4_i703] = c4_z[c4_i703] + c4_r[c4_i703];
      }

      /*  the common point in the rotation if there are solutions */
      _SFD_SCRIPT_CALL(6, 45);
      for (c4_i704 = 0; c4_i704 < 6; c4_i704 = c4_i704 + 1) {
        c4_b_kx2[c4_i704] = c4_kx2[c4_i704];
      }

      for (c4_i705 = 0; c4_i705 < 4; c4_i705 = c4_i705 + 1) {
        c4_b_p[c4_i705] = c4_p[c4_i705];
      }

      for (c4_i706 = 0; c4_i706 < 3; c4_i706 = c4_i706 + 1) {
        c4_b_c[c4_i706] = c4_c[c4_i706];
      }

      c4_theta2[_SFD_EML_ARRAY_BOUNDS_CHECK("theta2", (int32_T)
        _SFD_INTEGER_CHECK("i", c4_i), 1, 2, 1, 0) - 1] = c4_b_subPro1(
        chartInstance, c4_b_kx2, c4_b_p, c4_b_c);
      _SFD_SCRIPT_CALL(6, 46);
      for (c4_i707 = 0; c4_i707 < 6; c4_i707 = c4_i707 + 1) {
        c4_b_kx1[c4_i707] = c4_kx1[c4_i707];
      }

      for (c4_i708 = 0; c4_i708 < 3; c4_i708 = c4_i708 + 1) {
        c4_c_c[c4_i708] = c4_c[c4_i708];
      }

      for (c4_i709 = 0; c4_i709 < 4; c4_i709 = c4_i709 + 1) {
        c4_b_q[c4_i709] = c4_q[c4_i709];
      }

      c4_theta1[_SFD_EML_ARRAY_BOUNDS_CHECK("theta1", (int32_T)
        _SFD_INTEGER_CHECK("i", c4_i), 1, 2, 1, 0) - 1] = c4_c_subPro1(
        chartInstance, c4_b_kx1, c4_c_c, c4_b_q);
      c4_b_i = c4_b_i + 1.0;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_SCRIPT_FOR(6, 0, 0);
  }

  _SFD_SCRIPT_CALL(6, -46);
  sf_debug_symbol_scope_pop();
}

static void c4_findCommon(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
  real_T c4_w1[3], real_T c4_w2[3], real_T c4_r1[3]
  , real_T c4_r2[3], real_T c4_r[3])
{
  uint32_T c4_debug_family_var_map[10];
  real_T c4_A[4];
  real_T c4_vec[2];
  real_T c4_cof[2];
  real_T c4_nargin = 4.0;
  real_T c4_nargout = 1.0;
  real_T c4_b_r2[2];
  int32_T c4_i710;
  int32_T c4_i711;
  real_T c4_b_A[4];
  real_T c4_c_r2[2];
  int32_T c4_i712;
  int32_T c4_i713;
  real_T c4_c_A[4];
  real_T c4_d_r2[2];
  int32_T c4_i714;
  int32_T c4_i715;
  real_T c4_d_A[4];
  int32_T c4_i716;
  real_T c4_B[2];
  int32_T c4_i717;
  real_T c4_e_A[4];
  int32_T c4_i718;
  real_T c4_b_B[2];
  int32_T c4_i719;
  real_T c4_f_A[4];
  int32_T c4_i720;
  real_T c4_c_B[2];
  real_T c4_x;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_y;
  real_T c4_d_x;
  real_T c4_e_x;
  real_T c4_b_y;
  real_T c4_d;
  real_T c4_f_x;
  real_T c4_g_x;
  real_T c4_h_x;
  real_T c4_c_y;
  real_T c4_i_x;
  real_T c4_j_x;
  real_T c4_d_y;
  real_T c4_b_d;
  int32_T c4_b_r1;
  int32_T c4_e_r2;
  real_T c4_k_x;
  real_T c4_e_y;
  real_T c4_l_x;
  real_T c4_f_y;
  real_T c4_a21;
  real_T c4_a;
  real_T c4_b;
  real_T c4_g_y;
  real_T c4_a22;
  real_T c4_b_a;
  real_T c4_b_b;
  real_T c4_h_y;
  real_T c4_m_x;
  real_T c4_i_y;
  real_T c4_n_x;
  real_T c4_j_y;
  real_T c4_z;
  real_T c4_c_a;
  real_T c4_c_b;
  real_T c4_k_y;
  real_T c4_o_x;
  real_T c4_l_y;
  real_T c4_p_x;
  real_T c4_m_y;
  real_T c4_b_z;
  int32_T c4_i721;
  real_T c4_d_a[3];
  real_T c4_d_b;
  int32_T c4_i722;
  real_T c4_n_y[3];
  int32_T c4_i723;
  sf_debug_symbol_scope_push_eml(0U, 10U, 10U, c4_i_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_A, c4_l_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c4_vec, c4_i_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_cof, c4_i_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_w1, c4_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c4_w2, c4_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(c4_r1, c4_d_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(c4_r2, c4_d_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c4_r, c4_d_sf_marshall, 9U);
  CV_SCRIPT_FCN(6, 1);
  _SFD_SCRIPT_CALL(6, 56);
  c4_A[0] = c4_w1[0];
  c4_A[2] = -c4_w2[0];
  c4_A[1] = c4_w1[1];
  c4_A[3] = -c4_w2[1];
  _SFD_SCRIPT_CALL(6, 57);
  c4_b_r2[0] = c4_r2[0] - c4_r1[0];
  c4_b_r2[1] = c4_r2[1] - c4_r1[1];
  for (c4_i710 = 0; c4_i710 < 2; c4_i710 = c4_i710 + 1) {
    c4_vec[c4_i710] = c4_b_r2[c4_i710];
  }

  _SFD_SCRIPT_CALL(6, 59);
  for (c4_i711 = 0; c4_i711 < 4; c4_i711 = c4_i711 + 1) {
    c4_b_A[c4_i711] = c4_A[c4_i711];
  }

  if (CV_SCRIPT_IF(6, 3, c4_det(chartInstance, c4_b_A) == 0.0)) {
    /*  if the first two set of para are parallel */
    _SFD_SCRIPT_CALL(6, 60);
    c4_A[0] = c4_w1[0];
    c4_A[2] = -c4_w2[0];
    c4_A[1] = c4_w1[2];
    c4_A[3] = -c4_w2[2];
    _SFD_SCRIPT_CALL(6, 61);
    c4_c_r2[0] = c4_r2[0] - c4_r1[0];
    c4_c_r2[1] = c4_r2[2] - c4_r1[2];
    for (c4_i712 = 0; c4_i712 < 2; c4_i712 = c4_i712 + 1) {
      c4_vec[c4_i712] = c4_c_r2[c4_i712];
    }
  }

  _SFD_SCRIPT_CALL(6, 64);
  for (c4_i713 = 0; c4_i713 < 4; c4_i713 = c4_i713 + 1) {
    c4_c_A[c4_i713] = c4_A[c4_i713];
  }

  if (CV_SCRIPT_IF(6, 4, c4_det(chartInstance, c4_c_A) == 0.0)) {
    _SFD_SCRIPT_CALL(6, 65);
    c4_A[0] = c4_w1[1];
    c4_A[2] = -c4_w2[1];
    c4_A[1] = c4_w1[2];
    c4_A[3] = -c4_w2[2];
    _SFD_SCRIPT_CALL(6, 66);
    c4_d_r2[0] = c4_r2[1] - c4_r1[1];
    c4_d_r2[1] = c4_r2[2] - c4_r1[2];
    for (c4_i714 = 0; c4_i714 < 2; c4_i714 = c4_i714 + 1) {
      c4_vec[c4_i714] = c4_d_r2[c4_i714];
    }
  }

  _SFD_SCRIPT_CALL(6, 69);
  for (c4_i715 = 0; c4_i715 < 4; c4_i715 = c4_i715 + 1) {
    c4_d_A[c4_i715] = c4_A[c4_i715];
  }

  for (c4_i716 = 0; c4_i716 < 2; c4_i716 = c4_i716 + 1) {
    c4_B[c4_i716] = c4_vec[c4_i716];
  }

  for (c4_i717 = 0; c4_i717 < 4; c4_i717 = c4_i717 + 1) {
    c4_e_A[c4_i717] = c4_d_A[c4_i717];
  }

  for (c4_i718 = 0; c4_i718 < 2; c4_i718 = c4_i718 + 1) {
    c4_b_B[c4_i718] = c4_B[c4_i718];
  }

  for (c4_i719 = 0; c4_i719 < 4; c4_i719 = c4_i719 + 1) {
    c4_f_A[c4_i719] = c4_e_A[c4_i719];
  }

  for (c4_i720 = 0; c4_i720 < 2; c4_i720 = c4_i720 + 1) {
    c4_c_B[c4_i720] = c4_b_B[c4_i720];
  }

  c4_x = c4_f_A[1];
  c4_b_x = c4_x;
  c4_c_x = c4_b_x;
  c4_y = muDoubleScalarAbs(c4_c_x);
  c4_d_x = 0.0;
  c4_e_x = c4_d_x;
  c4_b_y = muDoubleScalarAbs(c4_e_x);
  c4_d = c4_y + c4_b_y;
  c4_f_x = c4_f_A[0];
  c4_g_x = c4_f_x;
  c4_h_x = c4_g_x;
  c4_c_y = muDoubleScalarAbs(c4_h_x);
  c4_i_x = 0.0;
  c4_j_x = c4_i_x;
  c4_d_y = muDoubleScalarAbs(c4_j_x);
  c4_b_d = c4_c_y + c4_d_y;
  if (c4_d > c4_b_d) {
    c4_b_r1 = 2;
    c4_e_r2 = 1;
  } else {
    c4_b_r1 = 1;
    c4_e_r2 = 2;
  }

  c4_k_x = c4_f_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_e_r2), 1, 2, 1, 0) - 1];
  c4_e_y = c4_f_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_b_r1), 1, 2, 1, 0) - 1];
  c4_l_x = c4_k_x;
  c4_f_y = c4_e_y;
  c4_a21 = c4_l_x / c4_f_y;
  c4_a = c4_a21;
  c4_b = c4_f_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_b_r1), 1, 2, 1, 0) + 1];
  c4_g_y = c4_a * c4_b;
  c4_a22 = c4_f_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_e_r2), 1, 2, 1, 0) + 1] - c4_g_y;
  if (c4_a22 == 0.0) {
  } else if (c4_f_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
               "", (real_T)c4_b_r1), 1, 2, 1, 0) - 1] == 0.0) {
  } else {
    goto label_1;
  }

  c4_eml_warning(chartInstance);
 label_1:
  ;
  c4_b_a = c4_c_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_b_r1), 1, 2, 1, 0) - 1];
  c4_b_b = c4_a21;
  c4_h_y = c4_b_a * c4_b_b;
  c4_m_x = c4_c_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_e_r2), 1, 2, 1, 0) - 1] - c4_h_y;
  c4_i_y = c4_a22;
  c4_n_x = c4_m_x;
  c4_j_y = c4_i_y;
  c4_z = c4_n_x / c4_j_y;
  c4_cof[1] = c4_z;
  c4_c_a = c4_cof[1];
  c4_c_b = c4_f_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_b_r1), 1, 2, 1, 0) + 1];
  c4_k_y = c4_c_a * c4_c_b;
  c4_o_x = c4_c_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_b_r1), 1, 2, 1, 0) - 1] - c4_k_y;
  c4_l_y = c4_f_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c4_b_r1), 1, 2, 1, 0) - 1];
  c4_p_x = c4_o_x;
  c4_m_y = c4_l_y;
  c4_b_z = c4_p_x / c4_m_y;
  c4_cof[0] = c4_b_z;

  /*  get the inverse */
  _SFD_SCRIPT_CALL(6, 71);
  for (c4_i721 = 0; c4_i721 < 3; c4_i721 = c4_i721 + 1) {
    c4_d_a[c4_i721] = c4_w1[c4_i721];
  }

  c4_d_b = c4_cof[0];
  for (c4_i722 = 0; c4_i722 < 3; c4_i722 = c4_i722 + 1) {
    c4_n_y[c4_i722] = c4_d_a[c4_i722] * c4_d_b;
  }

  for (c4_i723 = 0; c4_i723 < 3; c4_i723 = c4_i723 + 1) {
    c4_r[c4_i723] = c4_r1[c4_i723] + c4_n_y[c4_i723];
  }

  _SFD_SCRIPT_CALL(6, -71);
  sf_debug_symbol_scope_pop();
}

static real_T c4_det(SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance,
                     real_T c4_x[4])
{
  real_T c4_y;
  int32_T c4_i724;
  real_T c4_A[4];
  int32_T c4_i725;
  real_T c4_b_x[4];
  int32_T c4_i726;
  real_T c4_b_A[4];
  int32_T c4_i727;
  real_T c4_c_A[4];
  int32_T c4_i728;
  real_T c4_d_A[4];
  int32_T c4_info;
  int32_T c4_ipiv[2];
  real_T c4_e_A[4];
  int32_T c4_i729;
  int32_T c4_i730;
  int32_T c4_b_ipiv[2];
  int32_T c4_i731;
  int32_T c4_i732;
  int32_T c4_c_ipiv[2];
  int32_T c4_i733;
  int32_T c4_i734;
  int32_T c4_d_ipiv[2];
  real_T c4_a;
  real_T c4_b;
  boolean_T c4_isodd;
  for (c4_i724 = 0; c4_i724 < 4; c4_i724 = c4_i724 + 1) {
    c4_A[c4_i724] = c4_x[c4_i724];
  }

  for (c4_i725 = 0; c4_i725 < 4; c4_i725 = c4_i725 + 1) {
    c4_b_x[c4_i725] = c4_A[c4_i725];
  }

  for (c4_i726 = 0; c4_i726 < 4; c4_i726 = c4_i726 + 1) {
    c4_b_A[c4_i726] = c4_b_x[c4_i726];
  }

  for (c4_i727 = 0; c4_i727 < 4; c4_i727 = c4_i727 + 1) {
    c4_c_A[c4_i727] = c4_b_A[c4_i727];
  }

  for (c4_i728 = 0; c4_i728 < 4; c4_i728 = c4_i728 + 1) {
    c4_d_A[c4_i728] = c4_c_A[c4_i728];
  }

  c4_b_eml_matlab_zgetrf(chartInstance, c4_d_A, c4_e_A, c4_ipiv, &c4_info);
  for (c4_i729 = 0; c4_i729 < 4; c4_i729 = c4_i729 + 1) {
    c4_c_A[c4_i729] = c4_e_A[c4_i729];
  }

  for (c4_i730 = 0; c4_i730 < 2; c4_i730 = c4_i730 + 1) {
    c4_b_ipiv[c4_i730] = c4_ipiv[c4_i730];
  }

  for (c4_i731 = 0; c4_i731 < 4; c4_i731 = c4_i731 + 1) {
    c4_b_x[c4_i731] = c4_c_A[c4_i731];
  }

  for (c4_i732 = 0; c4_i732 < 2; c4_i732 = c4_i732 + 1) {
    c4_c_ipiv[c4_i732] = c4_b_ipiv[c4_i732];
  }

  for (c4_i733 = 0; c4_i733 < 4; c4_i733 = c4_i733 + 1) {
    c4_x[c4_i733] = c4_b_x[c4_i733];
  }

  for (c4_i734 = 0; c4_i734 < 2; c4_i734 = c4_i734 + 1) {
    c4_d_ipiv[c4_i734] = c4_c_ipiv[c4_i734];
  }

  c4_y = c4_x[0];
  c4_a = c4_y;
  c4_b = c4_x[3];
  c4_y = c4_a * c4_b;
  c4_isodd = FALSE;
  if ((real_T)c4_d_ipiv[0] > 1.0) {
    c4_isodd = TRUE;
  }

  if (c4_isodd) {
    return -c4_y;
  }

  return c4_y;
}

static void c4_b_eml_matlab_zgetrf(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_A[4], real_T c4_b_A[4], int32_T
  c4_ipiv[2], int32_T *c4_info)
{
  int32_T c4_i735;
  int32_T c4_i736;
  int32_T c4_i737;
  real_T c4_c_A[4];
  int32_T c4_a;
  int32_T c4_jpiv_offset;
  int32_T c4_b;
  int32_T c4_jpiv;
  int32_T c4_b_b;
  int32_T c4_c;
  int32_T c4_c_b;
  int32_T c4_jprow;
  int32_T c4_i738;
  real_T c4_x[4];
  int32_T c4_iy0;
  int32_T c4_i739;
  int32_T c4_i740;
  real_T c4_b_x[4];
  int32_T c4_b_iy0;
  int32_T c4_i741;
  real_T c4_c_x[4];
  int32_T c4_i742;
  real_T c4_d_x[4];
  real_T c4_e_x[4];
  int32_T c4_i743;
  int32_T c4_i744;
  real_T c4_f_x;
  real_T c4_y;
  real_T c4_g_x;
  real_T c4_b_y;
  real_T c4_z;
  int32_T c4_i745;
  real_T c4_d_A[4];
  int32_T c4_i746;
  int32_T c4_i747;
  real_T c4_e_A[4];
  int32_T c4_i748;
  int32_T c4_i749;
  real_T c4_f_A[4];
  int32_T c4_i750;
  int32_T c4_i751;
  real_T c4_g_A[4];
  for (c4_i735 = 0; c4_i735 < 4; c4_i735 = c4_i735 + 1) {
    c4_b_A[c4_i735] = c4_A[c4_i735];
  }

  c4_eps(chartInstance);
  for (c4_i736 = 0; c4_i736 < 2; c4_i736 = c4_i736 + 1) {
    c4_ipiv[c4_i736] = 1 + c4_i736;
  }

  *c4_info = 0;
  for (c4_i737 = 0; c4_i737 < 4; c4_i737 = c4_i737 + 1) {
    c4_c_A[c4_i737] = c4_b_A[c4_i737];
  }

  c4_a = c4_b_eml_ixamax(chartInstance, c4_c_A);
  c4_jpiv_offset = c4_a - 1;
  c4_b = c4_jpiv_offset;
  c4_jpiv = 1 + c4_b;
  if (c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c4_jpiv), 1, 4, 1, 0) - 1] != 0.0) {
    if ((real_T)c4_jpiv_offset != 0.0) {
      c4_b_b = c4_jpiv_offset;
      c4_c = 1 + c4_b_b;
      c4_ipiv[0] = c4_c;
      c4_c_b = c4_jpiv_offset;
      c4_jprow = 1 + c4_c_b;
      for (c4_i738 = 0; c4_i738 < 4; c4_i738 = c4_i738 + 1) {
        c4_x[c4_i738] = c4_b_A[c4_i738];
      }

      c4_iy0 = c4_jprow;
      for (c4_i739 = 0; c4_i739 < 4; c4_i739 = c4_i739 + 1) {
        c4_b_A[c4_i739] = c4_x[c4_i739];
      }

      for (c4_i740 = 0; c4_i740 < 4; c4_i740 = c4_i740 + 1) {
        c4_b_x[c4_i740] = c4_b_A[c4_i740];
      }

      c4_b_iy0 = c4_iy0;
      for (c4_i741 = 0; c4_i741 < 4; c4_i741 = c4_i741 + 1) {
        c4_c_x[c4_i741] = c4_b_x[c4_i741];
      }

      for (c4_i742 = 0; c4_i742 < 4; c4_i742 = c4_i742 + 1) {
        c4_d_x[c4_i742] = c4_c_x[c4_i742];
      }

      c4_b_ceval_xswap(chartInstance, 2, c4_d_x, 1, 2, c4_b_iy0, 2, c4_e_x);
      for (c4_i743 = 0; c4_i743 < 4; c4_i743 = c4_i743 + 1) {
        c4_c_x[c4_i743] = c4_e_x[c4_i743];
      }

      for (c4_i744 = 0; c4_i744 < 4; c4_i744 = c4_i744 + 1) {
        c4_b_A[c4_i744] = c4_c_x[c4_i744];
      }
    }

    c4_f_x = c4_b_A[1];
    c4_y = c4_b_A[0];
    c4_g_x = c4_f_x;
    c4_b_y = c4_y;
    c4_z = c4_g_x / c4_b_y;
    c4_b_A[1] = c4_z;
  } else {
    *c4_info = 1;
  }

  for (c4_i745 = 0; c4_i745 < 4; c4_i745 = c4_i745 + 1) {
    c4_d_A[c4_i745] = c4_b_A[c4_i745];
  }

  for (c4_i746 = 0; c4_i746 < 4; c4_i746 = c4_i746 + 1) {
    c4_b_A[c4_i746] = c4_d_A[c4_i746];
  }

  for (c4_i747 = 0; c4_i747 < 4; c4_i747 = c4_i747 + 1) {
    c4_e_A[c4_i747] = c4_b_A[c4_i747];
  }

  for (c4_i748 = 0; c4_i748 < 4; c4_i748 = c4_i748 + 1) {
    c4_b_A[c4_i748] = c4_e_A[c4_i748];
  }

  for (c4_i749 = 0; c4_i749 < 4; c4_i749 = c4_i749 + 1) {
    c4_f_A[c4_i749] = c4_b_A[c4_i749];
  }

  for (c4_i750 = 0; c4_i750 < 4; c4_i750 = c4_i750 + 1) {
    c4_b_A[c4_i750] = c4_f_A[c4_i750];
  }

  for (c4_i751 = 0; c4_i751 < 4; c4_i751 = c4_i751 + 1) {
    c4_g_A[c4_i751] = c4_b_A[c4_i751];
  }

  c4_b_ceval_xger(chartInstance, 1, 1, -1.0, 2, 1, 3, 2, c4_g_A, 4, 2, c4_b_A);
  if ((real_T)*c4_info == 0.0) {
    if (!(c4_b_A[3] != 0.0)) {
      *c4_info = 2;
      return;
    }
  }
}

static int32_T c4_b_eml_ixamax(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_x[4])
{
  int32_T c4_i752;
  real_T c4_b_x[4];
  int32_T c4_i753;
  real_T c4_c_x[4];
  for (c4_i752 = 0; c4_i752 < 4; c4_i752 = c4_i752 + 1) {
    c4_b_x[c4_i752] = c4_x[c4_i752];
  }

  for (c4_i753 = 0; c4_i753 < 4; c4_i753 = c4_i753 + 1) {
    c4_c_x[c4_i753] = c4_b_x[c4_i753];
  }

  return c4_b_ceval_ixamax(chartInstance, 2, c4_c_x, 1, 1);
}

static int32_T c4_b_ceval_ixamax(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[4], int32_T
  c4_ix0, int32_T c4_incx)
{
  return idamax32(&c4_n, &c4_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c4_ix0), 1, 4, 1, 0) - 1], &
                  c4_incx);
}

static void c4_b_ceval_xswap(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_n, real_T c4_x[4], int32_T c4_ix0,
  int32_T c4_incx, int32_T c4_iy0, int32_T c4_incy, real_T c4_b_x[4])
{
  int32_T c4_i754;

  /* Empty Loop. */
  for (c4_i754 = 0; c4_i754 < 4; c4_i754 = c4_i754 + 1) {
    c4_b_x[c4_i754] = c4_x[c4_i754];
  }

  dswap32(&c4_n, &c4_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           _SFD_INTEGER_CHECK("", (real_T)c4_ix0), 1, 4, 1, 0) - 1], &c4_incx,
          &c4_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_iy0), 1, 4, 1, 0) - 1], &c4_incy);
}

static void c4_b_ceval_xger(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, int32_T c4_m, int32_T c4_n, real_T c4_alpha1,
  int32_T c4_ix0, int32_T c4_incx, int32_T c4_iy0, int32_T c4_incy, real_T c4_A
  [4], int32_T c4_ia0, int32_T c4_lda, real_T c4_b_A[4])
{
  int32_T c4_i755;
  for (c4_i755 = 0; c4_i755 < 4; c4_i755 = c4_i755 + 1) {
    c4_b_A[c4_i755] = c4_A[c4_i755];
  }

  dger32(&c4_m, &c4_n, &c4_alpha1, &c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c4_ix0), 1, 4, 1, 0
          ) - 1], &c4_incx, &c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_iy0), 1, 4, 1, 0) - 1], &
         c4_incy, &c4_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_ia0), 1, 4, 1, 0) - 1], &c4_lda);
}

static void c4_c_eml_error(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
  int32_T c4_i756;
  static char_T c4_cv6[31] = { 'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'q', 'r', 't', ':', 'd'
    , 'o', 'm', 'a', 'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c4_u[31];
  const mxArray *c4_y = NULL;
  int32_T c4_i757;
  static char_T c4_cv7[77] = { 'D', 'o', 'm', 'a', 'i', 'n', ' ', 'e', 'r', 'r',
    'o', 'r', '.', ' ', 'T', 'o', ' ', 'c', 'o', 'm', 'p'
    , 'u', 't', 'e', ' ', 'c', 'o', 'm', 'p', 'l', 'e', 'x', ' ', 'r', 'e', 's',
    'u', 'l', 't', 's', ' ',
    'f', 'r', 'o', 'm', ' ', 'r', 'e', 'a', 'l', ' ', 'x', ',', ' ', 'u', 's',
    'e', ' ', '\'', 's', 'q',
    'r', 't', '(', 'c', 'o', 'm', 'p', 'l', 'e', 'x', '(', 'x', ')', ')', '\'',
    '.' };

  char_T c4_b_u[77];
  const mxArray *c4_b_y = NULL;
  for (c4_i756 = 0; c4_i756 < 31; c4_i756 = c4_i756 + 1) {
    c4_u[c4_i756] = c4_cv6[c4_i756];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 31));
  for (c4_i757 = 0; c4_i757 < 77; c4_i757 = c4_i757 + 1) {
    c4_b_u[c4_i757] = c4_cv7[c4_i757];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 77));
  sf_mex_call_debug("error", 0U, 2U, 14, c4_y, 14, c4_b_y);
}

static real_T c4_b_subPro1(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_kx[6], real_T c4_p[4], real_T c4_q[3])
{
  real_T c4_theta;
  uint32_T c4_debug_family_var_map[13];
  real_T c4_velociy[3];
  real_T c4_w[3];
  real_T c4_r[3];
  real_T c4_u[3];
  real_T c4_v[3];
  real_T c4_up[3];
  real_T c4_vp[3];
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 1.0;
  int32_T c4_i758;
  int32_T c4_i759;
  int32_T c4_i760;
  real_T c4_b_velociy[3];
  int32_T c4_i761;
  real_T c4_b_w[3];
  real_T c4_dv34[3];
  int32_T c4_i762;
  int32_T c4_i763;
  int32_T c4_i764;
  int32_T c4_i765;
  real_T c4_a[3];
  int32_T c4_i766;
  real_T c4_b[3];
  int32_T c4_i767;
  real_T c4_x[3];
  int32_T c4_i768;
  real_T c4_y[3];
  int32_T c4_i769;
  real_T c4_b_x[3];
  int32_T c4_i770;
  real_T c4_b_y[3];
  int32_T c4_i771;
  real_T c4_c_x[3];
  int32_T c4_i772;
  real_T c4_c_y[3];
  int32_T c4_i773;
  real_T c4_d_x[3];
  int32_T c4_i774;
  real_T c4_d_y[3];
  real_T c4_e_y;
  int32_T c4_i775;
  real_T c4_b_a[3];
  real_T c4_b_b;
  int32_T c4_i776;
  real_T c4_f_y[3];
  int32_T c4_i777;
  int32_T c4_i778;
  real_T c4_c_a[3];
  int32_T c4_i779;
  real_T c4_c_b[3];
  int32_T c4_i780;
  real_T c4_e_x[3];
  int32_T c4_i781;
  real_T c4_g_y[3];
  int32_T c4_i782;
  real_T c4_f_x[3];
  int32_T c4_i783;
  real_T c4_h_y[3];
  int32_T c4_i784;
  real_T c4_g_x[3];
  int32_T c4_i785;
  real_T c4_i_y[3];
  int32_T c4_i786;
  real_T c4_h_x[3];
  int32_T c4_i787;
  real_T c4_j_y[3];
  real_T c4_k_y;
  int32_T c4_i788;
  real_T c4_d_a[3];
  real_T c4_d_b;
  int32_T c4_i789;
  real_T c4_l_y[3];
  int32_T c4_i790;
  int32_T c4_i791;
  real_T c4_e_a[3];
  int32_T c4_i792;
  real_T c4_b_up[3];
  int32_T c4_i793;
  real_T c4_b_vp[3];
  real_T c4_e_b[3];
  int32_T c4_i794;
  real_T c4_i_x[3];
  int32_T c4_i795;
  real_T c4_m_y[3];
  int32_T c4_i796;
  real_T c4_j_x[3];
  int32_T c4_i797;
  real_T c4_n_y[3];
  int32_T c4_i798;
  real_T c4_k_x[3];
  int32_T c4_i799;
  real_T c4_o_y[3];
  int32_T c4_i800;
  real_T c4_l_x[3];
  int32_T c4_i801;
  real_T c4_p_y[3];
  real_T c4_q_y;
  int32_T c4_i802;
  real_T c4_f_a[3];
  int32_T c4_i803;
  real_T c4_f_b[3];
  int32_T c4_i804;
  real_T c4_m_x[3];
  int32_T c4_i805;
  real_T c4_r_y[3];
  int32_T c4_i806;
  real_T c4_n_x[3];
  int32_T c4_i807;
  real_T c4_s_y[3];
  int32_T c4_i808;
  real_T c4_o_x[3];
  int32_T c4_i809;
  real_T c4_t_y[3];
  int32_T c4_i810;
  real_T c4_p_x[3];
  int32_T c4_i811;
  real_T c4_u_y[3];
  real_T c4_v_y;
  sf_debug_symbol_scope_push_eml(0U, 13U, 13U, c4_j_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_velociy, c4_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c4_w, c4_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_r, c4_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c4_u, c4_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c4_v, c4_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_up, c4_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c4_vp, c4_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c4_kx, c4_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(c4_p, c4_j_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(c4_q, c4_d_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c4_theta, c4_e_sf_marshall, 12U);
  CV_SCRIPT_FCN(5, 0);
  _SFD_SCRIPT_CALL(5, 4);
  for (c4_i758 = 0; c4_i758 < 3; c4_i758 = c4_i758 + 1) {
    c4_velociy[c4_i758] = c4_kx[c4_i758];
  }

  _SFD_SCRIPT_CALL(5, 5);
  for (c4_i759 = 0; c4_i759 < 3; c4_i759 = c4_i759 + 1) {
    c4_w[c4_i759] = c4_kx[c4_i759 + 3];
  }

  /*  rotation axis */
  _SFD_SCRIPT_CALL(5, 6);
  for (c4_i760 = 0; c4_i760 < 3; c4_i760 = c4_i760 + 1) {
    c4_b_velociy[c4_i760] = c4_velociy[c4_i760];
  }

  for (c4_i761 = 0; c4_i761 < 3; c4_i761 = c4_i761 + 1) {
    c4_b_w[c4_i761] = c4_w[c4_i761];
  }

  c4_cross(chartInstance, c4_b_velociy, c4_b_w, c4_dv34);
  for (c4_i762 = 0; c4_i762 < 3; c4_i762 = c4_i762 + 1) {
    c4_r[c4_i762] = -c4_dv34[c4_i762];
  }

  _SFD_SCRIPT_CALL(5, 8);
  for (c4_i763 = 0; c4_i763 < 3; c4_i763 = c4_i763 + 1) {
    c4_u[c4_i763] = c4_p[c4_i763] - c4_r[c4_i763];
  }

  _SFD_SCRIPT_CALL(5, 9);
  for (c4_i764 = 0; c4_i764 < 3; c4_i764 = c4_i764 + 1) {
    c4_v[c4_i764] = c4_q[c4_i764] - c4_r[c4_i764];
  }

  _SFD_SCRIPT_CALL(5, 12);
  for (c4_i765 = 0; c4_i765 < 3; c4_i765 = c4_i765 + 1) {
    c4_a[c4_i765] = c4_w[c4_i765];
  }

  for (c4_i766 = 0; c4_i766 < 3; c4_i766 = c4_i766 + 1) {
    c4_b[c4_i766] = c4_u[c4_i766];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i767 = 0; c4_i767 < 3; c4_i767 = c4_i767 + 1) {
    c4_x[c4_i767] = c4_a[c4_i767];
  }

  for (c4_i768 = 0; c4_i768 < 3; c4_i768 = c4_i768 + 1) {
    c4_y[c4_i768] = c4_b[c4_i768];
  }

  for (c4_i769 = 0; c4_i769 < 3; c4_i769 = c4_i769 + 1) {
    c4_b_x[c4_i769] = c4_x[c4_i769];
  }

  for (c4_i770 = 0; c4_i770 < 3; c4_i770 = c4_i770 + 1) {
    c4_b_y[c4_i770] = c4_y[c4_i770];
  }

  for (c4_i771 = 0; c4_i771 < 3; c4_i771 = c4_i771 + 1) {
    c4_c_x[c4_i771] = c4_b_x[c4_i771];
  }

  for (c4_i772 = 0; c4_i772 < 3; c4_i772 = c4_i772 + 1) {
    c4_c_y[c4_i772] = c4_b_y[c4_i772];
  }

  for (c4_i773 = 0; c4_i773 < 3; c4_i773 = c4_i773 + 1) {
    c4_d_x[c4_i773] = c4_c_x[c4_i773];
  }

  for (c4_i774 = 0; c4_i774 < 3; c4_i774 = c4_i774 + 1) {
    c4_d_y[c4_i774] = c4_c_y[c4_i774];
  }

  c4_e_y = c4_ceval_xdot(chartInstance, 3, c4_d_x, 1, 1, c4_d_y, 1, 1);
  for (c4_i775 = 0; c4_i775 < 3; c4_i775 = c4_i775 + 1) {
    c4_b_a[c4_i775] = c4_w[c4_i775];
  }

  c4_b_b = c4_e_y;
  for (c4_i776 = 0; c4_i776 < 3; c4_i776 = c4_i776 + 1) {
    c4_f_y[c4_i776] = c4_b_a[c4_i776] * c4_b_b;
  }

  for (c4_i777 = 0; c4_i777 < 3; c4_i777 = c4_i777 + 1) {
    c4_up[c4_i777] = c4_u[c4_i777] - c4_f_y[c4_i777];
  }

  _SFD_SCRIPT_CALL(5, 13);
  for (c4_i778 = 0; c4_i778 < 3; c4_i778 = c4_i778 + 1) {
    c4_c_a[c4_i778] = c4_w[c4_i778];
  }

  for (c4_i779 = 0; c4_i779 < 3; c4_i779 = c4_i779 + 1) {
    c4_c_b[c4_i779] = c4_u[c4_i779];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i780 = 0; c4_i780 < 3; c4_i780 = c4_i780 + 1) {
    c4_e_x[c4_i780] = c4_c_a[c4_i780];
  }

  for (c4_i781 = 0; c4_i781 < 3; c4_i781 = c4_i781 + 1) {
    c4_g_y[c4_i781] = c4_c_b[c4_i781];
  }

  for (c4_i782 = 0; c4_i782 < 3; c4_i782 = c4_i782 + 1) {
    c4_f_x[c4_i782] = c4_e_x[c4_i782];
  }

  for (c4_i783 = 0; c4_i783 < 3; c4_i783 = c4_i783 + 1) {
    c4_h_y[c4_i783] = c4_g_y[c4_i783];
  }

  for (c4_i784 = 0; c4_i784 < 3; c4_i784 = c4_i784 + 1) {
    c4_g_x[c4_i784] = c4_f_x[c4_i784];
  }

  for (c4_i785 = 0; c4_i785 < 3; c4_i785 = c4_i785 + 1) {
    c4_i_y[c4_i785] = c4_h_y[c4_i785];
  }

  for (c4_i786 = 0; c4_i786 < 3; c4_i786 = c4_i786 + 1) {
    c4_h_x[c4_i786] = c4_g_x[c4_i786];
  }

  for (c4_i787 = 0; c4_i787 < 3; c4_i787 = c4_i787 + 1) {
    c4_j_y[c4_i787] = c4_i_y[c4_i787];
  }

  c4_k_y = c4_ceval_xdot(chartInstance, 3, c4_h_x, 1, 1, c4_j_y, 1, 1);
  for (c4_i788 = 0; c4_i788 < 3; c4_i788 = c4_i788 + 1) {
    c4_d_a[c4_i788] = c4_w[c4_i788];
  }

  c4_d_b = c4_k_y;
  for (c4_i789 = 0; c4_i789 < 3; c4_i789 = c4_i789 + 1) {
    c4_l_y[c4_i789] = c4_d_a[c4_i789] * c4_d_b;
  }

  for (c4_i790 = 0; c4_i790 < 3; c4_i790 = c4_i790 + 1) {
    c4_vp[c4_i790] = c4_v[c4_i790] - c4_l_y[c4_i790];
  }

  /*      if norm(up) == 0 */
  /*          error('SubPro1: up = 0, Infinite number of solutions!'); */
  /*      end */
  _SFD_SCRIPT_CALL(5, 19);
  for (c4_i791 = 0; c4_i791 < 3; c4_i791 = c4_i791 + 1) {
    c4_e_a[c4_i791] = c4_w[c4_i791];
  }

  for (c4_i792 = 0; c4_i792 < 3; c4_i792 = c4_i792 + 1) {
    c4_b_up[c4_i792] = c4_up[c4_i792];
  }

  for (c4_i793 = 0; c4_i793 < 3; c4_i793 = c4_i793 + 1) {
    c4_b_vp[c4_i793] = c4_vp[c4_i793];
  }

  c4_cross(chartInstance, c4_b_up, c4_b_vp, c4_e_b);
  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i794 = 0; c4_i794 < 3; c4_i794 = c4_i794 + 1) {
    c4_i_x[c4_i794] = c4_e_a[c4_i794];
  }

  for (c4_i795 = 0; c4_i795 < 3; c4_i795 = c4_i795 + 1) {
    c4_m_y[c4_i795] = c4_e_b[c4_i795];
  }

  for (c4_i796 = 0; c4_i796 < 3; c4_i796 = c4_i796 + 1) {
    c4_j_x[c4_i796] = c4_i_x[c4_i796];
  }

  for (c4_i797 = 0; c4_i797 < 3; c4_i797 = c4_i797 + 1) {
    c4_n_y[c4_i797] = c4_m_y[c4_i797];
  }

  for (c4_i798 = 0; c4_i798 < 3; c4_i798 = c4_i798 + 1) {
    c4_k_x[c4_i798] = c4_j_x[c4_i798];
  }

  for (c4_i799 = 0; c4_i799 < 3; c4_i799 = c4_i799 + 1) {
    c4_o_y[c4_i799] = c4_n_y[c4_i799];
  }

  for (c4_i800 = 0; c4_i800 < 3; c4_i800 = c4_i800 + 1) {
    c4_l_x[c4_i800] = c4_k_x[c4_i800];
  }

  for (c4_i801 = 0; c4_i801 < 3; c4_i801 = c4_i801 + 1) {
    c4_p_y[c4_i801] = c4_o_y[c4_i801];
  }

  c4_q_y = c4_ceval_xdot(chartInstance, 3, c4_l_x, 1, 1, c4_p_y, 1, 1);
  for (c4_i802 = 0; c4_i802 < 3; c4_i802 = c4_i802 + 1) {
    c4_f_a[c4_i802] = c4_up[c4_i802];
  }

  for (c4_i803 = 0; c4_i803 < 3; c4_i803 = c4_i803 + 1) {
    c4_f_b[c4_i803] = c4_vp[c4_i803];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i804 = 0; c4_i804 < 3; c4_i804 = c4_i804 + 1) {
    c4_m_x[c4_i804] = c4_f_a[c4_i804];
  }

  for (c4_i805 = 0; c4_i805 < 3; c4_i805 = c4_i805 + 1) {
    c4_r_y[c4_i805] = c4_f_b[c4_i805];
  }

  for (c4_i806 = 0; c4_i806 < 3; c4_i806 = c4_i806 + 1) {
    c4_n_x[c4_i806] = c4_m_x[c4_i806];
  }

  for (c4_i807 = 0; c4_i807 < 3; c4_i807 = c4_i807 + 1) {
    c4_s_y[c4_i807] = c4_r_y[c4_i807];
  }

  for (c4_i808 = 0; c4_i808 < 3; c4_i808 = c4_i808 + 1) {
    c4_o_x[c4_i808] = c4_n_x[c4_i808];
  }

  for (c4_i809 = 0; c4_i809 < 3; c4_i809 = c4_i809 + 1) {
    c4_t_y[c4_i809] = c4_s_y[c4_i809];
  }

  for (c4_i810 = 0; c4_i810 < 3; c4_i810 = c4_i810 + 1) {
    c4_p_x[c4_i810] = c4_o_x[c4_i810];
  }

  for (c4_i811 = 0; c4_i811 < 3; c4_i811 = c4_i811 + 1) {
    c4_u_y[c4_i811] = c4_t_y[c4_i811];
  }

  c4_v_y = c4_ceval_xdot(chartInstance, 3, c4_p_x, 1, 1, c4_u_y, 1, 1);
  c4_theta = c4_atan2(chartInstance, c4_q_y, c4_v_y);
  _SFD_SCRIPT_CALL(5, -19);
  sf_debug_symbol_scope_pop();
  return c4_theta;
}

static real_T c4_c_subPro1(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, real_T c4_kx[6], real_T c4_p[3], real_T c4_q[4])
{
  real_T c4_theta;
  uint32_T c4_debug_family_var_map[13];
  real_T c4_velociy[3];
  real_T c4_w[3];
  real_T c4_r[3];
  real_T c4_u[3];
  real_T c4_v[3];
  real_T c4_up[3];
  real_T c4_vp[3];
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 1.0;
  int32_T c4_i812;
  int32_T c4_i813;
  int32_T c4_i814;
  real_T c4_b_velociy[3];
  int32_T c4_i815;
  real_T c4_b_w[3];
  real_T c4_dv35[3];
  int32_T c4_i816;
  int32_T c4_i817;
  int32_T c4_i818;
  int32_T c4_i819;
  real_T c4_a[3];
  int32_T c4_i820;
  real_T c4_b[3];
  int32_T c4_i821;
  real_T c4_x[3];
  int32_T c4_i822;
  real_T c4_y[3];
  int32_T c4_i823;
  real_T c4_b_x[3];
  int32_T c4_i824;
  real_T c4_b_y[3];
  int32_T c4_i825;
  real_T c4_c_x[3];
  int32_T c4_i826;
  real_T c4_c_y[3];
  int32_T c4_i827;
  real_T c4_d_x[3];
  int32_T c4_i828;
  real_T c4_d_y[3];
  real_T c4_e_y;
  int32_T c4_i829;
  real_T c4_b_a[3];
  real_T c4_b_b;
  int32_T c4_i830;
  real_T c4_f_y[3];
  int32_T c4_i831;
  int32_T c4_i832;
  real_T c4_c_a[3];
  int32_T c4_i833;
  real_T c4_c_b[3];
  int32_T c4_i834;
  real_T c4_e_x[3];
  int32_T c4_i835;
  real_T c4_g_y[3];
  int32_T c4_i836;
  real_T c4_f_x[3];
  int32_T c4_i837;
  real_T c4_h_y[3];
  int32_T c4_i838;
  real_T c4_g_x[3];
  int32_T c4_i839;
  real_T c4_i_y[3];
  int32_T c4_i840;
  real_T c4_h_x[3];
  int32_T c4_i841;
  real_T c4_j_y[3];
  real_T c4_k_y;
  int32_T c4_i842;
  real_T c4_d_a[3];
  real_T c4_d_b;
  int32_T c4_i843;
  real_T c4_l_y[3];
  int32_T c4_i844;
  int32_T c4_i845;
  real_T c4_e_a[3];
  int32_T c4_i846;
  real_T c4_b_up[3];
  int32_T c4_i847;
  real_T c4_b_vp[3];
  real_T c4_e_b[3];
  int32_T c4_i848;
  real_T c4_i_x[3];
  int32_T c4_i849;
  real_T c4_m_y[3];
  int32_T c4_i850;
  real_T c4_j_x[3];
  int32_T c4_i851;
  real_T c4_n_y[3];
  int32_T c4_i852;
  real_T c4_k_x[3];
  int32_T c4_i853;
  real_T c4_o_y[3];
  int32_T c4_i854;
  real_T c4_l_x[3];
  int32_T c4_i855;
  real_T c4_p_y[3];
  real_T c4_q_y;
  int32_T c4_i856;
  real_T c4_f_a[3];
  int32_T c4_i857;
  real_T c4_f_b[3];
  int32_T c4_i858;
  real_T c4_m_x[3];
  int32_T c4_i859;
  real_T c4_r_y[3];
  int32_T c4_i860;
  real_T c4_n_x[3];
  int32_T c4_i861;
  real_T c4_s_y[3];
  int32_T c4_i862;
  real_T c4_o_x[3];
  int32_T c4_i863;
  real_T c4_t_y[3];
  int32_T c4_i864;
  real_T c4_p_x[3];
  int32_T c4_i865;
  real_T c4_u_y[3];
  real_T c4_v_y;
  sf_debug_symbol_scope_push_eml(0U, 13U, 13U, c4_k_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c4_velociy, c4_d_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(c4_w, c4_d_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(c4_r, c4_d_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(c4_u, c4_d_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(c4_v, c4_d_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(c4_up, c4_d_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(c4_vp, c4_d_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c4_nargin, c4_e_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c4_nargout, c4_e_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(c4_kx, c4_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(c4_p, c4_d_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(c4_q, c4_j_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c4_theta, c4_e_sf_marshall, 12U);
  CV_SCRIPT_FCN(5, 0);
  _SFD_SCRIPT_CALL(5, 4);
  for (c4_i812 = 0; c4_i812 < 3; c4_i812 = c4_i812 + 1) {
    c4_velociy[c4_i812] = c4_kx[c4_i812];
  }

  _SFD_SCRIPT_CALL(5, 5);
  for (c4_i813 = 0; c4_i813 < 3; c4_i813 = c4_i813 + 1) {
    c4_w[c4_i813] = c4_kx[c4_i813 + 3];
  }

  /*  rotation axis */
  _SFD_SCRIPT_CALL(5, 6);
  for (c4_i814 = 0; c4_i814 < 3; c4_i814 = c4_i814 + 1) {
    c4_b_velociy[c4_i814] = c4_velociy[c4_i814];
  }

  for (c4_i815 = 0; c4_i815 < 3; c4_i815 = c4_i815 + 1) {
    c4_b_w[c4_i815] = c4_w[c4_i815];
  }

  c4_cross(chartInstance, c4_b_velociy, c4_b_w, c4_dv35);
  for (c4_i816 = 0; c4_i816 < 3; c4_i816 = c4_i816 + 1) {
    c4_r[c4_i816] = -c4_dv35[c4_i816];
  }

  _SFD_SCRIPT_CALL(5, 8);
  for (c4_i817 = 0; c4_i817 < 3; c4_i817 = c4_i817 + 1) {
    c4_u[c4_i817] = c4_p[c4_i817] - c4_r[c4_i817];
  }

  _SFD_SCRIPT_CALL(5, 9);
  for (c4_i818 = 0; c4_i818 < 3; c4_i818 = c4_i818 + 1) {
    c4_v[c4_i818] = c4_q[c4_i818] - c4_r[c4_i818];
  }

  _SFD_SCRIPT_CALL(5, 12);
  for (c4_i819 = 0; c4_i819 < 3; c4_i819 = c4_i819 + 1) {
    c4_a[c4_i819] = c4_w[c4_i819];
  }

  for (c4_i820 = 0; c4_i820 < 3; c4_i820 = c4_i820 + 1) {
    c4_b[c4_i820] = c4_u[c4_i820];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i821 = 0; c4_i821 < 3; c4_i821 = c4_i821 + 1) {
    c4_x[c4_i821] = c4_a[c4_i821];
  }

  for (c4_i822 = 0; c4_i822 < 3; c4_i822 = c4_i822 + 1) {
    c4_y[c4_i822] = c4_b[c4_i822];
  }

  for (c4_i823 = 0; c4_i823 < 3; c4_i823 = c4_i823 + 1) {
    c4_b_x[c4_i823] = c4_x[c4_i823];
  }

  for (c4_i824 = 0; c4_i824 < 3; c4_i824 = c4_i824 + 1) {
    c4_b_y[c4_i824] = c4_y[c4_i824];
  }

  for (c4_i825 = 0; c4_i825 < 3; c4_i825 = c4_i825 + 1) {
    c4_c_x[c4_i825] = c4_b_x[c4_i825];
  }

  for (c4_i826 = 0; c4_i826 < 3; c4_i826 = c4_i826 + 1) {
    c4_c_y[c4_i826] = c4_b_y[c4_i826];
  }

  for (c4_i827 = 0; c4_i827 < 3; c4_i827 = c4_i827 + 1) {
    c4_d_x[c4_i827] = c4_c_x[c4_i827];
  }

  for (c4_i828 = 0; c4_i828 < 3; c4_i828 = c4_i828 + 1) {
    c4_d_y[c4_i828] = c4_c_y[c4_i828];
  }

  c4_e_y = c4_ceval_xdot(chartInstance, 3, c4_d_x, 1, 1, c4_d_y, 1, 1);
  for (c4_i829 = 0; c4_i829 < 3; c4_i829 = c4_i829 + 1) {
    c4_b_a[c4_i829] = c4_w[c4_i829];
  }

  c4_b_b = c4_e_y;
  for (c4_i830 = 0; c4_i830 < 3; c4_i830 = c4_i830 + 1) {
    c4_f_y[c4_i830] = c4_b_a[c4_i830] * c4_b_b;
  }

  for (c4_i831 = 0; c4_i831 < 3; c4_i831 = c4_i831 + 1) {
    c4_up[c4_i831] = c4_u[c4_i831] - c4_f_y[c4_i831];
  }

  _SFD_SCRIPT_CALL(5, 13);
  for (c4_i832 = 0; c4_i832 < 3; c4_i832 = c4_i832 + 1) {
    c4_c_a[c4_i832] = c4_w[c4_i832];
  }

  for (c4_i833 = 0; c4_i833 < 3; c4_i833 = c4_i833 + 1) {
    c4_c_b[c4_i833] = c4_u[c4_i833];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i834 = 0; c4_i834 < 3; c4_i834 = c4_i834 + 1) {
    c4_e_x[c4_i834] = c4_c_a[c4_i834];
  }

  for (c4_i835 = 0; c4_i835 < 3; c4_i835 = c4_i835 + 1) {
    c4_g_y[c4_i835] = c4_c_b[c4_i835];
  }

  for (c4_i836 = 0; c4_i836 < 3; c4_i836 = c4_i836 + 1) {
    c4_f_x[c4_i836] = c4_e_x[c4_i836];
  }

  for (c4_i837 = 0; c4_i837 < 3; c4_i837 = c4_i837 + 1) {
    c4_h_y[c4_i837] = c4_g_y[c4_i837];
  }

  for (c4_i838 = 0; c4_i838 < 3; c4_i838 = c4_i838 + 1) {
    c4_g_x[c4_i838] = c4_f_x[c4_i838];
  }

  for (c4_i839 = 0; c4_i839 < 3; c4_i839 = c4_i839 + 1) {
    c4_i_y[c4_i839] = c4_h_y[c4_i839];
  }

  for (c4_i840 = 0; c4_i840 < 3; c4_i840 = c4_i840 + 1) {
    c4_h_x[c4_i840] = c4_g_x[c4_i840];
  }

  for (c4_i841 = 0; c4_i841 < 3; c4_i841 = c4_i841 + 1) {
    c4_j_y[c4_i841] = c4_i_y[c4_i841];
  }

  c4_k_y = c4_ceval_xdot(chartInstance, 3, c4_h_x, 1, 1, c4_j_y, 1, 1);
  for (c4_i842 = 0; c4_i842 < 3; c4_i842 = c4_i842 + 1) {
    c4_d_a[c4_i842] = c4_w[c4_i842];
  }

  c4_d_b = c4_k_y;
  for (c4_i843 = 0; c4_i843 < 3; c4_i843 = c4_i843 + 1) {
    c4_l_y[c4_i843] = c4_d_a[c4_i843] * c4_d_b;
  }

  for (c4_i844 = 0; c4_i844 < 3; c4_i844 = c4_i844 + 1) {
    c4_vp[c4_i844] = c4_v[c4_i844] - c4_l_y[c4_i844];
  }

  /*      if norm(up) == 0 */
  /*          error('SubPro1: up = 0, Infinite number of solutions!'); */
  /*      end */
  _SFD_SCRIPT_CALL(5, 19);
  for (c4_i845 = 0; c4_i845 < 3; c4_i845 = c4_i845 + 1) {
    c4_e_a[c4_i845] = c4_w[c4_i845];
  }

  for (c4_i846 = 0; c4_i846 < 3; c4_i846 = c4_i846 + 1) {
    c4_b_up[c4_i846] = c4_up[c4_i846];
  }

  for (c4_i847 = 0; c4_i847 < 3; c4_i847 = c4_i847 + 1) {
    c4_b_vp[c4_i847] = c4_vp[c4_i847];
  }

  c4_cross(chartInstance, c4_b_up, c4_b_vp, c4_e_b);
  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i848 = 0; c4_i848 < 3; c4_i848 = c4_i848 + 1) {
    c4_i_x[c4_i848] = c4_e_a[c4_i848];
  }

  for (c4_i849 = 0; c4_i849 < 3; c4_i849 = c4_i849 + 1) {
    c4_m_y[c4_i849] = c4_e_b[c4_i849];
  }

  for (c4_i850 = 0; c4_i850 < 3; c4_i850 = c4_i850 + 1) {
    c4_j_x[c4_i850] = c4_i_x[c4_i850];
  }

  for (c4_i851 = 0; c4_i851 < 3; c4_i851 = c4_i851 + 1) {
    c4_n_y[c4_i851] = c4_m_y[c4_i851];
  }

  for (c4_i852 = 0; c4_i852 < 3; c4_i852 = c4_i852 + 1) {
    c4_k_x[c4_i852] = c4_j_x[c4_i852];
  }

  for (c4_i853 = 0; c4_i853 < 3; c4_i853 = c4_i853 + 1) {
    c4_o_y[c4_i853] = c4_n_y[c4_i853];
  }

  for (c4_i854 = 0; c4_i854 < 3; c4_i854 = c4_i854 + 1) {
    c4_l_x[c4_i854] = c4_k_x[c4_i854];
  }

  for (c4_i855 = 0; c4_i855 < 3; c4_i855 = c4_i855 + 1) {
    c4_p_y[c4_i855] = c4_o_y[c4_i855];
  }

  c4_q_y = c4_ceval_xdot(chartInstance, 3, c4_l_x, 1, 1, c4_p_y, 1, 1);
  for (c4_i856 = 0; c4_i856 < 3; c4_i856 = c4_i856 + 1) {
    c4_f_a[c4_i856] = c4_up[c4_i856];
  }

  for (c4_i857 = 0; c4_i857 < 3; c4_i857 = c4_i857 + 1) {
    c4_f_b[c4_i857] = c4_vp[c4_i857];
  }

  c4_g_eml_scalar_eg(chartInstance);
  for (c4_i858 = 0; c4_i858 < 3; c4_i858 = c4_i858 + 1) {
    c4_m_x[c4_i858] = c4_f_a[c4_i858];
  }

  for (c4_i859 = 0; c4_i859 < 3; c4_i859 = c4_i859 + 1) {
    c4_r_y[c4_i859] = c4_f_b[c4_i859];
  }

  for (c4_i860 = 0; c4_i860 < 3; c4_i860 = c4_i860 + 1) {
    c4_n_x[c4_i860] = c4_m_x[c4_i860];
  }

  for (c4_i861 = 0; c4_i861 < 3; c4_i861 = c4_i861 + 1) {
    c4_s_y[c4_i861] = c4_r_y[c4_i861];
  }

  for (c4_i862 = 0; c4_i862 < 3; c4_i862 = c4_i862 + 1) {
    c4_o_x[c4_i862] = c4_n_x[c4_i862];
  }

  for (c4_i863 = 0; c4_i863 < 3; c4_i863 = c4_i863 + 1) {
    c4_t_y[c4_i863] = c4_s_y[c4_i863];
  }

  for (c4_i864 = 0; c4_i864 < 3; c4_i864 = c4_i864 + 1) {
    c4_p_x[c4_i864] = c4_o_x[c4_i864];
  }

  for (c4_i865 = 0; c4_i865 < 3; c4_i865 = c4_i865 + 1) {
    c4_u_y[c4_i865] = c4_t_y[c4_i865];
  }

  c4_v_y = c4_ceval_xdot(chartInstance, 3, c4_p_x, 1, 1, c4_u_y, 1, 1);
  c4_theta = c4_atan2(chartInstance, c4_q_y, c4_v_y);
  _SFD_SCRIPT_CALL(5, -19);
  sf_debug_symbol_scope_pop();
  return c4_theta;
}

static const mxArray *c4_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i866;
  real_T c4_b_u[6];
  int32_T c4_i867;
  real_T c4_c_u[6];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  for (c4_i866 = 0; c4_i866 < 6; c4_i866 = c4_i866 + 1) {
    c4_b_u[c4_i866] = (*((real_T (*)[6])c4_u))[c4_i866];
  }

  for (c4_i867 = 0; c4_i867 < 6; c4_i867 = c4_i867 + 1) {
    c4_c_u[c4_i867] = c4_b_u[c4_i867];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 1, 6));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_b_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i868;
  real_T c4_b_u[9];
  int32_T c4_i869;
  real_T c4_c_u[9];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  for (c4_i868 = 0; c4_i868 < 9; c4_i868 = c4_i868 + 1) {
    c4_b_u[c4_i868] = (*((real_T (*)[9])c4_u))[c4_i868];
  }

  for (c4_i869 = 0; c4_i869 < 9; c4_i869 = c4_i869 + 1) {
    c4_c_u[c4_i869] = c4_b_u[c4_i869];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 2, 1, 9));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_c_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i870;
  int32_T c4_i871;
  int32_T c4_i872;
  real_T c4_b_u[9];
  int32_T c4_i873;
  int32_T c4_i874;
  int32_T c4_i875;
  real_T c4_c_u[9];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  c4_i870 = 0;
  for (c4_i871 = 0; c4_i871 < 3; c4_i871 = c4_i871 + 1) {
    for (c4_i872 = 0; c4_i872 < 3; c4_i872 = c4_i872 + 1) {
      c4_b_u[c4_i872 + c4_i870] = (*((real_T (*)[9])c4_u))[c4_i872 + c4_i870];
    }

    c4_i870 = c4_i870 + 3;
  }

  c4_i873 = 0;
  for (c4_i874 = 0; c4_i874 < 3; c4_i874 = c4_i874 + 1) {
    for (c4_i875 = 0; c4_i875 < 3; c4_i875 = c4_i875 + 1) {
      c4_c_u[c4_i875 + c4_i873] = c4_b_u[c4_i875 + c4_i873];
    }

    c4_i873 = c4_i873 + 3;
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 2, 3, 3));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_d_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i876;
  real_T c4_b_u[3];
  int32_T c4_i877;
  real_T c4_c_u[3];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  for (c4_i876 = 0; c4_i876 < 3; c4_i876 = c4_i876 + 1) {
    c4_b_u[c4_i876] = (*((real_T (*)[3])c4_u))[c4_i876];
  }

  for (c4_i877 = 0; c4_i877 < 3; c4_i877 = c4_i877 + 1) {
    c4_c_u[c4_i877] = c4_b_u[c4_i877];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 1, 3));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_e_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  real_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  c4_b_u = *((real_T *)c4_u);
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_f_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i878;
  int32_T c4_i879;
  int32_T c4_i880;
  real_T c4_b_u[24];
  int32_T c4_i881;
  int32_T c4_i882;
  int32_T c4_i883;
  real_T c4_c_u[24];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  c4_i878 = 0;
  for (c4_i879 = 0; c4_i879 < 4; c4_i879 = c4_i879 + 1) {
    for (c4_i880 = 0; c4_i880 < 6; c4_i880 = c4_i880 + 1) {
      c4_b_u[c4_i880 + c4_i878] = (*((real_T (*)[24])c4_u))[c4_i880 + c4_i878];
    }

    c4_i878 = c4_i878 + 6;
  }

  c4_i881 = 0;
  for (c4_i882 = 0; c4_i882 < 4; c4_i882 = c4_i882 + 1) {
    for (c4_i883 = 0; c4_i883 < 6; c4_i883 = c4_i883 + 1) {
      c4_c_u[c4_i883 + c4_i881] = c4_b_u[c4_i883 + c4_i881];
    }

    c4_i881 = c4_i881 + 6;
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 2, 6, 4));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_g_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i884;
  int32_T c4_i885;
  int32_T c4_i886;
  real_T c4_b_u[16];
  int32_T c4_i887;
  int32_T c4_i888;
  int32_T c4_i889;
  real_T c4_c_u[16];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  c4_i884 = 0;
  for (c4_i885 = 0; c4_i885 < 4; c4_i885 = c4_i885 + 1) {
    for (c4_i886 = 0; c4_i886 < 4; c4_i886 = c4_i886 + 1) {
      c4_b_u[c4_i886 + c4_i884] = (*((real_T (*)[16])c4_u))[c4_i886 + c4_i884];
    }

    c4_i884 = c4_i884 + 4;
  }

  c4_i887 = 0;
  for (c4_i888 = 0; c4_i888 < 4; c4_i888 = c4_i888 + 1) {
    for (c4_i889 = 0; c4_i889 < 4; c4_i889 = c4_i889 + 1) {
      c4_c_u[c4_i889 + c4_i887] = c4_b_u[c4_i889 + c4_i887];
    }

    c4_i887 = c4_i887 + 4;
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 2, 4, 4));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_h_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  boolean_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  c4_b_u = *((boolean_T *)c4_u);
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_i_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i890;
  real_T c4_b_u[2];
  int32_T c4_i891;
  real_T c4_c_u[2];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  for (c4_i890 = 0; c4_i890 < 2; c4_i890 = c4_i890 + 1) {
    c4_b_u[c4_i890] = (*((real_T (*)[2])c4_u))[c4_i890];
  }

  for (c4_i891 = 0; c4_i891 < 2; c4_i891 = c4_i891 + 1) {
    c4_c_u[c4_i891] = c4_b_u[c4_i891];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 1, 2));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_j_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i892;
  real_T c4_b_u[4];
  int32_T c4_i893;
  real_T c4_c_u[4];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  for (c4_i892 = 0; c4_i892 < 4; c4_i892 = c4_i892 + 1) {
    c4_b_u[c4_i892] = (*((real_T (*)[4])c4_u))[c4_i892];
  }

  for (c4_i893 = 0; c4_i893 < 4; c4_i893 = c4_i893 + 1) {
    c4_c_u[c4_i893] = c4_b_u[c4_i893];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 1, 4));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_k_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i894;
  boolean_T c4_b_u[2];
  int32_T c4_i895;
  boolean_T c4_c_u[2];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  for (c4_i894 = 0; c4_i894 < 2; c4_i894 = c4_i894 + 1) {
    c4_b_u[c4_i894] = (*((boolean_T (*)[2])c4_u))[c4_i894];
  }

  for (c4_i895 = 0; c4_i895 < 2; c4_i895 = c4_i895 + 1) {
    c4_c_u[c4_i895] = c4_b_u[c4_i895];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 11, 0U, 1U, 0U, 1, 2));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

static const mxArray *c4_l_sf_marshall(void *chartInstanceVoid, void *c4_u)
{
  const mxArray *c4_y = NULL;
  int32_T c4_i896;
  int32_T c4_i897;
  int32_T c4_i898;
  real_T c4_b_u[4];
  int32_T c4_i899;
  int32_T c4_i900;
  int32_T c4_i901;
  real_T c4_c_u[4];
  const mxArray *c4_b_y = NULL;
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  c4_i896 = 0;
  for (c4_i897 = 0; c4_i897 < 2; c4_i897 = c4_i897 + 1) {
    for (c4_i898 = 0; c4_i898 < 2; c4_i898 = c4_i898 + 1) {
      c4_b_u[c4_i898 + c4_i896] = (*((real_T (*)[4])c4_u))[c4_i898 + c4_i896];
    }

    c4_i896 = c4_i896 + 2;
  }

  c4_i899 = 0;
  for (c4_i900 = 0; c4_i900 < 2; c4_i900 = c4_i900 + 1) {
    for (c4_i901 = 0; c4_i901 < 2; c4_i901 = c4_i901 + 1) {
      c4_c_u[c4_i901 + c4_i899] = c4_b_u[c4_i901 + c4_i899];
    }

    c4_i899 = c4_i899 + 2;
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 2, 2, 2));
  sf_mex_assign(&c4_y, c4_b_y);
  return c4_y;
}

const mxArray *sf_c4_EurlerDynJointVerify_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_ResolvedFunctionInfo c4_info[121];
  const mxArray *c4_m0 = NULL;
  int32_T c4_i902;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_info_helper(c4_info);
  c4_b_info_helper(c4_info);
  sf_mex_assign(&c4_m0, sf_mex_createstruct("nameCaptureInfo", 1, 121));
  for (c4_i902 = 0; c4_i902 < 121; c4_i902 = c4_i902 + 1) {
    c4_r0 = &c4_info[c4_i902];
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context",
                    "nameCaptureInfo", c4_i902);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name",
                    "nameCaptureInfo", c4_i902);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c4_i902);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c4_i902);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c4_i902);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo",
                    c4_i902);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo",
                    c4_i902);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m0);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[121])
{
  c4_info[0].context = "";
  c4_info[0].name = "inv_kin";
  c4_info[0].dominantType = "double";
  c4_info[0].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[0].fileLength = 2977U;
  c4_info[0].fileTime1 = 1367251992U;
  c4_info[0].fileTime2 = 0U;
  c4_info[1].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[1].name = "zeros";
  c4_info[1].dominantType = "double";
  c4_info[1].resolved = "[B]zeros";
  c4_info[1].fileLength = 0U;
  c4_info[1].fileTime1 = 0U;
  c4_info[1].fileTime2 = 0U;
  c4_info[2].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[2].name = "uminus";
  c4_info[2].dominantType = "double";
  c4_info[2].resolved = "[B]uminus";
  c4_info[2].fileLength = 0U;
  c4_info[2].fileTime1 = 0U;
  c4_info[2].fileTime2 = 0U;
  c4_info[3].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[3].name = "cross";
  c4_info[3].dominantType = "double";
  c4_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[3].fileLength = 3157U;
  c4_info[3].fileTime1 = 1240240462U;
  c4_info[3].fileTime2 = 0U;
  c4_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[4].name = "nargin";
  c4_info[4].dominantType = "";
  c4_info[4].resolved = "[B]nargin";
  c4_info[4].fileLength = 0U;
  c4_info[4].fileTime1 = 0U;
  c4_info[4].fileTime2 = 0U;
  c4_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[5].name = "gt";
  c4_info[5].dominantType = "double";
  c4_info[5].resolved = "[B]gt";
  c4_info[5].fileLength = 0U;
  c4_info[5].fileTime1 = 0U;
  c4_info[5].fileTime2 = 0U;
  c4_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[6].name = "eq";
  c4_info[6].dominantType = "double";
  c4_info[6].resolved = "[B]eq";
  c4_info[6].fileLength = 0U;
  c4_info[6].fileTime1 = 0U;
  c4_info[6].fileTime2 = 0U;
  c4_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[7].name = "isa";
  c4_info[7].dominantType = "double";
  c4_info[7].resolved = "[B]isa";
  c4_info[7].fileLength = 0U;
  c4_info[7].fileTime1 = 0U;
  c4_info[7].fileTime2 = 0U;
  c4_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[8].name = "isvector";
  c4_info[8].dominantType = "double";
  c4_info[8].resolved = "[B]isvector";
  c4_info[8].fileLength = 0U;
  c4_info[8].fileTime1 = 0U;
  c4_info[8].fileTime2 = 0U;
  c4_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[9].name = "mtimes";
  c4_info[9].dominantType = "double";
  c4_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[9].fileLength = 3425U;
  c4_info[9].fileTime1 = 1251010272U;
  c4_info[9].fileTime2 = 0U;
  c4_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[10].name = "isinteger";
  c4_info[10].dominantType = "double";
  c4_info[10].resolved = "[B]isinteger";
  c4_info[10].fileLength = 0U;
  c4_info[10].fileTime1 = 0U;
  c4_info[10].fileTime2 = 0U;
  c4_info[11].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[11].name = "isscalar";
  c4_info[11].dominantType = "double";
  c4_info[11].resolved = "[B]isscalar";
  c4_info[11].fileLength = 0U;
  c4_info[11].fileTime1 = 0U;
  c4_info[11].fileTime2 = 0U;
  c4_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[12].name = "strcmp";
  c4_info[12].dominantType = "char";
  c4_info[12].resolved = "[B]strcmp";
  c4_info[12].fileLength = 0U;
  c4_info[12].fileTime1 = 0U;
  c4_info[12].fileTime2 = 0U;
  c4_info[13].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[13].name = "size";
  c4_info[13].dominantType = "double";
  c4_info[13].resolved = "[B]size";
  c4_info[13].fileLength = 0U;
  c4_info[13].fileTime1 = 0U;
  c4_info[13].fileTime2 = 0U;
  c4_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[14].name = "class";
  c4_info[14].dominantType = "double";
  c4_info[14].resolved = "[B]class";
  c4_info[14].fileLength = 0U;
  c4_info[14].fileTime1 = 0U;
  c4_info[14].fileTime2 = 0U;
  c4_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[15].name = "not";
  c4_info[15].dominantType = "logical";
  c4_info[15].resolved = "[B]not";
  c4_info[15].fileLength = 0U;
  c4_info[15].fileTime1 = 0U;
  c4_info[15].fileTime2 = 0U;
  c4_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[16].name = "minus";
  c4_info[16].dominantType = "double";
  c4_info[16].resolved = "[B]minus";
  c4_info[16].fileLength = 0U;
  c4_info[16].fileTime1 = 0U;
  c4_info[16].fileTime2 = 0U;
  c4_info[17].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[17].name = "plus";
  c4_info[17].dominantType = "double";
  c4_info[17].resolved = "[B]plus";
  c4_info[17].fileLength = 0U;
  c4_info[17].fileTime1 = 0U;
  c4_info[17].fileTime2 = 0U;
  c4_info[18].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[18].name = "all";
  c4_info[18].dominantType = "logical";
  c4_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c4_info[18].fileLength = 427U;
  c4_info[18].fileTime1 = 1221245538U;
  c4_info[18].fileTime2 = 0U;
  c4_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c4_info[19].name = "ischar";
  c4_info[19].dominantType = "logical";
  c4_info[19].resolved = "[B]ischar";
  c4_info[19].fileLength = 0U;
  c4_info[19].fileTime1 = 0U;
  c4_info[19].fileTime2 = 0U;
  c4_info[20].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c4_info[20].name = "islogical";
  c4_info[20].dominantType = "logical";
  c4_info[20].resolved = "[B]islogical";
  c4_info[20].fileLength = 0U;
  c4_info[20].fileTime1 = 0U;
  c4_info[20].fileTime2 = 0U;
  c4_info[21].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c4_info[21].name = "lt";
  c4_info[21].dominantType = "double";
  c4_info[21].resolved = "[B]lt";
  c4_info[21].fileLength = 0U;
  c4_info[21].fileTime1 = 0U;
  c4_info[21].fileTime2 = 0U;
  c4_info[22].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c4_info[22].name = "eml_all_or_any";
  c4_info[22].dominantType = "char";
  c4_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c4_info[22].fileLength = 3914U;
  c4_info[22].fileTime1 = 1271383994U;
  c4_info[22].fileTime2 = 0U;
  c4_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c4_info[23].name = "isequal";
  c4_info[23].dominantType = "double";
  c4_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c4_info[23].fileLength = 180U;
  c4_info[23].fileTime1 = 1226552070U;
  c4_info[23].fileTime2 = 0U;
  c4_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c4_info[24].name = "false";
  c4_info[24].dominantType = "";
  c4_info[24].resolved = "[B]false";
  c4_info[24].fileLength = 0U;
  c4_info[24].fileTime1 = 0U;
  c4_info[24].fileTime2 = 0U;
  c4_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c4_info[25].name = "eml_isequal_core";
  c4_info[25].dominantType = "double";
  c4_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c4_info[25].fileLength = 4192U;
  c4_info[25].fileTime1 = 1258039010U;
  c4_info[25].fileTime2 = 0U;
  c4_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c4_info[26].name = "ge";
  c4_info[26].dominantType = "double";
  c4_info[26].resolved = "[B]ge";
  c4_info[26].fileLength = 0U;
  c4_info[26].fileTime1 = 0U;
  c4_info[26].fileTime2 = 0U;
  c4_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c4_info[27].name = "isnumeric";
  c4_info[27].dominantType = "logical";
  c4_info[27].resolved = "[B]isnumeric";
  c4_info[27].fileLength = 0U;
  c4_info[27].fileTime1 = 0U;
  c4_info[27].fileTime2 = 0U;
  c4_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!same_size";
  c4_info[28].name = "ndims";
  c4_info[28].dominantType = "logical";
  c4_info[28].resolved = "[B]ndims";
  c4_info[28].fileLength = 0U;
  c4_info[28].fileTime1 = 0U;
  c4_info[28].fileTime2 = 0U;
  c4_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!same_size";
  c4_info[29].name = "ne";
  c4_info[29].dominantType = "double";
  c4_info[29].resolved = "[B]ne";
  c4_info[29].fileLength = 0U;
  c4_info[29].fileTime1 = 0U;
  c4_info[29].fileTime2 = 0U;
  c4_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!same_size";
  c4_info[30].name = "true";
  c4_info[30].dominantType = "";
  c4_info[30].resolved = "[B]true";
  c4_info[30].fileLength = 0U;
  c4_info[30].fileTime1 = 0U;
  c4_info[30].fileTime2 = 0U;
  c4_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c4_info[31].name = "eml_const_nonsingleton_dim";
  c4_info[31].dominantType = "logical";
  c4_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c4_info[31].fileLength = 1473U;
  c4_info[31].fileTime1 = 1240240402U;
  c4_info[31].fileTime2 = 0U;
  c4_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c4_info[32].name = "isempty";
  c4_info[32].dominantType = "logical";
  c4_info[32].resolved = "[B]isempty";
  c4_info[32].fileLength = 0U;
  c4_info[32].fileTime1 = 0U;
  c4_info[32].fileTime2 = 0U;
  c4_info[33].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[33].name = "mrdivide";
  c4_info[33].dominantType = "double";
  c4_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c4_info[33].fileLength = 432U;
  c4_info[33].fileTime1 = 1277726622U;
  c4_info[33].fileTime2 = 0U;
  c4_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c4_info[34].name = "ctranspose";
  c4_info[34].dominantType = "double";
  c4_info[34].resolved = "[B]ctranspose";
  c4_info[34].fileLength = 0U;
  c4_info[34].fileTime1 = 0U;
  c4_info[34].fileTime2 = 0U;
  c4_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c4_info[35].name = "mldivide";
  c4_info[35].dominantType = "double";
  c4_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c4_info[35].fileLength = 494U;
  c4_info[35].fileTime1 = 1277726622U;
  c4_info[35].fileTime2 = 0U;
  c4_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c4_info[36].name = "eml_lusolve";
  c4_info[36].dominantType = "double";
  c4_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c4_info[36].fileLength = 5239U;
  c4_info[36].fileTime1 = 1264408552U;
  c4_info[36].fileTime2 = 0U;
  c4_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c4_info[37].name = "eml_index_class";
  c4_info[37].dominantType = "";
  c4_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[37].fileLength = 909U;
  c4_info[37].fileTime1 = 1192445182U;
  c4_info[37].fileTime2 = 0U;
  c4_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c4_info[38].name = "cast";
  c4_info[38].dominantType = "double";
  c4_info[38].resolved = "[B]cast";
  c4_info[38].fileLength = 0U;
  c4_info[38].fileTime1 = 0U;
  c4_info[38].fileTime2 = 0U;
  c4_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c4_info[39].name = "nargout";
  c4_info[39].dominantType = "";
  c4_info[39].resolved = "[B]nargout";
  c4_info[39].fileLength = 0U;
  c4_info[39].fileTime1 = 0U;
  c4_info[39].fileTime2 = 0U;
  c4_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c4_info[40].name = "ones";
  c4_info[40].dominantType = "char";
  c4_info[40].resolved = "[B]ones";
  c4_info[40].fileLength = 0U;
  c4_info[40].fileTime1 = 0U;
  c4_info[40].fileTime2 = 0U;
  c4_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c4_info[41].name = "eml_xgetrf";
  c4_info[41].dominantType = "int32";
  c4_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c4_info[41].fileLength = 204U;
  c4_info[41].fileTime1 = 1271383994U;
  c4_info[41].fileTime2 = 0U;
  c4_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c4_info[42].name = "eml_lapack_xgetrf";
  c4_info[42].dominantType = "int32";
  c4_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c4_info[42].fileLength = 211U;
  c4_info[42].fileTime1 = 1271383994U;
  c4_info[42].fileTime2 = 0U;
  c4_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c4_info[43].name = "eml_matlab_zgetrf";
  c4_info[43].dominantType = "int32";
  c4_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[43].fileLength = 2193U;
  c4_info[43].fileTime1 = 1271383998U;
  c4_info[43].fileTime2 = 0U;
  c4_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[44].name = "realmin";
  c4_info[44].dominantType = "char";
  c4_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c4_info[44].fileLength = 749U;
  c4_info[44].fileTime1 = 1226552078U;
  c4_info[44].fileTime2 = 0U;
  c4_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c4_info[45].name = "mpower";
  c4_info[45].dominantType = "double";
  c4_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c4_info[45].fileLength = 3710U;
  c4_info[45].fileTime1 = 1238412688U;
  c4_info[45].fileTime2 = 0U;
  c4_info[46].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c4_info[46].name = "power";
  c4_info[46].dominantType = "double";
  c4_info[46].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[46].fileLength = 5380U;
  c4_info[46].fileTime1 = 1228068698U;
  c4_info[46].fileTime2 = 0U;
  c4_info[47].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[47].name = "eml_scalar_eg";
  c4_info[47].dominantType = "double";
  c4_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[47].fileLength = 3068U;
  c4_info[47].fileTime1 = 1240240410U;
  c4_info[47].fileTime2 = 0U;
  c4_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[48].name = "isstruct";
  c4_info[48].dominantType = "double";
  c4_info[48].resolved = "[B]isstruct";
  c4_info[48].fileLength = 0U;
  c4_info[48].fileTime1 = 0U;
  c4_info[48].fileTime2 = 0U;
  c4_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m!allreal";
  c4_info[49].name = "isreal";
  c4_info[49].dominantType = "double";
  c4_info[49].resolved = "[B]isreal";
  c4_info[49].fileLength = 0U;
  c4_info[49].fileTime1 = 0U;
  c4_info[49].fileTime2 = 0U;
  c4_info[50].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[50].name = "eml_scalexp_alloc";
  c4_info[50].dominantType = "double";
  c4_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c4_info[50].fileLength = 932U;
  c4_info[50].fileTime1 = 1261926670U;
  c4_info[50].fileTime2 = 0U;
  c4_info[51].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[51].name = "eml_scalar_floor";
  c4_info[51].dominantType = "double";
  c4_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c4_info[51].fileLength = 260U;
  c4_info[51].fileTime1 = 1209309190U;
  c4_info[51].fileTime2 = 0U;
  c4_info[52].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[52].name = "eml_error";
  c4_info[52].dominantType = "char";
  c4_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c4_info[52].fileLength = 315U;
  c4_info[52].fileTime1 = 1213905144U;
  c4_info[52].fileTime2 = 0U;
  c4_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[53].name = "eps";
  c4_info[53].dominantType = "char";
  c4_info[53].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c4_info[53].fileLength = 1331U;
  c4_info[53].fileTime1 = 1246588112U;
  c4_info[53].fileTime2 = 0U;
  c4_info[54].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c4_info[54].name = "eml_is_float_class";
  c4_info[54].dominantType = "char";
  c4_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c4_info[54].fileLength = 226U;
  c4_info[54].fileTime1 = 1197825240U;
  c4_info[54].fileTime2 = 0U;
  c4_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[55].name = "min";
  c4_info[55].dominantType = "int32";
  c4_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c4_info[55].fileLength = 362U;
  c4_info[55].fileTime1 = 1245080764U;
  c4_info[55].fileTime2 = 0U;
  c4_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c4_info[56].name = "le";
  c4_info[56].dominantType = "double";
  c4_info[56].resolved = "[B]le";
  c4_info[56].fileLength = 0U;
  c4_info[56].fileTime1 = 0U;
  c4_info[56].fileTime2 = 0U;
  c4_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c4_info[57].name = "eml_min_or_max";
  c4_info[57].dominantType = "int32";
  c4_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c4_info[57].fileLength = 9967U;
  c4_info[57].fileTime1 = 1261926670U;
  c4_info[57].fileTime2 = 0U;
  c4_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[58].name = "colon";
  c4_info[58].dominantType = "int32";
  c4_info[58].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c4_info[58].fileLength = 8633U;
  c4_info[58].fileTime1 = 1273822662U;
  c4_info[58].fileTime2 = 0U;
  c4_info[59].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c4_info[59].name = "floor";
  c4_info[59].dominantType = "double";
  c4_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c4_info[59].fileLength = 332U;
  c4_info[59].fileTime1 = 1203422822U;
  c4_info[59].fileTime2 = 0U;
  c4_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c4_info[60].name = "intmin";
  c4_info[60].dominantType = "char";
  c4_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c4_info[60].fileLength = 1505U;
  c4_info[60].fileTime1 = 1192445128U;
  c4_info[60].fileTime2 = 0U;
  c4_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c4_info[61].name = "int32";
  c4_info[61].dominantType = "double";
  c4_info[61].resolved = "[B]int32";
  c4_info[61].fileLength = 0U;
  c4_info[61].fileTime1 = 0U;
  c4_info[61].fileTime2 = 0U;
  c4_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c4_info[62].name = "intmax";
  c4_info[62].dominantType = "char";
  c4_info[62].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c4_info[62].fileLength = 1535U;
  c4_info[62].fileTime1 = 1192445128U;
  c4_info[62].fileTime2 = 0U;
  c4_info[63].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon";
  c4_info[63].name = "double";
  c4_info[63].dominantType = "int32";
  c4_info[63].resolved = "[B]double";
  c4_info[63].fileLength = 0U;
  c4_info[63].fileTime1 = 0U;
  c4_info[63].fileTime2 = 0U;
}

static void c4_b_info_helper(c4_ResolvedFunctionInfo c4_info[121])
{
  c4_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c4_info[64].name = "rdivide";
  c4_info[64].dominantType = "double";
  c4_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c4_info[64].fileLength = 403U;
  c4_info[64].fileTime1 = 1245080820U;
  c4_info[64].fileTime2 = 0U;
  c4_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c4_info[65].name = "eml_div";
  c4_info[65].dominantType = "double";
  c4_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c4_info[65].fileLength = 4918U;
  c4_info[65].fileTime1 = 1267038210U;
  c4_info[65].fileTime2 = 0U;
  c4_info[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon";
  c4_info[66].name = "transpose";
  c4_info[66].dominantType = "int32";
  c4_info[66].resolved = "[B]transpose";
  c4_info[66].fileLength = 0U;
  c4_info[66].fileTime1 = 0U;
  c4_info[66].fileTime2 = 0U;
  c4_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[67].name = "eml_index_plus";
  c4_info[67].dominantType = "int32";
  c4_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[67].fileLength = 272U;
  c4_info[67].fileTime1 = 1192445184U;
  c4_info[67].fileTime2 = 0U;
  c4_info[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[68].name = "eml_index_minus";
  c4_info[68].dominantType = "int32";
  c4_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c4_info[68].fileLength = 277U;
  c4_info[68].fileTime1 = 1192445184U;
  c4_info[68].fileTime2 = 0U;
  c4_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[69].name = "eml_index_times";
  c4_info[69].dominantType = "int32";
  c4_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c4_info[69].fileLength = 280U;
  c4_info[69].fileTime1 = 1192445186U;
  c4_info[69].fileTime2 = 0U;
  c4_info[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[70].name = "eml_ixamax";
  c4_info[70].dominantType = "int32";
  c4_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c4_info[70].fileLength = 731U;
  c4_info[70].fileTime1 = 1209309244U;
  c4_info[70].fileTime2 = 0U;
  c4_info[71].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c4_info[71].name = "eml_refblas_ixamax";
  c4_info[71].dominantType = "int32";
  c4_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c4_info[71].fileLength = 740U;
  c4_info[71].fileTime1 = 1192445266U;
  c4_info[71].fileTime2 = 0U;
  c4_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c4_info[72].name = "eml_xcabs1";
  c4_info[72].dominantType = "double";
  c4_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c4_info[72].fileLength = 419U;
  c4_info[72].fileTime1 = 1209309246U;
  c4_info[72].fileTime2 = 0U;
  c4_info[73].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c4_info[73].name = "real";
  c4_info[73].dominantType = "double";
  c4_info[73].resolved = "[B]real";
  c4_info[73].fileLength = 0U;
  c4_info[73].fileTime1 = 0U;
  c4_info[73].fileTime2 = 0U;
  c4_info[74].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c4_info[74].name = "abs";
  c4_info[74].dominantType = "double";
  c4_info[74].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[74].fileLength = 566U;
  c4_info[74].fileTime1 = 1221245532U;
  c4_info[74].fileTime2 = 0U;
  c4_info[75].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[75].name = "eml_scalar_abs";
  c4_info[75].dominantType = "double";
  c4_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c4_info[75].fileLength = 461U;
  c4_info[75].fileTime1 = 1203422760U;
  c4_info[75].fileTime2 = 0U;
  c4_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c4_info[76].name = "imag";
  c4_info[76].dominantType = "double";
  c4_info[76].resolved = "[B]imag";
  c4_info[76].fileLength = 0U;
  c4_info[76].fileTime1 = 0U;
  c4_info[76].fileTime2 = 0U;
  c4_info[77].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[77].name = "eml_xswap";
  c4_info[77].dominantType = "int32";
  c4_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c4_info[77].fileLength = 1330U;
  c4_info[77].fileTime1 = 1209309260U;
  c4_info[77].fileTime2 = 0U;
  c4_info[78].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c4_info[78].name = "eml_refblas_xswap";
  c4_info[78].dominantType = "int32";
  c4_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c4_info[78].fileLength = 905U;
  c4_info[78].fileTime1 = 1238412670U;
  c4_info[78].fileTime2 = 0U;
  c4_info[79].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[79].name = "eml_xgeru";
  c4_info[79].dominantType = "int32";
  c4_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c4_info[79].fileLength = 2462U;
  c4_info[79].fileTime1 = 1209309256U;
  c4_info[79].fileTime2 = 0U;
  c4_info[80].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c4_info[80].name = "eml_xger";
  c4_info[80].dominantType = "int32";
  c4_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c4_info[80].fileLength = 2168U;
  c4_info[80].fileTime1 = 1209309254U;
  c4_info[80].fileTime2 = 0U;
  c4_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c4_info[81].name = "eml_refblas_xger";
  c4_info[81].dominantType = "int32";
  c4_info[81].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c4_info[81].fileLength = 411U;
  c4_info[81].fileTime1 = 1211194448U;
  c4_info[81].fileTime2 = 0U;
  c4_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c4_info[82].name = "eml_refblas_xgerx";
  c4_info[82].dominantType = "int32";
  c4_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[82].fileLength = 2231U;
  c4_info[82].fileTime1 = 1238412668U;
  c4_info[82].fileTime2 = 0U;
  c4_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[83].name = "times";
  c4_info[83].dominantType = "double";
  c4_info[83].resolved = "[B]times";
  c4_info[83].fileLength = 0U;
  c4_info[83].fileTime1 = 0U;
  c4_info[83].fileTime2 = 0U;
  c4_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!warn_singular";
  c4_info[84].name = "eml_warning";
  c4_info[84].dominantType = "char";
  c4_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c4_info[84].fileLength = 262U;
  c4_info[84].fileTime1 = 1236232078U;
  c4_info[84].fileTime2 = 0U;
  c4_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN";
  c4_info[85].name = "eml_xtrsm";
  c4_info[85].dominantType = "int32";
  c4_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c4_info[85].fileLength = 2383U;
  c4_info[85].fileTime1 = 1209309262U;
  c4_info[85].fileTime2 = 0U;
  c4_info[86].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m!itcount";
  c4_info[86].name = "length";
  c4_info[86].dominantType = "double";
  c4_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c4_info[86].fileLength = 326U;
  c4_info[86].fileTime1 = 1226552074U;
  c4_info[86].fileTime2 = 0U;
  c4_info[87].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c4_info[87].name = "eml_refblas_xtrsm";
  c4_info[87].dominantType = "int32";
  c4_info[87].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c4_info[87].fileLength = 13101U;
  c4_info[87].fileTime1 = 1252487206U;
  c4_info[87].fileTime2 = 0U;
  c4_info[88].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[88].name = "eml_xgemm";
  c4_info[88].dominantType = "int32";
  c4_info[88].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c4_info[88].fileLength = 3184U;
  c4_info[88].fileTime1 = 1209309252U;
  c4_info[88].fileTime2 = 0U;
  c4_info[89].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c4_info[89].name = "eml_refblas_xgemm";
  c4_info[89].dominantType = "int32";
  c4_info[89].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c4_info[89].fileLength = 5748U;
  c4_info[89].fileTime1 = 1228068672U;
  c4_info[89].fileTime2 = 0U;
  c4_info[90].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[90].name = "atan2";
  c4_info[90].dominantType = "double";
  c4_info[90].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c4_info[90].fileLength = 605U;
  c4_info[90].fileTime1 = 1236232054U;
  c4_info[90].fileTime2 = 0U;
  c4_info[91].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c4_info[91].name = "eml_scalar_atan2";
  c4_info[91].dominantType = "double";
  c4_info[91].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m";
  c4_info[91].fileLength = 964U;
  c4_info[91].fileTime1 = 1209309186U;
  c4_info[91].fileTime2 = 0U;
  c4_info[92].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m!isInRange";
  c4_info[92].name = "pi";
  c4_info[92].dominantType = "";
  c4_info[92].resolved = "[B]pi";
  c4_info[92].fileLength = 0U;
  c4_info[92].fileTime1 = 0U;
  c4_info[92].fileTime2 = 0U;
  c4_info[93].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m!isInRange";
  c4_info[93].name = "and";
  c4_info[93].dominantType = "logical";
  c4_info[93].resolved = "[B]and";
  c4_info[93].fileLength = 0U;
  c4_info[93].fileTime1 = 0U;
  c4_info[93].fileTime2 = 0U;
  c4_info[94].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[94].name = "expWre";
  c4_info[94].dominantType = "double";
  c4_info[94].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/expWre.m";
  c4_info[94].fileLength = 413U;
  c4_info[94].fileTime1 = 1366220272U;
  c4_info[94].fileTime2 = 0U;
  c4_info[95].context = "[E]D:/Learn/Project_Matlab/Fanuc/expWre.m";
  c4_info[95].name = "eye";
  c4_info[95].dominantType = "double";
  c4_info[95].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c4_info[95].fileLength = 1765U;
  c4_info[95].fileTime1 = 1219731288U;
  c4_info[95].fileTime2 = 0U;
  c4_info[96].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c4_info[96].name = "eml_assert_valid_size_arg";
  c4_info[96].dominantType = "double";
  c4_info[96].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c4_info[96].fileLength = 3315U;
  c4_info[96].fileTime1 = 1256367816U;
  c4_info[96].fileTime2 = 0U;
  c4_info[97].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c4_info[97].name = "isinf";
  c4_info[97].dominantType = "double";
  c4_info[97].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c4_info[97].fileLength = 541U;
  c4_info[97].fileTime1 = 1271383988U;
  c4_info[97].fileTime2 = 0U;
  c4_info[98].context = "[E]D:/Learn/Project_Matlab/Fanuc/expWre.m";
  c4_info[98].name = "expRot";
  c4_info[98].dominantType = "double";
  c4_info[98].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/expRot.m";
  c4_info[98].fileLength = 236U;
  c4_info[98].fileTime1 = 1366773052U;
  c4_info[98].fileTime2 = 0U;
  c4_info[99].context = "[E]D:/Learn/Project_Matlab/Fanuc/expRot.m";
  c4_info[99].name = "skew";
  c4_info[99].dominantType = "double";
  c4_info[99].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/skew.m";
  c4_info[99].fileLength = 450U;
  c4_info[99].fileTime1 = 1399884445U;
  c4_info[99].fileTime2 = 0U;
  c4_info[100].context = "[E]D:/Learn/Project_Matlab/Fanuc/expRot.m";
  c4_info[100].name = "sin";
  c4_info[100].dominantType = "double";
  c4_info[100].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c4_info[100].fileLength = 324U;
  c4_info[100].fileTime1 = 1203422842U;
  c4_info[100].fileTime2 = 0U;
  c4_info[101].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c4_info[101].name = "eml_scalar_sin";
  c4_info[101].dominantType = "double";
  c4_info[101].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c4_info[101].fileLength = 601U;
  c4_info[101].fileTime1 = 1209309190U;
  c4_info[101].fileTime2 = 0U;
  c4_info[102].context = "[E]D:/Learn/Project_Matlab/Fanuc/expRot.m";
  c4_info[102].name = "cos";
  c4_info[102].dominantType = "double";
  c4_info[102].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c4_info[102].fileLength = 324U;
  c4_info[102].fileTime1 = 1203422750U;
  c4_info[102].fileTime2 = 0U;
  c4_info[103].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c4_info[103].name = "eml_scalar_cos";
  c4_info[103].dominantType = "double";
  c4_info[103].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c4_info[103].fileLength = 602U;
  c4_info[103].fileTime1 = 1209309186U;
  c4_info[103].fileTime2 = 0U;
  c4_info[104].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[104].name = "subPro3";
  c4_info[104].dominantType = "double";
  c4_info[104].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/subPro3.m";
  c4_info[104].fileLength = 1099U;
  c4_info[104].fileTime1 = 1367251936U;
  c4_info[104].fileTime2 = 0U;
  c4_info[105].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[105].name = "eml_xdotu";
  c4_info[105].dominantType = "int32";
  c4_info[105].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c4_info[105].fileLength = 1453U;
  c4_info[105].fileTime1 = 1209309250U;
  c4_info[105].fileTime2 = 0U;
  c4_info[106].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c4_info[106].name = "eml_xdot";
  c4_info[106].dominantType = "int32";
  c4_info[106].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c4_info[106].fileLength = 1330U;
  c4_info[106].fileTime1 = 1209309248U;
  c4_info[106].fileTime2 = 0U;
  c4_info[107].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c4_info[107].name = "eml_refblas_xdot";
  c4_info[107].dominantType = "int32";
  c4_info[107].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c4_info[107].fileLength = 343U;
  c4_info[107].fileTime1 = 1211194442U;
  c4_info[107].fileTime2 = 0U;
  c4_info[108].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c4_info[108].name = "eml_refblas_xdotx";
  c4_info[108].dominantType = "int32";
  c4_info[108].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c4_info[108].fileLength = 1605U;
  c4_info[108].fileTime1 = 1236232078U;
  c4_info[108].fileTime2 = 0U;
  c4_info[109].context = "[E]D:/Learn/Project_Matlab/Fanuc/subPro3.m";
  c4_info[109].name = "norm";
  c4_info[109].dominantType = "double";
  c4_info[109].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c4_info[109].fileLength = 5453U;
  c4_info[109].fileTime1 = 1271384008U;
  c4_info[109].fileTime2 = 0U;
  c4_info[110].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c4_info[110].name = "eml_xnrm2";
  c4_info[110].dominantType = "int32";
  c4_info[110].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c4_info[110].fileLength = 718U;
  c4_info[110].fileTime1 = 1209309256U;
  c4_info[110].fileTime2 = 0U;
  c4_info[111].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c4_info[111].name = "eml_refblas_xnrm2";
  c4_info[111].dominantType = "int32";
  c4_info[111].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c4_info[111].fileLength = 1433U;
  c4_info[111].fileTime1 = 1240240442U;
  c4_info[111].fileTime2 = 0U;
  c4_info[112].context = "[E]D:/Learn/Project_Matlab/Fanuc/subPro3.m";
  c4_info[112].name = "acos";
  c4_info[112].dominantType = "double";
  c4_info[112].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/acos.m";
  c4_info[112].fileLength = 585U;
  c4_info[112].fileTime1 = 1203422730U;
  c4_info[112].fileTime2 = 0U;
  c4_info[113].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/acos.m";
  c4_info[113].name = "eml_scalar_acos";
  c4_info[113].dominantType = "double";
  c4_info[113].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_acos.m";
  c4_info[113].fileLength = 553U;
  c4_info[113].fileTime1 = 1203422760U;
  c4_info[113].fileTime2 = 0U;
  c4_info[114].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[114].name = "any";
  c4_info[114].dominantType = "logical";
  c4_info[114].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c4_info[114].fileLength = 427U;
  c4_info[114].fileTime1 = 1221245538U;
  c4_info[114].fileTime2 = 0U;
  c4_info[115].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c4_info[115].name = "isnan";
  c4_info[115].dominantType = "logical";
  c4_info[115].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c4_info[115].fileLength = 541U;
  c4_info[115].fileTime1 = 1271383988U;
  c4_info[115].fileTime2 = 0U;
  c4_info[116].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[116].name = "subPro1";
  c4_info[116].dominantType = "double";
  c4_info[116].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/subPro1.m";
  c4_info[116].fileLength = 393U;
  c4_info[116].fileTime1 = 1336045298U;
  c4_info[116].fileTime2 = 0U;
  c4_info[117].context = "[E]D:/Learn/Project_Matlab/Fanuc/inv_kin.m";
  c4_info[117].name = "subPro2";
  c4_info[117].dominantType = "double";
  c4_info[117].resolved = "[E]D:/Learn/Project_Matlab/Fanuc/subPro2.m";
  c4_info[117].fileLength = 1886U;
  c4_info[117].fileTime1 = 1367255418U;
  c4_info[117].fileTime2 = 0U;
  c4_info[118].context = "[E]D:/Learn/Project_Matlab/Fanuc/subPro2.m!findCommon";
  c4_info[118].name = "det";
  c4_info[118].dominantType = "double";
  c4_info[118].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c4_info[118].fileLength = 755U;
  c4_info[118].fileTime1 = 1228068678U;
  c4_info[118].fileTime2 = 0U;
  c4_info[119].context = "[E]D:/Learn/Project_Matlab/Fanuc/subPro2.m";
  c4_info[119].name = "sqrt";
  c4_info[119].dominantType = "double";
  c4_info[119].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c4_info[119].fileLength = 572U;
  c4_info[119].fileTime1 = 1203422844U;
  c4_info[119].fileTime2 = 0U;
  c4_info[120].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c4_info[120].name = "eml_scalar_sqrt";
  c4_info[120].dominantType = "double";
  c4_info[120].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c4_info[120].fileLength = 664U;
  c4_info[120].fileTime1 = 1209309194U;
  c4_info[120].fileTime2 = 0U;
}

static void c4_emlrt_marshallIn(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *c4_theta, const char_T *
  c4_name, real_T c4_y[6])
{
  real_T c4_dv36[6];
  int32_T c4_i903;
  sf_mex_import(c4_name, sf_mex_dup(c4_theta), c4_dv36, 1, 0, 0U, 1, 0U, 1, 6);
  for (c4_i903 = 0; c4_i903 < 6; c4_i903 = c4_i903 + 1) {
    c4_y[c4_i903] = c4_dv36[c4_i903];
  }

  sf_mex_destroy(&c4_theta);
}

static uint8_T c4_b_emlrt_marshallIn(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance, const mxArray *
  c4_b_is_active_c4_EurlerDynJointVerify, const char_T *c4_name)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_name, sf_mex_dup(c4_b_is_active_c4_EurlerDynJointVerify),
                &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_b_is_active_c4_EurlerDynJointVerify);
  return c4_y;
}

static void init_dsm_address_info(SFc4_EurlerDynJointVerifyInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c4_EurlerDynJointVerify_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(26272930U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1779455369U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2790961819U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1307763216U);
}

mxArray *sf_c4_EurlerDynJointVerify_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3601552445U);
    pr[1] = (double)(3899762000U);
    pr[2] = (double)(2837095841U);
    pr[3] = (double)(1261358445U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
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

static mxArray *sf_get_sim_state_info_c4_EurlerDynJointVerify(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"theta\",},{M[8],M[0],T\"is_active_c4_EurlerDynJointVerify\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_EurlerDynJointVerify_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
    chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_EurlerDynJointVerifyMachineNumber_,
           4,
           1,
           1,
           4,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"EndPos");
          _SFD_SET_DATA_PROPS(1,10,0,0,"init_Rot");
          _SFD_SET_DATA_PROPS(2,2,0,1,"theta");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,173);
        _SFD_CV_INIT_SCRIPT(0,2,8,0,0,2,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"inv_kin",0,-1,2879);
        _SFD_CV_INIT_SCRIPT_FCN(0,1,"isInRange",2881,-1,2974);
        _SFD_CV_INIT_SCRIPT_IF(0,0,939,964,1003,1032);
        _SFD_CV_INIT_SCRIPT_IF(0,1,1003,1032,-1,1032);
        _SFD_CV_INIT_SCRIPT_IF(0,2,1348,1382,1597,1701);
        _SFD_CV_INIT_SCRIPT_IF(0,3,1597,1639,-1,-2);
        _SFD_CV_INIT_SCRIPT_IF(0,4,1727,1765,-1,2831);
        _SFD_CV_INIT_SCRIPT_IF(0,5,1889,1923,2249,2377);
        _SFD_CV_INIT_SCRIPT_IF(0,6,2249,2291,-1,-2);
        _SFD_CV_INIT_SCRIPT_IF(0,7,2424,2463,-1,2811);
        _SFD_CV_INIT_SCRIPT_FOR(0,0,1707,1723,2836);
        _SFD_CV_INIT_SCRIPT_FOR(0,1,2395,2412,2823);
        _SFD_CV_INIT_SCRIPT(1,1,2,0,0,0,0,3,1);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"expWre",30,-1,391);
        _SFD_CV_INIT_SCRIPT_IF(1,0,67,85,-1,135);
        _SFD_CV_INIT_SCRIPT_IF(1,1,188,221,267,358);

        {
          static int condStart[] = { 191, 202, 213 };

          static int condEnd[] = { 198, 209, 220 };

          static int pfixExpr[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_SCRIPT_MCDC(1,0,191,220,3,0,&(condStart[0]),&(condEnd[0]),
            5,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_SCRIPT(2,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"expRot",34,-1,217);
        _SFD_CV_INIT_SCRIPT(3,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(3,0,"skew",0,-1,450);
        _SFD_CV_INIT_SCRIPT_IF(3,0,27,44,-1,92);
        _SFD_CV_INIT_SCRIPT(4,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(4,0,"subPro3",0,-1,1098);
        _SFD_CV_INIT_SCRIPT_IF(4,0,995,1006,1029,1085);
        _SFD_CV_INIT_SCRIPT(5,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(5,0,"subPro1",0,-1,373);
        _SFD_CV_INIT_SCRIPT(6,2,5,0,0,1,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(6,0,"subPro2",0,-1,1337);
        _SFD_CV_INIT_SCRIPT_FCN(6,1,"findCommon",1340,-1,1814);
        _SFD_CV_INIT_SCRIPT_IF(6,0,887,898,921,990);
        _SFD_CV_INIT_SCRIPT_IF(6,1,921,937,960,990);
        _SFD_CV_INIT_SCRIPT_IF(6,2,996,1006,-1,1323);
        _SFD_CV_INIT_SCRIPT_IF(6,3,1468,1482,-1,1619);
        _SFD_CV_INIT_SCRIPT_IF(6,4,1629,1643,-1,1736);
        _SFD_CV_INIT_SCRIPT_FOR(6,0,1011,1022,1315);
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
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_d_sf_marshall);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_c_sf_marshall);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshall);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 9;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshall);
        }

        {
          real_T (*c4_EndPos)[3];
          real_T (*c4_theta)[6];
          c4_theta = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c4_EndPos = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c4_EndPos);
          _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c4_init_Rot);
          _SFD_SET_DATA_VALUE_PTR(2U, *c4_theta);
          _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c4_L);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration
        (_EurlerDynJointVerifyMachineNumber_,chartInstance->chartNumber,
         chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c4_EurlerDynJointVerify(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c4_EurlerDynJointVerify
    ((SFc4_EurlerDynJointVerifyInstanceStruct*) chartInstanceVar);
  initialize_c4_EurlerDynJointVerify((SFc4_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c4_EurlerDynJointVerify(void *chartInstanceVar)
{
  enable_c4_EurlerDynJointVerify((SFc4_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c4_EurlerDynJointVerify(void *chartInstanceVar)
{
  disable_c4_EurlerDynJointVerify((SFc4_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c4_EurlerDynJointVerify(void *chartInstanceVar)
{
  sf_c4_EurlerDynJointVerify((SFc4_EurlerDynJointVerifyInstanceStruct*)
    chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c4_EurlerDynJointVerify(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_EurlerDynJointVerify
    ((SFc4_EurlerDynJointVerifyInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c4_EurlerDynJointVerify();/* state var info */
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

static void sf_internal_set_sim_state_c4_EurlerDynJointVerify(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_EurlerDynJointVerify();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_EurlerDynJointVerify((SFc4_EurlerDynJointVerifyInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c4_EurlerDynJointVerify(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_EurlerDynJointVerify(S);
}

static void sf_opaque_set_sim_state_c4_EurlerDynJointVerify(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c4_EurlerDynJointVerify(S, st);
}

static void sf_opaque_terminate_c4_EurlerDynJointVerify(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_EurlerDynJointVerifyInstanceStruct*) chartInstanceVar
      )->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c4_EurlerDynJointVerify((SFc4_EurlerDynJointVerifyInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c4_EurlerDynJointVerify
    ((SFc4_EurlerDynJointVerifyInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_EurlerDynJointVerify(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_EurlerDynJointVerify
      ((SFc4_EurlerDynJointVerifyInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_EurlerDynJointVerify(SimStruct *S)
{
  /* Actual parameters from chart:
     L init_Rot
   */
  const char_T *rtParamNames[] = { "p1", "p2" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for L*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for init_Rot*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"EurlerDynJointVerify",
      "EurlerDynJointVerify",4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"EurlerDynJointVerify",
                "EurlerDynJointVerify",4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"EurlerDynJointVerify",
      "EurlerDynJointVerify",4,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"EurlerDynJointVerify",
        "EurlerDynJointVerify",4,1);
      sf_mark_chart_reusable_outputs(S,"EurlerDynJointVerify",
        "EurlerDynJointVerify",4,1);
    }

    sf_set_rtw_dwork_info(S,"EurlerDynJointVerify","EurlerDynJointVerify",4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4291737571U));
  ssSetChecksum1(S,(2241111574U));
  ssSetChecksum2(S,(223710917U));
  ssSetChecksum3(S,(1143837615U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c4_EurlerDynJointVerify(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "EurlerDynJointVerify", "EurlerDynJointVerify",4);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_EurlerDynJointVerify(SimStruct *S)
{
  SFc4_EurlerDynJointVerifyInstanceStruct *chartInstance;
  chartInstance = (SFc4_EurlerDynJointVerifyInstanceStruct *)malloc(sizeof
    (SFc4_EurlerDynJointVerifyInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_EurlerDynJointVerifyInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_EurlerDynJointVerify;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c4_EurlerDynJointVerify;
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

void c4_EurlerDynJointVerify_method_dispatcher(SimStruct *S, int_T method, void *
  data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_EurlerDynJointVerify(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_EurlerDynJointVerify(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_EurlerDynJointVerify(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_EurlerDynJointVerify_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}