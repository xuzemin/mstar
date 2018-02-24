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
#define MAPP_ZUI_ACTKTV_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal
//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"
#ifdef ENABLE_KTV
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "msAPI_Memory.h"
#include "drvUSB.h"
#include "msAPI_MSDCtrl.h"
#include "apiGOP.h"
#include "msAPI_audio.h"
#include "MApp_Audio.h"
#include "mapp_gb2unicode.h"
#include "MApp_ZUI_APIChineseIME.h"
#include "MApp_KTV_Main.h"
#include "MApp_KTV.h"
#include "MApp_KTV_Lyric.h"
#include "MApp_Ktv_DbSearch.h"
#include "MApp_ZUI_ACTKTV.h"
#include "MApp_UiMenuDef.h"
#include "MApp_RestoreToDefault.h"
#include "GPIO.h"
#include "FSUtil.h"
#include "IOUtil.h"
#include <stdio.h>
#include <string.h>
#include "ZUI_tables_h.inl"
#include "MApp_InputSource.h"
#include "MApp_TopStateMachine.h"

#define ZUIKTV_DBG(x)   x
static KTV_DIGIT_INFO           _mKTVDigitInfo;
static KTV_LETTER_INFO          _mKTVLetterInfo;
static KTV_DIALOG_INFO           _mKTVDialogInfo;
static KTV_TONE_OF_SONGS_INFO           _mKTVToneInfo;
static EN_SONG_CLASS en_song_class = SONG_CLASS_MALE;
static HWND hwnd_use_letter_board = HWND_KTV_SEARCH_BY_SINGER_PAGE; // Which page use software keyboard
static HWND hwnd_use_confirm_dialog = HWND_KTV_SEARCH_FOUND_SONGS; // Which page use confirm dailog
static HWND hwnd_use_songlist_page = HWND_KTV_SEARCH_BY_SINGER_PAGE; // Which page use song list page
static HWND hwnd_use_tone_page = HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST; // Which page use tone page
static U8 u8KTVSearchSingerListPage = 0;
static U8 u8KTVSearchSongListPage = 0;
static U8 u8KTVSearchSongWordNubmer = 0;
static U8 u8KTVSearchSongFirstWordPageNum = 0;
static U8 u8KTVSearchSongLanguage = 0;
static U8 KTVWaitingStringbuf[26];
static U8 u8WaitingCounter = 0;
static U8 u8TimeoutCounter = 0;
static BOOLEAN bIsthefirsttime = TRUE;
static U16 u16KTVWhichSingerSelected = 0;
static U16 u16KTVWhichSongSelected = 0;
static U16 u16KTVSearchSongFirstWord[25];

static  HWND _ZUI_TBLSEG hwnd2digitkey[][2] =
{
    { HWND_KTV_SOFTWARE_KEY_0, '0'},
    { HWND_KTV_SOFTWARE_KEY_1, '1'},
    { HWND_KTV_SOFTWARE_KEY_2, '2'},
    { HWND_KTV_SOFTWARE_KEY_3, '3'},
    { HWND_KTV_SOFTWARE_KEY_4, '4'},
    { HWND_KTV_SOFTWARE_KEY_5, '5'},
    { HWND_KTV_SOFTWARE_KEY_6, '6'},
    { HWND_KTV_SOFTWARE_KEY_7, '7'},
    { HWND_KTV_SOFTWARE_KEY_8, '8'},
    { HWND_KTV_SOFTWARE_KEY_9, '9'},
    { HWND_KTV_SOFTWARE_KEY_ENTER, 1},
    { HWND_KTV_SOFTWARE_KEY_INSERT, 2},
    { HWND_KTV_SOFTWARE_KEY_CANCEL, 3},
};
static  HWND _ZUI_TBLSEG hwnd2letterkey[][2] =
{
    { HWND_KTV_SOFTWARE_KEY_A, 'A'},
    { HWND_KTV_SOFTWARE_KEY_B, 'B'},
    { HWND_KTV_SOFTWARE_KEY_C, 'C'},
    { HWND_KTV_SOFTWARE_KEY_D, 'D'},
    { HWND_KTV_SOFTWARE_KEY_E, 'E'},
    { HWND_KTV_SOFTWARE_KEY_F, 'F'},
    { HWND_KTV_SOFTWARE_KEY_G, 'G'},
    { HWND_KTV_SOFTWARE_KEY_H, 'H'},
    { HWND_KTV_SOFTWARE_KEY_I, 'I'},
    { HWND_KTV_SOFTWARE_KEY_J, 'J'},
    { HWND_KTV_SOFTWARE_KEY_K, 'K'},
    { HWND_KTV_SOFTWARE_KEY_L, 'L'},
    { HWND_KTV_SOFTWARE_KEY_M, 'M'},
    { HWND_KTV_SOFTWARE_KEY_N, 'N'},
    { HWND_KTV_SOFTWARE_KEY_O, 'O'},
    { HWND_KTV_SOFTWARE_KEY_P, 'P'},
    { HWND_KTV_SOFTWARE_KEY_Q, 'Q'},
    { HWND_KTV_SOFTWARE_KEY_R, 'R'},
    { HWND_KTV_SOFTWARE_KEY_S, 'S'},
    { HWND_KTV_SOFTWARE_KEY_T, 'T'},
    { HWND_KTV_SOFTWARE_KEY_U, 'U'},
    { HWND_KTV_SOFTWARE_KEY_V, 'V'},
    { HWND_KTV_SOFTWARE_KEY_W, 'W'},
    { HWND_KTV_SOFTWARE_KEY_X, 'X'},
    { HWND_KTV_SOFTWARE_KEY_Y, 'Y'},
    { HWND_KTV_SOFTWARE_KEY_Z, 'Z'},
    { HWND_KTV_SOFTWARE_KEY_CLEAR, 4},
};
static  HWND _ZUI_TBLSEG _SingerNameListPageItemHwndList[NUM_OF_KTV_SINGERS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM1,
     HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM2,
     HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM3,
     HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM4,
     HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM5,
     HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM6,
     HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM7,
     HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM8,
};
static  HWND _ZUI_TBLSEG _SingerListPageItemHwndList[NUM_OF_KTV_SINGERS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8
};
static  HWND _ZUI_TBLSEG _SingerListPageItemIDHwndList[NUM_OF_KTV_SINGERS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1_ID,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2_ID,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3_ID,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4_ID,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5_ID,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6_ID,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7_ID,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8_ID
};
static  HWND _ZUI_TBLSEG _SingerListPageItemSingerHwndList[NUM_OF_KTV_SINGERS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8_SINGER
};
static  HWND _ZUI_TBLSEG _SingerListPageItemPinyinHwndList[NUM_OF_KTV_SINGERS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1_PINYIN,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2_PINYIN,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3_PINYIN,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4_PINYIN,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5_PINYIN,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6_PINYIN,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7_PINYIN,
     HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8_PINYIN
};
static  HWND _ZUI_TBLSEG _SongListPageItemHwndList[NUM_OF_KTV_SONGS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM2,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM3,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM4,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM5,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM6,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM7,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM8
};
static  HWND _ZUI_TBLSEG _SongListPageItemIDHwndList[NUM_OF_KTV_SONGS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1_ID,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM2_ID,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM3_ID,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM4_ID,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM5_ID,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM6_ID,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM7_ID,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM8_ID
};
static  HWND _ZUI_TBLSEG _SongListPageItemSongsHwndList[NUM_OF_KTV_SONGS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1_SONGS,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM2_SONGS,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM3_SONGS,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM4_SONGS,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM5_SONGS,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM6_SONGS,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM7_SONGS,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM8_SONGS
};
static  HWND _ZUI_TBLSEG _SongListPageItemSingerHwndList[NUM_OF_KTV_SONGS_PER_PAGE]=
{
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM2_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM3_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM4_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM5_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM6_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM7_SINGER,
     HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM8_SINGER
};

static  HWND _ZUI_TBLSEG _SongToPlayItemHwndList[NUM_OF_KTV_SONGS_PER_PAGE]=
{
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM2,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM3,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM4,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM5,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM6,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM7,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8
};

static  HWND _ZUI_TBLSEG _SongToPlayItemIDHwndList[NUM_OF_KTV_SONGS_PER_PAGE]=
{
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1_SONGID,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM2_SONGID,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM3_SONGID,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM4_SONGID,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM5_SONGID,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM6_SONGID,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM7_SONGID,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8_SONGID
};

static  HWND _ZUI_TBLSEG _SongToPlayItemSongHwndList[NUM_OF_KTV_SONGS_PER_PAGE]=
{
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1_SONGS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM2_SONGS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM3_SONGS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM4_SONGS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM5_SONGS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM6_SONGS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM7_SONGS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8_SONGS
};

static  HWND _ZUI_TBLSEG _SongToPlayItemSingerHwndList[NUM_OF_KTV_SONGS_PER_PAGE]=
{
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1_SINGERS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM2_SINGERS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM3_SINGERS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM4_SINGERS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM5_SINGERS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM6_SINGERS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM7_SINGERS,
     HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8_SINGERS
};

static U8 _WaitingType[][26]=
{
    {"乐器库装载中..."},
    {"乐曲装载中..."},
    {"服务器错误，播下一首"},
};

/******************************************************************************/
/// GB convert to UNICODE
/// @param  pu8Dst point to the GB string buffer
/// @return  N/A
/******************************************************************************/
void MApp_ZUI_ACTKTV_GBTOUNICODE(U8 *pu8Dst)
{
    U8 u8Len=0, u8Dst=0;
    U8  i;
    U16 u16convert;

    for(i=0; i<255; i += 2)
    {
        if((pu8Dst[i] == 0) &&  (pu8Dst[i+1] == 0))
        {
            //printf("\r\n u8Len = %bx", u8Len);
            break;
        }
        else
        {
            u8Len++;
        }
    }

    for(i=0; i<u8Len; i++)
    {
        u16convert = ((U16)pu8Dst[u8Dst] << 8) | (U16)pu8Dst[u8Dst+1];
        u16convert = MApp_GB2Unicode(u16convert);
        pu8Dst[u8Dst] = (U8)u16convert;
        pu8Dst[u8Dst+1] = (U8)(u16convert >> 8);
        u8Dst+=2;
    }
}

/******************************************************************************/
/// Number convert to UNICODE string
/// @param  u16Num -> the number which want to be converted.
/// @param  pu8Dst point to a string buffer, save the result
/// @return  N/A
/******************************************************************************/
void MApp_ZUI_ACTKTV_NUMTOUNICODE(U16 u16Num, U8 *pu8Dst)
{
    U8 u8tmp;
    U8 i, j;
    U16 u16Pow;

    for(i=0; i< 5; i++)
    {
        u16Pow = 1;
        for(j=0; j<i; j++)
        {
            u16Pow *= 10;
        }
        u8tmp = (U8)(u16Num/(10000/u16Pow));
        u16Num = u16Num%(10000/u16Pow);
        pu8Dst[i*2] = u8tmp + 0x30;
        pu8Dst[i*2+1] = 0;
        pu8Dst[i*2+2] = 0;
        pu8Dst[i*2+3] = 0;
    }
}

/******************************************************************************/
/// UNICODE stringconvert to Number
/// @param  pu8Dst point to a Unicode string, the char must be 0~9
/// @return  U32 number
/******************************************************************************/
U32 MApp_ZUI_ACTKTV_UnicodetoNum(U8 *pu8Dst)
{
    U32 u32tmp = 0;
    U8 len = 0, i;

    for(i=0; i< 50; i++)
    {
        if((pu8Dst[i*2] == 0) && (pu8Dst[i*2+1] == 0))
        {
            len = i;
            break;
        }
    }
    for(i=0; i< len; i++)
    {
        u32tmp = u32tmp*10 + (pu8Dst[i*2] - 0x30);
    }

    return u32tmp;
}

void MApp_ZUI_ACT_TerminateKTV(void)
{
    ZUI_MSG(printf("[]term:KTV\n");)
    //MApp_KTV_Main_Exit();
}

