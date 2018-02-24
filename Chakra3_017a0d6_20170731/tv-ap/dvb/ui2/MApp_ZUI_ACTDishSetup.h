////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPP_ZUI_ACTDISHSETUP_H
#define _MAPP_ZUI_ACTDISHSETUP_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef MAPP_ZUI_ACTDISHSETUP_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


typedef enum
{
    STATE_DISHSETUP_INIT,
    STATE_DISHSETUP_WAIT,
    STATE_DISHSETUP_CLEAN_UP,
    STATE_DISHSETUP_GOTO_STANDBY,
    STATE_DISHSETUP_GOTO_INPUTSOURCE,
    STATE_DISHSETUP_GOTO_MENU,
    STATE_DISHSETUP_GOTO_SCAN
} EN_DISHSETUP_STATE;

/////////////////////////////////////////
// Cutomize Window Procedures...
#if ENABLE_S2_QUALITY_DISPLAY_PERCENT
INTERFACE S32 MApp_ZUI_ACT_DISHSETUP_WINPROC(HWND, PMSG);
#define DISHSETUP_WINPROC MApp_ZUI_ACT_DISHSETUP_WINPROC
#endif
/////////////////////////////////////////
// Event Handlers....
INTERFACE void MApp_ZUI_ACT_TerminateDishSetupMenu(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleDishSetupMenuKey(VIRTUAL_KEY_CODE key);
INTERFACE void MApp_ZUI_ACT_AppShowDishSetupMenu(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteDishSetupMenuAction(U16 act);
INTERFACE LPTSTR MApp_ZUI_ACT_GetDishSetupMenuDynamicText(HWND hwnd);
INTERFACE U16  MApp_ZUI_ACT_GetDishSetupMenuDynamicBmp(HWND hwnd);
INTERFACE S16 MApp_ZUI_ACT_GetDynamicValue_DishSetupMenu(HWND hwnd);
INTERFACE GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryDishItemStatus(HWND hwnd);
INTERFACE U16 prefocuswind;
INTERFACE U16 PreTpFocusWind;
INTERFACE U8 SatListPageNum;
INTERFACE U8 TpListPageNum;
INTERFACE U8 LofListPageNum;
#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  // _MAPP_ZUI_ACTINSTALLGUIDE_H

