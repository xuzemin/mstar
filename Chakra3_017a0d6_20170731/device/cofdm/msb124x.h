/*@ <FileComment ID=1246257763790> @*/
/**********************************************************************
 Copyright (c) 2006-2009 MStar Semiconductor, Inc.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
 herein regardless in any format shall remain the sole proprietary of
 MStar Semiconductor Inc. and be kept in strict confidence
 (MStar Confidential Information) by the recipient.
 Any unauthorized act including without limitation unauthorized disclosure,
 copying, use, reproduction, sale, distribution, modification, disassembling,
 reverse engineering and compiling of the contents of MStar Confidential
 Information is unlawful and strictly prohibited. MStar hereby reserves the
 rights to any and all damages, losses, costs and expenses resulting therefrom.

* Class : mapi_demodulator_msb123x
* File  : mapi_demodulator_msb123x.h
**********************************************************************/

/*@ </FileComment ID=1246257763790> @*/


/*@ <IncludeGuard> @*/
#ifndef device_demodulator_msb1240
#define device_demodulator_msb1240
/*@ </IncludeGuard> @*/
/*@ <Include> @*/
#include "MsCommon.h"
#include "MsOS.h"
#include "Board.h"
#include "Tuner.h"
#include "msAPI_DTVSystem.h"
#include "drvIIC.h"
#include "apiDTVSatTable.h"
#include "drvDemod.h"

// For basic define
#include "msAPI_Demod_DVBC.h"

/*@ </Include> @*/

/*@ <Definitions> @*/
#ifndef MAPI_U8
#define MAPI_U8 MS_U8
#endif

#ifndef MAPI_U16
#define MAPI_U16 MS_U16
#endif

#ifndef MAPI_U32
#define MAPI_U32 MS_U32
#endif

#ifndef MAPI_BOOL
#define MAPI_BOOL MS_BOOL
#endif

#ifndef MAPI_S16
#define MAPI_S16 MS_S16
#endif

#define MAPI_TRUE TRUE
#define MAPI_FALSE FALSE

typedef enum
{
    DEV_MSB1240_FFT_2K      = 0x0,
    DEV_MSB1240_FFT_8K      = 0x1,
    DEV_MSB1240_FFT_4K      = 0x2,
    DEV_MSB1240_FFT_1K      = 0x3,
    DEV_MSB1240_FFT_16K      = 0x4,
    DEV_MSB1240_FFT_32K      = 0x5,
    DEV_MSB1240_FFT_8K_     = 0x6,
    DEV_MSB1240_FFT_32K_    = 0x7,
} DEV_MSB1240_FFT_VAL;

//Bit 0~2:        code rate (0 => 1/2, 1 => 3/5, 2 => 2/3, 3 =>3/4, 4 => 4/5, 5 => 5/6)
typedef enum
{
    _T2_CR1Y2   = 0x0,
    _T2_CR3Y5   = 0x1,
    _T2_CR2Y3   = 0x2,
    _T2_CR3Y4   = 0x3,
    _T2_CR4Y5   = 0x4,
    _T2_CR5Y6   = 0x5,
    _T2_CR_UNKNOWN     = 0xFF,
} E_T2_CODERATE;

//Bit 4~6:        constellation ( 0x000 => QPSK, 0x001 => 16QAM, 0x0010 => 64QAM, 0x0011=> 256QAM)
typedef enum
{
    _T2_QPSK    = 0x0,
    _T2_16QAM   = 0x1,
    _T2_64QAM   = 0x2,
    _T2_256QAM    = 0x3,
    _T2_QAM_UNKNOWN     = 0xFF,
} E_T2_CONSTEL;

typedef struct
{
    E_T2_CONSTEL           constel;
    E_T2_CODERATE          code_rate;
    float                  cn_ref;
} S_DVBT2_SQI_CN_NORDIGP1;

typedef enum
{
    TS_MODUL_MODE,
    TS_FFT_VALUE,
    TS_GUARD_INTERVAL,
    TS_CODE_RATE,
    TS_PREAMBLE,
    TS_S1_SIGNALLING,
    TS_PILOT_PATTERN,
    TS_BW_EXT,
    TS_PAPR_REDUCTION,
    TS_OFDM_SYMBOLS_PER_FRAME,
    TS_T2_GUARD_INTERVAL,
    TS_T2_FFT_VALUE,
    TS_PARAM_MAX_NUM
}E_SIGNAL_TYPE;
typedef enum
{
    T2_MODUL_MODE,
    T2_FFT_VALUE,
    T2_GUARD_INTERVAL,
    T2_CODE_RATE,
    T2_PREAMBLE,
    T2_S1_SIGNALLING,
    T2_PILOT_PATTERN,
    T2_BW_EXT,
    T2_PAPR_REDUCTION,
    T2_OFDM_SYMBOLS_PER_FRAME,
    T2_PARAM_MAX_NUM,
    T2_PLP_ROTATION,
    T2_PLP_FEC_TYPE,
    T2_NUM_PLP,
} E_T2_SIGNAL_INFO;
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

