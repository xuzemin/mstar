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
*						(c) copyright 2007,legendsilicon,beijing,China
*
*						         All Rights Reserved
*
*
* File Name			: LGS_8G75.h
*
* Programmer(s)			: wangying
*
* Date Created			: 2008.05.21
*
* Date Updated			:
*
* Current Revision		: v2.2.11
*
* Modification History	:
*
* Description			:
*
***************************************************************************************/
#ifndef _LGS_8G75_H_
#define _LGS_8G75_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "LGS_TYPES.h"

typedef enum
{
    COFDM_FEC_LOCK
} COFDM_LOCK_STATUS;

#define  LGS8G75_SEC1_ADDR       0x32
#define  LGS8G75_SEC2_ADDR       0x36

LGS_RESULT LGS8G75_WriteRegister(UINT8 regAddr, UINT8 regVal);
LGS_RESULT LGS8G75_ReadRegister(UINT8 regAddr, UINT8 *pregVal);

LGS_RESULT LGS8G75_ComputeSectionAddress(UINT8 regAddr, UINT8 *psecAddr);

LGS_RESULT LGS8G75_SoftReset(void);

LGS_RESULT LGS8G75_SelectADMode(UINT8 extAd);
/******************************************************************************
*clkFree		0	MPEG_CLK is internally gated by MPEG_VALID(default)
*				1	MPEG_CLK is free running
*
*clkPolInvd		0	MPRG output clock(pin 2) normal
*				1	MPEG output clock(pin 2) inverted(default)(for parallel video)
*
*serial			0	Parallel output of MPEG-2 data enabled(default)
*				1	Serial output of MPEG-2 data enabled(on D7 the MSB)
******************************************************************************/
LGS_RESULT LGS8G75_SetMpegMode(UINT8 clkFree, UINT8 clkPolInvd, UINT8 serial);

LGS_RESULT LGS8G75_SetManualParameters(UINT8 datax);

LGS_RESULT LGS8G75_CheckLocked(UINT8 *result);

LGS_RESULT LGS8G75_SetManualMode(void);

LGS_RESULT LGS8G75_AutoDetect(void);

LGS_RESULT LGS8G75_SetAutoMode(void);

/******************************************************************************
*canTuner		0	Silican tuner
*				1	Can tuner, IF is 36MHz
*				2	Can tuner, IF is 36.125MHz
*				3	Can tuner, IF is 36.167MHz
******************************************************************************/
LGS_RESULT LGS8G75_SelectTunerType(UINT8 canTuner);

LGS_RESULT LGS8G75_WaitForLock( UINT8 reg, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *real_times);

/******************************************************************************
*is30400K		0	60.8MHz
*				1	30.4MHz
******************************************************************************/
LGS_RESULT LGS8G75_SelectXOFrequency(UINT8 is30400K);

LGS_RESULT LGS_OpenTunerI2C(UINT8 tunerAddress);
LGS_RESULT LGS_CloseTunerI2C(void);
/******************************************************************************
*singleCarrier	0	multe carrier
*				1	single carrier
******************************************************************************/
LGS_RESULT LGS8G75_SetCarrierMode(UINT8 singleCarrier);

LGS_RESULT LGS8G75_Init(void);

LGS_RESULT LGS8G75_GetParameters(DEMOD_PARAMETERS *pPara);

LGS_RESULT LGS8G75_SetParameters(DEMOD_PARAMETERS *pPara);

#ifdef __cplusplus
}
#endif

#endif
