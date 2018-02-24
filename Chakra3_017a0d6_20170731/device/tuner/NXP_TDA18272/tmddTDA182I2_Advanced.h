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
Copyright (C) 2008 NXP B.V., All Rights Reserved.
This source code and any compilation or derivative thereof is the proprietary
information of NXP B.V. and is confidential in nature. Under no circumstances
is this software to be  exposed to or placed under an Open Source License of
any type without the expressed written permission of NXP B.V.
*
* \file          tmddTDA182I2.h
*                %version: 3 %
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
#ifndef _TMDD_TDA182I2_ADVANCED_H //-----------------
#define _TMDD_TDA182I2_ADVANCED_H

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
#define ddTDA182I2_ERR_BASE               (CID_COMP_TUNER | CID_LAYER_BSL)
#define ddTDA182I2_ERR_COMP               (CID_COMP_TUNER | CID_LAYER_BSL | TM_ERR_COMP_UNIQUE_START)

#define ddTDA182I2_ERR_BAD_UNIT_NUMBER    (ddTDA182I2_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define ddTDA182I2_ERR_NOT_INITIALIZED    (ddTDA182I2_ERR_BASE + TM_ERR_NOT_INITIALIZED)
#define ddTDA182I2_ERR_INIT_FAILED        (ddTDA182I2_ERR_BASE + TM_ERR_INIT_FAILED)
#define ddTDA182I2_ERR_BAD_PARAMETER      (ddTDA182I2_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define ddTDA182I2_ERR_NOT_SUPPORTED      (ddTDA182I2_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define ddTDA182I2_ERR_HW_FAILED          (ddTDA182I2_ERR_COMP + 0x0001)
#define ddTDA182I2_ERR_NOT_READY          (ddTDA182I2_ERR_COMP + 0x0002)
#define ddTDA182I2_ERR_BAD_VERSION        (ddTDA182I2_ERR_COMP + 0x0003)


    tmErrorCode_t
        tmddTDA182I2Init
        (
        tmUnitSelect_t    tUnit,    //  I: Unit number
        tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
        );
    tmErrorCode_t 
        tmddTDA182I2DeInit
        (
        tmUnitSelect_t    tUnit     //  I: Unit number
        );
    tmErrorCode_t
        tmddTDA182I2GetSWVersion
        (
        ptmSWVersion_t    pSWVersion        //  I: Receives SW Version 
        );
    tmErrorCode_t
        tmddTDA182I2Reset
        (
        tmUnitSelect_t  tUnit     //  I: Unit number
        );
    tmErrorCode_t
        tmddTDA182I2SetLPF_Gain_Mode
        (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt8           uMode   /* I: Unknown/Free/Frozen */
        );
    tmErrorCode_t
        tmddTDA182I2GetLPF_Gain_Mode
        (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt8           *puMode /* O: Unknown/Free/Frozen */
        );
    tmErrorCode_t
        tmddTDA182I2Write
        (
        tmUnitSelect_t      tUnit,      //  I: Unit number
        UInt32              uIndex,         //  I: Start index to write
        UInt32              uNbBytes,       //  I: Number of bytes to write
        UInt8*             puBytes         //  I: Pointer on an array of bytes
        );
    tmErrorCode_t
        tmddTDA182I2Read
        (
        tmUnitSelect_t      tUnit,      //  I: Unit number
        UInt32              uIndex,         //  I: Start index to read
        UInt32              uNbBytes,       //  I: Number of bytes to read
        UInt8*             puBytes         //  I: Pointer on an array of bytes
        );
    tmErrorCode_t
        tmddTDA182I2GetPOR
        (
        tmUnitSelect_t    tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetLO_Lock
        (
        tmUnitSelect_t    tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMS
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIdentity
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt16*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMinorRevision
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMajorRevision
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetTM_D
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetTM_ON
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetTM_ON
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPowerState
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        tmddTDA182I2PowerState_t  powerState    //  I: Power state of this device
        );
    tmErrorCode_t
        tmddTDA182I2GetPowerState
        (
        tmUnitSelect_t        tUnit,    //  I: Unit number
        ptmddTDA182I2PowerState_t    pPowerState  //  O: Power state of this device
        );

    tmErrorCode_t
        tmddTDA182I2GetPower_Level
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIRQ_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIRQ_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetXtalCal_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetXtalCal_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RSSI_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RSSI_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_LOCalc_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_LOCalc_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RFCAL_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RFCAL_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_IRCAL_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_IRCAL_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RCCal_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RCCal_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
	/*
    tmErrorCode_t
        tmddTDA182I2SetIRQ_Clear
        (
        tmUnitSelect_t      tUnit    //  I: Unit number
        );*/
    tmErrorCode_t
        tmddTDA182I2SetXtalCal_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetXtalCal_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RSSI_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RSSI_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_LOCalc_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_LOCalc_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RFCal_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RFCal_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_IRCAL_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_IRCAL_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RCCal_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RCCal_Clear
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIRQ_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIRQ_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetXtalCal_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetXtalCal_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RSSI_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RSSI_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_LOCalc_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_LOCalc_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RFCal_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RFCal_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_IRCAL_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_IRCAL_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_RCCal_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RCCal_Set
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIRQ_status
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_XtalCal_End
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RSSI_End
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_LOCalc_End
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RFCal_End
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_IRCAL_End
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_RCCal_End
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetLT_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetLT_Enable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC1_6_15dB
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC1_6_15dB
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC1_TOP
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC1_TOP
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC2_TOP
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC2_TOP
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGCs_Up_Step_assym
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGCs_Up_Step_assym
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGCs_Up_Step
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGCs_Up_Step
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPulse_Shaper_Disable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPulse_Shaper_Disable
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGCK_Step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGCK_Step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGCK_Mode
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGCK_Mode
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPD_RFAGC_Adapt
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPD_RFAGC_Adapt
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFAGC_Adapt_TOP
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFAGC_Adapt_TOP
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFAGC_Low_BW
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFAGC_Low_BW
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_Atten_3dB
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_Atten_3dB
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFAGC_Top
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFAGC_Top
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_Mixer_Top
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_Mixer_Top
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGCs_Do_Step_assym
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGCs_Do_Step_assym
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC5_Ana
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC5_Ana
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC5_TOP
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC5_TOP
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIF_Level
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIF_Level
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIF_HP_Fc
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIF_HP_Fc
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIF_ATSC_Notch
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIF_ATSC_Notch
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetLP_FC_Offset
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetLP_FC_Offset
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetLP_FC
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetLP_FC
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetI2C_Clock_Mode
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetI2C_Clock_Mode
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetDigital_Clock_Mode
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDigital_Clock_Mode
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetXtalOsc_AnaReg_En
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetXtalOsc_AnaReg_En
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetXTout
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetXTout
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIF_Freq
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt32          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIF_Freq
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt32*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_Freq
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt32          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_Freq
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt32*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRSSI_Meas
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRSSI_Meas
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_CAL_AV
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_CAL_AV
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_CAL
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_CAL
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_CAL_Loop
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_CAL_Loop
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_Cal_Image
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_Cal_Image
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_CAL_Wanted
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_CAL_Wanted
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRC_Cal
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRC_Cal
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetCalc_PLL
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetCalc_PLL
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetXtalCal_Launch
        (
        tmUnitSelect_t      tUnit    //  I: Unit number
        );
    tmErrorCode_t
        tmddTDA182I2GetXtalCal_Launch
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetMSM_Launch
        (
        tmUnitSelect_t      tUnit    //  I: Unit number
        );
    tmErrorCode_t
        tmddTDA182I2GetMSM_Launch
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPSM_AGC1
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPSM_AGC1
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPSM_StoB
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPSM_StoB
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPSMRFpoly
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPSMRFpoly
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPSM_Mixer
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPSM_Mixer
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPSM_Ifpoly
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPSM_Ifpoly
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPSM_Lodriver
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPSM_Lodriver
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetDCC_Bypass
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDCC_Bypass
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetDCC_Slow
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDCC_Slow
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetDCC_psm
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDCC_psm
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_Loop
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_Loop
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_Target
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_Target
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_GStep
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_GStep
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_Corr_Boost
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_Corr_Boost
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_FreqLow_Sel
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_FreqLow_Sel
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_mode_ram_store
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_mode_ram_store
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_FreqLow
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_FreqLow
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_FreqMid
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_FreqMid
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetCoarse_IR_FreqHigh
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetCoarse_IR_FreqHigh
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_FreqHigh
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_FreqHigh
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );

    tmErrorCode_t
        tmddTDA182I2SetPD_Vsync_Mgt
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPD_Vsync_Mgt
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPD_Ovld
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPD_Ovld
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetPD_Udld
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetPD_Udld
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC_Ovld_TOP
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC_Ovld_TOP
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC_Ovld_Timer
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC_Ovld_Timer
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_Mixer_loop_off
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_Mixer_loop_off
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIR_Mixer_Do_step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIR_Mixer_Do_step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetHi_Pass
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetHi_Pass
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIF_Notch
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIF_Notch
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC1_loop_off
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC1_loop_off
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC1_Do_step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC1_Do_step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetForce_AGC1_gain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetForce_AGC1_gain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC1_Gain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC1_Gain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC5_loop_off
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC5_loop_off
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC5_Do_step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC5_Do_step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetForce_AGC5_gain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetForce_AGC5_gain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC5_Gain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC5_Gain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq0
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq0
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq1
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq1
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq2
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq2
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq3
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq3
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq4
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq4
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq5
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq5
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq6
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq6
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq7
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq7
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq8
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq8
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq9
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq9
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq10
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq10
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Freq11
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Freq11
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset0
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset0
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset1
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset1
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset2
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset2
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset3
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset3
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset4
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset4
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset5
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue   //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset5
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset6
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset6
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset7
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset7
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset8
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset8
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset9
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset9
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset10
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset10
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Offset11
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Offset11
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_SW_Algo_Enable
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_SW_Algo_Enable
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_Filter_Bypass
        (
        tmUnitSelect_t  tUnit,    //  I: Unit number
        UInt8           uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_Filter_Bypass
        (
        tmUnitSelect_t  tUnit,    //  I: Unit number
        UInt8*          puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC2_loop_off
        (
        tmUnitSelect_t  tUnit,    //  I: Unit number
        UInt8           uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC2_loop_off
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetForce_AGC2_gain
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetForce_AGC2_gain
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_Filter_Gv
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_Filter_Gv
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_Filter_Band
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_Filter_Band
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_Filter_Cap
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_Filter_Cap
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetAGC2_Do_step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC2_Do_step
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetGain_Taper
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetGain_Taper
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_BPF
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_BPF
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRF_BPF_Bypass
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRF_BPF_Bypass
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetN_CP_Current
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetN_CP_Current
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetUp_AGC5
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDo_AGC5
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetUp_AGC4
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDo_AGC4
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetUp_AGC2
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDo_AGC2
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetUp_AGC1
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDo_AGC1
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC2_Gain_Read
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC1_Gain_Read
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetTOP_AGC3_Read
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC5_Gain_Read
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2GetAGC4_Gain_Read
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRSSI
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRSSI
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRSSI_AV
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRSSI_AV
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRSSI_Cap_Reset_En
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRSSI_Cap_Reset_En
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRSSI_Cap_Val
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRSSI_Cap_Val
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRSSI_Ck_Speed
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRSSI_Ck_Speed
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRSSI_Dicho_not
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRSSI_Dicho_not
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_Phi2
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_Phi2
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetDDS_Polarity
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8           uValue  //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetDDS_Polarity
        (
        tmUnitSelect_t  tUnit,  //  I: Unit number
        UInt8*          puValue //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetRFCAL_DeltaGain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetRFCAL_DeltaGain
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2SetIRQ_Polarity
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8          uValue      //  I: Item value
        );
    tmErrorCode_t
        tmddTDA182I2GetIRQ_Polarity
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_0
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_1
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_2
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_3
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_4
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_5
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_6
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_7
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_8
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_9
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_10
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2_ExpertGetrfcal_log_11
        (
        tmUnitSelect_t      tUnit,    //  I: Unit number
        UInt8*        puValue      //  I: Address of the variable to output item value
        );
    tmErrorCode_t
        tmddTDA182I2LaunchRF_CAL
        (
        tmUnitSelect_t      tUnit    //  I: Unit number
        );
    tmErrorCode_t
        tmddTDA182I2WaitIRQ
        (
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          timeOut,    /* I: timeout */
        UInt32          waitStep,   /* I: wait step */
        UInt8           irqStatus   /* I: IRQs to wait */
        );
    tmErrorCode_t
        tmddTDA182I2WaitXtalCal_End
        (
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          timeOut,    /* I: timeout */
        UInt32          waitStep    /* I: wait step */
        );
    tmErrorCode_t
        tmddTDA182I2SetResetWait
        (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        Bool            bWait   /* I: Determine if we need to wait in Reset function */
        );
    tmErrorCode_t
        tmddTDA182I2GetResetWait
        (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        Bool*           pbWait  /* O: Determine if we need to wait in Reset function */
        );

#ifdef __cplusplus
}
#endif

#endif // _TMDD_TDA182I2_ADVANCED_H //---------------
