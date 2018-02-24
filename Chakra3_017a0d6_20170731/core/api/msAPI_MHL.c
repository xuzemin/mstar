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
///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    msAPI_mhl.c
/// @author MStar Semiconductor Inc.
/// @brief  MHL API Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MSAPI_MHL_C_
#define _MSAPI_MHL_C_

#include "Board.h"


#if (ENABLE_MHL == ENABLE)

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition

#include "msAPI_MHL.h"
#include "MApp_Key.h"
#if (MHL_TYPE == MHL_TYPE_ELAND)
#include "apiMHL.h"
#endif
#if (MHL_TYPE == MHL_TYPE_ELAND)
#include "apiMHL_ELAND.h"
#endif
#include "drvGPIO.h"
#include "MApp_GlobalVar.h"

#include "apiXC.h"

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define msg_mhl_api(x) x

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

typedef struct
{
    U8 u8RCPKeyCode;
    U8 u8IRKeyCode;

} ST_RCP_KEY_TRANSLATE;

ST_RCP_KEY_TRANSLATE const astRCPKeyTranslate[] =
{
    //  Note: except the null IR key, all other IR keys should appear once.

    {RCP_KEYID_SELECT,          KEY_SELECT},
    {RCP_KEYID_UP,              KEY_UP},
    {RCP_KEYID_DOWN,            KEY_DOWN},
    {RCP_KEYID_LEFT,            KEY_LEFT},
    {RCP_KEYID_RIGHT,           KEY_RIGHT},

    //Sink does not support...
    /*
    {RCP_KEYID_RIGHT_UP, },
    {RCP_KEYID_RIGHT_DOWN, },
    {RCP_KEYID_LEFT_UP, },
    {RCP_KEYID_LEFT_DOWN, },
    */

    {RCP_KEYID_ROOT_MENU,       KEY_MENU},

    //Sink does not support...
    /*
    {RCP_KEYID_SETUP_MENU, },
    {RCP_KEYID_CONTENTS_MENU, },
    {RCP_KEYID_FAVORITE_MENU, },
    */

    {RCP_KEYID_EXIT,            KEY_EXIT},
    //0x0E - 0x1F are reserved
    {RCP_KEYID_NUM_0,           KEY_0},
    {RCP_KEYID_NUM_1,           KEY_1},
    {RCP_KEYID_NUM_2,           KEY_2},
    {RCP_KEYID_NUM_3,           KEY_3},
    {RCP_KEYID_NUM_4,           KEY_4},
    {RCP_KEYID_NUM_5,           KEY_5},
    {RCP_KEYID_NUM_6,           KEY_6},
    {RCP_KEYID_NUM_7,           KEY_7},
    {RCP_KEYID_NUM_8,           KEY_8},
    {RCP_KEYID_NUM_9,           KEY_9},

    //Sink does not support...
    /*
    {RCP_KEYID_DOT, },
    */

    {RCP_KEYID_ENTER,           KEY_NULL},
    {RCP_KEYID_CLEAR,           KEY_NULL},
    //0x2D - 0x2F are reserved
    {RCP_KEYID_CH_UP,           KEY_CHANNEL_PLUS},
    {RCP_KEYID_CH_DOWN,         KEY_CHANNEL_MINUS},
    {RCP_KEYID_PRE_CH,          KEY_CHANNEL_RETURN},
    {RCP_KEYID_SOUND_SELECT,    KEY_AUDIO},

    //Sink does not support...
    /*
    {RCP_KEYID_INPUT_SELECT, },
    {RCP_KEYID_SHOW_INFO, },
    {RCP_KEYID_HELP, },
    {RCP_KEYID_PAGE_UP, },
    {RCP_KEYID_PAGE_DOWN, },
    //0x39 - 0x40 are reserved
    {RCP_KEYID_VOL_UP, },
    {RCP_KEYID_VOL_DOWN, },
    {RCP_KEYID_MUTE, },
    */

    {RCP_KEYID_PLAY,            KEY_PLAY},
    {RCP_KEYID_STOP,            KEY_STOP},
    {RCP_KEYID_PAUSE,           KEY_PAUSE},
    {RCP_KEYID_RECORD,          KEY_RECORD},
    {RCP_KEYID_REWIND,          KEY_REWIND},
    {RCP_KEYID_FAST_FWD,        KEY_FF},
    {RCP_KEYID_EJECT,           KEY_NULL},
    {RCP_KEYID_FORWARD,         KEY_NEXT},
    {RCP_KEYID_BACKWARD,        KEY_PREVIOUS},
    //0x4D - 0x4F are reserved

    //Sink does not support...
    /*
    {RCP_KEYID_ANGLE, },
    {RCP_KEYID_SUBPICTURE, },
    */

    //0x52 - 0x5F are reserved
    {RCP_KEYID_PLAY_FUNC,       KEY_NULL},
    {RCP_KEYID_PAUSE_PLAY_FUNC, KEY_NULL},
    {RCP_KEYID_RECORD_FUNC,     KEY_NULL},
    {RCP_KEYID_PAUSE_REC_FUNC,  KEY_NULL},
    {RCP_KEYID_STOP_FUNC,       KEY_NULL},

    //Sink does not support...
    /*
    {RCP_KEYID_MUTE_FUNC, },
    {RCP_KEYID_UN_MUTE_FUNC, },
    {RCP_KEYID_TUNE_FUNC, },
    {RCP_KEYID_MEDIA_FUNC, },
    //0x69 - 0x70 are reserved
    {RCP_KEYID_F1, },
    {RCP_KEYID_F2, },
    {RCP_KEYID_F3, },
    {RCP_KEYID_F4, },
    {RCP_KEYID_F5, },
    //0x76 - 0x7D are reserved
    {RCP_KEYID_VENDOR_SPECIFIC, },
    {RCP_KEYID_RESERVED, }
    */
};

