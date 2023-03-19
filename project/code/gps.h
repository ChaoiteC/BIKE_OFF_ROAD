#ifndef __GPS_H
#define __GPS_H
#include "zf_driver_uart.h"


//--------------------------------------------------------------------------------------------------
//��������
//--------------------------------------------------------------------------------------------------
#define GPS_TAU1201_UART    UART_3	
#define GPS_TAU1201_RX      UART3_MAP0_TX_B10    // GPS RX�������ӵ���Ƭ����
#define GPS_TAU1201_TX      UART3_MAP0_RX_B11    // GPS TX��������



#define ANGLE_TO_RAD(X)    (X * PI / 180.0)//�Ƕ�ת��Ϊ����
#define RAD_TO_ANGLE(X)    (X * 180.0 / PI)//����ת��Ϊ�Ƕ�
#define PI                  3.1415926535898


typedef struct{
    
  unsigned char       state;              //��Ч״̬  1����λ��Ч  0����λ��Ч
    
  unsigned short int      latitude_degree;	//��
	unsigned short int      latitude_cent;		//��
	unsigned short int      latitude_second;    //��
	unsigned short int      longitude_degree;	//��
	unsigned short int      longitude_cent;		//��
	unsigned short int      longitude_second;   //��
    
  double      latitude;           //����
  double      longitude;          //γ��
    
  char 	    ns;                 //γ�Ȱ��� N�������򣩻� S���ϰ���
  char 	    ew;                 //���Ȱ��� E���������� W��������
    
  //������Ϣ��GNGGA����л�ȡ
  unsigned char       satellite_used;     //���ڶ�λ����������  
}gps_info_struct;

extern gps_info_struct gps_tau1201;
extern unsigned char gps_tau1201_flag;

double  get_two_points_distance(double lat1, double lng1, double lat2, double lng2);
double  get_two_points_azimuth(double lat1, double lon1, double lat2, double lon2);
void    gps_uart_callback(void);
void    gps_init(void);
void 		gps_data_parse(void);



#endif


