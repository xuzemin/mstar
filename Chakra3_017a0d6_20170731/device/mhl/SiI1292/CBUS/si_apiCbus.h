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
//!file     si_apiCbus.h
//!brief    CBUS API
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2007-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#ifndef __SI_APICBUS_H__
#define __SI_APICBUS_H__

#include "./SiI1292/API/si_api1292.h"
#include "./SiI1292/MSC/si_apiRCP.h"
#include "./SiI1292/MSC/si_apiRAP.h"
#include "./SiI1292/MSC/si_apiMSC.h"
#include "./SiI1292/CBUS/si_RegioCbus.h"
#include "./SiI1292/CBUS/si_cbus_regs.h"
#include "./SiI1292/CBUS/si_cbusDefs.h"            // MHL 0.8 related definitions

#define SUPPORT_MSCMSG_IGNORE_LIST
//------------------------------------------------------------------------------
// API Manifest Constants
//------------------------------------------------------------------------------

#define CBUS_NOCHANNEL      0xFF
#define CBUS_NOPORT         0xFF
enum
{
    MHL_MSC_MSG_RCP             = 0x10,     // RCP sub-command
    MHL_MSC_MSG_RCPK            = 0x11,     // RCP Acknowledge sub-command
    MHL_MSC_MSG_RCPE            = 0x12,     // RCP Error sub-command
    MHL_MSC_MSG_RAP             = 0x20,     // RAP sub-command
    MHL_MSC_MSG_RAPK            = 0x21,     // RAP Acknowledge sub-command
};

enum
{
    MHL_MSC_MSG_NO_ERROR        = 0x00,     // RCP No Error
    MHL_MSC_MSG_ERROR_KEY_CODE  = 0x01,     // RCP Unrecognized Key Code
    MHL_MSC_MSG_BUSY            = 0x02,     // RCP Response busy
};

enum
{
    MHL_RCP_CMD_POLL            = 0x00,
    MHL_RCP_CMD_PLAY            = 0x01,
    MHL_RCP_CMD_PAUSE           = 0x02,
    MHL_RCP_CMD_STOP            = 0x03,
    MHL_RCP_CMD_FASTFORWARD     = 0x04,
    MHL_RCP_CMD_REWIND          = 0x05,
    MHL_RCP_CMD_CH_UP           = 0x06,
    MHL_RCP_CMD_CH_DOWN         = 0x07,
    MHL_RCP_CMD_MENU            = 0x10,
    MHL_RCP_CMD_EXIT            = 0x11,
    MHL_RCP_CMD_OK              = 0x12,
    MHL_RCP_CMD_LEFT            = 0x13,
    MHL_RCP_CMD_RIGHT           = 0x14,
    MHL_RCP_CMD_UP              = 0x15,
    MHL_RCP_CMD_DOWN            = 0x16,

    MHL_RCP_CMD_AUDIO_TRACK     = 0x20,
    MHL_RCP_CMD_SUBTITLES       = 0x21,

    MHL_RCP_CMD_PWR_ON          = 0x30,
    MHL_RCP_CMD_PWR_OFF         = 0x31,
    MHL_RCP_CMD_VOL_UP          = 0x32,
    MHL_RCP_CMD_VOL_DOWN        = 0x33,
    MHL_RCP_CMD_MUTE            = 0x34,
    MHL_RCP_CMD_UN_MUTE         = 0x35,
    MHL_RCP_CMD_ACTIVE_SOURCE   = 0x36,

    MHL_RCP_CMD_NUM_0           = 0x40,
    MHL_RCP_CMD_NUM_1           = 0x41,
    MHL_RCP_CMD_NUM_2           = 0x42,
    MHL_RCP_CMD_NUM_3           = 0x43,
    MHL_RCP_CMD_NUM_4           = 0x44,
    MHL_RCP_CMD_NUM_5           = 0x45,
    MHL_RCP_CMD_NUM_6           = 0x46,
    MHL_RCP_CMD_NUM_7           = 0x47,
    MHL_RCP_CMD_NUM_8           = 0x48,
    MHL_RCP_CMD_NUM_9           = 0x49,
    MHL_RCP_CMD_NUM_10          = 0x4A,
    MHL_RCP_CMD_NUM_11          = 0x4B,
    MHL_RCP_CMD_NUM_12          = 0x4C,

