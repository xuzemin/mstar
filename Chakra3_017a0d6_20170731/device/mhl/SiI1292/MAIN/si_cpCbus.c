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
//!file     si_cpCBUS.c
//!brief    CP 9387 Starter Kit CDC demonstration code.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include "./SiI1292/MAIN/si_cp1292.h"
#include "./SiI1292/CBUS/si_apiCbus.h"
#include "./SiI1292/CEC/si_cec_enums.h"


#if (IS_CBUS == 1)


//------------------------------------------------------------------------------
// Function:    CbusConnectionCheck
// Description: Display any change in CBUS connection state and enable
//              CBUS heartbeat if channel has been connected.
// Parameters:  channel - CBUS channel to check
//------------------------------------------------------------------------------

static void CbusConnectionCheck ( uint8_si channel )
{
    static bool_si busConnected[ MHL_MAX_CHANNELS ] = {false};
    static bool_si hpd[ MHL_MAX_CHANNELS ] = {false};
    static bool_si rsen[ MHL_MAX_CHANNELS ] = {false};
	static uint32_si count = 0;
	static bool_si timer_set = false;
	uint8_si result;
	cbus_out_queue_t req;

    /* If CBUS connection state has changed for this channel,   */
    /* update channel state and hardware.                       */

    if ( busConnected[ channel ] != SI_CbusChannelConnected( channel ))
    {
        busConnected[ channel ] = SI_CbusChannelConnected( channel );


		#if API_DEBUG_CODE
       if ( busConnected[ channel] )
		printf("CBUS::  busConnected[ channel] = 1\n");
	else
		printf("CBUS::  busConnected[ channel] = 0\n");
		#endif	

		if ( !busConnected[ channel ] )
		{
            SiIRegioModify(REG_SRST, BIT_CBUS_RST, BIT_CBUS_RST);	// Reset CBUS block after CBUS disconnection
			SiIRegioModify(REG_SRST, BIT_CBUS_RST, 0);
			SI_CbusInitParam(channel);

			hpd[channel] = false;
			rsen[channel] = false;
			count = 0;

//			DEBUG_PRINT(MSG_DBG, ("after reset CBUS,CBUS PAGE: 0x3C = %02X\n", (int)SiIRegioCbusRead(REG_CBUS_LINK_LAYER_CTRL12,channel)));
            //fixed when abort packet received, not wait 2s.
            //write  REG_RX_MISC again when CBUS is reset; 
            SiIRegioModify(REG_RX_MISC, BIT_PSCTRL_OEN|BIT_PSCTRL_OUT|BIT_PSCTRL_AUTO|BIT_HPD_RSEN_ENABLE, 0); 
   
		}   

#ifdef SUPPORT_MSCMSG_IGNORE_LIST
		SI_CbusResetMscMsgIgnoreList(channel, CBUS_OUT);
#endif
		SI_CbusInitDevCap(channel);
//      SiIRegioCbusWrite(REG_CBUS_LINK_LAYER_CTRL12,channel,0xA3);  //tiger add this ,request from jason 2011-8-4
//      //CBUS 0X3C IS SET TO DEFAULTS ,when CBUS connection status changed;

        SiIRegioWrite(REG_CBUS_INTR_STATUS, BIT_MSC_MSG_RCV);//tiger , 12-07-2-11, bi3 hardware defualt value is 1,clear it when init; 
    }

	if ( busConnected[ channel] )
	{
		bool_si connect_wait, hpd_state, path_enable, connect_ready, dcap_rdy, read_info;

		connect_wait = SI_CbusGetConnectWait(channel);
		hpd_state	 = SI_CbusGetHpdState(channel);
		path_enable  = SI_CbusGetPathEnable(channel);
		connect_ready= SI_CbusGetConnectReady(channel);		
		dcap_rdy	 = SI_CbusGetDcapRdy(channel);
		read_info    = SI_CbusGetReadInfo(channel);

			#if API_DEBUG_CODE
	        if ( connect_wait)
			printf("CBUS::  connect_wait = 1\n");
		else
			printf("CBUS::  connect_wait = 0\n");
			#endif
		if ( !connect_wait )
		{
			if (!timer_set)
			{
				timer_set = true;
				count = timer_count;
			}
			else
			{
				if( HalTimerDelay(count, 2) )
				{
					SI_CbusSetConnectWait(channel, true);
					count = 0;
					timer_set= false;
					connect_wait = SI_CbusGetConnectWait(channel);
				}
			}
		}

		if ( connect_wait )
		{
			if ( hpd[channel] != g_HPD_IN )
			{
				hpd[channel] = g_HPD_IN;

				if ( hpd[channel] )
				{
					//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: SET HPD\n"));
					#if API_DEBUG_CODE
					printf("CBUS:: SET HPD\n");
    					#endif
					req.command = MSC_SET_HPD;
					req.dataRetHandler = SI_MscSetHpd;
					req.retry = 5;	// retry 2 times if timeout or abort for important MSC commands
					result = SI_CbusPushReqInOQ( channel, &req, true );
					
					if ( result != SUCCESS )
					{
						//DEBUG_PRINT(MSG_DBG, ("CBUS:: Error found in SI_CbusPushReqInOQ: %02X\n", (int)result));
						#if API_DEBUG_CODE
						printf("CBUS:: Error found in SI_CbusPushReqInOQ: %02X\n", (int)result);
    						#endif
						
						hpd[channel] = !g_HPD_IN;
					}
				}
				else
				{
					//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: CLR HPD\n"));
					#if API_DEBUG_CODE
						printf("CBUS:: CLR HPD\n");
    					#endif
					
					req.command = MSC_CLR_HPD;
					req.dataRetHandler = SI_MscClrHpd;	// will send disable path in SI_MscClrHpd
					req.retry = 5;	// retry 2 times if timeout or abort for important MSC commands
					result = SI_CbusPushReqInOQ( channel, &req, true );
					
					if ( result != SUCCESS )
					{
						//DEBUG_PRINT(MSG_DBG, ("CBUS:: Error found in SI_CbusPushReqInOQ: %02X\n", (int)result));
						#if API_DEBUG_CODE
						printf("CBUS:: Error found in SI_CbusPushReqInOQ: %02X\n", (int)result);
    						#endif
						
						hpd[channel] = !g_HPD_IN;
					}
#ifdef SUPPORT_MSCMSG_IGNORE_LIST					
					SI_CbusResetMscMsgIgnoreList(channel, CBUS_IN);
#endif
				}
			}
		}
		
		/*if ( hpd_state )
		{
			if (rsen[channel] != g_TX_RSEN_Valid)
			{
				rsen[channel] = g_TX_RSEN_Valid;

				if( rsen[channel] )
				{
					DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: Path Enable\n"));			
					req.command     = MSC_WRITE_STAT;
					req.offsetData  = MHL_DEVICE_STATUS_LINK_MODE_REG_OFFSET;
					req.msgData[0]	= PATH_EN;
					req.dataRetHandler = SI_MscPathEnable;
					req.retry = 2;	// retry 2 times if timeout or abort for important MSC commands
					result = SI_CbusPushReqInOQ( channel, &req, true );

					if ( result != SUCCESS )
					{
						DEBUG_PRINT(MSG_DBG, ("CBUS:: Error found in SI_CbusPushReqInOQ: %02X\n", (int)result));
						rsen[channel] = !g_TX_RSEN_Valid;
					}					
				}
			}
		}*/

		if ( path_enable )
		{
			if ( !connect_ready )
			{
				//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: Connected Ready\n"));	
				#if API_DEBUG_CODE
						printf("CBUS:: Connected Ready\n");
    				#endif
				
				req.command     = MSC_WRITE_STAT;
				req.offsetData  = MHL_DEVICE_STATUS_CONNECTED_RDY_REG_OFFSET;
				req.msgData[0]	= DCAP_RDY;
				req.dataRetHandler = SI_MscConnectReady;
				req.retry = 2;	// retry 2 times if timeout or abort for important MSC commands
				result = SI_CbusPushReqInOQ( channel, &req, true );

				if ( result != SUCCESS )
				{
					//DEBUG_PRINT(MSG_DBG, ("CBUS:: Error found in SI_CbusPushReqInOQ: %02X\n", (int)result));
					#if API_DEBUG_CODE
						printf("CBUS:: Error found in SI_CbusPushReqInOQ: %02X\n", (int)result);
    					#endif
				}					
				else
				{
					SI_CbusSetConnectReady(channel, true);
				}
			}
		}

		if ( connect_ready)
		{
			if ((!( read_info & DCAP_READ_DONE )) && dcap_rdy)
			{
				SI_MscStartGetDevInfo(channel);
			}
		}
	}
	
}

