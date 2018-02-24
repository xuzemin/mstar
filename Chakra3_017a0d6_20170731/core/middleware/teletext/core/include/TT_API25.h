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
#ifndef _TT_API25_H
#define _TT_API25_H

/* target */
#define TT_TARGET_PC                            1
#define TT_TARGET_XX                            2

/* autodetection of target */
#ifdef _MSC_VER
  #define TT_TARGET TT_TARGET_PC
#else
  #define TT_TARGET TT_TARGET_XX
#endif

#if (TT_TARGET == TT_TARGET_XX)
  #define TT_PACKETBUFFER_NUM_PACKETS     540
#else
  #define TT_PACKETBUFFER_NUM_PACKETS     360
#endif

#include "TT_IRenderSystem.h"
#include "TT_IFontCharsMan.h"
#include "TT_IDecoder.h"
#include "TT_INavigationBarHandler.h"
#include "TT_Global.h"
#include "TT_Charset.h"

//color index
#define TT_COLOR_BLACK        0x00
#define TT_COLOR_RED          0x01
#define TT_COLOR_GREEN        0x02
#define TT_COLOR_YELLOW       0x03
#define TT_COLOR_BLUE         0x04
#define TT_COLOR_MAGENTA      0x05
#define TT_COLOR_CYAN         0x06
#define TT_COLOR_WHITE        0x07

#define TT_COLOR_TRANSPARENT  0x08
#define TT_COLOR_HALF_RED     0x09
#define TT_COLOR_HALF_GREEN   0x0A
#define TT_COLOR_HALF_YELLOW  0x0B
#define TT_COLOR_HALF_BLUE    0x0C
#define TT_COLOR_HALF_MAGENTA 0x0D
#define TT_COLOR_HALF_CYAN    0x0E
#define TT_COLOR_GREY         0x0F

#define TT_DSP_NOF_ROWS                 26
#define TT_DSP_NOF_L1_COLUMNS           40
#define TT_DSP_NOF_COLUMNS              56  /* L1 + Sidepanel */
#define TT_DSP_NOF_SIDEPANEL_COLUMNS    (TT_DSP_NOF_COLUMNS-TT_DSP_NOF_L1_COLUMNS)
#define TT_DSP_NO_OF_COLORS             38

/*
max DRCS characters
*/
///14.4.1 A page may reference any 24 of the 96 DRCS characters defined by the two sub-tables.
#define TT_DISPLAY_MAX_DRCS 24

#if 1
/* display mode */
/// draw by building bitmaps
#define TT_DISPLAY_MODE_BITMAP                  1
/// draw by character attributes
#define TT_DISPLAY_MODE_CHAR                    2

#define TT_DISPLAY_MODE                 TT_DISPLAY_MODE_BITMAP
#endif

