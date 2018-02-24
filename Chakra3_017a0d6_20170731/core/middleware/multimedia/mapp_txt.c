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

#define MAPP_TXT_C

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"

#include <stdio.h>
#include <string.h>

#include "debug.h"
// Global Layer
#include "datatype.h"
#include "sysinfo.h"
#include "MsTypes.h"
#include "apiPNL.h"//#include "Panel.h"

#ifdef MSOS_TYPE_LINUX
#include "MsIRQ.h"
#endif
#include "MsOS.h"

// API Layer
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_MIU.h"
#include "msAPI_Memory.h"
#include "msAPI_Timer.h"
#include "msAPI_FCtrl.h"

// AP Layer
#include "MApp_GlobalSettingSt.h"
#include "MApp_Exit.h"
#include "MApp_FileBrowser.h"

#include "mapp_txt.h"

#include "MApp_UiMediaPlayer_Define.h"
#include "MApp_UiMediaPlayer.h"

#include "mapp_gb2unicode.h"
#include "mapp_big52unicode.h"
#include "MApp_CharTable.h"

//panel module
#include "Panel.h"
#include "apiPNL.h"

#include "MApp_IR.h"
#include "msAPI_DataStreamIO.h"

#if (ENABLE_DMP)
#define msAPI_FS_FileSeek(x,y) msAPI_FCtrl_FileSeek(x,y,FILE_SEEK_SET)

#if ENABLE_MPLAYER_TEXT
#if  TEXT_SHOW_BYLENGTH
    static U8 TEXT_PREVIEW_CHAR_NUM_PER_LINE = 90;  //chars per line
#else
    static U8 TEXT_PREVIEW_CHAR_NUM_PER_LINE = 15;  //chars per line
#endif
static U8 TEXT_PREVIEW_LINE_NUM  =5 ; //line number in preview window
#if  TEXT_SHOW_BYLENGTH
    static U8 TEXT_CHAR_NUM_PER_LINE = 255;  //chars per line
#else
    static U8 TEXT_CHAR_NUM_PER_LINE = 40;  //chars per line
#endif
static U8 TEXT_LINE_NUM_PER_PAGE = 16;  //line number in full screen

#define TXT_BROWER_BUFFER_SIZE      (TEXT_CHAR_NUM_PER_LINE*2+2+16)
#define TXT_PREVIEW_BUFFER_SIZE     (TEXT_PREVIEW_CHAR_NUM_PER_LINE*2+2+16)

//static U8* pu8TextBufPool=(U8 *)((TEXT_DATA_READ_MEMORY_TYPE & MIU1) ? (TEXT_DATA_READ_ADR | MIU_INTERVAL) : (TEXT_DATA_READ_ADR));
//static U32* pu32TextBufPool=(U32 *)_PA2VA((void *)((TEXT_DATA_READ_MEMORY_TYPE & MIU1) ? (TEXT_DATA_READ_ADR | MIU_INTERVAL) : (TEXT_DATA_READ_ADR)));

static enumTextCharsetType m_enTextCharsetType = E_TEXT_CHARSET_DEFAULT;

typedef struct
{
    U32 u32TxtBuffStart;        //Text Buffer Start
    U32 u32TxtBuffSize;         //Text Buffer Size
    U32 u32TxtBuffPos;          //Text data start
    U32 u32TxtReqSize;          //Text request size
    U32 u32TxtReadSize;         //Text readback size
    U32 u32TxtBuffFilePos;      //The file postition of current buffer start address
}TEXT_TxtBuff;

static TEXT_TxtBuff TxtBuff;

// We suggest that TEXT_READ_BUFF_LEN should be larger than 1 MB.
// Otherwise, the USB IO increases with smaller buffer size. Total TEXT loading performance will be poor.
#if(defined(TEXT_READ_BUFF_ADR) && (TEXT_READ_BUFF_LEN > 0))
#define TEXT_FAST_LOAD_FILE 1
#else
#define TEXT_FAST_LOAD_FILE 0
#endif

#define TEXT_PAGE_OFFSET_SIZE       4 //sizeof(U32)
#if(defined(TEXT_INDEX_BUFF_ADR) && (TEXT_INDEX_BUFF_LEN > 0))
#define TEXT_PAGE_INDEX_BUFF_ADDR   (TEXT_INDEX_BUFF_ADR)
#define TEXT_MAX_PAGE_NUM           (TEXT_INDEX_BUFF_LEN/TEXT_PAGE_OFFSET_SIZE)
#else
    #if(TEXT_FILE_LEN < TEXT_BUFF_SIZE)
    #error "TEXT_FILE_LEN < TEXT_BUFF_SIZE"
    #endif
#define TEXT_PAGE_INDEX_BUFF_ADDR   (TEXT_FILE_ADR + TEXT_BUFF_SIZE)
#define TEXT_MAX_PAGE_NUM           ((TEXT_FILE_LEN - TEXT_BUFF_SIZE) / TEXT_PAGE_OFFSET_SIZE)
#endif

//File process
//static S8 s8FileName[16] = "VTS_04_1.TXT";
static U8 u8FileHandle = FCTRL_INVALID_FILE_HANDLE;
static BOOLEAN bFileEnd = FALSE;
static U8 u8FileType = EN_TEXT_ANSI;
static U32 u32FileLength = 0;
static U32 u32FilePos = 0;
static U32 u32MemPos = 0;
static U32 u32PageIndex = 0;
static U32 u32TotalPage = 0;

//static code U8 u8Dummy;
static FileEntry *m_pTextFileEntry;

#define TEXT_DEBUG(x)   //x
#if TEXT_SHOW_BYLENGTH
    static BOOL TEXT_GetData(U8 *buf, U8 *bufData, U32 len, BOOLEAN Preview);
#else
    static BOOL TEXT_GetData(U8 *buf, U8 *bufData, U32 len);
#endif
void TEXT_BrowserText(void);
extern U16 MApp_Transfer2Unicode(U16 u16Code);

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------
BOOLEAN TEXT_Init(void)
{
    U32 u32MemStart;
    U32 u32BuffSize;

#if TEXT_FAST_LOAD_FILE
    u32MemStart = (U32)(((TEXT_FILE_MEMORY_TYPE & MIU1) ? (TEXT_READ_BUFF_ADR | MIU_INTERVAL) : (TEXT_READ_BUFF_ADR)));
    u32BuffSize = TEXT_READ_BUFF_LEN;
#else
    u32MemStart = (U32)(((TEXT_FILE_MEMORY_TYPE & MIU1) ? (TEXT_FILE_ADR | MIU_INTERVAL) : (TEXT_FILE_ADR)));
    //U32 u32MemEnd = (U32)(((TEXT_FILE_MEMORY_TYPE & MIU1) ? (TEXT_FILE_ADR | MIU_INTERVAL) : (TEXT_FILE_ADR)) + TEXT_FILE_LEN);
    u32BuffSize = TEXT_BUFF_SIZE;
#endif

    if (g_IPanel.Height()==1080)
    {
        TEXT_DEBUG(printf("TEXT_Init() Height=1080\n"));
	 #if TEXT_SHOW_BYLENGTH
            TEXT_PREVIEW_CHAR_NUM_PER_LINE =90;  //chars per line
        #else
            TEXT_PREVIEW_CHAR_NUM_PER_LINE =15;  //chars per line
        #endif
        TEXT_PREVIEW_LINE_NUM = 5;  //line number in preview window
        #if TEXT_SHOW_BYLENGTH
            TEXT_CHAR_NUM_PER_LINE =255;//90   //chars per line
        #else
            TEXT_CHAR_NUM_PER_LINE =40;//90   //chars per line
        #endif
        TEXT_LINE_NUM_PER_PAGE = 16 ; //line number in full screen
    }
    else if (g_IPanel.Height()==900)
    {
        TEXT_DEBUG(printf("TEXT_Init() Height=900\n"));
	 #if TEXT_SHOW_BYLENGTH
            TEXT_PREVIEW_CHAR_NUM_PER_LINE =90;  //chars per line
        #else
            TEXT_PREVIEW_CHAR_NUM_PER_LINE =15;  //chars per line
        #endif
        TEXT_PREVIEW_LINE_NUM = 5; //line number in preview window
        #if TEXT_SHOW_BYLENGTH
            TEXT_CHAR_NUM_PER_LINE =255;//90   //chars per line
        #else
            TEXT_CHAR_NUM_PER_LINE =40;//90   //chars per line
        #endif
        TEXT_LINE_NUM_PER_PAGE  =16;  //line number in full screen
    }
    else if (g_IPanel.Height()==768)
    {
        TEXT_DEBUG(printf("TEXT_Init() Height=768\n"));
	 #if TEXT_SHOW_BYLENGTH
            TEXT_PREVIEW_CHAR_NUM_PER_LINE =90;  //chars per line
        #else
            TEXT_PREVIEW_CHAR_NUM_PER_LINE =15;  //chars per line
        #endif
        TEXT_PREVIEW_LINE_NUM  =5 ; //line number in preview window
        #if TEXT_SHOW_BYLENGTH
            TEXT_CHAR_NUM_PER_LINE =255;//90   //chars per line
        #else
            TEXT_CHAR_NUM_PER_LINE =40;//90   //chars per line
        #endif
        TEXT_LINE_NUM_PER_PAGE = 16;  //line number in full screen
    }
    else
    {
        TEXT_DEBUG(printf("TEXT_Init() Height=%x\n", g_IPanel.Height()));
	 #if TEXT_SHOW_BYLENGTH
            TEXT_PREVIEW_CHAR_NUM_PER_LINE =90;  //chars per line
        #else
            TEXT_PREVIEW_CHAR_NUM_PER_LINE =15;  //chars per line
        #endif
        TEXT_PREVIEW_LINE_NUM  =5;  //line number in preview window
        #if TEXT_SHOW_BYLENGTH
            TEXT_CHAR_NUM_PER_LINE =255;//90   //chars per line
        #else
            TEXT_CHAR_NUM_PER_LINE =40;//90   //chars per line
        #endif
        TEXT_LINE_NUM_PER_PAGE  =16;  //line number in full screen
    }

    TxtBuff.u32TxtBuffStart = u32MemStart;
    TxtBuff.u32TxtBuffSize = u32BuffSize;
    TxtBuff.u32TxtReadSize = 0;
    TxtBuff.u32TxtReqSize = 0;
    TxtBuff.u32TxtBuffFilePos = 0;
    TxtBuff.u32TxtBuffPos = TxtBuff.u32TxtBuffStart;

    // clear the memory
    memset((void*)_PA2VA(TxtBuff.u32TxtBuffStart),0,TxtBuff.u32TxtBuffSize);

    return TRUE;
}

BOOLEAN TEXT_FileOpen(S16 s16Index)
{
    BOOLEAN bRet = FALSE;
    TEXT_DEBUG(printf("TEXT file index 0x%lx.\n", (U32)s16Index));

    s16Index = s16Index;
    if ((u8FileHandle = msAPI_FCtrl_FileOpen(m_pTextFileEntry, OPEN_MODE_FOR_READ)) != FCTRL_INVALID_FILE_HANDLE)
    {
        bFileEnd = FALSE;
        bRet = TRUE;
        u32PageIndex = 0;
        u32FilePos = 0;
        u32MemPos = 0;
        u32FileLength = msAPI_FCtrl_FileLength(u8FileHandle);

        TEXT_DEBUG(printf("TEXT file handle 0x%x, Length 0x%x.\n", u8FileHandle, u32FileLength));
    }
    else
    {
        TEXT_DEBUG(printf("TEXT open file fail 0x%lx.\n", s16Index));
    }

    return bRet;
}

