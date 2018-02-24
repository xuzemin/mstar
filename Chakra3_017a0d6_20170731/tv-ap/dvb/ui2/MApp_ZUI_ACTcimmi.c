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

#define MAPP_ZUI_ACTCIMMI_C
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
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_GlobalFunction.h"
#include "MApp_ZUI_ACTcimmi.h"
#include "msAPI_Memory.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTmenudlgfunc.h" //share U16 PasswordInput1
#include "string.h"
#include "msAPI_CI.h"
#include "MApp_CIMMI.h"
#include "msAPI_audio.h"
#include "MApp_Audio.h"
#include "MApp_TV.h"
#include "MApp_GlobalFunction.h"
#include "msAPI_audio.h"
#include "MApp_DataBase_Gen.h"

/////////////////////////////////////////////////////////////////////

typedef enum _CIMMI_MSGBOX_MODE
{
    EN_MSGBOX_MODE_INVALID,
    EN_MSGBOX_MODE_CI_DETECTED,                     ///< show CI detected
    EN_MSGBOX_MODE_CI_REMOVED,                     ///< show CI removed
    EN_MSGBOX_MODE_CI_LOAD_INFO,                     ///< show CI load info
    EN_MSGBOX_MODE_CI_NO_MODULE,                     ///< show CI no module
    EN_MSGBOX_MODE_CI_TRY_AGAIN,                     ///< show CI try again
} CIMMI_MSGBOX_MODE;

static CIMMI_MSGBOX_MODE _eMsgBoxMode;

/////////////////////////////////////////////////////////////////////
extern EN_CIMMI_STATE enCIEvtState;

static EN_CIMMI_STATE _enTargetCIMMIState=STATE_CIMMI_EVENT_HANDLE;

static CIMMI_INFO * _pInfo = 0;

static U8 _u8MenuCIMMICurIndex = 0;
static U8 _u8MenuCIMMIScrollIndex = 0;
static U8 u8PinNum = 0;
#if ENABLE_CI_PLUS
BOOLEAN bOPRefreshMsgbox = FALSE; //if show op refresh msgbox, bOPRefreshMsgbox will be true
extern DWORD        m_u32EpgNextStartUpTime_Temp;
extern BOOLEAN        m_u32EpgNextStartUpTime_Temp_Flag;
#endif
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
//extern void _MApp_ZUI_API_DrawDynamicComponent(DRAWCOMPONENT component, const void * param, const GRAPHIC_DC * pdc, const RECT * rect);

#define UI_CIMMI_ITEM_NUM 7
static  HWND _ZUI_TBLSEG _CIMMIItemHwndList[UI_CIMMI_ITEM_NUM]=
{
    HWND_CIMMI_SELECTION_ITEM1,
    HWND_CIMMI_SELECTION_ITEM2,
    HWND_CIMMI_SELECTION_ITEM3,
    HWND_CIMMI_SELECTION_ITEM4,
    HWND_CIMMI_SELECTION_ITEM5,
    HWND_CIMMI_SELECTION_ITEM6,
    HWND_CIMMI_SELECTION_ITEM7,
};

#define UI_CIMMI_PIN_NUM 20
static  HWND _ZUI_TBLSEG _CIMMIPinHwndList[UI_CIMMI_PIN_NUM]=
{
    HWND_CIMMI_INPUT_PIN1,
    HWND_CIMMI_INPUT_PIN2,
    HWND_CIMMI_INPUT_PIN3,
    HWND_CIMMI_INPUT_PIN4,
    HWND_CIMMI_INPUT_PIN5,
    HWND_CIMMI_INPUT_PIN6,
    HWND_CIMMI_INPUT_PIN7,
    HWND_CIMMI_INPUT_PIN8,
    HWND_CIMMI_INPUT_PIN9,
    HWND_CIMMI_INPUT_PIN10,
    HWND_CIMMI_INPUT_PIN11,
    HWND_CIMMI_INPUT_PIN12,
    HWND_CIMMI_INPUT_PIN13,
    HWND_CIMMI_INPUT_PIN14,
    HWND_CIMMI_INPUT_PIN15,
    HWND_CIMMI_INPUT_PIN16,
    HWND_CIMMI_INPUT_PIN17,
    HWND_CIMMI_INPUT_PIN18,
    HWND_CIMMI_INPUT_PIN19,
    HWND_CIMMI_INPUT_PIN20,
};

