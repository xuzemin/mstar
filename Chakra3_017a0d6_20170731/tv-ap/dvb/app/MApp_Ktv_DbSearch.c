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

///////////////////////////////////////////////////////////////////////////////
/// @file MApp_Singerlist.c
/// @brief Singer list query
/// @author MStar Semiconductor Inc.
///
/// KTV quecy & playback kernel provide a simple interface to let users implement
/// KTV function on MStar chip.
///
///////////////////////////////////////////////////////////////////////////////

#define MAPP_KTV_DBSEARCH_C
//---------------------------------------------------------------------------
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "msAPI_Global.h"

#ifdef ENABLE_KTV
#include "MApp_KTV.h"
#include "MApp_Ktv_DbSearch.h"


//----------------------------------------------------------------------------
//cmpare with input str
//return 0 means key is never equal to s
//return 1 means key is equal to s
//return 2 means key is maybe equal to s
U16 MApp_CompareWithKeyStr(const U8 *key,const U8 *s)
{
    U8 i, len;
    U8 len1=strlen((char *)key);
    U8 len2=s[0];
    const U8 *tmp=&(s[1]);

    if(len1>len2) return 0;

    len = (len1 < len2) ? len1:len2;

    for (i = 0; i < len; i ++)
    {
        if (key[i] != tmp[i]) return 0;
    }
    if(len1==len2)  return 1;
    else return 2;
}

void MApp_ConvertFlashNumberToFileName(U16 wFlash,U8 *FileName)
{
    U16 wFlashTemp;
    wFlashTemp = (wFlash&(BIT15|BIT14|BIT13|BIT12))>>12;
    FileName[0]=wFlashTemp+'A';
    wFlashTemp = (wFlash&(BIT12|BIT11|BIT10|BIT9))>>9;
    if(wFlashTemp>10)
    {
        FileName[1]='1';
        FileName[2]='0'+wFlashTemp-10;
    }
    else
    {
        FileName[1]='0';
        FileName[2]='0'+wFlashTemp;
    }
    FileName[3]='_';
    wFlashTemp = (wFlash&(BIT8|BIT7))>>7;
    FileName[4]='0'+wFlashTemp;
    wFlashTemp = (wFlash&(BIT6|BIT5|BIT4|BIT3))>>3;
    if(wFlashTemp>10)
    {
        FileName[5]='1';
        FileName[6]='0'+wFlashTemp-10;
    }
    else
    {
        FileName[5]='0';
        FileName[6]='0'+wFlashTemp;
    }
    FileName[7]='_';
    FileName[8]='0';
    wFlashTemp=wFlash&(BIT0|BIT1|BIT2);
    FileName[9]=wFlashTemp+'0';
    FileName[10]='.';
    FileName[11]='a';
    FileName[12]='v';
    FileName[13]='i';
    FileName[14]=0;

}

//----------------------------------------------------------------------------
//search singer by class and spell
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//u8cl--song class
//u8spl--spell string. must end with 0
//stp_searched_singer--search result output

BOOLEAN MApp_SearchSingerBySongClassAndSpell(const TKtvSinger *stp_singer,const TKtvTable *stp_song,U32 total_song,U8 u8cl,U8 *u8spl,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp,dwtmp2;
    if(u8spl==NULL||stp_singer==NULL||total_song==0||u8cl>=MAX_SONG_CLASS || stp_searched_singer == NULL || stp_song == NULL)
        return FALSE;

    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total_song;dwtmp++)
    {
        if(stp_searched_singer->u16total==MAX_SUITED_SINGER)
            return TRUE;
        if(stp_song[dwtmp].bSongClass==u8cl)
        {
            if(MApp_CompareWithKeyStr(u8spl,stp_singer[stp_song[dwtmp].wSingerIdx].Spell))
            {
                for(dwtmp2=0;dwtmp2<stp_searched_singer->u16total;dwtmp2++)
                    if(stp_searched_singer->st_singerbuf[dwtmp2]->ID==stp_singer[stp_song[dwtmp].wSingerIdx].ID)
                        break;
                if(dwtmp2==stp_searched_singer->u16total)
            {
                stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
                stp_searched_singer->u16total++;
            }
        }
    }
    }
    return TRUE;
}

//----------------------------------------------------------------------------
//search singer by class
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//u8cl--song class
//stp_searched_singer--search result output

