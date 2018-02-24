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
/// file    msAPI_CEC.c
/// @author MStar Semiconductor Inc.
/// @brief  HDMI CEC API Interface
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include <string.h>
#include "stdio.h"

//***************************************************************************************

#define _MSAPICEC_POSTMSG_C_

//
//***************************************************************************************
//

extern CEC_ERROR_CODE MDrv_CEC_TxApi2(MsCEC_DEVICELA dst_address, MsCEC_MSGLIST msg, MS_U8* operand_ptr, MS_U8 len);

//
//***************************************************************************************
//

CEC_ERROR_CODE msAPI_CEC_PostMsg(MsCEC_DEVICELA dst_address, MsCEC_MSGLIST msg, MS_U8 *cmd, MS_U8 len)
{
    CEC_ERROR_CODE cecErrorCode = E_CEC_FEATURE_ABORT;

    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return cecErrorCode;
    }

    // no need to check if CEC is enable or not
    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == ENABLE)
    {
      #if 1
        MS_U8 i;
        CEC_TX( printf("\n\33[0;33m CEC TX < %02X %02X ", (U8)dst_address, (U8)msg) );
        for(i = 0; i<(len); i++)
        {
            CEC_TX( printf("%02X ", (U8)cmd[i]) );
        }
        if ( (msg == E_MSG_FEATURE_ABORT) && (len ==0) )
        {
            CEC_TX( printf("> \33[m \n") );
        }
        else
        {
            CEC_TX( printf("> : %s \33[m \n", (char *)CEC_opCodeStr_Customer[msg]) );
        }
      #endif

        cecErrorCode = MDrv_CEC_TxApi2(dst_address, msg, cmd, len);

      #if 0 // no need, should be updated in CEC library
        /*
        CEC compliance test 9.7-2: waits for at least 7 bit periods before transmitting a message directly
                                   after transmitting a previous message.
        7 bit periods are about 16.8ms.
        */
        MsOS_DelayTask(1);
      #endif

        // add retry time for system busy
        if ( cecErrorCode & E_CEC_SYSTEM_BUSY )
        {
            MS_U32 u32Retry = 0;

            msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
            msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);

            while ( u32Retry < SYSTEM_BUSY_RETRY_TIME )
            {
                CEC_TX( printf("[CEC] CEC TX SYSTEM BUSY RETRY : %d \n", (u32Retry+1)) );

                MsOS_DelayTask(CEC_SYSTEM_BUSY_DELAY);

                cecErrorCode = MDrv_CEC_TxApi2(dst_address, msg, cmd, len);

                if ( !(cecErrorCode & E_CEC_SYSTEM_BUSY) )
                {
                    CEC_TX( printf("[CEC] CEC TX SYSTEM BUSY RETRY OK \n") );
                    break;
                }
                u32Retry++;
            }

            if (u32Retry == SYSTEM_BUSY_RETRY_TIME)
            {
                CEC_TX( printf("[CEC] CEC TX SYSTEM BUSY RETRY FAIL! \n") );
            }

            msDebug_ANSI_AllAttrOffText();
        }

        MsOS_DelayTask(CEC_TRANSITION_DELAY);
    }

    return cecErrorCode;
}

MS_BOOL msAPI_CEC_PostMsgToQueue (MsCEC_DEVICELA enDevice, MsCEC_MSGLIST enOpcode, MS_U8* pu8Operand, MS_U8 u8Len)
{
    PCECMSG pstCECMsg;
    MS_U8 i;

    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return FALSE;
    }

    if( u8Len > CEC_MSG_OPERAND_LEN )
    {
        return FALSE;
    }

    if(  (stGenSetting.stHDMISetting.g_bHdmiCecMode== DISABLE)
      && (stGenSetting.stHDMISetting.g_enHDMIARC == DISABLE) )
    {
        return FALSE;
    }

    // Checking array index
    if( _stCecMsgQueue.u8CecMsgQIdxStart >= CEC_MSG_QUEUE_SIZE )
    {
        _stCecMsgQueue.u8CecMsgQIdxStart = 0;
    }

    pstCECMsg = &(_stCecMsgQueue.astCecMsgQ[_stCecMsgQueue.u8CecMsgQIdxStart]);
    if (pstCECMsg->u8Handle!= CEC_INVALID)//Queue full
    {
        return FALSE;   // no available message queue slot
    }

    pstCECMsg->u8Handle = CEC_VALID;
    pstCECMsg->enDevice = enDevice;
    pstCECMsg->enOpcode = enOpcode;

    if( (u8Len > 0) && (pu8Operand != NULL) )
    {
        for(i=0; i<u8Len; i++)
        {
            pstCECMsg->au8Operand[i] = pu8Operand[i];
        }
    }

    pstCECMsg->u8Len = u8Len;

    ++_stCecMsgQueue.u8CecMsgQIdxStart;
    _stCecMsgQueue.u8CecMsgQIdxStart %= CEC_MSG_QUEUE_SIZE;

    return TRUE;
}

