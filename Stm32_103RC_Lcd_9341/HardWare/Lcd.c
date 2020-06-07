#include "lcd.h"
#include "delay.h"
#include "led.h"
#include "FONT.H"
void LcdSting(u16 x,u16 y,u8* cha)
{


}

void LcdChar(u16 x,u16 y,u8 cha )
{	u8 font,i=0,j=0,y1=y;
	cha-=' ';
	for (i=0;i<36;i++)
		{
			font=asc2_2412[cha][i];	
			for(j=0;j<8;j++)
			{
				if(font&0X80) LcdDrawPorint (y,x,GREEN);					
				 else LCD_WRITE_DATA (BLACK);
				font<<=1;
				y++;
			}	
			if(y>=240)return;
				if(y-y1==24)
				{
					y=y1;
					x++;
					if(x>=320)return;	
				}
		}
	
;
}
   
void LcdDrawCircle(u16 y0,u16 x0,u8 r,u16 COLOR)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LcdDrawPorint (x0+a,y0-b,COLOR);             //5
 		LcdDrawPorint(x0+b,y0-a,COLOR);             //0           
		LcdDrawPorint(x0+b,y0+a,COLOR);             //4               
		LcdDrawPorint(x0+a,y0+b,COLOR);             //6 
		LcdDrawPorint(x0-a,y0+b,COLOR);             //1       
 		LcdDrawPorint(x0-b,y0+a,COLOR);             
		LcdDrawPorint(x0-a,y0-b,COLOR);             //2             
  	LcdDrawPorint(x0-b,y0-a,COLOR);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									
void LCD_Fill(u16 y1,u16 x1,u16 y2,u16 x2,u16 color)
{          
	u16 i;
	for (;y1<=y2;y1++)
	{	
		SetCursor(x1,y1);
		LcdWriteRamPrepare ();
			for(i=x1;i<=x2;i++)
			{
				LcdWriteData (color);
			}

	}
	
	
}  

void LcdWriteChar (u16 x,u16 y)
{u8 i;
SetCursor(x,y);
LcdWriteRamPrepare();
for(i=0;i<24;i++)
//	{u8 FONT_BUFF=asc2_2412[33][i];
//		for (j=0;j<24;j++)
//		{
//			if(FONT_BUFF&0X80)
//			{
//							LCD_WRITE_DATA (RED);
//			}
//			else
//			{
//							LCD_WRITE_DATA (BLUE);
//			}
//			FONT_BUFF<<=1;		
//		}
//	 SetCursor(x,y++);
//		LcdWriteRamPrepare();
//	}
			LCD_WRITE_DATA (BLUE );


}
void LcdWriteData (u16 data)
{
LCD_RS_1;  //data 
LCD_RD_1;		//disable read
LCD_DATA(data)	;  //set the data
LCD_WR_0 ;		//write action
LCD_WR_1	; 
}

void LcdWriteCMD (u16 cmd)
{
LCD_RS_0 ; //cmd
LCD_RD_1 ; //disable read
LCD_CMD(cmd); //set the data
LCD_WR_0 ;	// write action
LCD_WR_1 ;
}

void   LcdWriteREG(u16  cmd ,u16 dat)
{	
LCD_WRITE_CMD	(cmd);
LCD_WRITE_DATA(dat);
//	LcdWriteCMD (cmd);
//	LcdWriteData (dat);
}

void SetCursor(u16 X,u16 Y)
{
LCD_WRITE_CMD 	(SET_X_CMD );
LCD_WRITE_DATA  (X>>8); 	//U16X的高8位输入
LCD_WRITE_DATA 	(X&0xFF);	//U16X的低8位输入
LCD_WRITE_CMD 	(SET_Y_CMD );
LCD_WRITE_DATA	(Y>>8);
LCD_WRITE_DATA 	(Y&0xFF);
}

void LcdWriteRamPrepare(void)
{
LCD_WRITE_CMD (WRAM_CMD);//写入0X2C将接收数据扩展为16位，准备写入数据。
//	LcdWriteCMD(WRAM_CMD );
}

void LcdDrawPorint(u16 X,u16 Y,u16 Z)
{
SetCursor(X,Y);
LcdWriteRamPrepare();
LCD_WRITE_DATA(Z);	
}

void LcdDrawSquar(u16 X,u16 Y,u16 Z)
{	u16 x=X, y=Y;
	u16 i=X, j=Y;
	for (;x<i+20;x++)
	{
		for(;y<j+50;y++)
		{
		LcdDrawPorint (x,y,Z);		
		}
		y=Y;
	}

}
	

void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=240*320;//得到总点数
	SetCursor (0,0);	//设置光标位置 
	LcdWriteRamPrepare ();     		//开始写入GRAM	  	  
	for(index=0;index<totalpoint;index++)LCD_WRITE_DATA(color);	
}

void LcdSetScanDirection(u8 DIR)
{
LcdWriteREG (SCAN_CMD ,DIR);
}

