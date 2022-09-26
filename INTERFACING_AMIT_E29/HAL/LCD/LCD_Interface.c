/*
* LCD_Interface.c
*
* Created: 8/21/2022 10:43:52 AM
*  Author: Abdulaziz
*/


#include "LCD_Private.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}
void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot
		
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}

void LCD_Initialization(void)
{
	//Initialize pins for control
	DIO_SetPin_Direction(LCD_CNTRL_PRT, LCD_RS, LCD_OUT);
	DIO_SetPin_Direction(LCD_CNTRL_PRT, LCD_RW, LCD_OUT);
	DIO_SetPin_Direction(LCD_CNTRL_PRT, LCD_EN, LCD_OUT);
	//Initialize pins for data
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D0, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D1, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D2, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D3, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D4, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D5, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D6, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D7, LCD_OUT);
	//Send sequence of commands
	LCD_Write_Command(0x33);
	LCD_Write_Command(0x32);
	LCD_Write_Command(0x28);//Choose 4-Bit mode
	LCD_Write_Command(0x01);//Clear Screen
	LCD_Write_Command(0x02);//Return Home 
	LCD_Write_Command(0x0C);//Display on, Cursor off
	LCD_Write_Command(0x06);//Shift writing to right
	_delay_ms(2);
}
void LCD_Write_Command(uint8_t command)
{
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_RS, LCD_LOW);//Select control register
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_RW, LCD_LOW);//Write on LCD
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_LOW);//Be sure that in low case
	//Send high nibble
	LCD_PRT = (command & 0xF0) | (LCD_PRT & 0x0F);
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_LOW);
	//Send low nibble
	LCD_PRT = ((command & 0x0F)<<4) | (LCD_PRT & 0x0F);
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_LOW);
	//Wait until LCD takes data
	_delay_ms(2);
}
void LCD_Write_Character(uint8_t character)
{
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_RS, LCD_HIGH);//Select data register
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_RW, LCD_LOW);//Write on LCD
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_LOW);//Be sure that in low case
	//Send high nibble
	LCD_PRT = (character & 0xF0) | (LCD_PRT & 0x0F);
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_LOW);
	//Send low nibble
	LCD_PRT = ((character & 0x0F)<<4) | (LCD_PRT & 0x0F);
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_LOW);
	//Wait until LCD takes data
	_delay_ms(2);
}
void LCD_Write_String(uint8_t* string)
{
	while (*string != '\0')
	{
		LCD_Write_Character(*string);
		_delay_ms(10);
		string++;
	}
}
void LCD_Write_Number(uint32_t number)
{
	uint8_t num[10];
	ltoa(number, (uint8_t*)num, 10);//Long To ASCII
	LCD_Write_String((uint8_t*)num);
}
void LCD_Write_Float_Number(fint32_t Fnumber)
{
	char num[10];
	ftoa(Fnumber, num, 3);//Float to ASCII
	LCD_Write_String((uint8_t*)num);
}
void LCD_Clear(void)
{
	LCD_Write_Command(0x01);
}
// "Ana O7bk"
void LCD_save_in_CGRAM(void)
{
	 LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
     
	 ///  SAVE Alph_hamza
	 LCD_Write_Character(0b00110);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B01110);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00100);
     ///  SAVE ba2
     LCD_Write_Character(0B00000);
     LCD_Write_Character(0B00000);
     LCD_Write_Character(0B00000);
     LCD_Write_Character(0B00000);
     LCD_Write_Character(0B00001);
     LCD_Write_Character(0B00001);
     LCD_Write_Character(0B11111);
     LCD_Write_Character(0B00100);

	 ///  SAVE kaph
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B01101);
	 LCD_Write_Character(0B01001);
	 LCD_Write_Character(0B11101);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B10001);
	 LCD_Write_Character(0B11111);
	 LCD_Write_Character(0B00000);
	 ///  SAVE  7a2
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B01110);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B11111);
	 LCD_Write_Character(0B00000);


 }
