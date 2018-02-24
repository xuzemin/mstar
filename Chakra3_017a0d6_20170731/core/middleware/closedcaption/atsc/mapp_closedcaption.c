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

#define MAPP_CLOSED_CAPTION_C

/******************************************************************************/
/*                 Header Files                   */
/* ****************************************************************************/
#include <string.h>
#include <stdio.h>
#include "Board.h"

#if (ATSC_CC != NO_CC)

#include "datatype.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_Global.h"
#include "sysinfo.h"
#include "msAPI_Memory.h"
#include "apiGOP.h"
#include "msAPI_OSD.h"
#include "msAPI_VD.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_GlobalVar.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "mapp_closedcaption.h"
#include "../mapp_closedcaption_customer.h"
#include "MApp_VDMode.h"
#include "MApp_Font.h"
#include "MApp_SignalMonitor.h"
#include "MApp_Sleep.h"
#include "MApp_ZUI_ACTglobal.h"
//----VChip data moving
#if (ENABLE_ATSC)
#include "MApp_Psip.h"
#endif
#include "msAPI_Timer.h"
#include "Panel.h"

#if (SUPPORT_INSERT_CC_TO_VE == 1)
#include "msAPI_VE.h"
#endif

#if (PARSING_CC_WHENMUTE)
#include "MApp_Audio.h"
#endif

#if (ATSC_CC != ATV_CC)
#include "MApp_VChip.h"
#endif

#if (PARSING_CC_AUTO708TO608)
#define AUTOSWITCH_CCTIMEOUT            10000   //10sec
#define AUTOSWITCH_CCDETECTTIME         60000   //60sec
#endif

static CC_Buf_Content volatile *ag_ccBytesBuf = ((CC_Buf_Content volatile *)((CCVBI_RINGBUFFER_START_MEMORY_TYPE & MIU1) ? (CCVBI_RINGBUFFER_START_ADR | MIU_INTERVAL) : (CCVBI_RINGBUFFER_START_ADR)));

// Print out debug message
#define CC_DBINFO_CMD_1(x)              x // print out

#define CC_DBAPP(y)                     y

#define AUTO_VBI_CLEAR_CC_TIME          1000UL  // 1 sec

//#define CC_GOP_GWIN_ALPHA_VALUE         0x7f7f

/********************************************************************************/
/*                    global variable                                           */
/********************************************************************************/
extern U32 g_GWIN_ALIGND_VALUE;
//extern BOOLEAN bIsGwinEnabled;
U32 TestTime = 0;
//==============================================================================
/*                      Local                                                   */
//==============================================================================
#if (ATSC_CC == ATV_CC)
static EN_CAPTION_STATE enCCState = STATE_CAPTION_INIT;  //STATE_CAPTION_PARSER;
#define CC_SETTING DB_CC_SETTING.stCaptionSetting
#else
static EN_CAPTION_STATE enCCState = STATE_CAPTION_PARSER;
#define CC_SETTING stGenSetting.g_CaptionSetting
#endif

static EN_RET enCCRetVal;
static MS_U8 fHasCCShow = FALSE;
MS_U8 fEnableCCInit = FALSE;

#if (ATSC_CC == ATV_CC)
static EN_RET bEn = EXIT_CLOSE;
#else
static EN_RET bEn = EXIT_NULL;
#endif

#if (PARSING_CC_AUTO708TO608)
U32 g_u32CCAutoSwichStartTime;
#endif

#define PRG_CHANGE_BY_EVENT     1
#define PRG_CHANGE_BY_USER      2

// current event info
#if (ATSC_CC != ATV_CC)
#if(ENABLE_ATSC_EPG_DB_2016)
 static MS_EPG_EVENT_New current_event;    //modified in 20160617 for mantis 1146924:cc info abnormal!
#else
 static MS_EPG_EVENT current_event;    //modified in 20160617 for mantis 1146924:cc info abnormal!
#endif

 static U16 current_event_id ;
 static U8 u8StopSwitchServiceMode;
#endif

static U8 u8CurrentCaptionServiceMode;
static U8 u8CC608AvailableType, u8CC708AvailableType;

static BOOLEAN bProgramChanged=FALSE;
static U8 u8BkupGOPNum = NA;

//static stCaptionSettingType stCaptionSetting;
static stCaptionSettingVariables stCCVarSetting;
static U8 u8CCmode = SYSINFO_MODE_DTV;
static U8 u8GOPID, u8GWINID, u8GEMODE;
static U16 u16CaptionWidth, u16CaptionHeight;

