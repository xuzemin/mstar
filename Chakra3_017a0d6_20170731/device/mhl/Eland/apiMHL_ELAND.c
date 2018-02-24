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
/// file    mapi_mhl.c
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_MHL_ELAND_C_
#define _API_MHL_ELAND_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include "MsCommon.h"
#include "MsVersion.h"
#ifdef MSOS_TYPE_LINUX_KERNEL
#include <linux/string.h>
#else
#include <string.h>
#endif

#include "drvMHL_ELAND_st.h"
#include "apiMHL_ELAND.h"
#include "drvMHL_ELAND.h"

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define msg_mhl(x) x

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------
MHLInfo_S gMHLInfo;// = {0};

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

MS_U8 _msapi_mhl_CbusRcpProcess (MS_U8 rcpCode)
{
    MS_U8 statusCode = MSC_RCP_NO_ERROR;

    switch(rcpCode)
    {
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

        default:
            statusCode = MSC_RCP_INEFFECTIVE_KEY_CODE;
            break;
    }

    if ( statusCode == MSC_RCP_INEFFECTIVE_KEY_CODE )
    {
        //msg_mhl(printf("KeyCode not supported" ));
    }

    return(statusCode);
}

MS_U8 _msapi_mhl_CbusRapProcess (MS_U8 rapCode)
{
    MS_U8 statusCode  = MSC_RAP_NO_ERROR;

    switch(rapCode)
    {
        case MSC_RAP_POLL:
            break;

        case MSC_RAP_CONTENT_ON:
            //mdrv_mhl_SetTMDSTxOnOff(TRUE);
            break;

        case MSC_RAP_CONTENT_OFF:
            //mdrv_mhl_SetTMDSTxOnOff(FALSE);
            break;

        default:
            statusCode = MSC_RAP_UNRECOGNIZED_ACTION_CODE;
            break;
    }

    return( statusCode );
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_MHLSupportPath()
//  [Description]
//                  MHL support path
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_MHLSupportPath(MS_U8 ucSelect)
{
    mdrv_mhl_MHLSupportPath(ucSelect);
}

#define DEVICE_CAPASITY_REGISTER_SIZE 16
void mapi_mhl_LoadDevCap(MS_U8 *u8devcap)
{
    if (u8devcap == NULL)
    {
        msg_mhl(printf("DevCap is NULL!\r\n"));
    }
#if 0
    else if (sizeof(u8devcap) != DEVICE_CAPASITY_REGISTER_SIZE)
    {
        msg_mhl(printf("Size of DevCap is Wrong!\r\n"));
    }
#endif
    else
    {
        mdrv_mhl_LoadDevCap(u8devcap);
        msg_mhl(printf("Load DevCap Success!\r\n"));
    }
}


//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_PowerCtrl()
//  [Description]
//                  Control R-term power
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_PowerCtrl(E_MHL_POWERCTRL_Mode pctrl)
{
    gMHLInfo.MhlPowerStatus = pctrl;

    switch(pctrl)
    {
        case E_MHL_POWER_ON:
            msg_mhl(printf("MHL power on mode\r\n"));
            mdrv_mhl_PowerOn();
            break;
        case E_MHL_POWER_STANDBY:
            msg_mhl(printf("MHL power standby mode\r\n"));
            memset(&(gMHLInfo.MhlCbusInfo), 0, sizeof(gMHLInfo.MhlCbusInfo));
            mdrv_mhl_PowerStandby(GET_MHL_CABLE_PLUGGED());
            break;
        case E_MHL_POWER_DOWN:
            msg_mhl(printf("MHL power down mode\r\n"));
            memset(&(gMHLInfo.MhlCbusInfo), 0, sizeof(gMHLInfo.MhlCbusInfo));
            mdrv_mhl_PowerDown();
            break;
        default:
            msg_mhl(printf("Wrong MHL power mode\r\n"));
            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CableDetect()
//  [Description]
//                  Get MHL cable detection flag
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_BOOL mapi_mhl_CableDetect(void)
{
    return GET_MHL_CABLE_PLUGGED();
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CbusStatus()
//  [Description]
//                  Get MHL CBUS connetion flag
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_BOOL mapi_mhl_CbusStatus(void)
{
    return GET_MHL_CBUS_CONNECT();
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CableDetect()
//  [Description]
//                  MHL cable detection
//  [Arguments]:
//
//  [Return]:
//                  TRUE: MHL cable plugged
//                  FALSE: MHL cable unplugged
//**************************************************************************
MS_BOOL _mapi_mhl_CableDetect(void)
{
    if(mdrv_mhl_CableDetect())
    {
        if(!GET_MHL_CABLE_PLUGGED())
        {
            mdrv_mhl_DriverControl(MHL_CABLE_PLUGGED);

            SET_MHL_CABLE_PLUGGED();
            msg_mhl(printf("** MHL Cable plugged!!\r\n"));
        }
    }
    else
    {
        if(GET_MHL_CABLE_PLUGGED() ||(!GET_MHL_PORT_ON_FLAG()))
        {
            gMHLInfo.MhlCbusInfo.curIdx = 0;
            SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);
            SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_NO_ERROR);
            CLR_CBUS_CABLE_FLAG();
            CLR_CBUS_LINK_CHECK();
            CLR_MHL_RECEIVE_FLAG();

            mdrv_mhl_DriverControl(MHL_CABLE_UNPLUGGED);

            msg_mhl(printf("** MHL Cable unplugged~~\r\n"));
        }
    }

    if(!GET_MHL_PORT_ON_FLAG())
    {
        mdrv_mhl_CbusIsolate(FALSE);

        mapi_mhl_CbusControl(MHL_CBUS_FLOATING_OFF);

        SET_MHL_PORT_ON_FLAG();
    }

    return GET_MHL_CABLE_PLUGGED();
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_SetControlTimer()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_SetControlTimer(MS_U8 ucTime)
{
    if(ucTime == 0)
    {
        CLR_MHL_TIME_OUT_FLAG();
    }
    else
    {
        SET_MHL_TIME_OUT_FLAG();
    }

#if(DMHL_TIMER_POLLING_INTERVAL)
    SET_MHL_DEBOUNCE_TIMER(ucTime *CBUS_TIMER_SECOND_COUNT);

#else
    SET_MHL_TIMEOUT_TIMER(ucTime);

#endif
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusIntCB()
//  [Description]
//                  MHL Cbus Interrupt Call Back function
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

void _mapi_mhl_CbusIntCB(void)
{
    MS_BOOL bflag;
    CbusReq_S preq;

    if(mdrv_mhl_CbusIsMscMsgReceived()) // received valid message
    {
        SET_MHL_RECEIVE_MSC();

        // Read received Cbus packet from register
        mdrv_mhl_CbusIntCB(&preq, &bflag);

#if DMHL_CTS
        // CTS 6.3.10.5
        #if 0
        if((preq.cmd != MSC_GET_MSC_ERRORCODE) && (preq.rcState == 0))
        {
            SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_NO_ERROR)
        }
        #endif

        // CTS 6.3.12.1 ~ 6.3.12.9
        if(preq.rcState == CBUS_RECEIVE_TIMEOUT)
        {
            SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_PEER_TIMEOUT);
        }

        // CTS 6.3.11.4 ~ 6.3.11.7
        if((GET_MHL_CBUS_STATE() != CBUS_STATE_SENT) &&
            ((preq.cmd == MSC_ACK) || (preq.cmd == MSC_NACK) || (preq.cmd == MSC_ABORT) ||(preq.cmd == MSC_EOF)))
        {
            SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_INVALID_OPCODE);

            if((preq.cmd != MSC_ABORT))
            {
                mdrv_mhl_CbusReply(MSC_ABORT, FALSE, 0);
            }
        }
#endif
        if((preq.cmd != MSC_ACK) && (preq.cmd != MSC_NACK) && (preq.cmd != MSC_ABORT))
        {
            memcpy(&(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX)), &preq, sizeof(CbusReq_S));
            gMHLInfo.MhlCbusInfo.bIsCmdinDataField = bflag;

            switch(GET_MHL_CBUS_STATE())
            {
                case CBUS_STATE_IDLE:
                case CBUS_STATE_SENT:
                    SET_MHL_QUEUE_STATE(MHL_CBUS_RX_QUEUE_INDEX, CBUS_REQ_RECEIVED);
                    SET_MHL_CBUS_STATE(CBUS_STATE_RECEIVED);
                    break;
                default:
                    SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);
                    break;
            }
        }
        else
        {
#if DMHL_CTS
            // CTS 6.3.6.3
            if((GET_MHL_CBUS_STATE() == CBUS_STATE_SENT) && ((preq.cmd == MSC_ACK) && bflag))
            {
                mdrv_mhl_CbusReply(MSC_ABORT, FALSE, 0);
                SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_PROTOCOL_ERROR);
            }

            // CTS 6.3.6.5
            if((GET_MHL_CBUS_STATE() == CBUS_STATE_SENT) && (preq.cmd == MSC_ABORT))
            {
                SET_MHL_RECEIVE_ABORT();
            }

            // CTS 6.3.6.4 & 6.3.6.5
            if((preq.rcState != CBUS_RECEIVE_TIMEOUT) && (preq.cmd != MSC_ABORT))
#endif
            {
                if(preq.cmd == MSC_ACK)
                {
                    SET_MHL_RECEIVE_ACK();
                }

                SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);
            }
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CBusProcessMSCSubCmd(MS_U8 cmd)
//  [Description]:
//                  MHL Cbus process MSC sub command
//  [Arguments]:
//                  cmd: command
//                  databuf: data
//  [Return]:
//
//**************************************************************************
MS_BOOL _mapi_mhl_CBusProcessMSCSubCmd (MS_U8 ucCmd)
{
    MS_BOOL bIndex = TRUE;

    switch(ucCmd)
    {
        case MSC_MSG_RCP:
        case MSC_MSG_RAP:
            SET_MHL_QUEUE_STATE(MHL_CBUS_RX_QUEUE_INDEX, CBUS_REQ_RECEIVED);
            SET_MHL_CBUS_STATE(CBUS_STATE_RECEIVED);
            SET_MHL_RECEIVE_RCP();
            SET_MHL_RECEIVE_RAP();

            break;

        case MSC_MSG_RCPK:

            break;

        case MSC_MSG_RCPE:

            break;

        case MSC_MSG_RAPK:

            break;

        default:

            break;
    }

    return bIndex;
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusIntHandler()
//  [Description]
//                  MHL Cbus Interrupt Handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_CbusIntHandler(void)
{
    //MS_U8 ucCount = 0;
    MS_BOOL bretAck = TRUE;
    //CbusReq_S req;

    if(GET_MHL_CBUS_STATE() == CBUS_STATE_RECEIVED) // received valid message
    {
        // Begin processing received packet, set Cbus state idle and free queue
        SET_MHL_QUEUE_STATE(MHL_CBUS_RX_QUEUE_INDEX, CBUS_REQ_IDLE);
        SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);

        if(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).rcState == CBUS_RECEIVE_NORMAL) // received normally
        {
            switch(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).cmd)
            {
                case MSC_ACK:
                    SET_MHL_CBUS_STATE(CBUS_STATE_ACK);
                    break;

                case MSC_NACK:
                    break;

                case MSC_ABORT: // wait 2 sec before starting a new Cbus transaction after receiving an ABORT, Chapter 13.10.3
                    SET_MHL_RECEIVE_ABORT();
                    break;

                case MSC_WRITE_STAT_OR_SET_INT:
            #if DMHL_CTS
                    // CTS 6.3.11.8 && 6.3.11.11
                    if(gMHLInfo.MhlCbusInfo.bIsCmdinDataField)
                    {
                        SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_PROTOCOL_ERROR);
                        bretAck = FALSE;
                    }
            #endif

                    if(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[0] == 0x31)
                    {
                        mdrv_mhl_CBusClockModeSwitch(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[1] &(BIT(2) |BIT(1) |BIT(0)));
                    }

                    mdrv_mhl_CbusReply(bretAck ? MSC_ACK : MSC_ABORT, FALSE, 0);

                    break;

                case MSC_READ_DEVCAP:
#if 1 //1: SW mode, 0: HW mode
                    // HW auto reply, REG_MHL_CBUS_23[10] = 1
            #if DMHL_CTS
                    // CTS 6.3.11.8
                    if(gMHLInfo.MhlCbusInfo.bIsCmdinDataField)
                    {
                        mdrv_mhl_CbusReply(MSC_ABORT, FALSE, 0);
                        SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_PROTOCOL_ERROR);
                    }
                    else
                    {
                        // CTS 6.3.11.9
                        if(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[0] <= 0x0F)
                        {
                            mdrv_mhl_CbusReply(MSC_ACK, TRUE, mdrv_mhl_GetDevCap(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[0]));
                            SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_NO_ERROR);
                        }
                        else
                        {
                            mdrv_mhl_CbusReply(MSC_ABORT, FALSE, 0);
                            SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_BAD_OFFSET);
                        }
                    }
           #else
                    mdrv_mhl_CbusReply(MSC_ACK, TRUE, mdrv_mhl_GetDevCap(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[0]));
           #endif // #if DMHL_CTS
