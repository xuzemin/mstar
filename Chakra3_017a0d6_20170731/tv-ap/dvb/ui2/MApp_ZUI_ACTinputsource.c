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
// (¨MStar Confidential Information〃) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTINPUTSOURCE_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include "MApp_GlobalSettingSt.h"
#include "MApp_InputSource.h"

#include "MApp_InputSource_Main.h"

#include "msAPI_CEC.h"
#include "msAPI_ATVSystem.h"

#include "MApp_TopStateMachine.h"

#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTinputsource.h"
#include "MApp_OSDPage_Main.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_Func_Inputsource.h"
#include "MApp_ZUI_EventNotify.h"
#if (ENABLE_UART_MSG_TO_USB)
#include "MApp_GlobalSettingSt.h"
#endif
#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
//#include "MApp_GlobalFunction.h"
#include "MApp_TTS_Cus.h"
#include "MApp_TTS_Cus_Say.h"
#endif
#if 0//def ENABLE_KTV
#include "MApp_KTV_Main.h"
#include "MApp_KTV.h"
#endif

#if ENABLE_PANEL_BIN
#include "Panel.h"
#include "MApp_DataBase_Gen.h"
#include "MApp_DataBase_Factory.h"
#include "SysInit.h"
#endif

#include "MApp_GlobalVar.h"

#define DEBUG_ACT_INPUT_SRC(x)  x //gchen @ 20171218 //open debug

/////////////////////////////////////////////////////////////////////
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);

extern EN_INPUTSOURCE_STATE enInputSourceState;

static EN_INPUTSOURCE_STATE _enTargetInputSourceState;

static U16 _u16LaunchKeys;
#if ENABLE_PANEL_BIN
BOOLEAN bSwitchPanelFlag = 0;
#endif
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
extern BOOLEAN MApp_IsSrcHasSignal(SCALER_WIN eWindow);

typedef struct _SOURCE_SRC2HWND_STRUCT
{
    E_UI_INPUT_SOURCE source;
    HWND hwnd;
} SOURCE_SRC2HWND_STRUCT;

static SOURCE_SRC2HWND_STRUCT _ZUI_TBLSEG _source_items[] =
{
#if ENABLE_S2
    {
        UI_INPUT_SOURCE_S2,
        HWND_SOURCE_INPUT_ITEM_S2
    },
#endif
/* gchen @ 20171218
#if (ENABLE_ATSC)
    {
        UI_INPUT_SOURCE_ATSC,            // ATSC project, only 1 TV source, this TV include DTV and ATV together.
        HWND_SOURCE_INPUT_ITEM_ATSC
    },
#else
    {
        UI_INPUT_SOURCE_ATV,             // VIDEO - TV Tuner
#if ((UI_SKIN_SEL == UI_SKIN_1366X768X565) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X4444) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X8888) \
        || (UI_SKIN_SEL == UI_SKIN_1920X1080X565) \
        || (UI_SKIN_SEL == UI_SKIN_960X540X565)\
        )
        HWND_SOURCE_INPUT_ITEM_ATV //gchen @ 20171218 //source item
#else
        HWND_SOURCE_INPUT_ITEM_TV
#endif
    },
#endif // End ENABLE_ATSC
*/
#if ENABLE_DVBT
    {
        UI_INPUT_SOURCE_DVBT,            // VIDEO - DTV Tuner
#if ((UI_SKIN_SEL == UI_SKIN_1366X768X565) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X4444) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X8888) \
        || (UI_SKIN_SEL == UI_SKIN_1920X1080X565) \
        || (UI_SKIN_SEL == UI_SKIN_960X540X565)\
        )
        HWND_SOURCE_INPUT_ITEM_DVBT
#else
        HWND_SOURCE_INPUT_ITEM_DTV
#endif
    },
#endif

#if ENABLE_DVBC
    {
        UI_INPUT_SOURCE_DVBC,            // VIDEO - DTV Tuner
#if ((UI_SKIN_SEL == UI_SKIN_1366X768X565) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X4444) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X8888) \
        || (UI_SKIN_SEL == UI_SKIN_1920X1080X565) \
        || (UI_SKIN_SEL == UI_SKIN_960X540X565)\
        )
        HWND_SOURCE_INPUT_ITEM_DVBC
#else
        HWND_SOURCE_INPUT_ITEM_DTV
#endif
    },
#endif

#if ENABLE_ISDBT
    {
        UI_INPUT_SOURCE_ISDBT,            // VIDEO - DTV Tuner
#if ((UI_SKIN_SEL == UI_SKIN_1366X768X565) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X4444) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X8888) \
        || (UI_SKIN_SEL == UI_SKIN_1920X1080X565) \
        || (UI_SKIN_SEL == UI_SKIN_960X540X565)\
        )
        HWND_SOURCE_INPUT_ITEM_ISDB
#else
        HWND_SOURCE_INPUT_ITEM_DTV
#endif
    },
#endif

#if ENABLE_DTMB
    {
        UI_INPUT_SOURCE_DTMB,            // VIDEO - DTV Tuner
#if ((UI_SKIN_SEL == UI_SKIN_1366X768X565) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X4444) \
        || (UI_SKIN_SEL == UI_SKIN_1366X768X8888) \
        || (UI_SKIN_SEL == UI_SKIN_1920X1080X565) \
        || (UI_SKIN_SEL == UI_SKIN_960X540X565)\
        )
        HWND_SOURCE_INPUT_ITEM_DTMB
#else
        HWND_SOURCE_INPUT_ITEM_DTV
#endif
    },
#endif

//#if DVB_T_C_DIFF_DB

#if (INPUT_SCART_VIDEO_COUNT >= 1)
    {
        UI_INPUT_SOURCE_SCART,
        HWND_SOURCE_INPUT_ITEM_SCART1
    },

