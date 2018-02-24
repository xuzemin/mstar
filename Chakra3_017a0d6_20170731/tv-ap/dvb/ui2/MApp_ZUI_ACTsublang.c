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

#define MAPP_ZUI_ACTSUBLANG_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"

#if ENABLE_SUBTITLE
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_OSDPage_Main.h"

#include "MApp_SaveData.h"
#include "MApp_UiMenuDef.h"
#include "MApp_Subtitle.h"
//ZUI: #include "MApp_DispMenu.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mapp_si.h"
#if (ENABLE_TTX)
#include "mapp_ttx.h"
#endif
#include "MApp_Subtitle.h"
//#include "MApp_Audio.h"
#if ENABLE_PVR
#include "MApp_PVR.h"
#endif

#include "mapp_si_if.h"

#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif
/////////////////////////////////////////////////////////////////////
#define HKEY_SUBTITLE_PAGE_MAX_ITEM             10

#define STRING_TO_U32(a,b,c)  (U32)(a<<24)+(U32)(b<<16)+(U32)(c<<8)

//note: current selection: u8SubtitleItemSelIdx (0=off)
//note: total count: u8SubtitleServiceNum (not include off)

static EN_OSDPAGE_STATE _enTargetState;

////////////////////////////////////////////////////////////////////


static  HWND _ZUI_TBLSEG _SubtitleLanguageHwndList[HKEY_SUBTITLE_PAGE_MAX_ITEM]=
{
    HWND_SUBLANG_ITEM0,
    HWND_SUBLANG_ITEM1,
    HWND_SUBLANG_ITEM2,
    HWND_SUBLANG_ITEM3,
    HWND_SUBLANG_ITEM4,
    HWND_SUBLANG_ITEM5,
    HWND_SUBLANG_ITEM6,
    HWND_SUBLANG_ITEM7,
    HWND_SUBLANG_ITEM8,
    HWND_SUBLANG_ITEM9,
};

static U8 _MApp_ZUI_ACT_SubtitleLanguageWindowMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < HKEY_SUBTITLE_PAGE_MAX_ITEM; i++)
    {
        if (hwnd == _SubtitleLanguageHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_SubtitleLanguageHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_SubtitleLanguageIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= HKEY_SUBTITLE_PAGE_MAX_ITEM)
        return HWND_INVALID;
    return _SubtitleLanguageHwndList[u8Index];

}


////////////////////////////////////////////////////////////


extern BOOLEAN MApp_TV_SearchLastSubtileLang(void);


