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
//  Description:    EPG Timer Related Functions
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MAPP_EPG_TIMER_H
#define MAPP_EPG_TIMER_H

/******************************************************************************/
/*                              Include files                                 */
/******************************************************************************/
#include "sysinfo.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Key.h"

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
#ifdef MAPP_EPG_TIMER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#if ENABLE_PVR
    #define DTG_FREEVIEW_STANDBY    0  //only turn off LCD for freeview test item #2.7
#else
    #define DTG_FREEVIEW_STANDBY    0
#endif

// Define for Feature configuration
#define ENABLE_TIMER_LIST_FOR_REMIND    TRUE
#define ENABLE_TIMER_LIST_FOR_RECORD    FALSE

#define STYLE_EPG_TIMEUP_MSG_NONE   0
#define STYLE_EPG_TIMEUP_MSG_COUNTDOWN   1
#define EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s   1//10
#define EPG_RECORD_WAKEUP_LEADING_TIME_s 			(2* 60)//10
#define EPG_WAKEUP_LEADING_TIME_s 			15//10
#define EPG_REMINDER_TIME			 60 //1 minute

#define EPG_TIMER_TIMEUP_MSG_STYLE      STYLE_EPG_TIMEUP_MSG_COUNTDOWN //STYLE_EPG_TIMEUP_MSG_NONE

//#define EPG_TIMER_MAX_NUM           5   //Max:12 , 12 x sizeof(MS_EPG_TIMER) < 0x400
#define EPG_TIMER_FIRST_INDEX        0
#define EPG_TIMER_MAX_EVT_NAME_LEN  30

//1. (EPG_REMINDER_MAX_COUNT + EPG_RECORDER_MAX_COUNT) <= EPG_TIMER_MAX_NUM
//2. {EPG_TIMER_MAX_NUM  x  sizeof(MS_EPG_TIMER) = RM_SIZE_MANUAL_TIMER_EVENT} < SCHEDULE_LIST_LEN
#if ENABLE_DTV_EPG //for some ATV project compiler error, I really don't known what some ATV project include EPG file
  #if(SCHEDULE_LIST_LEN >= 0x1000)
    #define EPG_TIMER_MAX_NUM       25
    #define EPG_REMINDER_MAX_COUNT  5
    #define EPG_RECORDER_MAX_COUNT  20
  #else
    #define EPG_TIMER_MAX_NUM       10
    #define EPG_REMINDER_MAX_COUNT  5
    #define EPG_RECORDER_MAX_COUNT  5
  #endif
#else
    #define EPG_TIMER_MAX_NUM       10
    #define EPG_REMINDER_MAX_COUNT  5
    #define EPG_RECORDER_MAX_COUNT  5
#endif

#define EPG_REAL_USE_DB_SIZE        (sizeof(MS_EPG_TIMER) * EPG_TIMER_MAX_NUM)


#define EPG_TIMER_LIST_ITEMS_PER_PAGE   5
#define EPG_TIMER_FIRST_INDEX        0
#define EPG_TIMER_MAX_EVT_NAME_LEN  30
#define ENABLE_TIMER_PCN             0
#if ENABLE_PVR
#define EPG_TIMER_Alternate                     -1
#define EPG_TIMER_InvalidIdx                    -2
#endif
/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
typedef enum
{
    EN_MT_SOURCE_SCHED,
    EN_MT_SOURCE_TL_EDIT,
    EN_MT_SOURCE_TL_NEW,
}   EN_EPG_MT_SOURCE;

typedef enum
{
    EN_MT_DATE_EVENT,
    EN_MT_DATE_NEW,
}   EN_EPG_MT_DATE;

typedef enum
{
    EN_EPGUI_TIMER_NULL,
    EN_EPGUI_TIMER_REMINDER,
    EN_EPGUI_TIMER_RECORDER,
#if ENABLE_CI_PLUS
    ///EPG timer event type op refresh
    EN_EPGUI_TIMER_CI_OP_REFRESH,
#endif
    EN_EPGUI_TIMER_INVALID,
}   EN_EPGUI_TIMER_TYPE;