typedef enum
{
    // fw version, check sum
    T_CHECK_SUM_L           = 0x00,
    T_CHECK_SUM_H,
    T_FW_VER_0,
    T_FW_VER_1,
    T_FW_VER_2,

    // operation mode settings
    T_OPMODE_RFAGC_EN  = 0x20,   // 0x20
    T_OPMODE_HUMDET_EN,
    T_OPMODE_DCR_EN,
    T_OPMODE_IIS_EN,
    T_OPMODE_CCI_EN,
    T_OPMODE_ACI_EN,
    T_OPMODE_IQB_EN,
    T_OPMODE_AUTO_IQ,
    T_OPMODE_AUTO_RFMAX,    // 0x28
    T_OPMODE_AUTO_ACI,
    T_OPMODE_FIX_MODE_CP,
    T_OPMODE_FIX_TPS,
    T_OPMODE_AUTO_SCAN,
    T_OPMODE_RSV_0X2D,
    T_OPMODE_RSV_0X2E,
    T_OPMODE_RSV_0X2F,

    // channel config param
    T_CONFIG_RSSI,    // 0x30
    T_CONFIG_ZIF,
    T_CONFIG_FREQ,
    T_CONFIG_FC_L,
    T_CONFIG_FC_H,
    T_CONFIG_FS_L,
    T_CONFIG_FS_H,
    T_CONFIG_BW,
    T_CONFIG_MODE,    // 0x38
    T_CONFIG_CP,
    T_CONFIG_LP_SEL,
    T_CONFIG_CSTL,
    T_CONFIG_HIER,
    T_CONFIG_HPCR,
    T_CONFIG_LPCR,
    T_CONFIG_IQ_SWAP,
    T_CONFIG_RFMAX,    // 0x40
    T_CONFIG_CCI,
    T_CONFIG_ICFO_RANGE,
    T_CONFIG_RFAGC_REF,
    T_CONFIG_IFAGC_REF_2K,
    T_CONFIG_IFAGC_REF_8K,
    T_CONFIG_IFAGC_REF_ACI,
    T_CONFIG_IFAGC_REF_IIS_2K,
    T_CONFIG_IFAGC_REF_IIS_8K,    // 0x48
    T_CONFIG_ACI_DET_TH_L,
    T_CONFIG_ACI_DET_TH_H,
    T_CONFIG_TS_SERIAL,
    T_CONFIG_TS_CLK_RATE,
    T_CONFIG_TS_OUT_INV,
    T_CONFIG_TS_DATA_SWAP,
    T_CONFIG_2K_SFO_H,
    T_CONFIG_2K_SFO_L,    // 0x50
    T_CONFIG_8K_SFO_H,
    T_CONFIG_8K_SFO_L,
    T_CONFIG_CHECK_CHANNEL,
    T_CONFIG_SLICER_SNR_POS,
    T_CONFIG_TDP_CCI_KP,
    T_CONFIG_CCI_FSWEEP,
    T_CONFIG_TS_CLK_RATE_AUTO,
    T_CONFIG_IF_INV_PWM_OUT_EN, //0x58

    // Open DVBT's IIS parameters
    T_CONFIG_IIS_NOISE_MAX_MIN_TH_2K = 0x80,
    T_CONFIG_IIS_BLANK_THR_2K,
    T_CONFIG_IIS_CLIP_THR_2K,
    T_CONFIG_IIS_NOISE_MAX_MIN_TH_8K,
    T_CONFIG_IIS_BLANK_THR_8K,
    T_CONFIG_IIS_CLIP_THR_8K,

    /**********************
     * crc =
     *    ~(T_OPMODE_RFAGC_EN^T_OPMODE_HUMDET_EN^....^T_CONFIG_TS_CLK_RATE_AUTO)
     ************************/
    // T_PARAM_CHECK_SUM,

    // dvbt lock history
    T_DVBT_LOCK_HIS   = 0xF0,
    T_DVBT2_NOCHAN_Flag = 0xF1,
    T_DVBT_NOCHAN_Flag = 0xF2,
    T_DETECT_DONE_FLAG      = 0xF3,
    T_SNR100_L,             // 0xF4
    T_SNR100_H,             // 0xF5
    T_CFO10K_L,             // 0xF6
    T_CFO10K_H,             // 0xF7
    T_CONFIG_SPREAD_SPAN,   // 0xF8
    T_CONFIG_SPREAD_STEP,   // 0xF9

    T_TS_DATA_RATE_0       = 0x130,
    T_TS_DATA_RATE_1       = 0x131,
    T_TS_DATA_RATE_2       = 0x132,
    T_TS_DATA_RATE_3       = 0x133,


    T_PHASE_TUNING_EN = 0x135,
    T_PHASE_TUNING_NUM = 0x136,

    DVBT_PARAM_LEN,
} MSB124X_DVBT_Param;

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


