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

///////////////////////////////////////////////////////////////2pa/////////////////
//
/// @file msAPI_ATVSystem.h
/// This file includes MStar ATV System Application interface
/// @brief API for ATV control
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
#include <stddef.h>
#include "MsCommon.h"
#include "debug.h"

#include "Utl.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Ram.h"
#include "msAPI_Tuning.h"
#include "msAPI_audio.h"
#include "msAPI_VD.h"
#include "msAPI_MIU.h"
#include "msAPI_Flash.h"
#if (ENABLE_TTX)
#include "msAPI_TTX.h"
#endif
#include "apiXC_Sys.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Cus.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MsOS.h"

#include "MApp_SaveData.h"
#include "MApp_DataBase.h"



#if 0 // set to 1 to enable debug
    #define ATV_MSG(a,b)    debugPrint(a,b)
#else
    #define ATV_MSG(a,b)
#endif

#include "debug.h"

//------------------------------------------------------------------------------
// Local Defines
//------------------------------------------------------------------------------

typedef enum
{
    E_BRIGHTNESS        = 0x00,
    E_CONTRAST          = 0x01,
    E_COLOR             = 0x02,
    E_HUE               = 0x03,
    E_SHARPNESS         = 0x04,
    E_MAX_ITEM          = 0x05
} EN_PICTURE_QUALITY_ITEMS;


#define DATA_IDENTIFICATION                         0x77        // Increase constant number when you want to restruct nvram map. never use 0x00.

#define PR_INVALID_INDEX                            0xFD
#define PR_NOTHING                                  PR_INVALID_INDEX

#define PRDATA_PLL_PARAM                            0x01
#define PRDATA_MISC_PARAM                           0x02
#define PRDATA_FINETUNE_PARAM                       0x04
#define PRDATA_NAME_PARAM                           0x08
#define PRDATA_SORT_PARAM                           0x10
#define PRDATA_LIST_PARAM                           0x20
#define PRDATA_ALL_PARAM                            (PRDATA_PLL_PARAM | PRDATA_MISC_PARAM | PRDATA_FINETUNE_PARAM | PRDATA_NAME_PARAM | PRDATA_LIST_PARAM)

#if ( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC) )
#define ATV_FIRST_PR_NUM                            (msAPI_ATV_GetChannelMin()-1)
#elif ENABLE_SBTVD_ATV_SYSTEM
#define ATV_FIRST_PR_NUM                            (IS_SBTVD_APP ? (msAPI_ATV_GetChannelMin()-1) : 0)
#else
#define ATV_FIRST_PR_NUM                            0
#endif

//------------------------------------------------------------------------------
// NVRAM Default
//------------------------------------------------------------------------------

#define DEFAULT_TV_AUDIOMODE                        E_AUDIOMODE_MONO //E_AUDIOMODE_INVALID     //E_AUDIOMODE_MONO    // NEED TOUCH
#define DEFAULT_LR_AUDIOMODE                        E_AUDIOMODE_LEFT_RIGHT

#define DEFAULT_LASTPROGRAM                         (msAPI_ATV_GetChannelMin()-1)
//#define DEFAULT_PLL                                 UHF_MAX_PLL+10 //let the default PLL out of normal range for identification default PLL valume
#define DEFAULT_MEDIUM                              MEDIUM_CABLE
#define DEFAULT_CHANNELNUMBER                       47


#define DEFAULT_SKIP_VALUE                          TRUE
#define DEFAULT_AFT_VALUE                           TRUE
#define DEFAULT_FAVORITE_VALUE                      FALSE
#define DEFAULT_LOCK_VALUE                          FALSE

#define DEFAULT_SEARCHED_VALUE                      FALSE

#if( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC))
#define DEFAULT_VIDEOSTANDARD_OF_PROGRAM            E_VIDEOSTANDARD_NTSC_M
#elif ENABLE_SBTVD_ATV_SYSTEM
#define DEFAULT_VIDEOSTANDARD_OF_PROGRAM            (IS_SBTVD_APP ? E_VIDEOSTANDARD_NTSC_M : E_VIDEOSTANDARD_PAL_BGHI)
#else
#define DEFAULT_VIDEOSTANDARD_OF_PROGRAM            E_VIDEOSTANDARD_PAL_BGHI
#endif


#define DEFAULT_USER_VIDEOSTANDARD_OF_PROGRAM       E_VIDEOSTANDARD_AUTO
#define DEFAULT_FINETUNE                            0x00
#define DEFAULT_LISTPAGE                            m_wDefaultListPageNumber
#define DEFAULT_DUAL_AUDIO_SELECTION                E_DUAL_AUDIO_A
#define DEFAULT_REALTIME_AUDIOSTNDARD_DETECTION     TRUE
#if( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC))
#define DEFAULT_LAST_VIDEOSTANDARD                  E_VIDEOSTANDARD_NTSC_M
#elif ENABLE_SBTVD_ATV_SYSTEM
#define DEFAULT_LAST_VIDEOSTANDARD                  (IS_SBTVD_APP ? E_VIDEOSTANDARD_NTSC_M : E_VIDEOSTANDARD_PAL_BGHI)
#else
#define DEFAULT_LAST_VIDEOSTANDARD                  E_VIDEOSTANDARD_PAL_BGHI
#endif
#if( ENABLE_ATV_SYS_PICTURE_SETTING )
// TODO: why use define and put here?
#define DEFAULT_ATV_BRIGHTNESS                      53
#define DEFAULT_CVBS1_BRIGHTNESS                    53
#define DEFAULT_CVBS2_BRIGHTNESS                    53
#define DEFAULT_SVIDEO1_BRIGHTNESS                  53
#define DEFAULT_SVIDEO2_BRIGHTNESS                  53
#define DEFAULT_SCART1_BRIGHTNESS                   53
#define DEFAULT_SCART2_BRIGHTNESS                   53

#define DEFAULT_ATV_CONTRAST                        50
#define DEFAULT_CVBS1_CONTRAST                      50
#define DEFAULT_CVBS2_CONTRAST                      50
#define DEFAULT_SVIDEO1_CONTRAST                    50
#define DEFAULT_SVIDEO2_CONTRAST                    50
#define DEFAULT_SCART1_CONTRAST                     50
#define DEFAULT_SCART2_CONTRAST                     50

#define DEFAULT_ATV_COLOR                           70
#define DEFAULT_CVBS1_COLOR                         70
#define DEFAULT_CVBS2_COLOR                         70
#define DEFAULT_SVIDEO1_COLOR                       70
#define DEFAULT_SVIDEO2_COLOR                       70
#define DEFAULT_SCART1_COLOR                        70
#define DEFAULT_SCART2_COLOR                        70

#define DEFAULT_ATV_HUE                             50
#define DEFAULT_CVBS1_HUE                           50
#define DEFAULT_CVBS2_HUE                           50
#define DEFAULT_SVIDEO1_HUE                         50
#define DEFAULT_SVIDEO2_HUE                         50
#define DEFAULT_SCART1_HUE                          50
#define DEFAULT_SCART2_HUE                          50

#define DEFAULT_ATV_SHARPNESS                       50
#define DEFAULT_CVBS1_SHARPNESS                     50
#define DEFAULT_CVBS2_SHARPNESS                     50
#define DEFAULT_SVIDEO1_SHARPNESS                   30
#define DEFAULT_SVIDEO2_SHARPNESS                   30
#define DEFAULT_SCART1_SHARPNESS                    50
#define DEFAULT_SCART2_SHARPNESS                    50
#endif

#if( ENABLE_CH_FORCEVIDEOSTANDARD )
    #define DEFAULT_FORCEVIDEOSTANDARD_VALUE        E_FORCE_VD_MODE_ON_FOREVER
#else
    #define DEFAULT_FORCEVIDEOSTANDARD_VALUE        E_FORCE_VD_MODE_OFF
#endif

// COMMON NVRAM MAP
#define BASEADDRESS_COMMON_DATA                     ( RM_TV_COMMON_DATA_START_ADR )
#define BASEADDRESS_IDENT                           ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, wID)) )
//#define BASEADDRESS_COUNTRY                         ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, eCountry)) )
#define BASEADDRESS_AUDIOMODE                       ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, AudioMode)) )
#define BASEADDRESS_LAST_VIDEOSTANDARD              ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, LastVideoStandard)) )

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
#define BASEADDRESS_PQ_ATV                          ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, PictureQualityOfATV)) )
#define BASEADDRESS_PQ_CVBS1                        ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, PictureQualityOfCVBS1)) )
#define BASEADDRESS_PQ_CVBS2                        ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, PictureQualityOfCVBS2)) )
#define BASEADDRESS_PQ_SVIDEO1                      ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, PictureQualityOfSVIDEO1)) )
#define BASEADDRESS_PQ_SVIDEO2                      ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, PictureQualityOfSVIDEO2)) )
#define BASEADDRESS_PQ_SCART1                       ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, PictureQualityOfSCART1)) )
#define BASEADDRESS_PQ_SCART2                       ( BASEADDRESS_COMMON_DATA + (offsetof(COMMON_DATA_STRUCTURE, PictureQualityOfSCART2)) )
#endif

#define END_BASEADDRESS_COMMON_DATA                 ( BASEADDRESS_COMMON_DATA + sizeof(COMMON_DATA_STRUCTURE))

// PROGRAM NVRAM MAP
//#define BASEADDRESS_PR_LASTPRNUMBER             RM_ATV_LAST_START_ADR
#define BASEADDRESS_PR_DATA                         ( RM_ATV_CHSET_START_ADDR )
#define BASEADDRESS_PR_ATVPRINDEXTABLE              ( BASEADDRESS_PR_DATA + (offsetof(ATV_PROGRAM_DATA_STRUCTURE, u8ATVPRIndexTable)) )
#define BASEADDRESS_PR_ATVPRTABLEMAP                ( BASEADDRESS_PR_DATA + (offsetof(ATV_PROGRAM_DATA_STRUCTURE, u8ATVPRTableMap)) )
#define BASEADDRESS_PR_ATVPRTABLE                   ( BASEADDRESS_PR_DATA + (offsetof(ATV_PROGRAM_DATA_STRUCTURE, ATVProgramData)) )

#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
//#define BASEADDRESS_CATV_PR_LASTPRNUMBER            RM_CATV_LAST_START_ADR
#define BASEADDRESS_CATV_PR_DATA                    ( BASEADDRESS_PR_DATA + sizeof(ATV_PROGRAM_DATA_STRUCTURE) )
#define BASEADDRESS_CATV_PR_ATVPRINDEXTABLE         ( BASEADDRESS_CATV_PR_DATA + (offsetof(CATV_PROGRAM_DATA_STRUCTURE, u8CATVPRIndexTable)) )
#define BASEADDRESS_CATV_PR_ATVPRTABLEMAP           ( BASEADDRESS_CATV_PR_DATA + (offsetof(CATV_PROGRAM_DATA_STRUCTURE, u8CATVPRTableMap)) )
#define BASEADDRESS_CATV_PR_ATVPRTABLE              ( BASEADDRESS_CATV_PR_DATA + (offsetof(CATV_PROGRAM_DATA_STRUCTURE, CATVProgramData)) )
#define END_ADDRESS_OF_ATVDATA_STRUCTURE            ( RM_ATV_CHSET_START_ADDR + (sizeof(CATV_PROGRAM_DATA_STRUCTURE)+sizeof(ATV_PROGRAM_DATA_STRUCTURE)))
#else
#define END_ADDRESS_OF_ATVDATA_STRUCTURE            ( RM_ATV_CHSET_START_ADDR + (sizeof(ATV_PROGRAM_DATA_STRUCTURE)))
#endif

//=================================================
// Variables resided in RAM
//=================================================
static WORD             _u16Identification = 0x00;

static BYTE             _u8CurrentProgramNumber;
static BYTE             _u8PastProgramNumber;

// PROGRAM DATA
#if ENABLE_SBTVD_ATV_SYSTEM

#if MAX_ATVPROGRAM > MAX_CATVPROGRAM
#error "MAX_ATVPROGRAM > MAX_CATVPROGRAM"
#endif

static BYTE             _u8ATVPRIndexTable[MAX_CATVPROGRAM]; // air/catv use same table
static BYTE             _u8PRTableMap[MAX_CATV_PRTABLEMAP];

#else

static BYTE             _u8ATVPRIndexTable[MAX_ATVPROGRAM];
static BYTE             _u8PRTableMap[MAX_PRTABLEMAP];

#endif

static BYTE sNullStationName[MAX_STATION_NAME] = { '-','-','-','-','-', 0, 0, 0 };

//=================================================
// Constants resided in ROM
//=================================================
#if ENABLE_TTX
static ROM WORD m_wDefaultListPageNumber[MAX_LISTPAGE] =
{
    100,
    200,
    300,
    400
};
#endif

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
typedef struct
{
    AVD_InputSourceType eVideoSource;
    PICTURE_QUALITY_ITEMS PictureQualityItems;
} PICTURE_QUALITY_ITEMS_DEFAULT;

static ROM PICTURE_QUALITY_ITEMS_DEFAULT m_PictureQualityItemsDefault[] =
{
    { E_INPUT_SOURCE_ATV,       {DEFAULT_ATV_BRIGHTNESS,    DEFAULT_ATV_CONTRAST,       DEFAULT_ATV_COLOR,        DEFAULT_ATV_HUE,        DEFAULT_ATV_SHARPNESS} },
    { E_INPUT_SOURCE_CVBS1,     {DEFAULT_CVBS1_BRIGHTNESS,  DEFAULT_CVBS1_CONTRAST,     DEFAULT_CVBS1_COLOR,    DEFAULT_CVBS1_HUE,        DEFAULT_CVBS1_SHARPNESS} },
    { E_INPUT_SOURCE_CVBS2,     {DEFAULT_CVBS2_BRIGHTNESS,  DEFAULT_CVBS2_CONTRAST,     DEFAULT_CVBS2_COLOR,    DEFAULT_CVBS2_HUE,        DEFAULT_CVBS2_SHARPNESS} },
    { E_INPUT_SOURCE_SVIDEO1,   {DEFAULT_SVIDEO1_BRIGHTNESS,DEFAULT_SVIDEO1_CONTRAST,   DEFAULT_SVIDEO1_COLOR,    DEFAULT_SVIDEO1_HUE,    DEFAULT_SVIDEO1_SHARPNESS} },
    { E_INPUT_SOURCE_SVIDEO2,   {DEFAULT_SVIDEO2_BRIGHTNESS,DEFAULT_SVIDEO2_CONTRAST,   DEFAULT_SVIDEO2_COLOR,    DEFAULT_SVIDEO2_HUE,    DEFAULT_SVIDEO2_SHARPNESS} },
    { E_INPUT_SOURCE_SCART1,    {DEFAULT_SCART1_BRIGHTNESS, DEFAULT_SCART1_CONTRAST,    DEFAULT_SCART1_COLOR,    DEFAULT_SCART1_HUE,        DEFAULT_SCART1_SHARPNESS} },
    { E_INPUT_SOURCE_SCART2,    {DEFAULT_SCART2_BRIGHTNESS, DEFAULT_SCART2_CONTRAST,    DEFAULT_SCART2_COLOR,    DEFAULT_SCART2_HUE,        DEFAULT_SCART2_SHARPNESS} }
};
#endif

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------
static void _CorrectDuplication(void);
static void _CorrectMapping(void);
static BOOLEAN _GetPRTable(BYTE u8Index, BYTE * pu8Buffer, BYTE u8Param);
static BOOLEAN _SetPRTable(BYTE u8Index, BYTE * pu8Buffer, BYTE u8Param);
static BOOLEAN _DeletePRTable(BYTE u8Index);
static BOOLEAN _MovePRTable(BYTE u8From, BYTE u8To);
static BOOLEAN _SwapPRTable(BYTE u8Index1, BYTE u8Index2);
static BYTE _GetPRIndexTable(BYTE u8Index);
static void _SetPRIndexTable(BYTE u8Index, BYTE u8PRIndex);
static BOOLEAN _IsPREntityActive(BYTE u8PRIndex);
static void _ActivePREntity(BYTE u8PRIndex, BOOLEAN bActive);
static BOOLEAN _IsIndexActive(BYTE u8Index);
static BYTE _GetEmptyPREntity(void);
static void _FillPREntityWithDefault(BYTE u8PRIndex);
static BYTE _LoadProgramNumber(void);
static void _SaveProgramNumber(BYTE u8ProgramNumber);

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
static BOOLEAN _GetPercentOfPictureItem(EN_PICTURE_QUALITY_ITEMS ePictureItem, AVD_InputSourceType eVideoSource, BYTE *pu8Percent);
static BOOLEAN _SetPercentOfPictureItem(EN_PICTURE_QUALITY_ITEMS ePictureItem, AVD_InputSourceType eVideoSource, BYTE u8Percent);
#endif

