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
/*************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 1 API
   API functions prototypes used by commands and properties
   FILE: Si2158_L1_API.h
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_1_build_9
   Revision: 0.1
   Date: March 20 2013
  (C) Copyright 2013, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef    _Si2158_L1_API_H_
#define    _Si2158_L1_API_H_

#include "silabs_L0_TV_Chassis.h"       

/* _demod_defines_insertion_start */
/* _demod_defines_insertion_point */

#include "Si2158_Commands.h"
#include "Si2158_Properties.h"
#include "Si2158_typedefs.h"
#include "Si2158_Commands_Prototypes.h"

#define NO_Si2158_ERROR                     0x00
#define ERROR_Si2158_PARAMETER_OUT_OF_RANGE 0x01
#define ERROR_Si2158_ALLOCATING_CONTEXT     0x02
#define ERROR_Si2158_SENDING_COMMAND        0x03
#define ERROR_Si2158_CTS_TIMEOUT            0x04
#define ERROR_Si2158_ERR                    0x05
#define ERROR_Si2158_POLLING_CTS            0x06
#define ERROR_Si2158_POLLING_RESPONSE       0x07
#define ERROR_Si2158_LOADING_FIRMWARE       0x08
#define ERROR_Si2158_LOADING_BOOTBLOCK      0x09
#define ERROR_Si2158_STARTING_FIRMWARE      0x0a
#define ERROR_Si2158_SW_RESET               0x0b
#define ERROR_Si2158_INCOMPATIBLE_PART      0x0c
/* _specific_error_value_insertion_start */
#define ERROR_Si2158_TUNINT_TIMEOUT         0x0d
#define ERROR_Si2158_xTVINT_TIMEOUT         0x0e
#define ERROR_Si2158_CRC_CHECK_ERROR        0x0f
/* _specific_error_value_insertion_point */

/* define PART_INTEGRITY_CHECKS (here) and the expected part number, chip rev, pmajor, pminor, and romid (in Si2158_L1_API.c) to use integrity checking */
#undef PART_INTEGRITY_CHECKS
/* chip rev constants for integrity checking */
extern const char Si2158_chiprev;
extern const char Si2158_part;
extern const char Si2158_partMajorVersion;
extern const char Si2158_partMinorVersion;
extern const char Si2158_partRomid;

unsigned char Si2158_L1_API_Init    (L1_Si2158_Context *api, int add);
unsigned char Si2158_L1_API_Patch   (L1_Si2158_Context *api, int iNbBytes, unsigned char *pucDataBuffer);
unsigned char Si2158_L1_CheckStatus (L1_Si2158_Context *api);
char*         Si2158_L1_API_ERROR_TEXT(unsigned char  error_code);
char*         Si2158_L1_API_TAG_TEXT  (void);

#define Si2158_TAG Si2158_L1_API_TAG_TEXT


#ifdef    Si2158_GET_PROPERTY_STRING
void Si2158_L1_FillPropertyStringText(L1_Si2158_Context *api, unsigned int prop_code, char *separator, char *msg);
#endif /* Si2158_GET_PROPERTY_STRING */

#endif /* _Si2158_L1_API_H_ */






