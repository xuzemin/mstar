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
#ifndef _TT_RENDER_PARAMS_H
#define _TT_RENDER_PARAMS_H

#ifndef TT_U8_TYPEDEF
#define TT_U8_TYPEDEF
typedef char TT_BOOL;
#endif

#ifndef TT_U16_TYPEDEF
#define TT_U16_TYPEDEF
typedef unsigned char TT_U8;
#endif

#ifndef TT_BOOL_TYPEDEF
#define TT_BOOL_TYPEDEF
typedef unsigned short TT_U16;
#endif

#ifndef TT_U32_TYPEDEF
#define TT_U32_TYPEDEF
typedef unsigned long TT_U32;
#endif

#include "TT_IFontCharsMan.h"

typedef enum
{
    TT_DSP_CHAR_ATTR_DOUBLE_HEIGHT_ZOOM  = 0x01,
    TT_DSP_CHAR_ATTR_UNDERLINE           = 0x02
}TT_Glyph_FLAGS;

#ifdef _MSC_VER
typedef struct
{
  TT_U8
    Row, Column;
  TT_U16
    Xpos, Ypos;
  TT_U8
    BgColour, FgColour;
  TT_U16
    Flags;
  TT_U8
    TT_ROM *pPixelData;
} TT_DRIVER_PARAMS;

#else

///The attribute of one glyph. This is only for internal usage.
typedef struct
{
    ///Which row and column
    TT_U8    Row, Column;
    ///The foreground color and background color
    TT_U8    BgColour, FgColour;
    ///More attribute for the glyph
    TT_Glyph_FLAGS   Flags;
    ///The desition width
    TT_U8    desWidth;
    ///The desition height
    TT_U8    desHeight;
    ///Should need to ignore this glyph?
    TT_U8    ignore;
    ///Reserved
    TT_U8    reserved4;
    ///Tell which font table ID it should take
    TT_Charset_Font    fontID;
    ///Which glyph in the font table
    TT_U8    glyphIndex;
    ///The flash mode of this glyphs
    TT_U8    flashMode;
    ///The reference display informations
        // bit 0..1: reserved
        // bit 2..3: the new Arabic font ID
        // bit 4..15: the new Arabic glyph index ,12 bits(0xExxx)
    TT_U16   refDisplayInfo;
    ///Reserved 
    TT_U32    reserved1;
    ///Reserved
    TT_U32    reserved2;
    ///Reserved
    TT_U32    reserved3;
} TT_DRIVER_PARAMS;

#endif

#endif

///*** please do not remove change list tag ***///
///***$Change: 465449 $***///