typedef enum
{
//    EN_MT_DATA_TYPE,
    EN_MT_DATA_PROG,
    EN_MT_DATA_START_HH,
    EN_MT_DATA_START_MM,
    EN_MT_DATA_REPEATMODE,
    EN_MT_DATA_DATE_DAY,
    EN_MT_DATA_DATE_MON,
    EN_MT_DATA_END_HH,
    EN_MT_DATA_END_MM,
}   EN_EPG_MANUALTIMER_DATA_FIELD;

typedef enum
{
    EN_TL_DATA_TITLE,
    EN_TL_DATA_TIME,
    EN_TL_DATA_DATE,
    EN_TL_DATA_PROG,
    EN_TL_DATA_REPEAT_MODE,
}   EN_EPG_TIMERLIST_DATA_FIELD;

typedef enum
{
    EN_TIMER_CHECK_NONE,
    EN_TIMER_CHECK_SUCCESS,
    EN_TIMER_CHECK_PAST,
    EN_TIMER_CHECK_OVERLAY,
    EN_TIMER_CHECK_ENDTIME_BEFORE_START,
    EN_TIMER_CHECK_ENDTIME_EXCEED_PERIOD,
    EN_TIMER_CHECK_FULL,
}   EN_EPG_TIMER_CHECK;

typedef enum
{
    MODE_EPGUI_TIMER_MANUAL,
    MODE_EPGUI_TIMER_LIST,
    #if ENABLE_PVR
    MODE_EPGUI_TIMER_MANUAL_RECORDER,
    MODE_EPGUI_TIMER_LIST_RECORDER,
    #endif
    MODE_EPGUI_TIMER_MAXNUM,
} EN_EPGUI_TIMER_MODE;

typedef enum
{
    EN_EPGRM_AUTO,
    EN_EPGRM_ONCE,
    EN_EPGRM_DAILY,
    EN_EPGRM_WEEKLY,
    EN_EPGRM_MAXNUM,
} EN_EPG_TIMER_REPEAT_MODE;

#if ENABLE_PVR
typedef enum
{
    EN_EPG_RECORDER_START_DATE,
    EN_EPG_RECORDER_START_TIME,
    EN_EPG_RECORDER_END_DATE,
    EN_EPG_RECORDER_END_TIME,
    EN_EPG_RECORDER_START_DATE_TIME,
    EN_EPG_RECORDER_END_DATE_TIME,
}   EN_EPG_MANUALTIMER_RECORDER_L2_DATA_FIELD;

typedef enum
{
    EN_EPG_RECORDER_START_YEAR,
    EN_EPG_RECORDER_START_MON,
    EN_EPG_RECORDER_START_DAY,
    EN_EPG_RECORDER_START_HOUR,
    EN_EPG_RECORDER_START_MIN,
}   EN_EPG_MANUALTIMER_RECORDER_DATA_FIELD;
#endif

typedef enum
{
    EN_EPGTIMER_ACT_NONE,
    EN_EPGTIMER_ACT_REMINDER,
    EN_EPGTIMER_ACT_RECORDER_START,
#if ENABLE_CI_PLUS
	EN_EPGTIMER_ACT_CI_OP_REFRESH,
#endif
}   EN_EPG_TIMER_ACT_TYPE;

typedef enum
{
    EN_EPGTIMER_STATUS_NORMAL,
    EN_EPGTIMER_STATUS_DISABLE,
}   EN_EPGTIMER_STATUS;

