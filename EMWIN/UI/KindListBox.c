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
#define ID_FRAMEWIN_0    (GUI_ID_USER + 0x25)
#define ID_LISTBOX_0    (GUI_ID_USER + 0x26)


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
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 302, 82, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_0, 0, 0, 300, 80, 0, 0x0, 0 },
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
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTitleVis(hItem, 0);
    FRAMEWIN_SetTitleHeight(hItem, 0);
    //
    // Initialization of 'Listbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
		/*RADIO_SetFont(hItem, &GUI_FontHZ16);
		RADIO_SetText(hItem, "渐进式安全钳", 0);
		RADIO_SetText(hItem, "滚柱瞬时式", 1);
		RADIO_SetText(hItem, "其他瞬时式", 2);*/
		LISTBOX_AddString(hItem, "渐进式安全钳");
    	LISTBOX_AddString(hItem, "滚柱瞬时式安全钳");
    	LISTBOX_AddString(hItem, "其他形式瞬时式安全钳");
    	LISTBOX_SetFont(hItem,  &GUI_FontHZ24);
		//LISTBOX_SetDefaultBkColor();
		LISTBOX_SetBkColor(hItem,LISTBOX_CI_SEL,GUI_GRAY);
		LISTBOX_SetTextColor(hItem,LISTBOX_CI_SEL,GUI_WHITE);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_LISTBOX_0: // Notifications sent by 'Listbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
        _config_content.sort=LISTBOX_GetSel(hItem);
        GUI_EndDialog(pMsg->hWin, 0);
		ui_page.klindlistbox=0;
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
WM_HWIN CreateFramewinKindListBox(void);
WM_HWIN CreateFramewinKindListBox(void) {
	WM_HWIN hWin;
	button_Press.windowSKB=0;
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
