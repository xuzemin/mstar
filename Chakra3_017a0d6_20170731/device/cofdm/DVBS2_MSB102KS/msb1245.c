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
#include <math.h>
#include "debug.h"
#include "MsCommon.h"
#include "Board.h"
//#include "mapi_gpio_devTable.h"
#include "DVBS2_MSB102KS/msb1245.h"
#include "MsOS.h"
#include "drvGPIO.h"
#include "msAPI_Timer.h"
#include "MApp_Scan.h"
//#include "drvDemod.h"
#include "apiDigiTuner.h"
#include "apiDMX.h"
#include "drvPCMCIA.h"
#include "drvSYS.h"
#include "drvDMD_common.h"
#include "drvIIC.h"
#include "MApp_Scan.h"
#include "msAPI_Memory.h"
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"
#include "mapp_si.h"
#include "MApp_GlobalVar.h"
#include "msAPI_Timer.h"

extern MAPI_BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks);
extern MAPI_BOOL MDrv_DVBS_Tuner_Initial(void);
extern MAPI_BOOL MDrv_DVBS_Tuner_CheckLock(void);
extern float MDrv_DVBS_Tuner_Get_RSSI(MS_U16 u16_gain, MS_U8 Dtype);
extern void *memset(void * s, int c, size_t count);

//extern MAPI_BOOL MDrv_DVBS_Tuner_Initial(void);
//extern float MDrv_DVBS_Tuner_Get_RSSI(MS_U16);
extern MS_SAT_PARAM sat_info;
extern BLINDSCAN_STATUS _enBlindScanStatus;
MAPI_BOOL  ReadMailbox(MS_U16 u16Addr, MS_U8* u8Data);

MAPI_U8 MSB1245_LIB[]=
{
#include "msb1245_dvbs.dat"
};

#define MSB1245_ADCPLL_IQ_SWAP          1
#define VERIFY_DSP                      0
#define MS1245_DEBUG                    0 ///1
#define POWER_ON_TIME_DBG               0 //1

#define DBG_TUNER(x)        //x

#if  MS1245_DEBUG
#define PRINTE(p) printf p
#else
#define PRINTE(p)
#endif
#define MSB124X_BLIND_SCAN_DEBUG 1
#define DEMOD_MSB1245_SLAVE_ID      (((U16)DVBS_DEMOD_IIC_BUS<<8)|0xF2)//(((U16)DVBS_DEMOD_IIC_BUS<<8)|0xD2)  //0xF2
#define MSB1245_MUTEX_TIMEOUT       (2000)
#define LOAD_CODE_I2C_BLOCK_NUM     (0x80)
#define SRAM_BASE                   (0x8000)
#define SAMPLING_RATE               (96000)
#define MSB1245_DEMOD_WAIT_TIMEOUT  (6000)
#define MSB1245_TUNER_WAIT_TIMEOUT  (50)

#define TR_TIME_OUT_WITH_FIX_SYMBOL_RATE                 3000 // for twice scan flow

// Mail box register address
#define REG_MB_CNTL      		0x098A
#define REG_MB_ADDR_L       	0x098B
#define REG_MB_ADDR_H       	0x098C
#define REG_MB_DATA         	0x098D

typedef enum
{
    E_DMD_S2_ZIF_EN = 0x00,
    E_DMD_S2_RF_AGC_EN,
    E_DMD_S2_DCR_EN,
    E_DMD_S2_IQB_EN,
    E_DMD_S2_IIS_EN,
    E_DMD_S2_CCI_EN,
    E_DMD_S2_FORCE_ACI_SELECT,
    E_DMD_S2_IQ_SWAP,					//For DVBS2
    E_DMD_S2_AGC_REF_EXT_0,
    E_DMD_S2_AGC_REF_EXT_1,
    E_DMD_S2_AGC_K,
    E_DMD_S2_ADCI_GAIN,
    E_DMD_S2_ADCQ_GAIN,
    E_DMD_S2_SRD_SIG_SRCH_RNG,
    E_DMD_S2_SRD_DC_EXC_RNG,
    E_DMD_S2_FORCE_CFO_0,				//0FH
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
    E_DMD_S2_FINEFE_KI_SWITCH_4,		//1FH
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
    E_DMD_S2_EQ_MU_FFE_DA,				//2FH
    E_DMD_S2_EQ_MU_FFE_DD,
    E_DMD_S2_EQ_ALPHA_SNR_DA,
    E_DMD_S2_EQ_ALPHA_SNR_DD,
    E_DMD_S2_FEC_ALFA,					//For DVBS2
    E_DMD_S2_FEC_BETA,					//For DVBS2
    E_DMD_S2_FEC_SCALING_LLR,			//For DVBS2
    E_DMD_S2_TS_SERIAL,
    E_DMD_S2_TS_CLK_RATE,
    E_DMD_S2_TS_OUT_INV,
    E_DMD_S2_TS_DATA_SWAP,
	//------------------------------------------
	E_DMD_S2_FW_VERSION_L,           	//0x3A
	E_DMD_S2_FW_VERSION_H,           	//0x3B
	E_DMD_S2_CHIP_VERSION,
	E_DMD_S2_FS_L,		 				//Frequency
	E_DMD_S2_FS_H,						//Frequency
	E_DMD_S2_MANUAL_TUNE_SYMBOLRATE_L,	//0x3F
	E_DMD_S2_MANUAL_TUNE_SYMBOLRATE_H,	//
	E_DMD_S2_SYSTEM_TYPE,				//DVBS/S2
	E_DMD_S2_MODULATION_TYPE,			//QPSK/8PSK
	E_DMD_S2_CODERATE,					//1/2

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
	E_DMD_S2_REV_FRAME_FLAG,			//0x4F
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
	E_DMD_S2_UNCRT_OVER_FLAG,			//0x5F
	E_DMD_S2_DISEQC_RX_LENGTH,
	E_DMD_S2_DISEQC_INTERRUPT_FLAG,
	E_DMD_S2_DISEQC_RX_FLAG,
	E_DMD_S2_DISEQC_INTERRUPT_STATUS,
	E_DMD_S2_DISEQC_STATUS_FLAG,
	E_DMD_S2_ACI_FIR_SELECTED,			//0x65
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
	E_DMD_S2_PR_LOCK_FLAG,				//0x6F
	E_DMD_S2_FSYNC_LOCK_FLAG,
	E_DMD_S2_FSYNC_FAIL_LOCK_FLAG,

  	E_DMD_S2_MB_SWUSE12L,				//0x72
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
  	E_DMD_S2_MB_SWUSE18H,				//0x7F
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
	E_DMD_S2_MB_SWUSE1FH, 				//0x8D

	E_DMD_S2_MB_DMDTOP_DBG_0,
	E_DMD_S2_MB_DMDTOP_DBG_1,			//0x8F
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
	E_DMD_S2_MB_DMDTOP_SWUSE02H,		//0x9F
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
	E_DMD_S2_MB_TOP_WR_DBG_95,			//0xAF
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
	E_DMD_S2_MB_DUMMY_REG_B,			//0xBF
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
	E_DMD_S2_LOG_FLAG,					//0xCF
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
	E_DMD_S2_TR_TIMEOUT,				//0xDF
	E_DMD_S2_BALANCE_TRACK,
	E_DMD_S2_GAIN_TILT_FLAG,			//0xE1

	DVBS2_PARAM_LEN
} DVBS_Param_2;



EN_BLINDSCAN_STATUS eBlindScanStatue = E_BLINDSCAN_NOTREADY;
MAPI_U8 u8DeviceBusy = 0;
MAPI_U8 u8PowerOnInit = 1;

EN_DEVICE_DEMOD_TYPE m_enCurrentDemodulator_Type = E_DEVICE_DEMOD_NULL;

static  MAPI_BOOL                     _bInited=MAPI_FALSE;
static  MAPI_BOOL                     _bDemodType=MAPI_FALSE;
static  MAPI_U16                      _u16BlindScanStartFreq=0;
static  MAPI_U16                      _u16BlindScanEndFreq=0;
static  MAPI_U16                      _u16TunerCenterFreq=0;
static  MAPI_U16                      _u16ChannelInfoIndex=0;
//Debug Only+
static  MAPI_U16                      _u16LockedSymbolRate=0;
static  MAPI_U16                      _u16LockedCenterFreq=0;
#if MSB124X_BLIND_SCAN_DEBUG
  static  MAPI_U16                      _u16NextCenterFreq=0;
static  MAPI_U16                      _u16PreLockedHB=0;
static  MAPI_U16                      _u16PreLockedLB=0;
static  MAPI_U16                      _u16CurrentSymbolRate=0;
static  MAPI_S16                      _s16CurrentCFO=0;
static  MAPI_U16                      _u16CurrentStepSize=0;
#endif
#if (ENABLE_S2 == 1)
static  MAPI_U32                      _u32CurrentFreq=0;
static  MAPI_U32                      _u32CurrentSR=0;
static  MAPI_U32                      _u32LocktimeStart=0;
static  MAPI_U8                       _u8LocktimeFlag=0;
#endif

static  float                         _fPostBer=0;
//static  MAPI_U16                    _u16RefPowerValue=0;
//static  MAPI_U8                     _u8CurrentCounter=0;
static  MAPI_U32                      _u32DemodLockTime=0;
static  MAPI_BOOL                     _bDemodLockFlag=MAPI_FALSE;
static  MAPI_U8                       _u8ToneBurstFlag=0;
// static  MAPI_U8                       _u8RollOff=0;
static  MAPI_U32                      _s32_Demod_DVBS2_Mutex=-1;
//static  MAPI_U32                      _s32_Demod_DVBS2_RW_Mutex=-1;   //For Register R/W
//static  MAPI_U32                      _s32_Demod_DVBS2_RW2_Mutex=-1;  //For DSP Register R/W
static  MAPI_U16                      _u16_packetError=0;
//static  MAPI_U8                     _u8_DVBS2_CurrentConstellation=0;
//static  MAPI_U8                     _u8_DVBS2_CurrentCodeRate=0;
static  float                         _f_DVBS2_CurrentSNR=0;

//Debug Only-
static  MAPI_U16                      _u16ChannelInfoArray[2][1000];
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
static MAPI_U8 S_TS_Output_VAL = 1; // 0:Parallel Mode 1: serial mode
MAPI_BOOL  MSB1245_I2C_Channel_Set(MAPI_U8 ch_num);
MAPI_BOOL  MSB1245_GPIO_Disable(MAPI_U8 u8Pin);
MAPI_BOOL  MSB1245_GPIO_SetLevel(MAPI_U8 u8Pin, MAPI_BOOL bLevel);
MAPI_BOOL  MSB1245_IIC_Bypass_Mode(MAPI_BOOL enable);
MAPI_BOOL  MSB1245_I2C_Channel_Set(MAPI_U8 ch_num);
MAPI_BOOL  MSB1245_I2C_Channel_Change(MAPI_U8 ch_num);
MAPI_BOOL  MSB1245_ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data);
MAPI_BOOL  MSB1245_WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data);
MAPI_BOOL  MSB1245_WriteReg2bytes(MAPI_U16 u16Addr, MAPI_U16 u16Data);
MAPI_BOOL  MSB1245_WriteRegs(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size);
MAPI_BOOL  MSB1245_LoadDSPCode(MAPI_U8  *pu8Buf, MAPI_U16 u16Len);
MAPI_BOOL  MSB1245_SetFrequency(MAPI_U16 u16CenterFreq, MAPI_U32 u32SymbolRate_Hz);
MAPI_U16   MSB1245_DTV_GetSignalStrength(void);
float      MSB1245_DTV_GetSignalNoiseRatio(void);
MAPI_U16   MSB1245_DTV_GetSignalQuality(MAPI_BOOL bDemodType);
MAPI_BOOL  MSB1245_DTV_GetLock(void);
MAPI_BOOL  MSB1245_DiSEqC_Init(void);

#if 0
MAPI_BOOL MDrv_msb1245_IIC_Write_300K(MAPI_U8 u8slaveID, MAPI_U8 *pu8Addr,MAPI_U8 u8AddrSize,
                             MAPI_U8 *pu8Data,  MAPI_U16 u16Size )
{
    mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_3);
    if(iptr ==NULL)
        ASSERT(0);
    iptr->SetSpeed((MAPI_U32)300);
    return iptr->WriteBytes( u8AddrSize, pu8Addr, u16Size, pu8Data);
}

MAPI_BOOL MDrv_msb1245_IIC_Write(MAPI_U8 u8slaveID, MAPI_U8 *pu8Addr,MAPI_U8 u8AddrSize,
                             MAPI_U8 *pu8Data,  MAPI_U16 u16Size )
{
    mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_3);
    return iptr->WriteBytes( u8AddrSize, pu8Addr, u16Size, pu8Data);
}

MAPI_BOOL MDrv_msb1245_IIC_Read_300K(MAPI_U8 u8slaveID, MAPI_U8 *pu8Addr,MAPI_U8 u8AddrSize,
                             MAPI_U8 *pu8Data,  MAPI_U16 u16Size )
{
    mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_3);

    if(iptr ==NULL)
        ASSERT(0);
    iptr->SetSpeed((MAPI_U32)300);
    return iptr->ReadBytes( u8AddrSize, pu8Addr, u16Size, pu8Data);
}

MAPI_BOOL MDrv_msb1245_IIC_Read(MAPI_U8 u8slaveID, MAPI_U8 *pu8Addr,MAPI_U8 u8AddrSize,
                             MAPI_U8 *pu8Data,  MAPI_U16 u16Size )
{
    mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_3);
    return iptr->ReadBytes( u8AddrSize, pu8Addr, u16Size, pu8Data);
}
#endif