/******************************************************************************/
/*                                 Structure                                  */
/******************************************************************************/
typedef struct
{
    U8                  enTimerType;            // need first // EN_EPGUI_TIMER_TYPE
    U8                  enRepeatMode:3;         // EN_EPG_TIMER_REPEAT_MODE
    U8                  satus:1;                // EN_EPGTIMER_STATUS
    U8                  bNoTitle:1;             // BOOLEAN
    U8                  bRecordSplitEvent:1;    // BOOLEAN, whether record split event, PVR has to change to next split event after current record completed.
    U8                  bRecordSeriesEvent:1;   // BOOLEAN, whether record series event, PVR has to change to next split event after current record completed.
    U8                  bRecordRecomEvent:1;    // BOOLEAN, whether record recommendations event, PVR has to change to next split event after current record completed.


    ST_TIME             stStartDate;
    ST_TIME             stEndDate;
#if(ENABLE_S2_EPG_REMINDER)
    WORD                  u8PCN;
#else
	U8					  u8PCN;
#endif
    U16                 u16SrvID;
    U16                 u16EventID;         //Event ID of EIT, not Event Index
    U16                 au16EvtName[EPG_TIMER_MAX_EVT_NAME_LEN];
#if 1//(ENABLE_S2_EPG_REMINDER)
    //U8                  u8SrcIsDtvS2;
    U8                  u8UiSrcType;
#endif
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
    /// active pin code cache
    BOOL bPinCodeCached;
    /// the cached pin code of CICAM
    U16 u16CachedPinCode;
#endif
}MS_EPG_TIMER;

typedef struct
{
    U8     u8TimerIndex;   //the index of recording schedule,
                           //indicate the recording index of _pstEpgTimer[],
                           //0xFF : means NULL.  (TIMER_END_INDEX_NULL)
                           //0xFE : means trigger by USER(REC key) (TIMER_END_INDEX_USER)
    U8     u8RecordPath;   //0xFF : means NULL
    U8     u8PfVersion;    //0xFF : means NULL, for DTR runaway
}MS_EPGTIMER_RECORDING_QUEUE;

#define EPGTIMER_REC_QUEUE_NUMBER PVR_MAX_RECORD_PATH
#define EPGTIMER_INDEX_NULL    0xFF   //Empty
#define EPGTIMER_INDEX_USER    0xFE   //Trigger by user press REC key

#define EPGTIMER_REC_PATH_UNKNOWN 0xFE  //add Record queue, but not get the record path yet
typedef struct
{    // for UI display
    U8                              u8CurTimerIdx;      // item index, 0~ EPG_RECORDER_MAX_COUNT
    EN_EPG_MT_SOURCE                enMTSOURCE;         // 3 possible entries to manual timer
    MS_EPG_TIMER                    stEpgTimer; // One buffered TimerSetting used in UI operation
}MS_EPG_TIMER_PARAM;

#if (ENABLE_DTV_EPG)
/******************************************************************************/
/* Color definition - Background, Frame, Text, Line                           */
/******************************************************************************/
// Manual Timer                             -> Colors - Background, Text
#define EPG_MANUAL_TIMER_COLOR_BG           EPG_COLOR_BG
#define EPG_MANUAL_TIMER_COLOR_TITLE        EPG_COLOR_TEXT
#define EPG_MANUAL_TIMER_COLOR_CONCAVE      0xDFDFDF
#define EPG_MANUAL_TIMER_COLOR_SEL          EPG_M_FOCEVENT_COLOR_BG
#define EPG_MANUAL_TIMER_COLOR_HELP_BG      EPG_HELPER_COLOR_BG

// Timer List                               -> Colors - Background, Text
#define EPG_TIMER_LIST_COLOR_BG             EPG_COLOR_BG
#define EPG_TIMER_LIST_COLOR_HELP_BG        EPG_HELPER_COLOR_BG
#define EPG_TIMER_LIST_DATA_TITLE_COLOR_BG  EPG_M_TIME_DOWN_COLOR_BG
#define EPG_TIMER_LIST_DATA_COLOR_BG_UNSEL  EPG_MANUAL_TIMER_COLOR_CONCAVE

/******************************************************************************/
/* Dimension definition - (x, y, w, h) or (x1, y1, x2, y2)                    */
/******************************************************************************/
#define EPG_TIMER_W  550
#define EPG_TIMER_ITEM_H  46
#define EPG_TIMER_TOP_BAR_H   120
#define EPG_TIMER_H   (EPG_TIMER_TOP_BAR_H+288)
#define EPG_TIMER_START_X ((NEWUI_EPG_GWIN_WIDTH-EPG_TIMER_W)/2)
#define EPG_TIMER_START_Y   100
#define EPG_TIMER_BOTTOM_Y  (EPG_TIMER_H+19)

