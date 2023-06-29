#include "zf_common_headfile.h"

kalman_param Encoder_kal;

float encoder_data_quaddec;//编码器的值
/**********************************************************************************************/
/* 名字：Encoder_text_init
 * 功能：编码器初始化，同时打开中断
 * 参数：无
 * 输出：无
 */
void encoder_init(){
    Encoder_kal_init(&Encoder_kal);
    encoder_quad_init(ENCODER_QUADDEC, ENCODER_QUADDEC_A, ENCODER_QUADDEC_B);   // 初始化编码器模块与引脚 正交解码编码器模式
    pit_ms_init(PIT_CH_Encoder, 2);
    interrupt_set_priority(PIT_PRIORITY_Encoder, 0);
}

/**********************************************************************************************/
/* 名字：Encoder_kal_init
 * 功能：对卡尔曼滤波数据进行初始化
 * 参数：kalman_param型的结构体指针
 * 输出：无
 */
void Encoder_kal_init(kalman_param *Encoder_kal){
    Encoder_kal->LastP = 0.02;
    Encoder_kal->Now_P = 0;
    Encoder_kal->out   = 0;
    Encoder_kal->Kg    = 0;
    Encoder_kal->Q     = 0.001;
    Encoder_kal->R     = 0.543;
}

/**********************************************************************************************/
/* 名字：kalman_filter
 * 功能：对卡尔曼滤波数据进行运算
 * 参数：kalman_param型的结构体指针，输入值（编码器值）
 * 输出：滤波运算结果（整形）
 */
int kalman_filter(kalman_param *Encoder_kal, int input){
    Encoder_kal->Now_P = Encoder_kal->LastP + Encoder_kal->Q;
    Encoder_kal->Kg = Encoder_kal->Now_P / (Encoder_kal->Now_P + Encoder_kal->R);//卡尔曼增益方程差
    Encoder_kal->out = Encoder_kal->out + Encoder_kal->Kg * (input-Encoder_kal->out);//更新最优值方程
    Encoder_kal->LastP = (1-Encoder_kal->Kg) * Encoder_kal->Now_P;//更新协方差方程
    return Encoder_kal->out;
}
