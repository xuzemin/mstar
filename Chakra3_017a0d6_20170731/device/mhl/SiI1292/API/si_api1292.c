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
//**************************************************************************
//!file     si_api1292.c
//!brief    SiI1292 API main functions.
//
// Note:    This file supports 1292
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009 -2010, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include "./SiI1292/API/si_api1292.h"
#include "./SiI1292/MAIN/si_cp1292.h"
#include "./SiI1292/API/si_regio.h" 
#include "./SiI1292/CEC/si_apiCEC.h"
#include "./SiI1292/CBUS/si_cbus_regs.h"
#include "./SiI1292/CBUS/si_apiCbus.h"
#if (API_DEBUG_CODE==1)
#  include <stdio.h>
#endif

#ifdef MSC_TESTER
extern void 	start_msc_tester(void);
#endif
//------------------------------------------------------------------------------
// Target System specific
//------------------------------------------------------------------------------

#if (FPGA_DEBUG_CODE == 1)
    char strDeviceID []             = "1292(FPGA)";
#else
    char strDeviceID []             = "1292";
#endif

//------------------------------------------------------------------------------
// Debug Trace
//------------------------------------------------------------------------------

#if (API_DEBUG_CODE==1)
    char        g_debugTraceVerStr[5]   = "0003";   // Changed each time the debug labels are
                                                    // changed to keep track of what values
                                                    // a specific version is monitoring.
    uint8_si     g_demFlags1           = 0;
    uint8_si     g_demFlags2           = DF2_MUTE_ON;
#endif

//------------------------------------------------------------------------------
// Device Event Monitor variables
//------------------------------------------------------------------------------

bool_si		    g_firstPass     = true;
uint32_si		g_pass			= 0;	// For time counting

static uint8_si  HDMI_connect_wait_count     = 0;	// For starter kiter

#ifdef SWWA
static uint8_si Tx_TMDS_toggle = 0;
#endif // SWWA

extern bool_si mhl_con;

//------------------------------------------------------------------------------
// Function:    SI_DeviceStatus
// Description: Return the requested status from the device.
//------------------------------------------------------------------------------

uint8_si SI_DeviceStatus ( uint8_si statusIndex )
{
    uint8_si regValue = 0;

    switch ( statusIndex )
    {

        case SI_DEV_IDH:
            regValue = SiIRegioRead( REG_DEV_IDH_RX );
            break;
        case SI_DEV_IDL:
            regValue = SiIRegioRead( REG_DEV_IDL_RX );
            break;
        case SI_DEV_REV:
            regValue = SiIRegioRead( REG_DEV_REV ) & 0x0F;
            break;

        default:
            regValue = 0;   
            break;

    }

    return( regValue );
}



//------------------------------------------------------------------------------
// Function:    GatherDeviceEvents
// Description: 
//
//------------------------------------------------------------------------------

static uint8_si GatherDeviceEvents ( void )
{
	uint8_si			events = 0;
    uint8_si         uData;

    uData = SiIRegioRead( REG_INTR1 );
	printf("[GatherDeviceEvents uData=0x%x]\n",uData);
	if (uData & INT_CBUS_CON)
	{
		events |= MHL_EVENT;
		SiIRegioModify(REG_INTR1, INT_CBUS_CON, INT_CBUS_CON);
	}	
	else 
	{
		printf("[GatherDeviceEvents2 uData=0x%x]\n",uData);
		if (uData & INT_RPWR)
		{
			printf("[GatherDeviceEvents3 uData=0x%x]\n",uData);
			//events |= HDMI_EVENT;
			if (!mhl_con)
				events |= HDMI_EVENT;
			//HDMI_connect_wait_count = 1;
			
			SiIRegioModify(REG_INTR1, INT_RPWR, INT_RPWR);
		}
	}

	if (uData & INT_HPD)
	{
		events |= TV_EVENT;
		SiIRegioModify(REG_INTR1, INT_HPD, INT_HPD);
	}		

	if (uData & INT_RSEN)
	{
		events |= RSEN_EVENT;
		SiIRegioModify(REG_INTR1, INT_RSEN, INT_RSEN);
	}

#ifdef SWWA
	if (uData & INT_SCDT)
	{
		events |= SCDT_EVENT;
		SiIRegioModify(REG_INTR1, INT_SCDT, INT_SCDT);
	}
#else // SWWA
		if (uData & INT_SCDT)
		{
		//	events |= SCDT_EVENT;

			//Keno20120315, fix MHL CTS4.3.24.1.
			if(mhl_con)
				SiIRegioModify(0x07A, 0x40, 0x40);
			else
				SiIRegioWrite(0x07A, 0xD0);

#ifdef BOARD_JULIPORT	   //for auto reset on SCDT
//		SiIRegioWrite(0x005, 0x28); // Hold CEC in Reset

	if(mhl_con)
		SiIRegioModify(0x07A, 0x40, 0x40);
	else
		SiIRegioWrite(0x07A, 0xD0);

		SiIRegioWrite(0x00C, 0x11); // DATA_MUX_1
		SiIRegioWrite(0x00D, 0x0B); // DATA_MUX_2

#endif

			SiIRegioModify(REG_INTR1, INT_SCDT, INT_SCDT);
		}
#endif
		if (uData & INT_CKDT)
		{
		//	events |= SCDT_EVENT;
			SiIRegioModify(REG_INTR1, INT_CKDT, INT_CKDT);
		}
	return events;

}


