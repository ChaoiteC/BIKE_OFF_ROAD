/*����GPS�����ɺ��� by ̼��*/

#include "zf_common_headfile.h"

/* @fn gps_average_pointing
 * @brief ��ȡʮ��GPS��γ�Ȳ�ȡ��ƽ��ֵ
 * @param *average_latitude ƽ��γ��
 * @param *average_longitude ƽ������
 * @return void
 */
void gps_average_pointing(int8* average_latitude,int8* average_longitude){
    
}

/* @fn gps_show_oled
 * @brief ��GPS��Ϣ��ʾ����Ļ��
 * @param void
 * @return void
 */
void gps_show_oled(void){
    oled_clear();
    oled_show_string(0,0, "GPS");
    if(!gps_tau1201.state){
        oled_show_string(0,2, "FAIL LOCATE");                //��λʧ��
        //oled_show_chinese(24, 0, 16, (const uint8 *)chinese_nodata, 4);
    }
    else{
        oled_show_string(0, 7, "TIM>");                      //ʱ��
        oled_show_int(32,7,gps_tau1201.time.hour,2);
        oled_show_int(50,7,gps_tau1201.time.minute,2);
        oled_show_int(68,7,gps_tau1201.time.second,2);
        oled_show_string(0, 2, "N ->");
        oled_show_float(32,2,gps_tau1201.latitude,4,6);      //γ��
        oled_show_string(0, 3, "E ->");
        oled_show_float(32,3,gps_tau1201.longitude,4,6);     //����
        oled_show_string(0, 4, "m/s>");
        oled_show_float(32,4,gps_tau1201.speed,4,6);         //�ٶ�
        oled_show_string(0, 5, "360>");
        oled_show_float(32,5,gps_tau1201.direction,4,6);     //����
        oled_show_string(0, 6, "STL>");
        oled_show_int(32,6,gps_tau1201.satellite_used,2);    //������������
    }
}
