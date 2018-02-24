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
/**
 * @file si_apiRCP.c
 *
 * RCP function of SiI1292
 * 
 * $Author: Silicon Image, firmware team
 * $Rev: 0.3
 * $Date: Apr. 2010
 *
 *****************************************************************************/

/***** #include statements ***************************************************/

#include "./SiI1292/MSC/si_apiRCP.h"
#include "CEC/si_apiCpi.h"
#include "./SiI1292/CEC/si_apiCEC.h"
#include "./SiI1292/CBUS/si_apiCbus.h"


//------------------------------------------------------------------------------
// Function:    	SI_IrRcpKeys
// Description: 	IR to RCP handler
// Parameters:	key: IR input Key
//				eventType: Key Pressed or Key Released
// Return:	 	false
//				1. Cbus driver return error
//				2. Unsupported Keys
//------------------------------------------------------------------------------
#if USE_Scaler_Standby_Mode
bool_si power_key_temp = 1;
#endif
bool_si SI_IrRcpKeys( uint8_si key, uint8_si eventType )
{

	bool_si result = false;
	uint8_si channel = SI_CbusPortToChannel(g_data.portSelect);

	//DEBUG_PRINT(MSG_DBG, ("Receive IR code: 0x%02X, EventType: 0x%02X\n", (int)key, (int)eventType));
	#if API_DEBUG_CODE
			printf("Receive IR code: 0x%02X, EventType: 0x%02X\n", (int)key, (int)eventType);
   	#endif
	
	if (eventType == KEY_DOWN)
	{
		cbus_out_queue_t req;
			
		//DEBUG_PRINT(MSG_DBG, ("Converting incoming IR command to RCP message\n"));
		#if API_DEBUG_CODE
			printf("Converting incoming IR command to RCP message\n");
		#endif
#if USE_Scaler_Standby_Mode
		{
			if((key == 0x40) && (power_key_temp == 0))
			{//[RC0x0C] Standby <<>> [CEC0x40]poweron
				SI_RapSendMsg(0, MHL_RAP_CMD_CONTENT_ON);
				power_key_temp = 1;
				#if API_DEBUG_CODE
				printf("RAP:: Send MHL_RAP_CMD_CONTENT_ON\n");
				#endif
				return result;
			}else if((key == 0x40) && (power_key_temp == 1))
			{//[RC0x0C] Standby <<>> [CEC0x40]poweroff
				SI_RapSendMsg(0, MHL_RAP_CMD_CONTENT_OFF);
				power_key_temp = 0;
				#if API_DEBUG_CODE
				printf("RAP:: Send MHL_RAP_CMD_CONTENT_OFF\n");
				#endif
				return result;
			}
		}
#endif
		#if API_DEBUG_CODE
		printf("Converting incoming IR command to RCP message\n");
		#endif
		req.command = MSC_MSG;
		req.msgData[0] = MHL_MSC_MSG_RCP;
		req.msgData[1] = key;
		//req.retry = 1;
 		req.retry = 0;
 		SI_CbusPushReqInOQ(channel, &req, false);

		//DEBUG_PRINT(MSG_DBG, ("Sending RCP message --> Key ID: %02X\n", (int)req.msgData[1]));
		#if API_DEBUG_CODE
			printf("Sending RCP message --> Key ID: %02X\n", (int)req.msgData[1]);
   		#endif
	}

	return result;

}



/*****************************************************************************/
/** 
 *  Cbus RCP operation: Send RCPE message
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          statusCode		including no error, ineffective code, responder busy
 *  
 *  @return             Result
 * 
 *****************************************************************************/
static uint8_si SI_RcpSendErr(uint8_si channel, uint8_si statusCode)
{
	uint8_si result = SUCCESS;
	cbus_out_queue_t req;

	req.command     = MSC_MSG;
	req.msgData[0]  = MHL_MSC_MSG_RCPE;
	req.msgData[1]  = statusCode;
	req.retry = 1;
	result = SI_CbusPushReqInOQ( channel, &req, false );

	//DEBUG_PRINT(MSG_DBG, ("RCP:: Sending RCPE -> Status Code: %02X\n", (int)statusCode));
	#if API_DEBUG_CODE
			printf("RCP:: Sending RCPE -> Status Code: %02X\n", (int)statusCode);
   	#endif

	return (result);
}



/*****************************************************************************/
/** 
 *  Cbus RCP operation: Send RCPK message
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          keyID			RCP Key ID
 *  
 *  @return             Result
 * 
 *****************************************************************************/
