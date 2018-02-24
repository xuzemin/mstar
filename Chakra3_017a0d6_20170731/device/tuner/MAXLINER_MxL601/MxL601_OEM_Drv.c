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
/*****************************************************************************************
 *
 * FILE NAME          : MxL601_OEM_Drv.c
 *
 * AUTHOR             : Dong Liu
 *
 * DATE CREATED       : 01/23/2011
 *
 * DESCRIPTION        : This file contains I2C driver and Sleep functins that
 *                      OEM should implement for MxL601 APIs
 *
 *****************************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ****************************************************************************************/

#include "MxL601_OEM_Drv.h"
#include "MaxLinearDataTypes.h"
#include "drvIIC.h"
#include "msAPI_Timer.h"

//#define MxL_I2CBUS_ADDR 0x0200
#define MxL_I2CBUS_ADDR			((TUNER_IIC_BUS << 8) | 0xC0)
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : Ctrl_WriteRegister
--|
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C write operation.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS Ctrl_WriteRegister(UINT8 I2cSlaveAddr, UINT8 RegAddr, UINT8 RegData)
{
//  MXL_STATUS status = MXL_TRUE;
//  U8 *PBUF;
//	U8 *PADDR;
//	UINT8 REG[1];
//	REG[0] = RegData;
    UNUSED(I2cSlaveAddr);
//	PBUF = REG;
//	PADDR = &RegAddr;
//	printf("Mxl I2C wirte RegAddr=%d,RegData=%d\n",RegAddr,RegData);
  // OEM should implement I2C write protocol that complies with MxL601 I2C
  // format.

  // 8 bit Register Write Protocol:
  // +------+-+-----+-+-+----------+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |RegAddr(H)| |RegAddr(L)| |RegData(L)| |P|
  // +------+-+-----+-+-+----------+-+----------+-+----------+-+-+
  // |SLAVE |         |A|          |A|          |A|          |A| |
  // +------+---------+-+----------+-+----------+-+----------+-+-+
  // Legends: SADDR (I2c slave address), S (Start condition), A (Ack), N(NACK),
  // P(Stop condition)
//	if(MDrv_IIC_WriteBytes((U16)(MxL_I2CBUS_ADDR|(I2cSlaveAddr<<1)), 0, PADDR, (U16) 1, &RegData))
    if(MDrv_IIC_WriteBytes((U16)(MxL_I2CBUS_ADDR), 1, &RegAddr, (U16) 1, &RegData))
        return MXL_TRUE;
    else
        printf("Mxl I2C wirte error. slaveid=0x%x, RegAddr=%d,RegData=%d\n",MxL_I2CBUS_ADDR,RegAddr,RegData);

    return MXL_FALSE;

 // return status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : Ctrl_ReadRegister
--|
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C read operation.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS Ctrl_ReadRegister(UINT8 I2cSlaveAddr, UINT8 RegAddr, UINT8 *DataPtr)
{
    UINT8 u8addr=0xFB;

    UNUSED(I2cSlaveAddr);

    if(!MDrv_IIC_WriteBytes((U16)(MxL_I2CBUS_ADDR),1, &u8addr,1,&RegAddr))
    {
        printf("Mxl I2C read 1 error. slaveid=0x%x\n",MxL_I2CBUS_ADDR);
        return MXL_FALSE;
    }
    if(MDrv_IIC_ReadBytes((U16)(MxL_I2CBUS_ADDR),0,NULL,1,DataPtr))
        return MXL_TRUE;

    printf("Mxl I2C read 2 error. slaveid=0x%x\n",MxL_I2CBUS_ADDR);

    return MXL_FALSE;


  // OEM should implement I2C read protocol that complies with MxL601 I2C
  // format.

  // 16 Register Read Protocol:
  // +------+-+-----+-+-+----+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |0xFB| |RegAddr(H)| |RegAddr(L)| |P|
  // +------+-+-----+-+-+----+-+----------+-+----------+-+-+
  // |SLAVE |         |A|    |A|          |A|          |A| |
  // +------+-+-----+-+-+----+-+----------+-+----------+-+-+
  // +------+-+-----+-+-+-----+--+-+
  // |MASTER|S|SADDR|R| |     |MN|P|
  // +------+-+-----+-+-+-----+--+-+
  // |SLAVE |         |A|Data |  | |
  // +------+---------+-+-----+--+-+
  // Legends: SADDR(I2c slave address), S(Start condition), MA(Master Ack), MN(Master NACK),
  // P(Stop condition)

 // return status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MXL_Sleep
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 01/10/2010
--|
--| DESCRIPTION   : This function complete sleep operation. WaitTime is in ms unit
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

void MxL_Sleep(UINT16 DelayTimeInMs)
{
	msAPI_Timer_Delayms(DelayTimeInMs);
  // OEM should implement sleep operation
}

