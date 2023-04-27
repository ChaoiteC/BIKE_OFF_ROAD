#include "zf_common_headfile.h"
/*惨めな夜もバカ笑いも
  あのね、その後が言えた日の笑顔も
  (あいむ あらいぶ なう いぇ
  すぷりんぐたいむ おぶ らいふ)
  鳴り止まなくてなにが悪い
  青春でなにが悪い*/

//写完了一段时间才发现，这个文件没有包含任何头文件？

void ex_init(void){
    //OLED初始化
    oled_set_dir(OLED_CROSSWISE);
    oled_set_font(OLED_6X8_FONT);
    oled_init();

    //键盘初始化
    oled_show_string(0, 0, "Keyboard loading...");
    key_init(500);

    //FLASH初始化
    oled_clear();
    oled_show_string(0, 0, "FLASH checking...");
    if(!flash_check (63,3)){//FLASH无数据则格式化
        oled_clear();
        oled_show_string(0, 0, "FLASH formatting...");
        
    }
    //GPS初始化
    oled_clear();
    oled_show_string(0, 0, "GPS loading...");
    gps_init();
    //IMU963RA初始化
    oled_show_string(0, 0, "IMU963RA loading...");
    if(imu963ra_init()){//自检失败
        system_delay_ms(1000);
    }
    pit_ms_init(TIM6_PIT,5);//定时器中断获取IMU963RA数据
    
    oled_clear();
    oled_show_chinese(0, 0, 16,(const uint8 *)IMU_offset1,5);
    oled_show_chinese(0, 4, 16,(const uint8 *)IMU_offset2,4);
    oled_show_string(0, 7, "IMU963RA loading...");
    system_delay_ms(1000);
    IMU963RA_Init_Offset();//IMU963RA去偏移
    
    //初始化完成
    oled_clear();
}
