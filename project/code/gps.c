/*大都会　空に向かって　
  伸びていくビルに夕焼け
  駆け出せ　目を開け
  影　引き連れてゆけ
  ひとりじゃない
  
  这个文件及它的头文件用于完成与GPS相关的各个功能。*/

#include "zf_common_headfile.h"

int gps_point_number=0;//GPS点位数量
float gps_distance;//到下一点的距离
float gps_azimuth;//到下一点位的测量方位角
float gps_error_azimuth;//测量方位角与车行进航向角误差，正值向左偏航

GPS_POINT gps_point[GPS_POINT_DATA_MAX];//GPS点位数列

/* @fn point_flash_input
 * @brief 向FLASH缓冲区中写入点位数据
 * @param gps_data 单个点位
 * @param flash_number FLASH缓冲区行数
 * @return void
 * @notice FLASH数据需要另行I/O
 */
void point_flash_input(GPS_POINT* gps_data,uint8 flash_number){
    flash_union_buffer[0+3*flash_number].float_type=gps_data->latitude;
    flash_union_buffer[1+3*flash_number].float_type=gps_data->longitude;
    flash_union_buffer[2+3*flash_number].uint8_type=gps_data->point_type;
}

/* @fn point_flash_output
 * @brief 从FLASH缓冲区中读出点位数据到gps_data的对应行
 * @param gps_data 单个点位
 * @param flash_number FLASH缓冲区行数
 * @return void
 * @notice FLASH数据需要另行I/O
 */
void point_flash_output(GPS_POINT* gps_data,uint8 flash_number){
    gps_data->latitude=flash_union_buffer[0+3*flash_number].float_type;
    gps_data->longitude=flash_union_buffer[1+3*flash_number].float_type;
    gps_data->point_type=flash_union_buffer[2+3*flash_number].uint8_type;
}

/* @fn gps_line_write
 * @brief 向GPS点位数组的指定行写入数据
 * @param line 指定行
 * @param latitude 纬度
 * @param longitude 经度
 * @param point_type 点位类型
 * @return void
 */
void gps_line_write(int line,float latitude,float longitude,uint8 point_type){
    gps_point[line].latitude=latitude;
    gps_point[line].longitude=longitude;
    gps_point[line].point_type=point_type;
}

/* @fn gps_read_flash
 * @brief 从FLASH中读出点位数据
 * @param void
 * @return 0 mean yes, 1 mean error
 */
int gps_check_flash(void){
    int i;
    flash_buffer_clear();
    flash_read_page_to_buffer(GPS_POINT_DATA_SECTION_INDEX,GPS_POINT_DATA_PAGE_INDEX);
    for(i=0;i<gps_point_number;i++){
        point_flash_output(&gps_point[i],i);
        if(gps_point[i].point_type==POINT_TYPE_FINISH){
            return 0;
        }
    }
    return 1;
}

/* @fn gps_display_point_type
 * @brief 显示GPS点类型选择页面
 * @param point_type 当前选择的GPS点类型
 * @return void
 */
void gps_display_point_type(uint8_t point_type) {
    oled_clear();
    oled_show_chinese(0, 0, 16,(const uint8 *)POINT_TYPE,5);
    oled_show_string(0,3,"[UP]"                      );
    oled_show_string(0,5,"[DOWN]"                    );
    oled_show_string(0,7,"[COF]  [RVK]"              );
    switch(point_type){
        case STR   :oled_show_string(36,4,"STR---"            );break;
        case UPHELL:oled_show_string(36,4,"UPHELL"            );break;
        case TAR   :oled_show_string(36,4,"-TAR--"            );break;
        case RTT   :oled_show_string(36,4,"--RTT-"            );break;
        case SBD   :oled_show_string(36,4,"---SBD"            );break;
        case POINT_TYPE_FINISH:oled_show_string(36,4,"FINISH" );
    }
}



/* @fn gps_get_point_UI
 * @brief GPS取点的专门用户交互页面
 * @param void
 * @return 0 mean yes, 1 mean error
 * @notice 我超写那么紧密耦合鬼看得懂
 */
