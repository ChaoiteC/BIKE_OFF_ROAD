/*惨めな夜もバカ笑いも
  あのね、その後が言えた日の笑顔も
  (あいむ あらいぶ なう いぇ
  すぷりんぐたいむ おぶ らいふ)
  鳴り止まなくてなにが悪い
  青春でなにが悪い
  
  这个文件及它的的头文件用于完成车辆各个软硬件的初始化。*/

#include "zf_common_headfile.h"

//单车各部分初始化
void bike_init(void){
    //OLED初始化
    oled_set_dir(OLED_CROSSWISE);
    oled_set_font(OLED_6X8_FONT);
    oled_init();

    //键盘初始化
    oled_show_string(0, 0, "Keyboard loading...");
    key_init(400);

    //IMU963RA初始化
    oled_show_string(0, 0, "IMU963RA loading...");
    if(imu963ra_init()){//自检失败
        system_delay_ms(5000);
    }
    else{
        pit_ms_init(TIM6_PIT,5);//定时器中断获取IMU963RA数据
        IMU_offset();
    }
    
    //PID初始化
    oled_clear();
    oled_show_string(0, 0, "PID loading...");
    flash_buffer_clear();
    if(!flash_check(63,3)){//无数据填入缺省值
        flash_union_buffer[0].float_type=-40.0;//b_acc PID
        flash_union_buffer[1].float_type=-0.005;
        flash_union_buffer[2].float_type=-5.0;
        flash_union_buffer[3].float_type=10000.0;
        flash_union_buffer[4].float_type=10000.0;
        flash_union_buffer[5].float_type=11.1;//b_ang PID
        flash_union_buffer[6].float_type=0.0;
        flash_union_buffer[7].float_type=0.0;
        flash_union_buffer[8].float_type=10000.0;
        flash_union_buffer[9].float_type=10000.0;
        flash_union_buffer[10].float_type=0.0;//b_vel PID
        flash_union_buffer[11].float_type=0.0;
        flash_union_buffer[12].float_type=0.0;
        flash_union_buffer[13].float_type=10000.0;
        flash_union_buffer[14].float_type=10000.0;
        flash_write_page_from_buffer(63,3);
    }
    flash_data_update();

    //GPS初始化
    oled_clear();
    oled_show_string(0, 0, "GPS loading...");
    gps_init();
    pit_ms_init(TIM7_PIT,100);//定时器中断获取GPS数据

    //舵机初始化
    oled_clear();
    oled_show_string(0, 0, "Servo loading...");
    Servo_Init(servo_motor_duty);

    //平衡初始化
    oled_clear();
    oled_show_string(0, 0, "Balance loading...");
    balance_init();

    //蓝牙初始化
    oled_clear();
    oled_show_string(0, 0, "Bluetooth checking...");
    bluetooth_ch9141_init();
    bluetooth_ch9141_send_string("Bluetooth OK.\r\n");

    //初始化完成
    oled_clear();
}

//FLASH在这里赋值各个变量
void flash_data_update(){
    flash_read_page_to_buffer(63,3);
    PID_set(&balance_acc,flash_union_buffer[0].float_type,flash_union_buffer[1].float_type,flash_union_buffer[2].float_type,flash_union_buffer[3].float_type,flash_union_buffer[4].float_type);
    PID_expect(&balance_acc,0);
    PID_set(&balance_ang,flash_union_buffer[6].float_type,flash_union_buffer[7].float_type,flash_union_buffer[8].float_type,flash_union_buffer[9].float_type,flash_union_buffer[10].float_type);
    PID_expect(&balance_ang,0);
    PID_set(&balance_vel,flash_union_buffer[11].float_type,flash_union_buffer[12].float_type,flash_union_buffer[13].float_type,flash_union_buffer[14].float_type,flash_union_buffer[15].float_type);
    PID_expect(&balance_vel,0);
}
