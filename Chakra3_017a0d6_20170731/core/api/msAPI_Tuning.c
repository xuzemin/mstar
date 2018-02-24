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
#define MSAPI_TUNING_C

#include <string.h>
#include "Board.h"
#include "msAPI_Global.h"
#include "msAPI_Tuning.h"
#include "msAPI_VD.h"
#include "msAPI_audio.h"
#if ENABLE_TTX
#include "msAPI_TTX.h"
#endif
#include "msAPI_FreqTableATV.h"
#include "msAPI_Memory.h"
#include "msAPI_Timer.h"

#include "Tuner.h"
#include "IF_Demodulator.h"
#include "GPIO.h"
#include "drvAVD.h"
#include "drvVIFInitial_MST.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ATVProc.h"
#include "MApp_UiMenuDef.h"
#include "drvVIFInitial_MST.h"
#include "MApp_ChannelChange.h"

#include "MApp_ZUI_ACTglobal.h"
#include "drvVIF.h"

//
//******************************************************************************
//

#define debugTuningPrint(a,b)    //printf(a,b)
#define L_SEARCH_DBG(x)          //x

//#define AUTO_TUNING_DEBUG                   // enable (define) or disable (undefine) debug code
#define AUTO_SCAN_TIME_PRINT        1


#if defined(AUTO_TUNING_DEBUG)
    #define AUTO_TUNING_PRINT(x)    x
#else
    #define AUTO_TUNING_PRINT(x)
#endif

#define DEBUG_TUNING(x)     //x

//
//******************************************************************************
//

#if (ENABLE_AUDIO_SYS_BTSC)
    extern BOOLEAN bForceCheckAudioMode;
#endif

#if ENABLE_AUTOTEST
    extern BOOLEAN g_bAutobuildDebug;
#endif

//------------------------------------------------------------------------------
// Locals
//------------------------------------------------------------------------------
typedef enum
{
    E_AUTO_SEARCH_TYPE_STOPED,
    E_AUTO_SEARCH_TYPE_ALLWAYUP,
    E_AUTO_SEARCH_TYPE_ALLWAYDOWN,
    E_AUTO_SEARCH_TYPE_ONETOUP,
    E_AUTO_SEARCH_TYPE_ONETODOWN
} AUTO_SEARCH_TYPE;

typedef enum
{
    E_TUNING_RANGE_CENTER,
    E_TUNING_RANGE_LOWER,
    E_TUNING_RANGE_UPPER,
    E_TUNING_RANGE_NEXTCHANNEL
} TUNING_RANGE;

typedef enum
{
    E_TUNING_STATUS_GOOD,
    E_TUNING_STATUS_OVER,
    E_TUNING_STATUS_UNDER,
    E_TUNING_STATUS_OVER_LITTLE,
    E_TUNING_STATUS_UNDER_LITTLE,
    E_TUNING_STATUS_OVER_MORE,
    E_TUNING_STATUS_UNDER_MORE,
    E_TUNING_STATUS_OUT_OF_AFCWIN,
} TUNING_STATUS;

typedef enum
{
    E_AGC_TUNING_STATUS_START,
    E_AGC_TUNING_STATUS_STOP
} AGC_TUNING_STATUS;


// AFT internal states
#if 1//(AUTO_TUNING_TYPE_SEL  == AUTO_TUNING_ALG_PAL_NEW)
    #define AFT_IDLE                        0x10

    #define AFT_GOTO_CHECK_VIFLOCK          0x11
    #define AFT_CHECK_VIFLOCK               0x12

    #define AFT_GOTO_CHECK_VDLOCK           0x13
    #define AFT_CHECK_VDLOCK                0x14

    #define AFT_JUMPFAR                     0x15    // <-<<<
    #define AFT_JUMPNEAR                    0x16
    #define AFT_JUMPNEARHALF                0x17
    #define AFT_TUNING                      0x18

    #define AFT_SHOWTIME1                   0x19
    #define AFT_SHOWTIME2                   0x1A

    #define AFT_DETECTVIDEO                 0x1B
    #define AFT_DETECTAUDIO                 0x1C
    #define AFT_CHECK_CNI                   0x1D

    #define AFT_MEMORIZECHDATA              0x1E
    #define AFT_MEMORIZEPRDATA              0x1F
    #define AFT_INCREASEPRNUMBER            0x20
    #define AFT_COMPLETE                    0x21
    #define AFT_CHANGEPROGRAM               0x22
    #define AFT_CHANGECHANNEL               0x23
    #define AFT_ONECHANNEL_AFT              0x24
    #define AFT_STABILIZE                   0x25
  #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    #define AFT_SWITCHIF                    0x26
  #endif
    #define AFT_SIGNAL_WEAK                 0x27
    #define AFT_L_SEARCH_CHECK              0x28
    #define AFT_CHECK_FALSESIGNAL           0x29

    #define AFT_CHECKSYNC                   0x30 //  SBTVD Brazil

    #define AFT_GOTO_CHECK_VIFLOCK_NTSC     0x41
    #define AFT_CHECK_VIFLOCK_NTSC          0x42
    #define AFT_GOTO_CHECK_VDLOCK_NTSC      0x43
    #define AFT_CHECK_VDLOCK_NTSC           0x44
    #define AFT_DETECTVIDEO_NTSC            0x45

#else

    #define AFT_IDLE                        0x10
    #define AFT_CHECKSYNC                   0x11
    #define AFT_CHECK_VDLOCK                0x12
    #define AFT_JUMPNEXT                    0x13    // <-<<<
    #define AFT_JUMPFAR                     0x14    // <-<<<
    #define AFT_JUMPNEAR                    0x15
    #define AFT_JUMPNEARHALF                0x16
    #define AFT_TUNING                      0x17
    #define AFT_SHOWTIME1                   0x18
    #define AFT_SHOWTIME2                   0x19
    #define AFT_DETECTVIDEO                 0x1A
    #define AFT_DETECTAUDIO                 0x1B
    #define AFT_MEMORIZECHDATA              0x1C
    #define AFT_MEMORIZEPRDATA              0x1D
    #define AFT_INCREASEPRNUMBER            0x1E
    #define AFT_COMPLETE                    0x1F
    #define AFT_CHANGEPROGRAM               0x20
    #define AFT_CHANGECHANNEL               0x21
    #define AFT_ONECHANNEL_AFT              0x22
    #define AFT_STABILIZE                   0x23
  #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    #define AFT_SWITCHIF                    0x24
  #endif
    #define AFT_SIGNAL_WEAK                 0x25
    #define AFT_L_SEARCH_CHECK              0x26

    #define AFT_CHECK_FALSESIGNAL           0x28

#endif

// Never change the following values and sequence.
    #define AFT_SYNCOK_1                    0x51
    #define AFT_SYNCOK_2                    0x52
    #define AFT_SYNCOK_3                    0x53
    #define AFT_SYNCOK_4                    0x54
    #define AFT_SYNCOK_5                    0x55
    #define AFT_NOSYNC_1                    0x61
    #define AFT_NOSYNC_2                    0x62
    #define AFT_NOSYNC_3                    0x63
    #define AFT_NOSYNC_4                    0x64
    #define AFT_NOSYNC_5                    0x65

//
//******************************************************************************
//

// PLL steps
#define PLLSTEP(x)                      (_u16TunerPLL+(x))

#define TUNER_PLL_REFRESH               0
#define TUNER_PLL_PLUS_37p5KHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(0):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(0):(1)) )
#define TUNER_PLL_PLUS_62p5KHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(1):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(1):(2)) )
#define TUNER_PLL_PLUS_87p5KHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(1):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(2):(3)) )
#define TUNER_PLL_PLUS_112p5KHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(2):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(2):(4)) )
#define TUNER_PLL_PLUS_137p5KHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(2):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(3):(4)) )
#define TUNER_PLL_PLUS_162p5KHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(2):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(3):(5)) )
#define TUNER_PLL_PLUS_187p5KHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(3):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(4):(6)) )
#define TUNER_PLL_PLUS_0p2MHz           ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(3):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(4):(6)) )
#define TUNER_PLL_PLUS_0p25MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(4):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(5):(8)) )
#define TUNER_PLL_PLUS_0p5MHz           ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(8):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(10):(16)) )
#define TUNER_PLL_PLUS_0p75MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(12):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(15):(24)) )
#define TUNER_PLL_PLUS_1MHz             ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(16):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(20):(32)) )
#define TUNER_PLL_PLUS_1p25MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(20):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(25):(40)) )
#define TUNER_PLL_PLUS_1p5MHz           ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(24):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(30):(48)) )
#define TUNER_PLL_PLUS_1p75MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(28):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(35):(56)) )
#define TUNER_PLL_PLUS_2MHz             ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(32):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(40):(64)) )
#define TUNER_PLL_PLUS_2p25MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(36):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(45):(72)) )
#define TUNER_PLL_PLUS_2p5MHz           ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(40):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(50):(80)) )
#define TUNER_PLL_PLUS_2p75MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(44):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(55):(88)) )
#define TUNER_PLL_PLUS_3MHz             ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(48):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(60):(96)) )
#define TUNER_PLL_PLUS_4MHz             ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(64):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(80):(128)) )
#define TUNER_PLL_PLUS_4p5MHz           ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(72):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(90):(144)) )
#define TUNER_PLL_PLUS_5MHz             ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(80):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(100):(160)) )
#define TUNER_PLL_PLUS_5p25MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(84):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(105):(168)) )
#define TUNER_PLL_PLUS_6p5MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(104):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(130):(208)) )

#define TUNER_PLL_MINUS_37p5KHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(0):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(0):(-1)) )
#define TUNER_PLL_MINUS_62p5KHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-1):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-1):(-2)) )
#define TUNER_PLL_MINUS_87p5KHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-1):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-2):(-3)) )
#define TUNER_PLL_MINUS_112p5KHz        ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-2):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-2):(-4)) )
#define TUNER_PLL_MINUS_137p5KHz        ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-2):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-3):(-4)) )
#define TUNER_PLL_MINUS_162p5KHz        ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-2):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-3):(-5)) )
#define TUNER_PLL_MINUS_187p5KHz        ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-3):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-4):(-6)) )
#define TUNER_PLL_MINUS_0p2MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-3):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-4):(-6)) )
#define TUNER_PLL_MINUS_0p25MHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-4):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-5):(-8)) )
#define TUNER_PLL_MINUS_0p5MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-8):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-10):(-16)) )
#define TUNER_PLL_MINUS_0p75MHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-12):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-15):(-24)) )
#define TUNER_PLL_MINUS_1MHz            ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-16):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-20):(-32)) )
#define TUNER_PLL_MINUS_1p25MHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-20):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-25):(-40)) )
#define TUNER_PLL_MINUS_1p5MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-24):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-30):(-48)) )
#define TUNER_PLL_MINUS_1p75MHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-28):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-35):(-56)) )
#define TUNER_PLL_MINUS_2MHz            ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-32):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-40):(-64)) )
#define TUNER_PLL_MINUS_2p25MHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-36):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-45):(-72)) )
#define TUNER_PLL_MINUS_2p5MHz          ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-40):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-50):(-80)) )
#define TUNER_PLL_MINUS_2p75MHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-44):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-55):(-88)) )
#define TUNER_PLL_MINUS_3MHz            ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-48):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-60):(-96)) )
#define TUNER_PLL_MINUS_4MHz            ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-64):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-80):(-128)) )
#define TUNER_PLL_MINUS_5MHz            ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-80):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-100):(-160)) )
#define TUNER_PLL_MINUS_5p25MHz         ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(-84):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(-105):(-168)) )

//
//******************************************************************************
//

#define FINE_TUNE_STEP                  1
#define NO_SYNC_COUNT_THRESHOLD         3
#define L_PRIME_BOUNDARY_FREQ           66500L // KHz
#define L_PRIME_FA_PLL                  ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(764):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(955):(1528)) )    // 47.75 MHz
#define L_PRIME_FB_PLL                  ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(892):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(1115):(1784)) )    // 55.75 MHz
#define L_PRIME_FC1_PLL                 ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(968):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(1210):(1936)) )    // 60.5 MHz
#define L_PRIME_FC_PLL                  ( (TN_FREQ_STEP==FREQ_STEP_62_5KHz)?(1020):((TN_FREQ_STEP==FREQ_STEP_50KHz)?(1275):(2040)) )// 63.75 MHz

#define UHF_MIN_FREQ_HZ                 300000000L // Hz

//
//******************************************************************************
//

static eAFTSTEP _eCurrentTuningState;
static MEDIUM _eMedium;
static U8 _u8ChannelNumber;
static U16 _u16TunerPLL;
#if (AUTO_TUNING_TYPE_SEL == AUTO_TUNING_ALG_PAL_NEW)
static U16 _u16Tune_MAX_PLL;
static U16 _u16Tune_LOW_PLL;
#endif
static U32 s_u32CurTunerFreq;
static U16 _u16TuningWaitTimer;
static U16 _u16AFTIdleTimer;
static U16 _u16RealtimeAFTBaseTunerPLL;
static U16 _u16UpdateStationNameTimer;
static U8 _sCurrentStationName[MAX_STATION_NAME];
static BOOLEAN _bChangeProgram;
static BOOLEANS _BOOLEANS;
static BOOLEAN _IsTuningSuspend;
static U8 u8ScanAFTCount = 0;