int gps_get_point_UI(void){
    int i=0,section=GPS_POINT_DATA_SECTION_INDEX,page=GPS_POINT_DATA_PAGE_INDEX;
    float latitude,longitude;
    int8 point_type=0;
    while(i<GPS_POINT_DATA_MAX){
        gps_display_point_type(point_type);
        key_scanner();
        system_delay_ms(50);
        if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
            if(--point_type<STR){
                point_type=POINT_TYPE_FINISH;
            }
        }
        else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
            if(++point_type>POINT_TYPE_FINISH){
                point_type=STR;
            }
        }
        else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
            if(--i<0){
                return 1;
            }
            else{
                gps_line_write(i,0.0,0.0,0);
            }
        }
        else if(KEY_SHORT_PRESS==key_get_state(KEY_CF)){
            gps_average_pointing(&latitude,&longitude);
            gps_line_write(i++,latitude,longitude,point_type);
            if(point_type==POINT_TYPE_FINISH){
                break;
            }
            else if(i>=GPS_POINT_DATA_MAX){
                return 1;
            }
        }
    }
    //这里将GPS数据逐个录入FLASH
    flash_buffer_clear();
    flash_erase_sector(section,page);
    for(;i<0;i--){
        point_flash_input(&gps_point[i],i);
    }
    flash_write_page_from_buffer(section,page);
    return 0;
}

/* @fn gps_average_pointing
 * @brief 获取GPS_OFFSET次GPS经纬度并取其平均值
 * @param *average_latitude 平均纬度
 * @param *average_longitude 平均经度
 * @return void
 */
void gps_average_pointing(int8* average_latitude,int8* average_longitude){
    double latitude_total=0;
    double longitude_total=0;
    int i=0;
    while(i<GPS_OFFSET){
        oled_clear();
        oled_show_string(0,0,"GPS GET POINT NOW");
        oled_show_int(0,1,i,2);
        oled_show_string(0,3,"WAITING GPS...");
        if(!gps_tau1201.state){
            oled_show_string(0,5,"GPS FAIL LOCATE");                //定位失败
            system_delay_ms(50);
        }
        else{
            oled_show_string(0,3, "               ");
            oled_show_string(0, 5, "N ->");
            oled_show_float(32,5,gps_tau1201.latitude,4,6);      //纬度
            oled_show_string(0, 6, "E ->");
            oled_show_float(32,6,gps_tau1201.longitude,4,6);     //经度
            oled_show_string(0, 7, "STL>");
            oled_show_int(32,7,gps_tau1201.satellite_used,2);    //卫星连接数量
            latitude_total+=gps_tau1201.latitude;
            longitude_total+=gps_tau1201.longitude;
            i++;
            system_delay_ms(1000);
        }
    }
    *average_latitude=latitude_total/GPS_OFFSET;
    *average_longitude=longitude_total/GPS_OFFSET;
}

/* @fn gps_show_point
 * @brief 在显示屏上显示GPS数组数据
 * @param void
 * @return void
 */
void gps_show_point(void){
    int i;
    flash_read_page_to_buffer(GPS_POINT_DATA_SECTION_INDEX,GPS_POINT_DATA_PAGE_INDEX);
    for(i=0;i<GPS_POINT_DATA_MAX;i++){
        oled_show_uint(0,0,i,2);
        oled_show_string(0, 4, "N ->");
        oled_show_float(32,4,gps_point[i].latitude,4,6);      //纬度
        oled_show_string(0, 5, "E ->");
        oled_show_float(32,5,gps_point[i].longitude,4,6);
        oled_show_string(0, 6, "TP->");
        switch(gps_point[i].point_type){
            case 1:oled_show_string(36,6,"STR---"            );break;
            case 2:oled_show_string(36,6,"UPHELL"            );break;
            case 3:oled_show_string(36,6,"-TAR--"            );break;
            case 4:oled_show_string(36,6,"--RTT-"            );break;
            case 5:oled_show_string(36,6,"---SBD"            );break;
            case 6:oled_show_string(36,6,"FINISH"            );
        }
        system_delay_ms(100);
        if(gps_point[i].point_type==POINT_TYPE_FINISH || i<GPS_POINT_DATA_MAX){
            return;
        }
    }
}

/* @fn gps_show_if
 * @brief 显示GPS接收的信息
 * @param void
 * @return 1=ERROR 0=OK
 */
int gps_show_if(void){
    if(!gps_tau1201.state){
        oled_show_string(0,4, "FAIL LOCATE");                //定位失败
        oled_show_string(0,6,"State lasts <2min."      );
        oled_show_string(0,7,"Indoor?Wiring bad?"      );
    }
    else{
        oled_show_string(0, 7, "TIM>");                      //时间
        oled_show_int(32,7,gps_tau1201.time.hour,2);
        oled_show_int(50,7,gps_tau1201.time.minute,2);
        oled_show_int(68,7,gps_tau1201.time.second,2);
        oled_show_string(0, 2, "N ->");
        oled_show_float(32,2,gps_tau1201.latitude,4,6);      //纬度
        oled_show_string(0, 3, "E ->");
        oled_show_float(32,3,gps_tau1201.longitude,4,6);     //经度
        oled_show_string(0, 4, "m/s>");
        oled_show_float(32,4,gps_tau1201.speed,4,6);         //速度
        oled_show_string(0, 5, "360>");
        oled_show_float(32,5,gps_tau1201.direction,4,6);     //方向
        oled_show_string(0, 6, "STL>");
        
    }
    oled_show_int(32,6,gps_tau1201.satellite_used,2);    //卫星连接数量
    if(gps_tau1201.satellite_used>=4){//4颗卫星及以上判定成功定位
        return 0;
    }
    else{
        return 1;
    }
}