static void _MApp_SubtitleLanguage_RefreshIcons(void)
{
    //printf("_MApp_SubtitleLanguage_RefreshIcons\n");
    static  HWND _ZUI_TBLSEG _hwndTTXIcons[HKEY_SUBTITLE_PAGE_MAX_ITEM]=
    {
        HWND_SUBLANG_ITEM0_ICON_TTX,
        HWND_SUBLANG_ITEM1_ICON_TTX,
        HWND_SUBLANG_ITEM2_ICON_TTX,
        HWND_SUBLANG_ITEM3_ICON_TTX,
        HWND_SUBLANG_ITEM4_ICON_TTX,
        HWND_SUBLANG_ITEM5_ICON_TTX,
        HWND_SUBLANG_ITEM6_ICON_TTX,
        HWND_SUBLANG_ITEM7_ICON_TTX,
        HWND_SUBLANG_ITEM8_ICON_TTX,
        HWND_SUBLANG_ITEM9_ICON_TTX,
    };
    static  HWND _ZUI_TBLSEG _hwndHOHIcons[HKEY_SUBTITLE_PAGE_MAX_ITEM]=
    {
        HWND_SUBLANG_ITEM0_ICON_HOH,
        HWND_SUBLANG_ITEM1_ICON_HOH,
        HWND_SUBLANG_ITEM2_ICON_HOH,
        HWND_SUBLANG_ITEM3_ICON_HOH,
        HWND_SUBLANG_ITEM4_ICON_HOH,
        HWND_SUBLANG_ITEM5_ICON_HOH,
        HWND_SUBLANG_ITEM6_ICON_HOH,
        HWND_SUBLANG_ITEM7_ICON_HOH,
        HWND_SUBLANG_ITEM8_ICON_HOH,
        HWND_SUBLANG_ITEM9_ICON_HOH,
    };

    static  HWND _ZUI_TBLSEG _hwndHDIcons[HKEY_SUBTITLE_PAGE_MAX_ITEM]=
    {
        HWND_SUBLANG_ITEM0_ICON_HD,
        HWND_SUBLANG_ITEM1_ICON_HD,
        HWND_SUBLANG_ITEM2_ICON_HD,
        HWND_SUBLANG_ITEM3_ICON_HD,
        HWND_SUBLANG_ITEM4_ICON_HD,
        HWND_SUBLANG_ITEM5_ICON_HD,
        HWND_SUBLANG_ITEM6_ICON_HD,
        HWND_SUBLANG_ITEM7_ICON_HD,
        HWND_SUBLANG_ITEM8_ICON_HD,
        HWND_SUBLANG_ITEM9_ICON_HD,
    };

    U8 cur_page = u8SubtitleItemSelIdx/HKEY_SUBTITLE_PAGE_MAX_ITEM;
    U8 loop;
    for (loop=0; loop<HKEY_SUBTITLE_PAGE_MAX_ITEM; loop++)
    {
        U8 idx = cur_page*HKEY_SUBTITLE_PAGE_MAX_ITEM+loop;
        BOOLEAN bShowTTX = FALSE;
        BOOLEAN bShowHOH = FALSE;
        BOOLEAN bShowHD = FALSE;

        if (0 < idx && idx <= u8SubtitleMenuNum) //note: 0=off
        {
            switch(SubtitleMenu[idx - 1].u8SubtitleType)
            {
                case SUBTITLING_TYPE_TELETEXT:
                    bShowTTX = TRUE;
                    break;
                case SUBTITLING_TYPE_TELETEXT_HOH:
                    bShowTTX = TRUE;
                    bShowHOH = TRUE;
                    break;
                case SUBTITLING_TYPE_NORMAL_HD:
                    bShowHD = TRUE;
                    break;
                case SUBTITLING_TYPE_HH_NO:
                case SUBTITLING_TYPE_HH_4X3:
                case SUBTITLING_TYPE_HH_16X9:
                case SUBTITLING_TYPE_HH_221X100:
                    bShowHOH = TRUE;
                    break;
                case SUBTITLING_TYPE_HH_HD:
                    bShowHD = TRUE;
                    bShowHOH = TRUE;
                    break;
                default:
                    break;
            }
        }
        MApp_ZUI_API_ShowWindow(_hwndTTXIcons[loop], bShowTTX? SW_SHOW: SW_HIDE);
        MApp_ZUI_API_ShowWindow(_hwndHOHIcons[loop], bShowHOH? SW_SHOW: SW_HIDE);
        MApp_ZUI_API_ShowWindow(_hwndHDIcons[loop], bShowHD? SW_SHOW: SW_HIDE);
    }//end of for loop

}

static void _MApp_SubtitleLanguage_Init(void)
{
    //no ttx subtitle  no subtitle
    if ( u8SubtitleMenuNum == 0 )//20071205 Vincent.lin show subtitle(no video didn't mean no subtitle)(the same behavior as LG)  || (TRUE == MApp_Scramble_GetCurStatus()) )
    {
        //MApp_ZUI_API_SetFocus(HWND_SUBLANG_ITEM0); //set to "off" item
    }
    else
    {
        //check last time select
        MApp_TV_SearchLastSubtileLang();

        if(u8SubtitleItemSelIdx>u8SubtitleMenuNum)
            u8SubtitleItemSelIdx=0;

        MApp_ZUI_API_SetFocus(
            _MApp_ZUI_ACT_SubtitleLanguageIndexMapToWindow(
                u8SubtitleItemSelIdx%HKEY_SUBTITLE_PAGE_MAX_ITEM));
    }
    _MApp_SubtitleLanguage_RefreshIcons();
}


