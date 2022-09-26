/*
* Interrupt_Configuration.h
*
* Created: 6/25/2022 11:30:21 AM
*  Author: Abdulaziz
*/


#ifndef INTERRUPT_CONFIGURATION_H_
#define INTERRUPT_CONFIGURATION_H_

//#include "Interrupt_Address.h"
#include "CPU_Configuartion.h"

typedef enum
{
	Interrupt_Low = 0,
	Interrupt_High = 1,
	Interrupt_Falling = 2,
	Interrupt_Rising = 3
}Interrupt_Sense;

typedef enum
{
	Interrupt0 = 0,
	Interrupt1 = 1,
	Interrupt2 = 2
}Interrupt;

#endif /* INTERRUPT_CONFIGURATION_H_ */