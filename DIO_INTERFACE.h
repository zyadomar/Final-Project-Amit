/*
 * DIO_INTERFACE.h
 *
 *  Created on: 11 Sep 2021
 *      Author: Zyad_
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define PIN_INPUT 0
#define PIN_OUTPUT 1

#define LOW 0
#define HIGH 1

#define PORT_OUTPUT   255
#define PORT_INPUT     0

#define MSB_PINS   1
#define LSB_PINS   2


enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}PinNumber;

u8 DIO_u8SetPinDirection(u8 Copy_u8PinNumber,u8 Copy_u8PortName,u8 Copy_u8Direction);
u8 DIO_u8SetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortName,u8 Copy_u8Value);

u8 DIO_u8SetPortDirection(u8 Copy_u8PortName,u8 Copy_u8Direction);
u8 DIO_u8SetPortValue(u8 Copy_u8PortName,u8 Copy_u8Value);

u8 DIO_u8GetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortName,u8*PtrToValue);

void DIO_u8Set4MSB_BitsValue(u8 Copy_u8PortNumber,u8 Copy_u8PortValue);

#endif /* DIO_INTERFACE_H_ */
