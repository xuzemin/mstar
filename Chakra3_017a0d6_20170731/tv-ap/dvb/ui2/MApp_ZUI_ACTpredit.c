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

#define MAPP_ZUI_ACTPREDIT_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_GlobalFunction.h"

#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_PrEdit_Main.h"
#include "MApp_OSDPage_Main.h"
#include "MApp_SaveData.h"
#include "MApp_UiMenuDef.h"
#include "msAPI_Memory.h"
#include "msAPI_ChProc.h"
#include "msAPI_DTVSystem.h"
#include "MApp_ChannelChange.h"
#include "MApp_ChannelList.h"
#include "MApp_GlobalFunction.h"

#if ENABLE_DVB//(ENABLE_DTV)
//#include "mapp_demux.h"
//#include "mapp_si.h"
#include "MApp_Dvb_SI.h" // "mapp_si.h"
#include "MApp_EpgTimer.h"
#endif


#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#include "MApp_Key.h"
#include "MApp_Menu_Main.h"
#include "MApp_BlockSys.h"

#include <stdio.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////
static EN_OSDPAGE_STATE _enTargetState;
extern EN_PREDIT_MODE _eProgramEditMode;

#if(ENABLE_DVB)
extern BOOLEAN MApp_CharTable_GetServiceNameToUCS2(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD * bChannelName, U8 ControlCodes);
#endif

#if (ENABLE_PVR)
extern BOOLEAN MApp_ZUI_ACT_PVR_Check_Switch_Channel(MEMBER_SERVICETYPE NewCMType, U16 u16NewPos);
#endif

#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
extern FUNCTION_RESULT msAPI_CM_MoveLCN(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD wLCN);
#endif
//////////////////////////////////////////
//Seprate keyborad rename and offset rename.
//True: do keyboard rename, False: do bar rename.
BOOL g_bKeyboardRename = FALSE;


#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
static U8 u8MoveLCNMaxDigiNum = 3;
static U16 u16MoveLCNInputValue = 0;
static U8 u8MoveLCNDigitCount = 0;
#endif

//*************************************************************************
//              Defines
//*************************************************************************
#define PROGRAM_EDIT_PAGE_NUM               10
#define PRG_EDIT_CURRENT_CN_TEXT_COLOR      0x00FF00
#define PRG_EDIT_CURRENT_CN_TEXT_HL_COLOR   0x0000FF
#define PROGRAM_EDIT_ITEM_INTERVAL          50
#define PROGRAM_EDIT_MOVE_OFFSET            10

typedef enum
{
    PROGRAM_EDIT_COMMAND_INIT,
    PROGRAM_EDIT_COMMAND_UP,
    PROGRAM_EDIT_COMMAND_DOWN,
    PROGRAM_EDIT_COMMAND_MOVE_UP,
    PROGRAM_EDIT_COMMAND_MOVE_DOWN,
    PROGRAM_EDIT_COMMAND_PRVPAGE,
    PROGRAM_EDIT_COMMAND_NEXTPAGE,
    PROGRAM_EDIT_COMMAND_DELETE,
} EN_PROGRAM_EDIT_COMMAND_TYPE;

/********************************************************************************/
/*                    Macro                                                     */
/********************************************************************************/
#define PROGRAM_EDIT_DBINFO(y)    //y



/********************************************************************************/
/*                      Local                                                   */
/********************************************************************************/
typedef struct _PROGRAM_EDIT_DATA_STRUCT
{
    U8  u8CurrentPage;
    U8  u8ServiceType;
    U16 u16ChCountOfCurPage;  //total channel count of current page
    U16 u16CurCh;
    U16 u16TotalChCount;  //total channel numer od database
    U8  u8PrevPage; //for program edit...
    U16 u16SrvPagePrvIndex;
    WORD wRenameProgramPosition;
    U8  u8RenameIndex;
} PROGRAM_EDIT_DATA_STRUCT;

static PROGRAM_EDIT_DATA_STRUCT * pPrEditData = NULL;

///////////////////////////////////////////////////////////////////////
static HWND _ZUI_TBLSEG _RenameHwndList[] =
{
    HWND_PREDIT_RENAME_CHAR0,
    HWND_PREDIT_RENAME_CHAR1,
    HWND_PREDIT_RENAME_CHAR2,
    HWND_PREDIT_RENAME_CHAR3,
    HWND_PREDIT_RENAME_CHAR4,
};

static  HWND _ZUI_TBLSEG _ProgramEditHwndList[PROGRAM_EDIT_PAGE_NUM]=
{
    HWND_PREDIT_ITEM0,
    HWND_PREDIT_ITEM1,
    HWND_PREDIT_ITEM2,
    HWND_PREDIT_ITEM3,
    HWND_PREDIT_ITEM4,
    HWND_PREDIT_ITEM5,
    HWND_PREDIT_ITEM6,
    HWND_PREDIT_ITEM7,
    HWND_PREDIT_ITEM8,
    HWND_PREDIT_ITEM9,
};



static U8 _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < PROGRAM_EDIT_PAGE_NUM; i++)
    {
        if (hwnd == _ProgramEditHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_ProgramEditHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= PROGRAM_EDIT_PAGE_NUM)
        return HWND_INVALID;
    return _ProgramEditHwndList[u8Index];

}

static void _MApp_ZUI_ACT_ProgramEditSetIndexFocus(U8 u8Index)
{
    HWND hwnd = _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(u8Index);
    if (hwnd == HWND_INVALID)
    {
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_PANE, SW_HIDE);
        MApp_ZUI_API_SetFocus(HWND_INVALID);
    }
    else
    {
        RECT rect;

        memset(&rect, 0, sizeof(RECT));
        MApp_ZUI_API_GetWindowRect(hwnd, &rect);

        //don't change type: MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_PANE, SW_SHOW);
        MApp_ZUI_API_MoveAllSuccessors(HWND_PREDIT_SELECTION_PANE, rect.left, rect.top);
        MApp_ZUI_API_SetFocus(hwnd);
    }
}

static void _MApp_ZUI_ACT_ProgramEditResetButtonState(void)
{
    MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_BTN_PANE, SW_HIDE);
    switch (_eProgramEditMode)
    {
        case MODE_PREDIT_BLOCK:
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_MENU_BTN, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_LOCK_BTN, SW_SHOW);
            break;
        case MODE_PREDIT_NORMAL:
            {
                EN_SERVICE_TYPE  u8Type;
                U16 g_wProgramPosition;
                U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(MApp_ZUI_API_GetFocus());

                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
                msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

                MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_RED_BTN, SW_SHOW);

#if ENABLE_SBTVD_CM_APP
                if(msAPI_SRC_IS_SBTVD_InUse())
                {
                    MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_YELLOW_BTN, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_GREEN_BTN, SW_HIDE);
                }
                else
#endif
                {
                #if (PRG_EDIT_INPUT_LCN_MOVE == 1)
                    if(u8Type == SERVICE_TYPE_ATV )
                        MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_YELLOW_BTN, SW_HIDE);
                    else
                        MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_YELLOW_BTN, SW_SHOW);
                #else
                    if(FALSE == fEnableLCN)
                    {
                        if(u8Type == SERVICE_TYPE_ATV )
                        {
                            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_YELLOW_BTN, SW_HIDE);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_YELLOW_BTN, SW_SHOW);
                        }
                    }
                    else
                        MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_YELLOW_BTN, SW_HIDE);
                    #endif

                    if(u8Type == SERVICE_TYPE_ATV)
                        MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_GREEN_BTN, SW_SHOW);
                    else
                        MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_GREEN_BTN, SW_HIDE);
                }

                MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_BLUE_BTN, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_FAV_BTN, SW_SHOW);
            }
            break;
        case MODE_PREDIT_MOVE:
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_MENU_BTN, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_YELLOW_BTN, SW_SHOW);
            break;
        case MODE_PREDIT_DELETE:
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_MENU_BTN, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_RED_BTN, SW_SHOW);
            break;
        case MODE_PREDIT_RENAME:
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_MENU_BTN, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_BOTTOM_HALF_GREEN_BTN, SW_SHOW);
            break;
    }
}

///////////////////////////////////////////////////////////////////////
// from MApp_ChannelList.c


//****************************************************************
//*** Channel Edit & Channel Block edit
//****************************************************************
//*************************************************************************
//Function name:        MApp_ChannelList_Init
//Passing parameter:    none
//Return parameter:     none
//Description:          Initialize channel list display flow
//*************************************************************************
static WORD _MApp_ProgramEdit_GetProgramPosition(U8 u8ServiceType, WORD wProgramPosition);
static void _MApp_ProgramEdit_Rename(U8 u8CharIdx, U8 u8Direction);