// "Ana g3an"
void LCD_save_in_CGRAM1(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE Alph_hamza
	LCD_Write_Character(0b00110);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	///  SAVE Alph
	LCD_Write_Character(0b00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00000);
	///  SAVE non
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  gem
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00100);
	///  SAVE  3en
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  non kbera
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);



} 
// "Ana s3ed"
void LCD_save_in_CGRAM2(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE Alph_hamza
	LCD_Write_Character(0b00110);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	///  SAVE Alph
	LCD_Write_Character(0b00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00000);
	///  SAVE non
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  sen
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  3en
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  ya2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B01010);
	///  SAVE  dal
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);



}
// "3aml gayed"
void LCD_save_in_CGRAM3(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE  3en
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	///  SAVE mem
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00000);
	///  SAVE  lam
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	
	///  SAVE  gem
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00100);

	///  SAVE  ya2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B01010);
	///  SAVE  dal
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
}	
// "shokran lak"
void LCD_save_in_CGRAM4(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE kaph
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B01101);
	LCD_Write_Character(0B01001);
	LCD_Write_Character(0B11101);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE lam
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  alph
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00000);

	///  SAVE  Ra2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01111);
	LCD_Write_Character(0B10000);

	
	///  SAVE  khaf
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B10000);
	LCD_Write_Character(0B01000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);

	
	///  SAVE  shen
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01010);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  Ra2 2
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);


}
// "ma haza"
void LCD_save_in_CGRAM5(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	
	///  SAVE ?
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B10000);
	LCD_Write_Character(0B10000);
	LCD_Write_Character(0B01000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	///  SAVE  alph 2
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00000);
	///  SAVE  zal
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	
	///  SAVE  ha2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  alph
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00000);
	///  SAVE mem
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B01110);
}
// "kayf 7alak"
void LCD_save_in_CGRAM6(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
		
		///  SAVE ?
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B10000);
	LCD_Write_Character(0B10000);
	LCD_Write_Character(0B01000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	///  SAVE kaph
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B01101);
	LCD_Write_Character(0B01001);
	LCD_Write_Character(0B11101);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE lam
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	
	///  SAVE  alph
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00000);
	///  SAVE  7a2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  fa2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B10111);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  ya2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B01010);
    ///  SAVE  khaf
    LCD_Write_Character(0B00000);
    LCD_Write_Character(0B11111);
    LCD_Write_Character(0B10000);
    LCD_Write_Character(0B01000);
    LCD_Write_Character(0B00100);
    LCD_Write_Character(0B00010);
    LCD_Write_Character(0B11111);
    LCD_Write_Character(0B00000);
	
}
// "Ayn tazhab"
void LCD_save_in_CGRAM7(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE ?
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B10000);
	LCD_Write_Character(0B10000);
	LCD_Write_Character(0B01000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	///  SAVE ba2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B10010);
	LCD_Write_Character(0B10010);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00100);
	///  SAVE  ha2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	
	///  SAVE  zal
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE Ta2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01010);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  non kbera
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  ya2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B01010);
	LCD_Write_Character(0B00000);
    ///  SAVE Alph_hamza
	LCD_Write_Character(0b00110);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	
}
// "Haza_Raheb"
void LCD_save_in_CGRAM8(void)
{
    LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	///  SAVE  !
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	///  SAVE  ba2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00100);
	///  SAVE  ya2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B01010);
	///  SAVE  ha2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  Ra2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01000);
	
	///  SAVE  alph 2
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00000);
	///  SAVE  zal
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	
	///  SAVE  ha2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	
}
// "Ant"
void LCD_save_in_CGRAM9(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE Ta2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01010);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	
	///  SAVE non
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE Alph_hamza
	LCD_Write_Character(0b00110);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	

	
	

}
// "7kan_O7bak"
void LCD_save_in_CGRAM10(void)
{
LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
     
	 ///  SAVE kaph
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B01101);
	 LCD_Write_Character(0B01001);
	 LCD_Write_Character(0B11101);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B10001);
	 LCD_Write_Character(0B11111);
	 LCD_Write_Character(0B00000);
	  ///  SAVE ba2
	  LCD_Write_Character(0B00000);
	  LCD_Write_Character(0B00000);
	  LCD_Write_Character(0B00000);
	  LCD_Write_Character(0B00000);
	  LCD_Write_Character(0B00001);
	  LCD_Write_Character(0B00001);
	  LCD_Write_Character(0B11111);
	  LCD_Write_Character(0B00100);
	 ///  SAVE  7a2
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B01110);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B11111);
	 LCD_Write_Character(0B00000);
	 
	  ///  SAVE Alph_hamza
	  LCD_Write_Character(0b00110);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B01110);
	  LCD_Write_Character(0B00000);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00100);
	  
	  ///  SAVE  alph 2
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00100);
	  LCD_Write_Character(0B00111);
	  LCD_Write_Character(0B00000);
	  
	  ///  SAVE  KKaph
	  LCD_Write_Character(0B00000);
	  LCD_Write_Character(0B00000);
	  LCD_Write_Character(0B01010);
	  LCD_Write_Character(0B00000);
	  LCD_Write_Character(0B01110);
	  LCD_Write_Character(0B01010);
	  LCD_Write_Character(0B11111);
	  LCD_Write_Character(0B00000);
	  
	
}
// "Ana Orakbak"
void LCD_save_in_CGRAM11(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE kaph
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B01101);
	LCD_Write_Character(0B01001);
	LCD_Write_Character(0B11101);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE ba2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00100);
	///  SAVE kkaph
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00110);
	LCD_Write_Character(0B01111);
	LCD_Write_Character(0B01001);
	LCD_Write_Character(0B01111);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
		///  SAVE alph 2
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00000);
	///  SAVE  Ra2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01000);
	
	///  SAVE Alph
	LCD_Write_Character(0b00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00000);
	///  SAVE non
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE Alph_hamza
	LCD_Write_Character(0b00110);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	
	
}
// "Ana 7azen"
void LCD_save_in_CGRAM12(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE  dal
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B10001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	
	///  SAVE  ya2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B01010);
	///  SAVE  zal
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00011);
	LCD_Write_Character(0B00010);
	///  SAVE  7a2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE Alph
	LCD_Write_Character(0b00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00111);
	LCD_Write_Character(0B00000);
	///  SAVE non
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE Alph_hamza
	LCD_Write_Character(0b00110);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	///  SAVE  zal 2
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01000);
	LCD_Write_Character(0B10000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	
	
}
// "Ash3r t3bn"
void LCD_save_in_CGRAM13(void)
{
	LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	
	///  SAVE Alph
	LCD_Write_Character(0b00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00000);
	///  SAVE ba2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00100);
	///  SAVE  ta2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B10100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B11110);
	LCD_Write_Character(0B00000);

	///  SAVE  Ra2
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01111);
	LCD_Write_Character(0B10000);

	///  SAVE  Ra2 2
	LCD_Write_Character(0B00001);
	LCD_Write_Character(0B00010);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	///  SAVE  3en
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B01000);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
	///  SAVE  shen
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01010);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B10101);
	LCD_Write_Character(0B11111);
	LCD_Write_Character(0B00000);
    
	///  SAVE Alph_hamza
	LCD_Write_Character(0b00110);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B01110);
	LCD_Write_Character(0B00000);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	LCD_Write_Character(0B00100);
	
	
}
 // "Atf2 elnor"
 void LCD_save_in_CGRAM14(void)
 {
	 LCD_Write_Command(0b01000000);  //0x40   0b 0100 0000
	 

	 ///  SAVE  Ra2
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B00010);
	 LCD_Write_Character(0B00100);
	 ///  SAVE  waw
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00111);
	 LCD_Write_Character(0B00101);
	 LCD_Write_Character(0B00111);
	 LCD_Write_Character(0B00010);
	 LCD_Write_Character(0B00100);

	 ///  SAVE  Non
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B11111);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);

	 ///  SAVE  Lam
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B00001);
	 LCD_Write_Character(0B11111);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 ///  SAVE  Lam alph
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B01100);
	 LCD_Write_Character(0B01000);
	 LCD_Write_Character(0B11100);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B10001);
	 LCD_Write_Character(0B11111);
	 ///  SAVE  Fa2
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00000);
	 LCD_Write_Character(0B01110);
	 LCD_Write_Character(0B01010);
	 LCD_Write_Character(0B11111);
	 LCD_Write_Character(0B00000);
	 
	 ///  SAVE TTa2
	 LCD_Write_Character(0b00000);
	 LCD_Write_Character(0B00010);
	 LCD_Write_Character(0B00010);
	 LCD_Write_Character(0B00010);
	 LCD_Write_Character(0B01111);
	 LCD_Write_Character(0B01001);
	 LCD_Write_Character(0B11111);
	 LCD_Write_Character(0B00000);
	 ///  SAVE Alph
	 LCD_Write_Character(0b00100);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00100);
	 LCD_Write_Character(0B00000);
	 
	 
 }
 void LCD_vidGoTo(unsigned char col,unsigned char Row)
 {
	 if(col==0)
	 {
		 LCD_Write_Command(0b10000000|Row);
	 }

	 else if(col==1)
	 {
		 LCD_Write_Command(0b11000000|Row);

	 }
}