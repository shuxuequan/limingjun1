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

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/


#define ID_FRAMEWIN_0     (GUI_ID_USER + 0x00)

#define ID_TEXT_0     (GUI_ID_USER + 0x01)
#define ID_TEXT_1     (GUI_ID_USER + 0x02)
#define ID_TEXT_2     (GUI_ID_USER + 0x03)
#define ID_TEXT_3     (GUI_ID_USER + 0x04)
#define ID_TEXT_4     (GUI_ID_USER + 0x05)
#define ID_TEXT_5     (GUI_ID_USER + 0x06)
#define ID_TEXT_6     (GUI_ID_USER + 0x07)
#define ID_TEXT_7     (GUI_ID_USER + 0x08)
#define ID_TEXT_8     (GUI_ID_USER + 0x09)


#define ID_TEXT_0_1     (GUI_ID_USER + 0x0A)
#define ID_TEXT_1_1     (GUI_ID_USER + 0x0B)
#define ID_TEXT_2_1     (GUI_ID_USER + 0x0C)
#define ID_TEXT_3_1     (GUI_ID_USER + 0x0D)
#define ID_TEXT_4_1     (GUI_ID_USER + 0x0E)
#define ID_TEXT_5_1     (GUI_ID_USER + 0x0F)
#define ID_TEXT_6_1     (GUI_ID_USER + 0x10)
#define ID_TEXT_7_1     (GUI_ID_USER + 0x11)
#define ID_TEXT_8_1     (GUI_ID_USER + 0x12)


#define  ID_EDIT_0     (GUI_ID_USER + 0x13)
#define  ID_EDIT_1     (GUI_ID_USER + 0x14)
#define  ID_EDIT_2     (GUI_ID_USER + 0x15)
#define  ID_EDIT_3     (GUI_ID_USER + 0x16)
#define  ID_EDIT_4     (GUI_ID_USER + 0x17)
#define  ID_EDIT_5     (GUI_ID_USER + 0x18)
#define  ID_EDIT_6     (GUI_ID_USER + 0x19)
#define  ID_EDIT_7     (GUI_ID_USER + 0x1A)
#define  ID_EDIT_8     (GUI_ID_USER + 0x1B)


