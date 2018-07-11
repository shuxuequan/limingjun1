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
 ALIENTEK战舰STM32开发板STemWin实验
 STemWin 汉字显示(FLASH外置字库)
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.co 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

//任务优先级
#define START_TASK_PRIO				3
//任务堆栈大小	
#define START_STK_SIZE 				1024
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
__align(8) CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//#define STATIC  1u

//TOUCH任务
//设置任务优先级
#define TOUCH_TASK_PRIO				4
//任务堆栈大小
#define TOUCH_STK_SIZE				128
//任务控制块
OS_TCB TouchTaskTCB;
//任务堆栈
__align(8) CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch任务
void touch_task(void *p_arg);

//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO 				5
//任务堆栈大小
#define LED0_STK_SIZE				128
//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈
__align(8) CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0任务
void led0_task(void *p_arg);

//字库更新任务
//设置任务优先级
#define FONTUPDATA_TASK_PRIO		6
//任务堆栈大小
#define FONTUPDATA_STK_SIZE			128
//任务控制块
OS_TCB FontupdataTaskTCB;
//任务堆栈
__align(8) CPU_STK FONTUPDATA_TASK_STK[FONTUPDATA_STK_SIZE];
//字库更新任务
void fontupdata_task(void *p_arg);

//EMWINDEMO任务
//设置任务优先级
#define EMWINDEMO_TASK_PRIO			7
//任务堆栈大小
#define EMWINDEMO_STK_SIZE			4096
//任务控制块
OS_TCB EmwindemoTaskTCB;
//任务堆栈
__align(8) CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task任务
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
	
	delay_init();	    	//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为115200
	uart3_init(9600);
 	//LED_Init();			    //LED端口初始化
	TFTLCD_Init();			//LCD初始化	
	RTC_Init();	  			//RTC初始化
	KEY_Init();	 			//按键初始化
	BEEP_Init();			//初始化蜂鸣器
	FSMC_SRAM_Init();		//初始化SRAM
	my_mem_init(SRAMIN); 	//初始化内部内存池
	my_mem_init(SRAMEX);  	//初始化外部内存池
	//TIM3_PWM_Init(899,0); 		
	TIM3_PWM_Init(899,3); //不分频。PWM频率=72000/(899+1)=80Khz
	TIM4_Int_Init(999,719);
	MOTOR_stop();
	MOTOR_Init();
	//printf("Val1:%s us\r\n","你好");
	//printf("ceshi1 %f m/s\r\n",1.0);
	//printf("Val1:%d us\r\n",SystemCoreClock);
	//printer_print("123456");
 	TIM5_Cap_Init(0XFFFF,7199);	//以1Mhz的频率计数// 72/(71+1)=1MHz, T=1us*(999+1) = 1ms 
	//MOTORP_out();
    /*TIM3_PWM_Init(899,0);
 	TIM_SetCompare2(TIM3,300);
	MOTORP_out();
	while(1)
	{
		//LED0 = !LED0;
		//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//延时500ms
		while(1)
	{
 		count++;
		if (count==600) MOTOR_stop();
		delay_ms(10);
		//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);
		TIM_SetCompare2(TIM3,count+1);

		//if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//溢出时间总和
			temp+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间
			//printf("HIGH:%d us\r\n",temp);//打印总的高点平时间
			TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
		}
	}	
	}*/
	exfuns_init();			//为fatfs文件系统分配内存
	f_mount(fs[0],"0:",1);	//挂载SD卡
	res=f_mount(fs[1],"1:",1);	//挂载FLASH
	if(res==0X0D)//FLASH磁盘,FAT文件系统错误,重新格式化FLASH
	{
		LCD_ShowString(30,150,200,16,16,"Flash Disk Formatting...");	//格式化FLASH
		res=f_mkfs("1:",1,4096);//格式化FLASH,1,盘符;1,不需要引导区,8个扇区为1个簇
		if(res==0)
		{
			f_setlabel((const TCHAR *)"1:ALIENTEK");	//设置Flash磁盘的名字为：ALIENTEK
			LCD_ShowString(30,150,200,16,16,"Flash Disk Format Finish");	//格式化完成
		}else LCD_ShowString(30,150,200,16,16,"Flash Disk Format Error ");	//格式化失败
		delay_ms(1000);
	}													    
	LCD_Fill(30,150,240,150+16,WHITE);		//清除显示	
	Backup_init();
	while(font_init())		//初始化字库
	{
		LCD_ShowString(30,70,200,16,16,"Font Error!");
		while(SD_Init())	//检测SD卡
		{
			LCD_ShowString(30,90,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,90,200+30,70+16,WHITE);
			delay_ms(200);		    
		}
		update_font(30,90,16,"0:");	//如果字库不存在就更新字库
		delay_ms(2000);
		LCD_Clear(WHITE);	//清屏
		break;
	}
	TP_Init();				//触摸屏初始化
	
	OSInit(&err);			//初始化UCOSIII
	OS_CRITICAL_ENTER();	//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
	while(1);
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//开启CRC时钟
	//printf("ceshi2 %f m/s\r\n",1.0);
	GUI_Init();  			//STemWin初始化
	//printf("ceshi3 %f m/s\r\n",1.0);
	OS_CRITICAL_ENTER();	//进入临界区
	//STemWin Demo任务	
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
	//触摸屏任务
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
	//LED0任务
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
	//字库更新任务
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
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务		*/
	
