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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTCHLIST_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
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
#include "MApp_ZUI_GlobalFunction.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_ChList_Main.h"
#include "MApp_OSDPage_Main.h"

#include "MApp_SaveData.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ChannelList.h"
#include "msAPI_Memory.h"
#include "msAPI_ChProc.h"
#if (ENABLE_ATSC)
  #include "MApp_ChannelProc_ATSC.h"
  #include "msAPI_Timer.h"
#endif
#include "MApp_GlobalFunction.h"
#include "MApp_TV.h"
#if(ENABLE_CI)
#include "MApp_CIMMI.h"
#include "msAPI_OpCache.h"
#endif
#include "MApp_Scan.h"
#if (ENABLE_DTV)
#include "mapp_demux.h"
#include "mapp_si.h"
#endif

#ifdef ENABLE_SELECT_NONESEARCH_CH
#include "MApp_TV.h"
#endif

#include "MApp_ChannelChange.h"

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#include "MApp_TTS_Cus_Say.h"
#endif

#if ENABLE_S2
#include "MApp_ZUI_ACTchlist.h"

extern void msAPI_CM_SetCurrentPositionAfterSort(WORD CurrentS2idx, WORD CurrentS2ServiceID, MEMBER_SERVICETYPE bServiceType);
extern VOID msAPI_CM_QuickSortService(MEMBER_SERVICETYPE bServiceType);
#endif
#include <string.h>
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
#include "MApp_DataBase_ATSC.h"
#endif
/////////////////////////////////////////////////////////////////////

static EN_OSDPAGE_STATE _enTargetState;

#if (ENABLE_ARABIC_OSD)
extern BOOLEAN ArabicCHStringFlag;
#endif

extern EN_CHLIST_MODE _eChannelListMode;
#if ENABLE_DVB
extern BOOLEAN MApp_CharTable_GetServiceNameToUCS2(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD * bChannelName, U8 ControlCodes);
#endif
static void _MApp_ZUI_ACT_Chlist_GetTotalProgCount(U8 u8ServiceType);
#if (ENABLE_PVR)
extern BOOLEAN MApp_ZUI_ACT_PVR_Check_Switch_Channel(MEMBER_SERVICETYPE NewCMType, U16 u16NewPos);
#endif
#if 0//NTV_FUNCTION_ENABLE //TODO
static U8 u8TotalNetWorkNum=0;
#endif
//*************************************************************************
//              Defines
//*************************************************************************
#define CHANNEL_LIST_PAGE_NUM          10
#define SIMILAR_LIST_PAGE_NUM          5
#define RECENT_LIST_PAGE_NUM           5
#define CH_LIST_CURRENT_CN_TEXT_COLOR      0x00FF00
#define CH_LIST_CURRENT_CN_TEXT_HL_COLOR   0x0000FF
#define CH_LIST_CURRENT_CN_TEXT_DISABLE_COLOR   0x808080
#define CH_LIST_CURRENT_CN_TEXT_HL_DISABLE_COLOR   0xF0F0F0

#define ENABLE_XL3_API 0

#define CHLIST_MARQUEE_INITIAL_INTERVAL_MS 1500
#define CHLIST_MARQUEE_ITEM (MApp_ZUI_API_GetFocus()+4)

#if ENABLE_XL3_API
#define SIZE_CHLIST_CHECK_BUF       (MAX_ATVPROGRAM+MAX_DTVPROGRAM)
U8 _pu8ChListCheckBuf[SIZE_CHLIST_CHECK_BUF];

#define IS_CHECK_CH(x)             (_pu8ChListCheckBuf[x])
#define SET_CHECK_CH(x,y)          _pu8ChListCheckBuf[x] = y
#endif

typedef enum
{
    CHANNEL_LIST_COMMAND_INIT,
    CHANNEL_LIST_COMMAND_UP,
    CHANNEL_LIST_COMMAND_DOWN,
    CHANNEL_LIST_COMMAND_PRVPAGE,
    CHANNEL_LIST_COMMAND_NEXTPAGE,
} EN_CHANNEL_LIST_COMMAND_TYPE;

typedef enum
{
    FAVORITE_LIST_COMMAND_INIT,
    FAVORITE_LIST_COMMAND_UP,
    FAVORITE_LIST_COMMAND_DOWN,
    FAVORITE_LIST_COMMAND_PRVPAGE,
    FAVORITE_LIST_COMMAND_NEXTPAGE,
} EN_FAVORITE_LIST_COMMAND_TYPE;

#if ENABLE_CI_PLUS
static U8 _u8OpMenuCurrentPage = 0;
static U8 u16OpMenuChCountOfCurPage = 0;

static  HWND _ZUI_TBLSEG _OpChannelListScrambleHwndList[CHANNEL_LIST_PAGE_NUM]=
{
    HWND_CHLIST_ITEM0_SCRAMBLE,
    HWND_CHLIST_ITEM1_SCRAMBLE,
    HWND_CHLIST_ITEM2_SCRAMBLE,
    HWND_CHLIST_ITEM3_SCRAMBLE,
    HWND_CHLIST_ITEM4_SCRAMBLE,
    HWND_CHLIST_ITEM5_SCRAMBLE,
    HWND_CHLIST_ITEM6_SCRAMBLE,
    HWND_CHLIST_ITEM7_SCRAMBLE,
    HWND_CHLIST_ITEM8_SCRAMBLE,
    HWND_CHLIST_ITEM9_SCRAMBLE,
};

typedef enum
{
    OPMENU_LIST_COMMAND_INIT,
    OPMENU_LIST_COMMAND_UP,
    OPMENU_LIST_COMMAND_DOWN,
    OPMENU_LIST_COMMAND_PRVPAGE,
    OPMENU_LIST_COMMAND_NEXTPAGE,
} EN_OPMENU_LIST_COMMAND_TYPE;
#endif
#if(ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
typedef enum
{
    FINDPROBYNAME_LIST_COMMAND_UP,
    FINDPROBYNAME_LIST_COMMAND_DOWN,
    FINDPROBYNAME_LIST_COMMAND_PRVPAGE,
    FINDPROBYNAME_LIST_COMMAND_NEXTPAGE,
} EN_FINDPROBYNAME_LIST_COMMAND_TYPE;
#endif
/********************************************************************************/
/*                    Macro                                                     */
/********************************************************************************/
#define CHANNEL_LIST_DBINFO(y)      //y
#define FAVORITE_LIST_DBINFO(y)     //y

#define RECENT_LIST_DBINFO(y)       //y
#define OPProfile_DBINFO(y)         //y

#define DEBUG_CH_LIST(x)            //x

/********************************************************************************/
/*                      Local                                                   */
/********************************************************************************/
//U8 m_au8OpProfileListMatchIndex[MAX_OP_CACHE_NUM] = {0};

typedef struct _CHANNEL_LIST_DATA_STRUCT
{
#if ENABLE_S2
    U16    u8CurrentPage;
#else
    U8  u8CurrentPage;
#endif
    U8  u8ServiceType;
    U16 u16ChCountOfCurPage;  //total channel count of current page
    U16 u16CurCh;
    U16 u16PageListIndex[CHANNEL_LIST_PAGE_NUM];
    U16 u16TotalChCount;  //total channel numer of database

} CHANNEL_LIST_DATA_STRUCT;

static CHANNEL_LIST_DATA_STRUCT * pChListData = NULL;
#if ENABLE_DTV
extern BOOLEAN gu8VerChange;
#endif

U16 MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(U8 u8VisIndex);

///////////////////////////////////////////////////////////////////////

#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))  // MTC_ADD_FIX
#define PROGRAMNAME_MAXLENGTH_CHLIST    11
static void _MApp_FindProByNameList_Init(U8 u8ServiceType);
MS_U8 u8ProgName_chlist[PROGRAMNAME_MAXLENGTH_CHLIST];
static MS_U8 u8ProgNameCharNum_chlist = 0;
static MS_BOOL bIsExtendChar_chlist = FALSE;
static MS_BOOL bIsCaptalChar_chlist = TRUE;
typedef struct _softkeypaddata
{
    HWND   hWnd;
    MS_U8  normalchar;
    MS_U8  normalcapschar;
    MS_U8  extendchar;
    MS_U8  extendcapschar;
}SOFTKEYPAD_DATA_CHLIST;
static SOFTKEYPAD_DATA_CHLIST softkey_chlist[]=
{
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_1,'a','A',0xE0,0xC0},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_2,'b','B',0xE1,0xC1},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_3,'c','C',0xE2,0xC2},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_4,'d','D',0xE3,0xC3},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_5,'e','E',0xE4,0xC4},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_6,'f','F',0xE5,0xC5},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_7,'g','G',0xE6,0xC6},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_8,'h','H',0xE7,0xC7},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_9,'i','I',0xE8,0xC8},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_10,'j','J',0xE9,0xC9},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_11,'k','K',0xEA,0xCA},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_12,'l','L',0xEB,0xCB},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_13,'m','M',0xEC,0xCC},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_14,'n','N',0xED,0xCD},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_15,'o','O',0xEE,0xCE},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_16,'p','P',0xEF,0xCF},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_17,'q','Q',0xF0,0xD0},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_18,'r','R',0xF1,0xD1},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_19,'s','S',0xF2,0xD2},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_20,'t','T',0xF3,0xD3},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_21,'u','U',0xF4,0xD4},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_22,'v','V',0xF5,0xD5},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_23,'w','W',0xF6,0xD6},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_24,'x','X',0xF7,0xD7},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_25,'y','Y',0xF8,0xD8},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_26,'z','Z',0xF9,0xD9},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_27,'<','0',0xFA,0xDA},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_28,'>','1',0xFB,0xDB},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_29,'.','2',0xFC,0xDC},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_30,'|','3',0xFD,0xDD},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_31,'@','4',0xFE,0xDE},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_32,'$','5',0xFF,0xDF},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_33,'/','6','0','8'},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_34,'%','7','1','9'},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_35,'\'','8','2','<'},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_36,'(','9','3','>'},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_37,')','!','4',':'},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_38,'_','?','5',';'},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_39,'-','#','6','\"'},
    {HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_40,'+',',','7','*'},
    {0,0,0,0,0}
};
static MS_U8 _Chlist_softkeyboard_dispchar(HWND hWnd)
{
    MS_U8 u8Index = 0;
    MS_U8 u8Char = 0;
    while (softkey_chlist[u8Index].hWnd >0 )
    {
        if (softkey_chlist[u8Index].hWnd == hWnd)
        {
            if (bIsExtendChar_chlist)
            {
                if (bIsCaptalChar_chlist)
                {
                    u8Char = softkey_chlist[u8Index].extendcapschar;
                }
                else
                {
                    u8Char = softkey_chlist[u8Index].extendchar;
                }
            }
            else
            {
                if (bIsCaptalChar_chlist)
                {
                    u8Char = softkey_chlist[u8Index].normalcapschar;
                }
                else
                {
                    u8Char=softkey_chlist[u8Index].normalchar;
                }
            }
            break;
        }
        u8Index ++;
    }
    return u8Char;
}
extern U8 UTL_strlen1(const char *pStr);
static LPTSTR _Chlist_softkeyboard_dynamictext(HWND hWnd)
{
    MS_U8 u8Str[2] = {0};
    u8Str[0] = _Chlist_softkeyboard_dispchar(hWnd);
    MApp_ZUI_API_StringBuffU8toU16( CHAR_BUFFER, (MS_U8*)u8Str,UTL_strlen1((char *)u8Str));
    return CHAR_BUFFER;
}

static MS_BOOL _Chlist_HandleSoftkeyboardkey(VIRTUAL_KEY_CODE key)
{
    MS_BOOL  eRetval = FALSE;
    switch(key)
    {
        case VK_MENU:
        case VK_EXIT:
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHLIST_SOFTKEYBOARD, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_TRANSPARENT_BG, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_CHLIST_ITEM0);
            eRetval = TRUE;
            break;
        case VK_SELECT:
        {
            HWND TempFocus = MApp_ZUI_API_GetFocus();
            switch(TempFocus)
            {
                case HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_EXTEND:
                    bIsExtendChar_chlist= !bIsExtendChar_chlist;
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_CHLIST_SOFTKEYBOARD);
                    return TRUE;
                case HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_CAPSON:
                    bIsCaptalChar_chlist= !bIsCaptalChar_chlist;
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_CHLIST_SOFTKEYBOARD);
                    return TRUE;
                case HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_BACKSPACE:
                    if (u8ProgNameCharNum_chlist > 0)
                    {
                        u8ProgNameCharNum_chlist--;
                        u8ProgName_chlist[u8ProgNameCharNum_chlist] = 0;
                        MApp_ZUI_API_InvalidateWindow(HWND_MENU_CHLIST_SOFTKEYBOARD_TITLE_M);
                    }
                    break;
                case HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_OK:
                    MApp_ZUI_API_ShowWindow(HWND_CHLIST_TRANSPARENT_BG, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_CHLIST_ITEM0);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHLIST_SOFTKEYBOARD, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_SHOW);
                    return TRUE;
                default:
                    break;
            }

            if (TempFocus >= HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_1 && TempFocus <= HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_40)
            {
                 if (u8ProgNameCharNum_chlist < PROGRAMNAME_MAXLENGTH_CHLIST-1)
                 {
                    u8ProgName_chlist[u8ProgNameCharNum_chlist] = _Chlist_softkeyboard_dispchar(TempFocus);
                    u8ProgNameCharNum_chlist++;
                    MApp_ZUI_API_InvalidateWindow(HWND_MENU_CHLIST_SOFTKEYBOARD_TITLE_M);
                 }
            }
            else if (TempFocus == HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_CANCEL)
            {
                if (u8ProgNameCharNum_chlist< PROGRAMNAME_MAXLENGTH_CHLIST-1)
                {
                    u8ProgName_chlist[u8ProgNameCharNum_chlist] = 0x20;
                    u8ProgNameCharNum_chlist++;

                    MApp_ZUI_API_InvalidateWindow(HWND_MENU_CHLIST_SOFTKEYBOARD_TITLE_M);
                 }
            }

            if(pChListData->u8ServiceType == E_SERVICETYPE_RADIO)
            {
                _MApp_FindProByNameList_Init(E_SERVICETYPE_UNITED_TV);
            }
            else if(pChListData->u8ServiceType == E_SERVICETYPE_DATA)
            {
                _MApp_FindProByNameList_Init(E_SERVICETYPE_UNITED_TV);
            }
            else
            {
                _MApp_FindProByNameList_Init(E_SERVICETYPE_UNITED_TV);
            }

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            eRetval = TRUE;
            break;
        }
        default:
            eRetval = FALSE;
            break;
    }
    return eRetval;
}

#endif

static  HWND _ZUI_TBLSEG _ChannelListHwndList[CHANNEL_LIST_PAGE_NUM]=
{
    HWND_CHLIST_ITEM0,
    HWND_CHLIST_ITEM1,
    HWND_CHLIST_ITEM2,
    HWND_CHLIST_ITEM3,
    HWND_CHLIST_ITEM4,
    HWND_CHLIST_ITEM5,
    HWND_CHLIST_ITEM6,
    HWND_CHLIST_ITEM7,
    HWND_CHLIST_ITEM8,
    HWND_CHLIST_ITEM9,
};

static void _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(HWND hwnd, BOOLEAN bEnable)
{
    //note: if enable, try to check string length is long enough, and then start animation
    //          if disable, stop and clear to normal status
    if (hwnd != HWND_INVALID)
    {
        GUI_DATA_MARQUEE_VARDATA *pData =
            (GUI_DATA_MARQUEE_VARDATA*)MApp_ZUI_API_GetWindowData(hwnd);

        if (pData == NULL)
        {
            return;
        }

        if (bEnable)
        {
            pData->u8ShowStartPosition = 0;
            MApp_ZUI_API_SetTimer(hwnd, 0, CHLIST_MARQUEE_INITIAL_INTERVAL_MS);

        }
        else
        {
            pData->u8ShowStartPosition = 0xFF;
            MApp_ZUI_API_KillTimer(hwnd, 0);
        }
        MApp_ZUI_API_InvalidateWindow(hwnd);
    }
}

static U8 _MApp_ZUI_ACT_ChannelListWindowMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < CHANNEL_LIST_PAGE_NUM; i++)
    {
        if (hwnd == _ChannelListHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_ChannelListHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_ChannelListIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= CHANNEL_LIST_PAGE_NUM)
        return HWND_INVALID;
    return _ChannelListHwndList[u8Index];

}


#if (ENABLE_ATSC)

#define HWND_FAVLIST_LIST_PANE HWND_CHLIST_LIST_PANE


const HWND _ZUI_TBLSEG _FavoriteListHwndList[10]=
{
    HWND_CHLIST_ITEM0,
    HWND_CHLIST_ITEM1,
    HWND_CHLIST_ITEM2,
    HWND_CHLIST_ITEM3,
    HWND_CHLIST_ITEM4,
    HWND_CHLIST_ITEM5,
    HWND_CHLIST_ITEM6,
    HWND_CHLIST_ITEM7,
    HWND_CHLIST_ITEM8,
    HWND_CHLIST_ITEM9,
};

#endif //ENABLE_ATSC

static BOOLEAN _MApp_ZUI_ACT_IsFavMode(void)
{
    return (/*_eChannelListMode == MODE_CHLIST_RADIO_FAV ||*/
            _eChannelListMode == MODE_CHLIST_TV_FAV);
}

#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
static BOOLEAN _MApp_ZUI_ACT_IsFindProByNameMode(void)
{
    return (_eChannelListMode == MODE_CHLIST_FIND_BYNAME);
}
#endif

