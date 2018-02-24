////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPP_ZUI_ACTKEYSTONEANGLE_H
#define _MAPP_ZUI_ACTKEYSTONEANGLE_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcommon.h"


#ifdef MAPP_ZUI_ACTBATPERCENTAGE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/////////////////////////////////////////
// Cutomize Window Procedures...
//INTERFACE S32 MApp_ZUI_ACT_BatPercentWinProc(HWND, PMSG);

//#define BATPERCENT_WINPROC MApp_ZUI_ACT_BatPercentWinProc

/////////////////////////////////////////
// Event Handlers....
INTERFACE void MApp_ZUI_ACT_AppShowKeystoneAngle(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleKeystoneAngleKey(VIRTUAL_KEY_CODE key);
INTERFACE void MApp_ZUI_ACT_TerminateKeystoneAngle(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteKeystoneAngleAction(U16 act);
INTERFACE LPTSTR MApp_ZUI_ACT_GetKeystoneAngleDynamicText(HWND hwnd);
INTERFACE S16 MApp_ZUI_ACT_GetKeystoneAngleDynamicValue(HWND hwnd);
INTERFACE U16 MApp_ZUI_ACT_GetKeystoneAngleDynamicBitmap(HWND hwnd);


#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_ACTKEYSTONEANGLE_H */

