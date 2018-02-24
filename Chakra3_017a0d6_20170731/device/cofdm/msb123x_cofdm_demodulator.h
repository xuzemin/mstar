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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#include "Board.h"
#if (ENABLE_DVB_T2)
//#include "MsBoard.h"
#include "Tuner.h"
#include "Enum_Device.h"
#include "COFDM_Demodulator.h"
#include "drvGPIO.h"

#define ENABLE_IIC_PASS_THROUGH_COFDM         0
/*
typedef enum
{
    E_SERIAL_INTERFACE,
    E_PARALLEL_INTERFACE
} TS_INTERFACE;
*/
/*
typedef enum
{
    E_RF_CH_BAND_6MHz = 0x01,       ///< 6MHz
    E_RF_CH_BAND_7MHz = 0x02,       ///< 7MHz
    E_RF_CH_BAND_8MHz = 0x03,       ///< 8MHz
    E_RF_CH_BAND_INVALID            ///< Invalid
} RF_CHANNEL_BANDWIDTH;
*/
typedef enum
{
    E_Network_Type_DVBT =1,
    E_Network_Type_DVBC ,
    E_Network_Type_Analog_T ,
    E_Network_Type_Analog_C ,
    E_Network_Type_DVBT2
} Network_Type;

typedef struct
{
    MS_BOOL IsDTVActive;
    RF_CHANNEL_BANDWIDTH RfBw;
    MS_U32 RfFreqInKHz;
}CUR_RF_INFO;

typedef enum
{
    //Internal Demodulator
    E_COFDM_INTERNAL_DVBT,
    E_COFDM_INTERNAL_DVBC,
    //External Demodulator
    E_COFDM_EXTERNAL_DVBT2,
    E_COFDM_EXTERNAL_DVBS,
    E_COFDM_INVALID
}CUR_COFDM_CFG;

//====================== cofdm common ======================
/*
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
*/
#if 0
typedef enum
{
    E_SYS_UNKOWN = -1,
    E_SYS_DVBT,
    E_SYS_DVBC,
    E_SYS_ATSC,
    E_SYS_VIF,

    E_SYS_NUM
}E_SYSTEM;

typedef enum
{
    SET_IF_FREQ = 0,
    SET_SOUND_SYS,
    VIF_INIT,
    SET_VIF_HANDLER,
    VIF_TOP_ADJUST,

    VIF_CMD_MAX_NUM
}E_VIF_CMD;
typedef enum
{
    TS_PARALLEL = 0,
    TS_SERIAL = 1,

    TS_MODE_MAX_NUM
}E_TS_MODE;
#endif

typedef enum
{
    TS_CLK_NO_INV = 0,
    TS_CLK_INVERSE = 1,

    TS_CLK_MODE_MAX_NUM
}E_TS_CLK_MODE;

typedef struct
{
    MS_U16 Constellation    : 3;
    MS_U16 Hierarchy         :3;
    MS_U16 LpCodeRate         :3;
    MS_U16 HpCodeRate         :3;
    MS_U16 GI                       :2;
    MS_U16 FFTmode         :1;
    MS_U16 Priority             :1;
} S_TPS_INFO;

typedef struct
{
    MS_U64 Constellation        :3;
    MS_U64 CodeRate              :3;
    MS_U64 GI                          :3;
    MS_U64 FFTmode               :3;
    MS_U64 Preamble              :1;
    MS_U64 S1Signalling          :2;
    MS_U64 l1PrePilot              :4;
    MS_U64 BwExt                     :1;
    MS_U64 l1PrePAPRReduction :3;
    MS_U64 ofdm_symbols_per_frame :12;
} S_TPS_INFO_T2;

typedef enum
{
    E_CONST_QPSK,    //DVBT
    E_CONST_16QAM,  //DVBT DVBC
    E_CONST_64QAM,  //DVBT DVBC
    E_CONST_32QAM,  //DVBC
    E_CONST_128QAM,  //DVBC
    E_CONST_256QAM,  //DVBC
    E_CONST_INVALID,
}E_TPS_CONST;

