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
////////////////////////////////////////////////////////////////////////////////
#define _HAL_VIF_C

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#include "halVif.h"
#include "drvIIC.h"
#include "Board.h"
////////////////////////////////////////////////////////////////////////////////
// Define & data type
///////////////////////////////////////////////////////////////////////////////
#define DBG_HAL_MSB(x)          //x
#define     DEMOD_ADDR_H            0x00
#define     DEMOD_READ_REG          0x04
////////////////////////////////////////////////////////////////////////////////
// Global variable
////////////////////////////////////////////////////////////////////////////////
extern U8 gu8DemoDynamicI2cAddress;
////////////////////////////////////////////////////////////////////////////////
// Extern Function
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function Declaration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Function
////////////////////////////////////////////////////////////////////////////////
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210 || FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
static U8 u8MsbData[6];

/***********************************************************************************
  Subject:    Write register
  Function:   MSB1210_WriteReg
  Parmeter:   u16Addr:   Register address
              u8Data:    Data to write
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1210_WriteReg(U16 u16Addr, U8 u8Data)
{
    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = (u16Addr >> 8) & 0xff;
    u8MsbData[2] = u16Addr & 0xff;
    u8MsbData[3] = u8Data;
    return MDrv_IIC_WriteBytes(gu8DemoDynamicI2cAddress, 0, 0, 4, u8MsbData);
}
/***********************************************************************************
  Subject:    read register
  Function:   MSB1210_ReadReg
  Parmeter:   u16Addr:   Register address
              pu8Data:   pointer for return data
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN MSB1210_ReadReg(U16 u16Addr, U8 *pu8Data)
{
    u8MsbData[0] = DEMOD_ADDR_H;
    u8MsbData[1] = (u16Addr >> 8) & 0xff;
    u8MsbData[2] = u16Addr & 0xff;

    if (MDrv_IIC_WriteBytes(gu8DemoDynamicI2cAddress, 0, 0, 3, u8MsbData) == FALSE)
    {
        DBG_HAL_MSB(printf("read write fail----%x\n",gu8DemoDynamicI2cAddress));
        return FALSE;
    }

    u8MsbData[0] = DEMOD_READ_REG;

    return MDrv_IIC_ReadBytes(gu8DemoDynamicI2cAddress, 1, u8MsbData, 1, pu8Data);
}
#endif