//------------------------------------------------------------------------------
// Function:    CpCbusProcessPrivateMessage
// Description: Get the result of the last message sent and use it appropriately
//              or process a request from the connected device.
// Parameters:  channel - CBUS channel that has message data for us.
//------------------------------------------------------------------------------

 uint8_si CpCbusProcessPrivateMessage ( uint8_si channel )
{
	uint8_si result, result1, result2;
	
	result1 = SI_CbusIQReqStatusCheck(channel);
	result2 = SI_CbusOQReqStatusCheck(channel);	
	result = result1 | result2;

	return (result);
}


//------------------------------------------------------------------------------
// Function:    CpCbusHandler
// Description: Polls the send/receive state of the CBUS hardware.
//------------------------------------------------------------------------------

void CpCbusHandler ( void )
{
    uint8_si channel, status;

	/* Check the current input to see if it switch between HDMI and MHL */

	if ( (g_currentInputMode == HDMI) )
		return;

    /* Monitor all CBUS channels.   */

    for ( channel = 0; channel < MHL_MAX_CHANNELS; channel++ )
    {
        /* Update CBUS status.  */
        SI_CbusUpdateBusStatus( channel );
        CbusConnectionCheck( channel );

        /* Monitor CBUS interrupts. */
        status = SI_CbusHandler( channel );
        if ( status != SUCCESS )
        {
            //DEBUG_PRINT(MSG_DBG, ("Error returned from SI_CbusHandler: %02X\n", (int)status));
            #if API_DEBUG_CODE
		printf("Error returned from SI_CbusHandler: %02X\n", (int)status);
    	     #endif
        }
		status = CpCbusProcessPrivateMessage( channel );
        if ( status != SUCCESS )
        {
            //DEBUG_PRINT(MSG_DBG, ("Error returned from CpCbusProcessPrivateMessage: %02X\n", (int)status));
            #if API_DEBUG_CODE
		printf("Error returned from CpCbusProcessPrivateMessage: %02X\n", (int)status);
    	     #endif
        }
    }
}



//------------------------------------------------------------------------------
// Function:    CpCbusInitialize
// Description: Initialize the CBUS subsystem and enabled the default channels
//------------------------------------------------------------------------------

void CpCbusInitialize ( void )
{

    SI_CbusInitialize();
	SI_MscInitialize();
}


#else

bool_si  CpCbusSendRcpMessage ( uint8_si port, uint8_si keyData ) { port = keyData; return( true ); }
void    CpCbusHandler ( void ) {}
void    CpCbusInitialize( void ) {}

#endif
