#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PF7Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��
void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //ʹ��GPIOF�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //BEEP-->PF.7 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOF, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOF.7
 
 GPIO_ResetBits(GPIOF,GPIO_Pin_7);//���0���رշ��������

}


void Touch_Beep(void){
	GPIO_SetBits(GPIOF,GPIO_Pin_7);
	delay_us(100000);
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);
}
