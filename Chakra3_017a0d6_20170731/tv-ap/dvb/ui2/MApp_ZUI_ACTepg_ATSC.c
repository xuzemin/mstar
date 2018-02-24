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

#define MAPP_ZUI_ACTEPG_ATSC_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"

#include "string.h"
#include "Utl.h"
#include "msAPI_Timer.h"
#include "MApp_UiEpg.h"

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
#include "MApp_ZUI_CTLdynatext.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_UiEpg.h"            // from CK3 code base
//#include "MApp_UiMenuEpg_ATSC.h" // from CK2 code base
#include "MApp_EpgDB_ATSC.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Psip.h"
#include "MApp_Audio.h"
#include "MApp_ChannelChange.h"
#include "MApp_ChannelProc_ATSC.h"
//#include "MApp_UiMenu.h"
#include "MApp_UiMenuStr_ATSC.h"
#include "MApp_VChip.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_UiMenuFunc_ATSC.h"
#include "apiGOP.h"
#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#include "MApp_TTS_Cus_Say.h"
#endif

//======================================= For Chakra3 + ATSC modify==================================
#define Mapp_GetDayOfWeek MApp_GetDayOfWeek
//#define MApp_UlongToString MApp_UlongToU8String
#define stDate _stDate

//#define ZUI_ENABLE_TRANSPARENCY_SYSSETTING FALSE
#define HWND_EPG_EVENT_INFO_PANEL  HWND_EPG_ATSC_EVENT_INFO_PANEL

#define E_GOP_SLV   0
#define HWND_EPG_EVENT_PANEL                     HWND_EPG_ATSC_EVENT_PANEL
#define HWND_EPG_PROG_TITLE_PANEL                HWND_EPG_ATSC_PROG_TITLE_PANEL
#define HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT       HWND_EPG_ATSC_EVENT_INFO_PANEL_ETT_TEXT
#define HWND_EPG_PROG_TITLE_TEXT                 HWND_EPG_ATSC_PROG_TITLE_TEXT
#define HWND_EPG_EVENT_INFO_PANEL_TIME_TEXT      HWND_EPG_ATSC_EVENT_INFO_PANEL_TIME_TEXT
#define HWND_EPG_ALL_HELP_PANEL_PREV_CH_NUM_TEXT HWND_EPG_ATSC_ALL_HELP_PANEL_PREV_CH_NUM_TEXT
#define HWND_EPG_ALL_HELP_PANEL_NEXT_CH_NUM_TEXT HWND_EPG_ATSC_ALL_HELP_PANEL_NEXT_CH_NUM_TEXT

//#define DEMOD_MODE_NTSC DEMOD_ATSC_MODE_NTSC
#define STRBUFF_LENGTH_ATSC  512 //256


//

//API layer

//////////////////////////////////////////////////////////////////////
// Feature Definitions
//#define EPG_FOR_HALF_HOUR           TRUE
//#define NEW_UI_FOR_TRUNK            FALSE//TRUE
//#define EPG_DRAW_EVENT_LR_ARROW     FALSE

//#define HALFHOUR_PER_PAGE           4
//#define SERVICE_PER_PAGE            6
//#define EPG_FULL_PORGRAM_DRAWN      0x3F
//#define INVALID_SEG_NUM             0xFF
//#define INVALID_INSERT_POSITION     0xFF
//#define EPGUI_UPDATE_PERIOD         500
//#define MAX_PAGE_EVENTS_IN_SERVICE  32
//#define MAX_INFO_STRING_LENGTH      1536    // Fixed the problem that buffer overflow in EPG Info

#define EVENT_PER_PAGE  8
#define    PROG_PER_PAGE                6

#include "msAPI_OSD.h"

/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/


/******************************************************************************/
/*                               Structure                                    */
/******************************************************************************/

#if(!ENABLE_ATSC_EPG_DB_2016)
typedef struct
{
    U8      u8TblIdx;
    U8      u8EventIdx;
} MS_EPG_EVENT_ITEM;

typedef struct
{
    U8                  u8ItemCtr;
    MS_EPG_EVENT_ITEM   astItem[MAX_EVENT_IN_TBL];
} MS_EPG_UI_POS;
#endif

typedef struct
{
    U32     u32Update;
    U32     u32System;
    U32     u32PageStart;
    U8      GPS_UTC_Offset;
    U32     u32EventStart;
    U32     u32EventEnd;
} MS_EPG_UI_TIME;

typedef struct
{
    U16     u16ProgNum;             // Start from 1

//#if (EPG_THIS_CH == TRUE)
    U8      u8ChabBufIdx;           // Index in astChannelBuf[]
//#else
//    U8      u8UiProgIdx;            // [0...PROG_PER_PAGE]
//    U8      u8DbProgIdx;            // [0...EPG_VCH_IN_DB]
//#endif
    U8      u8Table;
    U8      u8Event;
} MS_EPG_UI_FOCUS;

typedef struct
{
    U16     u16TotalProg;
    U16     u16IdleProgram;

    U16     u16EpgDbBufIdx;         // rang [0, 17]

    U8      u8HasDrawn;             // 0~5 for program, 6 for focus, 7 for ett
    U8      u8CurVirChIdx;

    U8      fIsTitleNoInfoHasDrawn :1;    // flag which is used to check if "No information" has drawn in title
    U8      fIsEttNoInfoHasDrawn   :1;    // flag which is used to check if "No information" has drawn in ett
    U8      fIsListHasDrawn :1;
    U8      fIsEventVChipInfoHasDrawn :1;
} MS_EPG_UI_PROG;

typedef struct
{
    U16     u16TotalNum;

    U8      u8OldFocusItem;
    U8      u8FocusItem;
//#if (EPG_THIS_CH != TRUE)
//    U8      u8UiHeadItemIdx;        // Ex: u8FocusItem [24, 29]    >> 24
//    U8      u8UiEndItemIdx;         // Ex: u8FocusItem [24, 29]    >> 29
//#endif
    U8      fIsSorted;
} MS_EPG_EVENT_POOL;

//typedef struct
//{
//    U8      ListEvtCnt;
//    U16     ListEvt[MAX_PAGE_EVENTS_IN_SERVICE];
//} MS_EPG_UI_SCHE_OSD;

//typedef struct
//{
//    U16 u16TotalService;
//    U8  u8TotalPage;
//    //ZUI: U8  u8HasDrawn;         // 0~6 for program
//} MS_EPG_UI_SERVICE;

typedef struct
{
    U8  reserved        : 2;
    U8  bScheNoInfo     : 1;
    U8  bScheEvent      : 1;
    U8  bNextNoInfo     : 1;
    U8  bNowNoInfo      : 1;
    U8  bNextEvent      : 1;
    U8  bNowEvent       : 1;
} MS_EPG_UI_DRAW_STATUS;

MS_EPG_LIST_DAY enEpgListDay = EPG_LIST_TODAY;

//extern EN_EPG_STATE enEpgState;
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
///////////////////////////////////////////////////////////////////////////////////
//static EN_EPGUI_INFO_STATE      enInfoState = STATE_EPGUI_INFO_INIT;
//static EN_RET                   enInfoRetVal;
// Clock related variables
static ST_TIME                  stClock;
//static ST_TIME                  stPrevClock;

// Time related variables
static MS_EPG_UI_TIME           stTime;

// program related variables
//static MS_EPG_UI_POS            astEpgPos[PROG_PER_PAGE];
static MS_EPG_UI_PROG           stProg;
static MS_EPG_UI_FOCUS          stFocus;
static MS_EPG_UI_FOCUS          stOldFocus;

static MS_EPG_EVENT_POOL        stEventPool;

#if( !ENABLE_ATSC_EPG_DB_2016 )
// Local Pointer and variables
static MS_EPG_VCH_BUF*          pDispVch;
static MS_EPG_VCH_BUF           stEpgUiVchBuf;
#endif

#if( ENABLE_ATSC_EPG_DB_2016 )
static MS_EPG_EVENT_New*        pstEvent;
#else
static MS_EPG_EVENT*            pstEvent;
#endif

#if ( !ENABLE_ATSC_EPG_DB_2016 )
static MS_EPG_EVENT             stNullEvent;
#endif


#if(!ENABLE_ATSC_EPG_DB_2016)
static MS_EPG_EVENT_ITEM        astEventItem[MAX_TBL_NUM*MAX_EVENT_IN_TBL];
#endif

//static U8 u8CurrentEITGet = 0;
static U8 u8EpgCurEventIndex = 0;  //current event index

#if(ENABLE_ATSC_EPG_DB_2016)
#define ATSC_UI_EVENT_LIST_NUM  100
static MS_EPG_EVENT_New* s_apstUiEventList[ATSC_UI_EVENT_LIST_NUM];
static U16 s_u16UiEventListNum = 0;
#endif


// Common string
static U8 const code au8NoInfo[]      = "No Information";
static U8 const code au8Receiving[]   = "No Information"; //"Receiving...";
//static U8 const code au8Dot[]       = "...";
static U8 const code szHelp[4][13]    = {"-2Hour", "+2Hour", "Info", "Single/Multi"};
static U8 const code au8Hide[]        = "Hide";
static U8 const code au8WeekDay[7][3] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
static U8 const code au8Month[12][3]  = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
static U8 const code au8WeekDay_Detail[7][10] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
static U8 const code au8Month_Detail[12][10] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

#if ENABLE_ATSC_TTS
static BOOLEAN s_EPG_bSayEtt = 0;
#endif

////////////////////////////////////////////////////////////////////////////////////////

#if(0)
static U8 u8IsEpgDataReadyForList = FALSE;
#endif

static BOOLEAN MApp_EpgZUI_IsEpgDataReadyForList(void)
{
#if( ENABLE_ATSC_EPG_DB_2016 )
    return (s_u16UiEventListNum > 0);
#else
    return ( (astEpgDbVchMask[0].fIsInSDRAM) || (astEpgDbVchMask[0].u8TblMask != 0) );
#endif
}


