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

#define _MAPP_TTS_CUS_C_

////////////////////////////////////////////////////////////////////////////////
/// @file MApp_TTSControlHandler.c
/// @author MStar Semiconductor Inc.
/// @brief Idle mode handler for APP layer
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/
#include "Board.h"

#if ENABLE_ATSC_TTS

//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

#include "debug.h"

#include "msAPI_Timer.h"
#include "msAPI_audio.h"

#include "msAPI_TTS_Sys.h"

#include "MApp_GlobalFunction.h"
#include "MApp_GlobalVar.h"
#include "MApp_IR.h"

#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"

#include "MApp_UiMenuFunc_ATSC.h"

// ZUI
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_ACTglobal.h"

extern void MApp_ZUI_API_ResetAllTimer(void);

#if(ENABLE_DMP)
extern void MApp_MPlayer_ResetPreviewTimer(void);
#endif

//==========================================================================
// Debug option

#define DEBUG_TTS_CUS(x)        //x

#define DEBUG_TTS_STR(x)        //x
#define DEBUG_TTS_ADD_STR(x)    //x
#define DEBUG_TTS_STR_SPLIT(x)  //x

#define DEBUG_TTS_CB(x)         //x

#define TTS_TEST_LONG_TEXT      0

//=========================================================================================

#define TTS_STRING_BUFFER_LENGTH    4096
#define TTS_STR_BUF_NUMBER          (16)

//#define TTS_ENABLE_SPLIT_STR    1

// One unicode convert to UTF8 1~3 Bytes,
#define TTS_CUS_SPLIT_STR_LEN       300//(TTS_TEXT_BUF_LEN*2/3)

#define TTS_TAG_SIZE_MAX            55

#define TTS_UNI_STR_MAX_LEN         1024

#define TTS_TMP_UNICODE_STR_LEN     (TTS_UNI_STR_MAX_LEN+TTS_TAG_SIZE_MAX)

//=========================================================================================

static U8 u8TextWriteNumber;
static U8 u8TextReadNumber;
static U8 g_TTS_au8TextBuffer[TTS_STRING_BUFFER_LENGTH];//main string buferr

typedef struct
{
    U16 u16StrStart;
    U16 u16StrLen;
}StuTtsStrInfo;
static StuTtsStrInfo g_TTS_astStrInfo[TTS_STR_BUF_NUMBER];

static BOOL g_TTS_Cus_bIsSupportedLang = FALSE;
static BOOL g_TTS_Cus_CurSysLang;

//=========================================================================================
// Internal function
void MApp_TTS_Cus_Reset_StringBuf(void);

#if ( TTS_TEST_LONG_TEXT )
void MApp_TTS_Cus_Test_LongText(void);
#endif

//==========================================================================

void MApp_TTS_CB_Init(void)
{
    DEBUG_TTS_CB(printf("%s()\n",__FUNCTION__););

    MApp_TTS_Cus_Reset_StringBuf();
}

void MApp_TTS_CB_BeforeDecode(void)
{
    DEBUG_TTS_CB(printf("%s()\n",__FUNCTION__););

    // Change language if need...
}

void MApp_TTS_CB_BeforeSay(void)
{
    DEBUG_TTS_CB(printf("%s()\n",__FUNCTION__););

    // Mute back ground if need...

    // Adjust back ground volume if need...
}

void MApp_TTS_CB_SayFinish(void)
{
    DEBUG_TTS_CB(printf("%s()\n",__FUNCTION__););

    // Adjust back ground volume if need...

    // UnMute back ground if need...

    MApp_TTS_Cus_Reset_StringBuf();
}

BOOLEAN MApp_TTS_CB_CheckIfUserBreak(void)
{
    // Get if user press key
    MApp_ProcessUserInput();

    if (u8KeyCode != KEY_NULL)
    {
        msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW);
        printf(" [TTS] User break!%s\n", ANSI_COLOR_OFF_STR );
        return TRUE;
    }

    return FALSE;
}