static void ProcessMhlEvent (void)
{
	uint8_si uData;

	uData = SiIRegioRead(REG_CBUS_BUS_STATUS);
	//DEBUG_PRINT(MSG_ALWAYS, ("REG_CBUS_BUS_STATUS = %02X\n", (int)uData));
	#if API_DEBUG_CODE
	printf("REG_CBUS_BUS_STATUS = %02X\n", (int)uData);
	#endif
	if (uData & BIT_BUS_CONNECTED)
	{
		//Set g_currentInputMode to MHL, then let CBUS driver handle everything
		g_currentInputMode = MHL;

		//Enable MHL interrupts
		SiIRegioWrite(REG_INTR1_MASK, 0xFF);
		SiIRegioWrite(REG_CBUS_INTR_ENABLE, 0xFF);
		
		g_MHL_Source_Connected = true;
		//DEBUG_PRINT(MSG_ALWAYS, ("MHL Source device Connected\n"));
		#if API_DEBUG_CODE
		printf("MHL Source device Connected\n");
		#endif
		if(HDMI_connect_wait_count)
			HDMI_connect_wait_count = 0;	// So it's a MHL device, clean the HDMI event
		//init CPI core
#if IS_CEC
		SI_CpiInit();
#endif

		GPIO_CLR(LED2_MHL);

		// Jin: For Bring-up
#if (FPGA_BUILD == 0)
		SiIRegioModify(0x073, 0x02, 0x02); // change mode to MHL
		SiIRegioModify(0x071, 0x02, 0x02);
		SiIRegioWrite(0x06C, 0x08);
		//SiIRegioWrite(0x009, 0x0);
#endif // FPGA_BUILD == 0

#ifdef MSC_TESTER
		start_msc_tester();
#endif // MSC_TESTER
	}
	else
	{
		g_MHL_Source_Connected = false;
		//DEBUG_PRINT(MSG_ALWAYS, ("MHL Source device Unconnected\n"));
		#if API_DEBUG_CODE
		printf("MHL Source device Unconnected\n");
		#endif
		GPIO_SET(LED2_MHL);
		g_currentInputMode = 0xff;
	}
	
}



static void ProcessHdmiEvent (void)
{
	uint8_si uData;
	static bool_si print_connected = false;

	uData = SiIRegioRead(REG_STATE);

	if (uData & BIT_PWR5V)
	{
		g_HDMI_Source_Connected = true;
		print_connected = true;
		//DEBUG_PRINT(MSG_ALWAYS, ("HDMI Source device Connected\n"));
		#if API_DEBUG_CODE
		printf("HDMI Source device Connected\n");
		#endif
	}
	else
	{
		g_HDMI_Source_Connected = false;
		g_HDMI_Source_Valid = false;
		//g_currentInputMode = MHL;
              g_currentInputMode = 0xff;
		if(print_connected)
		{
			//DEBUG_PRINT(MSG_ALWAYS, ("HDMI Source device Unconnected\n"));
			#if API_DEBUG_CODE
			printf("HDMI Source device Unconnected\n");
			#endif
			print_connected = false;
		}
		// Disable HDMI Mode
		//SiIRegioModify(REG_SYS_CTRL1, BIT_HDMI_MODE|BIT_RX_CLK, 0);
		//Jin: bringup in stater kit
		SiIRegioWrite(REG_SYS_CTRL1, 0);
		// Disable Rx Termination Core
		SiIRegioModify(REG_RX_CTRL5, BIT_HDMI_RX_EN, 0);

		GPIO_SET(LED3_HDMI);
	}
}



