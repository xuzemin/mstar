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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

#ifndef MAPP_TTX_H

#include "Board.h"

#if ENABLE_TTX

#if ENABLE_DTV
#include "mapp_si.h"
#endif

#include "msAPI_FreqTableCommon.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_Global.h"
#include "msAPI_TTX.h"

#define MAPP_TTX_H
#define TTX_VOLUMEBAR_REMOVE_TIME 3000

typedef enum
{
    STATE_TTX_OSD_NONE,
    STATE_TTX_OSD_HOKEY,
    STATE_TTX_OSD_MUTE,
    STATE_TTX_OSD_VOLUMN
} EN_TTX_OSD_STATE;

//****************************************************************************
// Control mode definitions
//****************************************************************************
typedef enum
{
    TTX_MODE_NORMAL,
    TTX_MODE_CLOCK,
    TTX_MODE_SUBTITLE,
    TTX_MODE_STATUS
} EN_TELETEXT_MODE;

extern U8 g_NeedReloadTTXFont;

#if ENABLE_DTV
extern MS_TELETEXT_INFO gstTtxInfo;
#endif

void MApp_TTX_InitVBITeletext(void);
void MApp_TTX_SetTeletextOnOff(BOOLEAN val);
void MApp_TTX_SetChInfoOnOff(BOOLEAN val);
BOOLEAN MApp_TTX_IsChInfoOn(void);
BOOLEAN MApp_TTX_IsTeletextOn(void);
BOOLEAN MApp_TTX_IsTeletextOffSuddenly(void);
void MApp_TTX_VBIDataProcessor(void);
void MApp_TTX_SetRP_Video_TTX(BOOLEAN bIsVideoTTX);
void MApp_TTX_ClockMode_Monitor(void);
void MApp_TTX_EnableScan(U_INT8 on);
FUNCTION_RESULT MApp_TTX_TeletextCommand(TELETEXT_COMMAND eCommand);
U_INT8 MApp_TTX_GetSubtitlesAvailable(void);
void MApp_TTX_SetSubtitlePage(U16 mag, U16 page);
void MApp_TTX_Decoder_Process(void);
void MApp_TTX_SetP830_DisplayPos(U16 u8X, U16 u8Y);
void MApp_TTX_Reflesh(void);
void MApp_TTX_SetControlMode(EN_TELETEXT_MODE mode);
EN_TELETEXT_MODE MApp_TTX_GetControlMode(void);
#if ENABLE_DTV
void MApp_TTX_SetDTV_TTXSystem(U16 pid, BOOLEAN bExitPVR);
U16 MApp_TTX_GetSubtitleTTX_PID(void);
void MApp_TTX_SetSubtitleTTX_PID(U16 pid);
U16 MApp_TTX_GetDefaultTTX_PID(void);
void MApp_TTX_SetDefaultTTX_PID(U16 pid);
BOOLEAN MApp_TTX_Is_EBUSubtitleExist(EN_TTX_TYPE eType);
#if 1
BOOLEAN MApp_TTX_Get_TTXInfoByTypeAndLang(EN_TTX_TYPE eType, EN_LANGUAGE lang, U8 *pu8TTXMagNum, U8 *pu8TTXPageNum);
#endif
void MApp_TTX_NotifyPMTTTXInfoChanged(void);
void MApp_TTX_Reset_TTX_Info(void);
#endif
void MApp_TTX_BackToOSDMode(void);
void MApp_TTX_BackToTTXMode(void);
FUNCTION_RESULT MApp_TTX_SetCountry(MEMBER_COUNTRY eCountry);
void MApp_TTX_NavigateSubtitlePagesInTTXMode(void);

void MApp_TTX_Set_ChannelChangeTime(void);
#if PVR_AND_TTX_DIFF_WITH_MHEG5
void MApp_TTX_TurnTTXOnOff(BOOLEAN bOn);
BOOLEAN MApp_TTX_CanBeTurnedOn(void);
#endif
#if ENABLE_TTX_ACI
typedef enum
{
    STATE_TTX_ACI_NONE,
    STATE_TTX_ACI_INIT,
    STATE_TTX_ACI_WAIT,
    STATE_TTX_ACI_FINALIZE_EXIT
} EN_TTX_ACI_STATE;

extern EN_TTX_ACI_STATE    enTTXACIState;

typedef enum
{
    E_ACI_TIMEOUT_NONE  = 0x00,
    E_ACI_TIMEOUT_PAGE_NOT_FOUND = 0x01,
    E_ACI_TIMEOUT_MULTIPACKAGE_WAITING_INPUT = 0x02
} ACI_TIMEOUT_TYPE;

extern ACI_TIMEOUT_TYPE   g_u8ACITimeoutType;
extern U32 g_u32ACITimeout;

void MApp_TTX_AciTimeoutProcess(void);
void MApp_TTX_AciTryGetScanData(void);
void MApp_TTX_ProcessACI(void);
void MApp_TTX_InitACI(void);
#endif

#endif // ENABLE_TTX

#endif