void MApp_TTS_CB_Set_MuteBGM(BOOLEAN bMuteBGM)
{
    DEBUG_TTS_CB( printf("MApp_TTS_Set_MuteBGM(bMuteBGM=%u)\n", bMuteBGM); );

    if(bMuteBGM)
    {
    #if TTS_MUTE_BGM
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_TTS_Background_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        //MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, GAME1_VOL, TRUE);
    #else
        //MApi_AUDIO_SetMixModeVolume(E_AUDIO_INFO_GAME_IN, GAME1_VOL, 0x20, 0);
    #endif
    }
    else
    {
    #if TTS_MUTE_BGM
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_TTS_Background_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        //MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, GAME1_VOL, FALSE);
    #else
        //MApi_AUDIO_SetMixModeVolume(E_AUDIO_INFO_GAME_IN, GAME1_VOL, u8DBVal, 0);
    #endif
    }
}

U8* MApp_TTS_Cus_Get_String_UTF8(U16* pu16BufSize)
{
    DEBUG_TTS_CB( printf("%s()\n",__FUNCTION__); );

    //printf("u8TextReadNumber=%u, u8TextWriteNumber=%u\n", u8TextReadNumber, u8TextWriteNumber);
    if( u8TextReadNumber >= u8TextWriteNumber )
    {
        return NULL;
    }

    U8* pu8Str = NULL;

    //pu8Str = (textBuffer+u8TextReadNumber*TTS_TEXT_BUF_LEN);
    //pu8Str = TTS_TEXT_BUF_STR_N(u8TextReadNumber);
    pu8Str = g_TTS_au8TextBuffer + g_TTS_astStrInfo[u8TextReadNumber].u16StrStart;

    //*pu16BufSize = TTS_TEXT_BUF_LEN; // todo: reifne
    *pu16BufSize = g_TTS_astStrInfo[u8TextReadNumber].u16StrLen; // todo: reifne

    u8TextReadNumber += 1;

    return pu8Str;
}

void MApp_TTS_Cus_Reset_StringBuf(void)
{
    u8TextWriteNumber = 0;
    u8TextReadNumber = 0;

    memset( g_TTS_au8TextBuffer, 0x0, sizeof(g_TTS_au8TextBuffer));

    memset( g_TTS_astStrInfo, 0x0, sizeof(g_TTS_astStrInfo));
}

long MApp_TTS_UNI_2_UTF8(U8 *pDest, const U16*pSrc, long destLen, long sourceLen)
{
   long i = 0;
   long size_d = 0;

    if (pSrc == NULL)
    {
        return 0;
    }

    while(i < sourceLen)
    {
        if( pSrc[i] == 0 )
        {
            if( pDest && (destLen>0) )
            {
                pDest[0] = 0;
            }
            break;
        }

       if(pSrc[i] < 0x80)
       {
           if(pDest)
           {
              if(destLen<1)
                  break;

              // Patch unsupport char
              if( pSrc[i] < 0x20 )
              {
                pDest[0] = ' ';
              }
              else
              {
                pDest[0] = (U8)pSrc[i];
              }

              destLen--;
              pDest++;
           }
           size_d++;
       }
      else  if(pSrc[i] < 0x800)
      {  //two byte  110x-xxxx 10xx-xxxx
           if(pDest)
           {
              if(destLen<2)
                  break;
              pDest[0] = (U8)((pSrc[i]>>6)&0x1F)|0xC0;
              pDest[1] = (U8)(pSrc[i]&0x3F)|0x80;
              destLen -= 2;
              pDest += 2;
           }
           size_d += 2;
      }
      else
      {  //three byte  1110-xxxx 10xx-xxxx 10xx-xxxx
           if(pDest)
           {
              if(destLen<3)
                  break;
              pDest[0] = (U8)((pSrc[i]>>12)&0x0F)|0xE0;
              pDest[1] = (U8)((pSrc[i]>>6)&0x3F)|0x80;
              pDest[2] = (U8)(pSrc[i]&0x3F)|0x80;
              destLen -= 3;
              pDest += 3;
           }
           size_d += 3;
      }
      i++;
   }

   return size_d;
}

