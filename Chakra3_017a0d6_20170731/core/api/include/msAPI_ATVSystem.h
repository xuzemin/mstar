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

#ifndef __API_ATVSYSTEM_H__
#define __API_ATVSYSTEM_H__

#include "Board.h"
#include "drvAVD.h"
#include "msAPI_FreqTableCommon.h"
#include "msAPI_audio.h"
#include "apiAUDIO.h"
#include "msAPI_Global.h"

#include "MApp_GlobalSettingSt_Common.h"


#define ENABLE_ATV_SYS_PICTURE_SETTING   0


// ATV PROGRAM DATA STRUCTURE
#define MAX_LISTPAGE                4
#define MAX_LISTPAGE_SIZE           ((MAX_LISTPAGE*10)/8)
#define MAX_PRTABLEMAP              ((MAX_ATVPROGRAM+7)/8)
#if 0
#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
#define MAX_CATV_PRTABLEMAP         ((MAX_CATVPROGRAM+7)/8)
#endif
#endif
#define MAX_STATION_NAME            8

#if 0
#if( DTV_SYSTEM_SEL == DTV_SYSTEM_ATSC )
    #define ATV_CHAN_AIR_MIN        2
    #define ATV_CHAN_AIR_MAX        10
    #define ATV_CHAN_CATV_MIN       1
    #define ATV_CHAN_CATV_MAX       10


#elif (ENABLE_SBTVD_ATV_SYSTEM)
    #define ATV_CHAN_AIR_MIN        2
    #define ATV_CHAN_AIR_MAX        69
    #define ATV_CHAN_CATV_MIN       1
    #define ATV_CHAN_CATV_MAX       125

#elif ( ENABLE_DVB_TAIWAN_APP )
    #define ATV_CHAN_AIR_MIN        2
    #define ATV_CHAN_AIR_MAX        69
    #define ATV_CHAN_CATV_MIN       1
    #define ATV_CHAN_CATV_MAX       135

#elif ( TV_SYSTEM == TV_NTSC )
    #define ATV_CHAN_AIR_MIN        1
    #define ATV_CHAN_AIR_MAX        99
    #define ATV_CHAN_CATV_MIN       1
    #define ATV_CHAN_CATV_MAX       135

#endif

#elif (ENABLE_SBTVD_ATV_SYSTEM)
    #define ATV_CHAN_AIR_MIN        2
    #define ATV_CHAN_AIR_MAX        69
    #define ATV_CHAN_CATV_MIN       1
    #define ATV_CHAN_CATV_MAX       125

#elif(ENABLE_ATSC) // No need save ATV
    #define ATV_CHAN_AIR_MIN        1
    #define ATV_CHAN_AIR_MAX        2
    #define ATV_CHAN_CATV_MIN       1
    #define ATV_CHAN_CATV_MAX       2

#else

    #define ATV_CHAN_AIR_MIN        1
    #define ATV_CHAN_AIR_MAX        99
    #define ATV_CHAN_CATV_MIN       1
    #define ATV_CHAN_CATV_MAX       135

#endif

#define MIN_ATVPROGRAM          ATV_CHAN_AIR_MIN
#define MAX_ATVPROGRAM          ATV_CHAN_AIR_MAX

#define MIN_CATVPROGRAM         ATV_CHAN_CATV_MIN
#define MAX_CATVPROGRAM         ATV_CHAN_CATV_MAX

#define MAX_CATV_PRTABLEMAP     ((MAX_CATVPROGRAM+7)/8)

//==================================================================

// Operation method
/*typedef enum
{
    OPERATIONMETHOD_MANUALLY,        ///< Operation method manually
    OPERATIONMETHOD_AUTOMATICALLY   ///< Operation method automatically
} OPERATIONMETHOD; */

typedef enum
{
    E_DUAL_MONO         = 0x00,
    E_DUAL_AUDIO_A      = 0x01,
    E_DUAL_AUDIO_B      = 0x02,
    E_DUAL_AUDIO_AB     = 0x03,
} EN_DUAL_AUDIO_SELECTION;

// Medium type
typedef enum
{
    MEDIUM_CABLE,   ///< Medium type Cable
    MEDIUM_AIR      ///< Medium type Air
} MEDIUM;

