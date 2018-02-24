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
*                           (c) Copyright 2008, LegendSilicon, beijing, China
*
*                                        All Rights Reserved
*
* Description :
*
* Notice:
*
***************************************************************************************/

#include "Board.h"
#if(FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
/***************************************************************************************
*								  INCLUDE FILES				
***************************************************************************************/
#ifdef __cplusplus 
extern "C" { 
#endif 

#include "LGS_TYPES.h"

extern LGS_HANDLE		g_lgsHandleI2c;

extern LGS_OPEN_I2C 	LGS_OpenI2C;
extern LGS_READ_I2C 	LGS_ReadI2C;
extern LGS_WRITE_I2C 	LGS_WriteI2C;
extern LGS_CLOSE_I2C 	LGS_CloseI2C;
extern LGS_WAIT			LGS_Wait;

void LGS_RegisterI2C(LGS_OPEN_I2C popen, LGS_READ_I2C pread, LGS_WRITE_I2C pwrite, LGS_CLOSE_I2C pclose);
void LGS_RegisterWait(LGS_WAIT wait);
//LGS_RESULT LGS_WaitForLock( UINT8 reg, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *real_times);

#ifdef __cplusplus 
} 
#endif 

#else
#ifndef _DEMOD_HOOK_C631FEF2_89A8_4ae5_B22A_04122BA8B12D_H_
#define _DEMOD_HOOK_C631FEF2_89A8_4ae5_B22A_04122BA8B12D_H_

#include "LGS_TYPES.h"
#include <stdio.h>

#ifdef _DEBUG
	#define LGSDbgPrint(_x_)	printf _x_
#else
	#define LGSDbgPrint(_x_)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// Description : 等待某寄存器的值成为期望值
// secAddr:section 地址  
// regAddr: 寄存器地址
// mask：掩码
// val：期望的正确值
// interval：每次循环之间的间隔
// times:循环的次数
// realTimes:实际的循环次数
LGS_RESULT LGS_WaitForLock_proc(UINT8 secAddr, UINT8 regAddr, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *realTimes  _LGS_DEVICEHANDLEC_);



extern LGS_WAIT				LGS_Wait;

extern LGS_REGISTER_READ		LGS_ReadRegister_proc;
extern LGS_REGISTER_WRITE		LGS_WriteRegister_proc;

extern LGS_REGISTER_READ_MULTIBYTE	LGS_ReadRegister_MultiByte_proc;
extern LGS_REGISTER_WRITE_MULTIBYTE	LGS_WriteRegister_MultiByte_proc;


////////////////////////////////////////////////////////////////
// 寄存器读写函数
////////////////////////////////////////////////////////////////
#define LGS_ReadRegister(_secAddr_, _regAddr_, _pregVal_) \
		LGS_ReadRegister_proc(_secAddr_, _regAddr_, _pregVal_  _LGS_DEVICEHANDLE_PARAC_)

#define LGS_WriteRegister(_secAddr_, _regAddr_, _regVal_) \
		LGS_WriteRegister_proc(_secAddr_, _regAddr_, _regVal_  _LGS_DEVICEHANDLE_PARAC_)

#define LGS_ReadRegister_MultiByte(_secAddr_, _regAddr_, _pregVal_, _len_) \
		LGS_ReadRegister_MultiByte_proc(_secAddr_, _regAddr_, _pregVal_, _len_  _LGS_DEVICEHANDLE_PARAC_)

#define LGS_WriteRegister_MultiByte(_secAddr_, _regAddr_, _pregVal_, _len_) \
		LGS_WriteRegister_MultiByte_proc(_secAddr_, _regAddr_, _pregVal_, _len_  _LGS_DEVICEHANDLE_PARAC_)

#define LGS_WaitForLock( _secAddr_, _regAddr_, _mask_, _val_, _interval_, _times_, _real_times_) \
		LGS_WaitForLock_proc( _secAddr_, _regAddr_, _mask_, _val_, _interval_, _times_, _real_times_  _LGS_DEVICEHANDLE_PARAC_)



LGS_RESULT LGS_RegisterBitSet( UINT8 secAddr, UINT8 regAddr, UINT8 bit  _LGS_DEVICEHANDLEC_);

LGS_RESULT LGS_RegisterBitClr(UINT8 secAddr, UINT8 regAddr, UINT8 bit  _LGS_DEVICEHANDLEC_);


static const UINT32 g_IFFrctor_1K = 141282;

static const UINT32 g_IFFrctor_1_7K = 240179;

// 内部函数使用的定义

/// Index for SetIFFreqOffset()
#define IFFREQ_ZERO_OFFSET		0
#define IFFREQ_8K_OFFSET		1
#define IFFREQ_4K_OFFSET		2
#define IFFREQ_POSITIVE_1_7K_OFFSET	3
#define IFFREQ_NEGATIVE_1_7K_OFFSET	4
#define IFFREQ_POSITIVE_3_4K_OFFSET	5
#define IFFREQ_NEGATIVE_3_4K_OFFSET	6
#define IFFREQ_RESET_FROM_AFCPHASE	7 /// Read AFC_PHASE, write to AFC_PHASE_INIT

/// Index for SetSpecialAFC()
#define SAFC_SET			0
#define SAFC_RESUME			1

#endif
#endif
