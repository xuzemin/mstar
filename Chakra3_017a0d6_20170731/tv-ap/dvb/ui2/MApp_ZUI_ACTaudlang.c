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

#define MAPP_ZUI_ACTAUDLANG_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
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
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_GlobalFunction.h"
#include "MApp_OSDPage_Main.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_SaveData.h"
#include "MApp_UiMenuDef.h"
#include "msAPI_Memory.h"
#include "MApp_SignalMonitor.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "MApp_Audio.h"

#if ENABLE_CI
//#include "MApp_CIMMI.h"
#include "msAPI_CI.h"

#include "mapp_si.h"
#include "MApp_Audio.h"

//extern unsigned char msAPI_CI_Polling(void);
#endif

#if ENABLE_PVR
#include "MApp_PVR.h"              //For pvr
#endif

#if ENABLE_ATSC
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_UiMenuFunc_ATSC.h"
#endif

#if ENABLE_ATSC_TTS
#include "MApp_TTS_Cus_Say.h"
#endif

extern LPTSTR MApp_ZUI_ACT_GetMenuLanguageStringByIndex(U8 u8Index);

/////////////////////////////////////////////////////////////////////
static EN_OSDPAGE_STATE _enTargetState;

#if ENABLE_ATSC
typedef enum
{
    STATE_AUDIO_MEPG_TYPE,
    STATE_AUDIO_AC3_TYPE,
    STATE_AUDIO_AAC_TYPE,
    STATE_AUDIO_L_SOUND,
    STATE_AUDIO_R_SOUND,
    STATE_AUDIO_FORMAT_TOTAL,
}EN_AUDIO_FORMAT_STATE;
#endif

/////////////////////////////////////////////////////////////////////

#define HKEY_AUDIO_LANG_PAGE_MAX_ITEM           10

/*
typedef struct _AUDIO_LANG_DATA_STRUCT
{
    U8 audioLangTotal;
    U8 curSelItemPage;
} AUDIO_LANG_DATA_STRUCT;

static AUDIO_LANG_DATA_STRUCT * pAudLangData = NULL;
*/
#if ENABLE_DTV
static U8 audioLangTotal;
static U8 curSelItemPage;

//note: current focus is "g_u8AudLangSelected"

////////////////////////////////////////////////////////////////////


static  HWND _ZUI_TBLSEG _AudioLanguageHwndList[HKEY_AUDIO_LANG_PAGE_MAX_ITEM]=
{
    HWND_AUDLANG_LIST_ITEM0,
    HWND_AUDLANG_LIST_ITEM1,
    HWND_AUDLANG_LIST_ITEM2,
    HWND_AUDLANG_LIST_ITEM3,
    HWND_AUDLANG_LIST_ITEM4,
    HWND_AUDLANG_LIST_ITEM5,
    HWND_AUDLANG_LIST_ITEM6,
    HWND_AUDLANG_LIST_ITEM7,
    HWND_AUDLANG_LIST_ITEM8,
    HWND_AUDLANG_LIST_ITEM9,
};

static U8 _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < HKEY_AUDIO_LANG_PAGE_MAX_ITEM; i++)
    {
        if (hwnd == _AudioLanguageHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_AudioLanguageHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_AudioLanguageIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= HKEY_AUDIO_LANG_PAGE_MAX_ITEM)
        return HWND_INVALID;
    return _AudioLanguageHwndList[u8Index];

}

/////////////////////////////////////////////////////////////////////

static void _MApp_AudioLanguage_Init(void)
{
    //from case MIA_MTS_MODE:
    curSelItemPage = g_u8AudLangSelected/HKEY_AUDIO_LANG_PAGE_MAX_ITEM;

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        audioLangTotal = MApp_PVR_PlaybackAudioGetLanguageTotal();
    }
    else
#endif
        audioLangTotal = msAPI_CM_GetAudioStreamCount(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));

#if ENABLE_CI
    if(audioLangTotal && !(msAPI_CM_GetProgramAttribute(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), E_ATTRIBUTE_IS_SCRAMBLED)&& !msAPI_CI_CardDetect()))
#else
    if(audioLangTotal && !(msAPI_CM_GetProgramAttribute(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), E_ATTRIBUTE_IS_SCRAMBLED)))
#endif
    {
        //draw items
    }
    else
    {
        audioLangTotal = 0; //draw nothing..
    }

    if (audioLangTotal)
    {
        MApp_ZUI_API_SetFocus(
            _MApp_ZUI_ACT_AudioLanguageIndexMapToWindow(
                g_u8AudLangSelected%HKEY_AUDIO_LANG_PAGE_MAX_ITEM));
    }
    else
    {
        MApp_ZUI_API_SetFocus(HWND_INVALID);
    }


}

extern U16 _MApp_ZUI_ACT_GetLanguageStringID(EN_LANGUAGE lang, BOOLEAN bDefaultEnglish);

void _TransCaptial(U8 *u8Char)
{
    if(*u8Char >= 'a' && *u8Char <= 'z')
    {
        *u8Char = *u8Char - 'a' + 'A';
    }
}

