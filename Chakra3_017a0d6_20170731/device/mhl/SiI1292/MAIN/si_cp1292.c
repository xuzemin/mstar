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
//!file     si_cp1292.c
//!brief    CP 1292 FPGA/Starter Kit firmware main module.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009-2010, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include <string.h>

#include "./SiI1292/MAIN/si_cp1292.h"
#include "./SiI1292/API/si_api1292.h"
#include "CEC/si_apiCpi.h"
#include "./SiI1292/CEC/si_apiCEC.h"
#include "./SiI1292/MAIN/si_cpCEC.h"
#include "./SiI1292/CEC/si_cec_enums.h"
#include "./SiI1292/API/si_regio.h"
#include "./SiI1292/MSC/si_apiRCP.h"


//------------------------------------------------------------------------------
// Module data
//------------------------------------------------------------------------------

#if (FPGA_BUILD == 1)
    #define FPGA_STRING " (FPGA)"
#else
    #define FPGA_STRING ""
#endif

#ifdef BOARD_CP1292
//static char l_signonMsg [] = "CP 1292 Firmware v1.0.9.5 for Start Kit Used" FPGA_STRING;
#endif
#ifdef BOARD_JULIPORT
static char l_signonMsg [] = "CP 1292 Firmware v1.0.9.5 for Reference Design Kit Used" FPGA_STRING;
#endif


//------------------------------------------------------------------------------
// Global Data
//------------------------------------------------------------------------------

SI_CP1292Config_t   g_data;

uint8_si g_dbgPrinted = 0;

uint8_si g_currentInputMode = 0xff;

bool_si g_MHL_Source_Connected = false;

bool_si g_HDMI_Source_Connected = false;
bool_si g_HDMI_Source_Valid = false;

bool_si g_HPD_IN = false;
bool_si g_TX_RSEN = false;
bool_si g_TX_RSEN_Valid = false;

uint8_si PeerDevCap[16] = {0,0};

bool_si g_RC5_Key_UP = false;//Keno20120219, when press remote controller key button, this moment has 2 status, one is press down, other is bounce. keu up is bounce.

bool_si IsPrintAllRegs;
//------------------------------------------------------------------------------
// Function:    CpDeviceInit
// Description: Initialize the 1292 deviice
//------------------------------------------------------------------------------

bool_si CpDeviceInit ( void )
{
    uint16_si    temp;
    bool_si        success = true;

    /* Perform a hard reset on the device to ensure that it is in a known   */
    /* state (also downloads a fresh copy of EDID from NVRAM).              */

  //  DEBUG_PRINT( MSG_ALWAYS,("\nPower up Initialize..."));
  		#if API_DEBUG_CODE
			printf("\nPower up Initialize...");
   		#endif

    temp = ((uint16_si)SI_DeviceStatus( SI_DEV_IDH)) << 8;
    temp |= SI_DeviceStatus( SI_DEV_IDL );
    //DEBUG_PRINT( MSG_ALWAYS,( "Silicon Image Device: %04X, rev %02X\n\n", temp, (int)(SI_DeviceStatus( SI_DEV_REV ) & 0x0F) ));
      		#if API_DEBUG_CODE
			printf("Silicon Image Device: %04X, rev %02X\n\n", temp, (int)(SI_DeviceStatus( SI_DEV_REV ) & 0x0F));
   		#endif

	g_data.portSelect = 0;	

	// Jin: For manually PS_CNTL, avioding power-on time HDMI_DET pin voltage high issue.
	// Disable Q3 FET first
	//SiIRegioModify(REG_RX_MISC, BIT_PSCTRL_OEN|BIT_PSCTRL_OUT|BIT_PSCTRL_AUTO, BIT_PSCTRL_OUT);

    /*if ( temp != 0x1292 && temp != 0x9292 )
    {
        success = false;
    }*/
	
    return( success );
}

