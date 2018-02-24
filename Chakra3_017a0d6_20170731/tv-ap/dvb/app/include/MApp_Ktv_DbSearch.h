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


#ifndef MAPP_KTV_DBSEARCH_H
#define MAPP_KTV_DBSEARCH_H

#include "datatype.h"
#include "MApp_Exit.h"
#include "MApp_ZUI_APIcommon.h"

#ifdef MAPP_KTV_DBSEARCH_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define MAX_SUITED_SONG 2000
#define MAX_SUITED_SINGER 2000
#define FILE_HEADER_SIZE 16
#define TOTAL_ITEM_OFFSET 8

#define NUM_OF_SONG_STRING      30
#define NUM_OF_SINGER_STRING    20

#define MAXNUM_OF_PLAY_SONG 30
#define MAXNUM_OF_PLAYED_SONG 50
#define MAXNUM_OF_FAVOR_SONG 30
#define MAXNUM_OF_REC_SONG 10
#define MAXNUM_OF_PLAYLIST      50 // must be more than other playlist

#define SONG_ATTR_PUBLIC BIT0
#define SONG_ATTR_EXPRIENCE BIT1
#define SONG_ATTR_LOVE BIT2
#define SONG_ATTR_BALLED BIT3
#define SONG_ATTR_REMINISCENCE BIT4
#define SONG_ATTR_DANCE BIT5
#define SONG_ATTR_RAP BIT6
#define SONG_ATTR_SCHOOL BIT7
#define SONG_ATTR_NEW BIT8
#define SONG_ATTR_HOT BIT9
#define SONG_ATTR_LOCAL BIT10

typedef enum
{
    SONG_CLASS_DEFAULT,
    SONG_CLASS_MALE,
    SONG_CLASS_FEMALE,
    SONG_CLASS_GROUP,
    SONG_CLASS_MALE_FEMALE,
    SONG_CLASS_FEMALE_FEMALE,
    SONG_CLASS_MALE_MALE,
    MAX_SONG_CLASS,
}EN_SONG_CLASS;

typedef enum
{
    SONG_LANGUAGE_DEFAULT,
    SONG_LANGUAGE_CHINESE,
    SONG_LANGUAGE_TAIWAN,
    SONG_LANGUAGE_CANTONESS,
    SONG_LANGUAGE_KOREAN,
    SONG_LANGUAGE_JANPANESE,
    SONG_LANGUAGE_ENGLISH,
    SONG_LANGUAGE_OTHER,
    MAX_SONG_LANGUAGE
}EN_SONG_LANGUAGE;

typedef struct
{
    U32 dwSongID;
    U16 wsSongName[NUM_OF_SONG_STRING];    //song name(unicode;first byte is the length)
    U8 csSongSpell[NUM_OF_SONG_STRING];   //song spell(string; first byte is the length)
    U8 bLanuage;
    U8 bNameCount;
    U8 bSongZone;
    U8 bSongClass;
    U8 bSimpStroke;
    U8 bSongPitch;
    U16 wFlashU;
    U16 wFlashV;
    U16 wFlashW;
    U16 wFlashX;
    U16 wFlashY;           //Flash* is the flash data
    U16 wPublic;           //attribute of song
    U16 wSingerID;         //singer id
    U16 wSingerIdx;        //singer index in singer list
} TKtvTable;

typedef struct
{
    U16 ID;
    U16 Name[NUM_OF_SINGER_STRING];      //singer name(unicode;first byte is the length)
    U8 Spell[NUM_OF_SINGER_STRING];     //singer spell(string;first byte is the length)
      U8 Count;         //singer name word number
    U8 reserved;
} TKtvSinger;

typedef struct
{
    U16 u16total;
    U16 u16Reserve;
    const TKtvSinger *st_singerbuf[MAX_SUITED_SINGER];
}ST_SEARCHED_SINGERS;

typedef struct
{
    U16 u16total;
    U16 u16Reserve;
    const TKtvTable *st_songbuf[MAX_SUITED_SONG];
}ST_SEARCHED_SONGS;

typedef struct
{
    U32     u32Song_ID;
    U16     u16Singer_ID;
    U16     u16Reserve;
    U16     u16SongSting[NUM_OF_SONG_STRING];// 30 UNICODE
    U16     u16SingerSting[NUM_OF_SINGER_STRING];// 20 UNICODE
} ST_LIST_ITEM;

typedef enum
{
    SONG_PLAYLIST,
    SONG_PLAYEDLIST,
    SONG_FAVORLIST,
    SONG_INSERT_PLAYLIST,
    MAX_LIST_TYPE
}EN_LIST_TYPE;

