#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

#define SW1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ����0 �������
#define SW2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ����1 ������������
#define SW3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����2 ������������
//#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3(WK_UP) 

 

#define SW1_PRES 	1	//KEY0����
#define SW2_PRES	2	//KEY1����
#define SW3_PRES	3	//KEY2����
//#define WKUP_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_sw1_detect(u8 mode); //0���� 1 �̰�
u8 KEY_sw2_detect(u8 mode);
u8 KEY_sw2_detect(u8 mode);
u8 KEY_sw2_detect_swich(u8 mode);
u8 KEY_sw3_detect_swich(u8 mode);

#endif
