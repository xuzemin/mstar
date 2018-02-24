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

////////////////////////////////////////////////////////////////////////////////
//
/// @file MApp_Subtitle.h
/// @brief API for Subtitle Display
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MAPP_SUBTITLE_H
#define MAPP_SUBTITLE_H

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define SIZE_OF_PMT_NODE            8
#define SUBTITLE_WITH_OSD           TRUE
#define SUBTITLE_REDUCE_GWIN        TRUE
#define MAX_SUBTITLE_OPTIONS        10
#define SUBTITLE_PMT_MONITOR_PERIOD 1500
#define SUBTITLE_TIMEOUT_THRESHOLD  15000 //UNIT:mSec,(15 Sec) DTG : 10 ~ 15 Sec
#if (SUBTITLE_WITH_OSD)
#define SUBTITLE_MAINPROC_TIMEOUT_THRESHOLD  30 //UNIT:mSec,(15 Sec) DTG : 10 ~ 15 Sec
#endif

//-------------------------------------------------------------------------------------------------
// Standard include files:
//-------------------------------------------------------------------------------------------------
#include "datatype.h"

#include "msAPI_Subtitle_Pub.h"
#include "msAPI_MIU.h"
#if (MHEG5_ENABLE)
#include "msAPI_MHEG5.h"
#endif

#if (ENABLE_TTX)
#include "mapp_ttx.h"
#endif
#include "MApp_Exit.h"
#include "MApp_VDMode.h"
#include "MApp_SignalMonitor.h"
#include "MApp_Key.h"
#include "MApp_GlobalSettingSt.h"
#if( ENABLE_DTV )
#include "mapp_si.h"
#endif

#ifdef MAPP_SUBTITLE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef enum
{
    SBTL_SERVICE_NOT_FOUND = 0,
    SBTL_SERVICE_FOUND,
    SBTL_SERVICE_TTX_FOUND
} RET_SBTL_SERVICE_SEARCH;

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define MAX_SUBTITLE_SERVICE_NUM       20
//#define MAX_TTX_SUBTITLE_SERVICE_NUM    6
//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    SBTL_GET_PES_STATE_FAIL = 0,
    SBTL_GET_PES_STATE_TOBECONTINUED,
    SBTL_GET_PES_STATE_FINISH,
    SBTL_GET_PES_STATE_WAITING
} GET_PES_STATE;

typedef enum _SUBTITLING_TYPE
{
    SUBTITLING_TYPE_TELETEXT       = 0x01,
    SUBTITLING_TYPE_TELETEXT_HOH   = 0x02,
    SUBTITLING_TYPE_NORMAL_NO      = 0x10,
    SUBTITLING_TYPE_NORMAL_4X3     = 0x11,
    SUBTITLING_TYPE_NORMAL_16X9    = 0x12,
    SUBTITLING_TYPE_NORMAL_221X100 = 0x13,
    SUBTITLING_TYPE_NORMAL_HD      = 0x14,
    SUBTITLING_TYPE_HH_NO          = 0x20,
    SUBTITLING_TYPE_HH_4X3         = 0x21,
    SUBTITLING_TYPE_HH_16X9        = 0x22,
    SUBTITLING_TYPE_HH_221X100     = 0x23,
    SUBTITLING_TYPE_HH_HD          = 0x24,
} SUBTITLING_TYPE;
typedef enum
{
    STATE_SUBTITLE_INIT = 0,
    STATE_SUBTITLE_DECODING
} EN_SUBTITLE_STATE;

typedef struct
{
    U16 u16PID;
    U8  StringCodes[4];
    SUBTITLING_TYPE  u8SubtitleType;
    U16 u16Composition_Page_id;
    U16 u16Ancillary_Page_id;
} DVB_SUBTITLE_SERVICE;
/*
typedef struct
{
    U8  StringCodes[4];
    U8  u8Magazine;
    U8  u8Page;
} TTX_SUBTITLE_SERVICES;
*/
typedef struct
{
    char StringCodes[4];
    U8  u8Magazine;
    U8  u8Page;
    U16 u16PID;
    SUBTITLING_TYPE  u8SubtitleType;
} SUBTITLE_MENU;

#if (ENABLE_SUBTITLE)
//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------
INTERFACE U8 u8SubtitleIdx;
#if (ENABLE_SUBTITLE)
INTERFACE U8 u8preSubtitleMenuIdx;
#endif
INTERFACE U8 *pu8ElementaryPID;
INTERFACE U8 SubtitleSamePIDCnt;
INTERFACE U8 u8SubtitleMenuNum;
INTERFACE U8 *pu8SubtitleDescriptor;
INTERFACE U8 u8DVBSubtitleServiceNum;
INTERFACE BOOLEAN bEnableSubtitleTimeoutMonitor;
INTERFACE U32 u32SubtitleTimeOut;
#if (SUBTITLE_WITH_OSD)
INTERFACE U32 u32SubtitleMainProcTimeOut;//for MApp_Subtitle_Main timeout 30ms
#endif
INTERFACE SUBTITLE_MENU SubtitleMenu[MAX_SUBTITLE_SERVICE_NUM];
INTERFACE DVB_SUBTITLE_SERVICE DVBSubtitleServices[MAX_SUBTITLE_SERVICE_NUM];

