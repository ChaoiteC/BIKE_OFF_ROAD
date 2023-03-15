#ifndef _IMU_H_
#define _IMU_H_


typedef struct
{
  float ax;
  float ay;
  float az;

  float gx;
  float gy;
  float gz;

  float pit;
  float rol;
  float yaw;
}_Attitude;


typedef struct
{
  float DCM[3][3];        //��������ϵ->��������ϵ
  float DCM_T[3][3];      //��������ϵ->��������ϵ
}_Matrix;

extern _Matrix Mat;
extern _Attitude att;

void mahony_update(float gx, float gy, float gz, float ax, float ay, float az) ;
void rotation_matrix(void);
void rotation_matrix_T(void);
void Matrix_ready(void);




#endif
