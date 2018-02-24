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

#ifndef _MAPP_ZUI_ACTDRAWDYNAWIN_H
#define _MAPP_ZUI_ACTDRAWDYNAWIN_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef MAPP_ZUI_ACTDRAWDYNAWIN_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define COWIN_ID_NONE           0xFF   //None
#define COWIN_ID_MUTE           0      //MUTE
#define COWIN_ID_PA_MUTE        2      //POWER AMPLIFIER MUTE
#define COWIN_ID_COUNT_DOWN_WIN 1   //Message box
#define COWIN_ID_ARC_DISC_WIN   3
#if (ENABLE_EASMONITOR)
#define COWIN_ID_EAS 		0x04
#endif

INTERFACE U8 u8CoexistWinType;  //Mute or count down win
INTERFACE void MApp_ARC_KeyProc_Mute(void);// anvi22

INTERFACE void MApp_KeyProc_Mute(void);
INTERFACE void MApp_UiMenu_MuteWin_Show(void);
INTERFACE void MApp_UiMenu_MuteWin_Hide(void);
INTERFACE void MApp_UiMenu_ARCDeviceStatusWin_Show(BOOLEAN IsConnect);
INTERFACE void MApp_UiMenu_ARCDeviceStatusWin_Hide(void);
INTERFACE void MApp_UiMenu_ARCDiscWin_State(void);
INTERFACE void MApp_ZUI_ACTcoexist_Enable(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_ZUI_ACTcoexist_Create (U8 win_ID, U16 win_x,U16 win_y,U16 win_w,U16 win_h);
INTERFACE void MApp_ZUI_ACTcoexist_Delete( void);
#if 1//(ENABLE_UI_3D_PROCESS)
INTERFACE void MApp_ZUI_ACTcoexist_RealDelete( void);
#endif
INTERFACE void MApp_UiMenu_CountDownWin_Draw(void);
INTERFACE void MApp_UiMenu_CountDownWin_Create(void);
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)		
INTERFACE BOOLEAN MApp_UiMenu_GetCoexistWin_State(void);
#endif
INTERFACE void MApp_fpGOP_CB(MS_U32 u32EventID, void* reserved0);
INTERFACE void MApp_MUTE_fpGOP_CB(MS_U32 u32EventID, void* reserved0);

#if (ENABLE_EASMONITOR)
INTERFACE void MApp_UiMenu_EASWin_Show(U8 *u8StrLang);
INTERFACE void MApp_UiMenu_EASWin_Hide(void);
INTERFACE U8 MApp_UiMenu_EASWin_Update(void);
#endif
#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_ACTDRAWDYNAWIN_H */

