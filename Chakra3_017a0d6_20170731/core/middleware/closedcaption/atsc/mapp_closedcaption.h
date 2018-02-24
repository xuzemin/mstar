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
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MAPP_CLOSED_CAPTION_H
#define MAPP_CLOSED_CAPTION_H

#include "datatype.h"
#include "mapi_cc_common.h"
#include "mapi_cc_interface.h"
#include "mapi_cc_decode.h"
#include "mapi_cc_render.h"
#include "mapi_cc_interface.h"
#include "mapi_cc_monitor.h"
#include "msAPI_cc_parser.h"
#include "msAPI_cc_sysinfo.h"
#include "MApp_Exit.h"
//#if BRAZIL_CC
//#include "msapi_cc_brazil_parser.h"
//#endif
#if (BRAZIL_CC == 0)

#ifdef MAPP_CLOSED_CAPTION_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#else

#ifdef MAPP_CLOSED_CAPTION_BRAZIL_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#endif

/************************************************************************/
/* Define                                                               */
/************************************************************************/

// Testing for ATV
#define CC_ATV_TEST                 0
#define CC_TV_TEST          0   // 1:test by unitest
#if  (ATSC_CC == ATV_CC)
#define PARSING_CC_WHENMUTE             0
#define PARSING_CC_AUTO708TO608         0
#else
#define PARSING_CC_WHENMUTE             1
#define PARSING_CC_AUTO708TO608         1
#endif

#define CC_USING_GOP_ID                         E_GOP_APP
#if (CC_USING_GOP_ID == 0)
#define CC_USING_GWIN_ID                        1
#else
#define CC_USING_GWIN_ID                        2
#endif

#if KOREAN_CC_ENABLE
#define CC_FONT_SET_NUM             1
#else
#define CC_FONT_SET_NUM             8
#endif
#define CC_PREVIEW_GWIN_WIDTH       1100

/************************************************************************/
/* Structure                                                            */
/************************************************************************/
typedef enum
{
    CC_MODE_DTV             = SYSINFO_MODE_DTV,
    CC_MODE_ATV             = SYSINFO_MODE_ATV,

} EN_CLOSEDCAPTION_SYSINFO;

/* This Enum should be followed by Menu Setting Enum */
typedef enum
{
    CC_SERVICE_OFF          = CS_OFF,
    CC_SERVICE_CC1          = CS_CC1,
    CC_SERVICE_CC2          = CS_CC2,
    CC_SERVICE_CC3          = CS_CC3,
    CC_SERVICE_CC4          = CS_CC4,
    CC_SERVICE_TEXT1        = CS_TEXT1,
    CC_SERVICE_TEXT2        = CS_TEXT2,
    CC_SERVICE_TEXT3        = CS_TEXT3,
    CC_SERVICE_TEXT4        = CS_TEXT4,
    CC_SERVICE_SERVICE1     = CS_SERVICE1,
    CC_SERVICE_SERVICE2     = CS_SERVICE2,
    CC_SERVICE_SERVICE3     = CS_SERVICE3,
    CC_SERVICE_SERVICE4     = CS_SERVICE4,
    CC_SERVICE_SERVICE5     = CS_SERVICE5,
    CC_SERVICE_SERVICE6     = CS_SERVICE6,

} EN_CLOSEDCAPTION_SERVICE;

/* ENUM List */
typedef enum
{
    STATE_CAPTION_INIT,
    STATE_CAPTION_PARSER,

} EN_CAPTION_STATE;

/* ENUM List */
typedef enum
{
    // action...
    CC_SELECTOR_MODE = 0x0000,
    CC_SELECTOR_SERVICE,
    CC_SELECTOR_BIN_ID_FONT_START,
    CC_SELECTOR_MAX_FONTTABLE_NUM,
    CC_SELECTOR_TRIGGER_LOAD_FONT,
    CC_SELECTOR_CSOPTION_STYLE,
    CC_SELECTOR_EDGE_STYLE,
    CC_SELECTOR_EDGE_COLOR,
    CC_SELECTOR_FG_COLOR,
    CC_SELECTOR_BG_COLOR,
    CC_SELECTOR_FG_OPACITY,
    CC_SELECTOR_BG_OPACITY,
    CC_SELECTOR_FONT,
    CC_SELECTOR_FONTSTYLE,
    CC_SELECTOR_RESET_TO_DEFAULT,

    // attribute...
    CC_SELECTOR_ENABLE24FONTS = 0x0100,
    CC_SELECTOR_ENABLEGOPZOOM,
    CC_SELECTOR_ENABLEAUTOSTABYVIDEOFMT,
    CC_SELECTOR_ENABLEFONTEDGE,
    CC_SELECTOR_ENABLERRVBLK,
    CC_SELECTOR_EDGEOPACITY_NOTRANSPARENT_FLAG,
    CC_SELECTOR_SUPPORT_WORDWRAP_FLAG,
    CC_SELECTOR_PARITY_ERROR_SOLID_BLOCK_FLAG,

    // offset, length...
    CC_SELECTOR_ROW_TOPRSVHEIGHT = 0x0200,
    CC_SELECTOR_ROW_BTMRSVHEIGHT,
    CC_SELECTOR_ATV_AXIS_XPOS,
    CC_SELECTOR_ATV_AXIS_YPOS,
    CC_SELECTOR_DTV_AXIS_XPOS,
    CC_SELECTOR_DTV_AXIS_YPOS,
    CC_SELECTOR_CC_LANG,
    CC_SELECTOR_TEXT_ROWNO,
    CC_SELECTOR_TEXT_YPOS,
    CC_SELECTOR_608_SCROLL_STEP,
    CC_SELECTOR_608_TIMEOUT_CAPITON,
    CC_SELECTOR_608_TIMEOUT_TEXT,
    CC_SELECTOR_708_TIMEOUT_CAPTION,
    CC_SELECTOR_DTV_TIMEOUT_CAPTION,//add this item for Brazil CC Timeout
    CC_SELECTOR_CC_CHECK_PERIOD,
    CC_SELECTOR_AXIS_X_OFFSET,
    CC_SELECTOR_AXIS_Y_OFFSET,
    CC_SELECTOR_TRANSLUCENT,
    CC_SELECTOR_INDENT_GAP,
    CC_SELECTOR_ENABLESVS,
    CC_SELECTOR_ENABLESHS,
    CC_SELECTOR_DEBUG,

    // info...
    CC_SELECTOR_ERROR_CODE = 0x0300,
    CC_SELECTOR_708_AVAILABLETYPE,
    CC_SELECTOR_608_AVAILABLETYPE,
    CC_SELECTOR_STATUS_CODE,
    CC_SELECTOR_DUMP_DBG_MSG,

    // CC selector tail
    CC_SELECTOR_END = 0x0f00

} EN_CC_SELECTOR;