#if ENABLE_DBG_ATV_SCAN // for debug
static BOOLEAN _IsDbgTuning = 0;
static U8      _u8DbgTuningLoopTime = 0;
#endif

#if( (AUTO_TUNING_TYPE_SEL == AUTO_TUNING_ALG_DEFAULT)  \
   ||(AUTO_TUNING_TYPE_SEL == AUTO_TUNING_ALG_TST)      \
   ||(AUTO_TUNING_TYPE_SEL == AUTO_TUNING_ALG_PAL_NEW)  \
    )
static U8 u8ScanAFTFlag = 0;
static U8 _u8TVScanStepDownCount;
#endif

#define _bIsAFTNeeded               _BOOLEANS.bBOOL_0
#define _bIsLSearch                 _BOOLEANS.bBOOL_1
#define _bIsOneProgramDetected      _BOOLEANS.bBOOL_2
#define _bIsSpeedUp                 _BOOLEANS.bBOOL_3
#define _bIsPreProgramDetected      _BOOLEANS.bBOOL_4

// In the AFT_SHOWTIME2 State, sometimes it will goto Sync-Unloc
// Here we create the configurations for user to adjust
//<1>.Configuration-A: 60% LOCK = PASS
//<2>.Configuration-B: 20% LOCK = PASS
//<3>.Configuration-C: ALL PASS
//PS: Before tye this configuration, please try the VD-Sensitivit first
//     in the drvVD.c #define HSEN_NORMAL_...

#define VD_SYNC_CRITERION_CONFIG_ENABLE   0 //Default = Disable

#if (VD_SYNC_CRITERION_CONFIG_ENABLE)
  #if 1 //<1>.Configuration-A: 60% LOCK = PASS
    #define SYNC_LOCKED_PASS_NUM             3
    #define SYNC_LOCKED_BASE_NUM             5
    #define SYNC_DETECTED_PASS_NUM          3
    #define SYNC_DETECTED_BASE_NUM          5
  #endif

  #if 0 //<2>.Configuration-B:20% LOCK = PASS
    #define SYNC_LOCKED_PASS_NUM             1
    #define SYNC_LOCKED_BASE_NUM             5
    #define SYNC_DETECTED_PASS_NUM          1
    #define SYNC_DETECTED_BASE_NUM          5
  #endif

  #if 0 //<3>.Configuration-C: ALL PASS
    #define SYNC_LOCKED_PASS_NUM             0
    #define SYNC_LOCKED_BASE_NUM             5
    #define SYNC_DETECTED_PASS_NUM          0
    #define SYNC_DETECTED_BASE_NUM          5
  #endif
#endif
//------------------------------------------------------------------------------
// Adjustment-3 => <1>For frequency offset  issue (for example:+-50KHz)
//------------------------------------------------------------------------------
//** Description:     To avoid the frequency offset  issue,
//** When to use?:  if you found that you can't get the correct frequency after scan, you can try it.
//                          for example: The Correct Frequency = 55.25MhZ
//                                            You got 55.25MHz (+-)50KHz
//**How to use?      Define it (SPECIFIC_AFC_GOOD_VALUE) in your board define.
//                          Value = 1 => 62p5KHz
//                          Value = 0 => 37p5KHz (Default)


//------------------------------------------------------------------------------
// Local functions
//------------------------------------------------------------------------------
static void _RomStringCopy(char *sDestination, char ROM *sSource, U8 u8Size);
RFBAND _GetBand(U16 u16PLL);
static void _SetTunerPLL(U16 u16PLL);
static BOOLEAN _IsTunerStable(void);
static void _OneChannelAFT(void);
static BOOLEAN _IsLPrime(void);

static BOOLEAN _CheckLPrimeBoundary_ByFreq(U32 u32TunerFreq);
static BOOLEAN _CheckLPrimeBoundary(void);

static void _SetDefaultStationName(BYTE *sStationName);
static void _DetectStationName(void);

#if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
static BOOLEAN _SetVifIfFreq(void);
#endif

extern TUNING_STATUS _GetTuningStatus(void);

//------------------------------------------------------------------------------
// Local Functions.
//------------------------------------------------------------------------------
static void msAPI_ConvertFrequencyToString(WORD wIntegerOfFreq, WORD wFractionOfFreq, char *pcBuffer)
{
    pcBuffer[0] = ((wIntegerOfFreq/100) == 0) ? ' ' : '0'+(wIntegerOfFreq/100);
    pcBuffer[1] = '0'+((wIntegerOfFreq%100)/10);
    pcBuffer[2] = '0'+(wIntegerOfFreq%10);
    pcBuffer[3] = '.';
    pcBuffer[4] = '0'+(wFractionOfFreq/100);
    pcBuffer[5] = '0'+((wFractionOfFreq%100)/10);
    pcBuffer[6] = 'M';
    pcBuffer[7] = 'H';
    pcBuffer[8] = 'z';
}

static BOOLEAN _IsTunerStable(void)
{
    if ( _u16TuningWaitTimer == 0 )
    {
        return TRUE;
    }

    _u16TuningWaitTimer--;


    if ( _bIsSpeedUp )
    {
        if (_u16TuningWaitTimer > AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_SPEEP_UP)
        {
            _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_SPEEP_UP;
        }
    }

    return FALSE;
}

#if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF) || (FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
static void _OneChannelAFT(void)
{
    return;
}
#elif (FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
static void _OneChannelAFT(void)
{
    WORD wUpperLimitPLL;
    WORD wLowerLimitPLL;
    WORD wBasePLL;
    WORD wOriginalPLL;
    TUNING_RANGE eNextTuningRange;
    BYTE i;

    wOriginalPLL = _u16TunerPLL;

    if ( _GetTuningStatus() != E_TUNING_STATUS_GOOD )
    {

        debugTuningPrint("One Channel AFT: Start\n", 0);

        eNextTuningRange = E_TUNING_RANGE_CENTER;

        while ( eNextTuningRange != E_TUNING_RANGE_NEXTCHANNEL )
        {
            switch ( eNextTuningRange )
            {
            case E_TUNING_RANGE_CENTER:
                wBasePLL = wOriginalPLL;
                wUpperLimitPLL = wOriginalPLL + TUNER_PLL_PLUS_1p75MHz;
                wLowerLimitPLL = wOriginalPLL + TUNER_PLL_MINUS_1p75MHz;
                eNextTuningRange = E_TUNING_RANGE_LOWER;
                break;

            case E_TUNING_RANGE_LOWER:
                wBasePLL = wOriginalPLL + TUNER_PLL_MINUS_1p75MHz;
                wUpperLimitPLL = wOriginalPLL + TUNER_PLL_PLUS_0p2MHz;
                wLowerLimitPLL = wOriginalPLL + TUNER_PLL_MINUS_2p25MHz;
                eNextTuningRange = E_TUNING_RANGE_UPPER;
                break;

            case E_TUNING_RANGE_UPPER:
                wBasePLL = wOriginalPLL + TUNER_PLL_PLUS_1p75MHz;
                wUpperLimitPLL = wOriginalPLL + TUNER_PLL_PLUS_2p25MHz;
                wLowerLimitPLL = wOriginalPLL + TUNER_PLL_MINUS_0p2MHz;
                eNextTuningRange = E_TUNING_RANGE_NEXTCHANNEL;
                break;

            default:
                debugTuningPrint("One Channel AFT: Fail\n", 0);

                _SetTunerPLL( wOriginalPLL );
                return;
            }

            _SetTunerPLL( wBasePLL );

            while ( _IsTunerStable() == FALSE )
            {
                msAPI_Timer_Delayms(10);

                msAPI_AVD_UpdateAutoAVState();
            }

            if ( msAPI_AVD_IsSyncLocked() == FALSE )
            {
                msAPI_Timer_Delayms(10);

                if ( msAPI_AVD_IsSyncLocked() == FALSE )
                {
                    msAPI_Timer_Delayms(10);

                    if ( msAPI_AVD_IsSyncLocked() == FALSE )
                    {
                        continue;
                    }
                }
            }

            for ( i = 0; i < TUNER_PLL_PLUS_2MHz; i++ )
            {
                msAPI_AVD_UpdateAutoAVState();

                if ( _GetTuningStatus() == E_TUNING_STATUS_GOOD )
                {
                    if ( msAPI_AVD_IsSyncLocked() == TRUE )
                    {
                        debugTuningPrint("One Channel AFT: OK\n", 0);
                        return;
                    }
                }

                switch( MDrv_IFDM_GetFreqDev() )
                {
                case E_AFC_BELOW_MINUS_125pKHz:
                    _SetTunerPLL( PLLSTEP(2) );
                    break;

                case E_AFC_MINUS_62p5KHz:
                    _SetTunerPLL( PLLSTEP(1) );
                    break;

                case E_AFC_PLUS_62p5KHz:
                    _SetTunerPLL( PLLSTEP(-1) );
                    break;

                case E_AFC_ABOVE_PLUS_125pKHz:
                    _SetTunerPLL( PLLSTEP(-2) );
                    break;
                }

                if ( (_u16TunerPLL <= wLowerLimitPLL) || (wUpperLimitPLL <= _u16TunerPLL) )
                {
                    break;
                }
            }
        }

        debugTuningPrint("One Channel AFT: Fail\n", 0);

        _SetTunerPLL( wOriginalPLL );
    }
}
#else

