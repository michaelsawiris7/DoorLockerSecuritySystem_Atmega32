################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BUZZER.c \
../DC_MOTOR.c \
../EEPROM.c \
../GPIO.c \
../I2C.c \
../LCD.c \
../MainApp.c \
../TIMER1.c \
../UART.c 

OBJS += \
./BUZZER.o \
./DC_MOTOR.o \
./EEPROM.o \
./GPIO.o \
./I2C.o \
./LCD.o \
./MainApp.o \
./TIMER1.o \
./UART.o 

C_DEPS += \
./BUZZER.d \
./DC_MOTOR.d \
./EEPROM.d \
./GPIO.d \
./I2C.d \
./LCD.d \
./MainApp.d \
./TIMER1.d \
./UART.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O2 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


