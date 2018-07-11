#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//蜂鸣器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PF7为输出口.并使能这个口的时钟		    
//蜂鸣器初始化
void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //使能GPIOF端口时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //BEEP-->PF.7 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 GPIO_Init(GPIOF, &GPIO_InitStructure);	 //根据参数初始化GPIOF.7
 
 GPIO_ResetBits(GPIOF,GPIO_Pin_7);//输出0，关闭蜂鸣器输出

}


void Touch_Beep(void){
	GPIO_SetBits(GPIOF,GPIO_Pin_7);
	delay_us(100000);
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);
}