static GOP_PaletteEntry _CCPaletteEntry[PALETTE_ENTRY_NUM] =
{
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0xff, 0x08, 0xff }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0xCC, 0xCC, 0xCC }},{{ 0x00, 0x54, 0x54, 0x54 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
    {{ 0x00, 0x0f, 0x0f, 0x0f }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0x00, 0x7f, 0x00 }},{{ 0x00, 0x7f, 0x7f, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},

    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0xff, 0x08, 0xff }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0xCC, 0xCC, 0xCC }},{{ 0x00, 0x54, 0x54, 0x54 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
    {{ 0x00, 0x0f, 0x0f, 0x0f }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0x00, 0x7f, 0x00 }},{{ 0x00, 0x7f, 0x7f, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},

    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0xff, 0x08, 0xff }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0xCC, 0xCC, 0xCC }},{{ 0x00, 0x54, 0x54, 0x54 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
    {{ 0x00, 0x0f, 0x0f, 0x0f }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0x00, 0x7f, 0x00 }},{{ 0x00, 0x7f, 0x7f, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},

    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0xff, 0x08, 0xff }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0xCC, 0xCC, 0xCC }},{{ 0x00, 0x54, 0x54, 0x54 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
    {{ 0x00, 0x0f, 0x0f, 0x0f }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0x00, 0x7f, 0x00 }},{{ 0x00, 0x7f, 0x7f, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},

    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0xff, 0x08, 0xff }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0xCC, 0xCC, 0xCC }},{{ 0x00, 0x54, 0x54, 0x54 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
    {{ 0x00, 0x0f, 0x0f, 0x0f }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0x00, 0x7f, 0x00 }},{{ 0x00, 0x7f, 0x7f, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},

    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0xff, 0x08, 0xff }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0xCC, 0xCC, 0xCC }},{{ 0x00, 0x54, 0x54, 0x54 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
    {{ 0x00, 0x0f, 0x0f, 0x0f }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0x00, 0x7f, 0x00 }},{{ 0x00, 0x7f, 0x7f, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},

    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0xff, 0x08, 0xff }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0xCC, 0xCC, 0xCC }},{{ 0x00, 0x54, 0x54, 0x54 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
    {{ 0x00, 0x0f, 0x0f, 0x0f }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0x00, 0x7f, 0x00 }},{{ 0x00, 0x7f, 0x7f, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},

    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0xff, 0x08, 0xff }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0xCC, 0xCC, 0xCC }},{{ 0x00, 0x54, 0x54, 0x54 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
    {{ 0x00, 0x0f, 0x0f, 0x0f }},{{ 0x00, 0xff, 0x00, 0x00 }},{{ 0x00, 0x00, 0xff, 0x00 }},{{ 0x00, 0xff, 0xff, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0xff }},{{ 0x00, 0xff, 0x00, 0xff }},{{ 0x00, 0x00, 0xff, 0xff }},{{ 0x00, 0xff, 0xff, 0xff }},
    {{ 0x00, 0x00, 0x00, 0x00 }},{{ 0x00, 0x7f, 0x00, 0x00 }},{{ 0x00, 0x00, 0x7f, 0x00 }},{{ 0x00, 0x7f, 0x7f, 0x00 }},
    {{ 0x00, 0x00, 0x00, 0x7f }},{{ 0x00, 0x7f, 0x00, 0x7f }},{{ 0x00, 0x00, 0x7f, 0x7f }},{{ 0x00, 0x7f, 0x7f, 0x7f }},
};

//==============================================================================
/*                      Functions                                               */
//==============================================================================
static void MApp_ClosedCaption_ProcessUserInput(void);

#if (CC_TV_TEST == 1)
static void MApp_UniTest(void);
#endif

///////////////////////////////////////////////////////////////////////////////
/// Normal APIs:
///
/// normal functions
///
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void MApp_ClosedCaption_Set_ProgramChange(void)
{
    CC_DBAPP(printf("\nSet_ProgramChange"));
    u8CC608AvailableType = 0;
    u8CC708AvailableType = 0;
    bProgramChanged = TRUE;
    CC_SourceFuns.ResetXDSInfo();    //benny added for mantis 1202661 in 20160919!
}

#if (PARSING_CC_AUTO708TO608)
static U8 MApp_ClosedCaption_Program_Change(void)
{
    CC_SourceFuns.ResetXDSInfo(); //benny added for mantis 1202661 in 20160919!
    if (bProgramChanged)
    {
        bProgramChanged = FALSE;
        CC_DBAPP(printf("\nreturn PRG_CHANGE_BY_USER"));
        return PRG_CHANGE_BY_USER;
    }

    MApp_EpgDB_GetCurEvent(&current_event);

    if (current_event_id != current_event.event_id)
    {
        CC_DBAPP(printf("\nCC monitor EVENT_ID CHANGE!! : current_event.event_id = %x \r\n",current_event.event_id));
        current_event_id = current_event.event_id;
        return PRG_CHANGE_BY_EVENT;
    }
    return FALSE;
}

/******************************************************************************/
static void MApp_ClosedCaption_Switch_Service_Mode(U8 mode)
{
    if (mode == CS_OFF)
        return;
    MApp_ClosedCaption_Stop();
    fEnableCCInit = FALSE;
    CC_SETTING.u8CaptionServiceMode = mode;
    u8CurrentCaptionServiceMode = mode;
    //MApp_VChip_Init();
    //Replace MApp_VChip_Init() by the following 2 initialization

    if( IsDTVInUse() )
        CC_SourceFuns.DrvInit( MSAPI_CC_TYPE_NTSC_TWOFIELD );
    else
        CC_SourceFuns.VbiInit((U32)(&ag_ccBytesBuf[0]));
    MApp_ClosedCaption_GetUserCmd();
    MApp_ClosedCaption_Init();
    fEnableCCInit = TRUE;
    enCCState = STATE_CAPTION_PARSER;
}
#endif

/******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
/// API for CC getting user command program::
/// Getting user commands for CC
/// @return void
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void MApp_ClosedCaption_GetUserCmd(void)
{
#if (ATSC_CC == DTV_CC)
    U8 u8Field=0;
#endif

    //----VChip data moving
#if (ATSC_CC != ATV_CC)
    u8StopSwitchServiceMode = 0;
#endif

    CC_DBINFO_CMD_1(printf("\n...[%s, %d] %d...\n", __FUNCTION__, __LINE__, CC_SETTING.u8CaptionServiceMode));

    if ( CC_SETTING.u8CaptionServiceMode == CS_OFF )
    {
        fEnableClosedCaptionFunc = FALSE;
        g_u8CCType_Option = MSAPI_CC_TYPE_NONE;
        u8CurrentCaptionServiceMode = CS_OFF;
        MApp_ClosedCaption_Stop();
        return;
    }

    //g_u32CCAutoSwichStartTime = msAPI_Timer_GetTime0();
    enCCState = STATE_CAPTION_INIT;

#if (ATSC_CC == DTV_CC)
    if(IsDTVInUse())
    {
        if ( (CC_SETTING.u8CaptionServiceModeATV == CS_CC1) || (CC_SETTING.u8CaptionServiceModeATV == CS_CC2) ||
             (CC_SETTING.u8CaptionServiceModeATV == CS_TEXT1) || (CC_SETTING.u8CaptionServiceModeATV == CS_TEXT2))
        {
             u8Field = 0;
        }
        else if (CC_SETTING.u8CaptionServiceModeATV != CS_OFF)
        {
            u8Field = 1;
        }

        MApp_EpgDB_GetCurEvent(&current_event);
        if (current_event_id == current_event.event_id)
        {
            CC_DBAPP(printf("\nEvent not changed"));
            if (CC_SETTING.u8CaptionServiceMode >= CS_SERVICE1)
            {
                if (u8CC708AvailableType & ( 1 << (CC_SETTING.u8CaptionServiceMode - CS_SERVICE1)))
                {
                    u8CurrentCaptionServiceMode = CC_SETTING.u8CaptionServiceMode;
                }
                else if ((u8CC608AvailableType & ((u8Field == 0)?0x33:0xcc)) && (CC_SETTING.u8CaptionServiceModeATV != CS_OFF))
                {
                    CC_SETTING.u8CaptionServiceMode = CC_SETTING.u8CaptionServiceModeATV;
                    u8CurrentCaptionServiceMode = CC_SETTING.u8CaptionServiceModeATV;
                }
                else
                {
                    u8CurrentCaptionServiceMode = CC_SETTING.u8CaptionServiceMode;
                }
            }
        }
        else
        {
            CC_DBAPP(printf("\nEvent changed: %d", CC_SETTING.u8CaptionServiceMode));
            u8CurrentCaptionServiceMode = CC_SETTING.u8CaptionServiceMode;
            u8CC608AvailableType = 0;
            u8CC708AvailableType = 0;
        }
        //20120821 max set ratio info to cc
        if(TRUE == current_event.fHasCCInfo)
        {
            if ((u8CurrentCaptionServiceMode >= CS_SERVICE1)
                &&(u8CurrentCaptionServiceMode <= CS_SERVICE6 )
                #if (PARSING_CC_WHENMUTE)
                &&(CC_SETTING.u8CCMode == CAPTIONMENU_MODE_ON ||CAPTIONMENU_MODE_CC_WHEN_MUTE))
                #else
                &&(CC_SETTING.u8CCMode == CAPTIONMENU_MODE_ON ))
                #endif
             {
                for (iu8Loop_i = 0; iu8Loop_i < current_event.stCaptionService.u8NumOfService; iu8Loop_i++)
                {
                    if(current_event.stCaptionService.stCaptionServiceItem[iu8Loop_i].bDigital_CC)
                    {
                        if((u8CurrentCaptionServiceMode-CS_TEXT4) == current_event.stCaptionService.stCaptionServiceItem[iu8Loop_i].u8CaptionSrvNum)
                        {
                            g_u8CC708_AspectRatio = current_event.stCaptionService.stCaptionServiceItem[iu8Loop_i].bWide_aspect_ratio;
                        }
                    }
                }
            }
        }
        else
        {
            g_u8CC708_AspectRatio = CAPTION_ASP_INVALID;
        }
    }
#endif // #if (ATSC_CC == DTV_CC)

    if ( ( CC_SETTING.u8CaptionServiceMode >= CS_CC1 ) && ( CC_SETTING.u8CaptionServiceMode <= CS_TEXT4 ) )
    {
        fEnableClosedCaptionFunc = TRUE;
        if ( ( CC_SETTING.u8CaptionServiceMode == CS_CC1 ) || ( CC_SETTING.u8CaptionServiceMode == CS_CC2 )  \
            || ( CC_SETTING.u8CaptionServiceMode == CS_TEXT1 ) || ( CC_SETTING.u8CaptionServiceMode == CS_TEXT2 ) )
        {
            g_u8CCType_Option = MSAPI_CC_TYPE_NTSC_FIELD1;
        }
        else
        {
            g_u8CCType_Option = MSAPI_CC_TYPE_NTSC_FIELD2;
        }
    }
#if (ATSC_CC == DTV_CC)
    else if ( ( CC_SETTING.u8CaptionServiceMode >= CS_SERVICE1 ) && ( CC_SETTING.u8CaptionServiceMode <= CS_SERVICE6 ) )
    {
        fEnableClosedCaptionFunc = TRUE;
        g_u8CCType_Option = MSAPI_CC_TYPE_DTVCC;
    }
#endif

    CC_DBINFO_CMD_1(printf("\n...[%s, %d] %d, %d...\n", __FUNCTION__, __LINE__, fEnableClosedCaptionFunc, g_u8CCType_Option));

   // msAPI_CC_ResetOsdSetting(&stCCVarSetting);  // temporary

}

/******************************************************************************/
void MApp_ClosedCaption_SysBuffer_Init(void)
{
    msAPI_CC_SetSysBuffer();
}

/******************************************************************************/
//#ifdef CC_MULTI_LANGUAGE
//extern stCaptionSettingType stCCOSDSetting;
//#endif
void MApp_ClosedCaption_Init(void)
{
    u8GEMODE = CC_GOP_MODE_I8;
    u8GOPID = CC_USING_GOP_ID;
    u8GWINID = CC_USING_GWIN_ID;

    if (fEnableClosedCaptionFunc == TRUE)
    {
        CC_DBINFO_CMD_1(printf("\n...[%s, %d] Init ->...\n", __FUNCTION__, __LINE__));
      #if (ATSC_CC == ATV_CC)
        MApp_ZUI_ACT_ShutdownOSD();
      #endif

        u8BkupGOPNum = MApi_GOP_GWIN_GetCurrentGOP();

      #ifdef CC_USE_MULTIPLE_GWINS
        MApi_GOP_GWIN_SwitchGOP(0);            // forced to '0'
      #else
        MApi_GOP_GWIN_SwitchGOP(u8GOPID);    // Following up the OSD
      //  msAPI_CC_SetGwinID(CC_USING_GOP_ID, CC_USING_GWIN_ID);
#if 0
        CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);
        CC_DecoderFuns.Initial();
        CC_RenderFuns.Init();
#endif
        printf("\n (%d), kepGOP:%d, cur gop:%d, gwin:%d", __LINE__, u8BkupGOPNum, CC_USING_GOP_ID, CC_USING_GWIN_ID);
      #endif
        MApp_CC_SetStretchWindow(u16CaptionWidth, u16CaptionHeight);
        MApp_CC_CtrlParser(CC_SELECTOR_RESET_TO_DEFAULT, TRUE);
        MApp_CC_CtrlParser(CC_SELECTOR_608_TIMEOUT_CAPITON, CC_CONFIG_608_TIMEOUT_CAPITON);
        MApp_CC_CtrlParser(CC_SELECTOR_708_TIMEOUT_CAPTION, CC_CONFIG_708_TIMEOUT_CAPTION);
        MApp_CC_CtrlParser(CC_SELECTOR_608_TIMEOUT_TEXT, CC_CONFIG_608_TIMEOUT_TEXT);
        MApp_CC_CtrlParser(CC_SELECTOR_TRANSLUCENT, CC_CONFIG_TRANSLUCENT);
        MApp_CC_CtrlParser(CC_SELECTOR_608_SCROLL_STEP, TRUE);
        //MApp_CC_CtrlParser(CC_SELECTOR_TEXT_ROWNO, CC_CONFIG_TEXT_ROWNO);
        MApp_CC_CtrlParser(CC_SELECTOR_INDENT_GAP, CC_CONFIG_INDENT_GAP);
        MApp_CC_CtrlParser(CC_SELECTOR_DUMP_DBG_MSG, CC_CONFIG_DUMP_DBG_MSG);
        //MApp_CC_CtrlParser(CC_SELECTOR_DTV_AXIS_YPOS, CC_CONFIG_DTV_AXIS_YPOS);
        //MApp_CC_CtrlParser(CC_SELECTOR_ROW_TOPRSVHEIGHT , CC_CONFIG_ROW_TOPRSVHEIGHT);
        //MApp_CC_CtrlParser(CC_SELECTOR_ROW_BTMRSVHEIGHT , CC_CONFIG_ROW_BTMRSVHEIGHT);

        MApp_CC_CtrlParser(CC_SELECTOR_ATV_AXIS_XPOS, CC_CONFIG_ATV_AXIS_XPOS);
        #if (KOREAN_CC_ENABLE)
        if(CC_SETTING.u8CaptionServiceModeATV == CS_CC3)
            MApp_CC_CtrlParser(CC_SELECTOR_ATV_AXIS_YPOS, CC_CONFIG_ATV_AXIS_YPOS);
        #else
#if ((CHIP_FAMILY_TYPE != CHIP_FAMILY_WHISKY)||(MEMORY_MAP > MMAP_32MB))
            MApp_CC_CtrlParser(CC_SELECTOR_ATV_AXIS_YPOS, CC_CONFIG_ATV_AXIS_YPOS);
#endif
        #endif

        /* In the following code sequence, it should be called in order */
        CC_DecoderFuns.SetFontHandle(&Font_CC[0]);

        msAPI_CC_SetSysBuffer();
        //msAPI_CC_ResetOsdSetting(&stCCVarSetting);  // Just in temporal...next time replaced by 'MApp_CC_CtrlParser'
        msAPI_CC_AllocateMemory(g_u8CCType_Option);
        msAPI_CC_ClearBuffer();
        msAPI_CC_SetOsdSetting(&CC_SETTING);
        //----VChip data moving
        #if (ATSC_CC == DTV_CC)
        if(IsDTVInUse())
        {
            #if (PARSING_CC_AUTO708TO608)
            if (MApp_ClosedCaption_Program_Change())
            {
                if (u8CurrentCaptionServiceMode != CC_SETTING.u8CaptionServiceMode)
                    u8CurrentCaptionServiceMode = CC_SETTING.u8CaptionServiceMode;
                u8StopSwitchServiceMode = 0;
                u8CC708AvailableType = 0;
                u8CC608AvailableType = 0;
            }
            g_u32CCAutoSwichStartTime = msAPI_Timer_GetTime0();
            #endif
            MApp_EpgDB_GetCurEvent(&current_event);
            //20120821 max set ratio info to cc
            if(TRUE == current_event.fHasCCInfo)
            {
                if ((u8CurrentCaptionServiceMode >= CS_SERVICE1)
                    &&(u8CurrentCaptionServiceMode <= CS_SERVICE6 )
                    #if (PARSING_CC_WHENMUTE)
                    &&(CC_SETTING.u8CCMode == CAPTIONMENU_MODE_ON ||CAPTIONMENU_MODE_CC_WHEN_MUTE))
                    #else
                    &&(CC_SETTING.u8CCMode == CAPTIONMENU_MODE_ON ))
                    #endif
                 {
                    for (iu8Loop_i = 0; iu8Loop_i < current_event.stCaptionService.u8NumOfService; iu8Loop_i++)
                    {
                        if(current_event.stCaptionService.stCaptionServiceItem[iu8Loop_i].bDigital_CC)
                        {
                            if((u8CurrentCaptionServiceMode-CS_TEXT4) == current_event.stCaptionService.stCaptionServiceItem[iu8Loop_i].u8CaptionSrvNum)
                            {
                                g_u8CC708_AspectRatio = current_event.stCaptionService.stCaptionServiceItem[iu8Loop_i].bWide_aspect_ratio;
                            }
                        }
                    }
                }
            }
            else
            {
                g_u8CC708_AspectRatio = CAPTION_ASP_INVALID;
            }

            msAPI_CC_InitialData(g_u8CCType_Option,TRUE);
        }
        else
        #endif
        {
            #if (ATSC_CC == ATV_CC)
                CC_SourceFuns.VbiInit((U32)(&ag_ccBytesBuf[0]));
            #endif
            msAPI_CC_InitialData(g_u8CCType_Option,FALSE);
        }

        CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);
        CC_DecoderFuns.Initial();
        CC_RenderFuns.Init();

        msAPI_CC_WakeUp();
    #if ( MEMORY_MAP != MMAP_16MB )
        //msAPI_CC_BlockInit(0, DTVCC_BLOCK0_START_ADR, DTVCC_BLOCK0_START_LEN);
        //msAPI_CC_BlockInit(1, DTVCC_BLOCK1_START_ADR, DTVCC_BLOCK1_START_LEN);
    #endif
        // enable VE
    #if (SUPPORT_INSERT_CC_TO_VE == 1)
        msAPI_VE_Init();
        msAPI_VE_EnableCC(TRUE);
    #endif
        CC_DBINFO_CMD_1(printf("\n...[%s, %d] <- Init...\n", __FUNCTION__, __LINE__));

        bEn = EXIT_CLOSEDCAPTION_DONE;
    }
}
/******************************************************************************/

