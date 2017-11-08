/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "m6775t.h"
#include "m6775t_fonts.h"


/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_FullDuplex_SoftNSS
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t	RAM1_bits0_7, RAM1_bits8_15, RAM1_bits16_23, RAM1_bits24_31, RAM1_bits32_39, RAM1_bits40_47, RAM1_bits48_55, RAM1_bits56_63, RAM1_bits64_71, RAM1_bits72_79,
				RAM2_bits0_7, RAM2_bits8_15, RAM2_bits16_23, RAM2_bits24_31, RAM2_bits32_39, RAM2_bits40_47, RAM2_bits48_55, RAM2_bits56_63, RAM2_bits64_71, RAM2_bits72_79,
				RAM3_bits0_7, RAM3_bits8_15, RAM3_bits16_23, RAM3_bits24_31, RAM3_bits32_39, RAM3_bits40_47, RAM3_bits48_55, RAM3_bits56_63, RAM3_bits64_71, RAM3_bits72_79,
				RAM4_bits0_7, RAM4_bits8_15, RAM4_bits16_23, RAM4_bits24_31, RAM4_bits32_39, RAM4_bits40_47, RAM4_bits48_55, RAM4_bits56_63, RAM4_bits64_71, RAM4_bits72_79;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void M6775T_SPI_Init(void)
{
	SPI_InitTypeDef SPI_MASTER;
	GPIO_InitTypeDef GPIO_SPI;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);
	

	//----------------SPI1 Initialization Structure----------------------------
	SPI_I2S_DeInit(SPI1);
	SPI_StructInit(&SPI_MASTER);
	SPI_MASTER.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_MASTER.SPI_Mode = SPI_Mode_Master;
  SPI_MASTER.SPI_DataSize = SPI_DataSize_8b;
  SPI_MASTER.SPI_CPOL = SPI_CPOL_Low;
  SPI_MASTER.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_MASTER.SPI_NSS = SPI_NSS_Hard;
  SPI_MASTER.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
  SPI_MASTER.SPI_FirstBit = SPI_FirstBit_LSB;
  SPI_MASTER.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_MASTER);
	SPI_NSSInternalSoftwareConfig(SPI1, 0);
	SPI_SSOutputCmd(SPI1, ENABLE);
	
	//----------------GPIOA Initialization Structure----------------------------
  /* Configure SPI1 pins: SCK, MOSI and NSS---------------------------------*/
  /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
  GPIO_SPI.GPIO_Pin = SPI_MASTER_SCK | SPI_MASTER_MOSI;
  GPIO_SPI.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_SPI.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_SPI);
	
	GPIO_SPI.GPIO_Pin =  SPI_MASTER_NSS;
  GPIO_SPI.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_SPI.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA, &GPIO_SPI);
	SPI_Cmd(SPI1, ENABLE);
}

void LCD_WRITE(uint8_t pack0, uint8_t pack1, uint8_t pack2, uint8_t pack3, uint8_t pack4,
							 uint8_t pack5, uint8_t pack6, uint8_t pack7, uint8_t pack8, uint8_t pack9,
							 uint8_t latch)
{
	SPI1->DR = pack0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack1;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack2;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack3;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack4;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack5;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack6;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack7;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack8;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = pack9;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = latch;
	
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	GPIO_SetBits(GPIOA, SPI_MASTER_NSS);
	GPIO_ResetBits(GPIOA, SPI_MASTER_NSS);
}

void CleanLCD(void)
{
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI1->DR = 0xff;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	GPIO_SetBits(GPIOA, SPI_MASTER_NSS);
	GPIO_ResetBits(GPIOA, SPI_MASTER_NSS);
}

void getTime(uint32_t TimeVar, uint32_t THH, uint32_t TMM,uint32_t TSS)
{
	/* Считаем часы */
  THH = TimeVar / 3600;
  /* Считаем минуты */
  TMM = (TimeVar % 3600) / 60;
  /* Считаем секунды */
  TSS = (TimeVar % 3600) % 60;
}

