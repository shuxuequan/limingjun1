#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM5_Cap_Init(u16 arr,u16 psc);
void TIM3_PWM_Enable(void);
void TIM3_PWM_Disable(void);
void TIM5_Cap_Enable(void);
void TIM5_Cap_Disable(void);
void TIM4_Enable();
void TIM4_Disable();
void TIM4_Int_Init(u16 arr,u16 psc);
#define TempLen 4
extern u32 Freq[TempLen];        //频率值缓存数组
extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
extern u32 Freq_value;  //频率浮点值

extern u32 Freq_ElectricSW_freq;
extern u8 Freq_ElectricSW_flag;
extern u8 Freq_start;
u8 Freq_Sample(void);
u32 the_end_Value(void);
#endif
