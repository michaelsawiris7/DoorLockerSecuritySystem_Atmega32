/*
 * MainApp.c
 *
 *  Created on: Mar 22, 2024
 *      Author: ENG. MICHAEL SAMIR SAWIRIS
 */
//########## START ########## START ########## START ########## START ########## START ########## START ########## START ########## START ##########
#include "UART.h"
#include "GPIO.h"
#include "EEPROM.h"
#include "DC_MOTOR.h"
#include "BUZZER.h"
#include "TIMER1.h"
#include "LCD.h"
#include <avr/interrupt.h>
//####################################### GLOBAL VARIABLES ########################################################################
static uint8 text=1;
static uint8 k   =0;                                                       //Iterator
uint32 tickk=0;
uint32 g_tick=0;
Timer1_ConfigType TIM2={0,0,Fcpu_64,Normal_mode};
//####################################### TEXT REPLACEMENT #######################################################################
#define NO_PASSWORD 5                                                    //Maximum numbers of password
#define EQUAL (1u)
#define NOTEQUAL (0u)
#define OPEN_DOOR (1u)
#define CHANGE_PASSWORD (2u)
#define FAULT_RESPONSE (0u)
#define FIRST_TIME_START  (1u)
#define STEP_THREE 3
#define STEP_FOUR  4
#define START 8
#define ERROR_PASS 2
#define MAX_WRONG_PASS 3
//############################################################################################################
void CallBackTimer(void)
{
	g_tick++;
	if(g_tick==2)
	{
		tickk++;
		g_tick=0;

	}}
static void Door_LockUnclock(const Timer1_ConfigType *  ptr1)
{
	while(UART_R()!=START);
	TIMER1_INIT(ptr1);
	DC_MOTOR(m_on_cw,50);

	while(tickk<=15){		LCD_moveCursor(0,0);		LCD_INT(tickk); LCD_STR("  ");}

	//while(UART_R()!=START);

	DC_MOTOR(m_off,0);

	while(tickk<=18){		LCD_moveCursor(0,0);		LCD_INT(tickk); LCD_STR("  ");}
	//while(UART_R()!=START);

	DC_MOTOR(m_on_acw,50);
	//while(UART_R()!=START);

	while(tickk<=33){		LCD_moveCursor(0,0);		LCD_INT(tickk); LCD_STR("  ");}

	DC_MOTOR(m_off,0);
	LCD_CLEAR();
	TIMER1_DeINIT();
	tickk=0;


}
void ErrorMessage(const Timer1_ConfigType *  ptr1)
{

	while(UART_R()!=START);
	TIMER1_INIT(ptr1);

	BUZZER_ON();
	while(tickk<=60){		LCD_moveCursor(0,0);		LCD_INT(tickk); LCD_STR("  ");}
	LCD_CLEAR();

	//while(UART_R()!=START);

	BUZZER_OFF();
    TIMER1_DeINIT();
	tickk=0;
	text=0;
}

//###############################################################################
// Step One [ Create a System Password ]
//###############################################################################
static uint8 StepOne(void)
{
	volatile uint8 R_password[NO_PASSWORD];                           //Recieved First Entered Password From User (array from 5 numbers)
	volatile uint8 R_password2[NO_PASSWORD];                          //Recieved Re[Second] Entered Password From user for Confirmation
	volatile uint8 state;                                             //State of Equality of two passwords (1-> EQUAL , 0 -> NOTEUQAL)

// RECIEVING FIRST PASSWORD THROUGH UART
	for(k=0;k<NO_PASSWORD;k++)
	{
		R_password[k]=UART_R();
	}
// RECIEVING SECOND PASSWORD THROUGH UART
	for(k=0;k<NO_PASSWORD;k++)
	{
		R_password2[k]=UART_R();
	}
//COMPARING TWO PASSWORDS AND CHECK EQUALITY
	for(k=0;k<NO_PASSWORD;k++)
	{
		if(R_password[k]!=R_password2[k])
		{
			state=NOTEQUAL;
			UART_T(state);
			return state;
		}
	}
	for(k=0;k<NO_PASSWORD;k++)
		{
			EEPROM_writeByte((EEPROM_ADDRESS)+k,R_password[k]);
			_delay_ms(20);
		}
	state= EQUAL;
	UART_T(state);
	return state;
}