MAPI_BOOL MDrv_Demod_Init(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U8 u8Data =0;
    MAPI_U16 u16Address =0;
    MAPI_U16 u16Data =0;
    MAPI_U16 u16dat_size =0;

#if(POWER_ON_TIME_DBG)
    MAPI_U32 u32InitTime =  MsOS_GetSystemTime();
    printf("\r\n MDrv_Demod_Init---START");
#endif

//    _bInited = MAPI_FALSE;

    if (_bInited==MAPI_TRUE)
    {
        PRINTE(("MSB1245 Already Init 0x%x\n",_bInited));
        return MAPI_TRUE;
    }

#if 0
     mapi_gpio *gptr = mapi_gpio::GetGPIO_Dev(DVBS_RESETZ);
    if(gptr != NULL)
    {
        gptr->SetOn();
        MsOS_DelayTask(10);
        gptr->SetOff();
        MsOS_DelayTask(20);
        gptr->SetOn();
    }
#endif

    MSB1245_GPIO_PowerOn();
    MsOS_DelayTask(10);
    MSB1245_GPIO_PowerOff();
    MsOS_DelayTask(20);
    MSB1245_GPIO_PowerOn();
    MsOS_DelayTask(10);

    PRINTE(("MSB1245 Init\n"));
    #if 1
    bRet&=MSB1245_I2C_Channel_Set(0);
    if (bRet==MAPI_FALSE)
    {
        PRINTE(("MSB1245 i2c channel set fail!!!\n"));
    }
    else
    {
        PRINTE(("MSB1245 i2c channel set success!!!\n"));
    }
    #endif
    //HW version Check
    u16Address=0x0900;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if (bRet==MAPI_FALSE)
    {
        PRINTE(("MSB1245 i2c read reg  fail!!!\n"));
    }
    else
    {
        PRINTE(("MSB1245 HW version: 0x%x=0x%x\n", u16Address, u8Data));
    }

    u16dat_size=sizeof(MSB1245_LIB);


#if(POWER_ON_TIME_DBG)
    MAPI_U32 u32DSPLoadtime = MsOS_GetSystemTime();
#endif

    bRet&=MSB1245_LoadDSPCode(MSB1245_LIB, u16dat_size);
    if (bRet==MAPI_FALSE)
    {
        PRINTE(("MSB1245 Load FW  fail!!!\n"));
    }
    else
    {
        PRINTE(("MSB1245 Load FW  success!!!\n"));
    }
#if(POWER_ON_TIME_DBG)
#if(VERIFY_DSP)
    printf("\r\n DSP LOAD & Verify time = %d ms",(int)MsOS_Timer_DiffTimeFromNow(u32DSPLoadtime));

#else
    printf("\r\n DSP LOAD  time = %d ms\n",(int)MsOS_Timer_DiffTimeFromNow(u32DSPLoadtime));
#endif
#endif
    MsOS_DelayTask(10);
    MSB1245_IIC_Bypass_Mode(MAPI_TRUE);
    bRet&=MDrv_DVBS_Tuner_Initial();
    MSB1245_IIC_Bypass_Mode(MAPI_FALSE);
    bRet&=MSB1245_DiSEqC_Init();
    //FW version Check
    u16Address=0x0989;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u16Data=u8Data;
    u16Address=0x0988;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u16Data=(u16Data<<8)|u8Data;
    PRINTE(("MSB1245  FW  Version:%x.%x\n", ((u16Data>>8)&0x00FF),(u16Data&0x00FF)));

    if (bRet==MAPI_FALSE)
    {
        printf("sttest MDRV DEMOD INIT fail \n");
    }
    _bInited = MAPI_TRUE;

#if(POWER_ON_TIME_DBG)
    printf("\r\n MDrv_Demod_Init---END total time = %d",(int)MsOS_Timer_DiffTimeFromNow(u32InitTime));
#endif
    return bRet;
}
//-----------------------------------------------------------------------

MAPI_BOOL MDrv_Demod_PowerOnOff(MAPI_BOOL bPowerOn)
{
    //MAPI_BOOL bRet=MAPI_TRUE;

    //mapi_gpio *gptr = mapi_gpio::GetGPIO_Dev(DVBS_RESETZ);

    if(bPowerOn)
        MSB1245_GPIO_PowerOn();
    else
        MSB1245_GPIO_PowerOff();

    return MAPI_TRUE;
}

void MApi_MSB1245_Demod_HWReset(void)
{
    if(u8PowerOnInit ==0) //AC/DC power on reset by mapi_interface_tv.cpp
    {
     //printf("\r\n boot-time-chk#aa MApi_MSB1245_Demod_HWReset-1");

     //mdrv_gpio_set_high(GPIO_FE_RST);
        MDrv_Demod_PowerOnOff(MAPI_TRUE);
        MsOS_DelayTask(10);
     //mdrv_gpio_set_low(GPIO_FE_RST);
        MDrv_Demod_PowerOnOff(MAPI_FALSE);
        MsOS_DelayTask(20);
     //mdrv_gpio_set_high(GPIO_FE_RST);
        MDrv_Demod_PowerOnOff(MAPI_TRUE);
        MsOS_DelayTask(10);
     }
}

MAPI_BOOL MDrv_Demod_StandBy(MAPI_BOOL bStandby)
{
    MAPI_BOOL bRet=MAPI_TRUE;

    PRINTE(("MDrv_Demod_StandBy+ 0x%x\n", bStandby));
    if (bStandby==MAPI_TRUE)
    {
        MApi_MSB1245_Demod_HWReset();
    }
    else if (bStandby==MAPI_FALSE)
    {
        MApi_MSB1245_Demod_HWReset();
        bRet&=MSB1245_I2C_Channel_Set(0);
        bRet&=MSB1245_WriteReg(0x10E1, 0x20);
        bRet&=MSB1245_WriteReg(0x10E0, 0x3F);
        bRet&=MSB1245_WriteReg(0x10E6, 0x08);
        bRet&=MSB1245_WriteReg(0x10E6, 0x00);
        bRet&=MSB1245_WriteReg(0x1004, 0x00);
        bRet&=MSB1245_WriteReg(0x1005, 0x00);
        bRet&=MSB1245_WriteReg(0x1000, 0x00);
        bRet&=MSB1245_WriteReg(0x1006, 0x7F);
        bRet&=MSB1245_WriteReg(0x1007, 0xFF);
        bRet&=MSB1245_WriteReg(0x1002, 0x00);
        bRet&=MSB1245_WriteReg(0x1018, 0x01);
        bRet&=MSB1245_WriteReg(0x0B32, 0x00);
    }
    PRINTE((" MDrv_Demod_StandBy-\n"));

    return bRet;
}
//-------------------------------------------------------------------------------------------

MAPI_BOOL MSB1245_IIC_Bypass_Mode(MAPI_BOOL enable)
{
    MAPI_U8   u8Retry = 10;

    while(u8Retry--)
    {
        if (enable)
            MSB1245_WriteReg(0x0900+(0x08)*2, 0x10);// IIC by-pass mode on
        else
            MSB1245_WriteReg(0x0900+(0x08)*2, 0x00);// IIC by-pass mode off
    }

    return MAPI_TRUE;
}
MAPI_BOOL  MSB1245_I2C_Channel_Set(MAPI_U8 ch_num)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U8 Data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);
    //Exit
    Data[0] = 0x34;
    bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    if (bRet != MAPI_TRUE)
    {
        printf("Err-%s():%d:\n", __FUNCTION__, __LINE__);
    }

    Data[0]=(ch_num & 0x01)? 0x36 : 0x45;
    bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    //Init
    Data[0] = 0x53;
    bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 5);
    Data[0]=(ch_num & 0x04)? 0x80 : 0x81;
    bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    if ((ch_num==4)||(ch_num==5)||(ch_num==1))
        Data[0]=0x82;
    else
        Data[0] = 0x83;
     bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);

    if ((ch_num==4)||(ch_num==5))
        Data[0]=0x85;
    else
        Data[0] = 0x84;
     bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
     Data[0]=(ch_num & 0x01)? 0x51 : 0x53;
     bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
     Data[0]=(ch_num & 0x01)? 0x37 : 0x7F;
     bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
     Data[0] = 0x35;
     bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
     Data[0] = 0x71;
     bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
     //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
     return bRet;
}
MAPI_BOOL  MSB1245_I2C_Channel_Change(MAPI_U8 ch_num)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U8 Data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);
    Data[0] = (ch_num & 0x01)? 0x81 : 0x80;
    bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    Data[0] = (ch_num & 0x02)? 0x83 : 0x82;
    bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    Data[0] = (ch_num & 0x04)? 0x85 : 0x84;
    bRet&=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return bRet;
}
MAPI_BOOL  MSB1245_ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data)
{
   MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U8 Data[5];

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) &0xff;
    Data[4] = u16Addr &0xff;

    Data[0] = 0x35;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    Data[0] = 0x10;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 5);
    bRet &=MDrv_msb1245_IIC_Read(DEMOD_MSB1245_SLAVE_ID, 0,0, pu8Data, 1);
    Data[0] = 0x34;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return bRet;
}
MAPI_BOOL MSB1245_WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U8 Data[6];

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);

    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) & 0xff;
    Data[4] = u16Addr & 0xff;
    Data[5] = u8Data;

    Data[0] = 0x35;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);

    Data[0] = 0x10;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 6);

    Data[0] = 0x34;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return bRet;
}
MAPI_BOOL MSB1245_WriteReg2bytes(MAPI_U16 u16Addr, MAPI_U16 u16Data)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    bRet &= MSB1245_WriteReg(u16Addr, (MAPI_U8)u16Data&0x00ff);
    bRet &= MSB1245_WriteReg(u16Addr + 0x0001, (MAPI_U8)(u16Data>>8)&0x00ff);
    return bRet;
}
MAPI_BOOL MSB1245_ReadReg2bytes(MAPI_U16 u16Addr, MAPI_U16 *pu16Data)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U8     u8Data =0;
    MAPI_U16    u16Data =0;

    bRet &= MSB1245_ReadReg(u16Addr + 0x0001, &u8Data);
    u16Data = u8Data;
    bRet &= MSB1245_ReadReg(u16Addr, &u8Data);
    *pu16Data = (u16Data<<8)|u8Data;

    return bRet;
}
MAPI_BOOL MSB1245_ReadRegs_300K(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    //MAPI_U16 index;
    MAPI_U8 Data[5];

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) &0xff;
    Data[4] = u16Addr &0xff;

    Data[0] = 0x35;
    bRet &=MDrv_msb1245_IIC_Write_300K(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    Data[0] = 0x10;
    bRet &=MDrv_msb1245_IIC_Write_300K(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 5);
    bRet &=MDrv_msb1245_IIC_Read_300K(DEMOD_MSB1245_SLAVE_ID, 0,0, u8pData, data_size);
    Data[0] = 0x34;
    bRet &=MDrv_msb1245_IIC_Write_300K(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return bRet;

}

MAPI_BOOL MSB1245_WriteRegs_300K(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 index;
    MAPI_U8 Data[LOAD_CODE_I2C_BLOCK_NUM+5];

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) &0xff;
    Data[4] = u16Addr &0xff;

#if(VERIFY_DSP)
    if(u16Addr > 0xf298)
    {
        for(index = 0; index < data_size ; index++)
        {
          if((index%16)==0)
            printf("\r\n");
          printf(" %2X ",u8pData[index]);
        }
    }
#endif
    for(index = 0; index < data_size ; index++)
    {
    Data[5+index] = u8pData[index];
    }
    Data[0] = 0x35;
    bRet &=MDrv_msb1245_IIC_Write_300K(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    Data[0] = 0x10;
    bRet &=MDrv_msb1245_IIC_Write_300K(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 5 + data_size);
    Data[0] = 0x34;
    bRet &=MDrv_msb1245_IIC_Write_300K(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return bRet;
}


MAPI_BOOL MSB1245_ReadRegs(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    //MAPI_U16 index;
    MAPI_U8 Data[5];

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) &0xff;
    Data[4] = u16Addr &0xff;

    Data[0] = 0x35;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    Data[0] = 0x10;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 5);
    bRet &=MDrv_msb1245_IIC_Read(DEMOD_MSB1245_SLAVE_ID, 0,0, u8pData, data_size);
    Data[0] = 0x34;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return bRet;

}

MAPI_BOOL MSB1245_WriteRegs(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 index;
    MAPI_U8 Data[LOAD_CODE_I2C_BLOCK_NUM+5];

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) &0xff;
    Data[4] = u16Addr &0xff;

    for(index = 0; index < data_size ; index++)
    {
    Data[5+index] = u8pData[index];
    }
    Data[0] = 0x35;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    Data[0] = 0x10;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 5 + data_size);
    Data[0] = 0x34;
    bRet &=MDrv_msb1245_IIC_Write(DEMOD_MSB1245_SLAVE_ID, 0, 0, Data, 1);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return bRet;
}

MAPI_BOOL MSB1245_LoadDSPCode(MAPI_U8  *pu8Buf, MAPI_U16 u16Len)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 index;
    MAPI_U16 SRAM_Address;

    bRet&=MSB1245_I2C_Channel_Change(3);
    bRet&=MSB1245_WriteReg(0x0B32, 0x01);
    bRet&=MSB1245_I2C_Channel_Change(0);
    bRet&=MSB1245_WriteReg(0x3008, 0x00);
    bRet&=MSB1245_WriteReg(0x3009, 0x00);
    bRet&=MSB1245_WriteReg(0x300A, 0x00);
    bRet&=MSB1245_WriteReg(0x300B, 0x00);
    bRet&=MSB1245_I2C_Channel_Change(3);
    bRet&=MSB1245_WriteReg(0x10E1, 0x20);
    bRet&=MSB1245_WriteReg(0x10E0, 0x3F);
    bRet&=MSB1245_WriteReg(0x10E6, 0x08);
    bRet&=MSB1245_I2C_Channel_Change(0);
    for (index = 0; index < u16Len;)
    {
            SRAM_Address = SRAM_BASE + index;
            if (index+LOAD_CODE_I2C_BLOCK_NUM-1<u16Len)
            {
                bRet&= MSB1245_WriteRegs_300K(SRAM_Address,pu8Buf+index,LOAD_CODE_I2C_BLOCK_NUM);
                index=index+LOAD_CODE_I2C_BLOCK_NUM-1;
            }
            else
            {
                bRet&=MSB1245_WriteRegs_300K(SRAM_Address,pu8Buf+index,u16Len-index);
                index=u16Len;
            }
    }
#if VERIFY_DSP
    unsigned char *t_cmpbuffer;
    t_cmpbuffer = (unsigned char*)malloc(u16Len);
    MAPI_U32 u32TimeTicket = MsOS_GetSystemTime();

    for (index = 0; index < u16Len;)
    {
        SRAM_Address = SRAM_BASE + index;
        //printf("\r\n SRAM Address = %x", SRAM_Address);
        if (index+LOAD_CODE_I2C_BLOCK_NUM-1<u16Len)
        {
            bRet&= MSB1245_ReadRegs_300K(SRAM_Address,t_cmpbuffer+index,LOAD_CODE_I2C_BLOCK_NUM);
            index=index+LOAD_CODE_I2C_BLOCK_NUM-1;
        }
        else
        {
            bRet&=MSB1245_ReadRegs_300K(SRAM_Address,t_cmpbuffer+index,u16Len-index);
            index=u16Len;
        }
    }

    PRINTE(("Check FW code+++ ALL\n"));
    for (index = 0; index < u16Len; index++)
    {
        if (pu8Buf[index]!=t_cmpbuffer[index])
        {
            printf("\r\n @@DVBS DSP Compare FAIL");
            PRINTE(("%d Different Code Write:0x%x Read:0x%x\n", index, pu8Buf[index], t_cmpbuffer[index]));
            bRet = MAPI_FALSE;
        }
        if (index > u16Len -10)
        {
            PRINTE(("%d Check Code Write:0x%x Read:0x%x\n", index, pu8Buf[index], t_cmpbuffer[index]));
        }
    }
    PRINTE(("Check FW code--- ALL\n"));

    free(t_cmpbuffer);
    printf("\r\n Verify DSP time = %d ms",(int)MsOS_Timer_DiffTimeFromNow(u32TimeTicket));