#if ENABLE_CI_PLUS
BOOLEAN _MApp_ZUI_ACT_IsOpProfileMenuMode(void)
{
    if((MApp_CI_IsOpMode()==FALSE)&&(IsDTVInUse())&&
      (MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN)))
    {
       return TRUE;
    }
    return FALSE;
}
///////////////////////////////////////////////////////////////////////
// from MApp_ChannelList.c
static void _MApp_OpMenuList_Handler (U16 u16ActiveProgOrder, U16 u16ShiftProgIndex, U16 u16TotalSrvCount, U8 u8SrvCommand)
{
    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(MApp_ZUI_API_GetFocus());
    U8 u8TotalOpNum = u16TotalSrvCount;
    UNUSED(u16ActiveProgOrder);
    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,FALSE);
    if(u16TotalSrvCount == 0)
    {
        return;
    }
    switch (u8SrvCommand)
    {
        case OPMENU_LIST_COMMAND_INIT:
        {
            _u8OpMenuCurrentPage = 0;
            pChListData->u8CurrentPage = u16ActiveProgOrder / CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_SetFocus(HWND_CHLIST_ITEM0);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            if ( ((u8TotalOpNum-1) / CHANNEL_LIST_PAGE_NUM) > _u8OpMenuCurrentPage)
            {
                u16OpMenuChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            }
            else
            {
                u16OpMenuChCountOfCurPage = ((u8TotalOpNum % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u8TotalOpNum % CHANNEL_LIST_PAGE_NUM));
            }
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;

        case OPMENU_LIST_COMMAND_UP:
        {
            if (u16SrvPageCurIndex >= u16ShiftProgIndex)
            {
                //in the same page movement
                u16SrvPageCurIndex -= u16ShiftProgIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                return;
            }
            if (_u8OpMenuCurrentPage == 0)
            {
                // first page
                _u8OpMenuCurrentPage= (u8TotalOpNum - 1) / CHANNEL_LIST_PAGE_NUM;
                u16OpMenuChCountOfCurPage = ((u8TotalOpNum % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u8TotalOpNum % CHANNEL_LIST_PAGE_NUM));
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16OpMenuChCountOfCurPage - 1));
                if (u8TotalOpNum > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                return;
            }
            // move to prev page
            _u8OpMenuCurrentPage--;
            u16OpMenuChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            u16SrvPageCurIndex = (u16SrvPageCurIndex + CHANNEL_LIST_PAGE_NUM - u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;

        case OPMENU_LIST_COMMAND_DOWN:
        {
            U16 u16PageLastIndex;

            CHANNEL_LIST_DBINFO(printf("\r\n [OpMenuList Handler]u16SrvPageCurIndex = %d,u16ShiftProgIndex = %d,u16OpMenuChCountOfCurPage=%d",
                u16SrvPageCurIndex,u16ShiftProgIndex,u16OpMenuChCountOfCurPage));

            if ((u16SrvPageCurIndex+u16ShiftProgIndex) < u16OpMenuChCountOfCurPage)
            {
                //in the same page movement
                u16SrvPageCurIndex += u16ShiftProgIndex;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                return;
            }
            u16PageLastIndex = (_u8OpMenuCurrentPage * CHANNEL_LIST_PAGE_NUM) + u16OpMenuChCountOfCurPage;
            if (u16PageLastIndex == u8TotalOpNum)
            {
                //move to first page
                _u8OpMenuCurrentPage = 0;
                u16OpMenuChCountOfCurPage = (u8TotalOpNum > CHANNEL_LIST_PAGE_NUM) ? CHANNEL_LIST_PAGE_NUM : u8TotalOpNum;
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                printf("\r\n should focus to the first item!!\n");
                if (u8TotalOpNum > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                return;
            }
            //move to next page
            _u8OpMenuCurrentPage++;
            if ( ((u8TotalOpNum-1) / CHANNEL_LIST_PAGE_NUM) > _u8OpMenuCurrentPage )
            {
                u16OpMenuChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            }
            else
            {
                u16OpMenuChCountOfCurPage = ((u8TotalOpNum % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u8TotalOpNum % CHANNEL_LIST_PAGE_NUM));
            }
            u16SrvPageCurIndex = (u16SrvPageCurIndex + u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
            CHANNEL_LIST_DBINFO(printf("\r\n [OpMenuList Handler]u16SrvPageCurIndex = %d,u16ShiftProgIndex = %d,u16OpMenuChCountOfCurPage=%d,_u8OpMenuCurrentPage = %d",
            u16SrvPageCurIndex,u16ShiftProgIndex,u16OpMenuChCountOfCurPage,_u8OpMenuCurrentPage));
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;

        case OPMENU_LIST_COMMAND_PRVPAGE:
        {
            if (_u8OpMenuCurrentPage == 0)
            {
                if (u16SrvPageCurIndex > 0)
                {
                    //focus the first item
                    MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                    return;
                }
                else
                {
                    //move to last page last item
                    _u8OpMenuCurrentPage = (u8TotalOpNum - 1) / CHANNEL_LIST_PAGE_NUM;
                    u16OpMenuChCountOfCurPage = ((u8TotalOpNum % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u8TotalOpNum % CHANNEL_LIST_PAGE_NUM));
                    u16SrvPageCurIndex = u16OpMenuChCountOfCurPage - 1;
                    MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                    if (u8TotalOpNum > CHANNEL_LIST_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                    }
                    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                    return;
                }
            }
            _u8OpMenuCurrentPage--;
            u16OpMenuChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;

        case OPMENU_LIST_COMMAND_NEXTPAGE:
        {
            U8 u8LastPage;
            u8LastPage = (u8TotalOpNum - 1) / CHANNEL_LIST_PAGE_NUM;
            if (u8LastPage == _u8OpMenuCurrentPage)
            {
                //the last page
                if (u16SrvPageCurIndex == (u16OpMenuChCountOfCurPage-1))
                {
                    //the last item, move to first page
                    _u8OpMenuCurrentPage = 0;
                    u16OpMenuChCountOfCurPage = (u8TotalOpNum > CHANNEL_LIST_PAGE_NUM) ? CHANNEL_LIST_PAGE_NUM : u8TotalOpNum;
                    MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                    if (u8TotalOpNum > CHANNEL_LIST_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                    }
                    else
                    {
                    }
                    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                    return;
                }
                else
                {
                    //focus the last item
                    u16SrvPageCurIndex = u16OpMenuChCountOfCurPage - 1;
                    MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                    return;
                }
            }
            //move to next page
            _u8OpMenuCurrentPage++;
            if (u8LastPage > _u8OpMenuCurrentPage)
            {
                u16OpMenuChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            }
            else
            {
                u16OpMenuChCountOfCurPage = ((u8TotalOpNum % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u8TotalOpNum % CHANNEL_LIST_PAGE_NUM));
            }
            if (u16SrvPageCurIndex >= u16OpMenuChCountOfCurPage)
            {
                u16SrvPageCurIndex = u16OpMenuChCountOfCurPage - 1;
            }
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;
    }
}
#endif

static void _MApp_ChannelList_Handler (U16 u16ActiveProgOrder, U16 u16ShiftProgIndex, U16 u16TotalSrvCount, U8 u8SrvCommand)
{
    DEBUG_CH_LIST( printf("_MApp_ChannelList_Handler(u16ActiveProgOrder=%u,u16ShiftProgIndex=%u, u16TotalSrvCount=%u, u8SrvCommand=%u\n",
            u16ActiveProgOrder, u16ShiftProgIndex, u16TotalSrvCount, u8SrvCommand ); );

    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(MApp_ZUI_API_GetFocus());
    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,FALSE);
    switch (u8SrvCommand)
    {
        case CHANNEL_LIST_COMMAND_INIT:
        {
            pChListData->u8CurrentPage = u16ActiveProgOrder / CHANNEL_LIST_PAGE_NUM;
            u16SrvPageCurIndex = u16ActiveProgOrder % CHANNEL_LIST_PAGE_NUM;
            DEBUG_CH_LIST( printf("pChListData->u8CurrentPage=%u\n", pChListData->u8CurrentPage); );
            DEBUG_CH_LIST( printf("u16SrvPageCurIndex=%u\n", u16SrvPageCurIndex); );

            if (u16TotalSrvCount == 0)
            {
                MApp_ZUI_API_SetFocus(HWND_INVALID);
            }
        #if (!ENABLE_ATSC)
            else if(IsATVInUse() &&
                msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_ATV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) ==0)
            {
                  pChListData->u8CurrentPage=0;
                  MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));

            }
        #endif
            else
            {
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            }

            //u16SrvPagePrvIndex = u16SrvPageCurIndex;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            if ( ((u16TotalSrvCount-1) / CHANNEL_LIST_PAGE_NUM) > pChListData->u8CurrentPage )
            {
                pChListData->u16ChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            }
            else
            {
                pChListData->u16ChCountOfCurPage = ((u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM));
            }
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
            DEBUG_CH_LIST( printf("pChListData->u16ChCountOfCurPage=%u\n", pChListData->u16ChCountOfCurPage); );

        }
        break;

        case CHANNEL_LIST_COMMAND_UP:
        {
            if (u16SrvPageCurIndex >= u16ShiftProgIndex)
            {
                //in the same page movement
                u16SrvPageCurIndex -= u16ShiftProgIndex;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                return;
            }
            if (pChListData->u8CurrentPage == 0)
            {
                // first page
                _MApp_ZUI_ACT_Chlist_GetTotalProgCount(pChListData->u8ServiceType);
                u16TotalSrvCount = pChListData->u16TotalChCount;
                pChListData->u8CurrentPage= (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
                pChListData->u16ChCountOfCurPage = ((u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM));
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(pChListData->u16ChCountOfCurPage - 1));
                if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                return;
            }
            // move to prev page
            pChListData->u8CurrentPage--;
            pChListData->u16ChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            u16SrvPageCurIndex = (u16SrvPageCurIndex + CHANNEL_LIST_PAGE_NUM - u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;

        case CHANNEL_LIST_COMMAND_DOWN:
        {
            U16 u16PageLastIndex;

            if ((u16SrvPageCurIndex+u16ShiftProgIndex) < pChListData->u16ChCountOfCurPage)
            {
                //in the same page movement
                u16SrvPageCurIndex += u16ShiftProgIndex;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                return;
            }
            u16PageLastIndex = (pChListData->u8CurrentPage * CHANNEL_LIST_PAGE_NUM) + pChListData->u16ChCountOfCurPage;
            if (u16PageLastIndex == u16TotalSrvCount)
            {
                //move to first page
                _MApp_ZUI_ACT_Chlist_GetTotalProgCount(pChListData->u8ServiceType);
                u16TotalSrvCount = pChListData->u16TotalChCount;
                pChListData->u8CurrentPage = 0;
                pChListData->u16ChCountOfCurPage = (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM) ? CHANNEL_LIST_PAGE_NUM : u16TotalSrvCount;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));

                if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                return;
            }
            //move to next page
            _MApp_ZUI_ACT_Chlist_GetTotalProgCount(pChListData->u8ServiceType);
            u16TotalSrvCount = pChListData->u16TotalChCount;
            pChListData->u8CurrentPage++;
            if ( ((u16TotalSrvCount-1) / CHANNEL_LIST_PAGE_NUM) > pChListData->u8CurrentPage )
            {
                pChListData->u16ChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            }
            else
            {
                pChListData->u16ChCountOfCurPage = ((u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM));
            }
            u16SrvPageCurIndex = (u16SrvPageCurIndex + u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;

        case CHANNEL_LIST_COMMAND_PRVPAGE:
        {
            if (pChListData->u8CurrentPage == 0)
            {
                if (u16SrvPageCurIndex > 0)
                {
                    //focus the first item
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                    return;
                }
                else
                {
                    //move to last page last item
                    _MApp_ZUI_ACT_Chlist_GetTotalProgCount(pChListData->u8ServiceType);
                    u16TotalSrvCount = pChListData->u16TotalChCount;
                    pChListData->u8CurrentPage= (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
                    pChListData->u16ChCountOfCurPage = ((u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM));
                    u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                    if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                    }
                    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                    return;
                }
            }
            pChListData->u8CurrentPage--;
            pChListData->u16ChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            //ZUI: u8SrvPageBehavior = CHANNEL_LIST_OSDEVENT_REDRAW;
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;

        case CHANNEL_LIST_COMMAND_NEXTPAGE:
        {
#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
            U16 u8LastPage;
#else
            U8 u8LastPage;
#endif
            _MApp_ZUI_ACT_Chlist_GetTotalProgCount(pChListData->u8ServiceType);
            u16TotalSrvCount = pChListData->u16TotalChCount;
            u8LastPage = (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
            if (u8LastPage == pChListData->u8CurrentPage)
            {
                //the last page
                if (u16SrvPageCurIndex == (pChListData->u16ChCountOfCurPage-1))
                {
                    //the last item, move to first page
                    pChListData->u8CurrentPage = 0;
                    pChListData->u16ChCountOfCurPage = (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM) ? CHANNEL_LIST_PAGE_NUM : u16TotalSrvCount;
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                    if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                    }
                    else
                    {
                    }
                    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                    return;
                }
                else
                {
                    //focus the last item
                    u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                    _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
                    return;
                }
            }
            //move to next page
            pChListData->u8CurrentPage++;
            if (u8LastPage > pChListData->u8CurrentPage)
            {
                pChListData->u16ChCountOfCurPage = CHANNEL_LIST_PAGE_NUM;
            }
            else
            {
                pChListData->u16ChCountOfCurPage = ((u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM) == 0 ? CHANNEL_LIST_PAGE_NUM : (u16TotalSrvCount % CHANNEL_LIST_PAGE_NUM));
            }
            if (u16SrvPageCurIndex >= pChListData->u16ChCountOfCurPage)
            {
                u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
            }
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,TRUE);
        }
        break;
    }
}

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
void MApp_Channel_ChSetting_Disp_Init(void)
{
    MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
    MApp_DB_ATSC_LoadChSetting(&stChSettingDisp[ANT_AIR]);
    MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
    MApp_DB_ATSC_LoadChSetting(&stChSettingDisp[ANT_CATV]);
    MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
}
#endif

static void _MApp_ChannelList_Init(U8 u8ServiceType)
{
    BOOLEAN bVisibleFlag = false;

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    MApp_Channel_ChSetting_Disp_Init();
#endif

    DEBUG_CH_LIST( PRINT_CURRENT_LINE(); );
    DEBUG_CH_LIST( printf("_MApp_ChannelList_Init: u8ServiceType=%bu\n", (U8)u8ServiceType); );

    pChListData->u8ServiceType = u8ServiceType;

    CHANNEL_LIST_DBINFO(printf("_MApp_ChannelList_Init: u8ServiceType=%bu\n", (U8)u8ServiceType));

  #if ENABLE_CI_PLUS
    if(MApp_CI_IsOpMode()==TRUE)
    {
      pChListData->u16TotalChCount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+
      msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    }
    else
  #endif
    {
      #if (ENABLE_ATSC)
        if (IsAtscInUse() || IsATVInUse())
        {
        #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
            pChListData->u16TotalChCount = stChSettingDisp[ANT_AIR].u16MainListSrvNum + stChSettingDisp[ANT_CATV].u16MainListSrvNum;
        #else
            pChListData->u16TotalChCount = stChSetting.u16MainListSrvNum;
        #endif
        }
        else
      #endif
        {
            pChListData->u16TotalChCount = msAPI_CHPROC_CM_CountProgram((MEMBER_SERVICETYPE)u8ServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        }
    }
    //printf("UI_MApp_ChannelList_Init: u8ServiceType=%bu, count = %u\n", (U8)u8ServiceType, pChListData->u16TotalChCount);

  #if (ENABLE_ATSC)
    // Fix Mantis 875179, because ATSC get program index API is different
    if (IsAtscInUse() || IsATVInUse())
    {
       pChListData->u16CurCh = MApp_ChanProc_GetCurProgIndex();   // Get current program index.
       pChListData->u16CurCh = pChListData->u16CurCh - 1;         // ATSC valid index is from 1, but channel list index is from 0
    }
    else
  #endif
    {
        pChListData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal((MEMBER_SERVICETYPE)u8ServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        DEBUG_CH_LIST( printf("VISIBLE_ONLY  pChListData->u16CurCh=%u\n", pChListData->u16CurCh); );

      #if ENABLE_SBTVD_ATV_SYSTEM
        if(msAPI_ATV_GetCurrentAntenna() == ANT_AIR)
      #endif
        {
            U16 u16CurChTmp;
            u16CurChTmp = msAPI_CHPROC_CM_GetCurrentOrdinal((MEMBER_SERVICETYPE)u8ServiceType, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
            DEBUG_CH_LIST( printf("INCLUDE_NOT_VISIBLE  u16CurChTmp=%u\n", u16CurChTmp); );

            msAPI_CHPROC_CM_GetAttributeOfOrdinal( (MEMBER_SERVICETYPE)u8ServiceType, u16CurChTmp, &bVisibleFlag, E_SERVICE_ATTR_VISIBLE, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO );

//            msAPI_CHPROC_CM_GetAttributeOfOrdinal( (MEMBER_SERVICETYPE)u8ServiceType, pChListData->u16CurCh, &bVisibleFlag, E_SERVICE_ATTR_VISIBLE, E_PROGACESS_INCLUDE_VISIBLE_ONLY );

            if ( !bVisibleFlag )
            {
                pChListData->u16CurCh = 0;
            }
            if (pChListData->u16CurCh >= pChListData->u16TotalChCount)
            {
                pChListData->u16CurCh = 0;
            }
            if ((pChListData->u16TotalChCount > 0) && (pChListData->u16CurCh == INVALID_ORDINAL))
            {
                pChListData->u16CurCh = 0;
            }
            else if (pChListData->u16TotalChCount == 0)
            {
                pChListData->u16CurCh = 0;
            }
        }
    }

    #if(!DVB_T_C_DIFF_DB && ENABLE_DVB)
        if((DB_PROGRAM_SOURCE_TYPE != UI_INPUT_SOURCE_TYPE) && (UI_INPUT_SOURCE_ATV != UI_INPUT_SOURCE_TYPE))
        {
            pChListData->u16CurCh = 0;
            pChListData->u16TotalChCount = 0;
        }
    #endif

    printf("pChListData->u16TotalChCount=%u\n", pChListData->u16TotalChCount);
    printf("pChListData->u16CurCh=%u\n", pChListData->u16CurCh);

    //CHANNEL_LIST_DBINFO(printf("pChListData->u16TotalChCount=%u\n", pChListData->u16TotalChCount));
    //CHANNEL_LIST_DBINFO(printf("pChListData->u16CurCh=%u\n", pChListData->u16CurCh));

    _MApp_ChannelList_Handler(pChListData->u16CurCh, 0, pChListData->u16TotalChCount, CHANNEL_LIST_COMMAND_INIT);

#if ENABLE_XL3_API
    memset(_pu8ChListCheckBuf, 0, SIZE_CHLIST_CHECK_BUF);
#endif
}

///////////////////////////////////////////////////////////////////////
//for favorite list

static U16 _MApp_FavoriteList_GetOnePagePositionByPageNum(EN_SERVICE_TYPE enType, U16 u16List[], U8 u8WhichPage)
{
    U8 u8Page = 0;
    U16 u16Count = 0, u16FavoriteCount = 0, u16Ptr = 0;
    U16 u16Position = 0, list_i = 0;

    FAVORITE_LIST_DBINFO(printf("_MApp_FavoriteList_GetOnePagePositionByPageNum\n"););
    for (list_i=0; list_i<CHANNEL_LIST_PAGE_NUM; list_i++)
    {
        u16List[list_i] = CHANNEL_LIST_INVALID_PROGINDEX;
    }

  #if (ENABLE_ATSC)
    if (IsAtscInUse() || IsATVInUse())
    {
        u16FavoriteCount = stChSetting.u16FavListSrvNum;
    }
    else
  #endif
    {
        u16FavoriteCount = msAPI_CHPROC_CM_CountFavoriteProgram((MEMBER_SERVICETYPE)enType);
    }
    FAVORITE_LIST_DBINFO(printf("   u16FavoriteCount=%u\n", u16FavoriteCount););
    if (u16FavoriteCount == 0)
    {
        return u16Count;
    }

    list_i = 0;

  #if (ENABLE_ATSC)
    if (IsAtscInUse() || IsATVInUse())
    {
        u16Position =  MApp_ChanProc_GetFirstFavoriteOrdinal();
    }
    else
  #endif
    {
        u16Position = msAPI_CHPROC_CM_GetFirstFavoriteOrdinal((MEMBER_SERVICETYPE)enType, TRUE);
    }

    do
    {
        if (u8Page == u8WhichPage)
        {
            u16List[list_i] = u16Position;
            FAVORITE_LIST_DBINFO(printf("   u16List[%u]=%u\n", list_i, u16List[list_i]););
            list_i++;
            u16Count++;
            if (list_i >= CHANNEL_LIST_PAGE_NUM)
            {
                // list filled
                break;
            }

          #if (ENABLE_ATSC)
            if (IsAtscInUse() || IsATVInUse())
            {
                u16Position =  MApp_ChanProc_GetNextFavoriteOrdinal(u16Position);
            }
            else
          #endif
            {
                u16Position = msAPI_CHPROC_CM_GetNextFavoriteOrdinal((MEMBER_SERVICETYPE)enType, u16Position, TRUE);
            }
        }
        else
        {
            list_i++;
            if (list_i == CHANNEL_LIST_PAGE_NUM)
            {
                list_i = 0;
                u8Page++;
            }

          #if (ENABLE_ATSC)
            if (IsAtscInUse() || IsATVInUse())
            {
                u16Position =  MApp_ChanProc_GetNextFavoriteOrdinal(u16Position);
            }
            else
          #endif
            {
                u16Position = msAPI_CHPROC_CM_GetNextFavoriteOrdinal((MEMBER_SERVICETYPE)enType, u16Position, TRUE);
            }
        }
        u16Ptr++;
    } while (u16Ptr < u16FavoriteCount);

    return u16Count;
}

static void _MApp_FavoriteList_Handler(U16 u16ActiveProgOrder, U16 u16ShiftProgIndex, U16 u16TotalSrvCount, U8 u8SrvCommand)
{
    FAVORITE_LIST_DBINFO( printf("UI_MApp_FavoriteList_Init: u8ServiceType=%bu\n", u8SrvCommand); );

    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(MApp_ZUI_API_GetFocus());

    switch (u8SrvCommand)
    {
        case FAVORITE_LIST_COMMAND_INIT:
        {
            pChListData->u8CurrentPage = u16ActiveProgOrder / CHANNEL_LIST_PAGE_NUM;
            u16SrvPageCurIndex = u16ActiveProgOrder % CHANNEL_LIST_PAGE_NUM;
            if (u16TotalSrvCount == 0)
                MApp_ZUI_API_SetFocus(HWND_INVALID);
            else
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
        }
        break;

        case FAVORITE_LIST_COMMAND_UP:
        {
            if (u16SrvPageCurIndex >= u16ShiftProgIndex)
            {
                //in the same page movement
                u16SrvPageCurIndex -= u16ShiftProgIndex;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                return;
            }
            if (pChListData->u8CurrentPage == 0)
            {
                //first page, move to last page
                pChListData->u8CurrentPage= (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
              #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
                pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
              #else
                pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
              #endif
                u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                return;
            }
            //move to prev page
            pChListData->u8CurrentPage--;
            pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
            u16SrvPageCurIndex = (u16SrvPageCurIndex + CHANNEL_LIST_PAGE_NUM - u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
        }
        break;

        case FAVORITE_LIST_COMMAND_DOWN:
        {
            U16 u16PageLastIndex;
            if ((u16SrvPageCurIndex+u16ShiftProgIndex) < pChListData->u16ChCountOfCurPage)
            {
                //in the same page movement
                u16SrvPageCurIndex += u16ShiftProgIndex;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                return;
            }
            u16PageLastIndex = (pChListData->u8CurrentPage * CHANNEL_LIST_PAGE_NUM) + pChListData->u16ChCountOfCurPage;
            if (u16PageLastIndex == u16TotalSrvCount)
            {
                //move to first page
                pChListData->u8CurrentPage = 0;
                pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                return;
            }
            //move to next page
            pChListData->u8CurrentPage++;
            pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
            u16SrvPageCurIndex = (u16SrvPageCurIndex + u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
        }
        break;

        case FAVORITE_LIST_COMMAND_PRVPAGE:
        {
            if (pChListData->u8CurrentPage == 0)
            {
                if (u16SrvPageCurIndex > 0)
                {
                    //focus the first item
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                    return;
                }
                else
                {
                    //move to last page last item
                    pChListData->u8CurrentPage= (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
                    pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
                    u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                    if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                    }
                    return;
                }
            }
            pChListData->u8CurrentPage--;
            pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
            if (u16SrvPageCurIndex >= pChListData->u16ChCountOfCurPage)
            {
                u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
            }
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
        }
        break;

        case FAVORITE_LIST_COMMAND_NEXTPAGE:
        {
          #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
            U16 u8LastPage = (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
          #else
            U8 u8LastPage = (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
          #endif
            if (u8LastPage == pChListData->u8CurrentPage)
            {
                //the last page
                if (u16SrvPageCurIndex == (pChListData->u16ChCountOfCurPage-1))
                {
                    //the last item, move to first page
                    pChListData->u8CurrentPage = 0;
                    pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                    if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                    }
                    else
                    {
                    }
                    return;
                }
                else
                {
                    //focus the last item
                    u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                    return;
                }
            }
            //move to next page
            pChListData->u8CurrentPage++;
            pChListData->u16ChCountOfCurPage = _MApp_FavoriteList_GetOnePagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex, pChListData->u8CurrentPage);
            if (u16SrvPageCurIndex >= pChListData->u16ChCountOfCurPage)
            {
                u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
            }
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
        }
        break;
    }
}

static void _MApp_FavoriteList_Init(U8 u8ServiceType)
{
    FAVORITE_LIST_DBINFO( printf("UI_MApp_FavoriteList_Init: u8ServiceType=%bu\n", u8ServiceType); );

    U16 u16Index,u16Ordinal;
    BOOLEAN bFind = FALSE;

    FAVORITE_LIST_DBINFO( printf("_eChannelListMode=%u\n", _eChannelListMode); );

    pChListData->u8ServiceType = u8ServiceType;


#if (ENABLE_ATSC)
    if (IsAtscInUse() || IsATVInUse())
    {
        MApp_ChanProc_GetTotalFavFromMainList();
        pChListData->u16TotalChCount = stChSetting.u16FavListSrvNum;
        pChListData->u16CurCh =  MApp_ChanProc_GetCurProgIndex();   // Get current program index.
        pChListData->u16CurCh = pChListData->u16CurCh  - 1;         // ATSC valid index is from 1, but channel list index is from 0
        u16Ordinal = MApp_ChanProc_GetFirstFavoriteOrdinal();
    }
    else
#endif
    {
        pChListData->u16TotalChCount = msAPI_CHPROC_CM_CountFavoriteProgram((MEMBER_SERVICETYPE)pChListData->u8ServiceType);
        FAVORITE_LIST_DBINFO(printf("pChListData->u16TotalChCount=%u\n", pChListData->u16TotalChCount); );

        pChListData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal((MEMBER_SERVICETYPE)u8ServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        FAVORITE_LIST_DBINFO(printf("pChListData->u16CurCh=%u\n", pChListData->u16CurCh); );

        u16Ordinal = msAPI_CHPROC_CM_GetFirstFavoriteOrdinal(E_SERVICETYPE_UNITED_TV, TRUE);
        FAVORITE_LIST_DBINFO(printf("u16Ordinal=%u\n", u16Ordinal); );
    }

    for( u16Index=0; u16Index < pChListData->u16TotalChCount; u16Index++ )
    {
        if(pChListData->u16CurCh == u16Ordinal)
        {
            pChListData->u16CurCh = u16Ordinal;
            bFind = TRUE;
            break;
        }
        else
        {
        #if (ENABLE_ATSC)
            if (IsAtscInUse() || IsATVInUse())
            {
                u16Ordinal = MApp_ChanProc_GetNextFavoriteOrdinal(u16Ordinal);
            }
            else
        #endif
            {
                u16Ordinal = msAPI_CHPROC_CM_GetNextFavoriteOrdinal(E_SERVICETYPE_UNITED_TV, u16Ordinal, TRUE);
            }
        }
    }

    if(!bFind)
    {   // when current program not set Favorite program, set focus to position 0 on Favorite List page.
#if (ENABLE_ATSC)
        if (IsAtscInUse() || IsATVInUse())
        {
            MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
            pChListData->u16CurCh = MApp_ChanProc_GetFirstFavoriteOrdinal();
            MApp_ChanProc_SetMainListProgIndex(pChListData->u16CurCh + 1);
            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
        }
        else
#endif
        {
            pChListData->u16CurCh = msAPI_CHPROC_CM_GetFirstFavoriteOrdinal(E_SERVICETYPE_UNITED_TV, TRUE);
        }
        u16Index = 0; // reset
    }

    FAVORITE_LIST_DBINFO(printf("pChListData->u16TotalChCount=%u\n", pChListData->u16TotalChCount));
    FAVORITE_LIST_DBINFO(printf("pChListData->u16CurCh=%u\n", pChListData->u16CurCh));

    _MApp_FavoriteList_Handler(u16Index, 0, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_INIT);

}


///////////////////////////////////////////////////////////////////////
#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
extern WORD msAPI_CHPROC_CM_CountFindProgramByName(MEMBER_SERVICETYPE bServiceType,BYTE *bProgramName) ;
extern WORD msAPI_CHPROC_CM_GetNextFindProgramByNameOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped,BYTE *bProgramName);
extern WORD msAPI_CHPROC_CM_GetPrevFindProgramByNameOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped,BYTE *bProgramName);

static U16 _MApp_FindPriBynameList_GetLastPagePositionByPageNum(EN_SERVICE_TYPE enType, U16 u16List[])
{
    U16 u16Count = 0, u16FindCount = 0, u16Ptr = 0;
    U16 u16Position = 0;
    int list_i = 0;

    for (list_i=0; list_i<CHANNEL_LIST_PAGE_NUM; list_i++)
    {
        u16List[list_i] = CHANNEL_LIST_INVALID_PROGINDEX;
    }

    u16FindCount = pChListData->u16TotalChCount;

    if (u16FindCount == 0)
    {
        return u16Count;
    }

    u16Position = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED)
            + msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, EXCLUDE_NOT_VISIBLE_AND_DELETED)
            + msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    list_i = ((pChListData->u16TotalChCount % CHANNEL_LIST_PAGE_NUM) - 1);
    do
    {
        u16Position = msAPI_CHPROC_CM_GetPrevFindProgramByNameOrdinal((MEMBER_SERVICETYPE)enType, u16Position, TRUE, u8ProgName_chlist);
        u16List[list_i] = u16Position;
        list_i--;
        u16Count++;
        if (list_i < 0)
        {
            // list filled
            break;
        }
        u16Ptr++;
    } while (u16Ptr < u16FindCount);

    return u16Count;
}

static U16 _MApp_FindPriBynameList_GetPrevPagePositionByPageNum(EN_SERVICE_TYPE enType, U16 u16List[])
{
    U16 u16Count = 0, u16FindCount = 0, u16Ptr = 0;
    U16 u16Position = 0;
    int list_i = 0;
    U16 u16NextPageLastPosition = u16List[0];

    for (list_i=0; list_i<CHANNEL_LIST_PAGE_NUM; list_i++)
    {
        u16List[list_i] = CHANNEL_LIST_INVALID_PROGINDEX;
    }

    u16FindCount = pChListData->u16TotalChCount;
    if (u16FindCount == 0)
    {
        return u16Count;
    }

    u16Position = u16NextPageLastPosition;
    list_i = CHANNEL_LIST_PAGE_NUM - 1;
    do
    {
        u16Position = msAPI_CHPROC_CM_GetPrevFindProgramByNameOrdinal((MEMBER_SERVICETYPE)enType, u16Position, TRUE, u8ProgName_chlist);
        u16List[list_i] = u16Position;
        printf("prve page return match u16Position = %d\n", u16Position);
        list_i--;
        u16Count++;
        if (list_i < 0)
        {
            // list filled
            break;
        }
        u16Ptr++;
    } while (u16Ptr < u16FindCount);

    return u16Count;
}

static U16 _MApp_FindPriBynameList_GetFirstPagePositionByPageNum(EN_SERVICE_TYPE enType, U16 u16List[])
{
    U16 u16Count = 0, u16FindCount = 0, u16Ptr = 0;
    U16 u16Position = 0, list_i = 0;

    for (list_i = 0; list_i < CHANNEL_LIST_PAGE_NUM; list_i++)
    {
        u16List[list_i] = CHANNEL_LIST_INVALID_PROGINDEX;
    }

    u16FindCount = pChListData->u16TotalChCount;

    if (u16FindCount == 0)
    {
        return u16Count;
    }

    u16Position = 0;
    list_i = 0;
    do
    {
        u16Position = msAPI_CHPROC_CM_GetNextFindProgramByNameOrdinal((MEMBER_SERVICETYPE)enType, u16Position, TRUE, u8ProgName_chlist);
        u16List[list_i] = u16Position;
        list_i++;
        u16Count++;
        if (list_i >= CHANNEL_LIST_PAGE_NUM)
        {
            // list filled
            break;
        }
        u16Ptr++;
    } while (u16Ptr < u16FindCount);

    return u16Count;
}

static U16 _MApp_FindPriBynameList_GetNextPagePositionByPageNum(EN_SERVICE_TYPE enType, U16 u16List[])
{
    U16 u16Count = 0, u16FindCount = 0, u16Ptr = 0;
    U16 u16Position = 0, list_i = 0;
    U16 u16PrevPageLastPosition = u16List[CHANNEL_LIST_PAGE_NUM - 1];

    for (list_i = 0; list_i < CHANNEL_LIST_PAGE_NUM; list_i++)
    {
        u16List[list_i] = CHANNEL_LIST_INVALID_PROGINDEX;
    }

    u16FindCount = pChListData->u16TotalChCount;

    if (u16FindCount == 0)
    {
        return u16Count;
    }

    u16Position = u16PrevPageLastPosition;
    list_i = 0;
    do
    {
        u16Position = msAPI_CHPROC_CM_GetNextFindProgramByNameOrdinal((MEMBER_SERVICETYPE)enType, u16Position, TRUE, u8ProgName_chlist);
        u16List[list_i] = u16Position;
        list_i++;
        u16Count++;
        if (list_i >= CHANNEL_LIST_PAGE_NUM)
        {
            // list filled
            break;
        }
        u16Ptr++;
    } while (u16Ptr < u16FindCount);

    return u16Count;
}

static void _MApp_FindProByNameList_Init(U8 u8ServiceType)
{
  //  BOOLEAN bFind = FALSE;
    pChListData->u8ServiceType = u8ServiceType;
    pChListData->u16TotalChCount = msAPI_CHPROC_CM_CountFindProgramByName((MEMBER_SERVICETYPE)pChListData->u8ServiceType,u8ProgName_chlist);
    pChListData->u16CurCh = 0; // reset
    pChListData->u8CurrentPage = 0;
    pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetFirstPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
    printf("\r\nssssssu8ServiceType=%d,ChCount=%d,CountOfCurPage=%d",u8ServiceType,pChListData->u16TotalChCount,pChListData->u16ChCountOfCurPage);
}

static void _MApp_FindProByNameList_Handler(U16 u16ActiveProgOrder, U16 u16ShiftProgIndex, U16 u16TotalSrvCount, U8 u8SrvCommand)
{
    u16ActiveProgOrder  = u16ActiveProgOrder;
    U8 u16SrvPageCurIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(      MApp_ZUI_API_GetFocus());
    switch (u8SrvCommand)
    {
        case FINDPROBYNAME_LIST_COMMAND_UP:
        {
            if (u16SrvPageCurIndex >= u16ShiftProgIndex)
            {
                //in the same page movement
                u16SrvPageCurIndex -= u16ShiftProgIndex;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                return;
            }
            //first page, move to last page
            if (pChListData->u8CurrentPage == 0)
            {
                pChListData->u8CurrentPage= (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;

                pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetLastPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);

                u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                return;
            }
            //move to first page
            if (pChListData->u8CurrentPage == 1)
            {
                //move to first page
                pChListData->u8CurrentPage = 0;
                pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetFirstPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);

                u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                return;
            }
            //move to prev page
            pChListData->u8CurrentPage--;
            pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetPrevPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
            u16SrvPageCurIndex = (u16SrvPageCurIndex + CHANNEL_LIST_PAGE_NUM - u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
        }
        break;

        case FINDPROBYNAME_LIST_COMMAND_DOWN:
        {
            U16 u16PageLastIndex;
            if ((u16SrvPageCurIndex+u16ShiftProgIndex) < pChListData->u16ChCountOfCurPage)
            {
                //in the same page movement
                u16SrvPageCurIndex += u16ShiftProgIndex;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                return;
            }
            u16PageLastIndex = (pChListData->u8CurrentPage * CHANNEL_LIST_PAGE_NUM) + pChListData->u16ChCountOfCurPage;
            //last page, move to first page
            if (u16PageLastIndex == u16TotalSrvCount)
            {
                pChListData->u8CurrentPage = 0;
                pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetFirstPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
                return;
            }
            //move to last page
            if(pChListData->u8CurrentPage == ((u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM - 1))
            {
                pChListData->u8CurrentPage++;
                pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetLastPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
                u16SrvPageCurIndex = (u16SrvPageCurIndex + u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                return;
            }
            //move to next page
            pChListData->u8CurrentPage++;
            pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetNextPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
            u16SrvPageCurIndex = (u16SrvPageCurIndex + u16ShiftProgIndex) % CHANNEL_LIST_PAGE_NUM;
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
        }
        break;

        case FINDPROBYNAME_LIST_COMMAND_PRVPAGE:
        {
            if (pChListData->u8CurrentPage == 0)
            {
                if (u16SrvPageCurIndex > 0)
                {
                    //focus the first item
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                    return;
                }
                else
                {
                    //first page, move to last page last item
                    pChListData->u8CurrentPage= (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
                    pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetLastPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
                    u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                    if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                    }
                    return;
                }
            }
            // move to first page
            if (pChListData->u8CurrentPage == 1)
            {
                pChListData->u8CurrentPage = 0;
                pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetFirstPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
                u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                return;
            }
            //move to prev page
            pChListData->u8CurrentPage--;
            pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetPrevPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
        }
        break;

        case FINDPROBYNAME_LIST_COMMAND_NEXTPAGE:
        {
            U16 u8LastPage = (u16TotalSrvCount - 1) / CHANNEL_LIST_PAGE_NUM;
            if (u8LastPage == pChListData->u8CurrentPage)
            {
                //the last page
                if (u16SrvPageCurIndex == (pChListData->u16ChCountOfCurPage-1))
                {
                    //the last page, move to first page
                    pChListData->u8CurrentPage = 0;
                    pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetFirstPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                    if (u16TotalSrvCount > CHANNEL_LIST_PAGE_NUM)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                    }
                    else
                    {
                    }
                    return;
                }
                else
                {
                    //focus the last item
                    u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
                    MApp_ZUI_API_SetFocus(
                        _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
                    return;
                }
            }
            //move to last page
            if (u8LastPage - 1 == pChListData->u8CurrentPage)
            {
                pChListData->u8CurrentPage++;
                pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetLastPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
                MApp_ZUI_API_SetFocus(
                    _MApp_ZUI_ACT_ChannelListIndexMapToWindow(0));
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                return;
            }
            //move to next page
            pChListData->u8CurrentPage++;
            pChListData->u16ChCountOfCurPage = _MApp_FindPriBynameList_GetNextPagePositionByPageNum((EN_SERVICE_TYPE)pChListData->u8ServiceType, pChListData->u16PageListIndex);
            if (u16SrvPageCurIndex >= pChListData->u16ChCountOfCurPage)
            {
                u16SrvPageCurIndex = pChListData->u16ChCountOfCurPage - 1;
            }
            MApp_ZUI_API_SetFocus(
                _MApp_ZUI_ACT_ChannelListIndexMapToWindow(u16SrvPageCurIndex));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
        }
        break;
    }
}
#endif

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

#if 0//ENABLE_S2
extern void MApp_ChannelChange_DisableChannel (BOOLEAN u8IfStopDsmcc, SCALER_WIN eWindow /*U8 u8ChanBufIdx*/ ); //for change channel
extern void MApp_ChannelChange_EnableChannel (SCALER_WIN eWindow);
#endif


void MApp_ZUI_ACT_AppShowChannelList(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_CHANNEL_LIST;
  #if ENABLE_CI_PLUS
    U8 u8OpNum = MApp_CI_GetOpCacheCount(); //Evie++:get num of op index
  #endif
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


    //RECT_SET(rect, ((g_IPanel.HStart()+3)&0xFFFC), 1, g_IPanel.Width(), g_IPanel.Height());
    RECT_SET(rect,
        ZUI_CHANNEL_LIST_XSTART, ZUI_CHANNEL_LIST_YSTART,
        ZUI_CHANNEL_LIST_WIDTH, ZUI_CHANNEL_LIST_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    //////////////////////////////
    // init internal data structre, before ZUI create message...
    if( pChListData )
    {
        _ZUI_FREE(pChListData);
    }

    pChListData = (CHANNEL_LIST_DATA_STRUCT*)_ZUI_MALLOC(
        sizeof(CHANNEL_LIST_DATA_STRUCT));
    if (pChListData == 0)
    {
        ZUI_DBG_FAIL(printf("[ZUI]ACHLIST\n"));
        ABORT();
        return;
    }
    //////////////////////////////

#if (ENABLE_ARABIC_OSD)
    ArabicCHStringFlag = TRUE;
#endif

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

#if ENABLE_ATSC_TTS
    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Channel_List), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Channel_List)));
    MApp_TTSControlSetOn(TRUE);
#endif

    switch (_eChannelListMode)
    {
        /*case MODE_CHLIST_RADIO_FAV:
            _MApp_FavoriteList_Init(SERVICE_TYPE_RADIO);
            break;
            */


        case MODE_CHLIST_TV_FAV:
            {
              #if ENABLE_SBTVD_ATV_SYSTEM
              if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                _MApp_FavoriteList_Init(SERVICE_TYPE_ATV);
              else
              #endif
                _MApp_FavoriteList_Init(SERVICE_TYPE_TV);
            }
            break;

    /*
        case MODE_CHLIST_RADIO:
            _MApp_ChannelList_Init(SERVICE_TYPE_RADIO);
            break;
*/

        case MODE_CHLIST_TV:
          #if ENABLE_SBTVD_ATV_SYSTEM
            if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                _MApp_ChannelList_Init(SERVICE_TYPE_ATV);
            else
                _MApp_ChannelList_Init(SERVICE_TYPE_TV);
          #else
            _MApp_ChannelList_Init(SERVICE_TYPE_TV);
          #endif
            break;


    #if 0//ENABLE_S2//ENABLE_QSORT_SERVICE
        case MODE_CHLIST_S2://ryan mark here
          #if(ENABLE_S2_PREDIT_SWITCH_LIST)
            if(msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_RADIO)
                _MApp_ChannelList_Init(E_SERVICETYPE_RADIO);
            else if(msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_DATA)
                _MApp_ChannelList_Init(E_SERVICETYPE_DATA);
            else
                _MApp_ChannelList_Init(E_SERVICETYPE_DTV);
          #else
            _MApp_ChannelList_Init(SERVICE_TYPE_TV);
          #endif
            break;
    #endif


    #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
        case MODE_CHLIST_FIND_BYNAME:
           break;
    #endif

    #if  0//NTV_FUNCTION_ENABLE //TODO
        case MODE_NETWORK_CHLIST_TV:
        {
            U8 k;
            u8TotalNetWorkNum = 0;

            for(k=0;k<MAX_NETWOEK_NUMBER;k++)
            {
                if(msAPI_CM_IS_NorwegianNetwork(k))
                {
                    u8TotalNetWorkNum++;
                }
            }
            //printf(">>>>>>>>>>>> xxxxxxx  MODE_NETWORK_CHLIST_TV\n");

            //_MApp_ChannelList_Init(SERVICE_TYPE_TV);

        }
            break;
    #endif
    }

  #if ENABLE_CI_PLUS
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE,SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN,SW_HIDE); //OP Menu
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);//Exit OP
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN,SW_HIDE);//Enter OP
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_MENU_BOTTOM_HALF_DELETE_PROFILE_BTN,SW_HIDE);//Delete Profile
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE,SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_PANE,SW_HIDE);
    if((u8OpNum>0)&&(MApp_CI_IsOpMode()==FALSE)&&IsDTVInUse())
    {
       MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN,SW_SHOW); //show OP Menu button
    }
    else if((u8OpNum>0)&&(MApp_CI_IsOpMode()==TRUE)&&IsDTVInUse())
    {
       MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_SHOW); //show exit OP button
    }
  #else
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE,SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN,SW_HIDE); //OP Menu
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);//Exit OP
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN,SW_HIDE);//Enter OP
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_MENU_BOTTOM_HALF_DELETE_PROFILE_BTN,SW_HIDE);//Delete Profile
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE,SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_PANE,SW_HIDE);
  #endif

  #if ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(ENABLE_ATSC)||(UI_SKIN_960X540X565== UI_SKIN_SEL))
    MApp_ZUI_API_ShowWindow(HWND_MENU_CHLIST_SOFTKEYBOARD, SW_HIDE);
  #endif

  #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(ENABLE_ATSC)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))//ENABLE_QSORT_SERVICE
    if(IsS2InUse())
    {
        MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_CHANNEL_LIST_OPTIONLIST_SORT_PAGE, SW_HIDE);
      #if ENABLE_CI_PLUS
        MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN,SW_HIDE); //OP Menu
        MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);//Exit OP
      #endif
    }
    else
    {
        MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_CHANNEL_LIST_OPTIONLIST_SORT_PAGE, SW_HIDE);
    }
  #elif (!ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(ENABLE_ATSC)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_CHANNEL_LIST_OPTIONLIST_SORT_PAGE, SW_HIDE);
  #endif

     MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_ExecuteChannelListAction(U16 act)
{
  #if ENABLE_CI_PLUS
    U8 u8Index;
    U8 u8DeletedProfileIndex;
    EN_DELIVERY_SYS_TYPE eProfileDtvSysType = E_DELIVERY_SYS_NONE;
  #endif

    if (pChListData == 0)
    {
        ZUI_DBG_FAIL(printf("[ZUI]ECHLIST\n"));
        ABORT();
        return TRUE;
    }

    CHANNEL_LIST_DBINFO(printf("Funs=%s, line=%d, act=%d\n",__FUNCTION__,__LINE__,act));

#if ENABLE_DVB
    if(gu8VerChange == TRUE)
    {
        pChListData->u16CurCh = 0;
        pChListData->u16TotalChCount = msAPI_CHPROC_CM_CountProgram((MEMBER_SERVICETYPE)E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        _MApp_ChannelList_Handler(pChListData->u16CurCh, 0, pChListData->u16TotalChCount, CHANNEL_LIST_COMMAND_INIT);
        gu8VerChange = FALSE;
    }
#endif

    switch (act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
          #if (ENABLE_ATSC)
            if (IsAtscInUse() || IsATVInUse())
            {
                if(_MApp_ZUI_ACT_IsFavMode())
                {
                    MApp_ChanProc_GetTotalFavFromMainList();
                    MApp_ChanProc_SwitchProgIndex(FAV_LIST, MAIN_LIST);
                    MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
                }
                else
                {
                    MApp_ChanProc_GetTotalDispFromMainList();
                    MApp_ChanProc_SwitchProgIndex(DISP_LIST, MAIN_LIST);
                    MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
                }
            }
            else
          #endif
            {

        #if 0//NTV_FUNCTION_ENABLE // wait to do
            if (MApp_ZUI_API_IsWindowVisible(HWND_NET_CHLIST_BG_PANE))
            {
                if(msAPI_CM_Get_FavoriteNetwork()==INVALID_NETWORKINDEX)
                {
                    msAPI_CM_Set_FavoriteNetwork(0);
                    msAPI_CM_RestoreLCN();
                    msAPI_CM_ArrangeDataManager(TRUE,FALSE);
                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY && MApp_Get_ScanGoRegion_Status())
                    {
                        MApp_Set_ScanGoRegion_Status(FALSE);
                        if(msAPI_CM_CountProgram(msAPI_CM_GetCurrentServiceType(), E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                        {
                            MApp_ChannelChange_EnableChannel();
                        }
                    }
                }
        #if 1//20100222 fix region select
                else if(MApp_DTV_Scan_GetSelectFavoriteNetwork() ==INVALID_NETWORKINDEX)
                {
                    MApp_DTV_Scan_SetSelectFavoriteNetwork(msAPI_CM_Get_FavoriteNetwork());
                    msAPI_CM_ArrangeDataManager(TRUE,FALSE);
                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY && MApp_Get_ScanGoRegion_Status())
                    {
                        MApp_Set_ScanGoRegion_Status(FALSE);
                        if(msAPI_CM_CountProgram(msAPI_CM_GetCurrentServiceType(), E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                        {
                            MApp_ChannelChange_EnableChannel();
                        }
                    }
                }
        #endif
            }
        #endif
            }
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_CLEAN_UP;
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_CHLIST_UP:
        {
            #if ENABLE_CI_PLUS
                if (_MApp_ZUI_ACT_IsFavMode())
                {
                    if (pChListData->u16TotalChCount == 0)
                    {
                        return TRUE;
                    }
                    _MApp_FavoriteList_Handler(0, 1, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_UP);
                }
                else if(_MApp_ZUI_ACT_IsOpProfileMenuMode())
                {
                    _MApp_OpMenuList_Handler(0, 1, MApp_CI_GetOpCacheCount(),  OPMENU_LIST_COMMAND_UP);
                }
            #if(ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL))) // MTC_ADD_FIX
                else if(_MApp_ZUI_ACT_IsFindProByNameMode())
                {
                    _MApp_FindProByNameList_Handler(0, 1, pChListData->u16TotalChCount,  FINDPROBYNAME_LIST_COMMAND_UP);
                }
            #endif
                else
                {    if (pChListData->u16TotalChCount == 0)
                     {
                         return TRUE;
                     }
                    _MApp_ChannelList_Handler(0, 1, pChListData->u16TotalChCount,  CHANNEL_LIST_COMMAND_UP);
                }
            #else //ENABLE_CI_PLUS
                if (pChListData->u16TotalChCount == 0)
                {
                    return TRUE;
                }

                if (_MApp_ZUI_ACT_IsFavMode())
                {
                    _MApp_FavoriteList_Handler(0, 1, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_UP);
#if (ENABLE_ATSC)
                    if (IsAtscInUse() || IsATVInUse())
                    {
                        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                        MApp_ChanProc_DecFavProgIndex(1, FALSE);
                        MApp_ChanProc_RefreshChannelBuffer(FAV_LIST);
                        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                    }
#endif
                }
            #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
            else if(_MApp_ZUI_ACT_IsFindProByNameMode())
            {
                _MApp_FindProByNameList_Handler(0, 1, pChListData->u16TotalChCount,  FINDPROBYNAME_LIST_COMMAND_UP);
            }
            #endif
                else
                {
                    _MApp_ChannelList_Handler(0, 1, pChListData->u16TotalChCount,  CHANNEL_LIST_COMMAND_UP);
                }
            #endif
            return TRUE;
        }

        case EN_EXE_CHLIST_DOWN:
        {
            #if ENABLE_CI_PLUS
                if (_MApp_ZUI_ACT_IsFavMode())
                {
                    if (pChListData->u16TotalChCount == 0)
                    {
                        return TRUE;
                    }
                    _MApp_FavoriteList_Handler(0, 1, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_DOWN);
                }
                else if(_MApp_ZUI_ACT_IsOpProfileMenuMode())
                {
                    _MApp_OpMenuList_Handler(0, 1, MApp_CI_GetOpCacheCount(),  OPMENU_LIST_COMMAND_DOWN);
                }
            #if(ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL))) // MTC_ADD_FIX
                else if(_MApp_ZUI_ACT_IsFindProByNameMode())
                {
                    _MApp_FindProByNameList_Handler(0, 1, pChListData->u16TotalChCount,  FINDPROBYNAME_LIST_COMMAND_DOWN);
                }
            #endif
                else
                {
                    if (pChListData->u16TotalChCount == 0)
                   {
                       return TRUE;
                   }
                    _MApp_ChannelList_Handler(0, 1, pChListData->u16TotalChCount,  CHANNEL_LIST_COMMAND_DOWN);
                }
            #else //ENABLE_CI_PLUS
                if (pChListData->u16TotalChCount == 0)
                {
                    return TRUE;
                }

                if (_MApp_ZUI_ACT_IsFavMode())
                {
                    _MApp_FavoriteList_Handler(0, 1, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_DOWN);
#if (ENABLE_ATSC)
                    if (IsAtscInUse() || IsATVInUse())
                    {
                        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                        MApp_ChanProc_IncFavProgIndex(1, FALSE);
                        MApp_ChanProc_RefreshChannelBuffer(FAV_LIST);
                        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                    }
#endif
                }
            #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
            else if(_MApp_ZUI_ACT_IsFindProByNameMode())
            {
                _MApp_FindProByNameList_Handler(0, 1, pChListData->u16TotalChCount,  FINDPROBYNAME_LIST_COMMAND_DOWN);
            }
            #endif
                else
                {
                    _MApp_ChannelList_Handler(0, 1, pChListData->u16TotalChCount,  CHANNEL_LIST_COMMAND_DOWN);
                }
            #endif
            return TRUE;
        }
        case EN_EXE_CHLIST_PAGE_UP:
            {
            #if ENABLE_CI_PLUS
                if (_MApp_ZUI_ACT_IsFavMode())
                {
                   if (pChListData->u16TotalChCount == 0)
                   {
                       return TRUE;
                   }
                    _MApp_FavoriteList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_PRVPAGE);
                }
                else if(_MApp_ZUI_ACT_IsOpProfileMenuMode())
                {
                    _MApp_OpMenuList_Handler(0, CHANNEL_LIST_PAGE_NUM, MApp_CI_GetOpCacheCount(),  OPMENU_LIST_COMMAND_PRVPAGE);
                }
            #if(ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL))) // MTC_ADD_FIX
                else if(_MApp_ZUI_ACT_IsFindProByNameMode())
                {
                    _MApp_FindProByNameList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  FINDPROBYNAME_LIST_COMMAND_PRVPAGE);
                }
            #endif
                else
                {
                    if (pChListData->u16TotalChCount == 0)
                    {
                       return TRUE;
                    }
                    _MApp_ChannelList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  CHANNEL_LIST_COMMAND_PRVPAGE);
                }
            #else
                if (pChListData->u16TotalChCount == 0)
                {
                    return TRUE;
                }

                if (_MApp_ZUI_ACT_IsFavMode())
                {
                    _MApp_FavoriteList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_PRVPAGE);
                }
            #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
            else if(_MApp_ZUI_ACT_IsFindProByNameMode())
            {
                _MApp_FindProByNameList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  FINDPROBYNAME_LIST_COMMAND_PRVPAGE);
            }
            #endif
                else
                {
                    _MApp_ChannelList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  CHANNEL_LIST_COMMAND_PRVPAGE);
                }
            #endif
            }
            return TRUE;

        case EN_EXE_CHLIST_PAGE_DOWN:
            {
            #if ENABLE_CI_PLUS
                if (_MApp_ZUI_ACT_IsFavMode())
                {
                   if (pChListData->u16TotalChCount == 0)
                   {
                      return TRUE;
                   }
                    _MApp_FavoriteList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_NEXTPAGE);
                }
                else if(_MApp_ZUI_ACT_IsOpProfileMenuMode())
                {
                    _MApp_OpMenuList_Handler(0, CHANNEL_LIST_PAGE_NUM, MApp_CI_GetOpCacheCount(),  OPMENU_LIST_COMMAND_NEXTPAGE);
                }
            #if(ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL))) // MTC_ADD_FIX
                else if(_MApp_ZUI_ACT_IsFindProByNameMode())
                {
                    _MApp_FindProByNameList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  FINDPROBYNAME_LIST_COMMAND_NEXTPAGE);
                }
            #endif
                else
                {
                    if (pChListData->u16TotalChCount == 0)
                    {
                       return TRUE;
                    }
                    _MApp_ChannelList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  CHANNEL_LIST_COMMAND_NEXTPAGE);
                }
            #else
                if (pChListData->u16TotalChCount == 0)
                {
                    return TRUE;
                }

                if (_MApp_ZUI_ACT_IsFavMode())
                {
                    _MApp_FavoriteList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  FAVORITE_LIST_COMMAND_NEXTPAGE);
                }
            #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
            else if(_MApp_ZUI_ACT_IsFindProByNameMode())
            {
                _MApp_FindProByNameList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  FINDPROBYNAME_LIST_COMMAND_NEXTPAGE);
            }
            #endif
                else
                {
                    _MApp_ChannelList_Handler(0, CHANNEL_LIST_PAGE_NUM, pChListData->u16TotalChCount,  CHANNEL_LIST_COMMAND_NEXTPAGE);
                }
            #endif
            }
            return TRUE;

        case EN_EXE_CHLIST_SELECT:
            {
                U16 u16ListOrdinal = 0;
                U8 u16SrvPageCurIndex = 0;

                if (pChListData->u16TotalChCount == 0)
                {
                    return TRUE;
                }

                u16SrvPageCurIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(MApp_ZUI_API_GetFocus());


                E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eChProcBoundary = E_PROGACESS_INCLUDE_VISIBLE_ONLY;

            #if(ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
                if( _MApp_ZUI_ACT_IsFavMode() )
                {
                    eChProcBoundary = CHPROC_FAV_ACCESS_BOUNDRY;
                }
            #endif

                u16ListOrdinal = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u16SrvPageCurIndex);

                if (u16ListOrdinal == CHANNEL_LIST_INVALID_PROGINDEX)
                    return TRUE;


            #if ENABLE_PVR
            {
                MEMBER_SERVICETYPE newCMtype=E_SERVICETYPE_DTV;
        #if (ENABLE_ATSC)
                if ((IsAtscInUse() || IsATVInUse())&&(!_MApp_ZUI_ACT_IsFavMode()))
                {
                    //Don't need to do anything in ATSC
                }
                else
        #else
                msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, u16ListOrdinal, (BYTE *)&newCMtype, E_SERVICE_ATTR_TYPE, eChProcBoundary);
        #endif
                if(MApp_ZUI_ACT_PVR_Check_Switch_Channel(newCMtype, u16ListOrdinal) == FALSE)
                {
                    return TRUE;
                }
            }
            #endif

            #if ENABLE_CI_PLUS
                if(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN)&&
                   MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_DELETE_PROFILE_BTN))
                {
                   return TRUE;
                }
                else
            #endif
                {
                #if (ENABLE_ATSC)
                    if ((IsAtscInUse() || IsATVInUse())&&(!_MApp_ZUI_ACT_IsFavMode()))
                    {
                        if (u16ListOrdinal == pChListData->u16CurCh)
                        {
                            return TRUE;
                        }

                         MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                         if (u16ListOrdinal > pChListData->u16CurCh)
                         {
                             MApp_ChanProc_IncProgIndex(MAIN_LIST,( u16ListOrdinal - pChListData->u16CurCh), FALSE);
                         }
                         else
                         {
                            MApp_ChanProc_DecProgIndex(MAIN_LIST,( pChListData->u16CurCh - u16ListOrdinal), FALSE);
                         }
                         MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
                         MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                    }
                    else
                #endif
                    {
                        _MApp_ChannelList_ChannelChange(u16ListOrdinal, pChListData->u8ServiceType, FALSE, eChProcBoundary);
                    }

                #if ENABLE_CI_PLUS
                    if(TRUE == MApp_CI_IsOpMode())
                    {
                        DB_CI_PLUS_SETTING.u16OpChannelIdex = u16ListOrdinal;
                    }
                #endif
                }

         #ifdef ENABLE_SELECT_NONESEARCH_CH
                u16ChannelReturn_Num2=u16ChannelReturn_Num1;
                u16ChannelReturn_Num1=IVALID_TV_RETURN_NUM;
         #endif

            #if (ENABLE_ATSC)
                // Fix Mantis 875179, because ATSC get program index API is different
                if ((IsAtscInUse() || IsATVInUse())&&(!_MApp_ZUI_ACT_IsFavMode()))
                {
                    pChListData->u16CurCh =  MApp_ChanProc_GetCurProgIndex();   // Get current program index.
                    pChListData->u16CurCh = pChListData->u16CurCh  - 1;         // ATSC valid index is from 1, but channel list index is from 0
                }
                else
            #endif
            #if ENABLE_SBTVD_ATV_SYSTEM
                if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                {
                    pChListData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_ATV, eChProcBoundary);
                }
                else
            #endif
                {
                    pChListData->u16CurCh = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_UNITED_TV, eChProcBoundary);
                }
                if ((!_MApp_ZUI_ACT_IsFavMode())
                #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
                ||_MApp_ZUI_ACT_IsFindProByNameMode()== FALSE
                #endif
                )
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
                }
            }
            return TRUE;

