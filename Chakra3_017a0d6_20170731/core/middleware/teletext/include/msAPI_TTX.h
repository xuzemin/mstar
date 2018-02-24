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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MSAPI_TTX_H
#define _MSAPI_TTX_H

#include "Board.h"

#if (ENABLE_TTX)

#include "TT_API25.h"
#include "drvAVD.h"
#include "msAPI_Global.h"

#ifdef _MSAPI_TTX_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define TTXBUF_VBI_SIZE         (360*48)

#define MSIF_TTX_LIB_CODE       {'T','T','X','_'} //Lib code
#define MSIF_TTX_LIBVER         {'0','2'} //LIB version
#define MSIF_TTX_BUILDNUM       {'0','0'} //Build Number
#define MSIF_TTX_CHANGELIST     {'0','0','2','0','1','7','5','0'} //P4 ChangeList Number

#define MW_TTX_VER                  /* Character String for DRV/API version             */  \
    MSIF_TAG,                   /* 'MSIF'                                           */  \
    MSIF_CLASS,                 /* '00'                                             */  \
    MSIF_CUS,                   /* 0x0000                                           */  \
    MSIF_MOD,                   /* 0x0000                                           */  \
    MSIF_CHIP,                                                                      	\
    MSIF_CPU,                                                                           \
    MSIF_TTX_LIB_CODE,              /* IP__                                             */  \
    MSIF_TTX_LIBVER,                /* 0.0 ~ Z.Z                                        */  \
    MSIF_TTX_BUILDNUM,              /* 00 ~ 99                                          */  \
    MSIF_TTX_CHANGELIST,  			/* CL#                         */  \
    MSIF_OS

#define lmiRED              0x00
#define lmiGREEN            0x01
#define lmiYELLOW           0x02
#define lmiCYAN             0x03

//****************************************************************************
// Public attributes.
//****************************************************************************

typedef enum
{
    TTX_DIGIT_0,
    TTX_DIGIT_1,
    TTX_DIGIT_2,
    TTX_DIGIT_3,
    TTX_DIGIT_4,
    TTX_DIGIT_5,
    TTX_DIGIT_6,
    TTX_DIGIT_7,
    TTX_DIGIT_8,
    TTX_DIGIT_9,
    TTX_PAGE_UP,
    TTX_PAGE_DOWN,
    TTX_SUBPAGE,
    TTX_PAGE_RIGHT,
    TTX_PAGE_LEFT,
    TTX_RED,
    TTX_GREEN,
    TTX_YELLOW,
    TTX_CYAN,
    TTX_MIX,
    TTX_TEXT,
    TTX_TV,
    TTX_UPDATE,
    TTX_INDEX,
    TTX_HOLD,
    TTX_LIST,
    TTX_TIME,
    TTX_SIZE,
    TTX_REVEAL,
    TTX_CLOCK,
    TTX_SUBTITLE_TTX_ON,
    TTX_SUBTITLE_NAVIGATION_MODE,
#if ENABLE_TTX_ACI
    TTX_UP,
    TTX_DOWN,
    TTX_OK,
    TTX_ACI,
#endif
    TTX_STATUS_DISPLAY,
    TTX_CLEAR_LIST,
    TTX_MIX_TEXT,
    TTX_GOTO_PAGE,
    TTX_PAT,
    TTX_CYCLE_SUBPAGE,
    TTX_CANCEL,
    TTX_MAX_TEXT_COMMAND
} TELETEXT_COMMAND;

/*
language group
*/
typedef enum
{
    TT_Charset_Group_West,// = TT_DEC_LG_WEST,//    = TT_DEC_WEST,
    TT_Charset_Group_East,// = TT_DEC_LG_EAST,//    = TT_DEC_EAST,
    TT_Charset_Group_Russian,// = TT_DEC_LG_RUSSIAN,// = TT_DEC_RUSSIAN,
    TT_Charset_Group_Arabic,// = TT_DEC_LG_ARABIC,//  = TT_DEC_ARABIC,
    TT_Charset_Group_Farsi// = TT_DEC_LG_FARSI//   = TT_DEC_FARSI

} TT_Charset_Group;