static void _MApp_ProgramEdit_Handler(U16 u16ActiveProgOrder, U16 u16ShiftProgIndex, U16 u16TotalSrvCount, U8 u8SrvCommand)
{
#if( ENABLE_DVB)
    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex( MApp_ZUI_API_GetFocus() );

    //U16 u16PageLastIndex;

    switch (u8SrvCommand)
    {
        case PROGRAM_EDIT_COMMAND_INIT:
        {
            pPrEditData->u8CurrentPage = u16ActiveProgOrder / PROGRAM_EDIT_PAGE_NUM;
            pPrEditData->u8PrevPage = pPrEditData->u8CurrentPage;
            u16SrvPageCurIndex = u16ActiveProgOrder % PROGRAM_EDIT_PAGE_NUM;

#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
            u16MoveLCNInputValue = 0;
            u8MoveLCNDigitCount = 0;
#endif
            if (u16TotalSrvCount == 0)
            {
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(0xFF); //no focus...
            }
            else if (IsATVInUse() && msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_ATV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) ==0)
            {
                pPrEditData->u8CurrentPage=0;
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(0);
            }
            else
            {
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);

            }
            pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
            if ( ((u16TotalSrvCount-1) / PROGRAM_EDIT_PAGE_NUM) > pPrEditData->u8CurrentPage )
            {
                pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {
                pPrEditData->u16ChCountOfCurPage = ((u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM) == 0 ? PROGRAM_EDIT_PAGE_NUM : (u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM));
            }
        }
        break;

        case PROGRAM_EDIT_COMMAND_UP:
        {
            pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
            pPrEditData->u8PrevPage = pPrEditData->u8CurrentPage;

            if (u16SrvPageCurIndex >= u16ShiftProgIndex)
            {
                //in the same page movement
                u16SrvPageCurIndex -= u16ShiftProgIndex;
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                //u8SrvPageBehavior = PROGRAM_EDIT_OSDEVENT_SWITCHINDEX;

            }
            else if (pPrEditData->u8CurrentPage == 0)
            {
                // first page
                pPrEditData->u8CurrentPage= (u16TotalSrvCount - 1) / PROGRAM_EDIT_PAGE_NUM;
                pPrEditData->u16ChCountOfCurPage = ((u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM) == 0 ? PROGRAM_EDIT_PAGE_NUM : (u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM));
                u16SrvPageCurIndex = pPrEditData->u16ChCountOfCurPage - 1;
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                if (u16TotalSrvCount > PROGRAM_EDIT_PAGE_NUM)
                {
                    //u8SrvPageBehavior = PROGRAM_EDIT_OSDEVENT_REDRAW;
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                }
                else
                {
                    //u8SrvPageBehavior = PROGRAM_EDIT_OSDEVENT_SWITCHINDEX;
                }
            }
            else
            {
                // move to prev page
                pPrEditData->u8CurrentPage--;
                pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                u16SrvPageCurIndex = (u16SrvPageCurIndex + PROGRAM_EDIT_PAGE_NUM - u16ShiftProgIndex) % PROGRAM_EDIT_PAGE_NUM;
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                //u8SrvPageBehavior = PROGRAM_EDIT_OSDEVENT_REDRAW;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
             }

            if (_eProgramEditMode !=MODE_PREDIT_BLOCK && _eProgramEditMode != MODE_PREDIT_DELETE)
            {
                _eProgramEditMode=MODE_PREDIT_NORMAL;
                _MApp_ZUI_ACT_ProgramEditResetButtonState();
            }
        }
        break;

        case PROGRAM_EDIT_COMMAND_DOWN:
        {
            U16 u16PageLastIndex;
            pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
            pPrEditData->u8PrevPage = pPrEditData->u8CurrentPage;
            u16PageLastIndex = (pPrEditData->u8CurrentPage * PROGRAM_EDIT_PAGE_NUM) + pPrEditData->u16ChCountOfCurPage;

            if ((u16SrvPageCurIndex+u16ShiftProgIndex) < pPrEditData->u16ChCountOfCurPage)
            {
                //in the same page movement
                u16SrvPageCurIndex += u16ShiftProgIndex;
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
            }
            else if (u16PageLastIndex == u16TotalSrvCount)
            {
                //move to first page
                pPrEditData->u8CurrentPage = 0;
                pPrEditData->u16ChCountOfCurPage = (u16TotalSrvCount > PROGRAM_EDIT_PAGE_NUM) ? PROGRAM_EDIT_PAGE_NUM : u16TotalSrvCount;
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(0);
                if (u16TotalSrvCount > PROGRAM_EDIT_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                }
            }
            else
            {
                //move to next page
                pPrEditData->u8CurrentPage++;
                if ( ((u16TotalSrvCount-1) / PROGRAM_EDIT_PAGE_NUM) > pPrEditData->u8CurrentPage )
                {
                    pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                }
                else
                {
                    pPrEditData->u16ChCountOfCurPage = ((u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM) == 0 ? PROGRAM_EDIT_PAGE_NUM : (u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM));
                }
                u16SrvPageCurIndex = (u16SrvPageCurIndex + u16ShiftProgIndex) % PROGRAM_EDIT_PAGE_NUM;
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
            }

            if (_eProgramEditMode !=MODE_PREDIT_BLOCK && _eProgramEditMode != MODE_PREDIT_DELETE)
            {
                _eProgramEditMode=MODE_PREDIT_NORMAL;
                _MApp_ZUI_ACT_ProgramEditResetButtonState();
            }
        }
        break;

        case PROGRAM_EDIT_COMMAND_MOVE_UP:
        {
            MApp_ZUI_API_RestoreWindowRect(MApp_ZUI_API_GetFocus());
            U16 u16DTVcount,u16Radiocount,u16ATVcount;
#if NORDIG_FUNC //for Nordig spec v2.0
            U16 u16Datacount;
#endif
            U8  u8TypeFirstPage,u8TypeLastPage; //the fist/last page index of current channel type
            U8  u8TypeFirstCh,u8TypeLastCh; //the fist/last channel index of current channel type
            EN_SERVICE_TYPE  u8Type,u8toType;
            U16 g_wProgramPosition;

            pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
            pPrEditData->u8PrevPage = pPrEditData->u8CurrentPage;

            g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
            msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

            u16DTVcount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            u16Radiocount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
#if NORDIG_FUNC //for Nordig spec v2.0
            u16Datacount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
#endif
            u16ATVcount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_ATV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

#if NORDIG_FUNC //for Nordig spec v2.0
            if(u8Type == SERVICE_TYPE_DTV)
            {
                u8TypeFirstPage = 0;
                u8TypeLastPage = (u16DTVcount-1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = 0;
                u8TypeLastCh = (u16DTVcount-1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else if(u8Type == SERVICE_TYPE_RADIO)
            {
                u8TypeFirstPage =  (u16DTVcount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else if(u8Type == SERVICE_TYPE_DATA)
            {
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16Datacount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16Datacount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {//ATV
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount + u16Datacount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16Datacount + u16ATVcount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount + u16Datacount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16Datacount + u16ATVcount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
#else
            if(u8Type == SERVICE_TYPE_DTV)
            {
                u8TypeFirstPage = 0;
                u8TypeLastPage = (u16DTVcount-1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = 0;
                u8TypeLastCh = (u16DTVcount-1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else if(u8Type == SERVICE_TYPE_RADIO)
            {
                u8TypeFirstPage =  (u16DTVcount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {//ATV
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16ATVcount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16ATVcount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
#endif
#if NORDIG_FUNC //for Nordig spec v2.0
            if((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)||(u8Type == SERVICE_TYPE_DATA))
            {
                u8TypeFirstPage = 0;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16Datacount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = 0;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16Datacount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {//ATV
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount + u16Datacount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16Datacount + u16ATVcount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount + u16Datacount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16Datacount + u16ATVcount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
#else
            if((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO))
            {
                u8TypeFirstPage = 0;
                u8TypeLastPage = (u16DTVcount + u16Radiocount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = 0;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {//ATV
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16ATVcount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16ATVcount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
#endif

            if(pPrEditData->u8CurrentPage == u8TypeFirstPage)
            {// first page of current service type
                if ((u16SrvPageCurIndex - u8TypeFirstCh) >= u16ShiftProgIndex)
                {
                    //in the same page movement
                    u16SrvPageCurIndex -= u16ShiftProgIndex;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                }
                else
                {   // change to last page of current channel type
                    pPrEditData->u8CurrentPage = u8TypeLastPage;
                    if(pPrEditData->u8CurrentPage == ((u16TotalSrvCount - 1)/PROGRAM_EDIT_PAGE_NUM))
                    {
                        pPrEditData->u16ChCountOfCurPage = ((u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM) == 0 ? PROGRAM_EDIT_PAGE_NUM : (u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM));
                    }
                    else
                    {
                        pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                    }
                    u16SrvPageCurIndex = (U16)u8TypeLastCh;//assign to last sevice channel
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                }
            }
            else
            {
                if (u16SrvPageCurIndex >= u16ShiftProgIndex)
                {   //in the same page movement
                    u16SrvPageCurIndex -= u16ShiftProgIndex;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                }
                else
                {   // move to prev page
                    pPrEditData->u8CurrentPage--;
                    pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                    u16SrvPageCurIndex = (u16SrvPageCurIndex + PROGRAM_EDIT_PAGE_NUM - u16ShiftProgIndex) % PROGRAM_EDIT_PAGE_NUM;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                }
            }

            MApp_ZUI_API_MoveWindowByOffset(MApp_ZUI_API_GetFocus(),0,-PROGRAM_EDIT_MOVE_OFFSET,0,2*PROGRAM_EDIT_MOVE_OFFSET);

            {   //exchange channel
                U16 u16FromPosition,u16ToPosition;
                u8toType = u8Type;      //init u8toType
                g_wProgramPosition = pPrEditData->u8PrevPage*PROGRAM_EDIT_PAGE_NUM + pPrEditData->u16SrvPagePrvIndex;
#if ENABLE_DTV
        #if NORDIG_FUNC //for Nordig spec v2.0
                if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)||(u8Type == SERVICE_TYPE_DATA)))
        #else
                if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)))
        #endif
                {
                    u16FromPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition, (MEMBER_SERVICETYPE *)&u8Type);
                }
                else
#endif
                {
                    u16FromPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
                }

                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
#if ENABLE_DTV
        #if NORDIG_FUNC //for Nordig spec v2.0
                if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)||(u8Type == SERVICE_TYPE_DATA)))
        #else
                if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)))
        #endif
                {
                    u16ToPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition, (MEMBER_SERVICETYPE *)&u8toType);
                }
                else
#endif
                {
                    u16ToPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
                }
#if ENABLE_DTV
#if NORDIG_FUNC //for Nordig spec v2.0
                if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO) || (u8Type==SERVICE_TYPE_DATA))
#else
                if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO))
#endif
                {
                    msAPI_CM_MoveProgram((MEMBER_SERVICETYPE)u8Type, u16FromPosition, u16ToPosition,(MEMBER_SERVICETYPE)u8toType);
                    if ( FALSE == fEnableLCN )
                    {
                        ddmArrangeLogicalChannelNumber( (MEMBER_SERVICETYPE)u8Type, E_LCN_TYPE_MOVE );
                    }
                }
                else
#endif
                if (u8Type == SERVICE_TYPE_ATV)
                {
                    msAPI_ATV_MoveProgram( u16FromPosition, u16ToPosition);
                }
                if((pPrEditData->u8PrevPage*PROGRAM_EDIT_PAGE_NUM + pPrEditData->u16SrvPagePrvIndex) == pPrEditData->u16CurCh) //if mve running channel
                {
                    if(pPrEditData->u16CurCh == u8TypeFirstCh)
                    {
#if NORDIG_FUNC //for Nordig spec v2.0
                        pPrEditData->u16CurCh = u16DTVcount + u16Radiocount + u16Datacount - 1;
#else
                        pPrEditData->u16CurCh = u16DTVcount + u16Radiocount - 1;
#endif
                    }
                    else
                    {
                        pPrEditData->u16CurCh--;
                    }
                }
                else if(g_wProgramPosition == pPrEditData->u16CurCh)     //if mve to the front  of  running channel
                {
                    pPrEditData->u16CurCh++;
                }
            }

        }
        break;

        case PROGRAM_EDIT_COMMAND_MOVE_DOWN:
        {
            MApp_ZUI_API_RestoreWindowRect(MApp_ZUI_API_GetFocus());
            U16 u16DTVcount,u16Radiocount,u16ATVcount;
#if NORDIG_FUNC //for Nordig spec v2.0
            U16 u16Datacount;
#endif
            U8  u8TypeFirstPage,u8TypeLastPage; //the fist/last page index of current channel type
            U8  u8TypeFirstCh,u8TypeLastCh; //the fist/last channel index of current channel type
            EN_SERVICE_TYPE  u8Type,u8toType;
            U16 g_wProgramPosition;

            pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
            pPrEditData->u8PrevPage = pPrEditData->u8CurrentPage;

            g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
            msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

            u16DTVcount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            u16Radiocount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            u16ATVcount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_ATV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
#if NORDIG_FUNC //for Nordig spec v2.0
            u16Datacount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
#endif

#if NORDIG_FUNC //for Nordig spec v2.0
            if(u8Type == SERVICE_TYPE_DTV)
            {
                u8TypeFirstPage = 0;
                u8TypeLastPage = (u16DTVcount-1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = 0;
                u8TypeLastCh = (u16DTVcount-1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else if(u8Type == SERVICE_TYPE_RADIO)
            {
                u8TypeFirstPage =  (u16DTVcount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else if(u8Type == SERVICE_TYPE_DATA)
            {
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16Datacount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16Datacount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {//ATV
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount + u16Datacount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16Datacount + u16ATVcount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount + u16Datacount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16Datacount + u16ATVcount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
#else
            if(u8Type == SERVICE_TYPE_DTV)
            {
                u8TypeFirstPage = 0;
                u8TypeLastPage = (u16DTVcount-1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = 0;
                u8TypeLastCh = (u16DTVcount-1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else if(u8Type == SERVICE_TYPE_RADIO)
            {
                u8TypeFirstPage =  (u16DTVcount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {//ATV
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16ATVcount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16ATVcount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
#endif
#if NORDIG_FUNC //for Nordig spec v2.0
            if((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)||(u8Type == SERVICE_TYPE_DATA))
            {
                u8TypeFirstPage = 0;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16Datacount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = 0;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16Datacount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {//ATV
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount + u16Datacount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16Datacount + u16ATVcount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount + u16Datacount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16Datacount + u16ATVcount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
#else
            if((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO))
            {
                u8TypeFirstPage = 0;
                u8TypeLastPage = (u16DTVcount + u16Radiocount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = 0;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
            else
            {//ATV
                u8TypeFirstPage =  (u16DTVcount + u16Radiocount)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastPage = (u16DTVcount + u16Radiocount + u16ATVcount - 1)/PROGRAM_EDIT_PAGE_NUM;
                u8TypeFirstCh = (u16DTVcount + u16Radiocount)%PROGRAM_EDIT_PAGE_NUM;
                u8TypeLastCh  = (u16DTVcount + u16Radiocount + u16ATVcount - 1)%PROGRAM_EDIT_PAGE_NUM;
            }
#endif

            if(pPrEditData->u8CurrentPage == u8TypeLastPage)
            {   // last page of current service type
                if ((u16SrvPageCurIndex + u16ShiftProgIndex) <= u8TypeLastCh)
                {   //in the same page movement
                    u16SrvPageCurIndex += u16ShiftProgIndex;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                }
                else
                {   // change to the first page of current channel type
                    pPrEditData->u8CurrentPage = u8TypeFirstPage;
                    if ( ((u16TotalSrvCount - 1) / PROGRAM_EDIT_PAGE_NUM) > pPrEditData->u8CurrentPage )
                    {
                        pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                    }
                    else
                    {
                        pPrEditData->u16ChCountOfCurPage = ((u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM) == 0 ? PROGRAM_EDIT_PAGE_NUM : (u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM));
                    }
                    u16SrvPageCurIndex = (U16)u8TypeFirstCh;//assign to the first channel
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                }
            }
            else
            {
                if ((u16SrvPageCurIndex+u16ShiftProgIndex) < pPrEditData->u16ChCountOfCurPage)
                {   //in the same page movement
                    u16SrvPageCurIndex += u16ShiftProgIndex;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                }
                else
                {   //move to next page
                    pPrEditData->u8CurrentPage++;
                    if ( ((u16TotalSrvCount-1) / PROGRAM_EDIT_PAGE_NUM) > pPrEditData->u8CurrentPage )
                    {
                        pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                    }
                    else
                    {
                        pPrEditData->u16ChCountOfCurPage = ((u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM) == 0 ? PROGRAM_EDIT_PAGE_NUM : (u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM));
                    }
                    u16SrvPageCurIndex = (u16SrvPageCurIndex + u16ShiftProgIndex) % PROGRAM_EDIT_PAGE_NUM;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                }
            }

            MApp_ZUI_API_MoveWindowByOffset(MApp_ZUI_API_GetFocus(),0,-PROGRAM_EDIT_MOVE_OFFSET,0,2*PROGRAM_EDIT_MOVE_OFFSET);

            {   //exchange channel
                U16 u16FromPosition,u16ToPosition;
                u8toType = u8Type;      //init u8toType
                g_wProgramPosition = pPrEditData->u8PrevPage*PROGRAM_EDIT_PAGE_NUM + pPrEditData->u16SrvPagePrvIndex;
#if ENABLE_DTV
        #if NORDIG_FUNC //for Nordig spec v2.0
                if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)||(u8Type == SERVICE_TYPE_DATA)))
        #else
                if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)))
        #endif
                {
                    u16FromPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition, (MEMBER_SERVICETYPE *)&u8Type);
                }
                else
#endif
                {
                    u16FromPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
                }

                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
#if ENABLE_DTV
        #if NORDIG_FUNC //for Nordig spec v2.0
                if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)||(u8Type == SERVICE_TYPE_DATA)))
        #else
                if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((u8Type == SERVICE_TYPE_DTV)||(u8Type == SERVICE_TYPE_RADIO)))
        #endif
                {
                    u16ToPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition, (MEMBER_SERVICETYPE *)&u8toType);
                }
                else
#endif
                {
                    u16ToPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
                }
#if ENABLE_DTV
#if NORDIG_FUNC //for Nordig spec v2.0
                if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO)|| (u8Type==SERVICE_TYPE_DATA))
#else
                if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO) )
#endif
                {
                    msAPI_CM_MoveProgram((MEMBER_SERVICETYPE)u8Type, u16FromPosition, u16ToPosition,(MEMBER_SERVICETYPE)u8toType);
                    if ( FALSE == fEnableLCN )
                    {
                        ddmArrangeLogicalChannelNumber((MEMBER_SERVICETYPE) u8Type, E_LCN_TYPE_MOVE );
                    }
                }
                else
#endif
                if (u8Type == SERVICE_TYPE_ATV)
                {
                    msAPI_ATV_MoveProgram( u16FromPosition, u16ToPosition);
                }
                if((pPrEditData->u8PrevPage*PROGRAM_EDIT_PAGE_NUM + pPrEditData->u16SrvPagePrvIndex) == pPrEditData->u16CurCh)   //if mve running channel
                {
#if NORDIG_FUNC //for Nordig spec v2.0
                    if(pPrEditData->u16CurCh == (u16DTVcount + u16Radiocount + u16Datacount - 1))
#else
                    if(pPrEditData->u16CurCh == (u16DTVcount + u16Radiocount - 1))
#endif
                    {
                        pPrEditData->u16CurCh = u8TypeFirstCh;
                    }
                    else
                    {
                        pPrEditData->u16CurCh++;
                    }
                }
                else if(g_wProgramPosition == pPrEditData->u16CurCh)     //if mve to the behind  of  running channel
                {
                    pPrEditData->u16CurCh--;
                }
            }

        }
        break;

        case PROGRAM_EDIT_COMMAND_PRVPAGE:
        {
            if (pPrEditData->u8CurrentPage == 0)
            {
                if (u16SrvPageCurIndex > 0)
                {
                    //focus the first item
                    pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
                    //u16SrvPageCurIndex = 0;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(0);
                }
                else
                {
                    //move to last page last item
                    pPrEditData->u8CurrentPage= (u16TotalSrvCount - 1) / PROGRAM_EDIT_PAGE_NUM;
                    pPrEditData->u16ChCountOfCurPage = ((u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM) == 0 ? PROGRAM_EDIT_PAGE_NUM : (u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM));
                    pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
                    u16SrvPageCurIndex = pPrEditData->u16ChCountOfCurPage - 1;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                    if (u16TotalSrvCount > PROGRAM_EDIT_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                    }
                }
            }
            else
            {
                pPrEditData->u8CurrentPage--;
                pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
            }
            if (_eProgramEditMode !=MODE_PREDIT_BLOCK && _eProgramEditMode != MODE_PREDIT_DELETE)
            {
                _eProgramEditMode=MODE_PREDIT_NORMAL;
                _MApp_ZUI_ACT_ProgramEditResetButtonState();
            }
        }
        break;

        case PROGRAM_EDIT_COMMAND_NEXTPAGE:
        {
            U8 u8LastPage = (u16TotalSrvCount - 1) / PROGRAM_EDIT_PAGE_NUM;
            if (u8LastPage == pPrEditData->u8CurrentPage)
            {
                //the last page
                if (u16SrvPageCurIndex == (pPrEditData->u16ChCountOfCurPage-1))
                {
                    //the last item, move to first page
                    pPrEditData->u8CurrentPage = 0;
                    pPrEditData->u16ChCountOfCurPage = (u16TotalSrvCount > PROGRAM_EDIT_PAGE_NUM) ? PROGRAM_EDIT_PAGE_NUM : u16TotalSrvCount;
                    pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
                    //u16SrvPageCurIndex = 0;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(0);
                    if (u16TotalSrvCount > PROGRAM_EDIT_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                    }
                }
                else
                {
                    //focus the last item
                    pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
                    u16SrvPageCurIndex = pPrEditData->u16ChCountOfCurPage - 1;
                    _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                }
            }
            else
            {
                //move to next page
                pPrEditData->u8CurrentPage++;
                if (u8LastPage > pPrEditData->u8CurrentPage)
                {
                    pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                }
                else
                {
                    pPrEditData->u16ChCountOfCurPage = ((u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM) == 0 ? PROGRAM_EDIT_PAGE_NUM : (u16TotalSrvCount % PROGRAM_EDIT_PAGE_NUM));
                }
                if (u16SrvPageCurIndex >= pPrEditData->u16ChCountOfCurPage)
                {
                    u16SrvPageCurIndex = pPrEditData->u16ChCountOfCurPage - 1;
                }
                pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
                _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
            }

             if (_eProgramEditMode !=MODE_PREDIT_BLOCK && _eProgramEditMode != MODE_PREDIT_DELETE)
            {
                _eProgramEditMode=MODE_PREDIT_NORMAL;
                _MApp_ZUI_ACT_ProgramEditResetButtonState();
            }
        }
        break;

        case PROGRAM_EDIT_COMMAND_DELETE:
        {
            U16     u16CurPosition;
            EN_SERVICE_TYPE      u8Type;
            U16 g_wProgramPosition;
            U16    u16PageLastIndex;
            MEMBER_SERVICETYPE  srvType = E_SERVICETYPE_INVALID;
            U16    srvPos = INVALID_SERVICE_ID;
            U8 Index;

            MS_EPG_TIMER* m_pstEpgTimer = MApp_Get_EPG_Timer_pstEpgTimer();
            g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;

#if ENABLE_SBTVD_CM_APP
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
                {
                    MEMBER_SERVICETYPE eServiceType;

                    msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(g_wProgramPosition,&eServiceType,&u16CurPosition);
                    u8Type = (EN_SERVICE_TYPE)eServiceType;
                    if(eServiceType == E_SERVICETYPE_ATV)
                        u16CurPosition = (U16)u16CurPosition >> 8;
                }
                else
                {
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    u16CurPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
                }
            }
            else
#endif
            {
                msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
#if ENABLE_DTV
                if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
                {
                    u16CurPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition, (MEMBER_SERVICETYPE *)&u8Type);
                }
                else
#endif
                {
                    u16CurPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
                }
            }

            pPrEditData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

#if ENABLE_DTV
#if NORDIG_FUNC //for Nordig spec v2.0
            if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO) || (u8Type==SERVICE_TYPE_DATA))