BOOLEAN msAPI_CEC_GetMsgInQueue (PCECMSG pCECMsg)
{
    if (_stCecMsgQueue.astCecMsgQ[_stCecMsgQueue.u8CecMsgQIdxEnd].u8Handle == CEC_INVALID)
        return FALSE;    // message queue is empty

    *pCECMsg = _stCecMsgQueue.astCecMsgQ[_stCecMsgQueue.u8CecMsgQIdxEnd];
    _stCecMsgQueue.astCecMsgQ[_stCecMsgQueue.u8CecMsgQIdxEnd].u8Handle = CEC_INVALID;

    ++_stCecMsgQueue.u8CecMsgQIdxEnd;
    _stCecMsgQueue.u8CecMsgQIdxEnd %= CEC_MSG_QUEUE_SIZE;
    return TRUE;
}

static void msCecEmptySwMsgQueue(void)
{
    MS_U8 i;

    _stCecMsgQueue.u8CecMsgQIdxStart = 0;
    _stCecMsgQueue.u8CecMsgQIdxEnd   = 0;

    for (i = 0; i < CEC_MSG_QUEUE_SIZE; i++)
        _stCecMsgQueue.astCecMsgQ[i].u8Handle= CEC_INVALID;
}

//***************************************************************************************

void msAPI_CEC_PostMsg_ActiveSource(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pPhysicalAddr)
{
    MS_U8 txbuf[2];

    txbuf[0] = pPhysicalAddr[0];
    txbuf[1] = pPhysicalAddr[1];

    CEC_POSTMSG_DEBUG(printf("%s_<Active Source>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", (txbuf[0]<<8 | txbuf[1])));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_ACTIVE_SOURCE, txbuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_ACTIVE_SOURCE, txbuf, 2);
    }
}

void msAPI_CEC_PostMsg_InActiveSource(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MS_U8* phy_Add)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Inactive Source>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" [0x%04x] - 0x%x \n", phy_Add, enDevice));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_RC_INACTIVE_SOURCE, (MS_U8 *)&phy_Add, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_RC_INACTIVE_SOURCE, (MS_U8 *)&phy_Add, 2);
    }
}

void msAPI_CEC_PostMsg_RequestActiveSource(EN_CEC_SEND_MSG enCecSendMsg)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Request Active Source> \n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_RC_REQUEST_ACTIVE_SOURCE, NULL, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_RC_REQUEST_ACTIVE_SOURCE, NULL, 0);
    }
}

void msAPI_CEC_PostMsg_RoutingChange(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pOrig_Addr, MS_U8* pNew_Addr)
{
    MS_U8 txbuf[4];

    txbuf[0] = pOrig_Addr[0];
    txbuf[1] = pOrig_Addr[1];

    txbuf[2] = pNew_Addr[0];
    txbuf[3] = pNew_Addr[1];

    CEC_POSTMSG_DEBUG(printf("%s_<Routing Change>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" from 0x%x to 0x%x \n", (txbuf[0]<<8 | txbuf[1]),
                                                      (txbuf[2]<<8 | txbuf[3]) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_RC_ROUTING_CHANGE, (MS_U8 *)&txbuf, 4);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_RC_ROUTING_CHANGE, (MS_U8 *)&txbuf, 4);
    }
}