static void _OneChannelAFT(void)
{
    WORD wUpperLimitPLL;
    WORD wLowerLimitPLL;
    WORD wBasePLL;
    WORD wOriginalPLL;
    TUNING_RANGE eNextTuningRange;
    BYTE i;

    PRINT_FUNC_START_TIME();

    wOriginalPLL = _u16TunerPLL;

    if ( _IsLPrime() == TRUE )
    {
        for ( i=0; i <= TUNER_PLL_PLUS_4MHz ; i++ )
        {
            msAPI_AVD_UpdateAutoAVState();

            switch ( MDrv_IFDM_GetFreqDev() )
            {
            case E_AFC_BELOW_MINUS_187p5KHz:
                _SetTunerPLL( PLLSTEP(8) );
                break;

            case E_AFC_MINUS_162p5KHz:
                _SetTunerPLL( PLLSTEP(5) );
                break;

            case E_AFC_MINUS_137p5KHz:
                _SetTunerPLL( PLLSTEP(4) );
                break;

            case E_AFC_MINUS_112p5KHz:
                _SetTunerPLL( PLLSTEP(3) );
                break;

            case E_AFC_MINUS_87p5KHz:
                _SetTunerPLL( PLLSTEP(3) );
                break;

            case E_AFC_MINUS_62p5KHz:
                _SetTunerPLL( PLLSTEP(2) );
                return;

            case E_AFC_MINUS_37p5KHz:
                _SetTunerPLL( PLLSTEP(1) );
                return;

            case E_AFC_MINUS_12p5KHz:
                return;

            case E_AFC_PLUS_12p5KHz:
                return;

            case E_AFC_PLUS_37p5KHz:
                _SetTunerPLL( PLLSTEP(-1) );
                return;

            case E_AFC_PLUS_62p5KHz:
                _SetTunerPLL( PLLSTEP(-2) );
                return;

            case E_AFC_PLUS_87p5KHz:
                _SetTunerPLL( PLLSTEP(-3) );
                break;

            case E_AFC_PLUS_112p5KHz:
                _SetTunerPLL( PLLSTEP(-3) );
                break;

            case E_AFC_PLUS_137p5KHz:
                _SetTunerPLL( PLLSTEP(-4) );
                break;

            case E_AFC_PLUS_162p5KHz:
                _SetTunerPLL( PLLSTEP(-5) );
                break;

            case E_AFC_ABOVE_PLUS_187p5KHz:
                _SetTunerPLL( PLLSTEP(-8) );
                break;

            default:
                _SetTunerPLL(wOriginalPLL);
                return;
            }

            if ( DIFFERENCE(wOriginalPLL,_u16TunerPLL) > TUNER_PLL_PLUS_2MHz )
            {
                if ( _u16TunerPLL < wOriginalPLL )
                {
                    _SetTunerPLL( wOriginalPLL + TUNER_PLL_PLUS_2MHz );
                }
                else
                {
                    _SetTunerPLL( wOriginalPLL + TUNER_PLL_MINUS_2MHz );
                }
            }
        }

        _SetTunerPLL(wOriginalPLL);

        return;
    }

    if ( _GetTuningStatus() != E_TUNING_STATUS_GOOD )
    {

        debugTuningPrint("One Channel AFT: Start\n", 0);

        eNextTuningRange = E_TUNING_RANGE_CENTER;

        while ( eNextTuningRange != E_TUNING_RANGE_NEXTCHANNEL )
        {
            switch ( eNextTuningRange )
            {
            case E_TUNING_RANGE_CENTER:
                wBasePLL = wOriginalPLL;
                wUpperLimitPLL = wOriginalPLL + TUNER_PLL_PLUS_1p75MHz;
                wLowerLimitPLL = wOriginalPLL + TUNER_PLL_MINUS_1p75MHz;
                eNextTuningRange = E_TUNING_RANGE_LOWER;
                break;

            case E_TUNING_RANGE_LOWER:
                wBasePLL = wOriginalPLL + TUNER_PLL_MINUS_1p75MHz;
                wUpperLimitPLL = wOriginalPLL + TUNER_PLL_PLUS_0p2MHz;
                wLowerLimitPLL = wOriginalPLL + TUNER_PLL_MINUS_2p25MHz;
                eNextTuningRange = E_TUNING_RANGE_UPPER;
                break;

            case E_TUNING_RANGE_UPPER:
                wBasePLL = wOriginalPLL + TUNER_PLL_PLUS_1p75MHz;
                wUpperLimitPLL = wOriginalPLL + TUNER_PLL_PLUS_2p25MHz;
                wLowerLimitPLL = wOriginalPLL + TUNER_PLL_MINUS_0p2MHz;
                eNextTuningRange = E_TUNING_RANGE_NEXTCHANNEL;
                break;

            default:
                debugTuningPrint("One Channel AFT: Fail\n", 0);

                _SetTunerPLL( wOriginalPLL );
                return;
            }

            _SetTunerPLL( wBasePLL );

            while ( _IsTunerStable() == FALSE )
            {
                msAPI_Timer_Delayms(10);

                msAPI_AVD_UpdateAutoAVState();
            }

            if ( msAPI_AVD_IsSyncLocked() == FALSE )
            {
                msAPI_Timer_Delayms(10);

                if ( msAPI_AVD_IsSyncLocked() == FALSE )
                {
                    msAPI_Timer_Delayms(10);

                    if ( msAPI_AVD_IsSyncLocked() == FALSE )
                    {
                        continue;
                    }
                }
            }

            for ( i = 0; i < TUNER_PLL_PLUS_2MHz; i++ )
            {
                msAPI_AVD_UpdateAutoAVState();

                if ( _GetTuningStatus() == E_TUNING_STATUS_GOOD )
                {
                    if ( msAPI_AVD_IsSyncLocked() == TRUE )
                    {
                        debugTuningPrint("One Channel AFT: OK\n", 0);
                        return;
                    }
                }

                switch( MDrv_IFDM_GetFreqDev() )
                {
                case E_AFC_BELOW_MINUS_187p5KHz:
                    _SetTunerPLL( PLLSTEP(3) );
                    break;

                case E_AFC_MINUS_162p5KHz:
                    _SetTunerPLL( PLLSTEP(3) );
                    break;

                case E_AFC_MINUS_137p5KHz:
                    _SetTunerPLL( PLLSTEP(2) );
                    break;

                case E_AFC_MINUS_112p5KHz:
                    _SetTunerPLL( PLLSTEP(2) );
                    break;

                case E_AFC_MINUS_87p5KHz:
                    _SetTunerPLL( PLLSTEP(2) );
                    break;

                case E_AFC_MINUS_62p5KHz:
                    _SetTunerPLL( PLLSTEP(1) );
                    break;

                case E_AFC_MINUS_37p5KHz:
                    _SetTunerPLL( PLLSTEP(1) );
                    break;

                case E_AFC_PLUS_37p5KHz:
                    _SetTunerPLL( PLLSTEP(-1) );
                    break;

                case E_AFC_PLUS_62p5KHz:
                    _SetTunerPLL( PLLSTEP(-1) );
                    break;

                case E_AFC_PLUS_87p5KHz:
                    _SetTunerPLL( PLLSTEP(-2) );
                    break;

                case E_AFC_PLUS_112p5KHz:
                    _SetTunerPLL( PLLSTEP(-2) );
                    break;

                case E_AFC_PLUS_137p5KHz:
                    _SetTunerPLL( PLLSTEP(-2) );
                    break;

                case E_AFC_PLUS_162p5KHz:
                    _SetTunerPLL( PLLSTEP(-3) );
                    break;

                case E_AFC_ABOVE_PLUS_187p5KHz:
                    _SetTunerPLL( PLLSTEP(-3) );
                    break;

                default:
                    break;
                }

                if ( (_u16TunerPLL <= wLowerLimitPLL) || (wUpperLimitPLL <= _u16TunerPLL) )
                {
                    break;
                }
            }
        }

        debugTuningPrint("One Channel AFT: Fail\n", 0);

        _SetTunerPLL( wOriginalPLL );
    }

    PRINT_FUNC_END_TIME();
}

#endif

static void _RomStringCopy(char *sDestination, char ROM *sSource, U8 u8Size)
{
    U8 i;

    for ( i = 0; i < u8Size; i++ )
    {
        sDestination[i] = sSource[i];
    }
}

RFBAND _GetBand(U16 u16PLL)
{
    if ( u16PLL < VHF_HIGHMIN_PLL )
    {
        return E_RFBAND_VHF_LOW;
    }

    if ( u16PLL < UHF_MIN_PLL )
    {
        return E_RFBAND_VHF_HIGH;
    }

    return E_RFBAND_UHF;
}

static U32 _TunerPllStepToRealFreq(U16 u16TunerPll)
{
#if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
    return (U32)u16TunerPll * 62500;
#elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
    return (U32)u16TunerPll * 50000;
#else
    #error "unknown tuner step"
#endif
}

static BOOLEAN _CheckLPrimeBoundary_ByFreq(U32 u32TunerFreq)
{
    if( (u32TunerFreq/1000) < L_PRIME_BOUNDARY_FREQ )
        return TRUE;
    else
        return FALSE;
}

static BOOLEAN _CheckLPrimeBoundary(void)
{
    U32 u32TunerFreq = _TunerPllStepToRealFreq(_u16TunerPLL);

    return _CheckLPrimeBoundary_ByFreq(u32TunerFreq);
}

static void _SetDefaultStationName(BYTE *sStationName)
{
    int i;

    for ( i = 0; i < (MAX_STATION_NAME-1); i++ )
    {
        sStationName[i] = '-';
    }
    sStationName[MAX_STATION_NAME-1] = '\0';
}


static BOOLEAN _IsLPrime(void)
{
    /*
    WORD wLPrimeBoundaryPLL;

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    wLPrimeBoundaryPLL = (WORD)((L_PRIME_BOUNDARY_FREQ * 10) / 625);
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    wLPrimeBoundaryPLL = (WORD)(L_PRIME_BOUNDARY_FREQ / 50);
#else
    wLPrimeBoundaryPLL = (WORD)((L_PRIME_BOUNDARY_FREQ * 100) / 3125);
#endif // TN_FREQ_STEP
*/

    if( (msAPI_AUD_GetAudioStandard() == E_AUDIOSTANDARD_L)
      //&&(_u16TunerPLL < wLPrimeBoundaryPLL)
      &&(_CheckLPrimeBoundary())
      )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


#if (TV_FREQ_SHIFT_CLOCK)
U32 g_u32Freq = 0;
void _TVShiftClk(AVD_ATV_CLK_TYPE u8Mode)
{
    //printf("\r\n _TVShiftClk=%x, %x\n",u8Mode, g_u8_ShiftClk_LastMode);
    if( u8Mode != g_u8_ShiftClk_LastMode )
    {
        debugTuningPrint("\r\n_TVShiftClk=%d", g_u32Freq);
        debugTuningPrint("\r\nTv shift Clk=%d\n", u8Mode);
        switch (u8Mode)
        {
            case E_ATV_CLK_TYPE1_42MHZ:
                //printf("--E_ATV_CLK_TYPE1_42MHZ---\n");
                msApi_AUD_SIF_Shift(MSAPI_AUD_SIF_42M);
                DRV_VIF_ShiftClk((U8)u8Mode);
                msAPI_AVD_ShiftClk(E_ATV_CLK_TYPE1_42MHZ);
                break;
            case E_ATV_CLK_TYPE2_44P4MHZ:
                //printf("--E_ATV_CLK_TYPE1_44p4MHZ---\n");
                msApi_AUD_SIF_Shift(MSAPI_AUD_SIF_44M);
                DRV_VIF_ShiftClk((U8)u8Mode);
                msAPI_AVD_ShiftClk(E_ATV_CLK_TYPE2_44P4MHZ);
                break;
            case E_ATV_CLK_ORIGIN_43P2MHZ:
            default:
                //printf("--E_ATV_CLK_TYPE1_43.2MHZ--\n");
                msApi_AUD_SIF_Shift(MSAPI_AUD_SIF_43M);
                DRV_VIF_ShiftClk((U8)u8Mode);
                msAPI_AVD_ShiftClk(E_ATV_CLK_ORIGIN_43P2MHZ);
                break;
        }
        //msAPI_Tuner_SetIF();
        g_u8_ShiftClk_LastMode = (U8)u8Mode;
    }

}
static AVD_ATV_CLK_TYPE _Get_Shift_Mode(U32 u32Freq)
{
    U32 u32Freq_KHz = u32Freq / 1000;
    //printf("\r\nEnable SW Patch Freq= %d", u32Freq_KHz);

    if (u32Freq_KHz <= 237000)   // 0~237MHz
    {
        if (((u32Freq_KHz >= 85250)&&(u32Freq_KHz <= 87650)) ||
            ((u32Freq_KHz >= 127250)&&(u32Freq_KHz <= 130850)) ||
            ((u32Freq_KHz >= 141250)&&(u32Freq_KHz <= 145250)) ||
            ((u32Freq_KHz >= 169250)&&(u32Freq_KHz <= 174050)) ||
            ((u32Freq_KHz >= 211250)&&(u32Freq_KHz <= 217250)))
        {
            return E_ATV_CLK_TYPE1_42MHZ;
        }
        else if (((u32Freq_KHz >= 81400)&&(u32Freq_KHz <= 83800)) ||
            ((u32Freq_KHz >= 124600)&&(u32Freq_KHz <= 127000)) ||
            ((u32Freq_KHz >= 137400)&&(u32Freq_KHz <141250)) ||
            ((u32Freq_KHz >= 167800)&&(u32Freq_KHz <= 169000)))
        {
            return E_ATV_CLK_TYPE2_44P4MHZ;
        }
    }
    else if (u32Freq_KHz <= 453000)   // 237~453MHz
    {
        if (((u32Freq_KHz >= 253250)&&(u32Freq_KHz <= 260450)) ||
            ((u32Freq_KHz >= 281250)&&(u32Freq_KHz <= 289250)) ||
            ((u32Freq_KHz >= 295250)&&(u32Freq_KHz <= 303650)) ||
            ((u32Freq_KHz >= 340600)&&(u32Freq_KHz <= 346850)) ||
            ((u32Freq_KHz >= 383800)&&(u32Freq_KHz <= 390050)) ||
            ((u32Freq_KHz >= 427000)&&(u32Freq_KHz <= 433250)))
        {
            return E_ATV_CLK_TYPE1_42MHZ;
        }
    }
    else if (u32Freq_KHz <= 669000)   // 453~669MHz
    {
        if (((u32Freq_KHz >= 421250)&&(u32Freq_KHz <= 433250)) ||
            ((u32Freq_KHz >= 470200)&&(u32Freq_KHz <= 476450)) ||
            ((u32Freq_KHz >= 513400)&&(u32Freq_KHz <= 519650)) ||
            ((u32Freq_KHz >= 556600)&&(u32Freq_KHz <= 562850)) ||
            ((u32Freq_KHz >= 561250)&&(u32Freq_KHz <= 577250)) ||
            ((u32Freq_KHz >= 599800)&&(u32Freq_KHz <= 606050)) ||
            ((u32Freq_KHz >= 643000)&&(u32Freq_KHz <= 649250)))
        {
            return E_ATV_CLK_TYPE1_42MHZ;
        }
    }
    else
    {
        if (((u32Freq_KHz >= 686200)&&(u32Freq_KHz <= 692450)) ||
            ((u32Freq_KHz >= 701250)&&(u32Freq_KHz <= 721250)) ||
            ((u32Freq_KHz >= 729400)&&(u32Freq_KHz <= 735650)) ||
            ((u32Freq_KHz >= 772600)&&(u32Freq_KHz <= 778850)) ||
            ((u32Freq_KHz >= 815800)&&(u32Freq_KHz <= 822050)) ||
            ((u32Freq_KHz >= 859000)&&(u32Freq_KHz <= 865250)))
        {
            return E_ATV_CLK_TYPE1_42MHZ;
        }
    }
    return E_ATV_CLK_ORIGIN_43P2MHZ;

}


static void _Set_Shift_Freq(U32 u32Freq)
{
    AVD_ATV_CLK_TYPE u8FreqShiftMode = E_ATV_CLK_ORIGIN_43P2MHZ;
#if ENABLE_VD_PACH_IN_CHINA
  #if(CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER)
    DWORD u16DescramblerBoxDelay;
  #endif
#endif

#if ( (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)            \
    ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)     \
    ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)    \
    )
    if ( msAPI_Tuner_IsTuningProcessorBusy() == TRUE )