U16 MApp_TTS_Cus_SplitLongText(U16* str, U16 u16MaxStrLen)
{
    if( str == NULL )
        return 0;

    U16 i;

    // First time, Find special char by lang
    if( g_TTS_Cus_CurSysLang == LANGUAGE_ENGLISH )
    {
        for( i = u16MaxStrLen - 2; i > 0; i -= 1 )
        {
            if( str[i] == '.' )
            {
                break;
            }
        }

        if( i > 0 )
            return (i+1);
    }

    // Find char ' '
    for( i = u16MaxStrLen - 2; i > 0; i -= 1 )
    {
        if( str[i] == 0x20 )
        {
            break;
        }
    }
    if( i > 0 )
        return (i+1);

    return (u16MaxStrLen - 1);
}

BOOLEAN MApp_TTS_Cus_AddUniStringToBuf(U16* pu16UniStr, U16 u16UniStrLen )
{
    DEBUG_TTS_ADD_STR( printf("AddUniStringToBuf(u16UniStrLen=%u)\n", u16UniStrLen); );

    if( u8TextWriteNumber >= TTS_STR_BUF_NUMBER )
    {
        printf("\nError: String buffer is full!\n");
        return FALSE;
    }

    //DEBUG_TTS_ADD_STR( printf("u16UniStrLen=%u\n", u16UniStrLen); );

    //memset( TTS_TEXT_BUF_STR_N(u8TextWriteNumber), 0x0, TTS_TEXT_BUF_LEN);

    if( u8TextWriteNumber > 0 )
        g_TTS_astStrInfo[u8TextWriteNumber].u16StrStart = g_TTS_astStrInfo[u8TextWriteNumber-1].u16StrStart + g_TTS_astStrInfo[u8TextWriteNumber-1].u16StrLen + 1;
    else
        g_TTS_astStrInfo[u8TextWriteNumber].u16StrStart = 0;

    U16 u16StrBufSpace = TTS_STRING_BUFFER_LENGTH - g_TTS_astStrInfo[u8TextWriteNumber].u16StrStart - 1;
    DEBUG_TTS_ADD_STR( printf("u16StrBufSpace=%u\n", u16StrBufSpace); );

    U16 u16UTFStrLen = MApp_TTS_UNI_2_UTF8( g_TTS_au8TextBuffer + g_TTS_astStrInfo[u8TextWriteNumber].u16StrStart, (U16*)pu16UniStr, u16StrBufSpace, u16UniStrLen);
    DEBUG_TTS_ADD_STR( printf("u16UTFStrLen=%u\n", u16UTFStrLen); );

    // Add 0 to str end
    g_TTS_au8TextBuffer[g_TTS_astStrInfo[u8TextWriteNumber].u16StrStart + u16UTFStrLen] = 0;

    g_TTS_astStrInfo[u8TextWriteNumber].u16StrLen = u16UTFStrLen;

    DEBUG_TTS_ADD_STR( printf(" => g_TTS_astStrInfo[%u].u16StrStart=%u\n", u8TextWriteNumber, g_TTS_astStrInfo[u8TextWriteNumber].u16StrStart); );
    DEBUG_TTS_ADD_STR( printf(" => g_TTS_astStrInfo[%u].u16StrLen=%u\n", u8TextWriteNumber, g_TTS_astStrInfo[u8TextWriteNumber].u16StrLen); );

    u8TextWriteNumber += 1;
    DEBUG_TTS_ADD_STR( printf(" => u8TextWriteNumber=%u\n", u8TextWriteNumber); );

    return TRUE;
}

