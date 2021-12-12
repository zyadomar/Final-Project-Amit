################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_PROGRAM.c \
../DIO_PROGRAM.c \
../EEPROM_PROGRAM.c \
../FP_PROGRAM.c \
../TWI_PROGRAM.c \
../main.c 

OBJS += \
./ADC_PROGRAM.o \
./DIO_PROGRAM.o \
./EEPROM_PROGRAM.o \
./FP_PROGRAM.o \
./TWI_PROGRAM.o \
./main.o 

C_DEPS += \
./ADC_PROGRAM.d \
./DIO_PROGRAM.d \
./EEPROM_PROGRAM.d \
./FP_PROGRAM.d \
./TWI_PROGRAM.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


