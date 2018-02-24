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
*                        (c) copyright 2007,legendsilicon,beijing,China
*
*                                 All Rights Reserved
*
*
* File Name            : LGS8942.h
*
* Programmer(s)            : wangying
*
* Date Created            : 2007.07.24
*
* Date Updated            :
*
* Current Revision        : V1.0.0
*
* Modification History    :
*
* Description            :
*
***************************************************************************************/

/***************************************************************************************
*                                  INCLUDE FILES
***************************************************************************************/
#include "Board.h"
#ifdef CUS_HSS
#include "LGS_8G52_HSS.h"
#else

#ifndef _LGS_8g52_H
#define _LGS_8g52_H

#include "GPIO.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "datatype.h"
//#include "SWI2C.h"
#include "drvIIC.h"
//#include "iic.h"
//#include "lgs_types.h"

#define  LGS8g42ADDR       0x32

#define SINGLE_CARRIER     0x01
#define MULTI_CARRIER      0x00

#define BY_PASS_TUNER_I2C    /*如果tuner的I2C总线通过（bypass）demodulator*/

#define INTERNAL_AD       0x00
#define EXTERNAL_AD       0x01

#define LGS_NO_ERROR        0    /**< no error */
#define LGS_REGISTER_ERROR    0xFF    /**< register error  */
#define LGS_I2C_OPEN_ERROR    0xFE    /**< I2C open error */
#define LGS_I2C_READ_ERROR    0xFD    /**< I2C read error */
#define LGS_I2C_WRITE_ERROR    0xFC    /**< I2C write error */
#define LGS_I2C_CLOSE_ERROR    0xFB    /**< I2C close error */
#define LGS_NO_LOCKED        0xFA    /**< not locked */
#define LGS_AUTO_DETECT_FAILED    0xF9    /**< auto detect failed */
#define LGS_FREQUENCY_ERROR    0xF8    /**< frequency error */
#define LGS_PAYLOAD_ERROR    0xF7    /**< compute payload error */
#define LGS_DETECT_ERROR        0xF6
#define LGS_SET_MANUAL_PARAMETERS_ERROR 0xF5
#define LGS_CHANGE_MODE_ERROR    0xF4
#define LGS_SET_IF_ERROR         0xF3
#define LGS_TUNER_LOCK           0xF2
#define LGS_TUNER_NOTLOCK        0xF1
#define COFDM_DEM_I2C_ID            LGS8G13ADDR

//#define true   1
//#define false  0

typedef enum
{
    COFDM_FEC_LOCK
} COFDM_LOCK_STATUS;

/*
typedef INT8 (*LGS_OPEN_I2C)(LGS_HANDLE *phI2c,
                const UINT8 secAddr,
                UINT16 timeout);

typedef INT8 (*LGS_READ_I2C)(LGS_HANDLE hI2c,
                UINT8 *pbuffer,
                UINT16 len,
                UINT16 timeout);

typedef INT8 (*LGS_WRITE_I2C)(LGS_HANDLE hI2c,
                 const UINT8 *pbuffer,
                 UINT16 len,
                 UINT16 timeout);

typedef INT8 (*LGS_CLOSE_I2C)(LGS_HANDLE hI2c);

typedef void (*LGS_WAIT)(UINT16 millisecond);
*/
#define UINT8 unsigned char
#define UINT16 unsigned short
//typedef char               INT8;    /* 8 bit signed integer value */
char LGS_WriteRegister(UINT8 regAddr, UINT8 regVal);
char  LGS_ReadRegister(UINT8 regAddr, UINT8 *pregVal);

void LGS_Wait(U32 delay);

UINT8 LGS_SoftReset(void);

char LGS_SelectADMode(UINT8 mode);

char LGS_SetMpegMode(UINT8 serial, UINT8 clkPolarity, UINT8 clkGated);

UINT8 LGS_SetManualParameters(UINT8 datax);

//char LGS_CheckLocked(UINT8 *result);
char LGS_CheckLocked(void);

UINT8 LGS_SetManualMode(void);

UINT8 LGS_AutoDetect(void);

UINT8 LGS_SetAutoMode(void);


char LGS_ComputeTunerRegister(UINT16 frequency,
                  UINT8 *ppd1,
                  UINT8 *ppd2,
                  UINT8 *pcb1,
                  UINT8 *pcb2,
                  UINT8 *pcb3a,
                  UINT8 *pcb3b) ;

UINT8 LGS_OpenTunerI2C(UINT8 tunerAddress);
UINT8 LGS_CloseTunerI2C(void);
char LGS_StartTuner(UINT16 frequency);


UINT8 WaitForLock( UINT8 reg, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *real_times);
UINT8 LGS_SetCarrierMode(UINT8 mode);  //add by dyx 20080102

char LGS8G52_SelectADMode(UINT8 extAd);
UINT8 LGS8G52_SetAutoMode(void);
UINT8 LGS8G52_AutoDetect(void);
char  LGS8G52_Init(void);
UINT8 LGS8G52_ReadType(void);
UINT8 LGS8G52_ReadCarrier(void);
UINT8 LGS8G52_ReadIntension(void);
UINT8 LGS8G52_ReadMastick(void);
BOOLEAN  CheckSignalCarrire(void);
BOOLEAN Set_CheckSignalCarrire(void);
UINT8 LGS8G52_ReadMode(void);
UINT8 LGS8G52_ReadPN(void);
UINT8 LGS8G52_ReadPNFLIP(void);
UINT8 LGS8G52_SetMode(U8 datax);
UINT8 LGS8G52_SetPN(U8 datax);
UINT8 LGS8G52_SetPNFLIP(U8 datax);
#endif
#endif
