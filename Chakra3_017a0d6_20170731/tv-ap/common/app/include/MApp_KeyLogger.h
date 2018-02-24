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
#ifndef MAPP_KEYLOGGER_H
#define MAPP_KEYLOGGER_H

#if ENABLE_KEY_LOGGER
//#include "MsCommon.h"
#include "datatype.h"
#include "MApp_GlobalSettingSt.h"

#ifdef MAPP_KEYLOGGER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef struct
{
    U32 u32EventTime;
    U8 u8CrcResult;
    U8 u8EventKeyCode;
    U8 u8EventKeyType:1;
    U8 u8EventKeyRepeat:1;
}ST_KEYLOGGER_EVENT;

typedef enum
{
    EN_KEYLOGGER_MODE_OFF,

    EN_KEYLOGGER_MODE_LOGGING_KEY,
    EN_KEYLOGGER_MODE_LOGGING_KEY_PLUS_DB,
    EN_KEYLOGGER_MODE_LOGGING_KEY_PLUS_PARTIAL_FLASH,

    EN_KEYLOGGER_MODE_SIMULATING_KEY,
    EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_DB,
    EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_PARTIAL_FLASH,

    EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_DB_ALWAYS_RECOVER,
    EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_PARTIAL_FLASH_ALWAYS_RECOVER,

    EN_KEYLOGGER_MODE_MAX = EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_PARTIAL_FLASH_ALWAYS_RECOVER,
}EN_KEYLOGGER_MODE;

typedef enum
{
    EN_KEYLOGGER_PACK_MODE_KEY_EVENT,
    EN_KEYLOGGER_PACK_MODE_DATABASE,
    EN_KEYLOGGER_PACK_MODE_PARTIAL_FLASH,
}
EN_KEYLOGGER_PACK_MODE;

#define _KEYLOGGER_CAPTURE_BY_SPECIAL_IR_KEY_     1

void MApp_KeyLogger_DataReset(void);
BOOL MApp_KeyLogger_Init(void);
void MApp_KeyLogger_Action_DumpAll(void);
void MApp_KeyLogger_SetMode(EN_KEYLOGGER_MODE eMode);
EN_KEYLOGGER_MODE MApp_KeyLogger_GetMode(void);
#if (_KEYLOGGER_CAPTURE_BY_SPECIAL_IR_KEY_)
void MApp_KeyLogger_ComboKeyChecker(U8 u8InputKey);
#endif
BOOL MApp_KeyLogger_ModifyConfigBin(EN_KEYLOGGER_MODE eMode);


BOOL MApp_KeyLogger_Action_Save(U8 u8KeyType, U8 u8KeyCode, BOOL bKeyRepeat);
BOOL MApp_KeyLogger_Encapsulate(EN_KEYLOGGER_PACK_MODE ePackMode);

BOOL MApp_KeyLogger_Action_Task(void);
U8 MApp_KeyLogger_GetSimulatedKey(U8* pU8KeyCode, U8* pU8KeyType, BOOL* pBRepeatKey);
BOOL MApp_KeyLogger_TerminateSimulation(void);


#undef INTERFACE
#endif
#endif  //MAPP_KEYLOGGER_H

