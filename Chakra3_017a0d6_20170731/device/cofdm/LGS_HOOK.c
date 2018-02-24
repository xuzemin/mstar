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
/***************************************************************************************
*					             
*			(c) Copyright 2008, LegendSilicon, beijing, China
*
*						         All Rights Reserved
*
* Description			: 
*
***************************************************************************************/

#include "Board.h"
#if(FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
/***************************************************************************************
*								  INCLUDE FILES				
***************************************************************************************/
#include "LGS_TYPES.h"

LGS_HANDLE		g_lgsHandleI2c = 0;

LGS_OPEN_I2C 	LGS_OpenI2C = 0;
LGS_READ_I2C 	LGS_ReadI2C = 0;
LGS_WRITE_I2C 	LGS_WriteI2C = 0;
LGS_CLOSE_I2C 	LGS_CloseI2C = 0;
LGS_WAIT		LGS_Wait = 0;

void LGS_RegisterI2C(LGS_OPEN_I2C popen_,
			 LGS_READ_I2C pread,
			 LGS_WRITE_I2C pwrite,
			 LGS_CLOSE_I2C pclose_)
{
	LGS_OpenI2C = popen_;
	LGS_ReadI2C = pread;
	LGS_WriteI2C = pwrite;
	LGS_CloseI2C = pclose_;
}

void LGS_RegisterWait(LGS_WAIT wait)
{
	LGS_Wait = wait;
}
#else
#include "LGS_HOOK.h"


LGS_WAIT		LGS_Wait = 0;

LGS_REGISTER_READ	LGS_ReadRegister_proc = 0;
LGS_REGISTER_WRITE	LGS_WriteRegister_proc = 0;

LGS_REGISTER_READ_MULTIBYTE	LGS_ReadRegister_MultiByte_proc = 0;
LGS_REGISTER_WRITE_MULTIBYTE	LGS_WriteRegister_MultiByte_proc = 0;

void LGS_DemodRegisterWait(LGS_WAIT wait)
{
	LGS_Wait = wait;
}

void LGS_DemodRegisterRegisterAccess(LGS_REGISTER_READ pread, LGS_REGISTER_WRITE pwrite, LGS_REGISTER_READ_MULTIBYTE	preadm, LGS_REGISTER_WRITE_MULTIBYTE pwritem)
{
	LGS_ReadRegister_proc = pread;
	LGS_WriteRegister_proc = pwrite;

	LGS_ReadRegister_MultiByte_proc = preadm;
	LGS_WriteRegister_MultiByte_proc = pwritem;
}

LGS_RESULT LGS_WaitForLock_proc(UINT8 secAddr, UINT8 regAddr, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *real_times  _LGS_DEVICEHANDLEC_)
{
	UINT8	i = 0;
	UINT8	tmp;

	for( i=0; i<times; i++ )
	{
		LGS_Wait(interval);
		LGS_ReadRegister(secAddr, regAddr, &tmp);

		if( (tmp & mask) == val )
		{
			*real_times = i;
			return LGS_NO_ERROR;
		}
	}
	*real_times = i;
	return LGS_TIMEOUT_ERROR;
}


LGS_RESULT LGS_RegisterBitSet( UINT8 secAddr, UINT8 regAddr, UINT8 bits  _LGS_DEVICEHANDLEC_)
{
	UINT8		dat;
	LGS_RESULT	err = LGS_NO_ERROR;

	if(LGS_ReadRegister_proc( secAddr, regAddr, &dat )) goto failed;
	dat |= bits;
	if(LGS_WriteRegister_proc( secAddr, regAddr, dat )) goto failed;

failed:
	return err;
}


LGS_RESULT LGS_RegisterBitClr(UINT8 secAddr, UINT8 regAddr, UINT8 bits  _LGS_DEVICEHANDLEC_)
{
	UINT8		dat;
	LGS_RESULT	err = LGS_NO_ERROR;

	if(LGS_ReadRegister_proc( secAddr, regAddr, &dat )) goto failed;
	dat &= ~(bits);
	if(LGS_WriteRegister_proc( secAddr, regAddr, dat )) goto failed;

failed:
	return err;
}

#endif
