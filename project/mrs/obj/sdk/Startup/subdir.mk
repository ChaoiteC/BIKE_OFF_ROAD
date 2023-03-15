################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/sdk/Startup/startup_ch32v30x_D8C.S 

OBJS += \
./sdk/Startup/startup_ch32v30x_D8C.o 

S_UPPER_DEPS += \
./sdk/Startup/startup_ch32v30x_D8C.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Startup/startup_ch32v30x_D8C.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/libraries/sdk/Startup/startup_ch32v30x_D8C.S
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