typedef enum
{
    E_HIERARCHY_NONE,
    E_HIERARCHY_APLHA1,
    E_HIERARCHY_APLHA2,
    E_HIERARCHY_APLHA4,
}E_TPS_HIERARCHY;

typedef enum
{
    E_FEC_1_2,
    E_FEC_2_3,
    E_FEC_3_4,
    E_FEC_5_6,
    E_FEC_7_8,
    E_FEC_4_5,
    E_FEC_6_7,
    E_FEC_8_9,
}E_TPS_FEC;

typedef enum
{
    E_FEC_T2_1_2,
    E_FEC_T2_3_5,
    E_FEC_T2_2_3,
    E_FEC_T2_3_4,
    E_FEC_T2_4_5,
    E_FEC_T2_5_6,
}E_TPS_FEC_T2;

typedef enum
{
    E_GI_1_32,
    E_GI_1_16,
    E_GI_1_8,
    E_GI_1_4,
    E_GI_1_128,  //DVBT2
    E_GI_19_128,  //DVBT2
    E_GI_19_256,  //DVBT2
}E_TPS_GI;

typedef enum
{
    E_FFT_2K,
    E_FFT_8K,
    E_FFT_1K,    //DVBT2
    E_FFT_4K,    //DVBT2
    E_FFT_16K,  //DVBT2
    E_FFT_32K,  //DVBT2
}E_TPS_FFT;

typedef enum
{
    E_PREAMBLE_NOT_MIXED = 0x00, //DVBT2
    E_PREAMBLE_MIXED = 0x01,  //DVBT2
}E_TPS_PREAMBLE;

typedef enum
{
    E_S1_SIGNALLING_T2_SISO = 0x00,  //DVBT2
    E_S1_SIGNALLING_T2_MISO = 0x01,  //DVBT2
    E_S1_SIGNALLING_NON_T2 = 0x02,  //DVBT2
    E_S1_SIGNALLING_RESERVED,  //DVBT2
}E_TPS_S1_SIGNALLING;

typedef enum
{
    E_l1_PRE_PILOT_PATTERN_1 = 0x00,  //DVBT2
    E_l1_PRE_PILOT_PATTERN_2 = 0x01,  //DVBT2
    E_l1_PRE_PILOT_PATTERN_3 = 0x02,  //DVBT2
    E_l1_PRE_PILOT_PATTERN_4 = 0x03,  //DVBT2
    E_l1_PRE_PILOT_PATTERN_5 = 0x04,  //DVBT2
    E_l1_PRE_PILOT_PATTERN_6 = 0x05,  //DVBT2
    E_l1_PRE_PILOT_PATTERN_7 = 0x06,  //DVBT2
    E_l1_PRE_PILOT_PATTERN_8 = 0x07,  //DVBT2
    E_l1_PRE_PILOT_PATTERN_RESERVED,  //DVBT2
}E_TPS_l1_PRE_PILOT;

typedef enum
{
    E_BW_NORMAL_MODE = 0x00,  //DVBT2
    E_BW_EXTENSION_MODE = 0x01,  //DVBT2
}E_TPS_BW_EXT;

typedef enum
{
    E_l1_PRE_PAPR_REDUCTION_NONE = 0x00,  //DVBT2
    E_l1_PRE_PAPR_REDUCTION_ACE = 0x01,  //DVBT2
    E_l1_PRE_PAPR_REDUCTION_TR = 0x02,  //DVBT2
    E_l1_PRE_PAPR_REDUCTION_TR_AND_ACE = 0x03,  //DVBT2
    E_l1_PRE_PAPR_REDUCTION_RESERVED,  //DVBT2
}E_TPS_l1_PRE_PEAK_AVERAGE_POWER_RATIO;

typedef enum
{
    agc_ref_small = 0,
    agc_ref_large,
    agc_ref_aci,
    ripple_switch_th_l,
    ripple_switch_th_h,

    TUNED_PARAM_MAX_NUM
}E_TUNED_PARAM;

