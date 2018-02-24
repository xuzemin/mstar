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
/******************************************************************************
 *
 * Copyright 2010, Silicon Image, Inc.  All rights reserved.  
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of: Silicon Image, Inc., 1060
 * East Arques Avenue, Sunnyvale, California 94085
 * 
 *****************************************************************************/
/**
 * @file si_apiCbus.c
 *
 * Cbus function of SiI1292, including Cbus driver and Cbus Req Queue operation
 * 
 * $Author: Silicon Image, firmware team
 * $Rev: 0.3
 * $Date: Apr. 2010
 *
 *****************************************************************************/

/***** #include statements ***************************************************/

#include "string.h"
#include "./SiI1292/CBUS/si_apiCbus.h"
#include "si_cbus.h"
#include "./SiI1292/MAIN/si_cp1292.h"
#if (IS_CBUS == 1 )

/***** local variable declarations *******************************************/

static cbusChannelState_t l_cbus[MHL_MAX_CHANNELS];

static uint8_si l_PortToChannel[SII_MAX_PORT]            = { CBUS_NOCHANNEL} ;
static uint8_si l_ChannelToPort[MHL_MAX_CHANNELS]        = { CBUS_NOPORT };

static bool_si rcp_reserved_list[RCP_KEYCODE_NUM] = 
{
/*  00    01    02   03    04    05    06    07   08     09    0A    0B    0C    0D    0E   0F */
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,		// 00
   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,		// 01
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,		// 02
   0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,		// 03
   1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,		// 04
   0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,		// 05
   0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,		// 06
   1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,		// 07
};


/***** local function prototypes *********************************************/

uint8_si CbusWriteCommand ( int channel, cbus_out_queue_t *pReq  );

/***** public functions *******************************************************/

/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get In-queue's active Req's Status
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return reqStatus
 *  @retval             0, CBUS_REQ_IDLE
 *  @retval             1, CBUS_REQ_PENDING
 *  @retval             2, CBUS_REQ_WAITING
 * 
 *****************************************************************************/
uint8_si SI_CbusIQReqStatus ( uint8_si channel )
{
    return ( l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex].reqStatus );
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Set In-queue's active Req's Status
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          reqStatus		The value will be set in active Req's Status
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusIQSetReqStatus( uint8_si channel, uint8_si reqStatus )
{
	l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex].reqStatus = reqStatus;
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req's Status
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return reqStatus
 *  @retval             0, CBUS_REQ_IDLE
 *  @retval             1, CBUS_REQ_PENDING
 *  @retval             2, CBUS_REQ_WAITING
 * 
 *****************************************************************************/
uint8_si SI_CbusOQReqStatus ( uint8_si channel )
{
    return ( l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].reqStatus );
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Set Out-queue's active Req's Status
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          reqStatus		The value will be set in active Req's Status
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusOQSetReqStatus( uint8_si channel, uint8_si reqStatus )
{
	l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].reqStatus = reqStatus;
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get In-queue's active Req's command
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the opcode in MSC_MSG
 *  @retval             0x10, MHL_MSC_MSG_RCP
 *  @retval             0x11, MHL_MSC_MSG_RCPK
 *  @retval             0x12, MHL_MSC_MSG_RCPE
 *  @retval             0x20, MHL_MSC_MSG_RAP
 *  @retval             0x21, MHL_MSC_MSG_RAPK
 * 
 *****************************************************************************/
uint8_si SI_CbusIQReqCmd ( uint8_si channel )
{
    return ( l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex].command);
}


/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req's command
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the MSC command
 *  @retval             0x60, MSC_WRITE_STAT / MSC_SET_INT
 *  @retval             0x61, MSC_READ_DEVCAP
 *  @retval             0x62, MSC_GET_STATE
 *  @retval             0x63, MSC_GET_VENDOR_ID
 *  @retval             0x64, MSC_SET_HPD
 *  @retval             0x65, MSC_CLR_HPD
 *  @retval             0x66, MSC_SET_CEC_CAP_ID
 *  @retval             0x67, MSC_GET_CEC_CAP_ID
 *  @retval             0x68, MSC_MSG
 *  @retval             0x69, MSC_GET_VS_ABORT
 *  @retval             0x6A, MSC_GET_DDC_ABORT
 *  @retval             0x6B, MSC_GET_MSC_ABORT
 *  @retval             0x6C, MSC_WRITE_BURST
 * 
 *****************************************************************************/
uint8_si SI_CbusOQReqCmd( uint8_si channel )
{
    return ( l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].command );
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get In-queue's active Req's data
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the KeyID in MSC_MSG
 * 
 *****************************************************************************/
uint8_si SI_CbusIQReqData ( uint8_si channel )
{
    return ( l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex].msgData);
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req's msgData[0]
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the data of MSC command
 * 
 *****************************************************************************/
uint8_si SI_CbusOQReqData0( uint8_si channel )
{
    return ( l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].msgData[0]);
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req's msgData[1]
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the data of MSC command
 * 
 *****************************************************************************/
uint8_si SI_CbusOQReqData1( uint8_si channel )
{
    return ( l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].msgData[1]);
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req's msgData[2]
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the data of MSC command
 * 
 *****************************************************************************/
uint8_si SI_CbusOQReqData2( uint8_si channel )
{
    return ( l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].msgData[2]);
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get In-queue's active Req
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the pointer to the req structure
 * 
 *****************************************************************************/
cbus_in_queue_t *SI_CbusIQActiveReq ( uint8_si channel )
{
    return ( &l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex]);
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the pointer to the req structure
 * 
 *****************************************************************************/
cbus_out_queue_t *SI_CbusOQActiveReq( uint8_si channel )
{
    return ( &l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex]);
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get In-queue's active Req's timeout value
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the value of timeout
 * 
 *****************************************************************************/
uint32_si SI_CbusIQReqTimeout ( uint8_si channel )
{
    return ( l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex].timeout);
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req's timeout value
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the value of timeout
 * 
 *****************************************************************************/
uint32_si SI_CbusOQReqTimeout( uint8_si channel )
{
    return ( l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].timeout );
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Set Out-queue's active Req's timeout value
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          value			timeout value
*  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusOQSetReqTimeout( uint8_si channel, uint32_si value)
{
    l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].timeout = value;
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req's retry value
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the value of retry
 * 
 *****************************************************************************/
uint8_si SI_CbusOQReqRetry( uint8_si channel )
{
    return ( l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].retry );
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Reduce Out-queue's active Req's retry value by 1
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusOQReduceReqRetry( uint8_si channel )
{
	l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].retry-- ;
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Get Out-queue's active Req's CecReq value
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Return the value of CecReq
 * 
 *****************************************************************************/
bool_si SI_CbusOQGetCecReq( uint8_si channel )
{
	return ( l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].cecReq );
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Set Out-queue's active Req's CecReq value
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusOQSetCecReq( uint8_si channel , bool_si value )
{
	l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].cecReq = value;
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Clean In-queue's active Req.
 *  					    Set the reqStatus to IDLE and timeout value to 0
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusIQCleanActiveReq( uint8_si channel )
{
	cbus_in_queue_t *pReq;
	
	pReq = SI_CbusIQActiveReq(channel);

	pReq->reqStatus = CBUS_REQ_IDLE;
	pReq->timeout = 0;
	pReq->timer_set = false;
}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Clean Out-queue's active Req.
 *  					    Set the reqStatus to IDLE, retry and timeout value to 0
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusOQCleanActiveReq( uint8_si channel )
{
	cbus_out_queue_t * pReq;
	
	pReq = SI_CbusOQActiveReq(channel);

	pReq->reqStatus = CBUS_REQ_IDLE;
	pReq->retry = 0;
	pReq->timeout = 0;
	pReq->vip = false;
	pReq->timer_set = false;
	pReq->cecReq = false;
	pReq->dataRetHandler = NULL;
}

/*****************************************************************************/
/** 
 *  Cbus data structure operation: Check if the command is the ignore command by the peer 
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          kerID			RCP or RAP's Key ID
 *  @param[in]          direction		Cbus In or Cbus Out
 *  
 *  @return             ignore or not
 *  @retval             true: ignore command
 *  @retval             false: normal command
 *****************************************************************************/
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
bool_si SI_CbusKeyIDCheck(uint8_si channel, uint8_si keyID, uint8_si direction)
#else
bool_si SI_CbusKeyIDCheck(uint8_si keyID, uint8_si direction)
#endif
{
	bool_si ret;
    ret = 0;
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
	if (direction == CBUS_IN)
	{
		ret = (l_cbus[channel].i_mscmsg_ignore_list[keyID])|rcp_reserved_list[keyID];
	}
	else if (direction == CBUS_OUT)
	{
		ret = (l_cbus[channel].o_mscmsg_ignore_list[keyID])|rcp_reserved_list[keyID];
	}
#else
	if (direction == CBUS_IN)
	{
		ret = rcp_reserved_list[keyID];
	}
	else if (direction == CBUS_OUT)
	{
		ret = rcp_reserved_list[keyID];
	}

#endif
	return (ret);
}