#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))//ENABLE_QSORT_SERVICE
        case EN_EXE_SORT_SELECT:
        {
            MEMBER_SERVICETYPE    cbServiceType = msAPI_CM_GetCurrentServiceType();
            WORD cwCurrentPosition = msAPI_CM_GetCurrentPosition(cbServiceType);
            WORD CurrentS2idx = CurrentS2idx=msAPI_CM_GetPhysicalidx(cbServiceType,cwCurrentPosition);
            WORD CurrentS2ServiceID = msAPI_CM_GetService_ID(cbServiceType,cwCurrentPosition);

            if(stGenSetting.stDvbsSetting.g_sort_type != EN_SORT_BY_DEFAULT)
            {
                msAPI_CM_QuickSortService(E_SERVICETYPE_DTV);
                msAPI_CM_QuickSortService(E_SERVICETYPE_RADIO);
                msAPI_CM_QuickSortService(E_SERVICETYPE_DATA);
            }
            else
            {
                extern BOOLEAN CreatS2ProgramIndexTableAndProgramIDTable(void);
                CreatS2ProgramIndexTableAndProgramIDTable();
            }
            MApp_ZUI_API_ShowWindow(HWND_CHANNEL_LIST_OPTIONLIST_SORT_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_SHOW);
            // MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE, SW_HIDE);
            // MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE, SW_HIDE);
             //MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            //MApp_ZUI_API_SetFocus(HWND_CHLIST_ITEM0);

            msAPI_CM_SetCurrentPositionAfterSort(CurrentS2idx, CurrentS2ServiceID, cbServiceType);

            //#if(ENABLE_S2_PREDIT_SWITCH_LIST)
            //_MApp_ChannelList_Init(cbServiceType);
            //#else
            _MApp_ChannelList_Init(SERVICE_TYPE_TV);
            //#endif

        MApp_ChannelChange_DisableChannel(FALSE, MAIN_WINDOW);
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            //MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);
           // MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
            return TRUE;
#endif
#if ENABLE_CI_PLUS
     case EN_EXE_CHLIST_OPMENU: //show OP menu
         {
             U8 i = 0;
             if(MApp_CI_GetOpCacheCount() == 0)
             {
                 return TRUE;
             }
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OK_BTN,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE,SW_SHOW);
            #if    (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))//ENABLE_QSORT_SERVICE
                  MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG, SW_HIDE);
                  MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_HIDE);
            #endif
             for(i=0; i<CHANNEL_LIST_PAGE_NUM; i++)
             {
                 MApp_ZUI_API_ShowWindow(_OpChannelListScrambleHwndList[i],SW_HIDE);
             }
          MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_PANE,SW_HIDE);
          _MApp_OpMenuList_Handler(0, 0, MApp_CI_GetOpCacheCount(),  OPMENU_LIST_COMMAND_INIT);
             MApp_ZUI_API_SetFocus(HWND_CHLIST_ITEM0);
          }
            return TRUE;
     case EN_EXE_CHLIST_OP: //show OP Channe List
          if(MApp_CI_GetOpCacheCount() == 0)
          {
             return TRUE;
          }
          u8Index = pChListData->u8CurrentPage*CHANNEL_LIST_PAGE_NUM + _MApp_ZUI_ACT_ChannelListWindowMapToIndex(MApp_ZUI_API_GetFocus());
          //CHANNEL_LIST_DBINFO(printf("\r\n [EXE CHLIST OP]u8Index = %d , m_au8OpProfileListMatchIndex[u8Index] = %d",u8Index,m_au8OpProfileListMatchIndex[u8Index]));
          MApp_CI_GetOpDtvSysTypeByIndex(u8Index, &eProfileDtvSysType);
          if(((eProfileDtvSysType == E_DELIVERY_SYS_CDSD) && (MApp_DVBType_GetCurrentType() != EN_DVB_C_TYPE))||
            ((eProfileDtvSysType == E_DELIVERY_SYS_TDSD) && (MApp_DVBType_GetCurrentType() != EN_DVB_T_TYPE)))
          {
            return TRUE;
          }
          else
          {
            U8 i = 0,j=0;
            i = u8Index;
              do
              {
                  MApp_CI_GetOpDtvSysTypeByIndex(i, &eProfileDtvSysType);
                  if(eProfileDtvSysType != E_DELIVERY_SYS_NONE )
                  {
                        //MS_USER_SYSTEM_SETTING *pstSysSetting = NULL;

                        //MApp_GetGenSetting(EN_GENSETTING_CLASS_SYS,  (void *)&pstSysSetting);
                        //pstSysSetting->u8OpIndex = i;
                        DB_CI_PLUS_SETTING.u8OpIndex = i;
                        //pstSysSetting->bInOpMenu= TRUE;
                        DB_CI_PLUS_SETTING.bInOpMenu= TRUE;
                        MApp_CI_EnterCiOperatorProfile(i);
                        break;
                  }
              }while((++i)<MAX_OP_CACHE_NUM);
            _MApp_ChannelList_Init(SERVICE_TYPE_TV);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN,SW_HIDE);//Enter OP
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_MENU_BOTTOM_HALF_DELETE_PROFILE_BTN,SW_HIDE);//Delete Profile
            MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_PANE,SW_HIDE);
        #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))//ENABLE_QSORT_SERVICE
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_HIDE);
        #endif
            for(j=0; j<CHANNEL_LIST_PAGE_NUM; j++)
            {
                MApp_ZUI_API_ShowWindow(_OpChannelListScrambleHwndList[j],SW_HIDE);
            }
            _MApp_ChannelList_Handler(pChListData->u16CurCh, 0, pChListData->u16TotalChCount, CHANNEL_LIST_COMMAND_INIT);
          }
          return TRUE;
     case EN_EXE_GOTO_CHLIST: //Exit OP,show Channel List
        {
            //MS_USER_SYSTEM_SETTING *pstSysSetting = NULL;

            //MApp_GetGenSetting(EN_GENSETTING_CLASS_SYS,  (void *)&pstSysSetting);
            //pstSysSetting->bInOpMenu = FALSE;
            DB_CI_PLUS_SETTING.bInOpMenu = FALSE;
        }

          MApp_CI_ExitCiOperatorProfile();
          _MApp_ChannelList_Init(SERVICE_TYPE_TV);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN,SW_HIDE);//Enter OP
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_MENU_BOTTOM_HALF_DELETE_PROFILE_BTN,SW_HIDE);//Delete Profile
          MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_PANE,SW_HIDE);
        #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))//ENABLE_QSORT_SERVICE
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_HIDE);
        #endif
          _MApp_ChannelList_Handler(pChListData->u16CurCh, 0, pChListData->u16TotalChCount, CHANNEL_LIST_COMMAND_INIT);
            return TRUE;
     case EN_EXE_WARNING_DLG:
          if(MApp_CI_GetOpCacheCount() == 0)
          {
             return TRUE;
          }
          MApp_ZUI_API_ShowWindow(HWND_MAINFRAME,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_TRANSPARENT_BG,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_BG,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_BTN_PANE,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_DELETE_OP_1,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_DELETE_OP_2,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_DELETE_OP_3,SW_SHOW);
          MApp_ZUI_API_SetFocus(HWND_OP_BTN_NO);
            return TRUE;
     case EN_EXE_DLG_CONFIRM_YES:
         if(MApp_ZUI_API_IsWindowVisible(HWND_OP_MSGBOX_DELETE_OP_1))
         {
            U8 i = 0;
            u8DeletedProfileIndex = pChListData->u8CurrentPage*CHANNEL_LIST_PAGE_NUM + _MApp_ZUI_ACT_ChannelListWindowMapToIndex(MApp_ZUI_API_GetFocusCheckpoint());
            i = u8DeletedProfileIndex;
#if ENABLE_CI_PLUS
			stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo = FALSE;  // clean flag
#endif
              do
              {
                  MApp_CI_GetOpDtvSysTypeByIndex(i, &eProfileDtvSysType);
                  printf("\r\n[Del]u8DeletedProfileIndex = %d,i=%d,eProfileDtvSysType = %d\n",u8DeletedProfileIndex,i,eProfileDtvSysType);
                  if(eProfileDtvSysType != E_DELIVERY_SYS_NONE )
                  {
                      MApp_CI_DeleteOpCacheByIndex(i);
                      break;
                  }
              }while((++i)<MAX_OP_CACHE_NUM);
          _MApp_OpMenuList_Handler(0, 0, MApp_CI_GetOpCacheCount(),  OPMENU_LIST_COMMAND_INIT);
          printf("Delete Operator Profile:%d,OpCacheCount = %d, ValidOpCacheCount = %d\n",u8DeletedProfileIndex,MApp_CI_GetOpCacheCount(),MApp_CI_GetValidOpCacheCount());
          if(MApp_CI_GetOpCacheCount() == 0)
          {
              MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
              _enTargetState = STATE_OSDPAGE_CLEAN_UP;
          }
          else
          {
              MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE,SW_SHOW);
              MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE,SW_SHOW);
              MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OK_BTN,SW_HIDE);
              MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN,SW_HIDE);
              MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);
              MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG,SW_HIDE);
              MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG,SW_HIDE);
              MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_PANE,SW_HIDE);
              MApp_ZUI_API_SetFocus(HWND_CHLIST_ITEM0);
          }
         }
         return TRUE;
     case EN_EXE_DLG_CONFIRM_NO:
        if(MApp_ZUI_API_IsWindowVisible(HWND_OP_MSGBOX_DELETE_OP_1))
        {
          U8 i=0;
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BG_PANE,SW_SHOW);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OK_BTN,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG,SW_HIDE);
          MApp_ZUI_API_ShowWindow(HWND_CHLIST_LIST_PANE,SW_SHOW);
          for(i=0; i<CHANNEL_LIST_PAGE_NUM; i++)
          {
              MApp_ZUI_API_ShowWindow(_OpChannelListScrambleHwndList[i],SW_HIDE);
          }
          MApp_ZUI_API_ShowWindow(HWND_OP_MSGBOX_PANE,SW_HIDE);
          MApp_ZUI_API_SetFocus(MApp_ZUI_API_GetFocusCheckpoint());
        }
        return TRUE;
