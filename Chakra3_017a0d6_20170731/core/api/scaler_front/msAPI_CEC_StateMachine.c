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
/// file    msAPI_CEC_StateMachine.c
/// @author MStar Semiconductor Inc.
/// @brief  HDMI CEC API Interface
///////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#if CEC_STATE_MACHINE

MS_U8 CEC_State_header = (E_LA_UNREGISTERED<<4) | E_LA_UNREGISTERED;
MsCEC_MSGLIST CEC_State_opcode = E_MSG_ABORT_MESSAGE;

/********************************************************************************/
/********************************************************************************/

#define CEC_6_3_3_2_DEBUG
#ifdef CEC_6_3_3_2_DEBUG
    #define CEC_6_3_3_2_DBG(x)      x
#else
    #define CEC_6_3_3_2_DBG(x)
#endif


#define CEC_CASE_DEBUG
#ifdef CEC_CASE_DEBUG
    #define CEC_CASE_DBG(x)      x
#else
    #define CEC_CASE_DBG(x)
#endif

/*
***Pre-condition
 Tune Internal source or HDMI input which Device isn¡¦t selected in Step1 from Device List.

*** When user selects a device from Device List, TV does following process.
 [Step1]¡GChange HDMI input of selected device. ¡GGoes to Step2
 [Step2]¡GTV sends <Routing Change> (Broadcast).
 	If <Routing Information> isn¡¦t received 500 ms later after it send.¡GGoes to Step3
 	If <Routing Information> is received. ¡GGoes to Step4
 [Step3]¡GTV sends a <Give Device Power Status> to the selected device.
 	If <Report Power Status> isn¡¦t received 500 ms later after it send.¡GGoes to Step5
 	If <Report Power Status> is received. ¡GGoes to Step6
 [Step4]¡GTV sends a <Give Device Power Status> to the selected device.
 	If <Report Power Status> isn¡¦t received 500 ms later after it send.¡GGoes to Step5
 	If <Report Power Status> is received. ¡GGoes to Step6
 [Step5]¡GExecute 7.2.2.2 Case2 <Give Device Power Status> retransmission processing,
 	If <Report Power Status> is received. ¡GGoes to Step6
 	If <Report Power Status> isn¡¦t received. ¡GFinish
 [Step6]¡GWhen the TV receives a <Report Power Status> form the device, the TV does the following action according to the [Power Status] described in the <Report Power Status>¡F
 	¡§In transition On to Standby¡¨ ¡GGoes to Step7
 	¡§Standby¡¨ ¡GGoes to Step8
 	¡§In transition Standby to On¡¨ ¡GGoes to Step9
 	¡§On¡¨ ¡GGoes to Step10
 [Step7]¡GThe TV continues to send <Give Device Power Status> to selected device every 6 seconds until a <Report Power Status>[Standby] is returned and then goes to Step8.
 [Step8]¡GThe TV sends a <User Control Pressed>[Power] to the selected device. And wait for 6 seconds after it send then goes to Step4.
 [Step9]¡GThe TV continues to send <Give Device Power Status> to selected device every 6 seconds until a <Report Power Status>[On] is returned and then goes to Step10.
 [Step10]¡GThe TV broadcasts a <Set Stream Path> with the physical address of theselected device.
*/
static EN_CEC_CASE_STATE enCECState_RoutingChange = E_CEC_STATE_7_IDLE;
U8 ori_phyaddr_7[2], new_phyaddr_7[2];
static MsCEC_DEVICELA _CEC_DeviceLA_7;

static U32 _u32CecState_VIVI_MonitorTimer = 0;
MsCEC_MSGLIST _opcode;

void msAPI_CEC_TrigCecState_7(MS_U16 pOrig_Addr, MS_U16 pNew_Addr, MsCEC_DEVICELA DeviceLA)
{
    ori_phyaddr_7[0] = ((pOrig_Addr & 0xFF00)>> 8);
    ori_phyaddr_7[1] = (pOrig_Addr & 0x00FF);

    new_phyaddr_7[0] = ((pNew_Addr & 0xFF00)>> 8);
    new_phyaddr_7[1] = (pNew_Addr & 0x00FF);

    printf("new_phyaddr_7= %x = %x  +  %x  \n", pNew_Addr, ((pNew_Addr & 0xFF00)>> 8), (pNew_Addr & 0x00FF));
    printf("_CEC_DeviceLA_7= %d", DeviceLA);

    _CEC_DeviceLA_7= DeviceLA;

    if (enCECState_RoutingChange != E_CEC_STATE_IDLE)
    {
        printf("\r\n !!! [CEC State(0x%x)] is not IDLE yet !!! \n", enCECState_RoutingChange);
    }
    else
    {
        CEC_CASE_DEBUG(printf("\r\n [%s] Set to Initial State \n", __FUNCTION__));

        enCECState_RoutingChange = E_CEC_STATE_7_SEND_ROUTING_CHANGE;
    }
}

