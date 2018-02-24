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

#ifndef MAPP_KTV_LYRIC_H
#define MAPP_KTV_LYRIC_H

#include "datatype.h"

//*****************************************************************************
//              Defines
//*****************************************************************************
#define KTV_LYRIC_DBG(x)          //x
#define DEBUG_MIC_LYRIC         0


#define KTV_LYRIC_BUFFER_LEN    (0xF000) // 60K
#define KTV_LYRIC_TAG_LEN       (0x2000) // 8K
#define KTV_LYRIC_WORDS_LEN     (0x800)  // 2K

#define KTV_LYRIC_FILENAME_MAXLEN       60
#define KTV_LYRIC_MAX_SIZE     76

/* place all the start time after sorting in 4K buffer  */
#define KTV_LYRIC_MAX_TAG_COUNT     (KTV_LYRIC_TAG_LEN/sizeof(Music_Mic_Lyric_Tag))
#if ((UI_SKIN_SEL==UI_SKIN_1366X768X565) || (UI_SKIN_SEL==UI_SKIN_1366X768X4444) || (UI_SKIN_SEL==UI_SKIN_1440X900X565))
#define KTV_LYRIC_GW_HSIZE    1310
#define KTV_LYRIC_GW_VSIZE    340
#define KTV_LYRIC_GW_LEFT     120
#define KTV_LYRIC_GW_TOP      575
#define KTV_LYRIC_DISP_HSIZE  KTV_LYRIC_GW_HSIZE - 8
#define KTV_LYRIC_DISP_VSIZE  KTV_LYRIC_GW_VSIZE - 8
#define KTV_UI_CHAR_PER_LINE  KTV_LYRIC_DISP_HSIZE/64
#define KTV_LYRIC_SECONDLINE_OFFSET 100
#define KTV_DOWNCOUNTER_BMP     39  //E_BMP_BALL_YELLOW_BG_UP
#define KTV_DOWNCOUNTER_BMP_SIZE     56
#define KTV_DOWNCOUNTER_BMP_GAP     8
#define LYRIC_FONTHIGHT_OFFSET  21
#define LYRIC_FONT_FRAME_SIZE  3
#define LYRIC_FONT_GAP  10
/*
// TCL define
#define KTV_LYRIC_GW_HSIZE      1310
#define KTV_LYRIC_GW_VSIZE      340
#define KTV_LYRIC_GW_LEFT      120
#define KTV_LYRIC_GW_TOP      700
#define KTV_LYRIC_DISP_HSIZE      KTV_LYRIC_GW_HSIZE - 8
#define KTV_LYRIC_DISP_VSIZE      KTV_LYRIC_GW_VSIZE - 8
#define KTV_UI_CHAR_PER_LINE    KTV_LYRIC_DISP_HSIZE/64
#define KTV_LYRIC_SECONDLINE_OFFSET 200
#define KTV_DOWNCOUNTER_BMP     38 //E_BMP_BALL_YELLOW_BG_UP
#define KTV_DOWNCOUNTER_BMP_SIZE     56
#define KTV_DOWNCOUNTER_BMP_GAP     8
#define LYRIC_FONTHIGHT_OFFSET  20
#define LYRIC_FONT_FRAME_SIZE  3
#define LYRIC_FONT_GAP  10 */

#else
#define KTV_LYRIC_GW_HSIZE      1300
#define KTV_LYRIC_GW_VSIZE      333
#define KTV_LYRIC_GW_LEFT      120
#define KTV_LYRIC_GW_TOP      600
#define KTV_LYRIC_DISP_HSIZE      KTV_LYRIC_GW_HSIZE - 8
#define KTV_LYRIC_DISP_VSIZE      KTV_LYRIC_GW_VSIZE - 8
#define KTV_UI_CHAR_PER_LINE    KTV_LYRIC_DISP_HSIZE/64
#define KTV_LYRIC_SECONDLINE_OFFSET 230
#define KTV_DOWNCOUNTER_BMP     39 /*E_BMP_BALL_YELLOW_BG_UP*/
#define KTV_DOWNCOUNTER_BMP_SIZE     56
#define KTV_DOWNCOUNTER_BMP_GAP     8
#define LYRIC_FONTHIGHT_OFFSET  20
#define LYRIC_FONT_FRAME_SIZE  3
#define LYRIC_FONT_GAP  10
#endif
#define LYRIC_TIME_OFFSET  3800

