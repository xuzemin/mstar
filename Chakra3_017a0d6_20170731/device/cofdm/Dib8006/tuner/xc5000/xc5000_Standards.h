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
// Copyright (c) 2009, Xceive Corporation <info@xceive.com>
//
// Permission to use, copy, and/or modify this software, only with Xceive ICs,
// for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all source code
// copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
//
// Automatically generated C header file for
// control of the XC5000 via the i2c interface.
//
// Filename : xc5000_Standards.h
// Generated : 1/13/2010 10:38:31 AM
// Firmware version : f.f
//
// (c) 2010, Xceive Corporation
//

#ifndef __XC5000_STANDARDS_H
#define __XC5000_STANDARDS_H


// ************************************************************
// *** Standard with Video/Audio Setting
// ************************************************************

#define MAX_TV_STANDARD   50

XC_TV_STANDARD XC5000_Standard[MAX_TV_STANDARD] = {
/*  0 */ { "M/N-NTSC/PAL-BTSC-IF"      , 0x0400 , 0x8020,},
 { "M/N-NTSC/PAL-A2-IF"        , 0x0600 , 0x8020,},
 { "M/N-NTSC/PAL-EIAJ"         , 0x0400 , 0x8000,},
 { "M/N-NTSC/PAL-MTS"          , 0x0478 , 0x8020,},
 { "M/N-NTSC/PAL-A2-MONO"      , 0x0478 , 0x8000,},
 { "I-PAL-NICAM"               , 0x1080 , 0x8009,},
 { "B/G-PAL-NICAM#A"           , 0x0C04 , 0x8059,},
 { "B/G-PAL-A2#B"              , 0x0A00 , 0x8079,},
 { "B/G-PAL-A2#A"              , 0x0A00 , 0x8059,},
 { "B/G-PAL-NICAM#B"           , 0x0C04 , 0x8079,},
/* 10 */ { "L-SECAM-NICAM"             , 0x8E82 , 0x0009,},
 { "L-SECAM-AM"                , 0xB508 , 0x0009,},
 { "L'-SECAM-NICAM"            , 0x8E82 , 0x4009,},
 { "L'-SECAM-AM"               , 0xB508 , 0x4009,},
 { "D/K-PAL-A2"                , 0x1600 , 0x8009,},
 { "D/K-PAL-FM-ONLY"           , 0x1408 , 0x8009,},
 { "D/K-PAL-NICAM"             , 0x0E80 , 0x8009,},
 { "D/K-SECAM-A2 DK1"          , 0x1200 , 0x8009,},
 { "D/K-SECAM-A2 L/DK3"        , 0x0E84 , 0x8009,},
 { "FM RADIO-INPUT2"           , 0x0208 , 0x9802,},
/* 20 */ { "FM RADIO-INPUT1"           , 0x0208 , 0x9002,},
 { "DTV6-ATSC-LG-6_0MHZ"       , 0x00C0 , 0x8002,},
 { "DTV6-ATSC-ATI-6_38MHZ"     , 0x00C0 , 0x8002,},
 { "DTV6-ATSC-SAMSUNG-5_38MHZ" , 0x00C0 , 0x8002,},
 { "DTV6-ATSC-OREN-5_38MHZ"    , 0x00C0 , 0x8002,},
 { "DTV6-ATSC-OREN-3_6MHZ"     , 0x00C0 , 0x8002,},
 { "DTV6-ATSC-TOYOTA-3_88MHZ"  , 0x00C0 , 0x8002,},
 { "DTV6-ATSC-TOYOTA-7_94MHZ"  , 0x00C0 , 0x8002,},
 { "DTV6-QAM-6_0MHZ"           , 0x00C0 , 0x8002,},
 { "DTV8-DIBCOM-5_2MHZ"        , 0x00C0 , 0x800B,},
/* 30 */ { "DTV78-DIBCOM-5_2MHZ"       , 0x00C0 , 0x801B,},
 { "DTV7-DIBCOM-5_2MHZ"        , 0x00C0 , 0x8007,},
 { "DTV6-XCEIVE-4_56MHZ"       , 0x00C0 , 0x8002,},
 { "DTV8-XCEIVE-4_56MHZ"       , 0x00C0 , 0x800B,},
 { "DTV78-XCEIVE-4_56MHZ"      , 0x00C0 , 0x801B,},
 { "DTV7-XCEIVE-4_56MHZ"       , 0x00C0 , 0x8007,},
 { "DTV8-CHINA-TEMPORARY"      , 0x00C0 , 0x800B,},
 { "I-PAL-NICAM-MONO"          , 0x0E78 , 0x8009,},
 { "B/G-PAL-NICAM#A-MONO"      , 0x0878 , 0x8059,},
 { "B/G-PAL-A2#B-MONO"         , 0x0878 , 0x8079,},
/* 40 */ { "B/G-PAL-A2#A-MONO"         , 0x0878 , 0x8059,},
 { "B/G-PAL-NICAM#B-MONO"      , 0x0878 , 0x8079,},
 { "D/K-PAL-A2-MONO"           , 0x1478 , 0x8009,},
 { "D/K-PAL-MONO"              , 0x1478 , 0x8009,},
 { "D/K-PAL-NICAM-MONO"        , 0x1478 , 0x8009,},
 { "D/K-SECAM-A2 DK1-MONO"     , 0x1478 , 0x8009,},
 { "D/K-SECAM-A2 L/DK3-MONO"   , 0x1478 , 0x8009,},
 { "DVBT-FUJITSU - LOW IF 4.063MHZ" , 0x00C0, 0x8003,},
 { "ISDB-T-TOSHIBA - LOW IF 4.063MHZ" , 0x00C0, 0x8003, },
 { "MSTAR-4_56MHZ"             , 0x00C0, 0x8003, },
 };

#endif

