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
//!file     si_apiCEC.c
//!brief    Silicon Image mid-level CEC handler
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include <string.h>
#include "./SiI1292/API/si_api1292.h"
#include "./SiI1292/MAIN/si_cp1292.h"
#if (API_DEBUG_CODE==1)
    #include <stdio.h>
#endif
#include "./SiI1292/API/si_regio.h"
#include "./SiI1292/CEC/si_apiCEC.h"
#include "./SiI1292/HAL/INC/si_hal.h"
#include "./SiI1292/CBUS/si_apiCbus.h"
//#include <si_apiHEAC.h>
#if IS_CEC
bool_si si_CecRxMsgHandlerARC( SI_CpiData_t *pCpi );   // Warning: Starter Kit Specific
bool_si CpCecRxMsgHandler( SI_CpiData_t *pCpi );       // Warning: Starter Kit Specific
bool_si si_CDCProcess( SI_CpiData_t *pCdcCmd );        // Warning: Starter Kit Specific

//-------------------------------------------------------------------------------
// CPI Enums, typedefs, and manifest constants
//-------------------------------------------------------------------------------

    /* New Source Task internal states    */

enum
{
    NST_START               = 1,
    NST_SENT_PS_REQUEST,
    NST_SENT_PWR_ON,
    NST_SENT_STREAM_REQUEST
};

    /* Task CPI states. */

enum
{
    CPI_IDLE            = 1,
    CPI_SENDING,
    CPI_WAIT_ACK,
    CPI_WAIT_RESPONSE,
    CPI_RESPONSE
};

typedef struct
{
    uint8_si     task;       // Current CEC task
    uint8_si     state;      // Internal task state
    uint8_si     cpiState;   // State of CPI transactions
    uint8_si     destLA;     // Logical address of target device
    uint8_si     taskData1;  // BYTE Data unique to task.
    uint16_si    taskData2;  // WORD Data unique to task.

} CEC_TASKSTATE;

//------------------------------------------------------------------------------
// Data
//------------------------------------------------------------------------------

CEC_DEVICE   g_childPortList [SII_NUMBER_OF_PORTS];

//-------------------------------------------------------------------------------
// Module data
//-------------------------------------------------------------------------------

uint8_si     g_cecAddress;
uint16_si    g_cecPhysical           = 0x0000;               // set 0 for initial

static uint8_si  g_currentTask       = SI_CECTASK_IDLE;

static bool_si     l_cecEnabled        = false;
static uint8_si  l_powerStatus       = CEC_POWERSTATUS_ON;
static uint8_si  l_portSelect        = 0x00;
static uint8_si  l_sourcePowerStatus = CEC_POWERSTATUS_STANDBY;

    /* Active Source Addresses  */

static uint8_si  l_activeSrcLogical  = CEC_LOGADDR_UNREGORBC;    // Logical address of our active source
static uint16_si l_activeSrcPhysical = 0x0000;

//Cbus Related data
static uint8_si l_cbusRequestChannel = 0xFF;
static uint32_si l_featureAbortTimer = 0;

//static uint8_si ROM l_devTypes [16] =
uint8_si l_devTypes [16] =
{
    CEC_LOGADDR_TV,
    CEC_LOGADDR_RECDEV1,
    CEC_LOGADDR_RECDEV2,
    CEC_LOGADDR_TUNER1,
    CEC_LOGADDR_PLAYBACK1,
    CEC_LOGADDR_AUDSYS,
    CEC_LOGADDR_TUNER2,
    CEC_LOGADDR_TUNER3,
    CEC_LOGADDR_PLAYBACK2,
    CEC_LOGADDR_RECDEV1,
    CEC_LOGADDR_TUNER2,
    CEC_LOGADDR_PLAYBACK3,
    0x02,
    0x02,
    CEC_LOGADDR_TV,
    CEC_LOGADDR_TV
};

    /* CEC task data    */

static uint8_si l_newTask            = false;
static CEC_TASKSTATE l_cecTaskState = { 0 };
static CEC_TASKSTATE l_cecTaskStateQueued =
{
    SI_CECTASK_ENUMERATE,           // Current CEC task
    0,                              // Internal task state
    CPI_IDLE,                       // cpi state
    0x00,                           // Logical address of target device
    0x00,                           // BYTE Data unique to task.
    0x0000                          // WORD Data unique to task.
};

//------------------------------------------------------------------------------
// Function:
// Description:
//------------------------------------------------------------------------------

static void PrintLogAddr ( uint8_si bLogAddr )
{

#if (INCLUDE_CEC_NAMES > CEC_NO_NAMES)
    //DEBUG_PRINT( MSG_DBG,(  " [%X] %s", (int)bLogAddr, CpCecTranslateLA( bLogAddr ) ));
	#if API_DEBUG_CODE
	printf(" [%X] %s", (int)bLogAddr, CpCecTranslateLA( bLogAddr ));
	#endif
#else
    bLogAddr = 0;   // Passify the compiler
#endif
}


//------------------------------------------------------------------------------
// Function:    CecSendUserControlPressed
// Description: Local function for sending a "remote control key pressed"
//              command to the specified source.
//------------------------------------------------------------------------------

static void CecSendUserControlPressed ( uint8_si keyCode, uint8_si destLA  )
{
    SI_CpiData_t cecFrame;

    cecFrame.opcode        = CECOP_USER_CONTROL_PRESSED;
    cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, destLA );
    cecFrame.args[0]       = keyCode;
    cecFrame.argCount      = 1;
    SI_CpiWrite( &cecFrame );
}

//------------------------------------------------------------------------------
// Function:    CecSendFeatureAbort
// Description: Send a feature abort as a response to this message unless
//              it was broadcast (illegal).
//------------------------------------------------------------------------------

static void CecSendFeatureAbort ( SI_CpiData_t *pCpi, uint8_si reason )
{
    SI_CpiData_t cecFrame;

    if (( pCpi->srcDestAddr & 0x0F) != CEC_LOGADDR_UNREGORBC )
    {
        cecFrame.opcode        = CECOP_FEATURE_ABORT;
        cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, (pCpi->srcDestAddr & 0xF0) >> 4 );
        cecFrame.args[0]       = pCpi->opcode;
        cecFrame.args[1]       = reason;
        cecFrame.argCount      = 2;
        SI_CpiWrite( &cecFrame );
    }
}



