/*********************************************************************************************************************
* 项目： 越野单车比赛
* 队名：
* 学校：
* 作者： 润、碳白
* 日期： 2023.3.12
********************************************************************************************************************/
#include "zf_common_headfile.h"

int main(void){
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
    debug_init();                                                               // 初始化默认 Debug UART
    
    //OLED初始化
    oled_set_dir(OLED_CROSSWISE);
    oled_set_font(OLED_6X8_FONT);
    oled_init();
    
    //GPS初始化
    oled_show_string(0, 0, "GPS loading...");
    gps_init();

    //MPU6050初始化
    oled_show_string(0, 0, "MPU6050 loading...");
    if(mpu6050_init()){//自检失败
        oled_show_string(0,7,"MPU6050 init FAIL.");
        while(1);
        //system_delay_ms(3000);
    }
    pit_ms_init(TIM6_PIT,5);//定时器中断获取MPU6050数据

    oled_clear();//初始化完成

    while(1){//主循环
        oled_show_mpu6050();
        system_delay_ms(1000);

        if(gps_tau1201_flag){//GPS数据处理完成
            gps_tau1201_flag=0;
            if (!gps_data_parse()) {
                oled_show_gps();
                system_delay_ms(1000);
            }
        }
    }
}


