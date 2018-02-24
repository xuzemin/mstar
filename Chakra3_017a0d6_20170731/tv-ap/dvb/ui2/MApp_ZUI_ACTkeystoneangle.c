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

#define MAPP_ZUI_ACTKEYSTONEANGLE_C
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
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "msAPI_Global.h"
#include "MApp_ZUI_ACTkeystoneangle.h"
#include "MApp_UiMenuDef.h"
//#include "MApp_Audio.h"
#include "MApp_GlobalSettingSt.h"
//#include "msAPI_audio.h"
#include "MApp_SaveData.h"
#include "drvGPIO.h"

#include "ZUI_bitmap_EnumIndex.h"
#include "MApp_TopStateMachine.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#include "MApp_GlobalFunction.h"
#include "MApp_ZUI_ACTdmp.h"
/////////////////////////////////////////////////////////////////////

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);


void MApp_ZUI_ACT_AppShowKeystoneAngle(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_KEYSTONE_ANGLE;

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
        ZUI_KEYSTONE_ANGLE_XSTART, ZUI_KEYSTONE_ANGLE_YSTART,
        ZUI_KEYSTONE_ANGLE_WIDTH, ZUI_KEYSTONE_ANGLE_HEIGHT);

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
	printf("MApp_ZUI_API_ShowWindow \n");
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_KEYSTONE_ANGLE_BG, SW_HIDE);
	//MApp_ZUI_API_ShowWindow(HWND_KEYSTONE_ANGLE_VALUE, SW_HIDE);
	//MApp_ZUI_API_ShowWindow(HWND_KEYSTONE_ANGLE_BAR, SW_HIDE);
	//MApp_ZUI_API_ShowWindow(HWND_KEYSTONE_ANGLE_ICON, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_KEYSTONE_ANGLE_BG, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_KEYSTONE_ANGLE_VALUE, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_KEYSTONE_ANGLE_BAR, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_KEYSTONE_ANGLE_ICON, SW_SHOW);
	//gU8Timer5ms = 1;
}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleKeystoneAngleKey(VIRTUAL_KEY_CODE key)
{
    //note: don't do anything here! keys will be handled in state machines
    //      moved to MApp_TV_ProcessAudioVolumeKey()
    UNUSED(key);
    ZUI_DBG_FAIL(printf("[ZUI]IDLEKEY\n"));
    //ABORT();
    return FALSE;
}

void MApp_ZUI_ACT_TerminateKeystoneAngle(void)
{
    ZUI_MSG(printf("[]term:volume\n"));
    //enAudioVolumeState = _enTargetAudioVolumeState;
}



BOOLEAN MApp_ZUI_ACT_ExecuteKeystoneAngleAction(U16 act)
{
    switch(act)
    {

        case EN_EXE_CLOSE_CURRENT_OSD:
        case EN_EXE_POWEROFF: //smc.chy 2010/10/14
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return TRUE;
			
        case EN_EXE_RESET_AUTO_CLOSE_TIMER:
            //reset timer if any key
            MApp_ZUI_API_ResetTimer(HWND_KEYSTONE_ANGLE_BG, 0);
            return FALSE;
        case EN_EXE_DEC_KEYSTONEANGLE:
        case EN_EXE_INC_KEYSTONEANGLE:
            if(act == EN_EXE_INC_KEYSTONEANGLE)
            {
                if ( stGenSetting.g_SysSetting.KeyStoneValue< 38 )
                {
                    stGenSetting.g_SysSetting.KeyStoneValue++;
					keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_KEYSTONE_ANGLE_BG);
                }
            }
            else
            {
                if ( stGenSetting.g_SysSetting.KeyStoneValue > -38)
                {
					stGenSetting.g_SysSetting.KeyStoneValue--;
					keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_KEYSTONE_ANGLE_BG);
                }
            }
            return TRUE;
    }
    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetKeystoneAngleDynamicText(HWND hwnd)
{
	printf("MApp_ZUI_ACT_GetKeystoneAngleDynamicText  %u\n",hwnd);
	//U8 u8Percent; 
    switch(hwnd)
    {
        case HWND_KEYSTONE_ANGLE_VALUE:
				return MApp_ZUI_API_GetS16SignString(stGenSetting.g_SysSetting.KeyStoneValue);
		default:
			break;
    }

    return 0; //for empty string....
}



S16 MApp_ZUI_ACT_GetKeystoneAngleDynamicValue(HWND hwnd)
{
	printf("MApp_ZUI_ACT_GetKeystoneAngleDynamicValue  %u\n",hwnd);
    switch(hwnd)
    {
        case HWND_KEYSTONE_ANGLE_BAR:
            return stGenSetting.g_SysSetting.KeyStoneValue+39;
		default:
			break;
    }

    return 0; //for empty  data
}

U16 MApp_ZUI_ACT_GetKeystoneAngleDynamicBitmap(HWND hwnd)
{
	printf("MApp_ZUI_ACT_GetKeystoneAngleDynamicBitmap  %u\n",hwnd);
    U16 u16BtimapIdx=0xFFFF;
    switch(hwnd)
    {
	    case HWND_KEYSTONE_ANGLE_ICON:
		 {
			 if(stGenSetting.g_SysSetting.KeyStoneValue >= 0)
		 	{
				u16BtimapIdx = E_BMP_UP_KEYSTONE;
		 	}
			 else
		 	{
				u16BtimapIdx = E_BMP_DOWN_KEYSTONE;
		 	}
		 }
		break;
		  default:
            break;
    }
    return u16BtimapIdx;
}
/*
/////////////////////////////////////////////////////////
// Customize Window Procedures
S32 MApp_ZUI_ACT_BatPercentWinProc(HWND hwnd, PMSG msg)
{
    //printf("\r\nMSG BOX = %d", msg->message);
    switch(msg->message)
    {
        case MSG_CREATE:
            {
                //checking timer...
                MApp_ZUI_API_SetTimer(hwnd, 0, 1000); //redraw message box
            }
            break;

        case MSG_TIMER:
            {
                //printf("\r\nMSG_TIMER = %d", _eMsgBoxMode);
                //repaint text message if msg mode is COUNT DOWN!

                {
                    //MApp_ZUI_API_InvalidateAllSuccessors(hwnd);

                    //don't auto close...
                   // MApp_ZUI_API_ResetTimer(HWND_MSGBOX_COMMON_BG, 0);
            }


    }
            break;
        default:
            break;

    }

    return DEFAULTWINPROC(hwnd, msg);
}
*/
#undef MAPP_ZUI_ACTKEYSTONEANGLE_C
