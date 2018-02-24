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
#ifndef MSAPI_SCAN_ATSC_H
#define MSAPI_SCAN_ATSC_H

#include "MApp_GlobalSettingSt_ATSC.h"

//==============================================================================
/*                     Macro                                                    */
//==============================================================================
#ifdef INTERFACE
#undef INTERFACE
#endif

#ifdef MSAPI_SCAN_ATAC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef enum
{
    STATE_NTSC_SCAN_INIT,
    STATE_NTSC_JUMP,
    STATE_NTSC_CHECK_LOCK,
} EN_NTSC_SCAN_STATE;

typedef enum
{
    STATE_VSB_SCAN_INIT,
    STATE_VSB_INIT_DEMODE,
    STATE_VSB_CHECK_LOCK,
    STATE_VSB_CHECK_FSYNC_LOCK,//Demod VSB  check lock first stage...in Fast lock mode only check first stage lock
    STATE_VSB_CHECK_FEC_LOCK //Demod VSB  check lock second stage
} EN_VSB_SCAN_STATE;

typedef enum
{
    STATE_QAM_SCAN_INIT,
    STATE_QAM_INIT_DEMODE,
    STATE_QAM_CHECK_LOCK,
    STATE_QAM_CHECK_PRE_LOCK, //Demod Qam  check lock first stage...in Fast lock mode only check first stage lock
    STATE_QAM_CHECK_MAIN_LOCK,   //Demod Qam  check lock second stage
} EN_QAM_SCAN_STATE;

typedef enum
{
    SCAN_ANT_CATV,
    SCAN_ANT_AIR,
    SCAN_ANT_TYPE_NUM
} EN_SCAN_ANT_TYPE;

INTERFACE BOOLEAN bInitDemod;

INTERFACE void msAPI_SCAN_Init(void);
INTERFACE EN_SCAN_RESULT msAPI_NTSC_Scan(MS_TP_SETTING_ATSC *pstTPSetting, U8 CurRFCh, EN_SCAN_ANT_TYPE CurChType);
INTERFACE EN_SCAN_RESULT msAPI_VSB_Scan( MS_TP_SETTING_ATSC *pstTPSetting );
INTERFACE EN_SCAN_RESULT msAPI_QAM_Scan(MS_TP_SETTING_ATSC *pstTPSetting);
INTERFACE S16 msAPI_ScanGetFreqByZigZagPoint(EN_DEMOD_ATSC_MODE Modulation, U8 ZigZagPt, U8 CurRF);
INTERFACE BOOL msAPI_InNTSC_FreqOffset_Range(S16 freq_offset, U8 CurRF);
INTERFACE void msAPI_IFDM_SetVIF_Notch(void);

#undef INTERFACE

#endif /* MSAPI_SCAN_ATSC_H */

