#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ILI93xx.h"
#include "usart.h"	 
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "sram.h"
#include "timer.h"
#include "sdio_sdcard.h"
#include "malloc.h"
#include "GUI.h"
#include "ff.h"
#include "exfuns.h"
#include "w25qxx.h"
#include "includes.h"
#include "fontupd.h"
#include "EmWinHZFont.h"
#include "WM.h"
#include "DIALOG.h"
#include "FramewinDLG.h"
#include "rtc.h" 
#include "backupIF.h"
#include "motor.h"
#include "print.h"
/************************************************
 ALIENTEKս��STM32������STemWinʵ��
 STemWin ������ʾ(FLASH�����ֿ�)
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.co 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

//�������ȼ�
#define START_TASK_PRIO				3
//�����ջ��С	
#define START_STK_SIZE 				1024
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
__align(8) CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//#define STATIC  1u

//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO				4
//�����ջ��С
#define TOUCH_STK_SIZE				128
//������ƿ�
OS_TCB TouchTaskTCB;
//�����ջ
__align(8) CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch����
void touch_task(void *p_arg);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 				5
//�����ջ��С
#define LED0_STK_SIZE				128
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ
__align(8) CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0����
void led0_task(void *p_arg);

//�ֿ��������
//�����������ȼ�
#define FONTUPDATA_TASK_PRIO		6
//�����ջ��С
#define FONTUPDATA_STK_SIZE			128
//������ƿ�
OS_TCB FontupdataTaskTCB;
//�����ջ
__align(8) CPU_STK FONTUPDATA_TASK_STK[FONTUPDATA_STK_SIZE];
//�ֿ��������
void fontupdata_task(void *p_arg);

//EMWINDEMO����
//�����������ȼ�
#define EMWINDEMO_TASK_PRIO			7
//�����ջ��С
#define EMWINDEMO_STK_SIZE			4096
//������ƿ�
OS_TCB EmwindemoTaskTCB;
//�����ջ
__align(8) CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task����
void emwindemo_task(void *p_arg);

#if defined(STATIC)
#define  SystemDatasBroadcast_PRIO            12 //   
#define  SystemDatasBroadcast_STK_SIZE       100 // 
OS_TCB  SystemDatasBroadcast_TCB;        //   
__align(8) CPU_STK SystemDatasBroadcast_STK [SystemDatasBroadcast_STK_SIZE];//
void SystemDatasBroadcast(void *p_arg);
#endif

int main(void)
{	
	OS_ERR err;
	u8 res=0;	
	u32 temp=0,count=0;
	CPU_SR_ALLOC();
	
	delay_init();	    	//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ115200
	uart3_init(9600);
 	//LED_Init();			    //LED�˿ڳ�ʼ��
	TFTLCD_Init();			//LCD��ʼ��	
	RTC_Init();	  			//RTC��ʼ��
	KEY_Init();	 			//������ʼ��
	BEEP_Init();			//��ʼ��������
	FSMC_SRAM_Init();		//��ʼ��SRAM
	my_mem_init(SRAMIN); 	//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);  	//��ʼ���ⲿ�ڴ��
	//TIM3_PWM_Init(899,0); 		
	TIM3_PWM_Init(899,3); //����Ƶ��PWMƵ��=72000/(899+1)=80Khz
	TIM4_Int_Init(999,719);
	MOTOR_stop();
	MOTOR_Init();
	//printf("Val1:%s us\r\n","���");
	//printf("ceshi1 %f m/s\r\n",1.0);
	//printf("Val1:%d us\r\n",SystemCoreClock);
	//printer_print("123456");
 	TIM5_Cap_Init(0XFFFF,7199);	//��1Mhz��Ƶ�ʼ���// 72/(71+1)=1MHz, T=1us*(999+1) = 1ms 
	//MOTORP_out();
    /*TIM3_PWM_Init(899,0);
 	TIM_SetCompare2(TIM3,300);
	MOTORP_out();
	while(1)
	{
		//LED0 = !LED0;
		//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
		while(1)
	{
 		count++;
		if (count==600) MOTOR_stop();
		delay_ms(10);
		//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);
		TIM_SetCompare2(TIM3,count+1);

		//if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			//printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
			TIM5CH1_CAPTURE_STA=0;//������һ�β���
		}
	}	
	}*/
	exfuns_init();			//Ϊfatfs�ļ�ϵͳ�����ڴ�
	f_mount(fs[0],"0:",1);	//����SD��
	res=f_mount(fs[1],"1:",1);	//����FLASH
	if(res==0X0D)//FLASH����,FAT�ļ�ϵͳ����,���¸�ʽ��FLASH
	{
		LCD_ShowString(30,150,200,16,16,"Flash Disk Formatting...");	//��ʽ��FLASH
		res=f_mkfs("1:",1,4096);//��ʽ��FLASH,1,�̷�;1,����Ҫ������,8������Ϊ1����
		if(res==0)
		{
			f_setlabel((const TCHAR *)"1:ALIENTEK");	//����Flash���̵�����Ϊ��ALIENTEK
			LCD_ShowString(30,150,200,16,16,"Flash Disk Format Finish");	//��ʽ�����
		}else LCD_ShowString(30,150,200,16,16,"Flash Disk Format Error ");	//��ʽ��ʧ��
		delay_ms(1000);
	}													    
	LCD_Fill(30,150,240,150+16,WHITE);		//�����ʾ	
	Backup_init();
	while(font_init())		//��ʼ���ֿ�
	{
		LCD_ShowString(30,70,200,16,16,"Font Error!");
		while(SD_Init())	//���SD��
		{
			LCD_ShowString(30,90,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,90,200+30,70+16,WHITE);
			delay_ms(200);		    
		}
		update_font(30,90,16,"0:");	//����ֿⲻ���ھ͸����ֿ�
		delay_ms(2000);
		LCD_Clear(WHITE);	//����
		break;
	}
	TP_Init();				//��������ʼ��
	
	OSInit(&err);			//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();	//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//����CRCʱ��
	//printf("ceshi2 %f m/s\r\n",1.0);
	GUI_Init();  			//STemWin��ʼ��
	//printf("ceshi3 %f m/s\r\n",1.0);
	OS_CRITICAL_ENTER();	//�����ٽ���
	//STemWin Demo����	
	OSTaskCreate((OS_TCB*     )&EmwindemoTaskTCB,		
				 (CPU_CHAR*   )"Emwindemo task", 		
                 (OS_TASK_PTR )emwindemo_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )EMWINDEMO_TASK_PRIO,     
                 (CPU_STK*    )&EMWINDEMO_TASK_STK[0],	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE/10,	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//����������
	OSTaskCreate((OS_TCB*     )&TouchTaskTCB,		
				 (CPU_CHAR*   )"Touch task", 		
                 (OS_TASK_PTR )touch_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )TOUCH_TASK_PRIO,     
                 (CPU_STK*    )&TOUCH_TASK_STK[0],	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);		 
	//LED0����
	/*OSTaskCreate((OS_TCB*     )&Led0TaskTCB,		
				 (CPU_CHAR*   )"Led0 task", 		
                 (OS_TASK_PTR )led0_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )LED0_TASK_PRIO,     
                 (CPU_STK*    )&LED0_TASK_STK[0],	
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED0_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);*/
	//�ֿ��������
	/*OSTaskCreate((OS_TCB*     )&FontupdataTaskTCB,		
				 (CPU_CHAR*   )"Fontupdata task", 		
                 (OS_TASK_PTR )fontupdata_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )FONTUPDATA_TASK_PRIO,     
                 (CPU_STK*    )&FONTUPDATA_TASK_STK[0],	
                 (CPU_STK_SIZE)FONTUPDATA_STK_SIZE/10,	
                 (CPU_STK_SIZE)FONTUPDATA_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����		*/
	
