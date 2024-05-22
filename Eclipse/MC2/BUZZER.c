/*
 * BUZZER.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Admin
 */



/*connect to CONTROL ECU -> MCU2*/
#include "BUZZER.h"

static volatile uint8 BUZZER_PORT;
static volatile uint8 BUZZER_PIN;

void BUZZER_INIT(uint8 port,uint8 pin)
{
	BUZZER_PORT=port;
	BUZZER_PIN=pin;

	DDR(port,pin,OUTPUT);
	PORT(port,pin,OFF_BUZZER);
}

void BUZZER_ON(void)
{
	PORT(BUZZER_PORT,BUZZER_PIN,ON_BUZZER);
}

void BUZZER_OFF(void)
{
	PORT(BUZZER_PORT,BUZZER_PIN,OFF_BUZZER);
}