static uint8 StepThree(void)
{
	static uint8 counter=1;
	uint8 data=0;
	volatile  uint8 R_password[NO_PASSWORD];
	uint8 state=EQUAL;

	for(k=0;k<NO_PASSWORD;k++)
	{
		R_password[k]=UART_R();
	}

	for(k=0;k<NO_PASSWORD;k++)
	{
		EEPROM_readByte(EEPROM_ADDRESS+k,&data);
		if(R_password[k]!=data)
		{
			state=NOTEQUAL;
			break;
		}
	}

	if (state==EQUAL)
	{
		UART_T(EQUAL);
		Door_LockUnclock(&TIM2);
		counter=1;
		return state;

	}
	else
	{
		UART_T(NOTEQUAL);
		if (counter ==MAX_WRONG_PASS)
		{
			ErrorMessage(&TIM2);
			counter=1;

			return ERROR_PASS;
		}
		else
		{
			while(UART_R()!=START);
			counter++;
			return NOTEQUAL;

		}
	}
}

static uint8 StepFour(void)
{
	static uint8 counter=1;
	uint8 data=0;
	volatile  uint8 R_password[NO_PASSWORD];
	uint8 state=EQUAL;

	for(k=0;k<NO_PASSWORD;k++)
	{
		R_password[k]=UART_R();
	}

	for(k=0;k<NO_PASSWORD;k++)
	{
		EEPROM_readByte(EEPROM_ADDRESS+k,&data);
		if(R_password[k]!=data)
		{
			state=NOTEQUAL;
			break;
		}
	}


	if (state==EQUAL)
	{
		UART_T(EQUAL);
		counter=1;

		return state;

	}
	else
	{
		UART_T(NOTEQUAL);
		if (counter ==MAX_WRONG_PASS)
		{
			ErrorMessage(&TIM2);
			counter=1;

			return ERROR_PASS;
		}
		else
		{
			while(UART_R()!=START);
			counter++;
			return NOTEQUAL;
		}
	}

}
//######################## MAIN TASKS OF MC2 ##############################################################
static uint8 Tasks(uint8 Startt)
{
	uint8 Start=Startt;                      //Check Start (If is it First start or not ) for disp/not disp HELLO on LCD
	volatile uint8 state;                    //RESPONSE FROM EACH STEP
	volatile uint8 Step;                     //Step Three /Four
	volatile uint8 St1;                      //Step One
//STEP_ONE  ##################################################################################################
	if(Start==FIRST_TIME_START)
	{
		St1=StepOne();
		while (St1==NOTEQUAL){St1=StepOne();}
	}
//WAITING RESPONSE FROM MC1 TO SELECT THE NEXT STEP ( STEP THREE OR STEP FOUR )
	state=UART_R();
//#####################################################################################################
	while (state==FAULT_RESPONSE){state=UART_R();}
//STEP_THREE  ##################################################################################################
	if(state==STEP_THREE)
	{
		Step= StepThree();
		while(Step==NOTEQUAL){Step=StepThree();}


	}
//STEP_FOUR   ##################################################################################################
	else if (state==STEP_FOUR)
	{
		Step= StepFour();
		while(Step==NOTEQUAL){Step=StepFour();}

	}

	return Step;
}
//###########################################################################################################################
//######################################## MAIN PROGRAM #####################################################################
//###########################################################################################################################
int main()
{
	LCD_INIT();
	SREG |= (1<<7);
	UART_ConfigType UART1_S = {data_8,even,one_bit,Baud};
	Timer1_setCallBack(CallBackTimer);

	//I2C_ConfigType I2C_C= {A1,Fcpu_1};
	//I2C_INIT(&I2C_C);
//############### LOCAL VARIABLES ##########################################################################
	uint8 start=1;
	volatile uint8 state;                      //RESPONSE FROM EACH STEP
//############# INIT OF EACH PERIPHRAL ###################################################################
	UART_INIT(&UART1_S);
	TWI_init();
	DC_MOTOR_INIT();
	BUZZER_INIT(PA,P0);

//############# MAIN LOOP ####################################################################################
	while(1)
	{
		state=Tasks(start);
		if(state==1){start=1;}
		else{start=0;}
	}
}
//########## END ########## END ########## END ########## END ########## END ########## END ########## END ########## END ##########

