/*Let me forget everything,
  still moonlight shines on us.
  Broken heart, 
  I don't want you to find and take a look at.
  So I'll sin more and destroy my thoughts, 
  make a mess of my hand.
  I swear on the darkest night I'll end it all.
  And testify....
  
  这个文件及它的头文件用于提供发车前的通用人机交互页面。有的功能有自己的人机交互界面。*/

#include "zf_common_headfile.h"
#define PID_NUMBER 3

uint8 now_page=0;                               //当前页面
uint8 gogogo=0;                                 //1=正式发车

int8 point=0;                                   //指示器
uint8 edit=0;
uint8 last_page=0;
uint8 flash_change=1;//为什么FLASH读写需要那么久(′へ`、 )

enum PAGE{
    MASTER,
    //START,
        GET_POINT,
      TET,
        GPS,
        MPU,
        IMU,
        BLE,
        SEV,
        ECD,
    //CP,
        PID_SUM,
}NOW_PAGE;

void menu(void){//人机交互页面
    first_page();
    while(!gogogo){
        oled_clear();
        if(last_page!=now_page){
            point=0;
            edit=0;
            flash_change=1;
        }
        last_page=now_page;
        switch(now_page){
            case MASTER   :page_MASTER_show();break;
            case GET_POINT:page_GET_POINT_show();break;
            case TET      :page_TET_show();break;
            case GPS      :page_GPS_show();break;
            case MPU      :page_MPU_show();break;
            case IMU      :page_IMU_show();break;
            case BLE      :page_BLE_show();break;
            case SEV      :page_SEV_show();break;
            case ECD      :page_ECD_show();break;
            case PID_SUM      :page_PID_show();break;
            default       :page_error();
        }
        key_scanner();
        system_delay_ms(50);
        switch(now_page){
            case MASTER   :page_MASTER_ex();break;
            case GET_POINT:page_GET_POINT_ex();break;
            case TET      :page_TET_ex();break;
            case GPS      :page_GPS_ex();break;
            case MPU      :page_MPU_ex();break;
            case IMU      :page_IMU_ex();break;
            case BLE      :page_BLE_ex();break;
            case SEV      :page_SEV_ex();break;
            case ECD      :page_ECD_ex();break;
            case PID_SUM  :page_PID_ex();break;
            default       :page_error();
        }
    }
}

/*其实为了节约内存，你可以选择在进入未定义页面时
  直接返回主页。就算要写一个错误页面，也不用写这
  么一大串没用的玩意。你写给谁看呢？而且事实上，
  当你完成程序的时候，根本不会再出现这种问题。
  所以，我设计这个页面的意义到底是什么？为什么
  我要在凌晨1点钟思考这个？难道真的没有别的事情
  需要做了吗？你的人生就像是这个页面一样失败而
  充满了混乱。*/
void page_error(void){
    oled_clear();
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

void gps_point_error(void){
    oled_clear();
    oled_show_string(0,0,"ERROR:"          );
    oled_show_string(0,1,"POINT_DATA_ERR"  );
    oled_show_string(0,2,"Maybe:"          );
    oled_show_string(0,4,"1.FLASH No data" );
    oled_show_string(0,5,"2.Data overflow" );
    oled_show_string(0,7,"NOW BACK TO <GP>");
}

//启动页面
void first_page(void){
    oled_clear();
    oled_show_chinese(0, 0, 16,(const uint8 *)IDP,6);
    oled_show_string(0,4,"BIKE_OFF_ROAD"           );
    oled_show_string(0,6,"(C) IDP.408SIC 2023,"    );
    oled_show_string(0,7,"All Rights Reserved."    );
    system_delay_ms(500);
    oled_clear();
    oled_show_chinese(0, 0, 16, (const uint8 *)BOR,8);
    oled_show_string(0,4,"      -AUTHOR-"          );
    oled_show_string(0,6," Feng Wei,  Qiu Run,"    );
    oled_show_string(0,7,"   Qin GuangQuan."       );
    system_delay_ms(500);
}

void page_MASTER_show(){
    oled_show_string(0,0,"DOS by SIC v1.0" );
    oled_show_string(0,1,"./"              );
    oled_show_string(0,3,"  START"         );//执行发车程序
    oled_show_string(0,4,"  test Ext.eq."  );//测试外设
    oled_show_string(0,5,"  change  PID "  );//改变参数
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
        first_page();
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(point){
            case 0:now_page=GET_POINT;break;
            case 1:now_page=TET;break;
            case 2:now_page=PID_SUM;break;
        }
    }
}


