/*惨めな夜もバカ笑いも
  あのね、その後が言えた日の笑顔も
  (あいむ あらいぶ なう いぇ
  すぷりんぐたいむ おぶ らいふ)
  鳴り止まなくてなにが悪い
  青春でなにが悪い*/

#include "zf_common_headfile.h"

void bike_init(void){
    //OLED初始化
    oled_set_dir(OLED_CROSSWISE);
    oled_set_font(OLED_6X8_FONT);
    oled_init();

    //键盘初始化
    oled_show_string(0, 0, "Keyboard loading...");
    key_init(500);


    //FLASH初始化，读出PID参数
    oled_clear();
    oled_show_string(0, 0, "FLASH loading...");
    flash_read_page_to_buffer(63,3);
    MOTOR1_SUM.kp=flash_union_buffer[0].float_type;
    MOTOR1_SUM.ki=flash_union_buffer[1].float_type;
    MOTOR1_SUM.kd=flash_union_buffer[2].float_type;
    MOTOR1_SUM.maxIntegral=flash_union_buffer[3].float_type;
    MOTOR1_SUM.maxOutput=flash_union_buffer[4].float_type;
    flash_read_page_to_buffer(63,2);
    MOTOR2_SUM.kp=flash_union_buffer[0].float_type;
    MOTOR2_SUM.ki=flash_union_buffer[1].float_type;
    MOTOR2_SUM.kd=flash_union_buffer[2].float_type;
    MOTOR2_SUM.maxIntegral=flash_union_buffer[3].float_type;
    MOTOR2_SUM.maxOutput=flash_union_buffer[4].float_type;


    //GPS初始化
    oled_clear();
    oled_show_string(0, 0, "GPS loading...");
    gps_init();
    
    //MPU6050初始化
    oled_show_string(0, 0, "MPU6050 loading...");
    if(mpu6050_init()){//自检失败
        system_delay_ms(3000);
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