// Note: the enum is not used in TTX 2.5, just for compile purpose
typedef enum
{
    OSD_H_START,
    OSD_V_START,
    OSD_WINDOW_WIDTH,
    OSD_WINDOW_HEIGHT,
    OSD_PAT_MODE,
    OSD_TRANSPARENT_COLOR_KEY,
    OSD_TRANSPARENT_COLOR,
    OSD_BACKGROUND_COLOR
} EN_TT_OSD_PARAMETER;

typedef enum
{
    TT_VALID_VPS,
    TT_VALID_PACKET_8_30_1,
    TT_VALID_PACKET_8_30_2,
    TT_VALID_TELETEXT_SIGNAL,
    TT_VALID_WSS,
    TT_VALID_CURRENT_PAGE,
    TT_VALID_LISTMODE,
    TT_VALID_MIXMODE,
    TT_VALID_CANCELMODE,
    TT_VALID_SUBTITLE,
    TT_VALID_SUBPAGEINPUT_ON,
    TT_VALID_SUBPAGEINPUT_AVAILABLE,
    TT_VALID_DISPLAY_OPENED,
    TT_VALID_UPDATEMODE,
    TT_VALID_SHOWNOSUBPAGE,
    TT_VALID_REVEALMODE,
    TT_VALID_NEWSFLASH,
} eTELETEXT_STATUS;

typedef struct
{
    U_INT8 u8Multiple_H;
    U_INT8 u8Multiple_V;

    U_INT8 u8CharWidth;
    U_INT8 u8CharHeight;
    U_INT8 u8CharSize;
    U_INT16 u16FontBinID;

    U_INT16 u16TTX_OSD_Width;
    U_INT16 u16TTX_OSD_Height;

    U_INT16 u16TTX_WIN_Width;
    U_INT16 u16TTX_WIN_Height;
    U_INT16 u16TTX_WIN_Start_X;
    U_INT16 u16TTX_WIN_Start_Y;

    U_INT16 u16TTX_PAT_WIN_Start_X;
} TTX_OSD_CONFIG;

//****************************************************************************
// Definitions
//****************************************************************************
#define ALIGNED_VALUE(value, align)  ( ((value) + ((align)-1)) & ~((align)-1) )

#define TTX_SOURCE_DTV  1
#define TTX_SOURCE_ANALOG   0

