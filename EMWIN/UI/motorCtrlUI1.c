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
static int	  numROW;  //list当前行数
static u32 temp=0,count=0;//时间 和占空比
static u8 timeout,timeoutstate;//电机不转次数
static u8 motorButton0State=0,motorStatedir1=0,motorStatedir2=0;//三个按键
static u8 motorMesureState=0;//测量状态
static u8 swichState=0;//测量状态
static void motor_ui_start(WM_MESSAGE * pMsg);
static void motor_ui_stop(WM_MESSAGE * pMsg);

static void motor_ui_start(WM_MESSAGE * pMsg){
	 char	  charBUF[8];
	 WM_HWIN hItem;
	TIM3_PWM_Enable();
	MOTOR_stop();
	count=50;//占空比初速度
	timeout=0;//电机不转次数
	timeoutstate=0;//电机还没开始转
	TIM5_Cap_Enable();
	MOTOR_start(count);
	//MOTORP_out();
	hlist = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);//获取LISTVIEW句柄
	LISTVIEW_AddRow(hlist, NULL);			//添加1行
	numROW = LISTVIEW_GetNumRows(hlist);	//获取行数
	//if(!numROW) break;
	sprintf(charBUF, "%d", numROW-1);
	LISTVIEW_SetItemText(hlist, 0, numROW-1, charBUF); 	
	motorButton0State =1;//停止按钮状态
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
	BUTTON_SetFont(hItem,&GUI_FontHZ16);		
	BUTTON_SetText(hItem, "停止");
	motorMesureState=1;//电机开始测量
}

