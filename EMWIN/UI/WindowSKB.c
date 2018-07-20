#include <string.h>
#include "DIALOG.h"
#include "EmWinHZFont.h"
#include "FramewinDLG.h"

#define ID_WINDOW_0  (GUI_ID_USER + 0x00)
#define ID_TEXT_0  (GUI_ID_USER + 0x01)
#define ID_TEXT_1  (GUI_ID_USER + 0x02)
#define ID_TEXT_2  (GUI_ID_USER + 0x03)
#define ID_TEXT_3  (GUI_ID_USER + 0x04)
#define ID_TEXT_4  (GUI_ID_USER + 0x05)
#define ID_TEXT_5  (GUI_ID_USER + 0x06)
#define ID_TEXT_6  (GUI_ID_USER + 0x07)
#define ID_TEXT_7  (GUI_ID_USER + 0x08)
#define ID_TEXT_8  (GUI_ID_USER + 0x09)
#define ID_TEXT_9  (GUI_ID_USER + 0x0A)
#define ID_BUTTON_0  (GUI_ID_USER + 0x0B)
#define ID_BUTTON_1  (GUI_ID_USER + 0x0C)
#define ID_BUTTON_2  (GUI_ID_USER + 0x0D)
#define ID_BUTTON_3  (GUI_ID_USER + 0x0E)
#define ID_BUTTON_4  (GUI_ID_USER + 0x0F)
#define ID_BUTTON_5  (GUI_ID_USER + 0x10)
#define ID_BUTTON_6  (GUI_ID_USER + 0x11)
#define ID_BUTTON_7  (GUI_ID_USER + 0x12)
#define ID_BUTTON_8  (GUI_ID_USER + 0x13)
#define ID_BUTTON_9  (GUI_ID_USER + 0x14)
#define ID_BUTTON_10  (GUI_ID_USER + 0x15)
#define ID_BUTTON_11  (GUI_ID_USER + 0x16)
#define ID_BUTTON_12  (GUI_ID_USER + 0x17)
#define ID_BUTTON_13  (GUI_ID_USER + 0x18)
#define ID_BUTTON_14  (GUI_ID_USER + 0x19)
#define ID_BUTTON_15  (GUI_ID_USER + 0x1A)
#define ID_BUTTON_16  (GUI_ID_USER + 0x1B)
#define ID_BUTTON_17  (GUI_ID_USER + 0x1C)
#define ID_BUTTON_18  (GUI_ID_USER + 0x1D)
#define ID_BUTTON_19  (GUI_ID_USER + 0x1E)
#define ID_BUTTON_20  (GUI_ID_USER + 0x1F)
#define ID_BUTTON_21  (GUI_ID_USER + 0x20)
#define ID_BUTTON_22  (GUI_ID_USER + 0x21)
#define ID_BUTTON_23  (GUI_ID_USER + 0x22)
#define ID_BUTTON_24  (GUI_ID_USER + 0x23)
#define ID_BUTTON_25  (GUI_ID_USER + 0x24)
#define ID_BUTTON_26  (GUI_ID_USER + 0x25)
#define ID_BUTTON_27  (GUI_ID_USER + 0x26)
#define ID_BUTTON_28  (GUI_ID_USER + 0x27)
#define ID_BUTTON_29  (GUI_ID_USER + 0x28)
#define ID_BUTTON_30  (GUI_ID_USER + 0x29)
#define ID_BUTTON_31  (GUI_ID_USER + 0x2A)
#define ID_BUTTON_32  (GUI_ID_USER + 0x2B)
#define ID_BUTTON_33  (GUI_ID_USER + 0x2C)
#define ID_BUTTON_34  (GUI_ID_USER + 0x2D)