#if (INPUT_SCART_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_SCART2,
        HWND_SOURCE_INPUT_ITEM_SCART2
    },
#endif
#endif

#if (INPUT_YPBPR_VIDEO_COUNT>=1)
    {
        UI_INPUT_SOURCE_COMPONENT,
        HWND_SOURCE_INPUT_ITEM_COMPONENT1
    },
#endif

#if (INPUT_YPBPR_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_COMPONENT2,
        HWND_SOURCE_INPUT_ITEM_COMPONENT2
    },
#endif
#if 0
    {
        UI_INPUT_SOURCE_RGB,            // PC - VGA
        HWND_SOURCE_INPUT_ITEM_PC
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT == 1)     //xzm @20171222
    {
        UI_INPUT_SOURCE_HDMI,           // HDMI
        HWND_SOURCE_INPUT_ITEM_HDMI1
    },
#endif

#if (INPUT_HDMI_VIDEO_COUNT == 2) 		//xzm @20171222
    {
        UI_INPUT_SOURCE_HDMI2,
        HWND_SOURCE_INPUT_ITEM_HDMI2
    },
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 3)
    {
        UI_INPUT_SOURCE_HDMI3,
        HWND_SOURCE_INPUT_ITEM_HDMI3
    },
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 4)
    {
        UI_INPUT_SOURCE_HDMI4,
        HWND_SOURCE_INPUT_ITEM_HDMI4
    },
#endif

#if (INPUT_AV_VIDEO_COUNT >= 1)
    {
        UI_INPUT_SOURCE_AV,             // VIDEO - CVBS
        HWND_SOURCE_INPUT_ITEM_AV1
    },
#endif

#if (INPUT_AV_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_AV2,             // VIDEO - CVBS
        HWND_SOURCE_INPUT_ITEM_AV2
    },
#endif

#if (INPUT_AV_VIDEO_COUNT >= 3)
    {
        UI_INPUT_SOURCE_AV3,             // VIDEO - CVBS
        HWND_SOURCE_INPUT_ITEM_AV3
    },
#endif

#if (INPUT_SV_VIDEO_COUNT >= 1)
    {
        UI_INPUT_SOURCE_SVIDEO,
        HWND_SOURCE_INPUT_ITEM_SVIDEO1
    },
#endif

#if (INPUT_SV_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_SVIDEO2,
        HWND_SOURCE_INPUT_ITEM_SVIDEO2
    },
#endif

#if (ENABLE_FM_RADIO)
    {
        UI_INPUT_SOURCE_FMRADIO,
        HWND_SOURCE_INPUT_ITEM_RADIO
    },
#endif
#if GAME_ENABLE
    {
        UI_INPUT_SOURCE_GAME,
        HWND_SOURCE_INPUT_ITEM_GAME
    },
#endif

#if ENABLE_USB_ITEM_IN_SOURCE_MENU
	{
		UI_INPUT_SOURCE_DMP,
		HWND_SOURCE_INPUT_ITEM_DMP
	},

#endif

};

static E_UI_INPUT_SOURCE _MApp_ZUI_ACT_InputSourceWindowMapToId(HWND hwnd)
{
    U8 i;

    DEBUG_ACT_INPUT_SRC(printf("_MApp_ZUI_ACT_InputSourceWindowMapToId(hwnd=%u)\n", hwnd););

    for (i = 0; i < COUNTOF(_source_items); i++)
    {
        if (hwnd == _source_items[i].hwnd ||
            MApp_ZUI_API_IsSuccessor(_source_items[i].hwnd, hwnd))
        {
        #if( ENABLE_DVBC && (!ENABLE_DVBC_USE_INDEPENDENT_UI_INPUT_SOURCE) )
            if (_source_items[i].source == UI_INPUT_SOURCE_DVBC)
            {
                if(MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_CHECK_DVBC, NULL, NULL))
                {
                    DEBUG_ACT_INPUT_SRC( printf("Rtn CADTV\n"); );
                    return UI_INPUT_SOURCE_DVBC;
                }
            }
        #endif

            DEBUG_ACT_INPUT_SRC( printf("Rtn normal src=%u\n", _source_items[i].source); );
            return _source_items[i].source;
        }
    }

    return _source_items[0].source;
}

static HWND _MApp_ZUI_ACT_InputSourceIdMapToWindow(E_UI_INPUT_SOURCE id)
{
    U8 i;

    for (i = 0; i < COUNTOF(_source_items); i++)
    {
    //#if (ENABLE_S2 && !DVB_T_C_DIFF_DB)
    #if 0//( ENABLE_DVBC && (!ENABLE_DVBC_USE_INDEPENDENT_UI_INPUT_SOURCE) )
        if (id == UI_INPUT_SOURCE_CADTV)
        {
            id = UI_INPUT_SOURCE_DTV;
        }
    #endif
        if (id == _source_items[i].source)
        {
            return _source_items[i].hwnd;
        }
    }

    return _source_items[0].hwnd;
}

