/*
 * ADC_Interface.c
 *
 * Created: 16-Sep-22 7:12:09 PM
 *  Author: Abdulaziz
 */ 

#include "ADC_Private.h"
#include "DIO_Private.h"
void ADC_Initialization(ADC_Chanel chanel)
{
	//DDRA &= ~1;
	DIO_SetPin_Direction(DIO_PORTA,DIO_PIN0,DIO_INPUT);
	DIO_SetPin_Direction(DIO_PORTA,DIO_PIN2,DIO_INPUT);
	DIO_SetPin_Direction(DIO_PORTA,DIO_PIN3,DIO_INPUT);
	

	
	//Select Voltage reference
	CLR_BIT(ADMUX, REFS1);SET_BIT(ADMUX, REFS0);
	//Select Left or Right Adjust
	CLR_BIT(ADMUX, ADLAR);
	//Choose chanel
	CLR_BIT(ADMUX, MUX4);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX1);
	CLR_BIT(ADMUX, MUX0);
	
	/*
	1- Select voltage reference
	2- Select left or right adjust
	3- Select chanel (1)
	*/
	CLR_BIT(ADCSRA, 7);
	
	_delay_ms(500);

	switch(chanel)
	{
		case ADC0:
		ADMUX |= 0b01000000;//0x40
		break;
		case ADC1:
		ADMUX |= 0b01000001;//0x41
		break;
		case ADC2:
		ADMUX |= 0b01000010;//0x42
		break;
		case ADC3:
		ADMUX |= 0b01000011;//0x43
		break;
		case ADC4:
		ADMUX |= 0b01000100;//0x44
		break;
		case ADC5:
		ADMUX |= 0b01000101;//0x45
		break;
		case ADC6:
		ADMUX |= 0b01000110;//0x46
		break;
		case ADC7:
		ADMUX |= 0b01000111;//0x47
		break;
	}
		_delay_ms(500);
		SET_BIT(ADCSRA, 7);
		
	/*
	1- Auto trigger mode
	2- Select prescaler
	3- enable ADC
	*/
	ADCSRA |= 0b10100111;//0xA7
}

uint16_t ADC_Read(void)
{
	uint16_t data = 0;
	SET_BIT(ADCSRA, ADSC);
	while(GET_BIT(ADCSRA, ADIF) != 1);//wait until conversion finished
	data = ADC_DATA;
	return data;
}