void MApp_ClosedCaption_Exit(void)
{
    if(enCCState == STATE_CAPTION_PARSER)
    {
        CC_DBINFO_CMD_1(printf("\n...[%s, %d] exit ->...\n", __FUNCTION__, __LINE__));
         MApp_ClosedCaption_Stop();

         if( IsDTVInUse() )
             CC_SourceFuns.DrvInit( MSAPI_CC_TYPE_NTSC_TWOFIELD );
         else
             CC_SourceFuns.VbiInit((U32)(&ag_ccBytesBuf[0]));



         if(MApi_GOP_GWIN_GetCurrentGOP() != CC_USING_GOP_ID )
            MApi_GOP_GWIN_SwitchGOP(CC_USING_GOP_ID);

         // Recover the stretch
         // MApp_CC_SetStretchWindow(0, 0);

#if(    (UI_SKIN_SEL ==  UI_SKIN_1366X768X4444) \
        ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X565) \
        ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X8888) \
        ||(UI_SKIN_SEL ==  UI_SKIN_960X540X565))
        #if ((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE))
			#if ENABLE_854x480_UI
	        if((g_IPanel.Width() >= 854) && (g_IPanel.Height() >= 480))
	        {
	            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
	            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,854, 480);
	            MApi_GOP_GWIN_Set_HSCALE(TRUE,854,PANEL_WIDTH);
	            MApi_GOP_GWIN_Set_VSCALE(TRUE, 480, PANEL_HEIGHT);
	        }
			#else
	        if((g_IPanel.Width() >= 960) && (g_IPanel.Height() >= 540))
	        {
	            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
	            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,960, 540);
	            MApi_GOP_GWIN_Set_HSCALE(TRUE,960,PANEL_WIDTH);
	            MApi_GOP_GWIN_Set_VSCALE(TRUE, 540, PANEL_HEIGHT);
	        }
			#endif
        #else
        if((g_IPanel.Width() >= ZUI_ALIGNED_VALUE(1366,16)) && (g_IPanel.Height() >= 768))
        {
            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0, ZUI_ALIGNED_VALUE(1366,16), 768);
            MApi_GOP_GWIN_Set_HSCALE(TRUE,ZUI_ALIGNED_VALUE(1366,16),PANEL_WIDTH);
            MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, PANEL_HEIGHT);
        }
        #endif
