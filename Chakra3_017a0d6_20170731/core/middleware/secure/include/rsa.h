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
//
// "Contains BIGDIGITS multiple-precision arithmetic code originally
// written by David Ireland, copyright (c) 2001-6 by D.I. Management
// Services Pty Limited <www.di-mgt.com.au>, and is used with
// permission."
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _RSA_H_
#define _RSA_H_

#include "datatype.h"
//-------------------------------------------------------------------------------------------------
// Type definition
//-------------------------------------------------------------------------------------------------
typedef U32                         DIGIT_T;
#define DIGIT_S                     sizeof(DIGIT_T)

#define RSA_KEY_DIGI_LEN            (64)                                // DIGIT_T count

#define REG_OTPKEY_RSA_N_LEN        (64*DIGIT_S)                        // 2048
#define REG_OTPKEY_RSA_E_LEN        (1 *DIGIT_S)                        // 32

typedef struct _Integer2048
{
    U8                              Byte[256];
} Integer2048;

typedef struct _Integer128
{
    U8                              Byte[16];
} Integer128;

typedef struct _Integer32
{
    U8                              Byte[4];
} Integer32;


//-------------------------------------------------------------------------------------------------
// Extern prototype
//-------------------------------------------------------------------------------------------------

extern int mpConvFromOctets(DIGIT_T a[], int ndigits, const unsigned char *c, int nbytes);
extern int mpModExp(DIGIT_T yout[], const DIGIT_T x[], const DIGIT_T e[], const DIGIT_T m[], int ndigits);
extern int mpEqual(const DIGIT_T a[], const DIGIT_T b[], int ndigits);
extern int mpSquare(DIGIT_T w[], const DIGIT_T x[], int ndigits);
extern int mpMultiply(DIGIT_T w[], const DIGIT_T u[], const DIGIT_T v[], int ndigits);
extern int mpDivide(DIGIT_T q[], DIGIT_T r[], const DIGIT_T u[], int udigits, DIGIT_T v[], int vdigits);
extern DIGIT_T mpShortDiv(DIGIT_T q[], const DIGIT_T u[], DIGIT_T v, int ndigits);
extern DIGIT_T mpShiftLeft(DIGIT_T a[], const DIGIT_T *b, int shift, int ndigits);
extern DIGIT_T mpShiftRight(DIGIT_T a[], const DIGIT_T b[], int shift, int ndigits);
extern int spMultiply(DIGIT_T p[2], DIGIT_T x, DIGIT_T y);
extern DIGIT_T spDivide(DIGIT_T *q, DIGIT_T *r, const DIGIT_T u[2], DIGIT_T v);


#endif // _RSA_H_