void MApp_TTS_Cus_AddUniString(U16* pu16UniStr )
{
    DEBUG_TTS_ADD_STR( printf("MApp_TTS_Cus_AddUniString()\n"); );

    if( FALSE == MApp_TTS_Cus_Get_UserSetting_TTSOn() )
        return ;

    if( u8TextWriteNumber >= TTS_STR_BUF_NUMBER )
    {
        printf("\nError: String buffer is full!\n");
        return;
    }

    if( pu16UniStr == NULL )
    {
        return;
    }

    U16 u16UniStrLen = Str16_StrLen(pu16UniStr);
    if( u16UniStrLen == 0 )
        return;

    //DEBUG_TTS_STR( printf("MApp_TTS_Cus_AddUniString(): "); );
    DEBUG_TTS_STR( printf(" \033[42;30m "); );
    DEBUG_TTS_STR( Str16_PrintStr(pu16UniStr); );
    DEBUG_TTS_STR( printf("\033[0m\n"); );


    DEBUG_TTS_STR_SPLIT( printf("TTS_CUS_SPLIT_STR_LEN=%u\n", TTS_CUS_SPLIT_STR_LEN); );

    //U16 u16UTFStrLen;

    if( u16UniStrLen < TTS_CUS_SPLIT_STR_LEN )
    {
    #if 1
        MApp_TTS_Cus_AddUniStringToBuf(pu16UniStr, u16UniStrLen);
    #else
        memset( TTS_TEXT_BUF_STR_N(u8TextWriteNumber), 0x0, TTS_TEXT_BUF_LEN);

        u16UTFStrLen = MApp_TTS_UNI_2_UTF8( TTS_TEXT_BUF_STR_N(u8TextWriteNumber), (U16*)pu16UniStr, TTS_TEXT_BUF_LEN, u16UniStrLen);

        DEBUG_TTS_ADD_STR( printf("u16UTFStrLen=%u\n", u16UTFStrLen); );

        u8TextWriteNumber += 1;
        DEBUG_TTS_ADD_STR( printf("[TTS] 1 u8TextWriteNumber=%u\n", u8TextWriteNumber); );
    #endif
    }
    else // > TTS_TEXT_BUF_LEN
    {
        U16 u16RemainLen;
        U16 u16StrOffset = 0;
        U16 u16ShortStrLen;
        DEBUG_TTS_STR_SPLIT( U16 au16ShortStrTmp[TTS_CUS_SPLIT_STR_LEN+1]; );

        while( (u16StrOffset < u16UniStrLen) )
        {
            u16RemainLen = u16UniStrLen - u16StrOffset;
            DEBUG_TTS_STR_SPLIT( printf("u16StrOffset=%u, u16RemainLen=%u\n", u16StrOffset, u16RemainLen); );

            if( u16RemainLen >= TTS_CUS_SPLIT_STR_LEN ) // Need split str
            {
                u16ShortStrLen = MApp_TTS_Cus_SplitLongText((U16 *)(pu16UniStr+u16StrOffset), TTS_CUS_SPLIT_STR_LEN);
            }
            else
            {
                u16ShortStrLen = u16RemainLen;
            }
            DEBUG_TTS_STR_SPLIT( printf("u16ShortStrLen=%u\n", u16ShortStrLen); );

            DEBUG_TTS_STR_SPLIT( Str16_StrNCpy(au16ShortStrTmp, pu16UniStr+u16StrOffset, u16ShortStrLen+1); );
            DEBUG_TTS_STR_SPLIT( printf("\033[42;30m "); );
            DEBUG_TTS_STR_SPLIT( Str16_PrintStr(au16ShortStrTmp); );
            DEBUG_TTS_STR_SPLIT( printf("\033[0m \n"); );

        #if 1
            if( FALSE == MApp_TTS_Cus_AddUniStringToBuf(pu16UniStr+u16StrOffset, u16ShortStrLen) )
                break;

        #else
            memset( TTS_TEXT_BUF_STR_N(u8TextWriteNumber), 0x0, TTS_TEXT_BUF_LEN);

            u16UTFStrLen = MApp_TTS_UNI_2_UTF8( TTS_TEXT_BUF_STR_N(u8TextWriteNumber), (U16*)(pu16UniStr+u16StrOffset), TTS_TEXT_BUF_LEN, u16ShortStrLen);

            DEBUG_TTS_ADD_STR( printf("u16UTFStrLen=%u\n", u16UTFStrLen); );

            // Add 0 to str end
            *(TTS_TEXT_BUF_STR_N(u8TextWriteNumber) + u16UTFStrLen) = 0;

            u8TextWriteNumber += 1;

            DEBUG_TTS_ADD_STR( printf("[TTS] 2 u8TextWriteNumber=%u\n", u8TextWriteNumber); );
            if( u8TextWriteNumber >= TTS_STR_BUF_NUMBER )
            {
                break;
            }
        #endif

            u16StrOffset += u16ShortStrLen;
        }
    }

    //DEBUG_TTS_ADD_STR( printf("[TTS] 3 u8TextWriteNumber=%u\n", u8TextWriteNumber); );
}

