/*大都会　空に向かって　
  伸びていくビルに夕焼け
  駆け出せ　目を開け
  影　引き連れてゆけ
  ひとりじゃない*/

#include "zf_common_headfile.h"



enum POINT_TYPE{//点位类型
    FIRST,//起点
    STR,//直道
    UPHELL,//爬坡
    TAR,//掉头
    RTT,//绕柱
    SBD,//S弯
    FINISH//终点
};

GPS_POINT gps_point[GPS_DATA_MAX];

/* @fn gps_read_flash
 * @brief 从FLASH中读出点位数据
 * @param void
 * @return 0 mean yes, 1 mean error
 */

int gps_check_flash(void){
    int i,column,section=GPS_DATA_SECTION_START_INDEX,page=GPS_DATA_PAGE_START_INDEX,point_number;
    flash_buffer_clear();
    flash_read_page_to_buffer(63,3);// 将GPS点位数量从 flash 读取到缓冲区
    point_number=flash_union_buffer[0].uint8_type;//获取点位数量
    flash_read_page_to_buffer(GPS_DATA_SECTION_START_INDEX,GPS_DATA_PAGE_START_INDEX);
    for(i=0,column=0;i<point_number && i<GPS_DATA_MAX;i++){
        gps_point[i].latitude=flash_union_buffer[1+column].float_type;
        gps_point[i].longitude=flash_union_buffer[2+column].float_type;
        gps_point[i].point_type=flash_union_buffer[3+column].uint8_type;
        if(column==3){
            column=0;
            if(--page<0){//翻页
                page=3;
                section--;//扇区
            }
            flash_buffer_clear();
            flash_read_page_to_buffer(section,page);
        }
        else{
            column=3;
        }
    }
    if(gps_point[i-1].point_type!=FINISH){
        return 1;
    }
    else{
        return 0;
    }
}

/* @fn gps_display_point_type
 * @brief 显示GPS点类型选择页面
 * @param point_type 当前选择的GPS点类型
 * @return void
 */
void gps_display_point_type(uint8_t point_type) {
    oled_clear();
    oled_show_chinese(0, 0, 16,(const uint8 *)POINT_TYPE,5);
    oled_show_string(0,3,"[UP]"                      );
    oled_show_string(0,5,"[DOWN]"                    );
    oled_show_string(0,7,"[COF]  [RVK]"              );
    switch(point_type){
        case 1:oled_show_string(36,4,"STR---"            );break;
        case 2:oled_show_string(36,4,"UPHELL"            );break;
        case 3:oled_show_string(36,4,"-TAR--"            );break;
        case 4:oled_show_string(36,4,"--RTT-"            );break;
        case 5:oled_show_string(36,4,"---SBD"            );break;
        case 6:oled_show_string(36,4,"FINISH"            );
    }
}

/* @fn gps_line_write
 * @brief 向GPS点位数组的指定行写入数据
 * @param line 指定行
 * @param latitude 纬度
 * @param longitude 经度
 * @param point_type 点位类型
 * @return void
 */
void gps_line_write(int line,float latitude,float longitude,uint8 point_type){
    gps_point[line].latitude=latitude;
    gps_point[line].longitude=longitude;
    gps_point[line].point_type=point_type;
}

/* @fn gps_get_point
 * @brief GPS取点的专门用户交互页面
 * @param void
 * @return 0 mean yes, 1 mean error
 * @notice 我超写那么紧密耦合鬼看得懂
 */
