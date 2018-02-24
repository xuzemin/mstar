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
/// @file   Mdrv_mhl.h
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_MHL_ELAND_H_
#define _DRV_MHL_ELAND_H_

#include "drvMHL_ELAND_st.h"
//#include "mdrv_mhl_st.h"


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
enum MHL_SYSTEM_CONTROL_TYPE
{
    MHL_CABLE_PLUGGED = 0,
    MHL_CABLE_UNPLUGGED,
    MHL_CBUS_UNCONNECTION,
    MHL_CBUS_CONNECTION,
    MHL_CBUS_NORMAL_24BIT_MODE,
    MHL_CBUS_PACKET_PIXEL_MODE,
    MHL_CBUS_AUTO_EQ_SETTING,
    MHL_CBUS_WAKE_UP_DETECT,
    MHL_CBUS_PM_MODE,
    MHL_CBUS_TEST_RASING,
    MHL_CBUS_TEST_FALLING,
};

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
void mdrv_mhl_MHLSupportPath(MS_U8 ucSelect);
void mdrv_mhl_init(MS_U8 *edid, MS_U8 *DevCap);
void mdrv_mhl_LoadDevCap(MS_U8 *u8devcap);
MS_BOOL mdrv_mhl_CableDetect(void);
MS_BOOL mdrv_mhl_CbusIsMscMsgReceived(void);
void mdrv_mhl_CbusIntCB(CbusReq_S *preq, MS_BOOL *bflag);
MS_U8 mdrv_mhl_GetDevCap(MS_U8 ucIndex);
MS_U8 mdrv_mhl_GetDDCErrorCode(void);
MS_U16 mdrv_mhl_CbusStatus(void);
void mdrv_mhl_Cbus_SetPathEn(MS_BOOL bFlag);
void mdrv_mhl_DriverControl(MS_U8 ucState);
MS_BOOL mdrv_mhl_CbusReply (MS_U8 ctrlpky, MS_BOOL bflag, MS_U8 databuf);
MS_BOOL mdrv_mhl_CBusWriteCmd(CbusReq_S *pReq);
void mdrv_mhl_CBusClockModeSwitch(MS_U8 ucSelect);
MS_BOOL mdrv_mhl_CBusStablePolling(MS_BOOL bFlag);

void mdrv_mhl_SetHPD(MS_BOOL bflag);

void mdrv_mhl_PowerOn(void);
void mdrv_mhl_PowerStandby(MS_BOOL bFlag);
void mdrv_mhl_PowerDown(void);

MS_BOOL mdrv_mhl_WakeupDetect(void);
void mdrv_mhl_SetPsCtrl(MS_U8 u8Ctrl);
void mdrv_mhl_SetPsCtrl_HDMImode(MS_U8 u8Ctrl);

void mdrv_mhl_LoadHdmiBypassTbl(void);
void mdrv_mhl_LoadMhl24bitsModeTbl(void);
void mdrv_mhl_LoadMhlPackedPixelModeTbl(void);
void mdrv_mhl_CbusIsolate(MS_BOOL bFlag);
void mdrv_mhl_CbusFloating(MS_BOOL bFlag);
void mdrv_mhl_CbusFloating(MS_BOOL bFlag);
void mdrv_mhl_RxRtermControl(RXRtermControl_T rctrl);
void mdrv_mhl_RxRtermIsolate(void);

//only for debug
void mdrv_mhl_Write2bytes(MS_U16 reg, MS_U16 val);
MS_U16 mdrv_mhl_Read2bytes(MS_U16 reg);

void mdrv_mhl_Set_IIC_16BMode(void);
void mdrv_mhl_RegisterCallBackFunctions(link_mhl_reg_i_func_b pfnRead, link_mhl_reg_o_func_b pfnWrite);
void mdrv_mhl_I2C_Channel_Settings(MS_U16 u16Channel, MS_U8 u8CommonID, MS_U8 u8ConfigID);
void mdrv_mhl_TxSwap_Settings(MS_BOOL bTxSwapEnable);


#endif //_DRV_MHL_ELAND_H_

