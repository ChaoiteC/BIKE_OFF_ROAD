#ifndef MENU_H_
#define MENU_H_

#define KEY_UP KEY_1
#define KEY_DOWN KEY_2
#define KEY_RT KEY_4
#define KEY_CF KEY_3

void menu(void);

void page_error(void);
void first_page(void);
void page_MASTER_show();
void page_MASTER_ex();
void page_GET_POINT_show();
void page_GET_POINT_ex();
void page_TET_show();
void page_TET_ex();
void page_GPS_show();
void page_GPS_ex();
void page_MPU_show();
void page_MPU_ex();
void page_IMU_show();
void page_IMU_ex();
void page_BLE_show();
void page_BLE_ex();
void page_SEV_show();
void page_SEV_ex();
void page_ECD_show();
void page_ECD_ex();
void page_FLS_show();
void page_FLS_ex();
void page_PID_show();
void page_PID_ex();
void flash_data_update();

#endif /* MENU_H_ */