static void motor_ui_stop(WM_MESSAGE * pMsg){
	 char	  charBUF[8];
	 WM_HWIN hItem;
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
	BUTTON_SetFont(hItem,&GUI_FontHZ16);		
	BUTTON_SetText(hItem, "开始");
	count=50;
	MOTOR_stop();
	TIM3_PWM_Disable();
	TIM5_Cap_Disable();
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
char acText[60];

    GUI_RECT Rect;
    GUI_RECT RectInvalid;
    int FontSizeY;
	if (Stage == GRAPH_DRAW_LAST) {
	if(swichState==1){
		strcat(acText,"x/div = 0.1s y/div = 0.21m/s");
	}else{
		strcat(acText,"x/div = 0.1s y/div = 0.21m/s电气开关没有复位");
	}
    GUI_SetFont(&GUI_FontHZ12);
    FontSizeY = GUI_GetFontSizeY();
    WM_GetInsideRect(&Rect);
    WM_GetInvalidRect(hWin, &RectInvalid);
    Rect.y1 = Rect.y0 + FontSizeY;
    GUI_SetColor(GUI_YELLOW);
    GUI_DispStringInRectEx(acText, &Rect, GUI_TA_LEFT, strlen(acText), GUI_ROTATE_0);
  }
}


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  
 
  HEADER_Handle hHanle;	
  static GRAPH_DATA_Handle  pdataGRP;
  int     NCode;
  int     Id;
  char	  charBUF[8];
  static  int Val = 0,time=0;
  float recordV1;
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
		FRAMEWIN_SetText(hItem, "上海盛蒂斯自动化设备股份有限公司");
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Graph'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		GRAPH_SetGridVis(hItem, 1);
		GRAPH_SetGridFixedX(hItem, 1);
		
		GRAPH_SetGridDistY(hItem, 20);
		GRAPH_SetGridDistX(hItem, 50);
		//GRAPH_SetUserDraw(hItem, _UserDraw);
		hScaleV = GRAPH_SCALE_Create(30, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 20);//创建和增加垂直范围尺度标签
		GRAPH_SCALE_SetFactor(hScaleV,0.01);
		GRAPH_SCALE_SetNumDecs(hScaleV,2);
		GRAPH_SCALE_SetTextColor(hScaleV, GUI_RED); 								//设置标签字体颜色
		GRAPH_AttachScale(hItem, hScaleV);											//将标签添加到垂直方向
		hScaleH = GRAPH_SCALE_Create(420, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 100);	//创建和增加水平范围尺度标签
		GRAPH_SCALE_SetFactor(hScaleH,0.01);
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
		hItem = WM_GetScrollbarH(hItem);
		SCROLLBAR_SetWidth(hItem, 18);		//设置滚动条宽
		SCROLLBAR_SetThumbSizeMin(18);		//设置拖块的最小长度
		SCROLLBAR_CreateAttached(hItem, SCROLLBAR_CF_VERTICAL);//创建1个垂直滚动条
		hItem = WM_GetScrollbarV(hItem);
		SCROLLBAR_SetWidth(hItem, 18);


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


		// USER START (Optionally insert additional code for further widget initialization)
		// USER END
    break;
  case WM_TIMER://定时器消息(定时到时程序跑到这里)
		WM_RestartTimer(pMsg->Data.v, 200);
		if(WM_IsCompletelyCovered(pMsg->hWin)) break;		//当切换到其他页面什么都不做
		//Val++;
		/*if((KEY_sw2_detect_swich(1)==SW2_PRES)||(KEY_sw3_detect_swich(1)==SW3_PRES)){
			swichState=0;//限位开关没有复位
			//hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
			//GRAPH_SetUserDraw(hItem, _UserDraw);
		}else{
			swichState =1;//限位开关复位
			//hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
			//GRAPH_SetUserDraw(hItem, _UserDraw);
		}*/
		
		if(motorMesureState ==1)
		{
			if(timeoutstate==1)
			timeout++;

			/*if(TIM_GetCapture2(TIM3)==899){
				count=0;
				//TIM_SetCompare2(TIM3,0);	
				}*/
	 		//if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
			//{
				/*temp=TIM5CH1_CAPTURE_STA&0X3F;
				temp*=65536;//溢出时间总和
				temp+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间*/
			if(Freq_Sample()){
				//timeout=0x80;//电机在转
				timeout=0;
				temp = Freq_value;
				printf("HIGH:%d ms\r\n",temp);//打印总的高点平时间
				//TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
				Val = 24*314;
				//printf("zhouchang:%d m \r\n",Val);
				Val = Val*100/temp;
				printf("Val1:%d m/s\r\n",Val);
				
				if(timeoutstate!=1){//电气开关还没有动作显示V1 list
					sprintf(charBUF, "%.2f", (float)Val/100);
					strcat(charBUF, "m/s");
					LISTVIEW_SetItemText(hlist, 1, numROW-1, charBUF); 	
				}else{
					sprintf(charBUF, "%.2f", (float)Val/100);
					strcat(charBUF, "m/s");
					LISTVIEW_SetItemText(hlist, 2, numROW-1, charBUF); 
				}
				if((KEY_sw2_detect(0)==SW2_PRES)||(KEY_sw3_detect(0)==SW3_PRES)){
					
						
						char intTofloat[5]="0.00",temp_intTofloat[2];
						int numb[4];
						timeoutstate =1;
						/*numb[0] = Val/100;
						numb[2] = (Val%100)/10;
						numb[3] = Val%10;
						sprintf(temp_intTofloat, " %d" , numb[0]);
						printf("!!!!!!!_test_result0:%s m/s\r\n",temp_intTofloat);
						strcat(intTofloat, ".");
						sprintf(temp_intTofloat, " %d" , numb[2]);
						printf("!!!!!!!_test_result0:%s m/s\r\n",temp_intTofloat);
						strcat(intTofloat, temp_intTofloat);
						sprintf(temp_intTofloat, " %d" , numb[3]);
						printf("!!!!!!!_test_result2:%s m/s\r\n",temp_intTofloat);
						strcat(intTofloat, temp_intTofloat);*/
						_test_result.v1 = (float)Val/100;
						printf("!!!!!!!_test_result:%f m/s\r\n",_test_result.v1);
						sprintf(charBUF, "%.2f", _test_result.v1);
						strcat(charBUF, "m/s");
						LISTVIEW_SetItemText(hlist, 1, numROW-1, charBUF); 	
						
					}
					if(Val<180)
					count=count+5;
					else if(Val>=180||Val<220){
					count=count+2;
					}else if (Val>220){
					count=count +1;
					}
				MOTOR_start(count);
 			
			}
		
		
		//可以在这里获取速度值
		if (timeout>3)//不转次数超过3次
		{
			//timeout = 0;
			timeoutstate=0;
			MOTOR_stop();
			TIM3_PWM_Disable();
			TIM5_Cap_Disable();
			Val=0;
			motorMesureState=0;
			motorButton0State =0;//停止按钮状态
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,&GUI_FontHZ16);		
			BUTTON_SetText(hItem, "开始");
		}else{
			if(Val<1000){//滤波
				GRAPH_DATA_YT_AddValue(pdataGRP, (I16)(Val));		//赋值到曲线
				//_test_result.v2 = (float)Val/100;
			}
		}
	}	
	break;		
  case WM_NOTIFY_PARENT: //开始
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
		//if(swichState==1){
		Touch_Beep();
	  	
        // USER START (Optionally insert code for reacting on notification message)
        	if(motorButton0State==0){
			GRAPH_DATA_YT_Clear(pdataGRP);
			//timer = WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 1, 30, 0); //创建一个软件定时器 10ms
			
			motor_ui_start(pMsg);
        	}
		else{
		
			motor_ui_stop(pMsg);
			
		}
		//}
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
				MOTORN_out();
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
				BUTTON_SetFont(hItem,&GUI_FontHZ16);		
				BUTTON_SetText(hItem, "上行测量");
				motorStatedir2=0;
				 
			}else{
			 	MOTORP_out();
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
		LISTVIEW_AddRow(hlist, NULL);			//添加1行
		numROW = LISTVIEW_GetNumRows(hlist);	//获取行数
		if(!numROW) break;
		sprintf(charBUF, "%d", numROW-1);
		LISTVIEW_SetItemText(hlist, 0, numROW-1, charBUF); 
		LISTVIEW_SetItemText(hlist, 1, numROW-1, "abc"); 
		LISTVIEW_SetItemText(hlist, 2, numROW-1, "neqee.com"); 
		LISTVIEW_SetItemText(hlist, 3, numROW-1, "neqee.com");
		LISTVIEW_SetItemText(hlist, 4, numROW-1, "neqee.com");
		LISTVIEW_SetItemText(hlist, 5, numROW-1, "你好");
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

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  WM_CreateTimer(WM_GetClientWindow(hWin), 1, 100, 0); //创建一个软件定时器 30ms
  MOTORP_out();
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
