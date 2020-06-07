#include "sys.h"   
#include "led.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/05
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��	   	 
	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	   	 
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003;//PA8 �������   	 
    GPIOA->ODR|=1<<8;      //PA8 �����
											  
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2�������
	GPIOD->ODR|=1<<2;      //PD.2����� 
//	GPIOD->BSRR|=1<<2;
}

//LED_COLOR   RED  GREEN 

void Blink(LED_SELECT LED_COLOR ,u8 TIMS)
{
	u8 i;
	for(i=0;i<TIMS ;i++)
	{
		switch (LED_COLOR)
    {
    	case red:
				PAout	(8)=!PAout (8);
    		break;
    	case green :
				PDout (2)=!PDout (2);
    		break;
    	default:
    		break;
    }
	
	delay_ms (100);
	}


}




