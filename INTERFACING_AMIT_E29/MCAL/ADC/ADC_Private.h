/*
 * ADC_Private.h
 *
 * Created: 16-Sep-22 7:16:00 PM
 *  Author: Abdulaziz
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


#include "ADC_Configuration.h"

void ADC_Initialization(ADC_Chanel chanel);

uint16_t ADC_Read(void);


#endif /* ADC_PRIVATE_H_ */