static void MApp_CECStateMachine_7(void)
{
    U8 u8flag = FALSE;

    switch (enCECState_RoutingChange)
    {
        case E_CEC_STATE_7_IDLE:
            //CEC_CASE_DEBUG(printf("\33[1;29mE_CEC_STATE_7_IDLE         \33[0m \n"));
        default:
            break;
        case E_CEC_STATE_7_SEND_ROUTING_CHANGE:
        {
            CEC_CASE_DEBUG(printf("\33[1;29mE_CEC_STATE_7_SEND_ROUTING_CHANGE         \33[0m \n"));

            enCECState_RoutingChange = E_CEC_STATE_7_WAIT_FOR_ROUTING_INFORMATION;
            msAPI_CEC_PostMsg_RoutingChange(DIRECTMSG, ori_phyaddr_7, new_phyaddr_7);
            _u32CecState_VIVI_MonitorTimer = msAPI_Timer_GetTime0();
            break;
        }
        case E_CEC_STATE_7_WAIT_FOR_ROUTING_INFORMATION:
        {
            if ( CEC_State_opcode == E_MSG_RC_ROUTING_INFO )
            {
                CEC_CASE_DEBUG(printf("\33[1;30m    --E_MSG_RC_ROUTING_INFO--     \33[0m \n"));
                enCECState_RoutingChange= E_CEC_STATE_7_SENT_GIVE_DEVICE_POWER_STATES;
            }
            else
            {
                if ( msAPI_Timer_DiffTimeFromNow(_u32CecState_VIVI_MonitorTimer) > 500 )
                {
                    CEC_CASE_DEBUG(printf("\33[1;30m    ++E_MSG_RC_ROUTING_INFO++     \33[0m \n"));
                    enCECState_RoutingChange = E_CEC_STATE_7_SENT_GIVE_DEVICE_POWER_STATES;
                }
            }
            break;
        }
        case E_CEC_STATE_7_SENT_GIVE_DEVICE_POWER_STATES:
        {
            CEC_CASE_DEBUG(printf("\33[1;31mE_CEC_STATE_7_SENT_GIVE_DEVICE_POWER_STATES     \33[0m \n"));

            enCECState_RoutingChange = E_CEC_STATE_7_WAIT_FOR_REPORT_POWER_STATE;

            msAPI_CEC_PostMsg_GiveDevicePowerStatus(DIRECTMSG, _CEC_DeviceLA_7);

            _u32CecState_VIVI_MonitorTimer = msAPI_Timer_GetTime0();
            break;
        }
        case E_CEC_STATE_7_WAIT_FOR_REPORT_POWER_STATE:
        {
            CEC_CASE_DEBUG(printf("\33[1;32mE_CEC_STATE_7_WAIT_FOR_REPORT_POWER_STATE     \33[0m \n"));
            MsCEC_MSG_POWER_STATUS_PARM _enPowerStatus;

            if( CEC_State_opcode == E_MSG_PS_REPORT_POWER_STATUS)
            {
                CEC_CASE_DEBUG(printf("\33[1;32m    --E_MSG_PS_REPORT_POWER_STATUS--     \33[0m \n"));

                _enPowerStatus= msAPI_CEC_GetPowerStatus(_CEC_DeviceLA_7);

                switch(_enPowerStatus)
                {
                    case E_MSG_PWRSTA_ON:
                        enCECState_RoutingChange= E_CEC_STATE_7_SENT_SET_STREAM_PATH;
                        break;
                    case E_MSG_PWRSTA_STANDBY:
                        enCECState_RoutingChange= E_CEC_STATE_7_SENT_USER_CONTROL_PRESSED;
                        break;
                    case E_MSG_PWRSTA_STANDBY2ON:
                        enCECState_RoutingChange= E_CEC_STATE_7_CONTINUTE_GIVE_DEVICE_POWER_STATE_PER_6S;
                        break;
                    case E_MSG_PWRSTA_ON2STANDBY:
                        enCECState_RoutingChange= E_CEC_STATE_7_CONTINUTE_GIVE_DEVICE_POWER_STATE_PER_6S;
                        break;
                    default:
                        break;
                }
                //_u32CecState_VIVI_MonitorTimer = msAPI_Timer_GetTime0();
            }
            else//execute 7.2.2.2
            {
                if(msAPI_Timer_DiffTimeFromNow(_u32CecState_VIVI_MonitorTimer) > 500)
                {
                    break;
                }
            }
            break;
        }
        case E_CEC_STATE_7_CONTINUTE_GIVE_DEVICE_POWER_STATE_PER_6S:
        {
            MsCEC_MSG_POWER_STATUS_PARM _enPowerStatus;

            if(msAPI_Timer_DiffTimeFromNow(_u32CecState_VIVI_MonitorTimer) > 6000) //6s
            {
                CEC_CASE_DEBUG(printf("\33[1;33mE_CEC_STATE_7_CONTINUTE_GIVE_DEVICE_POWER_STATE_PER_6S     \33[0m \n"));

                if(CEC_State_opcode == E_MSG_PS_REPORT_POWER_STATUS)
                {
                     _enPowerStatus= msAPI_CEC_GetPowerStatus(_CEC_DeviceLA_7);

                    switch(_enPowerStatus)
                    {
                        case E_MSG_PWRSTA_ON:
                                enCECState_RoutingChange= E_CEC_STATE_7_SENT_SET_STREAM_PATH;
                            break;
                        case E_MSG_PWRSTA_STANDBY:
                                enCECState_RoutingChange= E_CEC_STATE_7_SENT_USER_CONTROL_PRESSED;
                                u8flag = TRUE;
                            break;
                        case E_MSG_PWRSTA_STANDBY2ON:
                        case E_MSG_PWRSTA_ON2STANDBY:
                        default:
                            break;
                    }
                    _u32CecState_VIVI_MonitorTimer = msAPI_Timer_GetTime0();
                }
                else
                {
                    msAPI_CEC_PostMsg_GiveDevicePowerStatus(DIRECTMSG, _CEC_DeviceLA_7);
                    _u32CecState_VIVI_MonitorTimer = msAPI_Timer_GetTime0();

                }
            }
            break;
        }
        case E_CEC_STATE_7_SENT_SET_STREAM_PATH:
        {
            CEC_CASE_DEBUG(printf("\33[1;34mE_CEC_STATE_7_SENT_SET_STREAM_PATH     \33[0m \n"));

            msAPI_CEC_PostMsg_SetStreamPath(DIRECTMSG, new_phyaddr_7);
            enCECState_RoutingChange= E_CEC_STATE_7_IDLE;
            break;
        }
        case  E_CEC_STATE_7_SENT_USER_CONTROL_PRESSED:
        {
            if(u8flag == TRUE)
            {
                CEC_CASE_DEBUG(printf("\33[1;35mE_CEC_STATE_7_SENT_USER_CONTROL_PRESSED    \33[0m \n"));

                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, _CEC_DeviceLA_7, E_MSG_UI_POWER);
                //Sent UserControlRelease
                msAPI_CEC_PostMsg_UserCtrlReleased(DIRECTMSG, gCECUserControlEnable, _CEC_DeviceLA_7);
                _u32CecState_VIVI_MonitorTimer = msAPI_Timer_GetTime0();
                u8flag= FALSE;
            }

            if(msAPI_Timer_DiffTimeFromNow(_u32CecState_VIVI_MonitorTimer) > 6000) //6s
            {
                enCECState_RoutingChange= E_CEC_STATE_7_SENT_GIVE_DEVICE_POWER_STATES;
            }
            break;
        }

    }
}