typedef enum
{
    // fw version, check sum
    E_T2_CHECK_SUM_L      = 0x00,
    E_T2_CHECK_SUM_H,
    E_T2_FW_VER_0,
    E_T2_FW_VER_1,
    E_T2_FW_VER_2,

    // operation mode
    E_T2_ZIF_EN           = 0x20,
    E_T2_RF_AGC_EN,
    E_T2_HUM_DET_EN,
    E_T2_DCR_EN,
    E_T2_IQB_EN,
    E_T2_IIS_EN,
    E_T2_CCI_EN,
    E_T2_LOW_PWR_DET_EN,
    E_T2_ACI_DET_EN,
    E_T2_Windowing_EN,
    E_T2_FRC_Short_T2_EN,
    E_T2_FDSA_one_shot_EN,
    E_T2_FDSA_tracking_EN,
    E_T2_Excess_no_image_EN,
    E_T2_FRC_GI_EN,

    // channel tuning param
    E_T2_BW               = 0x40,
    E_T2_FC_L             = 0x41,
    E_T2_FC_H             = 0x42,
    E_T2_FS_L,              //0x43
    E_T2_FS_H,
    E_T2_ZIF,
    E_T2_GI,
    E_T2_ACI_DET_TYPE,
    E_T2_AGC_REF,         //0x48
    E_T2_RSSI_REF,
    E_T2_SNR_TIME_L,
    E_T2_SNR_TIME_H,
    E_T2_BER_CMP_TIME_L,
    E_T2_BER_CMP_TIME_H,
    E_T2_SFO_CFO_NUM,
    E_T2_CCI,
    E_T2_ACI_DET_TH_L,    //0x50
    E_T2_ACI_DET_TH_H,
    E_T2_TS_SERIAL     = 0x52,
    E_T2_TS_CLK_RATE   = 0x53,
    E_T2_TS_OUT_INV    = 0x54,
    E_T2_TS_DATA_SWAP  = 0x55,
    E_T2_TDP_CCI_KP,
    E_T2_CCI_FSWEEP,      //0x57
    E_T2_TS_ERR_POL,      //0x58
    E_T2_IF_AGC_INV_PWM_EN, // 0x59
    E_T2_CCI_TYPE,          //0x5A
    E_T2_LITE,              //0x5B

    // AGC
    E_T2_AGC_K              = 0x60,
    E_T2_AGC_RSSI_K,
    E_T2_AGC_LOCK_TH,       //0x62
    E_T2_AGC_LOCK_NUM,
    E_T2_AGC_CNT_CYCLE,
    E_T2_FE_AGC_LOCK,       //0x65

    // Mixer
    E_T2_FE_MIX_FC_FS_0,    //0x66
    E_T2_FE_MIX_FC_FS_1,
    E_T2_FE_MIX_FC_FS_2,
    E_T2_FE_MIX_FC_FS_3,    //0x69

    // IQSWAP
    E_T2_FE_IQB_SET,        //0x6A

    // CCI
    E_T2_Flag_CI,               //0x6B
    E_T2_FEEXT_CCI_LOCK_DET,
    E_T2_FEEXT_CCI_FREQN_0,
    E_T2_FEEXT_CCI_FREQN_1,
    E_T2_FEEXT_CCI_FREQN_2,     //0x6F

    // ACI
    E_T2_ACI_ANM1_DET_TH_L,     //0x70
    E_T2_ACI_ANM1_DET_TH_H,
    E_T2_ACI_ANP1_DET_TH_L,
    E_T2_ACI_ANP1_DET_TH_H,     //0x73

    // P1
    E_T2TDP_TYPE1_TH_1,         //0x74
    E_T2TDP_TYPE1_TH_2,
    E_T2TDP_TYPE1_TH_3,
    E_T2TDP_TYPE1_TH_4,
    E_T2TDP_TYPE2_TH_1,
    E_T2TDP_TYPE2_TH_2,
    E_T2TDP_TYPE2_TH_3,
    E_T2TDP_TYPE2_TH_4,
    E_T2TDP_TDP_R_0,
    E_T2TDP_TDP_R_1,            //0x7D

    // pilot pattern
    E_T2FDP_PPX_EXT,            //0x7E

    // Interpolator
    E_T2TDP_SEQ_FOE_NUM,        //0x7F
    E_FE_INTP_RATEM1_0,         //0x80
    E_FE_INTP_RATEM1_1,
    E_FE_INTP_RATEM1_2,
    E_FE_INTP_RATEM1_3,         //0x83

    // ICFO
    E_T2FDP_ICFO_R_VAL,         //0x84
    E_T2_TOTAL_CFO_0      = 0x85,
    E_T2_TOTAL_CFO_1,
    E_T2_TOTAL_CFO_2,
    E_T2_TOTAL_CFO_3,           //0x88

    // dvbt2 lock history
    E_T2_DVBT2_LOCK_HIS   = 0xF0,
    E_T2_FEF_DET_IND,
    E_T2_MPLP_NO_COMMON_IND,
    E_T2_SNR_L,             // 0xf3
    E_T2_SNR_H,             // 0xf4
    E_T2_DOPPLER_DET_FLAG,  // 0xf5
    E_T2_DOPPLER_DET_TH_L,  // 0xf6
    E_T2_DOPPLER_DET_TH_H,  // 0xf7
    E_T2_SPREAD_SPAN,       //0xf8
    E_T2_SPREAD_STEP,       //0xf9
    E_T2_FEF_DET_IND_S2,        //0xfa

    // splp, mplp releted
    E_T2_PLP_ID_ARR       = 0x100,
    E_T2_L1_FLAG          = 0x120,
    E_T2_PLP_ID,
    E_T2_GROUP_ID,

    E_T2_S9_DEBUG_INFO          = 0x280, //0x280
    E_T2_S9_RESET_DJB_INFO,     //0x281
    E_T2_S9_RESET_FDI_INFO_L,   //0x282
    E_T2_S9_RESET_FDI_INFO_H,   //0x283
    E_T2_S9_RESET_TO_S0_INFO,   //0x284
    E_T2_MainCenter_0           = 0x301,
    E_T2_MainCenter_1,          //0x302
    E_T2_MainCenter_2,          //0x303
    E_T2_MainCenter_3,          //0x304
    E_T2_MainLeft1st_0,         //0x305
    E_T2_MainLeft1st_1,         //0x306
    E_T2_MainLeft1st_2,         //0x307
    E_T2_MainLeft1st_3,         //0x308
    E_T2_MainLeft2nd_0,         //0x309
    E_T2_MainLeft2nd_1,         //0x30A
    E_T2_MainLeft2nd_2,         //0x30B
    E_T2_MainLeft2nd_3,         //0x30C
    E_T2_MainRight1st_0,        //0x30D
    E_T2_MainRight1st_1,        //0x30E
    E_T2_MainRight1st_2,        //0x30F
    E_T2_MainRight1st_3,        //0x310
    E_T2_MainRight2nd_0,        //0x311
    E_T2_MainRight2nd_1,        //0x312
    E_T2_MainRight2nd_2,        //0x313
    E_T2_MainRight2nd_3,        //0x314
    E_T2_MainCenterMin_0,       //0x315
    E_T2_MainCenterMin_1,       //0x316
    E_T2_MainCenterMin_2,       //0x317
    E_T2_MainCenterMin_3,       //0x318
    E_T2_CompareSNR_history,    //0x319
    E_T2_MinCase,               //0x31A
    E_T2_CompareSNR_case,       //0x31B
    E_T2_MinCPValue_H,          //0x31C
    E_T2_MinCPValue_L,          //0x31D
    E_T2_MainBPF_0,             //0x31E
    E_T2_MainBPF_1,             //0x31F
    E_T2_MainBPF_2,             //0x320
    E_T2_MainBPF_3,             //0x321
    E_T2_CompareSNR_debug,      //0x322

    E_T2_DAGC0_Locking_Time_H   = 0x323,//0x323
    E_T2_DAGC0_Locking_Time_L,  //0x324
    E_T2_DCR_Locking_Time_H,    //0x325
    E_T2_DCR_Locking_Time_L,    //0x326
    E_T2_DAGC1_Locking_Time_H,  //0x327
    E_T2_DAGC1_Locking_Time_L,  //0x328
    E_T2_DAGC2_Locking_Time_H,  //0x329
    E_T2_DAGC2_Locking_Time_L,  //0x32A
    E_T2_P1_First_Locking_Time_H,   //0x32B
    E_T2_P1_First_Locking_Time_L,   //0x32C
    E_T2_P1_Locking_Time_H,         //0x32D
    E_T2_P1_Locking_Time_L,         //0x32E
    E_T2_STATE6_Locking_Time_H,     //0x32F
    E_T2_STATE6_Locking_Time_L,     //0x330
    E_T2_STATE7_Locking_Time_H,     //0x331
    E_T2_STATE7_Locking_Time_L,     //0x332
    E_T2_GI_Locking_Time_H,         //0x333
    E_T2_GI_Locking_Time_L,         //0x334
    E_T2_SYMALI_Locking_Time_H,     //0x335
    E_T2_SYMALI_Locking_Time_L,     //0x336
    E_T2_TDCFOSFO_Locking_Time_H,   //0x337
    E_T2_TDCFOSFO_Locking_Time_L,   //0x338
    E_T2_ICFO_Locking_Time_H,       //0x339
    E_T2_ICFO_Locking_Time_L,       //0x33A
    E_T2_OneShot_Locking_Time_H,    //0x33B
    E_T2_OneShot_Locking_Time_L,    //0x33C
    E_T2_STATE8_Locking_Time_H,     //0x33D
    E_T2_STATE8_Locking_Time_L,     //0x33E
    E_T2_Total_Locking_Time_H,      //0x33F
    E_T2_Total_Locking_Time_L,      //0x340
    E_T2_start_Locking_Time_H,      //0x341
    E_T2_start_Locking_Time_L,      //0x342
    E_T2_end_Locking_Time_H,        //0x343
    E_T2_end_Locking_Time_L,        //0x344
    E_T2_CompareSNR_Locking_Time_H, //0x345
    E_T2_CompareSNR_Locking_Time_L, //0x346
    E_T2_STABLE_Locking_Time_H,     //0x347
    E_T2_STABLE_Locking_Time_L,     //0x348
    E_T2_STABLE_Timeout_Locking_Time_H, //0x349
    E_T2_STABLE_Timeout_Locking_Time_L, //0x34A

    // Debug
    E_T2_LITE_FEF_FORCEGAIN_FLAG        = 0x380,//0x380

    E_T2_PHASE_TUNING_EN = 0x135,
    E_T2_PHASE_TUNING_NUM = 0x136,

    E_T2_PARAM_NUM,
} E_DVBT2_PARAM;

