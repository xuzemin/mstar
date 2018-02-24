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

#ifndef __MSAPI_TUNING_H__
#define __MSAPI_TUNING_H__


#include "msAPI_ATVSystem.h"

#ifdef MSAPI_TUNING_C
#define INTERFACE
#else
#define INTERFACE extern
#endif



#define ENABLE_DEBUG_TUNING_TIME    0

#if( ENABLE_DEBUG_TUNING_TIME )
    #define DEBUG_TUNING_TIME(x)    x
#else
    #define DEBUG_TUNING_TIME(x)
#endif


#define ENABLE_DBG_ATV_SCAN         FALSE//TRUE//FALSE


//===============================================================
#define AUTO_TUNING_ALG_DEFAULT         0
#define AUTO_TUNING_ALG_NTSC            1
#define AUTO_TUNING_ALG_TST             2
#define AUTO_TUNING_ALG_PAL_NEW         3

#define LOWEST_SORTING_PRIORITY        0xFF

#define DIFFERENCE(a,b)             (((a)>=(b))?((a)-(b)):((b)-(a)))
//------  ATV SCAN CUSTOMIZE  ----------------------------------------------------

#if 0
  #if ENABLE_SBTVD_SCAN
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_NTSC
    #define ATVSCAN_SORT_BY_STATION_NAME        0
  #elif (ENABLE_DVB_TAIWAN_APP)
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_NTSC
    #define ATVSCAN_SORT_BY_STATION_NAME        0
  #elif( DTV_SYSTEM_SEL == DTV_SYSTEM_ATSC )
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_NTSC//AUTO_TUNING_ALG_PAL_NEW
    #define ATVSCAN_SORT_BY_STATION_NAME        0
#else
 #if (DTV_SYSTEM_SEL == DTV_SYSTEM_NONE)// ATV
  #if (TV_SYSTEM == TV_NTSC)
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_NTSC
    #define ATVSCAN_SORT_BY_STATION_NAME        0
  #else
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_PAL_NEW
    #if(ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP)
        #define ATVSCAN_SORT_BY_STATION_NAME        0
    #else
        #define ATVSCAN_SORT_BY_STATION_NAME        1
    #endif
  #endif
 #elif (TV_SYSTEM == TV_NTSC)
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_NTSC
    #define ATVSCAN_SORT_BY_STATION_NAME        0
 #else
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_PAL_NEW
    #if(ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP)
        #define ATVSCAN_SORT_BY_STATION_NAME        0
    #else
        #define ATVSCAN_SORT_BY_STATION_NAME        1
    #endif
 #endif
#endif

#else
  #if 0//ENABLE_SBTVD_SCAN
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_NTSC
  #else
    #define AUTO_TUNING_TYPE_SEL                AUTO_TUNING_ALG_PAL_NEW
  #endif
#endif

#if(FRONTEND_TUNER_TYPE == NXP_TD1616EF_TUNER)
    #define ATVSCAN_AUDIO_WAIT_TIME         WAIT_310ms
#endif

#if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF || FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_SPEEP_UP          23//
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP_L    23//
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP      11//
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P5MHZ_STEP       23//
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_4MHZ_STEP         23//
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_MAX_STEP          23//
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_CROSS_BAND_STEP   23//
#endif

    #define ATVSCAN_USE_TIMER_DELAY             1
    #define ATVSCAN_AUDIO_WAIT_TIME2            230     //unit:ms


    #define ATVSCAN_VIFLOCK_TOTAL_CHECK_TIME    30      //unit:ms
    #define ATVSCAN_VDLOCK_TOTAL_CHECK_TIME     180     //unit:ms
    #define ATVSCAN_CNI_TOTAL_CHECK_TIME        3000    //unit:ms


//------  ATV SCAN DEFAULT  ----------------------------------------------------

#ifndef AUTO_TUNING_TYPE_SEL
    #define AUTO_TUNING_TYPE_SEL        AUTO_TUNING_ALG_DEFAULT//AUTO_TUNING_ALG_TST//AUTO_TUNING_ALG_DEFAULT
#endif

#ifndef ATVSCAN_SORT_BY_STATION_NAME
    #define ATVSCAN_SORT_BY_STATION_NAME         1
#endif

#if (TV_SYSTEM == TV_PAL)
 #if(FRONTEND_TUNER_TYPE == NXP_TD1616EF_TUNER)
    #define TV_SCAN_PAL_SECAM_ONCE              0
 #else
  #if(AUTO_TUNING_TYPE_SEL ==AUTO_TUNING_ALG_PAL_NEW)
    #define TV_SCAN_PAL_SECAM_ONCE              1
  #else
    #define TV_SCAN_PAL_SECAM_ONCE              0
  #endif
 #endif
#else
    #define TV_SCAN_PAL_SECAM_ONCE              0
#endif

#ifndef FRANCE_SUPPORT_SECAM_BG_SECAM_DK
    #define FRANCE_SUPPORT_SECAM_BG_SECAM_DK    1
