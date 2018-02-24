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

#ifndef _MAPP_EPG_MAIN_H
#define _MAPP_EPG_MAIN_H

#include "datatype.h"
#include "MApp_Exit.h"
#include "msAPI_MW_GlobalSt.h"

#ifdef MAPP_EPG_MAIN_C
#define INTERFACE
#else
#define INTERFACE extern
#endif




typedef enum
{
    STATE_EPG_INIT,
    STATE_EPG_WAIT,
    //STATE_EPG_EPGTIMER_WAIT,
    STATE_EPG_CLEAN_UP,
    STATE_EPG_GOTO_STANDBY,
//#if (ENABLE_PIP)
    STATE_EPG_GOTO_PIP,
    STATE_EPG_ENABLE_PIP,
//#endif
    //STATE_EPG_GOTO_SCAN,
    //STATE_EPG_GOTO_EPG,
    //STATE_EPG_GOTO_CHANNELCHANGE, // To chagne TV<->RADIO when banner is displayed.
} EN_EPG_STATE;

INTERFACE EN_EPG_STATE enEpgState;


#if (ENABLE_ATSC)
// Invalid index or id definition
#define    INVALID_TBL_IDX              0xFF
#define    INVALID_EVENT_IDX            0xFF

#define MAX_NUM_OF_EPGLIST_ITEM         8

#define EPGUI_SYSTEMTIME_UPATE_PERIOD   1000//10000//1 min

#if ENABLE_ATSC_EPG_UI
typedef enum
{
    EPG_LIST_TODAY,
    EPG_LIST_TOMORROW,
    EPG_LIST_YESTERDAY,
}MS_EPG_LIST_DAY;

#endif
#endif


typedef enum
{
    MODE_EPG_SCHEDULE,
    MODE_EPG_DATE,
    MODE_EPG_PF,
    MODE_EPG_INFO,
    MODE_EPG_MANUALTIMER,
    MODE_EPG_TIMERLIST,
} EN_EPG_MODE;

INTERFACE EN_RET MApp_Epg_Main(void);
//INTERFACE void MApp_ProgramEdit_SetMode(EN_EPG_MODE mode);


/////////////////////////////////////////////////////////
//INTERFACE void      MApp_EpgUI_TableVersionUpdate( U16 u16SrvOrder, BOOLEAN bEitNowNext ); // No need anymore
//INTERFACE U16       MApp_EpgUI_Info_Get_DurationBar_Percentage( void );
//INTERFACE void      MApp_EpgUI_GWIN_Return( void );
//INTERFACE void      MApp_EpgUI_ConvertMonth2Str_U16( U8 u8Month, U16 *MonStr );
//INTERFACE BOOLEAN   MApp_EpgUI_Is_In_EpgUiDateState(void);



// EPG UI support functions
INTERFACE U16       MApp_EpgUI_Func_Get_SrvOrder(MEMBER_SERVICETYPE SrvType, U16 SrvPos);
INTERFACE BOOLEAN   MApp_EpgUI_IsFocusService(U8 u8UiSrvIdx);
//INTERFACE BOOLEAN   MApp_EpgUI_IsFocusEvent(U8 u8UiEvtIdx);
//INTERFACE BOOLEAN   MApp_EpgUI_IsCurrentEvent(void);
//INTERFACE BOOLEAN   MApp_EpgUI_UiServiceStatus_Get(U8 u8UiSrvIdx);
//INTERFACE void      MApp_EpgUI_UiServiceStatus_Set(U8 u8UiSrvIdx);
//INTERFACE BOOLEAN   MApp_EpgUI_IsTotalServiceHasDrawn(void);
//INTERFACE void      MApp_EpgUI_Func_Set_NoInfo_EventTime(U8 u8UiSrvIdx, U8 ListEvtIdx);
//INTERFACE MEMBER_SERVICETYPE MApp_EpgUI_GetFocusServiceType(void);
//INTERFACE void      MApp_EpgUI_Func_Set_Focus_Event(U8 u8UiSrvIdx, U8 EvtLoopIdx);

//INTERFACE void      MApp_EpgUI_Func_Clear_DrawStatus_All(void);
//INTERFACE void      MApp_EpgUI_Func_Clear_SpecificSrvOSDVar(U8 u8UiSrvIdx);
//INTERFACE void      MApp_EpgUI_Func_Set_PageTime(U32 time);
//INTERFACE BOOLEAN   MApp_EpgUI_Func_Add_EvtToOSDBuffer(U8 u8UiSrvIdx, U16 u16EvtIdx);
//INTERFACE void      MApp_EpgUI_Func_Add_MatchEvent_Sche(U8 u8UiSrvIdx);
//INTERFACE void      MApp_EpgUI_Func_Add_MatchEvent_PF(U8 u8UiSrvIdx);
//INTERFACE void      MApp_EpgUI_Func_Add_MatchEvent_NoInfo(U8 u8UiSrvIdx);


////////////////////////////////////////////////////////////////
#undef INTERFACE

#endif  // _MAPP_EPG_MAIN_H