void NumToTimeDigits(uint8_t THH, uint8_t TMM)
{
	/* Делим время на разряды */
	uint8_t time[4];
	time[2] = THH % 10;
  time[3] = (THH / 10) % 10;
  time[0] = TMM % 10;
  time[1] = (TMM / 10) % 10;
	/* ---------------------- */
	RAM1_bits0_7 |= 0x10;
	RAM1_bits0_7 &= ~0x2a;
	RAM2_bits0_7 &= ~0x7f;
	RAM3_bits0_7 &= ~0x7f;
	RAM4_bits0_7 &= ~0x7f;
	switch(time[0])
	{
		case(0):
			RAM1_bits0_7 |= 0x2;	RAM2_bits0_7 |= 0x3;	RAM3_bits0_7 |= 0x2;	RAM4_bits0_7 |= 0x3;	break;
		case(1):
			RAM2_bits0_7 |= 0x1;	RAM4_bits0_7 |= 0x1;
			break;
		case(2):
			RAM1_bits0_7 |= 0x2;	RAM2_bits0_7 |= 0x1;	RAM3_bits0_7 |= 0x3;	RAM4_bits0_7 |= 0x2;	break;
		case(3):
			RAM1_bits0_7 |= 0x2;	RAM2_bits0_7 |= 0x1;	RAM3_bits0_7 |= 0x1;	RAM4_bits0_7 |= 0x3;	break;
		case(4):
			RAM2_bits0_7 |= 0x3;	RAM3_bits0_7 |= 0x1;	RAM4_bits0_7 |= 0x1;	break;
		case(5):
			RAM1_bits0_7 |= 0x2;	RAM2_bits0_7 |= 0x2;	RAM3_bits0_7 |= 0x1;	RAM4_bits0_7 |= 0x3;	break;
		case(6):
			RAM1_bits0_7 |= 0x2;	RAM2_bits0_7 |= 0x2;	RAM3_bits0_7 |= 0x3;	RAM4_bits0_7 |= 0x3;	break;
		case(7):
			RAM1_bits0_7 |= 0x2;	RAM2_bits0_7 |= 0x1;	RAM4_bits0_7 |= 0x1;	break;
		case(8):
			RAM1_bits0_7 |= 0x2;	RAM2_bits0_7 |= 0x3;	RAM3_bits0_7 |= 0x3;	RAM4_bits0_7 |= 0x3;	break;
		case(9):
			RAM1_bits0_7 |= 0x2;	RAM2_bits0_7 |= 0x3;	RAM3_bits0_7 |= 0x1;	RAM4_bits0_7 |= 0x3;	break;
	}
	switch(time[1])
	{
		case(0):
			RAM1_bits0_7 |= 0x8;	RAM2_bits0_7 |= 0xc;	RAM3_bits0_7 |= 0x8;	RAM4_bits0_7 |= 0xc;	break;
		case(1):
			RAM2_bits0_7 |= 0x4;	RAM4_bits0_7 |= 0x4;	break;
		case(2):
			RAM1_bits0_7 |= 0x8;	RAM2_bits0_7 |= 0x4;	RAM3_bits0_7 |= 0xc;	RAM4_bits0_7 |= 0x8;	break;
		case(3):
			RAM1_bits0_7 |= 0x8;	RAM2_bits0_7 |= 0x4;	RAM3_bits0_7 |= 0x4;	RAM4_bits0_7 |= 0xc;	break;
		case(4):
			RAM2_bits0_7 |= 0xc;	RAM3_bits0_7 |= 0x4;	RAM4_bits0_7 |= 0x4;	break;
		case(5):
			RAM1_bits0_7 |= 0x8;	RAM2_bits0_7 |= 0x8;	RAM3_bits0_7 |= 0x4;	RAM4_bits0_7 |= 0xc;	break;
		case(6):
			RAM1_bits0_7 |= 0x8;	RAM2_bits0_7 |= 0x8;	RAM3_bits0_7 |= 0xc;	RAM4_bits0_7 |= 0xc;	break;
		case(7):
			RAM1_bits0_7 |= 0x8;	RAM2_bits0_7 |= 0x4;	RAM4_bits0_7 |= 0x4;	break;
		case(8):
			RAM1_bits0_7 |= 0x8;	RAM2_bits0_7 |= 0xc;	RAM3_bits0_7 |= 0xc;	RAM4_bits0_7 |= 0xc;	break;
		case(9):
			RAM1_bits0_7 |= 0x8;	RAM2_bits0_7 |= 0xc;	RAM3_bits0_7 |= 0x4;	RAM4_bits0_7 |= 0xc;	break;
	}
	switch(time[2])
	{
		case(0):
			RAM1_bits0_7 |= 0x8 << 2;	RAM2_bits0_7 |= 0xc << 2;	RAM3_bits0_7 |= 0x8 << 2;	RAM4_bits0_7 |= 0xc << 2;	break;
		case(1):
			RAM2_bits0_7 |= 0x4 << 2;	RAM4_bits0_7 |= 0x4 << 2;	break;
		case(2):
			RAM1_bits0_7 |= 0x8 << 2;	RAM2_bits0_7 |= 0x4 << 2;	RAM3_bits0_7 |= 0xc << 2;	RAM4_bits0_7 |= 0x8 << 2;	break;
		case(3):
			RAM1_bits0_7 |= 0x8 << 2;	RAM2_bits0_7 |= 0x4 << 2;	RAM3_bits0_7 |= 0x4 << 2;	RAM4_bits0_7 |= 0xc << 2;	break;
		case(4):
			RAM2_bits0_7 |= 0xc << 2;	RAM3_bits0_7 |= 0x4 << 2;	RAM4_bits0_7 |= 0x4 << 2;	break;
		case(5):
			RAM1_bits0_7 |= 0x8 << 2;	RAM2_bits0_7 |= 0x8 << 2;	RAM3_bits0_7 |= 0x4 << 2;	RAM4_bits0_7 |= 0xc << 2;	break;
		case(6):
			RAM1_bits0_7 |= 0x8 << 2;	RAM2_bits0_7 |= 0x8 << 2;	RAM3_bits0_7 |= 0xc << 2;	RAM4_bits0_7 |= 0xc << 2;	break;
		case(7):
			RAM1_bits0_7 |= 0x8 << 2;	RAM2_bits0_7 |= 0x4 << 2;	RAM4_bits0_7 |= 0x4 << 2;	break;
		case(8):
			RAM1_bits0_7 |= 0x8 << 2;	RAM2_bits0_7 |= 0xc << 2;	RAM3_bits0_7 |= 0xc << 2;	RAM4_bits0_7 |= 0xc << 2;	break;
		case(9):
			RAM1_bits0_7 |= 0x8 << 2;	RAM2_bits0_7 |= 0xc << 2;	RAM3_bits0_7 |= 0x4 << 2;	RAM4_bits0_7 |= 0xc << 2;	break;
	}
	switch(time[3])
	{
		case(1):
			RAM2_bits0_7 |= 0x40;	RAM4_bits0_7 |= 0x40;	break;
		case(2):
			RAM2_bits0_7 |= 0x40;	RAM3_bits0_7 |= 0x40;	break;
	}
}

uint32_t getChar(uint8_t SYMBOL)
{
	uint32_t symbol;
	if (SYMBOL<32)
	{
		return 32;
	}
	else
	{
		if (SYMBOL>127){SYMBOL -= 64;}
		SYMBOL -=  32;
		symbol = Font_19Seg[SYMBOL];
		return(symbol);
	}
}