static void ProcessTvEvent (void)
{
	uint8_si uData;

	uData = SiIRegioRead(REG_STATE);
	//DEBUG_PRINT(MSG_ALWAYS, ("REG_STATE = %02X\n", (int)uData));
	#if API_DEBUG_CODE
	printf("REG_STATE = %02X\n", (int)uData);
	#endif	
	SI_CbusInitDevCap(SI_CbusPortToChannel(g_data.portSelect));

	if (uData & BIT_HPD)
	{
#if !IS_CEC
		if(g_HPD_IN)
			return;
#endif
		
		g_HPD_IN = true; // true means high
		
		//DEBUG_PRINT(MSG_ALWAYS, ("HPD Detected\n"));
		#if API_DEBUG_CODE
		printf("HPD Detected\n");
#if IS_CEC
		//RG add code to read EDID from DS display

		//set I2C switch to DDC mode
		SiIRegioModify(REG_DDC_SW_CTRL, BIT_I2C_DDC_SW_EN, BIT_I2C_DDC_SW_EN);
		//read EDID information
		HalI2cWriteByte(0x60,0x00, 0x00);	//set segment pointer
		HalI2cWriteByte(0xA0,0x00, 0x00);	//set start address
		//Update PA
		g_cecPhysical = SI_EdidGetPA();
		if(!g_cecPhysical)
		{	
			// change back to default value
			g_cecPhysical = 0x1000;
			//DEBUG_PRINT(MSG_ALWAYS, ("Error in reading CEC physical address, change it to default value...\n"));
		}
		//DEBUG_PRINT(MSG_ALWAYS, ("CEC physical address: %04X\n", (int)g_cecPhysical));
		//Switch back

		//perform dummy read of 0xd0:0x84 as first read returns 0xff after SW is set to DDC position
		HalI2cReadByte(0xD0,0x84);
		//set I2C switch to DDC mode
		SiIRegioModify(REG_DDC_SW_CTRL, BIT_I2C_DDC_SW_EN, 0);

//		InitCECOnHPD();
#endif
		#endif	
	}
	else
	{
		if(!g_HPD_IN)
			return;

		g_HPD_IN = false; // false means low

		//DEBUG_PRINT(MSG_ALWAYS, ("HPD Undetected\n"));
		#if API_DEBUG_CODE
		printf("HPD Undetected\n");
		#endif	
	}
    SiIRegioWrite(REG_CBUS_INTR_STATUS, BIT_MSC_MSG_RCV);//tiger , 12-07-2-11, bit3 hardware defualt value is 1,clear it when init;

#if (FPGA_BUILD == 0)			
	#if API_DEBUG_CODE
	printf("g_currentInputMode=%d\n",g_currentInputMode);
	#endif	
	if (g_currentInputMode == HDMI)
	{
		#if API_DEBUG_CODE
		printf(" change mode to HDM\n");
		#endif	
		SiIRegioModify(0x073, 0x02, 0); // change mode to HDMI
		SiIRegioWrite(0x071, 0xA0);
		SiIRegioWrite(0x06C, 0x3F);
		SiIRegioWrite(0x070, 0xA8);
		SiIRegioWrite(0x009, 0x3E);			
#ifdef BOARD_JULIPORT
//		SiIRegioWrite(0x005, 0x28); // Hold CEC in Reset
		SiIRegioWrite(0x07A, 0xD0);	//disable power out in HDMI input mode
		SiIRegioWrite(0x00C, 0x11); // DATA_MUX_1
		SiIRegioWrite(0x00D, 0x0B); // DATA_MUX_2
#endif
#ifdef BOARD_CP1292
		SiIRegioWrite(0x07A, 0xD0);			
		SiIRegioWrite(0x00C, 0x45); // DATA_MUX_1
		SiIRegioWrite(0x00D, 0x0E); // DATA_MUX_2			  
#endif	
	}
	else
	{
		#if API_DEBUG_CODE
		printf(" change mode to MHL\n");
		#endif	
		SiIRegioModify(0x073, 0x02, 0x02); // change mode to MHL
		SiIRegioWrite(0x071, 0xA2);
		SiIRegioWrite(0x06C, 0x08);
		SiIRegioWrite(0x070, 0x48);
		SiIRegioWrite(0x009, 0x0);			
		
		//Keno20120315, fix MHL CTS4.3.24.1.
		if(mhl_con)
			SiIRegioWrite(0x07A, 0x40);
		else
			SiIRegioWrite(0x07A, 0xD0);

#ifdef BOARD_JULIPORT
//		SiIRegioWrite(0x005, 0x28); // Hold CEC in Reset
	if(mhl_con)
		SiIRegioWrite(0x07A, 0x40);
	else
		SiIRegioWrite(0x07A, 0xD0);

		SiIRegioWrite(0x00C, 0x11); // DATA_MUX_1
		SiIRegioWrite(0x00D, 0x0B); // DATA_MUX_2
#endif
#ifdef BOARD_CP1292
		if(mhl_con)
			SiIRegioWrite(0x07A, 0x40);
		else
			SiIRegioWrite(0x07A, 0xD0);
		
		SiIRegioWrite(0x00C, 0x45); // DATA_MUX_1
		SiIRegioWrite(0x00D, 0x0E); // DATA_MUX_2			  
#endif
	}
#endif // FPGA_BUILD == 0

}