#endif
        case EN_EXE_GOTO_MAINMENU:
#if 0//NTV_FUNCTION_ENABLE // wait to do
            if (MApp_ZUI_API_IsWindowVisible(HWND_NET_CHLIST_BG_PANE))
            {
                if(msAPI_CM_Get_FavoriteNetwork()==INVALID_NETWORKINDEX)
                {
                    msAPI_CM_Set_FavoriteNetwork(0);
                    msAPI_CM_RestoreLCN();
                    msAPI_CM_ArrangeDataManager(TRUE,FALSE);
                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY && MApp_Get_ScanGoRegion_Status())
                    {
                        MApp_Set_ScanGoRegion_Status(FALSE);
                        if(msAPI_CM_CountProgram(msAPI_CM_GetCurrentServiceType(), E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                        {
                            MApp_ChannelChange_EnableChannel();
                        }
                    }
                }
#if 1//20100222 fix region select
                else if(MApp_DTV_Scan_GetSelectFavoriteNetwork() ==INVALID_NETWORKINDEX)
                {
                    MApp_DTV_Scan_SetSelectFavoriteNetwork(msAPI_CM_Get_FavoriteNetwork());
                    msAPI_CM_ArrangeDataManager(TRUE,FALSE);
                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY && MApp_Get_ScanGoRegion_Status())
                    {
                        MApp_Set_ScanGoRegion_Status(FALSE);
                        if(msAPI_CM_CountProgram(msAPI_CM_GetCurrentServiceType(), E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                        {
                            MApp_ChannelChange_EnableChannel();
                        }
                    }
                }
#endif
            }
#endif
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_MAIN_MENU;
            return TRUE;
#if 0 //NTV_FUNCTION_ENABLE //wait to do
         case EN_EXE_NETWORK_LIST_SELECT:
            {
                U8 u8FavIdx=0;

                u8FavIdx=_MApp_ZUI_ACT_FavouriteRegionWindowMapToIndex(MApp_ZUI_API_GetFocus());
                msAPI_CM_Set_FavoriteNetwork(ValidNetID[u8FavIdx]);
#if 1//20100222 fix region select
                MApp_DTV_Scan_SetSelectFavoriteNetwork(ValidNetID[u8FavIdx]);
#endif
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CLOSE_CURRENT_OSD);
                {
                    msAPI_CM_RestoreLCN();
                    msAPI_CM_ArrangeDataManager(TRUE,FALSE);
                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY && MApp_Get_ScanGoRegion_Status())
                    {
                        MApp_Set_ScanGoRegion_Status(FALSE);
                        if(msAPI_CM_CountProgram(msAPI_CM_GetCurrentServiceType(), E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                        {
                            MApp_ChannelChange_EnableChannel();
                        }
                    }
                }
            }
            return TRUE;
         case EN_EXE_NETWORK_LIST_EXIT:
            {
                if(msAPI_CM_Get_FavoriteNetwork()==INVALID_NETWORKINDEX)
                {
                    msAPI_CM_Set_FavoriteNetwork(0);
                    msAPI_CM_RestoreLCN();
                    msAPI_CM_ArrangeDataManager(TRUE,FALSE);
                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY && MApp_Get_ScanGoRegion_Status())
                    {
                        MApp_Set_ScanGoRegion_Status(FALSE);
                        if(msAPI_CM_CountProgram(msAPI_CM_GetCurrentServiceType(), E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
                        {
                            MApp_ChannelChange_EnableChannel();
                        }
                    }
                }
                else
                {

                }
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CLOSE_CURRENT_OSD);

            }
            return TRUE;

            case EN_EXE_NETWORK_CHLIST_UP:
            {

                U8 u8FavIdx=0;
                MApp_ZUI_API_ResetTimer(HWND_CHLIST_LIST_PANE, 0);
                u8FavIdx=_MApp_ZUI_ACT_FavouriteRegionWindowMapToIndex(MApp_ZUI_API_GetFocus());
                if(u8FavIdx == 0)
                {
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }
            case EN_EXE_NETWORK_CHLIST_DOWN:
            {
                U8 u8FavIdx=0;

                MApp_ZUI_API_ResetTimer(HWND_CHLIST_LIST_PANE, 0);

                MApp_ZUI_API_ResetTimer(HWND_CHLIST_LIST_PANE, 0);
                u8FavIdx=_MApp_ZUI_ACT_FavouriteRegionWindowMapToIndex(MApp_ZUI_API_GetFocus());
                if(u8FavIdx == u8TotalNetWorkNum-1)
                {
                   return TRUE;
                }
                else
                {
                   return FALSE;
                }
            }
#endif

    }
    return FALSE;
}


BOOLEAN MApp_ZUI_ACT_HandleChannelListKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_CHLIST_LIST_PANE, 0);

    #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
    if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_CHLIST_SOFTKEYBOARD))
     {
         return _Chlist_HandleSoftkeyboardkey(key);
     }
    #endif

    CHANNEL_LIST_DBINFO(printf("Funs=%s, line=%d,key=%d\n",__FUNCTION__,__LINE__,key));

    switch(key)
    {
        case VK_EXIT:
        case VK_CHANNEL_LIST:
        case VK_CHANNEL_FAV_LIST:
#if ENABLE_ATSC_TTS
            MApp_TTS_Cus_Say_exit();
#endif
            if(MApp_ZUI_API_IsSuccessor(HWND_CHLIST_LIST_PANE,MApp_ZUI_API_GetFocus()))
            {
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,FALSE);
            }
            MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;
        case VK_POWER:
            MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_POWEROFF);
            return TRUE;

       case VK_UP:
