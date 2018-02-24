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
#ifndef __DRV_DEMOD_H__
#define __DRV_DEMOD_H__

#include "Board.h"
#ifdef TWIN_TUNER
#include "MsTypes.h"
#include "MsCommon.h"
#include "apiDMX.h"
#endif

//#define MAX_TPSOFSAT            10

#if 0
/// Demodulator tune parameter
typedef struct
{
    // Channel setting
    MS_U32                          u32SymRate;                         ///< Symbol rate (Ksym/sec)
    // Channel characteristic
    DMD_QAMType                     eQamType;                           ///< QAM type
    DMD_IQType                      eIQSwap;                            ///< IQ type
    DMD_TapAssign                   eTapAssign;                         ///< Tap assign
    MS_U32                          u32FreqOffset;                      ///< Carrier frequency offset
    MS_U8                           u8TuneFreqOffset;                   ///< Request Tuner offset
    MS_U32                          u32TunerFreq;                       ///< Request Tuner offset
} DMD_Param;
#endif

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
    DEMOD_BW_MODE_8MHZ,                                                        ///< 8 MHz
    DEMOD_BW_MODE_1_7MHZ                                                      ///< 1.7 MHz
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
    DEMOD_CAB_QAM256,
    DEMOD_CAB_QAMAUTO

} DEMOD_EN_CAB_CONSTEL_TYPE;


/// Define DVB-S IQ tuning mode
typedef enum
{
    DEMOD_CAB_IQ_NORMAL,                                                      ///< Normal
    DEMOD_CAB_IQ_INVERT                                                       ///< Inverse
} DEMOD_EN_CAB_IQ_MODE;

/// Define DVB-S modulatiopn scheme
typedef enum
{
    DEMOD_SAT_DVBS2,                                                          ///< DVBS2
    DEMOD_SAT_DVBS                                                            ///< DVBS
} DEMOD_EN_SAT_MOD_TYPE;