void msAPI_CEC_PostMsg_RoutingInformation(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* new_address)
{
    MS_U8 txbuf[2];

    txbuf[0] = new_address[0];
    txbuf[1] = new_address[1];

    CEC_POSTMSG_DEBUG(printf("%s_<Routing Information>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" [0x%04x] \n", (txbuf[0]<<8 | txbuf[1]) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_RC_ROUTING_INFORMATION, (MS_U8 *)&txbuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_RC_ROUTING_INFORMATION, (MS_U8 *)&txbuf, 2);
    }
}

void msAPI_CEC_PostMsg_SetStreamPath(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* new_address)
{
    MS_U8 txbuf[2];

    txbuf[0] = new_address[0];
    txbuf[1] = new_address[1];

    CEC_POSTMSG_DEBUG(printf("%s_<Set Stream Path>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" [0x%04x] \n", (txbuf[0]<<8 | txbuf[1]) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_RC_SET_STREM_PATH, (MS_U8 *)&txbuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_RC_SET_STREM_PATH, (MS_U8 *)&txbuf, 2);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_Standby(EN_CEC_SEND_MSG enCecSendMsg)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Standby> \n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_STANDBY, NULL, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_STANDBY, NULL, 0);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_RecordOff(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Record Off> \n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_OTR_RECORD_OFF, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_OTR_RECORD_OFF, 0, 0);
    }
}

void msAPI_CEC_PostMsg_RecordOn(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_RECORD_SOURCE_TYPE enCmd)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Record On> \n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_OTR_RECORD_ON, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_OTR_RECORD_ON, (MS_U8 *)&enCmd, 1);
    }
}

void msAPI_CEC_PostMsg_CECVersion(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MS_U8 u8Version)
{
    CEC_POSTMSG_DEBUG(printf("%s_<CEC Version>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x", enDevice ));

    switch (u8Version)
    {
        case CEC_VERSION_11:
            CEC_POSTMSG_DEBUG(printf(" CEC Ver 1.1 \n"));
            break;

        case CEC_VERSION_12:
            CEC_POSTMSG_DEBUG(printf(" CEC Ver 1.2 \n"));
            break;

        case CEC_VERSION_12a:
            CEC_POSTMSG_DEBUG(printf(" CEC Ver 1.2a \n"));
            break;

        case CEC_VERSION_13:
            CEC_POSTMSG_DEBUG(printf(" CEC Ver 1.3 \n"));
            break;

        case CEC_VERSION_13a:
            CEC_POSTMSG_DEBUG(printf(" CEC Ver 1.3a \n"));
            break;

        case CEC_VERSION_14:
            CEC_POSTMSG_DEBUG(printf(" CEC Ver 1.4 \n"));
            break;

        default:
            CEC_POSTMSG_DEBUG(printf(" Future use (reserved) [%bd] \n", u8Version));
            break;
    }

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_SI_CEC_VERSION, &u8Version, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_SI_CEC_VERSION, &u8Version, 1);
    }
}

void msAPI_CEC_PostMsg_GetCECVersion(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Get CEC Version>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_SI_GET_CEC_VERSION, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_SI_GET_CEC_VERSION, 0, 0);
    }
}

void msAPI_CEC_PostMsg_GivePhysicalAddress(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Give Physical Address>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_SI_GIVE_PHYSICAL_ADDRESS, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_SI_GIVE_PHYSICAL_ADDRESS, 0, 0);
    }
}

CEC_ERROR_CODE  msAPI_CEC_PingDevice(MsCEC_DEVICELA enPingDevice)
{
    CEC_ERROR_CODE enCecErrorCode;

    enCecErrorCode = msAPI_CEC_PostMsg(enPingDevice, (MsCEC_MSGLIST)0, (U8*)&enPingDevice, 0);

#if 0//CEC_DEBUG
    printf("\n <Ping 0x%x> -", enPingDevice);
    MApp_CEC_ERROR_CODE_String(enCecErrorCode);
    printf("\n");
#endif

    return enCecErrorCode;
}

CEC_ERROR_CODE msAPI_CEC_PostMsg_PollingMessage(MsCEC_DEVICELA enPingDevice)
{
    CEC_ERROR_CODE enCecErrorCode;

    enCecErrorCode = msAPI_CEC_PostMsg(enPingDevice, (MsCEC_MSGLIST)0, (U8*)&enPingDevice, 0);

#if 0//CEC_DEBUG
    printf("\n <Polling 0x%x> -", enPingDevice);
    MApp_CEC_ERROR_CODE_String(enCecErrorCode);
    printf("\n");
#endif

    return enCecErrorCode;
}