#define EPG_TIMER_BG_X 17
#define EPG_TIMER_ITEM_OPTION_X  200
#define EPG_TIMER_ITEM_OPTION_W  (EPG_TIMER_W - EPG_TIMER_ITEM_OPTION_X)

#define EPG_TIMER_WARNING_DLG_X (( PANEL_WIDTH - NEWUI_DEFAULT_POPUP_DIALOG_GWIN_WIDTH ) / 2)
#define EPG_TIMER_WARNING_DLG_Y (( PANEL_HEIGHT - NEWUI_DEFAULT_POPUP_DIALOG_GWIN_HEIGHT ) / 2)
#define EPG_TIMER_WARNING_DLG_W NEWUI_DEFAULT_POPUP_DIALOG_GWIN_WIDTH
#define EPG_TIMER_WARNING_DLG_H NEWUI_DEFAULT_POPUP_DIALOG_GWIN_HEIGHT

// == MANUAL TIMER PAGE ==
// Manual Timer Group                       -> Dimensions - (x, y, w, h), row number
#define EPG_MANUAL_TIMER_START_X            EPG_START_X
#define EPG_MANUAL_TIMER_START_Y            (EPG_HELPER_Y-EPG_MANUAL_TIMER_PAGE_BG_HEIGHT)
#define EPG_MANUAL_TIMER_PAGE_WIDTH         EPG_WIDTH
#define EPG_MANUAL_TIMER_PAGE_HEIGHT        (EPG_MANUAL_TIMER_PAGE_BG_HEIGHT+EPG_HELPER_HEIGHT)

#define EPG_MANUAL_TIMER_PAGE_BG_WIDTH      EPG_MANUAL_TIMER_PAGE_WIDTH
#define EPG_MANUAL_TIMER_PAGE_BG_HEIGHT     272
#define EPG_MANUAL_TIMER_PAGE_BG_RADIUS     0

#define EPG_MANUAL_TIMER_TITLE_TEXT_X       100
#define EPG_MANUAL_TIMER_TITLE_TEXT_Y       (66-EPG_FONT_XL_HEIGHT)
#define EPG_MANUAL_TIMER_TITLE_TEXT_WIDTH   EPG_TITLE_WIDTH
#define EPG_MANUAL_TIMER_TITLE_TEXT_HEIGHT  EPG_FONT_XL_HEIGHT

#define EPG_MANUAL_TIMER_CLOCK_X            (EPG_MANUAL_TIMER_TITLE_TEXT_X+EPG_MANUAL_TIMER_TITLE_TEXT_WIDTH)
#define EPG_MANUAL_TIMER_CLOCK_Y            (66-EPG_FONT_M_HEIGHT)
#define EPG_MANUAL_TIMER_CLOCK_WIDTH        EPG_CLOCK_WIDTH
#define EPG_MANUAL_TIMER_CLOCK_HEIGHT       EPG_FONT_M_HEIGHT

#define EPG_MANUAL_TIMER_DATA_TITLE_TEXT_Y       (148-EPG_FONT_L_HEIGHT)
#define EPG_MANUAL_TIMER_DATA_TITLE_TEXT_HEIGHT  EPG_FONT_L_HEIGHT

#define EPG_MANUAL_TIMER_DATA_BLOCK_RADIUS  0
#define EPG_MANUAL_TIMER_DATA_Y_OFFSET      17
#define EPG_MANUAL_TIMER_DATA_Y             (EPG_MANUAL_TIMER_START_Y+EPG_MANUAL_TIMER_CONCAVE_Y-EPG_MANUAL_TIMER_DATA_Y_OFFSET)