static U8 _MApp_ZUI_ACT_CIMMIWindowMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < UI_CIMMI_ITEM_NUM; i++)
    {
        if (hwnd == _CIMMIItemHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_CIMMIItemHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

HWND _MApp_ZUI_ACT_CIMMIWindowMapToWindow(U8 u8Index)
{
    if (u8Index >= COUNTOF(_CIMMIItemHwndList))
        return HWND_INVALID;
    return _CIMMIItemHwndList[u8Index];

}

static U8 _MApp_ZUI_ACT_CIMMIGetMenuListCnt(void)
{
        U8 total_count = 0;

        if(_pInfo)
        {
            if(_pInfo->enType==EN_CIMMI_TYPE_MENU)
                    total_count = (U16)_pInfo->content.menu_data.ListCnt;
            else if(_pInfo->enType==EN_CIMMI_TYPE_LIST)
                    total_count = (U16)_pInfo->content.list_data.ListCnt;
        }
        return total_count;
}

void _MApp_ZUI_ACT_CIMMINavUp(U8 total_count)
{
    if (total_count >= UI_CIMMI_ITEM_NUM)
    {
        if (_MApp_ZUI_ACT_CIMMIWindowMapToIndex(MApp_ZUI_API_GetFocus()) > 0)
        {
            _u8MenuCIMMICurIndex--;
            MApp_ZUI_API_SetFocus(MApp_ZUI_API_GetFocus()-1);
        }
        else
        {
            if (_u8MenuCIMMIScrollIndex+_MApp_ZUI_ACT_CIMMIWindowMapToIndex(MApp_ZUI_API_GetFocus()) == 0)
            {
                _u8MenuCIMMIScrollIndex=total_count-UI_CIMMI_ITEM_NUM;
                _u8MenuCIMMICurIndex = total_count-1;
                MApp_ZUI_API_SetFocus(HWND_CIMMI_SELECTION_ITEM7);
            }
            else
            {
                _u8MenuCIMMIScrollIndex--;
                _u8MenuCIMMICurIndex--;
                MApp_ZUI_API_SetFocus(HWND_CIMMI_SELECTION_ITEM1);
            }
        }
    }
    else
    {
        if (_MApp_ZUI_ACT_CIMMIWindowMapToIndex(MApp_ZUI_API_GetFocus()) > 0)
        {
            if (_u8MenuCIMMICurIndex > 0)
                _u8MenuCIMMICurIndex--;
            MApp_ZUI_API_SetFocus(MApp_ZUI_API_GetFocus()-1);
        }
        else
        {
            _u8MenuCIMMIScrollIndex=0;
            _u8MenuCIMMICurIndex = total_count-1;
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_CIMMIWindowMapToWindow(_u8MenuCIMMICurIndex%UI_CIMMI_ITEM_NUM));
        }
    }
}

void _MApp_ZUI_ACT_CIMMINavDown(U8 total_count)
{
    if (total_count >= UI_CIMMI_ITEM_NUM)
    {
        if (_MApp_ZUI_ACT_CIMMIWindowMapToIndex(MApp_ZUI_API_GetFocus()) < (UI_CIMMI_ITEM_NUM-1))
        {
            _u8MenuCIMMICurIndex++;
            MApp_ZUI_API_SetFocus(MApp_ZUI_API_GetFocus()+1);
        }
        else
        {
            if (_u8MenuCIMMIScrollIndex+_MApp_ZUI_ACT_CIMMIWindowMapToIndex(MApp_ZUI_API_GetFocus()) >= (total_count -1))
            {
                _u8MenuCIMMIScrollIndex=0;
                _u8MenuCIMMICurIndex = 0;
                MApp_ZUI_API_SetFocus(HWND_CIMMI_SELECTION_ITEM1);
            }
            else
            {
                _u8MenuCIMMIScrollIndex++;
                _u8MenuCIMMICurIndex++;
                MApp_ZUI_API_SetFocus(HWND_CIMMI_SELECTION_ITEM7);
            }
        }
    }
    else
    {
        if (_MApp_ZUI_ACT_CIMMIWindowMapToIndex(MApp_ZUI_API_GetFocus()) < (total_count-1))
        {
            _u8MenuCIMMICurIndex++;
            MApp_ZUI_API_SetFocus(MApp_ZUI_API_GetFocus()+1);
        }
        else
        {
            _u8MenuCIMMIScrollIndex=0;
            _u8MenuCIMMICurIndex = 0;
            MApp_ZUI_API_SetFocus(HWND_CIMMI_SELECTION_ITEM1);
        }
    }
}

void MApp_ZUI_ACT_AppShowCIMMI(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_CIMMI;

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

    RECT_SET(rect,
        ZUI_CIMMI_XSTART, ZUI_CIMMI_YSTART,
        ZUI_CIMMI_WIDTH, ZUI_CIMMI_HEIGHT);

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

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);

    //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_MAIN_MENU_SHOWUP, E_ZUI_STATE_RUNNING);

    if (_pInfo == 0)
    {
        _pInfo = (CIMMI_INFO*)_ZUI_MALLOC(sizeof(CIMMI_INFO));
    }
    if (_pInfo)
    {
        _pInfo->aTitleContent[0] = 0;
        _pInfo->enType = EN_CIMMI_TYPE_NONE;
    }
    else
    {
        __ASSERT(0);
    }

    _eMsgBoxMode = EN_MSGBOX_MODE_INVALID;

}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleCIMMIKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    //MApp_ZUI_API_ResetTimer(HWND_CIMMI_LIST_PANE, 0);
    stUserSoundSettingType *pstSoundSetting = NULL;

    MApp_GetGenSetting(EN_GENSETTING_CLASS_SOUND,  (void *)&pstSoundSetting);
    switch(key)
    {
        case VK_EXIT:
            //behavior: exit key => goto prev page: MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_CLOSE_CURRENT_OSD);
            if (_pInfo != NULL && _pInfo->enType == EN_CIMMI_TYPE_ENQ)
            {
                MMI_BackENQ();
            }
            else if (_pInfo != NULL && (_pInfo->enType == EN_CIMMI_TYPE_MENU || _pInfo->enType == EN_CIMMI_TYPE_LIST) )
            {
                MMI_SelectItem(-1);
            }

            MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_GOTO_CI_CLEAN_UP);
            return TRUE;

        case VK_MENU:
         msAPI_CI_MMIClose();
         MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_GOTO_CI_CLEAN_UP);
            return TRUE;


        case VK_POWER:
            MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_POWEROFF);
            return TRUE;

        //case VK_SELECT:
            //MApp_ZUI_API_SetTimer(HWND_CIMMI_BOTTOM_HALF_OK_BTN, 0, BUTTONANICLICK_PERIOD);
            //MApp_ZUI_API_InvalidateWindow(HWND_CIMMI_BOTTOM_HALF_OK_BTN);
            //break;

        case VK_UP:
              return MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_NAV_KEY_UP);

        case VK_DOWN:
              return MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_NAV_KEY_DOWN);

        case VK_VOLUME_PLUS:
            if (pstSoundSetting->Volume < MAX_NUM_OF_VOL_LEVEL )
            {
                pstSoundSetting->Volume++;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, pstSoundSetting->Volume, 0);
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            return TRUE;

        case VK_VOLUME_MINUS:
            if ( pstSoundSetting->Volume > 0 )
            {
                pstSoundSetting->Volume--;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, pstSoundSetting->Volume, 0);
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            return TRUE;
		
		case VK_KEYSTONE_PLUS:      //xzm @ 20171227
				stGenSetting.g_SysSetting.KeyStoneValue++;
		      if(stGenSetting.g_SysSetting.KeyStoneValue >= 38)
			  	stGenSetting.g_SysSetting.KeyStoneValue=39;

			  keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			break;
			
		case VK_KEYSTONE_MINUS:
			 stGenSetting.g_SysSetting.KeyStoneValue--;
			  if(stGenSetting.g_SysSetting.KeyStoneValue <=-38)
			  	stGenSetting.g_SysSetting.KeyStoneValue=-39;

			  keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			break;

		
        default:
        break;

    }

    return FALSE;
}