#if( !ENABLE_ATSC_EPG_DB_2016 )
static void MApp_EpgZUI_Sort_Tbl(U16 u16Vch, U8 u8Tbl, U8 u8NumOfEvent)
{
    //printf("MApp_EpgZUI_Sort_Tbl(u16Vch=%u, u8Tbl=%u, u8NumOfEvent=%u)\n", u16Vch, u8Tbl, u8NumOfEvent);

    U8  i, j;
    MS_U8 fFinishSort;
    U32 start_time_a, start_time_b;
    MS_EPG_EVENT    temp_event;


    if((u8NumOfEvent > 1) && (u8NumOfEvent <= MAX_EVENT_IN_TBL))
    {
        for(i=(u8NumOfEvent-1); i>0; i--)
        {
            fFinishSort = TRUE;

            for(j=0; j<i; j++)
            {
                // From small to large
                MApp_EpgDB_LoadEvent (u16Vch, u8Tbl, j, &g_stUiEvent);
                start_time_a = g_stUiEvent.start_time;

                MApp_EpgDB_LoadEvent (u16Vch, u8Tbl, j+1, &g_stUiEvent);
                start_time_b = g_stUiEvent.start_time;

                if(start_time_a > start_time_b)
                {
                    //printf ("Swap >> p[i] = %lX, p[j] = %lX\n", j, pEvent[j].start_time, j+1, pEvent[j+1].start_time);
                    MApp_EpgDB_LoadEvent(u16Vch, u8Tbl, j, &temp_event);        // j    -> temp
                    MApp_EpgDB_SaveEvent(u16Vch, u8Tbl, j, &g_stUiEvent);      // j+1  -> j
                    MApp_EpgDB_SaveEvent(u16Vch, u8Tbl, j+1, &temp_event);      // temp -> j+1
                    fFinishSort = FALSE;
                }
            }

            if(fFinishSort)
            {
                return;
            }
        }
    }
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
#define ONE_DAY_SECONDS 86400

#if (EPG_SORT_EVENT_FOR_ALL_EITTABLE)
static BOOLEAN MApp_EpgZUI_Sort_AllTbl(U16 u16Vch, U8 u8Tbl, U8 u8NumOfEvent, U8 u8PrevTableNumOfEvent)
{
    U8  u8i, u8j;
    MS_EPG_EVENT    stTempEvent;
    MS_EPG_EVENT    stTempEvent2;
    MS_EPG_EVENT    stCurrentTableEvent[MAX_EVENT_IN_TBL];
    memset(&stTempEvent, 0, sizeof(MS_EPG_EVENT));
    memset(&stTempEvent2, 0, sizeof(MS_EPG_EVENT));

    //printf("u8NumOfEvent = %d, u8PrevTableNumOfEvent = %d\n", u8NumOfEvent, u8PrevTableNumOfEvent);

    if(u8Tbl > 0)
    {
        if((u8PrevTableNumOfEvent >= 1) && (u8PrevTableNumOfEvent <= MAX_EVENT_IN_TBL))
        {
            MApp_EpgDB_LoadEvent (u16Vch, u8Tbl-1, u8PrevTableNumOfEvent-1, &stTempEvent);        // j    -> temp
            //printf("the EIT-%d event start time = 0x%x\n", u8Tbl-1, temp_event.start_time);
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
    //only need to compare first event of the table
    MApp_EpgDB_LoadEvent (u16Vch, u8Tbl, 0, &stTempEvent2);

    if(stTempEvent.start_time > stTempEvent2.start_time)
    {
        //printf("The EIT-%d event's time is earlier thant EIT-%d event's time\n", u8Tbl, u8Tbl-1);
        //swap the tbl save location
        if ((u8NumOfEvent >= 1) && (u8NumOfEvent <= MAX_EVENT_IN_TBL))
        {
            MS_EPG_EVENT    stEmptyEvent;
            memset(&stEmptyEvent, 0, sizeof(MS_EPG_EVENT));
            if(u8NumOfEvent > u8PrevTableNumOfEvent)
            {
                for(u8i=0; u8i< u8NumOfEvent; u8i++)
                {
                    MApp_EpgDB_LoadEvent(u16Vch, u8Tbl, u8i, &stCurrentTableEvent[u8i]);
                    if(u8i < u8PrevTableNumOfEvent)
                    {
                        MApp_EpgDB_LoadEvent(u16Vch, u8Tbl-1, u8i, &stTempEvent);
                        MApp_EpgDB_SaveEvent (u16Vch, u8Tbl, u8i, &stTempEvent);
                        MApp_EpgDB_SaveEvent (u16Vch, u8Tbl-1, u8i, &stCurrentTableEvent[u8i]);
                    }
                    else   //CurrentTable events > PreTable events --> save redundant current events into the end of pretable table address
                    {
                        MApp_EpgDB_SaveEvent (u16Vch, u8Tbl-1, u8i, &stCurrentTableEvent[u8i]);
                        MApp_EpgDB_SaveEvent (u16Vch, u8Tbl, u8i, &stEmptyEvent);

                    }
                }
            }
            else
            {
                for(u8j=0; u8j< u8PrevTableNumOfEvent; u8j++)
                {
                    MApp_EpgDB_LoadEvent(u16Vch, u8Tbl-1, u8j, &stTempEvent);
                    if(u8j < u8NumOfEvent)
                    {
                        MApp_EpgDB_LoadEvent(u16Vch, u8Tbl, u8j, &stCurrentTableEvent[j]);
                        MApp_EpgDB_SaveEvent (u16Vch, u8Tbl, u8j, &stTempEvent);
                        MApp_EpgDB_SaveEvent (u16Vch, u8Tbl-1, u8j, &stCurrentTableEvent[j]);
                    }
                    else   //PreTable events > CurrentTable events --> save redundant pretable events into the end of current table address
                    {
                        MApp_EpgDB_SaveEvent (u16Vch, u8Tbl, u8j, &stTempEvent);
                        MApp_EpgDB_SaveEvent (u16Vch, u8Tbl-1, u8j, &stEmptyEvent);
                    }
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}
#endif

#if( !ENABLE_ATSC_EPG_DB_2016 )
static void MApp_EpgZUI_Sort_This_Ch_Event(void)
{
    U8 u8TblIdx;
    U8 u8Event;
    U16 u16OldEventId;
    U8 u8OldTblIdx;
    U8 u8OldEvent;
    MS_EPG_EVENT stOldEvent;
#if (EPG_SORT_EVENT_FOR_ALL_EITTABLE)
    U8 u8PrevTableNumOfEvent =0;
#endif
    u16OldEventId = INVALID_EVENT_ID;
    u8OldTblIdx = INVALID_TBL_IDX;
    u8OldEvent = INVALID_EVENT_IDX;

    pstEvent = &g_stUiEvent;

    stTime.u32System = msAPI_Timer_GetSystemTime();

    stEventPool.u16TotalNum = 0;
    memset(&stNullEvent, 0x00, sizeof (stNullEvent));

#if (EPG_SORT_EVENT_FOR_ALL_EITTABLE)
    for(u8TblIdx = 0; u8TblIdx < MAX_TBL_NUM; u8TblIdx++)
    {
        //sort table i from old event to new event
        MApp_EpgZUI_Sort_Tbl(0, u8TblIdx, pDispVch->au8CntEvent_InTbl[u8TblIdx]);
        if(u8TblIdx > 0)
        {
            U8 u8TblIdxtemp = u8TblIdx;
            U8 u8PrevTableNumOfEvent_temp = u8PrevTableNumOfEvent;
            while(u8TblIdxtemp >0)
            {
                //sort
                if(MApp_EpgZUI_Sort_AllTbl(0, u8TblIdxtemp, pDispVch->au8CntEvent_InTbl[u8TblIdxtemp], u8PrevTableNumOfEvent_temp))
                {
                    u8TblIdxtemp--;
                    if(u8TblIdxtemp>0)
                        u8PrevTableNumOfEvent_temp = pDispVch->au8CntEvent_InTbl[u8TblIdxtemp-1];
                }
                else
                    break;
            }
        }
        u8PrevTableNumOfEvent = pDispVch->au8CntEvent_InTbl[u8TblIdx];
    }
#endif

    for(u8TblIdx = 0; u8TblIdx < MAX_TBL_NUM; u8TblIdx++)
    {
        // Sort sections in table
#if (!EPG_SORT_EVENT_FOR_ALL_EITTABLE)
        MApp_EpgZUI_Sort_Tbl(0, u8TblIdx, pDispVch->au8CntEvent_InTbl[u8TblIdx]);
#endif

        for(u8Event = 0; u8Event < pDispVch->au8CntEvent_InTbl[u8TblIdx]; u8Event++)
        {
            MApp_EpgDB_LoadEvent(0, u8TblIdx, u8Event, pstEvent);

            if(pstEvent->event_id == u16OldEventId)
            {
                MApp_EpgDB_LoadEvent(0, u8OldTblIdx, u8OldEvent, &stOldEvent);
                u8OldTblIdx        = u8TblIdx;
                u8OldEvent      = u8Event;
                u16OldEventId   = pstEvent->event_id;

                if(memcmp(&stOldEvent, pstEvent, 9)==0)
                {   // the same event.......
                    continue;
                }
            }
            else
            {
                u16OldEventId = pstEvent->event_id;
                u8OldTblIdx = u8TblIdx;
                u8OldEvent = u8Event;
            }

            // Put this checking mechanism after saving u16OldEventId, u8OldTblIdx and u8OldEvent
            if(memcmp(pstEvent, &stNullEvent, 9) == 0)
            {
                continue;
            }

            if(u8TblIdx == 0)
            {
                stTime.u32EventStart    = pstEvent->start_time - DEFAULT_SYSTEM_TIME - u8GpsUtcOffset;
                stTime.u32EventEnd      = stTime.u32EventStart + EPG_EVENT_LENGTH(pstEvent->length[0], pstEvent->length[1], pstEvent->length[2]);

                //printf("stTime.u32EventStart = 0x%x,  stTime.u32EventEnd  = 0x%x\n", stTime.u32EventStart,stTime.u32EventEnd);
                // Corresponding event >> Event end time > Page start time     AND    Event start < Page end time
            }

#if (EPG_DISCARD_EVENTS_BEFORE_YESTERDAY)
            if(stTime.u32EventEnd >= (stTime.u32System-ONE_DAY_SECONDS))
#else
            if(stTime.u32EventEnd >= (stTime.u32System))
#endif
            {
                //stEventPool.u8FocusItem = stEventPool.u8TotalNum;
                astEventItem[stEventPool.u16TotalNum].u8TblIdx   = u8TblIdx;
                astEventItem[stEventPool.u16TotalNum].u8EventIdx = u8Event;
                stEventPool.u16TotalNum++;
            }

        }
    }
    stEventPool.fIsSorted = TRUE;
    //stProg.fIsListHasDrawn = FALSE;
    //stProg.fIsEventVChipInfoHasDrawn = FALSE;
    //stProg.u8HasDrawn = 0;
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////

static void MApp_EpgZUI_Init_Local_Variables (void)
{
    // Time related variables
    stTime.u32Update         = msAPI_Timer_GetTime0();
    stTime.u32System         = msAPI_Timer_GetSystemTime();
    stTime.u32PageStart      = (stTime.u32System/SECONDS_PER_HOUR)*SECONDS_PER_HOUR;
    stTime.GPS_UTC_Offset    = u8GpsUtcOffset;


    // program related variables
//    memset(astEpgPos,       0x00, sizeof(astEpgPos));
    memset(&stProg,         0x00, sizeof(stProg));
    memset(&stFocus,        0x00, sizeof(stFocus));
    memset(&stOldFocus,     0x00, sizeof(stOldFocus));
    memset(&stEventPool,    0x00, sizeof(stEventPool));

   // u8CurrentEITGet = 0;

    // Local Pointer
#if( !ENABLE_ATSC_EPG_DB_2016 )
    pDispVch                = &stEpgUiVchBuf;
#endif
    pstEvent                = NULL;


#if(ENABLE_ATSC_EPG_DB_2016)
    PRINT_CURRENT_LINE();
    printf("Init event list\n");
    memset(&s_apstUiEventList, 0x00, sizeof(s_apstUiEventList));
    s_u16UiEventListNum = 0;
#endif

}

////////////////////////////////////////////////////////////////////////////////////////
static void MApp_EpgZUI_Set_ProgNum(U16 u16Prog)
{
    memcpy(&stOldFocus, &stFocus, sizeof(MS_EPG_UI_FOCUS));

    // Set program number, minimum program number and page start index in DB
    MApp_ChanProc_SetMainListProgIndex(u16Prog);
    stFocus.u16ProgNum          = u16Prog;
    stFocus.u8ChabBufIdx        = MApp_ChanProc_GetCurIdxMap2ChanBufIdx(u16Prog);
    stProg.u16TotalProg         = MApp_ChanProc_GetNumOfServices(MAIN_LIST);
}

///////////////////////////////////////////////////////////////////////////////////////
static void MApp_EpgZUI_Process_This_Ch_Event(void)
{
#if(ENABLE_ATSC_EPG_DB_2016)
    PRINT_CURRENT_LINE();

    U32 u32EventStartTime = msAPI_Timer_GetSystemTime();
    U32 u32EventEndTime = u32EventStartTime + (60*60*24);
    printf("u32EventStartTime=%u, u32EventEndTime=%u\n", u32EventStartTime, u32EventEndTime);

    printf("u32EventStartTime=");
    msAPI_AtscEpgDb_PrintTime(u32EventStartTime);
    printf("\n");
    printf("u32EventEndTime=");
    msAPI_AtscEpgDb_PrintTime(u32EventEndTime);
    printf("\n");


    stTime.u32System = u32EventStartTime;

    MS_VIRTUAL_CHANNEL* pstVirCh = MApp_ChanProc_GetCurChannelPointer();

    // Get events from DB to UI-List
    msAPI_AtscEpgDb_Set_DebugMode(1);

    s_u16UiEventListNum = msAPI_AtscEpgDb_Get_EventList_Ref(pstVirCh->u8RfNum, pstVirCh->u16SourceId,
        u32EventStartTime, u32EventEndTime, s_apstUiEventList, ATSC_UI_EVENT_LIST_NUM );

    msAPI_AtscEpgDb_Set_DebugMode(0);

    printf("s_u16UiEventListNum=%u\n", s_u16UiEventListNum);

    // ==> stEventPool.u8TotalNum
    stEventPool.u16TotalNum = s_u16UiEventListNum;
    printf("stEventPool.u8TotalNum=%u\n", stEventPool.u16TotalNum);

#else

//    printf(" MApp_EpgUI_Draw_This_Ch_Event : stProg.u8HasDrawn = 0x%x \r\n",stProg.u8HasDrawn);

    //if (stProg.u8HasDrawn != 0xFF)
   //{
        // Data ready in SDRAM or in xData
//        if ((astEpgDbVchMask[0].fIsInSDRAM)
//    #if (EPG_PARTIAL_DB == TRUE)
//        || (astEpgDbVchMask[0].u8TblMask != 0)
//    #endif
//        )
        {
            pDispVch   = &astEpgDbVchBuf[0];

            if ((!stEventPool.fIsSorted))
            {
                MApp_EpgZUI_Sort_This_Ch_Event();
            }
#if 0

            if (stEventPool.u8TotalNum != 0)
            {
                //MApp_EpgUI_Draw_Focus_All(&astEventItem[stEventPool.u8FocusItem]);
            }
            else
            {

                if (!stProg.fIsTitleNoInfoHasDrawn)
                {

                    au8EpgUiBuf[0] = (U8)sizeof(au8NoInfo);
                    memcpy(&au8EpgUiBuf[1], au8NoInfo, sizeof(au8NoInfo));
                    MApp_UiThisEpg_Draw_Event_Title();

                    stProg.fIsTitleNoInfoHasDrawn = TRUE;
                }

            }
#endif
        }
#if 0
         else if (stEpgDBInfo.u8EitIsReceiving != 0)
         {
            if (!stProg.fIsTitleNoInfoHasDrawn)
            {

                au8EpgUiBuf[0] = (U8)sizeof(au8Receiving);
                memcpy(&au8EpgUiBuf[1], au8Receiving, sizeof(au8Receiving));
                MApp_UiThisEpg_Draw_Event_Title();

                stProg.fIsTitleNoInfoHasDrawn = TRUE;
            }
        }
       else
        {

            if (!stProg.fIsTitleNoInfoHasDrawn)
            {

                au8EpgUiBuf[0] = (U8)sizeof(au8NoInfo);
                memcpy(&au8EpgUiBuf[1], au8NoInfo, sizeof(au8NoInfo));
                MApp_UiThisEpg_Draw_Event_Title();

               stProg.fIsTitleNoInfoHasDrawn = TRUE;

            }
#endif
//        }
  //  }

#endif
}

////////////////////////////////////////////////////////////////////////////////////////
static void MApp_EpgZUI_Init(void)
{
#if(ENABLE_ATSC_EPG_DB_2016)
    PRINT_CURRENT_LINE();
    msAPI_AtscEpgDb_PrintEvents(100);
#endif

    MApp_EpgZUI_Init_Local_Variables();

    //stEpgDBInfo.fIsSingleVchMode = FALSE;
    stProg.u16IdleProgram       = MApp_ChanProc_GetCurProgIndex();

    //printf(" EPG_BLOCK_EVENT_LIST_ITEM_WIDTH = %d EPG_WIDTH =%d \r\n",(int)EPG_BLOCK_EVENT_LIST_ITEM_WIDTH,(int)EPG_WIDTH);

    MApp_EpgZUI_Set_ProgNum(MApp_ChanProc_GetCurProgIndex());
    MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);

    //stProg.u8HasDrawn = 0x3F;
    //stProg.fIsTitleNoInfoHasDrawn   = FALSE;
    //stProg.fIsEttNoInfoHasDrawn     = FALSE;
    if (IsDTVInUse())
    {
        MApp_EpgZUI_Process_This_Ch_Event();
    }
}

////////////////////////////////////////////////////////////////////////////////////////
#if(!ENABLE_ATSC_EPG_DB_2016)
static void MApp_EpgZUI_QueryEPGDB_Reset_Status(void)
{
    if (MApp_EpgDB_GetResetStatus())
    {
        if (IsDTVInUse())
        {
            MApp_EpgDB_SetResetStatus(FALSE);
            stEventPool.fIsSorted = FALSE;
            MApp_EpgZUI_Process_This_Ch_Event();
        }
    }
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////
static void MApp_EpgZUI_GenEventTime_String(U8 u8Index)
{
    printf("MApp_EpgZUI_GenEventTime_String(idx=%u)\n", u8Index);

    U8 u8DayinWeek=0,u8Day,u8Month,i;

#if(ENABLE_ATSC_EPG_DB_2016)
    const MS_EPG_EVENT_New* pstCurEvent = s_apstUiEventList[u8Index];

    // Calculate event start time and end time
    stTime.u32EventStart    = pstCurEvent->start_time - DEFAULT_SYSTEM_TIME - stTime.GPS_UTC_Offset;
    stTime.u32EventEnd      = stTime.u32EventStart + pstCurEvent->u32TimeLen;

#else
    MS_EPG_EVENT_ITEM* pFocusEvent = &astEventItem[u8Index];

    MApp_EpgZUI_QueryEPGDB_Reset_Status();

    MApp_EpgDB_LoadEvent(0, pFocusEvent->u8TblIdx, pFocusEvent->u8EventIdx, &g_stUiEvent);

    pstEvent = &g_stUiEvent;

    // Calculate event start time and end time
    stTime.u32EventStart    = pstEvent->start_time - DEFAULT_SYSTEM_TIME - stTime.GPS_UTC_Offset;
    stTime.u32EventEnd      = stTime.u32EventStart + EPG_EVENT_LENGTH(pstEvent->length[0], pstEvent->length[1], pstEvent->length[2]);

#endif


    MApp_ConvertLocalTime2Date((S32) (stTime.u32EventStart + stGenSetting.g_Time.s32Offset_Time), &stClock);

    // Draw time and short description of focus event
    memset(pu8EpgString, 0x00, 28);

    // Store the Start time day info
    u8DayinWeek = Mapp_GetDayOfWeek(stClock.u16Year,stClock.u8Month,stClock.u8Day);
    u8Month = stClock.u8Month;
    u8Day = stClock.u8Day;
    //Start Time
    if (stClock.u8Hour == 0)
        MApp_UlongToString(12, &pu8EpgString[0], 2);
    else if(stClock.u8Hour<12)
        MApp_UlongToString(stClock.u8Hour, &pu8EpgString[0], 2);
    else if (stClock.u8Hour==12)
        MApp_UlongToString(12, &pu8EpgString[0], 2);
    else // > 12
        MApp_UlongToString((stClock.u8Hour-12), &pu8EpgString[0], 2);

    pu8EpgString[2] = ':';
    MApp_UlongToString(stClock.u8Min, &pu8EpgString[3], 2);

    if (stClock.u8Hour>=12)
    {
        pu8EpgString[5] = 'P';
        pu8EpgString[6] = 'M';
    }
    else
    {
        pu8EpgString[5] = 'A';
        pu8EpgString[6] = 'M';
    }

//    pu8EpgString[7] = ' ';
    pu8EpgString[7] = '-';
//    pu8EpgString[9] = ' ';

    MApp_ConvertLocalTime2Date((S32) (stTime.u32EventEnd + stGenSetting.g_Time.s32Offset_Time), &stClock);
    //End time
    if (stClock.u8Hour== 0)
        MApp_UlongToString(12, &pu8EpgString[8], 2);
    else if (stClock.u8Hour < 12)
        MApp_UlongToString(stClock.u8Hour, &pu8EpgString[8], 2);
    else if (stClock.u8Hour == 12)
        MApp_UlongToString(12, &pu8EpgString[8], 2);
    else // > 12
        MApp_UlongToString(stClock.u8Hour - 12, &pu8EpgString[8], 2);

    pu8EpgString[10] = ':';
    MApp_UlongToString(stClock.u8Min, &pu8EpgString[11], 2);

    if (stClock.u8Hour>=12)
    {
        pu8EpgString[13] = 'P';
        pu8EpgString[14] = 'M';
    }
    else
    {
        pu8EpgString[13] = 'A';
        pu8EpgString[14] = 'M';
    }

    //Day in week
    pu8EpgString[15] = ' ';

    i = strlen((char *)(au8WeekDay_Detail[u8DayinWeek]));
    strcpy((char *)(&pu8EpgString[16]), (char *)(au8WeekDay_Detail[u8DayinWeek]));

    i = i+16;

    pu8EpgString[i++]=',';

    //Day
    MApp_UlongToString(u8Day, &pu8EpgString[i], 2);
    i = i+2;
    pu8EpgString[i++] = '-';

    //Month
    if (stDate.u8Month<10)
    {
        MApp_UlongToString( stDate.u8Month, &pu8EpgString[i], 1 );
        i = i+1;
    }
    else
    {
        MApp_UlongToString( stDate.u8Month, &pu8EpgString[i], 2 );
        i = i+2;
    }
    /*
    j = strlen((char *)(au8Month_Detail[stDate.u8Month-1]));
    strcpy((char *)(&pu8EpgString[i]), (char *)(au8Month_Detail[stDate.u8Month-1]));
    i = i + j;
    */

    pu8EpgString[i++] = '-';

    MApp_UlongToString( ( U32 ) stDate.u16Year, &pu8EpgString[i], 4 );
    i +=4;
    pu8EpgString[i++] = '\0';

/*

    pu8EpgString[18] = au8WeekDay[u8DayinWeek][0];
    pu8EpgString[19] = au8WeekDay[u8DayinWeek][1];
    pu8EpgString[20] = au8WeekDay[u8DayinWeek][2];
    pu8EpgString[21] = ',';
    //Day
    MApp_UlongToString(u8Day, &pu8EpgString[22], 2);
    pu8EpgString[24] = '-';
    pu8EpgString[25] = au8Month[u8Month-1][0];
    pu8EpgString[26] = au8Month[u8Month-1][1];
    pu8EpgString[27] = au8Month[u8Month-1][2];
    pu8EpgString[28] = '\0';

*/
}

#if 0
//////////////////////////////////////////////////////////////////////////////////
static void MApp_EPG_ZUI_GenEventVChipInfo_String(U8 u8Index)
{
    MS_EPG_RATING *pstCurEvn;
    MS_EPG_EVENT    *pTempEvent;
    U8 u8MPAALevel=0,/* TV_FVSLD=0,*/ CanEngLevel=0,CanFreLevel=0;
    U32 u32StartTime, u32EndTime, u32SystemTime;
    extern U32 g_u32StreamTime;

    MS_EPG_EVENT_ITEM* pFocusEvent = &astEventItem[u8Index];

    MApp_EpgDB_LoadEvent(0, pFocusEvent->u8TblIdx, pFocusEvent->u8EventIdx, &g_stUiEvent);
    pTempEvent = &g_stUiEvent;
    pstCurEvn = &pTempEvent->stRating;
    memset(pu8EpgString, 0x00, sizeof(pu8EpgString));

// For current event

    if (g_u32StreamTime)
        u32SystemTime = g_u32StreamTime;
    else
        u32SystemTime   = msAPI_Timer_GetSystemTime();

    u32StartTime    = pTempEvent->start_time - DEFAULT_SYSTEM_TIME - u8GpsUtcOffset;
    u32EndTime  = u32StartTime + EPG_EVENT_LENGTH(pTempEvent->length[0], pTempEvent->length[1], pTempEvent->length[2]);

    if ( (u32StartTime <= u32SystemTime) && (u32EndTime > u32SystemTime) )
    {
        strcpy((char *)pu8EpgString, (char *)RatingInfoText());
        return;
    }

// For non-current event
    if (pstCurEvn->fRatingRxIsOK)
    {
        // For TV-Rating
        switch (pstCurEvn->u8TVRatingForEntire)
        {
            case 0:
                if (pstCurEvn->u8TVRatingForChild == 1)
                    UTL_strcat((char *)pu8EpgString,"TV-Y");
                else if (pstCurEvn->u8TVRatingForChild == 2)
                {
                    UTL_strcat((char *)pu8EpgString,"TV-Y7");;
                    if (pstCurEvn->fFantasyViolence == 1)
                    {
                        UTL_strcat((char *)pu8EpgString,"-FV");
                    }
                }
                break;
            case 1:
                UTL_strcat((char *)pu8EpgString,"TV-NONE");
                break;
            case 2:
                UTL_strcat((char *)pu8EpgString,"TV-G");
                break;
            case 3:
                UTL_strcat((char *)pu8EpgString,"TV-PG");
                break;
            case 4:
                UTL_strcat((char *)pu8EpgString,"TV-14");
                break;
            case 5:
                UTL_strcat((char *)pu8EpgString,"TV-MA");
                break;
        }


        //TV_Rating_FVSLD

        if (pstCurEvn->u8TVRatingForEntire == 3
            || pstCurEvn->u8TVRatingForEntire == 4)
        {
            // Sexually Suggestive Diaog is only for TV-PG and TV-14
            if (pstCurEvn->fDialog == 1)
            {
                UTL_strcat((char *)pu8EpgString,"-D");
            }
        }

        // LSV is only for TV-PG, TV-14 and TV-MA
        if (pstCurEvn->u8TVRatingForEntire == 3
            || pstCurEvn->u8TVRatingForEntire == 4
            || pstCurEvn->u8TVRatingForEntire == 5)
        {
            if (pstCurEvn->fLanguage == 1)
            {
                UTL_strcat((char *)pu8EpgString,"-L");
            }
            if (pstCurEvn->fSexualContent == 1)
            {
                UTL_strcat((char *)pu8EpgString,"-S");
            }
            if (pstCurEvn->fViolence == 1)
            {
                UTL_strcat((char *)pu8EpgString,"-V");
            }
        }


        //For MPAA_Rating
        if (pstCurEvn->u8MPAAFlag)
        {
            u8MPAALevel = pstCurEvn->u8MPAARatingD2-1;
            switch (u8MPAALevel)
            {
                case VCHIP_MPAARATING_G:
                    UTL_strcat((char *)pu8EpgString," MPAA-G");
                    break;
                case VCHIP_MPAARATING_PG:
                    UTL_strcat((char *)pu8EpgString," MPAA-PG");
                    break;
                case VCHIP_MPAARATING_PG_13:
                    UTL_strcat((char *)pu8EpgString," MPAA-PG13");
                    break;
                case VCHIP_MPAARATING_R:
                    UTL_strcat((char *)pu8EpgString," MPAA-R");
                    break;
                case VCHIP_MPAARATING_NC_17:
                    UTL_strcat((char *)pu8EpgString," MPAA-NC17");
                    break;
                case VCHIP_MPAARATING_X:
                    UTL_strcat((char *)pu8EpgString," MPAA-X");
                break;
            }
        }
        //For Canada English Rating
        if (pstCurEvn->u8CaEngFlag)
        {
            CanEngLevel = pstCurEvn->u8CaEngRatingD0;
            switch(CanEngLevel)
            {
                case VCHIP_ENGRATING_C:
                    UTL_strcat((char *)pu8EpgString," CAN-ENG-C");
                    break;
                case VCHIP_ENGRATING_C8Plus:
                    UTL_strcat((char *)pu8EpgString," CAN-ENG-C8+");
                    break;
                case VCHIP_ENGRATING_G:
                    UTL_strcat((char *)pu8EpgString," CAN-ENG-G");
                    break;
                case VCHIP_ENGRATING_PG:
                    UTL_strcat((char *)pu8EpgString," CAN-ENG-PG");
                    break;
                case VCHIP_ENGRATING_14Plus:
                    UTL_strcat((char *)pu8EpgString," CAN-ENG-14+");
                    break;
                case VCHIP_ENGRATING_18Plus:
                    UTL_strcat((char *)pu8EpgString," CAN-ENG-18+");
                    break;
            }
        }
        //For Canada French Rating
        if (pstCurEvn->u8CaFreFlag)
        {
            CanFreLevel = pstCurEvn->u8CaFreRatingD1;
            switch(CanFreLevel)
            {
                case VCHIP_FRERATING_G:
                    UTL_strcat((char *)pu8EpgString," CAN-FRE-G");
                    break;
                case VCHIP_FRERATING_8ansPlus:
                    UTL_strcat((char *)pu8EpgString," CAN-FRE-8ans+");
                    break;
                case VCHIP_FRERATING_13ansPlus:
                    UTL_strcat((char *)pu8EpgString," CAN-FRE-13ans+");
                    break;
                case VCHIP_FRERATING_16ansPlus:
                    UTL_strcat((char *)pu8EpgString," CAN-FRE-16ans+");
                    break;
                case VCHIP_FRERATING_18ansPlus:
                    UTL_strcat((char *)pu8EpgString," CAN-FRE-18ans+");
                    break;
            }
        }

        if (strlen((char *)pu8EpgString) > 0)
        {
            UTL_strcat((char *)pu8EpgString, " / ");
        }

        // Get RRT string
        if ((sizeof(pu8EpgString) - strlen((char *)pu8EpgString)) > 20)
        {
            MApp_UiMenuStr_GetRRT5String(pstCurEvn, pu8EpgString + strlen((char *)pu8EpgString), 20);
        }
        else
        {
            MApp_UiMenuStr_GetRRT5String(pstCurEvn, pu8EpgString + strlen((char *)pu8EpgString), (U8)(256 - strlen((char *)pu8EpgString)));
        }
        //stProg.fIsEventVChipInfoHasDrawn = TRUE;
    }

}
#endif

///////////////////////////////////////////////////////////////////////////////////
#if ( ENABLE_ATSC_EPG_DB_2016 )
void MApp_EpgZUI_Get_EventTitle(U8 u8Index, BOOLEAN* pbStrFormatIsUtf16)
{
    //printf("MApp_EpgZUI_Get_EventTitle(idx=%u)\n", u8Index);

    if( u8Index >= s_u16UiEventListNum )
    {
        printf("\nError: EventList idx=%u is wrong!\n", u8Index);
        return;
    }

    au8EpgUiBuf[0] = 0;
    au8EpgUiBuf[1] = 0;

    const MS_EPG_EVENT_New* pstCurEvent = s_apstUiEventList[u8Index];

    // Get title: put title into au8EpgUiBuf
    msAPI_AtscEpgDb_Get_EventTitle(pstCurEvent, au8EpgUiBuf, ATSC_EPG_TITLE_DATA_SIZE);

    *pbStrFormatIsUtf16 = pstCurEvent->fIsEitUTF16;
}

const MS_EPG_EVENT_New* MApp_EpgZUI_Get_Event_Ref(U8 u8Index)
{
    if( u8Index >= s_u16UiEventListNum )
    {
        //return NULL;
        return 0;
    }
    return s_apstUiEventList[u8Index];
}
#endif

void MApp_EpgZUI_Get_Event(U8 u8Index)
{
    au8EpgUiBuf[0] = 0;
    au8EpgUiBuf[1] = 0;

#if( ENABLE_ATSC_EPG_DB_2016 )

    //printf("MApp_EpgZUI_Get_Event(idx=%u)\n", u8Index);

    if( u8Index >= s_u16UiEventListNum )
    {
        printf("\nError: EventList idx=%u is wrong!\n", u8Index);
        return;
    }

    const MS_EPG_EVENT_New* pstCurEvent = s_apstUiEventList[u8Index];

    // Get time info...
    stTime.u32EventStart = pstCurEvent->start_time - DEFAULT_SYSTEM_TIME - stTime.GPS_UTC_Offset;

    // Get title: put title into au8EpgUiBuf
    //msAPI_AtscEpgDb_Get_EventTitle(pstCurEvent, au8EpgUiBuf, ATSC_EPG_TITLE_DATA_SIZE);

#else


    MS_EPG_EVENT_ITEM* pFocusEvent = &astEventItem[u8Index];
    MS_EPG_EVENT_TITILE pSrcEventTitle;

    MApp_EpgZUI_QueryEPGDB_Reset_Status();

    MApp_EpgDB_LoadEvent(0, pFocusEvent->u8TblIdx, pFocusEvent->u8EventIdx, &g_stUiEvent);

    pstEvent = &g_stUiEvent;


    pSrcEventTitle.pu8Title_content = au8EpgUiBuf;
    U16 u16TitleMaxLen = sizeof(au8EpgUiBuf) - 2;

    if( u16TitleMaxLen > EPG_EITTITLE_MAX_STR_LEN )
    {
        u16TitleMaxLen = EPG_EITTITLE_MAX_STR_LEN;
    }

    MApp_EpgDB_LoadEventTitle(0, pstEvent->u16DbTitlePos, &pSrcEventTitle, u16TitleMaxLen );

    //printf("pSrcEventTitle.u16Title_length=%u\n", pSrcEventTitle.u16Title_length);

    if( pSrcEventTitle.u16Title_length < (sizeof(au8EpgUiBuf) - 2) )
    {
        au8EpgUiBuf[ pSrcEventTitle.u16Title_length ] = '\0';
        au8EpgUiBuf[ pSrcEventTitle.u16Title_length+1 ] = '\0';
    }

    stTime.u32EventStart = pstEvent->start_time - DEFAULT_SYSTEM_TIME - stTime.GPS_UTC_Offset;

#endif

    MApp_ConvertLocalTime2Date((S32) (stTime.u32EventStart + stGenSetting.g_Time.s32Offset_Time), &stClock);
    MApp_ConvertLocalTime2Date((S32) (stTime.u32System + stGenSetting.g_Time.s32Offset_Time), &stDate);

    if(stClock.u8Day == stDate.u8Day)
        enEpgListDay = EPG_LIST_TODAY;
    else
    {
        enEpgListDay = stTime.u32System > stTime.u32EventStart ? EPG_LIST_YESTERDAY : EPG_LIST_TOMORROW;
    }

    if (stClock.u8Hour == 0)
        MApp_UlongToString( ( U32 ) (12), &pu8EpgString[0], 2 );
    else if (stClock.u8Hour < 12)
        MApp_UlongToString( ( U32 ) stClock.u8Hour, &pu8EpgString[0], 2 );
    else if (stClock.u8Hour == 12)
        MApp_UlongToString( ( U32 )12, &pu8EpgString[0], 2 );
    else // > 12
        MApp_UlongToString( ( U32 ) (stClock.u8Hour-12), &pu8EpgString[0], 2 );

    pu8EpgString[2] = ':';
    MApp_UlongToString(stClock.u8Min, &pu8EpgString[3], 2);

    pu8EpgString[5] = ' ';
    pu8EpgString[6] = stClock.u8Hour>=12 ? 'P' : 'A';
    pu8EpgString[7] = 'M';
    pu8EpgString[8] = 0x00;

    //pDispSrv = EPG_UI_SRV_BUF_ADR;
}

//**********************************************************************************

#if SUPPORT_LONG_ETT
LPTSTR MApp_EpgZUI_GetExtendText(
  #if ( ENABLE_ATSC_EPG_DB_2016 )
    const MS_EPG_EVENT_New *pEventNew
  #else
    MS_EPG_EVENT *pEvent
  #endif
)
{
    U8 i;
    U16 u16ETT_length;
    BOOL fIsEttUTF16;
    U8 *puString;


#if ( ENABLE_ATSC_EPG_DB_2016 )
    MS_EPG_EVENT_ETT_New stEventETT;

    if( FALSE == msAPI_AtscEpgDb_Get_Ett( pEventNew->u16DbEttIdx , &stEventETT ) )
    {
        return NULL;
    }

    u16ETT_length = stEventETT.u16EttDataLen;
    fIsEttUTF16 = stEventETT.bIsEttUTF16;
    puString = stEventETT.au8EttData;

#else

    /*if( !MApp_EpgZUI_IsEpgDataReadyForList() )
    {
        return NULL;
    } */

    U16 u16DbEttPos;
    MS_EPG_EVENT_ETT pSrcEventETT;

    if(pEvent)
    {
        if(!((stEpgDBInfo.u8EttRxOK == MAX_TBL_MASK) || (pEvent->u16DbEttPos != NULL)))
            return NULL;

        u16DbEttPos = pEvent->u16DbEttPos;
        fIsEttUTF16 = pEvent->fIsEttUTF16;
    }
    else
    {
        if(!g_bIsFastEtt )
            return NULL;

       // g_bChInfoIsFastEtt = TRUE;

        u16DbEttPos = 0;
        fIsEttUTF16 = g_bFastEttUTF16;
    }

    puString = pu8EpgString;
    pSrcEventETT.pu8ETT_content = pu8EpgString;

    MApp_EpgDB_LoadEventETT(0, u16DbEttPos, &pSrcEventETT, sizeof(pu8EpgString) );
    //g_u16ChInfoDbEttPos = u16DbEttPos;

    u16ETT_length = pSrcEventETT.u16ETT_length;

    if( u16ETT_length > (sizeof(pu8EpgString)-2) )
    {
        u16ETT_length = (sizeof(pu8EpgString)-2);
    }

#endif

    if( fIsEttUTF16 )
    {
        if(puString[0] == '\0')
        {
            if(u16ETT_length <=2)
                return NULL;
            if(puString[1] == '\0')
            {
                return NULL;
            }
        }
    }
    else
    {
        if(puString[0] == '\0')
        {
            return NULL;
        }
    }

    puString[u16ETT_length] = 0;
    puString[u16ETT_length+1] = 0;

    //u16ETT_length = MIN(u16ETT_length, EPG_LONG_ETT_MAX_STR_LEN-1);

    LPTSTR buf = (LPTSTR)(void*)&au8Section[0];

    if(fIsEttUTF16)
    {
        MApp_ZUI_API_StringBufferUTF16toU16(buf, puString, u16ETT_length);
    }
    else
    {
          MApp_ZUI_API_StringBuffU8toU16(buf, puString, u16ETT_length);
    }
    for(i=0;i<u16ETT_length;i++)
    {
        if(*buf == 0x20)
            buf++;
        else
            break;
    }

    if(i+g_u16LineAddrs[g_u8EpgEttPos] >= u16ETT_length)
        return NULL;

    if(g_u8EpgEttRows)
        buf += g_u16LineAddrs[g_u8EpgEttPos];

    return buf;
}
#else
static U8* MApp_EpgZUI_Get_Extend_Text_Table(U8 u8Index)
{
    MS_EPG_EVENT_ITEM* pFocusEvent = &astEventItem[u8Index];
    MS_EPG_EVENT_ETT pSrcEventETT;
    U8 *puString = au8EpgUiBuf;

    MApp_EpgZUI_QueryEPGDB_Reset_Status();

    MApp_EpgDB_LoadEvent(0, pFocusEvent->u8TblIdx, pFocusEvent->u8EventIdx, &g_stUiEvent);

    pstEvent = &g_stUiEvent;

    if ((stEpgDBInfo.u8EttRxOK == MAX_TBL_MASK) || (pstEvent->u16DbEttPos != NULL) )
    {
        pSrcEventETT.pu8ETT_content = au8EpgUiBuf;
        MApp_EpgDB_LoadEventETT(0, pstEvent->u16DbEttPos, &pSrcEventETT, sizeof(au8EpgUiBuf));
        //au8EpgUiBuf[pSrcEventETT.u16ETT_length] = '\0';
        //au8EpgUiBuf[pSrcEventETT.u16ETT_length+1] = '\0';
        if(g_u8EpgEttRows > ZUI_ETT_LINE)
            puString += g_u16LineAddrs[g_u8EpgEttPos]; // for scroll ETT use
    }
    else
    {
        au8EpgUiBuf[0] = '\0';
    }
    return puString;
}
#endif
//****************************************************************************************
static void MApp_EpgZUI_Exit(void)
{
#if( !ENABLE_ATSC_EPG_DB_2016 )
    pDispVch = NULL;
#endif

    stProg.u16IdleProgram = stFocus.u16ProgNum;
    MApp_ChanProc_SetMainListProgIndex(stProg.u16IdleProgram);
    MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);

#if 0//ENABLE_ATSC_TTS
    s_EPG_bSayEtt = FALSE;
#endif
}

//////////////////////////////////////////////////////////////////////////////////
static const HWND _ZUI_TBLSEG _EventHwndList[EVENT_PER_PAGE]=
{
    HWND_EPG_EVENT_PANEL_EVENT1,
    HWND_EPG_EVENT_PANEL_EVENT2,
    HWND_EPG_EVENT_PANEL_EVENT3,
    HWND_EPG_EVENT_PANEL_EVENT4,
    HWND_EPG_EVENT_PANEL_EVENT5,
    HWND_EPG_EVENT_PANEL_EVENT6,
    HWND_EPG_EVENT_PANEL_EVENT7,
    HWND_EPG_EVENT_PANEL_EVENT8,
};

static U8 _MApp_ZUI_ACT_EpgEventWindowMapToIndex(HWND hwnd)
{
    U8 u8PageBaseIndex = u8EpgCurEventIndex - (u8EpgCurEventIndex%MAX_NUM_OF_EPGLIST_ITEM);

    U8 i;
    for (i = 0; i < EVENT_PER_PAGE; i++)
    {
        if (hwnd == _EventHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_EventHwndList[i], hwnd))
        {
            return i + u8PageBaseIndex;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_EpgEventIndexMapToWindow(U8 u8Index)
{
    return _EventHwndList[u8Index%MAX_NUM_OF_EPGLIST_ITEM];
}

/////////////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_ACT_AppShowEpg_ATSC(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_EPG;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,ZUI_EPG_XSTART, ZUI_EPG_YSTART,ZUI_EPG_WIDTH, ZUI_EPG_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    /*#if !ENABLE_EPG_TRANSPARENT
    MApi_GOP_GWIN_SwitchGOP(E_GOP_SLV);
    MApi_GOP_GWIN_SetBlending(u8SlaveOSDWinId,TRUE,(DEFAULT_TRANSPARENCY*7)/100);
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    MApi_GOP_GWIN_SetBlending(MApp_ZUI_API_QueryGWinID(),TRUE,(TRANSPARENCY_0_PERCENTAGE_VALUE*7)/100);
    #endif*/

    //note: set the first invalid rect equal to gwin size
    MApp_ZUI_API_InvalidateRect(&rect);
    for (wnd = 1; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }
    MApp_EpgZUI_Init();
#if 0
    if(ZUI_ENABLE_TRANSPARENCY_SYSSETTING)
    {
        SetOsdPageBlendingValue(FALSE, (stGenSetting.g_SysSetting.Transparency*7)/100);
        MApi_GOP_GWIN_SwitchGOP(E_GOP_SLV);
        MApi_GOP_GWIN_SetBlending(u8SlaveOSDWinId,FALSE,(stGenSetting.g_SysSetting.Transparency*7)/100);
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
        MApi_GOP_GWIN_SetBlending(MApp_ZUI_API_QueryGWinID(),FALSE,(stGenSetting.g_SysSetting.Transparency*7)/100);
    }
#endif
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_EPG_EVENT_INFO_PANEL, SW_HIDE);
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
    MApp_ZUI_CTL_DynamicListRefreshContent(HWND_EPG_EVENT_PANEL);
}

/////////////////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_ACT_TerminateEpg_ATSC(void)
{
    //stGenSetting.g_SysSetting.Transparency = loc_PreTransparency;

    printf("[]MApp_ZUI_ACT_TerminateEpg_ATSC\n");
    u8EpgCurEventIndex = 0;
    MApp_EpgZUI_Exit();
#if ENABLE_ATSC_TTS
        MApp_TTSControlSetOn(FALSE);
#endif
    //enEpgState = STATE_EPG_CLEAN_UP;
}

////////////////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_HandleEpgKey_ATSC(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state
    //reset timer if any key
    //MApp_ZUI_API_ResetTimer(HWND_EPG_ALL_BGND_PANEL, 0);

#if 0
    //button click animation...
    {
        static const MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _key2btn[] =
        {
            {VK_UP, HWND_EPG_HELP_BTN_UP},
            {VK_DOWN, HWND_EPG_HELP_BTN_DOWN},
            {VK_LEFT, HWND_EPG_HELP_BTN_LEFT},
            {VK_RIGHT, HWND_EPG_HELP_BTN_RIGHT},
            {VK_SELECT, HWND_EPG_HELP_BTN_OK},
            {VK_YELLOW, HWND_EPG_HELP_BTN_DATE},
            {VK_INFO, HWND_EPG_HELP_BTN_INFO},
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
#endif

    U8 SkipAtvFlag = TRUE;

    switch(key)
    {
        case VK_EPG:
        case VK_EXIT:
        case VK_MENU:
        case VK_CHANNEL_RETURN:
            if(VK_EXIT == key)
            {
        #if ENABLE_ATSC_TTS
                MApp_TTS_Cus_Say_exit();
        #endif
            }
            MApp_ZUI_ACT_ExecuteEpgAction_ATSC(EN_EXE_CLOSE_CURRENT_OSD);
        #if 0//ENABLE_ATSC_TTS
            s_EPG_bSayEtt = FALSE;
        #endif
            return TRUE;
        case VK_POWER:
            MApp_ZUI_ACT_ExecuteEpgAction_ATSC(EN_EXE_POWEROFF);
            return TRUE;
        case VK_INFO:
        case VK_GREEN:
            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PROG_TITLE_PANEL )
                return TRUE;
            if( MApp_ZUI_API_IsWindowVisible(HWND_EPG_EVENT_INFO_PANEL) )
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_EVENT_INFO_PANEL, SW_HIDE);
        #if 0//ENABLE_ATSC_TTS
                s_EPG_bSayEtt = FALSE;
        #endif
            }
            else
            {
            #if (ENABLE_ATSC_TTS)
                if( MApp_TTS_Cus_Get_UserSetting_TTSOn() )
                {
                    s_EPG_bSayEtt = TRUE;
                }
            #endif

                g_u8EpgEttPos = 0;
                g_u8EpgEttRows = MApp_ZUI_API_GetPuncStringLineAddrs(HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT, MApp_ZUI_ACT_GetEpgDynamicText_ATSC(HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT), 10);
                //printf("g_u8EpgEttRows=%u\n", g_u8EpgEttRows);

                MApp_ZUI_API_ShowWindow(HWND_EPG_EVENT_INFO_PANEL, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_UP, SW_HIDE);

                if(g_u8EpgEttRows > ZUI_ETT_LINE)
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_DOWN, SW_SHOW);
                else
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_DOWN, SW_HIDE);

            }
            return TRUE;
        case VK_YELLOW:
            if( MApp_ZUI_API_IsWindowVisible(HWND_EPG_EVENT_INFO_PANEL) )
            {
                if(g_u8EpgEttRows - g_u8EpgEttPos > ZUI_ETT_LINE)
                {
                    g_u8EpgEttPos += ZUI_ETT_LINE;
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_UP, SW_SHOW);
                }
                if(g_u8EpgEttRows - g_u8EpgEttPos < ZUI_ETT_LINE)
                {
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_DOWN, SW_HIDE);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT);

            }
            return TRUE;
        case VK_BLUE:
            if( MApp_ZUI_API_IsWindowVisible(HWND_EPG_EVENT_INFO_PANEL) )
            {
                if(g_u8EpgEttPos)
                {
                    g_u8EpgEttPos -= ZUI_ETT_LINE;
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_DOWN, SW_SHOW);
                }
                if(g_u8EpgEttPos == 0 )
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_UP, SW_HIDE);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT);
            }
            return TRUE;
        case VK_LEFT:
        case VK_RIGHT:
            if( MApp_ZUI_API_GetFocus() != HWND_EPG_PROG_TITLE_PANEL )
            {
                return TRUE;
            }
            break;
        case VK_CHANNEL_PLUS:
        case VK_CHANNEL_MINUS:
            {
            #if 0// (NEW_VIRTUAL_CHANNEL_STRUCTURE == ENABLE)
                MS_RF_CHANNEL_new pRf_Ch;
            #endif
                MApp_ZUI_ACT_ExecuteEpgAction_ATSC(EN_EXE_CLOSE_CURRENT_OSD);

                u8EpgCurEventIndex=0;

                MApp_ZUI_API_ShowWindow(HWND_EPG_EVENT_INFO_PANEL, SW_HIDE);

                MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);

                if((key == VK_CHANNEL_PLUS) || (key == VK_RIGHT))
                    MApp_ChanProc_IncProgIndex(MAIN_LIST, 1, TRUE);
                else
                    MApp_ChanProc_DecProgIndex(MAIN_LIST, 1, TRUE);



                while( SkipAtvFlag )
                {
                    MS_VIRTUAL_CHANNEL *ptemp = NULL;
                    ptemp  = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(MApp_ChanProc_GetCurProgIndex()));
            #if 0//(NEW_VIRTUAL_CHANNEL_STRUCTURE == ENABLE)
                    MApp_ChanProc_GetRfChannelPointer(ptemp, &pRf_Ch);
                    if( pRf_Ch.stTPSetting.fModulation == DEMOD_MODE_NTSC )
            #else
                    //if( ptemp->stTPSetting.fModulation == DEMOD_MODE_NTSC )
                    if( MApp_ChanProc_Is_ChannelAtv(ptemp) )
            #endif
                    {
                        if((key == VK_CHANNEL_PLUS) || (key == VK_RIGHT))
                            MApp_ChanProc_IncProgIndex(MAIN_LIST, 1, TRUE);
                        else
                            MApp_ChanProc_DecProgIndex(MAIN_LIST, 1, TRUE);
                    }
                    else
                    {
                        SkipAtvFlag = FALSE;
                    }
                }
                MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
                MApp_EpgZUI_Set_ProgNum(MApp_ChanProc_GetCurProgIndex());

            #if(!ENABLE_ATSC_EPG_DB_2016)
                astEpgDbVchMask[0].fIsInSDRAM = FALSE;
                #if (EPG_PARTIAL_DB == TRUE)
                    astEpgDbVchMask[0].u8TblMask = 0;
                #endif
            #endif

                //u8CurrentEITGet = 0;
                //stEventPool.u8FocusItem = 0;
                //stEventPool.u8OldFocusItem= 0;
                stEventPool.fIsSorted = FALSE;
                stEventPool.u16TotalNum = 0;
                //stProg.fIsTitleNoInfoHasDrawn   = FALSE;
                //stProg.fIsEttNoInfoHasDrawn     = FALSE;
                //stProg.fIsEventVChipInfoHasDrawn= FALSE;
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                return TRUE;
            }
            break;

        case VK_VOLUME_PLUS:
