#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
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
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	/*//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0*/

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_sw1_detect(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(SW1==1))
	{
		delay_us(10);//ȥ���� 
		key_up=0;
		return SW1_PRES;
	}else if(SW1==0)key_up=1; 	    
 	return 0;// �ް�������
}

u8 KEY_sw2_detect(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(SW2==0))
	{
		delay_us(10);//ȥ���� 
		key_up=0;
		return SW2_PRES;
	}else if(SW2==1)key_up=1; 	    
 	return 0;// �ް�������
}

u8 KEY_sw3_detect(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(SW3==0))
	{
		delay_us(10);//ȥ���� 
		key_up=0;
		return SW3_PRES;
	}else if(SW3==1)key_up=1; 	    
 	return 0;// �ް�������
}

u8 KEY_sw2_detect_swich(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(SW2==0))
	{
		delay_us(10);//ȥ���� 
		key_up=0;
		return SW2_PRES;
	}else if(SW2==1)key_up=1; 	    
 	return 0;// �ް�������
}

u8 KEY_sw3_detect_swich(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(SW3==0))
	{
		delay_us(10);//ȥ���� 
		key_up=0;
		return SW3_PRES;
	}else if(SW3==1)key_up=1; 	    
 	return 0;// �ް�������
}

