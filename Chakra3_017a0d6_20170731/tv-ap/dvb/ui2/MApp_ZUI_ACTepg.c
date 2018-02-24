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

#define MAPP_ZUI_ACTEPG_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal
#define FBLMSG(fmt, args...) //printf("[MApp_Scaler][%5d]" fmt, __LINE__, ## args)

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

// Common Definition
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"

#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "apiGOP.h"

#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_audio.h"
#include "msAPI_OSD.h"
#include "msAPI_Power.h"
#if ENABLE_TTX
#include "msAPI_TTX.h"
#endif
#include "msAPI_Timer.h"

#if (ENABLE_DTV_EPG)
#include "MApp_ChannelList.h"
#include "ZUI_exefunc.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTepg.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_GlobalFunction.h"

#include "mapp_epgdb_public.h"
#include "MApp_UiEpg.h"
#include "MApp_EpgTimer.h"
#include "MApp_GlobalVar.h"
#include "mapp_demux.h"
#include "MApp_Audio.h"
#include "MApp_ChannelChange.h"
#include "MApp_UiMenuDef.h"
#include "mapp_si.h"
#include "mapp_eit.h"
#include "MApp_PCMode.h"
#include "MApp_TopStateMachine.h"
#include "MApp_XC_Sys.h"
#if (ENABLE_ATSC || ENABLE_DVBS)
#include "msAPI_FreqTableDTV.h"
#endif
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#include "msAPI_MHEG5.h"
#endif
#include "mapp_si_util.h"
#if ENABLE_PVR
#include "MApp_PVR.h"
#include "MApp_UiPvr.h"
#include "MApp_Playback.h"
#include "MApp_TimeShift.h"
#if (ENABLE_EPG_MUX)
#include "msAPI_FreqTableDTV.h"
#endif
#if(ENABLE_CI_PLUS)
#include "MApp_CIMMI.h"
#endif
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_CIPVR_Adaption.h"              //For pvr
#endif
extern BOOLEAN MApp_EpgTimer_CheckEventInTimerlist(U32 EventStart, U32 EventEnd, U16 stEvtID);
extern BOOLEAN MApp_ZUI_ACT_PVR_Check_Switch_Channel(MEMBER_SERVICETYPE NewCMType, U16 u16NewPos);
static HWND EpgPvrSaveNewFocus;
U8 u8PvrWarningMsgType = 0;
#endif
#if (ENABLE_ATSC || ENABLE_DVBS)
#include "MApp_SignalMonitor.h"
#endif
static MS_EPG_TIMER* _pstEpgTimer ;
#if (ENABLE_EPG_MUX)
static U8   EPG_RFIndex=INVALID_PHYSICAL_CHANNEL_NUMBER;
static BOOL s_bBarkerlinkageEnterFlag=FALSE;
static U8 EPG_ServiceType=0; // backup service type, consider for EPG priority shall change service type.
BOOLEAN g_bReadyForExitBarkerEPG=FALSE;
extern BOOLEAN bStopMonitorBlock;
#endif
#if (ENABLE_ARABIC_OSD)
extern BOOLEAN ArabicCHStringFlag;
#endif

#if ENABLE_EPG_INFO_DISP_GENRE_TYPE
extern U16 MApp_GetGenreTypeString(U8 u8NibbleLevel1, U8 u8NibbleLevel2);
#endif

//////////////////////////////////////////////////////////////////////
extern U16 _MApp_ZUI_ACT_PasswordConvertToSystemFormat(U16 password);


// Feature Definitions
#define EPG_FOR_HALF_HOUR           TRUE
#define NEW_UI_FOR_TRUNK            FALSE//TRUE
#define ADD_EVENT_BYCHANGEPAGE      FALSE

#define HALFHOUR_PER_PAGE           1
#define SERVICE_PER_PAGE            8
#define SCHEDULE_LIST_PER_PAGE      4
#define EPG_PAGE_DURATION           (HALFHOUR_PER_PAGE*SECONDS_PER_HALF_HOUR)
#define EPG_FULL_PORGRAM_DRAWN      0x3F
#define INVALID_SEG_NUM             0xFF
#define INVALID_INSERT_POSITION     0xFF
#define EPGUI_UPDATE_PERIOD         5000
#define MAX_PAGE_EVENTS_IN_SERVICE  8
#define MAX_CHANNEL_EVENTS          512
#define MAX_INFO_STRING_LENGTH      1024//(EIT_SCHE_EXT_STR_BUF_LEN/2)//8k/2
#define MAX_INFO_UNIT_LENGTH        256//512

/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
typedef enum
{
    MODE_EPGUI_EVENT_SCHEDULE,
    MODE_EPGUI_EVENT_NOWNEXT,
    MODE_EPGUI_EVENT_MAXNUM,
} EN_EPGUI_EVENT_MODE;

typedef enum
{
    TIMER_SAVE_RESULT_PAST,
    TIMER_SAVE_RESULT_OVERLAY,
    TIMER_SAVE_RESULT_SUCCESS,
    TIMER_DTG_SERIES_CHECK,
    TIMER_DTG_SPLIT_CHECK,
}EN_TIMER_SAVE_RESULT;

typedef enum
{
    MODE_EPGUI_PROGRAMGUIDE_TIME,
    MODE_EPGUI_PROGRAMGUIDE_CHANNEL,
} EN_EPGUI_PROGRAMGUIDE_MODE;

/******************************************************************************/
/*                               Structure                                    */
/******************************************************************************/
typedef struct
{
    U32 SystemTime;
    U32 PageStartTime;
    U32 PageEndTime;
    U32 EventStart;
    U32 EventEnd;
} MS_EPG_UI_TIME;

typedef struct
{
    U8      ListEvtCnt;
    U16     ListEvt[MAX_PAGE_EVENTS_IN_SERVICE];
} MS_EPG_UI_SCHE_OSD;

typedef struct
{
    U16     ListEvtCnt;
    U16     ListEvtIndex;
    U16     ListEvt[MAX_CHANNEL_EVENTS];
}MS_EPG_UI_Channel_Event;
typedef struct
{
    MEMBER_SERVICETYPE enSvt;
    U16 u16Service;         // Start from 0
    U8  u8UiSrvIdx;        // [0...SERVICE_PER_PAGE]

    U8  u8Page;
    U8  ListEvtIdx;         // the array index of ListEvt[ ]
    U16 PoolEvtIdx;         // event index in event pool, only use for switch time
} MS_EPG_UI_FOCUS;

typedef struct
{
    U16 u16TotalService;
    U8  u8TotalPage;
    //ZUI: U8  u8HasDrawn;         // 0~6 for program
} MS_EPG_UI_SERVICE;


/******************************************************************************/
/* Variable Declarations                                                      */
/******************************************************************************/
#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

U8                             _u8InfoScrollLineCount;
static U8                      _u8ScheduleStartingIdx;

extern U16                     u16RecordOnePageByte[12];

#if ADD_EVENT_BYCHANGEPAGE
    static U8                      _u8EpgChannelPageCount;
#endif
#if ENABLE_DVB

static BOOL _bChannelChagne ;
static MS_EPG_UI_TIME           stTime;
static MS_EPG_UI_SCHE_OSD       astScheOSD[SERVICE_PER_PAGE];
static U16                      au16SrvListOSD[SERVICE_PER_PAGE];
static MS_EPG_UI_Channel_Event  u16ChannelEvtList;
static MS_EPG_UI_FOCUS          stFocus;
static MS_EPG_UI_FOCUS          stOldFocus;
static MS_EPG_UI_SERVICE        stService;
static EN_TIMER_SAVE_RESULT     _timer_popup_type;
static EN_EPGUI_PROGRAMGUIDE_MODE _Current_ProgramGuide_Mode;
static U8                      _u8InfoScrollLineCount_Pre;

////////////////////////////    //////////////////////////////////////////
static  HWND _ZUI_TBLSEG _ChannelItemTimeHwndList[MAX_PAGE_EVENTS_IN_SERVICE]=
{
    HWND_EPG_CHANNELITEM1_TIME,
    HWND_EPG_CHANNELITEM2_TIME,
    HWND_EPG_CHANNELITEM3_TIME,
    HWND_EPG_CHANNELITEM4_TIME,
    HWND_EPG_CHANNELITEM5_TIME,
    HWND_EPG_CHANNELITEM6_TIME,
    HWND_EPG_CHANNELITEM7_TIME,
    HWND_EPG_CHANNELITEM8_TIME,
};
static U8 _MApp_ZUI_ACT_EpgChanneltemTimeWindowMapToIndex(HWND hwnd)
{

    U8 i;

    for (i = 0; i < MAX_PAGE_EVENTS_IN_SERVICE; i++)
    {
        if (hwnd == _ChannelItemTimeHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_ChannelItemTimeHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}
#if 0 //Not Used yet
static HWND _MApp_ZUI_ACT_EpgChannelItemTimeIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= MAX_PAGE_EVENTS_IN_SERVICE)
        return HWND_INVALID;
    return _ChannelItemTimeHwndList[u8Index];
}
#endif

static  HWND _ZUI_TBLSEG _ChannelItemEventHwndList[MAX_PAGE_EVENTS_IN_SERVICE]=
{
    HWND_EPG_CHANNELITEM1_EVENT,
    HWND_EPG_CHANNELITEM2_EVENT,
    HWND_EPG_CHANNELITEM3_EVENT,
    HWND_EPG_CHANNELITEM4_EVENT,
    HWND_EPG_CHANNELITEM5_EVENT,
    HWND_EPG_CHANNELITEM6_EVENT,
    HWND_EPG_CHANNELITEM7_EVENT,
    HWND_EPG_CHANNELITEM8_EVENT,
};
static U8 _MApp_ZUI_ACT_EpgChanneltemEventWindowMapToIndex(HWND hwnd)
{

    U8 i;

    for (i = 0; i < MAX_PAGE_EVENTS_IN_SERVICE; i++)
    {
        if (hwnd == _ChannelItemEventHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_ChannelItemEventHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}
#if 0 //Not Used yet
static HWND _MApp_ZUI_ACT_EpgChannelItemEventIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= MAX_PAGE_EVENTS_IN_SERVICE)
        return HWND_INVALID;
    return _ChannelItemEventHwndList[u8Index];
}
#endif

static  HWND _ZUI_TBLSEG _TimeItemServiceHwndList[SERVICE_PER_PAGE]=
{
    HWND_EPG_TIMEITEM1_SERVICE,
    HWND_EPG_TIMEITEM2_SERVICE,
    HWND_EPG_TIMEITEM3_SERVICE,
    HWND_EPG_TIMEITEM4_SERVICE,
    HWND_EPG_TIMEITEM5_SERVICE,
    HWND_EPG_TIMEITEM6_SERVICE,
    HWND_EPG_TIMEITEM7_SERVICE,
    HWND_EPG_TIMEITEM8_SERVICE,
};

static U8 _MApp_ZUI_ACT_EpgTimeItemServiceWindowMapToIndex(HWND hwnd)
{

    U8 i;

    for (i = 0; i < SERVICE_PER_PAGE; i++)
    {
        if (hwnd == _TimeItemServiceHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_TimeItemServiceHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_EpgTimeItemServiceIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= SERVICE_PER_PAGE)
        return HWND_INVALID;
    return _TimeItemServiceHwndList[u8Index];
}

static  HWND _ZUI_TBLSEG _ProGuideTimeItemHwndList[SERVICE_PER_PAGE]=
{
    HWND_EPG_PRO_GUIDE_TIME_ITEM_1,
    HWND_EPG_PRO_GUIDE_TIME_ITEM_2,
    HWND_EPG_PRO_GUIDE_TIME_ITEM_3,
    HWND_EPG_PRO_GUIDE_TIME_ITEM_4,
    HWND_EPG_PRO_GUIDE_TIME_ITEM_5,
    HWND_EPG_PRO_GUIDE_TIME_ITEM_6,
    HWND_EPG_PRO_GUIDE_TIME_ITEM_7,
    HWND_EPG_PRO_GUIDE_TIME_ITEM_8,
};

static  HWND _ZUI_TBLSEG _ProGuideChannelItemHwndList[SERVICE_PER_PAGE]=
{
    HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_1,
    HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_2,
    HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_3,
    HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_4,
    HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_5,
    HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_6,
    HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_7,
    HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_8,
};
static U8 _MApp_ZUI_ACT_EpgProGuideTimeItemMapToIndex(HWND hwnd)
{

    U8 i;
    for (i = 0; i < SERVICE_PER_PAGE; i++)
    {
        if (hwnd == _ProGuideTimeItemHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_ProGuideTimeItemHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_EpgProGuideTimeItemIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= SERVICE_PER_PAGE)
        return HWND_INVALID;
    return _ProGuideTimeItemHwndList[u8Index];
}
static HWND _MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= SERVICE_PER_PAGE)
        return HWND_INVALID;
    return _ProGuideChannelItemHwndList[u8Index];
}
#endif
/////////////////////////////////////////////////////////////////////
// from MApp_Epg_Public.c

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
// Debug message
#define     DBG_STATE       0x01
#define     DBG_FOCUS       0x02
#define     DBG_EED         0x04
#define     DBG_PF          0x08
#define     DBG_INFO        0x10
#define     DBG_HANDLER     0x20
#define     DBG_TIMER       0x40
#define     DBG_SCHE        0x80

#define     EPG_UI_DEBUG    0x00

#if        (EPG_UI_DEBUG)
#define    EPG_UI( flag, s )    { if (EPG_UI_DEBUG & flag)    {printf s;} }
#else
#define    EPG_UI( flag, s )
#endif

#define EPG_CLOSE_FEATURE   TRUE

#define EPG_UI_TIME_OUT     APPLEVEL_MENU_TIME_OUT

// Macro function
#define Local_Time(utc)     ((U32)(utc) + msAPI_Timer_GetOffsetTime())

typedef struct
{
    HWND hwnd;
    HWND hwndNext;
    HWND hwndPressed;
    U16 * pVar;
    U8 u8ShiftBits;
}PASSWORD_INPUT_DATA_STRUCT;
typedef enum PASSWORD_MODE
{
    PASSWORD_MODE_INPUT,
    PASSWORD_MODE_WRONG,
}PASSWORD_MODE;

static U16 PasswordInput;
static PASSWORD_MODE PasswordInputMode;

/******************************************************************************/
/*      Local Enum                                                            */
/******************************************************************************/

typedef enum
{
    EN_EPGUI_DATE_TODAY,
    EN_EPGUI_DATE_TOMORROW,
    EN_EPGUI_DATE_DAY_3,
    EN_EPGUI_DATE_DAY_4,
    EN_EPGUI_DATE_DAY_5,
    EN_EPGUI_DATE_DAY_6,
    EN_EPGUI_DATE_DAY_7,
    EN_EPGUI_DATE_DAY_8,
} EN_EPGUI_DATE_MODE_INDEX;

typedef enum
{
    EPGUI_SRV_LIST_NORMAL,
    EPGUI_SRV_LIST_FAVORITE,
} EN_EPGUI_LIST_TYPE;

typedef enum
{
    EN_OSD_CHANGE_LTOR,
    EN_OSD_CHANGE_RTOL,
}EN_EPG_OSD_CHANGE_LR;

typedef enum
{
    MODE_EPGUI_HELPER_SCHEDULE,
    MODE_EPGUI_HELPER_DATE,
    MODE_EPGUI_HELPER_PF,
    MODE_EPGUI_HELPER_INFO,
    MODE_EPGUI_HELPER_MANUALTIMER,
    MODE_EPGUI_HELPER_TIMERLIST,
    MODE_EPGUI_HELPER_MAXNUM,
} EN_EPGUI_HELPER_MODE;

/******************************************************************************/
/*      Global Variables                                                      */
/******************************************************************************/
EN_EPGUI_EVENT_MODE             enEventMode     = MODE_EPGUI_EVENT_SCHEDULE;

#if (EPG_FOR_HALF_HOUR==FALSE)
static EN_EPG_OSD_CHANGE_LR     enOSDCHLR;
#endif

extern bit  bStopScrollDown;
extern U8   g_TimerList_CurPageStartItem;

/******************************************************************************/
/*                               Functions                                    */
/******************************************************************************/

#if ENABLE_DVB
static EN_EPGUI_DATE_MODE_INDEX enDateModeIndex = EN_EPGUI_DATE_TODAY;

// EPG UI list type //New EPG UI only support EPGUI_SRV_LIST_NORMAL now
static EN_EPGUI_LIST_TYPE       enEpgUiListType = EPGUI_SRV_LIST_NORMAL;

// Time related variables
static U32                      u32FocusedEventTime;

// program related variables
static U16                      u16LastSrvTypeSrvPos = 0;


BOOLEAN MApp_EpgUI_IsFocusService(U8 u8UiSrvIdx)
{
    return (u8UiSrvIdx==stFocus.u8UiSrvIdx);
}

BOOLEAN MApp_EpgUI_IsFocusEvent(U8 u8UiEvtIdx)
{
    return (stFocus.ListEvtIdx==u8UiEvtIdx);
}

BOOLEAN MApp_EpgUI_IsCurrentEvent(void)
{
    return ((stTime.EventStart<stTime.SystemTime) && (stTime.EventEnd>stTime.SystemTime));
}

MEMBER_SERVICETYPE MApp_EpgUI_GetFocusServiceType(void)
{
    return stFocus.enSvt;
}

/******************************************************************************/
void MApp_EpgUI_Func_Clear_SpecificSrvOSDVar(U8 u8UiSrvIdx)
{
    astScheOSD[u8UiSrvIdx].ListEvtCnt = 0;
    memset(&astScheOSD[u8UiSrvIdx].ListEvt, 0xFF, sizeof(astScheOSD[u8UiSrvIdx].ListEvt));
}
/******************************************************************************/
void MApp_EpgUI_Func_Clear_ChannelEvtOSDVar(void )
{
    u16ChannelEvtList.ListEvtIndex = 0;
    u16ChannelEvtList.ListEvtCnt = 0;
    memset(&u16ChannelEvtList.ListEvt, 0xFF, sizeof(u16ChannelEvtList.ListEvt));
}
/******************************************************************************/
U16 MApp_EpgUI_Func_Get_SrvOrder(MEMBER_SERVICETYPE SrvType, U16 SrvPos)
{
    U16 Order = MW_INVALID_SERVICE_IDX;

    switch ( SrvType )
    {
        case E_SERVICETYPE_DTV:
            Order = SrvPos;
            break;

        case E_SERVICETYPE_RADIO:
            // Index range: 0 ~ MAX_DTVPROGRAM-1
            Order = ( (MAX_DTVPROGRAM-1) - SrvPos );
            break;
        default:
            Order = MW_INVALID_SERVICE_IDX;
            break;
    }

    if ( Order > (MAX_DTVPROGRAM-1) )
    {
        Order = MW_INVALID_SERVICE_IDX;
    }

    return Order;
}

/******************************************************************************/
U16 MApp_EpgUI_Func_Get_FocusSrvOrder(U8 u8UiSrvIdx)
{
    return MApp_EpgUI_Func_Get_SrvOrder(stFocus.enSvt, au16SrvListOSD[u8UiSrvIdx]);
}

/******************************************************************************/
MEMBER_SERVICETYPE MApp_EpgUI_Func_Get_CurFocusSrvType( void )
{
    return stFocus.enSvt;
}

/******************************************************************************/
U16 MApp_EpgUI_Func_Get_CurFocusSrvPos( void )
{
    return stFocus.u16Service;
}

/******************************************************************************/
U16 MApp_EpgUI_Func_Get_CurFocusEvtIdx( void )
{
    if(MApp_ZUI_API_GetFocus()>=HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_1 &&
       MApp_ZUI_API_GetFocus()<=HWND_EPG_PRO_GUIDE_CHANNEL_ITEM_8)
    {
        return u16ChannelEvtList.ListEvt[u16ChannelEvtList.ListEvtIndex];//PROGRAMME GUIDE CHANNEL
    }
    else
    {
        return astScheOSD[stFocus.u8UiSrvIdx].ListEvt[stFocus.ListEvtIdx];//PROGRAMME GUIDE TIME
    }
}

/******************************************************************************/
static void MApp_EpgUI_Func_Get_NormalProgram_InPage(U16 program,BOOLEAN bItemFocus)
{
    U8 i;
    U16 u16PageHeadNum;

    memcpy(&stOldFocus, &stFocus, sizeof(MS_EPG_UI_FOCUS));

    // Set program number, program index in ui page and total program number
    stFocus.u16Service          = program;
    stFocus.u8UiSrvIdx          = (U8)(stFocus.u16Service % SERVICE_PER_PAGE);
    stService.u16TotalService   = msAPI_CM_CountProgram(stFocus.enSvt, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    stService.u8TotalPage       = (stService.u16TotalService/SERVICE_PER_PAGE)+1;

    // Error Checking
    if ( stFocus.u16Service >= stService.u16TotalService )
    {
        stFocus.u16Service = 0;
    }

    u16PageHeadNum = ( stFocus.u16Service / SERVICE_PER_PAGE * SERVICE_PER_PAGE );

    for (i=0; i<SERVICE_PER_PAGE; i++)
    {
        if ((u16PageHeadNum+i) < stService.u16TotalService)
        {
            au16SrvListOSD[i] = u16PageHeadNum+i;
        }
        else
        {
            au16SrvListOSD[i] = MW_INVALID_SERVICE_IDX;
        }

    }

    if( bItemFocus )
        MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideTimeItemIndexMapToWindow(stFocus.u8UiSrvIdx));

    EPG_UI (DBG_FOCUS, ("Old: u16Service = %u, u8UiSrvIdx = %bu\n", stOldFocus.u16Service, stOldFocus.u8UiSrvIdx));
    EPG_UI (DBG_FOCUS, ("New: u16Service = %u, u8UiSrvIdx = %bu\n", stFocus.u16Service, stFocus.u8UiSrvIdx));
}
/******************************************************************************/
static U8 MApp_EpgUI_Func_Get_FavPagePosition(U8 u8WhichPage,U16 u16TotalFavoriteChannelInDB)
{
    U8 u8Page = 0;
    U8 i = 0;
    U8 u8CountChannelInOnePage = 0;
    U16 u16Position = 0;
    //U16 u16Order = 0;
    U16 u16CountFavoriteChannel = 0;

    if (u16TotalFavoriteChannelInDB == 0)
    {
        return u8CountChannelInOnePage;
    }

    i = 0;
    u16Position = msAPI_CM_GetFirstFavoriteProgramPosition(stFocus.enSvt, TRUE);
    do
    {
        // Same page
        if (u8Page == u8WhichPage)
        {
            au16SrvListOSD[i] = u16Position;
            //printf("FavList[%bu] >> position = %u\n", i, au16SrvListOSD[i]);
            i++;
            u8CountChannelInOnePage++;
            if (i >= SERVICE_PER_PAGE)  // List is full
            {
                break;
            }
            u16Position = msAPI_CM_GetNextFavoriteProgramPosition(stFocus.enSvt, u16Position, TRUE);
        }
        else
        {
            i++;
            if (i == SERVICE_PER_PAGE)
            {
                i = 0;
                u8Page++;
            }
            u16Position = msAPI_CM_GetNextFavoriteProgramPosition(stFocus.enSvt, u16Position, TRUE);
        }
        u16CountFavoriteChannel++;
    } while (u16CountFavoriteChannel < u16TotalFavoriteChannelInDB);

    return u8CountChannelInOnePage;
}
/******************************************************************************/
static void MApp_EpgUI_Func_Get_FavProgram_InPage(U16 program)
{
    U8 i;
    memcpy(&stOldFocus, &stFocus, sizeof(MS_EPG_UI_FOCUS));

    stService.u16TotalService    = msAPI_CM_CountFavoriteProgram(stFocus.enSvt);
    stService.u8TotalPage  = (stService.u16TotalService/SERVICE_PER_PAGE)+1;

    // Init List Page Index
    for (i=0; i<SERVICE_PER_PAGE; i++)
    {
        au16SrvListOSD[i] = MW_INVALID_SERVICE_IDX;
    }

    // Error Checking
    if (stService.u16TotalService == 0)
    {
        return;
    }

    MApp_EpgUI_Func_Get_FavPagePosition(stFocus.u8Page, stService.u16TotalService);

    // Set program number, minimum program number and page start index in DB
    if( TRUE == msAPI_CM_GetProgramAttribute(stFocus.enSvt, program, E_ATTRIBUTE_IS_FAVORITE) )
    {
        stFocus.u16Service  = program;
    }
    else
    {
        stFocus.u16Service  = au16SrvListOSD[0];
    }

    // Set current program index in database and in ui page
    stFocus.u8UiSrvIdx = 0;

    for (i=0; i<SERVICE_PER_PAGE; i++)
    {
        if (au16SrvListOSD[i] == program)
        {
            stFocus.u8UiSrvIdx = i;
        }
    }

    //printf ("UiProgIdx = %bu\n", stFocus.u8UiSrvIdx);

    EPG_UI (DBG_FOCUS, ("Old: u16Service = %u, u8UiSrvIdx = %bu\n", stOldFocus.u16Service, stOldFocus.u8UiSrvIdx));
    EPG_UI (DBG_FOCUS, ("New: u16Service = %u, u8UiSrvIdx = %bu\n", stFocus.u16Service, stFocus.u8UiSrvIdx));
}

/******************************************************************************/
static void MApp_EpgUI_Func_Get_Program_InPage(U16 program ,BOOLEAN bItemFocus)
{
    if (enEpgUiListType == EPGUI_SRV_LIST_NORMAL)
    {
        MApp_EpgUI_Func_Get_NormalProgram_InPage(program,bItemFocus);
    }
    else
    {
        MApp_EpgUI_Func_Get_FavProgram_InPage(program);
    }
}

/******************************************************************************/
void MApp_EpgUI_Func_Set_PageTime(U32 time)
{
#if (EPG_FOR_HALF_HOUR==FALSE)
    U32 time_align = time / EPG_PAGE_DURATION * EPG_PAGE_DURATION;
#else
    U32 time_align = time / SECONDS_PER_HALF_HOUR * SECONDS_PER_HALF_HOUR;
#endif

    stTime.PageStartTime = time_align;
    stTime.PageEndTime   = time_align + EPG_PAGE_DURATION;
}

/******************************************************************************/
void MApp_EpgUI_Func_Set_NoInfo_EventTime(U8 u8UiSrvIdx, U8 ListEvtIdx)
{
    EventTime   stEvtTime;
    U32 PrevEvtEndTime, NextEvtStartTime;

    // Set event start time to this "No Info"
    if ( ListEvtIdx < 1 )   // 1st event
    {
        PrevEvtEndTime = stTime.PageStartTime;
    }
    else                    // Not the 1st event
    {
        MApp_Epg_GetEventTime(astScheOSD[u8UiSrvIdx].ListEvt[ListEvtIdx-1], &stEvtTime);
        PrevEvtEndTime = stEvtTime.u32StartTime + stEvtTime.u32Duration;
    }

    // Set event end time to this "No Info"
    if ( ListEvtIdx == (astScheOSD[u8UiSrvIdx].ListEvtCnt-1) )  // Last event
    {
        NextEvtStartTime = stTime.PageEndTime;
    }
    else    // Not the last event
    {
        MApp_Epg_GetEventTime(astScheOSD[u8UiSrvIdx].ListEvt[ListEvtIdx+1], &stEvtTime);
        NextEvtStartTime = stEvtTime.u32StartTime;
    }

    // Set the event time interval for drawing the block
    stTime.EventStart = PrevEvtEndTime;
    stTime.EventEnd   = NextEvtStartTime;
}

