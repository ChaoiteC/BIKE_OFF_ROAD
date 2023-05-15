#ifndef GPS_H_
#define GPS_H_

#include "zf_common_headfile.h"

#define GPS_OFFSET 10 //GPS取平均次数 次数过多GPS可能漂移
#define GPS_DATA_SECTION_START_INDEX 63 //GPS点位数据开始记录的扇区，倒数，前面是其他数据
#define GPS_DATA_PAGE_START_INDEX     2 //GPS点位数据开始记录的页数，倒数，前面是其他数据

#define GPS_DATA_MAX  20 //GPS点位记录的最大量

extern int gps_point_number;

enum POINT_TYPE{//点位类型
    FIRST,//起点
    STR,//直道
    UPHELL,//爬坡
    TAR,//掉头
    RTT,//绕柱
    SBD,//S弯
    FINISH//终点
};
typedef struct{
    float latitude;//纬度
    float longitude;//经度
    uint8 point_type;//点位类型
}GPS_POINT;

extern GPS_POINT gps_point[GPS_DATA_MAX];

int gps_check_flash(void);
int gps_get_point();
void gps_average_pointing();
int gps_show_if();

#endif /* GPS_H_ */