#endif

    bRet&=MSB1245_I2C_Channel_Change(3);

    bRet&=MSB1245_WriteReg(0x10E6, 0x00);
    bRet&=MSB1245_WriteReg(0x1004, 0x00);
    bRet&=MSB1245_WriteReg(0x1005, 0x00);
    bRet&=MSB1245_WriteReg(0x1000, 0x00);
    bRet&=MSB1245_WriteReg(0x1006, 0x7F);
    bRet&=MSB1245_WriteReg(0x1007, 0xFF);
    bRet&=MSB1245_WriteReg(0x1002, 0x00);
    bRet&=MSB1245_WriteReg(0x1018, 0x01);
    bRet&=MSB1245_WriteReg(0x0B32, 0x00);

    return bRet;
}
MAPI_BOOL  MSB1245_SetFrequency(MAPI_U16 u16CenterFreq_MHz, MAPI_U32 u32SymbolRate_Ks)
{
     MAPI_BOOL bRet=MAPI_TRUE;
     MAPI_U16 u16LockCount;
    //printf("--%s():%d\n", __FUNCTION__, __LINE__);
    bRet&=MDrv_DVBS_Tuner_SetFreq(u16CenterFreq_MHz, u32SymbolRate_Ks);

    if (bRet==MAPI_TRUE)
    {
        u16LockCount=0;
        do
        {
            bRet=MAPI_TRUE;
            bRet&=MDrv_DVBS_Tuner_CheckLock();
            MsOS_DelayTask(1);
            u16LockCount++;
        }while((bRet==MAPI_FALSE) && (u16LockCount<MSB1245_TUNER_WAIT_TIMEOUT)) ;

        if (bRet==MAPI_TRUE)
        {
            PRINTE(("Tuner PLL Lock\n"));
        }
        else
        {
            PRINTE(("Tuner PLL Unlock\n"));
        }
    }

    return bRet;
}
MAPI_BOOL MSB1245_DiSEqC_Init(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    u16Address=0x0DCD; //Clear Status
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data=(u8Data&(~0x20))|(0x20);
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    u16Address=0x0DC0;
    u8Data=0x00;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    u16Address=0x0DC0;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data=(u8Data&(~0x06))|(0x06);
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    return bRet;
}

// return -1*rf_dbm*10
MAPI_U16    MSB1245_DTV_GetSignalStrength(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U16 u16Data =0;
    MAPI_U8  u8Data =0;
    //MAPI_U8  u8Index =0;
    float    rf_level_dbm = 0.0;
    MAPI_U16 u16_ssi = 0;

    if (MSB1245_DTV_GetLock()==MAPI_FALSE)//Demod unlock
    {
        return 0;
    }

    u16Address=0x3E26;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data=(u8Data&0xF0)|0x03;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    u16Address=0x3E05;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data|=0x80;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

    u16Address=0x3E29;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u16Data=u8Data;
    u16Address=0x3E28;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u16Data=(u16Data<<8)|u8Data;
    //printf("===========================Tuner u16Data = %d\n",u16Data);
    u16Address=0x3E05;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data&=~(0x80);
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    if (bRet==MAPI_FALSE)
    {
        PRINTE(("MSB1245_DTV_GetSignalStrength fail!!! \n"));
        return 0;
    }
    //printf("[ww] IF AGC [%d]\n",u16Data);
    MSB1245_IIC_Bypass_Mode(MAPI_TRUE);
    rf_level_dbm = MDrv_DVBS_Tuner_Get_RSSI(u16Data,2);
    MSB1245_IIC_Bypass_Mode(MAPI_FALSE);
    u16_ssi= 100+rf_level_dbm;

    return u16_ssi;
}
float MSB1245_DTV_GetSignalNoiseRatio(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    //MAPI_U32 u32Data;
    MAPI_U8  u8Data =0;
    //NDA SNR
    MAPI_U32 u32NDA_SNR_A =0;
    MAPI_U32 u32NDA_SNR_AB =0;

    //float  fvariance;
    //float  log_snr;

    //NDA SNR
    float NDA_SNR_A =0.0;
    float NDA_SNR_AB =0.0;
    float NDA_SNR =0.0;
    float snr_poly =0.0;
    float Fixed_SNR =0.0;
    if (MSB1245_DTV_GetLock()==MAPI_FALSE)
    {
            return 0;
    }

    u16Address=0x1B08;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data|=0x10;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    //NDA SNR
    u16Address=0x1B8E;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32NDA_SNR_A=(u8Data&0x03);
    u16Address=0x1B8D;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32NDA_SNR_A=(u32NDA_SNR_A<<8)|u8Data;
    u16Address=0x1B8C;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32NDA_SNR_A=(u32NDA_SNR_A<<8)|u8Data;      //printf("u32NDA SNR A = %lu\n",u32NDA_SNR_A);

    u16Address=0x1B92;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32NDA_SNR_AB=(u8Data&0x3F);
    u16Address=0x1B91;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32NDA_SNR_AB=(u32NDA_SNR_AB<<8)|u8Data;
    u16Address=0x1B90;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32NDA_SNR_AB=(u32NDA_SNR_AB<<8)|u8Data;    //printf("u32NDA SNR AB = %lu\n",u32NDA_SNR_AB);

    u16Address=0x1B08;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data&=~(0x10);
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

    if (bRet==MAPI_FALSE)
    {
        PRINTE(("MSB1245_DTV_GetSignalNoiseRatio fail!!! \n"));
        return 0;
    }
    //NDA SNR
    NDA_SNR_A=(float)u32NDA_SNR_A/65536;
    NDA_SNR_AB=(float)u32NDA_SNR_AB/4194304;
    //mick
    NDA_SNR_AB=(float)sqrt(NDA_SNR_AB);
    NDA_SNR=10*log10((double)(1/((NDA_SNR_A/NDA_SNR_AB)-1)));

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
    return (MAPI_U32)Fixed_SNR;//(MAPI_U32)NDA_SNR;
}
MAPI_U16    MSB1245_DTV_GetSignalQuality(MAPI_BOOL bDemodType)
{
        MAPI_BOOL bRet=MAPI_TRUE;
        MAPI_U16  u16Address =0, u16Data = 0;
        MAPI_U8   u8Data =0, u8Data2 = 0;
        MAPI_U8   _u8_DVBS2_CurrentConstellationLocal = 0, _u8_DVBS2_CurrentCodeRateLocal = 0;
        MAPI_U16  u16BitErrPeriod =0;
        MAPI_U32  u32BitErr =0;
        MAPI_U16  u16Quality = 0;
        MAPI_U16  BCH_Eflag2_Window=0;
        float fber =0.0;
        float __attribute__ ((unused)) log_ber = 0.0, ber_sqi = 0.0, cn_rel = 0.0, f_snr = 0.0;
        double LDPCBer=0.0, eFlag_PER=0.0;

        if (MSB1245_DTV_GetLock()==MAPI_FALSE)
            return 0;

        //_u8_DVBS2_CurrentConstellationLocal = _u8_DVBS2_CurrentConstellation;
        //_u8_DVBS2_CurrentCodeRateLocal = _u8_DVBS2_CurrentCodeRate;

        if (bDemodType==MAPI_FALSE)//S
        {
            u16Address=0x1C2C;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            if (bRet==MAPI_FALSE)
            {
                PRINTE(("MSB1245_DTV_GetSignalQuality fail!!! \n"));
                return 0;
            }
            if ((u8Data&0x02)!=0x02)
            {
                return 0;
            }
            u16Address=0x1C32;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u8Data|=0x80;
            bRet&=MSB1245_WriteReg(u16Address, u8Data);
            u16Address=0x1C31;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16BitErrPeriod=u8Data;
            u16Address=0x1C30;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16BitErrPeriod=(u16BitErrPeriod<<8)|u8Data;
            u16Address=0x1C3D;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32BitErr=u8Data;
            u16Address=0x1C3C;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32BitErr=(u32BitErr<<8)|u8Data;
            u16Address=0x1C3B;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32BitErr=(u32BitErr<<8)|u8Data;
            u16Address=0x1C3A;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32BitErr=(u32BitErr<<8)|u8Data;
            u16Address=0x1C32;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u8Data&=~(0x80);
            bRet&=MSB1245_WriteReg(u16Address, u8Data);
            if (u16BitErrPeriod == 0)
                u16BitErrPeriod = 1;
            if (u32BitErr <= 0)
                fber = 0.5 / ((float)u16BitErrPeriod *128 * 188 * 8);
            else
                fber = (float)u32BitErr / ((float)u16BitErrPeriod *128 * 188 * 8);
            _fPostBer=fber;
            if (bRet==MAPI_FALSE)
            {
                PRINTE(("MSB1245_DTV_GetSignalQuality GetPostViterbiBer Fail!\n"));
                return 0;
            }

            float fDVBS_SQI_CNref[]=
            {   //0,    1,    2,    3,    4
                //4.2,   5.9,  7.0,  7.9,  8.5,//QPSK
                5.7,   7.4,  8.5,  9.4,  10.0,//QPSK
            };
            u16Address = 0x1C84;
            bRet &= MSB1245_ReadReg(u16Address, &u8Data);
            _u8_DVBS2_CurrentCodeRateLocal = (u8Data & 0x07);

            log_ber = ( - 1) *log10f(1 / fber);//Mick,BY modify

            if (fber > 1.0E-3)
                ber_sqi = 0.0;
            else if(fber > 8.5E-7)
                ber_sqi = (log10f(1.0f/fber))*20.0f - 40.0f;
            else
                ber_sqi = 100.0;

            f_snr = MSB1245_DTV_GetSignalNoiseRatio();
            cn_rel = f_snr - fDVBS_SQI_CNref[_u8_DVBS2_CurrentCodeRateLocal];

            if (cn_rel < -7.0f)
            {
                u16Quality = 0;
            }
            else if (cn_rel < 3.0)
            {
                u16Quality = (MAPI_U16)(ber_sqi*((cn_rel - 3.0)/10.0 + 1.0));
            }
            else
            {
                u16Quality = (MAPI_U16)ber_sqi;
            }

            return u16Quality;
        }
        else    //S2
        {
            u16Address=0x1D04;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u8Data|=0x01;
            bRet&=MSB1245_WriteReg(u16Address, u8Data);
            //BCH eflag2 sum
            u16Address=0x1D57;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            _u16_packetError=u8Data;
            u16Address=0x1D56;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            _u16_packetError=(_u16_packetError<<8)|u8Data;

            //LDPC_Count_Window
            u16Address=0x1D25;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16BitErrPeriod=u8Data;
            u16Address=0x1D24;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16BitErrPeriod=(u16BitErrPeriod<<8)|u8Data;
            //LDPC_BER_Count
            u16Address=0x1D5B;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32BitErr=u8Data;
            u16Address=0x1D5A;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32BitErr=(u32BitErr<<8)|u8Data;
            u16Address=0x1D59;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32BitErr=(u32BitErr<<8)|u8Data;
            u16Address=0x1D58;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32BitErr=(u32BitErr<<8)|u8Data;

            u16Address=0x1D04;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u8Data&=~(0x01);
            bRet&=MSB1245_WriteReg(u16Address, u8Data);

            if (u16BitErrPeriod == 0)
                u16BitErrPeriod = 1;

            u16Address = 0x1D4A;                //BCH EFLAG2_Window, mick
            bRet &= MSB1245_ReadReg2bytes(u16Address, &u16Data);
            BCH_Eflag2_Window=u16Data;

            //New func                                                  //PostLDPC BER
            eFlag_PER = (float)(_u16_packetError)/(float)(BCH_Eflag2_Window);
            LDPCBer = 0.089267531133002*pow(eFlag_PER, 2) + 0.019640560289510*eFlag_PER + 0.0000000001;

            fber = LDPCBer;
            _fPostBer = LDPCBer;
            //fgPerBER = LDPCBer;

            //_fPostBer=fber;
            //SQI
            if (bRet==MAPI_FALSE)
            {
                PRINTE(("MSB1245_DTV_GetSignalQuality GetPostViterbiBer Fail!\n"));
                return 0;
            }

            float fDVBS2_SQI_CNref[][11]=
            {    //0,   1,    2,    3,    4,    5,    6,    7,    8,    9,    10
            //old 1/2, 1/3,  2/3,  1/4,  3/4,  2/5,  3/5,  4/5,  5/6,   8/9,  9/10
              //  1/4, 1/3,  2/5,  1/2,  3/5,  2/3,  3/4,  4/5,  5/6,   8/9,  9/10
                {-1.6,-0.5,  0.5,  1.8,  3.0,  3.8,  4.8,  5.4,  5.9,   6.9,  7.2}, //QPSK
                {0.0,  0.0,  0.0,  0.0,  6.3,  7.4,  8.7,  0.0, 10.1,  11.4, 11.8}, //8PSK
            };

            u16Address = 0x1BD7;
            bRet &= MSB1245_ReadReg(u16Address, &u8Data);
            _u8_DVBS2_CurrentCodeRateLocal = (u8Data & 0x3C)>>2;

            u16Address = 0x1BD7;
            bRet &= MSB1245_ReadReg(u16Address, &u8Data); //INNER_PLSCDEC_DEBUG_OUT1
            u16Address = 0x1BD6;
            bRet &= MSB1245_ReadReg(u16Address, &u8Data2);//INNER_PLSCDEC_DEBUG_OUT0

            if(((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x00))
            {
                _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_QPSK;
            }
            else if (((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x80))
            {
                _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_8PSK;//8PSK
            }

            log_ber = ( - 1) *log10f(1 / fber);
            if (fber > 1.0E-3)
                ber_sqi = 0.0;
            else if(fber > 8.5E-7)
                ber_sqi = (log10f(1.0f/fber))*20.0f - 40.0f;
            else
                ber_sqi = 100.0;

            f_snr = MSB1245_DTV_GetSignalNoiseRatio();
            cn_rel = f_snr - fDVBS2_SQI_CNref[_u8_DVBS2_CurrentConstellationLocal][_u8_DVBS2_CurrentCodeRateLocal];

            if (cn_rel < -7.0f)
            {
                u16Quality = 0;
            }
            else if (cn_rel < 3.0)
            {
                u16Quality = (MAPI_U16)(ber_sqi*((cn_rel - 3.0)/10.0 + 1.0));
            }
            else
            {
                u16Quality = (MAPI_U16)ber_sqi;
            }
            //printf("(JAMIE) u16Quality = %d\n",u16Quality);
            return u16Quality;

        }
}
MAPI_BOOL    MSB1245_DTV_GetLock(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if ((u8Data&0x02)==0x00)
    {
        u16Address=0x0B56;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        if ((u8Data>=15) && (u8Data!=0xcd)) //For lock/unlock issue.
        {
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
    }
    else
    {
        bRet = MAPI_TRUE;
    }
    return bRet;
}

//------------------------------------------------------------------------------
MAPI_BOOL MSB1245_TS_Enable(MAPI_BOOL bTsEnable)
{
    MAPI_BOOL bRet=MAPI_TRUE;

    if (bTsEnable == MAPI_TRUE)
    {
        bRet&=MSB1245_WriteReg(0x095A, 0xFF);
    }
    else
    {
        bRet&=MSB1245_WriteReg(0x095A, 0x00);
    }
    return bRet;
}
void MSB1245_GPIO_PowerOn(void)
{
	Demodulator_ON();
    PRINTE(("MSB1245 Demodulator_ON\n"));
}
void MSB1245_GPIO_PowerOff(void)
{
	Demodulator_OFF();
    PRINTE(("MSB1245 mapi_gpio_msb124x_Off\n"));
}
#if (ENABLE_S2)
//=======================================================================
MAPI_BOOL MDrv_CofdmDmd_SetTsSerial(MAPI_BOOL bSerial)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    UNUSED(bSerial);
    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_TPSGetLock(MAPI_BOOL *pbLock)
{
    MAPI_BOOL bRet=MAPI_TRUE;

    *pbLock=MSB1245_DTV_GetLock();
    PRINTE(("MSB1245 MDrv_Demod_TPSGetLock  0x%x\n", *pbLock));
    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_MPEGGetLock(MAPI_BOOL *pbLock)
{
    MAPI_BOOL bRet=MAPI_TRUE;

    *pbLock=MSB1245_DTV_GetLock();
    PRINTE(("MSB1245 MDrv_Demod_MPEGGetLock 0x%x\n", *pbLock));
    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_GetRollOff(MAPI_U8 *pRollOff)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    u16Address=0x1B1E;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if ((u8Data&0x03)==0x00)
        *pRollOff = 0;  //Rolloff 0.35
    else if (((u8Data&0x03)==0x01) || ((u8Data&0x03)==0x03))
        *pRollOff = 1;  //Rolloff 0.25
    else
        *pRollOff = 2;  //Rolloff 0.20
    PRINTE(("MDrv_Demod_GetRollOff:%d\n", *pRollOff));

    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_GetRFOffset(MAPI_S16 *ps16RFOff)
{
    MAPI_BOOL bRet=TRUE;
    MAPI_U16 u16Address;
    MAPI_U8 u8Data;
    MAPI_U32 u32FreqOffset;
    float FreqOffset;

    if (MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER)==FALSE)
    {
      PRINTE(("%s function mutex timeout\n", __FUNCTION__));
      return FALSE;
    }
    u32FreqOffset=0;
    u16Address=0x2C39;
    u8Data=0x08;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    u16Address=0x3E05;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data|=0x80;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    u16Address=0x2C46;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32FreqOffset=u8Data;
    u16Address=0x2C45;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32FreqOffset=(u32FreqOffset<<8)|u8Data;
    u16Address=0x2C44;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u32FreqOffset=(u32FreqOffset<<8)|u8Data;
    u16Address=0x3E05;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data&=~(0x80);
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    FreqOffset=(float)u32FreqOffset;
    if(FreqOffset>=2048)
    {
      FreqOffset=FreqOffset-4096;
    }
    FreqOffset=(FreqOffset/4096)*SAMPLING_RATE;
    *ps16RFOff=FreqOffset/1000;
    PRINTE(("MSB1245 FreqOffset:%f[MHz]\n", FreqOffset/1000));
    MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;

}
static MAPI_BOOL _MDrv_CofdmDmd_BlindScan_Start(MAPI_U16 u16StartFreq,MAPI_U16 u16EndFreq)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    PRINTE(("MDrv_CofdmDmd_BlindScan_Start+\n"));
    _u16BlindScanStartFreq=u16StartFreq;
    _u16BlindScanEndFreq=u16EndFreq;
    _u16TunerCenterFreq=0;
    _u16ChannelInfoIndex=0;
    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

    //ADCPLL IQ swap
    if(MSB1245_ADCPLL_IQ_SWAP==1)
    {
        u16Address=0x0A03;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data|=(0x10);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);

        //re-check
        u16Address=0x0A03;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        PRINTE(("[Mstar]BlindScan_Start_MSB1245_ADCPLL_IQ_SWAP==1 \n"));
        PRINTE(("[Mstar]BlindScan_Start_  u8Data=0x%x \n",u8Data));
    }
    else if(MSB1245_ADCPLL_IQ_SWAP==0)
    {
        u16Address=0x0A03;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x10);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);

        //re-check
        u16Address=0x0A03;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        PRINTE(("[Mstar]BlindScan_Start_MSB1245_ADCPLL_IQ_SWAP==0 \n"));
        PRINTE(("[Mstar]BlindScan_Start_  u8Data=0x%x \n",u8Data));
    }

    u16Address=0x0992;
    bRet&=MSB1245_WriteReg2bytes(u16Address, _u16BlindScanStartFreq);
    PRINTE(("MDrv_CofdmDmd_BlindScan_Start- _u16BlindScanStartFreq%d u16StartFreq %d u16EndFreq %d\n", _u16BlindScanStartFreq, u16StartFreq, u16EndFreq));

    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_BlindScan_NextFreq(MAPI_BOOL* bBlindScanEnd , MS_U8* u8Progress)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;
    MAPI_U8 u8Data2 =0;
    MAPI_U32  u32TunerCutOffFreq =0;
    MAPI_U16 u16WaitCount =0;
    MAPI_U16 u16TunerCenterFreq =0;

    PRINTE(("MDrv_CofdmDmd_BlindScan_NextFreq+\n"));
    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if ((u8Data&0x02)==0x02)
    {
            u8Data|=0x08;
            bRet&=MSB1245_WriteReg(u16Address, u8Data);
            u16WaitCount=0;
            do
            {
                u16Address=0x0B56;
                bRet&=MSB1245_ReadReg(u16Address, &u8Data);
                u16WaitCount++;
                PRINTE(("MDrv_CofdmDmd_BlindScan_NextFreq u8Data:0x%x u16WaitCount:%d\n", u8Data, u16WaitCount));
                MsOS_DelayTask(1);
            }while((u8Data!=0x01)&&(u16WaitCount<MSB1245_DEMOD_WAIT_TIMEOUT));
     }
    u16WaitCount=0;

    * bBlindScanEnd=MAPI_FALSE;
    u16TunerCenterFreq=0;
    u16Address=0x0993;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u16TunerCenterFreq=u8Data;
    u16Address=0x0992;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data2);
    u16TunerCenterFreq=(u16TunerCenterFreq<<8)|u8Data2;