#endif
                    break;

                case MSC_GET_STATE:
                    mdrv_mhl_CbusReply(MSC_GET_STATE, TRUE, mdrv_mhl_GetDevCap(0)); // DevCap register 0x00
                    break;

                case MSC_GET_VENDOR_ID:
                    mdrv_mhl_CbusReply(MSC_GET_VENDOR_ID, TRUE, DMHL_VENDOR_ID);
                    break;

                case MSC_MSC_MSG:
            #if DMHL_CTS
                    // CTS 6.3.11.22 & 6.3.11.24
                    if(gMHLInfo.MhlCbusInfo.bIsCmdinDataField)
                    {
                        SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_PROTOCOL_ERROR);
                        bretAck = FALSE;
                    }
                    else
                    {
                        bretAck = _mapi_mhl_CBusProcessMSCSubCmd(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[0]);
                    }
            #endif // #if DMHL_CTS

                    mdrv_mhl_CbusReply(bretAck ? MSC_ACK : MSC_ABORT, FALSE, 0);

                    break;

                case MSC_WRITE_BURST:
            #if DMHL_CTS
                    // CTS 6.3.11.20
                    if(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[0] + (GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).len -2) > (0x40 + MHL_MSC_SCRATCHPAD_SIZE))
                    {
                        SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_BAD_OFFSET);
                        bretAck = FALSE;
                    }

                    // CTS 6.3.11.14
                    if(gMHLInfo.MhlCbusInfo.bIsCmdinDataField)
                    {
                        SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_PROTOCOL_ERROR);
                        bretAck = FALSE;
                    }
            #endif // #if DMHL_CTS
                    mdrv_mhl_CbusReply(bretAck ? MSC_ACK : MSC_ABORT, FALSE, 0);

                    break;

                case MSC_GET_MSC_ERRORCODE:
                    mdrv_mhl_CbusReply(MSC_GET_MSC_ERRORCODE, TRUE, GET_MHL_CBUS_ERROE_CODE());
                    break;

                case MSC_GET_DDC_ERRORCODE:
                    mdrv_mhl_CbusReply(MSC_GET_DDC_ERRORCODE, TRUE, mdrv_mhl_GetDDCErrorCode());
                    break;

                case MSC_GET_SC1_ERRORCODE:
                case MSC_GET_SC3_ERRORCODE:
                    // CTS 6.3.11.1
                    SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_BAD_OFFSET);
                    //mdrv_mhl_CbusReply(MSC_ACK, TRUE, MSC_ERRORCODE_NO_ERROR);
                    break;

                case MSC_EOF:
                    break;

                // CTS 6.3.16.1 ~ 6.3.16.2
                case MSC_SET_HPD:
                case MSC_CLR_HPD:
                    mdrv_mhl_CbusReply(MSC_ABORT, FALSE, 0);
                    SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_INVALID_OPCODE);
                    break;

                default:
                    // CTS 6.3.6.2 & 6.3.11.2
                    mdrv_mhl_CbusReply(MSC_ABORT, FALSE, 0);
                    SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_INVALID_OPCODE);
                    break;
            }
        }
        else // received message is not valid
        {
            msg_mhl(printf("**Unknow: 0x%x \r\n", GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).cmd ));
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusQueueMscRxReply(BYTE subCmd, BYTE databuf)
//  [Description]
//                  MHL Cbus Reply MSC RCP or RAP into Queue
//  [Arguments]:
//                  subCmd: MSC subcommands
//                  databuf: command code
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL _mapi_mhl_CbusQueueMscRxReply(MS_U8 subCmd, MS_U8 databuf)
{
    CbusReq_S req;

    req.cmd = MSC_MSC_MSG;
    req.msgData[0] = subCmd;
    req.msgData[1] = databuf;
    req.len = 2;
    req.rcState = FALSE;
    req.reqStatus = CBUS_REQ_RECEIVED;

    memcpy(&(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX)), &req, sizeof(CbusReq_S));

    return TRUE;
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusRcpReply
//  [Description]
//                  MHL Cbus RCP response
//  [Arguments]:
//                  statusCode: RCP status code
//                  keyCode: RCP key code
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL _mapi_mhl_CbusRcpReply (MS_U8 statusCode, MS_U8 keyCode)
{
    if(statusCode != MSC_RCP_NO_ERROR)
    {
        return _mapi_mhl_CbusQueueMscRxReply(MSC_MSG_RCPE, statusCode);
    }
    else
    {
        return _mapi_mhl_CbusQueueMscRxReply(MSC_MSG_RCPK, keyCode);
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusRapReply
//  [Description]
//                  MHL Cbus RAP response
//  [Arguments]:
//                  statusCode: RAP status code
//
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL _mapi_mhl_CbusRapReply(MS_U8 statusCode)
{
    return _mapi_mhl_CbusQueueMscRxReply(MSC_MSG_RAPK, statusCode);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CbusProcessMSCSubCmd()
//  [Description]
//                  MHL Cbus process MSC sub-command
//  [Arguments]:
//                  subcmd: MSC sub-command
//                  subdata: MSC sub-data
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_CbusProcessMSCSubCmd(MS_U8 subcmd, MS_U8 subdata)
{
    MS_U8 status;

    switch(subcmd)
    {
        case MSC_MSG_RCP:
            status = _msapi_mhl_CbusRcpProcess(subdata);
            _mapi_mhl_CbusRcpReply(status, subdata);
            break;

        case MSC_MSG_RCPK:
        case MSC_MSG_RCPE:

            break;

        case MSC_MSG_RAP:
            status = _msapi_mhl_CbusRapProcess(subdata);
            _mapi_mhl_CbusRapReply(status);
            break;

        case MSC_MSG_RAPK:

            break;

        default: // MSGE

            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusStatus()
//  [Description]:
//                  MHL Cbus status
//  [Arguments]:
//
//  [Return]:
//                  TRUE: MHL Cbus connected
//                  FALSE: MHL Cbus disconnected
//**************************************************************************
MS_BOOL _mapi_mhl_CbusStatus(void)
{
    MS_U16 status;

    status = mdrv_mhl_CbusStatus();

    if(GET_MHL_CBUS_CONNECT() && ((status & 0x03) != 0x03))
    {
        SET_MHL_CBUS_STATE(CBUS_STATE_IDLE); // returm to idle state
    }

    if((status & 0x03) == 0x03)
    {
        SET_MHL_CBUS_CONNECT();
    }
    else
    {
        CLR_MHL_CBUS_CONNECT();
    }

    return GET_MHL_CBUS_CONNECT();
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CBusGetQueueIndex()
//  [Description]:
//                  MHL Cbus get transmitting queue index
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_U8 _mapi_mhl_CBusGetQueueIndex(MS_U8 ucIndex)
{
    MS_U8 uctemp = 0;

    // Check Rx queue have packet transmit success or not
    if(GET_MHL_QUEUE_STATE(MHL_CBUS_RX_QUEUE_INDEX) != CBUS_REQ_IDLE)
    {
        return MHL_CBUS_RX_QUEUE_INDEX;
    }

    // Check Tx queue have packet transmit success or not, search start  from current index
    for(uctemp =0; uctemp <(MHL_CBUS_TOTAL_QUEUE_NUM -1); uctemp++)
    {
        if(GET_MHL_QUEUE_STATE((ucIndex +uctemp) %(MHL_CBUS_TOTAL_QUEUE_NUM -1)) != CBUS_REQ_IDLE)
        {
            return ((ucIndex +uctemp) %(MHL_CBUS_TOTAL_QUEUE_NUM -1));
        }
    }

    return MHL_CBUS_TOTAL_QUEUE_NUM;
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusTxHandler()
//  [Description]
//                  MHL Cbus handle send MSC message
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_CbusTimerHandler(MS_U32 usTimer)
{
#if(DMHL_TIMER_POLLING_INTERVAL)
    MS_U32 ustemp = (GET_MHL_TIMEOUT_TIMER() +GET_MHL_DEBOUNCE_TIMER()) %CBUS_TIMER_CONTROL_MASK;   // Departure time

    // Current time
    usTimer = usTimer %CBUS_TIMER_CONTROL_MASK;

    // Compare current time and previous time, reset if too different
    // In normal case, current time larger than previous time
    if((usTimer +CBUS_TIMER_CONTROL_MASK -GET_MHL_TIMEOUT_TIMER()) %CBUS_TIMER_CONTROL_MASK > (CBUS_TIMER_CONTROL_MASK /2))
    {
        // Reset Timer
        CLR_MHL_TIME_OUT_FLAG();
    }

    if(usTimer != GET_MHL_TIMEOUT_TIMER())
    {
        // Departure time minus current time
        ustemp = (ustemp +CBUS_TIMER_CONTROL_MASK -usTimer) %CBUS_TIMER_CONTROL_MASK;

        if(ustemp > (CBUS_TIMER_CONTROL_MASK /2))   // Current time larger than departure time
        {
            // CTS 6.3.6.4 verify DUT receives result timeout => couldn's send any MSC packet within 2sec
            // CTS 6.3.6.5 verify no next command until hold-off after Abort seen => couldn's send any MSC packet within 2sec
            if(GET_MHL_TIME_OUT_FLAG())
            {
                msg_mhl(printf("**MHL TOUT"));
                SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);
                SET_MHL_QUEUE_STATE(gMHLInfo.MhlCbusInfo.curIdx, CBUS_REQ_IDLE);
            }

            _mapi_mhl_SetControlTimer(0);
        }
        else
        {
            SET_MHL_DEBOUNCE_TIMER(ustemp);
        }

        SET_MHL_TIMEOUT_TIMER(usTimer);
    }

#else
    usTimer = usTimer;

    if(GET_MHL_DEBOUNCE_TIMER() > 0)
    {
        DEC_MHL_DEBOUNCE_TIMER();
    }

    // CTS 6.3.6.4 verify DUT receives result timeout => couldn's send any MSC packet within 2sec
    // CTS 6.3.6.5 verify no next command until hold-off after Abort seen => couldn's send any MSC packet within 2sec
    if(GET_MHL_TIME_OUT_FLAG() &&(!GET_MHL_TIMEOUT_TIMER()))
    {
        msg_mhl(printf("**MHL TOUT"));
        SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);
        SET_MHL_QUEUE_STATE(gMHLInfo.MhlCbusInfo.curIdx, CBUS_REQ_IDLE);

        _mapi_mhl_SetControlTimer(0);
    }

#endif
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusGetLeastFlag()
//  [Description]:
//                  MHL Cbus get the least True flag in index
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_U8 _mapi_mhl_CbusGetLeastFlag(MS_U8 unindex)
{
    MS_U8 uctemp = BIT(0);

    if(unindex == 0)
    {
        return unindex;
    }

    while(!(unindex &uctemp))
    {
        uctemp = uctemp <<1;
    }

    return uctemp;
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusLinkCheck()
//  [Description]
//                  MHL Cbus handle send MSC message
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_CbusLinkCheck(void)
{
    MS_U8 ucindex = GET_CBUS_LINK_CHECK() ^MHL_CBUS_LINK_MASK;

    if(ucindex > 0)
    {
        SET_CBUS_LINK_CHECK(GET_CBUS_LINK_CHECK() |_mapi_mhl_CbusGetLeastFlag(ucindex));

        msg_mhl(printf("**MHL Cbus Receive ACK for Link\r\n"));
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusRxHandler()
//  [Description]
//                  MHL Cbus reply the received MSC message
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_CbusRxHandler(void)
{
    MS_U8 uctemp = 0;

    if(GET_MHL_RECEIVE_MSC())
    {
        if(GET_MHL_TIME_OUT_FLAG())
        {
            _mapi_mhl_SetControlTimer(0);   // timeout reset.
        }

        CLR_MHL_RECEIVE_MSC();
    }

    if(GET_MHL_RECEIVE_ACK())
    {
        if(GET_MHL_QUEUE_STATE(MHL_CBUS_RX_QUEUE_INDEX) != CBUS_REQ_IDLE)
        {
            SET_MHL_QUEUE_STATE(MHL_CBUS_RX_QUEUE_INDEX, CBUS_REQ_IDLE);
        }
        else
        {
            SET_MHL_QUEUE_STATE(gMHLInfo.MhlCbusInfo.curIdx, CBUS_REQ_IDLE);
        }

        uctemp = _mapi_mhl_CBusGetQueueIndex(gMHLInfo.MhlCbusInfo.curIdx);

        // Update current index to search index, but not Rx queue index
        if(uctemp < MHL_CBUS_RX_QUEUE_INDEX)
        {
            gMHLInfo.MhlCbusInfo.curIdx = uctemp;
        }

        _mapi_mhl_CbusLinkCheck();

        SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);

        CLR_MHL_RECEIVE_ACK();
    }

    if(GET_MHL_RECEIVE_ABORT())
    {
        _mapi_mhl_SetControlTimer(CBUS_ABORT_PADING_SECS);

        CLR_MHL_RECEIVE_ABORT();
    }

    if(GET_MHL_RECEIVE_RCP() ||GET_MHL_RECEIVE_RAP())
    {
        switch(GET_MHL_QUEUE_STATE(MHL_CBUS_RX_QUEUE_INDEX))
        {
            case CBUS_REQ_IDLE:
            case CBUS_REQ_PENDING:
            case CBUS_REQ_SENT:

                break;

            case CBUS_REQ_RECEIVED:
                _mapi_mhl_CbusProcessMSCSubCmd(GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[0], GET_MHL_CBUS_QUEUE(MHL_CBUS_RX_QUEUE_INDEX).msgData[1]);
                SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);

                break;

            default:

                break;
        }

        CLR_MHL_RECEIVE_RCP();
        CLR_MHL_RECEIVE_RAP();
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusTxHandler()
//  [Description]
//                  MHL Cbus handle send MSC message
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_CbusTxHandler(void)
{
    MS_U8 ucindex = 0;

    switch(GET_MHL_CBUS_STATE())
    {
        case CBUS_STATE_IDLE:
            ucindex = _mapi_mhl_CBusGetQueueIndex(gMHLInfo.MhlCbusInfo.curIdx);

            if((ucindex < MHL_CBUS_TOTAL_QUEUE_NUM) && !GET_MHL_DEBOUNCE_TIMER())
            {
                mdrv_mhl_DriverControl(MHL_CBUS_TEST_RASING);

                if(mdrv_mhl_CBusWriteCmd(&(GET_MHL_CBUS_QUEUE(ucindex))))
                {
                    // Retry send packet twice
                    if(GET_MHL_QUEUE_STATE(ucindex) == CBUS_REQ_SENT)
                    {
                        SET_MHL_QUEUE_STATE(ucindex, CBUS_REQ_IDLE);
                        msg_mhl(printf("MHL Tx retry"));
                    }
                    else if(GET_MHL_QUEUE_STATE(ucindex) > CBUS_REQ_SENT)
                    {
                        SET_MHL_QUEUE_STATE(ucindex, CBUS_REQ_SENT);
                    }

                    // Update current index to search index, but not Rx queue index
                    if(ucindex < MHL_CBUS_RX_QUEUE_INDEX)
                    {
                        gMHLInfo.MhlCbusInfo.curIdx = ucindex;
                    }

                    SET_MHL_CBUS_STATE(CBUS_STATE_SENT);
                    _mapi_mhl_SetControlTimer(CBUS_COMMAND_TIMEOUT_SECS);
                }
            }

            break;

        case CBUS_STATE_SENT:
        case CBUS_STATE_WAITING_ACK:
        case CBUS_STATE_RECEIVED:

            break;

        case CBUS_STATE_ACK:

            break;

        default:
            SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);
            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusQueueMscTxRequest(BYTE ucIndex, CbusReq_S *pReq)
//  [Description]
//                  MHL Cbus Request a MSC Cmd into Queue
//  [Arguments]:
//                  ucIndex: Current queue index
//                  pReq: Command buffer
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL _mapi_mhl_CbusQueueMscTxRequest(MS_U8 ucIndex, CbusReq_S *pReq)
{
    MS_U8 uctemp = ucIndex;

    // Search free queue
    for(uctemp = 0; uctemp <(MHL_CBUS_TOTAL_QUEUE_NUM -1); uctemp++)
    {
        if(GET_MHL_QUEUE_STATE((ucIndex +uctemp +1) %(MHL_CBUS_TOTAL_QUEUE_NUM -1)) == CBUS_REQ_IDLE)
        {
            uctemp = (ucIndex +uctemp +1) %(MHL_CBUS_TOTAL_QUEUE_NUM -1);

            break;
        }
    }

    if(uctemp == (MHL_CBUS_TOTAL_QUEUE_NUM -1)) // No free queue
    {
        return FALSE;
    }

    if(GET_MHL_QUEUE_STATE((uctemp +MHL_CBUS_TOTAL_QUEUE_NUM -2) %(MHL_CBUS_TOTAL_QUEUE_NUM -1)) == CBUS_REQ_IDLE)
    {
        uctemp = (uctemp +MHL_CBUS_TOTAL_QUEUE_NUM -2) %(MHL_CBUS_TOTAL_QUEUE_NUM -1);
    }

    memcpy(&(GET_MHL_CBUS_QUEUE(uctemp)), pReq, sizeof(CbusReq_S));

    return TRUE;
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_Cbus_SetHPDState()
//  [Description]:
//                  MHL Cbus set HPD state
//  [Arguments]:
//                  TRUE: SET_HPD
//                  FALSE: CLR_HPD
//  [Return]:
//
//**************************************************************************
MS_BOOL _mapi_mhl_Cbus_SetHPDState(MS_BOOL bflag)
{
    MS_BOOL bIndex;
    CbusReq_S req;

    if(GET_MHL_HPD_SET_FLAG() == bflag)
    {
        return TRUE;
    }

    req.cmd = (bflag == TRUE ? MSC_SET_HPD : MSC_CLR_HPD);
    req.len = 0;
    req.reqStatus = CBUS_REQ_PENDING;

    bIndex = _mapi_mhl_CbusQueueMscTxRequest(gMHLInfo.MhlCbusInfo.curIdx, &req);

    if(bIndex)
    {
        if(bflag)
        {
            SET_MHL_HPD_SET_FLAG();
        }
        else
        {
            CLR_MHL_HPD_SET_FLAG();
        }
    }

    return bIndex;
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusWriteStatusOrSetInt(BYTE addr, BYTE val)
//  [Description]:
//                  MHL Cbus write status or set interrupt
//  [Arguments]:
//
//  [Return]:
//                  TRUE: Cbus message send successfully
//                  FALSE: Cbus message send fail
//**************************************************************************
MS_BOOL _mapi_mhl_CbusWriteStatusOrSetInt(MS_U8 ucAddr, MS_U8 ucValue)
{
    CbusReq_S req;

    req.cmd = MSC_WRITE_STAT_OR_SET_INT;
    req.msgData[0] = ucAddr;
    req.msgData[1] = ucValue;
    req.len = 2;
    req.reqStatus = CBUS_REQ_PENDING;

    if(!_mapi_mhl_CbusQueueMscTxRequest(gMHLInfo.MhlCbusInfo.curIdx, &req))
    {
        return FALSE;
    }

    return TRUE;
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_Cbus_SetDCapRdy()
//  [Description]:
//                  MHL Cbus set capbility ready
//  [Arguments]:
//                  TRUE: Enable
//                  FALSE: Disable
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_Cbus_SetDCapRdy(MS_BOOL bflag)
{
    MS_BOOL bIndex = FALSE;

    if(bflag)
    {
        //set DCAP_RDY bit
        bIndex = _mapi_mhl_CbusWriteStatusOrSetInt(0x30, BIT(0));
    }

    if(bIndex || (!bflag))
    {
        if(bflag)
        {
            SET_MHL_DCAP_RDY_FLAG();
        }
        else
        {
            CLR_MHL_DCAP_RDY_FLAG();
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_Cbus_SetPathEn()
//  [Description]:
//                  MHL Cbus set path enable
//  [Arguments]:
//                  TRUE: Enable
//                  FALSE: Disable
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_Cbus_SetPathEn(MS_BOOL bflag)
{
    MS_BOOL bIndex = FALSE;

    bIndex = _mapi_mhl_CbusWriteStatusOrSetInt(0x31, bflag ? BIT(3) : 0);

    if(bIndex || (!bflag))
    {
        if(bflag)
        {
            SET_MHL_PATH_EN_FLAG();
        }
        else
        {
            CLR_MHL_PATH_EN_FLAG();
        }

        mdrv_mhl_Cbus_SetPathEn(bflag);
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_Cbus_SetDCapChg(Bool bflag)
//  [Description]:
//                  MHL Cbus set path enable
//  [Arguments]:
//                  TRUE: Enable
//                  FALSE: Disable
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_Cbus_SetDCapChg(MS_BOOL bflag)
{
    MS_BOOL bIndex = FALSE;

    if(bflag)
    {
        bIndex = _mapi_mhl_CbusWriteStatusOrSetInt(0x20, BIT(0));
    }

    if (bIndex || (!bflag))
    {
        if(bflag)
        {
            SET_MHL_DCAP_CHG_FLAG();
        }
        else
        {
            CLR_MHL_DCAP_CHG_FLAG();
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusConnectionCheck()
//  [Description]:
//                  MHL Cbus connection check
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mapi_mhl_CbusConnectionCheck(void)
{
    static MS_BOOL bCbusConnected = FALSE;
    MS_U8 ucindex = 0;
    if (bCbusConnected != GET_MHL_CBUS_CONNECT())
    {
        bCbusConnected = GET_MHL_CBUS_CONNECT();
        if(!bCbusConnected)
        {
            gMHLInfo.MhlCbusInfo.curIdx = 0;
            SET_MHL_CBUS_STATE(CBUS_STATE_IDLE);
            SET_MHL_CBUS_ERROE_CODE(MSC_ERRORCODE_NO_ERROR);
            CLR_CBUS_LINK_FLAG();
            CLR_CBUS_LINK_CHECK();
            CLR_MHL_RECEIVE_FLAG();

            _mapi_mhl_SetControlTimer(0);

            mdrv_mhl_DriverControl(MHL_CBUS_UNCONNECTION);

            memset(&gMHLInfo.MhlCbusInfo.request, 0, sizeof(gMHLInfo.MhlCbusInfo.request));

            if(!mdrv_mhl_CableDetect())
            {
                mdrv_mhl_DriverControl(MHL_CABLE_UNPLUGGED);
            }

            msg_mhl(printf("** MHL Cbus disconnected @@\r\n"));
        }
        else
        {
            SET_MHL_DEBOUNCE_TIMER(150); // reset 100msec

            mdrv_mhl_DriverControl(MHL_CBUS_CONNECTION);

            mdrv_mhl_DriverControl(MHL_CBUS_TEST_FALLING);

            msg_mhl(printf("** MHL Cbus connected~~ \r\n"));
        }
    }

    if(bCbusConnected)
    {
        ucindex = GET_CBUS_LINK_FLAG() ^MHL_CBUS_LINK_MASK;
        if(ucindex > 0)
        {
            switch(_mapi_mhl_CbusGetLeastFlag(ucindex))
            {
                case CBUS_HPD_SET_FLAG:
                    _mapi_mhl_Cbus_SetHPDState(TRUE);
                    break;

                case CBUS_DCAP_RDY_FLAG:
                    _mapi_mhl_Cbus_SetDCapRdy(TRUE);
                    break;

                case CBUS_PATH_EN_FLAG:
                    _mapi_mhl_Cbus_SetPathEn(TRUE);
                    break;

                case CBUS_DCAP_CHG_FLAG:
                    _mapi_mhl_Cbus_SetDCapChg(TRUE);
                    break;

                default:

                    break;
            };
        }

        if(mdrv_mhl_CBusStablePolling(GET_CBUS_LINK_FINISH()))
        {
            mdrv_mhl_CbusIsolate(TRUE);

            CLR_MHL_PORT_ON_FLAG();
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_Init()
//  [Description]
//                  MHL init
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_init(MS_U8 *edid, MS_U8 *DevCap)
{
    memset(&gMHLInfo, 0, sizeof(gMHLInfo));
    msg_mhl(printf("mapi_mhl_init()\r\n"));
    mdrv_mhl_Set_IIC_16BMode();

    mdrv_mhl_init(edid, DevCap);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_handler()
//  [Description]
//                  MHL handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_handler(void)
{
    MS_U32 ulTimer = MsOS_GetSystemTime();

    if(_mapi_mhl_CableDetect())
    {
        if(GET_MHL_CBUS_CONNECT())
        {
            _mapi_mhl_CbusIntCB();
            _mapi_mhl_CbusIntHandler();
            _mapi_mhl_CbusRxHandler();
        }

        _mapi_mhl_CbusTimerHandler(ulTimer);

        if(_mapi_mhl_CbusStatus())
        {
            _mapi_mhl_CbusTxHandler();
        }

        _mapi_mhl_CbusConnectionCheck();
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mapi_mhl_CbusMscMsgSubCmdSend
//  [Description]
//                  MHL Cbus MSC Send RCP or RAP
//  [Arguments]:
//                  subCmd: MSC subcommands
//                  databuf: command code
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL _mapi_mhl_CbusMscMsgSubCmdSend (MS_U8 subCmd, MS_U8 databuf)
{
    CbusReq_S req;

    req.cmd = MSC_MSC_MSG;
    req.msgData[0]  = subCmd;
    req.msgData[1]  = databuf;
    req.len = 2;
    req.reqStatus = CBUS_REQ_PENDING;

    return (_mapi_mhl_CbusQueueMscTxRequest(gMHLInfo.MhlCbusInfo.curIdx, &req));
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_SendRAPCmd
//  [Description]
//                  MHL Cbus MSC Send RAP Command
//  [Arguments]:
//
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL mapi_mhl_SendRAPCmd(MS_U8 databuf)
{
    return _mapi_mhl_CbusMscMsgSubCmdSend(MSC_MSG_RAP, databuf);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_SendRCPCmd
//  [Description]
//                  MHL Cbus MSC Send RCP Command
//  [Arguments]:
//
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL mapi_mhl_SendRCPCmd(MS_U8 databuf)
{
    return _mapi_mhl_CbusMscMsgSubCmdSend(MSC_MSG_RCP, databuf);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_SendRCP_PressRelease_Cmd
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL mapi_mhl_SendRCP_PressRelease_Cmd(MS_U8 u8RCPKey, MS_BOOL bIsRelease)
{
    //bIsRelease
    //0: press
    //1: release
    return mapi_mhl_SendRCPCmd((u8RCPKey|(bIsRelease<<7)));
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_SendWriteBurst
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//                  TRUE: success
//                  FALSE: fail
//**************************************************************************
MS_BOOL mapi_mhl_SendWriteBurst(MS_U8 ucAddr, MS_U8 ucLength, MS_U8 *buffer)
{
    MS_U8 uctemp = 0;
    CbusReq_S req;

    req.cmd = MSC_WRITE_BURST;
    req.msgData[0] = ucAddr;

    for(uctemp = 0;uctemp <ucLength;uctemp++)
    {
        req.msgData[uctemp +1] = buffer[uctemp];
    }

    req.len = ucLength +1; // offset + data packets
    req.reqStatus = CBUS_REQ_PENDING;

    return (_mapi_mhl_CbusQueueMscTxRequest(gMHLInfo.MhlCbusInfo.curIdx, &req));
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CbusIsolate
//  [Description]
//                  MHL Cbus isolate
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_CbusIsolate(void)
{
    CLR_MHL_PORT_ON_FLAG();

    mdrv_mhl_CbusIsolate(TRUE);

    _mapi_mhl_SetControlTimer(0);
}

#if(DMHL_WAKE_UP_PULSE_INT)
//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CbusWakeupIntSetting()
//  [Description]
//                  MHL Cbus isolate
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_CbusWakeupIntSetting(void)
{
    mdrv_mhl_DriverControl(MHL_CBUS_PM_MODE);
}

#endif

#if(DMHL_CTS_SEND_MSC)
//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CbusSendCommand()
//  [Description]
//                  For CTS send a MSC command
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_CbusSendCommand(void)
{
    _mapi_mhl_Cbus_SetDCapChg(TRUE);
}

#endif

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_WakeupDetect()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_BOOL mapi_mhl_WakeupDetect(void)
{
    return mdrv_mhl_WakeupDetect();
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_SetHPD()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_SetHPD(MS_BOOL bflag)
{
    if(GET_MHL_CABLE_PLUGGED() == FALSE)
    {
        mdrv_mhl_SetHPD(bflag);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_SetPsCtrl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_SetPsCtrl(MS_U8 u8Ctrl)
{
    mdrv_mhl_SetPsCtrl(u8Ctrl);
}

void mapi_mhl_SetPsCtrl_HDMImode(MS_U8 u8Ctrl)
{
   mdrv_mhl_SetPsCtrl_HDMImode(u8Ctrl);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CbusControl()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_CbusControl(MS_U8 ucState)
{
    switch(ucState)
    {
        case MHL_FORCE_HDMI_BY_PASS:
            mdrv_mhl_LoadHdmiBypassTbl();
            break;

        case MHL_FORCE_24BIT_MODE:
            mdrv_mhl_LoadMhl24bitsModeTbl();
            break;

        case MHL_FORCE_PACKET_PIXEL_MODE:
            mdrv_mhl_LoadMhlPackedPixelModeTbl();
            break;

        case MHL_CBUS_ISOLATION_ON:
            mdrv_mhl_CbusIsolate(TRUE);
            break;

        case MHL_CBUS_ISOLATION_OFF:
            mdrv_mhl_CbusIsolate(FALSE);
            break;

        case MHL_CBUS_FLOATING_ON:
            mdrv_mhl_CbusFloating(TRUE);
            break;

        case MHL_CBUS_FLOATING_OFF:
            mdrv_mhl_CbusFloating(FALSE);
            break;

        case MHL_CBUS_RTERM_OFF:
            mdrv_mhl_RxRtermControl(RX_RTERM_OFF);
            break;

        default:
            break;
    }
}

void mapi_mhl_GetSWVersion(void)
{
    char str[30] = "MHL-";
    strcat(str,FW_VER_MAJOR);
    strcat(str,".");
    strcat(str,FW_VER_MINOR);
    strcat(str,".");
    strcat(str,P4_CHANGELIST);

    printf("The SW Version of MHL is %s\n", str);
}

char* mapi_mhl_GetP4CL(void)
{
    return P4_CHANGELIST;
}

char* mapi_mhl_GetMajorVersion(void)
{
    return FW_VER_MAJOR;
}

char* mapi_mhl_GetMinorVersion(void)
{
    return FW_VER_MINOR;
}

void mapi_mhl_RxRtermIsolate(void)
{
    mdrv_mhl_RxRtermIsolate();
}

//only for debug
void mapi_mhl_Write2bytes(MS_U16 reg, MS_U16 val)
{
    mdrv_mhl_Write2bytes(reg,val);
}

MS_U16 mapi_mhl_Read2bytes(MS_U16 reg)
{
    return mdrv_mhl_Read2bytes(reg);
}

void mapi_mhl_RegisterIOCallBackFunctions(link_mhl_reg_i_func pfnRead, link_mhl_reg_o_func pfnWrite)
{
    mdrv_mhl_RegisterCallBackFunctions(pfnRead, pfnWrite);
}

// This could be a real ID or a index.
void mapi_mhl_I2C_Channel_Settings(MS_U16 u16Channel, MS_U8 u8CommonID, MS_U8 u8ConfigID)
{
    mdrv_mhl_I2C_Channel_Settings(u16Channel, u8CommonID, u8ConfigID);
}

void mapi_mhl_TxSwap_Settings(MS_BOOL bTxSwapEnable)
{
    mdrv_mhl_TxSwap_Settings(bTxSwapEnable);
}

#endif // _API_MHL_ELAND_C_

