#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/05
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//LED�˿ڶ���
#define LED0 PAout(8)	// PA8
#define LED1 PDout(2)	// PD2	

void LED_Init(void);	//��ʼ��

typedef enum {
	red =0,
green=1

}LED_SELECT;

void Blink(LED_SELECT LED_COLOR ,u8 TIMS);
#endif
