#if 0
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP )
#define DEFAULT_AUDIOSTANDARD                       E_AUDIOSTANDARD_DK

#elif (ENABLE_SBTVD_ATV_SYSTEM||ENABLE_DVB_TAIWAN_APP)
#define DEFAULT_AUDIOSTANDARD                       E_AUDIOSTANDARD_M_BTSC
#define DEFAULT_IS_AUTO_COLOR_SYSTEM            TRUE

#else
    #if (TV_SYSTEM == TV_NTSC)
        #if (AUDIO_SYSTEM_SEL == AUDIO_SYSTEM_BTSC)
        #define DEFAULT_AUDIOSTANDARD                       E_AUDIOSTANDARD_M_BTSC
        #elif (AUDIO_SYSTEM_SEL == AUDIO_SYSTEM_A2)
        #define DEFAULT_AUDIOSTANDARD                       E_AUDIOSTANDARD_M_A2;
        #endif
    #define DEFAULT_IS_AUTO_COLOR_SYSTEM            TRUE
    #else
        #define DEFAULT_AUDIOSTANDARD                       E_AUDIOSTANDARD_DK//E_AUDIOSTANDARD_BG
    #endif
#endif
#else
    #define DEFAULT_AUDIOSTANDARD                   E_AUDIOSTANDARD_DK
    #define DEFAULT_IS_AUTO_COLOR_SYSTEM            TRUE
#endif

#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
typedef enum
{
    E_VIDEOSTANDARD_BRAZIL_NTSC_M          = 0x01,        ///< Video standard NTSC M
    E_VIDEOSTANDARD_BRAZIL_PAL_M           = 0x02,        ///< Video standard  PAL M
    E_VIDEOSTANDARD_BRAZIL_PAL_N           = 0x03,        ///< Video standard  PAL N
    E_VIDEOSTANDARD_BRAZIL_AUTO            = 0x04,         ///< Video standard AUTO
    E_VIDEOSTANDARD_BRAZIL_MAX                           =0x05,     ///Max Number
} VIDEOSTANDARD_BRAZIL_TYPE;
#endif

typedef enum
{
    E_FORCE_VD_MODE_OFF                 = 0x00,
    E_FORCE_VD_MODE_ON_FOREVER          = 0x01,
    E_FORCE_VD_MODE_ON_FOR_A_WHILE      = 0x02,
} FORCE_VD_STD_MODE_TYPE;


typedef struct
{
    U8 u8ChannelNumber;

    WORD eVideoStandard                         : 4; // This allocation is very dangerous and not good. But I should use this method in order to reduce the size of NVRAM. I'm so sorry.
    WORD eVideoStandard_User					: 4;
    WORD eAudioMode                             : 4; // This allocation is very dangerous and not good. But I should use this method in order to reduce the size of NVRAM. I'm so sorry.
    WORD eAudioStandard                         : 4; // This allocation is very dangerous and not good. But I should use this method in order to reduce the size of NVRAM. I'm so sorry.

    WORD bWasDualAudioSelected                  : 2;
#if 0
#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
    WORD bIsSearched                            : 1; // In NTSC system, the number of the channels is determined whether. Use this bit to check whether a channel is real or not. Rock
    WORD bIsAutoColorSystem                     : 3;
#elif (ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    WORD bIsTerrestrial                         : 1; // In NTSC system, the number of the channels is determined whether. Use this bit to check whether a channel is real or not. Rock
    WORD Unused                                 : 3;
#else
    #if (ENABLE_CH_VOLUME_COMP)
    WORD eVolumeComp                            : 4; // Volume compensation for every channel.
    #else
    WORD Unused                                 : 4;
    #endif
#endif
#else
    WORD bIsSearched                            : 1; // In NTSC system, the number of the channels is determined whether. Use this bit to check whether a channel is real or not. Rock
    WORD bIsAutoColorSystem                     : 3;
    WORD bIsTerrestrial                         : 1; // In NTSC system, the number of the channels is determined whether. Use this bit to check whether a channel is real or not. Rock
    #if (ENABLE_CH_VOLUME_COMP)
    WORD eVolumeComp                            : 4; // Volume compensation for every channel.
    #else
    WORD Unused                                 : 4;
    #endif

#endif
    WORD bSkip                                  : 1;
    WORD bAFT                                   : 1;
    WORD bIsFavorite                            : 1;
    WORD eMedium                                : 1;
    WORD bIsLock                                : 1;

} __attribute__ ((packed)) ATV_MISC;