S16 MApp_ZUI_ACT_GetKTVDynamicValue(HWND hwnd)
{
    U16 u16Temp;

    switch(hwnd)
    {
        case HWND_KTV_SONG_PLAY_VOLUME:
            return stGenSetting.g_SoundSetting.Volume;
        case HWND_KTV_SETUP_MUSIC_VOLUME_BAR:
            u16Temp = ((_eKTVVolumeSetting.MusicVolume - KTV_MUSIC_VOLUME_MIN)*100)/(KTV_MUSIC_VOLUME_MAX - KTV_MUSIC_VOLUME_MIN);
            return u16Temp;
        case HWND_KTV_SETUP_MIC_VOLUME_BAR:
            u16Temp = ((_eKTVVolumeSetting.MicVolume - KTV_MIC_VOLUME_MIN)*100)/(KTV_MIC_VOLUME_MAX - KTV_MIC_VOLUME_MIN);
            return u16Temp;
        case HWND_KTV_SETUP_ECHO_BAR:
            u16Temp = ((_eKTVVolumeSetting.Echo - KTV_ECHO_MIN)*100)/(KTV_ECHO_MAX- KTV_ECHO_MIN);
            return u16Temp;
        case HWND_KTV_SETUP_MELODY_VOLUME_BAR:
            u16Temp = ((_eKTVVolumeSetting.MelodyVolume - KTV_MELODY_VOLUME_MIN)*100)/(KTV_MELODY_VOLUME_MAX - KTV_MELODY_VOLUME_MIN);
            return u16Temp;
        case HWND_KTV_SETUP_TONE_BAR:
            u16Temp = ((_eKTVVolumeSetting.MusicKey - KTV_MUSIC_KEY_MIN)*100)/(KTV_MUSIC_KEY_MAX - KTV_MUSIC_KEY_MIN);
            return u16Temp;
        case HWND_KTV_SETUP_PLAY_SPEED_BAR:
            u16Temp = ((_eKTVVolumeSetting.MusicTempo - KTV_MUSIC_TEMPO_MIN)*100)/(KTV_MUSIC_TEMPO_MAX - KTV_MUSIC_TEMPO_MIN);
            return u16Temp;
         default:
            break;
    }
    return 0; //for empty  data
}
LPTSTR MApp_ZUI_ACT_GetKTVDynamicText(HWND hwnd)
{
    U8 u8ItemIdx;
    U8 i;
    U16 u16ItemIndex;

    CHAR_BUFFER[0] = 0;
    CHAR_BUFFER[1] = 0;
    //printf("Dynamic Text : hwnd(%d)\n", (U16)hwnd);
    switch(hwnd)
    {
        case HWND_KTV_SEARCH_BY_ID_IDVALUE:
            memcpy(CHAR_BUFFER, _mKTVDigitInfo.u8Sting, sizeof(_mKTVDigitInfo.u8Sting));
        break;
        case HWND_KTV_SEARCH_BY_SINGER_PINYIN_EDIT:
            memcpy(CHAR_BUFFER, _mKTVLetterInfo.u8Sting, sizeof(_mKTVLetterInfo.u8Sting));
        break;
        case HWND_KTV_DIALOG_LINE1:
            memcpy(CHAR_BUFFER, _mKTVDialogInfo.u8Line1Sting, sizeof(_mKTVDialogInfo.u8Line1Sting));
            //printf("\r\n CHAR_BUFFER=%bx  %bx", CHAR_BUFFER[0], CHAR_BUFFER[1]);
        break;
        case HWND_KTV_WAITING_TEXT:
            memcpy(CHAR_BUFFER, KTVWaitingStringbuf, sizeof(KTVWaitingStringbuf));
        break;
        case HWND_KTV_DIALOG_LINE1_1:
        {
            U16 u16Name[NUM_OF_SONG_STRING];
            if((hwnd_use_confirm_dialog == HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ONE) || (hwnd_use_confirm_dialog == HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ALL))
                break;

            switch(hwnd_use_songlist_page )
            {
                case HWND_KTV_SEARCH_BY_NAME_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                case HWND_KTV_SEARCH_BY_LASTUPDATE:
                case HWND_KTV_SEARCH_BY_POPULAR:
                    if(st_searchedsong_buf == NULL)
                        break;

                    for(i=0; i<st_searchedsong_buf->st_songbuf[u16KTVWhichSongSelected]->wsSongName[0]; i++)
                    {
                        u16Name[i] = st_searchedsong_buf->st_songbuf[u16KTVWhichSongSelected]->wsSongName[i+1];
                        u16Name[i+1] = 0;
                    }
                    memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                break;

                case HWND_KTV_SONGS_HAD_SING:
                    if(st_ktv_list == NULL)
                        break;

                    for(i=0; i<st_ktv_list->st_played_song_list[u16KTVWhichSongSelected].u16SongSting[0]; i++)
                    {
                        u16Name[i] = st_ktv_list->st_played_song_list[u16KTVWhichSongSelected].u16SongSting[i+1];
                        u16Name[i+1] = 0;
                    }
                    memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                break;

                default:
                break;
            }
        }
        break;

        case HWND_KTV_DIALOG_LINE2:
            memcpy(CHAR_BUFFER, _mKTVDialogInfo.u8Line2Sting, sizeof(_mKTVDialogInfo.u8Line2Sting));
        break;

        case HWND_KTV_TONE_OF_SONGS_INFO_LINE1:
            memcpy(CHAR_BUFFER, _mKTVToneInfo.u8Line1Sting, sizeof(_mKTVToneInfo.u8Line1Sting));
        break;

        case HWND_KTV_TONE_OF_SONGS_INFO_LINE1_SONG:
        {
            U16 u16Name[NUM_OF_SONG_STRING];
            switch(hwnd_use_songlist_page )
            {
                case HWND_KTV_SEARCH_BY_NAME_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                case HWND_KTV_SEARCH_BY_LASTUPDATE:
                case HWND_KTV_SEARCH_BY_POPULAR:
                    if(st_searchedsong_buf == NULL)
                        break;

                    for(i=0; i<st_searchedsong_buf->st_songbuf[u16KTVWhichSongSelected]->wsSongName[0]; i++)
                    {
                        u16Name[i] = st_searchedsong_buf->st_songbuf[u16KTVWhichSongSelected]->wsSongName[i+1];
                        u16Name[i+1] = 0;
                    }
                    memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                break;

                case HWND_KTV_MY_FAVOURITE:
                    if(st_ktv_list == NULL)
                        break;

                    for(i=0; i<st_ktv_list->st_favor_song_list[u16KTVWhichSongSelected].u16SongSting[0]; i++)
                    {
                        u16Name[i] = st_ktv_list->st_favor_song_list[u16KTVWhichSongSelected].u16SongSting[i+1];
                        u16Name[i+1] = 0;
                    }
                    memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                break;

                case HWND_KTV_SONGS_HAD_SING:
                    if(st_ktv_list == NULL)
                        break;

                    for(i=0; i<st_ktv_list->st_played_song_list[u16KTVWhichSongSelected].u16SongSting[0]; i++)
                    {
                        u16Name[i] = st_ktv_list->st_played_song_list[u16KTVWhichSongSelected].u16SongSting[i+1];
                        u16Name[i+1] = 0;
                    }
                    memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                break;

                default:
                break;
            }

            if((hwnd_use_tone_page == HWND_KTV_SOFTWARE_KEY_ENTER) ||( hwnd_use_tone_page == HWND_KTV_SOFTWARE_KEY_INSERT))
            {
                if(st_searchedsong_buf == NULL)
                break;

                for(i=0; i<st_searchedsong_buf->st_songbuf[0]->wsSongName[0]; i++)
                {
                    u16Name[i] = st_searchedsong_buf->st_songbuf[0]->wsSongName[i+1];
                    u16Name[i+1] = 0;
                }
                memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
            }
        }
        break;

        case HWND_KTV_TONE_OF_SONGS_INFO_LINE2:
            memcpy(CHAR_BUFFER, _mKTVToneInfo.u8Line2Sting, sizeof(_mKTVToneInfo.u8Line2Sting));
        break;

        case HWND_KTV_CONTROL_VOLUME_MINUS:
            memcpy(CHAR_BUFFER, "-", sizeof("-"));
        break;

        case HWND_KTV_CONTROL_VOLUME_PLUS:
            memcpy(CHAR_BUFFER, "+", sizeof("+"));
        break;

        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_CURRENTPAGEHINT:
        {
            U8 u8PageIndexTmp[12];
            U8 u8PageIndex[12];
            CHAR_BUFFER[0]=0;
            CHAR_BUFFER[1]=0;
            memcpy(u8PageIndexTmp, "第", sizeof("第"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(u8PageIndexTmp);
            u8PageIndex[0]= u8PageIndexTmp[0];
            u8PageIndex[1]= u8PageIndexTmp[1];
            MApp_ZUI_ACTKTV_NUMTOUNICODE((U16)u8KTVSearchSongFirstWordPageNum+1, u8PageIndexTmp);
            u8PageIndex[2]= u8PageIndexTmp[2];
            u8PageIndex[3]= u8PageIndexTmp[3];
            u8PageIndex[4]= u8PageIndexTmp[4];
            u8PageIndex[5]= u8PageIndexTmp[5];
            u8PageIndex[6]= u8PageIndexTmp[6];
            u8PageIndex[7]= u8PageIndexTmp[7];
            u8PageIndex[8]= u8PageIndexTmp[8];
            u8PageIndex[9]= u8PageIndexTmp[9];
            memcpy(u8PageIndexTmp, "页", sizeof("页"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(u8PageIndexTmp);
            u8PageIndex[10]= u8PageIndexTmp[0];
            u8PageIndex[11]= u8PageIndexTmp[1];
            memcpy(CHAR_BUFFER, u8PageIndex, sizeof(u8PageIndex));
        }
        break;
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_TOTALPAGEHINT:
        {

            U8 u8PageIndexTmp[12];
            U8 u8PageIndex[12];
            CHAR_BUFFER[0]=0;
            CHAR_BUFFER[1]=0;
            memcpy(u8PageIndexTmp, "共", sizeof("共"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(u8PageIndexTmp);
            u8PageIndex[0]= u8PageIndexTmp[0];
            u8PageIndex[1]= u8PageIndexTmp[1];
            MApp_ZUI_ACTKTV_NUMTOUNICODE((U16)(st_searchedsong_buf->u16total/NUM_OF_KTV_SONGS_FIRSTWORD_PER_PAGE)+1, u8PageIndexTmp);
            u8PageIndex[2]= u8PageIndexTmp[2];
            u8PageIndex[3]= u8PageIndexTmp[3];
            u8PageIndex[4]= u8PageIndexTmp[4];
            u8PageIndex[5]= u8PageIndexTmp[5];
            u8PageIndex[6]= u8PageIndexTmp[6];
            u8PageIndex[7]= u8PageIndexTmp[7];
            u8PageIndex[8]= u8PageIndexTmp[8];
            u8PageIndex[9]= u8PageIndexTmp[9];
            memcpy(u8PageIndexTmp, "页", sizeof("页"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(u8PageIndexTmp);
            u8PageIndex[10]= u8PageIndexTmp[0];
            u8PageIndex[11]= u8PageIndexTmp[1];
            memcpy(CHAR_BUFFER, u8PageIndex, sizeof(u8PageIndex));
        }
        break;
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_2:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_3:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_4:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_5:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_6:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_7:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_8:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_9:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_10:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_11:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_12:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_13:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_14:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_15:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_16:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_17:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_18:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_19:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_20:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_21:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_22:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_23:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_MAX:
    {

            U16 u16NameFirst[6];
            u8ItemIdx = hwnd-HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_2;
            u16ItemIndex = u8ItemIdx + u8KTVSearchSongFirstWordPageNum*NUM_OF_KTV_SONGS_FIRSTWORD_PER_PAGE;
            CHAR_BUFFER[0]=0;
            CHAR_BUFFER[1]=0;
            if(st_searchedsong_buf == NULL)
                break;

            if(u16ItemIndex >= st_searchedsong_buf->u16total)
                break;
            else
            {


                if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_2)
                {
                    u16NameFirst[0]='2';
                    u16NameFirst[1]='.';
                    u16NameFirst[2]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[3]=0;
                    u16KTVSearchSongFirstWord[2] = u16NameFirst[2];

                }

                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_3)
                {
                    u16NameFirst[0]='3';
                    u16NameFirst[1]='.';
                    u16NameFirst[2]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[3]=0;
                    u16KTVSearchSongFirstWord[3] = u16NameFirst[2];

                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_4)
                {
                    u16NameFirst[0]='4';
                    u16NameFirst[1]='.';
                    u16NameFirst[2]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[3]=0;
                    u16KTVSearchSongFirstWord[4] = u16NameFirst[2];
                }

                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_5)
                {
                    u16NameFirst[0]='5';
                    u16NameFirst[1]='.';
                    u16NameFirst[2]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[3]=0;
                    u16KTVSearchSongFirstWord[5] = u16NameFirst[2];
                }

                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_6)
                {
                    u16NameFirst[0]='6';
                    u16NameFirst[1]='.';
                    u16NameFirst[2]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[3]=0;
                    u16KTVSearchSongFirstWord[6] = u16NameFirst[2];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_7)
                {
                    u16NameFirst[0]='7';
                    u16NameFirst[1]='.';
                    u16NameFirst[2]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[3]=0;
                    u16KTVSearchSongFirstWord[7] = u16NameFirst[2];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_8)
                {
                    u16NameFirst[0]='8';
                    u16NameFirst[1]='.';
                    u16NameFirst[2]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[3]=0;
                    u16KTVSearchSongFirstWord[8] = u16NameFirst[2];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_9)
                {
                    u16NameFirst[0]='9';
                    u16NameFirst[1]='.';
                    u16NameFirst[2]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[3]=0;
                    u16KTVSearchSongFirstWord[9] = u16NameFirst[2];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_10)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='0';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[10] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_11)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='1';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[11] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_12)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='2';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[12] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_13)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='3';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[13] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_14)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='4';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[14] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_15)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='5';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[15] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_16)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='6';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[16] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_17)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='7';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[17] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_18)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='8';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[18] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_19)
                {
                    u16NameFirst[0]='1';
                    u16NameFirst[1]='9';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[19] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_20)
                {
                    u16NameFirst[0]='2';
                    u16NameFirst[1]='0';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[20] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_21)
                {
                    u16NameFirst[0]='2';
                    u16NameFirst[1]='1';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[21] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_22)
                {
                    u16NameFirst[0]='2';
                    u16NameFirst[1]='2';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[22] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_23)
                {
                    u16NameFirst[0]='2';
                    u16NameFirst[1]='3';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[23] = u16NameFirst[3];
                }
                else if(hwnd == HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_MAX)
                {
                    u16NameFirst[0]='2';
                    u16NameFirst[1]='4';
                    u16NameFirst[2]='.';
                    u16NameFirst[3]=st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[1];
                    u16NameFirst[4]=0;
                    u16KTVSearchSongFirstWord[24] = u16NameFirst[3];
                }
                memcpy(CHAR_BUFFER, u16NameFirst, sizeof(u16NameFirst));
            }
        }
        break;
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8_ID:
        {
            U8 u8IDString[12];
            if(st_searchedsinger_buf == NULL)
                break;

            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SINGERS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SingerListPageItemIDHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE;
            if((u8ItemIdx < NUM_OF_KTV_SINGERS_PER_PAGE) && (u16ItemIndex < st_searchedsinger_buf->u16total))
            {
                MApp_ZUI_ACTKTV_NUMTOUNICODE((U16)st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->ID, u8IDString);
                memcpy(CHAR_BUFFER, u8IDString, sizeof(u8IDString));
            }
        }
        break;

        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8_SINGER:
        {
            U16 u16Name[NUM_OF_SONG_STRING];
            if(st_searchedsinger_buf == NULL)
                break;

            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SINGERS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SingerListPageItemSingerHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE;
            if((u8ItemIdx < NUM_OF_KTV_SINGERS_PER_PAGE) && (u16ItemIndex < st_searchedsinger_buf->u16total))
            {
                for(i=0; i<st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Name[0]; i++)
                {
                    u16Name[i] = st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Name[i+1];
                    u16Name[i+1] = 0;
                }
                memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
            }
        }
        break;

        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1_PINYIN:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2_PINYIN:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3_PINYIN:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4_PINYIN:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5_PINYIN:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6_PINYIN:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7_PINYIN:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8_PINYIN:
        {
            U8 u8Spell[32];
            if(st_searchedsinger_buf == NULL)
                break;

            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SINGERS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SingerListPageItemPinyinHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE;
            if((u8ItemIdx < NUM_OF_KTV_SINGERS_PER_PAGE) && (u16ItemIndex < st_searchedsinger_buf->u16total))
            {
                for(i=0; i<st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Spell[0]; i++)
                {
                    u8Spell[i*2] = st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Spell[i+1];
                    u8Spell[i*2+1] = 0;
                    u8Spell[i*2+2] = 0;
                    u8Spell[i*2+3] = 0;
                }
                memcpy(CHAR_BUFFER, u8Spell, sizeof(u8Spell));
            }
            }
        break;

        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM2_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM3_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM4_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM5_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM6_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM7_ID:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM8_ID:
        {
            U8 u8IDString[12];
            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SONGS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SongListPageItemIDHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
            switch(hwnd_use_songlist_page )
            {
                case HWND_KTV_SEARCH_BY_NAME_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                case HWND_KTV_SEARCH_BY_LASTUPDATE:
                case HWND_KTV_SEARCH_BY_POPULAR:
                    if(st_searchedsong_buf == NULL)
                            break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_searchedsong_buf->u16total))
                    {
                        MApp_ZUI_ACTKTV_NUMTOUNICODE((U16)st_searchedsong_buf->st_songbuf[u16ItemIndex]->dwSongID, u8IDString);
                        memcpy(CHAR_BUFFER, u8IDString, sizeof(u8IDString));
                    }
                break;

                case HWND_KTV_MY_FAVOURITE:
                    if(st_ktv_list == NULL)
                            break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8favorsongcounter))
                    {
                        MApp_ZUI_ACTKTV_NUMTOUNICODE((U16)st_ktv_list->st_favor_song_list[u16ItemIndex].u32Song_ID, u8IDString);
                        memcpy(CHAR_BUFFER, u8IDString, sizeof(u8IDString));
                    }
                break;

                case HWND_KTV_SONGS_HAD_SING:
                    if(st_ktv_list == NULL)
                            break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8playedsongcounter))
                    {
                        MApp_ZUI_ACTKTV_NUMTOUNICODE((U16)st_ktv_list->st_played_song_list[u16ItemIndex].u32Song_ID, u8IDString);
                        memcpy(CHAR_BUFFER, u8IDString, sizeof(u8IDString));
                    }
                break;

                default:
                break;
            }
        }
        break;

        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1_SONGS:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM2_SONGS:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM3_SONGS:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM4_SONGS:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM5_SONGS:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM6_SONGS:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM7_SONGS:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM8_SONGS:
        {
            U16 u16Name[NUM_OF_SONG_STRING];
            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SONGS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SongListPageItemSongsHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
            switch(hwnd_use_songlist_page )
            {
                case HWND_KTV_SEARCH_BY_NAME_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                case HWND_KTV_SEARCH_BY_LASTUPDATE:
                case HWND_KTV_SEARCH_BY_POPULAR:
                    if(st_searchedsong_buf == NULL)
                        break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_searchedsong_buf->u16total))
                    {
                        for(i=0; i<st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[0]; i++)
                        {
                            u16Name[i] = st_searchedsong_buf->st_songbuf[u16ItemIndex]->wsSongName[i+1];
                            u16Name[i+1] = 0;
                        }
                        memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                    }
                break;

                case HWND_KTV_MY_FAVOURITE:
                    if(st_ktv_list == NULL)
                        break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8favorsongcounter))
                    {
                        for(i=0; i<st_ktv_list->st_favor_song_list[u16ItemIndex].u16SongSting[0]; i++)
                        {
                            u16Name[i] = st_ktv_list->st_favor_song_list[u16ItemIndex].u16SongSting[i+1];
                            u16Name[i+1] = 0;
                        }
                        memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                    }
                break;

                case HWND_KTV_SONGS_HAD_SING:
                    if(st_ktv_list == NULL)
                        break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8playedsongcounter))
                    {
                        for(i=0; i<st_ktv_list->st_played_song_list[u16ItemIndex].u16SongSting[0]; i++)
                        {
                            u16Name[i] = st_ktv_list->st_played_song_list[u16ItemIndex].u16SongSting[i+1];
                            u16Name[i+1] = 0;
                        }
                        memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                    }
                break;

                default:
                break;
            }
        }
        break;

        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM2_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM3_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM4_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM5_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM6_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM7_SINGER:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM8_SINGER:
        {
            U16 u16Name[NUM_OF_SONG_STRING];
            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SONGS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SongListPageItemSingerHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
            switch(hwnd_use_songlist_page )
            {
                case HWND_KTV_SEARCH_BY_NAME_PAGE:
                case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                    if(st_searchedsong_buf == NULL ||st_searchedsinger_buf == NULL)
                        break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_searchedsong_buf->u16total))
                    {
                        for(i=0; i<st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Name[0]; i++)
                        {
                            u16Name[i] = st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Name[i+1];
                            u16Name[i+1] = 0;
                        }
                        memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                    }
                break;
                case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                    if(st_searchedsong_buf == NULL ||st_searchedsinger_buf == NULL)
                        break;

                if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_searchedsong_buf->u16total))
                {
                    for(i=0; i<st_searchedsinger_buf->st_singerbuf[u16KTVWhichSingerSelected]->Name[0]; i++)
                    {
                        u16Name[i] = st_searchedsinger_buf->st_singerbuf[u16KTVWhichSingerSelected]->Name[i+1];
                        u16Name[i+1] = 0;
                    }
                    memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                }
                break;

                case HWND_KTV_MY_FAVOURITE:
                    if(st_ktv_list == NULL)
                        break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8favorsongcounter))
                    {
                        for(i=0; i<st_ktv_list->st_favor_song_list[u16ItemIndex].u16SingerSting[0]; i++)
                        {
                            u16Name[i] = st_ktv_list->st_favor_song_list[u16ItemIndex].u16SingerSting[i+1];
                            u16Name[i+1] = 0;
                        }
                        memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                    }
                break;

                case HWND_KTV_SONGS_HAD_SING:
                    if(st_ktv_list == NULL)
                        break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8playedsongcounter))
                    {
                        for(i=0; i<st_ktv_list->st_played_song_list[u16ItemIndex].u16SingerSting[0]; i++)
                        {
                            u16Name[i] = st_ktv_list->st_played_song_list[u16ItemIndex].u16SingerSting[i+1];
                            u16Name[i+1] = 0;
                        }
                        memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                    }
                break;

                case HWND_KTV_SEARCH_BY_LASTUPDATE:
                case HWND_KTV_SEARCH_BY_POPULAR:
                    if(st_searchedsong_buf == NULL || st_searchedsinger_buf == NULL)
                        break;

                    if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_searchedsong_buf->u16total))
                    {
                        for(i=0; i<st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Name[0]; i++)
                        {
                            u16Name[i] = st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Name[i+1];
                            u16Name[i+1] = 0;
                        }
                        memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
                    }
                break;

                default:
                break;
            }
        }
        break;

        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM1:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM2:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM3:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM4:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM5:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM6:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM7:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM8:
        {
            U16 u16Name[NUM_OF_SONG_STRING];
            if(st_searchedsinger_buf == NULL)
                break;

            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SINGERS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SingerNameListPageItemHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE;
            if((u8ItemIdx < NUM_OF_KTV_SINGERS_PER_PAGE) && (u16ItemIndex < st_searchedsinger_buf->u16total))
            {
                for(i=0; i<st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Name[0]; i++)
                {
                    u16Name[i] = st_searchedsinger_buf->st_singerbuf[u16ItemIndex]->Name[i+1];
                    u16Name[i+1] = 0;
                }
                memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
            }
        }
        break;

        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1_SONGID:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM2_SONGID:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM3_SONGID:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM4_SONGID:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM5_SONGID:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM6_SONGID:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM7_SONGID:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8_SONGID:
        {
            U8 u8IDString[12];
            if(st_ktv_list == NULL)
                break;

            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SONGS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SongToPlayItemIDHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
            if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8playsongcounter))
            {
                MApp_ZUI_ACTKTV_NUMTOUNICODE((U16)st_ktv_list->st_play_song_list[u16ItemIndex].u32Song_ID, u8IDString);
                memcpy(CHAR_BUFFER, u8IDString, sizeof(u8IDString));
            }
        }
        break;

        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1_SONGS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM2_SONGS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM3_SONGS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM4_SONGS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM5_SONGS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM6_SONGS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM7_SONGS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8_SONGS:
        {
            U16 u16Name[NUM_OF_SONG_STRING];
            if(st_ktv_list == NULL)
                break;

            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SONGS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SongToPlayItemSongHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
            if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8playsongcounter))
            {
                for(i=0; i<st_ktv_list->st_play_song_list[u16ItemIndex].u16SongSting[0]; i++)
                {
                    u16Name[i] = st_ktv_list->st_play_song_list[u16ItemIndex].u16SongSting[i+1];
                    u16Name[i+1] = 0;
                }
                memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
            }
        }
        break;

        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1_SINGERS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM2_SINGERS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM3_SINGERS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM4_SINGERS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM5_SINGERS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM6_SINGERS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM7_SINGERS:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8_SINGERS:
        {
            U16 u16Name[NUM_OF_SONG_STRING];
            if(st_ktv_list == NULL)
                break;

            for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SONGS_PER_PAGE; u8ItemIdx++)
            {
                if(hwnd == _SongToPlayItemSingerHwndList[u8ItemIdx])
                {
                    break;
                }
            }
            u16ItemIndex = u8ItemIdx + u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
            if((u8ItemIdx < NUM_OF_KTV_SONGS_PER_PAGE) && (u16ItemIndex < st_ktv_list->u8playsongcounter))
            {
                for(i=0; i<st_ktv_list->st_play_song_list[u16ItemIndex].u16SingerSting[0]; i++)
                {
                    u16Name[i] = st_ktv_list->st_play_song_list[u16ItemIndex].u16SingerSting[i+1];
                    u16Name[i+1] = 0;
                }
                memcpy(CHAR_BUFFER, u16Name, sizeof(u16Name));
            }
        }
        break;

    default:
        break;
    }
    return CHAR_BUFFER;
}