static LPTSTR _MApp_ZUI_ACT_GetAudioLangItemText(U8 u8index)
{
#if( ENABLE_DVB )
    //from void MApp_UiMenu_DrawAudioLanguageItem(U8 u8index, U8 u8TotalIndex, U8 u8FocusedIndex)
    AUD_INFO stAudInfo;

    if (u8index >= audioLangTotal)
        return 0; //empty string

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        if (!MApp_PVR_PlaybackAudioGetStreamInfo(&stAudInfo, u8index))
            return 0;
    }
    else
#endif
    {
        if( TRUE != msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &stAudInfo, u8index) )
            return 0; //empty string : u8IsNullItem =  TRUE;
    }

    if(TRUE == MApp_Scramble_GetCurStatus())
        return 0; //empty string

    //from case HOTKEYLAGTEXT:
    if ( IsDTVInUse() )
    {
    #if ENABLE_NZ_FREEVIEW
        LPTSTR str_lang = MApp_ZUI_ACT_GetMenuLanguageStringByIndex(MApp_GetLanguageBySILanguage((EN_SI_LANGUAGE)stAudInfo.aISOLangInfo[0].bISOLangIndex));

        if (str_lang == 0)
        {
            U8 au8Code[MAX_ISO639CODE_LENGTH];
            LPTSTR str = CHAR_BUFFER;

            if(msAPI_SI_GetISOLangCodeFromIndex((EN_SI_LANGUAGE)stAudInfo.aISOLangInfo[0].bISOLangIndex, au8Code) == TRUE)
            {
                _TransCaptial(&au8Code[0]);
                _TransCaptial(&au8Code[1]);
                _TransCaptial(&au8Code[2]);

                str[0] = (U16)au8Code[0];
                str[1] = (U16)au8Code[1];
                str[2] = (U16)au8Code[2];
            }
            else
            {
                str[0] = 'U';
                str[1] = 'N';
                str[2] = 'D';
            }
            str[3] = 0;

            return CHAR_BUFFER;
        }
        return str_lang;
    #else
        LPTSTR str_lang = MApp_ZUI_ACT_GetMenuLanguageStringByIndex(MApp_GetLanguageBySILanguage((EN_SI_LANGUAGE)stAudInfo.aISOLangInfo[0].bISOLangIndex));

        if (str_lang == 0)
        {
            U8 au8Code[MAX_ISO639CODE_LENGTH];
            if(msAPI_SI_GetISOLangCodeFromIndex((EN_SI_LANGUAGE)stAudInfo.aISOLangInfo[0].bISOLangIndex, au8Code) == TRUE)
            {
                LPTSTR str = CHAR_BUFFER;
                str[0] = (U16)au8Code[0];
                str[1] = (U16)au8Code[1];
                str[2] = (U16)au8Code[2];
                str[3] = 0;

                if ((au8Code[0] == 'u' && au8Code[1] == 'n' && au8Code[2] == 'd') ||
                    (au8Code[0] == 'U' && au8Code[1] == 'N' && au8Code[2] == 'D'))
                {
                    return MApp_ZUI_API_GetString(en_str_not_define);
                }
                else
                {
                    return CHAR_BUFFER;
                }
            }
            else
            {

                return MApp_ZUI_API_GetString(en_str_not_define);
            }
        }
        return str_lang;
    #endif
    }

#else

    u8index=u8index;

#endif

    return 0; //empty string
}

static U16 _MApp_ZUI_ACT_GetAudioLangItemTypeBitmapID(U8 u8index, DRAWSTYLE_TYPE ds_type)
{
    //from void MApp_UiMenu_DrawAudioLanguageItem(U8 u8index, U8 u8TotalIndex, U8 u8FocusedIndex)
    AUD_INFO stAudInfo;

    if (u8index >= audioLangTotal)
        return 0xFFFF; //empty bitmap

    //u8TotalIndex = u8TotalIndex;    //reserve parameters for other UI need to draw different Top & Bottom items

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        if (!MApp_PVR_PlaybackAudioGetStreamInfo(&stAudInfo, u8index))
            return 0xFFFF;
    }
    else