//    if((u16TunerCenterFreq > _u16TunerCenterFreq) && (u16TunerCenterFreq >= _u16BlindScanStartFreq))
        _u16TunerCenterFreq = u16TunerCenterFreq;

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

    if (_u16TunerCenterFreq >=_u16BlindScanEndFreq)
    {
        PRINTE(("MDrv_CofdmDmd_BlindScan_NextFreq . _u16TunerCenterFreq %d _u16BlindScanEndFreq%d\n", _u16TunerCenterFreq, _u16BlindScanEndFreq));
        * bBlindScanEnd=MAPI_TRUE;

        return bRet;
    }
//#if (FRONTEND_TUNER_TYPE == TUNER_AV2011)
//    u32TunerCutOffFreq=44000;
//#else
    u32TunerCutOffFreq=44000;
//#endif
    if(_u16TunerCenterFreq<=990)//980
    {
       u16Address=0x0B51;
       bRet&=MSB1245_ReadReg(u16Address, &u8Data);
       if(u8Data==0x01)
       {
          if(_u16TunerCenterFreq<970)//970
          {
            u32TunerCutOffFreq=10000;
          }
          else
          {
            u32TunerCutOffFreq=20000;
          }
          u16Address=0x0B51;
          u8Data=0x02;
          bRet&=MSB1245_WriteReg(u16Address, u8Data);
       }
       else if(u8Data==0x02)
       {
          u16Address=0x0B51;
          u8Data=0x00;
          bRet&=MSB1245_WriteReg(u16Address, u8Data);
       }
    }

    MSB1245_IIC_Bypass_Mode(MAPI_TRUE);
    //printf("--%s():%d\n", __FUNCTION__, __LINE__);
    bRet&=MSB1245_SetFrequency(_u16TunerCenterFreq,u32TunerCutOffFreq);
    MSB1245_IIC_Bypass_Mode(MAPI_FALSE);
    MsOS_DelayTask(10);
    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if ((u8Data&0x02)==0x00)
    {
        u8Data&=~(0x08);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);
        u8Data|=0x02;
        bRet&=MSB1245_WriteReg(u16Address, u8Data);
        u8Data|=0x01;
        bRet&=MSB1245_WriteReg(u16Address, u8Data);
    }
    else
    {
        u8Data&=~(0x08);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);
    }
    PRINTE(("MDrv_CofdmDmd_BlindScan_NextFreq _u16TunerCenterFreq:%d-\n", _u16TunerCenterFreq));

    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(MAPI_U8* u8Progress,MAPI_U8 *u8FindNum)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U32  u32Data =0;
    MAPI_U16 u16Data =0;
    MAPI_U8   u8Data =0;
    MAPI_U16  u16WaitCount =0;

    PRINTE(("MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished+\n"));
    u16WaitCount=0;
    *u8FindNum=0;
    *u8Progress=0;
    do
    {
        u16Address=0x0B56;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u16WaitCount++;
        PRINTE(("MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished+1 u8Data:0x%x u16WaitCount:%d\n", u8Data, u16WaitCount));
        MsOS_DelayTask(1);
    }while((u8Data!=17)&&(u16WaitCount<MSB1245_DEMOD_WAIT_TIMEOUT));
    if (u16WaitCount>=MSB1245_DEMOD_WAIT_TIMEOUT)
    {
        bRet=MAPI_FALSE;
    }
    else
    {
        u16Address=0x0B57;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
#if MSB124X_BLIND_SCAN_DEBUG
        if (u8Data==0)
        {
            //Center Freq -- mail box version
//            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE13L,&u8Data);
            u16Address=0x0997;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32Data=u8Data;
//            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE12H,&u8Data);
            u16Address=0x0996;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32Data=(u32Data<<8)|u8Data;
//            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE12L,&u8Data);
            u16Address=0x0995;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32Data=(u32Data<<8)|u8Data;
            _u16ChannelInfoArray[0][_u16ChannelInfoIndex]=((u32Data+500)/1000); //Center Freq
            _u16LockedCenterFreq=((u32Data+500)/1000);

            //symbol rate -- mail box version
//            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE14H,&u8Data);
            u16Address=0x0B53;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16Data=u8Data;
//            bRet &= ReadMailbox(E_DMD_S2_MB_SWUSE14L,&u8Data);
            u16Address=0x0B52;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16Data=(u16Data<<8)|u8Data;
            _u16ChannelInfoArray[1][_u16ChannelInfoIndex]=(u16Data);//Symbol Rate
            _u16LockedSymbolRate=u16Data;
            _u16ChannelInfoIndex++;
            *u8FindNum=_u16ChannelInfoIndex;

            //current lock cfo -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE15H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE15L,&u8Data);
            u16Data=(u16Data<<8)|u8Data;
            if (u16Data*1000 >= 0x8000)
            {
                u16Data=0x10000- u16Data*1000;
                _s16CurrentCFO=-1*u16Data/1000;
            }
            else
            {
                _s16CurrentCFO=u16Data;
            }

            //current step size  -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE16H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE16L,&u8Data);
            u16Data=(u16Data<<8)|u8Data;
            _u16CurrentStepSize=u16Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE18H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE18L,&u8Data);
            u16Data=(u16Data<<8)|u8Data;
            _u16PreLockedHB=u16Data;
            //prelock LB  -- mail box version
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE19H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE19L,&u8Data);
            u16Data=(u16Data<<8)|u8Data;
            _u16PreLockedLB=u16Data;
            PRINTE(("Current Locked CF:%d BW:%d BWH:%d BWL:%d CFO:%d Step:%d\n", _u16LockedCenterFreq, _u16LockedSymbolRate,_u16PreLockedHB, _u16PreLockedLB, _s16CurrentCFO, _u16CurrentStepSize));
        }
        else if (u8Data==1)
        {
            u16Address=0x0993;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16Data=u8Data;
            u16Address=0x0992;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16Data=(u16Data<<8)|u8Data;
            _u16NextCenterFreq=u16Data;
            //_u16CurrentSymbolRate -- mail box
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE14H,&u8Data);
            u16Data=u8Data;
            bRet &= ReadMailbox(E_DMD_S2_MB_SWUSE14L,&u8Data);
            u16Data=(u16Data<<8)|u8Data;
            _u16CurrentSymbolRate=u16Data;
            // cfo -- mail box
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE15H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE15L,&u8Data);
            u16Data=(u16Data<<8)|u8Data;
            if (u16Data*1000 >= 0x8000)
            {
             u16Data = 0x10000 - u16Data*1000;
                _s16CurrentCFO=-1*u16Data/1000;
            }
            else
            {
                _s16CurrentCFO=u16Data;
            }
            // current step size -- mail box
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE16H,&u8Data);
            u16Data=u8Data;
            bRet&=ReadMailbox(E_DMD_S2_MB_SWUSE16L,&u8Data);
            u16Data=(u16Data<<8)|u8Data;
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
            PRINTE(("Pre Locked CF:%d BW:%d HBW:%d LBW:%d Current CF:%d BW:%d CFO:%d Step:%d\n", _u16LockedCenterFreq, _u16LockedSymbolRate,_u16PreLockedHB, _u16PreLockedLB,  _u16NextCenterFreq-_u16CurrentStepSize, _u16CurrentSymbolRate, _s16CurrentCFO, _u16CurrentStepSize));
        }