typedef struct
{
    MAPI_BOOL (*WriteBytes)(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr, MAPI_U16 u16Size, MAPI_U8 *pu8Data);
    MAPI_BOOL (*ReadBytes)(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr,MAPI_U16 u16Size, MAPI_U8 *pu8Data);
}mapi_i2c;


typedef enum
{
    TS_SERIAL_CLK_57p6M = 0,
    TS_SERIAL_CLK_72M = 2,

    TS_CLK_SEL_MAX_NUM,
}E_TS_CLK_SEL;

typedef struct
{
    float    power_db;
    MAPI_U8  agc_val;
}S_MSB_124X_IFAGC_SSI;

typedef struct
{
    float    power_db;
    MAPI_U8  sar3_val;
}S_MSB_124X_RFAGC_SSI;

typedef struct
{
    MAPI_U8     constel;
    MAPI_U8     code_rate;
    float  p_ref;
}S_SSI_PREF;

typedef struct
{
    MAPI_U8       constel;
    MAPI_U8       code_rate;
    float    cn_ref;
}S_SQI_CN_NORDIGP1;

typedef enum
{
    _QPSK_1     = 0x0,
    _16QAM_1    = 0x1,
    _64QAM_1    = 0x2,
}E_CONSTEL;

typedef enum
{
    _CR1Y2_1    = 0x0,
    _CR2Y3_1    = 0x1,
    _CR3Y4_1    = 0x2,
    _CR5Y6_1    = 0x3,
    _CR7Y8_1    = 0x4,
}E_CODERATE;