#if ENABLE_S2
#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))//ENABLE_QSORT_SERVICE
           if(MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM1
                   || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM2
                   || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM3
                   || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM4
#if(ENABLE_S2_PROGRAM_PREPARE)
                   || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM5
#endif
                   || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM6
             )
           {
               return FALSE;
           }
#endif
#endif
            MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CHLIST_UP);
            return TRUE;
            break;
        case VK_DOWN:
#if ENABLE_S2
#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))//ENABLE_QSORT_SERVICE
            if(MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM1
                    || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM2
                    || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM3
                    || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM4
#if(ENABLE_S2_PROGRAM_PREPARE)
                    || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM5
#endif
                   || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM6
              )
            {
                return FALSE;
            }
#endif
#endif
            MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CHLIST_DOWN);
            return TRUE;
            break;

        case VK_SELECT:
#if ENABLE_S2
        #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))//ENABLE_QSORT_SERVICE
            if(MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM1
            || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM2
            || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM3
            || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM4
        #if(ENABLE_S2_PROGRAM_PREPARE)
            || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM5
        #endif
            || MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM6
            )
            {
                if(MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM1)
                stGenSetting.stDvbsSetting.g_sort_type = EN_SORT_BY_FREQ;
                else if(MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM2)
                stGenSetting.stDvbsSetting.g_sort_type = EN_SORT_BY_SERVICE_NAME;
                else if(MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM3)
                stGenSetting.stDvbsSetting.g_sort_type = EN_SORT_BY_SAT_NAME;
                else if(MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM4)
                stGenSetting.stDvbsSetting.g_sort_type = EN_SORT_BY_Encrypt;
            #if(ENABLE_S2_PROGRAM_PREPARE)
                else if(MApp_ZUI_API_GetFocus() == HWND_CHANNEL_LIST_OPTIONLIST_ITEM5)
                stGenSetting.stDvbsSetting.g_sort_type =  EN_SORT_BY_PREPARE;
            #endif
                else
                stGenSetting.stDvbsSetting.g_sort_type = EN_SORT_BY_DEFAULT;
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_SORT_SELECT);
                return TRUE;
            }
            else
        #endif