#else
        if (u8Data==0)
        {
            u16Address=0x0997;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32Data=u8Data;
            u16Address=0x0996;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32Data=(u32Data<<8)|u8Data;
            u16Address=0x0995;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u32Data=(u32Data<<8)|u8Data;
            _u16ChannelInfoArray[0][_u16ChannelInfoIndex]=((u32Data+500)/1000); //Center Freq
            _u16LockedCenterFreq=((u32Data+500)/1000);


            u16Address=0x0B53;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16Data=u8Data;
            u16Address=0x0B52;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u16Data=(u16Data<<8)|u8Data;
            _u16ChannelInfoArray[1][_u16ChannelInfoIndex]=(u16Data);//Symbol Rate
            _u16LockedSymbolRate=u16Data;
            _u16ChannelInfoIndex++;
            *u8FindNum=_u16ChannelInfoIndex;

        }
#endif
    }
    *u8Progress=100;
    PRINTE(("MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished u8Progress%d u8FindNum %d-\n", *u8Progress, *u8FindNum));

    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_BlindScan_Cancel(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8   u8Data =0;
    MAPI_U16 u16Data =0;

    PRINTE(("MDrv_CofdmDmd_BlindScan_Cancel+\n"));
    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    u16Address=0x0992;
    u16Data=0x0000;
    bRet&=MSB1245_WriteReg2bytes(u16Address, u16Data);
    _u16TunerCenterFreq=0;
    _u16ChannelInfoIndex=0;
    PRINTE(("MDrv_CofdmDmd_BlindScan_Cancel-\n"));

    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_BlindScan_End(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8   u8Data =0;
    MAPI_U16 u16Data =0;

    PRINTE(("MDrv_CofdmDmd_BlindScan_End+\n"));
    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    u16Address=0x0992;
    u16Data=0x0000;
    bRet&=MSB1245_WriteReg2bytes(u16Address, u16Data);
    _u16TunerCenterFreq=0;
    _u16ChannelInfoIndex=0;
    PRINTE(("MDrv_CofdmDmd_BlindScan_End-\n"));

    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_BlindScan_GetChannel(MAPI_U16 u16ReadStart,MAPI_U16* u16TPNum,DTVPROGRAMID_M *pTable)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16  u16TableIndex;

    *u16TPNum=_u16ChannelInfoIndex-u16ReadStart;
    for(u16TableIndex = 0; u16TableIndex < (*u16TPNum); u16TableIndex++)
    {
        pTable[u16TableIndex].u32S2Frequency = _u16ChannelInfoArray[0][_u16ChannelInfoIndex-1];
        pTable[u16TableIndex].u16SymbolRate = _u16ChannelInfoArray[1][_u16ChannelInfoIndex-1];
       PRINTE(("MDrv_CofdmDmd_BlindScan_GetChannel Freq:%ld SymbolRate:%ld\n", pTable[u16TableIndex].u32S2Frequency, pTable[u16TableIndex].u16SymbolRate));
    }
    PRINTE(("MS1245 u16TPNum:%d\n", *u16TPNum));

    return bRet;
}

MAPI_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MAPI_U32 *u32CurrentFeq)
{
    MAPI_BOOL bRet=MAPI_TRUE;

    *u32CurrentFeq=(MAPI_U32) _u16TunerCenterFreq;

    return bRet;
}

#endif
MAPI_BOOL MDrv_DiSEqC_SetTone(MAPI_BOOL bTone1)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address;
    MAPI_U8 u8Data;
    //MAPI_U16 u16WaitCount;
    MAPI_U8 u8ReSet22k;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);

    //DIG_DISEQC_TX1
    u16Address=0x0DC4;
    u8Data=0x01;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

    //DIG_DISEQC_EN
    u16Address=0x0DC0;
    u8Data=0x4E;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    //DIG_DISEQC_FCAR
    u16Address=0x0DCC;
    u8Data=0x88;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    //DIG_DISEQC_MOD
    u16Address=0x0DC2;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8ReSet22k=u8Data;

    if (bTone1==MAPI_TRUE)
    {
       u8Data=0x19;
       bRet&=MSB1245_WriteReg(u16Address, u8Data);
       _u8ToneBurstFlag=1;
    }
    else
    {
       u8Data=0x11;
       bRet&=MSB1245_WriteReg(u16Address, u8Data);
       _u8ToneBurstFlag=2;
    }
    //DIG_DISEQC_TX_EN
    u16Address=0x0DCD;
    u8Data=u8Data&~(0x01);
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data=u8Data|0x3E;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    MsOS_DelayTask(10);
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data=u8Data&~(0x3E);
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    MsOS_DelayTask(1);
    u8Data=u8Data|0x01;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

    MsOS_DelayTask(100);//(100)
    //For ToneBurst 22k issue.
    u16Address=0x0DC2;                                                          //For ToneBurst 22k issue.
    u8Data=u8ReSet22k;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
MAPI_BOOL MDrv_DiSEqC_SetLNBOut(MAPI_BOOL bLow)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);

    u16Address=0x0DC2;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if (bLow==MAPI_TRUE)
    {
        u8Data=(u8Data|0x40);
    }
    else
    {
        u8Data=(u8Data&(~0x40));
    }
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
MAPI_BOOL MDrv_DiSEqC_GetLNBOut(MAPI_BOOL* bLNBOutLow)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);

    u16Address=0x0DC2;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if( (u8Data&0x40)==0x40)
    {
        * bLNBOutLow=MAPI_TRUE;
    }
    else
    {
        * bLNBOutLow=MAPI_FALSE;
    }
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
MAPI_BOOL MDrv_DiSEqC_Set22kOnOff(MAPI_BOOL b22kOn)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8   u8Data =0;

    PRINTE(("[Mstar] b22kOn: %d\n",b22kOn));

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
    u16Address=0x0DC2;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if (b22kOn==MAPI_TRUE)
    {
        u8Data=(u8Data & 0xc7);
        u8Data=(u8Data|0x08);
    }
    else
    {
        u8Data=(u8Data & 0xc7);
    }
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

    //re-check
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    PRINTE(("[Mstar] 22k tone reg: 0x%x\n",u8Data));

    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
MAPI_BOOL MDrv_DiSEqC_Get22kOnOff(MAPI_BOOL* b22kOn)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8   u8Data =0;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);

    u16Address=0x0DC2;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if ((u8Data&0x08)==0x08)
    {
        *b22kOn=MAPI_TRUE;
    }
    else
    {
        *b22kOn=MAPI_FALSE;
    }
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
MAPI_BOOL MDrv_DiSEqC_SendCmd(MAPI_U8* pCmd,MAPI_U8 u8CmdSize)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Address =0;
    MAPI_U8   u8Data =0;
    MAPI_U8   u8Index =0;
    MAPI_U16 u16WaitCount =0;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
//<<jc@150129
printf("\n [%s,%s,%d] \n",__FILE__,__FUNCTION__,__LINE__);
#if ( WATCH_DOG == ENABLE )//jc@150310
				 MDrv_Sys_DisableWatchDog();
#endif

    do
    {
        u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        MsOS_DelayTask(1);
        u16WaitCount++;
    }while(((u8Data&0x10)==0x10)&&(u16WaitCount < MSB1245_DEMOD_WAIT_TIMEOUT)) ;
#if ( WATCH_DOG == ENABLE )//jc@150310
			  MDrv_Sys_EnableWatchDog();
#endif

    if (u16WaitCount >= MSB1245_DEMOD_WAIT_TIMEOUT)
    {
        PRINTE(("MSB124X DiSEqC Send Command Busy!!!\n"));
        return FALSE;
    }
    PRINTE(("\r\n MDrv_DiSEqC_SendCmd++++"));
    for (u8Index=0; u8Index < u8CmdSize; u8Index++)
    {
        u16Address=0x0DC4+u8Index;
        u8Data=*(pCmd+u8Index);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);
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
    bRet&=MSB1245_WriteReg(u16Address, u8Data);
    MsOS_DelayTask(10);
    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data=u8Data|0x10;
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

#if 0       //For Unicable command timing,mick
    u16WaitCount=0;
    do
    {
        u16Address=0x0990;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
         MsOS_DelayTask(1);
         u16WaitCount++;
    }while(((u8Data&0x10)==0x10)&&(u16WaitCount < MSB1245_DEMOD_WAIT_TIMEOUT)) ;

    if (u16WaitCount >= MSB1245_DEMOD_WAIT_TIMEOUT)
    {
        PRINTE(("MSB1245 DiSEqC Send Command Busy!!!\n"));
        //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
        return MAPI_FALSE;
    }
#endif      //For Unicable command timing,mick

    PRINTE(("\r\n MDrv_DiSEqC_SendCmd----"));
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
MAPI_BOOL MDrv_Demod_Open(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;

    return bRet;
}
MAPI_BOOL MDrv_Demod_Close(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;

    return bRet;
}
MAPI_BOOL MDrv_Demod_Reset(void)
{
    MAPI_BOOL bRet=MAPI_TRUE;

    return bRet;
}
MAPI_BOOL MDrv_Demod_TsOut(MAPI_BOOL bEnable)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    UNUSED(bEnable);
    return bRet;
}

MAPI_BOOL MDrv_Demod_SetBW(MAPI_U32 u32BW)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    UNUSED(u32BW);
    return bRet;
}
MAPI_BOOL MDrv_Demod_GetBW(MAPI_U32 *pu32BW)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    UNUSED(pu32BW);
    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_GetLock(MAPI_BOOL *pbLock)
{
    MAPI_BOOL bRet=MAPI_TRUE;


    *pbLock=MSB1245_DTV_GetLock();
    if(((*pbLock)==MAPI_TRUE) && (_bDemodLockFlag==MAPI_FALSE))
    {
        _u32DemodLockTime= MsOS_GetSystemTime() - _u32DemodLockTime;
        _bDemodLockFlag=MAPI_TRUE;
        PRINTE(("Demod Lock Time %ld (ms)\n", _u32DemodLockTime));
    }
    else if(((*pbLock)==MAPI_FALSE)&&(_bDemodLockFlag==MAPI_TRUE))
    {
         _u32DemodLockTime= MsOS_GetSystemTime();
        _bDemodLockFlag=MAPI_FALSE;
    }
    PRINTE(("MSB1245 MDrv_Demod_GetLock 0x%x\n", *pbLock));

    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_GetSNR(MAPI_U32 *pu32SNR)//NDA_SNR
{
    MAPI_BOOL bRet=MAPI_TRUE;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
    *pu32SNR=(MAPI_U32) MSB1245_DTV_GetSignalNoiseRatio();
    PRINTE(("MSB1245 SNR %ld\n", *pu32SNR));
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_GetBER(float *pfBER)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16 u16Data=0;

    u16Data=MSB1245_DTV_GetSignalQuality(_bDemodType);
    *pfBER=(float)u16Data;
    PRINTE(("MSB1245 BER %f\n", *pfBER));

    return bRet;
}
MAPI_BOOL MDrv_CofdmDmd_GetPWR(MS_S32 *pfSignal)
{//-1.2~-92.2 dBm
    MAPI_BOOL bRet=MAPI_TRUE;
    float  fCableLess;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);

    //979MHz, 22Ms/s,DVB-S, QPSK¡B2/3 No Phose noise,No CN
    fCableLess = MSB1245_DTV_GetSignalStrength();

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
    fCableLess = (-1)*(fCableLess/10);
    *pfSignal=fCableLess;
    PRINTE(("MSB1245 Signal Level %f\n", *pfSignal));

    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
//mick
#if 0
MAPI_BOOL MDrv_CofdmDmd_GetSignalBar(MAPI_U16 *pu16SignalBar)
{//0-100

    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16  u16Address =0;
    MAPI_U8   u8Data =0, u8Data2 = 0;
    MAPI_U8   _u8_DVBS2_CurrentConstellationLocal = 0, _u8_DVBS2_CurrentCodeRateLocal = 0;
    MS_U32   ch_power_db=0, ch_power_db_rel=0;

    bRet &= MDrv_CofdmDmd_GetPWR(&ch_power_db);

    if (_bDemodType==MAPI_FALSE)//S
    {
        float fDVBS_SSI_Pref[]=
        {   //0,       1,       2,       3,       4
            -78.9,   -77.15,  -76.14,  -75.19,  -74.57,//QPSK
        };
        u16Address = 0x1C84;            //DVBSFEC_VITERBI_CODE_RATE
        bRet &= MSB1245_ReadReg(u16Address, &u8Data);
        _u8_DVBS2_CurrentCodeRateLocal = (u8Data & 0x07);
        ch_power_db_rel = ch_power_db - fDVBS_SSI_Pref[_u8_DVBS2_CurrentCodeRateLocal];
    }
    else
    {
        float fDVBS2_SSI_Pref[][11]=
        {   //  0,    1,       2,       3,       4,       5,       6,       7,       8,        9,       10
            //1/4,    1/3,     2/5,     1/2,     3/5,     2/3,     3/4,     4/5,     5/6,      8/9,     9/10
            {-85.17, -84.08,  -83.15,  -81.86,  -80.63,  -79.77,  -78.84,  -78.19,  -77.69,   -76.68,  -76.46}, //QPSK
            {   0.0,    0.0,     0.0,     0.0,  -77.36,  -76.24,  -74.95,     0.0,  -73.52,   -72.18,  -71.84}  //8PSK
        };

        u16Address = 0x1BD7;
        bRet &= MSB1245_ReadReg(u16Address, &u8Data);
        _u8_DVBS2_CurrentCodeRateLocal = (u8Data & 0x3C)>>2;

        u16Address = 0x1BD7;
        bRet &= MSB1245_ReadReg(u16Address, &u8Data);//INNER_PLSCDEC_DEBUG_OUT1
        u16Address = 0x1BD6;
        bRet &= MSB1245_ReadReg(u16Address, &u8Data2);//INNER_PLSCDEC_DEBUG_OUT0

        if(((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x00))
        {
            _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_QPSK;
        }
        else if (((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x80))
        {
            _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_8PSK;//8PSK
        }
        else if (((u8Data & 0x03)==0x02) && ((u8Data2 & 0x80)==0x00))
        {
            _u8_DVBS2_CurrentConstellationLocal = DEMOD_SAT_16APSK;//16APSK
        }

        ch_power_db_rel = ch_power_db - fDVBS2_SSI_Pref[_u8_DVBS2_CurrentConstellationLocal][_u8_DVBS2_CurrentCodeRateLocal];

    }

    if(ch_power_db_rel <= -15.0f)
        {*pu16SignalBar = 0;}
    else if (ch_power_db_rel <= 0.0f)
        {*pu16SignalBar = (MAPI_U16)(2.0f/3 * (ch_power_db_rel+15.0f));}
    else if (ch_power_db_rel <= 20.0f)
        {*pu16SignalBar = (MAPI_U16)(4.0f * ch_power_db_rel + 10.0f);}
    else if (ch_power_db_rel <= 35.0f)
        {*pu16SignalBar = (MAPI_U16)(2.0f/3 * (ch_power_db_rel-20.0f) + 90.0);}
    else
        {*pu16SignalBar = 100;}

    PRINTE(("MSB1245 Signal Bar %u\n", *pu16SignalBar));

    return bRet;
}
#endif
MAPI_BOOL MDrv_Demod_Config(MAPI_U8 *pRegParam)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    UNUSED(pRegParam);
    return bRet;
}

MAPI_BOOL MDrv_CofdmDmd_Restart(CofdmDMD_Param* pParam)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    MAPI_U16  u16Address =0;
    MAPI_U8   u8Data =0;
    MAPI_U16  u16SymbolRate =0;
    MAPI_U16  __attribute__ ((unused)) u16CenterFreq =0;
    MAPI_U8   u8counter = 0;

    u16SymbolRate=(pParam->u32SymbolRate/1000);
    u16CenterFreq=pParam->u32TunerFreq;
    PRINTE(("MSB1245 Mdrv_Demod_Restart+ Fc:%d MHz SymbolRate %d KS/s\n", u16CenterFreq, u16SymbolRate));
    MSB1245_IIC_Bypass_Mode(MAPI_TRUE);
    printf("--%s():%d\n", __FUNCTION__, __LINE__);
    bRet&=MSB1245_SetFrequency(pParam->u32TunerFreq,(pParam->u32SymbolRate/1000)); // (MHz, KS/s)
    MSB1245_IIC_Bypass_Mode(MAPI_FALSE);
    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    bRet&=MSB1245_WriteReg(u16Address,u8Data);

   //MCU reset
    u16Address=0x0B32;//MCU reset
    u8Data = 0x03;
    bRet&=MSB1245_WriteReg(u16Address,u8Data);
    MsOS_DelayTask(1);
    u8Data = 0x00;
    bRet&=MSB1245_WriteReg(u16Address,u8Data);
    MsOS_DelayTask(10);
	
    u16Address=0x0B52;
    u8Data=(u16SymbolRate&0xFF);
    bRet&=MSB1245_WriteReg(u16Address,u8Data);
    u16Address=0x0B53;
    u8Data=((u16SymbolRate>>8)&0xFF);
    bRet&=MSB1245_WriteReg(u16Address,u8Data);

    //ADCPLL IQ swap
    if(MSB1245_ADCPLL_IQ_SWAP==1)
    {
        u16Address=0x0A03;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data|=(0x10);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);
        PRINTE(("[Mstar]MSB1245_ADCPLL_IQ_SWAP==1 \n"));

         //re-check
        u16Address=0x0A03;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        PRINTE(("[Mstar]BlindScan_Start_  u8Data=0x%x \n",u8Data));
    }
    else if(MSB1245_ADCPLL_IQ_SWAP==0)
    {
        u16Address=0x0A03;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x10);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);
        PRINTE(("[Mstar]BlindScan_Start_MSB1245_ADCPLL_IQ_SWAP==0 \n"));

        //re-check
        u16Address=0x0A03;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        PRINTE(("[Mstar]BlindScan_Start_  u8Data=0x%x \n",u8Data));
    }