void msAPI_CEC_PostMsg_ReportPhysicalAddress(EN_CEC_SEND_MSG enCecSendMsg)
{
    MS_U8 txbuf[3];

    txbuf[0] = 0x00;
    txbuf[1] = 0x00;
    txbuf[2] = E_LA_TV;

    CEC_POSTMSG_DEBUG(printf("%s_<Report Physical Address> [0.0.0.0] [TV] \n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_SI_REPORT_PHYSICAL_ADDRESS, (MS_U8 *)&txbuf, 3);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_SI_REPORT_PHYSICAL_ADDRESS, (MS_U8 *)&txbuf, 3);
    }
}

void msAPI_CEC_PostMsg_SetMenuLang(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pu8MenuLanguageCode)
{
    MS_U8 txbuf[3];

    txbuf[0] = pu8MenuLanguageCode[0];
    txbuf[1] = pu8MenuLanguageCode[1];
    txbuf[2] = pu8MenuLanguageCode[2];

    CEC_POSTMSG_DEBUG(printf("%s_<Set Menu Language>\n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - [%c", txbuf[0] ));
    CEC_POSTMSG_DEBUG(printf(" %c", txbuf[1] ));
    CEC_POSTMSG_DEBUG(printf(" %c] \n", txbuf[2] ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_SI_SET_MENU_LANGUAGE, (MS_U8*)&txbuf, 3);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_SI_SET_MENU_LANGUAGE, (MS_U8*)&txbuf, 3);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_DeckCtrl(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_DC_DECK_CTRL_PARM enCmd)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Deck Control>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x -", enDevice ));

    switch (enCmd)
    {
        case E_MSG_DCM_CMD_SKIP_FORWARD:
            CEC_POSTMSG_DEBUG(printf(" Skip Forward/Wind \n"));
            break;

        case E_MSG_DCM_CMD_SKIP_REVERSE:
            CEC_POSTMSG_DEBUG(printf(" Skip Reverse/Rewind \n"));
            break;

        case E_MSG_DCM_CMD_STOP:
            CEC_POSTMSG_DEBUG(printf(" Stop \n"));
            break;

        case E_MSG_DCM_CMD_EJECT:
            CEC_POSTMSG_DEBUG(printf(" Eject \n"));
            break;

        default:
            CEC_POSTMSG_DEBUG(printf(" Reserved [%bd] \n", enCmd));
            break;
    }

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DC_DECK_CONTROL, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_DC_DECK_CONTROL, (MS_U8 *)&enCmd, 1);
    }
}

void msAPI_CEC_PostMsg_DeckStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_DC_DECK_STATUS_PARM enCmd)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Deck Status>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x -", enDevice ));

    switch (enCmd)
    {
        case E_MSG_DI_CMD_PLAY:
            CEC_POSTMSG_DEBUG(printf(" Play \n"));
            break;

        case E_MSG_DI_CMD_RECORD:
            CEC_POSTMSG_DEBUG(printf(" Record \n"));
            break;

        case E_MSG_DI_CMD_PLAY_REVERSE:
            CEC_POSTMSG_DEBUG(printf(" Play Reverse \n"));
            break;

        case E_MSG_DI_CMD_STILL:
            CEC_POSTMSG_DEBUG(printf(" Still \n"));
            break;

        case E_MSG_DI_CMD_SLOW:
            CEC_POSTMSG_DEBUG(printf(" Slow \n"));
            break;

        case E_MSG_DI_CMD_SLOW_REVERSE:
            CEC_POSTMSG_DEBUG(printf(" Slow Reverse \n"));
            break;

        case E_MSG_DI_CMD_FAST_FORWARD:
            CEC_POSTMSG_DEBUG(printf(" Fast Forward \n"));
            break;

        case E_MSG_DI_CMD_FAST_REVERSE:
            CEC_POSTMSG_DEBUG(printf(" Fast Reverse \n"));
            break;

        case E_MSG_DI_CMD_NO_MEDIA:
            CEC_POSTMSG_DEBUG(printf(" No Media \n"));
            break;

        case E_MSG_DI_CMD_STOP:
            CEC_POSTMSG_DEBUG(printf(" Stop \n"));
            break;

        case E_MSG_DI_CMD_SKIP_FORWARD:
            CEC_POSTMSG_DEBUG(printf(" Skip Forward \n"));
            break;

        case E_MSG_DI_CMD_SKIP_REVERSE:
            CEC_POSTMSG_DEBUG(printf(" Skip Reverse \n"));
            break;

        case E_MSG_DI_CMD_INDEX_SEARCH_FORWARD:
            CEC_POSTMSG_DEBUG(printf(" Index Search Forward \n"));
            break;

        case E_MSG_DI_CMD_INDEX_SEARCH_REVERSE:
            CEC_POSTMSG_DEBUG(printf(" Index Search Reverse \n"));
            break;

        case E_MSG_DI_CMD_OTHER_STATUS:
            CEC_POSTMSG_DEBUG(printf(" Other Status \n"));
            break;

        default:
            CEC_POSTMSG_DEBUG(printf(" Reserved [%bd] \n", enCmd));
            break;
    }

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DC_DECK_STATUS, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_DC_DECK_STATUS, (MS_U8 *)&enCmd, 1);
    }
}

