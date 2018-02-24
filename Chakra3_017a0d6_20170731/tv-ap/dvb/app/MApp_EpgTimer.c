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

#define MAPP_EPG_TIMER_C

/******************************************************************************/
/*      Header Files                                                          */
/******************************************************************************/
// C Library
#include <string.h>

// Kernel Layer
#include "MsCommon.h"
#include "MsOS.h"
#include "msAPI_Ram.h"
#include "msAPI_Timer.h"
#include "msAPI_Power.h"
#include "GPIO.h"

#if (ENABLE_DTV_EPG)

#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiVDEC.h"

#include "MApp_GlobalSettingSt.h"

// AP Layer
#include "MApp_UiMenuDef.h" //ZUI: #include "MApp_UiMenu.h"
#include "MApp_EpgTimer.h"
#include "MApp_ChannelChange.h"
#include "mapp_demux.h"
#include "MApp_SaveData.h"
#include "MApp_Main.h"
#include "MApp_TV.h"
#include "MApp_InputSource.h"
#include "MApp_MVDMode.h"
#include "MApp_ChannelList.h" //ZUI:
#include "MApp_AnalogInputs.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif
#include "MApp_TopStateMachine.h"
#include "MApp_SaveData.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIstrings.h"
#include "mapp_si.h"
#include "mapp_si_util.h"
#include "MApp_PVR.h"
#include "MApp_UiPvr.h"
#include "MApp_Playback.h"
#include "ZUI_exefunc.h"
#include "MApp_ZUI_ACTepg.h"
#include "IOUtil.h"
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
#include "msAPI_DrvInit.h"
#include "MApp_Standby.h"
#endif
#if ENABLE_PVR
#include "MApp_UiPvr.h"
#if DTG_FREEVIEW_STANDBY
extern BOOLEAN MApp_FreeView_Is_Standby(void);
extern void MApp_FreeView_PowerOn(void);
#endif
#endif
#if ENABLE_DMP
#include "MApp_DMP_Main.h"

#endif
#include "MApp_APEngine.h"
#include "msAPI_APEngine.h"
#include "MApp_ZUI_ACTdmp.h"
#include "MApp_TimeShift.h"
#include "MApp_ZUI_ACTcimmi.h"

#if 0//ENABLE_CI_PLUS
#include "msAPI_Flash.h"
#endif

#if ENABLE_CI_PLUS
#include "MApp_CIMMI.h"
#endif

/******************************************************************************/
/*      Macro                                                                 */
/******************************************************************************/

// Debug configuration
#define EPGTIMER_ENABLE_ASSERT  FALSE

#if EPGTIMER_ENABLE_ASSERT
#define EPG_ASSERT(expr)    __ASSERT(expr)
#else
#define EPG_ASSERT(expr)
#endif

// Debug message
#define EPG_TIMER_DEBUG     1

#if (EPG_TIMER_DEBUG)
#define TIMER_DBG( s )  { {printf s;} }
#else
#define TIMER_DBG( s )
#endif

#define TIMER_OVERLAP_DEG(x)     //x
#define TIMER_OVERLAP_WEEKLY_DEG(x)     //x
#define TIMER_OVERLAP_DAILY_DEG(x)     //x

#define MANUAL_TIMER_MONITOR_INTERVAL   500

#define EPG_TIMER_USE_XDATA_WINDOW      FALSE

#define GetScheduleListBufAddr()        (_PA2VA(((SCHEDULE_LIST_MEMORY_TYPE & MIU1) ? (SCHEDULE_LIST_ADR | MIU_INTERVAL) : (SCHEDULE_LIST_ADR))))

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/
#if(ENABLE_PVR_BROWSER)
extern void MApp_UiPvr_Browser_UpdateRecordingAttr(void);
#endif
extern MEMBER_SERVICETYPE MApp_EpgUI_Func_Get_CurFocusSrvType(void);
extern U16 MApp_EpgUI_Func_Get_CurFocusSrvPos(void);
extern U16 MApp_EpgUI_Func_Get_CurFocusEvtIdx(void);
extern void MApp_ZUI_UpdateEpgCountDownOsd(void);
U16 _MApp_EpgTimer_GetCheckSum(void);

/******************************************************************************/
/*      Global Variables                                                      */
/******************************************************************************/
#define p_string_buffer ((LPTSTR)CHAR_BUFFER) //ZUI: extern U16* p_string_buffer;
extern U8 g_u8MenuMainItemIndex;
extern BOOLEAN g_flgFromEPGRecorder;
extern BOOLEAN g_flgFromEPGRecorderNoTitle;

/******************************************************************************/
/*      Local Variables                                                       */
/******************************************************************************/
// Timer related variables
static MS_EPG_TIMER * _pstEpgTimer;
//static U32          _u32PrevAddress;

static DWORD        m_dwEPGManualTimerMonitorTimer;
static DWORD        m_u32EpgNextStartUpTime;

static U8           m_u8EpgNextStartUpIdx;  //the index of recording schedule,
                                            //indicate the recording item of _pstEpgTimer[],
                                            //0xFF : means NULL.  (TIMER_END_INDEX_NULL)
static U8           m_u8EpgStartingIdx;     //for recording flow control,save Liet index after record star up
#if ENABLE_PVR
static MS_EPGTIMER_RECORDING_QUEUE  m_u8EpgTimerRecQueue[EPGTIMER_REC_QUEUE_NUMBER];
#endif

EN_EPG_TIMER_ACT_TYPE _TimerActType = EN_EPGTIMER_ACT_NONE;
#if ENABLE_PVR
static MS_EPG_TIMER_PARAM m_AlternateEpgTimer;
static U8 RfChkCounter;
static S8 m_pstEpgidxItem = EPG_TIMER_InvalidIdx;
static S8 m_pstAlterIdx = EPG_TIMER_InvalidIdx;
static S32 s32SysTimerOffset = 0xFFFFFFFF;
static U32 _u32PVRExtPara = 0;     //pvr input from outside
#endif
extern U16 g_u16CiPinCode;

static U32 u32LatestManualTimerStartDate = 0;
U16             u16ReminderSrv=0;
U8               u8ReminderPcn=0;
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
BOOLEAN     g_bTimerTypeRecord=FALSE;
BOOLEAN     g_bTimerActiveStandbyMode=FALSE;
#endif
#if ENABLE_CI_PLUS
BOOLEAN     g_bTimeTypeOpRefresh = FALSE;
DWORD        m_u32EpgNextStartUpTime_Temp;
BOOLEAN        m_u32EpgNextStartUpTime_Temp_Flag = FALSE;
BOOLEAN        m_u32OpMenuRestart_Flag = FALSE;
#endif
/******************************************************************************/
/*                               Functions                                    */
/******************************************************************************/
/*****************************************************************************/
U32 MApp_EpgTimer_GetScheduleListBufAddr( void )
{
    return GetScheduleListBufAddr();
}

static U32 _MApp_EpgTimer_OpenXdataWindow( void )
{   // Warning: Be careful to use set and restore.
    EPG_ASSERT( 0 == (GetScheduleListBufAddr()%0x1000) );
    _pstEpgTimer = (MS_EPG_TIMER*)GetScheduleListBufAddr();

    return 0;
}

BOOLEAN _MApp_EpgTimer_Initdata( void )
{
    _pstEpgTimer = (MS_EPG_TIMER*)GetScheduleListBufAddr();

    return TRUE;
}

static void _MApp_EpgTimer_CloseXdataWindow(U32 u32PrvAddress)
{
    u32PrvAddress = u32PrvAddress;
}

static void _MApp_EpgTimer_ClearGlobalVar(void)
{
    m_dwEPGManualTimerMonitorTimer = msAPI_Timer_GetTime0();
    m_u32EpgNextStartUpTime    = 0;
    m_u8EpgNextStartUpIdx = EPGTIMER_INDEX_NULL;
}

DWORD MApp_GetEpgManualTimerStartDate(void)
{
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) )
//    ST_TIME stTime;
    return m_u32EpgNextStartUpTime;
//  MApp_ConvertSeconds2StTime(m_u32EpgNextStartUpTime,&stTime);
//  TIMER_DBG(("[%s:%s:%d] m_u32EpgNextStartUpTime : %u/%u/%u %u:%u:%u\n",
//                      __FILE__,__FUNCTION__,__LINE__,
//                    stTime.u16Year, stTime.u8Month, stTime.u8Day,
//                    stTime.u8Hour, stTime.u8Min, stTime.u8Sec));
#else
    ST_TIME stTime;
    U32 u32EpgNextStartUpTime = m_u32EpgNextStartUpTime;
    //add pre-stage for all scheduled event
    if(_TimerActType == EN_EPGTIMER_ACT_RECORDER_START)
    {
        if(MApp_GetLocalSystemTime()+EPG_RECORD_WAKEUP_LEADING_TIME_s < u32EpgNextStartUpTime)
        {
            if(u32EpgNextStartUpTime > EPG_RECORD_WAKEUP_LEADING_TIME_s)
                u32EpgNextStartUpTime -= EPG_RECORD_WAKEUP_LEADING_TIME_s;
            else
                u32EpgNextStartUpTime = 0;
        }
        else if((MApp_GetLocalSystemTime()+10) < u32EpgNextStartUpTime)
        {
            u32EpgNextStartUpTime = (MApp_GetLocalSystemTime()+10);
        }
    }
    else
    {
        if(MApp_GetLocalSystemTime()+EPG_WAKEUP_LEADING_TIME_s < u32EpgNextStartUpTime)
        {
            if(u32EpgNextStartUpTime > EPG_WAKEUP_LEADING_TIME_s)
                u32EpgNextStartUpTime -= EPG_WAKEUP_LEADING_TIME_s;
            else
                u32EpgNextStartUpTime = 0;
        }
    }
    MApp_ConvertSeconds2StTime(m_u32EpgNextStartUpTime,&stTime);
    TIMER_DBG(("[%s:%s:%d] m_u32EpgNextStartUpTime : %u/%u/%u %u:%u:%u\n",
                            __FILE__,__FUNCTION__,__LINE__,
                          stTime.u16Year, stTime.u8Month, stTime.u8Day,
                          stTime.u8Hour, stTime.u8Min, stTime.u8Sec));
    MApp_ConvertSeconds2StTime(u32EpgNextStartUpTime,&stTime);
    TIMER_DBG(("[%s:%s:%d] u32EpgNextStartUpTime : %u/%u/%u %u:%u:%u\n",
                            __FILE__,__FUNCTION__,__LINE__,
                          stTime.u16Year, stTime.u8Month, stTime.u8Day,
                          stTime.u8Hour, stTime.u8Min, stTime.u8Sec));
    return u32EpgNextStartUpTime;
#endif
}

/******************************************************************************/
#if ENABLE_PVR
BOOLEAN _EpgTimer_IsItemRecording(U8 ItemIndex)
{
    U8 i;

    for(i=0;i<EPGTIMER_REC_QUEUE_NUMBER;i++)
    {
        if(m_u8EpgTimerRecQueue[i].u8TimerIndex == ItemIndex)
        {
            return TRUE;
        }
    }
    return FALSE;
}
#endif

U32 MApp_EpgTimer_ResetStartUpTimer(U32 u32TimeAct)
{
    U8 u8TimerIdx;
    ST_TIME _stTime;
    U32 u32TimerItemStart, u32TimerItemEnd;
    U32 u32PrvAddress;
    U8 u8TimerTotal;

    u32TimerItemStart = u32TimerItemEnd = 0;

    m_u32EpgNextStartUpTime = 0xFFFFFFFF;
    m_u8EpgNextStartUpIdx = EPGTIMER_INDEX_NULL;
    _TimerActType = EN_EPGTIMER_ACT_NONE;

    u8TimerTotal = MApp_EpgUI_GetNumOfTimers();
    if ( u8TimerTotal == 0 )
    {
        m_u32EpgNextStartUpTime = 0;
        return 0;
    }

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
    u32TimeAct = u32TimeAct ;

    for ( u8TimerIdx = EPG_TIMER_FIRST_INDEX ; u8TimerIdx < u8TimerTotal ; u8TimerIdx++ )
    {
        _stTime  = _pstEpgTimer[u8TimerIdx].stStartDate;
        if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day == 0))
        {
            continue;
        }
        u32TimerItemStart = MApp_ConvertStTime2Seconds(&_stTime) ;

#if ENABLE_PVR
        //check whether the start time is past
        if ((u32TimerItemStart+20) < (MApp_GetLocalSystemTime()))
        {
            continue;
        }
        _stTime  = _pstEpgTimer[u8TimerIdx].stEndDate;
        if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day == 0))
        {
            continue;
        }
        u32TimerItemEnd = MApp_ConvertStTime2Seconds(&_stTime) ;


        if(EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[u8TimerIdx].enTimerType)
        {
            if(_pstEpgTimer[u8TimerIdx].satus == EN_EPGTIMER_STATUS_NORMAL)
            {
                if(u32TimerItemEnd > u32TimeAct && u32TimerItemStart < m_u32EpgNextStartUpTime)
                {
                    if(_EpgTimer_IsItemRecording(u8TimerIdx) == FALSE)
                    {
                        m_u32EpgNextStartUpTime = u32TimerItemStart;
                        m_u8EpgNextStartUpIdx = u8TimerIdx;
                        _TimerActType = EN_EPGTIMER_ACT_RECORDER_START;
                    }
                }
            }
        }
        else
#endif
        {
            if(EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[u8TimerIdx].enTimerType)
            {
                if(_pstEpgTimer[u8TimerIdx].satus == EN_EPGTIMER_STATUS_NORMAL)
                {
                    if(u32TimerItemStart < m_u32EpgNextStartUpTime)
                    {
                        m_u32EpgNextStartUpTime = u32TimerItemStart;
                        m_u8EpgNextStartUpIdx = u8TimerIdx;
                        _TimerActType = EN_EPGTIMER_ACT_REMINDER;
                    }
                }
            }
        #if ENABLE_CI_PLUS
            else if(EN_EPGUI_TIMER_CI_OP_REFRESH == _pstEpgTimer[u8TimerIdx].enTimerType)
            {
                if(_pstEpgTimer[u8TimerIdx].satus == EN_EPGTIMER_STATUS_NORMAL)
                {
                    if(u32TimerItemStart < m_u32EpgNextStartUpTime)
                    {
                        m_u32EpgNextStartUpTime = u32TimerItemStart;
                        m_u8EpgNextStartUpIdx = u8TimerIdx;
                        _TimerActType = EN_EPGTIMER_ACT_CI_OP_REFRESH;
                    }
                }
            }
        #endif
        }
    }

    if(m_u32EpgNextStartUpTime == 0xFFFFFFFF)
    {
        m_u32EpgNextStartUpTime = 0;
    }

    TIMER_DBG(("m_u32EpgNextStartUpTime:%ld\n", m_u32EpgNextStartUpTime));
    TIMER_DBG(("m_u8EpgNextStartUpIdx:%d\n", m_u8EpgNextStartUpIdx));
    {
        ST_TIME st;
        MApp_ConvertSeconds2StTime(m_u32EpgNextStartUpTime, &st);
        //printf("%d.%bd.%bd,%bd:%bd:%bd",st.u16Year,st.u8Month,st.u8Day,st.u8Hour,st.u8Min,st.u8Sec);
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    return m_u32EpgNextStartUpTime;
}