#endif

#ifndef ATVSCAN_AUDIO_WAIT_TIME
    #define ATVSCAN_AUDIO_WAIT_TIME             WAIT_770ms
#endif

#ifndef AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_SPEEP_UP
  #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_SPEEP_UP          23
  #else
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_SPEEP_UP          17
  #endif
#endif

#ifndef AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP_L
  #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP_L    23
  #else
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP_L    23
  #endif
#endif

#ifndef AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP
  #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP      11//
  #else
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP      9
  #endif
#endif

#ifndef AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P5MHZ_STEP
  #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P5MHZ_STEP       23//
  #else
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P5MHZ_STEP       23 //
  #endif
#endif

#ifndef AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_4MHZ_STEP
  #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_4MHZ_STEP         23//
  #else
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_4MHZ_STEP         23 //
  #endif
#endif

#ifndef AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_MAX_STEP
  #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_MAX_STEP          23//
  #else
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_MAX_STEP          23 //
  #endif
#endif

#ifndef AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_CROSS_BAND_STEP
  #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_CROSS_BAND_STEP   23//
  #else
    #define AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_CROSS_BAND_STEP   23 //
  #endif
#endif


#ifndef TUNER_PLL_NEXT_CHANNEL_JUMP
    #define TUNER_PLL_NEXT_CHANNEL_JUMP   TUNER_PLL_PLUS_2MHz          // WAIT_150ms
#endif


#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
    #define E_AFC_GOOD_MINUS_VALUE      E_AFC_MINUS_37p5KHz
    #define E_AFC_GOOD_PLUS_VALUE       E_AFC_PLUS_12p5KHz
#else
 #ifndef   SPECIFIC_AFC_GOOD_VALUE
    #define E_AFC_GOOD_MINUS_VALUE      E_AFC_MINUS_37p5KHz
    #define E_AFC_GOOD_PLUS_VALUE       E_AFC_PLUS_37p5KHz
 #else
  #if (SPECIFIC_AFC_GOOD_VALUE == 1)
    #define E_AFC_GOOD_MINUS_VALUE      E_AFC_MINUS_62p5KHz
    #define E_AFC_GOOD_PLUS_VALUE       E_AFC_PLUS_62p5KHz
  #else
    #define E_AFC_GOOD_MINUS_VALUE      E_AFC_MINUS_37p5KHz
    #define E_AFC_GOOD_PLUS_VALUE       E_AFC_PLUS_37p5KHz
  #endif
 #endif
#endif

#ifndef ENABLE_AUDIO_AUTO_DETECT
    #define ENABLE_AUDIO_AUTO_DETECT            1
#endif

// AFT external Steps
typedef U32 eAFTSTEP;
#define AFT_EXT_STEP_PERIODIC                   0x00
#define AFT_EXT_STEP_SEARCHALL                  0x01
#define AFT_EXT_STEP_SEARCHONETOUP              0x02
#define AFT_EXT_STEP_SEARCHONETODOWN            0x03
#define AFT_EXT_STEP_SEARCHSTOP                 0x04
#define AFT_TUNING_SUSPEND                      0x05
#define AFT_TUNING_RESUME                       0x06


#define SCAN_TEST_MODE_ENABLE  0
#if (SCAN_TEST_MODE_ENABLE==1)
#define TEST_MODE_ATV_SCAN_MAX                  50
#define TEST_MODE_ATV_SCAN_STATE_DISABLE         0
#define TEST_MODE_ATV_SCAN_STATE_SAVE_DATA       1
#define TEST_MODE_ATV_SCAN_STATE_VERIFY          2

#define TEST_MODE_ATV_SCAN_Init                  0
#define TEST_MODE_ATV_SCAN_Processing            1
#define TEST_MODE_ATV_SCAN_Finish                2
typedef struct
{
     U16    wPLL;
  //   BYTE  sName[MAX_STATION_NAME];
     WORD eAudioStandard                         : 4;
     WORD eVideoStandard                         : 3;
     WORD bActive                                : 1;
     WORD bFound                                 : 1;
     WORD Reserve                                : 9;

} SCAN_TEST_MODE_ATV_INFO;

typedef struct
{
    U8   u8State;
    U8   u8ActiveProgramNum;
    U8   u16VerifyCount;
    U8   u16VerifyCountInput;
    U8   u16Total_Lost_Channel;
    U8   u16Total_Ghost_Channel;

} SCAN_TEST_MODE_TEST_INFO;

extern SCAN_TEST_MODE_ATV_INFO TestModeScanInfo[TEST_MODE_ATV_SCAN_MAX];
extern SCAN_TEST_MODE_TEST_INFO AutoScanTest;

extern void TestMode_ATV_Scan_Verify(U8 u8VerifyState);
extern void TestMode_ATV_Scan_Save_Info(U8 u8SaveInfoState);
#endif // #if (SCAN_TEST_MODE_ENABLE==1)