/******************************************************************************/
BOOLEAN MApp_EpgUI_Func_Add_EvtToOSDBuffer(U8 u8UiSrvIdx, U16 u16EvtIdx)
{
    if (astScheOSD[u8UiSrvIdx].ListEvtCnt < MAX_PAGE_EVENTS_IN_SERVICE)
    {
        astScheOSD[u8UiSrvIdx].ListEvt[astScheOSD[u8UiSrvIdx].ListEvtCnt] = u16EvtIdx;
        astScheOSD[u8UiSrvIdx].ListEvtCnt++;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/******************************************************************************/
BOOLEAN MApp_EpgUI_Func_Channel_Add_EvtToOSDBuffer(U16 u16Idx, U16 u16EvtIdx)
{
    if ( u16ChannelEvtList.ListEvtCnt < MAX_CHANNEL_EVENTS)
    {
        //astScheOSD[u8UiSrvIdx].ListEvt[astScheOSD[u8UiSrvIdx].ListEvtCnt] = u16EvtIdx;
        MS_DEBUG_MSG(printf("add event u16ChannelEvtList[%u] = %u \n",u16Idx,u16EvtIdx));
     #if ADD_EVENT_BYCHANGEPAGE
            u16ChannelEvtList.ListEvt[u16Idx+_u8EpgChannelPageCount*SERVICE_PER_PAGE]=u16EvtIdx;
     #else
            u16ChannelEvtList.ListEvt[u16Idx]=u16EvtIdx;
     #endif
        u16ChannelEvtList.ListEvtCnt++;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/******************************************************************************/
/*        PageStart>>                                             <<PageEnd   */
/*                  +---------------------------------------------+           */
/*  case vacuum0:   |              No Information                 |           */
/*  case vacuum1:   |        No Information, Event . . .          |           */
/*  case vacuum2:   |     Event..., No Information, Event...      |           */
/*  case vacuum3:   |        Event . . ., No Information          |           */
/*                  +---------------------------------------------+           */
/******************************************************************************/
void MApp_EpgUI_Func_Add_MatchEvent_Sche(U8 u8UiSrvIdx)
{
    U32 u32SearchEvtTime;
    EventIndex  SearchEvtIdx;
    EventTime   stEvtTime;

    u32SearchEvtTime = stTime.PageStartTime;

    while ( u32SearchEvtTime < stTime.PageEndTime )
    {
        MApp_Epg_EventFindByTime(msAPI_SI_ToSI_Service_Type(stFocus.enSvt), au16SrvListOSD[u8UiSrvIdx], u32SearchEvtTime, &SearchEvtIdx);

        MApp_Epg_GetEventTime(SearchEvtIdx, &stEvtTime);
        stTime.EventStart = stEvtTime.u32StartTime;
        stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;

        // Page Matched Event
        if ( (stTime.EventEnd>stTime.PageStartTime) && (stTime.EventStart<stTime.PageEndTime) )
        {
            if ( MApp_EpgUI_Func_Add_EvtToOSDBuffer(u8UiSrvIdx, SearchEvtIdx) )
            {
                u32SearchEvtTime = stTime.EventEnd;
            }
            else
            {
                EPG_UI (DBG_HANDLER, ("Add_MatchEvent_Sche>> UI Event List is full, u8UiSrvIdx = %bu, ListEvtCnt = %2bu\n", u8UiSrvIdx, astScheOSD[u8UiSrvIdx].ListEvtCnt));
                break;
            }
        }
        else
        {
            EPG_UI (DBG_HANDLER, ("Add_MatchEvent_Sche>> Cant find matched sche event!\n"));
            break;
        }
    }

    EPG_UI (DBG_HANDLER, ("u8UiSrvIdx = %bu, ListEvtCnt = %2bu\n", u8UiSrvIdx, astScheOSD[u8UiSrvIdx].ListEvtCnt));


}

void MApp_EpgUI_Func_Add_MatchOneEvent(U8 u8UiSrvIdx)
{
    U32 u32SearchEvtTime = stTime.SystemTime;
    EventIndex  SearchEvtIdx = 0xFFFF;
    EventTime   stEvtTime;
    MW_EN_EPG_FUNC_STATUS enRtnValue;

    #if ENABLE_SBTVD_SI
    EventTime   stPresentEvtTime, stFollowingEvtTime;
    MW_EN_EPG_PF_SRV_HDR* pstPfSrvHdr = NULL;
    #endif

    enRtnValue = MApp_Epg_EventFindByTime(msAPI_SI_ToSI_Service_Type(stFocus.enSvt), au16SrvListOSD[u8UiSrvIdx], u32SearchEvtTime, &SearchEvtIdx);

    #if ENABLE_SBTVD_SI
    if(msAPI_SRC_IS_SBTVD_InUse())
        pstPfSrvHdr = MApp_Epg_Pf_SrvHdr_Load (au16SrvListOSD[u8UiSrvIdx]);
    #endif

    MApp_Epg_GetEventTime(SearchEvtIdx, &stEvtTime);
    stTime.EventStart = stEvtTime.u32StartTime;
    stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;

    #if ENABLE_SBTVD_SI
        if(msAPI_SRC_IS_SBTVD_InUse())
        {
            // if schedule event time and PF event time overlay, add PF event into event OSD buffer.
            if (pstPfSrvHdr != NULL)
            {

                MApp_Epg_GetEventTime(pstPfSrvHdr->au16PfEvtIdx[0], &stPresentEvtTime);
                MApp_Epg_GetEventTime(pstPfSrvHdr->au16PfEvtIdx[1], &stFollowingEvtTime);

                if (stEvtTime.u32StartTime == stPresentEvtTime.u32StartTime && stEvtTime.u32Duration == stPresentEvtTime.u32Duration)
                    SearchEvtIdx = pstPfSrvHdr->au16PfEvtIdx[0];
                else if (stEvtTime.u32StartTime == stFollowingEvtTime.u32StartTime && stEvtTime.u32Duration == stFollowingEvtTime.u32Duration)
                    SearchEvtIdx = pstPfSrvHdr->au16PfEvtIdx[1];
            }
        }
    #endif

    // Page Matched Event
    if ( (stTime.EventEnd > stTime.SystemTime && stTime.EventStart <= stTime.SystemTime ) && (enRtnValue == MW_EN_EPG_FUNC_STATUS_SUCCESS) )
    {
        if(!(MApp_EpgUI_Func_Add_EvtToOSDBuffer(u8UiSrvIdx, SearchEvtIdx)))
        {
            EPG_UI (DBG_HANDLER, ("Add_MatchEvent_Sche>> UI Event List is full, u8UiSrvIdx = %bu, ListEvtCnt = %2bu\n", u8UiSrvIdx, astScheOSD[u8UiSrvIdx].ListEvtCnt));
        }
    }
    else
    {
        MApp_EpgUI_Func_Add_EvtToOSDBuffer (u8UiSrvIdx, MW_INVALID_EVENT_IDX);
        EPG_UI (DBG_HANDLER, ("Add_MatchEvent_Sche>> Cant find matched sche event!\n"));
    }


    EPG_UI (DBG_HANDLER, ("u8UiSrvIdx = %bu, ListEvtCnt = %2bu\n", u8UiSrvIdx, astScheOSD[u8UiSrvIdx].ListEvtCnt));


}

//This function need to check
void MApp_EpgUI_Func_Add_NumberEvent(U8 u8UiSrvIdx)
{
    U32 u32SearchEvtTime;
    EventIndex  SearchEvtIdx;
    EventTime   stEvtTime;
    U32 u32EvtCount = 0;
    MW_EN_EPG_FUNC_STATUS EventSearchResult = MW_EN_EPG_FUNC_STATUS_SUCCESS;
#if (ENABLE_SBTVD_SI)
    BOOL bIsEventTimeUndecide = FALSE;
#endif
    //static U32 u32SearchEvtTimeFirst,u32SearchEvtTimeLast;
    #if ADD_EVENT_BYCHANGEPAGE
        if(_u8EpgChannelPageCount==0)
        {
            u32SearchEvtTime = stTime.PageStartTime;
            u16ChannelEvtList.ListEvtIndex=0;
            u16ChannelEvtList.ListEvtCnt=0;
         }
         else
      {
             u32SearchEvtTime = stTime.EventEnd;
         }
    #else
         u32SearchEvtTime = stTime.PageStartTime;
         u16ChannelEvtList.ListEvtIndex=0;
         u16ChannelEvtList.ListEvtCnt=0;
    #endif
    while ( EventSearchResult == MW_EN_EPG_FUNC_STATUS_SUCCESS )
    {
        #if (ENABLE_SBTVD_SI)
        EventTime   stPresentEvtTime, stFollowingEvtTime;
        MW_EN_EPG_PF_SRV_HDR* pstPfSrvHdr = NULL;
        if(msAPI_SRC_IS_SBTVD_InUse())
        {
            if (FALSE == bIsEventTimeUndecide)
            {
                EventSearchResult = MApp_Epg_EventFindByTime(msAPI_SI_ToSI_Service_Type(stFocus.enSvt), au16SrvListOSD[u8UiSrvIdx], u32SearchEvtTime, &SearchEvtIdx);
            }
            else
            {
                EventSearchResult = MApp_Epg_EventFindNextByTime(msAPI_SI_ToSI_Service_Type(stFocus.enSvt), au16SrvListOSD[u8UiSrvIdx], u32SearchEvtTime, &SearchEvtIdx);
            }
        }
        else
        #endif
        EventSearchResult = MApp_Epg_EventFindByTime(msAPI_SI_ToSI_Service_Type(stFocus.enSvt), au16SrvListOSD[u8UiSrvIdx], u32SearchEvtTime, &SearchEvtIdx);

        #if (ENABLE_SBTVD_SI)
        if(msAPI_SRC_IS_SBTVD_InUse())
            pstPfSrvHdr = MApp_Epg_Pf_SrvHdr_Load (au16SrvListOSD[u8UiSrvIdx]);
        #endif

        MApp_Epg_GetEventTime(SearchEvtIdx, &stEvtTime);
        stTime.EventStart = stEvtTime.u32StartTime;
        stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;

        #if (ENABLE_SBTVD_SI)
        // if schedule event time and PF event time overlay, add PF event into event OSD buffer.
        if(msAPI_SRC_IS_SBTVD_InUse())
        {
            if (pstPfSrvHdr != NULL)
            {

                MApp_Epg_GetEventTime(pstPfSrvHdr->au16PfEvtIdx[0], &stPresentEvtTime);
                MApp_Epg_GetEventTime(pstPfSrvHdr->au16PfEvtIdx[1], &stFollowingEvtTime);

                if (stEvtTime.u32StartTime == stPresentEvtTime.u32StartTime && stEvtTime.u32Duration == stPresentEvtTime.u32Duration)
                    SearchEvtIdx = pstPfSrvHdr->au16PfEvtIdx[0];
                else if (stEvtTime.u32StartTime == stFollowingEvtTime.u32StartTime && stEvtTime.u32Duration == stFollowingEvtTime.u32Duration)
                    SearchEvtIdx = pstPfSrvHdr->au16PfEvtIdx[1];
            }
        }
        #endif


        // Page Matched Event
        if ( EventSearchResult == MW_EN_EPG_FUNC_STATUS_SUCCESS )
        {
        #if ADD_EVENT_BYCHANGEPAGE
            if (( u32EvtCount < SERVICE_PER_PAGE ) && ( _u8EpgChannelPageCount < MAX_CHANNEL_EVENTS/SERVICE_PER_PAGE ))
     #else
         if ( u32EvtCount < MAX_CHANNEL_EVENTS )
     #endif
            {
            #if (ENABLE_SBTVD_SI)
                if(msAPI_SRC_IS_SBTVD_InUse())
                {
                    if (stEvtTime.u32Duration == 0x000937A1) //duration is undecided:FF:FF:FF
                    {
                        if (u32EvtCount>0)
                        {
                            break;
                        }
                        else
                        {
                            u32SearchEvtTime = MApp_GetLocalSystemTime();
                            bIsEventTimeUndecide = TRUE;
                        }
                    }
                    else
                    {
                        u32SearchEvtTime =stTime.EventEnd;
                        bIsEventTimeUndecide = FALSE;
                    }
                }
                else
            #endif
                {
                    u32SearchEvtTime =stTime.EventEnd;
                }
                MApp_EpgUI_Func_Channel_Add_EvtToOSDBuffer(u32EvtCount, SearchEvtIdx);
                u32EvtCount++;
            }
            else
            {
                MS_DEBUG_MSG(printf("u32EvtCount >= MAX_CHANNEL_EVENTS u16ChannelEvtList full!\n"));
                EPG_UI (DBG_HANDLER, ("Add_MatchEvent_Sche>> UI Event List is full, u8UiSrvIdx = %bu, ListEvtCnt = %2bu\n", u8UiSrvIdx, astScheOSD[u8UiSrvIdx].ListEvtCnt));
                break;
            }
        }
        else
        {
            MS_DEBUG_MSG(printf("EventSearchResult(%lu) != MW_EN_EPG_FUNC_STATUS_SUCCESS %lu events added.\n",(U32)EventSearchResult,u32EvtCount));
            //MApp_EpgUI_Func_Channel_Add_EvtToOSDBuffer (u32EvtCount, MW_INVALID_EVENT_IDX);
            break;
        }
    }

}
#endif
/******************************************************************************/

typedef enum _EN_EPG_SWITCH_FOCUS
{
#if (EPG_FOR_HALF_HOUR==FALSE)
    EPGUI_SWITCH_TIME,
#else
    EPGUI_SWITCH_TIME_TO_PREV_EVT,
    EPGUI_SWITCH_TIME_TO_CUR_EVT,
    EPGUI_SWITCH_TIME_TO_NEXT_EVT,
#endif
    EPGUI_SWITCH_OTHER
} EN_EPG_SWITCH_FOCUS;

static U8 _GetScheduleListItemIndexByHandle(HWND hwnd)
{

    switch(hwnd)
    {
         case HWND_EPG_SCHEDULE_LIST_ITEM_0:
         case HWND_EPG_SCHEDULE_LIST_ITEM_0_TITLE:
         case HWND_EPG_SCHEDULE_LIST_ITEM_0_TIME:
         case HWND_EPG_SCHEDULE_LIST_ITEM_0_DATE:
         case HWND_EPG_SCHEDULE_LIST_ITEM_0_PROGRAMME:
         case HWND_EPG_SCHEDULE_LIST_ITEM_0_ICON:
            return 0;

         case HWND_EPG_SCHEDULE_LIST_ITEM_1:
         case HWND_EPG_SCHEDULE_LIST_ITEM_1_TITLE:
         case HWND_EPG_SCHEDULE_LIST_ITEM_1_TIME:
         case HWND_EPG_SCHEDULE_LIST_ITEM_1_DATE:
         case HWND_EPG_SCHEDULE_LIST_ITEM_1_PROGRAMME:
         case HWND_EPG_SCHEDULE_LIST_ITEM_1_ICON:
            return 1;

         case HWND_EPG_SCHEDULE_LIST_ITEM_2:
         case HWND_EPG_SCHEDULE_LIST_ITEM_2_TITLE:
         case HWND_EPG_SCHEDULE_LIST_ITEM_2_TIME:
         case HWND_EPG_SCHEDULE_LIST_ITEM_2_DATE:
         case HWND_EPG_SCHEDULE_LIST_ITEM_2_PROGRAMME:
         case HWND_EPG_SCHEDULE_LIST_ITEM_2_ICON:
            return 2;

         case HWND_EPG_SCHEDULE_LIST_ITEM_3:
         case HWND_EPG_SCHEDULE_LIST_ITEM_3_TITLE:
         case HWND_EPG_SCHEDULE_LIST_ITEM_3_TIME:
         case HWND_EPG_SCHEDULE_LIST_ITEM_3_DATE:
         case HWND_EPG_SCHEDULE_LIST_ITEM_3_PROGRAMME:
         case HWND_EPG_SCHEDULE_LIST_ITEM_3_ICON:
            return 3;

         default:
            break;
    }

    return 0;
}
#if (ENABLE_PVR)
static U8 _GetRecorderScheduleListItemIndexByHandle(HWND hwnd)
{

    switch(hwnd)
    {
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_TITLE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_TIME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_DATE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_PROGRAMME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_MODE:
            return 0;

         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_TITLE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_TIME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_DATE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_PROGRAMME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_MODE:
            return 1;

         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_TITLE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_TIME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_DATE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_PROGRAMME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_MODE:
            return 2;

         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_TITLE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_TIME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_DATE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_PROGRAMME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_MODE:
            return 3;

         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_TITLE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_TIME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_DATE:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_PROGRAMME:
         case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_MODE:
            return 4;

         default:
            break;
    }

    return 0;
}
#endif

static U16 _GetScheduleListItemHandleByIndex(U8 u8Index)
{
    u8Index %= SCHEDULE_LIST_PER_PAGE;
    switch(u8Index)
    {
        case 0:
            return HWND_EPG_SCHEDULE_LIST_ITEM_0;

        case 1:
            return HWND_EPG_SCHEDULE_LIST_ITEM_1;

        case 2:
            return HWND_EPG_SCHEDULE_LIST_ITEM_2;

        case 3:
            return HWND_EPG_SCHEDULE_LIST_ITEM_3;
    }
    return HWND_INVALID;
}

static U16 _GetScheduleListRepeatItemByIndex(U8 u8Index)
{
    switch(u8Index)
    {
        case 0:
            return HWND_EPG_SCHEDULE_LIST_ITEM_0_MODE;

        case 1:
            return HWND_EPG_SCHEDULE_LIST_ITEM_1_MODE;

        case 2:
            return HWND_EPG_SCHEDULE_LIST_ITEM_2_MODE;

        case 3:
            return HWND_EPG_SCHEDULE_LIST_ITEM_3_MODE;
    }
    return HWND_INVALID;
}


#if (ENABLE_PVR)
static U16 _GetRecorderScheduleListItemHandleByIndex(U8 u8Index)
{
    switch(u8Index)
    {
        case 0:
            return HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0;

        case 1:
            return HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1;

        case 2:
            return HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2;

        case 3:
            return HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3;

        case 4:
            return HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4;
    }
    return HWND_INVALID;
}
#endif

static void _ValidateTimerListUI(void)
{

    U8 emptyIndex=0;
    U8 i=0;
    //U8 u8idx=0;
    //U8 u8idx1=0;
    //MS_EPG_TIMER * tmppstEpgTimer;

    //emptyIndex=MApp_EpgTimer_GetEmptyTimerIdx();
#if 0
    if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_SCHEDULE_LIST_PANEL))
    {
        emptyIndex = MApp_EpgTimer_GetTimerListPageItemsTotal(EN_EPGUI_TIMER_RECORDER);

        for(i=0;i<EPG_TIMER_MAX_NUM;i++)
        {
            if(i<emptyIndex)
            {
                MApp_ZUI_API_ShowWindow(_GetRecorderScheduleListItemHandleByIndex(i),SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(_GetRecorderScheduleListItemHandleByIndex(i),SW_HIDE);
            }
        }
        if(emptyIndex==0)
        {
            MApp_ZUI_API_SetFocus(HWND_INVALID);
        }
        else
        {
            MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0);
        }

    }
    else
#endif
    {
        emptyIndex = MApp_EpgUI_GetNumOfTimers();

        for( i=0 ; i < SCHEDULE_LIST_PER_PAGE ; i++)
        {
            if( (i+_u8ScheduleStartingIdx) < emptyIndex)
            {
                MApp_ZUI_API_ShowWindow(_GetScheduleListItemHandleByIndex(i),SW_SHOW);
                //u8idx1 = _GetScheduleListItemIndexByHandle(_GetScheduleListItemHandleByIndex(i));
                //u8idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(u8idx1+_u8ScheduleStartingIdx);
                _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

                if(_pstEpgTimer[i+_u8ScheduleStartingIdx].enRepeatMode != EN_EPGRM_ONCE)
                {
                    MApp_ZUI_API_ShowWindow(_GetScheduleListRepeatItemByIndex(i),SW_SHOW);
                }
                else
                {
                    MApp_ZUI_API_ShowWindow(_GetScheduleListRepeatItemByIndex(i),SW_HIDE);
                }

            }
            else
            {
                MApp_ZUI_API_ShowWindow(_GetScheduleListItemHandleByIndex(i),SW_HIDE);
            }
        }
        if(emptyIndex==0)
        {
            MApp_ZUI_API_SetFocus(HWND_INVALID);
        }
        //else
        //{
            //MApp_ZUI_API_SetFocus(HWND_EPG_SCHEDULE_LIST_ITEM_0);
        //}
    }
}

#if (ENABLE_PVR)
static void _ValidateRecorderTimerListUI(void)
{

    U8 emptyIndex=0;
    U8 i=0;

    //emptyIndex=MApp_EpgTimer_GetEmptyTimerIdx();
    emptyIndex = MApp_EpgTimer_GetTimerListPageItemsTotal(EN_EPGUI_TIMER_RECORDER);

    for(i=0;i<EPG_TIMER_MAX_NUM;i++)
    {
        if(i<emptyIndex)
        {
            MApp_ZUI_API_ShowWindow(_GetRecorderScheduleListItemHandleByIndex(i),SW_SHOW);
        }
        else
        {
            MApp_ZUI_API_ShowWindow(_GetRecorderScheduleListItemHandleByIndex(i),SW_HIDE);
        }
    }
    if(emptyIndex==0)
    {
        MApp_ZUI_API_SetFocus(HWND_INVALID);
    }
    else
    {
        MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0);
    }
}
#endif

extern U16 u16AlreadyShowHowManyBytes ;
void MApp_EpgUI_Func_GetNext_InfoStr( U16* pDescription)
{
    int u8Start = MAX_INFO_UNIT_LENGTH * _u8InfoScrollLineCount;
    u8Start = u16AlreadyShowHowManyBytes;

    if (u8Start >= MAX_INFO_STRING_LENGTH)
    {
        pDescription[0] = '\0';
        return ;
    }

    int u8Cnt = 0;

    for(;u8Cnt < MAX_INFO_UNIT_LENGTH;u8Cnt++)
    {
        pDescription[u8Cnt] = pDescription[u8Start++];
        if(pDescription[u8Start] == '\0' ||u8Cnt == MAX_INFO_UNIT_LENGTH-1 )
        {
            pDescription[++u8Cnt] = '\0';
            break;
        }
    }
}
#if ENABLE_DVB
void MApp_EpgUI_Func_Set_Focus_Event(U8 u8UiSrvIdx, EN_EPG_SWITCH_FOCUS eSwitch)
{
    U8 EvtLoopIdx;

    if ((u8UiSrvIdx >= SERVICE_PER_PAGE) || (u8UiSrvIdx != stFocus.u8UiSrvIdx))
    {
        return;
    }

    // Reset Focus Index
    {
        {
            if ( astScheOSD[u8UiSrvIdx].ListEvtCnt > 0 )   // Set focus to the last event in the beginning
            {
                stFocus.ListEvtIdx = astScheOSD[u8UiSrvIdx].ListEvtCnt - 1;
            }
            else
            {
                stFocus.ListEvtIdx = 0;
            }
        }
    }

#if (EPG_FOR_HALF_HOUR == TRUE)
    for( EvtLoopIdx=0 ; EvtLoopIdx<astScheOSD[u8UiSrvIdx].ListEvtCnt ; EvtLoopIdx++ )
    {
        switch ( eSwitch )
        {
            case EPGUI_SWITCH_TIME_TO_CUR_EVT:
                if (stFocus.PoolEvtIdx == astScheOSD[u8UiSrvIdx].ListEvt[EvtLoopIdx])
                {
                    stFocus.ListEvtIdx = EvtLoopIdx;
                    //printf ("SWITCH_TIME_TO_CUR_EVT>> (PoolEvtIdx,ListEvtIdx)=(%u, %bu)\n", stFocus.PoolEvtIdx, stFocus.ListEvtIdx);
                }
                break;
            case EPGUI_SWITCH_TIME_TO_PREV_EVT:
                if ( stFocus.PoolEvtIdx == MW_INVALID_EVENT_IDX )
                {
                    stFocus.ListEvtIdx = 0;
                    //printf ("SWITCH_TIME_TO_PREV_EVT>> Set Focus Index to 0\n");
                }
                else if (stFocus.PoolEvtIdx == astScheOSD[u8UiSrvIdx].ListEvt[EvtLoopIdx+1])
                {
                    stFocus.ListEvtIdx = EvtLoopIdx;
                    //printf ("SWITCH_TIME_TO_PREV_EVT>> (PoolEvtIdx,ListEvtIdx)=(%u, %bu)\n", stFocus.PoolEvtIdx, stFocus.ListEvtIdx);
                }
                break;
            case EPGUI_SWITCH_TIME_TO_NEXT_EVT:
                if ( stFocus.PoolEvtIdx == MW_INVALID_EVENT_IDX )
                {
                    stFocus.ListEvtIdx = astScheOSD[u8UiSrvIdx].ListEvtCnt - 1;
                    //printf ("SWITCH_TIME_TO_NEXT_EVT>> Set Focus Index to the End\n");
                }
                else if (stFocus.PoolEvtIdx == astScheOSD[u8UiSrvIdx].ListEvt[EvtLoopIdx])
                {
                    stFocus.ListEvtIdx = EvtLoopIdx+1;
                    //printf ("SWITCH_TIME_TO_NEXT_EVT>> (PoolEvtIdx,ListEvtIdx)=(%u, %bu)\n", stFocus.PoolEvtIdx, stFocus.ListEvtIdx);
                }
                break;

            default:
                break;
        }
    }
#endif

    // [Behavior] Set focused event in the middle of time of pre-focused event
    switch ( eSwitch )
    {
    #if (EPG_FOR_HALF_HOUR == FALSE)
        case EPGUI_SWITCH_TIME:
    #else
        case EPGUI_SWITCH_TIME_TO_CUR_EVT:
        case EPGUI_SWITCH_TIME_TO_PREV_EVT:
        case EPGUI_SWITCH_TIME_TO_NEXT_EVT:
    #endif
            {
                if ( MW_INVALID_EVENT_IDX != astScheOSD[u8UiSrvIdx].ListEvt[stFocus.ListEvtIdx] )
                {
                    EventTime stEvtTime;
                    MApp_Epg_GetEventTime(astScheOSD[u8UiSrvIdx].ListEvt[stFocus.ListEvtIdx], &stEvtTime);
                    stTime.EventStart = stEvtTime.u32StartTime;
                    stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                }
                else
                {
                    MApp_EpgUI_Func_Set_NoInfo_EventTime(u8UiSrvIdx, stFocus.ListEvtIdx);
                }
                u32FocusedEventTime = ( (MAX(stTime.PageStartTime, stTime.EventStart)+MIN(stTime.EventEnd, stTime.PageEndTime))/2 );
            }
            break;

        default:
            { //try to get previous focus event time..
                if ( MW_INVALID_EVENT_IDX != astScheOSD[stOldFocus.u8UiSrvIdx].ListEvt[stOldFocus.ListEvtIdx] )
                {
                    EventTime stEvtTime;
                    MApp_Epg_GetEventTime(astScheOSD[stOldFocus.u8UiSrvIdx].ListEvt[stOldFocus.ListEvtIdx], &stEvtTime);
                    stTime.EventStart = stEvtTime.u32StartTime;
                    stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                }
                else
                {
                    MApp_EpgUI_Func_Set_NoInfo_EventTime(stOldFocus.u8UiSrvIdx, stOldFocus.ListEvtIdx);
                }
                u32FocusedEventTime = ( (MAX(stTime.PageStartTime, stTime.EventStart)+MIN(stTime.EventEnd, stTime.PageEndTime))/2 );
            }

            for( EvtLoopIdx=0 ; EvtLoopIdx<astScheOSD[u8UiSrvIdx].ListEvtCnt ; EvtLoopIdx++ )
            {
                if ( MW_INVALID_EVENT_IDX != astScheOSD[u8UiSrvIdx].ListEvt[EvtLoopIdx] )
                {
                    EventTime stEvtTime;
                    MApp_Epg_GetEventTime(astScheOSD[u8UiSrvIdx].ListEvt[EvtLoopIdx], &stEvtTime);
                    stTime.EventStart = stEvtTime.u32StartTime;
                    stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                }
                else
                {
                    MApp_EpgUI_Func_Set_NoInfo_EventTime(u8UiSrvIdx, EvtLoopIdx);
                }

                if ( (u32FocusedEventTime>=MAX(stTime.PageStartTime,stTime.EventStart)) &&
                     (u32FocusedEventTime<MIN(stTime.EventEnd, stTime.PageEndTime)) )
                {
                    stFocus.ListEvtIdx = EvtLoopIdx;
                    u32FocusedEventTime = ( (MAX(stTime.PageStartTime, stTime.EventStart)+MIN(stTime.EventEnd, stTime.PageEndTime))/2 );

                    break;
                }
            }
            break;

    }
}
/******************************************************************************/

static void _MApp_EpgUI_ChannelItem_RefreshEvent(U8  u8UiSrvIdx)
{
    u8UiSrvIdx %= SERVICE_PER_PAGE;
    MApp_EpgUI_Func_Clear_ChannelEvtOSDVar();

    if (au16SrvListOSD[u8UiSrvIdx] == MW_INVALID_SERVICE_IDX )
    {
        return;
    }
    // To build astScheOSD and stFocus
        MApp_EpgUI_Func_Add_NumberEvent(u8UiSrvIdx);

}

/******************************************************************************/
static void _MApp_EpgUI_TimeItem_RefreshEvent(U8  u8UiSrvIdx)
{
    if (au16SrvListOSD[u8UiSrvIdx] == MW_INVALID_SERVICE_IDX)
    {
        return;
    }

    // To build astScheOSD and stFocus
    MApp_EpgUI_Func_Clear_SpecificSrvOSDVar(u8UiSrvIdx);
    MApp_EpgUI_Func_Add_MatchOneEvent(u8UiSrvIdx);

}

/******************************************************************************/
static void MApp_EpgUI_TimeItem_Switch_Page(void)
{
    U8 i;

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM);

    for (i = 0; i < SERVICE_PER_PAGE; i++)
    {
        _MApp_EpgUI_TimeItem_RefreshEvent(i);
    }

    MApp_EpgUI_Func_Set_Focus_Event(stFocus.u8UiSrvIdx, EPGUI_SWITCH_OTHER);

    //MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_ALL_EVENT_PANEL);
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM);
    //MApp_ZUI_API_InvalidateWindow(HWND_EPG_INFO_DESC_BG_0);
}

static void MApp_EpgUI_TimeItem_Switch_Program(void)
{
#if 0
    // Draw Old Program
    MApp_ZUI_API_InvalidateWindow(
        _MApp_ZUI_ACT_EpgTimeItemServiceIndexMapToWindow(stOldFocus.u8UiSrvIdx));
    _MApp_EpgUI_TimeItem_RefreshEvent(stOldFocus.u8UiSrvIdx);
    MApp_ZUI_API_InvalidateWindow(
        _MApp_ZUI_ACT_EpgProGuideTimeItemIndexMapToWindow(stOldFocus.u8UiSrvIdx));

    // Draw New Program
    MApp_ZUI_API_InvalidateWindow(
        _MApp_ZUI_ACT_EpgTimeItemServiceIndexMapToWindow(stFocus.u8UiSrvIdx));

    MApp_EpgUI_Func_Set_Focus_Event(stFocus.u8UiSrvIdx, EPGUI_SWITCH_OTHER);

    _MApp_EpgUI_TimeItem_RefreshEvent(stFocus.u8UiSrvIdx);
    MApp_ZUI_API_InvalidateWindow(
        _MApp_ZUI_ACT_EpgProGuideTimeItemIndexMapToWindow(stFocus.u8UiSrvIdx));
    //MApp_ZUI_API_InvalidateWindow(HWND_EPG_INFO_DESC_BG_0);
#endif
}
static void MApp_EpgUI_ChannelItem_Switch_Program(void)
{
     MApp_ZUI_API_InvalidateWindow(HWND_EPG_CHANNEL_SERVICE);
     MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);
}

/******************************************************************************/
static void MApp_EpgUI_Init_Local_Variables (void)
{
    // Time related variables
    stTime.SystemTime    = MApp_GetLocalSystemTime();

    MApp_EpgUI_Func_Set_PageTime(stTime.SystemTime);

    // program related variables
    memset(&stService,      0x00, sizeof(stService));
    memset(&stFocus,        0x00, sizeof(stFocus));
    memset(&stOldFocus,     0x00, sizeof(stOldFocus));
    stFocus.enSvt           = msAPI_CM_GetCurrentServiceType();
    stFocus.u16Service      = msAPI_CM_GetCurrentPosition(stFocus.enSvt);
    u16LastSrvTypeSrvPos    = 0;

    // Event related variables
    u32FocusedEventTime     = stTime.SystemTime;

    enDateModeIndex = EN_EPGUI_DATE_TODAY;
    #if ADD_EVENT_BYCHANGEPAGE
        _u8EpgChannelPageCount=0;
    #endif
}

/******************************************************************************/
static void MApp_EpgUI_Init(void)
{
    U8 i;

    MApp_EpgUI_Init_Local_Variables();

    MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service,TRUE);

    if ( enEventMode == MODE_EPGUI_EVENT_SCHEDULE)
    {
        MApp_Dmx_SetMonitorStatus(FALSE, EN_MONITOR_PF_EIT_ALL);
    }

    for (i = 0; i < SERVICE_PER_PAGE; i++) //inside _MApp_EpgUI_Draw_Event_All()
    {
        _MApp_EpgUI_TimeItem_RefreshEvent(i);
    }


}

/******************************************************************************/
static void MApp_EpgUI_Exit(void)
{

}

#endif
extern void _MApp_ZUI_ACT_LoadMonthString(U8 month, LPTSTR str);
extern void _MApp_ZUI_ACT_LoadWeekString(U8 month, LPTSTR str);
/////////////////////////////////////////////////////////////////////