#endif
    {
        if( TRUE != msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &stAudInfo, u8index) )
            return 0xFFFF; //empty bitmap: u8IsNullItem =  TRUE;
    }

    if(TRUE == MApp_Scramble_GetCurStatus())
        return 0xFFFF; //empty bitmap

    //draw icon mpeg/dolby
    //switch(stAudInfo.wAudType)
    switch( msAPI_CM_Get_AudStreamType_By_AudInfo(&stAudInfo) )
    {
        case E_AUDIOSTREAM_MPEG:
            //MApp_UiMenu_DrawBitmap_2(EN_BMP_AUDIO_LANG_MPEG, ComponentType);
            return  (ds_type == DS_FOCUS)? E_BMP_ICON_MPEG_F: E_BMP_ICON_MPEG_N;
        case E_AUDIOSTREAM_AC3:
            //MApp_UiMenu_DrawBitmap_2(EN_BMP_AUDIO_LANG_DOLBY, ComponentType);
            return  (ds_type == DS_FOCUS)? E_BMP_ICON_DOLBY_F: E_BMP_ICON_DOLBY_N;

        case E_AUDIOSTREAM_MPEG4:
    #if ((UI_SKIN_SEL != UI_SKIN_960X540XI8))
            //if(stAudInfo.u8ProfileAndLevel == HE_AAC_LEVEL2)
            if(stAudInfo.eProfileAndLevel == E_CM_PROFILE_HE_AAC_LEVEL2)
                return  (ds_type == DS_FOCUS)? E_BMP_Icon_Audio_HEAACL2_N: E_BMP_Icon_Audio_HEAACL2_N;
            //if(stAudInfo.u8ProfileAndLevel == HE_AAC_LEVEL4)
            if(stAudInfo.eProfileAndLevel == E_CM_PROFILE_HE_AAC_LEVEL4)
                return  (ds_type == DS_FOCUS)? E_BMP_Icon_Audio_HEAACL4_N: E_BMP_Icon_Audio_HEAACL4_N;
            else
                return  (ds_type == DS_FOCUS)? E_BMP_Icon_Audio_HEAACL1_N: E_BMP_Icon_Audio_HEAACL1_N;

    #else
            return  (ds_type == DS_FOCUS)? E_BMP_ICON_AUDIO_AAC_F: E_BMP_ICON_AUDIO_AAC_N;
    #endif

        case E_AUDIOSTREAM_AAC:
            return  (ds_type == DS_FOCUS)? E_BMP_ICON_AUDIO_AAC_F: E_BMP_ICON_AUDIO_AAC_N;
        case E_AUDIOSTREAM_AC3P:
            return  (ds_type == DS_FOCUS)? E_BMP_ICON_AUDIO_AC3P_F: E_BMP_ICON_AUDIO_AC3P_N;

        default:
            break;
    }

    return 0xFFFF; //empty bitmap

}

#if(ENABLE_ATSC )
GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryAudioLanguageItemStatus(HWND hwnd)
{
    if(_MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd) < MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum)
    {
        return EN_DL_STATE_NORMAL;
    }
    else
    {
        return EN_DL_STATE_HIDDEN;
    }
}
#endif

static U16 _MApp_ZUI_ACT_GetAudioLangItemType2BitmapID(U8 u8index, DRAWSTYLE_TYPE ds_type)
{
    AUD_INFO stAudInfo;

    if (u8index >= audioLangTotal)
        return 0xFFFF; //empty bitmap

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        if (!MApp_PVR_PlaybackAudioGetStreamInfo(&stAudInfo, u8index))
            return 0xFFFF;
    }
    else
#endif
    {
        if( TRUE != msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &stAudInfo, u8index) )
            return 0xFFFF; //empty bitmap: u8IsNullItem =  TRUE;
    }

    if(TRUE == MApp_Scramble_GetCurStatus())
        return 0xFFFF; //empty bitmap

    //draw icon stream info
    if(stAudInfo.aISOLangInfo[0].bBroadcastMixedAD)
    {
        return  (ds_type == DS_FOCUS)? E_BMP_ICON_AUDIO_VI_F: E_BMP_ICON_AUDIO_VI_N;
    }
    switch(stAudInfo.aISOLangInfo[0].bAudType)
    {
        case 1: // clean effect
            return  (ds_type == DS_FOCUS)? E_BMP_ICON_AUDIO_CE_F: E_BMP_ICON_AUDIO_CE_N;
        case 2: // hearing impaired
            return  (ds_type == DS_FOCUS)? E_BMP_ICON_AUDIO_HI_F: E_BMP_ICON_AUDIO_HI_N;
        case 3: // visual impaired
            return  (ds_type == DS_FOCUS)? E_BMP_ICON_AUDIO_VI_F: E_BMP_ICON_AUDIO_VI_N;
        case 0: // undefined
        default:
        break;
    }
    return 0xFFFF; //empty bitmap

}

#endif
/////////////////////////////////////////////////////////////////////
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
//extern void _MApp_ZUI_API_DrawDynamicComponent(DRAWCOMPONENT component, const void * param, const GRAPHIC_DC * pdc, const RECT * rect);



void MApp_ZUI_ACT_AppShowAudioLanguage(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_AUDIO_LANGUAGE;

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
        ZUI_AUDIO_LANGUAGE_XSTART, ZUI_AUDIO_LANGUAGE_YSTART,
        ZUI_AUDIO_LANGUAGE_WIDTH, ZUI_AUDIO_LANGUAGE_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    //////////////////////////////
    /*/ init internal data structre, before ZUI create message...
    _ZUI_FREE(pAudLangData);
    pAudLangData = (AUDIO_LANG_DATA_STRUCT*)_ZUI_MALLOC(
        sizeof(AUDIO_LANG_DATA_STRUCT));
    if (pAudLangData == 0)
    {
        ZUI_DBG_FAIL(printf("[ZUI]AAUDL\n"));
        ABORT();
        return;
    }
    *//////////////////////////////

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
#if ENABLE_ATSC
    if(IsAtscInUse() || IsATVInUse())
    {
        U8    u8Offset = (HWND_AUDLANG_LIST_ITEM1 - HWND_AUDLANG_LIST_ITEM0)*g_u8AudLangSelected;
        MApp_ZUI_API_SetFocus(HWND_AUDLANG_LIST_ITEM0+u8Offset);
    }
    else
#endif
    {
#if (ENABLE_DTV)
        _MApp_AudioLanguage_Init();
#endif
    }

    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);

}


