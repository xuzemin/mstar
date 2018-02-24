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
/*
  Copyright (C) 2006-2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmUnitParams.h
 *
 *                %version: CFR_FEAP#4 %
 *
 * \date          %modify_time%
 *
 * \author        Christophe CAZETTES
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 *
 */

#ifndef _TM_UNIT_PARAMS_H
#define _TM_UNIT_PARAMS_H

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/


/******************************************************************************/
/** \brief "These macros map to tmUnitSelect_t variables parts"
*
******************************************************************************/

#define UNIT_VALID(_tUnIt)                      (((_tUnIt)&0x80000000)==0)

#define UNIT_PATH_INDEX_MASK                    (0x0000001F)
#define UNIT_PATH_INDEX_POS                     (0)

#define UNIT_PATH_TYPE_MASK                     (0x000003E0)
#define UNIT_PATH_TYPE_POS                      (5)

#define UNIT_PATH_CONFIG_MASK                   (0x0003FC00)
#define UNIT_PATH_CONFIG_POS                    (10)

#define UNIT_SYSTEM_INDEX_MASK                  (0x007C0000)
#define UNIT_SYSTEM_INDEX_POS                   (18)

#define UNIT_SYSTEM_CONFIG_MASK                 (0x7F800000)
#define UNIT_SYSTEM_CONFIG_POS                  (23)




#define UNIT_PATH_INDEX_GET(_tUnIt)             ((_tUnIt)&UNIT_PATH_INDEX_MASK)
#define UNIT_PATH_INDEX_VAL(_val)               (((_val)<<UNIT_PATH_INDEX_POS)&UNIT_PATH_INDEX_MASK)
#define UNIT_PATH_INDEX_SET(_tUnIt, _val)       ( ((_tUnIt)&~UNIT_PATH_INDEX_MASK) | UNIT_PATH_INDEX_VAL(_val) )
#define UNIT_PATH_INDEX_VAL_GET(_val)           (UNIT_PATH_INDEX_VAL(UNIT_PATH_INDEX_GET(_val)))

#define UNIT_PATH_TYPE_GET(_tUnIt)              (((_tUnIt)&UNIT_PATH_TYPE_MASK) >> UNIT_PATH_TYPE_POS)
#define UNIT_PATH_TYPE_VAL(_val)                (((_val)<<UNIT_PATH_TYPE_POS)&UNIT_PATH_TYPE_MASK)
#define UNIT_PATH_TYPE_SET(_tUnIt, _val)        ( ((_tUnIt)&~UNIT_PATH_TYPE_MASK) | UNIT_PATH_TYPE_VAL(_val) )
#define UNIT_PATH_TYPE_VAL_GET(_val)            (UNIT_PATH_TYPE_VAL(UNIT_PATH_TYPE_GET(_val)))


#define UNIT_PATH_CONFIG_GET(_tUnIt)            (((_tUnIt)&UNIT_PATH_CONFIG_MASK) >> UNIT_PATH_CONFIG_POS)
#define UNIT_PATH_CONFIG_VAL(_val)              (((_val)<<UNIT_PATH_CONFIG_POS)&UNIT_PATH_CONFIG_MASK)
#define UNIT_PATH_CONFIG_SET(_tUnIt, _val)      ( ((_tUnIt)&~UNIT_PATH_CONFIG_MASK) | UNIT_PATH_CONFIG_VAL(_val) )
#define UNIT_PATH_CONFIG_VAL_GET(_val)          (UNIT_PATH_CONFIG_VAL(UNIT_PATH_CONFIG_GET(_val)))

#define UNIT_SYSTEM_INDEX_GET(_tUnIt)           (((_tUnIt)&UNIT_SYSTEM_INDEX_MASK) >> UNIT_SYSTEM_INDEX_POS)
#define UNIT_SYSTEM_INDEX_VAL(_val)             (((_val)<<UNIT_SYSTEM_INDEX_POS)&UNIT_SYSTEM_INDEX_MASK)
#define UNIT_SYSTEM_INDEX_SET(_tUnIt, _val)     ( ((_tUnIt)&~UNIT_SYSTEM_INDEX_MASK) | UNIT_SYSTEM_INDEX_VAL(_val) )
#define UNIT_SYSTEM_INDEX_VAL_GET(_val)         (UNIT_SYSTEM_INDEX_VAL(UNIT_SYSTEM_INDEX_GET(_val)))

#define UNIT_SYSTEM_CONFIG_GET(_tUnIt)          (((_tUnIt)&UNIT_SYSTEM_CONFIG_MASK) >> UNIT_SYSTEM_CONFIG_POS)
#define UNIT_SYSTEM_CONFIG_VAL(_val)            (((_val)<<UNIT_SYSTEM_CONFIG_POS)&UNIT_SYSTEM_CONFIG_MASK)
#define UNIT_SYSTEM_CONFIG_SET(_tUnIt, _val)    ( ((_tUnIt)&~UNIT_SYSTEM_CONFIG_MASK) | UNIT_SYSTEM_CONFIG_POS(_val) )
#define UNIT_SYSTEM_CONFIG_VAL_GET(_val)        (UNIT_SYSTEM_CONFIG_VAL(UNIT_SYSTEM_CONFIG_GET(_val)))


#define GET_WHOLE_SYSTEM_TUNIT(_tUnIt)          (UNIT_SYSTEM_CONFIG_VAL_GET(_tUnIt)|UNIT_SYSTEM_INDEX_VAL_GET(_tUnIt))

#define GET_SYSTEM_TUNIT(_tUnIt)                (UNIT_SYSTEM_CONFIG_VAL_GET(_tUnIt)|UNIT_SYSTEM_INDEX_VAL_GET(_tUnIt)|UNIT_PATH_INDEX_VAL_GET(_tUnIt))

#define GET_INDEX_TUNIT(_tUnIt)                 (UNIT_SYSTEM_INDEX_VAL_GET(_tUnIt)|UNIT_PATH_INDEX_VAL_GET(_tUnIt))

#define GET_INDEX_TYPE_TUNIT(_tUnIt)            (UNIT_SYSTEM_INDEX_VAL_GET(_tUnIt)|UNIT_PATH_INDEX_VAL_GET(_tUnIt)|UNIT_PATH_TYPE_VAL_GET(_tUnIt))

#define XFER_DISABLED_FLAG                      (UNIT_PATH_CONFIG_VAL(0x80))
#define GET_XFER_DISABLED_FLAG_TUNIT(_tUnIt)    (((_tUnIt)&XFER_DISABLED_FLAG)!=0)


/*============================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* _TM_UNIT_PARAMS_H */