//extern EN_EPG_STATE enEpgState;


extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);
extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);
extern BOOLEAN MApp_CharTable_GetServiceNameToUCS2(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD * bChannelName, U8 ControlCodes);

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
#if ENABLE_DVB
static EN_EPG_STATE _enTargetEpgState;

void MApp_ZUI_ACT_AppShowEpg(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_EPG;
    ZUI_MSG(printf("[]MApp_ZUI_ACT_AppShowEpg\n");)
    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);
    _Current_ProgramGuide_Mode = MODE_EPGUI_PROGRAMGUIDE_TIME;
    _u8InfoScrollLineCount = 0;
    _bChannelChagne = FALSE;
    u16AlreadyShowHowManyBytes = 0;

   #if ((FIXED_MIRROR_HD_PANEL_UI_LOSE == ENABLE) && (MirrorEnable == ENABLE))
    if((g_IPanel.Width()<=1366&&g_IPanel.Height()<=768)&&MApp_Image_GetMirror())
    {
        MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_DUPLICATE);
        MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_DUPLICATE);
    }
   #endif

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

#if (ENABLE_ARABIC_OSD)
        ArabicCHStringFlag = TRUE;
#endif

    //RECT_SET(rect, ((g_IPanel.HStart()+3)&0xFFFC), 1, g_IPanel.Width(), g_IPanel.Height());
    RECT_SET(rect,
        ZUI_EPG_XSTART, ZUI_EPG_YSTART,
        ZUI_EPG_WIDTH, ZUI_EPG_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

#if (ENABLE_UI_3D_PROCESS)
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_RUNNING);
#else
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
#endif

    if(MApp_TopStateMachine_GetTopState() == STATE_TOP_EPG) //avoid for count down win
    {
        #if MHEG5_ENABLE
        if(msAPI_MHEG5_IsRunning())
            MApp_MHEG5_Set_Display(TRUE,FALSE);
        #endif

        MApp_EpgUI_Init();
    #if (ENABLE_EPG_MUX)
        MApp_BarkerEPG_StartToCheck();
    #endif
    }
}

/////////////////////////////

U32 _MApp_TimerChange(ST_TIME stEventTime)
{
    U32 u32TimerNumber = 0;

    u32TimerNumber = stEventTime.u8Month;
    u32TimerNumber = u32TimerNumber * 100 + stEventTime.u8Day;
    u32TimerNumber = u32TimerNumber * 100 + stEventTime.u8Hour;
    u32TimerNumber = u32TimerNumber * 100 + stEventTime.u8Min;

    return u32TimerNumber;

}

U32 _MApp_Compare_Time(ST_TIME stUserTimer)
{
    ST_TIME _EventTimeStart;
    ST_TIME _EventTimeEnd;

#if ENABLE_NZ_EIT_TIME_DISPLAY
    BOOLEAN bDayLightTimeStart,bDayLightTimeEnd,bGotTOT;
    MS_EPG_UI_TIME           stNZTime;
#endif
    MS_EPG_UI_TIME stDispayTime;
    EventTime stEvtTime;
    MS_EPG_UI_TIME stChannelTime;
    U32 u32StartTimeNumber;
    U32 u32EndTimeNumber;
    U32 u32EventTimeNumber;
    U32 i = 0;

    for (i = 0; i < u16ChannelEvtList.ListEvtCnt; i++)
    {
        MApp_Epg_GetEventTime(u16ChannelEvtList.ListEvt[i], &stEvtTime);

        stChannelTime.EventStart = stEvtTime.u32StartTime;
        stChannelTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
    #if ENABLE_NZ_EIT_TIME_DISPLAY
        if ((IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))||(OSD_COUNTRY_SETTING==OSD_COUNTRY_NETHERLANDS))
        {
            stNZTime.EventStart = stEvtTime.u32StartTime - msAPI_Timer_GetOffsetTime();
            stNZTime.EventEnd = stNZTime.EventStart + stEvtTime.u32Duration;
            stNZTime.EventStart +=  MApp_SI_Get_OffsetTime(stNZTime.EventStart, &bDayLightTimeStart, &bGotTOT, TRUE);
            stNZTime.EventEnd = stNZTime.EventEnd + MApp_SI_Get_OffsetTime(stNZTime.EventEnd, &bDayLightTimeEnd, &bGotTOT, FALSE);

            stDispayTime.EventStart = stNZTime.EventStart;
            stDispayTime.EventEnd = stNZTime.EventEnd;
        }
        else
    #endif
        {
            stDispayTime.EventStart = stChannelTime.EventStart;
            stDispayTime.EventEnd = stChannelTime.EventEnd;

        }


        MApp_ConvertSeconds2StTime(stDispayTime.EventStart, &_EventTimeStart);
        MApp_ConvertSeconds2StTime(stDispayTime.EventEnd, &_EventTimeEnd);
        u32StartTimeNumber = _MApp_TimerChange(_EventTimeStart);
        u32EndTimeNumber = _MApp_TimerChange(_EventTimeEnd);
        u32EventTimeNumber = _MApp_TimerChange(stUserTimer);

        if((u32EventTimeNumber >= u32StartTimeNumber)
            && (u32EventTimeNumber < u32EndTimeNumber))
        {
            return i;
        }
    }

    return 0;
}

void _MApp_EditRemindEventNameByDate(void)
{
    MApp_Epg_GetEventName(u16ChannelEvtList.ListEvt[_MApp_Compare_Time(stEpgTimerParam.stEpgTimer.stStartDate)], stEpgTimerParam.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN);
}

//////////////////////////////////////////////////////////
// Key Handler
BOOLEAN _EpgTimer_IsItemRecording(U8 ItemIndex);

BOOLEAN MApp_ZUI_ACT_ExecuteEpgAction(U16 act)
{

    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
        {
            if(MApp_ZUI_API_IsSuccessor(HWND_EPG_RECORDER_PASSWORD, MApp_ZUI_API_GetFocus()))
            {
                #if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                stEpgTimerParam.stEpgTimer.bPinCodeCached = FALSE;
                stEpgTimerParam.stEpgTimer.u16CachedPinCode = 0xFFFF;
                #endif
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_SETTING_SAVE);
                PasswordInputMode = PASSWORD_MODE_INPUT;
            }
            else
            {
                MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
                _enTargetEpgState = STATE_EPG_CLEAN_UP;
            }
            return TRUE;
        }

#if (ENABLE_PIP)
        case EN_EXE_ENABLE_PIP_MODE:
            if(IsPIPSupported())
            {
                MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
                _enTargetEpgState = STATE_EPG_GOTO_PIP;
                return TRUE;
            }
            else
            {
                return FALSE;
            }
#endif

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetEpgState = STATE_EPG_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_TIME_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TITLE_CHANNEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_SCHEDULE_LIST_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_COUNTDOWN_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REC_TIME_STEEING_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_SCHEDULE_LIST_PANEL,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE_1, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TYPE_CHANNEL, SW_HIDE);
#if !(ENABLE_PVR)
            MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_CONTROL_ICON_RED, SW_HIDE);
#endif

    #if (UI_SKIN_SEL == UI_SKIN_1366X768X565 || UI_SKIN_SEL == UI_SKIN_1920X1080X565 || UI_SKIN_SEL == UI_SKIN_960X540X565)
            MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_PRO_GUIDE_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_HELP_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_PANEL, SW_HIDE);
    #endif

            MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service,TRUE);
            return TRUE;

         case EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_CHANNEL_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TITLE_TIME, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TIME_ITEM, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_SCHEDULE_LIST_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_COUNTDOWN_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REC_TIME_STEEING_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_SCHEDULE_LIST_PANEL,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE_1, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TYPE_TIME, SW_HIDE);
#if !(ENABLE_PVR)
            MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_CONTROL_ICON_RED, SW_HIDE);
#endif
#if (UI_SKIN_SEL == UI_SKIN_1366X768X565 || UI_SKIN_SEL == UI_SKIN_1920X1080X565 || UI_SKIN_SEL == UI_SKIN_960X540X565)
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_PRO_GUIDE_PANEL, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_HELP_PANEL, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_PANEL, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_PANEL, SW_HIDE);
#endif

            if (u16ChannelEvtList.ListEvtCnt > 0)
            {
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
                MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);
            }
            else
            {
                MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE_CHANNEL);
            }

            return TRUE;

        case EN_EXE_EPG_SHOW_INFO:
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_SHOW);
#if (UI_SKIN_SEL == UI_SKIN_1366X768X565) // ZUI to do --> || UI_SKIN_SEL == UI_SKIN_1920X1080X565 || UI_SKIN_SEL == UI_SKIN_960X540X565)
    #if (ENABLE_EPG_INFO_DISP_GENRE_TYPE == DISABLE)
            MApp_ZUI_API_ShowWindow(HWND_EPG_INFO_PANEL_EXT, SW_HIDE);
    #endif
#endif
            return TRUE;

        case EN_EXE_EPG_SHOW_TIMER_MANUAL:
            _MApp_EpgUI_ChannelItem_RefreshEvent(stFocus.u16Service);
            MApp_EpgTimer_LoadManualTimer(EN_EPGUI_TIMER_REMINDER);
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_TRANSPARENT_BG, SW_SHOW);

            if(stEpgTimerParam.stEpgTimer.enRepeatMode==EN_EPGRM_DAILY)
            {
                MApp_ZUI_API_EnableWindow(HWND_EPG_REMINDER_DATE,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_REMINDER_MONTH,FALSE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_EPG_REMINDER_DATE,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_REMINDER_MONTH,TRUE);
            }

            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_PANEL, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_TIMER_SAVE_DLG, SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_EPG_REMINDER_PROGRAMME);
            return TRUE;

        case EN_EXE_EPG_SHOW_TIMER_LIST:
            //MApp_EpgTimer_initTmpTimerListIdx();
            //MApp_EpgTimer_GetIdxFromTimerDBIdx(EN_EPGUI_TIMER_REMINDER);
            _u8ScheduleStartingIdx = 0;

            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_TRANSPARENT_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_EPG_SCHEDULE_LIST_PANEL, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_EPG_SCHEDULE_LIST_ITEM_0);
            _ValidateTimerListUI();
            return TRUE;

        case EN_EXE_EPG_SHOW_TIMER_COUNTDOWN:
            if(MApp_TopStateMachine_GetTopState() != STATE_TOP_EPG)
            {
                MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
            }
            MApp_ZUI_API_ShowWindow(HWND_EPG_COUNTDOWN_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_EPG_COUNTDOWN_BUTTON_BAR);
            return TRUE;

        case EN_EXE_EPG_TIMER_COUNTDOWN_UPDATE:
            MApp_ZUI_API_InvalidateWindow(HWND_EPG_COUNTDOWN_MSG_TXT);
            return TRUE;

        case EN_EXE_EPG_SHOW_RECORD_TIME_SETTING:
            MApp_ZUI_API_StoreFocusCheckpoint();

//            gbEPG_RECORDER_PANEL_CUR_FOCUS = TRUE;

            MApp_ZUI_API_ShowWindow(HWND_EPG_REC_TIME_STEEING_PANEL, SW_SHOW);

            MApp_ZUI_API_SetFocus(HWND_EPG_REC_TIME_STEEING_YEAR_ITEM);
            return TRUE;

        case EN_EXE_EPG_DATE_ADJ_DEC:
        case EN_EXE_EPG_DATE_ADJ_INC:
            {
                U8 i=0;
                enDateModeIndex = (EN_EPGUI_DATE_MODE_INDEX) MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_DATE_ADJ_INC, enDateModeIndex, EN_EPGUI_DATE_TODAY, EN_EPGUI_DATE_DAY_8, 1);
                stTime.SystemTime = MApp_GetLocalSystemTime() + enDateModeIndex*SECONDS_PER_DAY;
                MApp_EpgUI_Func_Set_PageTime(stTime.SystemTime);


                for (i = 0; i < SERVICE_PER_PAGE; i++)
                {
                    _MApp_EpgUI_TimeItem_RefreshEvent(i);
                }

                stFocus.ListEvtIdx = 0;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TITLE_TIME);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM_1);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM_2);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM_3);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM_4);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM_5);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM_6);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM_7);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PRO_GUIDE_TIME_ITEM_8);

                return TRUE;
            }

        case EN_EXE_EPG_TIMER_PROG_ADJ_DEC:
        case EN_EXE_EPG_TIMER_PROG_ADJ_INC:
#if (ENABLE_PVR)
        case EN_EXE_EPG_RECORDER_PROG_ADJ_DEC:
        case EN_EXE_EPG_RECORDER_PROG_ADJ_INC:
#endif
            {
                U16 DTVProgTtl = msAPI_CM_CountProgram( E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                U16 RadioProgTtl = msAPI_CM_CountProgram( E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                #if NORDIG_FUNC //for Nordig spec v2.0
                U16 DataProgTtl = msAPI_CM_CountProgram( E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                #endif

                MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
                U16 srvPos = INVALID_SERVICE_ID;

                if ( DTVProgTtl == 0 && RadioProgTtl == 0)   {   break;  }
                msAPI_CM_GetServiceTypeAndPositionWithPCN(stEpgTimerParam.stEpgTimer.u8PCN, stEpgTimerParam.stEpgTimer.u16SrvID, &srvType, &srvPos);

                if ( EN_EXE_EPG_TIMER_PROG_ADJ_INC == act
#if (ENABLE_PVR)
                    || EN_EXE_EPG_RECORDER_PROG_ADJ_INC == act
#endif
                    )
                {
                #if NORDIG_FUNC //for Nordig spec v2.0
                    if(E_SERVICETYPE_DTV == srvType)
                    {
                        if( srvPos >= (DTVProgTtl -1) )
                        {   //Last DTV channel
                            srvPos = 0;
                            if(RadioProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_RADIO;
                            }
                            else if(DataProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DATA;
                            }
                        }
                        else
                        {
                            srvPos ++;
                        }
                    }
                    else if(E_SERVICETYPE_RADIO == srvType)
                    {
                        if( srvPos >= (RadioProgTtl -1) )
                        {   //Last radio channel
                            srvPos = 0;
                            if(DTVProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DTV;
                            }
                            else if(DataProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DATA;
                            }
                        }
                        else
                        {
                            srvPos ++;
                        }
                    }
                    else if(E_SERVICETYPE_DATA == srvType)
                    {
                        if( srvPos >= (DataProgTtl -1) )
                        {   //Last radio channel
                            srvPos = 0;
                            if(DTVProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DTV;
                            }
                            else if(RadioProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_RADIO;
                            }
                        }
                        else
                        {
                            srvPos ++;
                        }
                    }
                    #else
                    if(E_SERVICETYPE_DTV == srvType)
                    {
                        if( srvPos >= (DTVProgTtl -1) )
                        {   //Last DTV channel
                            srvPos = 0;
                            if(RadioProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_RADIO;
                            }
                        }
                        else
                        {
                            srvPos ++;
                        }
                    }else if(E_SERVICETYPE_RADIO == srvType)
                    {
                        if( srvPos >= (RadioProgTtl -1) )
                        {   //Last radio channel
                            srvPos = 0;
                            if(DTVProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DTV;
                            }
                        }
                        else
                        {
                            srvPos ++;
                        }
                    }
                    #endif
                }
                else if ( EN_EXE_EPG_TIMER_PROG_ADJ_DEC == act
#if (ENABLE_PVR)
                    || EN_EXE_EPG_RECORDER_PROG_ADJ_DEC == act
#endif
                    )
                {
                #if NORDIG_FUNC //for Nordig spec v2.0
                    if(E_SERVICETYPE_DTV == srvType)
                    {
                        if( srvPos == 0 )
                        {   //First DTV channel
                            if(RadioProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_RADIO;
                                srvPos = RadioProgTtl - 1;
                            }
                            else if(DataProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DATA;
                                srvPos = DataProgTtl - 1;
                            }
                            else
                            {
                                srvPos = DTVProgTtl - 1;
                            }
                        }
                        else
                        {
                            srvPos --;
                        }
                    }
                    else if(E_SERVICETYPE_RADIO == srvType)
                    {
                       if( srvPos == 0 )
                        {   //First radio channel
                            if(DTVProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DTV;
                                srvPos = DTVProgTtl - 1;
                            }
                            else if(DataProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DATA;
                                srvPos = DataProgTtl - 1;
                            }
                            else
                            {
                                srvPos = RadioProgTtl - 1;
                            }
                        }
                        else
                        {
                            srvPos --;
                        }
                    }
                    else if(E_SERVICETYPE_DATA == srvType)
                    {
                       if( srvPos == 0 )
                        {   //First radio channel
                            if(DTVProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DTV;
                                srvPos = DTVProgTtl - 1;
                            }
                            else if(RadioProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_RADIO;
                                srvPos = RadioProgTtl - 1;
                            }
                            else
                            {
                                srvPos = RadioProgTtl - 1;
                            }
                        }
                        else
                        {
                            srvPos --;
                        }
                    }
                #else //non NORDIG_FUNC
                    if(E_SERVICETYPE_DTV == srvType)
                    {
                        if( srvPos == 0 )
                        {   //First DTV channel
                            if(RadioProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_RADIO;
                                srvPos = RadioProgTtl - 1;
                            }else{
                                srvPos = DTVProgTtl - 1;
                            }
                        }
                        else
                        {
                            srvPos --;
                        }
                    }
                    else if(E_SERVICETYPE_RADIO == srvType)
                    {
                       if( srvPos == 0 )
                        {   //First radio channel
                            if(DTVProgTtl > 0)
                            {
                                srvType = E_SERVICETYPE_DTV;
                                srvPos = DTVProgTtl - 1;
                            }else{
                                srvPos = RadioProgTtl - 1;
                            }
                        }
                        else
                        {
                            srvPos --;
                        }
                    }
                #endif
                }

                stEpgTimerParam.stEpgTimer.u16SrvID = msAPI_CM_GetService_ID(srvType, srvPos);
                stEpgTimerParam.stEpgTimer.u8PCN = msAPI_CM_GetPhysicalChannelNumber(srvType, srvPos);

                if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_PANEL))
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_PANEL);
                }
                else
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_REMINDER_PANEL);
                }
                return TRUE;
            }

        case EN_EXE_EPG_TIMER_MODE_ADJ_DEC:
        case EN_EXE_EPG_TIMER_MODE_ADJ_INC:
            {
                stEpgTimerParam.stEpgTimer.enRepeatMode = (EN_EPG_TIMER_REPEAT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_TIMER_MODE_ADJ_INC, stEpgTimerParam.stEpgTimer.enRepeatMode, EN_EPGRM_ONCE, EN_EPGRM_WEEKLY, 1);

                if(stEpgTimerParam.stEpgTimer.enRepeatMode==EN_EPGRM_DAILY)
                {
                    MApp_ZUI_API_EnableWindow(HWND_EPG_REMINDER_DATE,FALSE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_REMINDER_MONTH,FALSE);
                }
                else
                {
                    MApp_ZUI_API_EnableWindow(HWND_EPG_REMINDER_DATE,TRUE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_REMINDER_MONTH,TRUE);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_REMINDER_PANEL);



                return TRUE;
            }

        case EN_EXE_EPG_TIMER_MON_ADJ_DEC:
        case EN_EXE_EPG_TIMER_MON_ADJ_INC:
            {
                stEpgTimerParam.stEpgTimer.stStartDate.u8Month = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_TIMER_MON_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Month, 1, 12, 1 );
                stEpgTimerParam.stEpgTimer.stStartDate.u8Day = MIN( stEpgTimerParam.stEpgTimer.stStartDate.u8Day, ( U8 )MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stStartDate.u8Month ) );

                stEpgTimerParam.stEpgTimer.stEndDate.u8Month = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_TIMER_MON_ADJ_INC, stEpgTimerParam.stEpgTimer.stEndDate.u8Month, 1, 12, 1 );
                stEpgTimerParam.stEpgTimer.stEndDate.u8Day = MIN( stEpgTimerParam.stEpgTimer.stEndDate.u8Day, ( U8 )MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stEndDate.u8Month ) );

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_REMINDER_PANEL);

                return TRUE;
            }

        case EN_EXE_EPG_TIMER_DATE_ADJ_DEC:
        case EN_EXE_EPG_TIMER_DATE_ADJ_INC:
            {
                stEpgTimerParam.stEpgTimer.stStartDate.u8Day =(U8) MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_TIMER_DATE_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Day, 1, MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stStartDate.u8Month ), 1 );
                stEpgTimerParam.stEpgTimer.stEndDate.u8Day =(U8) MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_TIMER_DATE_ADJ_INC, stEpgTimerParam.stEpgTimer.stEndDate.u8Day, 1, MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stEndDate.u8Month ), 1 );

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_REMINDER_PANEL);

                return TRUE;
            }

        case EN_EXE_EPG_TIMER_HOUR_ADJ_DEC:
        case EN_EXE_EPG_TIMER_HOUR_ADJ_INC:
            {
                stEpgTimerParam.stEpgTimer.stStartDate.u8Hour = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_TIMER_HOUR_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Hour, 0, 23, 1 );

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_REMINDER_PANEL);

                return TRUE;
            }

        case EN_EXE_EPG_TIMER_MIN_ADJ_DEC:
        case EN_EXE_EPG_TIMER_MIN_ADJ_INC:
            {
                stEpgTimerParam.stEpgTimer.stStartDate.u8Min = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_TIMER_MIN_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Min, 0, 59, 1 );

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_REMINDER_PANEL);

                return TRUE;
            }


        case EN_EXE_EPG_REMINDER_SAVE:
            _MApp_EditRemindEventNameByDate();
            switch ( MApp_EpgTimer_SaveTimerSetting() )
            {
                case EN_TIMER_CHECK_PAST:
                    _timer_popup_type=TIMER_SAVE_RESULT_PAST;
                    break;

                case EN_TIMER_CHECK_OVERLAY:
                    _timer_popup_type=TIMER_SAVE_RESULT_OVERLAY;
                    break;

                case EN_TIMER_CHECK_SUCCESS:
                    _timer_popup_type=TIMER_SAVE_RESULT_SUCCESS;
                    break;

                case EN_TIMER_CHECK_FULL:
                    //need to add error message
                default:
                    return TRUE;
            }
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_PANEL,SW_HIDE);

            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_TIMER_SAVE_DLG,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_TIMER_SAVE_DLG_BG_L,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_TIMER_SAVE_DLG_BG_C,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_TIMER_SAVE_DLG_BG_R,SW_HIDE);

            MApp_ZUI_API_SetTimer(HWND_EPG_REMINDER_TIMER_SAVE_DLG,0,3000);

            MApp_ZUI_API_SetFocus(HWND_EPG_REMINDER_TIMER_SAVE_DLG_MSGBOX_BTN_OK);
            return TRUE;

        case EN_EXE_EPG_TIMER_DELETE_CURRENT:
            {
                U8 idx  = 0;
                U8 idx1 = 0;

                idx = _GetScheduleListItemIndexByHandle(MApp_ZUI_API_GetFocus())+_u8ScheduleStartingIdx;
                idx1 = _GetScheduleListItemIndexByHandle(MApp_ZUI_API_GetFocus());

              #if ENABLE_PVR
                if(_EpgTimer_IsItemRecording(idx))
                {
                    MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_SHOW);

                    MApp_ZUI_API_ShowWindow(HWND_EPG_COMMON_BTN_CLEAR, SW_HIDE);

                    EpgPvrSaveNewFocus = MApp_ZUI_API_GetFocus();
                    u8PvrWarningMsgType = 1;
                    MApp_ZUI_API_SetFocus(HWND_EPG_PVR_WARNING_DLG_CONFIRM_BTN_CANCEL);
                    return TRUE;
                }
              #endif

                MApp_EpgTimer_DelCurTimerListItem(idx);
                //MApp_EpgTimer_initTmpTimerListIdx();
                //MApp_EpgTimer_GetIdxFromTimerDBIdx(EN_EPGUI_TIMER_REMINDER);
                if( idx == MApp_EpgUI_GetNumOfTimers() )
                {
                    stEpgTimerParam.u8CurTimerIdx = idx-1;
                    if(idx1==0)
                    {
                        MApp_ZUI_API_ShowWindow(_GetScheduleListItemHandleByIndex(SCHEDULE_LIST_PER_PAGE-1),SW_SHOW);//in order to make setfocus success
                        MApp_ZUI_API_SetFocus(_GetScheduleListItemHandleByIndex(SCHEDULE_LIST_PER_PAGE-1));
                    }
                    else
                    {
                        MApp_ZUI_API_SetFocus(_GetScheduleListItemHandleByIndex(idx-1));
                    }
                    if(idx1==0&&_u8ScheduleStartingIdx>0)
                        _u8ScheduleStartingIdx -= SCHEDULE_LIST_PER_PAGE;
                }

                _ValidateTimerListUI();
                MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_SCHEDULE_LIST_PANEL);

            }
            return TRUE;

        case EN_EXE_EPG_TIMER_SAVE_DLG_CLOSE:
            {
                if(_timer_popup_type == TIMER_SAVE_RESULT_SUCCESS)
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_TIMER_LIST);
                }
                else
                {
                    MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_TIMER_SAVE_DLG, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_EPG_REMINDER_PROGRAMME);
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_CLOSE_CURRENT_OSD);

                }
            }
            return TRUE;

        case EN_EXE_EPG_TIMER_COUNTDOWN_BTN:
            {
                if (MApp_ZUI_API_GetFocus() == HWND_EPG_COUNTDOWN_BTN_YES)
                {
                    U32 ActiveTime;
                    #if ENABLE_PVR
                    ActiveTime = MApp_GetLocalSystemTime()+EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s + EPG_RECORDER_PVR_LEADING_TIME_s;
                    #else
                    ActiveTime = MApp_GetLocalSystemTime()+EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s;
                    #endif
                    MApp_EpgTimer_ExecTimerUpAct(MApp_EpgTimer_GetNextStartUpIndex());
                    MApp_EpgTimer_ReconfigTimerFromList(ActiveTime);
                }
                else if (MApp_ZUI_API_GetFocus() == HWND_EPG_COUNTDOWN_BTN_NO)
                {
                    MApp_EpgTimer_ResetStopppedTimerListItem(MApp_EpgTimer_GetNextStartUpIndex());
                    MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
                    if(MApp_TopStateMachine_GetTopState() == STATE_TOP_EPG)
                        MApp_ZUI_API_ShowWindow(HWND_EPG_COUNTDOWN_PANE, SW_HIDE);
                    else
                        MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_CLOSE_CURRENT_OSD);
                }
            }
            return TRUE;

        case EN_EXE_EPG_TIMER_COUNTDOWN_BTN_YES:
            {
                    U32 ActiveTime;
                    #if ENABLE_PVR
                    ActiveTime = MApp_GetLocalSystemTime()+EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s + EPG_RECORDER_PVR_LEADING_TIME_s;
                    #else
                    ActiveTime = MApp_GetLocalSystemTime()+EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s;
                    #endif
                    MApp_EpgTimer_ExecTimerUpAct(MApp_EpgTimer_GetNextStartUpIndex());
                    MApp_EpgTimer_ReconfigTimerFromList(ActiveTime);
                    if(MApp_TopStateMachine_GetTopState() == STATE_TOP_EPG)
                        MApp_ZUI_API_ShowWindow(HWND_EPG_COUNTDOWN_PANE, SW_HIDE);
                    else
                        MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
         return TRUE;

             case EN_EXE_EPG_TIMER_COUNTDOWN_BTN_NO:
            {
                    MApp_ZUI_ACT_ShutdownOSD();
                #if 0
                    MApp_EpgTimer_ResetStopppedTimerListItem(MApp_EpgTimer_GetNextStartUpIndex());
                    MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
                    if(MApp_TopStateMachine_GetTopState() == STATE_TOP_EPG)
                        MApp_ZUI_API_ShowWindow(HWND_EPG_COUNTDOWN_PANE, SW_HIDE);
                    else
                        MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_CLOSE_CURRENT_OSD);
                #endif
            }
        return TRUE;

#if ENABLE_PVR
            case EN_EXE_EPG_TIMERLIST_PREVITEM:
    #if ENABLE_PVR
            case EN_EXE_EPG_RECORDER_LIST_PREVITEM:
    #endif
            {
                U8 totalListItems;

                if(EN_EXE_EPG_TIMERLIST_PREVITEM)
                {
                    totalListItems = MApp_EpgTimer_GetTimerListPageItemsTotal(EN_EPGUI_TIMER_REMINDER);
                }
    #if ENABLE_PVR
                if(EN_EXE_EPG_RECORDER_LIST_PREVITEM)
                {
                     totalListItems = MApp_EpgTimer_GetTimerListPageItemsTotal(EN_EPGUI_TIMER_RECORDER);
                }
    #endif

                if(totalListItems == 0)
                {
                    break;
                }
                g_u8MenuMainItemIndex=_GetRecorderScheduleListItemIndexByHandle(MApp_ZUI_API_GetFocus());
                g_u8PrevMenuMainItemIndex = g_u8MenuMainItemIndex;

                if(g_u8MenuMainItemIndex == 0)
                {
                    if(g_TimerList_CurPageStartItem == 0)
                    {
                        g_TimerList_CurPageStartItem = (totalListItems - 1)/EPG_TIMER_LIST_ITEMS_PER_PAGE*EPG_TIMER_LIST_ITEMS_PER_PAGE;
                        g_u8MenuMainItemIndex = (totalListItems - 1)%EPG_TIMER_LIST_ITEMS_PER_PAGE;
                        MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_RECORDER_TIMER_LIST);
                    }
                    else
                    {
                        g_TimerList_CurPageStartItem -= EPG_TIMER_LIST_ITEMS_PER_PAGE;
                        g_u8MenuMainItemIndex = EPG_TIMER_LIST_ITEMS_PER_PAGE - 1;
                        MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_RECORDER_TIMER_LIST);
                    }
                }
                else
                {
                    g_u8MenuMainItemIndex-- ;
                }
            }
                break;

            case EN_EXE_EPG_TIMERLIST_NEXTITEM:
    #if ENABLE_PVR
            case EN_EXE_EPG_RECORDER_LIST_NEXTITEM:
    #endif
            {
                g_u8MenuMainItemIndex=_GetRecorderScheduleListItemIndexByHandle(MApp_ZUI_API_GetFocus());

                g_u8PrevMenuMainItemIndex = g_u8MenuMainItemIndex;
                if(g_TimerList_CurPageStartItem + g_u8MenuMainItemIndex >= (MApp_EpgTimer_GetTimerListItemsTotal(EN_EPGUI_TIMER_RECORDER) - 1))
                {  //end of all items
                    g_u8MenuMainItemIndex = 0;
                    g_TimerList_CurPageStartItem = 0;
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_RECORDER_TIMER_LIST);
                    //MApp_UiMenu_DrawAllTimerListItems();
                }
                else if(g_u8MenuMainItemIndex >= (EPG_TIMER_LIST_ITEMS_PER_PAGE - 1))
                {   //end of page
                    g_u8MenuMainItemIndex = 0;
                    g_TimerList_CurPageStartItem += EPG_TIMER_LIST_ITEMS_PER_PAGE;
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_RECORDER_TIMER_LIST);
                    //MApp_UiMenu_DrawAllTimerListItems();
                }
                else
                {
                    g_u8MenuMainItemIndex++;
                    //MApp_UiMenu_DrawTimerListItem(g_u8PrevMenuMainItemIndex);
                    //MApp_UiMenu_DrawTimerListItem(g_u8MenuMainItemIndex);
                }
                //stEpgTimerParam.u8CurTimerIdx = (g_TimerList_CurPageStartItem + g_u8MenuMainItemIndex);
            }
                break;