//////////////////////////////////////////////////////////
// Key Handler


BOOLEAN MApp_ZUI_ACT_ExecuteAudioLanguageAction(U16 act)
{

    /*
    if (pAudLangData == 0)
    {
        ZUI_DBG_FAIL(printf("[ZUI]EAUDL\n"));
        ABORT();
        return TRUE;
    }*/
#if (!ENABLE_DTV)
    UNUSED(act);
#else
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


        case EN_EXE_AUDIO_LANG_LEFT:                   ///< audio language left
        case EN_EXE_AUDIO_LANG_RIGHT:                    ///< audio language right
            //from case MIA_HKEY_AUDIO_LANG_LEFT:
            //from case MIA_HKEY_AUDIO_LANG_RIGHT:
        //[Evora Boxer ][Task 5.20/Task 5.26] Enter MTS,Can not use left/right key to change RR/RL/LL
            if(act == EN_EXE_AUDIO_LANG_LEFT)
            {
                if(g_u8LRAudioMode == 0)
                {
                    g_u8LRAudioMode = 2;
                }
                else
                {
                    g_u8LRAudioMode--;
                }
            }
            else
            {
                if(g_u8LRAudioMode == 2)
                {
                    g_u8LRAudioMode = 0;
                }
                else
                {
                    g_u8LRAudioMode++;
                }
            }
            if(g_u8LRAudioMode == 0)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_STEREO, 0);
                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LR, 0);
            }
            else if(g_u8LRAudioMode == 1)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_RR, 0);
                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_RR, 0);
            }
            else if(g_u8LRAudioMode == 2)
            {
                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
                MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LL, 0);
            }
            MApp_ZUI_API_InvalidateWindow(MApp_ZUI_API_GetFocus());

            return TRUE;

        case EN_EXE_AUDIO_LANG_UP:                   ///< audio language up
        case EN_EXE_AUDIO_LANG_DOWN:                    ///< audio language down
            //from case MIA_HKEY_AUDIO_LANG_UP:
            //from case MIA_HKEY_AUDIO_LANG_DOWN:
        #if ENABLE_ATSC
            if(IsAtscInUse() || IsATVInUse())
            {
                U8 u8AudLangNum = MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum;

                if(u8AudLangNum > 1)
                {
                    if(act==EN_EXE_AUDIO_LANG_UP)
                    {
                        if(g_u8AudLangSelected > 0)
                        {
                           g_u8AudLangSelected--;
                        }
                        else
                        {
                            g_u8AudLangSelected = u8AudLangNum - 1;
                        }

                    }
                    else
                    {
                        if(g_u8AudLangSelected < (u8AudLangNum - 1))
                        {
                            g_u8AudLangSelected++;
                        }
                        else
                        {
                            g_u8AudLangSelected = 0;
                        }
                    }
                    MApp_Aud_SetMtsMode();

                    #if ENABLE_SOUNDTRACK_CHECKER_NEW
                    MsOS_DelayTask(100);
                    #endif

                    MApp_ZUI_API_SetFocus(HWND_AUDLANG_LIST_ITEM0 + (HWND_AUDLANG_LIST_ITEM1 - HWND_AUDLANG_LIST_ITEM0)*g_u8AudLangSelected);
                }
            }
            else
        #endif
            {
                U8 u8CurrentItemIndex;
                U8 u8PrvItemPage, u8NewItemPage;
                AUD_INFO aAudioStreamInfo;
                BOOLEAN retval;

                memset(&aAudioStreamInfo, 0, sizeof(AUD_INFO));

                if (audioLangTotal <= 1)
                    return TRUE;

                g_u8LRAudioMode = 0;
                u8CurrentItemIndex = g_u8AudLangSelected;

                u8PrvItemPage = u8CurrentItemIndex / HKEY_AUDIO_LANG_PAGE_MAX_ITEM;
#if ENABLE_PVR
                if (MApp_PVR_IsPlaybacking())
                    audioLangTotal = MApp_PVR_PlaybackAudioGetLanguageTotal();
                else
#endif
                    audioLangTotal = msAPI_CM_GetAudioStreamCount(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));

                //printf("audioLangTotal=%u \n",audioLangTotal);
#if ENABLE_CI
                if(!audioLangTotal || (msAPI_CM_GetProgramAttribute(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), E_ATTRIBUTE_IS_SCRAMBLED)&& !msAPI_CI_CardDetect()))
#else
                if(!audioLangTotal || (msAPI_CM_GetProgramAttribute(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), E_ATTRIBUTE_IS_SCRAMBLED)))