/// Define DVB-S modulatiopn scheme
typedef enum
{
    DEMOD_SAT_QPSK,                                                           ///< QPSK
    DEMOD_SAT_8PSK,                                                           ///< 8PSK
    DEMOD_SAT_QAM16                                                           ///< QAM16
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

#ifdef DVBT2_STYLE
typedef enum
{
     E_DEMOD_TYPE_T =0,
     E_DEMOD_TYPE_T2,
}EN_DEMOD_TYPE;
#endif

#if 0//(!ENABLE_DVB_T2)
typedef enum
{
    E_DEMOD_LOCK = 0,
    E_DEMOD_CHECKING,
    E_DEMOD_CHECKEND,
    E_DEMOD_UNLOCK,
    E_DEMOD_NULL,
} EN_LOCK_STATUS;
#endif

// Device dependant parameter
typedef struct
{
	MS_U32							u32TunerFreq;						///Tuner Freq
	MS_U32							u32SymbolRate;						///SymbolRate
	MS_U8							u8BandWidth;						///Tunser Bandwith
} CofdmDMD_Param;

/// Define tuning paramter of DVB-T front-end
typedef struct
{
  #ifdef DVBT2_STYLE
    MS_U8                 u8PlpID;
    MS_U8                 u8ScanType;
    #endif
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
    DEMOD_EN_CAB_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    MS_U16                          u16SymbolRate;                      ///< Symbol rate (Ksym/sec)

    DEMOD_EN_CAB_IQ_MODE                  eIQMode;                            ///< IQ Mode
    MS_U8                           u8TapAssign;                        ///< Tap assign
    MS_U32                          u32FreqOffset;                      ///< Carrier frequency offset
    MS_U8                           u8TuneFreqOffset;                       ///< Requeset tuner freq offset
    MS_U8                           u8DemodConfig;
} DEMOD_MS_CAB_CARRIER_PARAM;

/// Define tuning paramter of DVB-S front-end
typedef struct
{
    DEMOD_EN_SAT_MOD_TYPE                   eDemod_Type;                        ///< Mode type
    DEMOD_EN_SAT_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    DEMOD_EN_SAT_ROLL_OFF_TYPE            eRollOff;                           ///< Roll-Off factor
    DEMOD_EN_SAT_IQ_MODE                  eIQ_Mode;                           ///< IQ mode
    DEMOD_EN_CONV_CODE_RATE_TYPE          eCodeRate;                          ///< Converlution code rate
    MS_U32                                u32SymbolRate;
    MS_U8                                 u8Polarity;                         // 0: Horizon; > 0(default 1): Vertical;
    MS_U16                                s16FreqOffset;
} DEMOD_MS_SAT_CARRIER_PARAM;

/// Define carrier paramter of digital tuner
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef struct
{
    MS_U32                          u32Frequency;                       ///< RF frequency
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
    DEMOD_EN_FE_LOCK_STATUS               eLock;
    DEMOD_EN_BIT_ERR_RATIO                eBER;                               ///< Bit error rate
    MS_U8                                 u8SNR;
    MS_U8                                 u8Signal;
    MS_U8                                 u8SignalQuality;                    ///< Signal Quality,mick
    float                                 fPreBER;                            ///< xxE-xx,mick
    float                                 fPostBerTSBER;
    MS_U16                                u16TSpacketError;                   ///< TS Packet Error
} DEMOD_MS_FE_CARRIER_STATUS;

typedef struct
{
        MS_BOOL                           bLNBPowerOn;                                              ///< Power On/Off
        MS_BOOL                           b22kOn;                                                           ///< LNB 22k On/Off
        MS_BOOL                           bLNBOutLow;                                                   ///< LNB 13/18V

} DEMOD_MS_FE_CARRIER_DISEQC;

/// Define the carrier information
typedef struct
{
    DEMOD_MS_FE_CARRIER_PARAM             Param;                              ///< Carrier parameter
    DEMOD_MS_FE_CARRIER_STATUS            Status;                             ///< Quality report
    DEMOD_MS_FE_CARRIER_DISEQC            DiSEqCp;                                                      ///< DiSEqC
} DEMOD_MS_FE_CARRIER_INFO_;//_ for compiler warning

typedef struct
{
    // Demodulator option
    MS_BOOL                         bX4CFE_en;                          ///< Carrier frequency estimation
    MS_BOOL                         bPPD_en;                            ///< Tap assign estimation
    MS_BOOL                         bIQAutoSwap_en;                     ///< IQ mode auto swap
    MS_BOOL                         bQAMScan_en;                        ///< QAM type auto scan
    MS_BOOL                         bFHO_en;                            ///< FHO
    MS_BOOL                         (*fptTunerSet)(MS_U32);             ///< Tuner set freq function pointer
// } DMD_Mode;
} Demod_Mode;

MS_BOOL MDrv_Demod_Init(void);
MS_BOOL MDrv_Demod_Open(void);
MS_BOOL MDrv_Demod_Close(void);
MS_BOOL MDrv_Demod_Reset(void);
MS_BOOL MDrv_Demod_TsOut(MS_BOOL bEnable);
MS_BOOL MDrv_Demod_PowerOnOff(MS_BOOL bPowerOn);
MS_BOOL MDrv_Demod_SetBW(MS_U32 u32BW);
MS_BOOL MDrv_Demod_GetBW(MS_U32 *pu32BW);
#ifdef TWIN_TUNER
MS_BOOL MDrv_CofdmDmd_GetLock(MS_BOOL *pbLock,MS_U8 i_dmd);
#else
MS_BOOL MDrv_CofdmDmd_GetLock(MS_BOOL *pbLock);
#endif
MS_BOOL MDrv_CofdmDmd_GetSNR(MS_U32 *pu32SNR);
MS_BOOL MDrv_Demod_GetBER(float *pfBER);
MS_BOOL MDrv_CofdmDmd_GetPWR(MS_S32 *ps32Signal);
MS_BOOL MDrv_Demod_Config(MS_U8 *pRegParam);

MS_BOOL MDrv_Demod_GetParam(DEMOD_MS_FE_CARRIER_PARAM* pParam); // MS_BOOL MDrv_Demod_GetParam(DMD_Param *pParam);
MS_BOOL MDrv_CofdmDmd_Restart(CofdmDMD_Param* pParam);
MS_BOOL MDrv_Demod_SetMode(Demod_Mode* pMode); // MS_BOOL MDrv_Demod_SetMode(DMD_Mode *pMode);

MS_BOOL MDrv_Demod_SetOutoutPath(DEMOD_INTERFACE_MODE path);
DEMOD_INTERFACE_MODE MDrv_Demod_GetOutoutPath(void);
#ifdef FE_AUTO_TEST
MS_U16  MDrv_Demod_ReadReg(MS_U16 RegAddr);
MS_BOOL MDrv_Demod_WriteReg(MS_U16 RegAddr, MS_U16 RegData);
MS_BOOL MDrv_Demod_Get_Packet_Error(MS_U16 *u16_data);
#endif
#ifdef TWIN_TUNER
MS_BOOL MDrv_Demod_I2C_ByPass(MS_BOOL bOn);
MS_BOOL MDrv_Demod_SetTsSerial(MS_BOOL bSerial);
typedef MS_BOOL (*DEMOD_INIT) (void);
typedef MS_BOOL (*DEMOD_OPEN) (void);
typedef MS_BOOL (*DEMOD_CLOSE) (void);
typedef MS_BOOL (*DEMOD_RESET) (void);
typedef MS_BOOL (*DEMOD_TSOUT) (MS_BOOL);
typedef MS_BOOL (*DEMOD_POWERONOFF) (MS_BOOL);
typedef MS_BOOL (*DEMOD_SETBW) (MS_U32);
typedef MS_BOOL (*DEMOD_GETBW) (MS_U32 *);
typedef MS_BOOL (*DEMOD_GETLOCK) (MS_BOOL *);
typedef MS_BOOL (*DEMOD_GETSNR) (MS_U32 *);
typedef MS_BOOL (*DEMOD_GETBER) (float *);
typedef MS_BOOL (*DEMOD_GETPWR) (MS_S32 *);
typedef MS_BOOL (*DEMOD_CONFIG)(MS_U8 *);
typedef MS_BOOL (*DEMOD_GETPARAM) (DEMOD_MS_FE_CARRIER_PARAM *);
typedef MS_BOOL (*DEMOD_SETMODE) (Demod_Mode *);
typedef MS_BOOL (*DEMOD_SETOUTOUTPATH) (DEMOD_INTERFACE_MODE);
typedef DEMOD_INTERFACE_MODE (*DEMOD_GETOUTOUTPATH) (void);
typedef MS_BOOL (*DEMOD_I2C_BYPASS) (MS_BOOL);
typedef MS_BOOL (*DEMOD_SETTSSERIAL) (MS_BOOL);
typedef MS_BOOL (*DEMOD_RESTART_TYPE)(DEMOD_MS_FE_CARRIER_PARAM*, DEMOD_EN_FE_TUNE_MODE,MS_U8);
typedef MS_BOOL (*DEMOD_GETSIGNALQUALITY)(MS_U16 *);
MS_BOOL DTV_DVB_S_GetParamInfo(DEMOD_MS_FE_CARRIER_INFO_* DEMOD_MS_FE_CARRIER_INFO);
typedef struct S_demod
{
    DEMOD_INIT                          demod_init;
    DEMOD_OPEN                        demod_open;
    DEMOD_CLOSE                      demod_close;
    DEMOD_RESET                      demod_reset;
    DEMOD_TSOUT                     demod_tsout;
    DEMOD_POWERONOFF           demod_poweronoff;
    DEMOD_SETBW                    demod_setbw;
    DEMOD_GETBW                    demod_getbw;
    DEMOD_GETLOCK                  demod_getlock;
    DEMOD_GETSNR                    demod_getsnr;
    DEMOD_GETBER                    demod_getber;
    DEMOD_GETPWR                   demod_getpwr;
    DEMOD_CONFIG                     demod_config;
    DEMOD_GETPARAM                 demod_getparam;
    DEMOD_SETMODE                   demod_setmode;
    DEMOD_SETOUTOUTPATH          demod_setoutoutpath;
    DEMOD_GETOUTOUTPATH         demod_getoutoutpath;
    DEMOD_I2C_BYPASS               demod_i2c_bypass;
    DEMOD_SETTSSERIAL            demod_settsserial;
    DEMOD_RESTART_TYPE         demod_restart_type;
    DEMOD_GETSIGNALQUALITY      demod_getsignalquality;
    DMX_FLOW_INPUT       demod_dmx_input;
    MS_BOOL                  bEnable;
    MS_BOOL                 bispreemptive;
    MS_U64                  i_demod;
    MS_S16                 auto_timeout;
    MS_S16                 manual_timeout;
    MS_S16                 lock_timeout;
    MS_BOOL               dmd_lock_status;
}s_demod;
MS_BOOL MDrv_Demod_Restart_Type(DEMOD_MS_FE_CARRIER_PARAM* pParam,DEMOD_EN_FE_TUNE_MODE eMode, MS_U8 i_demod);
MS_BOOL MDrv_Demod_GetMaxLockTime(DEMOD_EN_FE_TUNE_MODE eMode, MS_U32 *u32LockTime);
MS_BOOL MDrv_Demod_GetSignalQuality(MS_U16 *quality);
DMX_FLOW_INPUT  MDrv_Demod_GetDMXInputType_Play(void);
DMX_FLOW_INPUT  MDrv_Demod_GetDMXInputType_Record(MS_U8* i_demod);
void MDrv_Demod_Change_Demod(void);
MS_S8 MDrv_Demod_Get_DemodNum(void);
MS_S8 MDrv_Demod_Get_PreemtiveDMD_Index(void);
void MDrv_Demod_SetLockStatus(MS_BOOL block,MS_U8 i_dmd);
MS_BOOL MDrv_Demod_GetLockStatus(MS_U8 i_dmd);
MS_S16 MDrv_Demod_GetLockTime(MS_U8 i_dmd);
#else
MS_BOOL MDrv_Demod_I2C_ByPass(MS_BOOL bOn);
#ifdef DVBT2_STYLE
extern MS_U8     MDrv_Demod_GetCurrentDemodType(void);
extern MS_BOOL MDrv_Demod_SetScanTypeStatus(MS_U8 status);
extern MS_U8     MDrv_Demod_GetScanTypeStatus(void);
extern MS_U8     MDrv_Demod_GetPlpIDList(void);
extern MS_U8 MDrv_Demod_GetNextPlpID(MS_U8 u8Index);
extern MS_U8     MDrv_Demod_GetPlpIDSize(void);
extern void MDrv_Demod_CtrlResetDJBFlag(MS_U8 Ctrl) ;
extern MS_BOOL MDrv_Demod_InitParameter(void);
extern EN_LOCK_STATUS MDrv_Demod_GetT2LockStatus(void);
extern MS_U8 MDrv_Demod_Get_Packet_Error(MS_U16 *u16_data);
extern MS_U16 MDrv_Demod_Get_FreqOffset(float *pFreqOff, MS_U8 u8BW);
extern MS_BOOL MDrv_Demod_T2MI_Restart(void);
MS_U16  MDrv_Demod_ReadReg(MS_U16 RegAddr);
MS_BOOL MDrv_Demod_WriteReg(MS_U16 RegAddr, MS_U16 RegData);
#endif

#if ENABLE_S2
#if ((FRONTEND_DEMOD_S2_TYPE == DEMOD_AVL6211))// ||(FRONTEND_DEMOD_TYPE == MSTAR_MSB131X_DVBS2))
MS_BOOL MDrv_Demod_SetTsSerial(MS_BOOL bSerial);
MS_BOOL MDrv_Demod_TPSGetLock(MS_BOOL *pbLock);
MS_BOOL MDrv_Demod_MPEGGetLock(MS_BOOL *pbLock);
MS_BOOL MDrv_Demod_GetRollOff(MS_U8 *pRollOff);
MS_BOOL MDrv_CofdmDmd_GetRFOffset(MS_S16 *ps16RFOff);
MS_BOOL MDrv_CofdmDmd_BlindScan_Start(MS_U16 u16StartFreq,MS_U16 u16EndFreq,MS_BOOL bUCMode);
MS_BOOL MDrv_CofdmDmd_BlindScan_NextFreq(MS_BOOL* bBlindScanEnd,MS_U8* u8Progress);
MS_BOOL MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(MS_U8* u8Progress,MS_U8 *u8FindNum);
MS_BOOL MDrv_CofdmDmd_BlindScan_Cancel(void);
MS_BOOL MDrv_CofdmDmd_BlindScan_End(void);
MS_BOOL MDrv_CofdmDmd_BlindScan_GetChannel(MS_U16 u16ReadStart,MS_U16* u16TPNum,DTVPROGRAMID_M *pTable);
MS_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MS_U32 *u32CurrentFeq);
MS_BOOL MDrv_DiSEqC_SetTone(MS_BOOL bTone1);
MS_BOOL MDrv_DiSEqC_SetLNBOut(MS_BOOL bLow);
MS_BOOL MDrv_DiSEqC_GetLNBOut(MS_BOOL* bLNBOutLow);
MS_BOOL MDrv_DiSEqC_Set22kOnOff(MS_BOOL b22kOn);
MS_BOOL MDrv_DiSEqC_Get22kOnOff(MS_BOOL* b22kOn);
MS_BOOL MDrv_DiSEqC_SendCmd(MS_U8* pCmd,MS_U8 u8CmdSize);
#endif
#endif //#if ENABLE_S2
#endif

#endif // #define __DRV_DEMOD_H__