#elif(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
if((g_IPanel.Width() >= 1920) && (g_IPanel.Height() >= 1080))
        {
            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,UI_OSD_PANE_W, UI_OSD_PANE_H);
            MApi_GOP_GWIN_Set_HSCALE(TRUE,UI_OSD_PANE_W,PANEL_WIDTH);
            MApi_GOP_GWIN_Set_VSCALE(TRUE, UI_OSD_PANE_H, PANEL_HEIGHT);
        }
#endif
         // Switch gop
        if(u8BkupGOPNum != NA)
         {
             //printf("\n (%d), kepGOP:%d, cur gop:%d, gwin:%d", __LINE__, u8BkupGOPNum, CC_USING_GOP_ID, CC_USING_GWIN_ID);
            MApi_GOP_GWIN_SwitchGOP(u8BkupGOPNum);
            u8BkupGOPNum = NA;
          }

        CC_RenderFuns.Close();

     CC_DBINFO_CMD_1(printf("\n...[%s, %d] exit  < -...\n", __FUNCTION__, __LINE__));
     }

     enCCRetVal = EXIT_CLOSEDCAPTION_DONE;
     enCCState = STATE_CAPTION_INIT;
     fEnableCCInit = FALSE;

}

/******************************************************************************/
void MApp_ClosedCaption_Stop(void)
{
    CC_DBINFO_CMD_1(printf("\n...[%s, %d] stop -> ...\n", __FUNCTION__, __LINE__));
    CC_SourceFuns.Stop708Parsing();
    msAPI_CC_DeleteMemory();
    msAPI_CC_SetInputData(CC_INPUT_CAPTIONTYPE, MSAPI_CC_TYPE_NONE);
    if (fEnableCCInit)
    {
        CC_RenderFuns.Reset();
    }
    fEnableCCInit = FALSE;

    MApi_GOP_GWIN_SetDuplication(FALSE, FALSE);
    //MApi_GOP_GWIN_SetPalette();
    MApi_GOP_GWIN_SetPaletteOpt(_CCPaletteEntry, 0, 255, E_GOP_PAL_ARGB8888);
    enCCState = STATE_CAPTION_INIT;

  #if  (ATSC_CC == DTV_CC)
    MApp_EpgDB_GetCurEvent(&current_event);
    if ((current_event_id != current_event.event_id) && IsDTVInUse())
    {
        msAPI_CC_Reset();
    }
  #endif

    CC_DBINFO_CMD_1(printf("\n...[%s, %d] stop < - ...\n", __FUNCTION__, __LINE__));
    //CC708_Position_Dbg = 1;
}

/******************************************************************************/
static void MApp_ClosedCaption_ProcessUserInput(void)
{
    switch(u8KeyCode)
    {
        case KEY_NULL:
        case 0x27:      // Just using in temporary
            if (fEnableCCInit == FALSE)
                enCCState = STATE_CAPTION_INIT;
            else
            {
                enCCState = STATE_CAPTION_PARSER;
            }
            break;
            //20120727 Max fix invalid key will exit CC
            case KEY_UP:
            case KEY_EXIT:
            case KEY_DOWN:
            case KEY_RIGHT:
            case KEY_LEFT:
            case KEY_BACK:
            case KEY_RED:
            case KEY_GREEN:
            case KEY_YELLOW:
            case KEY_BLUE:
#if (ENABLE_CEC)
            case KEY_STOP:
#if (ENABLE_PVR == FALSE)
            case KEY_RECORD:
#endif
#endif
            case KEY_INDEX:
            case KEY_CLOCK:
            case KEY_FF:
            case KEY_REWIND:
            case KEY_NEXT:
            case KEY_PREVIOUS:
            case KEY_PAGE_UP:
            case KEY_PAGE_DOWN:
            case KEY_PAUSE:
            case KEY_PLAY:
            case KEY_SELECT:
            break;


        default:
            MApp_ClosedCaption_Exit();
        break;
    }

#if (ENABLE_ATSC)
  #if  ((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC))
    if( MApp_Sleep_GetSleepTimerCountDownStatus() )
    {
        MApp_ClosedCaption_Exit();
    }
  #endif
#endif

    // Don't clear the IR Key
    //u8KeyCode = KEY_NULL;
}


/******************************************************************************/
#if (CC_TV_TEST == 1)
U32 u32FirstChk=0;
#endif

