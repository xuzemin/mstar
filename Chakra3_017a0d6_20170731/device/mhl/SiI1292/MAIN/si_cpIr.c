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
//!file     si_cpIr.c
//!brief    CP 9387 Starter Kit top level IR Remote command parser.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2008-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include <string.h>

#include "./SiI1292/MAIN/si_cp1292.h"
#include "CEC/si_apiCpi.h"
#include "./SiI1292/CEC/si_apiCEC.h"
#include "./SiI1292/API/si_regio.h"
#include "./SiI1292/MAIN/si_cpCEC.h"
#include "./SiI1292/CEC/si_cec_enums.h"
#include "./SiI1292/CBUS/si_apiCbus.h"
#include "./SiI1292/MSC/si_apiRCP.h"
#include "./SiI1292/HAL/INC/si_hal.h"


#if (IS_IR == 1)

static bool_si   l_returnRC5 = false;


//------------------------------------------------------------------------------
// Module data
//------------------------------------------------------------------------------


typedef struct
{
    uint8_si timer;  //!< UI event type
    uint8_si command;    //!< UI command
} Irlast_t;

Irlast_t irlast = {0,0};

#if IS_CP_Remote_Controller
//typedef enum
enum
{
    RC5_0,
    RC5_1,
    RC5_2,
    RC5_3,
    RC5_4,
    RC5_5,
    RC5_6,
    RC5_7,
    RC5_8,
    RC5_9,
    RC5_STANDBY        = 0x0C,     //
    RC5_MUTE_OK        = 0x0D,     // 
    RC5_QUIT         	= 0x0F,
    RC5_VOL_UP          	= 0x10,     //
    RC5_VOL_DOWN     	= 0x11,     //
    RC5_ENTER		= 0x1a,
    RC5_PRG_UP          	= 0x20,     //
    RC5_PRG_DOWN     = 0x21,     //

    RC5__PAUSE          	= 0x29,     // Device 5
    RC5_UP			= 0x1c,
    RC5_DOWN		= 0x1d,
    RC5_RIGHT		= 0x2b,
    RC5_LEFT			= 0x2c,
    RC5_MENU		= 0x2e,
    RC5_FAST_REW      = 0x32,     // Device 5
    RC5_FAST_FWD     	= 0x34,     // Device 5
    RC5_PLAY            	= 0x35,     // Device 5
    RC5_STOP            	= 0x36,     // Device 5
    RC5_REC             	= 0x37,     // Device 5

    RC5__INPUT          	= 0x38,     // Device 5
    RC5__TV_VCR         = 0x3E,     // Device 5
};
#endif
#if IS_RK_Remote_Controller
//typedef enum
enum
{
    RC5_0			= 0x0b,
    RC5_1			= 0x02,
    RC5_2			= 0x05,
    RC5_3			= 0x06,
    RC5_4			= 0x00,
    RC5_5			= 0x01,
    RC5_6			= 0x03,
    RC5_7			= 0x09,
    RC5_8			= 0x0C,
    RC5_9			= 0x0F,
    RC5_STANDBY        = 0x04,     //
    RC5_MUTE_OK        = 0x07,     // 
    RC5_QUIT         	= 0x1F,
    RC5_VOL_UP          	= 0x0a,     //
    RC5_VOL_DOWN    	= 0x12,     //
    RC5_ENTER		= 0x1d,
    RC5_PRG_UP          	= 0x0d,     //
    RC5_PRG_DOWN    	= 0x17,     //

    RC5__PAUSE          	= 0x1a,     // Device 5
    RC5_UP			= 0x14,
    RC5_DOWN		= 0x1e,
    RC5_RIGHT		= 0x16,
    RC5_LEFT			= 0x11,
    RC5_MENU		= 0x19,
    RC5_FAST_REW     	= 0x23,     // Device 5
    RC5_FAST_FWD     	= 0x26,     // Device 5
    RC5_PLAY            	= 0x18,     // Device 5
    RC5_STOP            	= 0x1c,     // Device 5
    RC5_REC             	= 0x1b,     // Device 5

    RC5__INPUT          	= 0x2d,     // Device 5
    RC5__TV_VCR         = 0xFE,     //unknow keycode
};
#endif