/* @fn gps_read
 * @brief 定时器处理GPS数据
 * @param void
 * @return void
 */
void gps_read(){
    if(gps_data_parse()){
        return;
    }
    if(!gps_tau1201.state){
        return;//定位失败
    }
    else{
        gps_distance=get_two_points_distance(gps_tau1201.latitude,gps_tau1201.longitude,gps_point[current_gps_point].latitude,gps_point[current_gps_point].longitude);
        if(gps_distance<=EXPECTED_DISTANCE_THRESHOLD){//到点
            if(gps_point[current_gps_point++].point_type==POINT_TYPE_FINISH){//进入下一点位，如果已达终点
                stop_flag=1;
            }
        }
        gps_azimuth=get_two_points_azimuth(gps_tau1201.latitude,gps_tau1201.longitude,gps_point[current_gps_point].latitude,gps_point[current_gps_point].longitude);//测量方位角
        gps_error_azimuth=gps_tau1201.direction-gps_azimuth;//航向误差计算
        if(gps_error_azimuth<-180.0){
            gps_error_azimuth+=360.0;
        }
        else if(gps_error_azimuth>180.0){
            gps_error_azimuth-=360.0;
        }
    }
}

/*下面是GPS的卡尔曼滤波过程。*//*

double get_var(const double x_data[], const int x_size);//求方差函数
void gps_kalman();//滤波位gps
//gps_kalman所需参数
double gps_Rx = 0.7, gps_Ry = 0.7;//经纬度噪声
double gps_Qx = 0.5, gps_Qy = 0.5;//过程噪声
double gps_Px = 1.0, gps_Py = 1.0;//P矩阵，一般以1开始迭代
double k_gps_x = 0.0, k_gps_y = 0.0;//记录上一次最优估计
double z_gps_x = 0.0, z_gps_y = 0.0;//实际测量值
double gps_Kx = 0.0, gps_Ky = 0.0;//系数
double x_gps_x = 0.0, x_gps_y = 0.0;

//vel_kalman所需参数
double vel_Rx = 0.7, vel_Ry = 0.7;//经纬度噪声
double vel_Qx = 0.5, vel_Qy = 0.5;//过程噪声
double vel_Px = 1.0, vel_Py = 1.0;//P矩阵，一般以1开始迭代
double k_vx = 0.0, k_vy = 0.0;//记录上一次最优估计
double z_vx = 0.0, z_vy = 0.0;//实际测量值
double vel_Kx = 0.0, vel_Ky = 0.0;//系数
double x_vx = 0.0, x_vy = 0.0;//kalman预测速度
double v_gps_x = 0.0,v_gps_y = 0.0;//速度积分成位移

//acc
double ax = 0.0, ay = 0.0;
double a_vx = 0.0, a_vy = 0.0;//加速度积分成速度

//不同传感器调用周期
#define gps_dt 0.1;
#define vel_dt 0.01;
#define acc_dt 0.005;

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  get_gps()               
// 功能 :                  获取测量gps     
//////////////////////////////////////////////////////////////////////////////////////
void get_gps()
{
    z_gps_x=gps_tau1201.latitude;
    z_gps_y=gps_tau1201.longitude;
}

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  get_vel()               
// 功能 :                  获取测量速度vel  
//////////////////////////////////////////////////////////////////////////////////////
void get_vel()
{
    //TODO:将速度分量存入z_vx,z_vy
}

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  get_k_vel()               
// 功能 :                  取出kalman滤波后位移      
//////////////////////////////////////////////////////////////////////////////////////
void get_acc()
{
    //TODO:获得滤波后ax,ay
}

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  acc_integration()               
// 功能 :                  对加速度积分,调用频率为acc_dt     
//////////////////////////////////////////////////////////////////////////////////////
void acc_intergration()
{
    get_acc();
    a_vx += ax * acc_dt;
    a_vy += ay * acc_dt;
}

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  get_Bu_acc()               
// 功能 : 在vel_kalman调用时，调出加速度积分值（已经赋值给全局变量，使累加的积分归0，重新积分）  
//////////////////////////////////////////////////////////////////////////////////////
void get_Bu_acc()
{
    a_vx=0,a_vy=0;
}

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  vel_intergration()               
// 功能 :                  对速度积分,调用频率为vel_dt
//////////////////////////////////////////////////////////////////////////////////////
void vel_intergration()
{
    vel_kalman();
    v_gps_x += k_vx * vel_dt;
    v_gps_y += k_vy * vel_dt;
    //每调用一次kalman令v_gps_x=0,v_gps_y=0;
}

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  get_Bu_vel()               
// 功能 : 在gps_kalman调用时，调出度积分值（已经赋值给全局变量，使累加的积分归0，重新积分）
//////////////////////////////////////////////////////////////////////////////////////
void get_Bu_vel()
{
    v_gps_x=0,v_gps_y=0;
}

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  get_k_gps()               
// 功能 :                  取出kalman滤波后位移      
//////////////////////////////////////////////////////////////////////////////////////
void get_k_gps()
{
    //TODO:获得滤波后gps，k_gps_x,k_gps_y
}

//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  vel_kalman()                
// 功能 :                  
//////////////////////////////////////////////////////////////////////////////////////
void vel_kalman()
{
    //获取速度真实值
    get_vel();
    x_vx = k_vx + a_vx;
    x_vy = k_vy + a_vy;

    //更新a_vx,a_vy=0.0
    get_Bu_acc();

    vel_Px = vel_Px + vel_Qx;
    vel_Py = vel_Py + vel_Qy;

    //卡尔曼增益
    vel_Kx = vel_Px * 1. / (vel_Px + vel_Rx);
    vel_Ky = vel_Py * 1. / (vel_Py + vel_Ry);

    k_vx = x_vx + vel_Kx * (z_vx - x_vx);
    k_vy = x_vy + vel_Ky * (z_vy - x_vy);

    vel_Px = (1 - vel_Kx) * vel_Px;
    vel_Py = (1 - vel_Ky) * vel_Py;

}
//////////////////////////////////////////////////////////////////////////////////////
// 名称 :                  gps_kalman()                
// 功能 :                 
//////////////////////////////////////////////////////////////////////////////////////
void gps_kalman()
{
    get_gps();
    //预测
    x_gps_x = k_gps_x + v_gps_x;//加速度已通过动态的速度积分反应
    x_gps_y = k_gps_y + v_gps_y;

    //更新v_gps_x,v_gps_y=0.0
    get_Bu_vel();

    gps_Px = gps_Px + gps_Qx;
    gps_Py = gps_Py + gps_Qy;

    //卡尔曼增益
    gps_Kx = gps_Px * 1. / (gps_Px + gps_Rx);
    gps_Ky = gps_Py * 1. / (gps_Py + gps_Ry);

    k_gps_x = x_gps_x + gps_Kx * (z_gps_x - x_gps_x);
    k_gps_y = x_gps_y + gps_Ky * (z_gps_y - x_gps_y);

    gps_Px = (1 - gps_Kx) * gps_Px;
    gps_Py = (1 - gps_Ky) * gps_Py;

    //取出kalman滤波后的gps数据
    get_k_gps();

}
int main()
{
    while (1)
    {
        //调用频率根据自己模块的传感器定义
        //一般gps信号获取比速度慢，速度获取比加速度获取慢
        //代码实现思路
        //高频加速度数据积分，作为vel_kalman()输入矩阵，再将中频vel_kalman结果积分，作为gps_kalman()输入矩阵，最后返回准确的信号
        acc_intergration();//调用频率为acc_dt
        vel_intergration();//调用频率为vel_dt,在此函数里面调用vel_kalman
        gps_kalman();//调用频率为gps_dt
    }
}

double get_var(const double x_data[], const int x_size)
{
    double k;
    int n;
    double Ex;
    int b_k;
    double t;
    n = x_size;//数组长度
    if (x_size == 0) {
        k = 0;
    }
    else if (x_size == 1) {
        k = x_data[0];
    }
    else {
        Ex = x_data[0];
        for (b_k = 2; b_k <= n; b_k++) {
            Ex += x_data[b_k - 1];
        }

        Ex /= (double)x_size;
        k = 0.0;
        for (b_k = 1; b_k <= n; b_k++) {
            t = x_data[b_k - 1] - Ex;
            k += t * t;
        }
        k /= (double)x_size - 1.0;//sum((x-Ex)^2/n-1)
    }
    return k;
}


*/


