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

#ifndef _MAPP_ZUI_ACTTHUNDER_H
#define _MAPP_ZUI_ACTTHUNDER_H

#if 1//(ENABLE_THUNDER_DOWNLOAD)
#include "MApp_ZUI_APIgdi.h"

#ifdef MAPP_ZUI_ACTTHUNDER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define NUM_OF_IME_CHARS_PER_PAGE     8
#define NUM_OF_SEARCH_STRING     64


typedef enum
{
    TYPE_THUNDER_TORRENT_SEARCH,
    TYPE_THUNDER_TOP_10,
    TYPE_THUNDER_NEW_10,
    TYPE_THUNDER_DOWNLOAD_LIST,
    TYPE_THUNDER_SETUP,
    TYPE_THUNDER_INVALID=0xFF,
} EN_THUNDER_PAGE_TYPE;


typedef enum
{
    IME_TYPE_ENGLISH,
    IME_TYPE_CHINESE,
    IME_TYPE_PINYIN,
    IME_TYPE_MAX,
} EN_IME_TYPE;

typedef enum
{
    KEYWORD_SEARCH_STATE_STEP1,
    KEYWORD_SEARCH_STATE_STEP2,
} EN_KEYWORD_SEARCH_STATE;


/// Specify the torrent Search IME.
typedef enum
{
    STATE_IME_NULL,
    STATE_IME_SPELL,
    STATE_IME_CHS,
    STATE_IME_SETP3,
} EN_IME_STATE;


typedef struct
{
    BOOLEAN bInputOK;
    EN_IME_TYPE uIME_Type;
    BOOLEAN bIsCAPs;
    EN_IME_STATE     uIME_State;
    U8     u8Char;
    U16     u16SpellCounter;
    U16     u16SpellStar;
    U16     u16CHS_Offset;
    U8 u8Sting[NUM_OF_IME_CHARS_PER_PAGE][7];
    U16 u16StringName[NUM_OF_SEARCH_STRING];    // file name
} _Thunder_IME;


/////////////////////////////////////////
#define MApp_ZUI_ACT_BTTopWinProc MApp_ZUI_ACT_ThunderTopWinProc
#define MApp_ZUI_ACT_BTLinkPhotoWinProc MApp_ZUI_ACT_ThunderTopWinProc
#define MApp_ZUI_ACT_BTDescriptionWinProc MApp_ZUI_ACT_ThunderDescriptionWinProc
#define MApp_ZUI_ACT_TerminateBT MApp_ZUI_ACT_TerminateThunder
#define MApp_ZUI_ACT_GetBTDynamicText MApp_ZUI_ACT_GetThunderDynamicText
#define MApp_ZUI_ACT_GetBTDynamicBitmap MApp_ZUI_ACT_GetThunderDynamicBitmap
#define MApp_ZUI_ACT_HandleBTKey MApp_ZUI_ACT_HandleThunderKey
#define MApp_ZUI_ACT_ExecuteBTAction MApp_ZUI_ACT_ExecuteThunderAction
#define MApp_ZUI_ACT_AppShowBT MApp_ZUI_ACT_AppShowThunder
//#define MApp_ZUI_ACT_GetBTDynamicText MApp_ZUI_ACT_GetThunderDynamicText
//#define MApp_ZUI_ACT_GetBTDynamicText MApp_ZUI_ACT_GetThunderDynamicText

/////////////////////////////////////////
// Event Handlers....
INTERFACE S32 MApp_ZUI_ACT_ThunderTopWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_ThunderLinkPhotoWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_ThunderDescriptionWinProc(HWND hWnd, PMSG pMsg);
INTERFACE void MApp_ZUI_ACT_TerminateThunder(void);
INTERFACE LPTSTR MApp_ZUI_ACT_GetThunderDynamicText(HWND hwnd);
INTERFACE U16 MApp_ZUI_ACT_GetThunderDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleThunderKey(VIRTUAL_KEY_CODE key);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteThunderAction(U16 act);
INTERFACE void MApp_ZUI_ACT_AppShowThunder(void);
INTERFACE void MApp_Thunder_ClearTopOrNewListPhotoBG(U8 u8Item);
INTERFACE void MApp_ZUI_ACT_ThunderSystemErrorShow(void);
INTERFACE void MApp_ZUI_ACT_ThunderSystemErrorShowExit(void);



#undef INTERFACE

#endif // #if (ENABLE_THUNDER_DOWNLOAD)

#endif /* _MAPP_ZUI_ACTTHUNDER_H */


