/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.26                          *
*        Compiled Aug  8 2014, 14:49:54                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include <string.h>
#include <stdlib.h>
#include "DIALOG.h"
#include "EmWinHZFont.h"
#include "FramewinDLG.h"
#include "backupIF.h"
#include "timer.h"
#include "motor.h"
#include "key.h"
#include "beep.h"
#include "rtc.h"
#include "usart.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0     (GUI_ID_USER + 0x00)
#define ID_GRAPH_0     (GUI_ID_USER + 0x02)
#define ID_BUTTON_0     (GUI_ID_USER + 0x04)
#define ID_BUTTON_1     (GUI_ID_USER + 0x05)
#define ID_BUTTON_2     (GUI_ID_USER + 0x06)
#define ID_BUTTON_3     (GUI_ID_USER + 0x07)
#define ID_BUTTON_4     (GUI_ID_USER + 0x08)
#define ID_BUTTON_5     (GUI_ID_USER + 0x09)
#define ID_BUTTON_6     (GUI_ID_USER + 0x0A)
#define ID_BUTTON_7     (GUI_ID_USER + 0x0B)
#define ID_BUTTON_8     (GUI_ID_USER + 0x0C)
#define ID_LISTVIEW_0     (GUI_ID_USER + 0x0D)

WM_HMEM timer;

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 444, 0, 346, 440, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 0, 0, 80, 36, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 0, 46, 80, 36, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 0, 97, 80, 36, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 0, 148, 80, 36, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_4, 0, 199, 80, 36, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_5, 0, 250, 80, 36, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_6, 0, 301, 80, 36, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_7, 0, 347, 80, 36, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_8, 0, 393, 80, 36, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 81, 1, 360, 440, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static WM_HWIN  hlist;
static int numROW;  //list当前行数
static u32 temp=0,count=0;//时间 和占空比
static u8  timeout,timeoutstate;//电机不转次数
static u8  timeout_value;//电机不转次数确定值
static u8  motorButton0State=0,motorStatedir1=0,motorStatedir2=0;//三个按键
static u8  motorMesureState=0;//测量状态
static u8  swichState=0;//电气开关状态
static u8  swichStateboot=0;//电气开关状态显示屏不跳
//static u8  timerState=0;//0为电气开关未动作或动作以后 定时器正常 1为电气开关动作之前定时器变小
static _calendar_obj rtc_config;
static void motor_ui_start(WM_MESSAGE * pMsg);
static void motor_ui_stop(WM_MESSAGE * pMsg);

static void motor_ui_var_init(){  //切换页面时变量变零
	numROW=0; //list当前行数
	temp=0;
	count=0;//时间 和占空比
	timeout=0;
	timeoutstate=0;//电机不转次数
	motorButton0State=0;
	motorStatedir1=0;
	motorStatedir2=0;//三个按键
	motorMesureState=0;//测量状态
	swichState=0;//电气开关状态
	swichStateboot=0;//电气开关状态显示屏不跳
	timeoutstate=0;
	Freq_ElectricSW_freq=0;
    Freq_ElectricSW_flag=0;
}

static void motor_ui_start(WM_MESSAGE * pMsg){
	char	  charBUF[8];
	WM_HWIN hItem;
	TIM3_PWM_Enable();
	MOTOR_stop();
	//count=50;//占空比初速度
	timeout=0;//电机不转次数
	timeoutstate=0;//电机还没开始转
	Freq_ElectricSW_flag =0;
	Freq_start=0;
	//MOTORP_out();
	hlist = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);//获取LISTVIEW句柄
	LISTVIEW_AddRow(hlist, NULL);			//添加1行
	numROW = LISTVIEW_GetNumRows(hlist);	//获取行数
	//if(!numROW) break;
	sprintf(charBUF, "%d", numROW);
	{
		int i;
		for(i=0;i<6;i++)
		LISTVIEW_SetItemBkColor(hlist,i,numROW-1,LISTVIEW_CI_UNSEL,GUI_WHITE);
	}
	LISTVIEW_SetItemText(hlist, 0, numROW-1, charBUF); 
	LISTVIEW_SetItemText(hlist, 5, numROW-1, "运行"); 
	motorButton0State =1;//停止按钮状态
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
	BUTTON_SetFont(hItem,&GUI_FontHZ16);		
	BUTTON_SetText(hItem, "停止");
	if(motorStatedir2==1)
	LISTVIEW_SetItemText(hlist, 4, numROW-1, "上行"); 
	else
	LISTVIEW_SetItemText(hlist, 4, numROW-1, "下行"); 
	TIM5_Cap_Enable();
	//TIM4_Enable();
	if(_config_content.nominalSpeed<1.0)
	{
		count=40;
	}else{
		count=_test_result_compare.init_v+13;
	}
	MOTOR_start(count);
	motorMesureState=1;//电机开始测量
}

