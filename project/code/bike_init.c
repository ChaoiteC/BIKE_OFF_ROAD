/*惨めな夜もバカ笑いも
  あのね、その後が言えた日の笑顔も
  (あいむ あらいぶ なう いぇ
  すぷりんぐたいむ おぶ らいふ)
  鳴り止まなくてなにが悪い
  青春でなにが悪い
  
  这个文件及它的的头文件用于完成车辆各个软硬件的初始化。*/

#include "zf_common_headfile.h"

void bike_init(void){
    //OLED初始化
    oled_set_dir(OLED_CROSSWISE);
    oled_set_font(OLED_6X8_FONT);
    oled_init();

    //键盘初始化
    oled_show_string(0, 0, "Keyboard loading...");
    key_init(400);


    //PID初始化
    oled_clear();
    oled_show_string(0, 0, "PID loading...");
    flash_buffer_clear();
    if(!flash_check(63,3)){//无数据填入缺省值
        flash_union_buffer[0].float_type=1.0;//MT1 PID
        flash_union_buffer[1].float_type=0.0;
        flash_union_buffer[2].float_type=5.0;
        flash_union_buffer[3].float_type=20.0;
        flash_union_buffer[4].float_type=20.0;
        flash_union_buffer[5].float_type=1.0;//MT2 PID
        flash_union_buffer[6].float_type=0.0;
        flash_union_buffer[7].float_type=5.0;
        flash_union_buffer[8].float_type=20.0;
        flash_union_buffer[9].float_type=20.0;
        flash_union_buffer[10].float_type=1.0;//MT3 PID
        flash_union_buffer[11].float_type=0.0;
        flash_union_buffer[12].float_type=5.0;
        flash_union_buffer[13].float_type=20.0;
        flash_union_buffer[14].float_type=20.0;
        flash_write_page_from_buffer(63,3);
    }
    flash_data_update();
    //GPS初始化
    oled_clear();
    oled_show_string(0, 0, "GPS loading...");
    gps_init();
    pit_ms_init(TIM7_PIT,100);//定时器中断获取GPS数据

    //IMU963RA初始化
    oled_show_string(0, 0, "IMU963RA loading...");
    if(imu963ra_init()){//自检失败
        system_delay_ms(3000);
    }
    else{
        pit_ms_init(TIM6_PIT,5);//定时器中断获取IMU963RA数据
    }
    
    //舵机初始化
    oled_clear();
    oled_show_string(0, 0, "Servo loading...");
    Servo_Init(servo_motor_duty);
    

    //编码器初始化
    oled_clear();
    oled_show_string(0, 0, "Encoder loading...");
    Encoder_text_init();//编码器初始化，打开中断

    //电机初始化
    oled_clear();
    oled_show_string(0, 0, "MOTOR loading...");
    MOTOR_Init();

    //蓝牙初始化
    oled_clear();
    oled_show_string(0, 0, "Bluetooth checking...");
    bluetooth_ch9141_init();
    bluetooth_ch9141_send_string("Bluetooth OK.\r\n");


    //电机调试
    //初始化完成
    oled_clear();
}