U16 MApp_ZUI_ACT_GetKTVDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    hwnd = hwnd;
    ds_type = ds_type;
    return 0xFFFF; //for empty bitmap....
}

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
void MApp_ZUI_ACT_AppShowKTV(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_KTV_MAIN;

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
        ZUI_KTV_MAIN_XSTART, ZUI_KTV_MAIN_YSTART,
        ZUI_KTV_MAIN_WIDTH, ZUI_KTV_MAIN_HEIGHT);
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
    MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_BG, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
    MApp_ZUI_API_EnableWindow(HWND_KTV_SEARCH_BY_SINGER_DELETE, DISABLE);
    MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER);
    if(bIsthefirsttime )
    {
        MApp_ZUI_API_StoreFocusCheckpoint();
        MApp_ZUI_API_ShowWindow(HWND_KTV_WAITING_INFO, SW_SHOW);
        MApp_ZUI_API_SetFocus(HWND_KTV_WAITING_TEXT);
        MApp_ZUI_API_SetTimer(HWND_KTV_WAITING_INFO, 0, 500);
        memcpy(KTVWaitingStringbuf, _WaitingType[0], sizeof(_WaitingType[0]));
        MApp_ZUI_ACTKTV_GBTOUNICODE(KTVWaitingStringbuf);
        u8CountNum = 6;
    }
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
}