typedef enum
{
    DIRECTION_UP,
    DIRECTION_DOWN
} DIRECTION;
#if( TV_FREQ_SHIFT_CLOCK )
typedef enum
{
    SHIFT_CLK_ORIGIN_43d2M,
    SHIFT_CLK_TYPE1_42M,
    SHIFT_CLK_TYPE2_44d4M
} TV_FREQ_SHIFT_MODE;
#endif

#if ( TV_FREQ_SHIFT_CLOCK )
INTERFACE U8 g_u8_ShiftClk_LastMode;
#endif

//------------------------------------------------------------------------------
// Prototype
//------------------------------------------------------------------------------
INTERFACE void msAPI_Tuner_Init(void);
#if(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)
INTERFACE void msAPI_Tuner_Clear_IfFreqStatus(void);
INTERFACE void msAPI_SetTunerPLL(void);  //20100604EL
#endif
INTERFACE BOOLEAN msAPI_Tuner_IsTuningProcessorBusy(void);
INTERFACE BOOLEAN msAPI_Tuner_IsOneProgramDetected(void);
INTERFACE BOOLEAN msAPI_Tuner_PreProgramDeteted(void);
INTERFACE void msAPI_Tuner_SetRealtimeAFTBaseTunerPLL(U16 u16TunerPLL);
INTERFACE void msAPI_Tuner_TuningProcessor(eAFTSTEP eState);
INTERFACE void msAPI_Tuner_AdjustUnlimitedFineTune(DIRECTION eDirection);
INTERFACE U16 msAPI_Tuner_SetSearchManualTune(U16 u16InterFreq);
INTERFACE void msAPI_Tuner_ChangeProgram(void);
//INTERFACE void msAPI_Tuner_ChangeProgramWithoutStable(void);
INTERFACE MEDIUM msAPI_Tuner_GetMedium(void);
INTERFACE void msAPI_Tuner_SetMedium(MEDIUM eMedium);
INTERFACE U8 msAPI_Tuner_GetChannelNumber(void);
INTERFACE void msAPI_Tuner_SetChannelNumber(U8 u8Channel);
INTERFACE void msAPI_Tuner_SetIF(void);
void msAPI_Tuner_SetIF_By_Freq_AudioStd(U32 u32TunerFreg, AUDIOSTANDARD_TYPE eAudioStd);

#if(VIF_TUNER_TYPE==1)
INTERFACE void msAPI_SiTuner_Pre_SetIF(U16 u16PLL);
#endif
INTERFACE U16 msAPI_Tuner_GetCurrentChannelPLL(void);
INTERFACE void msAPI_Tuner_SetCurrentChannelPLL(U16 u16TunerPLL);
INTERFACE U16 msAPI_Tuner_GetCurrentChannelPLL2UiStr(void);
INTERFACE BOOLEAN msAPI_Tuner_IsCurrentChannelAndSavedChannelSame(void);
INTERFACE void msAPI_Tuner_ConvertMediumAndChannelNumberToString(MEDIUM eMedium, U8 u8ChannelNumber, BYTE * sStationName);
INTERFACE U8 msAPI_Tuner_GetTuningProcessPercent(void);
INTERFACE void msAPI_Tuner_GetCurrentStationName(BYTE *sName);
INTERFACE void msAPI_Tuner_ChangeCurrentStationName(BYTE cStationNameChar, U8 u8Position);
INTERFACE BOOLEAN msAPI_Tuner_IsAFTNeeded(void);
INTERFACE void msAPI_Tuner_UpdateMediumAndChannelNumber(void);
INTERFACE void msAPI_Tuner_PrintTVAVSourceInformation(void);
INTERFACE U16 msAPI_Tuner_GetIF(void);
INTERFACE void msAPI_Tuning_IsScanL(BOOLEAN bEnable);
INTERFACE BOOLEAN msAPI_Tuner_IsCurrentAudioLPrime(void);
INTERFACE void msAPI_Tuner_SetCurrentAudioStandard(void);


#if ENABLE_SBTVD_SCAN
INTERFACE U8 msAPI_Tuner_GetNumberOfChBeFound_WhileAutoScan(void);
INTERFACE void msAPI_Reset_Tuner_GetNumberOfChBeFound_WhileAutoScan(void);
#endif

#if( TV_FREQ_SHIFT_CLOCK )
INTERFACE void msAPI_Tuner_Patch_TVShiftClk(BOOL bEnable);
INTERFACE void msAPI_Tuner_Patch_ResetTVShiftClk(void);
INTERFACE void msAPI_Tuner_Patch_TVShiftVDClk(BOOL bEnable);
#endif

#if ENABLE_FM_RADIO
INTERFACE void msAPI_SetTunerPLL_FM(U16 u16PLL);
#endif

BOOL msAPI_Tunning_Is_CurrentTuningState_Idle(void);

#undef INTERFACE



#endif // __MSAPI_TUNING_H__