BOOLEAN TEXT_FileClose(void)
{
    BOOLEAN bRet = FALSE;
    if ((u8FileHandle != FCTRL_INVALID_FILE_HANDLE))
    {
        if (msAPI_FCtrl_FileClose(u8FileHandle))
        {
            u8FileHandle = FCTRL_INVALID_FILE_HANDLE;
            bFileEnd = FALSE;
            u32FilePos = 0;
            u32FileLength = 0;
            bRet = TRUE;
        }
        else
        {
            TEXT_DEBUG(printf("Close file fail %x.\n",u8FileHandle ));
        }
    }
    else
    {
        TEXT_DEBUG(printf("File is not open.\n"));
    }

    return bRet;
}
#if TEXT_FAST_LOAD_FILE
//******************************************************************************
/// File read. The default request maximum size is TEXT_BUFF_SIZE.
/// This function will fill the buffer and update the start pointer (u32TxtBuffPos)
/// @param  pTxtBuff \b IN  Specify the TEXT_TxtBuff structure.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN TEXT_FileRead(TEXT_TxtBuff* pTxtBuff)
{
    U32 u32ReqSize = 0;
    U32 u32TargetFilePos = u32FilePos;
    U32 u32TextReadSize = 0;
    U32 u32Target4KPos = (u32FilePos >> 12 ) << 12; //4k alignment
    TEXT_DEBUG(printf("\n[%d] u32TargetFilePos:%d u32Target4KPos:%d\n",__LINE__,u32TargetFilePos,u32Target4KPos));
    if(u8FileHandle == FCTRL_INVALID_FILE_HANDLE)
    {
        return FALSE;
    }

    if(u32FilePos > u32FileLength)
    {
        return FALSE;
    }

    if ((pTxtBuff->u32TxtReqSize > pTxtBuff->u32TxtBuffSize) ||
        (pTxtBuff->u32TxtReqSize == 0))
    {
        pTxtBuff->u32TxtReqSize = TEXT_BUFF_SIZE;
    }

    TEXT_DEBUG(printf("[%d] u32TxtBuffFilePos:%d u32TxtBuffFilePos:%d u32TxtBuffSize:%d\n",__LINE__,pTxtBuff->u32TxtBuffFilePos,pTxtBuff->u32TxtBuffFilePos,pTxtBuff->u32TxtBuffSize));

    if ((u32FilePos + pTxtBuff->u32TxtReqSize) <= u32FileLength)
    {
        u32ReqSize = pTxtBuff->u32TxtReqSize;
    }
    else if (u32FilePos < u32FileLength)
    {
        u32ReqSize = u32FileLength - u32FilePos;
    }
    else
    {
        TEXT_DEBUG(printf("Invalid length 0x%lx, Pos 0x%lx.", u32FileLength, u32FilePos));
        return FALSE;
    }
    TEXT_DEBUG(printf("u32ReqSize:%d\n",u32ReqSize));
    TEXT_DEBUG(printf("pTxtBuff->u32TxtReadSize:%d\n",pTxtBuff->u32TxtReadSize));
    TEXT_DEBUG(printf("pTxtBuff->u32TxtReqSize:%d\n",pTxtBuff->u32TxtReqSize));

    // Refresh the buffer if the target file data is not hit in the current buffer
    if((pTxtBuff->u32TxtReadSize == 0)
        || (u32TargetFilePos < pTxtBuff->u32TxtBuffFilePos)
        || ((pTxtBuff->u32TxtBuffFilePos + pTxtBuff->u32TxtBuffSize - u32ReqSize) < u32TargetFilePos))
    {
        if(pTxtBuff->u32TxtBuffSize > u32FileLength - u32Target4KPos)
        {
            u32TextReadSize = u32FileLength - u32Target4KPos;
        }
        else
        {
            u32TextReadSize = pTxtBuff->u32TxtBuffSize;
        }
        TEXT_DEBUG(printf("Reload, Seek to %d, Read to %d, Size: %d\n",u32Target4KPos,pTxtBuff->u32TxtBuffStart,u32TextReadSize));
        // clear the memory
        memset((void*)_PA2VA(TxtBuff.u32TxtBuffStart),0,TxtBuff.u32TxtBuffSize);
        // fill the data from the 4K alignment of file position
        msAPI_DataStreamIO_Seek((U32)u8FileHandle, u32Target4KPos, E_DATA_STREAM_SEEK_SET);
        msAPI_DataStreamIO_Read((U32)u8FileHandle, (void*)pTxtBuff->u32TxtBuffStart, u32TextReadSize);

        pTxtBuff->u32TxtBuffFilePos = u32Target4KPos;
    }

    //The request data start address in buffer
    pTxtBuff->u32TxtBuffPos = pTxtBuff->u32TxtBuffStart + (u32FilePos - pTxtBuff->u32TxtBuffFilePos);
    u32FilePos += u32ReqSize;
    pTxtBuff->u32TxtReadSize = u32ReqSize;

    TEXT_DEBUG(printf("     pTxtBuff->u32TxtBuffFilePos:%d\n",pTxtBuff->u32TxtBuffFilePos));
    TEXT_DEBUG(printf("     pTxtBuff->u32TxtBuffPos:%d\n",pTxtBuff->u32TxtBuffPos));
    TEXT_DEBUG(printf("     u32FilePos:%d\n",u32FilePos));
    TEXT_DEBUG(printf("     pTxtBuff->u32TxtReadSize:%d\n",pTxtBuff->u32TxtReadSize));

    return TRUE;
}
#else
BOOLEAN TEXT_FileRead(TEXT_TxtBuff* pTxtBuff)
{
    BOOLEAN bRet = FALSE;
    U32 u32Temp = 0;
    U32 u32RdSize = 0;
    U32 u32ReqSize = 0;

    if(u8FileHandle == FCTRL_INVALID_FILE_HANDLE)
    {
        return FALSE;
    }
    msAPI_FS_FileSeek(u8FileHandle, u32FilePos);
    TEXT_DEBUG(printf("current FilePos = %x\r\n", u32FilePos));
    if ((pTxtBuff->u32TxtReqSize > pTxtBuff->u32TxtBuffSize) ||
        (pTxtBuff->u32TxtReqSize == 0))
    {
        pTxtBuff->u32TxtReqSize = pTxtBuff->u32TxtBuffSize;
    }

    if ((u32FilePos + pTxtBuff->u32TxtReqSize) <= u32FileLength)
    {
        u32RdSize = pTxtBuff->u32TxtReqSize;
    }
    else if (u32FilePos < u32FileLength)
    {
        u32RdSize = u32FileLength - u32FilePos;
    }
    else
    {
        TEXT_DEBUG(printf("Invalid length 0x%lx, Pos 0x%lx.", u32FileLength, u32FilePos));
        return FALSE;
    }
    u32ReqSize = u32RdSize;

    TEXT_DEBUG(printf("TEXT_FileRead Rquest: 0x%lx, Read: 0x%lx.\n", u32ReqSize, u32RdSize));

    u32Temp = msAPI_FCtrl_FileRead(u8FileHandle, pTxtBuff->u32TxtBuffStart, u32ReqSize);
    pTxtBuff->u32TxtBuffPos = pTxtBuff->u32TxtBuffStart;
    if (u32Temp == 0)
    {
        u32FilePos += u32RdSize;
        pTxtBuff->u32TxtReadSize = u32RdSize;
        if (u32FilePos == u32FileLength)
        {
            bFileEnd = TRUE;
            //TEXT_DEBUG(printf("TEXT file end 1.\n"));
        }
        bRet = TRUE;
        //TEXT_DEBUG(printf("TEXT file read 0x%lx byte.\n", pTxtBuff->u32TxtReadSize));
    }
    else
    {
        if (u32Temp == (u32ReqSize - u32RdSize))
        {
            u32FilePos += u32RdSize;
            pTxtBuff->u32TxtReadSize = u32RdSize;
            if (u32FilePos == u32FileLength)
            {
                bFileEnd = TRUE;
                bRet = TRUE;
                //TEXT_DEBUG(printf("Text file end 2.\n"));
            }
            else
            {
                TEXT_DEBUG(printf("Read fail 0, pos 0x%lx, read size 0x%lx.\n", (u32FilePos - u32RdSize), u32RdSize));
            }
        }
        else
        {
            TEXT_DEBUG(printf("Read fail 1, pos 0x%lx, return 0x%lx.\n", u32FilePos, u32Temp));
        }
    }

    return bRet;
}
#endif
void SetTextPageOffset(U32 page, U32 ofs)
{
    U8 *pu8Temp=(U8 *)_PA2VA(TEXT_PAGE_INDEX_BUFF_ADDR);
    if(page <= TEXT_MAX_PAGE_NUM)
    {
        memcpy(pu8Temp + (page * TEXT_PAGE_OFFSET_SIZE),&ofs,TEXT_PAGE_OFFSET_SIZE);
    }
}

U32 GetTextPageOffset(U32 page)
{
    U32 offset = u32FileLength;
    U8 *pu8Temp=(U8 *)_PA2VA(TEXT_PAGE_INDEX_BUFF_ADDR);

    if(page <= TEXT_MAX_PAGE_NUM)
    {
        memcpy(&offset,pu8Temp + (page * TEXT_PAGE_OFFSET_SIZE),TEXT_PAGE_OFFSET_SIZE);
    }
    return offset;
}


inline BOOL IsNormalASCChar(char chWord)
{
    if(((chWord >= 'A') && (chWord <= 'Z')) ||
        ((chWord >= 'a') && (chWord <= 'z')) ||
        ((chWord >= '0') && (chWord <= '9')))
        return TRUE;

    return FALSE;
}

//Fix mips tool chain compile warning
// MIPS: Can't use inline
// ARM: Can't use "__attribute__((always_inline))"
/*__attribute__((always_inline))*/ U32 ASCWordWidth(U8 *bufData, U32 len)
{
    U32 u32DataLen = 0;
    U32 i=0;

    while((i < len) &&IsNormalASCChar(bufData[i]))
    {
        ++i;
        ++u32DataLen;
    }

    return u32DataLen;
}

inline BOOL IsNormalUniChar(U8* u8Char)
{
    if(u8Char[1] != 0)
        return FALSE;

    if(((u8Char[0] >= 'A') && (u8Char[0]  <= 'Z')) ||
        ((u8Char[0]  >= 'a') && (u8Char[0]  <= 'z')) ||
        ((u8Char[0]  >= '0') && (u8Char[0]  <= '9')))
        return TRUE;

    return FALSE;
}

inline U32 UniWordWidth(U8 *bufData, U32 len)
{
    U32 u32DataLen = 0;
    U32 i=0;

    while((i < len) &&IsNormalUniChar(&bufData[i]))
    {
        i+=2;
        ++u32DataLen;
    }

    return u32DataLen;
}


inline BOOL IsNormalUniBigChar(U8* u8Char)
{
    if(u8Char[0] != 0)
        return FALSE;

    if(((u8Char[1] >= 'A') && (u8Char[1]  <= 'Z')) ||
        ((u8Char[1]  >= 'a') && (u8Char[1]  <= 'z')) ||
        ((u8Char[1]  >= '0') && (u8Char[1]  <= '9')))
        return TRUE;

    return FALSE;
}

// unicode big edian
inline U32 UniBigWordBigWidth(U8 *bufData, U32 len)
{
    U32 u32DataLen = 0;
    U32 i=0;

    while((i < len) &&IsNormalUniBigChar(&bufData[i]))
    {
        i+=2;
        ++u32DataLen;
    }
    return u32DataLen;
}

//******************************************************************************
/// Get the UT8 word width
/// @param  bufData \b IN  Specify the data.
/// @return the UTF8 word width of current data
//******************************************************************************
inline U32 UTF8WordWidth(U8 *bufData)
{
    U32 u32DataLen = 0;

    if(bufData[0] < 0xC0)
    {
        u32DataLen = 1;
    }
    else if(bufData[0] < 0xE0)
    {
        u32DataLen = 2;
    }
    else if(bufData[0] < 0xF0)
    {
        u32DataLen = 3;
    }
    else if(bufData[0] < 0xF8)
    {
        u32DataLen = 4;
    }
    else if(bufData[0] < 0xFC)
    {
        u32DataLen = 5;
    }
    else
    {
        u32DataLen = 6;
    }

    return u32DataLen;
}

//******************************************************************************
/// Get the ANSI word width and the converted unicode word width
/// @param  bufData \b IN  Specify the data.
/// @param  u32UnicodeLenBytes \b IN  Specify the unicode word width.
/// @return the ANSI word width of current data
//******************************************************************************
inline U32 ANSI2UnicodeWordWidth(U8 *bufData, U32* u32UnicodeLenBytes)
{
    U32 u32DataLen = 0;
    *u32UnicodeLenBytes = 0;

    if (bufData[0] < 0x80)
    {
        if (bufData[0] == 0x0A)
        {
            u32DataLen = 1;
        }
        else if (bufData[0] == 0x09)
        {
            *u32UnicodeLenBytes = 8;
            u32DataLen = 1;
        }
        else
        {
            *u32UnicodeLenBytes = 2;
            u32DataLen = 1;
        }
    }
#if (ENABLE_ARABIC_OSD)
    //for Hebrew, convert according WINDOWS 1255
    else
    {
        *u32UnicodeLenBytes = 2;
        u32DataLen = 1;
    }
#else
    else
    {
        switch(m_enTextCharsetType)
        {
            case E_TEXT_CHARSET_CP874:                // Thai Windows Code Page 874
            case E_TEXT_CHARSET_CP1250:               // windows central european
            case E_TEXT_CHARSET_CP1251:               // Cyrillic Windows Code Page 1251
            case E_TEXT_CHARSET_CP1252:               // windows western european
            case E_TEXT_CHARSET_CP1253:               // Greek Windows Code Page 1253
            case E_TEXT_CHARSET_CP1254:               // windows turkey
            case E_TEXT_CHARSET_CP1255:               // Hebrew Windows Code Page 1255
            case E_TEXT_CHARSET_CP1256:               // Arabic Code Page 1256
            case E_TEXT_CHARSET_CP1257:               // Latin 4 Code Page 1257
            case E_TEXT_CHARSET_CP1258:               // Vietnamese  Code Page 1258
            case E_TEXT_CHARSET_ISO_8859_05:          //Cyrillic(ISO)
            case E_TEXT_CHARSET_ISO_8859_10:          //
            case E_TEXT_CHARSET_CROATIAN_MAC:         // croatian mac
            {
                *u32UnicodeLenBytes = 2;
                u32DataLen = 1;
            }
            break;
            case E_TEXT_CHARSET_KOREAN:
            {
        #if(CHAR_TABLE_SUPPORT_KOREAN_CODE)
                *u32UnicodeLenBytes = 2;
                u32DataLen = 2;
        #else
                //#error "32M unsupport Korean unicode"
                printf("\nError: 32M unsupport Korean unicode\n");
        #endif
            }
            break;
            case E_TEXT_CHARSET_GBK:
            case E_TEXT_CHARSET_DEFAULT:
            default:
            {
                // It is GB code.
                *u32UnicodeLenBytes = 2;
                u32DataLen = 2;
            }
            break;
        }
    }
#endif

    return u32DataLen;
}

#if TEXT_SHOW_BYLENGTH
    #define TEXT_PLAY_WINDOW_WIDTH  8000
    #define TEXT_PREVIEW_WINDOW_WIDTH 3500
    #define TEXT_DEFAULT_CHARWIDTH    89
    #if (ENABLE_ARABIC_OSD)
    #define HEBREW_CHARACTOR_WIDTH    TEXT_DEFAULT_CHARWIDTH  //temp set
    #endif
    #define SPECIAL_CHARACTOR_WIDTH    TEXT_DEFAULT_CHARWIDTH  //temp set
    #define GBK_CHARACTOR_WIDTH       200
    // NOTE: according to the implementation of TEXT_GetLine(), the real size of buf should be len+16 or
    // TEXT_GetLine() MAY access the memory not belong to buf and this criterion is NOTHING BUT A WORKAROUND