#if ENABLE_ATSC_TTS
U16 _ZUI_ACT_GetInputSourceStringID(HWND hwnd)
{
    E_UI_INPUT_SOURCE e_UI_INPUT_SOURCE = UI_INPUT_SOURCE_NONE;

    e_UI_INPUT_SOURCE = _MApp_ZUI_ACT_InputSourceWindowMapToId(hwnd);
    //printf("_ZUI_ACT_GetInputSourceStringID(hwnd=%u) => e_UI_INPUT_SOURCE:%u\n", hwnd, e_UI_INPUT_SOURCE);

    switch(e_UI_INPUT_SOURCE)
    {
/********************* < PC > *********************/
        case UI_INPUT_SOURCE_RGB:
            return en_str_PC;
/********************* < TV > *********************/
        case UI_INPUT_SOURCE_ATSC:
            return en_str_TV;
/********************* < AV > *********************/
#if (INPUT_AV_VIDEO_COUNT == 1)
        case UI_INPUT_SOURCE_AV:
            return en_str_AV;
#elif (INPUT_AV_VIDEO_COUNT == 2)
        case UI_INPUT_SOURCE_AV:
            return en_str_AV_1;
        case UI_INPUT_SOURCE_AV2:
            return en_str_AV_2;
#endif
/********************* < SV > *********************/
#if (INPUT_SV_VIDEO_COUNT == 1)
        case UI_INPUT_SOURCE_SVIDEO:
            return en_str_SdashVideo;
#elif (INPUT_SV_VIDEO_COUNT == 2)
        case UI_INPUT_SOURCE_SVIDEO:
            return en_str_SdashVideo_1;
        case UI_INPUT_SOURCE_SVIDEO2:
            return en_str_SdashVideo_2;
#endif
/********************* < YPBPR > *********************/
#if (INPUT_YPBPR_VIDEO_COUNT == 1)
        case UI_INPUT_SOURCE_COMPONENT:
            return en_str_Component1;
#elif (INPUT_YPBPR_VIDEO_COUNT == 2)
        case UI_INPUT_SOURCE_COMPONENT:
            return en_str_Component1;
        case UI_INPUT_SOURCE_COMPONENT2:
            return en_str_Component2;
#elif (INPUT_YPBPR_VIDEO_COUNT == 3)
        case UI_INPUT_SOURCE_COMPONENT:
            return en_str_Component1;
        case UI_INPUT_SOURCE_COMPONENT2:
            return en_str_Component2;
        case UI_INPUT_SOURCE_COMPONENT3:
            return en_str_DVD;
#endif
/********************* < SCART > *********************/
#if   (INPUT_SCART_VIDEO_COUNT == 1)
        case UI_INPUT_SOURCE_SCART:
            return en_str_SCART;
#elif (INPUT_SCART_VIDEO_COUNT == 2)
        case UI_INPUT_SOURCE_SCART:
            return en_str_SCART;
        case UI_INPUT_SOURCE_SCART2:
            return en_str_SCART;
#endif
/********************* < HDMI > *********************/
#if (ENABLE_HDMI)
  #if (INPUT_HDMI_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_HDMI:
            return en_str_HDMI;
  #endif
  #if (INPUT_HDMI_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_HDMI2:
            return en_str_HDMI2;
  #endif
  #if (INPUT_HDMI_VIDEO_COUNT >= 3)
        case UI_INPUT_SOURCE_HDMI3:
            return  en_str_HDMI1; //return en_str_HDMI3;
  #endif
  #if (INPUT_HDMI_VIDEO_COUNT >= 4)
        case UI_INPUT_SOURCE_HDMI4:
            return en_str_HDMI4;
  #endif
#endif
/********************* < DTV > *********************/
        //case UI_INPUT_SOURCE_DTV:
        default:
            return en_str_DTV;

/********************* < STORAGE > *********************/
/*
#if ENABLE_DMP
        case UI_INPUT_SOURCE_STORAGE:
            return en_str_STORAGE;
#endif
*/
        // TODO: fix me, new string for dmp?
#if ENABLE_DMP
        case UI_INPUT_SOURCE_DMP:
            return en_str_DMP;
#if(ATSC_READY)
      #if( ENABLE_DMP_SWITCH )
        case UI_INPUT_SOURCE_DMP1:
            return en_str_USB1;
        case UI_INPUT_SOURCE_DMP2:
            return en_str_USB2;
      #endif
#endif
#endif
/********************* < RADIO > *********************/
#if(ENABLE_FM_RADIO)
        case UI_INPUT_SOURCE_FMRADIO:
            return en_str_FM_Radio;      //temp use en_str_DMP,waitng for add new string
#endif

#if GAME_ENABLE
        case UI_INPUT_SOURCE_GAME:
            return en_str_Game;
#endif

        }

    return Empty;
}
#endif  //#if ENABLE_ATSC_TTS

void MApp_ZUI_ACT_AppShowInputSource(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_INPUT_SOURCE;

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

    //RECT_SET(rect, ((g_IPanel.HStart()+3)&0xFFFC), 1, g_IPanel.Width(), g_IPanel.Height());
    RECT_SET(rect,
        ZUI_INPUT_SOURCE_XSTART, ZUI_INPUT_SOURCE_YSTART,
        ZUI_INPUT_SOURCE_WIDTH, ZUI_INPUT_SOURCE_HEIGHT);

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
#if ENABLE_ATSC_TTS
    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Input_Source), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Input_Source)));
#endif
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_PVR_SOURCE_CHANGE_CHECK_PANE, SW_HIDE);


    MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_InputSourceIdMapToWindow(UI_INPUT_SOURCE_TYPE));
    MApp_ZUI_API_SendMessage(HWND_SOURCE_INPUT_LIST, MSG_NOTIFY_CONTENT_CHANGED, 0);

#if ENABLE_DMP
    if((UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP))
    {
        MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_SOURCE_INPUT_LIST,
            _MApp_ZUI_ACT_InputSourceIdMapToWindow(UI_PREV_INPUT_SOURCE_TYPE));
    }
    else
#endif
#if ENABLE_ISDBT
   if(MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_CHECK_ANTENNA, NULL, NULL) == EN_FUNC_INPUTSOURCE_STATUS_OK)
   {
      MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_SOURCE_INPUT_LIST,
          _MApp_ZUI_ACT_InputSourceIdMapToWindow(UI_INPUT_SOURCE_ISDBT));
   }
   else
#endif
    {
        MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_SOURCE_INPUT_LIST,
            _MApp_ZUI_ACT_InputSourceIdMapToWindow(UI_INPUT_SOURCE_TYPE));
    }

    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
    _u16LaunchKeys = 0xFFFF;