//------------------------------------------------------------------------------
// Function:    BoardInit
// Description: One time initialization at startup
//------------------------------------------------------------------------------
extern uint8_si HalVersion ( bool_si wantMajor );
static void BoardInit ( void )
{

    /* FPGA Initialization. */

#if (FPGA_BUILD == 1)
    char        i;
    //DEBUG_PRINT( MSG_ALWAYS, ("\n" ));
    #if API_DEBUG_CODE
	printf("\n");
   #endif	
		
    for ( i = 6; i >= 0; i-- )
    {
      //  DEBUG_PRINT( MSG_ALWAYS, ("%d...", (int)i ));
          #if API_DEBUG_CODE
		printf("%d...", (int)i );
   	   #endif	
        HalTimerWait( 1000 );
    }
  //  DEBUG_PRINT( MSG_ALWAYS, ("\n" ));
            #if API_DEBUG_CODE
		printf("\n");
   	   #endif	

   // DEBUG_PRINT( MSG_ALWAYS, ("FPGA HAL Version: %d.%02d\n", (int)HalVersionFPGA( 1 ), (int)HalVersionFPGA( 0 )));
           #if API_DEBUG_CODE
		printf("FPGA HAL Version: %d.%02d\n", (int)HalVersionFPGA( 1 ), (int)HalVersionFPGA( 0 ));
   	   #endif	
#else
  //  DEBUG_PRINT( MSG_ALWAYS, ("HAL Version: %d.%02d\n", (int)HalVersion( 1 ), (int)HalVersion( 0 )));
   	   #if API_DEBUG_CODE
		printf("HAL Version: %d.%02d\n", (int)HalVersion( 1 ), (int)HalVersion( 0 ));
   	   #endif	
#endif

    /* Power up the chip, check it's type, and initialize to default values.    */

    if ( !CpDeviceInit())
    {
        //DEBUG_PRINT( MSG_ALWAYS,( "\n!!!!Device Init failure, halting...\n" ));
          #if API_DEBUG_CODE
		printf("\n!!!!Device Init failure, halting...\n");
   	   #endif	
        //CpBlinkTilReset( 0x06 ); //del by dengqq
    }

#if (FPGA_BUILD == 0)
	CpCheckOTPRev();						// check OTP Rev and update the registers
#ifdef BOARD_JULIPORT
//		SiIRegioWrite(0x005, 0x28); // Hold CEC in Reset
		SiIRegioWrite(0x00C, 0x11); // DATA_MUX_1
		SiIRegioWrite(0x00D, 0x0B); // DATA_MUX_2

#endif
#endif // FPGA_BUILD == 0
    CpReadInitialSettings();                // Read Jumper settings
#if IS_CEC
    if ( g_data.cecEnabled )
    {
        SI_CecInit();
		//DEBUG_PRINT( MSG_ALWAYS, ("CEC initial Logical Address is 0x%02X \n\n", (int)g_cecAddress));
	 #if API_DEBUG_CODE
		printf("CEC initial Logical Address is 0x%02X \n\n", (int)g_cecAddress);
   	  #endif	
    }
#endif

}

#if 0
void CommonModeNote(bool_si CommonMode)
{
#if 0
    static bool_si timer_set = false;
    static uint32_si count = 0;

    if( CommonMode )
    {
        if (!timer_set)
        {
            timer_set = true;
            count = timer_count;
        }
        else
        {
            if( HalTimerDelay(count, 5000) )
            {
                count = 0;
                timer_set= false;
                printf("in Common mode\n");
            }
        }
    }
    else 
    {
        timer_set = false;
        count = 0;
    }
#endif
}
#endif