//-------------------------------------------------------------------------------------------------
// Extern Functions
///-------------------------------------------------------------------------------------------------
INTERFACE U8 MApp_Subtitle_Get_SubtitleOSDState(void);
INTERFACE U16 MApp_Subitle_GetCurPID(void);
INTERFACE void MApp_Subtitle_Disable(void);
INTERFACE BOOLEAN MApp_Subtitle_ParsePMT(void);
INTERFACE void MApp_Subtitle_GetPid(U16 *pu16_pid);
INTERFACE void MApp_Subtitle_Clear_ServiceData(BOOLEAN bUpdate);
INTERFACE void MApp_Subtitle_Force_Exit(void);
INTERFACE void MApp_Subtitle_Exit_ForAutoScart(void);
INTERFACE void MApp_Subtitle_OrgnizeServiceTbl(void);
INTERFACE void MApp_Subtitle_PID_Monitor(void);
INTERFACE void MApp_Subtitle_SetInvalidPID(void);
INTERFACE BOOLEAN MApp_Subtitle_IsRunning(void);
INTERFACE void MApp_Subtitle_PID_Updated(void);
INTERFACE void MApp_Subtitle_TimeOut_Clear(void);
INTERFACE BOOLEAN MApp_Subtitle_Initial(void);
INTERFACE BOOLEAN MApp_Subtitle_SetPid(U16 u16_pid);
INTERFACE BOOLEAN MApp_Subtitle_Select_Language(U8 SubtitleLang);
INTERFACE BOOLEAN MApp_Subtitle_SearchSubtitleLangPriority(EN_LANGUAGE* penLangList, U8 u8Number, BOOLEAN bIsHoH, BOOLEAN bIsHD, U8* pU8SelectIndex);

#if (ENABLE_DTV)
INTERFACE U8 MApp_TTX_Subtitle_ParsePMT(MS_TELETEXT_INFO *pTTXInfo, U16 pid, U8 u8NumOfTTX, BOOLEAN *bGotInitPage);
INTERFACE BOOLEAN MApp_TTX_Subtitle_GetData(U8 SubtitleIndex, U8 *Magazine, U8 *Page, U16 *u16Pid);
INTERFACE BOOLEAN MApp_TTX_Subtitle_GetDefaultLang(EN_LANGUAGE lang, U8 *Magazine, U8 *Page, U16 *u16Pid);
INTERFACE void MAPP_TTX_SUBTITLE_ONOFF(BOOLEAN bON);
#endif

//INTERFACE BOOLEAN MApp_Subtitle_SetPageId(U16 u16_component_page_id, U16 u16_ancillary_page_id);
//INTERFACE BOOLEAN MApp_Subtitle_IS_HoH(SUBTITLING_TYPE u8type);
INTERFACE EN_RET MApp_Subtitle_Main(void);
INTERFACE void MApp_Subtitle_OrgnizeServiceTbl(void);
INTERFACE void MApp_Subtitle_Switch2OP(void);
INTERFACE void MApp_Subtitle_Switch2IP(void);

INTERFACE void MApp_Subtitle_Exit(void);
INTERFACE void MApp_Subtitle_SetValidIndex(U8 type, U8* lang, U32 *pu32Validndex);
INTERFACE U8 MApp_Subtitle_ReArrange(U32 u32ValidIndex, U8 u8CurIdx);
INTERFACE void MApp_Subtitle_Open_Filter(U16 u16PID);
INTERFACE BOOLEAN MApp_Subtitle_IsTTXSubtitle(U8 SubtitleLang);
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
INTERFACE void MApp_Subtitle_SetShowStatus(BOOLEAN bShowStatus);
INTERFACE EN_SUBTITLE_STATE MApp_Subtitle_GetStatus(void);
INTERFACE BOOLEAN MApp_Subtitle_GetShowStatus(void);
INTERFACE void MApp_ReMoveUnShowSubtitle(void);
#endif
INTERFACE void MApp_SetSubtitleSelIdx(BOOLEAN bSelIdx);
INTERFACE BOOLEAN MApp_GetSubtitleSelIdx(void);
#else //ENABLE_SUBTITLE==0
#define MApp_Subtitle_PID_Updated()
#define MApp_Subtitle_Open_Filter(x)
#endif
#undef INTERFACE
#endif // _MAPP_SUBTITLE_H