#define EPG_MANUAL_TIMER_CONCAVE_Y          176
#define EPG_MANUAL_TIMER_CONCAVE_WIDTH      //
#define EPG_MANUAL_TIMER_CONCAVE_HEIGHT     EPG_UNIT_1X_EVENT_HEIGHT
#define EPG_MANUAL_TIMER_CONCAVE_GAP        8
#define EPG_MANUAL_TIMER_CONCAVE1_X         EPG_MANUAL_TIMER_TITLE_TEXT_X
#define EPG_MANUAL_TIMER_CONCAVE1_WIDTH     205
#define EPG_MANUAL_TIMER_CONCAVE2_X         (EPG_MANUAL_TIMER_CONCAVE1_X+EPG_MANUAL_TIMER_CONCAVE1_WIDTH+EPG_MANUAL_TIMER_CONCAVE_GAP)
#define EPG_MANUAL_TIMER_CONCAVE2_WIDTH     349
#define EPG_MANUAL_TIMER_CONCAVE3_X         (EPG_MANUAL_TIMER_CONCAVE2_X+EPG_MANUAL_TIMER_CONCAVE2_WIDTH+EPG_MANUAL_TIMER_CONCAVE_GAP)
#define EPG_MANUAL_TIMER_CONCAVE3_WIDTH     220
#define EPG_MANUAL_TIMER_CONCAVE4_X         (EPG_MANUAL_TIMER_CONCAVE3_X+EPG_MANUAL_TIMER_CONCAVE3_WIDTH+EPG_MANUAL_TIMER_CONCAVE_GAP)
#define EPG_MANUAL_TIMER_CONCAVE4_WIDTH     180
#define EPG_MANUAL_TIMER_CONCAVE5_X         (EPG_MANUAL_TIMER_CONCAVE4_X+EPG_MANUAL_TIMER_CONCAVE4_WIDTH+EPG_MANUAL_TIMER_CONCAVE_GAP)
#define EPG_MANUAL_TIMER_CONCAVE5_WIDTH     180

#define EPG_MANUAL_TIMER_HELPER_X           0
#define EPG_MANUAL_TIMER_HELPER_Y           EPG_MANUAL_TIMER_PAGE_BG_HEIGHT
#define EPG_MANUAL_TIMER_HELPER_BG_WIDTH    EPG_MANUAL_TIMER_PAGE_WIDTH
#define EPG_MANUAL_TIMER_HELPER_BG_HEIGHT   EPG_HELPER_HEIGHT
#define EPG_MANUAL_TIMER_HELPER_WIDTH       EPG_HELPER_ITEM_WIDTH       //per item
#define EPG_MANUAL_TIMER_HELPER_HEIGHT      43
#define EPG_MANUAL_TIMER_HELPER_ICON1_X     (110+2*EPG_MANUAL_TIMER_HELPER_WIDTH)
#define EPG_MANUAL_TIMER_HELPER_ICON2_X     (EPG_MANUAL_TIMER_HELPER_ICON1_X+EPG_MANUAL_TIMER_HELPER_WIDTH)
#define EPG_MANUAL_TIMER_HELPER_ICON_Y      (EPG_MANUAL_TIMER_HELPER_Y+10)


// == TIMER LIST PAGE ==
// Timer List Group                         -> Dimensions - (x, y, w, h), row number
#define EPG_TIMER_LIST_START_X              EPG_START_X
#define EPG_TIMER_LIST_START_Y              EPG_START_Y
#define EPG_TIMER_LIST_PAGE_WIDTH           EPG_BODY_WIDTH
#define EPG_TIMER_LIST_PAGE_HEIGHT          EPG_HEIGHT

#define EPG_TIMER_LIST_PAGE_BG_WIDTH        EPG_TIMER_LIST_PAGE_WIDTH
#define EPG_TIMER_LIST_PAGE_BG_HEIGHT       EPG_BODY_HEIGHT

#define EPG_TIMER_LIST_TITLE_TEXT_X         (EPG_TITLE_X-EPG_START_X)
#define EPG_TIMER_LIST_TITLE_TEXT_Y         (EPG_TITLE_Y-EPG_START_Y)
#define EPG_TIMER_LIST_TITLE_TEXT_WIDTH     EPG_TITLE_WIDTH
#define EPG_TIMER_LIST_TITLE_TEXT_HEIGHT    EPG_TITLE_HEIGHT

