/*Слышу голос из Прекрасного Далёка,
  голос утренний в серебряной росе.
  Слышу голос и манящая дорога кружит голову как в детстве карусель.
  он зовет меня в чудесные края.
  Слышу голос, голос спрашивает строго: "А сегодня, что для завтра сделал я?"
  Я клянусь,что стану чище и добрее,
  И в беде не брошу друга никогда.
  Слышу голос,и спешу на зов скорее,
  По дороге,на которой нет следа.
  От чистого истока в Прекрасное Далёко,
  в Прекрасное Далёко я начинаю путь.
  
  这个文件及它的头文件用于行车过程中的导航，即接收传感器的数据、决定车整体的动作与应该去往哪里。*/


#include "zf_common_headfile.h"

#define FLASH_PAGE_NUMBER 1 //FLASH页数

float gps_distance;//到下一点的距离
float gps_azimuth;//到下一点位的测量方位角

uint8 stop_flag=0;//停车信号 9=等待发车 1=终点 2=翻车 3=遥控

uint8 current_gps_point=0;//当前GPS正在前往的点位

/* @fn start_check
 * @brief 准备开车
 * @param void
 * @return void
 */
void start_check(){
    //将参数从FLASH全部重新读出
    oled_clear();
    oled_show_string(0,0, "Reading FLASH...");
    gps_check_flash();
    //确认GPS状态
    oled_clear();
    oled_show_string(0,0,"Loading GPS...");
    while(1){
        if(!gps_show_if()){
            break;
        }
    }
    //动量轮启动

}


void overturn_check(){
    if((IMU_Data.Rol >= 30) || (IMU_Data.Rol <= -30) || (IMU_Data.Pit >= 30) || (IMU_Data.Pit <= -30)){//翻车
        stop_flag=2;
    }
}

void bluetooth_check(){
    uint8 data_buffer[32];
    if(bluetooth_ch9141_read_buff(data_buffer,32)){
        if(!strcmp((const char *)data_buffer,"stop")){
            stop_flag=3;
        }
    }
}

void stop_do(){//停车处理
    if(stop_flag){
        oled_clear();
        oled_show_chinese(0, 0, 16,(const uint8 *)STOP,2);
        switch(stop_flag){
            case 1:oled_show_string(0,0, "!FINISH!");break;
            case 2:oled_show_string(0,0, "OVERTURN");break;
            case 3:oled_show_string(0,0, "BLET RC.");break;
            default:return;
        }
        while(1);//已经不用再努力了。
    }
}
