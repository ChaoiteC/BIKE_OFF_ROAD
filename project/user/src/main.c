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

    oled_clear();

    while(1)
    {
        if(gps_tau1201_flag)
        {
            gps_tau1201_flag = 0;
            if(!gps_data_parse())          //收到GPS数据
            {
                gps_show_oled();
                //system_delay_ms(1000);
            }
        }
    }
}