#if (ATSC_READY)
            MApp_UiMenuFunc_AudioVolumeConfig(TRUE);
#endif
            return TRUE;

        case VK_VOLUME_MINUS:
#if (ATSC_READY)
            MApp_UiMenuFunc_AudioVolumeConfig(FALSE);
#endif
            return TRUE;

        case VK_PAGE_UP:
            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PROG_TITLE_PANEL )
                return TRUE;
            if (stEventPool.u16TotalNum==0 || u8EpgCurEventIndex == 0)
                return TRUE;

            if ((u8EpgCurEventIndex < EVENT_PER_PAGE))
                u8EpgCurEventIndex = 0;
            else
                u8EpgCurEventIndex -= EVENT_PER_PAGE;

            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_EPG_EVENT_PANEL);
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgEventIndexMapToWindow(u8EpgCurEventIndex));
            return TRUE;
        case VK_PAGE_DOWN:
            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PROG_TITLE_PANEL )
                return TRUE;
            if (stEventPool.u16TotalNum==0 || u8EpgCurEventIndex == stEventPool.u16TotalNum-1)
                return TRUE;

            if ( (u8EpgCurEventIndex + EVENT_PER_PAGE) >= (stEventPool.u16TotalNum-1))
                u8EpgCurEventIndex = stEventPool.u16TotalNum-1;
            else
                u8EpgCurEventIndex += EVENT_PER_PAGE;

            MApp_ZUI_CTL_DynamicListRefreshContent(HWND_EPG_EVENT_PANEL);
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgEventIndexMapToWindow(u8EpgCurEventIndex));
            return TRUE;
        default:
            //
            break;
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_ExecuteEpgAction_ATSC(U16 act)
{
#if 0//(ENABLE_ATSC_EPG_DB_2016)
    PRINT_CURRENT_LINE();
    printf("MApp_ZUI_ACT_ExecuteEpgAction_ATSC(act=%d)\n", act);
#endif

//printf("Funs=%s, line=%d, act=%d\n",__FUNCTION__,__LINE__,act);
     switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            enEpgState = STATE_EPG_CLEAN_UP;
            MApp_ZUI_API_EmptyMessageQueue();
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            enEpgState = STATE_EPG_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_EPG_SHOW_FOCUS_INFO:
            if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_EVENT_INFO_PANEL) )
            {
                g_u8EpgEttPos = 0;
                g_u8EpgEttRows = MApp_ZUI_API_GetPuncStringLineAddrs(HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT, MApp_ZUI_ACT_GetEpgDynamicText_ATSC(HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT), 10);
                MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_UP, SW_HIDE);

                if(g_u8EpgEttRows>ZUI_ETT_LINE)
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_DOWN, SW_SHOW);
                else
                    MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_DOWN, SW_HIDE);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PROG_TITLE_PANEL);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_EVENT_INFO_PANEL);
            return FALSE;

        case EN_EXE_EPG_SHOW_PREV_INFO:
            if (stEventPool.u16TotalNum==0)
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_EVENT_INFO_PANEL, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_EPG_EVENT_PANEL_EVENT1);
                break;
            }

            if (u8EpgCurEventIndex == 0)
            {
                MApp_ZUI_API_ShowWindow(HWND_EPG_EVENT_INFO_PANEL, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_EPG_EVENT_PANEL_EVENT1);
                break;
            }
            else
            {
                  u8EpgCurEventIndex--;

            }

            if ((u8EpgCurEventIndex >= stEventPool.u16TotalNum-1) ||
                _MApp_ZUI_ACT_EpgEventIndexMapToWindow(u8EpgCurEventIndex) == HWND_EPG_EVENT_PANEL_EVENT8)
            {
                //change page case
                MApp_ZUI_CTL_DynamicListRefreshContent(HWND_EPG_EVENT_PANEL);
                MApp_ZUI_API_ShowWindow(_MApp_ZUI_ACT_EpgEventIndexMapToWindow(u8EpgCurEventIndex), SW_SHOW);    //prevent focus invalid
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgEventIndexMapToWindow(u8EpgCurEventIndex));
            }
            break;

        case EN_EXE_EPG_SHOW_NEXT_INFO:
            if (stEventPool.u16TotalNum==0)
                break;

            if (u8EpgCurEventIndex >= (stEventPool.u16TotalNum-1))
            {
                MApp_ZUI_CTL_DynamicListRefreshContent(HWND_EPG_EVENT_PANEL);
                MApp_ZUI_API_ShowWindow(HWND_EPG_EVENT_INFO_PANEL, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_EPG_EVENT_PANEL_EVENT1);
                u8EpgCurEventIndex = 0;
                break;
            }
            else
            {
                u8EpgCurEventIndex++;
            }

            if (_MApp_ZUI_ACT_EpgEventIndexMapToWindow(u8EpgCurEventIndex) == HWND_EPG_EVENT_PANEL_EVENT1)
            {
                //change page case
                MApp_ZUI_CTL_DynamicListRefreshContent(HWND_EPG_EVENT_PANEL);
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_EpgEventIndexMapToWindow(u8EpgCurEventIndex));
            }
            break;

        case EN_EXE_EPG_SHOW_INFO_ATSC:
            if (IsDTVInUse())
            {
                stEventPool.fIsSorted = FALSE;
                MApp_EpgZUI_Process_This_Ch_Event();
            }

            if( MApp_ZUI_API_GetFocus() == HWND_EPG_PROG_TITLE_PANEL )
            {
                //Use SendMessage to avoid MSG_NOTIFY_CONTENT_CHANGED set forcus error
                MApp_ZUI_API_SendMessage(HWND_EPG_EVENT_PANEL, MSG_NOTIFY_CONTENT_CHANGED, 0);
                MApp_ZUI_API_SetFocus(HWND_EPG_PROG_TITLE_PANEL);
            }
            else
                MApp_ZUI_CTL_DynamicListRefreshContent(HWND_EPG_EVENT_PANEL);

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_PROG_TITLE_PANEL);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EPG_EVENT_INFO_PANEL);
            return TRUE;