//Configure Serial/Parallel mode for TS output
    u16Address=0x2A40;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if(S_TS_Output_VAL) //Serial Mode
      u8Data|=0x01;
    else               //Parallel Mode
      u8Data&=~(0x01);
    bRet&=MSB1245_WriteReg(u16Address,u8Data);

    u16Address=0x0990;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    u8Data&=0xF0;
    u8Data|=0x01;
    bRet&=MSB1245_WriteReg(u16Address,u8Data);

    u8counter = 6;
    bRet&=MSB1245_ReadReg(u16Address,&u8Data);
    while( ((u8Data&0x01) == 0x00) && (u8counter != 0) )
    {
        printf("0x0990=0x%x, bRet=%d, u8counter=%d\n",u8Data,bRet,u8counter);
        u8Data|=0x01;
        bRet&=MSB1245_WriteReg(u16Address,u8Data);
        bRet&=MSB1245_ReadReg(u16Address,&u8Data);
        u8counter--;
    }

    if((u8Data&0x01)==0x00)
    {
        bRet = FALSE;
    }
    bRet&=MSB1245_DiSEqC_Init();
    PRINTE(("MSB1245 MDrv_Demod_Restart-\n"));

    return bRet;
}
MAPI_BOOL MDrv_Demod_SetMode(Demod_Mode* pMode)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    UNUSED(pMode);
    return bRet;
}

MAPI_BOOL MDrv_Demod_SetOutoutPath(DEMOD_INTERFACE_MODE path)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    UNUSED(path);
    return bRet;
}

MAPI_BOOL MDrv_Demod_UnicableAGCCheckPower(MAPI_BOOL pbAGCCheckPower)
{
    MAPI_BOOL bRet = MAPI_TRUE;
    MAPI_U16 u16Address;
    MAPI_U8 u8Data;

    u16Address = 0x0991;
    u8Data = 0x00;
    bRet &= MSB1245_WriteReg(u16Address,u8Data);

    u16Address = 0x0990;
    bRet &= MSB1245_ReadReg(u16Address, &u8Data);
    u8Data &= 0xFE;   //clean bit0
    bRet &= MSB1245_WriteReg(u16Address,u8Data);

    if (pbAGCCheckPower == MAPI_FALSE)//0
    {
        u16Address = 0x0991;//[TOP_WR_DBG_91]
        bRet &= MSB1245_ReadReg(u16Address, &u8Data);
        u8Data &= 0xFE;           //bit0=0
        bRet &= MSB1245_WriteReg(u16Address, u8Data);
        //printf("CMD=MAPI_FALSE==============================\n");
    }
    else
    {
        u16Address = 0x0991;//[TOP_WR_DBG_91]
        bRet &= MSB1245_ReadReg(u16Address, &u8Data);
        u8Data |= 0x01;           //bit0=1
        bRet &= MSB1245_WriteReg(u16Address, u8Data);
        //printf("CMD=MAPI_TRUE==============================\n");
    }

    u16Address = 0x0990;
    bRet &= MSB1245_ReadReg(u16Address, &u8Data);
    u8Data &= 0xF0;
    u8Data |= 0x01;
    bRet &= MSB1245_WriteReg(u16Address,u8Data);
    MsOS_DelayTask(500);


    u16Address = 0x0991;        //[TOP_WR_DBG_91]
    bRet &= MSB1245_ReadReg(u16Address, &u8Data);
    u8Data &= 0x80;             //Read bit7
    if (u8Data == 0x80)
    {
        u16Address = 0x0990;
        u8Data = 0x00;
        bRet &= MSB1245_WriteReg(u16Address,u8Data);
        u16Address = 0x0991;
        u8Data = 0x00;
        bRet &= MSB1245_WriteReg(u16Address,u8Data);
        return MAPI_TRUE;
    }
    else
    {
        u16Address = 0x0990;
        u8Data = 0x00;
        bRet &= MSB1245_WriteReg(u16Address,u8Data);
        u16Address = 0x0991;
        u8Data = 0x00;
        bRet &= MSB1245_WriteReg(u16Address,u8Data);
        return MAPI_FALSE;
    }
}

//----------------------------------------------------------------------------------------
//mick
MAPI_BOOL MDrv_Demod_GetModulationType(MAPI_U8* u8Constellation)
{
    MAPI_U16 u16Address;
    MAPI_U8  u8Data = 0;
    MAPI_BOOL bRet=TRUE;


    u16Address=0x1B80;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);

    if (u8Data&0x01)    //S
    {
        *u8Constellation=0;//QPSK
    }
    else                //S2
    {
        u16Address=0x1B96;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);

        if((u8Data&0x0F)==0x02)         //QPSK
            *u8Constellation=0;
        else if((u8Data&0x0F)==0x03)    //8PSK
            *u8Constellation=1;
        else if((u8Data&0x0F)==0x04)         //16APSK
            *u8Constellation=2;
        else if((u8Data&0x0F)==0x05)    //32APSK
            *u8Constellation=3;
    }

    return bRet;
}

MAPI_BOOL MDrv_Demod_GetModulationType_Lock(MAPI_U8* u8Constellation)
{
    MAPI_U16 u16Address;
    MAPI_U8  u8Data = 0,u8Data2 = 0;
    MAPI_BOOL bRet=TRUE;

    u16Address=0x1B80;
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);

    if (u8Data&0x01)    //S
    {
        *u8Constellation=0;             //QPSK
    }
    else                //S2
    {
        u16Address = 0x1BD7;
        bRet &= MSB1245_ReadReg(u16Address, &u8Data);   //INNER_PLSCDEC_DEBUG_OUT1
        u16Address = 0x1BD6;
        bRet &= MSB1245_ReadReg(u16Address, &u8Data2);  //INNER_PLSCDEC_DEBUG_OUT0

        if(((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x00))
        {
            *u8Constellation = 0;   //QPSK
        }
        else if (((u8Data & 0x03)==0x01) && ((u8Data2 & 0x80)==0x80))
        {
            *u8Constellation = 1;   //8PSK
        }
        else if (((u8Data & 0x03)==0x02) && ((u8Data2 & 0x80)==0x00))
        {
            *u8Constellation = 2;   //16APSK
        }
    }

    return bRet;
}

MAPI_BOOL MDrv_DiSEqC_SetTxToneMode(MAPI_BOOL bTxTone22kOff)
{
    MAPI_BOOL bRet=TRUE;
    MAPI_U16 u16Address;
    MAPI_U8   u8Data = 0;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);

    u16Address=0x0D57;                          //DIG_DBG_7 [1]: diseqc tx tone mode,ECO U03
    bRet&=MSB1245_ReadReg(u16Address, &u8Data);
    if (bTxTone22kOff==TRUE)
    {
        u8Data=(u8Data|0x02);                   //1: without 22K.
    }
    else
    {
        u8Data=(u8Data&(~0x02));                //0: with 22K.
    }
    bRet&=MSB1245_WriteReg(u16Address, u8Data);

    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
//======================================================================================
//---------------------------------------------------------------------
//---------------------------------------------------------------------
MAPI_BOOL MSB1245_GPIO_SetLevel(MAPI_U8 u8Pin, MAPI_BOOL bLevel)
{
    MAPI_BOOL bRet = MAPI_FALSE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    if (u8Pin==13)
    {
        u16Address=0x0955;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x20);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //set RF to GPIO
        u16Address=0x09CE;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x10);//u8Data|=0x10;
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //GPIO output enable
        if (bLevel==MAPI_FALSE)
        {
            u16Address=0x09CC;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u8Data|=0x10;
            bRet&=MSB1245_WriteReg(u16Address, u8Data); //Set level to high
        }
        else
        {
            u16Address=0x09CC;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u8Data&=(~0x10);
            bRet&=MSB1245_WriteReg(u16Address, u8Data); //Set level to high
        }
    }
    else if (u8Pin==11)
    {
        u16Address=0x095C;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x01);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //set TS_ERR to GPIO
        u16Address=0x09C3;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x08);//u8Data|=0x08;
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //GPIO output enable
        if (bLevel==MAPI_FALSE)
        {
            u16Address=0x09C3;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u8Data|=0x08;
            bRet&=MSB1245_WriteReg(u16Address, u8Data); //Set level to high
        }
        else
        {
            u16Address=0x09C3;
            bRet&=MSB1245_ReadReg(u16Address, &u8Data);
            u8Data&=(~0x08);
            bRet&=MSB1245_WriteReg(u16Address, u8Data); //Set level to high
        }
    }
    else
    {
        return MAPI_FALSE;
    }
    return bRet;
}
MAPI_BOOL MSB1245_GPIO_GetLevel(MAPI_U8 u8Pin, MAPI_BOOL *bLevel)
{
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;
    MAPI_BOOL bRet =MAPI_FALSE;
    if (u8Pin==13)
    {
        u16Address=0x0955;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x20);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //set RF to GPIO

        u16Address=0x09CE;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x10);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //GPIO output disable

        u16Address=0x09D0;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        if ((u8Data&0x10)==0x10)
        {
            *bLevel=MAPI_TRUE;
        }
        else
        {
            *bLevel=MAPI_FALSE;
        }
    }
    else if (u8Pin==11)
    {
        u16Address=0x095C;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x01);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //set TS_ERR to GPIO

        u16Address=0x09C1;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x08);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //GPIO output disable

        u16Address=0x09C5;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        if ((u8Data&0x08)==0x08)
        {
            *bLevel=MAPI_TRUE;
        }
        else
        {
            *bLevel=MAPI_FALSE;
        }
    }
    else
    {
        return MAPI_FALSE;
    }
    return bRet;
}

MAPI_BOOL  MSB1245_GPIO_Disable(MAPI_U8 u8Pin)
{
    MAPI_BOOL bRet =MAPI_FALSE;
    MAPI_U16 u16Address =0;
    MAPI_U8 u8Data =0;

    if (u8Pin==13)
    {
        u16Address=0x0955;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x20);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //set RF to GPIO

        u16Address=0x09CE;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x10);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //GPIO output disable

    }
    else if (u8Pin==11)
    {
        u16Address=0x095C;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x01);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //set TS_ERR to GPIO

        u16Address=0x09C1;
        bRet&=MSB1245_ReadReg(u16Address, &u8Data);
        u8Data&=(~0x08);
        bRet&=MSB1245_WriteReg(u16Address, u8Data);    //GPIO output disable
    }
    else
    {
        return MAPI_FALSE;
    }
    return bRet;
}

