//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
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

#ifndef _MAPP_ZUI_ACTGLOBAL_H
#define _MAPP_ZUI_ACTGLOBAL_H

#include "ZUI_tables_h.inl"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef MAPP_ZUI_ACTGLOBAL_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

////////////////////////////////////////////////////////
// UI customized constants
#define OSD_GOP_ID  E_GOP_OSD

//MStar OSD font settings
#if  (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP||CHINESE_SIMP_FONT_ENABLE)
    #if (CHINESE_BIG5_FONT_ENABLE)
    #define FONT_NORMAL FONT_0
    #define FONT_BIG    FONT_1
    #define FONT_SMALL  FONT_2
    #else
    #define FONT_NORMAL FONT_CHINESE
    #define FONT_BIG    FONT_CHINESE
    #define FONT_SMALL  FONT_CHINESE
    #endif
#elif  (CHINESE_BIG5_FONT_ENABLE)
#define FONT_NORMAL FONT_BIG5
#define FONT_BIG    FONT_BIG5
#define FONT_SMALL  FONT_BIG5
#else
#define FONT_BIG    FONT_0
#define FONT_NORMAL FONT_1
#define FONT_SMALL  FONT_2
#endif
#define FONT_SIMCHINESE  FONT_CHINESE

#define MENU_TIME_OUT_MS 30000
#define CHLIST_TIME_OUT_MS 10000
#define INSTALL_GUIDE_TIME_OUT_MS 180000   // 3 min
#define PROGRAM_EDIT_TIME_OUT_MS 10000
#define AUDIO_LANGUAGE_TIME_OUT_MS 10000
#define SUBTITLE_LANGUAGE_TIME_OUT_MS 3000
#define INPUT_SOURCE_TIME_OUT_MS 5000
#define HOTKEY_OPTION_TIME_OUT_MS 3000
#define AUDIO_VOLUME_TIME_OUT_MS 3000
#define AUDIO_KEYSTONE_TIME_OUT_MS 3000   //xzm @20171228
#define UART_DEBUG_TIME_OUT_MS 3000
#define MESSAGE_BOX_TIME_OUT_MS 3000
#define TENKEY_NUMBER_TIME_OUT_MS 3000
#define EPG_TIME_OUT_MS 180000      //3 minutes
#define CHANNEL_INFO_TIME_OUT_MS 5000
#define CIMMI_TIME_OUT_MS  720000      //3 minutes
#define PVR_TIME_OUT_MS     0//infinity if this time is too small OSD will close while format is not finished.
#define PVR_BROWSER_TIME_OUT_MS     30000
#define EFFECT_SETTING_TIME_OUT_MS  10000
#define DTV_MANUAL_SCAN_END_TIME_OUT_MS  10000
#define DIVX_DEACT_TIME_OUT_MS      10000

#define BUTTONANICLICK_PERIOD 200 //for pressing bitmap (ms)

#if (ENABLE_EWS == TRUE)
#define STRING_BUFFER_LENGTH    4096
#else
#define STRING_BUFFER_LENGTH    1024            // MApp_Epg_GetDetailDescription() need 2k bytes string buffer.
#endif

INTERFACE U16 u16StringBuffer[STRING_BUFFER_LENGTH];

#define CHAR_BUFFER ((LPTSTR)u16StringBuffer)

#define ZUI_CLEAR_STRING_BUFFER()   memset(u16StringBuffer, 0, sizeof(u16StringBuffer))


#define ZUI_COLOR_TRANSPARENT_RGB555 (((MPLAYER_CLRKEY_R>>3)<<10)|((MPLAYER_CLRKEY_G>>3)<<5)|((MPLAYER_CLRKEY_B>>3)))
#define ZUI_COLOR_TRANSPARENT_RGB8888 MPLAYER_CLRKEY
#define ZUI_GWIN_BLENDING           (63*9/10)
#define ZUI_EXCEPTION_MULTITASK          1
#if ZUI_EXCEPTION_MULTITASK
#define ZUI_EXCEPTION_MULITASK_TIMER              50
#endif

#define ENABLE_EXTERN_MFC_CHIP (ENABLE_MFC_6M30 || ENABLE_MFC_6M30)

////////////////////////////////////////////////////////

typedef enum
{
    ACTION_SELECT,
    ACTION_SELCHG,
    ACTION_ITEMCHG,
} ACTION_TYPE;

INTERFACE U16 MApp_ZUI_ACT_DecIncValue(BOOLEAN bInc, U16 u16Value, U16 u16MinValue, U16 u16MaxValue, U8 u8Step);
INTERFACE S8 MApp_ZUI_ACT_DecIncS8Value(BOOLEAN bInc, S8 s8Value, S8 s8MinValue, S8 s8MaxValue, U8 u8Step);
INTERFACE U16 MApp_ZUI_ACT_DecIncValue_Cycle(BOOLEAN bInc, U16 u16Value, U16 u16MinValue, U16 u16MaxValue, U8 u8Step);
INTERFACE U16 MApp_ZUI_ACT_DecIncParentalRatingClass_Cycle(BOOLEAN bInc, U16 u16Value);
INTERFACE U16 DEC_TO_HEX(U16 u16DecValue);

/////////////////////////////////////////
//INTERFACE BOOLEAN MApp_ZUI_ACT_HandleStartupKey(VIRTUAL_KEY_CODE key);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleGlobalKey(VIRTUAL_KEY_CODE key);
INTERFACE S32 MApp_ZUI_ACT_ExecuteWndProc(U8 u8WinProcID, PMSG msg);
//INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteWndAction(U16 act); //HWND hwnd, ACTION_TYPE act);
INTERFACE BOOLEAN MApp_ZUI_ACT_PostMessageFilter(U8 u8WinProcID, MESSAGE_ENUM msg);
//INTERFACE void _MApp_ZUI_ACT_AppClose(void); //HWND sender);
INTERFACE LPTSTR MApp_ZUI_ACT_GetDynamicText(HWND hwnd);
INTERFACE U16 MApp_ZUI_ACT_GetDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE type);
INTERFACE S16 MApp_ZUI_ACT_GetDynamicValue(HWND hwnd);
INTERFACE S16 MApp_ZUI_ACT_GetDynamicValue_2(HWND hwnd);
INTERFACE GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryDynamicListItemStatus(HWND hwnd);
INTERFACE OSD_COLOR MApp_ZUI_ACT_GetDynamicColor(HWND hwnd, DRAWSTYLE_TYPE type, OSD_COLOR colorOriginal);
INTERFACE BOOLEAN MApp_ZUI_ACT_CheckBypassKey(U8 checkedKey);

#if ZUI_EXCEPTION_MULTITASK
INTERFACE void MApp_ZUI_ACT_Exception_MultiTask(void);
#endif
#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_ACTGLOBAL_H */

