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
//!file     si_cp9387_ext.c
//!brief    CP 9387 Start Kit extension functions.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2008-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/
#include "./SiI1292/MAIN/si_cp1292.h"
#include "./SiI1292/API/si_regio.h"

//-------------------------------------------------------------------------------
//  Global data
//-------------------------------------------------------------------------------

bool_si g_deviceInterrupt = false;
bool_si mhl_con = false;

extern uint16_si g_pulseWidthCounter;
extern bool_si   g_startWidthCounter;

//------------------------------------------------------------------------------
// Function:    DeviceIntHandler
// Description: Silicon Image device interrupt handler.  This function only
//              sets the global interrupt flag, since accessing the I2C port
//              in an ISR is not a good thing.
//------------------------------------------------------------------------------

//static void DeviceIntHandler ( void ) interrupt 0
/*
static void DeviceIntHandler ( void )
{

    g_deviceInterrupt = true;
}
*/

//------------------------------------------------------------------------------
// Function:    CpCheckExternalRequests
// Description: Returns true if HDMIGear or Simon wants control
//------------------------------------------------------------------------------

bool_si CpCheckExternalRequests ( void )
{
    static uint8_si counter = 0;
    //static uint8_si simonLeds = 0x06;

    if ( HAL_RemoteRequestHandler() )
    {
        if ( counter > 50 )     // Blink every second that Simon is in operation
        {
            counter = 0;
            //CpSetPortLEDs( simonLeds );
        }
        return( true );
    }

    return( false );
}


//------------------------------------------------------------------------------
// Function:    CpBlinkTilReset
// Description: Blink 'til reset
//------------------------------------------------------------------------------

void CpBlinkTilReset ( uint8_si leds )
{
    while ( 1 )
    {
        //CpSetPortLEDs( leds );
        leds ^= 0x0F;
        HalTimerWait( 200 );
    }
}


//------------------------------------------------------------------------------
// Function:    CpReadInitialSettings
// Description: Read all option settings from EEPROM and the jumpers,
//              including start-up only options.
//
//              If EEPROM configuration is not valid, initialize it here.
//------------------------------------------------------------------------------

void CpReadInitialSettings ( void )
{
#if (FPGA_BUILD == 1)
    g_data.irEnabled    = false;
#else
	if(IS_IR == 1)g_data.irEnabled = true;else g_data.irEnabled = false;
#endif	// FPGA_BUILD

#if IS_CEC
    g_data.cecEnabled   = true;
#else
    g_data.cecEnabled   = false;
#endif

    g_halMsgLevel       = MSG_PRINT_ALL;

    GPIO_SET( SI_STANDBY_MODE );             // Configure for input
   // g_data.standby_mode = !GPIO_BIT( STANDBY_MODE );
   g_data.standby_mode = 0;

    //DEBUG_PRINT(MSG_ALWAYS,( "\nStandby Mode:        %s\n", g_data.standby_mode ? "ON" : "OFF" ));
     #if API_DEBUG_CODE
		printf("\nStandby Mode:        %s\n", g_data.standby_mode ? "ON" : "OFF");
     #endif	

	if (g_data.standby_mode)
	{
    	GPIO_SET( LED7_AMBER );
		GPIO_CLR( LED7_GREEN );
		SiIRegioModify(REG_GPIO_CTRL, BIT_GPIO0_OUTPUT_DISABLE, BIT_GPIO0_OUTPUT_DISABLE);
		SiIRegioModify(REG_TX_SWING1, BIT_SWCTRL_EN, 0);
	}
	else
	{
    	GPIO_SET( LED7_GREEN );
		GPIO_CLR( LED7_AMBER );
	}

  //  DEBUG_PRINT(MSG_ALWAYS,( "\nCEC Enabled:        %s\n", g_data.cecEnabled ? "YES" : "NO" ));
  //  DEBUG_PRINT(MSG_ALWAYS,( "IR Enabled:         %s\n", g_data.irEnabled ? "YES" : "NO" ));

  //  DEBUG_PRINT(MSG_ALWAYS,( "\n" ));
     #if API_DEBUG_CODE
		printf("\nCEC Enabled:        %s\n", g_data.cecEnabled ? "YES" : "NO" );
     #endif
     #if API_DEBUG_CODE
		printf("IR Enabled:         %s\n", g_data.irEnabled ? "YES" : "NO");
     #endif
     #if API_DEBUG_CODE
		printf("\n");
     #endif
	 
}