//------------------------------------------------------------------------------
// Function:    CecHandleFeatureAbort
// Description: Received a failure response to a previous message.  Print a
//              message and notify the rest of the system
//------------------------------------------------------------------------------

#if (INCLUDE_CEC_NAMES > CEC_NO_TEXT)
static char *ml_abortReason [] =        // (0x00) <Feature Abort> Opcode    (RX)
    {
    "Unrecognized OpCode",              // 0x00
    "Not in correct mode to respond",   // 0x01
    "Cannot provide source",            // 0x02
    "Invalid Operand",                  // 0x03
    "Refused"                           // 0x04
    };
#endif

static void CecHandleFeatureAbort( SI_CpiData_t *pCpi )
{
    SI_CpiData_t cecFrame;

    cecFrame.opcode = pCpi->args[0];
    cecFrame.argCount = 0;
#if (INCLUDE_CEC_NAMES > CEC_NO_NAMES)
#if 0
    DEBUG_PRINT(
        MSG_STAT, (
        "\nMessage %s(%02X) was %s by %s (%d)\n",
        CpCecTranslateOpcodeName( &cecFrame ), (int)pCpi->args[0],
        ml_abortReason[ (pCpi->args[1] <= CECAR_REFUSED) ? pCpi->args[1] : 0],
        CpCecTranslateLA( pCpi->srcDestAddr >> 4 ), (int)(pCpi->srcDestAddr >> 4)
        ));
#endif
	#if API_DEBUG_CODE
	printf(
        "\nMessage %s(%02X) was %s by %s (%d)\n",
        CpCecTranslateOpcodeName( &cecFrame ), (int)pCpi->args[0],
        ml_abortReason[ (pCpi->args[1] <= CECAR_REFUSED) ? pCpi->args[1] : 0],
        CpCecTranslateLA( pCpi->srcDestAddr >> 4 ), (int)(pCpi->srcDestAddr >> 4)
        );
	#endif
#elif (INCLUDE_CEC_NAMES > CEC_NO_TEXT)
#if 0
    DEBUG_PRINT(
        MSG_STAT, (
        "\nMessage %02X was %s by logical address %d\n",
        (int)pCpi->args[0],
        ml_abortReason[ (pCpi->args[1] <= CECAR_REFUSED) ? pCpi->args[1] : 0],
        (int)(pCpi->srcDestAddr >> 4)
        ));

#endif
	printf(
        "\nMessage %02X was %s by logical address %d\n",
        (int)pCpi->args[0],
        ml_abortReason[ (pCpi->args[1] <= CECAR_REFUSED) ? pCpi->args[1] : 0],
        (int)(pCpi->srcDestAddr >> 4)
        ):
#endif
	if ( (l_cbusRequestChannel != 0xFF) && (l_featureAbortTimer != 0) )
	{
		SI_CbusCecRetHandler(l_cbusRequestChannel, false);
		l_cbusRequestChannel = 0xFF;
		l_featureAbortTimer = 0;
	}

}



//------------------------------------------------------------------------------
// Function:    CecTaskEnumerate
// Description: Ping every logical address on the CEC bus to see if anything
//              is attached.  Code can be added to store information about an
//              attached device, but we currently do nothing with it.
//
//              As a side effect, we determines our Initiator address as
//              the first available address of 0x04, 0x08 or 0x0B.
//
// l_cecTaskState.taskData1 == Not Used.
// l_cecTaskState.taskData2 == Not used
//------------------------------------------------------------------------------

static uint8_si CecTaskEnumerate ( SI_CpiStatus_t *pCecStatus )
{
    uint8_si newTask = l_cecTaskState.task;

    if ( l_cecTaskState.cpiState == CPI_IDLE )
    {
        if ( l_cecTaskState.destLA < CEC_LOGADDR_UNREGORBC )   // Don't ping broadcast address
        {
            SI_CpiSendPing( l_cecTaskState.destLA );
            //DEBUG_PRINT( MSG_DBG, ( "...Ping...\n" ));
            	#if API_DEBUG_CODE
		printf("...Ping...\n");
		#endif
            PrintLogAddr( l_cecTaskState.destLA );
            l_cecTaskState.cpiState = CPI_WAIT_ACK;
        }
        else    // We're done
        {
            SI_CpiSetLogicalAddr( g_cecAddress );
            //DEBUG_PRINT( MSG_DBG,( "ENUM DONE: Initiator address is " ));
              #if API_DEBUG_CODE
		printf("ENUM DONE: Initiator address is ");
		#endif
            PrintLogAddr( g_cecAddress );
            //DEBUG_PRINT( MSG_DBG,( "\n" ));
              #if API_DEBUG_CODE
		printf("\n");
		#endif

                /* Go to idle task, we're done. */

            l_cecTaskState.cpiState = CPI_IDLE;
            newTask = SI_CECTASK_IDLE;
        }
    }
    else if ( l_cecTaskState.cpiState == CPI_WAIT_ACK )
    {
        if ( pCecStatus->txState == SI_TX_SENDFAILED )
        {
            //DEBUG_PRINT( MSG_DBG,( "\nEnum NoAck" ));
              #if API_DEBUG_CODE
		printf("\nEnum NoAck");
		#endif
            PrintLogAddr( l_cecTaskState.destLA );

            /* If a TV address, grab it for our use.    */

            if (( g_cecAddress == CEC_LOGADDR_UNREGORBC ) &&
                (( l_cecTaskState.destLA == CEC_LOGADDR_PLAYBACK1) ||
                 ( l_cecTaskState.destLA == CEC_LOGADDR_PLAYBACK2) ||
                 ( l_cecTaskState.destLA == CEC_LOGADDR_PLAYBACK3) ))
            {
                g_cecAddress = l_cecTaskState.destLA;
            }

            /* Restore Tx State to IDLE to try next address.    */

            l_cecTaskState.cpiState = CPI_IDLE;
            l_cecTaskState.destLA++;
        }
        else if ( pCecStatus->txState == SI_TX_SENDACKED )
        {
            //DEBUG_PRINT( MSG_DBG,( "\n-----------------------------------------------> Enum Ack\n" ));
              #if API_DEBUG_CODE
		printf("\n-----------------------------------------------> Enum Ack\n");
		#endif
            PrintLogAddr( l_cecTaskState.destLA );

            /* TODO: Add code here to store info about this device if needed.   */

            /* Restore Tx State to IDLE to try next address.    */

            l_cecTaskState.cpiState = CPI_IDLE;
            l_cecTaskState.destLA++;
        }
    }

    return( newTask );
}

