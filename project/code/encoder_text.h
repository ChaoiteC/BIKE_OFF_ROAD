/*
 * encoder_text.h
 *
 *  Created on: 2023��4��6��
 *      Author: 86152
 */

#ifndef ENCODER_TEXT_H_
#define ENCODER_TEXT_H_

#define PIT_CH_Encoder                          (TIM3_PIT )                     // ʹ�õ������жϱ�� ����޸� ��Ҫͬ����Ӧ�޸������жϱ���� isr.c �еĵ���
#define PIT_PRIORITY_Encoder                    (TIM3_IRQn)                     // ��Ӧ�����жϵ��жϱ��

#define ENCODER_QUADDEC                 (TIM1_ENCOEDER)                         // ������������Ӧʹ�õı������ӿ� ����ʹ��QTIMER1��ENCOEDER1
#define ENCODER_QUADDEC_A               (TIM1_ENCOEDER_MAP3_CH1_E9)             // A ���Ӧ������
#define ENCODER_QUADDEC_B               (TIM1_ENCOEDER_MAP3_CH2_E11)            // B ���Ӧ������

typedef struct
{

    float LastP;
    float Now_P;
    float out;
    float Kg;
    float Q;
    float R;
}kalman_param;


void Encoder_text_init();

void Encoder_kal_init_son(kalman_param *Encoder_kal);

int kalman_filter(kalman_param *Encoder_kal, int input);

extern kalman_param Encoder_kal;


#endif /* ENCODER_TEXT_H_ */