static void ProcessRsenEvent (void)
{
	uint8_si uData;

	uData = SiIRegioRead(REG_STATE2);
		
	if(uData)
	{
		g_TX_RSEN = true;
	}
	else
	{
		g_TX_RSEN = false;
		g_TX_RSEN_Valid = false;
	}

}



#ifdef SWWA
static void ProcessScdtEvent (void)
{
	uint8_si uData;
		
	uData = SiIRegioRead(REG_STATE);

	if(uData & BIT_SCDT)
	{
		if(Tx_TMDS_toggle == 0)
		{
			//DEBUG_PRINT(MSG_ALWAYS, ("DEBUG_INFO: 0x51[7] Low\n"));
			// Turn off/on Tx TMDS Core For HDCP on-off issue, Bug #19931
			SiIRegioModify(REG_TX_SWING1, BIT_SWCTRL_EN, 0);

			Tx_TMDS_toggle = 2;
			//SiIRegioModify(REG_TX_SWING1, BIT_SWCTRL_EN, BIT_SWCTRL_EN);
			//DEBUG_PRINT(MSG_ALWAYS, ("DEBUG_INFO: 0x51[7] High\n"));			
		}
	}

}
#endif // SWWA


static void ProcessDeviceEvents ( uint8_si events )
{

	if (events & MHL_EVENT)	
		ProcessMhlEvent();
	
	if (events & HDMI_EVENT)
		ProcessHdmiEvent();

	if (events & TV_EVENT)
		ProcessTvEvent();

	if (events & RSEN_EVENT)
		ProcessRsenEvent();

#ifdef SWWA
	if (events & SCDT_EVENT)
		ProcessScdtEvent();
#endif // SWWA
		
}


static void TxRsenValidCheck (void)
{
	static bool_si timer_set = false;
	static uint32_si count = 0;

	if (g_TX_RSEN)
	{
		if (!timer_set)
		{
			timer_set = true;
			count = timer_count;
		}
		else
		{
			if( HalTimerDelay(count, DEM_RSEN_VALID_TIME) )
			{
				g_TX_RSEN_Valid = true;
				count = 0;
				timer_set= false;
				//DEBUG_PRINT(MSG_ALWAYS, ("TX RSEN Stable\n"));
				//DEBUG_PRINT(MSG_ALWAYS, ("g_currentInputMode = %d\n",(int)g_currentInputMode));
				#if API_DEBUG_CODE
				printf("TX RSEN Stable\n");
				#endif	
				#if API_DEBUG_CODE
				printf("g_currentInputMode = %d\n",(int)g_currentInputMode);
				#endif	
				if (g_currentInputMode == HDMI)
					// enable Rx Core termination
					SiIRegioModify(REG_RX_CTRL5, BIT_HDMI_RX_EN, BIT_HDMI_RX_EN);	
			}
		}
	}
    else
    {
        timer_set = false;
        count = 0;
    }

}