//------------------------------------------------------------------------------
// Function:    CecTaskTxReport
// Description: Report Physical Address
//
// l_cecTaskState.taskData1 == retry number.
// l_cecTaskState.taskData2 == Not used
//------------------------------------------------------------------------------

static uint8_si CecTaskTxReport ( SI_CpiStatus_t *pCecStatus )
{
    uint8_si newTask = l_cecTaskState.task;

    if ( l_cecTaskState.cpiState == CPI_IDLE )
    {
	    SI_CpiData_t    cecFrame;

		cecFrame.opcode        = CECOP_REPORT_PHYSICAL_ADDRESS;
		cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_UNREGORBC );
		cecFrame.args[0]       = (uint8_si) (g_cecPhysical >> 8);             		// [Physical Address] high byte
		cecFrame.args[1]       = (uint8_si)(g_cecPhysical & 0x00FF);     // [Physical Address] low byte
		cecFrame.args[2]       = (uint8_si) g_cecAddress;   
		cecFrame.argCount      = 3;
		SI_CpiWrite( &cecFrame );


		cecFrame.opcode        = CECOP_REPORT_PHYSICAL_ADDRESS;
		cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_UNREGORBC );
		cecFrame.args[0]       = (uint8_si) (g_cecPhysical >> 8);             		// [Physical Address] high byte
		cecFrame.args[1]       = (uint8_si)(g_cecPhysical & 0x00FF);     // [Physical Address] low byte
		cecFrame.args[2]       = (uint8_si) g_cecAddress;   
		cecFrame.argCount      = 3;
		SI_CpiWrite( &cecFrame );



		l_cecTaskState.cpiState = CPI_WAIT_ACK;		
    }
    else if ( l_cecTaskState.cpiState == CPI_WAIT_ACK )
    {
        if ( pCecStatus->txState == SI_TX_SENDFAILED )
        {
            l_cecTaskState.cpiState = CPI_IDLE;
			if (l_cecTaskState.taskData1 == 0)
			{
				newTask = SI_CECTASK_TXREPORT;	// retry once
				l_cecTaskState.taskData1 = 1;
			}
			else
			{
				newTask = SI_CECTASK_IDLE;	// fail
				printf("CEC:: Report Physical Address fail!\n");
			}
        }
        else if ( pCecStatus->txState == SI_TX_SENDACKED )
        {
            l_cecTaskState.cpiState = CPI_IDLE;
			l_cecTaskState.taskData1 = 0;
			newTask = SI_CECTASK_IDLE;	// done
        }
    }
//	printf("CecTaskTxReport task returning [%d]\n",(int)newTask);
    return( newTask );
}

//------------------------------------------------------------------------------
// Function:    CecTaskSetOSDName
// Description: Report Physical Address
//
// l_cecTaskState.taskData1 == retry number.
// l_cecTaskState.taskData2 == Not used
//------------------------------------------------------------------------------

static uint8_si CecTaskSetOSDName ( SI_CpiStatus_t *pCecStatus )
{
    uint8_si newTask = l_cecTaskState.task;

    if ( l_cecTaskState.cpiState == CPI_IDLE )
    {
	    SI_CpiData_t    cecFrame;

        cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, 0 );
        cecFrame.opcode        = CECOP_SET_OSD_NAME;
	    cecFrame.args[0] = 0x4D; //M
        cecFrame.args[1] = 0x48; //H
        cecFrame.args[2] = 0x4C; //L
		cecFrame.args[3] = 0x20; //space
        cecFrame.args[4] = 0x44; //D
        cecFrame.args[5] = 0x65; //e
		cecFrame.args[6] = 0x76; //v
        cecFrame.args[7] = 0x69; //i
        cecFrame.args[8] = 0x63; //c
		cecFrame.args[9] = 0x65; //e
		cecFrame.argCount = 10;
        SI_CpiWrite( &cecFrame );

//		TIMER_Wait(TIMER_DELAY,50);

		l_cecTaskState.cpiState = CPI_WAIT_ACK;		
    }
    else if ( l_cecTaskState.cpiState == CPI_WAIT_ACK )
    {
        if ( pCecStatus->txState == SI_TX_SENDFAILED )
        {
            l_cecTaskState.cpiState = CPI_IDLE;
			if (l_cecTaskState.taskData1 == 0)
			{
				newTask = SI_CECTASK_SETOSDNAME;	// retry once
				l_cecTaskState.taskData1 = 1;
			}
			else
			{
				newTask = SI_CECTASK_IDLE;	// fail
				printf("CEC:: Report Physical Address fail!\n");
			}
        }
        else if ( pCecStatus->txState == SI_TX_SENDACKED )
        {
            l_cecTaskState.cpiState = CPI_IDLE;
			l_cecTaskState.taskData1 = 0;
			newTask = SI_CECTASK_IDLE;	// done
        }
    }
//	printf("CecTaskSetOSDName task returning [%d]\n",(int)newTask);
    return( newTask );
}

//------------------------------------------------------------------------------
// Function:    CecTaskOneTouchPlay
// Description: Send Active Source, Image view on, Text View on
//
// l_cecTaskState.taskData1 == retry number.
// l_cecTaskState.taskData2 == step number
//------------------------------------------------------------------------------

