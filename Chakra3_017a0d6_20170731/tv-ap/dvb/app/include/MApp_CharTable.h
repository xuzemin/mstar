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

#ifndef MAPP_CHAR_TABLE_H
#define MAPP_CHAR_TABLE_H

/********************************************************************************/
/*                           Macro                                              */
/********************************************************************************/
#ifdef MAPP_CHAR_TABLE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif



#if( ENABLE_DMP && (MEMORY_MAP>=MMAP_64MB) )
    #define CHAR_TABLE_SUPPORT_KOREAN_CODE  1
#else
    #define CHAR_TABLE_SUPPORT_KOREAN_CODE  0
#endif

/********************************************************************************/
/*                           Enum                                               */
/********************************************************************************/
typedef enum
{
    ISO_6937 = 0x0,
    ISO_8859_01,
    ISO_8859_02,
    ISO_8859_03,
    ISO_8859_04,
    ISO_8859_05,
    ISO_8859_06,
    ISO_8859_07,
    ISO_8859_08,
    ISO_8859_09,
    ISO_8859_10,
    ISO_8859_11,
    ISO_8859_13,
    ISO_8859_14,
    ISO_8859_15,
    #if 0
    ISO_8859_16,
    #endif
    WINDOWS_DEFAULT = 0x40,
    WINDOWS_CP874,
    WINDOWS_CP1250,
    WINDOWS_CP1251,
    WINDOWS_CP1252,
    WINDOWS_CP1253,
    WINDOWS_CP1254,
    WINDOWS_CP1255,
    WINDOWS_CP1256,
    WINDOWS_CP1257,
    WINDOWS_CP1258,
    WINDOWS_CROATIAN_MAC,
    UNSUPPORT_CHAR_TABLE = 0xFF
} EN_CHARACTER_CODE_TABLE;

#define REMOVE_NONE             0x0000
#define REMOVE_00AD_SOFT_HYPHEN 0x0001

/********************************************************************************/
/*                           Function prototypes                                */
/********************************************************************************/
INTERFACE U16 MApp_CharTable_MappingDVBTextToUCS2(U8 *pu8Str, U16 *pu16Str, U16 srcByteLen, U16 dstWideCharLen, U16 filterCtrl);
INTERFACE U16 MApp_CharTable_MappingIsoToUCS2(EN_CHARACTER_CODE_TABLE enTable, U8 *pu8Str, U16 *pu16Str, U16 u16SrcLen, U16 u16DestLen);
#if ENABLE_DMP
#if(CHAR_TABLE_SUPPORT_KOREAN_CODE)
INTERFACE U16 MApp_CharTable_MappingKor2Unicode(U16 u16Korcode);
#endif
INTERFACE U16 MApp_Transfer2Unicode(U16 u16Code);
#endif
INTERFACE U16 MApp_CharTable_MappingCharToUCS2(EN_CHARACTER_CODE_TABLE enTable, U8 u8Str);

#undef INTERFACE
#endif  /*MAPP_CHAR_TABLE_H*/
