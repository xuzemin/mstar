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

#include "MsCommon.h"
#include "MsOS.h"
#include "Board.h"
#include "Tuner.h"
#include "msAPI_DTVSystem.h"
#include "drvIIC.h"
#include "drvDemod.h"
#include "apiDTVSatTable.h"

#ifndef device_demodulator_msb131x_I2b28dd03m121c8cf959bmm7254_H
    #define device_demodulator_msb131x_I2b28dd03m121c8cf959bmm7254_H

#if 1

//#define INTERFACE extern

#define MAPI_U8 MS_U8
#define MAPI_U16 MS_U16
#define MAPI_U32 MS_U32
#define MAPI_BOOL MS_BOOL
#define MAPI_S16 MS_S16

#define MAPI_TRUE TRUE
#define MAPI_FALSE FALSE

/* move to msAPI_Demod.h
typedef enum
{
    E_DEVICE_DEMOD_ATV = 0,
    E_DEVICE_DEMOD_DVB_T,
    E_DEVICE_DEMOD_DVB_C,
    E_DEVICE_DEMOD_DVB_S,
    E_DEVICE_DEMOD_DTMB,
    E_DEVICE_DEMOD_ATSC,
    E_DEVICE_DEMOD_ATSC_VSB,
    E_DEVICE_DEMOD_ATSC_QPSK,
    E_DEVICE_DEMOD_ATSC_16QAM,
    E_DEVICE_DEMOD_ATSC_64QAM,
    E_DEVICE_DEMOD_ATSC_256QAM,
    E_DEVICE_DEMOD_DVB_T2,
    E_DEVICE_DEMOD_ISDB,
    E_DEVICE_DEMOD_MAX,
    E_DEVICE_DEMOD_NULL = E_DEVICE_DEMOD_MAX,
} EN_DEVICE_DEMOD_TYPE; */

/// Define blind scan status of DVBS
typedef enum
{
    E_BLINDSCAN_NOTREADY,                                                ///blind scan : not ready
    E_BLINDSCAN_INIT_FAILED,                                             ///blind scan : init failed
    E_BLINDSCAN_INIT_OK,                                                 ///blind scan : init ok
    E_BLINDSCAN_SCANFREQ_START_FAILED,                                   ///blind scan : scan freq start failed
    E_BLINDSCAN_SCANFREQ_SCANNING,                                       ///blind scan : scan freq scanning
    E_BLINDSCAN_SCANFREQ_COMPLETE,                                       ///blind scan : scan freq complete
    E_BLINDSCAN_ALLFREQ_COMPLETE,                                        ///blind scan : scan all freq complete
    E_BLINDSCAN_UNKNOWN                                                  ///blind scan : unknown
} EN_BLINDSCAN_STATUS;

#if 0
/// Define DVB-S modulatiopn scheme
typedef enum
{
    DEMOD_SAT_DVBS2,                                                          ///< DVBS2
    DEMOD_SAT_DVBS                                                            ///< DVBS
} DEMOD_EN_SAT_MOD_TYPE;

typedef struct
{
        MAPI_BOOL                           bLNBPowerOn;                                              ///< Power On/Off
        MAPI_BOOL                           b22kOn;                                                           ///< LNB 22k On/Off
        MAPI_BOOL                           bLNBOutLow;                                                   ///< LNB 13/18V

} DEMOD_MS_FE_CARRIER_DISEQC;

/// Define converlution code rate for DVB-T and DVB-S
typedef enum
{
    DEMOD_CONV_CODE_RATE_1_2,                                                 ///< Code rate = 1/2
    DEMOD_CONV_CODE_RATE_1_3,                                                 ///< Code rate = 1/3
    DEMOD_CONV_CODE_RATE_2_3,                                                 ///< Code rate = 2/3
    DEMOD_CONV_CODE_RATE_1_4,                                                 ///< Code rate = 1/4
    DEMOD_CONV_CODE_RATE_3_4,                                                 ///< Code rate = 3/4
    DEMOD_CONV_CODE_RATE_2_5,                                                 ///< Code rate = 2/5
    DEMOD_CONV_CODE_RATE_3_5,                                                 ///< Code rate = 3/5
    DEMOD_CONV_CODE_RATE_4_5,                                                 ///< Code rate = 4/5
    DEMOD_CONV_CODE_RATE_5_6,                                                 ///< Code rate = 5/6
    DEMOD_CONV_CODE_RATE_7_8,                                                 ///< Code rate = 7/8
    DEMOD_CONV_CODE_RATE_8_9,                                                 ///< Code rate = 8/9
    DEMOD_CONV_CODE_RATE_9_10                                                 ///< Code rate = 9/10

} DEMOD_EN_CONV_CODE_RATE_TYPE;