EN_RET MApp_ClosedCaption_Main(void)
{
    //printf("[%s][%d] fEnableClosedCaptionFunc: %d\n", __FUNCTION__, __LINE__, fEnableClosedCaptionFunc);//yym
  #if  (ATSC_CC == DTV_CC)
    U8 fCC608, fCC708, u8PrgChg;
    U32 u32TimeDiff;

    u8PrgChg = 0;
  #endif

    enCCRetVal = EXIT_CLOSEDCAPTION_NULL;

#if (CC_TV_TEST == 1)
    // -- For testing --------------------------->
    if(u32FirstChk == 0)
    {
        u32FirstChk = msAPI_Timer_GetTime0();
    }

    if((msAPI_Timer_GetTime0()-u32FirstChk) < (100))
    {
        printf("+");
        return EXIT_CLOSEDCAPTION_DONE;
    }
    else
    {
        if(u32FirstChk != 1000000)
        {
            u32FirstChk = 0;
            if(u32FirstChk == 0)
            {
                MApp_UniTest();     // test
                u32FirstChk = 1000000;
                printf("\n-- start to parse --\n\n\n");
            }
        }
    }
    // <------------------------------------------
#endif

    //printf("\n[%d]", msAPI_Timer_GetTime0()-u32KeepLast);
    if(fEnableClosedCaptionFunc == FALSE)
    {
        return EXIT_CLOSEDCAPTION_DONE;
    }

#if (ATSC_CC == DTV_CC)
  #if(ENABLE_ATSC_VCHIP)
    if (MApp_VChip_GetCurVChipBlockStatus())
    {
        if(fEnableCCInit == TRUE) // MApp_ClosedCaption_Init have been called before
        {
            MApp_ClosedCaption_Exit();
        }
        else
        {
            enCCRetVal = EXIT_CLOSEDCAPTION_DONE;
            enCCState = STATE_CAPTION_INIT;
        }
        return enCCRetVal;
    }
  #endif
#endif

    switch(enCCState)
    {
        case STATE_CAPTION_INIT:
            if (fEnableCCInit == FALSE)
            {
            #if(ATSC_CC == DTV_CC)
              #if (PARSING_CC_WHENMUTE)
                if (fEnableCCWhenMuteFunc)
                {
                    if(IsDTVInUse())
                    {
                        if (CC_SETTING.u8CaptionServiceModeDTV != CAPTIONMENU_SERVICE_OFF)
                            CC_SETTING.u8CaptionServiceMode = CC_SETTING.u8CaptionServiceModeDTV;
                        else
                            CC_SETTING.u8CaptionServiceMode = CC_SETTING.u8CaptionServiceModeATV;
                    }
                    else
                    {
                        CC_SETTING.u8CaptionServiceMode = CC_SETTING.u8CaptionServiceModeATV;
                    }
                    MApp_ClosedCaption_GetUserCmd();
                }
              #endif
            #endif
                MApp_ClosedCaption_Init();
                if(!bEn)
                {
                    printf("\n...CC init failed");
                    bEn = EXIT_CLOSEDCAPTION_NULL;
                    break;
                }

                fEnableCCInit = TRUE;
                fHasCCShow = FALSE;
            }
            enCCState = STATE_CAPTION_PARSER;
        break;

        case STATE_CAPTION_PARSER:
            if(CC_USING_GOP_ID != MApi_GOP_GWIN_GetCurrentGOP())
            {
                MApi_GOP_GWIN_SwitchGOP(u8GOPID);
                MApi_GOP_GWIN_Switch2Gwin(u8GWINID);
                CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);
            }

            MApp_ClosedCaption_ProcessUserInput();
            if (enCCState == STATE_CAPTION_PARSER)
            {
                if(IsDTVInUse())
                {
                #if (ATSC_CC == DTV_CC)
                    if((MApp_GetSignalLockStatus()==FE_LOCK)
                        //&& msAPI_CC_GetMVDDecodeStatus()
                        && !MApp_VChip_GetCurVChipBlockStatus())
                    {
                    #if (PARSING_CC_AUTO708TO608)
                        fCC708 = msAPI_CC_DigitalCC708_Available();
                        fCC608 = msAPI_CC_DigitalCC608_Available();
                        u8CC708AvailableType = msAPI_CC_DigitalCC708_AvailableType();
                        u8CC608AvailableType = msAPI_CC_CC608_AvailableType();
                        u8PrgChg = MApp_ClosedCaption_Program_Change();
                        if (u8PrgChg == PRG_CHANGE_BY_EVENT)
                        {
                            u8CC708AvailableType = msAPI_CC_DigitalCC708_AvailableType();
                            u8CC608AvailableType = msAPI_CC_CC608_AvailableType();
                            if (fCC708 && (u8CC708AvailableType & ( 1 << (CC_SETTING.u8CaptionServiceMode - CS_SERVICE1))))
                            {
                                if ((u8CurrentCaptionServiceMode != CC_SETTING.u8CaptionServiceModeDTV) &&
                                    (CC_SETTING.u8CaptionServiceModeDTV != CS_OFF))
                                {
                                    // Mode Changed
                                    MApp_ClosedCaption_Switch_Service_Mode(CC_SETTING.u8CaptionServiceModeDTV);
                                    CC_DBAPP(printf("\nA === ======  \r\n"));
                                }
                            }
                            g_u32CCAutoSwichStartTime = msAPI_Timer_GetTime0();
                            CC_DBAPP(printf("\nPg changed: %d: %u:%u %d", g_u32CCAutoSwichStartTime, fCC708, u8CC708AvailableType, u8CC608AvailableType));
                            u8StopSwitchServiceMode = 0;
                        }
                        else if (u8PrgChg == PRG_CHANGE_BY_USER)
                        {
                            CC_DBAPP(printf("\nPRG_CHANGE_BY_USER"));
                            u8CC708AvailableType = 0;
                            u8CC608AvailableType = 0;
                            if ((u8CurrentCaptionServiceMode != CC_SETTING.u8CaptionServiceModeDTV) &&
                                (CC_SETTING.u8CaptionServiceModeDTV != CS_OFF))
                            {
                                // Mode Changed
                                MApp_ClosedCaption_Switch_Service_Mode(CC_SETTING.u8CaptionServiceModeDTV);
                                CC_DBAPP(printf("\nB === ======  \r\n"));
                            }
                            g_u32CCAutoSwichStartTime = msAPI_Timer_GetTime0();
                            CC_DBAPP(printf("\nB-Pg changed: %d", g_u32CCAutoSwichStartTime));
                            u8StopSwitchServiceMode = 0;
                        }

                        u32TimeDiff = msAPI_Timer_DiffTimeFromNow(g_u32CCAutoSwichStartTime);
                        if (u32TimeDiff < AUTOSWITCH_CCDETECTTIME)
                        {
                            if (u8StopSwitchServiceMode == 0)
                            {
                                if ((u32TimeDiff > AUTOSWITCH_CCTIMEOUT) && (u8CurrentCaptionServiceMode >= CS_SERVICE1) && ((!fCC708) ||(!(u8CC708AvailableType & ( 1 << (CC_SETTING.u8CaptionServiceMode - CS_SERVICE1))))))
                                {
                                    MApp_ClosedCaption_Switch_Service_Mode(CC_SETTING.u8CaptionServiceModeATV);
                                }

                                if (((u8CC708AvailableType & ( 1 << (CC_SETTING.u8CaptionServiceModeDTV - CS_SERVICE1))))&&(fCC708))
                                {
                                    if (u8CurrentCaptionServiceMode < CS_SERVICE1)
                                    {
                                        MApp_ClosedCaption_Switch_Service_Mode(CC_SETTING.u8CaptionServiceModeDTV);
                                    }
                                    u8StopSwitchServiceMode = 1;
                                }
                            }
                        }
                        msAPI_CC_Parser(1, fEnableClosedCaptionFunc);
                    #else
                        msAPI_CC_Parser(1, fEnableClosedCaptionFunc);
                    #endif // #if (PARSING_CC_AUTO708TO608)

                        if(fTableVersionChanged){
                        MApp_ClosedCaption_Exit();
                        }
                    }
                    else
                    {
                        MApp_ClosedCaption_Exit();
                    }
                #endif // #ifndef NTSC_CC_ON_DVB
                }
                else if ( (MApp_VD_IsSyncLock() && IsDigitalSourceInUse())
                    #ifndef DISABLE_COMPONENT_VBI
                    ||(!MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW) && IsYPbPrInUse())
                    #endif
                    )
                {
                  #if  (ATSC_CC == DTV_CC)
                    if (!MApp_VChip_GetCurVChipBlockStatus())
                    {
                        msAPI_CC_Parser(0, fEnableClosedCaptionFunc);
                    }
                    else
                    {
                        MApp_ClosedCaption_Exit();
                    }
                  #else
                    msAPI_CC_Parser(0, fEnableClosedCaptionFunc);
                  #endif
                }
                else
                {   // analog no sync
                    MApp_ClosedCaption_Exit();
                }
            }
            break;

        default:
            enCCState = STATE_CAPTION_PARSER;
        break;
    }

    return enCCRetVal;
}

///////////////////////////////////////////////////////////////////////////////
///
///
/// API for UI Interface:
///
///
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// API to init Closed-caption
///
/// @return void
///////////////////////////////////////////////////////////////////////////////
void MApp_CC_Initialize(void)
{
    CC_SourceFuns.VbiInit((U32)(&ag_ccBytesBuf[0]));
    msAPI_CC_VchipRateReset();

    if(IsDTVInUse())
    {
        CC_SourceFuns.DrvInit(MSAPI_CC_TYPE_NTSC_TWOFIELD);
        CC_SourceFuns.DrvInit(MSAPI_CC_TYPE_DTVCC);
    }

    msAPI_CC_SetSysBuffer();
    msAPI_CC_SetDrvVar();    //msAPI_CC_ResetGWIN();
    msAPI_CC_Reset();
    msAPI_CC_CCInfoInit();  // It would be put another place in the future ?
    fEnableCCInit = FALSE;
    enCCState = STATE_CAPTION_INIT;
    g_fCCAttrFlag.fCCAttr_Font_Indention_Flag = FALSE;
    g_fCCAttrFlag.fCCAttr_EnableWindowOptionSetting = FALSE;
    MApp_CC_CtrlParser(CC_SELECTOR_CC_CHECK_PERIOD, CC_CONFIG_CHECK_PERIOD);
    MApp_CC_CtrlParser(CC_SELECTOR_TRANSLUCENT, CC_CONFIG_TRANSLUCENT);
    msAPI_CC_SetInputData(CC_INPUT_USING157, CC_CONFIG_INPUT_USING157);
    u16CaptionWidth = CC_ALIGNED_VALUE((CC_U16)msAPI_CC_Panel_WIDTH(), g_GWIN_ALIGND_VALUE) - g_GWIN_ALIGND_VALUE;
    u16CaptionHeight = (CC_U16)msAPI_CC_Panel_HEIGHT();
    CC_RenderFuns.SetCcInfo(NULL, CC_DISWINDOW_WIDTH, u16CaptionWidth);
    CC_RenderFuns.SetCcInfo(NULL, CC_DISWINDOW_HEIGHT, u16CaptionHeight);
}