#if 0
MAPI_BOOL DeviceDemodCreate()
{
    mapi_demodulator *pMapiDemod;
    pMapiDemod = mapi_interface::Get_mapi_demod_extend2();
    mapi_dish* pMapiDish;
    pMapiDish = mapi_interface::Get_mapi_dish();
    //Public:Common
    pMapiDemod->stMapiDemodulatorFun.Connect = Connect;
    pMapiDemod->stMapiDemodulatorFun.Disconnect = Disconnect;
    pMapiDemod->stMapiDemodulatorFun.Reset = Reset;
    pMapiDemod->stMapiDemodulatorFun.IIC_Bypass_Mode = IIC_Bypass_Mode;
    pMapiDemod->stMapiDemodulatorFun.Power_On_Initialization = Power_On_Initialization;
    pMapiDemod->stMapiDemodulatorFun.Set_PowerOn = DEMOD_MSB1245_Set_PowerOn;
    pMapiDemod->stMapiDemodulatorFun.Set_PowerOff = DEMOD_MSB1245_Set_PowerOff;
    pMapiDemod->stMapiDemodulatorFun.Active = Active;
    pMapiDemod->stMapiDemodulatorFun.GetCurrentDemodulatorType = GetCurrentDemodulatorType;
    pMapiDemod->stMapiDemodulatorFun.ExtendCmd = ExtendCmd;

    //Public:DTV
    pMapiDemod->stMapiDemodulatorFun.DTV_GetSNR = DTV_GetSNR;
    pMapiDemod->stMapiDemodulatorFun.DTV_GetBER = DTV_GetBER;
    pMapiDemod->stMapiDemodulatorFun.DTV_GetPacketErr = DTV_GetPacketErr;
    pMapiDemod->stMapiDemodulatorFun.DTV_GetSignalQuality = DTV_GetSignalQuality;
    pMapiDemod->stMapiDemodulatorFun.DTV_GetSignalStrength = DTV_GetSignalStrength_Percent;//DTV_GetSignalStrength;
    pMapiDemod->stMapiDemodulatorFun.DTV_Serial_Control = DTV_Serial_Control;
#if (ENABLE_S2 == 1)
    //Public:DTV-DVB-S
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_SetFrequency = DTV_DVB_S_SetFrequency;
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_GetLockStatus = DTV_DVB_S_GetLockStatus;
    //blind scan
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_BlindScan_Init = DTV_DVB_S_BlindScan_Init;
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_BlindScan_ScanNextFreq = DTV_DVB_S_BlindScan_ScanNextFreq;
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_BlindScan_GetFoundTP = DTV_DVB_S_BlindScan_GetFoundTP;
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_BlindScan_Cancel = DTV_DVB_S_BlindScan_Cancel;
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_BlindScan_End = DTV_DVB_S_BlindScan_End;
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_BlindScan_GetStatus = DTV_DVB_S_BlindScan_GetStatus;
    pMapiDemod->stMapiDemodulatorFun.DTV_DVB_S_BlindScan_GetScanFreq = DTV_DVB_S_BlindScan_GetScanFreq;
     //
    pMapiDish->stMapiDishFun.DTV_DVB_S_SetToneBurst = DTV_DVB_S_SetToneBurst;
    pMapiDish->stMapiDishFun.DTV_DVB_S_SendDiSEqCCmd = DTV_DVB_S_SendDiSEqCCmd;
    // pMapiDish->stMapiDishFun.DTV_DVB_S_SetLNBPower = DTV_DVB_S_SetLNBPower;

    device_dish::DeviceDishCreate();
    pMapiDish->stMapiDishFun.DTV_DVB_S_Set22KOnOff = DTV_DVB_S_Set22KOnOff;
    pMapiDish->stMapiDishFun.DTV_DVB_S_Get22KStatus = DTV_DVB_S_Get22KStatus;

    _s32_Demod_DVBS2_Mutex = MsOS_CreateMutex(E_MSOS_FIFO, (char *)"Mutex DVBS2", MSOS_PROCESS_SHARED);
    _s32_Demod_DVBS2_RW_Mutex = MsOS_CreateMutex(E_MSOS_FIFO, (char *)"Mutex DVBS2RW", MSOS_PROCESS_SHARED);
    _s32_Demod_DVBS2_RW2_Mutex = MsOS_CreateMutex(E_MSOS_FIFO, (char *)"Mutex DVBS2RW2", MSOS_PROCESS_SHARED);
#endif
    return MAPI_TRUE;
}
#endif
#if 0 //(STR_ENABLE == 1)
MAPI_BOOL SuspendDeInit()
{
    return MAPI_TRUE;
}

