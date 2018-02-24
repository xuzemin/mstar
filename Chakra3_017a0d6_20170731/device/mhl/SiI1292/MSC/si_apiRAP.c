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
//!file     si_apiRCP.c
//!brief    CP 1292 Starter Kit RCP functions.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009-2010, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include "./SiI1292/MSC/si_apiRAP.h"
#include "./SiI1292/CBUS/si_apiCbus.h"
#include "CEC/si_apiCpi.h"
#include "./SiI1292/CEC/si_apiCEC.h"

//ROM uint8_si RapSubCodeCmd[] =
uint8_si RapSubCodeCmd[]=
{
	MHL_RAP_CMD_POLL,
	MHL_RAP_CMD_CONTENT_ON,
	MHL_RAP_CMD_CONTENT_OFF
};

bool_si IsThisRapMsgInCategoryC(uint8_si rapStatusCode)
{
	int i;
	bool_si result = false;
 
	for( i = 0; i < 3; i++)
	{
		if ( rapStatusCode == RapSubCodeCmd[i])
		{
			result = true;
			break;
		}
	}

	return result;
}
/*****************************************************************************/
/** 
 *  Cbus RAP operation: Send RAPK message
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          statusCode		including no error, Unrecognized Action Code, Unsupported Action Code, responder busy
 *  
 *  @return             Result
 * 
 *****************************************************************************/
bool_si SI_RapSendAck(uint8_si channel, uint8_si statusCode)
{
	bool_si result = false;
	cbus_out_queue_t	req;

	req.command     = MSC_MSG;
	req.msgData[0]  = MHL_MSC_MSG_RAPK; 
	req.msgData[1]  = statusCode; 
	req.retry = 1;
    result = SI_CbusPushReqInOQ( channel, &req, false );
	
	//DEBUG_PRINT(MSG_DBG, ("RAP:: Sending RAPK --> Status Code: %02X\n", (int)statusCode));
	 #if API_DEBUG_CODE
		printf("RAP:: Sending RAPK --> Status Code: %02X\n", (int)statusCode);
   	#endif
	
    return( result);
}
/*****************************************************************************/
/** 
 *  Cbus RAP operation: Send RAP message
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          rapKeyCode	RAP Key ID
 *  
 *  @return             Result
 * 
 *****************************************************************************/
bool_si SI_RapSendMsg(uint8_si channel, uint8_si rapKeyCode)
{
	bool_si result = false;
	cbus_out_queue_t	req;

	req.command     = MSC_MSG;
	req.msgData[0]  = MHL_MSC_MSG_RAP; 
	req.msgData[1]  = rapKeyCode; 
	req.retry = 0;//Keno20120305, disable retry 1 to 0.
	result = SI_CbusPushReqInOQ( channel, &req, false );
    return( result);
}
/*****************************************************************************/
/** 
 *  Cbus RAP operation: RAP Handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Result
 * 
 *****************************************************************************/
