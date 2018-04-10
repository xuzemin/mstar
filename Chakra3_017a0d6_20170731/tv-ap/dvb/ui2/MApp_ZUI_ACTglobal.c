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

#define MAPP_ZUI_ACTGLOBAL_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"

#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiGOP.h"

#include "MApp_GlobalSettingSt.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTmainpage.h"

#include "MApp_ZUI_APIcontrols.h"
#include "ZUI_exefunc.h"
#include "MApp_UiMenuDef.h"
#include "MApp_Key.h"


#include "MApp_ZUI_CTLbuttonclick.h"
#if (DTV_USE_FBL)
  #include "apiVDEC.h"
#endif
//osd pages....
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTmenufunc.h"
#include "MApp_ZUI_ACTchannelinfo.h"
#if(ENABLE_ATSC)
#include "MApp_ZUI_ACTchannelinfo_ATSC.h"
#include "msAPI_Global.h"
#include "MApp_ChannelProc_ATSC.h"
#endif
#include "MApp_ZUI_ACTchlist.h"
#if ENABLE_DVBC
#include "MApp_ZUI_ACTcadtvmanualtuning.h"
#endif
#include "MApp_ZUI_ACTdtvmanualtuning.h"
#include "MApp_ZUI_ACTatvmanualtuning.h"
#include "MApp_ZUI_ACTpredit.h"
#include "MApp_ZUI_ACTaudlang.h"
#include "MApp_ZUI_ACTautotuning.h"
#include "MApp_ZUI_ACTscreensaver.h"
#include "MApp_ZUI_ACTinputsource.h"
#include "MApp_ZUI_ACTaudiovolume.h"
#include "MApp_ZUI_ACTinstall.h"
#if ENABLE_ATSC_INSTALLGUIDE
#include "MApp_ZUI_ACTinstall_ATSC.h"
#endif
#include "MApp_ZUI_ACThotkey.h"
#include "MApp_ZUI_ACTsublang.h"
#include "MApp_ZUI_ACTmsgbox.h"
#include "MApp_ZUI_ACTmenudlgfunc.h"
#include "MApp_ZUI_ACTepg.h"
#include "MApp_ZUI_ACTcimmi.h"
#include "MApp_ZUI_ACTexpertmenu.h"
#include "MApp_ZUI_ACTepop.h"
#include "MApp_ZUI_ACTkeystoneangle.h"
#if (ENABLE_OAD)
#include "MApp_ZUI_ACToad.h"
#endif
#if ENABLE_DMP
#include "MApp_ZUI_ACTdmp.h"
#if ENABLE_DMP_MINI_MENU
#include "MApp_ZUI_ACTdmpminimenu.h"
#endif
#include "mapp_txt.h"
#endif
#ifdef ENABLE_BT
#include "MApp_ZUI_ACTBT.h"
#endif

#ifdef ENABLE_KTV
#include "MApp_ZUI_ACTKTV.h"
#endif

#if ENABLE_PVR
    #include "MApp_ZUI_ACTpvr.h"
    #include "MApp_ZUI_ACTpvrBrowser.h"
#else
    #include "MApp_Subtitle.h"
#endif

#include "MApp_ZUI_ACTfactorymenu.h"
#include "MApp_ZUI_ACTdesignmenu.h"
#include "MApp_ZUI_ACTtenkey.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTeffectsetting.h"

#include "MApp_ZUI_ACTflippage.h"

#if (ENABLE_MFC_6M20)
#include "drvUrsaMFCAPI.h"
#endif

#if ENABLE_MFC_6M30
#include "drvUrsa6M30.h"
#endif

#if(ENABLE_6M40_4KX2K_PROCESS)
#include "drvUrsa6M40.h"
#endif

#if ENABLE_S2
#include "MApp_ZUI_ACTDishSetup.h"
#include "MApp_ChannelChange.h"
#endif

#if  (( (BRAZIL_CC))||(ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#endif
#include "msAPI_ATVSystem.h"
#if ENABLE_FM_RADIO
#include "MApp_ZUI_ACTFMRadio.h"
#endif

#if GAME_ENABLE
#include "MApp_ZUI_ACTGameList.h"
#endif
extern ZUI_STATE _eZUIState;
extern E_OSD_ID _eActiveOSD;
#if ENABLE_DMP_MINI_MENU
extern void MApp_ZUI_ACT_AppShowDmpMiniMenu(void);
#endif
/////////////////////////////////////////////////////////
// for customize

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_DecIncValue
///  increase or decrease a value with min, max and step
///
///  @param [in]       bInc BOOLEAN    increase or not
///  @param [in]       u16Value U16    integer value
///  @param [in]       u16MinValue U16    min value
///  @param [in]       u16MaxValue U16    max value
///  @param [in]       u8Step U8          step value
///
///  @return U16 result integer
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
U16 MApp_ZUI_ACT_DecIncValue(BOOLEAN bInc, U16 u16Value, U16 u16MinValue, U16 u16MaxValue, U8 u8Step)
{
    if (bInc) //((action == MIA_INCVALUE)||(action == MIA_INCVALUE_BAR))
    {
        if(u16Value >= u16MaxValue)
            return u16MaxValue;
        u16Value += u8Step;
        if(u16Value > u16MaxValue)
            u16Value = u16MaxValue;
    }
    else //if( (action==MIA_DECVALUE) || (action == MIA_DECVALUE_BAR))
    {
        if(u16Value <= u16MinValue)
            return u16MinValue;
        if(u16Value < u8Step)
            u16Value = 0;
        else
            u16Value -= u8Step;
        if(u16Value < u16MinValue)
            u16Value = u16MinValue;
    }
    return u16Value;
}

