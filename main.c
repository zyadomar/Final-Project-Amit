/*
 * main.c
 *
 *  Created on: 25 Nov 2021
 *      Author: Zyad_
 */

#include"STD_TYPES.h"
#include"DIO_INTERFACE.h"
#include"TWI_INTERFACE.h"
#include"EEPROM_PRIVATE.h"
#include "ADC_INTERFACE.h"
#include"FP_INTERFACE.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/eeprom.h>

int main()
{
	u8 Flag_Heating_Mode=0;
	u8 Flag_Heater_ON=0;
	u8 Temps_Readings[10] = {60,0,0,0,0,0,0,0,0,0};
	u8 *i=&Temps_Readings[0];
	u8 j=0;
	u8 k=0;
	u8 PinState1;
	u8 PinState2;
	u8 PinState3;
	u8 DigitalValue=0;
	u8 AnalogValue=0;
	u8 Copy_u16DigitalValue=0;
	//u8 Local_ReceiveDataByte;
	//i = Local_ReceiveDataByte;

	DIO_u8SetPinDirection(PIN0,DIO_PORTB,PIN_INPUT); // B0: ON/OFF BUTTON
	DIO_u8SetPinDirection(PIN6,DIO_PORTD,PIN_INPUT); // B1: UP BUTTON
	DIO_u8SetPinDirection(PIN2,DIO_PORTD,PIN_INPUT); // B2: DOWN BUTTON

	DIO_u8SetPinDirection(PIN7,DIO_PORTC,PIN_OUTPUT); // LED1: LED (HEATING/COOLING)

	DIO_u8SetPinDirection(PIN4,DIO_PORTA,PIN_OUTPUT); // SETTING UP 7-SEGMENT HERE & NEXT 7 LINES
	DIO_u8SetPinDirection(PIN5,DIO_PORTA,PIN_OUTPUT);
	DIO_u8SetPinDirection(PIN6,DIO_PORTA,PIN_OUTPUT);
	DIO_u8SetPinDirection(PIN7,DIO_PORTA,PIN_OUTPUT);

	DIO_u8SetPinDirection(PIN1,DIO_PORTB,PIN_OUTPUT);
	DIO_u8SetPinDirection(PIN2,DIO_PORTB,PIN_OUTPUT);

	DIO_u8SetPinValue(PIN1,DIO_PORTB,HIGH);
	DIO_u8SetPinValue(PIN2,DIO_PORTB,HIGH);

	ADC_voidInit();

//	TWI_voidInitMaster(16);

	DIO_u8Set4MSB_BitsValue(DIO_PORTA,HIGH); // SHIFT PORTA BY 4 (7-SEGMENT)
	_delay_ms(1000);

	while(1)
	{
		ADC_voidStartConversion(1); 	// S1: TEMPRATURE SENSOR @ PORTA PIN1

		DigitalValue = ADC_u16ReadDigitalValue();
		if(DigitalValue != Copy_u16DigitalValue)
		{
			AnalogValue = (DigitalValue*5000)/1024;
			Copy_u16DigitalValue = DigitalValue;

			if(Avg_Calc(10,&Temps_Readings[0]) == 35)
			{
				Flag_Heater_ON = 1;
			}
			if(Avg_Calc(10,&Temps_Readings[0]) == 75)
			{
				Flag_Heater_ON = 0;
			}
			_delay_ms(100);
		}
// -----------------------------------------------------------------------------------------------
		if(DIO_u8GetPinValue(PIN6,DIO_PORTD,&PinState1)==1 && (AnalogValue>=35) && (AnalogValue<=75)) // UP B1
		{
			_delay_ms(50);

			if(DIO_u8GetPinValue(PIN6,DIO_PORTD,&PinState1)==1 && (AnalogValue>=Temps_Readings[0]) && (AnalogValue<=75))
			{
				Flag_Heating_Mode = 0; // Heating Mode ON
				if(j==0)
				{
					PORTA=(AnalogValue<<4);
					DIO_u8SetPinValue(PIN1,DIO_PORTB,LOW);
					DIO_u8SetPinValue(PIN2,DIO_PORTB,LOW);
					_delay_ms(1000);
					DIO_u8SetPinValue(PIN1,DIO_PORTB,HIGH);
					DIO_u8SetPinValue(PIN2,DIO_PORTB,HIGH);
					_delay_ms(1000);
					j++;
				}
				if(Flag_Heating_Mode==0 && j>=1)
				{
					DIO_u8SetPinValue(PIN7,DIO_PORTC,HIGH);
					_delay_ms(1000);
					DIO_u8SetPinValue(PIN7,DIO_PORTC,LOW);
				    _delay_ms(1000);
					AnalogValue+=5;

					eeprom_write_word((unsigned int*)&Temps_Readings[*i], AnalogValue);
				//	EEPROM_voidSendDataByte(AnalogValue,0,i);
				//	Local_ReceiveDataByte = EEPROM_u8ReadDataByte(0,i);
				//	EEPROM_voidSendDataByte(Local_ReceiveDataByte,0,i+1);
				}
			}
		}
// -----------------------------------------------------------------------------------------------
		if(DIO_u8GetPinValue(PIN2,DIO_PORTD,&PinState2)==1 && (AnalogValue>=Temps_Readings[0]) && (AnalogValue>=35)) // DOWN B2
		{
			_delay_ms(50);

			if(DIO_u8GetPinValue(PIN2,DIO_PORTD,&PinState2)==1 && (AnalogValue>=Temps_Readings[0]) && (AnalogValue>=35))
			{
				Flag_Heating_Mode = 1; // Cooling Mode ON
				if(j==0)
				{
					PORTA=(AnalogValue<<4);
					DIO_u8SetPinValue(PIN1,DIO_PORTB,LOW);
					DIO_u8SetPinValue(PIN2,DIO_PORTB,LOW);
					_delay_ms(1000);
					DIO_u8SetPinValue(PIN1,DIO_PORTB,HIGH);
					DIO_u8SetPinValue(PIN2,DIO_PORTB,HIGH);
					j++;
				}
				if(Flag_Heating_Mode==1 && j>=1)
				{
					DIO_u8SetPinValue(PIN7,DIO_PORTC,HIGH);
					_delay_ms(1000);
					AnalogValue-=5;

					eeprom_write_word((unsigned int*)&Temps_Readings[*i], AnalogValue);
					//	EEPROM_voidSendDataByte(AnalogValue,0,i);
					//	Local_ReceiveDataByte = EEPROM_u8ReadDataByte(0,i);
					//	EEPROM_voidSendDataByte(Local_ReceiveDataByte,0,i+1);
				}
			}
		}
// -----------------------------------------------------------------------------------------------
		if(DIO_u8GetPinValue(PIN0,DIO_PORTB,&PinState3)==1) // ON/OFF B0
		{
			_delay_ms(50);

			if(DIO_u8GetPinValue(PIN0,DIO_PORTB,&PinState3)==1)
			{
				Flag_Heater_ON = 1;
				while(k<Temps_Readings[0])
				{
					k++;
				}
				PORTA=(k<<4);
				_delay_ms(1000);
			}
			else
			{
				Flag_Heater_ON = 0;
				DIO_u8SetPinValue(PIN1,DIO_PORTB,LOW);
				DIO_u8SetPinValue(PIN2,DIO_PORTB,LOW);
			}
		}
	}
	return 0;
}