//****************************************************************************
// Public implementation.
//****************************************************************************
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetCMD()
/// @brief \b Function \b Description:  Set TTX commands to TTX system
/// @param <IN>        \b wCMD             : Teletext commands
/// @param <IN>        \b parm1             : parameter 1
/// @param <IN>        \b parm2             : parameter 2
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE void msAPI_TTX_SetCMD(U16 wCMD, U16 parm1, U16 parm2);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_OnOffVBISlicer()
/// @brief \b Function \b Description:  Turn on/off the VBI slicer
/// @param <IN>        \b on               : enable/disable VBI slicer
///                                                   - -Disable(0)
///                                                   - -Enable(1)
/// @param <OUT>         \b None            :
/// @param <RET>          \b None            :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE void msAPI_TTX_OnOffVBISlicer(U8 on);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_CheckTTX()
/// @brief \b Function \b Description:  Check VBI H/W TTX indication status
/// @param <IN>        \b None               :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :
///                                                 TTX Not found(False).
///                                                 TTX Found(True)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE BOOLEAN msAPI_TTX_CheckTTX(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_CheckTTXSignal()
/// @brief \b Function \b Description:  Test if there's TTX signal
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :
///                                         - The TTX signal is valid(TRUE)
///                                         - The TTX signal is invalid(FALSE)
/// @param <GLOBAL>    \b None            :
/// COMMENT :
/// In 300ms, if the amount of valid headers is greater than DEFAULT_TTX_HEADER_COUNT
/// then we think it is a valid TTX channel
////////////////////////////////////////////////////////////////////////////////
INTERFACE BOOLEAN msAPI_TTX_CheckTTXSignal(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_CheckTTXClockSignal()
/// @brief \b Function \b Description:  Test if there's TTX clock
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :
///                                             - There's TTX clock info(1)
///                                             - There's TTX clock info(0)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE BOOLEAN msAPI_TTX_CheckTTXClockSignal(void);

#if 0
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_AcqGetCurrentPage()
/// @brief \b Function \b Description:  Returns the current page and subpage number.
/// @param <IN>        \b None             :
/// @param <OUT>         \b aMagPage            :   the Magpage number
/// @param <OUT>         \b aSubPage            :   the Subpage number
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE void msAPI_TTX_AcqGetCurrentPage (U16 *aMagPage, U16 *aSubPage);
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_GetWssStatus()
/// @brief \b Function \b Description:  Check the WSS decode status
/// @param <IN>        \b None               :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :   The WSS checking value
///                                                     WSS detected(1)
///                                                     WSS detected(0)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE U8 msAPI_TTX_GetWssStatus(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_ReadWssWord()
/// @brief \b Function \b Description:  Get the WSS value
/// @param <IN>        \b None               :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :  (U16) WSS value
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE U16 msAPI_TTX_ReadWssWord(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetSource()
/// @brief \b Function \b Description:  set TTX input source
/// @param <IN>        \b Source             :  analog(0), digital(1)
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE void msAPI_TTX_SetSource(U8 source);
#if 0
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetNaviMode()
/// @brief \b Function \b Description:  Set TTX navigation mode
/// @param <IN>        \b mode             :  TTX mode setting
///                                                 TT_DEC_HOLD_MODE(0x01)
///                                                 TT_DEC_REVEAL_MODE(0x02)
///                                                 TT_DEC_SIZE_MODE(0x04)
///                                                 TT_DEC_CANCEL_MODE(0x08)
///                                                 TT_DEC_MIX_MODE(0x10)
///                                                 TT_DEC_LIST_MODE(0x20)
///                                                 TT_DEC_CLOCK_MODE(0x40)
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE void msAPI_TTX_SetNaviMode(U16 mode);
#endif
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_GetSubtitlesAvailable()
/// @brief \b Function \b Description:  Check if there is subtitle page
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b           :
///                                                         Subtitle page found(1)
///                                                         Subtitle page not found(0)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE U32 msAPI_TTX_GetSubtitlesAvailable( void );

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_GetSubtitlePage()
/// @brief \b Function \b Description:  Get subtitle page information
/// @param <IN>        \b sub_index             :  Index of subtile pages
/// @param <OUT>         \b magPage            : Magazine page of the subtitle page
/// @param <OUT>         \b subPage            : Subcode of the subtitle page
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE BOOLEAN msAPI_TTX_GetSubtitlePage(U8 sub_index, U16 *magPage, U16 *subPage);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_Decoder_Process()
/// @brief \b Function \b Description:  TTX main routine, it needs to be run in task
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE void msAPI_TTX_Decoder_Process(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_GETColorKey()
/// @brief \b Function \b Description:  Get the LIST mode status
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :   LIST mode(1), non-LIST mode(0)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE BOOLEAN msAPI_TTX_GETColorKey(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetVideoStandard()
/// @brief \b Function \b Description:  Set video standard to VBI register
/// @param <IN>        \b ucVideoSystem             :
///                                                                 SIG_NTSC,           ///< NTSC
///                                                                 SIG_PAL,           ///< PAL
///                                                                 SIG_SECAM,           ///< SECAM
///                                                                 SIG_NTSC_443,           ///< NTSC 443
///                                                                 SIG_PAL_M,           ///< PAL M
///                                                                 SIG_PAL_NC,           ///< PAL NC
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
INTERFACE void msAPI_TTX_SetVideoStandard(AVD_VideoStandardType ucVideoSystem);

//****************************************************************************
/// Reset TTX decoding system
/// @param None \b IN:
/// @return None :
//****************************************************************************
INTERFACE void msAPI_TTX_ResetAcquisition(void);

//****************************************************************************
/// Check each TTX system event/status is valid or not
/// @param eStatus \b IN: checking status
/// -@see eTELETEXT_STATUS
/// @param *pbValid \b OUT: checking status
/// - TRUE: the checked status is valid
/// - FALSE: the checked status is invalid
/// @return BOOLEAN : return status
/// -@see BOOLEAN
//****************************************************************************
INTERFACE BOOLEAN msAPI_TTX_IsStatusValid(eTELETEXT_STATUS eStatus, BOOLEAN *pbValid);

//****************************************************************************
/// ATS system: Get ATV station name from Teletext system. It will base on VPS, P830FM1 and P830FM2
/// @param *sStationName \b OUT: Station name string
/// @param bArraySize \b IN: the length for input array "sStationName"
/// @param *pcPriority \b OUT: The sorting priority of sStationName
/// @return BOOLEAN : the return status
/// -@see BOOLEAN
//****************************************************************************
INTERFACE BOOLEAN msAPI_TTX_GetStationNameFromTeletext(BYTE *sStationName, BYTE bArraySize, BYTE *pcPriority);

//****************************************************************************
/// For TTX list mode system. It will get the corresponding pagelink from CM DB, and set to TTX List mode
/// @param None \b IN:
/// @return BOOLEAN : return status
/// -@see BOOLEAN
//****************************************************************************
INTERFACE BOOLEAN msAPI_TTX_ModifyListPageNumber(void);

//****************************************************************************
/// For TTX list mode system. It will save the corresponding pagelink to CM DB
/// @param None \b IN:
/// @return BOOLEAN : return status
/// -@see BOOLEAN
//****************************************************************************
INTERFACE BOOLEAN msAPI_TTX_SaveListPageNumber(void);

//****************************************************************************
/// Init the TTX whole system. This function must be called at system startup
/// @param None \b IN:
/// @return BOOLEAN :
/// - TRUE:   TTX init succeed
/// - FASLE:  TTX init fail
//****************************************************************************
INTERFACE BOOL msAPI_TTX_InitSystem(void);

//****************************************************************************
/// Get the TTX VBI buffer address in DRAM
/// @param None \b IN:
/// @return U32 : TTX VBI start buffer address in DRAM
//****************************************************************************
INTERFACE U32 msAPI_TTX_GetVBIStartAddress(void);

//****************************************************************************
/// Get the TTX VBI buffer size in DRAM
/// @param None \b IN:
/// @return U32 : TTX real start buffer address in DRAM
//****************************************************************************
INTERFACE U32 msAPI_TTX_GetVBI_BufferSize(void);

//****************************************************************************
/// Get the status which TTX packet acquire is running in ISR or not
/// @param None \b IN:
/// @return BOOLEAN :
/// - TRUE:   TTX ISR is running
/// - FASLE:  TTX ISR is not running
//****************************************************************************
INTERFACE U8 msAPI_TTX_Get_VBIAcquireEnableStatus(void);

//****************************************************************************
/// Enable/disable TTX packet acquire in ISR
/// @param enable \b IN:
/// - TRUE: enable TTX packet acquire in ISR
/// - DISABLE: disable TTX packet acquire in ISR
/// @return None :
//****************************************************************************
INTERFACE void msAPI_TTX_VBIAcquireEnable(U8 enable);

//****************************************************************************
/// Enable/disable TTX packet acquire in ISR (just for ATV scan purpose)
/// @param enable \b IN:
/// - TRUE: enable TTX packet acquire in ISR
/// - DISABLE: disable TTX packet acquire in ISR
/// @return None :
//****************************************************************************
INTERFACE void msAPI_TTX_VBIAcquireScanEnable(U8 enable);

//****************************************************************************
/// msAPI_TTX_LoadFon(): Load TTX font to DRAM
/// @param None \b IN:
/// @return None :
//****************************************************************************
INTERFACE void msAPI_TTX_LoadFont(void);

//****************************************************************************
/// msAPI_TTX_SetFontInfo(): set TTX font information
/// @param FontW \b IN: the font width
/// @param FontH \b IN: the font height
/// @param CharW \b IN: the displayed character width
/// @param CharH \b IN: the displayed character height
/// @param addr \b IN: the font address in DRAM
/// @param glyphSize \b IN: the glyph size of the font
/// @param u16BinID \b IN: the font BIN ID in flash
/// @return None :
//****************************************************************************
INTERFACE void msAPI_TTX_SetFontInfo(U_INT8 FontW, U_INT8 FontH,  U_INT8 CharW, U_INT8 CharH, U_INT32 addr, U_INT32 flashAddr, U_INT8 glyphSize, U_INT16 u16BinID);

//****************************************************************************
/// (DTV) set TTX filter ID to TTX system
/// @param u8DTVTTXFid \b IN: TTX filter ID
/// @return None :
//****************************************************************************
INTERFACE void msAPI_TTX_SetTTXFid(U_INT8 u8DTVTTXFid);

//****************************************************************************
/// msAPI_Teletext_GetLIBVerString: Get TTX Version String
/// @param pVer \b OUT: TTX Version String array
/// @return None :
//****************************************************************************
INTERFACE void msAPI_Teletext_GetLIBVerString(U8 *pVer);

INTERFACE void msAPI_TTX_OpenRenderObj(U32 ttxOSDMarginH,
                                     U32 ttxOSDMarginV,
                                       U32 displayX,
                                       U32 displayY,
                                       U32 displayWidth,
                                       U32 displayHeight,
                                     BOOL isTransparent);
INTERFACE void msAPI_TTX_CloseRenderObj(void);

INTERFACE void msAPI_TTX_CollectPackets(void);

INTERFACE void msAPI_TTX_Stop(void);

INTERFACE void msAPI_TTX_Run(void);

INTERFACE void msAPI_TTX_Command(TELETEXT_COMMAND command);

INTERFACE void msAPI_TTX_CommandExt(TELETEXT_COMMAND command,
                                               MS_BOOL boolParam,
                                               MS_U32 param1,
                                               MS_U32 param2);

INTERFACE void msAPI_TTX_SetLanguageGroup(TT_Charset_Group language);

INTERFACE void msAPI_TTX_SetPage(TT_U32 magPage, TT_U32 subpage);

INTERFACE void msAPI_TTX_SetFlofTopEnable(void);

INTERFACE void msAPI_TTX_SetDTVIndexPage(TT_U32 magNum, TT_U32 pageNum);

INTERFACE BOOLEAN msAPI_TTX_GetHeaderTime(TT_U8 *Hour, TT_U8 *Minute, TT_U8 *Second);

INTERFACE BOOLEAN msAPI_TTX_DoesReceiveDataPacketWithPrefix(U16 magPage, U8* prefix, U16 size);

INTERFACE void msAPI_TTX_GetInternalTTXWindowSize(U32* width,
                                                         U32* height,
                                                         U32 ttxMarginH,
                                                          U32 ttxMarginV,
                                                          U32 displayWidth,
                                                          U32 displayHeight);

 INTERFACE void msAPI_TTX_SetChannelChangeTime( U32 channel_change_time);

INTERFACE U8 msAPI_TTX_GetC12C13C14Values(void);

INTERFACE BOOLEAN msAPI_TTX_SetListPageNumber(BYTE cListIndex, WORD wPageNumber);

INTERFACE BOOLEAN msAPI_TTX_GetListPageNumber(BYTE cListIndex, WORD *pwPageNumber);


 #endif // #if (ENABLE_TTX)

#undef INTERFACE

#endif

