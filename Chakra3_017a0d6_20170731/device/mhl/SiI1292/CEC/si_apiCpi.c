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
//!file     si_apiCpi.c
//!brief    CP 9387 Starter Kit CPI functions.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2002-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include <stdio.h>
#include <string.h>
#include "./SiI1292/HAL/INC/si_hal.h"
#include "CEC/si_apiCpi.h"
#include "./SiI1292/API/si_api1292.h"
#include "si_cpi_regs.h"
#include "./SiI1292/API/si_regio.h"
#include "./SiI1292/CEC/si_cec_enums.h"
#include "./SiI1292/MAIN/si_cp1292.h"
#include "./SiI1292/CEC/si_apiCEC.h"
#if IS_CEC

//------------------------------------------------------------------------------
// Function:    SI_CpiSetLogicalAddr
// Description: Configure the CPI subsystem to respond to a specific CEC 
//              logical address.
//------------------------------------------------------------------------------

bool_si SI_CpiSetLogicalAddr ( uint8_si logicalAddress )
{
    uint8_si capture_address[2];
    uint8_si capture_addr_sel = 0x01;

#if 0//Keno20120301, disable RK design, because it will effect that cannot display
	if( logicalAddress != CEC_LOGADDR_UNREGORBC)
	{
	    uint8_si cecStatus[2];
		
		SI_CpiSendPing( logicalAddress );
		//DEBUG_PRINT(MSG_ALWAYS, ("Ping...[%X] %s...", (int)logicalAddress, CpCecTranslateLA( logicalAddress )));
		#if API_DEBUG_CODE
		printf("Ping...[%X] %s...", (int)logicalAddress, CpCecTranslateLA( logicalAddress ));
		#endif

		// Wait for SEND_POLL's Ack, if there's ACK, return false to try another address
        HalTimerWait( 1000 );
	    SiIRegioReadBlock( REG_CEC_INT_STATUS_0, cecStatus, 2);

		//printf("");
        if ( cecStatus[0] & BIT_TX_MESSAGE_SENT )
		{
			//DEBUG_PRINT(MSG_ALWAYS, ("----->Enum Ack\nTry next Address\n"));
			#if API_DEBUG_CODE
			printf("----->Enum Ack\nTry next Address\n");
			#endif
			return false;
		}
		else
		{
			//DEBUG_PRINT(MSG_ALWAYS, ("----->Enum No Ack\nThis address can be allocated\n"));
			#if API_DEBUG_CODE
			printf("----->Enum No Ack\nThis address can be allocated\n");
			#endif

		}
	}
#endif
	capture_address[0] = 0;
    capture_address[1] = 0;
    if( logicalAddress < 8 )
    {
        capture_addr_sel = capture_addr_sel << logicalAddress;
        capture_address[0] = capture_addr_sel;
    }
    else
    {
        capture_addr_sel   = capture_addr_sel << ( logicalAddress - 8 );
        capture_address[1] = capture_addr_sel;
    }

        // Set Capture Address

    SiIRegioWriteBlock(REG_CEC_CAPTURE_ID0, capture_address, 2 );
    SiIRegioWrite( REG_CEC_TX_INIT, logicalAddress );

	//DEBUG_PRINT( MSG_ALWAYS, (("CEC Logical Address: 0x%02X\n"), (int)logicalAddress ));
	#if API_DEBUG_CODE
	printf(("CEC Logical Address: 0x%02X\n"), (int)logicalAddress);
	#endif

    return( true );
}

//------------------------------------------------------------------------------
// Function:    SI_CpiSendPing
// Description: Initiate sending a ping, and used for checking available
//                       CEC devices
//------------------------------------------------------------------------------

void SI_CpiSendPing ( uint8_si bCECLogAddr )
{
    SiIRegioWrite( REG_CEC_TX_DEST, BIT_SEND_POLL | bCECLogAddr );
}

//------------------------------------------------------------------------------
// Function:    SI_CpiWrite
// Description: Send CEC command via CPI register set
//------------------------------------------------------------------------------

