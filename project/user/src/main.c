/*********************************************************************************************************************
* ��Ŀ�� ԽҰ��������
* ������
* ѧУ��
* ���ߣ� ��̼��
* ���ڣ� 2023.3.12
********************************************************************************************************************/
#include "zf_common_headfile.h"

int main(void){
    clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
    
    //OLED��ʼ��
    oled_set_dir(OLED_CROSSWISE);
    oled_set_font(OLED_6X8_FONT);
    oled_init();
    
    //GPS��ʼ��
    oled_show_string(0, 0, "GPS loading...");
    gps_init();

    //MPU6050��ʼ��
    oled_show_string(0, 0, "MPU6050 loading...");
    if(mpu6050_init()){//�Լ�ʧ��
        oled_show_string(0,7,"MPU6050 init FAIL.");
        while(1);
        //system_delay_ms(3000);
    }
    pit_ms_init(TIM6_PIT,5);//��ʱ���жϻ�ȡMPU6050����

    oled_clear();//��ʼ�����

    while(1){//��ѭ��
        oled_show_mpu6050();
        system_delay_ms(1000);

        if(gps_tau1201_flag){//GPS���ݴ������
            gps_tau1201_flag=0;
            if (!gps_data_parse()) {
                oled_show_gps();
                system_delay_ms(1000);
            }
        }
    }
}