///////////////////////////////////////////////////////////////////////////////
/// API to run the Closed-caption parser
///
/// @return error code
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_CC_CheckExist(void)
{
#if (ATSC_CC != ATV_CC)
    if (IsDTVInUse())
    {
        return (BOOLEAN)(
        //(MApp_EpgDB_GetCurEvent(&current_event) && (current_event.fHasCCInfo))  //yym@2014-2-10 Don't reference EPG info
        (msAPI_CC_DigitalCC708_Available())
        || (msAPI_CC_DigitalCC608_Available())
        );
    }
    else
#endif
    {
        return (BOOLEAN)(msAPI_CC_AnalogCC608_Available());
    }
}
///////////////////////////////////////////////////////////////////////////////
/// API to run the Closed-caption parser
///
/// @return error code
///////////////////////////////////////////////////////////////////////////////
U32 MApp_CC_StartParser(void)
{
    // enable CC
    fEnableClosedCaptionFunc = TRUE;

    // return
    return  CC_ERRORCODE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// API to set the data to the given position of the buffer
///
/// @param selector /b IN
/// @param value /b IN the selector's value
/// @return error code
///////////////////////////////////////////////////////////////////////////////
U32 MApp_CC_CtrlParser(U32 selector, U32 value)
{
    CC_DBINFO_CMD_1(printf("\n...[%s, %d] selector=0x%x, val=0x%x...\n", __FUNCTION__, __LINE__, selector, value));

    // Functionality select
    switch (selector)
    {
        //--------------------------------------------------------------------------
        //  action
        //--------------------------------------------------------------------------
        case CC_SELECTOR_MODE:

            if(value != SYSINFO_MODE_ATV)
            {
                u8CCmode = SYSINFO_MODE_DTV;
            }
            else
            {
                u8CCmode = SYSINFO_MODE_ATV;
            }

            break;

        case CC_SELECTOR_SERVICE:

            if(IsDTVInUse())
            {
                CC_SETTING.u8CaptionServiceModeDTV = value;
            }
            else
            {
                CC_SETTING.u8CaptionServiceModeATV = value;
            }

            CC_SETTING.u8CaptionServiceMode = value;

            MApp_ClosedCaption_GetUserCmd();

            break;

        case CC_SELECTOR_RESET_TO_DEFAULT:

            if(value != 0)
            {
                msAPI_CC_ResetOsdSetting(&stCCVarSetting);
            }

            break;

        //--------------------------------------------------------------------------
        //  attribute
        //--------------------------------------------------------------------------


        //--------------------------------------------------------------------------
        //  offset, length...
        //--------------------------------------------------------------------------
        case CC_SELECTOR_ROW_TOPRSVHEIGHT:

            if(u8CCmode == SYSINFO_MODE_DTV)
            {
                stCCVarSetting.u32Row_708_toprsvheight = value;
            }
            else
            {
                stCCVarSetting.u32Row_608_toprsvheight = value;
            }

            break;

        case CC_SELECTOR_ROW_BTMRSVHEIGHT:

            if(u8CCmode == SYSINFO_MODE_DTV)
            {
                stCCVarSetting.u32Row_708_btmrsvheight = value;
            }
            else
            {
                stCCVarSetting.u32Row_608_btmrsvheight = value;
            }

            break;

        case CC_SELECTOR_ATV_AXIS_XPOS:

            stCCVarSetting.u32ATV_Axis_xpos = value;

            break;

        case CC_SELECTOR_ATV_AXIS_YPOS:

            stCCVarSetting.u32ATV_Axis_ypos = value;

            break;

        case CC_SELECTOR_DTV_AXIS_XPOS:

            stCCVarSetting.u32DTV_Axis_xpos = value;

            break;

        case CC_SELECTOR_DTV_AXIS_YPOS:

            stCCVarSetting.u32DTV_Axis_ypos = value;

            break;

        case CC_SELECTOR_CC_LANG:

            stCCVarSetting.u32Cc_lang = (EN_CAPTION_FONT)value;

            break;

        case CC_SELECTOR_TEXT_ROWNO:

            stCCVarSetting.u32Text_608_rowno = value;

            break;

        case CC_SELECTOR_TEXT_YPOS:

            stCCVarSetting.u32Text_608_ypos = value;

            break;

        case CC_SELECTOR_608_SCROLL_STEP:

            stCCVarSetting.u32CC_608_ScrollStep = value;

            break;

        case CC_SELECTOR_608_TIMEOUT_CAPITON:

            stCCVarSetting.u32Timeout_608_capiton = value;

            break;

        case CC_SELECTOR_608_TIMEOUT_TEXT:

            stCCVarSetting.u32Timeout_608_text = value;

            break;

        case CC_SELECTOR_708_TIMEOUT_CAPTION:

            stCCVarSetting.u32Timeout_708_caption = value;

            break;

        case CC_SELECTOR_CC_CHECK_PERIOD:

            msAPI_CC_SetInputData(CC_INPUT_PERIODTIME, value);

            break;

        case  CC_SELECTOR_TRANSLUCENT:

            CC_RenderFuns.SetCcInfo(0, CC_TRANSTUCENT_VALUE, value);

            break;

        case CC_SELECTOR_INDENT_GAP:
        {
            CC_RenderFuns.SetCcInfo(0, CC_FONT_INDENTGAP, value);
        }
            break;


        case CC_SELECTOR_DUMP_DBG_MSG:
        {
            CC_SourceFuns.SetInputInfo(CC_INPUT_DUMP_DBG_MSG, (void *)&value);
        }
        break;
        //--------------------------------------------------------------------------
        //  default...
        //--------------------------------------------------------------------------
        default:

            printf("\n...[%s, %d] failed...\n", __FUNCTION__, __LINE__);

    }

    // updated
    if((selector >= CC_SELECTOR_ROW_TOPRSVHEIGHT) && (selector <= CC_SELECTOR_DEBUG))
    {
        msAPI_CC_SetVarSetting(&stCCVarSetting);
    }

    return  CC_ERRORCODE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// API to stop the Closed-caption parser
///
/// @return error code
///////////////////////////////////////////////////////////////////////////////
U32 MApp_CC_StopParser(void)
{
    // disable CC
    fEnableClosedCaptionFunc = FALSE;

    // disable VE
  #if (SUPPORT_INSERT_CC_TO_VE == 1)
    msAPI_VE_EnableCC(FALSE);
    msAPI_VE_Close();
  #endif
    // exit CC flow
    MApp_ClosedCaption_Exit();

    // return
    return  CC_ERRORCODE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// API to get the closed-caption's info
///
/// @param selector /b IN
/// @return given value
///////////////////////////////////////////////////////////////////////////////
U32 MApp_CC_GetInfo(U32 selector)
{

    CC_DBINFO_CMD_1(printf("\n...[%s, %d] selector=0x%x...\n", __FUNCTION__, __LINE__, selector));

    // Functionality select
    switch (selector)
    {
        case CC_SELECTOR_ERROR_CODE:
            return  ((U32)CC_ERRORCODE_SUCCESS);

            break;

        case CC_SELECTOR_STATUS_CODE:
            return  ((U32)enCCState);

            break;

        default:
            printf("\n...[%s, %d] failed...\n", __FUNCTION__, __LINE__);
    }

    return  CC_ERRORCODE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// API to get the closed-caption's info
///
/// @param selector /b IN
/// @return given value
///////////////////////////////////////////////////////////////////////////////
void MApp_CC_SetStretchWindow(U16 u16StretchWidth, U16 u16StretchHeight)
{
    // SH@20091229, to prevent the blinking when turning on the OSD
    MApi_GOP_GWIN_SwitchGOP(CC_USING_GOP_ID);
    MApi_GOP_GWIN_Set_STRETCHWIN(CC_USING_GOP_ID, E_GOP_DST_OP0, 0, 0, u16StretchWidth, u16StretchHeight);
    MApi_GOP_GWIN_Set_HSCALE(TRUE, u16StretchWidth, devPanel_WIDTH());
    MApi_GOP_GWIN_Set_VSCALE(TRUE, u16StretchHeight, devPanel_HEIGHT());
}

///////////////////////////////////////////////////////////////////////////////
/// Unitest program for Closed-caption
///
///
///
///////////////////////////////////////////////////////////////////////////////
#if (CC_TV_TEST == 1)
void MApp_UniTest(void)
{
    U32 u32Err;

    printf("\n...[%s, %d] enter...\n", __FUNCTION__, __LINE__);

    u32Err = 0;
    /*
     *  DTV
     */
    if(IsDTVInUse())
    {

#if 0
        // Set caption mode
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_MODE, CC_MODE_DTV);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Set caption service
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_SERVICE, CS_SERVICE1);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Start to parse
        u32Err = MApp_CC_StartParser();
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }
#else
        msAPI_CC_ResetOsdSetting(&stCCVarSetting);  // temporary
        CC_SETTING.u8CaptionServiceMode = CS_SERVICE1;
        MApp_ClosedCaption_GetUserCmd();
#endif

    }

    /*
     *  ATV
     */
    else
    {

#if 0
        // Set caption mode
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_MODE, CC_MODE_ATV);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Set caption service
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_SERVICE, CC_SERVICE_CC3);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Reset to default values --> Be run after 'Set caption mode'
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_RESET_TO_DEFAULT, ENABLE);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Set font size
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_CC_LANG, CC_FONTSIZE_NORMAL);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Start to parse
        u32Err = MApp_CC_StartParser();
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

#else
        msAPI_CC_ResetOsdSetting(&stCCVarSetting);
        CC_SETTING.u8CaptionServiceMode = CS_CC1;
        MApp_ClosedCaption_GetUserCmd();
#endif

    }

}
#endif

