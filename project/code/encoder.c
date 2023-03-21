/*NewBing跟我说这是编码器的相关代码，但我几乎没有看懂。
 *反正先放在这里，有没有用将来再说。*/
#include "encoder.h"

void encoder_init(void)
{
	tim_counter_init(TIM_3,ENCODER_LSB);
	gpio_init(B5, GPI, 0, GPI_PULL_UP);
}

unsigned short int get_count(void)
{
	short int encoder_count = 0;
	encoder_count = tim_counter_get_count(TIM_3);
	tim_counter_rst(TIM_3);
	if(gpio_get(B5) == 0)
	{
		encoder_count = -encoder_count;
	}
	return encoder_count;
}


unsigned short int filter(void) 
{ 
	static unsigned short int value_buff[4]; 
	static unsigned short int i=0; 
	unsigned short int count; 
	unsigned short int sum=0; 
	value_buff[i++]=get_count(); 
	if(i==4) 
			i=0; 
	for(count=0;count<4;count++)
	{
			sum+=value_buff[count]; 
	}

	return sum/4; 
} 