#if ENABLE_ATSC_EPG_UI
		case EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_EVENT_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
			MApp_ZUI_API_ShowWindow(HWND_EPG_PRO_GUIDE_PANEL, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_HELP_PANEL, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_ALL_INFO_PANEL, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_REMINDER_PANEL, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_SCHEDULE_LIST_PANEL, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_PANEL, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_REC_TIME_STEEING_PANEL, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_RECORDER_SCHEDULE_LIST_PANEL,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_COUNTDOWN_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EPG_PVR_WARNING_DLG_PANE_1, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_EPG_ATSC_EVENT_INFO_PANEL, SW_HIDE);

            //MApp_EpgUI_Func_Get_Program_InPage(stFocus.u16Service,TRUE);
			return TRUE;
#endif

        default:
            //
            break;
    }

    return FALSE;
}

//****************************************************************************************************************
//static void MApp_ZUI_ACT_EPG_String_Processing(HWND hwnd,U8* SrcStr,U16* DstStr, MS_EPG_EVENT* TempEvent)
static void MApp_ZUI_ACT_EPG_String_Processing(HWND hwnd,U8* SrcStr,U16* DstStr, BOOLEAN bSrcStrIsUTF16 )
{
    U16 i,length;

    //printf("MApp_ZUI_ACT_EPG_String_Processing(hwnd=%u, Utf16=%u)\n", hwnd, bSrcStrIsUTF16);

/*
    if( TempEvent == NULL )
    {
        return;
    }
*/

    switch(hwnd)
    {
        case HWND_EPG_EVENT_PANEL_EVENT1_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT2_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT3_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT4_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT5_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT6_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT7_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT8_TEXT:
        case HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT:

            /*if( TempEvent->fIsEitUTF16
              ||((hwnd == HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT) && TempEvent->fIsEttUTF16)
              )*/
            if( bSrcStrIsUTF16 )
            {
#if 0
                printf(">>>");
                for(i=0;i<20;i+=2)
                printf(" (%d,%d)",SrcStr[i],SrcStr[i+1]);
                printf("<<< \n\n");

                printf("hwnd is %d",hwnd);
                printf(">>>");
                for(i=0;i<20;i+=2)
                printf(" (%c,%c)",SrcStr[i],SrcStr[i+1]);
                printf("<<< \n\n");

                printf("\n");

#endif
                //The length is equal CHAR_BUFFER length
                length = STRBUFF_LENGTH_ATSC/sizeof(U16);
                for(i=0; i<length; i++)
                {
            #if ENABLE_LANGUAGE_KOREA
                    // Ray, 03302012
                    if( SrcStr[2*i] =='\0' && SrcStr[2*i+1] =='\0')
                        break;

            #else
                    if( SrcStr[2*i+1] =='\0' )
                        break;
            #endif
                    DstStr[i] = ((U16)SrcStr[2*i] << 8 | (U16)SrcStr[2*i+1]);
                }
                DstStr[i] ='\0';

            }
            else
            {
                  MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, SrcStr, strlen((char *)SrcStr));

        #if 0//ENABLE_ATSC_TTS
                if ((hwnd == HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT) && (s_EPG_bSayEtt == FALSE))
                {
                    MApp_TTSControlSetInputText(CHAR_BUFFER, strlen((char *)SrcStr));
                    MApp_TTSControlSetOn(TRUE);
                    s_EPG_bSayEtt = TRUE;
                }
        #endif
            }

        break;

//other windows
        default:
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, SrcStr, strlen((char *)SrcStr));
            break;
    }
}