#else
            if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO))
#endif
            {
                for(Index = 0;Index < MApp_EpgUI_GetNumOfTimers();)
                {
                    msAPI_CM_GetServiceTypeAndPositionWithPCN(m_pstEpgTimer[Index].u8PCN, m_pstEpgTimer[Index].u16SrvID, &srvType, &srvPos);
                    if((MEMBER_SERVICETYPE)u8Type == srvType && u16CurPosition == srvPos)
                    {
                        srvType = E_SERVICETYPE_INVALID;
                        srvPos = INVALID_SERVICE_ID;
                        MApp_EpgTimer_DelCurTimerListItem(Index);
                        Index = 0;
                    }
                    else
                    {
                        Index++;
                    }
                }
                MApp_EpgTimer_ReconfigTimerFromList(MApp_GetLocalSystemTime());
                msAPI_CM_DeleteProgram( (MEMBER_SERVICETYPE)u8Type, u16CurPosition, TRUE );
            }
            else
#endif
            if (u8Type == SERVICE_TYPE_ATV)
            {
                msAPI_ATV_DeleteProgram( u16CurPosition);
            }
            pPrEditData->u16TotalChCount--;
            pPrEditData->u16SrvPagePrvIndex = u16SrvPageCurIndex;
            //check if the last page
            u16PageLastIndex = (pPrEditData->u8CurrentPage * PROGRAM_EDIT_PAGE_NUM) + pPrEditData->u16ChCountOfCurPage;

            if (u16PageLastIndex == u16TotalSrvCount)//last page
            {
                if(pPrEditData->u16ChCountOfCurPage == (u16SrvPageCurIndex+1))//last item
                {
                    if(pPrEditData->u16ChCountOfCurPage>1)
                    {
                        pPrEditData->u16ChCountOfCurPage--;
                        u16SrvPageCurIndex--;
                        _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                    }
                    else
                    {
                        if(pPrEditData->u8CurrentPage>0)//go to previous page
                        {
                            pPrEditData->u8CurrentPage--;
                            pPrEditData->u16ChCountOfCurPage = PROGRAM_EDIT_PAGE_NUM;
                            u16SrvPageCurIndex = (u16SrvPageCurIndex + PROGRAM_EDIT_PAGE_NUM - u16ShiftProgIndex) % PROGRAM_EDIT_PAGE_NUM;
                            _MApp_ZUI_ACT_ProgramEditSetIndexFocus(u16SrvPageCurIndex);
                        }

                    }
                }
                else
                {
                     pPrEditData->u16ChCountOfCurPage--;
                }
            }


            #if ENABLE_SBTVD_CM_APP
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
    			if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
    			{
    				if(pPrEditData->u16TotalChCount==0)
    				{
    					msAPI_CHPROC_CM_ResetOridial();
    				}
    				else
    				{
    					msAPI_CHPROC_CM_InitOridial();
    				}
    			}
            }
            #endif



            if (g_wProgramPosition==pPrEditData->u16CurCh)
            {
                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
                if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                {
                    MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                }
                #if (ENABLE_PIP)
                if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                {
                    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                    {
                        MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                        MApp_ChannelChange_EnableChannel(SUB_WINDOW);
                    }
                }
                #endif
                _MApp_ChannelList_ChannelChange(g_wProgramPosition, pPrEditData->u8ServiceType, FALSE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            }
           if(g_wProgramPosition < pPrEditData->u16CurCh)     //if delete the front  of  running channel
           {
              pPrEditData->u16CurCh--;
           }
#if ENABLE_DTV
           //make sure that it will not change channel when delete the front  of  running channel
           msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, pPrEditData->u16CurCh, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
           if((u8Type != SERVICE_TYPE_ATV) && (IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING)))
           {
               g_wProgramPosition = msAPI_CM_GetPositionbyListPosition(pPrEditData->u16CurCh,(MEMBER_SERVICETYPE *)&u8Type);
           }
           else
           {
               g_wProgramPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, pPrEditData->u16CurCh);
           }
           msAPI_CM_SetCurrentServiceType((MEMBER_SERVICETYPE)u8Type);
           msAPI_CM_SetCurrentPosition((MEMBER_SERVICETYPE)u8Type,g_wProgramPosition);
    #if MHEG5_ENABLE
                g_eCurrentRealServiceType=g_eCurrentUserServiceType = (MEMBER_SERVICETYPE)u8Type;
                if(u8Type == E_SERVICETYPE_RADIO)
                    g_wCurrentRadioRealServicePosition=g_wCurrentRadioUserServicePosition = g_wProgramPosition;
        #if NORDIG_FUNC //for Nordig Spec v2.0
                else if(u8Type == E_SERVICETYPE_DATA)
                    g_wCurrentDataRealServicePosition=g_wCurrentDataUserServicePosition = g_wProgramPosition;
        #endif
                else
                    g_wCurrentTVRealServicePosition=g_wCurrentTVUserServicePosition = g_wProgramPosition;
    #endif