static code BYTE m_au8CharWidthTbl[]={
                           /*00*/      85,  85, 85,  85, 85,   85,  85,  85,  85,  85,  85, 85,  85,  85,  85,  85,
                           /*10*/      85,  85, 85,  85, 85,   85,  85,  85,  85,  85,  85, 85,  85,  85,  85,  85,
                           /*20*/      68,  34, 59,  129,94,  163, 136,34,  59,  59,  94, 120,42,  59,  34,  77,
                           /*30*/      110,110,110,110,110,110, 110,110,110, 110,34, 42,  120,120,120, 77,
                           /*40*/      163,134,103,114,120,94,   83,  130,110, 35,  60, 120,93, 127,110,  127,
                           /*50*/      93,  130,113,106,120,114, 136,180,133, 127,114,52,  77, 52,  52,   52,
                           /*60*/      52,  96,  106,50,  102,102, 77,  102,93,  34,  51,  102,34, 154,94,   102,
                           /*70*/      102,102, 68, 83,  74,  92,   114,152,114, 113,92,  85, 34,  85, 120,  85,
                                           };


static BOOL TEXT_GetData(U8 *buf, U8 *pu8bufData, U32 len, BOOLEAN Preview)
{
        U32 count = 0;
        U32 num = 0; // buf used number
        U16 tmp;
        U8 *bufData=(U8 *)_PA2VA((U32)pu8bufData);
        U32 width;
        U32 u32CharSumInOneLine=0;
        U32 u32CharSumInOneWord = 0;
        U32 u32Index;

        if(Preview)
            width=TEXT_PREVIEW_WINDOW_WIDTH;
        else
            width=TEXT_PLAY_WINDOW_WIDTH;

        //Memo: when 'len' is larger than a certain number(ex. TEXT_CHAR_NUM_PER_LINE*2), memset() will cause 'len = 0'.
        //      So, comment out below line to avoid problem.
        //for most case TxtBuff.u32TxtReadSize = 1328
        memset(buf, 0, len + 2);
        if (u8FileType == EN_TEXT_UNIB)
        {
            U32 u32NextWordLen = 0;
            while((u32MemPos < TxtBuff.u32TxtReadSize) && (bufData[u32MemPos] == 0) &&(bufData[u32MemPos+1] == ' '))
            {
                //printf("encounter blanck space in first place, skip it\n");
                u32MemPos+=2;
            }
            while ((num < len) && (u32MemPos < TxtBuff.u32TxtReadSize))
            {
                if((count+1) > len)//buf array overflow
                {
                    buf[count] = 0x00;
                    buf[count+1] = 0x00;
                    return true;
                }
                if (u32MemPos < TxtBuff.u32TxtReadSize)
                {
                    U32 u32MemPosOld = u32MemPos;
                    u32CharSumInOneWord = 0;
                    u32NextWordLen = UniBigWordBigWidth(&bufData[u32MemPos], TxtBuff.u32TxtReadSize - u32MemPos);
                    u32NextWordLen *=2;// cause 16 bits per char
                    if(u32NextWordLen > len)
                    {
                        //printf("1 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                    }
                    else if((u32NextWordLen + count) >  len)
                    {
                        //printf("find xcross word, put to next line\n");
                        //printf("2 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        buf[count]=0;
                        buf[count+1]=0;
                        return true;
                    }
                    else
                    {
                        //printf("3 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        // if 0, we can do the parse once
                    }
                    TEXT_DEBUG(printf("u32MemPos=%x bufData[u32MemPos]=%02x u32NextWordLen=%d\n",u32MemPos,bufData[u32MemPos+1],u32NextWordLen));

                    // If increased current word char length is large than line width, current word should be in next line
                    if(u32NextWordLen == 0)
                    {
                        if((bufData[u32MemPos] == 0x00)&&(bufData[u32MemPos+1]>=0x20&&bufData[u32MemPos+1]<=0x7E))
                        {
                            u32CharSumInOneWord = m_au8CharWidthTbl[bufData[u32MemPos+1]];
                            //printf("\r\n Charwidth=%bu",m_au8CharWidthTbl[buf[count]]);
                            //printf("\r\n u32CharSumInOneLine=%u",u32CharSumInOneLine);
                        }
                        else if((bufData[u32MemPos] == 0x00)&&(bufData[u32MemPos+1] == 0x0D))
                        {
                            u32CharSumInOneWord = 0;
                        }
                        else
                        {
                            u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                        }
                    }
                    else
                    {
                        for(u32Index = 0; u32Index < u32NextWordLen; u32Index+=2)
                        {
                            u32CharSumInOneWord += m_au8CharWidthTbl[bufData[u32MemPos+u32Index+1]];
                        }
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneWord+u32CharSumInOneLine));
                    if((u32CharSumInOneLine !=0) && (u32CharSumInOneWord + u32CharSumInOneLine > width))
                    {
                        buf[count] = 0x00;
                        buf[count+1] = 0x00;
                        return true;
                    }

                    do
                    {
                        //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                        buf[count]=bufData[u32MemPos+1];
                        buf[count+1]=bufData[u32MemPos];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!
                        if (buf[count+1] == 0x00)
                        {
                            if (buf[count] == 0x0D)
                            {
                                buf[count] = 0x00;
                                count += 2;
                                u32MemPos += 2;
                                //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                                buf[count]=bufData[u32MemPos+1];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!
                                buf[count+1]=bufData[u32MemPos];

                                if (buf[count+1] == 0x00 && buf[count] == 0x0A)
                                {
                                    u32MemPos += 2;
                                }
                                return true;
                            }
                        }
                       if((buf[count+1] == 0x00)&&(buf[count]>=0x20&&buf[count]<=0x7E))
                       {
                           u32CharSumInOneLine= m_au8CharWidthTbl[buf[count]]+u32CharSumInOneLine;
                           //printf("\r\n Charwidth=%bu",m_au8CharWidthTbl[buf[count]]);
                           //printf("\r\n u32CharSumInOneLine=%u",u32CharSumInOneLine);
                       }
                       else
                        {
                            u32CharSumInOneLine+= TEXT_DEFAULT_CHARWIDTH;
                        }
                        num += 2;
                        if (u32MemPos >= TxtBuff.u32TxtReadSize || num >= len || u32CharSumInOneLine>width)//couldn't cause buf array overflow
                        {
                            buf[count+2] = 0x00;
                            buf[count+3] = 0x00;
                            u32MemPos += 2;
                            return true;
                        }
                        count += 2;
                        u32MemPos += 2;
                    }while((u32MemPos - u32MemPosOld) < u32NextWordLen);
                }
            };
        }
        else if (u8FileType == EN_TEXT_UNIS)
        {
            U32 u32NextWordLen = 0;
            while((u32MemPos < TxtBuff.u32TxtReadSize) && (bufData[u32MemPos] == ' ') &&(bufData[u32MemPos+1] == 0))
            {
                //printf("encounter blanck space in first place, skip it\n");
                u32MemPos+=2;
            }
            while ((num < len) && (u32MemPos < TxtBuff.u32TxtReadSize))
            {
                if((count+1) > len)//buf array overflow
                {
                    buf[count] = 0x00;
                    buf[count+1] = 0x00;
                    return true;
                }
                if (u32MemPos < TxtBuff.u32TxtReadSize)
                {
                    U32 u32MemPosOld = u32MemPos;
                    u32CharSumInOneWord = 0;
                    u32NextWordLen = UniWordWidth(&bufData[u32MemPos], TxtBuff.u32TxtReadSize - u32MemPos);
                    u32NextWordLen *=2;// cause 16 bits per char
                    if(u32NextWordLen > len)
                    {
                        //printf("1 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                    }
                    else if((u32NextWordLen + count) >  len)
                    {
                    //    printf("find xcross word, put to next line\n");
                    //    printf("2 len=0x%lx, u32NextWordLen = 0x%lx, count = 0x%lx , u32MemPos = 0x%lx\n", len,u32NextWordLen, count,u32MemPos);
                        buf[count]=0;
                        buf[count+1]=0;
                        return true;
                    }
                    else
                    {
                        //printf("3 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        // if 0, we can do the parse once
                    }
                    TEXT_DEBUG(printf("u32MemPos=%x bufData[u32MemPos]=%02x u32NextWordLen=%d\n",u32MemPos,bufData[u32MemPos],u32NextWordLen));

                    // If increased current word char length is large than line width, current word should be in next line
                    if(u32NextWordLen == 0)
                    {
                        if((bufData[u32MemPos+1] == 0x00)&&(bufData[u32MemPos]>=0x20&&bufData[u32MemPos]<=0x7E))
                        {
                            u32CharSumInOneWord = m_au8CharWidthTbl[bufData[u32MemPos]];
                            //printf("\r\n Charwidth=%bu",m_au8CharWidthTbl[buf[count]]);
                            //printf("\r\n u32CharSumInOneLine=%u",u32CharSumInOneLine);
                        }
                        else if((bufData[u32MemPos+1] == 0x00)&&(bufData[u32MemPos] == 0x0D))
                        {
                            u32CharSumInOneWord = 0;
                        }
                        else
                        {
                            u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                        }
                    }
                    else
                    {
                        for(u32Index = 0; u32Index < u32NextWordLen; u32Index+=2)
                        {
                            u32CharSumInOneWord += m_au8CharWidthTbl[bufData[u32MemPos+u32Index]];
                        }
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneWord+u32CharSumInOneLine));
                    if((u32CharSumInOneLine !=0) && (u32CharSumInOneWord + u32CharSumInOneLine > width))
                    {
                        buf[count] = 0x00;
                        buf[count+1] = 0x00;
                        return true;
                    }

                    do
                    {
                        //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                        buf[count]=bufData[u32MemPos];
                        buf[count+1]=bufData[u32MemPos+1];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!

                        if (buf[count+1] == 0x00)
                        {
                            if (buf[count] == 0x0D)
                            {
                                buf[count] = 0x00;
                                count += 2;
                                u32MemPos += 2;
                                //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                                buf[count]=bufData[u32MemPos];
                                buf[count+1]=bufData[u32MemPos+1];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!

                                if (buf[count+1] == 0x00 && buf[count] == 0x0A)
                                {
                                    u32MemPos += 2;
                                }
                                return true;
                            }
                        }
                        if((buf[count+1] == 0x00)&&(buf[count]>=0x20&&buf[count]<=0x7E))
                        {
                            u32CharSumInOneLine= m_au8CharWidthTbl[buf[count]]+u32CharSumInOneLine;
                       //    printf("\r\n Charwidth=%bu",m_au8CharWidthTbl[buf[count]]);
                      //     printf("\r\n u32CharSumInOneLine=%u , num : %d ",u32CharSumInOneLine,num);
                        }
                       else
                        {
                            u32CharSumInOneLine+= TEXT_DEFAULT_CHARWIDTH;
                        }
                        num += 2;
                        if (u32MemPos >= TxtBuff.u32TxtReadSize || num >= len||u32CharSumInOneLine>width)//couldn't cause buf array overflow
                        {
                       //     printf("u32MemPos = 0x%lx, TxtBuff.u32TxtReadSize = 0x%lx\n", u32MemPos, TxtBuff.u32TxtReadSize);
                            buf[count+2] = 0x00;
                            buf[count+3] = 0x00;
                            u32MemPos += 2;
                            return true;
                        }
                        count += 2;
                        u32MemPos += 2;
                    }while((u32MemPos - u32MemPosOld) < u32NextWordLen);
                }
            };
        }
        else if (u8FileType == EN_TEXT_ANSI)
        {
            U32 u32NextWordLen;
            //printf("u32MemPos = 0x%lx, TxtBuff.u32TxtReadSize = 0x%lx\n", u32MemPos, TxtBuff.u32TxtReadSize);
            // if line head is blanck space, skip this
            while((u32MemPos < TxtBuff.u32TxtReadSize) && (bufData[u32MemPos] == ' '))
            {
                //printf("encounter blanck space in first place, skip it\n");
                u32MemPos++;
            }

            while ((num < len) && (u32MemPos < TxtBuff.u32TxtReadSize))
            {
                if((count+1) > len)//buf array overflow
                {
                    buf[count] = 0x00;
                    buf[count+1] = 0x00;
                    return true;
                }
                if (u32MemPos < TxtBuff.u32TxtReadSize)
                {
                    U32 u32MemPosOld = u32MemPos;
                    u32CharSumInOneWord = 0;
                    u32NextWordLen = ASCWordWidth(&bufData[u32MemPos], TxtBuff.u32TxtReadSize - u32MemPos);
                    if(2*u32NextWordLen > len)
                    {
                        //printf("1 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                    }
                    else if((2*u32NextWordLen + count) >  len)
                    {
                        //printf("find xcross word, put to next line\n");
                        //printf("2 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        buf[count]=0;
                        buf[count+1]=0;
                        return true;
                    }
                    else
                    {
                        //printf("3 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        // if 0, we can do the parse once
                    }
                    TEXT_DEBUG(printf("u32MemPos=%x bufData[u32MemPos]=%02x u32NextWordLen=%d\n",u32MemPos,bufData[u32MemPos],u32NextWordLen));

                    // If increased current word char length is large than line width, current word should be in next line
                    if(u32NextWordLen == 0)
                    {
                        if(bufData[u32MemPos] < 0x80)
                        {
                            if(bufData[u32MemPos] == 0x0A || bufData[u32MemPos] == 0x09)
                            {
                                u32CharSumInOneWord = 0;
                            }
                            else if(bufData[u32MemPos]>=0x20&&bufData[u32MemPos]<=0x7E)
                            {
                                u32CharSumInOneWord = m_au8CharWidthTbl[bufData[u32MemPos]];
                            }
                            else
                            {
                                u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                            }
                        }
                        else
                        {
#if (ENABLE_ARABIC_OSD)
                            if((bufData[u32MemPos] >= 0xE0) && (bufData[u32MemPos] <= 0xFA))
                            {
                                u32CharSumInOneWord = HEBREW_CHARACTOR_WIDTH;
                            }
                            else
                            {
                                u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                            }
#else
                            switch(m_enTextCharsetType)
                            {
                                case E_TEXT_CHARSET_CP1250:
                                case E_TEXT_CHARSET_CP1251:
                                case E_TEXT_CHARSET_CP1252:
                                case E_TEXT_CHARSET_CP1254:
                                case E_TEXT_CHARSET_CP1255:
                                case E_TEXT_CHARSET_CP1256:
                                case E_TEXT_CHARSET_CROATIAN_MAC:
                                {
                                    if((bufData[u32MemPos] >= 0xE0) && (bufData[u32MemPos] <= 0xFA))
                                    {
                                        u32CharSumInOneWord =  SPECIAL_CHARACTOR_WIDTH;
                                    }
                                    else
                                    {
                                        u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                                    }
                                }
                                break;

                                case E_TEXT_CHARSET_GBK:
                                case E_TEXT_CHARSET_DEFAULT:
                                default:
                                {
                                    // It is GB code.
                                    u32CharSumInOneWord = GBK_CHARACTOR_WIDTH;
                                }
                                break;
                            }
#endif
                        }
                    }
                    else
                    {
                        for(u32Index = 0; u32Index < u32NextWordLen; u32Index+=1)
                        {
                            u32CharSumInOneWord += m_au8CharWidthTbl[bufData[u32MemPos+u32Index]];
                        }
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneWord=%d u32CharSumInOneLine=%d\n",u32CharSumInOneWord,u32CharSumInOneLine));
                    if((u32CharSumInOneLine !=0) && (u32CharSumInOneWord + u32CharSumInOneLine > width))
                    {
                        buf[count] = 0x00;
                        buf[count+1] = 0x00;
                        return true;
                    }

                    do
                    {
                        if((count+1) > len)//buf array overflow
                        {
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            return true;
                        }
                        //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                        buf[count]=bufData[u32MemPos];
                        buf[count+1]=bufData[u32MemPos+1];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!
                        //printf("buf[%d] = %c bufData[0x%lx] = %c \r\n", (U8)count, (U8)buf[count],u32MemPos,(U8)bufData[u32MemPos]);
                        //printf("buf[%d] = %x\r\n", (U8)(count+1), (U8)buf[count+1]);
                        if (buf[count] == '\r')
                        {
                            //printf("enter r\n");
                            if(buf[count+1] == '\n' || buf[count+1] == '\r')
                            {
                                u32MemPos += 2;
                            }
                            else
                            {
                                u32MemPos += 1;
                            }
                            //buf[count] = 0x8A;
                            //buf[count+1] = 0xE0;    //0xE08A : \n
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            count += 2;
                            num += 2;
                            //printf("exit r\n");
                            return true;
                        }
                        else if (buf[count] == '\n') //DOS format
                        {
                            u32MemPos += 1;
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            return true;
                        }
                        else if (buf[count] < 0x80)
                        {
                            if (buf[count] == 0x0A)
                            {
                                u32MemPos += 1;
                            }
                            else if (buf[count] == 0x09)
                            {
                                buf[count] = 0x00;
                                buf[count+1] = 0x20;
                                buf[count+2] = 0x00;
                                buf[count+3] = 0x20;
                                buf[count+4] = 0x00;
                                buf[count+5] = 0x20;
                                buf[count+6] = 0x00;
                                buf[count+7] = 0x20;
                                count += 8;
                                num += 4;
                                u32MemPos += 1;
                            }
                            else
                            {
                                if(buf[count]>=0x20&&buf[count]<=0x7E)
                                {
                                    u32CharSumInOneLine= m_au8CharWidthTbl[buf[count]]+u32CharSumInOneLine;
                                    //printf("\r\n Charwidth=%bu",m_au8CharWidthTbl[buf[count]]);
                                    //printf("\r\n u32CharSumInOneLine=%u",u32CharSumInOneLine);
                                }
                                else
                                {
                                    u32CharSumInOneLine+= TEXT_DEFAULT_CHARWIDTH;
                                }

                                buf[count + 1] = 0x00;

                                count += 2;
                                num += 2;// 1   //modified from public version(20481)
                                u32MemPos += 1;
                            }
                        }
#if (ENABLE_ARABIC_OSD)
                        //for Hebrew, convert according WINDOWS 1255
                        else
                        {
                            if(buf[count]>=0xE0&&buf[count]<=0xFA)
                            {
                                u32CharSumInOneLine= HEBREW_CHARACTOR_WIDTH+u32CharSumInOneLine;
                                //printf("\r\n hebrew charactor, u32CharSumInOneLine=%u",u32CharSumInOneLine);
                            }
                            else
                            {
                                u32CharSumInOneLine+= TEXT_DEFAULT_CHARWIDTH;
                            }
                            tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1255, buf[count]);
                            //printf("%02x->%x\n",buf[count] ,tmp);
                            buf[count+1] = tmp >> 8;
                            buf[count] = tmp & 0xFF;
                            count += 2;
                            num += 2;
                            u32MemPos += 1;
                        }
#else
                        else
                        {
                            switch(m_enTextCharsetType)
                            {
                                case E_TEXT_CHARSET_CP1250:
								case E_TEXT_CHARSET_CP1251:
                                case E_TEXT_CHARSET_CP1252:
								case E_TEXT_CHARSET_CP1254:
                                case E_TEXT_CHARSET_CP1255:
								case E_TEXT_CHARSET_CP1256:
                                case E_TEXT_CHARSET_CROATIAN_MAC:
                                {
                                    EN_CHARACTER_CODE_TABLE enCharCodeTable = WINDOWS_CP1250;

                                    if(buf[count]>=0xE0&&buf[count]<=0xFA)
                                    {
                                        u32CharSumInOneLine= SPECIAL_CHARACTOR_WIDTH+u32CharSumInOneLine;
                                        //printf("\r\n special charactor, u32CharSumInOneLine=%u",u32CharSumInOneLine);
                                    }
                                    else
                                    {
                                        u32CharSumInOneLine+= TEXT_DEFAULT_CHARWIDTH;
                                    }

                                    if(m_enTextCharsetType == E_TEXT_CHARSET_CP1250)
                                    {
                                        enCharCodeTable = WINDOWS_CP1250;
                                    }
									else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1251)
									{
										enCharCodeTable = WINDOWS_CP1251;
									}
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1252)
                                    {
                                        enCharCodeTable = WINDOWS_CP1252;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1254)
                                    {
                                        enCharCodeTable = WINDOWS_CP1254;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1255)
                                    {
                                        enCharCodeTable = WINDOWS_CP1255;
                                    }
									else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1256)
									{
                                        enCharCodeTable = WINDOWS_CP1256;
									}
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CROATIAN_MAC)
                                    {
                                        enCharCodeTable = WINDOWS_CROATIAN_MAC;
                                    }

                                    tmp = MApp_CharTable_MappingCharToUCS2(enCharCodeTable, buf[count]);
                                    //printf("%02x->%x\n",buf[count] ,tmp);
                                    buf[count+1] = tmp >> 8;
                                    buf[count] = tmp & 0xFF;
                                    count += 2;
                                    num += 2;
                                    u32MemPos += 1;
                                }
                                break;

                                case E_TEXT_CHARSET_GBK:
                                case E_TEXT_CHARSET_DEFAULT:
                                default:
                                {
                                    // It is GB code.
                                    tmp = MApp_Transfer2Unicode(((U16)buf[count] << 8) + buf[count+1]);
                                    u32CharSumInOneLine+=GBK_CHARACTOR_WIDTH;
                                    buf[count+1] = tmp >> 8;
                                    buf[count] = tmp & 0xFF;
                                    num += 2;
                                    count += 2;
                                    u32MemPos += 2;
                                }
                                break;
                            }
                        }
#endif
                        if (u32MemPos >= TxtBuff.u32TxtReadSize)
                        {
                            //printf("exit TxtBuff.u32TxtReadSize = 0x%lx\n", TxtBuff.u32TxtReadSize);
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            return true;
                        }
                        TEXT_DEBUG(printf("######## u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                        if (u32CharSumInOneLine>width)
                        {

                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            return true;
                        }
                    }while((u32MemPos - u32MemPosOld) < u32NextWordLen);
                }
            };
            if(count)
                return true;
        }
        else if  (u8FileType == EN_TEXT_UTF8)
        {
            U32 u32NextWordLen = 0;

            //printf("u32MemPos = 0x%lx, TxtBuff.u32TxtReadSize = 0x%lx\n", u32MemPos, TxtBuff.u32TxtReadSize);

            // if line head is blanck space, skip this
            while((u32MemPos < TxtBuff.u32TxtReadSize) && (bufData[u32MemPos] == ' '))
            {
                //printf("encounter blanck space in first place, skip it\n");
                u32MemPos++;
            }

            while ((num < len) && (u32MemPos < TxtBuff.u32TxtReadSize))
            {
                if((count+1) > len)//buf array overflow
                {
                    buf[count] = 0x00;
                    buf[count+1] = 0x00;
                    return true;
                }
                if (u32MemPos < TxtBuff.u32TxtReadSize)
                {
                    U32 u32MemPosOld = u32MemPos;
                    u32CharSumInOneWord = 0;
                    u32NextWordLen = ASCWordWidth(&bufData[u32MemPos], TxtBuff.u32TxtReadSize - u32MemPos);

                     if(2*u32NextWordLen > len)
                    {
                        //printf("1 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                    }
                    else if((2*u32NextWordLen + count) >  len)
                    {
                        //printf("find xcross word, put to next line\n");
                        //printf("2 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        buf[count]=0;
                        buf[count+1]=0;
                        return true;
                    }
                    else
                    {
                        //printf("3 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        // if 0, we can do the parse once
                    }
                    TEXT_DEBUG(printf("u32MemPos=%x bufData[u32MemPos]=%02x u32NextWordLen=%d\n",u32MemPos,bufData[u32MemPos],u32NextWordLen));

                    // If increased current word char length is large than line width, current word should be in next line
                    if(u32NextWordLen == 0)
                    {
                        if(bufData[u32MemPos] == 0x0D && bufData[u32MemPos+1] == 0x0A)
                        {
                            u32CharSumInOneWord = 0;
                        }
                        else if(bufData[u32MemPos]>=0x20&&bufData[u32MemPos]<=0x7E)
                        {
                            u32CharSumInOneWord = m_au8CharWidthTbl[bufData[u32MemPos]];
                        }
                        else
                        {
                            u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                        }
                    }
                    else
                    {
                        for(u32Index = 0; u32Index < u32NextWordLen; u32Index+=1)
                        {
                            u32CharSumInOneWord += m_au8CharWidthTbl[bufData[u32MemPos+u32Index]];
                        }
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneWord=%d u32CharSumInOneLine=%d\n",u32CharSumInOneWord,u32CharSumInOneLine));
                    if((u32CharSumInOneLine !=0) && (u32CharSumInOneWord + u32CharSumInOneLine > width))
                    {
                        buf[count] = 0x00;
                        buf[count+1] = 0x00;
                        return true;
                    }

                    do
                    {
                        buf[count]=bufData[u32MemPos];
                        buf[count+1]=bufData[u32MemPos+1];
                        buf[count+2]=bufData[u32MemPos+2];
                        if ((buf[count] == 0xd) && (buf[count+1] == 0xa))
                        {
                            buf[count]=0;
                            buf[count+1]=0;
                            buf[count+2]=0;
                            u32MemPos += 2;

                            //printf("find feed back\n");
                            return true;
                        }
                        else if (buf[count] < 0x80)
                        {
                            buf[count + 1] = 0x00;
                            if((buf[count+1] == 0x00)&&(buf[count]>=0x20&&buf[count]<=0x7E))
                            {
                                u32CharSumInOneLine= m_au8CharWidthTbl[buf[count]]+u32CharSumInOneLine;
                                //printf("\r\n Charwidth=%bu",m_au8CharWidthTbl[buf[count]]);
                                //printf("\r\n u32CharSumInOneLine=%u",u32CharSumInOneLine);
                            }
                           else
                            {
                                u32CharSumInOneLine+= TEXT_DEFAULT_CHARWIDTH;
                            }
                            count += 2;
                            num += 2;
                            u32MemPos += 1;
                        }
                        else if ((buf[count] >=0xe0) && (buf[count+1] >=0x80) && (buf[count+2] >=0x80))
                        {
                            //UTF8 to UNICODE
                            buf[count]=(bufData[u32MemPos+2]&0x3f) + ((bufData[u32MemPos+1]&3)<<6);
                            buf[count+1]=((bufData[u32MemPos+1]&0x3c)>>2) + ((bufData[u32MemPos]&0xf)<<4);
                            //printf(" [%x] [%x] [%x]",bufData[u32MemPos],bufData[u32MemPos+1], bufData[u32MemPos+2]);
                            //printf("==> [%x],  [%x]",buf[count],buf[count+1]);
                            if((buf[count+1] == 0x00)&&(buf[count]>=0x20&&buf[count]<=0x7E))
                            {
                                u32CharSumInOneLine= m_au8CharWidthTbl[buf[count]]+u32CharSumInOneLine;
                                //printf("\r\n Charwidth=%bu",m_au8CharWidthTbl[buf[count]]);
                                //printf("\r\n u32CharSumInOneLine=%u",u32CharSumInOneLine);
                            }
                           else
                            {
                                u32CharSumInOneLine+= TEXT_DEFAULT_CHARWIDTH;
                            }
                            num += 2;
                            count += 2;
                            u32MemPos += 3;
                        }
                        else if (((buf[count] >=0xc0) && (buf[count] <0xe0)) && (buf[count+1] >=0x80))
                        {
                            //UTF8 to UNICODE
                            buf[count]=(bufData[u32MemPos+1]&0x3f)+((bufData[u32MemPos]&0x3)<<6);
                            buf[count+1]=(bufData[u32MemPos]&0x1f)>>2;
                            if((buf[count+1] == 0x00)&&(buf[count]>=0x20&&buf[count]<=0x7E))
                            {
                                u32CharSumInOneLine= m_au8CharWidthTbl[buf[count]]+u32CharSumInOneLine;
                                //printf("\r\n Charwidth=%bu",m_au8CharWidthTbl[buf[count]]);
                                //printf("\r\n u32CharSumInOneLine=%u",u32CharSumInOneLine);
                            }
                           else
                            {
                                u32CharSumInOneLine+= TEXT_DEFAULT_CHARWIDTH;
                            }
                            num += 2;
                            count += 2;
                            u32MemPos += 2;
                        }
                        else
                        {
                            //printf("1=%x,2=%x,3=%x\n", buf[count] , buf[count+1], buf[count+2]);
                            __ASSERT(0);
                            u32MemPos+=1;
                        }
                        if (u32MemPos >= TxtBuff.u32TxtReadSize || num >= len||u32CharSumInOneLine>width)//couldn't cause buf array overflow
                        {
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            //u32MemPos += 2;
                            return true;
                        }
                    }while((u32MemPos - u32MemPosOld) < u32NextWordLen);
                }
            };
            return true;
        }

        return false;
}
#if TEXT_FAST_LOAD_FILE
    //******************************************************************************
    /// Parse the word to count bytes for one line.
    /// @param  pu8bufData \b IN  Specify the data.
    /// @param  u32TargetBytes \b IN  Specify the targert bytes of one line.
    /// @return TRUE or FALSE
    //******************************************************************************
BOOL TEXT_ParseData(U8 *pu8bufData, U32 u32TargetBytes)
{
        U8 *bufData;
        U32 u32ParsedBytes = 0;
        U32 u32MemPosInBuff = u32MemPos;
        U32 u32CurBuffLen = TxtBuff.u32TxtReadSize;
        U32 u32Index;
        U32 u32CharSumInOneLine = 0;
        U32 u32NextWordLen = 0;

        //Use cache address
        bufData =(U8 *)MsOS_PA2KSEG0((U32)pu8bufData);

        if (u8FileType == EN_TEXT_UNIB)
        {
            while(u32MemPosInBuff < u32CurBuffLen)
            {
                //encounter blank space in first place, skip it
                if((u32ParsedBytes == 0) && (bufData[u32MemPosInBuff] == 0x00) && (bufData[u32MemPosInBuff+1] == ' '))
                {
                    u32MemPosInBuff+=2;
                    continue;
                }

                //new line
                if((bufData[u32MemPosInBuff] == 0x00) &&(bufData[u32MemPosInBuff+1] == 0x0D))
                {
                    if(u32ParsedBytes == u32TargetBytes)
                    {

                    }
                    else
                    {
                        u32MemPosInBuff += 2;
                        if((bufData[u32MemPosInBuff] == 0x00) && (bufData[u32MemPosInBuff+1] == 0x0A))
                        {
                            u32MemPosInBuff += 2;
                        }
                    }
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }
                //Get the word length
                u32NextWordLen = UniBigWordBigWidth(&bufData[u32MemPosInBuff], u32CurBuffLen - u32MemPosInBuff);
                u32NextWordLen *=2;// cause 16 bits per char
                if((u32NextWordLen + u32ParsedBytes) >  u32TargetBytes)
                {
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                TEXT_DEBUG(printf("u32MemPos=%x bufData[u32MemPos]=%02x u32NextWordLen=%d\n",u32MemPosInBuff,bufData[u32MemPosInBuff+1],u32NextWordLen));

                if(u32NextWordLen == 0)
                {
                    if((bufData[u32MemPosInBuff] == 0x00)&&(bufData[u32MemPosInBuff+1]>=0x20&&bufData[u32MemPosInBuff+1]<=0x7E))
                    {
                        u32CharSumInOneLine += m_au8CharWidthTbl[bufData[u32MemPosInBuff+1]];
                    }
                    else if((bufData[u32MemPosInBuff] == 0x00)&&(bufData[u32MemPosInBuff+1] == 0x0D))
                    {

                    }
                    else
                    {
                        u32CharSumInOneLine += TEXT_DEFAULT_CHARWIDTH;
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                    if (u32CharSumInOneLine > TEXT_PLAY_WINDOW_WIDTH)
                    {
                        u32MemPos = u32MemPosInBuff;
                        return true;
                    }
                    u32NextWordLen = 2;
                }
                else
                {
                    for(u32Index = 0; u32Index < u32NextWordLen; u32Index+=2)
                    {
                        u32CharSumInOneLine += m_au8CharWidthTbl[bufData[u32MemPosInBuff+u32Index+1]];

                        if(u32CharSumInOneLine > TEXT_PLAY_WINDOW_WIDTH)//couldn't cause buf array overflow
                        {
                            TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                            if(u32ParsedBytes !=0)
                            {
                                u32MemPos = u32MemPosInBuff;
                            }
                            else
                            {
                                u32MemPos = u32MemPosInBuff + u32Index + 2;
                            }
                            return true;
                        }
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                }
                u32MemPosInBuff += u32NextWordLen;
                u32ParsedBytes += u32NextWordLen;
            }
        }
        else if (u8FileType == EN_TEXT_UNIS)
        {
            while(u32MemPosInBuff < u32CurBuffLen)
            {
                //encounter blank space in first place, skip it
                if((u32ParsedBytes == 0) && (bufData[u32MemPosInBuff] == ' ') && (bufData[u32MemPosInBuff+1] == 0x00))
                {
                    u32MemPosInBuff+=2;
                    continue;
                }

                //new line
                if((bufData[u32MemPosInBuff] == 0x0D) &&(bufData[u32MemPosInBuff+1] == 0x00))
                {
                    if(u32ParsedBytes == u32TargetBytes)
                    {

                    }
                    else
                    {
                        u32MemPosInBuff += 2;
                        if((bufData[u32MemPosInBuff] == 0x0A) && (bufData[u32MemPosInBuff+1] == 0x00))
                        {
                            u32MemPosInBuff += 2;
                        }
                    }
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                //Get the word length
                u32NextWordLen = UniWordWidth(&bufData[u32MemPosInBuff], u32CurBuffLen - u32MemPosInBuff);
                u32NextWordLen *=2;// cause 16 bits per char
                if((u32NextWordLen + u32ParsedBytes) >  u32TargetBytes)
                {
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                TEXT_DEBUG(printf("u32MemPos=%x bufData[u32MemPos]=%02x u32NextWordLen=%d\n",u32MemPosInBuff,bufData[u32MemPosInBuff],u32NextWordLen));

                if(u32NextWordLen == 0)
                {
                    if((bufData[u32MemPosInBuff+1] == 0x00)&&(bufData[u32MemPosInBuff]>=0x20&&bufData[u32MemPosInBuff]<=0x7E))
                    {
                        u32CharSumInOneLine += m_au8CharWidthTbl[bufData[u32MemPosInBuff]];

                    }
                    else if((bufData[u32MemPosInBuff+1] == 0x00)&&(bufData[u32MemPosInBuff] == 0x0D))
                    {

                    }
                    else
                    {
                        u32CharSumInOneLine += TEXT_DEFAULT_CHARWIDTH;
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                    if (u32CharSumInOneLine > TEXT_PLAY_WINDOW_WIDTH)
                    {
                        u32MemPos = u32MemPosInBuff;
                        return true;
                    }
                    u32NextWordLen = 2;
                }
                else
                {
                    //u32CharSumInOneWord = 0;
                    for(u32Index = 0; u32Index < u32NextWordLen; u32Index+=2)
                    {
                        u32CharSumInOneLine += m_au8CharWidthTbl[bufData[u32MemPosInBuff+u32Index]];

                        if(u32CharSumInOneLine > TEXT_PLAY_WINDOW_WIDTH)//couldn't cause buf array overflow
                        {
                            TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                            if(u32ParsedBytes !=0)
                            {
                                u32MemPos = u32MemPosInBuff;
                            }
                            else
                            {
                                u32MemPos = u32MemPosInBuff + u32Index + 2;
                            }
                            return true;
                        }
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                }
                u32MemPosInBuff += u32NextWordLen;
                u32ParsedBytes += u32NextWordLen;
            }
        }
        else if (u8FileType == EN_TEXT_ANSI)
        {
            U32 u32CharSumInOneWord;
            U8 u32ANSILen = 0;
            while(u32MemPosInBuff < u32CurBuffLen)
            {
                //encounter blank space in first place, skip it
                if((u32ParsedBytes == 0) && (bufData[u32MemPosInBuff] == ' '))
                {
                    u32MemPosInBuff+=1;
                    continue;
                }

                //new line
                if(bufData[u32MemPosInBuff] == 0x0D)
                {
                    if(u32ParsedBytes == u32TargetBytes) // buffer already full
                    {

                    }
                    else
                    {
                        u32MemPosInBuff += 1;
                        if(bufData[u32MemPosInBuff] == 0x0A)
                        {
                            u32MemPosInBuff += 1;
                        }
                    }
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                //Get the word length
                u32NextWordLen = ASCWordWidth(&bufData[u32MemPosInBuff], u32CurBuffLen - u32MemPosInBuff);
                if((u32NextWordLen + u32ParsedBytes) >  u32TargetBytes)
                {
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }
                TEXT_DEBUG(printf("u32MemPos=%x bufData[u32MemPos]=%02x u32NextWordLen=%d\n",u32MemPosInBuff,bufData[u32MemPosInBuff],u32NextWordLen));

                if(u32NextWordLen == 0)
                {
                    u32CharSumInOneWord = 0;
                    if(bufData[u32MemPosInBuff] < 0x80)
                    {
                        if(bufData[u32MemPosInBuff] == 0x0A || bufData[u32MemPosInBuff] == 0x09)
                        {
                            u32CharSumInOneWord = 0;
                        }
                        else if(bufData[u32MemPosInBuff]>=0x20&&bufData[u32MemPosInBuff]<=0x7E)
                        {
                            u32CharSumInOneWord = m_au8CharWidthTbl[bufData[u32MemPosInBuff]];
                        }
                        else
                        {
                            u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                        }
                    }
                    else
                    {
#if (ENABLE_ARABIC_OSD)
                        if((bufData[u32MemPosInBuff] >= 0xE0) && (bufData[u32MemPosInBuff] <= 0xFA))
                        {
                            u32CharSumInOneWord =  HEBREW_CHARACTOR_WIDTH;
                        }
                        else
                        {
                            u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                        }
#else
                        switch(m_enTextCharsetType)
                        {
                            case E_TEXT_CHARSET_CP1250:
                            case E_TEXT_CHARSET_CP1251:
                            case E_TEXT_CHARSET_CP1252:
                            case E_TEXT_CHARSET_CP1254:
                            case E_TEXT_CHARSET_CP1255:
                            case E_TEXT_CHARSET_CP1256:
                            case E_TEXT_CHARSET_CROATIAN_MAC:
                            {
                                if((bufData[u32MemPosInBuff] >= 0xE0) && (bufData[u32MemPosInBuff] <= 0xFA))
                                {
                                    u32CharSumInOneWord =  SPECIAL_CHARACTOR_WIDTH;
                                }
                                else
                                {
                                    u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                                }
                            }
                            break;

                            case E_TEXT_CHARSET_GBK:
                            case E_TEXT_CHARSET_DEFAULT:
                            default:
                            {
                                // It is GB code.
                                u32CharSumInOneWord = GBK_CHARACTOR_WIDTH;
                            }
                            break;
                        }
#endif
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneWord=%d u32CharSumInOneLine=%d\n",u32CharSumInOneWord,u32CharSumInOneLine));
                    u32CharSumInOneLine += u32CharSumInOneWord;
                    if (u32CharSumInOneLine > TEXT_PLAY_WINDOW_WIDTH)
                    {
                        u32MemPos = u32MemPosInBuff;
                        return true;
                    }
                    u32ANSILen = ANSI2UnicodeWordWidth(&bufData[u32MemPosInBuff], &u32NextWordLen);
                }
                else
                {
                    for(u32Index = 0; u32Index < u32NextWordLen; u32Index++)
                    {
                        u32CharSumInOneLine += m_au8CharWidthTbl[bufData[u32MemPosInBuff+u32Index]];

                        if (u32CharSumInOneLine > TEXT_PLAY_WINDOW_WIDTH)//couldn't cause buf array overflow
                        {
                            TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                            if(u32ParsedBytes !=0)
                            {
                                u32MemPos = u32MemPosInBuff;
                            }
                            else
                            {
                                u32MemPos = u32MemPosInBuff + u32Index + 1;
                            }
                            return true;
                        }
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                    u32ANSILen = u32NextWordLen;
                }
                u32MemPosInBuff += u32ANSILen;
                u32ParsedBytes += u32NextWordLen;
            }
        }
        else if  (u8FileType == EN_TEXT_UTF8)
        {
            U8 u32UTF8Len = 0;
            U32 u32CharSumInOneWord;
            while(u32MemPosInBuff < u32CurBuffLen)
            {
                //encounter blank space in first place, skip it
                if((u32ParsedBytes == 0) && (bufData[u32MemPosInBuff] == ' '))
                {
                    u32MemPosInBuff+=1;
                    continue;
                }

                //new line
                if(bufData[u32MemPosInBuff] == 0x0D)
                {
                    if(u32ParsedBytes == u32TargetBytes) // buffer already full
                    {

                    }
                    else
                    {
                        u32MemPosInBuff += 1;
                        if(bufData[u32MemPosInBuff] == 0x0A)
                        {
                            u32MemPosInBuff += 1;
                        }
                    }
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                //Get the word length
                u32NextWordLen = ASCWordWidth(&bufData[u32MemPosInBuff], u32CurBuffLen - u32MemPosInBuff);
                if((u32NextWordLen + u32ParsedBytes) >  u32TargetBytes)
                {
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }
                TEXT_DEBUG(printf("u32MemPos=%x bufData[u32MemPos]=%02x u32NextWordLen=%d\n",u32MemPosInBuff,bufData[u32MemPosInBuff],u32NextWordLen));

                if(u32NextWordLen == 0) //not a number or a alphabet, need to convert
                {
                    u32CharSumInOneWord = 0;
                    if(bufData[u32MemPosInBuff] < 0x80)
                    {
                        if(bufData[u32MemPosInBuff] == 0x0A || bufData[u32MemPosInBuff] == 0x09)
                        {
                            u32CharSumInOneWord = 0;
                        }
                        else if(bufData[u32MemPosInBuff]>=0x20&&bufData[u32MemPosInBuff]<=0x7E)
                        {
                            u32CharSumInOneWord = m_au8CharWidthTbl[bufData[u32MemPosInBuff]];
                        }
                        else
                        {
                            u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                        }
                    }
                    else
                    {
                         u32CharSumInOneWord = TEXT_DEFAULT_CHARWIDTH;
                    }

                    TEXT_DEBUG(printf("u32CharSumInOneWord=%d u32CharSumInOneLine=%d\n",u32CharSumInOneWord,u32CharSumInOneLine));
                    u32CharSumInOneLine += u32CharSumInOneWord;
                    if (u32CharSumInOneLine > TEXT_PLAY_WINDOW_WIDTH)
                    {
                        u32MemPos = u32MemPosInBuff;
                        return true;
                    }
                    u32UTF8Len = UTF8WordWidth(&bufData[u32MemPosInBuff]);
                    u32NextWordLen = 2;
                }
                else
                {
                    for(u32Index = 0; u32Index < u32NextWordLen; u32Index++)
                    {
                        u32CharSumInOneLine += m_au8CharWidthTbl[bufData[u32MemPosInBuff+u32Index]];

                        if(u32CharSumInOneLine > TEXT_PLAY_WINDOW_WIDTH)//couldn't cause buf array overflow
                        {
                            TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                            if(u32ParsedBytes !=0)
                            {
                                u32MemPos = u32MemPosInBuff;
                            }
                            else
                            {
                                u32MemPos = u32MemPosInBuff + u32Index + 1;
                            }
                            return true;
                        }
                    }
                    TEXT_DEBUG(printf("u32CharSumInOneLine=%d\n",u32CharSumInOneLine));
                    u32UTF8Len = u32NextWordLen;
                    u32NextWordLen *=2;// cause 16 bits per char
                }
                u32ParsedBytes += u32NextWordLen;
                u32MemPosInBuff += u32UTF8Len;
            }
        }
        u32MemPos = u32MemPosInBuff;
        return false;

    }
#endif


#else
    // NOTE: according to the implementation of TEXT_GetLine(), the real size of buf should be len+16 or
    // TEXT_GetLine() MAY access the memory not belong to buf and this criterion is NOTHING BUT A WORKAROUND
    static BOOL TEXT_GetData(U8 *buf, U8 *pu8bufData, U32 len)
    {
        U32 count = 0;
        U32 num = 0; // buf used number
        U16 tmp;
        U8 *bufData=(U8 *)_PA2VA((U32)pu8bufData);

        //Memo: when 'len' is larger than a certain number(ex. TEXT_CHAR_NUM_PER_LINE*2), memset() will cause 'len = 0'.
        //      So, comment out below line to avoid problem.
        //for most case TxtBuff.u32TxtReadSize = 1328
        memset(buf, 0, len + 2);
        if (u8FileType == EN_TEXT_UNIB)
        {
            U32 u32NextWordLen = 0;
            while((u32MemPos < TxtBuff.u32TxtReadSize) && (bufData[u32MemPos] == 0) &&(bufData[u32MemPos+1] == ' '))
            {
                //printf("encounter blanck space in first place, skip it\n");
                u32MemPos+=2;
            }
            while ((num < len) && (u32MemPos < TxtBuff.u32TxtReadSize))
            {
                if((count+1) > len)//buf array overflow
                {
                    buf[count] = 0x00;
                    buf[count+1] = 0x00;
                    return true;
                }
                if (u32MemPos < TxtBuff.u32TxtReadSize)
                {
                    U32 u32MemPosOld = u32MemPos;
                    u32NextWordLen = UniBigWordBigWidth(&bufData[u32MemPos], TxtBuff.u32TxtReadSize - u32MemPos);
                    u32NextWordLen *=2;// cause 16 bits per char
                    if(u32NextWordLen > len)
                    {
                        //printf("1 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                    }
                    else if((u32NextWordLen + count) >  len)
                    {
                        //printf("find xcross word, put to next line\n");
                        //printf("2 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        buf[count]=0;
                        buf[count+1]=0;
                        return true;
                    }
                    else
                    {
                        //printf("3 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        // if 0, we can do the parse once
                    }
                    do
                    {
                        //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                        buf[count]=bufData[u32MemPos+1];
                        buf[count+1]=bufData[u32MemPos];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!
                        if (buf[count+1] == 0x00)
                        {
                            if (buf[count] == 0x0D)
                            {
                                buf[count] = 0x00;
                                count += 2;
                                u32MemPos += 2;
                                //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                                buf[count]=bufData[u32MemPos+1];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!
                                buf[count+1]=bufData[u32MemPos];

                                if (buf[count+1] == 0x00 && buf[count] == 0x0A)
                                {
                                    buf[count] = 0x00;
                                    u32MemPos += 2;
                                }
                                return true;
                            }
                        }
                        num += 2;
                        if (u32MemPos >= TxtBuff.u32TxtReadSize || num >= len)//couldn't cause buf array overflow
                        {
                            buf[count+2] = 0x00;
                            buf[count+3] = 0x00;
                            u32MemPos += 2;
                            return true;
                        }
                        count += 2;
                        u32MemPos += 2;
                    }while((u32MemPos - u32MemPosOld) < u32NextWordLen);
                }
            };
        }
        else if (u8FileType == EN_TEXT_UNIS)
        {
            U32 u32NextWordLen = 0;
            while((u32MemPos < TxtBuff.u32TxtReadSize) && (bufData[u32MemPos] == ' ') &&(bufData[u32MemPos+1] == 0))
            {
                //printf("encounter blanck space in first place, skip it\n");
                u32MemPos+=2;
            }
            while ((num < len) && (u32MemPos < TxtBuff.u32TxtReadSize))
            {
                if((count+1) > len)//buf array overflow
                {
                    buf[count] = 0x00;
                    buf[count+1] = 0x00;
                    return true;
                }
                if (u32MemPos < TxtBuff.u32TxtReadSize)
                {
                    U32 u32MemPosOld = u32MemPos;
                    u32NextWordLen = UniWordWidth(&bufData[u32MemPos], TxtBuff.u32TxtReadSize - u32MemPos);
                    u32NextWordLen *=2;// cause 16 bits per char
                    if(u32NextWordLen > len)
                    {
                        //printf("1 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                    }
                    else if((u32NextWordLen + count) >  len)
                    {
                        //printf("find xcross word, put to next line\n");
                        //printf("2 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        buf[count]=0;
                        buf[count+1]=0;
                        return true;
                    }
                    else
                    {
                        //printf("3 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        // if 0, we can do the parse once
                    }
                    do
                    {
                        //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                        buf[count]=bufData[u32MemPos];
                        buf[count+1]=bufData[u32MemPos+1];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!

                        if (buf[count+1] == 0x00)
                        {
                            if (buf[count] == 0x0D)
                            {
                                buf[count] = 0x00;
                                count += 2;
                                u32MemPos += 2;
                                //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                                buf[count]=bufData[u32MemPos];
                                buf[count+1]=bufData[u32MemPos+1];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!

                                if (buf[count+1] == 0x00 && buf[count] == 0x0A)
                                {
                                    buf[count] = 0x00;
                                    u32MemPos += 2;
                                }
                                return true;
                            }
                        }
                        num += 2;
                        if (u32MemPos >= TxtBuff.u32TxtReadSize || num >= len)//couldn't cause buf array overflow
                        {
                            buf[count+2] = 0x00;
                            buf[count+3] = 0x00;
                            u32MemPos += 2;
                            return true;
                        }
                        count += 2;
                        u32MemPos += 2;
                    }while((u32MemPos - u32MemPosOld) < u32NextWordLen);
                }
            };
        }
        else if (u8FileType == EN_TEXT_ANSI)
        {
            U32 CntUniCode = 0;
            U32 u32NextWordLen;
            //printf("u32MemPos = 0x%lx, TxtBuff.u32TxtReadSize = 0x%lx\n", u32MemPos, TxtBuff.u32TxtReadSize);
            // if line head is blanck space, skip this
            while((u32MemPos < TxtBuff.u32TxtReadSize) && (bufData[u32MemPos] == ' '))
            {
                //printf("encounter blanck space in first place, skip it\n");
                u32MemPos++;
            }

            while ((num < len) && (u32MemPos < TxtBuff.u32TxtReadSize))
            {
                if((count+1) > len)//buf array overflow
                {
                    buf[count] = 0x00;
                    buf[count+1] = 0x00;
                    return true;
                }
                if (u32MemPos < TxtBuff.u32TxtReadSize)
                {
                    U32 u32MemPosOld = u32MemPos;
                    u32NextWordLen = ASCWordWidth(&bufData[u32MemPos], TxtBuff.u32TxtReadSize - u32MemPos);
                    if(2*u32NextWordLen > len)
                    {
                        //printf("1 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                    }
                    else if((2*u32NextWordLen + count) >  len)
                    {
                        //printf("find xcross word, put to next line\n");
                        //printf("2 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        buf[count]=0;
                        buf[count+1]=0;
                        return true;
                    }
                    else
                    {
                        //printf("3 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        // if 0, we can do the parse once
                    }

                    do
                    {
                        if((count+1) > len)//buf array overflow
                        {
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            return true;
                        }
                        //msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos + u32MemPos, XD2PHY(&buf[count]), 2, MIU_SDRAM2SDRAM);
                        buf[count]=bufData[u32MemPos];
                        buf[count+1]=bufData[u32MemPos+1];    //Eric-PH Lee 20080422: Remove msAPI_MIC_Copy() because it's too slow!!!
                        //printf("buf[%d] = %c bufData[0x%lx] = %c \r\n", (U8)count, (U8)buf[count],u32MemPos,(U8)bufData[u32MemPos]);
                        //printf("buf[%d] = %x\r\n", (U8)(count+1), (U8)buf[count+1]);
                        if (buf[count] == '\r')
                        {
                            //printf("enter r\n");
                            if(buf[count+1] == '\n' || buf[count+1] == '\r')
                            {
                                u32MemPos += 2;
                            }
                            else
                            {
                                u32MemPos += 1;
                            }
                            //buf[count] = 0x8A;
                            //buf[count+1] = 0xE0;    //0xE08A : \n
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            count += 2;
                            num += 2;
                            //printf("exit r\n");
                            return true;
                        }
                        else if (buf[count] == '\n') //DOS format
                        {
                            u32MemPos += 1;
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            return true;
                        }
                        else if (buf[count] < 0x80)
                        {
                            if (buf[count] == 0x0A)
                            {
                                u32MemPos += 1;
                            }
                            else if (buf[count] == 0x09)
                            {
                                buf[count] = 0x00;
                                buf[count+1] = 0x20;
                                buf[count+2] = 0x00;
                                buf[count+3] = 0x20;
                                buf[count+4] = 0x00;
                                buf[count+5] = 0x20;
                                buf[count+6] = 0x00;
                                buf[count+7] = 0x20;
                                count += 8;
                                num += 4;
                                u32MemPos += 1;
                            }
                            else
                            {
                                buf[count + 1] = 0x00;

                                count += 2;
                                num += 2;// 1   //modified from public version(20481)
                                u32MemPos += 1;
                            }
                        }
#if (ENABLE_ARABIC_OSD)
                        //for Hebrew, convert according WINDOWS 1255
                        else
                        {
                            tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1255, buf[count]);
                            //printf("%02x->%x\n",buf[count] ,tmp);
                            buf[count+1] = tmp >> 8;
                            buf[count] = tmp & 0xFF;
                            count += 2;
                            num += 2;
                            u32MemPos += 1;
                        }
#else
                        else
                        {
                            switch(m_enTextCharsetType)
                            {
                                case E_TEXT_CHARSET_CP874:                // Thai Windows Code Page 874
                                case E_TEXT_CHARSET_CP1250:               // windows central european
                                case E_TEXT_CHARSET_CP1251:               // Cyrillic Windows Code Page 1251
                                case E_TEXT_CHARSET_CP1252:               // windows western european
                                case E_TEXT_CHARSET_CP1253:               // Greek Windows Code Page 1253
                                case E_TEXT_CHARSET_CP1254:               // windows turkey
                                case E_TEXT_CHARSET_CP1255:               // Hebrew Windows Code Page 1255
                                case E_TEXT_CHARSET_CP1256:               // Arabic Code Page 1256
                                case E_TEXT_CHARSET_CP1257:               // Latin 4 Code Page 1257
                                case E_TEXT_CHARSET_CP1258:               // Vietnamese  Code Page 1258
                                case E_TEXT_CHARSET_ISO_8859_05:          //Cyrillic(ISO)
                                case E_TEXT_CHARSET_ISO_8859_10:          //
                                case E_TEXT_CHARSET_CROATIAN_MAC:         // croatian mac
                                {
                                    EN_CHARACTER_CODE_TABLE enCharCodeTable = WINDOWS_CP1250;

                                    if(m_enTextCharsetType == E_TEXT_CHARSET_CP874)
                                    {
                                        enCharCodeTable = WINDOWS_CP874;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1250)
                                    {
                                        enCharCodeTable = WINDOWS_CP1250;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1251)
                                    {
                                        enCharCodeTable = WINDOWS_CP1251;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1252)
                                    {
                                        enCharCodeTable = WINDOWS_CP1252;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1253)
                                    {
                                        enCharCodeTable = WINDOWS_CP1253;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1254)
                                    {
                                        enCharCodeTable = WINDOWS_CP1254;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1255)
                                    {
                                        enCharCodeTable = WINDOWS_CP1255;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1256)
                                    {
                                        enCharCodeTable = WINDOWS_CP1256;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1257)
                                    {
                                        enCharCodeTable = WINDOWS_CP1257;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CP1258)
                                    {
                                        enCharCodeTable = WINDOWS_CP1258;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_ISO_8859_10/*SUBTITLE_CHARSET_ISO_8859_10*/)
                                    {
                                        enCharCodeTable = ISO_8859_10;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_ISO_8859_05/*SUBTITLE_CHARSET_ISO_8859_05*/ )
                                    {
                                        enCharCodeTable = ISO_8859_05;
                                    }
                                    else if(m_enTextCharsetType == E_TEXT_CHARSET_CROATIAN_MAC)
                                    {
                                        enCharCodeTable = WINDOWS_CROATIAN_MAC;
                                    }

                                    tmp = MApp_CharTable_MappingCharToUCS2(enCharCodeTable, buf[count]);
                                    //printf("%02x->%x\n",buf[count] ,tmp);
                                    buf[count+1] = tmp >> 8;
                                    buf[count] = tmp & 0xFF;
                                    count += 2;
                                    num += 2;
                                    u32MemPos += 1;
                                }
                                break;
                                case E_TEXT_CHARSET_KOREAN:
                                {
                                #if(CHAR_TABLE_SUPPORT_KOREAN_CODE)
                                    tmp = MApp_CharTable_MappingKor2Unicode(((U16)buf[count] << 8) + buf[count+1]);
                                    CntUniCode ++;
                                    buf[count+1] = tmp >> 8;
                                    buf[count] = tmp & 0xFF;
                                    num += 2;
                                    count += 2;
                                    u32MemPos += 2;
                                #else
                                    //#error "32M unsupport Korean unicode"
                                    printf("\nError: 32M unsupport Korean unicode\n");
                                #endif
                                }
                                break;
                                case E_TEXT_CHARSET_GBK:
                                case E_TEXT_CHARSET_DEFAULT:
                                default:
                                {
                                    // It is GB code.
                                    tmp = MApp_Transfer2Unicode(((U16)buf[count] << 8) + buf[count+1]);
                                    CntUniCode ++;
                                    buf[count+1] = tmp >> 8;
                                    buf[count] = tmp & 0xFF;
                                    num += 2;
                                    count += 2;
                                    u32MemPos += 2;
                                }
                                break;
                            }
                        }
#endif
                        if (u32MemPos >= TxtBuff.u32TxtReadSize)
                        {
                            //printf("exit TxtBuff.u32TxtReadSize = 0x%lx\n", TxtBuff.u32TxtReadSize);
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            return true;
                        }

                        if ((u32NextWordLen == 0) && (( count-CntUniCode*2)*10+CntUniCode*32)>1600 )
                        {

                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            //printf("CntUniCode=%lu, count=%lu, total=%lu\r\n",CntUniCode, count, (( count-CntUniCode*2)*10+CntUniCode*32));
                            return true;
                        }
                    }while((u32MemPos - u32MemPosOld) < u32NextWordLen);
                }
            };
            if(count)
                return true;
        }
        else if  (u8FileType == EN_TEXT_UTF8)
        {
            U32 u32NextWordLen = 0;

            //printf("u32MemPos = 0x%lx, TxtBuff.u32TxtReadSize = 0x%lx\n", u32MemPos, TxtBuff.u32TxtReadSize);

            // if line head is blanck space, skip this
            while((u32MemPos < TxtBuff.u32TxtReadSize) && (bufData[u32MemPos] == ' '))
            {
                //printf("encounter blanck space in first place, skip it\n");
                u32MemPos++;
            }

            while ((num < len) && (u32MemPos < TxtBuff.u32TxtReadSize))
            {
                if((count+1) > len)//buf array overflow
                {
                    buf[count] = 0x00;
                    buf[count+1] = 0x00;
                    return true;
                }
                if (u32MemPos < TxtBuff.u32TxtReadSize)
                {
                    U32 u32MemPosOld = u32MemPos;
                    u32NextWordLen = ASCWordWidth(&bufData[u32MemPos], TxtBuff.u32TxtReadSize - u32MemPos);

                     if(2*u32NextWordLen > len)
                    {
                        //printf("1 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                    }
                    else if((2*u32NextWordLen + count) >  len)
                    {
                        //printf("find xcross word, put to next line\n");
                        //printf("2 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        buf[count]=0;
                        buf[count+1]=0;
                        return true;
                    }
                    else
                    {
                        //printf("3 u32NextWordLen = 0x%lx, u32MemPos = 0x%lx\n", u32NextWordLen, u32MemPos);
                        // if 0, we can do the parse once
                    }

                    do
                    {
                        buf[count]=bufData[u32MemPos];
                        buf[count+1]=bufData[u32MemPos+1];
                        buf[count+2]=bufData[u32MemPos+2];
                        if ((buf[count] == 0xd) && (buf[count+1] == 0xa))
                        {
                            buf[count]=0;
                            buf[count+1]=0;
                            buf[count+2]=0;
                            u32MemPos += 2;

                            //printf("find feed back\n");
                            return true;
                        }
                        else if (buf[count] < 0x80)
                        {
                            buf[count + 1] = 0x00;
                            count += 2;
                            num += 2;
                            u32MemPos += 1;
                        }
                        else if ((buf[count] >=0xe0) && (buf[count+1] >=0x80) && (buf[count+2] >=0x80))
                        {
                            //UTF8 to UNICODE
                            buf[count]=(bufData[u32MemPos+2]&0x3f) + ((bufData[u32MemPos+1]&3)<<6);
                            buf[count+1]=((bufData[u32MemPos+1]&0x3c)>>2) + ((bufData[u32MemPos]&0xf)<<4);
                            //printf(" [%x] [%x] [%x]",bufData[u32MemPos],bufData[u32MemPos+1], bufData[u32MemPos+2]);
                            //printf("==> [%x],  [%x]",buf[count],buf[count+1]);

                            num += 2;
                            count += 2;
                            u32MemPos += 3;
                        }
                        else if (((buf[count] >=0xc0) && (buf[count] <0xe0)) && (buf[count+1] >=0x80))
                        {
                            //UTF8 to UNICODE
                            buf[count]=(bufData[u32MemPos+1]&0x3f)+((bufData[u32MemPos]&0x3)<<6);
                            buf[count+1]=(bufData[u32MemPos]&0x1f)>>2;

                            num += 2;
                            count += 2;
                            u32MemPos += 2;
                        }
                        else
                        {
                            //printf("1=%x,2=%x,3=%x\n", buf[count] , buf[count+1], buf[count+2]);
                            __ASSERT(0);
                            u32MemPos+=1;
                        }
                        if (u32MemPos >= TxtBuff.u32TxtReadSize || num >= len)//couldn't cause buf array overflow
                        {
                            buf[count] = 0x00;
                            buf[count+1] = 0x00;
                            //u32MemPos += 2;
                            return true;
                        }
                    }while((u32MemPos - u32MemPosOld) < u32NextWordLen);
                }
            };
            return true;
        }

        return false;

    }

#if TEXT_FAST_LOAD_FILE
//******************************************************************************
/// Parse the word to count bytes for one line.
/// @param  pu8bufData \b IN  Specify the data.
/// @param  u32TargetBytes \b IN  Specify the targert bytes of one line.
/// @return TRUE or FALSE
//******************************************************************************
BOOL TEXT_ParseData(U8 *pu8bufData, U32 u32TargetBytes)
    {
        //U16 tmp;
        U8 *bufData;
        U32 u32ParsedBytes = 0;
        U32 u32MemPosInBuff = u32MemPos;
        U32 u32CurBuffLen = TxtBuff.u32TxtReadSize;
        U32 u32NextWordLen = 0;

        //Use cache address
        bufData =(U8 *)MsOS_PA2KSEG0((U32)pu8bufData);

        if (u8FileType == EN_TEXT_UNIB)
        {
            while(u32MemPosInBuff < u32CurBuffLen)
            {
                //encounter blank space in first place, skip it
                if((u32ParsedBytes == 0) && (bufData[u32MemPosInBuff] == 0x00) && (bufData[u32MemPosInBuff+1] == ' '))
                {
                    u32MemPosInBuff+=2;
                    continue;
                }

                //new line
                if((bufData[u32MemPosInBuff] == 0x00) &&(bufData[u32MemPosInBuff+1] == 0x0D))
                {
                    if(u32ParsedBytes == u32TargetBytes)
                    {

                    }
                    else
                    {
                        u32MemPosInBuff += 2;
                        if((bufData[u32MemPosInBuff] == 0x00) && (bufData[u32MemPosInBuff+1] == 0x0A))
                        {
                            u32MemPosInBuff += 2;
                        }
                    }
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                //Get the word length
                u32NextWordLen = UniBigWordBigWidth(&bufData[u32MemPosInBuff], u32CurBuffLen - u32MemPosInBuff);

                if(u32NextWordLen == 0) //not a number or a alphabet
                {
                    u32NextWordLen = 2;
                }
                else
                {
                    u32NextWordLen *=2;// cause 16 bits per char
                }

                if((u32NextWordLen + u32ParsedBytes) > u32TargetBytes)
                {
                    //If next word length > one line length, cut the word
                    if(u32NextWordLen > u32TargetBytes)
                    {
                        u32MemPos = u32MemPosInBuff + (u32TargetBytes - u32ParsedBytes);
                    }
                    else
                    {
                        u32MemPos = u32MemPosInBuff;
                    }
                    return true;
                }
                u32ParsedBytes += u32NextWordLen;
                u32MemPosInBuff += u32NextWordLen;
            }
        }
        else if (u8FileType == EN_TEXT_UNIS)
        {
            while(u32MemPosInBuff < u32CurBuffLen)
            {
                //encounter blank space in first place, skip it
                if((u32ParsedBytes == 0) && (bufData[u32MemPosInBuff] == ' ') && (bufData[u32MemPosInBuff+1] == 0x00))
                {
                    u32MemPosInBuff+=2;
                    continue;
                }

                //new line
                if((bufData[u32MemPosInBuff] == 0x0D) &&(bufData[u32MemPosInBuff+1] == 0x00))
                {
                    if(u32ParsedBytes == u32TargetBytes)
                    {

                    }
                    else
                    {
                        u32MemPosInBuff += 2;
                        if((bufData[u32MemPosInBuff] == 0x0A) && (bufData[u32MemPosInBuff+1] == 0x00))
                        {
                            u32MemPosInBuff += 2;
                        }
                    }
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                //Get the word length
                u32NextWordLen = UniWordWidth(&bufData[u32MemPosInBuff], u32CurBuffLen - u32MemPosInBuff);

                if(u32NextWordLen == 0) //not a number or a alphabet
                {
                    u32NextWordLen = 2;
                }
                else
                {
                    u32NextWordLen *=2;// cause 16 bits per char
                }

                if((u32NextWordLen + u32ParsedBytes) > u32TargetBytes)
                {
                    //If next word length > one line length, cut the word
                    if(u32NextWordLen > u32TargetBytes)
                    {
                        u32MemPos = u32MemPosInBuff + (u32TargetBytes - u32ParsedBytes);
                    }
                    else
                    {
                        u32MemPos = u32MemPosInBuff;
                    }
                    return true;
                }
                u32ParsedBytes += u32NextWordLen;
                u32MemPosInBuff += u32NextWordLen;
            }
        }
        else if (u8FileType == EN_TEXT_ANSI)
        {
            U8 u32ANSILen = 0;

            while(u32MemPosInBuff < u32CurBuffLen)
            {
                //encounter blank space in first place, skip it
                if((u32ParsedBytes == 0) && (bufData[u32MemPosInBuff] == ' '))
                {
                    u32MemPosInBuff+=1;
                    continue;
                }

                //new line
                if(bufData[u32MemPosInBuff] == 0x0D)
                {
                    if(u32ParsedBytes == u32TargetBytes) // buffer already full
                    {

                    }
                    else
                    {
                        u32MemPosInBuff += 1;
                        if(bufData[u32MemPosInBuff] == 0x0A)
                        {
                            u32MemPosInBuff += 1;
                        }
                    }
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                //Get the word length
                u32NextWordLen = ASCWordWidth(&bufData[u32MemPosInBuff], u32CurBuffLen - u32MemPosInBuff);

                if(u32NextWordLen == 0) //not a number or a alphabet, need to convert
                {
                    u32ANSILen = ANSI2UnicodeWordWidth(&bufData[u32MemPosInBuff], &u32NextWordLen);
                }
                else
                {
                    u32ANSILen = u32NextWordLen;
                    u32NextWordLen *=2;// cause 16 bits per char
                }

                if((u32NextWordLen + u32ParsedBytes) > u32TargetBytes)
                {
                    //If next word length > one line length, cut the word
                    if(u32NextWordLen > u32TargetBytes)
                    {
                        u32MemPos = u32MemPosInBuff + (u32TargetBytes - u32ParsedBytes)/2;
                    }
                    else
                    {
                        u32MemPos = u32MemPosInBuff;
                    }
                    return true;
                }
                u32ParsedBytes += u32NextWordLen;
                u32MemPosInBuff += u32ANSILen;
            }
        }
        else if  (u8FileType == EN_TEXT_UTF8)
        {
            U8 u32UTF8Len = 0;

            while(u32MemPosInBuff < u32CurBuffLen)
            {
                //encounter blank space in first place, skip it
                if((u32ParsedBytes == 0) && (bufData[u32MemPosInBuff] == ' '))
                {
                    u32MemPosInBuff+=1;
                    continue;
                }

                //new line
                if(bufData[u32MemPosInBuff] == 0x0D)
                {
                    if(u32ParsedBytes == u32TargetBytes) // buffer already full
                    {

                    }
                    else
                    {
                        u32MemPosInBuff += 1;
                        if(bufData[u32MemPosInBuff] == 0x0A)
                        {
                            u32MemPosInBuff += 1;
                        }
                    }
                    u32MemPos = u32MemPosInBuff;
                    return true;
                }

                //Get the word length
                u32NextWordLen = ASCWordWidth(&bufData[u32MemPosInBuff], u32CurBuffLen - u32MemPosInBuff);

                if(u32NextWordLen == 0) //not a number or a alphabet, need to convert
                {
                    u32UTF8Len = UTF8WordWidth(&bufData[u32MemPosInBuff]);
                    u32NextWordLen = 2;
                }
                else
                {
                    u32UTF8Len = u32NextWordLen;
                    u32NextWordLen *=2;// cause 16 bits per char
                }

                if((u32NextWordLen + u32ParsedBytes) > u32TargetBytes)
                {
                    //If next word length > one line length, cut the word
                    if(u32NextWordLen > u32TargetBytes)
                    {
                        u32MemPos = u32MemPosInBuff + (u32TargetBytes - u32ParsedBytes)/2;
                    }
                    else
                    {
                        u32MemPos = u32MemPosInBuff;
                    }
                    return true;
                }
                u32ParsedBytes += u32NextWordLen;
                u32MemPosInBuff += u32UTF8Len;
            }
        }
        u32MemPos = u32MemPosInBuff;
        return false;

    }
#endif
#endif

BOOLEAN TEXT_TotalPage(void)
{
    U8 buf[100];

    memset(buf, 0, sizeof(buf));//remove klocwork warning message
    TEXT_FileClose();
    TEXT_Init();
    TEXT_FileOpen(0);

    u32PageIndex = 0;
    TEXT_FileRead(&TxtBuff);

//    msAPI_MIU_Copy(TxtBuff.u32TxtBuffPos, (U32)(buf), 3, MIU_SDRAM2SDRAM );
    memcpy(buf,(U8 *)_PA2VA((TxtBuff.u32TxtBuffPos)),3);

    if (buf[0] == 0xFF && buf[1] == 0xFE)
    {
        u8FileType = EN_TEXT_UNIS;
        u32FilePos = 2;
    }
    else if (buf[0] == 0xFE && buf[1] == 0xFF)
    {
        u8FileType = EN_TEXT_UNIB;
        u32FilePos = 2;
    }
    else if (buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF)
    {
        u8FileType = EN_TEXT_UTF8;
        u32FilePos = 3;
        //TEXT_FileClose();
        //MApp_UiMenu_DrawTextBrowserWindow();
        //return FALSE;
    }
    else
    {
        u8FileType = EN_TEXT_ANSI;
        u32FilePos = 0;
    }
    TEXT_DEBUG(printf("File type is %d\r\n", (int)u8FileType));
    u32MemPos = 0;
    SetTextPageOffset(0, u32FilePos);

    do{
		MApp_ProcessUserInput();
		if(u8KeyCode == KEY_EXIT)
		{
			break;
		}
        msAPI_Timer_ResetWDT();

        TEXT_BrowserText();


        u32FilePos = GetTextPageOffset(u32PageIndex+1);

        if (u32FilePos != 0 && u32FilePos < u32FileLength)
        {
            u32PageIndex ++;
            if(u32PageIndex%10==0)
            {
                MApp_MPlayer_BGM_Bitstream_Handle();
            }

            if(u32PageIndex >= TEXT_MAX_PAGE_NUM)
            {
                break;
            }
        }
        else
        {
            break;
        }

    }while(1);

    u32TotalPage=u32PageIndex;
    TEXT_DEBUG(printf("Total page is %lu\r\n", u32TotalPage));

    return TRUE;
}

BOOLEAN TEXT_LoadPreviewText(void)
{
    U8 buf[4];
    u32MemPos = 0;
    u32FilePos = 0;
    TEXT_FileRead(&TxtBuff);
    memcpy(buf,(U8 *)_PA2VA((TxtBuff.u32TxtBuffPos)),3);
    if (buf[0] == 0xFF && buf[1] == 0xFE)
    {
        u8FileType = EN_TEXT_UNIS;
        u32FilePos = 2;
    }
    else if (buf[0] == 0xFE && buf[1] == 0xFF)
    {
        u8FileType = EN_TEXT_UNIB;
        u32FilePos = 2;
    }
    else if (buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF)
    {
        u8FileType = EN_TEXT_UTF8;
        u32FilePos = 3;
       // TEXT_FileClose();
       // return FALSE;
    }
    else
    {
        u8FileType = EN_TEXT_ANSI;
        u32FilePos = 0;
    }
    u32MemPos = 0;

    TxtBuff.u32TxtReqSize = 0x400;  //Read 0x400 is enough for text preview!
    if(!TEXT_FileRead(&TxtBuff))
    {
        MS_DEBUG_MSG(printf("TEXT_FileRead error!!\n"));
    }

    return TRUE;
}

void TEXT_BrowserText(void)
{
    U16 i;
    U8 *bufData;
    U8 buf[TXT_BROWER_BUFFER_SIZE];
#if TEXT_FAST_LOAD_FILE
    UNUSED(*buf);
#endif

    TEXT_FileRead(&TxtBuff);
    TEXT_DEBUG(printf("Read Size: 0x%lx\r\n", TxtBuff.u32TxtReadSize));
    TEXT_DEBUG(printf("File Read MemPos: 0x%lx\r\n", TxtBuff.u32TxtBuffPos));

    u32MemPos=0;

    bufData = (U8 *)(TxtBuff.u32TxtBuffPos);

    for (i = 0; i < TEXT_LINE_NUM_PER_PAGE; i ++)
    {
        TEXT_DEBUG(printf("%x i=%d\n",u32MemPos,i));
    #if TEXT_SHOW_BYLENGTH
        #if TEXT_FAST_LOAD_FILE
            if (!TEXT_ParseData(bufData, TEXT_CHAR_NUM_PER_LINE*2))
            {
                break;
            }
        #else
            if (!TEXT_GetData(buf, bufData, TEXT_CHAR_NUM_PER_LINE*2,FALSE))
            {
                break;
            }
        #endif
    #else
        #if TEXT_FAST_LOAD_FILE
            if (!TEXT_ParseData(bufData, TEXT_CHAR_NUM_PER_LINE*2))
            {
                break;
            }
        #else
            if (!TEXT_GetData(buf, bufData, TEXT_CHAR_NUM_PER_LINE*2))
            {
                break;
            }
        #endif
    #endif
    }
    TEXT_DEBUG(printf("current page[%lx] = %lx\r\n", u32PageIndex, GetTextPageOffset(u32PageIndex)));
    TEXT_DEBUG(printf("current page length = %lx\r\n", u32MemPos));

    SetTextPageOffset(u32PageIndex + 1, GetTextPageOffset(u32PageIndex) + u32MemPos );

    TEXT_DEBUG(printf("next page[%lx] = %lx\r\n\r\n", u32PageIndex+1, GetTextPageOffset(u32PageIndex+1)));
}

BOOLEAN TEXT_LoadBrowserText(void)
{
    TxtBuff.u32TxtReqSize = 0x1000;

    if(!TEXT_FileRead(&TxtBuff))
    {
        TEXT_DEBUG(printf("TEXT_FileRead error!!\n"));
        return FALSE;
    }
    return TRUE;
}

BOOLEAN MApp_Text_Preview(void)
{
    TEXT_FileClose();
    TEXT_Init();
    TEXT_FileOpen(0);
    return TEXT_LoadPreviewText();
}

BOOLEAN Mapp_Text_Browser(void)
{
    U8 buf[4];

    if (!TEXT_TotalPage())
        return FALSE;

    TEXT_FileClose();
    TEXT_Init();
    TEXT_FileOpen(0);
// Fixed a bug : If there are 2 text file, one is in Unicode and another is in ASCII,
//                  play these two file will display in wrong type. Sometimes see WHITE screen
//                  and sometimes see text in wrong characters.
#if 1
    u32MemPos = 0;
    u32FilePos = 0;

    TEXT_FileRead(&TxtBuff);
    memcpy(buf,(U8 *)_PA2VA((TxtBuff.u32TxtBuffPos)),3);

    if (buf[0] == 0xFF && buf[1] == 0xFE)
    {
        u8FileType = EN_TEXT_UNIS;
        u32FilePos = 2;
    }
    else if (buf[0] == 0xFE && buf[1] == 0xFF)
    {
        u8FileType = EN_TEXT_UNIB;
        u32FilePos = 2;
    }
    else if (buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF)
    {
        u8FileType = EN_TEXT_UTF8;
        u32FilePos = 3;
        //TEXT_FileClose();
        //return FALSE;
    }
    else
    {
        u8FileType = EN_TEXT_ANSI;
        u32FilePos = 0;
    }
#else
    if (u8FileType == EN_TEXT_UNIS)
    {
        u32FilePos = 2;
    }
    else if (u8FileType == EN_TEXT_UNIB)
    {
        u32FilePos = 2;
    }
    else if (u8FileType == EN_TEXT_UTF8)
    {
        u32FilePos = 3;
    }
    else
    {
        u32FilePos = 0;
    }
#endif
    u32PageIndex = 0;
    TEXT_DEBUG(printf("File type is %d\r\n", (int)u8FileType));
    u32MemPos = 0;
    SetTextPageOffset(0, u32FilePos);
    TEXT_LoadBrowserText();

    return TRUE;
}

#if 0
void MApp_TEXT_ProcessKey(void)
{
    switch(u8KeyCode)
    {
    case KEY_PAGE_UP:
        TEXT_DEBUG(printf("Get PAGE UP KEY.\n"));
        if (u32PageIndex != 0)
        {
            u32PageIndex --;
            u32FilePos = GetTextPageOffset(u32PageIndex);
            TEXT_DEBUG(printf("u32FilePos = %lx\r\n", u32FilePos));
            TEXT_DrawBrowserText();
        }
        break;
    case KEY_PAGE_DOWN:
        //TEXT_DEBUG(printf("Get PAGE DOWN KEY.\n"));
        u32FilePos = GetTextPageOffset(u32PageIndex+1);
        TEXT_DEBUG(printf("u32FilePos = %lx\r\n", u32FilePos));
        if (u32FilePos != 0 && u32FilePos < u32FileLength)
        {
            u32PageIndex ++;
            TEXT_DrawBrowserText();
        }
        break;
    case KEY_EXIT:
        TEXT_FileClose();
        break;
    case KEY_NEXT:
        TEXT_DEBUG(printf("Get NEXT PAGE KEY.\n"));
        break;
    case KEY_PREVIOUS:
        Mapp_Text_Browser();
        break;
    default:
        break;
    }

    u8KeyCode = KEY_NULL;
}
#endif

BOOLEAN MApp_Text_PrevPage(void)
{
    if (u32PageIndex != 0)
    {
        u32PageIndex --;
        u32MemPos = 0;
        u32FilePos = GetTextPageOffset(u32PageIndex);
        TEXT_DEBUG(printf("u32FilePos = %lx\r\n", u32FilePos));
        TEXT_LoadBrowserText();
        return TRUE;
    }
    return FALSE;
}

BOOLEAN MApp_Text_NextPage(void)
{
    SetTextPageOffset(u32PageIndex + 1, GetTextPageOffset(u32PageIndex) + u32MemPos);
    //TEXT_DEBUG(printf("next page[%lx] = %lx\r\n", u32PageIndex+1, GetTextPageOffset(u32PageIndex+1)));

    u32FilePos = GetTextPageOffset(u32PageIndex+1);
    TEXT_DEBUG(printf("u32FilePos = %lx\r\n", u32FilePos));
    TEXT_DEBUG(printf("u32FileLength = %lx\r\n", u32FileLength));
    if (u32FilePos != 0 && u32FilePos < u32FileLength)
    {
        u32PageIndex ++;
        u32MemPos = 0;
        TEXT_LoadBrowserText();
        return TRUE;
    }
    return FALSE;
}

BOOLEAN MApp_Text_SetFileEntry(FileEntry *pEntry)
{
    m_pTextFileEntry = pEntry;
    return TRUE;
}

U32 MApp_TEXT_GetPageIndex(void)
{
    return u32PageIndex;
}

U32 MApp_TEXT_GetTotalPage(void)
{
    return u32TotalPage;
}

U32* MApp_TEXT_GetCurrentLineText(BOOLEAN bPreviw)
{
    U32 u32TempLen;
    U32* pu32TextBufPool;
    U8* u8Buf;

    pu32TextBufPool = (U32 *)_PA2VA(((TEXT_DATA_READ_MEMORY_TYPE & MIU1) ? (TEXT_DATA_READ_ADR | MIU_INTERVAL) : (TEXT_DATA_READ_ADR)));
    memset(pu32TextBufPool,0,TEXT_CHAR_NUM_PER_LINE*2+2);
    TEXT_DEBUG(printf("Read Size: 0x%lx\r\n", TxtBuff.u32TxtReadSize));
    TEXT_DEBUG(printf("File Read MemPos: 0x%lx\r\n", u32MemPos));

    if(bPreviw)
    {
        u32TempLen=TEXT_PREVIEW_CHAR_NUM_PER_LINE*2;
    }
    else
    {
        u32TempLen=TEXT_CHAR_NUM_PER_LINE*2;
    }

    if((TxtBuff.u32TxtReadSize*2)<u32TempLen)
    {
        u32TempLen=(TxtBuff.u32TxtReadSize*2);
    }

    u8Buf = (U8 *)(TxtBuff.u32TxtBuffPos);

#if TEXT_SHOW_BYLENGTH
    if(!TEXT_GetData((U8*)pu32TextBufPool, u8Buf, u32TempLen,bPreviw))
    {
        TEXT_DEBUG(printf("TEXT_GetData error!\n"));
    }
#else
    if(!TEXT_GetData((U8*)pu32TextBufPool, u8Buf, u32TempLen))
    {
        TEXT_DEBUG(printf("TEXT_GetData error!\n"));
    }
#endif
    return pu32TextBufPool;
}

BOOLEAN MApp_Text_CurPageReload(void)
{
    u32MemPos = 0;
    u32FilePos = GetTextPageOffset(u32PageIndex);
    TEXT_DEBUG(printf("u32FilePos = %lx\r\n", u32FilePos));
    TEXT_LoadBrowserText();
    return TRUE;
}

void MApp_Text_SetTextCharsetType(enumTextCharsetType enType)
{
    m_enTextCharsetType = enType;
}

enumTextCharsetType MApp_Text_GetTextCharsetType(void)
{
    return m_enTextCharsetType;
}

#endif  // #if ENABLE_MPLAYER_TEXT
#endif  //#if (ENABLE_DMP)

