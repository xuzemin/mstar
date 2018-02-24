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


#ifdef __BIDI_TEXT__

#include "msAPI_MLE_text_arabic_priv.h"
#include "msAPI_MLE_text_util.h"
#include "msAPI_MLE_helper.h"
#include "msAPI_MLE_font_vector.h"

/* Convert table from 0x06 table to 0xFE table */
const Text_ArabicConvertTable_t _tTextArabicConvertTable[] =
{
   { 0x81 , TRUE  }, /* 0x06 0x22 => (PL) 0xFE 0x81 */
   { 0x83 , TRUE  }, /* 0x06 0x23 => (PL) 0xFE 0x83 */
   { 0x85 , TRUE  }, /* 0x06 0x24 => (PL) 0xFE 0x85 */
   { 0x87 , TRUE  }, /* 0x06 0x25 => (PL) 0xFE 0x87 */
   { 0x89 , FALSE }, /* 0x06 0x26 => (PL) 0xFE 0x89 */
   { 0x8D , TRUE  }, /* 0x06 0x27 => (PL) 0xFE 0x8D */
   { 0x8F , FALSE }, /* 0x06 0x28 => (PL) 0xFE 0x8F */
   { 0x93 , TRUE  }, /* 0x06 0x29 => (PL) 0xFE 0x93 */
   { 0x95 , FALSE }, /* 0x06 0x2A => (PL) 0xFE 0x95 */
   { 0x99 , FALSE }, /* 0x06 0x2B => (PL) 0xFE 0x99 */
   { 0x9D , FALSE }, /* 0x06 0x2C => (PL) 0xFE 0x9D */
   { 0xA1 , FALSE }, /* 0x06 0x2D => (PL) 0xFE 0xA1 */
   { 0xA5 , FALSE }, /* 0x06 0x2E => (PL) 0xFE 0xA5 */
   { 0xA9 , TRUE  }, /* 0x06 0x2F => (PL) 0xFE 0xA9 */
   { 0xAB , TRUE  }, /* 0x06 0x30 => (PL) 0xFE 0xAB */
   { 0xAD , TRUE  }, /* 0x06 0x31 => (PL) 0xFE 0xAD */
   { 0xAF , TRUE  }, /* 0x06 0x32 => (PL) 0xFE 0xAF */
   { 0xB1 , FALSE }, /* 0x06 0x33 => (PL) 0xFE 0xB1 */
   { 0xB5 , FALSE }, /* 0x06 0x34 => (PL) 0xFE 0xB5 */
   { 0xB9 , FALSE }, /* 0x06 0x35 => (PL) 0xFE 0xB9 */
   { 0xBD , FALSE }, /* 0x06 0x36 => (PL) 0xFE 0xBD */
   { 0xC1 , FALSE }, /* 0x06 0x37 => (PL) 0xFE 0xC1 */
   { 0xC5 , FALSE }, /* 0x06 0x38 => (PL) 0xFE 0xC5 */
   { 0xC9 , FALSE }, /* 0x06 0x39 => (PL) 0xFE 0xC9 */
   { 0xCD , FALSE }, /* 0x06 0x3A => (PL) 0xFE 0xCD */
   { 0x00 , FALSE }, /* 0x06 0x3B => RESERVED       */
   { 0x00 , FALSE }, /* 0x06 0x3C => RESERVED       */
   { 0x00 , FALSE }, /* 0x06 0x3D => RESERVED       */
   { 0x00 , FALSE }, /* 0x06 0x3E => RESERVED       */
   { 0x00 , FALSE }, /* 0x06 0x3F => RESERVED       */
   { 0x00 , FALSE }, /* 0x06 0x40 => UNUSED         */
   { 0xD1 , FALSE }, /* 0x06 0x41 => (PL) 0xFE 0xD1 */
   { 0xD5 , FALSE }, /* 0x06 0x42 => (PL) 0xFE 0xD5 */
   { 0xD9 , FALSE }, /* 0x06 0x43 => (PL) 0xFE 0xD9 */
   { 0xDD , FALSE }, /* 0x06 0x44 => (PL) 0xFE 0xDD */
   { 0xE1 , FALSE }, /* 0x06 0x45 => (PL) 0xFE 0xE1 */
   { 0xE5 , FALSE }, /* 0x06 0x46 => (PL) 0xFE 0xE5 */
   { 0xE9 , FALSE }, /* 0x06 0x47 => (PL) 0xFE 0xE9 */
   { 0xED , TRUE  }, /* 0x06 0x48 => (PL) 0xFE 0xED */
   { 0xEF , TRUE  }, /* 0x06 0x49 => (PL) 0xFE 0xEF */
   { 0xF1 , FALSE }  /* 0x06 0x4A => (PL) 0xFE 0xF1 */
};

