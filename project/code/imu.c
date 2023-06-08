/*次の音にエスコート
  日々の憂いにディストーション
  ひとりの夜　鳴らすコード
  君も同じかい?
  理想像　追いかけた日々
  Fコード　掻き鳴らすんだディストーション
  ボリュームを振り切るよ
  
  这个文件及它的头文件用于进行惯性导航系统的姿态解算。*/

#include "zf_common_headfile.h"
#include "math.h"
#include "Mahony.h"

#define Buf_SIZE  20	//队列长度，越大，平滑性越高

#define OFFSET_CONUT 250 //去偏移计数

IMU_Info imu;

int16_t  IMU963RA_FIFO[9][Buf_SIZE];	//9个FIFO队列；0-2：陀螺仪数据；3-5：加速度计数据 6-8 磁度计数据	

int16_t lastAx,lastAy,lastAz,lastGx,lastGy,lastGz,lastMx,lastMy,lastMz;

static uint8_t Wr_Index = 0;	//当前FIFO的写入下标

static float Pitch_offset;
static float Roll_offset;
static float Yaw_offset;

//将val入队
static void IMU963RA_NewVal(int16_t* buf,int16_t val) {
  	buf[Wr_Index] = val;
}

//计算FIFO中的平均值
static int16_t IMU963RA_GetAvg(int16_t* buf)
{
  	int i;
	int32_t	sum = 0;
	for(i=0;i<Buf_SIZE;i++)
		sum += buf[i];
	sum = sum / Buf_SIZE;
	return (int16_t)sum;
}

//读取经过滤波的陀螺仪、加速度、磁度计数据
void IMU963RA_readGyro_Acc(int16_t *gyro,int16_t *acc,int16_t *mag)
{
	//static short buf[9];	//缓存原始数据：0-2：加速度计数据；3-5：陀螺仪数据 6-8 磁度计数据
	static int16_t gx,gy,gz;
	static int16_t ax,ay,az;
	static int16_t mx,my,mz;
	
	//将原始数据入队
	if(imu963ra_acc_x==imu963ra_acc_y){
	    return;
	}
	IMU963RA_NewVal(&IMU963RA_FIFO[0][0],imu963ra_acc_x);
	IMU963RA_NewVal(&IMU963RA_FIFO[1][0],imu963ra_acc_y);
	IMU963RA_NewVal(&IMU963RA_FIFO[2][0],imu963ra_acc_z);

	IMU963RA_NewVal(&IMU963RA_FIFO[3][0],imu963ra_gyro_x);
	IMU963RA_NewVal(&IMU963RA_FIFO[4][0],imu963ra_gyro_y);
	IMU963RA_NewVal(&IMU963RA_FIFO[5][0],imu963ra_gyro_z);

	IMU963RA_NewVal(&IMU963RA_FIFO[6][0],imu963ra_mag_x);
	IMU963RA_NewVal(&IMU963RA_FIFO[7][0],imu963ra_mag_y);
	IMU963RA_NewVal(&IMU963RA_FIFO[8][0],imu963ra_mag_z);
	
	//更新FIFO入口指针
	Wr_Index = (Wr_Index + 1) % Buf_SIZE;	

	//计算队列平均值
	gx =  IMU963RA_GetAvg(&IMU963RA_FIFO[4][0]);
	gy =  IMU963RA_GetAvg(&IMU963RA_FIFO[5][0]);
	gz =  IMU963RA_GetAvg(&IMU963RA_FIFO[6][0]);
	
	//陀螺仪数据要减去偏移量
	gyro[0] = gx - Roll_offset;	//gyro
	gyro[1] = gy - Pitch_offset;
	gyro[2] = gz - Yaw_offset;
		

	ax = 	IMU963RA_GetAvg(&IMU963RA_FIFO[0][0]);
	ay = 	IMU963RA_GetAvg(&IMU963RA_FIFO[1][0]);
	az = 	IMU963RA_GetAvg(&IMU963RA_FIFO[2][0]);
				
	acc[0] = ax; //acc
	acc[1] = ay;
	acc[2] = az;

	mx = 	IMU963RA_GetAvg(&IMU963RA_FIFO[6][0]);
	my = 	IMU963RA_GetAvg(&IMU963RA_FIFO[7][0]);
	mz = 	IMU963RA_GetAvg(&IMU963RA_FIFO[8][0]);

	mag[0] = mx; //mag
	mag[1] = my;
	mag[2] = mz;
}

