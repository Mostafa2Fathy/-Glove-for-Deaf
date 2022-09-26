/*
 * BTN0_Configuration.h
 *
 * Created: 6/24/2022 10:15:52 AM
 *  Author: Abdulaziz
 */ 


#ifndef BTN0_CONFIGURATION_H_
#define BTN0_CONFIGURATION_H_

#include "CPU_Configuartion.h"

#define BTN0         DIO_PIN0
#define BTN0_PRt     DIO_PORTB

#define BTN0_INP     DIO_INPUT

#define BTN0_Press   DIO_LOW
#define BTN0_NPress  DIO_HIGH


#endif /* BTN0_CONFIGURATION_H_ */