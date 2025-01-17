/*
 * MainApp.c
 *
 *  Created on: Mar 22, 2024
 *      Author: ENG. MICHAEL SAMIR SAWIRIS NAGUIB
 */
//########## START ########## START ########## START ########## START ########## START ########## START ########## START ########## START ##########
#include "LCD.h"
#include "GPIO.h"
#include "UART.h"
#include "KEYPAD.h"
#include "TIMER1.h"
#include <avr/interrupt.h>

//####################################### GLOBAL VARIABLES ########################################################################
static uint8 text=1;
static uint8 i   =0;                                                       //Iterator
uint32 Tickk=0;
uint32 g_tick=0;
Timer1_ConfigType TIM1={0,0,Fcpu_64,Normal_mode};
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

//################################################################################################
void CallBackTimer(void)
{
	g_tick++;
	if(g_tick==2)
	{
		Tickk++;
		g_tick=0;

	}
}
void Door_LockUnclock(Timer1_ConfigType *  ptr)
{
	TIMER1_INIT(ptr);
	UART_T(START);
	LCD_CLEAR();
	LCD_STR_R_C(0,0,"Door's Unlocking");
	LCD_moveCursor(1,0);
	while(Tickk<=15){
		LCD_moveCursor(1,0);		LCD_INT(Tickk); LCD_STR("  ");}


	//UART_T(START);
	LCD_CLEAR();
	LCD_STR_R_C(0,0,"Stopped");

	while(Tickk<=18){	LCD_moveCursor(1,0);		LCD_INT(Tickk); LCD_STR("  ");}
	//UART_T(START);

	LCD_CLEAR();
	LCD_STR_R_C(0,0,"Door's locking  ");
	while(Tickk<=33){	LCD_moveCursor(1,0);		LCD_INT(Tickk); LCD_STR("  ");}
	//UART_T(START);

	LCD_CLEAR();
	Tickk=0;g_tick=0;
	TIMER1_DeINIT();

}
void ErrorMessage(Timer1_ConfigType *  ptr)
{
	TIMER1_INIT(ptr);
	UART_T(START);
	LCD_CLEAR();
	LCD_STR_R_C(0,0,"ERROR_PASS");
	LCD_moveCursor(1,0);

	while(Tickk<=60){	LCD_moveCursor(1,0);		LCD_INT(Tickk); LCD_STR("  ");}
	//UART_T(START);

	LCD_CLEAR();
	Tickk=0;g_tick=0;
	TIMER1_DeINIT();

	text=0;


}