#define EPG_TIMER_LIST_DATA_TITLE_START_X   EPG_M_BODY_SRV_X_GAP
#define EPG_TIMER_LIST_DATA_TITLE_START_Y   142
#define EPG_TIMER_LIST_DATA_TITLE_WIDTH     (EPG_TIMER_LIST_PAGE_BG_WIDTH-2*EPG_M_BODY_SRV_X_GAP)
#define EPG_TIMER_LIST_DATA_TITLE_HEIGHT    52
#define EPG_TIMER_LIST_DATA_TITLE1_START_X  EPG_TIMER_LIST_DATA_TITLE_START_X
#define EPG_TIMER_LIST_DATA_TITLE1_WIDTH    420
#define EPG_TIMER_LIST_DATA_TITLE2_START_X  (EPG_TIMER_LIST_DATA_TITLE1_START_X+EPG_TIMER_LIST_DATA_TITLE1_WIDTH)
#define EPG_TIMER_LIST_DATA_TITLE2_WIDTH    100
#define EPG_TIMER_LIST_DATA_TITLE3_START_X  (EPG_TIMER_LIST_DATA_TITLE2_START_X+EPG_TIMER_LIST_DATA_TITLE2_WIDTH)
#define EPG_TIMER_LIST_DATA_TITLE3_WIDTH    180
#define EPG_TIMER_LIST_DATA_TITLE4_START_X  (EPG_TIMER_LIST_DATA_TITLE3_START_X+EPG_TIMER_LIST_DATA_TITLE3_WIDTH)
#define EPG_TIMER_LIST_DATA_TITLE4_WIDTH    320
#define EPG_TIMER_LIST_DATA_TITLE5_START_X  (EPG_TIMER_LIST_DATA_TITLE4_START_X+EPG_TIMER_LIST_DATA_TITLE4_WIDTH)
#define EPG_TIMER_LIST_DATA_TITLE5_WIDTH    137

#if ENABLE_PVR
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE_START_X   (EPG_M_BODY_SRV_X_GAP+25)
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE_START_Y   142
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE_WIDTH     EPG_TIMER_LIST_PAGE_BG_WIDTH
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE_HEIGHT    52
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE1_START_X  EPG_TIMER_LIST_RECORDER_DATA_TITLE_START_X
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE1_WIDTH    300
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE2_START_X  (EPG_TIMER_LIST_RECORDER_DATA_TITLE1_START_X+EPG_TIMER_LIST_RECORDER_DATA_TITLE1_WIDTH)
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE2_WIDTH    210
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE3_START_X  (EPG_TIMER_LIST_RECORDER_DATA_TITLE2_START_X+EPG_TIMER_LIST_RECORDER_DATA_TITLE2_WIDTH)
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE3_WIDTH    220
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE4_START_X  (EPG_TIMER_LIST_RECORDER_DATA_TITLE3_START_X+EPG_TIMER_LIST_RECORDER_DATA_TITLE3_WIDTH)
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE4_WIDTH    270
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE5_START_X  (EPG_TIMER_LIST_RECORDER_DATA_TITLE4_START_X+EPG_TIMER_LIST_RECORDER_DATA_TITLE4_WIDTH)
#define EPG_TIMER_LIST_RECORDER_DATA_TITLE5_WIDTH    (PANEL_WIDTH-EPG_TIMER_LIST_RECORDER_DATA_TITLE5_START_X)
#endif

#define EPG_TIMER_LIST_SEL_DESC_START_X     (EPG_START_X+EPG_TIMER_LIST_DATA_TITLE_START_X)
#define EPG_TIMER_LIST_SEL_DESC_START_Y     (EPG_START_Y-EPG_FONT_M_HEIGHT+150)
#define EPG_TIMER_LIST_SEL_DESC_WIDTH       (EPG_TIMER_LIST_PAGE_WIDTH-2*EPG_M_BODY_SRV_X_GAP)
#define EPG_TIMER_LIST_SEL_DESC_HEIGHT      EPG_FONT_M_HEIGHT
#define EPG_TIMER_LIST_SEL_TVMARK_WIDTH     42