static void ClearCbusInterrupts(void)
{

    SiIRegioWrite( REG_CBUS_INTR_STATUS, 0xFF );
	SiIRegioWrite( REG_CBUS_LINK_STATUS_2, 0 );
    SiIRegioWrite( REG_CBUS_REQUESTER_ABORT_REASON, 0xFF );
    SiIRegioWrite( REG_CBUS_RESPONDER_ABORT_REASON, 0xFF );
    SiIRegioWrite( REG_CBUS_DDC_ABORT_REASON, 0xFF );
    SiIRegioWrite( REG_CBUS_CEC_ABORT_REASON, 0xFF );
	
}


static void HdmiSourceValidCheck (void)
{
	static bool_si timer_set = false;
	static uint32_si count = 0;

	if (g_HDMI_Source_Connected)
	{

		if (!timer_set)
		{
			timer_set = true;
			timer_count = 0;
			count = timer_count;
		}
        else
        {
	     if( HalTimerDelay(count, DEM_HDMI_VALID_TIME) )
            {
                uint8_si uData;
            
                g_HDMI_Source_Valid = true;
                g_currentInputMode = HDMI;
				#if API_DEBUG_CODE
				printf(" change mode to HDM\n");
				#endif	
            
                // Jin: Fro Bring-up
            #if (FPGA_BUILD == 0)			
                SiIRegioModify(0x073, 0x02, 0); // change mode to HDMI
                SiIRegioWrite(0x071, 0xA0);
                SiIRegioWrite(0x06C, 0x3F);
                SiIRegioWrite(0x070, 0xA8);
                SiIRegioWrite(0x009, 0x3E);			
            #endif // FPGA_BUILD == 0
            
                // Disable CBUS interrupt
                SiIRegioWrite(REG_INTR1_MASK, 0xFE);
                SiIRegioWrite(REG_CBUS_INTR_ENABLE, 0);
            
                // Clear CBUS interrupts
                uData = SiIRegioRead(REG_CBUS_INTR_STATUS);
                if(uData)
                    ClearCbusInterrupts();			
            
                SiIRegioWrite(REG_INTR1, INT_CBUS);
                
                count = 0;
               // DEBUG_PRINT(MSG_ALWAYS, ("HDMI Source device Stable\n"));
		#if API_DEBUG_CODE
		printf("HDMI Source device Stable\n");
		#endif
            
                GPIO_CLR(LED3_HDMI);
                // Confirm HDMI MODE
                //SiIRegioModify(REG_SYS_CTRL1, BIT_HDMI_MODE|BIT_RX_CLK, BIT_HDMI_MODE|BIT_RX_CLK);
                //Jin: bringup in starter kit
                SiIRegioWrite(REG_SYS_CTRL1, 0xF8);
            
                // Enable HDMI Rx Core Termination
                if (g_TX_RSEN_Valid)
                    SiIRegioModify(REG_RX_CTRL5, BIT_HDMI_RX_EN, BIT_HDMI_RX_EN);
            
            }
        }
	}
	else
    {
        timer_set = false;
		count = 0;	// re-count
    }

}



//------------------------------------------------------------------------------
// Function:    SI_DeviceEventMonitor
// Description: Monitors important events in the life of the Main pipe and
//              intervenes where necessary to keep it running clean.
//
// NOTE:        This function is designed to be called at 100 millisecond
//              intervals. If the calling interval is changed, the
//              DEM_POLLING_DELAY value must be changed also to maintain the
//              proper intervals.
//
//------------------------------------------------------------------------------

