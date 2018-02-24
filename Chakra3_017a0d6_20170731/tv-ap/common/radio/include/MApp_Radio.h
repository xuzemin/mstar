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

#ifndef _MApp_FMRadio_H_
#define _MApp_FMRadio_H_

#ifdef MApp_FMRadio_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#include "Board.h"

#if(ENABLE_FM_RADIO)

//------------------------------------------------------------------------------

extern U8 g_Radio_u8CurChIdx;
extern StuRadioChData g_Radio_stCurChData;

extern U16 g_CurFMFreq;
extern U8 g_FMCurChName[RADIO_CH_NAME_LEN];


//------------------------------------------------------------------------------

void MApp_FMRadio_DB_Get_ChDefaultValue(U8 u8ChIdx, StuRadioChData* pstChData);
INTERFACE void MApp_FMRadio_DB_RestoreToDefault(void);

INTERFACE U8 MApp_FMRadio_Get_CurChIdx(void);
void MApp_FMRadio_Set_CurChIdx(U8 u8ChIdx);

INTERFACE void MApp_FMRadio_Get_ChName(U8 u8ChIdx, U8* pu8ChName);

//INTERFACE void MApp_FMRadio_ChangeCh(U8 u8ChIdx);

//void MApp_FMRadio_Task(void);


INTERFACE void MApp_FMRadio_SetFMFreq(U16 u16Freq_x10K);
INTERFACE BOOLEAN MApp_FMRadio_SaveCh(U8 u8ChIdx, StuRadioChData* pstChData);
INTERFACE BOOLEAN MApp_FMRadio_LoadCh(U8 u8ChIdx, StuRadioChData* pstChData);
INTERFACE void MApp_FMRadio_ChgCurCh(U8 u8ChIdx);
INTERFACE U8 MApp_FMRadio_GetCurChNum(void);
INTERFACE U16 MApp_FMRadio_Get_ChFreq(U8 u8ChIdx);
INTERFACE U16 MApp_FMRadio_GetCurChFreq(void);
INTERFACE void MApp_FMRadio_SetTestCh(void);
INTERFACE void MApp_FMRadio_Var_Init(void);
INTERFACE void MApp_FMRadio_Init(void);


//------------------------------------------------------------------------------

#endif // ENABLE_FM_RADIO

#endif //#ifndef _MApp_FMRadio_H_