void MApp_ZUI_ACT_TerminateCIMMI(void)
{
    ZUI_MSG(printf("[]term:cimmi\n");)

    if (_pInfo != 0)
    {
        _ZUI_FREE(_pInfo);
    }

    enCIEvtState = _enTargetCIMMIState;
}

extern U16 _MApp_ZUI_ACT_PasswordConvertToSystemFormat(U16 password);

BOOLEAN MApp_ZUI_ACT_ExecuteCIMMIAction(U16 act)
{
    switch(act)
    {

        case EN_EXE_GOTO_CI_CLEAN_UP:
            //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetCIMMIState = STATE_CIMMI_CLEAN_UP;
            return TRUE;

        case EN_EXE_CLOSE_CURRENT_OSD:
            //note: normally, this path will not be called..
            //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);

            if ((enCIEvtState == STATE_CIMMI_WAIT)&&(msAPI_CI_MMICheckEvent() == CI_EVENT_NONE))
            {
                msAPI_CI_MMIClose();//Send Close_CIMMI to CAM
            }
            _enTargetCIMMIState = STATE_CIMMI_CLEAN_UP;
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            if ((enCIEvtState == STATE_CIMMI_WAIT)&&(msAPI_CI_MMICheckEvent() == CI_EVENT_NONE))
            {
                msAPI_CI_MMIClose();//Send Close_CIMMI to CAM
            }
            _enTargetCIMMIState = STATE_CIMMI_CLEAN_UP;
            return TRUE;

        case EN_EXE_GOTO_CI_POLLING:
            //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_NONE, E_ZUI_STATE_RUNNING);
            //_enTargetCIMMIState = STATE_CIMMI_WAIT;
            enCIEvtState = STATE_CIMMI_WAIT;
            return TRUE;

        case EN_EXE_CIMMI_MENU_ITEM_SELECT:
            if (_pInfo != 0 && _pInfo->enType == EN_CIMMI_TYPE_MENU)
            {
                MMI_SelectItem(_u8MenuCIMMICurIndex);
            }
            return TRUE;

        case EN_EXE_CIMMI_INPUT_PIN_SELECT:
            if (_pInfo != 0)
            {
                MMI_InputENQ(_pInfo->aEnqInputBuffer);
            }
            return TRUE;

        case EN_EXE_REPAINT_CIMMI_PAGE:
            if (_pInfo)
            {
                U8 i, bFirst = TRUE;
                MMI_ParseInformaton(_pInfo);

                if(EN_CIMMI_TYPE_NONE==_pInfo->enType)// If EN_CIMMI_TYPE_NONE, drawing nothing
                    break;

                MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_CIMMI_BG_PANE, SW_SHOW);

                switch(_pInfo->enType)
                {
                    default:
                    case EN_CIMMI_TYPE_NONE:
                        break;

                    case EN_CIMMI_TYPE_MENU:
                        MApp_ZUI_API_ShowWindow(HWND_CIMMI_SELECTION_PAGE, SW_SHOW);

                        _u8MenuCIMMIScrollIndex = 0;
                        _u8MenuCIMMICurIndex = 0;

                        for (i = 0; i < UI_CIMMI_ITEM_NUM; i++)
                        {
                            if (_pInfo->content.menu_data.pString[i] == 0)
                            {
                                MApp_ZUI_API_ShowWindow(_CIMMIItemHwndList[i], SW_HIDE);
                            }
                            else if (bFirst)
                            {
                                bFirst = FALSE;
                                MApp_ZUI_API_SetFocus(_CIMMIItemHwndList[i]);
                            }
                        }
                        break;

                    case EN_CIMMI_TYPE_ENQ:
                        {
                        u8PinNum = _pInfo->content.enq_data.u8AnsLen;

                        if( u8PinNum > UI_CIMMI_PIN_NUM )
                        {
                            printf("[WARNING!] Some pin was truncated because host only support %d pin number!\n", UI_CIMMI_PIN_NUM);
                            u8PinNum = 20;
                        }

                        U8 u8MinPin = ( 10 - ( u8PinNum / 2 ));
                        U8 u8MaxPin = ( 10 + ( u8PinNum / 2 ));

                        for (i = u8MinPin; i < u8MaxPin; ++i)
                        {
                            MApp_ZUI_API_ShowWindow(_CIMMIPinHwndList[i], SW_SHOW);
                        }

                        if((u8PinNum%2==0)&&(u8MaxPin!=20))//if the num of square is even
                        {
                          MApp_ZUI_API_ShowWindow(_CIMMIPinHwndList[u8MaxPin], SW_HIDE);
                        }
                        MApp_ZUI_API_SetFocus(_CIMMIPinHwndList[u8MinPin]);
                        break;
                    }
                    case EN_CIMMI_TYPE_LIST:
                        MApp_ZUI_API_ShowWindow(HWND_CIMMI_SELECTION_PAGE, SW_SHOW);

                        _u8MenuCIMMIScrollIndex = 0;
                        _u8MenuCIMMICurIndex = 0;

                        for (i = 0; i < UI_CIMMI_ITEM_NUM; i++)
                        {
                            if (_pInfo->content.list_data.pString[i] == 0)
                            {
                                MApp_ZUI_API_ShowWindow(_CIMMIItemHwndList[i], SW_HIDE);
                            }

                            else if (bFirst) //Need focus
                            {
                                bFirst = FALSE;
                                MApp_ZUI_API_SetFocus(_CIMMIItemHwndList[i]);
                            }
                        }
                        //MApp_ZUI_API_SetFocus(HWND_INVALID); //no focus if list...
                        break;
                }
            }
            return TRUE;

        case EN_EXE_SHOW_CI_DETECTED_MSGBOX:
        case EN_EXE_SHOW_CI_REMOVED_MSGBOX:
        case EN_EXE_SHOW_CI_LOAD_INFO_MSGBOX:
        case EN_EXE_SHOW_CI_NO_MODULE_MSGBOX:
        case EN_EXE_SHOW_CI_TRY_AGAIN_MSGBOX:
            _eMsgBoxMode = (CIMMI_MSGBOX_MODE)(act - EN_EXE_SHOW_CI_DETECTED_MSGBOX + EN_MSGBOX_MODE_CI_DETECTED);
            //printf("[]mode=%bu\n", _eMsgBoxMode);
        #if ENABLE_CI_PLUS
            if(bOPRefreshMsgbox==TRUE)
            {
               MApp_CI_SendCiOpSearchStart();
               bOPRefreshMsgbox = FALSE;
            }
        #endif
            MApp_ZUI_API_ShowWindow(HWND_CIMMI_DLG_COMMON, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_INVALID);
            enCIEvtState = STATE_CIMMI_MESSAGE_BOX;
            return TRUE;

        case EN_EXE_NAV_KEY_UP :
            if(MApp_ZUI_API_IsWindowVisible(HWND_CIMMI_SELECTION_LIST))
            {
                U8 total_count;

                total_count =  _MApp_ZUI_ACT_CIMMIGetMenuListCnt();
                ZUI_MSG(printf("[]total_count=%u\n", total_count));
                _MApp_ZUI_ACT_CIMMINavUp(total_count);
                //MApp_ZUI_ACT_CIMMIUpdatePageScroll();
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CIMMI_SELECTION_LIST);
                return TRUE;

                /*
                if(total_count>UI_CIMMI_ITEM_NUM)
                {
                    _MApp_ZUI_ACT_CIMMINavUp(total_count);
                    //MApp_ZUI_ACT_CIMMIUpdatePageScroll();
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CIMMI_SELECTION_LIST);
                    return TRUE;
                }
                else
                    return FALSE;
                */
            }

        case EN_EXE_NAV_KEY_DOWN:

            if(MApp_ZUI_API_IsWindowVisible(HWND_CIMMI_SELECTION_LIST))
            {
                U8 total_count;

                total_count =  _MApp_ZUI_ACT_CIMMIGetMenuListCnt();
                //printf("[]total_count=%bu\n", total_count);
                _MApp_ZUI_ACT_CIMMINavDown(total_count);
                //MApp_ZUI_ACT_CIMMIUpdatePageScroll();
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CIMMI_SELECTION_LIST);
                return TRUE;

                /*
                if(total_count>UI_CIMMI_ITEM_NUM)
                {
                    _MApp_ZUI_ACT_CIMMINavDown(total_count);
                    //MApp_ZUI_ACT_CIMMIUpdatePageScroll();
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CIMMI_SELECTION_LIST);
                    return TRUE;
                }
                else
                    return FALSE;
                */
            }
    #if ENABLE_CI_PLUS
        case EN_EXE_REFRESH_DLG_CONFIRM_YES:
             if(MApp_ZUI_API_IsWindowVisible(HWND_OP_REFRESH_MSGBOX_REFRESH_2))
             {
                //MApp_CI_SendCiOpSearchStart();
                bOPRefreshMsgbox = FALSE;
                //stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo = FALSE;
                MApp_ZUI_API_KillTimer(HWND_OP_REFRESH_MSGBOX_PANE, 0);
                MApp_ZUI_API_ShowWindow(HWND_OP_REFRESH_MSGBOX_PANE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_CIMMI_TRANSPARENT_BG,SW_SHOW);
                {
                    U32 u32TimeCurrent;
                    u32TimeCurrent = MApp_GetLocalSystemTime();
                    if(u32TimeCurrent >= m_u32EpgNextStartUpTime_Temp)
                        MApp_CI_SendCiOpSearchStart();
                    else
                    {
                        m_u32EpgNextStartUpTime_Temp_Flag = TRUE;
                    }
                }
            }
             return TRUE;
        case EN_EXE_REFRESH_DLG_CONFIRM_NO:
            if(MApp_ZUI_API_IsWindowVisible(HWND_OP_REFRESH_MSGBOX_REFRESH_2))
            {
                bOPRefreshMsgbox = FALSE;
                stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo = TRUE;
                MApp_DB_GEN_SaveData_RightNow();
                MApp_ZUI_API_KillTimer(HWND_OP_REFRESH_MSGBOX_PANE, 0);
                MApp_ZUI_API_ShowWindow(HWND_OP_REFRESH_MSGBOX_PANE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_CIMMI_TRANSPARENT_BG,SW_SHOW);
            }
            return TRUE;
    #endif
    }
    return FALSE;
}