static BOOLEAN _MApp_KTV_GotoInputSourceState(void)
{
    if(enKTVState == STATE_KTV_WAIT ||
        enKTVState == STATE_KTV_INIT )
    {
        enKTVState = STATE_KTV_GOTO_INPUTSOURCE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
static void _MApp_KTV_InitDigitInfo(void)
{
    U8 i;
    for(i=0;i<NUM_OF_SOFTWARE_KEYBOARD_DIGIT_STRING;i++)
    {
        _mKTVDigitInfo.u8Sting[i]=0;
    }
    _mKTVDigitInfo.u8Input_Offset= 0;
}

/******************************************************************************/
/// handler MENU key input
/// @param  N/A
/// @return  true if hwnd is not invalid
/******************************************************************************/
static BOOLEAN _MApp_KTV_menukey_Handle(void)
{
    HWND hwnd;
    hwnd = MApp_ZUI_API_GetFocus();
    if(hwnd == HWND_INVALID)
    {
        MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
        MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER);
        return FALSE;
    }
     switch( MApp_ZUI_API_GetParent(hwnd))
    {
        case HWND_KTV_MAIN_ITEMS:
            {
                MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            }
        break;
        case HWND_KTV_SEARCH_BY_SINGER_TYPE:
            {
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER);
            }
        break;
        case HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE:
            {
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_SONGSTER);
            }
        break;
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
            {
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_NAMELIST, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_ALL);
            }
        break;
        case HWND_KTV_SOFTWARE_KEYBOARD_LETTER:
            {
                if(hwnd_use_letter_board == HWND_KTV_SEARCH_BY_SINGER_PAGE)
                {
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_PAGE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SOFTWARE_KEYBOARD_LETTER, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_FIRST_LETTER);
                }
            }
        break;
        case HWND_KTV_SEARCH_BY_SINGER_PAGE:
            {
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_KTV_SOFTWARE_KEYBOARD_LETTER, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_FIRST_LETTER);
            }
        break;
        case HWND_KTV_SEARCH_BY_NAME_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME);
        break;
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_PAGE, SW_SHOW);
            if(u8KTVSearchSongLanguage==SONG_LANGUAGE_CHINESE)
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_CHINESE);
            else if(u8KTVSearchSongLanguage==SONG_LANGUAGE_TAIWAN)
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_TAIYU);
            else if(u8KTVSearchSongLanguage==SONG_LANGUAGE_CANTONESS)
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_YUEYU);
        break;
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_1+u8KTVSearchSongWordNubmer-1);
        break;
        case HWND_KTV_SEARCH_FOUND_SONGS:
            {
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_HIDE);
                u8KTVSearchSongListPage = 0;
                switch(hwnd_use_songlist_page)
                {
                    case HWND_KTV_SEARCH_BY_NAME_PAGE:
                    {
                        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_PAGE, SW_SHOW);
                        if(u8KTVSearchSongLanguage==SONG_LANGUAGE_ENGLISH)
                            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_ENGLISH);
                        else if(u8KTVSearchSongLanguage==SONG_LANGUAGE_JANPANESE)
                            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_JAPANESE);
                        else if(u8KTVSearchSongLanguage==SONG_LANGUAGE_KOREAN)
                            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_KOREA);
                        else if(u8KTVSearchSongLanguage==SONG_LANGUAGE_OTHER)
                            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_OTHERS);
                    }
                    break;
                    case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                    {
                        MApp_SearchSongByLanguageAndNameCountDifferentFirstWord(stp_ktv_songbuf, 2000,stp_ktv_singerbuf,u8KTVSearchSongLanguage,u8KTVSearchSongWordNubmer, st_searchedsong_buf,st_searchedsinger_buf);
                        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE, SW_SHOW);
                        MApp_ZUI_API_SetFocus(u16KTVSearchSongFirstWord[1]);
                    }
                    break;
                    case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_PAGE, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_KTV_SOFTWARE_KEYBOARD_LETTER, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_KTV_SOFTWARE_KEY_M);
                        hwnd_use_letter_board = HWND_KTV_SEARCH_BY_SINGER_PAGE;
                    break;

                    case HWND_KTV_MY_FAVOURITE:
                        MApp_ZUI_API_EnableWindow(HWND_KTV_SEARCH_BY_SINGER_AS_FAVOURITE, ENABLE);
                        MApp_ZUI_API_EnableWindow(HWND_KTV_SEARCH_BY_SINGER_DELETE, DISABLE);
                        MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_KTV_MY_FAVOURITE);
                    break;
                    case HWND_KTV_SONGS_HAD_SING:
                        MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_HAD_SING);
                    break;
                    case HWND_KTV_SEARCH_BY_LASTUPDATE:
                        MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_LASTUPDATE);
                    break;
                    case HWND_KTV_SEARCH_BY_POPULAR:
                        MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_POPULAR);
                    break;

                    case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_NAMELIST, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM1);
                    break;
                    default:
                    break;
                }
            }
        break;
        case HWND_KTV_SONGS_LIST_TO_PLAY:
            u8KTVSearchSongListPage = 0;
            MApp_ZUI_API_ShowWindow(HWND_KTV_SONGS_LIST_TO_PLAY, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_TO_SING);
        break;
        case HWND_KTV_SOFTWARE_KEYBOARD_DIGIT:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SOFTWARE_KEYBOARD_DIGIT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_ID_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_LIST_NUM);
        break;
        case HWND_KTV_SETUP_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SETUP_TIEM);
        break;
        case HWND_KTV_SETUP_SOUND_SETTING_PAGE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_SOUND_SETTING_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SETUP_SOUND_SETTING);
        break;

        default:
        break;
    }
    return TRUE;
}

