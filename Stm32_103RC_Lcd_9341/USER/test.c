#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h"
#include "led.h"
//ALIENTEKMiniSTM32������ ʵ��0
//�½����� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
int main(void)
{	int i='a';
//	u16 i,k;
//	u16 j;
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	LED_Init();
	uart_init(72,115200); 	//���ڳ�ʼ��Ϊ115200	
  LcdInit();

  	while(1)
	{ 
		printf(" the read int is %c \r\n",i++);
		if('z'==i)	i='a';
		delay_ms (1000);


		LED0 =!LED0;
	}	 
} 