#if 0
////////////////////////////////////////////////////////////////////////////////////
#define ENABLE_EPG_CC_INFO     ENABLE  //show CC information on EPG

static void _MApp_ZUI_ACT_SetEPGCCstatus(HWND hwnd)
{
#if ENABLE_EPG_CC_INFO
    U8 u8IsEpgDataReady=((astEpgDbVchMask[0].fIsInSDRAM) || (astEpgDbVchMask[0].u8TblMask != 0));
    if(IsDTVInUse() && (stEventPool.u8TotalNum > 0) && u8IsEpgDataReady )
    {
        if(pstEvent->fHasCCInfo)
            MApp_ZUI_API_ShowWindow(hwnd,SW_SHOW);
        else
            MApp_ZUI_API_ShowWindow(hwnd,SW_HIDE);
    }
    else
    {
        if(MApp_ZUI_API_IsWindowVisible(hwnd))
            MApp_ZUI_API_ShowWindow(hwnd,SW_HIDE);
    }
#else
    MApp_ZUI_API_ShowWindow(hwnd,SW_HIDE);
#endif
}
#endif

U8 MApp_ZUI_ACT_Epg_HWndMappingToEventIdx(HWND hwnd)
{
    U8 u8EventIndex = 0;

    switch(hwnd)
    {
        default:
        case HWND_EPG_EVENT_PANEL_EVENT1_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT1_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT1_TIME_TEXT:
            u8EventIndex = 0;
            break;

        case HWND_EPG_EVENT_PANEL_EVENT2_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT2_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT2_TIME_TEXT:
            u8EventIndex = 1;
            break;

        case HWND_EPG_EVENT_PANEL_EVENT3_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT3_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT3_TIME_TEXT:
            u8EventIndex = 2;
            break;

        case HWND_EPG_EVENT_PANEL_EVENT4_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT4_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT4_TIME_TEXT:
            u8EventIndex = 3;
            break;

        case HWND_EPG_EVENT_PANEL_EVENT5_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT5_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT5_TIME_TEXT:
            u8EventIndex = 4;
            break;

        case HWND_EPG_EVENT_PANEL_EVENT6_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT6_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT6_TIME_TEXT:
            u8EventIndex = 5;
            break;

        case HWND_EPG_EVENT_PANEL_EVENT7_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT7_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT7_TIME_TEXT:
            u8EventIndex = 6;
            break;

        case HWND_EPG_EVENT_PANEL_EVENT8_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT8_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT8_TIME_TEXT:
            u8EventIndex = 7;
            break;

    }

    return u8EventIndex;
}