void MApp_TTS_Cus_Add_UniStr_Format(U16* pu16UniStr, EN_TTS_SPEAK enSpeakFormat)
{
    U16 u16SrcStrLen = Str16_StrLen(pu16UniStr);
    if( u16SrcStrLen == 0 )
        return;

    if( u16SrcStrLen > (TTS_UNI_STR_MAX_LEN-1) )
    {
        u16SrcStrLen = (TTS_UNI_STR_MAX_LEN-1);
    }

    U16 u16StrBufTmp[TTS_TMP_UNICODE_STR_LEN];
    U16 u16StrBufTmpLen = 0;

    memset(u16StrBufTmp,0, sizeof(u16StrBufTmp));

    // Check if need add tag
    if( enSpeakFormat != EN_TTS_SPEAK_NORMAL )
    {
        U16 au16TagBuf[TTS_TAG_SIZE_MAX];

        // Copy Tag-Start to tmp buf
        Str16_StrU8toU16(au16TagBuf, (U8*)MApp_TTSControlSpeakFormatMapping(enSpeakFormat), TTS_TAG_SIZE_MAX);

        Str16_StrNCpy(u16StrBufTmp, au16TagBuf, TTS_TMP_UNICODE_STR_LEN);
        u16StrBufTmpLen = Str16_StrLen(u16StrBufTmp);

        // Copy original string  to tmp buf
        Str16_StrNCpy(u16StrBufTmp+u16StrBufTmpLen, pu16UniStr, TTS_TMP_UNICODE_STR_LEN);
        u16StrBufTmpLen = Str16_StrLen(u16StrBufTmp);

        // Copy Tag-End to tmp buf
        Str16_StrU8toU16(au16TagBuf, (U8*)TTS_SPEAK_TAG_END, TTS_TAG_SIZE_MAX);
        Str16_StrNCpy(u16StrBufTmp+u16StrBufTmpLen, au16TagBuf, TTS_TMP_UNICODE_STR_LEN);

        MApp_TTS_Cus_AddUniString(u16StrBufTmp);
    }
    else
    {
        // Copy src string to tmp string
        //Str16_StrNCpy(u16StrBufTmp, pu16UniStr, TTS_TMP_UNICODE_STR_LEN);

        MApp_TTS_Cus_AddUniString(pu16UniStr);
    }

    // Add ','
    //u16StrBufTmpLen = MApp_ZUI_API_Strlen(u16StrBufTmp);
    //u16StrBufTmp[u16StrBufTmpLen++] = (U16)',';

    //MApp_TTS_Cus_AddUniString(u16StrBufTmp);

}

void MApp_TTS_Cus_AddU8String(const U8* pu8Str)
{
    U16 au16U16String[TTS_TMP_UNICODE_STR_LEN];

    Str16_StrU8toU16(au16U16String, pu8Str, TTS_TMP_UNICODE_STR_LEN);

    MApp_TTS_Cus_AddUniString(au16U16String);
}

void MApp_TTS_Cus_Add_U8Str_Format(const U8* pu8Str, EN_TTS_SPEAK enSpeakFormat)
{
    U16 au16U16String[TTS_TMP_UNICODE_STR_LEN];

    Str16_StrU8toU16(au16U16String, pu8Str, TTS_TMP_UNICODE_STR_LEN);

    MApp_TTS_Cus_Add_UniStr_Format(au16U16String, enSpeakFormat);
}

void MApp_TTS_Cus_Add_Str_By_StrId(U16 u16StrID)
{
    //PRINT_CURRENT_LINE();
    DEBUG_TTS_CUS( printf("MApp_TTS_Cus_Add_Str_By_StrId(%d)\n", u16StrID); );

    // Get string ...
    U16* pu16SrcStr = MApp_ZUI_API_GetString(u16StrID);
    if( pu16SrcStr == NULL )
        return;

    U16 u16SrcStrLen = Str16_StrLen(pu16SrcStr);
    if( u16SrcStrLen == 0 )
        return;

    MApp_TTS_Cus_AddUniString(pu16SrcStr);
}