void MApp_ClosedCaption_MapUIDefaultSetting(stCaptionSettingOption_Type *BlinkAttr)
{
    #if Support_Caption_Preview
    if(BlinkAttr->u8CSOptionFGColor == CAPTION_FGCOLOR_DEFAULT)
        BlinkAttr->u8CSOptionFGColor = CAPTION_FG_WHITE;

    if(BlinkAttr->u8CSOptionBGColor == CAPTION_BGCOLOR_DEFAULT)
        BlinkAttr->u8CSOptionBGColor  = CAPTION_BG_BLACK;

    if(BlinkAttr->u8CSOptionWindowColor == CAPTION_WINDOWCOLOR_DEFAULT)
        BlinkAttr->u8CSOptionWindowColor  = CAPTION_WINDOW_BLACK;

    if(BlinkAttr->u8CSOptionFGOpacity == CAPTION_FGOPACITY_DEFAULT)
        BlinkAttr->u8CSOptionFGOpacity = CAPTION_FG_SOLID;

    if(BlinkAttr->u8CSOptionBGOpacity == CAPTION_BGOPACITY_DEFAULT)
        BlinkAttr->u8CSOptionBGOpacity = CAPTION_BG_SOLID;

    if(BlinkAttr->u8CSOptionWindowOpacity == CAPTION_WINDOWOPACITY_DEFAULT)
        BlinkAttr->u8CSOptionWindowOpacity  = CAPTION_WINDOW_SOLID;

    if(BlinkAttr->u8CSFontSize == CAPTION_FONTSIZE_DEFAULT)
        BlinkAttr->u8CSFontSize  = CAPTION_FONTSIZE_NORMAL;

    if(BlinkAttr->u8CSFontStyle == CAPTION_FONTSTYLE_DEFAULT)
        BlinkAttr->u8CSFontStyle  = CAPTION_FONTSTYLE_0;

    if(BlinkAttr->u8CSOptionEdgeStyle == CAPTION_EDGESTYLE_DEFAULT)
        BlinkAttr->u8CSOptionEdgeStyle  = CAPTION_EDGESTYLE_NONE;

    if(BlinkAttr->u8CSOptionEdgeColor == CAPTION_EDGECOLOR_DEFAULT)
        BlinkAttr->u8CSOptionEdgeColor  = CAPTION_EDGECOLOR_BLACK;
    #else
        UNUSED(BlinkAttr);
    #endif
}

static U8 MApp_ClosedCaption_TransferColor(U8 u8Color , U8 type)
{
    printf("u8Color = %d, type = %d\n", u8Color,type);
    if(type)
    {
        switch(u8Color)
        {
            default:
            case CAPTION_FG_WHITE:
                return CAPTION_INNER_MIN8COLOR_WHITE;
            case CAPTION_FG_BLACK:
                return CAPTION_INNER_MIN8COLOR_BLACK;
            case CAPTION_FG_RED:
                return CAPTION_INNER_MIN8COLOR_RED;
            case CAPTION_FG_GREEN:
                return CAPTION_INNER_MIN8COLOR_GREEN;
            case CAPTION_FG_BLUE:
                return CAPTION_INNER_MIN8COLOR_BLUE;
            case CAPTION_FG_YELLOW:
                return CAPTION_INNER_MIN8COLOR_YELLOW;
            case CAPTION_FG_MAGENTA:
                return CAPTION_INNER_MIN8COLOR_MAGENTA;
            case CAPTION_FG_CYAN:
                return CAPTION_INNER_MIN8COLOR_CYAN;
        }
    }
    else
    {
        switch(u8Color)
        {
            default:
            case CAPTION_BG_BLACK:
                return CAPTION_INNER_MIN8COLOR_BLACK;
            case CAPTION_BG_WHITE:
                return CAPTION_INNER_MIN8COLOR_WHITE;
            case CAPTION_BG_RED:
                return CAPTION_INNER_MIN8COLOR_RED;
            case CAPTION_BG_GREEN:
                return CAPTION_INNER_MIN8COLOR_GREEN;
            case CAPTION_BG_BLUE:
                return CAPTION_INNER_MIN8COLOR_BLUE;
            case CAPTION_BG_YELLOW:
                return CAPTION_INNER_MIN8COLOR_YELLOW;
            case CAPTION_BG_MAGENTA:
                return CAPTION_INNER_MIN8COLOR_MAGENTA;
            case CAPTION_BG_CYAN:
                return CAPTION_INNER_MIN8COLOR_CYAN;
        }
    }
}

/******************************************************************************/
/// API for Draw CC Preview
/// @param BlinkAttr \b IN Blink FMT Info
/// @param stFont \b IN Font handle
/// @param pCCText \b IN Text String
/// @param CCTextLen \b IN Text Length
/// @param u16PosX \b IN x position
/// @param u16PosY \b IN y position
/******************************************************************************/
void MApp_ClosedCaption_Preview( stCaptionSettingOption_Type *BlinkAttr, CC_FONT * stFont, U8 *pCCText, U8 CCTextLen, U16 u16PosX, U16 u16PosY)
{
    BlinkBlock_Info BBlockInfo;
    BlinkChar_Info _CCTextBuf;
    U8 u8Loop;
    U8 FontIdx;
   #if !KOREAN_CC_ENABLE
    stCCFontBBOX stCCFontBbox;
   #endif

    UNUSED(u16PosX);
    UNUSED(u16PosY);
    /* Initialize Blink BitBlt Setting */
    //8Mx16  need modify   ___start____
    //msAPI_CC_SetGwinID(CC_USING_GOP_ID, CC_USING_GWIN_ID);//set the preview window's gop, for setting palette..

    CC_DecoderFuns.SetPalette(SYSINFO_MODE_708, FALSE);
    //msAPI_CC_SetGOPMode(CC_GOP_MODE_I8);

#if ( MEMORY_MAP != MMAP_16MB )
    BBlockInfo.BlockSrc0Address= DTVCC_BLOCK0_START_ADR;
    MDrv_GE_ClearFrameBuffer( DTVCC_BLOCK0_START_ADR, DTVCC_BLOCK0_START_LEN, 0);
    BBlockInfo.BlockSrc1Address= DTVCC_BLOCK1_START_ADR;
    MDrv_GE_ClearFrameBuffer( DTVCC_BLOCK1_START_ADR, DTVCC_BLOCK1_START_LEN, 0xff);
#endif

#ifndef SATURN2
    MApi_GOP_GWIN_SetTransClr(GOPTRANSCLR_FMT1, CC_COLOR_IDX_TRANSPARENT);
#else
  #ifndef S4LITE
    MDrv_GOP_GWIN_SetTransClr(GOPTRANSCLR_FMT0, 0);// + 128);
  #endif
#endif

#ifndef S4LITE
    MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT1,TRUE);
#endif

printf("\n...[%s, %d] u8CSOptionFGColor =%d, u8CSOptionBGColor =%d , u8CSOptionWindowColor = %d, u8CSOptionFGOpacity = %d, u8CSOptionBGOpacity = %d ,u8CSOptionWindowOpacity = %d ,u8CSFontSize = %d ,  u8CSFontStyle = %d , u8CSOptionEdgeStyle = %d ,  u8CSOptionEdgeColor = %d ...\n",
__FUNCTION__, __LINE__, BlinkAttr->u8CSOptionFGColor , BlinkAttr->u8CSOptionBGColor , BlinkAttr->u8CSOptionWindowColor , BlinkAttr->u8CSOptionFGOpacity , BlinkAttr->u8CSOptionBGOpacity , BlinkAttr->u8CSOptionWindowOpacity , BlinkAttr->u8CSFontSize , BlinkAttr->u8CSFontStyle ,BlinkAttr->u8CSOptionEdgeStyle , BlinkAttr->u8CSOptionEdgeColor);

/*
    if(BlinkAttr->u8CSFontStyle != CAPTION_FONTSTYLE_DEFAULT)           //young.yang@20120525 For mapping the Enum setting
        BlinkAttr->u8CSFontStyle--;

    if(BlinkAttr->u8CSOptionEdgeStyle != CAPTION_EDGESTYLE_DEFAULT)     //young.yang@20120525 For mapping the Enum setting
        BlinkAttr->u8CSOptionEdgeStyle--;
*/

    //Font2 & font4 should be set to proportional style.
    if((BlinkAttr->u8CSFontStyle == CAPTION_FONTSTYLE_2)
       ||(BlinkAttr->u8CSFontStyle == CAPTION_FONTSTYLE_4))
    {
        g_fCCAttrFlag.fCCAttr_Font_Indention_Flag = TRUE;
    }
    else
    {
        g_fCCAttrFlag.fCCAttr_Font_Indention_Flag = FALSE;
    }
    /* Get Font Width and Height */
    if(BlinkAttr->u8CSFontSize == CAPTION_FONTSIZE_SMALL)
    {
        FontIdx = BlinkAttr->u8CSFontStyle + CC_FONT_SET_NUM; // Small 8 - 15
    }
    else if(BlinkAttr->u8CSFontSize == CAPTION_FONTSIZE_LARGE)
    {
        FontIdx = BlinkAttr->u8CSFontStyle + CC_FONT_SET_NUM*2; // Large 16 - 23
    }
    else // Standard 0 - 7
    {
        FontIdx = BlinkAttr->u8CSFontStyle;
    }