static uint8_si CecTaskOneTouchPlay ( SI_CpiStatus_t *pCecStatus )
{
    uint8_si newTask = l_cecTaskState.task;

    if ( l_cecTaskState.cpiState == CPI_IDLE )
    {
	    SI_CpiData_t    cecFrame;

		if(l_cecTaskState.taskData2 == 0)
		{
			cecFrame.opcode        = CECOP_ACTIVE_SOURCE;
	        cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_UNREGORBC);
	        cecFrame.args[0]       = g_cecPhysical >> 8;             		// [Physical Address] high byte
	        cecFrame.args[1]       = (uint8_si)(g_cecPhysical & 0x00FF);     // [Physical Address] low byte
	        cecFrame.argCount      = 2;
	        SI_CpiWrite( &cecFrame );
		}
		else if (l_cecTaskState.taskData2 == 1)
		{
			cecFrame.opcode        = CECOP_IMAGE_VIEW_ON;
	        cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_TV );
	        cecFrame.argCount      = 0;
	        SI_CpiWrite( &cecFrame );
		}
		else
		{
			cecFrame.opcode        = CECOP_TEXT_VIEW_ON;
	        cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_TV );
	        cecFrame.argCount      = 0;
	        SI_CpiWrite( &cecFrame );
		}
		
		l_cecTaskState.cpiState = CPI_WAIT_ACK;		
    }
    else if ( l_cecTaskState.cpiState == CPI_WAIT_ACK )
    {
        if ( pCecStatus->txState == SI_TX_SENDFAILED )
        {
            l_cecTaskState.cpiState = CPI_IDLE;
			if (l_cecTaskState.taskData1 == 0)
			{
				newTask = SI_CECTASK_ONETOUCHPLAY;	// retry once
				l_cecTaskState.taskData1 = 1;
			}
			else
			{
				newTask = SI_CECTASK_IDLE;	//fail
				printf("CEC:: One Touch Play fail!\n");
			}
        }
        else if ( pCecStatus->txState == SI_TX_SENDACKED )
        {
            l_cecTaskState.cpiState = CPI_IDLE;
			l_cecTaskState.taskData1 = 0;
			l_cecTaskState.taskData2 ++;
			
			if(l_cecTaskState.taskData2 <= 2)
				newTask = SI_CECTASK_ONETOUCHPLAY;	// next step
			else
				newTask = SI_CECTASK_IDLE;	// done
        }
    }
//	printf("CecTaskOneTouchPlay task returning [%d]\n",(int)newTask);
    return( newTask );
}



//------------------------------------------------------------------------------
// Function:    ValidateCecMessage
// Description: Validate parameter count of passed CEC message
//              Returns FALSE if not enough operands for the message
//              Returns TRUE if the correct amount or more of operands (if more
//              the message processor willl just ignore them).
//------------------------------------------------------------------------------

static bool_si ValidateCecMessage ( SI_CpiData_t *pCpi )
{
    uint8_si parameterCount = 0;
    bool_si    countOK = true;

    /* Determine required parameter count   */

    switch ( pCpi->opcode )
    {
        case CECOP_IMAGE_VIEW_ON:
        case CECOP_TEXT_VIEW_ON:
        case CECOP_STANDBY:
        case CECOP_GIVE_PHYSICAL_ADDRESS:
        case CECOP_GIVE_DEVICE_POWER_STATUS:
        case CECOP_GET_MENU_LANGUAGE:
        case CECOP_GET_CEC_VERSION:
            parameterCount = 0;
            break;
        case CECOP_REPORT_POWER_STATUS:         // power status
        case CECOP_CEC_VERSION:                 // cec version
            parameterCount = 1;
            break;
        case CECOP_INACTIVE_SOURCE:             // physical address
        case CECOP_FEATURE_ABORT:               // feature opcode / abort reason
        case CECOP_ACTIVE_SOURCE:               // physical address
            parameterCount = 2;
            break;
        case CECOP_REPORT_PHYSICAL_ADDRESS:     // physical address / device type
        case CECOP_DEVICE_VENDOR_ID:            // vendor id
            parameterCount = 3;
            break;
        case CECOP_SET_OSD_NAME:                // osd name (1-14 bytes)
        case CECOP_SET_OSD_STRING:              // 1 + x   display control / osd string (1-13 bytes)
            parameterCount = 1;                 // must have a minimum of 1 operands
            break;
        case CECOP_ABORT:
            break;

        case CECOP_ARC_INITIATE:
            break;
        case CECOP_ARC_REPORT_INITIATED:
            break;
        case CECOP_ARC_REPORT_TERMINATED:
            break;

        case CECOP_ARC_REQUEST_INITIATION:
            break;
        case CECOP_ARC_REQUEST_TERMINATION:
            break;
        case CECOP_ARC_TERMINATE:
            break;
        default:
            break;
    }

    /* Test for correct parameter count.    */

    if ( pCpi->argCount < parameterCount )
    {
        countOK = false;
    }

    return( countOK );
}


static bool_si CectoRcpHandler(SI_CpiData_t *pCpi)
{
	bool_si msgHandled = false;
	bool_si isDirectAddressed;
	static uint8_si last_command = 0;
    	uint8_si cec_int_status_reg[2];

	// For losing Rx MSG issue, to clear Tx interrupt
    	SiIRegioModify( REG_CEC_DEBUG_3, BIT_FLUSH_TX_FIFO, BIT_FLUSH_TX_FIFO );  // Clear Tx Buffer
  
    	cec_int_status_reg[0] = 0x64 ; // Clear Tx Transmit Buffer Full Bit, Tx msg Sent Event Bit, and Tx FIFO Empty Event Bit
    	cec_int_status_reg[1] = 0x02 ; // Clear Tx Frame Retranmit Count Exceeded Bit.
    	SiIRegioWriteBlock( REG_CEC_INT_STATUS_0, cec_int_status_reg, 2 );
	
    	isDirectAddressed = !((pCpi->srcDestAddr & 0x0F ) == CEC_LOGADDR_UNREGORBC );

    	if ( isDirectAddressed )
	{
		// Is this a User control command?
		if ( pCpi->opcode == CECOP_USER_CONTROL_PRESSED )
		{
			cbus_out_queue_t req;
			uint8_si channel;
			bool_si ignore_check;

			channel = SI_CbusPortToChannel(l_portSelect);
			ignore_check = SI_CbusKeyIDCheck(channel, pCpi->args[0], CBUS_OUT);

			if (ignore_check)
			{
				if (pCpi->args[0] == CEC_RC_POWER)
				{
					static bool_si power_status = true;
					uint8_si keycode;

					if (power_status)
						keycode = MHL_RAP_CMD_CONTENT_ON;
					else
						keycode = MHL_RAP_CMD_CONTENT_OFF;

					power_status = !power_status;
					
					req.command = MSC_MSG;
					req.msgData[0] = MHL_MSC_MSG_RAP;
					req.msgData[1] = keycode;
					req.cecReq = true;
					req.retry = 1;

					SI_CbusPushReqInOQ(channel, &req, false);
				}
				else
                			CecSendFeatureAbort( pCpi, CECAR_REFUSED);
			}
			else
			{
				//DEBUG_PRINT(MSG_DBG, ("Converting incoming CEC command to RCP message\n"));
				req.command = MSC_MSG;
				req.msgData[0] = MHL_MSC_MSG_RCP;
				req.msgData[1] = pCpi->args[0];
				req.cecReq = true;
				req.retry = 0;


				SI_CbusPushReqInOQ(channel, &req, false);

				//DEBUG_PRINT(MSG_DBG, ("Sending RCP message --> Key ID: %02X\n", (int)req.msgData[1]));
			}
			
			msgHandled = true;
			last_command = pCpi->args[0];
		}
		else if ( pCpi->opcode == CECOP_USER_CONTROL_RELEASED )
		{
			cbus_out_queue_t req;
			uint8_si channel;
			bool_si ignore_check;

			channel = SI_CbusPortToChannel(l_portSelect);
			ignore_check = SI_CbusKeyIDCheck(channel, last_command, CBUS_OUT);
			
			if(ignore_check)
			{
				if (last_command != CEC_RC_POWER)
                		CecSendFeatureAbort( pCpi, CECAR_REFUSED);
			}
			else
			{
				//DEBUG_PRINT(MSG_DBG, ("Converting incoming CEC command to RCP message\n"));
				req.command = MSC_MSG;
				req.msgData[0] = MHL_MSC_MSG_RCP;
				req.msgData[1] = 0x80|last_command;
				req.cecReq = true;
				req.retry = 0;
				channel = SI_CbusPortToChannel(l_portSelect);

				SI_CbusPushReqInOQ(channel, &req, false);

				//DEBUG_PRINT(MSG_DBG, ("Sending RCP message --> Key ID: %02X\n", (int)req.msgData[1]));

			}
			
			msgHandled = true;
		}
	}

	return (msgHandled);
	
}



