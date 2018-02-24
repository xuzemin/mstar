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
*                %version: CFR_FEAP#10 %
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
#ifndef _TMDD_TDA18273_ADVANCED_H //-----------------
#define _TMDD_TDA18273_ADVANCED_H

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



tmErrorCode_t
    tmddTDA18273SetIRQ_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIRQ_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetXtalCal_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetXtalCal_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RSSI_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RSSI_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_LOCalc_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_LOCalc_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RFCAL_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RFCAL_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_IRCAL_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_IRCAL_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RCCal_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RCCal_Enable
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetXtalCal_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetXtalCal_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RSSI_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RSSI_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_LOCalc_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_LOCalc_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RFCal_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RFCal_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_IRCAL_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_IRCAL_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RCCal_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RCCal_Clear
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetIRQ_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIRQ_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetXtalCal_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetXtalCal_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RSSI_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RSSI_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetRSSI
    (
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
    );
tmErrorCode_t
    tmddTDA18273SetMSM_LOCalc_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_LOCalc_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RFCal_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RFCal_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_IRCAL_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_IRCAL_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetMSM_RCCal_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RCCal_Set
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetIRQ_status
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_XtalCal_End
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RSSI_End
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_LOCalc_End
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RFCal_End
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_IRCAL_End
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetMSM_RCCal_End
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC2_TOP
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC2_TOP
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGCs_Up_Step_assym
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGCs_Up_Step_assym
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGCK_Step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGCK_Step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGCK_Mode
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGCK_Mode
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFAGC_Low_BW
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFAGC_Low_BW
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
tmddTDA18273SetW_Filter_Bypass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetW_Filter_Bypass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
tmddTDA18273SetW_Filter
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
);
tmErrorCode_t
tmddTDA18273GetW_Filter
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
    tmddTDA18273SetIFnotchToRSSI
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIFnotchToRSSI
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetLPF_DCOffset_Corr
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetLPF_DCOffset_Corr
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetDigital_Clock_Mode
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetDigital_Clock_Mode
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetXTout
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetXTout
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPSM_AGC1
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPSM_AGC1
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPSM_Bandsplit_Filter
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPSM_Bandsplit_Filter
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPSMRFpoly
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPSMRFpoly
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPSM_Mixer
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPSM_Mixer
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPSM_Ifpoly
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPSM_Ifpoly
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPSM_Lodriver
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPSM_Lodriver
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPD_PLD_read
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPD_PLD_read
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPLD_Temp_Slope
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPLD_Temp_Slope
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPLD_Gain_Corr
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    Int8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPLD_Gain_Corr
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    Int8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetFast_Mode_AGC
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetFast_Mode_AGC
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRange_LNA_Adapt
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRange_LNA_Adapt
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetIndex_K_LNA_Adapt
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIndex_K_LNA_Adapt
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetIndex_K_Top_Adapt
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIndex_K_Top_Adapt
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetOvld_Udld_FastUp
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetOvld_Udld_FastUp
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetNeg_modulation
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetNeg_modulation
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetTracer_Step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetTracer_Step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetVsync_int
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetVsync_int
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetVsync_Thresh
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetVsync_Thresh
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetVsync_Len
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetVsync_Len
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPD_Vsync_Mgt
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPD_Vsync_Mgt
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPD_Ovld
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPD_Ovld
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPD_Ovld_RF
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPD_Ovld_RF
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC_Ovld_TOP
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC_Ovld_TOP
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetUp_Step_Ovld
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetUp_Step_Ovld
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC_Ovld_Timer
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC_Ovld_Timer
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetIR_Mixer_loop_off
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIR_Mixer_loop_off
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetIR_Mixer_Do_step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIR_Mixer_Do_step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetHi_Pass
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetHi_Pass
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetIF_Notch
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIF_Notch
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC1_loop_off
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC1_loop_off
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC1_Do_step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC1_Do_step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetForce_AGC1_gain
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetForce_AGC1_gain
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC5_loop_off
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC5_loop_off
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC5_Do_step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC5_Do_step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetForce_AGC5_gain
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetForce_AGC5_gain
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPLD_DAC_Scale
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPLD_DAC_Scale
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*        puValue  //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPLD_CC_Enable
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPLD_CC_Enable
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*        puValue  //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetPLD_Temp_Enable
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetPLD_Temp_Enable
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*        puValue  //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetTH_AGC_Adapt34
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetTH_AGC_Adapt34
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*        puValue  //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFAGC_Sense_Enable
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFAGC_Sense_Enable
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*        puValue  //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFAGC_K_Bypass
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFAGC_K_Bypass
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*        puValue  //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFAGC_K
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt16          uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFAGC_K
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt16*         puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset0
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset0
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset1
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset1
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset2
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset2
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset3
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset3
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset4
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset4
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset5
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue   //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset5
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset6
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset6
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset7
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset7
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset8
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset8
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset9
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset9
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset10
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset10
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRFCAL_Offset11
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRFCAL_Offset11
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetBandsplit_Filter_SubBand
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetBandsplit_Filter_SubBand
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRF_Filter_Bypass
    (
    tmUnitSelect_t  tUnit,    //  I: Unit number
    UInt8           uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRF_Filter_Bypass
    (
    tmUnitSelect_t  tUnit,    //  I: Unit number
    UInt8*          puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC2_loop_off
    (
    tmUnitSelect_t  tUnit,    //  I: Unit number
    UInt8           uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC2_loop_off
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetForce_AGC2_gain
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetForce_AGC2_gain
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRF_Filter_Gv
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRF_Filter_Gv
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRF_Filter_Band
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRF_Filter_Band
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRF_Filter_Cap
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRF_Filter_Cap
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetAGC2_Do_step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetAGC2_Do_step
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetGain_Taper
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetGain_Taper
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRF_BPF
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRF_BPF
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRF_BPF_Bypass
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRF_BPF_Bypass
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetLO_CP_Current
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetLO_CP_Current
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetN_CP_Current
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetN_CP_Current
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetUp_AGC5
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetDo_AGC5
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetUp_AGC4
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetDo_AGC4
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetUp_AGC2
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetDo_AGC2
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetUp_AGC1
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetDo_AGC1
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetTOP_AGC3_Read
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRSSI
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273SetRSSI_AV
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRSSI_AV
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRSSI_Cap_Reset_En
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRSSI_Cap_Reset_En
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRSSI_Cap_Val
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRSSI_Cap_Val
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRSSI_Ck_Speed
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRSSI_Ck_Speed
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetRSSI_Dicho_not
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetRSSI_Dicho_not
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273GetCprog_Read
    (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt8*          puValue /* I: Address of the variable to output item value */
    );
tmErrorCode_t
    tmddTDA18273GetDo_AGC1bis
    (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt8*          puValue /* I: Address of the variable to output item value */
    );
tmErrorCode_t
    tmddTDA18273GetAGC1_Top_Adapt_Low
    (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt8*          puValue /* I: Address of the variable to output item value */
    );
tmErrorCode_t
    tmddTDA18273GetUp_LNA_Adapt
    (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt8*          puValue /* I: Address of the variable to output item value */
    );
tmErrorCode_t
    tmddTDA18273GetDo_LNA_Adapt
    (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt8*          puValue /* I: Address of the variable to output item value */
    );
tmErrorCode_t
    tmddTDA18273GetRFAGC_Read_K
    (
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt16*         puValue /* I: Address of the variable to output item value */
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
    tmddTDA18273SetDDS_Polarity
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8           uValue  //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetDDS_Polarity
    (
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273SetIRQ_Mode
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8          uValue      //  I: Item value
    );
tmErrorCode_t
    tmddTDA18273GetIRQ_Mode
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_0
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_1
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_2
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_3
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_4
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_5
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_6
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_7
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_8
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_9
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_10
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
    tmddTDA18273_ExpertGetrfcal_log_11
    (
    tmUnitSelect_t      tUnit,    //  I: Unit number
    UInt8*        puValue      //  I: Address of the variable to output item value
    );
tmErrorCode_t
tmddTDA18273SetInternal_Test_Signal
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  //  I: Item value
);
tmErrorCode_t
tmddTDA18273GetInternal_Test_Signal
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
);
tmErrorCode_t
    tmddTDA18273SetResetWait
    (
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool            bWait   /* I: Determine if we need to wait in Reset function */
    );
tmErrorCode_t
    tmddTDA18273GetResetWait
    (
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool*           pbWait  /* O: Determine if we need to wait in Reset function */
    );
tmErrorCode_t
    tmddTDA18273GetAGC1_2_4_5_Gain_Read
    (
     tmUnitSelect_t  tUnit,       //  I: Unit number
     UInt8*          puAGC1Value, //  O: Address of the variable to output item value
     UInt8*          puAGC2Value, //  O: Address of the variable to output item value
     UInt8*          puAGC4Value, //  O: Address of the variable to output item value
     UInt8*          puAGC5Value  //  O: Address of the variable to output item value
    );

#ifdef __cplusplus
}
#endif

#endif // _TMDD_TDA18273_ADVANCED_H //---------------