bool_si SI_CpiWrite( SI_CpiData_t *pCpi )
{
    uint8_si cec_int_status_reg[2];
#if IS_CEC
    if ( !(SiIRegioRead( REG_CEC_INT_STATUS_0 ) & BIT_TX_BUFFER_FULL ))
    {
#endif
#if (INCLUDE_CEC_NAMES > CEC_NO_TEXT)
    CpCecPrintCommand( pCpi, true );
#endif
    SiIRegioModify( REG_CEC_DEBUG_3, BIT_FLUSH_TX_FIFO, BIT_FLUSH_TX_FIFO );  // Clear Tx Buffer

        /* Clear Tx-related buffers; write 1 to bits to be cleared. */
  
    cec_int_status_reg[0] = 0x64 ; // Clear Tx Transmit Buffer Full Bit, Tx msg Sent Event Bit, and Tx FIFO Empty Event Bit
    cec_int_status_reg[1] = 0x02 ; // Clear Tx Frame Retranmit Count Exceeded Bit.
    SiIRegioWriteBlock( REG_CEC_INT_STATUS_0, cec_int_status_reg, 2 );

        /* Send the command */

    SiIRegioWrite( REG_CEC_TX_DEST, pCpi->srcDestAddr & 0x0F );           // Destination
    SiIRegioWrite( REG_CEC_TX_COMMAND, pCpi->opcode );
    SiIRegioWriteBlock( REG_CEC_TX_OPERAND_0, pCpi->args, pCpi->argCount );
    SiIRegioWrite( REG_CEC_TRANSMIT_DATA, BIT_TRANSMIT_CMD | pCpi->argCount );
#if IS_CEC
		HalTimerWait(25);
		SiIRegioModify( REG_CEC_DEBUG_3, BIT_FLUSH_TX_FIFO, BIT_FLUSH_TX_FIFO );  // Clear Tx Buffer
    }
    else
    {
        //DEBUG_PRINT( MSG_DBG, ( "\nSI_CpiWrite:: CEC Write buffer full!\n" ));
		#if API_DEBUG_CODE
		printf("\nSI_CpiWrite:: CEC Write buffer full!\n");
		#endif
    }
#endif
    return( true );
}

//------------------------------------------------------------------------------
// Function:    SI_CpiRead
// Description: Reads a CEC message from the CPI read FIFO, if present.
//------------------------------------------------------------------------------

bool_si SI_CpiRead( SI_CpiData_t *pCpi )
{
    bool_si    error = false;
    uint8_si argCount;

    argCount = SiIRegioRead( REG_CEC_RX_COUNT );

    if ( argCount & BIT_MSG_ERROR )
    {
        error = true;
    }
    else
    {
        pCpi->argCount = argCount & 0x0F;
        pCpi->srcDestAddr = SiIRegioRead( REG_CEC_RX_CMD_HEADER );
        pCpi->opcode = SiIRegioRead( REG_CEC_RX_OPCODE );
        if ( pCpi->argCount )
        {
            SiIRegioReadBlock( REG_CEC_RX_OPERAND_0, pCpi->args, pCpi->argCount );
        }
    }

        // Clear CLR_RX_FIFO_CUR;
        // Clear current frame from Rx FIFO

    SiIRegioModify( REG_CEC_RX_CONTROL, BIT_CLR_RX_FIFO_CUR, BIT_CLR_RX_FIFO_CUR );

#if (INCLUDE_CEC_NAMES > CEC_NO_TEXT)
    if ( !error )
    {
        CpCecPrintCommand( pCpi, false );
    }
#endif
    return( error );
}


//------------------------------------------------------------------------------
// Function:    SI_CpiStatus
// Description: Check CPI registers for a CEC event
//------------------------------------------------------------------------------

