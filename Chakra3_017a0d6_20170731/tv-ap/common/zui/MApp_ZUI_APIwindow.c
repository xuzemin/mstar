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

#define MAPP_ZUI_APIWINDOW_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


///////////////////////////////////////////////////////////////////////////////////////////////////
// Description: Menu GUI window/control basic functions
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTeffect.h"
#include "msAPI_Timer.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_Func_AudioVolume.h"

//-------------------------------------------------------------------------------------------------
// Local Defines
//------------------------------------------------------------------------------------------------
//ZUI_VARDATA_MAXBYTESIZE: for storage visible/disable data, should be: ZUI_VARDATA_MAXBYTESIZE>=HWND_MAX/8
#define ZUI_VARDATA_MAXBYTESIZE        (1800/32) //for 800 windows...

//ZUI_MAX_MOVABLE_HWND: number of hwnd can be moved and scaled
#define ZUI_MAX_MOVABLE_HWND           1800

//ZUI_ALL_MOVABLE_HWND: all windows can be moved and scaled!!
#define ZUI_ALL_MOVABLE_HWND           1

//ZUI_MSG_QUEUE_SIZE: number of queue items in message queue
#define ZUI_MSG_QUEUE_SIZE             40

//ZUI_MAX_TIMER_COUNT: number of timers can be registered
#define ZUI_MAX_TIMER_COUNT            8

//ZUI_SUPPORT_MOVE_ALL_SUCCESSORS: support move all successors API
#define ZUI_SUPPORT_MOVE_ALL_SUCCESSORS 1

//ZUI_REPAINT_TIME_DEBUG_THRESHOLD
#define ZUI_REPAINT_TIME_DEBUG_THRESHOLD 50

//ZUI_LOW_FREQ_TIMER_THRESHOLD: for MHEG5, need to switch to ZUI at least this freq
#define ZUI_LOW_FREQ_TIMER_THRESHOLD       100

#define ZUI_DBG(x) //x

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------

extern ZUI_STATE _eZUIState;
extern E_OSD_ID _eActiveOSD;

//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------

typedef struct _TIMERSTRUCT
{
    HWND owner; //HWND_INVALID for unused
    U32  u32ID;
    U32 u32Period; // ms
    U32 u32PassTime; // ms
} TIMER_STRUCT;

// the MSGQUEUE struct is a internal struct.
// using semaphores to implement message queue.
typedef struct _MSGQUEUE
{
    MSG MsgQueue[ZUI_MSG_QUEUE_SIZE]; //HAND_INVALID for unused
    U32 u32MsgQIdxStart;
    U32 u32MsgQIdxEnd;
    TIMER_STRUCT Timers[ZUI_MAX_TIMER_COUNT];  // Timer owner
    U32 u32PrevTimerEntered;
} MSGQUEUE;

typedef struct _MOVABLEHWNDSTRUCT
{
    HWND hwnd; //HAND_INVALID for unused
    RECT rect; //special case: if width < 0 or height < 0, then move all successors (ZUI_SUPPORT_MOVE_ALL_SUCCESSORS)
} MOVABLE_HWND_STRUCT;


static INVALIDATE_CLIP _InvClip;
static MSGQUEUE     _MenuMsgQueue;
static HWND         _FocusHwnd = HWND_INVALID;
static HWND         _CheckpointFocusHwnd = HWND_INVALID;
#define GETWNDFOCUS() (_FocusHwnd)

static U32           _VarDataTemp[ZUI_VARDATA_MAXBYTESIZE*2]; //need to use msAPI_Memory to save XDATA?
static U32 *         _VarDataVisible = NULL;
static U32 *         _VarDataDisable = NULL;

//table access is THE SAME SPEED then bitwise operations
//static  U8 _ZUI_TBLSEG _bit_table[] = { BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7 };

//#define GETWNDVISIBLE(hwnd) (_VarDataVisible[hwnd>>5]&(1<<(hwnd&31)) )
#define GETWNDVISIBLE(hwnd) ((_VarDataVisible[hwnd>>5]>>(hwnd&31))&1)
#define SETWNDVISIBLE(hwnd) ( _VarDataVisible[hwnd>>5]|=(1<<(hwnd&31)) )
#define SETWNDINVISIBLE(hwnd) ( _VarDataVisible[hwnd>>5]&=~(1<<(hwnd&31)) )
//#define GETWNDDISABLE(hwnd) (_VarDataDisable[hwnd>>5]&(1<<(hwnd&31)) )
#define GETWNDDISABLE(hwnd) ((_VarDataDisable[hwnd>>5]>>(hwnd&31))&1)
#define SETWNDDISABLE(hwnd) ( _VarDataDisable[hwnd>>5]|=(1<<(hwnd&31)) )
#define SETWNDENABLE(hwnd) ( _VarDataDisable[hwnd>>5]&=~(1<<(hwnd&31)) )

#ifdef ZUI_MAX_MOVABLE_HWND
#if ZUI_ALL_MOVABLE_HWND
static RECT _VarDataMovableRect[ZUI_MAX_MOVABLE_HWND];
#else
static MOVABLE_HWND_STRUCT _VarDataMovableRect[ZUI_MAX_MOVABLE_HWND];
#endif
#endif //ZUI_MAX_MOVABLE_HWND

//MENU_STATE _eZUIState;
//HWND g_hwndDropList = HWND_INVALID;

#if ZUI_DBG_RECURSIVE
static BIT _bInSendMessage = 0;
static BIT _bInDispatchMessage = 0;
#endif //ZUI_DBG_RECURSIVE


extern void _MApp_ZUI_CTL_MainFramePaint(HWND hwndMainFrame, WPARAM *wParam);
extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);

