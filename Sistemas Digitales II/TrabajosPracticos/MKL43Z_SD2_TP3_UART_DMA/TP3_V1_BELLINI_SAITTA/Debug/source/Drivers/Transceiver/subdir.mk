################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Drivers/Transceiver/transceiver_RS485_UART.c \
../source/Drivers/Transceiver/transceiver_uart_rs485.c 

C_DEPS += \
./source/Drivers/Transceiver/transceiver_RS485_UART.d \
./source/Drivers/Transceiver/transceiver_uart_rs485.d 

OBJS += \
./source/Drivers/Transceiver/transceiver_RS485_UART.o \
./source/Drivers/Transceiver/transceiver_uart_rs485.o 


# Each subdirectory must supply rules for building sources it contributes
source/Drivers/Transceiver/%.o: ../source/Drivers/Transceiver/%.c source/Drivers/Transceiver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL43Z256VLH4 -DCPU_MKL43Z256VLH4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\board" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\source" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\drivers" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\component\uart" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\component\serial_manager" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\utilities" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\component\lists" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\device" -I"C:\Users\valen\Documents\MCUXpressoIDE_11.9.0_2144\workspace\TP3_V1_BELLINI_SAITTA\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-Drivers-2f-Transceiver

clean-source-2f-Drivers-2f-Transceiver:
	-$(RM) ./source/Drivers/Transceiver/transceiver_RS485_UART.d ./source/Drivers/Transceiver/transceiver_RS485_UART.o ./source/Drivers/Transceiver/transceiver_uart_rs485.d ./source/Drivers/Transceiver/transceiver_uart_rs485.o

.PHONY: clean-source-2f-Drivers-2f-Transceiver

