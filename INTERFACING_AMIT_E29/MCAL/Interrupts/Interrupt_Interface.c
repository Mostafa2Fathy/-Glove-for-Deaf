/*
* Interrupt_Interface.c
*
* Created: 6/25/2022 11:30:53 AM
*  Author: Abdulaziz
*/

#include "Interrupt_Private.h"



void External_Interrupt_Initialization(Interrupt interrupt, Interrupt_Sense sense)
{
	// Disable global interrupt, while initialization only
	//CLR_BIT(SREG, 7);
	cli();
	//Choose interrupt
	switch (interrupt)
	{
		case Interrupt0:
		SET_BIT(GICR, INT0);
			//Choose sense
			switch (sense)
			{
				case Interrupt_Low:
				CLR_BIT(MCUCR, ISC01);CLR_BIT(MCUCR, ISC00); // 0   0
				break;
				case Interrupt_High:
				CLR_BIT(MCUCR, ISC01);SET_BIT(MCUCR, ISC00); // 0   1
				break;
				case Interrupt_Falling:
				SET_BIT(MCUCR, ISC01);CLR_BIT(MCUCR, ISC00); // 1   0
				break;
				case Interrupt_Rising:
				SET_BIT(MCUCR, ISC01);SET_BIT(MCUCR, ISC00); // 1   1
				break;
			}
		break;
		case Interrupt1:
		GICR |= (1<<INT1);
			//Choose sense
			switch (sense)
			{
				case Interrupt_Low:
				CLR_BIT(MCUCR, ISC11);CLR_BIT(MCUCR, ISC10); // 0   0
				break;
				case Interrupt_High:
				CLR_BIT(MCUCR, ISC11);SET_BIT(MCUCR, ISC10); // 0   1
				break;
				case Interrupt_Falling:
				SET_BIT(MCUCR, ISC11);CLR_BIT(MCUCR, ISC10); // 1   0
				break;
				case Interrupt_Rising:
				SET_BIT(MCUCR, ISC11);SET_BIT(MCUCR, ISC10); // 1   1
				break;
			}
		break;
		case Interrupt2:
		GICR |= 0x20;
		break;
	}
	// Enable global interrupt
	//SET_BIT(SREG, 7);
	sei();
}