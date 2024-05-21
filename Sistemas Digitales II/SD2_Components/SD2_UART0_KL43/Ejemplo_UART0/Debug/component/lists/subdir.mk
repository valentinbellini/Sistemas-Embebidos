################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/lists/generic_list.c 

C_DEPS += \
./component/lists/generic_list.d 

OBJS += \
./component/lists/generic_list.o 


# Each subdirectory must supply rules for building sources it contributes
component/lists/%.o: ../component/lists/%.c component/lists/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL43Z256VLH4 -DCPU_MKL43Z256VLH4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\board" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\source" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\drivers" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\component\uart" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\component\serial_manager" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\utilities" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\component\lists" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\device" -I"C:\Users\guido\Documents\MCUXpressoIDE_11.6.1_8255\workspace\Docencia SD2\Ejemplo_UART0\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-lists

clean-component-2f-lists:
	-$(RM) ./component/lists/generic_list.d ./component/lists/generic_list.o

.PHONY: clean-component-2f-lists

