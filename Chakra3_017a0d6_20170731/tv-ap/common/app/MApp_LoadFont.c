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


#define MAPP_LOADFONT_C

#include <stdlib.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_MIU.h"
#include "msAPI_Font.h"
#include "msAPI_Timer.h"
#include "MApp_Font.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "BinInfo.h"
#include "Utl.h"
#if (ENABLE_ATSC)
#include "msAPI_cc_sysinfo.h"
#endif
#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#include "msAPI_cc_parser.h"
#endif


/*****************************************************************************/
/*                                 Global Variable                           */
/*****************************************************************************/

#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
static U8 CCFontNumber;
static U32 CCFontLoadTimer;
#elif (ENABLE_ATSC)
static U8 CCFontNumber;
static U32 CCFontLoadTimer;
#endif
/******************************************************************************/


//==============================================================================
/*                               Functions                                      */
//==============================================================================

void MApp_LoadFont_SetBMPFontInfo(LOADFONT_PAIR *fontpair, U8 u8num)
{
    U8 i = 0;

    for(;i<u8num;i++)
    {
        if(fontpair[i].FontID > MAX_FONTTABLE_NUM_OSD)
            break;//error

        Font[fontpair[i].FontID].fHandle = msAPI_Font_LoadFlashFontToSDRAM(fontpair[i].u16BinID);

        if ( Font[fontpair[i].FontID].fHandle != INVALID_FONTHANDLE )
        {
            FontHandleIndex[Font[fontpair[i].FontID].fHandle] = fontpair[i].FontID;
        }
    }

}

#if VECTOR_FONT_ENABLE
void MApp_LoadFont_SetVecFontInfo(LOADFONT_STRUCT* strfont, U8 u8Begin, U8 u8End)
{
    DEBUG_LOAD_VF(printf("MApp_LoadFont_SetVecFontInfo(u8Begin=%u, u8End=%u)\n", u8Begin, u8End););

    msAPI_Font_MVF_LoadFont(strfont, u8Begin, u8End);
}
#endif

/*************************************************************************************************************/
#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
void MApp_LoadFont_CC_Init(void)
{
    DEBUG_CC_FONT(printf("MApp_LoadFont_CC_Init()\n"););

    CCFontNumber    = 0;
    CCFontLoadTimer = msAPI_Timer_GetTime0();
    enCCFontStatus  = CC_FONT_UNLOAD;

    //msAPI_CC_SetCCFont(&Font_CC[0]);
}

BOOLEAN MApp_LoadFont_CC(void)
{
    DEBUG_CC_FONT(printf("MApp_LoadFont_CC()\n"););
    if(CCFontNumber >= MAX_FONTTABLE_NUM_CC)
    {
        return TRUE;
    }
    if(msAPI_Timer_DiffTimeFromNow(CCFontLoadTimer) < ((enCCFontStatus==CC_FONT_UNLOAD_SPEEDUP)? 10:100))
    {
        return FALSE;
    }
    Font_CC[CCFontNumber].fHandle = msAPI_Font_LoadFlashFontToSDRAM(CCFontNumber+BIN_ID_FONT_CS0);
        //printf("\n...load cc font, id=%d, fh=0x%x", CCFontNumber, Font_CC[CCFontNumber].fHandle);

    CCFontNumber++;

    CCFontLoadTimer=msAPI_Timer_GetTime0();

    return FALSE;
}

BOOLEAN MApp_LoadAll_Font_CC(void)
{
    DEBUG_CC_FONT(printf("MApp_LoadAll_Font_CC()\n"););

   U8 u8Count;

   for(u8Count=0;u8Count<MAX_FONTTABLE_NUM_CC;u8Count++)
   {
        //printf("Load CC font: %u %u at %u\n", CCFontNumber, CCFontNumber+BIN_ID_FONT_CS0, MsOS_GetSystemTime());

        Font_CC[CCFontNumber].fHandle = msAPI_Font_LoadFlashFontToSDRAM(CCFontNumber+BIN_ID_FONT_CS0);

        //printf("Done~ fHandle=%u at %u\n", Font_CC[CCFontNumber].fHandle, MsOS_GetSystemTime());

        //printf("\n...load cc font, id=%d, fh=0x%x", CCFontNumber, Font_CC[CCFontNumber].fHandle);

        CCFontNumber++;
   }

   return TRUE;
}

#elif( ATSC_CC == DTV_CC ) //(DTV_SYSTEM_SEL==DTV_SYSTEM_ATSC)
void MApp_LoadFont_CC_Init(void)
{
    DEBUG_CC_FONT(printf("MApp_LoadFont_CC_Init()\n"););

    CCFontNumber    = 0;
    CCFontLoadTimer = msAPI_Timer_GetTime0();
    enCCFontStatus  = CC_FONT_UNLOAD;

//    msAPI_CC_SetCCFont(&Font_CC[0]);
}

BOOLEAN MApp_LoadFont_CC(void)
{
    DEBUG_CC_FONT(printf("MApp_LoadFont_CC()\n"););

    if( CCFontNumber >= MAX_FONTTABLE_NUM_CC )
    {
        return TRUE;
    }

    if(msAPI_Timer_DiffTimeFromNow(CCFontLoadTimer) < ((enCCFontStatus==CC_FONT_UNLOAD_SPEEDUP)? 10:100))
    {
        return FALSE;
    }

    //printf("Load CC font: %u %u\n", CCFontNumber, CCFontNumber+BIN_ID_FONT_CS0);

    Font_CC[CCFontNumber].fHandle = msAPI_Font_LoadFlashFontToSDRAM(CCFontNumber+BIN_ID_FONT_CS0);
    //printf("\n...load cc font, id=%d, fh=0x%x", CCFontNumber, Font_CC[CCFontNumber].fHandle);

    CCFontNumber ++;

    CCFontLoadTimer = msAPI_Timer_GetTime0();

    return FALSE;
}

BOOLEAN MApp_LoadAll_Font_CC(void)
{
    DEBUG_CC_FONT(printf("MApp_LoadAll_Font_CC()\n"););
    U8 u8Count;

   //PRINT_CURRENT_LINE();

   for(u8Count=0;u8Count<MAX_FONTTABLE_NUM_CC;u8Count++)
   {
        //printf("Load CC font: %u %u at %u\n", CCFontNumber, CCFontNumber+BIN_ID_FONT_CS0, MsOS_GetSystemTime());

        Font_CC[CCFontNumber].fHandle = msAPI_Font_LoadFlashFontToSDRAM(CCFontNumber+BIN_ID_FONT_CS0);

        //printf("Done~ fHandle=%u at %u\n", Font_CC[CCFontNumber].fHandle, MsOS_GetSystemTime());

        //printf("\n...load cc font, id=%d, fh=0x%x", CCFontNumber, Font_CC[CCFontNumber].fHandle);

        CCFontNumber++;
   }

   return TRUE;
}

#endif

#undef MAPP_LOADFONT_C


