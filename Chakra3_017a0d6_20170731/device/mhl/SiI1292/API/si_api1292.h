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
//!file     si_api1292.h
//!brief    SiI1292 API functions.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009-2010, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#ifndef __SI_API1292_H__
#define __SI_API1292_H__
#include "./SiI1292/API/si_datatypes.h"
#include "./SiI1292/HAL/INC/si_hal.h"
//------------------------------------------------------------------------------
//  Compile-time build options
//------------------------------------------------------------------------------
//#define MSC_TESTER

#define API_DEBUG_CODE          0       // Set to 0 to eliminate debug print messages from code
                                        // Set to 1 to allow debug print messages in code
#define FPGA_DEBUG_CODE         0       // Set to 0 to for normal operation
                                        // Set to 1 to to work with FPGA test board
//#define CHIP_REVISION           ES10    // Set according to silicon revision

#define TIME_STAMP
//#define SWWA						// For software workaround
#define SWWA_21970					// SWWA for Bug#21970
#define SWWA_22334					// SWWA for Bug#22334

/* Control for amount of text printed by CEC commands.  */




#define CEC_NO_TEXT         0
#define CEC_NO_NAMES        1
#define CEC_ALL_TEXT        2           // Not compatible with IS_CDC==1 for 8051
#define INCLUDE_CEC_NAMES   CEC_ALL_TEXT

//------------------------------------------------------------------------------
//  Chip revision constants
//------------------------------------------------------------------------------

#define ES00       0
#define ES01       1
#define ES10       2

#define SII_MAX_PORT    1

//------------------------------------------------------------------------------
// Target System specific
//------------------------------------------------------------------------------
#define IS_RX                   1       // Set to 1 to if code is for Sink device
#define IS_TX                   0       // Set to 1 to if code is for Source device

    /* The following flags determine what feature set is compiled.  */

#define IS_CEC                  0// 1       // Set to 1 to enable CEC support //Keno20120301, base on RK1292 CEC to do. If don't want to use CEC functino, please define to 0.
#define IS_CBUS                1       // Set to 1 to enable MHL CBUS support
#define IS_IR               	0// 1       // Set to 1 to enable IR
#if IS_IR
//choose one, cannot both defined to 1.
#define IS_CP_Remote_Controller	1
#define IS_RK_Remote_Controller	0
#endif

//Keno20120306, add for reservation to SOC/Scaler use.
//CP/RK Remote Controller(RC) simulate SOC/Scaler RC to send CONTENT_ON/CONTENT_OFF to MHL Source.
//For MHL CTSv1.1, MHL Sink should not be tested it, therefore it can be disabled.
#define USE_Scaler_Standby_Mode 1

extern char strDeviceID [];

    // Debug Macros


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

   // MSG API   - For Debug purposes

#define MSG_ALWAYS              0x00
#define MSG_STAT                0x01
#define MSG_DBG                 0x02

//void    *malloc( uint16_si byteCount );
//void    free( void *pData );

#if (INCLUDE_CEC_NAMES > CEC_NO_TEXT)
    #include "CEC/si_apiCpi.h"
    #include "./SiI1292/MAIN/si_cpCEC.h"
#endif


//------------------------------------------------------------------------------
//
//  Other Manifest Constants
//
//------------------------------------------------------------------------------

#define DEM_POLLING_DELAY   50         // Main Loop Polling interval (ms)

typedef enum
{
    SI_DEV_INPUT_CONNECTED  = 1,
    SI_DEV_BOOT_STATE_MACHINE,
    SI_DEV_NVRAM,
    SI_DEV_IDH,
    SI_DEV_IDL,
    SI_DEV_REV,
    SI_DEV_ACTIVE_PORT
} SI_DEV_STATUS;

//-------------------------------------------------------------------------------
//  API Function Prototypes
//-------------------------------------------------------------------------------

uint8_si SI_DeviceStatus( uint8_si statusIndex );
enum
{
    SI_PWRUP_FAIL_DEVID_READ    = 0x00,
    SI_PWRUP_FAIL_BOOT          = 0x01,
    SI_PWRUP_FAIL_NVRAM_INIT    = 0x02,
    SI_PWRUP_BASE_ADDR_B0       = 0xB0,
    SI_PWRUP_BASE_ADDR_B2       = 0xB2

};

void    SI_DeviceEventMonitor( void );

enum
{
    SI_HPD_ACTIVE               = 0x00,     // HPD HI, HDCP, EDID, RX Term enabled
    SI_HPD_INACTIVE,                        // HPD LOW, HDCP, RX Term disabled
    SI_HPD_ACTIVE_EX,                       // EDID, RX Term enabled
    SI_HPD_INACTIVE_EX,                     // HPD HI, HDCP, EDID, RX Term disabled
    SI_HPD_TOGGLE,                  // Special use for CBUS connect
};

enum
{
    SI_TERM_HDMI                = 0x00,     // Enable for HDMI mode
    SI_TERM_MHL                 = 0x55,     // Enable for MHL mode
    SI_TERM_DISABLE             = 0xFF,     // Disable
};

#define RCP_DEBUG                       0

#define MHL_MAX_CHANNELS                1   // Number of MDHI channels

#define CBUS_CMD_RESPONSE_TIMEOUT       10      // In 100ms increments
#define CBUS_CONNECTION_CHECK_INTERVAL  40      // In 100ms increments

#define	CBUS_FW_COMMAND_TIMEOUT_SECS	1		// No response for 1 second means we hold off and move
#define	CBUS_FW_INTR_POLL_MILLISECS		50		// wait this to issue next status poll i2c read
#define	CBUS_FW_HOLD_OFF_SECS			2		// Allow bus to quieten down when ABORTs are received.

//Events definition
#define MHL_EVENT				0x01
#define HDMI_EVENT				0x02
#define TV_EVENT				0x04
#define RSEN_EVENT				0x08
#define SCDT_EVENT				0x10

//Wake up pulse definition
#define MIN_WAKE_PULSE_WIDTH_1		5
#define MAX_WAKE_PULSE_WIDTH_1		40
#define MIN_WAKE_PULSE_WIDTH_2		20
#define MAX_WAKE_PULSE_WIDTH_2		100

#define DEM_HDMI_VALID_TIME		               4  //500    	// HDMI valid time 500ms
#define DEM_RSEN_VALID_TIME				 8 //		1000		// RSEN Valid time 1s
#define DEM_MHL_WAIT_TIME					5 //	600			// MHL wait time after connection 600ms
#define DEM_MHL_RCP_TIMEOUT				8 //		1000		// MHL Rcp/Rap wait time	
#define DEM_MSC_MAX_REPLY_DELAY			4 //		500			// MSC Max reply delay for transfer done, 500ms
#define DEM_CEC_FEATURE_ABORT_MAX_DELAY  7 //		800	       // CEC Feature abort delay, 1000ms according to CEC spec Chapter7, but rcpk need within 1000ms, so set it 800ms 
#define DEM_CBUS_ABORT_WAIT				16 //		2000		// CBUS Abort wait time, 2000ms

#define TIMER_DEM_CEC_FEATURE_ABORT_MAX_DELAY		4//		(500  / DEM_POLLING_DELAY)	// CEC Feature abort delay, 500ms 

#endif  // __SI_API1292_H__