#endif
            //u8SrvPageBehavior = PROGRAM_EDIT_OSDEVENT_REDRAW;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
        }
        break;
    }

#else

    UNUSED(u16ActiveProgOrder);
    UNUSED(u16ShiftProgIndex);
    UNUSED(u16TotalSrvCount);
    UNUSED(u8SrvCommand);

#endif
}

static WORD _MApp_ProgramEdit_GetProgramPosition(U8 u8ServiceType, WORD wProgramPosition)
{
#if ENABLE_DTV
    if(u8ServiceType == SERVICE_TYPE_DTV)
    {
        return wProgramPosition;
    }
    else if(u8ServiceType == SERVICE_TYPE_RADIO)
    {
        return  wProgramPosition - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    }
#if NORDIG_FUNC //for Nordig spec v2.0
    else if(u8ServiceType == SERVICE_TYPE_DATA)
    {
        return  wProgramPosition - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    }
#endif
    else
#endif
    if(u8ServiceType == SERVICE_TYPE_ATV)
    {
        U16 u16CurPosition = 0;
        msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wProgramPosition, (U8*)&u16CurPosition, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        return u16CurPosition;
    }
    else
        return 0;
}

static void _MApp_ProgramEdit_Init(U8 u8ServiceType)
{
    BOOLEAN bVisibleFlag = false;

    pPrEditData->u8ServiceType = u8ServiceType;
    PROGRAM_EDIT_DBINFO(printf("UI_MApp_ChannelList_Init: u8ServiceType=%bu\n", (U8)u8ServiceType));

    pPrEditData->u16TotalChCount = msAPI_CHPROC_CM_CountProgram((MEMBER_SERVICETYPE)u8ServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    pPrEditData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal((MEMBER_SERVICETYPE)u8ServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

#if ENABLE_SBTVD_CM_APP
    if(msAPI_ATV_GetCurrentAntenna() == ANT_AIR)
#endif
    {
        msAPI_CHPROC_CM_GetAttributeOfOrdinal( (MEMBER_SERVICETYPE)u8ServiceType, pPrEditData->u16CurCh, &bVisibleFlag, E_SERVICE_ATTR_VISIBLE, E_PROGACESS_INCLUDE_VISIBLE_ONLY );
        if ( !bVisibleFlag )
        {
            pPrEditData->u16CurCh = 0;
        }

        if ((pPrEditData->u16TotalChCount > 0) && (pPrEditData->u16CurCh == INVALID_ORDINAL))
        {
            pPrEditData->u16CurCh = 0;
        }
        else if (pPrEditData->u16TotalChCount == 0)
        {
            pPrEditData->u16CurCh = 0;
        }
    }

    #if(!DVB_T_C_DIFF_DB && ENABLE_DVB)
        if((DB_PROGRAM_SOURCE_TYPE != UI_INPUT_SOURCE_TYPE) && (UI_INPUT_SOURCE_ATV != UI_INPUT_SOURCE_TYPE))
        {
            pPrEditData->u16CurCh = 0;
            pPrEditData->u16TotalChCount = 0;
        }
    #endif

    PROGRAM_EDIT_DBINFO(printf("pPrEditData->u16TotalChCount=%u\n", pPrEditData->u16TotalChCount));
    PROGRAM_EDIT_DBINFO(printf("pPrEditData->u16CurCh=%u\n", pPrEditData->u16CurCh));

    _MApp_ProgramEdit_Handler(pPrEditData->u16CurCh, 0, pPrEditData->u16TotalChCount,  PROGRAM_EDIT_COMMAND_INIT);
}

#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
static void _MApp_ProgramEdit_Move_ProcDigitKey(U8 bKeyValue)
{

    if(u8MoveLCNDigitCount >=3)
    {
        u16MoveLCNInputValue = 0;
        u8MoveLCNDigitCount = 0;

    }
    if (u16MoveLCNInputValue == 0)
    {
        u16MoveLCNInputValue = (bKeyValue - VK_NUM_0);
        u8MoveLCNDigitCount = 1;
    }
    else
    {
        u16MoveLCNInputValue = u16MoveLCNInputValue * 10 + (bKeyValue - VK_NUM_0);
        u8MoveLCNDigitCount++;
    }

    MApp_ZUI_API_InvalidateAllSuccessors(MApp_ZUI_API_GetFocus());

    #if (UI_SKIN_SEL != UI_SKIN_960X540XI8)     //for fix complier error
    if ( IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING) )
    #else
    if(1)
    #endif
    {
        u8MoveLCNMaxDigiNum = 4;
    }
    else if(IS_COUNTRY_ONLY_ATV(OSD_COUNTRY_SETTING))
    {
        u8MoveLCNMaxDigiNum = 2;
    }
    else
    {
        u8MoveLCNMaxDigiNum = 3;
    }
}
#endif
static void _MApp_ProgramEdit_Key_SKIP(void)
{
    BOOLEAN bSkip = false;
    BOOLEAN bFav = false;
    EN_SERVICE_TYPE u8Type = SERVICE_TYPE_INVALIDE;
    U16 u16CurPosition;
    U16 g_wProgramPosition;
    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(      MApp_ZUI_API_GetFocus());
    if (_eProgramEditMode == MODE_PREDIT_BLOCK)
        return;

    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bSkip, E_SERVICE_ATTR_SKIPPED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bFav, E_SERVICE_ATTR_FAVORITE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    bSkip = !bSkip;

#if ENABLE_SBTVD_CM_APP
    if(msAPI_SRC_IS_SBTVD_InUse())
    {
        MEMBER_SERVICETYPE eServiceType;
        if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
        {
             msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(g_wProgramPosition,&eServiceType,&g_wProgramPosition);
             if(eServiceType == E_SERVICETYPE_ATV)
                 u16CurPosition = (U16)g_wProgramPosition >> 8;
             else
                u16CurPosition = g_wProgramPosition;
        }
        else
        {
                msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                u16CurPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
        }
    }
    else
#endif
    {
      #if ENABLE_DVB
        if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
        {
            u16CurPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition, (MEMBER_SERVICETYPE *)&u8Type);
        }
        else
      #endif
        {
            u16CurPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
        }
    }

    MApp_ZUI_API_InvalidateAllSuccessors(
        _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(u16SrvPageCurIndex));

#if ENABLE_DVB
  #if NORDIG_FUNC //for Nordig spec v2.0
    if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO) || (u8Type==SERVICE_TYPE_DATA))
  #else
    if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO))
  #endif
    {
        if(bFav)
        {
            msAPI_CM_FavorProgram((MEMBER_SERVICETYPE)u8Type, u16CurPosition, !bFav);
        }

        msAPI_CM_SkipProgram((MEMBER_SERVICETYPE)u8Type, u16CurPosition, bSkip);

    }
    else
#endif
    if (u8Type == SERVICE_TYPE_ATV)
    {
        if(bFav)
        {
            msAPI_ATV_SetFavoriteProgram(u16CurPosition, !bFav);
        }

        msAPI_ATV_SkipProgram(u16CurPosition, bSkip);

    }
}

static void _MApp_ProgramEdit_Key_LOCK(void)
{
    BOOLEAN bLock = false;
    EN_SERVICE_TYPE u8Type;
    U16 u16CurPosition;
    U16 g_wProgramPosition;
    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(MApp_ZUI_API_GetFocus());

    if (_eProgramEditMode!=MODE_PREDIT_BLOCK)
        return;

    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bLock, E_SERVICE_ATTR_LOCKED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    bLock = !bLock;
#if ENABLE_SBTVD_CM_APP
    if(msAPI_SRC_IS_SBTVD_InUse() && ANT_AIR == msAPI_ATV_GetCurrentAntenna())
    {
        MEMBER_SERVICETYPE eServiceType;

        msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(g_wProgramPosition,&eServiceType,&g_wProgramPosition);
        if(eServiceType == E_SERVICETYPE_ATV)
            u16CurPosition = (U16)g_wProgramPosition >> 8;
        else
            u16CurPosition = g_wProgramPosition;
    }
    else
#endif
#if ENABLE_DVB
    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
        u16CurPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition, (MEMBER_SERVICETYPE *)&u8Type);
    }
    else
#endif
    {
        u16CurPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
    }
    MApp_ZUI_API_InvalidateAllSuccessors(
        _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(u16SrvPageCurIndex));

#if ENABLE_DVB
  #if NORDIG_FUNC //for Nordig spec v2.0
    if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO) || (u8Type==SERVICE_TYPE_DATA))
  #else
    if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO))
  #endif
    {
        msAPI_CM_LockProgram((MEMBER_SERVICETYPE)u8Type, u16CurPosition, bLock);
    }
    else
#endif
    if (u8Type == SERVICE_TYPE_ATV)
    {
        msAPI_ATV_LockProgram(u16CurPosition, bLock);
		if(IsATVInUse() && (u16CurPosition == msAPI_ATV_GetCurrentProgramNumber()))
		{
			if(bLock)
			{
				MApp_EnableBlockProgramme(TRUE);
				MApp_ParentalControl_SetBlockStatus(TRUE);
			}
			else
			{
				MApp_EnableBlockProgramme(FALSE);
				MApp_ParentalControl_SetBlockStatus(FALSE);
			}
		}
    }

    pPrEditData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

    if(pPrEditData->u16CurCh == g_wProgramPosition)
    {
        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
        {
            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
        }
        #if (ENABLE_PIP)
        if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
        {
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
            {
                MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                MApp_ChannelChange_EnableChannel(SUB_WINDOW);
            }
        }
        #endif
    }

}

static void _MApp_ProgramEdit_Key_DELETE(void)
{
    if (_eProgramEditMode==MODE_PREDIT_BLOCK)
        return;

    if(_eProgramEditMode==MODE_PREDIT_NORMAL)
    {
        //_eProgramEditMode=MODE_PREDIT_DELETE;
        //_MApp_ZUI_ACT_ProgramEditResetButtonState();
        //MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_PANE, SW_HIDE);
        //MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_RED_BG, SW_SHOW);
        //MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_RED_BTN, SW_SHOW);

        _MApp_ProgramEdit_Handler(0, 1, pPrEditData->u16TotalChCount,  PROGRAM_EDIT_COMMAND_DELETE);
        if(pPrEditData->u16TotalChCount == 0)
        {
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
            #if (ENABLE_PIP)
            if(IsPIPSupported())
            {
                if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                    MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
            }
            #endif
            u8KeyCode = KEY_MENU;
        }

    }
/*
    else if(_eProgramEditMode==MODE_PREDIT_DELETE)
    {
        _MApp_ProgramEdit_Handler(0, 1, pPrEditData->u16TotalChCount,  PROGRAM_EDIT_COMMAND_DELETE);
        if(pPrEditData->u16TotalChCount == 0)
        {
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
            #if (ENABLE_PIP)
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
            #endif
            u8KeyCode = KEY_MENU;
        }
    }
*/
}

