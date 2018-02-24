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
// reverse engineering and compiling of the contents of MStaR Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_TUNER_H
#define MSAPI_TUNER_H

#include "debug.h"
#include "Tuner.h"
#include "msAPI_Global.h"
#include "apiDMX.h"
#include "msAPI_DTV_Common.h"
#include "msAPI_Demod.h"


/******************************************************************************/
/*                 Macro                                                      */
/******************************************************************************/

#if 0
//for internal DEMOD init
typedef enum
{
    DEMOD_MODE_DVB_C,
    DEMOD_MODE_DVB_T,
    DEMOD_MODE_ISDB_T,
    DEMOD_MODE_N_DTV
} EN_INTERNAL_DEMOD_MODE;
#endif

#if( ENABLE_ATSC )
typedef enum
{
    LOCK,
    CHECKING,
    CHECKEND,
    UNLOCK,
} EN_SCAN_RESULT;
#endif

typedef enum
{
    DEMOD_MODE_PAL,
    DEMOD_MODE_DVB,
    DEMOD_MODE_NUM
} EN_DEMOD_MODE;


typedef enum
{
    PAL_SCAN,
    DVB_SCAN,
} EN_SCAN_MODE;


typedef enum
{
    SIGNAL_NO = 0,          // little or no input power detected
    SIGNAL_WEAK,            // some power detected.
    SIGNAL_MODERATE,        // lock achieved, SNR < 15 dB (approx)
    SIGNAL_STRONG,          // lock achieved, SNR < 24 dB (approx)
    SIGNAL_VERY_STRONG,     // lock achieved, SNR > 24 dB (approx)
} EN_SIGNAL_CONDITION;

typedef enum
{
    STATE_VSB_CHECK_INIT,
    STATE_VSB_CHECK_CR_LOCK,
    STATE_VSB_CHECK_WAIT_INIT,
    STATE_VSB_CHECK_SYNC_LOCK,
    STATE_VSB_CHECK_SNR,
} EN_VSB_CHECK_LOCK_STATE;

typedef enum
{
    STATE_QAM_CHECK_INIT,
    STATE_QAM_CHECK_WAIT_INIT,
    STATE_QAM_CHANGE_MODE,
    STATE_QAM_CHECK_FEC_LOCK,
    STATE_QAM_CHECK_MPEG_LOCK,
} EN_QAM_CHECK_LOCK_STATE;

typedef enum
{
    STATE_VSB_STABLE_INIT,
    STATE_VSB_STABLE_WAIT_INIT,
    STATE_VSB_STABLE_SYNC_LOCK,
} EN_VSB_CHECK_STABLE_STATE;

typedef enum
{
    EN_DVB_T_TYPE = 0,
    EN_DVB_C_TYPE,

#if 0//ENABLE_S2
    EN_DVB_S2_TYPE,
#endif
    EN_DVB_DEMOD_TYPE_UNKNOWN,

} EN_DVB_TYPE;

#ifdef MSAPI_TUNER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


#if(ENABLE_DTV)

INTERFACE void msAPI_Tuner_ResetDemodMode(void);
INTERFACE void msAPI_Tuner_InitCurrentTPSetting(void);

INTERFACE void msAPI_Tuner_Initialization_BySource(void);

INTERFACE void msAPI_Tuner_InitExternDemod(void);
INTERFACE void msAPI_Tuner_ZigZagScan(void);

INTERFACE void msAPI_Tuner_Tune2RfCh(MS_TP_SETTING *pstTPSetting);
INTERFACE BOOLEAN msAPI_Tuner_IsSameRfChannel(MS_TP_SETTING *pstTPSetting);
INTERFACE void msAPI_Tuner_Set_DemodPower(BOOLEAN bPower);
INTERFACE U8 msAPI_Tuner_GetSingalSNRPercentage(void);
INTERFACE WORD msAPI_Tuner_GetSignalQualityPercentage(void);
INTERFACE BOOLEAN msAPI_Tuner_GetBER(float *ber);
INTERFACE BOOLEAN msAPI_Tuner_GetSignalModulMode(U16 *pu16Modul_Mode);
INTERFACE void msAPI_Check_Lock_State_Init(void);
INTERFACE BOOLEAN msAPI_Tuner_CheckLock(BOOLEAN *CheckLockResult,BOOLEAN fScan);
BOOLEAN msAPI_Tuner_CheckLock_DetectUserKey(void);