#if ENABLE_PANEL_BIN
    bSwitchPanelFlag = 0;
#endif

#if(ENABLE_CEC)
    msAPI_CEC_GetDeviceInfo();
#endif
}

LPTSTR MApp_ZUI_ACT_GetInputSourceDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    switch(hwnd)
    {
    #if ENABLE_ISDBT
        case HWND_SOURCE_INPUT_ITEM_ISDB:
            {
                U16 curStringLen = 0;
                U16 u16StrBuf[32];
                MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_ISDB));
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Air));
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = 0;
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
            }
            return (LPTSTR) CHAR_BUFFER;

        case HWND_SOURCE_INPUT_ITEM_ATV:
            {
                U16 curStringLen = 0;
                U16 u16StrBuf[32];
                MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_ISDB));
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Cable));
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = 0;
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
            }
            return (LPTSTR) CHAR_BUFFER;
    #endif
		case HWND_SOURCE_INPUT_ITEM_DMP:    //xzm @20171222
            {
                U16 curStringLen = 0;
                U16 u16StrBuf[32];
                MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_ISDB));
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_DMP));
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = 0;
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
            }
            return (LPTSTR) CHAR_BUFFER;

        case HWND_SOURCE_INPUT_ITEM_HDMI1:
        case HWND_SOURCE_INPUT_ITEM_HDMI2:
        case HWND_SOURCE_INPUT_ITEM_HDMI3:
        case HWND_SOURCE_INPUT_ITEM_HDMI4:
         {

            U16 u16StrBuf[32];
            U16 curStringLen=0;
        #if(ENABLE_CEC)
            U16 u16Value;
            U8 i;
        #endif
			
            if(hwnd == HWND_SOURCE_INPUT_ITEM_HDMI1)
                u16TempID = en_str_HDMI1;
            else if(hwnd == HWND_SOURCE_INPUT_ITEM_HDMI2)
                u16TempID = en_str_HDMI2;
            else if(hwnd == HWND_SOURCE_INPUT_ITEM_HDMI3)
                u16TempID = en_str_HDMI1; //u16TempID = en_str_HDMI3;
            else
                u16TempID = en_str_HDMI4;

            MApp_ZUI_API_Strcpy(u16StrBuf, MApp_ZUI_API_GetString(u16TempID));
            curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);

        #if(ENABLE_CEC)
            if(hwnd == HWND_SOURCE_INPUT_ITEM_HDMI1)
            {
                for(i = 0; i< g_stMenuCecDeviceList.u8CECDeviceNum; i++)
                {
                    u16Value = (((g_stMenuCecDeviceList.wPhyAddr[i] & 0xF000) >> 12) & 0x000F);
                    if(u16Value == 1)
                    {
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        memset(au8Section,0,256);
                        strcpy((char *)au8Section,(char *)g_stMenuCecDeviceList.au8CecDeviceName[i]);
                        MApp_ZUI_API_StringBuffU8toU16((LPTSTR)&u16StrBuf[curStringLen], au8Section, strlen((char *)au8Section));
                        break;
                    }
                }
            }
            else if(hwnd == HWND_SOURCE_INPUT_ITEM_HDMI2)
            {
                for(i = 0; i< g_stMenuCecDeviceList.u8CECDeviceNum; i++)
                {
                    u16Value = (((g_stMenuCecDeviceList.wPhyAddr[i] & 0xF000) >> 12) & 0x000F);
                    if(u16Value == 2)
                    {
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        memset(au8Section,0,256);
                        strcpy((char *)au8Section,(char *)g_stMenuCecDeviceList.au8CecDeviceName[i]);
                        MApp_ZUI_API_StringBuffU8toU16((LPTSTR)&u16StrBuf[curStringLen], au8Section, strlen((char *)au8Section));
                        break;
                    }
                }
            }
            else if(hwnd == HWND_SOURCE_INPUT_ITEM_HDMI3)
            {
                for(i = 0; i< g_stMenuCecDeviceList.u8CECDeviceNum; i++)
                {
                    u16Value = (((g_stMenuCecDeviceList.wPhyAddr[i] & 0xF000) >> 12) & 0x000F);
                    if(u16Value == 3)
                    {
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        memset(au8Section,0,256);
                        strcpy((char *)au8Section,(char *)g_stMenuCecDeviceList.au8CecDeviceName[i]);
                        MApp_ZUI_API_StringBuffU8toU16((LPTSTR)&u16StrBuf[curStringLen], au8Section, strlen((char *)au8Section));
                        break;
                    }
                }
            }
            else
            {
                for(i = 0; i< g_stMenuCecDeviceList.u8CECDeviceNum; i++)
                {
                    u16Value = (((g_stMenuCecDeviceList.wPhyAddr[i] & 0xF000) >> 12) & 0x000F);
                    if(u16Value == 4)
                    {
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        memset(au8Section,0,256);
                        strcpy((char *)au8Section,(char *)g_stMenuCecDeviceList.au8CecDeviceName[i]);
                        MApp_ZUI_API_StringBuffU8toU16((LPTSTR)&u16StrBuf[curStringLen], au8Section, strlen((char *)au8Section));
                        break;
                    }
                }
            }
        #endif

            MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
            curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
            CHAR_BUFFER[curStringLen] = 0;
            return (LPTSTR) CHAR_BUFFER;

          }
          break;

          default:
              break;
    }

    if (u16TempID != Empty)
    {
        return MApp_ZUI_API_GetString(u16TempID);
    }
    else
    {
        return 0; //for empty string....
    }
}

