#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_7655511453115168940) {
   out_7655511453115168940[0] = delta_x[0] + nom_x[0];
   out_7655511453115168940[1] = delta_x[1] + nom_x[1];
   out_7655511453115168940[2] = delta_x[2] + nom_x[2];
   out_7655511453115168940[3] = delta_x[3] + nom_x[3];
   out_7655511453115168940[4] = delta_x[4] + nom_x[4];
   out_7655511453115168940[5] = delta_x[5] + nom_x[5];
   out_7655511453115168940[6] = delta_x[6] + nom_x[6];
   out_7655511453115168940[7] = delta_x[7] + nom_x[7];
   out_7655511453115168940[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2885483212860589707) {
   out_2885483212860589707[0] = -nom_x[0] + true_x[0];
   out_2885483212860589707[1] = -nom_x[1] + true_x[1];
   out_2885483212860589707[2] = -nom_x[2] + true_x[2];
   out_2885483212860589707[3] = -nom_x[3] + true_x[3];
   out_2885483212860589707[4] = -nom_x[4] + true_x[4];
   out_2885483212860589707[5] = -nom_x[5] + true_x[5];
   out_2885483212860589707[6] = -nom_x[6] + true_x[6];
   out_2885483212860589707[7] = -nom_x[7] + true_x[7];
   out_2885483212860589707[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3050833487134891442) {
   out_3050833487134891442[0] = 1.0;
   out_3050833487134891442[1] = 0;
   out_3050833487134891442[2] = 0;
   out_3050833487134891442[3] = 0;
   out_3050833487134891442[4] = 0;
   out_3050833487134891442[5] = 0;
   out_3050833487134891442[6] = 0;
   out_3050833487134891442[7] = 0;
   out_3050833487134891442[8] = 0;
   out_3050833487134891442[9] = 0;
   out_3050833487134891442[10] = 1.0;
   out_3050833487134891442[11] = 0;
   out_3050833487134891442[12] = 0;
   out_3050833487134891442[13] = 0;
   out_3050833487134891442[14] = 0;
   out_3050833487134891442[15] = 0;
   out_3050833487134891442[16] = 0;
   out_3050833487134891442[17] = 0;
   out_3050833487134891442[18] = 0;
   out_3050833487134891442[19] = 0;
   out_3050833487134891442[20] = 1.0;
   out_3050833487134891442[21] = 0;
   out_3050833487134891442[22] = 0;
   out_3050833487134891442[23] = 0;
   out_3050833487134891442[24] = 0;
   out_3050833487134891442[25] = 0;
   out_3050833487134891442[26] = 0;
   out_3050833487134891442[27] = 0;
   out_3050833487134891442[28] = 0;
   out_3050833487134891442[29] = 0;
   out_3050833487134891442[30] = 1.0;
   out_3050833487134891442[31] = 0;
   out_3050833487134891442[32] = 0;
   out_3050833487134891442[33] = 0;
   out_3050833487134891442[34] = 0;
   out_3050833487134891442[35] = 0;
   out_3050833487134891442[36] = 0;
   out_3050833487134891442[37] = 0;
   out_3050833487134891442[38] = 0;
   out_3050833487134891442[39] = 0;
   out_3050833487134891442[40] = 1.0;
   out_3050833487134891442[41] = 0;
   out_3050833487134891442[42] = 0;
   out_3050833487134891442[43] = 0;
   out_3050833487134891442[44] = 0;
   out_3050833487134891442[45] = 0;
   out_3050833487134891442[46] = 0;
   out_3050833487134891442[47] = 0;
   out_3050833487134891442[48] = 0;
   out_3050833487134891442[49] = 0;
   out_3050833487134891442[50] = 1.0;
   out_3050833487134891442[51] = 0;
   out_3050833487134891442[52] = 0;
   out_3050833487134891442[53] = 0;
   out_3050833487134891442[54] = 0;
   out_3050833487134891442[55] = 0;
   out_3050833487134891442[56] = 0;
   out_3050833487134891442[57] = 0;
   out_3050833487134891442[58] = 0;
   out_3050833487134891442[59] = 0;
   out_3050833487134891442[60] = 1.0;
   out_3050833487134891442[61] = 0;
   out_3050833487134891442[62] = 0;
   out_3050833487134891442[63] = 0;
   out_3050833487134891442[64] = 0;
   out_3050833487134891442[65] = 0;
   out_3050833487134891442[66] = 0;
   out_3050833487134891442[67] = 0;
   out_3050833487134891442[68] = 0;
   out_3050833487134891442[69] = 0;
   out_3050833487134891442[70] = 1.0;
   out_3050833487134891442[71] = 0;
   out_3050833487134891442[72] = 0;
   out_3050833487134891442[73] = 0;
   out_3050833487134891442[74] = 0;
   out_3050833487134891442[75] = 0;
   out_3050833487134891442[76] = 0;
   out_3050833487134891442[77] = 0;
   out_3050833487134891442[78] = 0;
   out_3050833487134891442[79] = 0;
   out_3050833487134891442[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6858776502225367365) {
   out_6858776502225367365[0] = state[0];
   out_6858776502225367365[1] = state[1];
   out_6858776502225367365[2] = state[2];
   out_6858776502225367365[3] = state[3];
   out_6858776502225367365[4] = state[4];
   out_6858776502225367365[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6858776502225367365[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6858776502225367365[7] = state[7];
   out_6858776502225367365[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8920567495883519593) {
   out_8920567495883519593[0] = 1;
   out_8920567495883519593[1] = 0;
   out_8920567495883519593[2] = 0;
   out_8920567495883519593[3] = 0;
   out_8920567495883519593[4] = 0;
   out_8920567495883519593[5] = 0;
   out_8920567495883519593[6] = 0;
   out_8920567495883519593[7] = 0;
   out_8920567495883519593[8] = 0;
   out_8920567495883519593[9] = 0;
   out_8920567495883519593[10] = 1;
   out_8920567495883519593[11] = 0;
   out_8920567495883519593[12] = 0;
   out_8920567495883519593[13] = 0;
   out_8920567495883519593[14] = 0;
   out_8920567495883519593[15] = 0;
   out_8920567495883519593[16] = 0;
   out_8920567495883519593[17] = 0;
   out_8920567495883519593[18] = 0;
   out_8920567495883519593[19] = 0;
   out_8920567495883519593[20] = 1;
   out_8920567495883519593[21] = 0;
   out_8920567495883519593[22] = 0;
   out_8920567495883519593[23] = 0;
   out_8920567495883519593[24] = 0;
   out_8920567495883519593[25] = 0;
   out_8920567495883519593[26] = 0;
   out_8920567495883519593[27] = 0;
   out_8920567495883519593[28] = 0;
   out_8920567495883519593[29] = 0;
   out_8920567495883519593[30] = 1;
   out_8920567495883519593[31] = 0;
   out_8920567495883519593[32] = 0;
   out_8920567495883519593[33] = 0;
   out_8920567495883519593[34] = 0;
   out_8920567495883519593[35] = 0;
   out_8920567495883519593[36] = 0;
   out_8920567495883519593[37] = 0;
   out_8920567495883519593[38] = 0;
   out_8920567495883519593[39] = 0;
   out_8920567495883519593[40] = 1;
   out_8920567495883519593[41] = 0;
   out_8920567495883519593[42] = 0;
   out_8920567495883519593[43] = 0;
   out_8920567495883519593[44] = 0;
   out_8920567495883519593[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8920567495883519593[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8920567495883519593[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8920567495883519593[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8920567495883519593[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8920567495883519593[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8920567495883519593[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8920567495883519593[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8920567495883519593[53] = -9.8000000000000007*dt;
   out_8920567495883519593[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8920567495883519593[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8920567495883519593[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8920567495883519593[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8920567495883519593[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8920567495883519593[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8920567495883519593[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8920567495883519593[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8920567495883519593[62] = 0;
   out_8920567495883519593[63] = 0;
   out_8920567495883519593[64] = 0;
   out_8920567495883519593[65] = 0;
   out_8920567495883519593[66] = 0;
   out_8920567495883519593[67] = 0;
   out_8920567495883519593[68] = 0;
   out_8920567495883519593[69] = 0;
   out_8920567495883519593[70] = 1;
   out_8920567495883519593[71] = 0;
   out_8920567495883519593[72] = 0;
   out_8920567495883519593[73] = 0;
   out_8920567495883519593[74] = 0;
   out_8920567495883519593[75] = 0;
   out_8920567495883519593[76] = 0;
   out_8920567495883519593[77] = 0;
   out_8920567495883519593[78] = 0;
   out_8920567495883519593[79] = 0;
   out_8920567495883519593[80] = 1;
}
void h_25(double *state, double *unused, double *out_1748943336957925663) {
   out_1748943336957925663[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7831722141357852418) {
   out_7831722141357852418[0] = 0;
   out_7831722141357852418[1] = 0;
   out_7831722141357852418[2] = 0;
   out_7831722141357852418[3] = 0;
   out_7831722141357852418[4] = 0;
   out_7831722141357852418[5] = 0;
   out_7831722141357852418[6] = 1;
   out_7831722141357852418[7] = 0;
   out_7831722141357852418[8] = 0;
}
void h_24(double *state, double *unused, double *out_3057523279018916844) {
   out_3057523279018916844[0] = state[4];
   out_3057523279018916844[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4417430629214797958) {
   out_4417430629214797958[0] = 0;
   out_4417430629214797958[1] = 0;
   out_4417430629214797958[2] = 0;
   out_4417430629214797958[3] = 0;
   out_4417430629214797958[4] = 1;
   out_4417430629214797958[5] = 0;
   out_4417430629214797958[6] = 0;
   out_4417430629214797958[7] = 0;
   out_4417430629214797958[8] = 0;
   out_4417430629214797958[9] = 0;
   out_4417430629214797958[10] = 0;
   out_4417430629214797958[11] = 0;
   out_4417430629214797958[12] = 0;
   out_4417430629214797958[13] = 0;
   out_4417430629214797958[14] = 1;
   out_4417430629214797958[15] = 0;
   out_4417430629214797958[16] = 0;
   out_4417430629214797958[17] = 0;
}
void h_30(double *state, double *unused, double *out_5610626813386427315) {
   out_5610626813386427315[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3304025811230244220) {
   out_3304025811230244220[0] = 0;
   out_3304025811230244220[1] = 0;
   out_3304025811230244220[2] = 0;
   out_3304025811230244220[3] = 0;
   out_3304025811230244220[4] = 1;
   out_3304025811230244220[5] = 0;
   out_3304025811230244220[6] = 0;
   out_3304025811230244220[7] = 0;
   out_3304025811230244220[8] = 0;
}
void h_26(double *state, double *unused, double *out_6056296858322780452) {
   out_6056296858322780452[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4090218822483796194) {
   out_4090218822483796194[0] = 0;
   out_4090218822483796194[1] = 0;
   out_4090218822483796194[2] = 0;
   out_4090218822483796194[3] = 0;
   out_4090218822483796194[4] = 0;
   out_4090218822483796194[5] = 0;
   out_4090218822483796194[6] = 0;
   out_4090218822483796194[7] = 1;
   out_4090218822483796194[8] = 0;
}
void h_27(double *state, double *unused, double *out_1063608766311927720) {
   out_1063608766311927720[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1129262499429819309) {
   out_1129262499429819309[0] = 0;
   out_1129262499429819309[1] = 0;
   out_1129262499429819309[2] = 0;
   out_1129262499429819309[3] = 1;
   out_1129262499429819309[4] = 0;
   out_1129262499429819309[5] = 0;
   out_1129262499429819309[6] = 0;
   out_1129262499429819309[7] = 0;
   out_1129262499429819309[8] = 0;
}
void h_29(double *state, double *unused, double *out_7834443992662278656) {
   out_7834443992662278656[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3814257155544636404) {
   out_3814257155544636404[0] = 0;
   out_3814257155544636404[1] = 1;
   out_3814257155544636404[2] = 0;
   out_3814257155544636404[3] = 0;
   out_3814257155544636404[4] = 0;
   out_3814257155544636404[5] = 0;
   out_3814257155544636404[6] = 0;
   out_3814257155544636404[7] = 0;
   out_3814257155544636404[8] = 0;
}
void h_28(double *state, double *unused, double *out_460292881635450203) {
   out_460292881635450203[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5777887427109962655) {
   out_5777887427109962655[0] = 1;
   out_5777887427109962655[1] = 0;
   out_5777887427109962655[2] = 0;
   out_5777887427109962655[3] = 0;
   out_5777887427109962655[4] = 0;
   out_5777887427109962655[5] = 0;
   out_5777887427109962655[6] = 0;
   out_5777887427109962655[7] = 0;
   out_5777887427109962655[8] = 0;
}
void h_31(double *state, double *unused, double *out_1697983222847899076) {
   out_1697983222847899076[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3464010720250444718) {
   out_3464010720250444718[0] = 0;
   out_3464010720250444718[1] = 0;
   out_3464010720250444718[2] = 0;
   out_3464010720250444718[3] = 0;
   out_3464010720250444718[4] = 0;
   out_3464010720250444718[5] = 0;
   out_3464010720250444718[6] = 0;
   out_3464010720250444718[7] = 0;
   out_3464010720250444718[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_7655511453115168940) {
  err_fun(nom_x, delta_x, out_7655511453115168940);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2885483212860589707) {
  inv_err_fun(nom_x, true_x, out_2885483212860589707);
}
void car_H_mod_fun(double *state, double *out_3050833487134891442) {
  H_mod_fun(state, out_3050833487134891442);
}
void car_f_fun(double *state, double dt, double *out_6858776502225367365) {
  f_fun(state,  dt, out_6858776502225367365);
}
void car_F_fun(double *state, double dt, double *out_8920567495883519593) {
  F_fun(state,  dt, out_8920567495883519593);
}
void car_h_25(double *state, double *unused, double *out_1748943336957925663) {
  h_25(state, unused, out_1748943336957925663);
}
void car_H_25(double *state, double *unused, double *out_7831722141357852418) {
  H_25(state, unused, out_7831722141357852418);
}
void car_h_24(double *state, double *unused, double *out_3057523279018916844) {
  h_24(state, unused, out_3057523279018916844);
}
void car_H_24(double *state, double *unused, double *out_4417430629214797958) {
  H_24(state, unused, out_4417430629214797958);
}
void car_h_30(double *state, double *unused, double *out_5610626813386427315) {
  h_30(state, unused, out_5610626813386427315);
}
void car_H_30(double *state, double *unused, double *out_3304025811230244220) {
  H_30(state, unused, out_3304025811230244220);
}
void car_h_26(double *state, double *unused, double *out_6056296858322780452) {
  h_26(state, unused, out_6056296858322780452);
}
void car_H_26(double *state, double *unused, double *out_4090218822483796194) {
  H_26(state, unused, out_4090218822483796194);
}
void car_h_27(double *state, double *unused, double *out_1063608766311927720) {
  h_27(state, unused, out_1063608766311927720);
}
void car_H_27(double *state, double *unused, double *out_1129262499429819309) {
  H_27(state, unused, out_1129262499429819309);
}
void car_h_29(double *state, double *unused, double *out_7834443992662278656) {
  h_29(state, unused, out_7834443992662278656);
}
void car_H_29(double *state, double *unused, double *out_3814257155544636404) {
  H_29(state, unused, out_3814257155544636404);
}
void car_h_28(double *state, double *unused, double *out_460292881635450203) {
  h_28(state, unused, out_460292881635450203);
}
void car_H_28(double *state, double *unused, double *out_5777887427109962655) {
  H_28(state, unused, out_5777887427109962655);
}
void car_h_31(double *state, double *unused, double *out_1697983222847899076) {
  h_31(state, unused, out_1697983222847899076);
}
void car_H_31(double *state, double *unused, double *out_3464010720250444718) {
  H_31(state, unused, out_3464010720250444718);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