static void _MApp_ProgramEdit_Cmf_Key_MENU(void)
{
    if (_eProgramEditMode==MODE_PREDIT_BLOCK)
        return;

    if (_eProgramEditMode == MODE_PREDIT_RENAME)
    {
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_RENAME_PANE, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_KEYBOARD,SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_INFO_MSG_BOX,SW_HIDE);
        MApp_ZUI_API_RestoreWindowRect(HWND_PREDIT_RENAME_PANE);
        _MApp_ZUI_ACT_ProgramEditSetIndexFocus(
            pPrEditData->u8RenameIndex);
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_RIGHT_TRANSPARENT_BG,SW_SHOW);

        if(pPrEditData->u8RenameIndex+1 < PROGRAM_EDIT_PAGE_NUM)
        {
            MApp_ZUI_API_ShowWindow(
            _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(pPrEditData->u8RenameIndex+1),SW_SHOW);
        }

        if(pPrEditData->u8RenameIndex == PROGRAM_EDIT_PAGE_NUM -1) //Move button when at last item
        {
            RECT rect;
            MApp_ZUI_API_GetWindowRect(HWND_PREDIT_BOTTOM_HALF_MENU_BTN, &rect);
            MApp_ZUI_API_MoveAllSuccessors(HWND_PREDIT_BOTTOM_HALF_MENU_BTN, rect.left, rect.top - PROGRAM_EDIT_ITEM_INTERVAL);
            MApp_ZUI_API_GetWindowRect(HWND_PREDIT_BOTTOM_HALF_GREEN_BTN, &rect);
            MApp_ZUI_API_MoveAllSuccessors(HWND_PREDIT_BOTTOM_HALF_GREEN_BTN, rect.left, rect.top - PROGRAM_EDIT_ITEM_INTERVAL);
        }
    }

    _eProgramEditMode=MODE_PREDIT_NORMAL;
    _MApp_ZUI_ACT_ProgramEditResetButtonState();
    MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_PANE, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_BLUE_BG, SW_SHOW);


    if(pPrEditData->u16TotalChCount>0)
    {
    }
    else
    {
        _MApp_ZUI_ACT_ProgramEditSetIndexFocus(0xFF); //no focus...
    }
}

void MApp_ZUI_Keyboard_GetEditText(U8* u8str )
{
    U16 u16Number = 0;
    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, pPrEditData->wRenameProgramPosition, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

    msAPI_ATV_GetStationName((BYTE)u16Number, u8str);
}

BOOL MApp_ZUI_Keyboard_SetEditText(U8* str)
{
    U16 u16Number = 0;
    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, pPrEditData->wRenameProgramPosition, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    return msAPI_ATV_SetStationName((BYTE)u16Number, str);
}


static void _MApp_ProgramEdit_Key_RENAME(void)
{
    EN_SERVICE_TYPE u8Type;
    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(      MApp_ZUI_API_GetFocus());
    if (_eProgramEditMode==MODE_PREDIT_BLOCK)
        return;

    pPrEditData->u8RenameIndex = u16SrvPageCurIndex;
    pPrEditData->wRenameProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType,
    pPrEditData->wRenameProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

#if ENABLE_SBTVD_CM_APP
    if(msAPI_SRC_IS_SBTVD_InUse())
        return;
#endif

    if(u8Type == SERVICE_TYPE_ATV)
    {
        RECT rect  = {0, 0, 0, 0};
        _eProgramEditMode=MODE_PREDIT_RENAME;
        _MApp_ZUI_ACT_ProgramEditResetButtonState();
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_PANE, SW_HIDE);


        if(g_bKeyboardRename)
        {

            MApp_ZUI_API_ShowWindow(HWND_PREDIT_KEYBOARD,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_INFO_MSG_BOX,SW_SHOW);
            //MApp_ZUI_CTL_Keyboard_SetFnEditText(HWND_PREDIT_KEYBOARD,HWND_PREDIT_INFO_MSG_BOX,MApp_ZUI_Keyboard_GetEditText,MApp_ZUI_Keyboard_SetEditText);
            //MApp_ZUI_API_SetFocus(HWND_PREDIT_KEY_0);
            return;
        }
        else
        {
            MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_RENAME_BG, SW_SHOW);
            MApp_ZUI_API_GetWindowRect(
                _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(u16SrvPageCurIndex), &rect);
            MApp_ZUI_API_MoveAllSuccessors(HWND_PREDIT_RENAME_PANE, rect.left, rect.top + (PROGRAM_EDIT_ITEM_INTERVAL*2));
        }


        if(u16SrvPageCurIndex+1 < PROGRAM_EDIT_PAGE_NUM)
        {
            MApp_ZUI_API_ShowWindow(
            _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(u16SrvPageCurIndex+1),SW_HIDE);
        }
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_RENAME_PANE, SW_SHOW);


        if(pPrEditData->u8RenameIndex == PROGRAM_EDIT_PAGE_NUM -1) //Move button when at last item
        {
            MApp_ZUI_API_GetWindowRect(HWND_PREDIT_BOTTOM_HALF_GREEN_BTN, &rect);
            MApp_ZUI_API_MoveAllSuccessors(HWND_PREDIT_BOTTOM_HALF_GREEN_BTN, rect.left, rect.top + PROGRAM_EDIT_ITEM_INTERVAL);
        }

        MApp_ZUI_API_SetFocus(HWND_PREDIT_RENAME_CHAR0);

    }
}

static void _MApp_ProgramEdit_Key_MOVE(void)
{
    EN_SERVICE_TYPE u8Type;
    U16 g_wProgramPosition;
    U8 u16SrvPageCurIndex;

    if (_eProgramEditMode==MODE_PREDIT_BLOCK)
        return;
    if (_eProgramEditMode==MODE_PREDIT_MOVE)
    {
        MApp_ZUI_API_RestoreWindowRect(MApp_ZUI_API_GetFocus());
        _eProgramEditMode=MODE_PREDIT_NORMAL;
        _MApp_ZUI_ACT_ProgramEditResetButtonState();
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_PANE, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_BLUE_BG, SW_SHOW);
        return;
    }

    u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(MApp_ZUI_API_GetFocus());
    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

#if ENABLE_SBTVD_CM_APP
    if(msAPI_SRC_IS_SBTVD_InUse())
        return;
#endif

	if(u8Type == SERVICE_TYPE_ATV )
		return;

#if (PRG_EDIT_INPUT_LCN_MOVE == 0)
    if(u8Type == SERVICE_TYPE_ATV || FALSE == fEnableLCN)
#endif
    {
        _eProgramEditMode=MODE_PREDIT_MOVE;
#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
            u16MoveLCNInputValue = 0;
            u8MoveLCNDigitCount = 0;
#endif
        _MApp_ZUI_ACT_ProgramEditResetButtonState();
        MApp_ZUI_API_MoveWindowByOffset(MApp_ZUI_API_GetFocus(),0,-PROGRAM_EDIT_MOVE_OFFSET,0,2*PROGRAM_EDIT_MOVE_OFFSET);
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_PANE, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_YELLOW_BG, SW_SHOW);
        //MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_YELLOW_BTN, SW_SHOW);
    }
}

static void _MApp_ProgramEdit_Key_FAV(void)
{
    BOOLEAN bFav = false;
    BOOLEAN bSkip = 0;
    EN_SERVICE_TYPE u8Type;
    U16 u16CurPosition;
    U16 g_wProgramPosition;
    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(MApp_ZUI_API_GetFocus());
    if (_eProgramEditMode == MODE_PREDIT_BLOCK)
        return;

    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bFav, E_SERVICE_ATTR_FAVORITE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bSkip, E_SERVICE_ATTR_SKIPPED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    bFav = !bFav;
#if ENABLE_SBTVD_CM_APP
    if(msAPI_SRC_IS_SBTVD_InUse() && ANT_AIR == msAPI_ATV_GetCurrentAntenna())
    {
        MEMBER_SERVICETYPE eServiceType;

        msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(g_wProgramPosition,&eServiceType,&g_wProgramPosition);
        if(eServiceType == E_SERVICETYPE_ATV)
            u16CurPosition = (U16)g_wProgramPosition >> 8;
        else
            u16CurPosition = g_wProgramPosition;
    }
    else
#endif
  #if ENABLE_DVB
    if((u8Type != SERVICE_TYPE_ATV) && (IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING)))
    {
        u16CurPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition, (MEMBER_SERVICETYPE *)&u8Type);
    }
    else
  #endif
    {
        u16CurPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, g_wProgramPosition );
    }

#if ENABLE_DVB
  #if NORDIG_FUNC //for Nordig spec v2.0
    if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO) || (u8Type==SERVICE_TYPE_DATA))
  #else
    if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO))
  #endif
    {

        if(bSkip)
        {
            msAPI_CM_SkipProgram((MEMBER_SERVICETYPE)u8Type, u16CurPosition, !bSkip);
        }

        msAPI_CM_FavorProgram((MEMBER_SERVICETYPE)u8Type, u16CurPosition, bFav);

    }
    else
#endif
    if (u8Type == SERVICE_TYPE_ATV)
    {

        if(bSkip)
        {
            msAPI_ATV_SkipProgram(u16CurPosition, !bSkip);
        }

        msAPI_ATV_SetFavoriteProgram(u16CurPosition, bFav);

    }
    MApp_ZUI_API_InvalidateAllSuccessors(
        _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(u16SrvPageCurIndex));
}

static void _MApp_ProgramEdit_Key_FAV_ALL(void)
{
    BOOLEAN bFav = false;
    BOOLEAN bSkip = 0;
    EN_SERVICE_TYPE u8Type;
    U16 u16CurPosition;
    U16 g_wProgramPosition;
    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(MApp_ZUI_API_GetFocus());
    U8 Index;
    if (_eProgramEditMode == MODE_PREDIT_BLOCK)
        return;

    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;

    for(Index = 0; Index < pPrEditData->u16TotalChCount; Index++)
    {
        printf("--sven--Index:%d\n",Index);
        bFav = false;
        bSkip = false;
        msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, Index, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, Index, &bFav, E_SERVICE_ATTR_FAVORITE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, Index, &bSkip, E_SERVICE_ATTR_SKIPPED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        bFav = !bFav;
      #if ENABLE_DVB
        if((u8Type != SERVICE_TYPE_ATV) && (IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING)))
        {
            u16CurPosition = msAPI_CM_GetPositionbyListPosition(Index, (MEMBER_SERVICETYPE *)&u8Type);
        }
        else
      #endif
        {
            u16CurPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, Index );
        }

#if ENABLE_DVB
      #if NORDIG_FUNC //for Nordig spec v2.0
        if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO) || (u8Type==SERVICE_TYPE_DATA))
      #else
        if ((u8Type==SERVICE_TYPE_DTV) || (u8Type==SERVICE_TYPE_RADIO))
      #endif
        {

            if(bSkip)
            {
                msAPI_CM_SkipProgram((MEMBER_SERVICETYPE)u8Type, u16CurPosition, !bSkip);
            }

            msAPI_CM_FavorProgram((MEMBER_SERVICETYPE)u8Type, u16CurPosition, bFav);

        }
        else
#endif
        if (u8Type == SERVICE_TYPE_ATV)
        {

            if(bSkip)
            {
                msAPI_ATV_SkipProgram(u16CurPosition, !bSkip);
            }

            msAPI_ATV_SetFavoriteProgram(u16CurPosition, bFav);

        }
            MApp_ZUI_API_InvalidateAllSuccessors(
                _MApp_ZUI_ACT_ProgramEditIndexMapToWindow(Index));
      }
}