#if defined(STATIC)
	OSTaskCreate( (OS_TCB     *)&SystemDatasBroadcast_TCB,  
                (CPU_CHAR   *)"SystemDatasBroadcast",  
                (OS_TASK_PTR ) SystemDatasBroadcast,  
                (void       *) 0,  
                (OS_PRIO     ) SystemDatasBroadcast_PRIO,  
                (CPU_STK    *)&SystemDatasBroadcast_STK[0],  
                (CPU_STK_SIZE) SystemDatasBroadcast_STK_SIZE/10,/*栈溢出临界值我设置在栈大小的90%处*/  
                (CPU_STK_SIZE) SystemDatasBroadcast_STK_SIZE,  
                (OS_MSG_QTY  ) 0,  
                (OS_TICK     ) 0,  
                (void       *) 0,  
                (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),   
                (OS_ERR     *) &err);     
#endif
	OS_CRITICAL_EXIT();	//退出临界区
}


//WM_HWIN hPage[3];
uiPage ui_page;

extern void GUI_UC_SetEncodeGBK(void);
//EMWINDEMO任务
void emwindemo_task(void *p_arg)
{
	/*GUI_CURSOR_Show();
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontHZ12);
	GUI_DispStringAt("12号字体：广州星翼电子 ALIENTEK!",10,10);
	GUI_SetFont(&GUI_FontHZ16);
	GUI_DispStringAt("16号字体：广州星翼电子 ALIENTEK!",10,30);
	GUI_SetFont(&GUI_FontHZ24);
	GUI_DispStringAt("24号字体：广州星翼电子 ALIENTEK!",10,50);*/
	//更换皮肤
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

//字库更新任务
//KEY_UP键长按2s更新字库
/*void fontupdata_task(void *pdata)
{
	OS_ERR err;
	while(1)
	{
		if(WK_UP == 1)				//KEY_UP键按下
		{
			OSTimeDlyHMSM(0,0,2,0,OS_OPT_TIME_PERIODIC,&err);//延时2s
			if(WK_UP == 1)			//还是KEY_UP键
			{
				LCD_Clear(WHITE);
				OSSchedLock(&err);		//调度器上锁
				LCD_ShowString(10,50,250,30,16,"Font Updataing,Please Wait...");
				update_font(10,70,16,"0:");//更新字库
				LCD_Clear(WHITE);
				POINT_COLOR = RED;
				LCD_ShowString(10,50,280,30,16,"Font Updata finshed,Please Restart!");
				OSSchedUnlock(&err);	//调度器解锁
			}
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);//延时10ms
	}
}*/

//TOUCH任务
void touch_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		//printf("touch_task@@@@@@@@@@@@@\r\n");
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//延时5ms
	}
}

//LED0任务
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
		//OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//延时500ms
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
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//溢出时间总和
			temp+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间
			//printf("HIGH:%d us\r\n",temp);//打印总的高点平时间
			TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
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
    OSTaskStkChk (&SystemDatasBroadcast_TCB,&free,&used,&err);//  把统计任务本身的堆栈使用量也打印出来  
                                  // 然后从实验结果看看我们设置100字节给它是不是真的合适  
    printf("SystemDatasBroadcast_TCB cp usage:%%%d\r\n",SystemDatasBroadcast_TCB.CPUUsage);
	printf("SystemDatasBroadcast_TCB cp MAXuse usage:%%%d\r\n",SystemDatasBroadcast_TCB.CPUUsageMax);
    printf("SystemDatasBroadcast_TCB static used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));
	printf("SystemDatasBroadcast_TCB调用次数 %d \r\n",SystemDatasBroadcast_TCB.CtxSwCtr);
	printf("SystemDatasBroadcast_TCB状态%d \r\n",SystemDatasBroadcast_TCB.TaskState);
	printf("\r\n"); 
          
    OSTaskStkChk (&TouchTaskTCB,&free,&used,&err);  
    printf("TouchTaskTCB cp usage:%%%d\r\n",TouchTaskTCB.CPUUsage);
	printf("TouchTaskTCB cp MAXuse usage:%%%d\r\n",TouchTaskTCB.CPUUsageMax);
    printf("TouchTaskTCB static used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));
	printf("TouchTaskTCB调用次数 %d \r\n",TouchTaskTCB.CtxSwCtr);
	printf("TouchTaskTCB状态%d \r\n",TouchTaskTCB.TaskState);
	printf("\r\n");   
          
    OSTaskStkChk (&EmwindemoTaskTCB,&free,&used,&err);  
	printf("EmwindemoTask cp usage:%%%d\r\n",EmwindemoTaskTCB.CPUUsage);
	printf("EmwindemoTask cp MAXuse usage:%%%d\r\n",EmwindemoTaskTCB.CPUUsageMax);
    printf("EmwindemoTask static used/free:%d/%d  usage:%%%d\r\n",used,free,(used*100)/(used+free));
	printf("EmwindemoTask调用次数 %d \r\n",EmwindemoTaskTCB.CtxSwCtr);
	printf("EmwindemoTask状态%d \r\n",EmwindemoTaskTCB.TaskState);
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