/*****************************************************************************/
/** 
 *  Cbus data structure operation: Get the value of connect_wait
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             connect_wait
 *  @retval             true: this step has been done
 *  @retval             false: this step hasn't been done
 * 
 *****************************************************************************/
bool_si SI_CbusGetConnectWait( uint8_si channel )
{
	return ( l_cbus[ channel].connect_wait);
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of connect_wait
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          value			value of connect_wait
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetConnectWait( uint8_si channel , bool_si value )
{
	l_cbus[ channel].connect_wait = value;
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Get the value of hpd_state
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             hpd_state
 *  @retval             true: hpd is set
 *  @retval             false: hpd is cleared
 * 
 *****************************************************************************/
bool_si SI_CbusGetHpdState( uint8_si channel )
{
	return ( l_cbus[ channel].hpd_state);
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of hpd_state
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          value			value of hpd_state
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetHpdState( uint8_si channel , bool_si value )
{
	l_cbus[ channel].hpd_state = value;
}


/*****************************************************************************/
/** 
 *  Cbus data structure operation: Get the value of grt_wrt
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  
 *  @return             path_enable
 *  @retval             true: connect path enabled
 *  @retval             false: connect path disabled
 * 
 *****************************************************************************/
bool_si SI_CbusGetGrtWrt( uint8_si channel )
{
	return ( l_cbus[ channel].grt_wrt);
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of grt_wrt
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  @param[in]          value			value of path_enable
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetGrtWrt( uint8_si channel , bool_si value )
{
	l_cbus[ channel].grt_wrt = value;
}


/*****************************************************************************/
/** 
 *  Cbus data structure operation: Get the value of path_enable
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             path_enable
 *  @retval             true: connect path enabled
 *  @retval             false: connect path disabled
 * 
 *****************************************************************************/
bool_si SI_CbusGetPathEnable( uint8_si channel )
{
	return ( l_cbus[ channel].path_enable);
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of path_enable
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          value			value of path_enable
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetPathEnable( uint8_si channel , bool_si value )
{
	l_cbus[ channel].path_enable = value;
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Get the value of dcap_rdy
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  
 *  @return             connect_ready
 *  @retval             true: peer dcap reg ready
 *  @retval             false: peer dcap reg not ready
 * 
 *****************************************************************************/
bool_si SI_CbusGetDcapRdy( uint8_si channel )
{
	return ( l_cbus[ channel].dcap_rdy);
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of dcap_rdy
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  @param[in]          value			value of dcap_rdy
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetDcapRdy( uint8_si channel , bool_si value )
{
	l_cbus[ channel].dcap_rdy = value;
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Get the value of connect_ready
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             connect_ready
 *  @retval             true: connect ready
 *  @retval             false: connect not ready
 * 
 *****************************************************************************/
bool_si SI_CbusGetConnectReady( uint8_si channel )
{
	return ( l_cbus[ channel].connect_ready);
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of connect_ready
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          value			value of connect_ready
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetConnectReady( uint8_si channel , bool_si value )
{
	l_cbus[ channel].connect_ready = value;
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Get the value of abort_wait
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  
 *  @return             abort_wait value
 *  @retval             true: need to do abort wait
 *  @retval             false: no abort wait
 * 
 *****************************************************************************/
bool_si SI_CbusGetAbortWait( uint8_si channel )
{
	return ( l_cbus[ channel].abort_wait);
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of abort_wait
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  @param[in]          value			value of abort_wait
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetAbortWait( uint8_si channel , bool_si value )
{
	l_cbus[ channel].abort_wait = value;

	if (value)
		l_cbus[ channel].base_time = timer_count;
	else
		l_cbus[ channel].base_time = 0;
		
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Get the value of read_info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             read_info
 *  @retval             true: this step has been done
 *  @retval             false: this step hasn't been done
 * 
 *****************************************************************************/
uint8_si SI_CbusGetReadInfo( uint8_si channel )
{
	return ( l_cbus[ channel].read_info);
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of read_info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          value			value of read_info
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetReadInfo( uint8_si channel , uint8_si value )
{
	l_cbus[ channel].read_info = value;
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of rcp_support
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          value			value of rcp_support
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetRcpSupport( uint8_si channel , bool_si value )
{
	l_cbus[ channel].rcp_support= value;
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: Set the value of rap_support
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          value			value of rap_support
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusSetRapSupport( uint8_si channel , bool_si value )
{
	l_cbus[ channel].rap_support= value;
}



/*****************************************************************************/
/** 
 *  Cbus data structure operation: initial the cbus parameters, set all to default							
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusInitParam( uint8_si channel )
{
	uint8_si i;

	l_cbus[channel].connect_wait = false;
	l_cbus[channel].hpd_state = false;
	l_cbus[channel].path_enable = false;
	l_cbus[channel].connect_ready = false;
	l_cbus[channel].dcap_rdy = false;
	l_cbus[channel].read_info = 0;
	l_cbus[channel].grt_wrt = false;
	l_cbus[channel].rcp_support = true;
	l_cbus[channel].rap_support = true;

	for (i = 0; i < CBUS_MAX_COMMAND_QUEUE; i ++)
	{
		l_cbus[channel].o_queue[i].reqStatus = CBUS_REQ_IDLE;
		l_cbus[channel].o_queue[i].cecReq = false;
		l_cbus[channel].o_queue[i].vip = false;
		l_cbus[channel].o_queue[i].timer_set = false;
		l_cbus[channel].o_queue[i].base_time = 0;
		l_cbus[channel].o_queue[i].timeout = 0;
		l_cbus[channel].o_queue[i].dataRetHandler = NULL;
		l_cbus[channel].i_queue[i].reqStatus = CBUS_REQ_IDLE;
		l_cbus[channel].i_queue[i].timer_set = false;
		l_cbus[channel].i_queue[i].base_time = 0;
		l_cbus[channel].i_queue[i].timeout = 0;
	}

	memset(PeerDevCap, 0, 16);

}




/*****************************************************************************/
/** 
 *  Cbus queue operation: Copy the prepared data into Out-Queue
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          index			the position of the queue
 *  @param[in]          pReq			the point of the prepared Req
 *  
 *  @return             void
 * 
 *****************************************************************************/
static void CopyDataInOQ(uint8_si channel, uint8_si t_index, cbus_out_queue_t *pReq )
{
	//DEBUG_PRINT(MSG_DBG, ("CBUS:: CopyDataInOQ \n"));
	#if API_DEBUG_CODE
	printf("CBUS:: CopyDataInOQ \n");
	#endif
	memcpy(&l_cbus[ channel].o_queue[t_index], pReq, sizeof(cbus_out_queue_t));
}



/*****************************************************************************/
/** 
 *  Cbus operation: The MSC command abort handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          abortReason	MSC abort reason
 *  
 *  @return             void
 * 
 *****************************************************************************/
static void SI_CbusOQReqAbort(uint8_si channel, uint8_si abortReason)
{
	//DEBUG_PRINT(MSG_DBG, ("CBUS:: Abort package received! Wait 2s ...\n"));
	#if API_DEBUG_CODE
	printf("CBUS:: Abort package received! Wait 2s ...\n");
	#endif
	SI_CbusSetAbortWait(channel, true);

	if (abortReason & 0x68)	// not a hotplug or a HB or undefined command
	{
		SI_CbusOQCleanActiveReq(channel);
		return;
	}

	{
		cbus_out_queue_t *pReq;
		
		pReq = SI_CbusOQActiveReq(channel);
			
		if ( pReq->retry != 0 )
		{
			pReq->retry--;
			pReq->reqStatus = CBUS_REQ_PENDING;
		}
		else
		{
			SI_CbusOQCleanActiveReq(channel);
		}	
	}

}



/*****************************************************************************/
/** 
 *  Cbus Queue operation: Push the prepared data into Out-queue
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          pReq			The pointer of the prepared Req data
 *  @param[in]          vip			define if the Req is a vip one
 *  
 *  @return             result
 *  @retval             0: SUCCESS
 *  @retval             0xA: ERROR_QUEUE_FULL
 * 
 *****************************************************************************/
uint8_si	SI_CbusPushReqInOQ( uint8_si channel, cbus_out_queue_t *pReq, bool_si vip )
{

	uint8_si result = ERROR_QUEUE_FULL;
	uint8_si status;
	if ( (pReq->command != MSC_MSG) && (pReq->dataRetHandler == NULL) )
	{
		//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: Error:Missing Return data handler!\n"));
		#if API_DEBUG_CODE
		printf("CBUS:: Error:Missing Return data handler!\n");
		#endif
		return (ERROR_RET_HANDLER);
	}

	status = SI_CbusOQReqStatus(channel);

    if (status == CBUS_REQ_IDLE)
    {
		CopyDataInOQ(channel, l_cbus[channel].o_activeIndex, pReq);
		l_cbus[ channel].o_queue[ l_cbus[channel].o_activeIndex].reqStatus = CBUS_REQ_PENDING;
		l_cbus[ channel].o_queue[ l_cbus[channel].o_activeIndex].vip = vip;
		result = STATUS_SUCCESS;
    }
	else
	{
		uint8_si queueIndex;
		
        for ( queueIndex = 0; queueIndex < CBUS_MAX_COMMAND_QUEUE; queueIndex++ )
        {
            if ( l_cbus[ channel].o_queue[ queueIndex].reqStatus == CBUS_REQ_IDLE )
            {
				CopyDataInOQ(channel, queueIndex, pReq);
				l_cbus[ channel].o_queue[ queueIndex].reqStatus = CBUS_REQ_PENDING;
				l_cbus[ channel].o_queue[ queueIndex].vip = vip;
				result = STATUS_SUCCESS;
				break;
            }
        }
	}

	if ( result != STATUS_SUCCESS )
	{
		if (vip)
		{
			uint8_si queueIndex;
			
	        for ( queueIndex = 0; queueIndex < CBUS_MAX_COMMAND_QUEUE; queueIndex++ )
	        {
	            if ( queueIndex != l_cbus[channel].o_activeIndex )
	            {
	            	if (l_cbus[ channel].o_queue[ queueIndex].vip == false)
	            	{
						CopyDataInOQ(channel, queueIndex, pReq);
						l_cbus[ channel].o_queue[ queueIndex].reqStatus = CBUS_REQ_PENDING;
						l_cbus[ channel].o_queue[ queueIndex].vip = true;
						result = STATUS_SUCCESS;
						//DEBUG_PRINT(MSG_DBG, ("CBUS:: Vip Req forces entering the queue\n"));
						#if API_DEBUG_CODE
						printf("CBUS:: Vip Req forces entering the queue\n");
						#endif
						break;
	            	}
	            }
	        }			
		}
	}

	if ( result != STATUS_SUCCESS )
	{
		uint8_si queueIndex;		
		//DEBUG_PRINT(MSG_DBG, ("CBUS:: Queue Full!\n"));
		#if API_DEBUG_CODE
		printf("CBUS:: Queue Full!\n");
		#endif
		
		for ( queueIndex = 0; queueIndex < CBUS_MAX_COMMAND_QUEUE; queueIndex++ )
		{
			//DEBUG_PRINT(MSG_DBG, ("CBUS:: que[%d].command = %x\n",(int)queueIndex,(int)l_cbus[ channel].o_queue[ queueIndex].command));
			#if API_DEBUG_CODE
			printf("CBUS:: que[%d].command = %x\n",(int)queueIndex,(int)l_cbus[ channel].o_queue[ queueIndex].command);
			#endif
		}
	}
	
	return (result);
}

#ifdef SUPPORT_MSCMSG_IGNORE_LIST
/*****************************************************************************/
/** 
 *  Cbus data structure operation: Push the Key ID into ignore list
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          keyID			Key ID of RCP or RAP
 *  @param[in]          direction		CBUS_IN or CBUS_OUT
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusPushKeytoIgnoreList(uint8_si channel, uint8_si keyID, uint8_si direction)
{
    if(keyID >=0x80) //add error checking 
    {
       // DEBUG_PRINT(MSG_DBG, ("please check your keyID(%x) >= 0x80 , can not put into ignore_list(%d)\n",(int)keyID,(int)direction));
	#if API_DEBUG_CODE
	printf("please check your keyID(%x) >= 0x80 , can not put into ignore_list(%d)\n",(int)keyID,(int)direction);
	#endif
        return ;
    }

   // DEBUG_PRINT(MSG_DBG, ("add key %x into ignore_list(%d)!\n",(int)keyID,(int)direction));
      #if API_DEBUG_CODE
	printf("add key %x into ignore_list(%d)!\n",(int)keyID,(int)direction);
	#endif

	if (direction == CBUS_IN)
	{
		l_cbus[channel].i_mscmsg_ignore_list[keyID] = true;
	}
	else if (direction == CBUS_OUT)
	{
		l_cbus[channel].o_mscmsg_ignore_list[keyID] = true;
	}
	
}

/*****************************************************************************/
/** 
 *  Cbus data structure operation: Push the Key ID into ignore list
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          keyID			Key ID of RCP or RAP
 *  @param[in]          direction		CBUS_IN or CBUS_OUT
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusResetMscMsgIgnoreList(uint8_si channel, uint8_si direction)
{
	int i;

	if (direction == CBUS_IN)
	{
		for (i = 0; i < MSC_MSG_MAX_IGNORE_CMD; i++)
		{
			l_cbus[channel].i_mscmsg_ignore_list[i] = false;
		}
	}
	else if (direction == CBUS_OUT)
	{
		for (i = 0; i < MSC_MSG_MAX_IGNORE_CMD; i++)
		{
			l_cbus[channel].o_mscmsg_ignore_list[i] = false;
		}
	}
}

#endif

/*****************************************************************************/
/** 
 *  Cbus operation: The MSC command return data handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			MSC command return data
 *  
 *  @return             result
 *  @retval             0: SUCCESS
 *  @retval             0xD: ERROR_RET_HANDLER
 * 
 *****************************************************************************/
static uint8_si SI_CbusRetDataHandler(uint8_si channel, uint8_si uData)
{
	uint8_si command, reqStatus;
	bool_si  ret = true;
	uint8_si result = SUCCESS;
	
	l_cbus[ channel].o_queue[l_cbus[ channel].o_activeIndex].timeout = 0;	// clean timeout count

	command = SI_CbusOQReqCmd(channel);
	reqStatus = SI_CbusOQReqStatus(channel);

	//DEBUG_PRINT(MSG_DBG, ("CBUS:: SI_CbusRetDataHandler command =%x,reqStatus = %x\n",(int)command,(int)reqStatus));
	#if API_DEBUG_CODE
	printf("CBUS:: SI_CbusRetDataHandler command =%x,reqStatus = %x\n",(int)command,(int)reqStatus);
	#endif

	if (reqStatus != CBUS_REQ_WAITING)
	{
        //DEBUG_PRINT(MSG_DBG, ("CBUS:: reqStatus is NOT WAITING , it shouled be ignored \n",(int)reqStatus));
	        #if API_DEBUG_CODE
		printf("CBUS:: reqStatus is NOT WAITING , it shouled be ignored \n",(int)reqStatus);
		#endif
		return (result);
	}
	
	if( command == MSC_MSG )
	{
		result = SI_CbusMscMsgTransferDone(channel);
	}
	else
	{
		if(l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].dataRetHandler)
		{
			//DEBUG_PRINT(MSG_DBG, ("CBUS:: dataRetHandler =%x\n",(int)l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].dataRetHandler));
		        #if API_DEBUG_CODE
			printf("CBUS:: dataRetHandler =%x\n",(int)l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].dataRetHandler);
			#endif
			ret = l_cbus[ channel].o_queue[ l_cbus[ channel].o_activeIndex].dataRetHandler(channel, uData);
		}
		else
		{
			//DEBUG_PRINT(MSG_DBG, ("CBUS:: dataRetHandler is NULL ,please check your code\n"));
		        #if API_DEBUG_CODE
			printf("CBUS:: dataRetHandler is NULL ,please check your code\n");
			#endif
		}
	}

	if(!ret)
		result = ERROR_RET_HANDLER;

	return (result);

}


#if IS_CEC
/*****************************************************************************/
/** 
 *  Cbus operation: The MSC MSG CEC return handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  @param[in]          success		CEC translation seccessful or not
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_CbusCecRetHandler(uint8_si channel, bool_si result)
{
	uint8_si command, reqStatus;

	command = SI_CbusIQReqCmd(channel);
	reqStatus = SI_CbusIQReqStatus(channel);

	if (reqStatus != CBUS_REQ_WAITING)
		return;
	
	if ( command == MHL_MSC_MSG_RCP )
	{
		SI_RcpCecRetHandler(channel, result);
	}
	else if ( command == MHL_MSC_MSG_RAP )
	{
		SI_RapCecRetHandler(channel, result);
	}
	else
	{
		//DEBUG_PRINT(MSG_ALWAYS, ("Cbus:: Can not find proper MSC MSG for Cbus Cec return Handler\n"));
		#if API_DEBUG_CODE
		printf("Cbus:: Can not find proper MSC MSG for Cbus Cec return Handler\n");
		#endif
	}
	
}
#endif
/*****************************************************************************/
/** 
 *  Cbus operation: The MSC MSG handler, process the incoming MSC_MSG
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             result
 * 
 *****************************************************************************/
static uint8_si SI_CbusMscMsgHandler(uint8_si channel)
{
	uint8_si result = SUCCESS;
	uint8_si command;

	command = SI_CbusIQReqCmd(channel);

	if ( (command == MHL_MSC_MSG_RCP)||(command == MHL_MSC_MSG_RCPK)||(command == MHL_MSC_MSG_RCPE) )
	{
		result = SI_RcpHandler(channel);
	}
	else if ( (command == MHL_MSC_MSG_RAP)||(command == MHL_MSC_MSG_RAPK))
	{
		result = SI_RapHandler(channel);
	}
	
	return (result);
}



/*****************************************************************************/
/** 
 *  Cbus operation: The MSC MSG timeout handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          direction		Cbus In or Cbus Out
 *  
 *  @return             result
 *  @retval		0: SUCCESS
 *  @retval		0x9: ERROR_WRONG_DIRECTION 
 * 
 *****************************************************************************/
uint8_si SI_CbusMscMsgTimeoutHandler(uint8_si channel, uint8_si direction)
{
	uint8_si result = SUCCESS;
	uint8_si command;

	if ( direction == CBUS_IN )
	{
		command = SI_CbusIQReqCmd(channel);

		if ( (command == MHL_MSC_MSG_RCP)||(command == MHL_MSC_MSG_RCPK)||(command == MHL_MSC_MSG_RCPE) )
		{
			result = SI_RcpTimeoutHandler(channel, direction);
		}
		else if ( (command == MHL_MSC_MSG_RAP)||(command == MHL_MSC_MSG_RAPK) )
		{
			result = SI_RapTimeoutHandler(channel, direction);
		}
	}
	else if ( direction == CBUS_OUT )
	{
		command = SI_CbusOQReqData0(channel);

		if ( (command == MHL_MSC_MSG_RCP)||(command == MHL_MSC_MSG_RCPK)||(command == MHL_MSC_MSG_RCPE) )
		{
			result = SI_RcpTimeoutHandler(channel, direction);
		}
		else if ( (command == MHL_MSC_MSG_RAP)||(command == MHL_MSC_MSG_RAPK) )
		{
			result = SI_RapTimeoutHandler(channel, direction);
		}
	}
	else
	{
		result = ERROR_WRONG_DIRECTION;	
	}
	
	return (result);
}



/*****************************************************************************/
/** 
 *  Cbus operation: The MSC MSG transfer done handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             result
 * 
 *****************************************************************************/
uint8_si SI_CbusMscMsgTransferDone(uint8_si channel)
{
	uint8_si result = SUCCESS;
	uint8_si command;

	command = SI_CbusOQReqData0(channel);

	if ( (command == MHL_MSC_MSG_RCP)||(command == MHL_MSC_MSG_RCPK)||(command == MHL_MSC_MSG_RCPE) )
	{
		result = SI_RcpTransferDoneHandler(channel);
	}
	else if ( (command == MHL_MSC_MSG_RAP)||(command == MHL_MSC_MSG_RAPK) )
	{
		result = SI_RapTransferDoneHandler(channel);
	}
	
	return (result);
}



/*****************************************************************************/
/** 
 *  Cbus queue operation: timeout counting in the reqs of In-queue
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             result
 * 
 *****************************************************************************/
static uint8_si SI_CbusIQReqTimeoutCount(uint8_si channel)
{
	uint8_si result = SUCCESS;
	cbus_in_queue_t *pReq;

	pReq = SI_CbusIQActiveReq(channel);

	if ( pReq->reqStatus == CBUS_REQ_PENDING )
	{
		if (!pReq->timer_set)
		{
			pReq->timer_set = true;
			pReq->base_time = timer_count;
		}
		else
		{
			if( HalTimerDelay(pReq->base_time, pReq->timeout) )
			{
				pReq->base_time = 0;
				pReq->timer_set = false;
				result = SI_CbusMscMsgTimeoutHandler(channel, CBUS_IN);	
			}
		}
	}

	return (result);
}



/*****************************************************************************/
/** 
 *  Cbus queue operation: timeout counting in the reqs of Out-queue
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             result
 * 
 *****************************************************************************/
static uint8_si SI_CbusOQReqTimeoutCount(uint8_si channel)
{
	uint8_si result = SUCCESS;
	cbus_out_queue_t *pReq;
	
	pReq = SI_CbusOQActiveReq(channel);

	if( pReq->reqStatus == CBUS_REQ_WAITING )
	{
		if (!pReq->timer_set)
		{
			pReq->timer_set = true;
			pReq->base_time = timer_count;
		}
		else
		{
			if( HalTimerDelay(pReq->base_time, pReq->timeout) )
			{
				pReq->base_time = 0;
				pReq->timer_set = false;

				if ( pReq->command == MSC_MSG )
					result = SI_CbusMscMsgTimeoutHandler(channel, CBUS_OUT);
				else
				{
					if ( pReq->retry != 0 )
					{
						//DEBUG_PRINT(MSG_ALWAYS, ("Cbus:: 0x%x  Req Timeout \n",(int)SI_CbusOQReqCmd(channel)));
					       #if API_DEBUG_CODE
						printf("Cbus:: 0x%x  Req Timeout \n",(int)SI_CbusOQReqCmd(channel));
						#endif
						pReq->retry--;
						result = CbusWriteCommand(channel, pReq);
						pReq->base_time = timer_count;
						pReq->reqStatus = CBUS_REQ_WAITING;
						pReq->timeout = DEM_MSC_MAX_REPLY_DELAY;
					}
					else
					{
						SI_CbusOQCleanActiveReq(channel);
					}
				}
			}
		}
	}
	
	return (result);
}



/*****************************************************************************/
/** 
 *  Cbus queue operation: In-queue main handler to check the req status
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             result
 * 
 *****************************************************************************/
uint8_si SI_CbusIQReqStatusCheck(uint8_si channel)
{
	uint8_si result = SUCCESS;
	uint8_si status;

	status = SI_CbusIQReqStatus(channel);

	if ( status == CBUS_REQ_PENDING )
	{
		result = SI_CbusMscMsgHandler(channel);
	}
	else if ( status == CBUS_REQ_IDLE )
	{
		uint8_si queueIndex;
		
        for ( queueIndex = 0; queueIndex < CBUS_MAX_COMMAND_QUEUE; queueIndex++ )
        {
            if ( l_cbus[ channel].i_queue[ queueIndex].reqStatus == CBUS_REQ_PENDING )
            {
				l_cbus[ channel].i_activeIndex = queueIndex;
				result = SI_CbusMscMsgHandler(channel);
            }
        }
	}

	result |= SI_CbusIQReqTimeoutCount(channel);

	return (result);

}



/*****************************************************************************/
/** 
 *  Cbus queue operation: Out-queue main handler to check the req status
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             result
 * 
 *****************************************************************************/
uint8_si SI_CbusOQReqStatusCheck(uint8_si channel)
{
	uint8_si result = SUCCESS;
	uint8_si status;
	bool_si  cbus_abort_wait = false;
	cbus_out_queue_t *pReq;

	cbus_abort_wait = SI_CbusGetAbortWait(channel);

	if ( cbus_abort_wait )
	{
        //   DEBUG_PRINT( MSG_DBG, ("CBUS:: cbus_abort_wait %x ----\n",(int)cbus_abort_wait));
	       #if API_DEBUG_CODE
		printf("CBUS:: cbus_abort_wait %x ----\n",(int)cbus_abort_wait);
		#endif
		if (HalTimerDelay(l_cbus[ channel].base_time, DEM_CBUS_ABORT_WAIT))
	       {
                    //DEBUG_PRINT( MSG_DBG, ("CBUS:: ---- ABORT WAIT finished----\n"));
                    #if API_DEBUG_CODE
			printf("CBUS:: ---- ABORT WAIT finished----\n");
			#endif
			SI_CbusSetAbortWait(channel, false);
              }
		else
             {
         //   DEBUG_PRINT( MSG_DBG, ("CBUS:: ---- ABORT WAIT ----\n"));
                  return (result);
            }
	}

	status = SI_CbusOQReqStatus(channel);

	if ( status == CBUS_REQ_PENDING )
	{
		pReq = SI_CbusOQActiveReq(channel);
		result = CbusWriteCommand(channel, pReq);
		pReq->base_time = timer_count;
		pReq->reqStatus = CBUS_REQ_WAITING;
		pReq->timeout = DEM_MSC_MAX_REPLY_DELAY;
	}
	else if ( status == CBUS_REQ_IDLE )
	{
		uint8_si queueIndex;
		
        for ( queueIndex = 0; queueIndex < CBUS_MAX_COMMAND_QUEUE; queueIndex++ )
        {
            if ( l_cbus[ channel].o_queue[ queueIndex].reqStatus == CBUS_REQ_PENDING )
            {
				l_cbus[ channel].o_activeIndex = queueIndex;
				
				pReq = SI_CbusOQActiveReq(channel);
				result = CbusWriteCommand(channel, pReq);
				pReq->base_time = timer_count;
				pReq->reqStatus = CBUS_REQ_WAITING;
				pReq->timeout = DEM_MSC_MAX_REPLY_DELAY;
            }
        }
	}

	result |= SI_CbusOQReqTimeoutCount(channel);
	
	return (result);

}

//------------------------------------------------------------------------------
// Function:    SI_CbusChannelConnected
// Description: Return the CBUS channel connected status for this channel.
// Returns:     true if connected. 
//              false if disconnected.
//------------------------------------------------------------------------------

bool_si SI_CbusChannelConnected (uint8_si channel)
{
    return( l_cbus[ channel].connected );
}

//------------------------------------------------------------------------------
// Function:    CbusProcessConnectionChange
// Description: Process a connection change interrupt
// Returns:     
//------------------------------------------------------------------------------

static uint8_si CbusProcessConnectionChange ( int channel )
{
    channel = 0;

    //DEBUG_PRINT( MSG_DBG, ("CBUS:: ----Connection Change----\n"));
        #if API_DEBUG_CODE
	printf("CBUS:: ----Connection Change----\n");
	#endif
    return( ERROR_CBUS_TIMEOUT );
}

//------------------------------------------------------------------------------
// Function:    CbusProcessFailureInterrupts
// Description: Check for and process any failure interrupts.
// Returns:     SUCCESS or ERROR_CBUS_ABORT
//------------------------------------------------------------------------------

uint8_si CbusProcessFailureInterrupts ( uint8_si channel, uint8_si intStatus, uint8_si inResult )
{
    uint8_si result          = inResult;
    uint8_si mscAbortReason  = SUCCESS;

    /* At this point, we only need to look at the abort interrupts. */

    intStatus &= (BIT_CEC_ABORT | BIT_DDC_ABORT | BIT_MSC_ABORT | BIT_MSC_XFR_ABORT);

    if ( intStatus )
    {
        result = ERROR_CBUS_ABORT;		// No Retry will help

        /* If transfer abort or MSC abort, clear the abort reason register. */

        if ( intStatus & BIT_MSC_XFR_ABORT )
        {
            mscAbortReason = SiIRegioCbusRead( REG_CBUS_REQUESTER_ABORT_REASON, channel );

          //  DEBUG_PRINT( MSG_DBG, ("CBUS:: MSC Requester Abort. Clearing 0x0D\n"));
		//	DEBUG_PRINT( MSG_DBG, ("CBUS:: MSC Requester Abort reason: %02X\n", (int)mscAbortReason));
		#if API_DEBUG_CODE
		printf("CBUS:: MSC Requester Abort. Clearing 0x0D\n");
		#endif
		#if API_DEBUG_CODE
		printf("CBUS:: MSC Requester Abort reason: %02X\n", (int)mscAbortReason);
		#endif		
            SiIRegioCbusWrite( REG_CBUS_REQUESTER_ABORT_REASON, channel, 0xFF );
			SI_CbusOQReqAbort(channel, mscAbortReason);
        }
        if ( intStatus & BIT_MSC_ABORT )
        {
            mscAbortReason = SiIRegioCbusRead( REG_CBUS_RESPONDER_ABORT_REASON, channel );

            //DEBUG_PRINT( MSG_DBG, ("CBUS:: MSC Responder Abort. Clearing 0x0E\n"));
		//DEBUG_PRINT( MSG_DBG, ("CBUS:: MSC Responder Abort reason: %02X\n", (int)mscAbortReason));      
		#if API_DEBUG_CODE
		printf("CBUS:: MSC Responder Abort. Clearing 0x0E\n");
		#endif
		#if API_DEBUG_CODE
		printf("CBUS:: MSC Responder Abort reason: %02X\n", (int)mscAbortReason);
		#endif	
            SiIRegioCbusWrite( REG_CBUS_RESPONDER_ABORT_REASON, channel, 0xFF );
			SI_CbusOQReqAbort(channel, mscAbortReason);
        }
		if ( intStatus & BIT_DDC_ABORT )
		{
            mscAbortReason = SiIRegioCbusRead( REG_CBUS_DDC_ABORT_REASON, channel );

            //DEBUG_PRINT( MSG_DBG, ("CBUS:: DDC Abort. Clearing 0x0C\n"));	
			//DEBUG_PRINT( MSG_DBG, ("CBUS:: DDC Abort reason: %02X\n", (int)mscAbortReason));      
		#if API_DEBUG_CODE
		printf("CBUS:: DDC Abort. Clearing 0x0C\n");
		#endif
		#if API_DEBUG_CODE
		printf("CBUS:: DDC Abort reason: %02X\n", (int)mscAbortReason);
		#endif	
            SiIRegioCbusWrite( REG_CBUS_DDC_ABORT_REASON, channel, 0xFF );
		}
		if ( intStatus & BIT_CEC_ABORT )
		{
            mscAbortReason = SiIRegioCbusRead( REG_CBUS_CEC_ABORT_REASON, channel );

           // DEBUG_PRINT( MSG_DBG, ("CBUS:: CEC Abort. Clearing 0x0B\n"));	
		//	DEBUG_PRINT( MSG_DBG, ("CBUS:: CEC Abort reason: %02X\n", (int)mscAbortReason));    
		#if API_DEBUG_CODE
		printf("CBUS:: CEC Abort. Clearing 0x0B\n");
		#endif
		#if API_DEBUG_CODE
		printf("CBUS:: CEC Abort reason: %02X\n", (int)mscAbortReason);
		#endif
            SiIRegioCbusWrite( REG_CBUS_CEC_ABORT_REASON, channel, 0xFF );
		}

        // Now display the abort reason.

        if ( mscAbortReason != 0 )
        {
           // DEBUG_PRINT( MSG_DBG, ("CBUS:: Reason for ABORT is ....0x%02X = ", (int)mscAbortReason ));
		#if API_DEBUG_CODE
		printf("CBUS:: Reason for ABORT is ....0x%02X = ", (int)mscAbortReason );
		#endif
            if ( mscAbortReason & CBUSABORT_BIT_REQ_MAXFAIL)
            {
                //DEBUG_PRINT( MSG_DBG, ("Requestor MAXFAIL - retry threshold exceeded\n"));
                #if API_DEBUG_CODE
		printf("Requestor MAXFAIL - retry threshold exceeded\n");
		#endif
            }
            if ( mscAbortReason & CBUSABORT_BIT_PROTOCOL_ERROR)
            {
               // DEBUG_PRINT( MSG_DBG, ("Protocol Error\n"));
               
               #if API_DEBUG_CODE
		printf("Protocol Error\n");
		#endif
               
            }
            if ( mscAbortReason & CBUSABORT_BIT_REQ_TIMEOUT)
            {
                //DEBUG_PRINT( MSG_DBG, ("Requestor translation layer timeout\n"));
                #if API_DEBUG_CODE
		printf("Requestor translation layer timeout\n");
		#endif
            }
            if ( mscAbortReason & CBUSABORT_BIT_PEER_ABORTED)
            {
              //  DEBUG_PRINT( MSG_DBG, ("Peer sent an abort\n"));
              #if API_DEBUG_CODE
		printf("Peer sent an abort\n");
		#endif
            }
            if ( mscAbortReason & CBUSABORT_BIT_UNDEFINED_OPCODE)
            {
               // DEBUG_PRINT( MSG_DBG, ("Undefined opcode\n"));
               #if API_DEBUG_CODE
		printf("Undefined opcode\n");
		#endif
            }
        }

        /* Clear any failure interrupt that we received.    */

        SiIRegioCbusWrite( REG_CBUS_INTR_STATUS, channel, intStatus );
    }

    return( result );
}

//------------------------------------------------------------------------------
// Function:    CbusProcessSubCommand
// Description: Process a sub-command (RCP) or sub-command response (RCPK).
//              Modifies channel state as necessary.
// Parameters:  channel - CBUS channel that received the command.
// Returns:     SUCCESS or CBUS_SOFTWARE_ERRORS_t
//              If SUCCESS, command data is returned in l_cbus[channel].msgData[i]
//------------------------------------------------------------------------------

static uint8_si CbusProcessSubCommand ( int channel )
{
	uint8_si		result = SUCCESS;
    uint8_si     vs_cmd, vs_data;
	uint8_si 	q_index = 0xFF;

    /* Get RCP message data for this channel from the hardware. */

    vs_cmd  = SiIRegioCbusRead( REG_CBUS_PRI_VS_CMD, channel );
    vs_data = SiIRegioCbusRead( REG_CBUS_PRI_VS_DATA, channel );
    #if API_DEBUG_CODE
	printf("vs_cmd = %02X\n", (int)vs_cmd);
	#endif

	//DEBUG_PRINT(MSG_ALWAYS, ("vs_cmd = %02X\n", (int)vs_cmd));

    // Save MSC_MSG data in the channel i_queue structure to be returned
    if (l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex].reqStatus == CBUS_REQ_IDLE)
    {
    	l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex].command = vs_cmd;
    	l_cbus[ channel].i_queue[ l_cbus[ channel].i_activeIndex].msgData = vs_data;
		q_index = l_cbus[ channel].i_activeIndex;
    }
	else
	{
		uint8_si queueIndex;
		
        for ( queueIndex = 0; queueIndex < CBUS_MAX_COMMAND_QUEUE; queueIndex++ )
        {
            if ( l_cbus[ channel].i_queue[ queueIndex].reqStatus == CBUS_REQ_IDLE )
            {
		    	l_cbus[ channel].i_queue[ queueIndex].command = vs_cmd;
		    	l_cbus[ channel].i_queue[ queueIndex].msgData = vs_data;
				q_index = queueIndex;
			break;  //add by dengqq	
           }
        }
	}

	if (q_index == 0xFF)
	{
		//DEBUG_PRINT(MSG_ALWAYS, ("CBUS::MSC_MSG Receiving Queue full!\n"));
	       #if API_DEBUG_CODE
		printf("CBUS::MSC_MSG Receiving Queue full!\n");
		#endif
		return (ERROR_QUEUE_FULL);
	}

	// Parse it a little before telling the upper level about it.  
    switch (vs_cmd)
    {
        case MHL_MSC_MSG_RCP:
           // DEBUG_PRINT( MSG_DBG, ("CBUS:: Received <-- MHL_MSC_MSG_RCP\n"));	
           	       #if API_DEBUG_CODE
			printf("CBUS:: Received <-- MHL_MSC_MSG_RCP\n");
			#endif
			l_cbus[ channel].i_queue[ q_index ].reqStatus = CBUS_REQ_PENDING;
			l_cbus[ channel].i_queue[ q_index ].timeout = DEM_MHL_RCP_TIMEOUT;		// setup the timeout wait time for RCP			
			result = SUCCESS;
            break;

        case MHL_MSC_MSG_RCPK:
            //DEBUG_PRINT( MSG_DBG, ("CBUS:: Received <-- MHL_MSC_MSG_RCPK\n"));
            		#if API_DEBUG_CODE
			printf("CBUS:: Received <-- MHL_MSC_MSG_RCPK\n");
			#endif
			l_cbus[ channel].i_queue[ q_index ].reqStatus = CBUS_REQ_IDLE;
			result = SI_RcpAckRcvd(channel, vs_data);
            break;

        case MHL_MSC_MSG_RCPE:
           // DEBUG_PRINT( MSG_DBG, ("CBUS:: Received <-- MHL_MSC_MSG_RCPE\n"));
           		#if API_DEBUG_CODE
			printf("CBUS:: Received <-- MHL_MSC_MSG_RCPE\n");
			#endif
			l_cbus[ channel].i_queue[ q_index ].reqStatus = CBUS_REQ_IDLE;
			result = SI_RcpErrRcvd(channel, vs_data);								// RCPE handler will reset the timer of RCP request in OQ to Trcp_wait
            break;
        case MHL_MSC_MSG_RAP:
            //DEBUG_PRINT( MSG_DBG, ("CBUS:: Received <-- MHL_MSC_MSG_RAP\n"));
                      #if API_DEBUG_CODE
			printf("CBUS:: Received <-- MHL_MSC_MSG_RAP\n");
			#endif
			l_cbus[ channel].i_queue[ q_index ].reqStatus = CBUS_REQ_PENDING;			
			l_cbus[ channel].i_queue[ q_index ].timeout = DEM_MHL_RCP_TIMEOUT;		// setup the timeout wait time for RAP			
			result = SUCCESS;
            break;
        case MHL_MSC_MSG_RAPK:
            //DEBUG_PRINT( MSG_DBG, ("CBUS:: Received <-- MHL_MSC_MSG_RAPK\n"));
                    #if API_DEBUG_CODE
			printf("CBUS:: Received <-- MHL_MSC_MSG_RAPK\n");
			#endif
			l_cbus[ channel].i_queue[ q_index ].reqStatus = CBUS_REQ_IDLE;
			result = SI_RapAckRcvd(channel, vs_data);			
            break;
    }

    //DEBUG_PRINT( MSG_DBG, ("CBUS:: MSC_MSG CMD:  0x%02X\n", (int)vs_cmd ));
    //DEBUG_PRINT( MSG_DBG, ("CBUS:: MSC_MSG Data: 0x%02X\n", (int)vs_data ));

    return( result );
}

//------------------------------------------------------------------------------
// Function:    CbusWriteCommand
// Description: Write the specified Sideband Channel command to the CBUS.
//              Command can be a MSC_MSG command (RCP/MCW/RAP), or another command 
//              such as READ_DEVCAP, GET_VENDOR_ID, SET_HPD, CLR_HPD, etc.
//
// Parameters:  channel - CBUS channel to write
//              pReq    - Pointer to a cbus_req_t structure containing the 
//                        command to write
// Returns:     TRUE    - successful write
//              FALSE   - write failed
//------------------------------------------------------------------------------

uint8_si CbusWriteCommand ( int channel, cbus_out_queue_t *pReq  )
{
    uint8_si i, startbit;
	uint8_si uData1 = 0;
	uint8_si uData2 = 0;	
    uint8_si result = SUCCESS;

    /****************************************************************************************/
    /* Setup for the command - write appropriate registers and determine the correct        */
    /*                         start bit.                                                   */
    /****************************************************************************************/

    SiIRegioCbusWrite( REG_CBUS_PRI_ADDR_CMD, channel, pReq->command );

    startbit = 0x00;
    switch ( pReq->command )
    {
        case MSC_WRITE_STAT:                        // Same opCode as MSC_SET_INT
            SiIRegioCbusWrite( REG_CBUS_PRI_ADDR_CMD, channel, pReq->offsetData );
            SiIRegioCbusWrite( REG_CBUS_PRI_WR_DATA_1ST, channel, pReq->msgData[0] );
            startbit = MSC_START_BIT_WRITE_REG;
			uData1 = pReq->offsetData;
			uData2 = pReq->msgData[0];
            break;

        case MSC_READ_DEVCAP:
            SiIRegioCbusWrite( REG_CBUS_PRI_ADDR_CMD, channel, pReq->offsetData );
            startbit = MSC_START_BIT_READ_REG;
 			uData1 = pReq->offsetData;
           break;

        case MSC_GET_STATE:
        case MSC_GET_VENDOR_ID:
        case MSC_SET_HPD:
        case MSC_CLR_HPD:
		case MSC_GET_VS_ABORT:
    	case MSC_GET_DDC_ABORT:
    	case MSC_GET_MSC_ABORT:     
            startbit = MSC_START_BIT_MSC_CMD;
            break;

        case MSC_MSG:
            SiIRegioCbusWrite( REG_CBUS_PRI_WR_DATA_1ST, channel, pReq->msgData[0] );
            SiIRegioCbusWrite( REG_CBUS_PRI_WR_DATA_2ND, channel, pReq->msgData[1] );
            startbit = MSC_START_BIT_VS_CMD;
			uData1 = pReq->msgData[0];
			uData2 = pReq->msgData[1];
            break;

        case MSC_WRITE_BURST:
            SiIRegioCbusWrite( REG_CBUS_PRI_ADDR_CMD, channel, pReq->offsetData );
            SiIRegioCbusWrite( REG_MSC_WRITE_BURST_LEN, channel, pReq->length - 1 );//be care of length , if length = 16 , write 15 into register 

            // Now copy all bytes from array to local scratchpad

            for ( i = 0; i < pReq->length; i++ )
            {
                SiIRegioCbusWrite( (REG_CBUS_SCRATCHPAD_0 + i), channel, pReq->msgData[i] );
            }
            startbit = MSC_START_BIT_WRITE_BURST;
			uData1 = pReq->offsetData;
			uData2 = pReq->length;
            break;

        default:
            result = ERROR_INVALID_MSC_CMD;
            break;
    }

    /****************************************************************************************/
    /* Trigger the CBUS command transfer using the determined start bit.                    */
    /****************************************************************************************/

    if ( result == SUCCESS )
    {
        SiIRegioCbusWrite( REG_CBUS_PRI_START, channel, startbit );
    	//DEBUG_PRINT( MSG_DBG, ("CBUS:: Sending MSC command %02X, %02X, %02X\n", (int)pReq->command, (int)uData1, (int)uData2));
        #if API_DEBUG_CODE
	printf("CBUS:: Sending MSC command %02X, %02X, %02X\n", (int)pReq->command, (int)uData1, (int)uData2);
	#endif
    }

    return( result );
}
static uint8_si SiiWriteBurstData(uint8_si channel)
{
    cbus_out_queue_t req;
    uint8_si result ,i;

    req.length = 0x10;    
    for ( i = 0; i < req.length; i++ )
    {
        req.msgData[i] = 0xA5;//just for example;
    }

    req.command = MSC_WRITE_BURST;
    req.offsetData = 0x40;//register offset
    req.dataRetHandler = SI_WriteBurstDataDone;
    #if 0	
    req.retry = 1;	// only try once due to 10ms timing
    result = SI_CbusPushReqInOQ( channel, &req, true );
    #else
    req.retry = 0;	// only try once due to 10ms timing
    result = SI_CbusPushReqInOQ( channel, &req, false );
    #endif
    return result;
}
///////////////////////////////////////////////////////////////////////////////
//
// SiiMhlTxGotMhlIntr
//
// This function is called by the driver to inform of arrival of a MHL INTERRUPT.
//
// It is called in interrupt context to meet some MHL specified timings, therefore,
// it should not have to call app layer and do negligible processing, no printfs.
//
void	SiiMhlTxGotMhlIntr(uint8_si channel , uint8_si intr_0, uint8_si intr_1 )
{
    uint8_si result;
	//DEBUG_PRINT(MSG_DBG,("MhlTx: INTERRUPT Arrived. %02X, %02X\n", (int) intr_0, (int) intr_1 ));
	intr_1 = intr_1;
	#if API_DEBUG_CODE
	printf("MhlTx: INTERRUPT Arrived. %02X, %02X\n", (int) intr_0, (int) intr_1);
	#endif
	//
	// Handle DCAP_CHG INTR here
	//
	if(CBUS_INT_BIT_DCAP_CHG & intr_0)
	{
        SI_CbusSetReadInfo(channel,0);//start to read DCAP in main loop
	}

	if( CBUS_INT_BIT_DSCR_CHG & intr_0)
    {

    }
	
	if( CBUS_INT_BIT_REQ_WRT  & intr_0)
    {
        bool_si grant = SI_CbusGetGrtWrt(channel);
        
        if ( !grant )
        {
            cbus_out_queue_t req;

            req.command = MSC_SET_INT;
            req.offsetData  = MHL_REG_CHANGE_INT_OFFSET;
            req.msgData[0]	= CBUS_INT_BIT_GRT_WRT;
            req.dataRetHandler = SI_MscGrtWrt;
            req.retry = 1;	// only try once due to 10ms timing
            result = SI_CbusPushReqInOQ( channel, &req, true );
        }
    }
	if( CBUS_INT_BIT_GRT_WRT  & intr_0)
    {

	   	//DEBUG_PRINT(MSG_DBG, ("MhlTx: you cant write your data now!\n"));
	 #if API_DEBUG_CODE
	printf("MhlTx: you cant write your data now!\n");
	#endif
        SiiWriteBurstData(channel);

    }
}

#if 0
///////////////////////////////////////////////////////////////////////////////
//
// SiiMhlTxGotMhlStatus
//
// This function is called by the driver to inform of arrival of a MHL STATUS.
//
// It is called in interrupt context to meet some MHL specified timings, therefore,
// it should not have to call app layer and do negligible processing, no printfs.
//
void	SiiMhlTxGotMhlStatus(uint8_si channel, uint8_si status_0, uint8_si status_1 )
{
//	TX_DEBUG_PRINT( ("MhlTx: STATUS Arrived. %02X, %02X\n", (int) status_0, (int) status_1) );
	//
	// Handle DCAP_RDY STATUS here itself
	//
    static uint8_si s_status_0 = 0, s_status_1 = 0;
	uint8_si StatusChangeBitMask0,StatusChangeBitMask1;

    StatusChangeBitMask0 = status_0 ^ s_status_0;
    StatusChangeBitMask1 = status_1 ^ s_status_1;
	// Remember the event.   (other code checks the saved values, so save the values early, but not before the XOR operations above)
	s_status_0 = status_0;
	s_status_1 = status_1;

	if(BIT_DCAP_RDY & StatusChangeBitMask0) //changed 
	{
        DEBUG_PRINT(MSG_DBG, ("MhlTx: DCAP_RDY changed\n"));
        if (BIT_DCAP_RDY & status_0)
        {
			//
        }
	}


    // did PATH_EN change?
	if(BIT_PATH_EN & StatusChangeBitMask1)
    {
        DEBUG_PRINT(MSG_DBG, ("MhlTx: PATH_EN changed\n"));
        if(BIT_PATH_EN & status_1)
        {
            // OK to call this here since all requests are queued
            SI_CbusSetPathEnable(channel , true);

        }
        else
        {
            // OK to call this here since all requests are queued
            SI_CbusSetPathEnable(channel , false);
        }
    }

}

#endif
//------------------------------------------------------------------------------
// Function:    CbusCheckInterruptStatus
// Description: If any interrupts on the specified channel are set, process them.
// Parameters:  channel - CBUS channel to check
// Returns:     SUCCESS or CBUS_SOFTWARE_ERRORS_t error code.
//------------------------------------------------------------------------------

static uint8_si CbusCheckInterruptStatus ( uint8_si channel )
{
    uint8_si result, uData;
	uint8_si intStatus;

    /* Read CBUS interrupt status.  */
    intStatus = SiIRegioCbusRead( REG_CBUS_INTR_STATUS, channel );

	if((intStatus != 0) && (intStatus != 0x04))
	   	//DEBUG_PRINT(MSG_DBG, ("CBUS:: Interrupt Status, %02X\n", (int)intStatus));
	   		 #if API_DEBUG_CODE
			printf("CBUS:: Interrupt Status, %02X\n", (int)intStatus);
			#endif
	
    /* Check for interrupts.  */

    result = SUCCESS;
    if ( intStatus != 0 )
    {
        if ( intStatus & BIT_MSC_MSG_RCV )
        {
            /* Receiving a sub-command, either an actual command or */
            /* the response to a command we sent.                   */
			//DEBUG_PRINT(MSG_DBG, ("BIT_MSC_MSG_RCV\n"));
            SiIRegioCbusWrite( REG_CBUS_INTR_STATUS, channel, BIT_MSC_MSG_RCV );
            result = CbusProcessSubCommand( channel );
        }

		if ( intStatus & BIT_MSC_XFR_DONE )
        {
            /* A previous MSC sub-command has been acknowledged by the responder.   */
            /* Does not include MSC MSG commands.                                   */
            SiIRegioCbusWrite( REG_CBUS_INTR_STATUS, channel, BIT_MSC_XFR_DONE );

			//DEBUG_PRINT(MSG_DBG, ("CBUS:: Interrupt Transfer Done\n"));
			#if API_DEBUG_CODE
			printf("CBUS:: Interrupt Transfer Done\n");
			#endif

			uData = SiIRegioCbusRead( REG_CBUS_WRITE_BURST_LEN, channel );
			if ( uData & BIT_MSC_DONE_WITH_NACK )
			{
				//DEBUG_PRINT(MSG_DBG, ("CBUS:: MSC Transfer Done with NACK. Need retry...\n"));
				#if API_DEBUG_CODE
				printf("CBUS:: MSC Transfer Done with NACK. Need retry...\n");
				#endif
				SI_CbusOQSetReqStatus( channel, CBUS_REQ_PENDING );
				SI_CbusOQSetReqTimeout( channel, 0 );
			}
			else
			{
	            /* Save any response data in the channel request structure to be returned    */
	            /* to the upper level.                                                      */

	            uData = SiIRegioCbusRead( REG_CBUS_PRI_RD_DATA_1ST, channel );		            
				result = SI_CbusRetDataHandler(channel, uData);
			}			
        }

        if ( intStatus & BIT_CONNECT_CHG )
        {
            /* The connection change interrupt has been received.   */
			
			//DEBUG_PRINT(MSG_DBG, ("CBUS:: Interrupt Connect Change\n"));
				#if API_DEBUG_CODE
				printf("CBUS:: Interrupt Connect Change\n");
				#endif
            SiIRegioCbusWrite( REG_CBUS_INTR_STATUS, channel, BIT_CONNECT_CHG );

			// MP: do we need to process the connection change
			
            result = CbusProcessConnectionChange( channel );
        }

		if ( intStatus & BIT_PARITY_ERROR)
		{
			//DEBUG_PRINT(MSG_DBG, ("CBUS:: Interrupt Parity Error\n"));
			#if API_DEBUG_CODE
			printf("CBUS:: Interrupt Parity Error\n");
			#endif
            SiIRegioCbusWrite( REG_CBUS_INTR_STATUS, channel, BIT_PARITY_ERROR );
			SiIRegioCbusWrite( REG_CBUS_LINK_STATUS_2, channel, 0 );
		}


        /* Check for failure interrupts.    */

        result = CbusProcessFailureInterrupts( channel, (uint8_si)intStatus, result );
    }

	// Add processing for WRITE_BURST
    intStatus = 0;
	intStatus = SiIRegioCbusRead( REG_CBUS_MSC_INT2_STATUS, channel );

	if( intStatus )
	{
	 //  	DEBUG_PRINT(MSG_DBG, ("CBUS:: REG_CBUS_MSC_INT2_STATUS, %02X\n", (int)intStatus));
		if ( intStatus & BIT_MSC_MR_SET_INT )
		{
            uint8_si intr_0 = 0,intr_1 = 0;
            intr_0 = SiIRegioCbusRead(REG_CBUS_INT_REG_0,channel);
            intr_1 = SiIRegioCbusRead(REG_CBUS_INT_REG_1,channel);
           // DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL INTR Received\n"));
           		#if API_DEBUG_CODE
			printf("CBUS:: MHL INTR Received\n");
			#endif

    		// We are interested only in first two bytes.
    		SiiMhlTxGotMhlIntr(channel ,intr_0, intr_1 );

			SiIRegioCbusWrite( REG_CBUS_INT_REG_0, channel, intr_0 );
			SiIRegioCbusWrite( REG_CBUS_INT_REG_1, channel, intr_1 );
		}

		if ( intStatus & BIT_MSC_WRITE_BURST )
		{
			#if API_DEBUG_CODE
			uint8_si i;
			#endif
			
			//DEBUG_PRINT(MSG_DBG, ("CBUS:: Interrupt WRITE_BURST\n"));
			#if API_DEBUG_CODE
			printf("CBUS:: Interrupt WRITE_BURST\n");
			#endif
			//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: Data received in Scratch Pad\n"));
			#if API_DEBUG_CODE
			printf("CBUS:: Data received in Scratch Pad\n");
			#endif
			#if API_DEBUG_CODE
			for (i = 0; i < 16; i++)
			{
				uint8_si reg_data = SiIRegioCbusRead((REG_CBUS_SCRATCHPAD_0 + i), channel);
				//DEBUG_PRINT(MSG_ALWAYS, ("%02X ", (int)reg_data));
				#if API_DEBUG_CODE
				printf("%02X ", (int)reg_data);
				#endif
			}
			#endif
			//DEBUG_PRINT(MSG_ALWAYS, ("\n"));
			#if API_DEBUG_CODE
			printf("\n");
			#endif
			SI_CbusSetGrtWrt(channel, false);
		}

#ifndef SWWA_21970
		if ( intStatus & BIT_MSC_MR_WRITE_STATE )
		{
			uint8_si reg_val = SiIRegioCbusRead(REG_CBUS_STAT_REG_0, channel);

			//DEBUG_PRINT(MSG_DBG, ("CBUS:: Interrupt WRITE_STATE\n"));
			if ( reg_val & BIT_DCAP_RDY )
			{
				//DEBUG_PRINT(MSG_DBG, ("CBUS:: Peer DevCap Ready\n"));
				SI_CbusSetDcapRdy(channel, true);
			}

			SiIRegioCbusWrite( REG_CBUS_STAT_REG_0, channel, reg_val );
		}
#endif //not define SWWA_21970

		SiIRegioCbusWrite(REG_CBUS_MSC_INT2_STATUS, channel, intStatus);
	}

#ifdef SWWA_21970
	{
		static uint8_si reg_B0 = 0;

		uData = SiIRegioCbusRead(REG_CBUS_STAT_REG_0, channel);
		if ( uData != reg_B0 )
		{
			if ( reg_B0 )
				//DEBUG_PRINT(MSG_DBG, ("CBUS:: Interrupt WRITE_STATE\n"));
				#if API_DEBUG_CODE
				printf("CBUS:: Interrupt WRITE_STATE\n");
				#endif

			reg_B0 = uData;
			if ( uData & BIT_DCAP_RDY )
			{
				//DEBUG_PRINT(MSG_DBG, ("CBUS:: Peer DevCap Ready\n"));
				#if API_DEBUG_CODE
				printf("CBUS:: Peer DevCap Ready\n");
				#endif
				SI_CbusSetDcapRdy(channel, true);
			}

		}
	}
#endif // define SWWA_21970

    return( result );
}



//------------------------------------------------------------------------------
// Function:    SI_CbusPortToChannel
// Description: Determine if the requested port is MHL
// Returns:     CBUS Channel if an MHL port, or 0xFF if not.
//
// Note:        Input parameter is NOT bounds-checked
//------------------------------------------------------------------------------

uint8_si SI_CbusPortToChannel ( uint8_si portIndex )
{
    return( l_PortToChannel[ portIndex ] );
}

//------------------------------------------------------------------------------
// Function:    SI_CbusChannelToPort
// Description: Determine which port is associated with the specified channel.
// Return:      Port number (0-4) or 0xFF if not found.
//
// Note:        Input parameter is NOT bounds-checked
//------------------------------------------------------------------------------

uint8_si SI_CbusChannelToPort ( uint8_si channel )
{
    return( l_ChannelToPort[ channel ] );
}



//------------------------------------------------------------------------------
// Function:    SI_CbusHandler
// Description: Check the state of any current CBUS message on specified channel.
//              Handle responses or failures and send any pending message if 
//              channel is IDLE.
// Parameters:  channel - CBUS channel to check
// Returns:     SUCCESS or one of CBUS_SOFTWARE_ERRORS_t
//------------------------------------------------------------------------------

uint8_si SI_CbusHandler ( uint8_si channel )
{
    uint8_si result = SUCCESS;

    if ( l_ChannelToPort[ channel ] == CBUS_NOPORT )   // Don't bother with disconnected channels
    {
        return( SUCCESS );
    }
    
    /* Check the channel interrupt status to see if anybody is  */
    /* talking to us. If they are, talk back.                   */

    result = CbusCheckInterruptStatus( channel );

    return( result );
}



//------------------------------------------------------------------------------
// Function:    SI_CbusUpdateBusStatus
// Description: Check the BUS status interrupt register for this channel and
//              update the channel data as needed.
//              channel.
// Parameters:  channel to check
// Returns:     TRUE    - connected
//              FALSE   - not connected
//
//  Note: This function should be called periodically to update the bus status
//
//------------------------------------------------------------------------------

bool_si SI_CbusUpdateBusStatus ( uint8_si channel )
{
    //uint8_si busStatus;

    //busStatus = SiIRegioCbusRead( REG_CBUS_BUS_STATUS, channel );

	//DJ: C8:08[0] has a bug?
    l_cbus[ channel].connected = g_MHL_Source_Connected;
	//DEBUG_PRINT(MSG_ALWAYS, ("busStatus: %02X, connected = %02X\n", (int)busStatus, (int)(l_cbus[ channel].connected)));

    //l_cbus[ channel].connected = g_MHL_Source_Connected;

    return( l_cbus[ channel].connected );
}



//------------------------------------------------------------------------------
// Function:    SI_CbusInitDevCap
// Description: Initialize device capability registers
// Returns:     none
//------------------------------------------------------------------------------
void SI_CbusInitDevCap( uint8_si channel )
{
    uint16_si    devcap_reg;

    devcap_reg = REG_CBUS_DEVICE_CAP_0;
		
    SiIRegioCbusWrite( devcap_reg++, channel, 0);          		// 0x00
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_VERSION);                 		// 0x01
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_DEVICE_CATEGORY );        		// 0x02
    SiIRegioCbusWrite( devcap_reg++, channel, 0);   								// 0x03
    SiIRegioCbusWrite( devcap_reg++, channel, 0);   								// 0x04
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_VIDEO_LINK_MODE_SUPORT);  		// 0x05
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_AUDIO_LINK_MODE_SUPORT);  		// 0x06
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_VIDEO_TYPE_SUPPORT);     			// 0x07
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_LOGICAL_DEVICE );     			// 0x08
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_BANDWIDTH_LIMIT);         		// 0x09
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_FEATURE_FLAG);     				// 0x0A
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_DEVICE_ID_H);   					// 0x0B
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_DEVICE_ID_L);   	     			// 0x0C
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_SCRATCHPAD_SIZE);		       		// 0x0D
    SiIRegioCbusWrite( devcap_reg++, channel, MHL_INT_STATUS_SIZE);					// 0x0E
    SiIRegioCbusWrite( devcap_reg++, channel, 0);  	// reserved			         		// 0x0F

}