static void _MApp_SubtitleLanguage_KeyUp(void)
{
    //from void MApp_UiMenu2_DrawSubtitleScrUP(void)

    if (u8SubtitleMenuNum == 0)
    {
        //only one item: off
    }
    else if ((u8SubtitleItemSelIdx)% HKEY_SUBTITLE_PAGE_MAX_ITEM ==0)//for changing page
    {
        U8 prev_page = u8SubtitleItemSelIdx/HKEY_SUBTITLE_PAGE_MAX_ITEM;

        if(u8SubtitleItemSelIdx==0)
            u8SubtitleItemSelIdx = u8SubtitleMenuNum;
        else
            u8SubtitleItemSelIdx = u8SubtitleItemSelIdx-1    ;

        //check different page...
        if (prev_page != (u8SubtitleItemSelIdx/HKEY_SUBTITLE_PAGE_MAX_ITEM))
        {
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_SUBLANG_LIST_PANE);
        }

        MApp_ZUI_API_SetFocus(
            _MApp_ZUI_ACT_SubtitleLanguageIndexMapToWindow(
                u8SubtitleItemSelIdx%HKEY_SUBTITLE_PAGE_MAX_ITEM));
    }
    else
    {
        u8SubtitleItemSelIdx = u8SubtitleItemSelIdx-1;
        MApp_ZUI_API_SetFocus(
            _MApp_ZUI_ACT_SubtitleLanguageIndexMapToWindow(
                u8SubtitleItemSelIdx%HKEY_SUBTITLE_PAGE_MAX_ITEM));

    }
}

static void _MApp_SubtitleLanguage_KeyDown(void)
{
    //from void MApp_UiMenu2_DrawSubtitleScrDOWN(void)
    if (u8SubtitleMenuNum == 0)
    {
        //only one item: off
    }
    else if(u8SubtitleItemSelIdx==u8SubtitleMenuNum||
        ((u8SubtitleItemSelIdx+1)%HKEY_SUBTITLE_PAGE_MAX_ITEM)==0)
    {
        U8 prev_page = u8SubtitleItemSelIdx/HKEY_SUBTITLE_PAGE_MAX_ITEM;

        if(u8SubtitleItemSelIdx==u8SubtitleMenuNum)
            u8SubtitleItemSelIdx = 0;
        else
            u8SubtitleItemSelIdx = u8SubtitleItemSelIdx+1   ;

        //check different page...
        if (prev_page != (u8SubtitleItemSelIdx/HKEY_SUBTITLE_PAGE_MAX_ITEM))
        {
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_SUBLANG_LIST_PANE);
        }

        MApp_ZUI_API_SetFocus(
            _MApp_ZUI_ACT_SubtitleLanguageIndexMapToWindow(
                u8SubtitleItemSelIdx%HKEY_SUBTITLE_PAGE_MAX_ITEM));

    }
    else
    {
        u8SubtitleItemSelIdx = u8SubtitleItemSelIdx+1;
        MApp_ZUI_API_SetFocus(
            _MApp_ZUI_ACT_SubtitleLanguageIndexMapToWindow(
                u8SubtitleItemSelIdx%HKEY_SUBTITLE_PAGE_MAX_ITEM));
    }

}

extern LPTSTR MApp_ZUI_ACT_GetMenuLanguageStringByIndex(U8 u8Index);