typedef struct
{
    WORD wPLL;
    ATV_MISC Misc;
    BYTE u8Sort;
    S8 s8FineTune;
    BYTE sName[MAX_STATION_NAME];
  #if (ENABLE_TTX || BLOADER)
    BYTE u8ListPage[MAX_LISTPAGE_SIZE];
    #endif
} ATVPROGRAMDATA;

typedef struct
{
    //BYTE            u8LastPRNumber;   // Move to EEPROM for save Flash life
    BYTE            u8ATVPRIndexTable[MAX_ATVPROGRAM];
    BYTE            u8ATVPRTableMap[MAX_PRTABLEMAP];
    ATVPROGRAMDATA  ATVProgramData[MAX_ATVPROGRAM];
} ATV_PROGRAM_DATA_STRUCTURE;

//---CATV PROGRAM DATA STRUCTURE---
#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
typedef struct
{
    //BYTE            u8CATVLastPRNumber;  // Move to EEprom for save Flash life
    BYTE            u8CATVPRIndexTable[MAX_CATVPROGRAM];
    BYTE            u8CATVPRTableMap[MAX_CATV_PRTABLEMAP];
    ATVPROGRAMDATA  CATVProgramData[MAX_CATVPROGRAM];
} CATV_PROGRAM_DATA_STRUCTURE;
#endif

//---COMMON DATA STRUCTURE---
typedef struct
{
    AUDIOMODE_TYPE      eCVBS1AudioMode;
    AUDIOMODE_TYPE      eCVBS2AudioMode;
    AUDIOMODE_TYPE      eSVIDEO1AudioMode;
    AUDIOMODE_TYPE      eSVIDEO2AudioMode;
    AUDIOMODE_TYPE      eSCART1AudioMode;
    AUDIOMODE_TYPE      eSCART2AudioMode;
    AUDIOMODE_TYPE      ePCAudioMode;
    AUDIOMODE_TYPE      eYPbPrAudioMode;
    AUDIOMODE_TYPE      eHDMIAudioMode;
} AUDIOMODE;

typedef struct
{
    AVD_VideoStandardType  eATVStandard;
    AVD_VideoStandardType  eCVBS1Standard;
    AVD_VideoStandardType  eCVBS2Standard;
    AVD_VideoStandardType  eSVIDEO1Standard;
    AVD_VideoStandardType  eSVIDEO2Standard;
    AVD_VideoStandardType  eSCART1Standard;
    AVD_VideoStandardType  eSCART2Standard;
} LASTVIDEOSTANDARD;

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
typedef struct
{
    BYTE u8Brightness;
    BYTE u8Contrast;
    BYTE u8Color;
    BYTE u8Hue;
    BYTE u8Sharpness;
} PICTURE_QUALITY_ITEMS;
#endif

typedef struct
{
    WORD                    wID;

    //MEMBER_COUNTRY          eCountry;

    AUDIOMODE               AudioMode;

    LASTVIDEOSTANDARD       LastVideoStandard;

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
    PICTURE_QUALITY_ITEMS   PictureQualityOfATV;
    PICTURE_QUALITY_ITEMS   PictureQualityOfCVBS1;
    PICTURE_QUALITY_ITEMS   PictureQualityOfCVBS2;
    PICTURE_QUALITY_ITEMS   PictureQualityOfSVIDEO1;
    PICTURE_QUALITY_ITEMS   PictureQualityOfSVIDEO2;
    PICTURE_QUALITY_ITEMS   PictureQualityOfSCART1;
    PICTURE_QUALITY_ITEMS   PictureQualityOfSCART2;
#endif
} COMMON_DATA_STRUCTURE;

