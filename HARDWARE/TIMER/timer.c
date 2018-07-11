#include "timer.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "backupIF.h"
#include "motor.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//PWM  驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!

static u32 max_min_Average(u32 * buffer,u8 lenth);
#define TempLen 4
u32 Freq_value=0;  //频率浮点值
u32 Freq[TempLen];        //频率值缓存数组
u32 Freq_Sum=0;      //
u32 Overflow_ptr=0;  //溢出计数值
u8 Freq_ptr1=0;      //滤波计数值1
u8 Freq_ptr2=0;      //滤波计数值2
//u8 Show_flag=0;      //频率值显示标志位

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update  |  //TIM 中断源
		TIM_IT_Trigger,   //TIM 触发中断源 
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		//LED1=!LED1;
		printf("TIM3\r\n");
		}
}


void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM4, //TIM2
		TIM_IT_Update  |  //TIM 中断源
		TIM_IT_Trigger,   //TIM 触发中断源 
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	//TIM_Cmd(TIM4, ENABLE);  //使能TIMx外设
							 
}

u32 Freq_ElectricSW_freq;
u8 Freq_ElectricSW_flag;
u8 Freq_start;
void TIM4_IRQHandler(void)   //TIM3中断
{
	static u8 switchboot=0;
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		
		if(1==Freq_start){
			//Freq_start=0;
			if((KEY_sw2_detect(0)==SW2_PRES)||(KEY_sw3_detect(0)==SW3_PRES)){
				Freq_ElectricSW_freq = Freq_value;
				Freq_ElectricSW_flag=1;
			}
			
		}
		
	
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//	}
}	

}


//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}

void TIM3_PWM_Enable(){
	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
}

void TIM3_PWM_Disable(){
	TIM_Cmd(TIM3, DISABLE);  //使能TIMx外设
}

void TIM4_Enable(){
	TIM_Cmd(TIM4, ENABLE);  //使能TIMx外设
}

void TIM4_Disable(){
	TIM_Cmd(TIM4, DISABLE);  //使能TIMx外设
}

void TIM5_Cap_Enable(){
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	//TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	TIM_Cmd(TIM5, ENABLE);  //使能TIMx外设
	TIM_SetCounter(TIM5,0);
	TIM5CH1_CAPTURE_STA=0;
}

void TIM5_Cap_Disable(){
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,DISABLE);//允许更新中断 ,允许CC1IE捕获中断	

	TIM_Cmd(TIM5, DISABLE);  //使能TIMx外设
	TIM5CH1_CAPTURE_STA=0;
}


//定时器5通道1输入捕获配置

TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 下拉
	
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	//上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_UpdateRequestConfig(TIM5,TIM_UpdateSource_Regular);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	//TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,DISABLE);//允许更新中断 ,允许CC1IE捕获中断
	TIM_ITConfig(TIM5,TIM_IT_CC1|TIM_IT_Update,DISABLE);
	//	TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
   	TIM_Cmd(TIM5,DISABLE ); 	//使能定时器5
   


}

u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
u16 ReadValue1,ReadValue2; 

//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 
//TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
	//TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	u8 updateState=0;
	u8 capturestate=0;
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){
		//printf("-1");
		updateState = 1;
	}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET){
		//printf("-2");
		capturestate =1;
	}
	//printf("TIM5CH1_CAPTURE_STA00000000:%d ms\r\n",TIM5CH1_CAPTURE_STA);
	//printf("TIM5_IRQHandler\r\n");
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		{
			
			//printf("TIM5CH1_CAPTURE_STA1???????:%d ms\r\n",TIM5CH1_CAPTURE_STA);
			//printf("1");
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3f)//高电平太长了
				{
					//printf("TIM5CH1_CAPTURE_STA2???????:%d ms\r\n",TIM5CH1_CAPTURE_STA);
					//printf("2");
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0;
				}
				else {
					TIM5CH1_CAPTURE_STA++;
					//printf("3\r\n");
					//printf("TIM5CH1_CAPTURE_STA3???????:%d ms\r\n",TIM5CH1_CAPTURE_STA);
				}
			}
		}
	 if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕第二次获到上升沿
			{
			TIM5CH1_CAPTURE_VAL= TIM_GetCapture1(TIM5);
			//printf("TIM5CH1_CAPTURE_VAL:%d ms\r\n",TIM5CH1_CAPTURE_VAL);
			#if 0
				ReadValue2 = TIM_GetCapture1(TIM5);
				//printf("4");
				printf("ReadValue1!!!!!!!111:%d ms\r\n",ReadValue1);
				printf("ReadValue2!!!!!!!!!!:%d ms\r\n",ReadValue2);
				if ((ReadValue2 > ReadValue1)&&(TIM5CH1_CAPTURE_STA==0x40))  //无溢出
				{
				TIM5CH1_CAPTURE_VAL = (ReadValue2 - ReadValue1); 
				printf("5\r\n");
				}
				else  //有溢出
				{
				TIM5CH1_CAPTURE_VAL =  ((0xFFFF - ReadValue1) +ReadValue2);
				printf("6\r\n");
				}
				//TIM5CH1_CAPTURE_VAL= TIM_GetCapture1(TIM5);
				//printf("!!!!TIM5CH1_CAPTURE_VAL:%d ms\r\n",TIM5CH1_CAPTURE_VAL);
				//printf("7");
			#endif	
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
			}
			else  								//第一次捕获上升沿
			{
				//ReadValue1=TIM_GetCapture1(TIM5);
				//printf("8");
				TIM_SetCounter(TIM5,0);
				//printf("ReadValue1:%d ms\r\n",TIM_GetCapture1(TIM5));
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA = 0X40;		//标记捕获到了上升沿
			}
		} 
 	} 
    	//TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
    	if(1==capturestate){
 		TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);
		//printf("9");
	}
	if(1==updateState)	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		//printf("10");
	}
}