static LPTSTR _MApp_SubtitleLanguage_MapFullLangName(U8 UI_Lang_IDX)
{
    U16 u16TempID;
    U32 u32StringCodes;
    U8 i=0;

    EN_SI_LANGUAGE enLang = msAPI_SI_GetLanguageByISO639LangCode((U8*)SubtitleMenu[UI_Lang_IDX].StringCodes);

    LPTSTR strLang = MApp_ZUI_ACT_GetMenuLanguageStringByIndex(MApp_GetLanguageBySILanguage(enLang));

    if(strLang)
    {
        return strLang;
    }

    for(i=0;i<4;i++)
    {
        SubtitleMenu[UI_Lang_IDX].StringCodes[i]= tolower((int)SubtitleMenu[UI_Lang_IDX].StringCodes[i]);
    }

    u32StringCodes =(SubtitleMenu[UI_Lang_IDX].StringCodes[0]<<24)
        +(SubtitleMenu[UI_Lang_IDX].StringCodes[1]<<16)
        +(SubtitleMenu[UI_Lang_IDX].StringCodes[2]<<8)
        +(SubtitleMenu[UI_Lang_IDX].StringCodes[3]<<0);

#if 0 // for debug subtitle display
    printf("u32StringCodes -->\n");
    for(i=0;i<4;i++)
    {
        printf("%c",SubtitleMenu[UI_Lang_IDX].StringCodes[i]);
    }
    printf("\n");
#endif
    switch(u32StringCodes)
    {
#if 0 // use msAPI_SI_GetLanguageByISO639LangCode

        case STRING_TO_U32('a','r','a'):
            u16TempID = en_str_Arabic;
            break;

        case STRING_TO_U32('b','u','l'):
            u16TempID = en_str_Bulgarian;
            break;

        case STRING_TO_U32('c','a','t'):
            u16TempID = en_str_Catalan;
            break;

        case STRING_TO_U32('c','r','o'):
            u16TempID = en_str_Hrvatski;
            break;

        case STRING_TO_U32('c','z','e'):
        case STRING_TO_U32('c','e','s'):
            u16TempID = en_str_Czech;
            break;

        case STRING_TO_U32('d','a','n'):
            u16TempID = en_str_Dansk;
            break;

        case STRING_TO_U32('d','u','t'):
        case STRING_TO_U32('n','l','d'):
            u16TempID = en_str_Nederlands;
            break;

        case STRING_TO_U32('e','n','g'):
            u16TempID = en_str_English;
            break;
#ifdef __MEL_SZ_FONT__
        case STRING_TO_U32('b','r','m'):
            u16TempID = en_str_Myanmar;
            break;
        case STRING_TO_U32('u','y','g'):
            u16TempID = en_str_Uyghur;
            break;
        case STRING_TO_U32('k','h','m'):
            u16TempID = en_str_Uyghur;
            break;
        case STRING_TO_U32('l','a','o'):
            u16TempID = en_str_Lao;
            break;
#else
        case STRING_TO_U32('b','r','m'):
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Myanmar", STRING_BUFFER_LENGTH);

        case STRING_TO_U32('k','h','m'):
        case STRING_TO_U32('u','y','g'):
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Uyghur", STRING_BUFFER_LENGTH);

        case STRING_TO_U32('l','a','o'):
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Lao", STRING_BUFFER_LENGTH);
#endif

        case STRING_TO_U32('f','i','n'):
            u16TempID = en_str_Suomi;
            break;

        case STRING_TO_U32('f','r','a'):
        case STRING_TO_U32('f','r','e'):
            u16TempID = en_str_France;
            break;

        case STRING_TO_U32('s','l','o'):
         u16TempID = en_str_Slovak;
         break;

        case STRING_TO_U32('g','e','r'):
        case STRING_TO_U32('d','e','u'):
            u16TempID = en_str_Deutsch;
            break;

        case STRING_TO_U32('g','l','a'):
        case STRING_TO_U32('g','a','e'):
        case STRING_TO_U32('g','l','g'):
            u16TempID = en_str_Gaelic;
            break;

        case STRING_TO_U32('g','l','e'):
            u16TempID = en_str_Irish;
            break;

        case STRING_TO_U32('g','r','e'):
        case STRING_TO_U32('e','l','l'):
            u16TempID = en_str_Greek;
            break;

        case STRING_TO_U32('h','r','v'):
            u16TempID = en_str_Hrvatski;
            break;

        case STRING_TO_U32('h','u','n'):
            u16TempID = en_str_Magyar;
            break;

        case STRING_TO_U32('i','t','a'):
            u16TempID = en_str_Italiano;
            break;

        case STRING_TO_U32('n','o','r'):
            u16TempID = en_str_Norsk;
            break;

        case STRING_TO_U32('p','o','l'):
            u16TempID = en_str_Polski;
            break;

        case STRING_TO_U32('p','o','r'):
            u16TempID = en_str_Portuguese;
            break;

        case STRING_TO_U32('r','o','m'):
            u16TempID = en_str_Romanian;
            break;

        case STRING_TO_U32('r','u','s'):
            u16TempID = en_str_Russian1;
            break;

        case STRING_TO_U32('s','l','v'):
            u16TempID = en_str_Slovene;
            break;

        case STRING_TO_U32('s','e','r'):
            u16TempID = en_str_Srpski;
            break;

        case STRING_TO_U32('s','p','a'):
            u16TempID = en_str_Spanish;
            break;

        case STRING_TO_U32('s','w','e'):
            u16TempID = en_str_Svenska;
            break;

        case STRING_TO_U32('c','h','i'):
        case STRING_TO_U32('z','h','o'):
            u16TempID = en_str_Chinese;
            break;

        case STRING_TO_U32('c','h','s'):
            u16TempID = en_str_SimpleChinese;
            break;

        case STRING_TO_U32('w','e','l'):
        case STRING_TO_U32('c','y','m'):
            u16TempID = en_str_Welsh;
            break;

        case STRING_TO_U32('q','a','a'):
            u16TempID = en_str_Qaa;
            break;

        case STRING_TO_U32('l','t','z'):
            u16TempID = en_str_Luxembourgish;
            break;

        case STRING_TO_U32('e','u','s'):
        case STRING_TO_U32('b','a','q'):
            u16TempID = en_str_Basque;
            break;

        case STRING_TO_U32('i','c','e'):
        case STRING_TO_U32('i','s','l'):
            u16TempID = en_str_Icelandic;
            break;

        case STRING_TO_U32('b','e','l'):
            u16TempID = en_str_Belarusian;
            break;

        case STRING_TO_U32('l','i','t'):
            u16TempID = en_str_Lithuanian;
            break;

        case STRING_TO_U32('u','k','r'):
            u16TempID = en_str_Ukranian;
            break;

        case STRING_TO_U32('l','a','v'):
            u16TempID = en_str_Latvian;
            break;

        case STRING_TO_U32('e','s','t'):
            u16TempID = en_str_Estonian;
            break;

       case STRING_TO_U32('h','e','b'):
            u16TempID = en_str_Hebrew;
            break;

       case STRING_TO_U32('t','u','r'):
            u16TempID = en_str_Turkish;
            break;

        case STRING_TO_U32('t','h','a'):
             u16TempID = en_str_Thailand;
             break;

        case STRING_TO_U32('s','g','a'):
            u16TempID = en_str_Sga;
            break;

        case STRING_TO_U32('c','m','n'):
            u16TempID = en_str_Mandarin;
            break;

        case STRING_TO_U32('y','u','e'):
            u16TempID = en_str_Cantonese;
            break;

        case STRING_TO_U32('k','o','r'):
            u16TempID = en_str_Korean;
            break;

        case STRING_TO_U32('j','p','n'):
            u16TempID = en_str_Japanese;
            break;

        case STRING_TO_U32('h','i','n'):
            u16TempID = en_str_Hindi;
            break;

#if 1//(ENABLE_COUNTRY_GHANA)
        case STRING_TO_U32('g','h','a'):
            u16TempID = en_str_Ghana;
            break;
#endif

        case STRING_TO_U32('m','a','o'):
            u16TempID = en_str_Maori;
            break;

        case STRING_TO_U32('i','n','d'):
            u16TempID = en_str_Indonesia;
            break;

        case STRING_TO_U32('s','w','a'):
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Swahili", STRING_BUFFER_LENGTH);

        case STRING_TO_U32('m','s','a'):
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Malay", STRING_BUFFER_LENGTH);

        case STRING_TO_U32('t','a','m'):
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Tamil", STRING_BUFFER_LENGTH);
#endif

        case STRING_TO_U32('m','u','l'):
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Multiple Language", STRING_BUFFER_LENGTH);

        default:
            u16TempID = en_str_Undefined;
            break;
    }

    return MApp_ZUI_API_GetString(u16TempID);
}


