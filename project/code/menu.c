/*Let me forget everything, still moonlight shines on us.
  Broken heart, I don't want you to find and take a look at.
  So I'll sin more and destroy my thoughts, make a mess of my hand.
  I swear on the darkest night I'll end it all.
  And testify....*/

#include "zf_common_headfile.h"





uint8 now_page=0;//当前页面
uint8 gogogo=0;//1=正式发车

int8 select=0;
uint8 edit=0;
uint8 last_page=0;

enum PAGE{
    MASTER,
    //START,
        GET_POINT,
      TET,
        GPS,
        AGM,
        IMU,
        BLE,
    //CP,
        FLS,
}NOW_PAGE;

void menu(void){//人机交互页面
    first_page();
    while(!gogogo){
        oled_clear();
        if(last_page!=now_page){
            select=0;
            edit=0;
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
    oled_show_string(0,5,"  chk. Params."  );//改变参数
    oled_show_string(0,7,"-[UP/DOMN/CF/RT]");

    oled_show_string(0,3+select,"->"        );//屏幕指针
}

void page_MASTER_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(--select<0){
            select=2;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(++select>2){
            select=0;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        first_page();
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(select){
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

    oled_show_string(0,5+select,"->"                );
}

void page_GET_POINT_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(--select<0){
            select=1;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(++select>1){
            select=0;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=MASTER;
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(select){
            case 0:{
                if(gps_check_flash()){
                    gps_point_error();
                    system_delay_ms(3000);
                    now_page=GET_POINT;
                }
            }break;
            case 1:{
                if(gps_get_point()){
                    gps_point_error();
                    system_delay_ms(3000);
                    now_page=GET_POINT;
                }
                else{
                    
                }
                break;
            }
        }
    }
}

void page_TET_show(){
    oled_show_string(0,0,"test Ext.eq."            );
    oled_show_string(0,1,"./TET"                   );
    oled_show_string(0,3,"  GPS_TAU1201"           );
    oled_show_string(0,4,"  IMU963RA"              );
    oled_show_string(0,5,"  IMU_Mahony"            );
    oled_show_string(0,6,"  BLUETOOTH"             );
    oled_show_string(0,7,"-[UP/DOMN/CF/RT]"        );

    oled_show_string(0,3+select,"->"                );
}

void page_TET_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(--select<0){
            select=3;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(++select>3){
            select=0;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=MASTER;
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        switch(select){
            case 0:now_page=GPS;break;
            case 1:now_page=AGM;break;
            case 2:now_page=IMU;break;
            case 3:now_page=BLE;break;
        }
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
    }
}

void page_AGM_show(){
    oled_show_string(0,0,"IMU963RA"                );
    oled_show_string(0,1,"./TET/AGM"               );
    oled_show_string(0,3,"A");
    oled_show_float(0,4,imu963ra_acc_transition(imu963ra_acc_x),2,2);
    oled_show_float(0,5,imu963ra_acc_transition(imu963ra_acc_y),2,2);
    oled_show_float(0,6,imu963ra_acc_transition(imu963ra_acc_z),2,2);

    oled_show_string(30,3,"G");
    oled_show_float(30,4,imu963ra_gyro_transition(imu963ra_gyro_x),2,2);
    oled_show_float(30,5,imu963ra_gyro_transition(imu963ra_gyro_y),2,2);
    oled_show_float(30,6,imu963ra_gyro_transition(imu963ra_gyro_z),2,2);

    oled_show_string(60,3,"M");
    oled_show_float(60,4,imu963ra_mag_transition(imu963ra_mag_x),2,2);
    oled_show_float(60,5,imu963ra_mag_transition(imu963ra_mag_y),2,2);
    oled_show_float(60,6,imu963ra_mag_transition(imu963ra_mag_z),2,2);
}

void page_AGM_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}

void page_IMU_show(){
    oled_show_string(0,0,"IMU_Mahony"              );
    oled_show_string(0,1,"./TET/IMU"               );
    if(imu963ra_acc_x==imu963ra_acc_y && imu963ra_acc_y==imu963ra_acc_z){
        oled_show_string(0,3,"WARNING: IMU NO DATA");
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

void page_BLE_show(){
    uint8 data_buffer[32];
    bluetooth_ch9141_read_buff(data_buffer,32);
    oled_show_string(0,0,"BLUETOOTH"               );
    oled_show_string(0,1,"./TET/BLE"               );
    oled_show_string(0,3,"TX TEXT:"                );
    oled_show_string(0,4,data_buffer               );
}

void page_BLE_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        now_page=TET;
    }
}

void page_FLS_show(){
    flash_read_page_to_buffer (63,3);
    oled_show_string(0,0,"FLASH TEST"              );
    oled_show_string(0,1,"./CP/FLS"                );
    for (int i=0;i<8;i++) {
        int x=(i<4)?12:64;
        int y=3+(i%4);
        oled_show_float(x,y,flash_union_buffer[i].float_type,2,1);
    }
    if(edit){
        oled_show_string(0,7,"-    [+/-/DF/RT]");
        if(select<=3){
            oled_show_string(0,3+select,">>"     );
        }
        else{
            oled_show_string(0,select-1,">>"     );
        }
    }
    else{
        oled_show_string(0,7,"-[UP/DOWN/CF/RT]");
        if(select<=3){
            oled_show_string(0,3+select,"->"     );
        }
        else{
            oled_show_string(0,select-1,"->"     );
        }
    }
}

void page_FLS_ex(){
    if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
        if(edit){
            flash_union_buffer[select].float_type+=0.1;
        }
        else{
            if(--select<0){
                select=7;
            }
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
        if(edit){
            flash_union_buffer[select].float_type-=0.1;
        }
        else{
            if(++select>7){
                select=0;
            }
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
        if(edit){
            edit=!edit;
        }
        else{
            now_page=MASTER;
        }
    }
    else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
        if(!edit){
            edit=!edit;
        }
    }
    flash_write_page_from_buffer(63,3);
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