#endif
    {
        _TVShiftClk(E_ATV_CLK_ORIGIN_43P2MHZ);
        return;
    }

    g_u32Freq = u32Freq;
    u8FreqShiftMode=_Get_Shift_Mode(u32Freq);
    _TVShiftClk(u8FreqShiftMode);

#if ENABLE_VD_PACH_IN_CHINA
  #if(CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER)
    u16DescramblerBoxDelay = (DWORD)G_FACTORY_SETTING.stVDSetting.Vif_PROGRAMMABLE_DELAY;
    u16DescramblerBoxDelay = (u16DescramblerBoxDelay*36)/10;
    if(G_FACTORY_SETTING.stVDSetting.China_DESCRAMBLER_BOX == 7)
    {
         DRV_VIF_SetParameter(VIF_PARA_SET_DESCRAMBLERBOX_DELAY, &u16DescramblerBoxDelay, sizeof(DWORD));
    }
  #endif
#endif
}

void msAPI_Tuner_Patch_TVShiftClk(BOOL bEnable)
{
    U32 u32TunerFreq;

    //printf("\r\nmsAPI_Tuner_Patch_TVShiftClk=%x",(U16)bEnable);

    if (bEnable)
    {
      #if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
        u32TunerFreq = (U32)_u16TunerPLL * 62500;
      #elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
        u32TunerFreq = (U32)_u16TunerPLL * 50000;
      #else
        #error "unknown step"
      #endif
        _Set_Shift_Freq(u32TunerFreq);
    }
    else
    {
        _TVShiftClk(E_ATV_CLK_ORIGIN_43P2MHZ);
    }
}

void msAPI_Tuner_Patch_ResetTVShiftClk(void)
{
    g_u8_ShiftClk_LastMode = 0xFF;
}

void msAPI_Tuner_Patch_TVShiftVDClk(BOOL bEnable)
{
    U32 u32Freq;
    AVD_ATV_CLK_TYPE u8FreqShiftMode = E_ATV_CLK_ORIGIN_43P2MHZ;
    debugTuningPrint("msAPI_Tuner_Patch_TVShiftVDClk=%x\n",(U16)bEnable);

    if (bEnable)
    {
      #if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
        u32Freq= (U32)_u16TunerPLL * 62500;
      #elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
        u32Freq = (U32)_u16TunerPLL * 50000;
      #else
        #error "unknown step"
      #endif

        //printf("\r\nEnable VD shift Patch Freq= %d", u32Freq);
        u8FreqShiftMode=_Get_Shift_Mode(u32Freq);
        msAPI_AVD_ShiftClk(u8FreqShiftMode);
    }
    else
    {
        msAPI_AVD_ShiftClk(E_ATV_CLK_ORIGIN_43P2MHZ);
    }
}

#endif


#if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))

//static void _SetTunerPLL(U16 u16PLL);

static U16 s_u16IfFreqPre = TUNER_IF_FREQ_KHz;

void msAPI_Tuner_Clear_IfFreqStatus(void)
{
    s_u16IfFreqPre =0;
}

void msAPI_SetTunerPLL(void)  //20100604EL
{
    _SetTunerPLL(msAPI_ATV_GetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber()));
}

#if ENABLE_FM_RADIO
void msAPI_SetTunerPLL_FM(U16 u16PLL)
{
    PRINT_CURRENT_LINE();

    printf("msAPI_SetTunerPLL_FM(u16PLL=%u)\n", u16PLL);

    _SetTunerPLL(u16PLL);
}
#endif

static BOOLEAN _SetVifIfFreq(void)
{
    U16 u16IfFreq;


    if ( FALSE == _IsLPrime() )
    {
        u16IfFreq = TUNER_IF_FREQ_KHz;
    }
    else
    {
        u16IfFreq = TUNER_L_PRIME_IF_FREQ_KHz;
    }
    if (s_u16IfFreqPre != u16IfFreq)
    {
        MDrv_IFDM_SetVifIfFreq(u16IfFreq) ;
        s_u16IfFreqPre = u16IfFreq;
    }

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA && 0 == CHINA_DESCRAMBLER_BOX)
    float X = 41.46; //31.85;  41.46(6FF)
    DWORD Y = DEC_TO_HEX((U16)(X * 43.2));
    DRV_VIF_SetParameter(VIF_PARA_SET_DESCRAMBLERBOX_DELAY, &Y, sizeof(DWORD));
#endif

    return TRUE;
}
#endif


extern BOOL gbTVAutoScanChannelEnable;

#if ENABLE_DEBUG_TUNING_TIME
U32 g_u32devTunerSetFreq_UseTotalTime = 0;
U32 g_u32SetTunerPLL_UseTotalTime = 0;
#endif

static void _SetTunerPLL(U16 u16PLL)
{
#if( ENABLE_DEBUG_TUNING_TIME )
    U32 u32Time1 = MsOS_GetSystemTime();
#endif

    static U32 s_u32PreTunerFreq = 0;

    //printf("  _SetTunerPLL() at %u\n", MsOS_GetSystemTime());
    PRINT_FUNC_START_TIME();

    _bIsPreProgramDetected = FALSE;

    if ( u16PLL < VHF_LOWMIN_PLL )
    {
        u16PLL = VHF_LOWMIN_PLL;
    }
    else if ( UHF_MAX_PLL < u16PLL )
    {
        if(u16PLL == DEFAULT_PLL) //DEFAULT_PLL
            ; //keep original Default PLL
        else
            u16PLL = UHF_MAX_PLL;
    }

#if(AUTO_TUNING_TYPE_SEL==AUTO_TUNING_ALG_PAL_NEW)

    _u16TuningWaitTimer =1;

#else
    if  ( DIFFERENCE(_u16TunerPLL, u16PLL) < TUNER_PLL_PLUS_0p25MHz )
    {
      #if TV_SCAN_PAL_SECAM_ONCE//For L Search, From BG to SCEAM-L, Step=0, u16TuningWaitTimer = WAIT_230ms;
        if ((_bIsLSearch))
            _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP_L;
        else
      #endif
            _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P25MHZ_STEP;
    }
    else if ( DIFFERENCE(_u16TunerPLL, u16PLL) < TUNER_PLL_PLUS_0p5MHz )
    {
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_0P5MHZ_STEP;
    }
    else if ( DIFFERENCE(_u16TunerPLL, u16PLL) < TUNER_PLL_PLUS_4MHz )
    {
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_4MHZ_STEP;
    }
    else
    {
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_MAX_STEP;
    }

    if ( _GetBand(_u16TunerPLL) != _GetBand(u16PLL) )
    {
        _u16TuningWaitTimer = AUTO_TUNING_DEFAULT_ALG_WAIT_TIME_CROSS_BAND_STEP;
    }
#endif

    _u16TunerPLL = u16PLL;

    {
        AUTO_TUNING_PRINT( printf("<_u16TunerPLL=%d.%d MHz>",
                              msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL),
                              msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL)) );
    }
#if ENABLE_AUTOTEST
    if(g_bAutobuildDebug && (msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL) == 850))
    {
        printf("31_ATV_Failed\n");
    }
#endif

    s_u32CurTunerFreq = _TunerPllStepToRealFreq(_u16TunerPLL);

    DEBUG_TUNING(printf(" s_u32CurTunerFreq=%dK\n", s_u32CurTunerFreq/1000););

#if(CHAKRA3_AUTO_TEST)
    printf(" s_u32CurTunerFreq=%dK\n", s_u32CurTunerFreq/1000);
#endif


#if ENABLE_DEBUG_TUNING_TIME
    U32 u32TunerTime1 = MsOS_GetSystemTime();
#endif

    //DEBUG_TUNING_TIME( printf(" t1=%u,", MsOS_GetSystemTime()); );

#if (  (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)         \
    || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)         \
    || (FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER)     \
    || (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)        \
    || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)        \
    || (FRONTEND_TUNER_TYPE == SILAB_2190B_TUNER)        \
    || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)        \
    || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)        \
    || (FRONTEND_TUNER_TYPE == NXP_TDA18273_TUNER)      \
    || (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)      \
    || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)      \
    || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)     \
    || (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER)    \
    || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER)    \
    || (FRONTEND_TUNER_TYPE == SAMSUNG_SI2176_TUNER)    \
    || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER)          \
    || (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)       \
    || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)       \
    || (FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
    )
    devTunerSetFreq( s_u32CurTunerFreq );
#else
    devTunerSetPLLData( _u16TunerPLL+msAPI_Tuner_GetIF(), _GetBand(_u16TunerPLL) );
#endif

#if ENABLE_DEBUG_TUNING_TIME
    if( gbTVAutoScanChannelEnable )
    {
        U32 u32TunerTime2 = msAPI_Timer_DiffTime_2(u32TunerTime1, MsOS_GetSystemTime());
        g_u32devTunerSetFreq_UseTotalTime += u32TunerTime2;
        if( u32TunerTime2 >= 2 )
        {
            printf("devTunerSetFreq use %u/%u\n", u32TunerTime2, g_u32devTunerSetFreq_UseTotalTime);
        }
    }
    else
    {
        if( g_u32devTunerSetFreq_UseTotalTime )
        {
            printf("_s_u32TunerUseTotalTime=%u\n", g_u32devTunerSetFreq_UseTotalTime);
            g_u32devTunerSetFreq_UseTotalTime = 0;
        }
    }
#endif

    //DEBUG_TUNING_TIME( printf(" t2=%u,", MsOS_GetSystemTime()); );

#if( (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210) \
   ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)         \
   ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)  \
   )
    MDrv_IFDM_SetFreqBand(_GetBand(_u16TunerPLL));

    _SetVifIfFreq();
#endif

    //DEBUG_TUNING_TIME( printf(" t3=%u,", MsOS_GetSystemTime()); );

#if (TV_FREQ_SHIFT_CLOCK)
    _Set_Shift_Freq(s_u32CurTunerFreq);
#endif

    //DEBUG_TUNING_TIME( printf(" t4=%u,", MsOS_GetSystemTime()); );

    s_u32PreTunerFreq = s_u32CurTunerFreq;

    //printf("  _SetTunerPLL() end at %u\n", MsOS_GetSystemTime());

#if( (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)   \
   ||(FRONTEND_TUNER_TYPE == MxL_601SI_TUNER))
{
    msAPI_Timer_Delayms(30);
    MDrv_VIF_Handler(gbTVAutoScanChannelEnable);
    msAPI_Timer_Delayms(5);
    MDrv_VIF_Handler(gbTVAutoScanChannelEnable);
    msAPI_Timer_Delayms(5);
}
#endif

#if( ENABLE_DEBUG_TUNING_TIME )
    if( gbTVAutoScanChannelEnable )
    {
        U32 u32Time2 = msAPI_Timer_DiffTime_2(u32Time1, MsOS_GetSystemTime());
        g_u32SetTunerPLL_UseTotalTime += u32Time2;
        if( u32Time2 >= 2 )
        {
            printf("_SetTunerPLL use %u\n", u32Time2);
        }
    }
    else
    {
        if( g_u32SetTunerPLL_UseTotalTime )
        {
            printf("g_u32SetTunerPLL_UseTotalTime=%u\n", g_u32SetTunerPLL_UseTotalTime);
            g_u32SetTunerPLL_UseTotalTime = 0;
        }
    }
#endif

    PRINT_FUNC_END_TIME();
}

static void _DetectStationName(void)
{
#if ENABLE_TTX
    if ( TRUE != msAPI_TTX_GetStationNameFromTeletext(_sCurrentStationName, MAX_STATION_NAME, NULL) )
#endif
    {
        msAPI_Tuner_ConvertMediumAndChannelNumberToString(_eMedium, _u8ChannelNumber, _sCurrentStationName);
    }

    _u16UpdateStationNameTimer = 197;
}

/******************************************************************************/
///- This function will initialize tuner
/* ****************************************************************************/
void msAPI_Tuner_Init(void)
{
    devTunerInit();

    // VIF already inited...
    //MDrv_IFDM_Init();

    // Set default IF
    msAPI_Tuner_SetIF();

    _eCurrentTuningState = AFT_IDLE;

    _SetTunerPLL(msAPI_ATV_GetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber()));

    _bIsOneProgramDetected = FALSE;

    //Redundant, will be called at SetInputSource
    //msAPI_AUD_SetAudioStandard( msAPI_ATV_GetAudioStandard(msAPI_ATV_GetCurrentProgramNumber()) );

    _u16TuningWaitTimer = 0;

    _u16AFTIdleTimer = 0;

#if(FRONTEND_TUNER_TYPE == NXP_TD1616EF_TUNER || FRONTEND_TUNER_TYPE == LG_TDTC_G001D_TUNER)
    _bIsAFTNeeded = TRUE;