//频率采样滤波处理
u8 Freq_Sample(void)
{
 u8 Show_flag=0;      //频率值显示标志位
 u32 Dtemp=0; 
 u8 i;
 //捕获了两次高电平
 if(TIM5CH1_CAPTURE_STA&0X80)
 {
  //滤波处理
  Freq_ptr1++;
  //Freq_ptr2++;
  if(Freq_ptr1>=TempLen)
  Freq_ptr1=0;    
  Dtemp = TIM5CH1_CAPTURE_STA&0X3F;
  #if 0
  Dtemp *= 65536;//溢出时间总和  
  if(Dtemp<=65536)  //溢出次数小于2
    Dtemp = TIM5CH1_CAPTURE_VAL;
  else 
    Dtemp = Dtemp-65536+TIM5CH1_CAPTURE_VAL;
  #endif
  Dtemp *= 65536;//溢出时间总和  
  if(Dtemp<65536)  //溢出次数小于2
    Dtemp = TIM5CH1_CAPTURE_VAL;
  else
  	Dtemp=Dtemp+TIM5CH1_CAPTURE_VAL;
     //Dtemp = TIM5CH1_CAPTURE_VAL;
  Freq[Freq_ptr1] = Dtemp;
  //Dtemp=0;
  //Freq_ptr1++;
  //if(Freq_ptr1>=TempLen)
  //{
	//Freq_ptr1=0; 
	//for(i=0;i<TempLen;i++)
       //Dtemp += Freq[i];     
    //Freq_value = 10000000.0/Dtemp;

	 //Freq_value = max_min_Average(Freq,TempLen);
  	Freq_value = Dtemp;
    //Freq_ptr2=TempLen;
  	//Overflow_ptr=0;
  	Show_flag =1;
	
  	//}
 	TIM5CH1_CAPTURE_STA=0;
 	}
 	else Show_flag=0;
 	return Show_flag;

}
  

static u32 max_min_Average(u32 * buffer,u8 lenth)
{
  u8  i;
	u32 max=0,min=0,sum=0,average=0;
		for (i=0;i<lenth;i++)
	{
		
		if (max<*(buffer+i))
			max=*(buffer+i);
		if (min>*(buffer+i))
			min=*(buffer+i);
    sum=sum+*(buffer+i);
	}	
	average=(sum-min-max)/(lenth-2);
	printf("max_min_Average %d\r\n",average);
	return average;
}

static void bubble_sort(u32 * a,u8  n); 
u32 the_end_Value(){
	u8 i =0;
	bubble_sort(Freq,TempLen);
	for (i=0;i<(TempLen-1);i++){
		//printf("Freq[]  %d\r\n:",Freq[i]);
		}
	for (i=0;i<(TempLen-1);i++){
		if(Freq[i]>0){
			if((Freq[i+1]-Freq[i])<500){
			return Freq[i];
		}
		}
		//if(i==1)
			//break;
	}
	return Freq[TempLen-1];
}


/*2、冒泡排序 
基本思想： 不断比较相邻的两个数，让较大的数不断地往后移。经过一番比较，就选出了最大的数。经过第二轮比较，就选出了次大的数。以此类推。 
那么对于大小为N的数组，需要N-1轮比较。 
平均时间复杂度O（N^2） 
最好情况O（N） 
最坏情况O（N^2） 
空间复杂度O（1） 
*/
void swap(u32 *a,u32 *b)  
{  
    int temp;  
    temp=*a;  
    *a=*b;  
    *b=temp;  
}  
static void bubble_sort(u32 * a,u8 n)  
{  
    //要进行N-1轮比较  
    u8 is_sorted = 1; 
	int i =0;
	int j=0;
    for(i = 0; i < n-1; i++ )//[0,n-2]恰好n-1轮比较  
    {  
        for(j = 0; j < n-i-1 ; j++)//已经排好序的最后i个不用比较，要比较的数的个数为n-i个，那么需要比较的次数为n-i-1  
        {  
            if(a[j] > a[j+1]){  
                is_sorted = 0;
                swap(&(a[j]),&(a[j+1]));  
            }  
        }  
        if(is_sorted)//如果没有发生交换，说明已经排好序了，提前退出循环,所以最好情况下时间复杂度为O（N）  
            break;  
    }  
}  