LPTSTR MApp_ZUI_ACT_GetCIMMIDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_CIMMI_PAGE_TITLE:
//            printf("[]_pInfo=%lx\n", (U32)_pInfo);
//            printf("[]content[0]=%bu\n", _pInfo->aTitleContent[0]);
            if (_pInfo && _pInfo->aTitleContent[0] != 0)
            {
                Mapp_MMI_ParseInformaton(CHAR_BUFFER, _pInfo->aTitleContent, 255);
                return CHAR_BUFFER;
               // return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, _pInfo->aTitleContent, 255);
            }
            break;

        case HWND_CIMMI_PAGE_SUBTITLE:
            if (_pInfo && _pInfo->enType == EN_CIMMI_TYPE_MENU &&
                _pInfo->content.menu_data.au8Subtitle[0] != 0)
            {
                Mapp_MMI_ParseInformaton(CHAR_BUFFER, _pInfo->content.menu_data.au8Subtitle, 255);
                return CHAR_BUFFER;
                //return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, _pInfo->content.menu_data.au8Subtitle, 255);
            }
            if (_pInfo && _pInfo->enType == EN_CIMMI_TYPE_LIST &&
                _pInfo->content.list_data.au8Subtitle[0] != 0)
            {
                Mapp_MMI_ParseInformaton(CHAR_BUFFER, _pInfo->content.list_data.au8Subtitle, 255);
                return CHAR_BUFFER;
                //return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, _pInfo->content.list_data.au8Subtitle, 255);
            }
            break;

        case HWND_CIMMI_PAGE_BOTTOM:
            if (_pInfo && _pInfo->enType == EN_CIMMI_TYPE_MENU &&
                _pInfo->content.menu_data.au8Bottom[0] != 0)
            {
                Mapp_MMI_ParseInformaton(CHAR_BUFFER, _pInfo->content.menu_data.au8Bottom, 255);
                return CHAR_BUFFER;
               // return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, _pInfo->content.menu_data.au8Bottom, 255);
            }
            if (_pInfo && _pInfo->enType == EN_CIMMI_TYPE_LIST &&
                _pInfo->content.list_data.au8Bottom[0] != 0)
            {
                Mapp_MMI_ParseInformaton(CHAR_BUFFER, _pInfo->content.list_data.au8Bottom, 255);
                return CHAR_BUFFER;
                //return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, _pInfo->content.list_data.au8Bottom, 255);
            }
            break;

        case HWND_CIMMI_SELECTION_ITEM1:
        case HWND_CIMMI_SELECTION_ITEM2:
        case HWND_CIMMI_SELECTION_ITEM3:
        case HWND_CIMMI_SELECTION_ITEM4:
        case HWND_CIMMI_SELECTION_ITEM5:
        case HWND_CIMMI_SELECTION_ITEM6:
        case HWND_CIMMI_SELECTION_ITEM7:
            {
                U8 idx = _MApp_ZUI_ACT_CIMMIWindowMapToIndex(hwnd);

                idx =_u8MenuCIMMIScrollIndex+idx;
                MApp_ZUI_API_SetTimer(HWND_CIMMI_DLG_COMMON_BG, 0, CIMMI_TIME_OUT_MS);

                if (_pInfo && _pInfo->enType == EN_CIMMI_TYPE_MENU &&
                    _pInfo->content.menu_data.pString[idx]!= 0)
                {
                    Mapp_MMI_ParseInformaton(CHAR_BUFFER, _pInfo->content.menu_data.pString[idx], 255);
                    return CHAR_BUFFER;
                    //return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, _pInfo->content.menu_data.pString[idx], 255);
                }
                if (_pInfo && _pInfo->enType == EN_CIMMI_TYPE_LIST &&
                    _pInfo->content.list_data.pString[idx]!= 0)
                {
                    Mapp_MMI_ParseInformaton(CHAR_BUFFER, _pInfo->content.list_data.pString[idx], 255);
                    return CHAR_BUFFER;
                    //return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, _pInfo->content.list_data.pString[idx], 255);
                }
            }
            break;

        /*
        case HWND_CIMMI_TEXTBOX:
            if (_pInfo && _pInfo->enType == EN_CIMMI_TYPE_LIST )
            {
                MApp_ZUI_API_ConvertStringU8ToU16(CHAR_BUFFER, _pInfo->content.list_data.aStringContent);
                return CHAR_BUFFER;
            }
            break;
        */

        case HWND_CIMMI_DLG_COMMON_TEXT1:
            switch(_eMsgBoxMode)
            {
                case  EN_MSGBOX_MODE_INVALID:
                default:
                    break;

                case EN_MSGBOX_MODE_CI_DETECTED:                     ///< show CI detected
                    u16TempID = en_str_CI_Module_Inserted;
                    break;

                case EN_MSGBOX_MODE_CI_REMOVED:                     ///< show CI removed
                    u16TempID = en_str_CI_Module_Removed;
                    break;

                case EN_MSGBOX_MODE_CI_LOAD_INFO:                     ///< show CI load info
                    u16TempID = en_str_Loading_CI_MMI3dot;
                    break;

                case EN_MSGBOX_MODE_CI_NO_MODULE:                     ///< show CI no module
                    u16TempID = en_str_Please_insert_CI_Module;
                    break;

                case EN_MSGBOX_MODE_CI_TRY_AGAIN:                     ///< show CI try again
                    u16TempID = en_str_Please_try_again_later3dot;
                    break;


            }
            //printf("[]txt=%u\n", u16TempID);
            break;
    }
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return NULL; //for empty string
}