#define ID_EDIT_0  (GUI_ID_USER + 0x30)
#define ID_FOCUS_OPERATE  (GUI_ID_USER + 0xFF)

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 580, 365, 0, 0x0, 0 },

  { TEXT_CreateIndirect, "ping", ID_TEXT_0, 5, 5 + 40, 80, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "1", ID_TEXT_1, 85, 5 + 40, 40, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "2", ID_TEXT_2, 135, 5 + 40, 40, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "3", ID_TEXT_3, 180, 5 + 40, 40, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "4", ID_TEXT_4, 225, 5 + 40, 40, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "5", ID_TEXT_5, 270, 5 + 40, 40, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "6", ID_TEXT_6, 315, 5 + 40, 40, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "7", ID_TEXT_7, 360, 5 + 40, 40, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "8", ID_TEXT_8, 405, 5 + 40, 40, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "9", ID_TEXT_9, 460, 5 + 40, 40, 50, 0, 0x64, 0 },

  { BUTTON_CreateIndirect, "q", ID_BUTTON_0, 5, 60+40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "w", ID_BUTTON_1, 60, 60 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "e", ID_BUTTON_2, 115, 60 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "r", ID_BUTTON_3, 170, 60 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "t", ID_BUTTON_4, 225, 60 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "y", ID_BUTTON_5, 280, 60 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "u", ID_BUTTON_6, 335, 60 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "i", ID_BUTTON_7, 390, 60 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "o", ID_BUTTON_8, 445, 60 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "p", ID_BUTTON_9, 500, 60 + 40, 50, 60, 0, 0x0, 0 },

  { BUTTON_CreateIndirect, "a", ID_BUTTON_10, 5, 125+40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "s", ID_BUTTON_11, 60, 125 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "d", ID_BUTTON_12, 115, 125 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "f", ID_BUTTON_13, 170, 125 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "g", ID_BUTTON_14, 225, 125 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "h", ID_BUTTON_15, 280, 125 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "j", ID_BUTTON_16, 335, 125 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "k", ID_BUTTON_17, 390, 125 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "l", ID_BUTTON_18, 445, 125 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "_", ID_BUTTON_19, 500, 125 + 40, 50, 60, 0, 0x0, 0 },

  { BUTTON_CreateIndirect, "z", ID_BUTTON_20, 5, 190+40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "x", ID_BUTTON_21, 60, 190 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "c", ID_BUTTON_22, 115, 190 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "v", ID_BUTTON_23, 170, 190 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "b", ID_BUTTON_24, 225, 190 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "n", ID_BUTTON_25, 280, 190 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "m", ID_BUTTON_26, 335, 190 + 40, 50, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "<-", ID_BUTTON_27, 390, 190 + 40, 80, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "->", ID_BUTTON_28, 471, 190 + 40, 80, 60, 0, 0x0, 0 },

  { BUTTON_CreateIndirect, "Caps", ID_BUTTON_29, 5, 255+40, 80, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Esc", ID_BUTTON_30, 90, 255 + 40, 80, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "", ID_BUTTON_31, 175, 255 + 40, 110, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "En", ID_BUTTON_32, 290, 255 + 40, 80, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Enter", ID_BUTTON_33, 375, 255 + 40, 80, 60, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "<---", ID_BUTTON_34, 460, 255 + 40, 80, 60, 0, 0x0, 0 },

  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 5, 1, 570, 40, 0, 0x64, 0 },
};

static const char keyCAP[] = {
'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '_',
'Z', 'X', 'C', 'V', 'B', 'N', 'M', 0};
static const char keyLOW[] = {
'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '_',
'z', 'x', 'c', 'v', 'b', 'n', 'm', 0};
static const char key123[] = {
'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
'!', '@', '%', '*', '(', ')', '_', '-', '+', '=',
'/', ':', ';', '"', ',', '.', '?', 0};
static unsigned char timerBoot=0;