typedef enum
{
    SONG_FAVORLIST_TO_PLAYLIST,
    SONG_PLAYEDLIST_TO_PLAYLIST,
    SONG_FAVORLIST_INSERT_PLAYLIST,
    SONG_PLAYEDLIST_INSERT_PLAYLIST,
    SONG_PLAYEDLIST_TO_FAVORLIST,
    SONG_PLAYLIST_TO_FAVORLIST,
}EN_LIST_ACT_TYPE;

typedef enum
{
    SONG_MOVEUP,
    SONG_MOVEDOWN,
    MAX_MOVE_TYPE
}EN_MOVE_TYPE;

typedef struct
{
    U8 u8playsongcounter;
    ST_LIST_ITEM st_play_song_list[MAXNUM_OF_PLAY_SONG];
    U8 u8playedsongcounter;
    ST_LIST_ITEM st_played_song_list[MAXNUM_OF_PLAYED_SONG];
    U8 u8favorsongcounter;
    ST_LIST_ITEM st_favor_song_list[MAXNUM_OF_FAVOR_SONG];
    U8 u8CurrentRecSongIndex;
    U32 u32RecSongID[MAXNUM_OF_REC_SONG];
}ST_KTV_LIST;

INTERFACE ST_SEARCHED_SONGS *st_searchedsong_buf;
INTERFACE ST_SEARCHED_SINGERS *st_searchedsinger_buf;
INTERFACE const TKtvSinger *stp_ktv_singerbuf;
INTERFACE const TKtvTable  *stp_ktv_songbuf;
INTERFACE U32 g_total_song;
INTERFACE U32 g_total_singer;
INTERFACE ST_KTV_LIST *st_ktv_list;
INTERFACE void MApp_ConvertFlashNumberToFileName(U16 wFlash,U8 *FileName);
INTERFACE BOOLEAN MApp_SearchSingerBySongClassAndSpell(const TKtvSinger *stp_singer,const TKtvTable *stp_song,U32 total_song,U8 u8cl,U8 *u8spl,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSingerBySongClass(const TKtvSinger *stp_singer,const TKtvTable *stp_song,U32 total_song,U8 u8cl,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongBySinger(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer, ST_SEARCHED_SONGS *stp_searched_song);
INTERFACE BOOLEAN MApp_SearchSongByLanguageAndNameCount(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8Lan,U8 u8Count,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongByLanguageAndNameCountDifferentFirstWord(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8Lan,U8 u8Count,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongByLanguageAndNameCountSameFirstWord(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8Lan,U8 u8Count,U16 wFirstWord,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongByLanguage(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8Lan,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongBySpell(const TKtvTable *stp_song,U32 total_song,U8 *u8spl,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongByStroke(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8key,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongByAttribute(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U16 u16key,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongByID(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U32 u32_id,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer);
INTERFACE BOOLEAN MApp_SearchSongByAttributeAndSpell(const TKtvTable *stp_song, U32 total, U16 u16key, U8 *u8spl, ST_SEARCHED_SONGS *stp_searched_song);
INTERFACE BOOLEAN MApp_SearchSongByLanguageAndSpell(const TKtvTable *stp_song, U32 total, U8 u8Lan, U8 *u8spl, ST_SEARCHED_SONGS *stp_searched_song);
INTERFACE BOOLEAN MApp_SearchSongBySingerAndSpell(const TKtvTable *stp_song,const TKtvSinger *stp_singer,U32 total, U8 *u8spl, ST_SEARCHED_SONGS *stp_searched_song);

INTERFACE BOOLEAN MApp_AddSongToList(const TKtvTable *stp_song,const TKtvSinger *stp_singerbuf,U8 lst,ST_KTV_LIST *stp_list);
INTERFACE BOOLEAN MApp_MoveSongBetweenlist(ST_KTV_LIST *stp_list,  U16 u16index, EN_LIST_ACT_TYPE lst);
INTERFACE BOOLEAN MApp_RemoveSongFromList(U32 u32songid,U8 lst,ST_KTV_LIST *stp_list);
INTERFACE BOOLEAN MApp_MoveSong(U8 u8index, EN_MOVE_TYPE u8Movetype, ST_KTV_LIST *stp_list);
INTERFACE BOOLEAN MApp_PlayedSong(U8 u8index, ST_KTV_LIST *stp_list);
INTERFACE BOOLEAN MApp_IsSonginPlaylist(U32 u32SongID, ST_KTV_LIST *stp_list);

#undef INTERFACE
#endif