/////////////////////////////////////////////////////////
// Customize Window Procedures

extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);
extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);
extern void _MApp_ZUI_API_DefaultOnPaint(HWND hWnd, PAINT_PARAM * param, BOOLEAN bDrawText);

typedef struct
{
    HWND hwnd;
    HWND hwndNext;
    //U16 * pVar;
    //U8 u8ShiftBits;
}PASSWORD_INPUT_DATA_STRUCT;

S32 MApp_ZUI_ACT_CIMMIPasswordInputWinProc(HWND hwnd, PMSG msg)//dynamic input squares
{
    static BOOLEAN _bPasswordBlinkBlack = FALSE;

    static  PASSWORD_INPUT_DATA_STRUCT _ZUI_TBLSEG _PasswordData[] =
    {
        {
            HWND_CIMMI_INPUT_PIN1,
            HWND_CIMMI_INPUT_PIN2,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN2,
            HWND_CIMMI_INPUT_PIN3,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN3,
            HWND_CIMMI_INPUT_PIN4,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN4,
            HWND_CIMMI_INPUT_PIN5,
            //&PasswordInput1,


        },
        {
            HWND_CIMMI_INPUT_PIN5,
            HWND_CIMMI_INPUT_PIN6,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN6,
            HWND_CIMMI_INPUT_PIN7,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN7,
            HWND_CIMMI_INPUT_PIN8,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN8,
            HWND_CIMMI_INPUT_PIN9,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN9,
            HWND_CIMMI_INPUT_PIN10,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN10,
            HWND_CIMMI_INPUT_PIN11,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN11,
            HWND_CIMMI_INPUT_PIN12,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN12,
            HWND_CIMMI_INPUT_PIN13,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN13,
            HWND_CIMMI_INPUT_PIN14,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN14,
            HWND_CIMMI_INPUT_PIN15,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN15,
            HWND_CIMMI_INPUT_PIN16,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN16,
            HWND_CIMMI_INPUT_PIN17,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN17,
            HWND_CIMMI_INPUT_PIN18,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN18,
            HWND_CIMMI_INPUT_PIN19,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN19,
            HWND_CIMMI_INPUT_PIN20,
            //&PasswordInput1,

        },
        {
            HWND_CIMMI_INPUT_PIN20,
            HWND_CIMMI_INPUT_PIN1,
            //&PasswordInput1,

        },

     };

    U8 i;
        for (i = 0; i < COUNTOF(_PasswordData); i++)
    {
        if (hwnd == _PasswordData[i].hwnd)
            break;
    }
    if (i == COUNTOF(_PasswordData)) //if not in the data list, we do nothing...
        return DEFAULTWINPROC(hwnd, msg);

    switch(msg->message)
    {
        case MSG_NOTIFY_SETFOCUS:
            {
                //enable blinking
                MApp_ZUI_API_SetTimer(hwnd, 0, 500);
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            return 0;

        case MSG_TIMER:
            {
                //blinking
                _bPasswordBlinkBlack = !_bPasswordBlinkBlack;
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            break;

        case MSG_NOTIFY_KILLFOCUS:
        case MSG_NOTIFY_HIDE:
            {
                //disable blinking
                MApp_ZUI_API_KillTimer(hwnd, 0);
            }
            return 0;

        case MSG_KEYDOWN:
            {
                if (VK_NUM_0 <= msg->wParam && msg->wParam <= VK_NUM_9)
                {
                    //*(_PasswordData[i].pVar) &= ~(PASSWORD_INPUT_MASK<<_PasswordData[i].u8ShiftBits);
                    //*(_PasswordData[i].pVar) |= ((msg->wParam-VK_NUM_0)<<_PasswordData[i].u8ShiftBits);
                    if (_pInfo)
                    {
                        _pInfo->aEnqInputBuffer[i - (9 - (u8PinNum / 2) + 1)] = '0'+msg->wParam-VK_NUM_0;
                        _pInfo->aEnqInputBuffer[i + 1 - (9 - (u8PinNum / 2) + 1)] = 0;
                    }

                    {
                        if(u8PinNum%2==0)//if the num of square is even
                        {
                          if (i == 9+(u8PinNum/2)) //last one
                          {
                            MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_CIMMI_INPUT_PIN_SELECT);
                            MsOS_DelayTask(500);
                          }
                           else
                          {
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                          }
                        }
                        else //if the num of square is odd
                        {
                          if (i == 10+(u8PinNum/2)) //last one
                          {
                            MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_CIMMI_INPUT_PIN_SELECT);
                            MsOS_DelayTask(500);
                          }
                           else
                          {
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                          }

                        }

                   }
                    return 0; //don't process default behavior....
                }
            }
            break;

        case MSG_PAINT:
            {
                static  DRAW_RECT _ZUI_TBLSEG _DrawPasswordBlinkBgFocus =
                {
                    0x707070,
                    0x707070,
                    OSD_GRADIENT_DISABLE, //OSD_GRADIENT eRectGradient;
                    0, //OSD_COLOR BroderColor;
                    eRectBorder, //RECT_ATTRIB attrib;
                    0, //U8 sizeBorder;
                    0, //radius
                };
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)msg->wParam;
                if (param->bIsFocus && _bPasswordBlinkBlack)
                {

                    //2007/12/22: for bank issue, we prepare it in XDATA
                    DRAW_RECT * pDraw = (DRAW_RECT*)_ZUI_MALLOC(sizeof(DRAW_RECT));
                    if (pDraw)
                    {
                        param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hwnd);
                        memcpy(pDraw, &_DrawPasswordBlinkBgFocus, sizeof(DRAW_RECT));
                        _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, pDraw, &param->dc, param->rect);
                        _ZUI_FREE(pDraw);
                    }
                    else
                    {
                        __ASSERT(0);
                    }
                    return DEFAULTWINPROC(hwnd, msg);
                }
                else if (param->bIsFocus)
                {
                    return DEFAULTWINPROC(hwnd, msg);
                }
                else
                {
                    //if focus is after this, show it as '*'
                    {
                        U8 j;
                        for (j = 0; j < COUNTOF(_PasswordData); j++)
                        {
                            if (MApp_ZUI_API_GetFocus()== _PasswordData[j].hwnd)
                                break;
                        }
                        if (j == COUNTOF(_PasswordData)) //if not in the password input, we do nothing...
                            return DEFAULTWINPROC(hwnd, msg);
                        if (i >= j) //if current password input is after focus (not yet input)
                            return DEFAULTWINPROC(hwnd, msg);
                    }
                    {
                        DRAW_TEXT_OUT_DYNAMIC * dyna;
                        U16 u16TextIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, DS_NORMAL, CP_TEXT_OUT);
                        if (u16TextIndex != 0xFFFF)
                        {
                            _MApp_ZUI_API_DefaultOnPaint(hwnd, param, FALSE); //draw others first

                            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hwnd);
                            dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
                            if (dyna)
                            {
                                LPTSTR str = CHAR_BUFFER;
                                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, dyna);
                                str[0] = '*';
                                str[1] = 0;
                                dyna->pString = str;

                                if (_pInfo != NULL &&
                                    _pInfo->enType == EN_CIMMI_TYPE_ENQ &&
                                    _pInfo->content.enq_data.bBlindAns == FALSE)
                                {
                                    //str[0] = '0' + ((*(_PasswordData[i].pVar)>>_PasswordData[i].u8ShiftBits)&PASSWORD_INPUT_MASK);
                                    str[0] = _pInfo->aEnqInputBuffer[i - (9 - (u8PinNum / 2) + 1)];
                                }

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
            }
            return 0;

        default:
            break;



    }

    return DEFAULTWINPROC(hwnd, msg);
}
////////////////////////////////////////////////////////////when 5 input squares