BOOLEAN MApp_SearchSingerBySongClass(const TKtvSinger *stp_singer,const TKtvTable *stp_song,U32 total_song,U8 u8cl,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp,dwtmp2;
    if(stp_singer==NULL|| stp_song == NULL || total_song==0||u8cl>=MAX_SONG_CLASS || stp_searched_singer == NULL)
        return FALSE;

    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total_song;dwtmp++)
    {
        if(stp_searched_singer->u16total==MAX_SUITED_SINGER)
            return TRUE;
        if(stp_song[dwtmp].bSongClass==u8cl)
        {
            for(dwtmp2=0;dwtmp2<stp_searched_singer->u16total;dwtmp2++)
                if(stp_searched_singer->st_singerbuf[dwtmp2]->ID==stp_singer[stp_song[dwtmp].wSingerIdx].ID)
                    break;
            if(dwtmp2==stp_searched_singer->u16total)
            {
            stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
            stp_searched_singer->u16total++;
        }
    }
    }
    return TRUE;
}


//----------------------------------------------------------------------------
//search song by singer
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer address which you want to search song with
//stp_searched_song--search result output

BOOLEAN MApp_SearchSongBySinger(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer, ST_SEARCHED_SONGS *stp_searched_song)
{
    U32 dwtmp;

    if(stp_song==NULL||stp_singer==NULL||total==0 || stp_searched_song == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(stp_song[dwtmp].wSingerID==stp_singer->ID)
        {
            stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
            stp_searched_song->u16total++;
        }
    }
    return TRUE;
}

//----------------------------------------------------------------------------
//search song by lnguage and name counter
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u8Lan--song language
//u8Count--number of song's word
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongByLanguageAndNameCount(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8Lan,U8 u8Count,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp;

    if(stp_song==NULL||total==0|| stp_singer == NULL || u8Lan>=MAX_SONG_LANGUAGE||u8Count==0 || stp_searched_song == NULL || stp_searched_singer == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(u8Count>11)
        {
            if(stp_song[dwtmp].bLanuage==u8Lan&&stp_song[dwtmp].bNameCount>=u8Count)
            {
                stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                stp_searched_song->u16total++;
                stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
                stp_searched_singer->u16total++;
            }
        }
        else
        {
            if(stp_song[dwtmp].bLanuage==u8Lan&&stp_song[dwtmp].bNameCount==u8Count)
            {
                stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                stp_searched_song->u16total++;
                stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
                stp_searched_singer->u16total++;
            }
        }
    }
    return TRUE;
}
//----------------------------------------------------------------------------
//search song by lnguage and name counter
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u8Lan--song language
//u8Count--number of song's word
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongByLanguageAndNameCountDifferentFirstWord(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8Lan,U8 u8Count,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp;
    U16 wtmp=0;

    if(stp_song==NULL||total==0||stp_singer == NULL || u8Lan>=MAX_SONG_LANGUAGE||u8Count==0 || stp_searched_song == NULL  || stp_searched_singer == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
         if(stp_searched_song->u16total==MAX_SUITED_SONG)
             return TRUE;
        if(u8Count>11)
        {
            if(stp_song[dwtmp].bLanuage==u8Lan&&stp_song[dwtmp].bNameCount>=u8Count)
            {
                if(wtmp!=stp_song[dwtmp].wsSongName[1])
                {
                    wtmp=stp_song[dwtmp].wsSongName[1];
                    stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                    stp_searched_song->u16total++;
                    stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
                    stp_searched_singer->u16total++;
                }
            }
        }
        else
        {
            if(stp_song[dwtmp].bLanuage==u8Lan&&stp_song[dwtmp].bNameCount==u8Count)
            {
                if(wtmp!=stp_song[dwtmp].wsSongName[1])
                {
                    wtmp=stp_song[dwtmp].wsSongName[1];
                    stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                    stp_searched_song->u16total++;
                    stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
                    stp_searched_singer->u16total++;
                }
            }
        }
    }
    return TRUE;
}
//----------------------------------------------------------------------------
//search song by lnguage and name counter
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u8Lan--song language
//u8Count--number of song's word
//u16FirstWord--song's Firstword
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongByLanguageAndNameCountSameFirstWord(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8Lan,U8 u8Count,U16 wFirstWord,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp;
    if(stp_song==NULL||total==0||stp_singer == NULL || u8Lan>=MAX_SONG_LANGUAGE||u8Count==0 || stp_searched_song == NULL || stp_searched_singer == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(u8Count>11)
        {
            if(stp_song[dwtmp].bLanuage==u8Lan&&stp_song[dwtmp].bNameCount>=u8Count)
            {
                if(wFirstWord==stp_song[dwtmp].wsSongName[1])
                {
                    stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                    stp_searched_song->u16total++;
                    stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
                    stp_searched_singer->u16total++;
                }
            }
        }
        else
        {
            if(stp_song[dwtmp].bLanuage==u8Lan&&stp_song[dwtmp].bNameCount==u8Count)
            {
                if(wFirstWord==stp_song[dwtmp].wsSongName[1])
                {
                    stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                    stp_searched_song->u16total++;
                    stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
                    stp_searched_singer->u16total++;
                }
            }
        }
    }
    return TRUE;
}