//------------------------------------------------------------------------------
// Function:    si_CecRxMsgHandlerLast
// Description: This is the last message handler called in the chain, and
//              parses any messages left untouched by the previous handlers.
//------------------------------------------------------------------------------

static bool_si si_CecRxMsgHandlerLast ( SI_CpiData_t *pCpi )
{
    bool_si            isDirectAddressed;
    SI_CpiData_t    cecFrame;

    isDirectAddressed = !((pCpi->srcDestAddr & 0x0F ) == CEC_LOGADDR_UNREGORBC );

    if ( ValidateCecMessage( pCpi ))            // If invalid message, ignore it, but treat it as handled 
    {
        if ( isDirectAddressed )
        {
            switch ( pCpi->opcode )
            {
				case CECOP_USER_CONTROL_PRESSED:
				case CECOP_USER_CONTROL_RELEASED:
					CectoRcpHandler( pCpi );
					break;
					
                case CECOP_STANDBY:             // Direct and Broadcast

                        /* Setting this here will let the main task know    */
                        /* (via SI_CecGetPowerState) and at the same time   */
                        /* prevent us from broadcasting a STANDBY message   */
                        /* of our own when the main task responds by        */
                        /* calling SI_CecSetPowerState( STANDBY );          */

                    l_powerStatus = CEC_POWERSTATUS_STANDBY;
                    break;

                case CECOP_GIVE_PHYSICAL_ADDRESS:

                    cecFrame.opcode        = CECOP_REPORT_PHYSICAL_ADDRESS;
                    cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_UNREGORBC );
                    cecFrame.args[0]       = g_cecPhysical >> 8;             		// [Physical Address] high byte
                    cecFrame.args[1]       = (uint8_si)(g_cecPhysical & 0x00FF);     // [Physical Address] low byte
                    cecFrame.args[2]       = (uint8_si)g_cecAddress;   
                    cecFrame.argCount      = 3;
                    SI_CpiWrite( &cecFrame );
                    break;

                case CECOP_GIVE_DEVICE_POWER_STATUS:

                    /* TV responds with power status.   */

                    cecFrame.opcode        = CECOP_REPORT_POWER_STATUS;
                    cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, (pCpi->srcDestAddr & 0xF0) >> 4 );
                    cecFrame.args[0]       = l_powerStatus;
                    cecFrame.argCount      = 1;
                    SI_CpiWrite( &cecFrame );
                    break;

                case CECOP_GET_MENU_LANGUAGE:

                    /* TV Responds with a Set Menu language command.    */

                    cecFrame.opcode         = CECOP_SET_MENU_LANGUAGE;
                    cecFrame.srcDestAddr    = CEC_LOGADDR_UNREGORBC;
                    cecFrame.args[0]        = 'e';     // [language code see iso/fdis 639-2]
                    cecFrame.args[1]        = 'n';     // [language code see iso/fdis 639-2]
                    cecFrame.args[2]        = 'g';     // [language code see iso/fdis 639-2]
                    cecFrame.argCount       = 3;
                    SI_CpiWrite( &cecFrame );
                    break;

                case CECOP_GET_CEC_VERSION:

                    /* TV responds to this request with it's CEC version support.   */

                    cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, (pCpi->srcDestAddr & 0xF0) >> 4 );
                    cecFrame.opcode        = CECOP_CEC_VERSION;
                    cecFrame.args[0]       = 0x04;       // Report CEC1.3a
                    cecFrame.argCount      = 1;
                    SI_CpiWrite( &cecFrame );
                    break;
//RG additions (DIRECTLY ADDRESS)
					
				case CECOP_GIVE_OSD_NAME:

                    /* Respond to TV with OSD name   */
					printf("RG recieved GIVE OSD NAME\n");

                    cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, (pCpi->srcDestAddr & 0xF0) >> 4 );
                    cecFrame.opcode        = CECOP_SET_OSD_NAME;
				    cecFrame.args[0] = 0x4D; //M
		            cecFrame.args[1] = 0x48; //H
		            cecFrame.args[2] = 0x4C; //L
					cecFrame.args[3] = 0x20; //space
		            cecFrame.args[4] = 0x44; //D
		            cecFrame.args[5] = 0x65; //e
					cecFrame.args[6] = 0x76; //v
		            cecFrame.args[7] = 0x69; //i
		            cecFrame.args[8] = 0x63; //c
					cecFrame.args[9] = 0x65; //e
					cecFrame.argCount = 10;
                    SI_CpiWrite( &cecFrame );

							HalTimerWait(50);
                    break;
//TODO add play etc