#endif  //ENABLE_PVR

#if (ENABLE_PVR)
        case EN_EXE_EPG_SHOW_RECORDER_SETTING:

            MApp_EpgTimer_LoadManualTimer(EN_EPGUI_TIMER_RECORDER);

            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PANEL, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_HELP_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_SYSTEM_TIME, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_EVENT_PANEL, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_SERVICE_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_SCHEDULE_LIST_PANEL, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_DATE_PREV, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_DATE_NEXT, SW_HIDE);

#if 0 //fix pvr
            MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_INFO, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_REMINDER, SW_HIDE);
#endif
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE_1, SW_HIDE);


            if(stEpgTimerParam.stEpgTimer.enRepeatMode == EN_EPGRM_AUTO)
            {
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_MIN_ITEM, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_HOUR_ITEM, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_MONTH_ITEM, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_DATE_ITEM, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_MIN_ITEM, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_HOUR_ITEM, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_MONTH_ITEM, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_DATE_ITEM, DISABLE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_MIN_ITEM, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_HOUR_ITEM, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_MONTH_ITEM, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_DATE_ITEM, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_MIN_ITEM, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_HOUR_ITEM, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_MONTH_ITEM, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_DATE_ITEM, ENABLE);
            }

//                stEpgTimerParam.stEpgTimer.enRepeatMode = (EN_EPG_TIMER_REPEAT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MODE_ADJ_INC, stEpgTimerParam.stEpgTimer.enRepeatMode, EN_EPGRM_ONCE, EN_EPGRM_MAXNUM-1, 1);
            //MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_PROGRAMME_ITEM, DISABLE);
            MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_PROGRAMME_ITEM);
            return TRUE;

        case EN_EXE_EPG_SHOW_RECORDER_TIMER_LIST:
            MApp_EpgTimer_initTmpTimerListIdx();
            MApp_EpgTimer_GetIdxFromTimerDBIdx(EN_EPGUI_TIMER_RECORDER);

            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_PAGE_TITLE_PANEL, SW_HIDE);
           // MApp_ZUI_API_ShowWindow(HWND_EPG_BGND_TITLE, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_SERVICE_TABLE_PANEL, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_EVENT_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_COUNTDOWN_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_SCHEDULE_LIST_PANEL,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REC_TIME_STEEING_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_TIMER_SAVE_DLG, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_DATE_PREV, SW_HIDE);
           // MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_DATE_NEXT, SW_HIDE);

#if 0 //fix pvr
            MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_INFO, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_OK, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_HELP_BTN_REMINDER, SW_HIDE);
#endif
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE_1, SW_HIDE);

            _ValidateRecorderTimerListUI();
            return TRUE;

        case EN_EXE_EPG_SHOW_RECORDER_TIMER_COUNTDOWN:
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);

            //MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_BGND_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_HELP_PANEL, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_TIME_PANEL, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_SERVICE_PANEL, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_EVENT_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_SCHEDULE_LIST_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_REC_TIME_STEEING_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_SCHEDULE_LIST_PANEL,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE_1, SW_HIDE);

            return TRUE;

        case EN_EXE_EPG_RECORDER_YEAR_ADJ_INC:
        case EN_EXE_EPG_RECORDER_YEAR_ADJ_DEC:
            {
                if (MApp_ZUI_API_GetFocusCheckpoint() == HWND_EPG_RECORDER_START_TIME_MIN_ITEM ||
                    MApp_ZUI_API_GetFocusCheckpoint() == HWND_EPG_RECORDER_START_TIME_HOUR_ITEM )
                {
                    stEpgTimerParam.stEpgTimer.stStartDate.u16Year = MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_YEAR_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u16Year, 1, 20, 1 );
                    stEpgTimerParam.stEpgTimer.stStartDate.u8Month = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MONTH_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Month, 1, 12, 1 );
                    stEpgTimerParam.stEpgTimer.stStartDate.u8Day = MIN( stEpgTimerParam.stEpgTimer.stStartDate.u8Day, ( U8 )MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stStartDate.u8Month ) );
                }
                else
                {
                    stEpgTimerParam.stEpgTimer.stEndDate.u16Year = MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_YEAR_ADJ_INC, stEpgTimerParam.stEpgTimer.stEndDate.u16Year, 1, 20, 1 );
                    stEpgTimerParam.stEpgTimer.stEndDate.u8Month = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MONTH_ADJ_INC, stEpgTimerParam.stEpgTimer.stEndDate.u8Month, 1, 12, 1 );
                    stEpgTimerParam.stEpgTimer.stEndDate.u8Day = MIN( stEpgTimerParam.stEpgTimer.stEndDate.u8Day, ( U8 )MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stEndDate.u8Month ) );
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_PANEL);

                return TRUE;
            }

        case EN_EXE_EPG_RECORDER_MODE_ADJ_DEC:
        case EN_EXE_EPG_RECORDER_MODE_ADJ_INC:
            {
            #if (ENABLE_PVR)
                #if SUPPORT_PVR_CRID
                stEpgTimerParam.stEpgTimer.enRepeatMode = (EN_EPG_TIMER_REPEAT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MODE_ADJ_INC, stEpgTimerParam.stEpgTimer.enRepeatMode, EN_EPGRM_AUTO, EN_EPGRM_MAXNUM-1, 1);
                #else
                stEpgTimerParam.stEpgTimer.enRepeatMode = (EN_EPG_TIMER_REPEAT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MODE_ADJ_INC, stEpgTimerParam.stEpgTimer.enRepeatMode, EN_EPGRM_ONCE, EN_EPGRM_MAXNUM-1, 1);
                #endif
                if(stEpgTimerParam.stEpgTimer.enRepeatMode == EN_EPGRM_AUTO)
                {
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_MIN_ITEM, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_HOUR_ITEM, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_MONTH_ITEM, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_DATE_ITEM, DISABLE);

                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_MIN_ITEM, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_HOUR_ITEM, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_MONTH_ITEM, DISABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_DATE_ITEM, DISABLE);
                }
                else
                {
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_MIN_ITEM, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_HOUR_ITEM, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_MONTH_ITEM, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_START_TIME_DATE_ITEM, ENABLE);

                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_MIN_ITEM, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_HOUR_ITEM, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_MONTH_ITEM, ENABLE);
                    MApp_ZUI_API_EnableWindow(HWND_EPG_RECORDER_END_TIME_DATE_ITEM, ENABLE);
                }
            #else
                stEpgTimerParam.stEpgTimer.enRepeatMode = (EN_EPG_TIMER_REPEAT_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MODE_ADJ_INC, stEpgTimerParam.stEpgTimer.enRepeatMode, EN_EPGRM_AUTO, EN_EPGRM_MAXNUM-1, 1);
            #endif

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_PANEL);
                return TRUE;
            }

        #if (SUPPORT_PVR_CRID)
         case EN_EXE_EPG_RECORDER_SPLIT_ADJ:
            if(stEpgTimerParam.stEpgTimer.bRecordSplitEvent == TRUE)
                stEpgTimerParam.stEpgTimer.bRecordSplitEvent = FALSE;
            else
                stEpgTimerParam.stEpgTimer.bRecordSplitEvent = TRUE;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_PANEL);
            //check DTG recorder #2.1.1.1 Split series
            if(stEpgTimerParam.stEpgTimer.bRecordSplitEvent == TRUE)
            {
                MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
                U16 srvPos = INVALID_SERVICE_ID;
                EventIndex CurEventIdx;

                msAPI_CM_GetServiceTypeAndPositionWithPCN(stEpgTimerParam.stEpgTimer.u8PCN,
                    stEpgTimerParam.stEpgTimer.u16SrvID, &srvType, &srvPos);

                if(MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType), srvPos, stEpgTimerParam.stEpgTimer.u16EventID, &CurEventIdx) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                {
                    //U32 u32EventStart;
                    U32 u32EventEnd;
                    EventTime stEvtTime;
                    EventIndex NextEventIdx;
                    U16        u16NextSrvID;
                    U8         u8NextPCN;
                    EventID    NextEventID;
                    U32 u32TimeCurrent;
                    //find previous event
                    if(MApp_Epg_IsEventSplit(CurEventIdx))
                    {
                        MApp_Epg_GetEventSplit(CurEventIdx, MW_EN_EPG_CRID_SEARCH_PREV, &u8NextPCN, &u16NextSrvID, &NextEventIdx);
                        MApp_Epg_GetEventID(NextEventIdx, &NextEventID);
                        //update event time
                        MApp_Epg_GetEventTime(NextEventIdx, &stEvtTime);
                        //u32EventStart = stEvtTime.u32StartTime;
                        u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                        u32TimeCurrent = MApp_GetLocalSystemTime();
                        if(u32EventEnd > u32TimeCurrent)
                        {
                            _timer_popup_type = TIMER_DTG_SPLIT_CHECK;


                            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG,TRUE);
                            //MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG_OK,FALSE);
                            MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_POPUP_DLG_YES);

                        }
                    }
                }
            }
            return TRUE;

        case EN_EXE_EPG_RECORDER_SERIES_ADJ:
            if(stEpgTimerParam.stEpgTimer.bRecordSeriesEvent == TRUE)
                stEpgTimerParam.stEpgTimer.bRecordSeriesEvent = FALSE;
            else
                stEpgTimerParam.stEpgTimer.bRecordSeriesEvent = TRUE;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_PANEL);

            //check DTG recorder #2.1.1.2 Record series
            if(stEpgTimerParam.stEpgTimer.bRecordSeriesEvent == TRUE)
            {
                MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
                U16 srvPos = INVALID_SERVICE_ID;
                EventIndex CurEventIdx;

                msAPI_CM_GetServiceTypeAndPositionWithPCN(stEpgTimerParam.stEpgTimer.u8PCN,
                    stEpgTimerParam.stEpgTimer.u16SrvID, &srvType, &srvPos);

                if(MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType), srvPos, stEpgTimerParam.stEpgTimer.u16EventID, &CurEventIdx) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                {
                    //U32 u32EventStart;
                    U32 u32EventEnd;
                    EventTime stEvtTime;
                    EventIndex NextEventIdx;
                    U16        u16NextSrvID;
                    U8         u8NextPCN;
                    EventID    NextEventID;
                    U32 u32TimeCurrent;
                    //find previous event
                    if(MApp_Epg_IsEventSeries(CurEventIdx))
                    {
                        MApp_Epg_GetEventSeries(CurEventIdx, MW_EN_EPG_CRID_SEARCH_PREV, &u8NextPCN, &u16NextSrvID, &NextEventIdx);
                        MApp_Epg_GetEventID(NextEventIdx, &NextEventID);
                        //update event time
                        MApp_Epg_GetEventTime(NextEventIdx, &stEvtTime);
                        //u32EventStart = stEvtTime.u32StartTime;
                        u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                        u32TimeCurrent = MApp_GetLocalSystemTime();
                        if(u32EventEnd > u32TimeCurrent)
                        {
                            _timer_popup_type = TIMER_DTG_SERIES_CHECK;


                            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG,TRUE);
                            //MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG_OK,FALSE);
                            MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_POPUP_DLG_YES);

                        }
                    }
                }
            }
            return TRUE;
        #endif

        case EN_EXE_EPG_RECORDER_MONTH_ADJ_DEC:
        case EN_EXE_EPG_RECORDER_MONTH_ADJ_INC:
            {
                if (MApp_ZUI_API_GetFocus() == HWND_EPG_RECORDER_START_TIME_MONTH_ITEM )
                {
                    stEpgTimerParam.stEpgTimer.stStartDate.u8Month = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MONTH_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Month, 1, 12, 1 );
                    stEpgTimerParam.stEpgTimer.stStartDate.u8Day = MIN( stEpgTimerParam.stEpgTimer.stStartDate.u8Day, ( U8 )MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stStartDate.u8Month ) );
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_RECORDER_START_TIME_MONTH_SETTING);
                }
                else
                {
                    stEpgTimerParam.stEpgTimer.stEndDate.u8Month = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MONTH_ADJ_INC, stEpgTimerParam.stEpgTimer.stEndDate.u8Month, 1, 12, 1 );
                    stEpgTimerParam.stEpgTimer.stEndDate.u8Day = MIN( stEpgTimerParam.stEpgTimer.stEndDate.u8Day, ( U8 )MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stEndDate.u8Month ) );
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_RECORDER_END_TIME_MONTH_SETTING);
                }


                return TRUE;
            }

        case EN_EXE_EPG_RECORDER_DAY_ADJ_DEC:
        case EN_EXE_EPG_RECORDER_DAY_ADJ_INC:
            {
                if (MApp_ZUI_API_GetFocus() == HWND_EPG_RECORDER_START_TIME_DATE_ITEM )
                {
                    stEpgTimerParam.stEpgTimer.stStartDate.u8Day =(U8) MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_DAY_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Day, 1, MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stStartDate.u8Month ), 1 );
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_RECORDER_START_TIME_DATE_SETTING);
                }
                else
                {
                    stEpgTimerParam.stEpgTimer.stEndDate.u8Day =(U8) MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_DAY_ADJ_INC, stEpgTimerParam.stEpgTimer.stEndDate.u8Day, 1, MApp_EpgTimer_CalDaysByMon( stEpgTimerParam.stEpgTimer.stEndDate.u8Month ), 1 );
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_RECORDER_END_TIME_DATE_SETTING);
                }


                return TRUE;
            }

        case EN_EXE_EPG_RECORDER_HOUR_ADJ_DEC:
        case EN_EXE_EPG_RECORDER_HOUR_ADJ_INC:
            {
                if (MApp_ZUI_API_GetFocus() == HWND_EPG_RECORDER_START_TIME_HOUR_ITEM )
                {
                    stEpgTimerParam.stEpgTimer.stStartDate.u8Hour = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_HOUR_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Hour, 0, 23, 1 );
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_RECORDER_START_TIME_HOUR_ITEM);
                }
                else
                {
                    stEpgTimerParam.stEpgTimer.stEndDate.u8Hour = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_HOUR_ADJ_INC, stEpgTimerParam.stEpgTimer.stEndDate.u8Hour, 0, 23, 1 );
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_RECORDER_END_TIME_HOUR_ITEM);
                }


                return TRUE;
            }

        case EN_EXE_EPG_RECORDER_MIN_ADJ_DEC:
        case EN_EXE_EPG_RECORDER_MIN_ADJ_INC:
            {
                if (MApp_ZUI_API_GetFocus() == HWND_EPG_RECORDER_START_TIME_MIN_ITEM )
                {
                    stEpgTimerParam.stEpgTimer.stStartDate.u8Min = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MIN_ADJ_INC, stEpgTimerParam.stEpgTimer.stStartDate.u8Min, 0, 59, 1 );
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_RECORDER_START_TIME_MIN_SETTING);
                }
                else
                {
                    stEpgTimerParam.stEpgTimer.stEndDate.u8Min = (U8)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_EPG_RECORDER_MIN_ADJ_INC, stEpgTimerParam.stEpgTimer.stEndDate.u8Min, 0, 59, 1 );
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_RECORDER_END_TIME_MIN_SETTING);
                }

                return TRUE;
            }

        case EN_EXE_EPG_RECORDER_PASSWORD_INPUT:
        {
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
            if(TRUE == MAPP_CIPVR_CICheckCCPinCapabilities(TRUE,FALSE,FALSE))
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_BG,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_BGND_TITLE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_BGND_START_TIME,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_BGND_END_TIME,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_BGND_SETTING,SW_HIDE);

                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD_OK,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD_TITLE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD_PRESSED_PANE,SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_PASSWORD_INPUT_1);
            }
            else
#endif
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_SETTING_SAVE);
            }
            return TRUE;
        }
        case EN_EXE_EPG_RECORDER_PASSWORD_WRONG:
        {
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD_OK,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD_TITLE,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD_PRESSED_PANE,SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_PASSWORD_INPUT_1);
            MApp_ZUI_API_SetTimer(HWND_EPG_RECORDER_PASSWORD_BG, 0, 30000);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_PASSWORD);
            return TRUE;
        }
        case EN_EXE_EPG_RECORDER_SETTING_SAVE:
            //if (msAPI_CM_CountProgram( E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY ) + msAPI_CM_CountProgram( E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY )>0)
            {
                switch ( MApp_EpgTimer_SaveTimerSetting() )
                {
                    case EN_TIMER_CHECK_PAST:
                        _timer_popup_type=TIMER_SAVE_RESULT_PAST;
                        break;

                    case EN_TIMER_CHECK_OVERLAY:
                #if (SUPPORT_PVR_CRID)
                    if (_MApp_EpgTimer_GetValidAlternate())
                    {
                       MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_ALTERNATIVE);
                    }
                    else
                #endif
                    {
                        _timer_popup_type=TIMER_SAVE_RESULT_OVERLAY;
                    }
                        break;

                    case EN_TIMER_CHECK_SUCCESS:
                        _timer_popup_type=TIMER_SAVE_RESULT_SUCCESS;
                        break;

                    default:
                        break;
                }
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PANEL,SW_HIDE);

                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG,SW_SHOW);

                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG_YES,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG_NO,SW_HIDE);

                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG_BG_L,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG_BG_C,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG_BG_R,SW_HIDE);

                MApp_ZUI_API_SetTimer(HWND_EPG_RECORDER_POPUP_DLG,0,3000);

                MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_POPUP_DLG_OK);
            }
            return TRUE;

        case EN_EXE_EPG_RECORDER_DELETE:
            {
                U8 idx  = 0;
                U8 idx1 = 0;

                idx1 = _GetRecorderScheduleListItemIndexByHandle(MApp_ZUI_API_GetFocus());
                idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1);

                MApp_EpgTimer_DelCurTimerListItem(idx);
                MApp_EpgTimer_initTmpTimerListIdx();
                MApp_EpgTimer_GetIdxFromTimerDBIdx(EN_EPGUI_TIMER_RECORDER);

                _ValidateRecorderTimerListUI();
                MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_SCHEDULE_LIST_PANEL);
            }
            return TRUE;

        case EN_EXE_EPG_RECORDER_SAVE_DLG_CLOSE:
            {
                if(_timer_popup_type == TIMER_SAVE_RESULT_SUCCESS)
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_TIMER_LIST);
                }
                else
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_CLOSE_CURRENT_OSD);
                }
            }
            return TRUE;

        #if (SUPPORT_PVR_CRID)
        case EN_EXE_EPG_RECORDER_POPUP_YES:
        {
            if(_timer_popup_type == TIMER_DTG_SERIES_CHECK)
            {
                //change recording time
                if(stEpgTimerParam.stEpgTimer.bRecordSeriesEvent == TRUE)
                {
                    MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
                    U16 srvPos = INVALID_SERVICE_ID;
                    EventIndex CurEventIdx;
                    BOOLEAN bContinuCheck = FALSE;

                    do
                    {
                        bContinuCheck = FALSE;
                        msAPI_CM_GetServiceTypeAndPositionWithPCN(stEpgTimerParam.stEpgTimer.u8PCN,
                            stEpgTimerParam.stEpgTimer.u16SrvID, &srvType, &srvPos);

                        if(MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType), srvPos, stEpgTimerParam.stEpgTimer.u16EventID, &CurEventIdx) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                        {
                            U32 u32EventStart;
                            U32 u32EventEnd;
                            EventTime stEvtTime;
                            EventIndex NextEventIdx;
                            U16        u16NextSrvID;
                            U8         u8NextPCN;
                            EventID    NextEventID;
                            U32 u32TimeCurrent;
                            //find previous event
                            if(MApp_Epg_IsEventSeries(CurEventIdx))
                            {
                                if(MApp_Epg_GetEventSeries(CurEventIdx, MW_EN_EPG_CRID_SEARCH_PREV, &u8NextPCN, &u16NextSrvID, &NextEventIdx) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                                {
                                    MApp_Epg_GetEventID(NextEventIdx, &NextEventID);
                                    //update event time
                                    MApp_Epg_GetEventTime(NextEventIdx, &stEvtTime);
                                    u32EventStart = stEvtTime.u32StartTime;
                                    u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                                    u32TimeCurrent = MApp_GetLocalSystemTime();
                                    if(u32EventEnd > u32TimeCurrent)
                                    {
                                        MApp_Epg_GetEventID(NextEventIdx, &NextEventID);
                                        MApp_Epg_GetEventTime(NextEventIdx, &stEvtTime);
                                        u32EventStart = stEvtTime.u32StartTime;
                                        u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                                        MApp_ConvertSeconds2StTime(u32EventStart, &(stEpgTimerParam.stEpgTimer.stStartDate));
                                        MApp_ConvertSeconds2StTime(u32EventEnd, &(stEpgTimerParam.stEpgTimer.stEndDate));
                                        //update event anme
                                        MApp_Epg_GetEventName(NextEventIdx, stEpgTimerParam.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN);
                                        //update event ID
                                        stEpgTimerParam.stEpgTimer.u16EventID = NextEventID;
                                        //update PCN
                                        stEpgTimerParam.stEpgTimer.u8PCN = u8NextPCN;
                                        //update Service ID
                                        stEpgTimerParam.stEpgTimer.u16SrvID = u16NextSrvID;
                                        bContinuCheck = TRUE;
                                        //printf("change to previous event\n");
                                    }
                                }
                            }
                        }
                    }
                    while(bContinuCheck);
                }

                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG, SW_HIDE);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_BGND_SETTING);
                //MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_AUTO_REC_SERIES_ITEM);

            }
            else if(_timer_popup_type == TIMER_DTG_SPLIT_CHECK)
            {
                //change recording time
                if(stEpgTimerParam.stEpgTimer.bRecordSplitEvent == TRUE)
                {
                    MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
                    U16 srvPos = INVALID_SERVICE_ID;
                    EventIndex CurEventIdx;
                    BOOLEAN bContinuCheck = FALSE;

                    do
                    {
                        bContinuCheck = FALSE;
                        msAPI_CM_GetServiceTypeAndPositionWithPCN(stEpgTimerParam.stEpgTimer.u8PCN,
                            stEpgTimerParam.stEpgTimer.u16SrvID, &srvType, &srvPos);

                        if(MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType), srvPos, stEpgTimerParam.stEpgTimer.u16EventID, &CurEventIdx) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                        {
                            U32 u32EventStart;
                            U32 u32EventEnd;
                            EventTime stEvtTime;
                            EventIndex NextEventIdx;
                            U16        u16NextSrvID;
                            U8         u8NextPCN;
                            EventID    NextEventID;
                            U32 u32TimeCurrent;
                            //find previous event
                            if(MApp_Epg_IsEventSplit(CurEventIdx))
                            {
                                if(MApp_Epg_GetEventSplit(CurEventIdx, MW_EN_EPG_CRID_SEARCH_PREV, &u8NextPCN, &u16NextSrvID, &NextEventIdx) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                                {
                                    MApp_Epg_GetEventID(NextEventIdx, &NextEventID);
                                    //update event time
                                    MApp_Epg_GetEventTime(NextEventIdx, &stEvtTime);
                                    u32EventStart = stEvtTime.u32StartTime;
                                    u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                                    u32TimeCurrent = MApp_GetLocalSystemTime();
                                    if(u32EventEnd > u32TimeCurrent)
                                    {
                                        MApp_Epg_GetEventID(NextEventIdx, &NextEventID);
                                        MApp_Epg_GetEventTime(NextEventIdx, &stEvtTime);
                                        u32EventStart = stEvtTime.u32StartTime;
                                        u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                                        MApp_ConvertSeconds2StTime(u32EventStart, &(stEpgTimerParam.stEpgTimer.stStartDate));
                                        MApp_ConvertSeconds2StTime(u32EventEnd, &(stEpgTimerParam.stEpgTimer.stEndDate));
                                        //update event anme
                                        MApp_Epg_GetEventName(NextEventIdx, stEpgTimerParam.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN);
                                        //update event ID
                                        stEpgTimerParam.stEpgTimer.u16EventID = NextEventID;
                                        //update PCN
                                        stEpgTimerParam.stEpgTimer.u8PCN = u8NextPCN;
                                        //update Service ID
                                        stEpgTimerParam.stEpgTimer.u16SrvID = u16NextSrvID;
                                        bContinuCheck = TRUE;
                                        //printf("change to previous event\n");
                                    }
                                }
                            }
                        }
                    }
                    while(bContinuCheck);
                }

                MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG, SW_HIDE);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_BGND_SETTING);
                //MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_AUTO_REC_SPLIT_ITEM);

            }


        }
            return TRUE;

        case EN_EXE_EPG_RECORDER_POPUP_NO:

            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_POPUP_DLG, SW_HIDE);

            if(_timer_popup_type == TIMER_DTG_SERIES_CHECK)
            {
                //MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_AUTO_REC_SERIES_ITEM);
            }
            else if(_timer_popup_type == TIMER_DTG_SPLIT_CHECK)
            {
                //MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_AUTO_REC_SPLIT_ITEM);
            }
            return TRUE;
        #endif

        case EN_EXE_EPG_CLOSE_RECORD_TIME_SETTING:
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_REC_TIME_STEEING_PANEL,SW_HIDE);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_RECORDER_PANEL);
                MApp_ZUI_API_RestoreFocusCheckpoint();
            }
            return TRUE;

        case EN_EXE_DLG_CONFIRM_OK:
            {
                MApp_UiPvr_RecordStop();

                MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
                msAPI_CM_SetCurrentServiceType(stFocus.enSvt);
                msAPI_CM_SetCurrentPosition(stFocus.enSvt, stFocus.u16Service);//, FALSE);
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);

                #if 0//(MHEG5_ENABLE)
                if (IS_MHEG5_COUNTRY(OSD_COUNTRY_SETTING))
                {
                    g_checkMHEGLoadingStatus = TRUE;
                    msAPI_MHEG5_SetGoBackMHEG5(false);
                }
                #endif
            }
            //go on UI display
        case EN_EXE_DLG_CONFIRM_CANCEL:
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_HIDE);
            MApp_ZUI_API_SetFocus(EpgPvrSaveNewFocus);
            return TRUE;
        case EN_EXE_EPG_RECORDER_ALTERNATIVE:
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE_1, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_EPG_PVR_ALTERNATE_BTN_BTN_OK);
                return TRUE;
            }

        case EN_EXE_EPG_RECORDER_ALTERNATIVE_OK:
            {
                S8 m_pstAlterIdx = MApp_Get_EPG_Timer_pstAlternate_Index();
                stEpgTimerParam = MApp_Get_EPG_Timer_stEpgTimerParam();
                MS_EPG_TIMER_PARAM m_AlternateEpgTimer = MApp_Get_EPG_Timer_Alternate();
                MS_EPG_TIMER* m_pstEpgTimer = MApp_Get_EPG_Timer_pstEpgTimer();
                if (m_pstAlterIdx == EPG_TIMER_Alternate)
                {
                    stEpgTimerParam = m_AlternateEpgTimer;
                    MApp_EpgTimer_SaveTimerSetting();
                }
                else if ((m_pstAlterIdx >= 0) && (m_pstEpgTimer != NULL))
                {
                    m_pstEpgTimer[m_pstAlterIdx] = m_AlternateEpgTimer.stEpgTimer;
                    MApp_EpgTimer_SaveTimerSetting();
                }

                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_RECORDER_TIMER_LIST);
                return TRUE;
            }

        case EN_EXE_EPG_RECORDER_ALTERNATIVE_CANCEL:
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_RECORDER_TIMER_LIST);
                return TRUE;
            }
#endif // (ENABLE_PVR)
    }
    return FALSE;
}

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