void page_GET_POINT_show(){
    oled_show_string(0,0,"GET_POINT"               );
    oled_show_string(0,1,"./SRT/GPT"               );
    oled_show_string(0,3,"GPS POINT?"              );
    oled_show_string(0,5,"  USE FLASH DATA"        );
    oled_show_string(0,6,"  RECORD NEW"            );

    oled_show_string(0,5+point,"->"                );
}

void page_GET_POINT_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(--point<0){
            point=1;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(++point>1){
            point=0;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=MASTER;
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(point){
            case 0:{//使用既有点位
                if(gps_check_flash()){
                    gps_point_error();
                    system_delay_ms(3000);
                    now_page=GET_POINT;
                }
                else{
                    gogogo=1;
                }
            }break;
            case 1:{//重新录入点位
                if(gps_get_point()){
                    gps_point_error();
                    system_delay_ms(3000);
                    now_page=GET_POINT;
                }
                else{
                    gogogo=1;
                }
                break;
            }
        }
    }
}

void page_TET_show(){
    oled_show_string(0,0,"test Ext.eq."            );
    oled_show_string(0,1,"./TET"                   );
    if(point<=3){
        oled_show_string(0,3,"  GPS_TAU1201"           );
        oled_show_string(0,4,"  MPU6050"               );
        oled_show_string(0,5,"  IMU_Mahony"            );
        oled_show_string(0,6,"  BLUETOOTH"             );
    }
    else{
        oled_show_string(0,3,"  SERVO"                 );
        oled_show_string(0,4,"  ENCODER"               );
    }
    oled_show_string(0,7,"-[UP/DOMN/CF/RT]"            );
    if(point<=3){
        oled_show_string(0,3+point,"->"                );
    }
    else{
        oled_show_string(0,point-1,"->"                );
    }
    
}

void page_TET_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(--point<0){
            point=5;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(++point>5){
            point=0;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=MASTER;
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(point){
            case 0:now_page=GPS;break;
            case 1:now_page=MPU;break;
            case 2:now_page=IMU;break;
            case 3:now_page=BLE;break;
            case 4:now_page=SEV;break;
            case 5:now_page=ECD;break;
        }
    }
}

void page_GPS_show(){
    oled_show_string(0,0,"GPS_TAU1201"             );
    oled_show_string(0,1,"./TET/GPS"               );
    if(gps_tau1201_flag){//GPS数据处理完成
        gps_tau1201_flag=0;
        gps_show_if();
    }
}

void page_GPS_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}

void page_MPU_show(){
    oled_show_string(0,0,"MPU6050"                );
    oled_show_string(0,1,"./TET/MPU"               );
    oled_show_string(0,3,"A");
    oled_show_float(0,4,mpu6050_acc_transition(mpu6050_acc_x),2,6);
    oled_show_float(0,5,mpu6050_acc_transition(mpu6050_acc_y),2,6);
    oled_show_float(0,6,mpu6050_acc_transition(mpu6050_acc_z),2,6);

    oled_show_string(64,3,"G");
    oled_show_float(64,4,mpu6050_gyro_transition(mpu6050_gyro_x),2,6);
    oled_show_float(64,5,mpu6050_gyro_transition(mpu6050_gyro_y),2,6);
    oled_show_float(64,6,mpu6050_gyro_transition(mpu6050_gyro_z),2,6);
}

void page_MPU_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}