#endif
                {   //no items
                    audioLangTotal = 0; //break;
                    MApp_ZUI_API_SetFocus(HWND_INVALID);
                    return TRUE;
                }

                if (act==EN_EXE_AUDIO_LANG_UP) //menuAction == MIA_HKEY_AUDIO_LANG_UP)
                {
#if ENABLE_PVR
                    if (MApp_PVR_IsPlaybacking())
                        u8CurrentItemIndex = (g_u8AudLangSelected+(audioLangTotal-1))%audioLangTotal;//(g_u8AudLangSelected==0)?audioLangTotal-1: g_u8AudLangSelected-1;
                    else
#endif
                        u8CurrentItemIndex = msAPI_CM_GetPrevAudioStreamOrdinal(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), g_u8AudLangSelected);
                }
                else
                {
#if ENABLE_PVR
                    if (MApp_PVR_IsPlaybacking())
                        u8CurrentItemIndex = (g_u8AudLangSelected+1)% audioLangTotal; //((g_u8AudLangSelected+1) == audioLangTotal)?0: g_u8AudLangSelected+1;
                    else
#endif
                        u8CurrentItemIndex = msAPI_CM_GetNextAudioStreamOrdinal(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), g_u8AudLangSelected);
                }

                u8NewItemPage = u8CurrentItemIndex / HKEY_AUDIO_LANG_PAGE_MAX_ITEM;

#if ENABLE_PVR
                if ( MApp_PVR_IsPlaybacking())
                {
                    retval = MApp_PVR_PlaybackAudioGetStreamInfo(&aAudioStreamInfo, u8CurrentItemIndex);
                }
                else
#endif
                {
                    retval = msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &aAudioStreamInfo, u8CurrentItemIndex);
                }

                if(!retval)
                {
                    ASSERT(0);
                }

                g_u8LRAudioMode = aAudioStreamInfo.aISOLangInfo[0].bISOLanguageInfo;

                if (u8PrvItemPage != u8NewItemPage)
                {
                    //clear background
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_AUDLANG_LIST_PANE);
                    curSelItemPage = u8NewItemPage;
                }

                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_AudioLanguageIndexMapToWindow(
                        u8CurrentItemIndex%HKEY_AUDIO_LANG_PAGE_MAX_ITEM));

                if (audioLangTotal > DEFAULT_AUD_LANG_NUM)
                {   //printf("set audio languge %u \n",g_u8AudLangSelected);
                #if(ENABLE_DVB)
                    MApp_Audio_SetAudioLanguage(u8CurrentItemIndex);
                #endif
                }

            }
            return TRUE;

        case EN_EXE_GOTO_MAINMENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_MAIN_MENU;
            return TRUE;
        //case EN_EXE_SWITCH_AUDIOLANG:

    }
#endif
    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_HandleAudioLanguageKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state
#if ENABLE_ATSC
    U8 u8Index;
