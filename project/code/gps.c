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
    for(i=0,column=0;i<point_number && i!=GPS_DATA_MAX;i++){
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

/* @fn gps_data_to_flash
 * @brief 将GPS点位存入FLASH
 * @param latitude 纬度
 * @param longitude 经度
 * @param point_type 点位类型
 * @return 
 */

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

/* @fn gps_get_point
 * @brief GPS
 * @param void
 * @return void
 */
void gps_get_point(type){
    
}