typedef enum
{
    DEMOD_CFG_DVBT = 0,
    DEMOD_CFG_DVBC,
    DEMOD_CFG_ATV,
    DEMOD_CFG_DVBT2,
    DEMOD_CFG_NUM,
} E_DEMOD_DSP_CFG;
typedef enum
{
    ICE_network_dvbt2 = 0,
    ICE_network_dvbt,
    ICE_network_dvbc,
    ICE_network_analog,
    ICE_network_num
}E_ICE_NETWORK_TYPE;
typedef struct
{
    U32 channel_frequency_khz;
    E_ICE_NETWORK_TYPE  network_type;
}ICE_TuneToParams;
#if(FRONTEND_DEMOD_T2_TYPE != MSTAR_MSB124X_DVBT)//(CHIP_FAMILY_TYPE!=CHIP_FAMILY_MAYA)
typedef enum
{
  COFDM_FEC_LOCK_DVBT_123X,
  COFDM_FEC_LOCK_DVBC_123X,
  COFDM_TR_LOCK_DVBC_123X,
  COFDM_PSYNC_LOCK_123X,
  COFDM_TPS_LOCK_123X,
  COFDM_TPS_LOCK_HISTORY_123X,
  COFDM_DCR_LOCK_123X,
  COFDM_AGC_LOCK_123X,
  COFDM_MODE_DET_123X,
  COFDM_LOCK_STABLE_DVBT_123X,
  COFDM_SYNC_LOCK_DVBT_123X,
  COFDM_FAST_LOCK_DVBT_123X,//add 0920
  //addy update 0805
  COFDM_P1_LOCK_123X,
  COFDM_P1_LOCK_HISTORY_123X,
  COFDM_L1_CRC_LOCK_123X,
  COFDM_FEC_LOCK_T2_123X

} COFDM_LOCK_STATUS_123X;

#endif


//====================== cofdm common ======================

//CUR_RF_INFO CurRFParam;
//MS_U32 ICE_scan_continue;
//MS_U32 gU32Max_Freq_KHz;
//MS_U32  gU32Min_Freq_KHz;
//MS_BOOL gbSECAM_LP_enable;

#define Count_Of_CheckLock_100ms    30
#define Count_Of_CheckLock_Msb1210_time_Count            30 // 30*50  1.5 sec
#define Count_Of_CheckLock_Msb1210_Extend_time_Count   160 //160*50  8 sec
#define Count_Of_CheckLock_Msb1210_Delay_ms             50
#define Count_Of_CheckLock_Msb1210_Short_Delay_ms       50
#define Count_Of_CheckLock_Msb1210_Successful_Num       6//3

#define Count_Of_CheckLock_Msb1222_Period_ms           30
#define Count_Of_CheckLock_Msb1222_Extend_Period_ms    24
#define Count_Of_CheckLock_Msb1222_Delay_ms           100
#define Count_Of_CheckLock_Msb1222_Short_Delay_ms     100
#define Count_Of_CheckLock_Msb1222_Successful_Num       1

#define Count_Of_CheckLock_Intern_dvbc_count               50
#define Count_Of_CheckLock_Intern_dvbc_Delay_ms           100
#define Count_Of_CheckLock_Intern_dvbc_Successful_Num       1