/* Convert table from 0x06 table to 0xFB table */
const Text_ArabicConvertTable_t _tTextArabicConvertFontATable[] =
{
   { 0x50 , TRUE  }, /* 0x06 0x71 => (PL) 0xFB 0x50 */
   { 0x00 , FALSE }, /* 0x06 0x72 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x73 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x74 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x75 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x76 => RESERVED */
   { 0xDD , TRUE  }, /* 0x06 0x77 => (PL) 0xFB 0xDD */
   { 0x00 , FALSE }, /* 0x06 0x78 => RESERVED */
   { 0x66 , FALSE }, /* 0x06 0x79 => (PL) 0xFB 0x66 */
   { 0x5E , FALSE }, /* 0x06 0x7A => (PL) 0xFB 0x5E */
   { 0x52 , FALSE }, /* 0x06 0x7B => (PL) 0xFB 0x52 */
   { 0x00 , FALSE }, /* 0x06 0x7C => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x7D => RESERVED */
   { 0x56 , FALSE }, /* 0x06 0x7E => (PL) 0xFB 0x56 */
   { 0x62 , FALSE }, /* 0x06 0x7F => (PL) 0xFB 0x62 */
   { 0x5A , FALSE }, /* 0x06 0x80 => (PL) 0xFB 0x5A */
   { 0x00 , TRUE  }, /* 0x06 0x81 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x82 => RESERVED */
   { 0x76 , FALSE }, /* 0x06 0x83 => (PL) 0xFB 0x76 */
   { 0x72 , FALSE }, /* 0x06 0x84 => (PL) 0xFB 0x72 */
   { 0x00 , FALSE }, /* 0x06 0x85 => RESERVED */
   { 0x7A , FALSE }, /* 0x06 0x86 => (PL) 0xFB 0x7A */
   { 0x7E , FALSE }, /* 0x06 0x87 => (PL) 0xFB 0x7E */
   { 0x88 , TRUE  }, /* 0x06 0x88 => (PL) 0xFB 0x88 */
   { 0x00 , FALSE }, /* 0x06 0x89 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x8A => RESERVED       */
   { 0x00 , FALSE }, /* 0x06 0x8B => RESERVED       */
   { 0x84 , TRUE  }, /* 0x06 0x8C => (PL) 0xFB 0x84 */
   { 0x82 , TRUE  }, /* 0x06 0x8D => (PL) 0xFB 0x82 */
   { 0x86 , TRUE  }, /* 0x06 0x8E => (PL) 0xFB 0x86 */
   { 0x00 , FALSE }, /* 0x06 0x8F => RESERVED       */
   { 0x00 , FALSE }, /* 0x06 0x90 => RESERVED */
   { 0x8C , TRUE  }, /* 0x06 0x91 => (PL) 0xFB 0x8C */
   { 0x00 , FALSE }, /* 0x06 0x92 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x93 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x94 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x95 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x96 => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0x97 => RESERVED */
   { 0x8A , TRUE  }, /* 0x06 0x98 => (PL) 0xFB 0x8A */
   { 0x00 , FALSE }, /* 0x06 0x99 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x9A => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x9B => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x9C => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0x9D => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0x9E => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0x9F => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xA0 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xA1 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xA2 => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0xA3 => RESERVED */
   { 0x6A , FALSE }, /* 0x06 0xA4 => (PL) 0xFB 0x6A */
   { 0x00 , FALSE }, /* 0x06 0xA5 => RESERVED */
   { 0x6E , FALSE }, /* 0x06 0xA6 => (PL) 0xFB 0x6E */
   { 0x00 , TRUE  }, /* 0x06 0xA7 => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0xA8 => RESERVED */
   { 0x8E , FALSE }, /* 0x06 0xA9 => (PL) 0xFB 0x8E */
   { 0x00 , FALSE }, /* 0x06 0xAA => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xAB => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0xAC => RESERVED */
   { 0xD3 , FALSE }, /* 0x06 0xAD => (PL) 0xFB 0xD3 */
   { 0x00 , FALSE }, /* 0x06 0xAE => RESERVED */
   { 0x92 , FALSE }, /* 0x06 0xAF => (PL) 0xFB 0x92 */
   { 0x00 , FALSE }, /* 0x06 0xB0 => RESERVED */
   { 0x9A , FALSE }, /* 0x06 0xB1 => (PL) 0xFB 0x9A */
   { 0x00 , FALSE }, /* 0x06 0xB2 => RESERVED */
   { 0x96 , FALSE }, /* 0x06 0xB3 => (PL) 0xFB 0x96 */
   { 0x00 , FALSE }, /* 0x06 0xB4 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xB5 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xB6 => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0xB7 => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0xB8 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xB9 => RESERVED */
   { 0x9E , TRUE  }, /* 0x06 0xBA => (PL) 0xFB 0x9E */
   { 0xA0 , FALSE }, /* 0x06 0xBB => (PL) 0xFB 0xA0 */
   { 0x00 , FALSE }, /* 0x06 0xBC => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xBD => RESERVED */
   { 0xAA , FALSE }, /* 0x06 0xBE => (PL) 0xFB 0xAA */
   { 0x00 , TRUE  }, /* 0x06 0xBF => RESERVED */
   { 0xA4 , TRUE  }, /* 0x06 0xC0 => (PL) 0xFB 0xA4 */
   { 0xA6 , FALSE }, /* 0x06 0xC1 => (PL) 0xFB 0xA6 */
   { 0x00 , FALSE }, /* 0x06 0xC2 => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xC3 => RESERVED */
   { 0x00 , TRUE  }, /* 0x06 0xC4 => RESERVED */
   { 0xE0 , TRUE  }, /* 0x06 0xC5 => (PL) 0xFB 0xE0 */
   { 0xD9 , TRUE  }, /* 0x06 0xC6 => (PL) 0xFB 0xD9 */
   { 0xD7 , TRUE  }, /* 0x06 0xC7 => (PL) 0xFB 0xD7 */
   { 0xDB , TRUE  }, /* 0x06 0xC8 => (PL) 0xFB 0xDB */
   { 0xE2 , TRUE  }, /* 0x06 0xC9 => (PL) 0xFB 0xE2 */
   { 0x00 , TRUE  }, /* 0x06 0xCA => RESERVED */
   { 0xDE , TRUE  }, /* 0x06 0xCB => (PL) 0xFB 0xDE */
   { 0xFC , FALSE }, /* 0x06 0xCC => (PL) 0xFB 0xFC */
   { 0x00 , TRUE  }, /* 0x06 0xCD => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xCE => RESERVED */
   { 0x00 , FALSE }, /* 0x06 0xCF => RESERVED */
   { 0xE4 , FALSE }, /* 0x06 0xD0 => (PL) 0xFB 0xE4 */
   { 0x00 , FALSE }, /* 0x06 0xD1 => RESERVED */
   { 0xAE , TRUE  }, /* 0x06 0xD2 => (PL) 0xFB 0xAE */
   { 0xB0 , TRUE  }  /* 0x06 0xD3 => (PL) 0xFB 0xB0 */
};