/******************************************************************************/
S8 MApp_EpgTimer_GetTimerItem(U32 u32TimeToFind)
{
    S8 s8RtnItem;
    U8 u8TimerIdx;
    ST_TIME _stTimeItem, _stTimeToFind;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    MApp_ConvertSeconds2StTime( u32TimeToFind, &_stTimeToFind);
    s8RtnItem = -1;
    for ( u8TimerIdx=EPG_TIMER_FIRST_INDEX ; u8TimerIdx<MApp_EpgUI_GetNumOfTimers() ; u8TimerIdx++ )
    {
        _stTimeItem  = _pstEpgTimer[u8TimerIdx].stStartDate;
        if ((_stTimeItem.u16Year == 0) && (_stTimeItem.u8Day == 0) && (_stTimeItem.u8Hour == 0))
        {
            continue;
        }

        if(_stTimeItem.u8Hour == _stTimeToFind.u8Hour && _stTimeItem.u8Min == _stTimeToFind.u8Min)
        {
            if(EN_EPGRM_WEEKLY == _pstEpgTimer[u8TimerIdx].enRepeatMode
                && MApp_GetDayOfWeek(_stTimeItem.u16Year, _stTimeItem.u8Month, _stTimeItem.u8Day)
                        != MApp_GetDayOfWeek(_stTimeToFind.u16Year, _stTimeToFind.u8Month, _stTimeToFind.u8Day))
            {
                continue;
            }
            s8RtnItem = u8TimerIdx;
            break;
        }

#if ENABLE_PVR
        //End time section
        _stTimeItem  = _pstEpgTimer[u8TimerIdx].stEndDate;
        if ((_stTimeItem.u16Year == 0) && (_stTimeItem.u8Day == 0) && (_stTimeItem.u8Hour == 0))
        {
            continue;
        }

        if(_stTimeItem.u8Hour == _stTimeToFind.u8Hour && _stTimeItem.u8Min == _stTimeToFind.u8Min)
        {
            if(EN_EPGRM_WEEKLY == _pstEpgTimer[u8TimerIdx].enRepeatMode
                && MApp_GetDayOfWeek(_stTimeItem.u16Year, _stTimeItem.u8Month, _stTimeItem.u8Day)
                        != MApp_GetDayOfWeek(_stTimeToFind.u16Year, _stTimeToFind.u8Month, _stTimeToFind.u8Day))
            {
                continue;
            }
            s8RtnItem = u8TimerIdx;
            break;
        }
#endif
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    return s8RtnItem;
}

/******************************************************************************/
// This function clone EPGTimer data from database memory to EPGTimer Array
/******************************************************************************/
void _MApp_EpgTimer_RetrieveTimerList(void)
{
    //U32 u32PrvAddress;

   // u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    // Load data from data base
    MApp_DB_Load_ManualEventSetting( (U8*)_pstEpgTimer, EPG_REAL_USE_DB_SIZE);

    //_MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
}

/******************************************************************************/
// This function clone EPGTimer data from EPGTimer Array to database memory
/******************************************************************************/
void _MApp_EpgTimer_SaveTimerList(BOOLEAN bUpdateDB)
{
    //U32 u32PrvAddress;
  #if 0//( BLOADER || (!ENABLE_CI_PLUS) )
    U16  u16CheckSum;
  #endif


    TIMER_DBG((("_MApp_EpgTimer_SaveTimerList()~UpdateDB:%u\n"), bUpdateDB));

    //u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();


    if( bUpdateDB )
    {
#if ( !BLOADER )
    #if 1//(ENABLE_S2_EPG_REMINDER)
        {
        #if 1 // Refine at 20150908
            //_pstEpgTimer->u8UiSrcType = MApp_InputSrc_Get_UiInputSrcType();
        #else
            if(IsS2InUse())
                _pstEpgTimer->u8SrcIsDtvS2 = 1;
            else
                _pstEpgTimer->u8SrcIsDtvS2 = 0;
        #endif
        }
    #endif

        //printf("_pstEpgTimer(%u) CRC=0x%X\n", EPG_REAL_USE_DB_SIZE, msAPI_CRC16_Cal(_pstEpgTimer, EPG_REAL_USE_DB_SIZE) );

        // Save data to data base
        MApp_DB_Save_ManualEventSetting((BYTE*)_pstEpgTimer, EPG_REAL_USE_DB_SIZE);

#else
        //u16CheckSum=0;
#endif
    }


    //_MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);

#if 0
    _MApp_EpgTimer_RetrieveTimerList();
    _MApp_EpgTimer_Show();
#endif
}

/******************************************************************************/
U16 MApp_EpgTimer_CalDaysByMon(U8 u8Mon)
{
    switch ( u8Mon )
    {
        case 2:
            return 29;

        case 4: case 6: case 9: case 11:
            return 30;

        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;

        default:
            return 0;
    }
}

#if 0
/******************************************************************************/
static void MApp_EpgTimer_LoadTimerList( U8 u8TimerListIdx )
{
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    /*
        // Switch TimerList Index between page1 to page2
        if ( (stEpgTimerParam.u8CurTimerIdx >= (EPG_TIMER_MAX_NUM/2)) &&
             (u8TimerListIdx < (EPG_TIMER_MAX_NUM/2)) )
        {
            u8TimerListIdx += (EPG_TIMER_MAX_NUM/2);
        }
    */


    if ( u8TimerListIdx < MApp_EpgUI_GetNumOfTimers() )
    {
        stEpgTimerParam.stEpgTimer = _pstEpgTimer[u8TimerListIdx];
    }
    else
    {
        TIMER_DBG(("Load Timer List>> INVALID Timer Index\n"));
    }

    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
}
#endif

/******************************************************************************/
static void _MApp_EpgTimer_SetTimerEventName(EN_EPG_MT_DATE enDateMode)
{
    switch ( enDateMode )
    {
        case EN_MT_DATE_EVENT:
            // Set event name to timer's title
//            MApp_Epg_GetEventName(MApp_EpgUI_Func_Get_CurFocusEvtIdx(), p_string_buffer, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN);
//            memcpy(stEpgTimerParam.stEpgTimer.au16EvtName, p_string_buffer, sizeof(stEpgTimerParam.stEpgTimer.au16EvtName));
            MApp_Epg_GetEventName(MApp_EpgUI_Func_Get_CurFocusEvtIdx(), stEpgTimerParam.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN);

            break;

        case EN_MT_DATE_NEW:
            break;
    }
}

/******************************************************************************/
static void MApp_EpgTimer_SetTimerDate(EN_EPG_MT_DATE enDateMode)
{
#if ENABLE_DVB
    U32 u32SystemTime, u32RecDur, u32EventStart, u32EventEnd;
    EventTime stEvtTime;

    switch ( enDateMode )
    {
        case EN_MT_DATE_EVENT:
            // Set event_date to timer's date
            MApp_Epg_GetEventTime(MApp_EpgUI_Func_Get_CurFocusEvtIdx(), &stEvtTime);
            u32EventStart = stEvtTime.u32StartTime;
            u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
            MApp_ConvertSeconds2StTime(u32EventStart, &(stEpgTimerParam.stEpgTimer.stStartDate));
            MApp_ConvertSeconds2StTime(u32EventEnd, &(stEpgTimerParam.stEpgTimer.stEndDate));

            break;

        case EN_MT_DATE_NEW:
            // Set current time to timer's date
            u32SystemTime = MApp_GetLocalSystemTime() + (2*SECONDS_PER_MIN);
            MApp_ConvertSeconds2StTime(u32SystemTime, &(stEpgTimerParam.stEpgTimer.stStartDate));
            u32RecDur = u32SystemTime + 30*60;   // set default record time as half hour
            MApp_ConvertSeconds2StTime((S32)(u32RecDur), &(stEpgTimerParam.stEpgTimer.stEndDate));
            break;
    }
#endif
}

/******************************************************************************/
static void MApp_EpgTimer_SetTimerAsNew( void )
{
    stEpgTimerParam.stEpgTimer.enTimerType = EN_EPGUI_TIMER_REMINDER;
    if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL))
    {
        stEpgTimerParam.stEpgTimer.enTimerType = EN_EPGUI_TIMER_REMINDER;
    }
    #if ENABLE_PVR
    else if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_PANEL))
    {
        stEpgTimerParam.stEpgTimer.enTimerType = EN_EPGUI_TIMER_RECORDER;
    }
    #endif

    // Set current focused srv to EpgTimerParam
    MEMBER_SERVICETYPE srvType = MApp_EpgUI_Func_Get_CurFocusSrvType();
    U16 srvPos = MApp_EpgUI_Func_Get_CurFocusSrvPos();

    stEpgTimerParam.stEpgTimer.u8PCN = msAPI_CM_GetPhysicalChannelNumber(srvType, srvPos);
    stEpgTimerParam.stEpgTimer.u16SrvID = msAPI_CM_GetService_ID(srvType, srvPos);
    MApp_EpgTimer_SetTimerDate( EN_MT_DATE_NEW );
    stEpgTimerParam.stEpgTimer.bNoTitle = FALSE;
    stEpgTimerParam.stEpgTimer.bRecordSplitEvent= FALSE;
    stEpgTimerParam.stEpgTimer.bRecordSeriesEvent = FALSE;
    stEpgTimerParam.stEpgTimer.bRecordRecomEvent= FALSE;
}

/******************************************************************************/
U8 MApp_EpgTimer_GetEmptyTimerIdx( void )
{
    U8 LoopIdx = EPG_TIMER_MAX_NUM;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    for ( LoopIdx=0; LoopIdx<EPG_TIMER_MAX_NUM ; LoopIdx++ )
    {
        if ( _pstEpgTimer[LoopIdx].enTimerType == EN_EPGUI_TIMER_NULL
            || _pstEpgTimer[LoopIdx].enTimerType >= EN_EPGUI_TIMER_INVALID)
        {
            break;
        }
    }

    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);

    return LoopIdx;
}

/******************************************************************************/
BOOLEAN MApp_EpgTimer_IsTimerExistByIdx( U8 u8TimerListIdx )
{
    U8 totalTimerListIdx;
    U8 curPageItem = 0;
    BOOLEAN isItemFound = FALSE;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    for ( totalTimerListIdx=0; totalTimerListIdx < EPG_TIMER_MAX_NUM; totalTimerListIdx++ )
    {
    #if 1
        if((MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL)
                        && EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
            || (MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_PANEL)
                        && EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[totalTimerListIdx].enTimerType))
    #else
#if (ENABLE_TIMER && ENABLE_PVR)
        if((MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL)
                        && EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
            || (MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_PANEL)
                        && EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[totalTimerListIdx].enTimerType))
#elif ENABLE_TIMER
        if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL) && EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
#elif ENABLE_PVR
        if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_PANEL) && EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
#endif
    #endif
        {
            if((u8TimerListIdx + g_TimerList_CurPageStartItem) == curPageItem )
            {
                stEpgTimerParam.stEpgTimer = _pstEpgTimer[totalTimerListIdx];       //Load list item data
                isItemFound = TRUE;
                break;
            }
            curPageItem++;
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    return isItemFound;
}