typedef struct
{
void (*FEND_Init)(void);
void (*FEND_CtlDTVPower)(BOOLEAN bPowerOn);
void (*FEND_SetDTVFrequency)(const ICE_TuneToParams* params, RF_CHANNEL_BANDWIDTH bandWith);
MS_BOOL (*FEND_GetSignalQuality)(MS_U16 *quality);
MS_BOOL (*FEND_GetSignalStrength)(MS_U16 *strength);
MS_BOOL (*FEND_GetLockStatus)(COFDM_LOCK_STATUS_123X eStatus);
MS_BOOL (*FEND_GetTPSInfo)(MS_U16 *Const);
MS_BOOL (*FEND_GetCellId)(MS_U16 *CellId);
MS_BOOL (*FEND_GetSymbolRate)(MS_U16 *pSymbolRate);
//void (*FEND_SetIFFrequency)(MS_U32 freq_KHz,ICE_AnalogTVSystem TV_SYS,MS_S16 s16Finetune);
//AFC(*FEND_VifGetAfc)(void);
void (*FEND_VifHandler)(MS_BOOL bAutoScan);
MS_U8 (*FEND_T2GetPlpIDList)(void);
MS_BOOL (*FEND_T2GetPlpGroupID)(MS_U8 u8PlpID, MS_U8* u8GroupID);
MS_BOOL (*FEND_T2SetPlpGroupID)(MS_U8 u8PlpID, MS_U8 u8GroupID);
MS_BOOL (*FEND_T2DemodReady)(void);
MS_BOOL (*FEND_T2GetTPSInfo)(MS_U64 *TPS_Info_T2);
MS_BOOL (*FEND_T2GetCurrentPlpID)(MS_U8 *pu8PlpID);

}sdevFENDfunc;
//******************************************************************************
// Functions prototype
//******************************************************************************
void mdev_CofdmHWireReset(void);
extern void mdev_CofdmInit(void);
void mdev_CofdmControlPowerOnOff(BOOLEAN bPowerOn);
MS_BOOL mdev_CofdmPowerSave(void);
void mdev_CofdmSetFrequency(const ICE_TuneToParams* params, RF_CHANNEL_BANDWIDTH bandWith);
MS_BOOL mdev_CofdmGetLockStatus(COFDM_LOCK_STATUS_123X eStatus);
MS_U8 mdev_CofdmGetSignalToNoiseRatio(void);
void mdev_CofdmPassThroughI2c(MS_BOOL bEnable);
MS_BOOL mdev_CofdmPassThroughI2cWriteBytes(MS_U8 u8SlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);
MS_BOOL mdev_CofdmPassThroughI2cReadBytes(MS_U8 u8SlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);
void mdev_CofdmSwitchTransportSteamInferface(TS_INTERFACE interface);
MS_BOOL mdev_CofdmGetSignalStrength(MS_U16 *strength);
MS_BOOL mdev_CofdmGetCellid(MS_U16 *wCell_id);
MS_BOOL mdev_CofdmGetSignalQuality(MS_U16 *quality);
MS_BOOL mdev_CofdmGetTpsInfo(MS_U16 *TPS_Info);
void mdev_CofdmTunerProgramming(MS_U8 *cTunerData);
MS_BOOL mdev_CofdmReadReg(MS_U16 u16Addr, MS_U8 *pu8Data);
MS_BOOL mdev_CofdmWriteReg(MS_U16 RegAddr, MS_U16 RegData);
MS_BOOL mdev_DVBT_GetSignalStrength_XC6200(MS_U16 *strength);
void mdev_Tuner_Get_Signal_Strength_XC6200(float *strength_dBm);
MS_BOOL mdev_CofdmGetCurrentPlpID(MS_U8 *pu8PlpID);
float Si2156_GetRSSILevel(float *strength_dBm);
MS_BOOL mdev_DVBT_GetSignalStrength_Si2156(MS_U16 *strength);
sdevFENDfunc* mdev_FrontEndAttach(void);
void mdev_CofdmBootSwitchTSInferface(TS_INTERFACE interface);
void mdev_CofdmDisableTSPAD(void);
CUR_COFDM_CFG mdev_Get_Current_DEMOD_TYPE(void);
void mdev_Set_Current_DEMOD_TYPE(CUR_COFDM_CFG sDemodType);
MS_U8 mdev_CofdmGetPlpIDList(void);
MS_BOOL mdev_CofdmSetPlpGroupID(MS_U8 u8PlpID, MS_U8 u8GroupID);
MS_BOOL mdev_Cofdm_MSB123X_Ready(void);
void mdev_ControlTSOutput(BOOLEAN bEnable);
void mdev_ControlAGCOutput(BOOLEAN bEnable);
MS_U16 mdev_CofdmGetPacketErr(void);

#endif


