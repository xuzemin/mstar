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
#ifndef _MSB1501_H_
#define _MSB1501_H_

/* ------------------------------------
    Header Files
   ------------------------------------ */

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"
/* ------------------------------------
    Macro Definitions
   ------------------------------------ */

#ifdef _MSB1501_C_
#define INTERFACE
#else
#define INTERFACE  extern
#endif

typedef enum
{
    DEMOD_INIT,
    DEMOD_CKING,
    DEMOD_END,
} EN_DEMOD_RESULT;

typedef enum
{
    MSB1501_SIGNAL_NO                   = 0,    /* little or no input power detected    */
    MSB1501_SIGNAL_WEAK                 = 1,    /* some power detected.                    */
    MSB1501_SIGNAL_MODERATE             = 2,
    MSB1501_SIGNAL_STRONG               = 4,
    MSB1501_SIGNAL_VERY_STRONG         = 8
}MSB1501SignalCondition_t;

#define VSB_1501 0x04
#define QAM256_1501  0x02
#define VSB 1
#define QAM64 2
#define QAM256 4
#define VSB_SIGNAL_DISTANCE 5
#define QAM_SIGNAL_DISTANCE 5

INTERFACE void MSB1501_StatusINIT(void);
INTERFACE BOOLEAN MSB1501_Init(void);
INTERFACE BOOLEAN MSB1501_Download(U8* MSB1501_Download_Address, U16 MSB1501_Download_Size, U8* MSB1501_Download_Table);
INTERFACE BOOLEAN MSB1501_ReadReg(U16 u16Addr, U8* u8Data);
INTERFACE BOOLEAN MSB1501_WriteReg(U16 u16Addr, U8 u8Data);
INTERFACE BOOLEAN MSB1501_RepeaterEnable(void);
INTERFACE BOOLEAN MSB1501_RepeaterDisable(void);
INTERFACE BOOLEAN MSB1501_SoftReset(void);
INTERFACE BOOLEAN MSB1501_VsbMode(void);
INTERFACE BOOLEAN MSB1501_64QamMode(void);
INTERFACE BOOLEAN MSB1501_256QamMode(void);
INTERFACE BOOLEAN MSB1501_Vsb_PreLock(void);
INTERFACE BOOLEAN MSB1501_Vsb_QAM_AGCLock(void);
INTERFACE BOOLEAN MSB1501_QAM_PreLock(void);
INTERFACE BOOLEAN MSB1501_QAM_Main_Lock(void);
INTERFACE BOOLEAN MSB1501_Vsb_CE_Lock(void);
INTERFACE BOOLEAN MSB1501_Vsb_FEC_Lock(void);
INTERFACE void MSB1501_CheckSignalCondition(MSB1501SignalCondition_t* pstatus);
INTERFACE EN_SCAN_RESULT MSB1501_QAMCheckLock(void);
INTERFACE U8  MSB1501_Check8VSB64_256QAM(void);
INTERFACE U8 MSB1501_ReadSNRPercentage(void);
INTERFACE S16 MSB1501_ReadFrequencyOffset(void);
INTERFACE void MSB1501_FWVERSION(void);
INTERFACE EN_SCAN_RESULT MSB1501_VSBCheckLock(void);

#undef INTERFACE

#endif

