/*关于GPS的若干函数 by 碳白*/

#include "zf_common_headfile.h"

#define GPS_OFFSET 10

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
