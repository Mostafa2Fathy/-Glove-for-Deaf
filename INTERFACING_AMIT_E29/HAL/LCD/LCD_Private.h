/*
 * LCD_Private.h
 *
 * Created: 8/21/2022 10:43:43 AM
 *  Author: Abdulaziz
 */ 


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#include "LCD_Configuration.h"

void LCD_Initialization(void);
void LCD_Write_Command(uint8_t command);
void LCD_Write_Character(uint8_t character);
void LCD_Write_String(uint8_t *string);
void LCD_Write_Number(uint32_t Number);
void LCD_Write_Float_Number(fint32_t Fnumber);
void LCD_Clear(void);
void LCD_save_in_CGRAM(void);
void LCD_save_in_CGRAM1(void);
void LCD_save_in_CGRAM3(void);
void LCD_save_in_CGRAM4(void);
void LCD_save_in_CGRAM5(void);
void LCD_save_in_CGRAM6(void);
void LCD_save_in_CGRAM7(void);
void LCD_save_in_CGRAM8(void);
void LCD_save_in_CGRAM9(void);
void LCD_save_in_CGRAM10(void);
void LCD_save_in_CGRAM11(void);
void LCD_save_in_CGRAM12(void);
void LCD_save_in_CGRAM13(void);
void LCD_save_in_CGRAM14(void);
void LCD_vidGoTo(unsigned char col,unsigned char Row);

#endif /* LCD_PRIVATE_H_ */