void LcdInit(void)	
{
 	RCC->APB2ENR|=1<<3;//先使能外设PORTB时钟
 	RCC->APB2ENR|=1<<4;//先使能外设PORTC时钟
	RCC->APB2ENR|=1<<0;    //开启辅助时钟（在对AFIO->MAPR操作之前必须首先打开AFIO时钟否则不能操作）
	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR|=1<<26;			//关闭JTAG调试模式，否则JTAG占用PB引脚会死机。		
	//JTAG_Set(SWD_ENABLE);  //开启SWD	

	//PORTC6~10复用推挽输出 	
	GPIOC->CRH&=0XFFFFF000;
	GPIOC->CRH|=0X00000333; 
	GPIOC->CRL&=0X00FFFFFF;
	GPIOC->CRL|=0X33000000;  
	GPIOC->ODR|=0X07C0; 	 
	//PORTB 推挽输出 	
	GPIOB->CRH=0X33333333;
	GPIOB->CRL=0X33333333; 	 
	GPIOB->ODR=0XFFFF;
	delay_ms(5); // delay 50 ms 
	LCD_ENABLE ; //使能LCD片选脚 CS:0
	LcdWriteREG (0x0000,0x0001);
	delay_ms(5); // delay 50 ms   
		LcdWriteCMD(0xCF);  
		LcdWriteData(0x00); 
		LcdWriteData(0xC1); 
		LcdWriteData(0X30); 
		LcdWriteCMD(0xED);  
		LcdWriteData(0x64); 
		LcdWriteData(0x03); 
		LcdWriteData(0X12); 
		LcdWriteData(0X81); 
		LcdWriteCMD(0xE8);  
		LcdWriteData(0x85); 
		LcdWriteData(0x10); 
		LcdWriteData(0x7A); 
		LcdWriteCMD(0xCB);  
		LcdWriteData(0x39); 
		LcdWriteData(0x2C); 
		LcdWriteData(0x00); 
		LcdWriteData(0x34); 
		LcdWriteData(0x02); 
		LcdWriteCMD(0xF7);  
		LcdWriteData(0x20); 
		LcdWriteCMD(0xEA);  
		LcdWriteData(0x00); 
		LcdWriteData(0x00); 
		LcdWriteCMD(0xC0);    //Power control 
		LcdWriteData(0x1B);   //VRH[5:0] 
		LcdWriteCMD(0xC1);    //Power control 
		LcdWriteData(0x01);   //SAP[2:0];BT[3:0] 
		LcdWriteCMD(0xC5);    //VCM control 
		LcdWriteData(0x30); 	 //3F
		LcdWriteData(0x30); 	 //3C
		LcdWriteCMD(0xC7);    //VCM control2 
		LcdWriteData(0XB7); 
		LcdWriteCMD(0x36);    // Memory Access Control 
		LcdWriteData(0x48); 
		LcdWriteCMD(0x3A);   
		LcdWriteData(0x55); 
		LcdWriteCMD(0xB1);   
		LcdWriteData(0x00);   
		LcdWriteData(0x1A); 
		LcdWriteCMD(0xB6);    // Display Function Control 
		LcdWriteData(0x0A); 
		LcdWriteData(0xA2); 
		LcdWriteCMD(0xF2);    // 3Gamma Function Disable 
		LcdWriteData(0x00); 
		LcdWriteCMD(0x26);    //Gamma curve selected 
		LcdWriteData(0x01); 
		LcdWriteCMD(0xE0);    //Set Gamma 
		LcdWriteData(0x0F); 
		LcdWriteData(0x2A); 
		LcdWriteData(0x28); 
		LcdWriteData(0x08); 
		LcdWriteData(0x0E); 
		LcdWriteData(0x08); 
		LcdWriteData(0x54); 
		LcdWriteData(0XA9); 
		LcdWriteData(0x43); 
		LcdWriteData(0x0A); 
		LcdWriteData(0x0F); 
		LcdWriteData(0x00); 
		LcdWriteData(0x00); 
		LcdWriteData(0x00); 
		LcdWriteData(0x00); 		 
		LcdWriteCMD(0XE1);    //Set Gamma 
		LcdWriteData(0x00); 
		LcdWriteData(0x15); 
		LcdWriteData(0x17); 
		LcdWriteData(0x07); 
		LcdWriteData(0x11); 
		LcdWriteData(0x06); 
		LcdWriteData(0x2B); 
		LcdWriteData(0x56); 
		LcdWriteData(0x3C); 
		LcdWriteData(0x05); 
		LcdWriteData(0x10); 
		LcdWriteData(0x0F); 
		LcdWriteData(0x3F); 
		LcdWriteData(0x3F); 
		LcdWriteData(0x0F); 
		LcdWriteCMD(0x2B); 
		LcdWriteData(0x00);
		LcdWriteData(0x00);
		LcdWriteData(0x01);
		LcdWriteData(0x3f);
		LcdWriteCMD(0x2A); 
		LcdWriteData(0x00);
		LcdWriteData(0x00);
		LcdWriteData(0x00);
		LcdWriteData(0xef);	
		LcdWriteCMD(0x11); //Exit Sleep
		delay_ms(20);
		LcdWriteCMD(0x29); //display on
		LCD_Clear (BLACK);

}
