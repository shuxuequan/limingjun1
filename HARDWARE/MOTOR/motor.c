#include "motor.h"
#include "timer.h"

void MOTOR_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 //GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);						 //PB.5 输出高

 GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);
 MOTOR_stop();
 //MOTORP_out();
}

//正转
void MOTORP_out(){
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
}

//正转
void MOTORN_out(){
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}

//停止
void MOTOR_stop(){
	//GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);
	TIM_SetCompare2(TIM3,0);
}

void MOTOR_start(u16 count){
	TIM_SetCompare2(TIM3,count);
}