#define ID_BUTTON_0     (GUI_ID_USER + 0x1C)
#define ID_BUTTON_1     (GUI_ID_USER + 0x1D)


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
	{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 265, 20, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 265, 60, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_2, 265, 100, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_3, 265, 140, 88, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_4, 265, 180, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_5, 265, 220, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_6, 265, 260, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_7, 265, 300, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_8, 265, 340, 85, 25, 0, 0x0, 0 },

	{ TEXT_CreateIndirect, "Text", ID_TEXT_0_1, 468, 20, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_1_1, 468, 60, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_2_1, 468, 100, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_3_1, 468, 140, 88, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_4_1, 468, 180, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_5_1, 468, 220, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_6_1, 468, 260, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_7_1, 468, 300, 85, 25, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_8_1, 468, 340, 85, 25, 0, 0x0, 0 },


	{ EDIT_CreateIndirect, "Edit", ID_EDIT_0, 368, 20, 85, 25, 0, 0x64, 0 },
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_1, 368, 60, 85, 25, 0, 0x64, 0 },
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_2, 368, 100, 85, 25, 0, 0x64, 0 },
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_3, 368, 140, 85, 25, 0, 0x64, 0 },
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_4, 368, 180, 85, 25, 0, 0x64, 0 },
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_5, 368, 220, 85, 25, 0, 0x64, 0 },
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_6, 368, 260, 85, 25, 0, 0x64, 0 },
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_7, 368, 300, 85, 25, 0, 0x64, 0 },
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_8, 368, 340, 85, 25, 0, 0x64, 0 },

	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 265, 390, 80, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 463, 390, 80, 30, 0, 0x0, 0 },

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
static void _cbDialog(WM_MESSAGE * pMsg) {
  	WM_HWIN hItem;
	int     NCode;
	int     Id,i;
	// USER START (Optionally insert additional variables)
	// USER END
	int posiX, posiY, sizeX[2], sizeY[2];
	char editBuffer[30];
	switch (pMsg->MsgId) {
		case WM_INIT_DIALOG:
		BUTTON_SetFocussable(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0), 0);
		BUTTON_SetFocussable(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1), 0);

		//
		// Initialization of 'Framewin'
		//
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 36);
		FRAMEWIN_SetFont(hItem, &GUI_FontHZ16);
		FRAMEWIN_SetText(hItem, "上海盛蒂斯自动化设备股份有限公司");
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "额定速度");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "节径");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "初速度");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "速度V1");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "速度V2");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "加速度A1");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "加速度A2");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "加速度A3");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "校准K");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "m/s");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "mm");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "m/s");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "m/s");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "m/s");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "m2/s");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "m2/s");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "m2/s");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

		//
		// Initialization of 'Text'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8_1);
		TEXT_SetFont(hItem, &GUI_FontHZ16);
		TEXT_SetText(hItem, "xxx");
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

		//
		// Initialization of 'Button'
		//

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "下一步");	
		//
		// Initialization of 'Button'
		//

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
		BUTTON_SetFont(hItem,&GUI_FontHZ16);		
		BUTTON_SetText(hItem, "返回");	


		// Initialization of 'Edit'
		//
		hItem= WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
		//EDIT_SetMaxLen(hItem,4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[0] , 2017, 2017, 3000, 0, 0);
		EDIT_SetText(hItem, "2.00");

		//
		// Initialization of 'Edit'
		//
		hItem= WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
		//EDIT_SetMaxLen(hItem,4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[1] , 1, 1, 12, 0,0);
		EDIT_SetText(hItem, "240.0");
		//
		// Initialization of 'Edit'
		//
		hItem= WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
		//EDIT_SetMaxLen(hItem,4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[2] , 1, 1, 31,0,0);
		EDIT_SetText(hItem, "0.40");
		//
		// Initialization of 'Edit'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
		//EDIT_SetMaxLen(hItem,4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[3] , 0, 0, 23, 0,0);
		EDIT_SetText(hItem, "1.70");
		//
		// Initialization of 'Edit'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_4);
		//EDIT_SetMaxLen(editbox[4],4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[4] , 0, 0, 59, 0, 0);
		EDIT_SetText(hItem, "2.10");

		// Initialization of 'Edit'
		//
		hItem= WM_GetDialogItem(pMsg->hWin, ID_EDIT_5);
		//EDIT_SetMaxLen(hItem,4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[0] , 2017, 2017, 3000, 0, 0);
		EDIT_SetText(hItem, "0.50");

		//
		// Initialization of 'Edit'
		//
		hItem= WM_GetDialogItem(pMsg->hWin, ID_EDIT_6);
		//EDIT_SetMaxLen(hItem,4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[1] , 1, 1, 12, 0,0);
		EDIT_SetText(hItem, "0.10");
		//
		// Initialization of 'Edit'
		//
		hItem= WM_GetDialogItem(pMsg->hWin, ID_EDIT_7);
		//EDIT_SetMaxLen(hItem,4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[2] , 1, 1, 31,0,0);
		EDIT_SetText(hItem, "0.02");
		//
		// Initialization of 'Edit'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_8);
		//EDIT_SetMaxLen(hItem,4);
		EDIT_SetFont(hItem,&GUI_FontHZ16);	
		//EDIT_SetDecMode(editbox[3] , 0, 0, 23, 0,0);
		EDIT_SetText(hItem, "01.0");

		// USER START (Optionally insert additional code for further widget initialization)
		// USER END
		break;
		case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
			case ID_EDIT_0:
			case ID_EDIT_1:
			case ID_EDIT_2:
			case ID_EDIT_3:
			case ID_EDIT_4:
			case ID_EDIT_5:
			case ID_EDIT_6:
			case ID_EDIT_7:
			case ID_EDIT_8:
				switch(NCode) {
				case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
					for(i=ID_EDIT_0; i<=ID_EDIT_8; i++) EDIT_SetFocussable(WM_GetDialogItem(pMsg->hWin, i), 0);	//disable focus
					EDIT_SetFocussable(WM_GetDialogItem(pMsg->hWin, Id), 1);
					WM_SetFocus(WM_GetDialogItem(WM_GetClientWindow(pMsg->hWin),Id));
					sizeX[0] = WM_GetWindowSizeX(WM_GetClientWindow(ui_page.configUi));
					sizeY[0] = WM_GetWindowSizeY(WM_GetClientWindow(ui_page.configUi));
					sizeX[1] = WM_GetWindowSizeX(ui_page.windowSKB);
					sizeY[1] = WM_GetWindowSizeY(ui_page.windowSKB);
					if(sizeX[0] - WM_GetWindowOrgX(pMsg->hWinSrc) < sizeX[1]) posiX = sizeX[0] - sizeX[1];
					else posiX = WM_GetWindowOrgX(pMsg->hWinSrc);
					if(sizeY[0]-WM_GetWindowOrgY(pMsg->hWinSrc)-WM_GetWindowSizeY(pMsg->hWinSrc) < sizeY[1])
					posiY = WM_GetWindowOrgY(pMsg->hWinSrc) - sizeY[1];
					else posiY = WM_GetWindowOrgY(pMsg->hWinSrc) + WM_GetWindowSizeY(pMsg->hWinSrc);

					WM_MoveTo(ui_page.windowSKB, posiX, posiY);
					WM_ShowWindow(ui_page.windowSKB);
					// USER END
					// USER END
					break;
					case WM_NOTIFICATION_RELEASED:
					// USER START (Optionally insert code for reacting on notification message)

					// USER END
					break;
					case WM_NOTIFICATION_VALUE_CHANGED:
					// USER START (Optionally insert code for reacting on notification message)
					// USER END
					break;
					// USER START (Optionally insert additional code for further notification handling)
					// USER END   
					}
				break;
		// USER START (Optionally insert additional message handling)
		// USER END
		case ID_BUTTON_0: // Notifications sent by 'Button'
			switch(NCode) {
				case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
				case WM_NOTIFICATION_RELEASED:
					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.nominalSpeed = atof(editBuffer);

					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.diameter = atof(editBuffer);

					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.initSpeed= atof(editBuffer);

					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.SpeedV1= atof(editBuffer);

					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_4);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.SpeedV2= atof(editBuffer);

					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_5);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.accelerate1= atof(editBuffer);

					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_6);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.accelerate2= atof(editBuffer);

					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_7);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.accelerate3= atof(editBuffer);

					hItem  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_8);
					EDIT_GetText(hItem, &editBuffer[0], sizeof(editBuffer));
					_config_content.calibration= atof(editBuffer);

					_test_result_compare.scale =500/((_config_content.nominalSpeed)*10);
					printf("_test_result_compare.scale=%d m/s\r\n",_test_result_compare.scale);
					_test_result_compare.diameter =(int)(_config_content.diameter/10);
					printf("_test_result_compare.diameter=%d m/s\r\n",_test_result_compare.diameter);
					_test_result_compare.init_v= (int)(_config_content.initSpeed*100);
					printf("_test_result_compare.init_v=%d m/s\r\n",_test_result_compare.init_v);
					_test_result_compare.accelerate_v1=((int)(_config_content.nominalSpeed*1150))-(int)(_config_content.nominalSpeed*1000)/2;
					printf("_test_result_compare.accelerate_v1=%d m/s\r\n",_test_result_compare.accelerate_v1);
					_test_result_compare.accelerate_v2=((int)(_config_content.nominalSpeed*1150))-(int)(_config_content.nominalSpeed*1000)/5;
					printf("_test_result_compare.accelerate_v2=%d m/s\r\n",_test_result_compare.accelerate_v2);

					/*>115% <1.25v+0.25/v*/
					_test_result_compare.result_v1=(int)(_config_content.nominalSpeed*115*10);//三位
					printf("_test_result_compare.result_v1=%d m/s\r\n",_test_result_compare.result_v1);
					_test_result_compare.result_v2=(int)(_config_content.nominalSpeed*125*10+25000/(_config_content.nominalSpeed*100));//四舍五入
					printf("_test_result_compare.result_v2=%d m/s\r\n",_test_result_compare.result_v2);


					GUI_EndDialog(ui_page.windowSKB, 0);
					GUI_EndDialog(pMsg->hWin, 0);
					ui_page.motorCtrlUI=CreateFramewinMotoCtrlUI();
					
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
					GUI_EndDialog(ui_page.windowSKB, 0);
					GUI_EndDialog(pMsg->hWin, 0);
					ui_page.index=CreateFramewinIndex();

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
WM_HWIN CreateFramewinConfigUI(void);
WM_HWIN CreateFramewinConfigUI(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