void page_IMU_show(){
    oled_show_string(0,0,"IMU_Mahony"              );
    oled_show_string(0,1,"./TET/IMU"               );
    if(mpu6050_acc_x==mpu6050_acc_y && mpu6050_acc_y==mpu6050_acc_z){
        oled_show_string(0,2,"WARNING: MPU NO DATA");
    }
    oled_show_string(42,3,"MHY  FCOF"                );
    oled_show_string(0,5,"X>rol>"                    );
    oled_show_int(42,5,(int)imu.Roll,2);
    oled_show_int(72,5,(int)FCOF_info.Roll,2);
    oled_show_string(0,6,"Y>pit>"                    );
    oled_show_int(42,6,(int)imu.Pitch,2);
    oled_show_int(72,6,(int)FCOF_info.Pitch,2);
    oled_show_string(0,7,"Z>yaw>"                    );
    oled_show_int(42,7,(int)imu.Yaw,2);
    oled_show_int(72,7,(int)FCOF_info.Yaw,2);
}

void page_IMU_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}

void page_BLE_show(){
    uint8 data_buffer[32];
    bluetooth_ch9141_read_buff(data_buffer,32);
    oled_show_string(0,0,"BLUETOOTH"               );
    oled_show_string(0,1,"./TET/BLE"               );
    oled_show_string(0,3,"TX TEXT:"                );
    oled_show_string(0,4,(const char *)data_buffer );
}

void page_BLE_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}

void page_SEV_show(){
    oled_show_string(0,0,"SERVO"                   );
    oled_show_string(0,1,"./TET/SEV"               );
  //oled_show_string(0,2,""                        );
  //oled_show_string(0,3,""                        );
  //oled_show_string(0,4,""                        );
  //oled_show_string(0,5,""                        );
  //oled_show_string(0,6,""                        );
  //oled_show_string(0,7,""                        );
  //oled_show_string(0,0+point,"->"                );
}

void page_SEV_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}


void page_ECD_show(){
    oled_show_string(0, 0, "ENCODER");
    oled_show_string(0,1,"./TET/ECD"                );
    oled_show_float (0,3,encoder_data_quaddec,4,4);
    oled_show_string(0,4, "PID_OUTPUT");
    oled_show_float (0,5,MOTOR1_SUM.output,4,4);
    oled_show_float (0,6,MOTOR1_SUM.integral,4,4);
    oled_show_float (0,7,MOTOR1_SUM.expect,4,4);



}

void page_ECD_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}


void page_PID_show(){
    if(flash_change){
        flash_read_page_to_buffer(63,3);
        flash_change=0;
    }
    int8 i;
    oled_show_string(0,0,"PID CHANGE"              );
    oled_show_string(0,1,"./CP/PID"                );
    for(i=0;i<5/* || i<PID_NUMBER*/;i++){
        oled_show_float(98,i+2,flash_union_buffer[point+i].float_type,2,2);
        switch(point+i){
            case 0:oled_show_string(0,i+2,"M1.P");break;
            case 1:oled_show_string(0,i+2,"M1.I");break;
            case 2:oled_show_string(0,i+2,"M1.D");break;
            case 3:oled_show_string(0,i+2,"M1.MI");break;
            case 4:oled_show_string(0,i+2,"M1.MO");break;
        }
    }


    if(edit){
        oled_show_string(0,7,"     [+/-/CF/RT]");
        oled_show_string(86,2,">>"     );
    }
    else{
        oled_show_string(0,7,"-[UP/DOWN/CF/RT]");
        oled_show_string(86,2,"->"     );
    }
}

void page_PID_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(edit){
            flash_union_buffer[point].float_type+=0.01;
        }
        else{
            if(--point<0){
                point=PID_NUMBER;
            }
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(edit){
            flash_union_buffer[point].float_type-=0.01;
        }
        else{
            if(++point>PID_NUMBER){
                point=0;
            }
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        if(edit){
            edit=!edit;
            flash_change=1;
        }
        else{
            now_page=MASTER;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        if(edit){
            oled_show_string(0,7,"SIT AND RELAX...");
            flash_write_page_from_buffer(63,3);
            flash_change=1;
            edit=!edit;
            /*这里要更新PID*/
        }
        else{
            edit=!edit;
        }
    }

}

/*//页面显示模板
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
  //页面操作模板
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