#else
    _bIsAFTNeeded = FALSE;
#endif

    msAPI_Tuner_SetRealtimeAFTBaseTunerPLL(_u16TunerPLL);

    msAPI_ATV_GetMediumAndChannelNumber(msAPI_ATV_GetCurrentProgramNumber(), &_eMedium, &_u8ChannelNumber);

    _SetDefaultStationName(_sCurrentStationName);

    _u16UpdateStationNameTimer = 0;

    _bChangeProgram = TRUE;

    _IsTuningSuspend = FALSE;

    _bIsPreProgramDetected = FALSE;
#if (TV_FREQ_SHIFT_CLOCK)
    msAPI_Tuner_Patch_ResetTVShiftClk();
#endif
}

/******************************************************************************/
///- This function will check whether Tuning module is busy or not
/// @return TRUE: tuning module is busy.
/* ****************************************************************************/
BOOLEAN msAPI_Tuner_IsTuningProcessorBusy(void)
{
    if ( _eCurrentTuningState == AFT_IDLE )
    {
        return FALSE;
    }

    return TRUE;
}

/******************************************************************************/
///- This function will check whether one program is detected or not when search.
/// @return TRUE: if one program is detected.
/* ****************************************************************************/
BOOLEAN msAPI_Tuner_IsOneProgramDetected(void)
{
    if ( _bIsOneProgramDetected == TRUE )
    {
        _bIsOneProgramDetected = FALSE;

        return TRUE;
    }

    return FALSE;
}

BOOLEAN msAPI_Tuner_PreProgramDeteted(void)
{
    return (BOOLEAN) _bIsPreProgramDetected ;
}

/******************************************************************************/
///- This API will set tuner PLL of center frequnecy which will be used in realtime AFT.
/// @param wTunerPLL \b IN: Tuner PLL
/******************************************************************************/
void msAPI_Tuner_SetRealtimeAFTBaseTunerPLL(U16 u16TunerPLL)
{
    _u16RealtimeAFTBaseTunerPLL = u16TunerPLL;
    u8ScanAFTCount = 0;
}

/******************************************************************************/
///- This function will check if sync is locked or NOT
/// @return BOOLEAN:
/// - TRUE: Sync is locked
/// - FALSE: Sync is not locked
/******************************************************************************/
BOOLEAN msAPI_Tuner_VD_IsSyncLocked(U8 u8CheckBaseCount, U8 u8PassCount)
{
    U8 bCount,bLockCount;

    if (u8CheckBaseCount<u8PassCount)
        return FALSE;
    if (u8PassCount==0)
        return TRUE;

    bCount=0;
    bLockCount=0;
    do
    {
        if (msAPI_AVD_IsSyncLocked() == TRUE )
            bLockCount++;
        bCount++;
     }while (bCount<u8CheckBaseCount);

    if (bLockCount >= u8PassCount)
        return TRUE;
    else
        return FALSE;
}

/******************************************************************************/
///- This function will check if sync is detected or NOT
/// @return BOOLEAN:
/// - TRUE: Sync is detected
/// - FALSE: Sync is not detected
/******************************************************************************/
BOOLEAN msAPI_Tuner_VD_IsSyncDetected(U8 u8CheckBaseCount, U8 u8PassCount)
{
    U8 bCount,bLockCount;

    if (u8CheckBaseCount<u8PassCount)
        return FALSE;
    if (u8PassCount==0)
        return TRUE;

    bCount=0;
    bLockCount=0;
    do
    {
        if (msAPI_AVD_IsSyncLocked() == TRUE )
            bLockCount++;
        bCount++;
     }while (bCount<u8CheckBaseCount);

    if (bLockCount >= u8PassCount)
        return TRUE;
    else
        return FALSE;
}


/******************************************************************************/
///- This API is called by MApp_ATVProc_Handler to keep tuning work.
/// @param eState \b IN: AFT_EXT_STEP_PERIODIC - This enum is called by ATVProc_Handler(). Don't call any other place except ATVProc_Handler().
///                  IN: AFT_EXT_STEP_SEARCHALL - This enum will start auto-tuning from VHF low to UHF max.
///                  IN: AFT_EXT_STEP_SEARCHONETOUP - This enum will search up for next one available channel.
///                  IN: AFT_EXT_STEP_SEARCHONETODOWN - This enum will search up for next one available channel.
///                  IN: AFT_EXT_STEP_SEARCH_STOP - This enum will stop searching.
/******************************************************************************/

#define VD_CHECK_SYNC_LOCKED            BIT15
#define VD_CHECK_HSYNC_LOCKED           BIT14
#define VD_CHECK_RESET_ON               BIT11
#define VD_CHECK_STATUS_RDY             BIT0
#define TN_READ_LOCK                    BIT0

#define ATVSCAN_VD_CHECKREADY_TIMEOUT   2000  //unit : ms

void msAPI_Tuning_GetStationName(void) //move to tuning.c
{
    if ( _u16UpdateStationNameTimer >= 1 )
    {
        _u16UpdateStationNameTimer--;

        if ( _u16UpdateStationNameTimer == 1 )
        {
        #if ENABLE_TTX
            if ( TRUE != msAPI_TTX_GetStationNameFromTeletext(_sCurrentStationName, MAX_STATION_NAME, NULL) )
        #endif
            {
                msAPI_Tuner_ConvertMediumAndChannelNumberToString(_eMedium, _u8ChannelNumber, _sCurrentStationName);
            }

            _u16UpdateStationNameTimer = 0;
        }
    }
}

BOOLEAN _GetVIFLockStatus(void)
{
    //printf("_GetVIFLockStatus()");
#if(FRONTEND_IF_DEMODE_TYPE == SAMSUNG_SI2176)

    return devTunerGetVIFLockStatus();

#else

    DRV_VIF_Handler(TRUE);  //speed up vif lock

    if (MDrv_VIF_Read_CR_LOCK_STATUS()& TN_READ_LOCK)
        return TRUE;
    else
        return FALSE;
#endif
}

TUNING_STATUS _GetTuningStatus(void)
{
    AFC eFreqDev;

    eFreqDev = MDrv_IFDM_GetFreqDev();
    AUTO_TUNING_PRINT(printf("AFCWIN = 0x%bx \n", eFreqDev));

    if ( eFreqDev == E_AFC_OUT_OF_AFCWIN )
    {
        return E_TUNING_STATUS_OUT_OF_AFCWIN;
    }
    else if ( eFreqDev <= E_AFC_GOOD_MINUS_VALUE || eFreqDev >= E_AFC_GOOD_PLUS_VALUE )
    {
        return E_TUNING_STATUS_GOOD;
    }
    else if ( eFreqDev <= E_AFC_MINUS_112p5KHz)
    {
        return E_TUNING_STATUS_UNDER_LITTLE;
    }
    else if ( eFreqDev >= E_AFC_PLUS_112p5KHz)
    {
        return E_TUNING_STATUS_OVER_LITTLE;
    }
    else if ( eFreqDev <= E_AFC_MINUS_162p5KHz )
    {
        return E_TUNING_STATUS_UNDER;
    }
    else if ( eFreqDev >= E_AFC_PLUS_162p5KHz )
    {
        return E_TUNING_STATUS_OVER;
    }
    else if ( eFreqDev <= E_AFC_BELOW_MINUS_187p5KHz )
    {
        return E_TUNING_STATUS_UNDER_MORE;
    }
  #if 0 // Marked by coverity_0150
    else if ( eFreqDev >= E_AFC_ABOVE_PLUS_187p5KHz )
    {
        return E_TUNING_STATUS_OVER_MORE;
    }

    else
    {
        /* ASSERT */
    }

    return E_TUNING_STATUS_GOOD;
  #else
    else // only 8
    {
        return E_TUNING_STATUS_OVER_MORE;
    }
  #endif
}


#if (ENABLE_SBTVD_SCAN)
    #include "msAPI_Tuning_BRAZIL.c"
#endif

#if (AUTO_TUNING_TYPE_SEL == AUTO_TUNING_ALG_NTSC) //Search NTSC ANT_AIR and ANT_CATV
    #include "msAPI_Tuning_NTSC.c"
#elif (AUTO_TUNING_TYPE_SEL == AUTO_TUNING_ALG_DEFAULT)   //-- AUTO_TUNING_TYPE_SEL --------------------------------------------------------------------------//
    #include "msAPI_Tuning_PAL.c"
#elif (AUTO_TUNING_TYPE_SEL == AUTO_TUNING_ALG_TST)   //-- AUTO_TUNING_TYPE_SEL --------------------------------------------------------------------------//
    #include "msAPI_Tuning_PAL_Tst.c"
#elif(AUTO_TUNING_TYPE_SEL == AUTO_TUNING_ALG_PAL_NEW)
    #include "msAPI_Tuning_PAL_NEW.c"
#else
    #error "No valid AUTO_TUNING_TYPE_SEL!!"
#endif

void msAPI_Tuner_TuningProcessor(eAFTSTEP eState)
{
#if (ENABLE_SBTVD_SCAN)
    if(IS_SBTVD_APP)
    {
        _msAPI_SBTVD_TuningProcessor(eState);
    }
    else
#endif
    {
        _msAPI_Tuner_TuningProcessor(eState);
    }
}

U8 msAPI_Tuner_GetTuningProcessPercent(void)
{
#if (ENABLE_SBTVD_SCAN)
    if(IS_SBTVD_APP)
    {
        return _msAPI_SBTVD_GetTuningProcessPercent();
    }
    else
#endif
    {
        return _msAPI_Tuner_GetTuningProcessPercent();
    }
}

/******************************************************************************/
///- This API is called by change program.
/******************************************************************************/
//extern BOOL g_Debug_Tuner;

#define DEBUG_CHNAGE_PROG(x)    //x
void msAPI_Tuner_SetCurrentAudioStandard(void)
{
    U8 u8CurrentProgramNumber;
    AUDIOSTANDARD_TYPE eAudioStandard;

    u8CurrentProgramNumber = msAPI_ATV_GetCurrentProgramNumber();
    eAudioStandard = msAPI_ATV_GetAudioStandard(u8CurrentProgramNumber);
    DEBUG_CHNAGE_PROG( printf(" eAudioStandard=%u\n", eAudioStandard); );
    msAPI_AUD_SetAudioStandard( eAudioStandard );
}