//------------------------------------------------------------------------------
// Public attributes.
//------------------------------------------------------------------------------
typedef enum
{
    E_ENABLE_SYSTEM_L,
    E_ENABLE_RF_TABLE,
    E_ENABLE_RT_AFT,
    E_ENABLE_CH_NAME,
    E_ENABLE_TTX,
    E_ENABLE_CARRIER_MUTE,
    E_ENABLE_SAVING_DUAL,
    E_ENABLE_HI_DEVIATION,
    E_ENABLE_VOLUME_CURVE_SEL,
    E_ENABLE_MONO_ONLY,
    E_ENABLE_SCART,
    E_ENABLE_WSS,
    E_MAX_THISATV_OPTION
} THISATV_OPTION;


#define IS_SYSTEM_L_ENABLED             MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_SYSTEM_L)
#define IS_RF_TABLE_ENABLED             MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_RF_TABLE)
#define IS_RT_AFT_ENABLED               MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_RT_AFT)
#define IS_CH_NAME_ENABLED              MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_CH_NAME)
#define IS_CARRIER_MUTE_ENABLED         MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_CARRIER_MUTE)
#define IS_SAVING_DUAL_ENABLED          MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_SAVING_DUAL)
#define IS_HI_DEVIDATION_ENABLED        MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_HI_DEVIATION)
#define IS_VOLUME_CURVE_ENABLED         MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_VOLUME_CURVE_SEL)
#define IS_MONO_ONLY_ENABLED            MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_MONO_ONLY)
#define IS_SCART_ENABLED                MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_SCART)
#define IS_WSS_ENABLED                  MApp_ATVProc_IsThisATVOptionEnabled(E_ENABLE_WSS)

#define IS_COUNTRY_ONLY_ATV(c)          ( (c==E_BULGARIA)      ||  \
                                          (c==E_CROATIA)       ||  \
                                          (c==E_HUNGARY)       ||  \
                                          (c==E_NORWAY)        ||  \
                                          (c==E_POLAND)        ||  \
                                          (c==E_PORTUGAL)      ||  \
                                          (c==E_ROMANIA)       ||  \
                                          (c==E_RUSSIA)        ||  \
                                          (c==E_SERBIA)        ||  \
                                          (c==E_SLOVENIA)      ||  \
                                          (c==E_SWITZERLAND) )


BOOLEAN MApp_ATVProc_IsThisATVOptionEnabled(THISATV_OPTION eOption);

// Prototype
void msAPI_ATV_InitVariable(void);
void msAPI_ATV_InitATVDataManager(void);
void msAPI_ATV_ResetATVDataManager(void);
void msAPI_ATV_ResetChannelData(void);

BOOLEAN msAPI_ATV_GetLastVideoStandard(AVD_InputSourceType eVideoSource, AVD_VideoStandardType *peVideoStandard);
BOOLEAN msAPI_ATV_SetLastVideoStandard(AVD_InputSourceType eVideoSource, AVD_VideoStandardType eVideoStandard);
S8 msAPI_ATV_GetFineTune(BYTE u8ProgramNumber);

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
BOOLEAN msAPI_ATV_GetBrightness(AVD_InputSourceType eVideoSource, BYTE *pu8Percent);
BOOLEAN msAPI_ATV_SetBrightness(AVD_InputSourceType eVideoSource, BYTE u8Percent);
BOOLEAN msAPI_ATV_GetContrast(AVD_InputSourceType eVideoSource, BYTE *pu8Percent);
BOOLEAN msAPI_ATV_SetContrast(AVD_InputSourceType eVideoSource, BYTE u8Percent);
BOOLEAN msAPI_ATV_GetColor(AVD_InputSourceType eVideoSource, BYTE *pu8Percent);
BOOLEAN msAPI_ATV_SetColor(AVD_InputSourceType eVideoSource, BYTE u8Percent);
BOOLEAN msAPI_ATV_GetHue(AVD_InputSourceType eVideoSource, BYTE *pu8Percent);
BOOLEAN msAPI_ATV_SetHue(AVD_InputSourceType eVideoSource, BYTE u8Percent);
BOOLEAN msAPI_ATV_GetSharpness(AVD_InputSourceType eVideoSource, BYTE *pu8Percent);
BOOLEAN msAPI_ATV_SetSharpness(AVD_InputSourceType eVideoSource, BYTE u8Percent);
#endif

