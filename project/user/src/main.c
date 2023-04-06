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

    oled_clear();

    while(1)
    {
        if(gps_tau1201_flag)
        {
            gps_tau1201_flag = 0;
            if(!gps_data_parse())          //�յ�GPS����
            {
                gps_show_oled();
                //system_delay_ms(1000);
            }
        }
    }
}
