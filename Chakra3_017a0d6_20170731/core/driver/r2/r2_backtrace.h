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

#ifndef _R2_BACKTRACE_H_
#define _R2_BACKTRACE_H_

#ifdef __aeon__


#define REG_R0              (0)         // Fixed to zero
#define REG_R1              (1)
#define REG_R2              (2)
#define REG_R3              (3)
#define REG_R4              (4)
#define REG_R5              (5)
#define REG_R6              (6)
#define REG_R7              (7)
#define REG_R8              (8)
#define REG_R9              (9)
#define REG_R10             (10)
#define REG_R11             (11)
#define REG_R12             (12)
#define REG_R13             (13)
#define REG_R14             (14)
#define REG_R15             (15)
#define REG_R16             (16)
#define REG_R17             (17)
#define REG_R18             (18)
#define REG_R19             (19)
#define REG_R20             (20)
#define REG_R21             (21)
#define REG_R22             (22)
#define REG_R23             (23)
#define REG_R24             (24)
#define REG_R25             (25)
#define REG_R26             (26)
#define REG_R27             (27)
#define REG_R28             (28)
#define REG_R29             (29)
#define REG_R30             (30)
#define REG_R31             (31)

#ifdef __AEONR2__
#define OP_R2_BT_ADDI_PFX 0x27
#define OP_R2_BN_ADDI_PFX 0x07
#define OP_R2_BG_ADDI_PFX 0x3F
#define OP_R2_BN_SW_PFX   0x03
#define OP_R2_BG_SW_PFX   0x3B
#define OP_R2_ENTRI_PFX   0x17
#define OP_R2_ENTRI_SUB   0x18
#define OP_R2_STACK_PFX   0x20
#elif defined __AEON1__
#define OP_AEON_ADDI_PFX  0x27
#define OP_AEON_SW_PFX    0x35
#endif

#define NULL 0
#define R2_BT_MAGIC_NUMBER      0xa55aadda

typedef enum bt_symbol_type
{
        SYM_OFF = 0x00,
        SYM_STR_ON = 0x01,
        SYM_SIZE_ON = 0x02,
        SYM_STR_SIZE_ON =0x03,
}e_symbol_type;

void r2_bt_init(void);
int r2_online_bt(void);
int r2_online_except_bt(int stack, int pc, int lr);

#endif

#endif

