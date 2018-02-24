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
//!file     si_cpCEC_translate.c
//!brief    CEC Message translation.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2002-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include <string.h>
#include "./SiI1292/MAIN/si_cp1292.h"
#include "CEC/si_apiCpi.h"
#include "./SiI1292/MAIN/si_cpCEC.h"
#include "./SiI1292/CEC/si_cec_enums.h"

#if (INCLUDE_CEC_NAMES > CEC_NO_NAMES)

static char *deckControlMsgs [] =
    {
    "SKIP_FWD",
    "SKIP_BACK",
    "STOP",
    "EJECT"
    };

static char l_descBuffer [40];

#endif

#if (INCLUDE_CEC_NAMES > CEC_NO_NAMES)

//------------------------------------------------------------------------------
// Function:    CpCecTranslateLA
// Description:
//
// Returns a string of up to 19 bytes (including null terminator)
//------------------------------------------------------------------------------

char *CpCecTranslateLA ( uint8_si bLogAddr )
{
    char *pStr = NULL;

    switch ( bLogAddr & CEC_LOGADDR_UNREGORBC )
    {
        case CEC_LOGADDR_TV:        pStr = "TV";                   break;
        case CEC_LOGADDR_RECDEV1:   pStr = "RecDev 1";             break;
        case CEC_LOGADDR_RECDEV2:   pStr = "RecDev 2";             break;
        case CEC_LOGADDR_TUNER1:    pStr = "Tuner 1";              break;
        case CEC_LOGADDR_PLAYBACK1: pStr = "Playback 1";           break;
        case CEC_LOGADDR_AUDSYS:    pStr = "Audio System";         break;
        case CEC_LOGADDR_TUNER2:    pStr = "Tuner 2";              break;
        case CEC_LOGADDR_TUNER3:    pStr = "Tuner 3";              break;
        case CEC_LOGADDR_PLAYBACK2: pStr = "Playback 2";           break;
        case CEC_LOGADDR_RECDEV3:   pStr = "RecDev 3";             break;
        case CEC_LOGADDR_TUNER4:    pStr = "Tuner 4";              break;
        case CEC_LOGADDR_PLAYBACK3: pStr = "Playback 3";           break;
        case CEC_LOGADDR_RES3:      pStr = "Res3";                 break;
        case CEC_LOGADDR_RES4:      pStr = "Res4";                 break;
        case CEC_LOGADDR_SPECIFICUSE:   pStr = "SpecificUse";              break;
        case CEC_LOGADDR_UNREGORBC: pStr = "Unreg or Broadcast";   break;
    }

    return( pStr );
}

//------------------------------------------------------------------------------
// Function:    CpCecTranslateOpcodeName
// Description: 
//------------------------------------------------------------------------------

