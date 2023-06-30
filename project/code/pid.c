/*这个文件及它的头文件用于完成PID的数学过程。PID变量请在各自文件中定义。*/
#include "zf_common_headfile.h"

/* 名字：PID_set
 * 功能：用于设定pid参数的函数
 * 参数：p,i,d,maxI,maxOut
 * 输出：无
 */
void PID_set(PID *pid,float p,float i,float d,float maxI,float maxOut){
    pid->kp=p;
    pid->ki=i;
    pid->kd=d;
    pid->maxIntegral=maxI;
    pid->maxOutput=maxOut;
}

/* 名字：PID_expect
 * 功能：设置PID期望
 * 参数：无
 * 输出：无
 */
void PID_expect(PID *pid,float e){
    pid->expect=e;
}

/* 名字：PID_Calc
 * 功能：进行一次pid计算
 * 参数：(pid结构体,反馈值)，计算结果放在pid结构体的output成员中
 * 输出：无
 */
void PID_calc(PID *pid,float feedback){

    //更新数据
    pid->lastError=pid->error;//将旧error存起来
    pid->error=pid->expect-feedback;//计算新error

    //计算微分
    float dout=(pid->error-pid->lastError)*pid->kd;

    //计算比例
    float pout=pid->error*pid->kp;

    //计算积分
    pid->integral+=pid->error*pid->ki;

    //积分限幅
    if(pid->integral > pid->maxIntegral){
        pid->integral=pid->maxIntegral;
    }
    else if(pid->integral < -pid->maxIntegral){
        pid->integral=-pid->maxIntegral;
    }

    //计算输出
    pid->output=pout+dout+pid->integral;
    
    //输出限幅
    if(pid->output > pid->maxOutput){
        pid->output=pid->maxOutput;
    }
    else if(pid->output < -pid->maxOutput){
        pid->output=-pid->maxOutput;
    }
}

//清除积分
void clear_integral(PID *pid){
    pid->integral = 0.0f;
}