//###############################################################################
// Step One [ Create a System Password ]
//###############################################################################
static uint8 StepOne(void)
{
	volatile uint8 password;                                              //Entered Password From User (array from 5 numbers)
	volatile uint8 CheckEQ;                                               //Return Value from MC2 to check the Equality of two passwords[0 (NOT EQUAL) or 1 (EQUAL) ]
//DISPLAYING ON LCD TO ENTER THE PASSWORD TO BE CREATED
	LCD_CLEAR();
	_delay_ms(500);
	LCD_STR_R_C(0,0,"Please Enter the");
	LCD_STR_R_C(1,0,"Password:");
	LCD_moveCursor(1,11);
//RECIEVING FROM USER Through KEYPAD & SENDING FIRST PASSWORD THROUGH UART
	for(i=0;i<NO_PASSWORD;i++)
	{
		password=KEYPAD();
		LCD_STR("*");
		UART_T(password);
		_delay_ms(800);
	}
//DISPLAYING PRESS ON ANY KEY TO CONTINUE
	LCD_CLEAR();
	_delay_ms(500);
	LCD_STR_R_C(0,0,"Press on any key");
	LCD_STR_R_C(1,0,"to continue.");
	while(KEYPAD()<0);
//DISPLAYING ON LCD TO RE-ENTER THE PASSWORD TO BE CREATED
	LCD_CLEAR();
	_delay_ms(500);
	LCD_STR_R_C(0,0,"Plz Re-Enter the");
	LCD_STR_R_C(1,0,"Password:");
	LCD_moveCursor(1,11);
//RECIEVING FROM USER Through KEYPAD & SENDING FIRST PASSWORD THROUGH UART
	for(i=0;i<NO_PASSWORD;i++)
	{
		password=KEYPAD();
		LCD_STR("*");
		UART_T(password);
		_delay_ms(800);
	}
//DISPLAYING PRESS ON ANY KEY TO CONTINUE
	LCD_CLEAR();
	_delay_ms(500);
	LCD_STR_R_C(0,0,"Press on any key");
	LCD_STR_R_C(1,0,"to continue.");
	while(KEYPAD()<0);
//WAITING THE RESPONSE FROM MC2 TO CHECK EQUALITY
	CheckEQ=UART_R();             //1 -> EQUAL     // 0 -> NOT EQUAL
	return CheckEQ;
}
//###############################################################################
// Step Two [ Main Options ]
//###############################################################################
static uint8 StepTwo(void)
{
	volatile uint8 state;
//DISPLAYING + FOR OPEN DOOR    - CHANGE PASSWORD
	LCD_CLEAR();
	LCD_STR_R_C(0,0,"+ : Open Door   ");
	LCD_STR_R_C(1,0,"- : Change Pass ");
//WAITING RESPONSE FROM USER
	state=KEYPAD();
	if(state=='+')
	{
		return OPEN_DOOR;
	}
	else if (state=='-')
	{
		return CHANGE_PASSWORD;
	}
	else
	{
		return FAULT_RESPONSE;
	}
}
//###############################################################################
// Step Three [ User Entered (+) for Open the door  ]
//###############################################################################
static uint8 StepThree(void)
{
	volatile uint8 password;                                              //Entered Password From User (array from 5 numbers)
	static uint8 counter=1;                                               //Counter to count the wrong input password from user
	volatile uint8 CheckEQ;                                               //Return Value from MC2 to check the Equality of two passwords[0 (NOT EQUAL) or 1 (EQUAL) ]
//DISPLAYING ON LCD TO ENTER THE PASSWORD
	LCD_CLEAR();
	_delay_ms(500);
	LCD_STR_R_C(0,0,"Please enter the");
	LCD_STR_R_C(1,0,"password:");
	LCD_moveCursor(1,11);
//RECIEVING FROM USER Through KEYPAD & SENDING FIRST PASSWORD THROUGH UART
	for(i=0;i<NO_PASSWORD;i++)
	{
		password=KEYPAD();
		LCD_STR("*");
		UART_T(password);
		_delay_ms(800);
	}
//DISPLAYING PRESS ON ANY KEY TO CONTINUE
	LCD_CLEAR();
	_delay_ms(500);
	LCD_STR_R_C(0,0,"Press on any key");
	LCD_STR_R_C(1,0,"to continue.");
	while(KEYPAD()<0);
//WAITING THE RESPONSE FROM MC2 TO CHECK EQUALITY
	CheckEQ=UART_R();
//########################################################
	if(CheckEQ==EQUAL)                    //IN CASE OF EQUAL PASSWORDS
	{
		Door_LockUnclock(&TIM1);
		counter=1;

		return CheckEQ;
	}
	else
	{
		if (counter ==MAX_WRONG_PASS)
		{
			ErrorMessage(&TIM1);
			counter=1;
			return ERROR_PASS;
		}
		else
		{
			UART_T(START);
			counter++;
			LCD_CLEAR();
			LCD_STR_R_C(0,0,"Not the same");
			LCD_STR_R_C(1,0,"Try Again");_delay_ms(500);
			return NOTEQUAL;

		}
	}
}
//###############################################################################
// Step Four [ User Entered (-) for Change the password  ]
//###############################################################################
static uint8 StepFour(void)
{
	volatile uint8 password;                                              //Entered Password From User (array from 5 numbers)
	static uint8 counter=1;                                               //Counter to count the wrong input password from user
	volatile uint8 CheckEQ;                                               //Return Value from MC2 to check the Equality of two passwords[0 (NOT EQUAL) or 1 (EQUAL) ]
//DISPLAYING ON LCD TO ENTER THE PASSWORD
	LCD_CLEAR();
	_delay_ms(500);
	LCD_STR_R_C(0,0,"Please enter the");
	LCD_STR_R_C(1,0,"password:");
	LCD_moveCursor(1,11);
//RECIEVING FROM USER Through KEYPAD & SENDING FIRST PASSWORD THROUGH UART
	for(i=0;i<NO_PASSWORD;i++)
	{
		password=KEYPAD();
		LCD_STR("*");
		UART_T(password);
		_delay_ms(800);
	}
//DISPLAYING PRESS ON ANY KEY TO CONTINUE
	LCD_CLEAR();
	_delay_ms(500);
	LCD_STR_R_C(0,0,"Press on any key");
	LCD_STR_R_C(1,0,"to continue.");
	while(KEYPAD()<0);
//WAITING THE RESPONSE FROM MC2 TO CHECK EQUALITY
	CheckEQ=UART_R();
//########################################################
	if(CheckEQ==EQUAL)                    //IN CASE OF EQUAL PASSWORDS
	{
		counter=1;
		return CheckEQ;
	}
	else                                   //IN CASE OF NOT-EQUAL PASSWORDS
	{
		if (counter ==MAX_WRONG_PASS)
		{
			ErrorMessage(&TIM1);
			counter=1;
			return ERROR_PASS;
		}
		else
		{
			UART_T(START);
			counter++;
			LCD_CLEAR();
			LCD_STR_R_C(0,0,"Not the same");
			LCD_STR_R_C(1,0,"Try Again ");_delay_ms(500);
			return NOTEQUAL;
		}
	}

}
//######################## MAIN TASKS OF MC1 ##############################################################
static uint8 Tasks(volatile uint8 Startt)
{
	volatile uint8 Start=Startt;             //Check Start (If is it First start or not ) for disp/not disp HELLO on LCD
	volatile uint8 state;                    //RESPONSE FROM EACH STEP
	volatile uint8 St1;                      //Step One
	volatile uint8 St2;                      //Step Two

	if(Start==FIRST_TIME_START)
	{
//DISPLAYING HELLO ( FOR THE FIRST TIME APP. START ) #########################################################
		LCD_CLEAR();LCD_STR("_HELLO_");_delay_ms(500);
//STEP_ONE  ##################################################################################################
		St1=StepOne();
		while (St1==NOTEQUAL)
		{
			LCD_CLEAR();LCD_STR("Not the same.");_delay_ms(500);
			LCD_CLEAR();LCD_STR("Try Again.")   ;_delay_ms(500);
			St1=StepOne();
		}
	}
//############################################################################################################
	if(text==1)
	{LCD_CLEAR();LCD_STR("Accepted.");_delay_ms(500);}
	text=1;
//STEP_TWO  ##################################################################################################
	St2=StepTwo();
	while (St2==FAULT_RESPONSE){UART_T(FAULT_RESPONSE);St2=StepTwo();}
//STEP_THREE  ##################################################################################################
	if(St2==OPEN_DOOR)
	{
		UART_T(STEP_THREE);
		state= StepThree();
		while(state==NOTEQUAL){state=StepThree();}
	}
//STEP_FOUR   ##################################################################################################
	else if (St2==CHANGE_PASSWORD)
	{
		UART_T(STEP_FOUR);
		state= StepFour();
		while(state==NOTEQUAL){state=StepFour();}

	}
	return state;
}
//###########################################################################################################################
//######################################## MAIN PROGRAM #####################################################################
//###########################################################################################################################
int main()
{
	Timer1_setCallBack(CallBackTimer);

	SREG |= (1<<7);
//############### LOCAL VARIABLES ##########################################################################
	uint8 start=1;
	volatile uint8 state;                      //RESPONSE FROM EACH STEP
	UART_ConfigType UART1_M = {data_8,even,one_bit,Baud};
//############# INIT OF EACH PERIPHRALS ###################################################################
	UART_INIT(&UART1_M);
	LCD_INIT();
//############# MAIN LOOP ####################################################################################
	while(1)
	{

		state=Tasks(start);
		if(state==1){start=1;}
		else{start=0;}
	}
}
//########## END ########## END ########## END ########## END ########## END ########## END ########## END ########## END ##########