int gps_get_point(void){
    int i=0,j=0,column=0,section=GPS_DATA_SECTION_START_INDEX,page=GPS_DATA_PAGE_START_INDEX;
    float latitude,longitude;
    uint8 point_type=1;
    while(i<GPS_DATA_MAX){
        gps_display_point_type(point_type);
        key_scanner();
        system_delay_ms(50);
        if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
            if(--point_type<1){
                point_type=6;
            }
        }
        else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
            if(++point_type>6){
                point_type=1;
            }
        }
        else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
            if(--i<0){
                return 1;
            }
            else{
                gps_line_write(i,0.0,0.0,0);
            }
        }
        else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
            gps_average_pointing(&latitude,&longitude);
            gps_line_write(i++,latitude,longitude,point_type);
            if(point_type==FINISH){
                break;
            }
            else if(i>=GPS_DATA_MAX){
                return 1;
            }
        }
    }
    //这里将GPS数据逐个录入FLASH
    flash_buffer_clear();
    flash_erase_sector(section,page);
    for(j=0;j<i;j++){
        flash_union_buffer[0+column].float_type=gps_point[j].latitude;
        flash_union_buffer[1+column].float_type=gps_point[j].longitude;
        flash_union_buffer[2+column].uint8_type=gps_point[j].point_type;
        if(column==0){
            column=3;
        }
        else{
            column=0;
            while(flash_write_page_from_buffer(section,page));
            if(--page<0){
                page=3;
                section--;
            }
            flash_erase_sector(section,page);
            flash_buffer_clear();
        }
    }
    flash_read_page_to_buffer(63,3);
    flash_union_buffer[0].uint8_type=i;
    flash_write_page_from_buffer(63,3);
    return 0;
}

/* @fn gps_average_pointing
 * @brief 获取GPS_OFFSET次GPS经纬度并取其平均值
 * @param *average_latitude 平均纬度
 * @param *average_longitude 平均经度
 * @return void
 */
void gps_average_pointing(int8* average_latitude,int8* average_longitude){
    double latitude_total=0;
    double longitude_total=0;
    int i=0;
    while(i<GPS_OFFSET){
        oled_clear();
        oled_show_string(0,0,"GPS GET POINT NOW");
        oled_show_int(0,1,i,2);
        oled_show_string(0,3,"WAITING GPS...");
        while(!gps_tau1201_flag);//等待GPS信号
        gps_tau1201_flag=0;
        if(!gps_tau1201.state){
            oled_show_string(0,3,"GPS FAIL LOCATE");                //定位失败
        }
        else{
            oled_show_string(0,3, "               ");
            oled_show_string(0, 5, "N ->");
            oled_show_float(32,5,gps_tau1201.latitude,4,6);      //纬度
            oled_show_string(0, 6, "E ->");
            oled_show_float(32,6,gps_tau1201.longitude,4,6);     //经度
            oled_show_string(0, 7, "STL>");
            oled_show_int(32,7,gps_tau1201.satellite_used,2);    //卫星连接数量
            latitude_total+=gps_tau1201.latitude;
            longitude_total+=gps_tau1201.longitude;
            i++;
        }
    }
    *average_latitude=latitude_total/GPS_OFFSET;
    *average_longitude=longitude_total/GPS_OFFSET;
}

void gps_show_point(void){
    int i,j;
    flash_read_page_to_buffer(63,3);
    j=flash_union_buffer[0].uint8_type;
    for(i=0;i<j;i++){
        oled_show_uint(0,0,i,2);
        oled_show_string(0, 4, "N ->");
        oled_show_float(32,4,gps_point[i].latitude,4,6);      //纬度
        oled_show_string(0, 5, "E ->");
        oled_show_float(32,5,gps_point[i].longitude,4,6);
        oled_show_string(0, 6, "TP->");
        switch(gps_point[i].point_type){
            case 1:oled_show_string(36,6,"STR---"            );break;
            case 2:oled_show_string(36,6,"UPHELL"            );break;
            case 3:oled_show_string(36,6,"-TAR--"            );break;
            case 4:oled_show_string(36,6,"--RTT-"            );break;
            case 5:oled_show_string(36,6,"---SBD"            );break;
            case 6:oled_show_string(36,6,"FINISH"            );
        }
        system_delay_ms(100);
    }
}