/// Define terrestrial band width
typedef enum
{
    DEMOD_BW_MODE_6MHZ = 0,                                                   ///< 6 MHz
    DEMOD_BW_MODE_7MHZ,                                                       ///< 7 MHz
    DEMOD_BW_MODE_8MHZ                                                        ///< 8 MHz
} DEMOD_EN_TER_BW_MODE;

/// Define terrestrial constellation type
typedef enum
{
    DEMOD_TER_QPSK,                                                           ///< QPSK type
    DEMOD_TER_QAM16,                                                          ///< QAM 16 type
    DEMOD_TER_QAM64                                                           ///< QAM 64 type
} DEMOD_EN_TER_CONSTEL_TYPE;

/// Define terrestrial hierarchy information
typedef enum
{
    DEMOD_TER_HIE_NONE,                                                       ///< Non-hierarchy
    DEMOD_TER_HIE_ALPHA_1,                                                    ///< Hierarchy alpha = 1
    DEMOD_TER_HIE_ALPHA_2,                                                    ///< Hierarchy alpha = 2
    DEMOD_TER_HIE_ALPHA_4                                                     ///< Hierarchy alpha = 4
} DEMOD_EN_TER_HIE_TYPE;

/// Define terrestrial guard interval
typedef enum
{
    DEMOD_TER_GI_1_32,                                                        ///< Guard interval value = 1/32
    DEMOD_TER_GI_1_16,                                                        ///< Guard interval value = 1/16
    DEMOD_TER_GI_1_8,                                                         ///< Guard interval value = 1/8
    DEMOD_TER_GI_1_4                                                          ///< Guard interval value = 1/4
} DEMOD_EN_TER_GI_TYPE;

/// Define terrestrial transmission mode
typedef enum
{
    DEMOD_TER_FFT_2K,                                                         ///< 2k FFT mode
    DEMOD_TER_FFT_8K                                                          ///< 8k FFT mode
} DEMOD_EN_TER_FFT_MODE;

/// Define terrestrial transmission mode
typedef enum
{
    DEMOD_TER_HP_SEL,                                                         ///< High priority level selection
    DEMOD_TER_LP_SEL                                                          ///< Low priority level selection
} DEMOD_EN_TER_LEVEL_SEL;

/// Define DVB-C modulation scheme
typedef enum
{
    DEMOD_CAB_QAM16,                                                          ///< QAM 16
    DEMOD_CAB_QAM32,                                                          ///< QAM 32
    DEMOD_CAB_QAM64,                                                          ///< QAM 64
    DEMOD_CAB_QAM128,                                                         ///< QAM 128
    DEMOD_CAB_QAM256
} DEMOD_EN_CAB_CONSTEL_TYPE;

/// Define DVB-S IQ tuning mode
typedef enum
{
    DEMOD_CAB_IQ_NORMAL,                                                      ///< Normal
    DEMOD_CAB_IQ_INVERT                                                       ///< Inverse
} DEMOD_EN_CAB_IQ_MODE;

typedef enum
{
    DEMOD_SAT_QPSK,                                                           ///< QPSK
    DEMOD_SAT_8PSK,                                                           ///< 8PSK
    DEMOD_SAT_16APSK,                                                           ///< 16APSK
    DEMOD_SAT_32APSK                                                           ///< 32APSK
} DEMOD_EN_SAT_CONSTEL_TYPE;

/// Define DVB-S Roll-Off factor
typedef enum
{
    DEMOD_SAT_RO_35,                                                          ///< roll-off factor = 0.35
    DEMOD_SAT_RO_25,                                                          ///< roll-off factor = 0.25
    DEMOD_SAT_RO_20                                                           ///< roll-off factor = 0.20
} DEMOD_EN_SAT_ROLL_OFF_TYPE;

/// Define DVB-S IQ tuning mode
typedef enum
{
    DEMOD_SAT_IQ_NORMAL,                                                      ///< Normal
    DEMOD_SAT_IQ_INVERSE                                                      ///< Inverse
} DEMOD_EN_SAT_IQ_MODE;

