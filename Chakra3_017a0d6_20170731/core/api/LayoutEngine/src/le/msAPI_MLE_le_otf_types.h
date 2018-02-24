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

#ifndef __MSAPI_MSTAR_LE_OTF_TYPES_H__
#define __MSAPI_MSTAR_LE_OTF_TYPES_H__

#ifdef __FEATURE_VECTOR_FONT__

enum
{
    LE_OTF_SCRIPT_DEVA = 0,
    LE_OTF_SCRIPT_BENG = 1,
    LE_OTF_SCRIPT_GUJR = 2,
    LE_OTF_SCRIPT_ORYA = 3,
    LE_OTF_SCRIPT_TAML = 4,
    LE_OTF_SCRIPT_TELU = 5,
    LE_OTF_SCRIPT_KNDA = 6,
    LE_OTF_SCRIPT_MLYM = 7,
    LE_OTF_SCRIPT_GURU = 8,
    LE_OTF_SCRIPT_SINH = 9,
    LE_OTF_SCRIPT_MYMR = 10,
    LE_OTF_SCRIPT_KHMR = 11,
    LE_OTF_SCRIPT_LAOO = 12,
    LE_OTF_SCRIPT_MYMR_EXTA = 13,
    LE_OTF_SCRIPT_MYMR_EXTB = 14,
    LE_OTF_SCRIPT_KHMR_DIGIT1 = 15,
    LE_OTF_SCRIPT_KHMR_DIGIT2 = 16,
    LE_OTF_SCRIPT_KHMR_SYMBOLS = 17,
    LE_OTF_MAX_SCRIPT_NUM
};
typedef U8 LE_OTF_ScriptTag_e;

enum
{
    LE_OTF_FEATURE_LOCL = 0,
    LE_OTF_FEATURE_INIT = 1,
    LE_OTF_FEATURE_NUKT = 2,
    LE_OTF_FEATURE_AKHN = 3,
    LE_OTF_FEATURE_RPHF = 4,
    LE_OTF_FEATURE_BLWF = 5,
    LE_OTF_FEATURE_HALF = 6,
    LE_OTF_FEATURE_PSTF = 7,
    LE_OTF_FEATURE_VATU = 8,
    LE_OTF_FEATURE_PRES = 9,
    LE_OTF_FEATURE_BLWS = 10,
    LE_OTF_FEATURE_ABVS = 11,
    LE_OTF_FEATURE_PSTS = 12,
    LE_OTF_FEATURE_HALN = 13,
    LE_OTF_FEATURE_BLWM = 14,
    LE_OTF_FEATURE_ABVM = 15,
    LE_OTF_FEATURE_DIST = 16,
    LE_OTF_FEATURE_RKRF = 17,
    LE_OTF_FEATURE_CJCT = 18,
    LE_OTF_FEATURE_CALT = 19,
    LE_OTF_FEATURE_KERN = 20,
    LE_OTF_FEATURE_PREF = 21,
    LE_OTF_FEATURE_MARK = 22,
    LE_OTF_FEATURE_MKMK = 23,
    LE_OTF_FEATURE_CLIG = 24,
    LE_OTF_FEATURE_LIGA = 25,
    LE_OTF_FEATURE_RLIG = 26,
    LE_OTF_MAX_FEATURE_NUM
};
typedef U8 LE_OTF_FeatureTag_e;

typedef struct
{
    LE_OTF_FeatureTag_e eTag;
    U32 u32Mask;
} LE_OTF_FeatureRecord_t;

#endif //__FEATURE_VECTOR_FONT__
#endif //__MSAPI_MSTAR_LE_OTF_TYPES_H__