S32 MApp_ZUI_ACT_CIMMIPasswordInputWinProc2(HWND hwnd, PMSG msg)
{
    static BOOLEAN _bPasswordBlinkBlack = FALSE;

    static  PASSWORD_INPUT_DATA_STRUCT _ZUI_TBLSEG _PasswordData[] =
    {
        {
            HWND_CIMMI_INPUT2_PIN1,
            HWND_CIMMI_INPUT2_PIN2,
            //&PasswordInput1,
            //16
        },
        {
            HWND_CIMMI_INPUT2_PIN2,
            HWND_CIMMI_INPUT2_PIN3,
            //&PasswordInput1,
            //12
        },
        {
            HWND_CIMMI_INPUT2_PIN3,
            HWND_CIMMI_INPUT2_PIN4,
            //&PasswordInput1,
            //8
        },
        {
            HWND_CIMMI_INPUT2_PIN4,
            HWND_CIMMI_INPUT2_PIN5,
            //&PasswordInput1,
            //4
        },
        {
            HWND_CIMMI_INPUT2_PIN5,
            HWND_CIMMI_INPUT2_PIN1,
            //&PasswordInput1,
            //0
        },

     };

    U8 i;
        for (i = 0; i < COUNTOF(_PasswordData); i++)
    {
        if (hwnd == _PasswordData[i].hwnd)
            break;
    }
    if (i == COUNTOF(_PasswordData)) //if not in the data list, we do nothing...
        return DEFAULTWINPROC(hwnd, msg);

    switch(msg->message)
    {
        case MSG_NOTIFY_SETFOCUS:
            {
                //enable blinking
                MApp_ZUI_API_SetTimer(hwnd, 0, 500);
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            return 0;

        case MSG_TIMER:
            {
                //blinking
                _bPasswordBlinkBlack = !_bPasswordBlinkBlack;
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            break;

        case MSG_NOTIFY_KILLFOCUS:
        case MSG_NOTIFY_HIDE:
            {
                //disable blinking
                MApp_ZUI_API_KillTimer(hwnd, 0);
            }
            return 0;

        case MSG_KEYDOWN:
            {
                if (VK_NUM_0 <= msg->wParam && msg->wParam <= VK_NUM_9)
                {
                    //*(_PasswordData[i].pVar) &= ~(PASSWORD_INPUT_MASK<<_PasswordData[i].u8ShiftBits);
                    //*(_PasswordData[i].pVar) |= ((msg->wParam-VK_NUM_0)<<_PasswordData[i].u8ShiftBits);
                    if (_pInfo)
                    {
                        _pInfo->aEnqInputBuffer[i] = '0'+msg->wParam-VK_NUM_0;
                        _pInfo->aEnqInputBuffer[i+1] = 0;
                    }

                    {
                        if (i == 4) //last one
                        {
                            MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_CIMMI_INPUT_PIN_SELECT);
                            MsOS_DelayTask(500);
                        }
                        else
    {
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }
                   }
                    return 0; //don't process default behavior....
                }
            }
            break;

        case MSG_PAINT:
            {
                static  DRAW_RECT _ZUI_TBLSEG _DrawPasswordBlinkBgFocus =
                {
                    0x707070,
                    0x707070,
                    OSD_GRADIENT_DISABLE, //OSD_GRADIENT eRectGradient;
                    0, //OSD_COLOR BroderColor;
                    eRectBorder, //RECT_ATTRIB attrib;
                    0, //U8 sizeBorder;
                    0, //radius
                };
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)msg->wParam;
                if (param->bIsFocus && _bPasswordBlinkBlack)
                {

                    //2007/12/22: for bank issue, we prepare it in XDATA
                    DRAW_RECT * pDraw = (DRAW_RECT*)_ZUI_MALLOC(sizeof(DRAW_RECT));
                    if (pDraw)
                    {
                        param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hwnd);
                        memcpy(pDraw, &_DrawPasswordBlinkBgFocus, sizeof(DRAW_RECT));
                        _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, pDraw, &param->dc, param->rect);
                        _ZUI_FREE(pDraw);
                    }
                    else
                    {
                        __ASSERT(0);
                    }
                    return DEFAULTWINPROC(hwnd, msg);
                }
                else if (param->bIsFocus)
                {
                    return DEFAULTWINPROC(hwnd, msg);
                }
                else
                {
                    //if focus is after this, show it as '*'
                    {
                        U8 j;
                        for (j = 0; j < COUNTOF(_PasswordData); j++)
                        {
                            if (MApp_ZUI_API_GetFocus()== _PasswordData[j].hwnd)
                                break;
                        }
                        if (j == COUNTOF(_PasswordData)) //if not in the password input, we do nothing...
                            return DEFAULTWINPROC(hwnd, msg);
                        if (i >= j) //if current password input is after focus (not yet input)
                            return DEFAULTWINPROC(hwnd, msg);
                    }
                    {
                        DRAW_TEXT_OUT_DYNAMIC * dyna;
                        U16 u16TextIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, DS_NORMAL, CP_TEXT_OUT);
                        if (u16TextIndex != 0xFFFF)
                        {
                            _MApp_ZUI_API_DefaultOnPaint(hwnd, param, FALSE); //draw others first

                            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hwnd);
                            dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
                            if (dyna)
                            {
                                LPTSTR str = CHAR_BUFFER;
                                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, dyna);
                                str[0] = '*';
                                str[1] = 0;
                                dyna->pString = str;

                                if (_pInfo != NULL &&
                                    _pInfo->enType == EN_CIMMI_TYPE_ENQ &&
                                    _pInfo->content.enq_data.bBlindAns == FALSE)
                                {
                                    //str[0] = '0' + ((*(_PasswordData[i].pVar)>>_PasswordData[i].u8ShiftBits)&PASSWORD_INPUT_MASK);
                                    str[0] = _pInfo->aEnqInputBuffer[i];
                                }

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
            }
            return 0;

        default:
            break;



    }

    return DEFAULTWINPROC(hwnd, msg);
}

