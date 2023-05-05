/*惨めな夜もバカ笑いも
  あのね、その後が言えた日の笑顔も
  (あいむ あらいぶ なう いぇ
  すぷりんぐたいむ おぶ らいふ)
  鳴り止まなくてなにが悪い
  青春でなにが悪い*/

#include "zf_common_headfile.h"

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
    if(!flash_check(63,3)){//FLASH无数据则格式化
        oled_clear();
        oled_show_string(0, 0, "FLASH formatting...");
        flash_init();
    }

    //GPS初始化
    oled_clear();
    oled_show_string(0, 0, "GPS loading...");
    gps_init();
    
    //MPU6050初始化
    oled_show_string(0, 0, "MPU6050 loading...");
    if(mpu6050_init()){//自检失败
        system_delay_ms(1000);
    }
    else{
        pit_ms_init(TIM6_PIT,5);//定时器中断获取MPU6050数据
        oled_clear();
        oled_show_chinese(0, 0, 16,(const uint8 *)MPU_offset1,5);
        oled_show_chinese(0, 4, 16,(const uint8 *)MPU_offset2,4);
        oled_show_string(0, 7, "MPU6050 loading...");
        system_delay_ms(1000);
        MPU6050_Init_Offset();//MPU6050去偏移
    }

    //舵机初始化
    oled_clear();
    oled_show_string(0, 0, "Servo loading...");
    Servo_Init(servo_motor_duty);
    

    //编码器初始化
    oled_clear();
    oled_show_string(0, 0, "Encoder loading...");
    Encoder_text_init();                                                        //编码器初始化，打开中段

    //电机初始化
    oled_clear();
    oled_show_string(0, 0, "MOTOR loading...");
    MOTOR_Init();

    //蓝牙初始化
    oled_clear();
    oled_show_string(0, 0, "Bluetooth checking...");
    bluetooth_ch9141_init();
    bluetooth_ch9141_send_string("Bluetooth OK.\r\n");

    //初始化完成
    oled_clear();
    //电机调试
    MOTOR_PID();

}

void flash_init(void){
    int i;
    flash_erase_sector(63,3);
    flash_buffer_clear();
    for(i=0;i<6;i++){

        flash_union_buffer[i].float_type=(float)i;
    }
    flash_write_page_from_buffer(63,3);
}