#endif
            {
            MApp_ZUI_API_SetTimer(HWND_CHLIST_BOTTOM_HALF_OK_BTN, 0, BUTTONANICLICK_PERIOD);
            MApp_ZUI_API_InvalidateWindow(HWND_CHLIST_BOTTOM_HALF_OK_BTN);
            break;
            }
        case VK_MENU:
            if(MApp_ZUI_API_IsSuccessor(HWND_CHLIST_LIST_PANE,MApp_ZUI_API_GetFocus()))
            {
                _MApp_ZUI_ACT_CHLISTMarqueeTextEnableAnimation(CHLIST_MARQUEE_ITEM,FALSE);
            }
            MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_GOTO_MAINMENU);
            return TRUE;
    #ifdef MTC_FIX_BUG_KEY
        case VK_INPUT_SOURCE:
            MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_SHOW_SOURCE_BANNER);
            return TRUE;
    #endif
#if ENABLE_S2
    #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
        case VK_GREEN:
            if(MApp_ZUI_API_IsSuccessor(HWND_CHANNEL_LIST_OPTIONLIST_SORT_PAGE, MApp_ZUI_API_GetFocus()))//ryan add
            {
                MApp_ZUI_API_ShowWindow(HWND_CHANNEL_LIST_OPTIONLIST_SORT_PAGE, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_CHLIST_ITEM0);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_CHANNEL_LIST_OPTIONLIST_SORT_PAGE, SW_SHOW);
#if(ENABLE_S2_PROGRAM_PREPARE)
                MApp_ZUI_API_ShowWindow(HWND_CHANNEL_LIST_OPTIONLIST_ITEM5, SW_SHOW);
#else
                MApp_ZUI_API_ShowWindow(HWND_CHANNEL_LIST_OPTIONLIST_ITEM5, SW_HIDE);
#endif
                if (stGenSetting.stDvbsSetting.g_sort_type ==  EN_SORT_BY_FREQ)
                    MApp_ZUI_API_SetFocus(HWND_CHANNEL_LIST_OPTIONLIST_ITEM1);
                else if (stGenSetting.stDvbsSetting.g_sort_type == EN_SORT_BY_SERVICE_NAME)
                    MApp_ZUI_API_SetFocus(HWND_CHANNEL_LIST_OPTIONLIST_ITEM2);
                else if (stGenSetting.stDvbsSetting.g_sort_type == EN_SORT_BY_SAT_NAME)
                    MApp_ZUI_API_SetFocus(HWND_CHANNEL_LIST_OPTIONLIST_ITEM3);
                else if (stGenSetting.stDvbsSetting.g_sort_type == EN_SORT_BY_Encrypt)
                    MApp_ZUI_API_SetFocus(HWND_CHANNEL_LIST_OPTIONLIST_ITEM4);
            #if(ENABLE_S2_PROGRAM_PREPARE)
                else if (stGenSetting.stDvbsSetting.g_sort_type == EN_SORT_BY_PREPARE)
                    MApp_ZUI_API_SetFocus(HWND_CHANNEL_LIST_OPTIONLIST_ITEM5);
            #endif
            //#if(DTV_SYSTEM_SEL == DTV_SYSTEM_ATSC)
                else if (stGenSetting.stDvbsSetting.g_sort_type == EN_SORT_BY_DEFAULT)
                    MApp_ZUI_API_SetFocus(HWND_CHANNEL_LIST_OPTIONLIST_ITEM6);
            //#endif

            }
            break;

        //case VK_GREEN:
        //{
           // MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_SORT_SELECT);
           // return TRUE;
        //}

        case VK_RED:
        if(IsS2InUse())
        {
            U8 i;
            for(i=0;i<PROGRAMNAME_MAXLENGTH_CHLIST;i++)
            {
                u8ProgName_chlist[i]=0;
            }
            u8ProgNameCharNum_chlist=0;
            MApp_ChannelList_SetMode(MODE_CHLIST_FIND_BYNAME);

            if(pChListData->u8ServiceType == E_SERVICETYPE_RADIO)
            {
                _MApp_FindProByNameList_Init(E_SERVICETYPE_UNITED_TV);
            }
            else if(pChListData->u8ServiceType == E_SERVICETYPE_DATA)
            {
                _MApp_FindProByNameList_Init(E_SERVICETYPE_UNITED_TV);
            }
            else
            {
                _MApp_FindProByNameList_Init(E_SERVICETYPE_UNITED_TV);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHLIST_SOFTKEYBOARD, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_SORT_BG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHLIST_BOTTOM_HALF_FIND_BG, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_MENU_CHLIST_SOFTKEYBOARD_BG, SW_HIDE);
            //MApp_ZUI_API_SetFocus(HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_CANCEL);
            MApp_ZUI_API_SetFocus(HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_1);
        }
        else
        {
        #if ENABLE_CI_PLUS
            if((MApp_CI_IsOpMode()==FALSE)&&(IsDTVInUse())&&
              (MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN)))
            {
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CHLIST_OPMENU); //show OP Menu
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN))
            {
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CHLIST_OP);  //Show OP Channel List
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN)&&(MApp_CI_IsOpMode()==TRUE))
            {
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_GOTO_CHLIST); //Exit OP,show Channel List
            }
        #endif
        }
        return TRUE;
    #else
        #if ENABLE_CI_PLUS
        case VK_RED:
        {
            if((MApp_CI_IsOpMode()==FALSE)&&(IsDTVInUse())&&
              (MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN)))
            {
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CHLIST_OPMENU); //show OP Menu
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN))
            {
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CHLIST_OP);  //Show OP Channel List
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN)&&(MApp_CI_IsOpMode()==TRUE))
            {
                MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_GOTO_CHLIST); //Exit OP,show Channel List
            }
         }
        return TRUE;
        #endif
    #endif
#endif
        #if ENABLE_CI_PLUS
        case VK_BLUE:
            if(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN))
            {
               MApp_ZUI_API_StoreFocusCheckpoint(); //save focus item
               MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_WARNING_DLG);
            }
            return TRUE;
        //case VK_RED:
            /*{
                if((MApp_CI_IsOpMode()==FALSE)&&(IsDTVInUse())&&
                  (MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_BOTTOM_HALF_OP_MENU_BTN)))
                {
                    MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CHLIST_OPMENU); //show OP Menu
                }
                else if(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN))
                {
                    MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_CHLIST_OP);  //Show OP Channel List
                }
                else if(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN)&&(MApp_CI_IsOpMode()==TRUE))
                {
                    MApp_ZUI_ACT_ExecuteChannelListAction(EN_EXE_GOTO_CHLIST); //Exit OP,show Channel List
                }
             }
             return TRUE;*/
        #endif

#if ENABLE_XL3_API
        case VK_GREEN:
            printf("\r\n >>>> %s delete service", __FUNCTION__);
            if(IS_HIDE_CH(pChListData->u16CurCh))
            {
                SET_HIDE_CH(FALSE);
            }
            else
            {
                SET_HIDE_CH(TRUE);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            return TRUE;

        case VK_YELLOW:
            printf("\r\n >>>> %s lock service", __FUNCTION__);
            if(IS_LOCK_CH(pChListData->u16CurCh))
            {
                SET_LOCK_CH(FALSE);
            }
            else
            {
                SET_LOCK_CH(TRUE);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            return TRUE;

        case VK_RED:
            printf("\r\n >>>> %s favorite service", __FUNCTION__);
            if(IS_FAV_CH(pChListData->u16CurCh))
            {
                SET_FAV_CH(FALSE);
            }
            else
            {
                SET_FAV_CH(TRUE);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            return TRUE;

        case VK_BLUE:
            {
            U16 i;
            U16 u16TotalCount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_ALL);;
            printf("\r\n >>>> %s select all service", __FUNCTION__);
            for(i = 0; i < u16TotalCount; i++)
            {
                SET_CHECK_CH(i, TRUE);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHLIST_LIST_PANE);
            return TRUE;
            }

 #endif

        default:
            break;

    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateChannelList(void)
{
#if (ENABLE_ARABIC_OSD)
    ArabicCHStringFlag = FALSE;
#endif
    ZUI_MSG(printf("[]term:chlist\n");)
    _ZUI_FREE(pChListData);
    MApp_OSDPage_SetState(_enTargetState);
}

#if (ENABLE_ATSC)
#ifndef CHAN_NUM_SEPERATOR
#define CHAN_NUM_SEPERATOR CHAR_DOT//CHAR_MINUS
#endif
extern EN_SYS_INPUT_SOURCE_TYPE  _enSysInputSource[2];
void MApp_UiMenuFunc_ConvertProgramNumber2Str (MS_VIRTUAL_CHANNEL_NUM *pstVirtualChNum, U8 *pu8Str)
{
    U8 u8NoOfDigit;
    u8NoOfDigit = MApp_GetNoOfDigit( pstVirtualChNum->major_num );
    MApp_UlongToU8String( pstVirtualChNum->major_num, pu8Str, u8NoOfDigit );

#if ONE_PART_CHNO
    if((!pstVirtualChNum->fIsOnePartChNum))
    {
        pu8Str[u8NoOfDigit++] = CHAN_NUM_SEPERATOR;//'-';
        MApp_UlongToU8String( ( U32 ) pstVirtualChNum->minor_num, pu8Str + u8NoOfDigit, MApp_GetNoOfDigit( pstVirtualChNum->minor_num ) );
    }
#else
    pu8Str[u8NoOfDigit++] = CHAN_NUM_SEPERATOR;//'-';
    MApp_UlongToU8String( ( U32 ) pstVirtualChNum->minor_num, pu8Str + u8NoOfDigit, u8NoOfDigit);
#endif
}
#endif

GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryChannelListItemStatus(HWND hwnd)
{
    switch(hwnd)
    {
#if(UI_SKIN_SEL != UI_SKIN_960X540XI8 && UI_SKIN_SEL != UI_SKIN_960X540X565)
#if(!ENABLE_S2_PROGRAM_PREPARE)
        case HWND_CHANNEL_LIST_OPTIONLIST_ITEM5:
            return EN_DL_STATE_HIDDEN;
#endif
#endif
        default:
        break;
    }
    return EN_DL_STATE_NORMAL;
}

U16 MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(U8 u8VisIndex)
{
    U16 u16ProgPos = CHANNEL_LIST_INVALID_PROGINDEX;

    if( _MApp_ZUI_ACT_IsFavMode()
  #if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
     || _MApp_ZUI_ACT_IsFindProByNameMode()
  #endif
      )
    {
        u16ProgPos = pChListData->u16PageListIndex[u8VisIndex];
    }
    else
    {
        u16ProgPos = pChListData->u8CurrentPage*CHANNEL_LIST_PAGE_NUM + u8VisIndex;
    }

    return u16ProgPos;
}

LPTSTR MApp_ZUI_ACT_GetChannelListDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    //printf("DynamicText: %u\n", hwnd);

  #if ENABLE_CI_PLUS
    U8 u8OpNum = MApp_CI_GetOpCacheCount(); //Evie++:get num of op index
    memset((void*)CHAR_BUFFER, '\0', 128);
  #endif

#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
    if(hwnd >= HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_1 && hwnd <= HWND_MENU_CHLIST_SOFTKEYBOARD_KEY_40)
    {
        return _Chlist_softkeyboard_dynamictext(hwnd);
    }
#endif

    switch(hwnd)
    {
    #if  (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
       case HWND_MENU_CHLIST_SOFTKEYBOARD_TITLE_M:
        {
             MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (MS_U8*)u8ProgName_chlist, UTL_strlen1((char *)u8ProgName_chlist));
             return CHAR_BUFFER;
        }
    #endif

        case HWND_CHLIST_TOP_HALF_BANNER_TITLE:
            if( _MApp_ZUI_ACT_IsFavMode() )
            {
                u16TempID = en_str_Favorite_List;
            }
            /*else if (_eChannelListMode == MODE_CHLIST_RADIO)
            {
                u16TempID = en_str_Radio_List;
            }*/
          #if ENABLE_CI_PLUS
            else if((MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN))&&(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_DELETE_PROFILE_BTN)))
                u16TempID = en_str_Operator_Profiles_Menu;  //OP Menu
            else if((u8OpNum>0)&&MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_BOTTOM_HALF_EXIT_OP_BTN))
                u16TempID = en_str_OP_Channel_List;  //OP Channel List
          #endif
            #if 0 //ENABLE_S2//ENABLE_QSORT_SERVICE
                else if (_eChannelListMode == MODE_CHLIST_S2)
                {
                #if 1//(CUSTOMER_TYPE == Customer_ODYS)
                    if((MEMBER_SERVICETYPE)pChListData->u8ServiceType==E_SERVICETYPE_RADIO)
                        u16TempID = en_str_Radio_List;
                    else
                #endif
                        u16TempID = en_str_S2_List_Text;
                }
            #endif
            else //if (_eChannelListMode == MODE_CHLIST_TV)
                u16TempID = en_str_Channel_List;

          #if 0//(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
            if (_eChannelListMode == MODE_CHLIST_RADIO_FAV ||
                _eChannelListMode == MODE_CHLIST_TV_FAV)
            {
                    if(g_favorite_type == 0)
                    u16TempID = en_str_FavoriteTypeNews;
                else if(g_favorite_type == 1)
                    u16TempID = en_str_Music;
                else if(g_favorite_type == 2)
                    u16TempID = en_str_Music;
                else if(g_favorite_type == 3)
                    u16TempID = en_str_Favorite_List;
                else
                    u16TempID = en_str_Favorite_List;
            }
           #endif
            break;

    #if ENABLE_CI_PLUS
        case HWND_OP_MSGBOX_DELETE_OP_3:
             {
                U8 u8DeletedProfileIndex;
                EN_DELIVERY_SYS_TYPE eProfileDtvSysType = E_DELIVERY_SYS_NONE;
                LPTSTR str = CHAR_BUFFER;
                U8 i = 0;
                u8DeletedProfileIndex = pChListData->u8CurrentPage*CHANNEL_LIST_PAGE_NUM + _MApp_ZUI_ACT_ChannelListWindowMapToIndex(MApp_ZUI_API_GetFocusCheckpoint());
                i = u8DeletedProfileIndex;
                do
                {
                    MApp_CI_GetOpDtvSysTypeByIndex(i, &eProfileDtvSysType);
                    if(eProfileDtvSysType != E_DELIVERY_SYS_NONE )
                    {
                        MApp_CI_GetOpProfileNameByIndex(i,str,STRING_BUFFER_LENGTH);
                        return CHAR_BUFFER;
                    }
                }while((++i)<MAX_OP_CACHE_NUM);
                return str;
             }
             break;
        case HWND_OP_MENU_ITEM0_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM1_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM2_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM3_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM4_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM5_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM6_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM7_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM8_DELIVERY_SYS_TYPE:
        case HWND_OP_MENU_ITEM9_DELIVERY_SYS_TYPE:
        {
          if(_MApp_ZUI_ACT_IsOpProfileMenuMode())
          {
            EN_DELIVERY_SYS_TYPE eProfileDtvSysType = E_DELIVERY_SYS_NONE;
            U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
            U16 wProgramPosition;
            U8 i = 0;
            wProgramPosition = _u8OpMenuCurrentPage*CHANNEL_LIST_PAGE_NUM + u8VisIndex;
            if(wProgramPosition >= MApp_CI_GetOpCacheCount())
            {
               break;
            }
            for(i = wProgramPosition; i<u8OpNum; i++)
            {
                do
                {
                    MApp_CI_GetOpDtvSysTypeByIndex(i, &eProfileDtvSysType);
                    if(eProfileDtvSysType != E_DELIVERY_SYS_NONE )
                    {
                        if(eProfileDtvSysType == E_DELIVERY_SYS_CDSD)
                        {
                            u16TempID = en_str_DVBdashC;
                        }
                        else if (eProfileDtvSysType == E_DELIVERY_SYS_TDSD)
                        {
                            u16TempID = en_str_DVBdashT;
                        }
                        else
                        {
                            u16TempID = Empty;
                        }
                        break;
                    }
                }while((++i)<MAX_OP_CACHE_NUM);
            }
            CHANNEL_LIST_DBINFO(printf("\r\n [OpMenu]g_wProgramPosition = %d,eProfileDtvSysType = %d\n",wProgramPosition,eProfileDtvSysType));
          }
        }
             break;
    #endif // ENABLE_CI_PLUS


        case HWND_CHLIST_ITEM0_SCRAMBLE:
        case HWND_CHLIST_ITEM1_SCRAMBLE:
        case HWND_CHLIST_ITEM2_SCRAMBLE:
        case HWND_CHLIST_ITEM3_SCRAMBLE:
        case HWND_CHLIST_ITEM4_SCRAMBLE:
        case HWND_CHLIST_ITEM5_SCRAMBLE:
        case HWND_CHLIST_ITEM6_SCRAMBLE:
        case HWND_CHLIST_ITEM7_SCRAMBLE:
        case HWND_CHLIST_ITEM8_SCRAMBLE:
        case HWND_CHLIST_ITEM9_SCRAMBLE:
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
                U16 u16ProgPosition = 0;

                u16ProgPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);
                if( (u16ProgPosition == CHANNEL_LIST_INVALID_PROGINDEX)
                  ||(u16ProgPosition >= pChListData->u16TotalChCount)
                  )
                {
                    break;
                }

            #if ENABLE_DTV
                {
                    LPTSTR str = CHAR_BUFFER;
                    MEMBER_SERVICETYPE bServiceType;
                    BOOLEAN bScramble;

                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, u16ProgPosition, ( BYTE *)&bServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                    bScramble = msAPI_CM_GetProgramAttribute(bServiceType,u16ProgPosition, E_ATTRIBUTE_IS_SCRAMBLED);

                    if (bScramble == TRUE)
                    {
                        *str ++ = CHAR_S;
                    }
                    else
                    {
                        *str ++ = CHAR_SPACE;
                    }

                    *str = 0;

                    return CHAR_BUFFER;
                }
            #else
                {
                    LPTSTR str = CHAR_BUFFER;
                    *str ++ = CHAR_SPACE;
                    *str = 0;
                    return CHAR_BUFFER;

                }
            #endif

            }
            break;


        case HWND_CHLIST_ITEM0_TEXT:
        case HWND_CHLIST_ITEM1_TEXT:
        case HWND_CHLIST_ITEM2_TEXT:
        case HWND_CHLIST_ITEM3_TEXT:
        case HWND_CHLIST_ITEM4_TEXT:
        case HWND_CHLIST_ITEM5_TEXT:
        case HWND_CHLIST_ITEM6_TEXT:
        case HWND_CHLIST_ITEM7_TEXT:
        case HWND_CHLIST_ITEM8_TEXT:
        case HWND_CHLIST_ITEM9_TEXT:
        {
            CHANNEL_LIST_DBINFO( printf(" HWND_CHLIST_ITEM(%u)_TEXT\n", hwnd-HWND_CHLIST_ITEM0_TEXT); );

            U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
            CHANNEL_LIST_DBINFO( printf(" u8VisIndex=%u\n", u8VisIndex); );

            U16 u16ProgPosition;

    #if (ENABLE_ATSC)
           if (IsAtscInUse() || IsATVInUse())
           {
                CHAR_BUFFER[0] = 0;
                U8  *pu8String;
                LPTSTR str = CHAR_BUFFER;

                u16ProgPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);
                if( (u16ProgPosition == CHANNEL_LIST_INVALID_PROGINDEX)
                ||(u16ProgPosition >= pChListData->u16TotalChCount)
                )
                {
                    break;
                }

//Channel number
            #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
                if (u16ProgPosition < stChSettingDisp[ANT_AIR].u16MainListSrvNum)
                {
                    MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
                    MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(u16ProgPosition+1))->stVirtualChNum, au8Section);
                }
                else
                {
                    MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
                    MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(u16ProgPosition+1 - stChSettingDisp[ANT_AIR].u16MainListSrvNum))->stVirtualChNum, au8Section);
                }
            #else
                MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(u16ProgPosition+1))->stVirtualChNum, au8Section);
            #endif
                MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, au8Section, strlen((char *)au8Section));

                str += MApp_ZUI_API_Strlen(str);//u8_idx = __strlen(p_string_buffer);
                *str++ = CHAR_SPACE; //p_string_buffer[u8_idx++] = CHAR_SPACE;
