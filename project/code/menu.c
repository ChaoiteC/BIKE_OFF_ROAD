/* 人机交互页面。
 * 
 * 林碳白
 * 202年4月7日
 */
#include "zf_common_headfile.h"

#define KEY_UP KEY_1
#define KEY_DOWN KEY_2
#define KEY_RT KEY_4
#define KEY_CF KEY_3



uint8 now_page=0;//当前页面
uint8 gogogo=0;//1=正式发车

uint8 point=0;

enum PAGE
{
    MASTER,
      START,

      TET,
        GPS,
        MPU,
        IMU,
        SERVO,
      CP,

} NOW_PAGE;


/*其实为了节约内存，你可以选择在进入未定义页面时
  直接返回主页。就算要写一个错误页面，也不用写这
  么一大串没用的玩意。你写给谁看呢？而且事实上，
  当你完成程序的时候，根本不会再出现这种问题。
  所以，我设计这个页面的意义到底是什么？为什么
  我要在凌晨1点钟思考这个？难道真的没有别的事情
  需要做了吗？你的人生就像是这个页面一样失败而
  充满了混乱。*/
void page_error(void){
    oled_show_string(0,0,"ERROR:"          );
    oled_show_string(0,1,"UNDEFINED_PAGE"  );
    oled_show_string(0,2,"ERR_PG:"         );
    oled_show_uint( 36 , 2 , now_page , 10 );
    oled_show_string(0,3,"You're trying go");
    oled_show_string(0,4,"to  an UNDEFINED");
    oled_show_string(0,5,"page. Dont worr-");
    oled_show_string(0,6,"-y,we'll back to");
    oled_show_string(0,7,"the MASTER page.");
    system_delay_ms(3000);
    now_page=MASTER;
}

//启动页面
void first_page(void){
    oled_clear();
    oled_show_chinese(0, 0, 16,(const uint8 *)IDP,6);
    oled_show_string(0,4,"BIKE_OFF_ROAD"           );
    oled_show_string(0,6,"(C) IDP.408SIC 2023,"    );
    oled_show_string(0,7,"All Rights Reserved."    );
    system_delay_ms(1500);
    oled_clear();
    oled_show_chinese(0, 0, 16, (const uint8 *)BOR,8);
    oled_show_string(0,4,"      -AUTHOR-"          );
    oled_show_string(0,6," Feng Wei,  Qiu Rui,"    );
    oled_show_string(0,7,"   Qin GuangQuan."       );
    system_delay_ms(1500);
}

void page_MASTER_show(){
    oled_show_string(0,0,"DOS by SIC v1.0" );
    oled_show_string(0,1,"./"              );
  //oled_show_string(0,2,""                );
    oled_show_string(0,3,"  START"         );//执行发车程序
    oled_show_string(0,4,"  test Ext.eq."  );//测试外设
    oled_show_string(0,5,"  chk. Params."  );//改变参数
  //oled_show_string(0,6,""                );
    oled_show_string(0,7,"-[UP/DOMN/CF/RT]");

    oled_show_string(0,3+point,"->"        );//屏幕指针
}

void page_MASTER_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(--point<0){
            point=2;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(++point>2){
            point=0;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        point=0;
        first_page();
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(point){
            case 0:now_page=START;break;
            case 1:now_page=TET;break;
            case 2:now_page=CP;break;
        }
        point=0;
    }
}

void page_TET_show(){
    oled_show_string(0,0,"test Ext.eq."            );
    oled_show_string(0,1,"./TET"                   );
  //oled_show_string(0,2,""                        );
    oled_show_string(0,3,"  GPS_TAU1201"           );
    oled_show_string(0,4,"  MPU6050"               );
    oled_show_string(0,5,"  IMU_Mahony"            );
    oled_show_string(0,6,"  SERVO"                 );
    oled_show_string(0,7,"-[UP/DOMN/CF/RT]"        );

    oled_show_string(0,3+point,"->"                );
}

void page_TET_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(--point<0){
            point=2;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(++point>2){
            point=0;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=MASTER;
        point=0;
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(point){
            case 0:now_page=GPS;break;
            case 1:now_page=MPU;break;
            case 2:now_page=IMU;break;
            case 3:now_page=SERVO;break;
        }
        point=0;
    }
}