//*****************************************************************************
//              Enums
//*****************************************************************************
typedef enum
{
    STATE_KTV_LYRIC_INIT,
    STATE_KTV_LYRIC_WAIT,
    STATE_KTV_LYRIC_GET_LRC_SIZE,
    STATE_KTV_LYRIC_PARSER,
    STATE_KTV_LYRIC_PLAY,
    STATE_KTV_LYRIC_PAUSE,
    STATE_KTV_LYRIC_STOP,
    STATE_KTV_LYRIC_PLAY_NEXT
} EN_KTV_LYRIC_STATE;


//*****************************************************************************
//              Data structure
//*****************************************************************************
typedef struct
{
    U32 u32Time;        // the time to show
    U16 u16LyricPos;        // the position in the lyric file
    U8 u8DisplayPos:2 ; // Which line to display. 1: the first line 2: the second line  3: the line to count down
    U8 u8BlushColor:1 ;    // 0: don't blush 1: need to blush
    U8 u8Reserved:5;
} Music_Mic_Lyric_Tag;


#ifdef MAPP_KTV_LYRIC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//*****************************************************************************
//              Global variables
//*****************************************************************************
INTERFACE U32 st_KTV_Lyric_buf_adr;
INTERFACE U32 st_KTV_Lyric_tags_adr;
INTERFACE U32 st_KTV_Lyric_words_adr;

INTERFACE U32 u32MicFileLen;
INTERFACE U32 u32LyricFileLen;
INTERFACE U32 u32LyricTotalTime;
INTERFACE EN_KTV_LYRIC_STATE enKTVLyricState;
INTERFACE U8 u8LyricFileName[KTV_LYRIC_FILENAME_MAXLEN];
INTERFACE U8 u8LyricExtFilename[5];
INTERFACE U8 au8LineSection[KTV_LYRIC_MAX_SIZE];
INTERFACE U8 u8CharNum;
INTERFACE BOOLEAN bContinuePlay;
INTERFACE BOOLEAN bCheckTime;
INTERFACE U16 u16LyricTagCount;    // the total tags of the lyric file
INTERFACE U16 u16LyricWordsCount;    // the total tags of the lyric file
INTERFACE U16 u16SongNameDisplayOffset;
INTERFACE U16 u16SingerNameDisplayOffset;
//*****************************************************************************
//              Function prototypes
//*****************************************************************************
INTERFACE BOOLEAN MApp_UiMenu_iSingOpenSubtitle(void);
INTERFACE void MApp_UiMenu_iSingCloseSubtitle(void);
INTERFACE void MApp_UiMenu_iSingDisplaySubtitle(U8 line);
INTERFACE void MApp_UiMenu_iSingDrawSubtitleChar(U8 line, U16 time);
INTERFACE void MApp_UiMenu_iSingDrawSubtitleMonitor(void);
INTERFACE void MApp_MIC_LyricInit(void);
INTERFACE U8 _MApp_KTV_GetLyric(U16 u16LyricPos, U8 *pu8Dst);
INTERFACE BOOLEAN MApp_KTV_GetDownCounterLyricTag(U32 u32Time, Music_Mic_Lyric_Tag *pLyricTag);
INTERFACE BOOLEAN MApp_KTV_GetLine1LyricTag(U32 u32Time, Music_Mic_Lyric_Tag *pLyricTag, U16 *Duringtime);
INTERFACE BOOLEAN MApp_KTV_GetLine2LyricTag(U32 u32Time, Music_Mic_Lyric_Tag *pLyricTag, U16 *Duringtime);
INTERFACE BOOLEAN MApp_MIC_Lyrics_Parser(U32 u32FileSize);

#undef INTERFACE

#endif