void msAPI_CEC_PostMsg_GiveDeckStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_STATUS_REQUEST_PARM enCmd)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Give Deck Status>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x -", enDevice ));

    switch (enCmd)
    {
        case E_MSG_SR_CMD_ON:
            CEC_POSTMSG_DEBUG(printf(" On \n"));
            break;

        case E_MSG_SR_CMD_OFF:
            CEC_POSTMSG_DEBUG(printf(" Off \n"));
            break;

        case E_MSG_SR_CMD_ONCE:
            CEC_POSTMSG_DEBUG(printf(" Once \n"));
            break;

        default:
            CEC_POSTMSG_DEBUG(printf(" Reserved [%bd] \n", enCmd));
            break;
    }

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DC_GIVE_DECK_STATUS, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_DC_GIVE_DECK_STATUS, (MS_U8 *)&enCmd, 1);
    }
}

void msAPI_CEC_PostMsg_DCPlay(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_DC_PLAY_PARM enCmd)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Deck Play>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x -", enDevice ));

    switch (enCmd)
    {
        case E_MSG_PM_CMD_PLAY_FORWARD:
            CEC_POSTMSG_DEBUG(printf(" Play Forward \n"));
            break;

        case E_MSG_PM_CMD_PLAY_REVERSE:
            CEC_POSTMSG_DEBUG(printf(" Play Reverse \n"));
            break;

        case E_MSG_PM_CMD_PLAY_STILL:
            CEC_POSTMSG_DEBUG(printf(" Play Still \n"));
            break;

        case E_MSG_PM_CMD_FAST_FORWARD_MINI_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Fast Forward Mini Speed \n"));
            break;

        case E_MSG_PM_CMD_FAST_FORWARD_MEDIUM_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Fast Forward Medium Speed \n"));
            break;

        case E_MSG_PM_CMD_FAST_FORWARD_MAXI_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Fast Forward Maxi Speed \n"));
            break;

        case E_MSG_PM_CMD_FAST_REVERSE_MINI_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Fast Reverse Mini Speed \n"));
            break;

        case E_MSG_PM_CMD_FAST_REVERSE_MEDIUM_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Fast Reverse Medium Speed \n"));
            break;

        case E_MSG_PM_CMD_FAST_REVERSE_MAXI_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Fast Reverse Maxi Speed \n"));
            break;

        case E_MSG_PM_CMD_SLOW_FORWARD_MINI_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Slow Forward Mini Speed \n"));
            break;

        case E_MSG_PM_CMD_SLOW_FORWARD_MEDIUM_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Slow Forward Medium Speed \n"));
            break;

        case E_MSG_PM_CMD_SLOW_FORWARD_MAXI_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Slow Forward Maxi Speed \n"));
            break;

        case E_MSG_PM_CMD_SLOW_REVERSE_MINI_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Slow Reverse Mini Speed \n"));
            break;

        case E_MSG_PM_CMD_SLOW_REVERSE_MEDIUM_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Slow Reverse Medium Speed \n"));
            break;

        case E_MSG_PM_CMD_SLOW_REVERSE_MAXI_SPEED:
            CEC_POSTMSG_DEBUG(printf(" Slow Reverse Maxi Speed \n"));
            break;

        default:
            CEC_POSTMSG_DEBUG(printf(" Reserved [%bd] \n", enCmd));
            break;
    }

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DC_PLAY, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_DC_PLAY, (MS_U8 *)&enCmd, 1);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_DeviceVendorID(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    MS_U8 txbuf[3];

    txbuf[0] = _stMsApiCecInfoList.u8CecVendorID[enDevice][0];
    txbuf[1] = _stMsApiCecInfoList.u8CecVendorID[enDevice][1];
    txbuf[2] = _stMsApiCecInfoList.u8CecVendorID[enDevice][2];

    CEC_POSTMSG_DEBUG(printf("%s_<Device Vendor ID>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" = 0x%x,", txbuf[0]));
    CEC_POSTMSG_DEBUG(printf(" 0x%x,",   txbuf[1]));
    CEC_POSTMSG_DEBUG(printf(" 0x%x \n", txbuf[2]));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_VS_DEVICE_VENDOR_ID, (MS_U8 *)&txbuf, 3);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_VS_DEVICE_VENDOR_ID, (MS_U8 *)&txbuf, 3);
    }
}