void page_GPS_show(){
    oled_show_string(0,0,"GPS_TAU1201"             );
    oled_show_string(0,1,"./TET/GPS"               );
    if(gps_tau1201_flag){//GPS数据处理完成
        gps_tau1201_flag=0;
        if(!gps_tau1201.state){
            oled_show_string(0,4, "FAIL LOCATE");                //定位失败
            oled_show_string(0,6,"State lasts <2min."      );
            oled_show_string(0,7,"Indoor?Wiring bad?"      );
        }
        else{
            oled_show_string(0, 7, "TIM>");                      //时间
            oled_show_int(32,7,gps_tau1201.time.hour,2);
            oled_show_int(50,7,gps_tau1201.time.minute,2);
            oled_show_int(68,7,gps_tau1201.time.second,2);
            oled_show_string(0, 2, "N ->");
            oled_show_float(32,2,gps_tau1201.latitude,4,6);      //纬度
            oled_show_string(0, 3, "E ->");
            oled_show_float(32,3,gps_tau1201.longitude,4,6);     //经度
            oled_show_string(0, 4, "m/s>");
            oled_show_float(32,4,gps_tau1201.speed,4,6);         //速度
            oled_show_string(0, 5, "360>");
            oled_show_float(32,5,gps_tau1201.direction,4,6);     //方向
            oled_show_string(0, 6, "STL>");
            oled_show_int(32,6,gps_tau1201.satellite_used,2);    //卫星连接数量
        }
    }
}

void page_GPS_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
        point=0;
    }
}

void page_MPU_show(){
    oled_show_string(0,0,"MPU6050"                 );
    oled_show_string(0,1,"./TET/MPU"               );
    oled_show_string(0,3,"ACC(m/s^2)");
    oled_show_float(0,4,mpu6050_acc_transition(mpu6050_acc_x),2,4);
    oled_show_float(0,5,mpu6050_acc_transition(mpu6050_acc_y),2,4);
    oled_show_float(0,6,mpu6050_acc_transition(mpu6050_acc_z),2,4);
    oled_show_string(64,3,"GYRO('/s)");
    oled_show_float(64,4,mpu6050_gyro_transition(mpu6050_gyro_x),2,4);
    oled_show_float(64,5,mpu6050_gyro_transition(mpu6050_gyro_y),2,4);
    oled_show_float(64,6,mpu6050_gyro_transition(mpu6050_gyro_z),2,4);
}

void page_MPU_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
        point=0;
    }
}

void page_IMU_show(){
    oled_show_string(0,0,"IMU_Mahony"              );
    oled_show_string(0,1,"./TET/IMU"               );
    if(mpu6050_acc_x==mpu6050_acc_y && mpu6050_acc_y==mpu6050_acc_z){
        oled_show_string(0,3,"WARNING: MPU NO DATA");
    }
    oled_show_string(0,5,"X>rol>"                    );
    oled_show_float(42,5,imu.Roll,2,6);
    oled_show_string(0,6,"Y>pit>"                    );
    oled_show_float(42,6,imu.Pitch,2,6);
    oled_show_string(0,7,"Z>yaw>"                    );
    oled_show_float(42,7,imu.Yaw,2,6);
}

void page_IMU_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}





/*页面显示模板
void page_xx_show(){
  //oled_show_string(0,0,""                        );
  //oled_show_string(0,1,""                        );
  //oled_show_string(0,2,""                        );
  //oled_show_string(0,3,""                        );
  //oled_show_string(0,4,""                        );
  //oled_show_string(0,5,""                        );
  //oled_show_string(0,6,""                        );
  //oled_show_string(0,7,""                        );

  //oled_show_string(0,0+point,"->"                );
}
  页面操作模板
void page_xx_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(--point<0){
            point=;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(++point>){
            point=0;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(point){
            case 0:now_page=;break;
            case 1:now_page=;break;
            case 2:now_page=;break;
        }
    }
}
*/
void menu(void){//人机交互页面
    first_page();
    while(!gogogo){
        oled_clear();
        switch(now_page){
            case MASTER:page_MASTER_show();break;
            case TET   :page_TET_show();break;
            case GPS   :page_GPS_show();break;
            case MPU   :page_MPU_show();break;
            case IMU   :page_IMU_show();break;
            default    :page_error();
        }
        key_scanner();
        system_delay_ms(50);
        switch(now_page){
            case MASTER:page_MASTER_ex();break;
            case TET   :page_TET_ex();break;
            case GPS   :page_GPS_ex();break;
            case MPU   :page_MPU_ex();break;
            case IMU   :page_IMU_ex();break;
            default    :page_error();
        }
    }
}