/*
6.3.3.2.   Case2
- When user switches to HDMI, TV sends <Routing Change>.
- When TV receives <Routing Information>, it waits for a 500ms. After that, TV sends a <Set Stream Path>
  with physical address as the parameter of the <Routing Information>.
- When <Routing Information> is not received even if 500ms has passed since < Routing Change > was transmitted,
  - When the power supply state of connected device is Power-on, TV sends <Set Stream Path>
    with physical address of the connected device.
  - When power supply state of connected device is ¡§Standby¡¨ or ¡¨In transition Standby to On¡¨ or
    ¡¨In transition On to Standby¡¨, TV executes 7.2.2.3 Case3 <Give Device Power Status> re-send processing.
    - If [Power Status] is ¡§On¡¨ after re-send processing, TV sends <Set Stream Path> with
      physical address of the connected device.
    - If [Power Status] is ¡§Standby¡¨, ¡§In transition Standby to On¡¨ or ¡¨In transition On to Standby¡¨
        after re-send processing, TV shall not send <Set Stream Path>.
*/
static EN_CEC_CASE_6_3_3_2_STATE enCecState_6_3_3_2 = E_CEC_STATE_6_3_3_2_IDLE;
U8 ori_phyaddr_6_3_3_2[2], new_phyaddr_6_3_3_2[2];
static U32 _u32CecState_6_3_3_2_MonitorTimer = 0;


