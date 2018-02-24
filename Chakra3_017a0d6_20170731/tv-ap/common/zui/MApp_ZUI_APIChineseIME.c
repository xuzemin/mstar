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

#define MAPP_ZUI_APICHINESEIME_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#ifdef ENABLE_BT
#include "MApp_ZUI_APIChineseIME.h"
#include "MApp_ZUI_APIChineseIMELib.h"

/////////////////////////////////////////////////////////////////////////////////
//Example:  want to input "°¡"
//
//  step1.  input  'a'      display: < 0:a 1: ai  2: an  3: ang  4: ao >
//  step2.  choose  0       display: < 0: °¡   1:  °¢   2:  ß¹    3:  àÄ   4:  ëç   5:  ï¹>
//  step3.  choose  0       display:  °¡
//
/////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetPinYinInfoByFistChar
///  Mainly for ZUI OSD display.
///
///  NOTE:
///
///  @param [in]       c  U8  => input one char
///  @param [out]     pstart U8*  => the first position of these pinyin
///  @param [out]     pnumber U16*  => numbers of the group of pinyin
///
///  @return
///
///  @author MStarSemi @date 2008/11/27
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_GetPinYinInfoByFistChar(U8 c, U16 *pstart, U16 *pnumber)
{
    U8 i, ndx;

    *pstart = 0;
    if (c >= 'a' && c <= 'z')
    {
        ndx = c - 'a';
        *pnumber = PinYinNumber[ndx];
        for (i = 0; i < ndx; i ++)
        {
            *pstart += PinYinNumber[i];
        }
    }
    else
    {
        *pnumber = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetStringByFirstChar
///  Get one pinyin by index number.  Mainly for ZUI OSD display.
///
///  NOTE:
///
///  @param [in]       c  U8  => input one char
///  @param [in]     offset U16  => input pinyin index number
///  @param [out]     pstr U8*  => output one pinyin
///
///  @return
///
///  @author MStarSemi @date 2008/11/27
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_GetStringByFirstChar(U8 c, U16 offset, U8 *pstr)
{
    U16 start, number;
    U8 *ptr;

    MApp_ZUI_API_GetPinYinInfoByFistChar(c, &start, &number);
    if (offset < number)
    {
        ptr = PinYinArray[start +offset];
        while (*ptr != '\0')
        {
            *pstr = *ptr;
            pstr ++;
            ptr ++;
        }
        *pstr = 0;
    }
    else
    {
        *pstr = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_GetWordsInfoByFistChar
///  Mainly for ZUI OSD display.
///
///  NOTE:
///
///  @param [in]       c  U8  => input one char
///  @param [in]     offset U16  => input pinyin index number
///  @param [out]     pstart U16*  => the first position of the words. They have the same pinyin.
///  @param [out]     pnumber U16*  => numbers of the group of words.
///
///  @return
///
///  @author MStarSemi @date 2008/11/27
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_API_GetWordsInfoByFistChar(U8 c, U16 offset, U16 *pstart, U16 *pnumber)
{
    U16 i, start0, number0;

    MApp_ZUI_API_GetPinYinInfoByFistChar(c, &start0, &number0);
    *pstart = 0;
    if (offset < number0)
    {
        start0 += offset;
        *pnumber = WordsNumber[start0];
        for (i = 0; i < start0; i ++)
        {
            *pstart += WordsNumber[i];
        }
    }
    else
    {
        *pnumber = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  GetStringByFirstChar
///  Mainly for ZUI OSD display.
///
///  NOTE:
///
///  @param [in]       c  U8  => input one char
///  @param [in]     offset U16  => input pinyin index number
///  @param [in]     wofs U16  => input one word's index
///
///  @return one word's unicode
///
///  @author MStarSemi @date 2008/11/27
///////////////////////////////////////////////////////////////////////////////
U16 MApp_ZUI_API_GetWordsByPinYin(char c, U16 offset, U16 wofs)
{
    U16 start, number;

    MApp_ZUI_API_GetWordsInfoByFistChar(c, offset, &start, &number);
    if (number != 0 && wofs < number)
    {
        return WordsUnicode[start + wofs];
    }
    else
    {
        return 0;
    }
}

#endif

#undef MAPP_ZUI_APISTRINGS_C