const UiRc5Conversion_t uiRc5ConvTable[] =
{
        // Device 0/5 (whichever is selected)
		//RC=RC key code	CEC_RC=CEC or RCP key code

    { RC5_0,        CEC_RC_0      },
    { RC5_1,        CEC_RC_1      },
    { RC5_2,        CEC_RC_2      },
    { RC5_3,        CEC_RC_3      },
    { RC5_4,        CEC_RC_4      },
    { RC5_5,        CEC_RC_5      },
    { RC5_6,        CEC_RC_6      },
    { RC5_7,        CEC_RC_7      },
    { RC5_8,        CEC_RC_8      },
    { RC5_9,        CEC_RC_9      },
    { RC5_STANDBY,  CEC_RC_POWER  },

        // Device 0

    { RC5_MUTE_OK,  CEC_RC_MUTE   },
    { RC5_QUIT,  CEC_RC_EXIT},
    { RC5_VOL_UP,   CEC_RC_VOLUME_UP  },
    { RC5_VOL_DOWN, CEC_RC_VOLUME_DOWN  },
    {RC5_ENTER,	CEC_RC_SELECT},
    { RC5_PRG_UP,   CEC_RC_CHANNEL_UP   },        // Device 5 Chapter ->
    { RC5_PRG_DOWN, CEC_RC_CHANNEL_DOWN   },      // Device 5 Chapter <-

    {RC5_UP,	CEC_RC_UP},
    {RC5_DOWN,	CEC_RC_DOWN},
    {RC5_RIGHT,	CEC_RC_RIGHT},
    {RC5_LEFT,	CEC_RC_LEFT},
    {RC5_MENU,	CEC_RC_ROOT_MENU},

      // device 5

    { RC5_FAST_REW, CEC_RC_REWIND    },
    { RC5_FAST_FWD, CEC_RC_FAST_FORWARD    },
    { RC5_PLAY,     CEC_RC_PLAY   },
    { RC5_STOP,     CEC_RC_STOP   },
    { RC5_REC,      CEC_RC_RECORD    },

    { RC5__PAUSE,   CEC_RC_PAUSE            },
    { RC5__INPUT,   CEC_RC_INPUT_SELECT     },  // Device 0
    { RC5__TV_VCR,  CEC_RC_INPUT_SELECT     },  // Device 5
};


const UiRC5CommandMap_t irCommandMap =
{
    0xFF,                   // RC5 device address
    ( sizeof( uiRc5ConvTable ) / sizeof(UiRc5Conversion_t) ),
    uiRc5ConvTable
};



//------------------------------------------------------------------------------
// Function:    IrCecKeys 
// Description: Parse CEC keys
//------------------------------------------------------------------------------

static bool_si IrCecKeys ( uint8_si key, uint8_si eventType )
{
    bool_si  usedKey = false;

#if (IS_CEC == 1)

    //if ( !g_data.rcSupport & RC_CEC_SUPPORT )
      //  return( false );

    if ( eventType == KEY_UP )
    {
        /* Send a key up command for every key we sent a key down command.  */

        switch( key )
        {
            case CEC_RC_MUTE:
            case CEC_RC_VOLUME_UP:
            case CEC_RC_VOLUME_DOWN:
            case CEC_RC_CHANNEL_UP:
            case CEC_RC_CHANNEL_DOWN:
            case CEC_RC_PAUSE:
            case CEC_RC_REWIND:
            case CEC_RC_FAST_FORWARD:
            case CEC_RC_PLAY:
            case CEC_RC_STOP:
            case CEC_RC_RECORD:
            case CEC_RC_ENTER:
#if IS_CEC
                if ( g_data.cecEnabled )
                {
                    SI_CecSendUserControlReleased();
                }
#endif
                usedKey = true;
                break;
        }
    }
    else if ( eventType == KEY_DOWN )
    {
        switch( key )
        {
            case CEC_RC_1:              
            case CEC_RC_2:
            case CEC_RC_3:
            case CEC_RC_4:                
            case CEC_RC_5:
                g_data.portSelect = key - CEC_RC_1;
                usedKey = true;
                break;

            case CEC_RC_0:
            case CEC_RC_6:
            case CEC_RC_7:
            case CEC_RC_8:
            case CEC_RC_9:
                usedKey = true;
                break;

            case CEC_RC_POWER:

               // DEBUG_PRINT( MSG_STAT,( "Remote Control Power Key Pressed!\n" ));     // Used for RC code selection
               #if API_DEBUG_CODE
			printf("Remote Control Power Key Pressed!\n");
    		#endif
                if ( SI_CecGetPowerState() == CEC_POWERSTATUS_ON )
                {
                    SI_CecSetPowerState( CEC_POWERSTATUS_STANDBY );
                }
                else
                {
                    SI_CecSetPowerState( CEC_POWERSTATUS_ON );
                }
                usedKey = true;
                break;

            case CEC_RC_MUTE:
            case CEC_RC_VOLUME_UP:
            case CEC_RC_VOLUME_DOWN:
            case CEC_RC_CHANNEL_UP:
            case CEC_RC_CHANNEL_DOWN:
            case CEC_RC_PAUSE:
            case CEC_RC_REWIND:
            case CEC_RC_FAST_FORWARD:
            case CEC_RC_PLAY:
            case CEC_RC_STOP:
            case CEC_RC_RECORD:
            case CEC_RC_ENTER:
                usedKey = true;
                // ---------------- Fall through to CEC_RC_INPUT_SELECT ---------------- 
            case CEC_RC_INPUT_SELECT:   // Don't mark as used
               // DEBUG_PRINT( MSG_DBG, ( "CEC: KeyCode: %02X\n", (int)key ));
		#if API_DEBUG_CODE
			printf("CEC: KeyCode: %02X\n", (int)key);
    		#endif
#if IS_CEC			   
                if ( g_data.cecEnabled )
                {
                    SI_CecSendUserControlPressed( key );
                }
#endif
                break;
        }
    }
#else
    key = key;
    eventType = eventType;
    // keyDown = eventType;
#endif

    return( usedKey );
}