BOOLEAN MApp_ZUI_ACT_HandleEpgKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    //MApp_ZUI_API_ResetTimer(HWND_EPG_ALL_BGND_PANEL, 0);

    MApp_ZUI_API_ResetTimer(HWND_EPG_PRO_GUIDE_PANEL_BG, 0);

    //button click animation...
    {
        static  MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _key2btn[] =
        {
            // {VK_UP, HWND_EPG_HELP_BTN_UP},
            //  {VK_DOWN, HWND_EPG_HELP_BTN_DOWN},
            //  {VK_LEFT, HWND_EPG_HELP_BTN_LEFT},
            //  {VK_RIGHT, HWND_EPG_HELP_BTN_RIGHT},
            //  {VK_SELECT, HWND_EPG_HELP_BTN_OK},
            //  {VK_YELLOW, HWND_EPG_HELP_BTN_SCHEDULE},
            //  {VK_BLUE, HWND_EPG_HELP_BTN_REMINDER},
            //  {VK_RED, HWND_EPG_HELP_BTN_DATE_PREV},
            //  {VK_GREEN, HWND_EPG_HELP_BTN_DATE_NEXT},
            //  {VK_GREEN, HWND_EPG_HELP_BTN_INFO},
            //{VK_RED,HWND_EPG_HELP_BTN_SCHEDULE_LIST_DELETE},
            {VK_RED,HWND_EPG__RECORDER_HELP_BTN_SCHEDULE_LIST_DELETE}
        };

        U8 i;

        for (i = 0; i < COUNTOF(_key2btn); i++)
        {
            if (_key2btn[i].key == key &&
                MApp_ZUI_API_IsWindowVisible(_key2btn[i].hwnd))
            {
                MApp_ZUI_API_SetTimer(_key2btn[i].hwnd, 0, BUTTONANICLICK_PERIOD);
                MApp_ZUI_API_InvalidateWindow(_key2btn[i].hwnd);
                //allow multiple binding: break;
            }
        }
    }
    if(MApp_ZUI_API_IsSuccessor(HWND_EPG_RECORDER_PASSWORD, MApp_ZUI_API_GetFocus()))
    {
        static  PASSWORD_INPUT_DATA_STRUCT _ZUI_TBLSEG _PasswordData[] =
        {
            {
                HWND_EPG_RECORDER_PASSWORD_INPUT_1,
                HWND_EPG_RECORDER_PASSWORD_INPUT_2,
                HWND_EPG_RECORDER_PASSWORD_PRESSED_1,
                &PasswordInput,
                0
            },
            {
                HWND_EPG_RECORDER_PASSWORD_INPUT_2,
                HWND_EPG_RECORDER_PASSWORD_INPUT_3,
                HWND_EPG_RECORDER_PASSWORD_PRESSED_2,
                &PasswordInput,
                4
            },
            {
                HWND_EPG_RECORDER_PASSWORD_INPUT_3,
                HWND_EPG_RECORDER_PASSWORD_INPUT_4,
                HWND_EPG_RECORDER_PASSWORD_PRESSED_3,
                &PasswordInput,
                8
            },
            {
                HWND_EPG_RECORDER_PASSWORD_INPUT_4,
                HWND_EPG_RECORDER_PASSWORD_PRESSED_4,
                HWND_EPG_RECORDER_PASSWORD_BTN_CANCEL,
                &PasswordInput,
                12
            },
        };

        U8 i;
        for (i = 0; i < COUNTOF(_PasswordData); i++)
        {
            if (MApp_ZUI_API_GetFocus() == _PasswordData[i].hwnd)
                break;
        }
        if (i == COUNTOF(_PasswordData)) //if not in the data list, we do nothing...
            return FALSE;

        if (VK_NUM_0 <= key && key <= VK_NUM_9 && i <= 3)
        {
            *(_PasswordData[i].pVar) &= ~(PASSWORD_INPUT_MASK<<_PasswordData[i].u8ShiftBits);
            *(_PasswordData[i].pVar) |= ((key-VK_NUM_0)<<_PasswordData[i].u8ShiftBits);
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
            if (i == 3) //last one
            {
                BOOL bPinCodeCorrect = FALSE;
                U16 u16CachedPinCode = 0;
                U16 ret = 0;
                ret += (PasswordInput)&PASSWORD_INPUT_MASK;
                ret *= 10;
                ret += (PasswordInput>>4)&PASSWORD_INPUT_MASK;
                ret *= 10;
                ret += (PasswordInput>>8)&PASSWORD_INPUT_MASK;
                ret *= 10;
                ret += (PasswordInput>>12)&PASSWORD_INPUT_MASK;
                printf("..............epg messagebox 4444444444444.....0x%x  %d.........\n",PasswordInput,
                             ret);
                MAPP_CIPVR_CISendCCPin(FALSE,ret);
                MAPP_CIPVR_CICheckPinEventStatus(&bPinCodeCorrect, &u16CachedPinCode);
                if(bPinCodeCorrect)
                {
                    #if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                    stEpgTimerParam.stEpgTimer.bPinCodeCached = bPinCodeCorrect;
                    stEpgTimerParam.stEpgTimer.u16CachedPinCode = u16CachedPinCode;
                    #endif
                    MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD, SW_HIDE);
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_SETTING_SAVE);
                    PasswordInputMode = PASSWORD_MODE_INPUT;
                }
                else
                {
                    PasswordInputMode = PASSWORD_MODE_WRONG;
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_PASSWORD_WRONG);
                }
            }
            else
#endif
            {
                MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
            }
        }
        else if (VK_LEFT== key)
        {
            MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PASSWORD_PRESSED_PANE,SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_EPG_RECORDER_PASSWORD_INPUT_1);
            PasswordInput = 0;
            return 0;
        }
        else if(VK_RIGHT== key)
        {
            MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_CLOSE_CURRENT_OSD);
        }

    }
    switch(key)
    {
        #if (ENABLE_PIP)
        case VK_PIP:
            if(IsPIPSupported())
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_ENABLE_PIP_MODE);
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        #endif
        case VK_EPG:
        case VK_EXIT:
        case VK_MENU:
        case VK_CHANNEL_RETURN:

            MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;

        case VK_POWER:
            MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_POWEROFF);
            return TRUE;

        case VK_VOLUME_PLUS:
            if ( stGenSetting.g_SoundSetting.Volume < MAX_NUM_OF_VOL_LEVEL )
            {
                stGenSetting.g_SoundSetting.Volume+= 5;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            return TRUE;

        case VK_VOLUME_MINUS:
            if ( stGenSetting.g_SoundSetting.Volume > 0 )
            {
                stGenSetting.g_SoundSetting.Volume-= 5;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            return TRUE;
		
		case VK_KEYSTONE_PLUS:      //xzm @ 20171227
			printf("ACTdmp KEY_VOLUME_PLUS\n");
			stGenSetting.g_SysSetting.KeyStoneValue++;
		    if(stGenSetting.g_SysSetting.KeyStoneValue >= 38)
			stGenSetting.g_SysSetting.KeyStoneValue=38;
			
			printf("ks2=%d",stGenSetting.g_SysSetting.KeyStoneValue);
			keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			break;
			
		case VK_KEYSTONE_MINUS:
			printf("ACTdmp KEY_VOLUME_PLUS\n");
			stGenSetting.g_SysSetting.KeyStoneValue--;
			if(stGenSetting.g_SysSetting.KeyStoneValue <=-38)
			stGenSetting.g_SysSetting.KeyStoneValue=-38;

			printf("ks1=%d",stGenSetting.g_SysSetting.KeyStoneValue);
			keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			break;
		
        case VK_MUTE:
            {
                BOOLEAN bIsAudioMuted;
                bIsAudioMuted = msAPI_AUD_IsAudioMutedByUser();
                if (bIsAudioMuted == FALSE)
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                else
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
            return TRUE;

        case VK_GREEN:
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                printf("101_EPGColorKeys\n");
            }
            #endif
            /* continue to the following step */
        case VK_INFO:
            if (MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE ||MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME
                || MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
            {
                return TRUE;
            }

            if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL,SW_HIDE);
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TIME_ITEM)||MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM))
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_INFO);
            }
            return TRUE;

        case VK_RED:
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                printf("101_EPGColorKeys\n");
            }
            #endif
            /* continue to the following step */
        case VK_RECORD:
#if (ENABLE_PVR)

            if (MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE ||MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME
                || MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
            {
                return TRUE;
            }

            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_PANEL))
            {
                if(_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_TIME)
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_TIME_PAGE);
                }
                else
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_CHANNEL_PAGE);
                }
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TIME_ITEM) || MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM))
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_RECORDER_SETTING);
            }

            else if((MApp_ZUI_API_IsWindowVisible(HWND_EPG_SCHEDULE_LIST_PANEL))
                || (MApp_ZUI_API_IsWindowVisible(HWND_EPG__RECORDER_HELP_BTN_SCHEDULE_LIST_DELETE)))
            {

                if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_SCHEDULE_LIST_PANEL))
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_TIMER_DELETE_CURRENT);
                }
                else
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_DELETE);
                }
            }
#else
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_SCHEDULE_LIST_PANEL))
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_TIMER_DELETE_CURRENT);
            }
#endif

            return TRUE;

        case VK_BLUE:
            if (MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE ||MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME
                || MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
            {
                return TRUE;
            }
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                printf("101_EPGColorKeys\n");
            }
            #endif
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL))
            {
                if(_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_TIME)
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_TIME_PAGE);
                }
                else
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_CHANNEL_PAGE);
                }
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TIME_ITEM)||MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM) )
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_TIMER_MANUAL);
            }
            return TRUE;

        case VK_YELLOW:
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                printf("101_EPGColorKeys\n");
            }
            #endif
            if((MApp_ZUI_API_IsWindowVisible(HWND_EPG_SCHEDULE_LIST_PANEL))
                || (MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_SCHEDULE_LIST_PANEL)))
            {

                if(_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_TIME)
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_TIME_PAGE);
                }
                else
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_CHANNEL_PAGE);
                }

            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TIME_ITEM)|| MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM))
            {
                //MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_RECORDER_TIMER_LIST);
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_TIMER_LIST);    //Arki
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL))
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_TIMER_LIST);
            }
            else if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_PANEL))
            {
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_SHOW_TIMER_LIST);
            }
            return TRUE;
#if 0 // mark for new epg UI
        case VK_RED:
            if((MApp_ZUI_API_IsWindowVisible(HWND_EPG_HELP_BTN_SCHEDULE_LIST_DELETE))
                || (MApp_ZUI_API_IsWindowVisible(HWND_EPG__RECORDER_HELP_BTN_SCHEDULE_LIST_DELETE)))
            {
                if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_SCHEDULE_LIST_PANEL))
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_TIMER_DELETE_CURRENT);
                }
                else
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_DELETE);
                }
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_EVENT_PANEL))
            {
                //if(enDateModeIndex != EN_EPGUI_DATE_TODAY)
                //    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_DATE_ADJ_DEC);
            }
            return TRUE;

        case VK_GREEN:
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_EVENT_PANEL))
            {
                if(enDateModeIndex != EN_EPGUI_DATE_DAY_8)
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_DATE_ADJ_INC);
            }
            return TRUE;
#endif
#if 0
        case VK_TV_RADIO:
//        case VK_GREEN:
            enEpguiState = STATE_EPGUI_SWITCH_SERVICETYPE;
            break;

        case VK_CHANNEL_FAV_LIST:
            enEpguiState = STATE_EPGUI_SWITCH_FAVORITE;
            break;

#endif
        default:
            break;
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateEpg(void)
{
    ZUI_MSG(printf("[]MApp_ZUI_ACT_TerminateEpg\n");)
    MApp_EpgUI_Exit();
#if (ENABLE_ARABIC_OSD)
    ArabicCHStringFlag = FALSE;
#endif
    //Show MHEG5 if MHEG5 is exist.
    #if MHEG5_ENABLE
    if(msAPI_MHEG5_IsRunning())
        MApp_MHEG5_Set_Display(TRUE,FALSE);
    #endif
    enEpgState = _enTargetEpgState;
    _enTargetEpgState = STATE_EPG_INIT;
}

 U16 u16ExtStrLen;
LPTSTR MApp_ZUI_ACT_GetEpgDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_EPG_PAGE_DATE:
            {
                LPTSTR str = CHAR_BUFFER;
                U32    u32PageLocalTime = stTime.PageStartTime;
                ST_TIME _PageTime;

                // Draw Date DD MMM
                MApp_ConvertSeconds2StTime((S32)u32PageLocalTime, &_PageTime);
                __MApp_UlongToString( _PageTime.u8Day, str, 2 );
                str[2] = CHAR_SPACE;
                _MApp_ZUI_ACT_LoadMonthString(_PageTime.u8Month-1, &str[3] );
                str[6] = CHAR_SPACE;
                __MApp_UlongToString(_PageTime.u16Year, &str[7], 4);
                str[11] = 0;
                //str[6] = '\0';
                return CHAR_BUFFER;
            }
            break;
#if 0 // New UI no need
        case HWND_EPG_PAGE_TIME_1:
        case HWND_EPG_PAGE_TIME_2:
            {
                LPTSTR str = CHAR_BUFFER;
                ST_TIME _PageTime;
                U32 u32PageLocalTime   = stTime.PageStartTime;

                if (hwnd == HWND_EPG_PAGE_TIME_2)
                    u32PageLocalTime += SECONDS_PER_HOUR;

                MApp_ConvertSeconds2StTime(u32PageLocalTime, &_PageTime);
                str[0] = CHAR_SPACE;
                str[1] = CHAR_SPACE;
                __MApp_UlongToString( _PageTime.u8Hour, &str[2], 2 );
                str[4] = CHAR_COLON;
                __MApp_UlongToString( _PageTime.u8Min, &str[5], 2 );
                return CHAR_BUFFER;
            }
            break;
#endif
#if 0// New UI no need
        case HWND_EPG_INFO_SERVICE_TYPE:
        case HWND_EPG_SERVICE_TYPE:
            {
                switch ( MApp_EpgUI_GetFocusServiceType() )
                {
                    case E_SERVICETYPE_DTV:
                        u16TempID = en_str_DTV;
                        break;

                    case E_SERVICETYPE_RADIO:
                        u16TempID = en_str_Radio;
                        break;

#if NORDIG_FUNC //for Nordig spec v2.0
                    case E_SERVICETYPE_DATA:
                        u16TempID = en_str_Data;
                        break;
#endif
                    default:
                        break;
                }
            }
            break;
#endif
        case HWND_EPG_CHANNELITEM1_TIME:
        case HWND_EPG_CHANNELITEM2_TIME:
        case HWND_EPG_CHANNELITEM3_TIME:
        case HWND_EPG_CHANNELITEM4_TIME:
        case HWND_EPG_CHANNELITEM5_TIME:
        case HWND_EPG_CHANNELITEM6_TIME:
        case HWND_EPG_CHANNELITEM7_TIME:
        case HWND_EPG_CHANNELITEM8_TIME:
            {
                LPTSTR str = CHAR_BUFFER;

                U8  u8UiTimeIdx;
                ST_TIME _EventTime;


                MS_EPG_UI_TIME           stDispayTime;
                EventTime stEvtTime;
                U16 u16ListFirstItemIndex;

                u8UiTimeIdx = _MApp_ZUI_ACT_EpgChanneltemTimeWindowMapToIndex(hwnd);
                u16ListFirstItemIndex=u16ChannelEvtList.ListEvtIndex-u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE;

                if ( MW_INVALID_EVENT_IDX != u16ChannelEvtList.ListEvt[u16ListFirstItemIndex+u8UiTimeIdx] )
                {
                    MApp_Epg_GetEventTime(u16ChannelEvtList.ListEvt[u16ListFirstItemIndex+u8UiTimeIdx], &stEvtTime);

                    stTime.EventStart = stEvtTime.u32StartTime;
                    stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
#if ENABLE_NZ_EIT_TIME_DISPLAY
                    if ((IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))||(OSD_COUNTRY_SETTING==OSD_COUNTRY_NETHERLANDS))
                    {
                        BOOLEAN bDayLightTimeStart,bDayLightTimeEnd,bGotTOT;
                        MS_EPG_UI_TIME           stNZTime;

                        stNZTime.EventStart = stEvtTime.u32StartTime - msAPI_Timer_GetOffsetTime();
                        stNZTime.EventEnd = stNZTime.EventStart + stEvtTime.u32Duration;
                        stNZTime.EventStart +=  MApp_SI_Get_OffsetTime(stNZTime.EventStart, &bDayLightTimeStart, &bGotTOT, TRUE);
                        stNZTime.EventEnd = stNZTime.EventEnd + MApp_SI_Get_OffsetTime(stNZTime.EventEnd, &bDayLightTimeEnd, &bGotTOT, FALSE);

                        stDispayTime.EventStart = stNZTime.EventStart;
                        stDispayTime.EventEnd = stNZTime.EventEnd;
                    }
                    else
#endif
                    {
                        stDispayTime.EventStart = stTime.EventStart;
                        stDispayTime.EventEnd = stTime.EventEnd;

                    }


                    MApp_ConvertSeconds2StTime(stDispayTime.EventStart, &_EventTime);

                    // HH:MM
                    __MApp_UlongToString( _EventTime.u8Hour, str, 2 );
                    str += 2;
                    *str++=CHAR_COLON;
                    __MApp_UlongToString( _EventTime.u8Min, str, 2 );
                    str += 2;
                    //*str++=CHAR_SPACE;
                    *str++='-';

                     MApp_ConvertSeconds2StTime(stDispayTime.EventEnd, &_EventTime);

                    // HH:MM
                    __MApp_UlongToString( _EventTime.u8Hour, str, 2 );
                    str += 2;
                    *str++=CHAR_COLON;
                    __MApp_UlongToString( _EventTime.u8Min, str, 2 );
                    str += 2;

                    *str=0;
                    return CHAR_BUFFER;
                }
                else
                    u16TempID = Empty;
            }
            break;
        //case HWND_EPG_INFO_SERVICE:
        case HWND_EPG_TIMEITEM1_SERVICE:
        case HWND_EPG_TIMEITEM2_SERVICE:
        case HWND_EPG_TIMEITEM3_SERVICE:
        case HWND_EPG_TIMEITEM4_SERVICE:
        case HWND_EPG_TIMEITEM5_SERVICE:
        case HWND_EPG_TIMEITEM6_SERVICE:
        case HWND_EPG_TIMEITEM7_SERVICE:
        case HWND_EPG_TIMEITEM8_SERVICE:
            {
                LPTSTR str = CHAR_BUFFER;
                U8  u8UiSrvIdx = _MApp_ZUI_ACT_EpgTimeItemServiceWindowMapToIndex(hwnd);
                U16 u16LCN;
                U16 u16Position = au16SrvListOSD[u8UiSrvIdx];

                if (u16Position == MW_INVALID_SERVICE_IDX)
                {
                    break;
                }

                // Draw program number
                u16LCN = msAPI_CM_GetLogicalChannelNumber(stFocus.enSvt, u16Position );

                MApp_ZUI_DTV_ChNumString(u16LCN, str);

                str += MApp_ZUI_API_Strlen(str);
                *str ++ = CHAR_SPACE;

                // Draw program name
                MApp_CharTable_GetServiceNameToUCS2(stFocus.enSvt, u16Position, str, KEEP_CONTROL_CODE_NONE);

                return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_SYSTEM_TIME:
            {
                ST_TIME _SysTime;
                LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;
                //stTime.SystemTime = MApp_GetLocalSystemTime();
                MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(), &_SysTime);
#if 0
                // DD MMM YYYY
                __MApp_UlongToString( _SysTime.u8Day, str, 2 );
                str += 2;
                *str++=CHAR_SPACE; //p_string_buffer[2] = ' ';
                //MApp_ZUI_API_LoadString(
                //    MApp_EpgUI_ConvertMonth2StringID( _SysTime.u8Month), str);
                _MApp_ZUI_ACT_LoadMonthString(_SysTime.u8Month-1, str);
                str += MApp_ZUI_API_Strlen(str);
                *str++=CHAR_SPACE; //p_string_buffer[6] = ' ';
                __MApp_UlongToString( _SysTime.u16Year, str, 4 );
                str += 4;
                *str++=CHAR_SPACE; //p_string_buffer[11] = ' ';
                *str++=CHAR_SPACE; //p_string_buffer[12] = ' ';
#endif
                // HH:MM
                __MApp_UlongToString( _SysTime.u8Hour, str, 2 );
                str += 2;
                *str++=CHAR_COLON; //p_string_buffer[15] = ':';
                __MApp_UlongToString( _SysTime.u8Min, str, 2 );
                str += 2;
                *str=0; //p_string_buffer[18] = '\0';

                return CHAR_BUFFER;
            }
#if 0 // New EPG UI no use
        //for information page////////////////////////////
        case HWND_EPG_INFO_EVENT_TITLE:
            if ( MApp_EpgUI_Func_Get_CurFocusEvtIdx() < MW_MAX_NUM_OF_EVENT_IN_EPGDB )
            {
                MApp_Epg_GetEventName(MApp_EpgUI_Func_Get_CurFocusEvtIdx(), CHAR_BUFFER, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN);
                //printf("[]title=[%x][%x][%x][%x]\n", CHAR_BUFFER[0], CHAR_BUFFER[1], CHAR_BUFFER[2], CHAR_BUFFER[3]);

                if (CHAR_BUFFER[0] != 0)
                    return CHAR_BUFFER;
            }
            u16TempID = en_str_No_Information;
            break;
#endif
        case HWND_EPG_INFO_DESC_TEXT:
        {
            MEMBER_SERVICETYPE enServiceType = MApp_EpgUI_Func_Get_CurFocusSrvType();
            U16 u16Pos = MApp_EpgUI_Func_Get_CurFocusSrvPos();
            U16 u16OnId = msAPI_CM_GetON_ID(enServiceType, u16Pos);
            U16 u16TsId = msAPI_CM_GetTS_ID(enServiceType, u16Pos);
            U16 u16SrvId = msAPI_CM_GetService_ID(enServiceType, u16Pos);
            U16 *u16BufOffset = NULL;
            if ( MApp_EpgUI_Func_Get_CurFocusEvtIdx() < MW_MAX_NUM_OF_EVENT_IN_EPGDB )
            {
                U16 u16InfoEvtIdx;
                U16 u16strEndidx;

                if(_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_CHANNEL)
                {
                    u16InfoEvtIdx = u16ChannelEvtList.ListEvt[u16ChannelEvtList.ListEvtIndex];
                }
                else
                {
                    u16InfoEvtIdx = MApp_EpgUI_Func_Get_CurFocusEvtIdx();
                }

                //MApp_Epg_GetDetailDescription(u16InfoEvtIdx, CHAR_BUFFER, &u16ExtStrLen, MAX_INFO_STRING_LENGTH);
                MApp_Epg_GetDetailDescription(u16InfoEvtIdx, CHAR_BUFFER, &u16ExtStrLen, 1024); // APP String buffer is 2K == (1K * 2 Byte)

#if 1   //display guidance information text for dvb-t2
                if (u16ExtStrLen<1024)
                {
                    u16BufOffset = (U16 *)((u16ExtStrLen>0) ? (CHAR_BUFFER+u16ExtStrLen-1) : CHAR_BUFFER);

                    //treats it as service guidance text dialogue
                    if (_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_TIME)
                    {
                        if (FALSE == MApp_SI_GetServiceGuidanceInfoTextWithIDs(u16OnId, u16TsId, u16SrvId,
                                            u16BufOffset, &u16ExtStrLen, (1024-u16ExtStrLen)))
                        {
                            EPG_UI (DBG_INFO, ("No service guidance information text\n"));
                        }
                    }
                    //treats it as event guidance text dialogue
                    else if (_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_CHANNEL)
                    {
                        if (MApp_Epg_GetGuidanceDescription(u16InfoEvtIdx, u16BufOffset, &u16ExtStrLen, (1024-u16ExtStrLen)))
                        {
                            // no event guidance information, find service guidance information
                            EPG_UI (DBG_INFO, ("No event guidance information\n"));
                            if (FALSE == MApp_SI_GetServiceGuidanceInfoTextWithIDs(u16OnId, u16TsId, u16SrvId,
                                                u16BufOffset, &u16ExtStrLen, (1024-u16ExtStrLen)))
                            {
                                EPG_UI (DBG_INFO, ("No service guidance information text\n"));
                            }
                        }
                        else
                        {
                            EPG_UI (DBG_INFO, ("event guidance information text found\n"));
                        }
                    }
                }
#endif
                if(_u8InfoScrollLineCount != _u8InfoScrollLineCount_Pre || _u8InfoScrollLineCount == 0)
                {
                    _u8InfoScrollLineCount_Pre = _u8InfoScrollLineCount;

                    //MApp_EpgUI_Func_GetNext_InfoStr(CHAR_BUFFER);
                }
                    MApp_EpgUI_Func_GetNext_InfoStr(CHAR_BUFFER);

                u16strEndidx = MAX_INFO_UNIT_LENGTH* (_u8InfoScrollLineCount + 1 )-1;

                if(CHAR_BUFFER[0] != '\0' && u16strEndidx < MAX_INFO_STRING_LENGTH)
                {
                    if(u16ExtStrLen < STRING_BUFFER_LENGTH)
                        CHAR_BUFFER[u16ExtStrLen] = '\0';
                    return CHAR_BUFFER;
                }

            }
            else
            {
                //treats it as service guidance text dialogue
                if (_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_TIME)
                {
                    if (FALSE == MApp_SI_GetServiceGuidanceInfoTextWithIDs(u16OnId, u16TsId, u16SrvId,
                                        CHAR_BUFFER, &u16ExtStrLen, 1024))
                    {
                        EPG_UI (DBG_INFO, ("No service guidance information text\n"));
                    }
                    else
                    {
                        if(CHAR_BUFFER[0] != '\0' && u16ExtStrLen < MAX_INFO_UNIT_LENGTH-1)
                        {
                            CHAR_BUFFER[u16ExtStrLen] = '\0';
                            return CHAR_BUFFER;
                        }
                    }
                }
            }
            u16TempID = en_str_No_Information;
            break;
        }
        case HWND_EPG_INFO_EVENT_DATE:
            if ( MApp_EpgUI_Func_Get_CurFocusEvtIdx() < MW_MAX_NUM_OF_EVENT_IN_EPGDB )
            {
                EventTime stEvtTime;
#if 1//ENABLE_NZ_EIT_TIME_DISPLAY
                MS_EPG_UI_TIME           stNZTime;
#endif
                MApp_Epg_GetEventTime(MApp_EpgUI_Func_Get_CurFocusEvtIdx(), &stEvtTime);
                stTime.EventStart = stEvtTime.u32StartTime;
                stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;

                {
                    ST_TIME _EventTime;
                    LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;
#if ENABLE_NZ_EIT_TIME_DISPLAY
                    if ((IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))||(OSD_COUNTRY_SETTING==OSD_COUNTRY_NETHERLANDS))
                    {
                        BOOLEAN bDayLightTimeStart,bDayLightTimeEnd,bGotTOT;

                        stNZTime.EventStart = stEvtTime.u32StartTime - msAPI_Timer_GetOffsetTime();
                        stNZTime.EventEnd = stNZTime.EventStart + stEvtTime.u32Duration;
                        stNZTime.EventStart +=  MApp_SI_Get_OffsetTime(stNZTime.EventStart, &bDayLightTimeStart, &bGotTOT, TRUE);
                        stNZTime.EventEnd = stNZTime.EventEnd + MApp_SI_Get_OffsetTime(stNZTime.EventEnd, &bDayLightTimeEnd, &bGotTOT, FALSE);

                    }
                    else
#endif
                    {
                        stNZTime.EventStart = stTime.EventStart;
                        stNZTime.EventEnd = stTime.EventEnd;

                    }

                    MApp_ConvertSeconds2StTime(stNZTime.EventStart, &_EventTime);

                    // DD MMM YYYY
                    __MApp_UlongToString( _EventTime.u8Day, str, 2 );
                    str += 2;
                    *str++=CHAR_SPACE; //p_string_buffer[2] = ' ';
                    _MApp_ZUI_ACT_LoadMonthString(_EventTime.u8Month-1, str);
                    str += MApp_ZUI_API_Strlen(str);
                    *str++=CHAR_SPACE; //p_string_buffer[6] = ' ';
                    __MApp_UlongToString( _EventTime.u16Year, str, 4 );
                    str += 4;
                    *str = 0;
                    return CHAR_BUFFER;
                }
            }
            break;

        case HWND_EPG_INFO_EVENT_START_TIME:
            if ( MApp_EpgUI_Func_Get_CurFocusEvtIdx() < MW_MAX_NUM_OF_EVENT_IN_EPGDB )
            {
                EventTime stEvtTime;

                MS_EPG_UI_TIME           stDispayTime;

                if(_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_CHANNEL)
                {
                    MApp_Epg_GetEventTime(u16ChannelEvtList.ListEvt[u16ChannelEvtList.ListEvtIndex], &stEvtTime);
                }
                else
                {
                    MApp_Epg_GetEventTime(MApp_EpgUI_Func_Get_CurFocusEvtIdx(), &stEvtTime);
                }

                stTime.EventStart = stEvtTime.u32StartTime;
                stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
#if ENABLE_NZ_EIT_TIME_DISPLAY
                if ((IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))||(OSD_COUNTRY_SETTING==OSD_COUNTRY_NETHERLANDS))
                {
                    BOOLEAN bDayLightTimeStart,bDayLightTimeEnd,bGotTOT;
                    MS_EPG_UI_TIME           stNZTime;

                    stNZTime.EventStart = stEvtTime.u32StartTime - msAPI_Timer_GetOffsetTime();
                    stNZTime.EventEnd = stNZTime.EventStart + stEvtTime.u32Duration;
                    stNZTime.EventStart +=  MApp_SI_Get_OffsetTime(stNZTime.EventStart, &bDayLightTimeStart, &bGotTOT, TRUE);
                    stNZTime.EventEnd = stNZTime.EventEnd + MApp_SI_Get_OffsetTime(stNZTime.EventEnd, &bDayLightTimeEnd, &bGotTOT, FALSE);

                    stDispayTime.EventStart = stNZTime.EventStart;
                    stDispayTime.EventEnd = stNZTime.EventEnd;
                }
                else
#endif
                {
                    stDispayTime.EventStart = stTime.EventStart;
                    stDispayTime.EventEnd = stTime.EventEnd;

                }

                {
                    ST_TIME _EventTime;
                    LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;

                    MApp_ConvertSeconds2StTime(stDispayTime.EventStart, &_EventTime);

                    // HH:MM
                    __MApp_UlongToString( _EventTime.u8Hour, str, 2 );
                    str += 2;
                    *str++=CHAR_COLON; //p_string_buffer[15] = ':';
                    __MApp_UlongToString( _EventTime.u8Min, str, 2 );
                    str += 2;
                    *str++='-';
                    *str=0; //p_string_buffer[18] = '\0';
                    return CHAR_BUFFER;
                }
            }
            break;

        case HWND_EPG_INFO_EVENT_END_TIME:
            if ( MApp_EpgUI_Func_Get_CurFocusEvtIdx() < MW_MAX_NUM_OF_EVENT_IN_EPGDB )
            {
                EventTime stEvtTime;
                MS_EPG_UI_TIME           stDispayTime;



                if(_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_CHANNEL)
                {
                    MApp_Epg_GetEventTime(u16ChannelEvtList.ListEvt[u16ChannelEvtList.ListEvtIndex], &stEvtTime);
                }
                else
                {
                    MApp_Epg_GetEventTime(MApp_EpgUI_Func_Get_CurFocusEvtIdx(), &stEvtTime);
                }

                stTime.EventStart = stEvtTime.u32StartTime;
                stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
#if ENABLE_NZ_EIT_TIME_DISPLAY
                if ((IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))||(OSD_COUNTRY_SETTING==OSD_COUNTRY_NETHERLANDS))
                {
                    BOOLEAN bDayLightTimeStart,bDayLightTimeEnd,bGotTOT;
                    MS_EPG_UI_TIME           stNZTime;

                    stNZTime.EventStart = stEvtTime.u32StartTime - msAPI_Timer_GetOffsetTime();
                    stNZTime.EventEnd = stNZTime.EventStart + stEvtTime.u32Duration;
                    stNZTime.EventStart +=  MApp_SI_Get_OffsetTime(stNZTime.EventStart, &bDayLightTimeStart, &bGotTOT, TRUE);
                    stNZTime.EventEnd = stNZTime.EventEnd + MApp_SI_Get_OffsetTime(stNZTime.EventEnd, &bDayLightTimeEnd, &bGotTOT, FALSE);

                    stDispayTime.EventStart = stNZTime.EventStart;
                    stDispayTime.EventEnd = stNZTime.EventEnd;
                }
                else