S8 MApp_ZUI_ACT_DecIncS8Value(BOOLEAN bInc, S8 s8Value, S8 s8MinValue, S8 s8MaxValue, U8 u8Step)
{
    if (bInc) //((action == MIA_INCVALUE)||(action == MIA_INCVALUE_BAR))
    {
        if((S8)(s8Value + u8Step) >= s8MaxValue)
            return s8MaxValue;
        else
            return (S8)(s8Value + u8Step);
    }
    else //if( (action==MIA_DECVALUE) || (action == MIA_DECVALUE_BAR))
    {
       if((S8)(s8Value - u8Step) <= s8MinValue)
            return s8MinValue;
       else
            return (S8)(s8Value - u8Step);
    }
    return s8Value;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_DecIncValue_Cycle
///  increase or decrease a value with min, max and step
///    if reach to max value => cycle to min value
///
///  @param [in]       bInc BOOLEAN    increase or not
///  @param [in]       u16Value U16    integer value
///  @param [in]       u16MinValue U16    min value
///  @param [in]       u16MaxValue U16    max value
///  @param [in]       u8Step U8          step value
///
///  @return U16 result integer
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
U16 MApp_ZUI_ACT_DecIncValue_Cycle(BOOLEAN bInc, U16 u16Value, U16 u16MinValue, U16 u16MaxValue, U8 u8Step)
{
    if (bInc) //action == MIA_INCVALUE)
    {
        if (u16Value >= u16MaxValue)
        {
            return u16MinValue;
        }
        if (u16Value < u16MinValue)
        {
            // Minimun value
            u16Value = u16MinValue;
        }
        else
        {
            u16Value += u8Step;
        }
        if (u16Value > u16MaxValue)
        {
            u16Value = u16MinValue;
        }
    }
    else //if (action == MIA_DECVALUE)
    {
        if (u16Value <= u16MinValue)
        {
            return u16MaxValue;
        }
        if (u16Value < u8Step)
        {
            u16Value = 0;
        }
        else
        {
            u16Value -= u8Step;
        }
        if (u16Value < u16MinValue)
        {
            u16Value = u16MaxValue;
        }
    }
    return u16Value;
}

//This function is just for the Singapore.
U16 MApp_ZUI_ACT_DecIncParentalRatingClass_Cycle(BOOLEAN bInc, U16 u16Value)
{
    if(bInc)
    {
        switch(u16Value)
        {
            case 3:
                u16Value = 4;//G
                break;
            case 4:
                u16Value = 7;//PG
                break;
            case 7:
                u16Value = 13;//PG13
                break;
            case 13:
                u16Value = 16;//NC16
                break;
            case 16:
                u16Value = 18;//M18
                break;
            case 18:
                u16Value = 21;//R21
                break;
            case 21:
                u16Value = 3;//off
                break;

            default:
                u16Value = 3;
                break;
        }
    }
    else
    {
        switch(u16Value)
        {
            case 3:
                u16Value = 21;//R21
                break;
            case 4:
                u16Value = 3;//off
                break;
            case 7:
                u16Value = 4;//G
                break;
            case 13:
                u16Value = 7;//PG
                break;
            case 16:
                u16Value = 13;//PG13
                break;
            case 18:
                u16Value = 16;//NC16
                break;
            case 21:
                u16Value = 18;//M18
                break;

            default:
                u16Value = 3;
                break;
        }
    }
    return u16Value;
}


U16 DEC_TO_HEX(U16 u16DecValue)
{
    U16 u16HexValue_Integer = 0;
    U16 u16HexValue_Remainder = 0;
    U16 u16HexValue = 0;

    u16HexValue_Integer = u16DecValue/16;
    if(u16DecValue%16 < 10)
    {
        u16HexValue_Remainder = u16DecValue%16;
    }
    else
    {
        u16HexValue_Remainder = (0x0A + (u16DecValue%16 - 10));
    }

    u16HexValue = (u16HexValue_Integer<<4)|u16HexValue_Remainder;
    return u16HexValue;
}


///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_ACT_MapToVirtualKeyCode
///     map system-dependent key code to system-independent key code
///     this mapping might be changed for different project/codebase
///
///  @param [in]       IR_key_code U8          system-dependent key code
///
///  @return VIRTUAL_KEY_CODE    system-independent key code
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
VIRTUAL_KEY_CODE _MApp_ZUI_ACT_MapToVirtualKeyCode(U8 IR_key_code)
{
    switch(IR_key_code)
    {
#if 1
        case KEY_TEMP_DET:			 return VK_TEMP_DET; 
#endif
		case KEY_BAT_LOW:			 return VK_BAT_LOW;//wht141014_8
        //case KEY_TV_RADIO:            return VK_TV_RADIO;
        //case KEY_CHANNEL_LIST:        return VK_CHANNEL_LIST;
        case KEY_CHANNEL_FAV_LIST:  return VK_CHANNEL_FAV_LIST;
        case KEY_CHANNEL_RETURN:    return VK_CHANNEL_RETURN;
        case KEY_CHANNEL_PLUS:      return VK_CHANNEL_PLUS;
        case KEY_CHANNEL_MINUS:     return VK_CHANNEL_MINUS;

        case KEY_AUDIO:             return VK_AUDIO;
        case KEY_VOLUME_PLUS:      return VK_VOLUME_PLUS;
        case KEY_VOLUME_MINUS:       return VK_VOLUME_MINUS;
		
		case KEY_KEYSTONE_POS:      return VK_KEYSTONE_PLUS;    //xzm @20171228 for keystone
        case KEY_KEYSTONE_NEG:      return VK_KEYSTONE_MINUS;
		
        case KEY_UP:                return VK_UP;
        case KEY_POWER:             return VK_POWER;
        case KEY_EXIT:              return VK_EXIT;
        case KEY_MENU:              return VK_MENU;
        case KEY_DOWN:              return VK_DOWN;
        case KEY_LEFT:              return VK_LEFT;
        case KEY_SELECT:            return VK_SELECT;
        case KEY_RIGHT:             return VK_RIGHT;
        case KEY_HOME:              return VK_HOME;
        case KEY_0:             return VK_NUM_0;
        case KEY_1:             return VK_NUM_1;
        case KEY_2:             return VK_NUM_2;
        case KEY_3:             return VK_NUM_3;
        case KEY_4:             return VK_NUM_4;
        case KEY_5:             return VK_NUM_5;
        case KEY_6:             return VK_NUM_6;
        case KEY_7:             return VK_NUM_7;
        case KEY_8:             return VK_NUM_8;
        case KEY_9:             return VK_NUM_9;

        case KEY_MUTE:              return VK_MUTE;
        //case KEY_PAGE_UP:             return VK_PAGE_UP;
        //case KEY_PAGE_DOWN:           return VK_PAGE_DOWN;
        case KEY_INPUT_SOURCE:          return VK_INPUT_SOURCE;
        case KEY_CHANNEL_LIST:          return VK_CHANNEL_LIST;
        case KEY_EPG:                   return VK_EPG;
        case KEY_INFO:                  return VK_INFO;
        case KEY_BACK:                  return VK_BACK;
        case KEY_RED:                   return VK_RED;
        case KEY_GREEN:                 return VK_GREEN;
        case KEY_BLUE:                  return VK_BLUE;
        case KEY_YELLOW:                return VK_YELLOW;
        case KEY_MTS:                   return VK_MTS;
        case KEY_TTX:                   return VK_TTX;
        case KEY_SLEEP:                 return VK_SLEEP;
        case KEY_PICTURE:               return VK_PICTURE;
        case KEY_ZOOM:                  return VK_ZOOM;
        case KEY_FREEZE:                return VK_FREEZE;
        case KEY_INDEX:                 return VK_INDEX;

#if ENABLE_DMP
        case KEY_PLAY:      printf("hotkey KEY_PLAY \n");            return VK_PLAY;
        case KEY_PAUSE:                 return VK_PAUSE;
        case KEY_STOP:                  return VK_STOP;
        case KEY_NEXT:                  return VK_NEXT;
        case KEY_PREVIOUS:              return VK_PREVIOUS;
        case KEY_FF:                    return VK_FF;
        case KEY_REWIND:                return VK_REWIND;
        case KEY_PAGE_UP:               return VK_PAGE_UP;
        case KEY_PAGE_DOWN:             return VK_PAGE_DOWN;
        case KEY_CC:                    return VK_CC;
        case KEY_RECORD:                return VK_RECORD;
        case KEY_SUBTITLE:              return VK_SUBTITLE;
        case KEY_UPDATE:                return VK_UPDATE;
#endif

//#if (ENABLE_PIP)
        case KEY_PIP:                return VK_PIP;
//#endif

        //fake keys...
        case KEY_COUNTDOWN_EXIT_TT_SUBTITLE: return VK_EXIT;
        case KEY_EPGTIMER_COUNTDOWN:
        {
            #if ENABLE_DMP

            if( MApp_ZUI_GetActiveOSD() == E_OSD_DMP )
            {
                return VK_EPGTIMER_COUNTDOWN;
            }
            else
            #endif
            {
                return VK_EXIT;
            }

        }

        default:                    return VK_NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_ACT_AppClose
///  close an application, default procedure
///    NOTE: DO NOT MODIFY THIS FUNCTION!
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
static void _MApp_ZUI_ACT_AppClose(void)
{
    HWND wnd;

    //UNUSED(sender);

    MApp_ZUI_API_SetFocus(HWND_INVALID);

    //for (wnd = HWND_MAX-1; wnd != HWND_INVALID; --wnd) //NOTE: from child to parent
    //  MApp_ZUI_API_PostMessage(wnd, MSG_DESTROYPANES, 0);
    for (wnd = HWND_MAX-1; wnd != HWND_INVALID; --wnd)
        MApp_ZUI_API_SendMessage(wnd, MSG_DESTROY, 0);

    //MApp_Menu_Album_Delete ();

    g_GUI_WindowList = 0;
    g_GUI_WinDrawStyleList =    0;
    g_GUI_WindowPositionList = 0;
    #if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = 0;
    #endif
    HWND_MAX = HWND_MAINFRAME+1;
}

BOOLEAN MApp_ZUI_ACT_Startup_ChannelInfo_OSD(void)
{
#if(ENABLE_ATSC)
    if ((IsAtscInUse() || IsATVInUse()))
    {
        if(MApp_ChanProc_GetNumOfServices(MAIN_LIST))
        {
            MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO_ATSC);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
#endif
    {
        MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
        return TRUE;
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_StartupOSD
///  startup and setup a specific osd page
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       id E_OSD_ID     osd page index
///
///  @return BOOLEAN success or not
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_StartupOSD2(U32 id)
{
    //2007/12/26: consider gop switching
    U8 u8PrevGopID = MApi_GOP_GWIN_GetCurrentGOP();

    ZUI_MSG(printf("[]startup:%u [now=%u,%u]\n", (U8)id, (U8)_eActiveOSD, (U8)_eZUIState));
#if (ENABLE_CI && ENABLE_CI_PLUS && MHEG5_ENABLE)
    if((id == E_OSD_SCREEN_SAVER)&&(E_MHEG_CI_RUNNING == msAPI_IsCIMHEGRun()))
        return FALSE;
#endif

#if ( (BRAZIL_CC))
  if ( (IsDTVInUse() && DB_CC_SETTING.enDTVCaptionType != DTV_CAPTION_OFF)
     ||(( IsATVInUse() || IsAVInUse() ) && DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF) )
  {
      if ( MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
      {
          MApp_CC_StopParser();
          #if (!ENABLE_BRAZIL_CC_DETECT_FLAG)
          MApp_Dmx_PES_Stop();
          #endif
      }
  }
#endif

#if (ATSC_CC == ATV_CC)
    if ((IsATVInUse()||IsAVInUse())&& DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF)
    {
        if ( MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
        {
             MApp_CC_StopParser();
        }
    }
#endif
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
        if (IsDTVInUse())
        {
        #if (ENABLE_SUBTITLE)
            if (( MApp_Subtitle_GetStatus() == STATE_SUBTITLE_DECODING)
            #if(ENABLE_TTX)
                ||(MApp_TTX_IsTeletextOn()&&stGenSetting.g_SysSetting.fEnableTTXSubTitle)
            #endif
                )
            {
                 MApp_Subtitle_SetShowStatus(FALSE);
            }
        #endif
        #if 0 //ENABLE_TTX
            MApp_TTX_ExitDTV_TTXSystem();
        #endif
        }
#endif

    if (_eZUIState == E_ZUI_STATE_UNKNOW)
        return FALSE;

    if (_eZUIState == E_ZUI_STATE_RUNNING && _eActiveOSD == id)
        return TRUE; //already init

    if (u8PrevGopID != OSD_GOP_ID)
        MApi_GOP_GWIN_SwitchGOP(OSD_GOP_ID);


    if (_eZUIState != E_ZUI_STATE_STANDBY)
    {
        MApp_ZUI_ACT_ShutdownOSD();
    }

    //printf("sizeof(WINDOWALPHADATA)=%bu\n", (U8)sizeof(WINDOWALPHADATA));
    //printf("sizeof(WINDOWDRAWSTYLEDATA)=%bu\n", (U8)sizeof(WINDOWDRAWSTYLEDATA));
    //printf("sizeof(WINDOWDATA)=%bu\n", (U8)sizeof(WINDOWDATA));

    MApp_ZUI_API_SetFocus(HWND_INVALID);
    _eZUIState = E_ZUI_STATE_RUNNING;
    _eActiveOSD = (E_OSD_ID) id;
    MApp_ZUI_API_EmptyMessageQueue();

    //NOTE: if an new OSD page added, please add here!
    switch(id)
    {
        case E_OSD_MAIN_MENU:
            MApp_ZUI_ACT_AppShowMainMenu();
            break;

        case E_OSD_CHANNEL_INFO:
            MApp_ZUI_ACT_AppShowChannelInfo();
            break;
#if (ENABLE_ATSC)
        case E_OSD_CHANNEL_INFO_ATSC:
                MApp_ZUI_ACT_AppShowChannelInfo_ATSC();
            break;
#endif

#if (ENABLE_DTMB || ENABLE_DVBT || ENABLE_DVBC || ENABLE_ISDBT || ENABLE_ATSC_SCAN_NEW_MODE)
        case E_OSD_DTV_MANUAL_TUNING:
            MApp_ZUI_ACT_AppShowDtvManualTuning();
            break;
#endif
        case E_OSD_ATV_MANUAL_TUNING:
            MApp_ZUI_ACT_AppShowAtvManualTuning();
            break;

        case E_OSD_PROGRAM_EDIT:
            MApp_ZUI_ACT_AppShowProgramEdit();
            break;

        case E_OSD_AUDIO_LANGUAGE:
            MApp_ZUI_ACT_AppShowAudioLanguage();
            break;

        #if ENABLE_SUBTITLE
        case E_OSD_SUBTITLE_LANGUAGE:
            MApp_ZUI_ACT_AppShowSubtitleLanguage();
            break;
        #endif

        case E_OSD_AUTO_TUNING:
            MApp_ZUI_ACT_AppShowAutoTuning();
            break;

        case E_OSD_SCREEN_SAVER:
            MApp_ZUI_ACT_AppShowScreenSaver();
            break;

        case E_OSD_INPUT_SOURCE:
            MApp_ZUI_ACT_AppShowInputSource();
            break;

        case E_OSD_AUDIO_VOLUME:
            MApp_ZUI_ACT_AppShowAudioVolume();
            break;

        case E_OSD_INSTALL_GUIDE:
            MApp_ZUI_ACT_AppShowInstallGuide();
            break;

#if ENABLE_ATSC_INSTALLGUIDE
        case E_OSD_INSTALL_GUIDE_ATSC:
            MApp_ZUI_ACT_AppShowInstallGuide_ATSC();
            break;
#endif

        case E_OSD_HOTKEY_OPTION:
            MApp_ZUI_ACT_AppShowHotkeyOption();
            break;

        case E_OSD_MESSAGE_BOX:
            MApp_ZUI_ACT_AppShowMessageBox();
            break;

        case E_OSD_CHANNEL_LIST:
            MApp_ZUI_ACT_AppShowChannelList();
            break;
#if (ENABLE_OAD)
        case E_OSD_OAD:
            MApp_ZUI_ACT_AppShowOAD();
            break;
#endif


    case E_OSD_EPG:
#if (ENABLE_ATSC)
        if (IsAtscInUse() || IsATVInUse())
        {
            MApp_ZUI_ACT_AppShowEpg_ATSC();
            break;
        }
#endif

#if (ENABLE_DTV_EPG)
        #if ENABLE_DVB
               MApp_ZUI_ACT_AppShowEpg();
        #endif
            break;
#endif  //#if (ENABLE_DTV_EPG)

#if (ENABLE_CI)
        case E_OSD_CIMMI:
            MApp_ZUI_ACT_AppShowCIMMI();
            break;
#endif
		case E_OSD_KEYSTONE_ANGLE:
			printf("E_OSD_KEYSTONE_ANGLE \n");
            MApp_ZUI_ACT_AppShowKeystoneAngle();
            break;

#if ENABLE_DMP
        case E_OSD_DMP:
            MApp_ZUI_ACT_AppShowDmp();
            break;

    #if ENABLE_DMP_MINI_MENU
        case E_OSD_DMP_MINI_MENU:
            MApp_ZUI_ACT_AppShowDmpMiniMenu();
            break;
    #endif
#endif
#if ENABLE_FM_RADIO
        case E_OSD_FMRADIO:
            MApp_ZUI_ACT_AppShowFMRadio();
            break;
#endif

        case E_OSD_FACTORY_MENU:
            MApp_ZUI_ACT_AppShowFactoryMenu();
            break;

        case E_OSD_EXPERT_MENU:
            MApp_ZUI_ACT_AppShowExpertMenu();
            break;


        case E_OSD_DESIGN_MENU:
            MApp_ZUI_ACT_AppShowDesignMenu();
            break;

        case E_OSD_TENKEY_NUMBER:
            MApp_ZUI_ACT_AppShowTenKeyNumber();
            break;

#ifdef ENABLE_BT
        case E_OSD_BT:
            MApp_ZUI_ACT_AppShowBT();
            break;
#endif

#ifdef ENABLE_KTV
        case E_OSD_KTV:
            MApp_ZUI_ACT_AppShowKTV();
            break;
#endif

#if(ENABLE_PVR ==1)
        case E_OSD_PVR:
            MApp_ZUI_ACT_AppShowPVR();
            break;
        case E_OSD_PVR_BROWSER:
          #if(ENABLE_PVR_BROWSER)
            MApp_ZUI_ACT_AppShowPvrBrowser();
          #endif
            break;
#endif

    #if ENABLE_DVBC
        case E_OSD_CADTV_MANUAL_TUNING:
            MApp_ZUI_ACT_AppShowCadtvManualTuning();
            break;
    #endif

        case E_OSD_EFFECT_SETTING:
            MApp_ZUI_ACT_AppShowEffectSetting();
            break;
    #if ENABLE_S2
        case E_OSD_MENU_DISHSETUP:
            MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
            MApp_ZUI_ACT_AppShowDishSetupMenu();
            break;
    #endif

    #if ENABLE_E_POP
        case E_OSD_EPOP:
            printf("\n case E_OSD_EPOP:\n");
            MApp_ZUI_ACT_AppShowEpop();
            break;
    #endif

#if GAME_ENABLE
        case E_OSD_GAME_LIST:
        {
            MApp_ZUI_ACT_AppShowGameList();
            break;
        }
#endif

        default:
            ZUI_DBG_FAIL(printf("[ZUI]GBLSHOW\n"));
            ABORT();
            break;
    }

    if (u8PrevGopID != OSD_GOP_ID)
        MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);

      #if (ENABLE_MFC_6M20)
         printf("\r\nOSD Area on");
         MDrv_Ursa_OsdWinHandler(TRUE);
      #endif

    return TRUE; //handled
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_TerminateOSD
///  terminate current OSD page. default procedure
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_ACT_TerminateOSD(void)
{
    ZUI_MSG(printf("[]terminate\n"));
    //2008-01-31: if (_eZUIState == E_ZUI_STATE_TERMINATE)
    {
        //NOTE: if an new OSD page added, please add here!
        switch(_eActiveOSD)
        {
            case E_OSD_MAIN_MENU:
                MApp_ZUI_ACT_TerminateMainMenu();
                break;

            case E_OSD_CHANNEL_INFO:
                MApp_ZUI_ACT_TerminateChannelInfo();
                break;
#if (ENABLE_ATSC)
            case E_OSD_CHANNEL_INFO_ATSC:
                    MApp_ZUI_ACT_TerminateChannelInfo_ATSC();
                break;
#endif

#if (ENABLE_DTMB || ENABLE_DVBT || ENABLE_DVBC || ENABLE_ISDBT || ENABLE_ATSC_SCAN_NEW_MODE)
            case E_OSD_DTV_MANUAL_TUNING:
                MApp_ZUI_ACT_TerminateDtvManualTuning();
                break;
#endif
            case E_OSD_ATV_MANUAL_TUNING:
                MApp_ZUI_ACT_TerminateAtvManualTuning();
                break;

            case E_OSD_PROGRAM_EDIT:
                MApp_ZUI_ACT_TerminateProgramEdit();
                break;

            case E_OSD_AUDIO_LANGUAGE:
                MApp_ZUI_ACT_TerminateAudioLanguage();
                break;

            #if ENABLE_SUBTITLE
            case E_OSD_SUBTITLE_LANGUAGE:
                MApp_ZUI_ACT_TerminateSubtitleLanguage();
                break;
            #endif

            case E_OSD_AUTO_TUNING:
                MApp_ZUI_ACT_TerminateAutoTuning();
                break;

            case E_OSD_SCREEN_SAVER:
                MApp_ZUI_ACT_TerminateScreenSaver();
                break;

            case E_OSD_INPUT_SOURCE:
                MApp_ZUI_ACT_TerminateInputSource();
                break;

            case E_OSD_AUDIO_VOLUME:
                MApp_ZUI_ACT_TerminateAudioVolume();
                break;
			
			case E_OSD_KEYSTONE_ANGLE:
                MApp_ZUI_ACT_TerminateKeystoneAngle();
                break;
			
            case E_OSD_INSTALL_GUIDE:
                MApp_ZUI_ACT_TerminateInstallGuide();
                break;

#if ENABLE_ATSC_INSTALLGUIDE
            case E_OSD_INSTALL_GUIDE_ATSC:
                MApp_ZUI_ACT_TerminateInstallGuide_ATSC();
                break;
#endif

            case E_OSD_HOTKEY_OPTION:
                MApp_ZUI_ACT_TerminateHotkeyOption();
                break;

            case E_OSD_MESSAGE_BOX:
                MApp_ZUI_ACT_TerminateMessageBox();
                break;

            case E_OSD_CHANNEL_LIST:
                MApp_ZUI_ACT_TerminateChannelList();
                break;
#if (ENABLE_OAD)
            case E_OSD_OAD:
                MApp_ZUI_ACT_TerminateOAD();
                break;
#endif


            case E_OSD_EPG:
                #if (ENABLE_ATSC)
                if (IsAtscInUse() || IsATVInUse())
                {
                    MApp_ZUI_ACT_TerminateEpg_ATSC();
                    break;
                }
                #endif

#if (ENABLE_DTV_EPG)

                #if ENABLE_DVB
                    MApp_ZUI_ACT_TerminateEpg();
                #endif
#endif  //#if (ENABLE_DTV_EPG)

            break;
#if (ENABLE_CI)
            case E_OSD_CIMMI:
                MApp_ZUI_ACT_TerminateCIMMI();
                break;
#endif
#if ENABLE_DMP
            case E_OSD_DMP:
                MApp_ZUI_ACT_TerminateDmp();
                break;
#endif
#if ENABLE_FM_RADIO
            case E_OSD_FMRADIO:
                MApp_ZUI_ACT_TerminateFMRadio();
                break;
#endif

            case E_OSD_FACTORY_MENU:
                MApp_ZUI_ACT_TerminateFactoryMenu();
                break;

            case E_OSD_EXPERT_MENU:
                MApp_ZUI_ACT_TerminateExpertMenu();
                break;

            case E_OSD_DESIGN_MENU:
                MApp_ZUI_ACT_TerminateDesignMenu();
                break;

            case E_OSD_TENKEY_NUMBER:
                MApp_ZUI_ACT_TerminateTenKeyNumber();
                break;

        #if 0//def ENABLE_BT
            case E_OSD_BT:
                MApp_ZUI_ACT_TerminateBT();
                break;
        #endif

        #if 0//def ENABLE_KTV
            case E_OSD_KTV:
                MApp_ZUI_ACT_TerminateKTV();
                break;
        #endif

        #if ENABLE_PVR
            case E_OSD_PVR:
                MApp_ZUI_ACT_TerminatePVR();
                break;

            case E_OSD_PVR_BROWSER:
              #if(ENABLE_PVR_BROWSER)
                MApp_ZUI_ACT_TerminatePvrBrowser();
              #endif
                break;
        #endif

        #if ENABLE_DVBC
            case E_OSD_CADTV_MANUAL_TUNING:
                MApp_ZUI_ACT_TerminateCadtvManualTuning();
                break;
        #endif

            case E_OSD_EFFECT_SETTING:
                MApp_ZUI_ACT_TerminateEffectSetting();
                break;

        #if ENABLE_S2
            case E_OSD_MENU_DISHSETUP:
                MApp_ZUI_ACT_TerminateDishSetupMenu();
                break;
        #endif

        #if ENABLE_E_POP
            case E_OSD_EPOP:
                MApp_ZUI_ACT_TerminateEpop();
                break;
        #endif
#if GAME_ENABLE
            case E_OSD_GAME_LIST:
            {
                MApp_ZUI_ACT_TerminateGameList();
            }
            break;
#endif

            default:
                ZUI_DBG_FAIL(printf("[ZUI]GBLTERM\n"));
                ABORT();
                break;

        }
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_ShutdownOSD
///  shutdown and destory current osd page. (this function will change ZUI state)
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_ACT_ShutdownOSD2(void)
{
    //2007/12/26: consider gop switching
    U8 u8PrevGopID = MApi_GOP_GWIN_GetCurrentGOP();

    ZUI_MSG(printf("[]shutdown [now=%u,%u]\n", (U8)_eActiveOSD, (U8)_eZUIState));

  #if 1//(CHAKRA3_AUTO_TEST)
    if (_eActiveOSD == E_OSD_EMPTY)
        return;
  #endif

    if (_eZUIState == E_ZUI_STATE_UNKNOW)
        return;
    if (_eZUIState == E_ZUI_STATE_STANDBY )
        return;

     #if (ENABLE_MFC_6M20)
     printf("\r\nOSD Area off");
     MDrv_Ursa_OsdWinHandler(FALSE);
     #endif

    #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
         if(MApp_ZUI_GetActiveOSD() == E_OSD_TENKEY_NUMBER)
              msAPI_ATV_SetDirectTuneFlag(FALSE);
    #endif

    if (u8PrevGopID != OSD_GOP_ID)
        MApi_GOP_GWIN_SwitchGOP(OSD_GOP_ID);

    _MApp_ZUI_ACT_AppClose();
    MApp_ZUI_ACT_TerminateOSD();

    MApp_ZUI_API_TerminateGDI(); //shutdown right now! destroy gwin and goto standby state!

  #if (DTV_USE_FBL)
    if(_eActiveOSD==E_OSD_MAIN_MENU && _eZUIState==E_ZUI_STATE_TERMINATE)
    {
        //enable de-blocking when exit Main Menu
        //for single MIU + FBL only
        if(  ( IsDTVInUse()
          #if(ENABLE_S2)
            || IsS2InUse()
          #endif
             )
          && MApi_XC_IsCurrentFrameBufferLessMode()
          )
        {
            MApi_VDEC_DisableDeblocking(FALSE); //means enable deblocking, so that VDEC would work as usual
            //printf("\n enable de-blocking \n");
        }
    }
  #endif

    MApp_ZUI_API_EmptyMessageQueue(); //clear message queue, before leave
    _eZUIState = E_ZUI_STATE_STANDBY;
    _eActiveOSD = E_OSD_EMPTY;

    if (u8PrevGopID != OSD_GOP_ID)
        MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);

}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_HandleGlobalKey
///  key preprocess handler for each osd page. (will be called before all winproc)
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       key VIRTUAL_KEY_CODE      key code
///
///  @return BOOLEAN true for handled (don't dispatch continully)
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_HandleGlobalKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //NOTE: if an new OSD page added, please add here!
    switch(_eActiveOSD)
    {
        case E_OSD_MAIN_MENU:
            return MApp_ZUI_ACT_HandleMainPageKey(key);

        case E_OSD_CHANNEL_INFO:
            return MApp_ZUI_ACT_HandleChannelInfoKey(key);

    #if (ENABLE_ATSC)
        case E_OSD_CHANNEL_INFO_ATSC:
                return MApp_ZUI_ACT_HandleChannelInfoKey_ATSC(key);
    #endif

    #if (ENABLE_DTMB || ENABLE_DVBT || ENABLE_DVBC || ENABLE_ISDBT || ENABLE_ATSC_SCAN_NEW_MODE)
        case E_OSD_DTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_HandleDtvManualTuningKey(key);
    #endif

        case E_OSD_ATV_MANUAL_TUNING:
            return MApp_ZUI_ACT_HandleAtvManualTuningKey(key);

        case E_OSD_PROGRAM_EDIT:
            return MApp_ZUI_ACT_HandleProgramEditKey(key);

        case E_OSD_AUDIO_LANGUAGE:
            return MApp_ZUI_ACT_HandleAudioLanguageKey(key);

    #if ENABLE_SUBTITLE
        case E_OSD_SUBTITLE_LANGUAGE:
            return MApp_ZUI_ACT_HandleSubtitleLanguageKey(key);
    #endif

        case E_OSD_AUTO_TUNING:
            return MApp_ZUI_ACT_HandleAutoTuningKey(key);

        case E_OSD_SCREEN_SAVER:
            return MApp_ZUI_ACT_HandleScreenSaverKey(key);

        case E_OSD_INPUT_SOURCE:
            return MApp_ZUI_ACT_HandleInputSourceKey(key);

        case E_OSD_AUDIO_VOLUME:
            return MApp_ZUI_ACT_HandleAudioVolumeKey(key);
		
		case E_OSD_KEYSTONE_ANGLE:
            return MApp_ZUI_ACT_HandleKeystoneAngleKey(key);
		
        case E_OSD_INSTALL_GUIDE:
            return MApp_ZUI_ACT_HandleInstallGuideKey(key);

    #if ENABLE_ATSC_INSTALLGUIDE
        case E_OSD_INSTALL_GUIDE_ATSC:
            return MApp_ZUI_ACT_HandleInstallGuideKey_ATSC(key);
    #endif

        case E_OSD_HOTKEY_OPTION:
            return MApp_ZUI_ACT_HandleHotkeyOptionKey(key);

        case E_OSD_MESSAGE_BOX:
            return MApp_ZUI_ACT_HandleMessageBoxKey(key);

        case E_OSD_CHANNEL_LIST:
            return MApp_ZUI_ACT_HandleChannelListKey(key);

    #if (ENABLE_OAD)
        case E_OSD_OAD:
            return MApp_ZUI_ACT_HandleOADKey(key);
    #endif

    case E_OSD_EPG:
  #if (ENABLE_ATSC)
        if (IsAtscInUse() || IsATVInUse())
        {
            return MApp_ZUI_ACT_HandleEpgKey_ATSC(key);
        }
  #endif

    #if (ENABLE_DTV_EPG)

          #if ENABLE_DVB
               return MApp_ZUI_ACT_HandleEpgKey(key);
          #endif
    #endif  //#if (ENABLE_DTV_EPG)

    break;


    #if (ENABLE_CI)
        case E_OSD_CIMMI:
            return MApp_ZUI_ACT_HandleCIMMIKey(key);
    #endif

    #if ENABLE_DMP
        case E_OSD_DMP:
            return MApp_ZUI_ACT_HandleDmpKey(key);

      #if ENABLE_DMP_MINI_MENU
        case E_OSD_DMP_MINI_MENU:
            return MApp_ZUI_ACT_HandleDmpMiniMenuKey(key);
      #endif
    #endif
    #if ENABLE_FM_RADIO
        case E_OSD_FMRADIO:
            return MApp_ZUI_ACT_HandleFMRadioKey(key);
    #endif

        case E_OSD_FACTORY_MENU:
            return MApp_ZUI_ACT_HandleFactoryMenuKey(key);

        case E_OSD_EXPERT_MENU:
            return MApp_ZUI_ACT_HandleExpertMenuKey(key);

        case E_OSD_DESIGN_MENU:
            return MApp_ZUI_ACT_HandleDesignMenuKey(key);

        case E_OSD_TENKEY_NUMBER:
            return MApp_ZUI_ACT_HandleTenKeyNumberKey(key);

    #if 0//def ENABLE_BT
        case E_OSD_BT:
            return MApp_ZUI_ACT_HandleBTKey(key);
    #endif

    #if 0//def ENABLE_KTV
        case E_OSD_KTV:
            return MApp_ZUI_ACT_HandleKTVKey(key);
    #endif

    #if ENABLE_PVR
        case E_OSD_PVR:
            return MApp_ZUI_ACT_HandlePvrKey(key);

      #if(ENABLE_PVR_BROWSER)
        case E_OSD_PVR_BROWSER:
            return MApp_ZUI_ACT_HandlePvrBrowserKey(key);
      #endif

    #endif

    #if ENABLE_DVBC
        case E_OSD_CADTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_HandleCadtvManualTuningKey(key);
    #endif

        case E_OSD_EFFECT_SETTING:
            return MApp_ZUI_ACT_HandleEffectSettingKey(key);
    #if ENABLE_S2
        case E_OSD_MENU_DISHSETUP:
            return MApp_ZUI_ACT_HandleDishSetupMenuKey(key);
    #endif
#if GAME_ENABLE
        case E_OSD_GAME_LIST:
        {
            return MApp_ZUI_ACT_HandleGameListKey(key);
        }
#endif
        default:
            ZUI_DBG_FAIL(printf("[ZUI]GBLKEY\n"));
            ABORT();
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_PostMessageFilter
///  message filter for each window proc type. (used for reduce number of message in queue)
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW WINDOW PROC!
///
///  @param [in]       u8WinProcID U8     window proc ID
///  @param [in]       msg MESSAGE_ENUM    message type
///
///  @return BOOLEAN    true for accept, false for ignore
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_PostMessageFilter(U8 u8WinProcID, MESSAGE_ENUM msg)
{
    //note: to reduce the usage of message queue, we provide a filter for each type of window proc
    //note: you MUST add a switch case if you added a new window proc

    switch (u8WinProcID)
    {
        case EN_ZUI_DEFAULTWINPROC:
            return FALSE; //ignore all notify

        case EN_ZUI_MAINFRAMEWINPROC:
            //NOTE: main frame MUST accept key down message!
            //      otherwise, all key message will lost!
            return (msg == MSG_KEYDOWN);

        //case EN_ZUI_TOPICON_WINPROC:
            //return (msg == MSG_NOTIFY_SETFOCUS||
                //msg == MSG_EFFECT_POPUP||
                //msg == MSG_EFFECT_SLIDEITEM);

        case EN_ZUI_INPUT_SOURCE_WINPROC:
            return (msg == MSG_NOTIFY_SETFOCUS ||
                msg == MSG_EFFECT_POPUP||
                msg == MSG_EFFECT_SLIDEITEM);

        //case EN_ZUI_CHANNELINFOROOT_WINPROC:
         //   return (msg == MSG_NOTIFY_SHOW);

        case EN_ZUI_ACT_MAINPAGE_DYNAMICLIST_WINPROC:
        case EN_ZUI_DYNAMICLIST_WINPROC:
            return (msg == MSG_NOTIFY_SHOW ||
                msg == MSG_NOTIFY_HIDE ||
                msg == MSG_NOTIFY_KEYDOWN ||
                msg == MSG_NOTIFY_CONTENT_CHANGED ||
                msg == MSG_USER||
                msg == (MSG_USER1/*MSG_USER+1*/));

        case EN_ZUI_CIMMIMSGBOX_WINPROC:
        case EN_ZUI_MENUCOMMONDLGROOT_WINPROC:
            return (msg == MSG_NOTIFY_SHOW ||
                msg == MSG_NOTIFY_HIDE);

        case EN_ZUI_PREDITRENAMEINPUT_WINPROC:
        case EN_ZUI_MENUPWDINPUT_WINPROC:
        case EN_ZUI_MSGBOX_PWDINPUT_WINPROC:
        case EN_ZUI_CIMMIPWDINPUT_WINPROC:
        //case EN_ZUI_CIMMIPWDINPUT_WINPROC2:
            return (
                msg == MSG_NOTIFY_HIDE ||
                msg == MSG_NOTIFY_SETFOCUS ||
                msg == MSG_NOTIFY_KILLFOCUS);
#if (ENABLE_DTV_EPG)
        case EN_ZUI_EPG_TIMER_LIST_ITEM_WINPROC:
            return (
                msg == MSG_NOTIFY_SETFOCUS);

        case EN_ZUI_EPG_TIMER_SAVE_DLG_WINPROC:
            return (
                msg==MSG_NOTIFY_SHOW );
#endif  //#if (ENABLE_DTV_EPG)

#if ENABLE_PVR
        case EN_ZUI_PVR_WINPROC:
            return (msg == MSG_NOTIFY_SETFOCUS);

        case EN_ZUI_PVR_BROWSER_WINPROC:
            return (msg == MSG_NOTIFY_SETFOCUS);
#endif

        case EN_ZUI_EFFECT_WINPROC:
        #if (ENABLE_UI_3D_PROCESS)
            if(MApp_ZUI_API_Is_UI_3D_Mode_ON())
            {
                return FALSE; //ignore all notify
            }
            else
        #endif
            {
                return (msg == MSG_EFFECT_POPUP ||
                            msg == MSG_EFFECT_SLIDEITEM ||
                            msg == MSG_EFFECT_ZOOMIN ||
                            msg == MSG_EFFECT_ZOOMOUT ||
                            msg == MSG_EFFECT_SPREADOUT ||
                            msg == MSG_EFFECT_ROLLUP);
            }

#if 0
        case EN_ZUI_EFFECT_POPUP_WINPROC:
            return (msg == MSG_EFFECT_POPUP);

        case EN_ZUI_EFFECT_SLIDEITEM_WINPROC:
            return (msg == MSG_EFFECT_SLIDEITEM);

        case EN_ZUI_EFFECT_ZOOM_WINPROC:
            return (msg == MSG_EFFECT_ZOOMIN ||
                msg == MSG_EFFECT_ZOOMOUT);

        case EN_ZUI_EFFECT_ROLL_WINPROC:
            return (msg == MSG_EFFECT_SPREADOUT ||
                msg == MSG_EFFECT_ROLLUP);

#endif



#if 0
        case EN_ZUI_DYNAMICTEXTEFFECT_WINPROC:
            return (msg == MSG_NOTIFY_SHOW ||
                    msg == MSG_EFFECT_DYNATEXT_LEFT ||
                    msg == MSG_EFFECT_DYNATEXT_RIGHT ||
                    msg == MSG_NOTIFY_KEYDOWN);
#endif

        case EN_ZUI_FLIPPAGE_WINPROC:
            return (msg == MSG_EFFECT);

        case EN_ZUI_GRID_WINPROC:
            return (msg == MSG_NOTIFY_SETFOCUS ||
                msg == MSG_NOTIFY_KEYDOWN);

        case EN_ZUI_ANIMATION_WINPROC:
            return (msg == MSG_CREATE ||
                msg == MSG_NOTIFY_HIDE||
                msg == MSG_TIMER||
                msg == MSG_PAINT);

        case EN_ZUI_KEYBOARDINPUT_WINPROC:
            return (msg == MSG_CREATE ||
                msg == MSG_NOTIFY_SETFOCUS ||
                msg == MSG_NOTIFY_SHOW ||
                msg == MSG_NOTIFY_HIDE ||
                msg == MSG_NOTIFY_KEYDOWN);
        default:
            return FALSE; //ignore all notify
    }

}

//note: avoid painting loop waste too much time
//please be attention here, if you want input some special function
#if ZUI_EXCEPTION_MULTITASK
void MApp_ZUI_ACT_Exception_MultiTask(void)
{

}
#endif

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_ExecuteWndProc
///  dispatch a window message, depent on window proc ID
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW WINDOW PROC!
///
///  @param [in]       u8WinProcID U8   window proc ID
///  @param [in]       msg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_ACT_ExecuteWndProc(U8 u8WinProcID, PMSG msg)
{
    //note: don't use function pointer,
    //      so we use a enumeration for all listed controls (included user overrided window proc)

    //note: you MUST add a switch case if you added a new window proc

    /*/WndProc = g_GUI_WindowList[focus].WindowProc;
    if (GETWNDPROC(focus))
    {
        printf("[dispmsg3]focus=%bu,msg=%bu\n", (U8)focus, pMsg->message);
        iRet = GETWNDPROC(focus)(focus, pMsg);

    }*/
    switch (u8WinProcID)
    {
        case EN_ZUI_DEFAULTWINPROC:
            return DEFAULTWINPROC(msg->hwnd, msg);

        case EN_ZUI_MAINFRAMEWINPROC:
            return MAINFRAMEWINPROC(msg->hwnd, msg);

        //case EN_ZUI_TOPICON_WINPROC:
            //return TOPICON_WINPROC(msg->hwnd, msg);

        case EN_ZUI_INPUT_SOURCE_WINPROC:
            return INPUT_SOURCE_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_MAIN_PAGE_DIRECTION_ICON_WINPROC:
            //eturn MAINMENU_TRIICON_WINPROC(msg->hwnd, msg);

        case EN_ZUI_BGTANSPARENT_WINPROC:
            return BGTRANSPARENT_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_MENUITEMBAR_WINPROC:
        //    return MENUITEMBAR_WINPROC(msg->hwnd, msg);

        case EN_ZUI_BUTTONANICLICK_WINPROC:
            return BUTTONANICLICK_WINPROC(msg->hwnd, msg);

        case EN_ZUI_BUTTONANICLICKCHILD_WINPROC:
            return BUTTONANICLICKCHILD_WINPROC(msg->hwnd, msg);

        case EN_ZUI_DYNAMICTEXT_WINPROC:
            return DYNAMICTEXT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_ANIMATION_WINPROC:
            return ANIMATION_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_DYNAMICTEXTEFFECT_WINPROC:
        //    return DYNAMICTEXTEFFECT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_DYNAMICCOLORTEXT_WINPROC:
            return DYNAMICCOLORTEXT_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_MENUROOT_WINPROC:
        //    return MENUROOT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_BALLPROGRESSBAR_WINPROC:
            return BALLPROGRESSBARCOLOR_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_BALLPROGRESSBAR_FOCUSSTYLE_WINPROC:
            //return BALLPROGRESSBAR_FOCUSSTYLE_WINPROC(msg->hwnd, msg);

        case EN_ZUI_RECTPROGRESSBAR_2_WINPROC:
            return RECTPROGRESSBAR_2_WINPROC(msg->hwnd, msg);
        #if TXTFONT_ZOOM2X
                case EN_ZUI_DYNAMICZOOM2X_WINPROC:
                    return DYNAMICZOOM2XPUNCTEXT_WINPROC(msg->hwnd,msg);
        #else
                case EN_ZUI_DYNAMICZOOM2X_WINPROC:
                    return DYNAMICEPGPUNCTEXT_WINPROC(msg->hwnd,msg);
        #endif


#if ENABLE_DMP
        case EN_ZUI_BUTTONCLICK_WINPROC:
            return BUTTONCLICK_WINPROC(msg->hwnd, msg);
        //case EN_ZUI_DMP_FILE_SELECT_THUMBNAIL_WINPROC:
        //    return DMP_FILE_SELECT_THUMBNAIL_WINPROC(msg->hwnd, msg);
        //case EN_ZUI_DMP_BGM_FILE_SELECT_THUMBNAIL_WINPROC:
        //    return DMP_BGM_FILE_SELECT_THUMBNAIL_WINPROC(msg->hwnd, msg);
        case EN_ZUI_DMP_PROGRESS_WINPROC:
            return DMP_PROGRESS_WINPROC(msg->hwnd, msg);
        case EN_ZUI_PERCENTPROGRESSBAR_WINPROC:
            return PERCENTPROGRESSBAR_WINPROC(msg->hwnd, msg);
        case EN_ZUI_DMP_PLAY_STATUS_WINPROC:
            return DMP_PLAY_STATUS_WINPROC(msg->hwnd, msg);
        case EN_ZUI_DMP_ALERT_WINPROC:
            return DMP_ALERT_WINPROC(msg->hwnd, msg);
        case EN_ZUI_TEXTVIEWER_WINPROC:
            // TODO: fix me, need MApp_Text_CurPageReload?
            #if (ENABLE_MPLAYER_TEXT)
            MApp_Text_CurPageReload();
            #endif
            return TEXTVIEWER_WINPROC(msg->hwnd, msg);
        case EN_ZUI_PREVIEW_WINPROC:
            return DMP_PREVIEW_WINPROC(msg->hwnd, msg);
        case EN_ZUI_DMP_VOLUME_WINPROC:
            return DMP_VOLUME_WINPROC(msg->hwnd, msg);
		case EN_ZUI_DMP_KEYSTONE_WINPROC:     //xzm @20171228 for keystone
			return DMP_KEYSTONE_WINPROC(msg->hwnd, msg);
        case EN_ZUI_DMP_EQ_PLAY_WINPROC:
            return DMP_EQ_PLAY_WINPROC(msg->hwnd, msg);
        case EN_ZUI_DMP_MARQUEE_WINPROC:
            return DMP_MARQUEE_WINPROC(msg->hwnd,msg);
        case EN_ZUI_DMP_MOVIERESUME_WINPROC:
            return DMP_MOVIERESUME_WINPROC(msg->hwnd, msg);
        // EN_ZUI_DMP_RESUMESTOP_WINPROC:
         //   return DMP_RESUMESTOP_WINPROC(msg->hwnd, msg);
    case EN_ZUI_DMP_UART_WINPROC:
            return DMP_UART_WINPROC(msg->hwnd, msg);
#endif

        //case EN_ZUI_MENUPICTUREPAGE1_WINPROC:
            //return MENUPICTUREPAGE1_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_CHANNELINFOROOT_WINPROC:
        //    return CHANNELINFOROOT_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_INPUTSOURCELIST_WINPROC:
        //    return INPUTSOURCELIST_WINPROC(msg->hwnd, msg);
#if (ENABLE_DTMB || ENABLE_DVBT || ENABLE_DVBC || ENABLE_ISDBT || ENABLE_ATSC_SCAN_NEW_MODE)
        case EN_ZUI_DTVMANUALTUNING_WINPROC:
            return DTVMANUALTUNING_WINPROC(msg->hwnd, msg);
    #endif

    #if ENABLE_S2
        case EN_ZUI_DISHSETUP_WINPROC:
            return DISHSETUP_WINPROC(msg->hwnd, msg);
    #endif

    #if ENABLE_DVBC
        case EN_ZUI_CADTVMANUALTUNING_WINPROC:
            return CADTVMANUALTUNING_WINPROC(msg->hwnd, msg);
    #endif

        case EN_ZUI_ATVMANUALTUNING_WINPROC:
            return ATVMANUALTUNING_WINPROC(msg->hwnd, msg);

        case EN_ZUI_SCREENSAVER_WINPROC:
            return SCREENSAVER_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_AUDIOVOLUME_WINPROC:
        //    return AUDIOVOLUME_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_PROGRAMEDITROOT_WINPROC:
        //    return PROGRAMEDITROOT_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_AUDIOLANGUAGELIST_WINPROC:
        //    return AUDIOLANGUAGELIST_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_SUBTITLELANGUAGELIST_WINPROC:
        //    return SUBTITLELANGUAGELIST_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_HOTKEYOPTION_WINPROC:
        //    return HOTKEYOPTION_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_MESSAGEBOX_WINPROC:
        //    return MESSAGEBOX_WINPROC(msg->hwnd, msg);

        case EN_ZUI_DYNAMICLIST_WINPROC:
            return DYNAMICLIST_WINPROC(msg->hwnd, msg);

        case EN_ZUI_ACT_MAINPAGE_DYNAMICLIST_WINPROC:
            return MApp_ZUI_ACT_Mainpage_DynamicListWinProc(msg->hwnd, msg);

        //case EN_ZUI_INSTALLGUIDEROOT_WINPROC:
        //    return INSTALLGUIDEROOT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_MENUCOMMONDLGROOT_WINPROC:
            return MENUCOMMONDLGROOT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_MENUPWDINPUT_WINPROC:
            return MENUPWDINPUT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_MSGBOX_PWDINPUT_WINPROC:
            return MSGBOXPWDINPUT_WINPROC(msg->hwnd, msg);
#if (ENABLE_CI)
        case EN_ZUI_CIMMIPWDINPUT_WINPROC:
            return CIMMIPWDINPUT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_CIMMIPWDINPUT_WINPROC2:
            return CIMMIPWDINPUT_WINPROC2(msg->hwnd, msg);
#endif
        //case EN_ZUI_CHANNELLISTROOT_WINPROC:
        //    return CHANNELLISTROOT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_DYNAMICBITMAP_WINPROC:
            return DYNAMICBITMAP_WINPROC(msg->hwnd, msg);

        case EN_ZUI_PREDITRENAMEINPUT_WINPROC:
            return PREDITRENAMEINPUT_WINPROC(msg->hwnd, msg);
    #if 0//ENABLE_S2
        case EN_ZUI_USBRENAMEINPUT_WINPROC:
            return USBRENAMEINPUT_WINPROC(msg->hwnd, msg);
    #endif
        case EN_ZUI_KEYBOARDINPUT_WINPROC:
            return KEYBOARDINPUT_WINPROC(msg->hwnd, msg);

        //case EN_ZUI_EPGROOT_WINPROC:
        //    return EPGROOT_WINPROC(msg->hwnd, msg);
#if (ENABLE_DTV_EPG)
  //      case EN_ZUI_EPGSERVICEBAR_WINPROC:
  //          return EPGSERVICEBAR_WINPROC(msg->hwnd, msg);
        case EN_ZUI_EPGPROGRAMMEGUIDE_TITLE_WINPROC:
            return EPGPROGRAMMEGUIDE_TITLE_WINPROC(msg->hwnd, msg);
        case EN_ZUI_EPGPROGRAMMEGUIDE_TIMEITEM_WINPROC:
            return EPGPROGRAMMEGUIDE_TIMEITEM_WINPROC(msg->hwnd, msg);
        case EN_ZUI_EPGTIMEITEMEVENT_WINPROC:
            return EPGTIMEITEMEVENT_WINPROC(msg->hwnd, msg);
        case EN_ZUI_EPGPROGRAMMEGUIDE_CHANNELITEM_WINPROC:
            return EPGPROGRAMMEGUIDE_CHANNELITEM_WINPROC(msg->hwnd, msg);
        case EN_ZUI_EPGCHANNELITEMEVENT_WINPROC:
            return EPGCHANNELITEMEVENT_WINPROC(msg->hwnd, msg);
//        case EN_ZUI_EPGTIMEPANE_WINPROC:
 //           return EPGTIMEPANE_WINPROC(msg->hwnd, msg);

        case EN_ZUI_EPGUPDATEALLTIMEITEM_WINPROC:
            return EPG_UPDATEALLTIMEITEM_WINPROC(msg->hwnd, msg);
#endif  //#if (ENABLE_DTV_EPG)
        //case EN_ZUI_DYNAMICPUNCTEXT_WINPROC:
        //    return DYNAMICPUNCTEXT_WINPROC(msg->hwnd, msg);

        case EN_ZUI_DYNAMICEPGPUNCTEXT_WINPROC:
            return DYNAMICEPGPUNCTEXT_WINPROC(msg->hwnd, msg);

#if (UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
        case EN_ZUI_DYNAMIC_SCROL_EPGPUNCTEXT_WINPROC:
            return DYNAMIC_SCROL_PUNCTEXT_WINPROC(msg->hwnd, msg);
#endif
#if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)
    case EN_ZUI_EWS_SLIDE_SCROL_WINPROC:
        return EWS_SLIDE_SCROL_WINPROC(msg->hwnd, msg);

#endif


        case EN_ZUI_AUTOCLOSE_WINPROC:
            return AUTOCLOSE_WINPROC(msg->hwnd, msg);
#if (ENABLE_CI)
        case EN_ZUI_CIMMIMSGBOX_WINPROC:
            return CIMMIMSGBOX_WINPROC(msg->hwnd, msg);

        case EN_ZUI_CIMMI_WINPROC:
            return CIMMI_WINPROC(msg->hwnd, msg);
#endif
#if (ENABLE_CI_PLUS)
        case EN_ZUI_OPMENUMSGBOX_WINPROC:
            return OPMENUMSGBOX_WINPROC(msg->hwnd, msg);
#endif
        case EN_ZUI_MSGBOXTEXTPANE_WINPROC:
            return MSGBOXTEXTPANE_WINPROC(msg->hwnd, msg);

        case EN_ZUI_AUTOTUNINGSKIPATV_WINPROC:
            return AUTOTUNINGSKIPATV_WINPROC(msg->hwnd, msg);

        case EN_ZUI_AUTOTUNINGSKIPDTV_WINPROC:
            return AUTOTUNINGSKIPDTV_WINPROC(msg->hwnd, msg);

#if (ENABLE_DTV_EPG)
        case EN_ZUI_EPG_TIMER_LIST_ITEM_WINPROC:
            return EPG_TIMER_LIST_ITEM_WINPROC(msg->hwnd, msg);

        case EN_ZUI_EPG_TIMER_SAVE_DLG_WINPROC:
            return EPG_TIMER_SAVE_DLG_WINPROC(msg->hwnd, msg);
#endif  //#if (ENABLE_DTV_EPG)

#if 0//def ENABLE_BT
        case EN_ZUI_BTTOP_WINPROC:
            return MApp_ZUI_ACT_BTTopWinProc(msg->hwnd, msg);
        case EN_ZUI_BTLINKPHOTO_WINPROC:
            return MApp_ZUI_ACT_BTLinkPhotoWinProc(msg->hwnd, msg);
        case EN_ZUI_BT_DESCRIPTION_WINPROC:
            return MApp_ZUI_ACT_BTDescriptionWinProc(msg->hwnd, msg);
#endif

#if 0//def ENABLE_KTV
        case EN_ZUI_KTV_WINPROC:
            return MApp_ZUI_ACT_KTVWinProc(msg->hwnd, msg);
#endif

#if ENABLE_PVR
        case EN_ZUI_PVR_WINPROC:
            return MApp_ZUI_ACT_PvrWinProc(msg->hwnd, msg);

    #if(ENABLE_PVR_BROWSER)
        case EN_ZUI_PVR_BROWSER_WINPROC:
            return MApp_ZUI_ACT_PvrBrowserWinProc(msg->hwnd, msg);
    #endif

    #if 0 //fix pvr
        case EN_ZUI_PVR_BALLPROGRESSBAR_WINPROC:
            return MApp_ZUI_CTL_PvrBallProgressBarWinProc(msg->hwnd, msg);

        case EN_ZUI_PVR_TWOBALLPROGRESSBAR_WINPROC:
            return MApp_ZUI_CTL_PvrTwoBallProgressBarWinProc(msg->hwnd, msg);
    #endif
#endif

        case EN_ZUI_EFFECT_WINPROC:
            return EFFECT_WINPROC(msg->hwnd, msg);

#if 0
        case EN_ZUI_EFFECT_POPUP_WINPROC:
            return EFFECTPOPUP_WINPROC(msg->hwnd, msg);

        case EN_ZUI_EFFECT_SLIDEITEM_WINPROC:
            return EFFECTSLIDEITEM_WINPROC(msg->hwnd, msg);

        case EN_ZUI_EFFECT_ZOOM_WINPROC:
            return EFFECTZOOM_WINPROC(msg->hwnd, msg);

        case EN_ZUI_EFFECT_ROLL_WINPROC:
            return EFFECTROLL_WINPROC(msg->hwnd, msg);
#endif

/*
        case EN_ZUI_MOTIONTRANS_ICON_WINPROC:
            return MApp_ZUI_CTL_MotionTrans_Icon_WinProc(msg->hwnd, msg);

        case EN_ZUI_MOTIONTRANS_WINPROC:
            return MApp_ZUI_CTL_MotionTransWinProc(msg->hwnd, msg);

        case EN_ZUI_FAKE3D_ICON_WINPROC:
            return MApp_ZUI_CTL_Fake3D_Icon_WinProc(msg->hwnd, msg);

        case EN_ZUI_FAKE3D_WINPROC:
            return MApp_ZUI_CTL_Fake3D_WinProc(msg->hwnd, msg);
*/



        case EN_ZUI_FLIPPAGE_WINPROC:
            return FLIPPAGE_WINPROC(msg->hwnd, msg);

        case EN_ZUI_GRID_WINPROC:
            return MApp_ZUI_CTL_GridWinProc(msg->hwnd, msg);

        case EN_ZUI_INSTALL_GUIDE_WINPROC:
            return INSTALL_GUIDE_WINPROC(msg->hwnd, msg);
#if ENABLE_ATSC
        case EN_ZUI_INSTALL_GUIDE_WINPROC_ATSC:
            return INSTALL_GUIDE_WINPROC_ATSC(msg->hwnd, msg);
#endif
        //case EN_ZUI_UPDATE_CEC_DEVICE_WINPROC:
        //    return UPDATE_CEC_DEVICE_WINPROC(msg->hwnd, msg);
#if ENABLE_WAIT_CEC_READY
        case EN_ZUI_WAIT_CEC_POLLING_WINPROC:
            return WAIT_CEC_POLLING_WINPROC(msg->hwnd, msg);
#endif
#if (ENABLE_E_POP)
        case EN_ZUI_EPOP_WINPROC:
            return MApp_ZUI_ACT_EpopWinProc(msg->hwnd, msg);
#endif
        default:
            ZUI_DBG_FAIL(printf("[ZUI]GBLWPROC\n"));
            ABORT();
            return 0;
    }

}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_ExecuteWndAction
///  execute a specific action. (this will dispatch by osd page)
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       act U16       action ID
///
///  @return BOOLEAN    true for accept, false for ignore
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_ExecuteWndAction(U16 act)
{
    if (_eActiveOSD == E_OSD_EMPTY)
    {
        return FALSE;
    }

    //global action....NOTE: don't write special case here!!
    switch (act)
    {
        case EN_EXE_NAV_KEY_UP:
            MApp_ZUI_API_SetFocusByNav(MApp_ZUI_API_GetFocus(), NAV_UP);
            return TRUE;

        case EN_EXE_NAV_KEY_DOWN:
            MApp_ZUI_API_SetFocusByNav(MApp_ZUI_API_GetFocus(), NAV_DOWN);
            return TRUE;

        case EN_EXE_NAV_KEY_LEFT:
            MApp_ZUI_API_SetFocusByNav(MApp_ZUI_API_GetFocus(), NAV_LEFT);
            return TRUE;

        case EN_EXE_NAV_KEY_RIGHT:
            MApp_ZUI_API_SetFocusByNav(MApp_ZUI_API_GetFocus(), NAV_RIGHT);
            return TRUE;


        case EN_EXE_NOTIFY_PARENT_KEY_SELECT:
            MApp_ZUI_API_PostMessage(
                MApp_ZUI_API_GetParent(MApp_ZUI_API_GetFocus()),
                MSG_NOTIFY_KEYDOWN, VK_SELECT);
            return TRUE;
        case EN_EXE_NOTIFY_PARENT_KEY_UP:
            MApp_ZUI_API_PostMessage(
                MApp_ZUI_API_GetParent(MApp_ZUI_API_GetFocus()),
                MSG_NOTIFY_KEYDOWN, VK_UP);
            return TRUE;

        case EN_EXE_NOTIFY_PARENT_KEY_DOWN:
            MApp_ZUI_API_PostMessage(
                MApp_ZUI_API_GetParent(MApp_ZUI_API_GetFocus()),
                MSG_NOTIFY_KEYDOWN, VK_DOWN);
            return TRUE;

        case EN_EXE_NOTIFY_PARENT_KEY_LEFT:
            MApp_ZUI_API_PostMessage(
                MApp_ZUI_API_GetParent(MApp_ZUI_API_GetFocus()),
                MSG_NOTIFY_KEYDOWN, VK_LEFT);
            return TRUE;

        case EN_EXE_NOTIFY_PARENT_KEY_RIGHT:
            MApp_ZUI_API_PostMessage(
                MApp_ZUI_API_GetParent(MApp_ZUI_API_GetFocus()),
                MSG_NOTIFY_KEYDOWN, VK_RIGHT);
            return TRUE;

        case EN_EXE_REPAINT_ALL:
            MApp_ZUI_API_InvalidateRect(NULL);
            return TRUE;

        default:
            break;

    }

    //NOTE: if an new OSD page added, please add here!
    switch(_eActiveOSD)
    {
        case E_OSD_MAIN_MENU:
            return MApp_ZUI_ACT_ExecuteMainMenuAction(act);

        case E_OSD_AUTO_TUNING:
            return MApp_ZUI_ACT_ExecuteAutoTuningAction(act);

        case E_OSD_CHANNEL_INFO:
            return MApp_ZUI_ACT_ExecuteChannelInfoAction(act);

#if (ENABLE_ATSC)
        case E_OSD_CHANNEL_INFO_ATSC:
            return MApp_ZUI_ACT_ExecuteChannelInfoAction_ATSC(act);
#endif

        case E_OSD_INPUT_SOURCE:
            return MApp_ZUI_ACT_ExecuteInputSourceAction(act);

        case E_OSD_AUDIO_VOLUME:
            return MApp_ZUI_ACT_ExecuteAudioVolumeAction(act);
		
		case E_OSD_KEYSTONE_ANGLE:
            return MApp_ZUI_ACT_ExecuteKeystoneAngleAction(act);
		
        case E_OSD_SCREEN_SAVER:
            return MApp_ZUI_ACT_ExecuteScreenSaverAction(act);

        case E_OSD_AUDIO_LANGUAGE:
            return MApp_ZUI_ACT_ExecuteAudioLanguageAction(act);

        #if ENABLE_SUBTITLE
        case E_OSD_SUBTITLE_LANGUAGE:
            return MApp_ZUI_ACT_ExecuteSubtitleLanguageAction(act);
        #endif
#if (ENABLE_DTMB || ENABLE_DVBT || ENABLE_DVBC || ENABLE_ISDBT || ENABLE_ATSC_SCAN_NEW_MODE)
        case E_OSD_DTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_ExecuteDtvManualTuningAction(act);
#endif
        case E_OSD_ATV_MANUAL_TUNING:
            return MApp_ZUI_ACT_ExecuteAtvManualTuningAction(act);

        case E_OSD_PROGRAM_EDIT:
            return MApp_ZUI_ACT_ExecuteProgramEditAction(act);

        case E_OSD_HOTKEY_OPTION:
            return MApp_ZUI_ACT_ExecuteHotkeyOptionAction(act);

        case E_OSD_MESSAGE_BOX:
            return MApp_ZUI_ACT_ExecuteMessageBoxAction(act);

        case E_OSD_INSTALL_GUIDE:
            return MApp_ZUI_ACT_ExecuteInstallGuideAction(act);

#if ENABLE_ATSC_INSTALLGUIDE
        case E_OSD_INSTALL_GUIDE_ATSC:
            return MApp_ZUI_ACT_ExecuteInstallGuideAction_ATSC(act);
#endif

        case E_OSD_CHANNEL_LIST:
            return MApp_ZUI_ACT_ExecuteChannelListAction(act);
#if (ENABLE_OAD)
        case E_OSD_OAD:
            return MApp_ZUI_ACT_ExecuteOADAction(act);
#endif


        case E_OSD_EPG:
            #if (ENABLE_ATSC)
            if (IsAtscInUse() || IsATVInUse())
            {
                return MApp_ZUI_ACT_ExecuteEpgAction_ATSC(act);
            }
            #endif

#if (ENABLE_DTV_EPG)

            #if ENABLE_DVB
            return MApp_ZUI_ACT_ExecuteEpgAction(act);
            #endif
#endif  //#if (ENABLE_DTV_EPG)
        break;

#if (ENABLE_CI)
        case E_OSD_CIMMI:
            return MApp_ZUI_ACT_ExecuteCIMMIAction(act);
#endif
#if ENABLE_DMP
        case E_OSD_DMP:
            return MApp_ZUI_ACT_ExecuteDmpAction(act);

    #if ENABLE_DMP_MINI_MENU
        case E_OSD_DMP_MINI_MENU:
            return MApp_ZUI_ACT_ExecuteDmpMiniMenuAction(act);
    #endif
#endif
#if ENABLE_FM_RADIO
        case E_OSD_FMRADIO:
            return MApp_ZUI_ACT_ExecuteFMRadioAction(act);
#endif

        case E_OSD_FACTORY_MENU:
            return MApp_ZUI_ACT_ExecuteFactoryMenuAction(act);

        case E_OSD_EXPERT_MENU:
            return MApp_ZUI_ACT_ExecuteExpertMenuAction(act);

        case E_OSD_DESIGN_MENU:
            return MApp_ZUI_ACT_ExecuteDesignMenuAction(act);

        case E_OSD_TENKEY_NUMBER:
            return MApp_ZUI_ACT_ExecuteTenKeyNumberAction(act);

    #if 0//def ENABLE_BT
        case E_OSD_BT:
            return MApp_ZUI_ACT_ExecuteBTAction(act);
    #endif

    #if 0//def ENABLE_KTV
        case E_OSD_KTV:
            return MApp_ZUI_ACT_ExecuteKTVAction(act);
    #endif

    #if ENABLE_PVR
        case E_OSD_PVR:
            return MApp_ZUI_ACT_ExecutePvrAction(act);

      #if(ENABLE_PVR_BROWSER)
        case E_OSD_PVR_BROWSER:
            return MApp_ZUI_ACT_ExecutePvrBrowserAction(act);
      #endif
    #endif

    #if ENABLE_DVBC
        case E_OSD_CADTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_ExecuteCadtvManualTuningAction(act);
    #endif

        case E_OSD_EFFECT_SETTING:
            return MApp_ZUI_ACT_ExecuteEffectSettingAction(act);

    #if ENABLE_S2
        case E_OSD_MENU_DISHSETUP:
            return MApp_ZUI_ACT_ExecuteDishSetupMenuAction(act);
    #endif

    #if ENABLE_E_POP
        case E_OSD_EPOP:
            return MApp_ZUI_ACT_ExecuteEpopAction(act);
    #endif
#if GAME_ENABLE
        case E_OSD_GAME_LIST:
        {
            return MApp_ZUI_ACT_ExecuteGameListAction(act);
        }
#endif

        default:
          #if 0
            ZUI_DBG_FAIL(printf("[ZUI]GBLACT=%bu,%bu\n", _eActiveOSD, act));
          #else // Modified by coverity_0450
            ZUI_DBG_FAIL(printf("[ZUI]GBLACT=%d,%d\n", (U8)_eActiveOSD, act));
          #endif
            ABORT();
            break;

    }

    return FALSE; //false for continue passing key event....
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_GetDynamicText
///  dynamic text content provider for "dynamic text" control
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return LPTSTR    string content, return 0 if want to display empty string
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_ACT_GetDynamicText(HWND hwnd)
{
    //NOTE: if an new OSD page added, please add here!
    switch(_eActiveOSD)
    {
        case E_OSD_MAIN_MENU:
            return MApp_ZUI_ACT_GetMainMenuDynamicText(hwnd);

        case E_OSD_AUTO_TUNING:
            return MApp_ZUI_ACT_GetAutoTuningDynamicText(hwnd);

        case E_OSD_CHANNEL_INFO:
            return MApp_ZUI_ACT_GetChannelInfoDynamicText(hwnd);

#if (ENABLE_ATSC)
        case E_OSD_CHANNEL_INFO_ATSC:
            return MApp_ZUI_ACT_GetChannelInfoDynamicText_ATSC(hwnd);
#endif

        case E_OSD_INPUT_SOURCE:
            return MApp_ZUI_ACT_GetInputSourceDynamicText(hwnd);

        case E_OSD_SCREEN_SAVER:
            return MApp_ZUI_ACT_GetScreenSaverDynamicText(hwnd);

        case E_OSD_AUDIO_VOLUME:
            return MApp_ZUI_ACT_GetAudioVolumeDynamicText(hwnd);
		
		case E_OSD_KEYSTONE_ANGLE:
            return MApp_ZUI_ACT_GetKeystoneAngleDynamicText(hwnd);
		
        case E_OSD_AUDIO_LANGUAGE:
            return MApp_ZUI_ACT_GetAudioLanguageDynamicText(hwnd);

       #if ENABLE_SUBTITLE
        case E_OSD_SUBTITLE_LANGUAGE:
            return MApp_ZUI_ACT_GetSubtitleLanguageDynamicText(hwnd);
       #endif
#if (ENABLE_DTMB || ENABLE_DVBT || ENABLE_DVBC || ENABLE_ISDBT || ENABLE_ATSC_SCAN_NEW_MODE)
        case E_OSD_DTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_GetDtvManualTuningDynamicText(hwnd);
#endif
        case E_OSD_ATV_MANUAL_TUNING:
            return MApp_ZUI_ACT_GetAtvManualTuningDynamicText(hwnd);

        case E_OSD_PROGRAM_EDIT:
            return MApp_ZUI_ACT_GetProgramEditDynamicText(hwnd);

        case E_OSD_HOTKEY_OPTION:
            return MApp_ZUI_ACT_GetHotkeyOptionDynamicText(hwnd);

        case E_OSD_MESSAGE_BOX:
            return MApp_ZUI_ACT_GetMessageBoxDynamicText(hwnd);

        case E_OSD_INSTALL_GUIDE:
            return MApp_ZUI_ACT_GetInstallGuideDynamicText(hwnd);

#if ENABLE_ATSC_INSTALLGUIDE
        case E_OSD_INSTALL_GUIDE_ATSC:
            return MApp_ZUI_ACT_GetInstallGuideDynamicText_ATSC(hwnd);
#endif

        case E_OSD_CHANNEL_LIST:
            return MApp_ZUI_ACT_GetChannelListDynamicText(hwnd);
#if (ENABLE_OAD)
        case E_OSD_OAD:
            return MApp_ZUI_ACT_GetOADDynamicText(hwnd);
#endif


        case E_OSD_EPG:
          #if (ENABLE_ATSC)
            if (IsAtscInUse() || IsATVInUse())
            {
                return MApp_ZUI_ACT_GetEpgDynamicText_ATSC(hwnd);
            }
          #endif

        #if (ENABLE_DTV_EPG)
          #if (ENABLE_DVB)
            return MApp_ZUI_ACT_GetEpgDynamicText(hwnd);
          #endif
        #endif  //#if (ENABLE_DTV_EPG)
        break;


#if (ENABLE_CI)
        case E_OSD_CIMMI:
            return MApp_ZUI_ACT_GetCIMMIDynamicText(hwnd);
#endif
#if ENABLE_DMP
        case E_OSD_DMP:
            return MApp_ZUI_ACT_GetDmpDynamicText(hwnd);

    #if ENABLE_DMP_MINI_MENU
        case E_OSD_DMP_MINI_MENU:
            return MApp_ZUI_ACT_GetDmpMiniMenuDynamicText(hwnd);
    #endif
#endif
#if ENABLE_FM_RADIO
        case E_OSD_FMRADIO:
            return MApp_ZUI_ACT_GetFMRadioDynamicText(hwnd);
#endif
        case E_OSD_FACTORY_MENU:
            return MApp_ZUI_ACT_GetFactoryMenuDynamicText(hwnd);

        case E_OSD_EXPERT_MENU:
            return MApp_ZUI_ACT_GetExpertMenuDynamicText(hwnd);

        case E_OSD_DESIGN_MENU:
            return MApp_ZUI_ACT_GetDesignMenuDynamicText(hwnd);

        case E_OSD_TENKEY_NUMBER:
            return MApp_ZUI_ACT_GetTenKeyNumberDynamicText(hwnd);

    #if 0//def ENABLE_BT
        case E_OSD_BT:
            return MApp_ZUI_ACT_GetBTDynamicText(hwnd);
    #endif

    #if 0//def ENABLE_KTV
        case E_OSD_KTV:
            return MApp_ZUI_ACT_GetKTVDynamicText(hwnd);
    #endif

    #if ENABLE_PVR
        case E_OSD_PVR:
            return MApp_ZUI_ACT_GetPvrDynamicText(hwnd);

      #if(ENABLE_PVR_BROWSER)
        case E_OSD_PVR_BROWSER:
            return MApp_ZUI_ACT_GetPvrBrowserDynamicText(hwnd);
      #endif
    #endif

    #if ENABLE_DVBC
        case E_OSD_CADTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_GetCadtvManualTuningDynamicText(hwnd);
    #endif

        case E_OSD_EFFECT_SETTING:
            return MApp_ZUI_ACT_GetEffectSettingDynamicText(hwnd);

    #if ENABLE_S2
        case E_OSD_MENU_DISHSETUP:
            return MApp_ZUI_ACT_GetDishSetupMenuDynamicText(hwnd);
    #endif

    #if ENABLE_E_POP
        case E_OSD_EPOP:
            return MApp_ZUI_ACT_GetEpopDynamicText(hwnd);
    #endif

#if GAME_ENABLE
        case E_OSD_GAME_LIST:
            return MApp_ZUI_ACT_GetGameListDynamicText(hwnd);
#endif

        default:
            ZUI_DBG_FAIL(printf("[ZUI]GBLDTEXT\n"));
            ABORT();
            break;
    }

    return 0; //false for empty string
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_GetDynamicBitmap
///  dynamic bitmap content provider for "dynamic bitmap" control
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       hwnd HWND     window handle we are processing
///  @param [in]       type DRAWSTYLE_TYPE     drawing type (normal/focus/disabled)
///
///  @return U16      bitmap index, return 0xFFFF if want to display empty bitmap
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
U16 MApp_ZUI_ACT_GetDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE type)
{
    //NOTE: if an new OSD page added, please add here!
    switch(_eActiveOSD)
    {
        case E_OSD_MAIN_MENU:
            return MApp_ZUI_ACT_GetMainMenuDynamicBitmap(hwnd, type);
        case E_OSD_CHANNEL_LIST:
            return MApp_ZUI_ACT_GetChannelListDynamicBitmap(hwnd, type);

        case E_OSD_PROGRAM_EDIT:
            return MApp_ZUI_ACT_GetProgramEditDynamicBitmap(hwnd, type);

        case E_OSD_AUDIO_LANGUAGE:
            return MApp_ZUI_ACT_GetAudioLanguageDynamicBitmap(hwnd, type);
		
		case E_OSD_KEYSTONE_ANGLE:
            return MApp_ZUI_ACT_GetKeystoneAngleDynamicBitmap(hwnd);
#if ENABLE_DMP
        case E_OSD_DMP:
            return MApp_ZUI_ACT_GetDmpDynamicBitmap(hwnd, type);

    #if ENABLE_DMP_MINI_MENU
        case E_OSD_DMP_MINI_MENU:
            return MApp_ZUI_ACT_GetDmpMiniMenuDynamicBitmap(hwnd, type);
    #endif
#endif

#if ENABLE_FM_RADIO
        case E_OSD_FMRADIO:
            return MApp_ZUI_ACT_GetFMRadioDynamicBitmap(hwnd, type);
#endif

#if 0//def ENABLE_BT
        case E_OSD_BT:
            return MApp_ZUI_ACT_GetBTDynamicBitmap(hwnd, type);
#endif
#if 0//def ENABLE_KTV
        case E_OSD_KTV:
            return MApp_ZUI_ACT_GetKTVDynamicBitmap(hwnd, type);
#endif

#if ENABLE_PVR_BROWSER
        case E_OSD_PVR_BROWSER:
            return MApp_ZUI_ACT_GetPvrBrowserDynamicBitmap(hwnd, type);
#endif
        case E_OSD_CHANNEL_INFO:
            return MApp_ZUI_ACT_GetChannelInfoDynamicBitmap(hwnd, type);

#if(ENABLE_ATSC)
        case E_OSD_CHANNEL_INFO_ATSC:
            return 0xFFFF;
#endif

#if (ENABLE_DTV_EPG)
        case E_OSD_EPG:
            return MApp_ZUI_ACT_GetEpgDynamicBitmap(hwnd, type);
#endif

        case E_OSD_INPUT_SOURCE:
            return MApp_ZUI_ACT_GetInputSourceDynamicBitmap(hwnd, type);

    #if ENABLE_S2
        case E_OSD_MENU_DISHSETUP:
            return MApp_ZUI_ACT_GetDishSetupMenuDynamicBmp(hwnd);
    #endif

#if (ENABLE_EWS)
        case E_OSD_MESSAGE_BOX:
            return MApp_ZUI_ACT_GetMsgBoxDynamicBitmap(hwnd, type);
#endif
        default:
            ZUI_DBG_FAIL(printf("[ZUI]GBLDBMP\n"));
            ABORT();
            break;
    }
    return 0xFFFF; //for empty bitmap

}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_GetDynamicValue
///  integer number provider for progress bar/checkbox/radio button controls
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return S16     integer value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S16 MApp_ZUI_ACT_GetDynamicValue(HWND hwnd)
{

    //NOTE: if an new OSD page added, please add here!
    switch(_eActiveOSD)
    {
        case E_OSD_MAIN_MENU:
            return MApp_ZUI_ACT_GetMainMenuDynamicValue(hwnd);

        case E_OSD_AUTO_TUNING:
            return MApp_ZUI_ACT_GetAutoTuningDynamicValue(hwnd);

        case E_OSD_CHANNEL_INFO:
            return MApp_ZUI_ACT_GetChannelInfoDynamicValue(hwnd);
    #if ENABLE_ATSC
        case E_OSD_CHANNEL_INFO_ATSC:
            return 0;
    #endif

        case E_OSD_AUDIO_VOLUME:
            return MApp_ZUI_ACT_GetAudioVolumeDynamicValue(hwnd);
		
		case E_OSD_KEYSTONE_ANGLE:    //xzm @20171228 keystone
            return MApp_ZUI_ACT_GetKeystoneAngleDynamicValue(hwnd);
    #if (ENABLE_DTMB || ENABLE_DVBT || ENABLE_DVBC || ENABLE_ISDBT || ENABLE_ATSC_SCAN_NEW_MODE)
        case E_OSD_DTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_GetDtvManualTuningDynamicValue(hwnd);
      #if ENABLE_DVBC
        case E_OSD_CADTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_GetCADtvManualTuningDynamicValue(hwnd);
      #endif
    #endif

    #if (ENABLE_DTV_EPG)
        //case E_OSD_EPG:
            //return MApp_ZUI_ACT_GetEpgDynamicValue(hwnd);
    #endif  //#if (ENABLE_DTV_EPG)

        //case E_OSD_HOTKEY_OPTION:
            //return MApp_ZUI_ACT_GetHotkeyOptionDynamicValue(hwnd);

    #if ENABLE_DMP
        case E_OSD_DMP:
            return MApp_ZUI_ACT_GetDmpDynamicValue(hwnd);
    #endif

    #if ENABLE_FM_RADIO
        case E_OSD_FMRADIO:
            return MApp_ZUI_ACT_GetFMRadioDynamicValue(hwnd);
    #endif

    #if 0//def ENABLE_KTV
        case E_OSD_KTV:
            return MApp_ZUI_ACT_GetKTVDynamicValue(hwnd);
    #endif

    #if ENABLE_PVR
        case E_OSD_PVR:
            return MApp_ZUI_ACT_GetPvrDynamicValue(hwnd);

      #if ENABLE_PVR_BROWSER
        case E_OSD_PVR_BROWSER:
            return MApp_ZUI_ACT_GetPvrBrowserDynamicValue(hwnd);
      #endif
    #endif

    #if ENABLE_S2
        case E_OSD_MENU_DISHSETUP:
            return MApp_ZUI_ACT_GetDynamicValue_DishSetupMenu(hwnd);
    #endif

    #if ENABLE_ATSC_INSTALLGUIDE
        case E_OSD_INSTALL_GUIDE_ATSC:
            return MApp_ZUI_ACT_GetInstallGuideDynamicValue_ATSC(hwnd);
    #endif

        default:
            ZUI_DBG_FAIL(printf("[ZUI]GBLDVALUE\n"));
            ABORT();
            break;
    }

    return 0; //false for empty string
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_GetDynamicValue_2
///  2nd integer number provider for dual progress bar
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return S16     integer value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S16 MApp_ZUI_ACT_GetDynamicValue_2(HWND hwnd)
{
#if !(ENABLE_PVR)
    UNUSED(hwnd);
#endif

    switch(_eActiveOSD)
    {
    #if ENABLE_PVR
        case E_OSD_PVR:
            return MApp_ZUI_ACT_GetPvrDynamicValue_2(hwnd);
    #endif
        default:
            return 100;  //background rect fill the whole line
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_QueryDynamicListItemStatus
///  status provider for dynamic list controls
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return GUI_ENUM_DYNAMIC_LIST_STATE     item status
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
#if ENABLE_ATSC_MENU_UI
extern GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryEPGItemStatus(HWND hwnd);
#endif
GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryDynamicListItemStatus(HWND hwnd)
{
    //NOTE: if an new OSD page added, please add here!
    switch(_eActiveOSD)
    {
        case E_OSD_EPG:
            #if ENABLE_ATSC_MENU_UI
            return MApp_ZUI_ACT_QueryEPGItemStatus(hwnd);
            #endif
            break;
        case E_OSD_MAIN_MENU:
            return MApp_ZUI_ACT_QueryMainMenuItemStatus(hwnd);

    #if ENABLE_ATSC
        case E_OSD_AUDIO_LANGUAGE:
            return MApp_ZUI_ACT_QueryAudioLanguageItemStatus(hwnd);
    #endif

        case E_OSD_INPUT_SOURCE:
            return MApp_ZUI_ACT_QueryInputSourceItemStatus(hwnd);

    #if ENABLE_PVR
        case E_OSD_PVR:
            return MApp_ZUI_ACT_QueryPvrFileSysStatus(hwnd);
    #endif
    #if ENABLE_DVBC
        case E_OSD_CADTV_MANUAL_TUNING:
            return MApp_ZUI_ACT_QueryCadtvManualTuningStatus(hwnd);
    #endif
        case E_OSD_ATV_MANUAL_TUNING:
            return MApp_ZUI_ACT_QueryAtvManualTuningStatus(hwnd);
    #if PLAYLIST_BGM
        case E_OSD_DMP:
            return MApp_ZUI_ACT_QueryDMPStatus(hwnd);
    #endif
    #if ENABLE_FM_RADIO
        case E_OSD_FMRADIO:
            return MApp_ZUI_ACT_QueryFMRadioStatus(hwnd);
    #endif
        case E_OSD_CHANNEL_LIST:
            return MApp_ZUI_ACT_QueryChannelListItemStatus(hwnd);
    #if ENABLE_S2
        case E_OSD_MENU_DISHSETUP:
            return MApp_ZUI_ACT_QueryDishItemStatus(hwnd);
    #endif
    #if GAME_ENABLE
        case E_OSD_GAME_LIST:
            return MApp_ZUI_ACT_QueryGameItemStatus(hwnd);
    #endif

        default:
            ZUI_DBG_FAIL(printf("[ZUI]GBLDLIST\n"));
            ABORT();
            break;
    }

    return EN_DL_STATE_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_GetDynamicColor
///  status provider for dynamic color text/marquee
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @param [in]       hwnd HWND     window handle we are processing
///  @param [in]       type DRAWSTYLE_TYPE     drawing type (normal/focus/disabled)
///  @param [in]       colorOriginal OSD_COLOR     original color
///
///  @return OSD_COLOR     color
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
OSD_COLOR MApp_ZUI_ACT_GetDynamicColor(HWND hwnd, DRAWSTYLE_TYPE type, OSD_COLOR colorOriginal)
{
    //NOTE: if an new OSD page added, please add here!
    //UNUSED(hwnd);
    UNUSED(type);

    switch(_eActiveOSD)
    {
        //case E_OSD_MENU_MAIN:
        //    return MApp_ZUI_ACT_GetMenuMainDynamicColor(hwnd, type, colorOriginal);

        case E_OSD_CHANNEL_LIST:
            return MApp_ZUI_ACT_GetChannelListDynamicColor(hwnd, type, colorOriginal);

        case E_OSD_PROGRAM_EDIT:
            return MApp_ZUI_ACT_GetProgramEditDynamicColor(hwnd, type, colorOriginal);

        case E_OSD_EXPERT_MENU:
            return MApp_ZUI_ACT_GetExpertmenuDynamicColor(hwnd, type, colorOriginal);

        case E_OSD_FACTORY_MENU:
            return MApp_ZUI_ACT_GetFactorymenuDynamicColor(hwnd, type, colorOriginal);

        case E_OSD_DESIGN_MENU:
            return MApp_ZUI_ACT_GetDesignmenuDynamicColor(hwnd, type, colorOriginal);
    #if(ENABLE_EWS == TRUE)
        case E_OSD_MESSAGE_BOX:
            return MApp_ZUI_ACT_GetMsgBoxmenuDynamicColor(hwnd, type, colorOriginal);
    #endif

        default:
            break;
    }

    return colorOriginal;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_CheckBypassKey
///  in some OSD we have to set it as priority, and bypass some key to it.
///    NOTE: DO NOT MODIFY THIS FUNCTION UNLESS YOU WANT TO ADD NEW OSD PAGE HANDLER!
///
///  @return EN_KEY  :0xFF means bypass all key
///
///  @author MStarSemi @date 2009/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_CheckBypassKey(U8 checkedKey)
{
    //NOTE: if an new OSD page added, please add here!

    switch(_eActiveOSD)
    {
#if ENABLE_PVR
        case E_OSD_PVR:
            return MApp_ZUI_ACT_CheckPvrBypassKey(checkedKey);
#endif

        default:
            UNUSED(checkedKey);
            break;
    }

    return KEY_NULL;
}


#undef MAPP_ZUI_ACTGLOBAL_C