//END OF RG ADDITIONS

				case CECOP_MENU_REQUEST:
                    cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_TV );
                    cecFrame.opcode        = CECOP_MENU_STATUS;
                    cecFrame.args[0]       = 0x0;       // Status Activitied
                    cecFrame.argCount      = 1;
                    SI_CpiWrite( &cecFrame );
					break;

				case CECOP_FEATURE_ABORT:
					CecHandleFeatureAbort( pCpi );
					break;
                /* Do not reply to directly addressed 'Broadcast' msgs.  */

                case CECOP_ACTIVE_SOURCE:
                case CECOP_REPORT_PHYSICAL_ADDRESS:     // A physical address was broadcast -- ignore it.
                case CECOP_ROUTING_CHANGE:              // We are not a downstream switch, so ignore this one.
                case CECOP_ROUTING_INFORMATION:         // We are not a downstream switch, so ignore this one.
                case CECOP_DEVICE_VENDOR_ID:
                case CECOP_ABORT:       				// Send Feature Abort for all unsupported features.
                case CECOP_IMAGE_VIEW_ON:       		// In our case, respond the same to both these messages
                case CECOP_TEXT_VIEW_ON:
                default:

                    CecSendFeatureAbort( pCpi, CECAR_UNRECOG_OPCODE );
                    break;
            }
        }

        /* Respond to broadcast messages.   */

        else
        {
            switch ( pCpi->opcode )
            {
                case CECOP_STANDBY:

                        /* Setting this here will let the main task know    */
                        /* (via SI_CecGetPowerState) and at the same time   */
                        /* prevent us from broadcasting a STANDBY message   */
                        /* of our own when the main task responds by        */
                        /* calling SI_CecSetPowerState( STANDBY );          */

                    l_powerStatus = CEC_POWERSTATUS_STANDBY;
                    break;

                /* Do not reply to 'Broadcast' msgs that we don't need.  */

                case CECOP_ROUTING_CHANGE:              // We are not a downstream switch, so ignore this one.
                case CECOP_ROUTING_INFORMATION:         // We are not a downstream switch, so ignore this one.
                    break;
				case  CECOP_SET_STREAM_PATH:

					/* Respond to TV with Active source   */

					printf("RG recieved SET STREAM PATH\n");

					cecFrame.opcode        = CECOP_ACTIVE_SOURCE;
			        cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, CEC_LOGADDR_UNREGORBC);
			        cecFrame.args[0]       = g_cecPhysical >> 8;             		// [Physical Address] high byte
			        cecFrame.args[1]       = (uint8_si)(g_cecPhysical & 0x00FF);     // [Physical Address] low byte
			        cecFrame.argCount      = 2;
			        SI_CpiWrite( &cecFrame );

				break;

            }
        }
    }

    return( true );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// All public API functions are below
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function:    si_CecSendMessage
// Description: Send a single byte (no parameter) message on the CEC bus.  Does
//              no wait for a reply.
//------------------------------------------------------------------------------

void si_CecSendMessage ( uint8_si opCode, uint8_si dest )
{
    SI_CpiData_t cecFrame;

    cecFrame.opcode        = opCode;
    cecFrame.srcDestAddr   = MAKE_SRCDEST( g_cecAddress, dest );
    cecFrame.argCount      = 0;
    SI_CpiWrite( &cecFrame );
}

//------------------------------------------------------------------------------
// Function:    SI_CecSendUserControlPressed
// Description: Send a remote control key pressed command to the
//              current active source.
//------------------------------------------------------------------------------

void SI_CecSendUserControlPressed ( uint8_si keyCode )
{
    if ( !l_cecEnabled )
        return;

    if ( l_activeSrcLogical != CEC_LOGADDR_UNREGORBC )
    {
        CecSendUserControlPressed( keyCode,  CEC_LOGADDR_TV);
    }
}

//------------------------------------------------------------------------------
// Function:    SI_CecSendUserControlReleased
// Description: Send a remote control key released command to the
//              current active source.
//------------------------------------------------------------------------------

void SI_CecSendUserControlReleased ( void )
{
    if ( !l_cecEnabled )
        return;

    if ( l_activeSrcLogical != CEC_LOGADDR_UNREGORBC )
    {
        si_CecSendMessage( CECOP_USER_CONTROL_RELEASED, CEC_LOGADDR_TV );
    }
}

//------------------------------------------------------------------------------
// Function:    SI_CecGetPowerState
// Description: Returns the CEC local power state.
//              Should be called after every call to SI_CecHandler since
//              a CEC device may have issued a standby or view message.
//
// Valid values:    CEC_POWERSTATUS_ON
//                  CEC_POWERSTATUS_STANDBY
//                  CEC_POWERSTATUS_STANDBY_TO_ON
//                  CEC_POWERSTATUS_ON_TO_STANDBY
//------------------------------------------------------------------------------

uint8_si SI_CecGetPowerState ( void )
{

    return( l_powerStatus );
}

//------------------------------------------------------------------------------
// Function:    SI_CecSetPowerState
// Description: Set the CEC local power state.
//
// Valid values:    CEC_POWERSTATUS_ON
//                  CEC_POWERSTATUS_STANDBY
//                  CEC_POWERSTATUS_STANDBY_TO_ON
//                  CEC_POWERSTATUS_ON_TO_STANDBY
//------------------------------------------------------------------------------

void SI_CecSetPowerState ( uint8_si newPowerState )
{
    if ( !l_cecEnabled )
        return;

    if ( l_powerStatus != newPowerState )
    {
        switch ( newPowerState )
        {
            case CEC_POWERSTATUS_ON:

                /* Find out who is the active source. Let the   */
                /* ACTIVE_SOURCE handler do the rest.           */

                si_CecSendMessage( CECOP_REQUEST_ACTIVE_SOURCE, CEC_LOGADDR_UNREGORBC );
                break;

            case CEC_POWERSTATUS_STANDBY:

                /* If we are shutting down, tell every one else to also.   */

                si_CecSendMessage( CECOP_STANDBY, CEC_LOGADDR_UNREGORBC );
                break;

            case CEC_POWERSTATUS_STANDBY_TO_ON:
            case CEC_POWERSTATUS_ON_TO_STANDBY:
            default:
                break;
        }

    l_powerStatus = newPowerState;
    }
}

//------------------------------------------------------------------------------
// Function:    SI_CecSourceRemoved
// Description: The hardware detected an HDMI connector removal, so clear the
//              position in our device list.
//
// TODO:    The source that was removed may or may not have had time to send out
//          an INACTIVE_SOURCE message, so we may want to emulate that action.
//
//------------------------------------------------------------------------------