void SI_DeviceEventMonitor ( void )
{
	uint8_si events = 0;

	//DEBUG_PRINT(MSG_DBG, ("[%d] ", (int)g_pass));
	g_pass++;
	if((int)g_pass < 0)//if overflow
	{
		g_pass = 0;
	}
		
	if (g_firstPass)
	{		
		bool_si mhl_cable_con = false;
			
		g_firstPass = false;

		//SiIRegioModify(REG_RX_MISC, BIT_PSCTRL_OEN|BIT_PSCTRL_OUT|BIT_PSCTRL_AUTO, BIT_PSCTRL_OUT);

		//enable all INT mask
		SiIRegioWrite(REG_INTR1_MASK, 0xFF);

#if 0//def BOARD_JULIPORT//Keno20120301, disable RK design, because it will effect that cannot display
		//enable mhl cable connect based on  V5DET 0x4E[0] mask at 0x4E[1], if high them MHL cable det.
		SiIRegioWrite(REG_INTR2_STATUS_MASK,0x02);
#endif

		//disable auto HPD/RSEN generation module
		SiIRegioModify(REG_RX_MISC, BIT_PSCTRL_OEN|BIT_PSCTRL_OUT|BIT_PSCTRL_AUTO|BIT_HPD_RSEN_ENABLE|BIT_5VDET_OVR, BIT_PSCTRL_OEN|BIT_PSCTRL_OUT|BIT_5VDET_OVR);

		mhl_cable_con = CpCableDetect();

		// Jin: for INT_RPWR/INT_CBUS doesn't show at first process
		{
			uint8_si	 uData = SiIRegioRead(REG_STATE);

			if (uData & BIT_PWR5V)
			{			
				//HDMI_connect_wait_count = 1;
				if(!mhl_con)
					events |= HDMI_EVENT;
			}

			if(mhl_cable_con)
			{
				if (uData & BIT_HPD)
				{
					g_HPD_IN = true; // true means high
			
					//DEBUG_PRINT(MSG_ALWAYS, ("HPD Detected\n"));	
					#if API_DEBUG_CODE
					printf("HPD Detected\n");
					#endif
				}
			}
			
			uData = SiIRegioRead(REG_CBUS_BUS_STATUS);

			if (uData & BIT_BUS_CONNECTED)
				events |= MHL_EVENT;
		}

	}

#if 0//def BOARD_JULIPORT//Keno20120301, disable RK design, because it will effect that cannot display
		if(SiIRegioRead(REG_INTR2_STATUS_MASK) & 0x01)
		{
			CpCableDetect();
			SiIRegioModify(REG_INTR2_STATUS_MASK, 0x01, 0x01);
		}
#endif
#if 1//def BOARD_CP1292//Keno20120301, enable RK design, because it will effect that cannot display
		CpCableDetect();
#endif
	
   	events |= GatherDeviceEvents();       // Gather info for this pass
	//DEBUG_PRINT(MSG_ALWAYS, ("events = %02X\n", (int)events));
	#if API_DEBUG_CODE
	printf("events = %02X,g_HDMI_Source_Connected=%d\n", (int)events,g_HDMI_Source_Connected);
	#endif
	
	/*if (HDMI_connect_wait_count)
	{
		if (HDMI_connect_wait_count == 5)	// wait at least 200ms for CBUS discovery
		{
			events |= HDMI_EVENT;
			HDMI_connect_wait_count = 0;
		}
		else
		{
			HDMI_connect_wait_count++;
		}
	}*/

	ProcessDeviceEvents(events);

#ifdef SWWA
	if (Tx_TMDS_toggle)
	{
		Tx_TMDS_toggle --;
		
		if (Tx_TMDS_toggle == 0)
		{
			//DEBUG_PRINT(MSG_ALWAYS, ("DEBUG_INFO: 0x51[7] High\n"));
			SiIRegioModify(REG_TX_SWING1, BIT_SWCTRL_EN, BIT_SWCTRL_EN);
		}
	}
#endif // SWWA

	// make sure TX_RSEN show 1s 
	if (g_TX_RSEN_Valid == false)
		TxRsenValidCheck();

	if (g_HDMI_Source_Valid == false)
		HdmiSourceValidCheck();
	
}
