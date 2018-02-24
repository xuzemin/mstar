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

#ifndef _M88DC2800_H_
#define _M88DC2800_H_

/* ------------------------------------
    Header Files
   ------------------------------------ */
#include "datatype.h"
#include "msAPI_Global.h"

/* ------------------------------------
    Macro Definitions
   ------------------------------------ */
#undef EXTERN

#ifdef _M88DC2800_C_
#define EXTERN
#else
#define EXTERN  extern
#endif


/* ------------------------------------
    Variables Definitions/Declarations
   ------------------------------------ */
#define FREQ_XTAL                   (28920000UL)

#define M88DC2800_devAddr              0x38
#define COFDM_DEM_I2C_ID            M88DC2800_devAddr

// Register
#define _QAM_SEL                    0x00
#define _BLIND_STEP1                0x01
#define _LMS_STEP1                  0x02
#define _LMS_STEP2                  0x05
#define _MSE_LO                     0x07
#define _MSE_HI                     0x08
#define _DERO_INIT_FREQ             0x11
#define _DERO_FREQ_STEP             0x12
#define _DERO_FREQ_LIM              0x13
#define _AGCRF_MAX_STEP             0x2A
#define _AGCIF_MAX                  0x30
#define _AGCRF_MAX                  0x32
#define _AGCIF_THR                  0x35
#define _AGC_FREZ                   0x36
#define _ADC_CRL_0                  0x37
#define _AGCRF_MIN                  0x39
#define _AGCIF_MIN                  0x3A
#define _AGCRF_CUR                  0x3B
#define _AGCIF_CUR                  0x3C
#define _AGC_REF_LO                 0x40
#define _AGC_REF_HI                 0x41
#define _AAGC_LCK_DUR               0x42
#define _AAGC_ACQ_CLR               0x43
#define _AAGC_GN                    0x44
#define _GPPWM_CORN_RAT_LO          0x4A
#define _GPPWM_CORN_RAT_HI          0x4B
#define _ADC_TM_COEF                0x4C
#define _STL_GN_1                   0x52
#define _STL_DIR_GN                 0x53
#define _STL_GN_2                   0x59
#define _SYMB_RATE_1                0x55
#define _SYMB_RATE_2                0x56
#define _SYMB_RATE_3                0x57
#define _SYMB_RATE_4                0x58
#define _STL_CTRL0                  0x5A
#define _SYMB_RATE_INV1             0x5C
#define _SYMB_RATE_INV2             0x5D
#define _CRL_SWP_INI_0              0x60
#define _CRL_SWP_SEL                0x61
#define _CRL_EQ_CAP0                0x63
#define _CRL_EQ_CAP1                0x64
#define _CRL_EQ_CAP2                0x65
#define _CRL_EQ_CAP3                0x66
#define _CRL_EQ_CAP4                0x67
#define _CRL_EQ_CAP5                0x68
#define _CRL_EQ_CAP6                0x69
#define _CRL_CTRL                   0x6A
#define _DAGC_LCK_THR_HI            0x71
#define _DAGC_LP_GN1                0x72
#define _DAGC_LP_GN2                0x73
#define _DAGC_LP_GN3                0x74
#define _VER_SRST                   0x80
#define _LCK                        0x82
#define _J83C_SPEC_INV              0x83
#define _GRST_FMT                   0x84
#define _INT                        0x85
#define _INT_LCK_SRC                0x86
#define _AGC_POL_INV                0x88
#define _REG_VGACFM                 0x8E
#define _SYNC_0                     0x90
#define _SYNC_1                     0x91
#define _RS_BER_0                   0xA0
#define _FMT_0                      0xC0
#define _FMT_2                      0xC2
#define _DESC_MD                    0xDE
#define _CNT_HLD_CLR                0xDF
#define _SLEEP_MD                   0xE2
#define _BLIND_DUR_HI               0xF0
#define _BLIND_DUR_LO               0xF1
#define _LMS_DUR_HI                 0xF2
#define _LMS_DUR_LO                 0xF3
#define _BLIND_STEP2                0xFB
#define _BLIND_STEP3                0xFC


typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_SYMBOL_TIMING_LOCK,
    COFDM_AGC_LOCK,
    COFDM_DESCRAMBLER_LOCK,
    COFDM_BYTE_ALIGNER_LOCK
} COFDM_LOCK_STATUS;

/* ------------------------------------
    Function Prototypes
   ------------------------------------ */
EXTERN void M88DC2800_Initialize(void);
EXTERN void M88DC2800_InitRegister(void);
EXTERN void M88DC2800_Config(void);
EXTERN BOOLEAN M88DC2800_SetTxMode(U8 inverted,U8 j83);
EXTERN BOOLEAN M88DC2800_SetSym(U32 sym, U32 xtal);
EXTERN BOOLEAN M88DC2800_SetQAM(U16 qam);
EXTERN BOOLEAN M88DC2800_SoftReset(void);
EXTERN BOOLEAN M88DC2800_RepeatControl ( BOOLEAN bEnable );
EXTERN BOOLEAN M88DC2800_Serial_Control(BOOLEAN bEnable);
EXTERN U8 M88DC2800_GetAgcLock(void);
EXTERN BOOLEAN M88DC2800_GetLock(void);
EXTERN U8 M88DC2800_GetSNR(void);
EXTERN FUNCTION_RESULT M88DC2800_GetSignalStrength(WORD *strength);
EXTERN BOOLEAN M88DC2800_TSOut_Control(BOOLEAN bEnable);

#endif /* _M88DC2800_H_ */
