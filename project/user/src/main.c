/*********************************************************************************************************************
* ��Ŀ�� ԽҰ��������
* ������
* ѧУ��
* ���ߣ� ��̼��
* ���ڣ� 2023.3.12
********************************************************************************************************************/
#include "zf_common_headfile.h"

int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
    
    //OLED��ʼ��
    oled_set_dir(OLED_CROSSWISE);
    oled_set_font(OLED_6X8_FONT);
    oled_init();
    
    //GPS��ʼ��
    oled_show_string(0, 0, "GPS loading...");
    //oled_show_chinese(24, 0, 16, (const uint8 *)chinese_loading, 3);
    gps_init();

    //MPU6050��ʼ��
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
            if(!gps_data_parse())          //�յ�GPS����
            {
                gps_show_oled();
                system_delay_ms(1000);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     PIT ���жϴ����� ����������� PIT ��Ӧ�Ķ�ʱ���жϵ��� ��� isr.c
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     pit_hanlder();
//-------------------------------------------------------------------------------------------------------------------
void pit_hanlder (void)
{
    mpu6050_get_acc();                                                         // ��ȡ MPU6050 �ļ��ٶȲ�����ֵ
    mpu6050_get_gyro();                                                        // ��ȡ MPU6050 �Ľ��ٶȲ�����ֵ
}