#endif
    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_AUDLANG_LIST_PANE, 0);

    switch(key)
    {
        case VK_MTS:
        case VK_EXIT:
#if ENABLE_ATSC_TTS
            MApp_TTS_Cus_Say_exit();
#endif
            MApp_ZUI_ACT_ExecuteAudioLanguageAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;
        case VK_POWER:
            MApp_ZUI_ACT_ExecuteAudioLanguageAction(EN_EXE_POWEROFF);
            return TRUE;
        case VK_SELECT:
            #if ENABLE_ATSC
                if(IsAtscInUse() || IsATVInUse())
                {
                      u8Index = _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(MApp_ZUI_API_GetFocus());
                    if(!MApp_UiMenuFunc_SetAudio_Language(u8Index))
                    {
                        ZUI_DBG_FAIL(printf("Set Audio Language fail\n"));
                    }
                    MApp_ZUI_ACT_ExecuteAudioLanguageAction(EN_EXE_CLOSE_CURRENT_OSD);
                    // MApp_ZUI_ACT_ShutdownOSD();
                    return TRUE;
                }
            #endif

            //MApp_ZUI_API_SetTimer(HWND_AUDLANG_BOTTOM_HALF_OK_BTN, 0, BUTTONANICLICK_PERIOD);
            //MApp_ZUI_API_InvalidateWindow(HWND_AUDLANG_BOTTOM_HALF_OK_BTN);
            break;
        /*case VK_EXIT:
            MApp_ZUI_API_SetTimer(HWND_MENU_BOTTOM_HALF_EXIT_BG, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_BOTTOM_HALF_EXIT_BG);
            break;*/
        case VK_UP:
            //MApp_ZUI_API_SetTimer(HWND_AUDLANG_BOTTOM_HALF_UP_BTN, 0, BUTTONANICLICK_PERIOD);
            //MApp_ZUI_API_InvalidateWindow(HWND_AUDLANG_BOTTOM_HALF_UP_BTN);
            break;
        case VK_DOWN:
            //MApp_ZUI_API_SetTimer(HWND_AUDLANG_BOTTOM_HALF_DOWN_BTN, 0, BUTTONANICLICK_PERIOD);
            //MApp_ZUI_API_InvalidateWindow(HWND_AUDLANG_BOTTOM_HALF_DOWN_BTN);
            break;
        case VK_LEFT:
            //MApp_ZUI_API_SetTimer(HWND_AUDLANG_BOTTOM_HALF_LEFT_BTN, 0, BUTTONANICLICK_PERIOD);
            //MApp_ZUI_API_InvalidateWindow(HWND_AUDLANG_BOTTOM_HALF_LEFT_BTN);
            break;
        case VK_RIGHT:
            //MApp_ZUI_API_SetTimer(HWND_AUDLANG_BOTTOM_HALF_RIGHT_BTN, 0, BUTTONANICLICK_PERIOD);
            //MApp_ZUI_API_InvalidateWindow(HWND_AUDLANG_BOTTOM_HALF_RIGHT_BTN);
            break;

        case VK_MENU:
            MApp_ZUI_ACT_ExecuteAudioLanguageAction(EN_EXE_GOTO_MAINMENU);
            break;

        default:
            break;
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateAudioLanguage(void)
{
    ZUI_MSG(printf("[]term:audlang\n"));
    MApp_OSDPage_SetState(_enTargetState);
}

#if ENABLE_ATSC
static LPTSTR MApp_ZUI_ACT_GetAudioLanguageString(U8 u8index)
{
    U8 Lang_Count = 0, Lang_Count_Total = 0,  i;
    LPTSTR u16StrLang;

    if (u8index >= MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum)
        return 0; //empty string

    U8 u8AudioLang = astgSoundTrack[u8index].u8AudLangIdx;
    for (i=0; i < MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum; i++)
    {
        if (astgSoundTrack[i].u8AudLangIdx == u8AudioLang)
            Lang_Count_Total ++;
        if (i == u8index)
            Lang_Count = Lang_Count_Total;
    }

    switch ((EN_ADUIO_LAN)u8AudioLang)
    {
        case SOUND_AUDIO_LAN_ENGLISH:
            u16StrLang = MApp_ZUI_API_GetString(en_str_English);
            break;
        case SOUND_AUDIO_LAN_FRENCH:
            u16StrLang = MApp_ZUI_API_GetString(en_str_French);
            break;
        case SOUND_AUDIO_LAN_SPANISH:
            u16StrLang = MApp_ZUI_API_GetString(en_str_Spanish);
            break;
        case SOUND_AUDIO_LAN_KOREA:
            u16StrLang = MApp_ZUI_API_GetString(en_str_Korean);
            break;
        case SOUND_AUDIO_LAN_JAPAN:
            u16StrLang = MApp_ZUI_API_GetString(en_str_Japan);
            break;
        case SOUND_AUDIO_LAN_CHINESE:
            u16StrLang = MApp_ZUI_API_GetString(en_str_Chinese);
            break;
        case SOUND_AUDIO_LANG_UND:
            u16StrLang = MApp_ZUI_API_GetString(en_str_Other);
            break;

        default:
            u16StrLang = MApp_ZUI_API_GetString(en_str_Other);
            break;
    }
    if (Lang_Count_Total > 1)
    {
        U8 u8StrLang[20];
        memset( u8StrLang, 0, sizeof(u8StrLang) );
        MApp_U16StringToU8String(u16StrLang, u8StrLang, MApp_UiMenu_u16Strlen(u16StrLang));
        u8StrLang[strlen((char *)u8StrLang)] = 0x20;
        u8StrLang[strlen((char *)u8StrLang)] = 0x30 + Lang_Count;
        MApp_U8StringToU16String(u8StrLang, u16StrLang, strlen((char *)u8StrLang));
    }
    return u16StrLang;
}
#endif

LPTSTR MApp_ZUI_ACT_GetAudioLanguageDynamicText(HWND hwnd)
{
    // Marked it by coverity_295
    //U16 u16TempID = Empty;
#if (!ENABLE_DTV)
    UNUSED(hwnd);
#else
    switch(hwnd)
    {
        case HWND_AUDLANG_ITEM0_LANG_TEXT:
        case HWND_AUDLANG_ITEM1_LANG_TEXT:
        case HWND_AUDLANG_ITEM2_LANG_TEXT:
        case HWND_AUDLANG_ITEM3_LANG_TEXT:
        case HWND_AUDLANG_ITEM4_LANG_TEXT:
        case HWND_AUDLANG_ITEM5_LANG_TEXT:
        case HWND_AUDLANG_ITEM6_LANG_TEXT:
        case HWND_AUDLANG_ITEM7_LANG_TEXT:
        case HWND_AUDLANG_ITEM8_LANG_TEXT:
        case HWND_AUDLANG_ITEM9_LANG_TEXT:
            {
            #if ENABLE_ATSC
                if(IsAtscInUse() || IsATVInUse())
                {
                    U8 u8Index= _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd);
                    return MApp_ZUI_ACT_GetAudioLanguageString(u8Index);
                }
                else
            #endif
                {
                    U8 idx = _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd)+
                    HKEY_AUDIO_LANG_PAGE_MAX_ITEM*curSelItemPage;
                    return _MApp_ZUI_ACT_GetAudioLangItemText(idx);
                }
            }

    }
#endif
    //if (u16TempID != Empty)
    //    return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