typedef enum                            // BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
{
    E_DEMOD_BW_17M    = 0x0,
    E_DEMOD_BW_5M      = 0x1,
    E_DEMOD_BW_6M      = 0x2,
    E_DEMOD_BW_7M      = 0x3,
    E_DEMOD_BW_8M      = 0x4,
    E_DEMOD_BW_10M    = 0x5,
}E_DEMOD_CHANNEL_BANDWIDTH;


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

typedef enum
{
    // fw version, check sum,Address Start at 0x00
    C_CHECK_SUM_L = 0x00,
    C_CHECK_SUM_H,
    C_FW_VER_0,
    C_FW_VER_1,
    C_FW_VER_2,

    // Operation Mode Settings,Address Start at 0x20
    C_opmode_auto_scan_sym_rate= 0x20,
    C_opmode_auto_scan_qam,
    C_if_inv_pwm_out_en,

    // Config Params
    C_config_zif= 0x23,
    C_config_fc_l,
    C_config_fc_h,
    C_config_fs_l,
    C_config_fs_h,
    C_config_bw_l,    // 0x28
    C_config_bw_h,
    C_config_bw1_l,
    C_config_bw1_h,
    C_config_bw2_l,
    C_config_bw2_h,
    C_config_bw3_l,
    C_config_bw3_h,
    C_config_qam,     // 0x30
    C_config_cci,
    C_config_ts_serial,
    C_config_ts_clk_rate,
    C_config_ts_out_inv,
    C_config_ts_data_swap,
    C_config_iq_swap,

     //not always changed
     C_opmode_rfagc_en,
     C_opmode_humdet_en,   // 0x38
     C_opmode_dcr_en,
     C_opmode_iqb_en,
     C_opmode_auto_iq,
     C_opmode_auto_rfmax,

     C_opmode_atv_detector_en,

     C_config_rssi,
     C_config_rfmax,

     C_lock_indicator, //0x40, [0] = TR lock HIS , [7] = FEC lock

     C_CFO10_L,
     C_CFO10_H,

     C_SNR100_L,
     C_SNR100_H,
     C_config_spread_span,
     C_config_spread_step,

    MSB124x_DVBC_PARAM_LEN,
    C_phase_tuning_en = 0x135,
    C_phase_tuning_num = 0x136,
} MSB124x_DVBC_Param;