#if defined(STATIC)
	OSTaskCreate( (OS_TCB     *)&SystemDatasBroadcast_TCB,  
                (CPU_CHAR   *)"SystemDatasBroadcast",  
                (OS_TASK_PTR ) SystemDatasBroadcast,  
                (void       *) 0,  
                (OS_PRIO     ) SystemDatasBroadcast_PRIO,  
                (CPU_STK    *)&SystemDatasBroadcast_STK[0],  
                (CPU_STK_SIZE) SystemDatasBroadcast_STK_SIZE/10,/*ջ����ٽ�ֵ��������ջ��С��90%��*/  
                (CPU_STK_SIZE) SystemDatasBroadcast_STK_SIZE,  
                (OS_MSG_QTY  ) 0,  
                (OS_TICK     ) 0,  
                (void       *) 0,  
                (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),   
                (OS_ERR     *) &err);     
#endif
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}


//WM_HWIN hPage[3];
uiPage ui_page;

extern void GUI_UC_SetEncodeGBK(void);
//EMWINDEMO����
void emwindemo_task(void *p_arg)
{
	/*GUI_CURSOR_Show();
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontHZ12);
	GUI_DispStringAt("12�����壺����������� ALIENTEK!",10,10);
	GUI_SetFont(&GUI_FontHZ16);
	GUI_DispStringAt("16�����壺����������� ALIENTEK!",10,30);
	GUI_SetFont(&GUI_FontHZ24);
	GUI_DispStringAt("24�����壺����������� ALIENTEK!",10,50);*/
	//����Ƥ��
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
	GUI_UC_SetEncodeGBK();
	ui_page.index=CreateFramewinIndex();
	//hPage[2]=CreateWindowSKB();
	//WM_HideWindow(hPage[2]);
	 //hPage[2]=CreateWindowSKB();
	 //hPage[2] = CreateWindowSKB();
	//WM_AttachWindow(hPage[2], hPage[0]);
	//WM_HideWindow(hPage[2]);
	//WM_HideWindow(hPage[2]);
	//WM_SetFocus(hPage[0]);
	
	while(1)
	{
		//printf("GU\r\n");
		GUI_Delay(100);
	}
}