//***************************************************
//* u8Direction : 0=> up, 1 => down
static void _MApp_ProgramEdit_Rename(U8 u8CharIdx, U8 u8Direction)
{
    U8 u8Temp[MAX_STATION_NAME]={0,0,0,0,0,0,0,0};
    U16 u16Number = 0;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, pPrEditData->wRenameProgramPosition, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    msAPI_ATV_GetStationName((BYTE)u16Number, u8Temp);


    if(u8CharIdx >= COUNTOF(_RenameHwndList) )
        return;
    if(u8Direction)
    {//down
        if(u8Temp[u8CharIdx] == 0x20)
            u8Temp[u8CharIdx] = 0x7A;
        else
            u8Temp[u8CharIdx]--;
    }
    else
    {//up
        if(u8Temp[u8CharIdx] == 0x7A)
            u8Temp[u8CharIdx] = 0x20;
        else
            u8Temp[u8CharIdx]++;
    }

    msAPI_ATV_SetStationName((BYTE)u16Number, u8Temp);
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_RENAME_PANE);
}

static U8 _MApp_ProgramEdit_Rename_GetChar(U8 u8CharIdx)
{
    U8 u8Temp[MAX_STATION_NAME];
    U16 u16Number=0;

    memset(&u8Temp,0,sizeof(u8Temp));
    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, pPrEditData->wRenameProgramPosition, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    msAPI_ATV_GetStationName((BYTE)u16Number, u8Temp);

    if(u8CharIdx >= strlen((char *)u8Temp))
        return 0;
    else
        return u8Temp[u8CharIdx];
}
////////////////////////////////////////////////////////////////

extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);
extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

void MApp_ZUI_ACT_AppShowProgramEdit(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_PROGRAM_EDIT;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    _enTargetState = STATE_OSDPAGE_CLEAN_UP;

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

#if ENABLE_DVB
    //MApp_Dmx_SetMonitorStatus(FALSE, EN_MONITOR_TABLE_ALL);
    MApp_SI_Disable_Auto_Update(TRUE);
#endif

    RECT_SET(rect,
        ZUI_PROGRAM_EDIT_XSTART, ZUI_PROGRAM_EDIT_YSTART,
        ZUI_PROGRAM_EDIT_WIDTH, ZUI_PROGRAM_EDIT_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    //////////////////////////////
    // init internal data structre, before ZUI create message...
    _ZUI_FREE(pPrEditData);
    pPrEditData = (PROGRAM_EDIT_DATA_STRUCT*)_ZUI_MALLOC(
        sizeof(PROGRAM_EDIT_DATA_STRUCT));
    if (pPrEditData == 0)
    {
        __ASSERT(0);
        ZUI_DBG_FAIL(printf("[ZUI]APREDIT\n"));
        ABORT();
        return;
    }
    //////////////////////////////

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }


#if ENABLE_SBTVD_CM_APP
    if(msAPI_SRC_IS_SBTVD_InUse())
    {
        if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
            _MApp_ProgramEdit_Init(SERVICE_TYPE_ATV);
        else
            _MApp_ProgramEdit_Init(SERVICE_TYPE_TV);
    }
    else
#endif
    {
        _MApp_ProgramEdit_Init(SERVICE_TYPE_TV);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_PREDIT_RENAME_PANE, SW_HIDE); //disable rename...
    MApp_ZUI_API_ShowWindow(HWND_PREDIT_KEYBOARD,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_PREDIT_INFO_MSG_BOX,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_PANE, SW_HIDE); //disable selection
    if(pPrEditData->u16TotalChCount > 0)
        MApp_ZUI_API_ShowWindow(HWND_PREDIT_SELECTION_BLUE_BG, SW_SHOW); //assume normal or block mode

    //show/hide necessary animation buttons...
    _MApp_ZUI_ACT_ProgramEditResetButtonState();

    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);

}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_ExecuteProgramEditAction(U16 act)
{
    if (pPrEditData == 0)
    {
        ZUI_DBG_FAIL(printf("[ZUI]EPREDIT\n"));
        ABORT();
        return TRUE;
    }

    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_CLEAN_UP;
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_GOTO_MAINMENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_MAIN_MENU;
            return TRUE;

        case EN_EXE_PREDIT_MENU:
            _MApp_ProgramEdit_Cmf_Key_MENU();
            return TRUE;

        case EN_EXE_PREDIT_SELECT:                         ///< program edit select
        case EN_EXE_PREDIT_UP:                               ///< program edit up
        case EN_EXE_PREDIT_DOWN:                             ///< program edit down
        case EN_EXE_PREDIT_PAGE_UP:                         ///< program edit page up
        case EN_EXE_PREDIT_PAGE_DOWN:                        ///< program edit page down
        case EN_EXE_PREDIT_SKIP:                             ///< program edit skip
        case EN_EXE_PREDIT_FAV:                              ///< program edit fav
        case EN_EXE_PREDIT_FAV_ALL:                              ///< program edit fav all
        case EN_EXE_PREDIT_LOCK:                             ///< program edit favorite
        case EN_EXE_PREDIT_DELETE:                           ///< program edit delete
        case EN_EXE_PREDIT_RENAME:                           ///< program edit rename
        case EN_EXE_PREDIT_MOVE:                             ///< program edit move
            if (pPrEditData->u16TotalChCount == 0)
            {
                return TRUE;
            }
            if(_eProgramEditMode == MODE_PREDIT_MOVE)
            {
                if((act == EN_EXE_PREDIT_SKIP)
                  ||(act == EN_EXE_PREDIT_FAV)
                  ||(act == EN_EXE_PREDIT_FAV_ALL)
                  ||(act == EN_EXE_PREDIT_DELETE)
                  ||(act == EN_EXE_PREDIT_RENAME))
                {
                    return TRUE;
                }
            }
            {
                U8 u8PageBehavior=PROGRAM_EDIT_COMMAND_INIT;

                switch(act)
                {
                    case EN_EXE_PREDIT_SELECT:
                        {
                            U16 u16ListOrdinal;
                            MEMBER_SERVICETYPE u8Type;
                            U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(MApp_ZUI_API_GetFocus());

                            u16ListOrdinal = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
                            msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, u16ListOrdinal, (BYTE*)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

                        #if( (ENABLE_DVB)&&(PRG_EDIT_INPUT_LCN_MOVE == 1) )
                            if (_eProgramEditMode==MODE_PREDIT_MOVE && u8Type != SERVICE_TYPE_ATV)
                            {

                                U16 u16ToPosition;
                                u16ToPosition = _MApp_ProgramEdit_GetProgramPosition(u8Type, u16ListOrdinal);

                                if (u16MoveLCNInputValue > 0)
                                {
                                    #if (UI_SKIN_SEL != UI_SKIN_960X540XI8)     //for fix complier error
                                    msAPI_CM_MoveLCN(u8Type, u16ToPosition, u16MoveLCNInputValue);
                                    #endif
                                }

                               #if MHEG5_ENABLE
                                    if(u8Type == SERVICE_TYPE_DTV)
                                            g_wCurrentTVRealServicePosition=g_wCurrentTVUserServicePosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DTV);
                                    else if(u8Type == SERVICE_TYPE_RADIO)
                                            g_wCurrentRadioRealServicePosition=g_wCurrentRadioUserServicePosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_RADIO);
                                    #if NORDIG_FUNC //for Nordig spec v2.0
                                     else if(u8Type == E_SERVICETYPE_DATA)
                                            g_wCurrentDataRealServicePosition=g_wCurrentDataUserServicePosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DATA);
                                    #endif
                                #endif

                                _MApp_ProgramEdit_Key_MOVE();
                            }
                            else
                        #endif
                            {
#if ENABLE_PVR
                                if(MApp_ZUI_ACT_PVR_Check_Switch_Channel((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, u16ListOrdinal) == FALSE)
                                {
                                    return TRUE;
                                }
#endif
                                _MApp_ChannelList_ChannelChange(u16ListOrdinal, pPrEditData->u8ServiceType, FALSE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

#if ENABLE_SBTVD_CM_APP
                                if(msAPI_SRC_IS_SBTVD_InUse())
                                {
                                    if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                                        pPrEditData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_ATV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                                    else
                                        pPrEditData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                                }
                                else
#endif
                                {
                                    pPrEditData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                                }
                             }
                             MApp_ZUI_API_InvalidateAllSuccessors(HWND_PREDIT_LIST_PANE);
                        }
                        return TRUE;

                    case EN_EXE_PREDIT_SKIP:
                        _MApp_ProgramEdit_Key_SKIP();
                        return TRUE;

                    case EN_EXE_PREDIT_FAV:
                        _MApp_ProgramEdit_Key_FAV();
                        return TRUE;

                    case EN_EXE_PREDIT_FAV_ALL:
                        _MApp_ProgramEdit_Key_FAV_ALL();
                        return TRUE;

                    case EN_EXE_PREDIT_LOCK:
                        _MApp_ProgramEdit_Key_LOCK();
                        return TRUE;

                    case EN_EXE_PREDIT_DELETE:
                        _MApp_ProgramEdit_Key_DELETE();
                        return TRUE;

                    case EN_EXE_PREDIT_RENAME:
                        _MApp_ProgramEdit_Key_RENAME();
                        return TRUE;

                    case EN_EXE_PREDIT_MOVE:
                        _MApp_ProgramEdit_Key_MOVE();
                        return TRUE;

                    case EN_EXE_PREDIT_UP:
                        if(_eProgramEditMode == MODE_PREDIT_MOVE)
                        {
                            EN_SERVICE_TYPE  u8Type;
                            U16 g_wProgramPosition;
                            U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(MApp_ZUI_API_GetFocus());
                            g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
                            msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

                            if (PRG_EDIT_INPUT_LCN_MOVE == 1)
                                u8PageBehavior = PROGRAM_EDIT_COMMAND_MOVE_UP;
                            else
                                return TRUE;
                        }
                        else
                        {
                            u8PageBehavior = PROGRAM_EDIT_COMMAND_UP;
                        }
                        break;

                    case EN_EXE_PREDIT_DOWN:
                        if(_eProgramEditMode == MODE_PREDIT_MOVE)
                        {
                            EN_SERVICE_TYPE  u8Type;
                            U16 g_wProgramPosition;
                            U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(MApp_ZUI_API_GetFocus());
                            g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM + u16SrvPageCurIndex;
                            msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

                            if (PRG_EDIT_INPUT_LCN_MOVE == 1)
                                u8PageBehavior = PROGRAM_EDIT_COMMAND_MOVE_DOWN;
                            else
                                return TRUE;
                        }
                        else
                        {
                            u8PageBehavior = PROGRAM_EDIT_COMMAND_DOWN;
                        }
                        break;

                    case EN_EXE_PREDIT_PAGE_UP:
                        u8PageBehavior = PROGRAM_EDIT_COMMAND_PRVPAGE;
                        break;

                    default:
                    case EN_EXE_PREDIT_PAGE_DOWN:
                        u8PageBehavior = PROGRAM_EDIT_COMMAND_NEXTPAGE;
                        break;
                }
                _MApp_ProgramEdit_Handler(0, 1, pPrEditData->u16TotalChCount,  u8PageBehavior);

            }
            return TRUE;
    }
    return FALSE;
}

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

