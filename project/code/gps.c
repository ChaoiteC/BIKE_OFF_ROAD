/*差し出すな君のその首を
  走り出して戻るなその道を
  決して犯すな過ちを
  振り返れば吸われる赤い血を*/

#include "zf_common_headfile.h"

/* @fn gps_read_flash
 * @brief 从FLASH中读出点位数据
 * @param void
 * @return 0 mean yes, 1 mean error
 */
int gps_check_flash(void){
    int i,column,section=GPS_DATA_SECTION_START_INDEX,page=GPS_DATA_PAGE_START_INDEX,point_number;
    flash_read_page_to_buffer(GPS_DATA_SECTION_START_INDEX,GPS_DATA_PAGE_START_INDEX);// 将GPS首页数据从 flash 读取到缓冲区
    point_number=flash_union_buffer[0].uint8_type;//获取点位数量
    for(i=0,column=0;i<point_number && i<GPS_DATA_MAX;i++){
        gps_point[i].latitude=flash_union_buffer[1+column].int16_type;
        gps_point[i].longitude=flash_union_buffer[2+column].int16_type;
        gps_point[i].point_type=flash_union_buffer[3+column].uint8_type;
        if(column==3){
            column=0;
            if(--page<0){//翻页
                page=3;
                section--;//扇区
            }
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
 */
int gps_get_point(void){
    int i=0,column=0,section=GPS_DATA_SECTION_START_INDEX,page=GPS_DATA_PAGE_START_INDEX;
    float latitude,longitude;
    uint8 point_type=1;
    oled_show_chinese(0, 0, 16,(const uint8 *)POINT_TYPE,5);
    oled_show_string(0,3,"[UP]"                      );
    oled_show_string(0,5,"[DOWN]"                    );
    oled_show_string(0,7,"[COF]  [RVK]"              );
    while(i<GPS_DATA_MAX){
        switch(point_type){
            case 1:oled_show_string(0,4,"STR---"            );break;
            case 2:oled_show_string(0,4,"UPHELL"            );break;
            case 3:oled_show_string(0,4,"-TAR--"            );break;
            case 4:oled_show_string(0,4,"--RTT-"            );break;
            case 5:oled_show_string(0,4,"---SBD"            );break;
            case 6:oled_show_string(0,4,"FINISH"            );
        }
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
            if(point_type==6){
                break;
            }
            else if(i>=GPS_DATA_MAX){
                return 1;
            }
        }
    }
    //这里将GPS数据逐个录入FLASH
}

/* @fn gps_average_pointing
 * @brief 获取GPS_OFFSET次GPS经纬度并取其平均值
 * @param *average_latitude 平均纬度
 * @param *average_longitude 平均经度
 * @return void
 */
void gps_average_pointing(int8* average_latitude,int8* average_longitude){
    double latitude_total;
    double longitude_total;
    int i;
    for(i=0;i<GPS_OFFSET;i++){
        while(!gps_tau1201_flag);//等待GPS信号
        gps_tau1201_flag=0;
        latitude_total+=gps_tau1201.latitude;
        longitude_total+=gps_tau1201.longitude;
    }
    *average_latitude=latitude_total/GPS_OFFSET;
    *average_longitude=longitude_total/GPS_OFFSET;
}
