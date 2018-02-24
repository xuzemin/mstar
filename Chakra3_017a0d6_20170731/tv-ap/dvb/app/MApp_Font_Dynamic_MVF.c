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

////////////////////////////////////////////////////////////////////////////////
//
/// @file MAPP_Font_Dynamic_MVF.h
/// This file includes MStar application interface for FONT.
/// @brief API for font handling
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
#define MAPP_FONT_DYNAMIC_MVF_C

// C Library
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "hwreg.h"

#if DYNAMIC_VECTOR_FONT_ENABLE
// Global Layer

// Driver Layer

// API Layer
#include "msAPI_OSD.h"
#include "msAPI_Timer.h"

// AP Layer
#include "MApp_Font.h"
#include "MApp_Font_Dynamic_MVF.h"



U16 gMVF_Unicode_Tbl[512];
U16 fontSize16=MS_DYNAMIC_FONTSIZE;
//U8 pMvfBuf[]={ 0xD9, 0x8F, 0x2f, 0x66, 0x4d, 0x00, 0x56, 0x00, 0x46, 0x00, 0x4b, 0x6d, 0xd5, 0x8b, 0x0b, 0x7a, 0x8f, 0x5e, 0x00, 0x00};
U8 pMvfBuf[]={0xD9, 0x8F, 0x2f, 0x66, 0x4d, 0x00, 0x56, 0x00, 0x46, 0x00, 0x4b, 0x6d, 0xd5, 0x8b, 0x0b, 0x7a, 0x8f, 0x5e, 0xD8, 0x98, 0x65, 0x67, 0x0, 0x4E, 0x35, 0x96, 0xE8, 0x96, 0x46, 0x00, 0x4b, 0x6d,
                        0x30, 0x00, 0x31, 0x00, 0x32, 0x00, 0x33, 0x00, 0xCF, 0x50, 0x76, 0x50, 0x2B, 0x4F,  0x4F, 0x46,  0x60,  0x4F,   0x5C,  0x50, 0x5F,  0x4E,  0x86, 0x4E,   0xBA, 0x4E,   0x1E, 0x4F,  0xd5, 0x8b, 0x0b, 0x7a, 0x8f, 0x5e, 0x00, 0x00};

void Dyx_MVF_LoadFont(U16 *pU16)
{
    U16 tableSize = 0, index=0, k, j;
    //U16 *pU16;
    //pU16 = (U16*)pMvfBuf;
    tableSize = 0;

    while(pU16[index])
    {
        for( k=0; k<tableSize; k++)
        {
            if(gMVF_Unicode_Tbl[k] >= pU16[index])
            {
                break;
            }
        }
        if(k==tableSize)
        {
            gMVF_Unicode_Tbl[tableSize++] =  pU16[index];
        }
        else if(gMVF_Unicode_Tbl[k] > pU16[index])
        {
            for(j= tableSize; j>k; j--)
                gMVF_Unicode_Tbl[j]= gMVF_Unicode_Tbl[j-1];
            gMVF_Unicode_Tbl[k] = pU16[index];
            tableSize++;
        }
        index++;
    }
    #if 0
    for( k=0; k<tableSize; k++)
    {
        printf("  [%x]  ",  gMVF_Unicode_Tbl[k]);
    }
    #endif

    printf("time 1: [%ld]    tableSize: [%d]\n", msAPI_Timer_GetTime0(), tableSize);
    if(msAPI_Dynamic_MVF_LoadFont((U16)FONT_DYNAMIC_MVF_EXT, fontSize16, MS_DYNAMIC_FONTOUTPUTSIZE, MS_DYNAMIC_FONTOUTPUTSIZE,  gMVF_Unicode_Tbl, tableSize))
    {
        msAPI_Font_Dynamic_MVF_StartGenerateBitmaps();
        msAPI_Font_Dynamic_MVF_EndGenerateBitmaps();
    }
    else
    {
        printf("Failed to load Font, return.\n");
        return;
    }

    printf("time 2: [%ld]\n", msAPI_Timer_GetTime0());

}

void TestDrawString(U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height, U32 u32TextColor)
{
    OSDClrBtn clrBtn1;

    clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;
    clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
    clrBtn1.Fontfmt.flag = GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP;
    clrBtn1.Fontfmt.ifont_gap = 2;
    clrBtn1.Fontfmt.width = MS_CHAR_WIDTHX2;
    clrBtn1.Fontfmt.height = MS_CHAR_HEIGHTX2;
    clrBtn1.u8Gradient = CONSTANT_COLOR;
    clrBtn1.radius = 5;
    clrBtn1.t_clr = u32TextColor;
    clrBtn1.fHighLight = FALSE;

    clrBtn1.x = u16X;
    clrBtn1.y = u16Y;
    clrBtn1.width = u16Width;
    clrBtn1.height = u16Height;
    clrBtn1.b_clr = COLOR_TRANSPARENT;//NEWUI_COLOR_TRANSPARENT;
    msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, pMvfBuf, &clrBtn1 );
}

void msAPI_MVF_LoadFont(void)
{
    printf("Dyx_MVF_LoadFont!\n");

    Dyx_MVF_LoadFont((U16*)pMvfBuf);
}

void msAPI_MVF_test(void)
{
    printf("MVF test!\n");

    TestDrawString(100, 200, 80, 80, COLOR_RED);

    fontSize16+=4;
    if(fontSize16 > 64)
        fontSize16 = 16;

}

#endif