	MHL_RCP_CMD_KEY_RELEASED	= 0x80,
};

enum
{
    MSC_WRITE_STAT              = 0x60,     // Two commands, one opCode
    MSC_SET_INT                 = 0x60,     // Two commands, one opCode
    MSC_READ_DEVCAP             = 0x61,
    MSC_GET_STATE               = 0x62,
    MSC_GET_VENDOR_ID           = 0x63,
    MSC_SET_HPD                 = 0x64,
    MSC_CLR_HPD                 = 0x65,
    MSC_SET_CEC_CAP_ID          = 0x66,
    MSC_GET_CEC_CAP_ID          = 0x67,
    MSC_MSG                     = 0x68,
    MSC_GET_VS_ABORT            = 0x69,
    MSC_GET_DDC_ABORT           = 0x6A,
    MSC_GET_MSC_ABORT           = 0x6B,
    MSC_WRITE_BURST             = 0x6C,
};

enum
{
    CBUS_TASK_IDLE,
    CBUS_TASK_TRANSLATION_LAYER_DONE,
    CBUS_TASK_WAIT_FOR_RESPONSE,
};

//
// CBUS module reports these error types
//
typedef enum
{
    STATUS_SUCCESS = 0,
    ERROR_CBUS_CAN_RETRY,
    ERROR_CBUS_ABORT,
    ERROR_CBUS_TIMEOUT,
    ERROR_CBUS_LINK_DOWN,
    ERROR_INVALID,
    ERROR_INIT,
    ERROR_WRITE_FAILED,
    ERROR_NO_HEARTBEAT,
    ERROR_WRONG_DIRECTION,
    ERROR_QUEUE_FULL,
    ERROR_MSC_MSG,
    ERROR_INVALID_MSC_CMD,
    ERROR_RET_HANDLER,
} CBUS_SOFTWARE_ERRORS_t;

typedef enum
{
    CBUS_IDLE           = 0,    // BUS idle
    CBUS_SENT,                  // Command sent
    CBUS_XFR_DONE,              // Translation layer complete
    CBUS_WAIT_RESPONSE,         // Waiting for response
} CBUS_STATE_t;

typedef enum
{
    CBUS_REQ_IDLE       = 0,
    CBUS_REQ_PENDING,           // Request is waiting to be processed
    CBUS_REQ_WAITING,			// Request is waiting response
} CBUS_REQ_t;

//------------------------------------------------------------------------------
// API typedefs
//------------------------------------------------------------------------------

//
// structure to hold command details from upper layer to CBUS module
// 
typedef bool_si (*dataRetHandler_t)(uint8_si, uint8_si);	

typedef struct 
{
    uint8_si reqStatus;                      			// REQ_IDLE, REQ_PENDING, REQ_WAITING
    uint8_si command;                        			// MSC command
    uint8_si offsetData;                     			// Offset of register on CBUS
    uint8_si length;                         			// Only applicable to write burst. ignored otherwise.
	uint8_si msgData[MHL_MAX_BUFFER_SIZE];   			// Pointer to message data area.
	dataRetHandler_t dataRetHandler;			// Data return handler for MSC commands
	uint32_si timeout;									// timing control
	uint32_si base_time;									// record the base time
	bool_si  timer_set;									// flag for enable/disable timer
	uint8_si retry;										// to define whether this command has been retried, default false
	bool_si  cecReq;										// define whether the Req is from Cec
	bool_si  vip;										// define whether the Req is a high priority request
} cbus_out_queue_t;

typedef struct 
{
    uint8_si reqStatus;                      			// REQ_IDLE, REQ_PENDING, REQ_WAITING
    uint8_si command;                        			// RAP or  RCP opcode
	uint8_si msgData;                     				// RAP or RCP data
	uint32_si timeout;									// timing control
	uint32_si base_time;									// record the base time
	bool_si  timer_set;									// flag for enable/disable timer
} cbus_in_queue_t;
 
#define CBUS_MAX_COMMAND_QUEUE     2

#define MSC_MSG_MAX_IGNORE_CMD		0x80