INTERFACE void msAPI_Tuner_Serial_Control(BOOLEAN bParallelMode,BOOLEAN bPVRMode);
INTERFACE FUNCTION_RESULT msAPI_Tuner_CheckSignalStrength(WORD *wStrength);
INTERFACE BOOLEAN msAPI_Tuner_Get_CELL_ID( WORD * cell_id);
INTERFACE BOOLEAN msAPI_Tuner_Get_PLP_ID( U8 * pu8plp_id);
INTERFACE U8 msAPI_Tuner_Get_HpLp( void);
#if( ENABLE_HIERARCHY )
INTERFACE BOOLEAN msAPI_Tuner_Is_HierarchyOn(void);
#endif
INTERFACE FUNCTION_RESULT msAPI_Tuner_GetCurTPSetting(MS_TP_SETTING *pstCurTPSetting);

#endif

INTERFACE void msAPI_Tuner_SwitchSource(EN_DVB_TYPE etype, BOOLEAN bInit);
INTERFACE EN_DVB_TYPE msAPI_Tuner_GetSourceType(void);
void msAPI_Tuner_Set_DvbType(EN_DVB_TYPE eDvbType);

INTERFACE void msAPI_Tuner_SetAntenna(BOOLEAN bIsCATV);
//INTERFACE DMX_FILTER_STATUS msAPI_Tuner_SetByPassMode(BOOLEAN bByPass, BOOLEAN bPVRMode);
//INTERFACE BOOLEAN msAPI_Tuner_IsByPassMode(void);

INTERFACE BOOLEAN msAPI_Tuner_IsParallelMode(void);

INTERFACE U8 msAPI_Tuner_GetDspStatus(void);

#if (ENABLE_DVBC)
INTERFACE void msAPI_Tuner_UpdateTPSetting(void);
#endif

#if ENABLE_DVB_T2
INTERFACE void msAPI_Tuner_SetCurrentTPSetting(U8 pu8PlpID);
INTERFACE U8 msAPI_Tuner_GetCurrentTPSetting(void);
#endif

