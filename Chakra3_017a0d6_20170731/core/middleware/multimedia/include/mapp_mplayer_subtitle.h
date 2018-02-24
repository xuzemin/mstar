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

#ifndef _MAPP_MPLAYER_SUBTITLE_H
#define _MAPP_MPLAYER_SUBTITLE_H

//-------------------------------------------------------------------------------------------------
// Standard include files:
//-------------------------------------------------------------------------------------------------
#include "sysinfo.h"
#include "msAPI_Subtitle_Pub.h"

//-------------------------------------------------------------------------------------------------
// Project include files:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#ifdef MAPP_MPLAYER_SUBTITLE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#if (ENABLE_SUBTITLE_DMP)
    //external subtitle
    #define ENABLE_SUBTITLE_SMI                     1
    #define ENABLE_SUBTITLE_SUB                     1
    #define ENABLE_SUBTITLE_TXT                     1
  #if (ENABLE_EXTERNAL_BMP_SUBTITLE)
    #define ENABLE_SUBTITLE_SUBIDX                  1 // 1: enable external bmp subtitle, 0: disable
  #else
    #define ENABLE_SUBTITLE_SUBIDX                  0 // 1: enable external bmp subtitle, 0: disable
  #endif

  #if (ENABLE_INTERNAL_TS_SUBTITLE)
    #define TS_INTERNAL_SUBTITLE_PGS                0
    #define TS_INTERNAL_SUBTITLE_BMP                1
  #else
    #define TS_INTERNAL_SUBTITLE_PGS                0
    #define TS_INTERNAL_SUBTITLE_BMP                0
  #endif

  #if ( (ENABLE_INTERNAL_TS_SUBTITLE)       \
      ||(ENABLE_INTERNAL_BMP_SUBTITLE)      \
      ||(ENABLE_INTERNAL_TEXT_SUBTITLE) )
    #define ENABLE_INTERNAL_SUBTITLE                1
  #else
    #define ENABLE_INTERNAL_SUBTITLE                0
  #endif
    #define MAX_ALIVE_SUBTITLE_NUM                 10
#else //#if (ENABLE_SUBTITLE_DMP)
    #define ENABLE_SUBTITLE_SMI                     0
    #define ENABLE_SUBTITLE_SUB                     0
    #define ENABLE_SUBTITLE_TXT                     0
    #define ENABLE_SUBTITLE_SUBIDX                  0
    #define ENABLE_INTERNAL_SUBTITLE                0
    #define TS_INTERNAL_SUBTITLE_PGS                0
    #define TS_INTERNAL_SUBTITLE_BMP                0
    #define ENABLE_INTERNAL_SUBTITLE                0
#endif //#if (ENABLE_SUBTITLE_DMP)

#define ENABLE_SMALL_BUF_SUBTITLE                   1
#define ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING     1

#define ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING        1

#if (MEMORY_MAP <= MMAP_32MB) & (ENABLE_SMALL_BUF_SUBTITLE==0)
#define SUPPORT_SUBITILE_TRACK_MAX                  1   // Limited: SUPPORT_SUBITILE_TRACK_MAX <= SUPPORT_SUBITILE_TYPE_MAX
#else
#define SUPPORT_SUBITILE_TRACK_MAX                  4   // Limited: SUPPORT_SUBITILE_TRACK_MAX <= SUPPORT_SUBITILE_TYPE_MAX
#endif
#define SUPPORT_SUBITILE_TYPE_MAX                   10

#define MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT        16  // Only for ENABLE_SMALL_BUF_SUBTITLE case
#define SUBTITLE_MAX_SIZE                           512
#define END_OF_LINE_SIZE                            2


#define MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT        16
#define MAX_INTERNAL_TEXT_SUBTITLE_LEN              0x100

#define VOBSUB_PACKET_SIZE                          0x800
#define VOBSUB_PACKET_MASK                          (VOBSUB_PACKET_SIZE-1)

#define MAX_CLASS_NAME_LEN                          10
#define MAX_LANG_LEN                                5

#define SUBTITLE_PARSING_TIMEOUT                    5000
#define ONE_SUBTITLE_PARSING_TIMEOUT                100