bool_si SI_RapHandler(uint8_si channel)
{
	bool_si result = false;
	uint8_si command;
	uint8_si rapKeyCode;
	
	command = SI_CbusIQReqCmd(channel);
	rapKeyCode = SI_CbusIQReqData(channel);
	
	if (command == MHL_MSC_MSG_RAP)
	{

		//DEBUG_PRINT(MSG_DBG, ("RAP:: RAP Received <-- Key ID: %02X\n", (int)rapKeyCode));
		#if API_DEBUG_CODE
		printf("RAP:: RAP Received <-- Key ID: %02X\n", (int)rapKeyCode);
   		#endif
		if ( !IsThisRapMsgInCategoryC(rapKeyCode) )
		{
			//DEBUG_PRINT( MSG_ALWAYS, ("SI_RcpMsgHandler: unrecognized Key Code: %s", (int)rapKeyCode) );
			#if API_DEBUG_CODE
			printf("SI_RcpMsgHandler: unrecognized Key Code: %s", (int)rapKeyCode);
   			#endif
			SI_RapSendAck(channel, RAP_UNRECOGNIZED);
			SI_CbusIQCleanActiveReq(channel);
			return result;
		}

		switch ( rapKeyCode )
		{
			case MHL_RAP_CMD_POLL:
				SI_RapSendAck(channel, RAP_NOERROR);
				SI_CbusIQCleanActiveReq(channel);
				break;
			case MHL_RAP_CMD_CONTENT_ON:					
				SiIRegioModify(REG_TX_SWING1, BIT_SWCTRL_EN, BIT_SWCTRL_EN);
				//DEBUG_PRINT(MSG_DBG, ("RAP:: CONTENT ON!"));
				#if API_DEBUG_CODE
				printf("RAP:: CONTENT ON!");
   				#endif
				SiIRegioWrite(0x00A, 0x3);/*Restore orignial value, see bug22585*/
				SI_RapSendAck(channel, RAP_NOERROR);
				SI_CbusIQCleanActiveReq(channel);
				break;
			case MHL_RAP_CMD_CONTENT_OFF:
				SiIRegioWrite(0x00A, 0x0);/*set it to 0 to enable TMDS Swing control, see bug22585*/
				SiIRegioModify(REG_TX_SWING1, BIT_SWCTRL_EN, 0);
				//DEBUG_PRINT(MSG_DBG, ("RAP:: CONTENT OFF!"));
				#if API_DEBUG_CODE
				printf("RAP:: CONTENT OFF!");
   				#endif
				SI_RapSendAck(channel, RAP_NOERROR);
				SI_CbusIQCleanActiveReq(channel);
				break;
			default:
				//DEBUG_PRINT( MSG_ALWAYS, ("SI_RcpMsgHandler: unrecognized Key Code: %s", (int)rapKeyCode) );
				#if API_DEBUG_CODE
				printf("SI_RcpMsgHandler: unrecognized Key Code: %s", (int)rapKeyCode);
   				#endif
				SI_RapSendAck(channel, RAP_UNRECOGNIZED);
				SI_CbusIQCleanActiveReq(channel);
				break;
		}

	}
	else
	{
		//DEBUG_PRINT( MSG_DBG, ("CBUS:: Received <-- MHL_MSC_MSG_RAPK\n"));
		#if API_DEBUG_CODE
			printf("CBUS:: Received <-- MHL_MSC_MSG_RAPK\n");
   		#endif
		SI_CbusIQCleanActiveReq(channel);
		result = SI_RapAckRcvd(channel, rapKeyCode);		
	}
	return result;
	
}
/*****************************************************************************/
/** 
 *  Cbus RAP operation: Send RAP message
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          rapKeyCode	RAP Key ID
 *  
 *  @return             Result
 * 
 *****************************************************************************/
bool_si SI_RapAckRcvd(uint8_si channel, uint8_si rapKeyCode)
{
	//DEBUG_PRINT(MSG_DBG, ("RAP:: RAPK Received <-- Status Code: %02X\n", (int)rapKeyCode));
	#if API_DEBUG_CODE
			printf("RAP:: RAPK Received <-- Status Code: %02X\n", (int)rapKeyCode);
   	#endif
		
	if (rapKeyCode)
		SI_RapErrProcess ( channel, rapKeyCode );
	else
		SI_CbusOQCleanActiveReq(channel);
	return SUCCESS;
}
/*****************************************************************************/
/** 
 *  Cbus RAP operation:  RAP error process
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          rapStatusCode	including Unrecognized Action Code, Unsupported Action Code, responder busy
 *  
 *  @return             Result
 * 
 *****************************************************************************/
bool_si SI_RapErrProcess(uint8_si channel, uint8_si rapStatusCode)
{	
#if IS_CEC
	SI_CpiData_t cecFrame;
#endif
	uint8_si retry;

	switch (rapStatusCode)
	{
		case RAP_UNRECOGNIZED:
		case RAP_UNSUPPORTED:

#ifdef SUPPORT_MSCMSG_IGNORE_LIST
			//add to ignore list
			SI_CbusOQCleanActiveReq(channel);
			if (rapStatusCode == MHL_RAP_CMD_CONTENT_ON)
				SI_CbusPushKeytoIgnoreList(channel, MHL_RAP_CMD_CONTENT_ON_IREG, CBUS_OUT);
			if (rapStatusCode == MHL_RAP_CMD_CONTENT_OFF)
				SI_CbusPushKeytoIgnoreList(channel, MHL_RAP_CMD_CONTENT_OFF_IREG, CBUS_OUT);
#endif
#if IS_CEC
			//feature abort
			cecFrame.opcode        = CECOP_FEATURE_ABORT;
	        cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_TV );	
	        cecFrame.args[0]       = rapStatusCode;
	        cecFrame.args[1]       = CECAR_UNRECOG_OPCODE;
	        cecFrame.argCount      = 2;
	        SI_CpiWrite( &cecFrame );				
#endif
			break;
		case RAP_BUSY:
			retry = SI_CbusOQReqRetry(channel);
			if (retry > 0)
			{
				SI_CbusOQReduceReqRetry(channel);
				SI_CbusOQSetReqStatus(channel, CBUS_REQ_PENDING);
			}
			else if (retry == 0)
			{
				SI_CbusOQCleanActiveReq(channel);
			}
			break;	
	}
	return SUCCESS;
}
/*****************************************************************************/
/** 
 *  Cbus RAP operation: RAP timeout handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          direction		include CBUS_IN and CBUS_OUT
 *  
 *  @return             Result
 * 
 *****************************************************************************/