static void motor_ui_stop(WM_MESSAGE * pMsg){
	 char	  charBUF[8];
	 WM_HWIN hItem;
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
	BUTTON_SetFont(hItem,&GUI_FontHZ16);		
	BUTTON_SetText(hItem, "开始");
	if(_config_content.nominalSpeed<1.0)
	{
		count=40;
	}else{
		count=_test_result_compare.init_v+13;
	}
	MOTOR_stop();
	//TIM3_PWM_Disable();
	TIM5_Cap_Disable();
	//TIM4_Disable();
	Freq_start=0;
	motorButton0State=0;//开始按钮状态
	motorMesureState=0;//电机停止测量

}


/*********************************************************************
*
*       _UserDraw
*
* Function description
*   This routine is called by the GRAPH object before anything is drawn
*   and after the last drawing operation.
*/
static void _UserDraw(WM_HWIN hWin, int Stage) {
  if (Stage == GRAPH_DRAW_LAST) {
    char acText[60]="";
    GUI_RECT Rect;
    GUI_RECT RectInvalid;
    int FontSizeY;
   if(swichState==1){
   	strcat(acText,"");
   	}else{
   	strcat(acText,"电气开关没有复位 ");
   	}

    GUI_SetFont(&GUI_FontHZ24);
    FontSizeY = GUI_GetFontSizeY();
    WM_GetInsideRect(&Rect);
    WM_GetInvalidRect(hWin, &RectInvalid);
    Rect.y1 = Rect.y0 + FontSizeY+ FontSizeY;
    GUI_SetColor(GUI_YELLOW);
    GUI_DispStringInRectEx(acText, &Rect, GUI_TA_CENTER, strlen(acText), GUI_ROTATE_0);
  }
}