/// DVB-T modulation mode
typedef enum
{
    /// QPSK
    E_DVBT_QPSK     = 0,
    /// 16QAM
    E_DVBT_16_QAM   = 1,
    /// 64QAM
    E_DVBT_64_QAM   = 2,
    /// 256QAM
    E_DVBT_256_QAM  = 3,
    /// invalid indicator
    E_DVBT_INVALID
} EN_DVBT_CONSTEL_TYPE;

/// guard interval enum
typedef enum
{
    /// 1/32
    E_DVBT_GUARD_INTERVAL_1_32  = 0,
    /// 1/16
    E_DVBT_GUARD_INTERVAL_1_16  = 1,
    /// 1/8
    E_DVBT_GUARD_INTERVAL_1_8   = 2,
    /// 1/4
    E_DVBT_GUARD_INTERVAL_1_4   = 3,
    /// 1/28
    E_DVBT_GUARD_INTERVAL_1_128 = 4,
    /// 19/128
    E_DVBT_GUARD_INTERVAL_19_128 = 5,
    /// 19/256
    E_DVBT_GUARD_INTERVAL_19_256 = 6,
    /// invalid indicator
    E_DVBT_GUARD_INTERVAL_INVALID,
} EN_DVBT_GUARD_INTERVAL;

#if 1 // (ENABLE_DVB_T2)
typedef enum
{
    /// lock
    E_MSB_124X_DEMOD_LOCK,
    /// is checking
    E_MSB_124X_DEMOD_CHECKING,
    /// after checking
    E_MSB_124X_DEMOD_CHECKEND,
    /// unlock
    E_MSB_124X_DEMOD_UNLOCK,
    /// NULL state
    E_MSB_124X_DEMOD_NULL,
} EN_MSB_124X_LOCK_STATUS;

#endif
/// DVB-T code rate
typedef enum
{
    /// 1/2
    E_DVBT_CODERATE_1_2 = 0,
    /// 2/3
    E_DVBT_CODERATE_2_3 = 1,
    /// 3/4
    E_DVBT_CODERATE_3_4 = 2,
    /// 5/6
    E_DVBT_CODERATE_5_6 = 3,
    /// 7/8
    E_DVBT_CODERATE_7_8 = 4,
    /// 4/5
    E_DVBT_CODERATE_4_5 = 5,
    /// 6/7
    E_DVBT_CODERATE_6_7 = 6,
    /// 8/9
    E_DVBT_CODERATE_8_9 = 7,
    /// invalid indicator
    E_DVBT_CODERATE_INVALID,
} EN_DVBT_CODE_RATE;
/*
typedef enum
{
    DEMOD_CAB_QAM16,                                                          ///< QAM 16
    DEMOD_CAB_QAM32,                                                          ///< QAM 32
    DEMOD_CAB_QAM64,                                                          ///< QAM 64
    DEMOD_CAB_QAM128,                                                         ///< QAM 128
    DEMOD_CAB_QAM256
} DEMOD_EN_CAB_CONSTEL_TYPE;
*/
/////////////// CONSTANT /////////////////
#define PAGE_WRITE_SIZE         256
#define VERSION_CODE_ADDR       0xFC0
#define VERSION_CODE_SIZE       32

//////////////MSPI Define//////////////////
#define READ_INDEX  0
#define WRITE_INDEX 1
#define CMD_INDEX 0
#define ADDR_INDEX 1
//SSPI COMMAND
#define RIU_W_CMD      0x1A
#define RIU_W1_CMD     0x1D
#define RIU_R_CMD       0x18
#define RIU_R1_CMD      0x1C
#define RIU_RT_CMD      0x11
#define RIU_R1T_CMD      0x15
#define MIU_W_CMD      0x25
#define MIU_R_CMD   0x20
#define MIU_ST_CMD       0x21
#define CFG_W_CMD       0x05
#define CFG_R_CMD       0x00

#if 1//(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBS2)
#define ENABLE_DEMOD1240_GPIO            0
#define DEMOD1240_PIN11_set_HIGH   MSB124X_GPIO_SetLevel(11,TRUE)//18
#define DEMOD1240_PIN11_set_LOW    MSB124X_GPIO_SetLevel(11,FALSE)//13
#define DEMOD1240_PIN13_set_HIGH   MSB124X_GPIO_SetLevel(13,TRUE)//power off
#define DEMOD1240_PIN13_set_LOW    MSB124X_GPIO_SetLevel(13,FALSE)//on