/// Define Bit Error Rate range measure from signal
typedef enum
{
    DEMOD_BIT_ERR_RATIO_LOW ,                                                 ///< Low BER
    DEMOD_BIT_ERR_RATIO_MEDIUM ,                                              ///< Medium BER
    DEMOD_BIT_ERR_RATIO_HIGH                                                  ///< High BER
} DEMOD_EN_BIT_ERR_RATIO;

/// Define lock status of front end
typedef enum
{
    DEMOD_FE_UNLOCKED = 0,                                                    ///< Frontend is unlocked
    DEMOD_FE_LOCKED                                                           ///< Frontend is locked
} DEMOD_EN_FE_LOCK_STATUS;


/// Define tuning mode
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef enum
{
    DEMOD_FE_TUNE_MANUAL,                                                     ///< Manual tuning to carrier
    DEMOD_FE_TUNE_AUTO,                                                       ///< Auto tuning to carrier
} DEMOD_EN_FE_TUNE_MODE;

/// Define output mode
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef enum
{
    DEMOD_INTERFACE_SERIAL = 0,                                                   ///< Serial interface
    DEMOD_INTERFACE_PARALLEL                                                  ///< Parallel interface
} DEMOD_INTERFACE_MODE;

/// Define tuning paramter of DVB-T front-end
typedef struct
{
    DEMOD_EN_TER_BW_MODE                  eBandWidth;                         ///< Band width
    DEMOD_EN_TER_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    DEMOD_EN_TER_HIE_TYPE                 eHierarchy;                         ///< Hierarchy
    DEMOD_EN_TER_GI_TYPE                  eGuardInterval;                     ///< Guard interval
    DEMOD_EN_TER_FFT_MODE                 eFFT_Mode;                          ///< Transmission mode
    DEMOD_EN_CONV_CODE_RATE_TYPE          eHPCodeRate;                        ///< HP code rate
    DEMOD_EN_CONV_CODE_RATE_TYPE          eLPCodeRate;                        ///< LP code rate
    DEMOD_EN_TER_LEVEL_SEL                eLevelSel;                          ///< Select HP or LP level
} DEMOD_MS_TER_CARRIER_PARAM;

/// Define tuning paramter of DVB-C front-end
typedef struct
{
    DEMOD_EN_CAB_CONSTEL_TYPE           eConstellation;                     ///< Constellation type
    MAPI_U16                          u16SymbolRate;                      ///< Symbol rate (Ksym/sec)

    DEMOD_EN_CAB_IQ_MODE                eIQMode;                            ///< IQ Mode
    MAPI_U8                           u8TapAssign;                        ///< Tap assign
    MAPI_U32                          u32FreqOffset;                      ///< Carrier frequency offset
    MAPI_U8                           u8TuneFreqOffset;                       ///< Requeset tuner freq offset
} DEMOD_MS_CAB_CARRIER_PARAM;

/// Define tuning paramter of DVB-S front-end
typedef struct
{
    DEMOD_EN_SAT_MOD_TYPE                   eDemod_Type;                        ///< Mode type
    DEMOD_EN_SAT_CONSTEL_TYPE               eConstellation;                     ///< Constellation type
    DEMOD_EN_SAT_ROLL_OFF_TYPE              eRollOff;                           ///< Roll-Off factor
    DEMOD_EN_SAT_IQ_MODE                    eIQ_Mode;                           ///< IQ mode
    DEMOD_EN_CONV_CODE_RATE_TYPE            eCodeRate;                          ///< Converlution code rate
    MAPI_U32                                u32SymbolRate;
    MAPI_U8                                 u8Polarity;                         // 0: Horizon; > 0(default 1): Vertical;
    MAPI_S16                                s16FreqOffset;

} DEMOD_MS_SAT_CARRIER_PARAM;

/// Define carrier paramter of digital tuner
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef struct
{
    MAPI_U32                          u32Frequency;
    union
    {
        DEMOD_MS_TER_CARRIER_PARAM        TerParam;                           ///< Paramters for DVB-T front-end
        DEMOD_MS_CAB_CARRIER_PARAM        CabParam;                           ///< Paramters for DVB-C front-end
        DEMOD_MS_SAT_CARRIER_PARAM        SatParam;                           ///< Paramters for DVB-S front-end
    };
} DEMOD_MS_FE_CARRIER_PARAM;