LPTSTR MApp_ZUI_ACT_GetEpgDynamicText_ATSC(HWND hwnd)
{
    //printf(">>>>>>>>> MApp_ZUI_ACT_GetEpgDynamicText_ATSC(hwnd=%d)\n", hwnd);

    U16 u16TempID = Empty;
    U8 *u8TempString = (U8 *)"";

    // Mapping UI to event idx
    U8 u8EventIndex = MApp_ZUI_ACT_Epg_HWndMappingToEventIdx(hwnd);

    U8 u8IsEpgDataReady = MApp_EpgZUI_IsEpgDataReadyForList();

    U8 u8PageBaseIndex = u8EpgCurEventIndex - (u8EpgCurEventIndex%MAX_NUM_OF_EPGLIST_ITEM);

    BOOLEAN bFormatIsUTF16 = FALSE;


    if( IsAtscInUse()
#if(ENABLE_ATSC)
     || IsATVInUse()
#endif
        )
    {
        if( stEventPool.u16TotalNum == 0 )
        {
            u8IsEpgDataReady = FALSE;
        }
    }
    else
    {
        u8IsEpgDataReady = FALSE;
    }



    switch(hwnd)
    {
        case HWND_EPG_PROG_TITLE_TEXT:
            u8TempString = CurEPGProgramInfoText();
          #if ENABLE_ATSC_TTS
            MApp_TTS_Cus_AddUniString(MApp_ZUI_API_StringBuffU8toU16(u16StringBuffer, u8TempString, strlen((char *)u8TempString)));
            MApp_TTSControlSetOn(TRUE);
          #endif
            break;

        case HWND_EPG_EVENT_INFO_PANEL_TIME_TEXT:

            if( /*IsDTVInUse() && (stEventPool.u8TotalNum > 0) &&*/ u8IsEpgDataReady )
            {
                u8EventIndex = _MApp_ZUI_ACT_EpgEventWindowMapToIndex(MApp_ZUI_API_GetFocus());
                MApp_EpgZUI_GenEventTime_String(u8EventIndex);
                u8TempString = ThisEpg_EventTimeText();
            }
            else
                u16TempID = en_str_No_Title;

            break;

#if 0
        case HWND_EPG_EVENT_INFO_PANEL_TV_RATING_VALUE_TEXT:

             if(IsDTVInUse() && (stEventPool.u8TotalNum > 0) && u8IsEpgDataReady )
                {
                    u8EventIndex = _MApp_ZUI_ACT_EpgEventWindowMapToIndex(MApp_ZUI_API_GetFocus());
                    MApp_EPG_ZUI_GenEventVChipInfo_String(u8EventIndex);
                    u8TempString = pu8EpgString;
                }
             else
                u8TempString = (U8 *)"N/A";
            break;
#endif


        case HWND_EPG_EVENT_PANEL_EVENT1_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT2_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT3_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT4_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT5_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT6_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT7_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT8_TEXT:

            //PRINT_CURRENT_LINE();
            if( u8IsEpgDataReady )
            {
            #if(ENABLE_ATSC_EPG_DB_2016)
                MApp_EpgZUI_Get_EventTitle(u8PageBaseIndex + u8EventIndex, &bFormatIsUTF16);
            #else
                MApp_EpgZUI_Get_Event(u8PageBaseIndex + u8EventIndex);
                bFormatIsUTF16 = pstEvent->fIsEitUTF16;
            #endif
                u8TempString = ThisEpg_EventTitleText();
            }
            else
            {
                u8TempString = (U8 *)"";
            }
            break;

        case HWND_EPG_EVENT_PANEL_EVENT1_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT2_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT3_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT4_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT5_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT6_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT7_DAY_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT8_DAY_TEXT:

            //PRINT_CURRENT_LINE();
            if( /*IsDTVInUse() && (stEventPool.u8TotalNum > 0) &&*/ u8IsEpgDataReady )
            {
                MApp_EpgZUI_Get_Event(u8PageBaseIndex + u8EventIndex);

                switch(enEpgListDay)
                {
                    case EPG_LIST_TODAY:
                        u16TempID = en_str_Today;
                        break;
                    case EPG_LIST_TOMORROW:
                        u16TempID = en_str_Tomorrow;
                        break;
                    case EPG_LIST_YESTERDAY:
                        u16TempID = en_str_Yesterday;
                        break;
                }
             }
            else
                 u16TempID = en_str_No_Title;
            break;

        case HWND_EPG_EVENT_PANEL_EVENT1_TIME_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT2_TIME_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT3_TIME_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT4_TIME_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT5_TIME_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT6_TIME_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT7_TIME_TEXT:
        case HWND_EPG_EVENT_PANEL_EVENT8_TIME_TEXT:

            //PRINT_CURRENT_LINE();
            if(/*IsDTVInUse() && (stEventPool.u8TotalNum > 0) &&*/ u8IsEpgDataReady )
            {
                MApp_EpgZUI_Get_Event(u8PageBaseIndex + u8EventIndex);
                u8TempString = ThisEpg_EventTimeText();
            }
            else
                u8TempString = (U8 *)"";

            break;

        case HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT:

            //printf("stEventPool.u8TotalNum=%u\n", stEventPool.u8TotalNum);
            //printf("u8IsEpgDataReady=%u\n", u8IsEpgDataReady);

            if( /*IsDTVInUse() && (stEventPool.u8TotalNum > 0) &&*/ u8IsEpgDataReady )
            {
                u8EventIndex = _MApp_ZUI_ACT_EpgEventWindowMapToIndex(MApp_ZUI_API_GetFocus());

                //printf("u8EventIndex=%u\n", u8EventIndex);

    #if SUPPORT_LONG_ETT
                LPTSTR strTttText = NULL;

            #if ( ENABLE_ATSC_EPG_DB_2016 )
                const MS_EPG_EVENT_New* pstEpgEvent = MApp_EpgZUI_Get_Event_Ref(u8EventIndex);
                strTttText = MApp_EpgZUI_GetExtendText(pstEpgEvent);
            #else
                MApp_EpgZUI_Get_Event(u8EventIndex);
                strTttText = MApp_EpgZUI_GetExtendText(&g_stUiEvent);
            #endif

                if(strTttText)
                {
                #if (ENABLE_ATSC_TTS)
                    if( s_EPG_bSayEtt )
                    {
                        MApp_TTS_Cus_AddUniString(strTttText);
                        MApp_TTSControlSetOn(TRUE);
                        s_EPG_bSayEtt = FALSE;
                    }
                #endif

                    return strTttText;
                }
                else
                {
                    u16TempID = en_str_No_Event_Information;

                #if (ENABLE_ATSC_TTS)
                    if( s_EPG_bSayEtt )
                    {
                        MApp_TTS_Cus_Add_Str_By_StrId(u16TempID);
                        MApp_TTSControlSetOn(TRUE);
                        s_EPG_bSayEtt = FALSE;
                    }
                #endif

                }
    #else
                u8TempString = MApp_EpgZUI_Get_Extend_Text_Table(u8EventIndex);

            #if ENABLE_LANGUAGE_KOREA
                // Ray, 04012012
                if((hwnd == HWND_EPG_EVENT_INFO_PANEL_ETT_TEXT) && pstEvent->fIsEttUTF16 )
                {
                    if((*u8TempString) == '\0')
                    {
                        if((*(u8TempString+1)) == '\0')
                            u16TempID = en_str_No_Event_Information;
                    }
                }
                else
                {
                    if((*u8TempString) == '\0')
                    u16TempID = en_str_No_Event_Information;
                }
            #else
                if((*u8TempString) == '\0')
                    u16TempID = en_str_No_Event_Information;
            #endif
    #endif

            #if(!ENABLE_ATSC_EPG_DB_2016)
                bFormatIsUTF16 = pstEvent->fIsEttUTF16;
            #endif

            }
            else
            {
                u16TempID = en_str_No_Title;
            }
            break;

        case HWND_EPG_ALL_HELP_PANEL_PREV_CH_NUM_TEXT:
            u8TempString = EPGPrevProgramNumberText();
            break;

        case HWND_EPG_ALL_HELP_PANEL_NEXT_CH_NUM_TEXT:
            u8TempString = EPGNextProgramNumberText();
            break;

        default:
            //
            break;

    }


#if 0
    if(hwnd == HWND_EPG_EVENT_PANEL_EVENT1_TEXT
    || hwnd == HWND_EPG_EVENT_PANEL_EVENT2_TEXT
    || hwnd == HWND_EPG_EVENT_PANEL_EVENT3_TEXT
    || hwnd == HWND_EPG_EVENT_PANEL_EVENT4_TEXT
    || hwnd == HWND_EPG_EVENT_PANEL_EVENT5_TEXT
    || hwnd == HWND_EPG_EVENT_PANEL_EVENT6_TEXT
    || hwnd == HWND_EPG_EVENT_PANEL_EVENT7_TEXT
    || hwnd == HWND_EPG_EVENT_PANEL_EVENT8_TEXT)
    {
        if(u16TempID == Empty)
        {
            if(g_stUiEvent.fIsEitUTF16)
            {
                U16 length = 0, i = 0, iRet = 0;
                char tmpNULL[] = "Null";
                length = strlen(tmpNULL);

                // Coverity 95840
                strcpy((char *)au8Section, (char *)u8TempString);

            	do
            	{
                	iRet = ((U16)au8Section[2*i] << 8 | (U16)au8Section[2*i+1]) - (U16)tmpNULL[i];
                	i++;
            	}while(i<length && iRet == 0);// compare util the end char of tmoNULL

            	if (iRet == 0)
            	{
                	u8TempString = (U8 *)"";
                    //u16TempID = en_str_No_Event_Information;
            	}
            }
            else if (strncmp((char *)(u8TempString), "Null", strlen((char *)(u8TempString))-1) == 0)
            {
                u8TempString = (U8 *)"";
                //u16TempID = en_str_No_Event_Information;
            }
        }
    }
#endif

    if( u16TempID != Empty )
    {
        //printf("END MApp_ZUI_ACT_GetEpgDynamicText_ATSC, u16TempID = %d\n", u16TempID);
        return MApp_ZUI_API_GetString(u16TempID);
    }
    else
    {
        //printf("END MApp_ZUI_ACT_GetEpgDynamicText_ATSC, u8TempString = %s\n", u8TempString);
        //MApp_ZUI_ACT_EPG_String_Processing(hwnd, u8TempString, CHAR_BUFFER, pstEvent);

        MApp_ZUI_ACT_EPG_String_Processing(hwnd, u8TempString, CHAR_BUFFER, bFormatIsUTF16);

        return CHAR_BUFFER;
    }
}