#endif
                {
                    stDispayTime.EventStart = stTime.EventStart;
                    stDispayTime.EventEnd = stTime.EventEnd;

                }


                {
                    ST_TIME _EventTime;
                    LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;

                    MApp_ConvertSeconds2StTime(stDispayTime.EventEnd, &_EventTime);

                    // HH:MM
                    __MApp_UlongToString( _EventTime.u8Hour, str, 2 );
                    str += 2;
                    *str++=CHAR_COLON; //p_string_buffer[15] = ':';
                    __MApp_UlongToString( _EventTime.u8Min, str, 2 );
                    str += 2;
                    *str=0; //p_string_buffer[18] = '\0';
                    return CHAR_BUFFER;
                }
            }
            break;

#if ENABLE_EPG_INFO_DISP_GENRE_TYPE
        case HWND_EPG_INFO_EVENT_GENRE_TEXT:
            if ( MApp_EpgUI_Func_Get_CurFocusEvtIdx() < MW_MAX_NUM_OF_EVENT_IN_EPGDB )
            {
                EventIndex curEventIdx;
                MW_EN_EPG_MAIN_GENRE_TYPE eGenreType;

                if(_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_CHANNEL)
                {
                    curEventIdx = u16ChannelEvtList.ListEvt[u16ChannelEvtList.ListEvtIndex];
                }
                else
                {
                    curEventIdx = MApp_EpgUI_Func_Get_CurFocusEvtIdx();
                }
                if(MApp_Epg_GetGenreType(curEventIdx, &eGenreType) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                {
                  #if (ENABLE_CI_PLUS)
                    if(MApp_CI_IsOpMode()==TRUE)
                    {
                        if(TRUE==MApp_CI_CompareCIContentByte(eGenreType,CHAR_BUFFER,STRING_BUFFER_LENGTH))
                        {
                            return CHAR_BUFFER;
                        }
                        else
                            u16TempID = MApp_GetGenreTypeString(((U8)eGenreType & 0xF0)>>4, (U8)eGenreType & 0x0F);
                    }
                    else
                  #endif
                    {
                        u16TempID = MApp_GetGenreTypeString(((U8)eGenreType & 0xF0)>>4, (U8)eGenreType & 0x0F);
                    }
                }
            }
            break;


        case HWND_EPG_INFO_EVENT_AGE_TEXT:
            if ( MApp_EpgUI_Func_Get_CurFocusEvtIdx() < MW_MAX_NUM_OF_EVENT_IN_EPGDB )
            {
                EventIndex curEventIdx;
                U8 u8Rating;

                if(_Current_ProgramGuide_Mode == MODE_EPGUI_PROGRAMGUIDE_CHANNEL)
                {
                    curEventIdx = u16ChannelEvtList.ListEvt[u16ChannelEvtList.ListEvtIndex];
                }
                else
                {
                    curEventIdx = MApp_EpgUI_Func_Get_CurFocusEvtIdx();
                }
                if(MApp_Epg_GetEventRating(curEventIdx, &u8Rating) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                {
                    if (u8Rating < (0x10 + PARENTAL_RATE_SHIFT) && u8Rating > (0x00 + PARENTAL_RATE_SHIFT))
                    {
                        LPTSTR str = CHAR_BUFFER;
                        MApp_ZUI_API_LoadString(en_str_Age, str);
                        str += MApp_ZUI_API_Strlen(str);
                        *str++ = CHAR_SPACE;
                        __MApp_UlongToString(u8Rating, str, 2);
                        return CHAR_BUFFER;
                    }
                }
            }
            break;
#endif

        case HWND_EPG_REMINDER_PROGRAMME_SETTING:
        case HWND_EPG_RECORDER_POPUP_DLG_TEXT3:
        case HWND_EPG_REMINDER_TIMER_SAVE_DLG_MSGBOX_TEXT2:
            {
                U16                 u16Num;
                LPTSTR              str = CHAR_BUFFER;

                MEMBER_SERVICETYPE  srvType = E_SERVICETYPE_INVALID;
                U16                 srvPos = INVALID_SERVICE_ID;

                msAPI_CM_GetServiceTypeAndPositionWithPCN(stEpgTimerParam.stEpgTimer.u8PCN, stEpgTimerParam.stEpgTimer.u16SrvID, &srvType, &srvPos);

                // Draw program number
                u16Num = msAPI_CM_GetLogicalChannelNumber(srvType, srvPos);

                MApp_ZUI_DTV_ChNumString(u16Num, str);

                str += MApp_ZUI_API_Strlen(str);
                *str ++ = CHAR_SPACE;

                // Draw program name
                MApp_CharTable_GetServiceNameToUCS2(srvType, srvPos, str, KEEP_CONTROL_CODE_NONE);

                return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REMINDER_DATE_SETTING:
            {
                U16 curStringLen=0;
                U16 u16StrBuf[32];
                __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Day, u16StrBuf, 2 );
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Date));
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = 0;
                return (LPTSTR) CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REMINDER_MONTH_SETTING:
            {
                U16 curStringLen=0;
                U16 u16StrBuf[32];
                _MApp_ZUI_ACT_LoadMonthString(stEpgTimerParam.stEpgTimer.stStartDate.u8Month-1, u16StrBuf);
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Month));
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = 0;
                return (LPTSTR) CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REMINDER_HOUR_SETTING:
            {
                U16 curStringLen=0;
                U16 u16StrBuf[32];
                __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Hour, u16StrBuf, 2 );
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Hour));
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = 0;
                return (LPTSTR) CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REMINDER_MINUTE_SETTING:
            {
                U16 curStringLen=0;
                U16 u16StrBuf[32];
                __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Min, u16StrBuf, 2 );
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Minute));
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = 0;
                return (LPTSTR) CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REMINDER_MODE_SETTING:
            {
                U16 curStringLen=0;
                U16 u16StrBuf[32];

                switch(stEpgTimerParam.stEpgTimer.enRepeatMode)
                {
                    case  EN_EPGRM_DAILY:
                        u16TempID = en_str_Every_Day;
                    break;

                    case  EN_EPGRM_WEEKLY:
                        u16TempID = en_str_Weekly;
                    break;

                    default:
                    case  EN_EPGRM_ONCE:
                        u16TempID = en_str_Once;
                    break;
                }
                MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(u16TempID));
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Mode));
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = 0;
                return (LPTSTR) CHAR_BUFFER;
            }
            break;

        case HWND_EPG_SCHEDULE_LIST_BGND_TITLE_TIME:
        {
            ST_TIME _SysTime;
            LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;

            stTime.SystemTime = MApp_GetLocalSystemTime();
            MApp_ConvertSeconds2StTime(stTime.SystemTime, &_SysTime);

            // HH:MM
            __MApp_UlongToString( _SysTime.u8Hour, str, 2 );
            str += 2;
            *str++=CHAR_COLON; //p_string_buffer[15] = ':';
            __MApp_UlongToString( _SysTime.u8Min, str, 2 );
            str += 2;
            *str=0; //p_string_buffer[18] = '\0';

            return CHAR_BUFFER;
        }

        case HWND_EPG_SCHEDULE_LIST_BGND_TITLE_DATE:
        {
            ST_TIME _stTime;
            LPTSTR str = CHAR_BUFFER;


            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

            // DDth MMM
            __MApp_UlongToString( _stTime.u8Day, str, 2 );
            str += 2;
            *str++ = 't';
            *str++ = 'h';
            *str++ = CHAR_SPACE; //p_string_buffer[2] = ' ';
            _MApp_ZUI_ACT_LoadMonthString(_stTime.u8Month-1, str);
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_SPACE; //p_string_buffer[6] = ' ';
            *str = 0;
            return CHAR_BUFFER;

        }


        case HWND_EPG_SCHEDULE_LIST_ITEM_0_TITLE:
        case HWND_EPG_SCHEDULE_LIST_ITEM_1_TITLE:
        case HWND_EPG_SCHEDULE_LIST_ITEM_2_TITLE:
        case HWND_EPG_SCHEDULE_LIST_ITEM_3_TITLE:
        {
            U8 idx=0;
            //U8 idx1=0;
            LPTSTR str = CHAR_BUFFER;

            //U32 u32SearchEvtTime;// = stTime.PageStartTime;
            //EventIndex  SearchEvtIdx;
            //EventTime   stEvtTime;
            //ST_TIME     _stTime;
            //U8  u8UiSrvIdx = _MApp_ZUI_ACT_EpgTimeItemServiceWindowMapToIndex(hwnd);
            *str=0;
            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx = _GetScheduleListItemIndexByHandle(hwnd);
            #if 0
            _stTime  = _pstEpgTimer[idx].stStartDate;
            u32SearchEvtTime = MApp_ConvertStTime2Seconds(&_stTime) ;
            MApp_Epg_EventFindByTime(msAPI_SI_ToSI_Service_Type(stFocus.enSvt), stFocus.u16Service, u32SearchEvtTime, &SearchEvtIdx);
            MApp_Epg_GetEventName(SearchEvtIdx, stEpgTimerParam.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN);
            #endif
            //idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1);

            if(_pstEpgTimer[idx+_u8ScheduleStartingIdx].bNoTitle)
            {
                //MApp_ZUI_API_Strcpy(str,stEpgTimerParam.stEpgTimer.au16EvtName);
                MApp_ZUI_API_Strcpy(str, _pstEpgTimer[idx+_u8ScheduleStartingIdx].au16EvtName);
            }
            else
            {
                MApp_ZUI_API_LoadString(en_str_No_Title ,str);
            }
            str += MApp_ZUI_API_Strlen(str);

            return CHAR_BUFFER;
        }

            break;

        case HWND_EPG_SCHEDULE_LIST_ITEM_0_TIME:
        case HWND_EPG_SCHEDULE_LIST_ITEM_1_TIME:
        case HWND_EPG_SCHEDULE_LIST_ITEM_2_TIME:
        case HWND_EPG_SCHEDULE_LIST_ITEM_3_TIME:
        {
            U8 idx=0;
            //U8 idx1=0;
            LPTSTR str = CHAR_BUFFER;

            *str=0;
            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx = _GetScheduleListItemIndexByHandle(hwnd);
            //idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1);
            __MApp_UlongToString(_pstEpgTimer[idx+_u8ScheduleStartingIdx].stStartDate.u8Hour, str, 2);
            str+=2;

            *str=':';

            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx+_u8ScheduleStartingIdx].stStartDate.u8Min,str,2);


            str += 2;
            if(_pstEpgTimer[idx+_u8ScheduleStartingIdx].enTimerType == EN_EPGUI_TIMER_RECORDER)
            {
                *str='-';

                str+=1;

                __MApp_UlongToString(_pstEpgTimer[idx+_u8ScheduleStartingIdx].stEndDate.u8Hour, str, 2);
                str+=2;

                *str=':';

                str+=1;

                __MApp_UlongToString(_pstEpgTimer[idx+_u8ScheduleStartingIdx].stEndDate.u8Min,str,2);


                str += 2;
            }
            *str=0;

            return CHAR_BUFFER;
        }
            break;



        case HWND_EPG_SCHEDULE_LIST_ITEM_0_DATE:
        case HWND_EPG_SCHEDULE_LIST_ITEM_1_DATE:
        case HWND_EPG_SCHEDULE_LIST_ITEM_2_DATE:
        case HWND_EPG_SCHEDULE_LIST_ITEM_3_DATE:
        {
            U8 idx=0;
            //U8 idx1=0;
            DAYOFWEEK eDayOfWeek;


            LPTSTR str = CHAR_BUFFER;

            *str=0;

            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx = _GetScheduleListItemIndexByHandle(hwnd);
            //idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1);

            eDayOfWeek = (DAYOFWEEK) MApp_GetDayOfWeek(_pstEpgTimer[idx+_u8ScheduleStartingIdx].stStartDate.u16Year,_pstEpgTimer[idx+_u8ScheduleStartingIdx].stStartDate.u8Month,_pstEpgTimer[idx+_u8ScheduleStartingIdx].stStartDate.u8Day);

            _MApp_ZUI_ACT_LoadWeekString(eDayOfWeek, str);
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_SPACE;

            __MApp_UlongToString(_pstEpgTimer[idx+_u8ScheduleStartingIdx].stStartDate.u8Day, str, 2 );
            str += 2;

            *str++ = CHAR_SPACE;

            _MApp_ZUI_ACT_LoadMonthString(_pstEpgTimer[idx+_u8ScheduleStartingIdx].stStartDate.u8Month-1, str);
            str += 3;

            *str=0;

            return CHAR_BUFFER;
        }
            break;


        case HWND_EPG_SCHEDULE_LIST_ITEM_0_PROGRAMME:
        case HWND_EPG_SCHEDULE_LIST_ITEM_1_PROGRAMME:
        case HWND_EPG_SCHEDULE_LIST_ITEM_2_PROGRAMME:
        case HWND_EPG_SCHEDULE_LIST_ITEM_3_PROGRAMME:
        {
            U16 u16Num;
            U8 u8str_idx=0;
            U8 idx=0;
            //U8 idx1=0;
            LPTSTR str = CHAR_BUFFER;

            MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
            U16 srvPos = INVALID_SERVICE_ID;

            *str=0;

            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx = _GetScheduleListItemIndexByHandle(hwnd);
            //idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1);

            msAPI_CM_GetServiceTypeAndPositionWithPCN(_pstEpgTimer[idx+_u8ScheduleStartingIdx].u8PCN, _pstEpgTimer[idx+_u8ScheduleStartingIdx].u16SrvID, &srvType, &srvPos);

            u16Num = msAPI_CM_GetLogicalChannelNumber(srvType, srvPos);

            MApp_ZUI_DTV_ChNumString(u16Num, str);

            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_SPACE;

            MApp_CharTable_GetServiceNameToUCS2(srvType, srvPos, &str[u8str_idx], KEEP_CONTROL_CODE_NONE);
            str += MApp_ZUI_API_Strlen(str);
            *str=0;

            return CHAR_BUFFER;
        }
            break;

        case HWND_EPG_REMINDER_TIMER_SAVE_DLG_MSGBOX_TEXT1:
        case HWND_EPG_RECORDER_POPUP_DLG_TEXT1:
            {
                LPTSTR str = CHAR_BUFFER;

                *str=0;

                if(_timer_popup_type==TIMER_SAVE_RESULT_PAST)
                {
                    MApp_ZUI_API_LoadString(en_str_Timer_Past,str);
                }
                else if(_timer_popup_type==TIMER_SAVE_RESULT_OVERLAY)
                {
                    MApp_ZUI_API_LoadString(en_str_Timer_Overlay,str);
                }
                else
                {
                    MApp_ZUI_API_LoadString(en_str_Timer_Save_Success,str);
                }

                 str += MApp_ZUI_API_Strlen(str);

                *str=0;

                return CHAR_BUFFER;

            }
            break;
        case HWND_EPG_RECORDER_POPUP_DLG_TEXT2:
        case HWND_EPG_REMINDER_TIMER_SAVE_DLG_MSGBOX_TEXT3:
        {
            LPTSTR str = CHAR_BUFFER;

            //_MApp_ZUI_ACT_LoadMonthString(stEpgTimerParam.stEpgTimer.stStartDate.u8Month-1, (U16*)Month);
            //str += MApp_ZUI_API_Strlen(str);
            //*str++ = CHAR_SPACE;

            __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Day, str, 2 );
            str += 2;

            *str++ = CHAR_SPACE;

            _MApp_ZUI_ACT_LoadMonthString(stEpgTimerParam.stEpgTimer.stStartDate.u8Month-1, str);
            str += 3;

            *str++ = CHAR_SPACE;

            __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u16Year, str, 4 );
            str += 4;

            *str++ = CHAR_SPACE;
            __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Hour, str, 2 );
            str += 2;

            *str++ = CHAR_COLON;
            __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Min, str, 2 );
            str += 2;

            *str=0;
            return CHAR_BUFFER;
        }
        case HWND_EPG_COUNTDOWN_MSG_TXT:
        {
            U16 strRet[128];
            LPTSTR str = strRet;
            U32 u32CountDown_s;
            U8 u8Nodigit;

            *str=0;

            u32CountDown_s = MApp_EpgTimer_GetCountDown_s();

//            printf("MApp_GetLocalSystemTime() = %lu\n",MApp_GetLocalSystemTime());
            if (u32CountDown_s >= 10)
            {
                u8Nodigit =2;
            }
            else
            {
                u8Nodigit =1;
            }
            __MApp_UlongToString(u32CountDown_s, str, u8Nodigit);
            str += MApp_ZUI_API_Strlen(str);
            *str = CHAR_SPACE;
            str++;
            MApp_ZUI_API_Strcpy(str, MApp_ZUI_API_GetString(en_str_Sec_to_Switc_Channel));
            MApp_ZUI_API_Strcpy(CHAR_BUFFER, strRet);
            return CHAR_BUFFER;
        }
        case HWND_EPG_CHANNEL_SERVICE:
            {
                LPTSTR str = CHAR_BUFFER;
                U8  u8UiSrvIdx = stFocus.u8UiSrvIdx;
                U16 u16LCN;
                U16 u16Position = au16SrvListOSD[u8UiSrvIdx];

                // Draw program number
                u16LCN = msAPI_CM_GetLogicalChannelNumber(stFocus.enSvt, u16Position );

                MApp_ZUI_DTV_ChNumString(u16LCN, str);

                str += MApp_ZUI_API_Strlen(str);
                *str ++ = CHAR_SPACE;

                // Draw program name
                MApp_CharTable_GetServiceNameToUCS2(stFocus.enSvt, u16Position, str, KEEP_CONTROL_CODE_NONE);

                return CHAR_BUFFER;
            }
            break;
#if (ENABLE_PVR)
        case HWND_EPG_RECORDER_PROGRAMME_SETTING:
            {
                U16                 u16Num;
                LPTSTR              str = CHAR_BUFFER;

                MEMBER_SERVICETYPE  srvType = E_SERVICETYPE_INVALID;
                U16                 srvPos = INVALID_SERVICE_ID;

                msAPI_CM_GetServiceTypeAndPositionWithPCN(stEpgTimerParam.stEpgTimer.u8PCN, stEpgTimerParam.stEpgTimer.u16SrvID, &srvType, &srvPos);

                // Draw program number
                u16Num = msAPI_CM_GetLogicalChannelNumber(srvType, srvPos);

                MApp_ZUI_DTV_ChNumString(u16Num, str);

                str += MApp_ZUI_API_Strlen(str);
                *str ++ = CHAR_SPACE;

                // Draw program name
                MApp_CharTable_GetServiceNameToUCS2(srvType, srvPos, str, KEEP_CONTROL_CODE_NONE);
                //MApp_ZUI_API_Strcpy(str, stEpgTimerParam.stEpgTimer.au16EvtName);

                return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_RECORDER_START_TIME_MIN_SETTING:
            {
                    LPTSTR str = CHAR_BUFFER;

                    __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stStartDate.u8Min, str, 2 );
                    str += 2;
                    *str=0; //p_string_buffer[18] = '\0';
                    return CHAR_BUFFER;
                    /*
                    // DD MMM YYYY
                    __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stStartDate.u8Day, str, 2 );
                    str += 2;
                    *str++=CHAR_SPACE; //p_string_buffer[2] = ' ';
                    _MApp_ZUI_ACT_LoadMonthString(stEpgTimerParam.stEpgTimer.stStartDate.u8Month-1, str);
                    str += MApp_ZUI_API_Strlen(str);
                    *str++=CHAR_SPACE; //p_string_buffer[6] = ' ';
                    __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stStartDate.u16Year, str, 4 );
                    str += 4;
                    *str = 0;
                    return CHAR_BUFFER;
                    */
            }
            break;

        case HWND_EPG_RECORDER_START_TIME_HOUR_SETTING:
            {
                    LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;

                    __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stStartDate.u8Hour, str, 2 );
                    str += 2;
                    *str=0; //p_string_buffer[18] = '\0';
                    return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_RECORDER_START_TIME_MONTH_SETTING:
             {
                LPTSTR str = CHAR_BUFFER;

                _MApp_ZUI_ACT_LoadMonthString(stEpgTimerParam.stEpgTimer.stStartDate.u8Month-1, str);
                str += MApp_ZUI_API_Strlen(str);
                *str++=CHAR_SPACE; //p_string_buffer[6] = ' ';
                *str = 0;
                return CHAR_BUFFER;
             /*
                 if(stEpgTimerParam.stEpgTimer.bRecordSeriesEvent)
                     u16TempID = en_str_Yes;
                 else
                     u16TempID = en_str_No;
                     */
             }
             break;

        case HWND_EPG_RECORDER_START_TIME_DATE_SETTING:
             {
                LPTSTR str = CHAR_BUFFER;

                __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stStartDate.u8Day, str, 2 );
                str += 2;
                *str = 0;
                return CHAR_BUFFER;

             }
             break;

         case HWND_EPG_RECORDER_END_TIME_MIN_SETTING:
             {
                    LPTSTR str = CHAR_BUFFER;

                    __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stEndDate.u8Min, str, 2 );
                    str += 2;
                    *str=0; //p_string_buffer[18] = '\0';
                    return CHAR_BUFFER;
             /*
                 if(stEpgTimerParam.stEpgTimer.bRecordSplitEvent)
                     u16TempID = en_str_Yes;
                 else
                     u16TempID = en_str_No;
                     */
             }
             break;

        case HWND_EPG_RECORDER_END_TIME_HOUR_SETTING:
            {
                    LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;

                    // HH:MM
                    __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stEndDate.u8Hour, str, 2 );
                    str += 2;
                   // *str++=CHAR_COLON; //p_string_buffer[15] = ':';
                   // __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stEndDate.u8Min, str, 2 );
                   // str += 2;
                    *str=0; //p_string_buffer[18] = '\0';
                    return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_RECORDER_END_TIME_MONTH_SETTING:
            {
                    LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;

                    // DD MMM YYYY
                    //__MApp_UlongToString( stEpgTimerParam.stEpgTimer.stEndDate.u8Day, str, 2 );
                    //str += 2;
                    // *str++=CHAR_SPACE; //p_string_buffer[2] = ' ';
                    _MApp_ZUI_ACT_LoadMonthString(stEpgTimerParam.stEpgTimer.stEndDate.u8Month-1, str);
                    str += MApp_ZUI_API_Strlen(str);
                    *str++=CHAR_SPACE; //p_string_buffer[6] = ' ';
                    *str = 0;
                    return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_RECORDER_END_TIME_DATE_SETTING:
             {
                LPTSTR str = CHAR_BUFFER;

                __MApp_UlongToString( stEpgTimerParam.stEpgTimer.stEndDate.u8Day, str, 2 );
                str += 2;
                *str = 0;
                return CHAR_BUFFER;

             }
             break;

        case HWND_EPG_RECORDER_MODE_SETTING:
            {
                switch(stEpgTimerParam.stEpgTimer.enRepeatMode)
                {
                    case  EN_EPGRM_DAILY:
                        u16TempID = en_str_Every_Day;
                    break;

                    case  EN_EPGRM_WEEKLY:
                        u16TempID = en_str_Weekly;
                    break;

                    case  EN_EPGRM_ONCE:
                        u16TempID = en_str_Once;
                    break;

                    case EN_EPGRM_AUTO:
                        u16TempID = en_str_Auto;
                        break;

                    default:
                        return 0;
                }
            }
            break;

        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_TITLE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_TITLE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_TITLE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_TITLE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_TITLE:
        {
            U8 idx=0;
            U8 idx1=0;
            LPTSTR str = CHAR_BUFFER;

            *str=0;
            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx1 = _GetRecorderScheduleListItemIndexByHandle(hwnd);
            idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1+(g_TimerList_CurPageStartItem%EPG_TIMER_LIST_ITEMS_PER_PAGE));

            if(_pstEpgTimer[idx].bNoTitle)
            {
                MApp_ZUI_API_Strcpy(str,_pstEpgTimer[idx].au16EvtName);
            }
            else
            {
                MApp_ZUI_API_LoadString(en_str_No_Title ,str);
            }
            str += MApp_ZUI_API_Strlen(str);

            *str=0;

            return CHAR_BUFFER;
        }

            break;

        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_TIME:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_TIME:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_TIME:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_TIME:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_TIME:
        {
            U8 idx=0;
            U8 idx1=0;

            LPTSTR str = CHAR_BUFFER;

            *str=0;
            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx1 = _GetRecorderScheduleListItemIndexByHandle(hwnd);
            idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1+(g_TimerList_CurPageStartItem%EPG_TIMER_LIST_ITEMS_PER_PAGE));

            __MApp_UlongToString(_pstEpgTimer[idx].stStartDate.u16Year, str, 4);
            str+=4;
            *str='/';
            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx].stStartDate.u8Month, str, 2);
            str+=2;
            *str='/';
            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx].stStartDate.u8Day, str, 2);
            str+=2;
            *str=' ';
            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx].stStartDate.u8Hour, str, 2);
            str+=2;
            *str=':';
            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx].stStartDate.u8Min,str,2);
            str += 2;
            *str=0;

            return CHAR_BUFFER;
        }
            break;



        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_DATE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_DATE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_DATE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_DATE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_DATE:
        {
            U8 idx=0;
            U8 idx1=0;
            LPTSTR str = CHAR_BUFFER;

            *str=0;
            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx1 = _GetRecorderScheduleListItemIndexByHandle(hwnd);
            idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1+(g_TimerList_CurPageStartItem%EPG_TIMER_LIST_ITEMS_PER_PAGE));

            __MApp_UlongToString(_pstEpgTimer[idx].stEndDate.u16Year, str, 4);
            str+=4;
            *str='/';
            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx].stEndDate.u8Month, str, 2);
            str+=2;
            *str='/';
            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx].stEndDate.u8Day, str, 2);
            str+=2;
            *str=' ';
            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx].stEndDate.u8Hour, str, 2);
            str+=2;
            *str=':';
            str+=1;

            __MApp_UlongToString(_pstEpgTimer[idx].stEndDate.u8Min,str,2);
            str += 2;
            *str=0;

            return CHAR_BUFFER;
        }
            break;


        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_PROGRAMME:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_PROGRAMME:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_PROGRAMME:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_PROGRAMME:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_PROGRAMME:
        {
            U16 u16Num;
            U8 u8str_idx;
            U8 idx=0;
            U8 idx1=0;
            LPTSTR str = CHAR_BUFFER;

            MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
            U16 srvPos = INVALID_SERVICE_ID;

            *str=0;

            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx1 = _GetRecorderScheduleListItemIndexByHandle(hwnd);
            idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1+(g_TimerList_CurPageStartItem%EPG_TIMER_LIST_ITEMS_PER_PAGE));

            msAPI_CM_GetServiceTypeAndPositionWithPCN(_pstEpgTimer[idx].u8PCN, _pstEpgTimer[idx].u16SrvID, &srvType, &srvPos);

            u16Num = msAPI_CM_GetLogicalChannelNumber(srvType, srvPos);
            u8str_idx = MApp_GetNoOfDigit((U32)u16Num);
            __MApp_UlongToString(u16Num, str, u8str_idx);

            str[u8str_idx] = ' ';
            u8str_idx++;

            MApp_CharTable_GetServiceNameToUCS2(srvType, srvPos, &str[u8str_idx], KEEP_CONTROL_CODE_NONE);


            str += MApp_ZUI_API_Strlen(str);

            *str=0;

            return CHAR_BUFFER;
        }
            break;

        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_0_MODE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_1_MODE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_2_MODE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_3_MODE:
        case HWND_EPG_RECORDER_SCHEDULE_LIST_ITEM_4_MODE:
        {
            U8 idx=0;
            U8 idx1=0;
            LPTSTR str = CHAR_BUFFER;

            *str=0;

            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx1 = _GetRecorderScheduleListItemIndexByHandle(hwnd);
            idx  = MApp_EpgTimer_GetTimerDBIdxFromIdx(idx1+(g_TimerList_CurPageStartItem%EPG_TIMER_LIST_ITEMS_PER_PAGE));

            switch(_pstEpgTimer[idx].enRepeatMode)
            {
                case  EN_EPGRM_DAILY:
                    MApp_ZUI_API_LoadString(en_str_Every_Day ,str);
                break;

                case  EN_EPGRM_WEEKLY:
                    MApp_ZUI_API_LoadString(en_str_Weekly ,str);
                break;

                case EN_EPGRM_AUTO:
                    MApp_ZUI_API_LoadString(en_str_Auto,str);
                    break;

                default:
                case  EN_EPGRM_ONCE:
                    MApp_ZUI_API_LoadString(en_str_Once ,str);
                break;
            }

            str += MApp_ZUI_API_Strlen(str);
            *str=0;

            return CHAR_BUFFER;
        }
            break;

        case HWND_EPG_REC_TIME_STEEING_YEAR_OPTION:
            {
                LPTSTR str = CHAR_BUFFER;

                if (MApp_ZUI_API_GetFocusCheckpoint() == HWND_EPG_RECORDER_START_TIME_MIN_ITEM ||
                    MApp_ZUI_API_GetFocusCheckpoint() ==HWND_EPG_RECORDER_START_TIME_HOUR_ITEM )
                {
                    __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u16Year, str, 4 );
                }
                else
                {
                    __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stEndDate.u16Year, str, 4 );
                }
                str += MApp_ZUI_API_Strlen(str);

                *str=0;
                return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REC_TIME_STEEING_MONTH_OPTION:
            {
                LPTSTR str = CHAR_BUFFER;

                if (MApp_ZUI_API_GetFocusCheckpoint() == HWND_EPG_RECORDER_START_TIME_MIN_ITEM ||
                    MApp_ZUI_API_GetFocusCheckpoint() ==HWND_EPG_RECORDER_START_TIME_HOUR_ITEM )
                {
                    _MApp_ZUI_ACT_LoadMonthString(stEpgTimerParam.stEpgTimer.stStartDate.u8Month-1, str);
                }
                else
                {
                    _MApp_ZUI_ACT_LoadMonthString(stEpgTimerParam.stEpgTimer.stEndDate.u8Month-1, str);
                }
                str += MApp_ZUI_API_Strlen(str);

                *str=0;
                return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REC_TIME_STEEING_DATE_OPTION:
            {
                DAYOFWEEK eDayOfWeek;
                LPTSTR str = CHAR_BUFFER;

                if (MApp_ZUI_API_GetFocusCheckpoint() == HWND_EPG_RECORDER_START_TIME_MIN_ITEM ||
                    MApp_ZUI_API_GetFocusCheckpoint() ==HWND_EPG_RECORDER_START_TIME_HOUR_ITEM )
                {
                    eDayOfWeek = (DAYOFWEEK) MApp_GetDayOfWeek(stEpgTimerParam.stEpgTimer.stStartDate.u16Year, stEpgTimerParam.stEpgTimer.stStartDate.u8Month, stEpgTimerParam.stEpgTimer.stStartDate.u8Day);
                }
                else
                {
                    eDayOfWeek = (DAYOFWEEK) MApp_GetDayOfWeek(stEpgTimerParam.stEpgTimer.stEndDate.u16Year, stEpgTimerParam.stEpgTimer.stEndDate.u8Month, stEpgTimerParam.stEpgTimer.stEndDate.u8Day);
                }

                _MApp_ZUI_ACT_LoadWeekString(eDayOfWeek, str);
                str += MApp_ZUI_API_Strlen(str);
                *str++ = CHAR_SPACE;

                if (MApp_ZUI_API_GetFocusCheckpoint() == HWND_EPG_RECORDER_START_TIME_MIN_ITEM ||
                    MApp_ZUI_API_GetFocusCheckpoint() ==HWND_EPG_RECORDER_START_TIME_HOUR_ITEM )
                {
                    __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Day, str, 2 );
                }
                else
                {
                   __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stEndDate.u8Day, str, 2 );
                }
                str += 2;

                *str=0;
                return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REC_TIME_STEEING_HOUR_OPTION:
            {
                LPTSTR str = CHAR_BUFFER;

                if (MApp_ZUI_API_GetFocusCheckpoint() == HWND_EPG_RECORDER_START_TIME_MIN_ITEM ||
                    MApp_ZUI_API_GetFocusCheckpoint() ==HWND_EPG_RECORDER_START_TIME_HOUR_ITEM )
                {
                    __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Hour, str, 2 );
                }
                else
                {
                    __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stEndDate.u8Hour, str, 2 );
                }
                str += 2;

                *str=0;
                return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_REC_TIME_STEEING_MIN_OPTION:
            {
                LPTSTR str = CHAR_BUFFER;

                if (MApp_ZUI_API_GetFocusCheckpoint() == HWND_EPG_RECORDER_START_TIME_MIN_ITEM ||
                    MApp_ZUI_API_GetFocusCheckpoint() ==HWND_EPG_RECORDER_START_TIME_HOUR_ITEM )
                {
                    __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stStartDate.u8Min, str, 2 );
                }
                else
                {
                    __MApp_UlongToString(stEpgTimerParam.stEpgTimer.stEndDate.u8Min, str, 2 );
                }
                str += 2;

                *str=0;
                return CHAR_BUFFER;
            }
            break;
        case HWND_EPG_PVR_ALTERNATE_DYNAMIC_TXT:
            {
                MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
                U16 srvPos = INVALID_SERVICE_ID;
                EventIndex AlternateEvtIdx;
                MS_EPG_TIMER_PARAM m_AlternateEpgTimer = MApp_Get_EPG_Timer_Alternate();
                msAPI_CM_GetServiceTypeAndPositionWithPCN(m_AlternateEpgTimer.stEpgTimer.u8PCN, m_AlternateEpgTimer.stEpgTimer.u16SrvID, &srvType, &srvPos);
                MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType),srvPos,m_AlternateEpgTimer.stEpgTimer.u16EventID,&AlternateEvtIdx);
                MApp_Epg_GetEventName(AlternateEvtIdx, CHAR_BUFFER, EPG_TIMER_MAX_EVT_NAME_LEN);//test

                return CHAR_BUFFER;
            }
            break;

        case HWND_EPG_PVR_ALTERNATE_DYNAMIC_TXT_1:
            {
                EventTime stEvtTime;
                MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
                U16 srvPos = INVALID_SERVICE_ID;
                EventIndex AlternateEvtIdx;
                MS_EPG_TIMER_PARAM m_AlternateEpgTimer = MApp_Get_EPG_Timer_Alternate();
                ST_TIME _EventTime;
                LPTSTR str = CHAR_BUFFER; //p_string_buffer[0] = 0;
#if 1//ENABLE_NZ_EIT_TIME_DISPLAY
                MS_EPG_UI_TIME           stNZTime;
#endif

                msAPI_CM_GetServiceTypeAndPositionWithPCN(m_AlternateEpgTimer.stEpgTimer.u8PCN, m_AlternateEpgTimer.stEpgTimer.u16SrvID, &srvType, &srvPos);
                MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType),srvPos,m_AlternateEpgTimer.stEpgTimer.u16EventID,&AlternateEvtIdx);
                MApp_Epg_GetEventTime(AlternateEvtIdx, &stEvtTime);
                stTime.EventStart = stEvtTime.u32StartTime;
                stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
