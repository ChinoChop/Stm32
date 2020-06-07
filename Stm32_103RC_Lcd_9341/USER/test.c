#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "led.h"
//ALIENTEKMiniSTM32开发板 实验0
//新建工程 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
int main(void)
{	int i='a';
//	u16 i,k;
//	u16 j;
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	LED_Init();
	uart_init(72,115200); 	//串口初始化为115200	
  LcdInit();

  	while(1)
	{ 
		printf(" the read int is %c \r\n",i++);
		if('z'==i)	i='a';
		delay_ms (1000);


		LED0 =!LED0;
	}	 
} 






