################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../Alarm_program.c \
../Display_program.c \
../ErrorM_program.c \
../GPIO_program.c \
../Home_program.c \
../Keypad_prgram.c \
../LCDAnimation_program.c \
../LCD_program.c \
../LDR_program.c \
../Led_program.c \
../Login_program.c \
../PWM_program.c \
../Queue_program.c \
../TempS_program.c \
../Util_String_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./Alarm_program.o \
./Display_program.o \
./ErrorM_program.o \
./GPIO_program.o \
./Home_program.o \
./Keypad_prgram.o \
./LCDAnimation_program.o \
./LCD_program.o \
./LDR_program.o \
./Led_program.o \
./Login_program.o \
./PWM_program.o \
./Queue_program.o \
./TempS_program.o \
./Util_String_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./Alarm_program.d \
./Display_program.d \
./ErrorM_program.d \
./GPIO_program.d \
./Home_program.d \
./Keypad_prgram.d \
./LCDAnimation_program.d \
./LCD_program.d \
./LDR_program.d \
./Led_program.d \
./Login_program.d \
./PWM_program.d \
./Queue_program.d \
./TempS_program.d \
./Util_String_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


