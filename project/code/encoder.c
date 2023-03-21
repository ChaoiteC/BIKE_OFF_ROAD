/*NewBing����˵���Ǳ���������ش��룬���Ҽ���û�п�����
 *�����ȷ��������û���ý�����˵��
 *˳����chatGPT�����ע�ͣ�Ҫ�����þͺ��ˡ�*/
#include "encoder.h"

void encoder_init(void)
{
    tim_counter_init(TIM_3, ENCODER_LSB); // ��ʼ����ʱ��3��������Ϊ������ģʽ
    gpio_init(B5, GPI, 0, GPI_PULL_UP); // ��ʼ������B5Ϊ����ģʽ����������
}

unsigned short int get_count(void)
{
    short int encoder_count = 0;
    encoder_count = tim_counter_get_count(TIM_3); // ��ȡ��ʱ��3�������ļ���ֵ
    tim_counter_rst(TIM_3); // ���ö�ʱ��3�������ļ���ֵ
    if(gpio_get(B5) == 0) // �������B5Ϊ�͵�ƽ��˵��������������ת
    {
        encoder_count = -encoder_count; // �Լ���ֵȡ��
    }
    return encoder_count; // ���ؼ���ֵ
}

unsigned short int filter(void) 
{ 
    static unsigned short int value_buff[4]; // ��̬�������ڴ洢����ֵ
    static unsigned short int i=0; // ��̬�������ڼ�¼��ǰ�洢λ��
    unsigned short int count; 
    unsigned short int sum=0; // ����ƽ��ֵʱ���ۼ���
    value_buff[i++]=get_count(); // ������ֵ��������
    if(i==4) 
        i=0; // ����洢λ�õ�������ĩβ����λ������Ϊ0
    for(count=0;count<4;count++)
    {
        sum+=value_buff[count]; // �������еļ���ֵ�����ۼ�
    }
    return sum/4; // ����ƽ��ֵ
}














