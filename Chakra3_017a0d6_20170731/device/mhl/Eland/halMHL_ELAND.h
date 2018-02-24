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
///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   MST_ELAND_HAL.h
/// @author MStar Semiconductor Inc.
/// @brief  MHL HAL Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _HAL_MHL_ELAND_H_
#define _HAL_MHL_ELAND_H_

#include "drvMHL_ELAND_st.h"

#define EnBYPASS_HDCP_DDC 1
#define EnBYPASS_EDID_DDC  0

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define MsMHL_CONFIG_ID 	0xD0
#define MsMHL_DEVICE_ID     0xC8

#define MHL_CDR_STABLE_THRESHOLD        100
#define MHL_CDR_STABLE_OFFSET           10

#define CBUS_CDR_CLOCK_TARGET           20
#define CBUS_CLOCK_DETECT_LEVEL         (CBUS_CDR_CLOCK_TARGET *64 /14.318)

#define CBUS_CDR_OFFSET_TARGET          0.5
#define CBUS_CLOCK_DETECT_OFFSET        (CBUS_CDR_OFFSET_TARGET *64 /14.318)

#define MHL_DRIVER_U01                  0
#define MHL_DRIVER_U02                  1
#define MHL_DRIVER_U03                  2
#define MHL_DRIVER_U04                  3

#define MHL_DRIVER_VERSION              MHL_DRIVER_U04

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
void mhal_mhl_MHLSupportPath(MS_U8 ucSelect);

void msWriteWord(MS_U16 reg, MS_U16 val);
void msWriteWordMask(MS_U16 reg, MS_U16 val, MS_U16 mask);
MS_U16 msReadWord(MS_U16 reg);
void mhal_mhl_Set_IIC_16BMode(void);
void mhal_mhl_Set_IIC_8BMode(void);
void mhal_mhl_Set_Bank(MS_U8 ucbank);

MS_BOOL mhal_mhl_CBusWrite(mhalCbusFifo_S *pdatabuf);
void mhal_mhl_CbusIsolate(MS_BOOL bFlag);
void mhal_mhl_init(MS_U8 *edid, MS_U8 *devcap);
void mhal_mhl_CbusFloating(MS_BOOL bFlag);
#if(DMHL_WAKE_UP_PULSE_INT)
void mhal_mhl_MHLForceToStandby(void);
void mhal_mhl_ClearWakeupIntFlag(void);
#endif
MS_BOOL mhal_mhl_CableDetect(void);
void mhal_mhl_Cbus_SetPathEn(MS_BOOL bflag);
//void mhal_mhl_SetTMDSTxOnOff(Bool bflag);
MS_BOOL mhal_mhl_CbusIsMscMsgReceived(void);
void mhal_mhl_CbusIntCB(MS_U8 *rcstate, MS_U8 *rccmd, MS_U8 *rcdata, MS_U8 *rclen, MS_U8 *bIsCmdInData);
MS_U16 mhal_mhl_CbusStatus(void);
MS_BOOL mhal_mhl_CDRModeMonitor(MS_BOOL bPathEnable);
MS_BOOL mhal_mhl_CBusCheckBCHError(void);
#if(DMHL_LG_PRADA_PATCH)
void mhal_mhl_AdjustCommonModeResistor(MS_BOOL bflag);
#endif
#if(DMHL_TEST_SIGNAL_SUPPORT)
void mhal_mhl_TestSignal(MS_BOOL bflag);
#endif
void mhal_mhl_RxRtermControl(RXRtermControl_T rctrl);
void mhal_mhl_LoadHdmiBypassTbl(void);
void mhal_mhl_LoadMhl24bitsModeTbl(void);
void mhal_mhl_LoadMhlPackedPixelModeTbl(void);

void mhal_mhl_LoadPowerOnTbl(void);
void mhal_mhl_LoadPowerStandbyTbl(void);
void mhal_mhl_LoadPowerDownTbl(void);

void mhal_mhl_SetHPD(MS_BOOL bflag);
MS_U8 mhal_mhl_GetDDCErrorCode(void);
MS_U16 mhal_mhl_GetTMDSClk(void);
void mhal_mhl_SetPsCtrl(MS_U8 u8Ctrl);
void mhal_mhl_SetPsCtrl_HDMImode(MS_U8 u8Ctrl);

void mhal_mhl_LoadDevCap(MS_U8 *devcap);
MS_U8 mhal_mhl_GetDevCap(MS_U8 u8Idx);


void mhal_mhl_RegisterCallBackFunctions(link_mhl_reg_i_func_b pfnRead, link_mhl_reg_o_func_b pfnWrite);
void mhal_mhl_I2C_Channel_Settings(MS_U16 u16Channel, MS_U8 u8CommonID, MS_U8 u8ConfigID);
void mhal_mhl_TxSwap_Settings(MS_BOOL bTxSwapEnable);

#endif //_HAL_MHL_ELAND_H_