#if 1
#define MDrv_IIC_Write(u16SlaveID, pu8Addr, u8AddrSize, pu8Buf, u16BufSize) MDrv_IIC_WriteBytes(u16SlaveID, u8AddrSize, pu8Addr, u16BufSize, pu8Buf)
#define MDrv_IIC_Read(u16SlaveID, pu8Addr, u8DevId, buf, count) MDrv_IIC_ReadBytes(u16SlaveID, 0, NULL, count, buf)
#define IIC_WRITE             		MDrv_IIC_Write
#define IIC_Read					MDrv_IIC_Read
#define IIC_DEVICEID                0
#endif
#define DEMOD_SLAVE_ID          				DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1
#define DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1    			(((U16)DEMOD_IIC_BUS<<8) | 0xF2)
#define DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_2    			(((U16)DEMOD_IIC_BUS<<8) | 0xA2)
#define MSB124X_DEMOD_IIC 						1
#define MSB124X_SPI_IIC                 		2

MAPI_BOOL DTV_DVB_T2_Get_L1_Parameter(MAPI_U16 * pu16L1_parameter, E_T2_SIGNAL_INFO eSignalInfo);

MS_BOOL DTV_Get_Current_Plp_Id(MS_U8 *plp_id);
//MAPI_BOOL Connect(EN_DEVICE_DEMOD_TYPE enDemodType);
MAPI_U16 DTV_GetSignalQuality(void);

MAPI_BOOL MSB124X_DVBC_Lock(QAM_LOCK_STATUS eStatus);
MAPI_U16 DTV_DVB_C_GetCurrentSymbolRate(void);
MAPI_U8 DTV_DVB_C_GetSignalModulation(void);
MAPI_BOOL DTV_DVB_C_SetFrequency(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth,MAPI_U32 u32SymRate, MAPI_U8 eQAM);
MAPI_BOOL Demod_MSB124X_Connect(EN_DEVICE_DEMOD_TYPE enDemodType);
MAPI_BOOL DTV_Serial_Control(MAPI_BOOL bEnable);
MAPI_BOOL Power_On_Initialization(void);

MAPI_BOOL DTV_GetPacketErr(MAPI_U16 *pu16BitErr);
void DTV_ControlAGCOutput(BOOLEAN bEnable);

MS_BOOL  MSB124X_GPIO_Disable(MS_U8 u8Pin);
MS_BOOL MSB124X_GPIO_SetLevel(MS_U8 u8Pin, MS_BOOL bLevel);
MS_BOOL IIC_Bypass_Mode(MS_BOOL enable);
MS_BOOL  MSB124X_I2C_Channel_Set(MS_U8 ch_num);
MS_BOOL  MSB124X_I2C_Channel_Change(MS_U8 ch_num);
MS_BOOL  ReadReg(MS_U16 u16Addr, MS_U8 *pu8Data);
MS_BOOL WriteReg(MS_U16 u16Addr, MS_U8 u8Data);
MS_BOOL WriteReg2bytes(MS_U16 u16Addr, MS_U16 u16Data);
MS_BOOL WriteRegs(MS_U16 u16Addr, MS_U8* u8pData, MS_U16 data_size);
MS_BOOL  MSB124X_LoadDSPCode(MS_U8  *pu8Buf, MS_U16 u16Len);
MS_BOOL  DTV_DVB_S_SetFrequency(MS_U16 u16CenterFreq, MS_U32 u32SymbolRate_Hz);
MS_U16	MSB124X_DTV_GetSignalStrength(void);
MS_U32	MSB124X_DTV_GetSignalNoiseRatio(void);
MS_U16	MSB124X_DTV_DVBS2_GetSignalQuality(MS_BOOL bDemodType);
MS_BOOL	MSB124X_DTV_GetLock(void);
void DTV_ControlTsOutput(BOOLEAN bEnable);
MS_BOOL MDrv_Demod_GetRollOff(MS_U8 *pRollOff);
MS_BOOL MDrv_CofdmDmd_GetRFOffset(MS_S16 *ps16RFOff);
MS_BOOL MDrv_CofdmDmd_BlindScan_Start(MS_U16 u16StartFreq,MS_U16 u16EndFreq,MS_BOOL bUCMode);
MS_BOOL MDrv_CofdmDmd_BlindScan_NextFreq(MS_BOOL* bBlindScanEnd,MS_U8* u8Progress);
MS_BOOL MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(MS_U8* u8Progress,MS_U8 *u8FindNum);
MS_BOOL MDrv_CofdmDmd_BlindScan_GetChannel(MS_U16 u16ReadStart,MS_U16* u16TPNum,DTVPROGRAMID_M *pTable);
MS_BOOL MDrv_CofdmDmd_BlindScan_Cancel(void);
MS_BOOL MDrv_CofdmDmd_BlindScan_End(void);
MS_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MS_U32 *u32CurrentFeq);

#if (ENABLE_DEMOD_DVBS)
MS_BOOL MSB124X_DiSEqC_Init(void);
MS_BOOL MDrv_DiSEqC_SetTone(MS_BOOL bTone1);
MS_BOOL MDrv_DiSEqC_Set22kOnOff(MS_BOOL b22kOn);
MS_BOOL MDrv_DiSEqC_Get22kOnOff(MS_BOOL* b22kOn);
MS_BOOL MDrv_DiSEqC_SendCmd(MS_U8* pCmd,MS_U8 u8CmdSize);
MS_BOOL MDrv_DiSEqC_SetLNBOut(MS_BOOL bLow);
#endif