void msAPI_Tuner_ChangeProgram(void)
{
    //g_Debug_Tuner = 1;
    //g_Debug_u32Time_ChangeChannel = 0;
#if( ENABLE_LOG_CHANGE_CHANNEL&&ENABLE_LOG_FILE_IN_MEM )
    Debug_Log_Reset(0);
#endif

    PRINT_FUNC_START_TIME();
    LOG_CHANGE_CHANNEL_TIME_FUNC_START();

  #if (ENABLE_SWITCH_CHANNEL_TIME)
    #define PT_MApp_TCP_SetBeginTime()      u32TimeBegin = msAPI_Timer_GetTime0()
    #define PT_MApp_TCP_PrintfTime(x)       u32TimeEnd = msAPI_Timer_DiffTimeFromNow(u32TimeBegin);\
                                            if(u32TimeEnd > 1)                                              \
                                            {                                                                \
                                                printf(x, u32TimeEnd);                                       \
                                            }                                                                \
                                            u32TimeBegin = msAPI_Timer_GetTime0()

    U32 u32TimeBegin = 0x00;
    U32 u32TimeEnd   = 0x00;
  #else
    #define PT_MApp_TCP_SetBeginTime()
    #define PT_MApp_TCP_PrintfTime(x)
  #endif

    AUDIOSTANDARD_TYPE eAudioStandard;
    AUDIOMODE_TYPE eSavedAudioMode;
    U8 u8CurrentProgramNumber;
#if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    EN_ATV_SYSTEM_TYPE u8AudioSystem =EN_ATV_SystemType_DK;
#else
    EN_ATV_SYSTEM_TYPE u8AudioSystem =EN_ATV_SystemType_DK;//EN_ATV_SystemType_BG;
#endif

#if ( !ENABLE_ATSC )
    U16 u16TunerPll;
#endif


    PT_MApp_TCP_SetBeginTime();
    u8CurrentProgramNumber = msAPI_ATV_GetCurrentProgramNumber();

    _bIsAFTNeeded = msAPI_ATV_IsAFTNeeded(u8CurrentProgramNumber);
    //PT_MApp_TCP_PrintfTime("[TCP]msAPI_ATV_IsAFTNeeded() -- %ld\n");
    DEBUG_CHNAGE_PROG(printf(" _bIsAFTNeeded=%u\n", _bIsAFTNeeded););

    //DEBUG_CHNAGE_PROG(printf("msAPI_Tuner_ChangeProgram() at %u\n", g_Debug_u32Time_ChangeChannel ););
   // printf("msAPI_Tuner_ChangeProgram() at %u\n", g_Debug_u32Time_ChangeChannel );
    DEBUG_CHNAGE_PROG(printf(" u8CurrentProgramNumber=%u\n", u8CurrentProgramNumber););

#if(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)
    msAPI_Tuner_Clear_IfFreqStatus();
#endif

  #if (TV_FREQ_SHIFT_CLOCK)
    msAPI_Tuner_Patch_ResetTVShiftClk();
  #endif

    eAudioStandard = msAPI_ATV_GetAudioStandard(u8CurrentProgramNumber);
    DEBUG_CHNAGE_PROG( printf(" eAudioStandard=%u\n", eAudioStandard); );


#if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
    if( msAPI_ATV_IsProgrambIsTerrestrial(u8CurrentProgramNumber) == IsDVBCInUse() )
    {
        stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType ^= 1;
        //msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, FALSE);
        msAPI_Tuner_Set_DvbType((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType);
        msAPI_Tuner_SetAntenna(IsDVBCInUse());
    }
#endif

    //SwitchChannelTimePrintf("[SwitchChannelTime][Pre]_SetTunerPLL(); --- %ld\n");

#if 0//(VIF_TUNER_TYPE==1)
    eAudioStandard = msAPI_ATV_GetAudioStandard(u8CurrentProgramNumber);
    msAPI_AUD_ChangeProgSetAudioStandard(eAudioStandard);
  #if (TV_FREQ_SHIFT_CLOCK)
    eProgramVideoStandard=msAPI_ATV_GetVideoStandardOfProgram(u8CurrentProgramNumber);
    if(eProgramVideoStandard<E_VIDEOSTANDARD_NOTSTANDARD)
    {
        MDrv_AVD_SetVideoStandard(eProgramVideoStandard,msAPI_Tuner_IsTuningProcessorBusy());
    }
    msAPI_AVD_RestartCheckVideoStandard();
  #endif
    msAPI_SiTuner_Pre_SetIF((U16)msAPI_ATV_GetProgramPLLData(u8CurrentProgramNumber));
#endif

#if ( !ENABLE_ATSC )
    // Get the tuner freq of this program
    u16TunerPll = msAPI_ATV_GetProgramPLLData(u8CurrentProgramNumber);

    if ( _bIsAFTNeeded == FALSE )
    {
        //_SetTunerPLL( PLLSTEP( msAPI_ATV_GetFineTune(u8CurrentProgramNumber)*FINE_TUNE_STEP ) );
        u16TunerPll += (msAPI_ATV_GetFineTune(u8CurrentProgramNumber)*FINE_TUNE_STEP);
    }


    // Because tuner driver will reference IF type,
    // Must set IF before set tuner freq
    msAPI_Tuner_SetIF_By_Freq_AudioStd( _TunerPllStepToRealFreq(u16TunerPll), eAudioStandard);

    PT_MApp_TCP_SetBeginTime();
    //PT_MApp_TCP_PrintfTime("[TCP]_SetTunerPLL-1() -- %ld\n");
    _SetTunerPLL( u16TunerPll );
    PT_MApp_TCP_PrintfTime("[TCP]_SetTunerPLL-2() -- %ld\n");

    msAPI_Tuner_SetRealtimeAFTBaseTunerPLL(u16TunerPll);
#endif

#if 0// ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)) //must;;AAA
    msAPI_AUD_SetAudioStandard( eAudioStandard );
    PT_MApp_TCP_PrintfTime("[TCP]msAPI_AUD_SetAudioStandard() -- %ld\n");
#endif

    //msAPI_Tuner_SetIF();
    //PT_MApp_TCP_PrintfTime("[TCP]msAPI_Tuner_SetIF() -- %ld\n");

#if ENABLE_TTX
    msAPI_TTX_ResetAcquisition();
#endif


#if ENABLE_CH_FORCEVIDEOSTANDARD
    MApp_ChannelChange_SetupVdForceMode();
#else

    AVD_VideoStandardType eVideoStandard;
    eVideoStandard = msAPI_ATV_GetVideoStandardOfProgram(u8CurrentProgramNumber);
    DEBUG_CHNAGE_PROG( printf(" eVideoStandard=%u\n",eVideoStandard); );

    BOOL bAVDAutoStd = TRUE;

 #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
    bAVDAutoStd = msAPI_ATV_IsProgramAutoColorSystem(u8CurrentProgramNumber);
 #elif(ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    if(eVideoStandard == E_VIDEOSTANDARD_AUTO)
    {
        bAVDAutoStd = TRUE;
    }
    else
    {
        bAVDAutoStd = FALSE;
    }
 #else

    if( (eVideoStandard == E_VIDEOSTANDARD_NTSC_M)
      ||(eVideoStandard == E_VIDEOSTANDARD_PAL_M)
      ||(eVideoStandard == E_VIDEOSTANDARD_PAL_N)
      )
    {
        bAVDAutoStd = FALSE;
    }
    else
    {
        bAVDAutoStd = TRUE;
    }
 #endif

    // Check again
    if( bAVDAutoStd == FALSE ) // Force mode
    {
        if((eVideoStandard==E_VIDEOSTANDARD_AUTO)||(eVideoStandard==E_VIDEOSTANDARD_NOTSTANDARD))
            bAVDAutoStd = TRUE;
    }

    if( bAVDAutoStd )
    {
        DEBUG_CHNAGE_PROG(printf(" VD auto\n"););
        msAPI_AVD_StartAutoStandardDetection();
        //???
        //msAPI_AVD_GetResultOfAutoStandardDetection();
    }
    else
    {
        DEBUG_CHNAGE_PROG(printf(" VD force\n"););
        // todo
        //  msAPI_AVD_ForceVideoStandard(eVideoStandard);
    }

    if( (eVideoStandard != E_VIDEOSTANDARD_AUTO)
      &&(eVideoStandard != E_VIDEOSTANDARD_NOTSTANDARD)
      )
    {
        msAPI_AVD_SetVideoStandard(eVideoStandard);
    }

#endif


    //eAudioStandard = msAPI_ATV_GetAudioStandard(u8CurrentProgramNumber);

#if (ENABLE_AUDIO_SYS_BTSC&&ENABLE_SBTVD_AUDIO)
    if( IS_COUNTRY_USE_SBTVD() )
    {
        bForceCheckAudioMode = TRUE;
    }
#endif

    u8AudioSystem = MApp_ATVProc_GetAudioSystem(eAudioStandard);
    if (u8AudioSystem != stGenSetting.stScanMenuSetting.u8SoundSystem)
    {
        stGenSetting.stScanMenuSetting.u8SoundSystem = u8AudioSystem;
    }
    msAPI_ATV_GetAudioMode(E_AUDIOSOURCE_ATV, &eSavedAudioMode);
    //PT_MApp_TCP_PrintfTime("[TCP]msAPI_ATV_GetAudioMode() -- %ld\n");
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, 1600, E_AUDIOMUTESOURCE_ATV);
    PT_MApp_TCP_PrintfTime("[TCP]msAPI_AUD_AdjustAudioFactor() -- %ld\n");

    //SwitchChannelTimePrintf("[SwitchChannelTime][Pre]msAPI_AUD_SetAudioStandard(); --- %ld\n");
    msAPI_AUD_SetAudioStandard( eAudioStandard );
    //PT_MApp_TCP_PrintfTime("[TCP]msAPI_AUD_SetAudioStandard() -- %ld\n");
//    MDrv_IFDM_Init();
//    msAPI_Tuner_SetIF();

    msAPI_AUD_ForceAudioMode(eSavedAudioMode);
    PT_MApp_TCP_PrintfTime("[TCP]msAPI_AUD_ForceAudioMode() -- %ld\n");

    SwitchChannelTimePrintf("[SwitchChannelTime][VD Start]msAPI_AVD_UpdateAutoAVState(); --- %ld\n");
    msAPI_AVD_UpdateAutoAVState();
    PT_MApp_TCP_PrintfTime("[TCP]msAPI_AVD_UpdateAutoAVState() -- %ld\n");

    if ( _bIsAFTNeeded == TRUE )
    {
        _OneChannelAFT();
        PT_MApp_TCP_PrintfTime("[TCP]_OneChannelAFT() -- %ld\n");
    }

    if ( msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) == TRUE )
    {
        msAPI_AVD_SwitchAutoAV();
        PT_MApp_TCP_PrintfTime("[TCP]msAPI_AVD_SwitchAutoAV() -- %ld\n");

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_BYSYNC_MUTEOFF,E_AUDIOMUTESOURCE_ATV);
        PT_MApp_TCP_PrintfTime("[TCP]msAPI_AUD_AdjustAudioFactor() -- %ld\n");
    }
    else
    {
        if(IsVDHasSignal()==FALSE)
        {
            // msAPI_VD_EnableAutoGainControl(TRUE); // <-<<< USELESS
            msAPI_AVD_SetForcedFreeRun(TRUE);
            PT_MApp_TCP_PrintfTime("[TCP] msAPI_AVD_SetForcedFreeRun() -- %ld\n");
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ATV);
            PT_MApp_TCP_PrintfTime("[TCP] msAPI_AUD_AdjustAudioFactor() -- %ld\n");
        }
        else
        {
            // msAPI_VD_EnableAutoGainControl(FALSE); // <-<<< USELESS
            msAPI_AVD_SetForcedFreeRun(FALSE);
            PT_MApp_TCP_PrintfTime("[TCP] msAPI_AVD_SetForcedFreeRun() -- %ld\n");

            //SwitchChannelTimePrintf("[SwitchChannelTime][Pre]msAPI_AVD_WaitForVideoSyncLock(); --- %ld\n");
            PT_MApp_TCP_SetBeginTime();
            //msAPI_AVD_WaitForVideoSyncLock();
            //PT_MApp_TCP_PrintfTime("[TCP] msAPI_AVD_WaitForVideoSyncLock() -- %ld\n");

            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_BYSYNC_MUTEOFF,E_AUDIOMUTESOURCE_ATV);
            PT_MApp_TCP_PrintfTime("[TCP] msAPI_AUD_AdjustAudioFactor() -- %ld\n");
        }
         #if(MS_BOARD_TYPE_SEL == BD_MSD309PX_HIS)
        // Ensure  audio sync with the video
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ATV);
         #endif
    }

    msAPI_ATV_GetMediumAndChannelNumber(u8CurrentProgramNumber, &_eMedium, &_u8ChannelNumber);
    //PT_MApp_TCP_PrintfTime("[TCP] msAPI_ATV_GetMediumAndChannelNumber() -- %ld\n");

    msAPI_ATV_GetStationName(u8CurrentProgramNumber, _sCurrentStationName);
    //PT_MApp_TCP_PrintfTime("[TCP] msAPI_ATV_GetStationName() -- %ld\n");

#if (1 != ENABLE_SW_CH_FREEZE_SCREEN)
    msAPI_AVD_CheckStdDetStableReset();
#endif

    _u16AFTIdleTimer = 0;    // reset timer, so AFT will be re-active

    //g_Debug_Tuner = 0;

    PRINT_FUNC_END_TIME();
    LOG_CHANGE_CHANNEL_TIME_FUNC_END();
}

/******************************************************************************/
///- This function is called to get current tuning interface.
/// @return MEDIUM: MEDIUM_CABLE or MEDIUM_AIR.
/******************************************************************************/
MEDIUM msAPI_Tuner_GetMedium(void)
{
    return _eMedium;
}

/******************************************************************************/
///- This API is called to set different tuning interface.
/// @param eMedium \b IN: MEDIUM_CABLE - cable.
///                   IN: MEDIUM_AIR - air.
/******************************************************************************/
void msAPI_Tuner_SetMedium(MEDIUM eMedium)
{
    _eMedium = eMedium;

    msAPI_Tuner_SetChannelNumber(_u8ChannelNumber);
}

/******************************************************************************/
///- This function is called to get current channel number.
/// @return U8: channel number.
/* ****************************************************************************/
U8 msAPI_Tuner_GetChannelNumber(void)
{
    return _u8ChannelNumber;
}

/******************************************************************************/
///- This function is called to set current channel number.
/// @param cChannelNumber \b IN: channel number
/******************************************************************************/
void msAPI_Tuner_SetChannelNumber(U8 u8ChannelNumber)
{
    U8 u8MinChannel, u8MaxChannel;

    msAPI_CFT_GetMinMaxChannel( _eMedium, &u8MinChannel, &u8MaxChannel );

    if ( u8ChannelNumber < u8MinChannel )
    {
        _u8ChannelNumber = u8MinChannel;
    }
    else if ( u8MaxChannel < u8ChannelNumber )
    {
        _u8ChannelNumber = u8MaxChannel;
    }
    else
    {
        _u8ChannelNumber = u8ChannelNumber;
    }

    _SetTunerPLL( msAPI_CFT_GetChannelPLLData(_eMedium, _u8ChannelNumber) );

#if ENABLE_TTX
    msAPI_TTX_ResetAcquisition();
#endif
    msAPI_Tuner_SetIF();

    msAPI_AVD_UpdateAutoAVState();

    _OneChannelAFT();

    _bIsAFTNeeded = TRUE;

    msAPI_Tuner_SetRealtimeAFTBaseTunerPLL(_u16TunerPLL);

    if ( msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) == TRUE )
    {
        msAPI_AVD_SwitchAutoAV();

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_BYSYNC_MUTEOFF,E_AUDIOMUTESOURCE_ATV);
    }
    else
    {
        if(IsVDHasSignal()==FALSE)
        {
            // msAPI_VD_EnableAutoGainControl(TRUE); // <-<<< USELESS
            msAPI_AVD_SetForcedFreeRun(TRUE);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ATV);
        }
        else
        {
            // msAPI_VD_EnableAutoGainControl(FALSE); // <-<<< USELESS

            msAPI_AVD_SetForcedFreeRun(FALSE);

            msAPI_AVD_WaitForVideoSyncLock();

            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_BYSYNC_MUTEOFF,E_AUDIOMUTESOURCE_ATV);
        }
    }

    _DetectStationName();

}