static uint8_si SI_RcpSendAck(uint8_si channel, uint8_si keyID)
{
	uint8_si result = SUCCESS;
	cbus_out_queue_t req;

	req.command     = MSC_MSG;
	req.msgData[0]  = MHL_MSC_MSG_RCPK;
	req.msgData[1]  = keyID;
	req.retry = 1;
	result = SI_CbusPushReqInOQ( channel, &req, false );

	//DEBUG_PRINT(MSG_DBG, ("RCP:: Sending RCPK --> Key ID: %02X\n", (int)keyID));
	#if API_DEBUG_CODE
			printf("RCP:: Sending RCPK --> Key ID: %02X\n", (int)keyID);
   	#endif

	return (result);
}



/*****************************************************************************/
/** 
 *  Cbus RCP operation: RCPK received handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          keyID			RCP Key ID
 *  
 *  @return             Result
 * 
 *****************************************************************************/
uint8_si SI_RcpAckRcvd(uint8_si channel, uint8_si keyID)
{
	uint8_si result = SUCCESS;
	uint8_si command, vsCmd, vsData, reqStatus;

	command = SI_CbusOQReqCmd(channel);
	vsCmd 	= SI_CbusOQReqData0(channel);
	vsData 	= SI_CbusOQReqData1(channel);
	reqStatus = SI_CbusOQReqStatus(channel);

	//DEBUG_PRINT(MSG_DBG, ("RCP:: RCPK Received <-- Key ID: %02X\n", (int)keyID));
	#if API_DEBUG_CODE
			printf("RCP:: RCPK Received <-- Key ID: %02X\n", (int)keyID);
   	#endif

	if ( (command == MSC_MSG) && (vsCmd == MHL_MSC_MSG_RCP) && (vsData == keyID) )
	{
		if(reqStatus == CBUS_REQ_WAITING)
		{
			// If the req status is waiting, it means it didn't receive RCPE before RCPK
			// If the req status is pending, there're 2 situations:
			// 1. it received RCPE (Responder busy), and is waiting to retry.
			// 2. it received RCPE (Ineffective KeyID), the current req is a new req.
			SI_CbusOQCleanActiveReq(channel);	
		}			
	}

	return (result);

}



/*****************************************************************************/
/** 
 *  Cbus RCP operation: RCPE received handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          statusCode		RCPE status code
 *  
 *  @return             Result
 * 
 *****************************************************************************/
