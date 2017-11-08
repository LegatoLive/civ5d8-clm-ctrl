/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __M6775T_H_
#define __M6775T_H_
/* SPI pins definition -------------------------------------------------------*/
#define SPI_MASTER_NSS	GPIO_Pin_4
#define SPI_MASTER_SCK	GPIO_Pin_5
#define SPI_MASTER_MISO	GPIO_Pin_6
#define SPI_MASTER_MOSI	GPIO_Pin_7

/* LATCHES DEFINITION */
#define LATCH1																		((uint8_t) 0x08)
#define LATCH2																		((uint8_t) 0x10)
#define LATCH3																		((uint8_t) 0x20)
#define LATCH4																		((uint8_t) 0x40)
#define LATCH5																		((uint8_t) 0x80)
/* ------------------ */
/* Includes ------------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uint8_t	RAM1_bits0_7, RAM1_bits8_15, RAM1_bits16_23, RAM1_bits24_31, RAM1_bits32_39, RAM1_bits40_47, RAM1_bits48_55, RAM1_bits56_63, RAM1_bits64_71, RAM1_bits72_79,
								RAM2_bits0_7, RAM2_bits8_15, RAM2_bits16_23, RAM2_bits24_31, RAM2_bits32_39, RAM2_bits40_47, RAM2_bits48_55, RAM2_bits56_63, RAM2_bits64_71, RAM2_bits72_79,
								RAM3_bits0_7, RAM3_bits8_15, RAM3_bits16_23, RAM3_bits24_31, RAM3_bits32_39, RAM3_bits40_47, RAM3_bits48_55, RAM3_bits56_63, RAM3_bits64_71, RAM3_bits72_79,
								RAM4_bits0_7, RAM4_bits8_15, RAM4_bits16_23, RAM4_bits24_31, RAM4_bits32_39, RAM4_bits40_47, RAM4_bits48_55, RAM4_bits56_63, RAM4_bits64_71, RAM4_bits72_79;

extern char lcdText[8];
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/*

struct CLIM1_LCD{
	
};
struct CLIM2_LCD{
	
};
struct STRING_LCD{
	
};
struct ICON_LCD{
	
};*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void M6775T_SPI_Init(void);
void CleanLCD(void);
void LCD_WRITE(uint8_t pack0, uint8_t pack1, uint8_t pack2, uint8_t pack3, uint8_t pack4,
							 uint8_t pack5, uint8_t pack6, uint8_t pack7, uint8_t pack8, uint8_t pack9,
							 uint8_t latch);
void getTime(uint32_t TimeVar, uint32_t THH, uint32_t TMM,uint32_t TSS);
void NumToTimeDigits(uint8_t THH, uint8_t TMM);
uint32_t getChar(uint8_t SYMBOL);
void LCD_WriteText(char string[]);
#endif /* __M6775T_H_ */