char *CpCecTranslateOpcodeName ( SI_CpiData_t *pMsg )
    {
    char *pName, *pOperand;
    int         i, outIndex;

    switch ( pMsg->opcode )
        {
        case CECOP_FEATURE_ABORT:               pName = "FEATURE_ABORT";                break;
        case CECOP_IMAGE_VIEW_ON:               pName = "IMAGE_VIEW_ON";                break;
        case CECOP_TUNER_STEP_INCREMENT:        pName = "TUNER_STEP_INCREMENT";         break;
        case CECOP_TUNER_STEP_DECREMENT:        pName = "TUNER_STEP_DECREMENT";         break;
        case CECOP_TUNER_DEVICE_STATUS:         pName = "TUNER_DEVICE_STATUS";          break;
        case CECOP_GIVE_TUNER_DEVICE_STATUS:    pName = "GIVE_TUNER_DEVICE_STATUS";     break;
        case CECOP_RECORD_ON:                   pName = "RECORD_ON";                    break;
        case CECOP_RECORD_STATUS:               pName = "RECORD_STATUS";                break;
        case CECOP_RECORD_OFF:                  pName = "RECORD_OFF";                   break;
        case CECOP_TEXT_VIEW_ON:                pName = "TEXT_VIEW_ON";                 break;
        case CECOP_RECORD_TV_SCREEN:            pName = "RECORD_TV_SCREEN";             break;
        case CECOP_GIVE_DECK_STATUS:            pName = "GIVE_DECK_STATUS";             break;
        case CECOP_DECK_STATUS:                 pName = "DECK_STATUS";                  break;
        case CECOP_SET_MENU_LANGUAGE:           pName = "SET_MENU_LANGUAGE";            break;
        case CECOP_CLEAR_ANALOGUE_TIMER:        pName = "CLEAR_ANALOGUE_TIMER";         break;
        case CECOP_SET_ANALOGUE_TIMER:          pName = "SET_ANALOGUE_TIMER";           break;
        case CECOP_TIMER_STATUS:                pName = "TIMER_STATUS";                 break;
        case CECOP_STANDBY:                     pName = "STANDBY";                      break;
        case CECOP_PLAY:
            pName = "PLAY";
            switch ( pMsg->args[0] )
                {
                case CEC_PLAY_SCAN_FWD_MIN: pOperand = "SCAN_FWD_MIN";  break;
                case CEC_PLAY_SCAN_FWD_MED: pOperand = "SCAN_FWD_MED";  break;
                case CEC_PLAY_SCAN_FWD_MAX: pOperand = "SCAN_FWD_MAX";  break;
                case CEC_PLAY_SCAN_REV_MIN: pOperand = "SCAN_REV_MIN";  break;
                case CEC_PLAY_SCAN_REV_MED: pOperand = "SCAN_REV_MED";  break;
                case CEC_PLAY_SCAN_REV_MAX: pOperand = "SCAN_REV_MAX";  break;
                case CEC_PLAY_SLOW_FWD_MIN: pOperand = "SLOW_FWD_MIN";  break;
                case CEC_PLAY_SLOW_FWD_MED: pOperand = "SLOW_FWD_MED";  break;
                case CEC_PLAY_SLOW_FWD_MAX: pOperand = "SLOW_FWD_MAX";  break;
                case CEC_PLAY_SLOW_REV_MIN: pOperand = "SLOW_REV_MIN";  break;
                case CEC_PLAY_SLOW_REV_MED: pOperand = "SLOW_REV_MED";  break;
                case CEC_PLAY_SLOW_REV_MAX: pOperand = "SLOW_REV_MAX";  break;
                case CEC_PLAY_REVERSE:      pOperand = "REVERSE";       break;
                case CEC_PLAY_FORWARD:      pOperand = "FORWARD";       break;
                case CEC_PLAY_STILL:        pOperand = "STILL";         break;
                default:                    pOperand = "UNKNOWN";       break;
                };
            sprintf( l_descBuffer, "%s (%s)", pName, pOperand );
            pName = l_descBuffer;
            break;
        case CECOP_DECK_CONTROL:
            pName = "DECK_CONTROL";
            sprintf( l_descBuffer, "%s (%s)", pName, deckControlMsgs[ pMsg->args[0] - 1] );
            pName = l_descBuffer;
            break;
        case CECOP_TIMER_CLEARED_STATUS:        pName = "TIMER_CLEARED_STATUS";         break;
        case CECOP_USER_CONTROL_PRESSED:        pName = "USER_CONTROL_PRESSED";         break;
        case CECOP_USER_CONTROL_RELEASED:       pName = "USER_CONTROL_RELEASED";        break;
        case CECOP_GIVE_OSD_NAME:               pName = "GIVE_OSD_NAME";                break;
        case CECOP_SET_OSD_NAME:
            {
            pName = "SET_OSD_NAME";
            outIndex = sprintf( l_descBuffer, "%s (", pName );
            for ( i = 0; i < pMsg->argCount; i++ )
                l_descBuffer[ outIndex++] = pMsg->args[i];
            l_descBuffer[ outIndex] = 0;

            strcat( l_descBuffer, ")" );
            pName = l_descBuffer;
            break;
            }
        case CECOP_SET_OSD_STRING:
            {
            pName = "SET_OSD_STRING";
            outIndex = sprintf( l_descBuffer, "%s (", pName );
            for ( i = 1; i < pMsg->argCount; i++ )
                l_descBuffer[ outIndex++] = pMsg->args[i];
            l_descBuffer[ outIndex] = 0;

            strcat( l_descBuffer, ")" );
            pName = l_descBuffer;
            break;
            }
        case CECOP_SET_TIMER_PROGRAM_TITLE:     pName = "SET_TIMER_PROGRAM_TITLE";      break;
        case CECOP_SYSTEM_AUDIO_MODE_REQUEST:   pName = "SYSTEM_AUDIO_MODE_REQUEST";    break;
        case CECOP_GIVE_AUDIO_STATUS:           pName = "GIVE_AUDIO_STATUS";            break;
        case CECOP_SET_SYSTEM_AUDIO_MODE:       pName = "SET_SYSTEM_AUDIO_MODE";        break;
        case CECOP_REPORT_AUDIO_STATUS:         pName = "REPORT_AUDIO_STATUS";          break;
        case CECOP_GIVE_SYSTEM_AUDIO_MODE_STATUS: pName = "GIVE_SYSTEM_AUDIO_MODE_STATUS";  break;
        case CECOP_SYSTEM_AUDIO_MODE_STATUS:    pName = "SYSTEM_AUDIO_MODE_STATUS";     break;
        case CECOP_ROUTING_CHANGE:              pName = "ROUTING_CHANGE";               break;
        case CECOP_ROUTING_INFORMATION:         pName = "ROUTING_INFORMATION";          break;
        case CECOP_ACTIVE_SOURCE:               pName = "ACTIVE_SOURCE";                break;
        case CECOP_GIVE_PHYSICAL_ADDRESS:       pName = "GIVE_PHYSICAL_ADDRESS";        break;
        case CECOP_REPORT_PHYSICAL_ADDRESS:     pName = "REPORT_PHYSICAL_ADDRESS";      break;
        case CECOP_REQUEST_ACTIVE_SOURCE:       pName = "REQUEST_ACTIVE_SOURCE";        break;
        case CECOP_SET_STREAM_PATH:             pName = "SET_STREAM_PATH";              break;
        case CECOP_DEVICE_VENDOR_ID:            pName = "DEVICE_VENDOR_ID";             break;
        case CECOP_VENDOR_COMMAND:              pName = "VENDOR_COMMAND";               break;
        case CECOP_VENDOR_REMOTE_BUTTON_DOWN:   pName = "VENDOR_REMOTE_BUTTON_DOWN";    break;
        case CECOP_VENDOR_REMOTE_BUTTON_UP:     pName = "VENDOR_REMOTE_BUTTON_UP";      break;
        case CECOP_GIVE_DEVICE_VENDOR_ID:       pName = "GIVE_DEVICE_VENDOR_ID";        break;
        case CECOP_MENU_REQUEST:                pName = "MENU_REQUEST";                 break;
        case CECOP_MENU_STATUS:                 pName = "MENU_STATUS";                  break;
        case CECOP_GIVE_DEVICE_POWER_STATUS:    pName = "GIVE_DEVICE_POWER_STATUS";     break;
        case CECOP_REPORT_POWER_STATUS:         pName = "REPORT_POWER_STATUS";          break;
        case CECOP_GET_MENU_LANGUAGE:           pName = "GET_MENU_LANGUAGE";            break;
        case CECOP_SELECT_ANALOGUE_SERVICE:     pName = "SELECT_ANALOGUE_SERVICE";      break;
        case CECOP_SELECT_DIGITAL_SERVICE:      pName = "SELECT_DIGITAL_SERVICE";       break;
        case CECOP_SET_DIGITAL_TIMER:           pName = "SET_DIGITAL_TIMER";            break;
        case CECOP_CLEAR_DIGITAL_TIMER:         pName = "CLEAR_DIGITAL_TIMER";          break;
        case CECOP_SET_AUDIO_RATE:              pName = "SET_AUDIO_RATE";               break;
        case CECOP_INACTIVE_SOURCE:             pName = "INACTIVE_SOURCE";              break;
        case CECOP_CEC_VERSION:                 pName = "CEC_VERSION";                  break;
        case CECOP_GET_CEC_VERSION:             pName = "GET_CEC_VERSION";              break;
        case CECOP_VENDOR_COMMAND_WITH_ID:      pName = "VENDOR_COMMAND_WITH_ID";       break;
        case CECOP_CLEAR_EXTERNAL_TIMER:        pName = "CLEAR_EXTERNAL_TIMER";         break;
        case CECOP_SET_EXTERNAL_TIMER:          pName = "SET_EXTERNAL_TIMER";           break;
        case CDCOP_HEADER:                       pName = "CDC_PACKET";                        break;
        case CECOP_ABORT:                       pName = "ABORT";                        break;

        case CECOP_ARC_INITIATE:                pName = "ARC_INITIATE";                  break;
        case CECOP_ARC_REPORT_INITIATED:       pName = "ARC_REPORT_INITIATED";              break;
        case CECOP_ARC_REPORT_TERMINATED:     pName = "ARC_REPORT_TERMINATED";            break;
        case CECOP_ARC_REQUEST_INITIATION:     pName = "ARC_REQUEST_INITIATION";            break;
        case CECOP_ARC_REQUEST_TERMINATION:   pName = "ARC_REQUEST_TERMINATION";          break;
        case CECOP_ARC_TERMINATE:              pName = "ARC_TERMINATE";                break;

        default:                                pName = "UNKNOWN";                      break;
        }

    return( pName );
    }