////////////////////////////////////////////////////////////
S32 MApp_ZUI_ACT_CIMMIWinProc(HWND hWnd, PMSG pMsg)
{


    switch(pMsg->message)
    {
        case MSG_CREATE:
            {
                U32 timeout_ms = MApp_ZUI_API_GetWindowData(hWnd);
                if (timeout_ms > 0)
                {
                    //setting AP timeout, auto close
                    MApp_ZUI_API_SetTimer(hWnd, 0, timeout_ms);
                }
            }
            break;

        case MSG_TIMER:
            {
                //if the time is up, kill the timer and then close AP!
                //maybe timeout on common dialog...MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_API_KillTimer(HWND_CIMMI_DLG_COMMON, 0);
                //msAPI_CI_MMIClose();
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
            break;

        default:
            break;

    }

    return DEFAULTWINPROC(hWnd, pMsg);
}
#if (ENABLE_CI_PLUS)
BOOLEAN MApp_ZUI_ACT_OPRefreshQueryUI(void) //show refresh msgbox
{
  bOPRefreshMsgbox = TRUE;
  stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo = TRUE;
  MApp_CI_CIClearOPSearchSuspended();

  if (MApp_ZUI_GetActiveOSD() != E_OSD_CIMMI)
  {
      MApp_ZUI_ACT_StartupOSD(E_OSD_CIMMI);
  }
  MApp_ZUI_API_ShowWindow(HWND_OP_REFRESH_MSGBOX_PANE,SW_SHOW);
  MApp_ZUI_API_ShowWindow(HWND_CIMMI_BG_PANE,SW_HIDE);
  MApp_ZUI_API_ShowWindow(HWND_CIMMI_SELECTION_PAGE,SW_HIDE);
  MApp_ZUI_API_ShowWindow(HWND_CIMMI_INPUT_PIN_PAGE,SW_HIDE);
  MApp_ZUI_API_ShowWindow(HWND_CIMMI_INPUT2_PIN_PAGE,SW_HIDE);
  MApp_ZUI_API_ShowWindow(HWND_CIMMI_DLG_COMMON,SW_HIDE);
  MApp_ZUI_API_SetFocus(HWND_OP_REFRESH_BTN_NO);
  MApp_ZUI_API_SetTimer(HWND_OP_REFRESH_MSGBOX_PANE, 0, 5000);

  return TRUE;
}


S32 MApp_ZUI_ACT_OPMenuMsgBoxWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_TIMER:
            {
                MApp_ZUI_API_KillTimer(HWND_OP_REFRESH_MSGBOX_PANE, 0);
                MApp_ZUI_API_ShowWindow(HWND_OP_REFRESH_MSGBOX_PANE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_CIMMI_TRANSPARENT_BG,SW_SHOW);
                MApp_CI_SendCiOpSearchStart();//do op refresh
                bOPRefreshMsgbox = FALSE;
                //stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo = FALSE;
            }
            break;

        default:
            break;

    }

    return DEFAULTWINPROC(hWnd, pMsg);
}
#endif
S32 MApp_ZUI_ACT_CIMMIMessageBoxWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_NOTIFY_SHOW:
            {
                //printf("[]msg_start\n");
                if ((_eMsgBoxMode==EN_MSGBOX_MODE_CI_DETECTED)||(_eMsgBoxMode==EN_MSGBOX_MODE_CI_REMOVED)||(_eMsgBoxMode==EN_MSGBOX_MODE_CI_NO_MODULE))
                {
                    MApp_ZUI_API_SetTimer(hWnd, 0, 2000);
                }
                else
                {
                    MApp_ZUI_API_SetTimer(hWnd, 0, 1000);
                }
            }
            break;

        case MSG_TIMER:
            {
                //printf("[]msg_go\n");
                MApp_ZUI_API_KillTimer(hWnd, 0);
                //note: don't show it at this time: MApp_ZUI_API_ShowWindow(HWND_CIMMI_DLG_COMMON, SW_HIDE);
                //  we will hide all after execute EN_EXE_REPAINT_CIMMI_PAGE
                if ((_eMsgBoxMode==EN_MSGBOX_MODE_CI_DETECTED)||(_eMsgBoxMode==EN_MSGBOX_MODE_CI_REMOVED)||(_eMsgBoxMode==EN_MSGBOX_MODE_CI_NO_MODULE))
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                else
                {
                #if ENABLE_CI_PLUS
                    if(bOPRefreshMsgbox==TRUE)
                    {
                       MApp_CI_SendCiOpSearchStart();
                       bOPRefreshMsgbox = FALSE;
                    }
                #endif
                    MApp_ZUI_ACT_ExecuteCIMMIAction(EN_EXE_GOTO_CI_POLLING);
                }
            }
            break;

        default:
            break;


    }

    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_ACTCIMMI_C
