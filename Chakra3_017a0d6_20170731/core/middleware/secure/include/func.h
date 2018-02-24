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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _FUNC_H_
#define _FUNC_H_

typedef void (*FP_SHA256_INIT)(U32 *hash);

typedef void (*FP_SHA256_HASH)(const U32 *data, U32 *hash);

typedef void (*FP_SHA1_INIT)(U32 *hash);

typedef void (*FP_SHA1_HASH)(const U32 *data, U32 *hash);

typedef int (*FP_MP_MOD_EXP)(DIGIT_T yout[], const DIGIT_T x[], const DIGIT_T e[], const DIGIT_T m[], int ndigits);

typedef int (*FP_MP_CONV_FROM_OCTETS)(DIGIT_T a[], int ndigits, const unsigned char *c, int nbytes);

typedef int (*FP_MP_EQUAL)(const DIGIT_T a[], const DIGIT_T b[], int ndigits);

typedef void (*FP_MP_SETZERO)(const DIGIT_T a[], int ndigits);

typedef void (*FP_NULL)(void);

//int mpSquare(DIGIT_T w[], const DIGIT_T x[], int ndigits)
typedef int (*FP_MP_SQUARE)(DIGIT_T w[], const DIGIT_T x[], int ndigits);

//int mpMultiply(DIGIT_T w[], const DIGIT_T u[], const DIGIT_T v[], int ndigits)
typedef int (*FP_MP_MULTIPLY)(DIGIT_T w[], const DIGIT_T u[], const DIGIT_T v[], int ndigits);

//int mpDivide(DIGIT_T q[], DIGIT_T r[], const DIGIT_T u[], int udigits, DIGIT_T v[], int vdigits)
typedef int (*FP_MP_DIVIDE)(DIGIT_T q[], DIGIT_T r[], const DIGIT_T u[], int udigits, DIGIT_T v[], int vdigits);

//DIGIT_T mpShortDiv(DIGIT_T q[], const DIGIT_T u[], DIGIT_T v, int ndigits)
typedef DIGIT_T (*FP_MP_SHORT_DIV)(DIGIT_T q[], const DIGIT_T u[], DIGIT_T v, int ndigits);

//DIGIT_T mpShiftLeft(DIGIT_T a[], const DIGIT_T *b, int shift, int ndigits)
typedef DIGIT_T (*FP_MP_SHIFT_LEFT)(DIGIT_T a[], const DIGIT_T *b, int shift, int ndigits);

//DIGIT_T mpShiftRight(DIGIT_T a[], const DIGIT_T b[], int shift, int ndigits)
typedef DIGIT_T (*FP_MP_SHIFT_RIGHT)(DIGIT_T a[], const DIGIT_T b[], int shift, int ndigits);

//int spMultiply(DIGIT_T p[2], DIGIT_T x, DIGIT_T y)
typedef int (*FP_SP_MULTIPLY)(DIGIT_T p[2], DIGIT_T x, DIGIT_T y);

//DIGIT_T spDivide(DIGIT_T *q, DIGIT_T *r, const DIGIT_T u[2], DIGIT_T v)
typedef DIGIT_T (*FP_SP_DIVIDE)(DIGIT_T *q, DIGIT_T *r, const DIGIT_T u[2], DIGIT_T v);

typedef struct
{
    FP_SHA256_INIT      Sha256Init;
    FP_SHA256_HASH      Sha256Hash;
    FP_SHA1_INIT        Sha1Init;
    FP_SHA1_HASH        Sha1Hash;

    FP_NULL             reserve_0[4];

    FP_MP_CONV_FROM_OCTETS ConvFromOctets;
    FP_MP_MOD_EXP       ModExp;
    FP_MP_EQUAL         Equal;

    FP_MP_SQUARE        Square;
    FP_MP_MULTIPLY      Multiply;
    FP_MP_DIVIDE        Divide;
    FP_MP_SHORT_DIV     ShortDiv;
    FP_MP_SHIFT_LEFT    ShiftLeft;
    FP_MP_SHIFT_RIGHT   ShiftRight;

    FP_SP_MULTIPLY      SpMultiply;
    FP_SP_DIVIDE        SpDivide;

    FP_NULL             reserve_1[13];
} MpFuncTbl;

extern MpFuncTbl        *mpFunc;
extern MpFuncTbl        _mpFunc;

//void mpfunc_relocate(void);

#endif