#if (FPGA_BUILD == 0)
#define LATEST_OTP_REV		4
//------------------------------------------------------------------------------
// Function:    CpCheckOTPRev
// Description: Read OTP Revision and update registes
//			Only in Chip mode, not for FPGA
//------------------------------------------------------------------------------
void CpCheckOTPRev( void )
{
	uint8_si		OTP_rev;

	OTP_rev = SiIRegioRead(REG_OTP_REV);
	OTP_rev &= MASK_OTP_REV;

	//DEBUG_PRINT(MSG_ALWAYS, ("Read OTP Revison ... %d\n", (int)OTP_rev));
	//DEBUG_PRINT(MSG_ALWAYS, ("Latest OTP Revison ... %d\n", (int)LATEST_OTP_REV));
     #if API_DEBUG_CODE
		printf("Read OTP Revison ... %d\n", (int)OTP_rev);
     #endif
     #if API_DEBUG_CODE
		printf("Latest OTP Revison ... %d\n", (int)LATEST_OTP_REV);
     #endif

	switch (OTP_rev)
	{
		case 0:
			SiIRegioWrite(0x071, 0xA2); // RX_Ctrl6
			SiIRegioWrite(0x06C, 0x08); // RX_Ctrl1
			SiIRegioWrite(0x024, 0x84); // DPLL_CFG6
			SiIRegioWrite(0x00C, 0x45); // DATA_MUX_1
			SiIRegioWrite(0x00D, 0x0E); // DATA_MUX_2
			SiIRegioWrite(0x050, 0xEE); // TX_SWING
			SiIRegioWrite(0x051, 0x80); // TX_SWING1
			SiIRegioWrite(0x07E, 0x10); // POWERMUX_CTRL2, To adjust 20MHz oscillator setting
			SiIRegioWrite(0x081, 0x98); // CBUS_FLOAT
			SiIRegioWrite(0x017, 0x00); // PEQ_VAL0
			SiIRegioWrite(0x018, 0x20); // PEQ_VAL1
			SiIRegioWrite(0x019, 0x40); // PEQ_VAL2
			SiIRegioWrite(0x01A, 0x70); // PEQ_VAL3
			SiIRegioWrite(0x01B, 0x13); // PEQ_VAL4
			SiIRegioWrite(0x01C, 0x23); // PEQ_VAL5
			SiIRegioWrite(0x01D, 0x33); // PEQ_VAL6
			SiIRegioWrite(0x01E, 0x63); // PEQ_VAL7
			SiIRegioWrite(0x089, 0x22); // DPLL_BW_CFG1
			SiIRegioWrite(0x08B, 0x00); // MEQ_VAL0
			SiIRegioWrite(0x08C, 0x20); // MEQ_VAL1
			SiIRegioWrite(0x08D, 0x40); // MEQ_VAL2
			SiIRegioWrite(0x08E, 0x70); // MEQ_VAL3
			SiIRegioWrite(0x013, 0x01); // DPLL_CFG3, turn OFF BW scan
			SiIRegioWrite(0x01F, 0x14); // PBW_VAL0, HDMI BW
			SiIRegioWrite(0x020, 0x15); // PBW_VAL1, This value may not be optimal, but is better than the current default one.  
										// Will probably not be used since BW scan is OFF, but probably is safer to have a decent value in this register just in case.
			SiIRegioWrite(0x021, 0x1B); // PBW_VAL2, MHL BW
			SiIRegioWrite(0x022, 0x1C); // PBW_VAL3, This value may not be optimal, but is better than the current default one.  
										// Will probably not be used since BW scan is OFF, but probably is safer to have a decent value in this register just in case.
			SiIRegioWrite(0x014, 0x9C); // DPLL_CFG4, SCDT auto reset enable
			SiIRegioWrite(0x077, 0x60); // CBUS_HPD_HOLD. Must change this value from default of 0xC0 to pass MHL spec for TSINK: DCAP_RDY parameter.  Must also change to this new value for the dongle (SiI9292) as well
			SiIRegioWrite(0x073, 0x03); // CBUS_DISC_OVR. Enable default MHL/HDMI mode strapping override.  New register value strapping is MHL mode.  
			SiIRegioWrite(0x007, 0x77); // RSVD. Change default value of CBUS drive strength.  Must also change to this new value for the dongle (SiI9292) as well
		case 1:
			SiIRegioWrite(0xC80, 0x00); // Dev Cap 0: DEV_STATE
			SiIRegioWrite(0xC81, 0x10); // Dev Cap 1: MHL_VERSION
			SiIRegioWrite(0xC82, 0x01); // Dev Cap 2: DEV_CAT
			SiIRegioWrite(0xC83, 0x00); // Dev Cap 3: ADOPTER_ID_H
			SiIRegioWrite(0xC84, 0x00); // Dev Cap 4: ADOPTER_ID_L
			SiIRegioWrite(0xC85, 0x37); // Dev Cap 5: VID_LINK_MODE
			SiIRegioWrite(0xC86, 0x00); // Dev Cap 6: AUD_LINK_MODE
			SiIRegioWrite(0xC87, 0x00); // Dev Cap 7: VIDEO_TYPE
			SiIRegioWrite(0xC88, 0x00); // Dev Cap 8: LOG_DEV_MAP
			SiIRegioWrite(0xC89, 0x0F); // Dev Cap 9: BANDWIDTH
			SiIRegioWrite(0xC8A, 0x07); // Dev Cap A: FEATURE_FLAG
			SiIRegioWrite(0xC8B, 0x92); // Dev Cap B: DEVICE_ID_H
			SiIRegioWrite(0xC8D, 0x10); // Dev Cap D: SCRATCHPAD_SIZE
			SiIRegioWrite(0xC8F, 0x00); // Dev Cap F: RESERVED
		case 2:
			SiIRegioWrite(0x00A, 0x03); // SYS_CTRL3: TMDS output swing enable controlled by CKDT and SCDT
			SiIRegioWrite(0x00B, 0x1F); // PAD_COMB_CTRL: Set bits [1:0] both to 1 to enable CBUS Vinh enhancement
			SiIRegioWrite(0xC07, 0x77); // RSVD: Change default value of CBUS drive strength to maximum value
		case 3:
			SiIRegioWrite(0x07C, 0x2C); // DDC_CTRL: Adjust DDC speed to increase DDC I2C setup time for I2C compliance
			SiIRegioWrite(0xC8E, 0x33); // Dev Cap E: INT_STAT_SIZE
			SiIRegioWrite(0xC8C, 0x41); // Dev Cap C: DEVICE_ID_L, Upper nibble [7:4] of this register is used to indicate OTP revision. Lower nibble [3:0] of this register is used to indicate silicon revision
			//DEBUG_PRINT(MSG_ALWAYS, ("Updating registers ...\n"));
			     #if API_DEBUG_CODE
				printf("Updating registers ...\n");
    			     #endif
		case 4:
			SiIRegioWrite(0x07A, 0xD0); // RX_MISC // change 0xD4 to 0xD0, taking over CBUS control
			break;
		default:
			//DEBUG_PRINT(MSG_ALWAYS, ("Error in OTP Revison\n"));
			#if API_DEBUG_CODE
				printf("Error in OTP Revison\n");
    			#endif
			break;
	}

}
#endif // (FPGA_BUILD == 0)



