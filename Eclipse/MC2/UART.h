/*
 * UART.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Admin
 */

#ifndef UART_H_
#define UART_H_


#include "avr/io.h" /* To use the UART Registers */
#include "MACROS.h" /* To use the macros like SET_BIT */
#include "STANDS.h"
#define Baud  9600

typedef enum
{
	data_5,data_6,data_7,data_8,data_9=7
}UART_BitData;

typedef enum
{
	disable,even=2,odd
}UART_Parity;

typedef enum
{
	one_bit,two_bit
} UART_StopBit;

volatile uint8 UART_BaudRate;

typedef struct {
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 volatile uint32 baudrate;
}UART_ConfigType;


void UART_INIT(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_T(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_R(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_T_STR(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_R_STR(uint8 *Str); // Receive until #




#endif /* UART_H_ */
