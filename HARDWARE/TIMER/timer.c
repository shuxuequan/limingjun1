#include "timer.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "backupIF.h"
#include "motor.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//PWM  ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!

static u32 max_min_Average(u32 * buffer,u8 lenth);
#define TempLen 4
u32 Freq_value=0;  //Ƶ�ʸ���ֵ
u32 Freq[TempLen];        //Ƶ��ֵ��������
u32 Freq_Sum=0;      //
u32 Overflow_ptr=0;  //�������ֵ
u8 Freq_ptr1=0;      //�˲�����ֵ1
u8 Freq_ptr2=0;      //�˲�����ֵ2
//u8 Show_flag=0;      //Ƶ��ֵ��ʾ��־λ

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		//LED1=!LED1;
		printf("TIM3\r\n");
		}
}


void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	//TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����
							 
}

u32 Freq_ElectricSW_freq;
u8 Freq_ElectricSW_flag;
u8 Freq_start;
void TIM4_IRQHandler(void)   //TIM3�ж�
{
	static u8 switchboot=0;
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		
		if(1==Freq_start){
			//Freq_start=0;
			if((KEY_sw2_detect(0)==SW2_PRES)||(KEY_sw3_detect(0)==SW3_PRES)){
				Freq_ElectricSW_freq = Freq_value;
				Freq_ElectricSW_flag=1;
			}
			
		}
		
	
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//	}
}	

}


//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
 	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}

void TIM3_PWM_Enable(){
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
}

void TIM3_PWM_Disable(){
	TIM_Cmd(TIM3, DISABLE);  //ʹ��TIMx����
}

void TIM4_Enable(){
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����
}

void TIM4_Disable(){
	TIM_Cmd(TIM4, DISABLE);  //ʹ��TIMx����
}

void TIM5_Cap_Enable(){
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	//TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx����
	TIM_SetCounter(TIM5,0);
	TIM5CH1_CAPTURE_STA=0;
}

void TIM5_Cap_Disable(){
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,DISABLE);//��������ж� ,����CC1IE�����ж�	

	TIM_Cmd(TIM5, DISABLE);  //ʹ��TIMx����
	TIM5CH1_CAPTURE_STA=0;
}


//��ʱ��5ͨ��1���벶������

TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����
	
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	//�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	TIM_UpdateRequestConfig(TIM5,TIM_UpdateSource_Regular);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	//TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,DISABLE);//��������ж� ,����CC1IE�����ж�
	TIM_ITConfig(TIM5,TIM_IT_CC1|TIM_IT_Update,DISABLE);
	//	TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�
   	TIM_Cmd(TIM5,DISABLE ); 	//ʹ�ܶ�ʱ��5
   


}

u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ
u16 ReadValue1,ReadValue2; 

//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 
//TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
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
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		{
			
			//printf("TIM5CH1_CAPTURE_STA1???????:%d ms\r\n",TIM5CH1_CAPTURE_STA);
			//printf("1");
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3f)//�ߵ�ƽ̫����
				{
					//printf("TIM5CH1_CAPTURE_STA2???????:%d ms\r\n",TIM5CH1_CAPTURE_STA);
					//printf("2");
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0;
				}
				else {
					TIM5CH1_CAPTURE_STA++;
					//printf("3\r\n");
					//printf("TIM5CH1_CAPTURE_STA3???????:%d ms\r\n",TIM5CH1_CAPTURE_STA);
				}
			}
		}
	 if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			
			if(TIM5CH1_CAPTURE_STA&0X40)		//���ڶ��λ�������
			{
			TIM5CH1_CAPTURE_VAL= TIM_GetCapture1(TIM5);
			//printf("TIM5CH1_CAPTURE_VAL:%d ms\r\n",TIM5CH1_CAPTURE_VAL);
			#if 0
				ReadValue2 = TIM_GetCapture1(TIM5);
				//printf("4");
				printf("ReadValue1!!!!!!!111:%d ms\r\n",ReadValue1);
				printf("ReadValue2!!!!!!!!!!:%d ms\r\n",ReadValue2);
				if ((ReadValue2 > ReadValue1)&&(TIM5CH1_CAPTURE_STA==0x40))  //�����
				{
				TIM5CH1_CAPTURE_VAL = (ReadValue2 - ReadValue1); 
				printf("5\r\n");
				}
				else  //�����
				{
				TIM5CH1_CAPTURE_VAL =  ((0xFFFF - ReadValue1) +ReadValue2);
				printf("6\r\n");
				}
				//TIM5CH1_CAPTURE_VAL= TIM_GetCapture1(TIM5);
				//printf("!!!!TIM5CH1_CAPTURE_VAL:%d ms\r\n",TIM5CH1_CAPTURE_VAL);
				//printf("7");
			#endif	
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
			}
			else  								//��һ�β���������
			{
				//ReadValue1=TIM_GetCapture1(TIM5);
				//printf("8");
				TIM_SetCounter(TIM5,0);
				//printf("ReadValue1:%d ms\r\n",TIM_GetCapture1(TIM5));
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA = 0X40;		//��ǲ�����������
			}
		} 
 	} 
    	//TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
    	if(1==capturestate){
 		TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);
		//printf("9");
	}
	if(1==updateState)	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		//printf("10");
	}
}




//Ƶ�ʲ����˲�����
u8 Freq_Sample(void)
{
 u8 Show_flag=0;      //Ƶ��ֵ��ʾ��־λ
 u32 Dtemp=0; 
 u8 i;
 //���������θߵ�ƽ
 if(TIM5CH1_CAPTURE_STA&0X80)
 {
  //�˲�����
  Freq_ptr1++;
  //Freq_ptr2++;
  if(Freq_ptr1>=TempLen)
  Freq_ptr1=0;    
  Dtemp = TIM5CH1_CAPTURE_STA&0X3F;
  #if 0
  Dtemp *= 65536;//���ʱ���ܺ�  
  if(Dtemp<=65536)  //�������С��2
    Dtemp = TIM5CH1_CAPTURE_VAL;
  else 
    Dtemp = Dtemp-65536+TIM5CH1_CAPTURE_VAL;
  #endif
  Dtemp *= 65536;//���ʱ���ܺ�  
  if(Dtemp<65536)  //�������С��2
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


/*2��ð������ 
����˼�룺 ���ϱȽ����ڵ����������ýϴ�������ϵ������ơ�����һ���Ƚϣ���ѡ�����������������ڶ��ֱȽϣ���ѡ���˴δ�������Դ����ơ� 
��ô���ڴ�СΪN�����飬��ҪN-1�ֱȽϡ� 
ƽ��ʱ�临�Ӷ�O��N^2�� 
������O��N�� 
����O��N^2�� 
�ռ临�Ӷ�O��1�� 
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
    //Ҫ����N-1�ֱȽ�  
    u8 is_sorted = 1; 
	int i =0;
	int j=0;
    for(i = 0; i < n-1; i++ )//[0,n-2]ǡ��n-1�ֱȽ�  
    {  
        for(j = 0; j < n-i-1 ; j++)//�Ѿ��ź�������i�����ñȽϣ�Ҫ�Ƚϵ����ĸ���Ϊn-i������ô��Ҫ�ȽϵĴ���Ϊn-i-1  
        {  
            if(a[j] > a[j+1]){  
                is_sorted = 0;
                swap(&(a[j]),&(a[j+1]));  
            }  
        }  
        if(is_sorted)//���û�з���������˵���Ѿ��ź����ˣ���ǰ�˳�ѭ��,������������ʱ�临�Ӷ�ΪO��N��  
            break;  
    }  
}  

