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
 * Class : mapi_demodulator_msb1240
 * File  : mapi_demodulator_msb1240.cpp
 **********************************************************************/

#ifndef MSB124X_C
#define MSB124X_C

/*@ </FileComment ID=1246257763790> @*/
/*@ <Include> @*/
#include <math.h>
#include <string.h>
#include "MsCommon.h"
#include "drvIIC.h"
#include "MsOS.h"
#include "Board.h"
#include "msb124x.h"
#include "drvGPIO.h"
#include "apiDigiTuner.h"
#include "apiDMX.h"
#include "drvPCMCIA.h"
#include "drvSYS.h"
#include "drvDMD_common.h"
#include "drvIIC.h"
#include "debug.h"
#include "MApp_Scan.h"
#include "msAPI_Memory.h"
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"
#include "mapp_si.h"
#include "MApp_GlobalVar.h"
#include "msAPI_Timer.h"
#define formula_A  0
#define formula_B  1
#define formula_OTHERS 100
#define D_CUSTOMER formula_A
#define DIG_DBG_BASE    0x0B00

#if (D_CUSTOMER == formula_A)
#if ((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER) || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER)||(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER)||(FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER))
#else
static float intern_dvb_c_qam_ref_1[] = {-81.5, -78.5, -75.5, -72.5, -69.5, 0.0}; //16q,32q,64q,128q,256q, and others
#endif
static float cn_nordig_p1_DVBC[] = {17.5, 20.5, 23.5, 26.5, 30.5, 0.0}; //16q,32q,64q,128q,256q, and others
#else
static float intern_dvb_c_qam_ref[] = {3.0, 0.0, 0.0, 0.0, 0.0, 80.0}; //16q,32q,64q,128q,256q, and others
#endif

#if ENABLE_S2
#if (FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2012 || FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2011)
#include "AVAILINK_AV2012/drvTuner_AV2012.h"
#elif (FRONTEND_TUNER_S2_TYPE == SHARP_BS2S7VZ7801_TUNER)
#include "drvTuner_Sharp7801.h"
#elif (FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2017)
#include "AVAILINK_AV2017/drvTuner_AV2017.h"
#endif
#endif

MAPI_U8 MSB1240_LIB_U01[]={
#include "msb124x_dvbt2.dat"
};

#define MS124X_DEBUG 1

#if  MS124X_DEBUG
#define PRINTE(p) printf p
#else
#define PRINTE(p)
#endif

/*@ </Include> @*/
/*@ <Definitions> @*/
#define ERR_DEMOD_MSB(x)    //x
#define DBG_DEMOD_MSB(x)     //x
#define DBG_DEMOD_FLOW(x)     //x
#define DBG_GET_SIGNAL(x)           //x
#define DBG_DEMOD_LOAD_I2C(x)      //x
#define DBG_DEMOD_CHECKSUM(x)       //x
#define DBG_FLASH_WP(x)        //x
#define DBG_SIGNAL_TPS(x)     //x

#define DBG_DVBS(x)     x


typedef enum
{
    E_DMD_S2_ZIF_EN = 0x00,
    E_DMD_S2_RF_AGC_EN,
    E_DMD_S2_DCR_EN,
    E_DMD_S2_IQB_EN,
    E_DMD_S2_IIS_EN,
    E_DMD_S2_CCI_EN,
    E_DMD_S2_FORCE_ACI_SELECT,
    E_DMD_S2_IQ_SWAP,//For DVBS2
    E_DMD_S2_AGC_REF_EXT_0,
    E_DMD_S2_AGC_REF_EXT_1,
    E_DMD_S2_AGC_K,
    E_DMD_S2_ADCI_GAIN,
    E_DMD_S2_ADCQ_GAIN,
    E_DMD_S2_SRD_SIG_SRCH_RNG,
    E_DMD_S2_SRD_DC_EXC_RNG,
    E_DMD_S2_FORCE_CFO_0,//0FH
    E_DMD_S2_FORCE_CFO_1,
    E_DMD_S2_DECIMATION_NUM,
    E_DMD_S2_PSD_SMTH_TAP,
    E_DMD_S2_CCI_FREQN_0_L,
    E_DMD_S2_CCI_FREQN_0_H,
    E_DMD_S2_CCI_FREQN_1_L,
    E_DMD_S2_CCI_FREQN_1_H,
    E_DMD_S2_CCI_FREQN_2_L,
    E_DMD_S2_CCI_FREQN_2_H,
    E_DMD_S2_TR_LOPF_KP,
    E_DMD_S2_TR_LOPF_KI,
    E_DMD_S2_FINEFE_KI_SWITCH_0,
    E_DMD_S2_FINEFE_KI_SWITCH_1,
    E_DMD_S2_FINEFE_KI_SWITCH_2,
    E_DMD_S2_FINEFE_KI_SWITCH_3,
    E_DMD_S2_FINEFE_KI_SWITCH_4,//1FH
    E_DMD_S2_PR_KP_SWITCH_0,
    E_DMD_S2_PR_KP_SWITCH_1,
    E_DMD_S2_PR_KP_SWITCH_2,
    E_DMD_S2_PR_KP_SWITCH_3,
    E_DMD_S2_PR_KP_SWITCH_4,
    E_DMD_S2_FS_GAMMA,
    E_DMD_S2_FS_ALPHA0,
    E_DMD_S2_FS_ALPHA1,
    E_DMD_S2_FS_ALPHA2,
    E_DMD_S2_FS_ALPHA3,
    E_DMD_S2_FS_H_MODE_SEL,
    E_DMD_S2_FS_OBSWIN,
    E_DMD_S2_FS_PEAK_DET_TH_L,
    E_DMD_S2_FS_PEAK_DET_TH_H,
    E_DMD_S2_FS_CONFIRM_NUM,
    E_DMD_S2_EQ_MU_FFE_DA,//2FH
    E_DMD_S2_EQ_MU_FFE_DD,
    E_DMD_S2_EQ_ALPHA_SNR_DA,
    E_DMD_S2_EQ_ALPHA_SNR_DD,
    E_DMD_S2_FEC_ALFA,//For DVBS2
    E_DMD_S2_FEC_BETA,//For DVBS2
    E_DMD_S2_FEC_SCALING_LLR,//For DVBS2
    E_DMD_S2_TS_SERIAL,
    E_DMD_S2_TS_CLK_RATE,
    E_DMD_S2_TS_OUT_INV,
    E_DMD_S2_TS_DATA_SWAP,
//------------------------------------------
    E_DMD_S2_FW_VERSION_L,           //0x3A
    E_DMD_S2_FW_VERSION_H,           //0x3B
    E_DMD_S2_CHIP_VERSION,
    E_DMD_S2_FS_L,                         //Frequency
    E_DMD_S2_FS_H,                        //Frequency
    E_DMD_S2_MANUAL_TUNE_SYMBOLRATE_L,    //0x3F
    E_DMD_S2_MANUAL_TUNE_SYMBOLRATE_H,    //
    E_DMD_S2_SYSTEM_TYPE,                //DVBS/S2
    E_DMD_S2_MODULATION_TYPE,            //QPSK/8PSK
    E_DMD_S2_CODERATE,                    //1/2

    E_DMD_S2_UNCRT_PKT_NUM_7_0,
    E_DMD_S2_UNCRT_PKT_NUM_8_15,
    E_DMD_S2_STATE_FLAG,
    E_DMD_S2_SUBSTATE_FLAG,
    E_DMD_S2_HUM_DETECT_FLAG,
    E_DMD_S2_CCI_DETECT_FLAG,
    E_DMD_S2_IIS_DETECT_FLAG,
    E_DMD_S2_OPEN_HUM_VLD_IRQ_FLAG,
    E_DMD_S2_SRD_COARSE_DONE_FLAG,
    E_DMD_S2_SRD_FINE_DONE_FLAG,
    E_DMD_S2_FINEFE_DONE_FLAG,
    E_DMD_S2_REV_FRAME_FLAG,            //0x4F
    E_DMD_S2_DUMMY_FRAME_FLAG,
    E_DMD_S2_PLSC_DONE_FLAG,
    E_DMD_S2_GET_INFO_FROM_FRAME_LENGTH_DONE_FLAG,
    E_DMD_S2_IQ_SWAP_DETECT_FLAG,
    E_DMD_S2_FRAME_ACQUISITION_DONE_FLAG,
    E_DMD_S2_OLCFE_DONE_FLAG,
    E_DMD_S2_FSYNC_FOUND_FLAG,
    E_DMD_S2_FSYNC_FAIL_SEARCH_FLAG,
    E_DMD_S2_FALSE_ALARM_FLAG,
    E_DMD_S2_VITERBI_IN_SYNC_FLAG,
    E_DMD_S2_INT_CODE_RATE_SEARCH_FAIL_FLAG,
    E_DMD_S2_VITERBI_INT_PRE_FLAG,
    E_DMD_S2_BER_WINDOW_END_FLAG,
    E_DMD_S2_PASS_WRONG_INT_FLAG,
    E_DMD_S2_CLK_CNT_OVER_FLAG,
    E_DMD_S2_UNCRT_OVER_FLAG,            //0x5F
    E_DMD_S2_DISEQC_RX_LENGTH,
    E_DMD_S2_DISEQC_INTERRUPT_FLAG,
    E_DMD_S2_DISEQC_RX_FLAG,
    E_DMD_S2_DISEQC_INTERRUPT_STATUS,
    E_DMD_S2_DISEQC_STATUS_FLAG,
    E_DMD_S2_ACI_FIR_SELECTED,            //0x65
    //LOCK
    E_DMD_S2_AGC_LOCK_FLAG,
    E_DMD_S2_DCR_LOCK_FLAG,
    E_DMD_S2_DAGC0_LOCK_FLAG,
    E_DMD_S2_DAGC1_LOCK_FLAG,
    E_DMD_S2_DAGC2_LOCK_FLAG,
    E_DMD_S2_DAGC3_LOCK_FLAG,
    E_DMD_S2_TR_LOCK_FLAG,
    E_DMD_S2_CLCFE_LOCK_FLAG,
    E_DMD_S2_EQ_LOCK_FLAG,
    E_DMD_S2_PR_LOCK_FLAG,                //0x6F
    E_DMD_S2_FSYNC_LOCK_FLAG,
    E_DMD_S2_FSYNC_FAIL_LOCK_FLAG,

      E_DMD_S2_MB_SWUSE12L,                //0x72
      E_DMD_S2_MB_SWUSE12H,
      E_DMD_S2_MB_SWUSE13L,
      E_DMD_S2_MB_SWUSE13H,
      E_DMD_S2_MB_SWUSE14L,
      E_DMD_S2_MB_SWUSE14H,
      E_DMD_S2_MB_SWUSE15L,
      E_DMD_S2_MB_SWUSE15H,
      E_DMD_S2_MB_SWUSE16L,
      E_DMD_S2_MB_SWUSE16H,
    E_DMD_S2_MB_SWUSE17L,
    E_DMD_S2_MB_SWUSE17H,
      E_DMD_S2_MB_SWUSE18L,
      E_DMD_S2_MB_SWUSE18H,                //0x7F
      E_DMD_S2_MB_SWUSE19L,
      E_DMD_S2_MB_SWUSE19H,
      E_DMD_S2_MB_SWUSE1AL,
      E_DMD_S2_MB_SWUSE1AH,
      E_DMD_S2_MB_SWUSE1BL,
      E_DMD_S2_MB_SWUSE1BH,
      E_DMD_S2_MB_SWUSE1CL,
      E_DMD_S2_MB_SWUSE1CH,
      E_DMD_S2_MB_SWUSE1DL,
      E_DMD_S2_MB_SWUSE1DH,
      E_DMD_S2_MB_SWUSE1EL,
    E_DMD_S2_MB_SWUSE1EH,
    E_DMD_S2_MB_SWUSE1FL,
    E_DMD_S2_MB_SWUSE1FH,                 //0x8D

    E_DMD_S2_MB_DMDTOP_DBG_0,
    E_DMD_S2_MB_DMDTOP_DBG_1,            //0x8F
    E_DMD_S2_MB_DMDTOP_DBG_2,
    E_DMD_S2_MB_DMDTOP_DBG_3,
    E_DMD_S2_MB_DMDTOP_DBG_4,
    E_DMD_S2_MB_DMDTOP_DBG_5,
    E_DMD_S2_MB_DMDTOP_DBG_6,
    E_DMD_S2_MB_DMDTOP_DBG_7,
    E_DMD_S2_MB_DMDTOP_DBG_8,
    E_DMD_S2_MB_DMDTOP_DBG_9,
    E_DMD_S2_MB_DMDTOP_DBG_A,
    E_DMD_S2_MB_DMDTOP_DBG_B,

    E_DMD_S2_MB_DMDTOP_SWUSE00L,
    E_DMD_S2_MB_DMDTOP_SWUSE00H,
    E_DMD_S2_MB_DMDTOP_SWUSE01L,
    E_DMD_S2_MB_DMDTOP_SWUSE01H,
    E_DMD_S2_MB_DMDTOP_SWUSE02L,
    E_DMD_S2_MB_DMDTOP_SWUSE02H,        //0x9F
    E_DMD_S2_MB_DMDTOP_SWUSE03L,
    E_DMD_S2_MB_DMDTOP_SWUSE03H,
    E_DMD_S2_MB_DMDTOP_SWUSE04L,
    E_DMD_S2_MB_DMDTOP_SWUSE04H,
    E_DMD_S2_MB_DMDTOP_SWUSE05L,
    E_DMD_S2_MB_DMDTOP_SWUSE05H,
    E_DMD_S2_MB_DMDTOP_SWUSE06L,
    E_DMD_S2_MB_DMDTOP_SWUSE06H,
    E_DMD_S2_MB_DMDTOP_SWUSE07L,
    E_DMD_S2_MB_DMDTOP_SWUSE07H,

    E_DMD_S2_MB_TOP_WR_DBG_90,
    E_DMD_S2_MB_TOP_WR_DBG_91,
    E_DMD_S2_MB_TOP_WR_DBG_92,
    E_DMD_S2_MB_TOP_WR_DBG_93,
    E_DMD_S2_MB_TOP_WR_DBG_94,
    E_DMD_S2_MB_TOP_WR_DBG_95,            //0xAF
    E_DMD_S2_MB_TOP_WR_DBG_96,
    E_DMD_S2_MB_TOP_WR_DBG_97,
    E_DMD_S2_MB_TOP_WR_DBG_98,
    E_DMD_S2_MB_TOP_WR_DBG_99,

    E_DMD_S2_MB_DUMMY_REG_0,
    E_DMD_S2_MB_DUMMY_REG_1,
    E_DMD_S2_MB_DUMMY_REG_2,
    E_DMD_S2_MB_DUMMY_REG_3,
    E_DMD_S2_MB_DUMMY_REG_4,
    E_DMD_S2_MB_DUMMY_REG_5,
    E_DMD_S2_MB_DUMMY_REG_6,
    E_DMD_S2_MB_DUMMY_REG_7,
    E_DMD_S2_MB_DUMMY_REG_8,
    E_DMD_S2_MB_DUMMY_REG_9,
    E_DMD_S2_MB_DUMMY_REG_A,
    E_DMD_S2_MB_DUMMY_REG_B,            //0xBF
    E_DMD_S2_MB_DUMMY_REG_C,
    E_DMD_S2_MB_DUMMY_REG_D,
    E_DMD_S2_MB_DUMMY_REG_E,
    E_DMD_S2_MB_DUMMY_REG_F,
    E_DMD_S2_MB_DUMMY_REG_10,
    E_DMD_S2_MB_DUMMY_REG_11,

    E_DMD_S2_MB_DMDTOP_INFO_01,
    E_DMD_S2_MB_DMDTOP_INFO_02,
    E_DMD_S2_MB_DMDTOP_INFO_03,
    E_DMD_S2_MB_DMDTOP_INFO_04,
    E_DMD_S2_MB_DMDTOP_INFO_05,
    E_DMD_S2_MB_DMDTOP_INFO_06,
    E_DMD_S2_MB_DMDTOP_INFO_07,
    E_DMD_S2_MB_DMDTOP_INFO_08,

    E_DMD_S2_IDLE_STATE_UPDATED,
    E_DMD_S2_LOG_FLAG,                    //0xCF
    E_DMD_S2_LOG_SKIP_INDEX,
    E_DMD_S2_LOCK_COUNT,
    E_DMD_S2_NARROW_STEP_FLAG,
    E_DMD_S2_UNCORRECT_PKT_COUNT,
    E_DMD_S2_DISEQC_INIT_MODE,
    E_DMD_S2_DECIMATE_FORCED,
    E_DMD_S2_SRD_MAX_SRG_FLAG,
    E_DMD_S2_DVBS_OUTER_RETRY,

    E_DMD_S2_FORCED_DECIMATE_FLAG,
    E_DMD_S2_NO_SIGNAL_FLAG,
    E_DMD_S2_SPECTRUM_TRACK_FLAG,
    E_DMD_S2_SRD_LOCAL_SEARCH_FLAG,
    E_DMD_S2_NO_SIGNAL_RATIO_CHECK_FLAG,
    E_DMD_S2_LOW_SR_ACI_FLAG,
    E_DMD_S2_SPECTRUM_TRACKER_TIMEOUT,
    E_DMD_S2_TR_TIMEOUT,                //0xDF
    E_DMD_S2_BALANCE_TRACK,
    E_DMD_S2_GAIN_TILT_FLAG,            //0xE1
    E_DMD_S2_IFAGC_POLARITY,            //0xE2
    E_DMD_S2_SPREAD_SPAN,               //0xE3
    E_DMD_S2_SPREAD_STEP,               //0xE4

    DVBS2_PARAM_LEN                 //0xE5
} DVBS_Param_2;
typedef struct
{
    MAPI_U16 u16_x_10cn;
    MAPI_U8 u8_y_sqi;
}S_SQI_TABLE;
#define MDrv_msb124x_IIC_Write                    MDrv_IIC_Write
#define MDrv_msb124x_IIC_Read                     MDrv_IIC_Read


#define LOAD_CODE_I2C_BLOCK_NUM                 (0x80)
#define SRAM_BASE                               (0x8000)
#define SAMPLING_RATE                           (96000)
#define MSB124X_DEMOD_WAIT_TIMEOUT              (6000)
#define MSB124X_TUNER_WAIT_TIMEOUT              (50)
#define MSB124X_TS_DATA_SWAP                    (1)
#define MSB1240_DVBS_TUNER_WAIT_TIMEOUT         (50)
#define MSB1240_DEMOD_WAIT_TIMEOUT              (5000)
#define MSB1240_DVBS_ADCPLL_IQ_SWAP             0 //1 is ADCPLL IQ swap enable, for customer issue.

#define resetDemodTime                          50
#define waitFlashTime                           50
#define SDRAM_DATA_CHECK                         0
#define TIMING_VERIFICATION                      0
#define SPI_DEVICE_BUFFER_SIZE                   256
#define SDRAM_BASE                               0x5000

// msb1240 flash size: 1Mbits
#define MAX_MSB1240_LIB_LEN                      262144
#define FLASH_WP_ENABLE                          1

#define MSB1240_BOOT                              0x01
#define MSB1240_DVBT2                             0x02
#define MSB1240_DVBT                              0x04
#define MSB1240_DVBC                              0x08
#define MSB1240_DVBS                                           0x10
#define MSB1240_ALL                               0x0F

#define MSB1240_BOOT_START_ADDR                 0x00000
#define MSB1240_BOOT_END_ADDR                   0x007FF
#define MSB1240_DVBT2_P1_START_ADDR             0x00800
#define MSB1240_DVBT2_P1_END_ADDR               0x087FF
#define MSB1240_DVBT2_P2_START_ADDR             0x08800
#define MSB1240_DVBT2_P2_END_ADDR               0x0FFFF
#define MSB1240_DVBT_START_ADDR                 0x10000
#define MSB1240_DVBT_END_ADDR                   0x17FFF
#define MSB1240_DVBC_START_ADDR                 0x18000
#define MSB1240_DVBC_END_ADDR                   0x1FFFF
#define MSB1240_DVBS_P1_START_ADDR                 0x20000
#define MSB1240_DVBS_P1_END_ADDR                     0x27FFF
#define MSB1240_DVBS_P2_START_ADDR                 0x28000
#define MSB1240_DVBS_P2_END_ADDR                     0x28FFF


#define MSB1240_WINDOWS_BASE                       0x100   // unit: 4K  // 0x100*4k base = 0x100000(1M)
#define MSB1240_BOOT_WINDOWS_OFFSET                MSB1240_WINDOWS_BASE    // 1M
#define MSB1240_DVBT2_P2_WINDOWS_OFFSET            (MSB1240_WINDOWS_BASE + 0x08)   // 1M+32k
#define MSB1240_DVBT2_P1_WINDOWS_OFFSET            (MSB1240_DVBT2_P2_WINDOWS_OFFSET + 0x08)   // 1M+64k
#define MSB1240_DVBT_WINDOWS_OFFSET                (MSB1240_DVBT2_P1_WINDOWS_OFFSET + 0x08)   // 1M+96k
#define MSB1240_DVBC_WINDOWS_OFFSET                (MSB1240_DVBT_WINDOWS_OFFSET + 0x08)   // 1M+128k
#define MSB1240_DVBS_P2_WINDOWS_OFFSET     (MSB1240_DVBC_WINDOWS_OFFSET + 0x08)       // 1M+128k+32k
#define MSB1240_DVBS_P1_WINDOWS_OFFSET     (MSB1240_DVBS_P2_WINDOWS_OFFSET + 0x08)    // 1M+128k+64k

#define MSB1240_MAX_FLASH_ON_RETRY_NUM             3

#define MSB1240_SW_SLEEP_MODE_EN                 0

#define TR_TIME_OUT_WITH_FIX_SYMBOL_RATE         1000
#define MSB1240_TOP_WR_DBG_90_ADDR  0x0990
#define MSB1240_TOP_WR_DBG_92_ADDR  0x0992
#define MSB1240_TOP_WR_DBG_93_ADDR  0x0993
#define MSB1240_DIG_DBG_5_ADDR  0x0B55
#define MSB1240_DIG_DBG_6_ADDR  0x0B56
#define REG_TOP_95 0x0995
#define REG_TOP_96 0x0996
#define REG_TOP_97 0x0997
#define REG_DBG_2 0x0B52
#define REG_DBG_3 0x0B53

// Mail box register address
#define REG_FSM_EN                               0x0CB8
#define REG_MB_CNTL                             0x0C80
#define REG_MB_ADDR_L                           0x0C84
#define REG_MB_ADDR_H                           0x0C82
#define REG_MB_DATA                             0x0C86

#define DBG_DUMP_LOAD_DSP_TIME 0
#define MDrv_Timer_Delayms OS_DELAY_TASK
#define MDrv_Timer_GetTime0 OS_SYSTEM_TIME

#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ENABLE 0
#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2_ENABLE 0
#define MSPI_ENABLE 0

#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ENABLE==1)
#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C  1
#else
#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C  0
#endif
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2_ENABLE==1)
#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2  1
#else
#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2  0
#endif
#define LOAD_DSP_CODE_FROM_MAIN_CHIP_I2C 0
#if (MSPI_ENABLE==1)
#define USE_SPI_LOAD_TO_SDRAM  1
#else //I2C
#define USE_SPI_LOAD_TO_SDRAM  0
#endif


typedef enum{
    DEMOD_SAT_QPSK_MSB1240,     ///< QPSK
    DEMOD_SAT_8PSK_MSB1240,     ///< 8PSK
    DEMOD_SAT_QAM16_MSB1240     ///< QAM16
} DEMOD_EN_SAT_CONSTEL_TYPE_MSB1240;



#if (LOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
static MS_U8 g_WO_SPI_FLASH = 1;
#else
static MS_U8 g_WO_SPI_FLASH = 0;
#endif


/*@ </Definitions> @*/
MAPI_U8 u8DeviceBusy = 0;
MAPI_U8 gu8ChipRevId = 0;
//MAPI_U8 gu8DemoDynamicI2cAddress = DEMOD_DYNAMIC_SLAVE_ID_1; //0x32;//Default
MAPI_BOOL FECLock = MAPI_FALSE;
MAPI_BOOL gbTVAutoScanEn = MAPI_FALSE; //init value=MAPI_FALSE, follow with auto/manual scan
EN_DEVICE_DEMOD_TYPE m_enCurrentDemodulator_Type = E_DEVICE_DEMOD_DVB_T;
EN_DEVICE_DEMOD_TYPE m_enPreDemodulator_Type = E_DEVICE_DEMOD_NULL;

#define usleep(x)                     MsOS_DelayTask(x/1000)
static MAPI_U32  u32ChkScanTimeStart = 0;

#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2 == 1)
static MAPI_BOOL bPreload_T2_en = MAPI_FALSE;
static MAPI_BOOL bSTR_mode_en = MAPI_FALSE;
#endif
static MAPI_U32  g_u32Frequency = 0;
static MAPI_BOOL p1_ever_lock_flag = 0;
static MAPI_U8   g_u8_bw = 0;
static float g_msb1233c_fSNR = 0.0;
static float g_min_ber = 5.19e-7; // [0.6/(128*188*8*6)]

// 0: Normal mode.
// 1: 1)reg r/w ok. 2)ADC powerdown. 3)MCU rst.
// 2: sleep mode.
static MAPI_U8   g_u8_msb1240_sleep_mode_status = 0;
// 0: Normal mode, ADC on.
// 1: ADC off.
static MAPI_U8  g_u8_msb1240_adc_mode_status = 0;
#if(TIMING_VERIFICATION == 1)
static MAPI_U32 tmm_1 = 0x00;
static MAPI_U32 tmm_2 = 0x00;
static MAPI_U32 tmm_3 = 0x00;
static MAPI_U32 tmm_4 = 0x00;
static MAPI_U32 tmm_5 = 0x00;
static MAPI_U32 tmm_6 = 0x00;
static MAPI_U32 tmm_7 = 0x00;
static MAPI_U32 tmm_8 = 0x00;
static MAPI_U32 tmm_9 = 0x00;
static MAPI_U32 tmm_10 = 0x00;
static MAPI_U32 tmm_11 = 0x00;
static MAPI_U32 tmm_12 = 0x00;
static MAPI_U32 tmm_13 = 0x00;
static MAPI_U32 tmm_14 = 0x00;
static MAPI_U32 tmm_15 = 0x00;
static MAPI_U32 tmm_16 = 0x00;
static MAPI_U32 tmm_17 = 0x00;
static MAPI_U32 tmm_18 = 0x00;
static MAPI_U32 tmm_19 = 0x00;
static MAPI_U32 tmm_20 = 0x00;
#define GIVE_ME_TIME MsOS_GetSystemTime();
#endif
static MAPI_BOOL bDoReset = FALSE;
MAPI_U32 u32StartTime = 0;
// MAPI_U8 gQamVal;
// ONLY wo flash procedure used.
static MS_U8 g_sdram_code = 0x0;
static MS_U8 g_sram_code  = 0x0;
static MS_U8 g_msb1240_plp_id   = 0xff;
static MS_U8 g_msb1240_group_id = 0xff;
static MS_U8 u8_g_pid0_timeout_flag = 0;
static float g_msb1240_fSNR = 0.0;
#if (ENABLE_S2)
static  MS_BOOL _bDemodType=FALSE;
static  MS_U16 _u16BlindScanStartFreq =0;
static  MS_U16 _u16BlindScanEndFreq   =0;
static  MS_U16 _u16TunerCenterFreq    =0;
static  MS_U16 _u16ChannelInfoIndex    =0;
//Debug Only+
static  MS_U16 _u16NextCenterFreq=0;
static  MS_U16 _u16LockedSymbolRate=0;
static  MS_U16 _u16LockedCenterFreq=0;
static  MS_U16  _u16PreLockedHB=0;
static  MS_U16  _u16PreLockedLB=0;
static  MS_U16 _u16CurrentSymbolRate=0;
static  MS_S16 _s16CurrentCFO=0;
static  MS_U16 _u16CurrentStepSize=0;
static  MS_U8  _u8ToneBurstFlag=0;
static  MS_U16 _u16ChannelInfoArray[2][1000];
MS_U16 u16_INTERN_DVBS_Version;
#if MSB124X_TS_DATA_SWAP
static MS_BOOL _bTSDataSwap=FALSE;
#endif
#endif
static  MS_U32                      _u32CurrentSR=0;
static  MS_U32                      _u32LocktimeStart=0;
#define     C_TS_SPREAD_SPAN          0 //Unit: kHz (0: disable; default: 40 kHz)
#define     C_TS_SPREAD_STEP_SIZE    0.0 //Unit: percent(%) (0: disable; default: 3.0 %)
static MAPI_BOOL bPower_init_en = MAPI_FALSE;
//configure

#define TS_CLK_INVERT 1
#define TS_DATA_SWAP 0
#define TS_DATA_SERIAL 1

#define MSB1240_SELECT_IF_INPUT         0  // 0:dvbt_I, 1:dvbs_I

//--------------------------------------------------------------------- for DVB-T2
// BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
#define T2_BW_VAL                       0x04
// FC: FC = FS = 5000 = 0x1388                 (5.0MHz IF)
#define T2_FC_L_VAL                        0x88    // 5.0M
#define T2_FC_H_VAL                        0x13
#define T2_TS_SERIAL_VAL                TS_DATA_SERIAL
#define T2_TS_CLK_RATE_VAL              0x06
#define T2_TS_OUT_INV_VAL               TS_CLK_INVERT
#define T2_TS_DATA_SWAP_VAL             TS_DATA_SWAP
#define T2_TS_ERR_POL_VAL               0x00
#define T2_IF_AGC_INV_PWM_EN_VAL         0x00
#define T2_TS_SPREAD_SPAN          0 //Unit: kHz (0: disable; default: 40 kHz)
#define T2_TS_SPREAD_STEP_SIZE    0.0 //Unit: percent(%) (0: disable; default: 3.0 %)

#define T2_TS_PHASE_TUNING_EN     0x00 //0: disable; 1: enable
#define T2_TS_PHASE_TUNING_NUM    0x00 //Unit: degree  <range: 0x00 ~ 0x1F>

static MAPI_U8   T2_TS_SERIAL         =     T2_TS_SERIAL_VAL;
//--------------------------------------------------------------------- for DVB-T
//configure
#define T_FC_L                            0xc0
#define T_FC_H                            0x12
#define T_FS_L                            0x80
#define T_FS_H                            0x70
#define T_BW                              0x03
#define T_IQ_SWAP                         0x00
#define T_SERIAL_TS                       TS_DATA_SERIAL
#define T_TS_CLK_SEL                      0x06
#define T_TS_OUT_INV                      TS_CLK_INVERT
#define T_TS_DATA_SWAP                    TS_DATA_SWAP
#define T_IF_INV_PWM_OUT_EN              0x00
#define T_TS_SPREAD_SPAN          0 //Unit: kHz (0: disable; default: 40 kHz)
#define T_TS_SPREAD_STEP_SIZE    0.0 //Unit: percent(%) (0: disable; default: 3.0 %)

#define T_TS_PHASE_TUNING_EN     0x00 //0: disable; 1: enable
#define T_TS_PHASE_TUNING_NUM    0x00 //Unit: degree  <range: 0x00 ~ 0x1F>

static MAPI_U8   T_SERIAL_TS_VAL     =     T_SERIAL_TS;
MS_U8 MSB1240_DVBT_DSPREG_TABLE[] =
{
    T_BW,  T_FC_L,  T_FC_H,  T_SERIAL_TS,  T_TS_CLK_SEL,  T_TS_OUT_INV,  T_TS_DATA_SWAP,
    T_IQ_SWAP,  T_IF_INV_PWM_OUT_EN,
    T_TS_SPREAD_SPAN,T_TS_SPREAD_STEP_SIZE,T_TS_PHASE_TUNING_EN,T_TS_PHASE_TUNING_NUM
};
//--------------------------------------------------------------------- for DVB-C
#define     C_AUTO_SCAN_SYM_RATE        1
#define     C_AUTO_SCAN_QAM                1
#define     C_IF_INV_PWM_OUT_EN         0
#define     C_ZIF                       0
#define     C_FC_L                      0x88
#define     C_FC_H                      0x13
#define     C_FS_L                      0xC0
#define     C_FS_H                      0x5D
#define     C_BW_L                      0xDB
#define     C_BW_H                      0x1A
#define     C_BW1_L                     0xF4
#define     C_BW1_H                     0x1A
#define     C_BW2_L                     0xDB
#define     C_BW2_H                     0x1A
#define     C_BW3_L                     0x58
#define     C_BW3_H                     0x1B
#define     C_QAM                       2
#define     C_CCI                       0
#define     C_TS_SERIAL                 TS_DATA_SERIAL
#define     C_TS_CLK_RATE               6
#define     C_TS_OUT_INV                TS_CLK_INVERT
#define     C_TS_DATA_SWAP              TS_DATA_SWAP
#define     C_IQ_SWAP                   0
#define     C_TS_SPREAD_SPAN          0 //Unit: kHz (0: disable; default: 40 kHz)
#define     C_TS_SPREAD_STEP_SIZE    0.0 //Unit: percent(%) (0: disable; default: 3.0 %)

#define     C_TS_PHASE_TUNING_EN     0x00 //0: disable; 1: enable
#define     C_TS_PHASE_TUNING_NUM    0x00 //Unit: degree  <range: 0x00 ~ 0x1F>
//--------------------------------------------------------------------- for DVB-SS2

#define     S_TS_SPREAD_SPAN          0 //Unit: kHz (0: disable; default: 40 kHz)
#define     S_TS_SPREAD_STEP_SIZE    0.0 //Unit: percent(%) (0: disable; default: 3.0 %)
static MAPI_U8 S_TS_Output_VAL             = TS_DATA_SERIAL;
static MAPI_BOOL S_TS_DataSwap_VAL         = TS_DATA_SWAP;
static MAPI_BOOL S_TS_clk_inv_VAL         = TS_CLK_INVERT;


MS_U8 MSB1240_DVBC_DSPREG_TABLE[] =
{
    C_AUTO_SCAN_SYM_RATE,  //0x20
    C_AUTO_SCAN_QAM,
    C_IF_INV_PWM_OUT_EN,
    C_ZIF,
    C_FC_L,
    C_FC_H,
    C_FS_L,
    C_FS_H,

    C_BW_L,             //0x28
    C_BW_H,
    C_BW1_L,
    C_BW1_H,
    C_BW2_L,
    C_BW2_H,
    C_BW3_L,
    C_BW3_H,

    C_QAM,               //0x30
    C_CCI,
    C_TS_SERIAL,
    C_TS_CLK_RATE,
    C_TS_OUT_INV,
    C_TS_DATA_SWAP,
    C_IQ_SWAP,
};

static S_DVBT2_SQI_CN_NORDIGP1 g_msb1240_dvbt2_sqi_cn_nordigp1[] =
{
    {_T2_QPSK, _T2_CR1Y2, 3.5},
    {_T2_QPSK, _T2_CR3Y5, 4.7},
    {_T2_QPSK, _T2_CR2Y3, 5.6},
    {_T2_QPSK, _T2_CR3Y4, 6.6},
    {_T2_QPSK, _T2_CR4Y5, 7.2},
    {_T2_QPSK, _T2_CR5Y6, 7.7},

    {_T2_16QAM, _T2_CR1Y2, 8.7},
    {_T2_16QAM, _T2_CR3Y5, 10.1},
    {_T2_16QAM, _T2_CR2Y3, 11.4},
    {_T2_16QAM, _T2_CR3Y4, 12.5},
    {_T2_16QAM, _T2_CR4Y5, 13.3},
    {_T2_16QAM, _T2_CR5Y6, 13.8},

    {_T2_64QAM, _T2_CR1Y2, 13.0},
    {_T2_64QAM, _T2_CR3Y5, 14.8},
    {_T2_64QAM, _T2_CR2Y3, 16.2},
    {_T2_64QAM, _T2_CR3Y4, 17.7},
    {_T2_64QAM, _T2_CR4Y5, 18.7},
    {_T2_64QAM, _T2_CR5Y6, 19.4},

    {_T2_256QAM, _T2_CR1Y2, 17.0},
    {_T2_256QAM, _T2_CR3Y5, 19.4},
    {_T2_256QAM, _T2_CR2Y3, 20.8},
    {_T2_256QAM, _T2_CR3Y4, 22.9},
    {_T2_256QAM, _T2_CR4Y5, 24.3},
    {_T2_256QAM, _T2_CR5Y6, 25.1},
    {_T2_QAM_UNKNOWN, _T2_CR_UNKNOWN, 0.0}
};

static  DMD_SQI_CN_NORDIGP1 SqiCnNordigP1[] =
{
{_QPSK,  _CR1Y2, 5.1 },
{_QPSK,  _CR2Y3, 6.9 },
{_QPSK,  _CR3Y4, 7.9 },
{_QPSK,  _CR5Y6, 8.9 },
{_QPSK,  _CR7Y8, 9.7 },
{_16QAM, _CR1Y2, 10.8},
{_16QAM, _CR2Y3, 13.1},
{_16QAM, _CR3Y4, 14.6},
{_16QAM, _CR5Y6, 15.6},
{_16QAM, _CR7Y8, 16.0},
{_64QAM, _CR1Y2, 16.5},
{_64QAM, _CR2Y3, 18.7},
{_64QAM, _CR3Y4, 20.2},
{_64QAM, _CR5Y6, 21.6},
{_64QAM, _CR7Y8, 22.5},
};

MAPI_U8 u8MSB1240ChipRev = 0;
MAPI_U8* MSB1240_LIB = MSB1240_LIB_U01;
MAPI_U32 u32SizeOfMSB1240_LIB = sizeof(MSB1240_LIB_U01);
MAPI_BOOL msb1240_flash_mode_en(void);
MAPI_BOOL msb1240_flash_boot_ready_waiting(MAPI_U8 *ptimeout);
extern MAPI_BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks);
//extern MAPI_BOOL MDrv_DVBS_Tuner_Initial(void);
extern MAPI_BOOL MDrv_DVBS_Tuner_CheckLock(void);
extern MAPI_BOOL MDrv_DVBS_Tuner_CheckLock(void);
extern float MDrv_DVBS_Tuner_Get_RSSI(MS_U16);
MAPI_BOOL SetCurrentDemodulatorType(EN_DEVICE_DEMOD_TYPE enDemodType);

#if (ENABLE_S2)
extern MS_SAT_PARAM sat_info;
extern BLINDSCAN_STATUS _enBlindScanStatus;
#endif
#if(TIMING_VERIFICATION == 1)
static void show_timer(void)
{
    printf("***************************\n");
    printf("[tmm1]t2-t1 = %ld (%ld - %ld)\n",tmm_2-tmm_1,tmm_2,tmm_1);
    printf("[tmm2]t4-t3 = %ld (%ld - %ld)\n",tmm_4-tmm_3,tmm_4,tmm_3);
    printf("[tmm3]t6-t5 = %ld (%ld - %ld)\n",tmm_6-tmm_5,tmm_6,tmm_5);
    printf("[tmm4]t8-t7 = %ld (%ld - %ld)\n",tmm_8-tmm_7,tmm_8,tmm_7);
    printf("[tmm5]t10-t9 = %ld (%ld - %ld)\n",tmm_10-tmm_9,tmm_10,tmm_9);
    printf("[tmm6]t12-t11 = %ld (%ld - %ld)\n",tmm_12-tmm_11,tmm_12,tmm_11);
    printf("[tmm7]t14-t13 = %ld (%ld - %ld)\n",tmm_14-tmm_13,tmm_14,tmm_13);
    printf("[tmm8]t16-t15 = %ld (%ld - %ld)\n",tmm_16-tmm_15,tmm_16,tmm_15);
    printf("[tmm9]t18-t17 = %ld (%ld - %ld)\n",tmm_18-tmm_17,tmm_18,tmm_17);
    printf("[tmm10]t20-t19 = %ld (%ld - %ld)\n",tmm_20-tmm_19,tmm_20,tmm_19);
    printf("[tmm11]lock_time# = %ld (%ld - %ld)\n",tmm_14-u32StartTime,tmm_14,u32StartTime);
    printf("[tmm12]lock-setf = %ld (%ld - %ld)\n",tmm_14-tmm_11,tmm_14,tmm_11);
    printf("[tmm13]lock-loaddsp = %ld (%ld - %ld)\n",tmm_14-tmm_9,tmm_14,tmm_9);
    printf("***************************\n");
}
#endif
/*@ <Operation ID=I2b28dd03m121c8cf959bmm6ff4> @*/
MAPI_BOOL WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    //DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = MAPI_TRUE;
    MS_U8 Data[6];
    if (g_u8_msb1240_sleep_mode_status > 1)
    {
        printf("%s, %s, %d, MSB1240 is sleeping, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
        return FALSE;
    }
#if USE_SPI_LOAD_TO_SDRAM
    bRet = MDrv_SS_RIU_Write8(u16Addr, u8Data);
#else
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2 == 1)
    mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1);
    bRet &= iptr->SetSpeed(350);
#endif
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) & 0xff;
    Data[4] = u16Addr & 0xff;
    Data[5] = u8Data;
    Data[0] = 0x35;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 1);
    Data[0] = 0x10;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 6);
    Data[0] = 0x34;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 1);
#endif
    return bRet;
}

MAPI_BOOL WriteRegs(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size)
{
    MAPI_BOOL bRet = MAPI_TRUE;
    MAPI_U16  u16index = 0;
    MS_U8 Data[LOAD_CODE_I2C_BLOCK_NUM+5];
    if (g_u8_msb1240_sleep_mode_status > 1)
    {
        printf("%s, %s, %d, MSB1240 is sleeping, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
        return FALSE;
    }

#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2 == 1)
    bRet &= iptr->SetSpeed(350);
#endif
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) &0xff;
    Data[4] = u16Addr &0xff;
    for(u16index = 0; u16index < data_size ; u16index++)
    {
        Data[5+u16index] = u8pData[u16index];
    }
    Data[0] = 0x35;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 1);
    Data[0] = 0x10;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 5 + data_size);
    Data[0] = 0x34;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 1);

    return bRet;
}

MAPI_BOOL WriteReg2bytes(MAPI_U16 u16Addr, MAPI_U16 u16Data)
{
    MAPI_BOOL ret = true;
#if USE_SPI_LOAD_TO_SDRAM
    ret &= MDrv_SS_RIU_Write16(u16Addr, u16Data);
#else
    ret &= WriteReg(u16Addr, (MAPI_U8)u16Data&0x00ff);
    ret &= WriteReg(u16Addr + 0x0001, (MAPI_U8)(u16Data>>8)&0x00ff);
#endif
    return ret;
}

/*@ </Operation ID=I2b28dd03m121c8cf959bmm6ff4> @*/
/*@ <Operation ID=I2b28dd03m121c8cf959bmm6fcf> @*/
MAPI_BOOL ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data)
{
    MAPI_BOOL bRet = MAPI_TRUE;
    MS_U8 Data[5];
    if (g_u8_msb1240_sleep_mode_status > 1)
    {
        printf("%s, %s, %d, MSB1240 is sleeping, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
        return FALSE;
    }
#if USE_SPI_LOAD_TO_SDRAM
    bRet = MDrv_SS_RIU_Read8(u16Addr, pu8Data);
#else
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) &0xff;
    Data[4] = u16Addr &0xff;

    Data[0] = 0x35;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 1);
    Data[0] = 0x10;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 5);
    bRet &=MDrv_msb124x_IIC_Read(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0,0, pu8Data, 1);
    Data[0] = 0x34;
    bRet &=MDrv_msb124x_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, 0, 0, Data, 1);
#endif
    return bRet;
}

MAPI_BOOL WriteDspReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    MAPI_U8     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;
    if (g_u8_msb1240_sleep_mode_status > 1)
    {
        printf("%s, %s, %d, MSB1240 is sleeping, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
        return FALSE;
    }
    if (g_u8_msb1240_adc_mode_status != 0)
    {
        printf("%s, %s, %d, MSB1240 ADC is off, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
        return FALSE;
    }
#if USE_SPI_LOAD_TO_SDRAM
    status &= MDrv_SS_RIU_Write8(REG_MB_DATA, u8Data);
    status &= MDrv_SS_RIU_Write16(REG_MB_ADDR_L, u16Addr);
    status &= MDrv_SS_RIU_Write8(REG_MB_CNTL, 0x04);
    do
    {
        status &= MDrv_SS_RIU_Read8(REG_MB_CNTL, &cntl);
        if (cntr++ > 0x7ff)
        {
            ERR_DEMOD_MSB(printf("MSB1240_MB_WRITE_FAILURE\n"));
            return FALSE;
        }
    }
    while(cntl != 0xff);
#else
    status &= WriteReg(REG_MB_DATA, u8Data);
    status &= WriteReg(REG_MB_ADDR_H, (MAPI_U8)(u16Addr >> 8));
    status &= WriteReg(REG_MB_ADDR_L, (MAPI_U8)(u16Addr));
    status &= WriteReg(REG_MB_CNTL, 0x04);
    do
    {
        status &= ReadReg(REG_MB_CNTL, &cntl);
        if (cntr++ > 0x7ff)
        {
            ERR_DEMOD_MSB(printf("MSB1240_MB_WRITE_FAILURE\n"));
            return false;
        }
    }
    while(cntl != 0xff);
#endif
    return status;
}

MAPI_BOOL ReadDspReg(MAPI_U16 u16Addr, MAPI_U8* pData)
{
    MAPI_U8     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;
    if (g_u8_msb1240_sleep_mode_status > 1)
    {
        printf("%s, %s, %d, MSB1240 is sleeping, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
        return FALSE;
    }
    if (g_u8_msb1240_adc_mode_status != 0)
    {
        printf("%s, %s, %d, MSB1240 ADC is off, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
        return FALSE;
    }
#if USE_SPI_LOAD_TO_SDRAM
    status &= MDrv_SS_RIU_Write16(REG_MB_ADDR_L, u16Addr);
    status &= MDrv_SS_RIU_Write8(REG_MB_CNTL, 0x03);
    do
    {
        status &= MDrv_SS_RIU_Read8(REG_MB_CNTL, &cntl);
        if (cntr++ > 0x7ff)
        {
            ERR_DEMOD_MSB(printf("MSB1240_MB_READ_FAILURE\n"));
            return FALSE;
        }
    }
    while(cntl != 0xff);
    status &= MDrv_SS_RIU_Read8(REG_MB_DATA, pData);
#else
    status &= WriteReg(REG_MB_ADDR_H, (MAPI_U8)(u16Addr >> 8));
    status &= WriteReg(REG_MB_ADDR_L, (MAPI_U8)(u16Addr));
    status &= WriteReg(REG_MB_CNTL, 0x03);
    do
    {
        status &= ReadReg(REG_MB_CNTL, &cntl);
        if (cntr++ > 0x7ff)
        {
            ERR_DEMOD_MSB(printf("MSB1240_MB_READ_FAILURE\n"));
            return false;
        }
    }
    while(cntl != 0xff);
#endif
    status &= ReadReg(REG_MB_DATA, pData);
    return status;
}

static float Log10Approx(float flt_x)
{
    MS_U32 u32_temp = 1;
    MS_U8 indx = 0;
    do
    {
        u32_temp = u32_temp << 1;
        if (flt_x < (float)u32_temp)
            break;
    }
    while (++indx < 32);
    return (float)0.3 *indx;
}

void mapi_gpio_msb124x_On(void)
{
    Demodulator_ON();
    printf("MSB124x Demodulator_ON\n");
}
void mapi_gpio_msb124x_Off(void)
{
    Demodulator_OFF();
    printf("MSB124x mapi_gpio_msb124x_Off\n");
}
typedef struct
{
    void (*SetOn)(void);
    void (*SetOff)(void);
}mapi_gpio;

mapi_gpio GPIOhandler;
mapi_gpio* mapi_gpio_GetGPIO_Dev(void)
{
    mapi_gpio *handler=&GPIOhandler;
    handler->SetOn= mapi_gpio_msb124x_On;
    handler->SetOff = mapi_gpio_msb124x_Off;
    return handler;
}

MAPI_BOOL mapi_i2c_WriteBytes_demod(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr, MAPI_U16 u16Size, MAPI_U8 *pu8Data)
{
    BOOLEAN bRet = 0;
    bRet = MDrv_IIC_WriteBytes(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, u8AddrSize, pu8Addr, u16Size, pu8Data);
    return bRet;
}

MAPI_BOOL mapi_i2c_ReadBytes_demod(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr,MAPI_U16 u16Size, MAPI_U8 *pu8Data)
{
    BOOLEAN bRet = 0;
    bRet = MDrv_IIC_ReadBytes(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_1, u8AddrSize, pu8Addr, u16Size, pu8Data);
    return bRet;
}

MAPI_BOOL mapi_i2c_WriteBytes_spi(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr, MAPI_U16 u16Size, MAPI_U8 *pu8Data)
{
    BOOLEAN bRet = 0;
    bRet = MDrv_IIC_WriteBytes(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_2, u8AddrSize, pu8Addr, u16Size, pu8Data);
    return bRet;
}

MAPI_BOOL mapi_i2c_ReadBytes_spi(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr,MAPI_U16 u16Size, MAPI_U8 *pu8Data)
{
    BOOLEAN bRet = 0;
    bRet = MDrv_IIC_ReadBytes(DEMOD_DYNAMIC_SLAVE_ID_MSB_124X_2, u8AddrSize, pu8Addr, u16Size, pu8Data);
    return bRet;
}

mapi_i2c DemodI2Chandler;
mapi_i2c SpiI2Chandler;
mapi_i2c* mapi_i2c_GetI2C_Dev(MAPI_U32 u32gID)
{
    mapi_i2c *handler;
    switch(u32gID)
    {
        default:
            printf("iic device not supported\n");
        case MSB124X_DEMOD_IIC:
            handler=&DemodI2Chandler;
            handler->WriteBytes= mapi_i2c_WriteBytes_demod;
            handler->ReadBytes = mapi_i2c_ReadBytes_demod;
            break;
        case MSB124X_SPI_IIC:
            handler=&SpiI2Chandler;
            handler->WriteBytes= mapi_i2c_WriteBytes_spi;
            handler->ReadBytes = mapi_i2c_ReadBytes_spi;
            break;
    }
    return handler;
}

MAPI_BOOL I2C_CH_Reset(MAPI_U8 ch_num)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8         data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]I2C_CH_Reset, CH=0x%x\n",ch_num));
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);

    // 8'hb2(SRID)->8,h53(PWD1)->8,h45(PWD2)->8,h52(PWD3)->8,h44(PWD4)->8,h42(PWD5)
    data[0] = 0x53;
    iptr->WriteBytes(0, NULL, 5, data);

    // 8'hb2(SRID)->8,h71(CMD)    //TV.n_iic_
    data[0] = 0x71;
    iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h81(CMD)    //TV.n_iic_sel_b0
    data[0] = ((ch_num & 0x01) != 0)? 0x81 : 0x80;
    iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h83(CMD)    //TV.n_iic_sel_b1
    data[0] = ((ch_num & 0x02) != 0)? 0x83 : 0x82;
    iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h84(CMD)    //TV.n_iic_sel_b2
    data[0] = ((ch_num & 0x04) != 0)? 0x85 : 0x84;
    iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h53(CMD)    //TV.n_iic_ad_byte_en2, 32bit read/write
    data[0] = 0x53;
    iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h7f(CMD)    //TV.n_iic_sel_use_cfg
    data[0] = 0x7f;
    iptr->WriteBytes(0, NULL, 1, data);

/*
    // 8'hb2(SRID)->8,h35(CMD)    //TV.n_iic_use
    data[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h71(CMD)    //TV.n_iic_Re-shape
    data[0] = 0x71;
    iptr->WriteBytes(0, NULL, 1, data);
*/
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]I2C_CH_Reset, CH=0x%x\n",ch_num));
    return MAPI_TRUE;
}

MS_BOOL IIC_Bypass_Mode(MS_BOOL enable)
{
    if (enable)
        WriteReg(0x0900+(0x08)*2, 0x10);// IIC by-pass mode on
    else
        WriteReg(0x0900+(0x08)*2, 0x00);// IIC by-pass mode off

    return TRUE;
}

//##########################################################################################################
//##########################################################################################################
//###############################  Public:Common Function Implementation ###################################
//##########################################################################################################
//##########################################################################################################
static MAPI_BOOL IspCheckVer(MAPI_U8* pLibData, MAPI_BOOL* pMatch)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8  bReadData[VERSION_CODE_SIZE];
    MAPI_U32  indx = 0;
    *pMatch = true;

    MAPI_U8 bWriteData[5] = {0x4D, 0x53, 0x54, 0x41, 0x52};
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_SPI_IIC);
    iptr->WriteBytes(0, NULL, 5, bWriteData);

    MAPI_U8    bAddr[1], bError = true;
    //MAPI_U16   Count;

    memset(bReadData, 0 , sizeof(bReadData));

    bAddr[0] = 0x10;
    //dwStartAddr=0;

    bWriteData[0] = 0x03;
    bWriteData[1] = VERSION_CODE_ADDR >> 16;
    bWriteData[2] = VERSION_CODE_ADDR >> 8;
    bWriteData[3] = VERSION_CODE_ADDR & 0xFF;

    bError &=  iptr->WriteBytes(1, bAddr, 4, bWriteData);

    bAddr[0] = 0x11;
    bError &= iptr->ReadBytes(1, bAddr, VERSION_CODE_SIZE, bReadData);

    bWriteData[0] = 0x12;
    bError &= iptr->WriteBytes(0, NULL, 1,  bWriteData);

    if(MAPI_FALSE == bError)
    {
        bWriteData[0] = 0x24 ;
        iptr->WriteBytes(0, NULL, 1, bWriteData);

        return MAPI_FALSE;
    }

    bWriteData[0] = 0x24 ;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    printf("sttest version data = ");
    for(indx = 0; indx < (VERSION_CODE_SIZE); indx++)
    {
        printf(" %x ,", bReadData[indx]);
        if(pLibData[indx+VERSION_CODE_ADDR] != bReadData[indx])
        {
            *pMatch = false;
            //break;
        }
    }
    printf(" \n");

    return MAPI_TRUE;
}

static MAPI_BOOL dram_crc_check(MAPI_U16 chksum_lib, MAPI_BOOL* pMatch)
{
    MAPI_U16  chksum = 0;
    // MAPI_U16  chksum_lib = 0;
    MAPI_U16  u16Addr = 0;
    MAPI_U8   u8MsbData[5];
    MAPI_U8   reg = 0;
    MAPI_BOOL bRet;
    MAPI_U8   mcu_status = 0;

    *pMatch = false;

    // MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);
    // iptr->WriteBytes(0, NULL, 5, bWriteData);

    /// crc H byte
    u16Addr = 0x0c00+0x5a*2;

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, u8MsbData);
    iptr->ReadBytes(0, NULL, 1, &reg);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);


   chksum = reg;

    /// crc L byte
    u16Addr = 0x0c00+0x5b*2;

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, u8MsbData);
    iptr->ReadBytes(0, NULL, 1, &reg);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);


   chksum = (chksum<<8)|reg;

    // get mcu status

    u16Addr = 0x0900+0x4f*2;

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, u8MsbData);
    iptr->ReadBytes(0, NULL, 1, &reg);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);


    mcu_status = reg;


    /// check the crc in dsp lib array

    if (mcu_status == 0xaa && ((chksum_lib&0xff00) == (chksum&0xff00)) )
      *pMatch = true;
    else if(chksum_lib == chksum)
      *pMatch = true;

    DBG_DEMOD_CHECKSUM(printf("[crc]chksum_lib=0x%x, chksum=0x%x, bRet=%d, Match=%d, mcu_status=0x%x\n",chksum_lib,chksum,bRet,*pMatch,mcu_status));

    return bRet;
}

#if (FLASH_WP_ENABLE == 1)
static MAPI_BOOL msb1240_flash_WP_reg_read(MAPI_U16 u16Addr, MAPI_U8 *pu8Data)
{
    MAPI_BOOL bRet;
    MAPI_U8   u8MsbData[5];
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, u8MsbData);
    iptr->ReadBytes(0, NULL, 1, pu8Data);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);
    return bRet;
}

static MAPI_BOOL msb1240_flash_WP_reg_write(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    MAPI_BOOL bRet = MAPI_TRUE;
    MAPI_U8   u8MsbData[6];
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2 == 1)
    bRet &= iptr->SetSpeed(350);
#endif

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;
    u8MsbData[5] = u8Data;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 6, u8MsbData);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);
    return bRet;
}

static MAPI_BOOL msb1240_flash_WRSR(MAPI_U8 reg)
{
    MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
    MAPI_U8     bAddr[1];
    MAPI_BOOL   rbet = true;

    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_SPI_IIC);
    iptr->WriteBytes(0, NULL, 5, bWriteData);

    // WREN
    bAddr[0] = 0x10;
    bWriteData[0] = 0x06;
    iptr->WriteBytes(1, bAddr, 1, bWriteData);

    bWriteData[0] = 0x12;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    // WRSR
    bAddr[0] = 0x10;
    bWriteData[0] = 0x01;
    bWriteData[1] = reg;
    iptr->WriteBytes(1, bAddr, 2, bWriteData);

    bWriteData[0] = 0x12;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    // WRDI
    bAddr[0] = 0x10;
    bWriteData[0] = 0x04;
    iptr->WriteBytes(1, bAddr, 1, bWriteData);

    bWriteData[0] = 0x12;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    // end
    bWriteData[0] = 0x24;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    DBG_FLASH_WP(printf("[wb]msb1240_flash_WRSR, reg=0x%x\n",reg);)

    return rbet;
}

static MAPI_BOOL msb1240_flash_SRSR(MAPI_U8 *p_reg)
{
    MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
    MAPI_U8     bAddr[1];
    MAPI_BOOL   bRet = true;
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_SPI_IIC);
    iptr->WriteBytes(0, NULL, 5, bWriteData);
    bAddr[0] = 0x10;
    bWriteData[0] = 0x05;
    iptr->WriteBytes(1, bAddr, 1, bWriteData);
    bAddr[0] = 0x11;
    iptr->ReadBytes(1, bAddr, 1, p_reg);
    bWriteData[0] = 0x12;
    iptr->WriteBytes(0, NULL, 1, bWriteData);
    // end
    bWriteData[0] = 0x24 ;
    iptr->WriteBytes(0, NULL, 1, bWriteData);
    DBG_FLASH_WP(printf("[wb]msb1240_flash_SRSR, reg=0x%x\n",*p_reg);)
    return bRet;
}

static MAPI_BOOL msb1240_flash_WP(MAPI_U8 enable)
{
    MAPI_U8 reg = 0;
    MAPI_BOOL bRet = true;
    MAPI_U8 u8_count = 0;

    DBG_FLASH_WP(printf("[wb]msb1240_flash_WP_Enable=%d\n",enable);)

    if (enable == 1)
    {
      u8_count = 20;
      do
      {
        msb1240_flash_SRSR(&reg);
        usleep(1*1000);
      }while(reg&0x01 && u8_count--);

      if (u8_count == 0)
      {
        bRet = false;
        DBG_FLASH_WP(printf("[wb]Err, flash_SRSR timeout!!!\n");)
        return bRet;
      }

      msb1240_flash_WRSR(reg|0x9c);

      u8_count = 20;
      do
      {
        msb1240_flash_SRSR(&reg);
        usleep(1*1000);
      }while(reg&0x01 && u8_count--);


      if (u8_count == 0)
      {
        bRet = false;
        DBG_FLASH_WP(printf("[wb]Err, flash_SRSR timeout!!!\n");)
        return bRet;
      }

      // active low
      // init gpio0
      bRet &= msb1240_flash_WP_reg_read(0x0900+0x2e*2, &reg);
      bRet &= msb1240_flash_WP_reg_write(0x0900+0x2e*2, reg&(~0x02));
      bRet &= msb1240_flash_WP_reg_read(0x0900+0x6b*2, &reg);
      bRet &= msb1240_flash_WP_reg_write(0x0900+0x6b*2, reg&(~0x30));

      // pull low
      bRet &= msb1240_flash_WP_reg_read(0x0900+0x63*2, &reg);
      bRet &= msb1240_flash_WP_reg_write(0x0900+0x63*2, reg&(~0x01));

      // gpio0 output enable
      bRet &= msb1240_flash_WP_reg_read(0x0900+0x64*2, &reg);
      bRet &= msb1240_flash_WP_reg_write(0x0900+0x64*2, reg&(~0x01));
    }
    else
    {
      // unactive high
      // init gpio0
      bRet &= msb1240_flash_WP_reg_read(0x0900+0x2e*2, &reg);
      bRet &= msb1240_flash_WP_reg_write(0x0900+0x2e*2, reg&(~0x02));
      bRet &= msb1240_flash_WP_reg_read(0x0900+0x6b*2, &reg);
      bRet &= msb1240_flash_WP_reg_write(0x0900+0x6b*2, reg&(~0x30));

      // pull high
      bRet &= msb1240_flash_WP_reg_read(0x0900+0x63*2, &reg);
      bRet &= msb1240_flash_WP_reg_write(0x0900+0x63*2, reg|0x01);

      // gpio0 output enable
      bRet &= msb1240_flash_WP_reg_read(0x0900+0x64*2, &reg);
      bRet &= msb1240_flash_WP_reg_write(0x0900+0x64*2, reg&(~0x01));

      u8_count = 20;
      do
      {
        msb1240_flash_SRSR(&reg);
        usleep(1*1000);
      }while(reg&0x01 && u8_count--);

      if (u8_count == 0)
      {
        bRet = false;
        DBG_FLASH_WP(printf("[wb]Err, flash_SRSR timeout!!!\n");)
        return bRet;
      }

      msb1240_flash_WRSR(reg&(~0x9c));

      u8_count = 20;
      do
      {
        msb1240_flash_SRSR(&reg);
        usleep(1*1000);
      }while(reg&0x01 && u8_count--);

      if (u8_count == 0)
      {
        bRet = false;
        DBG_FLASH_WP(printf("[wb]Err, flash_SRSR timeout!!!\n");)
        return bRet;
      }
    }
    return bRet;
}
#endif


MAPI_BOOL Turn_Off_ALL_Pad_In(MAPI_BOOL b_en)
{
    MAPI_BOOL bRet = true;
    MAPI_U8   u8_reg = 0;

    // Turn off all-pad-in function
    // [8:8] 1: all pad turn off except i2c.
    bRet &= ReadReg(0x0900+(0x28)*2+1, &u8_reg);
    if (b_en == MAPI_TRUE)
        u8_reg &= (0xff-0x01);
    else
        u8_reg |= 0x01;
    bRet &= WriteReg(0x0900+(0x28)*2+1, u8_reg);
    return bRet;
}

// 144 ms roughly
MAPI_BOOL DTV_DVB_HW_init(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8 u8_tmp = 0;
    MAPI_U8 u8_timeout = 0;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]MSB1240_HW_init\n"));

    // ASIC INIT for Windermere DVB-T2
    {
    // -------------------------------------------------------------------
    // Initialize DMD_ANA_MISC
    // -------------------------------------------------------------------
    // [0]    reg_tst_ldo25i
    // [1]    reg_tst_ldo25q
    // [5:4]    reg_tst_ldo25i_selfb
    // [7:6]    reg_tst_ldo25q_selfb
    // [8]    reg_pd_dm2p5ldoi = 1'b0
    // [9]    reg_pd_dm2p5ldoq = 1'b0
    bRet &= WriteReg2bytes(0x0A00+(0x4f)*2, 0x0000);

    // [0]    reg_tst_ldo11_clk
    // [1]    reg_tst_ldo26
    // [2]    reg_tst_ldo11_cmp
    // [3]    reg_pd_dm1p1ldo_clk = 1'b0
    // [4]    reg_pd_dm1p1ldo_cmp = 1'b0
    // [6]    reg_tst_ldo26_selfb
    // [7]    reg_pd_dm2p6ldo = 1'b0
    // [9:8]    reg_tst_ldo11_cmp_selfb
    // [11:10]    reg_tst_ldo11_clk_selfb
    bRet &= WriteReg2bytes(0x0A00+(0x4e)*2, 0x0000);

    // [1:0]    reg_mpll_loop_div_first       feedback divider 00:div by 1 01:div by 2 10:div by 4 11:div by 8
    // [15:8]    reg_mpll_loop_div_second      feedback divider, div by binary data number
    bRet &= WriteReg2bytes(0x0A00+(0x33)*2, 0x1201);

    // [2:0]    reg_mpll_ictrl            charge pump current control
    // [3]    reg_mpll_in_sel            1.8V or 3.3V reference clock domain select (1'b0=0==>3.3 V reference clock domain)
    // [4]    reg_mpll_xtal2adc_sel        select the XTAL clock bypass to MPLL_ADC_CLK
    // [5]    reg_mpll_xtal2next_pll_sel  crystal clock bypass to next PLL select
    // [6]    reg_mpll_vco_offset        set VCO initial offset frequency
    // [7]    reg_mpll_pd            gated reference clock and power down PLL analog_3v: 1=power down
    // [8]    reg_xtal_en            XTAL enable register; 1: enable
    // [10:9]    reg_xtal_sel            XTAL driven strength select.
    // [11]      reg_mpll_porst            MPLL input  power on reset, connect to reg as MPLL_RESET
    // [12]      reg_mpll_reset            PLL software reset; 1:reset
    // [13]      reg_pd_dmpll_clk        XTAL to MPLL clock reference power down
    // [14]      reg_pd_3p3_1            XTAL to CLK_24M_3P3_1 power down
    // [15]      reg_pd_3p3_2            XTAL to CLK_24M_3P3_2 power down
    bRet &= WriteReg2bytes(0x0A00+(0x35)*2, 0x1803);
    bRet &= WriteReg2bytes(0x0A00+(0x35)*2, 0x0003);


    // [0]    reg_mpll_clk_dp_pd    dummy
    // [1]    reg_adc_clk_pd        ADC output clock power down
    // [2]    reg_mpll_div2_pd    MPLL_DIV2 power down
    // [3]    reg_mpll_div3_pd    MPLL_DIV3 power down
    // [4]    reg_mpll_div4_pd    MPLL_DIV4 power down
    // [5]    reg_mpll_div8_pd    MPLL_DIV8 power down
    // [6]    reg_mpll_div10_pd    MPLL_DIV10 power down
          // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h2400);  // divide ADC clock to 24Mhz = 24*36/36
          bRet &= WriteReg2bytes(0x0A00+(0x30)*2, 0x2400);

    // $display("--------------------------------------");
    // $display("Initialize ADC I/Q");
    // $display("--------------------------------------");

    // [0]    Q channel ADC power down
    // [1]    I channel ADC power down
    // [2]    Q channel clamp enable. 0:enable, 1:disable
    // [3]    I channel clamp enable. 0:enable, 1:disable
    // [6:4]    I channel input mux control;
    //        3'b000=I channel ADC calibration mode input
    //            3'b001=VIF signal from VIFPGA
    //            3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //            all the other combination are only for test mode, don't use without understanding.
    // [10:8]   Q channel input mux control;
    //        3'b000=Q channel ADC calibration mode input
    //            3'b001=VIF signal from VIFPGA 3'b010 = SSIF signal from PAD_SIFP(M)
    //            3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //            all the other combination are only for test mode, don't use without understanding.
    // [12]    ADC I,Q swap enable; 1: swap
    // [13]    ADC clock out select; 1: ADC_CLKQ
    // [14]    ADC linear calibration bypass enable; 1:enable
    // [15]    ADC internal 1.2v regulator control always 0 in T3
        bRet &= WriteReg2bytes(0x0A00+(0x01)*2, 0x0440);

    // [2:0]    reg_imuxs_s
    // [6:4]    reg_qmuxs_s
    // [9:8]    reg_iclpstr_s
    // [13:12]    reg_qclpstr_s
        bRet &= WriteReg2bytes(0x0A00+(0x45)*2, 0x0000);


    // [0]    Channel I ADC power down: 1=power dwon
    // [1]    Channel Q ADC power down: 1=power dwon
    // [2]    power down clamp buffer for test mode
    // [3]    change ADC reference voltage for SSIF
    // [6:4]    ADC source bias current control
    // [9:8]    XTAL receiver amp gain
        bRet &= WriteReg2bytes(0x0A00+(0x0c)*2, 0x0002);

    // [0]    reg_linear_cal_start_q    0    0    1
    // [1]    reg_linear_cal_mode_q    0    0    1
    // [2]    reg_linear_cal_en_q    0    0    1
    // [3]    reg_linear_cal_code0_oren_q    0    0    1
    // [6:4]    reg_linear_cal_status_sel_q    2    0    3
    // [7]    reg_pwdn_vcalbuf    0    0    1
      bRet &= WriteReg2bytes(0x0A00+(0x0f)*2, 0x0000);

    // [3:0]    clamp voltage control
    //          3'b000 = 0.7v
    //          3'b001 = 0.75v
    //          3'b010 = 0.5v
    //          3'b011 = 0.4v
    //          3'b100 = 0.8v
    //          3'b101 = 0.9v
    //          3'b110 = 0.65v
    //          3'b111 = 0.60v
    // [4]    REFERENCE power down
      bRet &= WriteReg2bytes(0x0A00+(0x20)*2, 0x0000);

    // Set ADC gain is 1
      bRet &= WriteReg2bytes(0x0A00+(0x0b)*2, 0x0909);

    // Disable ADC Sign bit
      bRet &= WriteReg2bytes(0x0A00+(0x2e)*2, 0x0000);

    // ADC I channel offset
      bRet &= WriteReg2bytes(0x0A00+(0x2a)*2, 0x0c00);

    // ADC Q channel offset
      bRet &= WriteReg2bytes(0x0A00+(0x2b)*2, 0x0c00);

    // [2:0]reg_acl_ref
    // [5:4]reg_acl_isel
    // [8]    reg_xtal_pm_isel
    // [9]    reg_bond_mode
    // [10]    reg_clk_bond_mode
    // [11]    reg_clk_usb_3p3_en
    // [13:12]    reg_iq_ctrl    = 2'd1
    bRet &= WriteReg2bytes(0x0A00+(0x19)*2, 0x1e00);

    // [ 4:0]reg_ckg_bist[4:0]
    // [11:8]reg_ckg_adcd_d2[3:0]
    bRet &= WriteReg2bytes(0x0900+(0x1c)*2, 0x0000);

    // [ 4:0]reg_ckg_dvbtm_sram_t11x_t22x[4:0]
    // [12:8]reg_ckg_dvbtm_sram_t11x_t24x[4:0]
    bRet &= WriteReg2bytes(0x0900+(0x1e)*2, 0x0000);


    // -------------------------------------------------------------------
    // Release clock gating
    // -------------------------------------------------------------------

    // [0]    reg_xtal_en
    // [9:8]    reg_clk_pd_iic
    // [10]    reg_clk_pd_all
      bRet &= WriteReg2bytes(0x0900+(0x09)*2, 0x0101);

    // [3:0]    reg_ckg_adcd
    // [7:4]    reg_ckg_sadc
    // [11:8]    reg_ckg_iicm
    // [13:12]    reg_ckg_sbus
      bRet &= WriteReg2bytes(0x0900+(0x0a)*2, 0x0000);

    // [5:0]    reg_ckg_mcu
    // [6]    reg_ckg_live
    // [11:8]    reg_ckg_inner
      bRet &= WriteReg2bytes(0x0900+(0x0b)*2, 0x0030);
    //set MCU ckg to 108MHz by jason
    // reg_ckg_mcu[4:2] = 0x0
    // reg_ckg_mcu[5] = 0x0
//      bRet &= WriteReg2bytes(0x0900+(0x0b)*2, 0x0020);
//      bRet &= WriteReg2bytes(0x0900+(0x0b)*2, 0x0000);
    // @0x0910
    // [3:0]    reg_ckg_dvbtm_adc
    // [6:4]    reg_ckg_dvbt_inner1x
    // [10:8]    reg_ckg_dvbt_inner2x
    // [14:12]    reg_ckg_dvbt_inner4x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x10)*2, 0x1110);

    // @0x0911
    // [2:0]    reg_ckg_dvbt_outer1x
    // [6:4]    reg_ckg_dvbt_outer2x
    // [11:8]    reg_ckg_dvbtc_outer2x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x11)*2, 0x0111);

    // @0x0912
    // [3:0]    reg_ckg_dvbtm_ts
    // [4]    reg_dvbtm_ts_out_mode
    // [5]    reg_dvbtm_ts_clk_pol
    // [15:8]    reg_dvbtm_ts_clk_divnum
      bRet &= WriteReg2bytes(0x0900+(0x12)*2, 0x1418);

    // @0x0913
    // [5:0]    reg_ckg_spi
      bRet &= WriteReg2bytes(0x0900+(0x13)*2, 0x0020);

    // @0x0914
    // [12:8]    reg_ckg_dvbtm_sram_t1o2x_t22x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x14)*2, 0x0000);

    // @0x0915
    // [3:0]    reg_ckg_dvbc_inner
    // [6:4]    reg_ckg_dvbc_eq
    // [10:8]    reg_ckg_dvbc_eq8x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x15)*2, 0x0111);

    // @0x0916
    // [8:4]    reg_ckg_dvbtm_sram_adc_t22x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x16)*2, 0x0001);

    // @0x0917
    // [4:0]    reg_ckg_dvbtm_sram_t12x_t22x
    // [12:8]    reg_ckg_dvbtm_sram_t12x_t24x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x17)*2, 0x0000);

    // @0x0918
    // [4:0]    reg_ckg_dvbtm_sram_t14x_t24x
    // [12:8]    reg_ckg_dvbtm_ts_in
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x18)*2, 0x0400);

    // @0x0919
    // [2:0]    reg_ckg_tdp_jl_inner1x
    // [6:4]    reg_ckg_tdp_jl_inner4x
    // [15:8]    reg_ckg_miu
      bRet &= WriteReg2bytes(0x0900+(0x19)*2, 0x3c00);

    // @0x091a
    // [6:4]    reg_ckg_dvbt2_inner1x
    // [10:8]    reg_ckg_dvbt2_inner2x
    // [14:12]    reg_ckg_dvbt2_inner4x
     //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x1a)*2, 0x0000);

    // @0x090e
    // [3:0]    reg_ckg_dvbs2_ldpc_inner_sram
    // [7:4]    reg_ckg_dvbs_viterbi_sram
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x0e)*2, 0x0000);

    // @0x091b
    // [2:0]    reg_ckg_dvbt2_outer1x
    // [6:4]    reg_ckg_dvbt2_outer2x
    // [10:8]    reg_ckg_syn_miu
    // [14:12]    reg_ckg_syn_ts
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x1b)*2, 0x0000);

    // @0x091c
    // [4:0]    reg_ckg_bist
    // [11:8]    reg_ckg_adcd_d2
      bRet &= WriteReg2bytes(0x0900+(0x1c)*2, 0x0000);

    // @0x091d
    // [3:0]    reg_ckg_dvbtm_adc_eq_1x
    // [7:4]    reg_ckg_dvbtm_adc_eq_0p5x
      bRet &= WriteReg2bytes(0x0900+(0x1d)*2, 0x0000);

    // @0x0921
    // [2:0]    reg_ckg_tdp_teq_inner1x
    // [14:12]    reg_ckg_tdp_teq_inner2x
      bRet &= WriteReg2bytes(0x0900+(0x21)*2, 0x0000);

    // @0x0922
    // [3:0]    reg_ckg_dvbt_t2_inner0p5x_dvbc_eq1x
    // [7:4]    reg_ckg_dvbt_t2_inner2x_dvbc_eq4x
    // [11:8]    reg_ckg_dvbt_t2_inner1x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x22)*2, 0x0000);

    // [1:0]    reg_iicm_pad_sel
    // [4]    reg_i2c_sbpm_en
    // [12:8]    reg_i2c_sbpm_idle_num
      bRet &= WriteReg2bytes(0x0900+(0x08)*2, 0x0a01);

    // [8]    reg_turn_off_pad
      bRet &= WriteReg2bytes(0x0900+(0x28)*2, 0x0000);

    // @0x0970
    // [3:0]    reg_ckg_dvbt_inner2x_srd0p5x
    // [7:4]    reg_ckg_dvbt2_inner2x_srd0p5x
    // [12:8]    reg_ckg_dvbtm_sram_t1outer1x_t24x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x70)*2, 0x0000);

    // @0x0971
    // [4:0]    reg_ckg_dvbtm_sram_t12x_t24x_srd1x
    // [12:8]    reg_ckg_dvbtm_sram_t14x_t24x_srd1x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x71)*2, 0x0000);

    // @0x0972
    // [6:0]    reg_ckg_dvbt2_s2_bch_out
    // [12:8]    reg_ckg_dvbt2_outer2x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x72)*2, 0x0000);

    // @0x0973
    // [3:0]    reg_ckg_dvbt2_inner4x_s2_inner
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x73)*2, 0x0000);

    // @0x0974
    // [4:0]    reg_ckg_dvbtm_sram_t12x_t24x_s2inner
    // [12:8]    reg_ckg_dvbtm_sram_t14x_t24x_s2inner
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x74)*2, 0x0000);

    // @0x0975
    // [4:0]    reg_ckg_dvbtc_rs
    // [11:8]    reg_ckg_dvbs_outer2x_dvbt_outer2x
    // [15:12]    reg_ckg_dvbs_outer2x_dvbt_outer2x_miu
      bRet &= WriteReg2bytes(0x0900+(0x75)*2, 0xc101);

    // @0x0976
    // [4:0]    reg_ckg_dvbs_outer2x_dvbt_outer2x_dvbt2_inner2x
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x76)*2, 0x000c);

    // @0x0977
    // [3:0]    reg_ckg_dvbt2_inner4x_dvbtc_rs
    // [8:4]    reg_ckg_dvbtm_sram_adc_t22x_dvbtc_rs
    //DVBT2
      bRet &= WriteReg2bytes(0x0900+(0x77)*2, 0x0000);

//    $display("--------------------------------------");
//    $display("Initialize Transport Stream synthesizer and APLL");
//    $display("--------------------------------------");

    // [15:0]    reg_synth_set[15: 0]
    // [ 7:0]    reg_synth_set[23:16]
      bRet &= WriteReg2bytes(0x0900+(0x51)*2, 0x0000);
      bRet &= WriteReg2bytes(0x0900+(0x52)*2, 0x0040);


    // [0]    reg_synth_reset
    // [1]    reg_synth_ssc_en
    // [2]    reg_synth_ssc_mode
    // [4]    reg_synth_sld
      bRet &= WriteReg2bytes(0x0900+(0x50)*2, 0x0010);

    // [1:0]    reg_apll_loop_div_first
    // [15:8]    reg_apll_loop_div_second
      bRet &= WriteReg2bytes(0x0900+(0x57)*2, 0x0000);

    // [0]    reg_apll_pd
    // [1]    reg_apll_reset
    // [2]    reg_apll_porst
    // [3]    reg_apll_vco_offset
    // [4]    reg_apll_en_ts
    // [5]    reg_apll_endcc
    // [6]    reg_apll_clkin_sel
    // [8]    reg_apll_ts_mode
      bRet &= WriteReg2bytes(0x0900+(0x55)*2, 0x0100);
      bRet &= WriteReg2bytes(0x0900+(0x55)*2, 0x0110);

    // [16:0]    reg_apll_test
      bRet &= WriteReg2bytes(0x0900+(0x59)*2, 0x0000);

    // 0x0920
    // [3:0]    reg_ckg_ts_apll_div[2:0]
      bRet &= WriteReg2bytes(0x0900+(0x20)*2, 0x0004);


    // -------------------------------------------------------------------
    // initialize MIU
    // -------------------------------------------------------------------
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);


// set frequence 133MHz
    bRet &= WriteReg2bytes(0x1200+(0x11)*2, 0x60cc);
    bRet &= WriteReg2bytes(0x1200+(0x11)*2, 0x00cc);
    bRet &= WriteReg2bytes(0x1200+(0x11)*2, 0x004c);
    bRet &= WriteReg2bytes(0x1200+(0x10)*2, 0x33f8);
    bRet &= WriteReg2bytes(0x1200+(0x12)*2, 0x0000);
    bRet &= WriteReg2bytes(0x1200+(0x13)*2, 0x0000);
    // yihao 20130925 for new apll model
    bRet &= WriteReg2bytes(0x1200+(0x16)*2, 0x0000);
    bRet &= WriteReg2bytes(0x1200+(0x1c)*2, 0x00b0);

    bRet &= WriteReg2bytes(0x1200+(0x01)*2, 0x8100);
    // cke                : [0]
    // reg_self_refresh        : [1]
    // reg_dynamic_cke        : [2]
    // reg_dynamic_ck_odt        : [3]
    // reg_dram_bus            : [5:4] 00: 16b, 01: 32b, 10: 64b
    // reg_dram_type            : [7:6] 00: sdr, 01: ddr, 10: ddr2
    // reg_4ba            : [8]    0: 2bk,  1: 4bk
            // reg_col_size            : [10:9]
    // reg_cke_oenz            : [12]
    // reg_dq_oenz            : [13]
    // reg_adr_oenz            : [14]
    // reg_cs_z            : [15]
    bRet &= WriteReg2bytes(0x1200+(0x01)*2, 0xe100);
    bRet &= WriteReg2bytes(0x1200+(0x01)*2, 0x8100);
    bRet &= WriteReg2bytes(0x1200+(0x02)*2, 0x0371);
    bRet &= WriteReg2bytes(0x1200+(0x03)*2, 0x0030);
    bRet &= WriteReg2bytes(0x1200+(0x04)*2, 0x33c9);
    // reg_tRAS                      : [3:0]        9
    // reg_tRC                       : [7:4]        c
    // reg_tRCD                      : [11:8]       3
    // reg_tRP                       : [15:12]      3
    bRet &= WriteReg2bytes(0x1200+(0x05)*2, 0x4232);
    // reg_tRRD                      : [3:0]         2
    // tWR                           : [7:4]         3
    // reg_tMRD                      : [11:8]        2
    // reg_tRTP            : [15:12]    4
    bRet &= WriteReg2bytes(0x1200+(0x06)*2, 0x5532);
    // reg_w2r_dly(tWTR)             : [3:0]         2
    // reg_w2r_oen_dly               : [7:4]         3
    // reg_r2w_dly(tRTW)             : [11:8]        5
    // reg_r2w_oen_dly               : [15:12]       5
    bRet &= WriteReg2bytes(0x1200+(0x07)*2, 0x400c);
    // tRFC                          : [5:0]         c
    // reg_tRAS[4]                   : [6]           0
    // reg_tRC[4]                    : [7]           0
    // reg_write_latency             : [10:8]        0
    // reg_tCCD                      : [15:14]       1
    bRet &= WriteReg2bytes(0x1200+(0x0e)*2, 0x1800);

    bRet &= WriteReg2bytes(0x1200+(0x23)*2, 0x7ffe);

    bRet &= WriteReg2bytes(0x1200+(0x20)*2, 0xc001);

    //delay 1
    usleep(1000);

    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);
    bRet &= WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);

    bRet &= WriteReg2bytes(0x1200+(0x01)*2, 0x010d);


// $display("--------Initial DRAM start here!!!");
    bRet &= WriteReg2bytes(0x1200+(0x00)*2, 0x0001);


    // wait(test_chip_top.dut.i_dig_top.miu_inst.miu_reg_0.init_done);
    // while( (getValue(0x1200) & 0x8000)!= 0x8000);
    u8_timeout = 0;
    bRet &= ReadReg(0x1201, &u8_tmp);
    DBG_DEMOD_LOAD_I2C(printf("[msb1240]MIU wait init done, u8_tmp=0x%x, bRet=0x%x\n",u8_tmp,bRet));
    while( (u8_tmp&0x80) != 0x80)
    {
        if(u8_timeout++>200)
        {
            ERR_DEMOD_MSB(printf("[msb1240][err]MIU init failure...\n"));
            return MAPI_FALSE;
        }
        // 10us delay
        usleep(10);
        bRet &= ReadReg(0x1201, &u8_tmp);
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240]MIU init done, u8_tmp=0x%x, bRet=0x%x\n",u8_tmp,bRet));


    // $display("--------Initial Done");
    bRet &= WriteReg2bytes(0x1200+(0x08)*2, 0x0001);


    // $display("-------------------------");
    // $display("-- miu self test start --");
    // $display("-------------------------");
    bRet &= WriteReg2bytes(0x1200+(0x70)*2, 0x0000);
    bRet &= WriteReg2bytes(0x1200+(0x71)*2, 0x0000);
    bRet &= WriteReg2bytes(0x1200+(0x72)*2, 0x0010);
    bRet &= WriteReg2bytes(0x1200+(0x74)*2, 0x5aa5);
    bRet &= WriteReg2bytes(0x1200+(0x70)*2, 0x0001);

    // #10000;
    //delay 1
    usleep(1000);

    //wait test_finish
    u8_timeout = 0;
    bRet &= ReadReg(0x12E1, &u8_tmp);
    DBG_DEMOD_LOAD_I2C(printf("[msb1240]MIU self test Phase1 beg, u8_tmp=0x%x, bRet=0x%x\n",u8_tmp,bRet));
    while( (u8_tmp&0x80) != 0x80)
    {
        if(u8_timeout++>200)
        {
            ERR_DEMOD_MSB(printf("[msb1240][err]MIU self test Phase1 failure...\n"));
            return MAPI_FALSE;
        }
        // 10us delay
        usleep(10);
        bRet &= ReadReg(0x12E1, &u8_tmp);
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240]MIU self test Phase1 end, u8_tmp=0x%x, bRet=0x%x\n",u8_tmp,bRet));

     // #10000;
     //delay 1
     usleep(1000);

    // MIU self test FAIL let program stuck in this while loop
    u8_timeout = 0;
    bRet &= ReadReg(0x12E1, &u8_tmp);
    DBG_DEMOD_LOAD_I2C(printf("[msb1240]MIU self test Phase2 beg, u8_tmp=0x%x, bRet=0x%x\n",u8_tmp,bRet));
    while( (u8_tmp&0x40) != 0x00)
    {
        if(u8_timeout++>200)
        {
            ERR_DEMOD_MSB(printf("[msb1240][err]MIU self test Phase2 failure...\n"));
            return MAPI_FALSE;
        }
        // 10us delay
        usleep(10);
        bRet &= ReadReg(0x12E1, &u8_tmp);
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240]MIU self test Phase2 end, u8_tmp=0x%x, bRet=0x%x\n",u8_tmp,bRet));

    bRet &= WriteReg2bytes(0x1200+(0x23)*2, 0x0000);

    // -------------------------------------------------------------------
    // initialize MIU  finish
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    //  Turn on pads
    // -------------------------------------------------------------------

    // ------Turn off all pad in
    // [0] reg_set_pad_low
    // [1] reg_set_pad_high
    // [2] reg_set_i2cs_pad_low
    // [3] reg_set_i2cs_pad_high
    // [8] reg_turn_off_pad
     bRet &= WriteReg2bytes(0x0900+(0x28)*2, 0x0000);

    // ------I2CM pad on
    // [1:0]    reg_iicm_pad_sel[1:0]    1:iicm enable 2:UART enable
    // [4]        reg_i2c_sbpm_en        1: enable I2CS bypass to I2CM function
    // [12:8]   reg_i2c_sbpm_idle_num[4:0]    a: default
     bRet &= WriteReg2bytes(0x0900+(0x08)*2, 0x0a01);

    // ------Transport Stream pad on (except TS ERR pad)
    // [15:0]   reg_en_ts_pad[15:0]    0x00ff:normal TS location 0xff00:reverse TS location
     bRet &= WriteReg2bytes(0x0900+(0x2d)*2, 0x00ff);

    // ------Transport Stream pad on (TS ERR pad)
    // [0]        reg_en_ts_err_pad    1: enable
    // [4]        reg_ts_err_pol    1: inverse 0:normal
     bRet &= WriteReg2bytes(0x0900+(0x2e)*2, 0x0001);

    // ------AGC pad on
    // [0] reg_ifagc_t_enable
    // [1] reg_ifagc_t_odmode
    // [2] reg_ifagc_t_data_sel
    // [4] reg_ifagc_t_force_enable
    // [5] reg_ifagc_t_force_value
    // [8] reg_ifagc_s_enable
    // [9] reg_ifagc_s_odmode
    // [10] reg_ifagc_s_data_sel
    // [12] reg_ifagc_s_force_enable
    // [13] reg_ifagc_s_force_value
    bRet &= WriteReg2bytes(0x0a00+(0x18)*2, 0x0001);
    }

#if(TIMING_VERIFICATION == 1)
    tmm_2 = GIVE_ME_TIME
#endif

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]MSB1240_HW_init, bRet=0x%x\n",bRet));

    return bRet;

}

// i2c 150Kb/s, average rate 110Kb/s, 32KB, 2436ms.
MAPI_BOOL Load2Sdram(MAPI_U8 *u8_ptr, MAPI_U16 data_length, MAPI_U16 sdram_win_offset_base)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]Load2Sdram, len=0x%x, win_offset=0x%x\n",data_length,sdram_win_offset_base));

#if(TIMING_VERIFICATION == 1)
    tmm_3 = GIVE_ME_TIME;
#endif

    // mask miu access of fdp, tdi, djb
    bRet &= WriteReg(0x1200+(0x23)*2 + 1, 0x0f);
    bRet &= WriteReg(0x1200+(0x23)*2, 0xf0);

    // 10us delay
    usleep(10);

    // Disable MCU
    bRet &= WriteReg(0x0b00+(0x19)*2, 0x03);

#if USE_SPI_LOAD_TO_SDRAM
    MAPI_U32 u32Addr = 0;

    u32Addr = (MAPI_U32)sdram_win_offset_base * 0x1000; // unit: 4K
    bRet &= MDrv_SS_MIU_Writes(u32Addr, u8_ptr, data_length);
    printf("****SPI load2sdram****, sdram_addr=0x%lx, data_length=0x%x\n", u32Addr, data_length);

#if (SDRAM_DATA_CHECK == 1)
    MAPI_U16 i = 0, j = 0, index = 0;
    MAPI_U8 buf[SPI_DEVICE_BUFFER_SIZE]={0};

    if((data_length % SPI_DEVICE_BUFFER_SIZE) == 0)
        index = data_length / SPI_DEVICE_BUFFER_SIZE;
    else
        index = data_length / SPI_DEVICE_BUFFER_SIZE + 1;

    for (i=0; i<index; i++)
    {
        memset(buf, 0x00, SPI_DEVICE_BUFFER_SIZE);

        bRet &= MDrv_SS_MIU_Reads(u32Addr+SPI_DEVICE_BUFFER_SIZE*i, buf, SPI_DEVICE_BUFFER_SIZE);

        for (j=0; j<SPI_DEVICE_BUFFER_SIZE; j++)
        {
            //printf("j=%d, buf=0x%x, data=0x%x", j, buf[j], u8_ptr[j]);
            if (buf[j] != u8_ptr[SPI_DEVICE_BUFFER_SIZE*i+j])
            {
                printf("spi miu write&read fail! idx=%x, y=0x%x, x=0x%x\n", (SPI_DEVICE_BUFFER_SIZE*i+j), buf[i], u8_ptr[SPI_DEVICE_BUFFER_SIZE*i+j]);
                //break;
            }
        }
    }
#endif

#else

    MAPI_U16  sdram_win_offset = sdram_win_offset_base;
    MAPI_U16  x_data_offset = 0;
    MAPI_U16  y_cir_addr = 0;

    if (I2C_CH_Reset(0) == MAPI_FALSE)
    {
        ERR_DEMOD_MSB(printf(">>>MSB1240 CH0 Reset:Fail\n"));
        return MAPI_FALSE;
    }
    else
    {
        // set xData map upper and low bound for 64k DRAM window
        bRet &= WriteReg2bytes(0x2B00+(0x63)*2, 0x3F24);

        // set xData map offset for 64k DRAM window, 64kbytes alignment
        bRet &= WriteReg2bytes(0x2B00+(0x64)*2, 0x0000);

        // set xData map upper and low bound for 4k DRAM window
        bRet &= WriteReg2bytes(0x2B00+(0x65)*2, 0x2014);

        // set xData map offset for 4k DRAM window, 4kbytes alignment
        bRet &= WriteReg2bytes(0x2B00+(0x66)*2, sdram_win_offset++);

        // enable xData map for DRAM
        bRet &= WriteReg2bytes(0x2B00+(0x62)*2, 0x0007);

        for(x_data_offset = 0, y_cir_addr = SDRAM_BASE; x_data_offset < data_length;)
        {
            if (y_cir_addr == 0x6000)
            {
                //set xData map offset for 4k DRAM window, 4kbytes alignment
                // 0x1000, 4096 bytes
                bRet &= WriteReg2bytes(0x2B00+(0x66)*2, sdram_win_offset++);
                y_cir_addr = SDRAM_BASE;
            }

            // max 0x200, error above.....

            if((data_length - x_data_offset) >= LOAD_CODE_I2C_BLOCK_NUM)
            {
                bRet &= WriteRegs(y_cir_addr, (u8_ptr + x_data_offset),LOAD_CODE_I2C_BLOCK_NUM);
                y_cir_addr += LOAD_CODE_I2C_BLOCK_NUM;
                x_data_offset += LOAD_CODE_I2C_BLOCK_NUM;
            }
            else
            {
                bRet &= WriteRegs(y_cir_addr, (u8_ptr + x_data_offset),data_length - x_data_offset);
                y_cir_addr += (data_length - x_data_offset);
                x_data_offset += (data_length - x_data_offset);
            }
        }
        DBG_DEMOD_LOAD_I2C(printf("[msb1240]x_data_offset=%d,y_cir_addr=%d,z_block_num=%d\n",x_data_offset,y_cir_addr,sdram_win_offset));

    #if (SDRAM_DATA_CHECK == 1)
        // beg data check.
        DBG_DEMOD_LOAD_I2C(printf("[msb1240]SDRAM data check...\n"));

        sdram_win_offset = sdram_win_offset_base;

        // set xData map offset for 4k DRAM window, 4kbytes alignment
        bRet &= WriteReg2bytes(0x2B00+(0x66)*2, sdram_win_offset++);

        for(x_data_offset = 0, y_cir_addr = SDRAM_BASE; x_data_offset < data_length;)
        {
            MAPI_U8 u8_tmp;
            if (y_cir_addr == 0x6000)
            {
                //set xData map offset for 4k DRAM window, 4kbytes alignment
                // 0x1000, 4096 bytes
                bRet &= WriteReg2bytes(0x2B00+(0x66)*2, sdram_win_offset++);
                y_cir_addr = SDRAM_BASE;
            }

            bRet &= ReadReg(y_cir_addr++, &u8_tmp);
            if(u8_tmp != *(u8_ptr + x_data_offset++))
            {
                ERR_DEMOD_MSB(printf("[msb1240]error, idx=0x%x, y=0x%x, x=0x%x\n",y_cir_addr-1, u8_tmp, *(u8_ptr + x_data_offset-1)));
            }
        }

        DBG_DEMOD_LOAD_I2C(printf("[msb1240]SDRAM data check...Done\n"));

        // end data check
    #endif
        //  Release xData map for SDRAM
        bRet &= WriteReg2bytes(0x2B00+(0x62)*2, 0x0000);

        // Channel changed from CH 0x00 to CH 0x03
        if (I2C_CH_Reset(3) == MAPI_FALSE)
        {
            ERR_DEMOD_MSB(printf(">>>MSB1240 CH3 Reset:Fail\n"));
            return MAPI_FALSE;
        }
    }
    #endif

#if(TIMING_VERIFICATION == 1)
    tmm_4 = GIVE_ME_TIME
    show_timer();
#endif

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]Load2Sdram, len=0x%x, win_offset=0x%x\n",data_length,sdram_win_offset_base));
    return bRet;
}

// mem_type 0: dram, 1:dram+sram
// 28 ms roughly
MAPI_BOOL MSB1240_MEM_switch(MAPI_U8 mem_type)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8 u8_tmp = 0,u8Data = 0;
    MAPI_U16 timeout = 0;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]MSB1240_MEM_switch, mem_type=0x%x\n",mem_type));

#if(TIMING_VERIFICATION == 1)
    tmm_15 = GIVE_ME_TIME
#endif
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            u8Data=1;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            u8Data=2;
            break;
        case E_DEVICE_DEMOD_DVB_C:
            u8Data=3;
            break;
        case E_DEVICE_DEMOD_DVB_S:
            u8Data=4;
            break;
        default:
            u8Data=2;
            return MAPI_FALSE;
    }
    if(mem_type == 1)
    {
        // Enable SRAM+SDRAM memory map

        // SRAM_START_ADDR 0x0000
        bRet &= WriteReg2bytes(0x1000,0x0000);
        bRet &= WriteReg2bytes(0x1004,0x0000);

        // SRAM_END_ADDR 0x7FFF
        bRet &= WriteReg2bytes(0x1002,0x0000);
        bRet &= WriteReg2bytes(0x1006,0x7FFF);

        if (u8Data == 4)
        {

            bRet &= WriteReg(0x2B80,0x12);
            // DRAM_START_ADDR 1M+0x2*0x1000+0x8000
            bRet &= WriteReg2bytes(0x1008,0x0000);
            bRet &= WriteReg2bytes(0x100C,0x8000);


            // DRAM_END_ADDR   1M+0x2*0x1000+0xFFFF
            bRet &= WriteReg2bytes(0x100A,0x0000);
            bRet &= WriteReg2bytes(0x100E,0xFFFF);
        }
        else
        {
            bRet &= WriteReg(0x2B80,0x10);

        // DRAM_START_ADDR 0x8000
        bRet &= WriteReg2bytes(0x1008,0x0000);
        bRet &= WriteReg2bytes(0x100C,0x8000);


        // DRAM_END_ADDR    0xFFFF
        bRet &= WriteReg2bytes(0x100A,0x0000);
        bRet &= WriteReg2bytes(0x100E,0xFFFF);
        }

        // Enable SRAM&SDRAM memory map
        bRet &= WriteReg(0x1018,0x05);

        // Wait memory map to be enabled
        do
        {
            bRet &= ReadReg(0x1018,&u8_tmp);
            if(timeout++ > 500)
            {
                printf("@msb1240, D+S memory mapping failure.!!!\n");
                return MAPI_FALSE;
            }
        }
        while(u8_tmp != 0x05);
    }
    else if(mem_type == 0)
    {
        // Enable SDRAM memory map
        // Run bootloader from SDRAM 1M

        bRet &= WriteReg(0x2B80,0x10);

        // DRAM_START_ADDR 0x0000
        bRet &= WriteReg2bytes(0x1008,0x0000);
        bRet &= WriteReg2bytes(0x100C,0x0000);

        // DRAM_END_ADDR    0x7FFF
        bRet &= WriteReg2bytes(0x100A,0x0000);
        bRet &= WriteReg2bytes(0x100E,0x7FFF);

        // Enable SRAM&SDRAM memory map
        bRet &= WriteReg(0x1018,0x04);

        // Wait memory map to be enabled
        do
        {
            bRet &= ReadReg(0x1018,&u8_tmp);
            if(timeout++ > 500)
            {
                printf("@msb1240, D memory mapping failure.!!!\n");
                return MAPI_FALSE;
            }
        }
        while(u8_tmp != 0x04);
    }
    else
    {
       printf("@msb1240, invalid mem type mapping.\n");
       return MAPI_FALSE;
    }
#if(TIMING_VERIFICATION == 1)
    tmm_16 = GIVE_ME_TIME
#endif
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]MSB1240_MEM_switch, , mem_type=0x%x, bRet=0x%x\n",mem_type,bRet));
    return bRet;
}

// 92~95ms roughly
MAPI_BOOL LoadSdram2Sram(MAPI_U8 CodeNum)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8   u8_data = 0;
    MAPI_U8   u8_timeout = 0xFF;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]LoadSdram2Sram, g_sram_code=0x%x, codeNum=0x%x\n",g_sram_code,CodeNum));

#if(TIMING_VERIFICATION == 1)
    tmm_17 = GIVE_ME_TIME
#endif

    if(CodeNum == g_sram_code)
    {
        DBG_DEMOD_LOAD_I2C(printf("[msb1240]LoadSdram2Sram, code is available.\n"));
        return bRet;
    }

    // mask miu access of fdp, tdi, djb
    bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x0f);
    bRet &= WriteReg(0x1200+(0x23)*2,0xf0);

    // 10us delay
    usleep(10);

    // Disable MCU
    bRet &= WriteReg(0x0b00+(0x19)*2, 0x03);

    // Use GDMA move code from SDRAM to SRAM
     bRet &= WriteReg2bytes(0x0300+(0x00)*2, 0x4254);     // rst
     bRet &= WriteReg2bytes(0x0300+(0x00)*2, 0x4257);    // cfg & trig

   switch(CodeNum)
   {
        case 0x02: //DVB-T2 @001000h ~ 008FFFh
            bRet &= WriteReg2bytes(0x0300+(0x01)*2, 0x0000); // Set src_addr
            bRet &= WriteReg2bytes(0x0300+(0x02)*2, 0x0011); // start from 1M+64k
            break;

        case 0x04: //DVB-T @010000h ~ 017FFFh
            bRet &= WriteReg2bytes(0x0300+(0x01)*2, 0x8000); // Set src_addr
            bRet &= WriteReg2bytes(0x0300+(0x02)*2, 0x0011); // start from 1M+96k
            break;

        case 0x08: //DVB-C @018000h ~ 01FFFFh
            bRet &= WriteReg2bytes(0x0300+(0x01)*2, 0x0000); // Set src_addr
            bRet &= WriteReg2bytes(0x0300+(0x02)*2, 0x0012); // start from 1M+128k
            break;
        case 0x10:// DVB-S2
            bRet &= WriteReg2bytes(0x0300+(0x01)*2, 0x0000); // Set src_addr
            bRet &= WriteReg2bytes(0x0300+(0x02)*2, 0x0013); // start from 1M+192k
            break;
        default:
            bRet &= false;
            break;
   }

    // Set dst_addr
    bRet &= WriteReg2bytes(0x0300+(0x03)*2, 0x0000);
    bRet &= WriteReg2bytes(0x0300+(0x04)*2, 0x0000);

    // Set data_size
    bRet &= WriteReg2bytes(0x0300+(0x05)*2, 0x8000);
    bRet &= WriteReg2bytes(0x0300+(0x06)*2, 0x0000);

    bRet &= WriteReg(0x0300+(0x07)*2, 0x01); //start GDMA

    // Wait for GDMA
    do
    {
      usleep(10);
      bRet &= ReadReg(0x0300+(0x08)*2, &u8_data);
      u8_timeout--;
    }while(((u8_data&0x01) != 0x01) && (u8_timeout != 0x00));

    if(u8_data != 0x01)
    {
        printf("[msb1240]LoadSdram2Sram, GDMA move code fail!!\n");
        return false;
    }

    //if(CodeNum == 0x02)
    //    bRet &= MSB1240_MEM_switch(2);  // setting for rom code
    //else
        bRet &= MSB1240_MEM_switch(1);

    if(bRet == false)
    {
        g_sram_code = 0x00;
    }
    else
    {
        g_sram_code = CodeNum;
    }
#if(TIMING_VERIFICATION == 1)
    tmm_18 = GIVE_ME_TIME
#endif
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]LoadSdram2Sram, codeNum=0x%x, g_sram_code=0x%x, bRet=0x%x\n",CodeNum,g_sram_code,bRet));
    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_Boot(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]LoadDspCodeToSDRAM_Boot\n"));

    if(!(g_sdram_code&MSB1240_BOOT))
    {
        if(u32SizeOfMSB1240_LIB > MSB1240_BOOT_START_ADDR)
        {
            // boot code
            data_ptr = MSB1240_LIB + MSB1240_BOOT_START_ADDR;
            code_size = MSB1240_BOOT_END_ADDR - MSB1240_BOOT_START_ADDR + 1;
            win_offset = MSB1240_BOOT_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);
            if(bRet == true)
            {
                g_sdram_code |= MSB1240_BOOT;
            }
        }
        else
        {
            printf("@msb1240, boot code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]LoadDspCodeToSDRAM_Boot\n"));
    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbt2(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]LoadDspCodeToSDRAM_dvbt2\n"));

    if( !(g_sdram_code&MSB1240_DVBT2) )
    {
        if(u32SizeOfMSB1240_LIB > MSB1240_DVBT2_P1_START_ADDR)
        {
    #if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2 == 1)
        if (bPreload_T2_en == MAPI_FALSE)
        {
            // dvbt2_p2
            data_ptr = MSB1240_LIB + MSB1240_DVBT2_P2_START_ADDR;
            code_size = MSB1240_DVBT2_P2_END_ADDR - MSB1240_DVBT2_P2_START_ADDR + 1;
            win_offset = MSB1240_DVBT2_P2_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);
            if (bRet == true)
            {
                bPreload_T2_en = MAPI_TRUE;
            }
            return bRet;
         }
         else
          {
             // dvbt2_p1
             data_ptr = MSB1240_LIB + MSB1240_DVBT2_P1_START_ADDR;
             code_size = MSB1240_DVBT2_P1_END_ADDR - MSB1240_DVBT2_P1_START_ADDR + 1;
             win_offset = MSB1240_DVBT2_P1_WINDOWS_OFFSET;
             bRet &= Load2Sdram(data_ptr,code_size,win_offset);

             if(bRet == true)
             {
                 g_sdram_code |= MSB1240_DVBT2;
             }
          }
        #else
        // dvbt2_p2
            data_ptr = MSB1240_LIB + MSB1240_DVBT2_P2_START_ADDR;
            code_size = MSB1240_DVBT2_P2_END_ADDR - MSB1240_DVBT2_P2_START_ADDR + 1;
            win_offset = MSB1240_DVBT2_P2_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);

            // dvbt2_p1
            data_ptr = MSB1240_LIB + MSB1240_DVBT2_P1_START_ADDR;
            code_size = MSB1240_DVBT2_P1_END_ADDR - MSB1240_DVBT2_P1_START_ADDR + 1;
            win_offset = MSB1240_DVBT2_P1_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);

            if(bRet == true)
            {
                g_sdram_code |= MSB1240_DVBT2;
            }
        #endif
        }
        else
        {
            ERR_DEMOD_MSB(printf("@msb1240, dvbt2 code is unavailable!!!\n"));
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]LoadDspCodeToSDRAM_dvbt2\n"));
    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbt(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]LoadDspCodeToSDRAM_dvbt\n"));
    if(!(g_sdram_code&MSB1240_DVBT))
    {
        // dvbt code
        if(u32SizeOfMSB1240_LIB > MSB1240_DVBT_START_ADDR)
        {
            data_ptr = MSB1240_LIB + MSB1240_DVBT_START_ADDR;
            code_size = MSB1240_DVBT_END_ADDR - MSB1240_DVBT_START_ADDR + 1;
            win_offset = MSB1240_DVBT_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);
            if(bRet == true)
            {
                g_sdram_code |= MSB1240_DVBT;
            }
        }
        else
        {
            printf("@msb1240, dvbt code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]LoadDspCodeToSDRAM_dvbt\n"));
    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbc(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]LoadDspCodeToSDRAM_dvbc\n"));
    if(!(g_sdram_code&MSB1240_DVBC))
    {
        // dvbc code
        if(u32SizeOfMSB1240_LIB > MSB1240_DVBC_START_ADDR)
        {
            data_ptr = MSB1240_LIB + MSB1240_DVBC_START_ADDR;
            code_size = MSB1240_DVBC_END_ADDR - MSB1240_DVBC_START_ADDR + 1;
            win_offset = MSB1240_DVBC_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);
            if(bRet == true)
            {
               g_sdram_code |= MSB1240_DVBC;
            }
        }
        else
        {
            printf("@msb1240, dvbc code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]LoadDspCodeToSDRAM_dvbc\n"));
    return bRet;
}
MAPI_BOOL LoadDspCodeToSDRAM_dvbs(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]LoadDspCodeToSDRAM_dvbs\n"));
    if(!(g_sdram_code&MSB1240_DVBS))
    {
        // dvbs code
        if(u32SizeOfMSB1240_LIB > MSB1240_DVBS_P1_START_ADDR)
        {
            // dvbs2_p2
            data_ptr = MSB1240_LIB + MSB1240_DVBS_P2_START_ADDR;
            code_size = MSB1240_DVBS_P2_END_ADDR - MSB1240_DVBS_P2_START_ADDR + 1;
            win_offset = MSB1240_DVBS_P2_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);

            // dvbs2_p1
            data_ptr = MSB1240_LIB + MSB1240_DVBS_P1_START_ADDR;
            code_size = MSB1240_DVBS_P1_END_ADDR - MSB1240_DVBS_P1_START_ADDR + 1;
            win_offset = MSB1240_DVBS_P1_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr,code_size,win_offset);
            if(bRet == true)
            {
               g_sdram_code |= MSB1240_DVBS;
            }
        }
        else
        {
            printf("@msb1240, dvbs code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]LoadDspCodeToSDRAM_dvbs\n"));
    return bRet;
}

// [0] bootloader [1] dvbt2, [2] dvbt, [3] dvbc [4] all
MAPI_BOOL LoadDspCodeToSDRAM(MAPI_U8 code_n)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]LoadDspCodeToSDRAM, code_n=0x%x\n",code_n));

#if(TIMING_VERIFICATION == 1)
    tmm_7 = GIVE_ME_TIME
#endif

    switch(code_n)
    {
        case MSB1240_BOOT:
            {
                // boot code
                bRet &= LoadDspCodeToSDRAM_Boot();
            }
        break;
        case MSB1240_DVBT2:
            {
                // dvbt2 code
                bRet &= LoadDspCodeToSDRAM_dvbt2();
            }
            break;
        case MSB1240_DVBT:
            {
                // dvbt
                bRet &= LoadDspCodeToSDRAM_dvbt();
            }
            break;
        case MSB1240_DVBC:
            {
                // dvbtc
                bRet &= LoadDspCodeToSDRAM_dvbc();
            }
            break;
        case MSB1240_DVBS:
            {
                // dvbts
                bRet &= LoadDspCodeToSDRAM_dvbs();
            }
            break;
        case MSB1240_ALL:
        default:
            {
                // boot+dvbt2+dvbt+dvbc+dvbs

                // boot code
                bRet &= LoadDspCodeToSDRAM_Boot();
                // dvbt2
                bRet &= LoadDspCodeToSDRAM_dvbt2();
                // dvbt
                bRet &= LoadDspCodeToSDRAM_dvbt();
                // dvbtc
                bRet &= LoadDspCodeToSDRAM_dvbc();
                // dvbs
                bRet &= LoadDspCodeToSDRAM_dvbs();
            }
            break;
    }

#if(TIMING_VERIFICATION == 1)
    tmm_8 = GIVE_ME_TIME
    show_timer();
#endif
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]LoadDspCodeToSDRAM, code_n=0x%x, bRet=0x%x\n",code_n,bRet));
    return bRet;
}

MAPI_BOOL DTV_DVBT2_DSPReg_Init(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    if( WriteDspReg((MAPI_U8)E_T2_BW, T2_BW_VAL) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)E_T2_FC_L, T2_FC_L_VAL) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)E_T2_FC_H, T2_FC_H_VAL) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)E_T2_TS_SERIAL, T2_TS_SERIAL) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)E_T2_TS_CLK_RATE, T2_TS_CLK_RATE_VAL) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)E_T2_TS_OUT_INV, T2_TS_OUT_INV_VAL) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)E_T2_TS_DATA_SWAP, T2_TS_DATA_SWAP_VAL) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)E_T2_TS_ERR_POL, T2_TS_ERR_POL_VAL) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U16)E_T2_IF_AGC_INV_PWM_EN, T2_IF_AGC_INV_PWM_EN_VAL) != TRUE)
    {
      printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U16)E_T2_SPREAD_SPAN, (MAPI_U16) T2_TS_SPREAD_SPAN) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }

    if( WriteDspReg((MAPI_U16)E_T2_SPREAD_STEP, (MAPI_U16) T2_TS_SPREAD_STEP_SIZE) != TRUE)
    {
        printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }

    if( WriteDspReg((MS_U8)E_T2_PHASE_TUNING_EN, T2_TS_PHASE_TUNING_EN) != TRUE)
    {
      printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MS_U8)E_T2_PHASE_TUNING_NUM, T2_TS_PHASE_TUNING_NUM) != TRUE)
    {
      printf("T2 dsp reg init NG\n"); return MAPI_FALSE;
    }

    printf("T2 dsp reg init ok\n");

    return MAPI_TRUE;
}

MAPI_BOOL  DTV_DVBT_DSPReg_Init(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    printf(" T_SERIAL_TS_VAL : %d\n", T_SERIAL_TS_VAL);
#if(TIMING_VERIFICATION == 1)
    tmm_7 = GIVE_ME_TIME
#endif
    if( WriteDspReg((MAPI_U8)T_CONFIG_BW, T_BW) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)T_CONFIG_FC_L, T_FC_L) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)T_CONFIG_FC_H, T_FC_H) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)T_CONFIG_IQ_SWAP, T_IQ_SWAP) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)T_CONFIG_TS_SERIAL, T_SERIAL_TS_VAL) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)T_CONFIG_TS_CLK_RATE, T_TS_CLK_SEL) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)T_CONFIG_TS_OUT_INV, T_TS_OUT_INV) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U8)T_CONFIG_TS_DATA_SWAP, T_TS_DATA_SWAP) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U16)T_CONFIG_IF_INV_PWM_OUT_EN, T_IF_INV_PWM_OUT_EN) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U16)T_CONFIG_SPREAD_SPAN, (MAPI_U16) T_TS_SPREAD_SPAN) != TRUE)
    {
        printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MAPI_U16)T_CONFIG_SPREAD_STEP, (MAPI_U16) T_TS_SPREAD_STEP_SIZE) != TRUE)
    {
         printf("T dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MS_U8)T_PHASE_TUNING_EN, T_TS_PHASE_TUNING_EN) != TRUE)
    {
      printf("dvbt dsp reg init NG\n"); return MAPI_FALSE;
    }
    if( WriteDspReg((MS_U8)T_PHASE_TUNING_NUM, T_TS_PHASE_TUNING_NUM) != TRUE)
    {
      printf("dvbt dsp reg init NG\n"); return MAPI_FALSE;
    }

#if(TIMING_VERIFICATION == 1)
    tmm_8 = GIVE_ME_TIME
    printf("[33333]t8 - t7 = %ld (%ld - %ld) \n",tmm_8-tmm_7,tmm_8,tmm_7);
#endif
    printf("dvbt dsp reg init ok\n");
    return MAPI_TRUE;
}

MAPI_BOOL DTV_DVBC_DSPReg_Init(void)
{
   DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8    idx = 0;

    for (idx = 0; idx<sizeof(MSB1240_DVBC_DSPREG_TABLE); idx++)
    {
        if( WriteDspReg(idx + 0x20, MSB1240_DVBC_DSPREG_TABLE[idx])!=TRUE)
        {
            ERR_DEMOD_MSB(printf("dvbc dsp reg init NG\n"));
            return MAPI_FALSE;
        }
    }

     if( WriteDspReg((MAPI_U16)C_config_spread_span, (MAPI_U16) C_TS_SPREAD_SPAN) != TRUE)
    {
        printf("C dsp reg init NG\n"); return MAPI_FALSE;
    }

    if( WriteDspReg((MAPI_U16)C_config_spread_step, (MAPI_U16) C_TS_SPREAD_STEP_SIZE) != TRUE)
    {
        printf("C dsp reg init NG\n"); return MAPI_FALSE;
    }

    if( WriteDspReg(C_phase_tuning_en, C_TS_PHASE_TUNING_EN)!=TRUE)
    {
        printf("dvbc dsp reg init NG\n");
        return MAPI_FALSE;
    }
    if( WriteDspReg(C_phase_tuning_num, C_TS_PHASE_TUNING_NUM)!=TRUE)
    {
        printf("dvbc dsp reg init NG\n");
        return MAPI_FALSE;
    }

    ERR_DEMOD_MSB(printf("DVBC dsp reg init ok\n"));

    return MAPI_TRUE;
}

MAPI_BOOL LoadDSPCode(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]LoadDspCode\n"));

    MAPI_U32        u32Timeout = 0;
    MAPI_U8         u8DoneFlag = 0;
    MAPI_U8         u8Data = 0;
    MAPI_BOOL       bRet = true;
    MAPI_U8         u8_timeout=0xff;
    MAPI_U8         FWversionH = 0xFF;
    MAPI_U8         FWversionL = 0xFF;

    DBG_DEMOD_MSB(printf(">>>MSB1240: Load DSP...\n"));

    DBG_DEMOD_FLOW(printf(" m_enCurrentDemodulator_Type=%u\n", m_enCurrentDemodulator_Type););

    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            u8Data=1;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            u8Data=2;
            break;
        case E_DEVICE_DEMOD_DVB_C:
            u8Data=3;
            break;
        case E_DEVICE_DEMOD_DVB_S:
            u8Data=4;
            break;
        default:
            u8Data=2;
            return MAPI_FALSE;
    }

    printf("this is load LoadDSPCode \n");
    if(g_WO_SPI_FLASH == 1)
    {//I2C or MSPI path
        MAPI_U8 u8FirmwareType = MSB1240_DVBT;
        // mask miu access for all and mcu
        bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x7f);
        bRet &= WriteReg(0x1200+(0x23)*2,0xfe);
        // 10us delay
        usleep(10);
        // Disable MCU
        bRet &= WriteReg(0x0b00+(0x19)*2, 0x03);
        switch (u8Data)
        {
            case 1:
                u8FirmwareType = MSB1240_DVBT2;
                break;
            case 2:
            default:
                u8FirmwareType = MSB1240_DVBT;
                break;
            case 3:
                u8FirmwareType = MSB1240_DVBC;
                break;
            case 4:
                u8FirmwareType = MSB1240_DVBS;
                break;
        }

        bRet &= LoadDspCodeToSDRAM(u8FirmwareType);

        bRet &= LoadSdram2Sram(u8FirmwareType);
        // enable miu access of mcu gdma
        bRet &= WriteReg(0x1200+(0x23)*2,0xf0);
        // 10us delay
        usleep(10);
        // Enable MCU
        bRet &= WriteReg(0x0b00+(0x19)*2, 0x00);

    }
    else
    {//flash path
    #if(TIMING_VERIFICATION == 1)
        tmm_9 = GIVE_ME_TIME
    #endif
        // mask miu access of fdp, tdi, djb
        printf("this is 2 \n");
        bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x0f);
        bRet &= WriteReg(0x1200+(0x23)*2,0xf0);

        // 10us delay
        usleep(10);

        // Disable MCU
        bRet &= WriteReg(0x0b00+(0x19)*2, 0x03);

        // Use GDMA move code from SDRAM to SRAM
         bRet &= WriteReg2bytes(0x0300+(0x00)*2, 0x4254);     // rst
         bRet &= WriteReg2bytes(0x0300+(0x00)*2, 0x4257);    // cfg & trig

       switch(u8Data)
       {
            case 0x01: //DVB-T2 @001000h ~ 008FFFh
                bRet &= WriteReg2bytes(0x0300+(0x01)*2, 0x0000); // Set src_addr
                bRet &= WriteReg2bytes(0x0300+(0x02)*2, 0x0010); // start from 1M
                break;

            case 0x02: //DVB-T @010000h ~ 017FFFh
                bRet &= WriteReg2bytes(0x0300+(0x01)*2, 0x0000); // Set src_addr
                bRet &= WriteReg2bytes(0x0300+(0x02)*2, 0x0011); // start from 1M+64k
                break;

            case 0x03: //DVB-C @018000h ~ 01FFFFh
                bRet &= WriteReg2bytes(0x0300+(0x01)*2, 0x8000); // Set src_addr
                bRet &= WriteReg2bytes(0x0300+(0x02)*2, 0x0011); // start from 1M+96k
                break;
            case 0x04: //DVB-S @ 0x20000h ~ 0x27ff0h
                bRet &= WriteReg2bytes(0x0300+(0x01)*2, 0x0000); // Set src_addr
                bRet &= WriteReg2bytes(0x0300+ (0x02)*2, 0x0012); // start from 1M+128k
                break;
                default:
                bRet &= false;
                break;
       }

        // Set dst_addr
        bRet &= WriteReg2bytes(0x0300+(0x03)*2, 0x0000);
        bRet &= WriteReg2bytes(0x0300+(0x04)*2, 0x0000);

        // Set data_size
        bRet &= WriteReg2bytes(0x0300+(0x05)*2, 0x8000);
        bRet &= WriteReg2bytes(0x0300+(0x06)*2, 0x0000);
        bRet &= WriteReg(0x0300+(0x07)*2, 0x01); //start GDMA

    #if(TIMING_VERIFICATION == 1)
        tmm_10 = GIVE_ME_TIME
        printf("[tmm8]t10 - t9 = %ld (%ld - %ld)\n",tmm_10-tmm_9,tmm_10,tmm_9);
    #endif
    /////////////////////////////////////////////////
        // Wait for GDMA
        do
        {
            bRet &= ReadReg(0x0300+(0x08)*2, &u8DoneFlag);

            if (u32Timeout++ > 500)
            return MAPI_FALSE;

            usleep(500);
        }while((u8DoneFlag&0x01) != 0x01);



        // Wait for GDMA
        do
        {
            MsOS_DelayTask(1);
            ReadReg(0x0300+ 0x10,&u8DoneFlag);
            u8_timeout--;
        }while(((u8DoneFlag&0x01) != 0x01) && (u8_timeout != 0x00));

        if((u8DoneFlag&0x01) != 0x01)
        {
            printf("Fail to LoadSdram2Sram!!");
            return MAPI_FALSE;
        }

        printf("this si 3 \n");
    #if(TIMING_VERIFICATION == 1)
        tmm_11 = GIVE_ME_TIME
        printf("[tmm8]t11 - t10 = %ld (%ld - %ld)\n",tmm_11-tmm_10,tmm_11,tmm_10);
    #endif
        //if(u8Data == 0x01)
        //    bRet &= MSB1240_MEM_switch(2);  // dvbt2 setting for rom code
        //else
            bRet &= MSB1240_MEM_switch(1);
        printf("this is 4 \n");
        // enable miu access of mcu gdma
        bRet &= WriteReg(0x1200+(0x23)*2,0xf0);
        //Disable romA_en & romB_en
        bRet &=WriteReg2bytes(0x1000+ (0x1c)*2, 0x0000);
        // 10us delay
        usleep(10);
        // Enable MCU
        WriteReg(0x0b00+(0x19)*2, 0x00);
    }
    ////////////////////////
#if(TIMING_VERIFICATION == 1)
    tmm_12 = GIVE_ME_TIME
    printf("[tmm8]t12 - t11 = %ld (%ld - %ld), TYPE is %d \n",tmm_12-tmm_11,tmm_12,tmm_11,m_enCurrentDemodulator_Type);
#endif

    printf("1: %d, 2:%d, 3:%d \n",E_DEVICE_DEMOD_DVB_T2,E_DEVICE_DEMOD_DVB_T,E_DEVICE_DEMOD_DVB_C);
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            printf("11111\n");
            DTV_DVBT2_DSPReg_Init();
            break;
        case E_DEVICE_DEMOD_DVB_T:
            printf("2222\n");
            DTV_DVBT_DSPReg_Init();
            break;
        case E_DEVICE_DEMOD_DVB_C:
            printf("3333\n");
            DTV_DVBC_DSPReg_Init();
            break;
        case E_DEVICE_DEMOD_DVB_S:
            IIC_Bypass_Mode(MAPI_TRUE);
        #if ENABLE_S2
            extern MS_BOOL MDrv_Tuner_Initial(void);
            bRet&=MDrv_Tuner_Initial();
        #endif
            IIC_Bypass_Mode(MAPI_FALSE);
            //bRet&=MSB131X_DiSEqC_Init();
            bRet &=ReadReg(0x0900+(0x44)*2, &FWversionL);
            bRet &=ReadReg(0x0900+(0x44)*2+0x0001, &FWversionH);
            printf("\r\n MSB1240_S FW version :    %X.%X\n",FWversionL,FWversionH);
            printf("4444\n");
            break;
        default:
            return MAPI_FALSE;
    }

#if(TIMING_VERIFICATION == 1)
    tmm_13 = GIVE_ME_TIME
    printf("[tmm8]t13 - t12 = %ld (%ld - %ld)\n",tmm_13-tmm_12,tmm_13,tmm_12);
#endif

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]LoadDspCode\n"));
    return bRet;
}

static MAPI_BOOL IspProcFlash(MAPI_U8* pLibArry, MAPI_U32 dwLibSize)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U32    dwLoop, dwTimeOut;
    MAPI_U32    dwStartAddr, dwEndAddr;
    MAPI_U8     bError = false;

    MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_SPI_IIC);
    iptr->WriteBytes(0, NULL, 5, bWriteData);

    dwStartAddr = (MAPI_U32) 0;
    dwEndAddr = dwLibSize;

    MAPI_U8     _bAddr[1];
    MAPI_U8     bReadData=0;
    for(dwLoop=dwStartAddr; (dwLoop < dwEndAddr); dwLoop+=PAGE_WRITE_SIZE)
    {
        dwTimeOut = 10000;
        while(dwTimeOut--)
        {
            _bAddr[0] = 0x10;
            bWriteData[0] = 0x05;
            iptr->WriteBytes(1, _bAddr, 1, bWriteData);

            _bAddr[0] = 0x11;
            iptr->ReadBytes(1, _bAddr, 1, &bReadData);

            bWriteData[0] = 0x12;
            iptr->WriteBytes(0, NULL, 1, bWriteData);

            if (!(bReadData & 0x01))
                break;

            if(dwTimeOut==1)
            {
                bError = 1;
                break;
            }
            usleep(0);
        }

        if(!bError)
        {

            MAPI_U8    bAddr[5], _bWriteData[1];
            MAPI_BOOL _bError = TRUE;

            mapi_i2c *_iptr = mapi_i2c_GetI2C_Dev(MSB124X_SPI_IIC);
            bAddr[0] = 0x10;
            _bWriteData[0] = 0x06;
            _bError &= _iptr->WriteBytes(1, bAddr, 1, _bWriteData);

            _bWriteData[0] = 0x12;
            _bError &= _iptr->WriteBytes(0, NULL, 1, _bWriteData);

            // Page Program
            bAddr[0] = 0x10;
            bAddr[1] = 0x02;
            bAddr[2] = dwLoop >> 16;
            bAddr[3] = dwLoop >> 8;
            bAddr[4] = dwLoop;

            _bError &= _iptr->WriteBytes(5, bAddr, PAGE_WRITE_SIZE, (pLibArry+dwLoop));

            _bWriteData[0] = 0x12;
            _bError &=  _iptr->WriteBytes(0, NULL, 1, _bWriteData);

            bAddr[0] = 0x10;
            _bWriteData[0] = 0x04;
            _bError &=  _iptr->WriteBytes(1, bAddr, 1, _bWriteData);

            _bWriteData[0] = 0x12;
                _bError &=  _iptr->WriteBytes(0, NULL, 1, _bWriteData);

            if(_bError == FALSE)
            {
                break;
            }
        }
    }

    bWriteData[0]=0x24 ;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    if(bError==false)
        return MAPI_TRUE;
    else
        return MAPI_FALSE;
}

/*@ <Operation ID=I2b28dd03m121c8cf959bmm722c> @*/
#if (MSB123x_T2MI_DJB_RST_EN == 1)
MAPI_BOOL MSB123x_DJB_RST(void)
{
    return TRUE;
}
#endif

MAPI_BOOL MSB124X_ExtendCmd(MAPI_U8 SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void *pvParam3)
{
    MAPI_U8 u8Data = 0;
    MAPI_U8 u8Status = MAPI_TRUE;
    // return false if power_on_initialization() is not finished
    if (MAPI_TRUE != bPower_init_en)
    {
        return MAPI_FALSE;
    }
    //DBG_DEMOD_FLOW(printf("\r\n ===>> Enter, %s(),%d,SubCmd = %x,u32Param1 = %x,u32Param2 = %x\n",__func__,__LINE__,SubCmd,u32Param1,u32Param2));
    SubCmd=SubCmd;
    u32Param1=u32Param1;
    u32Param2=u32Param2;
    pvParam3=pvParam3;

    if(SubCmd == 1)
    {
        //1 => write
        // printf("[dvbt2]write register\n");
        return WriteReg((MS_U16) u32Param1, (MS_U8) u32Param2);
    }

    if(SubCmd == 2)
    {
        //2 =>    Read
        // printf("[dvbt2]read register\n");
        return ReadReg((MS_U16)u32Param1, (MS_U8*)pvParam3);
    }

    if(SubCmd == 0x10)
    {
        MAPI_U8 TR0 = 0;
        MAPI_U8 TR1 = 0;
        MAPI_U8 TR2 = 0;
        if(ReadReg(0x1b00+(0x0e)*2+1, &TR0) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
        if(ReadReg(0x3300+(0x19)*2+1, &TR1) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
        if(ReadReg(0x3300+(0x29)*2+1, &TR2) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
        if((((TR0|TR1|TR2)&0x01) == 0x00) &&
            (msAPI_Timer_DiffTimeFromNow(_u32LocktimeStart) > TR_TIME_OUT_WITH_FIX_SYMBOL_RATE) &&
            (_u32CurrentSR != 0)
        )
        {
            *((MAPI_U8*)pvParam3) = 0;
        }
        else
        {
            *((MAPI_U8*)pvParam3) = 1;
        }
    }

    if (SubCmd == 0x77)
    {
#if 0
        if (FECLock == TRUE)
            u8_g_pid0_timeout_flag = 1;
        else
            u8_g_pid0_timeout_flag = 0;
#endif
    }

    if (SubCmd == 0x80) // temp solution, to turn on/off IF AGC
    {
        if (u32Param1 == MAPI_TRUE)         // turn on
        {
            u8Status &= ReadReg(0x0a00+(0x18)*2, &u8Data);
            u8Data = u8Data|0x01;
            u8Status &= WriteReg(0x0a00+(0x18)*2, u8Data);
            DBG_DEMOD_MSB(printf("MSB1240: Turn on IF AGC: %02x\n", u8Data));
        }
        else if (u32Param1 == MAPI_FALSE)     // turn off
        {
            u8Status &= ReadReg(0x0a00+(0x18)*2, &u8Data);
            u8Data = u8Data&(0xff-0x01);
            u8Status &= WriteReg(0x0a00+(0x18)*2, u8Data);
            DBG_DEMOD_MSB(printf("MSB1240: Turn off IF AGC: %02x\n", u8Data));
        }
    }

    // DVB-T2 Tri-State setting
    // MAPI_FALSE(0) : Disable Tri-State, enable DVB-T2 output
    // MAPI_TRUE(1) : Enable Tri-State, disable DVB-T2 output
    if(SubCmd == 0x81)
    {
        if(u32Param1 == MAPI_TRUE)
        {
            WriteReg2bytes(0x0900+(0x2d)*2, 0x0000);
            DBG_DEMOD_MSB(printf("MSB1240: Disable extend demod TS PAD\n"));
        }
        else
        {
            WriteReg2bytes(0x0900+(0x2d)*2, 0x00ff);
            DBG_DEMOD_MSB(printf("MSB1240: Enable extend demod TS PAD\n"));
        }
    }

    if(SubCmd == 0x82)    // to turn on/off null packet insert
    {
        if(u32Param1 == 1)    // null packet on
        {
            //DVBT2
            u8Status &= ReadReg(0x2a00 + (0x20) * 2 , &u8Data);
            u8Status &= WriteReg(0x2a00 + (0x20) * 2 , (u8Data |0x80));
            //DVBT/C
            u8Status &= ReadReg(0x1100 + (0x20) * 2 , &u8Data);
            u8Status &= WriteReg(0x1100 + (0x20) * 2 , (u8Data |0x80));
        }
        else if(u32Param1 == 0)     // null packet off
        {
            //DVBT2
            u8Status &= ReadReg(0x2a00 + (0x20) * 2 , &u8Data);
            u8Status &= WriteReg(0x2a00 + (0x20) * 2 , (u8Data & (~0x80)));
            //DVBT/C
            u8Status &= ReadReg(0x1100 + (0x20) * 2 , &u8Data);
            u8Status &= WriteReg(0x1100 + (0x20) * 2 , (u8Data & (~0x80)));
        }
    }

    // get fef indiator
    if (SubCmd == 0x83)
    {
        MAPI_U8 u8Data_0 = 0;
        u8Status &= ReadDspReg(E_T2_FEF_DET_IND, &u8Data_0);
        *((MAPI_U8*)pvParam3) = u8Data_0;

//          printf("[dvbt2]get fef indicator = %d\n",u8Data);
    }

    // get CFO(frequency offset) value
    // Unit: kHz
    // Real_RF = Nominal_RF + fCFO.
    if (SubCmd == 0x84)
    {
        bool   status = true;

        // get CFO(frequency offset) value
        // Unit: kHz

        switch(m_enCurrentDemodulator_Type)
        {
            case E_DEVICE_DEMOD_DVB_T2:
            {
                float fCFO = 0.0;
                //MAPI_U8  u8Data = 0;
                MAPI_U8  u8_freeze = 0;
                MAPI_U16  u16Data = 0;
                MAPI_S16  s16_cfo10 = 0;

                // freeze
                status &= ReadReg(DIG_DBG_BASE+0x28*2+1, &u8_freeze);
                status &= WriteReg(DIG_DBG_BASE+0x28*2+1, u8_freeze|0x80);

                status &=ReadDspReg((MAPI_U16)E_T2_TOTAL_CFO_1, &u8Data);
                u16Data = u8Data;
                status &=ReadDspReg((MAPI_U16)E_T2_TOTAL_CFO_0, &u8Data);
                u16Data = (u16Data<<8)|u8Data;

                // unfreeze
                status &= WriteReg(DIG_DBG_BASE+0x28*2+1, u8_freeze);

                s16_cfo10 = (MAPI_S16)u16Data;
                fCFO = (float)s16_cfo10/10.0;

                 *((float*)pvParam3) = fCFO ;
            }
            break;

        case E_DEVICE_DEMOD_DVB_T:
        {
                float fCFO = 0.0;
                //MAPI_U8  u8Data = 0;
                MAPI_U8  u8_freeze = 0;
                MAPI_U16  u16Data = 0;
                MAPI_S16  s16_cfo10 = 0;

                // freeze
                status &= ReadReg(DIG_DBG_BASE+0x29*2, &u8_freeze);
                status &= WriteReg(DIG_DBG_BASE+0x29*2, u8_freeze|0x01);

                status &=ReadDspReg((MAPI_U16)T_CFO10K_H, &u8Data);
                u16Data = u8Data;
                status &=ReadDspReg((MAPI_U16)T_CFO10K_L, &u8Data);
                u16Data = (u16Data<<8)|u8Data;

                // unfreeze
                status &= WriteReg(DIG_DBG_BASE+0x29*2, u8_freeze);

                s16_cfo10 = (MAPI_S16)u16Data;
                fCFO = (float)s16_cfo10/10.0;
                *((float*)pvParam3) = fCFO ;
        }
            break;
        case E_DEVICE_DEMOD_DVB_C:
        {
                //MAPI_BOOL status = true;
                MAPI_U8 reg_frz = 0;
                MAPI_U16 u16_tmp = 0;
                MAPI_S16 s16_cfo10 = 0;
                //u8BW = u8BW;
                // freeze
                status &= ReadReg(DIG_DBG_BASE+0x52, &reg_frz);
                status &= WriteReg(DIG_DBG_BASE+0x52, reg_frz|0x01);

                status &=ReadDspReg((MAPI_U16)C_CFO10_H, &u8Data);
                u16_tmp = u8Data;
                status &=ReadDspReg((MAPI_U16)C_CFO10_L, &u8Data);
                u16_tmp = (u16_tmp<<8)|u8Data;

                // unfreeze
                reg_frz=reg_frz&(~0x01);
                status &= WriteReg(DIG_DBG_BASE+0x52, reg_frz);

                s16_cfo10 = (MAPI_S16)u16_tmp;
                *((float*)pvParam3) = (float)s16_cfo10/10.0;
        }
            break;
        default:
             *((float*)pvParam3) = 0;
        }
        return status;

    }

    // sleep mode
    if (SubCmd == 0x85)
    {
        MAPI_U8      u8Data_1  = 0x00;
        MAPI_U16     u16Retry = 0x00;
        static MAPI_U8 u8_mcu_save = 0;

        // sleep mode enable
        if (u32Param1 == 1)
        {
        #if (MSB1240_SW_SLEEP_MODE_EN == 1)
            // mask miu access for all and mcu
            WriteReg(0x1200+(0x23)*2 + 1,0x7f);
            WriteReg(0x1200+(0x23)*2,0xfe);
            // 10us delay
            usleep(10);

            WriteReg(0x0B00 + (0x10) * 2, 0x01);
            WriteReg(0x0B00 + (0x19) * 2, 0x03);
            WriteReg(REG_MB_CNTL, 0x00);             //clear MB_CNTL
            usleep(5 * 100);

            // ADC turn off.
            ReadReg(0x0900+(0x0B)*2,&u8Data_1);
            u8_mcu_save = u8Data_1;
            u8Data_1 |= 0x20;
            WriteReg(0x0900+(0x0B)*2,u8Data_1);

            ReadReg(0x0A00+(0x0C)*2,&u8Data_1);
            u8Data_1 |= 0x03;
            WriteReg(0x0A00+(0x0C)*2,u8Data_1);

            // ReadReg(0x0A00+(0x35)*2,&u8Data);
            // u8Data |= 0x80;
            // WriteReg(0x0A00+(0x35)*2,u8Data);

            g_u8_msb1240_sleep_mode_status = 1;
        #else
            mapi_gpio *gptr = NULL;
            // gptr = mapi_gpio::GetGPIO_Dev(MSB1240_HW_SLEEP_PIN);

            // mask miu access for all and mcu
            WriteReg(0x1200+(0x23)*2 + 1,0x7f);
            WriteReg(0x1200+(0x23)*2,0xfe);
            // 10us delay
            usleep(10);

            WriteReg(0x0B00 + (0x10) * 2, 0x01);
            WriteReg(0x0B00 + (0x19) * 2, 0x03);
            WriteReg(REG_MB_CNTL, 0x00);             //clear MB_CNTL
            usleep(5 * 100);

            // TS pad off
            WriteReg2bytes(0x0900+(0x2d)*2, 0x0000);

            // IF_AGC_T pad off
            u8Status &= ReadReg(0x0a00+(0x18)*2, &u8Data_1);
            u8Data_1 = u8Data_1&(0xff-0x01);
            u8Status &= WriteReg(0x0a00+(0x18)*2, u8Data_1);

            // IF_AGC_S pad off
            u8Status &= ReadReg(0x0a00+(0x18)*2+1, &u8Data_1);
            u8Data_1 = u8Data_1&(0xff-0x01);
            u8Status &= WriteReg(0x0a00+(0x18)*2+1, u8Data_1);

            // ADC turn off.
            ReadReg(0x0900+(0x0B)*2,&u8Data_1);
            u8_mcu_save = u8Data_1;
            u8Data_1 |= 0x20;
            WriteReg(0x0900+(0x0B)*2,u8Data_1);

            printf("%s, %d, r, u8_mcu_save=0x%x\n",__FILE__,__LINE__,u8_mcu_save);

            ReadReg(0x0A00+(0x0C)*2,&u8Data_1);
            u8Data_1 |= 0x03;
            WriteReg(0x0A00+(0x0C)*2,u8Data_1);

            // SR begin.
            WriteReg2bytes(0x1200+(0x01)*2, 0x0101);
            WriteReg2bytes(0x1200+(0x23)*2, 0xfffe);
            WriteReg2bytes(0x1200+(0x1c)*2, 0x00b2);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x00)*2, 0x0101);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x00)*2, 0x0301);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x00)*2, 0x0501);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x00)*2, 0x0001);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x23)*2, 0xffff);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x01)*2, 0x0103);

            WriteReg2bytes(0x1200+(0x1c)*2, 0x00b0);

            usleep(1*1000);
            //SR end

            // waiting for SR completed...
            usleep(10*1000);

            // turn off MPLL
            ReadReg(0x0A00+(0x35)*2,&u8Data_1);
            u8Data_1 |= 0x80;
            WriteReg(0x0A00+(0x35)*2,u8Data_1);
            // gpio pull low
            if(gptr != NULL)
            {
                gptr->SetOff();
            }
            else
            {
                printf("where is gpio??, %s, %s, %d",__FILE__,__FUNCTION__,__LINE__);
            }
            g_u8_msb1240_sleep_mode_status = 2;
            printf("%s,%d, g_u8_msb1240_sleep_mode_status=%d\n",__FILE__,__LINE__,g_u8_msb1240_sleep_mode_status);
        #endif
        }
        else
        {
        #if (MSB1240_SW_SLEEP_MODE_EN == 1)

            // ADC turn on.
            // ReadReg(0x0A00+(0x35)*2,&u8Data);
            // u8Data &= (0xff-0x80);
            // WriteReg(0x0A00+(0x35)*2,u8Data);

            ReadReg(0x0A00+(0x0C)*2,&u8Data_1);
            u8Data_1 &= (0xff-0x03);
            WriteReg(0x0A00+(0x0C)*2,u8Data_1);

            WriteReg(0x0900+(0x0B)*2,u8_mcu_save);

            // enable miu access of mcu gdma
            WriteReg(0x1200+(0x23)*2,0xf0);
            // 10us delay
            usleep(10);

            WriteReg(0x0B00 + (0x19) * 2, 0x00);
            WriteReg(0x0B00 + (0x10) * 2, 0x00);
            usleep(5 * 1000);
            ReadReg(REG_MB_CNTL, &u8Data_1);             //check MB_CNTL ready
            do
            {
                if (u8Data_1 == 0xff) //wake up from sleep mode successfully
                {
                    g_u8_msb1240_sleep_mode_status = 0;
                    printf(">>>MSB1240: wake up Success!\n");
                    break;
                }
                else // still in sleep mode
                {
                    usleep(50*1000);
                    ReadReg(REG_MB_CNTL, &u8Data_1);         //check MB_CNTL ready
                    u16Retry++;
                    printf(">>>MSB1240: wake up Fail! (u16Retry: %d) \n", u16Retry);
                }
            } while(u16Retry < 20);
        #else
            mapi_gpio *gptr = NULL;
            // gptr = mapi_gpio::GetGPIO_Dev(MSB1240_HW_SLEEP_PIN);
            // gpio pull high
            if(gptr != NULL)
            {
                gptr->SetOn();
            }
            else
            {
                printf("where is gpio??, %s, %s, %d",__FILE__,__FUNCTION__,__LINE__);
            }

            // waiting for xtal stablized
            usleep(50*1000);

            g_u8_msb1240_sleep_mode_status = 1;

            // Turn on MPLL
            ReadReg(0x0A00+(0x35)*2,&u8Data_1);
            u8Data_1 &= (0xff-0x80);
            WriteReg(0x0A00+(0x35)*2,u8Data_1);

            // SR begin
            WriteReg2bytes(0x1200+(0x1c)*2, 0x00b2);
            WriteReg2bytes(0x1200+(0x01)*2, 0x0101);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x23)*2, 0xfffe);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x00)*2, 0x0501);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x00)*2, 0x0301);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x00)*2, 0x0501);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x00)*2, 0x0001);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x1c)*2, 0x00b0);

            usleep(1*1000);

            WriteReg2bytes(0x1200+(0x01)*2, 0x010d);

            usleep(1*1000);

            // WriteReg2bytes(0x1200+(0x23)*2, 0x0000);

            // usleep(1*1000);
            //SR End

            // waiting for SR completed...
            usleep(10*1000);

            // ADC turn on.
            ReadReg(0x0A00+(0x0C)*2,&u8Data_1);
            u8Data_1 &= (0xff-0x03);
            WriteReg(0x0A00+(0x0C)*2,u8Data_1);

            // ReadReg(0x0900+(0x0B)*2,&u8Data);
            // u8Data &= (0xff-0x20);
            WriteReg(0x0900+(0x0B)*2,u8_mcu_save);
            printf("%s, %d, w, u8_mcu_save=0x%x\n",__FILE__,__LINE__,u8_mcu_save);

            // enable miu access of mcu gdma
            WriteReg(0x1200+(0x23)*2,0xf0);
            // 10us delay
            usleep(10);

            WriteReg(0x0B00 + (0x19) * 2, 0x00);
            WriteReg(0x0B00 + (0x10) * 2, 0x00);
            usleep(5 * 1000);
            ReadReg(REG_MB_CNTL, &u8Data_1);             //check MB_CNTL ready
            do
            {
                if (u8Data_1 == 0xff) //wake up from sleep mode successfully
                {
                    g_u8_msb1240_sleep_mode_status = 0;
                    printf(">>>MSB1240: wake up Success!\n");
                    break;
                }
                else // still in sleep mode
                {
                    usleep(50*1000);
                    ReadReg(REG_MB_CNTL, &u8Data_1);         //check MB_CNTL ready
                    u16Retry++;
                    printf(">>>MSB1240: wake up Fail! (u16Retry: %d) \n", u16Retry);
                }
            } while(u16Retry < 20);
            printf("%s,%d, g_u8_msb1240_sleep_mode_status=%d\n",__FILE__,__LINE__,g_u8_msb1240_sleep_mode_status);
        #endif
        }
    }

    // ADC enable(1)/disable(0)
    if (SubCmd == 0x86)
    {
        MAPI_U8      u8Data_2  = 0x00;
        MAPI_U16     u16Retry = 0x00;

        if (g_u8_msb1240_sleep_mode_status > 1)
        {
            printf("%s, %s, %d, MSB1240 is sleeping, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
            return FALSE;
        }

        // adc power disable
        if (u32Param1 == 0)
        {
            // mask miu access for all and mcu
            WriteReg(0x1200+(0x23)*2 + 1,0x7f);
            WriteReg(0x1200+(0x23)*2,0xfe);
            // 10us delay
            usleep(10);

            WriteReg(0x0B00 + (0x10) * 2, 0x01);
            WriteReg(0x0B00 + (0x19) * 2, 0x03);
            WriteReg(REG_MB_CNTL, 0x00);             //clear MB_CNTL
            usleep(5 * 100);

            // ADC turn off.
            ReadReg(0x0A00+(0x0C)*2,&u8Data_2);
            u8Data_2 |= 0x03;
            WriteReg(0x0A00+(0x0C)*2,u8Data_2);

            // ReadReg(0x0A00+(0x35)*2,&u8Data);
            // u8Data |= 0x80;
            // WriteReg(0x0A00+(0x35)*2,u8Data);
            g_u8_msb1240_adc_mode_status  = 1;
        }
        else
        {
            // ADC turn on.
            // ReadReg(0x0A00+(0x35)*2,&u8Data);
            // u8Data &= (0xff-0x80);
            // WriteReg(0x0A00+(0x35)*2,u8Data);

            ReadReg(0x0A00+(0x0C)*2,&u8Data_2);
            u8Data_2 &= (0xff-0x03);
            WriteReg(0x0A00+(0x0C)*2,u8Data_2);

            // enable miu access of mcu gdma
            WriteReg(0x1200+(0x23)*2,0xf0);
            // 10us delay
            usleep(10);

            WriteReg(0x0B00 + (0x19) * 2, 0x00);
            WriteReg(0x0B00 + (0x10) * 2, 0x00);
            usleep(5 * 1000);
            ReadReg(REG_MB_CNTL, &u8Data_2);             //check MB_CNTL ready
            do
            {
                if (u8Data_2 == 0xff) //wake up from sleep mode successfully
                {
                    printf(">>>MSB1240: ADC Enable Success!\n");
                    g_u8_msb1240_adc_mode_status  = 0;
                    break;
                }
                else // still in sleep mode
                {
                    usleep(50*1000);
                    ReadReg(REG_MB_CNTL, &u8Data_2);         //check MB_CNTL ready
                    u16Retry++;
                    printf(">>>MSB1240: ADC Enable Fail! (u16Retry: %d) \n", u16Retry);
                }
            } while(u16Retry < 20);
        }
    }

    // set TS serial mode, TS data swap, TS CLK inverse
    // Para1. for DVBSS2 TS output mode
    if (SubCmd == 0x87)
    {
      DBG_DEMOD_FLOW(printf("DVBSS2 TS out configuration:\n TS serial mode %d \n ",(MAPI_U8)u32Param1));
      S_TS_Output_VAL = (MAPI_U8)u32Param1;
    }
    // Para1. for DVBSS2 TS data swap on/off
    if (SubCmd == 0x88)
    {
      DBG_DEMOD_FLOW(printf("DVBSS2 TS out configuration:\n TS data SWAP mode %d \n",(MAPI_U8)u32Param1));
      S_TS_DataSwap_VAL = (MAPI_U8)u32Param1;
    }
    // Para1. for DVBSS2 TS CLK inverse on/off
    if (SubCmd == 0x89)
    {
      DBG_DEMOD_FLOW(printf("DVBSS2 TS out configuration:\n TS CLK inv mode %d\n",(MAPI_U8)u32Param1));
      S_TS_clk_inv_VAL = (MAPI_U8)u32Param1;
    }

    if (SubCmd == 0xEE)
    {
        MAPI_BOOL bRet = TRUE;
       // bRet &= MSB1240_demod_info((t2_mod_info*)pvParam3);
        if (bRet == FALSE)
            printf("ERROR!!!!!!!!!!!!!!!\n");
    }

    if (SubCmd == 0xFF) // temp solution, only for internal use, can't be called by upper layer
    {
        MAPI_U32    u32Timeout;
        MAPI_U32    u32LockTimeout=2000;
        MAPI_U8     u8Data_3 = 0;
        MAPI_U16    u16RegAddress;
        MAPI_U8     u8BitMask;
        MAPI_BOOL    bCheckPass=FALSE;
        static MAPI_U32 u32LockTimeStartDVBT = 0;
        static MAPI_U32 u32LockTimeStartDVBC = 0;//mick
        static MAPI_U32 u32LockTimeStartDVBT2 = 0;
        MAPI_U32 u32NowTime=MsOS_GetSystemTime();
        MAPI_U8     u8_fef_ind = 0;
        // MAPI_U8 tmp1, tmp2, tmp3;
        // printf("EXTCMD:0xFF. \n");
        switch(m_enCurrentDemodulator_Type)
        {
            case E_DEVICE_DEMOD_DVB_T2:
            {
                //DBG_DEMOD_MSB(printf("EXTCMD:0xFF.--->>> T2 T2 T2\n"));
                u32Timeout=8000;

                ReadDspReg(E_T2_DVBT2_LOCK_HIS, &u8Data_3);

                ReadDspReg(E_T2_FEF_DET_IND, &u8_fef_ind);
                if (u8_fef_ind == 1)
                    u32Timeout = 12000;

                //MAPI_U8 tmp1, tmp2, tmp3;
                //printf("=>[Debug] E_T2_DVBT2_LOCK_HIS = %d,p1_ever_lock_flag = %d,bDoReset = %d\n", u8Data_3,p1_ever_lock_flag,bDoReset);
                //ReadDspReg(E_T2_FW_VER_0, &tmp1);
                //ReadDspReg(E_T2_FW_VER_1, &tmp2);
                //ReadDspReg(E_T2_FW_VER_2, &tmp3);
                //printf("=========================>[Debug] FW Ver = %x.%x.%x\n", tmp1, tmp2, tmp3);
                //ReadReg(0x0990, &tmp1);
                //printf("=========================>[Debug] State = %d \n", tmp1);

                if((u8Data_3 & BIT7) != 0x00)
                    bCheckPass=MAPI_TRUE;
                else
                {
                    if (p1_ever_lock_flag == 0)
                    {
                        u16RegAddress = E_T2_DVBT2_LOCK_HIS; //P1 Lock History
                        u8BitMask = BIT5;
                        ReadDspReg(u16RegAddress, &u8Data_3);
                        if((u8Data_3&u8BitMask) == 0)
                        {
                            // Fix me please!
                            // Tmp solution: this timeout value needs to correct. (move to UpperLayer)
                            u32Timeout=600; //1500;//2000;
                        }
                        else
                        {
                            p1_ever_lock_flag = 1;
                        }
                    }
                }

                DBG_DEMOD_MSB(printf(">>>MSB1240: [%s] Lock Status = %d\n", __FUNCTION__, u8Data_3));
                if (bCheckPass)
                {

                    u32LockTimeStartDVBT2=MsOS_GetSystemTime();

                    FECLock = MAPI_TRUE;
                    if(bDoReset == TRUE)
                    {
                        printf("[msb1240]++++DVBT2 lock, freq=%ld\n",g_u32Frequency);
                        DBG_DEMOD_MSB(printf("\t\t\tDTV_DVB_T_GetLockStatus(LOCK/T2) TIME    %ld(=%ld-%ld)\n", u32LockTimeStartDVBT2-u32StartTime, u32LockTimeStartDVBT2, u32StartTime));//to measure time
                    #if (TIMING_VERIFICATION==1)
                        tmm_14 = GIVE_ME_TIME
                        show_timer();
                    #endif
                    }
                    bDoReset = FALSE;
                    *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_LOCK;
                }
                else if ((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                    ||(u32NowTime - u32LockTimeStartDVBT2 < u32LockTimeout))
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_CHECKING;
                }
                else
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_UNLOCK;
                }

                if ( (FECLock == MAPI_TRUE) && (u8_g_pid0_timeout_flag == 1))
                {
                    MS_U16 bch_eflag2_sum = 0;
                    MS_U8  reg = 0;

                    ReadReg(0x2600+0x26*2 + 1,&reg);
                    bch_eflag2_sum = reg;
                    ReadReg(0x2600+0x26*2,&reg);
                    bch_eflag2_sum = (bch_eflag2_sum<<8)|reg;

                    if (bch_eflag2_sum == 0x00)
                    {
                        //djb rst
                        ReadReg(0x2900+0x00*2,&reg);
                        reg |= 0x01;
                        WriteReg(0x2900+0x00*2,reg);
                        usleep(1000);
                        ReadReg(0x2900+0x00*2,&reg);
                        reg &= (0xff-0x01);
                        WriteReg(0x2900+0x00*2,reg);
                        printf("\ndjb_rst........\n");
                        // DBG_DEMOD_MSB(printf("\n......[mj]djb rst......\n");)
                    }
                    u8_g_pid0_timeout_flag = 0;
                }
            }
            break;
            case E_DEVICE_DEMOD_DVB_T:
               {
                    u32Timeout=1500;
                    ReadDspReg(T_DVBT_LOCK_HIS, &u8Data);
                    DBG_DEMOD_MSB(printf(">>>MSB1240: [%s] Lock Status = %d\n", __FUNCTION__, u8Data));
                    if( (u8Data&BIT6) == BIT6 )
                    {
                        bCheckPass=MAPI_TRUE;
                    }
                    else if ( (u8Data&BIT3) == BIT3 )
                    {
                        u32Timeout=6000;
                    }
                    //DBG_DEMOD_MSB(printf(">>>MSB1240: [%s] Lock Status = %d\n", __FUNCTION__, u8Data));
                    if (bCheckPass)
                    {
                        u32LockTimeStartDVBT=MsOS_GetSystemTime();
                        FECLock = MAPI_TRUE;
                        if(bDoReset==TRUE)
                        {
                            printf("[msb1240]++++DVBT lock, freq=%ld\n",g_u32Frequency);
                            DBG_DEMOD_MSB(printf("\t\t\tDTV_DVB_T_GetLockStatus(LOCK/T) TIME   %ld(=%ld-%ld)\n", u32LockTimeStartDVBT-u32StartTime, u32LockTimeStartDVBT, u32StartTime));//to measure time
                            #if (TIMING_VERIFICATION==1)
                                tmm_14 = GIVE_ME_TIME
                                show_timer();
                            #endif
                        }
                        bDoReset = FALSE;
                        *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_LOCK;
                    }
                    else if ((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                            ||(u32NowTime - u32LockTimeStartDVBT < u32LockTimeout))
                    {
                        FECLock = MAPI_FALSE;
                        *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_CHECKING;
                    }
                    else
                    {
                        FECLock = MAPI_FALSE;
                        *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_UNLOCK;
                    }
                }
                break;
            case E_DEVICE_DEMOD_DVB_C://mick
           {
                //mapi_tuner *pTuner=NULL;
                float fRFLevel=0.0f;
                MS_U8  u8DemodState = 0;
                MS_U32 u32u32Timeout_NoSignal = 400;
                u32Timeout=500;//1500;
                u16RegAddress=0x11E0;
                    //u8LockState=0x0C;
                ReadReg(u16RegAddress, &u8DemodState);
                //printf("[msb1240]+++++++++DVBC State---->%d\n",u8DemodState);//mick
                /*
                pTuner = mapi_interface::Get_mapi_pcb()->GetDvbtTuner(0);
                if (pTuner!=NULL)
                {
                    if ( MAPI_FALSE == pTuner->ExtendCommand(mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_LEVEL, 1, 0, &fRFLevel))
                    {
                        fRFLevel=200.0f;
                    }
                    else
                    {
                        // add for 1% SSI, remove if not necessary
                        // fRFLevel += (((float)rand()/(float)RAND_MAX) -0.5f);
                    }
                }
                else
                {
                    fRFLevel=200.0f;
                }
              */
                  if( (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER)\
                     || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)  \
                     || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)    \
                     || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)    \
                     || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)     \
                     || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)     \
                     || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)    \
                     || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)  \
                     || (FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
                     )
                    {
                         mdev_GetSignalStrength(&fRFLevel);
                    }
                    ReadDspReg(C_lock_indicator, &u8Data);
                    if( (u8Data & BIT7) == BIT7 )//FEC Lock Indicator
                    {
                        bCheckPass=MAPI_TRUE;
                    }
                    else if ( (u8Data&BIT0) == BIT0 )//TR Lock_history Indicator
                    {
                    u32Timeout=1900;//6000;
                    }
                
                if((fRFLevel < -90.0) && (u8DemodState <= 6))
                    {
                    // if signal strength < minimum sensitivity, go to no_channel case
                    // spec.~-77dBm (16QAM)
                    u32Timeout=u32u32Timeout_NoSignal;
                    }
                //DBG_DEMOD_MSB(printf(">>>MSB1240: [%s] Lock Status = %d\n", __FUNCTION__, u8Data));
                if (bCheckPass)
                {
                    u32LockTimeStartDVBC=MsOS_GetSystemTime();
                    FECLock = MAPI_TRUE;
                    if(bDoReset==TRUE)
                    {
                        printf("[msb1240]++++DVBC lock, freq=%d\n",g_u32Frequency);
                        DBG_DEMOD_MSB(printf("\t\t\tDTV_DVB_C_GetLockStatus(LOCK/C) TIME   %d(=%d-%d)\n", u32LockTimeStartDVBC-u32StartTime, u32LockTimeStartDVBC, u32StartTime));//to measure time
#if (TIMING_VERIFICATION==1)
                        tmm_14 = GIVE_ME_TIME
                        show_timer();
#endif
                    }
                    bDoReset = FALSE;
                    *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_LOCK;
                }
                else if ((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                ||(u32NowTime - u32LockTimeStartDVBC < u32LockTimeout))
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_CHECKING;
                }
                else
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_UNLOCK;
                }
            }
                break;
            default:
                *((EN_MSB_124X_LOCK_STATUS *)pvParam3) = E_MSB_124X_DEMOD_UNLOCK;
        }
    }
    return MAPI_TRUE;
}


MAPI_BOOL Demod_MSB124X_Connect(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    DBG_DEMOD_MSB(printf("Connect type=%d\n",(int)enDemodType));

    m_enPreDemodulator_Type = m_enCurrentDemodulator_Type;
    m_enCurrentDemodulator_Type = enDemodType;


    if (u8DeviceBusy == 1)
    {
        return MAPI_FALSE;
    }

    // Leave sleep mode if t2 demod is in sleep.
    if (g_u8_msb1240_sleep_mode_status != 0)
    {
        (printf("T2 demod leave sleep mode \n"));
        MSB124X_ExtendCmd(0x85, 0, 0, NULL);
    }
    u8DeviceBusy = 1;
    return MAPI_TRUE;
}
/*@ <Operation ID=I2b28dd03m121c8cf959bmm7207> @*/
MAPI_BOOL Disconnect(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    DBG_DEMOD_MSB(printf("device_demodulator_msb1240: Disconnect\n"));
#if 0
    // Enter sleep mode
    if (g_u8_msb1240_sleep_mode_status == 0)
    {
        (printf("T2 demod enter sleep mode\n"));
        MSB124X_ExtendCmd(0x85, 1, 0, NULL);
    }
#endif
    u8DeviceBusy = 0;

    return MAPI_TRUE;
}

#include "drvXC_IOPort.h"
#include "apiXC.h"

void Reset(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8     u8Data = 0x00;
    MAPI_U32    u32Retry = 0x00;

    DBG_DEMOD_MSB(printf(">>>MSB1240: Reset()\n"));
    u32StartTime = MsOS_GetSystemTime();
    DBG_DEMOD_MSB(printf("\t\t\tRESET TIME   %ld\n", u32StartTime));//to measure time
    bDoReset = TRUE;

    // mask miu access for all and mcu
    WriteReg(0x1200+(0x23)*2 + 1,0x0f);
    WriteReg(0x1200+(0x23)*2,0xf0);
    // 10us delay
    usleep(10);

    WriteReg(0x0B00 + (0x19) * 2, 0x03);
    WriteReg(0x0B00 + (0x10) * 2, 0x01);
    WriteReg(REG_MB_CNTL, 0x00);             //clear MB_CNTL
    usleep(5 * 100);

    // enable miu access of mcu gdma
    WriteReg(0x1200+(0x23)*2 + 1,0x00);
    WriteReg(0x1200+(0x23)*2,0x00);
    // 10us delay
    usleep(10);

    WriteReg(0x0B00 + (0x10) * 2, 0x00);
    WriteReg(0x0B00 + (0x19) * 2, 0x00);
    usleep(5 * 1000);
    ReadReg(REG_MB_CNTL, &u8Data);           //check MB_CNTL ready
    while(u8Data != 0xff)
    {
        usleep(50*1000);
        ReadReg(REG_MB_CNTL, &u8Data);       //check MB_CNTL ready
        if (u32Retry++ > 200)
        {
            ERR_DEMOD_MSB(printf(">>>MSB1240: Reset Fail!\n"));
            break;
        }
    }
    //printf(">>>MSB1240: Reset ok!\n");
    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();
    p1_ever_lock_flag = 0;

}
MAPI_BOOL Power_On_Initialization(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
#if(TIMING_VERIFICATION == 1)
    tmm_1 = GIVE_ME_TIME
#endif

#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2 == 0)
    return MAPI_TRUE;
#endif
#endif
    MAPI_U8     status = TRUE;
    MAPI_BOOL    bMatch = false;
    MAPI_U8     u8RetryCnt = 3;
    DBG_DEMOD_MSB(printf(">>>MSB1240: m_enPreDemodulator_Type=%d,m_enCurrentDemodulator_Type=%d.....\n",m_enPreDemodulator_Type,m_enCurrentDemodulator_Type));

    MSB124X_ExtendCmd(0x80,MAPI_TRUE,0,NULL);// enable extend demod IF-AGC
    MSB124X_ExtendCmd(0x81,MAPI_FALSE,0,NULL);// enable extend demod TS PAD

    DBG_DEMOD_MSB(printf(">>>MSB1240: Enter Power_On_Initialization() 000.....\n"));

    DBG_DEMOD_FLOW( printf("m_enPreDemodulator_Type=%u , Cur=%u\n", m_enPreDemodulator_Type, m_enCurrentDemodulator_Type ); );
    if (bPower_init_en == TRUE)
    {
        if((m_enPreDemodulator_Type!= E_DEVICE_DEMOD_DVB_T) &&(m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T))
        {
            DBG_DEMOD_MSB(printf(">>>MSB1240: Enter Power_On_Initialization() DVBT.....\n"));
            SetCurrentDemodulatorType(E_DEVICE_DEMOD_DVB_T);
        }

        if((m_enPreDemodulator_Type!=E_DEVICE_DEMOD_DVB_T2) &&(m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T2))
        {
            DBG_DEMOD_MSB(printf(">>>MSB1240: Enter Power_On_Initialization() DVBT2.....\n"));
            SetCurrentDemodulatorType(E_DEVICE_DEMOD_DVB_T2);
        }

        if((m_enPreDemodulator_Type!=E_DEVICE_DEMOD_DVB_C) &&(m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_C))
        {
            DBG_DEMOD_MSB(printf(">>>MSB1240: Enter Power_On_Initialization() DVBC.....\n"));
            SetCurrentDemodulatorType(E_DEVICE_DEMOD_DVB_C);
        }

        if((m_enPreDemodulator_Type!=E_DEVICE_DEMOD_DVB_S) &&(m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_S))
        {
            DBG_DEMOD_MSB(printf(">>>MSB1240: Enter Power_On_Initialization() DVBS.....\n"));
            SetCurrentDemodulatorType(E_DEVICE_DEMOD_DVB_S);
        }

        return    MAPI_TRUE;
    }

    DBG_DEMOD_MSB(printf(">>>MSB1240: Enter Power_On_Initialization() 111.....\n"));

    if(g_WO_SPI_FLASH == 1)
    {
    #if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    #if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2 == 1)
        status &= I2C_CH_Reset(3);
        if (bSTR_mode_en == MAPI_TRUE)
        {
            status &= MSB1240_HW_init();
            status &= LoadDspCodeToSDRAM(MSB1240_DVBT2);
        }
        status &= LoadDspCodeToSDRAM(MSB1240_BOOT);
        status &= LoadDspCodeToSDRAM(MSB1240_DVBT2);
        if(status == MAPI_FALSE)
        {
            ERR_DEMOD_MSB(printf("[msb1240][err] LoadDspCodeToSDRAM failure...\n"));
        }

        if (LoadDSPCode() == MAPI_FALSE)
        {
            ERR_DEMOD_MSB(printf(">>>>MSB1240:Fail\n"));
            status= MAPI_FALSE;
        }
    #endif
    #else
        mapi_gpio *gptr = mapi_gpio_GetGPIO_Dev();
        if(gptr != NULL)
        {
            gptr->SetOff();
        }

        usleep(resetDemodTime*1000);

        if(gptr != NULL)
        {
            gptr->SetOn();
        }

        status &= I2C_CH_Reset(3);
    #if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C_ONLY_LOAD_T2 == 0)
        status &= DTV_DVB_HW_init();
    #endif
        if(status == MAPI_FALSE)
        {
            ERR_DEMOD_MSB(printf("[msb1240][err] MSB1240_HW_init failure...\n"));
        }

        status &= LoadDspCodeToSDRAM(MSB1240_ALL);
        if(status == MAPI_FALSE)
        {
            ERR_DEMOD_MSB(printf("[msb1240][err] LoadDspCodeToSDRAM failure...\n"));
        }

        if (LoadDSPCode() == MAPI_FALSE)
        {
        ERR_DEMOD_MSB(printf(">>>>MSB1240:Fail\n"));
        status= MAPI_FALSE;
        }
    #endif
    }
    else
    {
        MAPI_U8     u8DoneFlag = 0;
        MAPI_U16    u16_counter = 0;

        MAPI_U16    crc16 = 0;
        MAPI_U8     _u8_reg = 0,u8_reg = 0;

        do
        {
            DBG_DEMOD_MSB(printf(">>>MSB1240: u8RetryCnt = %d\n",u8RetryCnt));

            MAPI_U8 flash_waiting_ready_timeout = 0;
            u8RetryCnt--;

            status = msb1240_flash_mode_en();
            if (status == FALSE)
            {
                           bPower_init_en = MAPI_FALSE;
                ERR_DEMOD_MSB(printf("[msb1240][error]msb1240_flash_mode_en fail....\n");)
                return MAPI_FALSE;
            }

        #if(TIMING_VERIFICATION)
            tmm_3 = GIVE_ME_TIME
        #endif
            status = msb1240_flash_boot_ready_waiting(&flash_waiting_ready_timeout);
            if ( (flash_waiting_ready_timeout == 1) || (status == FALSE) )
            {
                ERR_DEMOD_MSB(printf("[msb1240][error]msb1240_flash_boot_ready_waiting fail....\n");)
            }

            ReadReg(0x1200+(0x01)*2,&u8_reg);
            if (u8_reg & BIT1){
                printf(">>>MSB1240: leave DRAM SR mode\n");
                // Turn on MPLL
                ReadReg(0x0A00+(0x35)*2,&u8_reg);
                u8_reg &= (0xff-0x80);
                WriteReg(0x0A00+(0x35)*2,u8_reg);

                // SR begin
                WriteReg2bytes(0x1200+(0x1c)*2, 0x00b2);
                WriteReg2bytes(0x1200+(0x01)*2, 0x0101);

                usleep(1*1000);

                WriteReg2bytes(0x1200+(0x23)*2, 0xfffe);

                usleep(1*1000);

                WriteReg2bytes(0x1200+(0x00)*2, 0x0501);

                usleep(1*1000);

                WriteReg2bytes(0x1200+(0x00)*2, 0x0301);

                usleep(1*1000);

                WriteReg2bytes(0x1200+(0x00)*2, 0x0501);

                usleep(1*1000);

                WriteReg2bytes(0x1200+(0x00)*2, 0x0001);

                usleep(1*1000);

                WriteReg2bytes(0x1200+(0x1c)*2, 0x00b0);

                usleep(1*1000);

                WriteReg2bytes(0x1200+(0x01)*2, 0x010d);

                usleep(1*1000);

                // WriteReg2bytes(0x1200+(0x23)*2, 0x0000);

                // usleep(1*1000);
                //SR End

                // waiting for SR completed...
                usleep(10*1000);

                // ADC turn on.
                ReadReg(0x0A00+(0x0C)*2,&u8_reg);
                u8_reg &= (0xff-0x03);
                WriteReg(0x0A00+(0x0C)*2,u8_reg);

                // ReadReg(0x0900+(0x0B)*2,&u8Data);
                // u8Data &= (0xff-0x20);
                WriteReg(0x0900+(0x0B)*2, 0x00);

                // enable miu access of mcu gdma
                WriteReg(0x1200+(0x23)*2,0xf0);
                // 10us delay
                usleep(10);

                WriteReg(0x0B00 + (0x19) * 2, 0x00);
                WriteReg(0x0B00 + (0x10) * 2, 0x00);
            }
            ReadReg(0x0900+(0x02<<1),&_u8_reg);
            if(_u8_reg & BIT5)
            {
                crc16 = MSB1240_LIB[u32SizeOfMSB1240_LIB-2];
                crc16 = (crc16<<8)|MSB1240_LIB[u32SizeOfMSB1240_LIB-1];
            }
            else
            {
                crc16 = MSB1240_LIB[u32SizeOfMSB1240_LIB-4];
                crc16 = (crc16<<8)|MSB1240_LIB[u32SizeOfMSB1240_LIB-3];
            }

        #if(TIMING_VERIFICATION)
            tmm_4 = GIVE_ME_TIME
            printf("[tmm1]t4-t3 = %ld (%ld - %ld)\n",tmm_4-tmm_3,tmm_4,tmm_3);
        #endif

            if(status == FALSE)
            {
            #ifndef T3_Winbledon
                DBG_DEMOD_MSB(printf(">>>MSB1240: Reset Demodulator\n"));

                mapi_gpio *gptr = mapi_gpio_GetGPIO_Dev();
                if(gptr != NULL)
                {
                    gptr->SetOff();
                }

                usleep(resetDemodTime*1000);

                if(gptr != NULL)
                {
                    gptr->SetOn();
                }

                status = msb1240_flash_mode_en();
                if (status == FALSE) ERR_DEMOD_MSB(printf("[msb1240][error]msb1240_flash_mode_en fail....\n");)

                status = msb1240_flash_boot_ready_waiting(&flash_waiting_ready_timeout);
                if ( (flash_waiting_ready_timeout == 1) || (status == FALSE) ) ERR_DEMOD_MSB(printf("[msb1240][error]msb1240_flash_boot_ready_waiting fail....\n");)

                // usleep(waitFlashTime * 1000);
                if (I2C_CH_Reset(3) == MAPI_FALSE)
                {
                  DBG_DEMOD_MSB(printf(">>>MSB1240 CH Reset:Fail\n"));
                  status= MAPI_FALSE;
                  continue;
                }

                u16_counter = 1000;
                do
                {
                  // 10 ms
                  usleep(10*1000);
                  u16_counter--;
                  ReadReg(0x0900+(0x4f)*2, &u8DoneFlag);
                } while(u8DoneFlag != 0x99 && u16_counter != 0);

                if(u16_counter == 0 && u8DoneFlag != 0x99)
                {
                  DBG_DEMOD_MSB(printf("[wb]Err, MSB1240 didn't ready yet\n"));
                  status = false;
                }
                else
                  status = TRUE;
            #endif
            }
            // No need to switch to CH0 before SPI Flash access.
            status &= ReadReg(0x0900+0x01*2, &u8MSB1240ChipRev);
            if (u8MSB1240ChipRev == 0)
            {
                MSB1240_LIB = MSB1240_LIB_U01;
                u32SizeOfMSB1240_LIB = sizeof(MSB1240_LIB_U01);
            }
            {
                DBG_DEMOD_MSB(printf(">>>MSB1240: Check Version..."));
                // turn on spi function to read flash info.
                // mask miu access for all and mcu
                WriteReg(0x1200+(0x23)*2 + 1,0x0f);
                WriteReg(0x1200+(0x23)*2,0xf0);
                // 10us delay
                usleep(10);

                // MCU Reset
                ReadReg(0x0b00+(0x19<<1),&_u8_reg);
                _u8_reg |= 0x01;
                WriteReg(0x0b00+(0x19<<1),_u8_reg);

                ReadReg(0x0900+(0x07<<1),&_u8_reg);
                _u8_reg |= 0x10;
                WriteReg(0x0900+(0x07<<1),_u8_reg);

                ReadReg(0x0900+(0x3b<<1),&_u8_reg);
                _u8_reg |= 0x01;
                WriteReg(0x0900+(0x3b<<1),_u8_reg);

                if (IspCheckVer(MSB1240_LIB, &bMatch) == MAPI_FALSE)
                {
                    ERR_DEMOD_MSB(printf(">>> ISP read FAIL!\n"));
                    status= MAPI_FALSE;
                    continue;
                }

                if(bMatch == false)
                {
                  printf(">>> IspCheckVer FAIL!\n");
                }
                else
                {

                  if (I2C_CH_Reset(3) == MAPI_FALSE)
                  {
                    (printf(">>>MSB1240 CH Reset:Fail\n"));
                    status= MAPI_FALSE;
                    continue;
                  }
                  else
                  {
                    (printf(">>>MSB1240 CH Reset:OK\n"));
                  }

                  if (dram_crc_check(crc16, &bMatch) == MAPI_FALSE)
                  {
                      (printf(">>> reg read fail!\n"));
                      status= MAPI_FALSE;
                      continue;
                  }

                  if(bMatch == false)
                    printf(">>> dram crc check FAIL!\n");
                  else
                    printf(">>> dram crc check OK!\n");

                  if (bMatch == true)
                  {
                      // mask miu access for all and mcu
                      WriteReg(0x1200+(0x23)*2 + 1,0x0f);
                      WriteReg(0x1200+(0x23)*2,0xf0);
                      // 10us delay
                      usleep(10);
                      WriteReg(0x0B00 + (0x19) * 2, 0x03);
                  }
                }


            #if (FLASH_WP_ENABLE == 1)
                if (bMatch == false)
                {
                  // disable flash WP, pull high.
                  if(msb1240_flash_WP(0) == false)
                  {
                    DBG_FLASH_WP(printf("[wb]Err, FLASH WP Disable Fail!!!\n");)
                  }
                  usleep(100*1000);
                }
            #endif
                ////bMatch = true; //FIXME : Remove this to enable auto FW reload.
                if (bMatch == false)// Version not match
                {
                    MAPI_U8     bAddr[1];
                    MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
                    MAPI_U32 u32SizeOfLimit=0;

                    printf(">>> Not match! Reload Flash...");
                    if ( (u32SizeOfMSB1240_LIB%256) != 0)
                    {
                        printf(" MSB1240_LIB 256byte alignment error!%lu \n",u32SizeOfMSB1240_LIB);
                    }

                    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_SPI_IIC);
                    iptr->WriteBytes(0, NULL, 5, bWriteData);

                    bAddr[0] = 0x10;
                    bWriteData[0] = 0x06;
                    iptr->WriteBytes(1, bAddr, 1, bWriteData);

                    bWriteData[0] = 0x12;
                    iptr->WriteBytes(0, NULL, 1, bWriteData);

                    bAddr[0] = 0x10;

                    bWriteData[0] = 0xC7;
                    iptr->WriteBytes(1, bAddr, 1, bWriteData);

                    bWriteData[0] = 0x12;
                    iptr->WriteBytes(0, NULL, 1, bWriteData);

                    bWriteData[0]=0x24 ;
                    iptr->WriteBytes(0, NULL, 1, bWriteData);
                    DBG_DEMOD_MSB(printf("\t\t\tStart    %ld\n", MsOS_GetSystemTime()));//to measure time
                    if ( (u32SizeOfMSB1240_LIB - 4) > MAX_MSB1240_LIB_LEN)
                    {
                        printf("Err, msb1240_lib size(%ld) is larger than flash size(%d)\n",u32SizeOfMSB1240_LIB,MAX_MSB1240_LIB_LEN);
                    }

                    // if (IspProcFlash(MSB1240_LIB, u32SizeOfMSB1240_LIB) == MAPI_FALSE)
                    //if (IspProcFlash(MSB1240_LIB, u32SizeOfMSB1240_LIB-2) == MAPI_FALSE)
                    ReadReg(0x0900+(0x02<<1),&_u8_reg);
                    if(_u8_reg & BIT5)
                    {
                        u32SizeOfLimit = u32SizeOfMSB1240_LIB-4;
                    }
                    else
                    {
                        u32SizeOfLimit = u32SizeOfMSB1240_LIB-4-0x9000;
                    }
                    if (IspProcFlash(MSB1240_LIB, u32SizeOfLimit) == MAPI_FALSE)
                    {
                        ERR_DEMOD_MSB(printf(" ISP write FAIL\n"));
                        status= MAPI_FALSE;
                        continue;
                    }
                    else
                    {
                        DBG_DEMOD_MSB(printf("\t\t\tEnd   %ld\n", MsOS_GetSystemTime()));//to measure time
                        //check again
                        if ((IspCheckVer(MSB1240_LIB, &bMatch) == MAPI_FALSE)||(bMatch==false))
                        {
                            ERR_DEMOD_MSB(printf(">>> ISP read FAIL! bMatch %d \n",bMatch));
                            status= MAPI_FALSE;
                            continue;
                        }
                        else // reset again
                        {
                        #ifndef T3_Winbledon
                            DBG_DEMOD_MSB(printf(">>>MSB1240: Reset Demodulator\n"));

                            printf(">>>MSB1240[2]: Reset Demodulator\n");
                            mapi_gpio *gptr = mapi_gpio_GetGPIO_Dev();

                            if(gptr != NULL)
                            {
                                gptr->SetOff();
                            }

                            usleep(resetDemodTime*1000);

                            if(gptr != NULL)
                            {
                                gptr->SetOn();
                            }

                            status = msb1240_flash_mode_en();
                            if (status == FALSE) ERR_DEMOD_MSB(printf("[msb1240][error]msb1240_flash_mode_en fail....\n");)

                            status = msb1240_flash_boot_ready_waiting(&flash_waiting_ready_timeout);
                            if ( (flash_waiting_ready_timeout == 1) || (status == FALSE) ) ERR_DEMOD_MSB(printf("[msb1240][error]msb1240_flash_boot_ready_waiting fail....\n");)

                            // usleep(waitFlashTime * 1000);

                            if (I2C_CH_Reset(3) == MAPI_FALSE)
                            {
                              ERR_DEMOD_MSB(printf(">>>MSB1240 CH Reset:Fail\n"));
                              status= MAPI_FALSE;
                              continue;
                            }

                            u16_counter = 1000;
                            do
                            {
                              // 10 ms
                              usleep(10*1000);
                              u16_counter--;
                              ReadReg(0x0900+(0x4f)*2, &u8DoneFlag);
                            } while(u8DoneFlag != 0x99 && u16_counter != 0);

                            if(u16_counter == 0 && u8DoneFlag != 0x99)
                            {
                              ERR_DEMOD_MSB(printf("[wb]Err, MSB1240 didn't ready yet\n"));
                              status = false;
                            }
                            else
                              status = TRUE;
                        #endif

                            if (I2C_CH_Reset(3) == MAPI_FALSE)
                            {
                              (printf(">>>MSB1240 CH Reset:Fail\n"));
                              status= MAPI_FALSE;
                              continue;
                            }
                            else
                            {
                              (printf(">>>MSB1240 CH Reset:OK\n"));
                            }

                            if (dram_crc_check(crc16, &bMatch) == MAPI_FALSE)
                            {
                              (printf(">>> reg read fail!\n"));
                              status= MAPI_FALSE;
                              continue;
                            }

                            if(bMatch == false)
                              printf(">>> dram crc check FAIL!\n");
                            else
                              printf(">>> dram crc check OK!\n");

                            if (bMatch == true)
                            {
                                // mask miu access for all and mcu
                                WriteReg(0x1200+(0x23)*2 + 1,0x0f);
                                WriteReg(0x1200+(0x23)*2,0xf0);
                                // 10us delay
                                usleep(10);
                                WriteReg(0x0B00 + (0x19) * 2, 0x03);
                            }
                        }
                        DBG_DEMOD_MSB(printf(" OK\n"));
                    }
                }
                else
                {
                    // Version match, do nothing
                    DBG_DEMOD_MSB(printf(">>> Match\n"));
                }

            #if (FLASH_WP_ENABLE == 1)
                if (bMatch == true)
                {
                  // Enable flash WP, pull high.
                  if(msb1240_flash_WP(1) == false)
                  {
                    DBG_FLASH_WP(printf("[wb]Err, FLASH WP Enable Fail!!!\n");)
                  }
                  usleep(100*1000);
                }
            #endif
            }


            if (I2C_CH_Reset(3) == MAPI_FALSE)
            {
                ERR_DEMOD_MSB(printf(">>>MSB1240 CH Reset:Fail\n"));
                status= MAPI_FALSE;
                continue;
            }
            else
            {
                DBG_DEMOD_MSB(printf(">>>MSB1240 CH Reset:OK\n"));
            }
        #if(MSB1240_SELECT_IF_INPUT)
            //[0:0] reg_ana_setting_enable
            //[6:4] reg_ana_setting_sel
            status &= WriteReg2bytes(0x0A00+(0x51)*2, 0x0021);
        #endif
        #if(TIMING_VERIFICATION)
            tmm_5 = GIVE_ME_TIME
        #endif
            if (LoadDSPCode() == MAPI_FALSE)
            {
                ERR_DEMOD_MSB(printf(">>>>MSB1240:Fail\n"));
                status= MAPI_FALSE;
                continue;
            }
            else
            {
                // turn off spi function to keep impedance
                ReadReg(0x0900+(0x07<<1),&u8_reg);
                u8_reg &= (0xff-0x10);
                WriteReg(0x0900+(0x07<<1),u8_reg);

                ReadReg(0x0900+(0x3b<<1),&u8_reg);
                u8_reg &= (0xff-0x01);
                WriteReg(0x0900+(0x3b<<1),u8_reg);

                DBG_DEMOD_MSB(printf(">>>MSB1240:OK\n"));
            }
        #if(TIMING_VERIFICATION)
            tmm_6 = GIVE_ME_TIME
            printf("[tmm1]t6-t5 = %ld (%ld - %ld)\n",tmm_6-tmm_5,tmm_6,tmm_5);
        #endif

            ReadReg(0x0900+(0x01)*2, &gu8ChipRevId);
            DBG_DEMOD_MSB(printf(">>>MSB1240:Edinburgh RevID:%x\n", gu8ChipRevId));

            ReadReg(0x0900+(0x49)*2, &gu8ChipRevId);
            DBG_DEMOD_MSB(printf(">>>MSB1240:Edinburgh 0x49_L:%x\n", gu8ChipRevId));

            ReadReg(0x0900+(0x49)*2+1, &gu8ChipRevId);
            DBG_DEMOD_MSB(printf(">>>MSB1240:Edinburgh 0x49_H:%x\n", gu8ChipRevId));

            ReadReg(0x0900+(0x4A)*2, &gu8ChipRevId);
            DBG_DEMOD_MSB(printf(">>>MSB1240:Edinburgh 0x4A_L:%x\n", gu8ChipRevId));

        }while((u8RetryCnt>0)&&(status==FALSE));
    }

    if(status==FALSE)
    {
        ERR_DEMOD_MSB(printf("msb1240 power_on_init FAIL !!!!!! \n\n"));
    }
    else
    {
        g_u8_msb1240_sleep_mode_status = 0;
        bPower_init_en = MAPI_TRUE;
        printf("msb1240 power_on_init OK !!!!!! \n\n");
    #if(TIMING_VERIFICATION == 1)
        tmm_2 = GIVE_ME_TIME
        printf("[tmm]t2-t1 = %ld (%ld - %ld)\n",tmm_2-tmm_1,tmm_2,tmm_1);
    #endif
    }
    return status;
}

/*@ </Operation ID=Im17018142m1221763cc7cmm46c6> @*/
//m
MAPI_BOOL Set_PowerOn(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    return TRUE;
}
//m
MAPI_BOOL Set_PowerOff(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    return TRUE;
}

MAPI_U8  DTV_DVBT_DSPReg_CRC(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_U8 crc = 0;
    MAPI_U8 idx = 0;

    for (idx = 0; idx<(sizeof(MSB1240_DVBT_DSPREG_TABLE)); idx++)
    {
        crc ^= MSB1240_DVBT_DSPREG_TABLE[idx];
    }

    crc = ~crc;

    return crc;
}

void  DTV_DVBT_DSPReg_ReadBack(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));

    MAPI_U8 ret = 0;
    MAPI_U8 idx = 0;

    for (idx = T_OPMODE_RFAGC_EN; idx<(sizeof(MSB1240_DVBT_DSPREG_TABLE)); idx++)
    {
        ReadDspReg(idx,&ret);
        printf("@msb1240, idx=0x%x, dsp=0x%x, sw=0x%x\n",idx,ret,MSB1240_DVBT_DSPREG_TABLE[idx-(MAPI_U8)T_OPMODE_RFAGC_EN]);
    }

    return;
}

MAPI_BOOL Active(MAPI_BOOL bEnable)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL status = MAPI_TRUE;

    status = WriteReg(REG_FSM_EN, (U8)(bEnable)); // FSM_EN

    if(status)
    {
        printf(" @MSB1240_Active OK\n");
    }
    else
    {
        printf(" @MSB1240_Active NG\n");
    }
    return status;
}

EN_DEVICE_DEMOD_TYPE GetCurrentDemodulatorType(void)
{
    return m_enCurrentDemodulator_Type;
}

//########################################  Public:DTV Implementation ######################################
// DVBT2 95~101ms, DVBT 38~39ms
MAPI_BOOL DTV_SetFrequency(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth, MAPI_BOOL bPalBG, MAPI_BOOL bLPsel)
{
    MS_U32 u32DMD_IfFreq = 5000;
    MS_U8  u8_if_agc_mode = 0;

    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    UNUSED(bPalBG);
    UNUSED(bLPsel);
    g_u32Frequency=u32Frequency;
    DBG_DEMOD_MSB(printf("DTV_SetFrequency %d ,%d \n", (int)u32Frequency, (int)eBandWidth));

    if (g_u8_msb1240_sleep_mode_status != 0)
    {
        DBG_DEMOD_MSB(printf("%s, %s, %d, MSB1240 is sleeping, wake him up first\n",__FILE__,__FUNCTION__,__LINE__));
        return FALSE;
    }

    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();

#if(TIMING_VERIFICATION == 1)
    tmm_11 = GIVE_ME_TIME
#endif

    if(m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T2)
    {
        MAPI_U8 bw = E_DEMOD_BW_8M;
        switch (eBandWidth)
        {
            case E_RF_CH_BAND_6MHz:
                bw = E_DEMOD_BW_6M;
                break;
            case E_RF_CH_BAND_7MHz:
                bw = E_DEMOD_BW_7M;
                break;
            case E_RF_CH_BAND_8MHz:
                bw = E_DEMOD_BW_8M;
                break;
            default:
                bw = E_DEMOD_BW_8M;
                break;
        }
        Reset();
        usleep(500);
        WriteDspReg((MAPI_U16)E_T2_BW, bw);      // BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M

        WriteDspReg((MAPI_U16)E_T2_PLP_ID, g_msb1240_plp_id);
        WriteDspReg((MAPI_U16)E_T2_FC_L, (MS_U8)u32DMD_IfFreq);
        WriteDspReg((MAPI_U16)E_T2_FC_H, (MS_U8)(u32DMD_IfFreq>>8));
        WriteDspReg((MAPI_U16)E_T2_IF_AGC_INV_PWM_EN, u8_if_agc_mode);

        WriteReg(REG_FSM_EN, 0x01); // FSM_EN
        g_u8_bw = bw;
        DBG_DEMOD_MSB(printf("\n[msb1240][dvbt2]DTV_SetFrequency, plp=0x%x,bw=%d, if_KHz=%ld, if_agc_mode=%d\n",g_msb1240_plp_id,bw,u32DMD_IfFreq,u8_if_agc_mode);)
    }
    else if (m_enCurrentDemodulator_Type==E_DEVICE_DEMOD_DVB_T)
    {
        Reset();
        usleep(500);
        WriteDspReg((MAPI_U16)T_CONFIG_BW, eBandWidth);      // BW: 1->6M, 2->7M, 3->8M
        WriteDspReg((MAPI_U16)T_CONFIG_FC_L, (MS_U8)u32DMD_IfFreq);
        WriteDspReg((MAPI_U16)T_CONFIG_FC_H, (MS_U8)(u32DMD_IfFreq>>8));
        WriteDspReg((MAPI_U16)T_CONFIG_IF_INV_PWM_OUT_EN, u8_if_agc_mode);
        // MSB1240_DVBT_DSPREG_TABLE[(MAPI_U16)T_CONFIG_BW-(MAPI_U16)T_OPMODE_RFAGC_EN] = (MAPI_U8)eBandWidth;
        // MSB1240_DVBT_DSPREG_TABLE[(MAPI_U16)T_PARAM_CHECK_SUM-(MAPI_U16)T_OPMODE_RFAGC_EN] = DTV_DVBT_DSPReg_CRC();
        // WriteDspReg((MAPI_U8)T_PARAM_CHECK_SUM, MSB1240_DVBT_DSPREG_TABLE[(MAPI_U8)T_PARAM_CHECK_SUM-(MAPI_U8)T_OPMODE_RFAGC_EN]);      // BW: 1->6M, 2->7M, 3->8M

        // Hierarchy mode
        WriteDspReg((MAPI_U8)T_CONFIG_LP_SEL, bLPsel? 0x01:0x00);
        WriteReg(REG_FSM_EN, 0x01); // FSM_EN//Active(1);
        DBG_DEMOD_MSB(printf("\n[msb1240][dvbt]DTV_SetFrequency, if_KHz=%ld, if_agc_mode=%d\n",u32DMD_IfFreq,u8_if_agc_mode);)
        DBG_DEMOD_MSB(printf(" [dvbt] Set frequency BW = %d, FC_L = %d, FC_H = %d\n",eBandWidth,u32DMD_IfFreq,(u32DMD_IfFreq>>8)));
    }
#if(TIMING_VERIFICATION == 1)
    tmm_12 = GIVE_ME_TIME
    show_timer();
#endif

    return MAPI_TRUE;
}

#if (ENABLE_DEMOD_DVBS)
MAPI_BOOL DTV_DVB_S_SetFrequency(MS_U16 u16CenterFreq, MS_U32 u32SymbolRate_Hz)
{
     MS_BOOL bRet=TRUE;
     MS_U16 u16LockCount;


    //PRINT_CURRENT_LINE();
    DBG_DVBS( printf("DTV_DVB_S_SetFrequency(u16CenterFreq=%u, u32SymbolRate_Hz=%u)\n", u16CenterFreq, u32SymbolRate_Hz); );

#if (FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2012 || FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2011 || FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2017)
    //bRet&=MDrv_Tuner_SetFreq(u16CenterFreq, u32SymbolRate_Hz);
    bRet &= MDrv_DVBS_Tuner_SetFreq(u16CenterFreq, u32SymbolRate_Hz);

#elif (FRONTEND_TUNER_S2_TYPE==SHARP_BS2S7VZ7801_TUNER)
    bRet&=MDrv_Tuner_SetFreq(u16CenterFreq, u32SymbolRate_Hz/1000);
#endif

    if (bRet==FALSE)
        return bRet;

    u16LockCount=0;
    do
    {
        bRet=TRUE;
        extern MS_BOOL MDrv_Tuner_CheckLock(void);
        bRet&=MDrv_Tuner_CheckLock();
        MsOS_DelayTask(1);
        u16LockCount++;
    }while((bRet==FALSE) && (u16LockCount<MSB124X_TUNER_WAIT_TIMEOUT)) ;

    if (bRet==TRUE)
    {
        PRINTE(("####>> Tuner PLL Lock\n"));
    }
    else
    {
        PRINTE((" --->> Tuner PLL Unlock\n"));
    }
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_Restart(CofdmDMD_Param* pParam)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16  u16Address =0;
    MAPI_U8   u8Data =0;
    MAPI_U16  u16SymbolRate =0;
    MAPI_U16  __attribute__ ((unused)) u16CenterFreq =0;
    //MAPI_U16 u16LockCount;
    MAPI_U8   u8counter = 0;

    u16SymbolRate=(pParam->u32SymbolRate/1000);
    u16CenterFreq=pParam->u32TunerFreq;
    PRINTE(("--->>> MSB124X MDrv_CofdmDmd_Restart+ Fc:%d SymbolRate %d\n", u16CenterFreq, u16SymbolRate));
    IIC_Bypass_Mode(TRUE);
    bRet&=DTV_DVB_S_SetFrequency(pParam->u32TunerFreq,(pParam->u32SymbolRate/1000));
    IIC_Bypass_Mode(FALSE);
    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    bRet&=WriteReg(u16Address,u8Data);
    MsOS_DelayTask(50);
    u16Address=0x0B52;
    u8Data=(u16SymbolRate&0xFF);
    bRet&=WriteReg(u16Address,u8Data);
    u16Address=0x0B53;
    u8Data=((u16SymbolRate>>8)&0xFF);
    bRet&=WriteReg(u16Address,u8Data);

    //ADCPLL IQ swap
    if(MSB1240_DVBS_ADCPLL_IQ_SWAP==1)
    {
        u16Address=0x0A03;
        bRet&=ReadReg(u16Address, &u8Data);
        u8Data|=(0x10);
        bRet&=WriteReg(u16Address, u8Data);
    }

    //Configure Serial/Parallel mode for TS output
    u16Address=0x2A40;
    bRet&=ReadReg(u16Address, &u8Data);
    DBG_DEMOD_FLOW(printf("setting TS serial/parallel mode as %x\n",S_TS_Output_VAL));
    if(S_TS_Output_VAL) //Serial Mode
      u8Data|=0x01;
    else               //Parallel Mode
      u8Data&=~(0x01);
    bRet&=WriteReg(u16Address,u8Data);
    //Configure TS output data swap mode
    u16Address=0x2A40;
    bRet&=ReadReg(u16Address, &u8Data);
    DBG_DEMOD_FLOW( printf("setting TS data swap mode as %x\n",S_TS_DataSwap_VAL));
    if(S_TS_DataSwap_VAL) //enable
      u8Data|=0x20;
    else               //disable
      u8Data&=~(0x20);
    bRet&=WriteReg(u16Address,u8Data);
    //Configure TS clk inv mode
    u16Address=0x0924;
    bRet&=ReadReg(u16Address, &u8Data);
    DBG_DEMOD_FLOW(printf("setting TS clk inv mode as %x\n",S_TS_clk_inv_VAL));
    if(S_TS_clk_inv_VAL) //enable
      u8Data|=0x20;
    else               //disable
      u8Data&=~(0x20);
    bRet&=WriteReg(u16Address,u8Data);

    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    u8Data|=0x01;
    bRet&=WriteReg(u16Address,u8Data);

    u8counter = 6;
    bRet&=ReadReg(u16Address,&u8Data);
    while( ((u8Data&0x01) == 0x00) && (u8counter != 0) )
    {
        printf("0x0990=0x%x, bRet=%d, u8counter=%d\n",u8Data,bRet,u8counter);
        u8Data|=0x01;
        bRet&=WriteReg(u16Address,u8Data);
        bRet&=ReadReg(u16Address,&u8Data);
        u8counter--;
    }

    if((u8Data&0x01)==0x00)
    {
        bRet = FALSE;
    }

    printf("MSB1240_S MDrv_Demod_Restart-\n");
    return bRet;
}

MAPI_BOOL MSB1240_DVBS_GetLock(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    if ((u8Data&0x02)==0x00)
    {
        u16Address=MSB1240_DIG_DBG_5_ADDR;
        bRet&=ReadReg(u16Address, &u8Data);
        //DBG_DVBS( printf(" [demod_S state: %d] ", u8Data) );

        if ((u8Data>=15) && (u8Data!=0xcd)) //For lock/unlock issue.
        {
            //DBG_DVBS( printf(" [demod_S state: %d] ", u8Data) );
            if (u8Data==15)
            {
                _bDemodType=MAPI_FALSE;   //S
            }
            else
            {
                _bDemodType=MAPI_TRUE;    //S2
            }
            bRet = MAPI_TRUE;
        }
        else
        {
            bRet = MAPI_FALSE;
        }
    #if MSB124X_TS_DATA_SWAP
        if (bRet==FALSE)
        {
            _bTSDataSwap=FALSE;
        }
        else
        {
            if (_bTSDataSwap==FALSE)
            {
                _bTSDataSwap=TRUE;
                u16Address=0x0924;
                bRet&=ReadReg(u16Address, &u8Data);
                u8Data|=0x20;
                bRet&=WriteReg(u16Address, u8Data);
            }
        }
    #endif
    }
    else
    {
        bRet = MAPI_TRUE;
    }
    DTV_ControlTsOutput(1);
    return bRet;
}

MAPI_BOOL MSB1240_DVBS_DiSEqC_SetTone(MAPI_BOOL bTone1)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address;
    MAPI_U8 u8Data;
    //MAPI_U16 u16WaitCount;
    MAPI_U8 u8ReSet22k;

    //DIG_DISEQC_TX1
    u16Address=0x0DC4;
    u8Data=0x01;
    bRet&=WriteReg(u16Address, u8Data);

    //DIG_DISEQC_EN
    u16Address=0x0DC0;
    u8Data=0x4E;
    bRet&=WriteReg(u16Address, u8Data);
    //DIG_DISEQC_FCAR
    u16Address=0x0DCC;
    u8Data=0x80;
    bRet&=WriteReg(u16Address, u8Data);
    //DIG_DISEQC_MOD
    u16Address=0x0DC2;
    bRet&=ReadReg(u16Address, &u8Data);
    u8ReSet22k=u8Data;

    if (bTone1==MAPI_TRUE)
    {
       u8Data=0x19;
       bRet&=WriteReg(u16Address, u8Data);
       _u8ToneBurstFlag=1;
    }
    else
    {
       u8Data=0x11;
       bRet&=WriteReg(u16Address, u8Data);
       _u8ToneBurstFlag=2;
    }
    //DIG_DISEQC_TX_EN
    u16Address=0x0DCD;
    u8Data=u8Data&~(0x01);
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data=u8Data|0x3E;
    bRet&=WriteReg(u16Address, u8Data);
    MsOS_DelayTask(10);
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data=u8Data&~(0x3E);
    bRet&=WriteReg(u16Address, u8Data);
    MsOS_DelayTask(1);
    u8Data=u8Data|0x01;
    bRet&=WriteReg(u16Address, u8Data);

    MsOS_DelayTask(30);//(100)
    //For ToneBurst 22k issue.
    u16Address=0x0DC2;//For ToneBurst 22k issue.
    u8Data=u8ReSet22k;
    bRet&=WriteReg(u16Address, u8Data);

    return bRet;
}

MAPI_BOOL MSB1240_DVBS_DiSEqC_Set22kOnOff(MAPI_BOOL b22kOn)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8   u8Data =0;

    u16Address=0x0DC2;
    bRet&=ReadReg(u16Address, &u8Data);
    if (b22kOn==MAPI_TRUE)
    {
        u8Data=(u8Data|0x08);
    }
    else
    {
        u8Data=(u8Data&(~0x08));
    }
    bRet&=WriteReg(u16Address, u8Data);
    return bRet;
}

MAPI_BOOL DTV_DVB_S_Set22KOnOff(MAPI_BOOL bOn)
{
    return MSB1240_DVBS_DiSEqC_Set22kOnOff(bOn);
}

MAPI_BOOL MSB1240_DVBS_DiSEqC_Get22kOnOff(MAPI_BOOL* b22kOn)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8   u8Data =0;

    u16Address=0x0DC2;
    bRet&=ReadReg(u16Address, &u8Data);
    if ((u8Data&0x08)==0x08)
    {
        *b22kOn=MAPI_TRUE;
    }
    else
    {
        *b22kOn=MAPI_FALSE;
    }
    return bRet;
}

MAPI_BOOL DTV_DVB_S_Get22KStatus(MAPI_BOOL* bOn)
{
    return MSB1240_DVBS_DiSEqC_Get22kOnOff(bOn);
}

MAPI_BOOL MSB1240_DVBS_DiSEqC_SendCmd(MAPI_U8* pCmd,MAPI_U8 u8CmdSize)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8   u8Data =0;
    MAPI_U8   u8Index =0;
    MAPI_U16 u16WaitCount =0;

    printf(("\r\n MDrv_DiSEqC_SendCmd++++"));

    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data=(u8Data&~(0x10));
    bRet&=WriteReg(u16Address, u8Data);

    //u16Address=0x0BC4;
    for (u8Index=0; u8Index < u8CmdSize; u8Index++)
    {
        u16Address=0x0DC4+u8Index;
        u8Data=*(pCmd+u8Index);
        bRet&=WriteReg(u16Address, u8Data);
    }
    u8Data=((u8CmdSize-1)&0x07)|0x40;
    //Tone and Burst switch,Mantis 0232220
    if(((*pCmd)==0xE0)&&((*(pCmd + 1))==0x10)&&((*(pCmd + 2))==0x38)&&((((*(pCmd + 3))&0x0C)==0x0C)||(((*(pCmd + 3))&0x04)==0x04)))
    {
        u8Data|=0x80;   //u8Data|=0x20;Tone Burst1
    }
    else if(((*pCmd)==0xE0)&&((*(pCmd + 1))==0x10)&&((*(pCmd + 2))==0x38))
    {
        u8Data|=0x20;   //u8Data|=0x80;ToneBurst0
    }

    u16Address=0x0B54;
    bRet&=WriteReg(u16Address, u8Data);
    MsOS_DelayTask(10);
    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data=u8Data|0x10;
    bRet&=WriteReg(u16Address, u8Data);

#if 1       //For Unicable command timing,mick
    u16WaitCount=0;
    do
    {
        u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
        bRet&=ReadReg(u16Address, &u8Data);
         MsOS_DelayTask(1);
         u16WaitCount++;
    }while(((u8Data&0x10)==0x10)&&(u16WaitCount < MSB1240_DEMOD_WAIT_TIMEOUT)) ;

    if (u16WaitCount >= MSB1240_DEMOD_WAIT_TIMEOUT)
    {
        printf(("MSB1240 DVBS DiSEqC Send Command Busy!!!\n"));
        return MAPI_FALSE;
    }
#endif      //For Unicable command timing,mick
    printf(("\r\n MDrv_DiSEqC_SendCmd----"));
    return bRet;
}

MAPI_BOOL DTV_DVB_S_SendDiSEqCCmd(MAPI_U8* pCmd,MAPI_U8 u8CmdSize)
{
    return MSB1240_DVBS_DiSEqC_SendCmd(pCmd, u8CmdSize);
}

MS_BOOL MDrv_CofdmDmd_GetRFOffset(MS_S16 *ps16RFOff)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8 u8Data;
    MS_U32 u32FreqOffset;
    float FreqOffset;

    u32FreqOffset=0;

    u16Address=0x2C39;
    u8Data=0x08;
    bRet&=WriteReg(u16Address, u8Data);
    u16Address=0x3E05;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data|=0x80;
    bRet&=WriteReg(u16Address, u8Data);

    u16Address=0x2C46;
    bRet&=ReadReg(u16Address, &u8Data);
    u32FreqOffset=u8Data;
    u16Address=0x2C45;
    bRet&=ReadReg(u16Address, &u8Data);
    u32FreqOffset=(u32FreqOffset<<8)|u8Data;
    u16Address=0x2C44;
    bRet&=ReadReg(u16Address, &u8Data);
    u32FreqOffset=(u32FreqOffset<<8)|u8Data;

    u16Address=0x3E05;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data&=~(0x80);
    bRet&=WriteReg(u16Address, u8Data);
    FreqOffset=(float)u32FreqOffset;
    PRINTE(("HW_Offset:%ld[MHz]\n", u32FreqOffset));
    if (FreqOffset>=2048)
    {
        FreqOffset=FreqOffset-4096;
    }
    FreqOffset=(FreqOffset/4096)*SAMPLING_RATE;
    *ps16RFOff=FreqOffset/1000;
    PRINTE(("MSB124X FreqOffset:%f[MHz]\n", FreqOffset/1000));
    return bRet;
}

//BLIND SCAN
MS_BOOL MDrv_CofdmDmd_BlindScan_Start(MS_U16 u16StartFreq,MS_U16 u16EndFreq,MS_BOOL bUCMode)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8 u8Data=0;//fix coverity 90926

    UNUSED(bUCMode);
    PRINTE(("MDrv_CofdmDmd_BlindScan_Start+\n"));
    _u16BlindScanStartFreq=u16StartFreq;
    _u16BlindScanEndFreq=u16EndFreq;
    _u16TunerCenterFreq=0;
    _u16ChannelInfoIndex=0;
    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    bRet&=WriteReg(u16Address, u8Data);
    u16Address=MSB1240_TOP_WR_DBG_92_ADDR;
    bRet&=WriteReg2bytes(u16Address, _u16BlindScanStartFreq);
    PRINTE(("MDrv_CofdmDmd_BlindScan_Start- _u16BlindScanStartFreq%d u16StartFreq %d u16EndFreq %d\n", _u16BlindScanStartFreq, u16StartFreq, u16EndFreq));
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_NextFreq(MS_BOOL* bBlindScanEnd,MS_U8* u8Progress)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8   u8Data=0;//fix coverity 90925
    MS_U32  u32TunerCutOffFreq;
    MS_U16 u16WaitCount;
    PRINTE(("MDrv_CofdmDmd_BlindScan_NextFreq+\n"));
    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    if ((u8Data&0x02)==0x02)
    {
        u8Data|=0x08;
        bRet&=WriteReg(u16Address, u8Data);
        u16WaitCount=0;
        do
        {
          u16Address=MSB1240_DIG_DBG_5_ADDR;
            bRet&=ReadReg(u16Address, &u8Data);
            u16WaitCount++;
            PRINTE(("MDrv_CofdmDmd_BlindScan_NextFreq u8Data:0x%x u16WaitCount:%d\n", u8Data, u16WaitCount));
            MsOS_DelayTask(1);
        }while((u8Data!=0x01)&&(u16WaitCount<MSB124X_DEMOD_WAIT_TIMEOUT));
    }
    u16WaitCount=0;

    * bBlindScanEnd=FALSE;
    _u16TunerCenterFreq=0;
    u16Address=MSB1240_TOP_WR_DBG_93_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    _u16TunerCenterFreq=u8Data;
    u16Address=MSB1240_TOP_WR_DBG_92_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    _u16TunerCenterFreq=(_u16TunerCenterFreq<<8)|u8Data;
    if ((sat_info.u16LoLOF == sat_info.u16HiLOF) || (sat_info.u16LoLOF < MAX_C_LOF_FREQ)) // C Band
    {
        if (_enBlindScanStatus == BLINDSCAN_H_LoLOF)
        {
            *u8Progress = (U8)(((_u16TunerCenterFreq - _u16BlindScanStartFreq)*100)/((_u16BlindScanEndFreq-_u16BlindScanStartFreq)*2));
        }
        else
        {
            *u8Progress = (U8)((((_u16TunerCenterFreq - _u16BlindScanStartFreq)*100)/((_u16BlindScanEndFreq-_u16BlindScanStartFreq)*2)) + 50);
        }
    }
    else //KU Band
    {
        switch (_enBlindScanStatus)
        {
            case BLINDSCAN_H_LoLOF:
                *u8Progress = (U8)(((_u16TunerCenterFreq - _u16BlindScanStartFreq)*100)/((_u16BlindScanEndFreq-_u16BlindScanStartFreq)*4));
                break;
            case BLINDSCAN_V_LoLOF:
                *u8Progress = (U8)((((_u16TunerCenterFreq - _u16BlindScanStartFreq)*100)/((_u16BlindScanEndFreq-_u16BlindScanStartFreq)*4)) + 25);
                break;
            case BLINDSCAN_H_HiLOF:
                *u8Progress = (U8)((((_u16TunerCenterFreq - _u16BlindScanStartFreq)*100)/((_u16BlindScanEndFreq-_u16BlindScanStartFreq)*4)) + 50);
                break;
            case BLINDSCAN_V_HiLOF:
                *u8Progress = (U8)((((_u16TunerCenterFreq - _u16BlindScanStartFreq)*100)/((_u16BlindScanEndFreq-_u16BlindScanStartFreq)*4)) + 75);
                break;
            default:
                *u8Progress = 0;
                break;
        }
    }
    if (_u16TunerCenterFreq >= _u16BlindScanEndFreq)
    {
        PRINTE(("MDrv_CofdmDmd_BlindScan_NextFreq . _u16TunerCenterFreq %d _u16BlindScanEndFreq%d\n", _u16TunerCenterFreq, _u16BlindScanEndFreq));
        * bBlindScanEnd=TRUE;
        return bRet;
    }
#if (FRONTEND_TUNER_TYPE == AVAILINK_AV2011)
    u32TunerCutOffFreq=44000;
#else
    u32TunerCutOffFreq=44000; //34000
#endif
    IIC_Bypass_Mode(TRUE);
    bRet&=DTV_DVB_S_SetFrequency(_u16TunerCenterFreq,u32TunerCutOffFreq);
    IIC_Bypass_Mode(FALSE);
    MsOS_DelayTask(10);
    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    if ((u8Data&0x02)==0x00)
    {
        u8Data&=~(0x08);
        bRet&=WriteReg(u16Address, u8Data);
        u8Data|=0x02;
        bRet&=WriteReg(u16Address, u8Data);
        u8Data|=0x01;
        bRet&=WriteReg(u16Address, u8Data);
    }
    else
    {
        u8Data&=~(0x08);
        bRet&=WriteReg(u16Address, u8Data);
    }
    //PRINTE(("MDrv_CofdmDmd_BlindScan_NextFreq _u16TunerCenterFreq:%d-\n", _u16TunerCenterFreq));
    return bRet;
}
MS_BOOL MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(MS_U8* u8Progress,MS_U8 *u8FindNum)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U32    u32Data;
    MS_U16 u16Data;
    MS_U8    u8Data=0;//fix coverity 90928
    MS_U16    u16WaitCount;

    PRINTE(("\r\n 1234567 .... MDrv_Demod_BlindScan_WaitCurFreqFinished+\n"));
    u16WaitCount=0;
    *u8FindNum=0;
    *u8Progress=0;
    do
    {
        u16Address=MSB1240_DIG_DBG_5_ADDR; // "DIG_DBG_5" means state
        bRet&=ReadReg(u16Address, &u8Data);
        u16WaitCount++;
        PRINTE(("MDrv_Demod_BlindScan_WaitCurFreqFinished+1 u8Data:0x%x u16WaitCount:%d\n", u8Data, u16WaitCount));
        MsOS_DelayTask(1);
    }while((u8Data!=17)&&(u16WaitCount<MSB124X_DEMOD_WAIT_TIMEOUT));//#define      DVBS_BLIND_SCAN       17



    if (u16WaitCount>=MSB124X_DEMOD_WAIT_TIMEOUT)
    {
        printf("\r\n ===>>> WaitCurFreqFinished return False!\n ");
        bRet=FALSE;
    }
    else
    {
        u16Address=MSB1240_DIG_DBG_6_ADDR;// "DIG_DBG_6" means sub_state
        bRet&=ReadReg(u16Address, &u8Data);
        if (u8Data==0)
        {
            //Center Freq -- mail box version
            bRet&=ReadReg(REG_TOP_97, &u8Data);
            u32Data=u8Data;
            bRet&=ReadReg(REG_TOP_96, &u8Data);
            u32Data = (u32Data<<8)|u8Data;
            bRet&=ReadReg(REG_TOP_95, &u8Data);
            u32Data = (u32Data<<8)|u8Data;
            _u16ChannelInfoArray[0][_u16ChannelInfoIndex]=((u32Data+500)/1000); //Center Freq
            _u16LockedCenterFreq=((u32Data+500)/1000);

            //symbol rate -- mail box version
            bRet&=ReadReg(REG_DBG_3, &u8Data);
            u16Data = u8Data;
            bRet&=ReadReg(REG_DBG_2, &u8Data);
            u16Data = (u16Data<<8)|u8Data;
            _u16ChannelInfoArray[1][_u16ChannelInfoIndex]=(u16Data);//Symbol Rate
            _u16LockedSymbolRate = u16Data;
            _u16ChannelInfoIndex++;
            *u8FindNum = _u16ChannelInfoIndex;
            //current lock cfo -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE15H,&u8Data);
            u16Data = u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE15L,&u8Data);
            u16Data = (u16Data<<8)|u8Data;
            if(u16Data*1000 >= 0x8000)
            {
                u16Data = 0x10000 - (u16Data*1000);
                _s16CurrentCFO = -1*u16Data/1000;
            }
            else
            {
                _s16CurrentCFO = u16Data;
            }

            //current step size  -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE16H,&u8Data);
            u16Data = u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE16L,&u8Data);
            u16Data = (u16Data<<8)|u8Data;
            _u16CurrentStepSize=u16Data;

            //prelock HB  -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE18H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE18L,&u8Data);
            u16Data = (u16Data<<8)|u8Data;
            _u16PreLockedHB=u16Data;

            //prelock LB  -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE19H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE19L,&u8Data);
            u16Data = (u16Data<<8)|u8Data;
            _u16PreLockedLB=u16Data;

            printf("Current Locked CF:%d BW:%d BWH:%d BWL:%d CFO:%d Step:%d\n", _u16LockedCenterFreq, _u16LockedSymbolRate,_u16PreLockedHB, _u16PreLockedLB, _s16CurrentCFO, _u16CurrentStepSize);


        }
        else if (u8Data==1)
        {
            u16Address=MSB1240_TOP_WR_DBG_93_ADDR;
            bRet&=ReadReg(u16Address, &u8Data);
            u16Data=u8Data;
            u16Address=MSB1240_TOP_WR_DBG_92_ADDR;
            bRet&=ReadReg(u16Address, &u8Data);
            u16Data=(u16Data<<8)|u8Data;
            _u16NextCenterFreq=u16Data;


            //_u16CurrentSymbolRate -- mail box
            bRet&=ReadReg(REG_DBG_2, &u8Data);
            u16Data = u8Data;
            bRet&=ReadReg(REG_DBG_2, &u8Data);
            u16Data = (u16Data<<8)|u8Data;
            _u16CurrentSymbolRate = u16Data;


            // cfo -- mail box
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE15H,&u8Data);
            u16Data = u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE15L,&u8Data);
            u16Data = (u16Data<<8)|u8Data;
            if(u16Data*1000 >= 0x8000)
            {
                u16Data = 0x10000 - (u16Data*1000);
                _s16CurrentCFO = -1*u16Data/1000;
            }
            else
            {
                _s16CurrentCFO = u16Data;
            }

            // current step size -- mail box
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE16H,&u8Data);
            u16Data = u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE16L,&u8Data);
            u16Data = (u16Data<<8)|u8Data;
            _u16CurrentStepSize=u16Data;


            //prelock HB  -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE12H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE12L,&u8Data);
            u16Data = (u16Data<<8)|u8Data;
            _u16PreLockedHB=u16Data;

            //prelock LB  -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE13H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE13L,&u8Data);
            u16Data = (u16Data<<8)|u8Data;
            _u16PreLockedLB=u16Data;

            printf("Pre Locked CF:%d BW:%d HBW:%d LBW:%d Current CF:%d BW:%d CFO:%d Step:%d\n", _u16LockedCenterFreq, _u16LockedSymbolRate,_u16PreLockedHB, _u16PreLockedLB,  _u16NextCenterFreq-_u16CurrentStepSize, _u16CurrentSymbolRate, _s16CurrentCFO, _u16CurrentStepSize);
            //PRINTE(("Pre Locked CF:%d BW:%d HBW:%d LBW:%d Current CF:%d BW:%d CFO:%d Step:%d\n", _u16LockedCenterFreq, _u16LockedSymbolRate,_u16PreLockedHB, _u16PreLockedLB,  _u16NextCenterFreq-_u16CurrentStepSize, _u16CurrentSymbolRate, _s16CurrentCFO, _u16CurrentStepSize));
        }
    }
    *u8Progress=100;
    PRINTE(("MDrv_Demod_BlindScan_WaitCurFreqFinished u8Progress%d u8FindNum %d-\n", *u8Progress, *u8FindNum));
    return bRet;
}


MS_BOOL MDrv_CofdmDmd_BlindScan_Cancel(void)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8   u8Data=0;//fix coverity 90924
    MS_U16 u16Data;

    PRINTE(("MDrv_CofdmDmd_BlindScan_Cancel+\n"));
    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    bRet&=WriteReg(u16Address, u8Data);
    u16Address=MSB1240_TOP_WR_DBG_92_ADDR;
    u16Data=0x0000;
    bRet&=WriteReg2bytes(u16Address, u16Data);
    _u16TunerCenterFreq=0;
    _u16ChannelInfoIndex=0;
    PRINTE(("MDrv_CofdmDmd_BlindScan_Cancel-\n"));
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_End(void)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8   u8Data=0;//fix coverity 90924
    MS_U16 u16Data;

    PRINTE(("MDrv_CofdmDmd_BlindScan_End+\n"));
    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    bRet&=WriteReg(u16Address, u8Data);
    u16Address=MSB1240_TOP_WR_DBG_92_ADDR;
    u16Data=0x0000;
    bRet&=WriteReg2bytes(u16Address, u16Data);
    _u16TunerCenterFreq=0;
    _u16ChannelInfoIndex=0;
    PRINTE(("MDrv_CofdmDmd_BlindScan_End-\n"));
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_GetChannel(MS_U16 u16ReadStart,MS_U16* u16TPNum,DTVPROGRAMID_M *pTable)
{
    MS_BOOL bRet=TRUE;
    MS_U16  u16TableIndex;

    *u16TPNum=_u16ChannelInfoIndex-u16ReadStart;
    for(u16TableIndex = 0; u16TableIndex < (*u16TPNum); u16TableIndex++)
    {
        pTable[u16TableIndex].u32S2Frequency = _u16ChannelInfoArray[0][_u16ChannelInfoIndex-1];
        pTable[u16TableIndex].u16SymbolRate = _u16ChannelInfoArray[1][_u16ChannelInfoIndex-1];
       PRINTE(("MDrv_CofdmDmd_BlindScan_GetChannel Freq:%d SymbolRate:%d\n", pTable[u16TableIndex].u32S2Frequency, pTable[u16TableIndex].u16SymbolRate));
    }
    PRINTE(("MS124X u16TPNum:%d\n", *u16TPNum));
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MS_U32 *u32CurrentFeq)
{
    MS_BOOL bRet=TRUE;
    *u32CurrentFeq=_u16TunerCenterFreq;
    return bRet;
}

MS_BOOL MDrv_DiSEqC_SetTone(MS_BOOL bTone1)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8 u8Data;
    MS_U8 u8ReSet22k;

    u16Address=0x0DC4;
    u8Data=0x01;
    bRet&=WriteReg(u16Address, u8Data);

    u16Address=0x0DC0;
    u8Data=0x4E;
    bRet&=WriteReg(u16Address, u8Data);

    u16Address=0x0DCC;
    u8Data=0x80;
    bRet&=WriteReg(u16Address, u8Data);

    u16Address=0x0DC2;
    bRet&=ReadReg(u16Address, &u8Data);
    u8ReSet22k=u8Data;

    if (bTone1==TRUE)
    {
       u8Data=0x19;
       bRet&=WriteReg(u16Address, u8Data);
        _u8ToneBurstFlag=1;
    }
    else
    {
       u8Data=0x11;
       bRet&=WriteReg(u16Address, u8Data);
       _u8ToneBurstFlag=2;
    }
    u16Address=0x0DCD;
    u8Data=u8Data&~(0x01);
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data=u8Data|0x02;
    bRet&=WriteReg(u16Address, u8Data);
    MsOS_DelayTask(10);
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data=u8Data&~(0x02);
    bRet&=WriteReg(u16Address, u8Data);
    MsOS_DelayTask(1);
    u8Data=u8Data|0x01;
    bRet&=WriteReg(u16Address, u8Data);
    MsOS_DelayTask(100);

    u16Address=0x0DC2;
    u8Data=u8ReSet22k;
    bRet&=WriteReg(u16Address, u8Data);

    //MsOS_DelayTask(100);
    return bRet;
}
MS_BOOL MDrv_DiSEqC_SetLNBOut(MS_BOOL bLow)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8 u8Data=0;//fix coverity 51185

    u16Address=0x0DC2;
    bRet&=ReadReg(u16Address, &u8Data);
    if (bLow==TRUE)
    {
        u8Data=(u8Data|0x40);
    }
    else
    {
        u8Data=(u8Data&(~0x40));
    }
    bRet&=WriteReg(u16Address, u8Data);
    return bRet;
}
MS_BOOL MDrv_DiSEqC_GetLNBOut(MS_BOOL* bLNBOutLow)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8 u8Data=0;//fix coverity 51182

    u16Address=0x0DC2;
    bRet&=ReadReg(u16Address, &u8Data);
    if( (u8Data&0x40)==0x40)
    {
        * bLNBOutLow=TRUE;
    }
    else
    {
        * bLNBOutLow=FALSE;
    }
    return bRet;
}
MS_BOOL MDrv_DiSEqC_Set22kOnOff(MS_BOOL b22kOn)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8   u8Data=0;//fix coverity 51184

    u16Address=0x0DC2;
    bRet&=ReadReg(u16Address, &u8Data);
    if (b22kOn==TRUE)
    {
        // set bit[3:3]
        u8Data&=0xc7;
        u8Data|=0x08;
    }
    else
    {
        // clear bits[5:3]
        u8Data&=0xc7;
    }
    bRet&=WriteReg(u16Address, u8Data);
    return bRet;
}
MS_BOOL MDrv_DiSEqC_Get22kOnOff(MS_BOOL* b22kOn)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8   u8Data=0;//fix coverity 51181

    u16Address=0x0DC2;
    bRet&=ReadReg(u16Address, &u8Data);
    if ((u8Data&0x08)==0x08)
    {
        *b22kOn=TRUE;
    }
    else
    {
        *b22kOn=FALSE;
    }
    return bRet;
}
MS_BOOL MDrv_DiSEqC_SendCmd(MS_U8* pCmd,MS_U8 u8CmdSize)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U8   u8Data=0;//fix coverity 51183
    MS_U8   u8Index;
    MS_U16 u16WaitCount;

    u16WaitCount=0;
    do
    {
        u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
        bRet&=ReadReg(u16Address, &u8Data);
        MsOS_DelayTask(1);
        u16WaitCount++;
    }while(((u8Data&0x10)==0x10)&&(u16WaitCount < MSB124X_DEMOD_WAIT_TIMEOUT)) ;

    if (u16WaitCount >= MSB124X_DEMOD_WAIT_TIMEOUT)
    {
        PRINTE(("MSB124X DiSEqC Send Command Busy!!!\n"));
        return FALSE;
    }

    for (u8Index=0; u8Index < u8CmdSize; u8Index++)
    {
        u16Address=0x0DC4+u8Index;
        u8Data=*(pCmd+u8Index);
        bRet&=WriteReg(u16Address, u8Data);
    }
    u16Address=0x0B54;
    u8Data=((u8CmdSize-1)&0x07)|0x40;
    if (_u8ToneBurstFlag==1)
    {
        u8Data|=0x80;//0x20;
    }
    else if (_u8ToneBurstFlag==2)
    {
        u8Data|=0x20;//0x80;
    }
    _u8ToneBurstFlag=0;
    bRet&=WriteReg(u16Address, u8Data);
    MsOS_DelayTask(10);
    u16Address=MSB1240_TOP_WR_DBG_90_ADDR;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data=u8Data|0x10;
    bRet&=WriteReg(u16Address, u8Data);
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_GetLock(MS_BOOL *pbLock)
{
    MS_BOOL bRet=TRUE;

    *pbLock=MSB1240_DVBS_GetLock();
    return bRet;
}

//=== mailbox function ===
MS_BOOL  ReadMailbox(MS_U16 u16Addr, MS_U8* u8Data)
{
    MS_BOOL     status = true;
    MS_U8     cntl = 0x00;
    MS_U16    cntr = 0x00;
    //MS_U16    bank;
    MS_U16    addr;
    MS_U8     data;
   // MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);


   addr = REG_MB_ADDR_H;
   data = ((u16Addr >> 8)& 0xff) ;
   status &= WriteReg(addr, data);


   addr = REG_MB_ADDR_L;
   data = u16Addr & 0xff;
   status &= WriteReg(addr, data);


  addr = REG_MB_CNTL;
  status &= WriteReg(addr, 0x03); // 3: param read



  addr = REG_MB_DATA ;
  status &=ReadReg(addr, u8Data);


    do
    {
        addr = REG_MB_CNTL ;
        status &=ReadReg(addr, &cntl);
        if (cntr++ > 0x7ff)
        {
            //PRINTE(("MSB131X_MB_WRITE_FAILURE\n"));
            //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
            return FALSE;
        }
          addr = REG_MB_DATA ;
          status &=ReadReg(addr, u8Data);

    }
    while(cntl != 0xff);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return status;
}
#endif

void DVBT2Demod_Control_AGCOnOff(BOOLEAN bOn)
{
    MAPI_U8 u8Data = 0;
    MAPI_U8 u8Status = MAPI_TRUE;
    if(bOn) // turn on
    {
        u8Status &= ReadReg(0x0A00 + (0x18) * 2, &u8Data);
        u8Data |= 0x01;
        u8Status &= WriteReg(0x0A00 + (0x18) * 2, u8Data);
    }
    else  // turn off
    {
        u8Status &= ReadReg(0x0A00 + (0x18) * 2, &u8Data);
        u8Data &= (0xFF-0x01);
        u8Status &= WriteReg(0x0A00 + (0x18) * 2, u8Data);
    }
}

void DTV_ControlTsOutput(BOOLEAN bEnable)
{
    if(bEnable)
    {
        WriteReg(0x0900 + (0x2D*2), 0xFF);
        DBG_DEMOD_MSB(printf("MSB1240: Enable extend demod TS PAD\n"));
    }
    else
    {
        WriteReg(0x0900 + (0x2D*2), 0x00);
        DBG_DEMOD_MSB(printf("MSB1240: Disable extend demod TS PAD\n"));
    }
}
EN_MSB_124X_LOCK_STATUS DTV_DVB_T_GetLockStatus(void)
{
    EN_MSB_124X_LOCK_STATUS eLockStatus = E_MSB_124X_DEMOD_CHECKING;
    MSB124X_ExtendCmd(0xFF, 0, 0, (void *)&eLockStatus);
    return eLockStatus;
}


MAPI_BOOL DTV_DVB_T_Get_TPS_Parameter(MAPI_U16 * pu16TPS_parameter, E_SIGNAL_TYPE eSignalType)
{
    MAPI_U8         u8Data = 0;
    //if(DTV_DVB_T_GetLockStatus() == E_MSB_124X_DEMOD_LOCK)
    if (FECLock == TRUE)
    {
        if(eSignalType == TS_MODUL_MODE)
        {
            if(ReadReg(0x0F00 + (0x12 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT1 | BIT0));
        }

        else  if(eSignalType == TS_CODE_RATE)
        {
            if(ReadReg(0x0F00 + (0x12 * 2)+1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT6 | BIT5 | BIT4))>>4;
        }
        else if(eSignalType == TS_GUARD_INTERVAL)
        {
            if(ReadReg(0x0F00 + (0x01 * 2)+1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16TPS_parameter |= (((MAPI_U16) u8Data) & (BIT1 | BIT0)) ;
        }
        else if(eSignalType == TS_FFT_VALUE)
        {
           if(ReadReg(0x0E00 + (0x30 * 2) , &u8Data) == FALSE) // 0:2k,1:8k
            {
                return FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT0));

        }
        else
        {
            return FALSE;
        }
        DBG_DEMOD_MSB(printf(" Get T/C parameter %d, value = 0x%x\n", (MAPI_U16)eSignalType, *pu16TPS_parameter));
        return TRUE;
    }
    return FALSE;
}
MS_BOOL DTV_DVB_T_GetSignalTpsInfo(MS_U16 *TPS_Info)
{
    MS_U16 u16Data=0;//fix coverity 90920
    MS_BOOL bRet = TRUE;
    DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_CODE_RATE);
    *TPS_Info |= (u16Data & 0x07);
    DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_MODUL_MODE);
    *TPS_Info |= ((u16Data & 0x07) << 3);
    DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_GUARD_INTERVAL);
    *TPS_Info |= ((u16Data & 0x07) << 6);
    DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_FFT_VALUE);
    *TPS_Info |= ((u16Data & 0x07) << 9);
    return bRet;
}

MAPI_BOOL DTV_DVB_T2_Get_L1_Parameter(MAPI_U16 * pu16L1_parameter, E_T2_SIGNAL_INFO eSignalInfo)
{
    MAPI_U8     status = TRUE;
    MAPI_U8     u8Data = 0;
    MAPI_U16    FecType = 0;

    if (FECLock == TRUE)
    {
        if (eSignalInfo == T2_MODUL_MODE)
        {
            if (ReadReg(0x2700 + (0x47 * 2), &u8Data) == FALSE)
                return FALSE;

            *pu16L1_parameter  = (((MAPI_U16) u8Data) & (BIT5 | BIT4 | BIT3)) >> 3;
        }
        else  if (eSignalInfo == T2_CODE_RATE)
        {
            if (ReadReg(0x2700 + (0x47 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & (BIT2 | BIT1 | BIT0));
        }
        else if (eSignalInfo == T2_PREAMBLE)
        {
            if (ReadReg(0x2700 + (0x30 * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & (BIT4)) >> 4;
        }
        else if (eSignalInfo == T2_S1_SIGNALLING)
        {
            if (ReadReg(0x2700 + (0x30 * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & (BIT3 | BIT2 | BIT1)) >> 1;
        }
        else if (eSignalInfo == T2_PILOT_PATTERN)
        {
            if (ReadReg(0x2700 + (0x36 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & 0x0F);
        }
        else if (eSignalInfo == T2_BW_EXT)
        {
            if (ReadReg(0x2700 + (0x30 * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & (BIT0));
        }
        else if (eSignalInfo == T2_PAPR_REDUCTION)
        {
            if (ReadReg(0x2700 + (0x31 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & 0xF0) >> 4;
        }
        else if (eSignalInfo == T2_OFDM_SYMBOLS_PER_FRAME)
        {
            if (ReadReg(0x2700 + (0x3C * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (MAPI_U16) u8Data;
            if (ReadReg(0x2700 + (0x3C * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter |= (((MAPI_U16) u8Data) & 0x0F) << 8;
        }
        else if (eSignalInfo == T2_FFT_VALUE)
        {
            if (ReadReg(0x2700 + (0x30 * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            if ((u8Data & (BIT3 | BIT2)) >> 2)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & (BIT7 | BIT6 | BIT5)) >> 5;
        }
        else if (eSignalInfo == T2_GUARD_INTERVAL)
        {
            if (ReadReg(0x2700 + (0x31 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & (BIT3 | BIT2 | BIT1)) >> 1;
        }
        else if (eSignalInfo == T2_PLP_ROTATION)
        {
            if (ReadReg(0x2700 + (0x47 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MAPI_U16) u8Data) & BIT6) >> 6;
        }
        else if (eSignalInfo == T2_PLP_FEC_TYPE)
        {
            status &= ReadReg(0x278f, &u8Data);    //FEC Type[8:7]
            FecType = u8Data;
            status &= ReadReg(0x278e, &u8Data);    //FEC Type[8:7]
            FecType = (FecType << 8) | u8Data;

            *pu16L1_parameter = (FecType & 0x0180) >> 7;
        }
        else  if (eSignalInfo == T2_NUM_PLP)
        {
            if (ReadReg(0x2700 + (0x42 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (MAPI_U16)u8Data;
        }
        else
        {
            return FALSE;
        }
        DBG_DEMOD_MSB(printf(" Get T2 parameter %d, value = 0x%x\n", (MAPI_U16)eSignalInfo, *pu16L1_parameter));
        return status;

    }
    return FALSE;
}

EN_DVBT_CONSTEL_TYPE DTV_DVB_T_GetSignalModulation(void)
{
    MAPI_U16    u16Modulation = 0;
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
        {
           if(DTV_DVB_T2_Get_L1_Parameter(&u16Modulation, T2_MODUL_MODE) == FALSE)
           {
               printf("T2 L1 parameter can not be read.\n");
           }
           break;
        }
        case E_DEVICE_DEMOD_DVB_T:
        {
           if(DTV_DVB_T_Get_TPS_Parameter(&u16Modulation, TS_MODUL_MODE) == FALSE)
           {
               printf("TPS parameter can not be read.\n");
           }
           break;
        }
        default:
        {
           break;
        }
    DBG_DEMOD_MSB(printf("MSB1240 Extend Data Constellation Type = %d \n ", u16Modulation));
    }
    return (EN_DVBT_CONSTEL_TYPE)u16Modulation;
}
EN_DVBT_GUARD_INTERVAL DTV_DVB_T_GetSignalGuardInterval(void)
{
    MAPI_U16    u16GuardInterval = 0;

    if(DTV_DVB_T_Get_TPS_Parameter(&u16GuardInterval, TS_GUARD_INTERVAL) == FALSE)
    {
        printf("TPS parameter can not be read.\n");
    }
    printf("MSB1240 Extend Data Guard Interval = %d \n ", u16GuardInterval);
    return (EN_DVBT_GUARD_INTERVAL)u16GuardInterval;

}

EN_FRONTEND_SIGNAL_CONDITION DTV_GetSNR(void)
{
    MAPI_U8   status = MAPI_TRUE;
    float   f_snr = (float)0.0;
    MAPI_U32  snr_out = 0;
    MAPI_U8   reg = 0, reg_frz = 0,u8_gi = 0,u8_win = 0;

    EN_FRONTEND_SIGNAL_CONDITION eSignalCondition;
    eSignalCondition = E_FE_SIGNAL_NO;
    switch (m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            {
                //if(FECLock == FALSE) f_snr = (float)0.0;
                //else
                {
                    MAPI_U16 u16_snr100 = 0;
                    MAPI_U8  u8_reg = 0;
                    MAPI_U8  u8_freeze = 0;
                    //MAPI_U8  u8_win = 0;
                    //MAPI_U8  u8_gi = 0;

                    // freeze
                    status &= ReadReg(0x0b00+0x28*2+1, &u8_freeze);
                    status &= WriteReg(0x0b00+0x28*2+1, u8_freeze|0x80);

                    status &= ReadDspReg((MAPI_U16)E_T2_SNR_H,&u8_reg);
                    u16_snr100 = u8_reg;
                    status &= ReadDspReg((MAPI_U16)E_T2_SNR_L,&u8_reg);
                    u16_snr100 = (u16_snr100<<8)|u8_reg;

                    // unfreeze
                    status &= WriteReg(0x0b00+0x28*2+1, u8_freeze);

                    f_snr = (float)u16_snr100/100.0;

                    // snr cali
                    status &= ReadReg(0x2500+0x01*2, &u8_reg);
                    u8_win = (u8_reg>>2)&0x01;

                    if (u8_win == 1)
                    {
                        float snr_offset = 0.0;
                        float snr_cali = 0.0;

                        u8_gi = DTV_DVB_T_GetSignalGuardInterval();

                        if (u8_gi == 0) snr_offset = 0.157;
                        else if(u8_gi == 1) snr_offset = 0.317;
                        else if(u8_gi == 2) snr_offset = 0.645;
                        else if(u8_gi == 3) snr_offset = 1.335;
                        else if(u8_gi == 4) snr_offset = 0.039;
                        else if(u8_gi == 5) snr_offset = 0.771;
                        else if(u8_gi == 6) snr_offset = 0.378;

                        snr_cali = f_snr - snr_offset;
                        if (snr_cali > 0.0) f_snr = snr_cali;
                    }
                }

                g_msb1240_fSNR = f_snr;

                if (f_snr>25)
                eSignalCondition = E_FE_SIGNAL_STRONG;
                else if (f_snr>20)
                eSignalCondition = E_FE_SIGNAL_MODERATE;
                else if (f_snr>15)
                eSignalCondition = E_FE_SIGNAL_WEAK;
                else
                eSignalCondition = E_FE_SIGNAL_NO;
            }
            break;


           case E_DEVICE_DEMOD_DVB_T:

            // bank 6 0xfe [0] reg_fdp_freeze
            status &= ReadReg(0x0ffe, &reg);
            reg |= 0x01;
            status &= WriteReg(0x0ffe, reg);

            // bank 6 0xff [0] reg_fdp_load
            status &= WriteReg(0x0fff, 0x01);

            // bank 6 0x4a [26:0] reg_snr_accu <27,1>
            status &= ReadReg(0x0f4d, &reg);
            snr_out = reg & 0x07;
            status &= ReadReg(0x0f4c, &reg);
            snr_out = (snr_out << 8) | reg;
            status &= ReadReg(0x0f4b, &reg);
            snr_out = (snr_out << 8) | reg;
            status &= ReadReg(0x0f4a, &reg);
            snr_out = (snr_out << 8) | reg;
            snr_out = snr_out/2;

            // bank 6 0x26 [5:4] reg_transmission_mode
            status &= ReadReg(0x0f26, &reg);

            // bank 6 0xfe [0] reg_fdp_freeze
            status &= WriteReg(0x0ffe, reg_frz);

            // bank 6 0xff [0] reg_fdp_load
            status &= WriteReg(0x0fff, 0x01);

            if ((reg&0x30)==0x00)     //2K
            {
              if (snr_out<1512)
                  f_snr = 0;
              else
#ifdef MSOS_TYPE_LINUX
                  f_snr = 10*log10f((float)snr_out/6048);
#else
                  f_snr = 10*Log10Approx((float)snr_out/6048);
#endif
            }
            else
            {
              if (snr_out<6048)
                  f_snr = 0;
              else
#ifdef MSOS_TYPE_LINUX
                  f_snr = 10*log10f((float)snr_out/6048);
#else
                  f_snr = 10*Log10Approx((float)snr_out/6048);
#endif
            }

            // calibration, gi = 1/4, windowing enable...
            // get gi
            status &= ReadReg(0x0f26, &reg);
            u8_gi = reg&0x03;
            // windowing enable?
            status &= ReadReg(0x0f08, &reg);
            u8_win = reg&0x20;
            if ( u8_win != 0)
            {
              if (u8_gi == 3) f_snr -= 0.58;
              else if (u8_gi == 2) f_snr -=0.28;
            }
            if (status == FALSE)
                f_snr=-1;

            g_msb1233c_fSNR = f_snr;
            if (f_snr > 42) f_snr = 42;
            if (f_snr < 0) f_snr=0;
            if (f_snr > 25)
                eSignalCondition = E_FE_SIGNAL_STRONG;
            else if (f_snr > 20)
                eSignalCondition = E_FE_SIGNAL_MODERATE;
            else if (f_snr > 15)
                eSignalCondition = E_FE_SIGNAL_WEAK;
            else
                eSignalCondition = E_FE_SIGNAL_NO;
            break;

        case E_DEVICE_DEMOD_DVB_C:
            {
                MAPI_U8 u8Data = 0;
                MAPI_U16 u16_snr100 = 0;

                if(FECLock == FALSE)
                {
                    f_snr = (float)0.0;
                }
                else
                {
                    //int QAM_Mode;

                    //QAM_Mode = DTV_DVB_C_GetSignalModulation();//0:16q,1:32q,2:64q,3:128q,4:256q

                    // freeze
                    status &= ReadReg(DIG_DBG_BASE+0x52, &reg_frz);
                    status &= WriteReg(DIG_DBG_BASE+0x52, reg_frz|0x01);

                    status &= ReadDspReg((MAPI_U16)C_SNR100_H,&u8Data);
                    u16_snr100 = u8Data;
                    status &= ReadDspReg((MAPI_U16)C_SNR100_L,&u8Data);
                    u16_snr100 = (u16_snr100<<8)|u8Data;

                    // unfreeze
                    reg_frz=reg_frz&(~0x01);
                    status &= WriteReg(DIG_DBG_BASE+0x52, reg_frz);

                    f_snr = (float)u16_snr100/100.0;

                    //printf("f_snr=%f,",f_snr);
#if 0
                    if (QAM_Mode == 0) //16qam
                    f_snr -= 0.5;
                    else if (QAM_Mode == 2) //64qam
                    f_snr -= 0.2;
#endif
                    if (f_snr < 0)
                    {
                        f_snr = 0.0;
                    }
                }

                g_msb1240_fSNR = f_snr;

                if (f_snr>25)
                    eSignalCondition = E_FE_SIGNAL_STRONG;
                else if (f_snr>20)
                    eSignalCondition = E_FE_SIGNAL_MODERATE;
                else if (f_snr>15)
                    eSignalCondition = E_FE_SIGNAL_WEAK;
                else
                    eSignalCondition = E_FE_SIGNAL_NO;
            }
            break;
#if (ENABLE_S2)       
        case E_DEVICE_DEMOD_DVB_S:
            {
#if 0
                MAPI_U8 u8_reg = 0;
                MAPI_U16 u16_snr10 = 0;
                status &= ReadDspReg((MAPI_U16)E_S2_10SNR_H,&u8_reg);
                u16_snr10 = u8_reg;
                status &= ReadDspReg((MAPI_U16)E_S2_10SNR_L,&u8_reg);
                u16_snr10 = (u16_snr10<<8)|u8_reg;
                f_snr = (float)u16_snr10/10.0;
#else
                MAPI_BOOL bRet=MAPI_TRUE;
                MAPI_U16 u16Address =0;
                MAPI_U8  u8Data =0;
                //NDA SNR
                MAPI_U32 u32NDA_SNR_A =0;
                MAPI_U32 u32NDA_SNR_AB =0;
                
                //NDA SNR
                float NDA_SNR_A =0.0;
                float NDA_SNR_AB =0.0;
                // float NDA_SNR =0.0;
                
                // u16Address=0x1B08;
                // bRet&=ReadReg(u16Address, &u8Data);
                // u8Data|=0x10;
                // bRet&=WriteReg(u16Address, u8Data);
                //NDA SNR
                u16Address=0x1B8E;
                bRet&=ReadReg(u16Address, &u8Data);
                u32NDA_SNR_A=(u8Data&0x03);
                u16Address=0x1B8D;
                bRet&=ReadReg(u16Address, &u8Data);
                u32NDA_SNR_A=(u32NDA_SNR_A<<8)|u8Data;
                u16Address=0x1B8C;
                bRet&=ReadReg(u16Address, &u8Data);
                u32NDA_SNR_A=(u32NDA_SNR_A<<8)|u8Data;      
                //printf("u32NDA SNR A = %lu\n",u32NDA_SNR_A);
                
                u16Address=0x1B92;
                bRet&=ReadReg(u16Address, &u8Data);
                u32NDA_SNR_AB=(u8Data&0x3F);
                u16Address=0x1B91;
                bRet&=ReadReg(u16Address, &u8Data);
                u32NDA_SNR_AB=(u32NDA_SNR_AB<<8)|u8Data;
                u16Address=0x1B90;
                bRet&=ReadReg(u16Address, &u8Data);
                u32NDA_SNR_AB=(u32NDA_SNR_AB<<8)|u8Data;    
                //printf("u32NDA SNR AB = %lu\n",u32NDA_SNR_AB);
                
                // u16Address=0x1B08;
                // bRet&=ReadReg(u16Address, &u8Data);
                // u8Data&=~(0x10);
                // bRet&=WriteReg(u16Address, u8Data);
                
                if (bRet==MAPI_FALSE)
                {
                    printf(("MSB1240_DVBS_GetSignalNoiseRatio fail!!! \n"));
                }
                //NDA SNR
                if ((u32NDA_SNR_A==0) || (u32NDA_SNR_AB==0) || (bRet==MAPI_FALSE) )
                {
                    f_snr = 0.0;
                }
                else
                {
                    NDA_SNR_A=(float)u32NDA_SNR_A/65536;
                    NDA_SNR_AB=(float)u32NDA_SNR_AB/4194304;
                    
                    NDA_SNR_AB=(float)sqrt(NDA_SNR_AB);
                    if ((NDA_SNR_A/NDA_SNR_AB) > 1.0)
                    {
                        f_snr=10.0*log10((double)(1/((NDA_SNR_A/NDA_SNR_AB)-1)));
                    }
                    else
                    {
                        f_snr = 0.0; 
                    }
                }                                                        
#endif
                // f_snr = 6.0;
                g_msb1240_fSNR = f_snr;
                
                if (f_snr>12)
                    eSignalCondition = E_FE_SIGNAL_STRONG;
                else if (f_snr>8)
                    eSignalCondition = E_FE_SIGNAL_MODERATE;
                else if (f_snr>4)
                    eSignalCondition = E_FE_SIGNAL_WEAK;
                else
                     eSignalCondition = E_FE_SIGNAL_NO;

            }
            break;
#endif            
        default:
            f_snr = 0.0;
            eSignalCondition = E_FE_SIGNAL_NO;
            break;
    }
    DBG_GET_SIGNAL(printf(">>> SNR*100 = %d <<<\n", (int)g_msb1240_fSNR*100));
    return eSignalCondition;
}

MAPI_BOOL DTV_GetPreBER(float *p_preBer)
{
    MAPI_U16 BitErrPeriod = 0;
    MAPI_U32 BitErr = 0;
    MAPI_U8  reg = 0;
    MAPI_U16 FecType = 0;
    MAPI_U8  status = MAPI_TRUE;
    float    fber = (float)0.0;

    if (FECLock== TRUE)
    {
       switch(m_enCurrentDemodulator_Type)
       {
           case E_DEVICE_DEMOD_DVB_T2:
           {
               /////////// Data BER /////////////
               // bank 38 0x02 [0] freeze
               status &= WriteReg(0x2604, 0x01);  // avoid confliction

               // bank 38 0x12 Data BER Window[15:0]
               status &= ReadReg(0x2625, &reg);
               BitErrPeriod = reg;
               status &= ReadReg(0x2624, &reg);
               BitErrPeriod = (BitErrPeriod << 8) | reg;

               // bank 38 0x32 Data BER count[15:0]
               // bank 38 0x33 Data BER count[31:16]
               status &= ReadReg(0x2667, &reg);
               BitErr = reg;
               status &= ReadReg(0x2666, &reg);
               BitErr = (BitErr << 8) | reg;
               status &= ReadReg(0x2665, &reg);
               BitErr = (BitErr << 8) | reg;
               status &= ReadReg(0x2664, &reg);
               BitErr = (BitErr << 8) | reg;

               // bank 38 0x02 [0] freeze
               status &= WriteReg(0x2604, 0x00);   // avoid confliction
               if (BitErrPeriod == 0)
               //protect 0
                   BitErrPeriod = 1;

               status &= ReadReg(0x278f, &reg); //FEC Type[8:7]
               FecType = reg;
               status &= ReadReg(0x278e, &reg); //FEC Type[8:7]
               FecType = (FecType << 8) | reg;
               if (FecType&0x0180)
               {
                   if (BitErr == 0)
                       fber = (float)0.5/(float)(BitErrPeriod*64800);
                   else
                       fber = (float)BitErr/(float)(BitErrPeriod*64800);
               }
               else
               {
                   if (BitErr == 0)
                       fber = (float)0.5/(float)(BitErrPeriod*16200);
                   else
                       fber = (float)BitErr/(float)(BitErrPeriod*16200);
               }

               *p_preBer = fber;
               DBG_DEMOD_MSB(printf("MSB1240 Extend Data Pre BER = %8.3e \n ", fber));
           }
           break;

           case E_DEVICE_DEMOD_DVB_T:
           {
               /////////// Pre-Viterbi BER /////////////
               bool BEROver;
               U8 freeze_data=0;//fix coverity 90921

               // bank 0x1c 0x08 [3] reg_rd_freezeber
               status &= ReadReg(0x1c10, &freeze_data);
               freeze_data=freeze_data|0x08;
               status &= WriteReg(0x1c10, freeze_data);

               usleep(10);

               // bank 0x1c 0x08 [3] reg_rd_freezeber
               freeze_data=freeze_data&(~0x08);
               status &= WriteReg(0x1c10, freeze_data);

               // bank 0x1c 0x0b [7:0] reg_ber_timerl
               //               [15:8] reg_ber_timerm
               // bank 0x1c 0x0c [5:0] reg_ber_timerh
               status &= ReadReg(0x1c16, &reg);
               BitErrPeriod=reg;
               status &= ReadReg(0x1c17, &reg);
               BitErrPeriod=(reg<<8)|BitErrPeriod;
               status &= ReadReg(0x1c18, &reg);
               BitErrPeriod=((reg&0x3f)<<16)|BitErrPeriod;

               // bank 0x1c 0x0f [7:0] reg_ber_7_0
               //               [15:8] reg_ber_15_8
               status &= ReadReg(0x1c1e, &reg);
               BitErr=reg;
               status &= ReadReg(0x1c1f, &reg);
               BitErr=(reg<<8)|BitErr;
               // bank 0x11 0x0d [13:8] reg_cor_intstat_reg
               status &= ReadReg(0x1c1b, &reg);

               if (reg & 0x10)
                   BEROver = true;
               else
                   BEROver = false;

               if (BitErrPeriod ==0 )//protect 0
                   BitErrPeriod=1;
               if (BitErr <=0 )
                   fber=(float)0.5 /(float)(BitErrPeriod*256);
               else
                   fber=(float)BitErr/(float)(BitErrPeriod*256);

               if (BEROver == false)
                   *p_preBer = fber;
               else
                   *p_preBer =1;

               DBG_DEMOD_MSB(printf("MSB1240 Extend Data Pre BER = %8.3e \n ", fber));
           }
           break;

           case E_DEVICE_DEMOD_DVB_C:
           {
               *p_preBer = (float)0.0;
           }
           break;

           default:
               *p_preBer = (float)1.0;
                status = MAPI_FALSE;
       }
    }
    else
    {
        *p_preBer = (float)1.0;
        status = MAPI_FALSE;
    }
    return status;
}


//MAPI_BOOL DTV_GetPostBER(float *p_postBer)
MAPI_BOOL MSB124X_DTV_GetPostBER(float *p_postBer)
{
    MAPI_U16 BitErrPeriod = 0;
    MAPI_U16 BitErr = 0;
    MAPI_U8  reg = 0;
    float    fber = 0;
    MAPI_U8  status = MAPI_TRUE;
    MAPI_U16  FecType = 0;

    if (FECLock == TRUE)
    {
        switch(m_enCurrentDemodulator_Type)
        {
           case E_DEVICE_DEMOD_DVB_T2:
           {
               /////////// Data BER /////////////
               // bank 38 0x02 [0] freeze
               status &= WriteReg(0x2604, 0x01);  // avoid confliction

               // bank 38 0x12 Data BER Window[15:0]
               status &= ReadReg(0x2625, &reg);
               BitErrPeriod = reg;
               status &= ReadReg(0x2624, &reg);
               BitErrPeriod = (BitErrPeriod << 8) | reg;

               // bank 38 0x34 Data BER count[15:0]
               // bank 38 0x35 Data BER count[31:16]
               status &= ReadReg(0x2600+(0x34<<1)+3, &reg);
               BitErr = reg;
               status &= ReadReg(0x2600+(0x34<<1)+2, &reg);
               BitErr = (BitErr << 8) | reg;
               status &= ReadReg(0x2600+(0x34<<1)+1, &reg);
               BitErr = (BitErr << 8) | reg;
               status &= ReadReg(0x2600+(0x34<<1)+0, &reg);
               BitErr = (BitErr << 8) | reg;

               // bank 38 0x02 [0] freeze
               status &= WriteReg(0x2604, 0x00);   // avoid confliction

               if (BitErrPeriod == 0)
               //protect 0
                   BitErrPeriod = 1;

               status &= ReadReg(0x278f, &reg); //FEC Type[8:7]
               FecType = reg;
               status &= ReadReg(0x278e, &reg); //FEC Type[8:7]
               FecType = (FecType << 8) | reg;

               if (FecType&0x0180)
               {
                   if (BitErr == 0)
                       fber = (float)0.5/(float)(BitErrPeriod*64800);
                   else
                       fber = (float)BitErr/(float)(BitErrPeriod*64800);
               }
               else
               {
                   if (BitErr == 0)
                       fber = (float)0.5/(float)(BitErrPeriod*16200);
                   else
                       fber = (float)BitErr/(float)(BitErrPeriod*16200);
               }
               *p_postBer = fber;
               DBG_DEMOD_MSB(printf("MSB1240 Extend Data Post BER = %8.3e \n ", fber));
           }
           break;
           case E_DEVICE_DEMOD_DVB_T:
           case E_DEVICE_DEMOD_DVB_C:
            {
               MAPI_U8 reg_frz=0;

               /////////// Post-Viterbi BER /////////////
               // bank 0x11 0x19 [7] reg_bit_err_num_freeze
               status &= ReadReg(0x1132, & reg_frz);
               reg_frz=reg_frz|0x80;
               status &= WriteReg(0x1132, reg_frz);

               // bank 0x11 0x18 [7:0] reg_bit_err_sblprd_7_0
               // [15:8] reg_bit_err_sblprd_15_8
               status &= ReadReg(0x1131, &reg);
               BitErrPeriod = reg;
               status &= ReadReg(0x1130, &reg);
               BitErrPeriod = (BitErrPeriod << 8)|reg;

               // bank 0x11 0x1d [7:0] reg_bit_err_num_7_0
               // [15:8] reg_bit_err_num_15_8
               // bank 0x11 0x1e [7:0] reg_bit_err_num_23_16
               // [15:8] reg_bit_err_num_31_24
               status &= ReadReg(0x113D, &reg);
               BitErr = reg;
               status &= ReadReg(0x113C, &reg);
               BitErr = (BitErr << 8)|reg;
               status &= ReadReg(0x113B, &reg);
               BitErr = (BitErr << 8)|reg;
               status &= ReadReg(0x113A, &reg);
               BitErr = (BitErr << 8)|reg;

               // bank 0x11 0x19 [7] reg_bit_err_num_freeze
               reg_frz=reg_frz&(~0x80);
               status &= WriteReg(0x1132, reg_frz);

               if (BitErrPeriod ==0 )//protect 0
                   BitErrPeriod=1;

               if (BitErr <=0 )
               {
                   *p_postBer =0.5f / (double)(BitErrPeriod*128*188*8);
               }
               else
               {
                   *p_postBer = (double)(BitErr) /( double)(BitErrPeriod*128*188*8);
               }

               g_min_ber = 0.6f / ((float)BitErrPeriod*128*188*8);

               fber = *p_postBer;

               DBG_DEMOD_MSB(printf("MSB1240 Extend Data Post BER = %8.3e \n ", fber));
            }
           break;
#if (ENABLE_S2 )           
           case E_DEVICE_DEMOD_DVB_S:
           {
               if (_bDemodType==MAPI_FALSE)//S
               {
                   MAPI_U8 reg_frz=0;

                   /////////// Post-Viterbi BER /////////////
                   // bank 0x11 0x19 [7] reg_bit_err_num_freeze
                   status &= ReadReg(0x1132, & reg_frz);
                   reg_frz=reg_frz|0x80;
                   status &= WriteReg(0x1132, reg_frz);

                   // bank 0x11 0x18 [7:0] reg_bit_err_sblprd_7_0
                   // [15:8] reg_bit_err_sblprd_15_8
                   status &= ReadReg(0x1131, &reg);
                   BitErrPeriod = reg;
                   status &= ReadReg(0x1130, &reg);
                   BitErrPeriod = (BitErrPeriod << 8)|reg;

                   // bank 0x11 0x1d [7:0] reg_bit_err_num_7_0
                   // [15:8] reg_bit_err_num_15_8
                   // bank 0x11 0x1e [7:0] reg_bit_err_num_23_16
                   // [15:8] reg_bit_err_num_31_24
                   status &= ReadReg(0x113D, &reg);
                   BitErr = reg;
                   status &= ReadReg(0x113C, &reg);
                   BitErr = (BitErr << 8)|reg;
                   status &= ReadReg(0x113B, &reg);
                   BitErr = (BitErr << 8)|reg;
                   status &= ReadReg(0x113A, &reg);
                   BitErr = (BitErr << 8)|reg;

                   // bank 0x11 0x19 [7] reg_bit_err_num_freeze
                   reg_frz=reg_frz&(~0x80);
                   status &= WriteReg(0x1132, reg_frz);

                   if (BitErrPeriod ==0 )//protect 0
                       BitErrPeriod=1;

                   if (BitErr <=0 )
                   {
                       fber =0.5f / (double)(BitErrPeriod*128*188*8);
                   }
                   else
                   {
                       fber = (double)(BitErr) /( double)(BitErrPeriod*128*188*8);
                   }
                   *p_postBer = fber;
                   DBG_DEMOD_MSB(printf("MSB1240[S] Extend Data Post BER = %8.3e \n ", fber));
               }
               else
               {  // S2
                   /////////// Data BER /////////////
                   // bank 38 0x02 [0] freeze
                   // status &= WriteReg(0x2604, 0x01);  // avoid confliction

                   // bank 38 0x12 Data BER Window[15:0]
                   status &= ReadReg(0x2600+(25<<1)+1, &reg);
                   BitErrPeriod = reg;
                   status &= ReadReg(0x2600+(25<<1), &reg);
                   BitErrPeriod = (BitErrPeriod << 8) | reg;

                   // bank 38 0x34 Data BER count[15:0]
                   // bank 38 0x35 Data BER count[31:16]
                   // status &= ReadReg(0x2600+(0x26<<1)+3, &reg);
                   // BitErr = reg;
                   // status &= ReadReg(0x2600+(0x26<<1)+2, &reg);
                   // BitErr = (BitErr << 8) | reg;
                   status &= ReadReg(0x2600+(0x26<<1)+1, &reg);
                   BitErr = reg;
                   status &= ReadReg(0x2600+(0x26<<1)+0, &reg);
                   BitErr = (BitErr << 8) | reg;

                   // bank 38 0x02 [0] freeze
                   // status &= WriteReg(0x2604, 0x00);   // avoid confliction

                   if (BitErrPeriod == 0)
                   //protect 0
                       BitErrPeriod = 1;

                   if (BitErr == 0)
                       fber = (float)0.0001/(float)(BitErrPeriod*4);
                   else
                       fber = (float)BitErr/(float)(BitErrPeriod*4);

                   *p_postBer = fber;
                   DBG_DEMOD_MSB(printf("MSB1240[S2] Extend Data Post BER = %8.3e \n ", fber));
               }
           }
           break;
#endif           
           default:
                fber   = (float)1.0;
                status = MAPI_FALSE;
                break;
        }
    }
    else
    {
        fber = (float)1.0;
        status = MAPI_FALSE;
    }
    return status;
}

MAPI_U32 DTV_GetBER(void)
{
    float    fber =  (float)0.0;
    return (U32)fber;
}

MAPI_BOOL DTV_GetPacketErr(MAPI_U16 *pu16BitErr)
{
    MAPI_BOOL status = MAPI_TRUE;
    MAPI_U8   reg = 0, reg_frz;
    MAPI_U16  PktErr=0;

    if (FECLock == TRUE)
    {
        if (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
        {
            //freeze
            status &= WriteReg(0x2604, 0x01);

            //read packet error
            status &= ReadReg(0x265B, &reg);
            PktErr = reg;
            status &= ReadReg(0x265A, &reg);
            PktErr = (PktErr << 8) | reg;

            //release
            status &= WriteReg(0x2604, 0x00);

            *pu16BitErr = PktErr;

            DBG_DEMOD_MSB(printf("===================>MSB1240 T2 PktErr = %d \n ", (int)PktErr));
        }
        else
        {
            reg_frz = 0;
            // bank 0x11 0x19 [7] reg_bit_err_num_freeze
            status &= ReadReg(0x1132, &reg_frz);
            status &= WriteReg(0x1132, reg_frz | 0x80);

            // bank 0x11 0x1f [7:0] reg_uncrt_pkt_num_7_0
            //         [15:8] reg_uncrt_pkt_num_15_8
            status &= ReadReg(0x113F, &reg);
            PktErr = reg;
            status &= ReadReg(0x113E, &reg);
            PktErr = (PktErr << 8) | reg;

            // bank 0x11 0x19 [7] reg_bit_err_num_freeze
            status &= WriteReg(0x1132, reg_frz);

            *pu16BitErr = PktErr;

            DBG_DEMOD_MSB(printf("===================>MSB1240 T/C PktErr = %d \n ", (int)PktErr));
        }
    }
    else
        *pu16BitErr = 65535;

    if (status)
    {
        DBG_DEMOD_MSB(printf(" @MSB1240_Get_Packet_Error OK\n"));
        return  MAPI_TRUE;
    }
    else
    {
        DBG_DEMOD_MSB(printf(" @MSB1240_Get_Packet_Error NG\n"));
        return MAPI_FALSE;
    }
}

EN_DVBT_CODE_RATE DTV_DVB_T_GetSignalCodeRate(void)
{
    MAPI_U16    u16CodeRate = 0;
    switch(m_enCurrentDemodulator_Type)
    {
       case E_DEVICE_DEMOD_DVB_T2:
       {
           if(DTV_DVB_T2_Get_L1_Parameter(&u16CodeRate, T2_CODE_RATE) == FALSE)
           {
               printf("TPS parameter can not be read.\n");
           }
           break;
       }

       case E_DEVICE_DEMOD_DVB_T:
       {
           if(DTV_DVB_T_Get_TPS_Parameter(&u16CodeRate, TS_CODE_RATE) == FALSE)
           {
               printf("TPS parameter can not be read.\n");
           }
           break;
       }

       default:
       {
           break;
       }
    }  // end of switch
   DBG_DEMOD_MSB(printf("MSB1240 Extend Data Code Rate = %d \n ", u16CodeRate));
return (EN_DVBT_CODE_RATE)u16CodeRate;
}

MAPI_BOOL DTV_DVB_C_SetFrequency(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth,MAPI_U32 u32SymRate, MAPI_U8 eQAM)
{
    printf("%s(),%d\n",__FUNCTION__,__LINE__);

    MAPI_U8             reg_symrate_l = 0;
    MAPI_U8             reg_symrate_h = 0;

    MAPI_U32            u32DMD_IfFreq = 5000;
    MAPI_U8             u8_if_agc_mode = 0;

    //mapi_tuner          *pTuner = NULL;
    MAPI_BOOL           status = true;


    g_u32Frequency = u32Frequency;
    eBandWidth = eBandWidth;

    DBG_DEMOD_MSB(printf("DTV_SetFrequency %d ,%d \n", (int)u32Frequency, (int)eBandWidth));
    //mapi_scope_lock(scopeLock, &m_MutexOuter);

    if (g_u8_msb1240_sleep_mode_status != 0)
    {
        //printf("%s, %s, %d, MSB1240 is sleeping, wake him up first\n",__FILE__,__FUNCTION__,__LINE__);
        return FALSE;
    }

    // SetDvbcParam(eQAM);//QAM

    reg_symrate_l = (MAPI_U8) (u32SymRate & 0xff);
    reg_symrate_h = (MAPI_U8) (u32SymRate >> 8);
    // reg_qam = gQamVal;
/*
    pTuner = Get_mapi_pcb()->GetDvbtTuner(0);
    if (pTuner!=NULL)
    {
        if ( MAPI_FALSE == (pTuner->ExtendCommand(E_TUNER_SUBCMD_GET_DTV_IF_FREQ, E_TUNER_DTV_DVB_C_MODE, E_RF_CH_BAND_8MHz, &u32DMD_IfFreq)))
        {
            u32DMD_IfFreq = 5000;
        }
        if ( MAPI_FALSE == (pTuner->ExtendCommand(E_TUNER_SUBCMD_GET_DEMOD_CONFIG, E_TUNER_DTV_DVB_T2_MODE, eBandWidth, (void*)&u8_if_agc_mode)))
        {
            u8_if_agc_mode = 0;
        }
    }
*/
    //// Reset Demod ///////////////////
    Reset();
    usleep(500);
    //// DSP Register Overwrite ///////////////////
    status &= WriteDspReg((MAPI_U16)C_config_fc_l, (MAPI_U8)u32DMD_IfFreq);
    status &= WriteDspReg((MAPI_U16)C_config_fc_h, (MAPI_U8)(u32DMD_IfFreq>>8));
    status &= WriteDspReg((MAPI_U16)C_if_inv_pwm_out_en, u8_if_agc_mode);
    if (u32SymRate == 0)//Auto SR QAM Mode
    {
        // DTV_DVB_C_Set_Config_dvbc_auto(MAPI_TRUE);
        status &= WriteDspReg((MAPI_U16)C_opmode_auto_scan_sym_rate, 1);
        status &= WriteDspReg((MAPI_U16)C_opmode_auto_scan_qam, 1);
        status &= WriteDspReg((MAPI_U16)C_config_bw_l, C_BW_L);
        status &= WriteDspReg((MAPI_U16)C_config_bw_h, C_BW_H);
    }
    else //Manual Mode
    {
        status &= WriteDspReg((MAPI_U16)C_opmode_auto_scan_sym_rate, 0);
        status &= WriteDspReg((MAPI_U16)C_opmode_auto_scan_qam, 0);
        status &= WriteDspReg((MAPI_U16)C_config_bw_l, reg_symrate_l);
        status &= WriteDspReg((MAPI_U16)C_config_bw_h, reg_symrate_h);
        status &= WriteDspReg((MAPI_U16)C_config_qam, eQAM);
    }
    DBG_DEMOD_MSB(printf(" @MSB1240_dvbc_config SymRate=[%d]\n",(int)u32SymRate));
    DBG_DEMOD_MSB(printf(" @MSB1240_dvbc_config QAM Mode=[%d]\n",eQAM));
    DBG_DEMOD_MSB(printf(" @MSB1240_dvbc_config OK\n"));

    status &= WriteReg(REG_FSM_EN, 0x01);

    return status;
}

MAPI_U16 DTV_DVB_C_GetCurrentSymbolRate(void)
{
    MAPI_U32 u32_intp = 0;
    MAPI_U8  u8_reg = 0;
    float    symbol_rate = 0.0;

    ReadReg(0x2C00 + (0x27) * 2 + 3, &u8_reg);
    u32_intp = u8_reg;
    ReadReg(0x2C00 + (0x27) * 2 + 2, &u8_reg);
    u32_intp = (u32_intp<<8)|u8_reg;
    ReadReg(0x2C00 + (0x27) * 2 + 1, &u8_reg);
    u32_intp = (u32_intp<<8)|u8_reg;
    ReadReg(0x2C00 + (0x27) * 2 + 0, &u8_reg);
    u32_intp = (u32_intp<<8)|u8_reg;

    symbol_rate = 12.0/((float)u32_intp/4194304.0 + 1.0)*1000;

    //printf("%s(),%d, sr=%d\n",__FUNCTION__,__LINE__,(MAPI_U16)symbol_rate);
    return (MAPI_U16)symbol_rate;
}

MAPI_U8 DTV_DVB_C_GetSignalModulation(void)
{
    MAPI_U8  u8_reg = 0;

    // 0:16q,1:32q,2:64q,3:128q,4:256q
    ReadReg(0x2302, &u8_reg);
    u8_reg = u8_reg&0x07;

     //printf("%s(),%d, qam=%d\n",__FUNCTION__,__LINE__,u8_reg);


    return u8_reg;
}

MAPI_U16 DTV_GetSignalQuality(void)
{
    MAPI_U16    BitErrPeriod = 0;
    MAPI_U32    BitErr = 0;
    //MAPI_U16    FecType = 0;

    // MAPI_U8     fViterbiBerFiltered=-1;

    float       ber = (float)0.0;
    float       ber_sqi = (float)0.0;

    //float       log_ber = (float)0.0;

    MAPI_U8     tps_cnstl = 0, tps_cr = 0, i = 0;
    MS_U8       tps_param;
    MS_U16      u16_tmp = 0;
    float       cn_nordig_p1 = 0;
    E_SIGNAL_TYPE eSignalType;
    MAPI_U8     reg_frz = 0;
    #define DVBT2_BER_TH_HY 0.1
    MAPI_U8     status = true;
    MAPI_U8     reg = 0; //, reg_frz;
    MAPI_U8     u8_index = 0;
    float       fber = (float)0.0;
    float       SQI = (float)0.0;
    float       BER_SQI = (float)0.0;
    float       cn_ref = (float)0.0;
    float       cn_rec = (float)0.0;
    float       cn_rel = (float)0.0;
    static MAPI_U8 u8State = 0;
    float fBerTH1[] = {1E-4, 1E-4*(1.0-DVBT2_BER_TH_HY), 1E-4*(1.0+DVBT2_BER_TH_HY), 1E-4};
    float fBerTH2[] = {3E-7, 3E-7, 3E-7*(1.0-DVBT2_BER_TH_HY), 3E-7*(1.0+DVBT2_BER_TH_HY)};
    static float fBerFiltered = -1.0;

    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
        {
            E_T2_CONSTEL  constel =  _T2_QAM_UNKNOWN;
            E_T2_CODERATE coderate = _T2_CR_UNKNOWN;

            /////////// Check lock status /////////////
            status &= ReadDspReg(0x00f0, &reg);
            if((reg & BIT7) == 0x00)
            {
                printf("%s,%d,is no signal \r\n",__FUNCTION__,__LINE__);
                return 0;
            }
            printf("%s,%d\r\n",__FUNCTION__,__LINE__);

           status &= MSB124X_DTV_GetPostBER(&fber); // get BER

            if(status == FALSE)
            {
                printf("%s,%d\r\n",__FUNCTION__,__LINE__);
                //DBG_DEMOD_MSB(printf("DTV_GetSignalQuality_DVBT2_GetPostViterbiBer Fail!\n"));
                return 0;
            }

            if ((fBerFiltered <= 0.0) || ((fBerFiltered/fber) > 30.0 || (fBerFiltered/fber) < 0.03))
                fBerFiltered = fber;
            else
                fBerFiltered = 0.9f*fBerFiltered+0.1f*fber;
            fber = fBerFiltered;

            if (fber > fBerTH1[u8State])
            {
               BER_SQI = 0.0;
               u8State = 1;
            }
            else if (fber >=fBerTH2[u8State])
            {
               BER_SQI = 100.0/15;
               u8State = 2;
            }
            else
            {
               BER_SQI = 100.0/6;
               u8State = 3;
            }

            coderate = (E_T2_CODERATE)DTV_DVB_T_GetSignalCodeRate();
            constel = (E_T2_CONSTEL)DTV_DVB_T_GetSignalModulation();

            DTV_GetSNR();
            cn_rec = g_msb1240_fSNR;

            cn_ref = (float)-1.0;
            while(g_msb1240_dvbt2_sqi_cn_nordigp1[u8_index].constel != _T2_QAM_UNKNOWN)
            {
                if ((g_msb1240_dvbt2_sqi_cn_nordigp1[u8_index].constel == constel)
                    && (g_msb1240_dvbt2_sqi_cn_nordigp1[u8_index].code_rate == coderate))
                {
                   cn_ref = g_msb1240_dvbt2_sqi_cn_nordigp1[u8_index].cn_ref;
                   break;
                }
                else
                {
                   u8_index++;
                }
            }
            if (cn_ref == -1.0)
                SQI = (float)0.0;
            else
            {
                cn_rel = cn_rec - cn_ref;
                if (cn_rel > 3.0)
                    SQI = 100;
                else if (cn_rel >= -3)
                {
                    SQI = (cn_rel+3)*BER_SQI;
                    if (SQI > 100.0) SQI = 100.0;
                    else if (SQI < 0.0) SQI = 0.0;
                }
                else
                    SQI = (float)0.0;
            }

            // SQI patch, 256qam, R3/4 CN=20.8, SQI=0~13
            if ((constel==_T2_256QAM) && (coderate==_T2_CR3Y4))
            {
               if ( (cn_rec > 20.6) && (cn_rec < 20.9))
               {
                   if (SQI > 3) SQI -= 3;
               }
               else if ( (cn_rec >= 20.9) && (cn_rec < 21.2))
               {
                   if (SQI > 9) SQI -= 9;
               }
            }

            DBG_DEMOD_MSB(printf("[msb123x]signalquality, coderate=%d, constel=%d,cn_rec=%f, cn_ref=%f, BER_SQI=%f, SQI=%f, ber=%f\n",coderate,constel,cn_rec,cn_ref,BER_SQI,SQI, fber);)
            DBG_GET_SIGNAL(printf(">>> SQI = %d <<<\n", (int)SQI));
            return SQI;
            break;
        }
        break;

        case E_DEVICE_DEMOD_DVB_T:
        {

            status &= ReadReg(0x20ef, &reg);
            /////////// Post-Viterbi BER /////////////
            //printf("%s,%d\r\n",__FUNCTION__,__LINE__);

            // bank 7 0x32 [7] reg_bit_err_num_freeze
            status &= ReadReg(0x1132, &reg_frz);
            status &= WriteReg(0x1132, reg_frz | 0x80);

            // bank 7 0x30 [7:0] reg_bit_err_sblprd_7_0
            //             [15:8] reg_bit_err_sblprd_15_8
            status &= ReadReg(0x1131, &reg);
            BitErrPeriod = reg;

            status &= ReadReg(0x1130, &reg);
            BitErrPeriod = (BitErrPeriod << 8) | reg;
            //printf("BitErrPeriod [%d]\n",BitErrPeriod);/////////////
            // bank 7 0x3a [7:0] reg_bit_err_num_7_0
            //             [15:8] reg_bit_err_num_15_8
            // bank 7 0x3c [7:0] reg_bit_err_num_23_16
            //             [15:8] reg_bit_err_num_31_24

            status &= ReadReg(0x113D, &reg);
            BitErr = reg;

            status &= ReadReg(0x113C, &reg);
            BitErr = (BitErr << 8) | reg;

            status &= ReadReg(0x113B, &reg);
            BitErr = (BitErr << 8) | reg;

            status &= ReadReg(0x113A, &reg);
            BitErr = (BitErr << 8) | reg;

            if (BitErrPeriod == 0 )    //protect 0
                 BitErrPeriod = 1;
            if (BitErr <=0 )
                 ber = 0.5f / ((float)BitErrPeriod*128*188*8);
            else
                 ber = (float)BitErr / ((float)BitErrPeriod*128*188*8);

            if (ber > 1.0E-3)
                 ber_sqi = 0.0;
            else if (ber > 1.0E-7)
#ifdef MSOS_TYPE_LINUX
                 ber_sqi = (log10f(1.0f/ber))*20.0f - 26.0f;//ted
#else
                 ber_sqi = (Log10Approx(1.0f/ber))*20.0f - 26.0f;//ted
#endif
            else
                 ber_sqi = 100.0;

            g_min_ber = 0.6f / ((float)BitErrPeriod*128*188*8);
            if (ber < g_min_ber) ber_sqi = 100.0;

            DTV_GetSNR();
            cn_rec=g_msb1233c_fSNR;
            if (cn_rec == -1)   //get SNR return fail
                 status = FALSE;

        ///////// Get Constellation and Code Rate to determine Ref. C/N //////////

            tps_cnstl = 0xff;
            tps_cr = 0xff;

            eSignalType = TS_MODUL_MODE;
            if (eSignalType == TS_MODUL_MODE)
            {
                if ( ReadReg(0x0f00 + 0x24, &tps_param) == FALSE )
                     break;
                else
                    {
                     u16_tmp = tps_param & (BIT(0)|BIT(1)) ;
                    }
            }
            tps_cnstl = (MS_U8)u16_tmp&0x07;

            eSignalType = TS_CODE_RATE;
            if (eSignalType == TS_CODE_RATE)
            {
                if ( ReadReg(0x0f00 + 0x25, &tps_param) == FALSE )
                    {
                     break;
                    }
                else
                    {
                     u16_tmp = (tps_param & (BIT(6)|BIT(5)|BIT(4)))>>4 ;
                    }
            }
            tps_cr = (MS_U8)u16_tmp&0x07;

            for(i = 0; i < sizeof(SqiCnNordigP1)/sizeof(DMD_SQI_CN_NORDIGP1); i++)
            {
              if ( (tps_cnstl == SqiCnNordigP1[i].constel)&& (tps_cr == SqiCnNordigP1[i].code_rate) )
              {
                  cn_nordig_p1 = SqiCnNordigP1[i].cn_ref;
                  break;
              }
            }
            // 0,5, snr offset
            cn_rel = cn_rec - cn_nordig_p1 + 1.6f;
            if (cn_rel < -7.0f)
            {
                SQI= 0;
            }
            else if (cn_rel < 3.0)
            {
               SQI= (MS_U16)(ber_sqi*((cn_rel - 3.0)/10.0 + 1.0));
            }
            else
            {
                SQI= (MS_U16)ber_sqi;
            }
            DBG_DEMOD_MSB(printf("[msb124x]dvbt signal quality, cn_rec=%d, cn_ref=%d, BER_SQI=%d, SQI=%d, ber=%d\n",cn_rec,cn_ref,BER_SQI,SQI, fber);)
            DBG_GET_SIGNAL(printf(">>> SQI = %d <<<\n", (int)SQI));
            return SQI;
            break;
        }
        case E_DEVICE_DEMOD_DVB_C:
        {
            float   f_snr = 0.0;
            MAPI_U8   Qam_mode;

            MSB124X_DTV_GetPostBER(&fber);//get DVBT post ber

            DTV_GetSNR();
            f_snr = g_msb1240_fSNR;

            Qam_mode = DTV_DVB_C_GetSignalModulation();//0:16q,1:32q,2:64q,3:128q,4:256q

#if(D_CUSTOMER == formula_A)
            //float   ber_sqi = 0.0;
            if (fber > 1.0E-3)
            {
                ber_sqi = 0.0;
            }
            else if(fber > g_min_ber)
            {
                ber_sqi = (Log10Approx(1.0f/fber))*20.0f - 40.0f;
            }
            else
            {
                ber_sqi = 100.0;
            }

            if( (MAPI_U8)Qam_mode <= 4)//DMD_DVBC_QAM256
            {
                cn_rel = f_snr - cn_nordig_p1_DVBC[(MAPI_U8)Qam_mode];
            }
            else
            {
                cn_rel = -100.0f;
            }

            if (cn_rel < -7.0f)
            {
                SQI = 0;
            }
            else if (cn_rel < 3.0)
            {
                SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3.0)/10.0 + 1.0));
            }
            else
            {
                SQI = (MAPI_U16)ber_sqi;
            }

#elif(D_CUSTOMER == formula_B)
            if (Qam_mode == 0)//DMD_DVBC_QAM16
            {
                if (f_snr <= (14.2 + 0.6)) SQI = 0;
                else if (f_snr <= (15.7+0.3)) SQI = 20;
                else if (f_snr <= (16.6+0.2)) SQI = 30;
                else if (f_snr <= (17.3+0.1)) SQI = 40;
                else if (f_snr <= 18.0) SQI = 50;
                else if (f_snr <= 18.9) SQI = 60;
                else if (f_snr <= (20.1-0.1)) SQI = 70;
                // else if (f_snr <= 20.3) SQI = 80;
                else if (f_snr <= (20.4-0.2)) SQI = 80;
                else if (f_snr <= (20.6-0.2)) SQI = 90;
                else SQI = 100;
            }
            else if (Qam_mode == 1)//DMD_DVBC_QAM32
            {
                if (f_snr <= 17.2) SQI = 0;
                else if (f_snr <= 18.7) SQI = 20;
                else if (f_snr <= 19.6) SQI = 30;
                else if (f_snr <= 20.3) SQI = 40;
                else if (f_snr <= 21.0) SQI = 50;
                else if (f_snr <= 21.9) SQI = 60;
                else if (f_snr <= 23.1) SQI = 70;
                else if (f_snr <= 23.3) SQI = 80;
                else if (f_snr <= 23.4) SQI = 90;
                else if (f_snr <= 23.6) SQI = 100;
                else SQI = 100;
            }
            else if (Qam_mode == 2)//DMD_DVBC_QAM64
            {
                if (f_snr <= 19.5) SQI = 0;
                else if (f_snr <= 20.0) SQI = 10;
                else if (f_snr <= (21.6 + 0.1)) SQI = 20;
                else if (f_snr <= 22.5) SQI= 30;
                else if (f_snr <= 23.3) SQI = 40;
                else if (f_snr <= 24.1) SQI = 50;
                else if (f_snr <= 25.0) SQI = 60;
                else if (f_snr <= (26.3-0.1)) SQI = 70;
                // else if (f_snr <= (26.5-0.1)) SQI = 80;
                else if (f_snr <= (26.6-0.2)) SQI = 80;
                else if (f_snr <= (26.9 -0.2)) SQI = 90;
                else SQI = 100;
            }
            else if (Qam_mode == 3)//DMD_DVBC_QAM128
            {
                if (f_snr <= (22.0 + 0.4)) SQI = 0;
                else if (f_snr <= 22.5) SQI = 10;
                else if (f_snr <= (24.4+0.2)) SQI = 20;
                else if (f_snr <= (25.3+0.1)) SQI = 30;
                else if (f_snr <= (26.2+0.1)) SQI = 40;
                else if (f_snr <= (27.0+0.1)) SQI = 50;
                else if (f_snr <= (28.0+0.1)) SQI = 60;
                else if (f_snr <= (29.2+0.2)) SQI = 70;
                // else if (f_snr <= (29.5+0.1)) SQI = 80;
                else if (f_snr <= 29.7) SQI = 80;
                // else if (f_snr <= 29.8) SQI = 90;
                else if (f_snr <= 29.9) SQI = 90;
                else SQI = 100;
            }
            else //256QAM
            {
                if (f_snr <= 25.4) SQI = 0;
                else if (f_snr <= 27.6) SQI = 20;
                else if (f_snr <= 28.5) SQI = 30;
                else if (f_snr <= 29.4) SQI = 40;
                else if (f_snr <= 30.3) SQI = 50;
                else if (f_snr <= 31.3) SQI = 60;
                else if (f_snr <= 32.8) SQI = 70;
                else if (f_snr <= 33.1) SQI = 80;
                else if (f_snr <= 33.3) SQI = 90;
                // else if (f_snr <= 33.4) SQI = 90;
                // else if (f_snr <= 33.5) SQI = 90;
                else SQI = 100;
            }
#else
            float   log_ber;
            log_ber = (-1.0f)*Log10Approx(1.0f/fber); // Log10Approx() provide 1~2^32 input range only

            if (Qam_mode == 0)//DMD_DVBC_QAM16
            {
               if(log_ber  <= (-5.5f))
                    SQI = 100;
                else if(log_ber  <= (-5.1f))
                    SQI = (MAPI_U16)(90.0f + ((-5.1f)-log_ber)*10.0f/((-5.1f)-(-5.5f)));
                else if(log_ber  <= (-4.9f))
                    SQI = (MAPI_U16)(80.0f + ((-4.9f)-log_ber)*10.0f/((-4.9f)-(-5.1f)));
                else if(log_ber  <= (-4.5f))
                    SQI = (MAPI_U16)(70.0f + ((-4.5f)-log_ber)*10.0f/((-4.5f)-(-4.9f)));
                else if(log_ber  <= (-3.7f))
                    SQI = (MAPI_U16)(60.0f + ((-3.7f)-log_ber)*10.0f/((-3.7f)-(-4.5f)));
                else if(log_ber  <= (-3.2f))
                    SQI = (MAPI_U16)(50.0f + ((-3.2f)-log_ber)*10.0f/((-3.2f)-(-3.7f)));
                else if(log_ber  <= (-2.9f))
                    SQI = (MAPI_U16)(40.0f + ((-2.9f)-log_ber)*10.0f/((-2.9f)-(-3.2f)));
                else if(log_ber  <= (-2.5f))
                    SQI = (MAPI_U16)(30.0f + ((-2.5f)-log_ber)*10.0f/((-2.5f)-(-2.9f)));
                else if(log_ber  <= (-2.2f))
                    SQI = (MAPI_U16)(20.0f + ((-2.2f)-log_ber)*10.0f/((-2.2f)-(-2.5f)));
                else if(log_ber  <= (-2.0f))
                    SQI = (MAPI_U16)(0.0f + ((-2.0f)-log_ber)*10.0f/((-2.0f)-(-2.2f)));
                else
                    SQI = 0;
            }
            else if (Qam_mode == 1)//DMD_DVBC_QAM32
            {
                if(log_ber  <= (-5.0f))
                    SQI = 100;
                else if(log_ber  <= (-4.7f))
                    SQI = (MAPI_U16)(90.0f  + ((-4.7f)-log_ber)*10.0f/((-4.7f)-(-5.0f)));
                else if(log_ber  <= (-4.5f))
                    SQI = (MAPI_U16)(80.0f  + ((-4.5f)-log_ber)*10.0f/((-4.5f)-(-4.7f)));
                else if(log_ber  <= (-3.8f))
                    SQI = (MAPI_U16)(70.0f  + ((-3.8f)-log_ber)*10.0f/((-3.8f)-(-4.5f)));
                else if(log_ber  <= (-3.5f))
                    SQI = (MAPI_U16)(60.0f  + ((-3.5f)-log_ber)*10.0f/((-3.5f)-(-3.8f)));
                else if(log_ber  <= (-3.0f))
                    SQI = (MAPI_U16)(50.0f  + ((-3.0f)-log_ber)*10.0f/((-3.0f)-(-3.5f)));
                else if(log_ber  <= (-2.7f))
                    SQI = (MAPI_U16)(40.0f  + ((-2.7f)-log_ber)*10.0f/((-2.7f)-(-3.0f)));
                else if(log_ber  <= (-2.4f))
                    SQI = (MAPI_U16)(30.0f  + ((-2.4f)-log_ber)*10.0f/((-2.4f)-(-2.7f)));
                else if(log_ber  <= (-2.2f))
                    SQI = (MAPI_U16)(20.0f  + ((-2.2f)-log_ber)*10.0f/((-2.2f)-(-2.4f)));
                else if(log_ber  <= (-2.0f))
                    SQI = (MAPI_U16)(0.0f  + ((-2.0f)-log_ber)*10.0f/((-2.0f)-(-2.2f)));
                else
                    SQI = 0;
            }
            else if (Qam_mode == 2)//DMD_DVBC_QAM64
            {
                if(log_ber  <= (-5.4f))
                    SQI = 100;
                else if(log_ber  <= (-5.1f))
                    SQI = (MAPI_U16)(90.0f + ((-5.1f)-log_ber)*10.0f/((-5.1f)-(-5.4f)));
                else if(log_ber  <= (-4.9f))
                    SQI = (MAPI_U16)(80.0f + ((-4.9f)-log_ber)*10.0f/((-4.9f)-(-5.1f)));
                else if(log_ber  <= (-4.3f))
                    SQI = (MAPI_U16)(70.0f + ((-4.3f)-log_ber)*10.0f/((-4.3f)-(-4.9f)));
                else if(log_ber  <= (-3.7f))
                    SQI = (MAPI_U16)(60.0f + ((-3.7f)-log_ber)*10.0f/((-3.7f)-(-4.3f)));
                else if(log_ber  <= (-3.2f))
                    SQI = (MAPI_U16)(50.0f + ((-3.2f)-log_ber)*10.0f/((-3.2f)-(-3.7f)));
                else if(log_ber  <= (-2.9f))
                    SQI = (MAPI_U16)(40.0f + ((-2.9f)-log_ber)*10.0f/((-2.9f)-(-3.2f)));
                else if(log_ber  <= (-2.4f))
                    SQI = (MAPI_U16)(30.0f + ((-2.4f)-log_ber)*10.0f/((-2.4f)-(-2.9f)));
                else if(log_ber  <= (-2.2f))
                    SQI = (MAPI_U16)(20.0f + ((-2.2f)-log_ber)*10.0f/((-2.2f)-(-2.4f)));
                else if(log_ber  <= (-2.05f))
                    SQI = (MAPI_U16)(0.0f + ((-2.05f)-log_ber)*10.0f/((-2.05f)-(-2.2f)));
                else
                    SQI = 0;
            }
            else if (Qam_mode == 3)//DMD_DVBC_QAM128
            {
                if(log_ber  <= (-5.1f))
                    SQI = 100;
                else if(log_ber  <= (-4.9f))
                    SQI = (MAPI_U16)(90.0f + ((-4.9f)-log_ber)*10.0f/((-4.9f)-(-5.1f)));
                else if(log_ber  <= (-4.7f))
                    SQI = (MAPI_U16)(80.0f + ((-4.7f)-log_ber)*10.0f/((-4.7f)-(-4.9f)));
                else if(log_ber  <= (-4.1f))
                    SQI = (MAPI_U16)(70.0f + ((-4.1f)-log_ber)*10.0f/((-4.1f)-(-4.7f)));
                else if(log_ber  <= (-3.5f))
                    SQI = (MAPI_U16)(60.0f + ((-3.5f)-log_ber)*10.0f/((-3.5f)-(-4.1f)));
                else if(log_ber  <= (-3.1f))
                    SQI = (MAPI_U16)(50.0f + ((-3.1f)-log_ber)*10.0f/((-3.1f)-(-3.5f)));
                else if(log_ber  <= (-2.7f))
                    SQI = (MAPI_U16)(40.0f + ((-2.7f)-log_ber)*10.0f/((-2.7f)-(-3.1f)));
                else if(log_ber  <= (-2.5f))
                    SQI = (MAPI_U16)(30.0f + ((-2.5f)-log_ber)*10.0f/((-2.5f)-(-2.7f)));
                else if(log_ber  <= (-2.06f))
                    SQI = (MAPI_U16)(20.0f + ((-2.06f)-log_ber)*10.0f/((-2.06f)-(-2.5f)));
                else
                {
                    if (f_snr >= 27.2f)
                        SQI = 20;
                    else if (f_snr >= 25.1f)
                        SQI = (MAPI_U16)(0.0f + (f_snr - 25.1f)*20.0f/(27.2f-25.1f));
                    else
                        SQI = 0;
                }
            }
            else //256QAM
            {
                if(log_ber  <= (-4.8f))
                    SQI= 100;
                else if(log_ber  <= (-4.6f))
                    SQI = (MAPI_U16)(90.0f + ((-4.6f)-log_ber)*10.0f/((-4.6f)-(-4.8f)));
                else if(log_ber  <= (-4.4f))
                    SQI = (MAPI_U16)(80.0f + ((-4.4f)-log_ber)*10.0f/((-4.4f)-(-4.6f)));
                else if(log_ber  <= (-4.0f))
                    SQI = (MAPI_U16)(70.0f + ((-4.0f)-log_ber)*10.0f/((-4.0f)-(-4.4f)));
                else if(log_ber  <= (-3.5f))
                    SQI = (MAPI_U16)(60.0f + ((-3.5f)-log_ber)*10.0f/((-3.5f)-(-4.0f)));
                else if(log_ber  <= (-3.1f))
                    SQI = (MAPI_U16)(50.0f + ((-3.1f)-log_ber)*10.0f/((-3.1f)-(-3.5f)));
                else if(log_ber  <= (-2.7f))
                    SQI = (MAPI_U16)(40.0f + ((-2.7f)-log_ber)*10.0f/((-2.7f)-(-3.1f)));
                else if(log_ber  <= (-2.4f))
                    SQI = (MAPI_U16)(30.0f + ((-2.4f)-log_ber)*10.0f/((-2.4f)-(-2.7f)));
                else if(log_ber  <= (-2.06f))
                    SQI = (MAPI_U16)(20.0f + ((-2.06f)-log_ber)*10.0f/((-2.06f)-(-2.4f)));
                else
                {
                    if (f_snr >= 29.6f)
                        SQI = 20;
                    else if (f_snr >= 27.3f)
                        SQI = (MAPI_U16)(0.0f + (f_snr - 27.3f)*20.0f/(29.6f-27.3f));
                    else
                        SQI = 0;
                }
            }
#endif
            DBG_GET_SIGNAL(printf(">>> SQI = %d <<<\n", (int)SQI));

            return SQI;
        }
#if (ENABLE_S2)
        case E_DEVICE_DEMOD_DVB_S:
        {
            //GetSignalNoiseRatio
            MAPI_BOOL bRet=MAPI_TRUE;
            MAPI_U16 u16Address =0;
            MAPI_U8  u8Data =0;
            //NDA SNR
            // MAPI_U32 u32NDA_SNR_A =0;
            // MAPI_U32 u32NDA_SNR_AB =0;
            
            //NDA SNR
            // float NDA_SNR_A =0.0;
            // float NDA_SNR_AB =0.0;
            float NDA_SNR =0.0;
            float snr_poly =0.0;
            float Fixed_SNR =0.0;

            //GetSignalQuality
            MAPI_U16  u16Data = 0;
            MAPI_U8   u8Data2 = 0;
            MAPI_U8   _u8_DVBS2_CurrentConstellationLocal = 0, _u8_DVBS2_CurrentCodeRateLocal = 0;
            MAPI_U16  u16BitErrPeriod =0;
            MAPI_U32  u32BitErr =0;
        
            MAPI_U16  BCH_Eflag2_Window=0;
           // float fber =0.0;
            float __attribute__ ((unused)) log_ber = 0.0, f_snr = 0.0; //, ber_sqi = 0.0, cn_rel = 0.0
            double LDPCBer=0.0, eFlag_PER=0.0;
        
            S_SQI_TABLE *s2_sqi_ptr=NULL;
            MAPI_U8    s2_sqi_table_len = 0;
        

             // moving average
            static MAPI_U16  SQI_ARRAY[5]={255,255,255,255,255};
            static MAPI_U8    Index = 0;
            float  array_sum =0;
            float valid_count = 0;
            MAPI_U8 loop_index =0;
            MAPI_U16    u16_sqi = 0;
            static  float                         _f_DVBS2_CurrentSNR=0;
            static  MS_U16                        _u16_packetError=0;
            static  float                         _fPostBer=0;
        
        
            float fDVBS2_SQI_CNref[][11]=
            {    //0,   1,    2,    3,    4,    5,    6,    7,    8,    9,    10
            //old 1/2, 1/3,  2/3,  1/4,  3/4,  2/5,  3/5,  4/5,  5/6,   8/9,  9/10
              //  1/4, 1/3,  2/5,  1/2,  3/5,  2/3,  3/4,  4/5,  5/6,   8/9,  9/10
                {-1.6,-0.5,  0.5,  1.8,  3.0,  3.8,  4.8,  5.4,  5.9,   6.9,  7.2}, //QPSK
                {0.0,  0.0,  0.0,  0.0,  6.3,  7.4,  8.7,  0.0, 10.1,  11.4, 11.8}, //8PSK
            };
        
           
           S_SQI_TABLE S2_QPSK_CR23[] = 
            { 
                { 20,  10}, // CN 2.0 -> SQI 10
                { 25,  30},
                { 30,  50},
                { 36,  66},
                { 40,  74},
                { 45,  90},
                { 50, 100}, 
            };
        
           S_SQI_TABLE S2_QPSK_CR34[] = 
            { 
                { 20,  5},
                { 30, 15},
                { 35, 30},
                { 40, 50},
                { 46, 67},
                { 50, 74},
                { 60, 90}, 
            };
           
           S_SQI_TABLE S2_QPSK_CR56[] = 
            { 
                { 40,    5},
                { 45,  20},
                { 50,  46},
                { 55,  54},
                { 57,  70},
                { 60,  90},
                { 70, 100}, 
            };
        
           S_SQI_TABLE S2_8PSK_CR23[] = 
            { 
                { 50,   5},
                { 60, 20},
                { 65, 45},
                { 71, 66},
                { 80, 74},
                { 90, 90},
                {100, 100}, 
            };
        
           S_SQI_TABLE S2_8PSK_CR34[] = 
            { 
                { 70,   5},
                { 75, 20},
                { 80, 45},
                { 84, 66},
                { 90, 74},
                {100, 90},
                {110, 100}, 
            };
           
           S_SQI_TABLE S2_8PSK_CR56[] = 
            { 
                { 80,   5},
                { 85, 20},
                { 90, 45},
                { 95, 66},
                { 99, 74},
                {100, 90},
                {110, 100}, 
            };
        
           S_SQI_TABLE S_QPSK_CR23[] = 
            { 
                { 30,  10},
                { 40, 30},
                { 45, 47},
                { 50, 54},
                { 58, 67},
                { 60, 73},
                { 70, 90},
               { 80, 100},     
            };
        
           S_SQI_TABLE S_QPSK_CR34[] = 
            { 
                { 40,  10},
                { 50, 30},
                { 55, 47},
                { 60, 54},
                { 68, 67},
                { 70, 73},
                { 80, 90},
               { 90, 100},     
            };
           
           S_SQI_TABLE S_QPSK_CR56[] = 
            {
                { 50,  10},
                { 60, 30},
                { 65, 47},
                { 70, 54},
                { 78, 67},
                { 80, 73},
                { 90, 90},
               { 100, 100},
            };
        

            u16Address=0x0990;
            bRet&=ReadReg(u16Address, &u8Data);
            u8Data|=0x04;
            bRet&=WriteReg(u16Address, u8Data);
            
            u16Address=0x0B55;
            bRet&=ReadReg(u16Address, &u8Data);
            DBG_DEMOD_MSB(printf("u16Address=0x0B55 =%d\n",u8Data));
            if ((u8Data>=15) && (u8Data!=0xcd))
            {
                if (u8Data==15)//(_bDemodType==MAPI_FALSE)//S
                {
            
                    MAPI_U8 u8_i = 0;
                    MAPI_U16 u16_10snr = 0;
#if 1        
                    ReadDspReg(E_DMD_S2_MB_DUMMY_REG_11, &u8Data);
                    u16Data=u8Data;
                    ReadDspReg(E_DMD_S2_MB_DUMMY_REG_10, &u8Data);
                    u16Data = (u16Data<<8)|u8Data;
                    NDA_SNR = (float)u16Data/10.0;
                    u16_10snr = (MAPI_U16)(NDA_SNR*10.0+0.5);
#else
                    DTV_GetSNR();
                    u16_10snr = (MAPI_U16)(g_msb1240_fSNR*10);
#endif       
                    // u16_10snr = 60; 
                    u16Address = 0x1C84;
                    bRet &= ReadReg(u16Address, &u8Data);//INNER_PLSCDEC_DEBUG_OUT0
                    if ((u8Data&0x07)==0x01)  // CR2/3
                    {
                        s2_sqi_ptr=S_QPSK_CR23;
                        s2_sqi_table_len = sizeof(S_QPSK_CR23)/sizeof(S_SQI_TABLE);
                    }
                    else if ((u8Data&0x07)==0x02) //CR 3/4
                    {
                        s2_sqi_ptr=S_QPSK_CR34;
                        s2_sqi_table_len = sizeof(S_QPSK_CR34)/sizeof(S_SQI_TABLE);                
                    }
                    else
                    {
                        s2_sqi_ptr=S_QPSK_CR56;
                        s2_sqi_table_len = sizeof(S_QPSK_CR56)/sizeof(S_SQI_TABLE);   
                    }
            
                    if ((s2_sqi_table_len == 0) || (s2_sqi_ptr  == NULL))
                    {
                        u16_sqi = 0;
                    }
                    else
                    {
                        while(s2_sqi_ptr[u8_i].u16_x_10cn < u16_10snr)
                        {
                            u8_i++;
                            if(u8_i == s2_sqi_table_len) 
                                break;
                        }
            
                        if (u8_i == s2_sqi_table_len)
                        {
                            u16_sqi = (MAPI_U16)((float)(s2_sqi_ptr[u8_i-1].u8_y_sqi-s2_sqi_ptr[u8_i-2].u8_y_sqi)/(float)(s2_sqi_ptr[u8_i-1].u16_x_10cn-s2_sqi_ptr[u8_i-2].u16_x_10cn)*(float)(u16_10snr-s2_sqi_ptr[u8_i-2].u16_x_10cn)+s2_sqi_ptr[u8_i-2].u8_y_sqi);
                        }
                        else if (u8_i == 0)
                        {
                            u16_sqi = (MAPI_U16)((float)(s2_sqi_ptr[1].u8_y_sqi-s2_sqi_ptr[0].u8_y_sqi)/(float)(s2_sqi_ptr[1].u16_x_10cn-s2_sqi_ptr[0].u16_x_10cn)*(float)(u16_10snr-s2_sqi_ptr[0].u16_x_10cn)+s2_sqi_ptr[0].u8_y_sqi);
                            if (u16_sqi & 0x8000) 
                                u16_sqi = 0;
                        }
                        else
                        {
                            u16_sqi = (MAPI_U16)((float)(s2_sqi_ptr[u8_i].u8_y_sqi-s2_sqi_ptr[u8_i-1].u8_y_sqi)/(float)(s2_sqi_ptr[u8_i].u16_x_10cn-s2_sqi_ptr[u8_i-1].u16_x_10cn)*(float)(u16_10snr-s2_sqi_ptr[u8_i-1].u16_x_10cn)+s2_sqi_ptr[u8_i-1].u8_y_sqi);
                        }
            
                        if (u16_sqi > 100) 
                            u16_sqi = 100;
                    }
                }
                else    //S2
                {                    
#if 1                             
                    ReadDspReg(E_DMD_S2_MB_DUMMY_REG_11, &u8Data);
                    u16Data=u8Data;
                    ReadDspReg(E_DMD_S2_MB_DUMMY_REG_10, &u8Data);
                    u16Data = (u16Data<<8)|u8Data;
                    NDA_SNR = (float)u16Data/10.0;
#else
                    DTV_GetSNR();
                    NDA_SNR = g_msb1240_fSNR;                    
#endif             
                    // NDA_SNR = 6; 
                    //printf("[DVBS]: NDA_SNR ================================: %.1f\n", NDA_SNR);
                    _f_DVBS2_CurrentSNR = NDA_SNR;

                    //[DVBS/S2, QPSK/8PSK, 1/2~9/10 the same CN]
                    snr_poly = 0.0;     //use Polynomial curve fitting to fix SNR
                    snr_poly = 0.005261367463671*pow(NDA_SNR, 3)-0.116517828301214*pow(NDA_SNR, 2)+0.744836970505452*pow(NDA_SNR, 1)-0.86727609780167;
                    Fixed_SNR = NDA_SNR + snr_poly;
                    //printf("[DVBS]: NDA_SNR + snr_poly =====================: %.1f\n", Fixed_SNR);

                    if (Fixed_SNR < 17.0)
                        Fixed_SNR = Fixed_SNR;
                    else if ((Fixed_SNR < 20.0) && (Fixed_SNR >= 17.0))
                        Fixed_SNR = Fixed_SNR - 0.8;
                    else if ((Fixed_SNR < 22.5) && (Fixed_SNR >= 20.0))
                        Fixed_SNR = Fixed_SNR - 2.0;
                    else if ((Fixed_SNR < 27.0) && (Fixed_SNR >= 22.5))
                        Fixed_SNR = Fixed_SNR - 3.0;
                    else if ((Fixed_SNR < 29.0) && (Fixed_SNR >= 27.0))
                        Fixed_SNR = Fixed_SNR - 3.5;
                    else if (Fixed_SNR >= 29.0)
                        Fixed_SNR = Fixed_SNR - 3.0;


                    if (Fixed_SNR < 1.0)
                        Fixed_SNR = 1.0;
                    if (Fixed_SNR > 30.0)
                        Fixed_SNR = 30.0;
                    //printf("[DVBS]: SNR_Fixed_ =============================: %.1f\n", Fixed_SNR);

                    u16Address=0x1D04;
                    bRet&=ReadReg(u16Address, &u8Data);
                    u8Data|=0x01;
                    bRet&=WriteReg(u16Address, u8Data);
                    //BCH eflag2 sum
                    u16Address=0x264D;
                    bRet&=ReadReg(u16Address, &u8Data);
                    _u16_packetError=u8Data;
                    u16Address=0x264C;
                    bRet&=ReadReg(u16Address, &u8Data);
                    _u16_packetError=(_u16_packetError<<8)|u8Data;

                    //LDPC_Count_Window
                    u16Address=0x2625;
                    bRet&=ReadReg(u16Address, &u8Data);
                    u16BitErrPeriod=u8Data;
                    u16Address=0x2624;
                    bRet&=ReadReg(u16Address, &u8Data);
                    u16BitErrPeriod=(u16BitErrPeriod<<8)|u8Data;
                    //LDPC_BER_Count
                    u16Address=0x2667;
                    bRet&=ReadReg(u16Address, &u8Data);
                    u32BitErr=u8Data;
                    u16Address=0x2666;
                    bRet&=ReadReg(u16Address, &u8Data);
                    u32BitErr=(u32BitErr<<8)|u8Data;
                    u16Address=0x2665;
                    bRet&=ReadReg(u16Address, &u8Data);
                    u32BitErr=(u32BitErr<<8)|u8Data;
                    u16Address=0x2664;
                    bRet&=ReadReg(u16Address, &u8Data);
                    u32BitErr=(u32BitErr<<8)|u8Data;

                    u16Address=0x1D04;
                    bRet&=ReadReg(u16Address, &u8Data);
                    u8Data&=~(0x01);
                    bRet&=WriteReg(u16Address, u8Data);

                    if (u16BitErrPeriod == 0)
                        u16BitErrPeriod = 1;
                    /*//For Debug
                    u16Address = 0x264A;                //BCH EFLAG2_Window, mick
                    u16Data = 256*8;
                    bRet &= MSB131X_WriteReg2bytes(u16Address, u16Data);
                    */
                    u16Address = 0x264A;                //BCH EFLAG2_Window, mick

                    bRet &= ReadReg(u16Address + 0x0001, &u8Data);
                    u16Data = u8Data;
                    bRet &= ReadReg(u16Address, &u8Data);
                    u16Data = (u16Data<<8)|u8Data;

                    BCH_Eflag2_Window=u16Data;
                    //printf("E window %d\n", u16Data);
                    //fber = (float)u32BitErr/(u16BitErrPeriod*64800);          //PerLDPC BER

                    //New func                                                  //PostLDPC BER
                    eFlag_PER = (float)(_u16_packetError)/(float)(BCH_Eflag2_Window);
                    LDPCBer = 0.089267531133002*pow(eFlag_PER, 2) + 0.019640560289510*eFlag_PER + 0.0000000001;

                    //fber = LDPCBer;
                    _fPostBer = LDPCBer;
                    //fgPerBER = LDPCBer;

                    //_fPostBer=fber;
                    //SQI
                    if (bRet==MAPI_FALSE)
                    {
                        printf("MSB1240_DVBS_GetSignalQuality GetPostViterbiBer Fail!\n");
                        return FALSE;
                    }

                    u16Address = 0x1BD7;
                    bRet &= ReadReg(u16Address, &u8Data);
                    _u8_DVBS2_CurrentCodeRateLocal = (u8Data & 0x3C)>>2;

                    u16Address = 0x1BD7;
                    bRet &= ReadReg(u16Address, &u8Data); //INNER_PLSCDEC_DEBUG_OUT1
                    u16Address = 0x1BD6;
                    bRet &= ReadReg(u16Address, &u8Data2);//INNER_PLSCDEC_DEBUG_OUT0

                    if(((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x00))
                    {
                        _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_QPSK_MSB1240;
                    }
                    else if (((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x80))
                    {
                        _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_8PSK_MSB1240;//8PSK
                    }
                    log_ber = ( - 1) *log10f(1 / fber);
                    if (fber > 1.0E-1)
                        ber_sqi = (log10f(1.0f/fber))*20.0f + 8.0f;
                    else if (fber > 1.0E-3)
                        ber_sqi = (log10f(1.0f/fber))*20.0f + 30.0f;
                    else if(fber > 8.5E-7)
                        ber_sqi = (log10f(1.0f/fber))*20.0f - 30.0f;
                    else
                        ber_sqi = 100.0;

                    f_snr = Fixed_SNR;
                    cn_rel = (f_snr*1.1) - fDVBS2_SQI_CNref[_u8_DVBS2_CurrentConstellationLocal][_u8_DVBS2_CurrentCodeRateLocal];

                    //printf(" [DVBS2]fber = %f\n",fber);
                    //printf(" [DVBS2]f_snr = %f\n",f_snr);
                    //printf(" [DVBS2]cn_nordig_s2 = %f\n",fDVBS2_SQI_CNref[_u8_DVBS2_CurrentConstellationLocal][_u8_DVBS2_CurrentCodeRateLocal]);
                    //printf(" [DVBS2]cn_rel = %f\n",cn_rel);
                    //printf(" [DVBS2]ber_sqi = %f\n",ber_sqi);

                    if ((_u8_DVBS2_CurrentCodeRateLocal == 5)||(_u8_DVBS2_CurrentCodeRateLocal ==6)||(_u8_DVBS2_CurrentCodeRateLocal == 8))
                    {
                        MAPI_U8 u8_i = 0;
                        MAPI_U16 u16_10snr = (MAPI_U16)(NDA_SNR*10.0+0.5);                        
                        MAPI_U16 u16_symbolrate = 0;
                        MAPI_U8  u8_reg = 0;

                        bRet &= ReadReg(0x0b00+0x29*2+1, &u8_reg);
                        u16_symbolrate = u8_reg;
                        bRet &= ReadReg(0x0b00+0x29*2, &u8_reg);
                        u16_symbolrate = (u16_symbolrate<<8)|u8_reg;                

                        if (_u8_DVBS2_CurrentConstellationLocal == DEMOD_SAT_8PSK_MSB1240)
                        {
                            // added 0.3dB for 8PSK.
                            u16_10snr+=3;
                        }

                        if(u16_symbolrate < 22000) 
                        {
                            u16_10snr-=1;
                        }

                        switch(_u8_DVBS2_CurrentCodeRateLocal)
                        {  
                            case 5: // CR2/3
                            {
                                if (_u8_DVBS2_CurrentConstellationLocal == DEMOD_SAT_QPSK_MSB1240)
                                {
                                    s2_sqi_ptr = S2_QPSK_CR23;
                                    s2_sqi_table_len = sizeof(S2_QPSK_CR23)/sizeof(S_SQI_TABLE);
                                }
                                else if (_u8_DVBS2_CurrentConstellationLocal == DEMOD_SAT_8PSK_MSB1240)
                                {
                                    s2_sqi_ptr = S2_8PSK_CR23;
                                    s2_sqi_table_len = sizeof(S2_8PSK_CR23)/sizeof(S_SQI_TABLE);
                                }
                            }
                            break;
                            case 6: // CR 3/4
                            {
                                if (_u8_DVBS2_CurrentConstellationLocal == DEMOD_SAT_QPSK_MSB1240)
                                {
                                    s2_sqi_ptr = S2_QPSK_CR34;
                                    s2_sqi_table_len = sizeof(S2_QPSK_CR34)/sizeof(S_SQI_TABLE);
                                }
                                else if (_u8_DVBS2_CurrentConstellationLocal == DEMOD_SAT_8PSK_MSB1240)
                                {
                                    s2_sqi_ptr = S2_8PSK_CR34;
                                    s2_sqi_table_len = sizeof(S2_8PSK_CR34)/sizeof(S_SQI_TABLE);
                                }
                            }
                            break;
                            case 8: // CR 5/6
                            {
                                if (_u8_DVBS2_CurrentConstellationLocal == DEMOD_SAT_QPSK_MSB1240)
                                {
                                    s2_sqi_ptr = S2_QPSK_CR56;
                                    s2_sqi_table_len = sizeof(S2_QPSK_CR56)/sizeof(S_SQI_TABLE);
                                }
                                else if (_u8_DVBS2_CurrentConstellationLocal == DEMOD_SAT_8PSK_MSB1240)
                                {
                                    s2_sqi_ptr = S2_8PSK_CR56;
                                    s2_sqi_table_len = sizeof(S2_8PSK_CR56)/sizeof(S_SQI_TABLE);
                                }
                            }
                            break;
                            default:
                            break;
                        }

                        if ((s2_sqi_table_len == 0) || (s2_sqi_ptr  == NULL))
                        {
                            u16_sqi = 0;
                        }
                        else
                        {
                            while(s2_sqi_ptr[u8_i].u16_x_10cn < u16_10snr)
                            {
                                u8_i++;
                                if(u8_i == s2_sqi_table_len) 
                                    break;
                            }

                            if (u8_i == s2_sqi_table_len)
                            {
                                u16_sqi = (MAPI_U16)((float)(s2_sqi_ptr[u8_i-1].u8_y_sqi-s2_sqi_ptr[u8_i-2].u8_y_sqi)/(float)(s2_sqi_ptr[u8_i-1].u16_x_10cn-s2_sqi_ptr[u8_i-2].u16_x_10cn)*(float)(u16_10snr-s2_sqi_ptr[u8_i-2].u16_x_10cn)+s2_sqi_ptr[u8_i-2].u8_y_sqi);
                            }
                            else if (u8_i == 0)
                            {
                                u16_sqi = (MAPI_U16)((float)(s2_sqi_ptr[1].u8_y_sqi-s2_sqi_ptr[0].u8_y_sqi)/(float)(s2_sqi_ptr[1].u16_x_10cn-s2_sqi_ptr[0].u16_x_10cn)*(float)(u16_10snr-s2_sqi_ptr[0].u16_x_10cn)+s2_sqi_ptr[0].u8_y_sqi);
                                if (u16_sqi & 0x8000) 
                                u16_sqi = 0;
                            }
                            else
                            {
                                u16_sqi = (MAPI_U16)((float)(s2_sqi_ptr[u8_i].u8_y_sqi-s2_sqi_ptr[u8_i-1].u8_y_sqi)/(float)(s2_sqi_ptr[u8_i].u16_x_10cn-s2_sqi_ptr[u8_i-1].u16_x_10cn)*(float)(u16_10snr-s2_sqi_ptr[u8_i-1].u16_x_10cn)+s2_sqi_ptr[u8_i-1].u8_y_sqi);
                            }

                            if (u16_sqi > 100) 
                                u16_sqi = 100;
                        }
                    }       
                    else
                    {             
                        if (_u8_DVBS2_CurrentConstellationLocal == DEMOD_SAT_QPSK_MSB1240)
                        {
                            u16Address = 0x1BD7;
                            bRet &= ReadReg(u16Address, &u8Data);
                            if ((u8Data&0x3C) != 0x20)//not CR 5/6
                            {
                                if (cn_rel < -7.0f)
                                {
                                    SQI = 0;
                                }
                                else if (cn_rel < -2.0)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 4.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < -0.9)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < -0.5)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel + 1)/10.0 + 1.0));
                                }
                                else if (cn_rel < -0.2)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel + 8.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < 0.15)
                                {
                                    ber_sqi=58;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 2.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < 0.5)
                                {
                                    ber_sqi=80;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 4)/10.0 + 1.0));
                                }
                                else if (cn_rel < 1.5)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < 3)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3)/10.0 + 1.0));
                                }
                                else
                                {
                                    SQI = (MAPI_U16)ber_sqi;
                                }
                            }
                            else
                            {
                                if (cn_rel < -7.0f)
                                {
                                    SQI = 0;
                                }
                                else if (cn_rel < -0.6)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 7.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < -0.27)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel + 1)/10.0 + 1.0));
                                }
                                else if (cn_rel < 0.32)
                                {
                                    ber_sqi=50;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 1.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < 1.1)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < 1.5)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3)/10.0 + 1.0));
                                }
                                else if (cn_rel < 3)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3)/10.0 + 1.0));
                                }
                                else
                                {
                                    SQI = (MAPI_U16)ber_sqi;
                                }
                            }
                        }
                        else//8PSK
                        {
                            if ((u8Data&0x3C) != 0x20)
                            {
                                if (cn_rel < -7.0f)
                                {
                                    SQI = 0;
                                }
                                else if (cn_rel < -0.6)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 7)/10.0 + 1.0));
                                }
                                else if (cn_rel < -0.15)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel + 1)/10.0 + 1.0));
                                }
                                else if (cn_rel < 0.32)
                                {
                                    ber_sqi=50;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 1.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < 1.1)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < 1.7)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3.8)/10.0 + 1.0));
                                }
                                else if (cn_rel < 3)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3)/10.0 + 1.0));
                                }
                                else
                                {
                                    SQI = (MAPI_U16)ber_sqi;
                                }
                            }
                            else
                            {
                                // printf("S2_8PSK in CR5/6 \n");
                                if (cn_rel < -7.0f)
                                {
                                    SQI = 0;
                                }
                                else if (cn_rel < -1.0)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel -8)/10.0 + 1.0));
                                }
                                else if (cn_rel < -0.4)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel + 0.4)/10.0 + 1.0));
                                }
                                else if (cn_rel < -0.1)
                                {
                                    ber_sqi=27;
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel + 7)/10.0 + 1.0));
                                }
                                else if (cn_rel < 0.35)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3.0)/10.0 + 1.0));
                                }
                                else if (cn_rel < 0.9)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 2.5)/10.0 + 1.0));
                                    SQI=80;
                                }
                                else if (cn_rel < 1.5)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 3)/10.0 + 1.0));
                                }
                                else if (cn_rel < 1.55)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 4.5)/10.0 + 1.0));
                                }
                                else if (cn_rel < 3)
                                {
                                    SQI = (MAPI_U16)(ber_sqi*((cn_rel - 2.5)/10.0 + 1.0));
                                }
                                else
                               {
                                    SQI = (MAPI_U16)ber_sqi;
                               }
                            }
                        }
                        u16_sqi = (MAPI_U16)SQI;
                    }                
                }
            }
            else
            {
                u16_sqi = 0;
                return u16_sqi;
            }
            u16Address=0x0990;
            bRet&=ReadReg(u16Address, &u8Data);
            u8Data&=0xFB;
            bRet&=WriteReg(u16Address, u8Data);
        
            //moving average
            SQI_ARRAY[Index]=u16_sqi;
            Index = Index +1;
            if(Index>4)
                Index=0;
        
            array_sum =0;
            valid_count = 0;        
            for(loop_index=0;loop_index<5;loop_index++)
            {
                if( SQI_ARRAY[loop_index] != 255)
                {
                    array_sum +=SQI_ARRAY[loop_index];
                    valid_count +=1;
                }

            }

            if(valid_count>0)
                u16_sqi =array_sum /valid_count;  //(SQI_ARRAY[0]+SQI_ARRAY[1]+SQI_ARRAY[2]+SQI_ARRAY[3]+SQI_ARRAY[4])/5;
            else
                u16_sqi=0;

            //printf(">>>valid cout = %f \n",valid_count);
            
            DBG_DEMOD_MSB(printf(">>> SQI = %d <<<\n",u16_sqi));

            return u16_sqi;
        }
            break;
#endif

        default:
            break;
    }  // end of switch
    return 0;
#undef DVBT2_BER_TH_HY
}

MS_U32 DTV_GetSignalNoiseRatio(void)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16Address;
    MS_U32 u32Data;
    MS_U8  u8Data=0;//fix coverity 90922
    float  fvariance;
    float  log_snr;

    if (
    #if (ENABLE_S2)
        (MSB1240_DVBS_GetLock()==FALSE) &&
    #endif
        (DTV_DVB_T_GetLockStatus() == E_MSB_124X_DEMOD_UNLOCK)
       )
    {
        return 0;
    }
    u16Address=0x1B08;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data|=0x10;
    bRet&=WriteReg(u16Address, u8Data);

    u16Address=0x1BA5;
    bRet&=ReadReg(u16Address, &u8Data);
    u32Data=(u8Data&0x3F);

    u16Address=0x1BA4;
    bRet&=ReadReg(u16Address, &u8Data);
    u32Data=(u32Data<<8)|u8Data;

    u16Address=0x1BA3;
    bRet&=ReadReg(u16Address, &u8Data);
    u32Data=(u32Data<<8)|u8Data;

    u16Address=0x1BA2;
    bRet&=ReadReg(u16Address, &u8Data);
    u32Data=(u32Data<<8)|u8Data;

    u16Address=0x1B08;
    bRet&=ReadReg(u16Address, &u8Data);
    u8Data&=~(0x10);
    bRet&=WriteReg(u16Address, u8Data);
    if (bRet==FALSE)
    {
        return 0;
    }
    fvariance=(float)u32Data/0x20000000;
    if (fvariance==0)
        fvariance=1;
    log_snr=10*Log10Approx(1/fvariance);

    return (MS_U32)log_snr;
}

S_MSB_124X_RFAGC_SSI FT2125_RFAGC_SSI[] =
{
    {-19.40,    0x1B},
    {-20.40,    0x1C},
    {-21.40,    0x1D},
    {-22.40,    0x1E},
    {-23.40,    0x1F},
    {-24.40,    0x20},
    {-25.20,    0x21},
    {-26.60,    0x22},
    {-28.00,    0x23},
    {-29.20,    0x24},
    {-31.50,    0x25},
    {-32.75,    0x26},
    {-34.00,    0x27},
    {-35.25,    0x28},
    {-36.75,    0x29},
    {-38.50,    0x2a},
    {-40.00,    0x2b},
    {-42.00,    0x2c},
    {-43.50,    0x2d},
    {-44.80,    0x2e},
    {-46.20,    0x2f},
    {-47.40,    0x30},
    {-48.00,    0x31},
    {-48.40,    0x32},
    {-49.00,    0x33},
    {-99.00,    0x3f},
};

S_MSB_124X_IFAGC_SSI FT2125_IFAGC_SSI[] =
{
    {-48,   0x3A},
    {-49,   0x3B},
    {-50,   0x3C},
    {-51,   0x3E},
    {-52,   0x40},
    {-53,   0x43},
    {-54,   0x45},
    {-55,   0x47},
    {-56,   0x49},
    {-57,   0x4C},
    {-58,   0x4f},
    {-59,   0x51},
    {-60,   0x54},
    {-61,   0x56},
    {-62,   0x59},
    {-63,   0x5C},
    {-64,   0x5F},
    {-65,   0x62},
    {-66,   0x65},
    {-67,   0x69},
    {-68,   0x6E},
    {-69,   0x73},
    {-70,   0x78},
    {-71,   0x7F},
    {-72,   0x85},
    {-73,   0x8b},
    {-74,   0x9c},
    {-85,   0xc0},
    {-99,   0xFF},
};

S_SSI_PREF SsiPref[] =
{
    {_QPSK_1,  _CR1Y2_1, -81.0},
    {_QPSK_1,  _CR2Y3_1, -79.0},
    {_QPSK_1,  _CR3Y4_1, -78.0},
    {_QPSK_1,  _CR5Y6_1, -77.0},
    {_QPSK_1,  _CR7Y8_1, -76.0},

    {_16QAM_1, _CR1Y2_1, -75.0},
    {_16QAM_1, _CR2Y3_1, -73.0},
    {_16QAM_1, _CR3Y4_1, -72.0},
    {_16QAM_1, _CR5Y6_1, -71.0},
    {_16QAM_1, _CR7Y8_1, -70.0},

    {_64QAM_1, _CR1Y2_1, -69.0},
    {_64QAM_1, _CR2Y3_1, -68.0},
    {_64QAM_1, _CR3Y4_1, -66.0},
    {_64QAM_1, _CR5Y6_1, -65.0},
    {_64QAM_1, _CR7Y8_1, -64.0},
};
MAPI_BOOL MSB124X_Lock(COFDM_LOCK_STATUS eStatus)
{
    MAPI_U16        u16Address = 0;
    MAPI_U8         cData = 0;
    MAPI_U8         cBitMask = 0;
    MAPI_U8         use_dsp_reg = 0;
   // MAPI_U8         u8_tmp = 0;

    //printf(" MSB124X_Lock() ");

    // debug TS pad
    //ReadReg(0x0900+(0x2d)*2, &u8_tmp);
    //printf( "TS PAD (0xff:open) : 0x%x,\n",u8_tmp);
    // debug Serial mode
    //ReadReg(0x2a00+(0x20)*2, &u8_tmp);
    //printf( "check serial (0x0D:serial) : 0x%x,\n",u8_tmp);
    switch(eStatus)
    {
        case COFDM_P1_LOCK_123X:
            u16Address =  0x2482; //Pl lock,
            cBitMask = BIT3;
            break;

        case COFDM_P1_LOCK_HISTORY_123X:
            use_dsp_reg = 1;
            u16Address = E_T2_DVBT2_LOCK_HIS; //Pl ever lock,
            cBitMask = BIT5;
            break;

        case COFDM_L1_CRC_LOCK_123X:
            u16Address =  0x2741; //L1 CRC check,
            cBitMask = BIT5 | BIT6 | BIT7;
            break;

        case COFDM_FEC_LOCK:
            switch (m_enCurrentDemodulator_Type)
            {
                case E_DEVICE_DEMOD_DVB_T:
                    ReadReg(0x11E0, &cData);//addy update 0805
                    if (cData == 0x0B)
                       {
                        DBG_DEMOD_FLOW(printf("[msb1240] dvbt lock++\r\n"));
                        FECLock = MAPI_TRUE;
                        return MAPI_TRUE;
                        }
                    else
                        {
                        return MAPI_FALSE;
                        }
                    break;

                default:
                    return MAPI_FALSE;
            }
            break;

        case COFDM_TPS_LOCK:
            switch (m_enCurrentDemodulator_Type)
            {
                case E_DEVICE_DEMOD_DVB_T:
                    use_dsp_reg = 0;
                    u16Address =  0x0f22; //TPS Lock,ok
                    cBitMask = BIT1;
                    break;

                default:
                    return MAPI_FALSE;
            }
            break;
        default:
            return MAPI_FALSE;
    }
    if(!use_dsp_reg)
    {
        if(ReadReg(u16Address, &cData) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
    }
    else
    {
        if(ReadDspReg(u16Address, &cData) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
    }

    //printf("\r\n >>> MSB124X_Lock cData = %x, cBitMask=%x\n",cData,cBitMask);
    if((cData & cBitMask) == cBitMask)
    {
       DBG_DEMOD_FLOW(printf("[msb1240] dvbt TPS lock\r\n"));
       return MAPI_TRUE;
    }
    FECLock = MAPI_FALSE;
    return MAPI_FALSE;
}

MAPI_BOOL MSB124X_DVBC_Lock(QAM_LOCK_STATUS eStatus)
{

    MAPI_U8     u8Data = 0;
    MAPI_BOOL   bCheckPass=FALSE;
   DBG_DEMOD_FLOW( printf("%s,%d\r\n",__FUNCTION__,__LINE__));
    switch(eStatus)
    {
        case QAM_FEC_LOCK:
            ReadDspReg(C_lock_indicator, &u8Data);
                if( (u8Data & BIT7) == BIT7 )//FEC Lock Indicator
                {
                    bCheckPass = MAPI_TRUE;
                }
            break;
        case QAM_TR_LOCK:
            //ReadDspReg(C_lock_indicator, &u8Data);
            ReadReg(0x2200+(0x28)*2,&u8Data);
                if( (u8Data & BIT0) == BIT0 )//FEC Lock Indicator
                {
                    bCheckPass = MAPI_TRUE;
                }
            break;
        default:
            return MAPI_FALSE;
    }

    if(bCheckPass == MAPI_TRUE)
    {
        if(eStatus == QAM_FEC_LOCK)
        {
            DBG_DEMOD_FLOW(printf("[msb1240] dvbc lock++\r\n"));
            FECLock = MAPI_TRUE;
        }
        return MAPI_TRUE;
    }
    FECLock = MAPI_FALSE;
    return MAPI_FALSE;
}

MAPI_U16 DTV_GetSignalStrength(void)
{
#if((FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER)||(FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER))
    tmUnitSelect_t  sysUnit = 0;
    #if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
        pTDA182I4Object_t pObj = Null;
    #else
        ptmOM3912Object_t pObj = Null;
    #endif
    tmErrorCode_t   ErrorCode;
    MAPI_U8         PowerLevel_val = 0;
    float           PowerLevel = 0;
        MAPI_U8         ssi = 0;
    #if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
        iTDA182I4_GetInstance(sysUnit, &pObj);
    #else
        OM3912GetInstance(sysUnit, &pObj);
    #endif
    #if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
        ErrorCode = tmbslTDA182I4_GetPowerLevel(sysUnit, &PowerLevel_val);
    #else
        ErrorCode = tmbslTDA18273GetPowerLevel(pObj->tUnitTuner, &PowerLevel_val);
    #endif
    if(ErrorCode == TM_OK)
    {
        DBG_GET_SIGNAL(printf("TDA18273 Power Level value = %x\n", PowerLevel_val));
    }
    else
    {
        DBG_GET_SIGNAL(printf("Get Power Level value error %lx !!\n", (MAPI_U32)ErrorCode));
        return ssi;
    }

    PowerLevel = PowerLevel_val * 0.5 - 107;  // RSSI level in dBm

    if (PowerLevel < -95.0)
    {
        ssi = 0.0;
    }
    else if (PowerLevel < -80.0)
    {
        ssi = (MAPI_U8)((PowerLevel + 95.0)*(10.0/15.0));
    }
    else if (PowerLevel < -60.0)
    {
        ssi = (MAPI_U8)((PowerLevel + 80.0)*(80.0/20.0) + 10.0);
    }
    else if (PowerLevel < -50.0)
    {
        ssi = (MAPI_U8)((PowerLevel + 60.0)*(5.0/10.0) + 90.0);
    }
    else
    {
        ssi = 100.0;
    }

    return ssi;
#elif((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER) || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER))
    {
        MAPI_U16 ssi = 0;
        mdev_ATV_GetSignalStrength_Si2158(&ssi);
        return ssi;
    }
#else
    MAPI_U8    ssi = 0;
    double fPrel=0.0, fPinput=0.0;
    MAPI_U8  demodState = 0;
    MAPI_U8  temp_demodState = 0;
    //mapi_tuner *pTuner=NULL;
    float fRFLevel=200.0f;
    //MAPI_U16 if_agc_gain = 0;
    //status &= ReadReg(0x0990, &reg);
    //demodState = reg;

    if( (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER)\
       || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)  \
       || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)    \
       || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)    \
       || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)     \
       || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)     \
       || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)    \
       || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)  \
       || (FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
       )
        {
            mdev_GetSignalStrength(&fRFLevel);
        }
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
        {
           float fDVBT2_SSI_Pref[][6]=
                {
                    {-95.7, -94.4, -93.6, -92.6, -92.0, -91.5},
                    {-90.8, -89.1, -87.9, -86.7, -85.8, -85.2},
                    {-86.9, -84.6, -83.2, -81.4, -80.3, -79.7},
                    {-83.5, -80.4, -78.6, -76.0, -74.4, -73.3},
                };
                MAPI_U8 u8Modulation=0, u8CodeRate=0;
                static MAPI_U8 u8SignalEverStable=FALSE, u8ModulationStable=0, u8CodeRateStable=0;
                // cr, 3/5(1),  2/3(2), 3/4 (3)
                float fT2_SSI_formula[][12]=
                {
                    {1.0/5,  97.0,  3.0/2,  82.0, 16.0/5,  50.0, 29.0/10.0, 21.0, 18.0/15, 3.0, 3.0/5, 0.0}, // CR3/5
                    {2.0/3,  95.0,  9.0/5,  77.0, 17.0/5,  43.0, 14.0/5.0,  15.0, 13.0/15, 2.0, 2.0/5, 0.0}, // CR2/3
                    {1.0/2,  93.0, 19.0/10, 74.0, 31.0/10, 43.0, 22.0/10.0, 21.0, 18.0/15, 3.0, 3.0/5, 0.0}, // CR3/4
                };

                fPinput = fRFLevel;
                ReadReg(MSB1240_TOP_WR_DBG_90_ADDR, &temp_demodState);

                u8Modulation=DTV_DVB_T_GetSignalModulation();
                if (u8Modulation>=3) u8Modulation=3;

                u8CodeRate=DTV_DVB_T_GetSignalCodeRate();
                if (u8CodeRate>=5) u8CodeRate=5;

                ReadReg(MSB1240_TOP_WR_DBG_90_ADDR, &demodState);

                //Fix me, temp solution; demod doesn't lock, then use fref = -98 to compute SSI
                if ((temp_demodState >= 0x09)   &&   (demodState >= 0x09))
                {
                    fPrel=fPinput-fDVBT2_SSI_Pref[u8Modulation][u8CodeRate];
                    if (u8Modulation || u8CodeRate)
                    {
                        u8ModulationStable = u8Modulation;
                        u8CodeRateStable = u8CodeRate;
                        u8SignalEverStable = TRUE;
                    }
                }
                else if (u8SignalEverStable)
                {
                    fPrel=fPinput-fDVBT2_SSI_Pref[u8ModulationStable][u8CodeRateStable];
                }
                else
                {
                    fPrel=-20.0f; // for SSI to 0
                }

              if ( (u8ModulationStable == 3) //256qam
                    && (u8CodeRateStable > 0 && u8CodeRateStable < 4) // CR 3/5,2/3,3/4
                    )
                {
                    MAPI_U8 u8_x = u8CodeRateStable - 1;
                    float f_ssi = 0.0;

                    if (fPinput >= -50) f_ssi = fT2_SSI_formula[u8_x][0]*(fPinput + 50) + fT2_SSI_formula[u8_x][1];
                    else if (fPinput >= -60)  f_ssi = fT2_SSI_formula[u8_x][2]*(fPinput + 60) + fT2_SSI_formula[u8_x][3];
                    else if (fPinput >= -70)  f_ssi = fT2_SSI_formula[u8_x][4]*(fPinput + 70) + fT2_SSI_formula[u8_x][5];
                    else if (fPinput >= -80)  f_ssi = fT2_SSI_formula[u8_x][6]*(fPinput + 80) + fT2_SSI_formula[u8_x][7];
                    else if (fPinput >= -95)  f_ssi = fT2_SSI_formula[u8_x][8]*(fPinput + 95) + fT2_SSI_formula[u8_x][9];
                    else if (fPinput >= -100) f_ssi = fT2_SSI_formula[u8_x][10]*(fPinput + 100) + fT2_SSI_formula[u8_x][11];

                    if (f_ssi > 100) ssi = 100;
                    else if (f_ssi < 0) ssi = 0;
                    else ssi = (MAPI_U8)(f_ssi+0.5);

                    if (u8SignalEverStable == FALSE) ssi = 0;

                    DBG_GET_SIGNAL(printf("MSB1240 SSI... RF_level=%f, f_ssi=%f,ssi=%d,cr=%d,mod=%d\n",fPinput,f_ssi,ssi,u8CodeRateStable,u8ModulationStable);)
                }
                else
                {
                    if (fPrel<-15.0)
                    {
                        ssi = 0;
                    }
                    else if (fPrel<0.0)
                    {
                        ssi = (MAPI_U8)(((double)2.0/3)*(fPrel+15.0));
                    }
                    else if (fPrel<20.0)
                    {
                        ssi = 4*fPrel+10;
                    }
                    else if (fPrel<35.0)
                    {
                        ssi = (MAPI_U8)(((double)2.0/3)*(fPrel-20.0)+90);
                    }
                    else
                    {
                        ssi = 100;
                    }
                    DBG_GET_SIGNAL(printf("old ssi, ssi=%d, cr=%d, mod=%d\n",ssi,u8CodeRateStable,u8ModulationStable);)
                }

            DBG_GET_SIGNAL(printf(">>> SSI = %d <<<\n", (int)ssi));
        }
        break;
        case E_DEVICE_DEMOD_DVB_T:
        {
            float fDVBT_SSI_Pref[][5]=
            {
                {-93, -91, -90, -89, -88},
                {-87, -85, -84, -83, -82},
                {-82, -80, -78, -77, -76},
            };
            float   ch_power_db = 0.0f;
            float   ch_power_ref = 11.0f;
            float   ch_power_rel = 0.0f;
            MAPI_U8   tps_info_qam,tps_info_cr;


            ch_power_db = fRFLevel;// direct from tuner

            tps_info_qam = DTV_DVB_T_GetSignalModulation();// 0:QPSK, 1:16qam, 2:64qam
            tps_info_cr = DTV_DVB_T_GetSignalCodeRate();//0: 1/2; 1:2/3 ; 2:3/4; 3: 5/6; 4: 7/8

            if (tps_info_qam < 3 && tps_info_cr < 5)
                ch_power_ref =  fDVBT_SSI_Pref[tps_info_qam][tps_info_cr];

            if (ch_power_ref > 10.0f)
                ssi =0;
            else
            {
                ch_power_rel = ch_power_db - ch_power_ref;

                if (ch_power_rel<-15.0)
                {
                    ssi = 0;
                }
                else if (ch_power_rel<0.0)
                {
                    ssi = (MAPI_U8)(((double)2.0/3)*(ch_power_rel+15.0));
                }
                else if (ch_power_rel<20.0)
                {
                    ssi = 4*ch_power_rel+10;
                }
                else if (ch_power_rel<35.0)
                {
                    ssi = (MAPI_U8)(((double)2.0/3)*(ch_power_rel-20.0)+90);
                }
                else
                {
                    ssi = 100;
                }
            }
            DBG_GET_SIGNAL(printf(">>> SSI = %d <<<\n", (int)ssi));
        }
        break;
        case E_DEVICE_DEMOD_DVB_C:
        {
            float   ch_power_db=0.0f;
            float   ch_power_rel=0.0f;
            MAPI_U8     Qam_mode;



            ch_power_db = fRFLevel;// direct from tuner

            Qam_mode = DTV_DVB_C_GetSignalModulation();//0:16q,1:32q,2:64q,3:128q,4:256q

            if( (MAPI_U8)Qam_mode <= 4)//DMD_DVBC_QAM256
            {
                #if (D_CUSTOMER == formula_A)
                    ch_power_rel = ch_power_db - intern_dvb_c_qam_ref_1[(MAPI_U8)Qam_mode];
                #else
                    ch_power_rel = ch_power_db + intern_dvb_c_qam_ref[(MAPI_U8)Qam_mode];
                #endif
            }
            else
            {
                ch_power_rel = -100.0f;
            }
            #if (D_CUSTOMER == formula_A)
                if (ch_power_rel<-15.0)
                {
                    ssi = 0;
                }
                else if (ch_power_rel<0.0)
                {
                    ssi = (MAPI_U8)(((double)2.0/3)*(ch_power_rel+15.0));
                }
                else if (ch_power_rel<20.0)
                {
                    ssi = 4*ch_power_rel+10;
                }
                else if (ch_power_rel<35.0)
                {
                    ssi = (MAPI_U8)(((double)2.0/3)*(ch_power_rel-20.0)+90);
                }
                else
                {
                    ssi = 100;
                }
            #elif (D_CUSTOMER == formula_B)
                if(ch_power_rel <= -70.0f)
                {
                    ssi = 0;
                }
                else if (ch_power_rel <= -67.0f)
                {
                    ssi = (MAPI_U8)(0.0f + (ch_power_rel+70.0f)*3.0f/3.0f);
                }
                else if (ch_power_rel <= -62.0f)
                {
                    ssi = (MAPI_U8)(3.0f + (ch_power_rel+67.0f)*10.0f/5.0f);
                }
                else if (ch_power_rel <= -50.0f)
                {
                    ssi = (MAPI_U8)(13.0f + (ch_power_rel+62.0f)*60.0f/10.0f);
                }
                else if (ch_power_rel <= -40.0f)
                {
                    ssi = (MAPI_U8)(85.0f + (ch_power_rel+50.0f)*9.0f/10.0f);
                }
                else if (ch_power_rel <= -25.0f)
                {
                    ssi = (MAPI_U8)(94.0f + (ch_power_rel+40.0f)*6.0f/15.0f);
                }
                else
                {
                    ssi = 100;
                }

            #else // others...
                if(ch_power_rel <= -85.0f)
                {
                    ssi = 0;
                }
                else if (ch_power_rel <= -80.0f)
                {
                    ssi = (MAPI_U8)(0.0f + (ch_power_rel+85.0f)*10.0f/5.0f);
                }
                else if (ch_power_rel <= -75.0f)
                {
                    ssi = (MAPI_U8)(10.0f + (ch_power_rel+80.0f)*20.0f/5.0f);
                }
                else if (ch_power_rel <= -70.0f)
                {
                    ssi = (MAPI_U8)(30.0f + (ch_power_rel+75.0f)*30.0f/5.0f);
                }
                else if (ch_power_rel <= -65.0f)
                {
                    ssi = (MAPI_U8)(60.0f + (ch_power_rel+70.0f)*10.0f/5.0f);
                }
                else if (ch_power_rel <= -55.0f)
                {
                    ssi = (MAPI_U8)(70.0f + (ch_power_rel+65.0f)*20.0f/10.0f);
                }
                else if (ch_power_rel <= -45.0f)
                {
                    ssi = (MAPI_U8)(90.0f + (ch_power_rel+55.0f)*10.0f/10.0f);
                }
                else
                {
                    ssi = 100;
                }
            #endif
            DBG_GET_SIGNAL(printf(">>> SSI_CH_PWR(dB) = %f<<<\n",ch_power_db));
            DBG_GET_SIGNAL(printf(">>> SSI = %d <<<\n", (int)ssi));
        }
        break;

    #if(ENABLE_S2)
        case E_DEVICE_DEMOD_DVB_S:
        {
            //GetSignalStrength
            MAPI_BOOL bRet=MAPI_TRUE;
            MAPI_U16 u16Address =0;
            MAPI_U16 u16Data =0;
            MAPI_U8  u8Data =0;
            // MAPI_U8  u8Index =0;
            float    rf_level_dbm = 0.0;
            MAPI_U16 u16_ssi = 0;

            if (MSB1240_DVBS_GetLock()==MAPI_FALSE)//Demod unlock
            {
                return 0;
            }

            u16Address=0x3E26;//
            bRet&=ReadReg(u16Address, &u8Data);//
            u8Data=(u8Data&0xF0)|0x03;//
            bRet&=WriteReg(u16Address, u8Data);//
            u16Address=0x3E05;//
            bRet&=ReadReg(u16Address, &u8Data);//
            u8Data|=0x80;//
            bRet&=WriteReg(u16Address, u8Data);//

            u16Address=0x3E29;
            bRet&=ReadReg(u16Address, &u8Data);
            u16Data=u8Data;
            u16Address=0x3E28;
            bRet&=ReadReg(u16Address, &u8Data);
            u16Data=(u16Data<<8)|u8Data;
            //printf("===========================Tuner u16Data = %d\n",u16Data);
            u16Address=0x3E05;
            bRet&=ReadReg(u16Address, &u8Data);
            u8Data&=~(0x80);
            bRet&=WriteReg(u16Address, u8Data);
            if (bRet==MAPI_FALSE)
            {
                printf(("MSB1240_DVBS_GetSignalStrength fail!!! \n"));
                return 0;
            }

            //rf_level_dbm = MDrv_DVBS_Tuner_Get_RSSI(u16Data,1);
            rf_level_dbm = MDrv_DVBS_Tuner_Get_RSSI(u16Data);

            if (rf_level_dbm > 0) u16_ssi = 10; // -1dBm
            else u16_ssi = (MAPI_U16)(-1.0*rf_level_dbm*10.0);

            //GetPWR
            float  fCableLess;
            fCableLess = u16_ssi;

            //979MHz, 22Ms/s,DVB-S, QPSK¡B2/3 No Phose noise,No CN
            /*
                    //Add CN loss
                    printf("===========================fCableLess1 = %.2f\n",fCableLess);

                    if (fCableLess >= 160)
                        fCableLess = fCableLess + 10;
                    else if ((fCableLess < 160) && (fCableLess >= 140))
                        fCableLess = fCableLess;
                    else if ((fCableLess < 140) && (fCableLess >= 120))
                        fCableLess = fCableLess - 10;
                    else if ((fCableLess < 120) && (fCableLess >= 110))
                        fCableLess = fCableLess - 15;
                    else
                        fCableLess = fCableLess - 20;
                    */
            if (fCableLess >= 350)
                fCableLess = fCableLess - 35;
            else if ((fCableLess < 350) && (fCableLess >= 250))
                fCableLess = fCableLess - 25;
            else
                fCableLess = fCableLess - 5;

            if (fCableLess < 0)
                fCableLess = 0;
            if (fCableLess > 925)
                fCableLess = 925;

            //printf("===========================fCableLess2 = %.2f\n",fCableLess);
            fCableLess = (-1.0)*(fCableLess/10.0);

            //GetSignalBar
            MAPI_U8   u8Data2 = 0;
            MAPI_U8   _u8_DVBS2_CurrentConstellationLocal = 0, _u8_DVBS2_CurrentCodeRateLocal = 0;
            float   ch_power_db=0.0f, ch_power_db_rel=0.0f;

            ch_power_db = fCableLess;
            if (_bDemodType==MAPI_FALSE)//S
            {
                float fDVBS_SSI_Pref[]=
                {   //0,       1,       2,       3,       4
                    -78.9,   -77.15,  -76.14,  -75.19,  -74.57,//QPSK
                };
                u16Address = 0x1184;            //DVBSFEC_VITERBI_CODE_RATE
                bRet &= ReadReg(u16Address, &u8Data);
                _u8_DVBS2_CurrentCodeRateLocal = (u8Data & 0x07);
                ch_power_db_rel = ch_power_db - fDVBS_SSI_Pref[_u8_DVBS2_CurrentCodeRateLocal];

                //printf("[DVBS] power_ref_s1 = %f\n",fDVBS_SSI_Pref[_u8_DVBS2_CurrentCodeRateLocal]);
                //printf("[DVBS] ch_power_db_rel = %f\n",ch_power_db_rel);
            }
            else
            {
                float fDVBS2_SSI_Pref[][11]=
                {   //  0,    1,       2,       3,       4,       5,       6,       7,       8,        9,       10
                    //1/4,    1/3,     2/5,     1/2,     3/5,     2/3,     3/4,     4/5,     5/6,      8/9,     9/10
                    {-85.17, -84.08,  -83.15,  -81.86,  -80.63,  -79.77,  -78.84,  -78.19,  -77.69,   -76.68,  -76.46}, //QPSK
                    {   0.0,    0.0,     0.0,     0.0,  -77.36,  -76.24,  -74.95,     0.0,  -73.52,   -72.18,  -71.84}  //8PSK
                };

                u16Address = 0x24D7;
                bRet &= ReadReg(u16Address, &u8Data);
                _u8_DVBS2_CurrentCodeRateLocal = (u8Data & 0x3C)>>2;

                u16Address = 0x24D7;
                bRet &= ReadReg(u16Address, &u8Data);//INNER_PLSCDEC_DEBUG_OUT1
                u16Address = 0x24D6;
                bRet &= ReadReg(u16Address, &u8Data2);//INNER_PLSCDEC_DEBUG_OUT0

                if(((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x00))
                {
                    _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_QPSK_MSB1240;
                }
                else if (((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x80))
                {
                    _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_8PSK_MSB1240;//8PSK
                }

                ch_power_db_rel = ch_power_db - fDVBS2_SSI_Pref[_u8_DVBS2_CurrentConstellationLocal][_u8_DVBS2_CurrentCodeRateLocal];

                //printf("[DVBS2] power_ref_s2 = %f\n",fDVBS2_SSI_Pref[_u8_DVBS2_CurrentConstellationLocal][_u8_DVBS2_CurrentCodeRateLocal]);
                //printf("[DVBS2] ch_power_db_rel = %f\n",ch_power_db_rel);
                //printf("[DVBS2] _u8_DVBS2_CurrentConstellationLocal = %x ; _u8_DVBS2_CurrentCodeRateLocal=%x \n",_u8_DVBS2_CurrentConstellationLocal,_u8_DVBS2_CurrentCodeRateLocal);

            }
            if(ch_power_db_rel <= -15.0f)
                {ssi = 0;}
            else if (ch_power_db_rel <= 0.0f)
                {ssi = (MAPI_U16)(2.0f/3 * (ch_power_db_rel+15.0f));}
            else if (ch_power_db_rel <= 20.0f)
                {ssi = (MAPI_U16)(4.0f * ch_power_db_rel + 10.0f);}
            else if (ch_power_db_rel <= 35.0f)
                {ssi = (MAPI_U16)(2.0f/3 * (ch_power_db_rel-20.0f) + 90.0);}
            else
                {ssi = 100;}
            //printf(("MSB1240 DVBS Signal Bar %u\n", ssi));
        }
        break;
    #endif // ENABLE_S2

    default:
        ssi = 0;
        DBG_GET_SIGNAL(printf("Undefined!!!\n"));
        break;
    }
    return ssi;
#endif
}

MS_BOOL MDrv_CofdmDmd_GetPWR(MS_S32 *ps32Signal)
{
    MS_BOOL bRet=TRUE;
    *ps32Signal=(MS_S32)DTV_GetSignalStrength();
    *ps32Signal=(-1)*(*ps32Signal)/10;
    //PRINTE(("MSB124X Signal Level %d\n", *ps32Signal));
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_GetSNR(MS_U32 *pu32SNR)
{
    MS_BOOL bRet=TRUE;
    *pu32SNR=DTV_GetSignalNoiseRatio();
    //PRINTE(("MSB124X SNR %d\n", *pu32SNR));
    return bRet;
}

MAPI_BOOL DTV_Serial_Control(MAPI_BOOL bEnable)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8   status = MAPI_TRUE;
    MAPI_U8 u8Data;
    status = ReadReg(0x0900 + (0x2d * 2) , &u8Data) ;
    if(status != MAPI_FALSE && u8Data != 0x00)
    {
        if(bEnable){
            // Set TS[1]~TS[6] as GPIO_A3~GPIO_A8
            WriteReg(0x0900 + (0x2d * 2), 0x81);
            // Set GPIO_A3~GPIO_A8 as input
            WriteReg2bytes(0x0900+(0x61)*2, BIT3| BIT4|BIT5|BIT6|BIT7|BIT8);
        }
        else
        {
            // Set TS[0]~TS[7] as TS output
            WriteReg(0x0900 + (0x2d * 2), 0xFF);
        }
    }

    if (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
        T2_TS_SERIAL = (MAPI_U8)bEnable;
        //printf("T2_TS_SERIAL=%u\n", T2_TS_SERIAL);
    }
    else if (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T)
    {
        T_SERIAL_TS_VAL = (MAPI_U8)bEnable;
        MSB1240_DVBT_DSPREG_TABLE[3] = (MAPI_U8)bEnable;
        //printf("T_SERIAL_TS_VAL=%u\n", T_SERIAL_TS_VAL);
    }
    else if (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_C)
    {
        MSB1240_DVBC_DSPREG_TABLE[(MAPI_U8)C_config_ts_serial-(MAPI_U8)C_opmode_auto_scan_sym_rate] = (MAPI_U8)bEnable;
        //printf("DVBC_SERIAL=%u\n", bEnable);
    }

    return MAPI_TRUE;
}
//########################################  Private Function Implementation ################################
#if USE_SPI_LOAD_TO_SDRAM
MAPI_BOOL MDrv_SS_RIU_Write8(MAPI_U16 u16Addr, MAPI_U8 data)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MS_U8 Wdata[4];

    Wdata[0] = RIU_W1_CMD;
    Wdata[1] = u16Addr & 0xFF;
    Wdata[2] = (u16Addr >> 8) & 0xFF;
    Wdata[3] = data;
    //printf("MDrv_SS_RIU_Write\n");

    // Write operation
    MDrv_MSPI_SlaveEnable(TRUE);

    // send write address & data
    MDrv_MSPI_Write(Wdata,4);

    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;
}
MAPI_BOOL MDrv_SS_RIU_Read8(MAPI_U16 u16Addr, MAPI_U8 *pdata)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U8 Rdata[5];

    Rdata[0] = RIU_R1T_CMD;
    Rdata[1] = u16Addr & 0xFF;
    Rdata[2] = (u16Addr >> 8) & 0xFF;
    Rdata[3] = 0x00;
    //printf("MDrv_SS_RIU_Read8\n");

    MDrv_MSPI_SlaveEnable(TRUE);
    // send read command to read data
    MDrv_MSPI_Write(Rdata,4);
    // read operation
    //printf("Read Operation\n");
    MDrv_MSPI_Read(pdata, 1);
    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;

}

MAPI_BOOL MDrv_SS_RIU_Write16(MAPI_U16 u16Addr, MAPI_U16 u16Data)
{
    //DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL ret = TRUE;
    MS_U8 Wdata[5];

    Wdata[0] = RIU_W_CMD;
    Wdata[1] = u16Addr & 0xFF;
    Wdata[2] = (u16Addr >> 8) & 0xFF;
    Wdata[3] = (MAPI_U8)(u16Data&0x00ff);
    Wdata[4] = (MAPI_U8)((u16Data>>8)&0x00ff);
   //printf("MDrv_SS_RIU_Write\n");

    // Write operation
    MDrv_MSPI_SlaveEnable(TRUE);

    // send write address & data
    MDrv_MSPI_Write(Wdata,5);

    MDrv_MSPI_SlaveEnable(FALSE);

    //ret &= MDrv_SS_RIU_Write8(u16Addr, (MAPI_U8)(u16Data&0x00ff));
    //ret &= MDrv_SS_RIU_Write8(u16Addr + 0x0001, (MAPI_U8)((u16Data>>8)&0x00ff));
    return ret;
}

MAPI_BOOL MDrv_SS_MIU_Writes(MAPI_U32 u32Addr, MAPI_U8 *pdata, MAPI_U16 u16Size)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MS_U8 Wdata[5];

    Wdata[0] = MIU_W_CMD;
    Wdata[1] = u32Addr & 0xFF;
    Wdata[2] = (u32Addr >> 8) & 0xFF;
    Wdata[3] = (u32Addr >> 16)& 0xFF;
    Wdata[4] = (u32Addr >> 24);
    //printf("MDrv_SS_MIU_Writes\n");

    // Write operation
    MDrv_MSPI_SlaveEnable(TRUE);
    // send write address
    MDrv_MSPI_Write(Wdata,sizeof(Wdata));
    // send data
    MDrv_MSPI_Write(pdata,u16Size);
    MDrv_MSPI_SlaveEnable(FALSE);

    return bRet;
}

MAPI_BOOL MDrv_SS_MIU_Reads(MAPI_U32 u32Addr, MAPI_U8 *pdata, MAPI_U16 u16Size)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U8 Rdata[SPI_DEVICE_BUFFER_SIZE];
    MAPI_U16 dataLen, i, j=0;

    do
    {
        dataLen = (u16Size>16?16:u16Size);//(len>24?24:len);

        Rdata[0] = MIU_R_CMD;
        Rdata[1] = u32Addr & 0xFF;
        Rdata[2] = (u32Addr >> 8) & 0xFF;
        Rdata[3] = (u32Addr >> 16)& 0xFF;
        Rdata[4] = (u32Addr >> 24);
        Rdata[5] = dataLen+1;
        //printf("MDrv_SS_MIU_Reads, addr=0x%lx, dataLen=%d\n", u32Addr, dataLen);

        // send read command to read data
        MDrv_MSPI_SlaveEnable(TRUE);
        MDrv_MSPI_Write(Rdata,6);
        MDrv_MSPI_SlaveEnable(FALSE);

        // read operation
        Rdata[0] = MIU_ST_CMD;
        MDrv_MSPI_SlaveEnable(TRUE);
        MDrv_MSPI_Write(Rdata,1);
        //printf("Read Operation\n");
        MDrv_MSPI_Read(Rdata, dataLen+1);
        MDrv_MSPI_SlaveEnable(FALSE);

        if(Rdata[0] != 0x0A)
        {
            ERR_DEMOD_MSB(printf("MDrv_SS_MIU_Reads fail, status=0x%x\n", Rdata[0] ));
            return false;
        }

        for (i=1; i<dataLen+1; i++, j++)
        {
            pdata[j] = Rdata[i];
        }

        u16Size -= dataLen;
        u32Addr += dataLen;
    }while(u16Size);

    return bRet;
}
#endif

/************************************************************************************************
Subject:    Set demodulator type
Function:   SetCurrentDemodulatorType
Parmeter:   enDemodType
Return:     BOOLEAN :
*************************************************************************************************/

MAPI_BOOL SetCurrentDemodulatorType(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    if(enDemodType == m_enCurrentDemodulator_Type)
    {
        return MAPI_TRUE;
    }
#endif
    u32ChkScanTimeStart = MsOS_GetSystemTime();
    switch(enDemodType)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            m_enCurrentDemodulator_Type = enDemodType;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            m_enCurrentDemodulator_Type = enDemodType;
            break;
        case E_DEVICE_DEMOD_DVB_C://mick
            m_enCurrentDemodulator_Type = enDemodType;
            break;
        case E_DEVICE_DEMOD_DVB_S:
            m_enCurrentDemodulator_Type = enDemodType;
            break;
        default:
            return MAPI_FALSE;
    }
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    if (bPower_init_en != TRUE)
    {
        return MAPI_TRUE;
    }
#endif
    if (LoadDSPCode() == MAPI_FALSE)
    {

        ERR_DEMOD_MSB(printf(">>>>MSB1240:Fail\n"));
        return MAPI_FALSE;
    }
    else
    {
        DBG_DEMOD_MSB(printf(">>>MSB1240:OK\n"));
    }

    return MAPI_TRUE;
}


/************************************************************************************************
Subject:    Get PLP-ID Bit Map
Function:   DTV_GetPlpBitMap
Parmeter:   u32PlpBitMap
Return:     BOOLEAN :
Remark:     32 byte of data to show PLP-ID existense
            |00000000|00000000|...|00000000|00011111|11111111|
             byte31   byte30   ... byte2    byte1    byte0   => 256 bit in total
*************************************************************************************************/

MAPI_BOOL DTV_GetPlpBitMap(MAPI_U8* u8PlpBitMap)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL   status = MAPI_TRUE;
    MAPI_U8     u8Data = 0;
    MAPI_U8     indx = 0;
    MAPI_U8     u8_acc  = 0;

    status &= ReadDspReg(E_T2_L1_FLAG, &u8Data);     // check L1 ready
    if (u8Data != 0x30)
        return MAPI_FALSE;

    while(indx < 32)
    {
        status &= ReadDspReg(E_T2_PLP_ID_ARR+indx, &u8Data);
        u8PlpBitMap[indx] = u8Data;
        // printf("=========================>[GetPlpBitMap] u8PlpBitMap[%d] = 0x%x\n", indx, u8Data);
        indx++;
        if (u8_acc == 0)
        {
            u8_acc = u8Data;
        }
        DBG_DEMOD_MSB(printf("BitMap[%d]=0x%x, u8_acc=0x%x\n",indx,u8Data,u8_acc));
    }

    if (u8_acc == 0)
    {
        MAPI_U8 u8_plp_id = 0;
        MAPI_U8 u8_group_id = 0;
        MAPI_U8 u8_index = 0;
        MAPI_U8 u8_mod = 0;

        // SPLP with common case.
        // get current PLP_ID and GROUP_ID
        ReadReg(0x2700+0x45*2, &u8_plp_id);
        ReadReg(0x2700+0x46*2+1, &u8_group_id);

        u8_index = u8_plp_id/8;
        u8_mod = u8_plp_id%8;
        if (u8_index < 32)
        {
            u8PlpBitMap[u8_index]=(1<<u8_mod);
        }
        DBG_DEMOD_MSB(printf("[msb124x][SPLP with Common]Trigger!!!!!!!, plp_id=%d, group_id=%d, u8_index=%d,u8_mod=%d\n",u8_plp_id,u8_group_id,u8_index,u8_mod));
    }
    return status;
}

/************************************************************************************************
Subject:    Get GROUP_ID upon PLP_ID for MPLP mode
Function:   DTV_GetPlpGroupID
Parmeter:   u8PlpID, u8GroupID
Return:     BOOLEAN :
Remark:
*************************************************************************************************/

MAPI_BOOL DTV_GetPlpGroupID(MAPI_U8 u8PlpID, MAPI_U8* u8GroupID)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL   status = MAPI_TRUE;
    MAPI_U8 u8Data = 0;
    status &= ReadDspReg(E_T2_L1_FLAG, &u8Data);         // check L1 ready
    if (u8Data != 0x30)
    {
        ERR_DEMOD_MSB(printf("[msb1240]dvbt2 L1 not ready yet\n"));
        return MAPI_FALSE;
    }
    ReadDspReg(E_T2_DVBT2_LOCK_HIS, &u8Data);

    if ((u8Data & BIT7) == 0x00)
    {
        ERR_DEMOD_MSB(printf("[msb1240]dvbt2 is un-lock\n"));
        return MAPI_FALSE;
    }
    // assign PLP-ID value
    status &= WriteReg(0x2700+(0x78)*2, u8PlpID);
    status &= WriteReg(0x2700+(0x01)*2 + 1, 0x01);  // MEM_EN
    usleep(1000);
    status &= ReadReg(0x2700+(0x79)*2, u8GroupID);
    status &= WriteReg(0x2700+(0x01)*2 + 1, 0x00);  // ~MEM_EN
//  printf("=========================>[GetPlpGroupID] PlpID = %d, GroupID = %d\n", u8PlpID, *u8GroupID);

    return status;
}

/************************************************************************************************
Subject:    Select PLP_ID, GROUP_ID for MPLP mode
Function:   DTV_SetPlpGroupID
Parmeter:   u8PlpID, u8GroupID
Return:     BOOLEAN :
Remark:
*************************************************************************************************/

MAPI_BOOL DTV_SetPlpGroupID(MAPI_U8 u8PlpID, MAPI_U8 u8GroupID)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));

    MAPI_BOOL   status = MAPI_TRUE;
    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();

    g_msb1240_plp_id = u8PlpID;
    g_msb1240_group_id = u8GroupID;

    return status;
}

MS_BOOL DTV_Get_Current_Plp_Id(MS_U8 *plp_id)
{
    MS_BOOL  rbet = MAPI_TRUE;
    MS_U8    reg = 0;
    MS_U8    u8_plp_id = 0;

    rbet &= ReadDspReg((MAPI_U16)E_T2_PLP_ID, &reg);

    ReadReg(0x2700+0x45*2, &u8_plp_id);

    if (reg != u8_plp_id)
    {
        *plp_id = u8_plp_id;
        printf("[msb124x][SPLP with Common]Trigger!!!!!!!, dspregid=%d, regid=%d\n",reg,u8_plp_id);
    }
    else
    {
        *plp_id = reg;
    }

    DBG_DEMOD_MSB(printf("[msb124x]DTV_Get_Current_Plp_Id, plpid=%d\n",*plp_id));

    return rbet;
}

void Driving_Control(MAPI_BOOL bEnable)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8 u8Temp;
    ReadReg(0x0958, &u8Temp);
    if (bEnable)
    {
        u8Temp = 0xFF;
    }
    else
    {
        u8Temp = 0x00;
    }
    WriteReg(0x0958, u8Temp);

    ReadReg(0x0959, &u8Temp);
    if (bEnable)
    {
        u8Temp = u8Temp | 0x0F;
    }
    else
    {
        u8Temp = u8Temp &(~0x0F);
    }
    WriteReg(0x0959, u8Temp);
}


MAPI_U16 DTV_GetCellID(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8 id=0;
    MAPI_U8 status = MAPI_TRUE;
    MAPI_U16  cell_id  = 0;
    if (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
        return 0;
    }
    else if ((m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T)
            || (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_C))
    {
        status &= WriteReg(0x0ffe, 0x01);

        status &= ReadReg(0x0f2b, &id);
        cell_id = (MAPI_U16)id;

        status &= ReadReg(0x0f2a, &id);
        cell_id |= (MAPI_U16)id << 8;

        status &= WriteReg(0x0ffe, 0x00);

        if(status)
        {
            printf(" @MSB1240_GetCellId OK\n");
        }
        else
        {
            printf(" @MSB1240_GetCellId NG\n");
        }
    }
    return cell_id;
}
MAPI_BOOL DTV_IsHierarchyOn(void)
{
    return FALSE;
}
MAPI_BOOL DTV_DVB_T2_GetSignalTpsInfo(MS_U64 *TPS_Info)
{
    MS_BOOL bRet = TRUE;
    MS_U16    u16Data = 0;
    //const char* const cConStr[]={"qpsk","16qam","64qam","256qam"};
    //const char* const cCRStr[]={"1_2","3_5","2_3","3_4","4_5","5_6"};
    //const char* const cGIStr[]={"1_32","1_16","1_8","1_4","1_128","19_128","19_256"};
    //const char* const cFFTStr[]={"2k","8k","4k","1k","16k","32k","8k","32k"};
    //const char* const cPreAStr[]={"mixed","not_mixed"};
    //const char* const cS1SStr[]={"t2_siso","t2_miso","non_t2","reserved"};
    //const char* const cPPSStr[]={"PP1","PP2","PP3","PP4","PP5","PP6","PP7","PP8","reserved"};
    //const char* const cBWStr[]={"normal","extension"};
    //const char* const cPAPRStr[]={"none","ace","tr","tr_and_ace","reserved"};
    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_MODUL_MODE) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_MODUL_MODE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *TPS_Info = (MS_U64)(u16Data);
    DBG_SIGNAL_TPS(printf("Constellation:%s\n",cConStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_CODE_RATE) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_CODE_RATE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *TPS_Info |= (MS_U64)(u16Data<<3);
    DBG_SIGNAL_TPS(printf("Code Rate:%s\n",cCRStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_GUARD_INTERVAL) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_T2_GUARD_INTERVAL Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *TPS_Info |= (MS_U64)(u16Data<<6);
    DBG_SIGNAL_TPS(printf("GI:%s\n",cGIStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_FFT_VALUE) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_T2_FFT_VALUE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *TPS_Info |= (MS_U64)(u16Data<<9);
    DBG_SIGNAL_TPS(printf("FFT:%s\n",cFFTStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_PREAMBLE) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_PREAMBLE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x01;
    *TPS_Info |= (MS_U64)(u16Data<<12);
    DBG_SIGNAL_TPS(printf("Preamble:%s\n",cPreAStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_S1_SIGNALLING) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_S1_SIGNALLING Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x03;
    if(u16Data>2)
        u16Data = 3;
    *TPS_Info |= (MS_U64)(u16Data<<13);
    DBG_SIGNAL_TPS(printf("S1Signalling:%s\n",cS1SStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_PILOT_PATTERN) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_PILOT_PATTERN Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x0F;
    if(u16Data>7)
        u16Data = 8;
    *TPS_Info |= (MS_U64)(u16Data<<15);
    DBG_SIGNAL_TPS(printf("PilotPattern:%s\n",cPPSStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_BW_EXT) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_BW_EXT Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x01;
    *TPS_Info |= (MS_U64)(u16Data<<19);
    DBG_SIGNAL_TPS(printf("BW EXT:%s\n",cBWStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_PAPR_REDUCTION) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_PAPR_REDUCTION Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    if(u16Data>3)
        u16Data = 4;
    *TPS_Info |= (MS_U64)(u16Data<<20);
    DBG_SIGNAL_TPS(printf("PAPR:%s\n",cPAPRStr[u16Data]));

    if(DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_OFDM_SYMBOLS_PER_FRAME) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_OFDM_SYMBOLS_PER_FRAME Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0xFFF;
    *TPS_Info |= (MS_U64)(u16Data<<23);
    DBG_SIGNAL_TPS(printf("OFDM Symbols:%u\n",u16Data));

    return bRet;
}

MAPI_BOOL DTV_GetSNR_F(float *fSNR)
{
    DTV_GetSNR();
    *fSNR = g_msb1240_fSNR;
    return TRUE;
}

MAPI_BOOL msb1240_flash_mode_en(void)
{
    MAPI_BOOL  retb = TRUE;
    MAPI_U8    data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};
    MAPI_U8    u8MsbData[6] = {0};
    MAPI_U8    ch_num  = 3;
    MAPI_U8    u8Data  = 0;
    MAPI_U16   u16Addr = 0;
    MAPI_U8    retry_num = MSB1240_MAX_FLASH_ON_RETRY_NUM;

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]msb1240_flash_mode_en\n"));

    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);

    do
    {
        if (retry_num != MSB1240_MAX_FLASH_ON_RETRY_NUM)
        {
            ERR_DEMOD_MSB(printf("[msb1240][error]flash mode en fail.....retry=%d\n",retry_num);)
        }
        // retb = TRUE;
        // password
        // 8'hb2(SRID)->8,h53(PWD1)->8,h45(PWD2)->8,h52(PWD3)->8,h44(PWD4)->8,h42(PWD5)
        data[0] = 0x53;
        retb &= iptr->WriteBytes(0, NULL, 5, data);

        // 8'hb2(SRID)->8,h71(CMD)  //TV.n_iic_
        data[0] = 0x71;
        retb &= iptr->WriteBytes(0, NULL, 1, data);

        // 8'hb2(SRID)->8,h81(CMD)  //TV.n_iic_sel_b0
        data[0] = ((ch_num & 0x01) != 0)? 0x81 : 0x80;
        retb &= iptr->WriteBytes(0, NULL, 1, data);

        // 8'hb2(SRID)->8,h83(CMD)  //TV.n_iic_sel_b1
        data[0] = ((ch_num & 0x02) != 0)? 0x83 : 0x82;
        retb &= iptr->WriteBytes(0, NULL, 1, data);

        // 8'hb2(SRID)->8,h84(CMD)  //TV.n_iic_sel_b2
        data[0] = ((ch_num & 0x04) != 0)? 0x85 : 0x84;
        retb &= iptr->WriteBytes(0, NULL, 1, data);

        // 8'hb2(SRID)->8,h53(CMD)  //TV.n_iic_ad_byte_en2, 32bit read/write
        data[0] = 0x53;
        retb &= iptr->WriteBytes(0, NULL, 1, data);

        // 8'hb2(SRID)->8,h7f(CMD)  //TV.n_iic_sel_use_cfg
        data[0] = 0x7f;
        retb &= iptr->WriteBytes(0, NULL, 1, data);

    /*
        // 8'hb2(SRID)->8,h35(CMD)  //TV.n_iic_use
        data[0] = 0x35;
        retb &= iptr->WriteBytes(0, NULL, 1, data);

        // 8'hb2(SRID)->8,h71(CMD)  //TV.n_iic_Re-shape
        data[0] = 0x71;
        retb &= iptr->WriteBytes(0, NULL, 1, data);
    */
        retb = TRUE;

        // confirm first, 0x99 and 0xaa.
        // beg read register
        u16Addr = 0x0900+(0x4f<<1);
        u8Data = 0x0;

        u8MsbData[0] = 0x10;
        u8MsbData[1] = 0x00;
        u8MsbData[2] = 0x00;
        u8MsbData[3] = (u16Addr >> 8) &0xff;
        u8MsbData[4] = u16Addr &0xff;

        u8MsbData[0] = 0x35;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);

        u8MsbData[0] = 0x10;
        retb &= iptr->WriteBytes(0, NULL, 5, u8MsbData);
        retb &= iptr->ReadBytes(0, NULL, 1, &u8Data);

        u8MsbData[0] = 0x34;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
        // end read register

        if ((u8Data == 0x99) || (u8Data == 0xaa))
        {
            ERR_DEMOD_MSB(printf("[msb1240][warning]flash is already on....\n");)
            break;
        }
        // flash mode enable.
        // beg read register
        u16Addr = 0x0900+(0x28<<1)+1;
        u8Data = 0x0;

        u8MsbData[0] = 0x10;
        u8MsbData[1] = 0x00;
        u8MsbData[2] = 0x00;
        u8MsbData[3] = (u16Addr >> 8) &0xff;
        u8MsbData[4] = u16Addr &0xff;

        u8MsbData[0] = 0x35;

        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);



        u8MsbData[0] = 0x10;
        retb &= iptr->WriteBytes(0, NULL, 5, u8MsbData);
        retb &= iptr->ReadBytes(0, NULL, 1, &u8Data);

        u8MsbData[0] = 0x34;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
        // end read register

        // beg write register
        u16Addr = 0x0900+(0x28<<1) + 1;
        u8Data &= (0xff-0x01);

        u8MsbData[0] = 0x10;
        u8MsbData[1] = 0x00;
        u8MsbData[2] = 0x00;
        u8MsbData[3] = (u16Addr >> 8) &0xff;
        u8MsbData[4] = u16Addr &0xff;
        u8MsbData[5] = u8Data;

        u8MsbData[0] = 0x35;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);

        u8MsbData[0] = 0x10;
        retb &= iptr->WriteBytes(0, NULL, 6, u8MsbData);

        u8MsbData[0] = 0x34;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
        // end write register

        // beg write register
        u16Addr = 0x0900+(0x06<<1);
        u8Data = 0x10;

        u8MsbData[0] = 0x10;
        u8MsbData[1] = 0x00;
        u8MsbData[2] = 0x00;
        u8MsbData[3] = (u16Addr >> 8) &0xff;
        u8MsbData[4] = u16Addr &0xff;
        u8MsbData[5] = u8Data;

        u8MsbData[0] = 0x35;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);

        u8MsbData[0] = 0x10;
        retb &= iptr->WriteBytes(0, NULL, 6, u8MsbData);

        u8MsbData[0] = 0x34;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
        // end write register

        // beg write register

        u16Addr = 0x0900+(0x07<<1);
        u8Data = 0x10;

        u8MsbData[0] = 0x10;
        u8MsbData[1] = 0x00;
        u8MsbData[2] = 0x00;
        u8MsbData[3] = (u16Addr >> 8) &0xff;
        u8MsbData[4] = u16Addr &0xff;
        u8MsbData[5] = u8Data;

        u8MsbData[0] = 0x35;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);

        u8MsbData[0] = 0x10;
        retb &= iptr->WriteBytes(0, NULL, 6, u8MsbData);

        u8MsbData[0] = 0x34;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
    }while( (retb == FALSE) && (retry_num-- != 0));
    // end write register

    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]msb1240_flash_mode_en,retb=%d\n",retb));

    return retb;
}

MAPI_BOOL msb1240_flash_boot_ready_waiting(MAPI_U8 *ptimeout)
{
    MAPI_BOOL  retb = TRUE;
    MAPI_U8    u8MsbData[6] = {0};
    MAPI_U8    u8Data  = 0;
    MAPI_U16   u16Addr = 0;
    MAPI_U8    u8_timeout = 0;
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][beg]msb1240_flash_boot_ready_waiting\n"));
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);

    // wait for flash->dram ready.
    // read register

    u16Addr = 0x0900+(0x4f<<1);
    u8Data = 0x0;

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;
    u8_timeout = 0xff;
    while( (u8Data != 0x99) && (u8Data != 0xaa) && (u8_timeout-->0))
    {
        u8MsbData[0] = 0x35;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);

        u8MsbData[0] = 0x10;
        retb &= iptr->WriteBytes(0, NULL, 5, u8MsbData);
        retb &= iptr->ReadBytes(0, NULL, 1, &u8Data);

        u8MsbData[0] = 0x34;
        retb &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
        // 10ms
        usleep(1000*10);
    }
    // end read register
    *ptimeout = 0;
    if (u8_timeout == 0x00)
    {
        *ptimeout = 1;
        ERR_DEMOD_MSB(printf("[msb1240][error]msb1240_flash_boot_ready_waiting, timeout....\n");)
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb1240][end]msb1240_flash_boot_ready_waiting, t=%d\n",u8_timeout));
    return retb;
}

MAPI_U16 MSB1231_Lock(COFDM_LOCK_STATUS_123X eStatus)
{
    MAPI_U16        u16Address = 0;
    MAPI_U8         cData = 0;
    MAPI_U8         cBitMask = 0;
    MAPI_U8         use_dsp_reg = 0;
    //printf("\r\n >>> MSB1233C_Lock eStatus = %x\n",eStatus);
    switch(eStatus)
    {
        case COFDM_P1_LOCK_123X:
            u16Address =  0x2482; //Pl lock,
            cBitMask = BIT3;
            break;

        case COFDM_P1_LOCK_HISTORY_123X:
            use_dsp_reg = 1;
            u16Address = E_T2_DVBT2_LOCK_HIS; //Pl ever lock,
            cBitMask = BIT5;
            break;

        case COFDM_L1_CRC_LOCK_123X:
            u16Address =  0x2741; //L1 CRC check,
            cBitMask = BIT5 | BIT6 | BIT7;
            break;
        case COFDM_FEC_LOCK_T2_123X:
            use_dsp_reg = 1;
            u16Address =  E_T2_DVBT2_LOCK_HIS; //FEC lock,
            cBitMask = BIT7;
            break;

        default:
            return MAPI_FALSE;
    }
    if(!use_dsp_reg)
    {
        if(ReadReg(u16Address, &cData) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
    }
    else
    {
        if(ReadDspReg(u16Address, &cData) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
    }
    //printf("\r\n >>> MSB1233C_Lock cData = %x\n",cData);
    if((cData & cBitMask) == cBitMask)
    {
        if (eStatus == COFDM_FEC_LOCK_T2_123X)
        {
            printf(" [msb1240] dvbt2 lock++ \n");
            FECLock = MAPI_TRUE;
        }
        return MAPI_TRUE;
    }
    FECLock = MAPI_FALSE;
    return MAPI_FALSE;
}

void DTV_ControlAGCOutput(BOOLEAN bEnable)
{
    if (bEnable == TRUE)
        MSB124X_ExtendCmd(0x80,1,0,NULL);
    else
        MSB124X_ExtendCmd(0x80,0,0,NULL);
}


#if (SUPPORT_UNICABLE)
#define MAX_IF_FREQ              2150
#define MIN_IF_FREQ               950
#define MAX_SYM_RATE             45000
#define MIN_SYM_RATE             1
const MS_U8 u8BankMap[2][2][2] =
{
  //     {{0, 2}, {1, 3}}, //PosA, Low/High Band, Vertical/Horizontal Polarity
    {{2, 0}, {3, 1}},//PosA, Low/High Band, Horizontal/Vertical Polarity
    {{4, 6}, {5, 7}}  //PosB, Low/High Band, Vertical/Horizontal Polarity
};
MS_BOOL FrontEnd_DVBS2_Set(MS_U32 u32Frequency, MS_U32 u32SymRate, MS_U8 u8Polarity , MS_SAT_PARAM *stSatInfo)
{
    MS_BOOL bIsHiLOF = FALSE;
    S32 s32Freq = 0;
    CofdmDMD_Param unidmdpara;
    //MW_DTV_FRONTEND_FUNCTION("MW_DTV_FrontEnd_DVBS::Set6(%ld,%ld,%d) \n", u32Frequency, u32SymRate, u8Polarity);
    //ASSERT(u8Polarity<=1);
    //u32Frequency = 11053;
    // calc Mid Freq & LNB control(22K on/off)
    if (stSatInfo->u16LoLOF == stSatInfo->u16HiLOF)
    {
        s32Freq  = u32Frequency;
        s32Freq -= stSatInfo->u16LoLOF ;
        if(s32Freq < 0)
        {
            s32Freq = -s32Freq;
        }
        bIsHiLOF = FALSE;
    }
    else // 2LOF
    {
        if(stSatInfo->u16LoLOF < MAX_C_LOF_FREQ) // c band
        {
            s32Freq  = u32Frequency;
            if(u8Polarity == 1) //H ---> use low LOF
            {
                bIsHiLOF = FALSE;
                s32Freq = abs(stSatInfo->u16LoLOF - s32Freq);
            }
            else   //V --->use high LOF
            {
                bIsHiLOF = TRUE;
                s32Freq =  abs(stSatInfo->u16HiLOF - s32Freq) ;
            }
        }
        else //Ku band
        {
            U32 u32MidFreq;
            S32 s32Offset = 0;
            s32Freq  = u32Frequency;
            u32MidFreq = abs(s32Freq - stSatInfo->u16LoLOF) ;
            s32Offset = stSatInfo->u16LoLOF + MAX_IF_FREQ - stSatInfo->u16HiLOF - MIN_IF_FREQ;
            if(s32Offset < 0)
            {
                s32Offset = 0;
            }
            else
            {
                s32Offset /= 2;
            }
            if(u32MidFreq <= (U32)(MAX_IF_FREQ - s32Offset))
            {
                bIsHiLOF = FALSE;
                s32Freq = u32MidFreq;
            }
            else
            {
                bIsHiLOF = TRUE;
                s32Freq = abs(s32Freq - stSatInfo->u16HiLOF) ;
            }
        }
    }

    if(s32Freq < MIN_IF_FREQ || s32Freq > MAX_IF_FREQ)
    {
        printf("Invalid Freq = %ld\n", s32Freq);
        s32Freq = MIN_IF_FREQ;
    }
    if(u32SymRate > MAX_SYM_RATE || u32SymRate < MIN_SYM_RATE)
    {
        printf("Invalid u32SymRate = %ld\n", u32SymRate*1000);
        u32SymRate = 1000;
    }

    {
        U16 u16TuneWord = ((s32Freq + stSatInfo->u16IFreq)/4) - 350;

        printf("\r\n (%s,%d),FrontEnd_DVBS2_Set [%d] u16SymbolRate [%d], u16TuneWord = %ld\n",__FUNCTION__,__LINE__,u32Frequency, u32SymRate,u16TuneWord);
        ODU_ChChg(stSatInfo->u8ChannelId, u8BankMap[0][bIsHiLOF][u8Polarity], u16TuneWord,0);

        printf("[Gaven],set();[Unicable] [(Freq = %ld + IFreq = %d)/4 - 350] = (TuneWord = %d)\n",s32Freq, stSatInfo->u16IFreq, u16TuneWord);
        printf("[Gaven],set();[Unicable] ChannelId = %d, u32SymRate = %ld, u8Polarity = %d, Bank = %d\n",stSatInfo->u8ChannelId, u32SymRate*1000, u8Polarity, u8BankMap[0][bIsHiLOF][u8Polarity]);
        unidmdpara.u32TunerFreq=stSatInfo->u16IFreq;
        unidmdpara.u32SymbolRate=u32SymRate*1000;
        printf("[Gaven],set();[Unicable] s32Freq = %ld,u32TunerFreq = %ld, u32SymRate = %ld\n",s32Freq,unidmdpara.u32TunerFreq,unidmdpara.u32SymbolRate);
        if (MDrv_CofdmDmd_Restart(&unidmdpara) == FALSE)
        {
                return FALSE;
        }
    }
    return TRUE;
}
#endif
#if 1
ST_MAPI_DEMODULATOR_FUN stMapiDemodulatorFun;
ST_MAPI_DEMODULATOR_FUN* DeviceDemodCreate(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    memset(&stMapiDemodulatorFun, 0, sizeof(ST_MAPI_DEMODULATOR_FUN));

    //Public:Common
//    stMapiDemodulatorFun.Connect = Connect;
    stMapiDemodulatorFun.Connect = Demod_MSB124X_Connect;

    stMapiDemodulatorFun.Disconnect = Disconnect;
    stMapiDemodulatorFun.Reset = Reset;
    stMapiDemodulatorFun.IIC_Bypass_Mode = IIC_Bypass_Mode;
    stMapiDemodulatorFun.Power_On_Initialization = Power_On_Initialization;
    stMapiDemodulatorFun.Set_PowerOn = Set_PowerOn;
    stMapiDemodulatorFun.Set_PowerOff = Set_PowerOff;
    stMapiDemodulatorFun.Active = Active;
    stMapiDemodulatorFun.GetCurrentDemodulatorType = GetCurrentDemodulatorType;
    stMapiDemodulatorFun.SetCurrentDemodulatorType = SetCurrentDemodulatorType;
    stMapiDemodulatorFun.ExtendCmd = MSB124X_ExtendCmd;

    //Public:DTV
    stMapiDemodulatorFun.DTV_SetFrequency = DTV_SetFrequency;
    stMapiDemodulatorFun.DTV_GetSNR = DTV_GetSNR;
    stMapiDemodulatorFun.DTV_GetBER = DTV_GetBER;
    // stMapiDemodulatorFun.DTV_GetPacketErr = DTV_GetPacketErr;
    stMapiDemodulatorFun.DTV_GetSignalQuality = DTV_GetSignalQuality;
    stMapiDemodulatorFun.DTV_GetPostBER = MSB124X_DTV_GetPostBER;
    stMapiDemodulatorFun.DTV_GetSignalStrength = DTV_GetSignalStrength;
    stMapiDemodulatorFun.DTV_GetCellID = DTV_GetCellID;
    stMapiDemodulatorFun.DTV_Serial_Control = DTV_Serial_Control;
    stMapiDemodulatorFun.DTV_IsHierarchyOn = DTV_IsHierarchyOn;

    //Public:DTV-DVB-T
    stMapiDemodulatorFun.DTV_DVB_T_GetLockStatus = DTV_DVB_T_GetLockStatus;

    //Public:DTV-DVB-T2
    stMapiDemodulatorFun.DTV_DVB_T2_GetPlpBitMap = DTV_GetPlpBitMap;
    stMapiDemodulatorFun.DTV_DVB_T2_GetPlpGroupID = DTV_GetPlpGroupID;
    stMapiDemodulatorFun.DTV_DVB_T2_SetPlpGroupID = DTV_SetPlpGroupID;
    stMapiDemodulatorFun.DTV_DVB_T2_GetCurrentPlpId = DTV_Get_Current_Plp_Id;

    //custom
    stMapiDemodulatorFun.DTV_GetSNR_F = DTV_GetSNR_F;
    stMapiDemodulatorFun.bMSB123X_Ready = FALSE;
    stMapiDemodulatorFun.DTV_DVB_T2_GetSignalTpsInfo = DTV_DVB_T2_GetSignalTpsInfo;
    stMapiDemodulatorFun.DTV_GetLock = MSB1231_Lock;
    return &stMapiDemodulatorFun;
}
#endif

#endif // MSB124X_C