#define EPG_TIMER_LIST_TIMERX_START_X       EPG_TIMER_LIST_START_X
#define EPG_TIMER_LIST_TIMERX_HEIGHT        EPG_M_EVENT_HEIGHT
#define EPG_TIMER_LIST_TIMER1_START_Y       (EPG_TIMER_LIST_DATA_TITLE_START_Y+EPG_START_Y+EPG_TIMER_LIST_DATA_TITLE_HEIGHT)
#define EPG_TIMER_LIST_TIMER2_START_Y       (EPG_TIMER_LIST_TIMER1_START_Y+EPG_TIMER_LIST_TIMERX_HEIGHT)
#define EPG_TIMER_LIST_TIMER3_START_Y       (EPG_TIMER_LIST_TIMER2_START_Y+EPG_TIMER_LIST_TIMERX_HEIGHT)
#define EPG_TIMER_LIST_TIMER4_START_Y       (EPG_TIMER_LIST_TIMER3_START_Y+EPG_TIMER_LIST_TIMERX_HEIGHT)
#define EPG_TIMER_LIST_TIMER5_START_Y       (EPG_TIMER_LIST_TIMER4_START_Y+EPG_TIMER_LIST_TIMERX_HEIGHT)
#define EPG_TIMER_LIST_TIMER6_START_Y       (EPG_TIMER_LIST_TIMER5_START_Y+EPG_TIMER_LIST_TIMERX_HEIGHT)
#define EPG_TIMER_LIST_TIMER_ICON_WIDTH     78

#define EPG_TIMER_TITLE_CLOCK_BG_X    ((EPG_TIMER_W - EPG_CLOCK_WIDTH)/2-EPG_TIMER_BG_X+20)
#define EPG_TIMER_TITLE_CLOCK_BG_Y    (82)
#define EPG_TIMER_TITLE_CLOCK_BG_W   (EPG_CLOCK_WIDTH)
#define EPG_TIMER_TITLE_CLOCK_BG_H    (EPG_CLOCK_HEIGHT+5)
#define EPG_TIMER_TITLE_CLOCK_BG_R    ((EPG_CLOCK_HEIGHT/2)-2)

#define EPG_TIMER_LIST_TITLE_CLOCK_BG_X    ((EPG_WIDTH - EPG_CLOCK_WIDTH)/2-EPG_START_X)
#define EPG_TIMER_LIST_TITLE_CLOCK_BG_Y    (EPG_CLOCK_Y-EPG_START_Y)
#define EPG_TIMER_LIST_TITLE_CLOCK_BG_W    (EPG_CLOCK_WIDTH-10)
#define EPG_TIMER_LIST_TITLE_CLOCK_BG_H    (EPG_CLOCK_HEIGHT+5)

/******************************************************************************/
/* Variable Declarations                                                      */
/******************************************************************************/
INTERFACE   MS_EPG_TIMER_PARAM  stEpgTimerParam;
INTERFACE   U8  g_TimerList_CurPageStartItem;
INTERFACE   U8 tmpTimerListIdx[EPG_TIMER_MAX_NUM];

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/
#define MApp_EpgUI_GetNumOfTimers()             (MApp_EpgTimer_GetEmptyTimerIdx())
#define MApp_EpgUI_SetManualTimerSource(x)      (stEpgTimerParam.enMTSOURCE=x)
#define MApp_EpgUI_SetTimerListCurIdx(x)        (stEpgTimerParam.u8CurTimerIdx=x)
#define MApp_EpgTimer_GetCurrentTimerIdx()        (stEpgTimerParam.u8CurTimerIdx)

INTERFACE U32       MApp_EpgTimer_GetScheduleListBufAddr( void );
INTERFACE void      MApp_EpgTimer_InitTimerSettings( BOOLEAN bScanEnd );
INTERFACE void      MApp_EpgTimer_LoadManualTimer( EN_EPGUI_TIMER_TYPE enTimerType );
INTERFACE EN_EPG_TIMER_CHECK MApp_EpgTimer_SaveTimerSetting( void );
INTERFACE void      MApp_EpgTimer_DelCurTimerListItem( U8 u8Idx );
INTERFACE U16       MApp_EpgTimer_CalDaysByMon( U8 u8Mon );
INTERFACE BOOLEAN   MApp_EpgTimer_IsTimerExistByIdx( U8 u8TimerListIdx );
INTERFACE BOOLEAN   MApp_EpgTimer_IsPrInTimerList( MEMBER_SERVICETYPE enServiceType, U16 u16ServicePosition );
INTERFACE BOOLEAN   MApp_EpgTimer_IsReminderListFull( void );
INTERFACE U8        MApp_EpgTimer_GetEmptyTimerIdx( void );
INTERFACE void      MApp_EpgTimer_ManualTimerMonitor( void );
INTERFACE void      MApp_EpgTimer_ManualTimer_Init(void);
INTERFACE BOOLEAN MApp_EpgTimer_CheckOnTimeReminder(void);