bool_si SI_RapTimeoutHandler(uint8_si channel, uint8_si direction)
{
	uint8_si result = SUCCESS;

	if (direction == CBUS_IN)
	{
		SI_CbusIQCleanActiveReq(channel);
	}
	else if (direction == CBUS_OUT)
	{
		uint8_si retry;
		
		retry = SI_CbusOQReqRetry(channel);
		if (retry > 0)
		{
			SI_CbusOQReduceReqRetry(channel);
			SI_CbusOQSetReqStatus(channel, CBUS_REQ_PENDING);
		}
		else if (retry == 0)
		{
			SI_CbusOQCleanActiveReq(channel);
		}					
	}

	return (result);
}
/*****************************************************************************/
/** 
 *  Cbus RAP operation: RAP transfer donw handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Result
 * 
 *****************************************************************************/
uint8_si SI_RapTransferDoneHandler(uint8_si channel)
{
	uint8_si result = SUCCESS;
	uint8_si command;

	command = SI_CbusOQReqData0(channel);
	if (command == MHL_MSC_MSG_RAP)
	{
		SI_CbusOQSetReqTimeout(channel, DEM_MHL_RCP_TIMEOUT);
	}
	else if (command == MHL_MSC_MSG_RAPK)
	{
		SI_CbusOQCleanActiveReq(channel);
	}

	return (result);

}

/*****************************************************************************/
/** 
 *  Cbus RAP operation: RAP ignore keyID check
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          keyID			RAP Key ID
 *  @param[in]          direction		include CBUS_IN and CBUS_OUT
 *  
 *  @return             Result
 * 
 *****************************************************************************/
#if 0//Keno20120301, disable RK design, because it will effect that cannot display
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
bool_si SI_RapKeyIDCheck(uint8_si channel, uint8_si keyID, uint8_si direction)
#else
bool_si SI_RapKeyIDCheck(uint8_si keyID, uint8_si direction)
#endif
{
	bool_si ret;

	ret = false;
	if (keyID == MHL_RAP_CMD_CONTENT_ON)
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
		ret = SI_CbusKeyIDCheck(channel, MHL_RAP_CMD_CONTENT_ON_IREG, direction);
#else
		ret = SI_CbusKeyIDCheck(MHL_RAP_CMD_CONTENT_ON_IREG, direction);
#endif
	if (keyID == MHL_RAP_CMD_CONTENT_OFF)
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
		ret = SI_CbusKeyIDCheck(channel, MHL_RAP_CMD_CONTENT_OFF_IREG, direction);
#else
		ret = SI_CbusKeyIDCheck(MHL_RAP_CMD_CONTENT_OFF_IREG, direction);
#endif

	return (ret);
}
#endif

/*****************************************************************************/
/** 
 *  Cbus RAP operation: RAP cec return handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          success		if return successfully
 *  
 *  @return             Result
 * 
 *****************************************************************************/
void SI_RapCecRetHandler(uint8_si channel, bool_si result)
{
	uint8_si uData;

	uData = SI_CbusIQReqData(channel);

	if (result)
	{
		SI_RapSendAck(channel, RAP_NOERROR);
		SI_CbusIQCleanActiveReq(channel);
	}
	else
	{
		SI_RapSendAck(channel, RAP_UNSUPPORTED);

#ifdef SUPPORT_MSCMSG_IGNORE_LIST
		if (uData == MHL_RAP_CMD_CONTENT_ON)
				SI_CbusPushKeytoIgnoreList(channel, MHL_RAP_CMD_CONTENT_ON_IREG, CBUS_IN);
		if (uData == MHL_RAP_CMD_CONTENT_OFF)
				SI_CbusPushKeytoIgnoreList(channel, MHL_RAP_CMD_CONTENT_OFF_IREG, CBUS_IN);
#endif
		SI_CbusIQCleanActiveReq(channel);		// SI_RcpSendErr will save the RCP Key ID temporaily in OQ.offsetData
	}
}