void MApp_TTS_Cus_Add_Str_By_HWndID(U16 u16HWndID, EN_TTS_SPEAK enSpeakFormat)
{
    //PRINT_CURRENT_LINE();
    DEBUG_TTS_CUS(printf("MApp_TTS_Cus_Add_Str_By_HWndID(u16HWndID=%u,enSpeakFormat=%u)\n", u16HWndID, enSpeakFormat); );

#if( TTS_TEST_LONG_TEXT )
    MApp_TTS_Cus_Test_LongText();
    return;
#endif

    U16* pu16SrcStr;

    pu16SrcStr = MApp_ZUI_ACT_GetDynamicText((HWND)u16HWndID);
    if( pu16SrcStr == NULL )
        return;
#if 1
    MApp_TTS_Cus_Add_UniStr_Format(pu16SrcStr, enSpeakFormat);
#else
    U16 u16SrcStrLen = Str16_StrLen(pu16SrcStr);
    if( u16SrcStrLen == 0 )
        return;

    if( u16SrcStrLen > (TTS_UNI_STR_MAX_LEN-1) )
    {
        u16SrcStrLen = (TTS_UNI_STR_MAX_LEN-1);
    }

    U16 u16StrBufTmp[TTS_TMP_UNICODE_STR_LEN];
    U16 u16StrBufTmpLen = 0;

    memset(u16StrBufTmp,0, sizeof(u16StrBufTmp));

    // Check if need add tag
    if( enSpeakFormat != EN_TTS_SPEAK_NORMAL )
    {
        U16 au16TagBuf[TTS_TAG_SIZE_MAX];

        // Copy Tag-Start to tmp buf
        Str16_StrU8toU16(au16TagBuf, (U8*)MApp_TTSControlSpeakFormatMapping(enSpeakFormat), TTS_TAG_SIZE_MAX);

        Str16_StrNCpy(u16StrBufTmp, au16TagBuf, TTS_TMP_UNICODE_STR_LEN);
        u16StrBufTmpLen = Str16_StrLen(u16StrBufTmp);

        // Copy original string  to tmp buf
        Str16_StrNCpy(u16StrBufTmp+u16StrBufTmpLen, pu16SrcStr, TTS_TMP_UNICODE_STR_LEN);
        u16StrBufTmpLen = Str16_StrLen(u16StrBufTmp);

        // Copy Tag-End to tmp buf
        Str16_StrU8toU16(au16TagBuf, (U8*)TTS_SPEAK_TAG_END, TTS_TAG_SIZE_MAX);
        Str16_StrNCpy(u16StrBufTmp+u16StrBufTmpLen, au16TagBuf, TTS_TMP_UNICODE_STR_LEN);
    }
    else
    {
        // Copy src string to tmp string
        Str16_StrNCpy(u16StrBufTmp, pu16SrcStr, TTS_TMP_UNICODE_STR_LEN);
    }

    // Add ','
    //u16StrBufTmpLen = MApp_ZUI_API_Strlen(u16StrBufTmp);
    //u16StrBufTmp[u16StrBufTmpLen++] = (U16)',';

    MApp_TTS_Cus_AddUniString(u16StrBufTmp);
#endif
}

//void MApp_TTSControlSetOn(BOOLEAN bEn)
void MApp_TTS_Cus_Say(void)
{
    DEBUG_TTS_CUS( printf("MApp_TTS_Cus_Say()\n"); );

    // Check option on/off
    if( ! MApp_TTS_Get_Enable() )
    {
        // Reset string buffer
        MApp_TTS_Cus_Reset_StringBuf();
        return;
    }

    // Check string buffer
    if( u8TextWriteNumber == 0 ) // No string
    {
        printf("No String!");
        return;
    }

    MApp_TTS_Say_Start();
}

BOOLEAN MApp_TTS_Cus_Get_UserSetting_TTSOn(void)
{
    if( FALSE == g_TTS_Cus_bIsSupportedLang )
        return FALSE;

    return stGenSetting.g_SysSetting.bTTSOn;
}