#if ENABLE_TTX
static WORD _GetListPageNumber(BYTE *pu8Buffer, BYTE u8ListIndex);
static void _SetListPageNumber(BYTE *pu8Buffer, BYTE u8ListIndex, WORD u16ListPageNumber);
#endif
static BOOLEAN _GetNVRAM(DWORD u32Address, BYTE * pu8Buffer, BYTE u8Size);
static BOOLEAN _SetNVRAM(DWORD u32Address, BYTE *pu8Buffer, BYTE u8Size);
static void _StringCopy(BYTE *pu8Dst, BYTE *pu8Src, BYTE u8Size);

//------------------------------------------------------------------------------
/// -This function will reset ATV Data manager (for TV/AV)
//------------------------------------------------------------------------------
void msAPI_ATV_ResetATVDataManager(void)
{
    WORD wID = DATA_IDENTIFICATION;

    PRINT_CURRENT_LINE();
    printf("msAPI_ATV_InitATVDataManager()\n");

    msAPI_ATV_ResetChannelData();

    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, DEFAULT_TV_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_CVBS1, DEFAULT_LR_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_CVBS2, DEFAULT_LR_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_SVIDEO1, DEFAULT_LR_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_SVIDEO2, DEFAULT_LR_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_SCART1, DEFAULT_LR_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_SCART2, DEFAULT_LR_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_PC, DEFAULT_LR_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_YPbPr, DEFAULT_LR_AUDIOMODE);
    msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_HDMI, DEFAULT_LR_AUDIOMODE);

    msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_ATV, DEFAULT_LAST_VIDEOSTANDARD);
    msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_CVBS1, DEFAULT_LAST_VIDEOSTANDARD);
    msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_CVBS2, DEFAULT_LAST_VIDEOSTANDARD);
    msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_SVIDEO1, DEFAULT_LAST_VIDEOSTANDARD);
    msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_SVIDEO2, DEFAULT_LAST_VIDEOSTANDARD);
    msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_SCART1, DEFAULT_LAST_VIDEOSTANDARD);
    msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_SCART2, DEFAULT_LAST_VIDEOSTANDARD);

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
    msAPI_ATV_SetBrightness(E_INPUT_SOURCE_ATV, DEFAULT_ATV_BRIGHTNESS);
    msAPI_ATV_SetBrightness(E_INPUT_SOURCE_CVBS1, DEFAULT_CVBS1_BRIGHTNESS);
    msAPI_ATV_SetBrightness(E_INPUT_SOURCE_CVBS2, DEFAULT_CVBS2_BRIGHTNESS);
    msAPI_ATV_SetBrightness(E_INPUT_SOURCE_SVIDEO1, DEFAULT_SVIDEO1_BRIGHTNESS);
    msAPI_ATV_SetBrightness(E_INPUT_SOURCE_SVIDEO2, DEFAULT_SVIDEO2_BRIGHTNESS);
    msAPI_ATV_SetBrightness(E_INPUT_SOURCE_SCART1, DEFAULT_SCART1_BRIGHTNESS);
    msAPI_ATV_SetBrightness(E_INPUT_SOURCE_SCART2, DEFAULT_SCART2_BRIGHTNESS);

    msAPI_ATV_SetContrast(E_INPUT_SOURCE_ATV, DEFAULT_ATV_CONTRAST);
    msAPI_ATV_SetContrast(E_INPUT_SOURCE_CVBS1, DEFAULT_CVBS1_CONTRAST);
    msAPI_ATV_SetContrast(E_INPUT_SOURCE_CVBS2, DEFAULT_CVBS2_CONTRAST);
    msAPI_ATV_SetContrast(E_INPUT_SOURCE_SVIDEO1, DEFAULT_SVIDEO1_CONTRAST);
    msAPI_ATV_SetContrast(E_INPUT_SOURCE_SVIDEO2, DEFAULT_SVIDEO2_CONTRAST);
    msAPI_ATV_SetContrast(E_INPUT_SOURCE_SCART1, DEFAULT_SCART1_CONTRAST);
    msAPI_ATV_SetContrast(E_INPUT_SOURCE_SCART2, DEFAULT_SCART2_CONTRAST);

    msAPI_ATV_SetColor(E_INPUT_SOURCE_ATV, DEFAULT_ATV_COLOR);
    msAPI_ATV_SetColor(E_INPUT_SOURCE_CVBS1, DEFAULT_CVBS1_COLOR);
    msAPI_ATV_SetColor(E_INPUT_SOURCE_CVBS2, DEFAULT_CVBS2_COLOR);
    msAPI_ATV_SetColor(E_INPUT_SOURCE_SVIDEO1, DEFAULT_SVIDEO1_COLOR);
    msAPI_ATV_SetColor(E_INPUT_SOURCE_SVIDEO2, DEFAULT_SVIDEO2_COLOR);
    msAPI_ATV_SetColor(E_INPUT_SOURCE_SCART1, DEFAULT_SCART1_COLOR);
    msAPI_ATV_SetColor(E_INPUT_SOURCE_SCART2, DEFAULT_SCART2_COLOR);

    msAPI_ATV_SetHue(E_INPUT_SOURCE_ATV, DEFAULT_ATV_HUE);
    msAPI_ATV_SetHue(E_INPUT_SOURCE_CVBS1, DEFAULT_CVBS1_HUE);
    msAPI_ATV_SetHue(E_INPUT_SOURCE_CVBS2, DEFAULT_CVBS2_HUE);
    msAPI_ATV_SetHue(E_INPUT_SOURCE_SVIDEO1, DEFAULT_SVIDEO1_HUE);
    msAPI_ATV_SetHue(E_INPUT_SOURCE_SVIDEO2, DEFAULT_SVIDEO2_HUE);
    msAPI_ATV_SetHue(E_INPUT_SOURCE_SCART1, DEFAULT_SCART1_HUE);
    msAPI_ATV_SetHue(E_INPUT_SOURCE_SCART2, DEFAULT_SCART2_HUE);

    msAPI_ATV_SetSharpness(E_INPUT_SOURCE_ATV, DEFAULT_ATV_SHARPNESS);
    msAPI_ATV_SetSharpness(E_INPUT_SOURCE_CVBS1, DEFAULT_CVBS1_SHARPNESS);
    msAPI_ATV_SetSharpness(E_INPUT_SOURCE_CVBS2, DEFAULT_CVBS2_SHARPNESS);
    msAPI_ATV_SetSharpness(E_INPUT_SOURCE_SVIDEO1, DEFAULT_SVIDEO1_SHARPNESS);
    msAPI_ATV_SetSharpness(E_INPUT_SOURCE_SVIDEO2, DEFAULT_SVIDEO2_SHARPNESS);
    msAPI_ATV_SetSharpness(E_INPUT_SOURCE_SCART1, DEFAULT_SCART1_SHARPNESS);
    msAPI_ATV_SetSharpness(E_INPUT_SOURCE_SCART2, DEFAULT_SCART2_SHARPNESS);
#endif

    _SetNVRAM(BASEADDRESS_IDENT, (BYTE *)&wID, sizeof(wID));

}