uint8_si SI_RcpErrRcvd(uint8_si channel, uint8_si statusCode)
{
	uint8_si result = SUCCESS;

	//DEBUG_PRINT(MSG_DBG, ("RCP:: RCPE Received <-- Status Code: %02X\n", (int)statusCode));
	#if API_DEBUG_CODE
			printf("RCP:: RCPE Received <-- Status Code: %02X\n", (int)statusCode);
   	#endif

	if (statusCode == RCPE_INEFFECTIVE_KEY_CODE)
	{
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
		uint8_si msgData1;

		msgData1 = SI_CbusOQReqData1(channel);			
		SI_CbusPushKeytoIgnoreList(channel, msgData1, CBUS_OUT);		
#endif
	}
	else if (statusCode == RCPE_RESPONDER_BUSY)
	{
		uint8_si retry;
		
		retry = SI_CbusOQReqRetry(channel);
		if (retry > 0)
		{
			SI_CbusOQReduceReqRetry(channel);
			SI_CbusOQSetReqStatus(channel, CBUS_REQ_PENDING);
			SI_CbusOQSetReqTimeout(channel, 0);
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
 *  Cbus RCP operation: RCP timeout handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          direction		CBUS_IN or CBUS_OUT
 *  
 *  @return             Result
 * 
 *****************************************************************************/
uint8_si SI_RcpTimeoutHandler(uint8_si channel, uint8_si direction)
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
 *  Cbus RCP operation: RCP transfer done handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Result
 * 
 *****************************************************************************/
uint8_si SI_RcpTransferDoneHandler(uint8_si channel)
{
	uint8_si result = SUCCESS;
	uint8_si command;

	command = SI_CbusOQReqData0(channel);
	if (command == MHL_MSC_MSG_RCP)
	{
		SI_CbusOQSetReqTimeout(channel, DEM_MHL_RCP_TIMEOUT);
	}
	else if (command == MHL_MSC_MSG_RCPK)
	{
		SI_CbusOQCleanActiveReq(channel);
	}
	else if (command == MHL_MSC_MSG_RCPE)
	{
		uint8_si uData;

		uData = SI_CbusIQReqData(channel);//tiger sync to 9292
		SI_CbusOQCleanActiveReq(channel);
		result = SI_RcpSendAck(channel, uData);
	}

	return (result);

}



/*****************************************************************************/
/** 
 *  Cbus RCP operation: RCP Cec return handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          success		CEC return success or not
 *
 *  @return             Result
 * 
 *****************************************************************************/
void SI_RcpCecRetHandler(uint8_si channel, bool_si result)
{
	uint8_si uData;

	uData = SI_CbusIQReqData(channel);

	if (result)
	{
		SI_RcpSendAck(channel, uData);
		SI_CbusIQCleanActiveReq(channel);
	}
	else
	{
		SI_RcpSendErr(channel, RCPE_INEFFECTIVE_KEY_CODE);
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
		SI_CbusPushKeytoIgnoreList(channel, uData, CBUS_IN);
#endif
		SI_CbusIQCleanActiveReq(channel);		// SI_RcpSendErr will save the RCP Key ID temporaily in OQ.offsetData
	}
}



/*****************************************************************************/
/** 
 *  Cbus RCP operation: RCP handler
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             Result
 * 
 *****************************************************************************/

uint8_si SI_RcpHandler(uint8_si channel)
{
	uint8_si result = SUCCESS;
	uint8_si command, uData;

	command = SI_CbusIQReqCmd(channel);
	uData = SI_CbusIQReqData(channel);
	
	if (command == MHL_MSC_MSG_RCP)
	{
		bool_si ret;
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
		ret = SI_CbusKeyIDCheck(channel, (uData & 0x7F), CBUS_IN);
#else
		ret = SI_CbusKeyIDCheck((uData & 0x7F), CBUS_IN);
#endif
		if (ret)
			result = SI_RcpSendErr(channel, RCPE_INEFFECTIVE_KEY_CODE);
		else
			result = SI_RcpSendAck(channel, uData);

		//DEBUG_PRINT(MSG_DBG, ("RCP:: RCP Received <-- Key ID: %02X\n", (int)uData));
		#if API_DEBUG_CODE
			printf("RCP:: RCP Received <-- Key ID: %02X\n", (int)uData);
   		#endif
		SI_CbusIQCleanActiveReq(channel);
	}
	else if (command == MHL_MSC_MSG_RCPK)
	{
		uint8_si cmd, msgData0, msgData1, reqStatus;

		cmd = SI_CbusOQReqCmd(channel);
		msgData0 = SI_CbusOQReqData0(channel);
		msgData1 = SI_CbusOQReqData0(channel);
		reqStatus = SI_CbusOQReqStatus(channel);

		//DEBUG_PRINT(MSG_DBG, ("RCP:: RCPK Received <-- Key ID: %02X\n", (int)uData));
		#if API_DEBUG_CODE
			printf("RCP:: RCPK Received <-- Key ID: %02X\n", (int)uData);
   		#endif

		if ( (cmd == MSC_MSG) && (msgData0 == MHL_MSC_MSG_RCP) && (msgData1 == uData) )
		{
			if(reqStatus == CBUS_REQ_WAITING)
			{
				// If the req status is waiting, it means it didn't receive RCPE before RCPK
				// If the req status is pending, there're 2 situations:
				// 1. it received RCPE (Responder busy), and is waiting to retry.
				// 2. it received RCPE (Ineffective KeyID), the current req is a new req.
				SI_CbusOQCleanActiveReq(channel);	
			}			
		}
		
		SI_CbusIQCleanActiveReq(channel);
	}
	else if (command == MHL_MSC_MSG_RCPE)
	{
		//DEBUG_PRINT(MSG_DBG, ("RCP:: RCPE Received <-- Status Code: %02X\n", (int)uData));
		#if API_DEBUG_CODE
			printf("RCP:: RCPE Received <-- Status Code: %02X\n", (int)uData);
   		#endif

		if (uData == RCPE_INEFFECTIVE_KEY_CODE)
		{
#ifdef SUPPORT_MSCMSG_IGNORE_LIST
			uint8_si msgData1;

			msgData1 = SI_CbusOQReqData1(channel);	
					
			SI_CbusPushKeytoIgnoreList(channel, msgData1, CBUS_OUT);	
#endif	
		}
		else if (uData == RCPE_RESPONDER_BUSY)
		{
			uint8_si retry;
			
			retry = SI_CbusOQReqRetry(channel);
			if (retry > 0)
			{
				SI_CbusOQReduceReqRetry(channel);
				SI_CbusOQSetReqStatus(channel, CBUS_REQ_PENDING);
				SI_CbusOQSetReqTimeout(channel, 0);
			}
			else if (retry == 0)
			{
				SI_CbusOQCleanActiveReq(channel);
			}			
		}

		SI_CbusIQCleanActiveReq(channel);
	}

	return (result);

}

