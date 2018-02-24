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

#ifndef __COFDM_DEMODULATOR_H__
#define __COFDM_DEMODULATOR_H__

#include "debug.h"
#include "Tuner.h"
#include "msAPI_Global.h"

typedef enum
{
    E_SERIAL_INTERFACE,
    E_PARALLEL_INTERFACE
} TS_INTERFACE;

#include "msAPI_Demod.h"

#if 0
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
#include "MSB1200.h"
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
#include "MSB1210.h"
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD)
#include "lgs_8g13.h"
#elif(FRONTEND_DEMOD_TYPE ==LEGEND_8G42_DEMOD )
#include"LGS_8G42.h"
#elif(FRONTEND_DEMOD_TYPE ==LEGEND_8G52_DEMOD )
#include"LGS_8G52.h"
#elif(FRONTEND_DEMOD_TYPE ==LEGEND_8G75_DEMOD )
#include"LGS_8G75.h"
#elif(FRONTEND_DEMOD_TYPE ==LEGEND_8G80_DEMOD )
#include"LGS_8G80.h"
#elif(FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
#include"LGS_9X.h"
#include "INTERN_DVBT.h"
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
#include "device_demodulator_msb1400.h"
#include "INTERN_DVBT.h"  //For VIF init usage, only mailbox function 20100601EL
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
#include "M88DC2800.h"
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
#include "M88DD2000.h"
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
 #if USE_UTOPIA
    typedef enum
    {
        COFDM_FEC_LOCK,
        COFDM_PSYNC_LOCK,
        COFDM_TPS_LOCK,
        COFDM_DCR_LOCK,
        COFDM_AGC_LOCK,
        COFDM_MODE_DET,
        COFDM_TPS_EVER_LOCK,
        COFDM_NO_CHANNEL,
        COFDM_NO_CHANNEL_IFAGC,
        COFDM_ATV_DETECT,
        COFDM_BER_LOCK,
        COFDM_SNR_LOCK,
        COFDM_TR_LOCK,
    } COFDM_LOCK_STATUS;
#include "drvDMD_INTERN_DVBT.h"
#else
#include "INTERN_DVBT.h"
#endif

#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    #include "INTERN_ISDBT.h"

#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    #include "EXTERN_DTMB.h"

#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    #include "INTERN_DTMB.h"

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    #include "msb124x.h"
typedef enum
{
    /// lock
    COFDM_FEC_LOCK,
    /// is checking
    COFDM_TPS_LOCK,
    /// after checking
    COFDM_DEMOD_CHECKEND,
    /// unlock
    COFDM_DEMOD_UNLOCK,
    /// NULL state
    COFDM_DEMOD_NULL,
} COFDM_LOCK_STATUS;

#elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
      ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    #include "EXTERN_DTMB.h"

#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_883X)
    #include "atbm883x.h"

#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_884X)
    #include "atbm884x.h"
    #include "INTERN_DVBT.h"  //For VIF init usage, only mailbox function 20100601EL

typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
    COFDM_TPS_EVER_LOCK,
    COFDM_NO_CHANNEL,
    COFDM_NO_CHANNEL_IFAGC,
    COFDM_ATV_DETECT,
    COFDM_BER_LOCK,
    COFDM_SNR_LOCK,
    COFDM_TR_LOCK,
} COFDM_LOCK_STATUS;
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_885X)
#include "atbm885x.h"
typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
    COFDM_TPS_EVER_LOCK,
    COFDM_NO_CHANNEL,
    COFDM_NO_CHANNEL_IFAGC,
    COFDM_ATV_DETECT,
    COFDM_BER_LOCK,
    COFDM_SNR_LOCK,
    COFDM_TR_LOCK,
} COFDM_LOCK_STATUS;
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_886X)
#include "atbm886x.h"
typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
} COFDM_LOCK_STATUS;
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_887X)
#include "atbm887x.h"
typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
} COFDM_LOCK_STATUS;
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_888X)
#include "atbm888x.h"
typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
} COFDM_LOCK_STATUS;
#else
typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
    COFDM_TPS_EVER_LOCK,
    COFDM_NO_CHANNEL,
    COFDM_NO_CHANNEL_IFAGC,
    COFDM_ATV_DETECT,
    COFDM_BER_LOCK,
    COFDM_SNR_LOCK,
    COFDM_TR_LOCK,
} COFDM_LOCK_STATUS;
#endif
#else

typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_ICFO_CH_EXIST_FLAG,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
    COFDM_TPS_EVER_LOCK,
    COFDM_NO_CHANNEL,
    COFDM_NO_CHANNEL_IFAGC,
    COFDM_ATV_DETECT,
    COFDM_BER_LOCK,
    COFDM_SNR_LOCK,
    COFDM_TR_LOCK,
    COFDM_FSATRACK_LOCK,
} COFDM_LOCK_STATUS;

  #if ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
      ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    #include "EXTERN_DTMB.h"
  #endif

  #if(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    #include "INTERN_DTMB.h"
  #endif

 #if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
  #if DEMOD_DVBT_USE_UTOPIA
    #include "drvDMD_INTERN_DVBT.h"
  #else
    #include "INTERN_DVBT.h"
  #endif
 #endif

  #if (  FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT   \
      || FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT   \
      || FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBT)
    #include "msb124x.h"
  #endif

  #if (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X)
    #include "atbm886x.h"
  #endif

  #if (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    #include "INTERN_ISDBT.h"
  #endif

  #if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    #include "./EXTERN_ISDBT/EXTERN_ISDBT.h"
  #endif

#endif
//******************************************************************************
// Functions prototype
//******************************************************************************

//void devCOFDM_Init(void);
//void devCOFDM_ControlPowerOnOff(BOOLEAN bPowerOn);
FUNCTION_RESULT devCOFDM_PowerSave(void);
void devCOFDM_SetFreqStep(FREQSTEP eFreqStep);
void devCOFDM_SetFrequency(DWORD dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID);
BOOLEAN devCOFDM_GetLockStatus(COFDM_LOCK_STATUS eStatus);
BYTE devCOFDM_GetSignalToNoiseRatio(void);
void devCOFDM_PassThroughI2C(BOOLEAN bEnable);
BOOLEAN devCOFDM_PassThroughI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
BOOLEAN devCOFDM_PassThroughI2C_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
void devCOFDM_SwitchTransportSteamInferface(TS_INTERFACE interface);

#if DTV_SCAN_AUTO_FINE_TUNE_ENABLE
BOOLEAN devCOFDM_GetFrequencyOffset(float *pFreqOff, RF_CHANNEL_BANDWIDTH u8BW);
#endif
FUNCTION_RESULT devCOFDM_GetSignal_Vit( DWORD *vit );
//FUNCTION_RESULT devCOFDM_GetSignalStrength(WORD *strength);
BOOLEAN devCOFDM_Get_CELL_ID(WORD *wCell_id);
FUNCTION_RESULT devCOFDM_GetSignalQuality(WORD *quality);
BOOLEAN devCOFDM_GetBER(float *ber);
BOOLEAN devCOFDM_Get_Modul_Mode(WORD *Modul_Mode);
BOOLEAN devCOFDM_Is_Hierarchy_On(void);
void devCOFDM_TunerProgramming(U8 *cTunerData);
//MS_BOOL devCOFDM_GetCurrentPlpID(MS_U8 *pu8PlpID);


#if (ENABLE_DVBT ||ENABLE_ISDBT)
U16 devCOFDM_ReadReg(U16 RegAddr);
BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData);
U16 devCOFDM_DVBT_ReadReg(U16 RegAddr);
BOOLEAN devCOFDM_DVBT_WriteReg(U16 RegAddr, U16 RegData);
#endif


MS_U16 devCOFDM_GetPacketError(void);

//void MDrv_Tuner_Init(void);

#if (ENABLE_S2)
//BOOLEAN devCOFDM_SetCurrentDemodulatorType(EN_DEVICE_DEMOD_TYPE enDemodType);
U16 devCOFDM_ReadReg(U16 RegAddr);
BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData);
MS_U16 _MApp_getCurRFSignalSNR(void);
#endif

#endif // __COFDM_DEMODULATOR_H__


