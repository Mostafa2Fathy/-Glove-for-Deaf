/*
 * LCD_Configuration.h
 *
 * Created: 8/21/2022 10:43:32 AM
 *  Author: Abdulaziz
 */ 


#ifndef LCD_CONFIGURATION_H_
#define LCD_CONFIGURATION_H_

#include "CPU_Configuartion.h"

//Writing port
#define LCD_PRT PORTA
//Ports
#define LCD_CNTRL_PRT  DIO_PORTB
#define LCD_DATA_PRT   DIO_PORTA
//Control Pins
//#define LCD_v0   DIO_PIN1
#define LCD_RS   DIO_PIN1
#define LCD_RW   DIO_PIN2
#define LCD_EN   DIO_PIN3
//Data Pins
#define LCD_D0   DIO_PIN0
#define LCD_D1   DIO_PIN1
#define LCD_D2   DIO_PIN2
#define LCD_D3   DIO_PIN3
#define LCD_D4   DIO_PIN4
#define LCD_D5   DIO_PIN5
#define LCD_D6   DIO_PIN6
#define LCD_D7   DIO_PIN7
//Define State
#define LCD_INP DIO_INPUT
#define LCD_OUT DIO_OUTPUT
//Define Status
#define LCD_LOW  DIO_LOW
#define LCD_HIGH DIO_HIGH

#endif /* LCD_CONFIGURATION_H_ */