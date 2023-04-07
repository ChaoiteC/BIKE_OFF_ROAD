#include "zf_common_headfile.h"


/* @fn oled_show_gps
 * @brief 将GPS信息显示到OLED屏幕上
 * @param void
 * @return void
 */
void oled_show_gps(void){
    oled_clear();
    oled_show_string(0,0, "GPS");
    if(!gps_tau1201.state){
        oled_show_string(0,2, "FAIL LOCATE");                //定位失败
    }
    else{
        oled_show_string(0, 7, "TIM>");                      //时间
        oled_show_int(32,7,gps_tau1201.time.hour,2);
        oled_show_int(50,7,gps_tau1201.time.minute,2);
        oled_show_int(68,7,gps_tau1201.time.second,2);
        oled_show_string(0, 2, "N ->");
        oled_show_float(32,2,gps_tau1201.latitude,4,6);      //纬度
        oled_show_string(0, 3, "E ->");
        oled_show_float(32,3,gps_tau1201.longitude,4,6);     //经度
        oled_show_string(0, 4, "m/s>");
        oled_show_float(32,4,gps_tau1201.speed,4,6);         //速度
        oled_show_string(0, 5, "360>");
        oled_show_float(32,5,gps_tau1201.direction,4,6);     //方向
        oled_show_string(0, 6, "STL>");
        oled_show_int(32,6,gps_tau1201.satellite_used,2);    //卫星连接数量
    }
}

/* @fn oled_show_mpu6050
 * @brief 将MPU6050信息显示到OLED屏幕上
 * @param void
 * @return void
 */
void oled_show_mpu6050(void){
    oled_clear();
    oled_show_string(0,0,"MPU6050");
    oled_show_string(0,1,"ACC");
    oled_show_int(0,2,mpu6050_acc_x,5);
    oled_show_int(0,3,mpu6050_acc_y,5);
    oled_show_int(0,4,mpu6050_acc_z,5);
    oled_show_string(64,1,"GYRO");
    oled_show_int(64,2,mpu6050_gyro_x,5);
    oled_show_int(64,3,mpu6050_gyro_y,5);
    oled_show_int(64,4,mpu6050_gyro_z,5);
}
