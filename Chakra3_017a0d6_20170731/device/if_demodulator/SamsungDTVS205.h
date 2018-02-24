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
#ifndef _SAMSUNGDTVS205_H_
#define _SAMSUNGDTVS205_H_

/* ------------------------------------
    Header Files
   ------------------------------------ */

#include "Board.h"
#include "datatype.h"

/* ------------------------------------
    Macro Definitions
   ------------------------------------ */

#ifdef _SAMSUNGDTVS205_C_
#define INTERFACE
#else
#define INTERFACE  extern
#endif

typedef enum
{
    Samsung_ERR_NO = 0,
    Samsung_ERR_I2C = 1,
    Samsung_ERR_INIT = 2,
    Samsung_ERR_UNLOCK = 4,
    Samsung_ERR_PARAM = 8,
    /* Invalid parameter check                */
    Samsung_ERR_CHECK_FUNC = 16,
    /* Error returned from LgdtCheck...()    */
    Samsung_ERR_ALTER_FUNC = 32,
    /* Error returned from LgdtAlter...()    */
    Samsung_ERR_SPECTRUM = 64,
    /* Spectrum status symptom shows when QAM mode    */
    Samsung_ERR_OTHER = 128,
    Samsung_ERR_TUNER = 256,
    /* Reserved for a tuner manufacturer    */
    Samsung_ERR_SCAN = 512
}SamsungReturn_t;

typedef enum
{
    Samsung_SIGNAL_NO            = 0,    /* little or no input power detected    */
    Samsung_SIGNAL_WEAK        = 1,    /* some power detected.                    */
    Samsung_SIGNAL_MODERATE    = 2,    /* lock achieved, SNR < 15 dB (approx)    */
    Samsung_SIGNAL_STRONG        = 4,    /* lock achieved, SNR < 24 dB (approx)    */
    Samsung_SIGNAL_VERY_STRONG    = 8        /* lock achieved, SNR > 24 dB (approx)    */
}SamsungSignalCondition_t;

/*------------------------------------------------------//
// TYPE Definition of MPEG Mode
//------------------------------------------------------*/
typedef enum
{
    Samsung_PARAL = 0x00,
    /* Samsung_PARAL Mode                    */
    Samsung_SERIAL = 0x01                /* Samsung_SERIAL Mode                        */
}SamsungMpegMode_t;

typedef struct
{
    U8 Reg;
    U16 Value;
} SamsungChipInit_t;

INTERFACE BOOLEAN SamsungS5H1409_Init(void);
INTERFACE SamsungReturn_t SamsungS5H1409AlterMpegMode(SamsungMpegMode_t mode);
INTERFACE BOOLEAN SamsungS5H1409_MpegClk_InvertedSet(void);
INTERFACE BOOLEAN SamsungS5H1409_MpegClk_Non_InvertedSet(void);
INTERFACE BOOLEAN SamsungS5H1409xRepeaterEnable(void);
INTERFACE BOOLEAN SamsungS5H1409xRepeaterDisable(void);
INTERFACE BOOLEAN SamsungS5H1409xCheckIsSleep(void);
INTERFACE BOOLEAN SamsungS5H1409xSleepOn(void);
INTERFACE BOOLEAN SamsungS5H1409xSleepOff(void);
INTERFACE BOOLEAN SamsungS5H1409_SoftReset(void);
INTERFACE BOOLEAN SamsungS5H1409VsbMode(void);
INTERFACE BOOLEAN SamsungS5H1409x64QamMode(void);
INTERFACE BOOLEAN SamsungS5H1409x256QamMode(void);
INTERFACE void SamsungS5H1409_Interleave_Parallel_ModeSet(void);
INTERFACE void SamsungS5H1409_Interleave_Serial_ModeSet(void);
INTERFACE void SamsungS5H1409AMHUM_SetDriver(void);
INTERFACE BOOLEAN SamsungS5H1409xVSBScanInit(void);
INTERFACE BOOLEAN SamsungS5H1409xVSBScanEnd(void);
INTERFACE BOOLEAN SamsungS5H1409xVsb_Sync_Lock(void);
INTERFACE BOOLEAN SamsungS5H1409xQAM_IsAGC_Lock(void);
INTERFACE BOOLEAN SamsungS5H1409xVsb_QAM_Master_Lock(void);
INTERFACE BOOLEAN SamsungS5H1409xVsb_FEC_Lock(void);
INTERFACE void SamsungS5H1409xCheckSignalCondition(SamsungSignalCondition_t* pstatus);
INTERFACE BOOLEAN SamsungS5H1409xQAMCheckLock(void);
INTERFACE BOOLEAN SamsungS5H1409xAGCCheckLock(void);
INTERFACE double SamsungS5H1409xVsbSnrResultCheck ( void );
INTERFACE double SamsungS5H1409xQamSnrResultCheck ( void );
#undef INTERFACE

#endif