//----------------------------------------------------------------------------
//search song by lnguage
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u8Lan--song language
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongByLanguage(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8Lan,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp;

    if(stp_song==NULL||total==0||stp_singer == NULL || u8Lan>=MAX_SONG_LANGUAGE || stp_searched_song == NULL || stp_searched_singer == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(stp_song[dwtmp].bLanuage==u8Lan)
        {
            stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
            stp_searched_song->u16total++;
            stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
            stp_searched_singer->u16total++;
        }
    }
    return TRUE;
}
//----------------------------------------------------------------------------
//search song by Spell
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//* u8Spl--song Spell
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongBySpell(const TKtvTable *stp_song,U32 total_song,U8 *u8spl,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp,dwtmp2;
    if(u8spl==NULL||total_song==0|| stp_searched_singer == NULL || stp_song == NULL)
        return FALSE;

    stp_searched_singer->u16total=0;
    stp_searched_song->u16total=0;
    for(dwtmp=0;dwtmp<total_song;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SINGER)
            return TRUE;
        if(MApp_CompareWithKeyStr(u8spl,stp_song[dwtmp].csSongSpell))
        {
            for(dwtmp2=0;dwtmp2<stp_searched_song->u16total;dwtmp2++)
                if(stp_searched_song->st_songbuf[dwtmp2]->dwSongID==stp_song[dwtmp].dwSongID)
                    break;
            if(dwtmp2==stp_searched_song->u16total)
            {
                stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                stp_searched_song->u16total++;
            }
        }
    }
    return TRUE;
}

//----------------------------------------------------------------------------
//search song by lnguage and spell
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u8Lan--song language
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongByLanguageAndSpell(const TKtvTable *stp_song, U32 total, U8 u8Lan, U8 *u8spl, ST_SEARCHED_SONGS *stp_searched_song)
{
    U32 dwtmp, dwtmp2;
    U8 u8FoundOne = FALSE;

    if(stp_song==NULL||total==0||u8Lan>=MAX_SONG_LANGUAGE || stp_searched_song == NULL || u8spl == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(u8Lan==SONG_LANGUAGE_CHINESE && stp_song[dwtmp].bLanuage==u8Lan)
        {
            u8FoundOne = TRUE;
        }
        else if(u8Lan==SONG_LANGUAGE_CANTONESS && (stp_song[dwtmp].bLanuage==SONG_LANGUAGE_CANTONESS || stp_song[dwtmp].bLanuage==SONG_LANGUAGE_TAIWAN))
        {
            u8FoundOne = TRUE;
        }
        else if(u8Lan==SONG_LANGUAGE_ENGLISH &&
            ( stp_song[dwtmp].bLanuage==SONG_LANGUAGE_ENGLISH||
              stp_song[dwtmp].bLanuage==SONG_LANGUAGE_JANPANESE||
              stp_song[dwtmp].bLanuage==SONG_LANGUAGE_KOREAN||
              stp_song[dwtmp].bLanuage==SONG_LANGUAGE_OTHER))
        {
            u8FoundOne = TRUE;
        }
        if(u8FoundOne)
        {
            u8FoundOne = FALSE;
            if(MApp_CompareWithKeyStr(u8spl,stp_song[dwtmp].csSongSpell))
            {
                for(dwtmp2=0;dwtmp2<stp_searched_song->u16total;dwtmp2++)
                    if(stp_searched_song->st_songbuf[dwtmp2]->dwSongID==stp_song[dwtmp].dwSongID)
                        break;
                if(dwtmp2==stp_searched_song->u16total)
                {
                    stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                    stp_searched_song->u16total++;
                }
            }
        }
    }
    return TRUE;
}

//----------------------------------------------------------------------------
//search song by stroke
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u8key--the song's stroke num which you will search song with. it is a number.
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongByStroke(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U8 u8key,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp;

    if(stp_song==NULL||stp_singer == NULL || u8key==0 ||total==0 || stp_searched_song == NULL || stp_searched_singer == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(stp_song[dwtmp].bSimpStroke==u8key)
        {
            stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
            stp_searched_song->u16total++;
            stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
            stp_searched_singer->u16total++;
        }
    }
    return TRUE;
}