void msAPI_CEC_TrigCecState_6_3_3_2(MS_U8* pOrig_Addr, MS_U8* pNew_Addr)
{
    ori_phyaddr_6_3_3_2[0] = pOrig_Addr[0];
    ori_phyaddr_6_3_3_2[1] = pOrig_Addr[1];

    new_phyaddr_6_3_3_2[0] = pNew_Addr[0];
    new_phyaddr_6_3_3_2[1] = pNew_Addr[1];

    if (enCecState_6_3_3_2 != E_CEC_STATE_IDLE)
    {
        printf("\r\n !!! [CEC State(0x%x)] is not IDLE yet !!! \n", enCecState_6_3_3_2);
    }
    else
    {
        CEC_6_3_3_2_DBG(printf("\r\n [%s] Set to Initial State \n", __FUNCTION__););

        enCecState_6_3_3_2 = E_CEC_STATE_6_3_3_2_SEND_ROUTING_CHANGE;
    }
}

static void MApp_CecStateMachine_6_3_3_2(void)
{
    static MsCEC_DEVICELA enDevice;

    switch ( enCecState_6_3_3_2 )
    {
        case E_CEC_STATE_6_3_3_2_IDLE:
        default:
            break;

        case E_CEC_STATE_6_3_3_2_SEND_ROUTING_CHANGE:
            CEC_6_3_3_2_DBG(printf("\n [E_CEC_STATE_6_3_3_2_SEND_ROUTING_CHANGE] \n"););

            CEC_6_3_3_2_DBG(printf(" [Msg_RoutingChange] \n"));
            CEC_6_3_3_2_DBG(printf(" PHY ADDR from 0x%x to 0x%x \n",
                                    (ori_phyaddr_6_3_3_2[0]<<8 | ori_phyaddr_6_3_3_2[1]),
                                    (new_phyaddr_6_3_3_2[0]<<8 | new_phyaddr_6_3_3_2[1])));

            enCecState_6_3_3_2 = E_CEC_STATE_6_3_3_2_WAIT_FOR_ROUTING_INFORMATION;
            msAPI_CEC_PostMsg_RoutingChange(DIRECTMSG, ori_phyaddr_6_3_3_2, new_phyaddr_6_3_3_2);
            _u32CecState_6_3_3_2_MonitorTimer = msAPI_Timer_GetTime0();
            break;

        case E_CEC_STATE_6_3_3_2_WAIT_FOR_ROUTING_INFORMATION:
        {
            if ( CEC_State_opcode == E_MSG_RC_ROUTING_INFO )
            {
                CEC_6_3_3_2_DBG(printf("\n [E_CEC_STATE_6_3_3_2_WAIT_FOR_ROUTING_INFORMATION] - E_MSG_RC_ROUTING_INFO\n"););

                enCecState_6_3_3_2 = E_CEC_STATE_6_3_3_2_SET_STREAM_PATH_AFTER_500MS;

                enDevice = (MsCEC_DEVICELA)((CEC_State_header & 0xF0)>>4);

                _u32CecState_6_3_3_2_MonitorTimer = msAPI_Timer_GetTime0();
            }
            else
            {
                if ( msAPI_Timer_DiffTimeFromNow(_u32CecState_6_3_3_2_MonitorTimer) > 500 )
                {
                    CEC_6_3_3_2_DBG(printf("\n [E_CEC_STATE_6_3_3_2_WAIT_FOR_ROUTING_INFORMATION] - E_CEC_STATE_6_3_3_2_REPORT_POWER_STATUS\n"););

                  #if 0 // TO DO. should decide how to get enDevice.
                    // Send <Give Device Power Status>.
                    msAPI_CEC_PostMsg(enDevice, E_MSG_PS_GIVE_DEVICE_POWER_STATUS, 0, 0);
                  #endif

                    enCecState_6_3_3_2 = E_CEC_STATE_6_3_3_2_REPORT_POWER_STATUS;
                }
            }
            break;
        }

        case E_CEC_STATE_6_3_3_2_SET_STREAM_PATH_AFTER_500MS:
        {
            if (msAPI_Timer_DiffTimeFromNow(_u32CecState_6_3_3_2_MonitorTimer) > 500)
            {
                MS_U8 au8TxBuf[2];
                MS_U16 u16PhyAddr;

                CEC_6_3_3_2_DBG(printf("\n [E_CEC_STATE_6_3_3_2_SET_STREAM_PATH_AFTER_500MS] \n"););

                u16PhyAddr = msAPI_CEC_GetActivePhyAddr();
                au8TxBuf[0] = u16PhyAddr >> 8;
                au8TxBuf[1] = u16PhyAddr & 0xFF;

                msAPI_CEC_PostMsg_SetStreamPath(DIRECTMSG, au8TxBuf);

                enCecState_6_3_3_2 = E_CEC_STATE_6_3_3_2_DONE;
            }

            break;
        }

        case E_CEC_STATE_6_3_3_2_REPORT_POWER_STATUS:
        {
            CEC_6_3_3_2_DBG(printf("\n [E_CEC_STATE_6_3_3_2_REPORT_POWER_STATUS] \n"););

          #if 0 // TO DO
            ;
          #else
            enCecState_6_3_3_2 = E_CEC_STATE_6_3_3_2_DONE;
          #endif

            break;
        }

        case E_CEC_STATE_6_3_3_2_DONE:
        {
            CEC_6_3_3_2_DBG(printf("\n [E_CEC_STATE_6_3_3_2_DONE] \n"););

            enCecState_6_3_3_2 = E_CEC_STATE_6_3_3_2_IDLE;

            break;
        }

    }
}

