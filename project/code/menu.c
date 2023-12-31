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
#define FLASH_NUMBER 14

uint8 now_page=0;                               //当前页面
uint8 release=0;                                 //1=放行

int8 point=0;                                   //指示器
uint8 edit=0;
uint8 last_page=0;
uint8 flash_change=1;//为什么FLASH读写需要那么久(′へ`、 )

enum PAGE{
    MASTER,
      GET_POINT,
      TET,
        GPS,
        AGM,
        IMU,
        BLE,
        SEV,
        BLC,
      FLS,
}NOW_PAGE;

void menu(void){//人机交互页面
    first_page();
    while(!release){
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
            case AGM      :page_AGM_show();break;
            case IMU      :page_IMU_show();break;
            case BLE      :page_BLE_show();break;
            case SEV      :page_SEV_show();break;
            case BLC      :page_BLC_show();break;
            case FLS      :page_FLS_show();break;
            default       :page_error();
        }
        key_scanner();
        system_delay_ms(50);
        switch(now_page){
            case MASTER   :page_MASTER_ex();break;
            case GET_POINT:page_GET_POINT_ex();break;
            case TET      :page_TET_ex();break;
            case GPS      :page_GPS_ex();break;
            case AGM      :page_AGM_ex();break;
            case IMU      :page_IMU_ex();break;
            case BLE      :page_BLE_ex();break;
            case SEV      :page_SEV_ex();break;
            case BLC      :page_BLC_ex();break;
            case FLS      :page_FLS_ex();break;
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
    system_delay_ms(3000);
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
            case 2:now_page=FLS;break;
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
                    now_page=GET_POINT;
                }
                else{
                    release=1;
                }
            }break;
            case 1:{//重新录入点位
                if(gps_get_point_UI()){
                    gps_point_error();
                    now_page=GET_POINT;
                }
                else{
                    release=1;
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
        oled_show_string(0,4,"  IMU963RA"              );
        oled_show_string(0,5,"  IMU_FCOF"              );
        oled_show_string(0,6,"  BLUETOOTH"             );
    }
    else{
        oled_show_string(0,3,"  SERVO"                 );
        oled_show_string(0,4,"  BALANCE"               );
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
            case 1:now_page=AGM;break;
            case 2:now_page=IMU;break;
            case 3:now_page=BLE;break;
            case 4:now_page=SEV;break;
            case 5:now_page=BLC;break;
        }
    }
}

void page_GPS_show(){
    oled_show_string(0,0,"GPS_TAU1201"             );
    oled_show_string(0,1,"./TET/GPS"               );
    gps_show_if();
}

void page_GPS_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}

void page_AGM_show(){
    oled_show_string(0,0,"IMU963RA"                );
    oled_show_string(0,1,"./TET/AGM"               );
    oled_show_string(0,3,"A");
    oled_show_float(0,4,imu963ra_acc_transition(imu963ra_acc_x),2,2);
    oled_show_float(0,5,imu963ra_acc_transition(imu963ra_acc_y),2,2);
    oled_show_float(0,6,imu963ra_acc_transition(imu963ra_acc_z),2,2);

    oled_show_string(36,3,"G");
    oled_show_float(36,4,imu963ra_gyro_transition(imu963ra_gyro_x),2,2);
    oled_show_float(36,5,imu963ra_gyro_transition(imu963ra_gyro_y),2,2);
    oled_show_float(36,6,imu963ra_gyro_transition(imu963ra_gyro_z),2,2);

    oled_show_string(72,3,"M");
    oled_show_float(72,4,imu963ra_mag_transition(imu963ra_mag_x),2,2);
    oled_show_float(72,5,imu963ra_mag_transition(imu963ra_mag_y),2,2);
    oled_show_float(72,6,imu963ra_mag_transition(imu963ra_mag_z),2,2);
}

void page_AGM_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}

