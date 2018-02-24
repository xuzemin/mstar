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
//!file     si_apiMSC.c
//!brief    CP 1292 Starter Kit MSC functions.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009-2010, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/
/**
 * @file si_apiMSC.c
 *
 * MSC command function of SiI1292
 * 
 * $Author: Silicon Image, firmware team
 * $Rev: 0.3
 * $Date: Apr. 2010
 *
 *****************************************************************************/

/***** #include statements ***************************************************/

#include "./SiI1292/MSC/si_apiMSC.h"

/***** public functions *******************************************************/

/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: CLR_HPD
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscClrHpd(uint8_si channel, uint8_si uData)
{
	cbus_out_queue_t req;
	uData = uData;
	
	SI_CbusSetHpdState(channel, false);	
	SI_CbusOQCleanActiveReq(channel);

	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: Path Disable\n"));	
	#if API_DEBUG_CODE
	printf("CBUS:: Path Disable\n");
	#endif
	req.command     = MSC_WRITE_STAT;
	req.offsetData  = MHL_DEVICE_STATUS_LINK_MODE_REG_OFFSET;
	req.msgData[0]	= 0;
	req.dataRetHandler = SI_MscPathDisable;
	req.retry = 2;	// retry 2 times if timeout or abort for important MSC commands
	SI_CbusPushReqInOQ( channel, &req, true );				

	return (true);
	
}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: SET_HPD
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscSetHpd(uint8_si channel, uint8_si uData)
{
	cbus_out_queue_t req;
	uData = uData;

 	//Jin: Fix for Bug#22149
    //SiIRegioCbusWrite( REG_CBUS_DEVICE_CAP_0, channel, POWER_STATE_ACTIVE);

	SI_CbusSetHpdState(channel, true);	
	SI_CbusOQCleanActiveReq(channel);

	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: Path Enable\n"));		
	#if API_DEBUG_CODE
	printf("CBUS:: Path Enable\n");
	#endif
	req.command     = MSC_WRITE_STAT;
	req.offsetData  = MHL_DEVICE_STATUS_LINK_MODE_REG_OFFSET;
	req.msgData[0]	= PATH_EN;
	req.dataRetHandler = SI_MscPathEnable;
	req.retry = 2;	// retry 2 times if timeout or abort for important MSC commands
	SI_CbusPushReqInOQ( channel, &req, true );				

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: SET_INT, GRT_WRT
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscGrtWrt(uint8_si channel, uint8_si uData)
{
	uData = uData;

	SI_CbusSetGrtWrt(channel, true);
	SI_CbusOQCleanActiveReq(channel);

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: WRITE_STAT, Path enable
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscPathEnable(uint8_si channel, uint8_si uData)
{
	uData = uData;

	SI_CbusSetPathEnable(channel, true);
	SI_CbusOQCleanActiveReq(channel);

	return (true);
}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: WRITE_STAT, Path enable
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscPathDisable(uint8_si channel, uint8_si uData)
{
	uData = uData;

	SI_CbusSetPathEnable(channel, false);
	SI_CbusOQCleanActiveReq(channel);

	return (true);

}

/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: SET_INT, DCAP_CHG
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI9292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscDevCapChange(uint8_si channel, uint8_si uData)
{
	uData = uData;

	SI_CbusOQCleanActiveReq(channel);

	return (true);
}

/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: WRITE_STAT, Connect Ready
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscConnectReady(uint8_si channel, uint8_si uData)
{
    cbus_out_queue_t req;
	uData = uData;

	SI_CbusOQCleanActiveReq(channel);

    //after send DCAP_RDY, send DCAP_CHG to inform source to read devcap , tiger qin 08-10-2011 
      
    req.command     = MSC_SET_INT;
    req.offsetData  = MHL_REG_CHANGE_INT_OFFSET;
    req.msgData[0]	= CBUS_INT_BIT_DCAP_CHG;
    req.dataRetHandler = SI_MscDevCapChange;
    req.retry = 2;	// retry 2 times if timeout or abort for important MSC commands

    SI_CbusPushReqInOQ( channel, &req, true );
    //DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: Self Device Capability Registers Change\n"));
    	#if API_DEBUG_CODE
	printf("CBUS:: Self Device Capability Registers Change\n");
	#endif
	return (true);

}

/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: READ_DEVCAP, bandwidth info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscReadBandwidth(uint8_si channel, uint8_si uData)
{
	uint32_si frequency;
//	uint8_si  tmp = 0 ;
	PeerDevCap[9] = uData;

	if ( uData == 0 )
	{
		//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: No Bandwidth is indicated\n"));
	    	#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: No Bandwidth is indicated\n");
		#endif
	}
	else
	{
		frequency = uData * 5;
		//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Bandwidth: %dMHz\n", (int)frequency));	
		#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: Bandwidth: %dMHz\n", (int)frequency);
		#endif
	}

	SI_CbusSetReadInfo(channel, DCAP_READ_DONE);//finish read 
	SI_CbusOQCleanActiveReq(channel);

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: READ_DEVCAP, video type info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscReadVideoType(uint8_si channel, uint8_si uData)
{
	PeerDevCap[7] = uData;

	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Support Video Type: "));	
		#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: Support Video Type: ");
		#endif
#if API_DEBUG_CODE

	if ( uData & SUPP_VT )
	{
		if( uData & VT_GRAPHICS)
			//DEBUG_PRINT(MSG_ALWAYS, ("Graphics type of video content; "));	
			#if API_DEBUG_CODE
			printf("Graphics type of video content; ");
			#endif
		if( uData & VT_PHOTO)
			//DEBUG_PRINT(MSG_ALWAYS, ("Photo type of video content; "));
			#if API_DEBUG_CODE
			printf("Photo type of video content; ");
			#endif
		if( uData & VT_CINEMA)
			//DEBUG_PRINT(MSG_ALWAYS, ("Cinema type of video content; "));	
			#if API_DEBUG_CODE
			printf("Cinema type of video content; ");
			#endif
		if( uData & VT_GAME)
			//DEBUG_PRINT(MSG_ALWAYS, ("Game type of video content; "));		
			#if API_DEBUG_CODE
			printf("Game type of video content; ");
			#endif
	}
	else
	{
		//DEBUG_PRINT(MSG_ALWAYS, ("None"));		
		#if API_DEBUG_CODE
			printf("None");
		#endif
	}
#endif

	//DEBUG_PRINT(MSG_ALWAYS, ("\n"));	
	#if API_DEBUG_CODE
		printf("\n");
	#endif
	
	SI_CbusSetReadInfo(channel, ((SI_CbusGetReadInfo(channel)&DCAP_ITEM_INDEX_MASK) +1) &(~ DCAP_ITEM_READ_DOING));//finsh read 	

	SI_CbusOQCleanActiveReq(channel);

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: READ_DEVCAP, audio link mode info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscReadAudioLinkMode(uint8_si channel, uint8_si uData)
{
	PeerDevCap[6] = uData;

	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Audio Link Mode: "));	
	#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: Audio Link Mode: ");
	#endif

#if API_DEBUG_CODE
	if ( uData == 0 )
	{
		//DEBUG_PRINT(MSG_ALWAYS, ("None"));		
		#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: Audio Link Mode: ");
		#endif
	}
	else
	{
		if( uData & AUD_2CH )
			//DEBUG_PRINT(MSG_ALWAYS, ("2-Channel PCM audio streams (with Layout 0 audio data packets) "));
			#if API_DEBUG_CODE
			printf("2-Channel PCM audio streams (with Layout 0 audio data packets) ");
			#endif
		if( uData & AUD_8CH )
			//DEBUG_PRINT(MSG_ALWAYS, ("8-channel PCM audio streams (with Layout 1 audio data packets) "));	
			#if API_DEBUG_CODE
			printf("8-channel PCM audio streams (with Layout 1 audio data packets) ");
			#endif
	}
#endif
	//DEBUG_PRINT(MSG_ALWAYS, ("\n"));		
	#if API_DEBUG_CODE
		printf("\n");
	#endif
	SI_CbusSetReadInfo(channel, ((SI_CbusGetReadInfo(channel)&DCAP_ITEM_INDEX_MASK) +1) &(~ DCAP_ITEM_READ_DOING));//finsh read 

	SI_CbusOQCleanActiveReq(channel);

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: READ_DEVCAP, video link mode info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscReadVideoLinkMode(uint8_si channel, uint8_si uData)
{
	PeerDevCap[5] = uData;

	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Video Link Mode: "));	
	#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: Video Link Mode: ");
	#endif

#if API_DEBUG_CODE
	if ( uData == 0 )
	{
		//DEBUG_PRINT(MSG_ALWAYS, ("None"));		
		#if API_DEBUG_CODE
			printf("None");
		#endif
	}
	else
	{
		if( uData & SUPP_RGB444 )
			//DEBUG_PRINT(MSG_ALWAYS, ("RGB 4:4:4 "));	
			#if API_DEBUG_CODE
			printf("RGB 4:4:4 ");
			#endif
		if( uData & SUPP_YCBCR444 )
			//DEBUG_PRINT(MSG_ALWAYS, ("YCBCR 4:4:4 "));		
			#if API_DEBUG_CODE
			printf("YCBCR 4:4:4 ");
			#endif
		if( uData & SUPP_YCBCR422 )
			//DEBUG_PRINT(MSG_ALWAYS, ("YCBCR 4:2:2 "));		
			#if API_DEBUG_CODE
			printf("YCBCR 4:2:2 ");
			#endif
		if( uData & SUPP_PPIXEL )
			//DEBUG_PRINT(MSG_ALWAYS, ("Packed Pixel "));		
			#if API_DEBUG_CODE
			printf("Packed Pixel ");
			#endif
		if( uData & SUPP_ISLANDS)
			//DEBUG_PRINT(MSG_ALWAYS, ("Data Islands "));	
			#if API_DEBUG_CODE
			printf("Data Islands ");
			#endif
			
	}
#endif
	//DEBUG_PRINT(MSG_ALWAYS, ("\n"));		
	#if API_DEBUG_CODE
		printf("\n");
	#endif
	SI_CbusSetReadInfo(channel, ((SI_CbusGetReadInfo(channel)&DCAP_ITEM_INDEX_MASK) +1) &(~ DCAP_ITEM_READ_DOING));//finsh read 
	SI_CbusOQCleanActiveReq(channel);

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: READ_DEVCAP, Logical device map info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscReadLogDevMap(uint8_si channel, uint8_si uData)
{
	PeerDevCap[8] = uData;

	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Log Dev Map: "));		
	#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: Log Dev Map: ");
	#endif

#if API_DEBUG_CODE
	if ( uData == 0 )
	{
		//DEBUG_PRINT(MSG_ALWAYS, ("None"));		
		#if API_DEBUG_CODE
		printf("None");
		#endif
	}
	else
	{
		if( uData & LD_DISPLAY )
			//DEBUG_PRINT(MSG_ALWAYS, ("Display "));	
			#if API_DEBUG_CODE
			printf("Display ");
			#endif
		if( uData & LD_VIDEO )
			//DEBUG_PRINT(MSG_ALWAYS, ("Video "));	
			#if API_DEBUG_CODE
			printf("Video ");
			#endif
		if( uData & LD_AUDIO )
			//DEBUG_PRINT(MSG_ALWAYS, ("Audio "));		
			#if API_DEBUG_CODE
			printf("Audio ");
			#endif
		if( uData & LD_MEDIA )
			//DEBUG_PRINT(MSG_ALWAYS, ("Media "));
			#if API_DEBUG_CODE
			printf("Media ");
			#endif
		if( uData & LD_TUNER )
			//DEBUG_PRINT(MSG_ALWAYS, ("Tuner "));	
			#if API_DEBUG_CODE
			printf("Tuner ");
			#endif
		if( uData & LD_RECORD )
			//DEBUG_PRINT(MSG_ALWAYS, ("Record "));	
			#if API_DEBUG_CODE
			printf("Record ");
			#endif
		if( uData & LD_SPEAKER )
			//DEBUG_PRINT(MSG_ALWAYS, ("Speaker "));		
			#if API_DEBUG_CODE
			printf("Speaker ");
			#endif
		if( uData & LD_GUI )
			//DEBUG_PRINT(MSG_ALWAYS, ("Gui "));		
			#if API_DEBUG_CODE
			printf("Gui ");
			#endif
	}
#endif
	//DEBUG_PRINT(MSG_ALWAYS, ("\n"));	
	#if API_DEBUG_CODE
			printf("\n");
	#endif

	SI_CbusSetReadInfo(channel, ((SI_CbusGetReadInfo(channel)&DCAP_ITEM_INDEX_MASK) +1) &(~ DCAP_ITEM_READ_DOING));//finsh read 

	SI_CbusOQCleanActiveReq(channel);

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: READ_DEVCAP, device category info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscReadDevCat(uint8_si channel, uint8_si uData)
{
	PeerDevCap[2] = uData;

#if API_DEBUG_CODE
	switch (uData)
	{
		case SOURCE_DEV:
			//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Category: Source Device\n"));
			#if API_DEBUG_CODE
			printf("CBUS:: MHL Source Device Info: Category: Source Device\n");
			#endif
			break;

		case OTHER_DEV_CAT:
			//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Category: Other Device\n"));
			#if API_DEBUG_CODE
			printf("CBUS:: MHL Source Device Info: Category: Other Device\n");
			#endif
			break;

		default:
			//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Category: Incorrect\n"));
			#if API_DEBUG_CODE
			printf("CBUS:: MHL Source Device Info: Category: Incorrect\n");
			#endif
			break;			

	}
#endif

	SI_CbusSetReadInfo(channel, ((SI_CbusGetReadInfo(channel)&DCAP_ITEM_INDEX_MASK) +1) &(~ DCAP_ITEM_READ_DOING));//finsh read 

	SI_CbusOQCleanActiveReq(channel);
	return (true);
}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: READ_DEVCAP, MHL version info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscReadMhlVersion(uint8_si channel, uint8_si uData)
{
	uint8_si mhl_major, mhl_minor;

	PeerDevCap[1] = uData;

	mhl_major = (uData & 0xF0)>>4;
	mhl_minor = uData & 0x0F;

	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: MHL Version %d.%d\n", (int)mhl_major, (int)mhl_minor));
	#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: MHL Version %d.%d\n", (int)mhl_major, (int)mhl_minor);
	#endif

	SI_CbusSetReadInfo(channel, ((SI_CbusGetReadInfo(channel)&DCAP_ITEM_INDEX_MASK) +1) &(~ DCAP_ITEM_READ_DOING));//finsh read 

	SI_CbusOQCleanActiveReq(channel);

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus MSC command transfer done handler: MSC command: READ_DEVCAP, feature flag info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  @param[in]          uData			The return data of the command when transfer done
 *  
 *  @return             Result
 *  @retval             true, Success
 *  @retval             false, Failure
 * 
 *****************************************************************************/
bool_si SI_MscReadFeatureFlag(uint8_si channel, uint8_si uData)
{
//	uint8_si result;
//	cbus_out_queue_t req;
	bool_si rcp_support, rap_support;

	PeerDevCap[10] = uData;

	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Feature: RCP Support: %s\n", (uData & RCP_SUPPORT)?"Yes":"No"));
	#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: Feature: RCP Support: %s\n", (uData & RCP_SUPPORT)?"Yes":"No");
	#endif
    rcp_support = (uData & RCP_SUPPORT) ? true : false;
	SI_CbusSetRcpSupport(channel, rcp_support);
	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: MHL Source Device Info: Feature: RAP Support: %s\n", (uData & RAP_SUPPORT)?"Yes":"No"));
	#if API_DEBUG_CODE
		printf("CBUS:: MHL Source Device Info: Feature: RAP Support: %s\n", (uData & RAP_SUPPORT)?"Yes":"No");
	#endif
    rap_support = (uData & RAP_SUPPORT) ? true : false;
	SI_CbusSetRapSupport(channel, rap_support);

	SI_CbusSetReadInfo(channel, ((SI_CbusGetReadInfo(channel)&DCAP_ITEM_INDEX_MASK) +1) &(~ DCAP_ITEM_READ_DOING));//finsh read 
		
	SI_CbusOQCleanActiveReq(channel);

	return (true);

}



/*****************************************************************************/
/** 
 *  Cbus operation: start to get the peer's device cap registers' info
 *  
 * 				
 *  @param[in]          channel		Cbus channel, always 0 in SiI1292
 *  
 *  @return             void
 * 
 *****************************************************************************/
typedef struct tagDevcapRead
{
    uint8_si addressoffset;
    dataRetHandler_t dataRetHandler;
}DevcapReadItem_t;

DevcapReadItem_t  DevcapReadArray[]=
{
    {MHL_DEV_CAP_FEATURE_FLAG_REG_OFFSET,   SI_MscReadFeatureFlag},
    {MHL_DEV_CAP_MHL_VERSION_REG_OFFSET,    SI_MscReadMhlVersion},
    {MHL_DEV_CAP_DEV_CAT_REG_OFFSET,        SI_MscReadDevCat},
	{MHL_DEV_CAP_LOG_DEV_MAP_REG_OFFSET,    SI_MscReadLogDevMap},
	{MHL_DEV_CAP_VID_LINK_MODE_REG_OFFSET,  SI_MscReadVideoLinkMode},
	{MHL_DEV_CAP_AUD_LINK_MODE_REG_OFFSET,  SI_MscReadAudioLinkMode},
	{MHL_DEV_CAP_VIDEO_TYPE_REG_OFFSET,     SI_MscReadVideoType},
	{MHL_DEV_CAP_BANDWIDTH_REG_OFFSET,      SI_MscReadBandwidth},
};

#define DevcapReadItemCount (sizeof(DevcapReadArray)/sizeof(DevcapReadArray[0]))

void SI_MscStartGetDevInfo(uint8_si channel)
{
	uint8_si result;  
	cbus_out_queue_t req;
	uint8_si index, read_info;

    read_info = SI_CbusGetReadInfo(channel);
	index = read_info & DCAP_ITEM_INDEX_MASK;
	read_info &= (~DCAP_ITEM_INDEX_MASK);

	if(read_info & DCAP_READ_DONE )
	{
        //DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: DCAP_READ_DONE \n"));
        #if API_DEBUG_CODE
		printf("CBUS:: DCAP_READ_DONE \n");
	#endif
		return ;
	}

	if(read_info & DCAP_ITEM_READ_DOING )
	{
        //DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: current DCAP READ ITEM not done yet\n"));
          #if API_DEBUG_CODE
		printf("CBUS:: current DCAP READ ITEM not done yet\n");
	   #endif
        return;
	}

	if(index >=DevcapReadItemCount)
	{
       // DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: index error \n"));
         #if API_DEBUG_CODE
		printf("CBUS:: index error \n");
	   #endif
        return;
	}

   // DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: Read MHL Source Device infomation\n"));	
   // DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: current_item_index = %d\n",(int)index));	
   #if API_DEBUG_CODE
		printf("CBUS:: Read MHL Source Device infomation\n");
   #endif
   #if API_DEBUG_CODE
		printf("CBUS:: current_item_index = %d\n",(int)index);
   #endif   

//    DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: DevcapReadItemCount = %d\n",(int)DevcapReadItemCount));
    	
	req.command     = MSC_READ_DEVCAP;
	req.offsetData  = DevcapReadArray[index].addressoffset;
	req.dataRetHandler = DevcapReadArray[index].dataRetHandler;
	req.retry = 2;	// retry 2 times if timeout or abort for important MSC commands
	result = SI_CbusPushReqInOQ( channel, &req, true );		// make sure the first Read_Dev_Cap can be put in the queue

	if ( result != SUCCESS )
	{
		//DEBUG_PRINT(MSG_DBG, ("Cbus:: SI_MscStartGetDevInfo, Error found in SI_CbusPushReqInOQ: %02X\n", (int)result));
		 #if API_DEBUG_CODE
		printf("Cbus:: SI_MscStartGetDevInfo, Error found in SI_CbusPushReqInOQ: %02X\n", (int)result);
   		#endif   
	}
    else
    {
        SI_CbusSetReadInfo(channel,index | DCAP_ITEM_READ_DOING );
    }
}

/*****************************************************************************/
/** 
 *  Cbus operation: Initialize the parameters of MSC related variables
 *  
 *  @return             void
 * 
 *****************************************************************************/
void SI_MscInitialize()
{
	uint8_si		channel;
	
    /* Initialize MSC variables of all channels.    */
    for ( channel = 0; channel < MHL_MAX_CHANNELS; channel++ )
    {
		SI_CbusInitParam(channel);
    }
}

bool_si  SI_WriteBurstDataDone(uint8_si channel,uint8_si uData)
{
	uData = uData;
	//DEBUG_PRINT(MSG_ALWAYS, ("CBUS:: WriteBurstDataDone\n"));
		 #if API_DEBUG_CODE
		printf("CBUS:: WriteBurstDataDone\n");
   		#endif   

	SI_CbusOQCleanActiveReq(channel);
	return true;
}
