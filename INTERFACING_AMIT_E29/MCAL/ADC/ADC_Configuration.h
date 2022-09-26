/*
 * ADC_Configuration.h
 *
 * Created: 16-Sep-22 7:15:09 PM
 *  Author: Abdulaziz
 */ 


#ifndef ADC_CONFIGURATION_H_
#define ADC_CONFIGURATION_H_

#include "CPU_Configuartion.h"
#include "ADC_Address.h"

typedef enum
{
	ADC0 = 0,
	ADC1 = 1,
	ADC2 = 2,
	ADC3 = 3,
	ADC4 = 4,
	ADC5 = 5,
	ADC6 = 6,
	ADC7 = 7
}ADC_Chanel;

typedef enum
{
	FreeRunning = 0,
	AnalogComparator = 1,
	ExternalInterrupt0 = 2
}ADC_Mode;


#define FREE_RUNNING_MODE 0

#define ADC_Mode FREE_RUNNING_MODE

#endif /* ADC_CONFIGURATION_H_ */