//----------------------------------------------------------------------------
//search song by attribute
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u16key--attribute value
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongByAttribute(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U16 u16key,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp;

    if(stp_song==NULL||total==0 || stp_singer == NULL || stp_searched_song == NULL ||stp_searched_singer == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(stp_song[dwtmp].wPublic&u16key)
        {
            stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
            stp_searched_song->u16total++;
            stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
            stp_searched_singer->u16total++;
        }
    }
    return TRUE;
}
//----------------------------------------------------------------------------
//search song by attribute and spell
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u16key--attribute value
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output

BOOLEAN MApp_SearchSongByAttributeAndSpell(const TKtvTable *stp_song, U32 total, U16 u16key, U8 *u8spl, ST_SEARCHED_SONGS *stp_searched_song)
{
    U32 dwtmp, dwtmp2;

    if(stp_song==NULL||total==0 || stp_searched_song == NULL ||u8spl==NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(stp_song[dwtmp].wPublic&u16key)
        {
            if(MApp_CompareWithKeyStr(u8spl,stp_song[dwtmp].csSongSpell))
            {
                for(dwtmp2=0;dwtmp2<stp_searched_song->u16total;dwtmp2++)
                    if(stp_searched_song->st_songbuf[dwtmp2]->dwSongID==stp_song[dwtmp].dwSongID)
                        break;
                if(dwtmp2==stp_searched_song->u16total)
                {
                    stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                    stp_searched_song->u16total++;
                }
            }
        }
    }
    return TRUE;
}

//----------------------------------------------------------------------------
//search song by singer and song's spell
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer address which you want to search song with
//stp_searched_song--search result output

BOOLEAN MApp_SearchSongBySingerAndSpell(const TKtvTable *stp_song,const TKtvSinger *stp_singer,U32 total, U8 *u8spl, ST_SEARCHED_SONGS *stp_searched_song)
{
    U32 dwtmp, dwtmp2;

    if(stp_song==NULL||stp_singer==NULL||total==0 || stp_searched_song == NULL || u8spl == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_searched_song->u16total==MAX_SUITED_SONG)
            return TRUE;
        if(stp_song[dwtmp].wSingerID==stp_singer->ID)
        {
            if(MApp_CompareWithKeyStr(u8spl,stp_song[dwtmp].csSongSpell))
            {
                for(dwtmp2=0;dwtmp2<stp_searched_song->u16total;dwtmp2++)
                    if(stp_searched_song->st_songbuf[dwtmp2]->dwSongID==stp_song[dwtmp].dwSongID)
                        break;
                if(dwtmp2==stp_searched_song->u16total)
                {
                    stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
                    stp_searched_song->u16total++;
                }
            }
        }
    }
    return TRUE;
}
//----------------------------------------------------------------------------
//search song by ID
//stp_song--song buf for saving the data from bin file. please use global var 'stp_ktv_songbuf'
//total_song--total song number of database
//stp_singer--singer buf for saving the data from bin file. please use global var 'stp_ktv_singerbuf'
//u32_id--song id
//stp_searched_song--search result of song output
//stp_searched_singer--search result of singer output
BOOLEAN MApp_SearchSongByID(const TKtvTable *stp_song,U32 total,const TKtvSinger *stp_singer,U32 u32_id,ST_SEARCHED_SONGS *stp_searched_song,ST_SEARCHED_SINGERS *stp_searched_singer)
{
    U32 dwtmp;

    if(stp_song==NULL||total==0 || stp_singer == NULL  || stp_searched_song == NULL || stp_searched_singer == NULL)
        return FALSE;

    stp_searched_song->u16total=0;
    stp_searched_singer->u16total=0;
    for(dwtmp=0;dwtmp<total;dwtmp++)
    {
        if(stp_song[dwtmp].dwSongID==u32_id)
        {
            stp_searched_song->st_songbuf[stp_searched_song->u16total]=&(stp_song[dwtmp]);
            stp_searched_song->u16total++;
            stp_searched_singer->st_singerbuf[stp_searched_singer->u16total]=&(stp_singer[stp_song[dwtmp].wSingerIdx]);
            stp_searched_singer->u16total++;
        }
    }
    return TRUE;
}