void LCD_WriteText(char string[])
{
	uint32_t tempScaler=0x0;
	uint64_t tmpBufRAM1=0x0, tmpBufRAM2=0x0, tmpBufRAM3=0x0, tmpBufRAM4=0x0;
	//const uint64_t bufferMask=0x1;
	 
	for (uint8_t i=8; i>0; i--) // цикл создания буфера первой защёлки
	{
		//char SYMBOL = string[i];
		// Переменная буфера строки для защёлки
		// Алгоритм заплнения буфера
		// Присваиваем первые биты скалеру
		
		tempScaler = getChar(string[i-1]);
		
		// Пошло заполнение буфера для первой защёлки.

		tmpBufRAM1 <<= 1;
		tmpBufRAM2 <<= 1;
		tmpBufRAM3 <<= 1;
		tmpBufRAM4 <<= 1;
		if ((tempScaler>>14)&0x1){tmpBufRAM1 |= 0x1;}else{tmpBufRAM1 &= 0xfffffffffffffffe;} //Первая защёлка
		if ((tempScaler>>15)&0x1){tmpBufRAM2 |= 0x1;}else{tmpBufRAM2 &= 0xfffffffffffffffe;} //Вторая защёлка
		if ((tempScaler>>17)&0x1){tmpBufRAM3 |= 0x1;}else{tmpBufRAM3 &= 0xfffffffffffffffe;} //Третья защёлка
		if ((tempScaler>>18)&0x1){tmpBufRAM4 |= 0x1;}else{tmpBufRAM4 &= 0xfffffffffffffffe;} //Четвёртая защёлка
		tmpBufRAM1 <<= 1;
		tmpBufRAM2 <<= 1;
		tmpBufRAM3 <<= 1;
		tmpBufRAM4 <<= 1;
		if ((tempScaler>>9)&0x1){tmpBufRAM1 |= 0x1;}else{tmpBufRAM1 &= 0xfffffffffffffffe;}	//Первая защёлка
		if ((tempScaler>>13)&0x1){tmpBufRAM2 |= 0x1;}else{tmpBufRAM2 &= 0xfffffffffffffffe;} //Вторая защёлка
		if ((tempScaler>>12)&0x1){tmpBufRAM3 |= 0x1;}else{tmpBufRAM3 &= 0xfffffffffffffffe;} //Третья защёлка
		if ((tempScaler>>16)&0x1){tmpBufRAM4 |= 0x1;}else{tmpBufRAM4 &= 0xfffffffffffffffe;} //Четвёртая защёлка
		tmpBufRAM1 <<= 1;
		tmpBufRAM2 <<= 1;
		tmpBufRAM3 <<= 1;
		tmpBufRAM4 <<= 1;
		if ((tempScaler>>1)&0x1){tmpBufRAM1 |= 0x1;}else{tmpBufRAM1 &= 0xfffffffffffffffe;}	//Первая защёлка
		if ((tempScaler>>11)&0x1){tmpBufRAM2 |= 0x1;}else{tmpBufRAM2 &= 0xfffffffffffffffe;} //Вторая защёлка
		if ((tempScaler>>10)&0x1){tmpBufRAM3 |= 0x1;}else{tmpBufRAM3 &= 0xfffffffffffffffe;} //Третья защёлка
		if ((tempScaler>>6)&0x1){tmpBufRAM4 |= 0x1;}else{tmpBufRAM4 &= 0xfffffffffffffffe;} //Четвёртая защёлка
		tmpBufRAM1 <<= 1;
		tmpBufRAM2 <<= 1;
		tmpBufRAM3 <<= 1;
		tmpBufRAM4 <<= 1;
		if ((tempScaler)&0x1){tmpBufRAM1 |= 0x1;}else{tmpBufRAM1 &= 0xfffffffffffffffe;}	//Первая защёлка
		if ((tempScaler>>8)&0x1){tmpBufRAM2 |= 0x1;}else{tmpBufRAM2 &= 0xfffffffffffffffe;} //Вторая защёлка
		if ((tempScaler>>7)&0x1){tmpBufRAM3 |= 0x1;}else{tmpBufRAM3 &= 0xfffffffffffffffe;} //Третья защёлка
		if ((tempScaler>>5)&0x1){tmpBufRAM4 |= 0x1;}else{tmpBufRAM4 &= 0xfffffffffffffffe;} //Четвёртая защёлка
		tmpBufRAM2 <<= 1;
		tmpBufRAM3 <<= 1;
		tmpBufRAM4 <<= 1;
		if ((tempScaler>>2)&0x1){tmpBufRAM2 |= 0x1;}else{tmpBufRAM2 &= 0xfffffffffffffffe;} //Вторая защёлка
		if ((tempScaler>>3)&0x1){tmpBufRAM3 |= 0x1;}else{tmpBufRAM3 &= 0xfffffffffffffffe;} //Третья защёлка
		if ((tempScaler>>4)&0x1){tmpBufRAM4 |= 0x1;}else{tmpBufRAM4 &= 0xfffffffffffffffe;} //Четвёртая защёлка
	}
	// Заталкиваем данные буферов в переменную
	// Первый разряд
	if (tmpBufRAM1&0x1){RAM1_bits16_23 |= 0x04;}else{RAM1_bits16_23 &= 0xfb;}	tmpBufRAM1 >>= 1;//1-я защёлка A
	if (tmpBufRAM1&0x1){RAM1_bits16_23 |= 0x20;}else{RAM1_bits16_23 &= 0xdf;}	tmpBufRAM1 >>= 1;//1-я защёлка B1
	if (tmpBufRAM2&0x1){RAM2_bits16_23 |= 0x20;}else{RAM2_bits16_23 &= 0xdf;}	tmpBufRAM2 >>= 1;//2-я защёлка B2
	if (tmpBufRAM3&0x1){RAM3_bits16_23 |= 0x20;}else{RAM3_bits16_23 &= 0xdf;}	tmpBufRAM3 >>= 1;//3-я защёлка С1
	if (tmpBufRAM4&0x1){RAM4_bits16_23 |= 0x20;}else{RAM4_bits16_23 &= 0xdf;}	tmpBufRAM4 >>= 1;//4-я защёлка С2
	if (tmpBufRAM4&0x1){RAM4_bits16_23 |= 0x10;}else{RAM4_bits16_23 &= 0xef;}	tmpBufRAM4 >>= 1;//4-я защёлка D
	if (tmpBufRAM4&0x1){RAM4_bits16_23 |= 0x08;}else{RAM4_bits16_23 &= 0xf7;}	tmpBufRAM4 >>= 1;//4-я защёлка E1
	if (tmpBufRAM3&0x1){RAM3_bits16_23 |= 0x08;}else{RAM3_bits16_23 &= 0xf7;}	tmpBufRAM3 >>= 1;//3-я защёлка E2
	if (tmpBufRAM2&0x1){RAM2_bits16_23 |= 0x08;}else{RAM2_bits16_23 &= 0xf7;}	tmpBufRAM2 >>= 1;//2-я защёлка F1
	if (tmpBufRAM1&0x1){RAM1_bits16_23 |= 0x08;}else{RAM1_bits16_23 &= 0xf7;}	tmpBufRAM1 >>= 1;//1-я защёлка F2
	if (tmpBufRAM3&0x1){RAM3_bits16_23 |= 0x04;}else{RAM3_bits16_23 &= 0xfb;}	tmpBufRAM3 >>= 1;//3-я защёлка G1
	if (tmpBufRAM2&0x1){RAM2_bits16_23 |= 0x10;}else{RAM2_bits16_23 &= 0xef;}	tmpBufRAM2 >>= 1;//2-я защёлка G2
	if (tmpBufRAM3&0x1){RAM3_bits16_23 |= 0x02;}else{RAM3_bits16_23 &= 0xfd;}	tmpBufRAM3 >>= 1;//3-я защёлка G3
	if (tmpBufRAM2&0x1){RAM2_bits16_23 |= 0x04;}else{RAM2_bits16_23 &= 0xfb;}	tmpBufRAM2 >>= 1;//2-я защёлка H
	if (tmpBufRAM1&0x1){RAM1_bits16_23 |= 0x10;}else{RAM1_bits16_23 &= 0xef;}	tmpBufRAM1 >>= 1;//1-я защёлка I
	if (tmpBufRAM2&0x1){RAM2_bits16_23 |= 0x02;}else{RAM2_bits16_23 &= 0xfd;}	tmpBufRAM2 >>= 1;//2-я защёлка J
	if (tmpBufRAM4&0x1){RAM4_bits16_23 |= 0x02;}else{RAM4_bits16_23 &= 0xfd;}	tmpBufRAM4 >>= 1;//4-я защёлка K
	if (tmpBufRAM3&0x1){RAM3_bits16_23 |= 0x10;}else{RAM3_bits16_23 &= 0xef;}	tmpBufRAM3 >>= 1;//3-я защёлка L
	if (tmpBufRAM4&0x1){RAM4_bits16_23 |= 0x04;}else{RAM4_bits16_23 &= 0xfb;}	tmpBufRAM4 >>= 1;//4-я защёлка M
	// Второй разряд
	/*
	<<7 - 0x80 - inverse - 0x7f
	<<6 - 0x40 - inverse - 0xbf
	<<5 - 0x20 - inverse - 0xdf
	<<4 - 0x10 - inverse - 0xef
	<<3 - 0x08 - inverse - 0xf7
	<<2 - 0x04 - inverse - 0xfb
	<<1 - 0x02 - inverse - 0xfd
	<<0	- 0x01 - inverse - 0xfe
*/
	if (tmpBufRAM1&0x1){RAM1_bits16_23 |= 0x80;}else{RAM1_bits16_23 &= 0x7f;}	tmpBufRAM1 >>= 1;//1-я защёлка A
	if (tmpBufRAM1&0x1){RAM1_bits24_31 |= 0x02;}else{RAM1_bits24_31 &= 0xfd;}	tmpBufRAM1 >>= 1;//1-я защёлка B1
	if (tmpBufRAM2&0x1){RAM2_bits24_31 |= 0x02;}else{RAM2_bits24_31 &= 0xfd;}	tmpBufRAM2 >>= 1;//2-я защёлка B2
	if (tmpBufRAM3&0x1){RAM3_bits24_31 |= 0x02;}else{RAM3_bits24_31 &= 0xfd;}	tmpBufRAM3 >>= 1;//3-я защёлка С1
	if (tmpBufRAM4&0x1){RAM4_bits24_31 |= 0x02;}else{RAM4_bits24_31 &= 0xfd;}	tmpBufRAM4 >>= 1;//4-я защёлка С2
	if (tmpBufRAM4&0x1){RAM4_bits24_31 |= 0x01;}else{RAM4_bits24_31 &= 0xfe;}	tmpBufRAM4 >>= 1;//4-я защёлка D
	if (tmpBufRAM4&0x1){RAM4_bits16_23 |= 0x40;}else{RAM4_bits16_23 &= 0xbf;}	tmpBufRAM4 >>= 1;//4-я защёлка E1
	if (tmpBufRAM3&0x1){RAM3_bits16_23 |= 0x40;}else{RAM3_bits16_23 &= 0xbf;}	tmpBufRAM3 >>= 1;//3-я защёлка E2
	if (tmpBufRAM2&0x1){RAM2_bits16_23 |= 0x40;}else{RAM2_bits16_23 &= 0xbf;}	tmpBufRAM2 >>= 1;//2-я защёлка F1
	if (tmpBufRAM1&0x1){RAM1_bits16_23 |= 0x40;}else{RAM1_bits16_23 &= 0xbf;}	tmpBufRAM1 >>= 1;//1-я защёлка F2
	if (tmpBufRAM3&0x1){RAM3_bits16_23 |= 0x80;}else{RAM3_bits16_23 &= 0x7f;}	tmpBufRAM3 >>= 1;//3-я защёлка G1
	if (tmpBufRAM2&0x1){RAM2_bits24_31 |= 0x01;}else{RAM2_bits24_31 &= 0xfe;}	tmpBufRAM2 >>= 1;//2-я защёлка G2
	if (tmpBufRAM3&0x1){RAM3_bits16_23 |= 0x01;}else{RAM3_bits16_23 &= 0xfe;}	tmpBufRAM3 >>= 1;//3-я защёлка G3
	if (tmpBufRAM2&0x1){RAM2_bits16_23 |= 0x80;}else{RAM2_bits16_23 &= 0x7f;}	tmpBufRAM2 >>= 1;//2-я защёлка H
	if (tmpBufRAM1&0x1){RAM1_bits24_31 |= 0x01;}else{RAM1_bits24_31 &= 0xfe;}	tmpBufRAM1 >>= 1;//1-я защёлка I
	if (tmpBufRAM2&0x1){RAM2_bits16_23 |= 0x01;}else{RAM2_bits16_23 &= 0xfe;}	tmpBufRAM2 >>= 1;//2-я защёлка J
	if (tmpBufRAM4&0x1){RAM4_bits16_23 |= 0x01;}else{RAM4_bits16_23 &= 0xfe;}	tmpBufRAM4 >>= 1;//4-я защёлка K
	if (tmpBufRAM3&0x1){RAM3_bits24_31 |= 0x01;}else{RAM3_bits24_31 &= 0xfe;}	tmpBufRAM3 >>= 1;//3-я защёлка L
	if (tmpBufRAM4&0x1){RAM4_bits16_23 |= 0x80;}else{RAM4_bits16_23 &= 0x7f;}	tmpBufRAM4 >>= 1;//4-я защёлка M
	// Третий разряд
	if (tmpBufRAM1&0x1){RAM1_bits24_31 |= 0x08;}else{RAM1_bits24_31 &= 0xf7;}	tmpBufRAM1 >>= 1;//1-я защёлка A
	if (tmpBufRAM1&0x1){RAM1_bits48_55 |= 0x02;}else{RAM1_bits48_55 &= 0xfd;}	tmpBufRAM1 >>= 1;//1-я защёлка B1
	if (tmpBufRAM2&0x1){RAM2_bits48_55 |= 0x02;}else{RAM2_bits48_55 &= 0xfd;}	tmpBufRAM2 >>= 1;//2-я защёлка B2
	if (tmpBufRAM3&0x1){RAM3_bits48_55 |= 0x02;}else{RAM3_bits48_55 &= 0xfd;}	tmpBufRAM3 >>= 1;//3-я защёлка С1
	if (tmpBufRAM4&0x1){RAM4_bits48_55 |= 0x02;}else{RAM4_bits48_55 &= 0xfd;}	tmpBufRAM4 >>= 1;//4-я защёлка С2
	if (tmpBufRAM4&0x1){RAM4_bits48_55 |= 0x01;}else{RAM4_bits48_55 &= 0xfe;}	tmpBufRAM4 >>= 1;//4-я защёлка D
	if (tmpBufRAM4&0x1){RAM4_bits24_31 |= 0x04;}else{RAM4_bits24_31 &= 0xfb;}	tmpBufRAM4 >>= 1;//4-я защёлка E1
	if (tmpBufRAM3&0x1){RAM3_bits24_31 |= 0x04;}else{RAM3_bits24_31 &= 0xfb;}	tmpBufRAM3 >>= 1;//3-я защёлка E2
	if (tmpBufRAM2&0x1){RAM2_bits24_31 |= 0x04;}else{RAM2_bits24_31 &= 0xfb;}	tmpBufRAM2 >>= 1;//2-я защёлка F1
	if (tmpBufRAM1&0x1){RAM1_bits24_31 |= 0x04;}else{RAM1_bits24_31 &= 0xfb;}	tmpBufRAM1 >>= 1;//1-я защёлка F2
	if (tmpBufRAM3&0x1){RAM3_bits24_31 |= 0x08;}else{RAM3_bits24_31 &= 0xf7;}	tmpBufRAM3 >>= 1;//3-я защёлка G1
	if (tmpBufRAM2&0x1){RAM2_bits48_55 |= 0x01;}else{RAM2_bits48_55 &= 0xfe;}	tmpBufRAM2 >>= 1;//2-я защёлка G2
	if (tmpBufRAM3&0x1){RAM3_bits8_15 |= 0x80;}else{RAM3_bits8_15 &= 0x7f;}	tmpBufRAM3 >>= 1;//3-я защёлка G3
	if (tmpBufRAM2&0x1){RAM2_bits24_31 |= 0x08;}else{RAM2_bits24_31 &= 0xf7;}	tmpBufRAM2 >>= 1;//2-я защёлка H
	if (tmpBufRAM1&0x1){RAM1_bits48_55 |= 0x01;}else{RAM1_bits48_55 &= 0xfe;}	tmpBufRAM1 >>= 1;//1-я защёлка I
	if (tmpBufRAM2&0x1){RAM2_bits8_15 |= 0x80;}else{RAM2_bits8_15 &= 0x7f;}	tmpBufRAM2 >>= 1;//2-я защёлка J
	if (tmpBufRAM4&0x1){RAM4_bits8_15 |= 0x80;}else{RAM4_bits8_15 &= 0x7f;}	tmpBufRAM4 >>= 1;//4-я защёлка K
	if (tmpBufRAM3&0x1){RAM3_bits48_55 |= 0x01;}else{RAM3_bits48_55 &= 0xfe;}	tmpBufRAM3 >>= 1;//3-я защёлка L
	if (tmpBufRAM4&0x1){RAM4_bits24_31 |= 0x08;}else{RAM4_bits24_31 &= 0xf7;}	tmpBufRAM4 >>= 1;//4-я защёлка M
	// Четвёртый разряд
	if (tmpBufRAM1&0x1){RAM1_bits48_55 |= 0x08;}else{RAM1_bits48_55 &= 0xf7;}	tmpBufRAM1 >>= 1;//1-я защёлка A
	if (tmpBufRAM1&0x1){RAM1_bits48_55 |= 0x40;}else{RAM1_bits48_55 &= 0xbf;}	tmpBufRAM1 >>= 1;//1-я защёлка B1
	if (tmpBufRAM2&0x1){RAM2_bits48_55 |= 0x40;}else{RAM2_bits48_55 &= 0xbf;}	tmpBufRAM2 >>= 1;//2-я защёлка B2
	if (tmpBufRAM3&0x1){RAM3_bits48_55 |= 0x40;}else{RAM3_bits48_55 &= 0xbf;}	tmpBufRAM3 >>= 1;//3-я защёлка С1
	if (tmpBufRAM4&0x1){RAM4_bits48_55 |= 0x40;}else{RAM4_bits48_55 &= 0xbf;}	tmpBufRAM4 >>= 1;//4-я защёлка С2
	if (tmpBufRAM4&0x1){RAM4_bits48_55 |= 0x10;}else{RAM4_bits48_55 &= 0xef;}	tmpBufRAM4 >>= 1;//4-я защёлка D
	if (tmpBufRAM4&0x1){RAM4_bits48_55 |= 0x04;}else{RAM4_bits48_55 &= 0xfb;}	tmpBufRAM4 >>= 1;//4-я защёлка E1
	if (tmpBufRAM3&0x1){RAM3_bits48_55 |= 0x04;}else{RAM3_bits48_55 &= 0xfb;}	tmpBufRAM3 >>= 1;//3-я защёлка E2
	if (tmpBufRAM2&0x1){RAM2_bits48_55 |= 0x04;}else{RAM2_bits48_55 &= 0xfb;}	tmpBufRAM2 >>= 1;//2-я защёлка F1
	if (tmpBufRAM1&0x1){RAM1_bits48_55 |= 0x04;}else{RAM1_bits48_55 &= 0xfb;}	tmpBufRAM1 >>= 1;//1-я защёлка F2
	if (tmpBufRAM3&0x1){RAM3_bits48_55 |= 0x08;}else{RAM3_bits48_55 &= 0xf7;}	tmpBufRAM3 >>= 1;//3-я защёлка G1
	if (tmpBufRAM2&0x1){RAM2_bits48_55 |= 0x10;}else{RAM2_bits48_55 &= 0xef;}	tmpBufRAM2 >>= 1;//2-я защёлка G2
	if (tmpBufRAM3&0x1){RAM3_bits48_55 |= 0x20;}else{RAM3_bits48_55 &= 0xdf;}	tmpBufRAM3 >>= 1;//3-я защёлка G3
	if (tmpBufRAM2&0x1){RAM2_bits48_55 |= 0x08;}else{RAM2_bits48_55 &= 0xf7;}	tmpBufRAM2 >>= 1;//2-я защёлка H
	if (tmpBufRAM1&0x1){RAM1_bits48_55 |= 0x10;}else{RAM1_bits48_55 &= 0xef;}	tmpBufRAM1 >>= 1;//1-я защёлка I
	if (tmpBufRAM2&0x1){RAM2_bits48_55 |= 0x20;}else{RAM2_bits48_55 &= 0xdf;}	tmpBufRAM2 >>= 1;//2-я защёлка J
	if (tmpBufRAM4&0x1){RAM4_bits48_55 |= 0x20;}else{RAM4_bits48_55 &= 0xdf;}	tmpBufRAM4 >>= 1;//4-я защёлка K
	if (tmpBufRAM3&0x1){RAM3_bits48_55 |= 0x10;}else{RAM3_bits48_55 &= 0xef;}	tmpBufRAM3 >>= 1;//3-я защёлка L
	if (tmpBufRAM4&0x1){RAM4_bits48_55 |= 0x08;}else{RAM4_bits48_55 &= 0xf7;}	tmpBufRAM4 >>= 1;//4-я защёлка M
	// Пятый разряд
	if (tmpBufRAM1&0x1){RAM1_bits56_63 |= 0x20;}else{RAM1_bits56_63 &= 0xdf;}	tmpBufRAM1 >>= 1;//1-я защёлка A
	if (tmpBufRAM1&0x1){RAM1_bits64_71 |= 0x01;}else{RAM1_bits64_71 &= 0xfe;}	tmpBufRAM1 >>= 1;//1-я защёлка B1
	if (tmpBufRAM2&0x1){RAM2_bits64_71 |= 0x01;}else{RAM2_bits64_71 &= 0xfe;}	tmpBufRAM2 >>= 1;//2-я защёлка B2
	if (tmpBufRAM3&0x1){RAM3_bits64_71 |= 0x01;}else{RAM3_bits64_71 &= 0xfe;}	tmpBufRAM3 >>= 1;//3-я защёлка С1
	if (tmpBufRAM4&0x1){RAM4_bits64_71 |= 0x01;}else{RAM4_bits64_71 &= 0xfe;}	tmpBufRAM4 >>= 1;//4-я защёлка С2
	if (tmpBufRAM4&0x1){RAM4_bits56_63 |= 0x40;}else{RAM4_bits56_63 &= 0xbf;}	tmpBufRAM4 >>= 1;//4-я защёлка D
	if (tmpBufRAM4&0x1){RAM4_bits56_63 |= 0x10;}else{RAM4_bits56_63 &= 0xef;}	tmpBufRAM4 >>= 1;//4-я защёлка E1
	if (tmpBufRAM3&0x1){RAM3_bits56_63 |= 0x10;}else{RAM3_bits56_63 &= 0xef;}	tmpBufRAM3 >>= 1;//3-я защёлка E2
	if (tmpBufRAM2&0x1){RAM2_bits56_63 |= 0x10;}else{RAM2_bits56_63 &= 0xef;}	tmpBufRAM2 >>= 1;//2-я защёлка F1
	if (tmpBufRAM1&0x1){RAM1_bits56_63 |= 0x10;}else{RAM1_bits56_63 &= 0xef;}	tmpBufRAM1 >>= 1;//1-я защёлка F2
	if (tmpBufRAM3&0x1){RAM3_bits56_63 |= 0x20;}else{RAM3_bits56_63 &= 0xdf;}	tmpBufRAM3 >>= 1;//3-я защёлка G1
	if (tmpBufRAM2&0x1){RAM2_bits56_63 |= 0x40;}else{RAM2_bits56_63 &= 0xbf;}	tmpBufRAM2 >>= 1;//2-я защёлка G2
	if (tmpBufRAM3&0x1){RAM3_bits56_63 |= 0x80;}else{RAM3_bits56_63 &= 0x7f;}	tmpBufRAM3 >>= 1;//3-я защёлка G3
	if (tmpBufRAM2&0x1){RAM2_bits56_63 |= 0x20;}else{RAM2_bits56_63 &= 0xdf;}	tmpBufRAM2 >>= 1;//2-я защёлка H
	if (tmpBufRAM1&0x1){RAM1_bits56_63 |= 0x40;}else{RAM1_bits56_63 &= 0xbf;}	tmpBufRAM1 >>= 1;//1-я защёлка I
	if (tmpBufRAM2&0x1){RAM2_bits56_63 |= 0x80;}else{RAM2_bits56_63 &= 0x7f;}	tmpBufRAM2 >>= 1;//2-я защёлка J
	if (tmpBufRAM4&0x1){RAM4_bits56_63 |= 0x80;}else{RAM4_bits56_63 &= 0x7f;}	tmpBufRAM4 >>= 1;//4-я защёлка K
	if (tmpBufRAM3&0x1){RAM3_bits56_63 |= 0x40;}else{RAM3_bits56_63 &= 0xbf;}	tmpBufRAM3 >>= 1;//3-я защёлка L
	if (tmpBufRAM4&0x1){RAM4_bits56_63 |= 0x20;}else{RAM4_bits56_63 &= 0xdf;}	tmpBufRAM4 >>= 1;//4-я защёлка M
	// Шестой разряд
	if (tmpBufRAM1&0x1){RAM1_bits64_71 |= 0x04;}else{RAM1_bits64_71 &= 0xfb;}	tmpBufRAM1 >>= 1;//1-я защёлка A
	if (tmpBufRAM1&0x1){RAM1_bits64_71 |= 0x20;}else{RAM1_bits64_71 &= 0xdf;}	tmpBufRAM1 >>= 1;//1-я защёлка B1
	if (tmpBufRAM2&0x1){RAM2_bits64_71 |= 0x20;}else{RAM2_bits64_71 &= 0xdf;}	tmpBufRAM2 >>= 1;//2-я защёлка B2
	if (tmpBufRAM3&0x1){RAM3_bits64_71 |= 0x20;}else{RAM3_bits64_71 &= 0xdf;}	tmpBufRAM3 >>= 1;//3-я защёлка С1
	if (tmpBufRAM4&0x1){RAM4_bits64_71 |= 0x20;}else{RAM4_bits64_71 &= 0xdf;}	tmpBufRAM4 >>= 1;//4-я защёлка С2
	if (tmpBufRAM4&0x1){RAM4_bits64_71 |= 0x08;}else{RAM4_bits64_71 &= 0xf7;}	tmpBufRAM4 >>= 1;//4-я защёлка D
	if (tmpBufRAM4&0x1){RAM4_bits64_71 |= 0x02;}else{RAM4_bits64_71 &= 0xfd;}	tmpBufRAM4 >>= 1;//4-я защёлка E1
	if (tmpBufRAM3&0x1){RAM3_bits64_71 |= 0x02;}else{RAM3_bits64_71 &= 0xfd;}	tmpBufRAM3 >>= 1;//3-я защёлка E2
	if (tmpBufRAM2&0x1){RAM2_bits64_71 |= 0x02;}else{RAM2_bits64_71 &= 0xfd;}	tmpBufRAM2 >>= 1;//2-я защёлка F1
	if (tmpBufRAM1&0x1){RAM1_bits64_71 |= 0x02;}else{RAM1_bits64_71 &= 0xfd;}	tmpBufRAM1 >>= 1;//1-я защёлка F2
	if (tmpBufRAM3&0x1){RAM3_bits64_71 |= 0x04;}else{RAM3_bits64_71 &= 0xfb;}	tmpBufRAM3 >>= 1;//3-я защёлка G1
	if (tmpBufRAM2&0x1){RAM2_bits64_71 |= 0x08;}else{RAM2_bits64_71 &= 0xf7;}	tmpBufRAM2 >>= 1;//2-я защёлка G2
	if (tmpBufRAM3&0x1){RAM3_bits64_71 |= 0x10;}else{RAM3_bits64_71 &= 0xef;}	tmpBufRAM3 >>= 1;//3-я защёлка G3
	if (tmpBufRAM2&0x1){RAM2_bits64_71 |= 0x04;}else{RAM2_bits64_71 &= 0xfb;}	tmpBufRAM2 >>= 1;//2-я защёлка H
	if (tmpBufRAM1&0x1){RAM1_bits64_71 |= 0x08;}else{RAM1_bits64_71 &= 0xf7;}	tmpBufRAM1 >>= 1;//1-я защёлка I
	if (tmpBufRAM2&0x1){RAM2_bits64_71 |= 0x10;}else{RAM2_bits64_71 &= 0xef;}	tmpBufRAM2 >>= 1;//2-я защёлка J
	if (tmpBufRAM4&0x1){RAM4_bits64_71 |= 0x10;}else{RAM4_bits64_71 &= 0xef;}	tmpBufRAM4 >>= 1;//4-я защёлка K
	if (tmpBufRAM3&0x1){RAM3_bits64_71 |= 0x08;}else{RAM3_bits64_71 &= 0xf7;}	tmpBufRAM3 >>= 1;//3-я защёлка L
	if (tmpBufRAM4&0x1){RAM4_bits64_71 |= 0x04;}else{RAM4_bits64_71 &= 0xfb;}	tmpBufRAM4 >>= 1;//4-я защёлка M
	// Седьмой разряд
	if (tmpBufRAM1&0x1){RAM1_bits64_71 |= 0x80;}else{RAM1_bits64_71 &= 0x7f;}	tmpBufRAM1 >>= 1;//1-я защёлка A
	if (tmpBufRAM1&0x1){RAM1_bits72_79 |= 0x04;}else{RAM1_bits72_79 &= 0xfb;}	tmpBufRAM1 >>= 1;//1-я защёлка B1
	if (tmpBufRAM2&0x1){RAM2_bits72_79 |= 0x04;}else{RAM2_bits72_79 &= 0xfb;}	tmpBufRAM2 >>= 1;//2-я защёлка B2
	if (tmpBufRAM3&0x1){RAM3_bits72_79 |= 0x04;}else{RAM3_bits72_79 &= 0xfb;}	tmpBufRAM3 >>= 1;//3-я защёлка С1
	if (tmpBufRAM4&0x1){RAM4_bits72_79 |= 0x04;}else{RAM4_bits72_79 &= 0xfb;}	tmpBufRAM4 >>= 1;//4-я защёлка С2
	if (tmpBufRAM4&0x1){RAM4_bits72_79 |= 0x01;}else{RAM4_bits72_79 &= 0xfe;}	tmpBufRAM4 >>= 1;//4-я защёлка D
	if (tmpBufRAM4&0x1){RAM4_bits64_71 |= 0x40;}else{RAM4_bits64_71 &= 0xbf;}	tmpBufRAM4 >>= 1;//4-я защёлка E1
	if (tmpBufRAM3&0x1){RAM3_bits64_71 |= 0x40;}else{RAM3_bits64_71 &= 0xbf;}	tmpBufRAM3 >>= 1;//3-я защёлка E2
	if (tmpBufRAM2&0x1){RAM2_bits64_71 |= 0x40;}else{RAM2_bits64_71 &= 0xbf;}	tmpBufRAM2 >>= 1;//2-я защёлка F1
	if (tmpBufRAM1&0x1){RAM1_bits64_71 |= 0x40;}else{RAM1_bits64_71 &= 0xbf;}	tmpBufRAM1 >>= 1;//1-я защёлка F2
	if (tmpBufRAM3&0x1){RAM3_bits64_71 |= 0x80;}else{RAM3_bits64_71 &= 0x7f;}	tmpBufRAM3 >>= 1;//3-я защёлка G1
	if (tmpBufRAM2&0x1){RAM2_bits72_79 |= 0x01;}else{RAM2_bits72_79 &= 0xfe;}	tmpBufRAM2 >>= 1;//2-я защёлка G2
	if (tmpBufRAM3&0x1){RAM3_bits72_79 |= 0x02;}else{RAM3_bits72_79 &= 0xfd;}	tmpBufRAM3 >>= 1;//3-я защёлка G3
	if (tmpBufRAM2&0x1){RAM2_bits64_71 |= 0x80;}else{RAM2_bits64_71 &= 0x7f;}	tmpBufRAM2 >>= 1;//2-я защёлка H
	if (tmpBufRAM1&0x1){RAM1_bits72_79 |= 0x01;}else{RAM1_bits72_79 &= 0xfe;}	tmpBufRAM1 >>= 1;//1-я защёлка I
	if (tmpBufRAM2&0x1){RAM2_bits72_79 |= 0x02;}else{RAM2_bits72_79 &= 0xfd;}	tmpBufRAM2 >>= 1;//2-я защёлка J
	if (tmpBufRAM4&0x1){RAM4_bits72_79 |= 0x02;}else{RAM4_bits72_79 &= 0xfd;}	tmpBufRAM4 >>= 1;//4-я защёлка K
	if (tmpBufRAM3&0x1){RAM3_bits72_79 |= 0x01;}else{RAM3_bits72_79 &= 0xfe;}	tmpBufRAM3 >>= 1;//3-я защёлка L
	if (tmpBufRAM4&0x1){RAM4_bits64_71 |= 0x80;}else{RAM4_bits64_71 &= 0x7f;}	tmpBufRAM4 >>= 1;//4-я защёлка M
	// Восьмой разряд
	if (tmpBufRAM1&0x1){RAM1_bits72_79 |= 0x10;}else{RAM1_bits72_79 &= 0xef;}	tmpBufRAM1 >>= 1;//1-я защёлка A
	if (tmpBufRAM1&0x1){RAM1_bits72_79 |= 0x80;}else{RAM1_bits72_79 &= 0x7f;}	tmpBufRAM1 >>= 1;//1-я защёлка B1
	if (tmpBufRAM2&0x1){RAM2_bits72_79 |= 0x80;}else{RAM2_bits72_79 &= 0x7f;}	tmpBufRAM2 >>= 1;//2-я защёлка B2
	if (tmpBufRAM3&0x1){RAM3_bits72_79 |= 0x80;}else{RAM3_bits72_79 &= 0x7f;}	tmpBufRAM3 >>= 1;//3-я защёлка С1
	if (tmpBufRAM4&0x1){RAM4_bits72_79 |= 0x80;}else{RAM4_bits72_79 &= 0x7f;}	tmpBufRAM4 >>= 1;//4-я защёлка С2
	if (tmpBufRAM4&0x1){RAM4_bits72_79 |= 0x20;}else{RAM4_bits72_79 &= 0xdf;}	tmpBufRAM4 >>= 1;//4-я защёлка D
	if (tmpBufRAM4&0x1){RAM4_bits72_79 |= 0x08;}else{RAM4_bits72_79 &= 0xf7;}	tmpBufRAM4 >>= 1;//4-я защёлка E1
	if (tmpBufRAM3&0x1){RAM3_bits72_79 |= 0x08;}else{RAM3_bits72_79 &= 0xf7;}	tmpBufRAM3 >>= 1;//3-я защёлка E2
	if (tmpBufRAM2&0x1){RAM2_bits72_79 |= 0x08;}else{RAM2_bits72_79 &= 0xf7;}	tmpBufRAM2 >>= 1;//2-я защёлка F1
	if (tmpBufRAM1&0x1){RAM1_bits72_79 |= 0x08;}else{RAM1_bits72_79 &= 0xf7;}	tmpBufRAM1 >>= 1;//1-я защёлка F2
	if (tmpBufRAM3&0x1){RAM3_bits72_79 |= 0x10;}else{RAM3_bits72_79 &= 0xef;}	tmpBufRAM3 >>= 1;//3-я защёлка G1
	if (tmpBufRAM2&0x1){RAM2_bits72_79 |= 0x20;}else{RAM2_bits72_79 &= 0xdf;}	tmpBufRAM2 >>= 1;//2-я защёлка G2
	if (tmpBufRAM3&0x1){RAM3_bits72_79 |= 0x40;}else{RAM3_bits72_79 &= 0xbf;}	tmpBufRAM3 >>= 1;//3-я защёлка G3
	if (tmpBufRAM2&0x1){RAM2_bits72_79 |= 0x10;}else{RAM2_bits72_79 &= 0xef;}	tmpBufRAM2 >>= 1;//2-я защёлка H
	if (tmpBufRAM1&0x1){RAM1_bits72_79 |= 0x20;}else{RAM1_bits72_79 &= 0xdf;}	tmpBufRAM1 >>= 1;//1-я защёлка I
	if (tmpBufRAM2&0x1){RAM2_bits72_79 |= 0x40;}else{RAM2_bits72_79 &= 0xbf;}	tmpBufRAM2 >>= 1;//2-я защёлка J
	if (tmpBufRAM4&0x1){RAM4_bits72_79 |= 0x40;}else{RAM4_bits72_79 &= 0xbf;}	tmpBufRAM4 >>= 1;//4-я защёлка K
	if (tmpBufRAM3&0x1){RAM3_bits72_79 |= 0x20;}else{RAM3_bits72_79 &= 0xdf;}	tmpBufRAM3 >>= 1;//3-я защёлка L
	if (tmpBufRAM4&0x1){RAM4_bits72_79 |= 0x10;}else{RAM4_bits72_79 &= 0xef;}	tmpBufRAM4 >>= 1;//4-я защёлка M
}