/***********************************************************************************/

#ifdef CEC_STATE_PATTERN

//#define CEC_CASE_XX_DEBUG
#ifdef CEC_CASE_XX_DEBUG
    #define CEC_XX_DBG(x)      x
#else
    #define CEC_XX_DBG(x)
#endif

static EN_CEC_CASE_2_STATE enCecState_XX = E_CEC_STATE_IDLE;
static U32 _u32CecState_MonitorTimer_XX = 0;

static void msAPI_CEC_SetCecState_02(void)
{
    if (enCecState_02 != E_CEC_STATE_IDLE)
    {
        printf("\r\n !!! [CEC State(0x%x)] is not IDLE yet !!! \n", enCecState_02);
    }
    else
    {
        CEC_XX_DBG(printf("\r\n [%s] Set to Initial State \n", __FUNCTION__););

        enCecState_XX = E_CEC_STATE_XX_1;
    }
}

void MApp_CecStateMachine_2(void)
{
    switch ( enCecState_XX )
    {
        case E_CEC_STATE_XX_IDLE:
        default:
            break;

        case E_CEC_STATE_XX_1:
        {
            enCecState_XX = E_CEC_STATE_XX_2;

            _u32CecState_MonitorTimer_XX = msAPI_Timer_GetTime0();
            break;
        }

        case E_CEC_STATE_XX_2:
        {
            if (msAPI_Timer_DiffTimeFromNow(_u32CecState_MonitorTimer_XX) > 500)
            {
                enCecState_XX = E_CEC_STATE_XX_DONE;
            }

            break;
        }

        case E_CEC_STATE_XX_DONE:
        {
            enCecState_XX = E_CEC_STATE_XX_IDLE;

            break;
        }

    }
}

#endif

/***********************************************************************************/

void MApp_CecStateMachine(void)
{
    /********************************************
        Check 6.3.3.2.     Case2
    *********************************************/
    MApp_CecStateMachine_6_3_3_2();
    MApp_CECStateMachine_7();



#ifdef CEC_STATE_PATTERN
    /********************************************
        Check
    *********************************************/
    MApp_CecStateMachine_XX();
#endif

}





/*************************************************************************************************/
#endif // #if CEC_STATE_MACHINE