#if ENABLE_OFFLINE_SIGNAL_DETECTION
void MApp_ZUI_ACT_DrawAisIcon(void)
{
    if(MApp_ZUI_API_IsWindowVisible(HWND_SOURCE_INPUT_LIST))
    {
        if(stAISSrcList[UI_INPUT_SOURCE_COMPONENT].bChangeFlag)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_INPUT_ITEM_COMPONENT1);
        }
        else if(stAISSrcList[UI_INPUT_SOURCE_AV].bChangeFlag)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_INPUT_ITEM_AV1);
        }
        else if(stAISSrcList[UI_INPUT_SOURCE_RGB].bChangeFlag)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_INPUT_ITEM_PC);
        }
		else if(stAISSrcList[UI_INPUT_SOURCE_DMP].bChangeFlag)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_INPUT_ITEM_DMP);
        }
    }
}
void MApp_ZUI_ACT_InvalidateAisIcon(void)
{
    if(MApp_ZUI_API_IsWindowVisible(HWND_SOURCE_INPUT_LIST))
    {
        if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_COMPONENT)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_INPUT_ITEM_COMPONENT1);
        }
        else if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_AV)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_INPUT_ITEM_AV1);
        }
        else if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_RGB)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_INPUT_ITEM_PC);
        }
		else if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_INPUT_ITEM_DMP);
        }
    }
}
#endif

U16 MApp_ZUI_ACT_GetInputSourceDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    UNUSED(ds_type);
#if ENABLE_OFFLINE_SIGNAL_DETECTION
    switch(hwnd)
    {
        case HWND_SOURCE_INPUT_ITEM_COMPONENT1_AIS_ICON:
            if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_COMPONENT)
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                    return E_BMP_TRIANGLE_LEFT;
                }
            }
            else
            {
                if(stAISSrcList[UI_INPUT_SOURCE_COMPONENT].bHaveSignal)
                {
                    return E_BMP_TRIANGLE_LEFT;
                }
            }
            break;
        case HWND_SOUCE_INPUT_ITEM_PC_AIS_ICON:
            if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_RGB)
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                    return E_BMP_TRIANGLE_LEFT;
                }
            }
            else
            {
                if(stAISSrcList[UI_INPUT_SOURCE_RGB].bHaveSignal)
                {
                    return E_BMP_TRIANGLE_LEFT;
                }
            }
            break;
        case HWND_SOURCE_INPUT_ITEM_AV1_AIS_ICON:
            if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_AV)
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                    return E_BMP_TRIANGLE_LEFT;
                }
            }
            else
            {
                if(stAISSrcList[UI_INPUT_SOURCE_AV].bHaveSignal)
                {
                    return E_BMP_TRIANGLE_LEFT;
                }
            }
        break;
        default:
        break;
    }
#else
    UNUSED(hwnd);
#endif
    return 0xFFFF; //for empty bitmap....
}

//////////////////////////////////////////////////////////
// Key Handler
BOOLEAN MApp_ZUI_ACT_HandleInputSourceKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state
    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_SOURCE_BG_PANE, 0);
    switch(key)
    {
        case VK_MENU:
            MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_GOTO_MAINMENU);
            return TRUE;
        case VK_EXIT:
#if ENABLE_ATSC_TTS
            MApp_TTS_Cus_Say_exit();
#endif
            MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;
        case VK_POWER:
            MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_POWEROFF);
            return TRUE;
        case VK_SELECT:
            MApp_ZUI_API_SetTimer(HWND_SOURCE_BOTTOM_OK_BTN, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_SOURCE_BOTTOM_OK_BTN);
            break;

        case VK_INPUT_SOURCE:
        {
            break;
        }
        default:
            break;
    }

#if ENABLE_PANEL_BIN
    if(bSwitchPanelFlag == 1)
    {
        if((VK_NUM_0 <= key && key <= VK_NUM_9) && ((key - VK_NUM_0) < MApp_Get_PanelBin_TableNum()))
        {
            G_FACTORY_SETTING.stFacPnlSetting.u8PanelBinIndex = key - VK_NUM_0;
            printf("\n\r[MultiPanel] Switch %d panel index !",G_FACTORY_SETTING.stFacPnlSetting.u8PanelBinIndex);
            MApp_SaveFactorySetting();
            MApp_DB_GEN_SaveData_RightNow();
            MDrv_Sys_WholeChipReset();
            //MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_POWEROFF);
        }
        else if(VK_NUM_0 < key && key <= VK_NUM_9)
        {
            printf("\n\r[MultiPanel] Maxnum Panel Table is %d,only switch 0 ~ %d !",MApp_Get_PanelBin_TableNum(),MApp_Get_PanelBin_TableNum()-1);
        }
        else
        {
            printf("\n\r[MultiPanel] Invalid key,only digital keys are available");
        }
        bSwitchPanelFlag = 0;
    }
#endif
	 if (VK_LEFT<= key && key <= VK_RIGHT)//wht120713_1  if (VK_NUM_0 <= key && key <= VK_NUM_9)
    {	
		printf("_u16LaunchKeys---- %d \n",_u16LaunchKeys);
        _u16LaunchKeys = (_u16LaunchKeys<<4)|(key-VK_LEFT);//wht120713_1 (_u16LaunchKeys<<4)|(key-VK_NUM_0);
		printf("_u16LaunchKeys---- %d \n",_u16LaunchKeys);
        switch (_u16LaunchKeys)
        {
			case 0x0022:
                MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_GOTO_FACTORY_MENU);
                break;
            case 0x2200:
                MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_GOTO_EXPERT_MENU);
                break;
#if 0
			//<<--A-- SMC 20110421   --增加酒店功能--	
			case 0x2500:
				if(MApp_IsUserLockHotalMode())
					MApp_MApp_SetUserHotalModeLock(FALSE);
				else
					MApp_MApp_SetUserHotalModeLock(TRUE);
				break;
			//SMC 20110421 --增加酒店功能-- --A-->> 	
