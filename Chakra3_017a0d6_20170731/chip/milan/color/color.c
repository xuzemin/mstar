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

#ifndef _COLOR_C_
#define _COLOR_C_

#include "datatype.h"
#include "msAPI_Mode.h"
//------------------------------------------------------------------------------
// sRGB Transform Matrix
//------------------------------------------------------------------------------
code short  tSRGB[3][3] =
{
    { 1096, -43, -28 }, // R  1.0694, -0.0424, -0.0270
    { - 21,   1063, -18 }, // G -0.0204,  1.0376, -0.0172
    { - 1,   34,   991 }  // B -0.0009,  0.0330,  0.9679


};
//------------------------------------------------------------------------------
// Color Correcttion Matrix
//------------------------------------------------------------------------------
// Smooth (X)
// R Array (0,0), G Array (0,0), B Array (0,0)
// R Adj. (0), G Adj. (0), B Adj. (0)
code short  tDefaultColorCorrectionMatrix[] =
{
   0x03EA, 0x0035,-0x0020,-0x0003, 0x0420,-0x001D, 0x000A,-0x0043,
   0x0438,-0x034B, 0x0196,-0x068B, 0x03C9,-0x0439, 0x0032,-0x0004,
  -0x07EE, 0x04E7, 0x07CB,-0x04C3, 0x0404, 0x023B,-0x023E, 0x01D5,
  -0x0831, 0x0100,-0x0001, 0x0100,-0x0000, 0x0000, 0x0000, 0x0000,
};

// Smooth (X)
// R Array (0,0), G Array (0,0), B Array (0,0)
// R Adj. (0), G Adj. (0), B Adj. (0)
code short  tVideoColorCorrectionMatrix[] =
{
   0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
   0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
  -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
  -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

// Smooth (X)
// R Array (0,0), G Array (0,0), B Array (0,0)
// R Adj. (0), G Adj. (0), B Adj. (0)
code short  tHDTVColorCorrectionMatrix[] =
{
   0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
   0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
   -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
  -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

// Smooth (X)
// R Array (0,0), G Array (0,0), B Array (0,0)
// R Adj. (0), G Adj. (0), B Adj. (0)
code short  tSDTVColorCorrectionMatrix[] =
{
   0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
   0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
   -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
  -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

// Smooth (X)
// R Array (0,0), G Array (0,0), B Array (0,0)
// R Adj. (0), G Adj. (0), B Adj. (0)
code short  tATVColorCorrectionMatrix[] =
{
   0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
   0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
   -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
  -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

// Smooth (X)
// R Array (0,0), G Array (0,0), B Array (0,0)
// R Adj. (0), G Adj. (0), B Adj. (0)
code short  tSDYPbPrColorCorrectionMatrix[] =
{
   0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
   0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
   -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
  -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

// Smooth (X)
// R Array (0,0), G Array (0,0), B Array (0,0)
// R Adj. (0), G Adj. (0), B Adj. (0)
code short  tHDYPbPrColorCorrectionMatrix[] =
{
   0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
   0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
   -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
  -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

//------------------------------------------------------------------------------
// DLC Curve
//------------------------------------------------------------------------------
code U8     g_DLC_CURVE_Default_TBL[] =
//    { 0x07, 0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77, 0x87, 0x97, 0xA7, 0xB7, 0xC7, 0xD7, 0xE7, 0xF7 };
    { 0x06, 0x0A, 0x1A, 0x2D, 0x3E, 0x59, 0x6D, 0x7B, 0x8B, 0x9A, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
code U8     g_DLC_CURVE_00_TBL[] =
//    { 0x07, 0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77, 0x87, 0x97, 0xA7, 0xB7, 0xC7, 0xD7, 0xE7, 0xF7 };
    { 0x06, 0x13, 0x21, 0x32, 0x43, 0x56, 0x66, 0x76, 0x85, 0x95, 0xA4, 0xB5, 0xC5, 0xD8, 0xE8, 0xF8 };
code U8     g_DLC_CURVE_01_TBL[] =
//    { 0x06, 0x16, 0x26, 0x36, 0x47, 0x57, 0x67, 0x77, 0x87, 0x97, 0xA7, 0xB7, 0xC7, 0xD7, 0xE7, 0xF7 };
    { 0x04, 0x14, 0x2D, 0x43, 0x53, 0x61, 0x70, 0x7C, 0x8A, 0x98, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
#undef _COLOR_C_
#endif /* _COLOR_C_ */

