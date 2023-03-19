#include "gps.h"

gps_info_struct gps_tau1201;
unsigned char gps_tau1201_buffer1[100];                                                 // ����ȡ������ת�Ƶ������飬Ȼ��ʼ�����������
unsigned char gps_tau1201_buffer2[100];                                                 // ���ڽ��ջ�����
unsigned char gps_tau1201_num;                                                          // ��ǰ�����ַ�����
unsigned char gps_tau1201_flag;                                                         // 1���ɼ���� 0��û�вɼ����


//-------------------------------------------------------------------------------------------------------------------
// @brief		��ȡָ��,���������
// @param		num             �ڼ�������
// @param		*str            �ַ���           
// @return		unsigned char           ��������       	
//-------------------------------------------------------------------------------------------------------------------
unsigned char get_parameter_index(unsigned char num, char *str)
{
	unsigned char
 i, j = 0;
  char* temp;
  unsigned char
 len = 0, len1;
    
  temp = strchr(str, '\n');
	if(((void *)0) != temp)
	{
		len = (unsigned long int)temp - (unsigned long int)str + 1;
	}

	for(i = 0;i < len;i ++)
	{
		if(str[i] == ',')
    {
      j++;
    }
		if(j == num)
		{
			len1 =  i + 1;	
			break;
		}
	}

	return len1;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		�����ַ���ת��Ϊint
// @param		*s              �ַ���
// @return		double          ������ֵ           			
//-------------------------------------------------------------------------------------------------------------------
int str_to_int(char *buf)
{
	int return_value = 0;
	int dat;
	char *str = buf;
	while(*str != '\0')
	{
		dat = *str - '0';
		return_value = return_value * 10 + dat;
		str ++;
	}
	return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		�����ַ�����һ��,֮ǰ������ת��Ϊint
// @param		*s              �ַ���
// @return		float           ������ֵ           		
//-------------------------------------------------------------------------------------------------------------------
int get_int_number(char *s)
{
	char buf[10];
	unsigned char
 i;
	int return_value;
	i = get_parameter_index(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	return_value = str_to_int(buf);
	return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		�����ַ���ת��Ϊdouble	
// @param		*s              �ַ���
// @return		double          ������ֵ           			
//-------------------------------------------------------------------------------------------------------------------
double str_to_double(char *buf)
{
	double return_value = 0;
	double dat;
	int integer = 1;
	char *str = buf;
  char negative_flag = 1;
	int i;
	
	if('-' == *str)
	{
			negative_flag = -1;
			str++;
	}
        
	while(*str != '\0')
	{
		dat = *str - '0';
		
		if('.' == *str)
		{
			integer = 0;
			i = 1;
		}
		else
		{
			if( integer == 1 )
			{
				return_value = return_value * 10 + dat;
			}
			else
			{
				return_value = return_value + dat / (10 * i);
				i = i * 10 ;
			}
		}
		str ++;
	}
	return return_value*negative_flag;
}
												
//-------------------------------------------------------------------------------------------------------------------
// @brief		�����ַ�����һ��,֮ǰ������ת��Ϊfloat
// @param		*s              �ַ���
// @return		float           ������ֵ           			
//-------------------------------------------------------------------------------------------------------------------
float get_float_number(char *s)
{
  unsigned char
 i;
	char buf[10];
	float return_value;
    
	i=get_parameter_index(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	return_value = (float)str_to_double(buf);
	return return_value;	
}


												
//-------------------------------------------------------------------------------------------------------------------
// @brief		�����ַ�����һ��,֮ǰ������ת��Ϊdouble	
// @param		*s              �ַ���
// @return		double          ������ֵ           				
//-------------------------------------------------------------------------------------------------------------------
double get_double_number(char *s)
{
  unsigned char
 i;
	char buf[10];
	double return_value;
    
	i = get_parameter_index(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	return_value = str_to_double(buf);
	return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		RMC������
// @param		*line	        ���յ��������Ϣ		
// @param		*gps            ��������������
// @return		unsigned char           1�������ɹ� 0�����������ⲻ�ܽ���			
//-------------------------------------------------------------------------------------------------------------------
unsigned char gps_gnrmc_parse(char *line, gps_info_struct *gps)
{
	unsigned char
 state;
    
  double  latitude; //����
  double  longitude;//γ��
    
	float lati_cent_tmp, lati_second_tmp;
	float long_cent_tmp, long_second_tmp;
	
	char *buf = line;
  unsigned char
 return_value = 0;

	state = buf[get_parameter_index(2, buf)];

	gps->state = 0;
	if (state == 'A')  //���������Ч�����������
	{
			return_value = 1;
			gps->state = 1;
			gps -> ns       = buf[get_parameter_index(4, buf)];
			gps -> ew       = buf[get_parameter_index(6, buf)];

			latitude   = get_double_number(&buf[get_parameter_index(3, buf)]);
			longitude  = get_double_number(&buf[get_parameter_index( 5, buf)]);

			gps->latitude_degree  = (int)latitude / 100;   //γ��ת��Ϊ�ȷ���
			lati_cent_tmp         = (latitude - gps->latitude_degree * 100);
			gps->latitude_cent    = (int)lati_cent_tmp;
			lati_second_tmp       = (lati_cent_tmp - gps->latitude_cent) * 10000;
			gps->latitude_second  = (int)lati_second_tmp;

			gps->longitude_degree = (int)longitude / 100;	//����ת��Ϊ�ȷ���
			long_cent_tmp         = (longitude - gps->longitude_degree * 100);
			gps->longitude_cent   = (int)long_cent_tmp;
			long_second_tmp       = (long_cent_tmp - gps->longitude_cent) * 10000;
			gps->longitude_second = (int)long_second_tmp;
			
			gps->latitude = gps->latitude_degree + (double)gps->latitude_cent/60 + (double)gps->latitude_second/600000;
			gps->longitude = gps->longitude_degree + (double)gps->longitude_cent/60 + (double)gps->longitude_second/600000;			
	}
	
	return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		GGA������
// @param		*line	        ���յ��������Ϣ		
// @param		*gps            ��������������
// @return		unsigned char           1�������ɹ� 0�����������ⲻ�ܽ���
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
unsigned char gps_gngga_parse(char *line, gps_info_struct *gps)
{
	unsigned char
 state;
	char *buf = line;
  unsigned char
 return_value = 0;

	state = buf[get_parameter_index(2, buf)];

	if (state != ',')
	{
			gps->satellite_used = get_int_number(&buf[get_parameter_index(7, buf)]);
			return_value = 1;
	}
	
	return return_value;
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		����ӵ�һ���㵽�ڶ�����ľ���
// @param		latitude1		��һ�����γ��
// @param		longitude1		��һ����ľ���
// @param		latitude2		�ڶ������γ��
// @param		longitude2		�ڶ�����ľ���
// @return		double          �����������
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
double get_two_points_distance(double latitude1, double longitude1, double latitude2, double longitude2)
{  
	const double EARTH_RADIUS = 6378137;//����뾶(��λ��m)
	double rad_latitude1;
	double rad_latitude2;
	double rad_longitude1;
	double rad_longitude2;
	double distance;
	double a;
	double b;
	
	rad_latitude1 = ANGLE_TO_RAD(latitude1);//���ݽǶȼ��㻡��
	rad_latitude2 = ANGLE_TO_RAD(latitude2);
	rad_longitude1 = ANGLE_TO_RAD(longitude1);
	rad_longitude2 = ANGLE_TO_RAD(longitude2);

	a = rad_latitude1 - rad_latitude2;
	b = rad_longitude1 - rad_longitude2;

	distance = 2 * asin(sqrt(pow(sin(a/2),2) + cos(rad_latitude1)*cos(rad_latitude2)*pow(sin(b/2),2)));//google maps����ʵ�ֵ��㷨
	distance = distance * EARTH_RADIUS;  

	return distance;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		����ӵ�һ���㵽�ڶ�����ķ�λ��
// @param		latitude1		��һ�����γ��
// @param		longitude1		��һ����ľ���
// @param		latitude2		�ڶ������γ��
// @param		longitude2		�ڶ�����ľ���
// @return		double          ���ط�λ�ǣ�0��360��
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
double get_two_points_azimuth(double latitude1, double longitude1, double latitude2, double longitude2)
{
	latitude1 = ANGLE_TO_RAD(latitude1);
	latitude2 = ANGLE_TO_RAD(latitude2);
	longitude1 = ANGLE_TO_RAD(longitude1);
	longitude2 = ANGLE_TO_RAD(longitude2);

	double x = sin(longitude2 - longitude1) * cos(latitude2);
	double y = cos(latitude1) * sin(latitude2) - sin(latitude1) * cos(latitude2) * cos(longitude2 - longitude1);
	double angle = RAD_TO_ANGLE(atan2(x,y));

	return angle>=0?angle:angle+360;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		����GPS����
// @param		void			
// @return		void          
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void gps_data_parse(void)
{
	if(0 == strncmp((char *)&gps_tau1201_buffer1[3], "RMC", 3))
	{
			gps_gnrmc_parse((char *)gps_tau1201_buffer1, &gps_tau1201);
	}
	
	else if(0 == strncmp((char *)&gps_tau1201_buffer1[3], "GGA", 3))
	{
			gps_gngga_parse((char *)gps_tau1201_buffer1, &gps_tau1201);
	}
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		GPS���ڻص�����
// @param		void			
// @return		void          
// @since		v1.0
// Sample usage:				�˺�����Ҫ�ڴ��ڽ����ж��ڽ��е���
//-------------------------------------------------------------------------------------------------------------------
void gps_uart_callback(void)
{
	unsigned char
 dat;
	
	uart_query(GPS_TAU1201_UART, &dat);
	if('$' == dat || ('$' != gps_tau1201_buffer2[0]))                           // ֡ͷУ��
	{
			gps_tau1201_num = 0;
	}
	gps_tau1201_buffer2[gps_tau1201_num ++] = dat;
	
	if('\n' == dat)
	{
			// �յ�һ�����
			gps_tau1201_buffer2[gps_tau1201_num] = 0;                               // ��ĩβ���\0
			gps_tau1201_num ++;
			// �������ݵ� gps_tau1201_buffer1
			memcpy(gps_tau1201_buffer1, gps_tau1201_buffer2, gps_tau1201_num);
			gps_tau1201_flag = 1;
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		GPS��ʼ��
// @param		void			
// @return		void          
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void gps_init(void)
{
	const unsigned char
 set_rate[]      = {0xF1, 0xD9, 0x06, 0x42, 0x14, 0x00, 0x00, 0x0A, 0x05, 0x00, 0x64, 0x00, 0x00, 0x00, 0x60, 0xEA, 0x00, 0x00, 0xD0, 0x07, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xB8, 0xED};
	const unsigned char
 open_gga[]      = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x00, 0x01, 0xFB, 0x10};
	const unsigned char
 open_rmc[]      = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x05, 0x01, 0x00, 0x1A};
	
	const unsigned char
 close_gll[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x01, 0x00, 0xFB, 0x11};
	const unsigned char
 close_gsa[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x02, 0x00, 0xFC, 0x13};
	const unsigned char
 close_grs[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x03, 0x00, 0xFD, 0x15};
	const unsigned char
 close_gsv[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x04, 0x00, 0xFE, 0x17};
	const unsigned char
 close_vtg[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x06, 0x00, 0x00, 0x1B};
	const unsigned char
 close_zda[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x07, 0x00, 0x01, 0x1D};
	const unsigned char
 close_gst[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x08, 0x00, 0x02, 0x1F};
	const unsigned char
 close_txt[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x40, 0x00, 0x3A, 0x8F};
	const unsigned char
 close_txt_ant[] = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x20, 0x00, 0x1A, 0x4F};
	
	systick_delay_ms(500);//�ȴ�GPS������ʼ��ʼ��
	uart_init(GPS_TAU1201_UART, 115200, GPS_TAU1201_RX, GPS_TAU1201_TX);

	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)set_rate, sizeof(set_rate));//����GPS��������Ϊ10hz����������ô������Ĭ��Ϊ1hz
	systick_delay_ms(200);
	
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)open_rmc, sizeof(open_rmc));//����rmc���
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)open_gga, sizeof(open_gga));//����gga���
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_gll, sizeof(close_gll));
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_gsa, sizeof(close_gsa));
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_grs, sizeof(close_grs));
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_gsv, sizeof(close_gsv));
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_vtg, sizeof(close_vtg));
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_zda, sizeof(close_zda));
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_gst, sizeof(close_gst));
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_txt, sizeof(close_txt));
	systick_delay_ms(50);
	uart_putbuff(GPS_TAU1201_UART, (unsigned char
 *)close_txt_ant, sizeof(close_txt_ant));
	systick_delay_ms(50);

	uart_rx_irq(GPS_TAU1201_UART, 1);
}