#define SUBTITLE_CACHE_OFFSET                       2048
#define LAST_SUBTITLE_DISPLAY_TIME                  5

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define PALETTE_BUF_ADR         MemAlign((((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+MP4_SUBTITLE_BUFFER_LEN-8192), 4096)

#if (ENABLE_SUBTITLE_DMP)
#if ENABLE_SMALL_BUF_SUBTITLE
#define SUBTITLE_BUFFER_POOL_ADR        ((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))
#define SUBTITLE_BUFFER_POOL_SIZE       (MP4_SUBTITLE_BUFFER_LEN)

//for external buffer subtitle
#define SUBTITLE_READ_BUF_ADDR          SUBTITLE_BUFFER_POOL_ADR
#define SUBTITLE_READ_BUF_LEN           0x5000 //20k

#define SUBTITLE_USED_READ_BUF_ADDR     SUBTITLE_READ_BUF_ADDR
#define SUBTITLE_USED_READ_BUF_LEN      0x4000 //16k

#define SUBTITLE_RESERVE_READ_BUF_ADDR  (SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN)
#define SUBTITLE_RESERVE_READ_BUF_LEN   0x1000 //4k

#define PER_SUBTITLE_INDEX_SIZE         0x400 //1k
#define MAX_SUBTITLE_INDEX_NUM          (PER_SUBTITLE_INDEX_SIZE/4) //256
#define SUBTITLE_INDEX_BUF_ADDR         (SUBTITLE_READ_BUF_ADDR+SUBTITLE_READ_BUF_LEN)
#define SUBTITLE_INDEX_BUF_LEN          (SUPPORT_SUBITILE_TRACK_MAX*PER_SUBTITLE_INDEX_SIZE)

#define SUBTITLE_BUFFER_ADR             (SUBTITLE_INDEX_BUF_ADDR+SUBTITLE_INDEX_BUF_LEN)
#define SUBTITLE_BUFFER_SIZE            (MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT*SUBTITLE_MAX_SIZE) //8K

//for external image subtitle
#define EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_ADR     SUBTITLE_BUFFER_ADR
#define EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_SIZE    MAX(SUBTITLE_BUFFER_SIZE, VOBSUB_PACKET_SIZE)

//for internal text subtitle
#define INTERNAL_TEXT_SUBTITLE_BUFFER_ADR   (EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_ADR+EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_SIZE)
#define INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE  (MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT*MAX_INTERNAL_TEXT_SUBTITLE_LEN)

#define SUBTITLE_MEMORY_MAP_END         (INTERNAL_TEXT_SUBTITLE_BUFFER_ADR+INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE)

    #if (SUBTITLE_MEMORY_MAP_END > (SUBTITLE_BUFFER_POOL_ADR+SUBTITLE_BUFFER_POOL_SIZE))
        #error "Subtitle Memory MAP Overflow!!!"
    #endif

#else //#if ENABLE_SMALL_BUF_SUBTITLE

//for external text subtitle
#define SUBTITLE_SMALL_BUF_SHIFT        16
#define SUBTITLE_SMALL_BUF_SIZE         (1<<SUBTITLE_SMALL_BUF_SHIFT)
#define SUBTITLE_RESERVE_SIZE           4096
#define SUBTITLE_SMALL_READ_BUF_SIZE    (SUBTITLE_SMALL_BUF_SIZE + SUBTITLE_RESERVE_SIZE)
#define SUBTITLE_BUFFER_ADR             (((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)) + SUBTITLE_SMALL_READ_BUF_SIZE)
#define SUBTITLE_BUFFER_SIZE            (MP4_SUBTITLE_BUFFER_LEN - SUBTITLE_SMALL_READ_BUF_SIZE - 4096)
    #if (SUBTITLE_BUFFER_ADR > (((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+ MP4_SUBTITLE_BUFFER_LEN))
        #error "MP4_SUBTITLE_BUFFER_LEN is too small!!!"
    #endif
//for internal text subtitle
#define INTERNAL_TEXT_SUBTITLE_BUFFER_ADR       ((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))
#define INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE      SUBTITLE_SMALL_BUF_SIZE
    #if (MAX_INTERNAL_TEXT_SUBTITLE_LEN*MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT > INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE)
        #error "INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE is too small!!!"
    #endif
//for external image subtitle
#define EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_ADR     (INTERNAL_TEXT_SUBTITLE_BUFFER_ADR + INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE)
#define EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_SIZE    SUBTITLE_RESERVE_SIZE
    #if (VOBSUB_PACKET_SIZE > SUBTITLE_RESERVE_SIZE)
        #error "EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_SIZE is too small!!!"
    #endif

#define SUBTITLE_SMALL_BUF_MASK         (0xFFFFFFFF - (SUBTITLE_SMALL_BUF_SIZE-1))

#define SUBTITLE_TAG_BUFFER_PER_TRACK    (MP4_SUBTITLE_TAG_LEN/SUPPORT_SUBITILE_TRACK_MAX-1024)
#define SUBTITLE_TAG_NUM_MAX            (SUBTITLE_TAG_BUFFER_PER_TRACK/sizeof(MPlayer_Subtitle_Tag))
#define SUBTITLE_BUFFER_PER_TRACK  (SUBTITLE_BUFFER_SIZE/SUPPORT_SUBITILE_TRACK_MAX - 1024)
#define SUBTITLE_READ_BUF_LEN       SUBTITLE_SMALL_READ_BUF_SIZE
#endif //#if ENABLE_SMALL_BUF_SUBTITLE
#endif //#if (ENABLE_SUBTITLE_DMP)

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef struct
{
    U32 u32TimeStart;
    U32 u32TimeEnd;
    U32 u32SubtitlePos;
//    U32 u32Useless;
} MPlayer_Subtitle_Tag;

typedef struct
{
    U8 u8ClassName[MAX_CLASS_NAME_LEN];
    U8 u8Lang[MAX_LANG_LEN];
    U8 u8ClassLen;
    BOOLEAN bPClass;
} SMI_Subtitle_Class;

typedef struct
{
    U32 u32TrackStartFilePos; //start file position of track
} SUBIDX_Subtitle_Info;

typedef struct
{
    U32 u32TimeStart;
    U32 u32SubtitlefilePos;
} SMI_Final_Subtitle_Info;

typedef enum
{
    E_MPLAYER_SUBTITLE_SRT,
#if (ENABLE_SUBTITLE_SUBIDX)
    E_MPLAYER_SUBTITLE_SUBIDX,
#endif
    E_MPLAYER_SUBTITLE_SSA,
    E_MPLAYER_SUBTITLE_ASS,
#if (ENABLE_SUBTITLE_SMI)
    E_MPLAYER_SUBTITLE_SMI,
#endif
#if (ENABLE_SUBTITLE_TXT)
    E_MPLAYER_SUBTITLE_TMPLAYER,
    E_MPLAYER_SUBTITLE_TTXT,
    E_MPLAYER_SUBTITLE_TXT,
#endif
#if (ENABLE_SUBTITLE_SUB)
    E_MPLAYER_SUBTITLE_SUB,
    E_MPLAYER_SUBTITLE_SUBVIEWER,
    E_MPLAYER_SUBTITLE_MICRODVD,
    E_MPLAYER_SUBTITLE_SUBRIPPER,
    E_MPLAYER_SUBTITLE_DVDSUBTITLESYSTEM,
#endif
    E_MPLAYER_SUBTITLE_NUM,
    E_MPLAYER_SUBTITLE_INVALID,
} enumMPlayerSubtitleType;

typedef enum
{
    E_MPLAYER_SUBTITLE_CODING_ASC,
    E_MPLAYER_SUBTITLE_CODING_UNICODE,
    E_MPLAYER_SUBTITLE_CODING_UTF8,
    E_MPLAYER_SUBTITLE_CODING_INVALID,
} enumMplayerSubtitleCoding;

typedef enum
{
    E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK,
    E_MPLAYER_EXT_SUBTITLE_INFO_TRACK_ID,
    E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_TYPE,
    E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_CODING_TYPE,
} enumExtSutitleInfo;


typedef enum
{
    E_PARSE_INIT,
    E_PARSE_IDENTIFIER,
    E_PARSE_START_TIME,
    E_PARSE_SUB_LINE1,
    E_PARSE_SUB_LINE2,
    E_PARSE_END_TIME_LINE1,
    E_PARSE_END_TIME_LINE2,
    E_PARSE_DONE,
} enumMPlayerSubtitleParse;


typedef struct
{
    enumMPlayerSubtitleType eSubtitleType;
    enumMplayerSubtitleCoding eSubtitleCodingType;   // ASC, UTF8 or UNICODE
    U32 u32SubtitleLanguage;
    U16 u16SubtitleTagCount;
    U16 u16SubtitleTagStart;
    U16 u16SubtitleTagEnd;
#if (ENABLE_SMALL_BUF_SUBTITLE)
    FileEntry stFileEntry;
    BOOLEAN bBE2LE;
    SMI_Subtitle_Class stSMIClass;
    SMI_Final_Subtitle_Info stSMIFinalSubtitle;
    SUBIDX_Subtitle_Info stSUBIDXInfo;
#endif
} MPlayerSubtitleInfo;

typedef enum
{
    E_SUBTITLE_NOTIFY_AP_NULL                 = 0,        //
    E_SUBTITLE_NOTIFY_AP_UNICODE,   // send ap unicode subtitle
    E_SUBTITLE_NOTIFY_AP_RAWDATA,    // send ap raw data of subtitle.
    E_SUBTITLE_NOTIFY_MPLAYER,   //notify MPlayer
} enumNotifyType;

typedef void (*pfnDrawExternalSubtitle) (BOOLEAN bShowSubtitile, U32 u32TextDataAddress, U16 u16Len);

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------
//INTERFACE U8 fSubtitleTimeOutCountEn;


//-------------------------------------------------------------------------------------------------
// Extern Functions
///-------------------------------------------------------------------------------------------------
INTERFACE void MApp_MPlayer_SubtitleSetFileHandle(U8 u8FileNo);
INTERFACE void MApp_MPlayer_SubtitleSetFileInfo(FileEntry* pFileEntry);

#if (ENABLE_SMALL_BUF_SUBTITLE)
#if (ENABLE_SUBTITLE_SUBIDX)
INTERFACE void MApp_MPlayer_SubtitleSetSUBIDXFileHandle(U8 u8FileNo);
#endif
INTERFACE U32 MApp_MPlayer_Subtitle_GetSubtitle(U8 *pu8Dst, U32 u32BufSize, U32 u32SubtitlePos);
INTERFACE void MApp_MPlayer_RefreshTextSubtitleTag(U32 u32Time);
INTERFACE BOOLEAN MApp_MPlayer_EnableReloadAppositeSubtitleBuf(BOOLEAN bEnable);
INTERFACE void MApp_MPlayer_SubtitleParser_Main(U32 u32Time);
INTERFACE void MApp_MPlayer_CloseSubtitleFileHandle(void);
#endif
INTERFACE void MApp_MPlayer_SubtitleInit(void);
INTERFACE BOOLEAN MApp_MPlayer_SubtitleDeInit(void);
INTERFACE BOOLEAN MApp_MPlayer_Subtitle_Parser(enumMPlayerSubtitleType *peType, U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType);
INTERFACE U16 MApp_MPlayer_SearchSubtitleTag(U32 u32Time);
INTERFACE BOOLEAN MApp_MPlayer_GetSubtitleTag(MPlayer_Subtitle_Tag *pTag, U32 u32Time);
INTERFACE BOOLEAN MApp_MPlayer_GetSubtitleTagByIdx(MPlayer_Subtitle_Tag *pTag, U16 u16Idx);
INTERFACE void MApp_MPlayer_SetInternalSubtitle(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_MPlayer_EnableInternalSubtitle(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_MPlayer_SetSubtitleTrackID(U8 u8TrackId);
INTERFACE U32 MApp_MPlayer_GetInfo(enumExtSutitleInfo eInfo);
INTERFACE BOOLEAN MApp_MPlayer_GetSubtitleInByTrackID(U8 u8TrackId, MPlayerSubtitleInfo *pInfo);
INTERFACE void msAPI_Subtitle_Init_Queue(U32 u32Adr, U32 u32Len);
INTERFACE U32 msAPI_Subtitle_Queue_GetSDRAMAddress(U16 u16Len);
INTERFACE void MApp_TS_Subtitle_Switch2OP( void );
INTERFACE void MApp_TS_Subtitle_Switch2IP( void );
INTERFACE BOOLEAN MApp_TS_Subtitle_Display_Initial(void);
INTERFACE void msAPI_Subtitle_Init_Display(U16 u16VideoWidth, U16 u16VideoHeight);
INTERFACE void msAPI_Subtitle_DeInit(void);
INTERFACE void MApp_TS_Subtitle_Exit(void);
INTERFACE BOOLEAN msAPI_Subtitle_Decoder_Main(void);
INTERFACE U8 MApp_TS_Subtitle_Get_SubtitleOSDState(void);
INTERFACE void msAPI_Subtitle_SetPageIDs(U16 u16CPID, U16 u16APID);
INTERFACE void MApp_TS_Subtitle_SetVideoInfo(U16 u16VideoWidth, U16 u16VideoHeight);
INTERFACE void MApp_TS_Subtitle_Remove(void);
INTERFACE void MApp_TS_Subtitle_Main(U32 u32Stc);
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
INTERFACE void MApp_TS_Subtitle_SetShowStatus(BOOLEAN bShowStatus);
#endif

INTERFACE void MApp_MPlayer_Subtitle_Dinit(void);
INTERFACE BOOLEAN MApp_MPlayer_EnableMovieSubtitle(void);
INTERFACE BOOLEAN MApp_MPlayer_DisableMovieSubtitle(void);
INTERFACE BOOLEAN MApp_MPlayer_ChangeSubtitleTrack(U8 u8TrackId);
INTERFACE U16 MApp_MPlayer_QuerySubtitleNum(void);
INTERFACE U16 MApp_MPlayer_QueryCurSubtitleTrackIdx(void);
INTERFACE BOOLEAN MApp_MPlayer_CurSubtitleIsText(void);
INTERFACE BOOLEAN MApp_MPlayer_CurSubtitleIsUnicode(void);
INTERFACE void MApp_MPlayer_SetExternalSubtitleType(enumMPlayerSubtitleType eType);
INTERFACE void MApp_MPlayer_Register_Notify(enumNotifyType eNotifyAPType, pfnDrawExternalSubtitle pfnSubtitle);
INTERFACE BOOLEAN MApp_MPlayer_ExternalSubtitle_Parser(void *pSubtitleFile,void *pSubtitleSubFile);
INTERFACE void MApp_MPlayer_CheckInternalSubtitleEnabledFirst(void);
INTERFACE BOOLEAN MApp_MPlayer_CheckInternalSubtitleValid(void);
INTERFACE void  MApp_MPlayer_ExternalAndInternalTextSubtitleDraw(void);
INTERFACE BOOLEAN MApp_MPlayer_ExternalSubtitleIsEnabled(void);
INTERFACE void MApp_MPlayer_SetSubtitleDelaySteps(U32 u32Steps);
INTERFACE void MApp_MPlayer_SetSubtitleAdvanceSteps(U32 u32Steps);
INTERFACE void MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime( void );
INTERFACE BOOLEAN MApp_MPlayer_ResetAliveTextSubtitleStatus(void);
INTERFACE BOOLEAN MApp_MPlayer_GetAliveTextSubtitleTag(U32 u32Time, U8* pu8AliveSubtitleNum, MPlayer_Subtitle_Tag *pAliveSubtitles, BOOLEAN bSubtitleShownFLG);
INTERFACE U32 MApp_MPlayer_GetCurExternalSubtitleLanguage(void);
INTERFACE U32 MApp_MPlayer_GetExternalSubtitleLanguageByTrackIndex(U16 u16SubtitleTrack);
#undef INTERFACE

#endif  // _MAPP_MPLAYER_SUBTITLE_H