/******************************************************************************/
/// handler select key input
/// @param  N/A
/// @return  true if hwnd is not invalid
/******************************************************************************/
static BOOLEAN _MApp_KTV_Item_Select_Handle(void)
{
    HWND hwnd;

    hwnd = MApp_ZUI_API_GetFocus();
    if(hwnd == HWND_INVALID)
    {
        return FALSE;
    }
    switch(hwnd)
    {
        case HWND_KTV_EXIT_BUTTON:
            MApp_KTV_ExitKTV();
            MApp_ZUI_ACT_ShutdownOSD();
            MApp_KTV_Main_Exit();
            MApp_TopStateMachine_SetTopState( STATE_TOP_DIGITALINPUTS);
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
            MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
        break;
        case HWND_KTV_SEARCH_BY_SINGER:
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_SONGSTER);
        break;
        case HWND_KTV_SEARCH_BY_SINGER_SONGSTER:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_ALL);
            en_song_class = SONG_CLASS_MALE;
        break;
        case HWND_KTV_SEARCH_BY_SINGER_SONGSTRESS:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_ALL);
            en_song_class = SONG_CLASS_FEMALE;
        break;
        case HWND_KTV_SEARCH_BY_SINGER_BAND:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_ALL);
            en_song_class = SONG_CLASS_GROUP;
        break;
        case HWND_KTV_SEARCH_BY_SINGER_ANTISTROPHIC:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_ALL);
            en_song_class = SONG_CLASS_MALE_FEMALE;
        break;
        case HWND_KTV_SEARCH_BY_SINGER_FEMALE_CHORUS:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_ALL);
            en_song_class = SONG_CLASS_FEMALE_FEMALE;
        break;
        case HWND_KTV_SEARCH_BY_SINGER_MALE_CHORUS:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_TYPE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_ALL);
            en_song_class = SONG_CLASS_MALE_MALE;
        break;
        case HWND_KTV_SEARCH_BY_SINGER_ALL:
        {
            U8 u8StingASCII[2] = {0, 0};

            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_NAMELIST, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM1);
            MApp_SearchSingerBySongClassAndSpell(stp_ktv_singerbuf, stp_ktv_songbuf, g_total_song,  (U8)en_song_class, u8StingASCII, st_searchedsinger_buf);
            u8KTVSearchSingerListPage = 0;
        }
        break;

        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM1:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM2:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM3:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM4:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM5:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM6:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM7:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM8:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_NAMELIST, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            hwnd_use_songlist_page = HWND_KTV_SEARCH_BY_SINGER_NAMELIST;
            u16KTVWhichSingerSelected = u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE + (hwnd -HWND_KTV_SEARCH_BY_SINGER_NAMELIST_ITEM1);
            MApp_SearchSongBySinger(stp_ktv_songbuf, g_total_song, st_searchedsinger_buf->st_singerbuf[u16KTVWhichSingerSelected], st_searchedsong_buf);
            u8KTVSearchSongListPage = 0;
        break;
        case HWND_KTV_SEARCH_BY_SINGER_FIRST_LETTER:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_SEARCH_TYPE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_PAGE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SOFTWARE_KEYBOARD_LETTER, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SOFTWARE_KEY_M);
            hwnd_use_letter_board = HWND_KTV_SEARCH_BY_SINGER_PAGE;
            memset(_mKTVLetterInfo.u8Sting, 0, NUM_OF_SOFTWARE_KEYBOARD_LETTER_STRING);
            _mKTVLetterInfo.u8Input_Offset= 0;
            if(st_searchedsinger_buf != NULL)
                    st_searchedsinger_buf->u16total = 0;
        break;
        case HWND_KTV_SEARCH_BY_NAME:
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_CHINESE);
        break;
        case HWND_KTV_SEARCH_BY_NAME_CHINESE:
        case HWND_KTV_SEARCH_BY_NAME_TAIYU:
        case HWND_KTV_SEARCH_BY_NAME_YUEYU:
            if(hwnd ==HWND_KTV_SEARCH_BY_NAME_CHINESE)
                u8KTVSearchSongLanguage = SONG_LANGUAGE_CHINESE;
            else if(hwnd ==HWND_KTV_SEARCH_BY_NAME_TAIYU)
                u8KTVSearchSongLanguage = SONG_LANGUAGE_TAIWAN;
            else if(hwnd ==HWND_KTV_SEARCH_BY_NAME_YUEYU)
                u8KTVSearchSongLanguage = SONG_LANGUAGE_CANTONESS;
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_1);
        break;
        case HWND_KTV_SEARCH_BY_NAME_ENGLISH:
        case HWND_KTV_SEARCH_BY_NAME_JAPANESE:
        case HWND_KTV_SEARCH_BY_NAME_KOREA:
        case HWND_KTV_SEARCH_BY_NAME_OTHERS:
            hwnd_use_songlist_page = HWND_KTV_SEARCH_BY_NAME_PAGE;
            if(hwnd ==HWND_KTV_SEARCH_BY_NAME_ENGLISH)
                u8KTVSearchSongLanguage = SONG_LANGUAGE_ENGLISH;
            else if(hwnd ==HWND_KTV_SEARCH_BY_NAME_JAPANESE)
                u8KTVSearchSongLanguage = SONG_LANGUAGE_JANPANESE;
            else if(hwnd ==HWND_KTV_SEARCH_BY_NAME_KOREA)
                u8KTVSearchSongLanguage = SONG_LANGUAGE_KOREAN;
            else if(hwnd ==HWND_KTV_SEARCH_BY_NAME_OTHERS)
                u8KTVSearchSongLanguage = SONG_LANGUAGE_OTHER;
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            MApp_SearchSongByLanguage(stp_ktv_songbuf, 2000,stp_ktv_singerbuf,u8KTVSearchSongLanguage, st_searchedsong_buf,st_searchedsinger_buf);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
        break;
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_1:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_2:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_3:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_4:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_5:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_6:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_7:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_8:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_9:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_10:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_11:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_OTHERS:
            u8KTVSearchSongWordNubmer = hwnd-HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_1+1;
            u8KTVSearchSongFirstWordPageNum = 0;
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE, SW_SHOW);
            MApp_SearchSongByLanguageAndNameCountDifferentFirstWord(stp_ktv_songbuf, 2000,stp_ktv_singerbuf,u8KTVSearchSongLanguage,u8KTVSearchSongWordNubmer, st_searchedsong_buf,st_searchedsinger_buf);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_1);
        break;
    case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_1:
            u16KTVSearchSongFirstWord[1]=hwnd;
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            hwnd_use_songlist_page = HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE;
            MApp_SearchSongByLanguageAndNameCount(stp_ktv_songbuf, 2000,stp_ktv_singerbuf,u8KTVSearchSongLanguage,u8KTVSearchSongWordNubmer, st_searchedsong_buf,st_searchedsinger_buf);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
    break;
    case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_2:
    case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_3:
    case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_4:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_5:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_6:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_7:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_8:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_9:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_10:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_11:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_12:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_13:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_14:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_15:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_16:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_17:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_18:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_19:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_20:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_21:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_22:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_23:
        case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_MAX:
        {
            U16 wFirstWord;
            u16KTVSearchSongFirstWord[1]=hwnd;
            wFirstWord = u16KTVSearchSongFirstWord[hwnd-HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_1+1];
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            hwnd_use_songlist_page = HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE;
            MApp_SearchSongByLanguageAndNameCountSameFirstWord(stp_ktv_songbuf, 2000,stp_ktv_singerbuf,u8KTVSearchSongLanguage,u8KTVSearchSongWordNubmer,wFirstWord, st_searchedsong_buf,st_searchedsinger_buf);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
        }
        break;
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7:
        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SOFTWARE_KEYBOARD_LETTER, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            hwnd_use_songlist_page = HWND_KTV_SEARCH_BY_SINGER_PAGE;
            memset(_mKTVLetterInfo.u8Sting, 0, NUM_OF_SOFTWARE_KEYBOARD_LETTER_STRING);
            _mKTVLetterInfo.u8Input_Offset= 0;
            u16KTVWhichSingerSelected = u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE + (hwnd -HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1)/4;
            MApp_SearchSongBySinger(stp_ktv_songbuf, g_total_song, st_searchedsinger_buf->st_singerbuf[u16KTVWhichSingerSelected], st_searchedsong_buf);
            u8KTVSearchSongListPage = 0;
        break;
        case HWND_KTV_SEARCH_BY_LIST_NUM:
            _MApp_KTV_InitDigitInfo();
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_ID_PAGE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SOFTWARE_KEYBOARD_DIGIT, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SOFTWARE_KEY_1);
        break;
        case HWND_KTV_SEARCH_BY_LASTUPDATE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            hwnd_use_songlist_page = HWND_KTV_SEARCH_BY_LASTUPDATE;
            MApp_SearchSongByAttribute( stp_ktv_songbuf, g_total_song,  stp_ktv_singerbuf, 0x0000|BIT8, st_searchedsong_buf, st_searchedsinger_buf);
        break;
        case HWND_KTV_SEARCH_BY_POPULAR:
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            hwnd_use_songlist_page = HWND_KTV_SEARCH_BY_POPULAR;
            MApp_SearchSongByAttribute( stp_ktv_songbuf, g_total_song,  stp_ktv_singerbuf, 0x0000|BIT0, st_searchedsong_buf, st_searchedsinger_buf);
        break;
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM2:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM3:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM4:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM5:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM6:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM7:
        case HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM8:
            u16KTVWhichSongSelected = u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE + (hwnd -HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1)/4;;
            MApp_ZUI_API_EnableWindow(hwnd, DISABLE);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
        break;
        case HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST:
        {
            MApp_ZUI_API_ShowWindow(HWND_KTV_TONE_OF_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_TONE_OF_SONGS_ORIGINAL);
            memcpy(_mKTVToneInfo.u8Line1Sting, "已将", sizeof("已将"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line1Sting);
            memcpy(_mKTVToneInfo.u8Line2Sting, "加入至待唱歌曲", sizeof("加入至待唱歌曲"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line2Sting);
            hwnd_use_tone_page = HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST;
            switch(hwnd_use_songlist_page)
            {
                case HWND_KTV_SEARCH_BY_NAME_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                case HWND_KTV_SEARCH_BY_LASTUPDATE:
                case HWND_KTV_SEARCH_BY_POPULAR:
            MApp_AddSongToList(st_searchedsong_buf->st_songbuf[u16KTVWhichSongSelected],  stp_ktv_singerbuf, SONG_PLAYLIST, st_ktv_list);
                    break;

                case HWND_KTV_MY_FAVOURITE:
                    MApp_MoveSongBetweenlist(st_ktv_list,  u16KTVWhichSongSelected, SONG_FAVORLIST_TO_PLAYLIST);
                break;

                case HWND_KTV_SONGS_HAD_SING:
                    MApp_MoveSongBetweenlist(st_ktv_list,  u16KTVWhichSongSelected, SONG_PLAYEDLIST_TO_PLAYLIST);
                    break;

                default:
                    break;
            }
        }
        break;
        case HWND_KTV_SEARCH_BY_SINGER_INSERT_AHEAD:
            MApp_ZUI_API_ShowWindow(HWND_KTV_TONE_OF_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_TONE_OF_SONGS_ORIGINAL);
            memcpy(_mKTVToneInfo.u8Line1Sting, "已将", sizeof("已将"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line1Sting);
            memcpy(_mKTVToneInfo.u8Line2Sting, "插播至待唱歌曲", sizeof("插播至待唱歌曲"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line2Sting);
            hwnd_use_tone_page = HWND_KTV_SEARCH_BY_SINGER_INSERT_AHEAD;
            switch(hwnd_use_songlist_page)
            {
                case HWND_KTV_SEARCH_BY_NAME_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                case HWND_KTV_SEARCH_BY_LASTUPDATE:
                case HWND_KTV_SEARCH_BY_POPULAR:
            MApp_AddSongToList(st_searchedsong_buf->st_songbuf[u16KTVWhichSongSelected],  stp_ktv_singerbuf, SONG_INSERT_PLAYLIST, st_ktv_list);
        break;

                case HWND_KTV_MY_FAVOURITE:
                    MApp_MoveSongBetweenlist(st_ktv_list,  u16KTVWhichSongSelected, SONG_FAVORLIST_INSERT_PLAYLIST);
                break;

                case HWND_KTV_SONGS_HAD_SING:
                    MApp_MoveSongBetweenlist(st_ktv_list,  u16KTVWhichSongSelected, SONG_PLAYEDLIST_INSERT_PLAYLIST);
                    break;

                default:
                    break;
            }
        break;
        case HWND_KTV_TONE_OF_SONGS_ORIGINAL:
        case HWND_KTV_TONE_OF_SONGS_SINGER1:
        case HWND_KTV_TONE_OF_SONGS_SINGER2:
        case HWND_KTV_TONE_OF_SONGS_SINGER3:
        case HWND_KTV_TONE_OF_SONGS_SINGER4:
        case HWND_KTV_TONE_OF_SONGS_SINGER5:
            MApp_ZUI_API_ShowWindow(HWND_KTV_TONE_OF_SONGS, SW_HIDE);
            switch(hwnd_use_tone_page)
            {
                case HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST:
                    MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
                    break;
                case HWND_KTV_SEARCH_BY_SINGER_INSERT_AHEAD:
                    MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_INSERT_AHEAD);
                    break;
                case HWND_KTV_SOFTWARE_KEY_ENTER:
                    {
                        U8 u8Len;
                        MApp_ZUI_API_SetFocus(HWND_KTV_SOFTWARE_KEY_ENTER);
                        for (u8Len = 0; u8Len < NUM_OF_SOFTWARE_KEYBOARD_DIGIT_STRING; u8Len++)
                        {
                            _mKTVDigitInfo.u8Sting[u8Len]=0;
                        }
                        _mKTVDigitInfo.u8Input_Offset= 0;
                        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_ID_IDVALUE, SW_SHOW);
                    }
                    break;
                case HWND_KTV_SOFTWARE_KEY_INSERT:
                    {
                        U8 u8Len;
                        MApp_ZUI_API_SetFocus(HWND_KTV_SOFTWARE_KEY_INSERT);
                        for (u8Len = 0; u8Len < NUM_OF_SOFTWARE_KEYBOARD_DIGIT_STRING; u8Len++)
                        {
                            _mKTVDigitInfo.u8Sting[u8Len]=0;
                        }
                        _mKTVDigitInfo.u8Input_Offset= 0;
                        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_ID_IDVALUE, SW_SHOW);
                    }
                    break;
                default:
                    break;
            }
        break;
        case HWND_KTV_SEARCH_BY_SINGER_AS_FAVOURITE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_SHOW);
            MApp_ZUI_API_EnableWindow(HWND_KTV_DIALOG_CANCEL, DISABLE);
            MApp_ZUI_API_SetFocus(HWND_KTV_DIALOG_OK);
            hwnd_use_confirm_dialog = HWND_KTV_SEARCH_FOUND_SONGS;
            memcpy(_mKTVDialogInfo.u8Line1Sting, "已将", sizeof("已将"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVDialogInfo.u8Line1Sting);
            memcpy(_mKTVDialogInfo.u8Line2Sting, "加入至我的最爱清单", sizeof("加入至我的最爱清单"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVDialogInfo.u8Line2Sting);
            switch(hwnd_use_songlist_page)
            {
                case HWND_KTV_SEARCH_BY_NAME_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_PAGE:
                case HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE:
                case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
                case HWND_KTV_SEARCH_BY_LASTUPDATE:
                case HWND_KTV_SEARCH_BY_POPULAR:
                    MApp_AddSongToList(st_searchedsong_buf->st_songbuf[u16KTVWhichSongSelected],  stp_ktv_singerbuf, SONG_FAVORLIST, st_ktv_list);
                break;

                case HWND_KTV_SONGS_HAD_SING:
                    MApp_MoveSongBetweenlist(st_ktv_list,  u16KTVWhichSongSelected, SONG_PLAYEDLIST_TO_FAVORLIST);
                    break;

                default:
                    break;
            }
        break;

        case HWND_KTV_SEARCH_BY_SINGER_DELETE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_SHOW);
            MApp_ZUI_API_EnableWindow(HWND_KTV_DIALOG_CANCEL, ENABLE);
            MApp_ZUI_API_SetFocus(HWND_KTV_DIALOG_OK);
            hwnd_use_confirm_dialog = HWND_KTV_SEARCH_BY_SINGER_DELETE;
            memcpy(_mKTVDialogInfo.u8Line1Sting, "　", sizeof("　"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVDialogInfo.u8Line1Sting);
            memcpy(_mKTVDialogInfo.u8Line2Sting, "是否将选中歌曲从清单中移除？", sizeof("是否将选中歌曲从清单中移除？"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVDialogInfo.u8Line2Sting);
        break;

        case HWND_KTV_DIALOG_OK:
            switch(hwnd_use_confirm_dialog )
            {
                case HWND_KTV_SEARCH_FOUND_SONGS:
                {
                    MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_HIDE);
                    MApp_ZUI_API_EnableWindow(HWND_KTV_DIALOG_CANCEL, ENABLE);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_AS_FAVOURITE);
                }
                break;
                case HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ONE:
                {
                    U8 i;
                    for(i=0; i<NUM_OF_KTV_SONGS_PER_PAGE; i++)
                    {
                        MApp_ZUI_API_EnableWindow(_SongToPlayItemHwndList[i], ENABLE);
                    }
                    MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SONGS_LIST_TO_PLAY, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ONE);
                    MApp_RemoveSongFromList(st_ktv_list->st_play_song_list[u16KTVWhichSongSelected].u32Song_ID, SONG_PLAYLIST, st_ktv_list);
                }
                break;
                case HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ALL:
                {
                    U8 i;

                    for(i=0; i<NUM_OF_KTV_SONGS_PER_PAGE; i++)
                    {
                        MApp_ZUI_API_EnableWindow(_SongToPlayItemHwndList[i], ENABLE);
                    }
                    MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SONGS_LIST_TO_PLAY, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ALL);
                    for(i=st_ktv_list->u8playsongcounter; i>0; i--)
                    {
                        MApp_RemoveSongFromList(st_ktv_list->st_play_song_list[i-1].u32Song_ID, SONG_PLAYLIST, st_ktv_list);
                    }
                }
                break;
                case HWND_KTV_SEARCH_BY_SINGER_DELETE:
                {
                    U8 i;
                    for(i=0; i<NUM_OF_KTV_SONGS_PER_PAGE; i++)
                    {
                        MApp_ZUI_API_EnableWindow(_SongListPageItemHwndList[i], ENABLE);
                    }
                    MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_DELETE);
                    MApp_RemoveSongFromList(st_ktv_list->st_favor_song_list[u16KTVWhichSongSelected].u32Song_ID, SONG_FAVORLIST, st_ktv_list);
                }
                break;

                default:
                break;
            }
        break;
        case HWND_KTV_DIALOG_CANCEL:
            switch(hwnd_use_confirm_dialog)
            {
                case HWND_KTV_SEARCH_FOUND_SONGS:
                {
                    MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_AS_FAVOURITE);
                }
                break;
                case HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ONE:
                {
                    MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ONE);
                }
                break;
                case HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ALL:
                {
                    MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ALL);
                }
                break;
                case HWND_KTV_SEARCH_BY_SINGER_DELETE:
                {
                    MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_DELETE);
                }
                break;
                default:
                break;
            }
        break;
        case HWND_KTV_MY_FAVOURITE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_EnableWindow(HWND_KTV_SEARCH_BY_SINGER_AS_FAVOURITE, DISABLE);
            MApp_ZUI_API_EnableWindow(HWND_KTV_SEARCH_BY_SINGER_DELETE, ENABLE);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            hwnd_use_songlist_page = HWND_KTV_MY_FAVOURITE;
        break;
        case HWND_KTV_SONGS_TO_SING:
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SONGS_LIST_TO_PLAY, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_PLAY_NOW);
        break;
        case HWND_KTV_SONGS_HAD_SING:
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_APPENDTOPLAYLIST);
            hwnd_use_songlist_page = HWND_KTV_SONGS_HAD_SING;
        break;
        case HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ONE:
            MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_DIALOG_OK);
            hwnd_use_confirm_dialog = HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ONE;
            memcpy(_mKTVDialogInfo.u8Line1Sting, "　", sizeof("　"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVDialogInfo.u8Line1Sting);
            memcpy(_mKTVDialogInfo.u8Line2Sting, "是否将选中歌曲从清单中移除？", sizeof("是否将选中歌曲从清单中移除？"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVDialogInfo.u8Line2Sting);
        break;
        case HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ALL:
            MApp_ZUI_API_ShowWindow(HWND_KTV_DIALOG, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_DIALOG_OK);
            hwnd_use_confirm_dialog = HWND_KTV_SONGS_LIST_TO_PLAY_DELETE_ALL;
            memcpy(_mKTVDialogInfo.u8Line1Sting, "　", sizeof("　"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVDialogInfo.u8Line1Sting);
            memcpy(_mKTVDialogInfo.u8Line2Sting, "是否清空清单中所有歌曲？", sizeof("是否清空清单中所有歌曲？"));
            MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVDialogInfo.u8Line2Sting);
        break;
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM2:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM3:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM4:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM5:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM6:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM7:
        case HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8:
            u16KTVWhichSongSelected = u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE + (hwnd -HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1)/4;;
            MApp_ZUI_API_EnableWindow(hwnd, DISABLE);
            MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_MOVEUP);
        break;
        case HWND_KTV_SETUP_TIEM:
            MApp_ZUI_API_ShowWindow(HWND_KTV_MAIN_ITEMS, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SETUP_SOUND_SETTING);
        break;
        case HWND_KTV_SETUP_SOUND_SETTING:
            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_SOUND_SETTING_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SETUP_MUSIC_VOLUME_BAR);
        break;

        case HWND_KTV_SONGS_LIST_TO_PLAY_MOVEUP:
        {
            HWND hwnd_move;
            MApp_MoveSong(u16KTVWhichSongSelected, SONG_MOVEUP, st_ktv_list);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SONGS_LIST_TO_PLAY, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_MOVEUP);
            hwnd_move = (u16KTVWhichSongSelected - u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE) * 4 + HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1;
            MApp_ZUI_API_EnableWindow(hwnd_move, ENABLE);
            if(u16KTVWhichSongSelected)
            {
                if(hwnd_move == HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1)
                {
                    hwnd_move = HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8;
                    u8KTVSearchSongListPage--;
                }
                else
                {
                    hwnd_move--;
                }
                MApp_ZUI_API_EnableWindow(hwnd_move, DISABLE);
                u16KTVWhichSongSelected--;
            }
        }
        break;
        case HWND_KTV_SONGS_LIST_TO_PLAY_MOVEDOWN:
        {
            HWND hwnd_move;
            MApp_MoveSong(u16KTVWhichSongSelected, SONG_MOVEDOWN, st_ktv_list);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SONGS_LIST_TO_PLAY, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_MOVEDOWN);
            hwnd_move = (u16KTVWhichSongSelected - u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE) * 4 + HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1;
            MApp_ZUI_API_EnableWindow(hwnd_move, ENABLE);
            if(u16KTVWhichSongSelected < st_ktv_list->u8playsongcounter-1)
            {
                if(hwnd_move == HWND_KTV_SONGS_LIST_TO_PLAY_ITEM8)
                {
                    hwnd_move = HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1;
                    u8KTVSearchSongListPage++;
                }
                else
                {
                    hwnd_move++;
                }
                MApp_ZUI_API_EnableWindow(hwnd_move, DISABLE);
                u16KTVWhichSongSelected++;
            }
        }
        break;

        case HWND_KTV_SONGS_LIST_TO_PLAY_PLAY_NOW:
        case HWND_KTV_CONTROL_PLAY:
        {
            if( enKTVLyricState == STATE_KTV_LYRIC_PAUSE)
            {
                enKTVLyricState = STATE_KTV_LYRIC_PLAY;
                MApp_KTV_Play();
                _eKTVMovieActionMode =E_KTV_MOVIE_ACTION_PLAY;
            }
            else if( (enKTVLyricState != STATE_KTV_LYRIC_PLAY) && (st_ktv_list->u8playsongcounter > 0) )
            {
                MApp_KTV_OpenMicFileToBuffer();
                enKTVLyricState = STATE_KTV_LYRIC_GET_LRC_SIZE;
                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_ShowWindow(HWND_KTV_WAITING_INFO, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_KTV_WAITING_TEXT);
                MApp_ZUI_API_SetTimer(HWND_KTV_WAITING_INFO, 0, 500);
                memcpy(KTVWaitingStringbuf, _WaitingType[1], sizeof(_WaitingType[1]));
                MApp_ZUI_ACTKTV_GBTOUNICODE(KTVWaitingStringbuf);
                eKTVLoadFileAttribute = (enumKTVLoadFileAttribute)0;
                eKTVLoadFileAttribute |= E_KTV_BEGIAN_LOAD;
                if(bIsthefirsttime)
                {
                    bIsthefirsttime = FALSE;
                    u8CountNum = 60;
                }
                else
                {
                    u8CountNum = 20;
                }
            }
            bContinuePlay = TRUE;
        }
        break;

        case HWND_KTV_CONTROL_PAUSE:
        {
            MApp_KTV_Pause();
            _eKTVMovieActionMode =E_KTV_MOVIE_ACTION_PAUSE;
            enKTVLyricState = STATE_KTV_LYRIC_PAUSE;
        }
        break;
        case HWND_KTV_CONTROL_STOP:
        {
            if( enKTVLyricState == STATE_KTV_LYRIC_PLAY )
                            MApp_KTV_Stop();

            _eKTVMovieActionMode =E_KTV_MOVIE_ACTION_STOP;
            enKTVLyricState = STATE_KTV_LYRIC_STOP;
            bContinuePlay = FALSE;
        }
        break;

        #if 0
        case HWND_KTV_CONTROL_REW:
        {
            _eKTVMovieActionMode =E_KTV_MOVIE_ACTION_FB;
        }
        break;
        case HWND_KTV_CONTROL_FF:
        {
            _eKTVMovieActionMode =E_KTV_MOVIE_ACTION_FF;
        }
        break;
        #endif
        case HWND_KTV_CONTROL_FORWARD:
        {
            if( enKTVLyricState == STATE_KTV_LYRIC_PLAY )
            {
                MApp_PlayedSong(0,  st_ktv_list);
                if(st_ktv_list->u8playsongcounter > 0)
                {
                    MApp_UiMenu_iSingCloseSubtitle();
                    enKTVLyricState = STATE_KTV_LYRIC_INIT;
                    _eKTVMovieActionMode =E_KTV_MOVIE_ACTION_STOP;
                    MApp_KTV_Stop();
                }
            }
        }
        break;

        case HWND_KTV_MSGBOX_BTN_YES:
        {
            extern U8 u8UpdateReady;
            MApp_ZUI_API_ShowWindow(HWND_KTV_MSGBOX_PANE, SW_HIDE);
            MApp_ZUI_API_RestoreFocusCheckpoint();
            u8UpdateReady = 2;
        }
        break;
        case HWND_KTV_MSGBOX_BTN_NO:
        {
            extern U8 u8UpdateReady;
            MApp_ZUI_API_ShowWindow(HWND_KTV_MSGBOX_PANE, SW_HIDE);
            MApp_ZUI_API_RestoreFocusCheckpoint();
            u8UpdateReady = 0;
        }
        break;
        case HWND_KTV_SETUP_RESET:
            _eKTVVolumeSetting.MusicVolume = KTV_MUSIC_VOLUME_DEF;
            _eKTVVolumeSetting.MicVolume = KTV_MIC_VOLUME_DEF;
            _eKTVVolumeSetting.MelodyVolume = KTV_MELODY_VOLUME_DEF;
            _eKTVVolumeSetting.Echo= KTV_ECHO_DEF;
            _eKTVVolumeSetting.MusicKey = KTV_MUSIC_KEY_DEF;
            _eKTVVolumeSetting.MusicTempo = KTV_MUSIC_TEMPO_DEF;
            _eKTVVolumeSetting.MusicMode = 0;
            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_SOUND_SETTING_PAGE, SW_SHOW);
        break;

        default:
        break;
    }
    return TRUE;
}
static BOOLEAN _MApp_KTV_Volume_Adjust(U16 act)
{
    if(act == EN_EXE_KTV_VOLUME_DECREASE)
    {
        if ( stGenSetting.g_SoundSetting.Volume > 0 )
        {
            stGenSetting.g_SoundSetting.Volume-= 5;
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SONG_PLAY_VOLUME, SW_SHOW);
        }
    }
    else if(act == EN_EXE_KTV_VOLUME_INCREASE)
    {
        if ( stGenSetting.g_SoundSetting.Volume < MAX_NUM_OF_VOL_LEVEL )
        {
            stGenSetting.g_SoundSetting.Volume+= 5;
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            MApp_ZUI_API_ShowWindow(HWND_KTV_SONG_PLAY_VOLUME, SW_SHOW);
        }
    }
    return TRUE;
}
BOOLEAN MApp_ZUI_ACT_AdjustSingerSearchListItem(U16 act)
{
    HWND wnd;
    U8 u8ItemIdx;
    U16 u16Max;
    wnd = MApp_ZUI_API_GetFocus();
    if( MApp_ZUI_API_GetParent(wnd) == HWND_KTV_SEARCH_BY_SINGER_PAGE)
    {
        for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SINGERS_PER_PAGE; u8ItemIdx++)
        {
            if(wnd == _SingerListPageItemHwndList[u8ItemIdx])
            {
                break;
            }
        }
        u8ItemIdx += u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE;
        u16Max = st_searchedsinger_buf->u16total;
        u8ItemIdx = MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SINGERITEM_INCREASE), u8ItemIdx, 0, u16Max-1, 1);
        u8KTVSearchSingerListPage = (u8ItemIdx)/NUM_OF_KTV_SINGERS_PER_PAGE;
        u8ItemIdx -= u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE;
        wnd = _SingerListPageItemHwndList[u8ItemIdx];
        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_PAGE, SW_SHOW);
    }
    else if( MApp_ZUI_API_GetParent(wnd) == HWND_KTV_SEARCH_BY_SINGER_NAMELIST)
    {
        for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SINGERS_PER_PAGE; u8ItemIdx++)
        {
            if(wnd == _SingerNameListPageItemHwndList[u8ItemIdx])
            {
                break;
            }
        }
        u8ItemIdx += u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE;
        u16Max = st_searchedsinger_buf->u16total;
        u8ItemIdx = MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SINGERITEM_INCREASE), u8ItemIdx, 0, u16Max-1, 1);
        u8KTVSearchSingerListPage = (u8ItemIdx)/NUM_OF_KTV_SINGERS_PER_PAGE;
        u8ItemIdx -= u8KTVSearchSingerListPage*NUM_OF_KTV_SINGERS_PER_PAGE;
        wnd = _SingerNameListPageItemHwndList[u8ItemIdx];
        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_NAMELIST, SW_SHOW);
    }
    MApp_ZUI_API_SetFocus(wnd);
    return TRUE;
}
BOOLEAN MApp_ZUI_ACT_AdjustSongSearchListItem(U16 act)
{
    HWND wnd;
    U8 u8ItemIdx;
    U16 u16Max = 0;
    wnd = MApp_ZUI_API_GetFocus();
    for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SONGS_PER_PAGE; u8ItemIdx++)
    {
        if(wnd == _SongListPageItemHwndList[u8ItemIdx])
        {
            break;
        }
    }
    u8ItemIdx += u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
    switch(hwnd_use_songlist_page )
    {
        case HWND_KTV_SEARCH_BY_SINGER_PAGE:
        case HWND_KTV_SEARCH_BY_SINGER_NAMELIST:
        case HWND_KTV_SEARCH_BY_LASTUPDATE:
        case HWND_KTV_SEARCH_BY_POPULAR:
            if(st_searchedsong_buf == NULL)
                break;

            u16Max = st_searchedsong_buf->u16total;
            break;

        case HWND_KTV_MY_FAVOURITE:
            if(st_ktv_list == NULL)
                break;

            u16Max = (U16)st_ktv_list->u8favorsongcounter;
        break;

        case HWND_KTV_SONGS_HAD_SING:
            if(st_ktv_list == NULL)
                break;

            u16Max = (U16)st_ktv_list->u8playedsongcounter;
        break;

         default:
            break;
    }
    u8ItemIdx = MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SONGITEM_INCREASE), u8ItemIdx, 0, u16Max-1, 1);
    u8KTVSearchSongListPage = (u8ItemIdx)/NUM_OF_KTV_SONGS_PER_PAGE;
    u8ItemIdx -= u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
    wnd = _SongListPageItemHwndList[u8ItemIdx];
    MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_FOUND_SONGS, SW_SHOW);
    MApp_ZUI_API_SetFocus(wnd);
    return TRUE;
}
BOOLEAN MApp_ZUI_ACT_AdjustSongFiretWordListItem(U16 act)
{
    HWND wnd;
    U8 u8ItemIdx;
    U16 u16Max = 0,u16PageMax = 0;
    wnd = MApp_ZUI_API_GetFocus();
    u16Max = st_searchedsong_buf->u16total;
    u8ItemIdx = u8KTVSearchSongFirstWordPageNum*NUM_OF_KTV_SONGS_FIRSTWORD_PER_PAGE+wnd-HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_1;
    u16PageMax = st_searchedsong_buf->u16total/NUM_OF_KTV_SONGS_FIRSTWORD_PER_PAGE;

    switch(act)
    {
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_DECREASE:
        {
            if(wnd==HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_1)
                wnd = wnd;
            else
                wnd = wnd-1;
        }
        break;
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_INCREASE:
        {
            if(u8ItemIdx>=u16Max)
                break;
            else
                wnd = wnd+1;
        }
        break;
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_LEFT:
        {
            if(wnd>=HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_1&&wnd<=HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_4)
                break;
            else
                wnd=wnd-4;
        }
        break;
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_RIGHT:
        {

            if(wnd>=HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_21&&wnd<=HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_MAX)
                break;
            else if((u8ItemIdx+4)<=u16Max)
                wnd=wnd+4;
        }
        break;
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_PAGEUP:
        {
            if(u8KTVSearchSongFirstWordPageNum)
            {
                u8KTVSearchSongFirstWordPageNum=u8KTVSearchSongFirstWordPageNum-1;
                wnd = HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_1;
            }
        }
        break;
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_PAGEDOWN:
        {
            if(u8KTVSearchSongFirstWordPageNum>=u16PageMax)
                break;
            else
            {
                u8KTVSearchSongFirstWordPageNum=u8KTVSearchSongFirstWordPageNum+1;
                wnd = HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_1;
            }
        }
        break;
    }
    MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_NAME_WORDNUMBER_LIST_PAGE, SW_SHOW);
    MApp_ZUI_API_SetFocus(wnd);
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_AdjustPlayListItem(U16 act)
{
    HWND wnd;
    U8 u8ItemIdx, u8Max;
    if(st_ktv_list == NULL)
        return FALSE;

    wnd = MApp_ZUI_API_GetFocus();
    for(u8ItemIdx=0; u8ItemIdx<NUM_OF_KTV_SONGS_PER_PAGE; u8ItemIdx++)
    {
        if(wnd == _SongToPlayItemHwndList[u8ItemIdx])
        {
            break;
        }
    }
    u8ItemIdx += u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
    u8Max = st_ktv_list->u8playsongcounter;
    u8ItemIdx = MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_PLAYLIST_INCREASE), u8ItemIdx, 0, u8Max-1, 1);
    u8KTVSearchSongListPage = (u8ItemIdx)/NUM_OF_KTV_SONGS_PER_PAGE;
    u8ItemIdx -= u8KTVSearchSongListPage*NUM_OF_KTV_SONGS_PER_PAGE;
    wnd = _SongToPlayItemHwndList[u8ItemIdx];
    MApp_ZUI_API_ShowWindow(HWND_KTV_SONGS_LIST_TO_PLAY, SW_SHOW);
    MApp_ZUI_API_SetFocus(wnd);
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_AdjustVolumeSettingListItem(U16 act)
{
    //U16 u16Temp;

    HWND hwnd;

    hwnd = MApp_ZUI_API_GetFocus();
    if(hwnd == HWND_INVALID)
    {
        return FALSE;
    }
     switch( hwnd )
    {
        case  HWND_KTV_SETUP_MUSIC_VOLUME_BAR:
            _eKTVVolumeSetting.MusicVolume = MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SETUP_ITEM_INCREASE), _eKTVVolumeSetting.MusicVolume,
                                                                    KTV_MUSIC_VOLUME_MIN, KTV_MUSIC_VOLUME_MAX, (KTV_MUSIC_VOLUME_MAX-KTV_MUSIC_VOLUME_MIN)/100 );

            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_MUSIC_VOLUME_BAR, SW_SHOW);

            // set ktv Music Volume
            MApp_KTV_SendMailBoxCmd(MB_KTV_CMD_SET_MUSIC_VOL, _eKTVVolumeSetting.MusicVolume);

            break;

        case  HWND_KTV_SETUP_MIC_VOLUME_BAR:
            _eKTVVolumeSetting.MicVolume = MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SETUP_ITEM_INCREASE), _eKTVVolumeSetting.MicVolume,
                                                                    KTV_MIC_VOLUME_MIN, KTV_MIC_VOLUME_MAX, (KTV_MIC_VOLUME_MAX-KTV_MIC_VOLUME_MIN)/100 );

            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_MIC_VOLUME_BAR, SW_SHOW);

            // set ktv Mic Volume
            // TODO:

            break;

        case  HWND_KTV_SETUP_MELODY_VOLUME_BAR:
            _eKTVVolumeSetting.MelodyVolume = MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SETUP_ITEM_INCREASE), _eKTVVolumeSetting.MelodyVolume,
                                                                        KTV_MELODY_VOLUME_MIN, KTV_MELODY_VOLUME_MAX, (KTV_MELODY_VOLUME_MAX -KTV_MELODY_VOLUME_MIN)/100);

            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_MELODY_VOLUME_BAR, SW_SHOW);

            // set ktv Music Melody
            MApp_KTV_SendMailBoxCmd(MB_KTV_CMD_SET_MUSIC_MELODY, _eKTVVolumeSetting.MelodyVolume);

            break;

        case  HWND_KTV_SETUP_ECHO_BAR:
            _eKTVVolumeSetting.Echo = MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SETUP_ITEM_INCREASE), _eKTVVolumeSetting.Echo,
                                                                    KTV_ECHO_MIN, KTV_ECHO_MAX, (KTV_ECHO_MAX-KTV_ECHO_MIN)/100 );

            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_ECHO_BAR, SW_SHOW);

            // set ktv Echo
            // TODO:

            break;

        case  HWND_KTV_SETUP_TONE_BAR:
            _eKTVVolumeSetting.MusicKey= MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SETUP_ITEM_INCREASE), _eKTVVolumeSetting.MusicKey,
                                                                KTV_MUSIC_KEY_MIN, KTV_MUSIC_KEY_MAX, 1);

            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_TONE_BAR, SW_SHOW);

            // set ktv Music Melody
            MApp_KTV_SendMailBoxCmd(MB_KTV_CMD_SET_MUSIC_KEY, _eKTVVolumeSetting.MusicKey);

            break;

        case  HWND_KTV_SETUP_PLAY_SPEED_BAR:
            _eKTVVolumeSetting.MusicTempo= MApp_ZUI_ACT_DecIncValue((act == EN_EXE_KTV_SETUP_ITEM_INCREASE), _eKTVVolumeSetting.MusicTempo,
                                                                    KTV_MUSIC_TEMPO_MIN, KTV_MUSIC_TEMPO_MAX, (KTV_MUSIC_TEMPO_MAX - KTV_MUSIC_TEMPO_MIN)/100);

            MApp_ZUI_API_ShowWindow(HWND_KTV_SETUP_PLAY_SPEED_BAR, SW_SHOW);

            // set ktv Music Melody
            MApp_KTV_SendMailBoxCmd(MB_KTV_CMD_SET_MUSIC_TEMPO, _eKTVVolumeSetting.MusicTempo);

            break;

        default:
            break;
    }
    return TRUE;
}

