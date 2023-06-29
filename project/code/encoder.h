#ifndef ENCODER_H_
#define ENCODER_H_

#define PIT_CH_Encoder                          (TIM3_PIT )                     // 使用的周期中断编号 如果修改 需要同步对应修改周期中断编号与 isr.c 中的调用
#define PIT_PRIORITY_Encoder                    (TIM3_IRQn)                     // 对应周期中断的中断编号

#define ENCODER_QUADDEC                 (TIM1_ENCOEDER)                         // 正交编码器对应使用的编码器接口 这里使用QTIMER1的ENCOEDER1
#define ENCODER_QUADDEC_A               (TIM1_ENCOEDER_MAP3_CH1_E9)             // A 相对应的引脚
#define ENCODER_QUADDEC_B               (TIM1_ENCOEDER_MAP3_CH2_E11)            // B 相对应的引脚

typedef struct
{

    float LastP;
    float Now_P;
    float out;
    float Kg;
    float Q;
    float R;
}kalman_param;


void encoder_init();

void Encoder_kal_init(kalman_param *Encoder_kal);

int kalman_filter(kalman_param *Encoder_kal, int input);


extern kalman_param Encoder_kal;

extern float encoder_data_quaddec;

#endif /* ENCODER_H_ */
