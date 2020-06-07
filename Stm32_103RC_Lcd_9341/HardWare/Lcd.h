#ifndef __LCD_H
#define __LCD_H	
#include "sys.h"

//========================================
//画笔颜色

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			 			 0XFFE0
#define GBLUE			 			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 					 0XBC40 //棕色
#define BRRED 					 0XFC07 //棕红色
#define GRAY  					 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//============================================

#define PEN_COLOR  RED

// =======================================
//define CMD
#define SET_X_CMD 0X2A
#define SET_Y_CMD 0X2B 
#define WRAM_CMD	0X2C
#define RRAM_CMD	0X2E
#define SCAN_CMD	0X36
	#define LRUD	0X0<<5
	#define	LRDU	0X4<<5
	#define RLUD	0X2<<5
	#define RLDU	0X6<<5
	#define	UDLR	0X1<<5
	#define UDRL	0X3<<5
	#define	DULR	0X5<<5
	#define	DURL	0X7<<5
	 #define DEFAULE_SCAN_DICT 0X8
//=============================================
#define	LCD_RD_1	PCout(6)=1
#define	LCD_RD_0	PCout(6)=0
#define	LCD_WR_1	PCout(7)=1
#define	LCD_WR_0	PCout(7)=0
#define	LCD_RS_1	PCout(8)=1
#define	LCD_RS_0	PCout(8)=0
#define LCD_CS_1	PCout(9)=1
#define LCD_CS_0	PCout(9)=0

#define LCD_LED_1	PCout(10)=1
//==========================================
#define LCD_ENABLE 								LCD_CS_0
#define LCD_DISABLE								LCD_CS_1
#define	LCD_DAT_READ							{LCD_RS_1;LCD_WR_1;}
#define LCD_DAT_WRITE							{LCD_RS_1;LCD_RD_1;}
#define LCD_CMD_WRITE							{LCD_RS_0;LCD_RD_1;}
#define LCD_WRITE									{LCD_WR_0;LCD_WR_1;}
#define LCD_READ									{LCD_RD_0;LCD_RD_1;}
#define LCD_DATA(dat)		GPIOB->ODR=(dat)	
#define LCD_CMD(cmd)		GPIOB->ODR=(cmd)
//==============================================
#define LCD_WRITE_CMD(x)			{LCD_CMD_WRITE;LCD_CMD(x);LCD_WRITE;}
#define LCD_WRITE_DATA(data)	{LCD_DAT_WRITE;LCD_DATA(data);LCD_WRITE;}
#define LCD_READ_DATA					{LCD_DATA_READ;LCD_READ;}
//=================================================
void LcdSting(u16 x,u16 y,u8* cha);
void LcdChar(u16 x,u16 y,u8 cha);
void LcdDrawCircle(u16 x0,u16 y0,u8 r,u16 COLOR);
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LcdWriteChar (u16 x,u16 y );
void LcdDrawSquar(u16 X,u16 Y,u16 Z);
void LcdInit(void);	
void LcdSetScanDirection(u8 DIR);
void LCD_Clear(u16 color);
void LcdDrawPorint(u16 X,u16 Y,u16 Z);
void LcdWriteRamPrepare(void);
void SetCursor(u16 X,u16 Y);
void LcdWriteCMD (u16 data)	;										
void LcdWriteData (u16 data);
void LcdWriteREG(u16 LCD_REG,u16 LCD_REG_VALUE);
//void LcdWrite (u16 data);
#endif