typedef struct
{
    bool_si  connected;      							// True if a connected MHL port
	bool_si	connect_wait;								// True if wait enough time to send any command after cbus connection
    bool_si  hpd_state;									// For HPD
    bool_si  grt_wrt;									// For grant write scratch pad
    bool_si  path_enable;								// For path enable
    bool_si	connect_ready;								// For Connected Ready Register
	bool_si  dcap_rdy;									// For Peer Dcap Reg ready
    uint8_si	read_info;									// For read peer info
	bool_si  abort_wait;									// For ABORT_WAIT
	uint32_si base_time;									// record the base time	
	uint8_si o_activeIndex;    							// Active queue entry for sending command queue.
	uint8_si i_activeIndex;								// Active queue entry for sending command queue.
	cbus_out_queue_t  o_queue[ CBUS_MAX_COMMAND_QUEUE ];// sending command queue (RAP/RCP/MSC)
	cbus_in_queue_t   i_queue[ CBUS_MAX_COMMAND_QUEUE ];// receiving command queue (RAP/RCP)
	// CBUS_MAX_COMMAND_QUEUE = 2, reason for i_queue is timeout may cause receving 2 or more commands
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
	bool_si	o_mscmsg_ignore_list[ MSC_MSG_MAX_IGNORE_CMD ];	// sending msc msg ignore list
	bool_si	i_mscmsg_ignore_list[ MSC_MSG_MAX_IGNORE_CMD ];	// receiving msc msg ignore list
#endif
	bool_si	rcp_support;								// peer RCP_SUPPORT
	bool_si	rap_support;								// peer RAP_SUPPORT
} cbusChannelState_t;

//typedef enum
enum
{
    KEY_NOT_IN_IGNORELIST = 0x00,
    KEY_IN_IGNORELIST = 0x01,
    KEY_STATUS_NOT_INITLIAED = 0x20,
};

typedef enum
{
    CBUS_IN       = 0,	// Receiving
    CBUS_OUT,           // Sending
    CBUS_INOUT,			// Both
} CBUS_Direction_t;


#define DCAP_READ_DONE  0x80
#define DCAP_ITEM_READ_DOING 0x40
#define DCAP_ITEM_INDEX_MASK 0x3F

//------------------------------------------------------------------------------
// API Function Templates
//------------------------------------------------------------------------------

bool_si      SI_CbusInitialize( void );
void 		SI_CbusInitDevCap( uint8_si channel );
uint8_si     SI_CbusHandler( uint8_si channel );
uint8_si     SI_CbusPortToChannel( uint8_si port );

    /* CBUS Request functions.      */

uint8_si 	SI_CbusIQReqStatusCheck(uint8_si channel);
uint8_si 	SI_CbusOQReqStatusCheck(uint8_si channel);
uint8_si		SI_CbusIQReqStatus ( uint8_si channel );			// IQ Req->reqStatus
uint8_si 	SI_CbusOQReqStatus ( uint8_si channel );		// OQ Req->reqStatus
uint8_si 	SI_CbusIQReqCmd ( uint8_si channel );			// IQ Req->command
uint8_si 	SI_CbusOQReqCmd( uint8_si channel );			// OQ Req->command
uint8_si 	SI_CbusIQReqData ( uint8_si channel );			// IQ Req->Data
uint8_si 	SI_CbusOQReqData0( uint8_si channel );			// OQ Req->msgData[0]
uint8_si		SI_CbusOQReqData1( uint8_si channel );			// OQ Req->msgData[1]
cbus_in_queue_t *SI_CbusIQActiveReq ( uint8_si channel );	// IQ pReq
cbus_out_queue_t *SI_CbusOQActiveReq( uint8_si channel );	// OQ pReq
uint32_si 	SI_CbusIQReqTimeout ( uint8_si channel );		// IQ Req->timeout
uint32_si 	SI_CbusOQReqTimeout( uint8_si channel );		// OQ Req->timeout
uint8_si 	SI_CbusOQReqRetry( uint8_si channel );			// OQ Req->retry
void 		SI_CbusOQReduceReqRetry( uint8_si channel );
void 		SI_CbusIQCleanActiveReq( uint8_si channel );	// Clean IQ Req
void 		SI_CbusOQCleanActiveReq( uint8_si channel );	// Clean OQ Req
bool_si 		SI_CbusOQGetCecReq( uint8_si channel );
void 		SI_CbusOQSetCecReq( uint8_si channel , bool_si value );
void 		SI_CbusOQSetReqStatus( uint8_si channel, uint8_si reqStatus );
void 		SI_CbusOQSetReqTimeout( uint8_si channel, uint32_si value);
uint8_si 	SI_CbusOQReqData2( uint8_si channel );
void 		SI_CbusIQSetReqStatus( uint8_si channel, uint8_si reqStatus );
uint8_si 	SI_CbusPushReqInOQ( uint8_si channel, cbus_out_queue_t *pReq, bool_si vip );	// Push Req into OQ

