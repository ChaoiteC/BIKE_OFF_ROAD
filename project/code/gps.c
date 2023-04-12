#include "zf_common_headfile.h"

#define GPS_OFFSET 10 //GPS取平均次数 次数过多GPS可能漂移

enum POINT_TYPE{//点位类型
    FIRST,//起点
    STR,//直道
    UPHELL,//爬坡
    TAR,//掉头
    RTT,//绕柱
    SBD,//S弯
    FINISH//终点
};

/* @fn gps_check_flash
 * @brief 检查FLASH中是否存有点位数据
 * @param void
 * @return 0 mean no, 1 mean yes
 */
void gps_check_flash(void){
    
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