// for Favorate Program
void msAPI_ATV_SetFavoriteProgram(BYTE u8ProgramNumber, BOOLEAN bIsFavorite);
BYTE msAPI_ATV_GetFirstFavoriteProgramNumber(void);
BYTE msAPI_ATV_GetLastFavoriteProgramNumber(void);
BYTE msAPI_ATV_GetPreviousFavoriteProgramNumber(BYTE u8BaseProgramNumber);
BYTE msAPI_ATV_GetNextFavoriteProgramNumber(BYTE u8BaseProgramNumber);
BYTE msAPI_ATV_GetTotalFavoriteProgramCount(void);
BOOLEAN msAPI_ATV_IsProgramFavorite(BYTE u8ProgramNumber);

// for Program Type
BYTE msAPI_ATV_GetCurrentProgramNumber(void);
void msAPI_ATV_SetCurrentProgramNumber(BYTE u8ProgramNumber);
BYTE msAPI_ATV_GetFirstProgramNumber(BOOLEAN bIncludeSkipped);
BYTE msAPI_ATV_GetNextProgramNumber(BYTE u8BaseProgramNumber, BOOLEAN bIncludeSkipped);
BYTE msAPI_ATV_GetPrevProgramNumber(BYTE u8BaseProgramNumber, BOOLEAN bIncludeSkipped);
BYTE msAPI_ATV_GetPastProgramNumber(void);
BOOLEAN msAPI_ATV_IncCurrentProgramNumber(void);
BOOLEAN msAPI_ATV_DecCurrentProgramNumber(void);
WORD msAPI_ATV_GetProgramPLLData(BYTE u8ProgramNumber);
void msAPI_ATV_SetProgramPLLData(BYTE u8ProgramNumber, WORD wPLL);
AUDIOSTANDARD_TYPE msAPI_ATV_GetAudioStandard(BYTE u8ProgramNumber);
void msAPI_ATV_SetAudioStandard(BYTE u8ProgramNumber, AUDIOSTANDARD_TYPE eStandard);
AVD_VideoStandardType msAPI_ATV_GetVideoStandardOfProgram(BYTE u8ProgramNumber);
AVD_VideoStandardType msAPI_ATV_GetUserVideoStandardOfProgram(BYTE u8ProgramNumber);
void msAPI_ATV_SetVideoStandardOfProgram(BYTE u8ProgramNumber, AVD_VideoStandardType eStandard);
void msAPI_ATV_SetUserVideoStandardOfProgram(BYTE u8ProgramNumber, AVD_VideoStandardType eStandard);
//----------------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetAudioMode(AUDIOSOURCE_TYPE eSource, AUDIOMODE_TYPE *peAudioMode);

//----------------------------------------------------------------------------------------
//
#define DEBUG_SET_ATV_AUDIO_MODE    0
#if(DEBUG_SET_ATV_AUDIO_MODE)
#define msAPI_ATV_SetAudioMode(src, mode)   do {                    \
    printf("%u: %s call ATV_SetAudioMode\n", __LINE__, __FILE__);   \
    msAPI_ATV_SetAudioMode_2((src), (mode));                        \
} while(0)
#else
#define msAPI_ATV_SetAudioMode(src, mode)   do {    \
    msAPI_ATV_SetAudioMode_2((src), (mode));        \
} while(0)
#endif
BOOLEAN msAPI_ATV_SetAudioMode_2(AUDIOSOURCE_TYPE eSource, AUDIOMODE_TYPE eAudioMode);

//----------------------------------------------------------------------------------------
//BOOLEAN msAPI_ATV_WasForeignLanguageSelected(void);
BYTE msAPI_ATV_GetDualAudioSelected(void);
BOOLEAN msAPI_ATV_IsProgramSkipped(BYTE u8ProgramNumber);
void msAPI_ATV_SkipProgram(BYTE u8ProgramNumber, BOOLEAN bSkip);
BOOLEAN msAPI_ATV_IsProgramLocked(BYTE u8ProgramNumber);
void msAPI_ATV_LockProgram(BYTE u8ProgramNumber, BOOLEAN bIsLock);

#if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
BOOLEAN msAPI_ATV_IsProgrambIsTerrestrial(BYTE u8ProgramNumber);
void msAPI_ATV_SetProgramAntenna(BYTE u8ProgramNumber, BOOLEAN bIsTerrestrial);
#endif