#endif
        }
    }
    else
    {
        _u16LaunchKeys = 0xFFFF;
    }
    //launch code for factory menu, instart menu, media player(testing)
    /*if (VK_NUM_0 <= key && key <= VK_NUM_9)
    {
        _u16LaunchKeys = (_u16LaunchKeys<<4)|(key-VK_NUM_0);
        //printf("key=%u => 0x%X\n", (key-VK_NUM_0), _u16LaunchKeys );
        switch (_u16LaunchKeys)
        {
            case 0x2580:
                MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_GOTO_FACTORY_MENU);
                break;
            case 0x2588:
                MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_GOTO_EXPERT_MENU);
                break;
            case 0x1979:
                MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_GOTO_DESIGN_MENU);
                break;
            case 0x2016:
                MApp_ZUI_ACT_ToggleAudioMessageFlag();
                break;


        #if (ENABLE_UART_MSG_TO_USB)
            case 0x0851:
            {
                //stGenSetting.gbUart2Usb = EN_FacUD_UsbDump_On;
                g_stFactorySetting.stFacMiscSetting.eFactoryUSBLog = EN_FACTORY_USB_LOG_ON;
                msDebug_UartToUSB_Set_Enable(TRUE);
                break;
            }

            case 0x0850:
            {
                //stGenSetting.gbUart2Usb = EN_FacUD_UsbDump_Off;
                g_stFactorySetting.stFacMiscSetting.eFactoryUSBLog = EN_FACTORY_USB_LOG_OFF;
                msDebug_UartToUSB_Reset();
                break;
            }
        #endif


        #if ENABLE_PANEL_BIN
            case 0x2008:
                bSwitchPanelFlag = 1;
                break;
        #endif


        #if (ENABLE_SCRIPT_EXECUTE)
            case 0x0741:
            {
                g_stFactorySetting.stFacMiscSetting.eFactoryExecuteScript= EN_FACTORY_EXECUTE_SCRIPT_ON;
                break;
            }
            case 0x0740:
            {
                msUS_EventInit();
                g_stFactorySetting.stFacMiscSetting.eFactoryExecuteScript = EN_FACTORY_EXECUTE_SCRIPT_OFF;
                break;
            }
        #endif

        }
    }
    else
    {
        _u16LaunchKeys = 0xFFFF;
#if ENABLE_PANEL_BIN
        bSwitchPanelFlag = 0;
#endif
    }
	*/

    return FALSE;
}

void MApp_ZUI_ACT_TerminateInputSource(void)
{
    ZUI_MSG(printf("[]term:input\n");)
    enInputSourceState = _enTargetInputSourceState;

    MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_SAVE_SYS_SETTING, NULL, NULL);
}

E_UI_INPUT_SOURCE _MApp_ZUI_ACT_GetSourceType(void)
{
    E_UI_INPUT_SOURCE source_type;
    if(MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU && MApp_ZUI_API_IsSuccessor(HWND_MENU_APP_PAGE, MApp_ZUI_API_GetFocus()))
    {
          HWND hwnd;
          S16 s16Index = 0;
          hwnd = MApp_ZUI_API_GetFocus();
          s16Index = MApp_ZUI_API_GetChildIndex(hwnd);
          source_type = MApp_ZUI_ACT_GetAppItemSource(s16Index);
    }
    else
    {
          source_type = _MApp_ZUI_ACT_InputSourceWindowMapToId(MApp_ZUI_API_GetFocus());
    }

    return source_type;
}

void MApp_ZUI_ACT_InputSourceSwitch( E_UI_INPUT_SOURCE source_type )
{
    DEBUG_ACT_INPUT_SRC(printf("MApp_ZUI_ACT_InputSourceSwitch(source_type=%u)\n", source_type););


	
    if( source_type >= UI_INPUT_SOURCE_NUM )
    {
        printf("\nError: Invalid source_type=%u!\n", source_type);
        return;
    }

    if( UI_INPUT_SOURCE_TYPE == source_type )
    {
#if ENABLE_ISDBT
        if(!(IS_SBTVD_APP && (msAPI_ATV_GetCurrentAntenna() == ANT_AIR) && source_type == UI_INPUT_SOURCE_ATV))
#endif
        {
            printf("\nWarning: can't change same UI_source=%u!\n", source_type);
            return;
        }
    }
    MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_SOURCE, source_type, NULL);

}

static BOOLEAN s_bAudioMuteMessageFlag = 1;

void MApp_ZUI_ACT_ToggleAudioMessageFlag(void)
{
    s_bAudioMuteMessageFlag = !s_bAudioMuteMessageFlag;
    printf("s_bAudioMuteMessageFlag=%d\n", s_bAudioMuteMessageFlag);
}

U8 MApp_ZUI_ACT_GetAudioMessageFlag(void)
{
    return s_bAudioMuteMessageFlag;
}

