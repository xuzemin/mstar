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
//!file     si_apiEdid.c
//!brief    CP 1292 Starter Kit reading Edid functions.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009-2010, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/


#include "./SiI1292/EDID/si_apiEdid.h"

#define VMASK 0xe0

//------------------------------------------------------------------------------
// Function:    	wait
// Description: 	a short delay
// Parameters:		
// Return:	 	
//------------------------------------------------------------------------------
static void wait(void)
{
	uint32_si i;
    i = 0;
	while(i < 1000)
	{
		i++;
	}
}



//------------------------------------------------------------------------------
// Function:    	EdidGetPA
// Description: 	Get PA from total offset
// Parameters:		Len_value: total offset of Video Data Block
// Return:	 	PA value
//				0x0: error
//------------------------------------------------------------------------------
static uint16_si EdidGetPA( uint8_si Len_value )
{
	uint16_si PA_value = 0x0;
	uint8_si PA_Hbyte = 0x0;
	uint8_si PA_Lbyte = 0x0;

	PA_Hbyte = SiIRegioRead( REG_DDC_L1 + Len_value );
	// if the return value is 0, try read it again
	if(!PA_Hbyte)
	{
		wait();
		PA_Hbyte = SiIRegioRead( REG_DDC_L1 + Len_value );
	}
	
	PA_Lbyte = SiIRegioRead( REG_DDC_L1 + Len_value + 1 );
	// if the return value is 0, try read it again
	if(!PA_Lbyte)
	{
		wait();
		PA_Lbyte = SiIRegioRead( REG_DDC_L1 + Len_value + 1 );
	}

	PA_value = (PA_value | PA_Hbyte) << 8;
	PA_value |= PA_Lbyte;
	
	return PA_value;
}



//------------------------------------------------------------------------------
// Function:    	EdidGetLen
// Description: 	Get Ln number for calculating physical address byte offset
// Parameters:		Len : PA offset calculate
// Return:	 	Ln value
//				0x0: error
//				0xff: not wanted value
//------------------------------------------------------------------------------
static uint8_si EdidGetLen( uint8_si *Len )
{
	uint8_si value;
	uint8_si Ven_value = 0;
	uint8_si Len_value = 0;
	
	value = SiIRegioRead( REG_DDC_L1 + *Len );
	if(value == 0)
	{
		wait();
		value = SiIRegioRead( REG_DDC_L1 + *Len);
	// if the return value is 0, try read it again
	}
	if (value == 0)
	{
		return 0;
	}
	Len_value = value & LMASK;
	Ven_value = ((value & VMASK) >> 5);

	if (Ven_value == 3)
	{
		return Len_value;
	}

	*Len += (Len_value + 1);

	// not the video data block
	return 0xff;
}



//------------------------------------------------------------------------------
// Function:    	CheckPAOffsetValid 
// Description: 	Check the validation of physical address byte offset
// Parameters:		len : PA offset calculate
// Return:	 	result
//				0x0: invalid
//				0x1: valid
//------------------------------------------------------------------------------
static uint8_si CheckPAOffsetValid (uint8_si len)
{
	uint8_si value1, value2, value3;
	
	value1 = SiIRegioRead( REG_DDC_L1 + len + 1);
	value2 = SiIRegioRead( REG_DDC_L1 + len + 2);
	value3 = SiIRegioRead( REG_DDC_L1 + len + 3);
	if(value1 != 0x03)
		return false;
	if(value2 != 0x0C)
		return false;
	if(value3 != 0x00)
		return false;
	return true;
}



//------------------------------------------------------------------------------
// Function:    	CheckPAValid 
// Description: 	Check the validation of phsical address byte 
// Parameters:		physical_address : physical address byte
// Return:	 	result
//				0x0: invalid
//				0x1: valid
//------------------------------------------------------------------------------
static uint8_si CheckPAValid (uint16_si physical_address)
{
	uint16_si p1,p2,p3,p4;
	p1 = ( physical_address  & 0xF000);
	p2 = ( physical_address  & 0x0F00);
	p3 = ( physical_address  & 0x00F0);
	p4 = ( physical_address  & 0x000F);

	if (p1 == 0)
	{
		return false;
	}
	if (p2 == 0)
	{
		if (p3 | p4)
			return false;
		else
			return true;
	}
	if (p3 == 0)
	{
		if (p4)
			return false;
		else
			return true;
	}
	return true;
}



//------------------------------------------------------------------------------
// Function:    	SI_EdidGetPA
// Description: 	Get physical address from downstream EDID
// Parameters:	void
// Return:	 	PA value
//				0x0: error
//------------------------------------------------------------------------------
uint16_si SI_EdidGetPA( void )
{
	uint16_si physical_address = 0x0000;
	uint8_si Len = 0;
	uint8_si status;
	bool_si ret;
	uint8_si i;
	
	for (i=0; i<10; i++)	// increase the loop count to 10 since some TV may have more blocks than 4 before VSDB
	{
		status = EdidGetLen(&Len);
		if (status == 0)
		{
			//DEBUG_PRINT(MSG_ALWAYS, ("Edid:: Error found in Reading L%d value\n", (int)i));
			#if API_DEBUG_CODE
			printf("Edid:: Error found in Reading L%d value\n", (int)i);
			#endif
			return physical_address;
		}
		else if (status == 0xff)
		{
			continue;
		}
		else
		{
			ret = CheckPAOffsetValid(Len);
			if(ret == true)
			{
				physical_address = EdidGetPA(Len + 4);
				ret = CheckPAValid(physical_address);
				if (ret == true)
				{
					return physical_address;
				}
				else
				{
					//DEBUG_PRINT(MSG_ALWAYS, ("Edid:: Error found invalid PA value : %04X\n", (int)physical_address));
					#if API_DEBUG_CODE
					printf("Edid:: Error found invalid PA value : %04X\n", (int)physical_address);
					#endif
					physical_address = 0x0000;
					return physical_address;
				}
			}
			else
			{
				//DEBUG_PRINT(MSG_ALWAYS, ("Edid:: Error found invalid PA offset\n"));
				#if API_DEBUG_CODE
				printf("Edid:: Error found invalid PA offset\n");
				#endif
				return physical_address;
			}
		}
	}
	//DEBUG_PRINT(MSG_ALWAYS, ("Edid:: Error found no PA value\n"));
	#if API_DEBUG_CODE
	printf("Edid:: Error found no PA value\n");
	#endif
	return physical_address;
}