//-------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_InitMsgQueue
///  init the message queue
///
///  @return BOOLEAN TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_InitMsgQueue (void)
{
    //printf("init: sz_msg_q=%u\n", (U16)sizeof(_MenuMsgQueue));
    //printf("init: sz_var_r=%bu\n", (U8)sizeof(_VarDataMovableRect));

    MApp_ZUI_API_EmptyMessageQueue();
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_DispatchMessage
///  dispatch a message to a specified window handle
///
///  @param [in]       pMsg PMSG     message pointer
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_API_DispatchMessage (PMSG pMsg)
{
    HWND focus;
    S32 iRet = 0;
    //WNDPROC WndProc;

    //PRINT( "[DispatchMessage] message: %x, hWnd: %x, wP: %x\n",
    //    pMsg->message,
    //    pMsg->hwnd,
    //    pMsg->wParam);

#if ZUI_DBG_RECURSIVE
    if (_bInDispatchMessage)
    {
        printf("[RECURSIVE]DispatchMessage!!\n");
        ABORT();
        return 0;
    }
    _bInDispatchMessage = 1;
#endif //ZUI_DBG_RECURSIVE

    if (g_GUI_WindowList == 0)
    {
        return -2;
    }

    //process special case, don't do these in window proc..
    if (pMsg->message == MSG_KEYDOWN)
    {
        //printf("[dispmsg1]\n");
        if (_eZUIState == E_ZUI_STATE_RUNNING /*||
            _eZUIState == E_ZUI_STATE_MSGBOX_DOMODAL*/)
        {
            if (!MApp_ZUI_ACT_HandleGlobalKey((VIRTUAL_KEY_CODE)pMsg->wParam))
            {
                focus = GETWNDFOCUS();
                //printf("/focus=%bu\n", (U8)focus);
                //printf("[dispmsg2]\n");
                if(!(E_OSD_DMP == _eActiveOSD))
                {
                    MApp_FuncExec_AdjustVolume((VIRTUAL_KEY_CODE)pMsg->wParam);
                }
                if (HWND_INVALID != focus)
                {
                    pMsg->hwnd = focus; //2007/12/24: keydown message for focus
                    iRet = MApp_ZUI_ACT_ExecuteWndProc(GETWNDPROCID(focus), pMsg);
                }
            }
        }
#if ZUI_DBG_RECURSIVE
        _bInDispatchMessage = 0;
#endif //ZUI_DBG_RECURSIVE
        return iRet;
    }

    if (pMsg->hwnd == HWND_INVALID)
    {
#if ZUI_DBG_RECURSIVE
        _bInDispatchMessage = 0;
#endif //ZUI_DBG_RECURSIVE

        return -1;
    }

    iRet = MApp_ZUI_ACT_ExecuteWndProc(GETWNDPROCID(pMsg->hwnd), pMsg);

#if ZUI_DBG_RECURSIVE
        _bInDispatchMessage = 0;
#endif //ZUI_DBG_RECURSIVE

    return iRet;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_PostMessage
///  post a message to the message queue
///      the message won't be executed immediatly
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       iMsg MESSAGE_ENUM     message type
///  @param [in]       wParam WPARAM     message parameter
///
///  @return BOOLEAN TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_PostMessage (HWND hWnd, MESSAGE_ENUM iMsg, WPARAM wParam)
{
    PMSG pmessage;

    if (g_GUI_WindowList == 0)
    {
        return FALSE;
    }

    //add a filter to reduce message queue usage...
    if (!MApp_ZUI_ACT_PostMessageFilter(GETWNDPROCID(hWnd), iMsg))
    {
        //printf("message filtered!\n");
        return FALSE;
    }

    //printf("\n[post msg] hWnd = %d, iMsg = %d, wParam = %d", hWnd, iMsg, wParam);
    //printf("\n[WndPostMessage] message queue _MenuMsgQueue.u32MsgQIdxStart = %d, _MenuMsgQueue.u32MsgQIdxEnd = %d", _MenuMsgQueue.u32MsgQIdxStart, _MenuMsgQueue.u32MsgQIdxEnd);
    pmessage = &_MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxStart];
    if (pmessage->hwnd != HWND_INVALID)
    {
        ZUI_DBG_FAIL(printf("queue full! (%lu,%lu)\n",
                _MenuMsgQueue.u32MsgQIdxStart,
                _MenuMsgQueue.u32MsgQIdxEnd));
        /*for (i = 0; i < ZUI_MSG_QUEUE_SIZE; i++)
        {
            pmessage = &_MenuMsgQueue.MsgQueue[i];
            printf("\n[WndPostMessage] msg in queue[%d], bUsed = %d, hwnd = %d, imsg = %d, wparam = %d", i, (U16)_MenuMsgQueue.bUsed[i], pmessage->hwnd, pmessage->message, (U16)pmessage->wParam);
        }*/
        ABORT();

        return FALSE;   // no available message queue slot
    }

    //PRINT("\n[post msg] write msg index = %d", _MenuMsgQueue.u32MsgQIdxStart);
    //_MenuMsgQueue.bUsed[_MenuMsgQueue.u32MsgQIdxStart] = TRUE;
    pmessage->hwnd = hWnd;
    pmessage->message = iMsg;
    pmessage->wParam = wParam;

    //PRINT("\n[post msg] after write, wnd = %d, msg = %d", _MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxStart].hwnd, _MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxStart].message);
    ++_MenuMsgQueue.u32MsgQIdxStart;
    _MenuMsgQueue.u32MsgQIdxStart %= ZUI_MSG_QUEUE_SIZE;

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_EmptyMessageQueue
///  empty the message queue...
///
///  @return nothing
///
///  @author MStarSemi @date 2007/1/30
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_EmptyMessageQueue (void)
{
    U32 i;

    _MenuMsgQueue.u32MsgQIdxStart = 0;
    _MenuMsgQueue.u32MsgQIdxEnd = 0;
    for (i = 0; i < ZUI_MSG_QUEUE_SIZE; i++)
        _MenuMsgQueue.MsgQueue[i].hwnd = HWND_INVALID;

    //init timer table..
    for (i = 0; i < ZUI_MAX_TIMER_COUNT; i++)
        _MenuMsgQueue.Timers[i].owner = HWND_INVALID;

    //for (u16i = 0; u16i < ZUI_MSG_QUEUE_SIZE; u16i++)
    //    _MenuMsgQueue.bUsed[u16i] = FALSE;

    _MenuMsgQueue.u32PrevTimerEntered = msAPI_Timer_GetTime0();

    _InvClip.bNeedRepaint = FALSE;
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_SendMessage
///  send a message to the message queue
///      the message will be executed immediatly
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       iMsg MESSAGE_ENUM     message type
///  @param [in]       wParam WPARAM     message paramter
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_API_SendMessage (HWND hWnd, MESSAGE_ENUM iMsg, WPARAM wParam)
{
    //U8 u8Activeidx;
    S32 iRet;
    MSG msg;

#if ZUI_DBG_RECURSIVE
    if (_bInSendMessage)
    {
        printf("[RECURSIVE]SendMessage!!\n");
        ABORT();
        return 0;
    }
    _bInSendMessage = 1;
#endif //ZUI_DBG_RECURSIVE

    if (hWnd == HWND_INVALID)
    {
#if ZUI_DBG_RECURSIVE
        _bInSendMessage = 0;
#endif //ZUI_DBG_RECURSIVE
        return -1;
    }

    if (g_GUI_WindowList == 0)
    {
        return -2;
    }

    msg.hwnd = hWnd;
    msg.message = iMsg;
    msg.wParam = wParam;

    ZUI_DBG(printf("[send] hwnd = %lu, iMsg = %lu, wParam = %lx\n",
        (U32)hWnd, (U32)iMsg, (U32)wParam));
    //printf("\n[WndSendMessage] u8SendMsgIndex = %d", (U16)u8SendMsgIndex);

    iRet = MApp_ZUI_API_DispatchMessage(&msg);
#if ZUI_DBG_RECURSIVE
    _bInSendMessage = 0;
#endif //ZUI_DBG_RECURSIVE
    return iRet;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_InvalidateWindow
///  mark the window region as invalidated
///
///  @param [in]       hWnd HWND      target window
///
///  @return void
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_API_InvalidateWindow(HWND hWnd)
{
    RECT rect;
    //printf("[]dirty=%u\n", hWnd);
    memset(&rect,0,sizeof(RECT));
    MApp_ZUI_API_GetWindowRect(hWnd, &rect);
    MApp_ZUI_API_InvalidateRect(&rect);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_InvalidateRect
///  mark the rectangle region as invalidated
///
///  @param [in]       prc const RECT *    rectangle region
///
///  @return void
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void  MApp_ZUI_API_InvalidateRect (const RECT* prc)
{
    RECT rcNew;
    U8 u8I = 0, u8J;

    if (prc != 0)
        rcNew = *prc;
    else
        MApp_ZUI_API_GetWindowInitialRect(HWND_MAINFRAME, &rcNew);

    #ifdef ZUI_INVALIDATE_BORDER
    rcNew.left = prc->left-ZUI_INVALIDATE_BORDER;
    rcNew.top = prc->top-ZUI_INVALIDATE_BORDER;
    rcNew.width = prc->width+ZUI_INVALIDATE_BORDER*2;
    rcNew.height = prc->height+ZUI_INVALIDATE_BORDER*2;
    #endif //ZUI_INVALIDATE_BORDER

    //case1: trivial case: invalidate region is empty, just add into first rectangle
    if (!_InvClip.bNeedRepaint)
    {
        _InvClip.bNeedRepaint = TRUE;
        _InvClip.u8RectIndex = 1;
        _InvClip.stRect[0] = rcNew;

        for(u8J = 1; u8J < MAX_INVALIDATE_CLIP_RECT_NUMBER; u8J++)
            RECT_SET(_InvClip.stRect[u8J], 0, 0, 0, 0);

        return;
    }

    //case2: check for each rectangle, and union two intersected rectangle into one
    while(u8I < MAX_INVALIDATE_CLIP_RECT_NUMBER)
    {
        if (MApp_ZUI_API_DoesIntersect(&rcNew, &_InvClip.stRect[u8I]))
        {
            MApp_ZUI_API_UnionRect(&_InvClip.stRect[u8I], &rcNew);
            break;
        }
        else
        {
            u8I++; // direct to next index

            if( (u8I < MAX_INVALIDATE_CLIP_RECT_NUMBER) && (_InvClip.stRect[u8I].width == 0) )
            {
                _InvClip.stRect[u8I] = rcNew;
                _InvClip.u8RectIndex = MAX(_InvClip.u8RectIndex, u8I+1);
                break;
            }
        }
    }

    //case3: if rectangle are disjoint, then choose the smallest one after union
    if(u8I >= MAX_INVALIDATE_CLIP_RECT_NUMBER)
    {
        U8 u8Loop, u8MinIndex = 0;
        RECT stTempRect;
        U32 u32CurentArea, u32MinArea = 0;

        for(u8Loop = 0 ; u8Loop < _InvClip.u8RectIndex ; u8Loop++)
        {
            stTempRect = _InvClip.stRect[u8Loop];
            MApp_ZUI_API_UnionRect(&stTempRect, &rcNew);
            u32CurentArea = (U32)stTempRect.width * stTempRect.height;

            if(u8Loop == 0)
            {
                u8MinIndex = 0;
                u32MinArea= u32CurentArea;
            }
            else
            {
                if(u32CurentArea < u32MinArea)
                {
                    u32MinArea= u32CurentArea;
                    u8MinIndex = u8Loop;
                }
            }
        }
        MApp_ZUI_API_UnionRect(&_InvClip.stRect[u8MinIndex], &rcNew);
    }

    //finally, check if any of two rectangles are intersected
    if(_InvClip.u8RectIndex > 1)
    {
        for(u8I = 0 ;  u8I < _InvClip.u8RectIndex-1 ; u8I++)
        {
            for(u8J = u8I+1 ; u8J < _InvClip.u8RectIndex ; u8J++)
            {
                if(MApp_ZUI_API_DoesIntersect(&_InvClip.stRect[u8I], &_InvClip.stRect[u8J]))
                {
                    MApp_ZUI_API_UnionRect(&_InvClip.stRect[u8I], &_InvClip.stRect[u8J]);
                    RECT_SET(_InvClip.stRect[u8J], 0, 0, 0, 0);
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_InvalidateAllSuccessors
///  mark a specified window (and its successors) as invalidated
///
///  @param [in]       hwnd HWND          window handle
///
///  @return void
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_InvalidateAllSuccessors (HWND hwnd)
{
    HWND child, last_succ;
    if (hwnd == HWND_INVALID)
        return;

    //note: include self...
    last_succ = MApp_ZUI_API_GetLastSuccessor(hwnd);
    for (child = hwnd; child <= last_succ; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
    {
        //2007/12/4: for speed up IsSuccessor() checking: if (MApp_ZUI_API_IsSuccessor(hwnd, child))
        MApp_ZUI_API_InvalidateWindow(child);
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_SetTimer
///  add a timer to system, window will receive a MSG_TIMER message after a period time
///
///  @param [in]       hWnd HWND     window handle which wants to add a timer
///  @param [in]       u32id U32         timer ID for a single window handle
///  @param [in]       period u16    period time (in ms)
///
///  @return BOOLEAN TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_SetTimer (HWND hWnd, U32 u32id, U32 period)
{
    U32 i; //TIMER_STRUCT * timer;


    //printf("[WndSetTimer]  wnd = %d, id = %d, period = %ld\n", hWnd, u32id, period);

    if (hWnd == HWND_INVALID)
        return FALSE;

    for (i = 0; i < ZUI_MAX_TIMER_COUNT; i++)
    {
        if (_MenuMsgQueue.Timers[i].owner == hWnd &&
            _MenuMsgQueue.Timers[i].u32ID == u32id) //dup
        {
            //if exist.. reset timer value
            _MenuMsgQueue.Timers[i].u32PassTime = 0;
            _MenuMsgQueue.Timers[i].u32Period = period;
            return TRUE;
        }
    }

    for (i = 0; i < ZUI_MAX_TIMER_COUNT; i++)
    {
        if (_MenuMsgQueue.Timers[i].owner == HWND_INVALID) //not in used...
        {
            _MenuMsgQueue.Timers[i].owner = hWnd;
            _MenuMsgQueue.Timers[i].u32ID = u32id;
            _MenuMsgQueue.Timers[i].u32PassTime = 0;
            _MenuMsgQueue.Timers[i].u32Period = period;
            //printf("\n[WndSetTimer] find slot[%d], wnd = %d, id = %d, period = %ld", u16i, timer->owner, timer->s16ID, timer->u32Period);
            return TRUE;
        }
    }
    return FALSE; //not available timer...//not available timer...
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_KillTimer
///  unregister a timer
///
///  @param [in]       hWnd HWND     target window handle
///  @param [in]       id U32     timer ID
///
///  @return BOOLEAN TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_KillTimer (HWND hWnd, U32 id)
{
    U32 i;//TIMER_STRUCT * timer;

    //printf("[KillTimer] hwnd = %d, id = %d\n", hWnd, id);

    if (hWnd == HWND_INVALID)
        return FALSE;

    for (i = 0; i < ZUI_MAX_TIMER_COUNT; i++)
    {
        if (_MenuMsgQueue.Timers[i].owner != hWnd ||
            _MenuMsgQueue.Timers[i].u32ID != id)
            continue;

        //printf("\n[WndSetTimer] find slot[%d], wnd = %d, id = %d, period = %ld", u16i, timer->owner, timer->s16ID, timer->u32Period);
        _MenuMsgQueue.Timers[i].owner = HWND_INVALID;
        return TRUE;
    }
    //printf("\n[KillTimer] leave");
    return FALSE; //timer not found....
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_ResetTimer
///  change a timer period and reset status to zero
///
///  @param [in]       hWnd HWND     target window handle
///  @param [in]       id U32     timer ID
///
///  @return BOOLEAN TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_ResetTimer (HWND hWnd, U32 id)
{
    U32 i; //TIMER_STRUCT * timer;

    //printf("[ResetTimer] hwnd = %d, id = %d\n", hWnd, id);

    if (hWnd == HWND_INVALID)
        return FALSE;

    for (i = 0; i < ZUI_MAX_TIMER_COUNT; i++)
    {
        if (_MenuMsgQueue.Timers[i].owner != hWnd ||
            _MenuMsgQueue.Timers[i].u32ID != id)
            continue;

        _MenuMsgQueue.Timers[i].u32PassTime = 0;
	    _MenuMsgQueue.u32PrevTimerEntered = msAPI_Timer_GetTime0();
        //2007/12/15: don't support change it in this function:
        //        _MenuMsgQueue.Timers[i].u16Period = period;
        return TRUE;
    }
    return FALSE; //timer not found....
}

void MApp_ZUI_API_ResetAllTimer(void)
{
    //printf("[ResetAllTimer]\n");

    U32 i;

    for (i = 0; i < ZUI_MAX_TIMER_COUNT; i++)
    {
        if (_MenuMsgQueue.Timers[i].owner == HWND_INVALID) //not in used...
            continue;

        MApp_ZUI_API_ResetTimer(_MenuMsgQueue.Timers[i].owner, _MenuMsgQueue.Timers[i].u32ID);
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_IsExistTimer
///  check a timer is existed or not
///
///  @param [in]       hWnd HWND     target window handle
///  @param [in]       id U32     timer ID
///
///  @return BOOLEAN TRUE for exist, FALSE for not
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_IsExistTimer (HWND hWnd, U32 id)
{
    U32 i; //TIMER_STRUCT * timer;

    if (hWnd == HWND_INVALID)
        return FALSE;

    for (i = 0; i < ZUI_MAX_TIMER_COUNT; i++)
    {
        if (_MenuMsgQueue.Timers[i].owner != hWnd ||
            _MenuMsgQueue.Timers[i].u32ID != id)
            continue;

        return TRUE;
    }
    return FALSE; //timer not found....
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_WindowProcOnTimer
///  timer routine if message queue is empty (idle)
///     check and update status of times, invoke them if times up
///
///  @return BOOLEAN TRUE for execute at last one timer, FALSE for execute nothing
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN _MApp_ZUI_API_WindowProcOnTimer(void)
{
    BOOLEAN bRet = FALSE;
    //static U8 i;
    TIMER_STRUCT * timer;
    //U32 now_time; // = msAPI_Timer_GetTime0();
    U32 diff_time; // = now_time - _MenuMsgQueue.u32PrevTimerEntered;

    /*/note: tick count will reset to zero,
    //  so we assume the longest period is ZUI_TIMER_UNIT_MS*5
    now_time = msAPI_Timer_GetTime0();
    diff_time = now_time - _MenuMsgQueue.u32PrevTimerEntered;
    if (diff_time > ZUI_TIMER_UNIT_MS*1000)
        diff_time = ZUI_TIMER_UNIT_MS*2;
    _MenuMsgQueue.u32PrevTimerEntered = now_time;
    */
    diff_time = msAPI_Timer_DiffTimeFromNow(_MenuMsgQueue.u32PrevTimerEntered);
    _MenuMsgQueue.u32PrevTimerEntered = msAPI_Timer_GetTime0();

    for (timer = _MenuMsgQueue.Timers; timer < _MenuMsgQueue.Timers+ZUI_MAX_TIMER_COUNT; timer++)
    {
        //PRINT("\n[Note] loop timer %d", (U16)i);
        if (timer->owner == HWND_INVALID)
            continue;

        bRet = TRUE;
        timer->u32PassTime += diff_time;
        //PRINT("\n[Note] find timer[%d], owner = %d, id = %ld, period=%ld, passtime = %ld", i, timer->owner, timer->s32ID, timer->u32Period, timer->u32PassTime);
        if (timer->u32PassTime >= timer->u32Period)
        {
            timer->u32PassTime = 0; //note: reset pass time... -= timer->u32Period;
            //PRINT("\n[Note] send timer msg to window %d", timer->owner);
            MApp_ZUI_API_SendMessage(timer->owner, MSG_TIMER, timer->u32ID);
        }
    }
    return bRet;
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetFocus
///  query the focus window
///
///  @return HWND focus window, HWND_INVALiD for no focus
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
HWND MApp_ZUI_API_GetFocus(void)
{
    //printf("\n[Note] focus window = %d", _FocusHwnd);
    return _FocusHwnd;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_SetFocus
///  change focus to a specific window/control
///
///  @param [in]       hwnd HWND     window handle, could be HWND_INVALID (for clear focus)
///
///  @return BOOLEAN true for success, false for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_SetFocus(HWND hwnd)
{
    HWND prev = _FocusHwnd;
    HWND h, last_succ;

    //printf("[setfocus] = %u\n", hwnd);

    if (prev == hwnd)
        return FALSE; //nothing happened...
    if (hwnd != HWND_INVALID)
    {
        //U16 state = GETWNDINITSTATE(hwnd);
        if ((GETWNDINITSTATE(hwnd)&WS_FOCUSABLE) == 0 ||
            (GETWNDDISABLE(hwnd)) ||
            (!GETWNDVISIBLE(hwnd)) )
        {
            return FALSE; //nothing happened...
        }
    }

    //printf("[setfocus]2\n");
    if (prev != HWND_INVALID)
    {
        MApp_ZUI_API_PostMessage(prev, MSG_NOTIFY_KILLFOCUS, 0);

        //invalidate previous rect
        MApp_ZUI_API_InvalidateWindow(prev);

        //note: we assume if one window get focus, the child will be painted as focus style..
        last_succ = MApp_ZUI_API_GetLastSuccessor(prev);
        for (h = prev+1; h <= last_succ; h++)//for (h = prev+1; h < HWND_MAX; h++)
        {
            //2007/12/4: for speed up IsSuccessor() checking: if (MApp_ZUI_API_IsSuccessor(prev, h))
            {
                if (GETWNDVISIBLE(h))
                {
                    MApp_ZUI_API_InvalidateWindow(h);
                }
            }
        }
    }

    _FocusHwnd = hwnd; //could be HWND_INVALID
    if (hwnd != HWND_INVALID)
    {
        //printf("[setfocus]3\n");
        MApp_ZUI_API_PostMessage(hwnd, MSG_NOTIFY_SETFOCUS, 0);

        //invalidate current rect
        MApp_ZUI_API_InvalidateWindow(hwnd);

        //note: we assume if one window get focus, the child will be painted as focus style..
        last_succ = MApp_ZUI_API_GetLastSuccessor(hwnd);
        for (h = hwnd+1; h <= last_succ; h++) //for (h = hwnd+1; h < HWND_MAX; h++)
        {
            //2007/12/4: for speed up IsSuccessor() checking: if (MApp_ZUI_API_IsSuccessor(hwnd, h))
            {
                if (GETWNDVISIBLE(h))
                {
                    MApp_ZUI_API_InvalidateWindow(h);
                }
            }
        }
    }

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_StoreFocusCheckpoint
///  store the focus window to checkpoint
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_StoreFocusCheckpoint(void)
{
    _CheckpointFocusHwnd = _FocusHwnd;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_RestoreFocusCheckpoint
///  restore the focus window to previous checkpoint
///
///  @return HWND focus window, HWND_INVALiD for no focus
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
HWND MApp_ZUI_API_RestoreFocusCheckpoint(void)
{
    MApp_ZUI_API_SetFocus(_CheckpointFocusHwnd);
    return _FocusHwnd;
}

///////////////////////////////////////////////////////////////////////////////
///  global  HWND MApp_ZUI_API_GetFocusCheckpoint(void)
///  get the focus window to previous checkpoint
///
///  @return HWND focus window, HWND_INVALiD for no focus
///
///  @author MStarSemi @date 2009/03/25
///////////////////////////////////////////////////////////////////////////////
HWND MApp_ZUI_API_GetFocusCheckpoint(void)
{
    return _CheckpointFocusHwnd;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_SetPaneFocus
///  change focus to a container
///     if this window didn't have WS_FOCUSABLE attribute,
///     then find the first visible, enabled and focusable successor
///
///  @param [in]       hwnd HWND     window handle, could be HWND_INVALID (for clear focus)
///
///  @return BOOLEAN true for success, false for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_SetPaneFocus(HWND hwnd)
{
    //WINDOWDATA * win; //, *winchild;
    HWND child, last_succ;

    if (hwnd == HWND_INVALID)
    {
        MApp_ZUI_API_SetFocus(HWND_INVALID); //if no child, then no focus...
        return;
    }

    //printf("[pfocus]1\n");

    if (GETWNDINITSTATE(hwnd) & WS_FOCUSABLE)       // if it is focusable, set focus to it, otherwise, to first child window which is focusable
    {
        //printf("[pfocus]2\n");
        MApp_ZUI_API_SetFocus(hwnd);
    }
    else
    {
        //printf("[pfocus]3\n");
        //note: we assume all the children are sorted after their parent..
        last_succ = MApp_ZUI_API_GetLastSuccessor(hwnd);
        for (child = hwnd+1; child <= last_succ; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
        {
            //2007/12/4: for speed up IsSuccessor() checking: if (MApp_ZUI_API_IsSuccessor(hwnd, child))
            //for each child, try to set focus...
            //   if success, then done, else try the next child
            if (MApp_ZUI_API_SetFocus(child))
                return;
        }
        //printf("[pfocus]4\n");
        MApp_ZUI_API_SetFocus(HWND_INVALID); //if no child, then no focus...
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_SetFocusByNav
///  change focus by navigation keys
///     if this window didn't have WS_FOCUSABLE attribute (or invisible, disabled),
///     then follow the navigation direction, find the first visible, enabled and focusable window
///
///  @param [in]       hwnd HWND     window handle, could be HWND_INVALID (for clear focus)
///  @param [in]       nav U8        navigation direction
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_SetFocusByNav(HWND hwnd, U8 nav)
{
    U32 test;
    HWND next;

    if (hwnd == HWND_INVALID)
    {
        //MApp_ZUI_API_SetFocus(HWND_INVALID); //if no child, then no focus...
        return;
    }
    //win = &g_GUI_WindowList[hwnd];

    //printf("[pfocus]1\n");
    for (test = 0; test < 100; test++)
    {
        if (GETWNDNAVI(hwnd) == 0)
        {
            //no navigation data
            return;
        }
        next = GETWNDNAVI(hwnd)[nav];
        if (next == hwnd)
        {
            //next = self: end search
            return;
        }
        if ((GETWNDINITSTATE(next) & WS_FOCUSABLE) &&
            GETWNDVISIBLE(next) &&
            !GETWNDDISABLE(next))
        {
            //focusable, visible and enable: set focus!!
            MApp_ZUI_API_SetFocus(next);
            return;
        }
        hwnd = next;
    }
    if (test == 100)
    {
        ZUI_DBG_FAIL(printf("[ZUI]FNAVL\n"));
        ABORT();
    }

}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_IsSuccessor
///  determine if a control is the successor of another control
///
///  @param [in]       parent HWND     parent window handle
///  @param [in]       child HWND     child window handle
///
///  @return BOOLEAN  TRUE for yes, FALSE for no
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN  MApp_ZUI_API_IsSuccessor(HWND parent, HWND child)
{
    //HWND hParent;
    if (parent == HWND_INVALID || child == HWND_INVALID)
        return FALSE;

    //2007/12/4: for speed up IsSuccessor() checking: child must be in [parent+1, last_successor(parent)] range
    return (parent < child && child <= MApp_ZUI_API_GetLastSuccessor(parent));
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_IsParentFocused
///  determine if a control is in focused state (because of the parent state)
///
///  @param [in]       hwnd HWND     window handle
///
///  @return BOOLEAN  TRUE for yes, FALSE for no
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN  MApp_ZUI_API_IsParentFocused(HWND hwnd)
{
    return MApp_ZUI_API_IsSuccessor(GETWNDFOCUS(), hwnd);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_CountChildren
///  count the children of hwnd
///
///  @param [in]       hParent HWND     window handle
///
///  @return U8    hwnd of parent
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
U8 MApp_ZUI_API_CountChildren(HWND hParent)
{
    U8 ret = 0;
    HWND child, last_succ;
    last_succ = MApp_ZUI_API_GetLastSuccessor(hParent);
    for (child = hParent+1; child <= last_succ; child++)
    {
        if (MApp_ZUI_API_GetParent(child) == hParent)
            ret++;
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetChildIndex
///  get the child index of his parent
///
///  @param [in]       hParent HWND     window handle
///
///  @return U8    hwnd of parent
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S16 MApp_ZUI_API_GetChildIndex(HWND hwnd)
{
    HWND hParent = MApp_ZUI_API_GetParent(hwnd);

    S16 s16Index = 0;
    HWND child, last_succ;
    last_succ = MApp_ZUI_API_GetLastSuccessor(hParent);
    for (child=hParent+1; child<=last_succ; child++)
    {
        if (MApp_ZUI_API_GetParent(child) != hParent)
            continue;
        if ( child == hwnd )
            return s16Index;
        s16Index++;
    }

    return s16Index;
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_AllocateVarData
///  allocate visible/disable bit array, and movable windows array
///
///  @return BOOLEAN  TRUE for success, FALSE for no
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN _MApp_ZUI_API_AllocateVarData(void)
{
    //use HWND_MAX for allocating "visible" and "enable" data...
    U16 u16i;
    U16 ulong_size = (HWND_MAX+32)/32;
    HWND hwnd;
    //need to use msAPI_Memory to save XDATA??
    if (ulong_size > ZUI_VARDATA_MAXBYTESIZE)
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALSIZE\n"));
        ABORT();
        return FALSE;
    }
    _VarDataVisible = _VarDataTemp;
    _VarDataDisable = _VarDataTemp+ulong_size;
    //memset(_VarDataVisible, 0, ulong_size);
    //memset(_VarDataDisable, 0, ulong_size);
    for (u16i = 0; u16i < ulong_size; u16i++)
    {
        _VarDataVisible[u16i] = 0xFFFFFFFF; //2008/4/12: visible for general cases
        _VarDataDisable[u16i] = 0;
    }
    for (hwnd = 0; hwnd < HWND_MAX; hwnd++)
    {
        if ((GETWNDINITSTATE(hwnd)&WS_DISABLED) != 0)
        {
            SETWNDDISABLE(hwnd);
        }
        if ((GETWNDINITSTATE(hwnd)&WS_VISIBLE) == 0)
        {
            SETWNDINVISIBLE(hwnd);
        }
    }
    #ifdef ZUI_MAX_MOVABLE_HWND
    //initialize for initial position
    #if ZUI_ALL_MOVABLE_HWND
    if(g_GUI_WindowPositionList!=NULL)
    {
        for (u16i = 0; u16i < ZUI_MAX_MOVABLE_HWND; u16i++)
        {
            _VarDataMovableRect[u16i] = GETWNDINITRECT(u16i);
        }
        #else
        for (u16i = 0; u16i < ZUI_MAX_MOVABLE_HWND; u16i++)
        {
            _VarDataMovableRect[u16i].hwnd = HWND_INVALID;
        }
        #endif
    }
    #endif //ZUI_MAX_MOVABLE_HWND

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_IsWindowVisible
///  determine the window/control is shown or hidden
///
///  @param [in]       hWnd HWND     window handle
///
///  @return BOOLEAN TRUE for shown, FALSE for invisible
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN  MApp_ZUI_API_IsWindowVisible (HWND hWnd)
{
    if (hWnd == HWND_INVALID)
        return FALSE;

    if (_VarDataVisible == 0)
    {
        ZUI_DBG_FAIL(printf("[ZUI]WVAL\n"));
        ABORT();
        return FALSE;
    }

    return GETWNDVISIBLE(hWnd);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_ShowWindow
///  change window/control to visible/invisible
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       iCmdShow U32     SW_SHOW or SW_HIDE
///
///  @return BOOLEAN  TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN  MApp_ZUI_API_ShowWindow (HWND hwnd, U32 iCmdShow)
{
    HWND child, last_succ; //2008/4/12: get last successor once
    BOOLEAN bKillFocus = FALSE;

    if (hwnd == HWND_INVALID)
        return FALSE;

    //printf("\n[ShowWindow] showwindow %d, iCmdShow = %bu, visible = %bu", hwnd, iCmdShow, GETWNDVISIBLE(hwnd));
    if ( GETWNDVISIBLE(hwnd) )
    {
        if (iCmdShow != SW_SHOW)
        {
            SETWNDINVISIBLE(hwnd);
            if (GETWNDFOCUS() == hwnd)
                bKillFocus = TRUE;
            MApp_ZUI_API_PostMessage(hwnd, MSG_NOTIFY_HIDE, 0);

        }
    }
    else
    {
        if (iCmdShow != SW_HIDE)
        {
            SETWNDVISIBLE(hwnd);
            MApp_ZUI_API_PostMessage(hwnd, MSG_NOTIFY_SHOW, 0);
        }
    }

    //note: we cannot return if nothing changed...
    //        because sometimes parent is unchanged, but children changed...

    MApp_ZUI_API_InvalidateWindow(hwnd);
    //apply to children
    last_succ =  MApp_ZUI_API_GetLastSuccessor(hwnd);
    for (child = hwnd+1; child <= last_succ; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
    {
        //printf("\n[Note] hwnd = %d, child = %d, ischild = %d", hwnd, child, (U16)MApp_ZUI_API_IsChild(hwnd, child));
        //2007/12/4: for speed up IsSuccessor() checking: if (MApp_ZUI_API_IsSuccessor(hwnd, child))
        {
            if ( GETWNDVISIBLE(child) )
            {
                if (iCmdShow != SW_SHOW)
                {
                    SETWNDINVISIBLE(child);
                    if (GETWNDFOCUS() == child)
                        bKillFocus = TRUE;
                    MApp_ZUI_API_PostMessage(child, MSG_NOTIFY_HIDE, 0);

                }
            }
            else
            {
                if (iCmdShow != SW_HIDE)
                {
                    SETWNDVISIBLE(child);
                    MApp_ZUI_API_PostMessage(child, MSG_NOTIFY_SHOW, 0);
                }
            }

            if(hwnd != HWND_MAINFRAME)
                MApp_ZUI_API_InvalidateWindow(child);
        }
    }

    if (bKillFocus)
    {
        MApp_ZUI_API_SetFocus(HWND_INVALID);
    }

    return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_EnableWindow
///  enable/disable a window
///
///  @param [in]       hwnd HWND     target window handle
///  @param [in]       fEnable BOOLEAN     TRUE for enable, FALSE for disable
///
///  @return BOOLEAN TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN  MApp_ZUI_API_EnableWindow (HWND hwnd, BOOLEAN fEnable)
{
    HWND child, last_succ; //2008/4/12: get last successor once
    BOOLEAN bKillFocus = FALSE;

    if (hwnd == HWND_INVALID)
        return FALSE;

    if ( GETWNDDISABLE(hwnd) )
    {
        if (fEnable)
        {
            SETWNDENABLE(hwnd);
            MApp_ZUI_API_PostMessage(hwnd, MSG_NOTIFY_ENABLE, 0);

        }
    }
    else
    {
        if (!fEnable)
        {
            SETWNDDISABLE(hwnd);
            if (GETWNDFOCUS() == hwnd)
                bKillFocus = TRUE;
            MApp_ZUI_API_PostMessage(hwnd, MSG_NOTIFY_DISABLE, 0);
        }
    }

    //note: we cannot return if nothing changed...
    //        because sometimes parent is unchanged, but children changed...
    if (GETWNDVISIBLE(hwnd))
    {
        MApp_ZUI_API_InvalidateWindow(hwnd);
    }

    //apply to children
    last_succ = MApp_ZUI_API_GetLastSuccessor(hwnd);
    for (child = hwnd+1; child <= last_succ; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
    {
        //printf("\n[Note] hwnd = %d, child = %d, ischild = %d", hwnd, child, (U16)MApp_ZUI_API_IsChild(hwnd, child));
        //2007/12/4: for speed up IsSuccessor() checking: if (MApp_ZUI_API_IsSuccessor(hwnd, child))
        {
            if ( GETWNDDISABLE(child) )
            {
                if (fEnable)
                {
                    SETWNDENABLE(child);
                    MApp_ZUI_API_PostMessage(child, MSG_NOTIFY_ENABLE, 0);

                }
            }
            else
            {
                if (!fEnable)
                {
                    SETWNDDISABLE(child);
                    if (GETWNDFOCUS() == child)
                        bKillFocus = TRUE;
                    MApp_ZUI_API_PostMessage(child, MSG_NOTIFY_DISABLE, 0);
                }
            }

            MApp_ZUI_API_InvalidateWindow(child);
        }
    }

    if (bKillFocus)
    {
        MApp_ZUI_API_SetFocus(HWND_INVALID);
    }

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_IsWindowEnabled
///  determine if window is enabled
///
///  @param [in]       hWnd HWND     target window handle
///
///  @return BOOLEAN TRUE for enabled, FALSE for disabled
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN  MApp_ZUI_API_IsWindowEnabled (HWND hWnd)
{
    if (hWnd == HWND_INVALID)
        return FALSE;

    return (GETWNDDISABLE(hWnd) == 0);
}

#ifdef ZUI_MAX_MOVABLE_HWND
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_MoveWindowByOffset
///  change window position or size by offset value of top left width hight
///
///  @param [in]       hWnd HWND         target window handle
///  @param [in]       S16 LeftOffset      new rectangle Offset value compared to original rectangle
///  @param [in]       S16 TopOffset      new rectangle Offset value compared to original rectangle
///  @param [in]       S16 WidthOffset   new rectangle Offset value compared to original rectangle
///  @param [in]       S16 HeightOffset  new rectangle Offset value compared to original rectangle
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void  MApp_ZUI_API_MoveWindowByOffset (HWND hWnd, S16 LeftOffset, S16 TopOffset, S16 WidthOffset, S16 HeightOffset )
{
    const RECT * target_rect;
    RECT move_new_rect;
    target_rect = &GETWNDINITRECT(hWnd);
    move_new_rect.left = target_rect->left+LeftOffset;
    move_new_rect.top = target_rect->top+TopOffset;
    move_new_rect.width = target_rect->width+WidthOffset;
    move_new_rect.height = target_rect->height+HeightOffset;
    if(move_new_rect.left <0) {MS_DEBUG_MSG(printf("warning!! HWND x <0 /n"));}
    if(move_new_rect.top <0) {MS_DEBUG_MSG(printf("warning!! HWND y <0 /n"));}
    if(move_new_rect.width <=0) {MS_DEBUG_MSG(printf("warning!! HWND width <=0 /n"));}
    if(move_new_rect.height <=0) {MS_DEBUG_MSG(printf("warning!! HWND height <=0 /n"));}
    MApp_ZUI_API_MoveWindow(hWnd, &move_new_rect);
}
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_MoveWindow
///  change window position or size
///
///  @param [in]       hWnd HWND     target window handle
///  @param [in]       rc const RECT*  target rectangle position
///
///  @return BOOLEAN  TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN  MApp_ZUI_API_MoveWindow (HWND hWnd, const RECT * rc)
{
#if ZUI_ALL_MOVABLE_HWND
    if (hWnd >= ZUI_MAX_MOVABLE_HWND)
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALMOV3\n"));
        //ABORT();
        return FALSE;
    }
    if (GETWNDVISIBLE(hWnd))
    {
        //MApi_ZUI_InvalidateRect(&_VarDataMovableRect[i].rect);
        MApp_ZUI_API_InvalidateWindow(hWnd);
        _VarDataMovableRect[hWnd] = *rc;
        MApp_ZUI_API_InvalidateRect(rc);
    }
    else
    {
        _VarDataMovableRect[hWnd] = *rc;
    }
#else
    U32 i, j = 0xFF;
    for (i = 0; i < ZUI_MAX_MOVABLE_HWND; i++)
    {
        if (_VarDataMovableRect[i].hwnd == hWnd)
        {
            //_VarDataMovableRect[i].rect = *rc;
            break;
        }
        if (j == 0xFF && _VarDataMovableRect[i].hwnd== HWND_INVALID)
        {
            j = i;
        }
    }

    if ( i == ZUI_MAX_MOVABLE_HWND )
    {
        if ( j == 0xFF )
        {
            ZUI_DBG_FAIL(printf("[ZUI]ALMOV1\n"));
            ABORT();
            return FALSE;
        }
        i = j;

    }

    if (GETWNDVISIBLE(hWnd))
    {
        //MApp_ZUI_API_InvalidateRect(&_VarDataMovableRect[i].rect);
        MApp_ZUI_API_InvalidateWindow(hWnd);
        _VarDataMovableRect[i].hwnd = hWnd;
        _VarDataMovableRect[i].rect = *rc;
        MApp_ZUI_API_InvalidateRect(rc);
    }
    else
    {
        _VarDataMovableRect[i].hwnd = hWnd;
        _VarDataMovableRect[i].rect = *rc;
    }
#endif //ZUI_ALL_MOVABLE_HWND

    MApp_ZUI_API_PostMessage(hWnd, MSG_NOTIFY_MOVED, 0);

    return TRUE;
}

#if ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
BOOLEAN MApp_ZUI_API_MoveAllSuccessors (HWND hWnd, S16 x, S16 y)
{
#if ZUI_ALL_MOVABLE_HWND
    if (hWnd >= ZUI_MAX_MOVABLE_HWND)
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALMOV4\n"));
        //ABORT();
        return FALSE;
    }
    { //2007/12/26: invalide all visible children....
        HWND child, last_succ; //2008/4/12: get last successor once
        last_succ = GETWNDLASTSUCCESSOR(hWnd);
        for (child = hWnd; child <= last_succ; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
        {
            if (GETWNDVISIBLE(child))
                MApp_ZUI_API_InvalidateWindow(child);
        }
    }
    {
        S32 s32OffsetX = (S32)x - GETWNDINITRECT(hWnd).left;
        S32 s32OffsetY = (S32)y - GETWNDINITRECT(hWnd).top;
        HWND child, last_succ;
        last_succ = GETWNDLASTSUCCESSOR(hWnd);

        // Added by coverity_0166
        if (last_succ >= ZUI_MAX_MOVABLE_HWND)
        {
            last_succ = (ZUI_MAX_MOVABLE_HWND -1);
        }

        for (child = hWnd; child <= last_succ && child < ZUI_MAX_MOVABLE_HWND; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
        {
            _VarDataMovableRect[child] = GETWNDINITRECT(child);
            _VarDataMovableRect[child].left += s32OffsetX;
            _VarDataMovableRect[child].top += s32OffsetY;
        }
        _VarDataMovableRect[hWnd].width = -1; //2009/01/19: mark as moving successor root
        _VarDataMovableRect[hWnd].height = -1;
    }
    {
        HWND child, last_succ; //2008/4/12: get last successor once
        last_succ = GETWNDLASTSUCCESSOR(hWnd);
        for (child = hWnd; child <= last_succ; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
        {
            if (GETWNDVISIBLE(child))
                MApp_ZUI_API_InvalidateWindow(child);
        }
    }
#else
    U32 i, j = 0xFF;
    for (i = 0; i < ZUI_MAX_MOVABLE_HWND; i++)
    {
        if (_VarDataMovableRect[i].hwnd == hWnd)
        {
            //_VarDataMovableRect[i].rect = *rc;
            break;
        }
        if (j == 0xFF && _VarDataMovableRect[i].hwnd== HWND_INVALID)
        {
            j = i;
        }
    }

    if ( i == ZUI_MAX_MOVABLE_HWND )
    {
        if ( j == 0xFF )
        {
            ZUI_DBG_FAIL(printf("[ZUI]ALMOV2\n"));
            ABORT();
            return FALSE;
        }
        i = j;
    }

    { //2007/12/26: invalide all visible children....
        HWND child, last_succ; //2008/4/12: get last successor once
        last_succ = MApp_ZUI_API_GetLastSuccessor(hWnd);
        for (child = hWnd; child <= last_succ; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
        {
            if (GETWNDVISIBLE(child))
                MApp_ZUI_API_InvalidateWindow(child);
        }
    }
    _VarDataMovableRect[i].hwnd = hWnd;
    RECT_SET(_VarDataMovableRect[i].rect, x, y, -1, -1);
    {
        HWND child, last_succ; //2008/4/12: get last successor once
        last_succ = MApp_ZUI_API_GetLastSuccessor(hWnd);
        for (child = hWnd; child <= last_succ; child++) //for (child = hwnd+1; child < HWND_MAX; child++)
        {
            if (GETWNDVISIBLE(child))
                MApp_ZUI_API_InvalidateWindow(child);
        }
    }
#endif //ZUI_ALL_MOVABLE_HWND

    MApp_ZUI_API_PostMessage(hWnd, MSG_NOTIFY_MOVED, 0); //only send to container if move all successors...

    return TRUE;
}
#endif //ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
#endif //ZUI_MAX_MOVABLE_HWND


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetWindowRect
///  query window position and size
///
///  @param [in]       hwnd HWND     target window handle
///  @param [out]      rect RECT *    window position rectangle
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_GetWindowRect(HWND hwnd, RECT * rect)
{
#if ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
    RECT rect_hwnd;
#endif

    if (hwnd == HWND_INVALID)
        return;

#if ZUI_ALL_MOVABLE_HWND

    if (hwnd >= ZUI_MAX_MOVABLE_HWND)
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALMOV5\n"));
        //ABORT();
        return;
    }
    *rect = _VarDataMovableRect[hwnd];
#if ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
    if (rect->width < 0 || rect->height < 0)
    {
        MApp_ZUI_API_GetWindowInitialRect(hwnd, &rect_hwnd);
        rect->width = rect_hwnd.width;
        rect->height = rect_hwnd.height;
    }
#endif


#else


#ifdef ZUI_MAX_MOVABLE_HWND
    U32 i;

#if ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
    MApp_ZUI_API_GetWindowInitialRect(hwnd, &rect_hwnd);
#endif

    for (i = 0; i < ZUI_MAX_MOVABLE_HWND; i++)
    {
#if ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
        if (_VarDataMovableRect[i].hwnd == HWND_INVALID)
            continue;

        if (_VarDataMovableRect[i].rect.width < 0 ||
            _VarDataMovableRect[i].rect.height < 0)
        {
            HWND hParent = _VarDataMovableRect[i].hwnd;
            //include parent itself....
            if (hParent <= hwnd && hwnd <= MApp_ZUI_API_GetLastSuccessor(hParent))
            {
                RECT rect_parent;
                MApp_ZUI_API_GetWindowInitialRect(hParent, &rect_parent);
                RECT_SET((*rect),
                    _VarDataMovableRect[i].rect.left-rect_parent.left+rect_hwnd.left,
                    _VarDataMovableRect[i].rect.top-rect_parent.top+rect_hwnd.top,
                    rect_hwnd.width,
                    rect_hwnd.height);
                return;
            }
            else
            {
                continue;
            }
        }
#endif //ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
        if (_VarDataMovableRect[i].hwnd == hwnd)
        {
            *rect = _VarDataMovableRect[i].rect;
            return;
        }
    }
#endif //ZUI_MAX_MOVABLE_HWND
    *rect = rect_hwnd; //GETWNDINITRECT(hwnd);


#endif //ZUI_ALL_MOVABLE_HWND

}

#if ZUI_ALL_MOVABLE_HWND
///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_RestoreWindowRectSuccessor
///  restore a specified window index
///
///  @param [in]       hwnd HWND     window hwnd
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
static void _MApp_ZUI_API_RestoreWindowRectSuccessor(HWND hwnd)
{
#if ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
    //because we don't know is that all successors are visible or not
    //    so we just invalid them
    if (_VarDataMovableRect[hwnd].width < 0 ||
        _VarDataMovableRect[hwnd].height < 0)
    {
        MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
        _VarDataMovableRect[hwnd] = GETWNDINITRECT(hwnd);
        MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
    }
    else
#endif //ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
    {
        if (GETWNDVISIBLE(hwnd))
        {
            MApp_ZUI_API_InvalidateWindow(hwnd);
            _VarDataMovableRect[hwnd] = GETWNDINITRECT(hwnd);
            MApp_ZUI_API_InvalidateWindow(hwnd);
        }
        else
        {
            _VarDataMovableRect[hwnd] = GETWNDINITRECT(hwnd);
        }
    }

    MApp_ZUI_API_PostMessage(hwnd, MSG_NOTIFY_MOVED, 0);
}
#else
///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_RestoreWindowRectIndex
///  restore a specified window index
///
///  @param [in]       idx U32     window index
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
static void _MApp_ZUI_API_RestoreWindowRectIndex(U8 idx)
{
    HWND hwnd = _VarDataMovableRect[idx].hwnd;

#if ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
    //because we don't know is that all successors are visible or not
    //    so we just invalid them
    if (_VarDataMovableRect[idx].rect.width < 0 ||
        _VarDataMovableRect[idx].rect.height < 0)
    {
        MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
        _VarDataMovableRect[idx].hwnd = HWND_INVALID;
        MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
    }
    else
#endif //ZUI_SUPPORT_MOVE_ALL_SUCCESSORS
    {
        _VarDataMovableRect[idx].hwnd = HWND_INVALID;
        if (GETWNDVISIBLE(hwnd))
        {
            RECT rect_hwnd;
            MApp_ZUI_API_GetWindowInitialRect(hwnd, &rect_hwnd);
            MApp_ZUI_API_InvalidateRect(&_VarDataMovableRect[idx].rect);
            MApp_ZUI_API_InvalidateRect(&rect_hwnd);
        }
    }

    MApp_ZUI_API_PostMessage(hwnd, MSG_NOTIFY_MOVED, 0);
}
#endif //ZUI_ALL_MOVABLE_HWND

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_RestoreAllWindowRect
///  restore the positons of all movable windows
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_RestoreAllWindowRect(void)
{
    //clear _VarDataMovableRect[] to restore all window to init position..

    U32 i;

#if ZUI_ALL_MOVABLE_HWND
    for (i = 0; i < ZUI_MAX_MOVABLE_HWND; i++)
    {
        if (memcmp(
            &_VarDataMovableRect[i], &GETWNDINITRECT(i), sizeof(RECT)) != 0)
        {
            _MApp_ZUI_API_RestoreWindowRectSuccessor(i);
        }
    }
#else
    for (i = 0; i < ZUI_MAX_MOVABLE_HWND; i++)
    {
        if (_VarDataMovableRect[i].hwnd != HWND_INVALID )
        {
            _MApp_ZUI_API_RestoreWindowRectIndex(i);
        }
    }
#endif //ZUI_ALL_MOVABLE_HWND
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_RestoreWindowRect
///  restore a specified movable window
///
///  @param [in]       hwnd HWND     target window handle
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_RestoreWindowRect(HWND hwnd)
{
    //restore specific window to init position..

    if(hwnd >=ZUI_MAX_MOVABLE_HWND)
        return;
#if ZUI_ALL_MOVABLE_HWND
    {
        if (memcmp(
            &_VarDataMovableRect[hwnd], &GETWNDINITRECT(hwnd), sizeof(RECT)) != 0)
        {
            _MApp_ZUI_API_RestoreWindowRectSuccessor(hwnd);
        }
    }
#else
    U32 i;
    for (i = 0; i < ZUI_MAX_MOVABLE_HWND; i++)
    {
        if (_VarDataMovableRect[i].hwnd == hwnd )
        {
            _MApp_ZUI_API_RestoreWindowRectIndex(i);
        }
    }
#endif //ZUI_ALL_MOVABLE_HWND
}

U32 MApp_ZUI_API_GetWindowData(HWND hwnd)
{
    if (hwnd == HWND_INVALID)
        return 0;
    return (U32) GETWNDDATA(hwnd);
}

U8 MApp_ZUI_API_GetWindowProcId(HWND hwnd)
{
    if (hwnd == HWND_INVALID)
        return 0;
    return GETWNDPROCID(hwnd);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CheckNeedDrawing
///     determine drawing (GE/GOP operation) is needed or not
///
///  @return BOOLEAN true for needed
///
///  @author MStarSemi @date 2007/3/2
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_CheckNeedDrawing(void)
{
    switch (_eZUIState)
    {
        case E_ZUI_STATE_TERMINATE:
        case E_ZUI_STATE_TRANSEFF_DOING:
        case E_ZUI_STATE_TRANSEFF_END:
            return TRUE;

        case E_ZUI_STATE_RUNNING:
            //something need to paint, or some message inside the queue...
            if (_InvClip.bNeedRepaint)
                return TRUE;
            if (_MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxEnd].hwnd != HWND_INVALID)
                return TRUE;
            if (msAPI_Timer_DiffTimeFromNow(_MenuMsgQueue.u32PrevTimerEntered) > ZUI_LOW_FREQ_TIMER_THRESHOLD)
                return TRUE;
            break;

        default:
            break;
    }

    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_WindowProcOnIdle
///  idle handler for window system,
///      will check invalidate information, repaint invalidated region
///
///  @return BOOLEAN true for success
///
///  @author MStarSemi @date 2007/3/2
///////////////////////////////////////////////////////////////////////////////
BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void)
{

    if (_InvClip.bNeedRepaint)
    {
        #ifdef ZUI_REPAINT_TIME_DEBUG_THRESHOLD
        U32 now = msAPI_Timer_GetTime0();
        #endif //ZUI_REPAINT_TIME_DEBUG_THRESHOLD

        INVALIDATE_CLIP sCurInvClip = _InvClip;
        _InvClip.bNeedRepaint = FALSE;

         _MApp_ZUI_CTL_MainFramePaint(HWND_MAINFRAME, (WPARAM *)((void*)&sCurInvClip));

        #ifdef ZUI_REPAINT_TIME_DEBUG_THRESHOLD
        if (ZUI_REPAINT_TIME_DEBUG_THRESHOLD <= msAPI_Timer_DiffTimeFromNow(now))
        {
            //printf("repaint diff=%u\n", (U16)msAPI_Timer_DiffTimeFromNow(now));
        }
        #endif //ZUI_REPAINT_TIME_DEBUG_THRESHOLD

    }
    return TRUE;
}

/*
{

    if (_InvClip.bNeedRepaint)
    {
        #ifdef ZUI_REPAINT_TIME_DEBUG_THRESHOLD
        U32 now = msAPI_Timer_GetTime0();
        #endif //ZUI_REPAINT_TIME_DEBUG_THRESHOLD

         _MApp_ZUI_CTL_MainFramePaint(HWND_MAINFRAME, (WPARAM *)&_InvClip);

        #ifdef ZUI_REPAINT_TIME_DEBUG_THRESHOLD
        if (ZUI_REPAINT_TIME_DEBUG_THRESHOLD <= msAPI_Timer_DiffTimeFromNow(now))
        {
            //printf("repaint diff=%u\n", (U16)msAPI_Timer_DiffTimeFromNow(now));
        }
        #endif //ZUI_REPAINT_TIME_DEBUG_THRESHOLD

        _InvClip.bNeedRepaint = FALSE;

    }
    return TRUE;
}
*/
///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_API_GetMessage
///  query the first message in the event queue
///
///  @param [out]       pMsg MSG       window message
///
///  @return BOOLEAN true for exist, false for empty message queue
///
///  @author MStarSemi @date 2007/3/2
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_GetMessage (PMSG pMsg)
{
    //PRINT("\n[Getmsg] start = %d, end = %d", _MenuMsgQueue.u32MsgQIdxStart, _MenuMsgQueue.u32MsgQIdxEnd);
    //PRINT("\n[Getmsg] hwnd = %d, msg = %d\n", _MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxEnd].hwnd, _MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxEnd].message);

    if (_MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxEnd].hwnd == HWND_INVALID)
        return FALSE;    // message queue is empty

    *pMsg = _MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxEnd];
    _MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxEnd].hwnd = HWND_INVALID;

    ++_MenuMsgQueue.u32MsgQIdxEnd;
    _MenuMsgQueue.u32MsgQIdxEnd %= ZUI_MSG_QUEUE_SIZE;
    //pMsg = &_MenuMsgQueue.MsgQueue[_MenuMsgQueue.u32MsgQIdxEnd];
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_API_IsExistRemainingMessage
///  query the first message in the event queue
///
///  @param [in]       eMsg MESSAGE_ENUM       window message enum
///
///  @return BOOLEAN true for exist, false for no such message in message queue
///
///  @author MStarSemi @date 2007/3/2
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_API_IsExistRemainingMessage (MESSAGE_ENUM eMsg)
{
    U32 u32Idx = _MenuMsgQueue.u32MsgQIdxEnd;

    if (_MenuMsgQueue.MsgQueue[u32Idx].hwnd == HWND_INVALID)
        return FALSE;    // message queue is empty

    while( u32Idx != _MenuMsgQueue.u32MsgQIdxStart )
    {
        if (_MenuMsgQueue.MsgQueue[u32Idx].message == eMsg)
            return TRUE;

        u32Idx++;
        u32Idx %= ZUI_MSG_QUEUE_SIZE;
    }
    return FALSE;

}


#undef MAPP_ZUI_APIWINDOW_C
