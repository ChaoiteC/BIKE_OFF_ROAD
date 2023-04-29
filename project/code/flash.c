/*关于FLASH的若干函数 by 碳白*/

#include "zf_common_headfile.h"

void flash_init(void){
    int i;
    flash_erase_sector(63,3);
    for(i=0;i<8;i++){
        flash_buffer_clear();
        flash_union_buffer[i].float_type=(float)i;
    }
    flash_write_page_from_buffer(63,3);
}