//----------------------------------------------------------------------------
//copy string from source to destination;first byte of string is the length of str
//dst--output string
//src--src string
static void MApp_Db_Str_Cpy(U16 *dst, U16 *src)
{
    U16 i;
    for(i=0;i<src[0]+1;i++)
        dst[i]=src[i];
}

//----------------------------------------------------------------------------
//Add song to list
//stp_song--the song user select
//stp_singerbuf--singer buffer address; please use global var 'stp_ktv_singerbuf'
//lst--list type to add
//stp_list--output list
BOOLEAN MApp_AddSongToList(const TKtvTable *stp_song, const TKtvSinger *stp_singerbuf,U8 lst,ST_KTV_LIST *stp_list)
{
   U8 i;

   if(stp_song==NULL ||stp_singerbuf == NULL || stp_list == NULL)
        return FALSE;

   MApp_KTV_SetPlayListModifyFlag();
   switch(lst)
   {
        case SONG_PLAYLIST:
            if(stp_list->u8playsongcounter>=MAXNUM_OF_PLAY_SONG)
                return FALSE;
            /*for(i=0;i<stp_list->u8playsongcounter;i++)
            {
                if(stp_list->st_play_song_list[i].u32Song_ID==stp_song->dwSongID)
                    return TRUE;
            }*/
            stp_list->st_play_song_list[stp_list->u8playsongcounter].u16Singer_ID=stp_singerbuf[stp_song->wSingerIdx].ID;
            MApp_Db_Str_Cpy(stp_list->st_play_song_list[stp_list->u8playsongcounter].u16SingerSting, (U16 *)stp_singerbuf[stp_song->wSingerIdx].Name);
            stp_list->st_play_song_list[stp_list->u8playsongcounter].u32Song_ID=stp_song->dwSongID;
            MApp_Db_Str_Cpy(stp_list->st_play_song_list[stp_list->u8playsongcounter++].u16SongSting, (U16 *)stp_song->wsSongName);
            return TRUE;
        case SONG_PLAYEDLIST:
            if(stp_list->u8favorsongcounter>=MAXNUM_OF_PLAYED_SONG)
                return FALSE;
            for(i=0;i<stp_list->u8playedsongcounter;i++)
            {
                if(stp_list->st_played_song_list[i].u32Song_ID==stp_song->dwSongID)
                    return TRUE;
            }
            stp_list->st_played_song_list[stp_list->u8playedsongcounter].u16Singer_ID=stp_singerbuf[stp_song->wSingerIdx].ID;
            MApp_Db_Str_Cpy(stp_list->st_played_song_list[stp_list->u8playedsongcounter].u16SingerSting, (U16 *)stp_singerbuf[stp_song->wSingerIdx].Name);
            stp_list->st_played_song_list[stp_list->u8playedsongcounter].u32Song_ID=stp_song->dwSongID;
            MApp_Db_Str_Cpy(stp_list->st_played_song_list[stp_list->u8playedsongcounter++].u16SongSting, (U16 *)stp_song->wsSongName);
            return TRUE;
        case SONG_FAVORLIST:
            if(stp_list->u8favorsongcounter>=MAXNUM_OF_FAVOR_SONG)
                return FALSE;
            for(i=0;i<stp_list->u8favorsongcounter;i++)
            {
                if(stp_list->st_favor_song_list[i].u32Song_ID==stp_song->dwSongID)
                    return TRUE;
            }
            stp_list->st_favor_song_list[stp_list->u8favorsongcounter].u16Singer_ID=stp_singerbuf[stp_song->wSingerIdx].ID;
            MApp_Db_Str_Cpy(stp_list->st_favor_song_list[stp_list->u8favorsongcounter].u16SingerSting, (U16 *)stp_singerbuf[stp_song->wSingerIdx].Name);
            stp_list->st_favor_song_list[stp_list->u8favorsongcounter].u32Song_ID=stp_song->dwSongID;
            MApp_Db_Str_Cpy(stp_list->st_favor_song_list[stp_list->u8favorsongcounter++].u16SongSting, (U16 *)stp_song->wsSongName);
            return TRUE;
        case SONG_INSERT_PLAYLIST:
            if(stp_list->u8playsongcounter>=MAXNUM_OF_PLAY_SONG)
                return FALSE;
            for(i=stp_list->u8playsongcounter;i>0;i--)
            {
                stp_list->st_play_song_list[i].u16Singer_ID=stp_list->st_play_song_list[i-1].u16Singer_ID;
                MApp_Db_Str_Cpy(stp_list->st_play_song_list[i].u16SingerSting, (U16 *)stp_list->st_play_song_list[i-1].u16SingerSting);
                stp_list->st_play_song_list[i].u32Song_ID=stp_list->st_play_song_list[i-1].u32Song_ID;
                MApp_Db_Str_Cpy(stp_list->st_play_song_list[i].u16SongSting, (U16 *)stp_list->st_play_song_list[i-1].u16SongSting);
            }
            stp_list->st_play_song_list[0].u16Singer_ID=stp_singerbuf[stp_song->wSingerIdx].ID;
            MApp_Db_Str_Cpy(stp_list->st_play_song_list[0].u16SingerSting, (U16 *)stp_singerbuf[stp_song->wSingerIdx].Name);
            stp_list->st_play_song_list[0].u32Song_ID=stp_song->dwSongID;
            MApp_Db_Str_Cpy(stp_list->st_play_song_list[0].u16SongSting, (U16 *)stp_song->wsSongName);
            stp_list->u8playsongcounter++;
            return TRUE;

   }
   return FALSE;
}