/******************************************************************************/
///- This function is called to adjust fine-tune.
/// @param eDirection \b IN: Direction to adjust tuner PLL.
/******************************************************************************/
void msAPI_Tuner_AdjustUnlimitedFineTune(DIRECTION eDirection)
{
  #if ((FIXED_SI2158_FINE_TUNE_GARBAGE)&&(!BLOADER))
    S16 _u16TunerAFC;
  #endif

  #if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)
    U8 u8Ksel = 0;
    MDrv_IFDM_SetParameter(VIF_PARA_GET_K_SEL, &u8Ksel, sizeof(u8Ksel));
  #endif

    _bIsAFTNeeded = FALSE;


#if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)
    {
       if(u8Ksel==1)
       {
           DWORD kSel=0;
           DWORD hwKpKi=0x11;

           MDrv_IFDM_SetParameter(VIF_PARA_K_SEL, &kSel, sizeof(kSel));
           MDrv_IFDM_SetParameter(VIF_PARA_SET_HW_KPKI, &hwKpKi, sizeof(hwKpKi));
       }
     }
#endif

    if ( eDirection == DIRECTION_UP )
    {
        if(msAPI_Tuner_GetCurrentChannelPLL() >= UHF_MAX_PLL)
        {
            _u16TunerPLL = VHF_LOWMIN_PLL;
        }

      #if ((FIXED_SI2158_FINE_TUNE_GARBAGE)&&(!BLOADER))
        g_u16Si2158FineTuneCenterFreq +=100;
        if(g_u16Si2158FineTuneCenterFreq>=2000)
        {
            _SetTunerPLL( PLLSTEP(1));
            if((Si2158_GetATV_AFC_freq() != 0))
            {
                _u16TunerAFC = Si2158_GetATV_AFC_freq();
                _SetTunerPLL( PLLSTEP(_u16TunerAFC) );
            }
        }
        else
        {
            _u16TunerPLL ++;
            MApp_Si2158_FineTune(0,1,g_u16Si2158FineTuneCenterFreq);
        }
      #else
         _SetTunerPLL( PLLSTEP(1));
      #endif
    }
    else
    {
        if(msAPI_Tuner_GetCurrentChannelPLL() <= VHF_LOWMIN_PLL)
        {
            _u16TunerPLL = UHF_MAX_PLL;
        }

      #if ((FIXED_SI2158_FINE_TUNE_GARBAGE)&&(!BLOADER))
        g_u16Si2158FineTuneCenterFreq -=100;
        if(g_u16Si2158FineTuneCenterFreq<=-2000)
        {
            _SetTunerPLL( PLLSTEP(-1));
            if((Si2158_GetATV_AFC_freq() != 0))
            {
                _u16TunerAFC = Si2158_GetATV_AFC_freq();
                _SetTunerPLL( PLLSTEP(_u16TunerAFC) );
            }
        }
        else
        {
            _u16TunerPLL --;
            MApp_Si2158_FineTune(0,1,g_u16Si2158FineTuneCenterFreq);
        }
      #else
        _SetTunerPLL( PLLSTEP(-1));
      #endif
    }

#if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)
    {
       if(u8Ksel==1)
       {
           DWORD kSel=1;
           DWORD hwKpKi=(VIF_CR_KI1<<4)|VIF_CR_KP1;
           MDrv_IFDM_SetParameter(VIF_PARA_K_SEL, &kSel, sizeof(kSel));
           MDrv_IFDM_SetParameter(VIF_PARA_SET_HW_KPKI, &hwKpKi, sizeof(hwKpKi));
       }
    }
#endif

    _DetectStationName();
}
/******************************************************************************/
///- This function is called to set search manual-tune.
/// @param wTunerPLL \b IN: Tuner PLL
/// @return U16: The u16InterFreq nearest PLL of frequency table
/******************************************************************************/
U16 msAPI_Tuner_SetSearchManualTune(U16 u16InterFreq)
{
    U16 i,InterPLL,MinDiffPLL,OutputPLL;

    InterPLL = msAPI_CFT_ConvertFrequncyToPLL(u16InterFreq,0);

    OutputPLL = InterPLL;
    MinDiffPLL = 0xFFFF;

    for (i=msAPI_ATV_GetChannelMin(); i<msAPI_ATV_GetChannelMax(); i++)
    {
        if( msAPI_ATV_GetProgramPLLData(i) != DEFAULT_PLL)
        {
            if((msAPI_ATV_GetProgramPLLData(i) >= InterPLL) &&
                ((msAPI_ATV_GetProgramPLLData(i) - InterPLL) < MinDiffPLL))
            {
                MinDiffPLL = msAPI_ATV_GetProgramPLLData(i) - InterPLL;
                OutputPLL = msAPI_ATV_GetProgramPLLData(i);
            }
            else if((msAPI_ATV_GetProgramPLLData(i) < InterPLL) &&
                     ((InterPLL - msAPI_ATV_GetProgramPLLData(i)) < MinDiffPLL))
            {
                MinDiffPLL = InterPLL - msAPI_ATV_GetProgramPLLData(i);
                OutputPLL = msAPI_ATV_GetProgramPLLData(i);
            }
        }
    }

    _SetTunerPLL(OutputPLL);

    return     msAPI_CFT_ConvertPLLtoIntegerOfFrequency(OutputPLL);
}

/******************************************************************************/
///- This function is called to check demodulator's setting. It depends on audio standard.
/******************************************************************************/

void msAPI_Tuner_SetIF_By_Freq_AudioStd(U32 u32TunerFreg, AUDIOSTANDARD_TYPE eAudioStd)
{
    DEBUG_TUNING( printf("msAPI_Tuner_SetIF_By_Freq_AudioStd(u32TunerFreg=%uK, eAudioStd=0x%X)\n", u32TunerFreg/1000, eAudioStd); );

#if (ENABLE_ATSC)
    u32TunerFreg = u32TunerFreg;
    eAudioStd = eAudioStd;
    MDrv_IFDM_SetIF(IF_FREQ_MN);

#else

    AUDIOSTANDARD_TYPE eBasicAudioStd = E_AUDIOSTANDARD_DK;
    IF_FREQ eIF_Freq = IF_FREQ_DK;


    if( eAudioStd == E_AUDIOSTANDARD_NOTSTANDARD )
    {
        printf("\nError: AudioStd= E_AUDIOSTANDARD_NOTSTANDARD\n" );
    }
    else
    {
        eBasicAudioStd = MApi_AUDIO_SIF_ConvertToBasicAudioStandard(eAudioStd);
    }

    switch( eBasicAudioStd )
    {
        case E_AUDIOSTANDARD_BG:
            {
                if(u32TunerFreg < UHF_MIN_FREQ_HZ) // VHF
                {
                #if(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER || FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)//modified by Weng 2015.08.26
                eIF_Freq = IF_FREQ_G;
                #else
                eIF_Freq = IF_FREQ_B;
                #endif
                }
                else // UHF
                {
                    eIF_Freq = IF_FREQ_G;
                }
            }
            break;
        case E_AUDIOSTANDARD_I:
            {
                eIF_Freq = IF_FREQ_I;
            }
            break;
        case E_AUDIOSTANDARD_DK:
            {
                eIF_Freq = IF_FREQ_DK;
            }
            break;
        case E_AUDIOSTANDARD_L:
            {
                // Check boundary
                if( _CheckLPrimeBoundary_ByFreq(u32TunerFreg) )
                {
                    eIF_Freq = IF_FREQ_L_PRIME;
                }
                else
                {
                    eIF_Freq = IF_FREQ_L;
                }
            }
            break;
        case E_AUDIOSTANDARD_M:
            {
                eIF_Freq = IF_FREQ_MN;
            }
            break;
        default:
            {
                printf("\nError: Unknown eBasicAudioStd=%u\n", eBasicAudioStd);
            }
            break;
    }

#if (ENABLE_SBTVD_SCAN == 1)
    if(IS_SBTVD_APP)
    {
        eIF_Freq = IF_FREQ_MN;
    }
#endif

#if ( (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)  \
    ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)          \
    ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)   )

    if( eIF_Freq == IF_FREQ_L_PRIME )
    {
        SECAM_L_PRIME_ON();
    }
    else
    {
        SECAM_L_PRIME_OFF();
    }
#endif

    MDrv_IFDM_SetIF(eIF_Freq);
#endif
}

void msAPI_Tuner_SetIF(void)
{
#if( ENABLE_DEBUG_TUNING_TIME )
    U32 u32Time1 = MsOS_GetSystemTime();
    U32 u32Time2;
#endif

    DEBUG_TUNING( printf("msAPI_Tuner_SetIF()\n") );

#if 1

  #if (ENABLE_ATSC)
    MDrv_IFDM_SetIF(IF_FREQ_MN);
    MDrv_IFDM_SetVifIfFreq(TUNER_IF_FREQ_KHz);
  #else
    msAPI_Tuner_SetIF_By_Freq_AudioStd(_TunerPllStepToRealFreq(_u16TunerPLL), msAPI_AUD_GetAudioStandard());
  #endif

  #if( ENABLE_DEBUG_TUNING_TIME )
    u32Time2 = msAPI_Timer_DiffTime_2(u32Time1, MsOS_GetSystemTime());
    if( u32Time2 >= 2 )
    {
        printf("msAPI_Tuner_SetIF use %u\n", u32Time2);
    }
  #endif

#else
    if ( _IsLPrime() == TRUE )
    {
      #if ( (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)  \
          ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)          \
          ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)   )
        SECAM_L_PRIME_ON();
      #endif

        MDrv_IFDM_SetIF(IF_FREQ_L_PRIME);
    }
    else
    {
      #if( (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)   \
         ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)           \
         ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF) )
         SECAM_L_PRIME_OFF();
      #endif

        #if (ENABLE_SBTVD_SCAN == 1)
            MDrv_IFDM_SetIF(IF_FREQ_MN);
        #else
            switch ( MApi_AUDIO_SIF_ConvertToBasicAudioStandard(msAPI_AUD_GetAudioStandard()) )
            {
            case E_AUDIOSTANDARD_BG:
                MDrv_IFDM_SetIF(IF_FREQ_B);
                break;

            case E_AUDIOSTANDARD_I:
                MDrv_IFDM_SetIF(IF_FREQ_I);
                break;

            case E_AUDIOSTANDARD_DK:
                MDrv_IFDM_SetIF(IF_FREQ_DK);
                break;

            case E_AUDIOSTANDARD_L:
                MDrv_IFDM_SetIF(IF_FREQ_L);
                break;

            case E_AUDIOSTANDARD_M:
                MDrv_IFDM_SetIF(IF_FREQ_MN);
                break;

            default:
                return;
            }
        #endif
    }
#endif
}

#if 0//(VIF_TUNER_TYPE==1)
/******************************************************************************/
///- This function is called to pre set audio standard variable in order to for set tuner .
/******************************************************************************/
void msAPI_SiTuner_Pre_SetIF(U16 u16PLL)
{
    U16 temp_u16PLL;
    temp_u16PLL = _u16TunerPLL;
    _u16TunerPLL = u16PLL;
    if ( _IsLPrime() == TRUE )
    {
      #if ( (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)  \
          ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)          \
          ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)   )
        SECAM_L_PRIME_ON();
      #endif

        MDrv_IFDM_Pre_SetIF(IF_FREQ_L_PRIME);
    }
    else
    {
      #if( (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)   \
         ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)           \
         ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF) )
         SECAM_L_PRIME_OFF();
      #endif

        #if (ENABLE_SBTVD_SCAN == 1)
            MDrv_IFDM_Pre_SetIF(IF_FREQ_MN);
        #else
            switch ( MApi_AUDIO_SIF_ConvertToBasicAudioStandard(msAPI_AUD_GetAudioStandard()) )
            {
            case E_AUDIOSTANDARD_BG:
                MDrv_IFDM_Pre_SetIF(IF_FREQ_B);
                break;

            case E_AUDIOSTANDARD_I:
                MDrv_IFDM_Pre_SetIF(IF_FREQ_I);
                break;

            case E_AUDIOSTANDARD_DK:
                MDrv_IFDM_Pre_SetIF(IF_FREQ_DK);
                break;

            case E_AUDIOSTANDARD_L:
                MDrv_IFDM_Pre_SetIF(IF_FREQ_L);
                break;

            case E_AUDIOSTANDARD_M:
                MDrv_IFDM_Pre_SetIF(IF_FREQ_MN);
                break;

            default:
                return;
            }
        #endif
    }
    _u16TunerPLL = temp_u16PLL;

}
#endif
/******************************************************************************/
///- This function is called to get current channel PLL.
/// @return U16: current PLL value of tuner.
/******************************************************************************/
U16 msAPI_Tuner_GetCurrentChannelPLL(void)
{
    return _u16TunerPLL;
}