/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       test_result
*/
static u8 test_result_func(){//检测判别
	if(((int)(_test_result.v1*1000)>_test_result_compare.result_v1)&&((int)(_test_result.v2*1000)<_test_result_compare.result_v2)&&((int)(_test_result.v2*1000)>(int)(_test_result.v1*1000)))
	return 1;
	else
	return 0;
}

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem,hWin;
  HEADER_Handle hHanle;	
  static GRAPH_DATA_Handle  pdataGRP;
  int     NCode;
  int     Id;
  char	  charBUF[36];
  static  u32 Val = 0,time=0,Valswitch;
  float Valfloat;
  GRAPH_SCALE_Handle hScaleV;
  GRAPH_SCALE_Handle hScaleH;

  // USER START (Optionally insert additional variables)
  // USER END
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
		//
		// Initialization of 'Framewin'
		//
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 36);
		FRAMEWIN_SetFont(hItem, &GUI_FontHZ16);
		FRAMEWIN_SetText(hItem, COMPANYNAME);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Graph'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		GRAPH_SetGridVis(hItem, 1);
		GRAPH_SetGridFixedX(hItem, 1);
		GRAPH_SetGridDistY(hItem, _test_result_compare.scale);
		GRAPH_SetGridDistX(hItem, 50);
		//GRAPH_SetUserDraw(hItem, _UserDraw);
		hScaleV = GRAPH_SCALE_Create(30, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, _test_result_compare.scale);//创建和增加垂直范围尺度标签
		GRAPH_SCALE_SetFactor(hScaleV,0.01);
		GRAPH_SCALE_SetNumDecs(hScaleV,2);
		GRAPH_SCALE_SetTextColor(hScaleV, GUI_RED); 								//设置标签字体颜色
		GRAPH_AttachScale(hItem, hScaleV);											//将标签添加到垂直方向
		hScaleH = GRAPH_SCALE_Create(420, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);	//创建和增加水平范围尺度标签
		GRAPH_SCALE_SetFactor(hScaleH,0.02);
		GRAPH_SCALE_SetNumDecs(hScaleH,2);
		GRAPH_SCALE_SetTextColor(hScaleH, GUI_DARKGREEN);							//设置字体颜色
		GRAPH_AttachScale(hItem, hScaleH);											//添加到水平方向
		pdataGRP = GRAPH_DATA_YT_Create(GUI_GREEN, 500/*最大数据个数*/, 0, 0);		//创建一个数据曲线,可创建多个曲线
		GRAPH_AttachData(hItem, pdataGRP);											//为绘图控件添加数据对象
		GRAPH_DATA_YT_SetAlign(pdataGRP, GRAPH_ALIGN_LEFT);
        //GRAPH_DATA_YT_MirrorX (pdataGRP, 1);
		//以下是手动加入
		/*SCROLLBAR_CreateAttached(hItem, 0);	//创建1个水平滚动条,会自动附贴到LISTVIEW
		hWin = WM_GetScrollbarH(hItem);
		SCROLLBAR_SetWidth(hWin, 18);		//设置滚动条宽
		SCROLLBAR_SetThumbSizeMin(18);		//设置拖块的最小长度
		SCROLLBAR_CreateAttached(hItem, SCROLLBAR_CF_VERTICAL);//创建1个垂直滚动条
		hWin = WM_GetScrollbarV(hItem);
		SCROLLBAR_SetWidth(hWin, 18);*/
		//
		// Initialization of 'Listview'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
		hHanle = LISTVIEW_GetHeader(hItem);
		HEADER_SetFont(hHanle,&GUI_FontHZ12);
		LISTVIEW_SetFont(hItem,&GUI_FontHZ12 );
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
		LISTVIEW_AddColumn(hItem, 55, "序号", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 55, "速度1", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 55, "速度2", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_SetGridVis(hItem, 1);
		LISTVIEW_AddColumn(hItem, 55, "结果", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 55, "方向", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 55, "状态", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_SetHeaderHeight(hItem, 24);
		
		//以下是手动加入
		SCROLLBAR_CreateAttached(hItem, 0);	//创建1个水平滚动条,会自动附贴到LISTVIEW
		hWin = WM_GetScrollbarH(hItem);
		SCROLLBAR_SetWidth(hWin, 18);		//设置滚动条宽
		SCROLLBAR_SetThumbSizeMin(18);		//设置拖块的最小长度
		SCROLLBAR_CreateAttached(hItem, SCROLLBAR_CF_VERTICAL);//创建1个垂直滚动条
		hWin = WM_GetScrollbarV(hItem);
		SCROLLBAR_SetWidth(hWin, 18);


		//
		// Initialization of 'Button'
		//

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "开始");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "电机反转");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "上行测量");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "删除");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "保存");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "打印");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "参数设置");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "客户");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "主界面");		
		if(_test_result_compare.result_v1<1200){//200ms周期 小于1m/s以下的次数判断多
			timeout_value=25;
		}else{
			timeout_value=10;
		}
		timer = WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 1, 30, 0); //创建一个软件定时器 10ms

		// USER START (Optionally insert additional code for further widget initialization)
		// USER END
    break;
  case WM_TIMER://定时器消息(定时到时程序跑到这里)
		

		if((KEY_sw2_detect_swich(1)==SW2_PRES)||(KEY_sw3_detect_swich(1)==SW3_PRES)){//电气开关判断
			swichState =0;
			if(swichStateboot==0){
			hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
			GRAPH_SetUserDraw(hItem, _UserDraw);
			swichStateboot=1;
			}
			
			
		}else{
			swichState =1;//电气开关闭合
			if(swichStateboot==1){
			hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
			GRAPH_SetUserDraw(hItem, _UserDraw);
			swichStateboot=0;
			}
		}

		/*sw1启动开关*/
		if(swichState==1){//电气开关合上!
			if(KEY_sw1_detect(1)==SW1_PRES){
			Touch_Beep();
		  	
	        // USER START (Optionally insert code for reacting on notification message)
	        	if(motorButton0State==0){
				GRAPH_DATA_YT_Clear(pdataGRP);
				//timer = WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 1, 30, 0); //创建一个软件定时器 10ms
				
				motor_ui_start(pMsg);
	        	}
			else{
			
				motor_ui_stop(pMsg);
				hlist= WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
				//numROW = LISTVIEW_GetSel(hlist);		//获取当前选择行
				LISTVIEW_DeleteRow(hlist, numROW-1);		//删除当前选择行
				
			}
			}
		}
		
		
		if(motorMesureState ==1)//可以测量
		{
			if(timeoutstate==1)
			timeout++;

			
			if(Freq_Sample()){
				//timeout=0x80;//电机在转
				Freq_start=1;  //开始测量
				timeout=0;
				temp = Freq_value;
				//printf("Freq_value HIGH:%d ms\r\n",temp);//打印总的高点平时间
				Val = _test_result_compare.diameter*314;
				//printf("zhouchang:%d m \r\n",Val);
				Val = Val*1000/temp;//三位小数
				//printf("Val1:%d m/s\r\n",Val);
				
				
				if((KEY_sw2_detect(0)==SW2_PRES)||(KEY_sw3_detect(0)==SW3_PRES)){//电气开关动作
					
						//Freq_ElectricSW_flag=0;
						timeoutstate =1;
						//temp = Freq_value;
						//printf("Freq_value HIGH:%d ms\r\n",temp);//打印总的高点平时间
						Valswitch = _test_result_compare.diameter*314;
						//printf("zhouchang:%d m \r\n",Val);
						Valswitch = Valswitch*1000/Freq_value;//三位小数
						_test_result.v1 = ((float)Valswitch*1.0)/1000;
						//printf("!!!!!!!_test_result v1:%.3f m/s\r\n",_test_result.v1);
						sprintf(charBUF, "%.3f", _test_result.v1);
						strcat(charBUF, "m/s");
						LISTVIEW_SetItemText(hlist, 1, numROW-1, charBUF); 	
						
					}
				if(timeoutstate!=1){//电气开关还没有动作显示V1 list
					Valfloat=((float)Val*1.0)/1000;
					sprintf(charBUF, "%.3f", Valfloat);
					strcat(charBUF, "m/s");
					LISTVIEW_SetItemText(hlist, 1, numROW-1, charBUF); 	//v1显示
				}else{
					Valfloat=((float)Val*1.0)/1000;
					sprintf(charBUF, "%.3f", Valfloat);
					strcat(charBUF, "m/s");
					LISTVIEW_SetItemText(hlist, 2, numROW-1, charBUF); 	//v2动态显示
				}
					if(_config_content.nominalSpeed<1.0){
						if(Val<_test_result_compare.accelerate_v1)
						count=count+3;
						else if((Val>=_test_result_compare.accelerate_v1)&&(Val<_test_result_compare.accelerate_v2)){
						count=count+2;
						}else if (Val>=_test_result_compare.accelerate_v2){
							count=count +1;

						}
					}else{
						if(Val<_test_result_compare.accelerate_v1)
						count=count+5;
						else if((Val>=_test_result_compare.accelerate_v1)&&(Val<_test_result_compare.accelerate_v2)){
						count=count+2;
						}else if (Val>=_test_result_compare.accelerate_v2){
						count=count +1;

					}
					}
				MOTOR_start(count);
 			
		}
		
		
		//可以在这里获取速度值
		
		if (timeout>timeout_value)//不转次数超过3次
		{
			//timeout = 0;
			//printf("timeout:%d \r\n",timeout);
			timeoutstate=0;
			MOTOR_stop();
			//TIM3_PWM_Disable();
			TIM5_Cap_Disable();
			//TIM4_Disable();
			Val=0;
			motorMesureState=0;
			motorButton0State =0;//停止按钮状态
			Val = _test_result_compare.diameter*314;
			Val = (Val*1000)/(the_end_Value());//三位小数
			//printf("?????_test_resultV2:%d m/s\r\n",Val);
			_test_result.v2 = Val/(float)1000;
			Val=0;
			//printf("!!!!!!!_test_resultV2:%f m/s\r\n",_test_result.v2);
			sprintf(charBUF, "%.3f", _test_result.v2);
			strcat(charBUF, "m/s");
			LISTVIEW_SetItemText(hlist, 2, numROW-1, charBUF); 	//v2最终
			
			LISTVIEW_SetItemText(hlist, 5, numROW-1, "停止"); 	//状态显示
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,&GUI_FontHZ16);		
			BUTTON_SetText(hItem, "开始");
			if(test_result_func())
			LISTVIEW_SetItemText(hlist, 3, numROW-1, "合格"); 	//结果显示
			else{
				LISTVIEW_SetItemText(hlist, 3, numROW-1, "不合格"); 	//结果显示
				{
				int i;
				for(i=0;i<6;i++)
				LISTVIEW_SetItemBkColor(hlist,i,numROW-1,LISTVIEW_CI_UNSEL,GUI_RED);
				}
			}
		}else{
			if(Val<10000){//滤波
				GRAPH_DATA_YT_AddValue(pdataGRP, (I16)(Val/10));		//赋值到曲线
				//_test_result.v2 = (float)Val/1000;
				//printf("!!!!!!!_test_result:%f m/s\r\n",_test_result.v1);
			}
		}
	}	
	
	WM_RestartTimer(pMsg->Data.v, 200);

	if(WM_IsCompletelyCovered(pMsg->hWin)) break;		//当切换到其他页面什么都不做
	break;		
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc); 
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
		if(swichState==1){//电气开关合上!
		Touch_Beep();
	  	
        // USER START (Optionally insert code for reacting on notification message)
        	if(motorButton0State==0){
			GRAPH_DATA_YT_Clear(pdataGRP);
			//timer = WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 1, 30, 0); //创建一个软件定时器 10ms
			
			motor_ui_start(pMsg);
        	}
		else{
		
			motor_ui_stop(pMsg);
			hlist= WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
			//numROW = LISTVIEW_GetSel(hlist);		//获取当前选择行
			LISTVIEW_DeleteRow(hlist, numROW-1);		//删除当前选择行
			
		}
		}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        /*if(timer!=NULL)
        //WM_DeleteTimer (timer);
		count=50;
		MOTOR_stop();
		TIM3_PWM_Disable();
		TIM5_Cap_Disable();*/
		 if(0==motorButton0State){
		Touch_Beep();
		if(motorStatedir1==1){
			
			MOTORP_out();
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem,&GUI_FontHZ16);		
			BUTTON_SetText(hItem, "电机正转");
			motorStatedir1=0;
			 
		}else{
		 	MOTORN_out();
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem,&GUI_FontHZ16);		
			BUTTON_SetText(hItem, "电机反转");
			motorStatedir1=1;
			}
		}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        if(0==motorButton0State){
	        Touch_Beep();
	        if(motorStatedir2==1){
				
				MOTORP_out();

				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
				BUTTON_SetFont(hItem,&GUI_FontHZ16);		
				BUTTON_SetText(hItem, "上行测量");
				motorStatedir2=0;
				 
			}else{

				MOTORN_out();
			 	//MOTORN_out();
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
				BUTTON_SetFont(hItem,&GUI_FontHZ16);		
				BUTTON_SetText(hItem, "下行测量");
				motorStatedir2=1;
			}
        	}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        if(0==motorButton0State){
		hlist= WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
		numROW = LISTVIEW_GetSel(hlist);		//获取当前选择行
		LISTVIEW_DeleteRow(hlist, numROW);		//删除当前选择行
        	}
		break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
         if(0==motorButton0State){

         	}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_5: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
	 if(0==motorButton0State){
	 	hlist = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);//获取LISTVIEW句柄
		//LISTVIEW_AddRow(hlist, NULL);			//添加1行
		numROW = LISTVIEW_GetNumRows(hlist);	//获取行数
		if(!numROW) break;
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"————限速器测试报告————\r\n");

		sprintf(charBUF, "%d", calendar.w_year);
		strcat(charBUF, "-");
		usart_send_string(USART1,charBUF);

		sprintf(charBUF, "%d", calendar.w_month);
		strcat(charBUF, "-");
		usart_send_string(USART1,charBUF);

		sprintf(charBUF, "%d", calendar.w_date);
		strcat(charBUF, "-");
		usart_send_string(USART1,charBUF);

		sprintf(charBUF, "%d", calendar.hour);
		strcat(charBUF, "-");
		usart_send_string(USART1,charBUF);

		sprintf(charBUF, "%d", calendar.min);
		strcat(charBUF, "-");
		usart_send_string(USART1,charBUF);

		sprintf(charBUF, "%d", calendar.sec);
		strcat(charBUF, "\r\n");
		usart_send_string(USART1,charBUF);

		usart_send_string(USART1,"用户信息:");
		sprintf(charBUF, "%s", _login_content.userNAME);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"\r\n");

		usart_send_string(USART1,"电梯制造商:");
		sprintf(charBUF, "%s", _login_content.liftManufactureNAME);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"\r\n");

		usart_send_string(USART1,"电梯型号:");
		sprintf(charBUF, "%s", _login_content.liftManufactureMODEL);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"\r\n");

		usart_send_string(USART1,"限速器制造商:");
		sprintf(charBUF, "%s", _login_content.govenorManufactureNAME);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"\r\n");

		usart_send_string(USART1,"限速器型号:");
		sprintf(charBUF, "%s", _login_content.govenorfactureMODEL);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"\r\n");

		usart_send_string(USART1,"限速器编号:");
		sprintf(charBUF, "%s", _login_content.govenorfactureNAME);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"\r\n");

		usart_send_string(USART1,"限速器额定速度:");
		sprintf(charBUF, "%.3f",_config_content.nominalSpeed);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"(m/s)\r\n");

		usart_send_string(USART1,"合格范围:");
		sprintf(charBUF, "%.3f",(float)_test_result_compare.result_v1/1000);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"_");
		sprintf(charBUF, "%.3f",(float)_test_result_compare.result_v2/1000);
		usart_send_string(USART1,charBUF);
		usart_send_string(USART1,"(m/s)\r\n");
		
		usart_send_string(USART1,"序号 V1(m/s) V2(m/s) 方向 结果\r\n");

		{
		u8 i=0;
		u8 cha[36];
			for(i=0;i<numROW;i++){
				sprintf(charBUF, "%d",i+1);
				usart_send_string(USART1,charBUF);
				usart_send_string(USART1,"  ");
				
				LISTVIEW_GetItemText(hlist, 1,i, charBUF,30);
				sprintf(cha, "%s",charBUF);
				usart_send_string(USART1,cha);
				usart_send_string(USART1," ");
				
				LISTVIEW_GetItemText(hlist, 2,i, charBUF,30);
				sprintf(cha, "%s",charBUF);
				usart_send_string(USART1,cha);
				usart_send_string(USART1," ");

				LISTVIEW_GetItemText(hlist, 4,i, charBUF,30);
				sprintf(cha, "%s",charBUF);
				usart_send_string(USART1,cha);
				usart_send_string(USART1," ");

				LISTVIEW_GetItemText(hlist, 3,i, charBUF,30);
				sprintf(cha, "%s",charBUF);
				usart_send_string(USART1,cha);
				usart_send_string(USART1," ");

				usart_send_string(USART1,"\r\n");

			}
		}
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,COMPANYNAME);
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"\r\n");
		usart_send_string(USART1,"\r\n");


	#if 0
		hlist = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);//获取LISTVIEW句柄
		//LISTVIEW_AddRow(hlist, NULL);			//添加1行
		numROW = LISTVIEW_GetNumRows(hlist);	//获取行数
		if(!numROW) break;
		//sprintf(charBUF, "%d", numROW-1);
		/*LISTVIEW_SetItemText(hlist, 0, numROW-1, charBUF); 
		LISTVIEW_SetItemText(hlist, 1, numROW-1, "abc"); 
		LISTVIEW_SetItemText(hlist, 2, numROW-1, "neqee.com"); 
		LISTVIEW_SetItemText(hlist, 3, numROW-1, "neqee.com");
		LISTVIEW_SetItemText(hlist, 4, numROW-1, "neqee.com");
		LISTVIEW_SetItemText(hlist, 5, numROW-1, "你好");*/

		
		//printf("!!!!!!!_test_result:%f m/s\r\n",_test_result.v1);
		printf("\r\n");
		printf("\r\n");
		printf("————限速器测试报告————\r\n");
		printf("%d-",calendar.w_year);
		printf("%d-",calendar.w_month);
		printf("%d ",calendar.w_date);
		printf("%d:",calendar.hour);
		printf("%d:",calendar.min);
		printf("%d\r\n",calendar.sec);
		//sprintf(charBUF, "%.3f", _test_result.v2);
		printf("用户信息:");
		{
			u8 i=0;
			/*for(i=0;i<_login_content.userNAMElong;i++){
				printf("%s",_login_content.userNAME[i]);
			}*/
			//&_login_content.userNAME[_login_content.userNAMElong]="/0";
			sprintf(charBUF, "%s", _login_content.userNAME);
			printf("%s",charBUF);
			printf("\r\n");
		}
		printf("电梯制造商:");
		{
			u8 i=0;
			/*for(i=0;i<_login_content.liftManufactureNAMElong;i++){
				printf("%s",_login_content.liftManufactureNAME);
			}*/
			//&_login_content.liftManufactureNAME[_login_content.liftManufactureNAMElong]="/0";
			sprintf(charBUF, "%s", _login_content.liftManufactureNAME);
			printf("%s",charBUF);
			printf("\r\n");
		}
		printf("电梯型号:");
		{
			u8 i=0;
			/*for(i=0;i<_login_content.liftManufactureMODELlong;i++){
				printf("%s",_login_content.liftManufactureMODEL);
			}*/
			//&_login_content.liftManufactureMODEL[_login_content.liftManufactureMODELlong]="/0";
			sprintf(charBUF, "%s", _login_content.liftManufactureMODEL);
			printf("%s",charBUF);
			printf("\r\n");
		}
		printf("限速器制造商:");
		{
			u8 i=0;
			/*for(i=0;i<_login_content.govenorManufactureNAMElong;i++){
				printf("%s",_login_content.govenorManufactureNAME);
			}*/
			//&_login_content.govenorManufactureNAME[_login_content.govenorManufactureNAMElong]="/0";
			sprintf(charBUF, "%s", _login_content.govenorManufactureNAME);
			printf("%s",charBUF);
			printf("\r\n");
		}
		printf("限速器型号:");
		{
			u8 i=0;
			/*for(i=0;i<_login_content.govenorfactureMODELlong;i++){
				printf("%s",_login_content.govenorfactureMODEL);
			}*/
			sprintf(charBUF, "%s", _login_content.govenorfactureMODEL);
			//&_login_content.govenorfactureMODEL[_login_content.govenorfactureMODELlong]="/0";
			printf("%s",charBUF);
			printf("\r\n");
		}
		printf("限速器编号:");
		{
			u8 i=0;
			/*for(i=0;i<_login_content.govenorfactureNAMElong;i++){
				printf("%s",_login_content.govenorfactureNAME);
			}*/
			//&_login_content.govenorfactureNAME[_login_content.govenorfactureNAMElong]="/0"；
			sprintf(charBUF, "%s", _login_content.govenorfactureNAME);
			printf("%s",charBUF);
			printf("\r\n");
		}
		printf("限速器额定速度:%0.3f(m/s)\r\n",_config_content.nominalSpeed);
		printf("合格范围:");
		printf("%0.3f_%0.3f(m/s)\r\n",(float)_test_result_compare.result_v1/1000,(float)_test_result_compare.result_v2/1000);
		printf("序号 V1(m/s) V2(m/s) 方向 结果\r\n");

		{
			u8 i=0;
			for(i=0;i<numROW;i++){
			printf("%d  ",i+1);
			LISTVIEW_GetItemText(hlist, 1,i, charBUF,30);
			printf("%s ",charBUF);
			LISTVIEW_GetItemText(hlist, 2,i, charBUF,30);
			printf("%s ",charBUF);
			LISTVIEW_GetItemText(hlist, 4,i, charBUF,30);
			printf("%s ",charBUF);
			LISTVIEW_GetItemText(hlist, 3,i, charBUF,30);
			printf("%s ",charBUF);
			printf("\r\n");
			}
		}
		printf("\r\n");
		printf("上海盛蒂斯自动化设备股份有限公司\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
#endif
	 	}
	 
 		
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
	
      }
      break;
    case ID_BUTTON_6: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
         if(0==motorButton0State){
		 motor_ui_var_init();
		GUI_EndDialog(pMsg->hWin, 0);
		ui_page.configUi=CreateFramewinConfigUI();
		ui_page.windowSKB=CreateWindowSKB();
		WM_AttachWindow(ui_page.windowSKB, ui_page.configUi);
		WM_HideWindow(ui_page.windowSKB);
         }
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_7: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
         if(0==motorButton0State){
		 	motor_ui_var_init();
		GUI_EndDialog(pMsg->hWin, 0);
		ui_page.logUi=CreateFramewinLogUi();
		ui_page.windowSKB=CreateWindowSKB();
		WM_AttachWindow(ui_page.windowSKB, ui_page.logUi);
		WM_HideWindow(ui_page.windowSKB);
         	}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_8: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
         if(0==motorButton0State){
		 	motor_ui_var_init();
		GUI_EndDialog(pMsg->hWin, 0);
		ui_page.index=CreateFramewinIndex();
         	}
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTVIEW_0: // Notifications sent by 'Listview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN CreateFramewinMotoCtrlUI(void);
WM_HWIN CreateFramewinMotoCtrlUI(void) {
	WM_HWIN hWin;
	button_Press.windowSKB=0;
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	//WM_CreateTimer(WM_GetClientWindow(hWin), 1, 100, 0); //创建一个软件定时器 30ms
	MOTORP_out();
	return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