//------------------------------------------------------------------------------
// Function:    IrKeys 
// Description: Parse standard keys
//------------------------------------------------------------------------------

static bool_si IrKeys ( uint8_si keyDown )
{
    bool_si  usedKey = false;

    switch( keyDown )
    {
        case CEC_RC_1:              
        case CEC_RC_2:
        case CEC_RC_3:
        case CEC_RC_4:                
        case CEC_RC_5:
            g_data.portSelect = keyDown - CEC_RC_1;
            usedKey = true;
            break;

        case CEC_RC_0:
        case CEC_RC_6:
        case CEC_RC_7:
        case CEC_RC_8:
        case CEC_RC_9:
            usedKey = true;
            break;

        case CEC_RC_POWER:

            //DEBUG_PRINT( MSG_STAT,( "Remote Control Power Key Pressed!\n" ));     // Used for RC code selection
            #if API_DEBUG_CODE
			printf("Remote Control Power Key Pressed!\n");
    		#endif
            usedKey = true;
            break;

        case CEC_RC_INPUT_SELECT:

                /* Select the next available port and let   */
                /* the main loop switch the port.           */

            //g_data.portSelect = SI_PortGetNextPort( g_data.portSelect );
            usedKey = true;
            break;
    }

    return( usedKey );
}









//------------------------------------------------------------------------------
// Function:    CheckCommandMode
// Description: Check incoming keys.  If the command key sequence is followed, 
//              enter command mode and process keys until exit.
// Parameters:  keyCode - last key entered from remote control
// Returns:     true    - Key was used; entered and exited command mode
//              false   - Key was not used
//------------------------------------------------------------------------------

bool_si CpCheckCommandMode ( uint8_si keyCode )
{
    bool_si          result = false;
    static uint8_si  cmdModeKey [4] = { 0x26, 0x29, 0x27, 0x27 };
    static uint8_si  cmdModeIndex = 0;

    if ( l_returnRC5 )
    {
        //DEBUG_PRINT( MSG_DBG, ( "RC5: %02X\n", (int)keyCode ));
        #if API_DEBUG_CODE
			printf("RC5: %02X\n", (int)keyCode );
    	#endif
        keyCode += CEC_RC_0;
        result = true;
    }

    if ( keyCode == cmdModeKey[ cmdModeIndex] )
    {
        cmdModeIndex++;
        if ( cmdModeIndex == sizeof( cmdModeKey ))
        {
            cmdModeIndex = 0;
            //CommandMode();
            HalIRReturnRC5( l_returnRC5 );
            result = true;
        }
    }
    else
        cmdModeIndex = 0;

    return( result );
}


//------------------------------------------------------------------------------
// Function:    CpIrHandler
// Description: Check the IR port for a command and process it if found.
//------------------------------------------------------------------------------

bool_si CpIrHandler ( void )
{
    IrCommand_t  irCommand;

    irCommand = HalGetIRCommand();

	if ( irCommand.eventType == KEY_DOWN )
	{
		if (irlast.command != irCommand.command)
		{
			irlast.command = irCommand.command;
			irlast.timer = 50;//Keno20120302, modification for RC will count 50 for check command changed or not.//original=5
		}
	}	
	else if ( irCommand.eventType == KEY_UP )
    	{
    		irlast.command = 0;
	}
	if (irlast.command)
	{
		if (irlast.timer-- == 0)
		{
			irlast.timer = 5;
			irCommand.eventType = KEY_DOWN;
			irCommand.command = irlast.command;
		}
	}
    	if ( irCommand.eventType == KEY_UP )
    	{
        	/* In CEC demo mode, send a key up command for every key we sent a key down command.  */
		if (g_currentInputMode == MHL)
		{
			SI_IrRcpKeys( irCommand.command, irCommand.eventType );
			g_RC5_Key_UP = true;
		}
		else
        	IrCecKeys( irCommand.command, irCommand.eventType );
    	}

    	else if ( irCommand.eventType == KEY_DOWN )
    	{
        	for ( ;; )
        	{
			if (g_currentInputMode == MHL)
			{
				SI_IrRcpKeys( irCommand.command, irCommand.eventType );
				g_RC5_Key_UP = false;

				break;
			}
			else
			{
				if ( CpCheckCommandMode( irCommand.command ))
                			break;


            			//if ( IrCbusKeys( irCommand.command ))
            			//    break;
            			if ( IrCecKeys( irCommand.command, irCommand.eventType ))
                			break;

            			IrKeys( irCommand.command );    // Always handle last
			        	break;
			}
        	}
    	}
    return( true );
}

#else

bool_si CpIrHandler ( void ) { return( true ); }

const UiRC5CommandMap_t irCommandMap = { 0xFF, 0x00, 0 };

#endif