#define LENGTH_TRANSLATION_ARRAY sizeof(astRCPKeyTranslate)/sizeof(ST_RCP_KEY_TRANSLATE)
//const U8 LENGTH_TRANSLATION_ARRAY = sizeof(astRCPKeyTranslate)/sizeof(ST_RCP_KEY_TRANSLATE;

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------



#if ((MHL_TYPE == MHL_TYPE_ELAND) || (MHL_TYPE == MHL_TYPE_SI))
#include "apiSWI2C.h"

#if 0
#define MHL_SWI2C_SCL       PAD_GPIO0
#define MHL_SWI2C_SDA       PAD_GPIO1
#define MHL_SWI2C_SPEED     SWI2C_SPEED_MAPPING_300K//SWI2C_SPEED_MAPPING_100K

#define MHL_IIC_BUS_SYS   MHL_SWI2C_SCL,   MHL_SWI2C_SDA,   MHL_SWI2C_SPEED // EEPROM I2C bus

static SWI2C_BusCfg g_MhlI2CBus[] =
{
    {MHL_IIC_BUS_SYS}
};
#endif
#endif

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

MS_U8 msAPI_MHL_CbusRcpProcess (MS_U8 rcpCode)
{
    MS_U8 statusCode = MSC_RCP_NO_ERROR;

    printf("** Receive RCP Key 0x%x from source\r\n", rcpCode);

    switch(rcpCode)
    {
      #if 0
        case RCP_KEYID_MUTE:
        case RCP_KEYID_MUTE_FUNC:
            //mapi_interface::Get_mapi_mhl()->SI_CecSendUserControlPressed( CEC_RC_MUTE );
            //break;
        case RCP_KEYID_UN_MUTE_FUNC:
            //mapi_interface::Get_mapi_mhl()->SI_CecSendUserControlPressed( CEC_RC_RESTORE_VOLUME_FUNCTION );
            //break;
        case RCP_KEYID_VOL_UP:
            //mapi_interface::Get_mapi_mhl()->SI_CecSendUserControlPressed( CEC_RC_VOLUME_UP );
            //break;
        case RCP_KEYID_VOL_DOWN:
            //mapi_interface::Get_mapi_mhl()->SI_CecSendUserControlPressed( CEC_RC_VOLUME_DOWN );
            break;
       #endif
        case RCP_KEYID_SELECT:
            u8KeyCode = KEY_SELECT;
            break;
        case RCP_KEYID_UP:
            u8KeyCode = KEY_UP;
            break;
        case RCP_KEYID_DOWN:
            u8KeyCode = KEY_DOWN;
            break;
        case RCP_KEYID_ROOT_MENU:
            u8KeyCode = KEY_MENU;
            break;
        case RCP_KEYID_EXIT:
            u8KeyCode = KEY_EXIT;
            break;

        default:
            statusCode = MSC_RCP_INEFFECTIVE_KEY_CODE;
            break;
    }

    if ( statusCode == MSC_RCP_INEFFECTIVE_KEY_CODE )
    {
        printf("Key ID is not supported\r\n");
    }

    return(statusCode);
}