//Channel name
            #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
                if (u16ProgPosition < stChSettingDisp[ANT_AIR].u16MainListSrvNum)
                {
                    MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
                    pu8String = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_AIR(u16ProgPosition+1))->acServiceName;
                }
                else
                {
                    MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
                    pu8String = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX_CATV(u16ProgPosition+1-stChSettingDisp[ANT_AIR].u16MainListSrvNum))->acServiceName;
                }
                MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
            #else
                pu8String = MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(u16ProgPosition+1))->acServiceName;
            #endif
                MApp_ZUI_API_StringBufferUTF16toU16(str, pu8String, MAX_LENGTH_OF_SERVICE_NAME/2+1);

                str[MAX_LENGTH_OF_SERVICE_NAME/2] = 0;
                MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
                return CHAR_BUFFER;

            }
            else
    #endif  //ENABLE_ATSC
            {
                //U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
                //U16 g_wProgramPosition;

              #if ENABLE_CI_PLUS
                U8 i = 0;
                EN_DELIVERY_SYS_TYPE eProfileDtvSysType = E_DELIVERY_SYS_NONE;

                if(_MApp_ZUI_ACT_IsOpProfileMenuMode())//OP MENU Name
                {
                    u16ProgPosition = _u8OpMenuCurrentPage*CHANNEL_LIST_PAGE_NUM + u8VisIndex;
                    if(u16ProgPosition >= MApp_CI_GetOpCacheCount())
                    {
                       break;
                    }

                    LPTSTR str = CHAR_BUFFER;
                    for(i = u16ProgPosition; i<u8OpNum; i++)
                    {
                        do
                        {
                            MApp_CI_GetOpDtvSysTypeByIndex(i, &eProfileDtvSysType);
                            if(eProfileDtvSysType != E_DELIVERY_SYS_NONE )
                            {
                                MApp_CI_GetOpProfileNameByIndex(i, str , STRING_BUFFER_LENGTH);
                                return CHAR_BUFFER;
                            }
                        }while((++i)<MAX_OP_CACHE_NUM);
                    }
                    return CHAR_BUFFER;

                }
                else
              #endif    //ENABLE_CI_PLUS
                {
                    u16ProgPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);
                    CHANNEL_LIST_DBINFO( printf(" [TEXT] u8VisIndex=%d, u16ProgPosition = %d, u16TotalChCount = %d\n", u8VisIndex, u16ProgPosition, pChListData->u16TotalChCount); );

                    if( _MApp_ZUI_ACT_IsFavMode() )
                    {
                        if( (u16ProgPosition == CHANNEL_LIST_INVALID_PROGINDEX) )
                        {
                                break;
                        }
                    }
                    else
                    {
                        if( (u16ProgPosition == CHANNEL_LIST_INVALID_PROGINDEX)
                         || (u16ProgPosition >= pChListData->u16TotalChCount)
                          )
                        {
                                break;
                        }
                    }

                    LPTSTR str = CHAR_BUFFER;

        #if ENABLE_DVB
                #if ENABLE_S2//ENABLE_QSORT_SERVICE
                    if( /*_eChannelListMode == MODE_CHLIST_S2||*/_eChannelListMode == MODE_CHLIST_FIND_BYNAME)
                    {
                        MEMBER_SERVICETYPE bServiceType;
                        U16 u16Number = 0;
                        msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, u16ProgPosition, ( BYTE *)&bServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                        msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, u16ProgPosition, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                        CHANNEL_LIST_DBINFO( printf(" CHANNELLIST_PROGRAMNUMBERNAMETEXT>> msAPI_ATV_GetActiveProgramCount() %bu\n", msAPI_ATV_GetActiveProgramCount()); );
                        CHANNEL_LIST_DBINFO( printf(" g_wProgramPosition=%u, bServiceType=%u, u16Number=%u\n", g_wProgramPosition, bServiceType, u16Number); ) ;

                    #if(ENABLE_S2_PREDIT_SWITCH_LIST)
                        WORD DTVcount, Radiocount;
                        DTVcount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED);
                        Radiocount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
                    #endif

                        if (bServiceType == E_SERVICETYPE_DTV)
                        {
                            MApp_ZUI_DTV_ChNumString(u16Number, str);
                            str += MApp_ZUI_API_Strlen(str); //u8_idx = __strlen(p_string_buffer);
                            *str++ = CHAR_SPACE; //p_string_buffer[u8_idx++] = CHAR_SPACE;
                            //PRINT_CURRENT_LINE();

                            MApp_CharTable_GetServiceNameToUCS2(bServiceType, u16ProgPosition, str, KEEP_CONTROL_CODE_NONE);
                            str += MApp_ZUI_API_Strlen(str);
                        }
                        else if (bServiceType == E_SERVICETYPE_RADIO)
                        {
                            MApp_ZUI_DTV_ChNumString(u16Number, str);
                            str += MApp_ZUI_API_Strlen(str); //u8_idx = __strlen(p_string_buffer);
                            *str++ = CHAR_SPACE; //p_string_buffer[u8_idx++] = CHAR_SPACE;

                        #if(ENABLE_S2_PREDIT_SWITCH_LIST)
                            u16ProgPosition = u16ProgPosition - DTVcount;
                            MApp_CharTable_GetServiceNameToUCS2(bServiceType, u16ProgPosition, str, KEEP_CONTROL_CODE_NONE);
                        #else
                            MApp_CharTable_GetServiceNameToUCS2(bServiceType, u16ProgPosition-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY), str, KEEP_CONTROL_CODE_NONE);
                        #endif
                            str += MApp_ZUI_API_Strlen(str);
                        }
                    #if NORDIG_FUNC //for Nordig spec v2.0
                        else if (bServiceType == E_SERVICETYPE_DATA)
                        {
                            MApp_ZUI_API_GetU16String(u16Number); //__MApp_UlongToString(u16Number, p_string_buffer, MApp_GetNoOfDigit(u16Number));
                            str += MApp_ZUI_API_Strlen(str); //u8_idx = __strlen(p_string_buffer);
                            *str++ = CHAR_SPACE; //p_string_buffer[u8_idx++] = CHAR_SPACE;
                        #if(ENABLE_S2_PREDIT_SWITCH_LIST)
                            u16ProgPosition = u16ProgPosition - DTVcount - Radiocount;
                            MApp_CharTable_GetServiceNameToUCS2(bServiceType, u16ProgPosition, str, KEEP_CONTROL_CODE_NONE);
                        #else
                            MApp_CharTable_GetServiceNameToUCS2(bServiceType, u16ProgPosition-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY), str, KEEP_CONTROL_CODE_NONE);
                        #endif
                            str += MApp_ZUI_API_Strlen(str);
                        }
                    #endif
                    }
                    else
                #endif  //ENABLE_S2
        #endif // ENABLE_DVB
                    {
                        MEMBER_SERVICETYPE bServiceType = E_SERVICETYPE_INVALID;
                        U16 u16Position = 0xFFFF;
                        U16 u16Number = 0;

                        //PRINT_CURRENT_LINE();

                        E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eChProcBoundary = E_PROGACESS_INCLUDE_VISIBLE_ONLY;

                    #if(ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
                        if( _MApp_ZUI_ACT_IsFavMode() )
                            eChProcBoundary = CHPROC_FAV_ACCESS_BOUNDRY;
                    #endif

                        FAVORITE_LIST_DBINFO( printf(" eChProcBoundary=%u\n", eChProcBoundary); );

                        //msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, g_wProgramPosition, ( BYTE *)&bServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                        msAPI_CHPROC_CM_Get_ServiceType_Position_ByOrdinal(
                            (MEMBER_SERVICETYPE)pChListData->u8ServiceType, u16ProgPosition,
                            eChProcBoundary,
                            &bServiceType, &u16Position );

                        CHANNEL_LIST_DBINFO( printf(" u16ProgPosition=%u, Service=%u, Pos=%u\n", u16ProgPosition, bServiceType, u16Position); );

                        if( bServiceType != E_SERVICETYPE_INVALID )
                        {
                            msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, u16ProgPosition, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, eChProcBoundary);
                            CHANNEL_LIST_DBINFO( printf(" u16Number=%u\n", u16Number); );
                        }

                        // Print name
                    #if 0
                        //if( bServiceType != E_SERVICETYPE_ATV )
                        {
                            U8 au8ServiceName[100];
                            if(msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, g_wProgramPosition, au8ServiceName, E_SERVICE_ATTR_NAME, eBoundry) )
                            {
                                printf(" Name=%s\n", au8ServiceName);
                            }
                        }
                    #endif

                        if(msAPI_ATV_GetActiveProgramCount()==0 && bServiceType==E_SERVICETYPE_ATV)//Makes channel "0" when no ATV
                            u16Number=0;


                #if ENABLE_DVB
                        if( bServiceType == E_SERVICETYPE_DTV
                          ||bServiceType == E_SERVICETYPE_RADIO
                          ||bServiceType == E_SERVICETYPE_DATA
                          )
                        {
                            MApp_ZUI_DTV_ChNumString(u16Number, str);

                            str += MApp_ZUI_API_Strlen(str); //u8_idx = __strlen(p_string_buffer);
                            *str++ = CHAR_SPACE; //p_string_buffer[u8_idx++] = CHAR_SPACE;

                        #if 1
                            MApp_CharTable_GetServiceNameToUCS2(bServiceType, u16Position, str, KEEP_CONTROL_CODE_NONE);
                        #elif ENABLE_SBTVD_CM_APP
                            msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(g_wProgramPosition,&bServiceType,&g_wProgramPosition);
                            MApp_CharTable_GetServiceNameToUCS2(bServiceType, g_wProgramPosition, str, KEEP_CONTROL_CODE_NONE);
                        #else
                            MApp_CharTable_GetServiceNameToUCS2(bServiceType, g_wProgramPosition, str, KEEP_CONTROL_CODE_NONE);
                        #endif

                            str += MApp_ZUI_API_Strlen(str);
                        }
                        else
                #endif  //ENABLE_DVB
                        if (bServiceType == E_SERVICETYPE_ATV)
                        {
                            MApp_ZUI_API_GetU16String(u16Number+1);
                        #if ENABLE_SBTVD_ATV_SYSTEM
                            if(!IS_SBTVD_APP)
                        #endif
                            {
                                U8 u8Temp[MAX_STATION_NAME];
                                str += MApp_ZUI_API_Strlen(str); //u8_idx = __strlen(p_string_buffer);
                                *str++ = CHAR_SPACE; //p_string_buffer[u8_idx++] = CHAR_SPACE;

                                if(msAPI_ATV_GetStationName((BYTE)u16Number, u8Temp)) // Coverity 95841
                                {
                                    MApp_U8StringToU16String(u8Temp, str, MAX_STATION_NAME);
                                }
                                str += MApp_ZUI_API_Strlen(str);
                            }
                        }
                    }

                #if (ENABLE_DTV)
                    if ((str-CHAR_BUFFER) > MAX_LCN_SERVICE_NAME_LENGTH)
                    {
                        (CHAR_BUFFER)[MAX_LCN_SERVICE_NAME_LENGTH] = 0;
                    }
                #else
                    if ((str-CHAR_BUFFER) > 30)
                    {
                        (CHAR_BUFFER)[30] = 0;
                    }
                #endif

                    return CHAR_BUFFER;

                }
            }
        }
            break;

        default:
            break;

    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}


U16 MApp_ZUI_ACT_GetChannelListDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    //printf("=============== MApp_ZUI_ACT_GetChannelListDynamicBitmap() ========================\n");
//printf("DynamicBitmap: %u\n", hwnd);
    E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eChProcBoundary = E_PROGACESS_INCLUDE_VISIBLE_ONLY;

#if(ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
    if( _MApp_ZUI_ACT_IsFavMode() )
    {
        eChProcBoundary = CHPROC_FAV_ACCESS_BOUNDRY;
    }
#endif


#if ENABLE_CI_PLUS
    U8 u8OpNum = 0; //Evie++:get num of op index
  #if(ENABLE_DVB)
    if( IsDVBInUse() )
    {
        u8OpNum = MApp_CI_GetOpCacheCount(); //Evie++:get num of op index
    }
  #endif
