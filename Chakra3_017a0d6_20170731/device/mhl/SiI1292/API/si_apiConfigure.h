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
//!file     si_apiConfigure.h
//!brief    Configure the SiI1292 API for a specific system design.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009-2010, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#ifndef __SI_APICONFIGURE_H__
#define __SI_APICONFIGURE_H__
#include "./SiI1292/API/si_datatypes.h"
#include "./SiI1292/API/si_regio.h"
#include "./SiI1292/API/si_api1292.h"


//------------------------------------------------------------------------------
//  Compile-time build options
//------------------------------------------------------------------------------

#define API_DEBUG_CODE          0       // Set to 0 to eliminate debug print messages from code
                                        // Set to 1 to allow debug print messages in code
#define FPGA_DEBUG_CODE         0       // Set to 0 to for normal operation
                                        // Set to 1 to to work with FPGA test board
//#define CHIP_REVISION           ES10    // Set according to silicon revision
#define MHL_WORKAROUND          1       // Set to 1 to enable MHL workaround

#define DEM_POLLING_DELAY       100     // Main Loop Polling interval (ms)

#define IS_RX                   1       // Set to 1 to if code is for Sink device
#define IS_TX                   0       // Set to 1 to if code is for Source device


    /* The following flags determine what feature set is compiled.  */

#define IS_CEC                 0// 1       // Set to 1 to enable CEC support
#define IS_CBUS                 1       // Set to 1 to enable MHL CBUS support
#define IS_IR               0//	1       // Set to 1 to enable IR


//------------------------------------------------------------------------------
//  Device-specific constants
//------------------------------------------------------------------------------

#define ES00            0
#define ES01            1
#define ES10            2

#define SII_MAX_PORT    1

//------------------------------------------------------------------------------
// Target System specific
//------------------------------------------------------------------------------

#if (API_DEBUG_CODE==1)
    #include <stdio.h>
#endif

extern char g_strDeviceID [];

#if 0
    // Debug Macros
extern uint32_si g_pass;

#if (API_DEBUG_CODE==1)
    extern  uint8_si     g_halMsgLevel;

    #ifndef DEBUG_PRINT
	#ifdef TIME_STAMP
    	#define DEBUG_PRINT(l,x)        if (l<=g_halMsgLevel) {printf("[%d]: ", (int)g_pass);  printf x;}
	#else
        #define DEBUG_PRINT(l,x)        if (l<=g_halMsgLevel) printf x
	#endif
    #endif
    #define _DEBUG_(x)              x

#else
    #ifndef DEBUG_PRINT
        #define DEBUG_PRINT(l,x)
    #endif
    #define _DEBUG_(x)
#endif
#endif
    // HDMI port on board that is connected to ARC 

#define HEAC_ARC_PORT                   1

    // MSG API   - For Debug purposes

#define MSG_ALWAYS              0x00
#define MSG_STAT                0x01
#define MSG_DBG                 0x02

    // Timer API - Target system must create these functions
#if 0
#define ELAPSED_TIMER               0xFF
#define ELAPSED_TIMER1              0xFE
#define TIMER_0                     0   // DO NOT USE - reserved for TimerWait()
#define TIMER_POLLING               1   // Reserved for main polling loop
#define TIMER_2                     2   // Available
#define TIMER_3                     3   // Available
void        HalTimerSet( uint8_si timer, uint16_si m_sec );
void        HalTimerWait( uint16_si m_sec );
uint16_si    HalTimerElapsed( uint8_si index );
uint8_si     HalTimerExpired( uint8_si timer );
#endif

//void    *malloc( uint16_si byteCount );
//void    free( void *pData );

//------------------------------------------------------------------------------
// Debug Trace
//------------------------------------------------------------------------------

#if (API_DEBUG_CODE==1)
    #define DF1_SW_HDCPGOOD         0x01
    #define DF1_HW_HDCPGOOD         0x02
    #define DF1_SCDT_INT            0x04
    #define DF1_SCDT_HI             0x08
    #define DF1_SCDT_STABLE         0x10
    #define DF1_HDCP_STABLE         0x20
    #define DF1_NON_HDCP_STABLE     0x40
    #define DF1_RI_CLEARED          0x80

    #define DF2_MP_AUTH             0x01
    #define DF2_MP_DECRYPT          0x02
    #define DF2_HPD                 0x04
    #define DF2_HDMI_MODE           0x08
    #define DF2_MUTE_ON             0x10
    #define DF2_PORT_SWITCH_REQ     0x20
    #define DF2_PIPE_PWR            0x40
    #define DF2_PORT_PWR_CHG        0x80

typedef struct
{
    char    debugTraceVerStr[5];    // Changed each time the debug labels are
                                    // changed to keep track of what values
                                    // a specific version is monitoring.
    uint8_si demFlags1;
    uint8_si demFlags2;
} DEBUG_DATA_t;

extern DEBUG_DATA_t g_dbg;

#endif

//------------------------------------------------------------------------------
//  CEC
//------------------------------------------------------------------------------

/* Control for amount of text printed by CEC commands.  */

//#if (INCLUDE_CEC_NAMES > CEC_NO_TEXT)
    #include "CEC/si_apiCpi.h"
    #include "./SiI1292/MAIN/si_cpCEC.h"
//#endif

//------------------------------------------------------------------------------
//  MHL/CBUS
//------------------------------------------------------------------------------

#define RCP_DEBUG                       0

#define MHL_MAX_CHANNELS                1   // Number of MDHI channels

#define CBUS_CMD_RESPONSE_TIMEOUT       10      // In 100ms increments
#define CBUS_CONNECTION_CHECK_INTERVAL  40      // In 100ms increments

#define	CBUS_FW_COMMAND_TIMEOUT_SECS	1		// No response for 1 second means we hold off and move
#define	CBUS_FW_INTR_POLL_MILLISECS		50		// wait this to issue next status poll i2c read
#define	CBUS_FW_HOLD_OFF_SECS			2		// Allow bus to quieten down when ABORTs are received.

//------------------------------------------------------------------------------
//  API_SWITCH definitions
//------------------------------------------------------------------------------

#define DEM_HDMI_VALID_TIME		(500  / DEM_POLLING_DELAY)    	// HDMI valid time 500ms
#define DEM_RSEN_VALID_TIME		(1000 / DEM_POLLING_DELAY)		// RSEN Valid time 1s
#define DEM_MHL_WAIT_TIME		(600  / DEM_POLLING_DELAY)		// MHL wait time after connection 600ms
#define DEM_MHL_RCP_TIMEOUT		(1000 / DEM_POLLING_DELAY)		// MHL Rcp/Rap wait time	
#define DEM_MSC_MAX_REPLY_DELAY	(500  / DEM_POLLING_DELAY)		// MSC Max reply delay for transfer done, 500ms
#define DEM_CEC_FEATURE_ABORT_MAX_DELAY		(500  / DEM_POLLING_DELAY)	// CEC Feature abort delay, 500ms 

#endif  // __SI_APICONFIGURE_H__