/// Define the quality report
typedef struct
{
    DEMOD_EN_FE_LOCK_STATUS                 eLock;                              ///< Lock
    DEMOD_EN_BIT_ERR_RATIO                  eBER;                               ///< Bit error rate
    float                                 	fSNR;                              ///< SNR
    float                                   fSignalLevel;                       ///< Signal Level=1~100
    MAPI_U16                                u16SignalStrength;                  ///< Signal Strength[dBm],mick
    MAPI_U8                                 u8SignalQuality;                    ///< Signal Quality,mick
    float                                   fPreBER;                            ///< xxE-xx,mick
    float                                   fPostBerTSBER;
    MAPI_U32                                u32LockTime;                        ///< LockTime
    MAPI_U16                                u16TSpacketError;                   ///< TS Packet Error
} DEMOD_MS_FE_CARRIER_STATUS;


/// Define the carrier information
typedef struct
{
    DEMOD_MS_FE_CARRIER_PARAM             Param;                              ///< Carrier parameter
    DEMOD_MS_FE_CARRIER_STATUS            Status;                             ///< Quality report
    DEMOD_MS_FE_CARRIER_DISEQC            DiSEqCp;                                                      ///< DiSEqC
} DEMOD_MS_FE_CARRIER_INFO;

typedef struct
{
    // Demodulator option
    MAPI_BOOL                         bX4CFE_en;                          ///< Carrier frequency estimation
    MAPI_BOOL                         bPPD_en;                            ///< Tap assign estimation
    MAPI_BOOL                         bIQAutoSwap_en;                     ///< IQ mode auto swap
    MAPI_BOOL                         bQAMScan_en;                        ///< QAM type auto scan
    MAPI_BOOL                         bFHO_en;                            ///< FHO
    MAPI_BOOL                         (*fptTunerSet)(MAPI_U32);             ///< Tuner set freq function pointer
} Demod_Mode;

typedef enum
{
    /// lock
    E_DEMOD_LOCK,
    /// is checking
    E_DEMOD_CHECKING,
    /// after checking
    E_DEMOD_CHECKEND,
    /// unlock
    E_DEMOD_UNLOCK,
    /// NULL state
    E_DEMOD_NULL,
} EN_LOCK_STATUS;

#endif

/// the signal strength
/* move to msAPI_Demod.h
typedef enum
{
    /// no signal
    E_FE_SIGNAL_NO = 0,
    /// weak signal
    E_FE_SIGNAL_WEAK,
    /// moderate signal
    E_FE_SIGNAL_MODERATE,
    /// strong signal
    E_FE_SIGNAL_STRONG,
    /// very strong signal
    E_FE_SIGNAL_VERY_STRONG,
} EN_FRONTEND_SIGNAL_CONDITION; */



///TONE BUREST TYPE
typedef enum
{
    E_TONE0,                            ///  TYPE: TONE0
    E_TONE1,                            ///  TYPE: TONE1
} EN_SAT_TONEBUREST_TYPE;

///LNB POWER TYPE
typedef enum
{
    E_LNB_POWER_OFF,                    ///  POWER OFF
    E_LNB_POWER_13V,                    ///  POWER 13V
    E_LNB_POWER_14V,                    ///  POWER 14V
    E_LNB_POWER_18V,                    ///  POWER 18V
    E_LNB_POWER_19V,                    ///  POWER 19V
} EN_SAT_LNBPOWER_TYPE;


#if 1
#define MDrv_msb1245_IIC_Write    				MDrv_IIC_Write
#define MDrv_msb1245_IIC_Read     				MDrv_IIC_Read
#define MDrv_IIC_Write(u16SlaveID, pu8Addr, u8AddrSize, pu8Buf, u16BufSize) MDrv_IIC_WriteBytes(u16SlaveID, u8AddrSize, pu8Addr, u16BufSize, pu8Buf)
#define MDrv_IIC_Read(u16SlaveID, pu8Addr, u8DevId, buf, count) MDrv_IIC_ReadBytes(u16SlaveID, 0, NULL, count, buf)
#define IIC_WRITE             		MDrv_IIC_Write
#define IIC_Read					MDrv_IIC_Read
#define IIC_DEVICEID                0
#define MDrv_msb1245_IIC_Write_300K    		    MDrv_msb1245_IIC_Write
#define MDrv_msb1245_IIC_Read_300K              MDrv_msb1245_IIC_Read
#endif