#ifdef __cplusplus
extern "C" {
#endif

///Mainly for event handler.
///One event handler can be setup for each event.
typedef enum
{
  EVENT_HANDLER_BEFORE_UPDATE_PACGE,
  EVENT_HANDLER_ASK_FREEZE_SOURCE_INPUT,
  EVENT_HANDLER_ASK_THAW_SOURCE_INPUT,
  EVENT_HANDLER_BEFORE_ACCESS_CMD_QUEUE,
  EVENT_HANDLER_AFTER_ACCESS_CMD_QUEUE,
  EVENT_HANDLER_BEFORE_DIGEST_INPUT,
  EVENT_HANDLER_AFTER_DIGEST_INPUT,
}TT_EVENT_ID;

///The behavior configuration ID
typedef enum
{
  BEHAVIOR_CONFIG_NAVIGATION_BAR,
  BEHAVIOR_CONFIG_OVERWRITE_RENDERING_ROW,
  BEHAVIOR_CONFIG_SUBPAGE_BAR,
  BEHAVIOR_CONFIG_LISTMODE_COLORKEY_BAR,
  BEHAVIOR_CONFIG_PAGENUMBER,
  BEHAVIOR_CONFIG_UPDATE_MODE,
  BEHAVIOR_SUBTITLE_PAGE_NAVIGATION,
  BEHAVIOR_CONFIG_CANCEL_MODE,
  BEHAVIOR_CONFIG_SIZE_DISPLAY_MODE,
  BEHAVIOR_CONFIG_NAVIGATION_BAR_CONFIG,
  BEHAVIOR_CONFIG_CLOCK,
}TT_BEHAVIOR_CONFIG_ID;

///The navigation mode.
typedef enum
{
  TT_COLOR_KEY_NAVI_NONE,
  TT_COLOR_KEY_NAVI_TOP, //TOP only
  TT_COLOR_KEY_NAVI_FLOF, //FLOF only
  TT_COLOR_KEY_NAVI_FLOF_TOP, //FLOF takes the priority
  TT_COLOR_KEY_NAVI_TOP_FLOF //TOP thakes the priority
}TT_NavigationMode;

///The ID of the stcok font.
typedef enum
{
    TT_STOCK_FONT_G1_MOSAIK,
    TT_STOCK_FONT_G1_SEPARATED_MOSAIK,
    TT_STOCK_FONT_G3_SMOOTH_MOSAIK
}TT_StockFont;

///Mask bit of TT_SubpagebarConfig.
///Tells the validness of each field.
typedef enum
{
    SUBPAGEBAR_CONFIG_BG = 1 << 0,
    SUBPAGEBAR_CONFIG_ACTIVE_CYCLE_FG = 1 << 1,
    SUBPAGEBAR_CONFIG_ACTIVE_CYCLE_BG = 1 << 2,
    SUBPAGEBAR_CONFIG_INACTIVE_CYCLE_FG = 1 << 3,
    SUBPAGEBAR_CONFIG_INACTIVE_CYCLE_BG = 1 << 4,
    SUBPAGEBAR_CONFIG_ACTIVE_SUBPAGE_FG = 1 << 5,
    SUBPAGEBAR_CONFIG_ACTIVE_SUBPAGE_BG = 1 <<6,
    SUBPAGEBAR_CONFIG_INACTIVE_SUBPAGE_FG = 1 << 7,
    SUBPAGEBAR_CONFIG_INACTIVE_SUBPAGE_BG = 1 << 8,
    SUBPAGEBAR_CONFIG_VISIBLE = 1 << 9,
    SUBPAGEBAR_CONFIG_SHOWNOSUBPAGE = 1 << 10,
}TT_SubpagebarConfigFlags;

///The structre to configure the subpagebar behavior.
///TT_CustomBehaviorConfig_SetSubpagebarConfig() uses this parameter to directive the subpage bar behavior.
typedef struct
{
    ///Identify which field is valid
    TT_U32 ConfigFlags;
    ///The background color of the subpage bar
    TT_U8 SubpageBarBackground;
    ///The foreground color of the cycle symbol when it's active
    TT_U8 ActiveCycleSymbolForeground;
    ///The background color of the cycle symbol when it's active
    TT_U8 ActiveCycleSymbolBackground;
    ///The forground color of the cycle sybmole when it's inactive
    TT_U8 InactiveCycleSymbolForeground;
    ///The background color of the cycle symbole when it's inactive
    TT_U8 InactiveCycleSymbolBackground;
    ///The forground color of the active subpage
    TT_U8 ActiveSubpageForeground;
    ///The background color of the active subpage
    TT_U8 ActiveSubpageBackground;
    ///The forground color of the inactive subpage
    TT_U8 InactiveSubpageForeground;
    ///The background color of the inactive subpage
    TT_U8 InactiveSubpageBackground;
    ///make subpage bar visible or not ?
    TT_BOOL IsVisible;
    ///show "No Subpage" or not?
    TT_BOOL IsShowNoSubpage;
}TT_SubpagebarConfig;

///To config the behavior of color key bar in list mode
typedef struct
{
    ///Does the selected color key need to flash?
    TT_BOOL FlashModeForSelection;
    ///Does the color key bar in list mode show "L"
    TT_BOOL ShowListSymbol;
}TT_ListModeColorkeyBarConfig;

///To config the behavoir of displaying page number
typedef struct
{
    ///does the page number is prefixed with 'P'
    TT_BOOL PrefixWithP;
    ///does the TOP navigation bar show 'P+/P-' or '+/-'
    TT_BOOL TopPrefixWithP;
}TT_PagenumberConfig;

///To config the behavior of the update mode
typedef struct
{
    ///Decision to make after incomding page with C8 bit
    TT_BOOL IndicateC8UpdateByCancelUpdateMode;
    ///forground of the page title
    TT_U8 ForegroundNoUpdate;
    ///background of the page title
    TT_U8 BackgroundNoUpdate;
    ///foreground of the page title, only valid when IndicateC8UpdateByCancelUpdateMode==false
    TT_U8 ForegroundAfterUpdate;
    ///background of the page title, only valid when IndicateC8UpdateByCancelUpdateMode==false
    TT_U8 BackgroundAfterUpdate;
    ///show symbol or page number
    TT_BOOL DoesShowPageNumber;
}TT_UpdateModeConfig;

///To config the behavior of the cancel mode
typedef struct
{
    ///forground of the page title
    TT_U8 ForegroundNoUpdate;
    ///background of the page title
    TT_U8 BackgroundNoUpdate;
    ///show symbol or page number
    TT_BOOL DoesShowPageNumber;
}TT_CancelModeConfig;

///To config the behavior of the SUBTITLE-NAVIGATION-COMMAND
typedef struct
{
    ///do navigation circularly
    TT_BOOL NavigateCircularly;
}TT_SubtitlePageNavigationConfig;

///To config the behavior of the size display mode
typedef struct
{
    ///to set the new size display mode, use the original height of row 11 in the upper page
    TT_BOOL IsNewSizeDisplayMode;
}TT_SizeDisplayModeConfig;

///To config the behavior of the navigation bar
typedef struct
{
    ///to set TOP link content show page number or string
    TT_BOOL TopLinkShowPageNumber;
}TT_NavigationBarConfig;

///To config the clock on the page header
typedef struct
{
    ///All clock separator will show as ':'
    TT_BOOL ClockSeparatorShowAsColon;
}TT_ClockConfig;


///The commands to directive TTX engine
typedef struct
{
  ///digit input command
  void (*Digit)(TT_U32 digit);
  ///page up command
  void (*KeyUp)(TT_BOOL isSubpagePrevious);
  ///page down command
  void (*KeyDown)(TT_BOOL isSubpageNext);
  ///previous subpage command
  void (*KeyLeft)(void);
  ///new subpage command
  void (*KeyRight)(void);
  ///red button command
  void (*KeyRed)(void);
  ///green button command
  void (*KeyGreen)(void);
  ///yellow button command
  void (*KeyYellow)(void);
  ///cyan button command
  void (*KeyCyan)(void);
  ///entering update mode
  void (*KeyUpdate)(void);
  ///entering hold mode
  void (*KeyHold)(void);
  ///entering list mode
  void (*KeyList)(TT_U16 selection);
  ///go to index page
  void (*KeyIndex)(void);
  ///Larger size mode
  void (*KeySize)(void);
  ///Reveal the hiding chars
  void (*KeyReveal)(void);
  ///entering cancel mode
  void (*KeyCancel)(void);
  ///Made backgound color transparent or not
  void (*MixModeOnOff)(void);
  ///Subpage input mode on/off switch
  void (*SubpageInputOnOff)(void);
  ///Entering subtitle mode and take the <magPage,subpage> as the subtitle page
  void (*SubtitleOn)(TT_U16 magPage, TT_U16 subpage);
  ///When there is not TTX window is shown,
  ///this will entering subtitle mode and navigate through the subtitle pages in the
  ///following the same calls
  void (*SubtitleNavigationMode)(void);
  ///open TTX window and entering normal TTX mode
  void (*TTXOn)(void);
  ///Close TTX Window for whatever mode
  void (*TTXOff)(void);
  ///open TTX window and entering clock mode
  void (*ClockOn)(void);
  ///close clock mode
  void (*ClockOff)(void);
  ///open TTX window and entering status mode (show P830 text)
  void (*StatusOn)(TT_U32 posX, TT_U32 posY);
  ///close status mode
  void (*StatusOff)(void);
  ///clear memorized list(custom navigation pages) data
  void (*ClearList)(void);
  ///Setup the language set - Russian group
  void (*SetLanguageRussian)(void);
  ///Setup the language set - East Europe group
  void (*SetLanguageEast)(void);
  ///Setup the language set - Arabic group
  void (*SetLanguageArabic)(void);
  ///Setup the language set - West Europe group
  void (*SetLanguageWest)(void);
  ///Setup the language set - Farsi
  void (*SetLanguageFarsi)(void);
  ///Goto the designated page
  void (*SetPage)(TT_U32 magPage, TT_U32 subpageNum);
  ///Specify the index page
  void (*SetDTVIndexPage)(TT_U32 magNum, TT_U32 pageNum);
  ///setup the color key navigation mode
  void (*SetColorKeyMode)(TT_NavigationMode mode);
  ///Clear the internal DB
  void (*Reset)(void);
  ///Get CNI information P830/2
  TT_BOOL (*GetCNIP830_2)(TT_U8 values[2]);
  ///Get CNI information P830/1
  TT_BOOL (*GetNIP830_1)(TT_U8 values[2]);
  ///Get the subpage number
  TT_BOOL (*GetSubtitlePage)(TT_U8 index, TT_U16* magPage, TT_U16* subPage);
  ///Get the setted page numbers of the custom navigation buttons
  void (*GetListPageNums)(TT_U16* pageRed,
                          TT_U16* pageGreen,
                          TT_U16* pageYellow,
                          TT_U16* pageCyan);
  ///Setup the page number of the custom navigation buttons
  void (*SetListPageNums)(TT_U16 pageRed,
                          TT_U16 pageGreen,
                          TT_U16 pageYellow,
                          TT_U16 pageCyan);
  ///Query and get clock data from p830
  TT_BOOL (*GetClockData)(TT_U8* Hour,
                          TT_U8* Minue,
                          TT_U8* Sec);
  ///Query if there any packets in one page have the specified content
  TT_U16 (*QueryIfDataPacketWitPrefix)(TT_U16 magPage, TT_U8* rowData, TT_U16 size);
  ///open TTX window and entering PAT TTX mode
  void (*TTXOnPAT)(void);
  //Set subpage cycle shown
  void (*SetSubpageCycle)(void);
  //Set alarm clock time
  void (*SetAlarmClock)(TT_U16 time);
  //get current page subcode recently received:  for alarm page function
  TT_BOOL (*GetSubcode)(TT_U16* subcode);
  //get newsflashUpdate
  TT_BOOL (*GetNewsflashUpdate)(void);
   ///Setup the language set - Farsi
  void (*SetLanguagePrimeSecond)(TT_Charset_LG primeLanguage, TT_Charset_LG secondLanguage);
  ///Setup the language set - arabicHebrew
  void (*SetLanguageArabicHebrew)(void);
  ///Setup the language set - byelorussian
  void (*SetLanguageByelorussion)(void);
  ///Setup the title display or not on subtitle page on ttx mode
  void (*SetSubtitleTitleOnWithTTXMode)(TT_BOOL bOn);
}TT_EngineCommand;

///Query the state of the TTX engine
typedef struct
{
  ///Is it in the mix mode
  TT_BOOL (*IsMixModeActive)(void);
  ///Is it in the clock mode
  TT_BOOL (*IsClockModeActive)(void);
  ///Is it in the list mode (with custom navigation buttons)
  TT_BOOL (*IsListModeActive)(void);
  ///Is it in the cancel mode
  TT_BOOL (*IsCancelModeActive)(void);
  ///Is the displaying page with subnews attribute?
  TT_BOOL (*IsCurrentPageSubNews)(void);
  ///Are there any subtitles in the collecting data?
  TT_U32  (*DoesHaveSubtitles)(void);
  ///Are there any TTX packets incoming?
  TT_BOOL (*DoesHaveTTXSignals)(void);
  ///Are there any valid colck data from p830?
  TT_BOOL (*DoesHaveClockInfo)(void);
  ///Is there any command in the command queue?
  TT_BOOL (*IsAnyCmdInQueue)(void);
  ///Is the subpage input mode on?
  TT_BOOL (*IsSubpageInputOn)(void);
  ///Is there any subpage in the current displaying page?
  TT_BOOL (*IsSubpageAvailable)(void);
  ///Is displaying TTX ?
  TT_BOOL (*IsDisplayOpened)(void);
  ///The TTX L25 feature
  TT_BOOL (*DoesSupportSidePanel)(void);
  ///Is it in update mode
  TT_BOOL (*IsUpdateModeActive)(void);
  ///Is it in Hold mode
  TT_BOOL (*IsHoldModeActive)(void);
  ///Is it in Size mode
  TT_U8 (*IsSizeModeActive)(void);
  ///Is it show No Subpage
  TT_U8 (*IsShowNoSubpage)(void);
  ///Get the C12C13C14 values in packet header
  TT_U8 (*GetC12C13C14Values)(void);
  ///Is Reveal mode on
  TT_U8 (*IsRevealModeActive)(void);
  ///Is the displaying page is flash news?
  TT_BOOL (*IsCurrentPageFlashNews)(void);
  //Is current cycle subpage?
  TT_BOOL (*IsCurrentCycleSubpage)(void);
  //Is current multi subpage?
  TT_BOOL (*IsCurrentMultiSubpage)(void);
}TT_EngineStatus;

/**The backend feature.
*  The render taget tells the engine which mode to select when doing rendering
*/
typedef enum
{
    TT_ENGINE_DISPLAY_MODE_BITMAP,
    TT_ENGINE_DISPLAY_MODE_CHAR
}TT_EngineDisplayMode;


///The interface used to query the row/column numbers of the TTX drawing window
typedef struct
{
    ///Get number of row
    TT_U32 (*GetRowNum)(void);
    ///Get number of column
    TT_U32 (*GetColNum)(void);
}TT_EngineDisplayParams;

/// the TTX engine
typedef struct
{
  ///Start to initialate the state of each submodule
  ///memoryAddress - the buffer allocated for TTX
  ///memorySize - buffer size
  void (*Init)(TT_U32 memoryAddress, TT_U32 memorySize);
  ///Setup the rendering system (font + render target)
  void (*SetupRenderSystem)(const TT_IRenderSystem* renderSystem);
  ///Setup the event handler
  void (*SetupEventHandler)(TT_EVENT_ID which, void* handler);
  ///Setup the TTX decoder (L15 or L25)
  void (*SetupDecoder)(const TT_IDecoder* decoder);
  ///To customize the TTX behavior
  void (*SetupBehaviorConfig)(TT_BEHAVIOR_CONFIG_ID which, const void* handler);
  ///Stop doing anything, including input and output
  void (*ShutDown)(void);
  ///Do the real initialization (also called by .Init()), and
  ///restore back the states
  void (*KickOff)(void);
  ///Do decoding and displaying jobs
  void (*Heartbeat)(void);
  ///Get the rendering system (font + render target)
  TT_IRenderSystem const* (*GetRenderSystem)(void);
  ///Get the stcok font table
  TT_U8 const* (*GetStockFont)(TT_StockFont which);
  ///TTX commands
  TT_EngineCommand Commands;
  ///The interface to query the TTX engine status
  TT_EngineStatus Status;
  ///The interface to query the params of the drawing TTX
  TT_EngineDisplayParams DisplayParams;
}TT_Engine;

extern const TT_IDecoder TT_DecoderL25;
extern const TT_IDecoder TT_DecoderL15;
extern TT_Engine TT_EngineObj;
extern TT_IRenderSystem TT_BitmapRenderSystem;
extern TT_IRenderSystem TT_CharRenderSystem;
extern const TT_IBitmapFontCharsMan TT_DefaultFontCharsMan_;
extern const TT_INavigationBarHandler TT_NavigationBarHandlerFLOF_Supress_IfNoLink;
extern const TT_INavigationBarHandler TT_DefaultNavigationBarHandler;
extern const TT_INavigationBarHandler TT_NavigationBarHandlerShowInMissingPage;

#define TT_DefaultFontCharsMan ((const TT_IFontCharsMan*) &TT_DefaultFontCharsMan_)

#ifdef __cplusplus
  }
#endif

#endif

///*** please do not remove change list tag ***///
///***$Change: 519878 $***///
