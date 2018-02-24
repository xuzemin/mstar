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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPP_ZUI_MAIN_H
#define _MAPP_ZUI_MAIN_H

#include "datatype.h"
#include "Board.h"
#include "debug.h"


#ifdef MAPP_ZUI_APIWINDOW_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef enum
{
    E_ZUI_STATE_UNKNOW=0,
    E_ZUI_STATE_STANDBY=1,
    E_ZUI_STATE_RUNNING=2,
    E_ZUI_STATE_TRANSEFF_DOING=3,
    E_ZUI_STATE_TRANSEFF_END=4,
    E_ZUI_STATE_TERMINATE=5,
    E_ZUI_STATE_MAX=6
}ZUI_STATE;

typedef enum
{
    RET_ZUI_RUNNING,
    RET_ZUI_EXIT,
}ZUI_RET;

//////////////////////////////////////////////////////////////////
//  Configuration
//
#define ZUI_DBG_ERR 0 // 0//1
#define ZUI_DBG_RECURSIVE 0


#define CPU_BEON    0x0000
#define CPU_8051    0x0001
#define CPU_AEON    0x0002

// CPU type
#define CPU_TYPE    CPU_AEON//CPU_8051

#if (CPU_TYPE == CPU_8051)
    #define _ZUI_TBLSEG     code
    #define _MP_TBLSEG      code
#else
    #define _ZUI_TBLSEG
    #define _MP_TBLSEG
#endif // (CPU_TYPE == CPU_8051)

#if ZUI_DBG_ERR
    #define ABORT()         { printf("[ZUI ABORT] file=%s line=%d \n",__FILE__,__LINE__); }
    #define ZUI_DBG_FAIL(x) MS_DEBUG_MSG(x)
#else // ZUI_DBG_ERR
    #define ABORT()
    #define ZUI_DBG_FAIL(x) //x
#endif  // ZUI_DBG_ERR
    #define ZUI_MSG(x)      x //gchen @ 20171220 //open debug


#ifndef ENABLE_MAINPAGE_EFFECT
    #define ENABLE_MAINPAGE_EFFECT      ENABLE
#endif

#ifndef UNUSED //to avoid compile warnings...
    #define UNUSED(var) (void)((var) = (var))
#endif

#define _ZUI_MALLOC(x)      msAPI_Memory_Allocate((x),    BUF_ID_ZUI)
#define _ZUI_FREE(x)        MSAPI_MEMORY_FREE((x),BUF_ID_ZUI)

#define ZUI_ENABLE_ALPHATABLE               1
#define ZUI_ENABLE_REDUCED_ALPHATABLE       1

////////////////////////////////////////////////////////////////


INTERFACE void MApp_ZUI_ProcessKey(U8 u8IRKey);
INTERFACE ZUI_RET MApp_ZUI_MainTask(void);
INTERFACE BOOLEAN MApp_ZUI_CheckNeedDrawing(void);
INTERFACE BOOLEAN MApp_ZUI_Init(void);
INTERFACE ZUI_STATE MApp_ZUI_GetState(void);
INTERFACE U32 MApp_ZUI_GetActiveOSD(void);

INTERFACE U32 MApp_ZUI_GetActive_ChannelInfo_OSD(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_Startup_ChannelInfo_OSD(void);



//ZUI:
#if 1
#define MApp_ZUI_ACT_StartupOSD(x) do {                            \
    MApp_ZUI_ACT_StartupOSD2(x);                                  \
} while(0)
#else
#define MApp_ZUI_ACT_StartupOSD(x) do {                            \
    printf("%u  %s \n", __LINE__, __FILE__);                       \
    MApp_ZUI_ACT_StartupOSD2(x);                                  \
} while(0)
#endif

INTERFACE BOOLEAN MApp_ZUI_ACT_StartupOSD2(U32 id);
//ZUI:
#if 1
#define MApp_ZUI_ACT_ShutdownOSD() do {                            \
    MApp_ZUI_ACT_ShutdownOSD2();                                  \
} while(0)
#else
#define MApp_ZUI_ACT_ShutdownOSD() do {                            \
    printf("%u  %s \n", __LINE__, __FILE__);                       \
    MApp_ZUI_ACT_ShutdownOSD2();                                  \
} while(0)
#endif

INTERFACE void MApp_ZUI_ACT_ShutdownOSD2(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteWndAction(U16 act);

#undef INTERFACE

#endif  // _APP_ZUI_H