MAPI_BOOL ResumeInit()
{
    u8DeviceBusy = 0;
    u8PowerOnInit = 1;
    _bInited = FALSE;

    return MAPI_TRUE;
}
#endif

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL Demod_MSB1245_Connect(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    if (u8DeviceBusy == 1)
    {
        return MAPI_FALSE;
    }

    if(u8PowerOnInit == 0)
    {
        DEMOD_MSB1245_Set_PowerOn();
    }
    m_enCurrentDemodulator_Type = enDemodType;
    u8PowerOnInit = 0;
    u8DeviceBusy = 1;

    return MAPI_TRUE;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL Disconnect(void)
{
    u8DeviceBusy = 0;

    DEMOD_MSB1245_Set_PowerOff();
    return MAPI_TRUE;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void Reset(void)
{
}
MAPI_BOOL IIC_Bypass_Mode(MAPI_BOOL enable)
{
    return MSB1245_IIC_Bypass_Mode(enable);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL Power_On_Initialization(void)
{
    return MDrv_Demod_Init();
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL DEMOD_MSB1245_Set_PowerOn(void)
{
    return MDrv_Demod_StandBy(MAPI_FALSE);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL DEMOD_MSB1245_Set_PowerOff(void)
{
    return MDrv_Demod_StandBy(MAPI_TRUE);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL Active(MAPI_BOOL bEnable)
{
    UNUSED(bEnable);
    return MAPI_TRUE;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
EN_DEVICE_DEMOD_TYPE GetCurrentDemodulatorType(void)
{
    return m_enCurrentDemodulator_Type;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL ExtendCmd(MAPI_U8 SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void *pvParam3)
{
    MAPI_BOOL bRet = MAPI_TRUE;
    MS_U8 u8Data = 0;
    // DVB-S/S2 Tri-State setting
    // MAPI_FALSE(0) : Disable Tri-State, enable DVB-S/S2 output
    // MAPI_TRUE(1) : Enable Tri-State, disable DVB-S/S2 output
    UNUSED(u32Param2);

    if(SubCmd == 0x81)
    {
        if(u32Param1 == MAPI_TRUE)
        {
            printf("1245 demod extend command 0x81 close S TS pad\n");
            bRet &= MSB1245_ReadReg(0x0990, &u8Data);
	     u8Data&=0xFE;
	     bRet &= MSB1245_WriteReg(0x0990, u8Data);
            bRet &= MSB1245_WriteReg2bytes(0x0900+(0x2d)*2, 0x0000);
        }
        else
        {
            bRet &= MSB1245_WriteReg2bytes(0x0900+(0x2d)*2, 0x00ff);
        }
    }

    // Pin20 DISEQC_OUT
    // MAPI_FALSE(0), DISABLE (Set HZ)
    // MAPI_TRUE(1),  ENABLE
    if(SubCmd == 0x82)
    {
        u8Data = 0;
        if(u32Param1 == MAPI_TRUE)
        {
            bRet&=MSB1245_ReadReg(0x0d00+(0x60)*2, &u8Data);
            u8Data &= (0xff-0x01);
            bRet&=MSB1245_WriteReg(0x0d00+(0x60)*2, u8Data);
        }
        else
        {
            bRet&=MSB1245_ReadReg(0x0d00+(0x60)*2, &u8Data);
            u8Data |= 0x01;
            bRet&=MSB1245_WriteReg(0x0d00+(0x60)*2, u8Data);
        }
    }
    // set TS serial mode, TS data swap, TS CLK inverse
    // Para1. for DVBSS2 TS output mode
    if (SubCmd == 0x87)
    {
        printf("DVBSS2 TS out configuration:\n TS serial mode %d \n ",(MAPI_U8)u32Param1);
        S_TS_Output_VAL = (MAPI_U8)u32Param1;
    }
   // TS Clk invert setting
    else if (SubCmd == 0x89)
    {
        printf("\n\n DVBSS2 TS out configuration: TS CLK inv mode %d\n",(MAPI_U8)u32Param1);
        u8Data = 0;
        bRet&=MSB1245_ReadReg(0x0924, &u8Data);

      //  printf("\n\n\n u8Data:0x%x[%s,%s,%d] \n",u8Data,__FILE__,__FUNCTION__,__LINE__);

        if(u32Param1) //enable  demod clk invert
        {
          u8Data|=0x20;
        }
        else               //disable
        {
          u8Data&=~(0x20);
        }

        bRet &= MSB1245_WriteReg(0x0924, u8Data);
        if(bRet==0)
          printf("Configure TS CLK inv Fail!!");

    }


    // channel scan extend indicator
    if(SubCmd == 0x10)
    {
        MAPI_U16 u16reg = 0;
        MAPI_U16 u16Address = 0x0990;
        if (MSB1245_ReadReg2bytes(u16Address, &u16reg)== MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
        if ((u16reg&0x02)!=(0x02) &&
            (msAPI_Timer_DiffTimeFromNow(_u32LocktimeStart) > TR_TIME_OUT_WITH_FIX_SYMBOL_RATE) &&
            (_u32CurrentSR != 0)
           )
        {
            // dont extend(skip)
            *((MAPI_U8*)pvParam3) = 0;
        }
        else
        {
            // extend
            *((MAPI_U8*)pvParam3) = 1;
        }
        // printf("S_extend_flag = %d\n",*((MAPI_U8*)pvParam3));
    }
    return MAPI_TRUE;
}


//##########################################################################################################
//##########################################################################################################
//########################################  Public:DTV Implementation ##################################
//##########################################################################################################
//##########################################################################################################
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
EN_FRONTEND_SIGNAL_CONDITION DTV_GetSNR(void)
{
    EN_FRONTEND_SIGNAL_CONDITION eRet = E_FE_SIGNAL_NO;
    MAPI_U32 u32SNR = 0;
    if(MDrv_CofdmDmd_GetSNR(&u32SNR) == MAPI_TRUE)
    {
        // TODO
        // *fSNR=u32SNR;
        if (u32SNR > 30)
            eRet = E_FE_SIGNAL_VERY_STRONG;
        else if (u32SNR > 25)
            eRet = E_FE_SIGNAL_STRONG;
        else if (u32SNR > 20)
            eRet = E_FE_SIGNAL_MODERATE;
        else if (u32SNR > 15)
            eRet = E_FE_SIGNAL_WEAK;
        else
            eRet = E_FE_SIGNAL_NO;
    }
    return eRet;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_U32 DTV_GetBER(void)
{
#if 0
    float pfBER;
    if(MDrv_Demod_GetBER(&pfBER))
    {
        // ... TODO
        *fBER=pfBER;
    }
#endif
    return 0;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL DTV_GetPacketErr(MAPI_U16 *pu16BitErr)
{
    MAPI_BOOL status = MAPI_TRUE;
    MAPI_U8   reg = 0;
    MAPI_U16  PktErr=0, PRD=0, PER=0;

    if (_bDemodType == MAPI_FALSE)
    {
       status &= MSB1245_ReadReg(0x1132, &reg);
       reg|=0x80;
       status &= MSB1245_WriteReg(0x1132, reg); //freeze

       // bank 17 0x18 [7:0] reg_bit_err_sblprd_7_0  [15:8] reg_bit_err_sblprd_15_8
       status &= MSB1245_ReadReg(0x1130, &reg);
       PRD = reg;
       status &= MSB1245_ReadReg(0x1131, &reg);
       PRD= (reg<<8)| PRD;

       if (PRD == 0)    // avoide division by 0
           PRD++;

       // bank 17 0x1F [7:0] reg_uncrt_pkt_num_7_0 [15:8] reg_uncrt_pkt_num_15_8
       status &= MSB1245_ReadReg(0x113E, &reg);
       PER = reg;
       status &= MSB1245_ReadReg(0x113F, &reg);
       PER= (reg<<8)| PER; //Packet error

       status &= MSB1245_ReadReg(0x1132, &reg);
       reg&=(~0x80);
       status &= MSB1245_WriteReg(0x1132, reg); //unfreeze
       PktErr = (float)PER/(128*PRD);

       *pu16BitErr = PER;
       // printf("[dvbs]GetPktErr = %d\n",PktErr);
    }
    else if(_bDemodType == MAPI_TRUE)
    {
       status &= MSB1245_ReadReg(0x2604, &reg);
       reg|=0x01;
       status &= MSB1245_WriteReg(0x2604, reg); //freeze

       status &= MSB1245_ReadReg(0x264C, &reg);
       PER= reg;
       status &= MSB1245_ReadReg(0x264D, &reg);
       PER= (reg<<8)| PER;    //E-flag, error

       status &= MSB1245_ReadReg(0x2604, &reg);
       reg&=(~0x01);
       status &= MSB1245_WriteReg(0x2604, reg); //unfreeze

       *pu16BitErr = PktErr;
       // printf("[dvbs2]GetPktErr = %d\n",PktErr);
    }
    else
    {
       *pu16BitErr = 65535;
    }
    return status;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_U16 DTV_GetSignalQuality(void)
{
    //DEMOD_MS_FE_CARRIER_INFO       demod_info;
    MAPI_U8     u8_gSignalQualityValue;
    //ExtendCmd(0xDD, 0 ,0, &demod_info);

    u8_gSignalQualityValue = MSB1245_DTV_GetSignalQuality(_bDemodType);

    if ((_u16_packetError >= 1) && (u8_gSignalQualityValue > 30))           //Average
    {
        u8_gSignalQualityValue = 30;
    }
    else if ((_u16_packetError >= 1) && (u8_gSignalQualityValue > 10))      //Poor
    {
        u8_gSignalQualityValue = 10;
    }

    return u8_gSignalQualityValue;//MSB1245_DTV_GetSignalQuality(_bDemodType);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_U16 DTV_GetSignalStrength(void)
{//+12~922 Value
    return MSB1245_DTV_GetSignalStrength();
}
#if 0
MAPI_U16 DTV_GetSignalStrength_Percent(void)
{
    MAPI_U16 u16SignalStrength_Percent;         //0~100H
    MDrv_CofdmDmd_GetSignalBar(&u16SignalStrength_Percent);

    return u16SignalStrength_Percent;
}
#endif
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MAPI_BOOL DTV_Serial_Control(MAPI_BOOL bEnable)
{
    return MDrv_CofdmDmd_SetTsSerial(bEnable);
}

#if (ENABLE_S2 == 1)
MAPI_BOOL DTV_DVB_S_SetFrequency(MAPI_U32 u32Frequency, MAPI_U32 u32SymbolBitrate)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    CofdmDMD_Param pParam;

    pParam.u32TunerFreq= u32Frequency;
    pParam.u32SymbolRate = u32SymbolBitrate;
    _u32CurrentFreq=u32Frequency;
    _u32CurrentSR=u32SymbolBitrate;
    // _u32LocktimeStart=MsOS_GetSystemTime();
    _u32LocktimeStart = MsOS_GetSystemTime();
    _u8LocktimeFlag=0;
    printf("--%s():%d\n", __FUNCTION__, __LINE__);
    bRet &= MDrv_CofdmDmd_Restart(&pParam);
    return bRet;
}

EN_LOCK_STATUS DTV_DVB_S_GetLockStatus(void)
{
    MAPI_BOOL bLock = FALSE;
    EN_LOCK_STATUS eLockState=E_DEMOD_UNLOCK;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);

    bLock=MSB1245_DTV_GetLock();
    if(bLock)
        eLockState = E_DEMOD_LOCK;
    else
    {
        eLockState = E_DEMOD_UNLOCK;
    }

    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return eLockState;
}


EN_SAT_ROLL_OFF_TYPE DTV_DVB_S_GetRollOff(void)
{
    EN_SAT_ROLL_OFF_TYPE eRoll = SAT_RO_20;
    MAPI_U8 u8RollOff;

    if(MDrv_CofdmDmd_GetRollOff(&u8RollOff))
    {
        switch (u8RollOff)
        {
            case 0:
                eRoll = SAT_RO_35;
                break;
            case 1:
                eRoll = SAT_RO_25;
                break;
            case 2:
                eRoll = SAT_RO_20;
                break;
            default:
                eRoll = SAT_RO_20;
        }
    }
    return eRoll;
}


MAPI_BOOL DTV_DVB_S_SetToneBurst(EN_SAT_TONEBUREST_TYPE eTone)
{
    MAPI_BOOL bTone1;
    if(eTone == E_TONE1)
        bTone1 = MAPI_TRUE;
    else
        bTone1 = MAPI_FALSE;

    return MDrv_DiSEqC_SetTone(bTone1);
}

MAPI_BOOL DTV_DVB_S_SetLNBPower(EN_SAT_LNBPOWER_TYPE eLNBPower)
{
    MAPI_BOOL bLow;

    switch ( eLNBPower)
    {

        case E_LNB_POWER_18V:
        case E_LNB_POWER_19V:
            bLow =MAPI_FALSE;
            break;
        case E_LNB_POWER_13V:
        case E_LNB_POWER_14V:
            bLow =MAPI_TRUE;
            break;
        default:
            bLow =MAPI_TRUE;
    }

    return MDrv_DiSEqC_SetLNBOut(bLow);

}

MAPI_BOOL DTV_DVB_S_Set22KOnOff(MAPI_BOOL bOn)
{
     return MDrv_DiSEqC_Set22kOnOff(bOn);
}

MAPI_BOOL DTV_DVB_S_Get22KStatus(MAPI_BOOL* bOn)
{
    return MDrv_DiSEqC_Get22kOnOff(bOn);
}

MAPI_BOOL DTV_DVB_S_SendDiSEqCCmd(MAPI_U8* pCmd,MAPI_U8 u8CmdSize)
{
     return MDrv_DiSEqC_SendCmd(pCmd, u8CmdSize);
}

//BLIND SCAN
MS_BOOL MDrv_CofdmDmd_BlindScan_Start(MS_U16 u16StartFreq,MS_U16 u16EndFreq,MS_BOOL bUCMode)
{
    MAPI_BOOL bRet;
    UNUSED(bUCMode);
    _u32CurrentSR = 0;
    eBlindScanStatue = E_BLINDSCAN_NOTREADY;

     //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
     bRet=_MDrv_CofdmDmd_BlindScan_Start(u16StartFreq,u16EndFreq);
     if(bRet)
        eBlindScanStatue = E_BLINDSCAN_INIT_OK;
     else
        eBlindScanStatue = E_BLINDSCAN_INIT_FAILED;

     //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
     return bRet;
}
#if 0
MAPI_BOOL DTV_DVB_S_BlindScan_ScanNextFreq(void)
{
    MAPI_BOOL bBlindScanEnd;
    MAPI_BOOL bRet;

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
    bRet = MDrv_CofdmDmd_BlindScan_NextFreq(&bBlindScanEnd);
    if(bRet)
    {
        if(bBlindScanEnd)
            eBlindScanStatue = E_BLINDSCAN_ALLFREQ_COMPLETE;
        else
            eBlindScanStatue = E_BLINDSCAN_SCANFREQ_SCANNING;
    }
    else
    {
        eBlindScanStatue = E_BLINDSCAN_SCANFREQ_START_FAILED;
    }
    //printf("\033[35m[sttest]DTV_DVB_S_BlindScan_ScanNextFreq , %d, %d [CHECK]\033[m\n", bRet,eBlindScanStatue );

    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;
}
#endif
#if 1
MAPI_BOOL DTV_DVB_S_BlindScan_GetFoundTP(MAPI_U8 u8No, MAPI_U32 *u32Freq,MAPI_U32 *u32SymbolRate)
{
    MAPI_U16 u16Num = 1;
    DTVPROGRAMID_M stChannel;
    MAPI_BOOL bRet = MAPI_TRUE;

    memset(&stChannel, 0, sizeof(DEMOD_MS_FE_CARRIER_PARAM));

    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
    if(MDrv_CofdmDmd_BlindScan_GetChannel(u8No,&u16Num,&stChannel) != MAPI_TRUE)
    {
        *u32Freq = 0;
        *u32SymbolRate = 0;
        bRet = MAPI_FALSE;
    }
    else
    {
        if(u16Num == 0)
        {
            *u32Freq = 0;
            *u32SymbolRate = 0;
            bRet = MAPI_FALSE;
        }
        else
        {
            *u32Freq = stChannel.u32Frequency;//1000;
            *u32SymbolRate = stChannel.u16SymbolRate;// /1000;
        }
    }
    //printf("\033[35m[sttest]DTV_DVB_S_BlindScan_GetFoundTP , %d, %d ,%d [CHECK]\033[m\n", bRet,u16Freq,u16SymbolRate );

    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return bRet;

}
#endif
MAPI_BOOL DTV_DVB_S_BlindScan_Cancel(void)
{
      MAPI_BOOL bRet;

      //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
      bRet = MDrv_CofdmDmd_BlindScan_Cancel();
      //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);

      return bRet;
}

MAPI_BOOL DTV_DVB_S_BlindScan_End(void)
{
    //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
    if((eBlindScanStatue == E_BLINDSCAN_SCANFREQ_SCANNING))
    {
        if(MDrv_CofdmDmd_BlindScan_Cancel() != MAPI_TRUE)
        {
            //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
            return MAPI_FALSE;
        }
    }

    if(MDrv_CofdmDmd_BlindScan_End() != MAPI_TRUE)
    {
        //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
        return MAPI_FALSE;
    }

    eBlindScanStatue = E_BLINDSCAN_NOTREADY;
    //mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(DEMOD_DYNAMIC_SLAVE_ID_3);
    //iptr->SetSpeed(EN_HWI2C_HIGH);

    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
    return MAPI_TRUE;

}

MAPI_BOOL DTV_DVB_S_BlindScan_GetStatus(EN_BLINDSCAN_STATUS *eStatus)
{
    //A2108_ErrorCode eErrCode;
    MAPI_U8 u8Progress,u8ChannelNum;
    MAPI_BOOL bRet = MAPI_TRUE;

    // MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
     if(eBlindScanStatue == E_BLINDSCAN_SCANFREQ_SCANNING)
     {
        if(MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(&u8Progress,&u8ChannelNum) != MAPI_TRUE)
        {
            bRet = MAPI_FALSE;
        }
        else
        {
            if(u8Progress == 100)
            {
                eBlindScanStatue = E_BLINDSCAN_SCANFREQ_COMPLETE;
            }
        }
     }
     *eStatus = eBlindScanStatue;
     //printf("\033[35m[sttest]DTV_DVB_S_BlindScan_GetStatus, %d ,%d ,%d [CHECK]\033[m\n",  bRet ,u8Progress ,eBlindScanStatue);

    // MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);
     return bRet;
}

MAPI_BOOL DTV_DVB_S_BlindScan_GetScanFreq(MAPI_U32 *u32Freq)
{
      MAPI_BOOL bRet;

      //MsOS_ObtainMutex(_s32_Demod_DVBS2_Mutex, MSOS_WAIT_FOREVER);
      bRet = MDrv_CofdmDmd_BlindScan_GetCurrentFreq(u32Freq);
      //printf("\033[35m[sttest]DTV_DVB_S_BlindScan_GetScanFreq, %d ,%d  [CHECK]\033[m\n",  bRet ,u16Freq);
      //MsOS_ReleaseMutex(_s32_Demod_DVBS2_Mutex);

      return bRet;
}
#if (MSB123x_T2MI_DJB_RST_EN == 1)
MAPI_BOOL MSB123x_DJB_RST(void)
{
	return TRUE;
}
#endif
#if 0
MAPI_BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks)
{
    //return DTV_DVB_S_SetFrequency(u16CenterFreq_MHz, u32SymbolRate_Ks);
    return MDrv_Tuner_SetFreq(u16CenterFreq_MHz, u32SymbolRate_Ks);
}
MAPI_BOOL MDrv_DVBS_Tuner_Initial(void)
{
    extern MS_BOOL MDrv_Tuner_Initial(void);
    return MDrv_Tuner_Initial();
}
MAPI_BOOL MDrv_DVBS_Tuner_CheckLock(void)
{
    extern MS_BOOL MDrv_Tuner_CheckLock(void);
    return MDrv_Tuner_CheckLock();
}
#endif
//float MDrv_DVBS_Tuner_Get_RSSI(MS_U16);

//=== mailbox function ===
MAPI_BOOL  ReadMailbox(MS_U16 u16Addr, MS_U8* u8Data)
{
    MAPI_BOOL     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;
    MAPI_U16    addr;
    MAPI_U8     data;
    // MsOS_ObtainMutex(_s32_Demod_DVBS2_RW_Mutex, MSOS_WAIT_FOREVER);
    addr = REG_MB_ADDR_H;
    data = ((u16Addr >> 8)& 0xff) ;
    status &= MSB1245_WriteReg(addr, data);
    addr = REG_MB_ADDR_L;
    data = u16Addr & 0xff;
    status &= MSB1245_WriteReg(addr, data);
    addr = REG_MB_CNTL;
    status &= MSB1245_WriteReg(addr, 0x03); // 3: param read
    addr = REG_MB_DATA ;
    status &=MSB1245_ReadReg(addr, u8Data);
    do
    {
        addr = REG_MB_CNTL ;
        status &=MSB1245_ReadReg(addr, &cntl);
        if (cntr++ > 0x7ff)
        {
            //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
            return FALSE;
        }
        addr = REG_MB_DATA ;
        status &=MSB1245_ReadReg(addr, u8Data);
    }
    while(cntl != 0xff);
    //MsOS_ReleaseMutex(_s32_Demod_DVBS2_RW_Mutex);
    return status;
}

#if(SUPPORT_UNICABLE)

#define MAX_IF_FREQ  2150
#define MIN_IF_FREQ   950
#define MAX_SYM_RATE         45000
#define MIN_SYM_RATE         1

const MS_U8 u8BankMap[2][2][2] =
{
{{2, 0}, {3, 1}}, //PosA, Low/High Band, Vertical/Horizontal Polarity
{{4, 6}, {5, 7}}  //PosB, Low/High Band, Vertical/Horizontal Polarity
};
MAPI_BOOL FrontEnd_DVBS2_Set(MS_U32 u32Frequency, MS_U32 u32SymRate, MS_U8 u8Polarity , MS_SAT_PARAM *stSatInfo)
{
    MS_BOOL bIsHiLOF = FALSE, bHor = FALSE;
//	U8 s_enUnicableLNBNum;
    S32 s32Freq = 0;
	CofdmDMD_Param unidmdpara;
//   S32 sTempFreq = 0;
    //MW_DTV_FRONTEND_FUNCTION("MW_DTV_FrontEnd_DVBS::Set6(%ld,%ld,%d) \n", u32Frequency, u32SymRate, u8Polarity);
    //ASSERT(u8Polarity<=1);

    // calc Mid Freq & LNB control(22K on/off)
   //stSatInfo->u16LoLOF=  stSatInfo->u16UnicableLNBLow[stSatInfo->u8ChannelId] ;
   //stSatInfo->u16HiLOF =  stSatInfo->u16UnicableLNBHight[stSatInfo->u8ChannelId] ;
  //  printf("\r\n______lof[%u][%u]__________",stSatInfo->u16LoLOF,stSatInfo->u16HiLOF );
    if (stSatInfo->u16LoLOF == stSatInfo->u16HiLOF)
    {
        s32Freq  = u32Frequency;
        s32Freq -= stSatInfo->u16LoLOF ;
        if(s32Freq < 0)
        {
            s32Freq = -s32Freq;
        }
       // bIsHiLOF = FALSE;
    }
    else // 2LOF
    {
        if(stSatInfo->u16LoLOF < MAX_C_LOF_FREQ) // c band
        {
            s32Freq  = u32Frequency;
            if(u8Polarity == 0) //H ---> use low LOF
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
        printf("Invalid   Freq = %ld\n", s32Freq);
        s32Freq = MIN_IF_FREQ;
    }
    if(u32SymRate > MAX_SYM_RATE || u32SymRate < MIN_SYM_RATE)
    {
        printf("Invalid u32SymRate = %ld\n", u32SymRate*1000);
        u32SymRate = 1000;
    }


      if(u8Polarity == 0)
	{
		bHor = TRUE;
	}
	else
	{
		bHor = FALSE;
	}


        U16 u16TuneWord = ((s32Freq + stSatInfo->u16IFreq)/4) - 350;
        ODU_ChChg(stSatInfo->u8ChannelId,u8BankMap[0][bIsHiLOF][u8Polarity], u16TuneWord,0);

		printf("[Gaven],set();[Unicable] [(Freq = %ld + IFreq = %d)/4 - 350] = (TuneWord = %d)\n",s32Freq, stSatInfo->u16IFreq, u16TuneWord);
        printf("[Gaven],set();[Unicable] ChannelId = %d, u32SymRate = %ld, u8Polarity = %d, Bank = %d\n",stSatInfo->u8ChannelId, u32SymRate*1000, u8Polarity, u8BankMap[0][bIsHiLOF][u8Polarity]);

      //  AVL_SetFrequency(stSatInfo->u16IFreq, u32SymRate*1000);
       //MDrv_DVBS_Tuner_SetFreq(stSatInfo->u16IFreq, u32SymRate*1000);
      	unidmdpara.u32TunerFreq=stSatInfo->u16IFreq;
        unidmdpara.u32SymbolRate=u32SymRate*1000;
	if (MDrv_CofdmDmd_Restart(&unidmdpara) == FALSE)
	{
			return FALSE;
	}


    return TRUE;
}
#endif

#endif
