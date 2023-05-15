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
  в Прекрасное Далёко я начинаю путь.*/


#include "zf_common_headfile.h"

#define FLASH_PAGE_NUMBER 1 //FLASH页数
#define EXPECTED_DISTANCE_THRESHOLD 1.0 //GPS到点判定距离（单位：米）

uint8 current_gps_point=0;//当前GPS正在前往的点位

/* @fn ready_start
 * @brief 开车前的最后准备
 * @param void
 * @return void
 */
void ready_start(){
    //将参数从FLASH全部重新读出
    int i,sector,page;
    oled_clear();
    oled_show_string(0,0, "Reading FLASH...");
    for(i=0,sector=63,page=3;i<FLASH_PAGE_NUMBER;i++){
        oled_show_int(0,0,i,2);
        flash_buffer_clear();
        flash_read_page_to_buffer(sector,page);// 将GPS点位数量从 flash 读取到缓冲区
        switch(i){
            case 1:{
                gps_point_number=flash_union_buffer[0].uint8_type;//获取点位数量
            }
        }
        if(--page<0){//翻页
            page=3;
            sector--;
        }
    }
    //确认GPS状态
    oled_clear();
    oled_show_string(0,0, "Checking GPS...");
    while(1){
        if(gps_tau1201_flag){//GPS数据处理完成
            gps_tau1201_flag=0;
            while(gps_show_if());
        }
    }
    //动量轮启动

}

void gps_follow(){
    if(gps_tau1201_flag){//这段用于GPS数据处理
        gps_tau1201_flag=0;
        if(!gps_tau1201.state){
            return;//定位失败
        }
        else{
            float distance;
            distance=get_two_points_distance (gps_tau1201.latitude,gps_tau1201.longitude,gps_point[current_gps_point].latitude,gps_point[current_gps_point].longitude);
            if(distance<=EXPECTED_DISTANCE_THRESHOLD){//到点
                if(gps_point[current_gps_point++].point_type==FINISH){//进入下一点位，如果已达终点
                    MOTOR_Speed(0);
                }
            }
        }
    }
}

void MPU_follow(){
    if((imu.Roll >= 30) || (imu.Roll <= -30) || (imu.Pitch >= 30) || (imu.Pitch <= -30)){//翻车
        MOTOR_Speed(0);
        //pwm_disable(Servo_PWM_TIM);
    }
}
