/*********************************************************************************************************************
* 项目： 越野单车比赛
* 队名：
* 学校：
* 作者： 润、碳白
* 日期： 2023.3.12
********************************************************************************************************************/

#include "zf_common_headfile.h"


int main(void){
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
    debug_init();                                                               // 初始化默认 Debug UART
    bike_init();
    menu();//进入人机交互页面
    //wait_to_strat();
    
    while(1){//发车主循环


    }
}