void msAPI_CEC_PostMsg_GiveDeviceVendorID(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Give Device Vendor ID>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_VS_GIVE_DEVICE_VENDOR_ID, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_VS_GIVE_DEVICE_VENDOR_ID, 0, 0);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_GiveOSDName(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    if (enDevice != E_LA_BROADCAST)
    {
        CEC_POSTMSG_DEBUG(printf("%s_<Give OSD Name>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
        CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));

        if (enCecSendMsg == POSTMSG)
        {
            msAPI_CEC_PostMsgToQueue((MsCEC_DEVICELA)enDevice, E_MSG_OSDNT_GIVE_OSD_NAME, 0, 0);
        }
        else // if (enCecSendMsg == DIRECTMSG)
        {
            msAPI_CEC_PostMsg((MsCEC_DEVICELA)enDevice, E_MSG_OSDNT_GIVE_OSD_NAME, 0, 0);
        }
    }
    else
    {
        CEC_POSTMSG_ERROR_DEBUG(printf("! <Give OSD Name> - Wrong LA 0x%x ! \n", enDevice ));
    }
}

void msAPI_CEC_PostMsg_SetOSDName(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    MS_U16 u16len = 0;

    for (u16len=0; u16len < MAX_CEC_DEVICE_OSD_NAME; u16len++)
    {
        if (_stMsApiCecInfoList.u8CecDeviceName[E_LA_TV][u16len] == 0)
            break;
    }

    CEC_POSTMSG_DEBUG(printf("%s_<Set Osd Name>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x ", enDevice ));
    CEC_POSTMSG_DEBUG(printf(": %s \n", _stMsApiCecInfoList.u8CecDeviceName[E_LA_TV] ));

    // CEC HW operand len limit is 14
    if( u16len > CEC_MSG_OPERAND_LEN )
    {
        u16len = CEC_MSG_OPERAND_LEN;
    }

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_OSDNT_SET_OSD_NAME,
                    _stMsApiCecInfoList.u8CecDeviceName[E_LA_TV], u16len);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_OSDNT_SET_OSD_NAME,
                    _stMsApiCecInfoList.u8CecDeviceName[E_LA_TV], u16len);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_MenuRequest(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_MENU_REQ_TYPE enCmd)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Menu Request>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x ", enDevice ));

    switch (enCmd)
    {
        case E_MSG_MENU_REQ_ACTIVATED:
            CEC_POSTMSG_DEBUG(printf(" Activated \n"));
            break;

        case E_MSG_MENU_REQ_DEACTIVATED:
            CEC_POSTMSG_DEBUG(printf(" Deactivated \n"));
            break;

        case E_MSG_MENU_REQ_QUERY:
            CEC_POSTMSG_DEBUG(printf(" Query \n"));
            break;

        default:
            CEC_POSTMSG_DEBUG(printf(" Reserved [%bd] \n", enCmd));
            break;
    }

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DMC_MENU_REQUEST, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_DMC_MENU_REQUEST, (MS_U8 *)&enCmd, 1);
    }
}

void msAPI_CEC_PostMsg_MenuStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_MENU_STATE enCmd)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Menu Status>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x ", enDevice ));

    switch (enCmd)
    {
        case E_MSG_MENU_ACTIVATED:
            CEC_POSTMSG_DEBUG(printf(" Activated \n"));
            break;

        case E_MSG_MENU_DEACTIVATED:
            CEC_POSTMSG_DEBUG(printf(" Deactivated \n"));
            break;

        default:
            CEC_POSTMSG_DEBUG(printf(" Reserved [%bd] \n", enCmd));
            break;
    }

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DMC_MENU_STATUS, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_DMC_MENU_STATUS, (MS_U8 *)&enCmd, 1);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_UserCtrlPressed(EN_CEC_SEND_MSG enCecSendMsg, MS_BOOL bUserCtrlEn,
                                       MsCEC_DEVICELA enDevice, MsCEC_MSG_USER_CTRL_PARM cmd)
{
    if (bUserCtrlEn) // menu status is activated
    {
        CEC_POSTMSG_DEBUG(printf("%s_<User Control Pressed>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
        CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));
        CEC_POSTMSG_DEBUG(printf(" cmd: 0x%x \n", cmd ));

        if (enCecSendMsg == POSTMSG)
        {
             msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DMC_USER_CONTROL_PRESSED, (MS_U8*)&cmd, 1);
        }
        else // if (enCecSendMsg == DIRECTMSG)
        {
            msAPI_CEC_PostMsg(enDevice, E_MSG_DMC_USER_CONTROL_PRESSED, (MS_U8*)&cmd, 1);
        }
    }
}