#if ENABLE_ATSC
static BOOLEAN MApp_ZUI_ACT_GetAudioFormatStatus(U8 u8index, U8 u8AudioFormat )
{
    if (u8index >= MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum)
        return FALSE;

    switch((EN_AUDIO_FORMAT_STATE) u8AudioFormat)
    {
        case STATE_AUDIO_MEPG_TYPE:
            {
                U16 u16AudioType = astgSoundTrack[u8index].u16AudStreamType; //0=Mpeg, 1=AC3 ,2=AAC
                if(u16AudioType == AUD_STREAM_TYPE_MPEG)
                    return TRUE;
                else
                    return FALSE;
            }
            break;
        case STATE_AUDIO_AC3_TYPE:
            {
                U16 u16AudioType = astgSoundTrack[u8index].u16AudStreamType; //0=Mpeg, 1=AC3 ,2=AAC
                if(u16AudioType == AUD_STREAM_TYPE_AC3)
                    return TRUE;
                else
                    return FALSE;
            }
            break;
       case STATE_AUDIO_AAC_TYPE:
            {
                    U16 u16AudioType = astgSoundTrack[u8index].u16AudStreamType;//0=Mpeg, 1=AC3 ,2=AAC
                    if(u16AudioType == AUD_STREAM_TYPE_AAC)
                        return TRUE;
                    else
                        return FALSE;
             }
             break;

        case STATE_AUDIO_L_SOUND:
            {
                switch(stGenSetting.g_SoundSetting.enSoundAudioChannel)
                {
                    case 0:
                    case 1:
                        return TRUE;
                        break;
                    case 2:
                        return FALSE;
                        break;
                    default:
                        return TRUE;
                }
            }
            break;
        case STATE_AUDIO_R_SOUND:
            {
                switch(stGenSetting.g_SoundSetting.enSoundAudioChannel)
                {
                    case 0:
                    case 2:
                         return TRUE;
                        break;
                    case 1:
                        return FALSE;
                        break;

                    default:
                        return TRUE;
                }
            }
            break;

        default:
            break;
    }
    return TRUE;
}
#endif

U16 MApp_ZUI_ACT_GetAudioLanguageDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
#if (!ENABLE_DTV)
    UNUSED(hwnd);
    UNUSED(ds_type);
#else

#if ENABLE_ATSC
    U8 u8Index;
    U32 u32ShowAudType = FALSE;
    U32 u32ShowLSournd = FALSE;
    U32 u32ShowRSournd = FALSE;
#endif

    switch(hwnd)
    {
        case HWND_AUDLANG_ITEM0_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM1_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM2_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM3_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM4_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM5_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM6_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM7_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM8_L_SOUND_ICON:
        case HWND_AUDLANG_ITEM9_L_SOUND_ICON:
        #if ENABLE_ATSC
            if(IsAtscInUse() || IsATVInUse())
            {
                u8Index = _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd);
                u32ShowLSournd = MApp_ZUI_ACT_GetAudioFormatStatus(u8Index, STATE_AUDIO_L_SOUND);

                if (u32ShowLSournd)
                {
                    if (ds_type == DS_FOCUS)
                    {
                        return E_BMP_IDLE_IMG_ICON_L_FOCUS;
                    }
                    else
                    {
                        return E_BMP_IDLE_IMG_ICON_L_UNFOCUS;
                    }
                }
            }
            else
         #endif
            {
                //from MApp_UiMenu_DrawAudioLanguageItem()
                if (ds_type == DS_FOCUS)
                {
                    if (g_u8LRAudioMode == 0 || g_u8LRAudioMode == 2)
                        //return E_BMP_ICON_AUDIO_L_F;
                        return E_BMP_ICON_AUDIO_L_F;
                    if (g_u8LRAudioMode == 1)
                        //return E_BMP_ICON_AUDIO_R_F;
                        return E_BMP_ICON_AUDIO_R_F;
                }
            }
            break;

        case HWND_AUDLANG_ITEM0_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM1_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM2_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM3_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM4_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM5_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM6_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM7_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM8_R_SOUND_ICON:
        case HWND_AUDLANG_ITEM9_R_SOUND_ICON:
        #if ENABLE_ATSC
            if(IsAtscInUse() || IsATVInUse())
            {
                u8Index = _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd);
                u32ShowRSournd = MApp_ZUI_ACT_GetAudioFormatStatus(u8Index, STATE_AUDIO_R_SOUND);

                if (u32ShowRSournd)
                {
                    if (ds_type == DS_FOCUS)
                    {
                        return E_BMP_IDLE_IMG_ICON_R_FOCUS;
                    }
                    else
                    {
                        return E_BMP_IDLE_IMG_ICON_R_UNFOCUS;
                    }
                }
            }
            else
        #endif
            {
            //from MApp_UiMenu_DrawAudioLanguageItem()
                if (ds_type == DS_FOCUS)
                {
                    if (g_u8LRAudioMode == 0 || g_u8LRAudioMode == 1)
                        //return E_BMP_ICON_AUDIO_R_F;
                        return E_BMP_ICON_AUDIO_R_F;
                    if (g_u8LRAudioMode == 2)
                        //return E_BMP_ICON_AUDIO_L_F;
                        return E_BMP_ICON_AUDIO_L_F;
                }
           }
            break;

        case HWND_AUDLANG_ITEM0_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM1_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM2_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM3_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM4_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM5_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM6_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM7_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM8_AUDIO_TYPE_ICON:
        case HWND_AUDLANG_ITEM9_AUDIO_TYPE_ICON:
        #if ENABLE_ATSC
            if(IsAtscInUse() || IsATVInUse())
            {
                u8Index = _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd);
                u32ShowAudType = MApp_ZUI_ACT_GetAudioFormatStatus(u8Index, STATE_AUDIO_MEPG_TYPE);

                if (u32ShowAudType)
                {
                    if (ds_type == DS_FOCUS)
                    {
                        return E_BMP_IDLE_IMG_ICON_MPEG_FOCUS;
                    }
                    else
                    {
                        return E_BMP_IDLE_IMG_ICON_MPEG_UNFOCUS;
                    }
                }
            }
            else
        #endif
            {
                U8 idx = _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd)+
                    HKEY_AUDIO_LANG_PAGE_MAX_ITEM*curSelItemPage;
                return _MApp_ZUI_ACT_GetAudioLangItemTypeBitmapID(idx, ds_type);
            }
            break;
        case HWND_AUDLANG_ITEM0_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM1_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM2_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM3_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM4_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM5_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM6_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM7_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM8_AUDIO_TYPE2_ICON:
        case HWND_AUDLANG_ITEM9_AUDIO_TYPE2_ICON:
        #if ENABLE_ATSC
            if(IsAtscInUse() || IsATVInUse())
            {
                  u8Index = _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd);

                 if( MApp_ZUI_ACT_GetAudioFormatStatus(u8Index, STATE_AUDIO_MEPG_TYPE))
                 {
                    if (ds_type == DS_FOCUS)
                      {
                          return E_BMP_Icon_Audio_MPEG_F;
                      }
                      else
                      {
                          return E_BMP_Icon_Audio_MPEG_N;
                      }
                 }
                 else if( MApp_ZUI_ACT_GetAudioFormatStatus(u8Index, STATE_AUDIO_AC3_TYPE))
                 {
 #if ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565 == UI_SKIN_SEL))
                     if (ds_type == DS_FOCUS)
                      {
                         if(MApi_AUDIO_ReadDspCodeType() == AU_DVB_STANDARD_AC3)
                         {
							 return E_BMP_Icon_Audio_AC3_F;
						 }
						 if(MApi_AUDIO_ReadDspCodeType() == AU_DVB_STANDARD_AC3P)
						 {
							 return E_BMP_Icon_Audio_AC3p_F;
						 }
                      }
                      else
                      {
                          if(MApi_AUDIO_ReadDspCodeType() == AU_DVB_STANDARD_AC3)
                         {
							 return E_BMP_Icon_Audio_AC3_N;
						 }
						 if(MApi_AUDIO_ReadDspCodeType() == AU_DVB_STANDARD_AC3P)
						 {
							 return E_BMP_Icon_Audio_AC3p_N;
						 }
                      }
 #endif
                 }
                else if( MApp_ZUI_ACT_GetAudioFormatStatus(u8Index, STATE_AUDIO_AAC_TYPE))
                 {
                    if (ds_type == DS_FOCUS)
                      {
                          return E_BMP_Icon_Audio_AAC_F;
                      }
                      else
                      {
                          return E_BMP_Icon_Audio_AAC_N;
                      }
                 }
            }
            else
        #endif
            {
                U8 idx = _MApp_ZUI_ACT_AudioLanguageWindowMapToIndex(hwnd)+
                    HKEY_AUDIO_LANG_PAGE_MAX_ITEM*curSelItemPage;
                return _MApp_ZUI_ACT_GetAudioLangItemType2BitmapID(idx, ds_type);
            }
            break;
    }
