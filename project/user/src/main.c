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
        oled_show_string(0,7,"continue aft. 3s");
        system_delay_ms(3000);
    }
    pit_ms_init(TIM6_PIT,5);//定时器中断获取MPU6050数据
    //键盘初始化
    oled_show_string(0, 0, "Keyboard loading...");
    key_init(500);
    //初始化完成
    oled_clear();
    menu();//进入人机交互页面

    while(1){//发车主循环
        if(gps_tau1201_flag){//这段用于GPS数据处理
            gps_tau1201_flag=0;
        }
        mpu6050_acc_transition(mpu6050_acc_x);
    }
}