void msAPI_CEC_PostMsg_UserCtrlReleased(EN_CEC_SEND_MSG enCecSendMsg, MS_BOOL bUserCtrlEn, MsCEC_DEVICELA enDevice)
{
    if (bUserCtrlEn) // menu status is activated
    {
        CEC_POSTMSG_DEBUG(printf("%s_<User Control Released>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
        CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));
      //  CEC_POSTMSG_DEBUG(printf(" cmd: 0x%x \n", cmd ));

        if (enCecSendMsg == POSTMSG)
        {
             msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DMC_USER_CONTROL_RELEASED, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
        }
        else // if (enCecSendMsg == DIRECTMSG)
        {
            msAPI_CEC_PostMsg(enDevice, E_MSG_DMC_USER_CONTROL_RELEASED, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
        }
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_GiveDevicePowerStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Give Device Power Status>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_PS_GIVE_DEVICE_POWER_STATUS, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_PS_GIVE_DEVICE_POWER_STATUS, 0, 0);
    }
}

void msAPI_CEC_PostMsg_ReportPowerStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_POWER_STATUS_PARM MyPowerStatus)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Report Power Status>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x ", enDevice ));
    CEC_POSTMSG_DEBUG(printf(" - %s \n",  (MyPowerStatus == E_MSG_PWRSTA_ON)?         "PWRSTA_ON"
                                         :(MyPowerStatus == E_MSG_PWRSTA_STANDBY)?    "PWRSTA_STANDBY"
                                         :(MyPowerStatus == E_MSG_PWRSTA_STANDBY2ON)? "PWRSTA_STANDBY2ON"
                                         :(MyPowerStatus == E_MSG_PWRSTA_ON2STANDBY)? "PWRSTA_ON2STANDBY"
                                         :                                            "PWRSTA_UNKNOW" ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_PS_REPORT_POWER_STATUS, (MS_U8*)&MyPowerStatus, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_PS_REPORT_POWER_STATUS, (MS_U8*)&MyPowerStatus, 1);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_GiveAudioStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Give Audio Status>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_SAC_GIVE_AUDIO_STATUS, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_SAC_GIVE_AUDIO_STATUS, 0, 0);
    }
}

void msAPI_CEC_PostMsg_GiveSystemAudioModeStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Give System Audio Mode Status>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS, 0, 0);
    }
}

void msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(EN_CEC_SEND_MSG enCecSendMsg)
{
    CEC_POSTMSG_DEBUG(printf("%s_<System Audio Mode Request> \n", ((enCecSendMsg == POSTMSG)?("P"):("D"))));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, NULL, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, NULL, 0);
    }
}