//�ֿ��������
//KEY_UP������2s�����ֿ�
/*void fontupdata_task(void *pdata)
{
	OS_ERR err;
	while(1)
	{
		if(WK_UP == 1)				//KEY_UP������
		{
			OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_PERIODIC,&err);//��ʱ2s
			if(WK_UP == 1)			//����KEY_UP��
			{
				LCD_Clear(WHITE);
				OSSchedLock(&err);		//����������
				LCD_ShowString(10,50,250,30,16,"Font Updataing,Please Wait...");
				update_font(10,70,16,"0:");//�����ֿ�
				LCD_Clear(WHITE);
				POINT_COLOR = RED;
				LCD_ShowString(10,50,280,30,16,"Font Updata finshed,Please Restart!");
				OSSchedUnlock(&err);	//����������
			}
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);//��ʱ10ms
	}
}*/

//TOUCH����
void touch_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		//printf("touch_task@@@@@@@@@@@@@\r\n");
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//��ʱ5ms
	}
}

//LED0����
void led0_task(void *p_arg)
{
	OS_ERR err;
	u32 temp=0,count=0;
	//TIM3_PWM_Init(899,0);
 	TIM_SetCompare2(TIM3,300);
	MOTORP_out();
	while(1)
	{
		//LED0 = !LED0;
		//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
		while(1)
	{
 		count=count+10;
		if (count==600) 
		{
					//MOTOR_stop();
				count=0;
	}
		//delay_ms(10);
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);
		TIM_SetCompare2(TIM3,count);

		//if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			//printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
			TIM5CH1_CAPTURE_STA=0;//������һ�β���
		}
	}	
	}
}

#if defined(STATIC)
void  SystemDatasBroadcast (void *p_arg)  
{  
  OS_ERR err;  
  CPU_STK_SIZE free,used;  
  (void)p_arg;  
  while(DEF_TRUE)  
  {  
    OSTaskStkChk (&SystemDatasBroadcast_TCB,&free,&used,&err);//  ��ͳ��������Ķ�ջʹ����Ҳ��ӡ����  
                                  // Ȼ���ʵ����������������100�ֽڸ����ǲ�����ĺ���  
    printf("SystemDatasBroadcast_TCB cp usage:%%%d\r\n",SystemDatasBroadcast_TCB.CPUUsage);
	printf("SystemDatasBroadcast_TCB cp MAXuse usage:%%%d\r\n",SystemDatasBroadcast_TCB.CPUUsageMax);
    printf("SystemDatasBroadcast_TCB static used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));
	printf("SystemDatasBroadcast_TCB���ô��� %d \r\n",SystemDatasBroadcast_TCB.CtxSwCtr);
	printf("SystemDatasBroadcast_TCB״̬%d \r\n",SystemDatasBroadcast_TCB.TaskState);
	printf("\r\n"); 
          
    OSTaskStkChk (&TouchTaskTCB,&free,&used,&err);  
    printf("TouchTaskTCB cp usage:%%%d\r\n",TouchTaskTCB.CPUUsage);
	printf("TouchTaskTCB cp MAXuse usage:%%%d\r\n",TouchTaskTCB.CPUUsageMax);
    printf("TouchTaskTCB static used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));
	printf("TouchTaskTCB���ô��� %d \r\n",TouchTaskTCB.CtxSwCtr);
	printf("TouchTaskTCB״̬%d \r\n",TouchTaskTCB.TaskState);
	printf("\r\n");   
          
    OSTaskStkChk (&EmwindemoTaskTCB,&free,&used,&err);  
	printf("EmwindemoTask cp usage:%%%d\r\n",EmwindemoTaskTCB.CPUUsage);
	printf("EmwindemoTask cp MAXuse usage:%%%d\r\n",EmwindemoTaskTCB.CPUUsageMax);
    printf("EmwindemoTask static used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));
	printf("EmwindemoTask���ô��� %d \r\n",EmwindemoTaskTCB.CtxSwCtr);
	printf("EmwindemoTask״̬%d \r\n",EmwindemoTaskTCB.TaskState);
	printf("\r\n");  
#if 0          
    OSTaskStkChk (&KeyCheck_Process_TCB,&free,&used,&err);  
    printf("KeyCheck              used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));  
          
    OSTaskStkChk (&Light_Adjust_TCB,&free,&used,&err);  
    printf("Light_Adjust          used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));  
          
    OSTaskStkChk (&Calibrate_Process_TCB,&free,&used,&err);  
    printf("Calibrate             used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));  
  
  
    OSTaskStkChk (&Data_Process_TCB,&free,&used,&err);  
    printf("Data_Process          used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));  
#endif

    printf("\r\n\r\n\r\n");  
    OSTimeDlyHMSM(0,0,5,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);  
   }  
}  
#endif