//extern GUI_CONST_STORAGE GUI_FONT GBK_16m16;
extern const char *PYSearch(char *strInput_py_str);
void setWindowSKBtimerBoot(unsigned char statue);
unsigned char getWindowSKBtimerBoot();
static WM_HMEM timer;
static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem, hItext;
	int	 NCode;
	int	 Id, i, temp;
	char charBUFF[128], tempBUFF[128], editBuffer[128];
	static int *pbuffPY[64];
	static char **pstrPY=(char **)&pbuffPY[0];
	char *pstrTEMP;
	static unsigned char capsKEY = 0, inputTYPE = 0;
	WM_MESSAGE Message;
	WM_HWIN hWin;
	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
	capsKEY = 0, inputTYPE = 0;

	hItem = pMsg->hWin;
	WINDOW_SetBkColor(hItem, (0x00C0C0C0));
	timer = WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 1, 30, 0); //~10ms
	//timerBoot=1;//第一次启动清零 编辑器清零
	// Initialization of 'ping'
	TEXT_SetTextAlign(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), GUI_TA_LEFT | GUI_TA_VCENTER);
	TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), "");

	// Initialization of '1'
	for(i=ID_TEXT_1; i<=ID_TEXT_9; i++)
	{
		hItem = WM_GetDialogItem(pMsg->hWin, i);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetFont(hItem, &GUI_FontHZ24);
		TEXT_SetText(hItem, "");
	}

	hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
	EDIT_SetFont(hItem, &GUI_FontHZ24);
	EDIT_SetText(hItem, "");
	EDIT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);

	for(i=ID_BUTTON_0; i<=ID_BUTTON_34; i++) BUTTON_SetFocussable(WM_GetDialogItem(pMsg->hWin, i), 0);	//disable focus
	EDIT_SetFocussable(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0), 0);

	break;
	case WM_TIMER://~定时器
		/*if(0==getWindowSKBtimerBoot()){
			hItext = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
			EDIT_SetText(hItext, "");
		}else{*/
			EDIT_GetText(WM_GetFocussedWindow(), &editBuffer[0], sizeof(editBuffer));
			hItext = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
			EDIT_SetText(hItext, editBuffer);
		//}
		WM_RestartTimer(timer, 100);
		break;

	case WM_NOTIFY_PARENT:
	//setWindowSKBtimerBoot(1);
	
	Id	= WM_GetId(pMsg->hWinSrc);
	NCode = pMsg->Data.v;
	switch(Id) {
	case ID_BUTTON_0: // Notifications sent by 'q'
	case ID_BUTTON_1: // Notifications sent by 'w'
	case ID_BUTTON_2: // Notifications sent by 'e'
	case ID_BUTTON_3: // Notifications sent by 'r'
	case ID_BUTTON_4: // Notifications sent by 't'
	case ID_BUTTON_5: // Notifications sent by 'y'
	case ID_BUTTON_6: // Notifications sent by 'u'
	case ID_BUTTON_7: // Notifications sent by 'i'
	case ID_BUTTON_8: // Notifications sent by 'o'
	case ID_BUTTON_9: // Notifications sent by 'p'
	case ID_BUTTON_10: // Notifications sent by 'a'
	case ID_BUTTON_11: // Notifications sent by 's'
	case ID_BUTTON_12: // Notifications sent by 'd'
	case ID_BUTTON_13: // Notifications sent by 'f'
	case ID_BUTTON_14: // Notifications sent by 'g'
	case ID_BUTTON_15: // Notifications sent by 'h'
	case ID_BUTTON_16: // Notifications sent by 'j'
	case ID_BUTTON_17: // Notifications sent by 'k'
	case ID_BUTTON_18: // Notifications sent by 'l'
	case ID_BUTTON_20: // Notifications sent by 'z'
	case ID_BUTTON_21: // Notifications sent by 'x'
	case ID_BUTTON_22: // Notifications sent by 'c'
	case ID_BUTTON_23: // Notifications sent by 'v'
	case ID_BUTTON_24: // Notifications sent by 'b'
	case ID_BUTTON_25: // Notifications sent by 'n'
	case ID_BUTTON_26: // Notifications sent by 'm'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			if(inputTYPE == 0) goto gotoASCII;
			else if(inputTYPE == 1) goto gotoSYMBOL;
			else goto gotoPING;

			gotoASCII:
			BUTTON_GetText(pMsg->hWinSrc, &charBUFF[0], sizeof(charBUFF));
			GUI_StoreKeyMsg(charBUFF[0], 1);	//store key to EMWIN
			GUI_StoreKeyMsg(charBUFF[0], 0);
			break;

			gotoSYMBOL:
			BUTTON_GetText(pMsg->hWinSrc, &charBUFF[0], sizeof(charBUFF));
			GUI_StoreKeyMsg(charBUFF[0], 1);
			GUI_StoreKeyMsg(charBUFF[0], 0);
			break;

			gotoPING:
			if(capsKEY)						//if Caps is on
			{
				BUTTON_GetText(pMsg->hWinSrc, &charBUFF[0], sizeof(charBUFF));
				GUI_StoreKeyMsg(charBUFF[0], 1);	//store key to EMWIN and exit
				GUI_StoreKeyMsg(charBUFF[0], 0);
				break;
			}
			TEXT_GetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), &charBUFF[0], sizeof(charBUFF));
			BUTTON_GetText(pMsg->hWinSrc, &tempBUFF[0], sizeof(tempBUFF));
			strcat(charBUFF, tempBUFF);	//connect string
			TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), &charBUFF[0]);

			//send one message to ID_TEXT_0,update ID_TEXT_1~~ID_TEXT_9 content
			Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			Message.MsgId = WM_NOTIFY_PARENT;
			Message.Data.v = WM_NOTIFICATION_USER+0;
			WM_SendMessage(pMsg->hWin, &Message);
			break;
		}
		break;
	case ID_BUTTON_19: // Notifications sent by '_'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			BUTTON_GetText(pMsg->hWinSrc, &charBUFF[0], sizeof(charBUFF));
			GUI_StoreKeyMsg(charBUFF[0], 1);
			GUI_StoreKeyMsg(charBUFF[0], 0);
			break;
		}
		break;
	case ID_BUTTON_27: // Notifications sent by '<-'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			Message.MsgId = WM_NOTIFY_PARENT;
			Message.Data.v = WM_NOTIFICATION_USER+1;
			WM_SendMessage(pMsg->hWin, &Message);
			break;
		}
		break;
	case ID_BUTTON_28: // Notifications sent by '->'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			Message.MsgId = WM_NOTIFY_PARENT;
			Message.Data.v = WM_NOTIFICATION_USER+2;
			WM_SendMessage(pMsg->hWin, &Message);
			break;
		}
		break;
	case ID_BUTTON_29: // Notifications sent by 'Caps'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
		break;
		case WM_NOTIFICATION_RELEASED:
			if(inputTYPE==1) break;

			capsKEY = !capsKEY;
			if(capsKEY) BUTTON_SetTextColor(pMsg->hWinSrc, BUTTON_CI_UNPRESSED, GUI_RED);
			else BUTTON_SetTextColor(pMsg->hWinSrc, BUTTON_CI_UNPRESSED, GUI_BLACK);

			for(Id=ID_BUTTON_0; Id<=ID_BUTTON_26; Id++)	//change to English keyboard
			{
				charBUFF[0] = capsKEY ? keyCAP[Id-ID_BUTTON_0] : keyLOW[Id-ID_BUTTON_0]; charBUFF[1] = 0;
				BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, Id), &charBUFF[0]);
				BUTTON_SetTextColor(WM_GetDialogItem(pMsg->hWin, Id), BUTTON_CI_UNPRESSED, (!capsKEY&&(inputTYPE==2)) ? GUI_BLUE : GUI_BLACK);
			}
			break;
		}
		break;
	case ID_BUTTON_30: // Notifications sent by 'Esc'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			button_Press.windowSKB=0;
			WM_HideWindow(pMsg->hWin);

			//renew all keys include caps
			inputTYPE = (inputTYPE <= 0) ? 2 : (inputTYPE-1);
			Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_32);
			Message.MsgId = WM_NOTIFY_PARENT;
			Message.Data.v = WM_NOTIFICATION_RELEASED;
			WM_SendMessage(pMsg->hWin, &Message);
			/*hItext = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
			EDIT_SetText(hItext, "");*/
		}
		break;
	case ID_BUTTON_31: // Notifications sent by ' '
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			GUI_StoreKeyMsg(GUI_KEY_SPACE, 1);
			GUI_StoreKeyMsg(GUI_KEY_SPACE, 0);
			break;
		}
		break;
	case ID_BUTTON_32: // Notifications sent by 'EN'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			inputTYPE = (inputTYPE >= 2) ? 0 : (inputTYPE+1);

			capsKEY = 0;
			BUTTON_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_29), BUTTON_CI_UNPRESSED, GUI_BLACK);
			if(inputTYPE==2) for(i=ID_BUTTON_0; i<=ID_BUTTON_26; i++) BUTTON_SetTextColor(WM_GetDialogItem(pMsg->hWin, i), BUTTON_CI_UNPRESSED, GUI_BLUE);
			else for(i=ID_BUTTON_0; i<=ID_BUTTON_26; i++) BUTTON_SetTextColor(WM_GetDialogItem(pMsg->hWin, i), BUTTON_CI_UNPRESSED, GUI_BLACK);

			if(inputTYPE == 0) goto gotoEN;
			else if(inputTYPE == 1) goto goto123;
			else goto gotoCH;

			gotoEN:
			BUTTON_SetText(pMsg->hWinSrc, "EN");
			for(Id=ID_BUTTON_0; Id<=ID_BUTTON_26; Id++)	//change to English keyboard
			{
				charBUFF[0] = keyLOW[Id-ID_BUTTON_0]; charBUFF[1] = 0;
				BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, Id), &charBUFF[0]);
			}
			goto gotoEXIT;

			goto123:
			BUTTON_SetText(pMsg->hWinSrc, "123");
			for(Id=ID_BUTTON_0; Id<=ID_BUTTON_26; Id++)	//change to symbol keyboard
			{
				charBUFF[0] = key123[Id-ID_BUTTON_0]; charBUFF[1] = 0;
				BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, Id), &charBUFF[0]);
			}
			goto gotoEXIT;

			gotoCH:
			BUTTON_SetText(pMsg->hWinSrc, "CH");		//change to Chinese keyboard
			for(Id=ID_BUTTON_0; Id<=ID_BUTTON_26; Id++)
			{
				charBUFF[0] = keyLOW[Id-ID_BUTTON_0]; charBUFF[1] = 0;
				BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, Id), &charBUFF[0]);
			}
			goto gotoEXIT;

			gotoEXIT:
			TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), "");

			//send one message to ID_TEXT_0,update ID_TEXT_1~~ID_TEXT_9 content
			Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			Message.MsgId = WM_NOTIFY_PARENT;
			Message.Data.v = WM_NOTIFICATION_USER+0;
			WM_SendMessage(pMsg->hWin, &Message);
		}
		break;
	case ID_BUTTON_33: // Notifications sent by 'Enter'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			//GUI_StoreKeyMsg(GUI_KEY_ENTER, 1);
			//GUI_StoreKeyMsg(GUI_KEY_ENTER, 0);
			
			WM_HideWindow(pMsg->hWin);
			button_Press.windowSKB=0;
			//renew all keys include caps
			inputTYPE = (inputTYPE <= 0) ? 2 : (inputTYPE-1);
			Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_32);
			Message.MsgId = WM_NOTIFY_PARENT;
			Message.Data.v = WM_NOTIFICATION_RELEASED;
			WM_SendMessage(pMsg->hWin, &Message);

			hWin = WM_GetParent(pMsg->hWin);
			Message.hWinSrc = WM_GetDialogItem(hWin, ID_FOCUS_OPERATE);
			Message.MsgId = WM_NOTIFY_PARENT;
			Message.Data.v = WM_NOTIFICATION_USER;
			WM_SendMessage(hWin, &Message);
			//EDIT_GetText(WM_GetFocussedWindow(), &editBuffer[0], sizeof(editBuffer));
			hItext = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
			EDIT_SetText(hItext, "");
			
			break;
		}
		break;
	case ID_BUTTON_34: // Notifications sent by '<---'
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			if((inputTYPE==2) && !capsKEY && (i=TEXT_GetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), &charBUFF[0], sizeof(charBUFF))))
			{
				charBUFF[i-1] = 0;	//delete the last char
				TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), &charBUFF[0]);

				//send one message to ID_TEXT_0,update ID_TEXT_1~~ID_TEXT_9 content
				Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
				Message.MsgId = WM_NOTIFY_PARENT;
				Message.Data.v = WM_NOTIFICATION_USER+0;
				WM_SendMessage(pMsg->hWin, &Message);
			}
			if(((inputTYPE!=2)) || capsKEY || !i)
			{
				GUI_StoreKeyMsg(GUI_KEY_BACKSPACE, 1);
				GUI_StoreKeyMsg(GUI_KEY_BACKSPACE, 0);
			}
			break;
		}
		break;
	case ID_TEXT_0:
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
		case WM_NOTIFICATION_RELEASED:
		break;
		case WM_NOTIFICATION_USER+0:
		case WM_NOTIFICATION_USER+1:
		case WM_NOTIFICATION_USER+2:
			if(NCode == WM_NOTIFICATION_USER+0)
			{
				TEXT_GetText(pMsg->hWinSrc, &charBUFF[0], sizeof(charBUFF));	//Get ID_TEXT_0 text
				for(i=0; i<sizeof(pbuffPY)/4; i++) pbuffPY[i] = 0;
				pstrPY = (char **)&pbuffPY[0];
				pstrTEMP = (char *)PYSearch(&charBUFF[0]);
				//??9????~{!A~}???????????????pbuffPY[i]
				for(i=0; pstrTEMP&&*pstrTEMP&&(i<sizeof(pbuffPY)/4-1); i++)
				{
					pbuffPY[i] = (int *)pstrTEMP;
					//pstrTEMP move 9 Chinese characters
					for(temp=ID_TEXT_1; temp<=ID_TEXT_9; temp++)
					{
						pstrTEMP = pstrTEMP + GUI_pUC_API->pfGetCharSize(pstrTEMP);	//Using 'pfGetCharSize' to calculate bytes of one Chinese character
						if(!pstrTEMP || !*pstrTEMP) break;
					}
				}
			}
			else if(NCode == WM_NOTIFICATION_USER+1)			//'<-'
			{
				if(*(pstrPY-1) && (pstrPY != (char **)&pbuffPY[0])) pstrPY--;
			}
			else if(NCode == WM_NOTIFICATION_USER+2)			//'->'
			{
				if(*(pstrPY+1) && (pstrPY!=(char **)&pbuffPY[sizeof(pbuffPY)/4-1])) pstrPY++; else pstrPY = (char **)&pbuffPY[0];
			}

			//Display characters to ID_TEXT_1~~ID_TEXT_9
			for(pstrTEMP = *pstrPY, i=ID_TEXT_1; i<=ID_TEXT_9; i++)
			{
				memset(&tempBUFF[0], 0, sizeof(tempBUFF));
				if(!pstrTEMP || !*pstrTEMP) {TEXT_SetText(WM_GetDialogItem(pMsg->hWin, i), ""); continue;}

				memcpy(&tempBUFF[0], pstrTEMP, temp = GUI_pUC_API->pfGetCharSize(pstrTEMP));	//temp = bytes of a Chinese character
				TEXT_SetText(WM_GetDialogItem(pMsg->hWin, i), &tempBUFF[0]);				//display the Chinese character
				pstrTEMP = pstrTEMP + temp;
			}
		break;
		}
		break;
	case ID_TEXT_1:
	case ID_TEXT_2:
	case ID_TEXT_3:
	case ID_TEXT_4:
	case ID_TEXT_5:
	case ID_TEXT_6:
	case ID_TEXT_7:
	case ID_TEXT_8:
	case ID_TEXT_9:
		switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			break;
		case WM_NOTIFICATION_RELEASED:
			if(inputTYPE!=2) break;
			if(TEXT_GetText(WM_GetDialogItem(pMsg->hWin, Id), &tempBUFF[0], sizeof(tempBUFF)) == 0) break;
			EDIT_GetText(hItem=WM_GetFocussedWindow(), &charBUFF[0], sizeof(charBUFF));
			strcat(charBUFF, tempBUFF);
			EDIT_SetText(hItem, &charBUFF[0]);

			//send one message to ID_TEXT_0,update ID_TEXT_1~~ID_TEXT_9 content
			TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), "");
			Message.hWinSrc = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			Message.MsgId = WM_NOTIFY_PARENT;
			Message.Data.v = WM_NOTIFICATION_USER+0;
			WM_SendMessage(pMsg->hWin, &Message);
			break;
		}
		break;
	}
	break;
	default:
	WM_DefaultProc(pMsg);
	break;
	}
}

WM_HWIN CreateWindowSKB(void);
void DelWindowSKB(void);
//static unsigned char timerBoot=0;

void setWindowSKBtimerBoot(unsigned char statue){
	timerBoot=statue;
}
unsigned char getWindowSKBtimerBoot(){
	return timerBoot;
	}
void DelWindowSKB(void){
	WM_DeleteTimer(timer);
	GUI_EndDialog(ui_page.windowSKB, 0);
}
WM_HWIN CreateWindowSKB(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