//----------------------------------------------------------------------------
//Add song from my favourite list or the played list to playlist, or add song from the played list to my favourite list
//@u8index--> the index in the source list
//@lst-->list type to add
//@stp_list--> song list
//----------------------------------------------------------------------------
BOOLEAN MApp_MoveSongBetweenlist(ST_KTV_LIST *stp_list,  U16 u16index, EN_LIST_ACT_TYPE lst)
{
   U8 i;

    if(stp_list == NULL)
        return FALSE;

   MApp_KTV_SetPlayListModifyFlag();
   switch(lst)
   {
        case SONG_FAVORLIST_TO_PLAYLIST:
            if((stp_list->u8playsongcounter >= MAXNUM_OF_PLAY_SONG) ||(u16index >= MAXNUM_OF_FAVOR_SONG))
                return FALSE;

            memcpy(&(stp_list->st_play_song_list[stp_list->u8playsongcounter]),  &(stp_list->st_favor_song_list[u16index]), sizeof(ST_LIST_ITEM));
            stp_list->u8playsongcounter++;
            break;
        case SONG_PLAYEDLIST_TO_PLAYLIST:
            if((stp_list->u8playsongcounter >= MAXNUM_OF_PLAY_SONG) ||(u16index >= MAXNUM_OF_PLAYED_SONG))
                return FALSE;

            memcpy(&(stp_list->st_play_song_list[stp_list->u8playsongcounter]),  &(stp_list->st_played_song_list[u16index]), sizeof(ST_LIST_ITEM));
            stp_list->u8playsongcounter++;
            break;
        case SONG_FAVORLIST_INSERT_PLAYLIST:
            if((stp_list->u8playsongcounter >= MAXNUM_OF_PLAY_SONG) ||(u16index >= MAXNUM_OF_FAVOR_SONG))
                return FALSE;

            for(i=stp_list->u8playsongcounter; i>0; i--)
            {
                memcpy(&(stp_list->st_play_song_list[i]),  &(stp_list->st_play_song_list[i-1]), sizeof(ST_LIST_ITEM));
            }
            memcpy(&(stp_list->st_play_song_list[0]),  &(stp_list->st_favor_song_list[u16index]), sizeof(ST_LIST_ITEM));
            stp_list->u8playsongcounter++;
            break;
        case SONG_PLAYEDLIST_INSERT_PLAYLIST:
            if((stp_list->u8playsongcounter >= MAXNUM_OF_PLAY_SONG) ||(u16index >= MAXNUM_OF_PLAYED_SONG))
                return FALSE;

            for(i=stp_list->u8playsongcounter; i>0; i--)
            {
                memcpy(&(stp_list->st_play_song_list[i]),  &(stp_list->st_play_song_list[i-1]), sizeof(ST_LIST_ITEM));
            }
            memcpy(&(stp_list->st_play_song_list[0]),  &(stp_list->st_played_song_list[u16index]), sizeof(ST_LIST_ITEM));
            stp_list->u8playsongcounter++;
            break;
        case SONG_PLAYEDLIST_TO_FAVORLIST:
            if((stp_list->u8favorsongcounter >= MAXNUM_OF_FAVOR_SONG) ||(u16index >= MAXNUM_OF_PLAYED_SONG))
                return FALSE;

            for(i=0;i<stp_list->u8favorsongcounter;i++)
            {
                if(stp_list->st_favor_song_list[i].u32Song_ID == stp_list->st_played_song_list[u16index].u32Song_ID)
                    return TRUE;
            }

            memcpy(&(stp_list->st_favor_song_list[stp_list->u8favorsongcounter]),  &(stp_list->st_played_song_list[u16index]), sizeof(ST_LIST_ITEM));
            stp_list->u8favorsongcounter++;
            break;
        case SONG_PLAYLIST_TO_FAVORLIST:
            if((stp_list->u8favorsongcounter >= MAXNUM_OF_FAVOR_SONG) ||(u16index >= MAXNUM_OF_PLAY_SONG))
                return FALSE;

            for(i=0;i<stp_list->u8favorsongcounter;i++)
            {
                if(stp_list->st_favor_song_list[i].u32Song_ID == stp_list->st_play_song_list[u16index].u32Song_ID)
                    return TRUE;
            }
            memcpy(&(stp_list->st_favor_song_list[stp_list->u8favorsongcounter]),  &(stp_list->st_play_song_list[u16index]), sizeof(ST_LIST_ITEM));
            stp_list->u8favorsongcounter++;
            break;

        default:
            break;
    }
   return TRUE;
}
//----------------------------------------------------------------------------
//Remove song from list
//u32songid--Song id
//lst--list type to add
//stp_list--output list
//----------------------------------------------------------------------------
BOOLEAN MApp_RemoveSongFromList(U32 u32songid,U8 lst,ST_KTV_LIST *stp_list)
{
   U8 i,j;

    if(stp_list == NULL)
        return FALSE;

   MApp_KTV_SetPlayListModifyFlag();
   switch(lst)
   {
        case SONG_PLAYLIST:
            for(i=0;i<stp_list->u8playsongcounter;i++)
            {
                if(stp_list->st_play_song_list[i].u32Song_ID==u32songid)
                {
                    for(j=i;j<stp_list->u8playsongcounter-1;j++)
                    {
                        stp_list->st_play_song_list[j].u16Singer_ID=stp_list->st_play_song_list[j+1].u16Singer_ID;
                        MApp_Db_Str_Cpy(stp_list->st_play_song_list[j].u16SingerSting, (U16 *)stp_list->st_play_song_list[j+1].u16SingerSting);
                        stp_list->st_play_song_list[j].u32Song_ID=stp_list->st_play_song_list[j+1].u32Song_ID;
                        MApp_Db_Str_Cpy(stp_list->st_play_song_list[j].u16SongSting, (U16 *)stp_list->st_play_song_list[j+1].u16SongSting);
                    }
                    stp_list->u8playsongcounter--;
                    return TRUE;
                }
            }
            return FALSE;
        case SONG_PLAYEDLIST:
            for(i=0;i<stp_list->u8playedsongcounter;i++)
            {
                if(stp_list->st_played_song_list[i].u32Song_ID==u32songid)
                {
                    for(j=i;j<stp_list->u8playedsongcounter-1;j++)
                    {
                        stp_list->st_played_song_list[j].u16Singer_ID=stp_list->st_played_song_list[j+1].u16Singer_ID;
                        MApp_Db_Str_Cpy(stp_list->st_played_song_list[j].u16SingerSting, (U16 *)stp_list->st_played_song_list[j+1].u16SingerSting);
                        stp_list->st_played_song_list[j].u32Song_ID=stp_list->st_played_song_list[j+1].u32Song_ID;
                        MApp_Db_Str_Cpy(stp_list->st_played_song_list[j].u16SongSting, (U16 *)stp_list->st_played_song_list[j+1].u16SongSting);
                    }
                    stp_list->u8playedsongcounter--;
                    return TRUE;
                }
            }
            return FALSE;
        case SONG_FAVORLIST:
            for(i=0;i<stp_list->u8favorsongcounter;i++)
            {
                if(stp_list->st_favor_song_list[i].u32Song_ID==u32songid)
                {
                    for(j=i;j<stp_list->u8favorsongcounter-1;j++)
                    {
                        stp_list->st_favor_song_list[j].u16Singer_ID=stp_list->st_favor_song_list[j+1].u16Singer_ID;
                        MApp_Db_Str_Cpy(stp_list->st_favor_song_list[j].u16SingerSting, (U16 *)(stp_list->st_favor_song_list[j+1].u16SingerSting));
                        stp_list->st_favor_song_list[j].u32Song_ID=stp_list->st_favor_song_list[j+1].u32Song_ID;
                        MApp_Db_Str_Cpy(stp_list->st_favor_song_list[j].u16SongSting, (U16 *)(stp_list->st_favor_song_list[j+1].u16SongSting));
                    }
                    stp_list->u8favorsongcounter--;
                    return TRUE;
                }
            }
            return FALSE;

   }
   return FALSE;
}
//----------------------------------------------------------------------------
//Move song position in the playlist
//@u8index --> the index in st_play_song_list
//@u8Movetype-->move up or move down
//@stp_list-->output list
//----------------------------------------------------------------------------
BOOLEAN MApp_MoveSong(U8 u8index, EN_MOVE_TYPE u8Movetype, ST_KTV_LIST *stp_list)
{
    ST_LIST_ITEM st_play_song_tmp;

    if(stp_list == NULL)
        return FALSE;

   switch(u8Movetype)
   {
        case SONG_MOVEDOWN:
            if(u8index < stp_list->u8playsongcounter - 1)
            {
                memcpy(&st_play_song_tmp,  &(stp_list->st_play_song_list[u8index]), sizeof(st_play_song_tmp));
                memcpy(&(stp_list->st_play_song_list[u8index]),  &(stp_list->st_play_song_list[u8index+1]), sizeof(st_play_song_tmp));
                memcpy(&(stp_list->st_play_song_list[u8index+1]),  &st_play_song_tmp, sizeof(st_play_song_tmp));
                return TRUE;
            }
            break;

        case SONG_MOVEUP:
            if((u8index > 0 ) && (u8index < stp_list->u8playsongcounter))
            {
                memcpy(&st_play_song_tmp,  &(stp_list->st_play_song_list[u8index-1]), sizeof(st_play_song_tmp));
                memcpy(&(stp_list->st_play_song_list[u8index-1]),  &(stp_list->st_play_song_list[u8index]), sizeof(st_play_song_tmp));
                memcpy(&(stp_list->st_play_song_list[u8index]),  &st_play_song_tmp, sizeof(st_play_song_tmp));
                return TRUE;
            }
            break;

            default:
            break;
    }
   return FALSE;
}