#if ENABLE_NZ_EIT_TIME_DISPLAY
                if ((IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))||(OSD_COUNTRY_SETTING==OSD_COUNTRY_NETHERLANDS))
                {
                    BOOLEAN bDayLightTimeStart,bDayLightTimeEnd,bGotTOT;

                    stNZTime.EventStart = stEvtTime.u32StartTime - msAPI_Timer_GetOffsetTime();
                    stNZTime.EventEnd = stNZTime.EventStart + stEvtTime.u32Duration;
                    stNZTime.EventStart +=  MApp_SI_Get_OffsetTime(stNZTime.EventStart, &bDayLightTimeStart, &bGotTOT, TRUE);
                    stNZTime.EventEnd = stNZTime.EventEnd + MApp_SI_Get_OffsetTime(stNZTime.EventEnd, &bDayLightTimeEnd, &bGotTOT, FALSE);

                }
                else
#endif
                {
                    stNZTime.EventStart = stTime.EventStart;
                    stNZTime.EventEnd = stTime.EventEnd;

                }
                    MApp_ConvertSeconds2StTime(stNZTime.EventStart, &_EventTime);

                    // HH:MM
                    __MApp_UlongToString( _EventTime.u8Hour, str, 2 );
                    str += 2;
                    *str++=CHAR_COLON; //p_string_buffer[15] = ':';
                    __MApp_UlongToString( _EventTime.u8Min, str, 2 );
                    str += 2;
                    *str=0; //p_string_buffer[18] = '\0';
                    return CHAR_BUFFER;
            }
            break;

            case HWND_EPG_PVR_WARNING_DLG_TXT_1:
            {
                if(u8PvrWarningMsgType == 1)    //Delete currently recording schedule
                {
                    u16TempID = en_str_Cannot_delete_currect_recording_channeldot;
                }
                else//(u8PvrWarningMsgType == 2)    //Change RF during recording
                {
                    u16TempID = en_str_Are_you_sure_to_change_RF;
                }
            }
            break;

            case HWND_EPG_PVR_WARNING_DLG_TXT_2:
            {
                if(u8PvrWarningMsgType == 1)    //Delete currently recording schedule
                {
                }
                else//(u8PvrWarningMsgType == 2)    //Change RF during recording
                {
                    u16TempID = en_str_It_will_stop_PVR;
                }
            }
            break;
#endif
        case HWND_EPG_RECORDER_PASSWORD_TEXT1:
        {
            if(PasswordInputMode == PASSWORD_MODE_WRONG)
            {
                U8 str[] = {"CICAM Pin Error"};
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str,strlen((char *)str));
            }
            else
            {
                U8 str[] = {"Enter CICAM Pin For"};
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str,strlen((char *)str));
            }
            return CHAR_BUFFER;
        }
        break;
        case HWND_EPG_RECORDER_PASSWORD_TEXT2:
        {
            if(PasswordInputMode == PASSWORD_MODE_WRONG)
            {
                U8 str[] = {"Try Again"};
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str,strlen((char *)str));
            }
            else
            {
                U8 str[] = {"Uninterrupted Recording"};
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str,strlen((char *)str));
            }
            return CHAR_BUFFER;
        }
        break;
        /////////////////////////////////////////////////////
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}
#endif
///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetChannelInfoDynamicValue
///  [OSD page handler] dynamic integer value provider in MENU application
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return S16 integer value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
/*
S16 MApp_ZUI_ACT_GetEpgDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_EPG_INFO_EVENT_TIME_BAR:
        {
            S32 s32EventPassedTime   = (stTime.SystemTime - stTime.EventStart);
            S32 s32EventDurationTime = (stTime.EventEnd - stTime.EventStart);

            // Draw Progress Bar
            if ( stTime.SystemTime < stTime.EventStart )
            {
                return 0;
            }
            else if ( ( stTime.SystemTime > stTime.EventEnd ) && (s32EventDurationTime>0) )
            {
                return 100;
            }
            else if ( (s32EventPassedTime>0) && (s32EventDurationTime>0) )
            {
                return (U16)( (s32EventPassedTime*100) / s32EventDurationTime );
            }
        }
        break;

        default:
            break;


    }
    return 0; //for empty  data
}
*/
U16 MApp_ZUI_ACT_GetEpgDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    switch(hwnd)
    {
        case HWND_EPG_SCHEDULE_LIST_ITEM_0_ICON:
        case HWND_EPG_SCHEDULE_LIST_ITEM_1_ICON:
        case HWND_EPG_SCHEDULE_LIST_ITEM_2_ICON:
        case HWND_EPG_SCHEDULE_LIST_ITEM_3_ICON:
        {
            U8 idx=0;

            _pstEpgTimer = (MS_EPG_TIMER*)MApp_EpgTimer_GetScheduleListBufAddr();

            idx = _GetScheduleListItemIndexByHandle(hwnd);
            if(_pstEpgTimer[idx+_u8ScheduleStartingIdx].enTimerType == EN_EPGUI_TIMER_REMINDER)
            {
                if ( ds_type == DS_FOCUS )
                    return E_BMP_EPG_IMG_ICON_REMINDER_FOCUS;
                else
                    return E_BMP_EPG_IMG_ICON_REMINDER_UNFOCUS;
            }

            if(_pstEpgTimer[idx+_u8ScheduleStartingIdx].enTimerType == EN_EPGUI_TIMER_RECORDER)
            {   if ( ds_type == DS_FOCUS )
                    return E_BMP_EPG_IMG_ICON_VIDEO_FOCUS;
                else
                    return E_BMP_EPG_IMG_ICON_VIDEO_UNFOCUS;
            }
        }
            break;

        default:
            break;
    }
return 0xFFFF; //for empty bitmap....
}
#if ENABLE_DVB

static void _MApp_ZUI_ACT_EpgTiltleKeyHandle(VIRTUAL_KEY_CODE key)
{
    switch(key)
    {
        case VK_LEFT:
        case VK_RIGHT:
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TITLE_CHANNEL))
            {
                _Current_ProgramGuide_Mode = MODE_EPGUI_PROGRAMGUIDE_TIME;
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TITLE_CHANNEL, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TITLE_TIME, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TIME_ITEM, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TYPE_TIME, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TYPE_CHANNEL, SW_HIDE);
                MApp_EpgUI_TimeItem_Switch_Page();
            }
            else
            {
                _Current_ProgramGuide_Mode = MODE_EPGUI_PROGRAMGUIDE_CHANNEL;
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TITLE_CHANNEL, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TITLE_TIME, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TIME_ITEM, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TYPE_CHANNEL, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_TYPE_TIME, SW_HIDE);
                _MApp_EpgUI_ChannelItem_RefreshEvent(stFocus.u16Service);
                MApp_EpgUI_ChannelItem_Switch_Program();
            }
            break;

        case VK_UP:/*
            if( MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TIME_ITEM))
            {
                MApp_EpgUI_Func_Get_Program_InPage(stService.u16TotalService-1,TRUE);

                // Page change or Program change
                if (stService.u16TotalService > SERVICE_PER_PAGE)
                {
                    MApp_EpgUI_TimeItem_Switch_Page();
                }
                else
                {
                    MApp_EpgUI_TimeItem_Switch_Program();
                }
                // Calculate Pr Priority for EPGDB
                MApp_Epg_SrvPriorityHandler(stFocus.u16Service);
            }
            else if( MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM))
            {
                if(u16ChannelEvtList.ListEvtCnt == 0)//no info
                {
                    ;//do nothing
                }
                else
                {
                    u16ChannelEvtList.ListEvtIndex = u16ChannelEvtList.ListEvtCnt-1;
                    MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);
                }
            }*/
            break;

        case VK_DOWN:
            if( MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TITLE_CHANNEL))
            {
                MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE_CHANNEL);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_SHOW);
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TITLE_TIME))
            {
                MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE_TIME);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_SHOW);
            }
            break;

        default:
            break;
    }

}
/////////////////////////////////////////////////////////////
#endif
S32 MApp_ZUI_ACT_EpgTitleWinProc(HWND hwnd, PMSG msg)
{
#if ENABLE_DVB

    switch(msg->message)
    {
        case MSG_KEYDOWN:
            _MApp_ZUI_ACT_EpgTiltleKeyHandle((VIRTUAL_KEY_CODE)msg->wParam);
            return 0;

        default:
            break;
    }
#endif
    return DEFAULTWINPROC(hwnd, msg);
}
#if ENABLE_DVB
static void _MApp_ZUI_ACT_EpgTimeItemKeyHandle(VIRTUAL_KEY_CODE key)
{
    switch(key)
    {
#if 0 // Mark for New EPG UI
        case VK_LEFT:
        {
            if ( enEventMode == MODE_EPGUI_EVENT_SCHEDULE )
            {
                // 1st Event in Program     or Item ctr is zero    => Time Change
                if ( (stFocus.ListEvtIdx==0) || (astScheOSD[stFocus.u8UiSrvIdx].ListEvtCnt<=1) )
                {
                    stTime.SystemTime = MApp_GetLocalSystemTime();
                    if (stTime.PageStartTime <= stTime.SystemTime)
                    {
                        MApp_EpgUI_Func_Set_PageTime(stTime.SystemTime);
                    }
                    else
                    {
                    #if (EPG_FOR_HALF_HOUR==FALSE)
                        MApp_EpgUI_Func_Set_PageTime(stTime.PageStartTime - EPG_PAGE_DURATION);

                        if (stTime.PageStartTime <= stTime.SystemTime)
                        {
                            MApp_EpgUI_Func_Set_PageTime(stTime.SystemTime);
                        }

                        MApp_EpgUI_Switch_Time(EPGUI_SWITCH_TIME);
                        enOSDCHLR = EN_OSD_CHANGE_RTOL;
                    #else
                        {
                            U32 u32EventStart;
                            EventTime stEvtTime;

                            stFocus.PoolEvtIdx = MApp_EpgUI_Func_Get_CurFocusEvtIdx();
                            MApp_Epg_GetEventTime(stFocus.PoolEvtIdx, &stEvtTime);
                            u32EventStart = stEvtTime.u32StartTime;

                            MApp_EpgUI_Func_Set_PageTime(stTime.PageStartTime - SECONDS_PER_HALF_HOUR);

                            //printf ("\n(%bu, %u) >> (%lX, %lX)\n", stFocus.ListEvtIdx, stFocus.PoolEvtIdx, u32EventStart, stTime.UTC_PageEnd);
                            if ( (u32EventStart<stTime.PageStartTime) && (stFocus.PoolEvtIdx<MW_MAX_NUM_OF_EVENT_IN_EPGDB) )
                            {
                                //printf ("<< Key Left Cur >> \n");
                                MApp_EpgUI_Switch_Time(EPGUI_SWITCH_TIME_TO_CUR_EVT);

                            }
                            else
                            {
                                //printf ("<< Key Left Prev >> \n");
                                MApp_EpgUI_Switch_Time(EPGUI_SWITCH_TIME_TO_PREV_EVT);
                            }

                            if (stTime.PageStartTime <= stTime.SystemTime)
                            {
                                MApp_EpgUI_Func_Set_PageTime(stTime.SystemTime);
                                MApp_EpgUI_Switch_Time(EPGUI_SWITCH_TIME_TO_CUR_EVT);

                            }
                        }
                    #endif
                    }
                }
                // Not 1st Event in Program    => Event Change
                else
                {
                    MApp_EpgUI_Func_Move_Focus_Event(stFocus.ListEvtIdx-1);
                    MApp_EpgUI_Switch_Event();
                }
            }
            else
            {
                U8 tmp_evt_idx = (stFocus.ListEvtIdx<1)? 1 : 0;
                MApp_EpgUI_Func_Move_Focus_Event(tmp_evt_idx);
                MApp_EpgUI_Switch_Event();
            }
        }
        break;

        case VK_RIGHT:
        {
            if ( enEventMode == MODE_EPGUI_EVENT_SCHEDULE )
            {   // Only 0 or 1 event  ||  Last Event in Program     => Time change
                if ( (astScheOSD[stFocus.u8UiSrvIdx].ListEvtCnt==0) ||
                     (stFocus.ListEvtIdx>=(astScheOSD[stFocus.u8UiSrvIdx].ListEvtCnt-1)) )
                {
                    if ( (stTime.PageEndTime) < (stTime.SystemTime/SECONDS_PER_DAY*SECONDS_PER_DAY+SECONDS_PER_DAY*MW_MAX_NUM_OF_DAY_IN_SRV) )
                    {
                    #if (EPG_FOR_HALF_HOUR==FALSE)
                        MApp_EpgUI_Func_Set_PageTime(stTime.PageEndTime);
                        MApp_EpgUI_Switch_Time(EPGUI_SWITCH_TIME);
                        enOSDCHLR = EN_OSD_CHANGE_LTOR;
                    #else
                        {
                            U32 u32EventEnd;
                            EventTime stEvtTime;

                            stFocus.PoolEvtIdx = MApp_EpgUI_Func_Get_CurFocusEvtIdx();
                            MApp_Epg_GetEventTime(stFocus.PoolEvtIdx, &stEvtTime);
                            u32EventEnd = stEvtTime.u32StartTime + stEvtTime.u32Duration;

                            MApp_EpgUI_Func_Set_PageTime(stTime.PageStartTime + SECONDS_PER_HALF_HOUR);

                            //printf ("\n(%bu, %u) >> (%lX, %lX)\n", stFocus.ListEvtIdx, stFocus.PoolEvtIdx, u32EventEnd, stTime.UTC_PageEnd);
                            if (u32EventEnd >= stTime.PageEndTime)
                            {
                                //printf ("<< Key Right Cur >> \n");
                                MApp_EpgUI_Switch_Time(EPGUI_SWITCH_TIME_TO_CUR_EVT);
                            }
                            else
                            {
                                //printf ("<< Key Right Next >> \n");
                                MApp_EpgUI_Switch_Time(EPGUI_SWITCH_TIME_TO_NEXT_EVT);
                            }
                        }
                    #endif
                    }
                }
                else    // Not Last Event in Program    => Event Change
                {
                    MApp_EpgUI_Func_Move_Focus_Event(stFocus.ListEvtIdx+1);
                    MApp_EpgUI_Switch_Event();
                }
            }
            else // ( enEventMode == MODE_EPGUI_EVENT_NOWNEXT )
            {
                U8 tmp_evt_idx = (stFocus.ListEvtIdx<1)? 1 : 0;
                MApp_EpgUI_Func_Move_Focus_Event(tmp_evt_idx);
                MApp_EpgUI_Switch_Event();
            }
        }
        break;
#endif
        case VK_LEFT:
            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME)
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_DATE_ADJ_DEC);
            break;
        case VK_RIGHT:
            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME)
                MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_DATE_ADJ_INC);
            break;

        case VK_UP:
        {
            //reset info_page var
            _u8InfoScrollLineCount = 0;
            u16AlreadyShowHowManyBytes = 0;

            if (stFocus.u16Service < 1)                            // First program in program list
            {
            #if 0
                if(MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE)
                {
                    MApp_EpgUI_Func_Get_Program_InPage(stService.u16TotalService-1,TRUE);

                    // Page change or Program change
                    if (stService.u16TotalService > SERVICE_PER_PAGE)
                    {
                        MApp_EpgUI_TimeItem_Switch_Page();
                    }
                    else
                    {
                        MApp_EpgUI_TimeItem_Switch_Program();
                    }
                }
                else
                #endif
                if( MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME)
                {
                    MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE);
                    MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_HIDE);
                }
                else
                {
                    MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE_TIME);
                    MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_SHOW);
                }
                MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
            }
            else
            {
                // Page change or Program change
                if (stFocus.u8UiSrvIdx == 0)                    // 1st Program in Page    => Page Up
                {
                    MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service-1,TRUE);
                    MApp_EpgUI_TimeItem_Switch_Page();
                }
                else
                {
                    MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service-1,TRUE);
                    MApp_EpgUI_TimeItem_Switch_Program();
                }
            }
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
                MApp_ZUI_API_InvalidateWindow(HWND_EPG_ALL_INFO_PANEL);
               // Calculate Pr Priority for EPGDB
        MApp_Epg_SrvPriorityHandler(stFocus.u16Service);

        }
        break;

        case VK_DOWN:
        {
            //reset info_page var
            _u8InfoScrollLineCount = 0;
            u16AlreadyShowHowManyBytes = 0;

            //if( MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE)
            //        MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE_TIME);
            //else
            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME)
                    MApp_EpgUI_Func_Get_Program_InPage(0,TRUE);
            else if ((stFocus.u16Service+1) >= stService.u16TotalService)            // Last Program in Program List
            {
                MApp_EpgUI_Func_Get_Program_InPage(0,TRUE);
                MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
                // Page change or Program change
                if (stService.u16TotalService > SERVICE_PER_PAGE)
                {
                    MApp_EpgUI_TimeItem_Switch_Page();
                }
                else
                {
                    MApp_EpgUI_TimeItem_Switch_Program();
                }
            }
            else// Not Last Program    => Page Down
            {
                // Page change or Program change
                if (stFocus.u8UiSrvIdx == (SERVICE_PER_PAGE-1))        // 9th program in Page
                {
                    MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service+1,TRUE);
                    MApp_EpgUI_TimeItem_Switch_Page();
                }
                else
                {
                    MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service+1,TRUE);
                    MApp_EpgUI_TimeItem_Switch_Program();
                }
            }
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
                MApp_ZUI_API_InvalidateWindow(HWND_EPG_ALL_INFO_PANEL);
             // Calculate Pr Priority for EPGDB
        MApp_Epg_SrvPriorityHandler(stFocus.u16Service);
        }
        break;

        case VK_SELECT:
        if(MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME)
        {
            return;
        }
    #if (ENABLE_EPG_MUX)
        if (MApp_IsBarkerEPG())
        {
            return;
        }
        else
    #endif  //ENABLE_EPG_MUX
        {
            if ( MApp_EpgUI_Func_Get_SrvOrder(stFocus.enSvt, stFocus.u16Service) !=
                 MApp_EpgUI_Func_Get_SrvOrder(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType())) )
            {
                #if (ENABLE_DTV_EPG)
                MApp_EIT_All_Sche_ResetFilter();
                #endif  //ENABLE_DTV_EPG

                #if ENABLE_PVR
                {
                    BYTE cRF1 = msAPI_CM_GetPhysicalChannelNumber(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
                    BYTE cRF2 = msAPI_CM_GetPhysicalChannelNumber(stFocus.enSvt, stFocus.u16Service);

                    /* Differnet RF channel */
                    if( ( cRF1 != cRF2 )
                        && ( E_PVR_STATE_RECORD == MApp_PVR_StateMachineGet()
                            || E_PVR_STATE_RECORDnPLAYBACK == MApp_PVR_StateMachineGet() )
                        && ( E_RECORD_STATE_RECORDING == MApp_Record_StateMachineGet() )
                      )
                    {
                        EpgPvrSaveNewFocus = MApp_ZUI_API_GetFocus();
                        u8PvrWarningMsgType = 2;
                        MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_EPG_PVR_WARNING_DLG_CONFIRM_BTN_CANCEL);
                        break;
                    }

                	if( ( ( E_PVR_STATE_RECORD == MApp_PVR_StateMachineGet() || E_PVR_STATE_RECORDnPLAYBACK == MApp_PVR_StateMachineGet() )
                            && ( E_RECORD_STATE_RECORDING == MApp_Record_StateMachineGet() ) )
                        || ( ( E_PVR_STATE_TIMESHIFT == MApp_PVR_StateMachineGet() )
                            && ( E_TIMESHIFT_STATE_RECORDING == MApp_TimeShift_StateMachineGet() || E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING == MApp_TimeShift_StateMachineGet() ) )
                      )
                	{
                        EpgPvrSaveNewFocus = MApp_ZUI_API_GetFocus();
                        u8PvrWarningMsgType = 2;
                        MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_EPG_PVR_WARNING_DLG_PANE, 0, 5000);
                        MApp_ZUI_API_SetFocus(HWND_EPG_PVR_WARNING_DLG_CONFIRM_BTN_CANCEL);
                        break;
                	}
                }
                #endif  //ENABLE_PVR

                {
                    //Fix mantis 1425005...(customer mantis...enter epg and then channel change and then can not channel return
                    dmSetLastWatchedOrdinal();
                    MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
                    msAPI_CM_SetCurrentServiceType(stFocus.enSvt);
                    msAPI_CM_SetCurrentPosition(stFocus.enSvt, stFocus.u16Service);
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);

                    //Cancel Freeze
                    if(MApp_IsImageFrozen())
                    {
                        MApp_SetImageFrozen(FALSE);
                        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
                    }

                    #if 0//(MHEG5_ENABLE)
                    if (IS_MHEG5_COUNTRY(OSD_COUNTRY_SETTING))
                    {
                        g_checkMHEGLoadingStatus = TRUE;
                        msAPI_MHEG5_SetGoBackMHEG5(false);
                    }
                    #endif

               #if (NEW_UI_FOR_TRUNK==FALSE)
                    //Update TVMARK Current Program
                    MApp_ZUI_API_InvalidateAllSuccessors(
                        _MApp_ZUI_ACT_EpgTimeItemServiceIndexMapToWindow(stFocus.u8UiSrvIdx));
               #endif

                    _bChannelChagne = TRUE;

                }

            }
            #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                U8  au8EvtName[255];

                if(MW_EN_EPG_FUNC_STATUS_SUCCESS == MApp_Epg_GetUCS1EventName(MApp_EpgUI_Func_Get_CurFocusEvtIdx(), au8EvtName, 255)){
                    printf("101_EPGInfo:%s\n",au8EvtName);
                }
                else{
                    printf("101_EPGInfo:(NO Event Name)\n");
                }
            }
            #endif
        }
        break;

        case VK_PAGE_UP:
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
            {
                if(_u8InfoScrollLineCount != 0)
                {
                    _u8InfoScrollLineCount--;
                    u16AlreadyShowHowManyBytes -= (u16RecordOnePageByte[_u8InfoScrollLineCount]);
                }

                MApp_ZUI_API_InvalidateWindow(HWND_EPG_ALL_INFO_PANEL);
                break;
            }

            if(stFocus.u16Service >= SERVICE_PER_PAGE)
            {
                MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service - SERVICE_PER_PAGE,TRUE);
            }

            MApp_EpgUI_TimeItem_Switch_Page();



            // Calculate Pr Priority for EPGDB
            MApp_Epg_SrvPriorityHandler(stFocus.u16Service);

            break;

        case VK_PAGE_DOWN:
            if(MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME)
            {
                return;
            }
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
            {
                if(_u8InfoScrollLineCount < u16ExtStrLen/MAX_INFO_UNIT_LENGTH)
                {
                    u16AlreadyShowHowManyBytes += u16RecordOnePageByte[_u8InfoScrollLineCount];
                    _u8InfoScrollLineCount++;
                }

                MApp_ZUI_API_InvalidateWindow(HWND_EPG_ALL_INFO_PANEL);
                break;
            }

            if ((stFocus.u16Service + SERVICE_PER_PAGE) >= stService.u16TotalService) // Last Program in Program List
            {
                MApp_EpgUI_Func_Get_Program_InPage(stService.u16TotalService - 1,TRUE);
            }
            else// Not Last Program    => Page Down
            {
                MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service + SERVICE_PER_PAGE,TRUE);
            }

            MApp_EpgUI_TimeItem_Switch_Page();



            // Calculate Pr Priority for EPGDB
            MApp_Epg_SrvPriorityHandler(stFocus.u16Service);

            break;

        case VK_INDEX:
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_HIDE);
            MApp_EpgUI_Func_Get_Program_InPage(0,TRUE);
            MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE);
            MApp_EpgUI_TimeItem_Switch_Page();
            MApp_Epg_SrvPriorityHandler(stFocus.u16Service);
            break;
        default:
            break;


    }
}
#endif
S32 MApp_ZUI_ACT_EpgTimeItemWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_KEYDOWN:
            #if ENABLE_DVB
            _MApp_ZUI_ACT_EpgTimeItemKeyHandle((VIRTUAL_KEY_CODE)msg->wParam);
            #endif
            return 0;

        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

extern void _MApp_ZUI_API_DefaultOnPaint(HWND hWnd, PAINT_PARAM * param, BOOLEAN bDrawText);

#define EPG_EVENT_BORDER            5
#if ENABLE_DVB

