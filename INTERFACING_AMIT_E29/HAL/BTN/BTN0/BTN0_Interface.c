/*
 * BTN0_Interface.c
 *
 * Created: 6/24/2022 10:16:16 AM
 *  Author: Abdulaziz
 */ 

#include "BTN0_Private.h"

void BTN0_Initialization(void)
{
	DIO_SetPin_Direction(BTN0_PRt, BTN0, BTN0_INP);
}
uint8_t BTN0_Read(void)
{
	uint8_t val = 0;
	//#############################Way1#############################*******Delay
	_delay_ms(10);
	val = DIO_GetPin_Value(BTN0_PRt, BTN0);	
	//#############################Way3#############################*******High to low
	
	//#############################Way3#############################End
	return val;
}