/*
 * GPIO.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Eng. Michael Samir Sawiris Naguib
 */

#ifndef GPIO_H_
#define GPIO_H_

#include<avr/io.h>
#include"STANDS.h"
#include"MACROS.h"


#define PA    0
#define PB    1
#define PC    2
#define PD    3

#define P0    0
#define P1    1
#define P2    2
#define P3    3
#define P4    4
#define P5    5
#define P6    6
#define P7    7
#define total 8


void  DDR(uint8 Port,uint8 Pin,uint8 State);
void  PORT (uint8 Port,uint8 Pin,uint8 data);
uint8 PIN  (uint8 Port,uint8 Pin);


#endif /* GPIO_H_ */
