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

#ifndef MAPP_IR_H
#define MAPP_IR_H

#ifdef  MAPP_IR_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

//======================================================================
#define ENABLE_MBIR     0

//======================================================================
#if(ENABLE_MBIR)
typedef struct
{
    BOOLEAN empty;
    U16     keydata;
    U8      repeat;
    U8      flag;

} ST_MBIR;
#endif

INTERFACE void MApp_ProcessUserInput(void);
INTERFACE void MApp_Key_Initial_Status(void);
INTERFACE BOOLEAN MApp_GetCurrentKeyType(void);
INTERFACE BOOLEAN MApp_KeyIsReapeatStatus(void);

#if(ENABLE_MBIR)
INTERFACE void MApp_FillMBIR(U8 keycode, U8 repeat);
INTERFACE void MApp_ClearMBIR(void);
INTERFACE void MApp_SetMBIRFlag(U8 val);
INTERFACE U8 MApp_GetMBIRFlag(void);
INTERFACE void MApp_GetMBIR(ST_MBIR* pMBIR);
#endif

#if ENABLE_IR_BIN
#define IRBIN_BIN_END       0x00

#define IRBIN_HEADER_CODE0  0x01
#define IRBIN_HEADER_CODE1  0x02

#define IRBIN_KEYMAP_CODE   0x10

#define IRBIN_NUM   256

INTERFACE U16 g_u16IRkeyMap[IRBIN_NUM];

INTERFACE void MApp_IrBin_Init(void);
INTERFACE U8 MApp_IrBin_GetKeyCode(U8 u8Key);

#endif

#define KEY_TYPE_KEYPAD         0
#define KEY_TYPE_IR             1

typedef struct
{
    U8 keydown:1;
    U8 keyrepeat:1;
    U8 RepeatEnable:1;      // Repeat key is enable or not for a specific key.
    U8 keytype:1;           //0:  Key Pad  1: IR Key
    U8 KeyFilterPower:1;
    U8 Reserved:3;
    U8 keydata  ;
} KEYSTAT;

#undef INTERFACE

#endif

