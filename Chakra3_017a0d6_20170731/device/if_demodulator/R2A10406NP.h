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
/***********************************************************************************
*    File:                R2A10406NP.h
*
*    Project:              TV/AV
*
*    Description:
*
*    Date:                 started from 2006.02.16
*
***********************************************************************************/
#if !defined(__R2A10406NP_H__)
#define __R2A10406NP_H__


//****************************************************************************
// Public attributes.
//****************************************************************************
#define _IF_DEM_I2C_ID            0x84

//****************************************************************************
// Private attributes of this file.
//****************************************************************************

#define _IF_DEM_SUB_ADDRESS        0x00

//--------------------------------------------------
// Bescription of status register bits
//--------------------------------------------------
// AFC window
#define _MASK_OF_AFCWIN                    0xE0
#define _AFCWIN_IN_WINDOW                0x80
#define _AFCWIN_OUT_OF_WINDOW            0x00

// Automatic frequency contrl
#define _MASK_OF_AFC                    0xE0

//--------------------------------------------------
// Bit description for switching mode
//--------------------------------------------------

static IF_FREQ m_eIF_Freq;

typedef enum
{
    E_AFC_BELOW_MINUS_187p5KHz        = 0x07,
    E_AFC_MINUS_162p5KHz            = 0x06,
    E_AFC_MINUS_137p5KHz            = 0x05,
    E_AFC_MINUS_112p5KHz            = 0x04,
    E_AFC_MINUS_87p5KHz                = 0x03,
    E_AFC_MINUS_62p5KHz                = 0x02,
    E_AFC_MINUS_37p5KHz                = 0x01,
    E_AFC_MINUS_12p5KHz                = 0x00,
    E_AFC_PLUS_12p5KHz                = 0x0F,
    E_AFC_PLUS_37p5KHz                = 0x0E,
    E_AFC_PLUS_62p5KHz                = 0x0D,
    E_AFC_PLUS_87p5KHz                = 0x0C,
    E_AFC_PLUS_112p5KHz                = 0x0B,
    E_AFC_PLUS_137p5KHz                = 0x0A,
    E_AFC_PLUS_162p5KHz                = 0x09,
    E_AFC_ABOVE_PLUS_187p5KHz        = 0x08
    E_AFC_OUT_OF_AFCWIN             = 0x10,
} AFC;


//****************************************************************************
// Public functions.
//****************************************************************************

void MDrv_IFDM_Init(void);
AFC MDrv_IFDM_GetFreqDev(void);
BOOLEAN MDrv_IFDM_IsAFCInWindow(void);
void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq);
void MDrv_IFDM_CVBSOff(void);
INTERFACE IF_FREQ MDrv_IFDM_GetIF(void);
#endif
