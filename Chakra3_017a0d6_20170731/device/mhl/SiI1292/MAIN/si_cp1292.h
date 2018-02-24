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
//!file     si_cp1292.h
//!brief    CP 1292 FPGA/Starter Kit firmware main module.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009-2010, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#ifndef __SI_CP1292_H__
#define __SI_CP1292_H__
#include <stdio.h>
#include "./SiI1292/HAL/INC/si_hal.h"
#include "./SiI1292/API/si_regio.h"
#include "./SiI1292/API/si_api1292.h"
#include "EDID/si_apiEdid.h"

//#include <si_apiConfigure.h>


//------------------------------------------------------------------------------
//
//  Compile-time build options
//
//------------------------------------------------------------------------------

#define FPGA_BUILD          0           // 1 == FPGA, 0 == Silicon

//------------------------------------------------------------------------------
//
//  CP 1292 Starter Kit Manifest Constants
//
//------------------------------------------------------------------------------

//#define DEM_POLLING_DELAY   100         // Main Loop Polling interval (ms)


//-------------------------------------------------------------------------------
//  Chip Mode for CP 1292
//-------------------------------------------------------------------------------

//typedef enum
enum
{
	HDMI = 0,
	MHL
};

//------------------------------------------------------------------------------
//  typedefs
//------------------------------------------------------------------------------

typedef struct
{
    uint8_si portSelect;
    uint8_si cecEnabled;
    uint8_si irEnabled;
    uint8_si edidLoad;
	bool_si	standby_mode;

} SI_CP1292Config_t;

//------------------------------------------------------------------------------
//  Global Data
//------------------------------------------------------------------------------

extern SI_CP1292Config_t    g_data;

extern uint8_si 				g_currentInputMode;

extern bool_si 				g_MHL_Source_Connected;

extern bool_si 				g_HDMI_Source_Connected;
extern bool_si				g_HDMI_Source_Valid;

extern bool_si 				g_HPD_IN;
extern bool_si 				g_TX_RSEN;
extern bool_si 				g_TX_RSEN_Valid;

extern bool_si                 g_deviceInterrupt;
extern uint8_si              g_dbgPrinted;

extern uint8_si PeerDevCap[16];

extern uint32_si 			timer_count;

extern bool_si		g_RC5_Key_UP;
//-------------------------------------------------------------------------------
// Board-specific GPIO and sbit assigments
//-------------------------------------------------------------------------------

#define DEV_INT                 //P3^2        // 1292 Interrupt pin
#define SI_STANDBY_MODE			//P0^7		// For testing wakeup pulse detection
#define LED7_GREEN				//P2^0
#define LED7_AMBER				//P2^1
#define LED2_MHL				//P2^4
#define LED3_HDMI				//P2^5


#define GPIO_SET( gpioNum )        // gpio_##gpioNum = 1
#define GPIO_CLR( gpioNum )        // gpio_##gpioNum = 0
#define GPIO_BIT( gpioNum )        // gpio_##gpioNum
#define GPIO_READ( gpioNum )       // gpio_##gpioNum

#if 0
sbit gpio_DEV_INT               = DEV_INT;            // 1292 Interrupt pin
sbit gpio_STANDBY_MODE			= STANDBY_MODE;
sbit gpio_LED7_GREEN			= LED7_GREEN;
sbit gpio_LED7_AMBER			= LED7_AMBER;
sbit gpio_LED2_MHL				= LED2_MHL;
sbit gpio_LED3_HDMI				= LED3_HDMI;
#endif
//-------------------------------------------------------------------------------
//  Function Prototypes
//-------------------------------------------------------------------------------

bool_si CpCheckExternalRequests( void );
void CpReadInitialSettings( void );
#if (FPGA_BUILD == 0)
void CpCheckOTPRev( void );
#endif // FPGA_BUILD == 0
void CpBlinkTilReset( uint8_si leds );

bool_si CpIrHandler( void );

// For MHL cable detect and wakeup pulse detect
bool_si CpCheckStandbyMode( void );
bool_si CpCableDetect( void );
char CpWakePulseDetect( void );
extern void Mhlfuntion_inition(void);
extern void mhlfunction ( void );



    /* si_cpCbus.c      */

void    CpCbusHandler( void );
void    CpCbusInitialize( void );

#endif  // __SI_CP1292_H__

