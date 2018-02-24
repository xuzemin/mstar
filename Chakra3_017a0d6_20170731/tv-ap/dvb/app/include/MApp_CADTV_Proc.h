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

#ifndef _MApp_CADTVPROC_H
#define _MApp_CADTVPROC_H

#include "drvAVD.h"
#if(ENABLE_S2) 
#include "msAPI_Tuner.h"
#endif
/********************************************************************************/
/*                               Macro                                          */
/********************************************************************************/

#ifdef MAPP_CADTVPROC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//****************************************************************************
// Public attributes.
//****************************************************************************
// CADTV PROGRAM DATA STRUCTURE
#define DEFAULT_DVBC_CONSTEL_TYPE CAB_QAM16
#define MAX_DVBC_FREQUENCY        862000//888000
#define MIN_DVBC_FREQUENCY        48000//99000
#define DEFAULT_DVBC_FREQUENCY    770000 //642000
#define MAX_DVBC_SYMBOL_RATE      9999
#define MIN_DVBC_SYMBOL_RATE      9
#define DEFAULT_DVBC_NORDIG_SYMBOL_RATE  6875
#define DEFAULT_DVBC_CHINA_SYMBOL_RATE   6875
#define DEFAULT_DVBC_SYMBOL_RATE         6900

#define DEFAULT_DVBC_NID        0xFFFF
/// Define DVB-C modulation scheme
typedef enum
{
    CAB_QAM16,                                                          ///< QAM 16
    CAB_QAM32,                                                          ///< QAM 32
    CAB_QAM64,                                                          ///< QAM 64
    CAB_QAM128,                                                         ///< QAM 128
    CAB_QAM256,
} EN_CAB_CONSTEL_TYPE;
//****************************************************************************
// Public functions.
//****************************************************************************

INTERFACE BOOL MApp_CadtvManualTuning_IncreaseFrequency(void);
INTERFACE BOOL MApp_CadtvManualTuning_DecreaseFrequency(void);
INTERFACE U32 MApp_CadtvManualTuning_GetFrequency(void);
INTERFACE BOOL MApp_CadtvManualTuning_SetFrequency(U32 u32Freq);
INTERFACE BOOL MApp_CadtvManualTuning_IncreaseSymbol(void);
INTERFACE BOOL MApp_CadtvManualTuning_DecreaseSymbol(void);
INTERFACE U16 MApp_CadtvManualTuning_GetSymbol(void);
INTERFACE BOOL MApp_CadtvManualTuning_SetSymbol(U16 u16Sym);
INTERFACE BOOL MApp_CadtvManualTuning_IncreaseQamType(void);
INTERFACE BOOL MApp_CadtvManualTuning_DecreaseQamType(void);
INTERFACE EN_CAB_CONSTEL_TYPE MApp_CadtvManualTuning_GetQamType(void);
INTERFACE BOOL MApp_CadtvManualTuning_SetQamType(EN_CAB_CONSTEL_TYPE eQAM);
INTERFACE U16 MApp_CadtvManualTuning_GetNID(void);
INTERFACE BOOL MApp_CadtvManualTuning_SetNID(U16 u16NID);
INTERFACE void MApp_CATV_RestoreManutuning_settingDefault(void);
#undef INTERFACE
#endif // __CADTVPROC_H__
