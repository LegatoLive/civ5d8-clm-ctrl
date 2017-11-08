#include "stm32f10x.h"                  // Device header
#include "m6775t.h"
#include "main.h"
#include "rtc.h"
#include <stdio.h>

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);

uint16_t  i=0;
uint16_t	delay = 100;
uint32_t	timeCounter=0;
char text[8] = {""};
int main(void)
{
	M6775T_SPI_Init();
	if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }

	CleanLCD();
	//RAM3_bits24_31 = 0xff;
	while (1)
	{
		
		LCD_WriteText(" ну что ");
		LCD_WRITE(RAM1_bits0_7, RAM1_bits8_15, RAM1_bits16_23, RAM1_bits24_31, RAM1_bits32_39, RAM1_bits40_47, RAM1_bits48_55, RAM1_bits56_63, RAM1_bits64_71, RAM1_bits72_79, LATCH1);
		LCD_WRITE(RAM2_bits0_7, RAM2_bits8_15, RAM2_bits16_23, RAM2_bits24_31, RAM2_bits32_39, RAM2_bits40_47, RAM2_bits48_55, RAM2_bits56_63, RAM2_bits64_71, RAM2_bits72_79, LATCH2);
		LCD_WRITE(RAM3_bits0_7, RAM3_bits8_15, RAM3_bits16_23, RAM3_bits24_31, RAM3_bits32_39, RAM3_bits40_47, RAM3_bits48_55, RAM3_bits56_63, RAM3_bits64_71, RAM3_bits72_79, LATCH3);
		LCD_WRITE(RAM4_bits0_7, RAM4_bits8_15, RAM4_bits16_23, RAM4_bits24_31, RAM4_bits32_39, RAM4_bits40_47, RAM4_bits48_55, RAM4_bits56_63, RAM4_bits64_71, RAM4_bits72_79, LATCH4);
		Delay(1000);
		LCD_WriteText(" DRIVE2 ");
		LCD_WRITE(RAM1_bits0_7, RAM1_bits8_15, RAM1_bits16_23, RAM1_bits24_31, RAM1_bits32_39, RAM1_bits40_47, RAM1_bits48_55, RAM1_bits56_63, RAM1_bits64_71, RAM1_bits72_79, LATCH1);
		LCD_WRITE(RAM2_bits0_7, RAM2_bits8_15, RAM2_bits16_23, RAM2_bits24_31, RAM2_bits32_39, RAM2_bits40_47, RAM2_bits48_55, RAM2_bits56_63, RAM2_bits64_71, RAM2_bits72_79, LATCH2);
		LCD_WRITE(RAM3_bits0_7, RAM3_bits8_15, RAM3_bits16_23, RAM3_bits24_31, RAM3_bits32_39, RAM3_bits40_47, RAM3_bits48_55, RAM3_bits56_63, RAM3_bits64_71, RAM3_bits72_79, LATCH3);
		LCD_WRITE(RAM4_bits0_7, RAM4_bits8_15, RAM4_bits16_23, RAM4_bits24_31, RAM4_bits32_39, RAM4_bits40_47, RAM4_bits48_55, RAM4_bits56_63, RAM4_bits64_71, RAM4_bits72_79, LATCH4);
		Delay(1000);
		LCD_WriteText(" здоров ");
		LCD_WRITE(RAM1_bits0_7, RAM1_bits8_15, RAM1_bits16_23, RAM1_bits24_31, RAM1_bits32_39, RAM1_bits40_47, RAM1_bits48_55, RAM1_bits56_63, RAM1_bits64_71, RAM1_bits72_79, LATCH1);
		LCD_WRITE(RAM2_bits0_7, RAM2_bits8_15, RAM2_bits16_23, RAM2_bits24_31, RAM2_bits32_39, RAM2_bits40_47, RAM2_bits48_55, RAM2_bits56_63, RAM2_bits64_71, RAM2_bits72_79, LATCH2);
		LCD_WRITE(RAM3_bits0_7, RAM3_bits8_15, RAM3_bits16_23, RAM3_bits24_31, RAM3_bits32_39, RAM3_bits40_47, RAM3_bits48_55, RAM3_bits56_63, RAM3_bits64_71, RAM3_bits72_79, LATCH3);
		LCD_WRITE(RAM4_bits0_7, RAM4_bits8_15, RAM4_bits16_23, RAM4_bits24_31, RAM4_bits32_39, RAM4_bits40_47, RAM4_bits48_55, RAM4_bits56_63, RAM4_bits64_71, RAM4_bits72_79, LATCH4);
		Delay(1000);
		/*
		uint8_t temp,iTemp=32;
		while(iTemp<224)
		{
			for (uint8_t j=0; j<8; j++)
			{
				if (!(text[7]))
				{
					text[j] = iTemp;
				}
				else
				{
					if (j<7){temp = text[j+1];text[j] = temp;}
					if (j==7){text[7] = iTemp;}
				}
			if (text[7]==iTemp){iTemp++;}
			}
		
		LCD_WriteText(text);
		LCD_WRITE(RAM1_bits0_7, RAM1_bits8_15, RAM1_bits16_23, RAM1_bits24_31, RAM1_bits32_39, RAM1_bits40_47, RAM1_bits48_55, RAM1_bits56_63, RAM1_bits64_71, RAM1_bits72_79, LATCH1);
		LCD_WRITE(RAM2_bits0_7, RAM2_bits8_15, RAM2_bits16_23, RAM2_bits24_31, RAM2_bits32_39, RAM2_bits40_47, RAM2_bits48_55, RAM2_bits56_63, RAM2_bits64_71, RAM2_bits72_79, LATCH2);
		LCD_WRITE(RAM3_bits0_7, RAM3_bits8_15, RAM3_bits16_23, RAM3_bits24_31, RAM3_bits32_39, RAM3_bits40_47, RAM3_bits48_55, RAM3_bits56_63, RAM3_bits64_71, RAM3_bits72_79, LATCH3);
		LCD_WRITE(RAM4_bits0_7, RAM4_bits8_15, RAM4_bits16_23, RAM4_bits24_31, RAM4_bits32_39, RAM4_bits40_47, RAM4_bits48_55, RAM4_bits56_63, RAM4_bits64_71, RAM4_bits72_79, LATCH4);
		Delay(500);
		}*/
	}
}



void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