/////////////////////////////////////////////////////////////////////
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

void MApp_ZUI_ACT_AppShowSubtitleLanguage(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_SUBTITLE_LANGUAGE;

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
        ZUI_SUBTITLE_LANGUAGE_XSTART, ZUI_SUBTITLE_LANGUAGE_YSTART,
        ZUI_SUBTITLE_LANGUAGE_WIDTH, ZUI_SUBTITLE_LANGUAGE_HEIGHT);

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

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);

    _MApp_SubtitleLanguage_Init(); //after all item are created and shown...

#if (ENABLE_UI_3D_PROCESS)
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_RUNNING);
#else
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_LIST_SHOWUP, E_ZUI_STATE_RUNNING);
#endif
}


//////////////////////////////////////////////////////////
// Key Handler


BOOLEAN MApp_ZUI_ACT_ExecuteSubtitleLanguageAction(U16 act)
{

    switch(act)
    {
      #if 0
        case EN_EXE_CLOSE_SET_SUBTITLE:
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_SET_SUBTITLE, SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_SUBTITLE_LANG);
            return TRUE;
      #endif
        case EN_EXE_CLOSE_CURRENT_OSD:
        #if (ENABLE_UI_3D_PROCESS)
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
        #else
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
        #endif
            _enTargetState = STATE_OSDPAGE_CLEAN_UP;

      #if MHEG5_ENABLE
      #if (MHEG5_WITH_SUBTITLE==0)
            if(MApp_MHEG5_CheckGoMHEG5Process())
            {
            #if CIPLUS_MHEG_1_3
                if (msAPI_MHEG5_GoMHEGWhenSubtitleOn() == 0)
            #endif
                {
                    if((stGenSetting.g_SysSetting.fEnableSubTitle == EN_SUBTITILE_SYSTEM_ON) && u8SubtitleMenuNum && MApp_Subtitle_IsRunning() == TRUE)
                    {
                        if(msAPI_MHEG5_IsRunning())
                        {
                            MApp_MHEG5_Set_Display(FALSE,TRUE);
                            msAPI_MHEG5_SetRun(FALSE);
                        }
                    }
                    else if((stGenSetting.g_SysSetting.fEnableTTXSubTitle==TRUE)&& u8SubtitleMenuNum)
                    {
              #if (MHEG5_ENABLE)
                    #if (MHEG5_WITH_SUBTITLE==0)
                    if (MApp_MHEG5_CheckGoMHEG5Process())
                    {
                            MApp_MHEG5_Force_Exit();
                            MApp_MHEG5_SetGoMHEG5Process(FALSE);
                            msAPI_MHEG5_SetGoBackMHEG5(true);
                    }
                    #endif
                #endif
                    }
                    else if(stGenSetting.g_SysSetting.fEnableSubTitle == EN_SUBTITILE_SYSTEM_OFF)
                    {
                        if(!msAPI_MHEG5_IsRunning())
                        {
                            msAPI_MHEG5_SetRun(TRUE);
                            MApp_MHEG5_Set_Display(TRUE,TRUE);
                            MApi_GOP_GWIN_SwitchGOP( E_GOP_APP ); //sw to GOP1, Main OSD is on GOP1
                            MApi_GOP_GWIN_EnableTransClr((EN_GOP_TRANSCLR_FMT)0, FALSE);
                            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
                            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP,E_GOP_DST_OP0, g_MHEG5Video.stARCWin.u16H_DisStart,g_MHEG5Video.stARCWin.u16V_DisStart, MHEG_XRES, MHEG_YRES);
                            MApi_GOP_GWIN_Set_HSCALE(TRUE, MHEG_XRES, g_MHEG5Video.stARCWin.u16H_DisSize);
                            MApi_GOP_GWIN_Set_VSCALE(TRUE, MHEG_YRES, g_MHEG5Video.stARCWin.u16V_DisSize);
                            MApi_GOP_GWIN_SwitchGOP( E_GOP_OSD ); //sw to GOP1, Main OSD is on GOP1
                        }
                    }
                }
             }
      #endif
      #endif
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_SUBTITLE_LANG_UP:
        case EN_EXE_SUBTITLE_LANG_DOWN:
            if ((u8SubtitleMenuNum == 0)
              #if ENABLE_TTX
                && (FALSE == MApp_TTX_Is_EBUSubtitleExist(EN_TTX_SUBTITLE))
              #endif    //ENABLE_TTX
                )
            {   //No item
                return TRUE;
            }

            UI_Hotkey_Subtitle = TRUE;

            if(act == EN_EXE_SUBTITLE_LANG_UP)
            {
                _MApp_SubtitleLanguage_KeyUp();
            }
            else
            {
                _MApp_SubtitleLanguage_KeyDown();
            }
            if(u8SubtitleItemSelIdx != 0)
            {
                stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_ON;
            #if ENABLE_TTX  //ENABLE_TTX
                if(SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT
                    ||SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH)
                {
                    U8 Magazine = 0;
                    U8 Page = 0;
                    U16 u16Pid = 0;

                    //close the window and reopen it latter by the new parameters
                #if PVR_AND_TTX_DIFF_WITH_MHEG5
                    MApp_TTX_TurnTTXOnOff(TRUE);
                #endif  //PVR_AND_TTX_DIFF_WITH_MHEG5
                    MApp_TTX_TeletextCommand(TTX_TV);

                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=TRUE;
                    MApp_TTX_Subtitle_GetData((u8SubtitleItemSelIdx-1), &Magazine, &Page, &u16Pid);
                    MApp_TTX_SetSubtitleTTX_PID(u16Pid);
                #if ENABLE_PVR
                    if (MApp_PVR_IsPlaybacking())
                        MApp_TTX_SetDefaultTTX_PID(u16Pid);
                #endif  //ENABLE_PVR
                    MApp_TTX_SetSubtitlePage(((U16)Magazine<<8) | Page, 0xFFFF);
                    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx-1);  //set subtitle new index
                }
                else
            #endif  //ENABLE_TTX
                if(SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_HH_NO)
                {
                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
                    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx-1);
                }
                else
                {
                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
                    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx-1);
                }
            }
            else
            {
                stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
                stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_OFF;
                stGenSetting.g_SysSetting.fHardOfHearing = EN_SUBTITILE_SYSTEM_OFF;
            }
            _MApp_SubtitleLanguage_RefreshIcons();