//------------------------------------------------------------------------------
/// -This function will get last Video Standard (for TV/AV)
/// @return BOOLEAN : Function execution result
//------------------------------------------------------------------------------
#define DEBUG_ATV_LAST_VIDEO_STD(x)     //x
BOOLEAN msAPI_ATV_GetLastVideoStandard(AVD_InputSourceType eVideoSource, AVD_VideoStandardType *peVideoStandard)
{
    AVD_VideoStandardType eVideoStandard;

    DEBUG_ATV_LAST_VIDEO_STD(printf("msAPI_ATV_GetLastVideoStandard(eVideoSource=%u)\n", eVideoSource););

    switch (eVideoSource)
    {
    case E_INPUT_SOURCE_ATV:
        _GetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eATVStandard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_CVBS1:
        _GetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eCVBS1Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_CVBS2:
        _GetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eCVBS2Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_SVIDEO1:
        _GetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eSVIDEO1Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_SVIDEO2:
        _GetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eSVIDEO2Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_SCART1:
        _GetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eSCART1Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_SCART2:
        _GetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eSCART2Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    default:
        *peVideoStandard = DEFAULT_LAST_VIDEOSTANDARD;
        return FALSE;
    }

    if( eVideoStandard != E_VIDEOSTANDARD_PAL_BGHI &&
        eVideoStandard != E_VIDEOSTANDARD_NTSC_M &&
        eVideoStandard != E_VIDEOSTANDARD_SECAM &&
        eVideoStandard != E_VIDEOSTANDARD_NTSC_44 &&
        eVideoStandard != E_VIDEOSTANDARD_PAL_M &&
        eVideoStandard != E_VIDEOSTANDARD_PAL_N &&
        eVideoStandard != E_VIDEOSTANDARD_PAL_60 )
    {
        eVideoStandard = DEFAULT_LAST_VIDEOSTANDARD;
        msAPI_ATV_SetLastVideoStandard(eVideoSource, eVideoStandard);
    }

    *peVideoStandard = eVideoStandard;


    DEBUG_ATV_LAST_VIDEO_STD(printf(" => eVideoStandard=%u\n", eVideoStandard););

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will set last Video Standard (for TV/AV)
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param eVideoStandard \b IN: Video Standard
/// -@see AVD_VideoStandardType
/// @return BOOLEAN : Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetLastVideoStandard(AVD_InputSourceType eVideoSource, AVD_VideoStandardType eVideoStandard)
{
    DEBUG_ATV_LAST_VIDEO_STD(printf("msAPI_ATV_SetLastVideoStandard(eVideoSource=%u, eVideoStandard=%u)\n", eVideoSource, eVideoStandard););

    if ( eVideoStandard != E_VIDEOSTANDARD_PAL_BGHI &&
         eVideoStandard != E_VIDEOSTANDARD_NTSC_M &&
         eVideoStandard != E_VIDEOSTANDARD_SECAM &&
         eVideoStandard != E_VIDEOSTANDARD_NTSC_44 &&
         eVideoStandard != E_VIDEOSTANDARD_PAL_M &&
         eVideoStandard != E_VIDEOSTANDARD_PAL_N &&
         eVideoStandard != E_VIDEOSTANDARD_PAL_60 )
    {
        printf("\nWarning: ATV_SetLastVideoStandard: eVideoStandard=%u\n", eVideoStandard);
        return FALSE;
    }

    //printf("msAPI_ATV_SetLastVideoStandard eVideoStandard:%u\n", eVideoStandard);

    switch ( eVideoSource )
    {
    case E_INPUT_SOURCE_ATV:
        _SetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eATVStandard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_CVBS1:
        _SetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eCVBS1Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_CVBS2:
        _SetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eCVBS2Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_SVIDEO1:
        _SetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eSVIDEO1Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_SVIDEO2:
        _SetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eSVIDEO2Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_SCART1:
        _SetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eSCART1Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    case E_INPUT_SOURCE_SCART2:
        _SetNVRAM(BASEADDRESS_LAST_VIDEOSTANDARD + offsetof(LASTVIDEOSTANDARD, eSCART2Standard),
                (BYTE *)&eVideoStandard, sizeof(eVideoStandard));
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will get fine tune (for TV/AV)
/// @param cProgramNumber \b IN: program number
/// @return signed char:
/// - Fine tune table index if success
/// - DEFAULT_FINETUNE
//------------------------------------------------------------------------------
S8 msAPI_ATV_GetFineTune(BYTE u8ProgramNumber)
{
    signed char s8FineTune=0;

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&s8FineTune, PRDATA_FINETUNE_PARAM) )
    {
        return s8FineTune;
    }

    return DEFAULT_FINETUNE;
}

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
//------------------------------------------------------------------------------
/// -This function will get Brightness
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param *pcPercent \b IN: Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetBrightness(AVD_InputSourceType eVideoSource, BYTE *pu8Percent)
{
    return _GetPercentOfPictureItem(E_BRIGHTNESS, eVideoSource, pu8Percent);
}

//------------------------------------------------------------------------------
/// -This function will set Brightness
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param cPercent \b IN: Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetBrightness(AVD_InputSourceType eVideoSource, BYTE u8Percent)
{
    return _SetPercentOfPictureItem(E_BRIGHTNESS, eVideoSource, u8Percent);
}

//------------------------------------------------------------------------------
/// -This function will get Contrast
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param *pcPercent \b IN: pointer to the Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetContrast(AVD_InputSourceType eVideoSource, BYTE *pu8Percent)
{
    return _GetPercentOfPictureItem(E_CONTRAST, eVideoSource, pu8Percent);
}

//------------------------------------------------------------------------------
/// -This function will set Contrast
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param cPercent \b IN: Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetContrast(AVD_InputSourceType eVideoSource, BYTE u8Percent)
{
    return _SetPercentOfPictureItem(E_CONTRAST, eVideoSource, u8Percent);
}

//------------------------------------------------------------------------------
/// -This function will get Color
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param *pcPercent \b IN: pointer to the Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetColor(AVD_InputSourceType eVideoSource, BYTE *pu8Percent)
{
    return _GetPercentOfPictureItem(E_COLOR, eVideoSource, pu8Percent);
}

//------------------------------------------------------------------------------
/// -This function will set Color
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param cPercent \b IN: Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetColor(AVD_InputSourceType eVideoSource, BYTE u8Percent)
{
    return _SetPercentOfPictureItem(E_COLOR, eVideoSource, u8Percent);
}

//------------------------------------------------------------------------------
/// -This function will get Hue
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param *pcPercent \b IN: pointer to the Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetHue(AVD_InputSourceType eVideoSource, BYTE *pu8Percent)
{
    return _GetPercentOfPictureItem(E_HUE, eVideoSource, pu8Percent);
}

//------------------------------------------------------------------------------
/// -This function will set Color
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param cPercent \b IN: Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetHue(AVD_InputSourceType eVideoSource, BYTE u8Percent)
{
    return _SetPercentOfPictureItem(E_HUE, eVideoSource, u8Percent);
}

//------------------------------------------------------------------------------
/// -This function will get Sharpness
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param *pcPercent \b IN: pointer to the Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetSharpness(AVD_InputSourceType eVideoSource, BYTE *pu8Percent)
{
    return _GetPercentOfPictureItem(E_SHARPNESS, eVideoSource, pu8Percent);
}

//------------------------------------------------------------------------------
/// -This function will set Sharpness
/// @param eVideoSource \b IN: Video source type
/// -@see AVD_InputSourceType
/// @param cPercent \b IN: Value in percentage
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetSharpness(AVD_InputSourceType eVideoSource, BYTE u8Percent)
{
    return _SetPercentOfPictureItem(E_SHARPNESS, eVideoSource, u8Percent);
}
#endif

//------------------------------------------------------------------------------
/// -This function will set favorite Program
/// @param cProgramNumber \b IN: Program Number
/// @param bIsFavorite \b IN:
/// - TRUE: Favorite program
/// - FALSE: Not Favorite
//------------------------------------------------------------------------------
void msAPI_ATV_SetFavoriteProgram(BYTE u8ProgramNumber, BOOLEAN bIsFavorite)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( bIsFavorite == FALSE )
        {
            Misc.bIsFavorite = FALSE;
        }
        else
        {
            Misc.bIsFavorite = TRUE;
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}


//------------------------------------------------------------------------------
/// -This function will get last favorite Program
/// @return BYTE: Last Favorite Program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetLastFavoriteProgramNumber(void)
{
    return 1;
}

//------------------------------------------------------------------------------
/// -This function will check if the specific program is a favorit program
/// @param cProgramNumber \b IN: Base program number
/// @return BOOLEAN:
/// - TRUE: it's a favorite program
/// - FALSE: Not a favorite program
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgramFavorite(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( Misc.bIsFavorite == FALSE )
        {
            return FALSE;
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will get Current Program number
/// @return BYTE: Current Program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetCurrentProgramNumber(void)
{
    return _u8CurrentProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get past Program number
/// @return BYTE: past program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetPastProgramNumber(void)
{
    return _u8PastProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will decrease current Program number
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_DecCurrentProgramNumber(void)
{
    if ( _u8CurrentProgramNumber == ATV_FIRST_PR_NUM )
    {
        return FALSE;
    }

    _u8PastProgramNumber = _u8CurrentProgramNumber;

    _u8CurrentProgramNumber--;

    _SaveProgramNumber(_u8CurrentProgramNumber);

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will get Audio standard
/// @param cProgramNumber \b IN: program number
/// @return AUDIOSTANDARD_TYPE: Audio standard
/// -@see AUDIOSTANDARD_TYPE
//------------------------------------------------------------------------------
AUDIOSTANDARD_TYPE msAPI_ATV_GetAudioStandard(BYTE u8ProgramNumber)
{
#if(ENABLE_ATSC)
    u8ProgramNumber= u8ProgramNumber;
    return E_AUDIOSTANDARD_M_BTSC;

#else
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if( Misc.eAudioStandard == E_AUDIOSTANDARD_BG ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_BG_A2 ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_BG_NICAM ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_I ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_DK ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_DK1_A2 ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_DK2_A2 ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_DK3_A2 ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_DK_NICAM ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_L ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_M ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_M_BTSC ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_M_A2 ||
            Misc.eAudioStandard == E_AUDIOSTANDARD_M_EIA_J )
        {
            return (AUDIOSTANDARD_TYPE)Misc.eAudioStandard;
        }
    }

    return DEFAULT_AUDIOSTANDARD;
#endif
}

//------------------------------------------------------------------------------
/// -This function will set Audio standard
/// @param cProgramNumber \b IN: program number
/// @param eStandard \b IN: Audio standard
/// - @see AUDIOSTANDARD_TYPE
//------------------------------------------------------------------------------
void msAPI_ATV_SetAudioStandard(BYTE u8cProgramNumber, AUDIOSTANDARD_TYPE eStandard)
{
    ATV_MISC Misc;
    AUDIOSTANDARD_TYPE enNewAudioStd;


    //printf("\e[31;1m >> msAPI_ATV_SetAudioStandard(%u, [%s:%u]) \33[m \n", u8cProgramNumber, msAPI_AUD_Get_StdString(eStandard), eStandard);

    memset(&Misc,0,sizeof(ATV_MISC));
    if( TRUE == _GetPRTable(u8cProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if( eStandard == E_AUDIOSTANDARD_BG ||
            eStandard == E_AUDIOSTANDARD_BG_A2 ||
            eStandard == E_AUDIOSTANDARD_BG_NICAM ||
            eStandard == E_AUDIOSTANDARD_I ||
            eStandard == E_AUDIOSTANDARD_DK ||
            eStandard == E_AUDIOSTANDARD_DK1_A2 ||
            eStandard == E_AUDIOSTANDARD_DK2_A2 ||
            eStandard == E_AUDIOSTANDARD_DK3_A2 ||
            eStandard == E_AUDIOSTANDARD_DK_NICAM ||
            eStandard == E_AUDIOSTANDARD_L ||
            eStandard == E_AUDIOSTANDARD_M ||
            eStandard == E_AUDIOSTANDARD_M_BTSC ||
            eStandard == E_AUDIOSTANDARD_M_A2 ||
            eStandard == E_AUDIOSTANDARD_M_EIA_J )
        {
            //Misc.eAudioStandard = eStandard;
            enNewAudioStd = eStandard;
        }
        else
        {
            //Misc.eAudioStandard = DEFAULT_AUDIOSTANDARD;
            enNewAudioStd = DEFAULT_AUDIOSTANDARD;
        }

        // Check if changed
        if( enNewAudioStd == Misc.eAudioStandard ) // Data is the same...
        {
            //printf("  SetAudio: Skip Save~\n");
            return;
        }

        Misc.eAudioStandard = enNewAudioStd;

        if(TRUE != _SetPRTable(u8cProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}

//------------------------------------------------------------------------------
/// -This function will check if the specific program is skipped or not.
/// @param cProgramNumber \b IN: program number
/// @return BOOLEAN:
/// - TRUE: Skipped
/// - FALAS: Not skipped
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgramSkipped(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( Misc.bSkip == FALSE )
        {
            return FALSE;
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will check if the specific program is skipped or not.
/// @param cProgramNumber \b IN: program number
/// @param bSkip \b IN:
/// - TRUE: Skip this program
/// - FALAS: Don't skip this program
//------------------------------------------------------------------------------
void msAPI_ATV_SkipProgram(BYTE u8ProgramNumber, BOOLEAN bSkip)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( bSkip == FALSE )
        {
            Misc.bSkip = FALSE;
        }
        else
        {
            Misc.bSkip = TRUE;
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}

//------------------------------------------------------------------------------
/// -This function will check if the specific program is locked
/// @param cProgramNumber \b IN: program number
/// @return BOOLEAN:
/// - TRUE: Locked
/// - FALAS: Not Locked
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgramLocked(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( Misc.bIsLock == FALSE )
        {
            return FALSE;
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will check if the specific program is skipped or not.
/// @param cProgramNumber \b IN: program number
/// @param bIsLock \b IN:
/// - TRUE: Lock this program
/// - FALAS: Don't lock this program
//------------------------------------------------------------------------------
void msAPI_ATV_LockProgram(BYTE u8ProgramNumber, BOOLEAN bIsLock)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( bIsLock == FALSE )
        {
            Misc.bIsLock = FALSE;
        }
        else
        {
            Misc.bIsLock = TRUE;
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}

#if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
//------------------------------------------------------------------------------
/// -This function will check if the specific program is Terrestrial
/// @param cProgramNumber \b IN: program number
/// @return BOOLEAN:
/// - TRUE: Terrestrial
/// - FALAS: Cable
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgrambIsTerrestrial(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( Misc.bIsTerrestrial == FALSE )
        {
            return FALSE;
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will check if the specific program is or not.
/// @param cProgramNumber \b IN: program number
/// @param bIsTerrestral \b IN:
/// - TRUE: Set this program terrestral
/// - FALAS: Set this program Cable
//------------------------------------------------------------------------------
void msAPI_ATV_SetProgramAntenna(BYTE u8ProgramNumber, BOOLEAN bIsTerrestrial)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( bIsTerrestrial == FALSE )
        {
            Misc.bIsTerrestrial = FALSE;
        }
        else
        {
            Misc.bIsTerrestrial = TRUE;
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
            __ASSERT(0);
    }
}
#endif

//------------------------------------------------------------------------------
/// -This function will save program
/// @param cCurrentProgramNumber \b IN: current program number
//------------------------------------------------------------------------------
void msAPI_ATV_SaveProgram(BYTE u8CurrentProgramNumber)
{
    BYTE sStationName[MAX_STATION_NAME];

    if ( msAPI_ATV_GetCurrentProgramNumber() != u8CurrentProgramNumber )
    {
        msAPI_ATV_SetCurrentProgramNumber(u8CurrentProgramNumber);
    }

    if ( FALSE == msAPI_Tuner_IsAFTNeeded() &&
         TRUE == msAPI_Tuner_IsCurrentChannelAndSavedChannelSame() )
    {
        msAPI_ATV_NeedAFT(u8CurrentProgramNumber, FALSE);
    }
    else
    {
        msAPI_ATV_NeedAFT(u8CurrentProgramNumber, TRUE);
    }

    msAPI_ATV_SkipProgram(u8CurrentProgramNumber, FALSE);

    msAPI_ATV_SetFavoriteProgram(u8CurrentProgramNumber, FALSE);

    msAPI_ATV_LockProgram(u8CurrentProgramNumber, FALSE);

#if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
    msAPI_ATV_SetProgramAntenna(u8CurrentProgramNumber, (!IsDVBCInUse()));
#endif

#if (ENABLE_SBTVD_ATV_SYSTEM || ENABLE_DVB_TAIWAN_APP)
    msAPI_ATV_SetSearchedProgram(msAPI_ATV_GetCurrentProgramNumber(),TRUE);
#endif


    msAPI_Tuner_GetCurrentStationName(sStationName);

    msAPI_ATV_SetStationName(u8CurrentProgramNumber, sStationName);

    msAPI_ATV_SetAudioStandard(u8CurrentProgramNumber, msAPI_AUD_GetAudioStandard());

    msAPI_ATV_SetVideoStandardOfProgram(u8CurrentProgramNumber, msAPI_AVD_GetVideoStandard());

    msAPI_ATV_SetProgramPLLData(u8CurrentProgramNumber, msAPI_Tuner_GetCurrentChannelPLL());

    msAPI_ATV_SetMediumAndChannelNumber(u8CurrentProgramNumber, msAPI_Tuner_GetMedium(), msAPI_Tuner_GetChannelNumber());
}

//------------------------------------------------------------------------------
/// -This function will appoint if this program need AFT or not.
/// @param cProgramNumber \b IN: Program number
/// @param bNeed \b IN: needed or not
/// - TRUE: Yes
/// - FALSE: NO
//------------------------------------------------------------------------------
void msAPI_ATV_NeedAFT(BYTE u8ProgramNumber, BOOLEAN bNeed)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if (bNeed == TRUE)
        {
            Misc.bAFT = TRUE;
        }
        else
        {
            Misc.bAFT = FALSE;
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}


//------------------------------------------------------------------------------
/// -This function will get Video standard of the program
/// @param cProgramNumber \b IN: Program number
/// @return AVD_VideoStandardType: video standard type
//------------------------------------------------------------------------------

BOOL _msAPI_ATV_CheckRange_VideoStandardOfProgram(AVD_VideoStandardType eStandard)
{
#if(ENABLE_ATV_CHINA_APP||ENABLE_DTMB_CHINA_APP||ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    if( eStandard == E_VIDEOSTANDARD_PAL_BGHI ||
        eStandard == E_VIDEOSTANDARD_NTSC_M ||
        eStandard == E_VIDEOSTANDARD_SECAM ||
        eStandard == E_VIDEOSTANDARD_PAL_M ||
        eStandard == E_VIDEOSTANDARD_PAL_N ||
        eStandard == E_VIDEOSTANDARD_PAL_60||
        eStandard == E_VIDEOSTANDARD_NTSC_44
       )
    {
        return TRUE;
    }
    else
    {
        //eStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
        return FALSE;
    }
#else
    if( eStandard == E_VIDEOSTANDARD_PAL_BGHI ||
        eStandard == E_VIDEOSTANDARD_NTSC_M ||
        eStandard == E_VIDEOSTANDARD_SECAM ||
        eStandard == E_VIDEOSTANDARD_PAL_M ||
        eStandard == E_VIDEOSTANDARD_PAL_N )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

#endif

    return TRUE;
}

AVD_VideoStandardType msAPI_ATV_GetVideoStandardOfProgram(BYTE u8ProgramNumber)
{
#if ENABLE_ATSC

    u8ProgramNumber= u8ProgramNumber;
    return E_VIDEOSTANDARD_NTSC_M;
#else
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if( _msAPI_ATV_CheckRange_VideoStandardOfProgram((AVD_VideoStandardType)Misc.eVideoStandard) )
        {
            return (AVD_VideoStandardType)Misc.eVideoStandard;
        }
    }

/*
#if(ENABLE_ATV_CHINA_APP||ENABLE_DTMB_CHINA_APP||ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    return E_VIDEOSTANDARD_AUTO;
#else
    return E_VIDEOSTANDARD_NOTSTANDARD;
#endif
*/
    return DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
#endif
}

//------------------------------------------------------------------------------
/// -This function will set Video standard of the program
/// @param cProgramNumber \b IN: Program number
/// @param eStandard: video standard type
/// -@see AVD_VideoStandardType
//------------------------------------------------------------------------------
void msAPI_ATV_SetVideoStandardOfProgram(BYTE u8ProgramNumber, AVD_VideoStandardType eStandard)
{
    ATV_MISC Misc;


    // Check eStandard
    if( _msAPI_ATV_CheckRange_VideoStandardOfProgram(eStandard) )
    {
    }
    else
    {
        printf("\nError: ATV_SetVideoStd: invalid eStandard=%u\n", eStandard);
        return;

        eStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
    }

    memset(&Misc,0,sizeof(ATV_MISC));

    if( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        Misc.eVideoStandard = eStandard;

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}

//------------------------------------------------------------------------------
/// -This function will get Video standard of the program
/// @param cProgramNumber \b IN: Program number
/// @return AVD_VideoStandardType: video standard type
//------------------------------------------------------------------------------

BOOL _msAPI_ATV_CheckRange_UserVideoStandardOfProgram(AVD_VideoStandardType eStandard)
{
    if( eStandard == E_VIDEOSTANDARD_PAL_BGHI ||
        eStandard == E_VIDEOSTANDARD_NTSC_M ||
        eStandard == E_VIDEOSTANDARD_SECAM ||
        eStandard == E_VIDEOSTANDARD_PAL_M ||
        eStandard == E_VIDEOSTANDARD_PAL_N ||
        eStandard == E_VIDEOSTANDARD_PAL_60||
        eStandard == E_VIDEOSTANDARD_NTSC_44 ||
        eStandard == E_VIDEOSTANDARD_AUTO
       )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

AVD_VideoStandardType msAPI_ATV_GetUserVideoStandardOfProgram(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if( _msAPI_ATV_CheckRange_UserVideoStandardOfProgram((AVD_VideoStandardType)Misc.eVideoStandard_User) )
        {
            //printf("#### Misc.eVideoStandard_User:%u\n", Misc.eVideoStandard_User);
            return (AVD_VideoStandardType)Misc.eVideoStandard_User;
        }
    }

    return E_VIDEOSTANDARD_AUTO;
}

//------------------------------------------------------------------------------
/// -This function will set specific user's Video standard of the program
/// @param cProgramNumber \b IN: Program number
/// @param eStandard: video standard type
/// -@see AVD_VideoStandardType
//------------------------------------------------------------------------------
void msAPI_ATV_SetUserVideoStandardOfProgram(BYTE u8ProgramNumber, AVD_VideoStandardType eStandard)
{
    ATV_MISC Misc;

    // Check eStandard
    if( _msAPI_ATV_CheckRange_UserVideoStandardOfProgram(eStandard) )
    {
    }
    else
    {
        printf("\nError: ATV_SetUserVideoStd: invalid eStandard=%u\n", eStandard);
        return;
    }

    memset(&Misc,0,sizeof(ATV_MISC));
    if( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        Misc.eVideoStandard_User = eStandard;
        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
        //_GetPRTable(u8ProgramNumber, (BYTE *)&Misc2, PRDATA_MISC_PARAM);
    }
    else
    {
        __ASSERT(0);
    }
}

//------------------------------------------------------------------------------
/// -This function will get Audio Mode
/// @param eSource \b IN: Audio source type
/// - @see AUDIOSOURCE_TYPE
/// @param *peAudioMode \b IN: Pointer to Audio mode for return
/// - @see AUDIOMODE_TYPE
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetAudioMode(AUDIOSOURCE_TYPE eSource, AUDIOMODE_TYPE *peAudioMode)
{
    AUDIOMODE_TYPE eAudioMode;
    ATV_MISC Misc;

    //printf(" msAPI_ATV_GetAudioMode(eSource=%u)\n", eSource);

    if (peAudioMode == NULL)
    {
        return FALSE;
    }

    memset(&Misc,0,sizeof(ATV_MISC));
    eAudioMode = E_AUDIOMODE_INVALID;

    switch ( eSource )
    {
        case E_AUDIOSOURCE_MPEG:
            eAudioMode = E_AUDIOMODE_LEFT_RIGHT;
            break;

    case E_AUDIOSOURCE_ATV:
        if(TRUE == _GetPRTable(_u8CurrentProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            eAudioMode = (AUDIOMODE_TYPE)Misc.eAudioMode;
        }
        else
        {
            printf("_GetPRTable failed! _u8CurrentProgramNumber=%u\n", _u8CurrentProgramNumber);
        }
        break;

    case E_AUDIOSOURCE_CVBS1:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eCVBS1AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_CVBS2:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eCVBS2AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_SVIDEO1:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eSVIDEO1AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_SVIDEO2:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eSVIDEO2AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_SCART1:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eSCART1AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_SCART2:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eSCART2AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_PC:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, ePCAudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_YPbPr:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eYPbPrAudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_HDMI:
        _GetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eHDMIAudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    default:
        ATV_MSG("Audio Fatal ERROR",0);
        printf("\nError: ATV_GetAudioMode: eSource=%u\n", eSource);
        *peAudioMode = DEFAULT_LR_AUDIOMODE;
        return FALSE;
    }

    //printf(" eAudioMode=%u\n", eAudioMode);

    if ( eSource == E_AUDIOSOURCE_ATV )
    {
        if( eAudioMode == E_AUDIOMODE_MONO || eAudioMode == E_AUDIOMODE_FORCED_MONO || eAudioMode == E_AUDIOMODE_HIDEV_MONO ||
            eAudioMode == E_AUDIOMODE_G_STEREO || eAudioMode == E_AUDIOMODE_K_STEREO ||
            eAudioMode == E_AUDIOMODE_MONO_SAP || eAudioMode == E_AUDIOMODE_STEREO_SAP ||
            eAudioMode == E_AUDIOMODE_DUAL_A || eAudioMode == E_AUDIOMODE_DUAL_B || eAudioMode == E_AUDIOMODE_DUAL_AB ||
            eAudioMode == E_AUDIOMODE_NICAM_MONO ||
            eAudioMode == E_AUDIOMODE_NICAM_STEREO ||
            eAudioMode == E_AUDIOMODE_NICAM_DUAL_A || eAudioMode == E_AUDIOMODE_NICAM_DUAL_B || eAudioMode == E_AUDIOMODE_NICAM_DUAL_AB )
        {
            if ( FALSE == IS_SAVING_DUAL_ENABLED )
            {
                if ( eAudioMode == E_AUDIOMODE_DUAL_B || eAudioMode == E_AUDIOMODE_DUAL_AB )
                {
                    eAudioMode = E_AUDIOMODE_DUAL_A;
                }
                else if ( eAudioMode == E_AUDIOMODE_NICAM_DUAL_B || eAudioMode == E_AUDIOMODE_NICAM_DUAL_AB )
                {
                    eAudioMode = E_AUDIOMODE_NICAM_DUAL_A;
                }
            }

            *peAudioMode = eAudioMode;
            return TRUE;
        }
        else
        {
            msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, DEFAULT_TV_AUDIOMODE);
            *peAudioMode = DEFAULT_TV_AUDIOMODE;
        }
    }
    else
    {
        if ( eAudioMode == E_AUDIOMODE_LEFT_LEFT || eAudioMode == E_AUDIOMODE_RIGHT_RIGHT || eAudioMode == E_AUDIOMODE_LEFT_RIGHT )
        {
            *peAudioMode = eAudioMode;
            return TRUE;
        }
        else
        {
            msAPI_ATV_SetAudioMode(eSource, DEFAULT_LR_AUDIOMODE);
            *peAudioMode = DEFAULT_LR_AUDIOMODE;
        }
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will set Audio Mode
/// @param eSource \b IN: Audio source type
/// - @see AUDIOSOURCE_TYPE
/// @param eAudioMode \b IN:Audio mode
/// - @see AUDIOMODE_TYPE
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
//
BOOLEAN msAPI_ATV_SetAudioMode_2(AUDIOSOURCE_TYPE eSource, AUDIOMODE_TYPE eAudioMode)
{
    ATV_MISC Misc;

    //printf("msAPI_ATV_SetAudioMode(eSource=%u, eAudioMode=0x%X)\n", eSource, eAudioMode);

    if ( eSource == E_AUDIOSOURCE_ATV )
    {
        if( eAudioMode != E_AUDIOMODE_MONO && eAudioMode != E_AUDIOMODE_FORCED_MONO && eAudioMode != E_AUDIOMODE_HIDEV_MONO &&
            eAudioMode != E_AUDIOMODE_G_STEREO && eAudioMode != E_AUDIOMODE_K_STEREO &&
            eAudioMode != E_AUDIOMODE_MONO_SAP && eAudioMode != E_AUDIOMODE_STEREO_SAP &&
            eAudioMode != E_AUDIOMODE_DUAL_A && eAudioMode != E_AUDIOMODE_DUAL_B && eAudioMode != E_AUDIOMODE_DUAL_AB &&
            eAudioMode != E_AUDIOMODE_NICAM_MONO &&
            eAudioMode != E_AUDIOMODE_NICAM_STEREO &&
            eAudioMode != E_AUDIOMODE_NICAM_DUAL_A && eAudioMode != E_AUDIOMODE_NICAM_DUAL_B && eAudioMode != E_AUDIOMODE_NICAM_DUAL_AB )
        {
            return FALSE;
        }
    }
    else
    {
        if( eAudioMode != E_AUDIOMODE_LEFT_LEFT && eAudioMode != E_AUDIOMODE_RIGHT_RIGHT && eAudioMode != E_AUDIOMODE_LEFT_RIGHT )
        {
            return FALSE;
        }
    }

    switch ( eSource )
    {
    case E_AUDIOSOURCE_ATV :
        if(TRUE != _GetPRTable(_u8CurrentProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            printf("GetPRTable failed!\n");
            break;
        }

        if ( (eAudioMode == E_AUDIOMODE_DUAL_B) || (eAudioMode == E_AUDIOMODE_NICAM_DUAL_B) )
        {
            Misc.bWasDualAudioSelected = E_DUAL_AUDIO_B;
        }
        else if ( (eAudioMode == E_AUDIOMODE_DUAL_A) || (eAudioMode == E_AUDIOMODE_NICAM_DUAL_A) )
        {
            Misc.bWasDualAudioSelected = E_DUAL_AUDIO_A;
        }
        else if ( (eAudioMode == E_AUDIOMODE_DUAL_AB) || (eAudioMode == E_AUDIOMODE_NICAM_DUAL_AB) )
        {
            Misc.bWasDualAudioSelected = E_DUAL_AUDIO_AB;
        }

        Misc.eAudioMode = eAudioMode;

        if ( TRUE == _IsPREntityActive(_GetPRIndexTable(_u8CurrentProgramNumber)) )
        {
            if(TRUE != _SetPRTable(_u8CurrentProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
            {
                __ASSERT(0);
            }
        }
        break;

    case E_AUDIOSOURCE_CVBS1:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eCVBS1AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_CVBS2:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eCVBS2AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_SVIDEO1:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eSVIDEO1AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_SVIDEO2:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eSVIDEO2AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_SCART1:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eSCART1AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_SCART2:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eSCART2AudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_PC:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, ePCAudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_YPbPr:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eYPbPrAudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    case E_AUDIOSOURCE_HDMI:
        _SetNVRAM(BASEADDRESS_AUDIOMODE + offsetof(AUDIOMODE, eYPbPrAudioMode),
                (BYTE *)&eAudioMode, sizeof(AUDIOMODE_TYPE));
        break;

    default:
        ATV_MSG("Audio Fatal ERROR", 0);
        return FALSE;
    }

    return TRUE;
}

#if(0)
BOOLEAN msAPI_ATV_WasForeignLanguageSelected(void)
{
    ATV_MISC Misc;

    if ( TRUE == _GetPRTable(_u8CurrentProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if( Misc.bWasDualAudioSelected == TRUE )
        {
            return TRUE;
        }
    }

    return FALSE;
}
#endif

//------------------------------------------------------------------------------
/// -This function will get Dual Audio Selected
/// @return BYTE: Selected mode
/// -@see EN_DUAL_AUDIO_SELECTION
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetDualAudioSelected(void)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(_u8CurrentProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {

        return Misc.bWasDualAudioSelected;
    }
    return E_DUAL_MONO;
}

//------------------------------------------------------------------------------
/// -This function will set Station name
/// @param cProgramNumber \b IN: Program number
/// @param sName \b IN: station name
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetStationName(BYTE u8ProgramNumber, BYTE *sName)
{
    if ( TRUE == _SetPRTable(u8ProgramNumber, sName, PRDATA_NAME_PARAM) )
    {
        return TRUE;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will get List Page Number
/// @param u8ListIndex \b IN: List Index
/// @param pwListPageNumber \b IN: pointer to List Page Number
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
#if ENABLE_TTX
BOOLEAN msAPI_ATV_GetListPageNumber(BYTE u8ListIndex, WORD * pwListPageNumber)
{
    BYTE u8SavedListPage[MAX_LISTPAGE_SIZE]={0};
    WORD wSavedListPageNumber;

    if ( MAX_LISTPAGE <= u8ListIndex )
    {
        return FALSE;
    }

    if ( TRUE != _GetPRTable(_u8CurrentProgramNumber, u8SavedListPage, PRDATA_LIST_PARAM) )
    {
        return FALSE;
    }

    wSavedListPageNumber = _GetListPageNumber(u8SavedListPage, u8ListIndex);

    if ( wSavedListPageNumber < 100 || 899 < wSavedListPageNumber )
    {
        wSavedListPageNumber = DEFAULT_LISTPAGE[u8ListIndex];
    }

    *pwListPageNumber = wSavedListPageNumber;

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will set List Page Number
/// @param u8ListIndex \b IN: List Index
/// @param pwListPageNumber \b IN: pointer to List Page Number
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetListPageNumber(BYTE u8ListIndex, WORD wListPageNumber)
{
    BYTE u8SavedListPage[MAX_LISTPAGE_SIZE]={0};

    if ( MAX_LISTPAGE <= u8ListIndex )
    {
        return FALSE;
    }

    if ( wListPageNumber < 100 || 899 < wListPageNumber )
    {
        return FALSE;
    }

    if ( TRUE != _GetPRTable(_u8CurrentProgramNumber, u8SavedListPage, PRDATA_LIST_PARAM) )
    {
        return FALSE;
    }

    _SetListPageNumber(u8SavedListPage, u8ListIndex, wListPageNumber);

    if(TRUE == _SetPRTable(_u8CurrentProgramNumber, u8SavedListPage, PRDATA_LIST_PARAM))
        return TRUE;

    return FALSE;
}
#endif

//------------------------------------------------------------------------------
/// -This function will set Sorting Priority
/// @param u8Priority \b IN: Priority
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SetSortingPriority(BYTE u8Priority)
{
    if ( TRUE == _SetPRTable(_u8CurrentProgramNumber, &u8Priority, PRDATA_SORT_PARAM) )
    {
        return TRUE;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will copy program
/// @param cProgramNumber \b IN: Program number
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_DeleteProgram(BYTE u8ProgramNumber)
{
    if ( TRUE == _DeletePRTable(u8ProgramNumber) )
    {
        return TRUE;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will move program
/// @param cSource \b IN: Source
/// @param cTarget \b IN: Target
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_MoveProgram(BYTE u8Source, BYTE u8Target)
{
    if ( TRUE == _MovePRTable(u8Source, u8Target) )
    {
        if ( u8Source == _u8CurrentProgramNumber )
        {
            _u8CurrentProgramNumber = u8Target;
        }

        return TRUE;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will exchange program
/// @param u8Index1 \b IN: Program number 1
/// @param u8Index2 \b IN: Program number 2
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_SwapProgram(BYTE u8ProgramNumber1, BYTE u8ProgramNumber2)
{
    if ( TRUE == _SwapPRTable(u8ProgramNumber1, u8ProgramNumber2) )
    {
        return TRUE;
    }

    return FALSE;
}

#if ( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC) )
#include "msAPI_ATVSystem_NTSC.c"

void msAPI_ATV_InitVariable(void)
{
    if(stGenSetting.stScanMenuSetting.u8Antenna == ANT_CATV)
        _bAntenna = ANT_CATV;
    else
        _bAntenna = ANT_AIR;
}

#else

#if ENABLE_SBTVD_ATV_SYSTEM
static EN_ANT_TYPE _bAntenna = ANT_AIR;
#endif

#define _MAX_ATVPROGRAM     _u8MaxAtvProgram
#define _MAX_PRTABLEMAP     _u8MaxPRTableMap

static U32 _u32ATVPRIndexTableAddr;
static U32 _u32PRTableMapAddr;
static U32 _u32PRTableAddr;
static U8 _u8MaxAtvProgram;
static U8 _u8MaxPRTableMap;

void msAPI_ATV_InitATVDataAddr(void)
{
    //printf("msAPI_ATV_InitATVDataAddr()\n");
#if ENABLE_SBTVD_ATV_SYSTEM
    //printf("_bAntenna=%u\n", _bAntenna);
#endif

#if ENABLE_SBTVD_ATV_SYSTEM
    if( IS_SBTVD_APP && (_bAntenna == ANT_CATV))
    {
        _u32ATVPRIndexTableAddr = BASEADDRESS_CATV_PR_ATVPRINDEXTABLE;
        _u32PRTableMapAddr      = BASEADDRESS_CATV_PR_ATVPRTABLEMAP;
        _u32PRTableAddr         = BASEADDRESS_CATV_PR_ATVPRTABLE;
        _u8MaxAtvProgram        = MAX_CATVPROGRAM;
        _u8MaxPRTableMap        = MAX_CATV_PRTABLEMAP;
    }
    else
#endif
    {
        _u32ATVPRIndexTableAddr = BASEADDRESS_PR_ATVPRINDEXTABLE;
        _u32PRTableMapAddr      = BASEADDRESS_PR_ATVPRTABLEMAP;
        _u32PRTableAddr         = BASEADDRESS_PR_ATVPRTABLE;
        _u8MaxAtvProgram        = MAX_ATVPROGRAM;
        _u8MaxPRTableMap        = MAX_PRTABLEMAP;
    }
}

void msAPI_ATV_LoadATVData(void)
{
    _GetNVRAM(_u32ATVPRIndexTableAddr, _u8ATVPRIndexTable, _MAX_ATVPROGRAM);
    _GetNVRAM(_u32PRTableMapAddr, _u8PRTableMap, _MAX_PRTABLEMAP);
}

void msAPI_ATV_InitVariable(void)
{
#if ENABLE_SBTVD_ATV_SYSTEM
    if(IS_SBTVD_APP && stGenSetting.stScanMenuSetting.u8Antenna == ANT_CATV)
    {
        _bAntenna = ANT_CATV;
    }
    else
    {
        _bAntenna = ANT_AIR;
    }
#endif

    msAPI_ATV_InitATVDataAddr();
}

//------------------------------------------------------------------------------
/// -This function will init ATV Data manager (for TV/AV)
//------------------------------------------------------------------------------
//****************************************************************************
/// Init ATV Data Manager
//****************************************************************************
void msAPI_ATV_InitATVDataManager(void)
{
    BYTE i;

    PRINT_CURRENT_LINE();
    printf("msAPI_ATV_InitATVDataManager()\n");


    if ( _u16Identification != DATA_IDENTIFICATION )
    {
        for ( i = 0 ; i < 5 ; i++ )
        {
            if ( TRUE == _GetNVRAM(BASEADDRESS_IDENT, (BYTE *)&_u16Identification, sizeof(_u16Identification)) )
            {
                if ( _u16Identification == DATA_IDENTIFICATION )
                {
                    break;
                }
            }
        }

        #if 0
        if ( i >= 5 )
        {
            ATV_MSG("ATV data structure is cleard", 0);
        }
        #endif
    }
    else
    {
        _u8PastProgramNumber = _u8CurrentProgramNumber;

        return;
    }

    if ( _u16Identification != DATA_IDENTIFICATION )
    {
        msAPI_ATV_ResetATVDataManager();

        _u16Identification = DATA_IDENTIFICATION;

        _SetNVRAM(BASEADDRESS_IDENT, (BYTE *)&_u16Identification, sizeof(_u16Identification));
    }

    msAPI_ATV_LoadATVData();

    _CorrectDuplication();
    _CorrectMapping();

    _u8CurrentProgramNumber = _LoadProgramNumber();

    _u8PastProgramNumber = _u8CurrentProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will reset ATV Channel Data (for TV/AV)
//------------------------------------------------------------------------------
void msAPI_ATV_ResetAntennaChannelData(void)
{
    BYTE i;
    BOOL bIsFillCh = FALSE;

    PRINT_CURRENT_LINE();
    printf("msAPI_ATV_ResetAntennaChannelData()\n");

#if ENABLE_SBTVD_ATV_SYSTEM
    if(IS_SBTVD_APP)
    {
        bIsFillCh = TRUE;
    }
#endif

    _SaveProgramNumber(DEFAULT_LASTPROGRAM);

    _u8PastProgramNumber = DEFAULT_LASTPROGRAM;

    for ( i = 0; i < _MAX_PRTABLEMAP; i++ )
    {
        _u8PRTableMap[i] = bIsFillCh ? 0xFF : 0;
    }

    _SetNVRAM(_u32PRTableMapAddr, (BYTE *)&_u8PRTableMap, sizeof(_u8PRTableMap));

    for ( i = 0; i < _MAX_ATVPROGRAM; i++ )
    {
        if(bIsFillCh)
        {
            _SetPRIndexTable(i, i);
            _FillPREntityWithDefault(i);
        }
        else
        {
            _SetPRIndexTable(i, PR_NOTHING);
        }
    }
}

void msAPI_ATV_ResetChannelData(void)
{
#if ENABLE_SBTVD_ATV_SYSTEM
    if(IS_SBTVD_APP)
    {
        msAPI_Reset_Tuner_GetNumberOfChBeFound_WhileAutoScan();

        if(msAPI_ATV_GetCurrentAntenna() == ANT_AIR)
        {
            msAPI_ATV_SetCurrentAntenna(ANT_CATV);
        }
        else
        {
            msAPI_ATV_SetCurrentAntenna(ANT_AIR);
        }
        msAPI_ATV_ResetAntennaChannelData();

        if(msAPI_ATV_GetCurrentAntenna() == ANT_AIR)
        {
            msAPI_ATV_SetCurrentAntenna(ANT_CATV);
        }
        else
        {
            msAPI_ATV_SetCurrentAntenna(ANT_AIR);
        }
    }
    else
    {
        msAPI_ATV_SetCurrentAntenna(ANT_AIR);
    }
#endif

    msAPI_ATV_ResetAntennaChannelData();
}

#if ENABLE_SBTVD_ATV_SYSTEM
EN_ANT_TYPE msAPI_ATV_GetCurrentAntenna(void)
{
    return _bAntenna;
}

void msAPI_ATV_SetCurrentAntenna(EN_ANT_TYPE bAntenna)
{
    printf("msAPI_ATV_SetCurrentAntenna(bAntenna=%u)\n", bAntenna);

    if(IS_SBTVD_APP)
        _bAntenna = bAntenna;
    else
        _bAntenna = ANT_AIR;

    msAPI_ATV_InitATVDataAddr();

    msAPI_ATV_LoadATVData();

   #if ENABLE_ISDB_DOUBLE_RF_INPUT
    if (_bAntenna == ANT_AIR)
    {
        RF_Switch_To_Air();
    }
    else
    {
        RF_Switch_To_Cable();
    }
   #endif
}
#endif

//------------------------------------------------------------------------------
/// -This function will get Medium and Channel Number
/// @param cProgramNumber \b IN: Program number
/// @param *peMedium \b IN: pointer to Medium for return
/// -@see MEDIUM
/// @param *pcChannelNumber \b IN: pointer to Channel number for return
//------------------------------------------------------------------------------
void msAPI_ATV_GetMediumAndChannelNumber(BYTE u8ProgramNumber, MEDIUM * peMedium, BYTE * pcChannelNumber)
{
    ATV_MISC Misc;
    memset(&Misc,0,sizeof(ATV_MISC));
    WORD wPLL = 0;

    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        if ( peMedium != NULL )
        {
            *peMedium = DEFAULT_MEDIUM;
        }

        if ( pcChannelNumber != NULL )
        {
            *pcChannelNumber = DEFAULT_CHANNELNUMBER;
        }

        return;
    }

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( TRUE == msAPI_CFT_IsValidMediumAndChannel((MEDIUM)Misc.eMedium, Misc.u8ChannelNumber) )
        {
            if ( peMedium != NULL )
            {
                *peMedium = (MEDIUM)Misc.eMedium;
            }

            if ( pcChannelNumber != NULL )
            {
                *pcChannelNumber = Misc.u8ChannelNumber;
            }

            return;
        }
    }

    wPLL = msAPI_ATV_GetProgramPLLData(u8ProgramNumber);

    if ( peMedium != NULL )
    {
        *peMedium = msAPI_CFT_GetMedium(wPLL);
    }

    if ( pcChannelNumber != NULL )
    {
        *pcChannelNumber = msAPI_CFT_GetChannelNumber(wPLL);
    }
}

//------------------------------------------------------------------------------
/// -This function will get Medium and Channel Number
/// @param cProgramNumber \b IN: Program number
/// @param eMedium \b IN: Medium type
/// -@see MEDIUM
/// @param cChannelNumber \b IN: Channel number
//------------------------------------------------------------------------------
void msAPI_ATV_SetMediumAndChannelNumber(BYTE u8ProgramNumber, MEDIUM eMedium, BYTE cChannelNumber)
{
    ATV_MISC Misc;
    WORD wPLL;

    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        return;
    }

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( TRUE == msAPI_CFT_IsValidMediumAndChannel(eMedium, cChannelNumber) )
        {
            Misc.eMedium = eMedium;
            Misc.u8ChannelNumber = cChannelNumber;
        }
        else
        {
            wPLL = msAPI_ATV_GetProgramPLLData(u8ProgramNumber);

            Misc.eMedium = msAPI_CFT_GetMedium(wPLL);;
            Misc.u8ChannelNumber = msAPI_CFT_GetChannelNumber(wPLL);
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}

//------------------------------------------------------------------------------
/// -This function will get Station name
/// @param cProgramNumber \b IN: Program number
/// @param *sName \b IN: pointer to station name for return
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetStationName(BYTE u8ProgramNumber, BYTE *sName)
{
    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    if ( TRUE == _GetPRTable(u8ProgramNumber, sName, PRDATA_NAME_PARAM) )
    {
        return TRUE;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will check if AFT is needed
/// @param cProgramNumber \b IN: Program number
/// @return BOOLEAN: needed or not
/// - TRUE: Yes
/// - FALSE: NO
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsAFTNeeded(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;
    memset(&Misc,0,sizeof(ATV_MISC));

    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        return TRUE;
    }

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( Misc.bAFT == FALSE )
        {
            return FALSE;
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will sort program
/// @param cStart \b IN: start program
/// @param cStop \b IN: stop
//------------------------------------------------------------------------------
void msAPI_ATV_SortProgram(BYTE u8Start, BYTE u8Stop)
{
    BYTE i = 0;
    BYTE j = 0;
    BYTE u8MinValue = 0;
    BYTE u8MinIndex = 0;
    BYTE u8Value = 0;

    if ( IS_CH_NAME_ENABLED == FALSE )
    {
        return;
    }

    if ( u8Start >= u8Stop || u8Stop >= _MAX_ATVPROGRAM )
    {
        return;
    }

    for ( i = u8Start; i < u8Stop; i++ )
    {
        u8MinIndex = i;

        if(TRUE == _GetPRTable(i, &u8MinValue, PRDATA_SORT_PARAM))
        {
            for ( j = i+1; j <= u8Stop; j++ )
            {
                if(TRUE == _GetPRTable(j, &u8Value, PRDATA_SORT_PARAM))
                {
                    if ( u8MinValue > u8Value )
                    {
                        u8MinValue = u8Value;
                        u8MinIndex = j;
                    }
                }
            }
        }

        if ( i != u8MinIndex )
        {
            _MovePRTable(u8MinIndex, i);
        }
    }
}


//------------------------------------------------------------------------------
/// -This function will copy program
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _CopyPRTable(BYTE u8Index);

BOOLEAN msAPI_ATV_CopyProgram(void)
{
    if ( TRUE == _CopyPRTable(_u8CurrentProgramNumber) )
    {
        return TRUE;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will check if the program number is active or not
/// @param cProgramNumber \b IN: Program number
/// @return BOOLEAN: Active or not
/// - TRUE: Active
/// - FALSE: Not active
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgramNumberActive(BYTE u8ProgramNumber)
{
    BYTE u8PRIndex;

    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    u8PRIndex = _GetPRIndexTable(u8ProgramNumber);

    return _IsPREntityActive(u8PRIndex);
}

//------------------------------------------------------------------------------
/// -This function will check if the program number is Empty or not
/// @return BOOLEAN: Active or not
/// - TRUE: Empty
/// - FALSE: Not Empty
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgramEmpty(void)
{
    int i;

    for ( i = 0; i < _MAX_PRTABLEMAP; i++ )
    {
        if ( _u8PRTableMap[i] != 0 )
        {
            return FALSE;
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will get first program number
/// @param bIncludeSkipped \b IN: include skipped program or not
/// - TRUE: include
/// - FALSE: don't include
/// @return BYTE: The first program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetFirstProgramNumber(BOOLEAN bIncludeSkipped)
{
    BYTE u8ProgramNumber;

  #if 0
    bIncludeSkipped = FALSE;
  #else // Modified by coverity_0476
    UNUSED(bIncludeSkipped);
  #endif

    for (u8ProgramNumber = ATV_FIRST_PR_NUM; u8ProgramNumber < _MAX_ATVPROGRAM; u8ProgramNumber++)
    {
        if ( TRUE == _IsIndexActive(u8ProgramNumber) )
        {
            break;
        }
    }

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get active program count
/// @return BYTE: active program count
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetActiveProgramCount(void)
{
    BYTE count;
    int i;

    count = 0;

    for ( i = ATV_FIRST_PR_NUM; i < _MAX_ATVPROGRAM; i++ )
    {
        if ( _IsIndexActive(i) )
        {
            ++count;
        }
    }

    return count;
}

//------------------------------------------------------------------------------
/// -This function will convert program number to ordinal number
/// @return BYTE: ordinal number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_ConvertProgramNumberToOrdinalNumber(BYTE u8ProgramNumber)
{
    BYTE i;
    BYTE u8OrdinalNumber = 0;

    if (u8ProgramNumber < _MAX_ATVPROGRAM)
    {
        for ( i = ATV_FIRST_PR_NUM; i <= u8ProgramNumber; i++ )
        {
            if ( _IsIndexActive(i) )
            {
                ++u8OrdinalNumber;
            }
        }
    }

    if(u8OrdinalNumber > 0)
        u8OrdinalNumber--;

    //printf("u8ProgramNumber %bu => u8OrdinalNumber %bu\n", u8ProgramNumber, u8OrdinalNumber);

    return u8OrdinalNumber;
}

//------------------------------------------------------------------------------
/// -This function will get first favorite Program
/// @return BYTE: First Favorite Program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetFirstFavoriteProgramNumber(void)
{
    BYTE u8ProgramNumber;

    for (u8ProgramNumber = ATV_FIRST_PR_NUM; u8ProgramNumber < _MAX_ATVPROGRAM; u8ProgramNumber++)
    {
        if ( TRUE == _IsIndexActive(u8ProgramNumber) &&
             TRUE == msAPI_ATV_IsProgramFavorite(u8ProgramNumber) )
        {
            break;
        }
    }

    return u8ProgramNumber;
}


//------------------------------------------------------------------------------
/// -This function will get Previous favorite Program
/// @param cBaseProgramNumber \b IN: Base program number
/// @return BYTE: Previous Favorite Program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetPreviousFavoriteProgramNumber(BYTE u8BaseProgramNumber)
{
    BYTE u8ProgramNumber;

    u8ProgramNumber = u8BaseProgramNumber;

    do
    {
        u8ProgramNumber--;

        if (u8ProgramNumber <= ATV_FIRST_PR_NUM)
        {
            u8ProgramNumber = _MAX_ATVPROGRAM -1;
        }

        if ( TRUE == _IsIndexActive(u8ProgramNumber) &&
             TRUE == msAPI_ATV_IsProgramFavorite(u8ProgramNumber) )
        {
            break;
        }
    } while ( u8ProgramNumber != u8BaseProgramNumber );

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get next favorite Program
/// @param cBaseProgramNumber \b IN: Base program number
/// @return BYTE: Next Favorite Program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetNextFavoriteProgramNumber(BYTE u8BaseProgramNumber)
{
    BYTE u8ProgramNumber;

    u8ProgramNumber = u8BaseProgramNumber;

    do
    {
        u8ProgramNumber++;

        if (u8ProgramNumber >= _MAX_ATVPROGRAM)
        {
            u8ProgramNumber = ATV_FIRST_PR_NUM;
        }

        if ( TRUE == _IsIndexActive(u8ProgramNumber) && TRUE == msAPI_ATV_IsProgramFavorite(u8ProgramNumber) )
        {
            break;
        }
    } while ( u8ProgramNumber != u8BaseProgramNumber );

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get total favorite Program numbers
/// @return BYTE: Total Program numbers
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetTotalFavoriteProgramCount(void)
{
    BYTE u8FavoriteProgramCount = 0;
    BYTE u8ProgramNumber;

    for ( u8ProgramNumber = ATV_FIRST_PR_NUM; u8ProgramNumber < _MAX_ATVPROGRAM; u8ProgramNumber++ )
    {
        if ( TRUE == _IsIndexActive(u8ProgramNumber) && TRUE == msAPI_ATV_IsProgramFavorite(u8ProgramNumber) )
        {
            u8FavoriteProgramCount++;
        }
    }

    return u8FavoriteProgramCount;
}

//------------------------------------------------------------------------------
/// -This function will convert ordinal number to program number
/// @return BYTE: program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_ConvertOrdinalNumberToProgramNumber(WORD u16OrdinalNumber)
{
    BYTE i;
    BYTE u8ProgramNumber = 0;

    if (u16OrdinalNumber < _MAX_ATVPROGRAM)
    {
        for ( i = ATV_FIRST_PR_NUM; i < _MAX_ATVPROGRAM; i++ )
        {
            if ( _IsIndexActive(i) )
            {
                if(u16OrdinalNumber == u8ProgramNumber)
                {
                    u8ProgramNumber = i;
                    break;
                }

                ++u8ProgramNumber;
            }
        }
    }

    //printf("u16OrdinalNumber %bu => u8ProgramNumber %bu\n", u16OrdinalNumber, u8ProgramNumber);

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will set Current Program number
/// @param cProgramNumber \b IN: Current program number
//------------------------------------------------------------------------------
void msAPI_ATV_SetCurrentProgramNumber(BYTE u8ProgramNumber)
{
    if ( u8ProgramNumber < _MAX_ATVPROGRAM )
    {
        _u8PastProgramNumber = _u8CurrentProgramNumber;

        _u8CurrentProgramNumber = u8ProgramNumber;

        _SaveProgramNumber(_u8CurrentProgramNumber);
    }
}

//------------------------------------------------------------------------------
/// -This function will get Next Program number
/// @param cBaseProgramNumber \b IN: base program number
/// @param bIncludeSkipped \b IN: Include skpped program or not
/// - TURE: Include
/// - FALSE: Don't include skipped program
/// @return BYTE: Next program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetNextProgramNumber(BYTE u8BaseProgramNumber, BOOLEAN bIncludeSkipped)
{
    BYTE u8ProgramNumber;

  #if 0
    bIncludeSkipped = FALSE;
  #else // Modified by coverity_0474
    UNUSED(bIncludeSkipped);
  #endif

    //u8ProgramNumber = _u8CurrentProgramNumber;
    u8ProgramNumber = u8BaseProgramNumber;

    do
    {
        u8ProgramNumber++;

        if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
        {
            u8ProgramNumber = ATV_FIRST_PR_NUM;
        }

        if ( TRUE == _IsIndexActive(u8ProgramNumber) && FALSE == msAPI_ATV_IsProgramSkipped(u8ProgramNumber) )
        {
            break;
        }
    } while ( u8ProgramNumber != _u8CurrentProgramNumber );

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get Previous Program number
/// @param cBaseProgramNumber \b IN: base program number
/// @param bIncludeSkipped \b IN: Include skpped program or not
/// - TURE: Include
/// - FALSE: Don't include skipped program
/// @return BYTE: Previous program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetPrevProgramNumber(BYTE u8BaseProgramNumber, BOOLEAN bIncludeSkipped)
{
    BYTE u8ProgramNumber;

  #if 0
    bIncludeSkipped = FALSE;
  #else // Modified by coverity_0476
    UNUSED(bIncludeSkipped);
  #endif

    //u8ProgramNumber = _u8CurrentProgramNumber;
    u8ProgramNumber = u8BaseProgramNumber;

    do
    {
        if (u8ProgramNumber == ATV_FIRST_PR_NUM)
        {
            u8ProgramNumber = _MAX_ATVPROGRAM;
        }

        u8ProgramNumber--;

        if ( TRUE == _IsIndexActive(u8ProgramNumber) && FALSE == msAPI_ATV_IsProgramSkipped(u8ProgramNumber) )
        {
            break;
        }
    } while ( u8ProgramNumber != _u8CurrentProgramNumber );

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get Program PLL data
/// @param cProgramNumber \b IN: program number
/// @return WORD: PLL Data
//------------------------------------------------------------------------------
WORD msAPI_ATV_GetProgramPLLData(BYTE u8ProgramNumber)
{
    WORD wPLL = 0;

    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        return DEFAULT_PLL;
    }

    if(TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&wPLL, PRDATA_PLL_PARAM))
        return wPLL;

    return DEFAULT_PLL;
}

//------------------------------------------------------------------------------
/// -This function will set Program PLL data
/// @param cProgramNumber \b IN: program number
/// @param wPLL: PLL Data
//------------------------------------------------------------------------------
void msAPI_ATV_SetProgramPLLData(BYTE u8ProgramNumber, WORD wPLL)
{
    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        return;
    }

    if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&wPLL, PRDATA_PLL_PARAM))
    {
        __ASSERT(0);
    }
}

//------------------------------------------------------------------------------
/// -This function will increase current Program number
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IncCurrentProgramNumber(void)
{
    if ( _u8CurrentProgramNumber >= (_MAX_ATVPROGRAM - 1) )
    {
        return FALSE;
    }

    _u8PastProgramNumber = _u8CurrentProgramNumber;

    _u8CurrentProgramNumber++;

    _SaveProgramNumber(_u8CurrentProgramNumber);

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will Correct Duplication
//------------------------------------------------------------------------------
static void _CorrectDuplication(void)
{
    BYTE u8DuplicationMap[MAX_CATV_PRTABLEMAP];
    BYTE i;
    BYTE u8PRIndex;

    for ( i = 0; i < MAX_CATV_PRTABLEMAP; i++ )
    {
        u8DuplicationMap[i] = 0x00;
    }

    for ( i = 0; i < _MAX_ATVPROGRAM; i++ )
    {
        u8PRIndex = _GetPRIndexTable(i);

        if ( u8PRIndex >= _MAX_ATVPROGRAM )
        {
            continue;
        }

        if ( (u8DuplicationMap[u8PRIndex/8] & (0x01 << (u8PRIndex%8))) == TRUE )
        {
            _SetPRIndexTable(i, PR_NOTHING);

            ATV_MSG("ATV: Channel Duplication", 0);
        }
        else
        {
            u8DuplicationMap[u8PRIndex/8] =  u8DuplicationMap[u8PRIndex/8] | (0x01 << (u8PRIndex%8));
        }
    }
}

//------------------------------------------------------------------------------
/// -This function will Correct Mappin
//------------------------------------------------------------------------------
static void _CorrectMapping(void)
{
    BYTE u8PRIndex;
    BYTE i;
    BYTE u8IndexCount;
    BYTE u8MapCount;

    u8IndexCount = 0;

    for ( i = 0; i < _MAX_ATVPROGRAM; i++ )
    {
        u8PRIndex = _GetPRIndexTable(i);

        if ( u8PRIndex >= _MAX_ATVPROGRAM )
        {
            continue;
        }

        u8IndexCount++;

        if ( _IsPREntityActive(u8PRIndex) == FALSE )
        {
            _SetPRIndexTable(i, PR_NOTHING);

            u8IndexCount--;

            ATV_MSG("ATV: Mapping error", 0);
        }
    }

    u8MapCount = 0;

    for ( i = 0; i < _MAX_ATVPROGRAM; i++ )
    {
        if ( _IsPREntityActive(i) == TRUE )
        {
            u8MapCount++;
        }
    }

    if ( u8MapCount != u8IndexCount )
    {
        ATV_MSG("ATV: Count is different", 0);

        for ( i = 0; i < _MAX_ATVPROGRAM; i++ )
        {
            _ActivePREntity(i, FALSE);
        }

        for ( i = 0; i < _MAX_ATVPROGRAM; i++ )
        {
            u8PRIndex = _GetPRIndexTable(i);

            if ( u8PRIndex >= _MAX_ATVPROGRAM )
            {
                continue;
            }

            _ActivePREntity(u8PRIndex, TRUE);
        }
    }
}

//------------------------------------------------------------------------------
/// -This function will Get Program Table
/// @param u8Index \b IN: Index
/// @param pu8Buffer \b IN: pointer to Buffer
/// @param u8Param \b IN: pointer to Parameter
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _GetPRTable(BYTE u8Index, BYTE * pu8Buffer, BYTE u8Param)
{
    ATVPROGRAMDATA AtvProgramData;
    ATV_MISC AtvMisc;
    WORD wPLL;
    BYTE u8PRIndex,u8Sort;
    BOOLEAN b_IsPREntityActive;
    S8 s8FineTune;

    if ( u8Index >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    // Added by coverity_0217
    memset(&AtvProgramData, 0, sizeof(ATVPROGRAMDATA));

    u8PRIndex = _GetPRIndexTable(u8Index);

    b_IsPREntityActive = _IsPREntityActive(u8PRIndex);

    switch ( u8Param )
    {
    case PRDATA_ALL_PARAM:
        if ( b_IsPREntityActive == TRUE )
        {
            _GetNVRAM(_u32PRTableAddr+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)),
                    pu8Buffer, sizeof(ATVPROGRAMDATA));
        }
        else
        {
                AtvProgramData.wPLL = DEFAULT_PLL;
                AtvProgramData.Misc.eAudioStandard = DEFAULT_AUDIOSTANDARD;
                AtvProgramData.Misc.bSkip = DEFAULT_SKIP_VALUE;
                AtvProgramData.Misc.bAFT = DEFAULT_AFT_VALUE;
                AtvProgramData.Misc.eVideoStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
                AtvProgramData.Misc.eAudioMode = DEFAULT_TV_AUDIOMODE;
                AtvProgramData.Misc.bWasDualAudioSelected = DEFAULT_DUAL_AUDIO_SELECTION;
                AtvProgramData.Misc.bIsFavorite = DEFAULT_FAVORITE_VALUE;
                AtvProgramData.Misc.eMedium = DEFAULT_MEDIUM;
                AtvProgramData.Misc.bIsLock = DEFAULT_LOCK_VALUE;
                AtvProgramData.Misc.u8ChannelNumber = DEFAULT_CHANNELNUMBER;
                AtvMisc.eVideoStandard_User = DEFAULT_USER_VIDEOSTANDARD_OF_PROGRAM;
                AtvProgramData.s8FineTune = DEFAULT_FINETUNE;
                _StringCopy(AtvProgramData.sName, sNullStationName, MAX_STATION_NAME);
        // NTSC
                AtvProgramData.Misc.bIsSearched = DEFAULT_SEARCHED_VALUE;
                AtvProgramData.Misc.bIsAutoColorSystem=DEFAULT_IS_AUTO_COLOR_SYSTEM;

            #if ENABLE_TTX
                _SetListPageNumber(AtvProgramData.u8ListPage, 0, DEFAULT_LISTPAGE[0]);
                _SetListPageNumber(AtvProgramData.u8ListPage, 1, DEFAULT_LISTPAGE[1]);
                _SetListPageNumber(AtvProgramData.u8ListPage, 2, DEFAULT_LISTPAGE[2]);
                _SetListPageNumber(AtvProgramData.u8ListPage, 3, DEFAULT_LISTPAGE[3]);
            #endif
            memcpy(pu8Buffer,&AtvProgramData,sizeof(ATVPROGRAMDATA));
        }
        return TRUE;

    case PRDATA_PLL_PARAM:
        if (b_IsPREntityActive == TRUE)
        {
            _GetNVRAM(_u32PRTableAddr+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, wPLL)),
                    pu8Buffer, sizeof(WORD));
        }
        else
        {
                wPLL = DEFAULT_PLL;
                memcpy(pu8Buffer,&wPLL,sizeof(WORD));
        }

        return TRUE;

    case PRDATA_MISC_PARAM:
        if (b_IsPREntityActive == TRUE)
        {
            _GetNVRAM(_u32PRTableAddr+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, Misc)),
                    pu8Buffer, sizeof(ATV_MISC));
        }
        else
        {
                AtvMisc.eAudioStandard = DEFAULT_AUDIOSTANDARD;
                AtvMisc.bSkip = DEFAULT_SKIP_VALUE;
                AtvMisc.bAFT = DEFAULT_AFT_VALUE;
                AtvMisc.eVideoStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
                AtvMisc.eVideoStandard_User = DEFAULT_USER_VIDEOSTANDARD_OF_PROGRAM;
                AtvMisc.eAudioMode = DEFAULT_TV_AUDIOMODE;
                AtvMisc.bWasDualAudioSelected = DEFAULT_DUAL_AUDIO_SELECTION;
                AtvMisc.bIsFavorite = DEFAULT_FAVORITE_VALUE;
                AtvMisc.eMedium = DEFAULT_MEDIUM;
                AtvMisc.bIsLock = DEFAULT_LOCK_VALUE;
                AtvMisc.u8ChannelNumber = DEFAULT_CHANNELNUMBER;
        // NTSC
                AtvMisc.bIsSearched = DEFAULT_SEARCHED_VALUE;
                AtvMisc.bIsAutoColorSystem=DEFAULT_IS_AUTO_COLOR_SYSTEM;
                memcpy(pu8Buffer,&AtvMisc,sizeof(ATV_MISC));
        }

        return TRUE;

    case PRDATA_FINETUNE_PARAM:
        if (b_IsPREntityActive == TRUE)
        {
            _GetNVRAM(_u32PRTableAddr+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, s8FineTune)),
                    pu8Buffer, sizeof(BYTE));
        }
        else
        {
                s8FineTune = (BYTE)DEFAULT_FINETUNE;
                memcpy(pu8Buffer,&s8FineTune,sizeof(S8));
        }
        return TRUE;

    case PRDATA_SORT_PARAM:
        if (b_IsPREntityActive == TRUE)
        {
            _GetNVRAM(_u32PRTableAddr+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, u8Sort)),
                    pu8Buffer, sizeof(BYTE));
        }
        else
        {
                u8Sort = (BYTE)LOWEST_SORTING_PRIORITY;
                memcpy(pu8Buffer,&u8Sort,sizeof(BYTE));
        }
        return TRUE;

    case PRDATA_NAME_PARAM:
        if (b_IsPREntityActive == TRUE)
        {
            _GetNVRAM(_u32PRTableAddr+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, sName)),
                    pu8Buffer, sizeof(BYTE)*MAX_STATION_NAME);
        }
        else
        {
            _StringCopy(pu8Buffer, sNullStationName, MAX_STATION_NAME);
        }
        return TRUE;

    #if ENABLE_TTX
    case PRDATA_LIST_PARAM:
        if (b_IsPREntityActive == TRUE)
        {
            _GetNVRAM(_u32PRTableAddr+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, u8ListPage)),
                    pu8Buffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
        }
        else
        {
            _SetListPageNumber(pu8Buffer, 0, DEFAULT_LISTPAGE[0]);
            _SetListPageNumber(pu8Buffer, 1, DEFAULT_LISTPAGE[1]);
            _SetListPageNumber(pu8Buffer, 2, DEFAULT_LISTPAGE[2]);
            _SetListPageNumber(pu8Buffer, 3, DEFAULT_LISTPAGE[3]);
        }
        return TRUE;
    #endif
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will Set Program Table
/// @param u8Index \b IN: Index
/// @param pu8Buffer \b IN: pointer to Buffer
/// @param u8Param \b IN: pointer to Parameter
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _SetPRTable(BYTE u8Index, BYTE * pu8Buffer, BYTE u8Param)
{
    BYTE u8PRIndex;
    BYTE u8NewPREntity;

    //printf("_SetPRTable(u8Index=%u, u8Param=0x%X)\n", u8Index, u8Param);

    if ( u8Index >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    u8PRIndex = _GetPRIndexTable(u8Index);

    if ( TRUE != _IsPREntityActive(u8PRIndex) )
    {
        u8NewPREntity = _GetEmptyPREntity();

        if (u8NewPREntity >= _MAX_ATVPROGRAM || u8NewPREntity == PR_NOTHING)
        {
            _CorrectDuplication();

            _CorrectMapping();

            u8NewPREntity = _GetEmptyPREntity();

            if ( u8NewPREntity >= _MAX_ATVPROGRAM || u8NewPREntity == PR_NOTHING )
            {
                ATV_MSG("ATV: FATAL ERROR", 0);
                return FALSE;
            }
        }

        _FillPREntityWithDefault(u8NewPREntity);

        u8PRIndex = u8NewPREntity;

        _SetPRIndexTable(u8Index, u8PRIndex);

        _ActivePREntity(u8PRIndex, TRUE);
    }

    switch ( u8Param )
    {
    case PRDATA_PLL_PARAM:
        _SetNVRAM(_u32PRTableAddr+
                (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, wPLL)),
                pu8Buffer, sizeof(WORD));

        return TRUE;

    case PRDATA_MISC_PARAM:

        // Check if data changed
        /*{
            ATV_MISC tmpAtvMisc;

            //printf("sizeof(ATV_MISC)=%u\n", sizeof(ATV_MISC));
            _GetNVRAM(_u32PRTableAddr+
                (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, Misc)),
                (U8*)&tmpAtvMisc, sizeof(ATV_MISC));
            if( strncmp( (const char *)&tmpAtvMisc, (const char *)pu8Buffer, sizeof(ATV_MISC)) == 0 )
            {
                printf("Skip save misc\n");
                break;
            }
        }*/

        //printf(" save misc\n");
        _SetNVRAM(_u32PRTableAddr+
                (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, Misc)),
                pu8Buffer, sizeof(ATV_MISC));

        return TRUE;

    case PRDATA_FINETUNE_PARAM:
        _SetNVRAM(_u32PRTableAddr+
                (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, s8FineTune)),
                pu8Buffer, sizeof(BYTE));

        return TRUE;

    case PRDATA_SORT_PARAM:
        _SetNVRAM(_u32PRTableAddr+
                (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, u8Sort)),
                pu8Buffer, sizeof(BYTE));

        return TRUE;

    case PRDATA_NAME_PARAM:
        _SetNVRAM(_u32PRTableAddr+
                (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, sName)),
                pu8Buffer, sizeof(BYTE)*MAX_STATION_NAME);

        return TRUE;

    #if ENABLE_TTX
    case PRDATA_LIST_PARAM:
        _SetNVRAM(_u32PRTableAddr+
                (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, u8ListPage)),
                pu8Buffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
        return TRUE;
    #endif

    case PRDATA_ALL_PARAM:
        _SetNVRAM(_u32PRTableAddr+
                (u8PRIndex*sizeof(ATVPROGRAMDATA)),
                pu8Buffer, sizeof(ATVPROGRAMDATA));

        return TRUE;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will Copy Program Table
/// @param u8Index \b IN: Index
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _CopyPRTable(BYTE u8Index)
{
    BYTE u8PRIndex;
    BYTE i;
    ATVPROGRAMDATA prData;

    if ( u8Index >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    if ( u8Index == (_MAX_ATVPROGRAM-1) )
    {
        return TRUE;
    }

    u8PRIndex = _GetPRIndexTable((_MAX_ATVPROGRAM-1));

    if ( TRUE == _IsPREntityActive(u8PRIndex) )
    {
        _ActivePREntity(u8PRIndex, FALSE);
    }

    for ( i = (_MAX_ATVPROGRAM-1); i > u8Index; i-- )
    {
        u8PRIndex = _GetPRIndexTable(i-1);

        _SetPRIndexTable(i, u8PRIndex);
    }

    _SetPRIndexTable(u8Index+1, PR_NOTHING);

    if(TRUE != _GetPRTable(u8Index, (BYTE *)(&prData), PRDATA_ALL_PARAM))
        return FALSE;

    if(TRUE != _SetPRTable(u8Index+1, (BYTE *)(&prData), PRDATA_ALL_PARAM))
        return FALSE;

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will Delate Program Table
/// @param u8Index \b IN: Index
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _DeletePRTable(BYTE u8Index)
{
    BYTE u8PRIndex;
    BYTE i;

    if ( u8Index >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    u8PRIndex = _GetPRIndexTable(u8Index);

    if ( TRUE == _IsPREntityActive(u8PRIndex) )
    {
        _ActivePREntity(u8PRIndex, FALSE);
    }

    for ( i = u8Index; i < _MAX_ATVPROGRAM-1; i++ )
    {
        u8PRIndex = _GetPRIndexTable(i+1);

        _SetPRIndexTable(i, u8PRIndex);
    }
    _SetPRIndexTable(_MAX_ATVPROGRAM-1, PR_NOTHING);

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will Move Program Table
/// @param u8From \b IN: From
/// @param u8To \b IN: To
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _MovePRTable(BYTE u8From, BYTE u8To)
{
    BYTE u8PRIndex;
    BYTE u8TempPRIndex;
    BYTE i;

    if ( u8From >= _MAX_ATVPROGRAM || u8To >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    if ( u8From == u8To )
    {
        return TRUE;
    }

    if ( u8From > u8To )
    {
        u8TempPRIndex = _GetPRIndexTable(u8From);

        for ( i = u8From; i > u8To; i-- )
        {
            u8PRIndex = _GetPRIndexTable(i-1);

            _SetPRIndexTable(i, u8PRIndex);
        }

        _SetPRIndexTable(u8To, u8TempPRIndex);
    }
    else
    {
        u8TempPRIndex = _GetPRIndexTable(u8From);

        for ( i = u8From; i < u8To; i++ )
        {
            u8PRIndex = _GetPRIndexTable(i+1);

            _SetPRIndexTable(i, u8PRIndex);
        }

        _SetPRIndexTable(u8To, u8TempPRIndex);
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will Awap Program Table
/// @param u8Index1 \b IN: Index1
/// @param u8Index2 \b IN: Index2
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _SwapPRTable(BYTE u8Index1, BYTE u8Index2)
{
    BYTE u8PRIndex;
    BYTE u8TempPRIndex;

    if ( u8Index1 >= _MAX_ATVPROGRAM || u8Index2 >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    if ( u8Index1 == u8Index2 )
    {
        return TRUE;
    }

    u8TempPRIndex = _GetPRIndexTable(u8Index1);
    u8PRIndex = _GetPRIndexTable(u8Index2);
    _SetPRIndexTable(u8Index1, u8PRIndex);
    _SetPRIndexTable(u8Index2, u8TempPRIndex);

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will Get Program index Table
/// @param u8Index \b IN: Index
/// @return BYTE: Program Index
//------------------------------------------------------------------------------
static BYTE _GetPRIndexTable(BYTE u8Index)
{
    BYTE u8PRIndex;

    if ( u8Index >= _MAX_ATVPROGRAM )
    {
        return PR_INVALID_INDEX;
    }

    u8PRIndex = _u8ATVPRIndexTable[u8Index];

    return u8PRIndex;
}

//------------------------------------------------------------------------------
/// -This function will Set Program index Table
/// @param u8Index \b IN: Index
/// @param u8PRIndex \b IN: Program Index
//------------------------------------------------------------------------------
static void _SetPRIndexTable(BYTE u8Index, BYTE u8PRIndex)
{
    if ( u8Index >= _MAX_ATVPROGRAM )
    {
        return;
    }

    _u8ATVPRIndexTable[u8Index] = u8PRIndex;

    _SetNVRAM(_u32ATVPRIndexTableAddr+u8Index, &u8PRIndex, sizeof(u8PRIndex));
}

//------------------------------------------------------------------------------
/// -This function will check program Entity Active or not
/// @param u8PRIndex \b IN: Program Index
/// @return BOOLEAN: Active or not
/// - TRUE: Active
/// - FALSE: Not Active
//------------------------------------------------------------------------------
static BOOLEAN _IsPREntityActive(BYTE u8PRIndex)
{
    if ( u8PRIndex >= _MAX_ATVPROGRAM )
    {
        return FALSE;
    }

    return ( (_u8PRTableMap[u8PRIndex/8] & (0x01 << (u8PRIndex%8))) ? TRUE : FALSE );
}

//------------------------------------------------------------------------------
/// -This function will Active program Entity
/// @param u8PRIndex \b IN: Program Index
/// @param bActive \b IN: Active or not
//------------------------------------------------------------------------------
static void _ActivePREntity(BYTE u8PRIndex, BOOLEAN bActive)
{
    BYTE u8Temp;

    if ( u8PRIndex >= _MAX_ATVPROGRAM )
    {
        return;
    }

    u8Temp = u8PRIndex/8;

    if ( TRUE == bActive )
    {
        _u8PRTableMap[u8Temp] =  _u8PRTableMap[u8Temp] | (0x01 << (u8PRIndex%8));
    }
    else
    {
        _u8PRTableMap[u8Temp] =  _u8PRTableMap[u8Temp] & ~(0x01 << (u8PRIndex%8));
    }

    _SetNVRAM(_u32PRTableMapAddr+u8Temp, &(_u8PRTableMap[u8Temp]), sizeof(BYTE));
}

//------------------------------------------------------------------------------
/// -This function will check index Active or not
/// @param u8Index \b IN: Index
/// @return BOOLEAN: Active or not
/// - TRUE: Active
/// - FALSE: Not Active
//------------------------------------------------------------------------------
static BOOLEAN _IsIndexActive(BYTE u8Index)
{
#if ENABLE_SBTVD_ATV_SYSTEM
    if(IS_SBTVD_APP && msAPI_ATV_GetDirectTuneFlag() == FALSE)
    {
        if(msAPI_ATV_IsProgramSearched(u8Index) == FALSE)
            return FALSE;
    }
#endif
    BYTE u8PRIndex = _GetPRIndexTable(u8Index);

    return _IsPREntityActive(u8PRIndex);
}

//------------------------------------------------------------------------------
/// -This function will get Empty Program Entity
/// @param u8Index \b IN: Index
/// @return BYTE: progrm index
//------------------------------------------------------------------------------
static BYTE _GetEmptyPREntity(void)
{
    BYTE i;

    for ( i = 0; i < _MAX_ATVPROGRAM; i++ )
    {
        if ( FALSE == _IsPREntityActive(i) )
        {
            return i;
        }
    }

    return PR_NOTHING;
}

//------------------------------------------------------------------------------
/// -This function will Fill Program Entity With Default
/// @param u8PRIndex \b IN: Program Index
//------------------------------------------------------------------------------
static void _FillPREntityWithDefault(BYTE u8PRIndex)
{
    ATVPROGRAMDATA PRData;

    // Added by coverity_0504
    memset(&PRData, 0, sizeof(ATVPROGRAMDATA));

#if ENABLE_SBTVD_ATV_SYSTEM
    PRData.wPLL = IS_SBTVD_APP ? msAPI_ATV_MapChanToFreq(u8PRIndex+1) : DEFAULT_PLL;
#else
    PRData.wPLL = DEFAULT_PLL;
#endif
    PRData.Misc.eAudioStandard = DEFAULT_AUDIOSTANDARD;
    PRData.Misc.bSkip = DEFAULT_SKIP_VALUE;
    PRData.Misc.bAFT = DEFAULT_AFT_VALUE;
    PRData.Misc.eVideoStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
    PRData.Misc.eVideoStandard_User = DEFAULT_USER_VIDEOSTANDARD_OF_PROGRAM;
    PRData.Misc.eAudioMode = DEFAULT_TV_AUDIOMODE;
    PRData.Misc.bWasDualAudioSelected = DEFAULT_DUAL_AUDIO_SELECTION;
    PRData.Misc.bIsFavorite = DEFAULT_FAVORITE_VALUE;
    PRData.Misc.eMedium = DEFAULT_MEDIUM;
    PRData.Misc.bIsLock = DEFAULT_LOCK_VALUE;
    PRData.Misc.u8ChannelNumber = DEFAULT_CHANNELNUMBER;
    PRData.s8FineTune = DEFAULT_FINETUNE;
// NTSC
    PRData.Misc.bIsSearched = DEFAULT_SEARCHED_VALUE;
    PRData.Misc.bIsAutoColorSystem=DEFAULT_IS_AUTO_COLOR_SYSTEM;

    _StringCopy(PRData.sName, sNullStationName, MAX_STATION_NAME);
    #if ENABLE_TTX
    _SetListPageNumber(PRData.u8ListPage, 0, DEFAULT_LISTPAGE[0]);
    _SetListPageNumber(PRData.u8ListPage, 1, DEFAULT_LISTPAGE[1]);
    _SetListPageNumber(PRData.u8ListPage, 2, DEFAULT_LISTPAGE[2]);
    _SetListPageNumber(PRData.u8ListPage, 3, DEFAULT_LISTPAGE[3]);
    #endif

    _SetNVRAM( _u32PRTableAddr+(u8PRIndex*sizeof(ATVPROGRAMDATA)),
               (BYTE *)(&PRData), sizeof(PRData) );
}

//------------------------------------------------------------------------------
/// -This function will load Program number
/// @return BYTE: Program number
//------------------------------------------------------------------------------
static BYTE _LoadProgramNumber(void)
{
    BYTE u8ProgramNumber;

#if ENABLE_SBTVD_ATV_SYSTEM
    if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
        u8ProgramNumber = stGenSetting.stTvSetting.u8ATVProgramNumber_CATV;
    else
#endif
        u8ProgramNumber = stGenSetting.stTvSetting.u8ATVProgramNumber;

    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        u8ProgramNumber = DEFAULT_LASTPROGRAM;

        _SaveProgramNumber(u8ProgramNumber);
    }

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will Save Program Number
/// @param u8ProgramNumber \b IN: Program Number
//------------------------------------------------------------------------------
static void _SaveProgramNumber(BYTE u8ProgramNumber)
{
    if ( u8ProgramNumber >= _MAX_ATVPROGRAM )
    {
        return;
    }

#if ENABLE_SBTVD_ATV_SYSTEM
    if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
        stGenSetting.stTvSetting.u8ATVProgramNumber_CATV = u8ProgramNumber;
    else
#endif
        stGenSetting.stTvSetting.u8ATVProgramNumber = u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get max channel
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetChannelMax(void)
{
    return _MAX_ATVPROGRAM;
}

//------------------------------------------------------------------------------
/// -This function will get min channel
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetChannelMin(void)
{
    return MIN_ATVPROGRAM;
}
#endif

#if( ENABLE_ATV_SYS_PICTURE_SETTING )
//------------------------------------------------------------------------------
/// -This function will Get Percent Of Picture Item
/// @param ePictureItem \b IN: Picture Item
/// -@see EN_PICTURE_QUALITY_ITEMS
/// @param eVideoSource \b IN: Video Source
/// -@see AVD_InputSourceType
/// @param pu8Percent \b IN: Percent
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _GetPercentOfPictureItem(EN_PICTURE_QUALITY_ITEMS ePictureItem, AVD_InputSourceType eVideoSource, BYTE *pu8Percent)
{
    DWORD u32Address;
    BYTE u8OffsetOf;
    BYTE u8Percent;
    BYTE i;

    switch ( eVideoSource )
    {
    case E_INPUT_SOURCE_ATV:
        u32Address = BASEADDRESS_PQ_ATV;
        break;

    case E_INPUT_SOURCE_CVBS1:
        u32Address = BASEADDRESS_PQ_CVBS1;
        break;

    case E_INPUT_SOURCE_CVBS2:
        u32Address = BASEADDRESS_PQ_CVBS2;
        break;

    case E_INPUT_SOURCE_SVIDEO1:
        u32Address = BASEADDRESS_PQ_SVIDEO1;
        break;

    case E_INPUT_SOURCE_SVIDEO2:
        u32Address = BASEADDRESS_PQ_SVIDEO2;
        break;

    case E_INPUT_SOURCE_SCART1:
        u32Address = BASEADDRESS_PQ_SCART1;
        break;

    case E_INPUT_SOURCE_SCART2:
        u32Address = BASEADDRESS_PQ_SCART2;
        break;

    default:
        *pu8Percent = 100;
        ATV_MSG("ATV: FATAL ERROR", 0);
        return FALSE;
    }

    switch ( ePictureItem )
    {
    case E_BRIGHTNESS:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Brightness);
        break;

    case E_CONTRAST:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Contrast);
        break;

    case E_COLOR:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Color);
        break;

    case E_HUE:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Hue);
        break;

    case E_SHARPNESS:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Sharpness);
        break;

    default:
        *pu8Percent = 100;
        ATV_MSG("ATV: FATAL ERROR", 0);
        return FALSE;
    }

    _GetNVRAM(u32Address + u8OffsetOf, &u8Percent, sizeof(BYTE));

    if ( u8Percent <= 100 )
    {
        *pu8Percent = u8Percent;
    }
    else
    {
        for ( i = 0; i < (sizeof(m_PictureQualityItemsDefault)/sizeof(m_PictureQualityItemsDefault[0])); i++ )
        {
            if ( eVideoSource == m_PictureQualityItemsDefault[i].eVideoSource )
            {
                *pu8Percent = *(((BYTE *)&(m_PictureQualityItemsDefault[i].PictureQualityItems))+u8OffsetOf);
                break;
            }
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will Set Percent Of Picture Item
/// @param ePictureItem \b IN: Picture Item
/// -@see EN_PICTURE_QUALITY_ITEMS
/// @param eVideoSource \b IN: Video Source
/// -@see AVD_InputSourceType
/// @param pu8Percent \b IN: Percent
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _SetPercentOfPictureItem(EN_PICTURE_QUALITY_ITEMS ePictureItem, AVD_InputSourceType eVideoSource, BYTE u8Percent)
{
    DWORD u32Address;
    BYTE u8OffsetOf;

    switch ( eVideoSource )
    {
    case E_INPUT_SOURCE_ATV:
        u32Address = BASEADDRESS_PQ_ATV;
        break;

    case E_INPUT_SOURCE_CVBS1:
        u32Address = BASEADDRESS_PQ_CVBS1;
        break;

    case E_INPUT_SOURCE_CVBS2:
        u32Address = BASEADDRESS_PQ_CVBS2;
        break;

    case E_INPUT_SOURCE_SVIDEO1:
        u32Address = BASEADDRESS_PQ_SVIDEO1;
        break;

    case E_INPUT_SOURCE_SVIDEO2:
        u32Address = BASEADDRESS_PQ_SVIDEO2;
        break;

    case E_INPUT_SOURCE_SCART1:
        u32Address = BASEADDRESS_PQ_SCART1;
        break;

    case E_INPUT_SOURCE_SCART2:
        u32Address = BASEADDRESS_PQ_SCART2;
        break;

    default:
        ATV_MSG("ATV: FATAL ERROR", 0);
        return FALSE;
    }

    switch ( ePictureItem )
    {
    case E_BRIGHTNESS:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Brightness);
        break;

    case E_CONTRAST:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Contrast);
        break;

    case E_COLOR:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Color);
        break;

    case E_HUE:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Hue);
        break;

    case E_SHARPNESS:
        u8OffsetOf = offsetof(PICTURE_QUALITY_ITEMS, u8Sharpness);
        break;

    default:
        ATV_MSG("ATV: FATAL ERROR", 0);
        return FALSE;
    }

    if ( 100 < u8Percent )
    {
        ATV_MSG("ATV: FATAL ERROR", 0);
        return FALSE;
    }

    _SetNVRAM(u32Address + u8OffsetOf, &u8Percent, sizeof(BYTE));

    return TRUE;
}
#endif

#if ENABLE_TTX
//------------------------------------------------------------------------------
/// -This function will Get List Page Number
/// @param pu8Buffer \b IN: pointer to Buffer
/// @param u8ListIndex \b IN: List Index
/// @return WORD: List page number
//------------------------------------------------------------------------------
static WORD _GetListPageNumber(BYTE *pu8Buffer, BYTE u8ListIndex)
{
    WORD u16ListPageNumber;
    WORD u16Temp;

    switch ( u8ListIndex )
    {
    case 0:
        u16Temp = (WORD)pu8Buffer[0];
        u16Temp = u16Temp & 0x00FF;
        u16ListPageNumber = u16Temp;

        u16Temp = (WORD)pu8Buffer[1];
        u16Temp = u16Temp & 0x0003;
        u16ListPageNumber |= (u16Temp << 8);
        break;

    case 1:
        u16Temp = (WORD)pu8Buffer[1];
        u16Temp = u16Temp & 0x00FC;
        u16ListPageNumber = u16Temp >> 2;

        u16Temp = (WORD)pu8Buffer[2];
        u16Temp = u16Temp & 0x000F;
        u16ListPageNumber |= (u16Temp << 6);
        break;

    case 2:
        u16Temp = (WORD)pu8Buffer[2];
        u16Temp = u16Temp & 0x00F0;
        u16ListPageNumber = u16Temp >> 4;

        u16Temp = (WORD)pu8Buffer[3];
        u16Temp = u16Temp & 0x003F;
        u16ListPageNumber |= (u16Temp << 4);
        break;

    case 3:
        u16Temp = (WORD)pu8Buffer[3];
        u16Temp = u16Temp & 0x00C0;
        u16ListPageNumber = u16Temp >> 6;

        u16Temp = (WORD)pu8Buffer[4];
        u16Temp = u16Temp & 0x00FF;
        u16ListPageNumber |= (u16Temp << 2);
        break;

    default:
        u16ListPageNumber = DEFAULT_LISTPAGE[0];
        break;
    }

    u16ListPageNumber &= 0x03FF;

    return u16ListPageNumber;
}

//------------------------------------------------------------------------------
/// -This function will Set List Page Number
/// @param pu8Buffer \b IN: pointer to Buffer
/// @param u8ListIndex \b IN: List Index
/// @param u16ListPageNumber \b IN: List Page Number
//------------------------------------------------------------------------------
static void _SetListPageNumber(BYTE *pu8Buffer, BYTE u8ListIndex, WORD u16ListPageNumber)
{
    u16ListPageNumber &= 0x03FF;

    switch ( u8ListIndex )
    {
    case 0:
        pu8Buffer[0] &= 0x0000;
        pu8Buffer[0] |= (u16ListPageNumber & 0x00FF);

        pu8Buffer[1] &= 0x00FC;
        pu8Buffer[1] |= ((u16ListPageNumber & 0x0300) >> 8);
        break;

    case 1:
        pu8Buffer[1] &= 0x0003;
        pu8Buffer[1] |= ((u16ListPageNumber & 0x003F) << 2);

        pu8Buffer[2] &= 0x00F0;
        pu8Buffer[2] |= ((u16ListPageNumber & 0x03C0) >> 6);
        break;

    case 2:
        pu8Buffer[2] &= 0x000F;
        pu8Buffer[2] |= ((u16ListPageNumber & 0x000F) << 4);

        pu8Buffer[3] &= 0x00C0;
        pu8Buffer[3] |= ((u16ListPageNumber & 0x03F0) >> 4);
        break;

    case 3:
        pu8Buffer[3] &= 0x003F;
        pu8Buffer[3] |= ((u16ListPageNumber & 0x0003) << 6);

        pu8Buffer[4] &= 0x0000;
        pu8Buffer[4] |= ((u16ListPageNumber & 0x03FC) >> 2);
        break;
    }
}
#endif

//------------------------------------------------------------------------------
/// -This function will Get from NVRAM
/// @param u32Address \b IN: Address
/// @param pu8Buffer \b IN: pointer to Buffer
/// @param u8Size \b IN: Size
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _GetNVRAM(DWORD u32Address, BYTE * pu8Buffer, BYTE u8Size)
{
#if 1
    //printf("_GetNVRAM(u32Address=0x%X, u8Size=%u)\n", u32Address, u8Size);

    return MApp_ReadDatabase(u32Address, pu8Buffer, u8Size);
#else
    if ( u8Size == 0 )
    {
        return FALSE;
    }

    if(u32Address<RM_GEN_USAGE)
    {
      #if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
        memcpy((U8*)(pu8Buffer), (U8*)_PA2VA(u32Address+RAM_DISK_MEM_ADDR), u8Size);
      #else
        msAPI_rmBurstReadBytes(u32Address, pu8Buffer, u8Size);
      #endif
    }
    else if(u32Address>=RM_GEN_USAGE && u32Address<(RM_64K_SIZE+RM_GEN_USAGE))
    {
      #if (ENABLE_DRAM_DB_CH_SAVE_TO_EEPROM)
        msAPI_rmBurstReadBytes(u32Address, pu8Buffer, u8Size);
      #else
        memcpy( pu8Buffer, (void *)_PA2VA(u32Address+RAM_DISK_MEM_ADDR),  u8Size);
      #endif
    }
    else
    {
        __ASSERT(0);//printf("\n ReadDatabase index overflow...!!!");
        return FALSE;
    }

    return TRUE;
#endif
}

//------------------------------------------------------------------------------
/// -This function will Set to NVRAM
/// @param u32Address \b IN: Address
/// @param pu8Buffer \b IN: pointer to Buffer
/// @param u8Size \b IN: Size
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
static BOOLEAN _SetNVRAM(DWORD u32Address, BYTE *pu8Buffer, BYTE u8Size)
{
    //printf("_SetNVRAM(u32Address=0x%X, u8Size=%u)\n", u32Address, u8Size);

#if 1
    return MApp_WriteDatabase(u32Address, pu8Buffer, u8Size);

#else
    if ( u8Size == 0 )
    {
        return FALSE;
    }

    if( u32Address<RM_GEN_USAGE )
    {
      #if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
        memcpy((U8*)_PA2VA(u32Address+RAM_DISK_MEM_ADDR), (U8*)(pu8Buffer), u8Size);
        //g_u8QuickDataBase |= QUICK_DB_GENST_MODIFIED;
        MApp_DB_GEN_Set_DataChanged(TRUE);
      #else
        msAPI_rmBurstWriteBytes(u32Address, pu8Buffer, u8Size);
      #endif
    }
    else if(u32Address>=RM_GEN_USAGE && u32Address<(RM_64K_SIZE+RM_GEN_USAGE))
    {
      #if (ENABLE_DRAM_DB_CH_SAVE_TO_EEPROM)
        msAPI_rmBurstWriteBytes(u32Address, pu8Buffer, u8Size);
      #else
        memcpy( (void *)_PA2VA(u32Address+RAM_DISK_MEM_ADDR),
                pu8Buffer,u8Size );
        //g_u8QuickDataBase |= QUICK_DB_UPDATE;
        MApp_DB_CH_Set_DataChanged(TRUE);
      #endif
    }
    else
    {
        //printf("\n MApp_WriteDatabase index overflow...!!!");
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
#endif
}

//------------------------------------------------------------------------------
/// -This function will do String Copy
/// @param pu8Dst \b IN: Destination
/// @param pu8Src \b IN: Source
/// @param u8Size \b IN: Size
//------------------------------------------------------------------------------
static void _StringCopy(BYTE *pu8Dst, BYTE *pu8Src, BYTE u8Size)
{
    BYTE i;

    for ( i = 0; i < u8Size; i++)
    {
        pu8Dst[i] = pu8Src[i];
    }
}

#if (ENABLE_CH_VOLUME_COMP)
//------------------------------------------------------------------------------
/// -This function will Get Volume compensation
/// @param u8ProgramNumber \b IN: Program Number
/// @return BYTE : Volume compensation
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetVolumeComp(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        return (BYTE)Misc.eVolumeComp;
    }

    return MAX_VOLUME_COMP_ABS;
}

//------------------------------------------------------------------------------
/// -This function will Set Volume compensation
/// @param u8ProgramNumber \b IN: Program Number
/// @param eVolumeComp \b IN: Volume compensation
//------------------------------------------------------------------------------
void msAPI_ATV_SetVolumeComp(BYTE u8cProgramNumber, BYTE eVolumeComp)
{
    ATV_MISC Misc;

    if( TRUE == _GetPRTable(u8cProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        Misc.eVolumeComp = eVolumeComp;

        if(TRUE != _SetPRTable(u8cProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
            __ASSERT(0);
    }
}
#endif //(ENABLE_CH_VOLUME_COMP)

#if( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC))
static BOOLEAN _bDirectTune;

BOOLEAN msAPI_ATV_GetDirectTuneFlag(void)
{
    return _bDirectTune;
}

void msAPI_ATV_SetDirectTuneFlag(BOOLEAN bDirectTune)
{
#if ENABLE_SBTVD_ATV_SYSTEM
    if(!IS_SBTVD_APP)
    {
        _bDirectTune = FALSE;
    }
    else
#endif
    {
        _bDirectTune = bDirectTune;
    }
}

BYTE msAPI_ATV_LoadCurrentProgramNumber(void)
{
    _u8CurrentProgramNumber = _LoadProgramNumber();

    _u8PastProgramNumber = _u8CurrentProgramNumber;

    return _u8CurrentProgramNumber;
}

WORD msAPI_ATV_MapChanToFreq(BYTE u8ProgramNumber)
{
    WORD wPLL;
    DWORD DFreq = 0;

    if((msAPI_ATV_GetChannelMin() > u8ProgramNumber) || (msAPI_ATV_GetChannelMax() < u8ProgramNumber))
    {
        return UHF_MIN_PLL;
    }

#if ENABLE_SBTVD_ATV_SYSTEM
    if(_bAntenna == ANT_AIR)
    {
        switch(u8ProgramNumber)
        {
            default:
                if((u8ProgramNumber >= 7) && (u8ProgramNumber <= 13))
                    DFreq = (DWORD)((u8ProgramNumber - 7) * 6000L + 175250L);
                else if((u8ProgramNumber >= 14) && (u8ProgramNumber <= 69))
                    DFreq = (DWORD)((u8ProgramNumber - 14) * 6000L + 471250L);
                break;

            case 2:  DFreq = 55250L;    break;
            case 3:  DFreq = 61250L;    break;
            case 4:  DFreq = 67250L;    break;
            case 5:  DFreq = 77250L;    break;
            case 6:  DFreq = 83250L;    break;
        }
    }
    else //ANT_CATV
    {
        switch(u8ProgramNumber)
        {
            default:
                if((u8ProgramNumber >= 7) && (u8ProgramNumber <= 13))
                    DFreq = (DWORD)((u8ProgramNumber - 7) * 6000L + 175250L);
                else if((u8ProgramNumber >= 14) && (u8ProgramNumber <= 22))
                    DFreq = (DWORD)((u8ProgramNumber - 14) * 6000L + 121250L);
                else if((u8ProgramNumber >= 23) && (u8ProgramNumber <= 94))
                    DFreq = (DWORD)((u8ProgramNumber - 23) * 6000L + 217250L);
                else if((u8ProgramNumber >= 95) && (u8ProgramNumber <= 99))
                    DFreq = (DWORD)((u8ProgramNumber - 95) * 6000L + 91250L);
                else if((u8ProgramNumber >= 100) && (u8ProgramNumber <= 125))
                    DFreq = (DWORD)((u8ProgramNumber - 100) * 6000L + 649250L);
                break;

            case 1:  DFreq = 73250L;    break;
            case 2:  DFreq = 55250L;    break;
            case 3:  DFreq = 61250L;    break;
            case 4:  DFreq = 67250L;    break;
            case 5:  DFreq = 77250L;    break;
            case 6:  DFreq = 83250L;    break;
        }
    }
#elif ENABLE_DVB_TAIWAN_APP
    if (_bAntenna == ANT_AIR)
    {
        switch(u8ProgramNumber)
        {
            /* UHF */
            default:
                if((u8ProgramNumber >= 14) && (u8ProgramNumber <= 22))
                    DFreq = (DWORD)((u8ProgramNumber - 14) * 6000L + 121250L);
                else
                    DFreq = (DWORD)((u8ProgramNumber - 23) * 6000L + 217250L);
                break;
            /* Lo VHF */
            case 2: DFreq = 55250L;    break;
            case 3: DFreq = 61250L;    break;
            case 4: DFreq = 67250L;    break;
            case 5: DFreq = 77250L;    break;
            case 6: DFreq = 83250L;    break;
            /* Hi VHF */
            case 7: DFreq = 175250L;    break;
            case 8: DFreq = 181250L;    break;
            case 9: DFreq = 187250L;    break;
            case 10: DFreq = 193250L;    break;
            case 11: DFreq = 199250L;    break;
            case 12: DFreq = 205250L;    break;
            case 13: DFreq = 211250L;    break;
        }
    }
    else //ANT_CATV
    {
        switch(u8ProgramNumber)
        {
            default:
                if((u8ProgramNumber >= 7) && (u8ProgramNumber <= 13))
                    DFreq = (DWORD)((u8ProgramNumber - 7) * 6000L + 175250L);
                else if((u8ProgramNumber >= 14) && (u8ProgramNumber <= 22))
                    DFreq = (DWORD)((u8ProgramNumber - 14) * 6000L + 121250L);
                else if((u8ProgramNumber >= 23) && (u8ProgramNumber <= 94))
                    DFreq = (DWORD)((u8ProgramNumber - 23) * 6000L + 217250L);
                else if((u8ProgramNumber >= 95) && (u8ProgramNumber <= 99))
                    DFreq = (DWORD)((u8ProgramNumber - 95) * 6000L + 91250L);
                else if((u8ProgramNumber >= 100) && (u8ProgramNumber <= 158))
                    DFreq = (DWORD)((u8ProgramNumber - 100) * 6000L + 649250L);
                break;

            case 1:  DFreq = 73250L;    break;
            case 2:  DFreq = 55250L;    break;
            case 3:  DFreq = 61250L;    break;
            case 4:  DFreq = 67250L;    break;
            case 5:  DFreq = 77250L;    break;
            case 6:  DFreq = 83250L;    break;
        }
    }
#else
    if (_bAntenna == ANT_AIR)
    {
        switch(u8ProgramNumber)
        {
            /* UHF */
            default:DFreq = (DWORD)(u8ProgramNumber * 6000L + 387250L); break;
            /* Lo VHF */
            case 2: DFreq = 55250L;    break;
            case 3: DFreq = 61250L;    break;
            case 4: DFreq = 67250L;    break;
            case 5: DFreq = 77250L;    break;
            case 6: DFreq = 83250L;    break;
            /* Hi VHF */
            case 7: DFreq = 175250L;    break;
            case 8: DFreq = 181250L;    break;
            case 9: DFreq = 187250L;    break;
            case 10: DFreq = 193250L;    break;
            case 11: DFreq = 199250L;    break;
            case 12: DFreq = 205250L;    break;
            case 13: DFreq = 211250L;    break;
        }
    }
    else //ANT_CATV
    {
        switch(u8ProgramNumber)
        {
            default:
                if((u8ProgramNumber >= 7) && (u8ProgramNumber <= 13))
                    DFreq = (DWORD)((u8ProgramNumber - 7) * 6000L + 175250L);
                else if((u8ProgramNumber >= 14) && (u8ProgramNumber <= 22))
                    DFreq = (DWORD)((u8ProgramNumber - 14) * 6000L + 121250L);
                else if((u8ProgramNumber >= 23) && (u8ProgramNumber <= 94))
                    DFreq = (DWORD)((u8ProgramNumber - 23) * 6000L + 217250L);
                else if((u8ProgramNumber >= 95) && (u8ProgramNumber <= 99))
                    DFreq = (DWORD)((u8ProgramNumber - 95) * 6000L + 91250L);
                else if((u8ProgramNumber >= 100) && (u8ProgramNumber <= 158))
                    DFreq = (DWORD)((u8ProgramNumber - 100) * 6000L + 649250L);
                break;

            case 1:  DFreq = 73250L;    break;
            case 2:  DFreq = 55250L;    break;
            case 3:  DFreq = 61250L;    break;
            case 4:  DFreq = 67250L;    break;
            case 5:  DFreq = 77250L;    break;
            case 6:  DFreq = 83250L;    break;
        }
    }
#endif

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    wPLL = (WORD) ((DFreq* 10) / 625);  // 62.5KHz
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    wPLL = (WORD) (DFreq / 50);         // 50KHz
#else
    wPLL = (WORD) (DFreq * 100) / 3125);// 31.25KHz
#endif

    //printf("index %bu, DFreq = %lu, wPLL = %u\n", u8ProgramNumber-1, DFreq, wPLL);

    return wPLL;
}

//------------------------------------------------------------------------------
/// -This function will set all Program PLL data
//------------------------------------------------------------------------------
void msAPI_ATV_InitProgramPLLData(void)
{
    U8 _u8Buf0;
    U8 _u8Buf1 = msAPI_ATV_GetChannelMin();
    U8 _u8Buf2 = msAPI_ATV_GetChannelMax();
    WORD wPLL;

    for(_u8Buf0=_u8Buf1; _u8Buf0<=_u8Buf2 ;_u8Buf0++)
    {
        //printf("<1> [%bu][%bu] active = %bu\n", (_u8Buf0-1), _GetPRIndexTable(_u8Buf0-1), _IsPREntityActive(_GetPRIndexTable(_u8Buf0-1)));
        wPLL = msAPI_ATV_MapChanToFreq(_u8Buf0);
        if(TRUE != _SetPRTable(_u8Buf0-1, (BYTE *)&wPLL, PRDATA_PLL_PARAM))
        {
            __ASSERT(0);
        }
        //printf("<2> [%bu][%bu] active = %bu\n", (_u8Buf0-1), _GetPRIndexTable(_u8Buf0-1), _IsPREntityActive(_GetPRIndexTable(_u8Buf0-1)));
    }
}
//------------------------------------------------------------------------------
/// -This function will check if the specific program is Auto color system
/// @param cProgramNumber \b IN: program number
/// @return BOOLEAN:
/// - TRUE: yes ,auto color
/// - FALAS: no , not auto color
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgramAutoColorSystem(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( Misc.bIsAutoColorSystem == FALSE )
        {
            return FALSE;
        }
    }

    return TRUE;
}
//------------------------------------------------------------------------------
/// -This function will set  if the specific program is auto color system or not.
/// @param cProgramNumber \b IN: program number
/// @param bIsAutoColorSystem \b IN:
/// - TRUE:  this program is auto color system
/// - FALAS: this program is not auto color system
//------------------------------------------------------------------------------
void msAPI_ATV_SetProgramAutoColorSystem(BYTE u8ProgramNumber, BOOLEAN AutoColorSystem)
{
    ATV_MISC Misc;

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( AutoColorSystem == FALSE )
        {
            Misc.bIsAutoColorSystem = FALSE;
        }
        else
        {
            Misc.bIsAutoColorSystem = TRUE;
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}

//------------------------------------------------------------------------------
/// -This function will check if the specific program is Searched
/// @param cProgramNumber \b IN: program number
/// @return BOOLEAN:
/// - TRUE: Searched
/// - FALAS: Not Searched
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgramSearched(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( Misc.bIsSearched == FALSE )
        {
            return FALSE;
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will check if the specific program is Searched or not.
/// @param cProgramNumber \b IN: program number
/// @param Searched \b IN:
/// - TRUE: Searched this program
/// - FALAS: Don't Searched this program
//------------------------------------------------------------------------------
void msAPI_ATV_SetSearchedProgram(BYTE u8ProgramNumber, BOOLEAN bIsLock)
{
    ATV_MISC Misc;

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( bIsLock == FALSE )
        {
            Misc.bIsSearched = FALSE;
        }
        else
        {
            Misc.bIsSearched = TRUE;
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
        }
    }
}

BYTE msAPI_ATV_GetNextActiveProgNum(BYTE u8ProgramNumber)
{
    if(u8ProgramNumber < ATV_FIRST_PR_NUM)
    {
        u8ProgramNumber = ATV_FIRST_PR_NUM;
    }
    do
    {
        u8ProgramNumber++;

        if(TRUE == _IsIndexActive(u8ProgramNumber))
            break;

    } while (u8ProgramNumber <= msAPI_ATV_GetChannelMax());

    return u8ProgramNumber;
}


void msAPI_ATV_SaveProgram_Exit_Menu(BYTE u8CurrentProgramNumber)
{
#if(ENABLE_SBTVD_ATV_SYSTEM)
    if(msAPI_SRC_IS_SBTVD_InUse())
#endif
    {
        BYTE sStationName[MAX_STATION_NAME];

        if ( msAPI_ATV_GetCurrentProgramNumber() != u8CurrentProgramNumber )
        {
            msAPI_ATV_SetCurrentProgramNumber(u8CurrentProgramNumber);
        }

        if ( FALSE == msAPI_Tuner_IsAFTNeeded() &&
             TRUE == msAPI_Tuner_IsCurrentChannelAndSavedChannelSame() )
        {
            msAPI_ATV_NeedAFT(u8CurrentProgramNumber, FALSE);
        }
        else
        {
            msAPI_ATV_NeedAFT(u8CurrentProgramNumber, TRUE);
        }

        //msAPI_ATV_SkipProgram(u8CurrentProgramNumber, FALSE);

        //msAPI_ATV_SetFavoriteProgram(u8CurrentProgramNumber, FALSE);

        //msAPI_ATV_LockProgram(u8CurrentProgramNumber, FALSE);

        msAPI_Tuner_GetCurrentStationName(sStationName);

        msAPI_ATV_SetStationName(u8CurrentProgramNumber, sStationName);

        msAPI_ATV_SetAudioStandard(u8CurrentProgramNumber, msAPI_AUD_GetAudioStandard());

        msAPI_ATV_SetVideoStandardOfProgram(u8CurrentProgramNumber, msAPI_AVD_GetVideoStandard());

        msAPI_ATV_SetProgramPLLData(u8CurrentProgramNumber, msAPI_Tuner_GetCurrentChannelPLL());

        msAPI_ATV_SetMediumAndChannelNumber(u8CurrentProgramNumber, msAPI_Tuner_GetMedium(), msAPI_Tuner_GetChannelNumber());
    }

}
#endif

