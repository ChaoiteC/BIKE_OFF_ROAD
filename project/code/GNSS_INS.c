#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//这是通过人工智能编写的GNSS与IMU融合导航代码，不过显然不能用。
//很遗憾，但我只能说我不是什么都能学会。

/*#define NUM_STATES 6

double a = 6378137.0;               // m Earth's ellipsoid radius at equator
double b = 6356752.3142;            // m Earth's ellipsoid radius at poles
double ecc = 0.0818191908426;       // - Earth's ellipsoid eccentricity
double w_i_e = 7.2921150e-5;        // rad/s Earth's rotational speed
double mu = 3.986004418e14;         // m^3/s^2 Geocentric gravitational constant
double f = 1/298.257223563;         // - Earth's ellipsoid flattening
double omega_ib_b[3][3] = {0};      // Initialize to all zeros
double g0 = 0;
double R2D = 180/3.14159265358979323846;
double D2R = 3.14159265358979323846/180;
double x_0, y_0, phi_0, phi_D_0, v_0, a_0;
double x_i = 0, y_i = 0, phi_i = 0, phi_D_i = 0, v_i = 0, a_i = 0;
double Delta_t = 0.001;
double Variance_phi_D = 0.0035;
double Variance_a = pow(0.01, 2);
double Variance_x = pow(10, -4);
double Variance_y = pow(10, -4);
double Variance_phi = pow(10, -5);
double P_kM1[NUM_STATES][NUM_STATES] = {
    { Variance_x, 0, 0, 0, 0, 0 },
    { 0, Variance_y, 0, 0, 0, 0 },
    { 0, 0, Variance_phi, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 }            
};
int Res, cnt = 1, cnt_b = 1, Interval = 1, P_Interval = 10;

int main() {
    // Load variables from file
    // Assumes imu.rpy_ned(1,3), gps, and UTM have already been loaded
    // Not included in C code since it depends on file I/O operations
    // Manually initialize other variables
    x_0 = UTM[0][0];
    y_0 = UTM[0][1];
    phi_0 = imu.rpy_ned[0][2];
    phi_D_0 = 0;
    v_0 = 0;
    a_0 = 0;
    
    float x_kM[6] = {x_0 + v_0Delta_tcos(phi_0),
y_0 + v_0Delta_tsin(phi_0),
phi_0 + phi_D_0Delta_t,
phi_D_0,
v_0+a_0Delta_t,
a_0};

// Ans1[cnt][0]=x_kM[0];
// Ans1[cnt][1]=x_kM[1];

float Tans_Matrix[6][6] = {{1,0,-v_0Delta_tsin(phi_0),0,Delta_tcos(phi_0),0},
{0,1, v_0Delta_tcos(phi_0),0,Delta_tsin(phi_0),0},
{0,0,1,Delta_t,0,0},
{0,0,0,1,0,0},
{0,0,0,0,1,Delta_t},
{0,0,0,0,0,1}};

float Q[2][2] = {{Variance_phi_D,0},
{0,Varince_a}};

float GQG_T[6][6] = {{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,Variance_phi_DDelta_tDelta_t,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,Varince_aDelta_tDelta_t}};

float P_k_M[6][6];

// matrix multiplication: Tans_Matrix * P_kM1 * Tans_Matrix'
for(int i=0; i<6; i++) {
for(int j=0; j<6; j++) {
P_k_M[i][j] = 0;
for(int k=0; k<6; k++) {
P_k_M[i][j] += Tans_Matrix[i][k] * P_kM1[k][j];
}
P_k_M[i][j] *= Tans_Matrix[j][i]; // note the transpose
}
}

// add GQG_T to P_k_M
for(int i=0; i<6; i++) {
for(int j=0; j<6; j++) {
P_k_M[i][j] += GQG_T[i][j];
}
}
    //*****************Correction*****************************
float Varince_x_gps = 0.01;
float Varince_y_gps = 0.01;
float Variance_Acc = 0.001;
float Variance_gyro = 5e-5;

float z_k[4] = {UTM[cnt][0], UTM[cnt][1], -imu.acc_ib_b[cnt_b][0], imu.omg_ib_b[cnt_b][2]};
float R_gps[4][4] = {{Varince_x_gps, 0, 0, 0},
                    {0, Varince_y_gps, 0, 0},
                    {0, 0, Variance_Acc, 0},
                    {0, 0, 0, Variance_gyro}};

float H[4][6] = {{1, 0, 0, 0, 0, 0},
                 {0, 1, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 1},
                 {0, 0, 0, 1, 0, 0}};

float h[4];
matmul(H, x_kM, h, 4, 6, 1);

float K_k[6][4];
matmul(P_k_M, H, K_k, 6, 6, 4);
float temp[4][6];
matmul(H, P_k_M, temp, 4, 6, 6);
float temp2[4][4];
matmul(temp, transpose(H), temp2, 4, 6, 4);
add(temp2, R_gps, temp2, 4, 4);
float inv_temp[4][4];
inv(temp2, inv_temp, 4);
matmul(K_k, inv_temp, K_k, 6, 4, 4);

float z_k_sub_h[4];
sub(z_k, h, z_k_sub_h, 4);

float K_k_times_z_k_sub_h[6];
matmul(K_k, z_k_sub_h, K_k_times_z_k_sub_h, 6, 4, 1);
add(x_kM, K_k_times_z_k_sub_h, x_k, 6, 1);

float KH[6][6];
matmul(K_k, H, KH, 6, 4, 6);
float I_minus_KH[6][6];
sub(eye6, KH, I_minus_KH, 6, 6);
matmul(I_minus_KH, P_k_M, P_k, 6, 6, 6);

Ans[cnt][0] = x_k[0];
Ans[cnt][1] = x_k[1];

matcpy(P_kM1, P_k_M, 6, 6);

x_0 = x_k[0];
y_0 = x_k[1];
phi_0 = x_k[2];
phi_D_0 = x_k[3];
v_0 = x_k[4];
a_0 = x_k[5];

cnt += Interval;
cnt_b += P_Interval;

//Time fraction 
Delta_t = imu.imu_time[cnt_b] - imu.imu_time[cnt_b-P_Interval];
    return 0;
}*/