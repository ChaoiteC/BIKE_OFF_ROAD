################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/code/controller.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/code/imath.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/code/imu.c \
C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/code/pid.c 

OBJS += \
./code/controller.o \
./code/imath.o \
./code/imu.o \
./code/pid.o 

C_DEPS += \
./code/controller.d \
./code/imath.d \
./code/imu.d \
./code/pid.d 


# Each subdirectory must supply rules for building sources it contributes
code/controller.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/code/controller.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/imath.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/code/imath.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/imu.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/code/imu.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/pid.o: C:/Users/86152/Desktop/单车越野/我的/代码调试/Bicycle_Code/project/code/pid.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\Libraries\doc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Core" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Peripheral" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Startup" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\user\inc" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_common" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\project\code" -I"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

