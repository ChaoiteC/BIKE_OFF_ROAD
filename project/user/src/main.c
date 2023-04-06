/*********************************************************************************************************************
* 项目： 越野单车比赛
* 队名：
* 学校：
* 作者： 润、碳白
* 日期： 2023.3.12
********************************************************************************************************************/
#include "zf_common_headfile.h"

int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
    debug_init();                                                               // 初始化默认 Debug UART
    
    //OLED初始化
    oled_set_dir(OLED_CROSSWISE);
    oled_set_font(OLED_6X8_FONT);
    oled_init();
    
    //GPS初始化
    oled_show_string(0, 0, "GPS loading...");
    //oled_show_chinese(24, 0, 16, (const uint8 *)chinese_loading, 3);
    gps_init();

    //MPU6050初始化
    oled_show_string(0, 0, "MPU6050 loading...");
    if(mpu6050_init()){
        oled_show_string(0,0,"MPU6050 init FAIL.");
        system_delay_ms(2000);
    }

    oled_clear();

    while(1)
    {
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
        system_delay_ms(1000);

        if(gps_tau1201_flag)
        {
            gps_tau1201_flag = 0;
            if(!gps_data_parse())          //收到GPS数据
            {
                gps_show_oled();
                system_delay_ms(1000);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 的中断处理函数 这个函数将在 PIT 对应的定时器中断调用 详见 isr.c
// 参数说明     void
// 返回参数     void
// 使用示例     pit_hanlder();
//-------------------------------------------------------------------------------------------------------------------
void pit_hanlder (void)
{
    mpu6050_get_acc();                                                         // 获取 MPU6050 的加速度测量数值
    mpu6050_get_gyro();                                                        // 获取 MPU6050 的角速度测量数值
}