void SI_CecSourceRemoved ( uint8_si portIndex )
{
    if ( !l_cecEnabled )
        return;
#if 0
    DEBUG_PRINT(
        MSG_DBG,
        ( "CEC Source removed: Port: %d, LA:%02X \n",
        (int)portIndex, (int)g_childPortList[ portIndex].cecLA
        ));
#endif
#if API_DEBUG_CODE
	printf( "CEC Source removed: Port: %d, LA:%02X \n",
        (int)portIndex, (int)g_childPortList[ portIndex].cecLA
        );
#endif
}

//------------------------------------------------------------------------------
// Function:    SI_CecGetDevicePA
// Description: Return the physical address for this Host device
//
//------------------------------------------------------------------------------

uint16_si SI_CecGetDevicePA ( void )
{
    return( g_cecPhysical );
}

//------------------------------------------------------------------------------
// Function:    SI_CecSetDevicePA
// Description: Set the host device physical address (initiator physical address)
//------------------------------------------------------------------------------

void SI_CecSetDevicePA ( uint16_si devPa )
{
    g_cecPhysical = devPa;
    //DEBUG_PRINT( MSG_STAT, ("\nDevice PA [%04X]\n", (int)devPa ));
    #if API_DEBUG_CODE
	printf( "\nDevice PA [%04X]\n", (int)devPa);
    #endif
}

//------------------------------------------------------------------------------
// Function:    SI_CecInit
// Description: Initialize the CEC subsystem.
//------------------------------------------------------------------------------

bool_si SI_CecInit ( void )
{
    SI_CpiInit();

    l_cecEnabled = true;
    return( true );
}

//------------------------------------------------------------------------------
// Function:    si_TaskServer
// Description: Calls the current task handler.  A task is used to handle cases
//              where we must send and receive a specific set of CEC commands.
//------------------------------------------------------------------------------

static void si_TaskServer ( SI_CpiStatus_t *pCecStatus )
{
	static uint8_si prevTask = 0;

   	if(g_currentTask != prevTask)
	{
    	printf("current task = [%d] prev task = [%d]\n",(int)g_currentTask,(int)prevTask);
	    prevTask = g_currentTask;
	}

	//RG enable processing of incomming CEC messages
//	if((prevTask == 4) &&  (g_currentTask == 0))


	switch ( g_currentTask )
    {
        case SI_CECTASK_IDLE:
            if ( l_newTask )
            {
                /* New task; copy the queued task block into the operating task block.  */

                memcpy( &l_cecTaskState, &l_cecTaskStateQueued, sizeof( CEC_TASKSTATE ));
                l_newTask = false;
                g_currentTask = l_cecTaskState.task;
            }
            break;

        case SI_CECTASK_ENUMERATE:
            g_currentTask = CecTaskEnumerate( pCecStatus );
            break;
        case SI_CECTASK_TXREPORT:
            g_currentTask = CecTaskTxReport( pCecStatus );
            break;
		case SI_CECTASK_SETOSDNAME:
			g_currentTask = CecTaskSetOSDName( pCecStatus );
			break;
        case SI_CECTASK_ONETOUCHPLAY:
            g_currentTask = CecTaskOneTouchPlay( pCecStatus );
            break;

        default:
            break;
    }

}

//------------------------------------------------------------------------------
// Function:    SI_CecEnumerate
// Description: Send the appropriate CEC commands to enumerate all the logical
//              devices on the CEC bus.
//------------------------------------------------------------------------------

bool_si SI_CecEnumerate ( void )
{
    bool_si            success = false;

    /* If the task handler queue is not full, add the enumerate task.   */

    if ( !l_newTask )
    {
        l_cecTaskStateQueued.task       = SI_CECTASK_ENUMERATE;
        l_cecTaskStateQueued.state      = 0;
        l_cecTaskStateQueued.destLA     = 0;
        l_cecTaskStateQueued.cpiState   = CPI_IDLE;
        l_cecTaskStateQueued.taskData1  = 0;
        l_cecTaskStateQueued.taskData2  = 0;
        l_newTask   = true;
        success     = true;
    }

    return( success );
}


//------------------------------------------------------------------------------
// Function:    SI_CecTxReport
// Description: Send the appropriate CEC commands to report Physical Address
//
//------------------------------------------------------------------------------

bool_si SI_CecTxReport ( void )
{
    bool_si            success = false;

    /* If the task handler queue is not full, add the enumerate task.   */

    if ( !l_newTask )
    {
        l_cecTaskStateQueued.task       = SI_CECTASK_TXREPORT;
        l_cecTaskStateQueued.state      = 0;
        l_cecTaskStateQueued.destLA     = 0;
        l_cecTaskStateQueued.cpiState   = CPI_IDLE;
        l_cecTaskStateQueued.taskData1  = 0;
        l_cecTaskStateQueued.taskData2  = 0;
        l_newTask   = true;
        success     = true;
    }

    return( success );
}

//------------------------------------------------------------------------------
// Function:    SI_CecSetOsdName
// Description: Send the appropriate CEC commands to report Physical Address
//
//------------------------------------------------------------------------------

bool_si SI_CecSetOsdName ( void )
{
    bool_si            success = false;

    /* If the task handler queue is not full, add the enumerate task.   */

    if ( !l_newTask )
    {
        l_cecTaskStateQueued.task       = SI_CECTASK_SETOSDNAME;
        l_cecTaskStateQueued.state      = 0;
        l_cecTaskStateQueued.destLA     = 0;
        l_cecTaskStateQueued.cpiState   = CPI_IDLE;
        l_cecTaskStateQueued.taskData1  = 0;
        l_cecTaskStateQueued.taskData2  = 0;
        l_newTask   = true;
        success     = true;
    }

    return( success );
}



//------------------------------------------------------------------------------
// Function:    SI_CecOneTouchPlay
// Description: Send the appropriate CEC commands to report Physical Address
//
//------------------------------------------------------------------------------