#endif  //(INCLUDE_CEC_NAMES > CEC_NO_NAMES)

#if (INCLUDE_CEC_NAMES > CEC_NO_TEXT)

//------------------------------------------------------------------------------
// Function:    CpCecPrintCommand
// Description: Translate CEC transaction into human-readable form.
//------------------------------------------------------------------------------

bool_si CpCecPrintCommand ( SI_CpiData_t *pMsg, bool_si isTX )
    {
    bool_si        success = false;
#if (INCLUDE_CEC_NAMES == CEC_ALL_TEXT)
    char        logStr [120];
#else
    char        logStr [60];
#endif
    uint16_si    writeCnt;
    int         i;


    writeCnt = sprintf(
        logStr, "\n[%02X][%c%02X](%d): ",
        (uint16_si)pMsg->opcode, isTX ? 'W' : 'R', (uint16_si)pMsg->srcDestAddr, (uint16_si)pMsg->argCount
        );
    for ( i = 0; i < pMsg->argCount; i++ )
        writeCnt = sprintf( logStr, "%s%02X ", logStr, (uint16_si)pMsg->args[ i] );

#if (INCLUDE_CEC_NAMES > CEC_NO_NAMES)

    /* Add human readable command name  */

    sprintf(
        logStr, "%s%*s%s\r\n",
        logStr,
        52 - writeCnt, "; ",
        CpCecTranslateOpcodeName( pMsg )
        );
#endif

//    DEBUG_PRINT( MSG_STAT,( logStr ));
//	DEBUG_PRINT( MSG_STAT, ("\n"));
	
    return( success );
    }
#endif // (INCLUDE_CEC_NAMES > CEC_NO_TEXT)