static void _MApp_ZUI_ACT_EpgrOnPaintOneEvent(HWND hwnd, PAINT_PARAM * param,
    U8  u8UiSrvIdx, U8 u8ListEvtIdx)
{
    RECT       rcEvent;
    RECT       *oldRect;
    DRAW_TEXT_OUT_DYNAMIC * pText = 0; //void * pDraw = 0;
    DRAWSTYLE_TYPE ds_type;

#if ENABLE_PVR
    U8 bReminderProgram = false;
    EventID   stEvtID;
#endif

    if ((u8UiSrvIdx >= SERVICE_PER_PAGE) || (u8ListEvtIdx>= astScheOSD[u8UiSrvIdx].ListEvtCnt) || au16SrvListOSD[u8UiSrvIdx] == MW_INVALID_SERVICE_IDX)
    {
        return;
    }

  #if 0
    printf ("(%bu/%bu) ListEvtIdx = %u\n", u8ListEvtIdx, astScheOSD[u8UiSrvIdx].ListEvtCnt-1, astScheOSD[u8UiSrvIdx].ListEvt[u8ListEvtIdx]);
  #else // Modified by coverity_0208
   //kk test printf ("(%d/%d) ListEvtIdx = %d\n", (int)u8ListEvtIdx, (int)astScheOSD[u8UiSrvIdx].ListEvtCnt-1, (int)astScheOSD[u8UiSrvIdx].ListEvt[u8ListEvtIdx]);
  #endif

    if ( MW_INVALID_EVENT_IDX != astScheOSD[u8UiSrvIdx].ListEvt[u8ListEvtIdx] )
    {
        EventTime stEvtTime;

        MApp_Epg_GetEventTime(astScheOSD[u8UiSrvIdx].ListEvt[u8ListEvtIdx], &stEvtTime);
        stTime.EventStart = stEvtTime.u32StartTime;
        stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;

        MApp_Epg_GetEventName(astScheOSD[u8UiSrvIdx].ListEvt[u8ListEvtIdx], CHAR_BUFFER, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN);
    }
    else
    {
        MApp_EpgUI_Func_Set_NoInfo_EventTime(u8UiSrvIdx, u8ListEvtIdx);
        //printf ("Draw_Main_Event >> No Information, and Set NoInfo Event Time\n");
        (CHAR_BUFFER)[0] = 0;    // Set event name length to 0 for "No Info"
    }

    // Set focused event, start position <x>, <width>, <background color> and <text color> of "Event"
    //replace new rectangle region, need to be restore!!
    oldRect = param->rect;
    rcEvent = *param->rect;
    param->rect = &rcEvent;


#if ENABLE_PVR
    MApp_Epg_GetEventID(astScheOSD[u8UiSrvIdx].ListEvt[u8ListEvtIdx], &stEvtID);
    bReminderProgram = MApp_EpgTimer_CheckEventInTimerlist(stTime.EventStart, stTime.EventEnd, stEvtID);
#endif
    if (rcEvent.width <= 1)
        goto END;

    pText = _ZUI_MALLOC(
        sizeof(DRAW_TEXT_OUT_DYNAMIC));
    if (pText == NULL)
    {
        __ASSERT(0);
        goto END;
    }

    {
        // 1. Focus Event
        //IF Focus in Item , then draw event use forcus style
        if(MApp_ZUI_API_IsParentFocused(hwnd))
        {
            param->bIsFocus = TRUE;
            param->bIsDisable = FALSE;
            ds_type = DS_FOCUS;
        }
        else
        {
            param->bIsFocus = FALSE;
            param->bIsDisable = FALSE;
            ds_type = DS_NORMAL;
        }

        _MApp_ZUI_API_DefaultOnPaint(hwnd, param, FALSE);
    }

#if ENABLE_PVR
    if( bReminderProgram)
    {
        clrBtn1.b_clr       = COLOR_PURPLERED;
        msAPI_OSD_DrawBlock(&clrBtn1);
    }
#endif
    // Draw Event Result in Event Area
    {
        U16 u16TextIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, ds_type, CP_TEXT_OUT);
        if (u16TextIndex != 0xFFFF)
        {
            LPTSTR str = (CHAR_BUFFER);
            // Check String
            if ( rcEvent.width > (18*3) )    // three Char
            {
                if( *str == 0 )
                {
                    MApp_ZUI_API_GetString(en_str_No_Information);
                }
            }
            else if ( rcEvent.width > 18 )    // 1 Char
            {
                MApp_ZUI_API_GetString(en_str_3Dot);
            }
            else
            {
                str[0] = 0;
            }

            if (*str != 0)
            {
                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, pText);
                pText->pString = (CHAR_BUFFER);
                rcEvent.left += EPG_EVENT_BORDER;
                rcEvent.width -= EPG_EVENT_BORDER*2;
#if ENABLE_PVR
                if( bReminderProgram)
                {
                    pText->TextColor = COLOR_WHITE;
                }
#endif
                _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, pText, &param->dc, param->rect);
            }
        }
    }

    _ZUI_FREE(pText);

END:
    param->rect = oldRect;
}

static void _MApp_ZUI_ACT_EpgOnPaintOneEventChannel(HWND hwnd, PAINT_PARAM * param,
    U8  u8UiSrvIdx, U8 u8ListEvtIdx)
{
    RECT       rcEvent;
    RECT       *oldRect;
    DRAW_TEXT_OUT_DYNAMIC * pText = 0; //void * pDraw = 0;
    DRAWSTYLE_TYPE ds_type;
    U16 u16ListFirstItemIndex;
#if ENABLE_PVR
    U8 bReminderProgram = false;
    EventID   stEvtID;
#endif

    UNUSED(u8UiSrvIdx);

    if ((u8ListEvtIdx >= SERVICE_PER_PAGE) )
    {
        return;
    }
    u16ListFirstItemIndex=u16ChannelEvtList.ListEvtIndex-u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE;

  #if 0
    printf ("(%bu/%bu) ListEvtIdx = %u\n", u8ListEvtIdx, u16ChannelEvtList.ListEvtIndex, u16ChannelEvtList.ListEvt[u16ListFirstItemIndex+u8ListEvtIdx]);
  #else // Modified by coverity_0580
//kk test    printf ("(%d/%d) ListEvtIdx = %d\n", (int)u8ListEvtIdx, (int)u16ChannelEvtList.ListEvtIndex, (int)u16ChannelEvtList.ListEvt[u16ListFirstItemIndex+u8ListEvtIdx]);
  #endif

    if ( MW_INVALID_EVENT_IDX != u16ChannelEvtList.ListEvt[u16ListFirstItemIndex+u8ListEvtIdx] )
    {
        EventTime stEvtTime;

        MApp_Epg_GetEventTime(u16ChannelEvtList.ListEvt[u16ListFirstItemIndex+u8ListEvtIdx], &stEvtTime);
        stTime.EventStart = stEvtTime.u32StartTime;
        stTime.EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;

        MApp_Epg_GetEventName(u16ChannelEvtList.ListEvt[u16ListFirstItemIndex+u8ListEvtIdx], CHAR_BUFFER, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN);
    }
    else
    {
        return;


      #if 0 // Marked by coverity_0581
        MApp_EpgUI_Func_Set_NoInfo_EventTime(u8UiSrvIdx, u8ListEvtIdx);
        //printf ("Draw_Main_Event >> No Information, and Set NoInfo Event Time\n");
        (CHAR_BUFFER)[0] = 0;    // Set event name length to 0 for "No Info"
      #endif
    }

    // Set focused event, start position <x>, <width>, <background color> and <text color> of "Event"
    //replace new rectangle region, need to be restore!!
    oldRect = param->rect;
    rcEvent = *param->rect;
    param->rect = &rcEvent;


#if ENABLE_PVR
    MApp_Epg_GetEventID(u16ChannelEvtList.ListEvt[u16ListFirstItemIndex+u8ListEvtIdx], &stEvtID);
    bReminderProgram = MApp_EpgTimer_CheckEventInTimerlist(stTime.EventStart, stTime.EventEnd, stEvtID);
#endif
    if (rcEvent.width <= 1)
        goto END;

    pText = _ZUI_MALLOC(
        sizeof(DRAW_TEXT_OUT_DYNAMIC));
    if (pText == NULL)
    {
        __ASSERT(0);
        goto END;
    }

    {
        // 1. Focus Event
        //IF Focus in Item , then draw event use forcus style
        if(MApp_ZUI_API_IsParentFocused(hwnd))
        {
            param->bIsFocus = TRUE;
            param->bIsDisable = FALSE;
            ds_type = DS_FOCUS;
        }
        else
        {
            param->bIsFocus = FALSE;
            param->bIsDisable = FALSE;
            ds_type = DS_NORMAL;
        }

        _MApp_ZUI_API_DefaultOnPaint(hwnd, param, FALSE);
    }

#if ENABLE_PVR
    if( bReminderProgram)
    {
        clrBtn1.b_clr       = COLOR_PURPLERED;
        msAPI_OSD_DrawBlock(&clrBtn1);
    }
#endif
    // Draw Event Result in Event Area
    {
        U16 u16TextIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, ds_type, CP_TEXT_OUT);
        if (u16TextIndex != 0xFFFF)
        {
            LPTSTR str = (CHAR_BUFFER);
            // Check String
            if ( rcEvent.width > (18*3) )    // three Char
            {
                if( *str == 0 )
                {
                    MApp_ZUI_API_GetString(en_str_No_Information);
                }
            }
            else if ( rcEvent.width > 18 )    // 1 Char
            {
                MApp_ZUI_API_GetString(en_str_3Dot);
            }
            else
            {
                str[0] = 0;
            }

            if (*str != 0)
            {
                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, pText);
                pText->pString = (CHAR_BUFFER);
                rcEvent.left += EPG_EVENT_BORDER;
                rcEvent.width -= EPG_EVENT_BORDER*2;
#if ENABLE_PVR
                if( bReminderProgram)
                {
                    pText->TextColor = COLOR_WHITE;
                }
#endif
                _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, pText, &param->dc, param->rect);
            }
        }
    }

    _ZUI_FREE(pText);

END:
    param->rect = oldRect;
}
#endif
S32 MApp_ZUI_ACT_EpgTimeItemEventWinProc(HWND hwnd, PMSG msg)
{
#if ENABLE_DVB

    switch(msg->message)
    {

        case MSG_PAINT:
            if ( enEventMode == MODE_EPGUI_EVENT_SCHEDULE )
            {
               _MApp_ZUI_ACT_EpgrOnPaintOneEvent(hwnd,(PAINT_PARAM *) msg->wParam, _MApp_ZUI_ACT_EpgProGuideTimeItemMapToIndex(hwnd), 0);
            }
            return 0;

        default:
            break;

    }
#endif
    return DEFAULTWINPROC(hwnd, msg);
}

S32 MApp_ZUI_ACT_EpgChannelItemEventWinProc(HWND hwnd, PMSG msg)
{
#if ENABLE_DVB

    switch(msg->message)
    {

        case MSG_PAINT:
            if ( enEventMode == MODE_EPGUI_EVENT_SCHEDULE )
            {
                _MApp_ZUI_ACT_EpgOnPaintOneEventChannel(hwnd,(PAINT_PARAM *) msg->wParam,stFocus.u8UiSrvIdx,_MApp_ZUI_ACT_EpgChanneltemEventWindowMapToIndex(hwnd));
            }
            return 0;

        default:
            break;

    }
#endif
    return DEFAULTWINPROC(hwnd, msg);
}
#if ENABLE_DVB

static void _MApp_ZUI_ACT_EpgChannelItemKeyHandle(VIRTUAL_KEY_CODE key)
{
    switch(key)
    {
        case VK_LEFT:
            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
            {
                if( stFocus.u16Service < 1 ) // First program in program list
                {
                    MApp_EpgUI_Func_Get_Program_InPage(stService.u16TotalService-1,FALSE);
                    _MApp_EpgUI_ChannelItem_RefreshEvent(stFocus.u16Service);
                    MApp_EpgUI_ChannelItem_Switch_Program();
                }
                else
                {
                    MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service-1,FALSE);
                    _MApp_EpgUI_ChannelItem_RefreshEvent(stFocus.u16Service);
                    MApp_EpgUI_ChannelItem_Switch_Program();
                }
                // Calculate Pr Priority for EPGDB
                MApp_Epg_SrvPriorityHandler(stFocus.u16Service);
            }
            break;
        case VK_RIGHT:
            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
            {
                if ((stFocus.u16Service+1) >= stService.u16TotalService)// Last Program in Program List
                {
                    MApp_EpgUI_Func_Get_Program_InPage(0,FALSE);
                    _MApp_EpgUI_ChannelItem_RefreshEvent(stFocus.u16Service);
                    MApp_EpgUI_ChannelItem_Switch_Program();
                }
                else// Not Last Program    => Page Down
                {
                    MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service+1,FALSE);
                    _MApp_EpgUI_ChannelItem_RefreshEvent(stFocus.u16Service);
                    MApp_EpgUI_ChannelItem_Switch_Program();
                }

                // Calculate Pr Priority for EPGDB
                MApp_Epg_SrvPriorityHandler(stFocus.u16Service);
             }
            break;

        case VK_UP:
            //reset info_page var
            _u8InfoScrollLineCount = 0;
            u16AlreadyShowHowManyBytes = 0;

            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_HIDE);
            }
            else if ( u16ChannelEvtList.ListEvtIndex == 0 )//First Event
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE_CHANNEL);
                MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_SHOW);
            }
            else if ((u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE) == 0)//Change to previous page
            {
            #if ADD_EVENT_BYCHANGEPAGE
                 _u8EpgChannelPageCount--;
             #endif
                u16ChannelEvtList.ListEvtIndex--;
         #if ADD_EVENT_BYCHANGEPAGE
             if(u16ChannelEvtList.ListEvtCnt%SERVICE_PER_PAGE==0)
              u16ChannelEvtList.ListEvtCnt -= SERVICE_PER_PAGE;
          else
              u16ChannelEvtList.ListEvtCnt -= (u16ChannelEvtList.ListEvtCnt%SERVICE_PER_PAGE);
         #endif
                stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
                MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);
            }
            else//move up in current page
            {
                u16ChannelEvtList.ListEvtIndex--;
                stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
            }

            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
            {
                MApp_ZUI_API_InvalidateWindow(HWND_EPG_ALL_INFO_PANEL);
            }


            break;

        case VK_DOWN:

             //reset info_page var
            _u8InfoScrollLineCount = 0;
            u16AlreadyShowHowManyBytes = 0;

        #if ADD_EVENT_BYCHANGEPAGE
            if ((u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE) == (SERVICE_PER_PAGE-1))//Change to next page
            {
          _u8EpgChannelPageCount++;
          MApp_EpgUI_Func_Add_NumberEvent(stFocus.u16Service);
            }
     #endif
            if(u16ChannelEvtList.ListEvtCnt == 0)//no info
            {
            #if ADD_EVENT_BYCHANGEPAGE
                   _u8EpgChannelPageCount=0;
         #endif
                MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
                ;//do nothing
            }
            else if ( u16ChannelEvtList.ListEvtIndex == u16ChannelEvtList.ListEvtCnt-1)//Last Event
            {
                //only one channel item case, because index start at 0.
                if(u16ChannelEvtList.ListEvtCnt != 0 && MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
                {
                    stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                    MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
                }
                else
                {
                #if ADD_EVENT_BYCHANGEPAGE
                      _u8EpgChannelPageCount=0;
              MApp_EpgUI_Func_Add_NumberEvent(stFocus.u16Service);
          #endif
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE);
                    MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_HIDE);
                    u16ChannelEvtList.ListEvtIndex=0;
                    stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                    MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);
                }
            }
            else if ((u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE) == (SERVICE_PER_PAGE-1))//Change to next page
            {
                u16ChannelEvtList.ListEvtIndex++;
                stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
                MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);
                MS_DEBUG_MSG(printf("u16ChannelEvtList.ListEvtIndex:%d\n", u16ChannelEvtList.ListEvtIndex));
            }
            else if(MApp_ZUI_API_GetFocus()==HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)//First Event
            {
            #if ADD_EVENT_BYCHANGEPAGE
                   _u8EpgChannelPageCount=0;
         #endif
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
            }
            else//move down in current page
            {
                u16ChannelEvtList.ListEvtIndex++;
                stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
            }

            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
                MApp_ZUI_API_InvalidateWindow(HWND_EPG_ALL_INFO_PANEL);
            break;

        case VK_PAGE_UP:
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
            {
                if(_u8InfoScrollLineCount != 0)
                {
                    _u8InfoScrollLineCount--;
                    u16AlreadyShowHowManyBytes -= (u16RecordOnePageByte[_u8InfoScrollLineCount]);
                }

                MApp_ZUI_API_InvalidateWindow(HWND_EPG_ALL_INFO_PANEL);
                break;
            }

            if(u16ChannelEvtList.ListEvtIndex >= MAX_PAGE_EVENTS_IN_SERVICE)
            {
                u16ChannelEvtList.ListEvtIndex -= MAX_PAGE_EVENTS_IN_SERVICE;
                stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
            }


            MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);

            break;

        case VK_PAGE_DOWN:
            if(MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
            {
                return;
            }
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
            {
                if(_u8InfoScrollLineCount < u16ExtStrLen/MAX_INFO_UNIT_LENGTH)
                {
                    u16AlreadyShowHowManyBytes += u16RecordOnePageByte[_u8InfoScrollLineCount];
                    _u8InfoScrollLineCount++;
                }

                MApp_ZUI_API_InvalidateWindow(HWND_EPG_ALL_INFO_PANEL);
                break;
            }

            if ((u16ChannelEvtList.ListEvtIndex + MAX_PAGE_EVENTS_IN_SERVICE) >= u16ChannelEvtList.ListEvtCnt-1) // Last event in List
            {
                u16ChannelEvtList.ListEvtIndex = u16ChannelEvtList.ListEvtCnt-1;
                stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
            }
            else// Not Last Program    => Page Down
            {
                u16ChannelEvtList.ListEvtIndex += MAX_PAGE_EVENTS_IN_SERVICE;
                stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgProGuideChannelItemIndexMapToWindow(u16ChannelEvtList.ListEvtIndex%SERVICE_PER_PAGE));
            }

            MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);

            break;

        case VK_INDEX:
            MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_UP_ARROW, SW_HIDE);
            u16ChannelEvtList.ListEvtIndex = 0 ;
            stFocus.ListEvtIdx = u16ChannelEvtList.ListEvtIndex;
            MApp_ZUI_API_InvalidateWindow(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM);
            MApp_ZUI_API_SetFocus(HWND_EPG_PRO_GUIDE_TITLE);
            break;
        default:
            break;
    }

}
#endif
/////////////////////////////////////////////////////////////

S32 MApp_ZUI_ACT_EpgChannelItemWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_KEYDOWN:
            #if ENABLE_DVB
            _MApp_ZUI_ACT_EpgChannelItemKeyHandle((VIRTUAL_KEY_CODE)msg->wParam);
            #endif
            return 0;

        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

/////////////////////////////////////////////////////////////
S32 MApp_ZUI_EpgUpdateAllTimeItemWinProc(HWND hwnd, PMSG msg)
{
#if ENABLE_DVB

    switch(msg->message)
    {
        case MSG_CREATE:
            MApp_ZUI_API_SetTimer(hwnd, 0, EPGUI_UPDATE_PERIOD);
            return 0;
        break;

        case MSG_TIMER:
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_TIME_ITEM) && hwnd == HWND_EPG_PRO_GUIDE_TIME_ITEM)
            {
                U8 i=0;

                if( _bChannelChagne )
                {
                    _bChannelChagne = FALSE;
                    stTime.SystemTime = MApp_GetLocalSystemTime();
                }
                else
                {
                    if (enDateModeIndex == EN_EPGUI_DATE_TODAY)
                    {
                        stTime.SystemTime = MApp_GetLocalSystemTime();
                    }
                    else
                    {
                        stTime.SystemTime = stTime.SystemTime + EPGUI_UPDATE_PERIOD/1000;
                    }
                }


                MApp_EpgUI_Func_Set_PageTime(stTime.SystemTime);
                MApp_ZUI_API_ShowWindow(HWND_EPG_SYSTEM_TIME,SW_SHOW);

                for (i = 0; i < SERVICE_PER_PAGE; i++)
                {
                    _MApp_EpgUI_TimeItem_RefreshEvent(i);
                }
                if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_ALL_INFO_PANEL))
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_ALL_INFO_PANEL);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
                return 0;
            }
            else if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_PRO_GUIDE_CHANNEL_ITEM))
            {

                if (MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE ||MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_TIME
                || MApp_ZUI_API_GetFocus() == HWND_EPG_PRO_GUIDE_TITLE_CHANNEL)
                {
                     _MApp_EpgUI_ChannelItem_RefreshEvent(stFocus.u16Service);
                     MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
                }
                return 0;
            }
            else if( MApp_ZUI_API_IsWindowVisible(HWND_EPG_SCHEDULE_LIST_BGND_TITLE) )
            {
                stTime.SystemTime = MApp_GetLocalSystemTime();
                MApp_ZUI_API_ShowWindow(HWND_EPG_SCHEDULE_LIST_BGND_TITLE_TIME,SW_SHOW);
                MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
                return 0;
            }
        break;

        default:
        break;
    }
#endif
    return DEFAULTWINPROC(hwnd, msg);
}

////////////////////////////////////////////////////////////

S32 MApp_ZUI_ACT_EpgTimePaneWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_CREATE:
            {
                MApp_ZUI_API_SetTimer(hWnd, 0, 30*1000);
            }
            break;

        case MSG_TIMER:
            {
                //if the time is up, update all time/date information...
                MApp_ZUI_API_InvalidateAllSuccessors(hWnd);
            }
            break;
        default:
            break;


    }

    return DEFAULTWINPROC(hWnd, pMsg);
}

static void _MApp_ZUI_ACT_EpgScheduleKeyHandle(VIRTUAL_KEY_CODE key)
{
    switch(key)
    {
        case VK_UP:
            if(stEpgTimerParam.u8CurTimerIdx != 0)
            {
                stEpgTimerParam.u8CurTimerIdx--;
            }
            if( ((stEpgTimerParam.u8CurTimerIdx+1)%SCHEDULE_LIST_PER_PAGE == 0) &&_u8ScheduleStartingIdx != 0)
            {
                _u8ScheduleStartingIdx -= SCHEDULE_LIST_PER_PAGE;
            }

            _ValidateTimerListUI();
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_SCHEDULE_LIST_PANEL);
            MApp_ZUI_API_SetFocus(_GetScheduleListItemHandleByIndex(stEpgTimerParam.u8CurTimerIdx));

            break;

        case VK_DOWN:
            if(stEpgTimerParam.u8CurTimerIdx + 1 < MApp_EpgUI_GetNumOfTimers())
            {
                stEpgTimerParam.u8CurTimerIdx++;
                if( stEpgTimerParam.u8CurTimerIdx%SCHEDULE_LIST_PER_PAGE == 0)
                _u8ScheduleStartingIdx += SCHEDULE_LIST_PER_PAGE;
            }

            _ValidateTimerListUI();
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_SCHEDULE_LIST_PANEL);
            MApp_ZUI_API_SetFocus(_GetScheduleListItemHandleByIndex(stEpgTimerParam.u8CurTimerIdx));
            break;

        default:
            break;
    }

}


S32 MApp_ZUI_ACT_EpgTimerListItemWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_NOTIFY_SETFOCUS:
             //stEpgTimerParam.u8CurTimerIdx= _GetScheduleListItemIndexByHandle(hwnd);
             break;

        case MSG_KEYDOWN:
            _MApp_ZUI_ACT_EpgScheduleKeyHandle((VIRTUAL_KEY_CODE)msg->wParam);
            return 0;

        default:
            break;
    }


    return DEFAULTWINPROC(hwnd, msg);

}


S32 MApp_ZUI_ACT_EpgTimerSaveDialogWinProc(HWND hwnd, PMSG msg)
{
#if ENABLE_DVB

    switch(msg->message)
    {
        case MSG_NOTIFY_SHOW:
            {
                U32 timeout_ms = MApp_ZUI_API_GetWindowData(hwnd);
                if (timeout_ms > 0)
                {
                    //setting AP timeout, auto close
                    MApp_ZUI_API_SetTimer(hwnd, 0, timeout_ms);
                }
            }
            break;

        case MSG_TIMER:
            {
                if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_TIMER_SAVE_DLG))
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_TIMER_SAVE_DLG_CLOSE);
                }
                else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_POPUP_DLG))
                {
                    if(_timer_popup_type == TIMER_DTG_SERIES_CHECK)
                         MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_POPUP_NO);
                    else
                        MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_RECORDER_SAVE_DLG_CLOSE);
                }
                else if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_REC_TIME_STEEING_PANEL))
                {
                    MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_CLOSE_RECORD_TIME_SETTING);
                }
            }
            break;

        default:
            break;

    }
#endif
    return DEFAULTWINPROC(hwnd, msg);
}

void MApp_ZUI_EpgTimerCountDown(void)
{
    if(MApp_ZUI_GetActiveOSD() != E_OSD_EPG)
    {
        MApp_ZUI_ACT_StartupOSD(E_OSD_EPG);
    }

    if(MApp_ZUI_API_IsSuccessor(HWND_EPG_COUNTDOWN_PANE, MApp_ZUI_API_GetFocus()))
        MApp_ZUI_API_InvalidateWindow(HWND_EPG_COUNTDOWN_MSG_TXT);
    else
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_EPG_SHOW_TIMER_COUNTDOWN);
}

void MApp_ZUI_UpdateEpgCountDownOsd(void)
{
    if(MApp_ZUI_GetActiveOSD() == E_OSD_EPG)
    {
      if(MApp_ZUI_API_IsSuccessor(HWND_EPG_COUNTDOWN_PANE, MApp_ZUI_API_GetFocus()))
      {
         MApp_ZUI_API_InvalidateWindow(HWND_EPG_COUNTDOWN_MSG_TXT);
      }
    }
}

#if ENABLE_DVB
BOOLEAN MApp_TV_ProcessEpgCountDownKey(U8 key)
{
    if (key == KEY_NULL)
        return TRUE;

    /*if(MApp_ZUI_API_GetFocus() != HWND_EPG_COUNTDOWN_BTN_YES &&
       MApp_ZUI_API_GetFocus() != HWND_EPG_COUNTDOWN_BTN_NO)*/
    if(MApp_ZUI_API_GetFocus() != HWND_EPG_COUNTDOWN_BUTTON_BAR)
       return FALSE;

    switch(key)
    {
        case KEY_LEFT:
            MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_TIMER_COUNTDOWN_BTN_YES);
            return TRUE;

        case KEY_RIGHT:
            MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_TIMER_COUNTDOWN_BTN_NO);
            return TRUE;

        /*case KEY_SELECT:
            MApp_ZUI_ACT_ExecuteEpgAction(EN_EXE_EPG_TIMER_COUNTDOWN_BTN);

            return TRUE;*/

        default:
            return FALSE;
    }
}
U8 MApp_ZUI_ACT_EPGGetDescInfoPageNum(void)
{
    return u16ExtStrLen/MAX_INFO_UNIT_LENGTH;
}
#endif
#if (ENABLE_EPG_MUX)
BOOLEAN MApp_IsBarkerEPG_Refresh(void)
{
    return msAPI_CM_GetEITUpdate();
}

void MApp_BarkerEPG_StartToCheck(void)
{
    U16 onid = 0xFFFF,tsid = 0xFFFF;
    EPG_RFIndex = INVALID_PHYSICAL_CHANNEL_NUMBER;
    printf("\r\n@@@@ <MApp_ZUI_ACT_EPGMenu_Barker_EPG_Enter = %d>",EPG_RFIndex);
    if (MApp_SI_GetEPGMUXInfo(&onid,&tsid))
    {
        s_bBarkerlinkageEnterFlag=TRUE;
        EPG_RFIndex = msAPI_CM_GetPhysicalChannelNumberByID(onid,tsid);
        if (EPG_RFIndex != INVALID_PHYSICAL_CHANNEL_NUMBER)
        {
            MS_TP_SETTING stTempTP;

            memset(&stTempTP, 0x00, sizeof(stTempTP)); // fix coverity 207495

            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
            enFrotEndLockStatus  = FRONTEND_LOCK;
            fEnableSignalMonitor = TRUE;

          #if ENABLE_DVBC
            if (IsDVBCInUse())
            {
                DTVPROGRAMID_M stDPI;
                memset(&stDPI, 0, sizeof(stDPI));
                if (msAPI_CM_GetIDTable(EPG_RFIndex,(BYTE *)&stDPI,E_DATA_ID_TABLE))
                {
                    //stTempTP.u32Symbol_rate = stDPI.u32SymbRate;
                    stTempTP.u32Symbol_rate = msAPI_CM_Get_IDTab_SymbolRate(&stDPI);

                    stTempTP.u8Modulation   = stDPI.QamMode;
                    stTempTP.u32Frequency   = stDPI.u32Frequency;
                    msAPI_Tuner_Tune2RfCh(&stTempTP);
                    printf("\r\n <stTempTP.u32Symbol_rate = %d>",stTempTP.u32Symbol_rate);
                    printf("\r\n <stTempTP.u8Modulation   = %d>",stTempTP.u8Modulation);
                    printf("\r\n <stTempTP.u32Frequency   = %d>",stTempTP.u32Frequency);
                }
            }
            else
          #endif
                if(msAPI_DFT_GetTSSetting(EPG_RFIndex, &stTempTP) == TRUE)
            {
                stTempTP.u8PLPID = 0;
                stTempTP.u8HpLp=0;
                msAPI_Tuner_Tune2RfCh(&stTempTP);
            }

            MApp_SI_SetEPGMuxMode(TRUE);
            // MApp_Epg_Init();//Don't clear the EPG data for Barker EPG. Aron 2011/06/09
        #if 0//ENABLE_EPG_SERVICE_PRIORITY && ENABLE_TSB_CANAL_DIGITAL_933xx
            if(uniSys_Is_Vendor_CanalDigital())
            {
                MApp_Epg_SrvPriorityHandler(msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));// for fixed EPG constant movement with Canal Digital's stream.
                printf("\n Set MApp_Epg_SrvPriorityHandler() ");
            }
        #endif
        }
    }

    if(EPG_ServiceType & EPG_ServiceType_Return)
    {
        EPG_ServiceType &= ~EPG_ServiceType_Return;
    }
    else
    {
        EPG_ServiceType = msAPI_CM_GetCurrentServiceType();
    }
    if(!s_bBarkerlinkageEnterFlag)
    {
        EPG_ServiceType |= EPG_ServiceType_WithoutBaker; // or 0x80 indicated without Barker
    }
    printf("\n Baker Enter EPG_ServiceType 0x%x, %d ", EPG_ServiceType, s_bBarkerlinkageEnterFlag);
}

void MApp_BarkerEPG_Exit(void)
{
    printf("\n MApp_ZUI_ACT_EPGMenu_Barker_EPG_Exit 0x%x, %d ", EPG_ServiceType, msAPI_CM_GetCurrentServiceType());
    if(EPG_ServiceType & EPG_ServiceType_WithoutBaker)
    {
        EPG_ServiceType &= 0x0F;
        if(EPG_ServiceType != msAPI_CM_GetCurrentServiceType())
        {
            msAPI_CM_SetCurrentServiceType((MEMBER_SERVICETYPE)EPG_ServiceType);
        }
    }

    EPG_ServiceType = 0;
    if (s_bBarkerlinkageEnterFlag==FALSE)
    return;

    s_bBarkerlinkageEnterFlag=FALSE;
    if(EPG_ServiceType != msAPI_CM_GetCurrentServiceType())
    {
        msAPI_CM_SetCurrentServiceType((MEMBER_SERVICETYPE)EPG_ServiceType);
    }

    if (EPG_RFIndex != INVALID_PHYSICAL_CHANNEL_NUMBER)
    {
        BOOLEAN bTmpVar = bStopMonitorBlock;
        enFrotEndLockStatus  = FRONTEND_UNLOCK;
        fEnableSignalMonitor = FALSE;
        MApp_SI_SetEPGMuxMode(FALSE);
        bStopMonitorBlock = TRUE;
        g_bReadyForExitBarkerEPG = TRUE;
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
        g_bReadyForExitBarkerEPG = FALSE;
        bStopMonitorBlock = bTmpVar;
        EPG_RFIndex = INVALID_PHYSICAL_CHANNEL_NUMBER;
        printf("\r\n <MApp_ZUI_ACT_EPGMenu_Barker_EPG_Exit = %d>",EPG_RFIndex);
    }
}

BOOLEAN MApp_IsBarkerEPG(void)
{
    return s_bBarkerlinkageEnterFlag;
}
#endif

#endif  //#if (ENABLE_DTV_EPG)
#undef MAPP_ZUI_ACTEPG_C