#if ENABLE_S2
#define MAX_C_LOF_FREQ			6350
#define SAT_MOVE_TIME			10
/// Define converlution code rate for DVB-T and DVB-S
typedef enum
{
    CONV_CODE_RATE_1_2,                                                 ///< Code rate = 1/2
    CONV_CODE_RATE_2_3,                                                 ///< Code rate = 2/3
    CONV_CODE_RATE_3_4,                                                 ///< Code rate = 3/4
    CONV_CODE_RATE_5_6,                                                 ///< Code rate = 5/6
    CONV_CODE_RATE_7_8,                                                 ///< Code rate = 7/8
} EN_CONV_CODE_RATE_TYPE;
/// Define terrestrial hierarchy information
typedef enum
{
    TER_HIE_NONE,                                                       ///< Non-hierarchy
    TER_HIE_ALPHA_1,                                                    ///< Hierarchy alpha = 1
    TER_HIE_ALPHA_2,                                                    ///< Hierarchy alpha = 2
    TER_HIE_ALPHA_4                                                     ///< Hierarchy alpha = 4
} EN_TER_HIE_TYPE;
/// Define terrestrial guard interval
typedef enum
{
    TER_GI_1_32,                                                        ///< Guard interval value = 1/32
    TER_GI_1_16,                                                        ///< Guard interval value = 1/16
    TER_GI_1_8,                                                         ///< Guard interval value = 1/8
    TER_GI_1_4                                                          ///< Guard interval value = 1/4
} EN_TER_GI_TYPE;
/// Define terrestrial transmission mode
typedef enum
{
    TER_FFT_2K,                                                         ///< 2k FFT mode
    TER_FFT_8K                                                          ///< 8k FFT mode
} EN_TER_FFT_MODE;
/// Define terrestrial transmission mode
typedef enum
{
    TER_HP_SEL,                                                         ///< High priority level selection
    TER_LP_SEL                                                          ///< Low priority level selection
} EN_TER_LEVEL_SEL;
/// Define DVB-S IQ tuning mode
typedef enum
{
    CAB_IQ_NORMAL,                                                      ///< Normal
    CAB_IQ_INVERT                                                       ///< Inverse
} EN_CAB_IQ_MODE;
/// Define DVB-S modulatiopn scheme
typedef enum
{
    SAT_QPSK,                                                           ///< QPSK
    SAT_8PSK,                                                           ///< 8PSK
    SAT_QAM16                                                           ///< QAM16
} EN_SAT_CONSTEL_TYPE;
/// Define DVB-S Roll-Off factor
typedef enum
{
    SAT_RO_35,                                                          ///< roll-off factor = 0.35
    SAT_RO_25,                                                          ///< roll-off factor = 0.25
    SAT_RO_20                                                           ///< roll-off factor = 0.20
} EN_SAT_ROLL_OFF_TYPE;
/// Define DVB-S IQ tuning mode
typedef enum
{
    SAT_IQ_NORMAL,                                                      ///< Normal
    SAT_IQ_INVERSE                                                      ///< Inverse
} EN_SAT_IQ_MODE;
/// Define Bit Error Rate range measure from signal
typedef enum
{
    BIT_ERR_RATIO_LOW ,                                                 ///< Low BER
    BIT_ERR_RATIO_MEDIUM ,                                              ///< Medium BER
    BIT_ERR_RATIO_HIGH                                                  ///< High BER
} EN_BIT_ERR_RATIO;
/// Define lock status of front end
typedef enum
{
    FE_UNLOCKED = 0,                                                    ///< Frontend is unlocked
    FE_LOCKED                                                           ///< Frontend is locked
} EN_FE_LOCK_STATUS;
/// Define tuning mode
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef enum
{
    FE_TUNE_MANUAL,                                                     ///< Manual tuning to carrier
    FE_TUNE_AUTO,                                                       ///< Auto tuning to carrier
} EN_FE_TUNE_MODE;
typedef enum
{
	BW_MODE_6MHZ = 0,                                                   ///< 6 MHz
	BW_MODE_7MHZ,                                                       ///< 7 MHz
	BW_MODE_8MHZ                                                        ///< 8 MHz
} EN_TER_BW_MODE;
typedef enum
{
    TER_QPSK,                                                           ///< QPSK type
    TER_QAM16,                                                          ///< QAM 16 type
    TER_QAM64                                                           ///< QAM 64 type
} EN_TER_CONSTEL_TYPE;
/// Define symbol rate for DVB-S, unit in symbol/sec
typedef MS_U32                      FE_SYMBOL_RATE;                     ///< unit in symbol/sec
/// Define the cellule identifier
typedef MS_U16                      FE_CELL_ID;
/// Define tuning paramter of DVB-T front-end
typedef struct
{
    EN_TER_BW_MODE                  eBandWidth;                         ///< Band width
    EN_TER_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    EN_TER_HIE_TYPE                 eHierarchy;                         ///< Hierarchy
    EN_TER_GI_TYPE                  eGuardInterval;                     ///< Guard interval
    EN_TER_FFT_MODE                 eFFT_Mode;                          ///< Transmission mode
    EN_CONV_CODE_RATE_TYPE          eHPCodeRate;                        ///< HP code rate
    EN_CONV_CODE_RATE_TYPE          eLPCodeRate;                        ///< LP code rate
    EN_TER_LEVEL_SEL                eLevelSel;                          ///< Select HP or LP level
} MS_TER_CARRIER_PARAM;
/// Define tuning paramter of DVB-C front-end
typedef struct
{
    //EN_CAB_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    MS_U16                          u16SymbolRate;                      ///< Symbol rate (Ksym/sec)
    EN_CAB_IQ_MODE                  eIQMode;                            ///< IQ Mode
    MS_U8                           u8TapAssign;                        ///< Tap assign
    MS_U32                          u32FreqOffset;                      ///< Carrier frequency offset
	MS_U8							u8TuneFreqOffset;					///< Requeset tuner freq offset
} MS_CAB_CARRIER_PARAM;
/// Define tuning paramter of DVB-S front-end
typedef struct
{
    EN_SAT_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    EN_SAT_ROLL_OFF_TYPE            eRollOff;                           ///< Roll-Off factor
    EN_SAT_IQ_MODE                  eIQ_Mode;                           ///< IQ mode
    EN_CONV_CODE_RATE_TYPE          eCodeRate;                          ///< Converlution code rate
    MS_U16                          u16SymbolRate;                      ///< Symbol rate (Ksym/sec)
    MS_U8                            u8Polarity; // 0: Horizon; > 0(default 1): Vertical;
    MS_U8                            u8SatID;
} MS_SAT_CARRIER_PARAM;
/// Define carrier paramter of digital tuner
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef struct
{
    MS_U32                          u32Frequency;                       ///< RF frequency,Unit KHZ
    union
    {
	    MS_TER_CARRIER_PARAM        TerParam;                           ///< Paramters for DVB-T front-end
	    MS_CAB_CARRIER_PARAM        CabParam;                           ///< Paramters for DVB-C front-end
	    MS_SAT_CARRIER_PARAM        SatParam;                           ///< Paramters for DVB-S front-end
    };
} MS_FE_CARRIER_PARAM;
#endif




#define ENABLE_SCAN_ONELINE_MSG     0



/***************************************************************************************/

#undef INTERFACE

/***************************************************************************************/

#endif // MSAPI_TUNER_H