//------------------------------------------------------------------------------
// Function:    CpCheckStandbyMode
// Description: To check if chip is in the standby mode
//              
//
//              
//------------------------------------------------------------------------------
bool_si CpCheckStandbyMode( void )
{
	return (g_data.standby_mode);

}


//------------------------------------------------------------------------------
// Function:    CpCableDetect
// Description: To check if MHL cable connected
//              
//
//              
//------------------------------------------------------------------------------
bool_si CpCableDetect( void )
{
	uint8_si uData;

#if 0
#ifdef BOARD_CP1292
	uData = SiIRegioRead(REG_GPIO_CTRL);
	if(uData & BIT_GPIO0_INPUT)
	{
#endif
#endif
//#ifdef BOARD_JULIPORT
	uData = SiIRegioRead(REG_STATE);
#if API_DEBUG_CODE
		printf("MHL REG_STATE uData = %x,mhl_con=%d\n",uData,mhl_con);
	#endif

	if(uData & BIT_V5DET)
	{

//#endif 
		if (!mhl_con)
		{
			mhl_con = true;
            SiIRegioModify(REG_RX_MISC, BIT_PSCTRL_OEN|BIT_PSCTRL_OUT|BIT_PSCTRL_AUTO|BIT_HPD_RSEN_ENABLE, 0);            			
			//DEBUG_PRINT(MSG_DBG, ("MHL Cable Connected!\n"));
			#if API_DEBUG_CODE
				printf("MHL Cable Connected!\n");
    			#endif
		}
		else
		{
			if(!g_HPD_IN)
			{
				SiIRegioWrite(0x07A, 0x40);
			}
		}
		return true;
	}
	else
	{
		if (mhl_con)
		{
			mhl_con = false;
			SiIRegioModify(REG_RX_MISC, BIT_PSCTRL_OEN|BIT_PSCTRL_OUT|BIT_PSCTRL_AUTO, BIT_PSCTRL_OEN|BIT_PSCTRL_OUT);			
			//DEBUG_PRINT(MSG_DBG, ("MHL Cable Unconnected!\n"));
			#if API_DEBUG_CODE
				printf("MHL Cable Unconnected!\n");
    			#endif
		}
		return false;
	}

}

bool_si CpCableDetect2( void )
{
	uint8_si uData;
	uData = SiIRegioRead(REG_GPIO_CTRL);
	if(uData & BIT_GPIO0_INPUT)
	{
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
// Function:    CpWakePulseDetect
// Description: To check if chip is in the standby mode
//              
//
//              
//------------------------------------------------------------------------------
char CpWakePulseDetect( void )
{
	static uint8_si state = 0;
	bool_si gpioValue;

	gpioValue = HalGpioReadWakeUpPin();

	if (state == 0)
	{
		if (!gpioValue)
		{
			g_startWidthCounter = true;
			state = 1;
			//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine: State 1\n"));
		}
	}
	else if (state == 1)
	{
		if (gpioValue)
		{
			g_startWidthCounter = false;
			
			if ((g_pulseWidthCounter >= MIN_WAKE_PULSE_WIDTH_1) && (g_pulseWidthCounter <= MAX_WAKE_PULSE_WIDTH_1))
			{
				state = 2;
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine: State 2\n"));
				g_pulseWidthCounter = 0;
				g_startWidthCounter = true;
			}
			else
			{
				state = 0;
				
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, 1 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, 1 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter);
    				#endif
				g_pulseWidthCounter = 0;
			}
		}
		else
		{
			if (g_pulseWidthCounter > MAX_WAKE_PULSE_WIDTH_1)
			{
				g_startWidthCounter = false;
				state = 0;
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, 1 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter));
				g_pulseWidthCounter = 0;
			}
		}
	}
	else if (state == 2)
	{
		if (!gpioValue)
		{
			g_startWidthCounter = false;
			
			if ((g_pulseWidthCounter >= MIN_WAKE_PULSE_WIDTH_1) && (g_pulseWidthCounter <= MAX_WAKE_PULSE_WIDTH_1))
			{
				state = 3;
				g_pulseWidthCounter = 0;
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine: State 3\n"));
			}
			else
			{
				state = 0;
				
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, 2 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, 2 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter);
    				#endif
				
				g_pulseWidthCounter = 0;
			}
		}
		else
		{
			if (g_pulseWidthCounter > MAX_WAKE_PULSE_WIDTH_1)
			{
				g_startWidthCounter = false;
				state = 0;
				
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, 2 Back to state 0, gpioValue = %x,  pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, 2 Back to state 0, gpioValue = %x,  pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter);
    				#endif

				g_pulseWidthCounter = 0;
			}
		}
	}
	else if (state == 3)
	{
		if (gpioValue)
		{
			state = 4;
			g_pulseWidthCounter = 0;
			g_startWidthCounter = true;
			//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine: State 4\n"));
		}
	}
	else if (state == 4)
	{
		if (!gpioValue)
		{
			g_startWidthCounter = false;
			
			if ((g_pulseWidthCounter >= MIN_WAKE_PULSE_WIDTH_2) && (g_pulseWidthCounter <= MAX_WAKE_PULSE_WIDTH_2))
			{
				state = 5;
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine: State 5\n"));

				g_pulseWidthCounter = 0;
				g_startWidthCounter = true;
			}
			else
			{
				state = 0;
				
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, 4 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, 4 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter);
    				#endif

				g_pulseWidthCounter = 0;
			}
		}
		else
		{
			if (g_pulseWidthCounter > MAX_WAKE_PULSE_WIDTH_2)
			{
				g_startWidthCounter = false;
				state = 0;
				
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, 4 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, 4 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter);
    				#endif

				g_pulseWidthCounter = 0;
			}
		}
	}
	else if (state == 5)
	{
		if (gpioValue)
		{
			g_startWidthCounter = false;
			
			if ((g_pulseWidthCounter >= MIN_WAKE_PULSE_WIDTH_1) && (g_pulseWidthCounter <= MAX_WAKE_PULSE_WIDTH_1))
			{
				state = 6;
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine: State 6\n"));

				g_pulseWidthCounter = 0;
				g_startWidthCounter = true;
			}
			else
			{
				state = 0;
				
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, 5 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, 5 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter);
    				#endif
				g_pulseWidthCounter = 0;
			}
		}
		else
		{
			if (g_pulseWidthCounter > MAX_WAKE_PULSE_WIDTH_1)
			{
				g_startWidthCounter = false;
				state = 0;
				
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, 5 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, 5 Back to state 0, gpioValue = %x, pulseWidth = %x\n", (int)gpioValue, (int)g_pulseWidthCounter);
    				#endif
				g_pulseWidthCounter = 0;
			}
		}
	}
	else if (state == 6)
	{
		if (!gpioValue)
		{
			g_startWidthCounter = false;
			
			if ((g_pulseWidthCounter >= MIN_WAKE_PULSE_WIDTH_1) && (g_pulseWidthCounter <= MAX_WAKE_PULSE_WIDTH_1))
			{
				state = 0;
				g_pulseWidthCounter = 0;
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse Detected\n"));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse Detected\n");
    				#endif

				g_data.standby_mode = false;
				SiIRegioModify(REG_TX_SWING1, BIT_SWCTRL_EN, BIT_SWCTRL_EN);
		    	GPIO_SET( LED7_GREEN );
				GPIO_CLR( LED7_AMBER );

				return true;
			}
			else
			{
				state = 0;
				g_pulseWidthCounter = 0;
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, Back to state 0\n"));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, Back to state 0\n");
    				#endif
			}
		}
		else
		{
			if (g_pulseWidthCounter > MAX_WAKE_PULSE_WIDTH_1)
			{
				g_startWidthCounter = false;
				state = 0;
				g_pulseWidthCounter = 0;
				//DEBUG_PRINT(MSG_DBG, ("WakeUp Pulse State Machine Check Fail, Back to state 0\n"));
				#if API_DEBUG_CODE
				printf("WakeUp Pulse State Machine Check Fail, Back to state 0\n");
    				#endif
			}
		}
	}

	return false;
}


