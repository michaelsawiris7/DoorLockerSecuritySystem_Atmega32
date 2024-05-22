/*
 * UART.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Admin
 */




#include "UART.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
/*
 *
 *
 *
 *
 *
 */
void UART_INIT(const UART_ConfigType * Config_Ptr)
{
    	uint16 ubrrValue;

		/* U2X = 1 for double transmission speed */
		UCSRA = (1<<U2X);

		/************************** UCSRB Description **************************
		 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
		 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
		 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
		 * RXEN  = 1 Receiver Enable
		 * RXEN  = 1 Transmitter Enable
		 * UCSZ2 = 0 For 8-bit data mode
		 * RXB8 & TXB8 not used for 8-bit data mode
		 ***********************************************************************/
		UCSRB = (1<<RXEN) | (1<<TXEN);

		/************************** UCSRC Description **************************
		 * URSEL   = 1 The URSEL must be one when writing the UCSRC
		 * UMSEL   = 0 Asynchronous Operation
		 * UPM1:0  = 00 Disable parity bit
		 * USBS    = 0 One stop bit
		 * UCSZ1:0 = 11 For 8-bit data mode
		 * UCPOL   = 0 Used with the Synchronous operation only
		 ***********************************************************************/
		UCSRC = (1<<URSEL) ;
		UCSRC=(UCSRC&0xCF)|((  (Config_Ptr->parity  )<<UPM0 ) &0x30 );
		UCSRC=(UCSRC&0xF9)|((  (Config_Ptr->bit_data)<<UCSZ0) &0x06 );
		UCSRC=(UCSRC&0xF7)|((  (Config_Ptr->stop_bit)<<USBS ) &0x08 );
		ubrrValue = (uint16)(((F_CPU / ((Config_Ptr->baudrate) * 8))) - 1);


		/* Calculate the UBRR register value */
		//ubrr_value = (uint16)(((F_CPU / (baud_rate * 8UL))) - 1);

		/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/

		UBRRH = ubrrValue>>8;
		UBRRL = ubrrValue;



}
void UART_T(const uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}
uint8 UART_R(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
    return UDR;
}
void UART_T_STR(const uint8 *ptr)
{
	while(*ptr != '\0')
	{
		UART_T(*ptr);
		ptr++;
	}
}

void UART_R_STR(uint8 *ptr)
{
	*ptr = UART_R();
	while(*ptr != '#')
	{
		ptr++;
		*ptr = UART_R();
	}
	*ptr = '\0';
}