MS_BOOL  ReadMailbox(MS_U16 u16Addr, MS_U8* u8Data);
    #if (SUPPORT_UNICABLE)
    MS_BOOL FrontEnd_DVBS2_Set(MS_U32 u32Frequency, MS_U32 u32SymRate, MS_U8 u8Polarity , MS_SAT_PARAM *stSatInfo);
    #endif
#endif

MAPI_BOOL msb1240_flash_mode_en(void);
MAPI_BOOL MDrv_SS_RIU_Write8(MAPI_U16 u16Addr, MAPI_U8 data);
MAPI_BOOL MDrv_SS_RIU_Read8(MAPI_U16 u16Addr, MAPI_U8 *pdata);
MAPI_BOOL MDrv_SS_RIU_Write16(MAPI_U16 u16Addr, MAPI_U16 u16data);
MAPI_BOOL MDrv_SS_MIU_Writes(MAPI_U32 u32Addr, MAPI_U8 *pdata, MAPI_U16 u16Size);
MAPI_BOOL MDrv_SS_MIU_Reads(MAPI_U32 u32Addr, MAPI_U8 *pdata, MAPI_U16 u16Size);

/// Demodulator Interface Structure Define
typedef struct
{
    //Public:Common
    MAPI_BOOL(*Connect)(EN_DEVICE_DEMOD_TYPE enDemodType);
    MAPI_BOOL(*Disconnect)(void);
    void (*Reset)(void);
    MAPI_BOOL(*IIC_Bypass_Mode)(MAPI_BOOL enable);
    MAPI_BOOL(*Power_On_Initialization)(void);
    MAPI_BOOL(*Set_PowerOn)(void);
    MAPI_BOOL(*Set_PowerOff)(void);
    MAPI_BOOL(*Active)(MAPI_BOOL bEnable);
    EN_DEVICE_DEMOD_TYPE(*GetCurrentDemodulatorType)(void);
    MAPI_BOOL(*SetCurrentDemodulatorType)(EN_DEVICE_DEMOD_TYPE enDemodType);
    MAPI_BOOL(*ExtendCmd)(MAPI_U8 SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void *pvParam3);
    //Public:DTV
    MAPI_BOOL(*DTV_SetFrequency)(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth, MAPI_BOOL bPalBG, MAPI_BOOL bLPsel);
    EN_FRONTEND_SIGNAL_CONDITION(*DTV_GetSNR)(void);
    MAPI_U32(*DTV_GetBER)(void);
    MAPI_U16(*DTV_GetSignalQuality)(void);
    MAPI_BOOL(*DTV_GetPostBER)(float *p_postBer);
    MAPI_U16(*DTV_GetSignalStrength)(void);
    MAPI_U16(*DTV_GetCellID)(void);
    MAPI_BOOL(*DTV_Serial_Control)(MAPI_BOOL bEnable);
    MAPI_BOOL(*DTV_IsHierarchyOn)(void);
    //Public:DTV-DVB-T
    EN_MSB_124X_LOCK_STATUS(*DTV_DVB_T_GetLockStatus)(void);
    //Public:DTV-DVB-T2
    MAPI_BOOL(*DTV_DVB_T2_GetPlpBitMap)(MAPI_U8* u8PlpBitMap);
    MAPI_BOOL(*DTV_DVB_T2_GetPlpGroupID)(MAPI_U8 u8PlpID, MAPI_U8* u8GroupID);
    MAPI_BOOL(*DTV_DVB_T2_SetPlpGroupID)(MAPI_U8 u8PlpID, MAPI_U8 u8GroupID);
    MAPI_BOOL(*DTV_DVB_T2_GetCurrentPlpId)(MAPI_U8 *pu8PlpID);
    float (*Si2156_GetRSSILevel)(float *strength_dBm);
    //custom
    MAPI_BOOL (*DTV_GetSNR_F)(float *fSNR);
    MAPI_BOOL bMSB123X_Ready;
    MAPI_BOOL (*DTV_DVB_T2_GetSignalTpsInfo)(MS_U64 *TPS_Info);
    MS_U16 (*DTV_GetLock)(COFDM_LOCK_STATUS_123X eStatus);
} ST_MAPI_DEMODULATOR_FUN;

//--------------------------------------------------------------------------

MAPI_U16 DTV_GetSignalStrength(void);
MAPI_BOOL MSB124X_DTV_GetPostBER(float *p_postBer);


/*@ <IncludeGuardEnd> @*/
#endif // mapi_demodulator_msb123x_I2b28dd03m121c8cf959bmm7254_H
/*@ </IncludeGuardEnd> @*/