void page_IMU_show(){
    oled_show_string(0,0,"IMU_FOCF"              );
    oled_show_string(0,1,"./TET/IMU"               );
    if(imu963ra_acc_x==imu963ra_acc_y && imu963ra_acc_y==imu963ra_acc_z){
        oled_show_string(0,2,"WARNING: AGM NO DATA");
    }
    oled_show_string(0,4,"X>rol>"                    );
    oled_show_int(42,4,(int)IMU_Data.Roll,4);
    oled_show_string(0,5,"Y>pit>"                    );
    oled_show_int(42,5,(int)IMU_Data.Pitch,4);
    oled_show_string(0,6,"Z>yaw>"                    );
    oled_show_int(42,6,(int)IMU_Data.Yaw,4);
    oled_show_string(0,7,"-[UP/DOMN/CF/RT]"            );
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
    oled_show_int(84,7,encoder_data_quaddec,4);
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


void page_BLC_show(){
    oled_show_string(0, 0, "BALANCE");
    oled_show_string(0,1,"./TET/BLC"                );
    oled_show_string(0,4,"    ACC  ANG  VEL"        );
    oled_show_string(0,5,"OUT"                      );
    oled_show_string(0,6,"ERR"                      );
    oled_show_string(0,7,"RAW"                      );
    oled_show_int(24,5,balance_acc.output,4);
    oled_show_int(24,6,balance_acc.error,4);
    oled_show_int(24,7,imu963ra_acc_x,4);
    oled_show_int(54,5,balance_ang.output,4);
    oled_show_int(54,6,balance_ang.error,4);
    oled_show_int(54,7,IMU_Data.Roll,4);
    oled_show_int(84,5,balance_vel.output,4);
    oled_show_int(84,6,balance_vel.error,4);
    oled_show_int(84,7,encoder_data_quaddec,4);



}

void page_BLC_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}


void page_FLS_show(){
    if(flash_change){
        flash_read_page_to_buffer(63,3);
        flash_change=0;
    }
    int8 i;
    oled_show_string(0,0,"FLASH EDITER"         );
    oled_show_string(0,1,"./FLS"                );
    for(i=0;i<5&&point+i<FLASH_NUMBER;i++){
        oled_show_float(84,i+2,flash_union_buffer[point+i].float_type,5,2);
        switch(point+i){//显示在数值左边的注释。不能超过12个字符，虽然大部分情况也不会超过。
            case  0:oled_show_string(0,i+2,"B_acc.P");break;
            case  1:oled_show_string(0,i+2,"B_acc.I");break;
            case  2:oled_show_string(0,i+2,"B_acc.D");break;
            case  3:oled_show_string(0,i+2,"B_acc.MI");break;
            case  4:oled_show_string(0,i+2,"B_acc.MO");break;
            case  5:oled_show_string(0,i+2,"B_ang.P");break;
            case  6:oled_show_string(0,i+2,"B_ang.I");break;
            case  7:oled_show_string(0,i+2,"B_ang.D");break;
            case  8:oled_show_string(0,i+2,"B_ang.MI");break;
            case  9:oled_show_string(0,i+2,"B_ang.MO");break;
            case 10:oled_show_string(0,i+2,"B_vel.P");break;
            case 11:oled_show_string(0,i+2,"B_vel.I");break;
            case 12:oled_show_string(0,i+2,"B_vel.D");break;
            case 13:oled_show_string(0,i+2,"B_vel.MI");break;
            case 14:oled_show_string(0,i+2,"B_vel.MO");break;
        }
    }
    if(edit){
        oled_show_string(0,7,"     [+/-/CF/RT]");
        oled_show_string(72,2,">>"     );
    }
    else{
        oled_show_string(0,7,"-[UP/DOWN/CF/RT]");
        oled_show_string(72,2,"->"     );
    }
}

void page_FLS_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(edit){
            flash_union_buffer[point].float_type+=0.1;
        }
        else{
            if(--point<0){
                point=FLASH_NUMBER-1;
            }
        }
    }
    else if(KEY_LONG_PRESS==key_get_state(KEY_UP)){
        if(edit){
            flash_union_buffer[point].float_type+=0.005;//0.0005是一个经验得出的值，这样比较舒适，因为每次判定长按都会增加。
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(edit){
            flash_union_buffer[point].float_type-=0.1;
        }
        else{
            if(++point>=FLASH_NUMBER){
                point=0;
            }
        }
    }
    else if(KEY_LONG_PRESS==key_get_state(KEY_DOWN)){
        if(edit){
            flash_union_buffer[point].float_type-=0.005;
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
            flash_data_update();
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
