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
/**
Copyright (C) 2010 NXP B.V., All Rights Reserved.
This source code and any compilation or derivative thereof is the proprietary
information of NXP B.V. and is confidential in nature. Under no circumstances
is this software to be  exposed to or placed under an Open Source License of
any type without the expressed written permission of NXP B.V.
*
* \file          tmddTDA18273.h
*                %version: 1 %
*
* \date          %date_modified%
*
* \brief         Describe briefly the purpose of this file.
*
* REFERENCE DOCUMENTS :
*
* Detailed description may be added here.
*
* \section info Change Information
*
* \verbatim
Date          Modified by CRPRNr  TASKNr  Maintenance description
-------------|-----------|-------|-------|-----------------------------------
|            |           |       |
-------------|-----------|-------|-------|-----------------------------------
|            |           |       |
-------------|-----------|-------|-------|-----------------------------------
\endverbatim
*
*/
#ifndef _TMDD_TDA18273_H //-----------------
#define _TMDD_TDA18273_H

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
//

#ifdef __cplusplus
extern "C"
{
#endif

//-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
//

/* SW Error codes */
#define ddTDA18273_ERR_BASE               (CID_COMP_TUNER | CID_LAYER_BSL)
#define ddTDA18273_ERR_COMP               (CID_COMP_TUNER | CID_LAYER_BSL | TM_ERR_COMP_UNIQUE_START)

#define ddTDA18273_ERR_BAD_UNIT_NUMBER    (ddTDA18273_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define ddTDA18273_ERR_NOT_INITIALIZED    (ddTDA18273_ERR_BASE + TM_ERR_NOT_INITIALIZED)
#define ddTDA18273_ERR_INIT_FAILED        (ddTDA18273_ERR_BASE + TM_ERR_INIT_FAILED)
#define ddTDA18273_ERR_BAD_PARAMETER      (ddTDA18273_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define ddTDA18273_ERR_NOT_SUPPORTED      (ddTDA18273_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define ddTDA18273_ERR_HW_FAILED          (ddTDA18273_ERR_COMP + 0x0001)
#define ddTDA18273_ERR_NOT_READY          (ddTDA18273_ERR_COMP + 0x0002)
#define ddTDA18273_ERR_BAD_VERSION        (ddTDA18273_ERR_COMP + 0x0003)

#define TDA18273_MAX_UNITS  2 // 1 change unit count 1 to 2 by yooheeyong 20110823
#define TDA18273_I2C_MAP_NB_BYTES 69

typedef enum _tmddTDA18273PowerState_t {
    tmddTDA18273_PowerNormalMode,                                               /* Device normal mode */
    tmddTDA18273_PowerStandbyWithXtalOn,                                        /* Device standby mode with Xtal Output */
    tmddTDA18273_PowerStandby,                                                  /* Device standby mode */
    tmddTDA18273_PowerMax
} tmddTDA18273PowerState_t, *ptmddTDA18273PowerState_t;

tmErrorCode_t
tmddTDA18273Init
(
    tmUnitSelect_t    tUnit,    //  I: Unit number
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
);
tmErrorCode_t 
tmddTDA18273DeInit
(
    tmUnitSelect_t    tUnit     //  I: Unit number
);
tmErrorCode_t
tmddTDA18273Write
(
    tmUnitSelect_t      tUnit,      //  I: Unit number
    UInt32              uIndex,         //  I: Start index to write
    UInt32              uNbBytes,       //  I: Number of bytes to write
    UInt8*             puBytes         //  I: Pointer on an array of bytes
);
tmErrorCode_t
tmddTDA18273Read
(
    tmUnitSelect_t      tUnit,      //  I: Unit number
    UInt32              uIndex,         //  I: Start index to read
    UInt32              uNbBytes,       //  I: Number of bytes to read
    UInt8*             puBytes         //  I: Pointer on an array of bytes
);
tmErrorCode_t
tmddTDA18273GetPOR
(
    tmUnitSelect_t    tUnit,    //  I: Unit number
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetAGCs_Lock
(
    tmUnitSelect_t    tUnit,    //  I: Unit number
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetVsync_Lock
(
    tmUnitSelect_t    tUnit,    //  I: Unit number
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetLO_Lock
(
    tmUnitSelect_t    tUnit,    //  I: Unit number
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetIdentity
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt16*        puValue      //  I: Address of the variable to output item value
);
tmErrorCode_t
tmddTDA18273GetMinorRevision
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetMajorRevision
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetTM_D
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetTM_ON
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetTM_ON
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetPowerState
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
tmddTDA18273PowerState_t  powerState    //  I: Power state of this device
);
tmErrorCode_t
tmddTDA18273GetPowerState
(
tmUnitSelect_t        tUnit,    //  I: Unit number
ptmddTDA18273PowerState_t    pPowerState  //  O: Power state of this device
);

tmErrorCode_t
tmddTDA18273GetPower_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIRQ_Clear
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8           irqStatus   /* I: IRQs to clear */
);
tmErrorCode_t
tmddTDA18273SetAGC1_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC1_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGC1_Top_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC1_Top_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGC1_Top_Mode_Val
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC1_Top_Mode_Val
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetPulse_Shaper_Disable
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetPulse_Shaper_Disable
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);

tmErrorCode_t
tmddTDA18273SetPD_AGC_Adapt3x
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  //  I: Item value
);
tmErrorCode_t
tmddTDA18273GetPD_AGC_Adapt3x
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetRFAGC_Adapt_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  //  I: Item value
);
tmErrorCode_t
tmddTDA18273GetRFAGC_Adapt_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetRF_Atten_3dB
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  //  I: Item value
);
tmErrorCode_t
tmddTDA18273GetRF_Atten_3dB
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetRFAGC_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetRFAGC_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetVHF_III_mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetVHF_III_mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetW_Filter_Enable
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetW_Filter_Enable
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetW_Filter_Offset
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetW_Filter_Offset
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetS2D_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetS2D_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIR_Mixer_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetIR_Mixer_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGCs_Do_Step_assym
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
UInt8           uValue  //  I: Item value
);
tmErrorCode_t
tmddTDA18273GetAGCs_Do_Step_assym
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGC5_Ana
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC5_Ana
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGC5_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC5_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIF_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetIF_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIF_HP_Fc
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetIF_HP_Fc
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIF_ATSC_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetIF_ATSC_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetLP_FC_Offset
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetLP_FC_Offset
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetLP_FC
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetLP_FC
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uValue      //  I: Item value
);
tmErrorCode_t
tmddTDA18273GetIF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*        puValue      //  I: Address of the variable to output item value
);
tmErrorCode_t
tmddTDA18273SetRF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uValue      //  I: Item value
);
tmErrorCode_t
tmddTDA18273GetRF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*        puValue      //  I: Address of the variable to output item value
);
tmErrorCode_t
tmddTDA18273SetRSSI_Meas
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetRSSI_Meas
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetRF_CAL_AV
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetRF_CAL_AV
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetRF_CAL
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetRF_CAL
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIR_CAL_Loop
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetIR_CAL_Loop
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIR_Cal_Image
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetIR_Cal_Image
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIR_CAL_Wanted
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetIR_CAL_Wanted
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetRC_Cal
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetRC_Cal
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetCalc_PLL
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetCalc_PLL
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetXtalCal_Launch
(
    tmUnitSelect_t      tUnit    //  I: Unit number
);
tmErrorCode_t
tmddTDA18273GetXtalCal_Launch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetTriggerMSM
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273SetMSM_Launch
(
    tmUnitSelect_t      tUnit    //  I: Unit number
);
tmErrorCode_t
tmddTDA18273GetMSM_Launch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGC1_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC1_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGC5_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC5_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetAGC1_Gain_Read
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetAGC2_Gain_Read
(
tmUnitSelect_t      tUnit,    //  I: Unit number
UInt8*        puValue      //  I: Address of the variable to output item value
);
tmErrorCode_t
tmddTDA18273GetAGC5_Gain_Read
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273GetAGC4_Gain_Read
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetIRQ_Polarity
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetIRQ_Polarity
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGC1_Do_step
(
	tmUnitSelect_t  tUnit,  /*  I: Unit number */
	UInt8           uValue  /*  I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC1_Do_step
(
	tmUnitSelect_t  tUnit,  /*  I: Unit number */
	UInt8*          puValue /*  I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetAGC2_Do_step
(
	tmUnitSelect_t  tUnit,  /*  I: Unit number */
	UInt8           uValue  /*  I: Item value */
);
tmErrorCode_t
tmddTDA18273GetAGC2_Do_step
(
	tmUnitSelect_t  tUnit,  /*  I: Unit number */
	UInt8*          puValue /*  I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetPD_Underload
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  //  I: Item value
);
tmErrorCode_t
tmddTDA18273GetPD_Underload
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_0
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_1
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_2
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_3
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_4
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_5
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_6
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_7
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_8
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_9
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_10
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273Getrfcal_log_11
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273WaitIRQ
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeout */
    UInt32          waitStep,   /* I: wait step */
    UInt8           irqStatus   /* I: IRQs to wait */
);
tmErrorCode_t
tmddTDA18273WaitXtalCal_End
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeout */
    UInt32          waitStep    /* I: wait step */
);

#ifdef __cplusplus
}
#endif

#endif // _TMDD_TDA18273_H //---------------