BOOLEAN MApp_ZUI_ACT_HandleProgramEditKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_PREDIT_LIST_PANE, 0);

    //button click animation...
    {
        static  MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _key2btn[] =
        {
            {VK_MENU, HWND_PREDIT_BOTTOM_HALF_MENU_BTN},
            {VK_BLUE, HWND_PREDIT_BOTTOM_HALF_BLUE_BTN},
            {VK_YELLOW, HWND_PREDIT_BOTTOM_HALF_YELLOW_BTN},
            {VK_GREEN, HWND_PREDIT_BOTTOM_HALF_GREEN_BTN},
            {VK_GREEN, HWND_PREDIT_BOTTOM_HALF_LOCK_BTN},
            {VK_RED, HWND_PREDIT_BOTTOM_HALF_RED_BTN},
            {VK_CHANNEL_FAV_LIST, HWND_PREDIT_BOTTOM_HALF_FAV_BTN},
            {VK_HOME, HWND_PREDIT_BOTTOM_HALF_FAV_BTN},
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


    switch(key)
    {
        case VK_MENU:
        {
            if(_eProgramEditMode == MODE_PREDIT_BLOCK)
            {
                _enReturnMenuItem = STATE_RETURN_PROGRAM_BLOCK;
                MApp_ZUI_ACT_ExecuteProgramEditAction(EN_EXE_GOTO_MAINMENU);
                return TRUE;
            }
            else if(_eProgramEditMode == MODE_PREDIT_NORMAL)
            {
                _enReturnMenuItem = STATE_RETURN_PROGRAM_EDIT;
                MApp_ZUI_ACT_ExecuteProgramEditAction(EN_EXE_GOTO_MAINMENU);
                return TRUE;
            }
            else
            {
                return FALSE; // bypass the key
            }
        }
        case VK_EXIT:
            MApp_ZUI_ACT_ExecuteProgramEditAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;
#if 0//(NTV_FUNCTION_ENABLE) //wait to do
        case VK_RIGHT:
            msAPI_CM_RestoreProgramOrder();
            MApp_ZUI_API_InvalidateWindow(HWND_PREDIT_LIST_PANE);
            return TRUE;
#endif
        case VK_POWER:
            MApp_ZUI_ACT_ExecuteProgramEditAction(EN_EXE_POWEROFF);
            return TRUE;

#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
        case VK_NUM_0:
        case VK_NUM_1:
        case VK_NUM_2:
        case VK_NUM_3:
        case VK_NUM_4:
        case VK_NUM_5:
        case VK_NUM_6:
        case VK_NUM_7:
        case VK_NUM_8:
        case VK_NUM_9:
           {
                if (_eProgramEditMode==MODE_PREDIT_MOVE)
                    _MApp_ProgramEdit_Move_ProcDigitKey(key);
            }
            break;
#endif

        default:
            break;
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateProgramEdit(void)
{
    ZUI_MSG(printf("[]term:predit\n");)
    _ZUI_FREE(pPrEditData);

#if ENABLE_DVB
    //MApp_Dmx_SetMonitorStatus(TRUE, EN_MONITOR_TABLE_ALL);
    MApp_SI_Disable_Auto_Update(FALSE);
#endif

    MApp_OSDPage_SetState(_enTargetState);
}

LPTSTR MApp_ZUI_ACT_GetProgramEditDynamicText(HWND hwnd)
{

    if(MApp_ZUI_API_IsSuccessor(HWND_PREDIT_KEYBOARD,hwnd) || MApp_ZUI_API_IsSuccessor(HWND_PREDIT_INFO_MSG_BOX,hwnd))
        return MApp_ZUI_CTL_KeyboardGetDynamicText(HWND_PREDIT_KEYBOARD,hwnd);

    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_PREDIT_TOP_HALF_TITLE:
            if (_eProgramEditMode == MODE_PREDIT_BLOCK)
                u16TempID = en_str_Block_Program;
            else
                u16TempID = en_str_Programme_Edit;
            break;

        case HWND_PREDIT_ITEM0_TEXT:
        case HWND_PREDIT_ITEM1_TEXT:
        case HWND_PREDIT_ITEM2_TEXT:
        case HWND_PREDIT_ITEM3_TEXT:
        case HWND_PREDIT_ITEM4_TEXT:
        case HWND_PREDIT_ITEM5_TEXT:
        case HWND_PREDIT_ITEM6_TEXT:
        case HWND_PREDIT_ITEM7_TEXT:
        case HWND_PREDIT_ITEM8_TEXT:
        case HWND_PREDIT_ITEM9_TEXT:
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(hwnd);
                EN_SERVICE_TYPE  u8Type;
                U16 g_wProgramPosition;
                if(_eProgramEditMode == MODE_PREDIT_MOVE)
                {
                    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(      MApp_ZUI_API_GetFocus());
                    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+ u16SrvPageCurIndex;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, ( BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                }
                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+  u8VisIndex;
                if (g_wProgramPosition >= pPrEditData->u16TotalChCount)
                    break;
                {
                    LPTSTR str = CHAR_BUFFER;

                    MEMBER_SERVICETYPE bServiceType;
                    U16 u16Number=0;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, ( BYTE *)&bServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    if(msAPI_ATV_GetActiveProgramCount()==0 && bServiceType==E_SERVICETYPE_ATV)//Makes channel "0" when no ATV
                        u16Number=0;

            #if ENABLE_DVB
                    U16 uProgNumStrlen = 0;  // 130531 Compile
                    if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((bServiceType == E_SERVICETYPE_DTV)||(bServiceType == E_SERVICETYPE_RADIO)||(bServiceType == E_SERVICETYPE_DATA)))
                    {
                        MApp_ZUI_API_GetU16String(u16Number);
                        uProgNumStrlen = MApp_ZUI_API_Strlen(str);
                        str += MApp_ZUI_API_Strlen(str);
                        *str++ = CHAR_SPACE;
                        g_wProgramPosition = msAPI_CM_GetPositionbyListPosition(g_wProgramPosition,&bServiceType);
                        MApp_CharTable_GetServiceNameToUCS2(bServiceType, g_wProgramPosition, str, KEEP_CONTROL_CODE_NONE);
                        str += MApp_ZUI_API_Strlen(str);
                    }
                    else if (bServiceType == E_SERVICETYPE_DTV)
                    {
                        MApp_ZUI_DTV_ChNumString(u16Number, str);
                        str += MApp_ZUI_API_Strlen(str);
                        *str++ = CHAR_SPACE;

                    #if ENABLE_SBTVD_CM_APP
                        if(msAPI_SRC_IS_SBTVD_InUse())
                        {
                            msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(g_wProgramPosition,&bServiceType,&g_wProgramPosition);
                        }
                    #endif
                        MApp_CharTable_GetServiceNameToUCS2(bServiceType, g_wProgramPosition, str, KEEP_CONTROL_CODE_NONE);
                        str += MApp_ZUI_API_Strlen(str);
                    }
                    else if (bServiceType == E_SERVICETYPE_RADIO)
                    {
                        MApp_ZUI_DTV_ChNumString(u16Number, str);
                        str += MApp_ZUI_API_Strlen(str);
                        *str++ = CHAR_SPACE;
                        MApp_CharTable_GetServiceNameToUCS2(bServiceType, g_wProgramPosition-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY), str, KEEP_CONTROL_CODE_NONE);
                        str += MApp_ZUI_API_Strlen(str);
                    }
                #if NORDIG_FUNC //for Nordig spec v2.0
                    else if (bServiceType == E_SERVICETYPE_DATA)
                    {
                        MApp_ZUI_API_GetU16String(u16Number);
                        str += MApp_ZUI_API_Strlen(str);
                        *str++ = CHAR_SPACE;
                        MApp_CharTable_GetServiceNameToUCS2(bServiceType, g_wProgramPosition-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY), str, KEEP_CONTROL_CODE_NONE);
                        str += MApp_ZUI_API_Strlen(str);
                    }
                #endif
                    else
            #endif
                    if (bServiceType == E_SERVICETYPE_ATV)
                    {
#if ENABLE_SBTVD_CM_APP
                        if(msAPI_SRC_IS_SBTVD_InUse())
                        {
                            MApp_ZUI_API_GetU16String(u16Number+1);
                        }
                        else
#endif
                        {
                            U8 u8Temp[MAX_STATION_NAME];
                            MApp_ZUI_API_GetU16String(u16Number+1);
                            str += MApp_ZUI_API_Strlen(str);
                            *str++ = CHAR_SPACE;
                            if(msAPI_ATV_GetStationName((BYTE)u16Number, u8Temp)) // Coverity 95842
                            {
                                MApp_U8StringToU16String(u8Temp, str, MAX_STATION_NAME);
                            }
                            str += MApp_ZUI_API_Strlen(str);
                        }
                    }
#if (ENABLE_DTV)
                    if ((str-CHAR_BUFFER) > MAX_LCN_SERVICE_NAME_LENGTH)
                    {
                        (CHAR_BUFFER)[MAX_LCN_SERVICE_NAME_LENGTH] = 0;
                    }
#else
                    if ((str-CHAR_BUFFER) > 16)
                    {
                        (CHAR_BUFFER)[16] = 0;
                    }
#endif
                    return CHAR_BUFFER;

                }


            }
            break;
#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
        case HWND_PREDIT_ITEM0_LCN_INPUT:
        case HWND_PREDIT_ITEM1_LCN_INPUT:
        case HWND_PREDIT_ITEM2_LCN_INPUT:
        case HWND_PREDIT_ITEM3_LCN_INPUT:
        case HWND_PREDIT_ITEM4_LCN_INPUT:
        case HWND_PREDIT_ITEM5_LCN_INPUT:
        case HWND_PREDIT_ITEM6_LCN_INPUT:
        case HWND_PREDIT_ITEM7_LCN_INPUT:
        case HWND_PREDIT_ITEM8_LCN_INPUT:
        case HWND_PREDIT_ITEM9_LCN_INPUT:
        {

            if (u16MoveLCNInputValue == 0 || _eProgramEditMode != MODE_PREDIT_MOVE)
            {
                u16TempID = Empty;
            }
            else
            {
                LPTSTR str = CHAR_BUFFER;
                MApp_UlongToU16String((U32)u16MoveLCNInputValue, str, (S8)MApp_GetNoOfDigit((U32)u16MoveLCNInputValue));

                return CHAR_BUFFER;
            }

        }
            break;
#endif
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

U16 MApp_ZUI_ACT_GetProgramEditDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    switch(hwnd)
    {
        case HWND_PREDIT_ITEM0_TYPE:
        case HWND_PREDIT_ITEM1_TYPE:
        case HWND_PREDIT_ITEM2_TYPE:
        case HWND_PREDIT_ITEM3_TYPE:
        case HWND_PREDIT_ITEM4_TYPE:
        case HWND_PREDIT_ITEM5_TYPE:
        case HWND_PREDIT_ITEM6_TYPE:
        case HWND_PREDIT_ITEM7_TYPE:
        case HWND_PREDIT_ITEM8_TYPE:
        case HWND_PREDIT_ITEM9_TYPE:
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(hwnd);
                EN_SERVICE_TYPE  u8Type;
                U16 g_wProgramPosition;

                if(_eProgramEditMode == MODE_PREDIT_RENAME && pPrEditData->u8RenameIndex == u8VisIndex)
                {
                    break;
                }

                if(_eProgramEditMode ==   MODE_PREDIT_MOVE)
                {
                    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(      MApp_ZUI_API_GetFocus());
                    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+ u16SrvPageCurIndex;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                }
                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+  u8VisIndex;
                if (g_wProgramPosition >= pPrEditData->u16TotalChCount)
                    break;
                {
                   // EN_SERVICE_TYPE u8Type;
                    BOOLEAN bLock = false;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bLock, E_SERVICE_ATTR_LOCKED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    if (ds_type == DS_FOCUS && !bLock)
                    {
                        if (u8Type == SERVICE_TYPE_DTV)
                        {
                            return E_BMP_IDLE_IMG_ICON_DTV_FOCUS;
                        }
                        else if (u8Type == SERVICE_TYPE_RADIO)
                        {
                            return E_BMP_IDLE_IMG_ICON_RADIO_FOCUS;
                        }
#if NORDIG_FUNC //for Nordig spec v2.0
                        else if (u8Type == SERVICE_TYPE_DATA)
                        {
                            return E_BMP_IDLE_IMG_ICON_DATA_FOCUS;
                        }
#endif
                        else if (u8Type == SERVICE_TYPE_ATV)
                        {
#if ENABLE_SBTVD_CM_APP
                            if(msAPI_SRC_IS_SBTVD_InUse())
                            {
                                if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                                    return E_BMP_ICON_CATV_F;
                                else
                                    return E_BMP_IDLE_IMG_ICON_ATV_FOCUS;
                            }
                            else
#endif
                            {
                                return E_BMP_IDLE_IMG_ICON_ATV_FOCUS;
                            }
                        }
                    }
                    else
                    {
                        if (u8Type == SERVICE_TYPE_DTV)
                        {
                            return E_BMP_IDLE_IMG_ICON_DTV_UNFOCUS;
                        }
                        else if (u8Type == SERVICE_TYPE_RADIO)
                        {
                            return E_BMP_IDLE_IMG_ICON_RADIO_UNFOCUS;
                        }
#if NORDIG_FUNC //for Nordig spec v2.0
                        else if (u8Type == SERVICE_TYPE_DATA)
                        {
                            return E_BMP_IDLE_IMG_ICON_DATA_UNFOCUS;
                        }
#endif
                        else if (u8Type == SERVICE_TYPE_ATV)
                        {
#if ENABLE_SBTVD_CM_APP
                            if(msAPI_SRC_IS_SBTVD_InUse())
                            {
                                if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                                    return E_BMP_ICON_CATV_N;
                                else
                                    return E_BMP_IDLE_IMG_ICON_ATV_UNFOCUS;
                            }
                            else
#endif
                            {
                                return E_BMP_IDLE_IMG_ICON_ATV_UNFOCUS;
                            }
                        }
                    }
                }


            }
            break;

        case HWND_PREDIT_ITEM0_LOCK:
        case HWND_PREDIT_ITEM1_LOCK:
        case HWND_PREDIT_ITEM2_LOCK:
        case HWND_PREDIT_ITEM3_LOCK:
        case HWND_PREDIT_ITEM4_LOCK:
        case HWND_PREDIT_ITEM5_LOCK:
        case HWND_PREDIT_ITEM6_LOCK:
        case HWND_PREDIT_ITEM7_LOCK:
        case HWND_PREDIT_ITEM8_LOCK:
        case HWND_PREDIT_ITEM9_LOCK:
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(hwnd);
                EN_SERVICE_TYPE u8Type;
                U16 g_wProgramPosition;

                if(_eProgramEditMode == MODE_PREDIT_RENAME && pPrEditData->u8RenameIndex == u8VisIndex)
                {
                    break;
                }

                if(_eProgramEditMode ==   MODE_PREDIT_MOVE)
                {
                    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(      MApp_ZUI_API_GetFocus());
                    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+ u16SrvPageCurIndex;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                }
                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+  u8VisIndex;
                if (g_wProgramPosition >= pPrEditData->u16TotalChCount)
                    break;
                {
                    BOOLEAN bLock = false;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bLock, E_SERVICE_ATTR_LOCKED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    if (bLock)
                    {
                        if (ds_type == DS_FOCUS)
                        {
                            return E_BMP_IDLE_IMG_ICON_LOCK_FOCUS;
                        }
                        else
                        {
                            return E_BMP_IDLE_IMG_ICON_LOCK_UNFOCUS;
                        }
                    }
                }


            }
            break;

        case HWND_PREDIT_ITEM0_FAV:
        case HWND_PREDIT_ITEM1_FAV:
        case HWND_PREDIT_ITEM2_FAV:
        case HWND_PREDIT_ITEM3_FAV:
        case HWND_PREDIT_ITEM4_FAV:
        case HWND_PREDIT_ITEM5_FAV:
        case HWND_PREDIT_ITEM6_FAV:
        case HWND_PREDIT_ITEM7_FAV:
        case HWND_PREDIT_ITEM8_FAV:
        case HWND_PREDIT_ITEM9_FAV:
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(hwnd);
                EN_SERVICE_TYPE u8Type;
                U16 g_wProgramPosition;

                if(_eProgramEditMode == MODE_PREDIT_RENAME && pPrEditData->u8RenameIndex == u8VisIndex)
                {
                    break;
                }

                if(_eProgramEditMode ==   MODE_PREDIT_MOVE)
                {
                    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(      MApp_ZUI_API_GetFocus());
                    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+ u16SrvPageCurIndex;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                }
                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+  u8VisIndex;
                if (g_wProgramPosition >= pPrEditData->u16TotalChCount)
                    break;
                {
                    BOOLEAN bLock = false;
                    BOOLEAN bFav = false;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bLock, E_SERVICE_ATTR_LOCKED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bFav, E_SERVICE_ATTR_FAVORITE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    if (bFav && _eProgramEditMode != MODE_PREDIT_BLOCK)
                    {
                        //if (ds_type == DS_FOCUS && !bLock)
                        if (ds_type == DS_FOCUS)
                        {
                            return E_BMP_IDLE_IMG_ICON_FAVORITE_FOCUS;
                        }
                        else
                        {
                            return E_BMP_IDLE_IMG_ICON_FAVORITE_UNFOCUS;
                        }
                    }
                }
            }
            break;

        case HWND_PREDIT_ITEM0_SKIP:
        case HWND_PREDIT_ITEM1_SKIP:
        case HWND_PREDIT_ITEM2_SKIP:
        case HWND_PREDIT_ITEM3_SKIP:
        case HWND_PREDIT_ITEM4_SKIP:
        case HWND_PREDIT_ITEM5_SKIP:
        case HWND_PREDIT_ITEM6_SKIP:
        case HWND_PREDIT_ITEM7_SKIP:
        case HWND_PREDIT_ITEM8_SKIP:
        case HWND_PREDIT_ITEM9_SKIP:
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(hwnd);
                EN_SERVICE_TYPE u8Type;
                U16 g_wProgramPosition;

                if(_eProgramEditMode == MODE_PREDIT_RENAME && pPrEditData->u8RenameIndex == u8VisIndex)
                {
                    break;
                }

                if(_eProgramEditMode ==   MODE_PREDIT_MOVE)
                {
                    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ProgramEditWindowMapToIndex(      MApp_ZUI_API_GetFocus());
                    g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+ u16SrvPageCurIndex;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                }
                g_wProgramPosition = pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM+  u8VisIndex;
                if (g_wProgramPosition >= pPrEditData->u16TotalChCount)
                    break;
                {
                    BOOLEAN bLock = false;
                    BOOLEAN bSkip = false;
                    BOOLEAN bFav = false;
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bLock, E_SERVICE_ATTR_LOCKED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bSkip, E_SERVICE_ATTR_SKIPPED, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pPrEditData->u8ServiceType, g_wProgramPosition, &bFav, E_SERVICE_ATTR_FAVORITE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    if (bSkip && _eProgramEditMode != MODE_PREDIT_BLOCK)
                    {
                        //if (ds_type == DS_FOCUS && !bLock)
                        if (ds_type == DS_FOCUS && !bFav)
                        {
                            return E_BMP_ICON_CHANNEL_SKIP_SEL;
                        }
                        else
                        {
                            return E_BMP_ICON_CHANNEL_SKIP_UNSEL;
                        }
                    }

                }


            }
            break;

    }

    return 0xFFFF; //for empty bitmap....
}