//----------------------------------------------------------------------------
//Play the selected song in the playlist
//@u8index --> the index in st_play_song_list
//@stp_list-->output list
//----------------------------------------------------------------------------
BOOLEAN MApp_PlayedSong(U8 u8index, ST_KTV_LIST *stp_list)
{
    U8 i;

    if((u8index > stp_list->u8playsongcounter - 1) || (stp_list == NULL))
       return FALSE;

    if( stp_list->u8playedsongcounter < MAXNUM_OF_PLAYED_SONG)
    {
        memcpy(&(stp_list->st_played_song_list[stp_list->u8playedsongcounter]),  &(stp_list->st_play_song_list[u8index]), sizeof(ST_LIST_ITEM));
        stp_list->u8playedsongcounter++;
    }
    else
    {
        for(i=0; i< stp_list->u8playedsongcounter - 1; i++)
        {
            memcpy(&(stp_list->st_played_song_list[i]),  &(stp_list->st_played_song_list[i+1]), sizeof(ST_LIST_ITEM));
        }
        memcpy(&(stp_list->st_played_song_list[stp_list->u8playedsongcounter-1]),  &(stp_list->st_play_song_list[u8index]), sizeof(ST_LIST_ITEM));
    }

    for(i=u8index; i< stp_list->u8playsongcounter - 1; i++)
    {
        memcpy(&(stp_list->st_play_song_list[i]),  &(stp_list->st_play_song_list[i+1]), sizeof(ST_LIST_ITEM));
    }
    MApp_RemoveSongFromList(stp_list->st_play_song_list[stp_list->u8playsongcounter - 1].u32Song_ID, SONG_PLAYLIST, stp_list);

   return TRUE;
}

//----------------------------------------------------------------------------
//To find wether the song is in the playlist.
//@u32SongID --> the song ID
//@stp_list--> the playlist
//----------------------------------------------------------------------------
BOOLEAN MApp_IsSonginPlaylist(U32 u32SongID, ST_KTV_LIST *stp_list)
{
    U8 i;

    if((stp_list->u8playsongcounter == 0) || (stp_list->u8playsongcounter > MAXNUM_OF_PLAY_SONG) || (stp_list == NULL))
       return FALSE;

    for(i=0; i< stp_list->u8playsongcounter; i++)
    {
        //printf("\r\n %lx  <==>  %lx", u32SongID, stp_list->st_play_song_list[i].u32Song_ID);
        if(u32SongID == stp_list->st_play_song_list[i].u32Song_ID)
        {
           return TRUE;
        }
    }

   return FALSE;
}

#endif
#undef MAPP_KTV_DBSEARCH_C