BOOLEAN MApp_ZUI_ACT_AdjustKeyUptoListItem(void)
{
    U8 i;
    HWND hwnd;

    hwnd = MApp_ZUI_API_GetFocus();
    if(hwnd == HWND_INVALID)
    {
        return FALSE;
    }
     switch( MApp_ZUI_API_GetParent(hwnd))
    {
        case  HWND_KTV_SEARCH_FOUND_SONGS:
            for(i=0; i<NUM_OF_KTV_SONGS_PER_PAGE; i++)
            {
                MApp_ZUI_API_EnableWindow(_SongListPageItemHwndList[i], ENABLE);
            }
            MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_SONGLIST_ITEM1);
            break;

        case  HWND_KTV_SONGS_LIST_TO_PLAY:
            for(i=0; i<NUM_OF_KTV_SONGS_PER_PAGE; i++)
            {
                MApp_ZUI_API_EnableWindow(_SongToPlayItemHwndList[i], ENABLE);
            }
            MApp_ZUI_API_SetFocus(HWND_KTV_SONGS_LIST_TO_PLAY_ITEM1);
            break;

        default:
            break;
    }
    return TRUE;
}

/******************************************************************************/
/// handler software keyboard digit input
/// @param  act \b IN Specify the input key type.
/// @return
/******************************************************************************/
static BOOLEAN _MApp_KTV_SoftwareKeyBoard_Input(U16 act)
{
    HWND wnd;
    U8  u8Char = 0, u8Len;

    wnd = MApp_ZUI_API_GetFocus();
    if(act == EN_EXE_KTV_SOFTWARW_KEYBOARD_DIGITINPUT)
    {
        for (u8Len = 0; u8Len < COUNTOF(hwnd2digitkey); u8Len++)
        {
            if (MApp_ZUI_API_GetFocus()== hwnd2digitkey[u8Len][0])
            {
                u8Char = (U8)hwnd2digitkey[u8Len][1];
                break;
            }
        }
        switch(u8Char)
        {
            case 1: // for add song into the last playlist
                // add API
                MApp_SearchSongByID(stp_ktv_songbuf, g_total_song,  stp_ktv_singerbuf, MApp_ZUI_ACTKTV_UnicodetoNum(_mKTVDigitInfo.u8Sting), st_searchedsong_buf, st_searchedsinger_buf);
                if((st_searchedsong_buf->u16total == 0) || (st_searchedsong_buf == NULL) || (st_searchedsinger_buf == NULL))
                {
                    memcpy(_mKTVToneInfo.u8Line1Sting, "没找到", sizeof("没找到"));
                    MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line1Sting);
                    memcpy(_mKTVDigitInfo.u8Sting, _mKTVToneInfo.u8Line1Sting, sizeof(_mKTVDigitInfo.u8Sting));
                    _mKTVDigitInfo.u8Input_Offset = 0;
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_ID_IDVALUE, SW_SHOW);
                    break;
                }
                MApp_AddSongToList(st_searchedsong_buf->st_songbuf[0],  stp_ktv_singerbuf, SONG_PLAYLIST, st_ktv_list);
                MApp_ZUI_API_ShowWindow(HWND_KTV_TONE_OF_SONGS, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_KTV_TONE_OF_SONGS_ORIGINAL);
                memcpy(_mKTVToneInfo.u8Line1Sting, "已将", sizeof("已将"));
                MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line1Sting);
                memcpy(_mKTVToneInfo.u8Line2Sting, "加入至待唱歌曲", sizeof("加入至待唱歌曲"));
                MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line2Sting);
                hwnd_use_tone_page = HWND_KTV_SOFTWARE_KEY_ENTER;
                break;

            case 2: // for add song into current playlist
                // add API
                MApp_SearchSongByID(stp_ktv_songbuf, g_total_song,  stp_ktv_singerbuf, MApp_ZUI_ACTKTV_UnicodetoNum(_mKTVDigitInfo.u8Sting), st_searchedsong_buf, st_searchedsinger_buf);
                if((st_searchedsong_buf->u16total == 0) || (st_searchedsong_buf == NULL) || (st_searchedsinger_buf == NULL))
                {
                    memcpy(_mKTVToneInfo.u8Line1Sting, "没找到", sizeof("没找到"));
                    MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line1Sting);
                    memcpy(_mKTVDigitInfo.u8Sting, _mKTVToneInfo.u8Line1Sting, sizeof(_mKTVDigitInfo.u8Sting));
                    _mKTVDigitInfo.u8Input_Offset = 0;
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_ID_IDVALUE, SW_SHOW);
                    break;
                }
                MApp_AddSongToList(st_searchedsong_buf->st_songbuf[0],  stp_ktv_singerbuf, SONG_INSERT_PLAYLIST, st_ktv_list);
                MApp_ZUI_API_ShowWindow(HWND_KTV_TONE_OF_SONGS, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_KTV_TONE_OF_SONGS_ORIGINAL);
                memcpy(_mKTVToneInfo.u8Line1Sting, "已将", sizeof("已将"));
                MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line1Sting);
                memcpy(_mKTVToneInfo.u8Line2Sting, "插播至待唱歌曲", sizeof("插播至待唱歌曲"));
                MApp_ZUI_ACTKTV_GBTOUNICODE(_mKTVToneInfo.u8Line2Sting);
                hwnd_use_tone_page = HWND_KTV_SOFTWARE_KEY_INSERT;
                break;

            case 3: // cancel input
                for (u8Len = 0; u8Len < NUM_OF_SOFTWARE_KEYBOARD_DIGIT_STRING; u8Len++)
                {
                    _mKTVDigitInfo.u8Sting[u8Len]=0;
                }
                _mKTVDigitInfo.u8Input_Offset= 0;
                MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_ID_IDVALUE, SW_SHOW);
                break;
            case CHAR_0:
            case CHAR_1:
            case CHAR_2:
            case CHAR_3:
            case CHAR_4:
            case CHAR_5:
            case CHAR_6:
            case CHAR_7:
            case CHAR_8:
            case CHAR_9:
                if(_mKTVDigitInfo.u8Input_Offset<(NUM_OF_SOFTWARE_KEYBOARD_DIGIT_STRING/2-1))
                {
                    _mKTVDigitInfo.u8Sting[_mKTVDigitInfo.u8Input_Offset*2] = u8Char;
                    _mKTVDigitInfo.u8Sting[_mKTVDigitInfo.u8Input_Offset*2 + 1] = 0;
                    _mKTVDigitInfo.u8Input_Offset+= 1;
                    MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_ID_IDVALUE, SW_SHOW);
                }
                break;
            default:
                break;
        }
    }
    else //EN_EXE_KTV_SOFTWARW_KEYBOARD_LETTERINPUT
    {
        U8 u8StingASCII[NUM_OF_SOFTWARE_KEYBOARD_LETTER_STRING/2];
        for (u8Len = 0; u8Len < COUNTOF(hwnd2letterkey); u8Len++)
        {
            if (MApp_ZUI_API_GetFocus()== hwnd2letterkey[u8Len][0])
            {
                u8Char = hwnd2letterkey[u8Len][1];
                break;
            }
        }
        if((u8Char >= CHAR_A) && (u8Char <= CHAR_Z))
        {
            if(_mKTVLetterInfo.u8Input_Offset<(NUM_OF_SOFTWARE_KEYBOARD_LETTER_STRING/2-1))
            {
                _mKTVLetterInfo.u8Sting[_mKTVLetterInfo.u8Input_Offset*2] = u8Char;
                _mKTVLetterInfo.u8Sting[_mKTVLetterInfo.u8Input_Offset*2 + 1] = 0;
                _mKTVLetterInfo.u8Input_Offset+= 1;
            }
        }
        else //clear input
        {
            for (u8Len = 0; u8Len < NUM_OF_SOFTWARE_KEYBOARD_LETTER_STRING; u8Len++)
            {
                _mKTVLetterInfo.u8Sting[u8Len]=0;
            }
            _mKTVLetterInfo.u8Input_Offset= 0;
        }
        for (u8Len = 0; u8Len < (NUM_OF_SOFTWARE_KEYBOARD_LETTER_STRING/2-1); u8Len++)
        {
            u8StingASCII[u8Len] = _mKTVLetterInfo.u8Sting[u8Len*2];
            u8StingASCII[u8Len+1] = 0;
        }
        MApp_SearchSingerBySongClassAndSpell(stp_ktv_singerbuf, stp_ktv_songbuf, g_total_song,  (U8)en_song_class, u8StingASCII, st_searchedsinger_buf);
        MApp_ZUI_API_ShowWindow(HWND_KTV_SEARCH_BY_SINGER_PAGE, SW_SHOW);
        u8KTVSearchSingerListPage = 0;
    }
    // Input Error!!
    if(u8Char == 0)
        return FALSE;
    return TRUE;
}
//////////////////////////////////////////////////////////
// Key Handler
BOOLEAN MApp_ZUI_ACT_HandleKTVKey(VIRTUAL_KEY_CODE key)
{
    if(MApp_ZUI_API_IsWindowVisible(HWND_KTV_WAITING_INFO))
    {
        if((key == VK_GREEN) && bShowErrorInfo)
        {
            bShowErrorInfo = FALSE;
            MApp_ZUI_API_ShowWindow(HWND_KTV_WAITING_INFO, SW_SHOW);
            memcpy(KTVWaitingStringbuf, _WaitingType[2], sizeof(_WaitingType[2]));
            MApp_ZUI_ACTKTV_GBTOUNICODE(KTVWaitingStringbuf);
            u8CountNum = u8WaitingCounter + 8;
        }
        return TRUE;
    }
    switch(key)
    {
        case VK_RED:
            {  extern U8 u8UpdateReady;
                if(u8UpdateReady==1)
                {
                    MApp_ZUI_API_ShowWindow(HWND_KTV_MSGBOX_PANE, SW_SHOW);
                    MApp_ZUI_API_StoreFocusCheckpoint();
                    MApp_ZUI_API_SetFocus(HWND_KTV_MSGBOX_BTN_YES);
                    return TRUE;
                }
            }
            break;
        case VK_GREEN:
            if(bShowErrorInfo)
            {
                bShowErrorInfo = FALSE;
                MApp_ZUI_API_StoreFocusCheckpoint();
                memcpy(KTVWaitingStringbuf, _WaitingType[2], sizeof(_WaitingType[2]));
                MApp_ZUI_ACTKTV_GBTOUNICODE(KTVWaitingStringbuf);
                MApp_ZUI_API_ShowWindow(HWND_KTV_WAITING_INFO, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_KTV_WAITING_TEXT);
                MApp_ZUI_API_SetTimer(HWND_KTV_WAITING_INFO, 0, 500);
                u8CountNum = 10;
            }
            break;
        case VK_YELLOW:
            break;
        case VK_BLUE:
            break;
        case VK_EXIT:
            break;
        case VK_STOP:
            break;
        case VK_PAUSE:
            break;
        case VK_SELECT:
            break;
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
            break;
        case VK_INFO:
        {
            HWND hwnd;
            hwnd = MApp_ZUI_API_GetFocus();
            if(hwnd == HWND_INVALID)
            {
            MApp_ZUI_API_ShowWindow(HWND_KTV_SIMPLE_CONTROL_BAR, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_KTV_CONTROL_PLAY);
            }
            else if(MApp_ZUI_API_IsWindowVisible(HWND_KTV_SIMPLE_CONTROL_BAR))
            {
                MApp_ZUI_API_ShowWindow(HWND_KTV_SIMPLE_CONTROL_BAR, SW_HIDE);
            }
        }
            break;
        case VK_LEFT:
        case VK_RIGHT:
        case VK_UP:
        case VK_DOWN:
            ZUIKTV_DBG(printf("VK_LRUD\n"));
            break;
        case VK_MENU:
            ZUIKTV_DBG(printf("VK_MENU\n"));
            _MApp_KTV_menukey_Handle();
            return TRUE;
        case VK_INPUT_SOURCE:
            _MApp_KTV_GotoInputSourceState();
            return TRUE;
        case VK_POWER:
            //MApp_ZUI_ACT_ExecuteKTVAction(EN_EXE_POWEROFF);
            return TRUE;
        break;
        default:
            break;
    }
    return FALSE;
}
BOOLEAN MApp_ZUI_ACT_ExecuteKTVAction(U16 act)
{
    BOOLEAN bExeResult = FALSE;

    if(MApp_ZUI_API_IsWindowVisible(HWND_KTV_WAITING_INFO))
        return FALSE;

    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            enKTVState = STATE_KTV_CLEAN_UP;
            bExeResult = TRUE;
        break;
        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            bExeResult = TRUE;
        break;
        case EN_EXE_KTV_ENTER:
            bExeResult = _MApp_KTV_Item_Select_Handle();
        break;
        case EN_EXE_KTV_SOFTWARW_KEYBOARD_DIGITINPUT:
        case EN_EXE_KTV_SOFTWARW_KEYBOARD_LETTERINPUT:
            bExeResult = _MApp_KTV_SoftwareKeyBoard_Input(act);
            break;
        case EN_EXE_KTV_VOLUME_DECREASE:
        case EN_EXE_KTV_VOLUME_INCREASE:
            bExeResult = _MApp_KTV_Volume_Adjust(act);
            break;
        case EN_EXE_KTV_SINGERITEM_INCREASE:
        case EN_EXE_KTV_SINGERITEM_DECREASE:
            bExeResult = MApp_ZUI_ACT_AdjustSingerSearchListItem(act);
            break;
        case EN_EXE_KTV_SONGITEM_INCREASE:
        case EN_EXE_KTV_SONGITEM_DECREASE:
            bExeResult = MApp_ZUI_ACT_AdjustSongSearchListItem(act);
            break;
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_DECREASE:
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_INCREASE:
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_LEFT:
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_RIGHT:
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_PAGEUP:
        case EN_EXE_KTV_SONG_FIRSTWORD_ITEM_PAGEDOWN:
            bExeResult = MApp_ZUI_ACT_AdjustSongFiretWordListItem(act);
            break;
        case EN_EXE_KTV_PLAYLIST_DECREASE:
        case EN_EXE_KTV_PLAYLIST_INCREASE:
            bExeResult = MApp_ZUI_ACT_AdjustPlayListItem(act);
            break;

        case EN_EXE_KTV_SETUP_ITEM_DECREASE:
        case EN_EXE_KTV_SETUP_ITEM_INCREASE:
            bExeResult = MApp_ZUI_ACT_AdjustVolumeSettingListItem(act);
            break;

        case EN_EXE_KTV_KEYUP_TO_LIST:
            bExeResult = MApp_ZUI_ACT_AdjustKeyUptoListItem();
            break;
        case EN_EXE_KTV_FAVOR_KEYRIGHT:
            if(MApp_ZUI_API_IsWindowEnabled(HWND_KTV_SEARCH_BY_SINGER_DELETE))
            {
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_DELETE);
            }
            else
            {
                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_AS_FAVOURITE);
            }
            bExeResult = TRUE;
            break;

        default:
            break;
    }
    return bExeResult;
}
S32 MApp_ZUI_ACT_KTVWinProc(HWND hwnd, PMSG msg)
{
    //printf("topicon_winproc\n");
    switch(msg->message)
    {
        case MSG_CREATE:
            break;
        case MSG_KEYDOWN:
            {
                if (msg->wParam == VK_LEFT)
                {
                    switch(hwnd)
                    {
                        case HWND_KTV_SOFTWARE_KEY_A:
                        case HWND_KTV_SOFTWARE_KEY_I:
                        case HWND_KTV_SOFTWARE_KEY_Q:
                        case HWND_KTV_SOFTWARE_KEY_Y:
                            if(hwnd_use_letter_board == HWND_KTV_SEARCH_BY_SINGER_PAGE)
                            {
                                MApp_ZUI_API_SetFocus(HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1);
                            }
                            break;
                        default:
                            break;
                    }
                }
                else if(msg->wParam == VK_RIGHT)
                {
                    switch(hwnd)
                    {
                        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM1:
                        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM2:
                        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM3:
                        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM4:
                        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM5:
                        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM6:
                        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM7:
                        case HWND_KTV_SEARCH_BY_SINGER_SINGERLIST_ITEM8:
                            MApp_ZUI_API_SetFocus(HWND_KTV_SOFTWARE_KEY_K);
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
        case MSG_TIMER:
            if(MApp_ZUI_API_IsWindowVisible(HWND_KTV_WAITING_INFO))
            {
                //printf("\r\n eKTVLoadFileAttribute = %bx", eKTVLoadFileAttribute);
                if(eKTVLoadFileAttribute & E_KTV_SOUNDFONT_LOADED)
                {
                    eKTVLoadFileAttribute  &= (enumKTVLoadFileAttribute)(~E_KTV_SOUNDFONT_LOADED);
                }
                else if(
                                (eKTVLoadFileAttribute & E_KTV_SOUNDFONTADDRESS_SEND)
                           && (eKTVLoadFileAttribute & E_KTV_MICADDRESS_SEND)
                           && (eKTVLoadFileAttribute & E_KTV_LRCADDRESS_SEND)
                           && (eKTVLoadFileAttribute & E_KTV_INIADDRESS_SEND)
                           )
                {
                    eKTVLoadFileAttribute &= (enumKTVLoadFileAttribute)(~(E_KTV_SOUNDFONTADDRESS_SEND | E_KTV_MICADDRESS_SEND | E_KTV_LRCADDRESS_SEND | E_KTV_INIADDRESS_SEND));
                }
                else if(eKTVLoadFileAttribute & E_KTV_SONG_LOADED)
                {
                    eKTVLoadFileAttribute &= (enumKTVLoadFileAttribute)(~E_KTV_SONG_LOADED);
                }

                if(!MDrv_UsbDeviceConnect()&&!MDrv_UsbDeviceConnect_Port2())    //close loading window when usb is not connected
                   u8TimeoutCounter=100;

                if(
                           ( (eKTVLoadFileAttribute & E_KTV_BEGIAN_LOAD)
                        && (u8WaitingCounter ++ > u8CountNum)
                       && !(eKTVLoadFileAttribute & E_KTV_SOUNDFONTADDRESS_SEND)
                       && !(eKTVLoadFileAttribute & E_KTV_MICADDRESS_SEND)
                       && !(eKTVLoadFileAttribute & E_KTV_LRCADDRESS_SEND)
                       && !(eKTVLoadFileAttribute & E_KTV_SOUNDFONT_LOADED)
                       && !(eKTVLoadFileAttribute & E_KTV_SONG_LOADED))
                       || (u8TimeoutCounter ++ > 80)
                    )
                {
                    u8TimeoutCounter = 0;
                    u8WaitingCounter = 0;
                    eKTVLoadFileAttribute &= (enumKTVLoadFileAttribute)(~E_KTV_BEGIAN_LOAD);
                    MApp_ZUI_API_ShowWindow(HWND_KTV_WAITING_INFO, SW_HIDE);
                    MApp_ZUI_API_RestoreFocusCheckpoint();

                    MApp_ZUI_API_KillTimer(HWND_KTV_WAITING_INFO, 0);
                }
                else if(MApp_ZUI_API_GetFocus() == HWND_KTV_WAITING_TEXT)
                {
                    MApp_ZUI_API_SetFocus(HWND_INVALID);
                }
                else
                {
                    MApp_ZUI_API_SetFocus(HWND_KTV_WAITING_TEXT);
                }
            }
            break;

    default:
        break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}
/////////////////////////////////////////////////////////
// Customize Window Procedures
#endif
#undef MAPP_ZUI_ACTKTV_C
