################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/user/src/isr.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/user/src/main.c 

OBJS += \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