#if 0
                if(IsTTX_Subtile && (u8SubtitleItemSelIdx==(TotalSutitleItem-1)))
                {
                    stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_ON;

                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=TRUE;
                    //MApp_DigitalTTX_SetSubtitleMode(pTTXInfo->u8TTXMagNum, pTTXInfo->u8TTXPageNum);

                }
                else if(u8SubtitleItemSelIdx!=0 &&(u8SubtitleItemSelIdx <= (TotalSutitleItem-1)))
                {
                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
                    stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_ON;
                    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx-1);
                    //save current selected subtitle lang
                    MApp_UiMenuFunc_SaveSelectSubtileLang();

                }
                else
                {

                    stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
                    stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_OFF;
                }
#endif
            return TRUE;

    }
    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_HandleSubtitleLanguageKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_SUBLANG_LIST_PANE, 0);

    switch(key)
    {
        case VK_EXIT:
            MApp_ZUI_ACT_ExecuteSubtitleLanguageAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;
        case VK_POWER:
            MApp_ZUI_ACT_ExecuteSubtitleLanguageAction(EN_EXE_POWEROFF);
            return TRUE;
        case VK_SELECT:
            MApp_ZUI_API_SetTimer(HWND_SUBLANG_BOTTOM_HALF_OK_BTN, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_SUBLANG_BOTTOM_HALF_OK_BTN);
            break;
        /*case VK_EXIT:
            MApp_ZUI_API_SetTimer(HWND_MENU_BOTTOM_HALF_EXIT_BG, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_BOTTOM_HALF_EXIT_BG);
            break;
        case VK_UP:
            MApp_ZUI_API_SetTimer(HWND_SUBLANG_BOTTOM_HALF_UP_BTN, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_SUBLANG_BOTTOM_HALF_UP_BTN);
            break;
        case VK_DOWN:
            MApp_ZUI_API_SetTimer(HWND_SUBLANG_BOTTOM_HALF_DOWN_BTN, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_SUBLANG_BOTTOM_HALF_DOWN_BTN);
            break;
        case VK_LEFT:
            MApp_ZUI_API_SetTimer(HWND_SUBLANG_BOTTOM_HALF_LEFT_BTN, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_SUBLANG_BOTTOM_HALF_LEFT_BTN);
            break;
        case VK_RIGHT:
            MApp_ZUI_API_SetTimer(HWND_SUBLANG_BOTTOM_HALF_RIGHT_BTN, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_SUBLANG_BOTTOM_HALF_RIGHT_BTN);
            break;*/

        default:
            break;

    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateSubtitleLanguage(void)
{
    ZUI_MSG(printf("[]term:sublang\n");)
    MApp_OSDPage_SetState(_enTargetState);
}
LPTSTR MApp_ZUI_ACT_GetSubtitleLanguageDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_SUBLANG_ITEM0_TEXT:
        case HWND_SUBLANG_ITEM1_TEXT:
        case HWND_SUBLANG_ITEM2_TEXT:
        case HWND_SUBLANG_ITEM3_TEXT:
        case HWND_SUBLANG_ITEM4_TEXT:
        case HWND_SUBLANG_ITEM5_TEXT:
        case HWND_SUBLANG_ITEM6_TEXT:
        case HWND_SUBLANG_ITEM7_TEXT:
        case HWND_SUBLANG_ITEM8_TEXT:
        case HWND_SUBLANG_ITEM9_TEXT:
            //from case SUBTITLE_LAG_0_TEXT:
            {
                U8 idx = _MApp_ZUI_ACT_SubtitleLanguageWindowMapToIndex(hwnd)+
                    HKEY_SUBTITLE_PAGE_MAX_ITEM*(u8SubtitleItemSelIdx/HKEY_SUBTITLE_PAGE_MAX_ITEM);

                if(idx ==0 )
                {
                    if ( u8SubtitleMenuNum!=0 )
                        u16TempID=en_str_Off;
                    else
                        u16TempID=Empty;
                }
                /*/ZUI: unused path:
                else if( (IsTTX_Subtile) && (u8SubtitleItemSelIdx == u8SubtitleServiceNum+1))
                {
                    TTxMapFull_Lang_Name(TTxIDx,&u16TempID);
                }*/
                else if( idx <= u8SubtitleMenuNum)
                {
                    return _MApp_SubtitleLanguage_MapFullLangName(idx-1);
                }
            }
            break;
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

void MApp_ZUI_ACT_Subtitle_Toggle(BOOLEAN bEnable)
{
    if(bEnable == FALSE)
    {
        UI_Hotkey_Subtitle = TRUE;
        stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
        stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_OFF;
        stGenSetting.g_SysSetting.fHardOfHearing = EN_SUBTITILE_SYSTEM_OFF;
    }
    else
    {
        stGenSetting.g_SysSetting.fEnableTTXSubTitle=TRUE;
        stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_ON;
        stGenSetting.g_SysSetting.fHardOfHearing = EN_SUBTITILE_SYSTEM_ON;
    }
}

/////////////////////////////////////////////////////////
// Customize Window Procedures

/*
S32 MApp_ZUI_ACT_SubtitleLanguageListWinProc(HWND hwnd, PMSG msg)
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
#endif
#undef MAPP_ZUI_ACTSUBLANG_C
