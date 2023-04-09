#include "zf_common_headfile.h"
/* @fn ex_init
 * @brief 外设初始化，为了main文件美观放在这里。
 * @param void
 * @return void
 * */
void ex_init(void){
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
    
    oled_clear();
    oled_show_chinese(0, 0, 16,(const uint8 *)MPU_offset1,5);
    oled_show_chinese(0, 4, 16,(const uint8 *)MPU_offset2,4);
    oled_show_string(0, 7, "MPU6050 loading...");
    system_delay_ms(1000);
    MPU6050_Init_Offset();//MPU6050去偏移
    
    //键盘初始化
    oled_show_string(0, 0, "Keyboard loading...");
    key_init(500);
    //初始化完成
    oled_clear();
}
