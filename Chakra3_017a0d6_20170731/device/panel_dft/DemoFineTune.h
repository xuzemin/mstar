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
#ifndef _DEMO_FINE_TUNE_H_
#define _DEMO_FINE_TUNE_H_

#include "Board.h"
#include "apiPNL.h"


#define DLC_PURE_IMAGE_DLC_CURVE            0
#define DLC_PURE_IMAGE_LINEAR_CURVE         1
#define DLC_PURE_IMAGE_DO_NOTHING           2

// ===== Demo Fine Tune item =======================================
#define DFT_NONE                            0
#define DFT_STD_ORIGINAL_SETTING            1
#define DFT_STD_FULLHD_CMO216_H1L01         2
#define DFT_STD_WXGA_AU20_T200XW02          3
#define DFT_STD_FULLHD_LG47_LC470WU1        4


/*************** SONY DEMO ***************/
//#define DFT_SONY_FULLHD_CMO216_H1L01        22
#define DFT_SONY_WXGA_AU20_T200XW02         23


// =============================================================

#if( ENABLE_DEMO_FINE_TUNE )
  #ifndef DEMO_FINE_TUNE_SEL
    #define DEMO_FINE_TUNE_SEL      DFT_STD_FULLHD_CMO216_H1L01
  #endif
#else
  #ifndef DEMO_FINE_TUNE_SEL
    #define DEMO_FINE_TUNE_SEL      DFT_STD_ORIGINAL_SETTING
  #endif
#endif // #if( ENABLE_DEMO_FINE_TUNE )

// =============================================================
#if( DEMO_FINE_TUNE_SEL == DFT_STD_ORIGINAL_SETTING )
    #include "DFT_STD_ORIGINAL_SETTING.h"
#elif( DEMO_FINE_TUNE_SEL == DFT_STD_FULLHD_CMO216_H1L01 )
    #include "DFT_STD_FULLHD_CMO216_H1L01.h"
#elif( DEMO_FINE_TUNE_SEL == DFT_STD_WXGA_AU20_T200XW02 )
    #include "DFT_STD_WXGA_AU20_T200XW02.h"
#elif( DEMO_FINE_TUNE_SEL == DFT_STD_FULLHD_LG47_LC470WU1 )
    #include "DFT_STD_FULLHD_LG47_LC470WU1.h"

/*************** SONY DEMO ***************/
#elif( DEMO_FINE_TUNE_SEL == DFT_SONY_WXGA_AU20_T200XW02 )
    #include "DFT_SONY_WXGA_AU20_T200XW02.h"

#endif

extern BYTE *tAllGammaTab[3];
extern APIPNL_GAMMA_MAPPEING_MODE GAMMA_MAPPING_MODE;



/*****************************************************************************/
#endif // _DEMO_FINE_TUNE_H_

