/*NewBing跟我说这是编码器的相关代码，但我几乎没有看懂。
 *反正先放在这里，有没有用将来再说。
 *顺便用chatGPT添加了注释，要是有用就好了。*/
#include "encoder.h"

void encoder_init(void)
{
    tim_counter_init(TIM_3, ENCODER_LSB); // 初始化定时器3，并配置为编码器模式
    gpio_init(B5, GPI, 0, GPI_PULL_UP); // 初始化引脚B5为输入模式，上拉输入
}

unsigned short int get_count(void)
{
    short int encoder_count = 0;
    encoder_count = tim_counter_get_count(TIM_3); // 获取定时器3计数器的计数值
    tim_counter_rst(TIM_3); // 重置定时器3计数器的计数值
    if(gpio_get(B5) == 0) // 如果引脚B5为低电平，说明编码器逆向旋转
    {
        encoder_count = -encoder_count; // 对计数值取反
    }
    return encoder_count; // 返回计数值
}

unsigned short int filter(void) 
{ 
    static unsigned short int value_buff[4]; // 静态数组用于存储计数值
    static unsigned short int i=0; // 静态变量用于记录当前存储位置
    unsigned short int count; 
    unsigned short int sum=0; // 计算平均值时的累加器
    value_buff[i++]=get_count(); // 将计数值存入数组
    if(i==4) 
        i=0; // 如果存储位置到达数组末尾，将位置重置为0
    for(count=0;count<4;count++)
    {
        sum+=value_buff[count]; // 对数组中的计数值进行累加
    }
    return sum/4; // 返回平均值
}














