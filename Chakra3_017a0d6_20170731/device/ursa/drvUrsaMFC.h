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
// Copyright (c) 2008 MStar Semiconductor, Inc.
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
// File Name: drvUrsaMFC.h
// Description: Comunication to URSA module
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_URSA_H__
#define __DRV_URSA_H__

#include "datatype.h"
#include "drvGlobal.h"

 #define MST6M10_RESET_MODE    1   // 0/1/2/3=NONE/HAND_SHAKE/WDT_RESET/HW_RESET

#define NEW_URSA_SERIAL_DEBUG_MODE 0// 1

// ***************************************************************************
// ************************* START OF REGISTER TYPES *************************
// ***************************************************************************
#define MST6M10_SW_VERSION 0x11
#define MFCLevel_HIGH     0x03
#define MFCLevel_MIDDLE 0x02
#define MFCLevel_LOW      0x01

//----------------------------------------------------------------------------
// Control register bit field structure definitions
//----------------------------------------------------------------------------
#define reg_2905MFC     0x2905
#define reg_2907MFC     0x2907
#define reg_290EMFC     0x290E
#define reg_2940MFC     0x2940
#define reg_2F0CMFC     0x2F0C
#define reg_2F10MFC     0x2F10
#define reg_2F2BMFC     0x2F2B
#define reg_3050MFC     0x3050
#define reg_207CMFC     0x207C//for6M20 sw version
#define reg_207DMFC     0x207D
#define reg_2420MFC        0x2420
#define reg_2436MFC        0x2436
#define reg_2613MFC        0x2613
#define reg_3250MFC      0x3250
#define reg_MFCLevel        0x2C22
#define reg_OSDX0        0x2422
#define reg_OSDX1        0x2423
#define reg_OSDY0          0x2424
#define reg_OSDY1        0x2425
#define reg_2A18MFC 0x2A18
#define reg_3015MFC   0x3015
#define reg_3016MFC   0x3016
#define reg_3017MFC   0x3017
#define reg_300BMFC   0X300B

//-------------------------------------------------------------------------
// Register maps enum
//-------------------------------------------------------------------------

typedef struct {

    U16             uwAddr;
    BOOLEAN         bHigh;
    U8              ucData;
} URSA_REGMAP, *URSA_PREGMAP;

#define BOOL        BOOLEAN

#endif // __DRV_URSA_H__