#if KOREAN_CC_ENABLE
    _CCTextBuf.fHandle = stFont[(CC_FONTHANDLE)FontIdx + 3].fHandle;  //to korean cc font
#else
    _CCTextBuf.fHandle = stFont[(CC_FONTHANDLE)FontIdx].fHandle;
#endif
    CC_RenderFuns.GetCcFontInfo(_CCTextBuf.fHandle, CC_FONTINFO_WIDTH, &BBlockInfo.Char_Width);
    CC_RenderFuns.GetCcFontInfo(_CCTextBuf.fHandle, CC_FONTINFO_HEIGHT, &BBlockInfo.Char_Height);

    /* Draw BG Blink Block */
    BBlockInfo.TOPRSV_Lines = 0;
    BBlockInfo.BTMRSV_Lines = 0;
    BBlockInfo.BGFlashMode = 1;

    BBlockInfo.FGColorIndex = MApp_ClosedCaption_TransferColor(BlinkAttr->u8CSOptionBGColor, 0);
    if(g_fCCAttrFlag.fCCAttr_EnableWindowOptionSetting == TRUE)
        BBlockInfo.BGColorIndex = MApp_ClosedCaption_TransferColor(BlinkAttr->u8CSOptionWindowColor, 0);
    else
        BBlockInfo.BGColorIndex = CC_COLOR_IDX_TRANSPARENT;

//    BBlockInfo.V0_x = (CC_PREVIEW_GWIN_WIDTH - BBlockInfo.Char_Width * CCTextLen)/2;
//    BBlockInfo.V0_y = 0;
    BBlockInfo.V0_x = BBlockInfo.Char_Width;
    BBlockInfo.V0_y = 0;
    BBlockInfo.V1_x = BBlockInfo.V0_x + (BBlockInfo.Char_Width * CCTextLen) - 1;
    BBlockInfo.V1_y = BBlockInfo.Char_Height -1; //+2; // draw 2 more pixels
    BBlockInfo.fbId = NA_PREVIEW;

    /* Set control flag */
    CC_RenderFuns.SetCcInfo(NA_PREVIEW, CC_ATTRIBUTE_FLAG, (CC_U32)(&g_fCCAttrFlag));

    /* Draw Text */
    _CCTextBuf.FGColorIndex = MApp_ClosedCaption_TransferColor(BlinkAttr->u8CSOptionFGColor, 1);
    _CCTextBuf.BGColorIndex = MApp_ClosedCaption_TransferColor(BlinkAttr->u8CSOptionBGColor, 0);

    _CCTextBuf.EdgeType = BlinkAttr->u8CSOptionEdgeStyle;
    _CCTextBuf.EdgeColorIdx = MApp_ClosedCaption_TransferColor(BlinkAttr->u8CSOptionEdgeColor, 0);
    _CCTextBuf.Underline = FALSE;
    _CCTextBuf.CharSize = BBlockInfo.Char_Width;
    _CCTextBuf.Italic = FALSE;
    _CCTextBuf.HeadBlock = FALSE;
    _CCTextBuf.TailBlock = FALSE;

    /* Check Background Opacity */
    if (BlinkAttr->u8CSOptionBGOpacity == CAPTION_BG_FLASHING)
    {
        BBlockInfo.FG_Blink = TRUE;
        //_CCTextBuf.BG_Blink = TRUE;
    }
    else
    {
        BBlockInfo.FG_Blink = FALSE;
        //_CCTextBuf.BG_Blink = FALSE;

        if (BlinkAttr->u8CSOptionBGOpacity == CAPTION_BG_TRANSLUCENT)
        {
            BBlockInfo.FGColorIndex |= CC_COLOR_IDX_TRANSLUCENT;
            _CCTextBuf.BGColorIndex |= CC_COLOR_IDX_TRANSLUCENT;
        }
        else if (BlinkAttr->u8CSOptionBGOpacity == CAPTION_BG_TRANSPARENT)
        {
            BBlockInfo.FGColorIndex = CC_COLOR_IDX_TRANSPARENT;
            _CCTextBuf.BGColorIndex = CC_COLOR_IDX_TRANSPARENT;
        }
    }

    /* Check Foreground Opacity */
    if (BlinkAttr->u8CSOptionFGOpacity == CAPTION_BG_FLASHING)
        _CCTextBuf.FG_Blink = TRUE;
    else
    {
        _CCTextBuf.FG_Blink = FALSE;
        if (BlinkAttr->u8CSOptionFGOpacity == CAPTION_BG_TRANSLUCENT)
        {
            _CCTextBuf.FGColorIndex |= CC_COLOR_IDX_TRANSLUCENT;
            _CCTextBuf.EdgeColorIdx |= CC_COLOR_IDX_TRANSLUCENT;
        }
        else if (BlinkAttr->u8CSOptionFGOpacity == CAPTION_BG_TRANSPARENT)
        {
            _CCTextBuf.FGColorIndex = CC_COLOR_IDX_TRANSPARENT;
            _CCTextBuf.EdgeColorIdx = CC_COLOR_IDX_TRANSPARENT;
        }
    }

    /* Check Window Opacity */
    if (BlinkAttr->u8CSOptionWindowOpacity == CAPTION_WINDOW_FLASHING)
        BBlockInfo.BG_Blink = TRUE;
    else
    {
        BBlockInfo.BG_Blink = FALSE;
        if(BlinkAttr->u8CSOptionWindowOpacity == CAPTION_WINDOW_TRANSLUCENT)
            BBlockInfo.BGColorIndex |= CC_COLOR_IDX_TRANSLUCENT;
        else if (BlinkAttr->u8CSOptionWindowOpacity == CAPTION_WINDOW_TRANSPARENT)
            BBlockInfo.BGColorIndex = CC_COLOR_IDX_TRANSPARENT;
    }

    printf("SetPreviewPalette! _CCTextBuf.FG_Blink = %d, BBlockInfo.BG_Blink = %d\n", _CCTextBuf.FG_Blink, BBlockInfo.BG_Blink);
    CC_RenderFuns.SetPreviewPalette(_CCTextBuf.FG_Blink, BBlockInfo.FG_Blink, BBlockInfo.BG_Blink, &BBlockInfo, &_CCTextBuf);

    for (u8Loop =0; u8Loop < CCTextLen; u8Loop++)
    {
    #if KOREAN_CC_ENABLE
        _CCTextBuf.TextCode = ((pCCText[u8Loop*2] << 8) |pCCText[u8Loop*2 + 1]);
        if(!(_CCTextBuf.TextCode & 0xFF00)) //english font
        {
            _CCTextBuf.fHandle = stFont[(CC_FONTHANDLE)FontIdx].fHandle;
        }

        CC_RenderFuns.DrawText(&BBlockInfo, &_CCTextBuf, 1, FALSE, NULL, NULL);
        BBlockInfo.V0_x += BBlockInfo.Char_Width;

    #else
        _CCTextBuf.TextCode =(U16) pCCText[u8Loop];
        if(g_fCCAttrFlag.fCCAttr_Font_Indention_Flag == TRUE)
        {
            CC_RenderFuns.GetFontBBoxinfo(_CCTextBuf.fHandle, _CCTextBuf.TextCode,_CCTextBuf.Italic, &stCCFontBbox);
            CC_RenderFuns.DrawText(&BBlockInfo, &_CCTextBuf, 1, TRUE, NULL, NULL);
            BBlockInfo.V0_x += stCCFontBbox.u8DisplayWidth;
        }
        else
        {
            CC_RenderFuns.DrawText(&BBlockInfo, &_CCTextBuf, 1, FALSE, NULL, NULL);
            BBlockInfo.V0_x += BBlockInfo.Char_Width;
        }
    #endif
    }
}

#if CUSTOMER_FOR_UI_CC_708_608_APPEARING
void MApp_ClosedCaption_Parser_Init(void)
{
    if ( (IsDTVInUse()==TRUE))
    {
        printf("\nINFO-DCC-INIT");

        msAPI_CC_DrvInit(MSAPI_CC_TYPE_NTSC_TWOFIELD);

        msAPI_CC_DrvInit(MSAPI_CC_TYPE_DTVCC);
    }
}

void MApp_ClosedCaption_Parser_Stop(void)

{

    //printf("\nINFO-STOP");

    if (IsDTVInUse()==TRUE)

    {

        msAPI_CC_StopMVDParser();

    }

    msAPI_CC_Reset();

}
#endif


/******************************************************************************/

#undef MAPP_CLOSED_CAPTION_C

#endif //#if(ENABLE_ATSC)
