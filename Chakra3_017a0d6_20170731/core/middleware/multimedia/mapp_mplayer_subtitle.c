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

#define MAPP_MPLAYER_SUBTITLE_C

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "sysinfo.h"
#include "datatype.h"
#include "ctype.h"
#include "SysInit.h"
#ifdef MSOS_TYPE_LINUX
#include "MsIRQ.h"
#include "MsOS.h"
#endif
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_MPEG_Subtitle.h"
#include "msAPI_FCtrl.h"
#include "msAPI_Timer.h"
#include "apiPNL.h"
#include "MApp_UiMediaPlayer_Define.h"
#include "mapp_mplayer.h"
#include "mapp_mplayer_subtitle.h"
#include "mapp_videoplayer.h"
#include "apiGOP.h"
#include "msAPI_DataStreamIO.h"
#include "MApp_ZUI_ACTdmp.h"
#include "mapp_digitalmedia.h"


////////////////////////////////////////////////////////////////////////////////
#if (ENABLE_DMP)
#if (ENABLE_SUBTITLE_DMP)
//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define SUBTITLE_SUBRIPPER_DBG(x)         //x
#define SUBTITLE_FILTER_DBG(x)   //x
#define SUBTITLE_DUMP_FILTER_CONTENT  0
#define SUBTITLE_RESERVE_ASCII_UTF8_END_LENGTH 3 //In UTF-8 mode, _MApp_MPlayer_GetSubtitle() will get 3bytes as an unit.
                                                 //Ex : (E8 XX XX). Which might bypass the end charactors.
                                                 //Thus we need 3 bytes to avoid above case.
#define SUBTITLE_RESERVE_UNICODE_END_LENGTH 2
#define SMALL_BUF_DBG(x)    //(x)
#define SMALL_BUF_PARSER_DBG(x)    //(x)
#define ISSPACE(ch)                     (ch == 0x20 || (ch >= 0x09 && ch <= 0x0D))
//#define ISSPACE_UNICODE(ch)             (ch == 0x2000 || ch == 0x0900 || ch == 0x0A00 || ch == 0x0B00 || ch == 0x0C00 || ch == 0x0D00)
//#define ISSPACE_UNICODE(ch)             ((LOBYTE(ch) == 0) && ((HIBYTE(ch) == 0x20) || ((HIBYTE(ch) >= 0x09) && (HIBYTE(ch) <= 0x0D))))
//#define ISDIGIT_UNICODE(ch)             ((LOBYTE(ch) == 0) && (HIBYTE(ch) >= '0') && (HIBYTE(ch) <= '9'))
//#define ISHEX_UNICODE(ch)               ((LOBYTE(ch) == 0) && (((HIBYTE(ch) >= '0') && (HIBYTE(ch) <= '9')) || ((HIBYTE(ch) >= 'a') && (HIBYTE(ch) <= 'f'))))

#define ISSPACE_UNICODE(ch)             ((HIBYTE(ch) == 0) && ((LOBYTE(ch) == 0x20) || ((LOBYTE(ch) >= 0x09) && (LOBYTE(ch) <= 0x0D))))
#define ISDIGIT_UNICODE(ch)             ((HIBYTE(ch) == 0) && (LOBYTE(ch) >= '0') && (LOBYTE(ch) <= '9'))
#define ISHEX_UNICODE(ch)               ((HIBYTE(ch) == 0) && (((LOBYTE(ch) >= '0') && (LOBYTE(ch) <= '9')) || ((LOBYTE(ch) >= 'a') && (LOBYTE(ch) <= 'f'))))


#define SUBTITLE_SKIP_SPACE(ch, idx, size)                          \
        {                                                           \
            for(;idx<size;idx++)                                    \
            {                                                       \
                if(!ISSPACE(ch[idx]))                               \
                {                                                   \
                    break;                                          \
                }                                                   \
            }                                                       \
        }

#define SUBTITLE_SKIP_ONELINEFEED(ch, idx, size)                    \
        {                                                           \
            for(;idx<size;idx++)                                    \
            {                                                       \
                if(ch[idx]=='\r' || ch[idx]=='\n')                  \
                {                                                   \
                    idx++;                                          \
                    break;                                          \
                }                                                   \
            }                                                       \
            if(ch[idx]=='\r' || ch[idx]=='\n')                      \
            {                                                       \
                idx++;                                              \
            }                                                       \
        }

#define SUBTITLE_FIND_DIGIT(ch, idx, size)                          \
        {                                                           \
            for(;idx<size;idx++)                                    \
            {                                                       \
                if(ch[idx] >= '0' && ch[idx] <= '9')                \
                {                                                   \
                    break;                                          \
                }                                                   \
            }                                                       \
        }


#define SUBTITLE_FIND_NEXTLINE(ch, idx, size)                       \
        {                                                           \
            for(;idx<size;idx++)                                    \
            {                                                       \
                if(ch[idx] == 0x0D || ch[idx] == 0x0A)              \
                {                                                   \
                    for(;idx<size;idx++)                            \
                    {                                               \
                        if(ch[idx] != 0x0D && ch[idx] != 0x0A)      \
                        {                                           \
                            break;                                  \
                        }                                           \
                    }                                               \
                    break;                                          \
                }                                                   \
            }                                                       \
        }

#define SUBTITLE_SKIP_SPACE_UNICODE(ch, idx, size)                  \
        {                                                           \
            for(;idx<size;idx++)                                    \
            {                                                       \
                if(!ISSPACE_UNICODE(ch[idx]))                       \
                {                                                   \
                    break;                                          \
                }                                                   \
            }                                                       \
        }

#define SUBTITLE_SKIP_ONELINEFEED_UNICODE(ch, idx, size)            \
        {                                                           \
            for(;idx<size;idx++)                                    \
            {                                                       \
                if(ch[idx]==0x000D || ch[idx]==0x000A)              \
                {                                                   \
                    idx++;                                          \
                    break;                                          \
                }                                                   \
            }                                                       \
            if(ch[idx]==0x000D || ch[idx]==0x000A)                  \
            {                                                       \
                idx++;                                              \
            }                                                       \
        }


#define SUBTITLE_FIND_DIGIT_UNICODE(ch, idx, size)                  \
        {                                                           \
            for(;idx<(size);idx++)                                  \
            {                                                       \
                if(ISDIGIT_UNICODE(ch[idx]))                        \
                {                                                   \
                    break;                                          \
                }                                                   \
            }                                                       \
        }

#define SUBTITLE_FIND_NEXTLINE_UNICODE(ch, idx, size)               \
        {                                                           \
            for(;idx<size;idx++)                                    \
            {                                                       \
                if(ch[idx] == 0x000D || ch[idx] == 0x000A)          \
                {                                                   \
                    for(;idx<size;idx++)                            \
                    {                                               \
                        if(ch[idx] != 0x000D && ch[idx] != 0x000A)  \
                        {                                           \
                            break;                                  \
                        }                                           \
                    }                                               \
                    break;                                          \
                }                                                   \
            }                                                       \
        }

//-------------------------------------------------------------------------------------------------
// Data Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_SUBTITLE_FLG_NULL                 = 0,        //
    E_SUBTITLE_FLG_SUBTITLE_INITED            = BIT0,   // Need to do some initialization for media file.
    E_SUBTITLE_FLG_SUBTITLE_ENABLE      = BIT1,    // subtitle is enabled by users.
    E_SUBTITLE_FLG_SUBTITLE_VALID       = BIT2,    // subtitle is valid.
    E_SUBTITLE_FLG_SUBTITLE_SHOWN       = BIT3,   // Has shown the subtitle.
    E_SUBTITLE_FLG_SUBTITLE_EXTERNAL    = BIT4,   // Subtitle is external.
    E_SUBTITLE_FLG_HIDE_SUBTITLE        = BIT5,   // Hide or show subtitle.
    E_SUBTITLE_FLG_INTL_SUBTITLE_FIRST   = BIT6,// Specify internal subtitle has higher priority.
} enumSubtitleFlags;

typedef enum
{
    E_PARSE_ONE_SUBTITLE_DONE=0,
    E_PARSE_ONE_SUBTITLE_FAIL,
    E_PARSE_ONE_SUBTITLE_FILE_END,
    E_PARSE_ONE_SUBTITLE_TIME_OUT,
} EN_PARSE_ONE_SUBTITLE_RET;

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
static U16 m_u16SubtitleTagCount;
static BOOLEAN m_bInternalSubtitle;
static U8 m_u8SubtitleTrackNum;
static U8 m_u8CurTrackIdx;
static U32 m_u32PreMovieTimer = 0;
static S32 m_s32PreSubtitleIdx = -1;
static S32 m_s32DeadSubtitleIdx = -1;
static MPlayerSubtitleInfo m_MPlayerSubtitleInfo[SUPPORT_SUBITILE_TYPE_MAX];
static U32 m_u32CurSubtitleFilePos;
static U8  m_u8FileNo;
static FileEntry FileEntrySubtitle;
#if (ENABLE_SMALL_BUF_SUBTITLE)
static U32 m_u32SubtitleBufParsed = 0;
static MPlayer_Subtitle_Tag m_astExternalTextSubtitleTag[MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT];
static U16 m_u16SubtitleEndPos = 0;
static U16 m_u16SubtitleTagCnt = 0;
static BOOLEAN m_bIsReadBufferEmpty = TRUE;
#if (ENABLE_SUBTITLE_SUBIDX)
static U8 m_u8ExternalSubtitleFileHandle=FCTRL_INVALID_FILE_HANDLE; //SUBIDX sub file handle
#endif
#endif
extern U16 MApp_Transfer2Unicode(U16 u16Code);
static enumMPlayerSubtitleType m_eType;
static BOOLEAN m_bIsUnicode;
static BOOLEAN _bGOP2OP = FALSE;
static U32 m_u32SubtitleDelaySteps = 0;
static U32 m_u32SubtitleAdvanceSteps = 0;
#if (ENABLE_SUBTITLE_SUB)
static U32 m_u32MicroDVDFrameRate = 0;
#endif

//sync the order of astSubtitle and enumMPlayerSubtitleType
static const char *_gSubtitleName[E_MPLAYER_SUBTITLE_INVALID+1] =
{
    "SRT",
#if (ENABLE_SUBTITLE_SUBIDX)
    "SUBIDX",
#endif
    "SSA",
    "ASS",
#if (ENABLE_SUBTITLE_SMI)
    "SMI",
#endif
#if (ENABLE_SUBTITLE_TXT)
    "TMPLAYER",
    "TTXT",
#endif
#if (ENABLE_SUBTITLE_SUB)
    "SUB",
    "SUBVIEWER",
    "MICRODVD",
    "DVDSUBTITLESYSTEM",
#endif
    "NUM",
    "INVALID",
};

#if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
int _MApp_MPlayer_SubtitleTagCompare( const void *a, const void *b)
{
    int Tag1 = ((MPlayer_Subtitle_Tag*)a)->u32TimeStart;
    int Tag2 = ((MPlayer_Subtitle_Tag*)b)->u32TimeStart;
    return (Tag1-Tag2);
}

void _MApp_MPlayer_SubtitleTagSort(MPlayer_Subtitle_Tag  *pSubtitleTag,  S32  s32Num)
{
   S32  i,  j;
   MPlayer_Subtitle_Tag Tag;

   for  (i=1; i<s32Num; i++)
   {
       Tag=*(pSubtitleTag+i);

       for  (j=i-1; j>=0 && (Tag.u32TimeStart < (pSubtitleTag+j)->u32TimeStart); j--)
       {
           *(pSubtitleTag+j+1)  =  *(pSubtitleTag+j);
       }

       *(pSubtitleTag+j+1)  =  Tag;
   }
}
#endif

static U8  _u8OriGWId;
static U16 _u16OriX0, _u16OriY0, _u16OriX1, _u16OriY1;
static BOOLEAN  _bSubtitleOn        = FALSE;
static U16      _u16_video_width    = 0;
static U16      _u16_video_height   = 0;

//for external subtitle
static enumSubtitleFlags  eSubtitleFlag = E_SUBTITLE_FLG_NULL;
static MPlayer_Subtitle_Tag m_Subtitle_Tag;
static enumMPlayerSubtitleType m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
static enumMplayerSubtitleCoding m_eSubtitleCodingType;

#if (ENABLE_SUBTITLE_SUBIDX)
static U16 m_u16ExternalSubtitleIdx=0;
static U32 m_u32NextExternalSubtitleStartTime=0;
#endif
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
static BOOLEAN m_bShowTsSubtitle   = FALSE;
#endif

static U32 m_u32PlayCheckTime;
static U32 m_u32LyricSubtitleCurTime;
static U32 m_u32CurSubtitlePos;
static U32 u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB = INVALID_DATA_STREAM_HDL;
static enumNotifyType _geNotifyAP = E_SUBTITLE_NOTIFY_AP_NULL;
static pfnDrawExternalSubtitle _gfnSubtitle = NULL;
static U8* _gpu8RenderTextData = NULL;
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
extern U8 u8IsFontTableReady;
#endif

//*****************************************************************************
//              Local Functions Prototype
//*****************************************************************************
static BOOLEAN _MApp_MPlayer_UnicodeBE2UnicodeLE(void *pBufferAddr, U32 u32Len);

//-------------------------------------------------------------------------------------------------
// Function Implementation

//******************************************************************************
/// Filter any char between start pattern and end pattern(including)
/// ex: pu8Data is '1<234>5' start pattern is < and end pattern is > will change pu8Data to '15'
/// if find <br>/r/n will remove /r/n
/// @param  pu8Data \b IN  Specify buffer pointer.
/// @param  u16Len \b IN  buffer pointer length
/// @param  pu8FilterStartData \b IN  filter start pattern
/// @param  u8FilterStartLen \b IN  length of pu8FilterStartData
/// @param  pu8FilterEndData \b IN  filter end pattern
/// @param  u8FilterEndLen \b IN  length of pu8FilterEndData
/// @param  bUniCode \b IN  True if unicode, false if non-unicode
/// @return how many char replaced
//******************************************************************************
//-------------------------------------------------------------------------------------------------
static U16 _MApp_MPlayer_SubtitleDataFilter(U8 *pu8Data, U16 u16Len, const char* pu8FilterStartData, U8 u8FilterStartLen, const char* pu8FilterEndData, U8 u8FilterEndLen, BOOLEAN bUniCode)
{
    U16 u16FilterStartPosition = 0, u16FilterEndPosition = 0;
    U8 *pu8OriStringData = NULL;
    U16 i = 0, u16SrcDataPosition = 0, u16DesDataPosition = 0, u16FilterSize = 0, u16OffsetSize = 0;
    BOOL bCheckStart = TRUE;

    SUBTITLE_FILTER_DBG(printf("u16Len:%d\n",u16Len));

    if(pu8Data==NULL)
    {
        SUBTITLE_FILTER_DBG(printf("pu8Data is NULL\n"));
        return 0;
    }

    if(u16Len>0 && u16Len > u8FilterStartLen && u16Len > u8FilterEndLen)
    {
        pu8OriStringData = (U8 *) msAPI_Memory_Allocate(u16Len*sizeof(U8),BUF_ID_FILEBROWER);
        if(pu8OriStringData == NULL)
        {
            SUBTITLE_FILTER_DBG(printf("Filter fail!\n"));
            return 0;
        }

        memcpy(pu8OriStringData,pu8Data,u16Len);

        for(i=0;i<u16Len;i++)
        {
            if(bCheckStart)
            {
                if(i+u8FilterStartLen>=u16Len)
                {
                    break;
                }

                if(memcmp((const char*)&pu8OriStringData[i],pu8FilterStartData,u8FilterStartLen)==0)  //Check start
                {
                    if(bUniCode == TRUE)
                    {
                        BOOLEAN bFilterEndDataMatch = FALSE;

                        if(memcmp((const char*)&pu8OriStringData[i+6],pu8FilterEndData,u8FilterEndLen)==0)
                        {
                            bFilterEndDataMatch = TRUE;
                        }
                        else
                        {
                            bFilterEndDataMatch = FALSE;
                        }

                        if((pu8OriStringData[i+2]=='b') && (pu8OriStringData[i+4]=='r') &&(bFilterEndDataMatch==TRUE))
                        {
                            i += 8;  // <\0b\0r\0>\0
                            u16OffsetSize = (i-u16SrcDataPosition);
                            memcpy(pu8Data+u16DesDataPosition,pu8OriStringData+u16SrcDataPosition,u16OffsetSize);
                            u16SrcDataPosition += u16OffsetSize;
                            u16DesDataPosition += u16OffsetSize;

                            if((pu8OriStringData[i]=='\r') && (pu8OriStringData[i+2]=='\n'))
                            {
                                i += 4;
                                u16SrcDataPosition += 4;
                                u16FilterSize +=4;
                            }
                            i--; //for loop will do i++;
                            continue;
                        }
                        else if((pu8OriStringData[i+2]=='B') && (pu8OriStringData[i+4]=='R') &&(bFilterEndDataMatch==TRUE))
                        {
                            i += 8;  // <\0b\0r\0>\0
                            u16OffsetSize = (i-u16SrcDataPosition);
                            memcpy(pu8Data+u16DesDataPosition,pu8OriStringData+u16SrcDataPosition,u16OffsetSize);
                            u16SrcDataPosition += u16OffsetSize;
                            u16DesDataPosition += u16OffsetSize;

                            if((pu8OriStringData[i]=='\r') && (pu8OriStringData[i+2]=='\n'))
                            {
                                i += 4;
                                u16SrcDataPosition += 4;
                                u16FilterSize +=4;
                            }
                            i--; //for loop will do i++;
                            continue;
                        }
                        else if(bFilterEndDataMatch==FALSE)
                        {
                            i = i+8;
                            continue;
                        }
                    }
                    else
                    {
                        BOOLEAN bFilterEndDataMatch = FALSE;
                        if(memcmp((const char*)&pu8OriStringData[i+3],pu8FilterEndData,u8FilterEndLen)==0)
                        {
                            bFilterEndDataMatch = TRUE;
                        }
                        else
                        {
                            bFilterEndDataMatch = FALSE;
                        }

                        if((pu8OriStringData[i+1]=='b') && (pu8OriStringData[i+2]=='r') &&(bFilterEndDataMatch==TRUE))
                        {
                            i += 4; // <br>
                            u16OffsetSize = (i-u16SrcDataPosition);
                            memcpy(pu8Data+u16DesDataPosition,pu8OriStringData+u16SrcDataPosition,u16OffsetSize);
                            u16SrcDataPosition += u16OffsetSize;
                            u16DesDataPosition += u16OffsetSize;
                            if((pu8OriStringData[i]=='\r') && (pu8OriStringData[i+1]=='\n'))
                            {
                                i += 2;
                                u16SrcDataPosition += 2;
                                u16FilterSize +=2;
                            }
                            i--; //for loop will do i++;
                            continue;
                        }
                        else if((pu8OriStringData[i+1]=='B') && (pu8OriStringData[i+2]=='R')&&(bFilterEndDataMatch==TRUE))
                        {
                            i += 4; // <br>
                            u16OffsetSize = (i-u16SrcDataPosition);
                            memcpy(pu8Data+u16DesDataPosition,pu8OriStringData+u16SrcDataPosition,u16OffsetSize);
                            u16SrcDataPosition += u16OffsetSize;
                            u16DesDataPosition += u16OffsetSize;
                            if((pu8OriStringData[i]=='\r') && (pu8OriStringData[i+1]=='\n'))
                            {
                                i += 2;
                                u16SrcDataPosition += 2;
                                u16FilterSize +=2;
                            }
                            i--; //for loop will do i++;
                            continue;
                        }
                        else if(bFilterEndDataMatch==FALSE)
                        {
                            i = i+4;
                            continue;
                        }
                    }

                    bCheckStart = FALSE;
                    u16FilterStartPosition = i;
                    u16OffsetSize = (i-u16SrcDataPosition);
                    if( u16OffsetSize>0 )
                    {
                        memcpy(pu8Data+u16DesDataPosition,pu8OriStringData+u16SrcDataPosition,(i-u16SrcDataPosition));
                        //printf("A: memcpy u16DesDataPosition:0x%x u16SrcDataPosition:0x%x size:0x%x\n",u16DesDataPosition,u16SrcDataPosition,u16OffsetSize);
                        u16SrcDataPosition += u16OffsetSize;
                        u16DesDataPosition += u16OffsetSize;
                    }
                }
            }
            else
            {
                if(i+u8FilterEndLen>=u16Len)
                {
                    break;
                }

                if(memcmp((const char*)&pu8OriStringData[i],pu8FilterEndData,u8FilterEndLen)==0)
                {
                    bCheckStart = TRUE;
                    u16OffsetSize = (i+u8FilterEndLen);
                    u16FilterEndPosition = u16OffsetSize-1;
                    u16SrcDataPosition = u16OffsetSize;
                    u16FilterSize += (u16FilterEndPosition-u16FilterStartPosition+1);
                    //printf("u16FilterStartPosition:0x%x u8FilterEndPosition:0x%x\n",u16FilterStartPosition,u16FilterEndPosition);
                }
            }

            if(bUniCode)
            {
                i++;
            }
        }//end of for loop

        if(u16SrcDataPosition < u16Len)
        {
            memcpy(pu8Data+u16DesDataPosition,pu8OriStringData+u16SrcDataPosition,(u16Len-u16SrcDataPosition));
            //printf("B: memcpy u16DesDataPosition:0x%x u16SrcDataPosition:0x%x size:0x%x\n",u16DesDataPosition,u16SrcDataPosition,(u16Len-u16SrcDataPosition));
        }

#if SUBTITLE_DUMP_FILTER_CONTENT //for debug
        printf("SRC:");
        for(i=0;i<u16Len;i++)
        {
            printf("%c ",pu8OriStringData[i]);
        }

        printf("\nDES:");
        for(i=0;i<(u16Len-u16FilterSize);i++)
        {
            printf("%c ",pu8Data[i]);
        }

        printf("\n0:0x%x 1:0x%x\n\n",u16Len,u16FilterSize);
#endif
        free(pu8OriStringData);
    }
    SUBTITLE_FILTER_DBG(printf("u16FilterSize:%d\n",u16FilterSize));
    return u16FilterSize;
}

//-------------------------------------------------------------------------------------------------
static U16 _MApp_MPlayer_ScanDigit(U8 *pu8Data, U32 *pu32Val)
{
    U16 u16Index;

    pu32Val[0] = 0;
    for(u16Index=0;
        pu8Data[u16Index] >= '0' && pu8Data[u16Index] <= '9';
        u16Index++)
    {
        pu32Val[0] = pu32Val[0] * 10 + (U32)(pu8Data[u16Index] - '0');
    }
    return u16Index;
}

//******************************************************************************
/// Scan MilliSecond from target buffer.
/// ex:20.1 , you should input '1' , the we will return 100 miliseconds
/// ex:20.12 , you should input '12' , the we will return 120 miliseconds
/// ex:20.123 , you should input '123' , the we will return 123 miliseconds
/// ex:20.1234 , you should input '1234' , the we will return 123 miliseconds , because '4' is smaller milisecond , we will not check it
/// @param  pu8Data \b IN  Specify buffer pointer.
/// @param  pu32Val \b OUT  Specify MilliSecond.
/// @return TRUE or FALSE
//******************************************************************************
static U16 _MApp_MPlayer_ScanMilliSecond(U8 *pu8Data, U32 *pu32Val)
{
    #define HUNDRED_DIGIT 3

    U32 au32Factor[HUNDRED_DIGIT] = {100, 10, 1}; //hundred-digit, ten-digit, Single-digit
    U8 u8Count;

    *pu32Val = 0;
    for(u8Count=0; u8Count<HUNDRED_DIGIT; u8Count++)
    {
        if(pu8Data[u8Count] >= '0' && pu8Data[u8Count] <= '9')
        {
            *pu32Val += (((U32)(pu8Data[u8Count] - '0'))*au32Factor[u8Count]);
        }
        else
        {
            break;
        }
    }

    return u8Count;
}

#if (ENABLE_SUBTITLE_SUBIDX)
static U16 _MApp_MPlayer_ScanHex(U8 *pu8Data, U32 *pu32Val)
{
    U16 u16Index=0xFFFF;

    pu32Val[0] = 0;
    for(u16Index=0;;u16Index++)
    {
        if(pu8Data[u16Index] >= '0' && pu8Data[u16Index] <= '9')
        {
            pu32Val[0] = pu32Val[0] * 16 + (U32)(pu8Data[u16Index] - '0');
        }
        else if(pu8Data[u16Index] >= 'a' && pu8Data[u16Index] <= 'f')
        {
            pu32Val[0] = pu32Val[0] * 16 + (U32)(pu8Data[u16Index] - ('a' - 10));
        }
        else if(pu8Data[u16Index] >= 'A' && pu8Data[u16Index] <= 'F')
        {
            pu32Val[0] = pu32Val[0] * 16 + (U32)(pu8Data[u16Index] - ('A' - 10));
        }
        else
        {
            break;
        }
    }
    return u16Index;
}

static U32 _MApp_MPlayer_ScanfIdxPos(U8 *pu8Data)
{
    U32 u32Pos;

    if(0xFFFF != _MApp_MPlayer_ScanHex(pu8Data, &u32Pos))
    {
        return u32Pos;
    }
    return 0;
}
#endif //#if (ENABLE_SUBTITLE_SUBIDX)


#if (ENABLE_SUBTITLE_SUB)
static BOOLEAN _MApp_MPlayer_MicroDVDScanfTime(U8  *pu8Data, U32 *pu32Index, U32 *pu32Start, U32 *pu32End)
{
    U32 u32Index=0;
    U32 u32DigitCnt;
    #define SUBTITLE_CACHE_SIZE 1024

    // Scan start time
    *pu32Index = 0;
    for(u32Index=0;u32Index<(SUBTITLE_CACHE_SIZE);u32Index++)
    {
        if(pu8Data[u32Index] == '{')
            break;
    }
    u32Index++; //skip '{'
    u32DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u32Index, pu32Start);
    u32Index += u32DigitCnt;

    if(u32DigitCnt == 0 || pu8Data[u32Index] != '}' || pu8Data[u32Index+1] != '{')
    {
        return FALSE;
    }

    u32Index += 2; //skip '{';

    u32DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u32Index, pu32End);

    u32Index += u32DigitCnt;
    if(u32DigitCnt == 0 || pu8Data[u32Index] != '}')
    {
        return FALSE;
    }

    *pu32Index = u32Index+1; //skip '}'

    return TRUE;
}

//******************************************************************************
/// Get MicroDVD subtitle frame rate.
/// @param  pu8Data \b IN  Specify buffer pointer.
/// @param  pu32FrameRate \b OUT  Specify MicroDVD subtitle frame rate.
/// @return TRUE or FALSE
//******************************************************************************
static BOOLEAN _MApp_MPlayer_MicroDVDScanfFrameRate(U8 *pu8Data, U32 *pu32FrameRate)
{
    U32 u32Index=0;
    U32 u32DigitCnt;
    U32 u32Integer, u32Decimal, u32FrameRate;

    u32DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u32Index, &u32Integer);

    if(u32DigitCnt == 0)
    {
        *pu32FrameRate = 0;
        return FALSE;
    }

    u32FrameRate = u32Integer*1000;
    u32Index += u32DigitCnt;

    if(pu8Data[u32Index] == '.')
    {
        u32Index++;
        u32DigitCnt = _MApp_MPlayer_ScanMilliSecond(pu8Data+u32Index, &u32Decimal);
        u32FrameRate += u32Decimal;
        u32Index += u32DigitCnt;
    }
    *pu32FrameRate = u32FrameRate;

    return TRUE;
}

static BOOLEAN _MApp_MPlayer_SubRipperScanfTime(U8  *pu8Data, U32 *pu32Index, U32 *pu32Hour1,
                                          U32 *pu32Min1, U32 *pu32Second1,U32 *pu32ms1)
{
    U32 u32Index=0;
    U32 u32DigitCnt;

    // Scan hour1
    *pu32Index = 0;

    u32DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u32Index, pu32Hour1);
    u32Index += u32DigitCnt;
    if(u32DigitCnt == 0 || pu8Data[u32Index] != ':')
    {
        return FALSE;
    }
    u32Index++;

    // Scan min1
    u32DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u32Index, pu32Min1);
    u32Index += u32DigitCnt;
    if(u32DigitCnt == 0 || pu8Data[u32Index] != ':')
    {
        return FALSE;
    }
    u32Index++;

    // Scan sec1
    u32DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u32Index, pu32Second1);
    u32Index += u32DigitCnt;
    if(u32DigitCnt == 0 || pu8Data[u32Index] != ':')
    {
        return FALSE;
    }
    u32Index++;

    // Scan sec1
    u32DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u32Index, pu32ms1);
    u32Index += u32DigitCnt;

    *pu32Index = u32Index;

    return TRUE;
}
#endif //#if (ENABLE_SUBTITLE_SUB)


#if (ENABLE_SUBTITLE_TXT)
static U8 _MApp_MPlayer_TXTPlayerScanfTime(U8 *pu8Data, U32 *pu32Hour1,
                                          U32 *pu32Min1, U32 *pu32Second1)
{
//txt subtitle format should be : h:mm:ss:ttttttttt....
//                                h:mm:ss:
    U16 u16Index=0;
    U16 u16DigitCnt;

    // Scan hour1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data, pu32Hour1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan min1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Min1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan sec1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Second1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

static U8 _MApp_MPlayer_TMPlayerScanfTime(U8  *pu8Data,U32 *pu32Hour1,
                                          U32 *pu32Min1, U32 *pu32Second1,
                                          U8 u8Line)
{
//    #define TIME_STAMP_FMT  "%ld:%ld:%ld,%ld --> %ld:%ld:%ld,%ld"
    U16 u16Index=0;
    U16 u16DigitCnt;

    // Scan hour1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data, pu32Hour1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan min1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Min1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan sec1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Second1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ',')
    {
        return 0;
    }
    u16Index++;

    if(pu8Data[u16Index+1] == '=') //assume max 2 lines
    {
        if((pu8Data[u16Index] == '1') && (u8Line == 1))
        {
            return 1;
        }
        else if((pu8Data[u16Index] == '2') && (u8Line == 2))
        {
            return 1;
        }
    }

    return 0;
}

static U8 _MApp_MPlayer_TTXTScanfTime(U8  *pu8Data,U32 *pu32Hour1,
                                          U32 *pu32Min1, U32 *pu32Second1,U32 *pu32ms1)
{
    U16 u16Index=0;
    U16 u16DigitCnt;

    // Scan hour1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data, pu32Hour1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan min1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Min1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan sec1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Second1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != '.')
    {
        return 0;
    }
    u16Index++;

    // Scan sec1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32ms1);
    u16Index += u16DigitCnt;

    return 1;
}

#endif //#if (ENABLE_SUBTITLE_TXT)


static U8 _MApp_MPlayer_ScanfTime(U8  *pu8Data,
                                  U32 *pu32Hour1,   U32 *pu32Min1,
                                  U32 *pu32Second1, U32 *pu32ms1,
                                  U32 *pu32Hour2,   U32 *pu32Min2,
                                  U32 *pu32Second2, U32 *pu32ms2,
                                  U8  *pu8Dividor,  U8 u8Dot,
                                  U8  u8TimeStampNum)
{
//    #define TIME_STAMP_FMT  "%ld:%ld:%ld,%ld --> %ld:%ld:%ld,%ld"
    U16 u16Index=0;
    U16 u16DigitCnt;

    // Scan hour1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data, pu32Hour1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan min1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Min1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan sec1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Second1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != u8Dot)
    {
        return 0;
    }
    u16Index++;

    if((u8TimeStampNum < 2)&&(*pu8Dividor == '#'))
    {
        return 3; //for SubViewer10 [%ld:%ld:%ld]
    }

    // Scan ms1
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32ms1);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || memcmp(pu8Dividor, &pu8Data[u16Index], strlen((char*)pu8Dividor)))
    {
        return 0;
    }

    if(u8TimeStampNum < 2)
    {
        return 4;
    }
    u16Index += strlen((char*)pu8Dividor);

    // Scan hour2
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Hour2);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan min2
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Min2);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != ':')
    {
        return 0;
    }
    u16Index++;

    // Scan sec2
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32Second2);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0 || pu8Data[u16Index] != u8Dot)
    {
        return 0;
    }
    u16Index++;

    // Scan ms2
    u16DigitCnt = _MApp_MPlayer_ScanDigit(pu8Data+u16Index, pu32ms2);
    u16Index += u16DigitCnt;
    if(u16DigitCnt == 0)
    {
        return 0;
    }

    return 8;
}

#if (ENABLE_SUBTITLE_SMI)
static void _MApp_MPlayer_nupr(U8 *pu8Data, U16 u16Len)
{
    U16 i;

    for(i=0;i<u16Len;i++)
    {
        if(pu8Data[i] >= 'a' && pu8Data[i] <= 'z')
        {
            pu8Data[i] = pu8Data[i] - 'a' + 'A';
        }
    }
}

static void _MApp_MPlayer_nupr_Unicode(U8 *pu8Data, U16 u16Len)
{
    U16 i;

    for(i=0;i<u16Len;i+=2)
    {
        if(pu8Data[i] >= 'a' && pu8Data[i] <= 'z' && pu8Data[i+1] == 0)
        {
            pu8Data[i] = pu8Data[i] - 'a' + 'A';
        }
    }
}
#endif

#if (ENABLE_SUBTITLE_SUB)
//******************************************************************************
/// Sub MicroDVD decide frame rate and do it after get FrameRate called in MApp_VDPlayer_Init()
/// @param  void
/// @return void
//******************************************************************************
void MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime( void )
{
    U8 u8TrackIndex = 0;
    U16 u16TagIndex = 0;
    U32 u32FrameRate;


    if(m_u32MicroDVDFrameRate > 0)
    {
        //if frame rate > 0 , it means we can get framrate information in subtitle file , so we have to use it , refer to KMPlayer
        u32FrameRate = m_u32MicroDVDFrameRate;
    }
    else
    {
        //If frame rate = 0 , it means we can not get frame rate information in subtitle file , so we have to get frame rate information from movie file
        u32FrameRate = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAME_RATE);
    }

    if(u32FrameRate == 0)
    {
        u32FrameRate = 33000;
    }

#if (ENABLE_SMALL_BUF_SUBTITLE)
    m_u32MicroDVDFrameRate = u32FrameRate; //save actual frame rate for _MApp_MPlayer_MicroDVD_ParseOneSubtitle()
#endif

    for(u8TrackIndex = 0; u8TrackIndex < m_u8SubtitleTrackNum; ++u8TrackIndex)
    {
        if(m_MPlayerSubtitleInfo[u8TrackIndex].eSubtitleType == E_MPLAYER_SUBTITLE_MICRODVD)
        {
#if (ENABLE_SMALL_BUF_SUBTITLE)
            U32 *pu32Index = (U32 *)_PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8CurTrackIdx*PER_SUBTITLE_INDEX_SIZE);

            for(u16TagIndex = 0; u16TagIndex <= m_MPlayerSubtitleInfo[u8TrackIndex].u16SubtitleTagEnd; ++u16TagIndex)
            {
                pu32Index[u16TagIndex]= (U32)(((float)pu32Index[u16TagIndex]/u32FrameRate)*1000000);
            }
#else
            MPlayer_Subtitle_Tag *pTag;
            pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+u8TrackIndex*SUBTITLE_TAG_BUFFER_PER_TRACK);

            for(u16TagIndex = 0; u16TagIndex <= m_MPlayerSubtitleInfo[u8TrackIndex].u16SubtitleTagEnd; ++u16TagIndex)
            {
                pTag[u16TagIndex].u32TimeStart = (U32)(((float)pTag[u16TagIndex].u32TimeStart/u32FrameRate)*1000000);
                pTag[u16TagIndex].u32TimeEnd   = (U32)(((float)pTag[u16TagIndex].u32TimeEnd /u32FrameRate)*1000000);
            }
#endif //#if(ENABLE_SMALL_BUF_SUBTITLE)
        }
    }
}
#endif //ENABLE_SUBTITLE_SUB

#if (ENABLE_SMALL_BUF_SUBTITLE)
//******************************************************************************
/// compute offset which is times of read buffer(SUBTITLE_USED_READ_BUF_LEN) between subtitlte index
/// determined by filesize and index buffer size
/// @param  u32FileSize \b IN Specify file size
/// @return u32OffsetTimes times of read buffer
//******************************************************************************
static U32 _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(U32 u32FileSize)
{
    U32 u32OffsetTimes = 1;//initial value 1 of buffer size; each buffer size is SUBTITLE_USED_READ_BUF_LEN(16K)

    if(u32FileSize > SUBTITLE_USED_READ_BUF_LEN*MAX_SUBTITLE_INDEX_NUM) //16K X 256
    {
        u32OffsetTimes = (u32FileSize+MAX_SUBTITLE_INDEX_NUM-1)/MAX_SUBTITLE_INDEX_NUM;
        u32OffsetTimes = (u32OffsetTimes+SUBTITLE_USED_READ_BUF_LEN-1)/SUBTITLE_USED_READ_BUF_LEN;
    }
    return u32OffsetTimes;
}

//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SRT_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define TIME_STAMP_LEN  29

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enSRTParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32CacheParsed=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    BOOLEAN bNeedTrans2Unicode=FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_SRT_Parser_END; //not found SRT
            }

            switch(enSRTParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_USED_READ_BUF_LEN/2;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                           (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                           (LOBYTE(pu16Cache[i+2]) == ':'))
                        {
                            enSRTParse = E_PARSE_START_TIME;
                            break;
                        }
                    }

                    u32CacheParsed = i;
                    break;

                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }
                    pu8Cache[TIME_STAMP_LEN] = '\0';

                    if((_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", ',', 2) == 8)||
                       (_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", '.', 2) == 8))
                    {
                        enSRTParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enSRTParse = E_PARSE_INIT;
                    }

                    break;

                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    enSRTParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;

                if(bNeedTrans2Unicode==TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SRT_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_SRT_Parser_END; //not found SRT
            }

            switch(enSRTParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_USED_READ_BUF_LEN;i++)
                    {
                        if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                           (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                           (pu8Cache[i+2] == ':'))
                        {
                            enSRTParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    u32CacheParsed = i;

                    break;

                case E_PARSE_START_TIME:
                    if((_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", ',', 2) == 8)||
                       (_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", '.', 2) == 8))
                    {
                        enSRTParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enSRTParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    enSRTParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SRT_Parser_END;
            }
        }
    }

_MApp_MPlayer_SRT_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SRT;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_SRT_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define SUBTITLE_CACHE_SIZE     1024
    #define TIME_STAMP_LEN  29

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enSRTParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32PrevTagPos=0;
    U32 u32TagStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    U32 u32TextParseMax = 0;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 > u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SRT_Parser_END;
            }

            switch(enSRTParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_USED_READ_BUF_LEN/2;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                           (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                           (LOBYTE(pu16Cache[i+2]) == ':'))
                        {
                            enSRTParse = E_PARSE_START_TIME;
                            break;
                        }
                    }

                    u32CacheParsed = i;
                    u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                    break;

                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }
                    pu8Cache[TIME_STAMP_LEN] = '\0';

                    if((_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", ',', 2) == 8)||
                       (_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", '.', 2) == 8))
                    {
                        U32 u32CahceSize;
                        u32CacheParsed += TIME_STAMP_LEN;
                        // 3.1 Skip one line feed.
                        u32CahceSize = MIN(SUBTITLE_USED_READ_BUF_LEN/2, u32CacheParsed+ SUBTITLE_CACHE_SIZE/2);
                        SUBTITLE_SKIP_ONELINEFEED_UNICODE(pu16Cache, u32CacheParsed, u32CahceSize);
                        u32TagStart = u32CacheParsed;
                        enSRTParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enSRTParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2) - SUBTITLE_RESERVE_UNICODE_END_LENGTH;
                    for(i=u32CacheParsed;i<=u32TextParseMax;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n') &&
                           (LOBYTE(pu16Cache[i+2]) >= '\r' && LOBYTE(pu16Cache[i+3]) <= '\n'))
                        {
                            break;
                        }
                        if(LOBYTE(pu16Cache[i]) == '\n' && LOBYTE(pu16Cache[i+1]) == '\n')
                        {
                            break;
                        }
                        if ((LOBYTE(pu16Cache[i]) == '\r') && (LOBYTE(pu16Cache[i+1]) == '\n') && ((m_u32CurSubtitleFilePos+(i+2)*2) >= u32FileSize))
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i*2) >= u32FileSize)
                        {
                            break;
                        }
                    }

                    u32CacheParsed = i;
                    for(i=0; i<SUBTITLE_RESERVE_UNICODE_END_LENGTH; i++)
                    {
                        pu16Cache[u32CacheParsed + i] = '\0';
                    }

                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], ((u32CacheParsed + SUBTITLE_RESERVE_UNICODE_END_LENGTH)-u32TagStart)*2);
                    enSRTParse = E_PARSE_DONE;
                    break;

                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enSRTParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));

                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enSRTParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSRTParse = E_PARSE_INIT;
                }

                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                m_u32SubtitleBufParsed = u32CacheParsed*2;
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SRT_Parser_END;
            }
        }
    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed > u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SRT_Parser_END;
            }

            switch(enSRTParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_USED_READ_BUF_LEN;i++)
                    {
                        if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                           (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                           (pu8Cache[i+2] == ':'))
                        {
                            enSRTParse = E_PARSE_START_TIME;
                            break;
                        }
                    }

                    u32CacheParsed = i;
                    u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                    break;

                case E_PARSE_START_TIME:
                    if((_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", ',', 2) == 8)||
                       (_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", '.', 2) == 8))
                    {
                        U32 u32CahceSize;
                        u32CacheParsed += TIME_STAMP_LEN;
                        // 3.1 Skip one line feed.
                        u32CahceSize = MIN(SUBTITLE_USED_READ_BUF_LEN, u32CacheParsed+ SUBTITLE_CACHE_SIZE);
                        SUBTITLE_SKIP_ONELINEFEED(pu8Cache, u32CacheParsed, u32CahceSize);
                        u32TagStart = u32CacheParsed;
                        enSRTParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enSRTParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN) - SUBTITLE_RESERVE_ASCII_UTF8_END_LENGTH;
                    for(i=u32CacheParsed;i<=u32TextParseMax;i++)
                    {
                        if((pu8Cache[i] == '\r' && pu8Cache[i+1] == '\n') &&
                           (pu8Cache[i+2] >= '\r' && pu8Cache[i+3] <= '\n'))
                        {
                            break;
                        }
                        if(pu8Cache[i] == '\n' && pu8Cache[i+1] == '\n')
                        {
                            break;
                        }
                        if ((pu8Cache[i] == '\r') && (pu8Cache[i+1] == '\n') && ((m_u32CurSubtitleFilePos+i+2) >= u32FileSize))
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    for(i=0; i<SUBTITLE_RESERVE_ASCII_UTF8_END_LENGTH; i++)
                    {
                        pu8Cache[u32CacheParsed + i] = '\0';
                    }


                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], ((u32CacheParsed + SUBTITLE_RESERVE_ASCII_UTF8_END_LENGTH)-u32TagStart));
                    enSRTParse = E_PARSE_DONE;
                    break;

                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enSRTParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(enSRTParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSRTParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                m_u32SubtitleBufParsed = u32CacheParsed;
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SRT_Parser_END;
            }
        }
    }

_MApp_MPlayer_SRT_Parser_END:

    return eRet;
}

#if (ENABLE_SUBTITLE_SUBIDX)
//******************************************************************************
/// Set SUBIDX subtitle's sub file handle
/// @param  u8FileNo \b file handle created by SUBIDX sub file open
/// @return N/A
//******************************************************************************
void MApp_MPlayer_SubtitleSetSUBIDXFileHandle(U8 u8FileNo)
{
    m_u8ExternalSubtitleFileHandle = u8FileNo;
}

//******************************************************************************
/// Push SUBIDX one subtitle to spu queue
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @return TRUE if success, FALSE otherwise
//******************************************************************************
BOOLEAN MApp_MPlayer_PushSubtitleSUB(MPlayer_Subtitle_Tag *pSubtitleTag)
{
    #define READ_BUF_SIZE   EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_SIZE
#if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
    #define SUBIDX_READ_BUF_ADR            EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_ADR
#else
    #define SUBIDX_READ_BUF_ADR            (((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+MP4_SUBTITLE_BUFFER_LEN/2)
#endif
    U32 u32SubtitleBuff=0;
    U8 *pu8Data;
    U16 *pu16Data;
    U16 u16DataIdx;
    BOOLEAN bRet=FALSE;
    U16 u16PacketLen;
    U16 u16HeaderLen, u16CopyLen;
    U16 u16SubtitleLen, u16SubtitleLenAligned, u16SubtitleDstPos;
    U32 u32ReadBufAddr;

    u16SubtitleLen = 0;
    if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
    {
        u32ReadBufAddr = SUBIDX_READ_BUF_ADR;

        if(msAPI_FCtrl_FileSeek(m_u8ExternalSubtitleFileHandle,
                                pSubtitleTag->u32SubtitlePos,
                                FILE_SEEK_SET) == FALSE)
        {
            goto _MApp_MPlayer_PushSubtitleSUB_END;
        }
        if(0 != msAPI_FCtrl_FileRead(m_u8ExternalSubtitleFileHandle,
                                     SUBIDX_READ_BUF_ADR,
                                     READ_BUF_SIZE))
        {
            goto _MApp_MPlayer_PushSubtitleSUB_END;
        }

        // Parse subtitle.
        u16SubtitleLen = 0;
        u16SubtitleDstPos = 0;
        u16DataIdx = 0;
        pu8Data = (U8 *)_PA2VA(u32ReadBufAddr);
        pu16Data = (U16 *)_PA2VA(u32ReadBufAddr);
        do
        {
            // Process start code
            if(*(U32*)_PA2VA((u32ReadBufAddr + u16DataIdx)) != 0xBA010000)
            {
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }
            u16DataIdx += 4;

            switch(pu8Data[u16DataIdx] & 0xC0)
            {
            case 0x40:
                u16DataIdx += 10;
                break;
            case 0x20:
                u16DataIdx += 8;
                break;
            default:
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }

            if((pu16Data[u16DataIdx>>1]!=0x0000) || (pu16Data[(u16DataIdx>>1)+1]!=0xBD01))    // private stream 1
            {
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }
            u16DataIdx += 4;
//            u16PacketLen = *(U16*)((void *)&pu8Data[u16DataIdx]);
            u16PacketLen = ((pu8Data[u16DataIdx]<<8)|(pu8Data[u16DataIdx+1]));
            u16DataIdx+=2;
            if((pu8Data[u16DataIdx] & 0xC0) != 0x80)
            {
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }
            u16DataIdx += 2;
            u16HeaderLen = (U16)pu8Data[u16DataIdx];

            u16DataIdx += u16HeaderLen + 1 + 1;
            u16CopyLen = u16PacketLen - (u16HeaderLen + 4);

        #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
            if(u16SubtitleLen == 0)
            {
                // Read remain data to DRAM.
//                u16SubtitleLen = *(U16*)((void *)&pu8Data[u16DataIdx]);
                u16SubtitleLen = ((pu8Data[u16DataIdx]<<8)|(pu8Data[u16DataIdx+1]));
                if(u16SubtitleLen == 0)
                {
                    goto _MApp_MPlayer_PushSubtitleSUB_END;
                }

                u32SubtitleBuff = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(u16SubtitleLen);
                if(u32SubtitleBuff == 0)
                {
                    goto _MApp_MPlayer_PushSubtitleSUB_END;
                }

                u16SubtitleLenAligned = (u16SubtitleLen + VOBSUB_PACKET_MASK) & 0xF800;
            }
        #else
            if(u16SubtitleLen == 0)
            {
                // Read remain data to DRAM.
//                u16SubtitleLen = *(U16*)((void *)&pu8Data[u16DataIdx]);
                u16SubtitleLen = ((pu8Data[u16DataIdx]<<8)|(pu8Data[u16DataIdx+1]));

                if(u16SubtitleLen == 0)
                {
                    goto _MApp_MPlayer_PushSubtitleSUB_END;
                }
                u16SubtitleLenAligned = (u16SubtitleLen + VOBSUB_PACKET_MASK) & 0xF800;
                if(u16SubtitleLenAligned > READ_BUF_SIZE)
                {
                    if(msAPI_FCtrl_FileRead(m_u8ExternalSubtitleFileHandle,
                                            (SUBIDX_READ_BUF_ADR+READ_BUF_SIZE),
                                            u16SubtitleLenAligned-READ_BUF_SIZE) != 0)
                    {
                        goto _MApp_MPlayer_PushSubtitleSUB_END;
                    }
                }
            }
        #endif

            // Copy Subtitle to buffer.
            //msAPI_MIU_Copy((U32)(u32ReadBufAddr+u16DataIdx), (U32)(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+u16SubtitleDstPos), u16CopyLen, MIU_SDRAM2SDRAM);
        #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
            memcpy((U8 *)_PA2VA(u32SubtitleBuff+u16SubtitleDstPos), (U8 *)_PA2VA((u32ReadBufAddr+u16DataIdx)), u16CopyLen);
        #else
            memcpy((U8 *)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+u16SubtitleDstPos), (U8 *)_PA2VA((u32ReadBufAddr+u16DataIdx)), u16CopyLen);
        #endif
            u16SubtitleDstPos += u16CopyLen;
            if(u16SubtitleDstPos >= u16SubtitleLen)
            {
                break;
            }

            u16DataIdx += u16CopyLen;

            if((u16DataIdx & VOBSUB_PACKET_MASK) != 0)
            {
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }
            else if(u16DataIdx >= READ_BUF_SIZE)
            {
            #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
                if(msAPI_FCtrl_FileRead(m_u8ExternalSubtitleFileHandle,
                    SUBIDX_READ_BUF_ADR,READ_BUF_SIZE) != 0)
                    {
                        goto _MApp_MPlayer_PushSubtitleSUB_END;
                    }
                u32ReadBufAddr = SUBIDX_READ_BUF_ADR;
            #else
                u32ReadBufAddr += SUBIDX_READ_BUF_ADR;
            #endif
                u16DataIdx = 0;
                pu8Data = (U8 *)_PA2VA(u32ReadBufAddr);
                pu16Data = (U16 *)_PA2VA(u32ReadBufAddr);
            }

        } while(1);
    #if (ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE==0)
        u32SubtitleBuff = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(u16SubtitleLen);
    #endif

        if(u32SubtitleBuff >0)
        {
            //msAPI_MIU_Copy(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), u32SubtitleBuff, u16SubtitleLen, MIU_SDRAM2SDRAM);
        #if (ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE==0)
            memcpy((U8 *)_PA2VA(u32SubtitleBuff), (U8 *)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), u16SubtitleLen);
        #endif
            msAPI_MpegSP_SpuQueue_Push(E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB,  //E_SUBTITLE_VIDEO_TYPE_MPEG4,
                       u32SubtitleBuff, u16SubtitleLen, pSubtitleTag->u32TimeStart * 90, 0);
            //*pu32NextExternalSubtitleStartTime = pSubtitleTag->u32TimeStart;
        bRet = TRUE;
        }
    }
_MApp_MPlayer_PushSubtitleSUB_END:

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return TRUE if success, FALSE otherwise
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SUBIDX_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define SUBTITLE_CACHE_SIZE         1024
    #define LANGIDX_TAG                 "langidx:"
    #define DELAY_TAG                   "delay:"
    #define ID_TAG                      "id:"
    #define PALETTE_TAG                 "palette:"
    #define SIZE_TAG                    "size:"
    #define ORG_TAG                     "org:"
    #define TIMESTAMP_TAG               "timestamp:"
    #define CUSTOMER_COLOR_TAG          "custom colors:"
    #define LANGIDX_TAG_UNICODE         "l\0a\0n\0g\0i\0d\0x\0:\0"
    #define DELAY_TAG_UNICODE           "d\0e\0l\0a\0y\0:\0"
    #define ID_TAG_UNICODE              "i\0d\0:\0"
    #define PALETTE_TAG_UNICODE         "p\0a\0l\0e\0t\0t\0e\0:\0"
    #define SIZE_TAG_UNICODE            "s\0i\0z\0e\0:\0"
    #define ORG_TAG_UNICODE             "o\0r\0g\0:\0"
    #define TIMESTAMP_TAG_UNICODE       "t\0i\0m\0e\0s\0t\0a\0m\0p\0:\0"
    #define CUSTOMER_COLOR_TAG_UNICODE  "c\0u\0s\0t\0o\0m\0 \0c\0o\0l\0o\0r\0s\0:\0"
    #define SUBIDX_TIME_STAMP_LEN       13
    #define SUBIDX_TIME_LEN             9
    #define PALETTE_NUM                 16

    U16 i;
    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 u32Palette[PALETTE_NUM];
    U16 u16PaletteNum;
    U16 u16HexNum;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32CacheParsed=0;
    U32 u32ParsingTime=0;
    BOOLEAN bNeedTrans2Unicode = FALSE;
    U32 u32OffsetTimesPerIndex;
    U16 u16TagEnd=0; //keep last tag count
    enumMPlayerSubtitleParse enIdxParse = E_PARSE_IDENTIFIER;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;
    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    // Check whether it is Unicode.
    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    enIdxParse = E_PARSE_INIT;

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            switch(enIdxParse)
            {
                case E_PARSE_INIT:
                    // Find the pallete
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], PALETTE_TAG_UNICODE, sizeof(PALETTE_TAG_UNICODE)-1)==0)
                        {
                            break;
                        }
                        else if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
                        {
                            goto _MApp_MPlayer_SUBIDX_Parser_END;
                        }
                    }

                    memset(u32Palette, 0, PALETTE_NUM*sizeof(U32));
                    u16PaletteNum = 0;

                    u32CacheParsed += sizeof(PALETTE_TAG_UNICODE)/2;
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        // Convert time to ASCII.
                        for(i=0;i<SUBTITLE_CACHE_SIZE/2;i++)
                        {
                            if(ISHEX_UNICODE(pu16Cache[u32CacheParsed+i]))
                            {
                                pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                            }
                            else
                            {
                                pu8Cache[i] = '\0';
                                break;
                            }
                        }

                        u16HexNum = _MApp_MPlayer_ScanHex(&pu8Cache[0],
                                                           &u32Palette[u16PaletteNum]);
                        if(u16HexNum != 0xFFFF)
                        {
                            //printf(" palltet[%d] %lx\n", u16PaletteNum, u32Palette[u16PaletteNum]);
                            u16PaletteNum ++;
                            u32CacheParsed += u16HexNum;
                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            u32CacheParsed++;       // Skip ','
                            if(u16PaletteNum == PALETTE_NUM)
                            {
                                msAPI_MpegSP_SetPalette(u32Palette, 16);
                                u32CacheParsed = 0;
                                enIdxParse = E_PARSE_IDENTIFIER;
                                break;
                            }
                        }
                    }

                    break;

                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], ID_TAG_UNICODE, sizeof(ID_TAG_UNICODE)-1)==0)
                        {
                            // Check the language type.
                            u32CacheParsed += sizeof(ID_TAG_UNICODE)/2;

                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);

                            U32 u32TempSubtitleLang;
                            u32TempSubtitleLang = LOBYTE(pu16Cache[u32CacheParsed+1]);
                            u32TempSubtitleLang = (u32TempSubtitleLang<<8) + LOBYTE(pu16Cache[u32CacheParsed]);
                            m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = u32TempSubtitleLang;
                            m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSUBIDXInfo.u32TrackStartFilePos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart =  m_u16SubtitleTagCount; //next track start tag count
                            pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

                            enIdxParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    if(memcmp(&pu16Cache[u32CacheParsed], TIMESTAMP_TAG_UNICODE, sizeof(TIMESTAMP_TAG_UNICODE)-1) == 0)
                    {
                        u32CacheParsed += sizeof(TIMESTAMP_TAG_UNICODE)/2;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        // Convert time to ASCII.
                        for(i=0;i<SUBIDX_TIME_STAMP_LEN;i++)
                        {
                            pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                        }
                        pu8Cache[i] = '\0';
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                                    NULL, NULL, NULL, NULL,
                                                    (U8*)",", ':', 1) == 4)
                        {
                            u32CacheParsed += SUBIDX_TIME_STAMP_LEN;
                            SUBTITLE_FIND_DIGIT_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);

                            // Fill the subtitle tag.
                            if(bSubtitleFoundInBuff == FALSE)
                            {
                                pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                                SMALL_BUF_PARSER_DBG(printf("Trk%d, first Tag[%d] fpos %ld %ld %ld %ld,%ld = %ld ms\n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, m_u32CurSubtitleFilePos + u32CacheParsed*2, u32Hour1, u32Min1, u32econd1, u32ms1, pu32Index[m_u16SubtitleTagCount]));
                                u16TagEnd = m_u16SubtitleTagCount;
                            }

                            bRet = TRUE;
                            bSubtitleFoundInBuff = TRUE;
                        }
                        else
                        {
                            u32CacheParsed++;
                        }
                    }
                    else if(memcmp(&pu16Cache[u32CacheParsed], ID_TAG_UNICODE, sizeof(ID_TAG_UNICODE)-1) == 0)
                    {
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = u16TagEnd;
                        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));

                        m_u8SubtitleTrackNum++;
                        bSubtitleFoundInBuff = FALSE; //change track, find the first tag

                        if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX)
                        {
                            goto _MApp_MPlayer_SUBIDX_Parser_END;
                        }
                        // Check the language type.
                        u32CacheParsed += sizeof(ID_TAG_UNICODE)/2;

                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);

                        U32 u32TempSubtitleLang;
                        u32TempSubtitleLang = LOBYTE(pu16Cache[u32CacheParsed+1]);
                        u32TempSubtitleLang = (u32TempSubtitleLang<<8) + LOBYTE(pu16Cache[u32CacheParsed]);
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = u32TempSubtitleLang;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSUBIDXInfo.u32TrackStartFilePos = m_u32CurSubtitleFilePos + u32CacheParsed*2; //next track start file pos
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart =  m_u16SubtitleTagCount; //next track start tag count
                        pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                default:
                    break;
            }

            //over used read buffer, need to keep tag start info
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= ((U32)SUBTITLE_USED_READ_BUF_LEN*u32OffsetTimesPerIndex*(m_u16SubtitleTagCount+1)))
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    // no subtitle tag in this range
                    if(m_u16SubtitleTagCount==0)
                    {
                        pu32Index[m_u16SubtitleTagCount] = 0;
                    }
                    else
                    {
                        pu32Index[m_u16SubtitleTagCount]= pu32Index[m_u16SubtitleTagCount-1];
                    }
                    u16TagEnd = m_u16SubtitleTagCount;
                    SMALL_BUF_PARSER_DBG(printf("Trk%d, first Tag pu32Index[%d] = %d\n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                }

                bSubtitleFoundInBuff = FALSE;
                m_u16SubtitleTagCount++;

            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {   // Read the next block of data.
                m_u32CurSubtitleFilePos += u32CacheParsed*2;
                //enIdxParse = E_PARSE_START_TIME;
                //printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos);

                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SUBIDX_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            switch(enIdxParse)
            {
                case E_PARSE_INIT:
                    // Find the pallete
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], PALETTE_TAG, sizeof(PALETTE_TAG)-1)==0)
                        {
                            break;
                        }
                        else if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
                        {
                            goto _MApp_MPlayer_SUBIDX_Parser_END;
                        }
                    }

                    memset(u32Palette, 0, PALETTE_NUM*sizeof(U32));
                    u16PaletteNum = 0;

                    u32CacheParsed += sizeof(PALETTE_TAG);
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        u16HexNum = _MApp_MPlayer_ScanHex(&pu8Cache[u32CacheParsed],
                                                           &u32Palette[u16PaletteNum]);
                        if(u16HexNum != 0xFFFF)
                        {
                            //printf(" palltet[%d] %lx\n", u16PaletteNum, u32Palette[u16PaletteNum]);
                            u16PaletteNum ++;
                            u32CacheParsed += u16HexNum;
                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            u32CacheParsed++;       // Skip ','
                            if(u16PaletteNum == PALETTE_NUM)
                            {
                                msAPI_MpegSP_SetPalette(u32Palette, 16);
                                u32CacheParsed = 0;
                                enIdxParse = E_PARSE_IDENTIFIER;
                                break;
                            }
                        }
                    }
                    break;

                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], ID_TAG, sizeof(ID_TAG)-1)==0)
                        {
                            // Check the language type.
                            u32CacheParsed += sizeof(ID_TAG);

                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);

                            U32 u32TempSubtitleLang;
                            u32TempSubtitleLang = pu8Cache[u32CacheParsed+1];
                            u32TempSubtitleLang = (u32TempSubtitleLang<<8) + pu8Cache[u32CacheParsed];
                            m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = u32TempSubtitleLang;
                            m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSUBIDXInfo.u32TrackStartFilePos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart =  m_u16SubtitleTagCount; //next track start tag count
                            pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

                            enIdxParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    if(memcmp(&pu8Cache[u32CacheParsed], TIMESTAMP_TAG, sizeof(TIMESTAMP_TAG)-1) == 0)
                    {
                        u32CacheParsed += sizeof(TIMESTAMP_TAG);
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                                    NULL, NULL, NULL, NULL,
                                                    (U8*)",", ':', 1) == 4)
                        {
                            u32CacheParsed += SUBIDX_TIME_STAMP_LEN;
                            SUBTITLE_FIND_DIGIT(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);

                            // Fill the subtitle tag.
                            if(bSubtitleFoundInBuff == FALSE)
                            {
                                pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                                SMALL_BUF_PARSER_DBG(printf("Trk%d, first Tag[%d] fpos %ld %ld %ld %ld,%ld = %ldms\n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, m_u32CurSubtitleFilePos + u32CacheParsed*2, u32Hour1, u32Min1, u32econd1, u32ms1, pu32Index[m_u16SubtitleTagCount]));
                                u16TagEnd = m_u16SubtitleTagCount;
                            }

                            bRet = TRUE;
                            bSubtitleFoundInBuff = TRUE;

                        }
                        else
                        {
                            u32CacheParsed++;
                        }
                    }
                    else if(memcmp(&pu8Cache[u32CacheParsed], ID_TAG, sizeof(ID_TAG)-1) == 0)
                    {
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = u16TagEnd;
                        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));

                        m_u8SubtitleTrackNum++;
                        bSubtitleFoundInBuff = FALSE; //change track, find the first tag

                        if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX)
                        {
                            goto _MApp_MPlayer_SUBIDX_Parser_END;
                        }

                        // Check the language type.
                        u32CacheParsed += sizeof(ID_TAG);

                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);

                        U32 u32TempSubtitleLang;
                        u32TempSubtitleLang = pu8Cache[u32CacheParsed+1];
                        u32TempSubtitleLang = (u32TempSubtitleLang<<8) + pu8Cache[u32CacheParsed];
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = u32TempSubtitleLang;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSUBIDXInfo.u32TrackStartFilePos = m_u32CurSubtitleFilePos + u32CacheParsed; //next track start file pos
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart =  m_u16SubtitleTagCount; //next track start tag count
                        pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                default:
                    break;
            }

            //over used read buffer, need to keep tag start info
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= ((U32)SUBTITLE_USED_READ_BUF_LEN*u32OffsetTimesPerIndex*(m_u16SubtitleTagCount+1)))
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    // no subtitle tag in this range
                    if(m_u16SubtitleTagCount==0)
                    {
                        pu32Index[m_u16SubtitleTagCount] = 0;
                    }
                    else
                    {
                        pu32Index[m_u16SubtitleTagCount]= pu32Index[m_u16SubtitleTagCount-1];
                    }
                    u16TagEnd = m_u16SubtitleTagCount;
                    SMALL_BUF_PARSER_DBG(printf("Trk%d, first Tag pu32Index[%d] = %d\n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                }

                bSubtitleFoundInBuff = FALSE;
                m_u16SubtitleTagCount++;

            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {   // Read the next block of data.
                m_u32CurSubtitleFilePos += u32CacheParsed;
                //enIdxParse = E_PARSE_START_TIME;
                //printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos);

                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SUBIDX_Parser_END;
            }
        }
    }

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = u16TagEnd;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));

        m_u8SubtitleTrackNum++;
    }

_MApp_MPlayer_SUBIDX_Parser_END:

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_SUBIDX_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define SUBTITLE_CACHE_SIZE         1024
    #define LANGIDX_TAG                 "langidx:"
    #define DELAY_TAG                   "delay:"
    #define ID_TAG                      "id:"
    #define PALETTE_TAG                 "palette:"
    #define SIZE_TAG                    "size:"
    #define ORG_TAG                     "org:"
    #define TIMESTAMP_TAG               "timestamp:"
    #define CUSTOMER_COLOR_TAG          "custom colors:"
    #define LANGIDX_TAG_UNICODE         "l\0a\0n\0g\0i\0d\0x\0:\0"
    #define DELAY_TAG_UNICODE           "d\0e\0l\0a\0y\0:\0"
    #define ID_TAG_UNICODE              "i\0d\0:\0"
    #define PALETTE_TAG_UNICODE         "p\0a\0l\0e\0t\0t\0e\0:\0"
    #define SIZE_TAG_UNICODE            "s\0i\0z\0e\0:\0"
    #define ORG_TAG_UNICODE             "o\0r\0g\0:\0"
    #define TIMESTAMP_TAG_UNICODE       "t\0i\0m\0e\0s\0t\0a\0m\0p\0:\0"
    #define CUSTOMER_COLOR_TAG_UNICODE  "c\0u\0s\0t\0o\0m\0 \0c\0o\0l\0o\0r\0s\0:\0"
    #define SUBIDX_TIME_STAMP_LEN       13
    #define SUBIDX_TIME_LEN             9
    #define PALETTE_NUM                 16

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    U16 i;
    BOOLEAN bFindSubtitle = FALSE;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32ParsingTime=0;
    U32 u32CacheParsed=m_u32SubtitleBufParsed;
    enumMPlayerSubtitleParse enIdxParse = E_PARSE_START_TIME;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    SUBIDX_Subtitle_Info *pSUBIDXInfo = &m_MPlayerSubtitleInfo[m_u8CurTrackIdx].stSUBIDXInfo;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();


    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {

        //jump Parsed position to track start file position which is kept in u32TrackStartFilePos of SUBIDX_Subtitle_Info
        if(m_u32CurSubtitleFilePos+u32CacheParsed*2 < pSUBIDXInfo->u32TrackStartFilePos)
        {
            u32CacheParsed = pSUBIDXInfo->u32TrackStartFilePos - m_u32CurSubtitleFilePos;
        }

        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SUBIDX_Parser_END;
            }

            switch(enIdxParse)
            {
                case E_PARSE_START_TIME:
                    if(memcmp(&pu16Cache[u32CacheParsed], TIMESTAMP_TAG_UNICODE, sizeof(TIMESTAMP_TAG_UNICODE)-1) == 0)
                    {
                        u32CacheParsed += sizeof(TIMESTAMP_TAG_UNICODE)/2;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        // Convert time to ASCII.
                        for(i=0;i<SUBIDX_TIME_STAMP_LEN;i++)
                        {
                            pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                        }
                        pu8Cache[i] = '\0';
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                                    NULL, NULL, NULL, NULL,
                                                    (U8*)",", ':', 1) == 4)
                        {
                            u32CacheParsed += SUBIDX_TIME_STAMP_LEN;
                            SUBTITLE_FIND_DIGIT_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);

                            // Fill the subtitle tag.
                            pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                            pSubtitleTag->u32TimeEnd = 0xFFFFFFFF;

                            // Convert position to ASCII.
                            for(i=0;i<SUBIDX_TIME_STAMP_LEN;i++)
                            {
                                if(ISHEX_UNICODE(pu16Cache[u32CacheParsed+i]))
                                {
                                    pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                                }
                                else
                                {
                                    pu8Cache[i] = '\0';
                                    break;
                                }
                            }

                            pSubtitleTag->u32SubtitlePos = _MApp_MPlayer_ScanfIdxPos(&pu8Cache[0]);

                            SMALL_BUF_PARSER_DBG(printf("Trk%d, Tag %ld %ld %ld,%ld -> %ld\n", m_u8CurTrackIdx, u32Hour1, u32Min1, u32econd1, u32ms1, pSubtitleTag->u32SubtitlePos));

                            m_u16SubtitleTagCount++;
                            u32CacheParsed += i;

                            m_u32SubtitleBufParsed = u32CacheParsed*2;
                            bFindSubtitle = TRUE;
                            eRet = E_PARSE_ONE_SUBTITLE_DONE;
                        }
                        else
                        {
                            u32CacheParsed++;
                        }
                    }
                    else if(memcmp(&pu16Cache[u32CacheParsed], ID_TAG_UNICODE, sizeof(ID_TAG_UNICODE)-1) == 0)
                    {
                        SMALL_BUF_PARSER_DBG(printf("Trk%d: pos<%d> find next track ID and don't parser any more\n", m_u8CurTrackIdx, m_u32CurSubtitleFilePos + u32CacheParsed*2));
                        goto _MApp_MPlayer_SUBIDX_Parser_END;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {   // Read the next block of data.
                m_u32CurSubtitleFilePos += u32CacheParsed*2;
                enIdxParse = E_PARSE_START_TIME;
                //SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                m_u32SubtitleBufParsed = u32CacheParsed*2;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SUBIDX_Parser_END;
            }
        }
    }
    else
    {
        //jump Parsed position to track start file position which is kept in u32TrackStartFilePos of SUBIDX_Subtitle_Info
        if(m_u32CurSubtitleFilePos+u32CacheParsed < pSUBIDXInfo->u32TrackStartFilePos)
        {
            u32CacheParsed = pSUBIDXInfo->u32TrackStartFilePos - m_u32CurSubtitleFilePos;
        }

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SUBIDX_Parser_END;
            }

            switch(enIdxParse)
            {
                case E_PARSE_START_TIME:
                    if(memcmp(&pu8Cache[u32CacheParsed], TIMESTAMP_TAG, sizeof(TIMESTAMP_TAG)-1) == 0)
                    {
                        u32CacheParsed += sizeof(TIMESTAMP_TAG);
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                                    NULL, NULL, NULL, NULL,
                                                    (U8*)",", ':', 1) == 4)
                        {
                            u32CacheParsed += SUBIDX_TIME_STAMP_LEN;
                            SUBTITLE_FIND_DIGIT(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);

                            // Fill the subtitle tag.
                            pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                            pSubtitleTag->u32TimeEnd = 0xFFFFFFFF;

                            pSubtitleTag->u32SubtitlePos = _MApp_MPlayer_ScanfIdxPos(&pu8Cache[u32CacheParsed]);

                            SMALL_BUF_PARSER_DBG(printf("Trk%d, Tag %ld %ld %ld,%ld -> %ld\n", m_u8CurTrackIdx, u32Hour1, u32Min1, u32econd1, u32ms1, pSubtitleTag->u32SubtitlePos));

                            m_u32SubtitleBufParsed = u32CacheParsed;
                            bFindSubtitle = TRUE;
                            eRet = E_PARSE_ONE_SUBTITLE_DONE;

                        }
                        else
                        {
                            u32CacheParsed++;
                        }
                    }
                    else if(memcmp(&pu8Cache[u32CacheParsed], ID_TAG, sizeof(ID_TAG)-1) == 0)
                    {
                        SMALL_BUF_PARSER_DBG(printf("Trk%d: pos<%d> find next track ID and don't parser any more\n", m_u32CurSubtitleFilePos + u32CacheParsed));
                        goto _MApp_MPlayer_SUBIDX_Parser_END;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {   // Read the next block of data.
                m_u32CurSubtitleFilePos += u32CacheParsed;
                enIdxParse = E_PARSE_START_TIME;
                //SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                m_u32SubtitleBufParsed = u32CacheParsed;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SUBIDX_Parser_END;
            }
        }
    }

_MApp_MPlayer_SUBIDX_Parser_END:

    return eRet;
}
#endif //(ENABLE_SUBTITLE_SUBIDX)

//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SSA_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define SUBTITLE_CACHE_SIZE     1024
    #define EVENT_TAG               "[Events]"
    #define EVENT_TAG_SIZE          8
    #define DIALOGUE_HEAD           "Dialogue:"
    #define DIALOGUE_HEAD_SIZE      9
    #define EVENT_TAG_UNICODE       "[\0E\0v\0e\0n\0t\0s\0]\0"
    #define DIALOGUE_HEAD_UNICODE   "D\0i\0a\0l\0o\0g\0u\0e\0:\0"
    #define SSA_TIME_STAMP_LEN      21
    #define SKIP_COMMA_NUM          7
    #define COMMA_IN_TIMER          2
    #define SKIP_BRACE_NUM          2

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enSSAParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U32 u32CacheParsed=0;
    U32 u32ParsingTime = 0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    U32 u32SSATimeStampLen = 0, u32CommaInTime = 0, u32SSAToLineEndLen = 0;
    BOOLEAN bNeedTrans2Unicode = FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;
    U8 u8ToCheckStartTime = FALSE; //used in INIT to get start time if INIT check OK

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    enSSAParse = E_PARSE_IDENTIFIER;

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_SSA_Parser_END;//not found SSA
            }

            switch(enSSAParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(pu16Cache[u32CacheParsed] == 0x005B)    // '['
                        {
                            if(memcmp(&pu16Cache[u32CacheParsed], EVENT_TAG_UNICODE, sizeof(EVENT_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(EVENT_TAG_UNICODE)/2;
                                enSSAParse = E_PARSE_INIT;
                                break;
                            }
                        }
                    }
                    break;

                case E_PARSE_INIT:
                    u8ToCheckStartTime = FALSE;
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], DIALOGUE_HEAD_UNICODE, sizeof(DIALOGUE_HEAD_UNICODE)-1)==0)
                        {
                            u8ToCheckStartTime = TRUE;
                            u32CacheParsed += sizeof(DIALOGUE_HEAD_UNICODE)/2;
                            for(;u32CacheParsed<=(SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET)/2;u32CacheParsed++)
                            {
                                if(pu16Cache[u32CacheParsed] == 0x002C) //','
                                {
                                    u32CacheParsed++;
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    if(u8ToCheckStartTime)
                    {
                        u32SSATimeStampLen = 0;
                        u32CommaInTime = 0;
                        u32SSAToLineEndLen = 0;

                        //Check if time stamp. check leave condition: buffer size or file size
                        for(i=0;((u32CacheParsed+i) <= (SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET)/2) && (m_u32CurSubtitleFilePos + (u32CacheParsed+i)*2 < u32FileSize); i++)
                        {
                            pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                            if ((pu16Cache[u32CacheParsed+i] == 0x000D) && (pu16Cache[u32CacheParsed+i+1] == 0x000A)) //0x000D '\r', 0x000A '\n'
                            {
                                u32SSAToLineEndLen = i;
                                break;
                            }
                            if(pu8Cache[i] == ',')
                            {
                                u32CommaInTime ++;
                                if(u32CommaInTime == COMMA_IN_TIMER) //timestamp format : 0:00:01.00,0:00:30.00,
                                {
                                    u32SSATimeStampLen = i;
                                    break;
                                }
                            }
                        }
                        pu8Cache[u32SSATimeStampLen] = '\0';

                        //failed case:
                        //case 1: checking to line end   ==> jump to line end and return INIT state to find next Dialog
                        //case 2: checking to buffer end ==> leave and read more data
                        if(u32CommaInTime != COMMA_IN_TIMER)
                        {
                            SMALL_BUF_PARSER_DBG(printf("Not found!"));
                            if(u32SSAToLineEndLen!=0)
                            {
                                u32CacheParsed += u32SSAToLineEndLen;
                                enSSAParse = E_PARSE_INIT;
                            }
                            else
                            {
                                u32CacheParsed = SUBTITLE_USED_READ_BUF_LEN/2;
                             }
                        }
                        else if(_MApp_MPlayer_ScanfTime((U8*)&pu8Cache[0],
                                                    &u32Hour1, &u32Min1,
                                                    &u32econd1, &u32ms1,
                                                    &u32Hour2, &u32Min2,
                                                    &u32econd2, &u32ms2,
                                                    (U8*)",", '.', 2) == 8)
                        {
                            enSSAParse = E_PARSE_DONE;
                        }
                        else
                        {
                            u32CacheParsed += SSA_TIME_STAMP_LEN;
                            enSSAParse = E_PARSE_INIT;
                        }
                    }
                    break;

                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    enSSAParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || (u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2 && enSSAParse != E_PARSE_DONE))
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SSA_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_SSA_Parser_END;//not found SSA
            }

            switch(enSSAParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize);u32CacheParsed++)
                    {
                        if(pu8Cache[u32CacheParsed] == '[')    // '['
                        {
                            if(memcmp(&pu8Cache[u32CacheParsed], EVENT_TAG, sizeof(EVENT_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(EVENT_TAG)-1;
                                enSSAParse = E_PARSE_INIT;
                                break;
                            }
                        }
                    }
                    break;

                case E_PARSE_INIT:
                    u8ToCheckStartTime = FALSE;
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize) ;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], DIALOGUE_HEAD, sizeof(DIALOGUE_HEAD)-1)==0)
                        {
                            u8ToCheckStartTime = TRUE;
                            u32CacheParsed += sizeof(DIALOGUE_HEAD)-1;
                            for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET;u32CacheParsed++)
                            {
                                if(pu8Cache[u32CacheParsed] == ',') //','
                                {
                                    u32CacheParsed++;
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    if(u8ToCheckStartTime)
                    {
                        u32SSATimeStampLen = 0;
                        u32CommaInTime = 0;
                        u32SSAToLineEndLen = 0;
                        //Check if time stamp. check leave condition: buffer size or file size
                        for(i=0;((u32CacheParsed+i) <= SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET) && (m_u32CurSubtitleFilePos + (u32CacheParsed+i) < u32FileSize);i++)
                        {
                            if ((pu8Cache[u32CacheParsed+i] == '\r') && (pu8Cache[u32CacheParsed+i+1] == '\n'))
                            {
                                u32SSAToLineEndLen = i;
                                break;
                            }
                            if(pu8Cache[u32CacheParsed+i] == ',')
                            {
                                u32CommaInTime ++;
                                if(u32CommaInTime == COMMA_IN_TIMER) //timestamp format : 0:00:01.00,0:00:30.00,
                                {
                                    u32SSATimeStampLen = i;
                                    break;
                                }
                            }
                        }
                        //failed case:
                        //case 1: checking to line end   ==> jump to line end and return INIT state to find next Dialog
                        //case 2: checking to buffer end ==> leave and read more data
                        if(u32CommaInTime != COMMA_IN_TIMER)
                        {
                            SMALL_BUF_PARSER_DBG(printf("Not found!"));
                            if(u32SSAToLineEndLen!=0)
                            {
                                u32CacheParsed += u32SSAToLineEndLen;
                                enSSAParse = E_PARSE_INIT;
                            }
                            else
                            {
                                u32CacheParsed = SUBTITLE_USED_READ_BUF_LEN;
                            }
                        }
                        else if(_MApp_MPlayer_ScanfTime((U8*)&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1,
                                                    &u32econd1, &u32ms1,
                                                    &u32Hour2, &u32Min2,
                                                    &u32econd2, &u32ms2,
                                                    (U8*)",", '.', 2) == 8)
                        {
                            enSSAParse = E_PARSE_DONE;
                        }
                        else
                        {
                            u32CacheParsed += SSA_TIME_STAMP_LEN;
                            enSSAParse = E_PARSE_INIT;
                        }
                    }
                    break;

                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    enSSAParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || (u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN && enSSAParse != E_PARSE_DONE))
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]= pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                if(m_u16SubtitleTagCount >= MAX_SUBTITLE_INDEX_NUM)
                {   // Exceed the maximum tag number. Stop parse.
                    goto _MApp_MPlayer_SSA_Parser_END;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SSA_Parser_END;
            }
        }
    }

_MApp_MPlayer_SSA_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SSA;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_SSA_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define SUBTITLE_CACHE_SIZE     1024
    #define EVENT_TAG               "[Events]"
    #define EVENT_TAG_SIZE          8
    #define DIALOGUE_HEAD           "Dialogue:"
    #define DIALOGUE_HEAD_SIZE      9
    #define EVENT_TAG_UNICODE       "[\0E\0v\0e\0n\0t\0s\0]\0"
    #define DIALOGUE_HEAD_UNICODE   "D\0i\0a\0l\0o\0g\0u\0e\0:\0"
    #define SSA_TIME_STAMP_LEN      21
    #define SKIP_COMMA_NUM          7
    #define COMMA_IN_TIMER          2
    #define SKIP_BRACE_NUM          2

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE, bLeftBrace = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enSSAParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U32 u32PrevTagPos=0;
    U32 u32TextParseMax = 0;
    U32 u32TagStart=0;
    U32 u32ParsingTime = 0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32SSATimeStampLen = 0, u32CommaInTime = 0, u32SSAToLineEndLen = 0;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    U32 u32SubtitlePos = 0;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();

    enSSAParse = E_PARSE_INIT;

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {

            if((m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize) && (enSSAParse != E_PARSE_DONE))
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SSA_Parser_END;
            }

            switch(enSSAParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(pu16Cache[u32CacheParsed] == 0x005B)    // '['
                        {
                            if(memcmp(&pu16Cache[u32CacheParsed], EVENT_TAG_UNICODE, sizeof(EVENT_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(EVENT_TAG_UNICODE)/2;
                                enSSAParse = E_PARSE_INIT;
                                break;
                            }
                        }
                    }
                    break;

                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], DIALOGUE_HEAD_UNICODE, sizeof(DIALOGUE_HEAD_UNICODE)-1)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            enSSAParse = E_PARSE_START_TIME;
                            u32CacheParsed += sizeof(DIALOGUE_HEAD_UNICODE)/2;
                            for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                            {
                                if(pu16Cache[u32CacheParsed] == 0x002C) //','
                                {
                                    u32CacheParsed++;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    u32SSATimeStampLen = 0;
                    u32CommaInTime = 0;
                    u32SSAToLineEndLen = 0;

                    //Check if time stamp. check leave condition: buffer size or file size
                    for(i=0;((u32CacheParsed+i) <= SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + (u32CacheParsed+i)*2 < u32FileSize); i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                        if ((pu16Cache[u32CacheParsed+i] == 0x000D) && (pu16Cache[u32CacheParsed+i+1] == 0x000A)) //0x000D '\r', 0x000A '\n'
                        {
                            u32SSAToLineEndLen = i;
                            break;
                        }
                        if(pu8Cache[i] == ',')
                        {
                            u32CommaInTime ++;
                            if(u32CommaInTime == COMMA_IN_TIMER) //timestamp format : 0:00:01.00,0:00:30.00,
                            {
                                u32SSATimeStampLen = i;
                                break;
                            }
                        }
                    }
                    pu8Cache[u32SSATimeStampLen] = '\0';

                    //failed case:
                    //case 1: checking to line end   ==> jump to line end and return INIT state to find next Dialog
                    //case 2: checking to buffer end ==> leave and read more data
                    if(u32CommaInTime != COMMA_IN_TIMER)
                    {
                        SMALL_BUF_PARSER_DBG(printf("Not found!"));
                        if(u32SSAToLineEndLen!=0)
                        {//case 1
                            u32CacheParsed += u32SSAToLineEndLen;
                            enSSAParse = E_PARSE_INIT;
                        }
                        else
                        {//case 2, 3
                            u32CacheParsed += i;
                        }
                    }
                    else if(_MApp_MPlayer_ScanfTime((U8*)&pu8Cache[0],
                                                &u32Hour1, &u32Min1,
                                                &u32econd1, &u32ms1,
                                                &u32Hour2, &u32Min2,
                                                &u32econd2, &u32ms2,
                                                (U8*)",", '.', 2) == 8)
                    {

                        //jump to behind the timestamp
                        u32CacheParsed += u32SSATimeStampLen;

                        // Search the texts, skip 7 ','
                        i=0;
                        for(;i < SKIP_COMMA_NUM &&
                             u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN/2;
                             u32CacheParsed++)
                        {
                            if ((pu16Cache[u32CacheParsed] == 0x000D) && (pu16Cache[u32CacheParsed+1] == 0x000A)) //0x000D '\r', 0x000A '\n'
                            {   //this line is invalid, go INIT state to find next Dialog
                                enSSAParse = E_PARSE_INIT;
                                break;
                            }
                            if(pu16Cache[u32CacheParsed] == 0x002C)     //','
                            {
                                i++;
                            }
                        }
                        //make sure COMMA number is currect, otherwise u32CacheParsed = SUBTITLE_USED_READ_BUF_LEN
                        if(i == SKIP_COMMA_NUM)
                        {
                            u32TagStart = u32CacheParsed;
                            enSSAParse = E_PARSE_SUB_LINE1;
                        }
                    }
                    else
                    {
                        u32CacheParsed += SSA_TIME_STAMP_LEN;
                        enSSAParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                    bLeftBrace = FALSE;

                    for(;u32CacheParsed<u32TextParseMax;u32CacheParsed++)
                    {
                        if(bLeftBrace == FALSE && pu16Cache[u32CacheParsed] == 0x007B)//'{'
                        {
                            if(u32CacheParsed-u32TagStart)
                            {
                                memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], 2*(u32CacheParsed-u32TagStart));
                                u32SubtitlePos += 2*(u32CacheParsed-u32TagStart);
                                u32TagStart = u32CacheParsed;
                            }
                            bLeftBrace = TRUE;
                        }
                        else if(bLeftBrace == TRUE && pu16Cache[u32CacheParsed] == 0x007D)//'}'
                        {
                            u32TagStart = u32CacheParsed+1;
                            bLeftBrace = FALSE;
                        }
                        else if(pu16Cache[u32CacheParsed] == 0x005C)//'\\'
                        {
                            if(pu16Cache[u32CacheParsed+1] == 0x004E || pu16Cache[u32CacheParsed+1] == 0x006E)//'N','n'
                            {
                                //new line
                                pu16Cache[u32CacheParsed] = 0x000D;     //'\r'
                                pu16Cache[u32CacheParsed+1] = 0x000A;   //'\n'
                                ++u32CacheParsed;
                            }
                            else if(pu16Cache[u32CacheParsed+1] == 0x0068)
                            {
                                //0x1A ascii substitute
                                pu16Cache[u32CacheParsed] = 0x001A;    //hide
                                pu16Cache[u32CacheParsed+1] = 0x001A;  //hide
                                ++u32CacheParsed;
                            }
                        }
                        else if(pu16Cache[u32CacheParsed] == 0x000D && pu16Cache[u32CacheParsed+1] == 0x000A)
                        {
                            break;
                        }
                        if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
                        {
                            break;
                        }
                    }

                    if(u32CacheParsed < SUBTITLE_USED_READ_BUF_LEN/2)
                    {
                        pu16Cache[u32CacheParsed] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+1-u32TagStart)*2);
                        u32SubtitlePos += (u32CacheParsed+1-u32TagStart)*2;
                        enSSAParse = E_PARSE_DONE;
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enSSAParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));

                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enSSAParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSSAParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SSA_Parser_END;
            }
        }
    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if((m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize) && (enSSAParse != E_PARSE_DONE))
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SSA_Parser_END;
            }

            switch(enSSAParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize);u32CacheParsed++)
                    {
                        if(pu8Cache[u32CacheParsed] == '[')    // '['
                        {
                            if(memcmp(&pu8Cache[u32CacheParsed], EVENT_TAG, sizeof(EVENT_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(EVENT_TAG)-1;
                                enSSAParse = E_PARSE_INIT;
                                break;
                            }
                        }
                    }
                    break;

                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize) ;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], DIALOGUE_HEAD, sizeof(DIALOGUE_HEAD)-1)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            enSSAParse = E_PARSE_START_TIME;
                            u32CacheParsed += sizeof(DIALOGUE_HEAD)-1;
                            for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                            {
                                if(pu8Cache[u32CacheParsed] == ',') //','
                                {
                                    u32CacheParsed++;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    u32SSATimeStampLen = 0;
                    u32CommaInTime = 0;
                    u32SSAToLineEndLen = 0;

                    //Check if time stamp. check leave condition: buffer size or file size
                    for(i=0;((u32CacheParsed+i) <= SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + (u32CacheParsed+i) < u32FileSize);i++)
                    {
                        if ((pu8Cache[u32CacheParsed+i] == '\r') && (pu8Cache[u32CacheParsed+i+1] == '\n'))
                        {
                            u32SSAToLineEndLen = i;
                            break;
                        }
                        if(pu8Cache[u32CacheParsed+i] == ',')
                        {
                            u32CommaInTime ++;
                            if(u32CommaInTime == COMMA_IN_TIMER) //timestamp format : 0:00:01.00,0:00:30.00,
                            {
                                u32SSATimeStampLen = i;
                                break;
                            }
                        }
                    }
                    //failed case:
                    //case 1: checking to line end   ==> jump to line end and return INIT state to find next Dialog
                    //case 2: checking to buffer end ==> leave and read more data
                    //case 3: checking to file end ==> leave
                    if(u32CommaInTime != COMMA_IN_TIMER)
                    {
                        SMALL_BUF_PARSER_DBG(printf("Not found!"));
                        if(u32SSAToLineEndLen!=0)
                        {//case 1
                            u32CacheParsed += u32SSAToLineEndLen;
                            enSSAParse = E_PARSE_INIT;
                        }
                        else
                        {//case 2, 3
                            u32CacheParsed += i;
                        }
                    }
                    else if(_MApp_MPlayer_ScanfTime((U8*)&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1,
                                                &u32econd1, &u32ms1,
                                                &u32Hour2, &u32Min2,
                                                &u32econd2, &u32ms2,
                                                (U8*)",", '.', 2) == 8)
                    {
                        //jump to behind the timestamp
                        u32CacheParsed += u32SSATimeStampLen;

                        // Search the texts, skip 7 ','
                        i=0;
                        for(;i < SKIP_COMMA_NUM &&
                             u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN;
                             u32CacheParsed++)
                        {
                            if ((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
                            {   //this line is invalid, go INIT state to find next Dialog
                                enSSAParse = E_PARSE_INIT;
                                break;
                            }
                            if(pu8Cache[u32CacheParsed] == ',')     //','
                            {
                                i++;
                            }
                        }
                        //make sure COMMA number is currect, otherwise u32CacheParsed = SUBTITLE_USED_READ_BUF_LEN
                        if(i == SKIP_COMMA_NUM)
                        {
                            u32TagStart = u32CacheParsed;
                            enSSAParse = E_PARSE_SUB_LINE1;
                        }
                    }
                    else
                    {
                        u32CacheParsed += SSA_TIME_STAMP_LEN;
                        enSSAParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                    bLeftBrace = FALSE;
                    for(;u32CacheParsed<u32TextParseMax;u32CacheParsed++)
                    {
                        if(bLeftBrace == FALSE && pu8Cache[u32CacheParsed] == '{')
                        {
                            if(u32CacheParsed-u32TagStart)
                            {
                                memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], (u32CacheParsed-u32TagStart));
                                u32SubtitlePos += (u32CacheParsed-u32TagStart);
                                u32TagStart = u32CacheParsed;
                            }
                            bLeftBrace = TRUE;
                        }
                        else if(bLeftBrace == TRUE && pu8Cache[u32CacheParsed] == '}')
                        {
                            u32TagStart = u32CacheParsed+1;
                            bLeftBrace = FALSE;
                        }
                        else if(pu8Cache[u32CacheParsed] == '\\')
                        {
                            if(pu8Cache[u32CacheParsed+1] == 'n' || pu8Cache[u32CacheParsed+1] == 'N')
                            {
                                //new line
                                pu8Cache[u32CacheParsed] = '\r';
                                pu8Cache[u32CacheParsed+1] = '\n';
                                ++u32CacheParsed;
                            }
                            else if(pu8Cache[u32CacheParsed+1] == 'h')
                            {
                                //0x1A ascii substitute
                                pu8Cache[u32CacheParsed] = 26;    //hide
                                pu8Cache[u32CacheParsed+1] = 26;  //hide
                                ++u32CacheParsed;
                            }
                        }
                        else if((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
                        {
                            break;
                        }
                        if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
                        {
                            break;
                        }
                    }

                    if(u32CacheParsed < SUBTITLE_USED_READ_BUF_LEN)
                    {
                        pu8Cache[u32CacheParsed] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], (u32CacheParsed+1-u32TagStart));
                        u32SubtitlePos += (u32CacheParsed+1-u32TagStart);
                        enSSAParse = E_PARSE_DONE;
                    }
                    break;

                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enSSAParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                // Read the next block of data.
                if(enSSAParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSSAParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SSA_Parser_END;
            }
        }
    }

#if 0
    for(i=0;i<20;i++)
    {
        printf("Time = %ld, %ld, %08lx\n", pTag[i].u32TimeStart, pTag[i].u32TimeEnd, pTag[i].u32SubtitlePos);
    }
#endif

_MApp_MPlayer_SSA_Parser_END:

    return eRet;
}

#if (ENABLE_SUBTITLE_SMI)
//******************************************************************************
/// parse one subtitle information and it also needs paser second subtitle for end time
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_SMI_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define SUBTITLE_CACHE_SIZE             1024
    #define STYLE_TAG                       "<STYLE TYPE="
    #define STYLE_TAG_UNICODE               "<\0S\0T\0Y\0L\0E\0 \0T\0Y\0P\0E\0=\0"
    #define PCLASS_TAG                      "<P CLASS="
    #define PCLASS_TAG_UNICODE              "<\0P\0 \0C\0L\0A\0S\0S\0=\0"
    #define SYNC_TAG                        "<SYNC START="
    #define SYNC_TAG_UNICODE                "<\0S\0Y\0N\0C\0 \0S\0T\0A\0R\0T\0=\0"
    #define BODY_TAG                        "</BODY>"
    #define SAMI_TAG                        "</SAMI>"
    #define BODY_TAG_UNICODE                "<\0/\0B\0O\0D\0Y\0>\0"
    #define SAMI_TAG_UNICODE                "<\0/\0S\0A\0M\0I\0>\0"
    #define LANG_TAG                        "LANG:"
    #define LANG_TAG_UNICODE                "L\0A\0N\0G\0:\0"
    #define SAMI_PREPARSE_LEN               128
    #define CLASS_LEN                       64
    #define MAX_SMI_TIME_DIGIT              24
    #define FILTER_TAG                      "<"
    #define FILTER_TAG_END                  ">"
    #define FILTER_TAG_UNICODE              "<\0"
    #define FILTER_TAG_END_UNICODE          ">\0"


    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    BOOLEAN bFound = FALSE;
    U32 i;
    U32 u32TimeStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U8 u8FindSubtitleCnt=0; //number of subtitle is found
    SMI_Subtitle_Class *pClass = &m_MPlayerSubtitleInfo[m_u8CurTrackIdx].stSMIClass;
    enumMPlayerSubtitleParse enSMIParse = E_PARSE_START_TIME;
    U32 u32TagStart=0;
    U32 u32CacheParsed=m_u32SubtitleBufParsed;
    U32 u32PrevTagPos=0;
    U32 u32ParsingTime=0;
    U32 u32TextParseMax = 0;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);


    u32ParsingTime = msAPI_Timer_GetTime0();

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SMI_Parser_END;
            }

            switch(enSMIParse)
            {
                case E_PARSE_START_TIME:
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                        if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            u32CacheParsed += sizeof(SYNC_TAG_UNICODE)/2;
                            SUBTITLE_FIND_DIGIT_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            // Convert time to ASCII.
                            for(i=0;i<MAX_SMI_TIME_DIGIT/2;i++)
                            {
                                if(ISDIGIT_UNICODE(pu16Cache[u32CacheParsed+i]))
                                {
                                    pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                                }
                                else
                                {
                                    pu8Cache[i] = '\0';
                                    break;
                                }
                            }

                            i = _MApp_MPlayer_ScanDigit(&pu8Cache[0], &u32TimeStart);
                            u32CacheParsed = u32CacheParsed + i +1;
                            enSMIParse = E_PARSE_SUB_LINE1;
                            break;
                        }
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    // search PCLASS_TAG
                    bFound = FALSE;
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if(m_MPlayerSubtitleInfo[m_u8CurTrackIdx].stSMIClass.bPClass)
                        {
                            _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(PCLASS_TAG_UNICODE)-1);
                            if(memcmp(&pu16Cache[u32CacheParsed], PCLASS_TAG_UNICODE, sizeof(PCLASS_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(PCLASS_TAG_UNICODE)/2;
                                if( pClass->u8ClassLen != 0)
                                {
                                    //this data transformation is for class name check, so using with CLASS_LEN
                                    for(i=0;i<CLASS_LEN/2;i++)
                                    {
                                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                                    }
                                    //in E_PARSE_IDENTIFIER state, pClass[u8CurClassNo].u8ClassName is converted to uppercase.
                                    //We have to convert read data to uppercase by comparison with u8ClassName
                                    //_MApp_MPlayer_nupr(pClass[u8CurClassNo].u8ClassName, pClass[u8CurClassNo].u8ClassLen);
                                    _MApp_MPlayer_nupr(&pu8Cache[0], pClass->u8ClassLen);
                                    SMALL_BUF_PARSER_DBG(printf("Class name: %s\n", pClass->u8ClassName));
                                    if(memcmp(&pu8Cache[0], pClass->u8ClassName,  pClass->u8ClassLen) == 0)
                                    {
                                        //To solve the case: <P Class=ENUSCC ID=Source>The Speaker </P>
                                        //if not found the end of class name('>') in SUBTITLE_SMALL_BUF_SIZE, will read next block
                                        for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                                        {
                                            if ((pu16Cache[u32CacheParsed] == 0x000D) && (pu16Cache[u32CacheParsed+1] == 0x000A)) //0x000D '\r', 0x000A '\n'
                                            {
                                                u32TagStart = u32CacheParsed+2; //cannot find '>' until line end, this line is no subtitle
                                                u32CacheParsed = u32TagStart;
                                                break;
                                            }

                                            if(pu16Cache[u32CacheParsed] == 0x003E) //'>'
                                            {
                                                u32TagStart = u32CacheParsed+1;
                                                u32CacheParsed = u32TagStart;
                                                bFound = TRUE;
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                if((pu16Cache[u32CacheParsed] == 0x003C) &&
                                    (pu16Cache[u32CacheParsed+1]  == 0x0053) &&
                                    (pu16Cache[u32CacheParsed+2]  == 0x0059) &&
                                    (pu16Cache[u32CacheParsed+3]  == 0x004E) &&
                                    (pu16Cache[u32CacheParsed+4]  == 0x0043))
                                {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                }
                            }
                        }
                        else
                        {
                            if(pu16Cache[u32CacheParsed] == 0x003E)
                            {
                                u32TagStart = u32CacheParsed+1;
                                u32CacheParsed = u32TagStart;
                                bFound = TRUE;
                                break;
                            }
                            else
                            {
                                if((pu16Cache[u32CacheParsed] == 0x003C) &&
                                    (pu16Cache[u32CacheParsed+1]  == 0x0053) &&
                                    (pu16Cache[u32CacheParsed+2]  == 0x0059) &&
                                    (pu16Cache[u32CacheParsed+3]  == 0x004E) &&
                                    (pu16Cache[u32CacheParsed+4]  == 0x0043))
                                {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                }
                            }
                        }
                    }

                    if((enSMIParse == E_PARSE_START_TIME)||(!bFound))
                    {
                        break;
                    }

                    // search the next PCLASS_TAG & SYNC_START
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                    for(;u32CacheParsed<=u32TextParseMax;u32CacheParsed++)
                    {
                        /* DOS types*/
                        if((pu16Cache[u32CacheParsed] == 0x000D) && //'\r'
                            (pu16Cache[u32CacheParsed+1] == 0x000A) && //'\n'
                            (pu16Cache[u32CacheParsed+2] == 0x003C) && //'<'
                            (pu16Cache[u32CacheParsed+3] == 0x0053 || pu16Cache[u32CacheParsed+3] == 0x0073) && //'S','s'
                            (pu16Cache[u32CacheParsed+4] == 0x0059 || pu16Cache[u32CacheParsed+4] == 0x0079) && //'Y','y'
                            (pu16Cache[u32CacheParsed+5] == 0x004E || pu16Cache[u32CacheParsed+5] == 0x006E) && //'N','n'
                            (pu16Cache[u32CacheParsed+6] == 0x0043 || pu16Cache[u32CacheParsed+6] == 0x0063) //'C','c'
                            )
                        {
                            break;
                        }
                        else if((pu16Cache[u32CacheParsed] == 0x000D) && //'\r'
                            (pu16Cache[u32CacheParsed+1] == 0x000A) && //'\n'
                            (pu16Cache[u32CacheParsed+2] == 0x003C) && //'<'
                            (pu16Cache[u32CacheParsed+3] == 0x0050 || pu16Cache[u32CacheParsed+3] == 0x0070) && //'P','p'
                            (pu16Cache[u32CacheParsed+4] == 0x0020) && //' '
                            (pu16Cache[u32CacheParsed+5] == 0x0043 || pu16Cache[u32CacheParsed+5] == 0x0063) && //'C','c'
                            (pu16Cache[u32CacheParsed+6] == 0x004C || pu16Cache[u32CacheParsed+6] == 0x006C) //'L','l'
                            )
                        {
                            break;
                        }
                        else if((pu16Cache[u32CacheParsed] == 0x000D) && //'\r'
                            (pu16Cache[u32CacheParsed+1] == 0x000A) && //'\n'
                            (pu16Cache[u32CacheParsed+2] == 0x003C) && //'<'
                            (pu16Cache[u32CacheParsed+3] == 0x002F) && //'/'
                            (pu16Cache[u32CacheParsed+4] == 0x0042 || pu16Cache[u32CacheParsed+4] == 0x0062) && //'B','b'
                            (pu16Cache[u32CacheParsed+5] == 0x004F || pu16Cache[u32CacheParsed+5] == 0x006F) && //'O','o'
                            (pu16Cache[u32CacheParsed+6] == 0x0044 || pu16Cache[u32CacheParsed+6] == 0x0064) && //'D','d'
                            (pu16Cache[u32CacheParsed+7] == 0x0059 || pu16Cache[u32CacheParsed+7] == 0x0079) //'Y','y'
                            )
                        {
                            break;
                        }
                        /* UNIX types*/
                        else if((pu16Cache[u32CacheParsed] == 0x000A) && //'\n'
                            (pu16Cache[u32CacheParsed+1] == 0x003C) && //'<'
                            (pu16Cache[u32CacheParsed+2] == 0x0053 || pu16Cache[u32CacheParsed+2] == 0x0073) && //'S','s'
                            (pu16Cache[u32CacheParsed+3] == 0x0059 || pu16Cache[u32CacheParsed+3] == 0x0079) && //'Y','y'
                            (pu16Cache[u32CacheParsed+4] == 0x004E || pu16Cache[u32CacheParsed+4] == 0x006E) && //'N','n'
                            (pu16Cache[u32CacheParsed+5] == 0x0043 || pu16Cache[u32CacheParsed+5] == 0x0063) //'C','c'
                            )
                        {
                            break;
                        }
                        else if((pu16Cache[u32CacheParsed] == 0x000A) && //'\n'
                            (pu16Cache[u32CacheParsed+1] == 0x003C) && //'<'
                            (pu16Cache[u32CacheParsed+2] == 0x0050 || pu16Cache[u32CacheParsed+2] == 0x0070) && //'P','p'
                            (pu16Cache[u32CacheParsed+3] == 0x0020) && //' '
                            (pu16Cache[u32CacheParsed+4] == 0x0043 || pu16Cache[u32CacheParsed+4] == 0x0063) && //'C','c'
                            (pu16Cache[u32CacheParsed+5] == 0x004C || pu16Cache[u32CacheParsed+5] == 0x006C) //'L','l'
                            )
                        {
                            break;
                        }
                        else if((pu16Cache[u32CacheParsed] == 0x000A) && //'\n'
                            (pu16Cache[u32CacheParsed+1] == 0x003C) && //'<'
                            (pu16Cache[u32CacheParsed+2] == 0x002F) && //'/'
                            (pu16Cache[u32CacheParsed+3] == 0x0042 || pu16Cache[u32CacheParsed+3] == 0x0062) && //'B','b'
                            (pu16Cache[u32CacheParsed+4] == 0x004F || pu16Cache[u32CacheParsed+4] == 0x006F) && //'O','o'
                            (pu16Cache[u32CacheParsed+5] == 0x0044 || pu16Cache[u32CacheParsed+5] == 0x0064) && //'D','d'
                            (pu16Cache[u32CacheParsed+6] == 0x0059 || pu16Cache[u32CacheParsed+6] == 0x0079) //'Y','y'
                            )
                        {
                            break;
                        }
                    }

                    u8FindSubtitleCnt++;
                    if(u8FindSubtitleCnt < 2) //check if the first subtitle
                    {//only save at firt subtitle

                        SUBTITLE_FILTER_DBG(printf("this is unicode\n"));
                        U16 u16NeedFilterLength = (u32CacheParsed-u32TagStart)*2;   //unicode, so *2
                        U8 *pu8TempCache = NULL;

                        pu8TempCache = (U8 *)msAPI_Memory_Allocate((u16NeedFilterLength + 2)*sizeof(U8),BUF_ID_FILEBROWER);

                        if(pu8TempCache==NULL)
                        {
                            SUBTITLE_FILTER_DBG(printf("pu8TempCache is NULL\n"));
                            eRet = E_PARSE_ONE_SUBTITLE_FAIL;
                            return eRet;
                        }
                        memcpy(pu8TempCache,pu16Cache+u32TagStart,u16NeedFilterLength);

#if SUBTITLE_DUMP_FILTER_CONTENT  //for debug
                        U16 u16TempCounter1 = 0;
                        printf("\n\n------------pu16TempCache Start -----------------------\n");
                        for(u16TempCounter1=0;u16TempCounter1<u16NeedFilterLength;u16TempCounter1++)
                        {
                            //printf("u16SasukeCounter:%d\n",u16SasukeCounter);
                            printf("%c",pu8TempCache[u16TempCounter1]);
                        }
                        printf("\n------------pu8TempCache done---------------\n\n");
#endif

                        U16 u16ReplaceCount = 0;
                        //unicode, therefore u16NeedFilterLength*2
                        u16ReplaceCount = _MApp_MPlayer_SubtitleDataFilter(pu8TempCache, u16NeedFilterLength,FILTER_TAG_UNICODE,2,FILTER_TAG_END_UNICODE,2, TRUE);
                        u16NeedFilterLength = u16NeedFilterLength - u16ReplaceCount;
                        u32CacheParsed = u32CacheParsed - (u16ReplaceCount/2);
                        SUBTITLE_FILTER_DBG(printf("after filer u16ReplaceCount:%d  u16NeedFilterLength:%d\n",u16ReplaceCount,u16NeedFilterLength));

#if SUBTITLE_DUMP_FILTER_CONTENT  //for debug
                        U16 u16TempCounter2 = 0;
                        printf("\n\n------------after filter-----------------------\n");
                        for(u16TempCounter2=0;u16TempCounter2<u16NeedFilterLength;u16TempCounter2++)
                        {
                            printf("%c",pu8TempCache[u16TempCounter2]);
                        }
                        printf("\n------------filterdone done---------------\n\n");
#endif

                        pu16Cache[u32CacheParsed] = '\0';
                        pu16Cache[u32CacheParsed+1] = '\0';
                        pu8TempCache[u16NeedFilterLength] = '\0';
                        pu8TempCache[u16NeedFilterLength+1] = '\0';

                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), pu8TempCache, u16NeedFilterLength+2);

                        if(pu8TempCache!=NULL)
                        {
                            msAPI_Memory_Free(pu8TempCache,BUF_ID_FILEBROWER);
                            pu8TempCache = NULL;
                        }
                    }
                    enSMIParse = E_PARSE_DONE;

                    break;

                case E_PARSE_DONE:

                    enSMIParse = E_PARSE_START_TIME;

                    if(u8FindSubtitleCnt < 2)
                    {//1st subtitle found
                        // Fill the subtitle tag.
                        pSubtitleTag->u32TimeStart  = u32TimeStart;
                        pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                        //check if find subtitle, we will add LAST_SUBTITLE_DISPLAY_TIME at the end time
                        if(m_MPlayerSubtitleInfo[m_u8CurTrackIdx].stSMIFinalSubtitle.u32TimeStart == u32TimeStart &&
                            m_MPlayerSubtitleInfo[m_u8CurTrackIdx].stSMIFinalSubtitle.u32SubtitlefilePos == m_u32CurSubtitleFilePos+u32TagStart*2)
                        {
                            m_u32SubtitleBufParsed = u32CacheParsed*2;
                            pSubtitleTag->u32TimeEnd = pSubtitleTag->u32TimeStart + LAST_SUBTITLE_DISPLAY_TIME*1000;
                            bFindSubtitle = TRUE;
                        }
                    }
                    else
                    {//2nd subtitle found
                        //save next start file position at u32PrevTagPos
                        m_u32SubtitleBufParsed = u32PrevTagPos - m_u32CurSubtitleFilePos;

                        pSubtitleTag->u32TimeEnd = u32TimeStart;
                        bFindSubtitle = TRUE;
                    }

                    if(bFindSubtitle == TRUE)
                    {
                        SMALL_BUF_PARSER_DBG(printf("CurTrack %d Next start fpos %d tag -> %lu\n", m_u8CurTrackIdx, u32PrevTagPos, u32TimeStart));
                        SMALL_BUF_PARSER_DBG(printf("Tag %lu -> %lu\n", pSubtitleTag->u32TimeStart, pSubtitleTag->u32TimeEnd));
                        eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    }
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enSMIParse == E_PARSE_START_TIME)
                { //1. start time
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSMIParse = E_PARSE_START_TIME;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SMI_Parser_END;
            }
        }
    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SMI_Parser_END;
            }

            switch(enSMIParse)
            {
                case E_PARSE_START_TIME:
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                        if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            u32CacheParsed += sizeof(SYNC_TAG)-1;
                            SUBTITLE_FIND_DIGIT(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            i = _MApp_MPlayer_ScanDigit(&pu8Cache[u32CacheParsed], &u32TimeStart);
                            u32CacheParsed = u32CacheParsed + i +1;
                            enSMIParse = E_PARSE_SUB_LINE1;
                            break;
                        }
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    // search PCLASS_TAG
                    bFound = FALSE;
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if(m_MPlayerSubtitleInfo[m_u8CurTrackIdx].stSMIClass.bPClass)
                        {
                            _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(PCLASS_TAG)-1);
                            if(memcmp(&pu8Cache[u32CacheParsed], PCLASS_TAG, sizeof(PCLASS_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(PCLASS_TAG)-1;
                                if( pClass->u8ClassLen != 0)
                                {
                                    //in E_PARSE_IDENTIFIER state, pClass[u8CurClassNo].u8ClassName is converted to uppercase.
                                    //We have to convert read data to uppercase by comparison with u8ClassName
                                    SMALL_BUF_PARSER_DBG(printf("Class name: %s\n", pClass->u8ClassName));
                                    _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], pClass->u8ClassLen);
                                    if(memcmp(&pu8Cache[u32CacheParsed], pClass->u8ClassName,  pClass->u8ClassLen) == 0)
                                    {
                                        //To solve the case: <P Class=ENUSCC ID=Source>The Speaker </P>
                                        //if not found the end of class name('>') in SUBTITLE_SMALL_BUF_SIZE, will read next block
                                        for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                                        {
                                            if ((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
                                            {
                                                u32TagStart = u32CacheParsed+2; //cannot find '>' until line end, this line is no subtitle
                                                u32CacheParsed = u32TagStart;
                                                break;
                                            }

                                            if(pu8Cache[u32CacheParsed] == '>')
                                            {
                                                u32TagStart = u32CacheParsed+1;
                                                u32CacheParsed = u32TagStart;
                                                bFound = TRUE;
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                if((pu8Cache[u32CacheParsed] == '<') &&
                                    (pu8Cache[u32CacheParsed+1]  == 'S') &&
                                    (pu8Cache[u32CacheParsed+2]  == 'Y') &&
                                    (pu8Cache[u32CacheParsed+3]  == 'N') &&
                                    (pu8Cache[u32CacheParsed+4]  == 'C'))
                                {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                }
                            }
                        }
                        else
                        {
                           if(pu8Cache[u32CacheParsed] == '>')
                            {
                                u32TagStart = u32CacheParsed+1;
                                u32CacheParsed = u32TagStart;
                                bFound = TRUE;
                                break;
                            }
                            else
                            {
                                if((pu8Cache[u32CacheParsed] == '<') &&
                                    (pu8Cache[u32CacheParsed+1]  == 'S') &&
                                    (pu8Cache[u32CacheParsed+2]  == 'Y') &&
                                    (pu8Cache[u32CacheParsed+3]  == 'N') &&
                                    (pu8Cache[u32CacheParsed+4]  == 'C'))
                                {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                }
                            }
                        }
                    }

                    if((enSMIParse == E_PARSE_START_TIME)||(!bFound))
                    {
                        break;
                    }

                    // search the next PCLASS_TAG & SYNC_START
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                    for(;u32CacheParsed<=u32TextParseMax;u32CacheParsed++)
                    {
                        /* DOS types*/
                        if((pu8Cache[u32CacheParsed] == '\r') &&
                            (pu8Cache[u32CacheParsed+1] == '\n') &&
                            (pu8Cache[u32CacheParsed+2] == '<') &&
                            (pu8Cache[u32CacheParsed+3] == 'S' || pu8Cache[u32CacheParsed+3] == 's') &&
                            (pu8Cache[u32CacheParsed+4] == 'Y' || pu8Cache[u32CacheParsed+4] == 'y') &&
                            (pu8Cache[u32CacheParsed+5] == 'N' || pu8Cache[u32CacheParsed+5] == 'n') &&
                            (pu8Cache[u32CacheParsed+6] == 'C' || pu8Cache[u32CacheParsed+6] == 'c')
                           )
                        {
                            break;
                        }
                        else if((pu8Cache[u32CacheParsed] == '\r') &&
                            (pu8Cache[u32CacheParsed+1] == '\n') &&
                            (pu8Cache[u32CacheParsed+2] == '<') &&
                            (pu8Cache[u32CacheParsed+3] == 'P' || pu8Cache[u32CacheParsed+3] == 'p') &&
                            (pu8Cache[u32CacheParsed+4] == ' ') &&
                            (pu8Cache[u32CacheParsed+5] == 'C' || pu8Cache[u32CacheParsed+4] == 'c') &&
                            (pu8Cache[u32CacheParsed+6] == 'L' || pu8Cache[u32CacheParsed+5] == 'l')
                           )
                        {
                            break;
                        }
                        else if((pu8Cache[u32CacheParsed] == '\r') &&
                            (pu8Cache[u32CacheParsed+1] == '\n') &&
                            (pu8Cache[u32CacheParsed+2] == '<') &&
                            (pu8Cache[u32CacheParsed+3] == '/') &&
                            (pu8Cache[u32CacheParsed+4] == 'B' || pu8Cache[u32CacheParsed+4] == 'b') &&
                            (pu8Cache[u32CacheParsed+5] == 'O' || pu8Cache[u32CacheParsed+5] == 'o') &&
                            (pu8Cache[u32CacheParsed+6] == 'D' || pu8Cache[u32CacheParsed+6] == 'd') &&
                            (pu8Cache[u32CacheParsed+7] == 'Y' || pu8Cache[u32CacheParsed+7] == 'y')
                            )
                        {
                            break;
                        }
                        /* UNIX types*/
                        else if((pu8Cache[u32CacheParsed] == '\n') &&
                            (pu8Cache[u32CacheParsed+1] == '<') &&
                            (pu8Cache[u32CacheParsed+2] == 'S' || pu8Cache[u32CacheParsed+2] == 's') &&
                            (pu8Cache[u32CacheParsed+3] == 'Y' || pu8Cache[u32CacheParsed+3] == 'y') &&
                            (pu8Cache[u32CacheParsed+4] == 'N' || pu8Cache[u32CacheParsed+4] == 'n') &&
                            (pu8Cache[u32CacheParsed+5] == 'C' || pu8Cache[u32CacheParsed+5] == 'c')
                            )
                        {
                            break;
                        }
                        else if((pu8Cache[u32CacheParsed] == '\n') &&
                            (pu8Cache[u32CacheParsed+1] == '<') &&
                            (pu8Cache[u32CacheParsed+2] == 'P' || pu8Cache[u32CacheParsed+2] == 'p') &&
                            (pu8Cache[u32CacheParsed+3] == ' ') &&
                            (pu8Cache[u32CacheParsed+4] == 'C' || pu8Cache[u32CacheParsed+4] == 'c') &&
                            (pu8Cache[u32CacheParsed+5] == 'L' || pu8Cache[u32CacheParsed+5] == 'l')
                            )
                        {
                            break;
                        }
                        else if((pu8Cache[u32CacheParsed] == '\n') &&
                            (pu8Cache[u32CacheParsed+1] == '<') &&
                            (pu8Cache[u32CacheParsed+2] == '/') &&
                            (pu8Cache[u32CacheParsed+3] == 'B' || pu8Cache[u32CacheParsed+3] == 'b') &&
                            (pu8Cache[u32CacheParsed+4] == 'O' || pu8Cache[u32CacheParsed+4] == 'o') &&
                            (pu8Cache[u32CacheParsed+5] == 'D' || pu8Cache[u32CacheParsed+5] == 'd') &&
                            (pu8Cache[u32CacheParsed+6] == 'Y' || pu8Cache[u32CacheParsed+6] == 'y')
                            )
                        {
                            break;
                        }
                    }

                    u8FindSubtitleCnt++;
                    if(u8FindSubtitleCnt < 2) //check if the first subtitle
                    {//only save at firt subtitle

                        U16 u16NeedFilterLength = u32CacheParsed-u32TagStart;
                        U8 *pu8TempCache = NULL;

                        pu8TempCache = (U8 *)msAPI_Memory_Allocate((u16NeedFilterLength + 1)*sizeof(U8),BUF_ID_FILEBROWER);

                        if(pu8TempCache==NULL)
                        {
                            SUBTITLE_FILTER_DBG(printf("pu8TempCache is NULL\n"));
                            eRet = E_PARSE_ONE_SUBTITLE_FAIL;
                            return eRet;
                        }
                        memcpy(pu8TempCache,pu8Cache+u32TagStart,u16NeedFilterLength);
                        SUBTITLE_FILTER_DBG(printf("Before filter u16NeedFilterLength:%d\n",u16NeedFilterLength));

#if SUBTITLE_DUMP_FILTER_CONTENT    //for debug
                        U16 u16TempCounter1 = 0;
                        SUBTITLE_FILTER_DBG(printf("\n\n------------pu8TempCache Start -----------------------\n"));
                        for(u16TempCounter1=0;u16TempCounter1<u16NeedFilterLength;u16TempCounter1++)
                        {
                            printf("%c",pu8TempCache[u16TempCounter1]);
                        }
                        printf("\n------------pu8TempCache done---------------\n\n");
#endif

                        U16 u16ReplaceCount = 0;
                        u16ReplaceCount = _MApp_MPlayer_SubtitleDataFilter(pu8TempCache, u16NeedFilterLength,FILTER_TAG,1,FILTER_TAG_END,1, FALSE);
                        u16NeedFilterLength = u16NeedFilterLength - u16ReplaceCount;
                        u32CacheParsed = u32CacheParsed - u16ReplaceCount;

#if SUBTITLE_DUMP_FILTER_CONTENT  //for debug
                        U16 u16TempCounter2 = 0;
                        printf("\n\n------------after filter-----------------------\n");
                        for(u16TempCounter2=0;u16TempCounter2<u16NeedFilterLength;u16TempCounter2++)
                        {
                            //printf("u16SasukeCounter:%d\n",u16SasukeCounter);
                            printf("%c",pu8TempCache[u16TempCounter2]);
                        }
                        printf("\n------------filterdone done---------------\n\n");
#endif

                        pu8Cache[u32CacheParsed] = '\0';
                        pu8TempCache[u16NeedFilterLength] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), pu8TempCache, (u16NeedFilterLength+1));
                        if(pu8TempCache!=NULL)
                        {
                            msAPI_Memory_Free(pu8TempCache,BUF_ID_FILEBROWER);
                            pu8TempCache = NULL;
                        }
                    }
                    enSMIParse = E_PARSE_DONE;

                    break;

                case E_PARSE_DONE:

                    enSMIParse = E_PARSE_START_TIME;

                    if(u8FindSubtitleCnt < 2)
                    {//1st subtitle found
                        // Fill the subtitle tag.
                        pSubtitleTag->u32TimeStart  = u32TimeStart;
                        pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                        //check if find subtitle, we will add LAST_SUBTITLE_DISPLAY_TIME at the end time
                        if(m_MPlayerSubtitleInfo[m_u8CurTrackIdx].stSMIFinalSubtitle.u32TimeStart == u32TimeStart &&
                            m_MPlayerSubtitleInfo[m_u8CurTrackIdx].stSMIFinalSubtitle.u32SubtitlefilePos == m_u32CurSubtitleFilePos+u32TagStart)
                        {
                            m_u32SubtitleBufParsed = u32CacheParsed;
                            pSubtitleTag->u32TimeEnd = pSubtitleTag->u32TimeStart + LAST_SUBTITLE_DISPLAY_TIME*1000;
                            bFindSubtitle = TRUE;
                        }
                    }
                    else
                    {//2nd subtitle found
                        //save next start file position at u32PrevTagPos
                        m_u32SubtitleBufParsed = u32PrevTagPos - m_u32CurSubtitleFilePos;

                        pSubtitleTag->u32TimeEnd = u32TimeStart;
                        bFindSubtitle = TRUE;
                    }

                    if(bFindSubtitle == TRUE)
                    {
                        SMALL_BUF_PARSER_DBG(printf("CurTrack %d Next start fpos %d tag -> %lu\n", m_u8CurTrackIdx, u32PrevTagPos, u32TimeStart));
                        SMALL_BUF_PARSER_DBG(printf("Tag %lu -> %lu\n", pSubtitleTag->u32TimeStart, pSubtitleTag->u32TimeEnd));
                        eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    }
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                // Read the next block of data.
                if(enSMIParse == E_PARSE_START_TIME)
                { //1. start time
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSMIParse = E_PARSE_START_TIME;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SMI_Parser_END;
            }
        }
    }

_MApp_MPlayer_SMI_Parser_END:

    return eRet;
}

//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// also search the each track's final subtitle(enable bToFindfinalSubtitle to TRUE) and save data in stSMIFinalSubtitle
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SMI_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define SUBTITLE_CACHE_SIZE             1024
    #define STYLE_TAG                       "<STYLE TYPE="
    #define STYLE_TAG_UNICODE               "<\0S\0T\0Y\0L\0E\0 \0T\0Y\0P\0E\0=\0"
    #define PCLASS_TAG                      "<P CLASS="
    #define PCLASS_TAG_UNICODE              "<\0P\0 \0C\0L\0A\0S\0S\0=\0"
    #define SYNC_TAG                        "<SYNC START="
    #define SYNC_TAG_UNICODE                "<\0S\0Y\0N\0C\0 \0S\0T\0A\0R\0T\0=\0"
    #define BODY_TAG                        "</BODY>"
    #define SAMI_TAG                        "</SAMI>"
    #define BODY_TAG_UNICODE                "<\0/\0B\0O\0D\0Y\0>\0"
    #define SAMI_TAG_UNICODE                "<\0/\0S\0A\0M\0I\0>\0"
    #define LANG_TAG                        "LANG:"
    #define LANG_TAG_UNICODE                "L\0A\0N\0G\0:\0"
    #define SAMI_PREPARSE_LEN               128
    #define CLASS_LEN                       64
    #define MAX_SMI_TIME_DIGIT              24

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    BOOLEAN bMultiClass = FALSE;
    BOOLEAN bFound = FALSE;
    BOOLEAN bPClass = FALSE;
    U32 i;
    U32 u32TimeStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    U8 u8ClassLen=0;
    SMI_Subtitle_Class astClass[SUPPORT_SUBITILE_TRACK_MAX];
    SMI_Subtitle_Class *pClass;
    U8 u8TotalClassNo=0;
    U8 u8CurClassNo=0;
    enumMPlayerSubtitleParse enSMIParse = E_PARSE_INIT;
    U32 u32TagStart=0;
    U32 u32CacheParsed=0;
    U32 u32ParsingTime=0;
    BOOLEAN bNeedTrans2Unicode = FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;
    U16 u16SMIFinalSubtitleTagCount=0;
    BOOLEAN bToFindfinalSubtitle = FALSE; //if TRUE, re-enter state to find the final subtitle
    U8 u8ToCheckPClassName = FALSE; //used in START_TIME to check if the same PClass
    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

_MApp_MPlayer_Parse_Next_Class:

    m_u16SubtitleTagCount = 0;
    u32SearchLoopCnt=0;
    bToFindfinalSubtitle = FALSE;
    //save all tracks' language using class number not track number in state of E_PARSE_IDENTIFIER.
    //m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;
    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);
    pClass = &astClass[0];

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32CacheParsed = 0;

    u32ParsingTime = msAPI_Timer_GetTime0();

_MApp_MPlayer_SMI_Parse_Final_Subtitle:

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            switch(enSMIParse)
            {
                case E_PARSE_INIT:
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                        if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                        {
                            u32CacheParsed = 0;
                            break;
                        }
                        else if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
                        {
                            goto _MApp_MPlayer_SMI_Parser_END;
                        }
                    }
                    enSMIParse = E_PARSE_IDENTIFIER;
                    break;

                case E_PARSE_IDENTIFIER:
                    // Find the <STYLE TYPE=
                    for(;(u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN/2)&&(u8TotalClassNo < SUPPORT_SUBITILE_TRACK_MAX);u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(STYLE_TAG_UNICODE)-1);

                        if(memcmp(&pu16Cache[u32CacheParsed], STYLE_TAG_UNICODE, sizeof(STYLE_TAG_UNICODE)-1)==0)
                        {
                            for(;u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                            {
                                if(pu16Cache[u32CacheParsed] == 0x007D)
                                {
                                    break;
                                }
                            }

                            pClass[u8TotalClassNo].u8ClassLen = 0;
                            for(;u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                            {
                                if(pu16Cache[u32CacheParsed] == 0x002E)
                                {
                                    for(u8ClassLen=0;u8ClassLen<MAX_CLASS_NAME_LEN;u8ClassLen++)
                                    {
                                        if(pu16Cache[u32CacheParsed+u8ClassLen+1] == 0x0020)
                                        {
                                            break;
                                        }
                                        pClass[u8TotalClassNo].u8ClassName[u8ClassLen] = LOBYTE(pu16Cache[u32CacheParsed+u8ClassLen+1]);
                                    }
                                    pClass[u8TotalClassNo].u8ClassLen = u8ClassLen;
                                    _MApp_MPlayer_nupr(pClass[u8TotalClassNo].u8ClassName, u8ClassLen);
                                    SMALL_BUF_PARSER_DBG(printf("Class name: %s\n", pClass[u8TotalClassNo].u8ClassName));

                                    u32CacheParsed += u8ClassLen;
                                    for(;u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                                    {
                                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(LANG_TAG_UNICODE)/2);
                                        if(memcmp(&pu16Cache[u32CacheParsed], LANG_TAG_UNICODE, sizeof(LANG_TAG_UNICODE)-1)==0)
                                        {
                                            u32CacheParsed += sizeof(LANG_TAG_UNICODE)/2;
                                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                                            pClass[u8TotalClassNo].u8Lang[0] = LOBYTE(pu16Cache[u32CacheParsed]);
                                            pClass[u8TotalClassNo].u8Lang[1] = LOBYTE(pu16Cache[u32CacheParsed+1]);

                                            U32 u32TempSubtitleLang;
                                            u32TempSubtitleLang = pClass[u8TotalClassNo].u8Lang[1];
                                            u32TempSubtitleLang = (u32TempSubtitleLang<<8) + pClass[u8TotalClassNo].u8Lang[0];
                                            SMALL_BUF_PARSER_DBG(printf("ClassNo=%d, Lang[0]=%c [1]=%c \n", u8TotalClassNo, pClass[u8TotalClassNo].u8Lang[0], pClass[u8TotalClassNo].u8Lang[1]));

                                            if(u8TotalClassNo < SUPPORT_SUBITILE_TRACK_MAX)
                                            {
                                                m_MPlayerSubtitleInfo[u8TotalClassNo].u32SubtitleLanguage = u32TempSubtitleLang;
                                            }
                                            break;
                                        }
                                        else if(pu16Cache[u32CacheParsed] == 0x007D)
                                        {
                                            break;
                                        }
                                    }

                                    u8TotalClassNo++;

                                    if(u8TotalClassNo >= SUPPORT_SUBITILE_TRACK_MAX)
                                    {
                                        SMALL_BUF_PARSER_DBG(printf("SMI OVER class number!\n"));
                                        break;
                                    }
                                }
                                else
                                {
                                    if((pu16Cache[u32CacheParsed] == 0x002D) && (pu16Cache[u32CacheParsed+1] == 0x002D) &&
                                        (pu16Cache[u32CacheParsed+2] == 0x003E))
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    bPClass = FALSE;

                    if(u8TotalClassNo > 0)
                    {
                        bMultiClass = FALSE;
                        u8CurClassNo = 0;
                        // Find the <SYNC START=
                        for(u32CacheParsed=0;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                        {
                            _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                            if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(SYNC_TAG_UNICODE)/2;
                                // search PCLASS_TAG
                                for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                                {
                                    _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(PCLASS_TAG_UNICODE)-1);
                                    if(memcmp(&pu16Cache[u32CacheParsed], PCLASS_TAG_UNICODE, sizeof(PCLASS_TAG_UNICODE)-1)==0)
                                    {
                                        u8CurClassNo++;
                                        u32CacheParsed += sizeof(PCLASS_TAG_UNICODE)/2;
                                        bPClass = TRUE;
                                    }

                                    _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                                    if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                                    {
                                        SMALL_BUF_PARSER_DBG(printf(" found 2nd SYNC_START\n"));
                                        break;
                                    }

                                    if(u8CurClassNo == u8TotalClassNo)
                                    {
                                        bMultiClass = TRUE;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    else
                    {
                        for(u32CacheParsed=0;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                        {
                            _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(PCLASS_TAG_UNICODE)-1);
                            if(memcmp(&pu16Cache[u32CacheParsed], PCLASS_TAG_UNICODE, sizeof(PCLASS_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(PCLASS_TAG_UNICODE)/2;
                                for(u8ClassLen=0;u8ClassLen<MAX_CLASS_NAME_LEN;u8ClassLen++)
                                {
                                    pClass[u8TotalClassNo].u8ClassName[u8ClassLen] = LOBYTE(pu16Cache[u32CacheParsed+u8ClassLen]);
                                    if(LOBYTE(pu16Cache[u32CacheParsed+u8ClassLen]) == '>' || LOBYTE(pu16Cache[u32CacheParsed+u8ClassLen]) == ' ')
                                    {
                                        break;
                                    }
                                }
                                pClass[u8TotalClassNo].u8ClassLen = u8ClassLen;
                                _MApp_MPlayer_nupr(pClass[u8TotalClassNo].u8ClassName, u8ClassLen);
                                u8TotalClassNo++;
                                bPClass = TRUE;
                                break;
                            }
                        }
                    }

                    u8CurClassNo = 0;
                    u32CacheParsed = 0;
                    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                    if(bNeedTrans2Unicode == TRUE)
                    {
                        //Every time we load data from usb to subtitle buufer.
                        //If it is big endian, we need to transfer it to little endian for parsing.
                        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                    }

                    enSMIParse = E_PARSE_START_TIME;
                    break;

                case E_PARSE_START_TIME:
                    u8ToCheckPClassName = FALSE;
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                        if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                        {
                            u32CacheParsed += sizeof(SYNC_TAG_UNICODE)/2;
                            SUBTITLE_FIND_DIGIT_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            // Convert time to ASCII.
                            for(i=0;i<MAX_SMI_TIME_DIGIT/2;i++)
                            {
                                if(ISDIGIT_UNICODE(pu16Cache[u32CacheParsed+i]))
                                {
                                    pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                                }
                                else
                                {
                                    pu8Cache[i] = '\0';
                                    break;
                                }
                            }

                            i = _MApp_MPlayer_ScanDigit(&pu8Cache[0], &u32TimeStart);
                            u32CacheParsed = u32CacheParsed + i +1;
                            u8ToCheckPClassName = TRUE;
                            break;
                        }
                    }

                    if(u8ToCheckPClassName)
                    {
                        // search PCLASS_TAG
                        bFound = FALSE;
                        for(;u32CacheParsed<=(SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET)/2;u32CacheParsed++)
                        {
                            if(bPClass)
                            {
                                _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(PCLASS_TAG_UNICODE)-1);
                                if(memcmp(&pu16Cache[u32CacheParsed], PCLASS_TAG_UNICODE, sizeof(PCLASS_TAG_UNICODE)-1)==0)
                                {
                                    u32CacheParsed += sizeof(PCLASS_TAG_UNICODE)/2;
                                    if( pClass[u8CurClassNo].u8ClassLen != 0)
                                    {
                                        //this data transformation is for class name check, so using with CLASS_LEN
                                        for(i=0;i<CLASS_LEN/2;i++)
                                        {
                                            pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                                        }
                                        //in E_PARSE_IDENTIFIER state, pClass[u8CurClassNo].u8ClassName is converted to uppercase.
                                        //We have to convert read data to uppercase by comparison with u8ClassName
                                        //_MApp_MPlayer_nupr(pClass[u8CurClassNo].u8ClassName, pClass[u8CurClassNo].u8ClassLen);
                                        _MApp_MPlayer_nupr(&pu8Cache[0], pClass[u8CurClassNo].u8ClassLen);
                                        SMALL_BUF_PARSER_DBG(printf("Class name: %s\n", pClass[u8CurClassNo].u8ClassName));
                                        if(memcmp(&pu8Cache[0], pClass[u8CurClassNo].u8ClassName,  pClass[u8CurClassNo].u8ClassLen) == 0)
                                        {
                                            //To solve the case: <P Class=ENUSCC ID=Source>The Speaker </P>
                                            //if not found the end of class name('>') in SUBTITLE_SMALL_BUF_SIZE, will read next block
                                            for(;u32CacheParsed<=(SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET)/2;u32CacheParsed++)
                                            {
                                                if ((pu16Cache[u32CacheParsed] == 0x000D) && (pu16Cache[u32CacheParsed+1] == 0x000A)) //0x000D '\r', 0x000A '\n'
                                                {
                                                    u32TagStart = u32CacheParsed+2; //cannot find '>' until line end, this line is no subtitle
                                                    u32CacheParsed = u32TagStart;
                                                    break;
                                                }

                                                if(pu16Cache[u32CacheParsed] == 0x003E) //'>'
                                                {
                                                    u32TagStart = u32CacheParsed+1;
                                                    u32CacheParsed = u32TagStart;
                                                    bFound = TRUE;
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                        else if(!bMultiClass)
                                        {
                                            enSMIParse = E_PARSE_START_TIME;
                                            break;
                                        }
                                    }
                                }
                                else
                                {   //check "<SYNC"
                                    if((pu16Cache[u32CacheParsed] == 0x003C) &&
                                        (pu16Cache[u32CacheParsed+1]  == 0x0053) &&
                                        (pu16Cache[u32CacheParsed+2]  == 0x0059) &&
                                        (pu16Cache[u32CacheParsed+3]  == 0x004E) &&
                                        (pu16Cache[u32CacheParsed+4]  == 0x0043))
                                    {
                                            enSMIParse = E_PARSE_START_TIME;
                                            break;
                                    }
                                }
                            }
                            else
                            {   //check '>'
                                if(pu16Cache[u32CacheParsed] == 0x003E)
                                {
                                    u32TagStart = u32CacheParsed+1;
                                    u32CacheParsed = u32TagStart;
                                    bFound = TRUE;
                                    break;
                                }
                                else
                                {    //check "<SYNC"
                                    if((pu16Cache[u32CacheParsed] == 0x003C) &&
                                        (pu16Cache[u32CacheParsed+1]  == 0x0053) &&
                                        (pu16Cache[u32CacheParsed+2]  == 0x0059) &&
                                        (pu16Cache[u32CacheParsed+3]  == 0x004E) &&
                                        (pu16Cache[u32CacheParsed+4]  == 0x0043))
                                    {
                                            enSMIParse = E_PARSE_START_TIME;
                                            break;
                                    }
                                }
                            }
                        }

                        if(!bFound)
                        {
                            break;
                        }

                        enSMIParse = E_PARSE_DONE;
                    }

                    break;

                case E_PARSE_DONE:
                    if(bToFindfinalSubtitle==FALSE)
                    {   // Fill the subtitle tag.
                        pClass[u8CurClassNo].bPClass = bPClass; //save for SMI_ParseOneSubtitle
                        pu32Index[m_u16SubtitleTagCount] = u32TimeStart;
                        //save tag count to find the last subtitle
                        u16SMIFinalSubtitleTagCount = m_u16SubtitleTagCount;
                        bRet = TRUE;
                        bSubtitleFoundInBuff = TRUE;
                    }
                    else
                    {  //find and save final subtitle info
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSMIFinalSubtitle.u32TimeStart = u32TimeStart;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSMIFinalSubtitle.u32SubtitlefilePos = m_u32CurSubtitleFilePos+u32TagStart*2;
                    }
                    SMALL_BUF_PARSER_DBG(printf("CurClassNo %d fpos %d tag[%u] -> %lu\n", u8CurClassNo, m_u32CurSubtitleFilePos + u32CacheParsed*2,m_u16SubtitleTagCount, u32TimeStart));

                    enSMIParse = E_PARSE_START_TIME;

                    break;

                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || (u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2 && enSMIParse != E_PARSE_DONE))
            {
                if(bToFindfinalSubtitle)
                {
                    if(u32SearchLoopCnt < u32OffsetTimesPerIndex-1)
                    {
                        u32SearchLoopCnt++;
                    }
                    else
                    {//check until the end of final buffer
                       goto _MApp_MPlayer_SMI_Parser_END;
                    }
                    // Read the next block of data.
                    m_u32CurSubtitleFilePos = (u16SMIFinalSubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;

                }
                else
                {
                    if(bSubtitleFoundInBuff == FALSE)
                    {
                        u32SearchLoopCnt++;

                        if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                        {
                            // no subtitle tag in this range
                            if(m_u16SubtitleTagCount==0)
                            {
                                pu32Index[m_u16SubtitleTagCount]=0;
                            }
                            else
                            {
                                pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                            }
                            SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                            m_u16SubtitleTagCount++;
                            u32SearchLoopCnt=0;
                        }
                    }
                    else
                    {
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                    // Read the next block of data.
                    m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;

                }

                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SMI_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            switch(enSMIParse)
            {
                case E_PARSE_INIT:
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                        if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                        {
                            u32CacheParsed = 0;
                            break;
                        }
                        else if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
                        {
                            goto _MApp_MPlayer_SMI_Parser_END;
                        }
                    }
                    enSMIParse = E_PARSE_IDENTIFIER;
                    break;

                case E_PARSE_IDENTIFIER:
                    // Find the <STYLE TYPE=
                    for(;(u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN)&&(u8TotalClassNo < SUPPORT_SUBITILE_TRACK_MAX);u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(STYLE_TAG)-1);
                        if(memcmp(&pu8Cache[u32CacheParsed], STYLE_TAG, sizeof(STYLE_TAG)-1)==0)
                        {
                            for(;u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                            {
                                if(pu8Cache[u32CacheParsed] == '}')
                                {
                                    break;
                                }
                            }
                            pClass[u8TotalClassNo].u8ClassLen = 0;
                            for(;u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                            {
                                if(pu8Cache[u32CacheParsed] == '.')
                                {
                                    for(u8ClassLen=0;u8ClassLen<MAX_CLASS_NAME_LEN;u8ClassLen++)
                                    {
                                        if(pu8Cache[u32CacheParsed+u8ClassLen+1] == ' ')
                                        {
                                            break;
                                        }
                                        pClass[u8TotalClassNo].u8ClassName[u8ClassLen] = pu8Cache[u32CacheParsed+u8ClassLen+1];
                                    }
                                    pClass[u8TotalClassNo].u8ClassLen = u8ClassLen;
                                    _MApp_MPlayer_nupr(pClass[u8TotalClassNo].u8ClassName, u8ClassLen);

                                    SMALL_BUF_PARSER_DBG(printf("Class name: %s\n", pClass[u8TotalClassNo].u8ClassName));
                                    u32CacheParsed += u8ClassLen;
                                    for(;u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                                    {
                                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(LANG_TAG)-1);
                                        if(memcmp(&pu8Cache[u32CacheParsed], LANG_TAG, sizeof(LANG_TAG)-1)==0)
                                        {
                                            u32CacheParsed += sizeof(LANG_TAG)-1;
                                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                                            pClass[u8TotalClassNo].u8Lang[0] = pu8Cache[u32CacheParsed];
                                            pClass[u8TotalClassNo].u8Lang[1] = pu8Cache[u32CacheParsed+1];

                                            U32 u32TempSubtitleLang;
                                            u32TempSubtitleLang = pClass[u8TotalClassNo].u8Lang[1];
                                            u32TempSubtitleLang = (u32TempSubtitleLang<<8) + pClass[u8TotalClassNo].u8Lang[0];
                                            SMALL_BUF_PARSER_DBG(printf("ClassNo=%d, Lang[0]=%c [1]=%c \n", u8TotalClassNo, pClass[u8TotalClassNo].u8Lang[0], pClass[u8TotalClassNo].u8Lang[1]));

                                            if(u8TotalClassNo < SUPPORT_SUBITILE_TRACK_MAX)
                                            {
                                                m_MPlayerSubtitleInfo[u8TotalClassNo].u32SubtitleLanguage = u32TempSubtitleLang;
                                            }
                                            break;
                                        }
                                        else if(pu8Cache[u32CacheParsed] == '}')
                                        {
                                            break;
                                        }
                                    }

                                    u8TotalClassNo++;

                                    if(u8TotalClassNo >= SUPPORT_SUBITILE_TRACK_MAX)
                                    {
                                        SMALL_BUF_PARSER_DBG(printf("SMI OVER class number!\n"));
                                        break;
                                    }
                                }
                                else
                                {
                                    if((pu8Cache[u32CacheParsed] == '-') && (pu8Cache[u32CacheParsed+1] == '-') &&
                                        (pu8Cache[u32CacheParsed+2] == '>'))
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    bPClass = FALSE;

                    if(u8TotalClassNo > 0)
                    {
                        bMultiClass = FALSE;
                        u8CurClassNo = 0;
                        // Find the <SYNC START=
                        for(u32CacheParsed=0;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                        {
                            _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                            if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(SYNC_TAG)-1;
                                // search PCLASS_TAG
                                for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                                {
                                    _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(PCLASS_TAG)-1);
                                    if(memcmp(&pu8Cache[u32CacheParsed], PCLASS_TAG, sizeof(PCLASS_TAG)-1)==0)
                                    {
                                        u8CurClassNo++;
                                        u32CacheParsed += sizeof(PCLASS_TAG)-1;
                                        bPClass = TRUE;
                                    }

                                    _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                                    if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                                    {
                                        SMALL_BUF_PARSER_DBG(printf(" found 2nd SYNC_START\n"));
                                        break;
                                    }

                                    if(u8CurClassNo == u8TotalClassNo)
                                    {
                                        bMultiClass = TRUE;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    else
                    {
                        for(u32CacheParsed=0;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                        {
                            _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(PCLASS_TAG)-1);
                            if(memcmp(&pu8Cache[u32CacheParsed], PCLASS_TAG, sizeof(PCLASS_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(PCLASS_TAG)-1;
                                for(u8ClassLen=0;u8ClassLen<MAX_CLASS_NAME_LEN;u8ClassLen++)
                                {
                                    pClass[u8TotalClassNo].u8ClassName[u8ClassLen] = pu8Cache[u32CacheParsed+u8ClassLen];
                                    if(pu8Cache[u32CacheParsed+u8ClassLen] == '>' || pu8Cache[u32CacheParsed+u8ClassLen] == ' ')
                                    {
                                        break;
                                    }
                                }
                                pClass[u8TotalClassNo].u8ClassLen = u8ClassLen;
                                _MApp_MPlayer_nupr(pClass[u8TotalClassNo].u8ClassName, u8ClassLen);
                                u8TotalClassNo++;
                                bPClass = TRUE;
                                break;
                            }
                        }
                    }

                    u8CurClassNo = 0;
                    u32CacheParsed = 0;
                    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                    enSMIParse = E_PARSE_START_TIME;
                    break;

                case E_PARSE_START_TIME:
                    u8ToCheckPClassName = FALSE;
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                        if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                        {
                            u32CacheParsed += sizeof(SYNC_TAG)-1;
                            SUBTITLE_FIND_DIGIT(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            i = _MApp_MPlayer_ScanDigit(&pu8Cache[u32CacheParsed], &u32TimeStart);
                            u32CacheParsed = u32CacheParsed + i +1;
                            u8ToCheckPClassName = TRUE;
                            break;
                        }
                    }

                    if(u8ToCheckPClassName)
                    {
                        // search PCLASS_TAG
                        bFound = FALSE;
                        for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET;u32CacheParsed++)
                        {
                            if(bPClass)
                            {
                                _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(PCLASS_TAG)-1);
                                if(memcmp(&pu8Cache[u32CacheParsed], PCLASS_TAG, sizeof(PCLASS_TAG)-1)==0)
                                {
                                    u32CacheParsed += sizeof(PCLASS_TAG)-1;
                                    if( pClass[u8CurClassNo].u8ClassLen != 0)
                                    {
                                        //in E_PARSE_IDENTIFIER state, pClass[u8CurClassNo].u8ClassName is converted to uppercase.
                                        //We have to convert read data to uppercase by comparison with u8ClassName
                                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], pClass[u8CurClassNo].u8ClassLen);
                                        SMALL_BUF_PARSER_DBG(printf("Class name: %s\n", pClass[u8CurClassNo].u8ClassName));
                                        if(memcmp(&pu8Cache[u32CacheParsed], pClass[u8CurClassNo].u8ClassName,  pClass[u8CurClassNo].u8ClassLen) == 0)
                                        {
                                            //To solve the case: <P Class=ENUSCC ID=Source>The Speaker </P>
                                            //if not found the end of class name('>') in SUBTITLE_SMALL_BUF_SIZE, will read next block
                                            for(i=u32CacheParsed;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET;u32CacheParsed++)
                                            {
                                                if ((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
                                                {
                                                    u32TagStart = u32CacheParsed+2; //cannot find '>' until line end, this line is no subtitle
                                                    u32CacheParsed = u32TagStart;
                                                    break;
                                                }

                                                if(pu8Cache[u32CacheParsed] == '>')
                                                {
                                                    u32TagStart = u32CacheParsed+1;
                                                    u32CacheParsed = u32TagStart;
                                                    bFound = TRUE;
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                        else if(!bMultiClass)
                                        {
                                            enSMIParse = E_PARSE_START_TIME;
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    if((pu8Cache[u32CacheParsed] == '<') &&
                                        (pu8Cache[u32CacheParsed+1]  == 'S') &&
                                        (pu8Cache[u32CacheParsed+2]  == 'Y') &&
                                        (pu8Cache[u32CacheParsed+3]  == 'N') &&
                                        (pu8Cache[u32CacheParsed+4]  == 'C'))
                                    {
                                            enSMIParse = E_PARSE_START_TIME;
                                            break;
                                    }
                                }
                            }
                            else
                            {
                                if(pu8Cache[u32CacheParsed] == '>')
                                {
                                    u32TagStart = u32CacheParsed+1;
                                    u32CacheParsed = u32TagStart;
                                    bFound = TRUE;
                                    break;
                                }
                                else
                                {
                                    if((pu8Cache[u32CacheParsed] == '<') &&
                                        (pu8Cache[u32CacheParsed+1]  == 'S') &&
                                        (pu8Cache[u32CacheParsed+2]  == 'Y') &&
                                        (pu8Cache[u32CacheParsed+3]  == 'N') &&
                                        (pu8Cache[u32CacheParsed+4]  == 'C'))
                                    {
                                            enSMIParse = E_PARSE_START_TIME;
                                            break;
                                    }
                                }
                            }
                        }
                        if(!bFound)
                        {
                            break;
                        }

                        enSMIParse = E_PARSE_DONE;
                    }

                    break;

                case E_PARSE_DONE:
                    if(bToFindfinalSubtitle==FALSE)
                    {   // Fill the subtitle tag.
                        pClass[u8CurClassNo].bPClass = bPClass; //save for SMI_ParseOneSubtitle
                        pu32Index[m_u16SubtitleTagCount] = u32TimeStart;
                        //save tag count to find the last subtitle
                        u16SMIFinalSubtitleTagCount = m_u16SubtitleTagCount;
                        bRet = TRUE;
                        bSubtitleFoundInBuff = TRUE;
                    }
                    else
                    {  //find and save final subtitle info
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSMIFinalSubtitle.u32TimeStart = u32TimeStart;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSMIFinalSubtitle.u32SubtitlefilePos = m_u32CurSubtitleFilePos+u32TagStart;
                    }
                    SMALL_BUF_PARSER_DBG(printf("CurClassNo %d fpos %d tag[%u] -> %lu\n", u8CurClassNo, m_u32CurSubtitleFilePos + u32CacheParsed,m_u16SubtitleTagCount, u32TimeStart));

                    enSMIParse = E_PARSE_START_TIME;
                    break;

                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || (u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN && enSMIParse != E_PARSE_DONE))
            {
                if(bToFindfinalSubtitle)
                {
                    if(u32SearchLoopCnt < u32OffsetTimesPerIndex-1)
                    {
                        u32SearchLoopCnt++;
                    }
                    else
                    {//check until the end of final buffer
                       goto _MApp_MPlayer_SMI_Parser_END;
                    }
                    // Read the next block of data.
                    m_u32CurSubtitleFilePos = (u16SMIFinalSubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;

                }
                else
                {
                    if(bSubtitleFoundInBuff == FALSE)
                    {
                        u32SearchLoopCnt++;

                        if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                        {
                            // no subtitle tag in this range
                            if(m_u16SubtitleTagCount==0)
                            {
                                pu32Index[m_u16SubtitleTagCount]=0;
                            }
                            else
                            {
                                pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                            }
                            SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                            m_u16SubtitleTagCount++;
                            u32SearchLoopCnt=0;
                        }
                    }
                    else
                    {
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                    // Read the next block of data.
                    m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;

                }

                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SMI_Parser_END;
            }
        }
    }

_MApp_MPlayer_SMI_Parser_END:

    if(bRet)
    {
        //Find last subtitle and give it the end time
        if(bToFindfinalSubtitle == FALSE)
        {
                m_u32CurSubtitleFilePos = u16SMIFinalSubtitleTagCount*u32OffsetTimesPerIndex*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("read block %ld for last subtitle\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                u32SearchLoopCnt = 0;
                bSubtitleFoundInBuff = FALSE;
                enSMIParse = E_PARSE_START_TIME;
                bToFindfinalSubtitle = TRUE;
                goto _MApp_MPlayer_SMI_Parse_Final_Subtitle;
        }

        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SMI;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stSMIClass, &pClass[u8CurClassNo], sizeof(SMI_Subtitle_Class));
        m_u8SubtitleTrackNum++;
    }

    if(m_u8SubtitleTrackNum < SUPPORT_SUBITILE_TRACK_MAX)
    {
        u8CurClassNo++;
        if((u8TotalClassNo > 1) && (u8CurClassNo < u8TotalClassNo))
        {
            m_u32CurSubtitleFilePos = 0;
            u32CacheParsed = 0;
            enSMIParse = E_PARSE_START_TIME;
            goto _MApp_MPlayer_Parse_Next_Class;
        }
    }

    return bRet;
}
#endif  // #if (ENABLE_SUBTITLE_SMI)

#if (ENABLE_SUBTITLE_TXT)
//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_TXT_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define TXT_TIME_STAMP_LEN  8

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enTMPlayerParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32ParsingTime=0;
    U32 u32CacheParsed=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    BOOLEAN bNeedTrans2Unicode=FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {

        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_TXT_Parser_END; //not found TMPlayer
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                                (LOBYTE(pu16Cache[u32CacheParsed+1]) == ':' )&&
                                (LOBYTE(pu16Cache[u32CacheParsed+4]) == ':' )&&
                                (LOBYTE(pu16Cache[u32CacheParsed+7]) == ':' )&&
                                (pu16Cache[u32CacheParsed+TXT_TIME_STAMP_LEN] != 0x000D && pu16Cache[u32CacheParsed+TXT_TIME_STAMP_LEN] != 0x000A))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    for(i=0;i<TXT_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TXTPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour1, &u32Min1, &u32Sec1))
                    {
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTMPlayerParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld\n", u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enTMPlayerParse= E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode==TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TXT_Parser_END;
            }
        }
    }
    else
    {
        while((m_u32CurSubtitleFilePos+ u32CacheParsed) < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_TXT_Parser_END; //not found TMPlayer
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                               (pu8Cache[u32CacheParsed+1] == ':')&&
                               (pu8Cache[u32CacheParsed+4] == ':')&&
                               (pu8Cache[u32CacheParsed+7] == ':')&&
                               (pu8Cache[u32CacheParsed+TXT_TIME_STAMP_LEN] != '\r' && pu8Cache[u32CacheParsed+TXT_TIME_STAMP_LEN+1] != '\n'))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_TXTPlayerScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1, &u32Sec1))
                    {
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTMPlayerParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld\n", u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enTMPlayerParse= E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TXT_Parser_END;
            }
        }
    }

_MApp_MPlayer_TXT_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_TXT;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_TXT_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define TXT_TIME_STAMP_LEN  8

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enTMPlayerParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32PrevTagPos=0;
    U32 u32TagStart=0;
    U32 u32LineOneLength=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    U32 u32TextParseMax;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_TXT_Parser_END;
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                                (LOBYTE(pu16Cache[u32CacheParsed+1]) == ':')&&
                                (LOBYTE(pu16Cache[u32CacheParsed+4]) == ':')&&
                                (LOBYTE(pu16Cache[u32CacheParsed+7]) == ':')&&
                                (pu16Cache[u32CacheParsed+TXT_TIME_STAMP_LEN] != 0x000D &&
                                pu16Cache[u32CacheParsed+TXT_TIME_STAMP_LEN+1] != 0x000A))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    for(i=0;i<TXT_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TXTPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour1, &u32Min1, &u32Sec1))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                        u32CacheParsed += TXT_TIME_STAMP_LEN;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTMPlayerParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                    for(i=u32CacheParsed;i<u32TextParseMax;i++)
                    {
                        if(LOBYTE(pu16Cache[i]) == '\n')
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i*2) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    u32LineOneLength = (u32CacheParsed-u32TagStart)*2;// save the length of Line 1 to calculate the address of line 2
                    pu16Cache[u32CacheParsed++] = 0x0000;
                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], (u32CacheParsed-u32TagStart)*2);
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    u32TagStart = u32CacheParsed;
                    enTMPlayerParse = E_PARSE_END_TIME_LINE1;
                    break;
                case E_PARSE_END_TIME_LINE1:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) == ':')&&
                           (LOBYTE(pu16Cache[u32CacheParsed+4]) == ':')&&
                           (LOBYTE(pu16Cache[u32CacheParsed+7]) == ':'))
                        {
                            break;
                        }
                    }
                    for(i=0;i<TXT_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TXTPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2))
                    {
                        u32CacheParsed += TXT_TIME_STAMP_LEN+2;
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        goto _MApp_MPlayer_TXT_Parser_END;
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enTMPlayerParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enTMPlayerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTMPlayerParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_TXT_Parser_END;
            }
        }

    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_TXT_Parser_END;
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] == ':') &&
                           (pu8Cache[u32CacheParsed+4] == ':') &&
                           (pu8Cache[u32CacheParsed+7] == ':') &&
                           (pu8Cache[u32CacheParsed+TXT_TIME_STAMP_LEN] != '\r') &&
                           (pu8Cache[u32CacheParsed+TXT_TIME_STAMP_LEN+1] != '\n'))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_TXTPlayerScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1, &u32Sec1))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                        u32CacheParsed += TXT_TIME_STAMP_LEN;
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTMPlayerParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                    for(i=u32CacheParsed;i<u32TextParseMax;i++)
                    {
                        if(pu8Cache[i] == '\n')
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    u32LineOneLength = (u32CacheParsed-u32TagStart); // save the length of Line 1 to calculate the address of line 2
                    pu8Cache[u32CacheParsed++] = '\0';
                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], (u32CacheParsed-u32TagStart));
                    u32TagStart = u32CacheParsed;
                    enTMPlayerParse = E_PARSE_END_TIME_LINE1;
                    break;
                case E_PARSE_END_TIME_LINE1:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] == ':') &&
                           (pu8Cache[u32CacheParsed+4] == ':') &&
                           (pu8Cache[u32CacheParsed+7] == ':'))
                        {
                            break;
                        }
                    }
                    for(i=0;i<TXT_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu8Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TXTPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2))
                    {
                        u32CacheParsed += TXT_TIME_STAMP_LEN+2;
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        goto _MApp_MPlayer_TXT_Parser_END;
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enTMPlayerParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                // Read the next block of data.
                if(enTMPlayerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTMPlayerParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_TXT_Parser_END;
            }
        }
    }

_MApp_MPlayer_TXT_Parser_END:
    return eRet;
}


//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_TMPlayer_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define TMPLAYER_TIME_STAMP_LEN  11

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enTMPlayerParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32ParsingTime=0;
    U32 u32CacheParsed=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    BOOLEAN bNeedTrans2Unicode=FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {

        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_TMPlayer_Parser_END; //not found TMPlayer
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':' && LOBYTE(pu16Cache[u32CacheParsed+9]) == '1') &&
                           (pu16Cache[u32CacheParsed+11] != 0x000D && pu16Cache[u32CacheParsed+11] != 0x000A))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour1, &u32Min1, &u32Sec1, 1))
                    {
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTMPlayerParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld\n", u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enTMPlayerParse= E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode==TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TMPlayer_Parser_END;
            }
        }
    }
    else
    {
        while((m_u32CurSubtitleFilePos+ u32CacheParsed) < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_TMPlayer_Parser_END; //not found TMPlayer
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':') && (pu8Cache[u32CacheParsed+9] == '1') &&
                           (pu8Cache[u32CacheParsed+11] != '\r' && pu8Cache[u32CacheParsed+12] != '\n'))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1, &u32Sec1, 1))
                    {
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTMPlayerParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld\n", u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enTMPlayerParse= E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TMPlayer_Parser_END;
            }
        }
    }

_MApp_MPlayer_TMPlayer_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_TMPLAYER;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_TMPlayer_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define TMPLAYER_TIME_STAMP_LEN  11

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enTMPlayerParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32PrevTagPos=0;
    U32 u32TagStart=0;
    U32 u32LineOneLength=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    U32 u32TextParseMax;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_TMPlayer_Parser_END;
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':' && LOBYTE(pu16Cache[u32CacheParsed+9]) == '1') &&
                           (pu16Cache[u32CacheParsed+11] != 0x000D && pu16Cache[u32CacheParsed+12] != 0x000A))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour1, &u32Min1, &u32Sec1, 1))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTMPlayerParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                    for(i=u32CacheParsed;i<u32TextParseMax;i++)
                    {
                        if(LOBYTE(pu16Cache[i]) == '\n')
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i*2) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    u32LineOneLength = (u32CacheParsed-u32TagStart)*2;// save the length of Line 1 to calculate the address of line 2
                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], (u32CacheParsed-u32TagStart)*2);

                    //skip the timestamp of line 2
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':' && LOBYTE(pu16Cache[u32CacheParsed+9]) == '2'))
                        {
                            break;
                        }
                    }
                    u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                    u32TagStart = u32CacheParsed;
                    enTMPlayerParse = E_PARSE_SUB_LINE2;
                    break;
                case E_PARSE_SUB_LINE2:
                    if(u32LineOneLength < SUBTITLE_MAX_SIZE - END_OF_LINE_SIZE)
                    {
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE-u32LineOneLength)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                        for(i=u32CacheParsed;i<u32TextParseMax;i++)
                        {
                            if(LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n')
                            {
                                break;
                            }
                            if(LOBYTE(pu16Cache[i]) == '\n')
                            {
                                break;
                            }
                            if ((m_u32CurSubtitleFilePos+i*2) >= u32FileSize)
                            {
                                break;
                            }
                        }
                        u32CacheParsed = i;
                    }
                    pu16Cache[u32CacheParsed] = '\0';
                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32LineOneLength), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+1-u32TagStart)*2);
                    u32TagStart = u32CacheParsed;
                    enTMPlayerParse = E_PARSE_END_TIME_LINE1;
                    break;
                case E_PARSE_END_TIME_LINE1:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':'))
                        {
                            break;
                        }
                    }
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2, 1))
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN+2;
                        enTMPlayerParse = E_PARSE_END_TIME_LINE2;
                    }
                    else
                    {
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }
                    break;
                case E_PARSE_END_TIME_LINE2:
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2, 2))
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }

                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enTMPlayerParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));

                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enTMPlayerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTMPlayerParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_TMPlayer_Parser_END;
            }
        }

    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_TMPlayer_Parser_END;
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':' && pu8Cache[u32CacheParsed+9] == '1')&&
                           (pu8Cache[u32CacheParsed+11] != '\r' && pu8Cache[u32CacheParsed+12] != '\n'))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1, &u32Sec1, 1))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTMPlayerParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                    for(i=u32CacheParsed;i<u32TextParseMax;i++)
                    {
                        if(pu8Cache[i] == '\n')
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    u32LineOneLength = (u32CacheParsed-u32TagStart); // save the length of Line 1 to calculate the address of line 2
                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], (u32CacheParsed-u32TagStart));

                    //skip the timestamp of line 2
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':' && pu8Cache[u32CacheParsed+9] == '2'))
                        {
                            break;
                        }
                    }
                    u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                    u32TagStart = u32CacheParsed;
                    enTMPlayerParse = E_PARSE_SUB_LINE2;
                    break;
                case E_PARSE_SUB_LINE2:
                    if(u32LineOneLength < (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2)
                    {
                        u32TextParseMax = MIN((u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2 - u32LineOneLength), SUBTITLE_USED_READ_BUF_LEN);
                        for(i=u32CacheParsed;i<u32TextParseMax;i++)
                        {
                            if(LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n')
                            {
                                break;
                            }
                            if(pu8Cache[i] == '\n')
                            {
                                break;
                            }
                            if ((m_u32CurSubtitleFilePos+i) >= u32FileSize)
                            {
                                break;
                            }
                        }
                        u32CacheParsed = i;
                    }
                    pu8Cache[u32CacheParsed] = '\0';
                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32LineOneLength), (void*)&pu8Cache[u32TagStart], (u32CacheParsed+1-u32TagStart));
                    u32TagStart = u32CacheParsed;
                    enTMPlayerParse = E_PARSE_END_TIME_LINE1;
                    break;
                case E_PARSE_END_TIME_LINE1:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':'))
                        {
                            break;
                        }
                    }
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu8Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2, 1))
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN+2;
                        enTMPlayerParse = E_PARSE_END_TIME_LINE2;
                    }
                    else
                    {
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }
                    break;
                case E_PARSE_END_TIME_LINE2:
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu8Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2, 2))
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enTMPlayerParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                // Read the next block of data.
                if(enTMPlayerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTMPlayerParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_TMPlayer_Parser_END;
            }
        }
    }

_MApp_MPlayer_TMPlayer_Parser_END:
    return eRet;
}

//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_TTXT_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define TEXTSAMPLE_TAG              "<TextSample"
    #define TEXTSAMPLE_TAG_UNICODE      "<\0T\0e\0x\0t\0S\0a\0m\0p\0l\0e\0"
    #define TEXTSAMPLE_START_TAG_LEN    24
    #define TTXT_TIME_STAMP_LEN         12

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enTTXTParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32ParsingTime=0;
    U32 u32CacheParsed=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    BOOLEAN bNeedTrans2Unicode=FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {

        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_TTXT_Parser_END;//not found Subviewer
            }

            switch(enTTXTParse)
            {
                case E_PARSE_INIT:
                    if(memcmp(&pu16Cache[u32CacheParsed], TEXTSAMPLE_TAG_UNICODE, sizeof(TEXTSAMPLE_TAG_UNICODE)-1)==0)
                    {
                        enTTXTParse = E_PARSE_START_TIME;
                        u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;
                        break;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;
                case E_PARSE_START_TIME:
                    // Check if time stamp.
                    for(i=0;i<TTXT_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[0],
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        enTTXTParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTTXTParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Unicode Tag %ld %ld %ld,%ld\n", u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enTTXTParse= E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                if(bNeedTrans2Unicode==TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TTXT_Parser_END;
            }

        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed > SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_TTXT_Parser_END;//not found Subviewer
            }

            switch(enTTXTParse)
            {
                case E_PARSE_INIT:
                    if(memcmp(&pu8Cache[u32CacheParsed], TEXTSAMPLE_TAG, sizeof(TEXTSAMPLE_TAG)-1)==0)
                    {
                        enTTXTParse = E_PARSE_START_TIME;
                        u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;
                        break;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        enTTXTParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTTXTParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld\n", u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enTTXTParse= E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TTXT_Parser_END;
            }
        }
    }

_MApp_MPlayer_TTXT_Parser_END:
    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_TTXT;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_TTXT_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define TEXTSAMPLE_TAG              "<TextSample"
    #define TEXTSAMPLE_TAG_UNICODE      "<\0T\0e\0x\0t\0S\0a\0m\0p\0l\0e\0"
    #define TEXT_START_TAG              "text="
    #define TEXT_START_TAG_UNICODE      "t\0e\0x\0t\0=\0"
    #define TEXT_END_TAG                "</TextSample"
    #define TEXT_END_TAG_UNICODE        "<\0/\0T\0e\0x\0t\0S\0a\0m\0p\0l\0e\0"
    #define TEXT_FILE_END               "</TextStream"
    #define TEXT_FILE_END_UNICODE       "<\0/\0T\0e\0x\0t\0S\0t\0r\0e\0a\0m\0"
    #define TEXTSAMPLE_START_TAG_LEN    24
    #define TTXT_TIME_STAMP_LEN         12

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enTTXTParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32PrevTagPos=0;
    U32 u32TagStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    U32 u32TextParseMax;
    BOOLEAN bTTXT10=FALSE;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_TTXT_Parser_END;
            }

            switch(enTTXTParse)
            {
                case E_PARSE_INIT:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], TEXTSAMPLE_TAG_UNICODE, sizeof(TEXTSAMPLE_TAG_UNICODE)-1)==0)
                        {
                            break;
                        }
                    }
                    u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                    enTTXTParse = E_PARSE_START_TIME;
                    u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;
                    break;
                case E_PARSE_START_TIME:
                    // Check if time stamp.
                    for(i=0;i<TTXT_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[0],
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32CacheParsed += TTXT_TIME_STAMP_LEN;
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                        for(i=u32CacheParsed;i<u32TextParseMax;i++)
                        {
                            // check TTXT version
                            if(LOBYTE(pu16Cache[i]) == '>')
                            {
                                u32CacheParsed = i+1;
                                break;
                            }

                            if(memcmp(&pu16Cache[i], TEXT_START_TAG_UNICODE, sizeof(TEXT_START_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed = i + (sizeof(TEXT_START_TAG_UNICODE)-1)/2+1; //to the first position after TEXT_START_TAG_UNICODE
                                bTTXT10 = TRUE;
                                break;
                            }
                        }
                        u32TagStart = u32CacheParsed;
                        enTTXTParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTTXTParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    if(bTTXT10)
                    {
                        BOOLEAN bParseLine = FALSE;
                        U32 u32CacheSaved = 0;

                        for(;u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                        {
                            if(pu16Cache[u32CacheParsed] == 0x0022) // quotation mark (")
                            {
                                break;
                            }

                            //current parsed and saved characters number >= the max size of subtitle - END_OF_Line size
                            if((u32CacheParsed-u32TagStart+u32CacheSaved) >= (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2 && bParseLine)
                            {
                                memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32CacheSaved*2), (void*)&pu16Cache[u32TagStart], (u32CacheParsed-u32TagStart)*2);
                                u32CacheSaved += (u32CacheParsed-u32TagStart);
                                break;
                            }
                            else if(pu16Cache[u32CacheParsed] == 0x0027 && !bParseLine) //first ' of one line
                            {
                                u32TagStart = u32CacheParsed+1;
                                bParseLine = TRUE;
                            }
                            else if(pu16Cache[u32CacheParsed] == 0x0027 && bParseLine) //last ' of one line
                            {
                                //replace ' to line feed
                                pu16Cache[u32CacheParsed] = 0x000A;
                                memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32CacheSaved*2), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+1-u32TagStart)*2);
                                u32CacheSaved += (u32CacheParsed+1-u32TagStart);
                                bParseLine = FALSE;
                            }
                        }

                        pu16Cache[u32CacheParsed] = '\0'; // save the last \0
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32CacheSaved*2), (void*)&pu16Cache[u32CacheParsed], 2);
                        u32TagStart = u32CacheParsed;
                        enTTXTParse = E_PARSE_END_TIME_LINE1;
                    }
                    else //TTXT 1.1
                    {
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                        for(;u32CacheParsed<u32TextParseMax;u32CacheParsed++)
                        {
                            if(memcmp(&pu16Cache[u32CacheParsed], TEXT_END_TAG_UNICODE, sizeof(TEXT_END_TAG_UNICODE)-1)==0)
                            {
                                break;
                            }
                        }

                        pu16Cache[u32CacheParsed] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], (u32CacheParsed-u32TagStart+1)*2);
                        u32TagStart = u32CacheParsed;
                        enTTXTParse = E_PARSE_END_TIME_LINE1;
                    }
                    break;
                case E_PARSE_END_TIME_LINE1:
                case E_PARSE_END_TIME_LINE2:
                    if(memcmp(&pu16Cache[u32CacheParsed], TEXTSAMPLE_TAG_UNICODE, sizeof(TEXTSAMPLE_TAG_UNICODE)-1)==0)
                    {
                        u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;

                        for(i=0;i<TTXT_TIME_STAMP_LEN;i++)
                        {
                            pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                        }

                        if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[0],
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2))
                        {
                            enTTXTParse = E_PARSE_DONE;
                            u32CacheParsed -= TEXTSAMPLE_START_TAG_LEN;
                        }
                    }
                    else if(memcmp(&pu16Cache[u32CacheParsed], TEXT_FILE_END_UNICODE, sizeof(TEXT_FILE_END_UNICODE)-1)==0)
                    {
                        //for the last line without end time
                        u32Hour2 = u32Hour1;
                        u32Min2 =  u32Min1;
                        u32Sec2 = u32Sec1 + LAST_SUBTITLE_DISPLAY_TIME;
                        u32ms2 = u32ms1;
                        enTTXTParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enTTXTParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enTTXTParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTTXTParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_TTXT_Parser_END;
            }
        }
    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_TTXT_Parser_END;
            }

            switch(enTTXTParse)
            {
                case E_PARSE_INIT:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], TEXTSAMPLE_TAG, sizeof(TEXTSAMPLE_TAG)-1)==0)
                        {
                            break;
                        }
                    }

                    u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                    enTTXTParse = E_PARSE_START_TIME;
                    u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32CacheParsed += TTXT_TIME_STAMP_LEN;
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE), SUBTITLE_USED_READ_BUF_LEN);
                        for(i=u32CacheParsed;i<u32TextParseMax;i++)
                        {
                            // check TTXT version
                            if(LOBYTE(pu8Cache[i]) == '>')
                            {
                                u32CacheParsed = i+1;
                                break;
                            }

                            if(memcmp(&pu8Cache[i], TEXT_START_TAG, sizeof(TEXT_START_TAG)-1)==0)
                            {
                                u32CacheParsed = i + sizeof(TEXT_START_TAG);//to the first position after TEXT_START_TAG
                                bTTXT10 = TRUE;
                                break;
                            }
                        }
                        u32TagStart = u32CacheParsed;
                        enTTXTParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTTXTParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    if(bTTXT10)
                    {
                        BOOLEAN bParseLine = FALSE;
                        U32 u32CacheSaved = 0;

                        for(;u32CacheParsed<SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                        {
                            if(pu8Cache[u32CacheParsed] == 0x22) // quotation mark (")
                            {
                                break;
                            }

                            //current parsed + saved >= the max size of subtitle
                            if((u32CacheParsed-u32TagStart+u32CacheSaved) >= (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2 && bParseLine)
                            {
                                memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32CacheSaved), (void*)&pu8Cache[u32TagStart], (u32CacheParsed-u32TagStart));
                                u32CacheSaved += (u32CacheParsed-u32TagStart);
                                break;
                            }
                            else if(pu8Cache[u32CacheParsed] == 0x27 && !bParseLine) //first ' of one line
                            {
                                u32TagStart = u32CacheParsed+1;
                                bParseLine = TRUE;
                            }
                            else if(pu8Cache[u32CacheParsed] == 0x27 && bParseLine) //last ' of one line
                            {
                                //replace ' to line feed
                                pu8Cache[u32CacheParsed] = '\n';
                                memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32CacheSaved), (void*)&pu8Cache[u32TagStart], (u32CacheParsed+1-u32TagStart));
                                u32CacheSaved += (u32CacheParsed+1-u32TagStart);
                                bParseLine = FALSE;
                            }
                        }

                        pu8Cache[u32CacheParsed] = '\0'; // save the last \0
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr+u32CacheSaved), (void*)&pu8Cache[u32CacheParsed], 1);
                        u32TagStart = u32CacheParsed;
                        enTTXTParse = E_PARSE_END_TIME_LINE1;
                    }
                    else //TTXT 1.1
                    {
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE), SUBTITLE_USED_READ_BUF_LEN);
                        for(;u32CacheParsed<u32TextParseMax;u32CacheParsed++)
                        {
                            if(memcmp(&pu8Cache[u32CacheParsed], TEXT_END_TAG, sizeof(TEXT_END_TAG)-1)==0)
                            {
                                break;
                            }
                        }

                        pu8Cache[u32CacheParsed] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], (u32CacheParsed-u32TagStart+1));
                        u32TagStart = u32CacheParsed;
                        enTTXTParse = E_PARSE_END_TIME_LINE1;
                    }
                    break;
                case E_PARSE_END_TIME_LINE1:
                case E_PARSE_END_TIME_LINE2:
                    if(memcmp(&pu8Cache[u32CacheParsed], TEXTSAMPLE_TAG, sizeof(TEXTSAMPLE_TAG)-1)==0)
                    {
                        u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;

                        if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2))
                        {
                            enTTXTParse = E_PARSE_DONE;
                            u32CacheParsed -= TEXTSAMPLE_START_TAG_LEN;
                        }
                    }
                    else if(memcmp(&pu8Cache[u32CacheParsed], TEXT_FILE_END, sizeof(TEXT_FILE_END)-1)==0)
                    {
                        //for the last line without end time
                        u32Hour2 = u32Hour1;
                        u32Min2 =  u32Min1;
                        u32Sec2 = u32Sec1 + 5;
                        u32ms2 = u32ms1;
                        enTTXTParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enTTXTParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                // Read the next block of data.
                if(enTTXTParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTTXTParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_TTXT_Parser_END;
            }
        }
    }

_MApp_MPlayer_TTXT_Parser_END:
    return eRet;
}
#endif //#if (ENABLE_SUBTITLE_TXT)

#if (ENABLE_SUBTITLE_SUB)
//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SubViewer_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define SUBVIEWER10_TIME_STAMP_LEN  10
    #define SUBVIEWER20_TIME_STAMP_LEN  23

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enSubViewerParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32CacheParsed=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    BOOLEAN bSubViewer20=FALSE;
    BOOLEAN bNeedTrans2Unicode=FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    // Parse the time

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_SubViewer_Parser_END;//not found Subviewer
            }

            switch(enSubViewerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':'))
                        {
                            if(LOBYTE(pu16Cache[u32CacheParsed+8])== '.' && LOBYTE(pu16Cache[u32CacheParsed+11])== ',')
                            {
                                bSubViewer20 = TRUE;
                                enSubViewerParse = E_PARSE_START_TIME;
                                break;
                            }
                            else if(u32CacheParsed>0)
                            {
                                if(LOBYTE(pu16Cache[u32CacheParsed-1])== '[' && LOBYTE(pu16Cache[u32CacheParsed+8])== ']')
                                {
                                    bSubViewer20 = FALSE;
                                    enSubViewerParse = E_PARSE_START_TIME;
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    for(i=0;i<SUBVIEWER20_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(bSubViewer20)
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)",", '.', 2) == 8)
                        {
                            enSubViewerParse = E_PARSE_DONE;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    else
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)"#", ']', 1) == 3)
                        {
                            enSubViewerParse = E_PARSE_DONE;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Unicode Tag %ld %ld %ld,%ld\n", u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enSubViewerParse = E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                if(bNeedTrans2Unicode==TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SubViewer_Parser_END;
            }
        }
    }
    else
    {
        while((m_u32CurSubtitleFilePos+ u32CacheParsed) < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed > SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_SubViewer_Parser_END;//not found Subviewer
            }

            switch(enSubViewerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':'))
                        {
                            if(pu8Cache[u32CacheParsed+8]== '.' && pu8Cache[u32CacheParsed+11]== ',')
                            {
                                bSubViewer20 = TRUE;
                                enSubViewerParse = E_PARSE_START_TIME;
                                break;
                            }
                            else if(u32CacheParsed>0)
                            {
                                if(pu8Cache[u32CacheParsed-1]== '[' && pu8Cache[u32CacheParsed+8]== ']')
                                {
                                    bSubViewer20 = FALSE;
                                    enSubViewerParse = E_PARSE_START_TIME;
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(bSubViewer20)
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                   &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                   &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                   (U8*)",", '.', 2) == 8)
                        {
                            enSubViewerParse = E_PARSE_DONE;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    else
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)"#", ']', 1) == 3)
                        {
                            enSubViewerParse = E_PARSE_DONE;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld\n", u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enSubViewerParse = E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SubViewer_Parser_END;
            }
        }
    }

_MApp_MPlayer_SubViewer_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBVIEWER;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }

    return bRet;//TRUE;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_SubViewer_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define SUBVIEWER10_TIME_STAMP_LEN  10
    #define SUBVIEWER20_TIME_STAMP_LEN  23

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enSubViewerParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32PrevTagPos=0;
    U32 u32TagStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    BOOLEAN bSubViewer20=FALSE;
    U32 u32TextParseMax;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SubViewer_Parser_END;
            }

            switch(enSubViewerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':'))
                        {
                            if(LOBYTE(pu16Cache[u32CacheParsed+8])== '.' && LOBYTE(pu16Cache[u32CacheParsed+11])== ',')
                            {
                                bSubViewer20 = TRUE;
                                enSubViewerParse = E_PARSE_START_TIME;
                                break;
                            }
                            else if(u32CacheParsed>0)
                            {
                                if(LOBYTE(pu16Cache[u32CacheParsed-1])== '[' && LOBYTE(pu16Cache[u32CacheParsed+8])== ']')
                                {
                                    bSubViewer20 = FALSE;
                                    enSubViewerParse = E_PARSE_START_TIME;
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    for(i=0;i<SUBVIEWER20_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(bSubViewer20)
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)",", '.', 2) == 8)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            u32CacheParsed += SUBVIEWER20_TIME_STAMP_LEN;
                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            u32TagStart = u32CacheParsed;
                            enSubViewerParse = E_PARSE_SUB_LINE1;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    else
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)"#", ']', 1) == 3)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + (u32CacheParsed-1)*2;// subtract 1 for the left [ of start time
                            u32CacheParsed += SUBVIEWER10_TIME_STAMP_LEN;
                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            u32TagStart = u32CacheParsed;
                            enSubViewerParse = E_PARSE_SUB_LINE1;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    if(bSubViewer20)
                    {
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                        for(i=u32CacheParsed;i<u32TextParseMax;i++)
                        {
                            if((LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n') &&
                               (LOBYTE(pu16Cache[i+2]) == '\r' && LOBYTE(pu16Cache[i+3]) == '\n'))
                            {
                                break;
                            }
                            if(LOBYTE(pu16Cache[i]) == '\n' && LOBYTE(pu16Cache[i+1]) == '\n')
                            {
                                break;
                            }
                            if ((LOBYTE(pu16Cache[i]) == '\r') && (LOBYTE(pu16Cache[i+1]) == '\n') && ((m_u32CurSubtitleFilePos+(i+2)*2) >= u32FileSize))
                            {
                                break;
                            }
                            if ((m_u32CurSubtitleFilePos+i*2) >= u32FileSize)
                            {
                                break;
                            }
                        }
                        u32CacheParsed = i;
                        pu16Cache[u32CacheParsed] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+1-u32TagStart)*2);
                        enSubViewerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                        for(i=u32CacheParsed;i<u32TextParseMax;i++)
                        {
                            if((LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n'))
                            {
                                break;
                            }
                            if(LOBYTE(pu16Cache[i]) == '\n')
                            {
                                break;
                            }
                            if ((m_u32CurSubtitleFilePos+i*2) >= u32FileSize)
                            {
                                break;
                            }
                        }
                        u32CacheParsed = i;
                        pu16Cache[u32CacheParsed] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+1-u32TagStart)*2);
                        enSubViewerParse = E_PARSE_END_TIME_LINE1;
                    }
                    break;
                case E_PARSE_END_TIME_LINE1:
                case E_PARSE_END_TIME_LINE2:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':'))
                        {
                            break;
                        }
                    }

                    for(i=0;i<SUBVIEWER10_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                &u32ms1, &u32ms1, &u32ms1, &u32ms1,
                                                (U8*)"#", ']', 1) == 3)
                    {
                        u32CacheParsed += SUBVIEWER10_TIME_STAMP_LEN;
                        enSubViewerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_SubViewer_Parser_END;
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enSubViewerParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enSubViewerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSubViewerParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SubViewer_Parser_END;
            }
        }
    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_SubViewer_Parser_END;
            }

            switch(enSubViewerParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':'))
                        {
                            if(pu8Cache[u32CacheParsed+8]== '.' && pu8Cache[u32CacheParsed+11]== ',')
                            {
                                bSubViewer20 = TRUE;
                                enSubViewerParse = E_PARSE_START_TIME;
                                break;
                            }
                            else if(u32CacheParsed>0)
                            {
                                if(pu8Cache[u32CacheParsed-1]== '[' && pu8Cache[u32CacheParsed+8]== ']')
                                {
                                    bSubViewer20 = FALSE;
                                    enSubViewerParse = E_PARSE_START_TIME;
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(bSubViewer20)
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)",", '.', 2) == 8)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            u32CacheParsed += SUBVIEWER20_TIME_STAMP_LEN;
                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            u32TagStart = u32CacheParsed;
                            enSubViewerParse = E_PARSE_SUB_LINE1;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    else
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)"#", ']', 1) == 3)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + (u32CacheParsed-1);// subtract 1 for the left [ of start time
                            u32CacheParsed += SUBVIEWER10_TIME_STAMP_LEN;
                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            u32TagStart = u32CacheParsed;
                            enSubViewerParse = E_PARSE_SUB_LINE1;
                        }
                        else
                        {
                            //u32ParsedPos += u16CacheParsed;
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    if(bSubViewer20)
                    {
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                        for(i=u32CacheParsed;i<u32TextParseMax;i++)
                        {
                            if((pu8Cache[i] == '\r' && pu8Cache[i+1] == '\n') &&
                               (pu8Cache[i+2] >= '\r' && pu8Cache[i+3] <= '\n'))
                            {
                                break;
                            }
                            if(pu8Cache[i] == '\n' && pu8Cache[i+1] == '\n')
                            {
                                break;
                            }
                            if ((pu8Cache[i] == '\r') && (pu8Cache[i+1] == '\n') && ((m_u32CurSubtitleFilePos+i+2) >= u32FileSize))
                            {
                                break;
                            }
                            if ((m_u32CurSubtitleFilePos+i) >= u32FileSize)
                            {
                                break;
                            }
                        }
                        u32CacheParsed = i;
                        pu8Cache[u32CacheParsed] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], (u32CacheParsed+1-u32TagStart));
                        enSubViewerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                        for(i=u32CacheParsed;i<u32TextParseMax;i++)
                        {
                            if(pu8Cache[i] == '\r' && pu8Cache[i+1] == '\n')
                            {
                                break;
                            }
                            if(pu8Cache[i] == '\n')
                            {
                                break;
                            }
                            if ((m_u32CurSubtitleFilePos+i) >= u32FileSize)
                            {
                                break;
                            }
                        }
                        u32CacheParsed = i;
                        pu8Cache[u32CacheParsed] = '\0';
                        memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], (u32CacheParsed+1-u32TagStart));
                        enSubViewerParse = E_PARSE_END_TIME_LINE1;
                    }
                    break;
                case E_PARSE_END_TIME_LINE1:
                case E_PARSE_END_TIME_LINE2:
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':'))
                        {
                            break;
                        }
                    }

                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                &u32ms1, &u32ms1, &u32ms1, &u32ms1,
                                                (U8*)"#", ']', 1) == 3)
                    {
                        u32CacheParsed += SUBVIEWER10_TIME_STAMP_LEN;
                        enSubViewerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_SubViewer_Parser_END;
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enSubViewerParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                // Read the next block of data.
                if(enSubViewerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSubViewerParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SubViewer_Parser_END;
            }
        }
    }

_MApp_MPlayer_SubViewer_Parser_END:

    return eRet;
}


//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SubRipper_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define SUBRIPPER_TIMETAG                   "{T "
    #define SUBRIPPER_TIMETAG_LEN               3
    #define SUBRIPPER_TIMETAG_UNICODE           "{\0T\0 \0"
    #define SUBRIPPER_TIMETAG_UNICODE_LEN       6
    #define SUBRIPPER_HEADER                   "{HEAD"
    #define SUBRIPPER_HEADER_LEN               5
    #define SUBRIPPER_HEADER_UNICODE           "{\0H\0E\0A\0D\0"
    #define SUBRIPPER_HEADER_UNICODE_LEN       10
    #define SUBRIPPER_MAX_TIMELENGTH        12
    #define SUBTITLE_CACHE_SIZE            1024

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    enumMPlayerSubtitleParse enSubRipperParse = E_PARSE_IDENTIFIER;
    U32 u32CacheParsed=0;
    U32 u32ParsingTime=0;
    BOOLEAN bNeedTrans2Unicode = FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;
    U32 u32PrevTagPos=0;
    U32 i = 0;
    U32 u32SubRipperTimeLen = 0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    U32 u32Hour1 = 0;
    U32 u32Min1 = 0;
    U32 u32Sec1 = 0;
    U32 u32ms1 = 0;

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_SubRipper_Parser_END;//not found SubRipper
            }

            switch(enSubRipperParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], SUBRIPPER_HEADER_UNICODE, SUBRIPPER_HEADER_UNICODE_LEN)==0)
                        {
                            enSubRipperParse = E_PARSE_INIT;
                            u32CacheParsed += (SUBRIPPER_HEADER_UNICODE_LEN/2);
                            break;
                        }
                    }
                    break;
                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], SUBRIPPER_TIMETAG_UNICODE, SUBRIPPER_TIMETAG_UNICODE_LEN)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            enSubRipperParse = E_PARSE_START_TIME;
                            u32CacheParsed += (SUBRIPPER_TIMETAG_UNICODE_LEN/2);
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<SUBRIPPER_MAX_TIMELENGTH;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }
                    if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[0], &u32SubRipperTimeLen,
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32CacheParsed += u32SubRipperTimeLen*2;
                        enSubRipperParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enSubRipperParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    // do rescale in MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enSubRipperParse = E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = m_u16SubtitleTagCount*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
                enSubRipperParse = E_PARSE_INIT;
            }
            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SubRipper_Parser_END;
            }
        }

    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_SubRipper_Parser_END;//not found SubRipper
            }

            switch(enSubRipperParse)
            {

                case E_PARSE_IDENTIFIER:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN -3) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize -3);u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed],SUBRIPPER_HEADER,SUBRIPPER_HEADER_LEN)==0)
                        {
                            enSubRipperParse = E_PARSE_INIT;
                            u32CacheParsed +=SUBRIPPER_HEADER_LEN;
                            break;
                        }
                    }
                    break;
                case E_PARSE_INIT:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN-3) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize-3);u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed],SUBRIPPER_TIMETAG,SUBRIPPER_TIMETAG_LEN)==0)
                        {
                            enSubRipperParse = E_PARSE_START_TIME;
                            u32CacheParsed +=SUBRIPPER_TIMETAG_LEN;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[u32CacheParsed],&u32SubRipperTimeLen, &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32CacheParsed += u32SubRipperTimeLen;
                        enSubRipperParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enSubRipperParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32ms1));
                    enSubRipperParse = E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
                enSubRipperParse = E_PARSE_INIT;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SubRipper_Parser_END;
            }
        }
    }

_MApp_MPlayer_SubRipper_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBRIPPER;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }
    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_SubRipper_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{

    #define SUBRIPPER_TIMETAG                   "{T "
    #define SUBRIPPER_TIMETAG_LEN               3
    #define SUBRIPPER_TIMETAG_UNICODE           "{\0T\0 \0"
    #define SUBRIPPER_TIMETAG_UNICODE_LEN       6
    #define SURIPPER_LINE_END                   "}"
    #define SURIPPER_LINE_END_LEN               1
    #define SURIPPER_LINE_END_UNICODE           "}\0"
    #define SURIPPER_LINE_END_UNICODE_LEN       2
    #define SUBRIPPER_MAX_TIMELENGTH            12

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    enumMPlayerSubtitleParse enSubRipperParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32PrevTagPos=0;
    U32 u32TagStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    U32 i =0;
    U32 u32TextParseMax;
    U32 u32SubRipperTimeLen = 0;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();

    U32 u32EndLine1Index = 0;

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {

        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if( (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize) || (m_u32CurSubtitleFilePos + u32EndLine1Index*2 >= u32FileSize))
            {
                if(enSubRipperParse==E_PARSE_END_TIME_LINE1)
                {
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = 0xFFFFFFFF;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                }
                else
                {
                    eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                }
                goto _MApp_MPlayer_SubRipper_ParserOne_END;
            }

            switch(enSubRipperParse)
            {
                case E_PARSE_INIT:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], SUBRIPPER_TIMETAG_UNICODE, SUBRIPPER_TIMETAG_UNICODE_LEN)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            enSubRipperParse = E_PARSE_START_TIME;
                            u32CacheParsed += (SUBRIPPER_TIMETAG_UNICODE_LEN/2);
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    // Check if time stamp.
                    for(i=0;i<SUBRIPPER_MAX_TIMELENGTH;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[0], &u32SubRipperTimeLen,
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32CacheParsed += u32SubRipperTimeLen;
                        enSubRipperParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed+=2;
                        enSubRipperParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                    u32TagStart = u32CacheParsed;
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                    for(;u32CacheParsed<u32TextParseMax;u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed],SURIPPER_LINE_END_UNICODE,SURIPPER_LINE_END_UNICODE_LEN)==0)
                        {
                            pu16Cache[u32CacheParsed] = '\0';
                            memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+1-u32TagStart)*2);
                            enSubRipperParse = E_PARSE_END_TIME_LINE1;
                            u32CacheParsed ++;
                            break;
                        }
                    }
                    break;
                case E_PARSE_END_TIME_LINE1:
                    u32EndLine1Index = u32CacheParsed;
                    u32SubRipperTimeLen = 0;
                    for(;(u32EndLine1Index<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32EndLine1Index < u32FileSize);u32EndLine1Index++)
                    {
                        if(memcmp(&pu16Cache[u32EndLine1Index], SUBRIPPER_TIMETAG_UNICODE, SUBRIPPER_TIMETAG_UNICODE_LEN)==0)
                        {
                            u32EndLine1Index += (SUBRIPPER_TIMETAG_UNICODE_LEN/2);

                            for(i=0;i<SUBRIPPER_MAX_TIMELENGTH;i++)
                            {
                                pu8Cache[i] = LOBYTE(pu16Cache[u32EndLine1Index+i]);
                            }

                            if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[0], &u32SubRipperTimeLen,
                                                &u32Hour2, &u32Min2, &u32Sec2, &u32ms2)==FALSE)
                            {
                                u32Hour2 = u32Hour1;
                                u32Min2 = u32Min1;
                                u32Sec2 = u32Sec1;
                                u32ms2 = u32ms1;
                            }
                            enSubRipperParse = E_PARSE_DONE;
                            break;
                        }
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enSubRipperParse  = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if((u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)  || (u32EndLine1Index >=SUBTITLE_USED_READ_BUF_LEN/2))
            {
                // Read the next block of data.
                if(enSubRipperParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else if(enSubRipperParse==E_PARSE_END_TIME_LINE1)
                {
                    m_u32CurSubtitleFilePos += u32EndLine1Index*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSubRipperParse  = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                u32EndLine1Index = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SubRipper_ParserOne_END;
            }
        }
    }
    else
    {
        while(bFindSubtitle==FALSE)
        {

            if((m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize) || (m_u32CurSubtitleFilePos + u32EndLine1Index >= u32FileSize))
            {
                if(enSubRipperParse==E_PARSE_END_TIME_LINE1)
                {
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = 0xFFFFFFFF;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                }
                else
                {
                    eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                }
                goto _MApp_MPlayer_SubRipper_ParserOne_END;
            }

            switch(enSubRipperParse)
            {
                case E_PARSE_INIT:
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], SUBRIPPER_TIMETAG, SUBRIPPER_TIMETAG_LEN)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            enSubRipperParse = E_PARSE_START_TIME;
                            u32CacheParsed += SUBRIPPER_TIMETAG_LEN;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[u32CacheParsed], &u32SubRipperTimeLen,
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32CacheParsed += u32SubRipperTimeLen;
                        enSubRipperParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enSubRipperParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                    u32TagStart = u32CacheParsed;
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                    for(;u32CacheParsed<u32TextParseMax;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed],SURIPPER_LINE_END,SURIPPER_LINE_END_LEN)==0)
                        {
                            pu8Cache[u32CacheParsed] = '\0';
                            memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], (u32CacheParsed+1-u32TagStart));
                            enSubRipperParse = E_PARSE_END_TIME_LINE1;
                            u32CacheParsed ++;
                            break;
                        }
                    }

                    break;
                case E_PARSE_END_TIME_LINE1:
                    u32EndLine1Index = u32CacheParsed;
                    u32SubRipperTimeLen = 0;
                    for(;(u32EndLine1Index<=SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + u32EndLine1Index < u32FileSize);u32EndLine1Index++)
                    {
                        if(memcmp(&pu8Cache[u32EndLine1Index], SUBRIPPER_TIMETAG, SUBRIPPER_TIMETAG_LEN)==0)
                        {
                            u32EndLine1Index += SUBRIPPER_TIMETAG_LEN;
                            if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[u32EndLine1Index], &u32SubRipperTimeLen,
                                                &u32Hour2, &u32Min2, &u32Sec2, &u32ms2)==FALSE)
                            {
                                u32Hour2 = u32Hour1;
                                u32Min2 = u32Min1;
                                u32Sec2 = u32Sec1;
                                u32ms2 = u32ms1;
                            }
                            enSubRipperParse = E_PARSE_DONE;
                            break;
                        }
                    }
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    u32SubRipperTimeLen = 0;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enSubRipperParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32Sec1, u32ms1, u32Hour2, u32Min2, u32Sec2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN || u32EndLine1Index >=SUBTITLE_USED_READ_BUF_LEN)
            {
                // Read the next block of data.
                if(enSubRipperParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else if(enSubRipperParse==E_PARSE_END_TIME_LINE1)
                {
                    m_u32CurSubtitleFilePos += u32EndLine1Index;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSubRipperParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                u32EndLine1Index = 0;

            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_SubRipper_ParserOne_END;
            }
        }
    }

_MApp_MPlayer_SubRipper_ParserOne_END:
    return eRet;
}


//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_MicroDVD_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define SUBTITLE_CACHE_SIZE     1024

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 i;
    U32 u32TimeStart=0, u32TimeEnd=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    U32 u32SubtitleOffset=0;
    BOOLEAN bFound, bFirstTag=TRUE;
    enumMPlayerSubtitleParse enMicroDVDParse = E_PARSE_INIT;
    U32 u32CacheParsed=0;
    U32 u32TagStart=0;
    U32 u32ParsingTime=0;
    BOOLEAN bNeedTrans2Unicode = FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    // Parse the time
    #define MICRODVD_TIME_STAMP_LEN  24 //assume max 24

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_MicroDVD_Parser_END;//not found MicroDVD
            }

            switch(enMicroDVDParse)
            {
                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) == '{') && (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9'))
                        {
                            enMicroDVDParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<MICRODVD_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_MicroDVDScanfTime(&pu8Cache[0], &u32SubtitleOffset, &u32TimeStart, &u32TimeEnd))
                    {
                        if(bFirstTag)
                        {
                           u32CacheParsed += u32SubtitleOffset;
                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            u32TagStart = u32CacheParsed;

    	                    bFound = FALSE;
    	                    for(i=u32CacheParsed;i<=(SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET)/2;i++)
    	                    {
    	                        if(LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n')
    	                        {
    	                            bFound = TRUE;
    	                            break;
    	                        }
    	                    }

    	                    if(bFound)
    	                    {
	                            //Check first tag is valid frame rate informatoin or not  , ex:only {1}{1} frame is valid otherwise , it should use movie frame rate information
	                            if(u32TimeStart==1 && u32TimeEnd==1)
	                            {
	                                U8 au8Temp[MICRODVD_TIME_STAMP_LEN];

	                                for(i=0;i<MICRODVD_TIME_STAMP_LEN;i++)
	                                {
	                                    au8Temp[i] = LOBYTE(pu16Cache[u32TagStart+i]);
	                                }
	                                _MApp_MPlayer_MicroDVDScanfFrameRate(&au8Temp[0], &m_u32MicroDVDFrameRate);
	                                enMicroDVDParse = E_PARSE_INIT;
	                            }
    	                        bFirstTag = FALSE;
    	                    }
                        }
                        else
                        {
                            enMicroDVDParse = E_PARSE_DONE;
                        }
                    }
                    else
                    {
                        u32CacheParsed++;
                        enMicroDVDParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    // do rescale in MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime
                    pu32Index[m_u16SubtitleTagCount] = u32TimeStart;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld --> %ld \n", m_u16SubtitleTagCount, u32TimeStart, u32TimeEnd));
                    enMicroDVDParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = m_u16SubtitleTagCount*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
                enMicroDVDParse = E_PARSE_INIT;
            }
            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_MicroDVD_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_MicroDVD_Parser_END;//not found MicroDVD
            }

            switch(enMicroDVDParse)
            {
                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize);u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] == '{') && (pu8Cache[u32CacheParsed+1] >= '0') && (pu8Cache[u32CacheParsed+1] <= '9'))
                        {
                            enMicroDVDParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    if(_MApp_MPlayer_MicroDVDScanfTime(&pu8Cache[u32CacheParsed], &u32SubtitleOffset, &u32TimeStart, &u32TimeEnd))
                    {
                        if(bFirstTag)
                        {
                            u32CacheParsed += u32SubtitleOffset;
                            SUBTITLE_SKIP_SPACE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            u32TagStart = u32CacheParsed;
    	                    bFound = FALSE;
    	                    for(;u32CacheParsed<=(SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);u32CacheParsed++)
    	                    {
    	                        if((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
    	                        {
    	                            bFound = TRUE;
    	                            break;
    	                        }
    	                    }

    	                    if(bFound)
    	                    {
	                            //Check first tag is valid frame rate informatoin or not  , ex:only {1}{1} frame is valid otherwise , it should use movie frame rate information
	                            if(u32TimeStart==1 && u32TimeEnd==1)
	                            {
	                                _MApp_MPlayer_MicroDVDScanfFrameRate(&pu8Cache[u32TagStart], &m_u32MicroDVDFrameRate);
	                                enMicroDVDParse = E_PARSE_INIT;
	                            }
	                            bFirstTag = FALSE;
	                        }
	                    }
                        else
                        {
                            enMicroDVDParse = E_PARSE_DONE;
                        }

                    }
                    else
                    {
                        u32CacheParsed++;
                        enMicroDVDParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_DONE:
                    // do rescale in MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime
                    pu32Index[m_u16SubtitleTagCount] = u32TimeStart;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld --> %ld \n", m_u16SubtitleTagCount, u32TimeStart, u32TimeEnd));
                    enMicroDVDParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount]=0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]=pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
                enMicroDVDParse = E_PARSE_INIT;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_MicroDVD_Parser_END;
            }
        }
    }

_MApp_MPlayer_MicroDVD_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_MICRODVD;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_MicroDVD_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define SUBTITLE_CACHE_SIZE     1024

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    U32 i;
    U32 u32TimeStart=0, u32TimeEnd=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32SubtitleOffset=0;
    BOOLEAN bFound, bFirstTag=FALSE; //bFirstTag in ParserOneSubtitle always set FALSE
    enumMPlayerSubtitleParse enMicroDVDParse = E_PARSE_INIT;
    U32 u32PrevTagPos=0;
    U32 u32TagStart=0;
    U32 u32ParsingTime=0;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    U32 u32TextParseMax = 0;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    // Parse the time
    #define MICRODVD_TIME_STAMP_LEN  24 //assume max 24

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_MicroDVD_Parser_END;
            }

            switch(enMicroDVDParse)
            {
                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) == '{') && (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9'))
                        {
                            enMicroDVDParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<MICRODVD_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_MicroDVDScanfTime(&pu8Cache[0], &u32SubtitleOffset, &u32TimeStart, &u32TimeEnd))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                        u32CacheParsed += u32SubtitleOffset;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        u32TagStart = u32CacheParsed;
                        enMicroDVDParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enMicroDVDParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    bFound = FALSE;
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                    for(i=u32CacheParsed;i<u32TextParseMax;i++)
                    {
                        if(LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n')
                        {
                            bFound = TRUE;
                            break;
                        }
                    }

                    u32CacheParsed = i;

                    if(bFound)
                    {
                        if(bFirstTag)
                        {
                            //Check first tag is valid frame rate informatoin or not  , ex:only {1}{1} frame is valid otherwise , it should use movie frame rate information
                            if(u32TimeStart==1 && u32TimeEnd==1)
                            {
                                U8 au8Temp[MICRODVD_TIME_STAMP_LEN];

                                for(i=0;i<MICRODVD_TIME_STAMP_LEN;i++)
                                {
                                    au8Temp[i] = LOBYTE(pu16Cache[u32TagStart+i]);
                                }
                                _MApp_MPlayer_MicroDVDScanfFrameRate(&au8Temp[0], &m_u32MicroDVDFrameRate);
                                enMicroDVDParse = E_PARSE_INIT;
                            }
                            bFirstTag = FALSE;
                        }
                        else
                        {
                            pu16Cache[u32CacheParsed] = '\0';
                            memcpy( (void*)_PA2VA( u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+1-u32TagStart)*2);
                            enMicroDVDParse = E_PARSE_DONE;
                        }
                    }
                    break;

                case E_PARSE_DONE:
                    // Using m_u32MicroDVDFrameRate decided in MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime() to do rescale
                    pSubtitleTag->u32TimeStart  = (U32)(((float)u32TimeStart/m_u32MicroDVDFrameRate)*1000000);
                    pSubtitleTag->u32TimeEnd  = (U32)(((float)u32TimeEnd/m_u32MicroDVDFrameRate)*1000000);
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enMicroDVDParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld --> %ld \n", pSubtitleTag->u32TimeStart, pSubtitleTag->u32TimeEnd));
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enMicroDVDParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enMicroDVDParse = E_PARSE_INIT;
                }

                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_MicroDVD_Parser_END;
            }
        }
    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_MicroDVD_Parser_END;
            }

            switch(enMicroDVDParse)
            {
                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;u32CacheParsed<=SUBTITLE_USED_READ_BUF_LEN;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] == '{') && (pu8Cache[u32CacheParsed+1] >= '0') && (pu8Cache[u32CacheParsed+1] <= '9'))
                        {
                            enMicroDVDParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    if(_MApp_MPlayer_MicroDVDScanfTime(&pu8Cache[u32CacheParsed], &u32SubtitleOffset, &u32TimeStart, &u32TimeEnd))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                        u32CacheParsed += u32SubtitleOffset;
                        SUBTITLE_SKIP_SPACE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        u32TagStart = u32CacheParsed;
                        enMicroDVDParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enMicroDVDParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    bFound = FALSE;
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                    for(i=u32CacheParsed;i<u32TextParseMax;i++)
                    {
                        if((pu8Cache[i] == '\r') && (pu8Cache[i+1] == '\n'))
                        {
                            bFound = TRUE;
                            break;
                        }
                    }

                    u32CacheParsed = i;

                    if(bFound)
                    {
                        if(bFirstTag)
                        {
                            //Check first tag is valid frame rate informatoin or not  , ex:only {1}{1} frame is valid otherwise , it should use movie frame rate information
                            if(u32TimeStart==1 && u32TimeEnd==1)
                            {
                                _MApp_MPlayer_MicroDVDScanfFrameRate(&pu8Cache[u32TagStart], &m_u32MicroDVDFrameRate);
                                enMicroDVDParse = E_PARSE_INIT;
                            }
                            bFirstTag = FALSE;
                        }
                        else
                        {
                            pu8Cache[u32CacheParsed] = '\0';
                            memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], u32CacheParsed+1-u32TagStart);
                            enMicroDVDParse = E_PARSE_DONE;
                        }
                    }
                    break;

                case E_PARSE_DONE:
                    // Using m_u32MicroDVDFrameRate decided in MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime() to do rescale
                    pSubtitleTag->u32TimeStart  = (U32)(((float)u32TimeStart/m_u32MicroDVDFrameRate)*1000000);
                    pSubtitleTag->u32TimeEnd  = (U32)(((float)u32TimeEnd/m_u32MicroDVDFrameRate)*1000000);
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enMicroDVDParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld --> %ld \n", pSubtitleTag->u32TimeStart, pSubtitleTag->u32TimeEnd));
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                // Read the next block of data.
                if(enMicroDVDParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enMicroDVDParse = E_PARSE_INIT;
                }

                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_MicroDVD_Parser_END;
            }
        }
    }

_MApp_MPlayer_MicroDVD_Parser_END:

    return eRet;
}

//******************************************************************************
/// parse all file to get every first start time in SUBTITLE_READ_BUF
/// @param  u32FileSize \b IN Specify file size
/// @param  pCodingType \b OUT content coding type(ex: UNICODE, UTF8, ASCII)
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_DvdSubtitleSystem_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define DVDSUBTITLE_TIME_STAMP_LEN  23

    //bRet: check if subtitle is parsed before time out.
    //bSubtitleFoundInBuff: check if there is a subtitle in used read buffer.
    BOOLEAN bRet = FALSE, bSubtitleFoundInBuff = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enDvdSubtitleParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32CacheParsed=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 *pu32Index;
    BOOLEAN bNeedTrans2Unicode=FALSE;
    U32 u32OffsetTimesPerIndex, u32SearchLoopCnt=0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    u32OffsetTimesPerIndex = _MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = FALSE;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu32Index = (U32*) _PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8SubtitleTrackNum*PER_SUBTITLE_INDEX_SIZE);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].bBE2LE = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
    }
    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+SUBTITLE_CACHE_OFFSET);

        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_DVDSubtileSystem_Parser_END;//not found DvdSubtitle
            }

            switch(enDvdSubtitleParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_USED_READ_BUF_LEN/2;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                           (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                           (LOBYTE(pu16Cache[i+2]) == ':' ) && (LOBYTE(pu16Cache[i+5]) == ':' ) && (LOBYTE(pu16Cache[i+8]) == ':' ) &&
                           (LOBYTE(pu16Cache[i+11]) == ' ') &&
                           (LOBYTE(pu16Cache[i+14]) == ':' ) && (LOBYTE(pu16Cache[i+17]) == ':' ) && (LOBYTE(pu16Cache[i+20]) == ':' ))
                        {
                            enDvdSubtitleParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    break;
                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<DVDSUBTITLE_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }
                    pu8Cache[DVDSUBTITLE_TIME_STAMP_LEN] = '\0';
                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" ", ':', 2) == 8)
                    {
                        enDvdSubtitleParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed += DVDSUBTITLE_TIME_STAMP_LEN;
                        enDvdSubtitleParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    enDvdSubtitleParse = E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount] = 0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]= pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;

                if(bNeedTrans2Unicode==TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_DVDSubtileSystem_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN))
            {
                goto _MApp_MPlayer_DVDSubtileSystem_Parser_END;//not found DvdSubtitle
            }

            switch(enDvdSubtitleParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_USED_READ_BUF_LEN;i++)
                    {
                        if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                           (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                           (pu8Cache[i+2] == ':' ) && (pu8Cache[i+5] == ':' ) && (pu8Cache[i+8] == ':' ) &&
                           (pu8Cache[i+11] == ' ') &&
                           (pu8Cache[i+14] == ':' ) && (pu8Cache[i+17] == ':' ) && (pu8Cache[i+20] == ':' ))
                        {
                            enDvdSubtitleParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" ", ':', 2) == 8)
                    {
                        enDvdSubtitleParse = E_PARSE_DONE;
                    }
                    else
                    {
                        u32CacheParsed += DVDSUBTITLE_TIME_STAMP_LEN;
                        enDvdSubtitleParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_DONE:
                    pu32Index[m_u16SubtitleTagCount] = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    bRet = TRUE;
                    bSubtitleFoundInBuff = TRUE;
                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    enDvdSubtitleParse = E_PARSE_INIT;
                    break;
                default:
                    break;
            }

            if(bSubtitleFoundInBuff == TRUE || u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(bSubtitleFoundInBuff == FALSE)
                {
                    u32SearchLoopCnt++;

                    if(u32SearchLoopCnt == u32OffsetTimesPerIndex)
                    {
                        // no subtitle tag in this range
                        if(m_u16SubtitleTagCount==0)
                        {
                            pu32Index[m_u16SubtitleTagCount] = 0;
                        }
                        else
                        {
                            pu32Index[m_u16SubtitleTagCount]= pu32Index[m_u16SubtitleTagCount-1];
                        }
                        SMALL_BUF_PARSER_DBG(printf("pu32Index[%d]=%d\n", m_u16SubtitleTagCount, pu32Index[m_u16SubtitleTagCount]));
                        m_u16SubtitleTagCount++;
                        u32SearchLoopCnt=0;
                    }
                }
                else
                {
                    m_u16SubtitleTagCount++;
                    u32SearchLoopCnt=0;
                }

                // Read the next block of data.
                m_u32CurSubtitleFilePos = (m_u16SubtitleTagCount*u32OffsetTimesPerIndex+u32SearchLoopCnt)*SUBTITLE_USED_READ_BUF_LEN;
                SMALL_BUF_PARSER_DBG(printf("----------> loopcnt %d read next block %ld \n", u32SearchLoopCnt, m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
                bSubtitleFoundInBuff = FALSE;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_DVDSubtileSystem_Parser_END;
            }
        }
    }

_MApp_MPlayer_DVDSubtileSystem_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_DVDSUBTITLESYSTEM;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        memcpy(&m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].stFileEntry, &FileEntrySubtitle, sizeof(FileEntry));
        m_u8SubtitleTrackNum++;
    }

    return bRet;
}

//******************************************************************************
/// parse one subtitle information
/// @param  pSubtitleTag \b OUT subtitle tag information
/// @param  u32SubtitlePhyAddr \b OUT one subtitle
/// @return EN_PARSE_ONE_SUBTITLE_RET: return parser status
//******************************************************************************
static EN_PARSE_ONE_SUBTITLE_RET _MApp_MPlayer_DvdSubtitleSystem_ParseOneSubtitle(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr)
{
    #define SUBTITLE_CACHE_SIZE     1024
    #define DVDSUBTITLE_TIME_STAMP_LEN  23

    EN_PARSE_ONE_SUBTITLE_RET eRet = E_PARSE_ONE_SUBTITLE_FAIL;

    if(pSubtitleTag == NULL || u32SubtitlePhyAddr == NULL)
    {
        return eRet;
    }

    BOOLEAN bFindSubtitle = FALSE;
    U32 i;
    enumMPlayerSubtitleParse enDvdSubtitleParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32PrevTagPos=0;
    U32 u32TagStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    enumMplayerSubtitleCoding eUnicodeFile = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;
    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32CacheParsed = m_u32SubtitleBufParsed;
    U32 u32TextParseMax = 0;
    U32 u32CahceSize;

    pu8Cache  = (U8*)  _PA2VA(SUBTITLE_READ_BUF_ADDR);
    pu16Cache = (U16*) _PA2VA(SUBTITLE_READ_BUF_ADDR);

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(eUnicodeFile == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        BOOLEAN bNeedTrans2Unicode = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE;
        u32CacheParsed /= 2;
        pu8Cache = (U8*) _PA2VA(SUBTITLE_READ_BUF_ADDR+SUBTITLE_USED_READ_BUF_LEN+2048);

        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_DVDSubtileSystem_Parser_END;
            }

            switch(enDvdSubtitleParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_USED_READ_BUF_LEN/2;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                           (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                           (LOBYTE(pu16Cache[i+2]) == ':' ) && (LOBYTE(pu16Cache[i+5]) == ':' ) && (LOBYTE(pu16Cache[i+8]) == ':' ) &&
                           (LOBYTE(pu16Cache[i+11]) == ' ') &&
                           (LOBYTE(pu16Cache[i+14]) == ':' ) && (LOBYTE(pu16Cache[i+17]) == ':' ) && (LOBYTE(pu16Cache[i+20]) == ':' ))
                        {
                            enDvdSubtitleParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    break;
                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<DVDSUBTITLE_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }
                    pu8Cache[DVDSUBTITLE_TIME_STAMP_LEN] = '\0';

                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" ", ':', 2) == 8)
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                        u32CacheParsed += DVDSUBTITLE_TIME_STAMP_LEN;
                        // Skip one space.
                        u32CahceSize = MIN(SUBTITLE_USED_READ_BUF_LEN/2, u32CacheParsed+ SUBTITLE_CACHE_SIZE/2);
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, u32CahceSize);
                        u32TagStart = u32CacheParsed;
                        enDvdSubtitleParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed += DVDSUBTITLE_TIME_STAMP_LEN;
                        enDvdSubtitleParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN/2);
                    for(i=u32CacheParsed;i<u32TextParseMax;i++)
                    {
                        if(LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n')
                        {
                            break;
                        }
                        if(LOBYTE(pu16Cache[i]) == '\n')
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i*2) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    pu16Cache[u32CacheParsed] = '\0';
                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+1-u32TagStart)*2);
                    enDvdSubtitleParse = E_PARSE_DONE;
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed*2;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enDvdSubtitleParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN/2)
            {
                // Read the next block of data.
                if(enDvdSubtitleParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enDvdSubtitleParse = E_PARSE_INIT;
                }

                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_READ_BUF_LEN);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_DVDSubtileSystem_Parser_END;
            }
        }
    }
    else
    {
        while(bFindSubtitle==FALSE)
        {
            if(m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)
            {
                eRet = E_PARSE_ONE_SUBTITLE_FILE_END;
                goto _MApp_MPlayer_DVDSubtileSystem_Parser_END;
            }

            switch(enDvdSubtitleParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_USED_READ_BUF_LEN;i++)
                    {
                        if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                           (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                           (pu8Cache[i+2] == ':' ) && (pu8Cache[i+5] == ':' ) && (pu8Cache[i+8] == ':' ) &&
                           (pu8Cache[i+11] == ' ') &&
                           (pu8Cache[i+14] == ':' ) && (pu8Cache[i+17] == ':' ) && (pu8Cache[i+20] == ':' ))
                        {
                            enDvdSubtitleParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" ", ':', 2) == 8)
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                        u32CacheParsed += DVDSUBTITLE_TIME_STAMP_LEN;
                        // Skip one space.
                        u32CahceSize = MIN(SUBTITLE_USED_READ_BUF_LEN, u32CacheParsed+ SUBTITLE_CACHE_SIZE);
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, u32CahceSize);
                        u32TagStart = u32CacheParsed;
                        enDvdSubtitleParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed += DVDSUBTITLE_TIME_STAMP_LEN;
                        enDvdSubtitleParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    u32TextParseMax = MIN(u32CacheParsed + (SUBTITLE_MAX_SIZE-END_OF_LINE_SIZE)/2, SUBTITLE_USED_READ_BUF_LEN);
                    for(i=u32CacheParsed;i<u32TextParseMax;i++)
                    {
                        if(pu8Cache[i] == '\r' && pu8Cache[i+1] == '\n')
                        {
                            break;
                        }
                        if(pu8Cache[i] == '\n')
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    pu8Cache[u32CacheParsed] = '\0';
                    memcpy( (void*)_PA2VA(u32SubtitlePhyAddr), (void*)&pu8Cache[u32TagStart], (u32CacheParsed+1-u32TagStart));
                    enDvdSubtitleParse = E_PARSE_DONE;
                    break;
                case E_PARSE_DONE:
                    pSubtitleTag->u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pSubtitleTag->u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pSubtitleTag->u32SubtitlePos = u32SubtitlePhyAddr;
                    m_u32SubtitleBufParsed = u32CacheParsed;
                    bFindSubtitle = TRUE;
                    eRet = E_PARSE_ONE_SUBTITLE_DONE;
                    enDvdSubtitleParse = E_PARSE_INIT;
                    SMALL_BUF_PARSER_DBG(printf("Tag %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    break;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_USED_READ_BUF_LEN)
            {
                if(enDvdSubtitleParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enDvdSubtitleParse = E_PARSE_INIT;
                }
                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %ld\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > ONE_SUBTITLE_PARSING_TIMEOUT)
            {
                eRet = E_PARSE_ONE_SUBTITLE_TIME_OUT;
                goto _MApp_MPlayer_DVDSubtileSystem_Parser_END;
            }
        }
    }

_MApp_MPlayer_DVDSubtileSystem_Parser_END:

    return eRet;
}

#endif //#if (ENABLE_SUBTITLE_SUB)
#else  //#if (ENABLE_SMALL_BUF_SUBTITLE)

static BOOLEAN _MApp_MPlayer_SRT_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define SUBTITLE_CACHE_SIZE     1024
    #define TIME_STAMP_LEN  29

    BOOLEAN bRet = FALSE;
    U32 i;
    MPlayer_Subtitle_Tag *pTag;
    enumMPlayerSubtitleParse enSRTParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U32 u32ParsingTime=0;
    U32 u32SubtitlePos=0, u32PrevSubPos=0,  u32CacheParsed=0, u32PrevTagPos=0;
    U32 u32TagStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    BOOLEAN bUnicodeFile=FALSE, bNeedTrans2Unicode=FALSE;
    U32 u32TextParseMax = 0;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        bUnicodeFile=TRUE;
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(bUnicodeFile)
    {
        pu8Cache = (U8*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);

        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 <= u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_SRT_Parser_END; //not found SRT
            }

            switch(enSRTParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_SMALL_BUF_SIZE/2;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                           (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                           (LOBYTE(pu16Cache[i+2]) == ':'))
                        {
                            enSRTParse = E_PARSE_START_TIME;
                            break;
                        }
                    }

                    if((bRet == FALSE) && (i >= SUBTITLE_SMALL_BUF_SIZE/2))
                    {
                        goto _MApp_MPlayer_SRT_Parser_END; //not found SRT
                    }

                    u32CacheParsed = i;
                    break;

                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }
                    pu8Cache[TIME_STAMP_LEN] = '\0';

                    if((_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", ',', 2) == 8)||
                       (_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", '.', 2) == 8))
                    {
                        U32 u32CahceSize;
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                        u32CacheParsed += TIME_STAMP_LEN;
                        // 3.1 Skip one line feed.
                        u32CahceSize = MIN(SUBTITLE_SMALL_BUF_SIZE/2, u32CacheParsed+ SUBTITLE_CACHE_SIZE/2);
                        SUBTITLE_SKIP_ONELINEFEED_UNICODE(pu16Cache, u32CacheParsed, u32CahceSize);
                        u32TagStart = u32CacheParsed;
                        enSRTParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed += TIME_STAMP_LEN;
                        enSRTParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    for(i=u32CacheParsed;i<=SUBTITLE_SMALL_BUF_SIZE/2;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n') &&
                           (LOBYTE(pu16Cache[i+2]) >= '\r' && LOBYTE(pu16Cache[i+3]) <= '\n'))
                        {
                            break;
                        }
                        if(LOBYTE(pu16Cache[i]) == '\n' && LOBYTE(pu16Cache[i+1]) == '\n')
                        {
                            break;
                        }
                        if ((LOBYTE(pu16Cache[i]) == '\r') && (LOBYTE(pu16Cache[i+1]) == '\n') && ((m_u32CurSubtitleFilePos+(i+2)*2) >= u32FileSize))
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i*2) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    pu16Cache[u32CacheParsed] = '\0';
                    pu16Cache[u32CacheParsed+1] = '\0';
                    memcpy( (void*)_PA2VA(SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);
                    u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                    enSRTParse = E_PARSE_DONE;
                    break;

                case E_PARSE_DONE:
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    u32CacheParsed+=2;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;

                    SMALL_BUF_PARSER_DBG(printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2));
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {
                        goto _MApp_MPlayer_SRT_Parser_END;
                    }
                    enSRTParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
            {   // Read the next block of data.
                if(enSRTParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSRTParse = E_PARSE_INIT;
                }

                SMALL_BUF_PARSER_DBG(printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos));
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode==TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SRT_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed <= u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_SRT_Parser_END; //not found SRT
            }

            switch(enSRTParse)
            {
                case E_PARSE_INIT:
                    for(i=u32CacheParsed;i<=SUBTITLE_SMALL_BUF_SIZE;i++)
                    {
                        if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                           (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                           (pu8Cache[i+2] == ':'))
                        {
                            enSRTParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    u32CacheParsed = i;

                    if((bRet == FALSE) && (i>=SUBTITLE_SMALL_BUF_SIZE))
                    {
                        // Cannot find subtitle.
                        goto _MApp_MPlayer_SRT_Parser_END;
                    }
                    break;

                case E_PARSE_START_TIME:
                    if((_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", ',', 2) == 8)||
                       (_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" --> ", '.', 2) == 8))
                    {
                        U32 u32CahceSize;
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                        u32CacheParsed += TIME_STAMP_LEN;
                        // 3.1 Skip one line feed.
                        u32CahceSize = MIN(SUBTITLE_SMALL_BUF_SIZE, u32CacheParsed+ SUBTITLE_CACHE_SIZE);
                        SUBTITLE_SKIP_ONELINEFEED(pu8Cache, u32CacheParsed, u32CahceSize);

                        u32TagStart = u32CacheParsed;
                        enSRTParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed += TIME_STAMP_LEN;
                        enSRTParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    u32TextParseMax = MIN(u32CacheParsed + SUBTITLE_MAX_SIZE, SUBTITLE_SMALL_BUF_SIZE - 4);
                    for(i=u32CacheParsed;i<=u32TextParseMax;i++)
                    {
                        if((pu8Cache[i] == '\r' && pu8Cache[i+1] == '\n') &&
                           (pu8Cache[i+2] >= '\r' && pu8Cache[i+3] <= '\n'))
                        {
                            break;
                        }
                        if(pu8Cache[i] == '\n' && pu8Cache[i+1] == '\n')
                        {
                            break;
                        }
                        if ((pu8Cache[i] == '\r') && (pu8Cache[i+1] == '\n') && ((m_u32CurSubtitleFilePos+i+2) >= u32FileSize))
                        {
                            break;
                        }
                        if ((m_u32CurSubtitleFilePos+i) >= u32FileSize)
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    pu8Cache[u32CacheParsed] = '\0';
                    pu8Cache[u32CacheParsed+1] = '\0';
                    memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], (u32CacheParsed+2-u32TagStart));
                    u32SubtitlePos += u32CacheParsed+2-u32TagStart;
                    enSRTParse = E_PARSE_DONE;
                    break;

                case E_PARSE_DONE:
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    u32CacheParsed+=2;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {
                        goto _MApp_MPlayer_SRT_Parser_END;
                    }
                    enSRTParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enSRTParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSRTParse = E_PARSE_INIT;
                }
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SRT_Parser_END;
            }
        }

    }

#if 0
    printf("\n\n*************************************\n\n");
    for(i=0;i<10;i++)
    {
        printf("Time = %ld, %ld, %08lx\n", pTag[i].u32TimeStart, pTag[i].u32TimeEnd, pTag[i].u32SubtitlePos);
    }
    printf("\n\n*************************************\n\n");
#endif

_MApp_MPlayer_SRT_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SRT;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        m_u8SubtitleTrackNum++;

      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
      #endif
    }

    return bRet;
}

#if (ENABLE_SUBTITLE_SUBIDX)
static BOOLEAN _MApp_MPlayer_SUBIDX_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define SUBTITLE_CACHE_SIZE         1024
    #define LANGIDX_TAG                 "langidx:"
    #define DELAY_TAG                   "delay:"
    #define ID_TAG                      "id:"
    #define PALETTE_TAG                 "palette:"
    #define SIZE_TAG                    "size:"
    #define ORG_TAG                     "org:"
    #define TIMESTAMP_TAG               "timestamp:"
    #define CUSTOMER_COLOR_TAG          "custom colors:"
    #define LANGIDX_TAG_UNICODE         "l\0a\0n\0g\0i\0d\0x\0:\0"
    #define DELAY_TAG_UNICODE           "d\0e\0l\0a\0y\0:\0"
    #define ID_TAG_UNICODE              "i\0d\0:\0"
    #define PALETTE_TAG_UNICODE         "p\0a\0l\0e\0t\0t\0e\0:\0"
    #define SIZE_TAG_UNICODE            "s\0i\0z\0e\0:\0"
    #define ORG_TAG_UNICODE             "o\0r\0g\0:\0"
    #define TIMESTAMP_TAG_UNICODE       "t\0i\0m\0e\0s\0t\0a\0m\0p\0:\0"
    #define CUSTOMER_COLOR_TAG_UNICODE  "c\0u\0s\0t\0o\0m\0 \0c\0o\0l\0o\0r\0s\0:\0"
    #define SUBIDX_TIME_STAMP_LEN       13
    #define SUBIDX_TIME_LEN             9
    #define PALETTE_NUM                 16

    U16 i;
    BOOLEAN bRet = FALSE;
    U32 u32Palette[PALETTE_NUM];
    U16 u16PaletteNum;
    U16 u16HexNum;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32CacheParsed=0;
    U32 u32ParsingTime;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    MPlayer_Subtitle_Tag *pTag;
    enumMPlayerSubtitleParse enIdxParse = E_PARSE_IDENTIFIER;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    // Check whether it is Unicode.
    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    enIdxParse = E_PARSE_INIT;

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*)_PA2VA(( ((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            switch(enIdxParse)
            {
                case E_PARSE_INIT:
                    // Find the pallete
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], PALETTE_TAG_UNICODE, sizeof(PALETTE_TAG_UNICODE)-1)==0)
                        {
                            break;
                        }
                        else if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
                        {
                            goto _MApp_MPlayer_SUBIDX_Parser_END;
                        }
                    }

                    memset(u32Palette, 0, PALETTE_NUM*sizeof(U32));
                    u16PaletteNum = 0;

                    u32CacheParsed += sizeof(PALETTE_TAG_UNICODE)/2;
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        // Convert time to ASCII.
                        for(i=0;i<SUBTITLE_CACHE_SIZE/2;i++)
                        {
                            if(ISHEX_UNICODE(pu16Cache[u32CacheParsed+i]))
                            {
                                pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                            }
                            else
                            {
                                pu8Cache[i] = '\0';
                                break;
                            }
                        }

                        u16HexNum = _MApp_MPlayer_ScanHex(&pu8Cache[0],
                                                           &u32Palette[u16PaletteNum]);
                        if(u16HexNum != 0xFFFF)
                        {
                            //printf(" palltet[%d] %lx\n", u16PaletteNum, u32Palette[u16PaletteNum]);
                            u16PaletteNum ++;
                            u32CacheParsed += u16HexNum;
                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            u32CacheParsed++;       // Skip ','
                            if(u16PaletteNum == PALETTE_NUM)
                            {
                                msAPI_MpegSP_SetPalette(u32Palette, 16);
                                u32CacheParsed = 0;
                                enIdxParse = E_PARSE_IDENTIFIER;
                                break;
                            }
                        }
                    }

                    if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
                    {
                        goto _MApp_MPlayer_SUBIDX_Parser_END;
                    }
                    break;

                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], ID_TAG_UNICODE, sizeof(ID_TAG_UNICODE)-1)==0)
                        {
                            // Check the language type.
                            u32CacheParsed += sizeof(ID_TAG_UNICODE)/2;

                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);

                            U32 u32TempSubtitleLang;
                            u32TempSubtitleLang = LOBYTE(pu16Cache[u32CacheParsed+1]);
                            u32TempSubtitleLang = (u32TempSubtitleLang<<8) + LOBYTE(pu16Cache[u32CacheParsed]);
                            m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = u32TempSubtitleLang;

                            enIdxParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    if(memcmp(&pu16Cache[u32CacheParsed], TIMESTAMP_TAG_UNICODE, sizeof(TIMESTAMP_TAG_UNICODE)-1) == 0)
                    {
                        u32CacheParsed += sizeof(TIMESTAMP_TAG_UNICODE)/2;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        // Convert time to ASCII.
                        for(i=0;i<SUBIDX_TIME_STAMP_LEN;i++)
                        {
                            pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                        }
                        pu8Cache[i] = '\0';
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                                    NULL, NULL, NULL, NULL,
                                                    (U8*)",", ':', 1) == 4)
                        {
                            u32CacheParsed += SUBIDX_TIME_STAMP_LEN;
                            SUBTITLE_FIND_DIGIT_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);

                            //if(u32CacheParsed < SUBTITLE_SMALL_BUF_SIZE/2)
                            {
                                // Fill the subtitle tag.
                                pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                                pTag[m_u16SubtitleTagCount].u32TimeEnd = 0xFFFFFFFF;

                                // Convert position to ASCII.
                                for(i=0;i<SUBIDX_TIME_STAMP_LEN;i++)
                                {
                                    if(ISHEX_UNICODE(pu16Cache[u32CacheParsed+i]))
                                    {
                                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                                    }
                                    else
                                    {
                                        pu8Cache[i] = '\0';
                                        break;
                                    }
                                }

                                pTag[m_u16SubtitleTagCount].u32SubtitlePos = _MApp_MPlayer_ScanfIdxPos(&pu8Cache[0]);

                                //printf("Trk%d, Tag[%d] %ld %ld %ld,%ld -> %lx\n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, pTag[m_u16SubtitleTagCount].u32SubtitlePos);

                                m_u16SubtitleTagCount++;
                                u32CacheParsed += i;

                                bRet = TRUE;
                                if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                                {
                                    //printf("Trk%d, Tag[%d] %ld %ld %ld,%ld \n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1);
                                    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
                                    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
                                  #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
                                    qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
                                  #endif
                                    m_u16SubtitleTagCount = 0;
                                    m_u8SubtitleTrackNum++;

                                    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX)
                                    {
                                        goto _MApp_MPlayer_SUBIDX_Parser_END;
                                    }
                                    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA((MP4_SUBTITLE_TAG_ADR+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK));
                                    enIdxParse = E_PARSE_IDENTIFIER;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            u32CacheParsed++;
                        }
                    }
                    else if(memcmp(&pu16Cache[u32CacheParsed], ID_TAG_UNICODE, sizeof(ID_TAG_UNICODE)-1) == 0)
                    {
                        //printf("Trk%d, Tag[%d] %ld %ld %ld,%ld \n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1);
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
                      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
                        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
                      #endif
                        m_u16SubtitleTagCount = 0;
                        m_u8SubtitleTrackNum++;

                        if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX)
                        {
                            goto _MApp_MPlayer_SUBIDX_Parser_END;
                        }
                        pTag = (MPlayer_Subtitle_Tag  *) _PA2VA((MP4_SUBTITLE_TAG_ADR+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK));

                        // Check the language type.
                        u32CacheParsed += sizeof(ID_TAG_UNICODE)/2;

                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);

                        U32 u32TempSubtitleLang;
                        u32TempSubtitleLang = LOBYTE(pu16Cache[u32CacheParsed+1]);
                        u32TempSubtitleLang = (u32TempSubtitleLang<<8) + LOBYTE(pu16Cache[u32CacheParsed]);
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = u32TempSubtitleLang;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
            {   // Read the next block of data.
                m_u32CurSubtitleFilePos += u32CacheParsed*2;
                enIdxParse = E_PARSE_START_TIME;
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SUBIDX_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            switch(enIdxParse)
            {
                case E_PARSE_INIT:
                    // Find the pallete
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], PALETTE_TAG, sizeof(PALETTE_TAG)-1)==0)
                        {
                            break;
                        }
                        else if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
                        {
                            goto _MApp_MPlayer_SUBIDX_Parser_END;
                        }
                    }

                    memset(u32Palette, 0, PALETTE_NUM*sizeof(U32));
                    u16PaletteNum = 0;

                    u32CacheParsed += sizeof(PALETTE_TAG);
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        u16HexNum = _MApp_MPlayer_ScanHex(&pu8Cache[u32CacheParsed],
                                                           &u32Palette[u16PaletteNum]);
                        if(u16HexNum != 0xFFFF)
                        {
                            //printf(" palltet[%d] %lx\n", u16PaletteNum, u32Palette[u16PaletteNum]);
                            u16PaletteNum ++;
                            u32CacheParsed += u16HexNum;
                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            u32CacheParsed++;       // Skip ','
                            if(u16PaletteNum == PALETTE_NUM)
                            {
                                msAPI_MpegSP_SetPalette(u32Palette, 16);
                                u32CacheParsed = 0;
                                enIdxParse = E_PARSE_IDENTIFIER;
                                break;
                            }
                        }
                    }

                    if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
                    {
                        goto _MApp_MPlayer_SUBIDX_Parser_END;
                    }
                    break;

                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], ID_TAG, sizeof(ID_TAG)-1)==0)
                        {
                            // Check the language type.
                            u32CacheParsed += sizeof(ID_TAG);

                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);

                            U32 u32TempSubtitleLang;
                            u32TempSubtitleLang = pu8Cache[u32CacheParsed+1];
                            u32TempSubtitleLang = (u32TempSubtitleLang<<8) + pu8Cache[u32CacheParsed];
                            m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = u32TempSubtitleLang;

                            enIdxParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    if(memcmp(&pu8Cache[u32CacheParsed], TIMESTAMP_TAG, sizeof(TIMESTAMP_TAG)-1) == 0)
                    {
                        u32CacheParsed += sizeof(TIMESTAMP_TAG);
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                                    NULL, NULL, NULL, NULL,
                                                    (U8*)",", ':', 1) == 4)
                        {
                            u32CacheParsed += SUBIDX_TIME_STAMP_LEN;
                            SUBTITLE_FIND_DIGIT(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);

                            //if(u32CacheParsed < SUBTITLE_SMALL_BUF_SIZE)
                            {
                                // Fill the subtitle tag.
                                pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                                pTag[m_u16SubtitleTagCount].u32TimeEnd = 0xFFFFFFFF;

                                pTag[m_u16SubtitleTagCount].u32SubtitlePos = _MApp_MPlayer_ScanfIdxPos(&pu8Cache[u32CacheParsed]);

                                //printf("Trk%d, Tag[%d] %ld %ld %ld,%ld -> %lx\n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, pTag[m_u16SubtitleTagCount].u32SubtitlePos);

                                m_u16SubtitleTagCount++;

                                bRet = TRUE;
                                if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                                {
                                    //printf("Trk%d, Tag[%d] %ld %ld %ld,%ld \n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1);
                                    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
                                    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
                                  #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
                                    qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
                                  #endif
                                    m_u16SubtitleTagCount = 0;
                                    m_u8SubtitleTrackNum++;

                                    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX)
                                    {
                                        goto _MApp_MPlayer_SUBIDX_Parser_END;
                                    }
                                    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA((MP4_SUBTITLE_TAG_ADR+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK));
                                    enIdxParse = E_PARSE_IDENTIFIER;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            u32CacheParsed++;
                        }
                    }
                    else if(memcmp(&pu8Cache[u32CacheParsed], ID_TAG, sizeof(ID_TAG)-1) == 0)
                    {
                        //printf("Trk%d, Tag[%d] %ld %ld %ld,%ld \n", m_u8SubtitleTrackNum, m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1);
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
                      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
                        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
                      #endif
                        m_u16SubtitleTagCount = 0;
                        m_u8SubtitleTrackNum++;

                        if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX)
                        {
                            goto _MApp_MPlayer_SUBIDX_Parser_END;
                        }
                        pTag = (MPlayer_Subtitle_Tag  *) _PA2VA((MP4_SUBTITLE_TAG_ADR+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK));

                        // Check the language type.
                        u32CacheParsed += sizeof(ID_TAG);

                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);

                        U32 u32TempSubtitleLang;
                        u32TempSubtitleLang = pu8Cache[u32CacheParsed+1];
                        u32TempSubtitleLang = (u32TempSubtitleLang<<8) + pu8Cache[u32CacheParsed];
                        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = u32TempSubtitleLang;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                m_u32CurSubtitleFilePos += u32CacheParsed;
                enIdxParse = E_PARSE_START_TIME;
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SUBIDX_Parser_END;
            }
        }
    }

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        m_u8SubtitleTrackNum++;
      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
      #endif
    }

#if 0
    for(i=0;i<20;i++)
    {
        printf("Time = %ld, %ld, %08lx\n", pTag[i].u32TimeStart, pTag[i].u32TimeEnd, pTag[i].u32SubtitlePos);
    }
#endif

_MApp_MPlayer_SUBIDX_Parser_END:

    return bRet;
}
#endif //#if (ENABLE_SUBTITLE_SUBIDX)

static BOOLEAN _MApp_MPlayer_SSA_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define EVENT_TAG               "[Events]"
    #define EVENT_TAG_SIZE          8
    #define DIALOGUE_HEAD           "Dialogue:"
    #define DIALOGUE_HEAD_SIZE      9
    #define EVENT_TAG_UNICODE       "[\0E\0v\0e\0n\0t\0s\0]\0"
    #define DIALOGUE_HEAD_UNICODE   "D\0i\0a\0l\0o\0g\0u\0e\0:\0"
    #define SSA_TIME_STAMP_LEN      21
    #define SKIP_COMMA_NUM          7
    #define COMMA_IN_TIMER          2
    #define SKIP_BRACE_NUM          2

    BOOLEAN bRet = FALSE, bLeftBrace = FALSE;
    U32 i;
    MPlayer_Subtitle_Tag *pTag;
    enumMPlayerSubtitleParse enSSAParse = E_PARSE_INIT;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U32 u32SubtitlePos=0, u32PrevSubPos=0,  u32CacheParsed=0, u32PrevTagPos=0;
    U32 u32TextParseMax = 0;
    U32 u32TagStart=0;
    U32 u32ParsingTime = 0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32SSATimeStampLen = 0, u32CommaInTime = 0, u32SSAToLineEndLen = 0;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32ParsingTime = msAPI_Timer_GetTime0();

    enSSAParse = E_PARSE_IDENTIFIER;
    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 > SUBTITLE_SMALL_BUF_SIZE/2))
            {
                goto _MApp_MPlayer_SSA_Parser_END;//not found SSA
            }

            switch(enSSAParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;(u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(pu16Cache[u32CacheParsed] == 0x005B)    // '['
                        {
                            if(memcmp(&pu16Cache[u32CacheParsed], EVENT_TAG_UNICODE, sizeof(EVENT_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(EVENT_TAG_UNICODE)/2;
                                enSSAParse = E_PARSE_INIT;
                                break;
                            }
                        }
                    }

                    if((bRet == FALSE) && ((u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2) || (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= u32FileSize)))
                    {
                        goto _MApp_MPlayer_SSA_Parser_END; //not found SSA
                    }
                    break;

                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], DIALOGUE_HEAD_UNICODE, sizeof(DIALOGUE_HEAD_UNICODE)-1)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            enSSAParse = E_PARSE_START_TIME;
                            u32CacheParsed += sizeof(DIALOGUE_HEAD_UNICODE)/2;
                            for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                            {
                                if(pu16Cache[u32CacheParsed] == 0x002C) //','
                                {
                                    u32CacheParsed++;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    u32SSATimeStampLen = 0;
                    u32CommaInTime = 0;
                    u32SSAToLineEndLen = 0;

                    //Check if time stamp. check leave condition: buffer size or file size
                    for(i=0;((u32CacheParsed+i) <= SUBTITLE_SMALL_BUF_SIZE/2) && (m_u32CurSubtitleFilePos + (u32CacheParsed+i)*2 < u32FileSize); i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                        if ((pu16Cache[u32CacheParsed+i] == 0x000D) && (pu16Cache[u32CacheParsed+i+1] == 0x000A)) //0x000D '\r', 0x000A '\n'
                        {
                            u32SSAToLineEndLen = i;
                            break;
                        }
                        if(pu8Cache[i] == ',')
                        {
                            u32CommaInTime ++;
                            if(u32CommaInTime == COMMA_IN_TIMER) //timestamp format : 0:00:01.00,0:00:30.00,
                            {
                                u32SSATimeStampLen = i;
                                break;
                            }
                        }
                    }
                    pu8Cache[u32SSATimeStampLen] = '\0';

                    //failed case:
                    //case 1: checking to line end   ==> jump to line end and return INIT state to find next Dialog
                    //case 2: checking to buffer end ==> leave and read more data
                    if(u32CommaInTime != COMMA_IN_TIMER)
                    {
                        //printf("Not found!");
                        if(u32SSAToLineEndLen!=0)
                        {
                            u32CacheParsed += u32SSAToLineEndLen;
                            enSSAParse = E_PARSE_INIT;
                        }
                        else
                        {
                            u32CacheParsed = SUBTITLE_SMALL_BUF_SIZE/2;
                         }
                    }
                    else if(_MApp_MPlayer_ScanfTime((U8*)&pu8Cache[0],
                                                &u32Hour1, &u32Min1,
                                                &u32econd1, &u32ms1,
                                                &u32Hour2, &u32Min2,
                                                &u32econd2, &u32ms2,
                                                (U8*)",", '.', 2) == 8)
                    {

                        //jump to behind the timestamp
                        u32CacheParsed += u32SSATimeStampLen;

                        // Search the texts, skip 7 ','
                        i=0;
                        for(;i < SKIP_COMMA_NUM &&
                             u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE/2;
                             u32CacheParsed++)
                        {
                            if(pu16Cache[u32CacheParsed] == 0x002C)     //','
                            {
                                i++;
                            }
                        }

                        u32TagStart = u32CacheParsed;
                        enSSAParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed += SSA_TIME_STAMP_LEN;
                        enSSAParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    #if 1
                    u32TextParseMax = MIN(u32CacheParsed + SUBTITLE_MAX_SIZE, SUBTITLE_SMALL_BUF_SIZE/2-1);
                    bLeftBrace = FALSE;

                    for(;u32CacheParsed<=u32TextParseMax;u32CacheParsed++)
                    {
                        if(bLeftBrace == FALSE && pu16Cache[u32CacheParsed] == 0x007B)//'{'
                        {
                            if(u32CacheParsed-u32TagStart)
                            {
                                memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], 2*(u32CacheParsed-u32TagStart));
                                u32SubtitlePos +=(u32CacheParsed-u32TagStart)*2;
                                u32TagStart = u32CacheParsed;
                            }
                            bLeftBrace = TRUE;
                        }
                        else if(bLeftBrace == TRUE && pu16Cache[u32CacheParsed] == 0x007D)//'}'
                        {
                            u32TagStart = u32CacheParsed+1;
                            bLeftBrace = FALSE;
                        }
                        else if(pu16Cache[u32CacheParsed] == 0x005C)//'\\'
                        {
                            if(pu16Cache[u32CacheParsed+1] == 0x004E || pu16Cache[u32CacheParsed+1] == 0x006E)//'N','n'
                            {
                                //new line
                                pu16Cache[u32CacheParsed] = 0x000D;     //'\r'
                                pu16Cache[u32CacheParsed+1] = 0x000A;   //'\n'
                                ++u32CacheParsed;
                            }
                            else if(pu16Cache[u32CacheParsed+1] == 0x0068)
                            {
                                //0x1A ascii substitute
                                pu16Cache[u32CacheParsed] = 0x001A;    //hide
                                pu16Cache[u32CacheParsed+1] = 0x001A;  //hide
                                ++u32CacheParsed;
                            }
                        }
                        else if(pu16Cache[u32CacheParsed] == 0x000D && pu16Cache[u32CacheParsed+1] == 0x000A)
                        {
                            break;
                        }
                    }

                    if(u32CacheParsed < SUBTITLE_SMALL_BUF_SIZE/2)
                    {
                        pu16Cache[u32CacheParsed] = '\0';
                        pu16Cache[u32CacheParsed+1] = '\0';
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);
                        u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                        enSSAParse = E_PARSE_DONE;
                    }
                    break;
                    #endif
                    #if 0
                    u32TextParseMax = MIN(u32CacheParsed + SUBTITLE_MAX_SIZE, SUBTITLE_SMALL_BUF_SIZE/2);
                    for(i=u32CacheParsed;i<=u32TextParseMax;i++)
                    {
                        if(LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n')
                        {
                            break;
                        }
                    }

                    u32CacheParsed = i;
                    pu16Cache[u32CacheParsed] = '\0';
                    pu16Cache[u32CacheParsed+1] = '\0';
                    memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);
                    u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                    enSSAParse = E_PARSE_DONE;
                    break;
                    #endif

                case E_PARSE_DONE:
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    u32CacheParsed+=2;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {
                        goto _MApp_MPlayer_SSA_Parser_END;
                    }
                    enSSAParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if((u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize))
            {   // Read the next block of data.
                if(enSSAParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSSAParse = E_PARSE_INIT;
                }
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SSA_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed > SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_SSA_Parser_END;//not found SSA
            }

            switch(enSSAParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;(u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize);u32CacheParsed++)
                    {
                        if(pu8Cache[u32CacheParsed] == '[')    // '['
                        {
                            if(memcmp(&pu8Cache[u32CacheParsed], EVENT_TAG, sizeof(EVENT_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(EVENT_TAG)-1;
                                enSSAParse = E_PARSE_INIT;
                                break;
                            }
                        }
                    }

                    if((bRet == FALSE) && ((u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE) || (m_u32CurSubtitleFilePos + u32CacheParsed >= u32FileSize)))
                    {
                        goto _MApp_MPlayer_SSA_Parser_END; //not found SSA
                    }
                    break;

                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;(u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize) ;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], DIALOGUE_HEAD, sizeof(DIALOGUE_HEAD)-1)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            enSSAParse = E_PARSE_START_TIME;
                            u32CacheParsed += sizeof(DIALOGUE_HEAD)-1;
                            for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                            {
                                if(pu8Cache[u32CacheParsed] == ',') //','
                                {
                                    u32CacheParsed++;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;

                case E_PARSE_START_TIME:
                    u32SSATimeStampLen = 0;
                    u32CommaInTime = 0;
                    u32SSAToLineEndLen = 0;

                    //Check if time stamp. check leave condition: buffer size or file size
                    for(i=0;((u32CacheParsed+i) <= SUBTITLE_SMALL_BUF_SIZE) && (m_u32CurSubtitleFilePos + (u32CacheParsed+i) < u32FileSize);i++)
                    {
                        if ((pu8Cache[u32CacheParsed+i] == '\r') && (pu8Cache[u32CacheParsed+i+1] == '\n'))
                        {
                            u32SSAToLineEndLen = i;
                            break;
                        }
                        if(pu8Cache[u32CacheParsed+i] == ',')
                        {
                            u32CommaInTime ++;
                            if(u32CommaInTime == COMMA_IN_TIMER) //timestamp format : 0:00:01.00,0:00:30.00,
                            {
                                u32SSATimeStampLen = i;
                                break;
                            }
                        }
                    }

                    //failed case:
                    //case 1: checking to line end   ==> jump to line end and return INIT state to find next Dialog
                    //case 2: checking to buffer end ==> leave and read more data
                    if(u32CommaInTime != COMMA_IN_TIMER)
                    {
                        //printf("Not found!");
                        if(u32SSAToLineEndLen!=0)
                        {
                            u32CacheParsed += u32SSAToLineEndLen;
                            enSSAParse = E_PARSE_INIT;
                        }
                        else
                        {
                            u32CacheParsed = SUBTITLE_SMALL_BUF_SIZE;
                        }
                    }
                    else if(_MApp_MPlayer_ScanfTime((U8*)&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1,
                                                &u32econd1, &u32ms1,
                                                &u32Hour2, &u32Min2,
                                                &u32econd2, &u32ms2,
                                                (U8*)",", '.', 2) == 8)
                    {

                        //jump to behind the timestamp
                        u32CacheParsed += u32SSATimeStampLen;

                        // Search the texts, skip 7 ','
                        i=0;
                        for(;i < SKIP_COMMA_NUM &&
                             u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE;
                             u32CacheParsed++)
                        {
                            if(pu8Cache[u32CacheParsed] == ',')     //','
                            {
                                i++;
                            }
                        }
                        #if 0
                        for(i = 0; i <SKIP_BRACE_NUM ;++i)
                        {
                            if(pu8Cache[u32CacheParsed] == '{')
                            {
                                // Skip SSA instructions.
                                for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                                {
                                    if(pu8Cache[u32CacheParsed] == '}')
                                    {
                                        u32CacheParsed++;
                                        break;
                                    }
                                }
                            }
                        }
                        #endif
                        u32TagStart = u32CacheParsed;
                        enSSAParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed += SSA_TIME_STAMP_LEN;
                        enSSAParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    #if 1
                    u32TextParseMax = MIN(u32CacheParsed + SUBTITLE_MAX_SIZE, SUBTITLE_SMALL_BUF_SIZE-1);
                    bLeftBrace = FALSE;

                    for(;u32CacheParsed<=u32TextParseMax;u32CacheParsed++)
                    {
                        if(bLeftBrace == FALSE && pu8Cache[u32CacheParsed] == '{')
                        {
                            if(u32CacheParsed-u32TagStart)
                            {
                                memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], u32CacheParsed-u32TagStart);
                                u32SubtitlePos +=(u32CacheParsed-u32TagStart);
                                u32TagStart = u32CacheParsed;
                            }
                            bLeftBrace = TRUE;
                        }
                        else if(bLeftBrace == TRUE && pu8Cache[u32CacheParsed] == '}')
                        {
                            u32TagStart = u32CacheParsed+1;
                            bLeftBrace = FALSE;
                        }
                        else if(pu8Cache[u32CacheParsed] == '\\')
                        {
                            if(pu8Cache[u32CacheParsed+1] == 'n' || pu8Cache[u32CacheParsed+1] == 'N')
                            {
                                //new line
                                pu8Cache[u32CacheParsed] = '\r';
                                pu8Cache[u32CacheParsed+1] = '\n';
                                ++u32CacheParsed;
                            }
                            else if(pu8Cache[u32CacheParsed+1] == 'h')
                            {
                                //0x1A ascii substitute
                                pu8Cache[u32CacheParsed] = 26;    //hide
                                pu8Cache[u32CacheParsed+1] = 26;  //hide
                                ++u32CacheParsed;
                            }
                        }
                        else if((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
                        {
                            break;
                        }
                    }
                    if(u32CacheParsed < SUBTITLE_SMALL_BUF_SIZE)
                    {
                        pu8Cache[u32CacheParsed] = '\0';
                        pu8Cache[u32CacheParsed+1] = '\0';
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);
                        u32SubtitlePos += u32CacheParsed+2-u32TagStart;
                        enSSAParse = E_PARSE_DONE;
                    }
                    break;
                    #endif
                    #if 0
                    u32TextParseMax = MIN(u32CacheParsed + SUBTITLE_MAX_SIZE, SUBTITLE_SMALL_BUF_SIZE - 4);
                    for(i=u32CacheParsed;i<=u32TextParseMax;i++)
                    {
                        if((pu8Cache[i] == '\r') && (pu8Cache[i+1] == '\n'))
                        {
                            break;
                        }
                    }

                    u32CacheParsed = i;
                    pu8Cache[u32CacheParsed] = '\0';
                    pu8Cache[u32CacheParsed+1] = '\0';
                    memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);
                    u32SubtitlePos += u32CacheParsed+2-u32TagStart;
                    enSSAParse = E_PARSE_DONE;
                    break;
                    #endif

                case E_PARSE_DONE:
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    u32CacheParsed+=2;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf("Tag[%d] %ld %ld %ld,%ld --> %ld %ld %ld,%ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {
                        goto _MApp_MPlayer_SSA_Parser_END;
                    }
                    enSSAParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if((u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize))
            {   // Read the next block of data.
                if(enSSAParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSSAParse = E_PARSE_INIT;
                }
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SSA_Parser_END;
            }
        }
    }

#if 0
    for(i=0;i<20;i++)
    {
        printf("Time = %ld, %ld, %08lx\n", pTag[i].u32TimeStart, pTag[i].u32TimeEnd, pTag[i].u32SubtitlePos);
    }
#endif

_MApp_MPlayer_SSA_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SSA;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        m_u8SubtitleTrackNum++;
      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        //qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
        _MApp_MPlayer_SubtitleTagSort(pTag, m_u16SubtitleTagCount);
      #endif
    }

    return bRet;
}

#if (ENABLE_SUBTITLE_SMI)
static BOOLEAN _MApp_MPlayer_SMI_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define STYLE_TAG                       "<STYLE TYPE="
    #define STYLE_TAG_UNICODE               "<\0S\0T\0Y\0L\0E\0 \0T\0Y\0P\0E\0=\0"
    #define PCLASS_TAG                      "<P CLASS="
    #define PCLASS_TAG_UNICODE              "<\0P\0 \0C\0L\0A\0S\0S\0=\0"
    #define SYNC_TAG                        "<SYNC START="
    #define SYNC_TAG_UNICODE                "<\0S\0Y\0N\0C\0 \0S\0T\0A\0R\0T\0=\0"
    #define BODY_TAG                        "</BODY>"
    #define SAMI_TAG                        "</SAMI>"
    #define BODY_TAG_UNICODE                "<\0/\0B\0O\0D\0Y\0>\0"
    #define SAMI_TAG_UNICODE                "<\0/\0S\0A\0M\0I\0>\0"
    #define LANG_TAG                        "LANG:"
    #define LANG_TAG_UNICODE                "L\0A\0N\0G\0:\0"
    #define SAMI_PREPARSE_LEN               128
    #define CLASS_LEN                       64
    #define MAX_SMI_TIME_DIGIT              24
    #define LAST_SUBTITLE_DISPLAY_TIME      5

    BOOLEAN bRet = FALSE;
    BOOLEAN bMultiClass = FALSE;
    BOOLEAN bFound = FALSE;
    BOOLEAN bPClass = FALSE;
    MPlayer_Subtitle_Tag *pTag;
    U32 i;
    U32 u32TimeStart=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U8 u8ClassLen=0;
    SMI_Subtitle_Class astClass[SUPPORT_SUBITILE_TRACK_MAX];
    SMI_Subtitle_Class *pClass;
    U8 u8TotalClassNo=0;
    U8 u8CurClassNo=0;
    enumMPlayerSubtitleParse enSMIParse = E_PARSE_INIT;
    U32 u32TagStart=0;
    U32 u32SubtitlePos=0, u32PrevSubPos=0;
    U32 u32CacheParsed=0;
    U32 u32PrevTagPos=0;
    U32 u32ParsingTime=0;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

_MApp_MPlayer_Parse_Next_Class:

    m_u16SubtitleTagCount = 0;
    //save all tracks' language using class number not track number in state of E_PARSE_IDENTIFIER.
    //m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);
    pClass = &astClass[0];

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32SubtitlePos = 0;
    u32PrevSubPos = 0;
    u32CacheParsed = 0;
    u32PrevTagPos = 0;

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(*pCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
    {
        pu8Cache = (U8*)_PA2VA((((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            switch(enSMIParse)
            {
                case E_PARSE_INIT:
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                        if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                        {
                            u32CacheParsed = 0;
                            break;
                        }
                        else if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
                        {
                            goto _MApp_MPlayer_SMI_Parser_END;
                        }
                    }
                    enSMIParse = E_PARSE_IDENTIFIER;
                    break;

                case E_PARSE_IDENTIFIER:
                    // Find the <STYLE TYPE=
                    for(;(u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE/2)&&(u8TotalClassNo < SUPPORT_SUBITILE_TRACK_MAX);u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(STYLE_TAG_UNICODE)-1);

                        if(memcmp(&pu16Cache[u32CacheParsed], STYLE_TAG_UNICODE, sizeof(STYLE_TAG_UNICODE)-1)==0)
                        {
                            for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                            {
                                if(pu16Cache[u32CacheParsed] == 0x007D)
                                {
                                    break;
                                }
                            }

                            pClass[u8TotalClassNo].u8ClassLen = 0;
                            for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                            {
                                if(pu16Cache[u32CacheParsed] == 0x002E)
                                {
                                    for(u8ClassLen=0;u8ClassLen<MAX_CLASS_NAME_LEN;u8ClassLen++)
                                    {
                                        if(pu16Cache[u32CacheParsed+u8ClassLen+1] == 0x0020)
                                        {
                                            break;
                                        }
                                        pClass[u8TotalClassNo].u8ClassName[u8ClassLen] = LOBYTE(pu16Cache[u32CacheParsed+u8ClassLen+1]);
                                    }
                                    pClass[u8TotalClassNo].u8ClassLen = u8ClassLen;
                                    _MApp_MPlayer_nupr(pClass[u8TotalClassNo].u8ClassName, u8ClassLen);

                                    u32CacheParsed += u8ClassLen;
                                    for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                                    {
                                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(LANG_TAG_UNICODE)/2);
                                        if(memcmp(&pu16Cache[u32CacheParsed], LANG_TAG_UNICODE, sizeof(LANG_TAG_UNICODE)-1)==0)
                                        {
                                            u32CacheParsed += sizeof(LANG_TAG_UNICODE)/2;
                                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                                            pClass[u8TotalClassNo].u8Lang[0] = LOBYTE(pu16Cache[u32CacheParsed]);
                                            pClass[u8TotalClassNo].u8Lang[1] = LOBYTE(pu16Cache[u32CacheParsed+1]);

                                            U32 u32TempSubtitleLang;
                                            u32TempSubtitleLang = pClass[u8TotalClassNo].u8Lang[1];
                                            u32TempSubtitleLang = (u32TempSubtitleLang<<8) + pClass[u8TotalClassNo].u8Lang[0];
                                            //printf("ClassNo=%d, Lang[0]=%c [1]=%c \n", u8TotalClassNo, pClass[u8TotalClassNo].u8Lang[0], pClass[u8TotalClassNo].u8Lang[1]);

                                            if(u8TotalClassNo < SUPPORT_SUBITILE_TRACK_MAX)
                                            {
                                                m_MPlayerSubtitleInfo[u8TotalClassNo].u32SubtitleLanguage = u32TempSubtitleLang;
                                            }
                                            break;
                                        }
                                        else if(pu16Cache[u32CacheParsed] == 0x007D)
                                        {
                                            break;
                                        }
                                    }
                                    u8TotalClassNo++;

                                    if(u8TotalClassNo >= SUPPORT_SUBITILE_TRACK_MAX)
                                    {
                                        SMALL_BUF_PARSER_DBG(printf("SMI OVER class number!\n"));
                                        break;
                                    }
                                }
                                else
                                {
                                    if((pu16Cache[u32CacheParsed] == 0x002D) && (pu16Cache[u32CacheParsed+1] == 0x002D) &&
                                        (pu16Cache[u32CacheParsed+2] == 0x003E))
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    bPClass = FALSE;
                    //in case of u8TotalClassNo =0, it meanms no class name in subtitle header. need to check PCLASS tag
                    if(u8TotalClassNo > 0)
                    {
                        bMultiClass = FALSE;
                        u8CurClassNo = 0;
                        // Find the <SYNC START=
                        for(u32CacheParsed=0;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                        {
                            _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                            if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(SYNC_TAG_UNICODE)/2;
                                // search PCLASS_TAG
                                for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                                {
                                    _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(PCLASS_TAG_UNICODE)-1);
                                    if(memcmp(&pu16Cache[u32CacheParsed], PCLASS_TAG_UNICODE, sizeof(PCLASS_TAG_UNICODE)-1)==0)
                                    {
                                        u8CurClassNo++;
                                        u32CacheParsed += sizeof(PCLASS_TAG_UNICODE)/2;
                                        bPClass = TRUE;
                                    }

                                    _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                                    if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                                    {
                                        break;
                                    }

                                    if(u8CurClassNo == u8TotalClassNo)
                                    {
                                        bMultiClass = TRUE;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    else
                    {
                        for(u32CacheParsed=0;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                        {
                            _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(PCLASS_TAG_UNICODE)-1);
                            if(memcmp(&pu16Cache[u32CacheParsed], PCLASS_TAG_UNICODE, sizeof(PCLASS_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(PCLASS_TAG_UNICODE)/2;
                                for(u8ClassLen=0;u8ClassLen<MAX_CLASS_NAME_LEN;u8ClassLen++)
                                {
                                    pClass[u8TotalClassNo].u8ClassName[u8ClassLen] = LOBYTE(pu16Cache[u32CacheParsed+u8ClassLen]);
                                    if(LOBYTE(pu16Cache[u32CacheParsed+u8ClassLen]) == '>')
                                    {
                                        break;
                                    }
                                }
                                pClass[u8TotalClassNo].u8ClassLen = u8ClassLen;
                                _MApp_MPlayer_nupr(pClass[u8TotalClassNo].u8ClassName, u8ClassLen);
                                u8TotalClassNo++;
                                bPClass = TRUE;
                                break;
                            }
                        }
                    }
                    u8CurClassNo = 0;
                    u32CacheParsed = 0;
                    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                    if(bNeedTrans2Unicode == TRUE)
                    {
                        //Every time we load data from usb to subtitle buufer.
                        //If it is big endian, we need to transfer it to little endian for parsing.
                        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                    }

                    enSMIParse = E_PARSE_START_TIME;
                    break;

                case E_PARSE_START_TIME:
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(SYNC_TAG_UNICODE)-1);
                        if(memcmp(&pu16Cache[u32CacheParsed], SYNC_TAG_UNICODE, sizeof(SYNC_TAG_UNICODE)-1)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            u32CacheParsed += sizeof(SYNC_TAG_UNICODE)/2;
                            SUBTITLE_FIND_DIGIT_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            // Convert time to ASCII.
                            for(i=0;i<MAX_SMI_TIME_DIGIT/2;i++)
                            {
                                if(ISDIGIT_UNICODE(pu16Cache[u32CacheParsed+i]))
                                {
                                    pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                                }
                                else
                                {
                                    pu8Cache[i] = '\0';
                                    break;
                                }
                            }

                            i = _MApp_MPlayer_ScanDigit(&pu8Cache[0], &u32TimeStart);
                            enSMIParse = E_PARSE_SUB_LINE1;
                            u32CacheParsed = u32CacheParsed + i +1;

                            break;
                        }
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    // search PCLASS_TAG
                    bFound = FALSE;
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if(bPClass)
                        {
                            _MApp_MPlayer_nupr_Unicode((U8*)&pu16Cache[u32CacheParsed], sizeof(PCLASS_TAG_UNICODE)-1);
                            if(memcmp(&pu16Cache[u32CacheParsed], PCLASS_TAG_UNICODE, sizeof(PCLASS_TAG_UNICODE)-1)==0)
                            {
                                u32CacheParsed += sizeof(PCLASS_TAG_UNICODE)/2;
                                if( pClass[u8CurClassNo].u8ClassLen != 0)
                                {
                                    //this data transformation is for class name check, so using with CLASS_LEN
                                    for(i=0;i<CLASS_LEN/2;i++)
                                    {
                                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                                    }
                                    //in E_PARSE_IDENTIFIER state, pClass[u8CurClassNo].u8ClassName is converted to uppercase.
                                    //We have to convert read data to uppercase by comparison with u8ClassName
                                    //_MApp_MPlayer_nupr(pClass[u8CurClassNo].u8ClassName, pClass[u8CurClassNo].u8ClassLen);
                                    _MApp_MPlayer_nupr(&pu8Cache[0], pClass[u8CurClassNo].u8ClassLen);
                                    if(memcmp(&pu8Cache[0], pClass[u8CurClassNo].u8ClassName,  pClass[u8CurClassNo].u8ClassLen) == 0)
                                    {

                                        //To solve the case: <P Class=ENUSCC ID=Source>The Speaker </P>
                                        //if not found the end of class name('>') in SUBTITLE_SMALL_BUF_SIZE, will read next block
                                        for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                                        {
                                            if ((pu16Cache[u32CacheParsed] == 0x000D) && (pu16Cache[u32CacheParsed+1] == 0x000A)) //0x000D '\r', 0x000A '\n'
                                            {
                                                u32TagStart = u32CacheParsed+2; //cannot find '>' until line end, this line is no subtitle
                                                u32CacheParsed = u32TagStart;
                                                break;
                                            }

                                            if(pu16Cache[u32CacheParsed] == 0x003E) //'>'
                                            {
                                                u32TagStart = u32CacheParsed+1;
                                                u32CacheParsed = u32TagStart;
                                                bFound = TRUE;
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    else if(!bMultiClass)
                                    {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                if((pu16Cache[u32CacheParsed] == 0x003C) &&
                                    (pu16Cache[u32CacheParsed+1]  == 0x0053) &&
                                    (pu16Cache[u32CacheParsed+2]  == 0x0059) &&
                                    (pu16Cache[u32CacheParsed+3]  == 0x004E) &&
                                    (pu16Cache[u32CacheParsed+4]  == 0x0043))
                                {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                }
                            }
                        }
                        else
                        {
                            if(pu16Cache[u32CacheParsed] == 0x003E)
                            {
                                u32TagStart = u32CacheParsed+1;
                                u32CacheParsed = u32TagStart;
                                bFound = TRUE;
                                break;
                            }
                            else
                            {
                                if((pu16Cache[u32CacheParsed] == 0x003C) &&
                                    (pu16Cache[u32CacheParsed+1]  == 0x0053) &&
                                    (pu16Cache[u32CacheParsed+2]  == 0x0059) &&
                                    (pu16Cache[u32CacheParsed+3]  == 0x004E) &&
                                    (pu16Cache[u32CacheParsed+4]  == 0x0043))
                                {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                }
                            }

                        }
                    }

                    if((enSMIParse == E_PARSE_START_TIME)||(!bFound))
                    {
                        break;
                    }

                    // search the next PCLASS_TAG & SYNC_START
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if(((pu16Cache[u32CacheParsed] == 0x003C) &&
                            (pu16Cache[u32CacheParsed+1]  == 0x0053 || pu16Cache[u32CacheParsed+1]  == 0x0073) &&
                            (pu16Cache[u32CacheParsed+2]  == 0x0059 || pu16Cache[u32CacheParsed+2]  == 0x0079) &&
                            (pu16Cache[u32CacheParsed+3]  == 0x004E || pu16Cache[u32CacheParsed+3]  == 0x006E) &&
                            (pu16Cache[u32CacheParsed+4]  == 0x0043 || pu16Cache[u32CacheParsed+4]  == 0x0063))
                            ||
                            ((pu16Cache[u32CacheParsed+1]  == 0x0050 || pu16Cache[u32CacheParsed+1]  == 0x0070) &&
                            (pu16Cache[u32CacheParsed+2]  ==  0x0020) &&
                            (pu16Cache[u32CacheParsed+3]  == 0x0043 || pu16Cache[u32CacheParsed+3]  == 0x0063) &&
                            (pu16Cache[u32CacheParsed+4]  == 0x004C || pu16Cache[u32CacheParsed+4]  == 0x006C)))
                        {
                            break;
                        }
                        else if((pu16Cache[u32CacheParsed] == 0x003C) &&
                            (pu16Cache[u32CacheParsed+1]  == 0x002F ) &&
                            (pu16Cache[u32CacheParsed+2]  ==  0x0042|| pu16Cache[u32CacheParsed+2]  == 0x0062) &&
                            (pu16Cache[u32CacheParsed+3]  == 0x004F || pu16Cache[u32CacheParsed+3]  == 0x006F) &&
                            (pu16Cache[u32CacheParsed+4]  == 0x0044 || pu16Cache[u32CacheParsed+4]  == 0x0064) &&
                            (pu16Cache[u32CacheParsed+5]  == 0x0059 || pu16Cache[u32CacheParsed+5]  == 0x0079))
                        {
                            break;
                        }

                    }

                    u32CacheParsed-=2;
                    pu16Cache[u32CacheParsed] = '\0';
                    pu16Cache[u32CacheParsed+1] = '\0';
                    memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);
                    u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                    enSMIParse = E_PARSE_DONE;
                    break;

                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = u32TimeStart;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = 0xFFFFFFFF;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    u32CacheParsed+=2;
                    bRet = TRUE;

                    //printf(" tag[%u] -> %lu, max %u, %lx\n", m_u16SubtitleTagCount, u32TimeStart, (U16)SUBTITLE_TAG_NUM_MAX, u32SubtitlePos);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_SMI_Parser_END;
                    }

                    enSMIParse = E_PARSE_START_TIME;
/*
                    if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
                    {   // Read the next block of data.
                        m_u32CurSubtitleFilePos += u32CacheParsed*2;
                        msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                        msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                        u32CacheParsed = 0;
                    }
*/
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
            {   // Read the next block of data.
                if(enSMIParse == E_PARSE_START_TIME)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSMIParse = E_PARSE_START_TIME;
                }
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SMI_Parser_END;
            }
        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            switch(enSMIParse)
            {
                case E_PARSE_INIT:
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                        if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                        {
                            u32CacheParsed = 0;
                            break;
                        }
                        else if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
                        {
                            goto _MApp_MPlayer_SMI_Parser_END;
                        }
                    }
                    enSMIParse = E_PARSE_IDENTIFIER;
                    break;

                case E_PARSE_IDENTIFIER:
                    // Find the <STYLE TYPE=
                    for(;(u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE)&&(u8TotalClassNo < SUPPORT_SUBITILE_TRACK_MAX);u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(STYLE_TAG)-1);
                        if(memcmp(&pu8Cache[u32CacheParsed], STYLE_TAG, sizeof(STYLE_TAG)-1)==0)
                        {
                            for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                            {
                                if(pu8Cache[u32CacheParsed] == '}')
                                {
                                    break;
                                }
                            }

                            pClass[u8TotalClassNo].u8ClassLen = 0;
                            for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                            {
                                if(pu8Cache[u32CacheParsed] == '.')
                                {
                                    for(u8ClassLen=0;u8ClassLen<MAX_CLASS_NAME_LEN;u8ClassLen++)
                                    {
                                        if(pu8Cache[u32CacheParsed+u8ClassLen+1] == ' ')
                                        {
                                            break;
                                        }
                                        pClass[u8TotalClassNo].u8ClassName[u8ClassLen] = pu8Cache[u32CacheParsed+u8ClassLen+1];
                                    }
                                    pClass[u8TotalClassNo].u8ClassLen = u8ClassLen;
                                    _MApp_MPlayer_nupr(pClass[u8TotalClassNo].u8ClassName, u8ClassLen);

                                    u32CacheParsed += u8ClassLen;
                                    for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                                    {
                                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(LANG_TAG)-1);
                                        if(memcmp(&pu8Cache[u32CacheParsed], LANG_TAG, sizeof(LANG_TAG)-1)==0)
                                        {
                                            u32CacheParsed += sizeof(LANG_TAG)-1;
                                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                                            pClass[u8TotalClassNo].u8Lang[0] = pu8Cache[u32CacheParsed];
                                            pClass[u8TotalClassNo].u8Lang[1] = pu8Cache[u32CacheParsed+1];

                                            U32 u32TempSubtitleLang;
                                            u32TempSubtitleLang = pClass[u8TotalClassNo].u8Lang[1];
                                            u32TempSubtitleLang = (u32TempSubtitleLang<<8) + pClass[u8TotalClassNo].u8Lang[0];
                                            //printf("ClassNo=%d, Lang[0]=%c [1]=%c \n", u8TotalClassNo, pClass[u8TotalClassNo].u8Lang[0], pClass[u8TotalClassNo].u8Lang[1]);

                                            if(u8TotalClassNo < SUPPORT_SUBITILE_TRACK_MAX)
                                            {
                                                m_MPlayerSubtitleInfo[u8TotalClassNo].u32SubtitleLanguage = u32TempSubtitleLang;
                                            }
                                            break;
                                        }
                                        else if(pu8Cache[u32CacheParsed] == '}')
                                        {
                                            break;
                                        }
                                    }

                                    u8TotalClassNo++;

                                    if(u8TotalClassNo >= SUPPORT_SUBITILE_TRACK_MAX)
                                    {
                                        (printf("SMI OVER class number!\n"));
                                        break;
                                    }
                                }
                                else
                                {
                                    if((pu8Cache[u32CacheParsed] == '-') && (pu8Cache[u32CacheParsed+1] == '-') &&
                                        (pu8Cache[u32CacheParsed+2] == '>'))
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    bPClass = FALSE;
                    //in case of u8TotalClassNo =0, it meanms no class name in subtitle header. need to check PCLASS tag
                    if(u8TotalClassNo > 0)
                    {
                        bMultiClass = FALSE;
                        u8CurClassNo = 0;
                        // Find the <SYNC START=
                        for(u32CacheParsed=0;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                        {
                            _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                            if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(SYNC_TAG)-1;
                                // search PCLASS_TAG
                                for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                                {
                                    _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(PCLASS_TAG)-1);
                                    if(memcmp(&pu8Cache[u32CacheParsed], PCLASS_TAG, sizeof(PCLASS_TAG)-1)==0)
                                    {
                                        u8CurClassNo++;
                                        u32CacheParsed += sizeof(PCLASS_TAG)-1;
                                        bPClass = TRUE;
                                    }

                                    _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                                    if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                                    {
                                        //printf(" found 2nd SYNC_START\n");
                                        break;
                                    }

                                    if(u8CurClassNo == u8TotalClassNo)
                                    {
                                        bMultiClass = TRUE;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    else
                    {
                        for(u32CacheParsed=0;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                        {
                            _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(PCLASS_TAG)-1);
                            if(memcmp(&pu8Cache[u32CacheParsed], PCLASS_TAG, sizeof(PCLASS_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(PCLASS_TAG)-1;
                                for(u8ClassLen=0;u8ClassLen<MAX_CLASS_NAME_LEN;u8ClassLen++)
                                {
                                    pClass[u8TotalClassNo].u8ClassName[u8ClassLen] = pu8Cache[u32CacheParsed+u8ClassLen];
                                    if(pu8Cache[u32CacheParsed+u8ClassLen] == '>')
                                    {
                                        break;
                                    }
                                }
                                pClass[u8TotalClassNo].u8ClassLen = u8ClassLen;
                                _MApp_MPlayer_nupr(pClass[u8TotalClassNo].u8ClassName, u8ClassLen);
                                u8TotalClassNo++;
                                bPClass = TRUE;
                                break;
                            }
                        }
                    }

                    u8CurClassNo = 0;
                    u32CacheParsed = 0;
                    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                    enSMIParse = E_PARSE_START_TIME;
                    break;

                case E_PARSE_START_TIME:
                    // Find the <SYNC START=
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(SYNC_TAG)-1);
                        if(memcmp(&pu8Cache[u32CacheParsed], SYNC_TAG, sizeof(SYNC_TAG)-1)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            u32CacheParsed += sizeof(SYNC_TAG)-1;
                            SUBTITLE_FIND_DIGIT(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            i = _MApp_MPlayer_ScanDigit(&pu8Cache[u32CacheParsed], &u32TimeStart);
                            u32CacheParsed = u32CacheParsed + i +1;
                            enSMIParse = E_PARSE_SUB_LINE1;
                            break;
                        }
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    // search PCLASS_TAG
                    bFound = FALSE;
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if(bPClass)
                        {
                            _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], sizeof(PCLASS_TAG)-1);
                            if(memcmp(&pu8Cache[u32CacheParsed], PCLASS_TAG, sizeof(PCLASS_TAG)-1)==0)
                            {
                                u32CacheParsed += sizeof(PCLASS_TAG)-1;
                                if( pClass[u8CurClassNo].u8ClassLen != 0)
                                {
                                    //in E_PARSE_IDENTIFIER state, pClass[u8CurClassNo].u8ClassName is converted to uppercase.
                                    //We have to convert read data to uppercase by comparison with u8ClassName
                                    _MApp_MPlayer_nupr(&pu8Cache[u32CacheParsed], pClass[u8CurClassNo].u8ClassLen);
                                    if(memcmp(&pu8Cache[u32CacheParsed], pClass[u8CurClassNo].u8ClassName,  pClass[u8CurClassNo].u8ClassLen) == 0)
                                    {
                                        //To solve the case: <P Class=ENUSCC ID=Source>The Speaker </P>
                                        //if not found the end of class name('>') in SUBTITLE_SMALL_BUF_SIZE, will read next block
                                        for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                                        {
                                            if ((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
                                            {
                                                u32TagStart = u32CacheParsed+2; //cannot find '>' until line end, this line is no subtitle
                                                u32CacheParsed = u32TagStart;
                                                break;
                                            }
                                            if(pu8Cache[u32CacheParsed] == '>')
                                            {
                                                u32TagStart = u32CacheParsed+1;
                                                u32CacheParsed = u32TagStart;
                                                bFound = TRUE;
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    else if(!bMultiClass)
                                    {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                if((pu8Cache[u32CacheParsed] == '<') &&
                                    (pu8Cache[u32CacheParsed+1]  == 'S') &&
                                    (pu8Cache[u32CacheParsed+2]  == 'Y') &&
                                    (pu8Cache[u32CacheParsed+3]  == 'N') &&
                                    (pu8Cache[u32CacheParsed+4]  == 'C'))
                                {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                }
                            }
                        }
                        else
                        {
                            if(pu8Cache[u32CacheParsed] == '>')
                            {
                                u32TagStart = u32CacheParsed+1;
                                u32CacheParsed = u32TagStart;
                                bFound = TRUE;
                                break;
                            }
                            else
                            {
                                if((pu8Cache[u32CacheParsed] == '<') &&
                                    (pu8Cache[u32CacheParsed+1]  == 'S') &&
                                    (pu8Cache[u32CacheParsed+2]  == 'Y') &&
                                    (pu8Cache[u32CacheParsed+3]  == 'N') &&
                                    (pu8Cache[u32CacheParsed+4]  == 'C'))
                                {
                                        enSMIParse = E_PARSE_START_TIME;
                                        break;
                                }
                            }
                        }
                    }

                    if((enSMIParse == E_PARSE_START_TIME)||(!bFound))
                    {
                        break;
                    }
//                    u32CacheParsed = u32TagStart;
                    // search the next PCLASS_TAG & SYNC_START
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if(((pu8Cache[u32CacheParsed] == '<') &&
                            (pu8Cache[u32CacheParsed+1]  == 'S' || pu8Cache[u32CacheParsed+1]  == 's') &&
                            (pu8Cache[u32CacheParsed+2]  == 'Y' || pu8Cache[u32CacheParsed+2]  == 'y') &&
                            (pu8Cache[u32CacheParsed+3]  == 'N' || pu8Cache[u32CacheParsed+3]  == 'n') &&
                            (pu8Cache[u32CacheParsed+4]  == 'C' || pu8Cache[u32CacheParsed+4]  == 'c'))
                            ||
                            ((pu8Cache[u32CacheParsed+1]  == 'P' || pu8Cache[u32CacheParsed+1]  == 'p') &&
                            (pu8Cache[u32CacheParsed+2]  == ' ') &&
                            (pu8Cache[u32CacheParsed+3]  == 'C' || pu8Cache[u32CacheParsed+3]  == 'c') &&
                            (pu8Cache[u32CacheParsed+4]  == 'L' || pu8Cache[u32CacheParsed+4]  == 'l')))
                        {
                            break;
                        }
                        else if((pu8Cache[u32CacheParsed] == '<') &&
                            (pu8Cache[u32CacheParsed+1]  == '/') &&
                            (pu8Cache[u32CacheParsed+2]  == 'B' || pu8Cache[u32CacheParsed+2]  == 'b') &&
                            (pu8Cache[u32CacheParsed+3]  == 'O' || pu8Cache[u32CacheParsed+3]  == 'o') &&
                            (pu8Cache[u32CacheParsed+4]  == 'D' || pu8Cache[u32CacheParsed+4]  == 'd') &&
                            (pu8Cache[u32CacheParsed+5]  == 'Y' || pu8Cache[u32CacheParsed+5]  == 'y'))
                        {
                            break;
                        }

                    }

                    u32CacheParsed-=2;
                    pu8Cache[u32CacheParsed] = '\0';
                    pu8Cache[u32CacheParsed+1] = '\0';
                    memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);
                    u32SubtitlePos += (u32CacheParsed+2-u32TagStart);
                    enSMIParse = E_PARSE_DONE;
                    break;

                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = u32TimeStart;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = 0xFFFFFFFF;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    u32CacheParsed+=2;
                    bRet = TRUE;
                    //printf(" tag[%u] -> %lu\n", m_u16SubtitleTagCount, u32TimeStart);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_SMI_Parser_END;
                    }

                    enSMIParse = E_PARSE_START_TIME;
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos + u32CacheParsed);
                if(enSMIParse == E_PARSE_START_TIME)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSMIParse = E_PARSE_START_TIME;
                }
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SMI_Parser_END;
            }
        }
    }

#if 0
    for(i=0;i<20;i++)
    {
        printf("Time = %ld, %ld, %08lx\n", pTag[i].u32TimeStart, pTag[i].u32TimeEnd, pTag[i].u32SubtitlePos);
    }
#endif

_MApp_MPlayer_SMI_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SMI;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        pTag[m_u16SubtitleTagCount].u32TimeEnd = pTag[m_u16SubtitleTagCount].u32TimeStart + LAST_SUBTITLE_DISPLAY_TIME;
        m_u8SubtitleTrackNum++;
      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
      #endif
    }

    if(m_u8SubtitleTrackNum < SUPPORT_SUBITILE_TRACK_MAX)
    {
        u8CurClassNo++;
        if((u8TotalClassNo > 1) && (u8CurClassNo < u8TotalClassNo))
        {
            m_u32CurSubtitleFilePos = 0;
            u32CacheParsed = 0;
            enSMIParse = E_PARSE_START_TIME;
            goto _MApp_MPlayer_Parse_Next_Class;
        }
    }
    return bRet;
}
#endif  // #if (ENABLE_SUBTITLE_SMI)

#if (ENABLE_SUBTITLE_TXT)
static BOOLEAN _MApp_MPlayer_TMPlayer_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    BOOLEAN bRet = FALSE;
    U32 i;
    MPlayer_Subtitle_Tag *pTag;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0;
    U32 u32SubtitlePos, u32PrevSubPos;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32CacheParsed;
    U32 u32TagStart, u32PrevTagPos;
    U32 u32ParsingTime = 0;
    BOOLEAN bUnicodeFile=FALSE;
    enumMPlayerSubtitleParse enTMPlayerParse;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        bUnicodeFile=TRUE;
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }
    // Parse the time
    #define TMPLAYER_TIME_STAMP_LEN  11
    u32SubtitlePos = 0;
    u32PrevSubPos = 0;
    u32CacheParsed = 0;
    u32TagStart = 0;
    u32PrevTagPos = 0;

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(bUnicodeFile)
    {
        enTMPlayerParse = E_PARSE_INIT;
        pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);

        while(m_u32CurSubtitleFilePos+ u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 >= SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_TMPlayer_Parser_END; //not found TMPlayer
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    // 1. Skip header.
                    for(i=u32CacheParsed;i<=SUBTITLE_SMALL_BUF_SIZE/2;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                           (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                           (LOBYTE(pu16Cache[i+2]) == ':'))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }

                    if((bRet == FALSE) && (i >= SUBTITLE_SMALL_BUF_SIZE/2))
                    {
                        goto _MApp_MPlayer_TMPlayer_Parser_END; //not found SRT
                    }

                    u32CacheParsed = i;

                    // 1. Check if time stamp.
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }
                    break;

                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour1, &u32Min1, &u32Sec1, 1))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos+u32CacheParsed*2;
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);

                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        enTMPlayerParse = E_PARSE_INIT;
                        if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
                        {
                            goto _MApp_MPlayer_TMPlayer_Parser_END; //improper format
                        }
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                    if(pu16Cache[u32CacheParsed] == 0x000D && pu16Cache[u32CacheParsed+1] == 0x000A)
                    {
                        memcpy( (void*)_PA2VA(SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);

                        u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;

                        for(i=u32TagStart;i<SUBTITLE_SMALL_BUF_SIZE;i++)
                        {
                            if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                               (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                               (LOBYTE(pu16Cache[i+2]) == ':'))
                            {
                                break;
                            }
                        }
                        u32CacheParsed = i;

                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_SUB_LINE2;

                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                case E_PARSE_SUB_LINE2:
                    if(pu16Cache[u32CacheParsed] == 0x000D && pu16Cache[u32CacheParsed+1] == 0x000A)
                    {
                        if(u32TagStart == u32CacheParsed)
                        {
                            pu16Cache[u32CacheParsed] = '\0';
                            pu16Cache[u32CacheParsed+1] = '\0';
                            memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos-2*2),(void*)&pu16Cache[u32TagStart], 4);
                        }
                        else
                        {
                            pu16Cache[u32CacheParsed] = '\0';
                            pu16Cache[u32CacheParsed+1] = '\0';
                            memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);
                            u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                        }
                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_END_TIME_LINE1;
                    }
                    else if(pu16Cache[u32CacheParsed] == 0x0032 && pu16Cache[u32CacheParsed+1] == 0x003D)
                    {
                        u32TagStart = u32CacheParsed + 2;
                    }

                    u32CacheParsed++;
                    break;

                case E_PARSE_END_TIME_LINE1:
                    for(i=u32CacheParsed;i<SUBTITLE_SMALL_BUF_SIZE;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                           (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                           (LOBYTE(pu16Cache[i+2]) == ':'))
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    // Check if time stamp.
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2, 1))
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN+2;
                        enTMPlayerParse = E_PARSE_END_TIME_LINE2;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }

                    break;

                case E_PARSE_END_TIME_LINE2:
                    // Check if time stamp.
                    for(i=0;i<TMPLAYER_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2, 2))
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }

                    break;

                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;

                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    u32CacheParsed++;
                    bRet = TRUE;
                    //printf("Tag[%d] %ld %ld %ld --> %ld %ld %ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }
                    enTMPlayerParse = E_PARSE_INIT;
                    break;

                case E_PARSE_IDENTIFIER:
                default:
                    break;
            }

            if(u32CacheParsed*2 >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enTMPlayerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTMPlayerParse = E_PARSE_INIT;
                }
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TMPlayer_Parser_END;
            }

        }
    }
    else
    {
        enTMPlayerParse = E_PARSE_INIT;
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_TMPlayer_Parser_END; //not found TMPlayer
            }

            switch(enTMPlayerParse)
            {
                case E_PARSE_INIT:
                    // Skip header.
                    for(i=u32CacheParsed;i<=SUBTITLE_SMALL_BUF_SIZE;i++)
                    {
                        if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                           (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                           (pu8Cache[i+2] == ':'))
                        {
                            enTMPlayerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    if((bRet == FALSE) && (i >= SUBTITLE_SMALL_BUF_SIZE))
                    {
                        goto _MApp_MPlayer_TMPlayer_Parser_END; //not found TMPlayer
                    }

                    u32CacheParsed = i;
                    break;

                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1, &u32Sec1, 1))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        enTMPlayerParse = E_PARSE_INIT;
                        if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
                        {
                            //__ASSERT(0);
                            goto _MApp_MPlayer_TMPlayer_Parser_END; //improper format
                        }
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                    if(pu8Cache[u32CacheParsed] == '\r' && pu8Cache[u32CacheParsed+1] == '\n')
                    {
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);
                        u32SubtitlePos += (u32CacheParsed+2-u32TagStart);

                        for(i=u32CacheParsed;i<SUBTITLE_SMALL_BUF_SIZE;i++)
                        {
                            if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                               (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                               (pu8Cache[i+2] == ':'))
                            {
                                break;
                            }
                        }
                        u32CacheParsed = i;

                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_SUB_LINE2;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                case E_PARSE_SUB_LINE2:
                    if(pu8Cache[u32CacheParsed] == '\r' && pu8Cache[u32CacheParsed+1] == '\n')
                    {
                        if(u32TagStart == u32CacheParsed)
                        {
                            pu8Cache[u32CacheParsed] = '\0';
                            pu8Cache[u32CacheParsed+1] = '\0';
                            memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos-2),(void*)&pu8Cache[u32TagStart], 2);
                        }
                        else
                        {
                            pu8Cache[u32CacheParsed] = '\0';
                            pu8Cache[u32CacheParsed+1] = '\0';
                            memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);
                            u32SubtitlePos += (u32CacheParsed+2-u32TagStart);
                        }
                        u32TagStart = u32CacheParsed;
                        enTMPlayerParse = E_PARSE_END_TIME_LINE1;
                    }
                    else if(pu8Cache[u32CacheParsed] == '2' && pu8Cache[u32CacheParsed+1] == '=')
                    {
                        u32TagStart = u32CacheParsed + 2;
                    }

                    u32CacheParsed++;
                    break;

                case E_PARSE_END_TIME_LINE1:

                    for(i=u32CacheParsed;i<SUBTITLE_SMALL_BUF_SIZE;i++)
                    {
                        if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                           (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                           (pu8Cache[i+2] == ':'))
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;
                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour2, &u32Min2, &u32Sec2, 1))
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN+2;
                        enTMPlayerParse = E_PARSE_END_TIME_LINE2;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }

                    break;

                case E_PARSE_END_TIME_LINE2:

                    if(_MApp_MPlayer_TMPlayerScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour2, &u32Min2, &u32Sec2, 2))
                    {
                        u32CacheParsed += TMPLAYER_TIME_STAMP_LEN;
                        enTMPlayerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }

                    break;

                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    u32CacheParsed++;
                    bRet = TRUE;
                    //printf("Tag[%d] %ld %ld %ld --> %ld %ld %ld \n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        __ASSERT(0);
                        goto _MApp_MPlayer_TMPlayer_Parser_END;
                    }
                    enTMPlayerParse = E_PARSE_INIT;
/*
                    if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
                    {   // Read the next block of data.
                        m_u32CurSubtitleFilePos += u32CacheParsed;
                        msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                        msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                        u32CacheParsed = 0;
                    }
*/
                    break;

                case E_PARSE_IDENTIFIER:
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enTMPlayerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTMPlayerParse = E_PARSE_INIT;
                }
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TMPlayer_Parser_END;
            }

        }
    }

_MApp_MPlayer_TMPlayer_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_TMPLAYER;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        m_u8SubtitleTrackNum++;
      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
      #endif
    }
    return bRet;
}


static BOOLEAN _MApp_MPlayer_TTXT_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    #define TTXT_CACHE_SIZE             1024
    #define XML_TAG                     "?xml"
    #define XML_TAG_UNICODE             "?\0x\0m\0l\0"
    #define TEXTSAMPLE_TAG              "<TextSample"
    #define TEXTSAMPLE_TAG_UNICODE      "<\0T\0e\0x\0t\0S\0a\0m\0p\0l\0e\0"
    #define TEXT_START_TAG              "text="
    #define TEXT_START_TAG_UNICODE      "t\0e\0x\0t\0=\0"
    #define TEXT_END_TAG                "</TextSample"
    #define TEXT_END_TAG_UNICODE        "<\0/\0T\0e\0x\0t\0S\0a\0m\0p\0l\0e\0"
    #define TEXTSAMPLE_START_TAG_LEN    24
    #define TTXT_TIME_STAMP_LEN         12

    BOOLEAN bRet = FALSE;
    U32 i;
    MPlayer_Subtitle_Tag *pTag;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32SubtitlePos, u32PrevSubPos;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32CacheParsed=0;
    U32 u32TagStart=0;
    U32 u32PrevTagPos=0;
    U32 u32ParsingTime=0;
    BOOLEAN bUnicodeFile=FALSE;
    enumMPlayerSubtitleParse enTTXTParse=E_PARSE_IDENTIFIER;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        bUnicodeFile=TRUE;
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32SubtitlePos = 0;
    u32PrevSubPos = 0;
    u32CacheParsed = 0;
    u32PrevTagPos = 0;

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(bUnicodeFile)
    {
        pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);

        while((m_u32CurSubtitleFilePos+ u32CacheParsed*2) < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed*2 > SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_TTXT_Parser_END;//not found Subviewer
            }

            switch(enTTXTParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], XML_TAG_UNICODE, sizeof(XML_TAG_UNICODE)-1)==0)
                        {
                            enTTXTParse = E_PARSE_INIT;
                            break;
                        }
                    }

                    if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2))
                    {
                        goto _MApp_MPlayer_TTXT_Parser_END; //not found TTXT
                    }
                    break;

                case E_PARSE_INIT:
                    if(memcmp(&pu16Cache[u32CacheParsed], TEXTSAMPLE_TAG_UNICODE, sizeof(TEXTSAMPLE_TAG_UNICODE)-1)==0)
                    {
                        enTTXTParse = E_PARSE_START_TIME;
                        u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;
                        break;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                case E_PARSE_START_TIME:
                    // Check if time stamp.
                    for(i=0;i<TTXT_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[0],
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos+ u32CacheParsed*2;
                        u32CacheParsed += TTXT_TIME_STAMP_LEN;
                        enTTXTParse = E_PARSE_SUB_LINE2;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTTXTParse = E_PARSE_INIT;
                    }

                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    if((pu16Cache[u32CacheParsed] == 0x0027) &&
                        (pu16Cache[u32CacheParsed+1] == 0x0022) &&
                        (pu16Cache[u32CacheParsed+2]==0x003E))
                    {
                        pu16Cache[u32CacheParsed] = '\0';
                        pu16Cache[u32CacheParsed+1] = '\0';
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);

                        u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                        u32CacheParsed += 3; //skip text end code
                        enTTXTParse = E_PARSE_END_TIME_LINE2;
                    }
                    else if(memcmp(&pu16Cache[u32CacheParsed], TEXT_START_TAG_UNICODE, sizeof(TEXT_START_TAG_UNICODE)-1)==0)
                    {
                        u32CacheParsed += sizeof(TEXT_START_TAG_UNICODE)/2+2;
                        u32TagStart = u32CacheParsed;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                case E_PARSE_END_TIME_LINE1:
                case E_PARSE_END_TIME_LINE2:
                    if(memcmp(&pu16Cache[u32CacheParsed], TEXTSAMPLE_TAG_UNICODE, sizeof(TEXTSAMPLE_TAG_UNICODE)-1)==0)
                    {
                        u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;

                        for(i=0;i<TTXT_TIME_STAMP_LEN;i++)
                        {
                            pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                        }

                        if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[0],
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2))
                        {
                            enTTXTParse = E_PARSE_DONE;
                            u32CacheParsed -= TEXTSAMPLE_START_TAG_LEN;
                        }
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf("Tag[%d] %lu, %lu, %lu -> %lu, %lu, %lu\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_TTXT_Parser_END;
                    }

                    enTTXTParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(u32CacheParsed*2 >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enTTXTParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTTXTParse = E_PARSE_INIT;
                }
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TTXT_Parser_END;
            }

        }
    }
    else
    {
        while((m_u32CurSubtitleFilePos+ u32CacheParsed) < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed > SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_TTXT_Parser_END;//not found Subviewer
            }

            switch(enTTXTParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], XML_TAG, sizeof(XML_TAG)-1)==0)
                        {
                            enTTXTParse = E_PARSE_INIT;
                            break;
                        }
                    }

                    if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE))
                    {
                        goto _MApp_MPlayer_TTXT_Parser_END; //not found TTXT
                    }
                    break;

                case E_PARSE_INIT:
                    if(memcmp(&pu8Cache[u32CacheParsed], TEXTSAMPLE_TAG, sizeof(TEXTSAMPLE_TAG)-1)==0)
                    {
                        enTTXTParse = E_PARSE_START_TIME;
                        u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;
                        break;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                case E_PARSE_START_TIME:
                    // Check if time stamp.
                    if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos+ u32CacheParsed;
                        u32CacheParsed += TTXT_TIME_STAMP_LEN;
                        enTTXTParse = E_PARSE_SUB_LINE2;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enTTXTParse = E_PARSE_INIT;
                    }

                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    if((pu8Cache[u32CacheParsed] == 0x27)&&(pu8Cache[u32CacheParsed+1] == 0x22)&&(pu8Cache[u32CacheParsed+2]==0x3E))
                    {
                        pu8Cache[u32CacheParsed] = '\0';
                        pu8Cache[u32CacheParsed+1] = '\0';
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);

                        u32SubtitlePos += (u32CacheParsed+2-u32TagStart);
                        u32CacheParsed += 3; //skip text end code
                        enTTXTParse = E_PARSE_END_TIME_LINE2;
                    }
                    else if(memcmp(&pu8Cache[u32CacheParsed], TEXT_START_TAG, sizeof(TEXT_START_TAG)-1)==0)
                    {
                        u32CacheParsed += sizeof(TEXT_START_TAG)+1;
                        u32TagStart = u32CacheParsed;
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                case E_PARSE_END_TIME_LINE1:
                case E_PARSE_END_TIME_LINE2:
                    if(memcmp(&pu8Cache[u32CacheParsed], TEXTSAMPLE_TAG, sizeof(TEXTSAMPLE_TAG)-1)==0)
                    {
                        u32CacheParsed += TEXTSAMPLE_START_TAG_LEN;
                        if(_MApp_MPlayer_TTXTScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2))
                        {
                            enTTXTParse = E_PARSE_DONE;
                            u32CacheParsed -= TEXTSAMPLE_START_TAG_LEN;
                        }
                    }
                    else
                    {
                        u32CacheParsed++;
                    }
                    break;

                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    MS_DEBUG_MSG(printf("Tag[%d] %lu, %lu, %lu -> %lu, %lu, %lu\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2));
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_TTXT_Parser_END;
                    }

                    enTTXTParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enTTXTParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enTTXTParse = E_PARSE_INIT;
                }
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_TTXT_Parser_END;
            }
        }
    }

_MApp_MPlayer_TTXT_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_TTXT;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        m_u8SubtitleTrackNum++;
      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
      #endif
    }
    return bRet;
}
#endif //#if (ENABLE_SUBTITLE_TXT)

#if (ENABLE_SUBTITLE_SUB)
static BOOLEAN _MApp_MPlayer_SubRipper_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{

    #define SUBRIPPER_HEADER                   "{HEAD"
    #define SUBRIPPER_HEADER_LEN               5
    #define SUBRIPPER_HEADER_UNICODE           "{\0H\0E\0A\0D\0"
    #define SUBRIPPER_HEADER_UNICODE_LEN       10
    #define SUBRIPPER_TIMETAG                   "{T "
    #define SUBRIPPER_TIMETAG_LEN               3
    #define SUBRIPPER_TIMETAG_UNICODE           "{\0T\0 \0"
    #define SUBRIPPER_TIMETAG_UNICODE_LEN       6
    #define SUBRIPPER_MAX_TIMELENGTH            12
    #define SURIPPER_LINE_END                   "}"
    #define SURIPPER_LINE_END_LEN               1
    #define SURIPPER_LINE_END_UNICODE           "}\0"
    #define SURIPPER_LINE_END_UNICODE_LEN       2

    BOOLEAN bRet = FALSE;
    U32 i;
    MPlayer_Subtitle_Tag *pTag;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32SubtitlePos, u32PrevSubPos;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32CacheParsed=0;
    U32 u32TagStart=0;
    U32 u32PrevTagPos=0;
    U32 u32ParsingTime=0;
    U32 u32SubRipperTimeLen = 0;
    U32 u32EndLine1Index = 0;
    BOOLEAN bUnicodeFile=FALSE;
    enumMPlayerSubtitleParse enSubRipperParse=E_PARSE_IDENTIFIER;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        bUnicodeFile=TRUE;
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    u32SubtitlePos = 0;
    u32PrevSubPos = 0;
    u32CacheParsed = 0;
    u32PrevTagPos = 0;

    u32ParsingTime = msAPI_Timer_GetTime0();


    if(bUnicodeFile)
    {
        pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);

        while(((m_u32CurSubtitleFilePos+ u32CacheParsed*2) < u32FileSize)  && ((m_u32CurSubtitleFilePos + u32EndLine1Index*2) < u32FileSize))
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed*2 > SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_SUBRIPPER_Parser_END;//not found Subviewer
            }

            switch(enSubRipperParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=(SUBTITLE_SMALL_BUF_SIZE/2);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed],SUBRIPPER_HEADER_UNICODE, SUBRIPPER_HEADER_UNICODE_LEN)==0)
                        {
                            enSubRipperParse = E_PARSE_INIT;
                            break;
                        }
                    }
                    break;
                case E_PARSE_INIT:
                    for(;(u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed], SUBRIPPER_TIMETAG_UNICODE, SUBRIPPER_TIMETAG_UNICODE_LEN)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + (u32CacheParsed*2);
                            enSubRipperParse = E_PARSE_START_TIME;
                            u32CacheParsed += (SUBRIPPER_TIMETAG_UNICODE_LEN/2);
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    // Check if time stamp.
                    for(i=0;i<SUBRIPPER_MAX_TIMELENGTH;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[0], &u32SubRipperTimeLen,
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32CacheParsed += u32SubRipperTimeLen;
                        enSubRipperParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed+=2;
                        enSubRipperParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                    u32TagStart = u32CacheParsed;
                    for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if(memcmp(&pu16Cache[u32CacheParsed],SURIPPER_LINE_END_UNICODE,SURIPPER_LINE_END_UNICODE_LEN)==0)
                        {
                            pu16Cache[u32CacheParsed] = '\0';
                            pu16Cache[u32CacheParsed+1] = '\0';
                            memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);
                            u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                            enSubRipperParse = E_PARSE_END_TIME_LINE1;
                            u32CacheParsed +=2;
                            break;
                        }
                    }
                    break;
                case E_PARSE_END_TIME_LINE1:
                    u32EndLine1Index = u32CacheParsed;
                    u32SubRipperTimeLen = 0;
                    for(;(u32EndLine1Index<=SUBTITLE_SMALL_BUF_SIZE/2) && (m_u32CurSubtitleFilePos + u32EndLine1Index*2 < u32FileSize);u32EndLine1Index++)
                    {
                        if(memcmp(&pu16Cache[u32EndLine1Index], SUBRIPPER_TIMETAG_UNICODE, SUBRIPPER_TIMETAG_UNICODE_LEN)==0)
                        {
                            u32EndLine1Index += (SUBRIPPER_TIMETAG_UNICODE_LEN/2);

                            for(i=0;i<SUBRIPPER_MAX_TIMELENGTH;i++)
                            {
                                pu8Cache[i] = LOBYTE(pu16Cache[u32EndLine1Index+i]);
                            }
                            if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[0], &u32SubRipperTimeLen,
                                                &u32Hour2, &u32Min2, &u32Sec2, &u32ms2)==FALSE)
                            {
                                u32Hour2 = u32Hour1;
                                u32Min2 = u32Min1;
                                u32Sec2 = u32Sec1;
                                u32ms2 = u32ms1;
                            }
                            u32EndLine1Index += u32SubRipperTimeLen;
                            enSubRipperParse = E_PARSE_DONE;
                            break;
                        }
                    }
                    break;
                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    SUBTITLE_SUBRIPPER_DBG(printf("Tag[%d] %lu, %lu, %lu -> %lu, %lu, %lu\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2));
                    SUBTITLE_SUBRIPPER_DBG(printf("u32SubtitlePos:0x%x\n",pTag[m_u16SubtitleTagCount].u32SubtitlePos));
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf("Tag[%d] %lu, %lu, %lu -> %lu, %lu, %lu\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2);

                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_SUBRIPPER_Parser_END;
                    }

                    enSubRipperParse = E_PARSE_SUB_LINE1;
                    u32Hour1 = u32Hour2;
                    u32Min1 = u32Min2;
                    u32Sec1 = u32Sec2;
                    u32CacheParsed = u32EndLine1Index;
                    break;

                default:
                    break;
            }

            if((u32CacheParsed*2 >= SUBTITLE_SMALL_BUF_SIZE) || (u32EndLine1Index*2 >= SUBTITLE_SMALL_BUF_SIZE))
            {   // Read the next block of data.
                if(enSubRipperParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else if(enSubRipperParse==E_PARSE_END_TIME_LINE1)
                {
                    m_u32CurSubtitleFilePos += u32EndLine1Index*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSubRipperParse = E_PARSE_INIT;
                    u32Hour1 = 0;
                    u32Min1 = 0;
                    u32Sec1 = 0;
                    u32Hour2 = 0;
                    u32Min2 = 0;
                    u32Sec2 = 0;
                }
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
                u32EndLine1Index = 0;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SUBRIPPER_Parser_END;
            }

        }
        if(enSubRipperParse==E_PARSE_END_TIME_LINE1)
        {
            pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
            pTag[m_u16SubtitleTagCount].u32TimeEnd = 0xFFFFFFFF;
            pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
            SUBTITLE_SUBRIPPER_DBG(printf("u32SubtitlePos:0x%x at last line\n",pTag[m_u16SubtitleTagCount].u32SubtitlePos);)
            SUBTITLE_SUBRIPPER_DBG(printf("u32TimeStart%lu  u32TimeEnd:%lu at last line\n",pTag[m_u16SubtitleTagCount].u32TimeStart, pTag[m_u16SubtitleTagCount].u32TimeEnd);)
            m_u16SubtitleTagCount++;
        }
    }
    else
    {
        while( ((m_u32CurSubtitleFilePos+ u32CacheParsed) < u32FileSize) && ((m_u32CurSubtitleFilePos + u32EndLine1Index) < u32FileSize))
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed > SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_SUBRIPPER_Parser_END;//not found SubRipper
            }

            switch(enSubRipperParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed],SUBRIPPER_HEADER, SUBRIPPER_HEADER_LEN)==0)
                        {
                            enSubRipperParse = E_PARSE_INIT;
                            break;
                        }
                    }
                    break;
                case E_PARSE_INIT:
                    for(;(u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE) && (m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize);u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed], SUBRIPPER_TIMETAG, SUBRIPPER_TIMETAG_LEN)==0)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                            enSubRipperParse = E_PARSE_START_TIME;
                            u32CacheParsed += SUBRIPPER_TIMETAG_LEN;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    // Check if time stamp.
                    if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[u32CacheParsed], &u32SubRipperTimeLen,
                                                &u32Hour1, &u32Min1, &u32Sec1, &u32ms1))
                    {
                        u32CacheParsed += u32SubRipperTimeLen;
                        enSubRipperParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enSubRipperParse = E_PARSE_INIT;
                    }
                    break;
                case E_PARSE_SUB_LINE1:
                    u32TagStart = u32CacheParsed;
                    for(;u32CacheParsed<SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if(memcmp(&pu8Cache[u32CacheParsed],SURIPPER_LINE_END,SURIPPER_LINE_END_LEN)==0)
                        {
                            pu8Cache[u32CacheParsed] = '\0';
                            pu8Cache[u32CacheParsed+1] = '\0';
                            memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);
                            u32SubtitlePos += u32CacheParsed+2-u32TagStart;
                            enSubRipperParse = E_PARSE_END_TIME_LINE1;
                            u32CacheParsed ++;
                            break;
                        }
                    }

                    break;
                case E_PARSE_END_TIME_LINE1:
                    u32EndLine1Index = u32CacheParsed;
                    u32SubRipperTimeLen = 0;
                    for(;(u32EndLine1Index<=SUBTITLE_SMALL_BUF_SIZE) && (m_u32CurSubtitleFilePos + u32EndLine1Index < u32FileSize);u32EndLine1Index++)
                    {
                        if(memcmp(&pu8Cache[u32EndLine1Index], SUBRIPPER_TIMETAG, SUBRIPPER_TIMETAG_LEN)==0)
                        {
                            u32EndLine1Index += SUBRIPPER_TIMETAG_LEN;
                            if(_MApp_MPlayer_SubRipperScanfTime(&pu8Cache[u32EndLine1Index], &u32SubRipperTimeLen,
                                                &u32Hour2, &u32Min2, &u32Sec2, &u32ms2)==FALSE)
                            {
                                u32Hour2 = u32Hour1;
                                u32Min2 = u32Min1;
                                u32Sec2 = u32Sec1;
                                u32ms2 = u32ms1;
                            }
                            u32EndLine1Index += u32SubRipperTimeLen;
                            enSubRipperParse = E_PARSE_DONE;
                            break;
                        }
                    }
                    break;
                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    SUBTITLE_SUBRIPPER_DBG(printf("Tag[%d] %lu, %lu, %lu -> %lu, %lu, %lu\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2);)
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_SUBRIPPER_Parser_END;
                    }

                    enSubRipperParse = E_PARSE_SUB_LINE1;
                    u32Hour1 = u32Hour2;
                    u32Min1 = u32Min2;
                    u32Sec1 = u32Sec2;
                    u32CacheParsed = u32EndLine1Index;
                    break;
                default:
                    break;
            }

            if((u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE) || (u32EndLine1Index >= SUBTITLE_SMALL_BUF_SIZE))
            {   // Read the next block of data.
                if(enSubRipperParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else if(enSubRipperParse==E_PARSE_END_TIME_LINE1)
                {
                    m_u32CurSubtitleFilePos += u32EndLine1Index;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSubRipperParse = E_PARSE_INIT;
                    u32Hour1 = 0;
                    u32Min1 = 0;
                    u32Sec1 = 0;
                    u32Hour2 = 0;
                    u32Min2 = 0;
                    u32Sec2 = 0;
                }
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
                u32EndLine1Index = 0;
            }

            msAPI_Timer_ResetWDT();

            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SUBRIPPER_Parser_END;
            }
        }

        if(enSubRipperParse==E_PARSE_END_TIME_LINE1)
        {
            pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
            pTag[m_u16SubtitleTagCount].u32TimeEnd = 0xFFFFFFFF;
            pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
            SUBTITLE_SUBRIPPER_DBG(printf("u32SubtitlePos:0x%x at final line\n",pTag[m_u16SubtitleTagCount].u32SubtitlePos);)
            SUBTITLE_SUBRIPPER_DBG(printf("u32TimeStart%lu  u32TimeEnd:%lu at final line\n",pTag[m_u16SubtitleTagCount].u32TimeStart, pTag[m_u16SubtitleTagCount].u32TimeEnd);)
            m_u16SubtitleTagCount ++;
            bRet = TRUE;
        }
    }

_MApp_MPlayer_SUBRIPPER_Parser_END:
    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBRIPPER;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount;
        m_u8SubtitleTrackNum++;
      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
      #endif
    }
    return bRet;
}

static BOOLEAN _MApp_MPlayer_SubViewer_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    BOOLEAN bRet = FALSE;
    U32 i;
    MPlayer_Subtitle_Tag *pTag;
    U32 u32Hour1=0, u32Min1=0, u32Sec1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32Sec2=0, u32ms2=0;
    U32 u32SubtitlePos, u32PrevSubPos;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32CacheParsed=0;
    U32 u32TagStart=0;
    U32 u32PrevTagPos=0;
    U32 u32ParsingTime=0;
    BOOLEAN bUnicodeFile=FALSE;
    BOOLEAN bSubViewer20=FALSE;
    enumMPlayerSubtitleParse enSubViewerParse;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        bUnicodeFile=TRUE;
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    // Parse the time
    #define SUBVIEWER10_TIME_STAMP_LEN  10
    #define SUBVIEWER20_TIME_STAMP_LEN  23
    u32SubtitlePos = 0;
    u32PrevSubPos = 0;
    u32CacheParsed = 0;
    u32PrevTagPos = 0;

    u32ParsingTime = msAPI_Timer_GetTime0();

    enSubViewerParse = E_PARSE_IDENTIFIER;

    if(bUnicodeFile)
    {
        pu8Cache = (U8*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);

        while((m_u32CurSubtitleFilePos+ u32CacheParsed*2) < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed*2 > SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_SubViewer_Parser_END;//not found Subviewer
            }

            switch(enSubViewerParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':'))
                        {
                            if(LOBYTE(pu16Cache[u32CacheParsed+8])== '.' && LOBYTE(pu16Cache[u32CacheParsed+11])== ',')
                            {
                                bSubViewer20 = TRUE;
                                enSubViewerParse = E_PARSE_INIT;
                                break;
                            }
                            else if(u32CacheParsed>0)
                            {
                                if(LOBYTE(pu16Cache[u32CacheParsed-1])== '[' && LOBYTE(pu16Cache[u32CacheParsed+8])== ']')
                                {
                                    bSubViewer20 = FALSE;
                                    enSubViewerParse = E_PARSE_INIT;
                                    break;
                                }
                            }
                        }
                    }

                    if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2))
                    {
                        goto _MApp_MPlayer_SubViewer_Parser_END; //not found SubViewer
                    }
                    break;
                case E_PARSE_INIT:
                    // Skip header.
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':'))
                        {
                            enSubViewerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    // 3. Check if time stamp.
                    for(i=0;i<SUBVIEWER20_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(bSubViewer20)
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)",", '.', 2) == 8)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            u32CacheParsed += SUBVIEWER20_TIME_STAMP_LEN;
                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            u32TagStart = u32CacheParsed;
                            enSubViewerParse = E_PARSE_SUB_LINE1;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    else
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)"#", ']', 1) == 3)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                            u32CacheParsed += SUBVIEWER10_TIME_STAMP_LEN;
                            SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                            u32TagStart = u32CacheParsed;
                            enSubViewerParse = E_PARSE_SUB_LINE1;

                        }
                        else
                        {
                            //u32ParsedPos += u16CacheParsed;
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    if(pu16Cache[u32CacheParsed] == 0x000D && pu16Cache[u32CacheParsed+1] == 0x000A)
                    {
                        pu16Cache[u32CacheParsed] = '\0';
                        pu16Cache[u32CacheParsed+1] = '\0';
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);

                        u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;

                        u32TagStart = u32CacheParsed;
                        if(bSubViewer20)
                        {
                            enSubViewerParse = E_PARSE_DONE;
                        }
                        else
                        {
                            enSubViewerParse = E_PARSE_END_TIME_LINE1;
                        }
                    }
                    u32CacheParsed++;
                    break;
                case E_PARSE_END_TIME_LINE1:
                case E_PARSE_END_TIME_LINE2:
                    for(i=u32CacheParsed;i<SUBTITLE_SMALL_BUF_SIZE/2;i++)
                    {
                        if((LOBYTE(pu16Cache[i]) >= '0' && LOBYTE(pu16Cache[i]) <= '9') &&
                           (LOBYTE(pu16Cache[i+1]) >= '0' && LOBYTE(pu16Cache[i+1]) <= '9') &&
                           (LOBYTE(pu16Cache[i+2]) == ':'))
                        {
                            break;
                        }
                    }

                    u32CacheParsed = i;
                    for(i=0;i<SUBVIEWER10_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                                &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                &u32ms1, &u32ms1, &u32ms1, &u32ms1,
                                                (U8*)"#", ']', 1) == 3)
                    {
                        u32CacheParsed += SUBVIEWER10_TIME_STAMP_LEN;
                        enSubViewerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        //__ASSERT(0);
                        goto _MApp_MPlayer_SubViewer_Parser_END;
                    }

                    break;
                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    u32CacheParsed++;
                    bRet = TRUE;
                    //printf("Tag[%d] %lu, %lu, %lu -> %lu, %lu, %lu\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_SubViewer_Parser_END;
                    }

                    enSubViewerParse = E_PARSE_INIT;
                    break;

                    default:
                        break;
            }

            if(u32CacheParsed*2 >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enSubViewerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSubViewerParse = E_PARSE_INIT;
                }

                //printf(" ----------> read next block %lx %lx\n", m_u32CurSubtitleFilePos, u32FileSize);

                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SubViewer_Parser_END;
            }

        }
    }
    else
    {
        while((m_u32CurSubtitleFilePos+ u32CacheParsed) < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos+ u32CacheParsed > SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_SubViewer_Parser_END;//not found Subviewer
            }

            switch(enSubViewerParse)
            {
                case E_PARSE_IDENTIFIER:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':'))
                        {
                            if(pu8Cache[u32CacheParsed+8]== '.' && pu8Cache[u32CacheParsed+11]== ',')
                            {
                                bSubViewer20 = TRUE;
                                enSubViewerParse = E_PARSE_INIT;
                                break;
                            }
                            else if(u32CacheParsed>0)
                            {
                                if(pu8Cache[u32CacheParsed-1]== '[' && pu8Cache[u32CacheParsed+8]== ']')
                                {
                                    bSubViewer20 = FALSE;
                                    enSubViewerParse = E_PARSE_INIT;
                                    break;
                                }
                            }
                        }
                    }

                    if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE))
                    {
                        goto _MApp_MPlayer_SubViewer_Parser_END; //not found SubViewer
                    }
                    break;

                case E_PARSE_INIT:
                    // Skip header.
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':'))
                        {
                            enSubViewerParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    break;
                case E_PARSE_START_TIME:
                    // 3. Check if time stamp.
                    if(bSubViewer20)
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)",", '.', 2) == 8)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos+ u32CacheParsed;
                            u32CacheParsed += SUBVIEWER20_TIME_STAMP_LEN;
                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            u32TagStart = u32CacheParsed;
                            enSubViewerParse = E_PARSE_SUB_LINE2;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    else
                    {
                        if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                    &u32Hour1, &u32Min1, &u32Sec1, &u32ms1,
                                                    &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                    (U8*)"#", ']', 1) == 3)
                        {
                            u32PrevTagPos = m_u32CurSubtitleFilePos+ u32CacheParsed;
                            u32CacheParsed += SUBVIEWER10_TIME_STAMP_LEN;
                            SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                            u32TagStart = u32CacheParsed;
                            enSubViewerParse = E_PARSE_SUB_LINE2;
                        }
                        else
                        {
                            u32CacheParsed++;
                            enSubViewerParse = E_PARSE_INIT;
                        }
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    if(pu8Cache[u32CacheParsed] == '\r' && pu8Cache[u32CacheParsed+1] == '\n')
                    {
                        pu8Cache[u32CacheParsed] = '\0';
                        pu8Cache[u32CacheParsed+1] = '\0';
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos),(void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);

                        u32SubtitlePos += (u32CacheParsed+2-u32TagStart);

                        u32TagStart = u32CacheParsed;
                        if(bSubViewer20)
                        {
                            enSubViewerParse = E_PARSE_DONE;
                        }
                        else
                        {
                            enSubViewerParse = E_PARSE_END_TIME_LINE1;
                        }
                    }
                    u32CacheParsed++;
                    break;
                case E_PARSE_END_TIME_LINE1:
                case E_PARSE_END_TIME_LINE2:
                    for(i=u32CacheParsed;i<SUBTITLE_SMALL_BUF_SIZE;i++)
                    {
                        if((pu8Cache[i] >= '0' && pu8Cache[i] <= '9') &&
                           (pu8Cache[i+1] >= '0' && pu8Cache[i+1] <= '9') &&
                           (pu8Cache[i+2] == ':'))
                        {
                            break;
                        }
                    }
                    u32CacheParsed = i;

                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                                &u32Hour2, &u32Min2, &u32Sec2, &u32ms2,
                                                &u32ms1, &u32ms1, &u32ms1, &u32ms1,
                                                (U8*)"#", ']', 1) == 3)
                    {
                        u32CacheParsed += SUBVIEWER10_TIME_STAMP_LEN;
                        enSubViewerParse = E_PARSE_DONE;
                    }
                    else
                    {
                        __ASSERT(0);
                        goto _MApp_MPlayer_SubViewer_Parser_END;
                    }

                    break;
                case E_PARSE_DONE:
                    // Fill the subtitle tag.
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32Sec1)*1000;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32Sec2)*1000;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;
                    u32PrevSubPos = u32SubtitlePos;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf("Tag[%d] %lu, %lu, %lu -> %lu, %lu, %lu\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32Sec1, u32Hour2, u32Min2, u32Sec2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {   // Exceed the maximum tag number. Stop parse.
                        goto _MApp_MPlayer_SubViewer_Parser_END;
                    }

                    enSubViewerParse = E_PARSE_INIT;
                    break;

                    default:
                        break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enSubViewerParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enSubViewerParse = E_PARSE_INIT;
                }
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SubViewer_Parser_END;
            }

        }
    }

_MApp_MPlayer_SubViewer_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_SUBVIEWER;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        m_u8SubtitleTrackNum++;
#if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
#endif
    }
    return bRet;
}


static BOOLEAN _MApp_MPlayer_MicroDVD_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{

    BOOLEAN bRet = FALSE;
    U32 i;
    MPlayer_Subtitle_Tag *pTag;
    U32 u32TimeStart=0, u32TimeEnd=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    U32 u32SubtitleOffset=0;
    BOOLEAN bFound, bFirstTag=TRUE;
    BOOLEAN bUnicodeFile=FALSE;
    enumMPlayerSubtitleParse enMicroDVDParse = E_PARSE_INIT;
    U32 u32SubtitlePos=0, u32PrevSubPos=0,  u32CacheParsed=0, u32PrevTagPos=0;
    U32 u32TagStart=0;
    U32 u32ParsingTime=0;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        bUnicodeFile=TRUE;
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    // Parse the time
    #define MICRODVD_TIME_STAMP_LEN  24 //assume max 24

    u32ParsingTime = msAPI_Timer_GetTime0();

    if(bUnicodeFile)
    {
        pu8Cache = (U8*)_PA2VA((((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);

        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed*2 > SUBTITLE_SMALL_BUF_SIZE/2))
            {
                goto _MApp_MPlayer_MicroDVD_Parser_END;//not found MicroDVD
            }

            switch(enMicroDVDParse)
            {
                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) == '{') && (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9'))
                        {
                            enMicroDVDParse = E_PARSE_START_TIME;
                            break;
                        }
                    }

                    if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2))
                    {
                        goto _MApp_MPlayer_MicroDVD_Parser_END; //not found SRT
                    }
                    break;
                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    for(i=0;i<MICRODVD_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_MicroDVDScanfTime(&pu8Cache[0], &u32SubtitleOffset, &u32TimeStart, &u32TimeEnd))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                        u32CacheParsed += u32SubtitleOffset;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        u32TagStart = u32CacheParsed;
                        enMicroDVDParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enMicroDVDParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    bFound = FALSE;
                    for(i=u32CacheParsed;i<=SUBTITLE_SMALL_BUF_SIZE/2;i++)
                    {
                        if(LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n')
                        {
                            bFound = TRUE;
                            break;
                        }
                    }

                    if(bFound)
                    {
                        if(bFirstTag)
                        {
                            //Check first tag is valid frame rate informatoin or not  , ex:only {1}{1} frame is valid otherwise , it should use movie frame rate information
                            if(u32TimeStart==1 && u32TimeEnd==1)
                            {
                                U8 au8Temp[MICRODVD_TIME_STAMP_LEN];

                                for(i=0;i<MICRODVD_TIME_STAMP_LEN;i++)
                                {
                                    au8Temp[i] = LOBYTE(pu16Cache[u32TagStart+i]);
                                }
                                _MApp_MPlayer_MicroDVDScanfFrameRate(&au8Temp[0], &m_u32MicroDVDFrameRate);
                                enMicroDVDParse = E_PARSE_INIT;
                            }
                            bFirstTag = FALSE;
                        }
                        else
                        {
                            u32CacheParsed = i;
                            pu16Cache[u32CacheParsed] = '\0';
                            pu16Cache[u32CacheParsed+1] = '\0';
                            memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);
                            u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                            enMicroDVDParse = E_PARSE_DONE;
                        }
                    }
                    break;

                case E_PARSE_DONE:
                    // do rescale in MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime
                    pTag[m_u16SubtitleTagCount].u32TimeStart = u32TimeStart;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = u32TimeEnd;

                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;

                    u32PrevSubPos = u32SubtitlePos;
                    u32CacheParsed+=2;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;

                    //printf("Tag[%d] %ld --> %ld \n", m_u16SubtitleTagCount, u32TimeStart, u32TimeEnd);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {
                        goto _MApp_MPlayer_MicroDVD_Parser_END;
                    }
                    enMicroDVDParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
            {   // Read the next block of data.
                if(enMicroDVDParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enMicroDVDParse = E_PARSE_INIT;
                }
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }
            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_MicroDVD_Parser_END;
            }

        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (m_u32CurSubtitleFilePos + u32CacheParsed > SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_MicroDVD_Parser_END;//not found MicroDVD
            }

            switch(enMicroDVDParse)
            {
                case E_PARSE_INIT:
                    // Find Dialogue
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] == '{') && (pu8Cache[u32CacheParsed+1] >= '0') && (pu8Cache[u32CacheParsed+1] <= '9'))
                        {
                            enMicroDVDParse = E_PARSE_START_TIME;
                            break;
                        }
                    }

                    if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE))
                    {
                        goto _MApp_MPlayer_MicroDVD_Parser_END; //not found SRT
                    }
                    break;

                case E_PARSE_START_TIME:
                    // 2. Check if time stamp.
                    if(_MApp_MPlayer_MicroDVDScanfTime(&pu8Cache[u32CacheParsed], &u32SubtitleOffset, &u32TimeStart, &u32TimeEnd))
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                        u32CacheParsed += u32SubtitleOffset;
                        SUBTITLE_SKIP_SPACE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        u32TagStart = u32CacheParsed;
                        enMicroDVDParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enMicroDVDParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    bFound = FALSE;
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
                        {
                            bFound = TRUE;
                            break;
                        }
                    }

                    if(bFound)
                    {
                        if(bFirstTag)
                        {
                            //Check first tag is valid frame rate informatoin or not  , ex:only {1}{1} frame is valid otherwise , it should use movie frame rate information
                            if(u32TimeStart==1 && u32TimeEnd==1)
                            {
                                _MApp_MPlayer_MicroDVDScanfFrameRate(&pu8Cache[u32TagStart], &m_u32MicroDVDFrameRate);
                                enMicroDVDParse = E_PARSE_INIT;
                            }
                            bFirstTag = FALSE;
                        }
                        else
                        {
                            pu8Cache[u32CacheParsed] = '\0';
                            pu8Cache[u32CacheParsed+1] = '\0';
                            memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);
                            u32SubtitlePos += u32CacheParsed+2-u32TagStart;
                            enMicroDVDParse = E_PARSE_DONE;
                        }
                    }
                    break;

                case E_PARSE_DONE:
                    // do rescale in MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime
                    pTag[m_u16SubtitleTagCount].u32TimeStart = u32TimeStart;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = u32TimeEnd;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;

                    u32PrevSubPos = u32SubtitlePos;
                    u32CacheParsed+=2;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf("Tag[%d] %ld --> %ld \n", m_u16SubtitleTagCount, u32TimeStart, u32TimeEnd);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {
                        goto _MApp_MPlayer_MicroDVD_Parser_END;
                    }
                    enMicroDVDParse = E_PARSE_INIT;
                    break;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enMicroDVDParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enMicroDVDParse = E_PARSE_INIT;
                }
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }
            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_MicroDVD_Parser_END;
            }

        }
    }

_MApp_MPlayer_MicroDVD_Parser_END:

    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_MICRODVD;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        m_u8SubtitleTrackNum++;
#if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
#endif
    }

    return bRet;
}


static BOOLEAN _MApp_MPlayer_DvdSubtitleSystem_Parser(U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    BOOLEAN bRet = FALSE;
    U32 i;
    MPlayer_Subtitle_Tag *pTag;
    U32 u32Hour1=0, u32Min1=0, u32econd1=0, u32ms1=0;
    U32 u32Hour2=0, u32Min2=0, u32econd2=0, u32ms2=0;
    U8 *pu8Cache;
    U16 *pu16Cache;
    BOOLEAN bFound;
    BOOLEAN bUnicodeFile=FALSE;
    enumMPlayerSubtitleParse enDvdSubtitleParse = E_PARSE_INIT;
    U32 u32SubtitlePos=0, u32PrevSubPos=0,  u32CacheParsed=0, u32PrevTagPos=0;
    U32 u32TagStart=0;
    U32 u32ParsingTime=0;
    BOOLEAN bNeedTrans2Unicode = FALSE;

    if(m_u8SubtitleTrackNum >= SUPPORT_SUBITILE_TRACK_MAX || pCodingType == NULL)
    {
        return FALSE;
    }

    m_u16SubtitleTagCount = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u32SubtitleLanguage = 0;
    m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagStart = m_u16SubtitleTagCount;

    *pCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;

    m_u32CurSubtitleFilePos = 0;
    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
    msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

    pu8Cache = (U8*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pu16Cache = (U16*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
    pTag = (MPlayer_Subtitle_Tag  *) _PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8SubtitleTrackNum*SUBTITLE_TAG_BUFFER_PER_TRACK);

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(pu8Cache[0]==0xFE && pu8Cache[1]==0xFF)
    {
        bNeedTrans2Unicode = TRUE;
        _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
    }

    if(pu8Cache[0]==0xFF && pu8Cache[1]==0xFE)
    {
        bUnicodeFile=TRUE;
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
    }
    else if (pu8Cache[0] == 0xEF && pu8Cache[1] == 0xBB && pu8Cache[2] == 0xBF)
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_UTF8;
    }
    else
    {
        *pCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
    }

    // Parse the time
    #define DVDSUBTITLE_SYSTEM_TIME_STAMP_LEN  23

    if(bUnicodeFile)
    {
        pu8Cache = (U8*)_PA2VA((((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)))+SUBTITLE_SMALL_BUF_SIZE+SUBTITLE_CACHE_OFFSET);
        while(m_u32CurSubtitleFilePos + u32CacheParsed*2 < u32FileSize)
        {
            if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2))
            {
                goto _MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END;//not found DvdSubtitle
            }

            switch(enDvdSubtitleParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE/2;u32CacheParsed++)
                    {
                        if((LOBYTE(pu16Cache[u32CacheParsed]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+1]) >= '0' && LOBYTE(pu16Cache[u32CacheParsed+1]) <= '9') &&
                           (LOBYTE(pu16Cache[u32CacheParsed+2]) == ':' ) && (LOBYTE(pu16Cache[u32CacheParsed+8]) == ':' ) &&
                           (LOBYTE(pu16Cache[u32CacheParsed+11]) == ' '))
                        {
                            enDvdSubtitleParse = E_PARSE_START_TIME;
                            break;
                        }
                    }
                    if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2))
                    {
                        goto _MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END; //not found SRT
                    }
                    break;

                case E_PARSE_START_TIME:
                    for(i=0;i<DVDSUBTITLE_SYSTEM_TIME_STAMP_LEN;i++)
                    {
                        pu8Cache[i] = LOBYTE(pu16Cache[u32CacheParsed+i]);
                    }

                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[0],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" ", ':', 2) == 8)
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed*2;
                        u32CacheParsed += DVDSUBTITLE_SYSTEM_TIME_STAMP_LEN;
                        SUBTITLE_SKIP_SPACE_UNICODE(pu16Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN/2);
                        u32TagStart = u32CacheParsed;
                        enDvdSubtitleParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enDvdSubtitleParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    bFound = FALSE;
                    for(i=u32CacheParsed;i<=SUBTITLE_SMALL_BUF_SIZE/2;i++)
                    {
                        if(LOBYTE(pu16Cache[i]) == '\r' && LOBYTE(pu16Cache[i+1]) == '\n')
                        {
                            bFound = TRUE;
                            break;
                        }
                    }

                    if(bFound)
                    {
                        u32CacheParsed = i;
                        pu16Cache[u32CacheParsed] = '\0';
                        pu16Cache[u32CacheParsed+1] = '\0';
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu16Cache[u32TagStart], (u32CacheParsed+2-u32TagStart)*2);
                        u32SubtitlePos += (u32CacheParsed+2-u32TagStart)*2;
                        enDvdSubtitleParse = E_PARSE_DONE;
                    }
                    break;

                case E_PARSE_DONE:
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;

                    u32PrevSubPos = u32SubtitlePos;
                    u32CacheParsed+=2;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf(" Tag[%d] %02ld %02ld %02ld %02ld    %02ld %02ld %02ld %02ld\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {
                        goto _MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END;
                    }
                    enDvdSubtitleParse = E_PARSE_INIT;

                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE/2)
            {   // Read the next block of data.
                if(enDvdSubtitleParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed*2;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enDvdSubtitleParse = E_PARSE_INIT;
                }
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);

                if(bNeedTrans2Unicode == TRUE)
                {
                    //Every time we load data from usb to subtitle buufer.
                    //If it is big endian, we need to transfer it to little endian for parsing.
                    _MApp_MPlayer_UnicodeBE2UnicodeLE(pu16Cache, SUBTITLE_SMALL_READ_BUF_SIZE);
                }
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END;
            }

        }
    }
    else
    {
        while(m_u32CurSubtitleFilePos + u32CacheParsed < u32FileSize)
        {
            if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE))
            {
                goto _MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END;//not found DvdSubtitle
            }

            switch(enDvdSubtitleParse)
            {
                case E_PARSE_INIT:
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] >= '0' && pu8Cache[u32CacheParsed] <= '9') &&
                           (pu8Cache[u32CacheParsed+1] >= '0' && pu8Cache[u32CacheParsed+1] <= '9') &&
                           (pu8Cache[u32CacheParsed+2] == ':' ) && (pu8Cache[u32CacheParsed+8] == ':' ) &&
                           (pu8Cache[u32CacheParsed+11] == ' '))
                        {
                            enDvdSubtitleParse = E_PARSE_START_TIME;
                            break;
                        }
                    }

                    if((bRet == FALSE) && (u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE))
                    {
                        goto _MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END;//not found DvdSubtitle
                    }
                    break;
                case E_PARSE_START_TIME:
                    if(_MApp_MPlayer_ScanfTime(&pu8Cache[u32CacheParsed],
                                               &u32Hour1, &u32Min1, &u32econd1, &u32ms1,
                                               &u32Hour2, &u32Min2, &u32econd2, &u32ms2,
                                               (U8*)" ", ':', 2) == 8)
                    {
                        u32PrevTagPos = m_u32CurSubtitleFilePos + u32CacheParsed;
                        u32CacheParsed += DVDSUBTITLE_SYSTEM_TIME_STAMP_LEN;
                        SUBTITLE_SKIP_SPACE(pu8Cache, u32CacheParsed, SUBTITLE_READ_BUF_LEN);
                        u32TagStart = u32CacheParsed;
                        enDvdSubtitleParse = E_PARSE_SUB_LINE1;
                    }
                    else
                    {
                        u32CacheParsed++;
                        enDvdSubtitleParse = E_PARSE_INIT;
                    }
                    break;

                case E_PARSE_SUB_LINE1:
                case E_PARSE_SUB_LINE2:
                    bFound = FALSE;
                    for(;u32CacheParsed<=SUBTITLE_SMALL_BUF_SIZE;u32CacheParsed++)
                    {
                        if((pu8Cache[u32CacheParsed] == '\r') && (pu8Cache[u32CacheParsed+1] == '\n'))
                        {
                            bFound = TRUE;
                            break;
                        }
                    }

                    if(bFound)
                    {
                        pu8Cache[u32CacheParsed] = '\0';
                        pu8Cache[u32CacheParsed+1] = '\0';
                        memcpy( (void*)_PA2VA( SUBTITLE_BUFFER_ADR+m_u8SubtitleTrackNum*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos), (void*)&pu8Cache[u32TagStart], u32CacheParsed+2-u32TagStart);
                        u32SubtitlePos += u32CacheParsed+2-u32TagStart;
                        enDvdSubtitleParse = E_PARSE_DONE;
                    }
                    break;

                case E_PARSE_DONE:
                    pTag[m_u16SubtitleTagCount].u32TimeStart = (u32Hour1*3600+u32Min1*60+u32econd1)*1000+u32ms1;
                    pTag[m_u16SubtitleTagCount].u32TimeEnd = (u32Hour2*3600+u32Min2*60+u32econd2)*1000+u32ms2;
                    pTag[m_u16SubtitleTagCount].u32SubtitlePos = u32PrevSubPos;

                    u32PrevSubPos = u32SubtitlePos;
                    u32CacheParsed+=2;
                    m_u16SubtitleTagCount++;
                    bRet = TRUE;
                    //printf(" Tag[%d] %02ld %02ld %02ld %02ld    %02ld %02ld %02ld %02ld\n", m_u16SubtitleTagCount, u32Hour1, u32Min1, u32econd1, u32ms1, u32Hour2, u32Min2, u32econd2, u32ms2);
                    if(m_u16SubtitleTagCount >= SUBTITLE_TAG_NUM_MAX)
                    {
                        goto _MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END;
                    }
                    enDvdSubtitleParse = E_PARSE_INIT;
                default:
                    break;
            }

            if(u32CacheParsed >= SUBTITLE_SMALL_BUF_SIZE)
            {   // Read the next block of data.
                if(enDvdSubtitleParse == E_PARSE_INIT)
                {
                    m_u32CurSubtitleFilePos += u32CacheParsed;
                }
                else
                {
                    m_u32CurSubtitleFilePos = u32PrevTagPos;
                    enDvdSubtitleParse = E_PARSE_INIT;
                }
                //printf(" ----------> read next block %lx\n", m_u32CurSubtitleFilePos);
                memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, SUBTITLE_SMALL_READ_BUF_SIZE);
                msAPI_DataStreamIO_Seek(m_u8FileNo, m_u32CurSubtitleFilePos, E_DATA_STREAM_SEEK_SET);
                msAPI_DataStreamIO_Read(m_u8FileNo, (void*)MP4_SUBTITLE_BUFFER_ADR, SUBTITLE_SMALL_READ_BUF_SIZE);
                u32CacheParsed = 0;
            }

            msAPI_Timer_ResetWDT();
            if(msAPI_Timer_DiffTimeFromNow(u32ParsingTime) > SUBTITLE_PARSING_TIMEOUT)
            {
                goto _MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END;
            }

        }
    }

_MApp_MPlayer_SUB_DvdSubtitleSystem_Parser_END:
    if(bRet)
    {
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleCodingType = *pCodingType;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].eSubtitleType = E_MPLAYER_SUBTITLE_DVDSUBTITLESYSTEM;
        m_MPlayerSubtitleInfo[m_u8SubtitleTrackNum].u16SubtitleTagEnd = m_u16SubtitleTagCount-1;
        m_u8SubtitleTrackNum++;
      #if (ENABLE_EXTERNAL_SUBTITLE_TAG_SORTING)
        qsort(pTag, m_u16SubtitleTagCount, sizeof(MPlayer_Subtitle_Tag), _MApp_MPlayer_SubtitleTagCompare);
      #endif
    }

    return bRet;
}
#endif //#if (ENABLE_SUBTITLE_SUB)
#endif  // #if (ENABLE_SMALL_BUF_SUBTITLE)

void MApp_MPlayer_SubtitleSetFileHandle(U8 u8FileNo)
{
    m_u32CurSubtitleFilePos = 0;
    m_u8FileNo = u8FileNo;
}

void MApp_MPlayer_SubtitleSetFileInfo(FileEntry* pFileEntry)
{
    memcpy(&FileEntrySubtitle, pFileEntry,sizeof(FileEntry));
}

BOOLEAN MApp_MPlayer_OpenSubtitleFileHandle(void)
{
    m_u8FileNo = msAPI_FCtrl_FileOpen(&FileEntrySubtitle, OPEN_MODE_FOR_READ);

    if(FCTRL_INVALID_FILE_HANDLE == m_u8FileNo)
    {
        SMALL_BUF_DBG(printf("Open file failed\n"));
        return FALSE;
    }
    SMALL_BUF_DBG(printf(" !!!!! MApp_MPlayer_OpenSubtitleFileHandle %d!!!!!\n", m_u8FileNo));
    return TRUE;
}

void MApp_MPlayer_CloseSubtitleFileHandle(void)
{
    if(m_u8FileNo != FCTRL_INVALID_FILE_HANDLE)
    {
        msAPI_FCtrl_FileClose(m_u8FileNo);
        m_u8FileNo = FCTRL_INVALID_FILE_HANDLE;
        SMALL_BUF_DBG(printf(" !!!!! MApp_MPlayer_CloseSubtitleFileHandle !!!!!\n"));
    }
}

#if (ENABLE_SMALL_BUF_SUBTITLE)
//******************************************************************************
/// Enable read buffer empty flag to reload apposite subtitle buffer
/// Check read buffer empty flag in SubtitleParser_Main() and reload file data to buffer
/// @param  bEnable \b IN TRUE:   reload apposite subtitle buffer
///                       FALSE:  otherwise
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
BOOLEAN MApp_MPlayer_EnableReloadAppositeSubtitleBuf(BOOLEAN bEnable)
{
    m_bIsReadBufferEmpty = bEnable;

    return TRUE;
}


//******************************************************************************
/// Using binary search to find subtitle buffer index
/// @param  u32Time \b Specify current movie time for search.
/// @return u16AppositeIdx subtitle buffer index
//******************************************************************************
static U16 _MApp_MPlayer_Subtitle_BinarySearchBuffByCurTime(U32 u32Time)
{
    U32 u32Pts1, u32Pts2;
    S32 s32Start, s32End, s32Pos;
    BOOLEAN bContinue = TRUE;
    S32 s32SubtitleTagCount;
    U16 u16AppositeIdx=0;

    s32Start = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u16SubtitleTagStart;
    s32End = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u16SubtitleTagEnd + 1;

    s32SubtitleTagCount = s32End;

    U32 *pu32Index = (U32 *)_PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8CurTrackIdx*PER_SUBTITLE_INDEX_SIZE);

    while(bContinue)
    {
        s32Pos = (s32Start + s32End) / 2;
        u32Pts1 = pu32Index[s32Pos];

        if(u32Time >= u32Pts1)
        {
            if(s32Pos < (s32SubtitleTagCount - 1))
            {
                u32Pts2 = pu32Index[s32Pos+1];

                if(u32Time < u32Pts2)
                {
                    u16AppositeIdx = s32Pos;
                    bContinue = FALSE;
                }
                else
                {
                    s32Start = s32Pos + 1;
                    if(s32Start > s32End)
                    {
                        bContinue = FALSE;
                    }
                }
            }
            else
            {
                u16AppositeIdx = s32Pos;
                bContinue = FALSE;
            }
        }
        else if(u32Time < u32Pts1)
        {
            if(s32Pos > 0)
            {
                u32Pts2 = pu32Index[s32Pos-1];

                if(u32Time >= u32Pts2)
                {
                    u16AppositeIdx = s32Pos - 1;
                    bContinue = FALSE;
                }
                else
                {
                    if(s32Pos == m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u16SubtitleTagStart)
                    {
                        u16AppositeIdx = s32Pos;
                        bContinue = FALSE;
                    }
                    s32End = s32Pos - 1;
                    if(s32Start > s32End)
                    {
                        bContinue = FALSE;
                    }
                }
            }
            else
            {
                bContinue = FALSE;
            }
        }
    }

    return u16AppositeIdx;
}

//******************************************************************************
/// reload apposite subtitle buffer by current movie time
/// @param  u32Time \b current movie time
/// @return N/A
//******************************************************************************
static void _MApp_MPlayer_ReloadAppositeSubtitleBuf(U32 u32Time)
{
    if(m_u8SubtitleTrackNum == 0 || m_u8FileNo == FCTRL_INVALID_FILE_HANDLE)
    {
        return;
    }

    U16 u16AppositeIdx=0;

    U32 *pu32Index = (U32 *)_PA2VA(SUBTITLE_INDEX_BUF_ADDR+m_u8CurTrackIdx*PER_SUBTITLE_INDEX_SIZE);

    u16AppositeIdx = _MApp_MPlayer_Subtitle_BinarySearchBuffByCurTime(u32Time);

     //Consider that SMI has many classes in one file, if parser from previous block, timeout happened easily
     //SMI: no multi-subttile at the same time
    if(m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleType != E_MPLAYER_SUBTITLE_SMI
        #if ENABLE_SUBTITLE_SUBIDX
        && m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleType != E_MPLAYER_SUBTITLE_SUBIDX
        #endif
        )
    {
        //search forward to find the first block if there are continuous same PTS blocks
        while(u16AppositeIdx>0)
        {
            if(pu32Index[u16AppositeIdx] == pu32Index[u16AppositeIdx-1])
            {
                u16AppositeIdx--;
            }
            else
            {
                u16AppositeIdx--; //for safety search one more previous block
                break;
            }
        }
        //for safety search one more previous block
        //also need to search forward to find the first block if there are continuous same PTS blocks
        while(u16AppositeIdx>0)
        {
            if(pu32Index[u16AppositeIdx] == pu32Index[u16AppositeIdx-1])
            {
                u16AppositeIdx--;
            }
            else
            {
                break;
            }
        }
    }

    U32 u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);
    U32 u32OffsetPerIndex = SUBTITLE_USED_READ_BUF_LEN*_MApp_MPlayer_ComputeOffsetTimesBetweenSubtitleIndex(u32FileSize);
    memset((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), 0, SUBTITLE_READ_BUF_LEN);
    msAPI_DataStreamIO_Seek(m_u8FileNo, u16AppositeIdx*u32OffsetPerIndex, E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(m_u8FileNo, (void*)SUBTITLE_READ_BUF_ADDR, SUBTITLE_READ_BUF_LEN);

    m_u32CurSubtitleFilePos = u16AppositeIdx*u32OffsetPerIndex;
    m_u32SubtitleBufParsed = 0;
    SMALL_BUF_DBG(printf("RELOAD BUFF, Index: %d, Pts: %d ms, FilePos: %d, Parsed: %d\n"
    ,u16AppositeIdx, pu32Index[u16AppositeIdx], m_u32CurSubtitleFilePos, m_u32SubtitleBufParsed));

    //Check unicode big endian identifier. If yes, transfer data from big endian to little endian.
    if(m_MPlayerSubtitleInfo[m_u8CurTrackIdx].bBE2LE == TRUE)
    {
        _MApp_MPlayer_UnicodeBE2UnicodeLE((void*)_PA2VA(SUBTITLE_READ_BUF_ADDR), SUBTITLE_READ_BUF_LEN);
    }
    m_bIsReadBufferEmpty = FALSE;


    MApp_MPlayer_ResetAliveTextSubtitleStatus();
}

//******************************************************************************
/// Get one subtitle from _MApp_MPlayer_XXX_ParseOneSubtitle by current subtitle type
/// check read buffer empty flag is TRUE, and reload file data to buffer
/// @param  u32Time \b current movie time
/// @return N/A
//******************************************************************************
void MApp_MPlayer_SubtitleParser_Main(U32 u32Time)
{
    if(m_u8SubtitleTrackNum == 0 || m_u8FileNo == FCTRL_INVALID_FILE_HANDLE)
    {
        return;
    }

    typedef EN_PARSE_ONE_SUBTITLE_RET (*PF_PARSE_ONE_SUBTITLE)(MPlayer_Subtitle_Tag *pSubtitleTag, U32 u32SubtitlePhyAddr);

    PF_PARSE_ONE_SUBTITLE pfParseOneSubtitle = NULL;
    enumMPlayerSubtitleType eSubtitleType = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleType;

    switch(eSubtitleType)
    {
        case E_MPLAYER_SUBTITLE_SRT:
            pfParseOneSubtitle = _MApp_MPlayer_SRT_ParseOneSubtitle;
            break;
#if (ENABLE_SUBTITLE_SUBIDX)
        case E_MPLAYER_SUBTITLE_SUBIDX:
            pfParseOneSubtitle = _MApp_MPlayer_SUBIDX_ParseOneSubtitle;
            break;
#endif
        case E_MPLAYER_SUBTITLE_SSA:
        case E_MPLAYER_SUBTITLE_ASS:
            pfParseOneSubtitle = _MApp_MPlayer_SSA_ParseOneSubtitle;
            break;
#if (ENABLE_SUBTITLE_SMI)
        case E_MPLAYER_SUBTITLE_SMI:
            pfParseOneSubtitle = _MApp_MPlayer_SMI_ParseOneSubtitle;
            break;
#endif
#if (ENABLE_SUBTITLE_TXT)
        case E_MPLAYER_SUBTITLE_TMPLAYER:
            pfParseOneSubtitle = _MApp_MPlayer_TMPlayer_ParseOneSubtitle;
            break;
        case E_MPLAYER_SUBTITLE_TTXT:
            pfParseOneSubtitle = _MApp_MPlayer_TTXT_ParseOneSubtitle;
            break;
        case E_MPLAYER_SUBTITLE_TXT:
            pfParseOneSubtitle = _MApp_MPlayer_TXT_ParseOneSubtitle;
            break;
#endif
#if (ENABLE_SUBTITLE_SUB)
        case E_MPLAYER_SUBTITLE_SUBVIEWER:
            pfParseOneSubtitle = _MApp_MPlayer_SubViewer_ParseOneSubtitle;
            break;

        case E_MPLAYER_SUBTITLE_MICRODVD:
            pfParseOneSubtitle = _MApp_MPlayer_MicroDVD_ParseOneSubtitle;
            break;
        case E_MPLAYER_SUBTITLE_SUBRIPPER:
            pfParseOneSubtitle = _MApp_MPlayer_SubRipper_ParseOneSubtitle;
            break;
        case E_MPLAYER_SUBTITLE_DVDSUBTITLESYSTEM:
            pfParseOneSubtitle = _MApp_MPlayer_DvdSubtitleSystem_ParseOneSubtitle;
            break;
#endif
        default:
            break;
    }

    if(pfParseOneSubtitle == NULL)
    {
        return;
    }

    if(m_bIsReadBufferEmpty == TRUE)
    {
        _MApp_MPlayer_ReloadAppositeSubtitleBuf(u32Time);
    }

    U32 u32SubtitleBufPhyAddr;

    while(m_u16SubtitleTagCnt < MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT)
    {
        u32SubtitleBufPhyAddr = SUBTITLE_BUFFER_ADR+m_u16SubtitleEndPos*SUBTITLE_MAX_SIZE;
      #if ENABLE_SUBTITLE_SUBIDX
        if(eSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {
            if(msAPI_MpegSP_SpuQueue_GetCount() < 2)
            {
                if(pfParseOneSubtitle(&m_astExternalTextSubtitleTag[0],u32SubtitleBufPhyAddr) == E_PARSE_ONE_SUBTITLE_DONE)
                {
                    MApp_MPlayer_PushSubtitleSUB(&m_astExternalTextSubtitleTag[0]);
                }
            }
            return;
        }
      #endif
        if(pfParseOneSubtitle(&m_astExternalTextSubtitleTag[m_u16SubtitleEndPos],u32SubtitleBufPhyAddr) == E_PARSE_ONE_SUBTITLE_DONE)
        {
            if(m_astExternalTextSubtitleTag[m_u16SubtitleEndPos].u32TimeEnd > u32Time)
            {
                SMALL_BUF_DBG(printf("[SMALL SUBTITLE][Cnt:%d]CurTime: %d ms, Start Pts: %d ms, End Pts: %d ms\n"
                ,m_u16SubtitleTagCnt, u32Time, m_astExternalTextSubtitleTag[m_u16SubtitleEndPos].u32TimeStart, m_astExternalTextSubtitleTag[m_u16SubtitleEndPos].u32TimeEnd));

                m_u16SubtitleEndPos++;
                m_u16SubtitleTagCnt++;
                m_u16SubtitleEndPos%= MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT;
            }
        }
        else
        {
            return;
        }
    }
}
#endif  //#if (ENABLE_SMALL_BUF_SUBTITLE)

void MApp_MPlayer_SubtitleInit(void)
{
    m_u16SubtitleTagCount = 0;
    m_u8SubtitleTrackNum = 0;
    m_u8CurTrackIdx = 0;
    m_eType = E_MPLAYER_SUBTITLE_INVALID;
    m_bIsUnicode = FALSE;
    m_u32SubtitleDelaySteps   = 0;
    m_u32SubtitleAdvanceSteps = 0;
    m_u8FileNo = FCTRL_INVALID_FILE_HANDLE;
#if (ENABLE_SUBTITLE_SUB)
    m_u32MicroDVDFrameRate = 0;
#endif
#if ENABLE_SMALL_BUF_SUBTITLE
    m_bIsReadBufferEmpty = TRUE;
#endif
}

//******************************************************************************
/// Deinit the variables of subtitle task
/// @param  N/A
/// @return BOOLEAN
//******************************************************************************
BOOLEAN MApp_MPlayer_SubtitleDeInit(void)
{
    m_u8SubtitleTrackNum = 0;

    return TRUE;
}

BOOLEAN MApp_MPlayer_Subtitle_Parser(enumMPlayerSubtitleType *peType, U32 u32FileSize, enumMplayerSubtitleCoding *pCodingType)
{
    typedef BOOLEAN (*PF_SUBTITLE)(U32 u32FileSize, enumMplayerSubtitleCoding *pbIsUnicode);
    U8 u8TypeIndex = 0, u8Cnt;
    BOOLEAN bRet = FALSE;

    //printf("*peType<%d> \n", *peType);

    if(MApp_MPlayer_OpenSubtitleFileHandle()==FALSE)
    {
        return FALSE;
    }

    u32FileSize = msAPI_FCtrl_FileLength(m_u8FileNo);

    typedef struct stSubtitle
    {
        PF_SUBTITLE pfSubtitle;
        enumMPlayerSubtitleType eSubtitleType;
    }ST_SUBTITLE;

    ST_SUBTITLE astSubtitle[] = {
        {_MApp_MPlayer_SRT_Parser, E_MPLAYER_SUBTITLE_SRT},
#if (ENABLE_SUBTITLE_SUBIDX)
        {_MApp_MPlayer_SUBIDX_Parser, E_MPLAYER_SUBTITLE_SUBIDX},
#endif
        {_MApp_MPlayer_SSA_Parser, E_MPLAYER_SUBTITLE_SSA},
        {_MApp_MPlayer_SSA_Parser, E_MPLAYER_SUBTITLE_ASS},
#if (ENABLE_SUBTITLE_SMI)
        {_MApp_MPlayer_SMI_Parser, E_MPLAYER_SUBTITLE_SMI},
#endif
#if (ENABLE_SUBTITLE_TXT)
        {_MApp_MPlayer_TMPlayer_Parser, E_MPLAYER_SUBTITLE_TMPLAYER},
        {_MApp_MPlayer_TTXT_Parser, E_MPLAYER_SUBTITLE_TTXT},
        {_MApp_MPlayer_TXT_Parser, E_MPLAYER_SUBTITLE_TXT},
#endif
#if (ENABLE_SUBTITLE_SUB)
        {NULL, E_MPLAYER_SUBTITLE_SUB}, //sub type is a group includes SUBVIEWER, MICRODVD, DVDSUBTITLESYSTEM
        {_MApp_MPlayer_SubViewer_Parser, E_MPLAYER_SUBTITLE_SUBVIEWER},
        {_MApp_MPlayer_MicroDVD_Parser, E_MPLAYER_SUBTITLE_MICRODVD},
        {_MApp_MPlayer_SubRipper_Parser, E_MPLAYER_SUBTITLE_SUBRIPPER},
        {_MApp_MPlayer_DvdSubtitleSystem_Parser, E_MPLAYER_SUBTITLE_DVDSUBTITLESYSTEM},
#endif
    };

    U8 u8NumberOfastSubtitle = sizeof(astSubtitle)/sizeof(astSubtitle[0]);

    //find the corresponding type in struct of astSubtitle
    for(u8TypeIndex=0; u8TypeIndex < u8NumberOfastSubtitle; u8TypeIndex++)
    {
        if(*peType == astSubtitle[u8TypeIndex].eSubtitleType)
        {
            break;
        }
    }

    //We will check the TypeIndex which we found first , because we will trust the extension file name first
    //If TypeIndex is incorrect , we will check others by sequencial
    for(u8Cnt=0; u8Cnt < u8NumberOfastSubtitle; u8Cnt++,u8TypeIndex++)
    {
        u8TypeIndex = u8TypeIndex % u8NumberOfastSubtitle;

        if(astSubtitle[u8TypeIndex].pfSubtitle !=NULL)
        {
            if(astSubtitle[u8TypeIndex].pfSubtitle(u32FileSize, pCodingType))
            {
                *peType = astSubtitle[u8TypeIndex].eSubtitleType;
                printf("%s found\n", _gSubtitleName[*peType]);
                bRet = TRUE;
                break;
            }
        }
    }

    MApp_MPlayer_CloseSubtitleFileHandle();

    if(bRet==FALSE)
    {
    *peType = E_MPLAYER_SUBTITLE_INVALID;
    }

    return bRet;
}

//******************************************************************************
/// reset alive text subtitle status
/// @param  void
/// @return  TRUE: Success , FALSE: FAIL
//******************************************************************************
BOOLEAN MApp_MPlayer_ResetAliveTextSubtitleStatus(void)
{
    m_u32PreMovieTimer = 0;
    m_s32PreSubtitleIdx = -1;
    m_s32DeadSubtitleIdx = -1;
#if (ENABLE_SMALL_BUF_SUBTITLE)
    m_u16SubtitleEndPos=0;
    m_u16SubtitleTagCnt=0;
#endif

    return TRUE;
}

#if (ENABLE_SMALL_BUF_SUBTITLE)
//******************************************************************************
/// Refresh external text subtitle tag queue, skip expired tags.
/// @param  u32Time \b IN  Specify the time in milliseconds.
/// @return void
//******************************************************************************
void MApp_MPlayer_RefreshTextSubtitleTag(U32 u32Time)
{
    U8 u8Count, u8SkipCnt=0;
    U16 u16TagIdx=0xFFFF, u16TagIdx2;
    U16 u16TempSubtitleTagCnt;
    MPlayer_Subtitle_Tag Tag;

    if(m_u16SubtitleTagCnt>0)
    {
        //u16tagposition is end of the ring queue.
        //u16SubtitleTagCnt is number of tags in ring queue.
        u16TagIdx = ((m_u16SubtitleEndPos+MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT - m_u16SubtitleTagCnt)%MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT);

        //skip expired tags which have a larger start time than the next tag.
        if(m_u16SubtitleTagCnt>1)
        {
            for(u8Count=0; u8Count<m_u16SubtitleTagCnt-1; u8Count++)
            {
                u16TagIdx2 = (u16TagIdx+1)%MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT;

                if(m_astExternalTextSubtitleTag[u16TagIdx2].u32TimeStart
                 < m_astExternalTextSubtitleTag[u16TagIdx].u32TimeStart)
                {
                    u8SkipCnt = u8Count+1; //max skip count = u16SubtitleTagCnt-1
                }
                u16TagIdx = u16TagIdx2;
            }
            m_u16SubtitleTagCnt -= u8SkipCnt;
        }

        //senario: When queue is full and then rewind/jump backward, new tag from VDPlayer cannot push to queue.
        //solution: if queue is full and previous time > current time(after rewind/jump backward), will clear queue buffer
        if(m_u16SubtitleTagCnt >= MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT && m_u32PreMovieTimer > u32Time)
        {
            MApp_MPlayer_ResetAliveTextSubtitleStatus();
        }
        m_u32PreMovieTimer = u32Time;

        u16TagIdx = ((m_u16SubtitleEndPos+MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT - m_u16SubtitleTagCnt)%MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT);
        u16TempSubtitleTagCnt = m_u16SubtitleTagCnt;

        //skip expired tags which have a smaller end time than current time.
        for(u8Count=0; u8Count<u16TempSubtitleTagCnt; u8Count++)
        {
            Tag = m_astExternalTextSubtitleTag[u16TagIdx];

            if(Tag.u32TimeEnd <= u32Time)
            {
                m_u16SubtitleTagCnt--;
            }
            else
            {
                break;
            }
            u16TagIdx = (u16TagIdx+1)%MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT;
        }
    }
}

//******************************************************************************
/// Get alive external text subtitle tags.
/// @param  u32Time             \b IN  Specify the time in milliseconds.
/// @param  pu8AliveSubtitleNum \b OUT Return the number of alive external text subtitle
/// @param  pAliveSubtitles     \b OUT Return the alive external text subtitle tags.
/// @param  bSubtitleShownFLG   \b IN  Specify the text subtitle is shown or not.
/// @return number of alive external text subtitle tags.
//******************************************************************************
BOOLEAN MApp_MPlayer_GetAliveTextSubtitleTag(U32 u32Time, U8* pu8AliveSubtitleNum, MPlayer_Subtitle_Tag *pAliveSubtitles, BOOLEAN bSubtitleShownFLG)
{
    U8 u8Count, u8AliveSubtitleNum = 0;
    U16 u16TagIdx=0xFFFF;
    U16 u16CurSubtitleTagIdx=0xFFFF;
    MPlayer_Subtitle_Tag Tag;
#if (ENABLE_SUBTITLE_SMI)
    enumMPlayerSubtitleType eExternalSubtitleType;
    eExternalSubtitleType = (enumMPlayerSubtitleType)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_TYPE);
#endif

    MApp_MPlayer_RefreshTextSubtitleTag(u32Time);

    if(m_u16SubtitleTagCnt > 0)
    {
        //m_u16SubtitleEndPos is end of the ring queue.
        //u16SubtitleTagCnt is number of tags in ring queue.
        u16TagIdx = ((m_u16SubtitleEndPos+MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT - m_u16SubtitleTagCnt)%MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT);

        //find current tag.
        for(u8Count=0; u8Count<m_u16SubtitleTagCnt; u8Count++)
        {
            Tag = m_astExternalTextSubtitleTag[u16TagIdx];

            if(Tag.u32TimeStart <= u32Time)
            {
                u16CurSubtitleTagIdx = u16TagIdx;
            }
            else
            {
                if(u8Count==0)
                {
                    //Can not find the subtitle which time is less or equal to u32Time.
                    return FALSE;
                }
                break;
            }
            u16TagIdx = (u16TagIdx+1)%MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT;
        }

    #if 0// (ENABLE_SUBTITLE_SMI)
        if(eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI)
        {
            //SMI doesn't have end time stamp.
            //skip expired tags before current tag.
            m_u16SubtitleTagCnt -= (u8Count-1);
        }
    #endif

        if(bSubtitleShownFLG)
        {
            if(m_s32PreSubtitleIdx == u16CurSubtitleTagIdx)
            {
                //if current tag is equal to previous tag, no need to refresh subtitle.
                return FALSE;
            }
        }
        m_s32PreSubtitleIdx = u16CurSubtitleTagIdx;

    #if 0//(ENABLE_SUBTITLE_SMI)
        if(eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI)
        {
            if(u16CurSubtitleTagIdx < MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT)
            {
                //SMI doesn't have end time stamp.
                //SMI can not support multiple subtitle.
                Tag = m_astExternalTextSubtitleTag[u16CurSubtitleTagIdx];
                if(Tag.u32TimeEnd > u32Time) //check end time to avoid last subtitle is shown
                {
                    pAliveSubtitles[0] = Tag;
                    u8AliveSubtitleNum = 1;
                }
            }
        }
        else
    #endif
        {
            u16TagIdx = ((m_u16SubtitleEndPos+MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT - m_u16SubtitleTagCnt)%MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT);

            //printf("EndPos<%d> u16Tag<%d> IdxagCnt<%d>\n", m_u16SubtitleEndPos, u16TagIdx, m_u16SubtitleTagCnt);

            //find alive internal text subtitle tags.
            for(u8Count=0; u8Count<m_u16SubtitleTagCnt; u8Count++)
            {
                Tag = m_astExternalTextSubtitleTag[u16TagIdx];

                if(Tag.u32TimeStart <= u32Time)
                {
                    if(Tag.u32TimeEnd > u32Time)
                    {
                        pAliveSubtitles[u8AliveSubtitleNum] = Tag;
                        u8AliveSubtitleNum++;

                        if(u8AliveSubtitleNum >= MAX_ALIVE_SUBTITLE_NUM)
                        {
                            break;
                        }
                    }
                }
                u16TagIdx = (u16TagIdx+1)%MAX_EXTERNAL_TEXT_SUBTITLE_TAG_COUNT;
            }
        }
    }

    *pu8AliveSubtitleNum = u8AliveSubtitleNum;

    if(*pu8AliveSubtitleNum)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#else //#if(ENABLE_SMALL_BUF_SUBTITLE)
BOOLEAN MApp_MPlayer_GetAliveTextSubtitleTag(U32 u32Time, U8* pu8AliveSubtitleNum, MPlayer_Subtitle_Tag *pAliveSubtitles, BOOLEAN bSubtitleShownFLG)
{
    U16 u16CurSubtitleIdx;

    u16CurSubtitleIdx = MApp_MPlayer_SearchSubtitleTag(u32Time);

    if(m_u32PreMovieTimer > u32Time)
    {
        m_s32DeadSubtitleIdx = -1;
    }
    m_u32PreMovieTimer = u32Time;

    if(bSubtitleShownFLG)
    {
        if(m_s32PreSubtitleIdx == u16CurSubtitleIdx)
        {
            return FALSE;
        }
    }
    m_s32PreSubtitleIdx = u16CurSubtitleIdx;

    if(u16CurSubtitleIdx==0xFFFF)
    {
        *pu8AliveSubtitleNum = 0;
        return FALSE;
    }

    MPlayer_Subtitle_Tag *Subtitle_Tag;
    U8 u8AliveSubtitleCnt = 0;
    BOOLEAN bDeadContinued = TRUE;

    Subtitle_Tag = (MPlayer_Subtitle_Tag *)_PA2VA((((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8CurTrackIdx*SUBTITLE_TAG_BUFFER_PER_TRACK));

#if (ENABLE_SUBTITLE_SMI)
    enumMPlayerSubtitleType eExternalSubtitleType;
    eExternalSubtitleType = (enumMPlayerSubtitleType)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_TYPE);

    if(eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI)
    {
        //SMI doesn't have end time stamp.
        //SMI can not support multiple subtitle.
        pAliveSubtitles[0]= Subtitle_Tag[u16CurSubtitleIdx];
        u8AliveSubtitleCnt = 1;
    }
    else
#endif
    {
        U16 i;
        for(i=m_s32DeadSubtitleIdx+1; i <= u16CurSubtitleIdx; i++)
        {
            if(Subtitle_Tag[i].u32TimeEnd <= u32Time)
            {
                if(bDeadContinued)
                {
                    ++m_s32DeadSubtitleIdx;
                }
            }
            else
            {
                bDeadContinued = FALSE;
                pAliveSubtitles[u8AliveSubtitleCnt]= Subtitle_Tag[i];
                ++u8AliveSubtitleCnt;

                if(u8AliveSubtitleCnt >= MAX_ALIVE_SUBTITLE_NUM)
                {
                    break;
                }
            }
        }
    }
    *pu8AliveSubtitleNum = u8AliveSubtitleCnt;

    if(*pu8AliveSubtitleNum)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//only for external text and external image subtitle.
U16 MApp_MPlayer_SearchSubtitleTag(U32 u32Time)
{
    // Find the subtitle which time is less or equal to u32Time.
    MPlayer_Subtitle_Tag Tag1, Tag2;
    S32 s32Start;
    S32 s32End;
    S32 s32Pos;
    BOOLEAN bContinue = TRUE;
    S32 s32SubtitleTagCount;
    U16 u16TagIdx=0xFFFF;
/*
    if(m_bInternalSubtitle)
    {
        s32Start = 0;
        s32End = ( MP4_SUBTITLE_BUFFER_LEN >> 8) - MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TAGCOUNT);
    }
    else
*/
    {
        s32Start = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u16SubtitleTagStart;
        s32End = m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u16SubtitleTagEnd + 1;
    }
    s32SubtitleTagCount = s32End;

    while(bContinue)
    {
        s32Pos = (s32Start + s32End) / 2;
        Tag1 = *(MPlayer_Subtitle_Tag *)_PA2VA((((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8CurTrackIdx*SUBTITLE_TAG_BUFFER_PER_TRACK+(U32)s32Pos*sizeof(MPlayer_Subtitle_Tag)));

        if(u32Time >= Tag1.u32TimeStart)
        {
            if(s32Pos < (s32SubtitleTagCount - 1))
            {
                Tag2 = *(MPlayer_Subtitle_Tag *)_PA2VA((((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8CurTrackIdx*SUBTITLE_TAG_BUFFER_PER_TRACK+((U32)s32Pos+1)*sizeof(MPlayer_Subtitle_Tag)));

                if(u32Time < Tag2.u32TimeStart)
                {
                    u16TagIdx = s32Pos;
                    bContinue = FALSE;
                }
                else
                {
                    s32Start = s32Pos + 1;
                    if(s32Start > s32End)
                    {
                        bContinue = FALSE;
                    }
                }
            }
            else
            {
                u16TagIdx = s32Pos;
                bContinue = FALSE;
            }
        }
        else if(u32Time < Tag1.u32TimeStart)
        {
            if(s32Pos > 0)
            {
                Tag2 = *(MPlayer_Subtitle_Tag *)_PA2VA((((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8CurTrackIdx*SUBTITLE_TAG_BUFFER_PER_TRACK+((U32)s32Pos-1)*sizeof(MPlayer_Subtitle_Tag)));

                if(u32Time >= Tag2.u32TimeStart)
                {
                    u16TagIdx = s32Pos - 1;
                    bContinue = FALSE;
                }
                else
                {
                    if(s32Pos == m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u16SubtitleTagStart)
                    {
                        u16TagIdx = s32Pos;
                        bContinue = FALSE;
                    }
                    s32End = s32Pos - 1;
                    if(s32Start > s32End)
                    {
                        bContinue = FALSE;
                    }
                }
            }
            else
            {
                bContinue = FALSE;
            }
        }
    }

    return u16TagIdx;
}

BOOLEAN MApp_MPlayer_GetSubtitleTag(MPlayer_Subtitle_Tag *pTag, U32 u32Time)
{
    U16 u16TagIdx;

    if(m_bInternalSubtitle)
    {
        u16TagIdx = MApp_VDPlayer_GetTextSubtitleTag(pTag, u32Time);
        if(u16TagIdx != 0xFFFF)
        {
            return TRUE;
        }
        else
            return FALSE;
    }
    else
    {
        u16TagIdx = MApp_MPlayer_SearchSubtitleTag(u32Time);
    }

    if(u16TagIdx != 0xFFFF)
    {
        *pTag = *(MPlayer_Subtitle_Tag *)_PA2VA((((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+m_u8CurTrackIdx*SUBTITLE_TAG_BUFFER_PER_TRACK+((U32)u16TagIdx)*sizeof(MPlayer_Subtitle_Tag)));
        return TRUE;
    }
    return FALSE;
}
#endif// #if(ENABLE_SMALL_BUF_SUBTITLE)

#if (ENABLE_SUBTITLE_SUBIDX)
BOOLEAN MApp_MPlayer_GetSubtitleTagByIdx(MPlayer_Subtitle_Tag *pTag, U16 u16Idx)
{
#if(ENABLE_SMALL_BUF_SUBTITLE==0)
    if(u16Idx >= m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u16SubtitleTagStart &&
       u16Idx <= m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u16SubtitleTagEnd)
    {
        memcpy(pTag, (void*)_PA2VA((U32)MP4_SUBTITLE_TAG_ADR+m_u8CurTrackIdx*SUBTITLE_TAG_BUFFER_PER_TRACK+(U32)u16Idx*sizeof(MPlayer_Subtitle_Tag)), sizeof(MPlayer_Subtitle_Tag));
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#else
    UNUSED(pTag);
    UNUSED(u16Idx);
    return TRUE;
#endif
}
#endif //#if (ENABLE_SUBTITLE_SUBIDX)

void MApp_MPlayer_SetInternalSubtitle(BOOLEAN bEnable)
{
    m_bInternalSubtitle = bEnable;
}

BOOLEAN MApp_MPlayer_EnableInternalSubtitle(BOOLEAN bEnable)
{
#if (ENABLE_INTERNAL_SUBTITLE)
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
    U32 u32SubtitleType = MApp_VDPlayer_GetSubtitleInfo(E_SUBTITLE_INFO_TYPE);
    if(bEnable)
    {
        switch(u32SubtitleType)
        {
        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
            msAPI_MpegSP_Show();
            break;
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
        if(u8IsFontTableReady)
        {
            msAPI_MpegSP_Show();
        }
            break;
#endif
        default:
            break;
        }
    }
    else
    {
        switch(u32SubtitleType)
        {
        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
            msAPI_MpegSP_Unshow();
            break;
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
        if(u8IsFontTableReady)
        {
            msAPI_MpegSP_Unshow();
        }
            break;
#endif
        default:
            break;
        }
    }
#endif

    MApp_VDPlayer_ShowTSSubtitle(bEnable);
    return TRUE;
#else
    UNUSED(bEnable);
    return FALSE;
#endif
}

//****************************************************************************
/// Set subtitle track by track ID
/// @param u8TrackId \b IN: Track ID
/// @return TRUE if success, FALSE otherwise
//****************************************************************************
BOOLEAN MApp_MPlayer_SetSubtitleTrackID(U8 u8TrackId)
{
    if(u8TrackId < m_u8SubtitleTrackNum)
    {
    #if ENABLE_SMALL_BUF_SUBTITLE
        if(m_u8FileNo == FCTRL_INVALID_FILE_HANDLE)
        {
            m_u8FileNo = msAPI_FCtrl_FileOpen(&m_MPlayerSubtitleInfo[u8TrackId].stFileEntry, OPEN_MODE_FOR_READ);
        }
        else if(u8TrackId != m_u8CurTrackIdx)
        {
            msAPI_FCtrl_FileClose(m_u8FileNo);
            m_u8FileNo = msAPI_FCtrl_FileOpen(&m_MPlayerSubtitleInfo[u8TrackId].stFileEntry, OPEN_MODE_FOR_READ);
        }
        m_bIsReadBufferEmpty = TRUE;
    #endif
        m_u8CurTrackIdx = u8TrackId;
        return TRUE;
    }
    return FALSE;
}

U32 MApp_MPlayer_GetInfo(enumExtSutitleInfo eInfo)
{
    switch(eInfo)
    {
        case E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK:
            return (U32)m_u8SubtitleTrackNum;

        case E_MPLAYER_EXT_SUBTITLE_INFO_TRACK_ID:
            return (U32)m_u8CurTrackIdx;

        case E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_TYPE:
            return (U32)m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleType;
        case E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_CODING_TYPE:
            return (U32)m_MPlayerSubtitleInfo[m_u8CurTrackIdx].eSubtitleCodingType;

        default:
            break;
    }
    return 0;
}

BOOLEAN MApp_MPlayer_GetSubtitleInByTrackID(U8 u8TrackId, MPlayerSubtitleInfo *pInfo)
{
    if(u8TrackId < m_u8SubtitleTrackNum)
    {
        memcpy(pInfo, &m_MPlayerSubtitleInfo[u8TrackId], sizeof(MPlayerSubtitleInfo));
        return TRUE;
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_TS_Subtitle_Delete_OSDGWIN()
/// @brief \b Function \b Description : Delete OSD GWIN
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
static void MApp_TS_Subtitle_Delete_OSDGWIN( void )
{
    U16 u16StretchWidth;
    U16 u16StretchHeight;

    _bSubtitleOn = TRUE;

    // always set OSD on top
    MApi_GOP_GWIN_OutputLayerSwitch(E_GOP_OSD);

    if(_bGOP2OP)
        MApi_GOP_GWIN_SetGOPDst( E_GOP_APP, E_GOP_DST_OP0);
    else
        MApi_GOP_GWIN_SetGOPDst( E_GOP_APP, E_GOP_DST_IP0);

    MApi_GOP_GWIN_SwitchGOP( E_GOP_APP );

    if(_bGOP2OP)
    {
        u16StretchWidth = g_IPanel.Width()< 720 ? g_IPanel.Width(): 720;
        u16StretchHeight= g_IPanel.Height()< 576 ? g_IPanel.Height(): 576;
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0, u16StretchWidth, u16StretchHeight);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, u16StretchWidth, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, u16StretchHeight, g_IPanel.Height());
    }
    else
    {
        u16StretchWidth = (_u16_video_width > 1920) ? 1920 : _u16_video_width;
        u16StretchHeight= (_u16_video_height> 1080) ? 1080 : _u16_video_height;

        // If HD reduce gwin to 1/2 video width and using GOP stretch to video width
        if(u16StretchWidth >= 1280)
        {
			msAPI_Subtitle_SetReduceGwin(TRUE);
            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_IP0,0, 0, u16StretchWidth/2, u16StretchHeight);
            MApi_GOP_GWIN_Set_HSCALE(TRUE,1,2);
        }
        else
        {
			msAPI_Subtitle_SetReduceGwin(FALSE);
            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_IP0,0, 0, u16StretchWidth, u16StretchHeight);
            MApi_GOP_GWIN_Set_HSCALE(TRUE,1,1);
        }
        MApi_GOP_GWIN_Set_VSCALE(TRUE,1,1);
    }

#if (ENABLE_VOP_DUPLICATE)
    if(MDrv_MVOP_GetIsHDuplicate())
    {
        MApi_GOP_GWIN_Set_HSCALE(TRUE, _u16_video_width, _u16_video_width*2);
    }
#endif


}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_TS_Subtitle_Restore_OSDGWIN()
/// @brief \b Function \b Description : Restore OSD GWIN
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
static void MApp_TS_Subtitle_Restore_OSDGWIN( void )
{
    _bSubtitleOn = FALSE;

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    MApi_GOP_GWIN_Set_HSCALE(TRUE,1,1);
    MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0,0, g_IPanel.Width(), g_IPanel.Height());
    MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_OP0);
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    msAPI_MIU_Set_DRAM2DRAM_Mode( TRUE );
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_TS_Subtitle_Switch2OP()
/// @brief \b Function \b Description : Switch GOP
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_TS_Subtitle_Switch2OP( void )
{
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    MApi_GOP_GWIN_Switch2Gwin(_u8OriGWId);
    msAPI_OSD_SetClipWindow(_u16OriX0, _u16OriY0, _u16OriX1, _u16OriY1);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_TS_Subtitle_Switch2OP()
/// @brief \b Function \b Description : Switch GOP
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_TS_Subtitle_Switch2IP( void )
{
    MApi_GOP_GWIN_SwitchGOP( E_GOP_APP );
    _u8OriGWId = MApi_GOP_GWIN_GetCurrentWinId();
    msAPI_OSD_GetClipWindow(&_u16OriX0, &_u16OriY0, &_u16OriX1, &_u16OriY1);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_TS_Subtitle_Display_Initial()
/// @brief \b Function \b Description : Main Subtitle Initial
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b BOOLEAN : FALSE if Subtitle Initial Fail
////////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_TS_Subtitle_Display_Initial( void )
{
    if((_u16_video_width == 0) || (_u16_video_height == 0))
    {
        return FALSE;
    }

    if(!_bSubtitleOn)
    {
    #if(ENABLE_MIU_1)
        #ifdef GOP_GWIN_RB2_ADR
        #if(GOP_GWIN_RB2_MEMORY_TYPE&MIU1)
            MApi_GOP_MIUSel(E_GOP_APP, E_GOP_SEL_MIU1);
        #else
            MApi_GOP_MIUSel(E_GOP_APP, E_GOP_SEL_MIU0);
        #endif
        #endif
    #endif

        MApp_TS_Subtitle_Delete_OSDGWIN();
        msAPI_MIU_SetRoundRobin(FALSE);

        if(_bGOP2OP)
        {
            msAPI_Subtitle_Init_Display_OP();
        }
        else
        {
            msAPI_Subtitle_Init_Display(_u16_video_width, _u16_video_height);
        }
    }
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_TS_Subtitle_Exit()
/// @brief \b Function \b Description : Exit Subtitle Gwin Display
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_TS_Subtitle_Exit(void)
{
    if(_bSubtitleOn)
    {
        msAPI_Subtitle_DeInit();
        msAPI_MIU_SetRoundRobin(TRUE);
        MApp_TS_Subtitle_Restore_OSDGWIN();
    }
}
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_TS_Subtitle_SetShowStatus(BOOLEAN bShowStatus)
/// @brief \b Function \b Description : Set Subtitle show status
///
/// @param <IN>        \b BOOLEAN : subtitle can show or not in exclusive mode
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_TS_Subtitle_SetShowStatus(BOOLEAN bShowStatus)
{
    m_bShowTsSubtitle = bShowStatus;
    if(!bShowStatus)
    {
        MApp_TS_Subtitle_Exit();
    }
    else
    {
        MApp_TS_Subtitle_Remove();
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name:MApp_TS_Subtitle_Main(U32 u32Stc)
/// @brief \b Function \b Description : MM TS Subtitle decode main loop
///
/// @param <IN>         \b U32 u32Stc :system time for check pts to keep subtitle sync
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_TS_Subtitle_Main(U32 u32Stc)
{
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
    if(m_bShowTsSubtitle == FALSE)
    {
        MApp_TS_Subtitle_Exit();
        return;
    }
#endif

    msAPI_Subtitle_Remove_Expired(u32Stc);
    if(msAPI_Subtitle_CheckPTS(u32Stc))
    {
        msAPI_Subtitle_SetFreeRunTime(35);
        MApp_TS_Subtitle_Switch2IP();  // switch to E_GOP_APP for subtitle.record current status.
        if(MApp_TS_Subtitle_Display_Initial())
        {
            msAPI_Subtitle_Decoder_Main();
        }
        MApp_TS_Subtitle_Switch2OP();  // switch to OSD for icon.restore status.
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_TS_Subtitle_Get_SubtitleOSDState()
/// @brief \b Function \b Description : Get Subtitle on/off status
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b BOOLEAN : FALSE if Subtitle turn off
////////////////////////////////////////////////////////////////////////////////
U8 MApp_TS_Subtitle_Get_SubtitleOSDState(void)
{
    return _bSubtitleOn;
}

void MApp_TS_Subtitle_SetVideoInfo(U16 u16VideoWidth, U16 u16VideoHeight)
{
    _u16_video_width = u16VideoWidth;
    _u16_video_height = u16VideoHeight;
}

void MApp_TS_Subtitle_Remove(void)
{
    U32 u32Stc = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_PTS);
    msAPI_Subtitle_Remove(u32Stc*90);//remove the subtitles whose pts is less than u32Stc*90
}

static void _MApp_MPlayer_GetMovieSubtitle(U8 *pu8Dst, U32 u32BufSize, U32 u32SubtitlePos)
{
    U16 u16Src, u16Dst, u16Tmp;
    U8 *pu8Src;
    U32 u32CurTrk;

    if(u32SubtitlePos == 0xFFFFFFFF)
    {
        pu8Dst[0] = '\0';
        pu8Dst[1] = '\0';
        return;
    }

#if (ENABLE_SMALL_BUF_SUBTITLE)
    u32CurTrk = u16Tmp = 0;
    if(eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL)
    {
        MApp_MPlayer_Subtitle_GetSubtitle(pu8Dst, u32BufSize, u32SubtitlePos);
    }
    else
    {   // Internal subtitle, assume it is UTF8.
        pu8Src = (U8*)_PA2VA((((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+u32SubtitlePos));

        for(u16Dst=0,u16Src=0;u16Dst<SUBTITLE_MAX_SIZE;)
        {
            if(pu8Src[u16Src] == '\0')
            {
                pu8Dst[u16Dst] = '\0';
                pu8Dst[u16Dst+1] = '\0';
                break;
            }
            else if(pu8Src[u16Src] == '\r')
            {
                pu8Dst[u16Dst] = '\0';
                pu8Dst[u16Dst+1] = '\r';
                u16Src++;
                u16Dst+=2;
            }
            else if(pu8Src[u16Src] == '\n')
            {   // Skip '\n'.
                u16Src++;
            }
            else if(pu8Src[u16Src] & 0x80)   // Not ASCII
            {
                if((pu8Src[u16Src] & 0xF0) == 0xE0)
                {   // 3-byte
                    pu8Dst[u16Dst] = (pu8Src[u16Src] << 4) | ((pu8Src[u16Src+1] >> 2) & 0x0F);
                    pu8Dst[u16Dst+1] = (pu8Src[u16Src+1] << 6) | (pu8Src[u16Src+2] & 0x3F);
                    u16Dst += 2;
                    u16Src += 3;
                }
                else if((pu8Src[u16Src] & 0xE0) == 0xC0)
                {   // 2-byte
                    pu8Dst[u16Dst] = (pu8Src[u16Src] >> 2) & 0x07;
                    pu8Dst[u16Dst+1] = (pu8Src[u16Src+1] << 6) | (pu8Src[u16Src+2] & 0x3F);
                    u16Dst += 2;
                    u16Src += 2;
                }
                else
                {
                    u16Src++;
                }
            }
            else
            {
                pu8Dst[u16Dst] = '\0';
                pu8Dst[u16Dst+1] = pu8Src[u16Src];
                u16Src++;
                u16Dst+=2;
            }
        }

        pu8Dst[SUBTITLE_MAX_SIZE] = '\0';
        pu8Dst[SUBTITLE_MAX_SIZE+1] = '\0';
    }
#else  //#if (ENABLE_SMALL_BUF_SUBTITLE)

    u32BufSize = u32BufSize; //remove compile warning
    u32CurTrk = MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_TRACK_ID);

    if(m_eExternalSubtitleType==E_MPLAYER_SUBTITLE_INVALID)
        pu8Src = (U8*)_PA2VA((((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+u32SubtitlePos));
    else
        pu8Src = (U8*)_PA2VA((SUBTITLE_BUFFER_ADR+u32CurTrk*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos));

    if(eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL)
    {
        U32 eSubtitleCodingType = MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_CODING_TYPE);
        if(eSubtitleCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
        {
            for(u16Dst=0,u16Src=0;u16Dst<SUBTITLE_MAX_SIZE;)
            {
                if(pu8Src[u16Src] == '\0' && pu8Src[u16Src+1] == '\0')
                {
                    pu8Dst[u16Dst] = '\0';
                    pu8Dst[u16Dst+1] = '\0';
                    break;
                }
                else if(pu8Src[u16Src] == '\r' && pu8Src[u16Src+1] == '\0')
                {
                    pu8Dst[u16Dst+1] = 0xE0;
                    pu8Dst[u16Dst] = 0x8A;
                    u16Src+=2;
                    u16Dst+=2;
                }
                else if(pu8Src[u16Src] == '\n' && pu8Src[u16Src+1] == '\0')
                {   // Skip '\n'.
                    u16Src+=2;
                }
            #if (ENABLE_SUBTITLE_SUB)
                else if(pu8Src[u16Src] == '|' && pu8Src[u16Src+1] == '\0')
                {
                    if(pu8Src[u16Src] == '|')
                    {
                        pu8Dst[u16Dst+1] = 0xE0;
                        pu8Dst[u16Dst] = 0x8A; //MicroDVD & Subviewer10 change line
                        u16Src+=2;
                        u16Dst+=2;
                    }
                }
                else if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBVIEWER) &&
                        ((pu8Src[u16Src] == '[')&&(pu8Src[u16Src+1] == '\0')) &&
                        ((pu8Src[u16Src+2] == 'b')&&(pu8Src[u16Src+3] == '\0')) &&
                        ((pu8Src[u16Src+4] == 'r')&&(pu8Src[u16Src+5] == '\0')) &&
                        ((pu8Src[u16Src+6] == ']')&&(pu8Src[u16Src+7] == '\0')))
                {
                    pu8Dst[u16Dst+1] = 0xE0;
                    pu8Dst[u16Dst] = 0x8A; //Subviewer changeline
                    u16Dst+=2;
                    u16Src += 8;
                }
            #endif //#if (ENABLE_SUBTITLE_SUB)

            #if (ENABLE_SUBTITLE_SMI)
                else if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI) &&
                        ((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == '\0')) &&
                        ((pu8Src[u16Src+2] == 'b')&&(pu8Src[u16Src+3] == '\0')) &&
                        ((pu8Src[u16Src+4] == 'r')&&(pu8Src[u16Src+5] == '\0')) &&
                        ((pu8Src[u16Src+6] == '>')&&(pu8Src[u16Src+7] == '\0')))
                {
                    pu8Dst[u16Dst+1] = 0xE0;
                    pu8Dst[u16Dst] = 0x8A; //Subviewer changeline
                    u16Dst+=2;
                    u16Src += 8;
                }
#endif
                else
                {
                    pu8Dst[u16Dst+1] = pu8Src[u16Src+1];
                    pu8Dst[u16Dst] = pu8Src[u16Src];
                    u16Src+=2;
                    u16Dst+=2;
                }
            }
        }
        else
        {
            for(u16Dst=0,u16Src=0;u16Dst<SUBTITLE_MAX_SIZE;)
            {
                if(isprint(pu8Src[u16Src]) || (pu8Src[u16Src] == 0x09))
                {
                    pu8Dst[u16Dst+1] = '\0';
                    pu8Dst[u16Dst] = pu8Src[u16Src];

                #if (ENABLE_SUBTITLE_SUB)
                    if(pu8Src[u16Src] == '|')
                    {
                        pu8Dst[u16Dst] = 0x8A; //MicroDVD & Subviewer10 change line
                        pu8Dst[u16Dst+1] = 0xE0;
                    }
                    else if((pu8Src[u16Src] == '[')&&(pu8Src[u16Src+1] == 'b')
                            &&(pu8Src[u16Src+2] == 'r')&&(pu8Src[u16Src+3] == ']')
                            && (m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBVIEWER))
                    {
                        pu8Dst[u16Dst] = 0x8A; //Subviewer20 changeline
                        pu8Dst[u16Dst+1] = 0xE0;
                        u16Src += 3;
                    }
                #endif //#if (ENABLE_SUBTITLE_SUB)

                #if (ENABLE_SUBTITLE_SMI)
                     if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'b')
                            &&(pu8Src[u16Src+2] == 'r')&&(pu8Src[u16Src+3] == '>')
                            &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                    {
                        pu8Dst[u16Dst] = 0x8A; //SMI changeline
                        pu8Dst[u16Dst+1] = 0xE0;
                        u16Src += 3;
                    }
                #endif

                    u16Src++;
                    u16Dst+=2;
                }
                else if(pu8Src[u16Src] == '\0')
                {
                    pu8Dst[u16Dst] = '\0';
                    pu8Dst[u16Dst+1] = '\0';
                    break;
                }
                else if(pu8Src[u16Src] == '\r')
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\r';
                    u16Src++;
                    u16Dst+=2;
                }
                else if(pu8Src[u16Src] == '\n')
                {   // Skip '\n'.
                    u16Src++;
                }
                else
                {   // It is GB code.
                    u16Tmp = ((pu8Src[u16Src+1]) | ((pu8Src[u16Src])<<8));
                    u16Tmp = MApp_Transfer2Unicode(u16Tmp);
                    memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                    u16Src+=2;
                    u16Dst+=2;
                }
            }
        }
    }
    else
    {   // Internal subtitle, assume it is UTF8.
        for(u16Dst=0,u16Src=0;u16Dst<SUBTITLE_MAX_SIZE;)
        {
            if(pu8Src[u16Src] == '\0')
            {
                pu8Dst[u16Dst] = '\0';
                pu8Dst[u16Dst+1] = '\0';
                break;
            }
            else if(pu8Src[u16Src] == '\r')
            {
                pu8Dst[u16Dst+1] = 0xE0;//'\0';
                pu8Dst[u16Dst] = 0x8A;//'\r';
                u16Src++;
                u16Dst+=2;
            }
            else if(pu8Src[u16Src] == '\n')
            {   // Skip '\n'.
                u16Src++;
            }
            else if((pu8Src[u16Src] == '\\') && ((pu8Src[u16Src + 1] == 'n') || (pu8Src[u16Src + 1] == 'N')))
            {
                pu8Dst[u16Dst+1] = 0xE0;//'\0';
                pu8Dst[u16Dst] = 0x8A;//'\r';
                u16Src+=2;
                u16Dst+=2;
            }
            else if(pu8Src[u16Src] & 0x80)   // Not ASCII
            {
                if((pu8Src[u16Src] & 0xF0) == 0xE0)
                {   // 3-byte
                    pu8Dst[u16Dst+1] = (pu8Src[u16Src] << 4) | ((pu8Src[u16Src+1] >> 2) & 0x0F);
                    pu8Dst[u16Dst] = (pu8Src[u16Src+1] << 6) | (pu8Src[u16Src+2] & 0x3F);
                    u16Dst += 2;
                    u16Src += 3;
                }
                else if((pu8Src[u16Src] & 0xE0) == 0xC0)
                {   // 2-byte
                    pu8Dst[u16Dst+1] = (pu8Src[u16Src] >> 2) & 0x07;
                    pu8Dst[u16Dst] = (pu8Src[u16Src+1] << 6) | (pu8Src[u16Src+2] & 0x3F);
                    u16Dst += 2;
                    u16Src += 2;
                }
                else
                {
                    u16Src++;
                }
            }
            else
            {
                pu8Dst[u16Dst+1] = '\0';
                pu8Dst[u16Dst] = pu8Src[u16Src];
                u16Src++;
                u16Dst+=2;
            }
        }

        pu8Dst[SUBTITLE_MAX_SIZE] = '\0';
        pu8Dst[SUBTITLE_MAX_SIZE+1] = '\0';
    }
#endif  //#if (ENABLE_SMALL_BUF_SUBTITLE)

#if 0
    for(u16Dst=0;u16Dst<96;u16Dst++)
    {
        if((u16Dst%16)==0)
            printf("\n");
        printf("%02x ", pu8Dst[u16Dst]);
    }
    printf("\n");
#endif
}


#if (ENABLE_SUBTITLE_SUBIDX)
static BOOLEAN _MApp_MPlayer_PushMovieSubtitleSUB(void)
{
    #define FIRST_READ_SIZE         4096
    #define READ_BUF_ADR            (((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+MP4_SUBTITLE_BUFFER_LEN/2)
    U32 u32SubtitleBuff;
    U8 *pu8Data;
    U16 *pu16Data;
    U16 u16DataIdx;
    BOOLEAN bRet=FALSE;
    U16 u16PacketLen;
    U16 u16HeaderLen, u16CopyLen;
    U16 u16SubtitleLen, u16SubtitleLenAligned, u16SubtitleDstPos;
    U32 u32ReadBufAddr;

    u16SubtitleLen = 0;
    if((u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB != FCTRL_INVALID_FILE_HANDLE) &&
       (MApp_MPlayer_GetSubtitleTagByIdx(&m_Subtitle_Tag, m_u16ExternalSubtitleIdx)))
    {
        u32ReadBufAddr = READ_BUF_ADR;

        if(msAPI_DataStreamIO_Seek(u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB,
                                m_Subtitle_Tag.u32SubtitlePos,
                                E_DATA_STREAM_SEEK_SET) == FALSE)
        {
            goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
        }
        if(0 != msAPI_DataStreamIO_Read(u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB,
                                     (void*)READ_BUF_ADR,
                                     FIRST_READ_SIZE))
        {
            goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
        }

        // Parse subtitle.
        u16SubtitleLen = 0;
        u16SubtitleDstPos = 0;
        u16DataIdx = 0;
        pu8Data = (U8 *)_PA2VA(u32ReadBufAddr);
        pu16Data = (U16 *)_PA2VA(u32ReadBufAddr);
        do
        {
            // Process start code
            if(*(U32*)_PA2VA((u32ReadBufAddr + u16DataIdx)) != 0xBA010000)
            {
                goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
            }
            u16DataIdx += 4;

            switch(pu8Data[u16DataIdx] & 0xC0)
            {
            case 0x40:
                u16DataIdx += 10;
                break;
            case 0x20:
                u16DataIdx += 8;
                break;
            default:
                goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
            }

            if((pu16Data[u16DataIdx>>1]!=0x0000) || (pu16Data[(u16DataIdx>>1)+1]!=0xBD01))    // private stream 1
            {
                goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
            }
            u16DataIdx += 4;
            u16PacketLen = ((pu8Data[u16DataIdx]<<8)|(pu8Data[u16DataIdx+1]));
            u16DataIdx+=2;
            if((pu8Data[u16DataIdx] & 0xC0) != 0x80)
            {
                goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
            }
            u16DataIdx += 2;
            u16HeaderLen = (U16)pu8Data[u16DataIdx];

            u16DataIdx += u16HeaderLen + 1 + 1;
            u16CopyLen = u16PacketLen - (u16HeaderLen + 4);


            if(u16SubtitleLen == 0)
            {
                // Read remain data to DRAM.
                u16SubtitleLen = ((pu8Data[u16DataIdx]<<8)|(pu8Data[u16DataIdx+1]));

                if(u16SubtitleLen == 0)
                {
                    goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
                }
                u16SubtitleLenAligned = (u16SubtitleLen + 0x7FF) & 0xF800;
                if(u16SubtitleLenAligned > FIRST_READ_SIZE)
                {
                    if(msAPI_DataStreamIO_Read(u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB,
                                            (void*)(READ_BUF_ADR+FIRST_READ_SIZE),
                                            u16SubtitleLenAligned-FIRST_READ_SIZE) != 0)
                    {
                        goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
                    }
                }
            }

            // Copy Subtitle to buffer.
            //msAPI_MIU_Copy((U32)(u32ReadBufAddr+u16DataIdx), (U32)(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+u16SubtitleDstPos), u16CopyLen, MIU_SDRAM2SDRAM);
            memcpy((U8 *)_PA2VA((((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+u16SubtitleDstPos)), (U8 *)_PA2VA((u32ReadBufAddr+u16DataIdx)), u16CopyLen);

            u16SubtitleDstPos += u16CopyLen;
            if(u16SubtitleDstPos >= u16SubtitleLen)
            {
                break;
            }

            u16DataIdx += u16CopyLen;

            if((u16DataIdx & 0x7FF) != 0)
            {
                goto _MApp_MPlayer_PushMovieSubtitleSUB_END;
            }
            else if(u16DataIdx >= FIRST_READ_SIZE)
            {
                u32ReadBufAddr += FIRST_READ_SIZE;
                u16DataIdx = 0;
                pu8Data = (U8 *)_PA2VA(u32ReadBufAddr);
                pu16Data = (U16 *)_PA2VA(u32ReadBufAddr);
            }

        } while(1);

        u32SubtitleBuff = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(u16SubtitleLen);

        if(u32SubtitleBuff >0)
        {
            memcpy((U8 *)_PA2VA(u32SubtitleBuff), (U8 *)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), u16SubtitleLen);

            msAPI_MpegSP_SpuQueue_Push(E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB,  //E_SUBTITLE_VIDEO_TYPE_MPEG4,
                       u32SubtitleBuff, u16SubtitleLen, m_Subtitle_Tag.u32TimeStart * 90, 0);
            m_u32NextExternalSubtitleStartTime = m_Subtitle_Tag.u32TimeStart;
        }
        bRet = TRUE;

_MApp_MPlayer_PushMovieSubtitleSUB_END:
        m_u16ExternalSubtitleIdx++;
    }

    return bRet;
}

static BOOLEAN _MApp_MPlayer_SetMovieMpegSubtitle(void)
{
    U32 u32CurTime;
    U32 u32TmpIdx;

    msAPI_MpegSP_Reset_SpuQueue();
    u32CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
    u32TmpIdx = MApp_MPlayer_SearchSubtitleTag(u32CurTime);

    if( u32TmpIdx != 0xFFFF)
    {
        m_u16ExternalSubtitleIdx = u32TmpIdx;
        _MApp_MPlayer_PushMovieSubtitleSUB();
        _MApp_MPlayer_PushMovieSubtitleSUB();
    }
    return TRUE;
}
#endif //#if (ENABLE_SUBTITLE_SUBIDX)

void MApp_MPlayer_Subtitle_Dinit(void)
{
    if(eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_VALID)
    {
        if(eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL)
        {
            if (eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_SHOWN)
            {
                if ((_gfnSubtitle != NULL) && ((_geNotifyAP == E_SUBTITLE_NOTIFY_AP_RAWDATA) || (_geNotifyAP == E_SUBTITLE_NOTIFY_AP_UNICODE)))
                {
                    (*_gfnSubtitle)(FALSE, 0, 0);
                }
            }
        }

        if(u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB != INVALID_DATA_STREAM_HDL )
        {
            msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB);
            u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB = INVALID_DATA_STREAM_HDL;
        }

        MApp_MPlayer_EnableInternalSubtitle(FALSE);

    #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
        msAPI_MpegSP_Reset_SpuQueue();
        msAPI_MpegSP_Dinit();
    #endif

        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
    }

    m_u32LyricSubtitleCurTime = 0;
    eSubtitleFlag = E_SUBTITLE_FLG_NULL;
    _geNotifyAP = E_SUBTITLE_NOTIFY_AP_NULL;
    _gfnSubtitle = NULL;

    if(_gpu8RenderTextData)
    {
        msAPI_Memory_Free(_gpu8RenderTextData, BUF_ID_FILEBROWER);
        _gpu8RenderTextData = NULL;
    }

    memset((U8 *)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))),0, MP4_SUBTITLE_BUFFER_LEN);
}

BOOLEAN MApp_MPlayer_EnableMovieSubtitle(void)
{
    eSubtitleFlag |= E_SUBTITLE_FLG_SUBTITLE_ENABLE;
    if(eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL)
    {
    #if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {
            msAPI_MpegSP_Show();
        }
    #endif
    }
    else
    {
        MApp_MPlayer_EnableInternalSubtitle(TRUE);
    }
    return TRUE;
}


BOOLEAN MApp_MPlayer_DisableMovieSubtitle(void)
{
    if(eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL)
    {
        if (eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_SHOWN)
        {
            if ((_gfnSubtitle != NULL) && ((_geNotifyAP == E_SUBTITLE_NOTIFY_AP_RAWDATA) || (_geNotifyAP == E_SUBTITLE_NOTIFY_AP_UNICODE)))
            {
                (*_gfnSubtitle)(FALSE, 0, 0);
            }
            eSubtitleFlag &= (enumSubtitleFlags)~E_SUBTITLE_FLG_SUBTITLE_SHOWN;
        }

    #if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {
            msAPI_MpegSP_Unshow();
        }
    #endif
    }
    else
    {
        MApp_MPlayer_EnableInternalSubtitle(FALSE);

        if (eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_SHOWN)
        {
            if ((_gfnSubtitle != NULL) && ((_geNotifyAP == E_SUBTITLE_NOTIFY_AP_RAWDATA) || (_geNotifyAP == E_SUBTITLE_NOTIFY_AP_UNICODE)))
            {
                (*_gfnSubtitle)(FALSE, 0, 0);
            }
            eSubtitleFlag &= (enumSubtitleFlags)~E_SUBTITLE_FLG_SUBTITLE_SHOWN;
        }
    }
    eSubtitleFlag &= (enumSubtitleFlags)~E_SUBTITLE_FLG_SUBTITLE_ENABLE;

    return TRUE;
}

BOOLEAN MApp_MPlayer_ChangeSubtitleTrack(U8 u8TrackId)
{
    if(E_SUBTITLE_FLG_SUBTITLE_EXTERNAL & eSubtitleFlag)
    {
        if(MApp_MPlayer_SetSubtitleTrackID(u8TrackId))
        {
        #if (ENABLE_SUBTITLE_SUBIDX)
            if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
            {
                _MApp_MPlayer_SetMovieMpegSubtitle();
            }
        #endif
            return TRUE;
        }
    }
    else
    {
        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK)>1)
        {
            if(MApp_VDPlayer_SetSubtitleTrackID(u8TrackId))
            {
                eSubtitleFlag |= E_SUBTITLE_FLG_SUBTITLE_VALID;
                MApp_MPlayer_EnableInternalSubtitle(TRUE);
                m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
                if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT))
                {
                    if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_ISUNICODE) )
                    {
                        m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
                    }
                    else
                    {
                        m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
                    }
                }
                return TRUE;
            }
        }
    }
    return FALSE;
}


U16 MApp_MPlayer_QuerySubtitleNum(void)
{
    if(E_SUBTITLE_FLG_SUBTITLE_EXTERNAL & eSubtitleFlag)
    {
        return((U16)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK));
    }
    else
    {
        return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK));
    }
}

U16 MApp_MPlayer_QueryCurSubtitleTrackIdx(void)
{
    if(E_SUBTITLE_FLG_SUBTITLE_EXTERNAL & eSubtitleFlag)
    {
        return((U16)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_TRACK_ID));
    }
    else
    {
        return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_SUBTITLE_TRACK_ID));
    }
}

BOOLEAN MApp_MPlayer_CurSubtitleIsText(void)
{
    if(E_SUBTITLE_FLG_SUBTITLE_EXTERNAL & eSubtitleFlag)
    {
#if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType != E_MPLAYER_SUBTITLE_SUBIDX)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
#else
        return TRUE;
#endif
    }
    else
    {
        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

}


BOOLEAN MApp_MPlayer_CurSubtitleIsUnicode(void)
{
    if(_geNotifyAP == E_SUBTITLE_NOTIFY_AP_UNICODE)
    {
        return TRUE;
    }
    else
    {
        if(m_eSubtitleCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
            return TRUE;
        else
            return FALSE;
    }
}

//check whether external subtitle is enabled now.
BOOLEAN MApp_MPlayer_ExternalSubtitleIsEnabled(void)
{
    if((eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL) == 0)
    {
        return FALSE;
    }
    else if(eSubtitleFlag &(E_SUBTITLE_FLG_SUBTITLE_VALID |E_SUBTITLE_FLG_SUBTITLE_ENABLE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//after video init, check internal subtitle is enabled.(only call once for every play)
void MApp_MPlayer_CheckInternalSubtitleEnabledFirst(void)
{
        //check whether codec finishes subtitl init
    if((eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL) == 0)
    {
        //enable internal subtitle
        MApp_VDPlayer_SetSubtitleShow( E_SUBTITLE_STATE_COMMAND_SHOW/*TRUE*/ );

        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK))
        {
            eSubtitleFlag &=
                (enumSubtitleFlags)~(E_SUBTITLE_FLG_SUBTITLE_EXTERNAL |
                                        E_SUBTITLE_FLG_SUBTITLE_ENABLE |
                                        E_SUBTITLE_FLG_SUBTITLE_VALID);
            eSubtitleFlag= E_SUBTITLE_FLG_INTL_SUBTITLE_FIRST;

            if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT))
            {
                eSubtitleFlag= (E_SUBTITLE_FLG_SUBTITLE_VALID | E_SUBTITLE_FLG_SUBTITLE_ENABLE);
                MApp_MPlayer_SetInternalSubtitle(TRUE);
                MApp_MPlayer_EnableInternalSubtitle(TRUE);
                if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_ISUNICODE) )
                {
                    m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
                }
                else
                {
                    m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
                }
                m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
                eSubtitleFlag &= (enumSubtitleFlags)~E_SUBTITLE_FLG_INTL_SUBTITLE_FIRST;
            }
        }
    }
}

//loop check whether internal subtitle is valid from codec.
BOOLEAN MApp_MPlayer_CheckInternalSubtitleValid(void)
{
    //check whether codec finishes subtitl init
    if(((eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL) == 0) &&
        (eSubtitleFlag & E_SUBTITLE_FLG_INTL_SUBTITLE_FIRST))
    {
            if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT))
            {
                eSubtitleFlag |= (E_SUBTITLE_FLG_SUBTITLE_VALID | E_SUBTITLE_FLG_SUBTITLE_ENABLE);
                MApp_MPlayer_SetInternalSubtitle(TRUE);
                MApp_MPlayer_EnableInternalSubtitle(TRUE);
                if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_ISUNICODE) )
                {
                    m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
                }
                else
                {
                    m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
                }
                m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;          //disable external subtitle
                eSubtitleFlag &= (enumSubtitleFlags)~E_SUBTITLE_FLG_INTL_SUBTITLE_FIRST;
            }
    }

    if ((eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_VALID)&& ((eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_EXTERNAL) == 0))
        return TRUE;

    return FALSE;
}

//draw external subtitle or internal text type subtitle
void  MApp_MPlayer_ExternalAndInternalTextSubtitleDraw()
{
    BOOLEAN bUpdateStatus = FALSE;
    BOOLEAN bShowSubtitile = FALSE;
    U32 u32TextDataAddress = 0;
    U16 u16Len = 0;

    if((eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_VALID) == 0 ||
        (eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_ENABLE) == 0)
        return ;

    if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>200)
    {
        U32 u32CurTime;

        // Deal with subtitle.
        u32CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);

        if(m_u32SubtitleDelaySteps != 0) // fetch N ms ago subtitle to display
        {
            u32CurTime = (u32CurTime > m_u32SubtitleDelaySteps * 100 ?
                                        u32CurTime - m_u32SubtitleDelaySteps * 100 : 0);
        }
        else if (m_u32SubtitleAdvanceSteps != 0)
        {
            u32CurTime += m_u32SubtitleAdvanceSteps * 100;
        }

    #if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {
            if( (u32CurTime > 0) &&
                (MApp_MPlayer_GetSubtitleTag(&m_Subtitle_Tag, u32CurTime)))
            {

                msAPI_MpegSP_Main(u32CurTime*90);

                if(m_Subtitle_Tag.u32TimeStart != m_u32LyricSubtitleCurTime)
                {
                    //msAPI_MpegSP_Main(u32CurTime*90);
                    if(msAPI_MpegSP_SpuQueue_GetCount() < 2)
                    {
                        _MApp_MPlayer_PushMovieSubtitleSUB();
                    }
                    //if(msAPI_MpegSP_SpuQueue_GetCount() < 2)
                    //{
                    //    _MApp_MPlayer_PushMovieSubtitleSUB();
                    //}
                    m_u32LyricSubtitleCurTime = m_Subtitle_Tag.u32TimeStart;
                }
            }
        }
        else
    #endif //#if (ENABLE_SUBTITLE_SUBIDX)
        {
            // Check if hide the current subtitle.
            if((eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_SHOWN) &&
               ((m_Subtitle_Tag.u32TimeEnd <= u32CurTime) ||
               // in RepeatAB mode, the current subtitle shall hide if jump to previous scenario
               m_Subtitle_Tag.u32TimeStart > u32CurTime))
            {
                if(_geNotifyAP == E_SUBTITLE_NOTIFY_AP_UNICODE || _geNotifyAP == E_SUBTITLE_NOTIFY_AP_RAWDATA)
                {
                    bShowSubtitile = FALSE;
                    bUpdateStatus = TRUE;
                }
                else if(_geNotifyAP == E_SUBTITLE_NOTIFY_MPLAYER)
                {
                    MApp_UiMediaPlayer_Notify(E_MPLAYER_NOTIFY_HIDE_SUBTITLE, NULL);
                }
                else
                {
                    bUpdateStatus = FALSE;
                }
                eSubtitleFlag &= (enumSubtitleFlags)~E_SUBTITLE_FLG_SUBTITLE_SHOWN;
            }
            if((u32CurTime > 0) &&
               (MApp_MPlayer_GetSubtitleTag(&m_Subtitle_Tag, u32CurTime)) &&
               ((m_Subtitle_Tag.u32TimeEnd > u32CurTime) && (m_Subtitle_Tag.u32TimeStart <= u32CurTime)))
            {
                if(m_Subtitle_Tag.u32TimeStart != m_u32LyricSubtitleCurTime)
                {
                    eSubtitleFlag |= E_SUBTITLE_FLG_SUBTITLE_SHOWN;
                    if(_geNotifyAP == E_SUBTITLE_NOTIFY_AP_RAWDATA)
                    {
                        bShowSubtitile = TRUE;
                        u32TextDataAddress = ((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+m_Subtitle_Tag.u32SubtitlePos;
                        bUpdateStatus = TRUE;
                        u16Len = SUBTITLE_MAX_SIZE;
                    }
                    else if(_geNotifyAP == E_SUBTITLE_NOTIFY_AP_UNICODE)
                    {
                        if(_gpu8RenderTextData)
                        {
                            _MApp_MPlayer_GetMovieSubtitle(_gpu8RenderTextData, SUBTITLE_MAX_SIZE, m_Subtitle_Tag.u32SubtitlePos);
                            bShowSubtitile = TRUE;
                            u32TextDataAddress = (U32)_gpu8RenderTextData;
                            bUpdateStatus = TRUE;
                            u16Len = SUBTITLE_MAX_SIZE;
                        }
                        else
                        {
                            bUpdateStatus = FALSE;
                        }
                    }
                    else if(_geNotifyAP == E_SUBTITLE_NOTIFY_MPLAYER)
                    {
                        MApp_UiMediaPlayer_Notify(E_MPLAYER_NOTIFY_SHOW_SUBTITLE, (void*)_gpu8RenderTextData);
                    }
                    else
                    {
                        bUpdateStatus = FALSE;
                    }

                    m_u32CurSubtitlePos = m_Subtitle_Tag.u32SubtitlePos;
                    m_u32LyricSubtitleCurTime = m_Subtitle_Tag.u32TimeStart;
                }
            }
        }
        m_u32PlayCheckTime = msAPI_Timer_GetTime0();

        if (bUpdateStatus && (_gfnSubtitle != NULL) && ((_geNotifyAP == E_SUBTITLE_NOTIFY_AP_RAWDATA) || (_geNotifyAP == E_SUBTITLE_NOTIFY_AP_UNICODE)))
        {
            (*_gfnSubtitle)(bShowSubtitile, u32TextDataAddress, u16Len);
        }
    }
}

void MApp_MPlayer_SetExternalSubtitleType(enumMPlayerSubtitleType eType)
{
    //need set type before init external subtitle
    if(eSubtitleFlag & E_SUBTITLE_FLG_SUBTITLE_INITED)
        return;

    if(eType < E_MPLAYER_SUBTITLE_NUM)
    {
        m_eExternalSubtitleType = eType;
    }
    else
    {
        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
    }
}

void MApp_MPlayer_Register_Notify(enumNotifyType eNotifyAPType, pfnDrawExternalSubtitle pfnSubtitle)
{
    _geNotifyAP = eNotifyAPType;
    _gfnSubtitle = pfnSubtitle;
}

BOOLEAN MApp_MPlayer_ExternalSubtitle_Parser(void *pSubtitleFile,void *pSubtitleSubFile)
{
    BOOLEAN bRet = FALSE;
    U32 u32FileSize;
    U32 u32VDPlayerStreamHandleIdx_ExternalSubtitle;
#if (ENABLE_SUBTITLE_SUBIDX)
    U32 SubFileSize;
#else
    UNUSED(pSubtitleSubFile);
#endif

    m_u32LyricSubtitleCurTime = 0;
    eSubtitleFlag = E_SUBTITLE_FLG_NULL;
    m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;
    u32VDPlayerStreamHandleIdx_ExternalSubtitle = INVALID_DATA_STREAM_HDL;
    u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB = INVALID_DATA_STREAM_HDL;
    m_u32PlayCheckTime = -1;

    MApp_MPlayer_SetInternalSubtitle(FALSE);

    if(_gpu8RenderTextData == NULL)
    {
        _gpu8RenderTextData = msAPI_Memory_Allocate(SUBTITLE_MAX_SIZE+2, BUF_ID_FILEBROWER);
        if(_gpu8RenderTextData == NULL)
        {
            __ASSERT(0);
            goto _MApp_MPlayer_Subtitle_Parser_END;
        }
    }

    if(m_eExternalSubtitleType >= E_MPLAYER_SUBTITLE_NUM)
    {
        goto _MApp_MPlayer_Subtitle_Parser_END;
    }

    MApp_MPlayer_SubtitleInit();

    if(INVALID_DATA_STREAM_HDL == (u32VDPlayerStreamHandleIdx_ExternalSubtitle = msAPI_DataStreamIO_Open(pSubtitleFile, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_EX_SUB0)))
    {
        goto _MApp_MPlayer_Subtitle_Parser_END;
    }
    MApp_MPlayer_SubtitleSetFileHandle(u32VDPlayerStreamHandleIdx_ExternalSubtitle);
    u32FileSize = msAPI_DataStreamIO_Length(u32VDPlayerStreamHandleIdx_ExternalSubtitle);
    if(u32FileSize == 0)
    {
        goto _MApp_MPlayer_Subtitle_Parser_END;
    }

    // Read file.
    memset((void*)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), 0, MP4_SUBTITLE_BUFFER_LEN);
    msAPI_DataStreamIO_Seek(u32VDPlayerStreamHandleIdx_ExternalSubtitle,0,E_DATA_STREAM_SEEK_SET);
    u32FileSize = MIN(u32FileSize, MP4_SUBTITLE_BUFFER_LEN);
    if(u32FileSize == msAPI_DataStreamIO_Read(u32VDPlayerStreamHandleIdx_ExternalSubtitle, (void*)((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), u32FileSize))
    {
        goto _MApp_MPlayer_Subtitle_Parser_END;
    }

    if(MApp_MPlayer_Subtitle_Parser(&m_eExternalSubtitleType, u32FileSize, &m_eSubtitleCodingType))
    {
        // for the caller to judge the encoding type
        msAPI_DataStreamIO_Seek(u32VDPlayerStreamHandleIdx_ExternalSubtitle,0,E_DATA_STREAM_SEEK_SET);
        msAPI_DataStreamIO_Read(u32VDPlayerStreamHandleIdx_ExternalSubtitle, (void*)((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), 0x10);

        msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_ExternalSubtitle);
        u32VDPlayerStreamHandleIdx_ExternalSubtitle = INVALID_DATA_STREAM_HDL;

    #if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {

            u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB = msAPI_DataStreamIO_Open(pSubtitleSubFile, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_EX_SUB1);
            SubFileSize = msAPI_DataStreamIO_Length(u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB);//?
            if(SubFileSize == 0)
            {
                msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_ExternalSubtitleSUB);
                goto _MApp_MPlayer_Subtitle_Parser_END;
            }
            m_u16ExternalSubtitleIdx = 0;
        }
    #endif
        eSubtitleFlag |= (E_SUBTITLE_FLG_SUBTITLE_VALID |
                                     E_SUBTITLE_FLG_SUBTITLE_ENABLE |
                                     E_SUBTITLE_FLG_SUBTITLE_EXTERNAL|
                                     E_SUBTITLE_FLG_SUBTITLE_INITED);
        bRet = TRUE;
    }

_MApp_MPlayer_Subtitle_Parser_END:
    if(INVALID_DATA_STREAM_HDL != u32VDPlayerStreamHandleIdx_ExternalSubtitle)
    {
        msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_ExternalSubtitle);
    }
    return bRet;
}

void MApp_MPlayer_SetSubtitleDelaySteps(U32 u32Steps)
{
    m_u32SubtitleDelaySteps  = u32Steps;
    m_u32SubtitleAdvanceSteps = 0;
}

void MApp_MPlayer_SetSubtitleAdvanceSteps(U32 u32Steps)
{
    m_u32SubtitleDelaySteps  = 0;
    m_u32SubtitleAdvanceSteps = u32Steps;
}

U32 MApp_MPlayer_GetCurExternalSubtitleLanguage(void)
{
    return m_MPlayerSubtitleInfo[m_u8CurTrackIdx].u32SubtitleLanguage;
}

//******************************************************************************
/// Query external subtitle language by subtitle track index.
/// @param u16SubtitleTrack \b IN: subtitle track index
/// @return four characters in U32
//******************************************************************************
U32 MApp_MPlayer_GetExternalSubtitleLanguageByTrackIndex(U16 u16SubtitleTrack)
{
    if(u16SubtitleTrack >= m_u8SubtitleTrackNum)
    {
        return 0;
    }

    return m_MPlayerSubtitleInfo[u16SubtitleTrack].u32SubtitleLanguage;
}

//******************************************************************************
/// Transfer data from unicode big endian to unicode little endian.
/// @param pBufferAddr \b IN/OUT: Specify pointer of unicode big endian data.
/// @param u32Len      \b IN    : Specify length of input buffer.
/// @return TRUE if success, FALSE otherwise
//******************************************************************************
static BOOLEAN _MApp_MPlayer_UnicodeBE2UnicodeLE(void *pBufferAddr, U32 u32Len)
{
    if(pBufferAddr == NULL)
    {
        return FALSE;
    }

    U16 *pu16BufferAddr = pBufferAddr;

    U32 i;

    for(i=0; i<u32Len/2; i++)
    {
        pu16BufferAddr[i] = (pu16BufferAddr[i] << 8) | (pu16BufferAddr[i] >> 8 );
    }

    return TRUE;
}
#endif //#if (ENABLE_SUBTITLE_DMP)
#endif  //#if (ENABLE_DMP)


////////////////////////////////////////////////////////////////////////////////
#undef MAPP_MPLAYER_SUBTITLE_C