void PrintAllRegs(void)
{
#if API_DEBUG_CODE
	uint8_si temp;
	uint16_si i;
	printf("\n\nPage0, Address0xD0 (CI2CA = LOW), Addess0xD4 (CI2CA = HIGH)\n", 0);
	printf("      0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F\n", 0);
	printf("-----------------------------------------------------------------------\n", 0);
	for(i=0x0000;i<0x0100;i++)
	{
		if((i == 0x00)||(i == 0x10)||(i == 0x20)||(i == 0x30)||(i == 0x40)||(i == 0x50)||(i == 0x60)||(i == 0x70)||
		(i == 0x80)||(i == 0x90)||(i == 0xA0)||(i == 0xB0)||(i == 0xC0)||(i == 0xD0)||(i == 0xE0)||(i == 0xF0))printf("%02X:  ", (int)i);
		temp = SiIRegioRead(i);
		printf("%02X  ", (int)temp);
		if((i == 0x0F)||(i == 0x1F)||(i == 0x2F)||(i == 0x3F)||(i == 0x4F)||(i == 0x5F)||(i == 0x6F)||(i == 0x7F)||
		(i == 0x8F)||(i == 0x9F)||(i == 0xAF)||(i == 0xBF)||(i == 0xCF)||(i == 0xDF)||(i == 0xEF)||(i == 0xFF))printf("\n", 0);
	}
	printf("\n\nPage8, Address0xC0 (CI2CA = LOW), Addess0xC4 (CI2CA = HIGH)\n", 0);
	printf("      0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F\n", 0);
	printf("-----------------------------------------------------------------------\n", 0);
	for(i=0x0800;i<0x0900;i++)
	{
		if((i == 0x0800)||(i == 0x0810)||(i == 0x0820)||(i == 0x0830)||(i == 0x0840)||(i == 0x0850)||(i == 0x0860)||(i == 0x0870)||
		(i == 0x0880)||(i == 0x0890)||(i == 0x08A0)||(i == 0x08B0)||(i == 0x08C0)||(i == 0x08D0)||(i == 0x08E0)||(i == 0x08F0))printf("%02X:  ", (int)i);
		temp = SiIRegioRead(i);
		printf("%02X  ", (int)temp);
		if((i == 0x080F)||(i == 0x081F)||(i == 0x082F)||(i == 0x083F)||(i == 0x084F)||(i == 0x085F)||(i == 0x086F)||(i == 0x087F)||
		(i == 0x088F)||(i == 0x089F)||(i == 0x08AF)||(i == 0x08BF)||(i == 0x08CF)||(i == 0x08DF)||(i == 0x08EF)||(i == 0x08FF))printf("\n", 0);
	}
	printf("\n\nPageC, Address0xC8 (CI2CA = LOW), Addess0xCC (CI2CA = HIGH)\n", 0);
	printf("      0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F\n", 0);
	printf("-----------------------------------------------------------------------\n", 0);
	for(i=0x0C00;i<0x0D00;i++)
	{
		if((i == 0x0C00)||(i == 0x0C10)||(i == 0x0C20)||(i == 0x0C30)||(i == 0x0C40)||(i == 0x0C50)||(i == 0x0C60)||(i == 0x0C70)||
		(i == 0x0C80)||(i == 0x0C90)||(i == 0x0CA0)||(i == 0x0CB0)||(i == 0x0CC0)||(i == 0x0CD0)||(i == 0x0CE0)||(i == 0x0CF0))printf("%02X:  ", (int)i);
		temp = SiIRegioRead(i);
		printf("%02X  ", (int)temp);
		if((i == 0x0C0F)||(i == 0x0C1F)||(i == 0x0C2F)||(i == 0x0C3F)||(i == 0x0C4F)||(i == 0x0C5F)||(i == 0x0C6F)||(i == 0x0C7F)||
		(i == 0x0C8F)||(i == 0x0C9F)||(i == 0x0CAF)||(i == 0x0CBF)||(i == 0x0CCF)||(i == 0x0CDF)||(i == 0x0CEF)||(i == 0x0CFF))printf("\n", 0);
	}
#endif
}
//------------------------------------------------------------------------------
// Function:    main
// Description: CP 1292 startup and supervisor control loop
//------------------------------------------------------------------------------

#if 0
void main ( void )
{

    HalInitialize();
    HalTimerInit();
    HalUartInit();
    HalIRInit();
    HalGpioInit();
 //   EA  = 1;                                    // Enable MCU global interrupts (HAL Timer, UART, IR, EX0)

    printf( "\n\n%s - %s\n", l_signonMsg, strDeviceID );
    printf("Build: %s-%s\n", __DATE2__, __TIME__ );

    printf("NOTE: from 1.0.8 , hw i2c is used;\n" );
    printf("NOTE: please be sure that R27 and R29 is weld in CP1292 start kit \n");

#ifdef HWI2C
    printf("NOTE: hw i2c is using now \n" );
#endif

    BoardInit();

    CpCbusInitialize();

    while ( 1 )
    {
        /* Check Simon or . requests.    */

        if ( CpCheckExternalRequests() )
        {
            CommonModeNote(true);
            continue;
        }
        else
        {
            CommonModeNote(false);
        }

        /*****************************************************************************************/
        /****** The remainder of this function is executed only if Simon is NOT in operation.    */
        /*****************************************************************************************/ 

        /* Check to see if the chip wants service.  */

        CpCbusHandler();

        if ( g_data.irEnabled )
        {
            CpIrHandler();
        }
        if ( g_data.cecEnabled )
        {
            /* Process any pending CEC messages received.   */

            SI_CecHandler( g_data.portSelect, false );

        }

        SI_DeviceEventMonitor();
    }
}
#else
extern void HAL_8032_TO_RiscIR(uint8_si teventType,uint8_si command );
void Mhlfuntion_inition(void)
{

	CpCbusInitialize();
	BoardInit();
	HAL_8032_TO_RiscIR(0,0); //init ir data;

}

void mhlfunction ( void )
{
    
   // while ( 1 )
    {
        /* Check Simon or . requests.    */

        if ( CpCheckExternalRequests() )
        {
          //  CommonModeNote(true);
           // continue; 
        }
        else
        {
           // CommonModeNote(false);
        

        /*****************************************************************************************/
        /****** The remainder of this function is executed only if Simon is NOT in operation.    */
        /*****************************************************************************************/ 

        /* Check to see if the chip wants service.  */

        CpCbusHandler();

        if ( g_data.irEnabled ) //system is set to false
        {
            CpIrHandler();
        }
#if IS_CEC		
        if ( g_data.cecEnabled ) //system is set to true
        {
            /* Process any pending CEC messages received.   */

            SI_CecHandler( g_data.portSelect, false );

        }
#endif
        SI_DeviceEventMonitor();
        }
    }
    
}
#endif