void IMU963RA_Init_Offset(void)//IMU963RA初始化去偏移
{
	int i;
	int16_t temp[3],temp2[3],temp3[3];
	int32_t	tempgx=0,tempgy=0,tempgz=0;
	int32_t tempax=0,tempay=0,tempaz=0;
	int32_t tempmx=0,tempmy=0,tempmz=0;
	Pitch_offset = 0;
	Roll_offset = 0;
	Yaw_offset = 0;
	
	//等待ICM准备就绪
	for(i=0;i<100;i++){
  		system_delay_ms(5);
		IMU963RA_readGyro_Acc(temp,temp2,temp3);
	}
	
	//计算imu数据的平均值作为偏移量
 	for(i=0;i<OFFSET_CONUT;i++){
		system_delay_ms(10);
		IMU963RA_readGyro_Acc(temp,temp2,temp3);
		oled_show_int(0,2,i,3);
		if(temp[0]==temp[1]){
			i--;
			oled_show_string(0,3,"WARNING: IMU NO DATA");
		}
		else{
			//oled_show_string(0,3,"                    ");
			tempgx += temp[0];
			tempgy += temp[1];
			tempgz += temp[2];
			
			tempax += temp2[0];
			tempay += temp2[1];
			tempaz += temp2[2];

			tempmx += temp3[0];
			tempmy += temp3[1];
			tempmz += temp3[2];
		}
	}
	
	Pitch_offset = tempgy/OFFSET_CONUT;
	Roll_offset = tempgx/OFFSET_CONUT;
	Yaw_offset = tempgz/OFFSET_CONUT;
	
}

static void Get_IMU_Values(float *values)
{
	int16_t gyro[3],acc[3],mag[3];
	
	IMU963RA_readGyro_Acc(&gyro[0],&acc[0],&mag[0]);
	
	for(int i=0;i<3;i++)
	{
		values[i]=(imu963ra_gyro_transition (gyro[i]));	//这里我们改用逐飞的转换函数
		values[3+i]=(float) acc[i];
		values[6+i]=(float) mag[i];
	}
	
}

//arcsin函数
float safe_asin(float v)
{
	if (isnan(v)) {
		return 0.0f;
	}
	if (v >= 1.0f) {
		return PI/2;
	}
	if (v <= -1.0f) {
		return -PI/2;
	}
	return asin(v);
}
void IMU_Update(void)
{
	static float q[4];
	float Values[9];	
	Get_IMU_Values(Values);	
	
	//将角度改为弧度，用Mahony计算imu
	MahonyAHRSupdate(Values[0] * PI/180, Values[1] * PI/180, Values[2] * PI/180,Values[3], Values[4], Values[5],Values[6], Values[7], Values[8]);		
	
	//保存四元数（Quaternion）。
	q[0] = q0;
	q[1] = q1;
	q[2] = q2;
	q[3] = q3;
	
	imu.ax = Values[3];
	imu.ay = Values[4];
	imu.az = Values[5];

	imu.Pitch_v = Values[0];
	imu.Roll_v = Values[1];
	imu.Yaw_v = Values[2];

	//用四元数计算imu的角度
	imu.Roll = (atan2(2.0f*(q[0]*q[1] + q[2]*q[3]),1 - 2.0f*(q[1]*q[1] + q[2]*q[2])))* 180/PI;	
	imu.Pitch = -safe_asin(2.0f*(q[0]*q[2] - q[1]*q[3]))* 180/PI;
	imu.Yaw = -atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3 * q3 + 1)* 180/PI; // yaw
}