void msAPI_Tuner_SetCurrentChannelPLL(U16 u16TunerPLL)
{
    _u16TunerPLL = u16TunerPLL;
}

U16 msAPI_Tuner_GetCurrentChannelPLL2UiStr(void)
{
#if((AUTO_TUNING_TYPE_SEL==AUTO_TUNING_ALG_TST)&&(TV_SCAN_PAL_SECAM_ONCE==1))
    return _MenualScanPLL();
#else
    return _u16TunerPLL;
#endif
}

BOOLEAN msAPI_Tuner_IsCurrentChannelAndSavedChannelSame(void)
{
    U16 u16SavedTunerPLL;

    u16SavedTunerPLL = msAPI_ATV_GetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber());

    if ( (msAPI_CFT_GetMedium(u16SavedTunerPLL) == msAPI_CFT_GetMedium(_u16TunerPLL)) &&
         (msAPI_CFT_GetChannelNumber(u16SavedTunerPLL) == msAPI_CFT_GetChannelNumber(_u16TunerPLL)) )
    {
        return TRUE;
    }

    return FALSE;
}

void msAPI_Tuner_ConvertMediumAndChannelNumberToString(MEDIUM eMedium, U8 u8ChannelNumber, BYTE * sStationName)
{
    if ( eMedium == MEDIUM_AIR )
    {
        sStationName[0] = 'C';    // Air
    }
    else
    {
        sStationName[0] = 'S';    // Cable
    }

    sStationName[1] = '-';
    sStationName[2] = (u8ChannelNumber / 10) + '0';
    sStationName[3] = (u8ChannelNumber % 10) + '0';
    sStationName[4] = ' ';
    sStationName[5] = '\0';
}


void msAPI_Tuner_GetCurrentStationName(BYTE *sName)
{
    U8 i;

    for ( i = 0; i < MAX_STATION_NAME; i++ )
    {
        sName[i] = _sCurrentStationName[i];
    }
}

void msAPI_Tuner_ChangeCurrentStationName(BYTE cStationNameChar, U8 u8Position)
{
    if ( u8Position >= strlen((char*)_sCurrentStationName))
    {
        return;
    }

    _sCurrentStationName[u8Position] = cStationNameChar;
}

BOOLEAN msAPI_Tuner_IsAFTNeeded(void)
{
    return _bIsAFTNeeded;
}

void msAPI_Tuner_UpdateMediumAndChannelNumber(void)
{
    _eMedium = msAPI_CFT_GetMedium(_u16TunerPLL);

    _u8ChannelNumber = msAPI_CFT_GetChannelNumber(_u16TunerPLL);
}

//------------------------------------------------------------------------------
// Start of test function. Use the following functions to test.
// If you do not need the following functions, remove it.
//------------------------------------------------------------------------------
#if 1 //


#define MAX_VIDEOSTANDARDSTRING         8

typedef struct
{
    AVD_VideoStandardType eVideoStandard;
    BYTE sStandardSting[MAX_VIDEOSTANDARDSTRING];
} VIDEOSTANDARDINFO;

#define MAX_VIDEOSTANDARDINFO           7

static ROM VIDEOSTANDARDINFO m_VideoStandardInfo[MAX_VIDEOSTANDARDINFO] =
{
    {E_VIDEOSTANDARD_PAL_BGHI,          "PAL    "},
    {E_VIDEOSTANDARD_SECAM,             "SECAM  "},
    {E_VIDEOSTANDARD_PAL_N,             "PAL N  "},
    {E_VIDEOSTANDARD_PAL_M,             "PAL M  "},
    {E_VIDEOSTANDARD_PAL_60,            "PAL 60 "},
    {E_VIDEOSTANDARD_NTSC_M,            "NTSC M "},
    {E_VIDEOSTANDARD_NTSC_44,           "NTSC 44"}
};

static void msAPI_ConvertVideoStandardToString(AVD_VideoStandardType eVideoStandard, char *pcBuffer)
{
    BYTE i;

    //printf("msAPI_ConvertVideoStandardToString(eVideoStandard=%u) pcBuffer=[%s]\n", eVideoStandard, pcBuffer);

    for ( i = 0; i < MAX_VIDEOSTANDARDINFO; i++ )
    {
        if ( eVideoStandard == m_VideoStandardInfo[i].eVideoStandard )
        {
            _RomStringCopy(pcBuffer, (char ROM *)m_VideoStandardInfo[i].sStandardSting, MAX_VIDEOSTANDARDSTRING-1);
            return;
        }
    }

    if ( i == MAX_VIDEOSTANDARDINFO )
    {
        _RomStringCopy(pcBuffer, "ALLOM  ", MAX_VIDEOSTANDARDSTRING-1);
    }
}

#define MAX_AUDIOSTANDARDSTRING         9

typedef struct
{
    AUDIOSTANDARD_TYPE eAudioStandard;
    BYTE sStandardSting[MAX_AUDIOSTANDARDSTRING];
} AUDIOSTANDARDINFO;

#define MAX_AUDIOSTANDARDINFO           14

static ROM AUDIOSTANDARDINFO m_AudioStandardInfo[MAX_AUDIOSTANDARDINFO] =
{
    {E_AUDIOSTANDARD_BG,            "BG MONO "},
    {E_AUDIOSTANDARD_BG_A2,         "BG A2   "},
    {E_AUDIOSTANDARD_BG_NICAM,      "BG NICAM"},
    {E_AUDIOSTANDARD_I,             "I       "},
    {E_AUDIOSTANDARD_DK,            "DK MONO "},
    {E_AUDIOSTANDARD_DK1_A2,        "DK1 A2  "},
    {E_AUDIOSTANDARD_DK2_A2,        "DK2 A2  "},
    {E_AUDIOSTANDARD_DK3_A2,        "DK3 A2  "},
    {E_AUDIOSTANDARD_DK_NICAM,      "DK NICAM"},
    {E_AUDIOSTANDARD_L,             "L       "},
    {E_AUDIOSTANDARD_M,             "M MONO  "},
    {E_AUDIOSTANDARD_M_BTSC,        "M BTSC  "},
    {E_AUDIOSTANDARD_M_A2,          "M A2    "},
    {E_AUDIOSTANDARD_M_EIA_J,       "M EIA-J "}
};

static void msAPI_ConvertAudioStandardToString(AUDIOSTANDARD_TYPE eAudioStandard, char *pcBuffer)
{
    U8 i;

    for ( i = 0; i < MAX_AUDIOSTANDARDINFO; i++ )
    {
        if ( eAudioStandard == m_AudioStandardInfo[i].eAudioStandard )
        {
            _RomStringCopy(pcBuffer, ( char ROM *)m_AudioStandardInfo[i].sStandardSting, MAX_AUDIOSTANDARDSTRING-1);
            return;
        }
    }

    if ( i == MAX_AUDIOSTANDARDINFO )
    {
        _RomStringCopy(pcBuffer, "ALLOM   ", MAX_AUDIOSTANDARDSTRING-1);
    }
}

void msAPI_Tuner_PrintTVAVSourceInformation(void)
{
    char sChannelInfo[40] = "ABCDE:000.00MHz NTSC 44  BG NICAM";
    char acChannelInfo2[41];
    WORD wIntegerOfFreq, wFractionOfFreq;
    U8 i;
    U8 u8BufLen = strlen(sChannelInfo);

    msDebug_ANSI_SetColorText(E_FONT_COLOR_RED);
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW);

    //printf(" msAPI_Tuner_PrintTVAVSourceInformation()\n");

#define STATION_NAME_INFO_START_INDEX   0
#define STATION_NAME_INFO_LEN           5
#if ENABLE_TTX
    if ( TRUE != msAPI_TTX_GetStationNameFromTeletext((U8*)&sChannelInfo[STATION_NAME_INFO_START_INDEX], STATION_NAME_INFO_LEN, NULL) )
#endif
    {
        msAPI_Tuner_ConvertMediumAndChannelNumberToString(_eMedium, _u8ChannelNumber, (U8*)&sChannelInfo[STATION_NAME_INFO_START_INDEX]);
    }
    sChannelInfo[5]=' ';// can not print other message using msTV_tools


#define FREQUENCY_INFO_START_INDEX    6
    wIntegerOfFreq = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL);
    wFractionOfFreq = msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL);
    msAPI_ConvertFrequencyToString(wIntegerOfFreq, wFractionOfFreq, &sChannelInfo[FREQUENCY_INFO_START_INDEX]);


#define VIDEO_STANDARD_INFO_START_INDEX    16
    msAPI_ConvertVideoStandardToString(msAPI_AVD_GetVideoStandard(), &sChannelInfo[VIDEO_STANDARD_INFO_START_INDEX]);


#define AUDIO_STANDARD_INFO_START_INDEX    25
    //msAPI_ConvertAudioStandardToString(msAPI_AUD_GetAudioStandard(), &sChannelInfo[AUDIO_STANDARD_INFO_START_INDEX]);
    msAPI_ConvertAudioStandardToString(msAPI_ATV_GetAudioStandard(msAPI_ATV_GetCurrentProgramNumber()),
                                &sChannelInfo[AUDIO_STANDARD_INFO_START_INDEX]);

    for( i = 0; (i < u8BufLen)&&(i<40); i++ )
    {
        char ch = sChannelInfo[i];
        if( (ch>= 20)&&(ch < 0x7F) )
            acChannelInfo2[i] = ch;
        else
            acChannelInfo2[i] = ' ';
    }
    acChannelInfo2[i] = 0;

    printf(" (%u) %s\r\n", msAPI_ATV_GetCurrentProgramNumber(), acChannelInfo2 );

    msDebug_ANSI_AllAttrOffText();
}
#endif

void msAPI_Tuning_IsScanL(BOOLEAN bEnable)
{
    _bIsLSearch = bEnable;
}
//------------------------------------------------------------------------------
// Local Functions.
//------------------------------------------------------------------------------

U16 msAPI_Tuner_GetIF(void)
{
    if ( FALSE == _IsLPrime() )
    {
    #if TN_FREQ_STEP == FREQ_STEP_62_5KHz
        return (WORD)((TUNER_IF_FREQ_KHz * 10) / 625);
    #elif TN_FREQ_STEP == FREQ_STEP_50KHz
        return (WORD)(TUNER_IF_FREQ_KHz / 50);
    #else
        return (WORD)((TUNER_IF_FREQ_KHz * 100) / 3125);
    #endif // TN_FREQ_STEP
    }
    else
    {
    #if TN_FREQ_STEP == FREQ_STEP_62_5KHz
        return (WORD)((TUNER_L_PRIME_IF_FREQ_KHz * 10) / 625);
    #elif TN_FREQ_STEP == FREQ_STEP_50KHz
        return (WORD)(TUNER_L_PRIME_IF_FREQ_KHz / 50);
    #else
        return (WORD)((TUNER_L_PRIME_IF_FREQ_KHz * 100) / 3125);
    #endif // TN_FREQ_STEP
    }
}

BOOLEAN msAPI_Tuner_IsCurrentAudioLPrime(void)
{
    WORD wTunerPLL;
    U32 u32TunerPLLI, u32TunerPLLF, u32LPrimeFreq;
    AUDIOSTANDARD_TYPE eAudioStandard;

    eAudioStandard = msAPI_AUD_GetAudioStandard();
    if (eAudioStandard != E_AUDIOSTANDARD_L)
        return FALSE;

    wTunerPLL = msAPI_Tuner_GetCurrentChannelPLL();
    u32TunerPLLI = (U32)msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wTunerPLL);
    u32TunerPLLF = (U32)msAPI_CFT_ConvertPLLtoFractionOfFrequency(wTunerPLL);
    u32LPrimeFreq = (u32TunerPLLI*1000) + u32TunerPLLF;
    if (u32LPrimeFreq < (U32)L_PRIME_BOUNDARY_FREQ)
       return TRUE;

    return FALSE;
}

BOOL msAPI_Tunning_Is_CurrentTuningState_Idle(void) //ryan add
{
     if (_eCurrentTuningState == AFT_IDLE)
         return TRUE;
     else
         return FALSE;
}

//
//******************************************************************************
//

#undef MSAPI_TUNING_C