//------------------------------------------------------------------------------
// Function:    SI_CbusInitialize
// Description: Attempts to intialize the CBUS. If register reads return 0xFF,
//              it declares error in initialization.
//              Initializes discovery enabling registers and anything needed in
//              config register, interrupt masks.
// Returns:     TRUE if no problem
//------------------------------------------------------------------------------

bool_si SI_CbusInitialize ( void )
{
	uint8_si		channel;
    bool_si      success = true;

    memset( &l_cbus, 0, sizeof( l_cbus ));

	l_PortToChannel[ 0 ] = 0;
    l_ChannelToPort[ 0 ] = 0;

    /* Initialize CBUS channels.    */

    for ( channel = 0; channel < MHL_MAX_CHANNELS; channel++ )
    {
		SI_CbusInitDevCap(channel);

        SiIRegioCbusWrite( REG_CBUS_INTR_ENABLE, channel, 0xFF );  // Enable all interrupts
        SiIRegioWrite(REG_CBUS_INTR_STATUS, BIT_MSC_MSG_RCV);//tiger , 12-07-2-11, bi3 hardware defualt value is 1,clear it when init; 
//      SiIRegioCbusWrite(REG_CBUS_LINK_LAYER_CTRL12,channel,0xA3);

    }
    
    return( success );
}

#else

bool_si SI_CbusInitialize ( void ) { return( true );}
uint8_si SI_CbusHandler ( uint8_si channel ) { channel = 0; return( true );}

bool_si SI_CbusMhlHpdState( uint8_si port, uint8_si newState ) { port = newState; return( false ); }

uint8_si SI_CbusPortToChannel( uint8_si port ) { port = 0xFF; return( port ); }
uint8_si SI_CbusChannelToPort( uint8_si channel ) { channel = 0xFF; return( channel ); }

bool_si SI_CbusRcpMessageSend( uint8_si channel, uint8_si command, uint8_si cmdData )
{
    channel = command = cmdData;
    return( false );
}
bool_si    SI_CbusChannelEnable( uint8_si channel, bool_si enable ) { channel = enable; return( false ); }

void    SI_CbusCbusEventMonitor( void ) {}


#endif
