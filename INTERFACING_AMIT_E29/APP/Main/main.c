/*

* Created: 8/20/2022 10:49:57 AM
* Author : Abdulaziz
*/

#include "main.h"
#include "words.h"


int main(void)
{

	LCD_Initialization();
	LCD_Clear();
	        
			Uint16_t A=10,B=10,C=10;
			int A1=370,A2=480;
			int B1=100,B2=105;
			int C1=160,C2=165;
			
			while(1)
	  {
            
			ADC_Initialization(0);
			ADC_Read();   // 370 to 480
			A = ADC_Read();
			ADC_Initialization(2);
			ADC_Read();// 250 to 380
			B = ADC_Read();
			ADC_Initialization(3);
			ADC_Read();// 250 to 380
			C = ADC_Read();
			//External_Interrupt_Initialization(0,1);

			if ((A<A1) & (B<B1) & (C<C1))        //1 |||
			{ LCD_Clear();Ana_O7bak();  }
			else if((A<A1) & (B>B2) & (C>C2))    //2 |--
			{LCD_Clear();Ant();}
			else if((A<A1) & (B>B2) & (C<C1))    //3 |-|
			{LCD_Clear();ma_haza();}
			else if((A>A2) & (B<B1) & (C>C2))   //4  -|-
			{LCD_Clear();Hakan_O7bak();}	
			else if((A>A2) & (B>B2) & (C>C2))    //5 ---
			{LCD_Clear();Ash3r_t3bn();}
			else if((A>A1) & (B>B1) & (C>C1))   //6 ///
			{LCD_Clear();Haza_Raheb();}		
			else if((A>A2) & (B>B2) & (C<C1))   //7 --|
			{LCD_Clear();kayf_7alak();}	
			else if((A>A2) & (B<B1) & (C<C1))   //8 -||
			{LCD_Clear();shokran_lak();}	
			else if((A<A1) & (B>B1) & (C<C1))    //9 |/|
			{LCD_Clear();Aml_gayed();}
			else if((A>A2) & (B>B1) & (C>C2))   //10 -/-
			{LCD_Clear();Ayn_tazhab();}	
			else if((A<A1) & (B>B1) & (C>C1))    //11 |//
			{LCD_Clear();Ana_7azen();}	
			else if((A>A1) & (B>B1) & (C<C1))   //12 //|
			{LCD_Clear();Ana_g3an();}	
			else if((A>A1) & (B>B1) & (C>C2))    //13 //-
			{LCD_Clear();Ana_s3ed();}		
			else if((A>A2) & (B>B2) & (C>C1))   //14 --/
			{LCD_Clear();Atfa2_elnor();}
			else if((A<A1) & (B<B1) & (C<C1))    //15 ||-
			{LCD_Clear();Ana_Orakbak();
}		
				
			_delay_ms(1000);
			
				
		}
		
		
		_delay_ms(50);
		
	}
	
	