#endif
    return 0xFFFF; //for empty bitmap....
}

BOOLEAN MApp_ZUI_ACT_ExecuteSetAudLangDialogAction(U16 act)
{
    stUserSoundSettingType *pstSoundSetting = NULL;

    MApp_GetGenSetting(EN_GENSETTING_CLASS_SOUND,  (void *)&pstSoundSetting);
#if (!ENABLE_DTV)
    UNUSED(act);
#else
    switch(act)
    {
        case EN_EXE_AUDIOLANG_SET:
            pstSoundSetting->Primary_Flag= !pstSoundSetting->Primary_Flag;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_OPTION_AUDIOLANG_PRIMARY_OPTION);
            return true;

        default:
            ZUI_DBG_FAIL(printf("[ZUI]SetLangACT\n"));
            ABORT();
    }
#endif
    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetSetAudLangDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    stUserSoundSettingType *pstSoundSetting = NULL;

    MApp_GetGenSetting(EN_GENSETTING_CLASS_SOUND,  (void *)&pstSoundSetting);
    switch(hwnd)
    {
        case HWND_MENU_OPTION_AUDIOLANG_PRIMARY_OPTION:
        {
            if(!pstSoundSetting->Primary_Flag)
                u16TempID=en_str_Primary;
            else
                u16TempID=en_str_Secondary;
            break;
        }

    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

/////////////////////////////////////////////////////////
// Customize Window Procedures

/*
S32 MApp_ZUI_ACT_AudioLanguageListWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            {

                //setting AP timeout, auto close
                MApp_ZUI_API_SetTimer(hwnd, 0, HOT_MENU_TIME_OUT_3SEC);
            }
            break;

        case MSG_TIMER:
            {
                //if the time is up, kill the timer and then close AP!
                MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
            break;

        case MSG_DESTROY:
            break;

    }

    return DEFAULTWINPROC(hwnd, msg);
}
*/

#undef MAPP_ZUI_ACTAUDLANG_C