bool_si SI_CpiStatus( SI_CpiStatus_t *pStatus )
{
    uint8_si cecStatus[2];

    pStatus->txState    = 0;
    pStatus->cecError   = 0;
    pStatus->rxState    = 0;

    SiIRegioReadBlock( REG_CEC_INT_STATUS_0, cecStatus, 2);

    if ( (cecStatus[0] & 0x7F) || cecStatus[1] )
    {
        //DEBUG_PRINT(MSG_STAT,("\nCEC Status: %02X %02X\n", (int) cecStatus[0], (int) cecStatus[1]));
        	#if API_DEBUG_CODE
		printf("\nCEC Status: %02X %02X\n", (int) cecStatus[0], (int) cecStatus[1]);
		#endif

            // Clear interrupts

        if ( cecStatus[1] & BIT_FRAME_RETRANSM_OV )
        {
            //DEBUG_PRINT(MSG_DBG,("\n!TX retry count exceeded! [%02X][%02X]\n",(int) cecStatus[0], (int) cecStatus[1]));

                /* Flush TX, otherwise after clearing the BIT_FRAME_RETRANSM_OV */
                /* interrupt, the TX command will be re-sent.                   */

            SiIRegioModify( REG_CEC_DEBUG_3,BIT_FLUSH_TX_FIFO, BIT_FLUSH_TX_FIFO );
        }

            // Clear set bits that are set

        SiIRegioWriteBlock( REG_CEC_INT_STATUS_0, cecStatus, 2 );

            // RX Processing

        if ( cecStatus[0] & BIT_RX_MSG_RECEIVED )
        {
            pStatus->rxState = 1;   // Flag caller that CEC frames are present in RX FIFO
        }

            // RX Errors processing

        if ( cecStatus[1] & BIT_SHORT_PULSE_DET )
        {
            pStatus->cecError |= SI_CEC_SHORTPULSE;
        }

        if ( cecStatus[1] & BIT_START_IRREGULAR )
        {
            pStatus->cecError |= SI_CEC_BADSTART;
        }

        if ( cecStatus[1] & BIT_RX_FIFO_OVERRUN )
        {
            pStatus->cecError |= SI_CEC_RXOVERFLOW;
        }

            // TX Processing

        if ( cecStatus[0] & BIT_TX_FIFO_EMPTY )
        {
            pStatus->txState = SI_TX_WAITCMD;
        }
        if ( cecStatus[0] & BIT_TX_MESSAGE_SENT )
        {
            pStatus->txState = SI_TX_SENDACKED;
        }
        if ( cecStatus[1] & BIT_FRAME_RETRANSM_OV )
        {
            pStatus->txState = SI_TX_SENDFAILED;
        }
    }

    return( true );
}

//------------------------------------------------------------------------------
// Function:    SI_CpiGetLogicalAddr
// Description: Get Logical Address
//------------------------------------------------------------------------------

uint8_si SI_CpiGetLogicalAddr( void )
{
	return SiIRegioRead( REG_CEC_TX_INIT);
}

//------------------------------------------------------------------------------
// Function:    SI_CpiInit
// Description: Initialize the CPI subsystem for communicating via CEC
//------------------------------------------------------------------------------

bool_si SI_CpiInit( void )
{
    uint8_si capture_address[2];
    uint8_si capture_addr_sel = 0x01;

    // Turn off CEC auto response to <Abort> command.   
    //Remove this for pass CEC CTS
    //SiIRegioWrite( CEC_OP_ABORT_31, CLEAR_BITS );

    SiIRegioWrite( REG_CEC_CONFIG_CPI, 0x00 );
	SiIRegioBitToggle( REG_SRST, BIT_CEC_RST );

	// Jin: software workaround For Bug #20040
	// Disable CDC registers
	SiIRegioWrite( 0x8E3, 0x00);
	SiIRegioWrite( 0x8E4, 0x00);

    // initialized he CEC CEC_LOGADDR_TV logical address
#if 0//Keno20120301, disable RK design, because it will effect that cannot display
    if ( !SI_CpiSetLogicalAddr( CEC_LOGADDR_TV ))
    {
       	if ( !SI_CpiSetLogicalAddr( CEC_LOGADDR_SPECIFICUSE ))
	    {
			SI_CpiSetLogicalAddr( CEC_LOGADDR_UNREGORBC );
			g_cecAddress = CEC_LOGADDR_UNREGORBC;
		}
		else
			g_cecAddress = CEC_LOGADDR_SPECIFICUSE;
    }
	else
		g_cecAddress = CEC_LOGADDR_TV;
#endif
		g_cecAddress = CEC_LOGADDR_PLAYBACK1;	// Set CEC_LOGADDR_PLAYBACK1 at initial time
	
    capture_address[0] = 0;
    capture_address[1] = 0;
    if( g_cecAddress < 8 )
    {
        capture_addr_sel = capture_addr_sel << g_cecAddress;
        capture_address[0] = capture_addr_sel;
    }
    else
    {
        capture_addr_sel   = capture_addr_sel << ( g_cecAddress - 8 );
        capture_address[1] = capture_addr_sel;
    }

        // Set Capture Address

    SiIRegioWriteBlock(REG_CEC_CAPTURE_ID0, capture_address, 2 );
    SiIRegioWrite( REG_CEC_TX_INIT, g_cecAddress );

	//DEBUG_PRINT( MSG_ALWAYS, (("CEC Logical Address: 0x%02X\n"), (int)g_cecAddress ));
	#if API_DEBUG_CODE
		printf("CEC Logical Address: 0x%02X\n");
	#endif

	
    return( true );
}
#endif