BOOLEAN MApp_ZUI_ACT_ExecuteInputSourceAction(U16 act)
{
    DEBUG_ACT_INPUT_SRC(printf("MApp_ZUI_ACT_ExecuteInputSourceAction(act=%u)\n", act););

    switch(act)
    {
#if GAME_ENABLE
        case EN_EXE_GOTO_GAME_PAGE:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_GAME;
            return TRUE;
            break;
#endif

        case EN_EXE_GOTO_MAINMENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_MAIN_MENU;
            return TRUE;
        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            #if ENABLE_DMP
            if(UI_INPUT_SOURCE_DMP == UI_INPUT_SOURCE_TYPE)
            {
                _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_DMP;
            }
            else
            #endif
            _enTargetInputSourceState = STATE_INPUTSOURCE_CLEAN_UP;


            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_GOTO_FACTORY_MENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_OSDPAGE;
            MApp_OSDPage_SetOSDPage(E_OSD_FACTORY_MENU);
            return TRUE;

        case EN_EXE_GOTO_EXPERT_MENU:
            // TODO: entry point
            MS_DEBUG_MSG(printf("MDrv_PQ_StoreCurrentValue\n"));
            MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_STORE_PQ, NULL, NULL);
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_OSDPAGE;
            MApp_OSDPage_SetOSDPage(E_OSD_EXPERT_MENU);
            return TRUE;

        case EN_EXE_GOTO_DESIGN_MENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_OSDPAGE;
            MApp_OSDPage_SetOSDPage(E_OSD_DESIGN_MENU);
            return TRUE;

        //EN_EXE_GOTO_MEDIA_PLAYER do not use currently; MM entry already moved to app list of main menu.
    #if 0
        case EN_EXE_GOTO_MEDIA_PLAYER:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_MEDIAPLAYER;
            return TRUE;
    #endif

    #ifdef ENABLE_BT
        case EN_EXE_GOTO_BT:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_BT;
            return TRUE;
    #endif

    #ifdef ENABLE_KTV
        case EN_EXE_GOTO_KTV:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_KTV;
            return TRUE;
    #endif

    #ifdef ENABLE_YOUTUBE
        case EN_EXE_GOTO_YOUTUBE:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_YOUTUBE;
            return TRUE;
    #endif
    #ifdef ENABLE_EXTENSION
        case EN_EXE_GOTO_EXTENSION:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_EXTENSION;
            return TRUE;
    #endif
    #ifdef ENABLE_RSS
        case EN_EXE_GOTO_RSS:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_RSS;
            return TRUE;
    #endif

        case EN_EXE_GOTO_SWITCH_INPUTSOURCE: //for click animation
            MApp_ZUI_API_SetTimer(HWND_SOURCE_BG_PANE, 0, 100);
            break;

        case EN_EXE_SWITCH_INPUTSOURCE:
            printf("\r\n [EN_EXE_SWITCH_INPUTSOURCE] start \r\n");
            MApp_ZUI_ACT_InputSourceSwitch( _MApp_ZUI_ACT_GetSourceType() );
			#if ENABLE_USB_ITEM_IN_SOURCE_MENU //gchen @ 20171221
			if (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP)
            {
                MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
                _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_DMP;
            }
			MApp_ZUI_ACT_InputSourceSwitch( _MApp_ZUI_ACT_GetSourceType() );    //xzm set choose @20171222
			
			#endif
            printf("\n [EN_EXE_SWITCH_INPUTSOURCE] end \r\n");
            return TRUE;
#if (ENABLE_FM_RADIO)
        case EN_EXE_GOTO_RADIO:
            printf("switch source to radio\n");
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_RADIO;
            return TRUE;
#endif
        case EN_EXE_SHOW_BRIEF_CH_INFO:
            #if (ENABLE_USB_ITEM_IN_SOURCE_MENU) //gchen  @ 20171221
				if (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP)
					return TRUE;
            #endif
			
          #if ENABLE_PVR
            //PVR is recording, so already popup souce change dialog,not do anything here
            if( MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_CHECK_PVR_RECORDING, NULL, NULL) && MApp_ZUI_API_IsWindowVisible(HWND_PVR_SOURCE_CHANGE_CHECK_PANE) )
                return TRUE;
          #endif
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_CH_INFO;
            return TRUE;

    #if ENABLE_PVR
        case EN_EXE_SWITCH_INPUTSOURCE_CONFIRM_OK:
        {
            MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_STOP_PVR, NULL, NULL);
            MApp_ZUI_API_SetFocus( _MApp_ZUI_ACT_InputSourceIdMapToWindow(MApp_InputSource_GetRecordSource()));
            MApp_ZUI_ACT_InputSourceSwitch( _MApp_ZUI_ACT_GetSourceType() );
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_GOTO_CH_INFO;

            break;
        }

        case EN_EXE_SWITCH_INPUTSOURCE_CONFIRM_CANCEL:
            MApp_ZUI_API_ShowWindow(HWND_PVR_SOURCE_CHANGE_CHECK_PANE, SW_HIDE);
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInputSourceState = STATE_INPUTSOURCE_CLEAN_UP;
            break;
    #endif

        case EN_EXE_EFFECT_POPUP:
            printf("EN_EXE_EFFECT_POPUP \r\n");
            switch(MApp_ZUI_API_GetFocus())
            {
                default:
                    break;
            }
            MApp_ZUI_API_PostMessage(MApp_ZUI_API_GetFocus(), MSG_EFFECT_POPUP, (WPARAM)NULL);
        #if ENABLE_OFFLINE_SIGNAL_DETECTION
            MApp_ZUI_ACT_InvalidateAisIcon();
        #endif
            return TRUE;

        case EN_EXE_EFFECT_SLIDEITEM:
            MApp_ZUI_API_PostMessage(MApp_ZUI_API_GetFocus(), MSG_EFFECT_SLIDEITEM, MApp_ZUI_API_GetFocus());
            return TRUE;


    }
    return FALSE;
}


GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryInputSourceItemStatus(HWND hwnd)
{
    U8 i;

    //printf("[]query=%u\n", hwnd);
#if ENABLE_FACTORY_INPUT_SOURCE_FUNCTION
    switch (hwnd)
    {
        case HWND_SOURCE_INPUT_ITEM_S2:
          #if (ENABLE_S2)
            return EN_DL_STATE_NORMAL;
          #else
            return EN_DL_STATE_HIDDEN;
          #endif
            break;

        default:
        {
            for (i = 0; i < COUNTOF(_source_items); i++)
            {
                if (hwnd == _source_items[i].hwnd)
                {
                    if( G_FACTORY_SETTING.stFacMiscSetting.u16_AV_Count == 0 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_AV1 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_AV2 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_AV3 )
                            return EN_DL_STATE_HIDDEN;
                    }
                    else if( G_FACTORY_SETTING.stFacMiscSetting.u16_AV_Count == 1 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_AV2 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_AV3 )
                            return EN_DL_STATE_HIDDEN;
                    }
                    else if( G_FACTORY_SETTING.stFacMiscSetting.u16_AV_Count == 2 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_AV3 )
                            return EN_DL_STATE_HIDDEN;
                    }

                    if( G_FACTORY_SETTING.stFacMiscSetting.u16_SV_Count == 0 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_SVIDEO1 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_SVIDEO2 )
                            return EN_DL_STATE_HIDDEN;
                    }
                    else if( G_FACTORY_SETTING.stFacMiscSetting.u16_SV_Count == 1 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_SVIDEO2 )
                            return EN_DL_STATE_HIDDEN;
                    }

                    if( G_FACTORY_SETTING.stFacMiscSetting.u16_SCART_Count == 0 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_SCART1 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_SCART2 )
                            return EN_DL_STATE_HIDDEN;
                    }
                    else if( G_FACTORY_SETTING.stFacMiscSetting.u16_SCART_Count == 1 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_SCART2 )
                            return EN_DL_STATE_HIDDEN;
                    }

                    if( G_FACTORY_SETTING.stFacMiscSetting.u16_COMPONENT_Count == 0 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_COMPONENT1 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_COMPONENT2 )
                            return EN_DL_STATE_HIDDEN;
                    }
                    else if( G_FACTORY_SETTING.stFacMiscSetting.u16_COMPONENT_Count == 1 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_COMPONENT2 )
                            return EN_DL_STATE_HIDDEN;
                    }

                    if( G_FACTORY_SETTING.stFacMiscSetting.u16_HDMI_Count == 1 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_HDMI2 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_HDMI3 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_HDMI4 )
                            return EN_DL_STATE_HIDDEN;
                    }
                    else if( G_FACTORY_SETTING.stFacMiscSetting.u16_HDMI_Count == 2 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_HDMI3 )
                            return EN_DL_STATE_HIDDEN;
                        else if ( hwnd == HWND_SOURCE_INPUT_ITEM_HDMI4 )
                            return EN_DL_STATE_HIDDEN;
                    }
                    else if( G_FACTORY_SETTING.stFacMiscSetting.u16_HDMI_Count == 3 )
                    {
                        if ( hwnd == HWND_SOURCE_INPUT_ITEM_HDMI4 )
                            return EN_DL_STATE_HIDDEN;
                    }
                    return EN_DL_STATE_NORMAL;
                }
            }
            return EN_DL_STATE_HIDDEN;
        }
        break;
    }
#else

#if ENABLE_ISDBT_AND_DVB
    switch(hwnd)
    {
        case HWND_SOURCE_INPUT_ITEM_DVBT:
        case HWND_SOURCE_INPUT_ITEM_DVBC:
            if(IS_SBTVD_APP)
            {
                return EN_DL_STATE_HIDDEN;
            }
            break;

        case HWND_SOURCE_INPUT_ITEM_ISDB:
            if(!IS_SBTVD_APP)
            {
                return EN_DL_STATE_HIDDEN;
            }
            break;
    }
#endif

    for (i = 0; i < COUNTOF(_source_items); i++)
    {
        if (hwnd == _source_items[i].hwnd)
        {
            return EN_DL_STATE_NORMAL;
        }
    }
#endif
    return EN_DL_STATE_HIDDEN;
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_InputSourceWinProc
///  [MENU application customization] top circle icon rotate animation
///
///  @param [in]       hwnd HWND     window handle we are processing
///  @param [in]       msg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_ACT_InputSourceWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
    #if ENABLE_ISDBT
        case MSG_PAINT:
            if (hwnd == HWND_SOURCE_INPUT_ITEM_ISDB || hwnd == HWND_SOURCE_INPUT_ITEM_ATV)
            {
                if(IS_SBTVD_APP)
                    return DYNAMICTEXT_WINPROC(hwnd, msg);
            }
                break;
    #endif

        case MSG_NOTIFY_SETFOCUS:
        #if ENABLE_ATSC_TTS
            {
                U16 u16SrcStrID = _ZUI_ACT_GetInputSourceStringID(MApp_ZUI_API_GetFocus());
                //printf("u16SrcStrID=%u\n", u16SrcStrID);

                MApp_TTS_Cus_Say_InputSource(u16SrcStrID);

                //MApp_TTS_Cus_Add_Str_By_StrId(u16SrcStrID);
                //MApp_TTSControlSetOn(TRUE);
            }
        #endif
            break;

        case MSG_TIMER:
            if(hwnd == HWND_SOURCE_BG_PANE)
            {
                MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_ACT_InputSourceSwitch( _MApp_ZUI_ACT_GetSourceType() );
                MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_CLOSE_CURRENT_OSD);
            }

        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
    //return EFFECT_WINPROC(hwnd, msg);
}

/////////////////////////////////////////////////////////
// Customize Window Procedures

void MApp_Ui_InputSourcePage_Notify(INPUT_SOURCE_PAGE_NOTIFY_TYPE enInputSourcePageNotify, U16 para1, U16 para2)
{
    para1 = para1;
    para2 = para2;
    switch (enInputSourcePageNotify)
    {
        case EN_INPUT_SOURCE_PAGE_NOTIFY_PVR_SOURCE_CHANGE_CHECK_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_PVR_SOURCE_CHANGE_CHECK_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_PVR_SOURCE_CHANGE_CHECK_TXT_2);
            break;

        default:
            break;
    }
}



//
//******************************************************************************
//
#undef MAPP_ZUI_ACTINPUTSOURCE_C