void msAPI_CEC_TxMsgSystemAudioModeRequest(EN_CEC_SEND_MSG enCecSendMsg, BOOLEAN bTurnOnOff)
{
    MS_U8 txbuf[2];
    MS_U16 u16PhyAddr = _stMsApiCecInfoList.u16ActiveSourceAddress;

    txbuf[0] = (MS_U8)(u16PhyAddr>>8);
    txbuf[1] = (MS_U8)(u16PhyAddr&0x0F);

    CEC_POSTMSG_DEBUG(printf("%s_<System Audio Mode Request>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    if(bTurnOnOff)
    {
        CEC_POSTMSG_DEBUG(printf(" - [0x%04x] \n", u16PhyAddr));

        if (enCecSendMsg == POSTMSG)
        {
            msAPI_CEC_PostMsgToQueue(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, txbuf, 2);
        }
        else // if (enCecSendMsg == DIRECTMSG)
        {
            msAPI_CEC_PostMsg(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, txbuf, 2);
        }
    }
    else
    {
        CEC_POSTMSG_DEBUG(printf("\n"));
        if (enCecSendMsg == POSTMSG)
        {
            msAPI_CEC_PostMsgToQueue(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, NULL, 0);
        }
        else // if (enCecSendMsg == DIRECTMSG)
        {
            msAPI_CEC_PostMsg(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, 0, 0);
        }
    }
}

void msAPI_CEC_PostMsg_SystemAudioModeReq(EN_CEC_SEND_MSG enCecSendMsg, MS_U16 u16PhyAddr)
{
    MS_U8 txbuf[2];

    CEC_POSTMSG_DEBUG(printf("%s_<System Audio Mode Req>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - [0x%04x] \n", u16PhyAddr));

    txbuf[0] = (MS_U8)(u16PhyAddr>>8);
    txbuf[1] = (MS_U8)(u16PhyAddr&0x0F);

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, txbuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, txbuf, 2);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_ReportARCInitiated(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Report ARC Initiated>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_ARC_REPORT_ARC_INITIATED, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_ARC_REPORT_ARC_INITIATED, 0, 0);
    }
}

void msAPI_CEC_PostMsg_ReportARCTerminated(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Report ARC Terminated>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_ARC_REPORT_ARC_TERMINATED, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_ARC_REPORT_ARC_TERMINATED, 0, 0);
    }
}

void msAPI_CEC_PostMsg_RequestARCInitiation(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Request ARC Initiation>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_ARC_REQUEST_ARC_INITIATION, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_ARC_REQUEST_ARC_INITIATION, 0, 0);
    }
}

void msAPI_CEC_PostMsg_RequestARCTermination(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Request ARC Termination>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_ARC_REQUEST_ARC_TERMINATION, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_ARC_REQUEST_ARC_TERMINATION, 0, 0);
    }
}

void msAPI_CEC_PostMsg_RequestShortAudioDescriptor(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Request Short Audio Descriptor>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice));
    MS_U8 txbuf[4] = {2, 6, 7, 10};   //AC-3, AAC, DTS, DD+

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_SAC_REQUEST_SHORT_AUDIO_DESCRIPTOR, txbuf, 4);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_SAC_REQUEST_SHORT_AUDIO_DESCRIPTOR, txbuf, 4);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_FeatureAbort(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice,
                                    MsCEC_MSGLIST enMsg, MsCEC_MSG_ABORT_REASON enCmd)
{
    MS_U8 txbuf[2];

    txbuf[0] = enMsg;
    txbuf[1] = enCmd;

    CEC_POSTMSG_DEBUG(printf("%s_<Feature Abort>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));
    CEC_POSTMSG_DEBUG(printf(" opcode: 0x%x \n", txbuf[0] ));
    CEC_POSTMSG_DEBUG(printf(" reason:"));

    switch (txbuf[1])
    {
        case E_MSG_AR_UNRECOGNIZE_OPCDE:
            CEC_POSTMSG_DEBUG(printf(" Unrecognize Opcode"));
            break;

        case E_MSG_AR_CANNOTRESPOND:
            CEC_POSTMSG_DEBUG(printf(" Cannot Respond"));
            break;

        case E_MSG_AR_CANNOTPROVIDESCR:
            CEC_POSTMSG_DEBUG(printf(" Cannot Providescr"));
            break;

        case E_MSG_AR_INVALID_OPCODE:
            CEC_POSTMSG_DEBUG(printf(" Invalid Opcode"));
            break;

        case E_MSG_AR_REFUSED:
            CEC_POSTMSG_DEBUG(printf(" Refused"));
            break;

        case E_MSG_AR_IGNORED:
            CEC_POSTMSG_DEBUG(printf(" Ignored"));
            break;

        case E_MSG_AR_SUCCESSED:
            CEC_POSTMSG_DEBUG(printf(" Successed"));
            break;

        default:
            CEC_POSTMSG_DEBUG(printf(" Reserved"));
            break;
    }
    CEC_POSTMSG_DEBUG(printf(" (0x%x) \n", txbuf[1]));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_FEATURE_ABORT, (MS_U8 *)&txbuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_FEATURE_ABORT, (MS_U8 *)&txbuf, 2);
    }
}

void msAPI_CEC_PostMsg_AbortMessage(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Abort Message>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_ABORT_MESSAGE, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_ABORT_MESSAGE, 0, 0);
    }
}

//***************************************************************************************