#ifdef SUPPORT_MSCMSG_IGNORE_LIST
void 		SI_CbusPushKeytoIgnoreList(uint8_si channel, uint8_si keyID, uint8_si direction);
void        SI_CbusUpdateIgnoreListInitStatus(uint8_si channel, uint8_si keyID, uint8_si direction);
bool_si 		SI_RcpIgnoreKeyIDCheck(uint8_si channel, uint8_si keyID, uint8_si direction);
void		SI_CbusResetMscMsgIgnoreList(uint8_si channel, uint8_si direction);
#endif

#ifdef SUPPORT_MSCMSG_IGNORE_LIST
bool_si 		SI_CbusKeyIDCheck(uint8_si channel, uint8_si keyID, uint8_si direction);
#else
bool_si 		SI_CbusKeyIDCheck(uint8_si keyID, uint8_si direction);
#endif

void 		SI_CbusCecRetHandler(uint8_si channel, bool_si result);
uint8_si 	SI_CbusMscMsgTimeoutHandler(uint8_si channel, uint8_si direction);
uint8_si CbusWriteCommand ( int channel, cbus_out_queue_t *pReq  );
uint8_si CbusProcessFailureInterrupts ( uint8_si channel, uint8_si intStatus, uint8_si inResult );

    /* CBUS Channel functions.      */

uint8_si     SI_CbusChannelToPort( uint8_si channel );
uint8_si     SI_CbusChannelStatus( uint8_si channel );
bool_si      SI_CbusChannelConnected( uint8_si channel );
void 		SI_CbusInitParam( uint8_si channel );
bool_si 		SI_CbusGetConnectWait( uint8_si channel );
bool_si 		SI_CbusGetHpdState( uint8_si channel );
bool_si 		SI_CbusGetGrtWrt( uint8_si channel );
void 		SI_CbusSetGrtWrt( uint8_si channel , bool_si value );
bool_si 		SI_CbusGetPathEnable( uint8_si channel );
bool_si 		SI_CbusGetConnectReady( uint8_si channel );
bool_si 		SI_CbusGetAbortWait( uint8_si channel );
bool_si 		SI_CbusGetDcapRdy( uint8_si channel );
bool_si 		SI_CbusGetReadInfo( uint8_si channel );
void 		SI_CbusSetConnectWait( uint8_si channel , bool_si value );
void 		SI_CbusSetHpdState( uint8_si channel , bool_si value );
void 		SI_CbusSetPathEnable( uint8_si channel , bool_si value );
void 		SI_CbusSetConnectReady( uint8_si channel , bool_si value );
void 		SI_CbusSetAbortWait( uint8_si channel , bool_si value );
void 		SI_CbusSetDcapRdy( uint8_si channel , bool_si value );
void 		SI_CbusSetReadInfo( uint8_si channel , uint8_si value );
void 		SI_CbusSetRcpSupport( uint8_si channel , bool_si value );
void 		SI_CbusSetRapSupport( uint8_si channel , bool_si value );
//uint8_si 		SI_CbusIgnoreListCheck(uint8_si channel, uint8_si keyID, uint8_si direction);

    /* RCP Message send functions.  */

uint8_si 	SI_CbusMscMsgTransferDone( uint8_si channel );
bool_si      SI_CbusUpdateBusStatus( uint8_si channel );


#endif  // __SI_APICBUS_H__

