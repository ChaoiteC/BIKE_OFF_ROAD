#ifndef __GPS_H
#define __GPS_H
#include "zf_driver_uart.h"


//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
#define GPS_TAU1201_UART    UART_3	
#define GPS_TAU1201_RX      UART3_MAP0_TX_B10    // GPS RX引脚连接到单片机此
#define GPS_TAU1201_TX      UART3_MAP0_RX_B11    // GPS TX串口引脚



#define ANGLE_TO_RAD(X)    (X * PI / 180.0)//角度转换为弧度
#define RAD_TO_ANGLE(X)    (X * 180.0 / PI)//弧度转换为角度
#define PI                  3.1415926535898


typedef struct{
    
  unsigned char       state;              //有效状态  1：定位有效  0：定位无效
    
  unsigned short int      latitude_degree;	//度
	unsigned short int      latitude_cent;		//分
	unsigned short int      latitude_second;    //秒
	unsigned short int      longitude_degree;	//度
	unsigned short int      longitude_cent;		//分
	unsigned short int      longitude_second;   //秒
    
  double      latitude;           //经度
  double      longitude;          //纬度
    
  char 	    ns;                 //纬度半球 N（北半球）或 S（南半球）
  char 	    ew;                 //经度半球 E（东经）或 W（西经）
    
  //下面信息从GNGGA语句中获取
  unsigned char       satellite_used;     //用于定位的卫星数量  
}gps_info_struct;

extern gps_info_struct gps_tau1201;
extern unsigned char gps_tau1201_flag;

double  get_two_points_distance(double lat1, double lng1, double lat2, double lng2);
double  get_two_points_azimuth(double lat1, double lon1, double lat2, double lon2);
void    gps_uart_callback(void);
void    gps_init(void);
void 		gps_data_parse(void);



#endif


