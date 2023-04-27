/*
 * encoder_text.c
 *
 *  Created on: 2023��4��6��
 *      Author: 86152
 */
#include "zf_common_headfile.h"

kalman_param Encoder_kal;

/**********************************************************************************************/
/* ���֣�Encoder_text_init
 * ���ܣ���������ʼ����ͬʱ���ж�
 * ��������
 * �������
 */
void Encoder_text_init()
{

    Encoder_kal_init_son(&Encoder_kal);
    encoder_quad_init(ENCODER_QUADDEC, ENCODER_QUADDEC_A, ENCODER_QUADDEC_B);   // ��ʼ��������ģ�������� �������������ģʽ
    pit_ms_init(PIT_CH_Encoder, 100);
    interrupt_set_priority(PIT_PRIORITY_Encoder, 0);
}

/**********************************************************************************************/
/* ���֣�Encoder_kal_init_son
 * ���ܣ��Կ������˲����ݾ��г�ʼ��
 * ������kalman_param�͵Ľṹ��ָ��
 * �������
 */
void Encoder_kal_init_son(kalman_param *Encoder_kal)
{
    {
        Encoder_kal->LastP = 0.02;
        Encoder_kal->Now_P = 0;
        Encoder_kal->out   = 0;
        Encoder_kal->Kg    = 0;
        Encoder_kal->Q     = 0.001;
        Encoder_kal->R     = 0.543;
    }
}

/**********************************************************************************************/
/* ���֣�kalman_filter
 * ���ܣ��Կ������˲����ݾ�������
 * ������kalman_param�͵Ľṹ��ָ�룬����ֵ��������ֵ��
 * ������˲������������Σ�
 */
int kalman_filter(kalman_param *Encoder_kal, int input)
{

     Encoder_kal->Now_P = Encoder_kal->LastP + Encoder_kal->Q;
     //���������淽�̲�
     Encoder_kal->Kg = Encoder_kal->Now_P / (Encoder_kal->Now_P + Encoder_kal->R);
     //��������ֵ����
     Encoder_kal->out = Encoder_kal->out + Encoder_kal->Kg * (input-Encoder_kal->out);
     //����Э�����
     Encoder_kal->LastP = (1-Encoder_kal->Kg) * Encoder_kal->Now_P;

     return Encoder_kal->out;
}