//////////////////////////////////////////////////////////////////////////////////
GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryEPGItemStatus(HWND hwnd)
{
    U8 u8PageBaseIndex;

    //printf("stEventPool.u8TotalNum = %ld\n",(U32)stEventPool.u16TotalNum);
    //printf("u8EventProcessCnt = %ld\n",(U32)u8EventProcessCnt);
    //printf("QueryEPGItemStatus(%u)\n", hwnd);


/*
    if( hwnd == HWND_EPG_EVENT_PANEL_EVENT1 )
    {
        u8IsEpgDataReadyForList = ((astEpgDbVchMask[0].fIsInSDRAM) || (astEpgDbVchMask[0].u8TblMask != 0));
        printf(" u8IsEpgDataReadyForList=%u\n", u8IsEpgDataReadyForList);
    }
*/

    if( IsATVInUse() )
    {
        u8EpgCurEventIndex = 0;

        if( hwnd == HWND_EPG_EVENT_PANEL_EVENT1 )
            return EN_DL_STATE_NORMAL;
        else
            return EN_DL_STATE_HIDDEN;
    }

//DTV in use
    u8PageBaseIndex = u8EpgCurEventIndex - (u8EpgCurEventIndex%MAX_NUM_OF_EPGLIST_ITEM);

    //if( stEventPool.u8TotalNum == 0 || u8IsEpgDataReadyForList == FALSE )
    if( 0 == MApp_EpgZUI_IsEpgDataReadyForList() )
    {
         if(hwnd == HWND_EPG_EVENT_PANEL_EVENT1)
            return EN_DL_STATE_NORMAL;
         else
            return EN_DL_STATE_HIDDEN;
    }
    else if( (stEventPool.u16TotalNum - u8PageBaseIndex) >=  8 )
    {
        return EN_DL_STATE_NORMAL;
    }


    switch(hwnd)
    {
        case HWND_EPG_EVENT_PANEL_EVENT1:
        case HWND_EPG_EVENT_PANEL_EVENT2:
        case HWND_EPG_EVENT_PANEL_EVENT3:
        case HWND_EPG_EVENT_PANEL_EVENT4:
        case HWND_EPG_EVENT_PANEL_EVENT5:
        case HWND_EPG_EVENT_PANEL_EVENT6:
        case HWND_EPG_EVENT_PANEL_EVENT7:
        case HWND_EPG_EVENT_PANEL_EVENT8:
            if (_MApp_ZUI_ACT_EpgEventWindowMapToIndex(hwnd) < stEventPool.u16TotalNum)
            {
                return EN_DL_STATE_NORMAL;
            }
            else
            {
                return EN_DL_STATE_HIDDEN;
            }
        default:
            //
            break;
    }

    return EN_DL_STATE_DISABLED;
}
//////////////////////////////////////////////////////////////////////////////////

#undef MAPP_ZUI_ACTEPG_ATSC_C