////////////////////////////////////////////////////////////////



S32 MApp_ZUI_ACT_PrEditRenameInputWinProc(HWND hwnd, PMSG msg)
{
    static BOOLEAN _bRenameBlinkBlack = FALSE;

    U8 i;
    for (i = 0; i < COUNTOF(_RenameHwndList); i++)
    {
        if (hwnd == _RenameHwndList[i])
            break;
    }
    if (i == COUNTOF(_RenameHwndList)) //if not in the data list, we do nothing...
        return DEFAULTWINPROC(hwnd, msg);

    switch(msg->message)
    {
        case MSG_NOTIFY_SETFOCUS:
            {
                //enable blinking
                MApp_ZUI_API_SetTimer(hwnd, 0, 500);
                MApp_ZUI_API_InvalidateWindow(hwnd);
                MApp_ZUI_API_SetTimer(HWND_PREDIT_RENAME_CHAR_BLK, 0, 500);
                MApp_ZUI_API_InvalidateWindow(HWND_PREDIT_RENAME_CHAR_BLK);
            }
            return 0;

        case MSG_TIMER:
            {
                //blinking
                _bRenameBlinkBlack = !_bRenameBlinkBlack;
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            break;

        case MSG_NOTIFY_KILLFOCUS:
        case MSG_NOTIFY_HIDE:
            {
                //disable blinking
                MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_API_KillTimer(HWND_PREDIT_RENAME_CHAR_BLK,0);
            }
            return 0;

        case MSG_KEYDOWN:
            {
                MApp_ZUI_API_ResetTimer(HWND_PREDIT_LIST_PANE, 0);

                if (VK_UP == msg->wParam)
                {
                    _MApp_ProgramEdit_Rename(i, 0);
                    MApp_ZUI_API_InvalidateWindow(hwnd);
                    return 0;
                }
                else if (VK_DOWN == msg->wParam)
                {
                    _MApp_ProgramEdit_Rename(i, 1);
                    MApp_ZUI_API_InvalidateWindow(hwnd);
                    return 0;
                }
                else if (VK_LEFT== msg->wParam)
                {
                    if (i!=0)
                    {
                        RECT rect;

                        memset(&rect, 0, sizeof(RECT));

                        MApp_ZUI_API_SetFocus(_RenameHwndList[i-1]);
                        MApp_ZUI_API_GetWindowRect(_RenameHwndList[i-1], &rect);
                        _bRenameBlinkBlack = FALSE;
                        MApp_ZUI_API_InvalidateWindow(HWND_PREDIT_RENAME_CHAR_BLK);
                        MApp_ZUI_API_MoveAllSuccessors(HWND_PREDIT_RENAME_CHAR_BLK, rect.left, rect.top);
                    }

                    return 0;
                }
                else if (VK_RIGHT== msg->wParam)
                {
                    if (i<4)
                    {
                        RECT rect;

                        memset(&rect, 0, sizeof(RECT));

                        MApp_ZUI_API_SetFocus(_RenameHwndList[i+1]);
                        MApp_ZUI_API_GetWindowRect(_RenameHwndList[i+1], &rect);
                        _bRenameBlinkBlack = FALSE;
                        MApp_ZUI_API_InvalidateWindow(HWND_PREDIT_RENAME_CHAR_BLK);
                        MApp_ZUI_API_MoveAllSuccessors(HWND_PREDIT_RENAME_CHAR_BLK, rect.left, rect.top);

                    }
                    return 0;
                }
            }
            break;

        case MSG_PAINT:
            {

                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)msg->wParam;

                //step1:draw word blink
                if (param->bIsFocus)
                {
                    DRAW_TEXT_OUT_DYNAMIC * dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
                    LPTSTR str = CHAR_BUFFER;
                    U16 u16TextIndex;
                    u16TextIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, DS_NORMAL, CP_TEXT_OUT);

                    if (dyna)
                    {
                        _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, dyna);
                        if (_bRenameBlinkBlack)
                        {
                            str[0] = CHAR_US;
                        }
                        else
                        {
                            str[0] = CHAR_SPACE;
                        }
                        str[1] = 0;
                        dyna->pString = str;
                        _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, dyna, &param->dc, param->rect);
                        _ZUI_FREE(dyna);
                    }
                    else
                    {
                        __ASSERT(0);
                    }

                }
                //step2: draw text
                {
                    DRAW_TEXT_OUT_DYNAMIC * dyna;
                    U16 u16TextIndex;
                    u16TextIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, (param->bIsFocus)? DS_FOCUS: DS_NORMAL, CP_TEXT_OUT);

                    if (u16TextIndex != 0xFFFF)
                    {
                        if (param->bIsFocus)
                            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hwnd);
                        else
                            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hwnd);

                        dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
                        if (dyna)
                        {
                            LPTSTR str = CHAR_BUFFER;
                            _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, dyna);
                            str[0] = _MApp_ProgramEdit_Rename_GetChar(i);
                            str[1] = 0;
                            dyna->pString = str;
                            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, dyna, &param->dc, param->rect);
                            _ZUI_FREE(dyna);
                        }
                        else
                        {
                            __ASSERT(0);
                        }
                    }
                }
            }
            return 0;

            default:
                break;

    }

    return DEFAULTWINPROC(hwnd, msg);
}

OSD_COLOR MApp_ZUI_ACT_GetProgramEditDynamicColor(HWND hwnd, DRAWSTYLE_TYPE type, OSD_COLOR colorOriginal)
{
    U16 u16SrvPageCurIndex;
    U16 g_wProgramPosition;
    UNUSED(type);

    u16SrvPageCurIndex = (U16)_MApp_ZUI_ACT_ProgramEditWindowMapToIndex(hwnd);
    g_wProgramPosition = (U16)(pPrEditData->u8CurrentPage*PROGRAM_EDIT_PAGE_NUM) + u16SrvPageCurIndex;
    if(g_wProgramPosition == pPrEditData->u16CurCh)
    {
        if(u16SrvPageCurIndex == _MApp_ZUI_ACT_ProgramEditWindowMapToIndex( MApp_ZUI_API_GetFocus())) //is the high light program
            return PRG_EDIT_CURRENT_CN_TEXT_HL_COLOR;
        else
            return PRG_EDIT_CURRENT_CN_TEXT_COLOR;
    }
    return colorOriginal;
}


#undef MAPP_ZUI_ACTPREDIT_C
