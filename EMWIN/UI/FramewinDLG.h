#ifndef _FRAMEWINDLG_H
#define _FRAMEWINDLG_H
#include "sys.h"
#include "WM.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F103战舰开发板
//STemWin GUIBulider使用
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/4/15
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
#define SHENGDISI

#if defined(SHENGDISI)
#define COMPANYNAME   "上海盛蒂斯自动化设备股份有限公司"
#define PHONE "电话 ：+86-021-54884259"
#define NET "http://www.shengdisi.com"
#define ADDRES "盛蒂斯 股票代码：839579"


#else
#define COMPANYNAME   "邦亿精密量仪(上海)有限公司"
#define PHONE "电话 ：021-37890161"
#define NET "www.b-yes.cn"
#define ADDRES "上海市松江区宝胜路18号"
	
#endif

typedef struct 
{
	WM_HWIN index;
	WM_HWIN timesetui;
	WM_HWIN logUi;			
	WM_HWIN configUi;
	WM_HWIN  windowSKB;
	WM_HWIN  motorCtrlUI;
	WM_HWIN  klindlistbox;	
	WM_HWIN  versionUI;
}uiPage;	
extern uiPage ui_page;	//UI界面

typedef struct 
{
	u8 windowSKB;//1windowSKB按下 0windowSKB释放
}buttonPress;
extern buttonPress button_Press;	


WM_HWIN CreateFramewin(void);
WM_HWIN CreateWindowSKB(void);
WM_HWIN CreateFramewinTimeSet(void);
WM_HWIN CreateFramewinIndex(void);
WM_HWIN CreateFramewinLogUi(void);
WM_HWIN CreateFramewinConfigUI(void);
WM_HWIN CreateFramewinMotoCtrlUI(void);
void DelWindowSKB(void);//关闭键盘
void setWindowSKBtimerBoot(unsigned char statue);//设置键盘编辑框为空 0为空 1为和聚焦编辑框的值相同
unsigned char getWindowSKBtimerBoot();//获取键盘编辑框状态
WM_HWIN CreateFramewinKindListBox(void); //限速器种类
WM_HWIN CreateFramewinVersion(void);
extern WM_HWIN hPage[3];

#endif
