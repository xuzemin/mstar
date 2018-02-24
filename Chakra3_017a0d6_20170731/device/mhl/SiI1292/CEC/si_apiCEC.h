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
//***************************************************************************
//!file     si_apicec.h
//!brief    Silicon Image CEC API
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#ifndef __SI_APICEC_H__
#define __SI_APICEC_H__
#include "./SiI1292/API/si_datatypes.h"
#include "./SiI1292/CEC/si_apiCpi.h"
#include "./SiI1292/CEC/si_cpi_regs.h"
#include "./SiI1292/CEC/si_cec_enums.h"
#if IS_CEC

//-------------------------------------------------------------------------------
// CPI Enums, typedefs, and manifest constants
//-------------------------------------------------------------------------------

#define MAKE_SRCDEST( src, dest)    (( src << 4) | dest )

#define SII_NUMBER_OF_PORTS         1 //for Jubilee
#define SII_EHDMI_PORT              (1)

enum 
{
    SI_CECTASK_IDLE,
    SI_CECTASK_ENUMERATE,
    SI_CECTASK_TXREPORT,	
    SI_CECTASK_ONETOUCHPLAY,
	SI_CECTASK_SETOSDNAME,
};

typedef struct
{
    uint8_si deviceType;     // 0 - Device is a TV.
                            // 1 - Device is a Recording device
                            // 2 - Device is a reserved device
                            // 3 - Device is a Tuner
                            // 4 - Device is a Playback device
                            // 5 - Device is an Audio System
    uint8_si  cecLA;         // CEC Logical address of the device.
    uint16_si cecPA;         // CEC Physical address of the device.
} CEC_DEVICE;

extern uint8_si  g_cecAddress;       // Initiator
extern uint16_si g_cecPhysical;      // For TV, the physical address is 0.0.0.0

//------------------------------------------------------------------------------
// Data
//------------------------------------------------------------------------------

extern CEC_DEVICE   g_childPortList [SII_NUMBER_OF_PORTS];

//------------------------------------------------------------------------------
// API Function Templates
//------------------------------------------------------------------------------

void        si_CecSendMessage( uint8_si opCode, uint8_si dest );
void        SI_CecSendUserControlPressed( uint8_si keyCode );
void        SI_CecSendUserControlReleased( void );
bool_si 		SI_CecOneTouchPlay ( void );
bool_si        SI_CecEnumerate( void );
uint8_si     SI_CecHandler( uint8_si currentPort, bool_si returnTask );
uint8_si     SI_CecGetPowerState( void );
void        SI_CecSetPowerState( uint8_si newPowerState );
void        SI_CecSourceRemoved( uint8_si portIndex );
uint16_si    SI_CecGetDevicePA( void );
void        SI_CecSetDevicePA( uint16_si devPa );
bool_si        SI_CecInit( void );
uint8_si 	SI_CecMscMsgConvertHandler(SI_CpiData_t *pCpi, uint8_si channel);
#endif
#endif // __SI_APICEC_H__