#if 0
EunMsTtsLangId MApp_TTS_Cus_ConvertSysLang2DriverLang(U16 u16SysLang)
{
    EunMsTtsLangId u8DriverLang = MB_TTS_LANG_NONE;

    switch (u16SysLang)
    {
        case LANGUAGE_ENGLISH:
            u8DriverLang = MB_TTS_LANG_ENGLISH;
            break;

    #if(ENABLE_TTS_LANG_ES_MX)
        case LANGUAGE_SPANISH:
            u8DriverLang = MB_TTS_LANG_SPANISH;
            break;
    #endif

    #if(ENABLE_TTS_LANG_FRANCH)
        case LANGUAGE_FRENCH:
            u8DriverLang = MB_TTS_LANG_FRANCH;
            break;
    #endif

    #if(ENABLE_TTS_LANG_KO)
        case LANGUAGE_KOREAN:
            u8DriverLang = MB_TTS_LANG_KOREAN;
            break;
    #endif

        default:
        case LANGUAGE_NONE:
            u8DriverLang = MB_TTS_LANG_NONE;
            break;
    }

    return u8DriverLang;
}
#endif

U8 MApp_TTS_Decide_TtsLang_BySysLang(U16 u16SysLangId, EunMsTtsLangId* peTtsLang1, EunMsTtsLangId* peTtsLang2)
{
    EunMsTtsLangId eTtsLangId_1st = MB_TTS_LANG_NONE;
    EunMsTtsLangId eTtsLangId_2nd = MB_TTS_LANG_NONE;


    switch (u16SysLangId)
    {
        case LANGUAGE_ENGLISH:
            eTtsLangId_1st = MB_TTS_LANG_ENGLISH;
            break;

    #if(ENABLE_TTS_LANG_ES_MX)
        case LANGUAGE_SPANISH:
            eTtsLangId_1st = MB_TTS_LANG_SPANISH;
            break;
    #endif

    #if(ENABLE_TTS_LANG_FRANCH)
        case LANGUAGE_FRENCH:
            eTtsLangId_1st = MB_TTS_LANG_FRANCH;
            break;
    #endif

    #if(ENABLE_TTS_LANG_KO)
        case LANGUAGE_KOREAN:
            eTtsLangId_1st = MB_TTS_LANG_KOREAN;
            break;
    #endif
    }

    *peTtsLang1 = eTtsLangId_1st;


#if( ENABLE_TTS_2ND_LANG )

  #if( MS_TTS_LIB_SEL == MS_TTS_LIB_EN_KR )
    if( u16SysLangId == LANGUAGE_KOREAN )
    {
        eTtsLangId_2nd = MB_TTS_LANG_ENGLISH;
    }
    else if( u16SysLangId == LANGUAGE_ENGLISH )
    {
        eTtsLangId_2nd = MB_TTS_LANG_KOREAN;
    }
  #endif

#endif

    if( peTtsLang2 )
    {
        *peTtsLang2 = eTtsLangId_2nd;
    }

    if( eTtsLangId_2nd != LANGUAGE_NONE )
        return 2;

    return 1;
}

void MApp_TTS_Cus_Init(U16 u16SysLangId)
{
    EunMsTtsLangId eTtsLangId_1st = MB_TTS_LANG_NONE;
    EunMsTtsLangId eTtsLangId_2nd = MB_TTS_LANG_NONE;

    // Test...
    //u16SysLangId = LANGUAGE_KOREAN;
    g_TTS_Cus_CurSysLang = u16SysLangId;

    // Decide tts lang
    MApp_TTS_Decide_TtsLang_BySysLang(u16SysLangId, &eTtsLangId_1st, &eTtsLangId_2nd);
    if( eTtsLangId_1st == MB_TTS_LANG_NONE )
    {
        eTtsLangId_1st = MB_TTS_LANG_ENGLISH;
        g_TTS_Cus_bIsSupportedLang = FALSE;
    }
    else
    {
        g_TTS_Cus_bIsSupportedLang = TRUE;
    }

    MApp_TTSControlHandler_Init(eTtsLangId_1st, eTtsLangId_2nd);

    MApp_UiMenuFunc_SetTTSVolume(stGenSetting.g_SysSetting.u8TTSVolume);
    MApp_UiMenuFunc_SetTTSPitch(stGenSetting.g_SysSetting.u8TTSPitch);
    MApp_UiMenuFunc_SetTTSSpeed(stGenSetting.g_SysSetting.u8TTSSpeed);
}