BOOLEAN msAPI_ATV_IsAFTNeeded(BYTE u8ProgramNumber);
void msAPI_ATV_NeedAFT(BYTE u8ProgramNumber, BOOLEAN bNeed);
void msAPI_ATV_GetMediumAndChannelNumber(BYTE u8ProgramNumber, MEDIUM * peMedium, BYTE * pu8ChannelNumber);
void msAPI_ATV_SetMediumAndChannelNumber(BYTE u8ProgramNumber, MEDIUM eMedium, BYTE u8ChannelNumber);
BOOLEAN msAPI_ATV_GetStationName(BYTE u8ProgramNumber, BYTE *sName);
BOOLEAN msAPI_ATV_SetStationName(BYTE u8ProgramNumber, BYTE *sName);
BOOLEAN msAPI_ATV_GetListPageNumber(BYTE u8ListIndex, WORD *pwListPageNumber);
BOOLEAN msAPI_ATV_SetListPageNumber(BYTE u8ListIndex, WORD wListPageNumber);
BOOLEAN msAPI_ATV_SetSortingPriority(BYTE u8Priority);
void msAPI_ATV_SortProgram(BYTE u8Start, BYTE u8Stop);
BOOLEAN msAPI_ATV_DeleteProgram(BYTE u8ProgramNumber);
BOOLEAN msAPI_ATV_MoveProgram(BYTE u8Source, BYTE u8Target);
BOOLEAN msAPI_ATV_SwapProgram(BYTE u8ProgramNumber1, BYTE u8ProgramNumber2);
BOOLEAN msAPI_ATV_IsProgramNumberActive(BYTE u8ProgramNumber);
BOOLEAN msAPI_ATV_IsProgramEmpty(void);
BYTE msAPI_ATV_GetActiveProgramCount(void);
void msAPI_ATV_SaveProgram(BYTE u8CurrentProgramNumber);
BYTE msAPI_ATV_ConvertProgramNumberToOrdinalNumber(BYTE u8ProgramNumber);
BYTE msAPI_ATV_ConvertOrdinalNumberToProgramNumber(WORD u16OrdinalNumber);

#if( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC))
void msAPI_ATV_ResetAntennaChannelData(void);
//BOOLEAN msAPI_ATV_CopyProgram(void);
BOOLEAN msAPI_ATV_IsProgramAutoColorSystem(BYTE u8ProgramNumber);
void msAPI_ATV_SaveProgram_Exit_Menu(BYTE u8CurrentProgramNumber);
void msAPI_ATV_SetProgramAutoColorSystem(BYTE u8ProgramNumber, BOOLEAN AutoColorSystem);
BOOLEAN msAPI_ATV_IsProgramSearched(BYTE u8ProgramNumber);
void msAPI_ATV_SetSearchedProgram(BYTE u8ProgramNumber, BOOLEAN bIsSearched);
WORD msAPI_ATV_MapChanToFreq(BYTE u8ProgramNumber);

EN_ANT_TYPE msAPI_ATV_GetCurrentAntenna(void);
void msAPI_ATV_SetCurrentAntenna(EN_ANT_TYPE bAntenna);

BYTE msAPI_ATV_LoadCurrentProgramNumber(void);
BOOLEAN msAPI_ATV_GetDirectTuneFlag(void);
void msAPI_ATV_SetDirectTuneFlag(BOOLEAN bDirectTune);
void msAPI_ATV_InitProgramPLLData(void);
#endif // #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )


#if (ENABLE_CH_VOLUME_COMP)
BYTE msAPI_ATV_GetVolumeComp(BYTE u8ProgramNumber);
void msAPI_ATV_SetVolumeComp(BYTE u8cProgramNumber, BYTE eVolumeComp);
#endif //(ENABLE_CH_VOLUME_COMP)

BYTE msAPI_ATV_GetChannelMax(void);
BYTE msAPI_ATV_GetChannelMin(void);

#if 1//ENABLE_CH_FORCEVIDEOSTANDARD
void msAPI_ATV_SetForceVideoStandardFlag(BYTE u8ProgramNumber, U8 u8Force);
U8 msAPI_ATV_GetForceVideoStandardFlag(BYTE u8ProgramNumber);
#endif



/***************************************************************************************/

#endif // __API_ATVSYSTEM_H__