bool_si SI_CecOneTouchPlay ( void )
{
    bool_si            success = false;

    /* If the task handler queue is not full, add the enumerate task.   */

    if ( !l_newTask )
    {
        l_cecTaskStateQueued.task       = SI_CECTASK_ONETOUCHPLAY;
        l_cecTaskStateQueued.state      = 0;
        l_cecTaskStateQueued.destLA     = 0;
        l_cecTaskStateQueued.cpiState   = CPI_IDLE;
        l_cecTaskStateQueued.taskData1  = 0;
        l_cecTaskStateQueued.taskData2  = 0;
        l_newTask   = true;
        success     = true;
    }

    return( success );
}


uint8_si SI_CecMscMsgConvertHandler(SI_CpiData_t *pCpi, uint8_si channel)
{
	uint8_si result = SUCCESS;
	
	SI_CpiWrite(pCpi);
	l_cbusRequestChannel = channel;
	l_featureAbortTimer = DEM_CEC_FEATURE_ABORT_MAX_DELAY;
	HalTimerSet(TIMER_DEM_CEC_FEATURE_ABORT_MAX_DELAY,500); 
	return (result);
}



//------------------------------------------------------------------------------
// Function:    SI_CecHandler
// Description: Polls the send/receive state of the CPI hardware and runs the
//              current task, if any.
//
//              A task is used to handle cases where we must send and receive
//              a specific set of CEC commands.
//------------------------------------------------------------------------------

uint8_si SI_CecHandler ( uint8_si currentPort, bool_si returnTask )
{
    bool_si cdcCalled  = false;
    SI_CpiStatus_t  cecStatus;
	static bool_si TV_connected = false;
	static bool_si MHL_connected = false;
	static uint8_si start_con = 0;
	static uint8_si start_con_prev = 0;
	static bool_si timer_set = false;
	static uint32_si count;


//	si_TaskServer( &cecStatus );
//	SI_CpiStatus( &cecStatus );


//TODO the issue is we gate entering this function based on whether g_mhl_connected is true, but if it is true the
//status will not be updated within this function therefore we will not start our discovery state machine again
//need to implemente a mechanism to tell this function whether it needs to perform a re-start or not.



	if(start_con != start_con_prev)
	{
		printf("START CON = 0x%d\n",(int)start_con);
		start_con_prev = start_con;
	}
//	printf("TV_c = [%d] gHDP = [%d] MHL_c = [%d] gMHL = [%d]\n",(int)TV_connected, (int) g_HPD_IN, (int) MHL_connected, (int) g_MHL_Source_Connected);
	// Check whether the TV is connected
	if (( TV_connected != g_HPD_IN ) || (MHL_connected != g_MHL_Source_Connected))
	{
		TV_connected = g_HPD_IN;
		MHL_connected = g_MHL_Source_Connected;

		if ( (TV_connected == true) && (g_MHL_Source_Connected == true))
		{
			//RG clear any pending tasks
			start_con = 1;
			g_currentTask       = SI_CECTASK_IDLE;
			l_newTask			= false;
	//		SiIRegioModify( REG_CEC_DEBUG_3,BIT_FLUSH_TX_FIFO, BIT_FLUSH_TX_FIFO );
			printf("START CON = 1\n");
		}
		else
		{
			start_con = 0;
			printf("START CON = 0\n");
		}
	}
	
	if( (TV_connected == true) && (g_MHL_Source_Connected == true))
	{	

		if (start_con == 1)
		{
		    g_cecAddress = CEC_LOGADDR_UNREGORBC;
	
			if(SI_CecEnumerate())
				start_con = 2;
		}
		else if (start_con == 2)
		{
			if(SI_CecTxReport())
				start_con = 3;
		}
		else if (start_con == 3 /*&& g_MHL_Source_Connected*/)
		{
			if(SI_CecOneTouchPlay())
				start_con = 4;
		}
		else if (start_con == 4)
		{
			if(SI_CecSetOsdName())
				start_con = 0;
		}
	  
		if (l_featureAbortTimer != 0)
		{
			if( !timer_set )
			{
				timer_set = true;
				count = timer_count;
				//RG modification to set timer
	//			TIMER_Set(TIMER_DEM_CEC_FEATURE_ABORT_MAX_DELAY,500); 
			}
			else
			{			
	//			if( HalTimerDelay(count, l_featureAbortTimer) )
				if(HalTimerExpired(TIMER_DEM_CEC_FEATURE_ABORT_MAX_DELAY))
				{
	
						SI_CbusCecRetHandler(l_cbusRequestChannel, true);
						l_cbusRequestChannel = 0xFF;
						l_featureAbortTimer = 0;
						count = 0;
						timer_set= false;
					}
			}
		}
	
	    l_portSelect = currentPort;
	
	    /* Get the CEC transceiver status and pass it to the    */
	    /* current task.  The task will send any required       */
	    /* CEC commands.                                        */
	
	    SI_CpiStatus( &cecStatus );
	    si_TaskServer( &cecStatus );
	
	    /* Now look to see if any CEC commands were received.   */
	
	    if ( cecStatus.rxState )
	    {
	        uint8_si         frameCount;
	        SI_CpiData_t    cecFrame;
	
	        /* Get CEC frames until no more are present.    */
	
	        cecStatus.rxState = 0;      // Clear activity flag
			//DEBUG_PRINT( MSG_DBG, ("\nREG_CEC_RX_COUNT %02x\n", (int)SiIRegioRead( REG_CEC_RX_COUNT) ));
			
			while ((frameCount = ((SiIRegioRead( REG_CEC_RX_COUNT) & 0xF0) >> 4))>0)
	        {
	            printf("\n%d frames in Rx Fifo\n", (int)frameCount );
				//RG addidtion wait for start_con == 0 before responging to messages
				
		            if ( SI_CpiRead( &cecFrame ))
		            {
		                printf( "Error in Rx Fifo \n" );
		                break;
		            }
		
		            /* Send the frame through the RX message Handler chain. */
				if(( start_con == 0))
				{
		            for (;;)
		            {
		                if ( CpCecRxMsgHandler( &cecFrame ))        // Let the end-user app have a shot at it.
		                    break;
		                si_CecRxMsgHandlerLast( &cecFrame );        // We get a chance at it afer the end user App to cleanup
		                break;
		            }
		        }
			}
	    }
	
	    if ( l_portSelect != currentPort )
	    {
	        printf("\nNew port value returned: %02X (Return Task: %d)\n", (int)l_portSelect, (int)returnTask );
	    }
    	return( returnTask ? g_currentTask : l_portSelect );
	}
	return true;
}
#endif
