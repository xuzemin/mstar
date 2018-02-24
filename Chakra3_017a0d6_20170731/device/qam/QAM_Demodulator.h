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
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __QAM_DEMODULATOR_H__
#define __QAM_DEMODULATOR_H__

#include "debug.h"
#include "Tuner.h"
#include "msAPI_Global.h"


typedef enum
{
    E_QAM_SERIAL_INTERFACE,
    E_QAM_PARALLEL_INTERFACE
} QAM_TS_INTERFACE;



#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD))
    #if DEMOD_DVBC_USE_UTOPIA
        #include "drvDMD_INTERN_DVBC.h"
        #if DTV_LOW_IF_FREQ
            #if(FRONTEND_TUNER_TYPE==NXP_TDA18272_TUNER|| FRONTEND_TUNER_TYPE==NUTUNE_FK1602_TUNER || FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
                #define DTV_IF_8M_FREQ  5000L
                #define DTV_IF_7M_FREQ  3500L
                #define DTV_IF_6M_FREQ  3000L
            #else
                #define DTV_IF_8M_FREQ  4000L
                #define DTV_IF_7M_FREQ  3500L
                #define DTV_IF_6M_FREQ  3000L
            #endif
        #else
            #define DTV_IF_8M_FREQ  36167L
        #endif

        /*
        typedef enum
        {
            QAM_FEC_LOCK,
            QAM_PSYNC_LOCK,
            //QAM_TPS_LOCK,
            QAM_NO_CHANNEL, //ADD
            QAM_DCR_LOCK,
            QAM_AGC_LOCK,
            //QAM_MODE_DET,
            QAM_ATV_DETECT, //ADD
            QAM_TR_LOCK, //ADD

        } QAM_LOCK_STATUS;
        */
    #else
        #include "INTERN_DVBC.h"
    #endif

#elif(FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)

    #include "msb124x.h"


#else
    /*
    #if(FRONTEND_DEMOD_TYPE != MSTAR_MSB124X_DVBT)
    typedef enum
    {
        QAM_FEC_LOCK,
        QAM_PSYNC_LOCK,
        //QAM_TPS_LOCK,
        QAM_NO_CHANNEL, //ADD
        QAM_DCR_LOCK,
        QAM_AGC_LOCK,
        //QAM_MODE_DET,
        QAM_ATV_DETECT, //ADD
        QAM_TR_LOCK, //ADD

    } QAM_LOCK_STATUS;
    #endif
    */
#endif


//******************************************************************************
// Functions prototype
//******************************************************************************

void devQAM_Init(void);
void devQAM_ControlPowerOnOff(BOOLEAN bPowerOn);
FUNCTION_RESULT devQAM_PowerSave(void);
void devQAM_SetFreqStep(FREQSTEP eFreqStep);
void devQAM_SetFrequency(DWORD dwFrequency, U8 u8QamMode, U16 u16SymbolRate, BOOLEAN bSpecInv, U8 u8AutoSR, U8 u8AutoQAM);
void devQAM_SetAutoMode(U8 u8AutoSymbolRateFlag, U8 u8AutoQamFlag); //mick
U8 devQAM_GetSymbolRateMode(void);
WORD devQAM_GetCurrentSymbolRate(void); //mick
U8 devQAM_GetCurrentQAM(void);//mick
U16 devQAM_GetSpeedUp(void);//mick

BOOLEAN devQAM_GetLockStatus(QAM_LOCK_STATUS eStatus);
BYTE devQAM_GetSignalToNoiseRatio(void);
void devQAM_PassThroughI2C(BOOLEAN bEnable);
BOOLEAN devQAM_PassThroughI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
BOOLEAN devQAM_PassThroughI2C_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
void devQAM_SwitchTransportSteamInferface(QAM_TS_INTERFACE interface);

#if DTV_SCAN_AUTO_FINE_TUNE_ENABLE
BOOLEAN devQAM_GetFrequencyOffset(float *pFreqOff, RF_CHANNEL_BANDWIDTH u8BW);
BOOLEAN devQAM_SetAfcEnable(BOOLEAN bEnable);
#endif

FUNCTION_RESULT devQAM_GetSignal_Vit( DWORD *vit );
FUNCTION_RESULT devQAM_GetSignalStrength(WORD *strength);
FUNCTION_RESULT devQAM_GetSignalQuality(WORD *quality);
void devQAM_TunerProgramming(U8 *cTunerData);
BOOLEAN devQAM_GetSpecInv(void);

#if ENABLE_DVBC
U16 devQAM_ReadReg(U16 RegAddr);
BOOLEAN devQAM_WriteReg(U16 RegAddr, U16 RegData);
#endif

#endif // __QAM_DEMODULATOR_H__