MS_U8 msAPI_MHL_CbusRapProcess (MS_U8 rapCode)
{
    MS_U8 statusCode  = MSC_RAP_NO_ERROR;

    printf("** Receive RAP Key 0x%x from source\r\n", rapCode);

    switch(rapCode)
    {
        case MSC_RAP_POLL:
            break;

        case MSC_RAP_CONTENT_ON:
            //mdrv_mhl_SetTMDSTxOnOff(TRUE);
            if (UI_INPUT_SOURCE_TYPE == HDMI_PORT_FOR_MHL)
            {
                MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW);
            }
            break;

        case MSC_RAP_CONTENT_OFF:
            //mdrv_mhl_SetTMDSTxOnOff(FALSE);
            if (UI_INPUT_SOURCE_TYPE == HDMI_PORT_FOR_MHL)
            {
                MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
            }
            break;

        default:
            statusCode = MSC_RAP_UNRECOGNIZED_ACTION_CODE;
            break;
    }

    return( statusCode );
}

BOOLEAN msAPI_MHL_IRKeyProcess(U8 u8Keycode, BOOL bIsRelease)
{
    U8 u8RcpKey = 0xFF;
    U8 u8Idx;// u8Len;

#if (MHL_TYPE == MHL_TYPE_INTERNAL)
    if(bIsRelease == TRUE) //after sending Press key, release key wiil be sent by driver untile success
        return FALSE;
#endif
    //printf("IR Key: 0x%x\r\n", u8Keycode);

    //u8Len = sizeof(astRCPKeyTranslate)/sizeof(ST_RCP_KEY_TRANSLATE);

    for(u8Idx = 0; u8Idx < LENGTH_TRANSLATION_ARRAY; u8Idx++)
    {
        if (astRCPKeyTranslate[u8Idx].u8IRKeyCode == u8Keycode)
        {
            u8RcpKey = astRCPKeyTranslate[u8Idx].u8RCPKeyCode;
            //printf("RCP Key: 0x%x\r\n", u8RcpKey);
            break;
        }
    }

    if (u8Idx == LENGTH_TRANSLATION_ARRAY)
    {
        printf("IR key is not supported by RCP key.\r\n");
        return FALSE;
    }
    else
    {
#if (MHL_TYPE == MHL_TYPE_INTERNAL)
        return (msAPI_MHL_SendRCPAutoReleaseCmd(u8RcpKey));
#else
        return msAPI_MHL_SendRCP_PressRelease_Cmd(u8RcpKey, bIsRelease);
#endif
    }

}
BOOLEAN msAPI_CheckMHL_IRKeyValid(U8 u8Keycode)
{
    BOOLEAN bRcpKeyValid = FALSE;
    U8 u8Idx;// u8Len;
    for(u8Idx = 0; u8Idx < LENGTH_TRANSLATION_ARRAY; u8Idx++)
    {
        if (astRCPKeyTranslate[u8Idx].u8IRKeyCode == u8Keycode)
        {
            bRcpKeyValid=TRUE;
            break;
        }
    }

    if (bRcpKeyValid == FALSE)
    {
        printf("IR key is not MHL RCP key.\r\n");
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

#endif // ENABLE_MHL
#endif // _MSAPI_MHL_C_