/* Convert table from 0xFE table to 0x06 table */
const Text_FEArabicConvertTable_t _tTextFEArabicConvertTable[] =
{
    { 0x22, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x81 => (PL) 0x06 0x22 */
    { 0x22, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x82 => (PL) 0x06 0x22 */
    { 0x23, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x83 => (PL) 0x06 0x22 */
    { 0x23, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x84 => (PL) 0x06 0x22 */
    { 0x24, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x85 => (PL) 0x06 0x22 */
    { 0x24, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x86 => (PL) 0x06 0x22 */
    { 0x25, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x87 => (PL) 0x06 0x22 */
    { 0x25, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x88 => (PL) 0x06 0x22 */
    { 0x26, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x89 => (PL) 0x06 0x22 */
    { 0x26, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x8a => (PL) 0x06 0x22 */
    { 0x26, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0x8b => (PL) 0x06 0x22 */
    { 0x26, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0x8c => (PL) 0x06 0x22 */
    { 0x27, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x8d => (PL) 0x06 0x22 */
    { 0x27, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x8e => (PL) 0x06 0x22 */
    { 0x28, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x8f => (PL) 0x06 0x22 */
    { 0x28, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x90 => (PL) 0x06 0x22 */
    { 0x28, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0x91 => (PL) 0x06 0x22 */
    { 0x28, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0x92 => (PL) 0x06 0x22 */
    { 0x29, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x93 => (PL) 0x06 0x22 */
    { 0x29, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x94 => (PL) 0x06 0x22 */
    { 0x2a, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x95 => (PL) 0x06 0x22 */
    { 0x2a, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x96 => (PL) 0x06 0x22 */
    { 0x2a, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0x97 => (PL) 0x06 0x22 */
    { 0x2a, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0x98 => (PL) 0x06 0x22 */
    { 0x2b, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x99 => (PL) 0x06 0x22 */
    { 0x2b, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x9a => (PL) 0x06 0x22 */
    { 0x2b, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0x9b => (PL) 0x06 0x22 */
    { 0x2b, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0x9c => (PL) 0x06 0x22 */
    { 0x2c, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0x9d => (PL) 0x06 0x22 */
    { 0x2c, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0x9e => (PL) 0x06 0x22 */
    { 0x2c, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0x9f => (PL) 0x06 0x22 */
    { 0x2c, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xa0 => (PL) 0x06 0x22 */
    { 0x2d, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xa1 => (PL) 0x06 0x22 */
    { 0x2d, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xa2 => (PL) 0x06 0x22 */
    { 0x2d, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xa3 => (PL) 0x06 0x22 */
    { 0x2d, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xa4 => (PL) 0x06 0x22 */
    { 0x2e, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xa5 => (PL) 0x06 0x22 */
    { 0x2e, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xa6 => (PL) 0x06 0x22 */
    { 0x2e, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xa7 => (PL) 0x06 0x22 */
    { 0x2e, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xa8 => (PL) 0x06 0x22 */
    { 0x2f, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xa9 => (PL) 0x06 0x22 */
    { 0x2f, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xaa => (PL) 0x06 0x22 */
    { 0x30, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xab => (PL) 0x06 0x22 */
    { 0x30, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xac => (PL) 0x06 0x22 */
    { 0x31, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xad => (PL) 0x06 0x22 */
    { 0x31, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xae => (PL) 0x06 0x22 */
    { 0x32, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xaf => (PL) 0x06 0x22 */
    { 0x32, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xb0 => (PL) 0x06 0x22 */
    { 0x33, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xb1 => (PL) 0x06 0x22 */
    { 0x33, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xb2 => (PL) 0x06 0x22 */
    { 0x33, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xb3 => (PL) 0x06 0x22 */
    { 0x33, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xb4 => (PL) 0x06 0x22 */
    { 0x34, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xb5 => (PL) 0x06 0x22 */
    { 0x34, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xb6 => (PL) 0x06 0x22 */
    { 0x34, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xb7 => (PL) 0x06 0x22 */
    { 0x34, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xb8 => (PL) 0x06 0x22 */
    { 0x35, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xb9 => (PL) 0x06 0x22 */
    { 0x35, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xba => (PL) 0x06 0x22 */
    { 0x35, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xbb => (PL) 0x06 0x22 */
    { 0x35, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xbc => (PL) 0x06 0x22 */
    { 0x36, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xbd => (PL) 0x06 0x22 */
    { 0x36, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xbe => (PL) 0x06 0x22 */
    { 0x36, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xbf => (PL) 0x06 0x22 */
    { 0x36, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xc0 => (PL) 0x06 0x22 */
    { 0x37, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xc1 => (PL) 0x06 0x22 */
    { 0x37, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xc2 => (PL) 0x06 0x22 */
    { 0x37, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xc3 => (PL) 0x06 0x22 */
    { 0x37, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xc4 => (PL) 0x06 0x22 */
    { 0x38, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xc5 => (PL) 0x06 0x22 */
    { 0x38, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xc6 => (PL) 0x06 0x22 */
    { 0x38, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xc7 => (PL) 0x06 0x22 */
    { 0x38, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xc8 => (PL) 0x06 0x22 */
    { 0x39, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xc9 => (PL) 0x06 0x22 */
    { 0x39, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xca => (PL) 0x06 0x22 */
    { 0x39, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xcb => (PL) 0x06 0x22 */
    { 0x39, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xcc => (PL) 0x06 0x22 */
    { 0x3a, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xcd => (PL) 0x06 0x22 */
    { 0x3a, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xce => (PL) 0x06 0x22 */
    { 0x3a, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xcf => (PL) 0x06 0x22 */
    { 0x3a, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xd0 => (PL) 0x06 0x22 */
    { 0x41, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xd1 => (PL) 0x06 0x22 */
    { 0x41, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xd2 => (PL) 0x06 0x22 */
    { 0x41, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xd3 => (PL) 0x06 0x22 */
    { 0x41, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xd4 => (PL) 0x06 0x22 */
    { 0x42, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xd5 => (PL) 0x06 0x22 */
    { 0x42, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xd6 => (PL) 0x06 0x22 */
    { 0x42, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xd7 => (PL) 0x06 0x22 */
    { 0x42, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xd8 => (PL) 0x06 0x22 */
    { 0x43, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xd9 => (PL) 0x06 0x22 */
    { 0x43, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xda => (PL) 0x06 0x22 */
    { 0x43, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xdb => (PL) 0x06 0x22 */
    { 0x43, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xdc => (PL) 0x06 0x22 */
    { 0x44, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xdd => (PL) 0x06 0x22 */
    { 0x44, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xde => (PL) 0x06 0x22 */
    { 0x44, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xdf => (PL) 0x06 0x22 */
    { 0x44, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xe0 => (PL) 0x06 0x22 */
    { 0x45, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xe1 => (PL) 0x06 0x22 */
    { 0x45, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xe2 => (PL) 0x06 0x22 */
    { 0x45, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xe3 => (PL) 0x06 0x22 */
    { 0x45, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xe4 => (PL) 0x06 0x22 */
    { 0x46, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xe5 => (PL) 0x06 0x22 */
    { 0x46, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xe6 => (PL) 0x06 0x22 */
    { 0x46, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xe7 => (PL) 0x06 0x22 */
    { 0x46, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xe8 => (PL) 0x06 0x22 */
    { 0x47, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xe9 => (PL) 0x06 0x47 */
    { 0x47, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xea => (PL) 0x06 0x47 */
    { 0x47, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xeb => (PL) 0x06 0x47 */
    { 0x47, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xec => (PL) 0x06 0x47 */
    { 0x48, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xed => (PL) 0x06 0x48 */
    { 0x48, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xee => (PL) 0x06 0x48 */
    { 0x49, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xef => (PL) 0x06 0x49 */
    { 0x49, TEXT_ARABIC_PM_POSITION }, /* 0xFE 0xf0 => (PL) 0x06 0x49 */
    { 0x4a, TEXT_ARABIC_PL_POSITION }, /* 0xFE 0xf1 => (PL) 0x06 0x4a */
    { 0x4a, TEXT_ARABIC_PF_POSITION }, /* 0xFE 0xf2 => (PL) 0x06 0x4a */
    { 0x4a, TEXT_ARABIC_PI_POSITION }, /* 0xFE 0xf3 => (PL) 0x06 0x4a */
    { 0x4a, TEXT_ARABIC_PM_POSITION }  /* 0xFE 0xf4 => (PL) 0x06 0x4a */
};

/* Convert table from 0xFB table to 0x06 table */
const Text_FEArabicConvertTable_t _tTextFBArabicConvertFontATable[] =
{
    { 0x71, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x50 => (PL) 0x06 0x22 */
    { 0x71, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x51 => (PL) 0x06 0x22 */ 
    { 0x7B, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x52 => (PL) 0x06 0x22 */
    { 0x7B, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x53 => (PL) 0x06 0x22 */ 
    { 0x7B, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x54 => (PL) 0x06 0x22 */
    { 0x7B, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x55 => (PL) 0x06 0x22 */ 
    { 0x7E, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x56 => (PL) 0x06 0x22 */
    { 0x7E, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x57 => (PL) 0x06 0x22 */ 
    { 0x7E, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x58 => (PL) 0x06 0x22 */
    { 0x7E, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x59 => (PL) 0x06 0x22 */ 
    { 0x80, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x5A => (PL) 0x06 0x22 */
    { 0x80, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x5B => (PL) 0x06 0x22 */ 
    { 0x80, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x5C => (PL) 0x06 0x22 */
    { 0x80, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x5D => (PL) 0x06 0x22 */ 
    { 0x7A, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x5E => (PL) 0x06 0x22 */
    { 0x7A, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x5F => (PL) 0x06 0x22 */ 
    { 0x7A, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x60 => (PL) 0x06 0x22 */
    { 0x7A, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x61 => (PL) 0x06 0x22 */ 
    { 0x7F, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x62 => (PL) 0x06 0x22 */
    { 0x7F, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x63 => (PL) 0x06 0x22 */ 
    { 0x7F, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x64 => (PL) 0x06 0x22 */
    { 0x7F, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x65 => (PL) 0x06 0x22 */ 
    { 0x79, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x66 => (PL) 0x06 0x22 */
    { 0x79, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x67 => (PL) 0x06 0x22 */ 
    { 0x79, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x68 => (PL) 0x06 0x22 */
    { 0x79, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x69 => (PL) 0x06 0x22 */ 
    { 0xA4, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x6A => (PL) 0x06 0x22 */
    { 0xA4, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x6B => (PL) 0x06 0x22 */ 
    { 0xA4, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x6C => (PL) 0x06 0x22 */
    { 0xA4, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x6D => (PL) 0x06 0x22 */ 
    { 0xA6, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x6E => (PL) 0x06 0x22 */
    { 0xA6, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x6F => (PL) 0x06 0x22 */ 
    { 0xA6, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x70 => (PL) 0x06 0x22 */
    { 0xA6, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x71 => (PL) 0x06 0x22 */ 
    { 0x84, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x72 => (PL) 0x06 0x22 */
    { 0x84, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x73 => (PL) 0x06 0x22 */ 
    { 0x84, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x74 => (PL) 0x06 0x22 */
    { 0x84, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x75 => (PL) 0x06 0x22 */ 
    { 0x83, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x76 => (PL) 0x06 0x22 */
    { 0x83, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x77 => (PL) 0x06 0x22 */ 
    { 0x83, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x78 => (PL) 0x06 0x22 */
    { 0x83, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x79 => (PL) 0x06 0x22 */ 
    { 0x86, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x7A => (PL) 0x06 0x22 */
    { 0x86, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x7B => (PL) 0x06 0x22 */ 
    { 0x86, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x7C => (PL) 0x06 0x22 */
    { 0x86, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x7D => (PL) 0x06 0x22 */ 
    { 0x87, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x7E => (PL) 0x06 0x22 */
    { 0x87, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x7F => (PL) 0x06 0x22 */
    { 0x87, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x80 => (PL) 0x06 0x22 */ 
    { 0x87, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x81 => (PL) 0x06 0x22 */
    { 0x8D, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x82 => (PL) 0x06 0x22 */ 
    { 0x8D, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x83 => (PL) 0x06 0x22 */
    { 0x8C, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x84 => (PL) 0x06 0x22 */ 
    { 0x8C, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x85 => (PL) 0x06 0x22 */
    { 0x8E, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x86 => (PL) 0x06 0x22 */ 
    { 0x8E, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x87 => (PL) 0x06 0x22 */
    { 0x88, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x88 => (PL) 0x06 0x22 */ 
    { 0x88, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x89 => (PL) 0x06 0x22 */
    { 0x98, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x8A => (PL) 0x06 0x22 */ 
    { 0x98, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x8B => (PL) 0x06 0x22 */
    { 0x91, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x8C => (PL) 0x06 0x22 */ 
    { 0x91, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x8D => (PL) 0x06 0x22 */
    { 0xA9, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x8E => (PL) 0x06 0x22 */ 
    { 0xA9, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x8F => (PL) 0x06 0x22 */
    { 0xA9, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x90 => (PL) 0x06 0x22 */ 
    { 0xA9, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x91 => (PL) 0x06 0x22 */
    { 0xAF, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x92 => (PL) 0x06 0x22 */ 
    { 0xAF, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x93 => (PL) 0x06 0x22 */
    { 0xAF, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x94 => (PL) 0x06 0x22 */ 
    { 0xAF, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x95 => (PL) 0x06 0x22 */
    { 0xB3, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x96 => (PL) 0x06 0x22 */ 
    { 0xB3, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x97 => (PL) 0x06 0x22 */
    { 0xB3, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x98 => (PL) 0x06 0x22 */ 
    { 0xB3, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x99 => (PL) 0x06 0x22 */
    { 0xB1, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x9A => (PL) 0x06 0x22 */ 
    { 0xB1, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x9B => (PL) 0x06 0x22 */
    { 0xB1, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0x9C => (PL) 0x06 0x22 */ 
    { 0xB1, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0x9D => (PL) 0x06 0x22 */
    { 0xBA, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0x9E => (PL) 0x06 0x22 */ 
    { 0xBA, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0x9F => (PL) 0x06 0x22 */
    { 0xBB, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xA0 => (PL) 0x06 0x22 */ 
    { 0xBB, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xA1 => (PL) 0x06 0x22 */
    { 0xBB, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0xA2 => (PL) 0x06 0x22 */ 
    { 0xBB, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0xA3 => (PL) 0x06 0x22 */
    { 0xC0, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xA4 => (PL) 0x06 0x22 */ 
    { 0xC0, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xA5 => (PL) 0x06 0x22 */
    { 0xC1, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xA6 => (PL) 0x06 0x22 */ 
    { 0xC1, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xA7 => (PL) 0x06 0x22 */
    { 0xC1, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0xA8 => (PL) 0x06 0x22 */ 
    { 0xC1, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0xA9 => (PL) 0x06 0x22 */
    { 0xBE, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xAA => (PL) 0x06 0x22 */ 
    { 0xBE, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xAB => (PL) 0x06 0x22 */
    { 0xBE, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0xAC => (PL) 0x06 0x22 */ 
    { 0xBE, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0xAD => (PL) 0x06 0x22 */
    { 0xD2, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xAE => (PL) 0x06 0x22 */ 
    { 0xD2, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xAF => (PL) 0x06 0x22 */
    { 0xD3, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB0 => (PL) 0x06 0x22 */ 
    { 0xD3, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xB1 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB2 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB3 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB4 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB5 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB6 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB7 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB8 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xB9 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xBA => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xBB => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xBC => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xBD => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xBE => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xBF => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC0 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC1 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC2 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC3 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC4 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC5 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC6 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC7 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC8 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xC9 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xCA => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xCB => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xCC => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xCD => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xCE => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xCF => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xD0 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xD1 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xD2 => (PL) 0x06 0x22 */
    { 0xAD, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xD3 => (PL) 0x06 0x22 */
    { 0xAD, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xD4 => (PL) 0x06 0x22 */ 
    { 0xAD, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0xD5 => (PL) 0x06 0x22 */
    { 0xAD, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0xD6 => (PL) 0x06 0x22 */ 
    { 0xC7, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xD7 => (PL) 0x06 0x22 */
    { 0xC7, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xD8 => (PL) 0x06 0x22 */ 
    { 0xC6, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xD9 => (PL) 0x06 0x22 */
    { 0xC6, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xDA => (PL) 0x06 0x22 */ 
    { 0xC8, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xDB => (PL) 0x06 0x22 */
    { 0xC8, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xDC => (PL) 0x06 0x22 */ 
    { 0x77, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xDD => (PL) 0x06 0x22 */
    { 0xCB, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xDE => (PL) 0x06 0x22 */ 
    { 0xCB, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xDF => (PL) 0x06 0x22 */
    { 0xC5, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xE0 => (PL) 0x06 0x22 */ 
    { 0xC5, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xE1 => (PL) 0x06 0x22 */
    { 0xC9, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xE2 => (PL) 0x06 0x22 */ 
    { 0xC9, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xE3 => (PL) 0x06 0x22 */
    { 0xD0, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xE4 => (PL) 0x06 0x22 */ 
    { 0xD0, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xE5 => (PL) 0x06 0x22 */
    { 0xD0, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0xE6 => (PL) 0x06 0x22 */ 
    { 0xD0, TEXT_ARABIC_PM_POSITION }, /* 0xFB 0xE7 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xE8 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xE9 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xEA => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xEB => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xEC => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xED => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xEF => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF0 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF1 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF2 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF3 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF4 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF5 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF6 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF7 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF8 => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xF9 => (PL) 0x06 0x22 */
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xFA => (PL) 0x06 0x22 */ 
    { 0x00, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xFB => (PL) 0x06 0x22 */
    { 0xCC, TEXT_ARABIC_PL_POSITION }, /* 0xFB 0xFC => (PL) 0x06 0x22 */ 
    { 0xCC, TEXT_ARABIC_PF_POSITION }, /* 0xFB 0xFD => (PL) 0x06 0x22 */
    { 0xCC, TEXT_ARABIC_PI_POSITION }, /* 0xFB 0xFE => (PL) 0x06 0x22 */ 
    { 0xCC, TEXT_ARABIC_PM_POSITION }  /* 0xFB 0xFF => (PL) 0x06 0x22 */
};

#define MLE_TEXT_ARABIC_CONVERT_LEN 6

U32 msAPI_MLE_TEXTUTIL_ConvertToArabicStr( MLE_WChar *pString, U32 nStrLen, BOOLEAN bDispStr )
{
    U32 nReturnLen = 0;

    if ( pString == NULL || nStrLen == 0 )
    {
        return 0;
    }

    if ( bDispStr )
    {
        msAPI_MLE_TEXTUTIL_UCS2Invert( pString, nStrLen, 0, nStrLen, NULL );
    }

    nReturnLen = _msAPI_MLE_TextArabicConvertToDisplay( pString, nStrLen );

    if ( bDispStr )
    {
        msAPI_MLE_TEXTUTIL_UCS2Invert( pString, nReturnLen, 0, nReturnLen, NULL );
    }

    return nReturnLen;
}

BOOLEAN msAPI_MLE_TEXTUTIL_ConvertToArabicFEStr( MLE_WChar *pString, U32 nStrLen, BOOLEAN bDispStr )
{
    BOOLEAN bReturn = FALSE;

    if ( pString == NULL || nStrLen == 0 )
    {
        return FALSE;
    }

    if ( bDispStr )
    {
        msAPI_MLE_TEXTUTIL_UCS2Invert( pString, nStrLen, 0, nStrLen, NULL );
    }

    bReturn = _msAPI_MLE_TextArabicConvertFEFormat( pString, nStrLen );

    if ( bDispStr )
    {
        msAPI_MLE_TEXTUTIL_UCS2Invert( pString, nStrLen, 0, nStrLen, NULL );
    }

    return bReturn;
}

U16 msAPI_MLE_TEXTUTIL_ConvertToArabicFEChar( const MLE_WChar *pString, U32 nStrLen, U32 nOffset, BOOLEAN bDispStr, U16 *pNextFEChar )
{
    U32 nStrIndex = 0;     /* string counter */
    BOOLEAN bInWord = FALSE; /* Indicates if counter is in a word */
    BOOLEAN bPreCharIsFirst = FALSE;  /* Indicates whether prec car in firts position */
    U16 nConverStr[MLE_TEXT_ARABIC_CONVERT_LEN] = {0,};
    U32 nStartOffset = 0;
    U32 nConverStrOffset = 0;
    U32 nConverStrLen = 0;
    U16 nConvertChar = 0;
    BOOLEAN bIsPreComposedChar = FALSE;

    if ( pString == NULL || nStrLen == 0 || nOffset >= nStrLen )
    {
        return 0;
    }

    nConvertChar = pString[nOffset];

    if ( msAPI_MLE_TEXTUTIL_IsArabicChar(pString[nOffset]) )
    {
        nStartOffset = (nOffset >= 1) ? (nOffset - 1) : 0;
        nConverStrLen = (nOffset + (MLE_TEXT_ARABIC_CONVERT_LEN - 1) < nStrLen) ? ((MLE_TEXT_ARABIC_CONVERT_LEN - 1) + (nOffset - nStartOffset)) : (nStrLen - nStartOffset);
        nConverStrOffset = nOffset - nStartOffset;

        memcpy( (void *)nConverStr, (void *)(pString + nStartOffset), nConverStrLen * sizeof(U16) );

        if ( bDispStr )
        {
            msAPI_MLE_TEXTUTIL_UCS2Invert( nConverStr, nConverStrLen, 0, nConverStrLen, NULL );
        }

        /* Convert to 0xFE format */
        while ( nStrIndex <= nConverStrLen )
        {
            if ( nStrIndex == 0 )
            {
                U16 nPreChar = 0;
                _msAPI_MLE_TextArabicConvertFEChar( &(nConverStr[nStrIndex]), &nPreChar, &bInWord, &bPreCharIsFirst );
            }
            else if ( nStrIndex == nConverStrLen )
            {
                U16 nLastChar = 0;
                _msAPI_MLE_TextArabicConvertFEChar( &nLastChar, &(nConverStr[nStrIndex - 1]), &bInWord, &bPreCharIsFirst );
            }
            else
            {
                if ( !TEXT_IS_ARABIC_COMPOSED_CHAR(pString[nStrIndex]) )
                {
                    if ( bIsPreComposedChar )
                    {
                        _msAPI_MLE_TextArabicConvertFEChar( &(nConverStr[nStrIndex]), &(nConverStr[nStrIndex - 2]), &bInWord, &bPreCharIsFirst );
                    }
                    else
                    {
                        _msAPI_MLE_TextArabicConvertFEChar( &(nConverStr[nStrIndex]), &(nConverStr[nStrIndex - 1]), &bInWord, &bPreCharIsFirst );
                    }
                    bIsPreComposedChar = FALSE;
                }
                else
                {
                    if ( bIsPreComposedChar )
                    {
                        bIsPreComposedChar = FALSE;
                        bPreCharIsFirst = FALSE;
                        bInWord = FALSE;
                    }
                    else
                    {
                        bIsPreComposedChar = TRUE;
                    }
                }
            }
            nStrIndex++;
        }

        if ( bDispStr )
        {
            msAPI_MLE_TEXTUTIL_UCS2Invert( nConverStr, nConverStrLen, 0, nConverStrLen, NULL );
        }

        nConvertChar = nConverStr[nConverStrOffset];
    }

    if ( pNextFEChar )
    {
        if ( nConverStrLen > 0 && nConverStrOffset < (nConverStrLen - 1) )
        {
            *pNextFEChar = nConverStr[nConverStrOffset + 1];
        }
    }

    return nConvertChar;
}

U32 msAPI_MLE_TEXTUTIL_NumConvertToArabicNum( MLE_WChar *pString, U32 nStrLen )
{
    U16 nDigit = 0;
    U32 i;

    if ( pString == NULL || nStrLen == 0 )
    {
        return 0;
    }

    for ( i = 0; i < nStrLen; i++ )
    {
        if ( msAPI_MLE_isdigit(pString[i]) )
        {
            nDigit = msAPI_MLE_isdigit(pString[i]) - (U16)'0';
            pString[i] = TEXT_SET_CHAR(TEXT_ARABIC_ROW, (nDigit + TEXT_ARABIC_INDIC_DIGIT_ZERO) );
        }
    }

    return nStrLen;
}

U32 msAPI_MLE_TEXTUTIL_ArabicNumConvertToNum( MLE_WChar *pString, U32 nStrLen )
{
    U32 i;

    if ( pString == NULL || nStrLen == 0 )
    {
        return 0;
    }

    for ( i = 0; i < nStrLen; i++ )
    {
        if ( TEXT_IS_ARABIC_DIGIT_CHAR(pString[i]) )
        {
            pString[i] = (pString[i] & 0x00FF) - (U16)TEXT_ARABIC_INDIC_DIGIT_ZERO + (U16)'0';
        }
    }

    return nStrLen;
}

BOOLEAN msAPI_MLE_TEXTUTIL_IsArabicText( const MLE_WChar *pString, U32 nStrLen )
{
    U32 nStrCpt = 0;

    while ( nStrCpt < nStrLen )
    {
        /* if current char is an arabic char then return true */
        if ( msAPI_MLE_TEXTUTIL_IsArabicChar(pString[nStrCpt]) )
        {
            return TRUE;
        }
        nStrCpt ++;
    }

    return FALSE;
}

BOOLEAN msAPI_MLE_TEXTUTIL_IsArabicChar( MLE_WChar nChar )
{
    BOOLEAN bReturn = FALSE;
#ifndef __BIDI_TEST__
    if ( TEXT_IS_ARABIC_ALPHA_CHAR(nChar) || TEXT_IS_ARABIC_DIGIT_CHAR(nChar) )
    {
        if(nChar == 0xFEFF || nChar == 0xFFFE) // check if the char is a byte order signature
        {
            bReturn = FALSE;
        }
        else
        {
            bReturn = TRUE;
        }
    }
#else
    if ( TEXT_GET_ROW(nChar) == 0 &&
         ((TEXT_GET_COL(nChar) >= 0x41 && TEXT_GET_COL(nChar) <= 0x5A) ||
          (TEXT_GET_COL(nChar) >= 0x36 && TEXT_GET_COL(nChar) <= 0x39)) )
    {
        bReturn = TRUE;
    }
#endif //__BIDI_TEST__

    return bReturn;
}

BOOLEAN msAPI_MLE_TEXTUTIL_ConcatenationArabicFEChar( MLE_WChar *pChar, MLE_WChar nNextChar )
{
    if ( pChar == NULL || nNextChar == 0 )
    {
        return FALSE;
    }

    // Concatenation
    return _msAPI_MLE_TextArabicFEConcatenationNextChar( pChar, nNextChar );
}

BOOLEAN msAPI_MLE_TEXTUTIL_IsArabicBreakChar( const MLE_WChar *pwStr, U32 u32StrLen, U32 u32Offset )
{
    BOOLEAN bReturnValue = FALSE;
    MLE_WChar wChar;
    if ( pwStr == NULL || u32StrLen == 0 || u32Offset >= u32StrLen )
    {
        return FALSE;
    }
    wChar = pwStr[u32Offset];
    if ( TEXT_GET_ROW(wChar) != TEXT_ARABIC_ROW )
    {
        return FALSE;
    }
    if ( (TEXT_IS_ARABIC_ALPHA_FONTB_TO_CONVERT(wChar) && TEXT_ARABIC_FORCE_END(TEXT_GET_COL(wChar))) || 
          (TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT(wChar) && TEXT_ARABIC_FONTA_FORCE_END(TEXT_GET_COL(wChar))) )
    {
        bReturnValue = TRUE;
    }
    else
    {
        BOOLEAN bInWord = FALSE; 
        BOOLEAN bPreCharIsFirst = FALSE;
        U32 u32StartAt;
        U32 i;
        BOOLEAN bPreCharInWord = FALSE;
        u32StartAt = (u32Offset > 1) ? (u32Offset - 2) : 0;
        for ( i = u32StartAt; i < (u32Offset + 1); i++ )
        {
            if ( i >= u32StrLen )
            {
                wChar = 0;
            }
            else
            {
                wChar = pwStr[i];
            }
            bPreCharInWord = bInWord;
            if ( TEXT_IS_ARABIC_ALPHA_TO_CONVERT(wChar) )/* current char is an arabic alpha char */
            {
                // Convert prec char | prec car is PI or PM
                if ( bInWord ) 
                {
                    bPreCharIsFirst = FALSE;
                }
                else
                {
                    bPreCharIsFirst = TRUE;
                }

                // Convert current char | cur car is PL or PF
                if ( TEXT_ARABIC_FORCE_END(TEXT_GET_COL(wChar)) || TEXT_ARABIC_FONTA_FORCE_END(TEXT_GET_COL(wChar)) )
                {
                    bInWord = FALSE;
                }
                else
                {
                    bInWord = TRUE;
                }
            }
            else /* non arabic alpha char or end of string */
            {      
                 bInWord = FALSE;
            } 
        }

        //pre char is last char
        if ( (bPreCharIsFirst && !bInWord) ||/*is isolate*/
             (!bPreCharIsFirst && bPreCharInWord && !bInWord) /*is last*/ )
        {
            bReturnValue = TRUE;
        }
    }
    return bReturnValue;
}

static U32 _msAPI_MLE_TextArabicConvertToDisplay( MLE_WChar *pString, U32 nStrLen )
{
    U32 nReturnValue = 0;

    if ( pString == NULL || nStrLen == 0 )
    {
        return 0;
    }

    nReturnValue = nStrLen;

    if ( _msAPI_MLE_TextArabicConvertFEFormat( pString, nReturnValue ) )
    {
        nReturnValue = _msAPI_MLE_TextArabicEFConcatenation(pString, nReturnValue);
    }

    return nReturnValue;

}

static BOOLEAN _msAPI_MLE_TextArabicConvertFEFormat( MLE_WChar *pString, U32 nStrLen )
{
    U32 nStrIndex = 0;     /* string counter */
    BOOLEAN bInWord = FALSE; /* Indicates if counter is in a word */
    BOOLEAN bPreCharIsFirst = FALSE;  /* Indicates whether prec car in firts position */
    BOOLEAN bIsPreComposedChar = FALSE;

    if ( pString == NULL || nStrLen == 0 )
    {
        return FALSE;
    }

    /* Convert to 0xFE format */
    while ( nStrIndex <= nStrLen )
    {
        if ( nStrIndex == 0 )
        {
            U16 nPreChar = 0;
            _msAPI_MLE_TextArabicConvertFEChar( &pString[nStrIndex], &nPreChar, &bInWord, &bPreCharIsFirst );
        }
        else if ( nStrIndex == nStrLen )
        {
            U16 nLastChar = 0;
            _msAPI_MLE_TextArabicConvertFEChar( &nLastChar, &pString[nStrIndex - 1], &bInWord, &bPreCharIsFirst );
        }
        else
        {
            if ( !TEXT_IS_ARABIC_COMPOSED_CHAR(pString[nStrIndex]) )
            {
                if ( bIsPreComposedChar )
                {
                    _msAPI_MLE_TextArabicConvertFEChar( &pString[nStrIndex], &pString[nStrIndex - 2], &bInWord, &bPreCharIsFirst );
                }
                else
                {
                    _msAPI_MLE_TextArabicConvertFEChar( &pString[nStrIndex], &pString[nStrIndex - 1], &bInWord, &bPreCharIsFirst );
                }
                bIsPreComposedChar = FALSE;
            }
            else
            {
                if ( bIsPreComposedChar )
                {
                    bIsPreComposedChar = FALSE;
                    bPreCharIsFirst = FALSE;
                    bInWord = FALSE;
                }
                else
                {
                    bIsPreComposedChar = TRUE;
                }
            }
        }
        nStrIndex++;
    }

    return TRUE;
}

static BOOLEAN _msAPI_MLE_TextArabicConvertFEChar( MLE_WChar *pChar, MLE_WChar *pPreChar, BOOLEAN *pInWord, BOOLEAN *pPreCharIsFirst )
{
    U8 nCharCol = 0;

    if ( (pChar == NULL && pPreChar == NULL) || pInWord == NULL || pPreCharIsFirst == NULL )
    {
        return FALSE;
    }

    if ( pPreChar == NULL && *pInWord == TRUE )
    {
        return FALSE;
    }

    /* Convert to 0xFE format */
    if ( pChar && TEXT_IS_ARABIC_ALPHA_TO_CONVERT(*pChar) )/* current char is an arabic alpha char */
    {
        // Convert prec char | prec car is PI or PM
        if ( *pInWord )
        {
            if ( pPreChar )
            {
                nCharCol = TEXT_GET_COL(*pPreChar);
                if ( TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT(*pPreChar) )
                {
                    TEXT_SET_ROW( *pPreChar, TEXT_ARABIC_FORM_A_ROW );
                    nCharCol = TEXT_ARABIC_FONTA_CONVERT2PL(nCharCol) + (*pPreCharIsFirst ? TEXT_ARABIC_PI_POSITION : TEXT_ARABIC_PM_POSITION); 
                }
                else
                {
                    TEXT_SET_ROW( *pPreChar, TEXT_ARABIC_FORM_B_ROW );
                    nCharCol = TEXT_ARABIC_CONVERT2PL(nCharCol) + (*pPreCharIsFirst ? TEXT_ARABIC_PI_POSITION : TEXT_ARABIC_PM_POSITION);
                }
                TEXT_SET_COL( *pPreChar, nCharCol );
            }
            *pPreCharIsFirst = FALSE;
        }
        else
        {
            *pPreCharIsFirst = TRUE;
        }

        // Convert current char | cur car is PL or PF
        if ( ((TEXT_GET_COL(*pChar) > TEXT_ARABIC_HAMZA_CHAR) && (TEXT_GET_COL(*pChar) <= TEXT_ARABIC_YEH_CHAR) && TEXT_ARABIC_FORCE_END(TEXT_GET_COL(*pChar))) || 
             ((TEXT_GET_COL(*pChar) >= TEXT_ARABIC_WASLA_CHAR) && TEXT_ARABIC_FONTA_FORCE_END(TEXT_GET_COL(*pChar))) )
        {
            nCharCol = TEXT_GET_COL(*pChar);
            if ( TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT(*pChar) )
            {
                TEXT_SET_ROW( *pChar, TEXT_ARABIC_FORM_A_ROW );
                nCharCol = TEXT_ARABIC_FONTA_CONVERT2PL(nCharCol) + (*pInWord ? TEXT_ARABIC_PF_POSITION : TEXT_ARABIC_PL_POSITION); 
            }
            else
            {
            TEXT_SET_ROW( *pChar, TEXT_ARABIC_FORM_B_ROW );
            nCharCol = TEXT_ARABIC_CONVERT2PL(nCharCol) + (*pInWord ? TEXT_ARABIC_PF_POSITION : TEXT_ARABIC_PL_POSITION);
            }
            TEXT_SET_COL( *pChar, nCharCol );
            /* end of word */
            *pInWord = FALSE;
        }
        else
        {
            /* in a word */
            *pInWord = TRUE;
        }
    }
    else /* non arabic alpha char or end of string */
    {
        if ( *pInWord && pPreChar)
        {
            // Convert prec char | prec car is PF or PL
            nCharCol = TEXT_GET_COL(*pPreChar);
            if (pChar &&  TEXT_GET_COL(*pChar) == 0x40 ) //a join causing character
            {
                if ( TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT(*pPreChar) )
                {
                    TEXT_SET_ROW( *pPreChar, TEXT_ARABIC_FORM_A_ROW );
                    nCharCol = TEXT_ARABIC_FONTA_CONVERT2PL(nCharCol) + (*pPreCharIsFirst ? TEXT_ARABIC_PI_POSITION : TEXT_ARABIC_PM_POSITION);
                }
                else
            {
                    TEXT_SET_ROW( *pPreChar, TEXT_ARABIC_FORM_B_ROW );
                nCharCol = TEXT_ARABIC_CONVERT2PL(nCharCol) + (*pPreCharIsFirst ? TEXT_ARABIC_PI_POSITION : TEXT_ARABIC_PM_POSITION);
            }
            }
            else
            {
                if ( TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT(*pPreChar) )
                {
                    TEXT_SET_ROW( *pPreChar, TEXT_ARABIC_FORM_A_ROW );
                    nCharCol = TEXT_ARABIC_FONTA_CONVERT2PL(nCharCol) + (*pPreCharIsFirst ? TEXT_ARABIC_PL_POSITION : TEXT_ARABIC_PF_POSITION);
                }
            else
            {
                    TEXT_SET_ROW( *pPreChar, TEXT_ARABIC_FORM_B_ROW );
            nCharCol = TEXT_ARABIC_CONVERT2PL(nCharCol) + (*pPreCharIsFirst ? TEXT_ARABIC_PL_POSITION : TEXT_ARABIC_PF_POSITION);
            }
            }
            TEXT_SET_COL( *pPreChar, nCharCol );
        }

        /* end of word */
        *pInWord = FALSE;
    }

    return TRUE;
}

static U32 _msAPI_MLE_TextArabicEFConcatenation( MLE_WChar *pEFString, U32 nStrLen )
{
    U32 nStrIndex = 0;     /* string counter */
    U32 nReturnValue = 0;

    if ( pEFString == NULL || nStrLen == 0 )
    {
        return 0;
    }

    nReturnValue = nStrLen;

    /* char concatenation */
    while ( nStrIndex < nStrLen - 1 )
    {
        if ( _msAPI_MLE_TextArabicFEConcatenationNextChar( &(pEFString[nStrIndex]), pEFString[nStrIndex + 1]) )
        {
            /* delete second char and adjust string len */
            nReturnValue = msAPI_MLE_TEXTUTIL_UCS2RemoveCharAt( pEFString, nReturnValue, (nStrIndex + 1) );
            nStrLen = nReturnValue;
        }

        nStrIndex++;
    }

    return nReturnValue;
}

static BOOLEAN _msAPI_MLE_TextArabicFEConcatenationNextChar( MLE_WChar *pEFChar, MLE_WChar nEFNextChar )
{
    U8 nCharCol = 0;
    U8 nCharForm;
    BOOLEAN bReturn = FALSE;

    if ( pEFChar == NULL )
    {
        return FALSE;
    }

    if ( nEFNextChar &&
         (TEXT_GET_ROW(*pEFChar) == TEXT_ARABIC_FORM_B_ROW) &&
         (TEXT_GET_ROW(nEFNextChar) == TEXT_ARABIC_FORM_B_ROW) &&
         ((TEXT_GET_COL(*pEFChar) == TEXT_ARABIC_LAM_CHAR_PL + TEXT_ARABIC_PI_POSITION) ||
          (TEXT_GET_COL(*pEFChar) == TEXT_ARABIC_LAM_CHAR_PL + TEXT_ARABIC_PM_POSITION) ) &&
         ((TEXT_GET_COL(nEFNextChar) == TEXT_ARABIC_ALEF_MADDA_ABOVE_CHAR_PL + TEXT_ARABIC_PF_POSITION) ||
          (TEXT_GET_COL(nEFNextChar) == TEXT_ARABIC_ALEF_HAMZA_ABOVE_CHAR_PL + TEXT_ARABIC_PF_POSITION) ||
          (TEXT_GET_COL(nEFNextChar) == TEXT_ARABIC_ALEF_HAMZA_BELOW_CHAR_PL + TEXT_ARABIC_PF_POSITION) ||
          (TEXT_GET_COL(nEFNextChar) == TEXT_ARABIC_ALEF_CHAR_PL             + TEXT_ARABIC_PF_POSITION)) )
    /* current char is ARABIC_LAM_CHAR (PI or PM) and next char is an ALEF (PF) */
    {
        /* determine position of substituted char */
        nCharForm = (TEXT_GET_COL(*pEFChar) == (TEXT_ARABIC_LAM_CHAR_PL + TEXT_ARABIC_PI_POSITION)) ? TEXT_ARABIC_PL_POSITION : TEXT_ARABIC_PF_POSITION;

        switch ( TEXT_GET_COL(nEFNextChar) )
        {
            case (TEXT_ARABIC_ALEF_MADDA_ABOVE_CHAR_PL + TEXT_ARABIC_PF_POSITION):
                nCharCol = TEXT_ARABIC_LIG_LAM_ALEF_MADDA_ABOVE_CHAR_PL;
                break;
            case (TEXT_ARABIC_ALEF_HAMZA_ABOVE_CHAR_PL + TEXT_ARABIC_PF_POSITION):
                nCharCol = TEXT_ARABIC_LIG_LAM_ALEF_HAMZA_ABOVE_CHAR_PL;
                break;
            case (TEXT_ARABIC_ALEF_HAMZA_BELOW_CHAR_PL + TEXT_ARABIC_PF_POSITION):
                nCharCol = TEXT_ARABIC_LIG_LAM_ALEF_HAMZA_BELOW_CHAR_PL;
                break;
            case (TEXT_ARABIC_ALEF_CHAR_PL + TEXT_ARABIC_PF_POSITION):
                nCharCol = TEXT_ARABIC_LIG_LAM_ALEF_CHAR_PL;
                break;
        }

        /* select correct position:*/
        nCharCol = nCharCol + nCharForm;
        TEXT_SET_COL( *pEFChar, nCharCol );
        bReturn = TRUE;
    }

    return bReturn;
}

U16 msAPI_MLE_TextArabicGetNextCodes(const U16 *pInTxt, U32 nInLen, U32 nOffset, U32 nSubLen, U16 *pOutCode, U32 nOutLen, U32 *paConsumed, BOOLEAN bDispStr, U16 *pLastCode )
{
    U16 nChar = 0;
    U16 nNextChar = 0;
    U16 nConverStrLen = 0;
    U16 nConverStr[MLE_TEXT_ARABIC_CONVERT_LEN] = {0,};
    U16 nReturnLen = 0;

    nOutLen = nOutLen;
    
    if ( nSubLen == 0 || (nOffset + nSubLen) > nInLen || pOutCode == NULL || paConsumed == NULL )
    {
        return 0;
    }

    paConsumed[0] = 1;
    paConsumed[1] = 1;
    pOutCode[0] = pInTxt[nOffset];

    if ( pLastCode )
    {
        *pLastCode = 0;
    }

    if ( msAPI_MLE_TEXTUTIL_IsArabicChar(pInTxt[nOffset]) )
    {
        U32 nConvertOffset = 0;
        nReturnLen = 1;

        //init to convert string
        if ( nOffset > 0 )
        {
            if ( nOffset + nSubLen < nInLen )
            {
                nConverStrLen = (nSubLen > (MLE_TEXT_ARABIC_CONVERT_LEN - 2)) ? MLE_TEXT_ARABIC_CONVERT_LEN : (nSubLen + 2);
            }
            else
            {
                nConverStrLen = (nSubLen > (MLE_TEXT_ARABIC_CONVERT_LEN - 1)) ? MLE_TEXT_ARABIC_CONVERT_LEN : (nSubLen + 1);
            }
            MEMCPY( (void *)nConverStr, (void *)(pInTxt + nOffset - 1), sizeof(U16) * nConverStrLen );
            nConvertOffset = 1;
        }
        else
        {
            if ( nOffset + nSubLen < nInLen )
            {
                nConverStrLen = (nSubLen > (MLE_TEXT_ARABIC_CONVERT_LEN - 1)) ? MLE_TEXT_ARABIC_CONVERT_LEN : (nSubLen + 1);
            }
            else
            {
                nConverStrLen = (nSubLen > MLE_TEXT_ARABIC_CONVERT_LEN) ? MLE_TEXT_ARABIC_CONVERT_LEN : nSubLen;
            }
            MEMCPY( (void *)nConverStr, (void *)(pInTxt + nOffset), sizeof(U16) * nConverStrLen );
        }

        msAPI_MLE_TEXTUTIL_ConvertToArabicFEStr( nConverStr, nConverStrLen, bDispStr );

        nChar = nConverStr[nConvertOffset];
        pOutCode[0] = nChar;

        if ( (nConverStrLen - nConvertOffset) > 1 )
        {
            U16 nThirdChar = 0;

            nNextChar = nConverStr[nConvertOffset + 1];

            if ( bDispStr )
            {
                if ( TEXT_IS_ARABIC_COMPOSED_CHAR(nNextChar) )
                {
                    if ( (nConverStrLen - nConvertOffset) > 2 )
                    {
                        nThirdChar = nConverStr[nConvertOffset + 2];
                        if ( msAPI_MLE_TEXTUTIL_ConcatenationArabicFEChar(&nThirdChar, nChar) )
                        {
                            pOutCode[0] = nThirdChar;
                            pOutCode[1] = nNextChar;
                            paConsumed[0] = 3;
                            paConsumed[1] = 2;
                            paConsumed[2] = 1;
                            nReturnLen = 2;
                        }
                    }
                }
                else
                {
                    if ( msAPI_MLE_TEXTUTIL_ConcatenationArabicFEChar(&nNextChar, nChar) )
                    {
                        pOutCode[0] = nNextChar;
                        paConsumed[0] = 2;
                        paConsumed[1] = 2;
                        nReturnLen = 1;
                    }
                    else
                    {
                        if ( TEXT_IS_ARABIC_COMPOSED_CHAR(nChar) )
                        {
                            pOutCode[0] = nNextChar;
                            pOutCode[1] = nChar;
                            paConsumed[0] = 2;
                            paConsumed[1] = 1;
                            paConsumed[2] = 1;
                            nReturnLen = 2;
                            if ( (nConverStrLen - nConvertOffset) > 2 )
                            {
                                nThirdChar = nConverStr[nConvertOffset + 2];
                                if ( msAPI_MLE_TEXTUTIL_ConcatenationArabicFEChar(&nThirdChar, nNextChar) )
                                {
                                    pOutCode[0] = nThirdChar;
                                    pOutCode[1] = nChar;
                                    paConsumed[0] = 3;
                                    paConsumed[1] = 2;
                                    paConsumed[2] = 1;
                                    nReturnLen = 2;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if ( TEXT_IS_ARABIC_COMPOSED_CHAR(nNextChar) )
                {
                    pOutCode[1] = nNextChar;
                    paConsumed[0] = 2;
                    paConsumed[1] = 1;
                    paConsumed[2] = 1;
                    nReturnLen = 2;

                    if ( (nConverStrLen - nConvertOffset) > 2 )
                    {
                        nThirdChar = nConverStr[nConvertOffset + 2];
                        if ( msAPI_MLE_TEXTUTIL_ConcatenationArabicFEChar(&nChar, nThirdChar) )
                        {
                            pOutCode[0] = nChar;
                            pOutCode[1] = nNextChar;
                            paConsumed[0] = 3;
                            paConsumed[1] = 2;
                            paConsumed[2] = 1;
                            nReturnLen = 2;
                        }
                    }
                }
                else
                {
                    if ( msAPI_MLE_TEXTUTIL_ConcatenationArabicFEChar(&nChar, nNextChar) )
                    {
                        pOutCode[0] = nChar;
                        paConsumed[0] = 2;
                        paConsumed[1] = 2;
                        nReturnLen = 1;

                        if ( (nConverStrLen - nConvertOffset) > 2 )
                        {
                            nThirdChar = nConverStr[nConvertOffset + 2];
                            if ( TEXT_IS_ARABIC_COMPOSED_CHAR(nThirdChar) )
                            {
                                pOutCode[1] = nThirdChar;
                                paConsumed[0] = 3;
                                paConsumed[1] = 2;
                                paConsumed[2] = 1;
                                nReturnLen = 2;
                            }
                        }
                    }
                }
            }
        }

        _msAPI_MLE_TextArabicConvertLastCodeType( pOutCode[0], pLastCode );
    }

    return nReturnLen;
}

#ifdef __FEATURE_VECTOR_FONT__
U16 msAPI_MLE_TextArabicVectorGetNextCodes(const U16 *pInTxt, U32 nInLen, U32 nOffset, U32 nSubLen, U16 *pOutCode, U32 nOutLen, U32 *paConsumed, BOOLEAN bDispStr, U16 *pLastCode )
{
    U16 u16ReturnLen = 0;
    
    u16ReturnLen = msAPI_MLE_TextArabicGetNextCodes(pInTxt, nInLen, nOffset, nSubLen, pOutCode, nOutLen, paConsumed, bDispStr, pLastCode);

    if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
    {
        U16 i;
        for ( i = 0; i < u16ReturnLen; i++ )
        {
            if( msAPI_MLE_FontBaseIsControlChar(pOutCode[i]) )
            {
                pOutCode[i] = (U16)(-2); //Control code
            }
            else
            {
                pOutCode[i] = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(pOutCode[i]);
            }
        }
    }

    return u16ReturnLen;
}
#endif //__FEATURE_VECTOR_FONT__

static BOOLEAN _msAPI_MLE_TextArabicConvertLastCodeType( const U16 nChar, U16 *pLastCodeType )
{
    U8 nCharCol;
    BOOLEAN bResult = FALSE;

    if ( pLastCodeType == NULL )
    {
        return FALSE;
    }

    *pLastCodeType = 0;

    if ( TEXT_IS_ARABIC_ALPHA_TO_CONVERT(nChar) )
    {
        if ( !TEXT_ARABIC_FORCE_END(TEXT_GET_COL(nChar)) && !TEXT_ARABIC_FONTA_FORCE_END(TEXT_GET_COL(nChar)) )
        {
            nCharCol = TEXT_GET_COL(nChar);
            if ( TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT(*pLastCodeType) )
            {
                TEXT_SET_ROW( *pLastCodeType, TEXT_ARABIC_FORM_A_ROW );
                nCharCol = TEXT_ARABIC_FONTA_CONVERT2PL(nCharCol);  
            }
            else
        {
            TEXT_SET_ROW( *pLastCodeType, TEXT_ARABIC_FORM_B_ROW );
            nCharCol = TEXT_ARABIC_CONVERT2PL(nCharCol);
            }
            TEXT_SET_COL( *pLastCodeType, nCharCol );
            bResult = TRUE;
        }
    }
    else if ( (TEXT_GET_ROW(nChar) == TEXT_ARABIC_FORM_B_ROW) &&
               (TEXT_GET_COL(nChar) > 0x80) && (TEXT_GET_COL(nChar) < 0xF5) )
    {
        nCharCol = TEXT_GET_COL( nChar );
        if ( TEXT_FEARABIC_PL(nCharCol) == TEXT_ARABIC_PI_POSITION )
        {
            TEXT_SET_ROW( *pLastCodeType, TEXT_ARABIC_FORM_B_ROW );
            nCharCol = TEXT_FEARABIC_CONVERT2PL(nCharCol);
            nCharCol = TEXT_ARABIC_CONVERT2PL(nCharCol);
            TEXT_SET_COL( *pLastCodeType, nCharCol );
            bResult = TRUE;
        }
        else if ( TEXT_FEARABIC_PL(nCharCol) == TEXT_ARABIC_PM_POSITION )
        {
            TEXT_SET_ROW( *pLastCodeType, TEXT_ARABIC_FORM_B_ROW );
            nCharCol = TEXT_FEARABIC_CONVERT2PL(nCharCol);
            nCharCol = TEXT_ARABIC_CONVERT2PL(nCharCol) + TEXT_ARABIC_PF_POSITION;
            TEXT_SET_COL( *pLastCodeType, nCharCol );
            bResult = TRUE;
        }
    }
    else if ( (TEXT_GET_ROW(nChar) == TEXT_ARABIC_FORM_A_ROW) && 
               (TEXT_GET_COL(nChar) >= 0x50))
    {
        nCharCol = TEXT_GET_COL( nChar );
        if ( TEXT_FBARABIC_FONTA_PL(nCharCol) == TEXT_ARABIC_PI_POSITION )
        {
            TEXT_SET_ROW( *pLastCodeType, TEXT_ARABIC_FORM_A_ROW );
            nCharCol = TEXT_FBARABIC_FONTA_CONVERT2PL(nCharCol);   
            nCharCol = TEXT_ARABIC_FONTA_CONVERT2PL(nCharCol);   
            TEXT_SET_COL( *pLastCodeType, nCharCol );
            bResult = TRUE;
        }
        else if ( TEXT_FBARABIC_FONTA_PL(nCharCol) == TEXT_ARABIC_PM_POSITION )
        {
            TEXT_SET_ROW( *pLastCodeType, TEXT_ARABIC_FORM_A_ROW );
            nCharCol = TEXT_FBARABIC_FONTA_CONVERT2PL(nCharCol);   
            nCharCol = TEXT_ARABIC_FONTA_CONVERT2PL(nCharCol) + TEXT_ARABIC_PF_POSITION;   
            TEXT_SET_COL( *pLastCodeType, nCharCol );
            bResult = TRUE;
        }
    }
    return bResult;
}

#endif //__BIDI_TEXT__