void MApp_TTS_Cus_Set_Lang(U16 u16SysLangId)
{
    EunMsTtsLangId eTtsLangId_1st = MB_TTS_LANG_NONE;
    EunMsTtsLangId eTtsLangId_2nd = MB_TTS_LANG_NONE;

    printf("MApp_TTS_Cus_Set_Lang(u16SysLangId=%u)\n", u16SysLangId);

    g_TTS_Cus_CurSysLang = u16SysLangId;

    // Decide tts lang
    MApp_TTS_Decide_TtsLang_BySysLang(u16SysLangId, &eTtsLangId_1st, &eTtsLangId_2nd);
    if( eTtsLangId_1st == MB_TTS_LANG_NONE )
    {
        printf("\nError: Unsupported u16SysLangId=%u\n", u16SysLangId);
        g_TTS_Cus_bIsSupportedLang = FALSE;
    }
    else
    {
        g_TTS_Cus_bIsSupportedLang = TRUE;
        MApp_TTSControlSetLanguage(eTtsLangId_1st, eTtsLangId_2nd);

        MApp_UiMenuFunc_SetTTSVolume(stGenSetting.g_SysSetting.u8TTSVolume);
        MApp_UiMenuFunc_SetTTSPitch(stGenSetting.g_SysSetting.u8TTSPitch);
        MApp_UiMenuFunc_SetTTSSpeed(stGenSetting.g_SysSetting.u8TTSSpeed);
    }
}

void MApp_TTS_Cus_Task(void)
{
    static U32 g_TTS_u32TTS_Cus_Task_LastTime = 0;

    if( msAPI_Timer_DiffTime_2(g_TTS_u32TTS_Cus_Task_LastTime, MsOS_GetSystemTime()) < 1000 )
        return;

    g_TTS_u32TTS_Cus_Task_LastTime = MsOS_GetSystemTime();

    MApp_ZUI_API_ResetAllTimer();

#if(ENABLE_DMP)
    // Reset MM timer
    if( IsStorageInUse() )
    {
        MApp_MPlayer_ResetPreviewTimer();
    }
#endif
}

//--------------------------------------------------------------------------------------------------

void MApp_TTS_Cus_AddU16StrAndWaitSayFinish(U16* pu16Str, BOOL bEnableUserBreak, U32 u32WaitTimeout)
{
    DEBUG_TTS_CUS( printf("MApp_TTS_Cus_AddU16StrAndWaitSayFinish()\n"); );

    if( FALSE == MApp_TTS_Get_Enable() )
    {
        return;
    }

    MApp_TTS_Cus_AddUniString(pu16Str);

    BOOLEAN bOriEnUserBreak = MApp_TTS_Get_EnableUserBreak();

    if( bEnableUserBreak != bOriEnUserBreak )
    {
        MApp_TTS_Set_EnableUserBreak(bEnableUserBreak);
    }

    MApp_TTS_Cus_Say();

    MApp_TTS_WaitSayFinish(u32WaitTimeout);

    if( bEnableUserBreak != bOriEnUserBreak )
    {
        MApp_TTS_Set_EnableUserBreak(bOriEnUserBreak);
    }
}

//--------------------------------------------------------------------------------------------------

#if( TTS_TEST_LONG_TEXT )
#if 0
U8 g_TTS_au8LongStr[] = {"Automatically adjusts the volume level when you change video sources or content so the level remains the same"};
#else
U8 g_TTS_au8LongStr[] = {
"All but one analog television system began as black-and-white systems.\
 Each country, faced with local political, technical, and economic issues, adopted a color television system which was grafted onto an existing monochrome system, using gaps in the video spectrum (explained below) to allow color transmission information to fit in the existing channels allotted.\
 The grafting of the color transmission standards onto existing monochrome systems permitted existing monochrome television receivers predating the changeover to color television to continue to be operated as monochrome television.\
 Because of this compatibility requirement, color standards added a second"};
#endif

void MApp_TTS_Cus_Test_LongText(void)
{
    PRINT_CURRENT_LINE();

    MApp_TTS_Cus_AddU8String(g_TTS_au8LongStr);
}

#endif // TTS_TEST_LONG_TEXT

//==============================================================================

#endif // ENABLE_ATSC_TTS

