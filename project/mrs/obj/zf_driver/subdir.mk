################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_adc.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_delay.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_dvp.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_encoder.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_exti.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_flash.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_gpio.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_iic.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_pit.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_pwm.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_soft_iic.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_soft_spi.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_spi.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_timer.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_uart.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_usb_cdc.c 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_exti.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_iic.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_soft_spi.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_exti.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_iic.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_soft_spi.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_iic.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_spi.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_soft_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

