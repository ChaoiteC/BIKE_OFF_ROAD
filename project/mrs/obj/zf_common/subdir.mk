################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_clock.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_debug.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_fifo.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_font.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_function.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_interrupt.c 

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
zf_common/zf_common_clock.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