void MSB1245_GPIO_PowerOn(void);
void MSB1245_GPIO_PowerOff(void);
void MApi_MSB1245_Demod_HWReset(void);
MAPI_BOOL Power_On_Initialization(void);
MAPI_BOOL Demod_MSB1245_Connect(EN_DEVICE_DEMOD_TYPE enDemodType);

//MAPI_BOOL MDrv_Demod_Restart(DEMOD_MS_FE_CARRIER_PARAM* pParam);
MAPI_BOOL MDrv_CofdmDmd_SetTsSerial(MAPI_BOOL bSerial);
MAPI_BOOL MDrv_CofdmDmd_GetRollOff(MAPI_U8 *pRollOff);
MAPI_BOOL MDrv_CofdmDmd_GetRFOffset(MS_S16 *ps16RFOff);

MAPI_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MAPI_U32 *u16CurrentFeq);
// INTERFACE MAPI_BOOL MSB123x_DJB_RST(void);



MAPI_BOOL MDrv_CofdmDmd_SetTsSerial(MAPI_BOOL bSerial);
MAPI_BOOL MDrv_CofdmDmd_TPSGetLock(MAPI_BOOL *pbLock);
MAPI_BOOL MDrv_CofdmDmd_MPEGGetLock(MAPI_BOOL *pbLock);
MAPI_BOOL MDrv_CofdmDmd_GetRollOff(MAPI_U8 *pRollOff);
MAPI_BOOL MDrv_CofdmDmd_GetRFOffset(MAPI_S16 *ps16RFOff);
MAPI_BOOL MDrv_CofdmDmd_BlindScan_Start(MS_U16 u16StartFreq,MS_U16 u16EndFreq,MS_BOOL bUCMode);
MAPI_BOOL MDrv_CofdmDmd_BlindScan_NextFreq(MAPI_BOOL* bBlindScanEnd , MS_U8* u8Progress);
MAPI_BOOL MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(MAPI_U8* u8Progress,MAPI_U8 *u8FindNum);
MAPI_BOOL MDrv_CofdmDmd_BlindScan_Cancel(void);
MAPI_BOOL MDrv_CofdmDmd_BlindScan_End(void);
MAPI_BOOL MDrv_CofdmDmd_BlindScan_GetChannel(MAPI_U16 u16ReadStart,MAPI_U16* u16TPNum,DTVPROGRAMID_M *pTable);
MAPI_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MAPI_U32 *u32CurrentFeq);



MAPI_BOOL MDrv_DiSEqC_SetTone(MAPI_BOOL bTone1);
MAPI_BOOL MDrv_DiSEqC_Get22kOnOff(MAPI_BOOL* b22kOn);
MAPI_BOOL MDrv_DiSEqC_SetLNBOut(MAPI_BOOL bLow);
MAPI_BOOL MDrv_DiSEqC_GetLNBOut(MAPI_BOOL* bLNBOutLow);
MAPI_BOOL MDrv_DiSEqC_Set22kOnOff(MAPI_BOOL b22kOn);
MAPI_BOOL MDrv_DiSEqC_Set22kOnOff(MAPI_BOOL b22kOn);
MAPI_BOOL MDrv_DiSEqC_SendCmd(MAPI_U8* pCmd,MAPI_U8 u8CmdSize);

MAPI_BOOL DEMOD_MSB1245_Set_PowerOn(void);
MAPI_BOOL DEMOD_MSB1245_Set_PowerOff(void);
MAPI_BOOL Active(MAPI_BOOL bEnable);

MAPI_BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks);
MAPI_BOOL MDrv_DVBS_Tuner_Initial(void);
MAPI_BOOL MDrv_DVBS_Tuner_CheckLock(void);
MAPI_BOOL ExtendCmd(MAPI_U8 SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void *pvParam3);

//float MDrv_DVBS_Tuner_Get_RSSI(MS_U16);
#if(SUPPORT_UNICABLE)	 // anvi
MAPI_BOOL FrontEnd_DVBS2_Set(MS_U32 u32Frequency, MS_U32 u32SymRate, MS_U8 u8Polarity , MS_SAT_PARAM *stSatInfo);
#endif

MAPI_U16 DTV_GetSignalStrength(void);
MAPI_BOOL MDrv_Demod_GetModulationType(MAPI_U8* u8Constellation);


#endif
#endif