/******************************************************************************/
// Add to check the timerlist is full or not
BOOLEAN MApp_EpgTimer_IsReminderListFull(void)
{
    #if 0
    if(MApp_EpgUI_GetNumOfTimers() >= EPG_TIMER_MAX_NUM)
    {
         return TRUE;
    }
    else
    {
        return FALSE;
    }
    #else
    U8 reminderCount = 0;
    U8 totalTimerListIdx;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    for ( totalTimerListIdx=0; totalTimerListIdx<EPG_TIMER_MAX_NUM; totalTimerListIdx++ )
    {
        if (EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
        {
            reminderCount++;
            if(reminderCount >= EPG_REMINDER_MAX_COUNT)
            {
                return TRUE;
            }
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    return FALSE;
    #endif
}

/*Overlap Check Start*/
#if (ENABLE_PVR)
/***************************************************************************************/
static BOOLEAN _MApp_EpgTimer_IsTimePeriodOverlap(U32 u32ChkStartTime, U32 u32ChkEndTime, U32 u32ItemStartTime, U32 u32ItemEndTime)
{
    TIMER_OVERLAP_DEG(printf("[%lu-%lu][%lu-%lu]\n", u32ChkStartTime, u32ChkEndTime, u32ItemStartTime, u32ItemEndTime));
    return ( u32ChkStartTime < u32ItemEndTime && u32ChkEndTime > u32ItemStartTime );
}

/***************************************************************************************/
BOOLEAN _MApp_EpgTimer_IsTimeSpotInPeriod(U32 u32TimeSpot, U32 u32TimePeriodStart, U32 u32TimePeriodEnd)
{
    if(u32TimeSpot >= u32TimePeriodStart && u32TimeSpot <= u32TimePeriodEnd)
    {
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************************/
static void _MApp_EpgTimer_GetWeekStartingTime(ST_TIME *pstTime)
{
    DAYOFWEEK day = (DAYOFWEEK)MApp_GetDayOfWeek(pstTime->u16Year, pstTime->u8Month, pstTime->u8Day);
    MApp_AddDay2StTime(((S32)(-1)*day), pstTime);
    pstTime->u8Hour = 0;
    pstTime->u8Min = 0;
    pstTime->u8Sec = 0;
}

/***************************************************************************************/
static void _MApp_EpgTimer_GetWeekEndingTime(ST_TIME *pstTime)
{
    DAYOFWEEK day = (DAYOFWEEK)MApp_GetDayOfWeek(pstTime->u16Year, pstTime->u8Month, pstTime->u8Day);
    MApp_AddDay2StTime(((S32)6-day), pstTime);
    pstTime->u8Hour = 23;
    pstTime->u8Min = 59;
    pstTime->u8Sec = 59;
}

/***************************************************************************************/
static void _MApp_EpgTimer_GetDayStartingTime(ST_TIME *pstTime)
{
    pstTime->u8Hour = 0;
    pstTime->u8Min = 0;
    pstTime->u8Sec = 0;
}

/***************************************************************************************/
static void _MApp_EpgTimer_GetDayEndingTime(ST_TIME *pstTime)
{
    pstTime->u8Hour = 23;
    pstTime->u8Min = 59;
    pstTime->u8Sec = 59;
}

/***************************************************************************************/
static void _MApp_EpgTimer_ShiftTimeToSameWeek(ST_TIME *pTimeToShift, ST_TIME *pTimeFixed)
{//Alter the date of pTimeToShift to the week of pTimeFixed
    DAYOFWEEK dayShift = (DAYOFWEEK)MApp_GetDayOfWeek(pTimeToShift->u16Year, pTimeToShift->u8Month, pTimeToShift->u8Day);
    DAYOFWEEK dayStandard = (DAYOFWEEK)MApp_GetDayOfWeek(pTimeFixed->u16Year, pTimeFixed->u8Month, pTimeFixed->u8Day);

    pTimeToShift->u16Year = pTimeFixed->u16Year;
    pTimeToShift->u8Month = pTimeFixed->u8Month;
    pTimeToShift->u8Day = pTimeFixed->u8Day;
    MApp_AddDay2StTime(((S32)dayShift - dayStandard), pTimeToShift);
}

/***************************************************************************************/
static void _MApp_EpgTimer_ShiftTimeToSameDay(ST_TIME *pTimeToShift, ST_TIME *pTimeFixed)
{//Alter the day of pTimeToShift to the day of pTimeFixed
    pTimeToShift->u16Year = pTimeFixed->u16Year;
    pTimeToShift->u8Month = pTimeFixed->u8Month;
    pTimeToShift->u8Day = pTimeFixed->u8Day;
}

/***************************************************************************************/
static S8 _MApp_EpgTimer_CheckInSingleWeek(ST_TIME *pstTimeStart ,ST_TIME *pstTimeEnd)
{   //return value [1: Across week]  [0: Same week]  [-1: > 7 Days]
    DAYOFWEEK eDayOfWeekStart = (DAYOFWEEK)MApp_GetDayOfWeek(pstTimeStart->u16Year, pstTimeStart->u8Month, pstTimeStart->u8Day);
    DAYOFWEEK eDayOfWeekEnd = (DAYOFWEEK)MApp_GetDayOfWeek(pstTimeEnd->u16Year, pstTimeEnd->u8Month, pstTimeEnd->u8Day);
    if((MApp_ConvertStTime2Seconds(pstTimeEnd) - MApp_ConvertStTime2Seconds(pstTimeStart)) > SECONDS_PER_DAY*7)
    {
        return -1;
    }
    else if(eDayOfWeekStart > eDayOfWeekEnd
                || (eDayOfWeekStart == eDayOfWeekEnd
                    && (pstTimeStart->u8Hour > pstTimeEnd->u8Hour
                        || (pstTimeStart->u8Hour == pstTimeEnd->u8Hour && pstTimeStart->u8Min > pstTimeEnd->u8Min))))
    {
        return 1;
    }
    return 0;
}

/***************************************************************************************/
static S8 _MApp_EpgTimer_CheckInSingleDay(ST_TIME *pstTimeStart ,ST_TIME *pstTimeEnd)
{   //return value [1: Across day]  [0: Same day]  [-1: > One day]
    if((MApp_ConvertStTime2Seconds(pstTimeEnd) - MApp_ConvertStTime2Seconds(pstTimeStart)) > SECONDS_PER_DAY)
    {
        return -1;
    }
    else if((pstTimeStart->u16Year != pstTimeEnd->u16Year
        || pstTimeStart->u8Month != pstTimeEnd->u8Month
        || pstTimeStart->u8Day != pstTimeEnd->u8Day))
    {
        return 1;
    }
    return 0;
}

/***************************************************************************************/
S8 _MApp_EpgTimer_CompareTimeToMin(ST_TIME *pstTimeA, ST_TIME *pstTimeB)
{   //return value [1:A>B]  [0: A==B]  [-1:A<B]
    U32 timeA = MApp_ConvertStTime2Seconds(pstTimeA) ;
    U32 timeB = MApp_ConvertStTime2Seconds(pstTimeB) ;
    if(timeA == timeB)
    {
        return 0;
    }
    else if(timeA > timeB)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
/***************************************************************************************/
BOOLEAN _MApp_EpgTimer_IsOverlapShiftSameWeek(ST_TIME *pstTimeA_Start, ST_TIME *pstTimeA_End, ST_TIME *pstTimeB_Start, ST_TIME *pstTimeB_End)
{
    ST_TIME stTimeTmp;
    U32 u32TimeB_Start;
    U32 u32TimeB_End;
    U32 u32TimeA_Start = MApp_ConvertStTime2Seconds(pstTimeA_Start) ;
    U32 u32TimeA_End = MApp_ConvertStTime2Seconds(pstTimeA_End) ;

    stTimeTmp = *pstTimeB_Start;
    _MApp_EpgTimer_ShiftTimeToSameWeek(&stTimeTmp, pstTimeA_Start);
    u32TimeB_Start = MApp_ConvertStTime2Seconds(&stTimeTmp);

    stTimeTmp = *pstTimeB_End;
    _MApp_EpgTimer_ShiftTimeToSameWeek(&stTimeTmp, pstTimeA_Start);
    u32TimeB_End = MApp_ConvertStTime2Seconds(&stTimeTmp);
    #if 0
    {
    ST_TIME time;
    MApp_ConvertSeconds2StTime(u32TimeA_Start, &time);
    printf("A_S:[%u/%bu/%bu][%bu:%bu:%bu]\n",time.u16Year, time.u8Month, time.u8Day, time.u8Hour, time.u8Min, time.u8Sec);
    MApp_ConvertSeconds2StTime(u32TimeA_End, &time);
    printf("A_E:[%u/%bu/%bu][%bu:%bu:%bu]\n",time.u16Year, time.u8Month, time.u8Day, time.u8Hour, time.u8Min, time.u8Sec);
    MApp_ConvertSeconds2StTime(u32TimeB_Start, &time);
    printf("B_S:[%u/%bu/%bu][%bu:%bu:%bu]\n",time.u16Year, time.u8Month, time.u8Day, time.u8Hour, time.u8Min, time.u8Sec);
    MApp_ConvertSeconds2StTime(u32TimeB_End, &time);
    printf("B_E:[%u/%bu/%bu][%bu:%bu:%bu]\n",time.u16Year, time.u8Month, time.u8Day, time.u8Hour, time.u8Min, time.u8Sec);
    }
    #endif
    return _MApp_EpgTimer_IsTimePeriodOverlap(u32TimeA_Start, u32TimeA_End, u32TimeB_Start, u32TimeB_End);
}

/***************************************************************************************/
BOOLEAN _MApp_EpgTimer_IsOverlapShiftSameDay(ST_TIME *pstTimeA_Start, ST_TIME *pstTimeA_End, ST_TIME *pstTimeB_Start, ST_TIME *pstTimeB_End)
{
    ST_TIME stTimeTmp;
    U32 u32TimeB_Start;
    U32 u32TimeB_End;
    U32 u32TimeA_Start = MApp_ConvertStTime2Seconds(pstTimeA_Start) ;
    U32 u32TimeA_End = MApp_ConvertStTime2Seconds(pstTimeA_End) ;

    stTimeTmp = *pstTimeB_Start;
    _MApp_EpgTimer_ShiftTimeToSameDay(&stTimeTmp, pstTimeA_Start);
    u32TimeB_Start = MApp_ConvertStTime2Seconds(&stTimeTmp);

    stTimeTmp = *pstTimeB_End;
    _MApp_EpgTimer_ShiftTimeToSameDay(&stTimeTmp, pstTimeA_Start);
    u32TimeB_End = MApp_ConvertStTime2Seconds(&stTimeTmp);

    return _MApp_EpgTimer_IsTimePeriodOverlap(u32TimeA_Start, u32TimeA_End, u32TimeB_Start, u32TimeB_End);
}

/***************************************************************************************/
#if ENABLE_PVR
BOOLEAN MApp_EpgTimer_CheckEventInTimerlist(U32 EventStart, U32 EventEnd, U16 stEvtID)
{
    U8 u8TimerIdx;
    ST_TIME _stTime;
    U32 u32TimerItemStart, u32TimerItemEnd;
    for ( u8TimerIdx=EPG_TIMER_FIRST_INDEX ; u8TimerIdx<MApp_EpgUI_GetNumOfTimers() ; u8TimerIdx++ )
    {
        _stTime  = _pstEpgTimer[u8TimerIdx].stStartDate;
        if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day == 0))
        {
            continue;
        }
        u32TimerItemStart = MApp_ConvertStTime2Seconds(&_stTime) ;


        _stTime  = _pstEpgTimer[u8TimerIdx].stEndDate;
        if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day == 0))
        {
            continue;
        }
        u32TimerItemEnd = MApp_ConvertStTime2Seconds(&_stTime) ;
        if (stEvtID == _pstEpgTimer[u8TimerIdx].u16EventID)
        {
            if((EventEnd > u32TimerItemStart) && (EventStart < u32TimerItemEnd))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

     }
    return false;
}
#endif
/***************************************************************************************/
#if 1
BOOLEAN _MApp_EpgTimer_IsOverlapInWeekly(ST_TIME *pstTimeA_Start, ST_TIME *pstTimeA_End, ST_TIME *pstTimeB_Start, ST_TIME *pstTimeB_End)
{
    ST_TIME stTimeTmp;
    //U32 u32TimeA_Start = MApp_ConvertStTime2Seconds(pstTimeA_Start) ;
    //U32 u32TimeA_End = MApp_ConvertStTime2Seconds(pstTimeA_End) ;
    // u32TimeB_Start = MApp_ConvertStTime2Seconds(pstTimeB_Start) ;
//    U32 u32TimeB_End = MApp_ConvertStTime2Seconds(pstTimeB_End) ;

        //----  A > 7 Days or B > 7 Days
    if(_MApp_EpgTimer_CheckInSingleWeek(pstTimeA_Start, pstTimeA_End) < 0
        ||_MApp_EpgTimer_CheckInSingleWeek(pstTimeB_Start, pstTimeB_End) < 0 )
    {
        TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly past.\n"));
        return TRUE;
    }
    else if(_MApp_EpgTimer_CheckInSingleWeek(pstTimeA_Start, pstTimeA_End) > 0)
    {
        //----  A across week ,B across week
        if(_MApp_EpgTimer_CheckInSingleWeek(pstTimeB_Start, pstTimeB_End) > 0)
        {
            ST_TIME stTimeTmpB;
            TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.c/B.c.\n"));

            stTimeTmp = *pstTimeA_Start;
            _MApp_EpgTimer_GetWeekEndingTime(&stTimeTmp);
            stTimeTmpB = *pstTimeB_Start;
            _MApp_EpgTimer_GetWeekEndingTime(&stTimeTmpB);
            if(_MApp_EpgTimer_IsOverlapShiftSameWeek(pstTimeA_Start, &stTimeTmp, pstTimeB_Start, &stTimeTmpB))
            {
                TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.c/B.c overlap1.\n"));
                return TRUE;
            }

            stTimeTmpB = *pstTimeB_End;
            _MApp_EpgTimer_GetWeekStartingTime(&stTimeTmpB);
            if(_MApp_EpgTimer_IsOverlapShiftSameWeek(pstTimeA_Start, &stTimeTmp, &stTimeTmpB, pstTimeB_End))
            {
                TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.c/B.c overlap2.\n"));
                return TRUE;
            }

            stTimeTmp = *pstTimeA_End;
            _MApp_EpgTimer_GetWeekStartingTime(&stTimeTmp);
            stTimeTmpB = *pstTimeB_Start;
            _MApp_EpgTimer_GetWeekEndingTime(&stTimeTmpB);
            if(_MApp_EpgTimer_IsOverlapShiftSameWeek(&stTimeTmp, pstTimeA_End, pstTimeB_Start, &stTimeTmpB))
            {
                TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.c/B.c overlap3.\n"));
                return TRUE;
            }

            stTimeTmpB = *pstTimeB_End;
            _MApp_EpgTimer_GetWeekStartingTime(&stTimeTmpB);
            if(_MApp_EpgTimer_IsOverlapShiftSameWeek(&stTimeTmp, pstTimeA_End, &stTimeTmpB, pstTimeB_End))
            {
                TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.c/B.c overlap4.\n"));
                return TRUE;
            }

            return FALSE;
        }

        //----  A across week ,B same week
        else if(_MApp_EpgTimer_CheckInSingleWeek(pstTimeB_Start, pstTimeB_End) == 0)
        {
            stTimeTmp = *pstTimeA_Start;
            TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.c/B.s\n"));

            _MApp_EpgTimer_GetWeekEndingTime(&stTimeTmp);
            if(_MApp_EpgTimer_IsOverlapShiftSameWeek(pstTimeA_Start, &stTimeTmp, pstTimeB_Start, pstTimeB_End))
            {
                TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.c/B.s overlap1.\n"));
                return TRUE;
            }

            stTimeTmp = *pstTimeA_End;
            _MApp_EpgTimer_GetWeekStartingTime(&stTimeTmp);

            if(_MApp_EpgTimer_IsOverlapShiftSameWeek(&stTimeTmp, pstTimeA_End, pstTimeB_Start, pstTimeB_End))
            {
                TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.c/B.s overlap2.\n"));
                return TRUE;
            }

            return FALSE;
        }
    }
    else if(_MApp_EpgTimer_CheckInSingleWeek(pstTimeA_Start, pstTimeA_End) == 0)
    {
        //----  A same week ,B across week
        if(_MApp_EpgTimer_CheckInSingleWeek(pstTimeB_Start, pstTimeB_End) > 0)
        {
            stTimeTmp = *pstTimeB_Start;
            TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.s/B.c\n"));

            _MApp_EpgTimer_GetWeekEndingTime(&stTimeTmp);
            if(_MApp_EpgTimer_IsOverlapShiftSameWeek(pstTimeA_Start, pstTimeA_End, pstTimeB_Start, &stTimeTmp))
            {
                TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.s/B.c overlap1.\n"));
                return TRUE;
            }

            stTimeTmp = *pstTimeB_End;
            _MApp_EpgTimer_GetWeekStartingTime(&stTimeTmp);
            if(_MApp_EpgTimer_IsOverlapShiftSameWeek(pstTimeA_Start, pstTimeA_End, &stTimeTmp, pstTimeB_End))
            {
                TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.s/B.c overlap2.\n"));
                return TRUE;
            }

            return FALSE;
        }

        //----  A same week ,B same week
        else if(_MApp_EpgTimer_CheckInSingleWeek(pstTimeB_Start, pstTimeB_End) == 0)
        {
            TIMER_OVERLAP_WEEKLY_DEG(printf("Check weekly A.s/B.s\n"));
            return _MApp_EpgTimer_IsOverlapShiftSameWeek(pstTimeA_Start, pstTimeA_End, pstTimeB_Start, pstTimeB_End);
        }
    }
    return FALSE;
}
#endif
/***************************************************************************************/
BOOLEAN _MApp_EpgTimer_IsOverlapInDaily(ST_TIME *pstTimeA_Start, ST_TIME *pstTimeA_End, ST_TIME *pstTimeB_Start, ST_TIME *pstTimeB_End)
{
    ST_TIME stTimeTmp;

        //----  A > One day or B > One day
    if(_MApp_EpgTimer_CheckInSingleDay(pstTimeA_Start, pstTimeA_End) < 0
        ||_MApp_EpgTimer_CheckInSingleDay(pstTimeB_Start, pstTimeB_End) < 0 )
    {
        TIMER_OVERLAP_DAILY_DEG(printf("Check daily past.\n"));
        return TRUE;
    }
    else if(_MApp_EpgTimer_CheckInSingleDay(pstTimeA_Start, pstTimeA_End) > 0)
    {
        //----  A across day ,B across day
        if(_MApp_EpgTimer_CheckInSingleDay(pstTimeB_Start, pstTimeB_End) > 0)
        {
            ST_TIME stTimeTmpB;
            TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.c/B.c.\n"));

            stTimeTmp = *pstTimeA_Start;
            _MApp_EpgTimer_GetDayEndingTime(&stTimeTmp);
            stTimeTmpB = *pstTimeB_Start;
            _MApp_EpgTimer_GetDayEndingTime(&stTimeTmpB);
            if(_MApp_EpgTimer_IsOverlapShiftSameDay(pstTimeA_Start, &stTimeTmp, pstTimeB_Start, &stTimeTmpB))
            {
                TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.c/B.c overlap1.\n"));
                return TRUE;
            }

            stTimeTmpB = *pstTimeB_End;
            _MApp_EpgTimer_GetDayStartingTime(&stTimeTmpB);
            if(_MApp_EpgTimer_IsOverlapShiftSameDay(pstTimeA_Start, &stTimeTmp, &stTimeTmpB, pstTimeB_End))
            {
                TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.c/B.c overlap2.\n"));
                return TRUE;
            }

            stTimeTmp = *pstTimeA_End;
            _MApp_EpgTimer_GetDayStartingTime(&stTimeTmp);
            stTimeTmpB = *pstTimeB_Start;
            _MApp_EpgTimer_GetDayEndingTime(&stTimeTmpB);
            if(_MApp_EpgTimer_IsOverlapShiftSameDay(&stTimeTmp, pstTimeA_End, pstTimeB_Start, &stTimeTmpB))
            {
                TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.c/B.c overlap3.\n"));
                return TRUE;
            }

            stTimeTmpB = *pstTimeB_End;
            _MApp_EpgTimer_GetDayStartingTime(&stTimeTmpB);
            if(_MApp_EpgTimer_IsOverlapShiftSameDay(&stTimeTmp, pstTimeA_End, &stTimeTmpB, pstTimeB_End))
            {
                TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.c/B.c overlap4.\n"));
                return TRUE;
            }

            return FALSE;
        }
        //----  A across day ,B same day
        else if(_MApp_EpgTimer_CheckInSingleDay(pstTimeB_Start, pstTimeB_End) == 0)
        {
            stTimeTmp = *pstTimeA_Start;
            TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.c/B.s\n"));

            _MApp_EpgTimer_GetDayEndingTime(&stTimeTmp);
            if(_MApp_EpgTimer_IsOverlapShiftSameDay(pstTimeA_Start, &stTimeTmp, pstTimeB_Start, pstTimeB_End))
            {
                TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.c/B.s overlap1.\n"));
                return TRUE;
            }

            stTimeTmp = *pstTimeA_End;
            _MApp_EpgTimer_GetDayStartingTime(&stTimeTmp);

            if(_MApp_EpgTimer_IsOverlapShiftSameDay(&stTimeTmp, pstTimeA_End, pstTimeB_Start, pstTimeB_End))
            {
                TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.c/B.s overlap2.\n"));
                return TRUE;
            }

            return FALSE;
        }
    }
    else if(_MApp_EpgTimer_CheckInSingleDay(pstTimeA_Start, pstTimeA_End) == 0)
    {
        //----  A same day ,B across day
        if(_MApp_EpgTimer_CheckInSingleDay(pstTimeB_Start, pstTimeB_End) > 0)
        {
            stTimeTmp = *pstTimeB_Start;
            TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.s/B.c\n"));

            _MApp_EpgTimer_GetDayEndingTime(&stTimeTmp);
            if(_MApp_EpgTimer_IsOverlapShiftSameDay(pstTimeA_Start, pstTimeA_End, pstTimeB_Start, &stTimeTmp))
            {
                TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.s/B.c overlap1.\n"));
                return TRUE;
            }

            stTimeTmp = *pstTimeB_End;
            _MApp_EpgTimer_GetDayStartingTime(&stTimeTmp);
            if(_MApp_EpgTimer_IsOverlapShiftSameDay(pstTimeA_Start, pstTimeA_End, &stTimeTmp, pstTimeB_End))
            {
                TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.s/B.c overlap2.\n"));
                return TRUE;
            }

            return FALSE;
        }
        //----  A same day ,B same day
        else if(_MApp_EpgTimer_CheckInSingleDay(pstTimeB_Start, pstTimeB_End) == 0)
        {
            TIMER_OVERLAP_DAILY_DEG(printf("Check daily A.s/B.s\n"));
            return _MApp_EpgTimer_IsOverlapShiftSameDay(pstTimeA_Start, pstTimeA_End, pstTimeB_Start, pstTimeB_End);
        }
    }
    return FALSE;
}

/***************************************************************************************/
static BOOLEAN _MApp_EpgTimer_IsRecorderSettingOverlap(MS_EPG_TIMER *pTimerChk , MS_EPG_TIMER *pTimerItem)
{
    #if 0 // dead code when bEnableOneRfRecTwoItem = FALSE;
    {
        BOOLEAN bEnableOneRfRecTwoItem = FALSE;
        if (bEnableOneRfRecTwoItem)
        {
            //skip overlap checking when recording channels within same RF, but not same program
        MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
        U16 srvPos = INVALID_SERVICE_ID;
        BYTE cRfChk;
        BYTE cRfItem;

        msAPI_CM_GetServiceTypeAndPositionWithPCN(pTimerChk->u8PCN, pTimerChk->u16SrvID, &srvType, &srvPos);
        cRfChk = msAPI_CM_GetPhysicalChannelNumber(srvType, srvPos);
        msAPI_CM_GetServiceTypeAndPositionWithPCN(pTimerItem->u8PCN, pTimerItem->u16SrvID, &srvType, &srvPos);
        cRfItem = msAPI_CM_GetPhysicalChannelNumber(srvType, srvPos);
        if((cRfChk == cRfItem && RfChkCounter==0)
            && !(pTimerChk->u8PCN == pTimerItem->u8PCN
                && pTimerChk->u16SrvID == pTimerItem->u16SrvID))
        {
            RfChkCounter = 1;
            return FALSE;
        }
    }
    }
    #endif
    if((EN_EPGRM_ONCE == pTimerChk->enRepeatMode || EN_EPGRM_AUTO == pTimerChk->enRepeatMode)
        && (_MApp_EpgTimer_CompareTimeToMin(&(pTimerChk->stEndDate), &(pTimerItem->stStartDate)) < 0))
    {
        TIMER_OVERLAP_DEG(printf("skip before repeat start time.\n"));
        return FALSE;
    }
    else if(EN_EPGRM_DAILY == pTimerChk->enRepeatMode || EN_EPGRM_DAILY == pTimerItem->enRepeatMode)
    {
        TIMER_OVERLAP_DEG(printf("Recorder overlap daily.\n"));

        return _MApp_EpgTimer_IsOverlapInDaily(&(pTimerChk->stStartDate), &(pTimerChk->stEndDate),&(pTimerItem->stStartDate), &(pTimerItem->stEndDate));
    }
    else if(EN_EPGRM_WEEKLY== pTimerChk->enRepeatMode || EN_EPGRM_WEEKLY == pTimerItem->enRepeatMode)
    {
        TIMER_OVERLAP_DEG(printf("Recorder overlap weekly.\n"));

        return _MApp_EpgTimer_IsOverlapInWeekly(&(pTimerChk->stStartDate), &(pTimerChk->stEndDate),&(pTimerItem->stStartDate), &(pTimerItem->stEndDate));
    }
    else if((EN_EPGRM_ONCE == pTimerChk->enRepeatMode || EN_EPGRM_AUTO == pTimerChk->enRepeatMode)
        && (EN_EPGRM_ONCE == pTimerItem->enRepeatMode || EN_EPGRM_AUTO == pTimerItem->enRepeatMode))
    {
        TIMER_OVERLAP_DEG(printf("Recorder overlap once.\n"));
        {
            U32 u32TimeChk_Start = MApp_ConvertStTime2Seconds(&(pTimerChk->stStartDate)) ;
            U32 u32TimeChk_End = MApp_ConvertStTime2Seconds(&(pTimerChk->stEndDate)) ;
            U32 u32TimeItem_Start = MApp_ConvertStTime2Seconds(&(pTimerItem->stStartDate)) ;
            U32 u32TimeItem_End = MApp_ConvertStTime2Seconds(&(pTimerItem->stEndDate)) ;

            return _MApp_EpgTimer_IsTimePeriodOverlap(u32TimeChk_Start, u32TimeChk_End, u32TimeItem_Start, u32TimeItem_End);
        }
    }
    else
    {
        TIMER_OVERLAP_DEG(printf("Recorder overlap error.\n"));
    }

    return FALSE;
}
#endif
/***************************************************************************************/
BOOLEAN _MApp_EpgTimer_IsStartTimeOverlap(MS_EPG_TIMER *pTimerChk , MS_EPG_TIMER *pTimerItem)
{
    TIMER_OVERLAP_DEG(printf("_MApp_EpgTimer_IsStartTimeOverlap()\n"));
    TIMER_OVERLAP_DEG(printf("Check[%u/%u/%u]:",pTimerChk->stStartDate.u16Year, pTimerChk->stStartDate.u8Month,pTimerChk->stStartDate.u8Day));
    TIMER_OVERLAP_DEG(printf("[%u:%u][Repeat:%u]\n",pTimerChk->stStartDate.u8Hour, pTimerChk->stStartDate.u8Min, pTimerChk->enRepeatMode));
    TIMER_OVERLAP_DEG(printf("Item[%u/%u/%u]:",pTimerItem->stStartDate.u16Year, pTimerItem->stStartDate.u8Month,pTimerItem->stStartDate.u8Day));
    TIMER_OVERLAP_DEG(printf("[%u:%u][Repeat:%u]\n",pTimerItem->stStartDate.u8Hour, pTimerItem->stStartDate.u8Min, pTimerItem->enRepeatMode));

    if(pTimerChk->stStartDate.u8Hour == pTimerItem->stStartDate.u8Hour
        && pTimerChk->stStartDate.u8Min == pTimerItem->stStartDate.u8Min)
    {
        if(((EN_EPGRM_WEEKLY == pTimerChk->enRepeatMode || EN_EPGRM_WEEKLY == pTimerItem->enRepeatMode)
                    && EN_EPGRM_DAILY != pTimerChk->enRepeatMode
                    && EN_EPGRM_DAILY != pTimerItem->enRepeatMode)
            &&(MApp_GetDayOfWeek(pTimerChk->stStartDate.u16Year, pTimerChk->stStartDate.u8Month, pTimerChk->stStartDate.u8Day)
                    != MApp_GetDayOfWeek(pTimerItem->stStartDate.u16Year, pTimerItem->stStartDate.u8Month, pTimerItem->stStartDate.u8Day)))
        {
            TIMER_OVERLAP_DEG(printf("Pass daily/weekly\n"));
            return FALSE;
        }
        else if(((EN_EPGRM_ONCE == pTimerChk->enRepeatMode || EN_EPGRM_AUTO == pTimerChk->enRepeatMode)
            && (EN_EPGRM_ONCE == pTimerItem->enRepeatMode || EN_EPGRM_AUTO == pTimerItem->enRepeatMode))
            && (pTimerChk->stStartDate.u16Year != pTimerItem->stStartDate.u16Year
                        || pTimerChk->stStartDate.u8Month != pTimerItem->stStartDate.u8Month
                        || pTimerChk->stStartDate.u8Day != pTimerItem->stStartDate.u8Day) )
        {
            TIMER_OVERLAP_DEG(printf("Pass once\n"));
            return FALSE;
        }
        TIMER_OVERLAP_DEG(printf("Overlap!\n\n"));
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************************/
BOOLEAN _MApp_EpgTimer_IsTimerOverlap(MS_EPG_TIMER *pTimerChk , MS_EPG_TIMER *pTimerItem)
{
    if(EN_EPGUI_TIMER_REMINDER == pTimerChk->enTimerType && EN_EPGUI_TIMER_REMINDER == pTimerItem->enTimerType)
    {
        TIMER_OVERLAP_DEG(printf("Check Reminder-(Item)Reminder\n"));
        return _MApp_EpgTimer_IsStartTimeOverlap(pTimerChk, pTimerItem);
    }
#if ENABLE_PVR
    else if(EN_EPGUI_TIMER_RECORDER == pTimerChk->enTimerType && EN_EPGUI_TIMER_RECORDER == pTimerItem->enTimerType)
    {
        TIMER_OVERLAP_DEG(printf("Check Recorder-(Item)Recorder\n"));
        return(_MApp_EpgTimer_IsRecorderSettingOverlap(pTimerChk, pTimerItem));
    }
    /*Remain conditions:: Checking across different lists may confuse the user. Besides, these two actions does not conflict.
        else if((EN_EPGUI_TIMER_REMINDER == pTimerChk->enTimerType &&  EN_EPGUI_TIMER_RECORDER == pTimerItem->enTimerType)
                ||(EN_EPGUI_TIMER_RECORDER == pTimerChk->enTimerType && EN_EPGUI_TIMER_REMINDER == pTimerItem->enTimerType))
           return FALSE;
    */
#endif
    return FALSE;

}
#if ( (ENABLE_PVR) && (SUPPORT_PVR_CRID) )
/***************************************************************************************/
BOOLEAN _MApp_EpgTimer_GetValidAlternate()
{
    MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
    U16 srvPos = INVALID_SERVICE_ID;
    BOOLEAN bAlterOverlap = FALSE;
    U8 pPCN,idxItem;
    U16 pServiceID;
    U32 u32EventStart,u32EventEnd,u32PrvAddress;
    EventIndex TimerEventIdx,ItemEventIdx,pEvent;
    EventTime stEvtTime;
    m_pstAlterIdx = EPG_TIMER_InvalidIdx;

    if(msAPI_CM_GetServiceTypeAndPositionWithPCN(stEpgTimerParam.stEpgTimer.u8PCN, stEpgTimerParam.stEpgTimer.u16SrvID, &srvType, &srvPos) != TRUE)
    {
        return FALSE;
    }
    TimerEventIdx = MApp_EpgUI_Func_Get_CurFocusEvtIdx();
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
    if(msAPI_CM_GetServiceTypeAndPositionWithPCN(_pstEpgTimer[m_pstEpgidxItem].u8PCN, _pstEpgTimer[m_pstEpgidxItem].u16SrvID, &srvType, &srvPos) != TRUE)
    {
        _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        return FALSE;
    }
    if(MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType),srvPos,_pstEpgTimer[m_pstEpgidxItem].u16EventID,&ItemEventIdx) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
    {
        _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        return FALSE;
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    /*Check alternative programs when overlaping*/
    /*Check for timer overlap items*/
    if(MApp_Epg_IsEventAlternate(TimerEventIdx))
    {
        if(MApp_Epg_GetEventAlternate(TimerEventIdx,MW_EN_EPG_CRID_SEARCH_NEXT,&pPCN,&pServiceID,&pEvent) == MW_EN_EPG_FUNC_STATUS_SUCCESS && RfChkCounter == 0)
        {
            /*Update new event parameters*/
            if(MApp_Epg_GetEventID(pEvent, &(m_AlternateEpgTimer.stEpgTimer.u16EventID)) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            m_AlternateEpgTimer.stEpgTimer.u8PCN= pPCN;
            m_AlternateEpgTimer.stEpgTimer.u16SrvID = pServiceID;
            if(MApp_Epg_GetEventName(pEvent, m_AlternateEpgTimer.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            if(MApp_Epg_GetEventTime(pEvent, &stEvtTime) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            u32EventStart = stEvtTime.u32StartTime;
            u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
            MApp_ConvertSeconds2StTime(u32EventStart, &(m_AlternateEpgTimer.stEpgTimer.stStartDate));
            MApp_ConvertSeconds2StTime(u32EventEnd, &(m_AlternateEpgTimer.stEpgTimer.stEndDate));
            m_AlternateEpgTimer.stEpgTimer.bNoTitle = TRUE;
            m_AlternateEpgTimer.stEpgTimer.enTimerType = EN_EPGUI_TIMER_RECORDER;
            m_AlternateEpgTimer.stEpgTimer.enRepeatMode = stEpgTimerParam.stEpgTimer.enRepeatMode;
            m_AlternateEpgTimer.stEpgTimer.bRecordSplitEvent = stEpgTimerParam.stEpgTimer.bRecordSplitEvent;
            m_AlternateEpgTimer.stEpgTimer.bRecordSeriesEvent = stEpgTimerParam.stEpgTimer.bRecordSeriesEvent;
            m_AlternateEpgTimer.stEpgTimer.bRecordRecomEvent = stEpgTimerParam.stEpgTimer.bRecordRecomEvent;
            m_AlternateEpgTimer.stEpgTimer.satus = stEpgTimerParam.stEpgTimer.satus;

            u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
            for ( idxItem=0 ; idxItem<MApp_EpgUI_GetNumOfTimers() ; idxItem++ )
            {
                //skip check self item
                if(stEpgTimerParam.enMTSOURCE == EN_MT_SOURCE_TL_EDIT && stEpgTimerParam.u8CurTimerIdx == idxItem)
                {
                    continue;
                }
                /*Check if alternative programs overlap*/
                if(_MApp_EpgTimer_IsTimerOverlap(&m_AlternateEpgTimer.stEpgTimer, &_pstEpgTimer[idxItem]))
                {
                    bAlterOverlap = TRUE;
                }
                if((idxItem == MApp_EpgUI_GetNumOfTimers()-1)&&(bAlterOverlap == FALSE))
                {
                    m_pstAlterIdx = EPG_TIMER_Alternate;
                    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
                    return TRUE;
                }
            }
            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        }
        else if(MApp_Epg_GetEventAlternate(TimerEventIdx,MW_EN_EPG_CRID_SEARCH_PREV,&pPCN,&pServiceID,&pEvent) == MW_EN_EPG_FUNC_STATUS_SUCCESS && RfChkCounter == 0)
        {
            /*Update new event parameters*/
            if(MApp_Epg_GetEventID(pEvent, &(m_AlternateEpgTimer.stEpgTimer.u16EventID)) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            m_AlternateEpgTimer.stEpgTimer.u8PCN= pPCN;
            m_AlternateEpgTimer.stEpgTimer.u16SrvID = pServiceID;
            if(MApp_Epg_GetEventName(pEvent, m_AlternateEpgTimer.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            if(MApp_Epg_GetEventTime(pEvent, &stEvtTime) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            u32EventStart = stEvtTime.u32StartTime;
            u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
            MApp_ConvertSeconds2StTime(u32EventStart, &(m_AlternateEpgTimer.stEpgTimer.stStartDate));
            MApp_ConvertSeconds2StTime(u32EventEnd, &(m_AlternateEpgTimer.stEpgTimer.stEndDate));
            m_AlternateEpgTimer.stEpgTimer.bNoTitle = TRUE;
            m_AlternateEpgTimer.stEpgTimer.enTimerType = EN_EPGUI_TIMER_RECORDER;
            m_AlternateEpgTimer.stEpgTimer.enRepeatMode = stEpgTimerParam.stEpgTimer.enRepeatMode;
            m_AlternateEpgTimer.stEpgTimer.bRecordSplitEvent = stEpgTimerParam.stEpgTimer.bRecordSplitEvent;
            m_AlternateEpgTimer.stEpgTimer.bRecordSeriesEvent = stEpgTimerParam.stEpgTimer.bRecordSeriesEvent;
            m_AlternateEpgTimer.stEpgTimer.bRecordRecomEvent = stEpgTimerParam.stEpgTimer.bRecordRecomEvent;
            m_AlternateEpgTimer.stEpgTimer.satus = stEpgTimerParam.stEpgTimer.satus;

            u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
            for ( idxItem=0 ; idxItem<MApp_EpgUI_GetNumOfTimers() ; idxItem++ )
            {
                //skip check self item
                if(stEpgTimerParam.enMTSOURCE == EN_MT_SOURCE_TL_EDIT && stEpgTimerParam.u8CurTimerIdx == idxItem)
                {
                    continue;
                }

                if((_MApp_EpgTimer_IsTimerOverlap(&m_AlternateEpgTimer.stEpgTimer, &_pstEpgTimer[idxItem])) || u32EventStart <= MApp_GetLocalSystemTime())
                {
                    bAlterOverlap = TRUE;
                }
                if((idxItem == MApp_EpgUI_GetNumOfTimers()-1)&&(bAlterOverlap == FALSE))
                {
                    m_pstAlterIdx = EPG_TIMER_Alternate;
                    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
                    return TRUE;
                }
            }
            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        }
    }
    /*Check for recorder list overlap items*/
    if(MApp_Epg_IsEventAlternate(ItemEventIdx))
    {
        if(MApp_Epg_GetEventAlternate(ItemEventIdx,MW_EN_EPG_CRID_SEARCH_NEXT,&pPCN,&pServiceID,&pEvent) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
        {
            /*Update new event parameters*/
            if(MApp_Epg_GetEventID(pEvent, &(m_AlternateEpgTimer.stEpgTimer.u16EventID)) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            m_AlternateEpgTimer.stEpgTimer.u8PCN= pPCN;
            m_AlternateEpgTimer.stEpgTimer.u16SrvID = pServiceID;
            if(MApp_Epg_GetEventName(pEvent, m_AlternateEpgTimer.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            if(MApp_Epg_GetEventTime(pEvent, &stEvtTime) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            u32EventStart = stEvtTime.u32StartTime;
            u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
            MApp_ConvertSeconds2StTime(u32EventStart, &(m_AlternateEpgTimer.stEpgTimer.stStartDate));
            MApp_ConvertSeconds2StTime(u32EventEnd, &(m_AlternateEpgTimer.stEpgTimer.stEndDate));
            m_AlternateEpgTimer.stEpgTimer.bNoTitle = TRUE;
            m_AlternateEpgTimer.stEpgTimer.enTimerType = EN_EPGUI_TIMER_RECORDER;
            m_AlternateEpgTimer.stEpgTimer.enRepeatMode = stEpgTimerParam.stEpgTimer.enRepeatMode;
            m_AlternateEpgTimer.stEpgTimer.bRecordSplitEvent = stEpgTimerParam.stEpgTimer.bRecordSplitEvent;
            m_AlternateEpgTimer.stEpgTimer.bRecordSeriesEvent = stEpgTimerParam.stEpgTimer.bRecordSeriesEvent;
            m_AlternateEpgTimer.stEpgTimer.bRecordRecomEvent = stEpgTimerParam.stEpgTimer.bRecordRecomEvent;
            m_AlternateEpgTimer.stEpgTimer.satus = stEpgTimerParam.stEpgTimer.satus;

            u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
            for ( idxItem=0 ; idxItem<MApp_EpgUI_GetNumOfTimers() ; idxItem++ )
            {
                //skip check self item
                if(stEpgTimerParam.enMTSOURCE == EN_MT_SOURCE_TL_EDIT && stEpgTimerParam.u8CurTimerIdx == idxItem)
                {
                    continue;
                }

                if(_MApp_EpgTimer_IsTimerOverlap(&m_AlternateEpgTimer.stEpgTimer, &_pstEpgTimer[idxItem]))
                {
                    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
                    return FALSE;
                }
                if(idxItem == MApp_EpgUI_GetNumOfTimers()-1)
                {
                    m_pstAlterIdx = m_pstEpgidxItem;
                    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
                    return TRUE;
                }
            }
            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        }
        else if (MApp_Epg_GetEventAlternate(ItemEventIdx,MW_EN_EPG_CRID_SEARCH_PREV,&pPCN,&pServiceID,&pEvent) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
        {
            /*Update new event parameters*/
            if(MApp_Epg_GetEventID(pEvent, &(m_AlternateEpgTimer.stEpgTimer.u16EventID)) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            m_AlternateEpgTimer.stEpgTimer.u8PCN= pPCN;
            m_AlternateEpgTimer.stEpgTimer.u16SrvID = pServiceID;
            if(MApp_Epg_GetEventName(pEvent, m_AlternateEpgTimer.stEpgTimer.au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            if(MApp_Epg_GetEventTime(pEvent, &stEvtTime) != MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                return FALSE;
            }
            u32EventStart = stEvtTime.u32StartTime;
            u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
            MApp_ConvertSeconds2StTime(u32EventStart, &(m_AlternateEpgTimer.stEpgTimer.stStartDate));
            MApp_ConvertSeconds2StTime(u32EventEnd, &(m_AlternateEpgTimer.stEpgTimer.stEndDate));
            m_AlternateEpgTimer.stEpgTimer.bNoTitle = TRUE;
            m_AlternateEpgTimer.stEpgTimer.enTimerType = EN_EPGUI_TIMER_RECORDER;
            m_AlternateEpgTimer.stEpgTimer.enRepeatMode = stEpgTimerParam.stEpgTimer.enRepeatMode;
            m_AlternateEpgTimer.stEpgTimer.bRecordSplitEvent = stEpgTimerParam.stEpgTimer.bRecordSplitEvent;
            m_AlternateEpgTimer.stEpgTimer.bRecordSeriesEvent = stEpgTimerParam.stEpgTimer.bRecordSeriesEvent;
            m_AlternateEpgTimer.stEpgTimer.bRecordRecomEvent = stEpgTimerParam.stEpgTimer.bRecordRecomEvent;
            m_AlternateEpgTimer.stEpgTimer.satus = stEpgTimerParam.stEpgTimer.satus;

            u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
            for ( idxItem=0 ; idxItem<MApp_EpgUI_GetNumOfTimers() ; idxItem++ )
            {
                //skip check self item
                if(stEpgTimerParam.enMTSOURCE == EN_MT_SOURCE_TL_EDIT && stEpgTimerParam.u8CurTimerIdx == idxItem)
                {
                    continue;
                }

                if((_MApp_EpgTimer_IsTimerOverlap(&m_AlternateEpgTimer.stEpgTimer, &_pstEpgTimer[idxItem])) || u32EventStart <= MApp_GetLocalSystemTime())
                {
                    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
                    return FALSE;
                }
                if(idxItem == MApp_EpgUI_GetNumOfTimers()-1)
                {
                    m_pstAlterIdx = m_pstEpgidxItem;
                    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
                    return TRUE;
                }
            }
            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        }
    }
    return FALSE;
}
#endif
/*Overlap Check End*/
#if ENABLE_PVR
/***************************************************************************************/
MS_EPG_TIMER_PARAM MApp_Get_EPG_Timer_Alternate(void)
{
    return m_AlternateEpgTimer;
}

/***************************************************************************************/
MS_EPG_TIMER_PARAM MApp_Get_EPG_Timer_stEpgTimerParam(void)
{
    return stEpgTimerParam;
}

/***************************************************************************************/
S8 MApp_Get_EPG_Timer_pstAlternate_Index(void)
{
    return m_pstAlterIdx;
}
#endif
/***************************************************************************************/

MS_EPG_TIMER* MApp_Get_EPG_Timer_pstEpgTimer(void)
{
    return _pstEpgTimer;
}

/***************************************************************************************/

EN_EPG_TIMER_CHECK MApp_EpgTimer_IsTimerSettingValid( void )
#if 1
{
    EN_EPG_TIMER_CHECK enTimerCheck = EN_TIMER_CHECK_SUCCESS;
    ST_TIME stTime;
    U32 u32NewTimerStartTime;
    U8 idxItem;
    U32 u32PrvAddress;
#if ENABLE_PVR
    U32 u32NewTimerEndTime;
    m_pstEpgidxItem = EPG_TIMER_InvalidIdx;
#endif

    stTime = stEpgTimerParam.stEpgTimer.stStartDate;
    u32NewTimerStartTime = MApp_ConvertStTime2Seconds(&stTime) ;

    // [1] Check if start timer is past
    if ((
    #if ENABLE_CI_PLUS
        (EN_EPGUI_TIMER_CI_OP_REFRESH == stEpgTimerParam.stEpgTimer.enTimerType) ||
    #endif
        (EN_EPGUI_TIMER_REMINDER == stEpgTimerParam.stEpgTimer.enTimerType))
            && (EN_EPGRM_ONCE == stEpgTimerParam.stEpgTimer.enRepeatMode || EN_EPGRM_AUTO == stEpgTimerParam.stEpgTimer.enRepeatMode)
        && (u32NewTimerStartTime <= MApp_GetLocalSystemTime()) )
    {
        return EN_TIMER_CHECK_PAST;
    }

#if ENABLE_PVR
    // [2] Check end time
    stTime = stEpgTimerParam.stEpgTimer.stEndDate;
    u32NewTimerEndTime = MApp_ConvertStTime2Seconds(&stTime) ;

    if(EN_EPGUI_TIMER_RECORDER == stEpgTimerParam.stEpgTimer.enTimerType)
    {
            //(1.)Check if end time is past
        if(u32NewTimerEndTime <= MApp_GetLocalSystemTime())
        {
            return EN_TIMER_CHECK_PAST;
        }
            //(2.)check end time > start time
        else if(u32NewTimerStartTime >= u32NewTimerEndTime)
        {
            return EN_TIMER_CHECK_ENDTIME_BEFORE_START;
        }
            //(3.)check end time - start time < 24Hr when repeat daily
        else if((EN_EPGRM_DAILY == stEpgTimerParam.stEpgTimer.enRepeatMode)
                    && (u32NewTimerEndTime - u32NewTimerStartTime) >= SECONDS_PER_DAY)
        {
            return EN_TIMER_CHECK_ENDTIME_EXCEED_PERIOD;
        }
            //(4.)check end time - start time < 7Days when repeat weekly
        else if((EN_EPGRM_WEEKLY== stEpgTimerParam.stEpgTimer.enRepeatMode)
                    && (u32NewTimerEndTime - u32NewTimerStartTime) >= (7*SECONDS_PER_DAY))
        {
            return EN_TIMER_CHECK_ENDTIME_EXCEED_PERIOD;

        }
             //(5.)Check if start time is past
        else if((EN_EPGRM_ONCE == stEpgTimerParam.stEpgTimer.enRepeatMode)
                    && (u32NewTimerStartTime) < MApp_GetLocalSystemTime())
        {
            return EN_TIMER_CHECK_PAST;
        }
    }
#endif

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
#if ENABLE_PVR
    RfChkCounter = 0;
#endif
    // [3] Check if new timer is overlapping the existed timer list
    if ( MApp_EpgUI_GetNumOfTimers() > 0 )      // modify some condition and variable
    {
        for ( idxItem=0 ; idxItem<MApp_EpgUI_GetNumOfTimers() ; idxItem++ )
        {
            //skip check self item
            if(stEpgTimerParam.enMTSOURCE == EN_MT_SOURCE_TL_EDIT && stEpgTimerParam.u8CurTimerIdx == idxItem)
            {
                continue;
            }

            if(_MApp_EpgTimer_IsTimerOverlap(&stEpgTimerParam.stEpgTimer, &_pstEpgTimer[idxItem]))
            {
                enTimerCheck = EN_TIMER_CHECK_OVERLAY;
                #if ENABLE_PVR
                m_pstEpgidxItem = idxItem;
                #endif
                _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
                return enTimerCheck;
            }
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    return enTimerCheck;
}
#else
{
    EN_EPG_TIMER_CHECK enTimerCheck = EN_TIMER_CHECK_SUCCESS;
    ST_TIME _stTime;
    U32 u32NewTimerStartDate;
    #if ENABLE_PVR
    U32 u32NewTimerEndTime;
    #endif
    U8 u8i;
    EN_EPG_TIMER_REPEAT_MODE _RepeatMode;

    _stTime           = stEpgTimerParam.stEpgTimer.stStartDate;
    u32NewTimerStartDate = MApp_ConvertStTime2Seconds(&_stTime) ;

    // [1] Check if the timer is past
    if ((EN_EPGRM_ONCE == stEpgTimerParam.stEpgTimer.enRepeatMode) && (u32NewTimerStartDate <= MApp_GetLocalSystemTime()) )
    {
        enTimerCheck = EN_TIMER_CHECK_PAST;
        return enTimerCheck;
    }

    // [2] Check if the timer is existed in saved timers
    if ( MApp_EpgUI_GetNumOfTimers() > 0 )      // modify some condition and variable
    {
        for ( u8i=0 ; u8i<MApp_EpgUI_GetNumOfTimers() ; u8i++ )
        {
            if(stEpgTimerParam.enMTSOURCE == EN_MT_SOURCE_TL_EDIT && stEpgTimerParam.u8CurTimerIdx == u8i)
            {
                u8i++;
                if(u8i == MApp_EpgUI_GetNumOfTimers())
                {
                    return enTimerCheck;
                }
            }

            _stTime = _pstEpgTimer[u8i].stStartDate;
            _RepeatMode = _pstEpgTimer[u8i].enRepeatMode;
            if(stEpgTimerParam.stEpgTimer.stStartDate.u8Hour == _stTime.u8Hour
                && stEpgTimerParam.stEpgTimer.stStartDate.u8Min== _stTime.u8Min)
            {
                if(((EN_EPGRM_WEEKLY == stEpgTimerParam.stEpgTimer.enRepeatMode || EN_EPGRM_WEEKLY == _RepeatMode)
                            && EN_EPGRM_DAILY != stEpgTimerParam.stEpgTimer.enRepeatMode
                            && EN_EPGRM_DAILY != _RepeatMode)
                    &&(MApp_GetDayOfWeek(stEpgTimerParam.stEpgTimer.stStartDate.u16Year, stEpgTimerParam.stEpgTimer.stStartDate.u8Month, stEpgTimerParam.stEpgTimer.stStartDate.u8Day
                            != MApp_GetDayOfWeek(_stTime.u16Year, _stTime.u8Month, _stTime.u8Day))))
                {
                    continue;
                }

                if((EN_EPGRM_ONCE== stEpgTimerParam.stEpgTimer.enRepeatMode && EN_EPGRM_ONCE == _RepeatMode)
                    && (stEpgTimerParam.stEpgTimer.stStartDate.u16Year != _stTime.u16Year
                                || stEpgTimerParam.stEpgTimer.stStartDate.u8Month != _stTime.u8Month
                                || stEpgTimerParam.stEpgTimer.stStartDate.u8Day != _stTime.u8Day) )
                {
                    continue;
                }

                enTimerCheck = EN_TIMER_CHECK_OVERLAY;
                return enTimerCheck;
            }
        }
    }
    return enTimerCheck;
}
#endif

#if ENABLE_PVR
static BOOLEAN _MApp_EpgTimer_UpdateEventData(void)
{
    U8  idxTimerItem,i,j;
    U32 u32PrvAddress;
    BOOLEAN retval = FALSE;
    BOOLEAN TimerOffsetChanged;
    S32 TimerOffset;
    MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
    U16 srvPos = INVALID_SERVICE_ID;
    EventIndex pEventIdx;
    U16 EventChangedSvrID[EPG_TIMER_MAX_NUM];
    U8 EventChangedNum = 0;

    TimerOffset = msAPI_Timer_GetOffsetTime();
    if( s32SysTimerOffset == (S32)0xFFFFFFFF)
    {
        s32SysTimerOffset = TimerOffset;
        TimerOffsetChanged = FALSE;
    }
    else
    {
        if(s32SysTimerOffset == TimerOffset)
        {
            TimerOffsetChanged = FALSE;
        }
        else
        {
            s32SysTimerOffset = TimerOffset;
            TimerOffsetChanged = TRUE;
        }
    }
    i = MApp_EpgUI_GetNumOfTimers();

    if(i == 0)
        return FALSE;

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
    for(; i > 0; i--)
    {
        idxTimerItem = i - 1;
        if(_pstEpgTimer[idxTimerItem].enRepeatMode == EN_EPGRM_AUTO)
        {
            msAPI_CM_GetServiceTypeAndPositionWithPCN(_pstEpgTimer[idxTimerItem].u8PCN, _pstEpgTimer[idxTimerItem].u16SrvID, &srvType, &srvPos);

            if(TimerOffsetChanged)
            { //go on evnet change process
            }
            else if(MApp_Epg_IsEventInfoUpdated(msAPI_SI_ToSI_Service_Type(srvType), srvPos)) //event change
            {
                for(j=0;j<EventChangedNum;j++)
                {
                    if(EventChangedSvrID[j] == _pstEpgTimer[idxTimerItem].u16SrvID)
                        break;
                }
                if(j >= EventChangedNum)
                    EventChangedSvrID[EventChangedNum++] = _pstEpgTimer[idxTimerItem].u16SrvID;
                //go on evnet change process
            }
            else if(EventChangedNum>0)
            {
                for(j=0;j<EventChangedNum;j++)
                {
                    if(EventChangedSvrID[j] == _pstEpgTimer[idxTimerItem].u16SrvID)
                        break;
                }
                if(j >= EventChangedNum)
                    continue;
            }
            else
            {
                continue;
            }
            //go on evnet change process

            {
                if(MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType), srvPos, _pstEpgTimer[idxTimerItem].u16EventID, &pEventIdx) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                {
                    U32 u32EventStart, u32EventEnd;
                    EventTime stEvtTime;

                    MApp_Epg_GetEventTime(pEventIdx, &stEvtTime);
                    u32EventStart = stEvtTime.u32StartTime;
                    u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                    MApp_ConvertSeconds2StTime(u32EventStart, &(_pstEpgTimer[idxTimerItem].stStartDate));
                    MApp_ConvertSeconds2StTime(u32EventEnd, &(_pstEpgTimer[idxTimerItem].stEndDate));
                    retval = TRUE;
                    TIMER_DBG(("Event Changed,idxTimerItem=%u\n",idxTimerItem));
                }
            }
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);

    return retval;
}
#endif

void MApp_EpgTimer_ResetStopppedTimerListItem(U8 ItemIndex )
{
#if ENABLE_DVB

    ST_TIME _stTime;    //temp varible for time related calculation
    U32 u32ItemStartTime;
    U32 u32ItemEndTime;
    U8 u8ItemTotal;
    U32 u32PrvAddress;

    u8ItemTotal = MApp_EpgUI_GetNumOfTimers();

    TIMER_DBG(("ResetStopppedItem,ItemIndex=%d\n",ItemIndex));

    if(ItemIndex >= u8ItemTotal || u8ItemTotal ==0)
    {
        return;
    }
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

#if ENABLE_PVR //for DTR run away check
    if(_pstEpgTimer[ItemIndex].enTimerType == EN_EPGUI_TIMER_RECORDER)
    {
        U8 i;
        for(i=0;i<EPGTIMER_REC_QUEUE_NUMBER;i++)
        {
            if(m_u8EpgTimerRecQueue[i].u8TimerIndex == ItemIndex) //do not delete recording item
            {
                TIMER_DBG(("can't delete recording item\n"));
                _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
                return;
            }
        }
    }
#endif

    _stTime = _pstEpgTimer[ItemIndex].stStartDate;
    u32ItemStartTime = MApp_ConvertStTime2Seconds(&_stTime) ;

    switch(_pstEpgTimer[ItemIndex].enRepeatMode)
    {
        #if (SUPPORT_PVR_CRID)
        case EN_EPGRM_AUTO:
        {
            MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
            U16 srvPos = INVALID_SERVICE_ID;
            EventIndex CurEventIdx;

            msAPI_CM_GetServiceTypeAndPositionWithPCN(_pstEpgTimer[ItemIndex].u8PCN, _pstEpgTimer[ItemIndex].u16SrvID, &srvType, &srvPos);
            if(MApp_Epg_EventFindByID(msAPI_SI_ToSI_Service_Type(srvType), srvPos, _pstEpgTimer[ItemIndex].u16EventID, &CurEventIdx) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
            {
                U32 u32EventStart, u32EventEnd;
                EventTime stEvtTime;
                EventIndex NextEventIdx;
                U16        u16NextSrvID;
                U8         u8NextPCN;
                EventID    NextEventID;
                BOOLEAN    bChangeEvent = FALSE;

                //find Split event
                if(MApp_Epg_IsEventSplit(CurEventIdx) && _pstEpgTimer[ItemIndex].bRecordSplitEvent == TRUE)
                {
                    MApp_Epg_GetEventSplit(CurEventIdx, MW_EN_EPG_CRID_SEARCH_NEXT, &u8NextPCN, &u16NextSrvID, &NextEventIdx);
                    bChangeEvent = TRUE;
                }
                else if(MApp_Epg_IsEventSeries(CurEventIdx) && _pstEpgTimer[ItemIndex].bRecordSeriesEvent == TRUE)
                {
                    MApp_Epg_GetEventSeries(CurEventIdx, MW_EN_EPG_CRID_SEARCH_NEXT, &u8NextPCN, &u16NextSrvID, &NextEventIdx);
                    bChangeEvent = TRUE;
                }

                if(bChangeEvent == TRUE)
                {
                    MApp_Epg_GetEventID(NextEventIdx, &NextEventID);
                    //update event time
                    MApp_Epg_GetEventTime(NextEventIdx, &stEvtTime);
                    u32EventStart = stEvtTime.u32StartTime;
                    u32EventEnd   = stEvtTime.u32StartTime + stEvtTime.u32Duration;
                    MApp_ConvertSeconds2StTime(u32EventStart, &(_pstEpgTimer[ItemIndex].stStartDate));
                    MApp_ConvertSeconds2StTime(u32EventEnd, &(_pstEpgTimer[ItemIndex].stEndDate));
                    //update event anme
                    MApp_Epg_GetEventName(NextEventIdx, _pstEpgTimer[ItemIndex].au16EvtName, EPG_TIMER_MAX_EVT_NAME_LEN);
                    //update event ID
                    _pstEpgTimer[ItemIndex].u16EventID = NextEventID;
                    //update PCN
                    _pstEpgTimer[ItemIndex].u8PCN = u8NextPCN;
                    //update Service ID
                    _pstEpgTimer[ItemIndex].u16SrvID = u16NextSrvID;

                    TIMER_DBG(("Event Changed to Split\n"));
                    break;
                }
            }
        }
        #endif
        // go on erase item
        case EN_EPGRM_ONCE:
        {//erase
            U8 curLastValid = u8ItemTotal - 1;
            _pstEpgTimer[ItemIndex] = _pstEpgTimer[curLastValid];
            memset(&_pstEpgTimer[curLastValid], 0x00, sizeof(MS_EPG_TIMER) );
            _pstEpgTimer[curLastValid].enTimerType = EN_EPGUI_TIMER_NULL;

            TIMER_DBG(("Delete Item=%d\n",ItemIndex));
        #if ENABLE_PVR
            {
                U8 idx;
                for(idx=0;idx<EPGTIMER_REC_QUEUE_NUMBER;idx++)
                {
                    if(m_u8EpgTimerRecQueue[idx].u8TimerIndex == ItemIndex)
                    {
                        m_u8EpgTimerRecQueue[idx].u8TimerIndex = EPGTIMER_INDEX_NULL;//item deleted
                        TIMER_DBG(("m_u8EpgTimerRecQueue[%d].u8TimerIndex = %d\n",idx,m_u8EpgTimerRecQueue[idx].u8TimerIndex));
                    }
                    else if(m_u8EpgTimerRecQueue[idx].u8TimerIndex == curLastValid)
                    {
                        m_u8EpgTimerRecQueue[idx].u8TimerIndex = ItemIndex;
                        TIMER_DBG(("m_u8EpgTimerRecQueue[%d].u8TimerIndex = %d\n",idx,m_u8EpgTimerRecQueue[idx].u8TimerIndex));
                    }
                }
            }
        #endif
            if(m_u8EpgNextStartUpIdx == ItemIndex)
            {
                m_u8EpgNextStartUpIdx = EPGTIMER_INDEX_NULL; //item deleted
                TIMER_DBG(("m_u8EpgNextStartUpIdx=%d\n", m_u8EpgNextStartUpIdx));
            }
            else if(m_u8EpgNextStartUpIdx == curLastValid)
            {
                m_u8EpgNextStartUpIdx = ItemIndex;
                TIMER_DBG(("m_u8EpgNextStartUpIdx=%d\n", m_u8EpgNextStartUpIdx));
            }

            if(m_u8EpgStartingIdx == ItemIndex)
            {
                m_u8EpgStartingIdx = EPGTIMER_INDEX_NULL; //item deleted
                TIMER_DBG(("m_u8EpgStartingIdx=%d\n", EPGTIMER_INDEX_NULL));
            }
            else if(m_u8EpgStartingIdx == curLastValid)
            {
                m_u8EpgStartingIdx = ItemIndex;
                TIMER_DBG(("m_u8EpgStartingIdx=%d\n", m_u8EpgStartingIdx));
            }
        }
        break;

        case EN_EPGRM_DAILY:
        case EN_EPGRM_WEEKLY:
        {//reset to next
            U32 u32CurTime =MApp_GetLocalSystemTime();

            if (u32CurTime <= u32ItemStartTime && !MApp_ZUI_API_IsSuccessor(HWND_EPG_COUNTDOWN_PANE, MApp_ZUI_API_GetFocus()))
            {
                break;
            }

            _stTime = _pstEpgTimer[ItemIndex].stEndDate;
            if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day== 0))
            {
                ASSERT(0);
            }
            u32ItemEndTime = MApp_ConvertStTime2Seconds(&_stTime) ;
            if (EN_EPGRM_DAILY == _pstEpgTimer[ItemIndex].enRepeatMode)
            {
                // The purpose of usage of while loop, because current time must bigger than ItemStartTime
                do
                {
                     u32ItemStartTime += SECONDS_PER_DAY;
                     u32ItemEndTime   += SECONDS_PER_DAY;
                }while (u32CurTime> u32ItemStartTime);
            }
            else if (EN_EPGRM_WEEKLY == _pstEpgTimer[ItemIndex].enRepeatMode)
            {
                // To fix Mantis 0905462
                // The purpose of usage of while loop, because current time must bigger than ItemStartTime
                do
                {
                     u32ItemStartTime += (SECONDS_PER_DAY*7);
                     u32ItemEndTime   += (SECONDS_PER_DAY*7);
                }while (u32CurTime> u32ItemStartTime);
            }

            MApp_ConvertSeconds2StTime(u32ItemStartTime, &_stTime);
            _pstEpgTimer[ItemIndex].stStartDate  = _stTime;
            MApp_ConvertSeconds2StTime(u32ItemEndTime, &_stTime);
            _pstEpgTimer[ItemIndex].stEndDate    = _stTime;
            TIMER_DBG(("Item Reset\n"));

        }
        break;

        default:
            ASSERT(0);
            break;
    }

    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
#endif
}

static void _MApp_EpgTimer_DelPastTimeItems(U32 u32TimeActing )
{
    ST_TIME _stTime;
    U32 u32ItemStartDate;
    U32 u32ItemEndDate;
    S8  idxTimerItem;
    U32 u32PrvAddress;
    U8 i;

    TIMER_DBG(("_MApp_EpgTimer_DelPastTimeItems()\n"));
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    i = MApp_EpgUI_GetNumOfTimers();
    if(i == 0)
        return;

    for(; i > 0; i--)
    {
        idxTimerItem = i-1;
          //if past, move last item to current
        _stTime = _pstEpgTimer[idxTimerItem].stStartDate;
        if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day== 0))
        {
            continue;
        }
                u32ItemStartDate = MApp_ConvertStTime2Seconds(&_stTime) ;

        _stTime = _pstEpgTimer[idxTimerItem].stEndDate;
        if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day== 0))
        {
            continue;
        }
        u32ItemEndDate = MApp_ConvertStTime2Seconds(&_stTime) ;

        if((EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[idxTimerItem].enTimerType) && (u32ItemStartDate > u32TimeActing))
        {
            continue;
        }
    #if ENABLE_CI_PLUS
        else if((EN_EPGUI_TIMER_CI_OP_REFRESH == _pstEpgTimer[idxTimerItem].enTimerType) && (u32ItemStartDate + EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s > u32TimeActing) )
        {
            continue;
        }
    #endif
    #if ENABLE_PVR
        else if((EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[idxTimerItem].enTimerType) && (u32ItemEndDate > u32TimeActing))
        {
            continue;
        }
    #endif//ENABLE_PVR

        MApp_EpgTimer_ResetStopppedTimerListItem(idxTimerItem);
    }

    _MApp_EpgTimer_ClearGlobalVar();
    _MApp_EpgTimer_SaveTimerList(FALSE);
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
}

void MApp_EpgTimer_DelPastTimeAndNoDeviceCurItems(U32 u32TimeActing )
{
    ST_TIME _stTime;
    U32 u32ItemStartDate;
    U32 u32ItemEndDate;
    S8  idxTimerItem;
    U8 i;

    i = MApp_EpgUI_GetNumOfTimers();
    if(i == 0)
        return;

    for(; i > 0; i--)
    {
        idxTimerItem = i-1;
        _stTime = _pstEpgTimer[idxTimerItem].stStartDate;
        if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day== 0))
        {
            continue;
        }
        u32ItemStartDate = MApp_ConvertStTime2Seconds(&_stTime) ;

        _stTime = _pstEpgTimer[idxTimerItem].stEndDate;
        if ((_stTime.u16Year == 0) && (_stTime.u8Month == 0) && (_stTime.u8Day== 0))
        {
            continue;
        }
        u32ItemEndDate = MApp_ConvertStTime2Seconds(&_stTime) ;

        if((EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[idxTimerItem].enTimerType) && (u32ItemStartDate > u32TimeActing))
        {
            continue;
        }
    #if ENABLE_CI_PLUS
        else if((EN_EPGUI_TIMER_CI_OP_REFRESH == _pstEpgTimer[idxTimerItem].enTimerType) && (u32ItemStartDate + EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s > u32TimeActing) )
        {
            continue;
        }
    #endif
    #if ENABLE_PVR
        else if((EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[idxTimerItem].enTimerType) && (u32ItemStartDate > u32TimeActing))
        {
            continue;
        }
    #endif//ENABLE_PVR
        MApp_EpgTimer_DelCurTimerListItem(idxTimerItem);

    }
}


/******************************************************************************/
//for UI display sequence
static void _MApp_EpgTimer_SortTimerList(void)
{
    MS_EPG_TIMER temp;
    ST_TIME _stTime;
    U32 u32CurrentTimerStartDate, u32NextTimerStartDate;
    U8  i;
    U8  j;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    // Boundary Check
    if ( MApp_EpgTimer_GetEmptyTimerIdx() == 0 )
    {
        _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        return;
    }

    for(i= 0 ; i < MApp_EpgTimer_GetEmptyTimerIdx()-1 ; i++)
    {
        for(j = i+1 ; j < MApp_EpgTimer_GetEmptyTimerIdx() ; j++)
        {
            _stTime  = _pstEpgTimer[i].stStartDate;
            if ((_stTime.u16Year == 0) && (_stTime.u8Day == 0) && (_stTime.u8Hour == 0))
            {
                return;
            }

            u32CurrentTimerStartDate = MApp_ConvertStTime2Seconds(&_stTime) ;
            _stTime  = _pstEpgTimer[j].stStartDate;
            if ((_stTime.u16Year == 0) && (_stTime.u8Day == 0) && (_stTime.u8Hour == 0))
            {
                return;
            }

            u32NextTimerStartDate = MApp_ConvertStTime2Seconds(&_stTime) ;

            if((_pstEpgTimer[i].enRepeatMode < _pstEpgTimer[j].enRepeatMode)                    //EN_EPGRM_WEEKLY -> DAILY -> ONCE
                ||(_pstEpgTimer[i].enRepeatMode == _pstEpgTimer[j].enRepeatMode
                        && u32CurrentTimerStartDate > u32NextTimerStartDate))
            {
                temp = _pstEpgTimer[j];
                _pstEpgTimer[j] = _pstEpgTimer[i];
                _pstEpgTimer[i] = temp;

            #if ENABLE_PVR
                //update recording Queue
                {
                    U8 idx;
                    for(idx=0;idx<EPGTIMER_REC_QUEUE_NUMBER;idx++)
                    {
                        if(m_u8EpgTimerRecQueue[idx].u8TimerIndex == i)
                            m_u8EpgTimerRecQueue[idx].u8TimerIndex = j;
                        else if(m_u8EpgTimerRecQueue[idx].u8TimerIndex == j)
                            m_u8EpgTimerRecQueue[idx].u8TimerIndex = i;
                    }
                }
            #endif
                //update record index
                if(m_u8EpgNextStartUpIdx == i)
                {
                    m_u8EpgNextStartUpIdx = j;
                    TIMER_DBG(("m_u8EpgNextStartUpIdx=%d\n",m_u8EpgNextStartUpIdx));
                }
                else if(m_u8EpgNextStartUpIdx == j)
                {
                    m_u8EpgNextStartUpIdx = i;
                    TIMER_DBG(("m_u8EpgNextStartUpIdx=%d\n",m_u8EpgNextStartUpIdx));
                }

                if(m_u8EpgStartingIdx == i)
                {
                    m_u8EpgStartingIdx = j;
                    TIMER_DBG(("m_u8EpgStartingIdx=%d\n",m_u8EpgStartingIdx));
                }
                else if(m_u8EpgStartingIdx == j)
                {
                    m_u8EpgStartingIdx = i;
                    TIMER_DBG(("m_u8EpgStartingIdx=%d\n",m_u8EpgStartingIdx));
                }

                //update recording schedule list
                if(m_u8EpgNextStartUpIdx == i)
                    m_u8EpgNextStartUpIdx = j;
                else if(m_u8EpgNextStartUpIdx == j)
                    m_u8EpgNextStartUpIdx = i;
            }
        }
    }

    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
}

/******************************************************************************/
EN_EPG_TIMER_CHECK MApp_EpgTimer_SaveTimerSetting( void )
{
    EN_EPG_TIMER_CHECK enTimerCheck;
    U8 CurIdx = 0;

    enTimerCheck = MApp_EpgTimer_IsTimerSettingValid();
    if ( enTimerCheck == EN_TIMER_CHECK_SUCCESS )
    {
        switch ( stEpgTimerParam.enMTSOURCE )
        {
            case EN_MT_SOURCE_SCHED:
            case EN_MT_SOURCE_TL_NEW:
            {
                CurIdx = MApp_EpgTimer_GetEmptyTimerIdx();
                if(CurIdx >=EPG_TIMER_MAX_NUM)
                     return EN_TIMER_CHECK_FULL;

                stEpgTimerParam.stEpgTimer.u8UiSrcType = MApp_InputSrc_Get_UiInputSrcType();
                _pstEpgTimer[CurIdx] = stEpgTimerParam.stEpgTimer;
                MApp_EpgUI_SetTimerListCurIdx(0);

                TIMER_DBG(("MApp_EpgTimer_SaveTimerSetting()>> [enTimerItem = %u][u8PCN = %u][u16EventID = %u][u8Month=%u, u8Day=%u, u8Hour=%u, u8Min=%u]\n",
                  CurIdx, stEpgTimerParam.stEpgTimer.u8PCN, stEpgTimerParam.stEpgTimer.u16EventID,
                  stEpgTimerParam.stEpgTimer.stStartDate.u8Month, stEpgTimerParam.stEpgTimer.stStartDate.u8Day, stEpgTimerParam.stEpgTimer.stStartDate.u8Hour, stEpgTimerParam.stEpgTimer.stStartDate.u8Min));
            }
                break;

            case EN_MT_SOURCE_TL_EDIT:
            {
                CurIdx = stEpgTimerParam.u8CurTimerIdx;
                _pstEpgTimer[CurIdx] = stEpgTimerParam.stEpgTimer;
            }
                break;
        }

   #if 1//(ENABLE_S2_EPG_REMINDER)
      #if 1 // Refine at 20150908
        _pstEpgTimer->u8UiSrcType = MApp_InputSrc_Get_UiInputSrcType();
      #else
        if(IsS2InUse())
        {
            _pstEpgTimer[CurIdx].u8SrcIsDtvS2 = 1;
        }
        else
        {
            _pstEpgTimer[CurIdx].u8SrcIsDtvS2 = 0;
        }
      #endif
   #endif

        MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
    }

    return enTimerCheck;
}

/******************************************************************************/
BOOLEAN MApp_EpgTimer_CheckExceedLastItem( void )
{
    U8 totalTimerListIdx;
    U8 validItemCount = 0;
    U32 u32PrvAddress;

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
    for (totalTimerListIdx=0; totalTimerListIdx<EPG_TIMER_MAX_NUM; totalTimerListIdx++)
    {
        if(_pstEpgTimer[totalTimerListIdx].enTimerType == EN_EPGUI_TIMER_NULL
            || _pstEpgTimer[totalTimerListIdx].enTimerType >= EN_EPGUI_TIMER_INVALID)
        {
            break;
        }
#if ENABLE_PVR
        if((MApp_ZUI_API_IsWindowVisible(HWND_EPG_SCHEDULE_LIST_PANEL) && EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
           ||(MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_SCHEDULE_LIST_PANEL) && EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[totalTimerListIdx].enTimerType))
#else
        if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL) && EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
#endif
        {
            validItemCount++;
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
/*
    if(validItemCount > g_u8MenuMainItemIndex)
    {
        return TRUE;
    }
*/
    return FALSE;
}

/******************************************************************************/
void MApp_EpgTimer_DelCurTimerListItem( U8 u8Idx  )
#if 0
{
    U8 totalTimerListIdx;
    BOOLEAN isDelItemFound = FALSE;
    U8 curItemIdx = 0;
    U8 totalTimers = MApp_EpgUI_GetNumOfTimers();
    U32 u32PrvAddress;

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
    for (totalTimerListIdx=0; totalTimerListIdx<totalTimers; totalTimerListIdx++)
    {
#if ENABLE_PVR
        if((MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL) && EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
           ||(MApp_ZUI_API_IsWindowVisible(HWND_EPG_RECORDER_PANEL) && EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[totalTimerListIdx].enTimerType))
#else
        if (MApp_ZUI_API_IsWindowVisible(HWND_EPG_REMINDER_PANEL) && EN_EPGUI_TIMER_REMINDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
#endif
        {
            if(curItemIdx == g_u8MenuMainItemIndex + g_TimerList_CurPageStartItem)
            {
                isDelItemFound = TRUE;
                break;
            }
            curItemIdx++;
        }
    }

    if(!isDelItemFound)
    {
        _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        return;
    }

    for(;totalTimerListIdx<totalTimers; totalTimerListIdx++)
    {
        memset(&_pstEpgTimer[totalTimerListIdx], 0x00, sizeof(MS_EPG_TIMER) );
        _pstEpgTimer[totalTimerListIdx].enTimerType = EN_EPGUI_TIMER_NULL;    //add to initial timer type as invalid

        if ( totalTimerListIdx < (totalTimers-1) )
        {
            _pstEpgTimer[totalTimerListIdx] = _pstEpgTimer[totalTimerListIdx+1];
        }
    }

    _MApp_EpgTimer_SaveTimerList(TRUE);
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);

    //Resetting list index
    {
        U8 totalListItems = MApp_EpgTimer_GetTimerListItemsTotal(EN_EPGUI_TIMER_RECORDER);
        if(totalListItems == 0)
        {
            return;
        }

        if(g_u8MenuMainItemIndex + g_TimerList_CurPageStartItem >= totalListItems)
        {//exceed last item
            if(g_u8MenuMainItemIndex == 0)
            {
                g_TimerList_CurPageStartItem--;
                g_u8MenuMainItemIndex = EPG_TIMER_LIST_ITEMS_PER_PAGE - 1;
            }
            else
            {
                g_u8MenuMainItemIndex--;
            }
        }
    }
}
#else
{
    U8 u8TimerIdx;
    U8 u8NumOfTimers = MApp_EpgUI_GetNumOfTimers();
    U32 u32PrvAddress;

    if ( u8NumOfTimers < 1 )
    {
        return;
    }

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    // Del timer from arrayDB
    for ( u8TimerIdx = u8Idx ; u8TimerIdx<u8NumOfTimers ; u8TimerIdx++ )
    {
        memset(&_pstEpgTimer[u8TimerIdx], 0x00, sizeof(MS_EPG_TIMER) );
        _pstEpgTimer[u8TimerIdx].enTimerType = EN_EPGUI_TIMER_NULL;    //add to initial timer type as invalid

        if ( u8TimerIdx < (u8NumOfTimers-1) )
        {
            _pstEpgTimer[u8TimerIdx] = _pstEpgTimer[u8TimerIdx+1];
        }
    }

    // Reset timer index
    MApp_EpgUI_SetTimerListCurIdx(0);
//    g_u8PrevMenuMainItemIndex = g_u8MenuMainItemIndex = 0;

    _MApp_EpgTimer_SaveTimerList(TRUE);

    m_u32EpgNextStartUpTime = 0;
    m_u8EpgNextStartUpIdx = EPGTIMER_INDEX_NULL;

    //Resetting list index
    {
        U8 totalListItems = MApp_EpgTimer_GetTimerListItemsTotal(EN_EPGUI_TIMER_RECORDER);
        if(totalListItems == 0)
        {
            return;
        }
        if(g_u8MenuMainItemIndex + g_TimerList_CurPageStartItem >= totalListItems)
        {//exceed last item
            if(g_u8MenuMainItemIndex == 0)
            {
                g_TimerList_CurPageStartItem = 0;
                g_u8MenuMainItemIndex = EPG_TIMER_LIST_ITEMS_PER_PAGE - 1;
            }
            else
            {
                g_u8MenuMainItemIndex--;
            }
        }
    }

    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
}
#endif
/******************************************************************************/
void MApp_EpgTimer_LoadManualTimer( EN_EPGUI_TIMER_TYPE enTimerType )
{
#if ENABLE_DVB

    U16 EvnIdx;
    memset(&(stEpgTimerParam.stEpgTimer), 0x00, sizeof(stEpgTimerParam.stEpgTimer));

    switch ( stEpgTimerParam.enMTSOURCE )
    {
        case EN_MT_SOURCE_SCHED:
            TIMER_DBG(("Load Timer Setting>> from EIT . . .\n"));

            MApp_EpgTimer_SetTimerAsNew();

            EvnIdx = MApp_EpgUI_Func_Get_CurFocusEvtIdx();
            if ( EvnIdx < MW_MAX_NUM_OF_EVENT_IN_EPGDB)
            {
                MApp_Epg_GetEventID(EvnIdx, &(stEpgTimerParam.stEpgTimer.u16EventID));
                MApp_EpgTimer_SetTimerDate(EN_MT_DATE_EVENT);
                _MApp_EpgTimer_SetTimerEventName(EN_MT_DATE_EVENT);
                stEpgTimerParam.stEpgTimer.bNoTitle = TRUE;
            }
            break;

        case EN_MT_SOURCE_TL_EDIT:
            TIMER_DBG(("Load Timer Setting>> from TimerList KEY_EDIT, u8CurTimerIdx = %u\n", stEpgTimerParam.u8CurTimerIdx));

            stEpgTimerParam.stEpgTimer = _pstEpgTimer[stEpgTimerParam.u8CurTimerIdx];
            break;

        case EN_MT_SOURCE_TL_NEW:
            TIMER_DBG(("Load Timer Setting>> from TimerList KEY_NEW . . .\n"));
            MApp_EpgTimer_SetTimerAsNew();
            break;
    }
    stEpgTimerParam.stEpgTimer.enTimerType = enTimerType;
    if((enTimerType == EN_EPGUI_TIMER_REMINDER)
    #if (SUPPORT_PVR_CRID == DISABLE)
        || (enTimerType == EN_EPGUI_TIMER_RECORDER)
    #endif
    )
    {
        stEpgTimerParam.stEpgTimer.enRepeatMode = EN_EPGRM_ONCE;
    }
    TIMER_DBG(("stEpgTimerParam>> [enTimerType = %u][u8PCN = %u][u16EventID = %u][u8Month=%u, u8Day=%u, u8Hour=%u, u8Min=%u]\n",
     stEpgTimerParam.stEpgTimer.enTimerType, stEpgTimerParam.stEpgTimer.u8PCN, stEpgTimerParam.stEpgTimer.u16EventID,
     stEpgTimerParam.stEpgTimer.stStartDate.u8Month, stEpgTimerParam.stEpgTimer.stStartDate.u8Day, stEpgTimerParam.stEpgTimer.stStartDate.u8Hour, stEpgTimerParam.stEpgTimer.stStartDate.u8Min));
#endif
}


/******************************************************************************/
BOOLEAN MApp_EpgTimer_IsPrInTimerList( MEMBER_SERVICETYPE enServiceType, U16 u16ServicePosition )
{
    U8 u8LoopIdx;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    for ( u8LoopIdx=0 ; u8LoopIdx<MApp_EpgUI_GetNumOfTimers() ; u8LoopIdx++ )
    {
        MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
        U16 srvPos = INVALID_SERVICE_ID;

        msAPI_CM_GetServiceTypeAndPositionWithPCN(_pstEpgTimer[u8LoopIdx].u8PCN, _pstEpgTimer[u8LoopIdx].u16SrvID, &srvType, &srvPos);
        if (  (enServiceType == srvType) && (u16ServicePosition == srvPos) )
        {
            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
            return TRUE;
        }
    }

    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    return FALSE;
}

/******************************************************************************/
static void _MApp_EpgTimer_CountDownNotify(void)
{
#if(EPG_TIMER_TIMEUP_MSG_STYLE == STYLE_EPG_TIMEUP_MSG_COUNTDOWN)
     u8KeyCode  =  KEY_EPGTIMER_COUNTDOWN;
#elif(EPG_TIMER_TIMEUP_MSG_STYLE == STYLE_EPG_TIMEUP_MSG_NONE)
    return;
#endif
        }

/******************************************************************************/
void MApp_EpgTimer_ManualTimerMonitor(void)
{
    static BOOLEAN isTimerInitiatedOnce = FALSE;
    U32 u32TimeCurrent;
#if (ENABLE_CI_PLUS) // in op refersh menu key to yes, "op search start" msg show in HTT console in 12:12:00 on time precise.
    if(m_u32EpgNextStartUpTime_Temp_Flag == TRUE)
    {
        u32TimeCurrent = MApp_GetLocalSystemTime();
        if(u32TimeCurrent >= (m_u32EpgNextStartUpTime_Temp - 2))
        {
            m_u32EpgNextStartUpTime_Temp_Flag = FALSE;
            m_u32EpgNextStartUpTime_Temp = 0;
            MApp_CI_SendCiOpSearchStart();
        }
    }

#endif

    if(isTimerInitiatedOnce == FALSE)
    {
        if(MApp_UiMenuFunc_IsSystemClockSet())
        {
            MApp_EpgTimer_ManualTimer_Init();
            isTimerInitiatedOnce = TRUE;
        }
        return;
    }

    //Monitor timer
    if (msAPI_Timer_DiffTimeFromNow(m_dwEPGManualTimerMonitorTimer) < MANUAL_TIMER_MONITOR_INTERVAL)
    {
        return;
    }
    m_dwEPGManualTimerMonitorTimer = msAPI_Timer_GetTime0();

    //Check acting EPG timer
    u32TimeCurrent = MApp_GetLocalSystemTime();

#if (ENABLE_PVR)
    //check USB status

    if(g_PVRCheckFSStatus == EN_PVR_CHKSTS_CHECK_FORMAT
        || g_PVRCheckFSStatus == EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PASS)
    {
        return;
    }

    if(g_PVR_RecordStatus == E_PVR_RECORDER_TIMEUP
        || g_PVR_RecordStatus == E_PVR_RECORDER_TIMEUP_TO_REC)
    {
        return;
    }
    else
    {
        if(u32TimeCurrent <= u32LatestManualTimerStartDate)//for avoid leading time issue
        {
            return;
        }
        else  //the leading time pass, renew PVR attribute
        {
            if(u32LatestManualTimerStartDate != 0)
            {
                if(g_PVR_RecordStatus == E_PVR_RECORDER_IDLE)
                {
                    u32LatestManualTimerStartDate = 0;
                }
                else if(u32TimeCurrent >= u32LatestManualTimerStartDate+50) //waiting EIT change
                {
                #if(ENABLE_PVR_BROWSER)
                    MApp_UiPvr_Browser_UpdateRecordingAttr();
                #endif
                    u32LatestManualTimerStartDate = 0;
                }
            }
        }
        if(_MApp_EpgTimer_UpdateEventData())
        {
            MApp_EpgTimer_ReconfigTimerFromList(u32TimeCurrent);
        }
    }
#endif

#if ENABLE_PVR
    //check if recording arrival end time
    MApp_EpgTimer_CheckRecordEndTime(u32TimeCurrent);
#endif

    if (m_u8EpgNextStartUpIdx == EPGTIMER_INDEX_NULL)
    {
        return;
    }
if(EN_EPGTIMER_ACT_REMINDER != _TimerActType)
{
  #if ENABLE_PVR
      if (u32TimeCurrent < (m_u32EpgNextStartUpTime - EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s - EPG_RECORDER_PVR_LEADING_TIME_s))
  #else
      if (u32TimeCurrent < (m_u32EpgNextStartUpTime - EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s))
  #endif
      {
          return;
      }
}
    //Count down: from (m_u32EpgNextStartUpTime - EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s) to m_u32EpgNextStartUpTime
    if(EN_EPGTIMER_ACT_REMINDER == _TimerActType)
    {
        /*set reminder time to one minute*/
        if(u32TimeCurrent < (m_u32EpgNextStartUpTime - EPG_REMINDER_TIME))
        {
            return;
        }

        /*show count down osd one minute ago*/
        if(u32TimeCurrent < (m_u32EpgNextStartUpTime - EPG_REMINDER_TIME+EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s))
        {
           _MApp_EpgTimer_CountDownNotify();
            return;
        }
        //not arrival yet
        if(u32TimeCurrent < (m_u32EpgNextStartUpTime - EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s))
        {
            MApp_ZUI_UpdateEpgCountDownOsd();
            return;
        }

        //count down
        if(u32TimeCurrent < m_u32EpgNextStartUpTime)
        {
           _MApp_EpgTimer_CountDownNotify();
           return;
        }
    }
#if (ENABLE_CI_PLUS)
    else if(EN_EPGTIMER_ACT_CI_OP_REFRESH == _TimerActType)
    {
        //not arrival yet
        if(u32TimeCurrent < (m_u32EpgNextStartUpTime - EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s))
        {
            return;
        }

        //count down till EPG_RECORDER_PVR_LEADING_TIME_s
        if(u32TimeCurrent < m_u32EpgNextStartUpTime)
        {
            if(msAPI_CI_CardDetect())
            {
                MApp_ZUI_ACT_OPRefreshQueryUI();
                MApp_EpgTimer_DelCurTimerListItem(m_u8EpgNextStartUpIdx);
                MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
            }
            else
            {
                printf("No CI card, cancel OP Refresh!!!\n");
            }
            return;
        }
    }
#endif
#if ENABLE_PVR
    else if(EN_EPGTIMER_ACT_RECORDER_START == _TimerActType)
    {
        //not arrival yet
        if(u32TimeCurrent < (m_u32EpgNextStartUpTime - EPG_TIMEUP_COUNTDOWN_LEADING_TIME_s - EPG_RECORDER_PVR_LEADING_TIME_s))
        {
            return;
        }

        //count down till EPG_RECORDER_PVR_LEADING_TIME_s
        if(u32TimeCurrent < (m_u32EpgNextStartUpTime - EPG_RECORDER_PVR_LEADING_TIME_s))
        {
            _MApp_EpgTimer_CountDownNotify();
            return;
        }
    }

#endif

    //(4.)Time up action
    MApp_ZUI_ACT_ShutdownOSD();
    //printf("Time up action\n");
#if ENABLE_PVR
    if(EN_EPGTIMER_ACT_RECORDER_START == _TimerActType)
    {
        u32TimeCurrent += EPG_RECORDER_PVR_LEADING_TIME_s;
    }
#endif
    MApp_EpgTimer_ExecTimerUpAct(m_u8EpgNextStartUpIdx);
    MApp_EpgTimer_ReconfigTimerFromList(u32TimeCurrent);

    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
}

/******************************************************************************/
void MApp_EpgTimer_InitTimerSettings( BOOLEAN bScanEnd )
{
    U8 i;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();


    memset(_pstEpgTimer,        0x00, SCHEDULE_LIST_LEN);
    memset(&(stEpgTimerParam),  0x00, sizeof(stEpgTimerParam));

    // EPG initial setting
    for(i = 0; i < EPG_TIMER_MAX_NUM; i++)
    {
        _pstEpgTimer[i].enTimerType = EN_EPGUI_TIMER_NULL;
    }

    // Manual timer recording
    m_dwEPGManualTimerMonitorTimer = msAPI_Timer_GetTime0();

    m_u32EpgNextStartUpTime = 0;
#if ENABLE_CI_PLUS
    m_u32EpgNextStartUpTime_Temp = 0;
    m_u32EpgNextStartUpTime_Temp_Flag = FALSE;
#endif
    m_u8EpgNextStartUpIdx = EPGTIMER_INDEX_NULL;
    m_u8EpgStartingIdx = EPGTIMER_INDEX_NULL;

#if ENABLE_PVR
    for(i=0;i<EPGTIMER_REC_QUEUE_NUMBER;i++)
    {
        m_u8EpgTimerRecQueue[i].u8TimerIndex = EPGTIMER_INDEX_NULL;
        m_u8EpgTimerRecQueue[i].u8RecordPath = RECORD_PATH_INVALID;
    }
#endif

    g_TimerList_CurPageStartItem= 0;

    _MApp_EpgTimer_SaveTimerList(bScanEnd);

    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
}

/******************************************************************************/
void MApp_EpgTimer_ManualTimer_Init(void)
{
    TIMER_DBG(("MApp_EpgTimer_ManualTimer_Init()\n"));

    _MApp_EpgTimer_RetrieveTimerList();

    //if(_u32CheckSum != _MApp_EpgTimer_GetCheckSum())
    //{
        //MApp_EpgTimer_InitTimerSettings(TRUE);
    //}
    //MApp_EpgTimer_ExecTimerUpAct(MApp_GetLocalSystemTime());
   if(MApp_EpgTimer_GetEmptyTimerIdx())
        MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
}

BOOLEAN MApp_EpgTimer_CheckOnTimeReminder(void)
{
    ST_TIME _stTime;
    U32 u32TimerItemStart=0;
    U32 u32TimeCurrent=0;

    _MApp_EpgTimer_RetrieveTimerList();
    if(MApp_EpgUI_GetNumOfTimers()==0)
    {
        return FALSE;
    }
    u32TimeCurrent = MApp_GetLocalSystemTime();
     _stTime  = _pstEpgTimer[0].stStartDate;
     u16ReminderSrv  = _pstEpgTimer[0].u16SrvID;
     u8ReminderPcn  =_pstEpgTimer[0].u8PCN;
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
     if(EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[0].enTimerType)
     {
        g_bTimerTypeRecord = TRUE;
     }
#if ENABLE_CI_PLUS
     else if(EN_EPGUI_TIMER_CI_OP_REFRESH == _pstEpgTimer[0].enTimerType)
     {
        g_bTimeTypeOpRefresh = TRUE;
     }
#endif
#endif
     u32TimerItemStart = MApp_ConvertStTime2Seconds(&_stTime) ;
     if((u32TimerItemStart<=u32TimeCurrent)&&((u32TimerItemStart+60)>=u32TimeCurrent))
     return TRUE;
     else
     return FALSE;
}

/******************************************************************************/
void MApp_EpgTimer_ReconfigTimerFromList(U32 u32TimeActing )
{
    TIMER_DBG(("MApp_EpgTimer_ReconfigTimerFromList()\n"));
    _MApp_EpgTimer_DelPastTimeItems(u32TimeActing);
    _MApp_EpgTimer_SortTimerList();
    _MApp_EpgTimer_SaveTimerList(TRUE);

    MApp_EpgTimer_ResetStartUpTimer(u32TimeActing);

    TIMER_DBG(("MApp_EpgTimer_ReconfigTimerFromList()~ Done\n"));
}

/******************************************************************************/
void MApp_EpgTimer_ExecTimerUpAct(U8 u8TimeUpIndex)
{
    //S8 s8TimerItem;
    MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID, CurSrvType = E_SERVICETYPE_INVALID;
    U16 srvPos = INVALID_SERVICE_ID, CurSrvPos = INVALID_SERVICE_ID;
    MS_EPG_TIMER epgTimerAct;   //needed as W1 data will be erased by Line MApp_ChannelChange_DisableChannel()
    U32 u32PrvAddress;
    U32 u32TimeCurrent;

  #if ENABLE_PVR
    enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();   //get state here
    TIMER_DBG(("MApp_EpgTimer_ExecTimerUpAct()\n"));
    if(TimeShiftState == E_TIMESHIFT_STATE_RECORDING) //timeshift should be closed when recorder is starting
    {
        MApp_TimeShift_StateMachineInput(E_TIMESHIFT_INPUT_PLAYBACK_CLOSE, _u32PVRExtPara);
        MApp_TimeShift_StateMachineInput(E_TIMESHIFT_INPUT_RECORD_CLOSE, _u32PVRExtPara);
    }
  #endif

    if(u8TimeUpIndex >= MApp_EpgUI_GetNumOfTimers())
    {
        return;
    }

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
    epgTimerAct = _pstEpgTimer[u8TimeUpIndex];

    if(epgTimerAct.satus != EN_EPGTIMER_STATUS_NORMAL)
    {
        ASSERT(0);
        _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        return;
    }

    u32TimeCurrent = MApp_GetLocalSystemTime();

    //to avoid system unstable after the system offset abnormal
    if(EN_EPGTIMER_ACT_REMINDER == _TimerActType)
    {
        if(u32TimeCurrent > (m_u32EpgNextStartUpTime + 30))
        {
            TIMER_DBG(("System time abnormal\n"));
            TIMER_DBG(("m_u8EpgNextStartUpIdx=%u\n",m_u8EpgNextStartUpIdx));
            TIMER_DBG(("m_u32EpgNextStartUpTime=%u\n",m_u32EpgNextStartUpTime));
            TIMER_DBG(("u32TimeCurrent         =%u\n",u32TimeCurrent));
            MApp_EpgTimer_ReconfigTimerFromList(u32TimeCurrent);
            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
            return;
        }
    }
#if ENABLE_CI_PLUS
    else if(EN_EPGTIMER_ACT_CI_OP_REFRESH == _TimerActType)
    {
        if(u32TimeCurrent > (m_u32EpgNextStartUpTime + 30))
        {
            TIMER_DBG(("System time abnormal\n"));
            TIMER_DBG(("m_u8EpgNextStartUpIdx=%u\n",m_u8EpgNextStartUpIdx));
            TIMER_DBG(("m_u32EpgNextStartUpTime=%u\n",m_u32EpgNextStartUpTime));
            TIMER_DBG(("u32TimeCurrent         =%u\n",u32TimeCurrent));
            MApp_EpgTimer_ReconfigTimerFromList(u32TimeCurrent);
            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
            return;
        }
    }
#endif
#if ENABLE_PVR
    else if(EN_EPGTIMER_ACT_RECORDER_START == _TimerActType)
    {
        ST_TIME _stTime;
        U32 u32TimerItemEnd;

        _stTime  = _pstEpgTimer[u8TimeUpIndex].stEndDate;
        u32TimerItemEnd = MApp_ConvertStTime2Seconds(&_stTime);
        if(u32TimeCurrent > u32TimerItemEnd)
        {
            TIMER_DBG(("System time abnormal\n"));
            TIMER_DBG(("m_u8EpgNextStartUpIdx=%u\n",m_u8EpgNextStartUpIdx));
            TIMER_DBG(("m_u32EpgNextStartUpTime=%u\n",m_u32EpgNextStartUpTime));
            TIMER_DBG(("u32TimeCurrent         =%u\n",u32TimeCurrent));

            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
            return;
        }
        MApp_EpgTimer_SetStartingIndex(u8TimeUpIndex);
        MApp_UiPvr_RecordStop(); //computing power issue, only can record one channel at once
        MApp_UiPvr_PlaybackStop();
        u8TimeUpIndex = MApp_EpgTimer_GetStartingIndex(); //get active index that changed by RecordStop
    }
#endif

  #if ENABLE_PVR
    MApp_EpgTimer_SetStartingIndex(u8TimeUpIndex);
    if(EN_EPGTIMER_ACT_RECORDER_START == _TimerActType && EN_EPGUI_TIMER_RECORDER == epgTimerAct.enTimerType)
    {
        U8 RecordQueueIdx = EPGTIMER_INDEX_NULL;
        RecordQueueIdx = MApp_EpgTimer_RecordQueueAdd(u8TimeUpIndex, EPGTIMER_REC_PATH_UNKNOWN);
        if( RecordQueueIdx < EPGTIMER_REC_QUEUE_NUMBER)
        {
            //ready to record
        }
        else
        {
            ASSERT(0);
            MApp_EpgTimer_ClearStartingIndex();
            _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
            return;
        }
    }
    else
  #endif
    if(EN_EPGTIMER_ACT_REMINDER== _TimerActType && EN_EPGUI_TIMER_REMINDER == epgTimerAct.enTimerType)
    {
        //channel change
    }
    else
    {
        ASSERT(0);
    #if ENABLE_PVR
        MApp_EpgTimer_ClearStartingIndex();
    #endif
        _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        return;
    }

    {
        ST_TIME st;
        st = _pstEpgTimer[u8TimeUpIndex].stStartDate;
        u32LatestManualTimerStartDate = MApp_ConvertStTime2Seconds(&st);
    }

    //Channel change Begin...
    {
        BOOLEAN isChannelChanged = FALSE;

        msAPI_CM_GetServiceTypeAndPositionWithPCN(epgTimerAct.u8PCN, epgTimerAct.u16SrvID, &srvType, &srvPos);
        CurSrvType = msAPI_CM_GetCurrentServiceType();
        CurSrvPos  = msAPI_CM_GetCurrentPosition(CurSrvType);

        //Set current channel as previous
    #if 0//(ENABLE_S2_SOURCE)
        if(IsATVInUse()
            ||((IsDTVInUse()||IsS2InUse()) && !(CurSrvType == srvType && CurSrvPos == srvPos)))
    #else
        // IsDTVInUse() include dvbs
        if( IsATVInUse()
          ||(IsDTVInUse() && !(CurSrvType == srvType && CurSrvPos == srvPos))
          )
    #endif
        {
            dmSetLastWatchedOrdinal();
            isChannelChanged = TRUE;
        }

        //Switch input source

        // If current source is not DTV
    #if 0//(ENABLE_S2_SOURCE)
        if(!(IsDTVInUse()||IsS2InUse()))
    #else
        if (IsDTVInUse() == FALSE)
    #endif
        {
          #if 0//def AP_COWORK
            if(MApp_APEngine_CheckAPStatus() && !(MApp_APEngine_CheckAPStatus()>>1))
            {
                msAPI_APEngine_TransmitKey(KEY_EXIT);
                MApp_APEngine_Exit();
            }
          #endif

            #if ENABLE_DMP
            if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP)
            {
            #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL)
                MApp_ZUI_ACT_ExitThumbnailMode();
            #endif
                MApp_DMP_Exit();
            #if (ENABLE_DTV_EPG  && ENABLE_DVB)
                MApp_Epg_Init();
            #endif
            }
            #endif

            #if 0//def ENABLE_KTV
            if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_KTV
                && IsStorageInUse())
            {
                MApp_KTV_ExitKTV();
                MApp_KTV_Main_Exit();
            }
            #endif

            MApp_Dmx_CloseAllFilters();

      #if 1 // Refine at 20150908
            //UI_INPUT_SOURCE_TYPE = epgTimerAct.u8UiSrcType;
            MApp_InputSrc_Set_UiInputSrcType((E_UI_INPUT_SOURCE)epgTimerAct.u8UiSrcType);
      #else
         #if ENABLE_S2_EPG_REMINDER
            if(epgTimerAct.u8SrcIsDtvS2 == 1)
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
            else
         #endif
            { // todo
            #if ENABLE_DVBT
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
            #elif ENABLE_DVBC
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
            #elif ENABLE_DTMB
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
            #elif ENABLE_ISDBT
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
            #else
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
            #endif
            }
       #endif

            MApp_InputSource_SwitchSource(MApp_InputSrc_Get_UiInputSrcType(), MAIN_WINDOW);
            MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
            //enMenuMode = MENU_MODE;
            isChannelChanged = TRUE;

        }
      #if(ENABLE_S2_EPG_REMINDER)
        else
        {
        #if 1 // Refine at 20150908
            if( MApp_InputSrc_Get_UiInputSrcType() != epgTimerAct.u8UiSrcType )
            {
                MApp_InputSrc_Set_UiInputSrcType((E_UI_INPUT_SOURCE)epgTimerAct.u8UiSrcType);

                MApp_InputSource_SwitchSource(MApp_InputSrc_Get_UiInputSrcType(), MAIN_WINDOW);
            }
        #else
            if(epgTimerAct.u8SrcIsDtvS2 == 1)
            {
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_S2)
                {
                    //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                    MApp_InputSrc_Set_UiInputSrcType(UI_INPUT_SOURCE_S2);
                    MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);
                }
            }
            else
            {
                //if (UI_INPUT_SOURCE_TYPE > UI_INPUT_SOURCE_DTMB)
                if ( MApp_InputSrc_Is_UiInputSrcTypeDtv(UI_INPUT_SOURCE_TYPE) == FALSE)
                {
                    //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;//Thomas 20150714 to do
                    MApp_InputSrc_Set_UiInputSrcType(SYS_DEFAULT_DTV_UI_INPUTSOURCE);
                    MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);
                }
            }
        #endif
        }
      #endif

        //Channel change
        if (isChannelChanged)
        {
            #if ENABLE_PVR
            if(MApp_PVR_IsRecording())
            {
                MApp_UiPvr_PlaybackStop();
                MApp_UiPvr_RecordStop();
            }
            #endif
            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);    //This line will erase W1 data.
            if(srvType != msAPI_CM_GetCurrentServiceType())
            {
                msAPI_CM_SetCurrentServiceType(srvType);
            }
            msAPI_CM_SetCurrentPosition(srvType, srvPos);
            MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);
        }
    }
    //Channel change End...

#if ENABLE_PVR
      if(EN_EPGUI_TIMER_RECORDER == epgTimerAct.enTimerType && EN_EPGTIMER_ACT_RECORDER_START == _TimerActType)
       {
         g_PVR_RecordStatus = E_PVR_RECORDER_TIMEUP;
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        if(epgTimerAct.bPinCodeCached)
        {
            g_u16CiPinCode = epgTimerAct.u16CachedPinCode;
       }
        else
#endif
        {
            g_u16CiPinCode = 0xFFFF;
        }
        
    #if DTG_FREEVIEW_STANDBY
         if(MApp_FreeView_Is_Standby())
         {
            MApp_FreeView_PowerOn();
         }
    #endif
       }
#endif
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
}

#if ENABLE_PVR
void MApp_EpgTimer_CheckRecordEndTime(U32 u32TimeActing)
{
    U32 u32ItemEndTime;
    U32 u32PrvAddress;
    ST_TIME _stTime;
    U8 u8TimerTotal;
    U8 u8TimerIndex;
    U8 i;
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
    BOOLEAN bRecordFinishedPowerOff = FALSE;
#endif

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    u8TimerTotal = MApp_EpgUI_GetNumOfTimers();
    u32TimeActing = u32TimeActing ;

    for(i=0;i<EPGTIMER_REC_QUEUE_NUMBER;i++)
    {
        u8TimerIndex = m_u8EpgTimerRecQueue[i].u8TimerIndex;

        if(u8TimerIndex == EPGTIMER_INDEX_NULL)
            continue;

        if(u8TimerIndex == EPGTIMER_INDEX_USER)
        {
            if(MApp_UiPvr_IsRecordingExceedMaxTime(m_u8EpgTimerRecQueue[i].u8RecordPath))
            {
                MApp_UiPvr_RecordStop();
                m_u8EpgTimerRecQueue[i].u8TimerIndex = EPGTIMER_INDEX_NULL;
                m_u8EpgTimerRecQueue[i].u8RecordPath = RECORD_PATH_INVALID;
            }
            continue;
        }

        if(u8TimerIndex >= u8TimerTotal)
        {
            TIMER_DBG(("u8TimerTotal=%d,u8TimerIndex=%d\n",u8TimerTotal,u8TimerIndex));
            ASSERT(0);
            m_u8EpgTimerRecQueue[i].u8TimerIndex = EPGTIMER_INDEX_NULL;
            m_u8EpgTimerRecQueue[i].u8RecordPath = RECORD_PATH_INVALID;
            continue;
        }

        _stTime = _pstEpgTimer[u8TimerIndex].stEndDate;
        u32ItemEndTime = MApp_ConvertStTime2Seconds(&_stTime) ;

        if(u32TimeActing > (u32ItemEndTime-60)) //update PF version before 1 minute
        {
            if(m_u8EpgTimerRecQueue[i].u8PfVersion == 0xFF)
            {
                MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
                U16 srvPos = INVALID_SERVICE_ID;
                U8 PfVersion;

                msAPI_CM_GetServiceTypeAndPositionWithPCN(_pstEpgTimer[m_u8EpgTimerRecQueue[i].u8TimerIndex].u8PCN,
                    _pstEpgTimer[m_u8EpgTimerRecQueue[i].u8TimerIndex].u16SrvID, &srvType, &srvPos);

                if(MApp_Epg_Pf_GetTableVersion(msAPI_SI_ToSI_Service_Type(srvType), srvPos , &PfVersion) == MW_EN_EPG_FUNC_STATUS_SUCCESS)
                {
                    TIMER_DBG(("PfVersion=%u\n", PfVersion));
                    m_u8EpgTimerRecQueue[i].u8PfVersion = PfVersion;
                }
            }
        }

        if(u32TimeActing >= u32ItemEndTime)
        {
            MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
            U16 srvPos = INVALID_SERVICE_ID;
            U8 PfVersion;

            msAPI_CM_GetServiceTypeAndPositionWithPCN(_pstEpgTimer[m_u8EpgTimerRecQueue[i].u8TimerIndex].u8PCN,
                _pstEpgTimer[m_u8EpgTimerRecQueue[i].u8TimerIndex].u16SrvID, &srvType, &srvPos);

            MApp_Epg_Pf_GetTableVersion(msAPI_SI_ToSI_Service_Type(srvType), srvPos , &PfVersion);
            if((EN_EPGRM_AUTO != _pstEpgTimer[m_u8EpgTimerRecQueue[i].u8TimerIndex].enRepeatMode)
                    ||(PfVersion != m_u8EpgTimerRecQueue[i].u8PfVersion
                            || u32TimeActing > (u32ItemEndTime+(SECONDS_PER_HOUR*2))))
           {
                if(HWND_EPG_COUNTDOWN_BUTTON_BAR == MApp_ZUI_API_GetFocus())
                {
                    MApp_ZUI_ACT_ShutdownOSD();
                    MApp_EpgTimer_ExecTimerUpAct(m_u8EpgNextStartUpIdx);
                }

                TIMER_DBG(("record Stopped"));
                MApp_UiPvr_RecordStop();
                m_u8EpgTimerRecQueue[i].u8TimerIndex = EPGTIMER_INDEX_NULL;
                m_u8EpgTimerRecQueue[i].u8RecordPath = RECORD_PATH_INVALID;

                MApp_EpgTimer_ReconfigTimerFromList(u32TimeActing);
            #if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
                if(MApp_GetActiveStandbyMode())
                {
                    bRecordFinishedPowerOff = TRUE;
                }
            #endif
            }
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
    if(bRecordFinishedPowerOff)
    {
        g_bTimerTypeRecord = FALSE;
        bRecordFinishedPowerOff = FALSE;
             MApp_Standby_Init();
    }
#endif
}
#endif

/******************************************************************************/
U32 MApp_EpgTimer_GetCountDown_s(void)
{
#if ENABLE_PVR
    if(EN_EPGTIMER_ACT_RECORDER_START == _TimerActType)
    {
        return (m_u32EpgNextStartUpTime - MApp_GetLocalSystemTime() - EPG_RECORDER_PVR_LEADING_TIME_s);
    }
    else if(EN_EPGTIMER_ACT_REMINDER == _TimerActType)
    {
        return (m_u32EpgNextStartUpTime - MApp_GetLocalSystemTime());
    }
#if ENABLE_CI_PLUS
    else if(EN_EPGTIMER_ACT_CI_OP_REFRESH == _TimerActType)
    {
        return (m_u32EpgNextStartUpTime - MApp_GetLocalSystemTime());
    }
#endif
    else
    {
        return 0;
    }
#else
    return (m_u32EpgNextStartUpTime - MApp_GetLocalSystemTime());
#endif
}

/******************************************************************************/
U16 _MApp_EpgTimer_GetCheckSum(void)
{   //cost about EPG_TIMER_MAX_NUM x 1 ms
    U8   u8IdxItem, u8IdxShift;
    U32  u16CheckSum = 0;
    U8 *pBuf;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
    for(u8IdxItem=0; u8IdxItem<EPG_TIMER_MAX_NUM; u8IdxItem++)
    {
        pBuf=(U8*)(&_pstEpgTimer[u8IdxItem]);
        //for(u8IdxShift = 0; u8IdxShift<((sizeof(MS_EPG_TIMER)-sizeof(MS_EPG_TIMER)%4)/4); u8IdxShift++)
        for(u8IdxShift = 0; u8IdxShift<sizeof(MS_EPG_TIMER); u8IdxShift++)
        {
            u16CheckSum += pBuf[u8IdxShift];
        }
    }

    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    return (u16CheckSum);
}

/******************************************************************************/

//******************************************************************************/
void MApp_EpgTimer_TimerList_UI_Init(void)
{
    g_TimerList_CurPageStartItem = 0;
    MApp_EpgUI_SetTimerListCurIdx(0);
    memset(&(stEpgTimerParam),  0x00, sizeof(stEpgTimerParam));
}

//******************************************************************************/
U8 MApp_EpgTimer_GetTimerListPageItemsTotal(EN_EPGUI_TIMER_TYPE timerType)
{
    U8 recorderListIdx;
    U8 itemCount = 0;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    for ( recorderListIdx=g_TimerList_CurPageStartItem; recorderListIdx < EPG_TIMER_MAX_NUM; recorderListIdx++ )
    {

        if(EN_EPGUI_TIMER_NULL == _pstEpgTimer[recorderListIdx].enTimerType
            || _pstEpgTimer[recorderListIdx].enTimerType >= EN_EPGUI_TIMER_INVALID)
        {
            break;
        }
        else if(timerType == _pstEpgTimer[recorderListIdx].enTimerType)
        {
            itemCount++;
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);

    return itemCount;
}
//******************************************************************************/
U8 MApp_EpgTimer_GetTimerListItemsTotal(EN_EPGUI_TIMER_TYPE timerType)
{
    U8 recorderListIdx;
    U8 itemCount = 0;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    for ( recorderListIdx=0; recorderListIdx < EPG_TIMER_MAX_NUM; recorderListIdx++ )
    {

        if(EN_EPGUI_TIMER_NULL == _pstEpgTimer[recorderListIdx].enTimerType
            ||_pstEpgTimer[recorderListIdx].enTimerType >= EN_EPGUI_TIMER_INVALID)
        {
            break;
        }
        else if(timerType == _pstEpgTimer[recorderListIdx].enTimerType)
        {
            itemCount++;
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);

    return itemCount;
}
//******************************************************************************/
U8 MApp_EpgTimer_GetIdxFromTimerDBIdx(EN_EPGUI_TIMER_TYPE timerType)
{
    U8 recorderListIdx;
    U8 itemCount = 0;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    for ( recorderListIdx=g_TimerList_CurPageStartItem; recorderListIdx < EPG_TIMER_MAX_NUM; recorderListIdx++ )
    {
        if(EN_EPGUI_TIMER_NULL == _pstEpgTimer[recorderListIdx].enTimerType
            ||_pstEpgTimer[recorderListIdx].enTimerType >= EN_EPGUI_TIMER_INVALID)
        {
            break;
        }
        else if(timerType == _pstEpgTimer[recorderListIdx].enTimerType)
        {
            tmpTimerListIdx[itemCount] = recorderListIdx;
            //printf("~tmpTimerListIdx[%bu]=%bu \n", itemCount, tmpTimerListIdx[itemCount]);
            itemCount++;
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);

    return itemCount;
}
//******************************************************************************/

U8 MApp_EpgTimer_GetTimerDBIdxFromIdx(U8 u8Idx)
{
    return tmpTimerListIdx[u8Idx];
}
//******************************************************************************/

void MApp_EpgTimer_initTmpTimerListIdx(void)
{
    U8 totalTimerListIdx;

    //memset(tmpTimerListIdx, 0xff, sizeof(U8));

    for ( totalTimerListIdx=0; totalTimerListIdx<EPG_TIMER_MAX_NUM; totalTimerListIdx++ )
    {
        tmpTimerListIdx[totalTimerListIdx] = 0xFF;
    }
}
//******************************************************************************/

U8 MApp_EpgTimer_GetTmpArrayIdTotal(void)
{
    U8 recorderCount = 0;
    U8 totalTimerListIdx;

    for ( totalTimerListIdx=0; totalTimerListIdx<EPG_TIMER_MAX_NUM; totalTimerListIdx++ )
    {
        if (tmpTimerListIdx[totalTimerListIdx] == 0xFF) break;
        recorderCount++;
    }

    return recorderCount;
}

EN_EPG_TIMER_ACT_TYPE MApp_EpgTimer_GetTimerActType(void)
{
    return _TimerActType;
}

U8 MApp_EpgTimer_GetNextStartUpIndex(void)
{
    return m_u8EpgNextStartUpIdx;
}

BOOLEAN MApp_EpgTimer_AddEpgEvent(MS_EPG_TIMER* pEpgTimerEvent)
{
    U8 u8CurIdx = MApp_EpgTimer_GetEmptyTimerIdx();
    U32 u32PrvAddress;

    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();
    if(u8CurIdx >= EPG_TIMER_MAX_NUM)
    {
        TIMER_DBG(("EPG event has fulled : %u!!!\n",u8CurIdx));
        _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
        return FALSE;
    }

    _pstEpgTimer[u8CurIdx] = *pEpgTimerEvent;
    MApp_EpgUI_SetTimerListCurIdx(0);
    MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);
    return TRUE;
}

#if ENABLE_PVR
/******************************************************************************/
BOOLEAN MApp_EpgTimer_IsRecorderListFull(U8 *u8RecorderNumInList)
{
    U8 recorderCount = 0;
    U8 totalTimerListIdx;
    U32 u32PrvAddress;
    u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

    for ( totalTimerListIdx=0; totalTimerListIdx<EPG_TIMER_MAX_NUM; totalTimerListIdx++ )
    {
        if (EN_EPGUI_TIMER_RECORDER == _pstEpgTimer[totalTimerListIdx].enTimerType)
        {
            recorderCount++;
            *u8RecorderNumInList = recorderCount;
            if(recorderCount >= EPG_RECORDER_MAX_COUNT)
            {
                return TRUE;
            }
        }
    }
    _MApp_EpgTimer_CloseXdataWindow(u32PrvAddress);

    return FALSE;
}

U8 MApp_EpgTimer_RecordQueueAdd(U8 ItemIndex, U8 RecPath)
{
    U8 i;

    TIMER_DBG(("MApp_EpgTimer_RecordQueueAdd,ItemIndex=%d,RecPath=%d\n",ItemIndex,RecPath));

    for(i=0;i<EPGTIMER_REC_QUEUE_NUMBER;i++)
    {
        if(m_u8EpgTimerRecQueue[i].u8TimerIndex == EPGTIMER_INDEX_NULL)
        {
            m_u8EpgTimerRecQueue[i].u8TimerIndex = ItemIndex;
            m_u8EpgTimerRecQueue[i].u8RecordPath = RecPath;
            m_u8EpgTimerRecQueue[i].u8PfVersion = 0xFF;

            return i;
        }
    }
    ASSERT(0);
    return EPGTIMER_INDEX_NULL;
}

void MApp_EpgTimer_RecordQueueDel(U8 RecPath)
{
    U8 i;

    TIMER_DBG(("MApp_EpgTimer_RecordQueueDel,RecPath=%d\n",RecPath));
    for(i=0;i<EPGTIMER_REC_QUEUE_NUMBER;i++)
    {
        if(m_u8EpgTimerRecQueue[i].u8RecordPath == RecPath)
        {
            if(m_u8EpgTimerRecQueue[i].u8TimerIndex != EPGTIMER_INDEX_NULL
                || m_u8EpgTimerRecQueue[i].u8TimerIndex != EPGTIMER_INDEX_USER)
            {
                U8 Tidx = m_u8EpgTimerRecQueue[i].u8TimerIndex;
                m_u8EpgTimerRecQueue[i].u8RecordPath = RECORD_PATH_INVALID;
                m_u8EpgTimerRecQueue[i].u8TimerIndex = EPGTIMER_INDEX_NULL;

                MApp_EpgTimer_ResetStopppedTimerListItem(Tidx);
                MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime() );
            }
            return;
        }
    }
//    ASSERT(0);
    return;
}

void MApp_EpgTimer_RecordQueueSetPath(U8 ItemIndex, U8 RecPath)
{
    U8 i;

    TIMER_DBG(("MApp_EpgTimer_RecordQueueSetPath,ItemIndex=%d,RecPath=%d\n",ItemIndex,RecPath));
    for(i=0;i<EPGTIMER_REC_QUEUE_NUMBER;i++)
    {
        if(m_u8EpgTimerRecQueue[i].u8TimerIndex == ItemIndex)
        {
            m_u8EpgTimerRecQueue[i].u8RecordPath = RecPath;
            return;
        }
    }
    ASSERT(0);
    return;
}

BOOLEAN MApp_EpgTimer_IsTriggerByTimer(void)
{
    if(m_u8EpgStartingIdx != EPGTIMER_INDEX_NULL)
        return TRUE;
    else
        return FALSE;
}

BOOLEAN MApp_EpgTimer_GetStartingEventName(U16 * pEventName)
{
    if(m_u8EpgStartingIdx == EPGTIMER_INDEX_NULL)
    {
        pEventName[0] = '\0';
        return FALSE;
    }
    else
    {
        U32 u32PrvAddress;
        u32PrvAddress = _MApp_EpgTimer_OpenXdataWindow();

        UnicodeCpy((S8*)pEventName, (S8*)_pstEpgTimer[m_u8EpgStartingIdx].au16EvtName);
        if(pEventName[0] == '\0')
            return FALSE;
        else
            return TRUE;
   }
}

void MApp_EpgTimer_SetStartingIndex(U8 Index)
{
    m_u8EpgStartingIdx = Index;
    return;
}

void MApp_EpgTimer_ClearStartingIndex(void)
{
    m_u8EpgStartingIdx = EPGTIMER_INDEX_NULL;
    return;
}

U8 MApp_EpgTimer_GetStartingIndex(void)
{
    return m_u8EpgStartingIdx;
}

/*
BOOLEAN  MApp_EpgTimer_RecordQueueIsFull(void)
{
    U8 i;

    TIMER_DBG(("MApp_EpgTimer_RecordQueueIsFull\n"));
    for(i=0;i<EPGTIMER_REC_QUEUE_NUMBER;i++)
    {
        if(m_u8EpgTimerRecQueue[i].u8TimerIndex != RECORD_PATH_INVALID)
        {
            return FALSE;
        }
    }
    TIMER_DBG(("Record Queue is full\n"));
    return TRUE;
}
*/

#endif//ENABLE_PVR

#endif  //#if (ENABLE_DTV_EPG)
#undef MAPP_EPG_TIMER_C