/* Error code */
typedef enum
{
    CC_ERRORCODE_SUCCESS            = 0x0000,
    CC_ERRORCODE_FAIL               = 0x0001,

    CC_ERRORCODE_LOAD_FONT_FAIL     = 0xf000

} EN_CC_ERRORCODE;

// Get PES status
typedef enum
{
    CC_GET_PES_STATE_FAIL = 0,
    CC_GET_PES_STATE_TOBECONTINUED,
    CC_GET_PES_STATE_FINISH,
    CC_GET_PES_STATE_WAITING

} EN_CC_PES_STATE;

typedef enum
{
    CC_FONTSIZE_NORMAL  = CAPTION_FONTSIZE_NORMAL,
    CC_FONTSIZE_SMALL   = CAPTION_FONTSIZE_SMALL,
    CC_FONTSIZE_LARGE   = CAPTION_FONTSIZE_LARGE

} EN_CC_CAPTION_FONT;

typedef enum
{
    CAPTIONMENU_MODE_OFF =0,
    CAPTIONMENU_MODE_ON,
#if (PARSING_CC_WHENMUTE)
    CAPTIONMENU_MODE_CC_WHEN_MUTE,
#endif
    CAPTIONMENU_MODE_NUM,
} EN_CAPTIONMENU_MODE;

typedef enum
{
    CAPTIONMENU_OPTIONMODE_DEFAULT =0,
    CAPTIONMENU_OPTIONMODE_CUSTOM,
    CAPTIONMENU_OPTIONMODE_NUM,
} EN_CAPTIONMENU_OPTIONMODE_MODE;


/************************************************************************/
/* Function List                                                        */
/************************************************************************/

/*
 * CC main functions
 */
INTERFACE void MApp_ClosedCaption_GetUserCmd(void);
INTERFACE EN_RET MApp_ClosedCaption_Main(void);
INTERFACE void MApp_ClosedCaption_Init(void);
INTERFACE void MApp_ClosedCaption_Stop(void);
INTERFACE void MApp_ClosedCaption_SysBuffer_Init(void);
INTERFACE void MApp_ClosedCaption_Set_ProgramChange( void );
INTERFACE void MApp_CC_SetStretchWindow(U16 u16StretchWidth, U16 u16StretchHeight);
/*
 * CC UI Interface
 */
INTERFACE void MApp_ClosedCaption_Exit(void);
INTERFACE void MApp_CC_Initialize(void);
INTERFACE U32 MApp_CC_StartParser(void);
INTERFACE U32 MApp_CC_CtrlParser(U32 selector, U32 value);
INTERFACE U32 MApp_CC_StopParser(void);
INTERFACE U32 MApp_CC_GetInfo(U32 selector);
INTERFACE void MApp_ClosedCaption_Open_Filter(U16 u16PID);
INTERFACE BOOLEAN MApp_CC_CheckExist(void);
INTERFACE void MApp_ClosedCaption_Preview( stCaptionSettingOption_Type *BlinkAttr,CC_FONT * stFont, U8 *pCCText, U8 CCTextLen, U16 u16PosX, U16 u16PosY);
INTERFACE void MApp_ClosedCaption_MapUIDefaultSetting(stCaptionSettingOption_Type *BlinkAttr);
INTERFACE BOOLEAN MApp_IsCCFileIn(void);
 #if CUSTOMER_FOR_UI_CC_708_608_APPEARING
 INTERFACE void MApp_ClosedCaption_Parser_Init(void);
INTERFACE void MApp_ClosedCaption_Parser_Stop(void);
#endif

#undef INTERFACE
#endif