INTERFACE void      MApp_EpgTimer_ChangeMovedPositionIn(U16 u16PrevPosition, U16 u16ChangedPosition);
INTERFACE U32 MApp_EpgTimer_GetCountDown_s(void);
INTERFACE void MApp_EpgTimer_ExecTimerUpAct(U8 u8TimeUpIndex);
INTERFACE void MApp_EpgTimer_ReconfigTimerFromList(U32 u32TimeActing);
INTERFACE void MApp_EpgTimer_DelPastTimeAndNoDeviceCurItems(U32 u32TimeActing );
#endif

INTERFACE BOOLEAN _MApp_EpgTimer_Initdata( void );
INTERFACE void MApp_EpgTimer_TimerList_UI_Init(void);
INTERFACE U8 MApp_EpgTimer_GetTimerListItemsTotal(EN_EPGUI_TIMER_TYPE timerType);
INTERFACE U8 MApp_EpgTimer_GetNextStartUpIndex(void);

INTERFACE BOOLEAN MApp_EpgTimer_IsRecorderListFull(U8 *u8RecorderNumInList);
INTERFACE EN_EPG_TIMER_ACT_TYPE MApp_EpgTimer_GetTimerActType(void);

INTERFACE void MApp_EpgTimer_ResetStopppedTimerListItem(U8 ItemIndex );

INTERFACE U8 MApp_EpgTimer_GetTimerListPageItemsTotal(EN_EPGUI_TIMER_TYPE timerType);
INTERFACE U8 MApp_EpgTimer_GetIdxFromTimerDBIdx(EN_EPGUI_TIMER_TYPE timerType);
INTERFACE U8 MApp_EpgTimer_GetTimerDBIdxFromIdx(U8 u8Idx);
INTERFACE void MApp_EpgTimer_initTmpTimerListIdx(void);
INTERFACE U8 MApp_EpgTimer_GetTmpArrayIdTotal(void);
INTERFACE BOOLEAN MApp_EpgTimer_AddEpgEvent(MS_EPG_TIMER* pEpgTimerEvent);

INTERFACE MS_EPG_TIMER* MApp_Get_EPG_Timer_pstEpgTimer(void);

#if ENABLE_PVR
    INTERFACE void MApp_EpgTimer_CheckRecordEndTime(U32 u32TimeActing);
    INTERFACE U8   MApp_EpgTimer_RecordQueueAdd(U8 ItemIndex, U8 RecPath);
    INTERFACE void MApp_EpgTimer_RecordQueueSetPath(U8 ItemIndex, U8 RecPath);
    INTERFACE void MApp_EpgTimer_RecordQueueDel(U8 RecPath);
    INTERFACE void MApp_EpgTimer_SetStartingIndex(U8 Index);
    INTERFACE void MApp_EpgTimer_ClearStartingIndex(void);
    INTERFACE U8   MApp_EpgTimer_GetStartingIndex(void);
    INTERFACE BOOLEAN MApp_EpgTimer_IsTriggerByTimer(void);
    INTERFACE BOOLEAN MApp_EpgTimer_GetStartingEventName(U16 * pEventName);
//    INTERFACE BOOLEAN MApp_EpgTimer_RecordQueueIsFull(void);
    INTERFACE BOOLEAN _MApp_EpgTimer_GetValidAlternate(void);
    INTERFACE MS_EPG_TIMER_PARAM MApp_Get_EPG_Timer_Alternate(void);
    INTERFACE MS_EPG_TIMER_PARAM MApp_Get_EPG_Timer_stEpgTimerParam(void);
    INTERFACE S8 MApp_Get_EPG_Timer_pstAlternate_Index(void);
#endif  //#if ENABLE_PVR

#undef INTERFACE
#endif /* MAPP_EPG_TIMER_H */

