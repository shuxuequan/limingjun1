#ifndef _FRAMEWINDLG_H
#define _FRAMEWINDLG_H
#include "sys.h"
#include "WM.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103ս��������
//STemWin GUIBuliderʹ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/15
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//#define SHENGDISI

#if defined(SHENGDISI)
#define COMPANYNAME   "�Ϻ�ʢ��˹�Զ����豸�ɷ����޹�˾"
#define PHONE "�绰 ��+86-021-54884259"
#define NET "http://www.shengdisi.com"
#define ADDRES "ʢ��˹ ��Ʊ���룺839579"


#else
#define COMPANYNAME   "���ھ�������(�Ϻ�)���޹�˾"
#define PHONE "�绰 ��021-37890161"
#define NET "www.b-yes.cn"
#define ADDRES "�Ϻ����ɽ�����ʤ·18��"
	
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
extern uiPage ui_page;	//UI����

WM_HWIN CreateFramewin(void);
WM_HWIN CreateWindowSKB(void);
WM_HWIN CreateFramewinTimeSet(void);
WM_HWIN CreateFramewinIndex(void);
WM_HWIN CreateFramewinLogUi(void);
WM_HWIN CreateFramewinConfigUI(void);
WM_HWIN CreateFramewinMotoCtrlUI(void);
void DelWindowSKB(void);//�رռ���
void setWindowSKBtimerBoot(unsigned char statue);//���ü��̱༭��Ϊ�� 0Ϊ�� 1Ϊ�;۽��༭���ֵ��ͬ
unsigned char getWindowSKBtimerBoot();//��ȡ���̱༭��״̬
WM_HWIN CreateFramewinKindListBox(void); //����������
WM_HWIN CreateFramewinVersion(void);
extern WM_HWIN hPage[3];

#endif