#endif

    switch(hwnd)
    {
        case HWND_CHLIST_ITEM0_TYPE:
        case HWND_CHLIST_ITEM1_TYPE:
        case HWND_CHLIST_ITEM2_TYPE:
        case HWND_CHLIST_ITEM3_TYPE:
        case HWND_CHLIST_ITEM4_TYPE:
        case HWND_CHLIST_ITEM5_TYPE:
        case HWND_CHLIST_ITEM6_TYPE:
        case HWND_CHLIST_ITEM7_TYPE:
        case HWND_CHLIST_ITEM8_TYPE:
        case HWND_CHLIST_ITEM9_TYPE:
            //printf("HWND_CHLIST_ITEM0~9\n");
    #if (ENABLE_ATSC)
        if (IsAtscInUse() || IsATVInUse())
        {
            //CHAR_BUFFER[0] = 0;
            U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
            //printf("1 hwnd=%u, u8VisIndex=%u\n", hwnd, u8VisIndex);

            U16 wProgramPosition;

            wProgramPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);

            if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX)
              ||(wProgramPosition >= pChListData->u16TotalChCount)
              )
            {
                break; //for empty bitmap....
            }

            //printf("wProgramPosition=%u\n", wProgramPosition);

            MEMBER_SERVICETYPE eServiceType = msAPI_ChProc_ATSC_Get_ServiceType_By_ProgIdx(wProgramPosition);

            if( eServiceType == E_SERVICETYPE_RADIO )
            {
                if (ds_type == DS_FOCUS)
                {
                    return E_BMP_IDLE_IMG_ICON_RADIO_FOCUS;
                }
                else
                {
                    return E_BMP_IDLE_IMG_ICON_RADIO_UNFOCUS;
                }
            }
            else if( eServiceType == E_SERVICETYPE_DTV )
            {
                if (ds_type == DS_FOCUS)
                {
                    return E_BMP_IDLE_IMG_ICON_DTV_FOCUS;
                }
                else
                {
                    return E_BMP_IDLE_IMG_ICON_DTV_UNFOCUS;
                }
            }
            else // ATV
            {
                if (ds_type == DS_FOCUS)
                {
                    return E_BMP_IDLE_IMG_ICON_ATV_FOCUS;
                }
                else
                {
                    return E_BMP_IDLE_IMG_ICON_ATV_UNFOCUS;
                }
            }
        }
        else
    #endif
        {
            U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
            U16 wProgramPosition;

            wProgramPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);
            CHANNEL_LIST_DBINFO( printf(" [TYPE] u8VisIndex=%d, wProgramPosition = %d, u16TotalChCount = %d\n", u8VisIndex, wProgramPosition, pChListData->u16TotalChCount); );

            if( _MApp_ZUI_ACT_IsFavMode() )
            {
                if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX) )
                {
                        break;
                }
            }
            else
            {
                if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX)
                 || (wProgramPosition >= pChListData->u16TotalChCount)
                  )
                {
                        break;
                }
            }


            {
                EN_SERVICE_TYPE u8Type = SERVICE_TYPE_INVALIDE;
                BOOLEAN bSkip = false;

                msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition, &bSkip, E_SERVICE_ATTR_SKIPPED, eChProcBoundary);
                msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition, (BYTE *)&u8Type, E_SERVICE_ATTR_TYPE, eChProcBoundary);

          #if ENABLE_CI_PLUS
            if ((u8OpNum>0)&&(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN)))
            {
               return 0xFFFF;
            }
            else
          #endif
            {
                if (ds_type == DS_FOCUS && !bSkip)
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
#if ENABLE_SBTVD_ATV_SYSTEM
                        if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                        {
                            return E_BMP_ICON_CATV_F;
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
#if ENABLE_SBTVD_ATV_SYSTEM
                        if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                        {
                            return E_BMP_ICON_CATV_N;
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
        }
            break;

        case HWND_CHLIST_ITEM0_LOCK:
        case HWND_CHLIST_ITEM1_LOCK:
        case HWND_CHLIST_ITEM2_LOCK:
        case HWND_CHLIST_ITEM3_LOCK:
        case HWND_CHLIST_ITEM4_LOCK:
        case HWND_CHLIST_ITEM5_LOCK:
        case HWND_CHLIST_ITEM6_LOCK:
        case HWND_CHLIST_ITEM7_LOCK:
        case HWND_CHLIST_ITEM8_LOCK:
        case HWND_CHLIST_ITEM9_LOCK:
            //printf("HWND_CHLIST_ITEM0_LOCK ~ 9\n");
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
                U16 wProgramPosition;

                //printf("2 hwnd=%u, u8VisIndex=%u\n", hwnd, u8VisIndex);

                wProgramPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);
                if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX)
                  ||(wProgramPosition >= pChListData->u16TotalChCount)
                  )
                {
                    break;
                }
                //printf("wProgramPosition=%u\n", wProgramPosition);

            #if (ENABLE_ATSC)
                if( IsAtscInUse() || IsATVInUse() )
                {
                    BOOLEAN bLock = msAPI_ChProc_ATSC_Get_Attr_Lock_By_ProgIdx(wProgramPosition);

                    // TODO : How to draw "LOCK"?
                    if( bLock )
                    {
                    }
                    else
                    {
                    }

                    return 0xFFFF;
                }
                else
            #endif
              #if ENABLE_CI_PLUS
                if((u8OpNum>0)&&(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN)))
                {
                     return 0xFFFF;
                }
                else
              #endif
                {
                    BOOLEAN bLock = false;
                    BOOLEAN bSkip = false;
                    //PRINT_CURRENT_LINE();
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition, &bSkip, E_SERVICE_ATTR_SKIPPED, eChProcBoundary);
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition, &bLock, E_SERVICE_ATTR_LOCKED, eChProcBoundary);
                    if (bLock)
                    {
                        //if (ds_type == DS_FOCUS && !bSkip)
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

        case HWND_CHLIST_ITEM0_FAV:
        case HWND_CHLIST_ITEM1_FAV:
        case HWND_CHLIST_ITEM2_FAV:
        case HWND_CHLIST_ITEM3_FAV:
        case HWND_CHLIST_ITEM4_FAV:
        case HWND_CHLIST_ITEM5_FAV:
        case HWND_CHLIST_ITEM6_FAV:
        case HWND_CHLIST_ITEM7_FAV:
        case HWND_CHLIST_ITEM8_FAV:
        case HWND_CHLIST_ITEM9_FAV:
            //printf("HWND_CHLIST_ITEM0_FAV ~ 9\n");
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
                U16 wProgramPosition;

                wProgramPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);
                FAVORITE_LIST_DBINFO( printf(" [FAVICON] u8VisIndex=%d, wProgramPosition = %d, u16TotalChCount = %d\n", u8VisIndex, wProgramPosition, pChListData->u16TotalChCount); );

                if( _MApp_ZUI_ACT_IsFavMode() )
                {
                    if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX) )
                    {
                            break;
                    }
                }
                else
                {
                    if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX)
                     || (wProgramPosition >= pChListData->u16TotalChCount)
                      )
                    {
                            break;
                    }
                }

            #if (ENABLE_ATSC)
                if( IsAtscInUse() || IsATVInUse() )
                {
                    BOOL bIsFav = msAPI_ChProc_ATSC_Get_Attr_Fav_By_ProgIdx(wProgramPosition);

                    if (bIsFav)
                    {
                        if (ds_type == DS_FOCUS)
                        {
                            return E_BMP_IDLE_IMG_ICON_FAVORITE_FOCUS;
                        }
                        else
                        {
                            return E_BMP_IDLE_IMG_ICON_FAVORITE_UNFOCUS;
                        }
                    }
                    break;
                }
                else
            #endif
                {

                  #if ENABLE_CI_PLUS
                    if((u8OpNum>0)&&(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN)))
                    {
                         return 0xFFFF;
                    }
                    else
                  #endif
                    {
                        BOOLEAN bFav = false;
                        BOOLEAN bSkip = false;

                        msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition, &bSkip, E_SERVICE_ATTR_SKIPPED, eChProcBoundary);
                        msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition, &bFav, E_SERVICE_ATTR_FAVORITE, eChProcBoundary);

                        if (bFav)
                        {
                            if (ds_type == DS_FOCUS && !bSkip)
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
            }
            break;

        case HWND_CHLIST_ITEM0_SCRAMBLE:
        case HWND_CHLIST_ITEM1_SCRAMBLE:
        case HWND_CHLIST_ITEM2_SCRAMBLE:
        case HWND_CHLIST_ITEM3_SCRAMBLE:
        case HWND_CHLIST_ITEM4_SCRAMBLE:
        case HWND_CHLIST_ITEM5_SCRAMBLE:
        case HWND_CHLIST_ITEM6_SCRAMBLE:
        case HWND_CHLIST_ITEM7_SCRAMBLE:
        case HWND_CHLIST_ITEM8_SCRAMBLE:
        case HWND_CHLIST_ITEM9_SCRAMBLE:
            //printf("HWND_CHLIST_ITEM0_SCRAMBLE ~ 9\n");
        #if(ENABLE_DTV)
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
                U16 wProgramPosition = 0;

                wProgramPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);
                if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX)
                  ||(wProgramPosition >= pChListData->u16TotalChCount)
                  )
                {
                    break;
                }

            #if (ENABLE_ATSC)
                if( IsAtscInUse() || IsATVInUse() )
                {
                    // todo
                    break;
                }
                else
            #endif
                {
                #if ENABLE_DVB
                  #if ENABLE_CI_PLUS
                    if(( TRUE == MApp_CI_IsOpMode() )||(_MApp_ZUI_ACT_IsOpProfileMenuMode()))
                    {
                         return 0xFFFF;
                    }
                    else
                  #endif
                    {
                        MEMBER_SERVICETYPE bServiceType;
                        BOOLEAN bScramble = FALSE;
                        U16 u16CMPosition;

                        if( msAPI_CHPROC_CM_Get_ServiceType_Position_ByOrdinal(
                                (MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition,
                                eChProcBoundary,
                                &bServiceType, &u16CMPosition ) )
                        {
                            bScramble = msAPI_CM_GetProgramAttribute(bServiceType,u16CMPosition, E_ATTRIBUTE_IS_SCRAMBLED);
                        }

                        if (bScramble == TRUE)
                        {
                            if(ds_type == DS_FOCUS)
                                return E_BMP_IDLE_IMG_ICON_SSL_FOCUS;
                            else
                                return E_BMP_IDLE_IMG_ICON_SSL_UNFOCUS;
                        }
                        else
                        {
                            return 0xFFFF;//empty bitmap....
                        }

                    }
                #endif
                }
            }
        #endif
            break;

        #if 1//ENABLE_S2
            case HWND_CHLIST_ITEM0_SKIP:
            case HWND_CHLIST_ITEM1_SKIP:
            case HWND_CHLIST_ITEM2_SKIP:
            case HWND_CHLIST_ITEM3_SKIP:
            case HWND_CHLIST_ITEM4_SKIP:
            case HWND_CHLIST_ITEM5_SKIP:
            case HWND_CHLIST_ITEM6_SKIP:
            case HWND_CHLIST_ITEM7_SKIP:
            case HWND_CHLIST_ITEM8_SKIP:
            case HWND_CHLIST_ITEM9_SKIP:
            {
                U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
                U16 wProgramPosition;

                wProgramPosition = MApp_ZUI_ACT_ChList_Get_ProgPos_By_VisIndex(u8VisIndex);

                if( _MApp_ZUI_ACT_IsFavMode() )
                {
                    if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX) )
                    {
                            break;
                    }
                }
                else
                {
                    if( (wProgramPosition == CHANNEL_LIST_INVALID_PROGINDEX)
                     || (wProgramPosition >= pChListData->u16TotalChCount)
                      )
                    {
                            break;
                    }
                }

            #if ENABLE_CI_PLUS
                if((u8OpNum>0)&&(MApp_ZUI_API_IsWindowVisible(HWND_CHLIST_OP_MENU_BOTTOM_HALF_ENTER_OP_BTN)))
                {
                    return 0xFFFF;
                }
                else
            #endif    //ENABLE_CI_PLUS
                {
                    BOOLEAN bFav = false;
                    BOOLEAN bSkip = false;

                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition, &bSkip, E_SERVICE_ATTR_SKIPPED, eChProcBoundary);
                    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)pChListData->u8ServiceType, wProgramPosition, &bFav, E_SERVICE_ATTR_FAVORITE, eChProcBoundary);

                    if (bSkip)
                    {
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
        #endif

        default:
            break;
    }

    return 0xFFFF; //for empty bitmap....
}

OSD_COLOR MApp_ZUI_ACT_GetChannelListDynamicColor(HWND hwnd, DRAWSTYLE_TYPE type, OSD_COLOR colorOriginal)
{
//printf("DynamicColor: %u\n", hwnd);

    U16 u16SrvPageCurIndex;
    U16 g_wProgramPosition;
    UNUSED(type);
  #if ENABLE_CI_PLUS
    U8 u8OpNum = MApp_CI_GetOpCacheCount();
  #endif
    u16SrvPageCurIndex = (U16)_MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);

    #if ENABLE_CI_PLUS
    if(_MApp_ZUI_ACT_IsOpProfileMenuMode())
    {
        switch(hwnd)
        {
            case HWND_CHLIST_ITEM0_TEXT:
            case HWND_CHLIST_ITEM1_TEXT:
            case HWND_CHLIST_ITEM2_TEXT:
            case HWND_CHLIST_ITEM3_TEXT:
            case HWND_CHLIST_ITEM4_TEXT:
            case HWND_CHLIST_ITEM5_TEXT:
            case HWND_CHLIST_ITEM6_TEXT:
            case HWND_CHLIST_ITEM7_TEXT:
            case HWND_CHLIST_ITEM8_TEXT:
            case HWND_CHLIST_ITEM9_TEXT:
            {
                EN_DELIVERY_SYS_TYPE eProfileDtvSysType = E_DELIVERY_SYS_NONE;
                U8 u8VisIndex = _MApp_ZUI_ACT_ChannelListWindowMapToIndex(hwnd);
                U8 i = 0;
                g_wProgramPosition = pChListData->u8CurrentPage*CHANNEL_LIST_PAGE_NUM + u8VisIndex;
                if(g_wProgramPosition >= MApp_CI_GetOpCacheCount())
                {
                    break;
                }
                for(i = g_wProgramPosition; i<u8OpNum; i++)
                {
                    do
                    {
                        MApp_CI_GetOpDtvSysTypeByIndex(i, &eProfileDtvSysType);
                        if(eProfileDtvSysType != E_DELIVERY_SYS_NONE )
                        {
                            if((eProfileDtvSysType == E_DELIVERY_SYS_CDSD) && (MApp_DVBType_GetCurrentType() == EN_DVB_C_TYPE))
                            {
                                return colorOriginal;
                            }
                            else if ((eProfileDtvSysType == E_DELIVERY_SYS_TDSD) && (MApp_DVBType_GetCurrentType() == EN_DVB_T_TYPE))
                            {
                                return colorOriginal;
                            }
                            else
                            {
                                return CH_LIST_CURRENT_CN_TEXT_DISABLE_COLOR;
                            }
                            break;
                        }
                    }while((++i)<MAX_OP_CACHE_NUM);
                }
            }
            break;
        }
    }
    else
    #endif
    {

        if(_MApp_ZUI_ACT_IsFavMode()
#if (ENABLE_S2_FIND_PROGRAM_BYNAME && ((UI_SKIN_1366X768X565 == UI_SKIN_SEL)||(UI_SKIN_1920X1080X565== UI_SKIN_SEL)||(UI_SKIN_960X540X565== UI_SKIN_SEL)))
        ||_MApp_ZUI_ACT_IsFindProByNameMode()
#endif
        )
        {
            return colorOriginal;
        }
        else
        {
            g_wProgramPosition = (U16)(pChListData->u8CurrentPage*CHANNEL_LIST_PAGE_NUM) + u16SrvPageCurIndex;
        }

#if 1
#if (UI_SKIN_960X540XI8 != UI_SKIN_SEL)
        if(g_wProgramPosition == pChListData->u16CurCh)
        {
            if(u16SrvPageCurIndex == (U16)_MApp_ZUI_ACT_ChannelListWindowMapToIndex( MApp_ZUI_API_GetFocus())) //is the high light program
                return CH_LIST_CURRENT_CN_TEXT_HL_COLOR;
            else
                return CH_LIST_CURRENT_CN_TEXT_COLOR;
        }
#endif
#else
        if(g_wProgramPosition == pChListData->u16CurCh)
        {
            if(u16SrvPageCurIndex == (U16)_MApp_ZUI_ACT_ChannelListWindowMapToIndex( MApp_ZUI_API_GetFocus())) //is the high light program
            {
                if(IS_HIDE_CH(pChListData->u16CurCh))
                {
                    return CH_LIST_CURRENT_CN_TEXT_HL_DISABLE_COLOR;
                }
                else
                {
                    return CH_LIST_CURRENT_CN_TEXT_HL_COLOR;
                }
            }
            else
            {
                if(IS_HIDE_CH(pChListData->u16CurCh))
                {
                    return CH_LIST_CURRENT_CN_TEXT_DISABLE_COLOR;
                }
                else
                {
                    return CH_LIST_CURRENT_CN_TEXT_COLOR;
                }
            }
        }
        else
        {
                if(IS_HIDE_CH(g_wProgramPosition))
                {
                    return CH_LIST_CURRENT_CN_TEXT_DISABLE_COLOR;
                }
        }
#endif
        }
    return colorOriginal;
}

static void _MApp_ZUI_ACT_Chlist_GetTotalProgCount(U8 u8ServiceType)
{
#if (ENABLE_ATSC)
    if (IsAtscInUse() || IsATVInUse())
    {
    #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
        pChListData->u16TotalChCount = stChSettingDisp[ANT_AIR].u16MainListSrvNum + stChSettingDisp[ANT_CATV].u16MainListSrvNum;
    #else
        pChListData->u16TotalChCount = stChSetting.u16MainListSrvNum;
    #endif
    }
    else
#endif
    {
        pChListData->u16TotalChCount = msAPI_CHPROC_CM_CountProgram((MEMBER_SERVICETYPE)u8ServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    }
}

#if ENABLE_XL3_API
U16 MApp_ZUI_ACT_GetChannelNumber(WORD wOrdinal)
{
    U16 u16Number = 0;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wOrdinal, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_ALL);

    return u16Number;
}

LPTSTR MApp_ZUI_ACT_GetChannelCHName(WORD wOrdinal)
{
    MEMBER_SERVICETYPE msServiceType;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wOrdinal, (BYTE *)&msServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_ALL);

    if(msServiceType == E_SERVICETYPE_ATV)
    {
        msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wOrdinal, au8Section, E_SERVICE_ATTR_NAME, E_PROGACESS_INCLUDE_ALL);

        MApp_U8StringToU16String(au8Section, CHAR_BUFFER, strlen((char*)au8Section));
    }
    else
    {
        MApp_CharTable_GetServiceNameToUCS2(msServiceType, wOrdinal, CHAR_BUFFER, KEEP_CONTROL_CODE_NONE);
    }
    return CHAR_BUFFER;
}

WORD MApp_ZUI_ACT_GetOridnalByChNum(U16 u16ChNum, BOOL bIsDtv)
{
    U16 u16Number;
    WORD i, wTvStart, wTvEnd;

    WORD wCount = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_ALL);

    wCount += msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_ALL);

#if NORDIG_FUNC
    wCount = msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_ALL);
#endif

    if(bIsDtv)
    {
        wTvStart = 0;
        wTvEnd = wCount;
    }
    else
    {
        wTvStart = wCount;
        wTvEnd = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);;
        //u16ChNum--;
    }

    for(i=wTvStart; i < wTvEnd; i++)
    {
        if(msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, i, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_ALL))

        if(u16Number == u16ChNum)
            return i;
    }
    return INVALID_ORDINAL;
}
#endif
#undef MAPP_ZUI_ACTCHLIST_C
