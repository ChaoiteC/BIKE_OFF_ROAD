#include "zf_common_headfile.h"

FCOFI FCOF;


float angle;                //数据融合后的角度    
float acc_ratio = 4.08;      //加速度计比例    
float gyro_ratio = 1.6;    //陀螺仪比例    
float dt = 0.005;           //采样周期    

//----------------------------------------------------------------    
//  @brief      一阶互补滤波    
//  @param      angle_m     加速度计数据    
//  @param      gyro_m      陀螺仪数据    
//  @return     float       数据融合后的角度    
//----------------------------------------------------------------    
float angle_calc(float angle_m, float gyro_m)    
{    
    float temp_angle;               
    float gyro_now;    
    float error_angle;
    static float last_angle;    
    static uint8 first_angle;    
    if(!first_angle){//判断是否为第一次运行本函数    
        //如果是第一次运行，则将上次角度值设置为与加速度值一致    
        first_angle = 1;    
        last_angle = angle_m;    
    }
    gyro_now = gyro_m * gyro_ratio;
    //根据测量到的加速度值转换为角度之后与上次的角度值求偏差    
    error_angle = (angle_m - last_angle)*acc_ratio;
    //根据偏差与陀螺仪测量得到的角度值计算当前角度值
    temp_angle = last_angle + (error_angle + gyro_now)*dt;
    //保存当前角度值    
    last_angle = temp_angle;
    return temp_angle;    
}    
void FCOF_update(void){
    FCOF.Pitch=angle_calc(mpu6050_acc_y, mpu6050_gyro_y);
    FCOF.Roll=angle_calc(mpu6050_acc_x, mpu6050_gyro_x);
    FCOF.Yaw=angle_calc(mpu6050_acc_z, mpu6050_gyro_z);
}
    

/*int main(void)    

{    

    uint8 virsco_data[10];                

        

    DisableGlobalIRQ();    

    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口    

      

    systick_delay_ms(300);  

      

    icm20602_init_spi();        //六轴陀螺仪初始化    

    seekfree_wireless_init();   //无线转串口初始化    

    

    systick_delay_ms(50);       //初始化完成后延时一定的时间  

    //总中断最后开启    

    EnableGlobalIRQ(0);    

    while (1)    

    {    

        get_icm20602_accdata_spi();     //获取加速度数据    

        get_icm20602_gyro_spi();        //获取陀螺仪数据    

            

        angle = angle_calc(icm_acc_z, icm_gyro_y); //一阶互补滤波计算角度值  

            

        data_conversion(icm_acc_z, icm_gyro_y, (int)angle, 0, virsco_data); //发送数据到上位机    

        seekfree_wireless_send_buff(virsco_data, 10);    

            

        systick_delay_ms(5);//延时5ms    

    }    

} */
