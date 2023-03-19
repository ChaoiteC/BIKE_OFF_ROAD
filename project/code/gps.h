#ifndef __GPS_H
#define __GPS_H

//--------------------------------------------------------------------------------------------------
//��������
//--------------------------------------------------------------------------------------------------
#define GPS_TAU1201_UART    UART_3	
#define GPS_TAU1201_RX      UART3_TX_B10    // GPS RX�������ӵ���Ƭ����
#define GPS_TAU1201_TX      UART3_RX_B11    // GPS TX��������



#define ANGLE_TO_RAD(X)    (X * PI / 180.0)//�Ƕ�ת��Ϊ����
#define RAD_TO_ANGLE(X)    (X * 180.0 / PI)//����ת��Ϊ�Ƕ�
#define PI                  3.1415926535898


typedef struct{
    
  uint8       state;              //��Ч״̬  1����λ��Ч  0����λ��Ч
    
  uint16      latitude_degree;	//��
	uint16      latitude_cent;		//��
	uint16      latitude_second;    //��
	uint16      longitude_degree;	//��
	uint16      longitude_cent;		//��
	uint16      longitude_second;   //��
    
  double      latitude;           //����
  double      longitude;          //γ��
    
  int8 	    ns;                 //γ�Ȱ��� N�������򣩻� S���ϰ���
  int8 	    ew;                 //���Ȱ��� E���������� W��������
    
  //������Ϣ��GNGGA����л�ȡ
  uint8       satellite_used;     //���ڶ�λ����������  
}gps_info_struct;

extern gps_info_struct gps_tau1201;
extern uint8 gps_tau1201_flag;

double  get_two_points_distance(double lat1, double lng1, double lat2, double lng2);
double  get_two_points_azimuth(double lat1, double lon1, double lat2, double lon2);
void    gps_uart_callback(void);
void    gps_init(void);
void 		gps_data_parse(void);



#endif


