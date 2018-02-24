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
//#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include <string.h>
#include "stdio.h"

#if ENABLE_CEC

#define _MSAPICEC_C_
#include "drvGlobal.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_OSD.h"
#include "apiCEC.h"
#include "msAPI_CEC.h"
#include "msIR.h"
#include "MApp_Key.h"
#include "apiPNL.h"
#include "Panel.h"
#include "MApp_GlobalVar.h"
#include "MApp_InputSource.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_exefunc.h"
#include "msAPI_Tuning.h"
#include "drvPM.h"
#include "MApp_Audio.h"
#include "MApp_ZUI_ACTglobal.h"
#include "msAPI_audio.h"
#ifdef ENABLE_DMP
#include "mapp_mplayer.h"
#include "MApp_TopStateMachine.h"
#include "MApp_ChannelChange.h"
#endif
#include "msAPI_Timer.h"
#include "drvGPIO.h"

#include "MApp_GlobalFunction.h"

#include "msAPI_CEC_StateMachine.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#include "MApp_ZUI_ACTinputsource.h"

#include "ZUI_tables_h.inl"
#if ENABLE_PVR
#include "MApp_PVR.h"
#endif

//-------------------------------------------------------------------------------------------------

extern BOOLEAN MApp_UiMenu_IsCountDownWinShow(void);

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define CEC_PORT1   0x10    //HDMI 1
#define CEC_PORT2   0x20    //HDMI 2
#define CEC_PORT3   0x30    //HDMI 3
#define CEC_PORT4   0x40    //HDMI 4


#define CEC_DEBUG                           FALSE//TRUE//FALSE
#if CEC_DEBUG
    #define CEC_MSG(x)                      x
    #define CEC_DPUTSTR(str)                printf(str)
    #define CEC_DPRINTF(str, x)             printf(str, x)
    #define CEC_ERROR_DEBUG(str, x)         printf(str, x)
    #define CEC_POSTMSG_DEBUG(x)            x
    #define CEC_POSTMSG_ERROR_DEBUG(x)      x
    #define CEC_POLLING_MSG_DBG(x)          x
#else
    #define CEC_MSG(x)                      //x
    #define CEC_DPUTSTR(str)                //printf(str)
    #define CEC_DPRINTF(str, x)             //printf(str, x)
    #define CEC_ERROR_DEBUG(str, x)         //printf(str, x)
    #define CEC_POSTMSG_DEBUG(x)            //x
    #define CEC_POSTMSG_ERROR_DEBUG(x)      //x
    #define CEC_POLLING_MSG_DBG(x)          //x
#endif



// CEC function catalog
#define ONE_TOUCH_PLAY_SUPPORT                  1 // TV, CEC switches
#define ROUTING_CONTROL_SUPPORT                 1 // TV, CEC switches
#define STANDBY_COMMAND_SUPPORT                 1 // All
#define ONE_TOUCH_RECORD_SUPPORT                0 // Recording devices
#define TIMER_PROGRAMMER_SUPPORT                0 //
#define SYSTEM_INFORMATION_SUPPORT              1 // All
#define DECK_CONTROL_SUPPORT                    1
#define TUNER_CONTROL_SUPPORT                   0
#define VENDOR_SPECIFIC_SUPPORT                 1 // All
#define OSD_DISPLAY_SUPPORT                     0
#define DEVICE_OSD_NAME_TRANSFER_SUPPORT        1 //anvi cec
#define DEVICE_MENU_CONTROL_SUPPORT             1
#define REMOTE_CONTROL_PASSTHROUGH_SUPPORT      1
#define POWER_STATUS_SUPPORT                    1 // All except CEC switches
#define SYSTEM_AUDIO_CONTROL_SUPPORT            1
#define GENERAL_PROTOCAL_SUPPORT                1 // All
#define AUDIO_RETURN_CHANNEL_SUPPORT            1

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

MS_U8 code gStrCECDeviceType[16][MAX_CEC_DEVICE_OSD_NAME]=
{
    {'T', 'V', ':', ' '},
    {'R', 'e', 'c', 'o', 'r', 'd', 'e', 'r', '1', ':', ' '},
    {'R', 'e', 'c', 'o', 'r', 'd', 'e', 'r', '2', ':', ' '},
    {'T', 'u', 'n', 'e', 'r', '1', ':', ' '},
    {'P', 'l', 'a', 'y', 'b', 'a', 'c', 'k', '1', ':', ' '},
    {'A', 'u', 'd', 'i', 'o', ' ', 'S', 'y', 's', ':', ' '},
    {'T', 'u', 'n', 'e', 'r', '2', ':', ' '},
    {'T', 'u', 'n', 'e', 'r', '3', ':', ' '},
    {'P', 'l', 'a', 'y', 'b', 'a', 'c', 'k', '2', ':', ' '},
    {'R', 'e', 'c', 'o', 'r', 'd', 'e', 'r', '3', ':', ' '},
    {'T', 'u', 'n', 'e', 'r', '4', ':', ' '},
    {'P', 'l', 'a', 'y', 'b', 'a', 'c', 'k', '3', ':', ' '},
    {'R', 'e', 's', 'e', 'r', 'v', 'e', 'd', ':', ' '},
    {'R', 'e', 's', 'e', 'r', 'v', 'e', 'd', ':', ' '},
    {'F', 'r', 'e', 'e', ' ', 'u', 's', 'e', ':', ' '},
    {'B', 'r', 'o', 'a', 'd', 'c', 'a', 's', 't', ':', ' '},
};

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

static BOOLEAN gCECInitDone = FALSE;

static CECMSGQUEUE  _stCecMsgQueue;
static MS_CEC_INFO_LIST _stCecApiInfo;

static MS_U8 _u8CecDeviceCount = 0;
static MS_U8 _au8CecDeviceIdx[16];
static MS_U16 _au16CecDeviceIdx_PhyAddr[16];
static MS_U8 _au8CecDeviceName[16][13];

static EN_CEC_POLLING_STATUS _bStartPolling = STATUS_POLLING_IDLE;
static U32 _u32CecDeviceMonitorTimer = 0;

BOOLEAN g_bCecForceImmediatelyPolling = FALSE;

BOOLEAN gCECKeyENABLE = TRUE;
BOOLEAN gCECRecordEnable = FALSE;
BOOLEAN gCECProcessCMDbyKey = FALSE;
MS_U8  gCECProcessCMDKeycode = 0xFF;
MsCEC_MSG_DC_DECK_STATUS_PARM gCECDeckStatus = (MsCEC_MSG_DC_DECK_STATUS_PARM) 0xFF;
BOOLEAN gCECUserControlEnable;
MS_U8 gCECOSDStr[40];
BOOLEAN gCECQueryPowerFlag = FALSE;

static BOOLEAN bSystemAudioMode = FALSE;

BOOLEAN gCECAmpARCOffOnStatusCheck = FALSE;
//BOOLEAN gCECAmpIsNotExit = TRUE;
BOOLEAN gIsCECAmpARCOn = FALSE;
MS_U8 ARCAudioVolume = 0;
BOOLEAN ARCAMPIsMute = FALSE;
//-------------------------------------------------------------------------------------------------
//  External Variables
//-------------------------------------------------------------------------------------------------

extern E_OSD_ID _eActiveOSD;

//-------------------------------------------------------------------------------------------------
//  external Functions
//-------------------------------------------------------------------------------------------------

extern void MsOS_DelayTask(U32 u32milisec);

//-------------------------------------------------------------------------------------------------
//  external Files
//-------------------------------------------------------------------------------------------------

#include "msAPI_CEC_StateMachine.c"

//-------------------------------------------------------------------------------------------------
//  Local Functions prototype
//-------------------------------------------------------------------------------------------------

BOOLEAN msAPI_CEC_IsCECKey(MS_U8 bKey);
BOOLEAN msAPI_CEC_IsByPass(void);

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
void msAPI_CEC_SetSystemAudioMode(BOOLEAN bMode)
{
    bSystemAudioMode = bMode;
}

BOOLEAN msAPI_CEC_QuerySystemAudioMode(void)
{
    return bSystemAudioMode;
}

CEC_ERROR_CODE msAPI_CEC_PostMsg(MsCEC_DEVICELA dst_address, MsCEC_MSGLIST msg, MS_U8 *cmd, MS_U8 len)
{
    CEC_ERROR_CODE cecErrorCode = E_CEC_FEATURE_ABORT;

     if ( gCECInitDone == FALSE)
     {
        //printf("!!! CEC HW not Init yet !!! \n");
        return cecErrorCode;
    }

    if (DB_HDMI_SETTING.g_bHdmiCecMode == ENABLE)
    {
        cecErrorCode = MApi_CEC_TxSendMsg(dst_address, msg, cmd, len);
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

    if (  (DB_HDMI_SETTING.g_bHdmiCecMode== DISABLE)
      && (DB_HDMI_SETTING.g_enHDMIARC == DISABLE) )
    {
        return FALSE;
    }

    // Checking array index
    if( _stCecMsgQueue.u8CecMsgQIdxStart >= CEC_MSG_QUEUE_SIZE )
    {
        _stCecMsgQueue.u8CecMsgQIdxStart = 0;
    }

    pstCECMsg = &_stCecMsgQueue.astCecMsgQ[_stCecMsgQueue.u8CecMsgQIdxStart];
    if (pstCECMsg->u8Handle!= CEC_INVALID)//Queue full
    {
        return FALSE;   // no available message queue slot
    }

    pstCECMsg->u8Handle = CEC_VALID;
    pstCECMsg->enDevice= enDevice;
    pstCECMsg->enOpcode= enOpcode;
    for(i=0;i<u8Len;i++)
    {
        pstCECMsg->au8Operand[i] = *(pu8Operand+i);
    }

    pstCECMsg->u8Len = u8Len;

    #if 0//def APICEC_DEBUG
    APICEC_DPRINTF(printf("\rastCecMsgQIdxStart=%bu\t",(MS_U8)_stCecMsgQueue.u8CecMsgQIdxStart));
    APICEC_DPRINTF(printf("enDevice=0x%bx , opcode=0x%bx\t",(MS_U8)pstCECMsg->enDevice, (MS_U8)pstCECMsg->enOpcode));
    for(i=0;i<u8Len;i++)
        APICEC_DPRINTF(printf("cmd=0x%bx\n",(MS_U8)pstCECMsg->au8Operand[i]));
    #endif

    ++_stCecMsgQueue.u8CecMsgQIdxStart;
    _stCecMsgQueue.u8CecMsgQIdxStart %= CEC_MSG_QUEUE_SIZE;

    return TRUE;
}

//***************************************************************************************

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

void msAPI_CEC_EmptyMsgQueue (void)
{
    MS_U8 i;

    _stCecMsgQueue.u8CecMsgQIdxStart = 0;
    _stCecMsgQueue.u8CecMsgQIdxEnd = 0;

    for (i = 0; i < CEC_MSG_QUEUE_SIZE; i++)
        _stCecMsgQueue.astCecMsgQ[i].u8Handle= CEC_INVALID;
}

//***************************************************************************************

MS_BOOL msAPI_CEC_IsDeviceExist(MsCEC_DEVICELA enDevice)
{
    return _stCecApiInfo.CecDevicesExisted[enDevice];
}

//***************************************************************************************

MS_U8 msAPI_CEC_GetDeviceTotalNum(void)
{
    return _u8CecDeviceCount;
}

MS_U8 msAPI_CEC_GetHeader(MsCEC_DEVICELA enDevice)
{
    return (MS_U8)(((E_LA_TV<<4)&0xF0) | enDevice);
}

//***************************************************************************************

MS_U8* msAPI_CEC_GetDeviceName(MS_U8 u8Device)
{
    return (MS_U8*)_au8CecDeviceName[u8Device];
}

void msAPI_CEC_SetDeviceName(MS_U8 u8Device, MS_U8* pName, MS_BOOL bIsDefault)
{
    if(bIsDefault)
        strncpy((char *)_au8CecDeviceName[u8Device], (char *)gStrCECDeviceType[u8Device], strlen((char *)gStrCECDeviceType[u8Device]));
    else
        strncpy((char *)_au8CecDeviceName[u8Device], (char *)pName, strlen((char *)pName));
}

//***************************************************************************************

MS_U8 msAPI_CEC_GetDeviceIdx(MS_U8 u8Idx)
{
    return _au8CecDeviceIdx[u8Idx];
}

void msAPI_CEC_SetDeviceIdx(MS_U8 u8Idx, MS_U8 u8Device)
{
    _au8CecDeviceIdx[u8Idx]=u8Device;
}

//***************************************************************************************

MS_U16 msAPI_CEC_GetDeviceIdx_PhyAddr(MS_U8 u8Idx)
{
    return _au16CecDeviceIdx_PhyAddr[u8Idx];
}

void msAPI_CEC_SetDeviceIdx_PhyAddr(MS_U8 u8Idx, MS_U16 u16PhyAddr)
{
    _au16CecDeviceIdx_PhyAddr[u8Idx]=u16PhyAddr;
}

//***************************************************************************************

void msAPI_CEC_SetActiveDevice(MsCEC_DEVICELA enDevice)
{
    _stCecApiInfo.ActiveLogicalAddress = (MsCEC_DEVICELA) (enDevice & 0x0F);
}

MsCEC_DEVICELA msAPI_CEC_GetActiveDevice(void)
{
    return _stCecApiInfo.ActiveLogicalAddress;
}

//***************************************************************************************

void MApp_CEC_SetMyPhyAddr(INPUT_SOURCE_TYPE_t pre_srctype, INPUT_SOURCE_TYPE_t cur_srctype)
{
    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
           return;
    }

    if (DB_HDMI_SETTING.g_bHdmiCecMode == DISABLE)
    {
       return;
    }

    if (IsSrcTypeHDMI(pre_srctype) && !IsSrcTypeHDMI(cur_srctype))
    {
        _stCecApiInfo.ActivePhysicalAddress[0] = 0x00 ;
        _stCecApiInfo.ActivePhysicalAddress[1] = 0x00 ;
    }
}

U16 msAPI_CEC_GetActivePhyAddr(void)
{
    return _stCecApiInfo.ActivePhysicalAddress[0] << 8 | _stCecApiInfo.ActivePhysicalAddress[1];
}

//***************************************************************************************

void MApp_CEC_ERROR_CODE_String(CEC_ERROR_CODE enCode)
{
    switch (enCode)
    {
        case E_CEC_FEATURE_ABORT:
            printf(" E_CEC_FEATURE_ABORT ");
            break;

        case E_CEC_RX_SUCCESS:
            printf(" E_CEC_RX_SUCCESS ");
            break;

        case E_CEC_TX_SUCCESS:
            printf(" E_CEC_TX_SUCCESS ");
            break;

        case E_CEC_RF:
            printf(" E_CEC_RF ");
            break;

        case E_CEC_LOST_ABT:
            printf(" E_CEC_LOST_ABT ");
            break;

        case E_CEC_BIT_SHORT:
            printf(" E_CEC_BIT_SHORT ");
            break;

        case E_CEC_BIT_LONG:
            printf(" E_CEC_BIT_LONG ");
            break;

        case E_CEC_NACK:
            printf(" E_CEC_NACK ");
            break;

        case E_CEC_SYSTEM_BUSY:
            printf(" E_CEC_SYSTEM_BUSY ");
            break;

        default:
            break;
    }
}

//***************************************************************************************

CEC_ERROR_CODE  msAPI_CEC_PingDevice(MsCEC_DEVICELA enPingDevice)
{
    CEC_ERROR_CODE enCecErrorCode;

    enCecErrorCode = MApi_CEC_TxSendMsg(enPingDevice, (MsCEC_MSGLIST)0, (U8*)&enPingDevice, 0);

#if CEC_DEBUG
    printf("\n <Ping 0x%x> -", enPingDevice);
    MApp_CEC_ERROR_CODE_String(enCecErrorCode);
    printf("\n");
#endif

    return enCecErrorCode;
}

//***************************************************************************************

void msAPI_CEC_PostMsg_ActiveSource(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pPhysicalAddr)
{
    MS_U8 au8TxBuf[2];

    au8TxBuf[0] = pPhysicalAddr[0];
    au8TxBuf[1] = pPhysicalAddr[1];

    CEC_POSTMSG_DEBUG(printf("%s_<Active Source>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", (au8TxBuf[0]<<8 | au8TxBuf[1])));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_ACTIVE_SOURCE, au8TxBuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_ACTIVE_SOURCE, au8TxBuf, 2);
    }
}

//***************************************************************************************

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
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_RC_REQ_ACTIVE_SOURCE, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_RC_REQ_ACTIVE_SOURCE, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
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
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_RC_ROUTING_INFO, (MS_U8 *)&txbuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_RC_ROUTING_INFO, (MS_U8 *)&txbuf, 2);
    }
}

void msAPI_CEC_PostMsg_RoutingChange(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pOrig_Addr, MS_U8* pNew_Addr)
{
    MS_U8 au8TxBuf[4];

    au8TxBuf[0] = pOrig_Addr[0];
    au8TxBuf[1] = pOrig_Addr[1];

    au8TxBuf[2] = pNew_Addr[0];
    au8TxBuf[3] = pNew_Addr[1];

    CEC_POSTMSG_DEBUG(printf("%s_<Routing Change>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" from 0x%x to 0x%x \n", (au8TxBuf[0]<<8 | au8TxBuf[1]),
                                                      (au8TxBuf[2]<<8 | au8TxBuf[3]) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_RC_ROUTING_CHANGE, (MS_U8 *)&au8TxBuf, 4);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_RC_ROUTING_CHANGE, (MS_U8 *)&au8TxBuf, 4);
    }
}

void msAPI_CEC_PostMsg_SetStreamPath(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* new_address)
{
    MS_U8 au8TxBuf[2];

    au8TxBuf[0] = new_address[0];
    au8TxBuf[1] = new_address[1];

    CEC_POSTMSG_DEBUG(printf("%s_<Set Stream Path>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" [0x%04x] \n", (au8TxBuf[0]<<8 | au8TxBuf[1]) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_RC_SET_STREM_PATH, (MS_U8 *)&au8TxBuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_RC_SET_STREM_PATH, (MS_U8 *)&au8TxBuf, 2);
    }
}

//***************************************************************************************

void msAPI_CEC_PostMsg_Standby(EN_CEC_SEND_MSG enCecSendMsg)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Standby> \n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_STANDBY, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_STANDBY, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
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

//***************************************************************************************

//E_MSG_TP_CLEAR_ANALOG_TIMER:
//E_MSG_TP_CLEAR_DIGITAL_TIMER:
//E_MSG_TP_CLEAR_EXT_TIMER:
//E_MSG_TP_SET_ANALOG_TIMER:
//E_MSG_TP_SET_DIGITAL_TIMER:
//E_MSG_TP_SET_EXT_TIMER:
//E_MSG_TP_SET_TIMER_PROGRAM_TITLE:
//E_MSG_TP_TIMER_CLEARD_STATUS:
//E_MSG_TP_TIMER_STATUS:

//***************************************************************************************

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

//***************************************************************************************

void msAPI_CEC_PostMsg_GivePhysicalAddress(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Give Physical Address>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_SI_REQUEST_PHY_ADDR, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_SI_REQUEST_PHY_ADDR, 0, 0);
    }
}

void msAPI_CEC_PostMsg_ReportPhysicalAddress(EN_CEC_SEND_MSG enCecSendMsg)
{
    MS_U8 au8TxBuf[3];

    au8TxBuf[0] = 0x00;
    au8TxBuf[1] = 0x00;
    au8TxBuf[2] = E_LA_TV;

    CEC_POSTMSG_DEBUG(printf("%s_<Report Physical Address> [0.0.0.0] [TV] \n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_SI_REPORT_PHY_ADDR, (MS_U8 *)&au8TxBuf, 3);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_SI_REPORT_PHY_ADDR, (MS_U8 *)&au8TxBuf, 3);
    }
}

//E_MSG_SI_GET_MENU_LANGUAGE:

void msAPI_CEC_PostMsg_SetMenuLang(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pu8MenuLanguageCode)
{
    MS_U8 au8TxBuf[3];

    au8TxBuf[0] = pu8MenuLanguageCode[0];
    au8TxBuf[1] = pu8MenuLanguageCode[1];
    au8TxBuf[2] = pu8MenuLanguageCode[2];

    CEC_POSTMSG_DEBUG(printf("%s_<Set Menu Language>\n", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - [%s", au8TxBuf[0] ));
    CEC_POSTMSG_DEBUG(printf(" %s", au8TxBuf[1] ));
    CEC_POSTMSG_DEBUG(printf(" %s] \n", au8TxBuf[2] ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_BROADCAST, E_MSG_SI_SET_MENU_LANGUAGE, (MS_U8*)&au8TxBuf, 3);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_BROADCAST, E_MSG_SI_SET_MENU_LANGUAGE, (MS_U8*)&au8TxBuf, 3);
    }
 }

//E_MSG_SI_POLLING_MESSAGE:

//***************************************************************************************

void msAPI_CEC_PostMsg_DeckCtrl(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_DC_DECK_CTRL_PARM enCmd)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Deck Control>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
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
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DC_DECK_CTRL, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_DC_DECK_CTRL, (MS_U8 *)&enCmd, 1);
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
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_DC_PLAY, (MS_U8 *)&enCmd, 1);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_DC_PLAY, (MS_U8 *)&enCmd, 1);
    }
}

//***************************************************************************************

//E_MSG_TC_GIVE_TUNER_STATUS:
//E_MSG_TC_SEL_ANALOG_SERVICE:
//E_MSG_TC_SEL_DIGITAL_SERVICE:
//E_MSG_TC_TUNER_DEVICE_STATUS:
//E_MSG_TC_TUNER_STEP_DEC:
//E_MSG_TC_TUNER_STEP_INC:

//***************************************************************************************

void msAPI_CEC_PostMsg_DeviceVendorID(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
  #if 1 // TO DO
    MS_U8 u8VendorID[3] = {0x00, 0x00, 0x39};    //Toshiba ID
  #else
    MS_U8 u8VendorID[3];

    u8VendorID[0] = _stCecApiInfo.u8CecVendorID[enDeviceDst][0];
    u8VendorID[1] = _stCecApiInfo.u8CecVendorID[enDeviceDst][1];
    u8VendorID[2] = _stCecApiInfo.u8CecVendorID[enDeviceDst][2];
  #endif

    CEC_POSTMSG_DEBUG(printf("%s_<Device Vendor ID>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" = 0x%x,", u8VendorID[0]));
    CEC_POSTMSG_DEBUG(printf(" 0x%x,", u8VendorID[1]));
    CEC_POSTMSG_DEBUG(printf(" 0x%x \n", u8VendorID[2]));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_VS_DEVICE_VENDOR_ID, (MS_U8 *)&u8VendorID, 3);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_VS_DEVICE_VENDOR_ID, (MS_U8 *)&u8VendorID, 3);
    }

}

void msAPI_CEC_PostMsg_GiveDeviceVendorID(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice)
{
    CEC_POSTMSG_DEBUG(printf("%s_<Give Device Vendor ID>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_VS_GIVE_VENDOR_ID, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_VS_GIVE_VENDOR_ID, 0, 0);
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
             msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_UI_PRESS, (MS_U8*)&cmd, 1);
        }
        else // if (enCecSendMsg == DIRECTMSG)
        {
            msAPI_CEC_PostMsg(enDevice, E_MSG_UI_PRESS, (MS_U8*)&cmd, 1);
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
             msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_UI_RELEASE, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
        }
        else // if (enCecSendMsg == DIRECTMSG)
        {
            msAPI_CEC_PostMsg(enDevice, E_MSG_UI_RELEASE, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
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
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_PS_GIVE_POWER_STATUS, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_PS_GIVE_POWER_STATUS, 0, 0);
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

//E_MSG_SAC_REPORT_AUDIO_STATUS:
//E_MSG_SAC_SET_SYSTEM_AUDIO_MODE:

void msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(EN_CEC_SEND_MSG enCecSendMsg)
{
    CEC_POSTMSG_DEBUG(printf("%s_<System Audio Mode Request> \n", ((enCecSendMsg == POSTMSG)?("P"):("D"))));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, (MS_U8*)E_MSG_FEATURE_ABORT, 0);
    }
}

void msAPI_CEC_PostMsg_SystemAudioModeReq(EN_CEC_SEND_MSG enCecSendMsg, MS_U16 u16PhyAddr)
{
    MS_U8 au8TxBuf[2];

    CEC_POSTMSG_DEBUG(printf("%s_<System Audio Mode Request>", ((enCecSendMsg == POSTMSG)?("P"):("D"))));
    CEC_POSTMSG_DEBUG(printf(" - [0x%04x] \n", u16PhyAddr));

    au8TxBuf[0] = (MS_U8)(u16PhyAddr>>8);
    au8TxBuf[1] = (MS_U8)(u16PhyAddr&0x0F);

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, (MS_U8 *)&au8TxBuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(E_LA_AUDIO_SYS, E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST, (MS_U8 *)&au8TxBuf, 2);
    }
}

//E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS:
//E_MSG_SAC_SET_AUDIO_RATE:

//***************************************************************************************

//    E_MSG_ARC_INITIATE_ARC                    = 0xC0,

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
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_ARC_REQUEST_ARC_INITATION, 0, 0);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_ARC_REQUEST_ARC_INITATION, 0, 0);
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

//    E_MSG_ARC_TERMINATED_ARC                  = 0xC5,

//***************************************************************************************

void msAPI_CEC_PostMsg_FeatureAbort(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice,
                                    MsCEC_MSGLIST enMsg, MsCEC_MSG_ABORT_REASON enCmd)
{
    MS_U8 au8TxBuf[2];

    au8TxBuf[0] = enMsg;
    au8TxBuf[1] = enCmd;

    CEC_POSTMSG_DEBUG(printf("%s_<Feature Abort>", ((enCecSendMsg == POSTMSG)?("P"):("D")) ));
    CEC_POSTMSG_DEBUG(printf(" - 0x%x \n", enDevice ));
    CEC_POSTMSG_DEBUG(printf(" opcode: 0x%x \n", au8TxBuf[0] ));
    CEC_POSTMSG_DEBUG(printf(" reason:"));

    switch (au8TxBuf[1])
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
    CEC_POSTMSG_DEBUG(printf(" (0x%x) \n", au8TxBuf[1]));

    if (enCecSendMsg == POSTMSG)
    {
        msAPI_CEC_PostMsgToQueue(enDevice, E_MSG_FEATURE_ABORT, (MS_U8 *)&au8TxBuf, 2);
    }
    else // if (enCecSendMsg == DIRECTMSG)
    {
        msAPI_CEC_PostMsg(enDevice, E_MSG_FEATURE_ABORT, (MS_U8 *)&au8TxBuf, 2);
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

void msAPI_CEC_RequestARCAction(U8 action)
{
    MsCEC_DEVICELA DeviceIdex=E_LA_TV;

    DeviceIdex = MApi_CEC_GetActiveLogicalAddress();

    if(DeviceIdex<=RESERVED_2)
    {
        if(action == CEC_ARC_REQUEST_INITIATION)
        {
            //For mantis 527266, Yamaha Amplifier RX V373 cannot Init ARC correctly
            //After comparing with Chakra2_ATSC CEC command,
            //add SystemAudioModeReq before requesting ARC init
            msAPI_CEC_PostMsg_SystemAudioModeReq(POSTMSG, msAPI_CEC_GetActivePhyAddr());
            msAPI_CEC_PostMsg_RequestARCInitiation(POSTMSG, E_LA_AUDIO_SYS);
        }
        else if(action == CEC_ARC_REQUEST_TERMINATION)
        {
            MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);
            //MUTE_Off();
            MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);


            msAPI_CEC_PostMsg_RequestARCTermination(POSTMSG, E_LA_AUDIO_SYS);
        }
    }
}

//***************************************************************************************

void msAPI_CEC_DeviceChange(MsCEC_DEVICELA enChangedDevice)
{
    U16 u16PhyAddr = 0xFFFF;
    U8 new_phyaddress[2];
    U8 i;

    if ( !IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
    {
        CEC_MSG(printf(" Not in HDMI \n"));
        return;
    }

    if ( !msAPI_CEC_IsDeviceExist(enChangedDevice) )
    {
        CEC_MSG(printf(" LA 0x%x is not exist \n", enChangedDevice));
        return;
    }

    CEC_MSG(printf(">> msAPI_CEC_DeviceChange \n"));
    CEC_MSG(printf("LA: 0x%x, ", enChangedDevice));

    for(i=0; i<=msAPI_CEC_GetDeviceTotalNum(); i++)
    {
        if (msAPI_CEC_GetDeviceIdx(i) == enChangedDevice)
        {
            u16PhyAddr = msAPI_CEC_GetDeviceIdx_PhyAddr(i);
            CEC_MSG(printf(" PhyAddr: 0x%x \n", u16PhyAddr));
            break;
        }
    }
    CEC_MSG(printf("Current LA: 0x%x, ", msAPI_CEC_GetActiveDevice()));
    CEC_MSG(printf(" PhyAddr: 0x%x \n", msAPI_CEC_GetDeviceIdx_PhyAddr(msAPI_CEC_GetActiveDevice())));

    if (u16PhyAddr != 0xFFFF)
    {
        new_phyaddress[0] = u16PhyAddr >> 8;
        new_phyaddress[1] = u16PhyAddr & 0xFF;

        msAPI_CEC_PostMsg_SetStreamPath(DIRECTMSG, new_phyaddress);

        _stCecApiInfo.ActivePhysicalAddress[0] = u16PhyAddr >> 8;
        _stCecApiInfo.ActivePhysicalAddress[1] = u16PhyAddr & 0xFF;

        MApi_CEC_SetActiveLogicalAddress(enChangedDevice);
        msAPI_CEC_SetActiveDevice(enChangedDevice);
    }
}

//**************************************************************************
// For CEC usage - sending routing change or active source when switching source
// - Routing change: HDMI -> HDMI, non-HDMI -> HDMI
// - Active source   : HDMI -> non-HDMI

void msAPI_CEC_RoutingControl_SourceChange(INPUT_SOURCE_TYPE_t pre_srctype, INPUT_SOURCE_TYPE_t cur_srctype)
{
    U8 orig_phyaddress[2], new_phyaddress[2];
    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
       return;
    }

    if (DB_HDMI_SETTING.g_bHdmiCecMode == DISABLE)
    {
       return;
    }

    MApp_CEC_SetMyPhyAddr(pre_srctype, cur_srctype);

    if ( IsSrcTypeHDMI(pre_srctype) && (!IsSrcTypeHDMI(cur_srctype)) )
    {
        MS_U8 au8TxBuf[2];

        au8TxBuf[0] = 0x00;
        au8TxBuf[1] = 0x00;

        msAPI_CEC_PostMsg_ActiveSource(DIRECTMSG, au8TxBuf);
    }
    else if ( (IsSrcTypeHDMI(pre_srctype) && IsSrcTypeHDMI(cur_srctype))
           || (!IsSrcTypeHDMI(pre_srctype) && IsSrcTypeHDMI(cur_srctype)) )
    {
        switch (pre_srctype)
        {
            case INPUT_SOURCE_HDMI:
                orig_phyaddress[0] = CEC_PORT1;
                break;

          #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_HDMI2:
                orig_phyaddress[0] = CEC_PORT2;
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case INPUT_SOURCE_HDMI3:
                orig_phyaddress[0] = CEC_PORT3;
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case INPUT_SOURCE_HDMI4:
                orig_phyaddress[0] = CEC_PORT4;
                break;
          #endif

            default:
                if(!IsSrcTypeHDMI(pre_srctype)) // switch to the internal TV sources
                    orig_phyaddress[0] = 0x00;
                break;
        }
        orig_phyaddress[1] = 0x00;

        switch (cur_srctype)
        {
            case INPUT_SOURCE_HDMI:
                new_phyaddress[0] = CEC_PORT1;
                break;

          #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_HDMI2:
                new_phyaddress[0] = CEC_PORT2;
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case INPUT_SOURCE_HDMI3:
                new_phyaddress[0] = CEC_PORT3;
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case INPUT_SOURCE_HDMI4:
                new_phyaddress[0] = CEC_PORT4;
                break;
          #endif

            default:
                break;
        }
        new_phyaddress[1] = 0x00;

    #if CEC_STATE_MACHINE
        msAPI_CEC_TrigCecState_6_3_3_2(orig_phyaddress, new_phyaddress);
    #else
        msAPI_CEC_PostMsg_RoutingChange(DIRECTMSG, orig_phyaddress, new_phyaddress);

        msAPI_CEC_PostMsg_SetStreamPath(DIRECTMSG, new_phyaddress);
    #endif

        _stCecApiInfo.ActivePhysicalAddress[0] = new_phyaddress[0];
        _stCecApiInfo.ActivePhysicalAddress[1] = new_phyaddress[1];
    }
}

//**************************************************************************

/*
static void msAPI_CEC_CheckActiveDevice(void)
{
    MS_BOOL bCheck = FALSE;
    MsCEC_DEVICELA i, enActLA;

    enActLA = msAPI_CEC_GetActiveDevice();

    if (  ( enActLA == E_LA_TV)
       || ( msAPI_CEC_IsDeviceExist(enActLA) == FALSE )
       )
    {
        bCheck = TRUE;
    }

    if ( bCheck )
    {
        if ( msAPI_CEC_GetDeviceTotalNum() == 0)
        {
            msAPI_CEC_SetActiveDevice(E_LA_TV);
        }
        else if ( msAPI_CEC_GetDeviceTotalNum() == 1)
        {
            for (i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
            {
                if ( msAPI_CEC_IsDeviceExist(i) == TRUE )
                {
                    msAPI_CEC_SetActiveDevice(i);
                }
            }
        }
        else
        {
            U8 u8HSB = 0x10;

          #if (INPUT_HDMI_VIDEO_COUNT >= 1)
           if (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI)
            {
                u8HSB = 0x10;
            }
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 2)
           if (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI2)
            {
                u8HSB = 0x20;
            }
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 3)
           if (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI3)
            {
                u8HSB = 0x30;
            }
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 4)
           if (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI4)
            {
                u8HSB = 0x40;
            }
          #endif

            // 1. check if any device is match with child position [x,0.0.0]
            for (i=E_LA_RECORDER1; i<E_LA_UNREGISTERED; i++)
            {
                if ( (msAPI_CEC_GetDeviceIdx_PhyAddr(i) & 0xFF00) == (u8HSB << 8) )
                {
                    msAPI_CEC_SetActiveDevice(i);
                }
            }

            if ( msAPI_CEC_GetActiveDevice() == E_LA_TV )
            {
                for (i=E_LA_RECORDER1; i<E_LA_UNREGISTERED; i++)
                {
                    if ( (msAPI_CEC_GetDeviceIdx_PhyAddr(i) & 0xF000) == (u8HSB << 8) )
                    {
                        msAPI_CEC_SetActiveDevice(i);
                    }
                }
            }
        }
    }

    printf("\n *** Active 0x%x \n", msAPI_CEC_GetActiveDevice() );
}
*/

void msAPI_CEC_ReportDevice(void)
{
#if CEC_DEBUG
    MsCEC_DEVICELA i;
    MS_U8 u8Num = msAPI_CEC_GetDeviceTotalNum();

    if (u8Num > 0)
    {
        printf("\n ***** Device List View ***** \n");
        printf(" [%2d], ", u8Num);
        printf(" Active 0x%x", msAPI_CEC_GetActiveDevice() );
        printf(" [0x%x] \n", MApi_CEC_GetActiveLogicalAddress() );

        for (i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
        {
            if (msAPI_CEC_GetDeviceIdx(i) != 0xFF)
            {
                printf(" PhyAddr of hDevice 0x%x is", msAPI_CEC_GetDeviceIdx(i) );
                printf(" [0x%04x] \n", msAPI_CEC_GetDeviceIdx_PhyAddr((MS_U8)i));
            }
        }
        printf(" **************************** \n");
    }
#endif
}

void msAPI_CEC_AddDevice(MsCEC_DEVICELA enDevice)
{
    U8 i;

    if(_stCecApiInfo.CecDevicesExisted[enDevice] == FALSE)
    {
        _stCecApiInfo.CecDevicesExisted[enDevice] = TRUE;

      #if 0 // don't know why this code is added here, it will cause CTS fail
        if (enDevice != E_LA_AUDIO_SYS)
        {
            msAPI_CEC_SetActiveDevice(enDevice);
        }
      #endif

        for(i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
        {
            if(msAPI_CEC_GetDeviceIdx(i)==0xFF)
            {
                msAPI_CEC_SetDeviceIdx(i, (U8)enDevice);
                printf("[Add New Device]    _au8CecDeviceIdx[%bx] = %bx\n",(MS_U8)i ,(MS_U8)enDevice);
                break;
            }
        }
        _u8CecDeviceCount++;

        // request new device info
        if(( (MsCEC_MSGLIST)  MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 1) == E_MSG_ACTIVE_SOURCE )&& ((MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 0)&0x0F)!=0x0F))
            ;
        else
        {
            msAPI_CEC_PostMsgToQueue((MsCEC_DEVICELA)(enDevice), E_MSG_SI_REQUEST_PHY_ADDR, 0, 0);
        }

        msAPI_CEC_ReportDevice();
    }
}

void msAPI_CEC_RemoveDevice(MsCEC_DEVICELA enDevice)
{
    U8 i, j;

    if(_stCecApiInfo.CecDevicesExisted[enDevice] == TRUE)
    {
        _stCecApiInfo.CecDevicesExisted[enDevice] = FALSE;

        for(i=0; i<E_LA_UNREGISTERED; i++)
        {
            if((U8)enDevice==msAPI_CEC_GetDeviceIdx(i))
            {
                for(j = i; j<E_LA_UNREGISTERED; j++)
                {
                    if(msAPI_CEC_GetDeviceIdx(j+1)!=0xFF)
                    {
                        msAPI_CEC_SetDeviceIdx(j, msAPI_CEC_GetDeviceIdx(j+1));
                        msAPI_CEC_SetDeviceIdx_PhyAddr(j, msAPI_CEC_GetDeviceIdx_PhyAddr(j+1));
                    }
                    else
                    {
                        msAPI_CEC_SetDeviceIdx(j, 0xFF);
                        msAPI_CEC_SetDeviceIdx_PhyAddr(j, 0);
                       break;
                    }
                }
                msAPI_CEC_SetDeviceName(enDevice, NULL, TRUE);
                break;
            }
        }

        printf("[Remove Device]    _au8CecDeviceIdx[%bx] = %bx\n",(MS_U8)i, (MS_U8)enDevice);
        _u8CecDeviceCount--;

        msAPI_CEC_ReportDevice();
    }
}

//***************************************************************************************
#if 0
MS_U8 msAPI_CEC_AMPHanlder(void)
{
    CEC_ERROR_CODE  res = E_CEC_FEATURE_ABORT;
    static U32 _u32AudioSysMonitorTimer =0;
    static U32 _u32AudioSysPostMsgTimer = 0;
    //static U8 _CountCheck =0;

    if(DB_HDMI_SETTING.g_enHDMIARC ==TRUE)// anvi
    {
        if(msAPI_Timer_DiffTimeFromNow(_u32AudioSysMonitorTimer) > B_MONITOR_CEC_AUDIO_SYS_PERIOD)
        {
            res = msAPI_CEC_PingDevice(E_LA_AUDIO_SYS);

            if (res != E_CEC_TX_SUCCESS && res != E_CEC_SYSTEM_BUSY)
            {
                CEC_MSG(printf("\n E_LA_AUDIO_SYS Is Not Exsit \n"));
                msAPI_CEC_RemoveDevice(E_LA_AUDIO_SYS);

                gCECAmpIsNotExit = TRUE;
                //_CountCheck++;
                //if(_CountCheck<10)
                //{
                MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);
                //}
                //printf("\n\n speak open [%s,%s,%d]\n\n",__FUNCTION__,__FILE__,__LINE__);
                            //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

                MUTE_Off();
            }

            if(res ==E_CEC_TX_SUCCESS)
            {
                //_CountCheck = 0;
                msAPI_CEC_AddDevice(E_LA_AUDIO_SYS);
                if(DB_HDMI_SETTING.g_enHDMIARC == TRUE)
                {
                    if(gCECAmpIsNotExit ==TRUE)
                    {
                        //printf("\ngCECAmpARCOffOnStatusCheck = FALSE [%s,%s,%d]\n",__FUNCTION__,__FILE__,__LINE__);
                        gCECAmpARCOffOnStatusCheck = FALSE;

                    }
                    else
                    {
                        gCECAmpARCOffOnStatusCheck = TRUE;
                    }
                    if(msAPI_Timer_DiffTimeFromNow(_u32AudioSysMonitorTimer)>900)
                    msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);
                }
                _u32AudioSysPostMsgTimer = msAPI_Timer_GetTime0();
            }

            _u32AudioSysMonitorTimer = msAPI_Timer_GetTime0();
        }
    }

    return TRUE;
}
#endif

//***************************************************************************************

void msAPI_CEC_InitVariableForPollingDeviceList(void)
{
    MS_U8 i;

    for(i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
    {
        _au8CecDeviceIdx[i] = 0xFF;
        _au16CecDeviceIdx_PhyAddr[i] = 0;
        _stCecApiInfo.CecDevicesExisted[i] = FALSE;
        strncpy((char *)_au8CecDeviceName[i], (char *)gStrCECDeviceType[i], strlen((char *)gStrCECDeviceType[i]));
    }
}

void msAPI_CEC_ForceImmediatelyPolling(BOOLEAN bCecDeviceListPolling)
{
    g_bCecForceImmediatelyPolling = TRUE;

    msAPI_CEC_InitVariableForPollingDeviceList();

    UNUSED(bCecDeviceListPolling);
}

void msAPI_CEC_PollingDevice(void)
{
    CEC_ERROR_CODE  res = E_CEC_FEATURE_ABORT;
    MsCEC_DEVICELA i = E_LA_TV;

    static MsCEC_DEVICELA _enDeviceIdex;
    static MS_BOOL CecDevicesExisted[15];

#if IMMEDIATELY_POLLING
    if ( g_bCecForceImmediatelyPolling )
    {
        CEC_POLLING_MSG_DBG(printf("\r\n[I] Start Polling CEC Device \n"));

        g_bCecForceImmediatelyPolling = FALSE;

        _bStartPolling = I_POLLING_START_PING;
        _enDeviceIdex = E_LA_TV;

        for (i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
        {
            CecDevicesExisted[i] = FALSE;
        }

        _u32CecDeviceMonitorTimer = msAPI_Timer_GetTime0();
    }
#endif


#if BACKGROUND_POLLING
    if (  (_bStartPolling == STATUS_POLLING_IDLE)
       && (msAPI_Timer_DiffTimeFromNow(_u32CecDeviceMonitorTimer) > B_MONITOR_CEC_DEVICE_PERIOD)
       )
    {
        CEC_POLLING_MSG_DBG(printf("\r\n[B] Start Polling CEC Device \n"));

        _bStartPolling = B_POLLING_START_PING;
        _enDeviceIdex = E_LA_TV;

        for (i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
        {
            CecDevicesExisted[i] = FALSE;
        }

        _u32CecDeviceMonitorTimer = msAPI_Timer_GetTime0();
    }

    /*
    *************************************************************************
    background polling start
    *************************************************************************
    */
    if (_bStartPolling == B_POLLING_START_PING)
    {
        if (msAPI_Timer_DiffTimeFromNow(_u32CecDeviceMonitorTimer) > B_CEC_POLLING_START_PING_PERIOD)
        {
            CEC_POLLING_MSG_DBG(printf("[B] Polling CEC Device 0x%x", _enDeviceIdex));

            res = msAPI_CEC_PingDevice(_enDeviceIdex);

            if (res & E_CEC_TX_SUCCESS)
            {
                CecDevicesExisted[_enDeviceIdex] = TRUE;

                CEC_POLLING_MSG_DBG(printf(" - ADD \n"));
            }
            else if(res & E_CEC_SYSTEM_BUSY)
            {
                CEC_MSG(printf("\n  E_CEC_SYSTEM_BUSY \n"));
            }
            else
            {
                CecDevicesExisted[_enDeviceIdex] = FALSE;
                CEC_POLLING_MSG_DBG(printf(" \n"));
            }

            if (_enDeviceIdex >= E_LA_FREE_USE)
            {
                _enDeviceIdex = E_LA_TV;
                for (i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
                {
                    if (CecDevicesExisted[i] == TRUE)
                    {
                        _enDeviceIdex = i;
                        break;
                    }
                }

                if (_enDeviceIdex != E_LA_TV)
                {
                    _bStartPolling = B_POLLING_GIVE_PHYSICAL_ADDRESS;

                    CEC_POLLING_MSG_DBG(printf("[B] Start <Give Physical Address>[%d] \n", _enDeviceIdex));
                }
                else
                {
                    _enDeviceIdex = E_LA_TV;
                    _bStartPolling = STATUS_POLLING_IDLE;

                    CEC_POLLING_MSG_DBG(printf("[B] Connect No CEC Device \n"));
                }
            }
            else
            {
                _enDeviceIdex++;
            }

            _u32CecDeviceMonitorTimer = msAPI_Timer_GetTime0();
        }
    }

    if (_bStartPolling == B_POLLING_GIVE_PHYSICAL_ADDRESS)
    {
        if (msAPI_Timer_DiffTimeFromNow(_u32CecDeviceMonitorTimer) > B_CEC_GIVE_PHYSICAL_ADDRESS_PERIOD)
        {
            CEC_POLLING_MSG_DBG(printf("[B] Reporting Physical Address 0x%x \n", _enDeviceIdex));

            msAPI_CEC_PostMsg_GivePhysicalAddress(DIRECTMSG, _enDeviceIdex);

            if (_enDeviceIdex < E_LA_UNREGISTERED)
                _enDeviceIdex++;

            while (  (_enDeviceIdex < E_LA_UNREGISTERED)
                  && (CecDevicesExisted[_enDeviceIdex] == FALSE) )
            {
                 _enDeviceIdex++;
            }

            if (_enDeviceIdex >= E_LA_UNREGISTERED)
            {
                CEC_POLLING_MSG_DBG(printf("[B] Done_ \n"));

                _enDeviceIdex = E_LA_TV;
                _bStartPolling = STATUS_POLLING_IDLE;
            }

            _u32CecDeviceMonitorTimer = msAPI_Timer_GetTime0();
        }
    }
    /*
    *************************************************************************
    background polling end
    *************************************************************************
    */
#endif


#if IMMEDIATELY_POLLING
    /*
    *************************************************************************
    immediately polling start
    *************************************************************************
    */
    if (_bStartPolling == I_POLLING_START_PING)
    {
        if (msAPI_Timer_DiffTimeFromNow(_u32CecDeviceMonitorTimer) > I_CEC_POLLING_START_PING_PERIOD)
        {
            res = E_CEC_FEATURE_ABORT;

            CEC_POLLING_MSG_DBG(printf("[I] Polling CEC Device 0x%x ", _enDeviceIdex));

            res = msAPI_CEC_PingDevice(_enDeviceIdex);

            if (res & E_CEC_TX_SUCCESS)
            {
                CecDevicesExisted[_enDeviceIdex] = TRUE;

                CEC_POLLING_MSG_DBG(printf(" - ADD \n"));
            }
            else if(res & E_CEC_SYSTEM_BUSY )
            {
             CEC_MSG(printf("\n  E_CEC_SYSTEM_BUSY \n"));
            }
            else
            {
                CecDevicesExisted[_enDeviceIdex] = FALSE;

                CEC_POLLING_MSG_DBG(printf(" \n"));
            }

            if (_enDeviceIdex >= E_LA_FREE_USE)
            {
                _enDeviceIdex = E_LA_TV;
                for (i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
                {
                    if (CecDevicesExisted[i] == TRUE)
                    {
                        _enDeviceIdex = i;
                        break;
                    }
                }

                if (_enDeviceIdex != E_LA_TV)
                {
                    _bStartPolling = I_POLLING_GIVE_PHYSICAL_ADDRESS;

                    CEC_POLLING_MSG_DBG(printf("[I] Start <Give Physical Address>[%d] \n", _enDeviceIdex));
                }
                else
                {
                    _enDeviceIdex = E_LA_TV;
                    _bStartPolling = STATUS_POLLING_IDLE;

                    CEC_POLLING_MSG_DBG(printf("[I] Connect No CEC Device \n"));
                }
            }
            else
            {
                _enDeviceIdex++;
            }

            _u32CecDeviceMonitorTimer = msAPI_Timer_GetTime0();
        }
    }

    if (_bStartPolling == I_POLLING_GIVE_PHYSICAL_ADDRESS)
    {
        if (msAPI_Timer_DiffTimeFromNow(_u32CecDeviceMonitorTimer) > I_CEC_GIVE_PHYSICAL_ADDRESS_PERIOD)
        {
            CEC_POLLING_MSG_DBG(printf("[I] Reporting Physical Address 0x%x \n", _enDeviceIdex));

            msAPI_CEC_PostMsg_GivePhysicalAddress(DIRECTMSG, _enDeviceIdex);

            if (_enDeviceIdex < E_LA_UNREGISTERED)
                _enDeviceIdex++;

            while (  (_enDeviceIdex < E_LA_UNREGISTERED)
                  && (CecDevicesExisted[_enDeviceIdex] == FALSE) )
            {
                _enDeviceIdex++;
            }

            if (_enDeviceIdex >= E_LA_UNREGISTERED)
            {
                if ( IsHDMIInUse() )
                {
                    _enDeviceIdex = E_LA_TV;

                    for (i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
                    {
                        if (CecDevicesExisted[i] == TRUE)
                        {
                            _enDeviceIdex = i;
                            break;
                        }
                    }

                    _bStartPolling = I_POLLING_REPORT_POWER_STATUS;
                    CEC_POLLING_MSG_DBG(printf("[I] Start <Give Device Power Status>[%d] \n", _enDeviceIdex));
                }
                else
                {
                    CEC_POLLING_MSG_DBG(printf("[I] Done \n"));

                    _enDeviceIdex = E_LA_TV;
                    _bStartPolling = STATUS_POLLING_IDLE;
                }
            }

            _u32CecDeviceMonitorTimer = msAPI_Timer_GetTime0();
        }
    }

    if (_bStartPolling == I_POLLING_REPORT_POWER_STATUS)
    {
        if (msAPI_Timer_DiffTimeFromNow(_u32CecDeviceMonitorTimer) > I_CEC_REPORT_POWER_STATUS_PERIOD)
        {
            CEC_POLLING_MSG_DBG(printf("[I] Reporting Power Status 0x%x \n", _enDeviceIdex));

            msAPI_CEC_PostMsg_GiveDevicePowerStatus(POSTMSG, _enDeviceIdex);

            if (_enDeviceIdex < E_LA_UNREGISTERED)
                _enDeviceIdex++;

            while (  (_enDeviceIdex < E_LA_UNREGISTERED)
                  && (CecDevicesExisted[_enDeviceIdex] == FALSE) )
            {
                 _enDeviceIdex++;
            }

            _u32CecDeviceMonitorTimer = msAPI_Timer_GetTime0();

            if (_enDeviceIdex >= E_LA_UNREGISTERED)
            {
                CEC_POLLING_MSG_DBG(printf("[I] Done \n"));

                _enDeviceIdex = E_LA_TV;
                _bStartPolling = STATUS_POLLING_IDLE;

                _u32CecDeviceMonitorTimer += B_MONITOR_CEC_DEVICE_PERIOD;
            }
        }
    }
    /*
    *************************************************************************
    immediately polling end
    *************************************************************************
    */
#endif

}


//**************************************************************************
//  [Function Name]:
//                   MsAPI_CECOSDMessage()
//  [Description]
//                   Set logical address to next active device
//  [Arguments]:
//                   device_index: activated device name
//                   str_index: message
//                   strlen: string length
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_OSDMessage(MS_U8 device_index, MS_U8* pstr, MS_U8 strlen_t)
{
    MS_U8 i, str_len;

    str_len = 0;
    for(str_len=0; str_len<11; str_len++)
    {
        gCECOSDStr[1+str_len] = gStrCECDeviceType[device_index][str_len];
        if(gStrCECDeviceType[device_index][str_len] == ' ')
            break;
    }
    str_len++;

    // byte 0 : string length
    // byte 1 ~ str_len : CEC device type
    // byte str_len+1 ~ str_len+strlen: CEC message
    for(i=0; i<strlen_t; i++)
    {
        gCECOSDStr[i+str_len+1] = *(pstr+i);
    }
    gCECOSDStr[0] = str_len+strlen_t;
    gCECOSDStr[str_len+strlen_t+1] = 0;
    #if 1//def ZUI
    //NG to call UI function in API?
    //MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
    //MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_CEC_DEVICE_MSGBOX);
    #else
    MApp_UiMenu_Show_Warning_Message_Dialog(MENU_CEC_DEVICE_ISR_MSG);
    #endif
}


static void msAPI_CEC_HandleFeatureAbort(MsCEC_DEVICELA enDeviceFA, MsCEC_DEVICELA enDeviceDstFA,
                                         MS_U8 u8opCode, MS_U8 u8reason)
{
    CEC_DPRINTF("UnSupport opCode =%bx \n", u8opCode);
    CEC_DPRINTF("UnSupport reason =%bx \n", u8reason);

    switch (u8opCode)      //CEC1.3a Table 7 ~ 27
    {
      #if SYSTEM_AUDIO_CONTROL_SUPPORT
        case E_MSG_SAC_GIVE_AUDIO_STATUS:
        {
        }
        break;

        case  E_MSG_ARC_REQUEST_ARC_INITATION:
        {
            if(enDeviceFA== E_LA_AUDIO_SYS && gCECAmpARCOffOnStatusCheck ==TRUE)
            {
                CEC_MSG(printf("\n Amp ARC OFF!\n"));
                gCECAmpARCOffOnStatusCheck=FALSE;
                gIsCECAmpARCOn = FALSE;
				#if 0
                printf("\n\n speak open [%s,%s,%d]\n\n",__FUNCTION__,__FILE__,__LINE__);
                MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);
                        //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

                //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

                MUTE_Off();
                #endif
            }
        }
        break;
      #endif


      #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
        case E_MSG_OSDNT_GIVE_OSD_NAME:
        {
            if (msAPI_CEC_IsDeviceExist(enDeviceFA) == TRUE )
                msAPI_CEC_SetDeviceName(enDeviceFA, NULL, TRUE);
        }
        break;
      #endif


      #if VENDOR_SPECIFIC_SUPPORT
        case E_MSG_VS_GIVE_VENDOR_ID:
        {
        }
        break;
      #endif

        default:
            break;
    }

    UNUSED(enDeviceDstFA);
    UNUSED(u8reason);
}



//**************************************************************************
//  [Function Name]:
//                   MsAPI_CECProcessCmd()
//  [Description]
//                   It used to parse CEC command
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_ProcessCmd(void)
{
    MS_U8 header, len;
    MS_U8 para0 = 0, para1 = 0, para2 = 0, para3 = 0;
    MsCEC_MSGLIST opcode;
    MsCEC_DEVICELA enDevice, enDeviceDst;
    MS_U8 u8Fifoidx;
    MS_U8 i;
    BOOLEAN bCheckFrameOK = TRUE;
    BOOLEAN bNewDeviceDetect = FALSE;
    MS_U32 u32StartTime, u32CheckTime;

    if (MApi_CEC_GetMsgCnt() == 0 ) return;  //no received message to process

    u32StartTime = msAPI_Timer_GetTime0();

    header = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 0);
    opcode = (MsCEC_MSGLIST)  MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 1);

    len = MApi_CEC_GetCmdLen();

    if (len>2)  para0  = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 2);
    if (len>3)  para1  = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 3);
    if (len>4)  para2  = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 4);
    if (len>5)  para3  = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 5);

    enDevice    = (MsCEC_DEVICELA)((header & 0xF0)>>4);
    enDeviceDst = (MsCEC_DEVICELA)(header & 0x0F);

#if  CEC_DEBUG
    printf("\n ========= [CEC] ========= \n");

    printf(" header   = 0x%bx \n", header);
    printf(" opcode   = 0x%bx \n", opcode);

    for (i=2; i<len; i++)
    {
        printf(" para%2d   =", (i-2));
        printf(" 0x%bx \n", MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), i));
    }
    printf(" enDevice = 0x%bx \n", enDevice);
    printf(" enDeviceDst = 0x%bx \n", enDeviceDst);
    printf(" ========================= \n");
#endif

    // Check Frame first
    switch (opcode)      //CEC1.3a Table 7 ~ 27
    {
    //----- One Touch Play ---------------
    #if ONE_TOUCH_PLAY_SUPPORT
        case E_MSG_OTP_IMAGE_VIEW_ON:     //if in standby, firstly power on
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTP_IMAGE_VIEW_ON(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_OTP_TEXT_VIEW_ON:      //if in standby, firstly power on
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTP_TEXT_VIEW_ON(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif
    //----- One Touch Play end ---------------


    //----- One Touch Play --------------
    //----- Routing Control --------------
    #if (ONE_TOUCH_PLAY_SUPPORT || ROUTING_CONTROL_SUPPORT)
        case E_MSG_ACTIVE_SOURCE:             //broadcast, if addressed, ignored
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ACTIVE_SOURCE(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if (ONE_TOUCH_PLAY_SUPPORT || ROUTING_CONTROL_SUPPORT)
    //----- One Touch Play end --------------
    //----- Routing Control end --------------


    //----- Routing Control --------------
    #if (ROUTING_CONTROL_SUPPORT)
        case E_MSG_RC_INACTIVE_SOURCE:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_INACTIVE_SOURCE(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_RC_REQ_ACTIVE_SOURCE:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_REQUEST_ACTIVE_SOURCE(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_RC_ROUTING_CHANGE:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 6) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_ROUTING_CHANGE(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_RC_ROUTING_INFO:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_ROUTING_INFO(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_RC_SET_STREM_PATH:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_SET_STREM_PATH(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if (ROUTING_CONTROL_SUPPORT)
    //----- Routing Control end --------------


    //----- Standby Command --------------
    #if STANDBY_COMMAND_SUPPORT
        case E_MSG_STANDBY:
            if (MApi_CEC_CheckFrame(E_TRANS_BOTHTYPE_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_STANDBY(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if STANDBY_COMMAND_SUPPORT
    //----- Standby Command end --------------


    //----- One Touch Record--------------
    #if ONE_TOUCH_RECORD_SUPPORT
        //case E_MSG_OTR_RECORD_ON:
        //case E_MSG_OTR_RECORD_OFF:
        case E_MSG_OTR_RECORD_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTR_RECORD_STATUS(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        // Initiate a recording using the <Record On> message, or send a <Feature Abort> [Cannot provide source]
        // if the presently displayed source is not recordable.
        case E_MSG_OTR_RECORD_TV_SCREEN:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTR_RECORD_TV_SCREEN(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if ONE_TOUCH_RECORD_SUPPORT
    //----- One Touch Record end --------------


    //----- Timer programmer -------------
    #if TIMER_PROGRAMMER_SUPPORT
        case E_MSG_TP_CLEAR_ANALOG_TIMER:
        case E_MSG_TP_CLEAR_DIGITAL_TIMER:
        case E_MSG_TP_CLEAR_EXT_TIMER:
        case E_MSG_TP_SET_ANALOG_TIMER:
        case E_MSG_TP_SET_DIGITAL_TIMER:
        case E_MSG_TP_SET_EXT_TIMER:
        case E_MSG_TP_SET_TIMER_PROGRAM_TITLE:
        case E_MSG_TP_TIMER_CLEARD_STATUS:
        case E_MSG_TP_TIMER_STATUS:
            break;
    #endif
    //----- Timer programmer end -------------


    //----- System Information -----------
    //----- Vendor Specific -----------
    #if (SYSTEM_INFORMATION_SUPPORT | VENDOR_SPECIFIC_SUPPORT)
        case E_MSG_SI_CEC_VERSION:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_CEC_VERSION(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SI_GET_CEC_VERSION:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_GET_CEC_VERSION(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if (SYSTEM_INFORMATION_SUPPORT | VENDOR_SPECIFIC_SUPPORT)
    //----- System Information end -----------
    //----- Vendor Specific end -----------



    //----- System Information -----------
    #if SYSTEM_INFORMATION_SUPPORT
        case E_MSG_SI_REQUEST_PHY_ADDR:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_REQUEST_PHY_ADDR(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SI_REPORT_PHY_ADDR:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 5) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_REPORT_PHY_ADDR(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SI_GET_MENU_LANGUAGE:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_GET_MENU_LANGUAGE(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SI_SET_MENU_LANGUAGE:
            printf("[CEC] E_MSG_SI_SET_MENU_LANGUAGE(0x%x) \n", opcode);
            printf(" len   = 0x%x \n", len);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
            break;

//        case E_MSG_SI_POLLING_MESSAGE:
//                break;
    #endif // #if SYSTEM_INFORMATION_SUPPORT
    //----- System Information end -----------


    //----- Deck Control Feature----------
    #if DECK_CONTROL_SUPPORT
        //case E_MSG_DC_DECK_CTRL:
        case E_MSG_DC_DECK_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DC_DECK_STATUS(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if DECK_CONTROL_SUPPORT
    //----- Deck Control Feature end -----------


    #if TUNER_CONTROL_SUPPORT
    //----- Tuner Control ----------------
        case E_MSG_TC_GIVE_TUNER_STATUS:
        case E_MSG_TC_SEL_ANALOG_SERVICE:
        case E_MSG_TC_SEL_DIGITAL_SERVICE:
        case E_MSG_TC_TUNER_DEVICE_STATUS:
        case E_MSG_TC_TUNER_STEP_DEC:
        case E_MSG_TC_TUNER_STEP_INC:
            break;
    #endif // #if TUNER_CONTROL_SUPPORT
    //----- Tuner Control end -----------


    #if VENDOR_SPECIFIC_SUPPORT
    //---------Vendor Specific -----------
        case E_MSG_VS_DEVICE_VENDOR_ID: // 0x87
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_VS_DEVICE_VENDOR_ID(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_VS_GIVE_VENDOR_ID:   // 0x8C
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_VS_GIVE_DEVICE_VENDOR_ID(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_VS_VENDOR_COMMAND:
        case E_MSG_VS_VENDOR_COMMAND_WITH_ID:
        case E_MSG_VS_VENDOR_RC_BUT_DOWN:
        case E_MSG_VS_VENDOR_RC_BUT_UP:
            break;
    #endif // #if VENDOR_SPECIFIC_SUPPORT
    //----- Vendor Specific end -----------


    #if OSD_DISPLAY_SUPPORT
    //----- OSD Display ------------------
        case E_MSG_SET_OSD_STRING:
            break;
    #endif // #if OSD_DISPLAY_SUPPORT
    //----- OSD Display end -----------


    #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
    //----- Device OSD Name Transfer  ----
//        case E_MSG_OSDNT_GIVE_OSD_NAME:
//            CEC_DPRINTF("*CEC*:E_MSG_OSDNT_GIVE_OSD_NAME(0x%x) \n", opcode);
//            break;

        case E_MSG_OSDNT_SET_OSD_NAME:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)    // at least 3 frames
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OSDNT_SET_OSD_NAME(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

    #endif // #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
    //----- Device OSD Name Transfer end -----------


    #if DEVICE_MENU_CONTROL_SUPPORT
    //----- Device Menu Control ----------
        //case E_MSG_DMC_MENU_REQUEST:
        case E_MSG_DMC_MENU_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DMC_MENU_STATUS(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if DEVICE_MENU_CONTROL_SUPPORT
    //----- Device Menu Control end -----------


    //----- Remote Control Passthrough ---
    //----- UI Message -------------------
    #if (DEVICE_MENU_CONTROL_SUPPORT || REMOTE_CONTROL_PASSTHROUGH_SUPPORT)
        case E_MSG_UI_PRESS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_UI_PRESS(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_UI_RELEASE:
            break;
    #endif // #if (DEVICE_MENU_CONTROL_SUPPORT || REMOTE_CONTROL_PASSTHROUGH_SUPPORT)
    //----- Remote Control Passthrough end -----------
    //----- UI Message end -----------


    //----- Power Status Support -----
    #if POWER_STATUS_SUPPORT
        case E_MSG_PS_GIVE_POWER_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_PS_GIVE_DEVICE_POWER_STATUS(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

      case E_MSG_PS_REPORT_POWER_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_PS_REPORT_POWER_STATUS(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if POWER_STATUS_SUPPORT
    //----- Power Status Support end ---------


    //----- System Audio Control ---------
    #if SYSTEM_AUDIO_CONTROL_SUPPORT
        case E_MSG_SAC_GIVE_AUDIO_STATUS:
            printf("[CEC] E_MSG_SAC_GIVE_AUDIO_STATUS(0x%x) \n", opcode);
            printf(" len   = 0x%x \n", len);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
            break;

        case E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS:
            printf("[CEC] E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS(0x%x) \n", opcode);
            printf(" len   = 0x%x \n", len);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
            break;

        case E_MSG_SAC_REPORT_AUDIO_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_REPORT_AUDIO_STATUS(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SAC_SET_SYSTEM_AUDIO_MODE:
            // support Directly addressed and Broadcast both
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 3) == 0)
                {
                    CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_SET_SYSTEM_AUDIO_MODE(0x%x) Frame Fail \n", opcode);
                    bCheckFrameOK = FALSE;
                }
            }
            break;

        case E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST:
            printf("[CEC] E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST(0x%x) \n", opcode);
            printf(" len   = 0x%x \n", len);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
            break;

        case E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SAC_SET_AUDIO_RATE:
            printf("[CEC] E_MSG_SAC_SET_AUDIO_RATE(0x%x) \n", opcode);
            printf(" len   = 0x%x \n", len);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
            break;
    #endif // #if SYSTEM_AUDIO_CONTROL_SUPPORT
    //----- System Audio Control end ---------

#if 1
    //----- Audio Return Channel Support ---------
    #if AUDIO_RETURN_CHANNEL_SUPPORT
        case E_MSG_ARC_INITIATE_ARC:
            printf("[CEC] E_MSG_ARC_INITIATE_ARC(0x%x) \n", opcode);
            printf(" len   = 0x%x \n", len);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
            break;

        case E_MSG_ARC_TERMINATED_ARC:
            printf("[CEC] E_MSG_ARC_TERMINATED_ARC(0x%x) \n", opcode);
            printf(" len   = 0x%x \n", len);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
            break;
    #endif // #if AUDIO_RETURN_CHANNEL_SUPPORT
    //----- Audio Return Channel Support end ---------

#endif
    //----- General Protocal Message -----
    #if GENERAL_PROTOCAL_SUPPORT
        //----- Feature Abort ----------------
        case E_MSG_FEATURE_ABORT:     //[DA],
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_FEATURE_ABORT(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        //----- Abort Message ----------------
        case E_MSG_ABORT_MESSAGE: //same as default, for testing
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ABORT_MESSAGE(0x%x) Frame Fail \n", opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if GENERAL_PROTOCAL_SUPPORT
    //----- General Protocal Message end -----


        default:    //not support opcode
            CEC_ERROR_DEBUG("[CEC] Not Support opCode(0x%x) \n", opcode);
            if ( (header & 0x0F) != 0x0F ) //broadcast will not respond feature abort
            {
                msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, enDevice, opcode, E_MSG_AR_UNRECOGNIZE_OPCDE);
            }
            break;
    }

    //***********************************************************************************

    // Frame Check OK
    if (bCheckFrameOK)
    {
        if (msAPI_CEC_IsDeviceExist(enDevice) == FALSE )
        {
            if (E_MSG_ABORT_MESSAGE !=  opcode )
            {
                msAPI_CEC_AddDevice(enDevice);
                bNewDeviceDetect = TRUE;
            }
        }

        gCECProcessCMDbyKey = FALSE;
        gCECProcessCMDKeycode = 0xFF;

        u32CheckTime = msAPI_Timer_DiffTimeFromNow(u32StartTime);
        //printf("[TIME] CEC_ProcessCmd: %ld\n", u32CheckTime);

        switch (opcode)      //CEC1.3a Table 7 ~ 27
        {
        //----- One Touch Play ---------------
        #if ONE_TOUCH_PLAY_SUPPORT
            case E_MSG_OTP_IMAGE_VIEW_ON:     //if in standby, firstly power on
            {
                CEC_DPRINTF("[CEC] E_MSG_OTP_IMAGE_VIEW_ON(0x%x) \n", opcode);

                // show OSD message to report image view on
                msAPI_CEC_SetActiveDevice(enDevice);  // anvi cec
                msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Image View On", 13);
                MApi_CEC_SetActiveLogicalAddress((MsCEC_DEVICELA) ((header & 0xF0)>>4));
                msAPI_CEC_SetActiveDevice((MsCEC_DEVICELA) ((header & 0xF0)>>4));

                CEC_DPRINTF("\r\n=IMAGE_VIEW_ON= %bd\r\n", MApi_CEC_GetPowerStatus());
                if(MApi_CEC_GetPowerStatus() != E_MSG_PWRSTA_ON)    //when power off, leave standby
                {
                    gCECProcessCMDbyKey = TRUE;
                    IR_CODE = IRKEY_POWER;
                    g_bIrDetect = TRUE;
                    //g_bIRRepeat = 0;
                }
                else // remove text, OSD menu or PIP
                {
                    if(!msAPI_CEC_IsByPass())
                    {
                        #if 1//def ZUI
                        MApp_ZUI_ACT_ShutdownOSD();
                        #else
                        MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                        #endif
                    }
                }
                break;
            }

            case E_MSG_OTP_TEXT_VIEW_ON:      //if in standby, firstly power on
            {
                CEC_DPRINTF("[CEC] E_MSG_OTP_TEXT_VIEW_ON(0x%x) \n", opcode);

                // show OSD message to report text veiw on
                msAPI_CEC_SetActiveDevice(enDevice);  // anvi cec
                msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Text View On", 12);
                MApi_CEC_SetActiveLogicalAddress((MsCEC_DEVICELA) ((header & 0xF0)>>4));
                msAPI_CEC_SetActiveDevice((MsCEC_DEVICELA) ((header & 0xF0)>>4));

                CEC_DPRINTF("\r\n=TEXT_VIEW_ON= %bd\r\n", MApi_CEC_GetPowerStatus());
                if(MApi_CEC_GetPowerStatus() != E_MSG_PWRSTA_ON)    //when power off, leave standby
                {
                    gCECProcessCMDbyKey = TRUE;
                    IR_CODE = KEY_POWER;
                    g_bIrDetect = TRUE;
                }
                else // remove text, OSD menu or PIP
                {
                    if(!msAPI_CEC_IsByPass())
                    {
                        #if 1//def ZUI
                        MApp_ZUI_ACT_ShutdownOSD();
                        #else
                        MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                        #endif
                    }
                }
                break;
            }
        #endif // #if ONE_TOUCH_PLAY_SUPPORT
        //----- One Touch Play end ---------------

        //----- One Touch Play --------------
        //----- Routing Control --------------
        #if (ONE_TOUCH_PLAY_SUPPORT || ROUTING_CONTROL_SUPPORT)
            case E_MSG_ACTIVE_SOURCE:
            {
                CEC_DPRINTF("[CEC] E_MSG_ACTIVE_SOURCE(0x%x) \n", opcode);

                if(msAPI_CEC_IsByPass())
                {
                    CEC_DPUTSTR("Active source cmd is cec-by-pass\n");
                    break;
                }

                MApi_CEC_SetActivePowerStatus(E_MSG_PWRSTA_ON);
                msAPI_CEC_SetActiveDevice(enDevice);  // anvi cec start
                _stCecApiInfo.ActivePhysicalAddress[0] = para0 ;
                _stCecApiInfo.ActivePhysicalAddress[1] = para1 ;
                // anvi cec end
                MApi_CEC_SetActivePhysicalAddress(para0, para1);
                MApi_CEC_SetActiveLogicalAddress((MsCEC_DEVICELA) ((header & 0xF0)>>4));
                msAPI_CEC_SetActiveDevice((MsCEC_DEVICELA) ((header & 0xF0)>>4));

                // show OSD message to report active source
                msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Active Source", 13);
                CEC_DPRINTF("\r\n=Active Source= %bd\r\n", MApi_CEC_GetPowerStatus());

                printf("\n CEC Active Source:%x\n",para0);//Please Don't Remove This Line For Bug Tracking

            #if ( INPUT_HDMI_VIDEO_COUNT )
                if(HIGHNIBBLE(para0) == 0x1)         //switch to HDMI1 input
                {
                    if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI)
                    {
                        //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI;
                        #ifdef ENABLE_DMP
                        if(IsStorageInUse())
                        {
                            MApp_MPlayer_StopPreview();
                            MApp_MPlayer_Stop();
                            MApp_MPlayer_ExitMediaPlayer();
                        }
                        #endif
                        #if 1//def ZUI
                        MApp_ZUI_ACT_ShutdownOSD();
                        #else
                        MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT); // remove existed menu
                        #endif
                        //MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
                        MApp_ZUI_ACT_InputSourceSwitch(UI_INPUT_SOURCE_HDMI);            //4Tenny at 20100624: Replaced above code for avoiding DTV no signal when switch back to DTV
                        #ifdef ENABLE_DMP
                        MApp_ChannelChange_VariableInit();
                        MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
                        #endif
                        CEC_DPUTSTR("\r\nswitch into HDMI1");
                    }
                }
             #if ( INPUT_HDMI_VIDEO_COUNT >= 2 )
                else if(HIGHNIBBLE(para0) == 0x2)    //switch to HDMI2 input
                {
                    if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI2)
                    {
                        //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI2;
                        #ifdef ENABLE_DMP
                        if(IsStorageInUse())
                        {
                            MApp_MPlayer_StopPreview();
                            MApp_MPlayer_Stop();
                            MApp_MPlayer_ExitMediaPlayer();
                        }
                        #endif
                        #if 1//def ZUI
                        MApp_ZUI_ACT_ShutdownOSD();
                        #else
                        MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT); // remove existed menu
                        #endif
                        //MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
                        MApp_ZUI_ACT_InputSourceSwitch(UI_INPUT_SOURCE_HDMI2);            //4Tenny at 20100624: Replaced above code for avoiding DTV no signal when switch back to DTV
                        #ifdef ENABLE_DMP
                        MApp_ChannelChange_VariableInit();
                        MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
                        #endif
                        CEC_DPUTSTR("\r\nswitch into HDMI2");
                    }
                }
              #if( INPUT_HDMI_VIDEO_COUNT >= 3 )
                else if(HIGHNIBBLE(para0) == 0x3)    //switch to HDMI3 input
                {
                    if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI3)
                    {
                        //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI3;
                        #ifdef ENABLE_DMP
                        if(IsStorageInUse())
                        {
                            MApp_MPlayer_StopPreview();
                            MApp_MPlayer_Stop();
                            MApp_MPlayer_ExitMediaPlayer();
                        }
                        #endif
                        #if 1//def ZUI
                        MApp_ZUI_ACT_ShutdownOSD();
                        #else
                        MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT); // remove existed menu
                        #endif
                        //MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
                        MApp_ZUI_ACT_InputSourceSwitch(UI_INPUT_SOURCE_HDMI3);            //4Tenny at 20100624: Replaced above code for avoiding DTV no signal when switch back to DTV
                        #ifdef ENABLE_DMP
                        MApp_ChannelChange_VariableInit();
                        MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
                        #endif
                        CEC_DPUTSTR("\r\nswitch into HDMI3");
                    }
                }
               #if( INPUT_HDMI_VIDEO_COUNT >= 4 )
                else if(HIGHNIBBLE(para0) == 0x4)    //switch to HDMI3 input
                {
                    if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI4)
                    {
                        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI4;
                        #if 1//def ZUI
                        MApp_ZUI_ACT_ShutdownOSD();
                        #else
                        MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT); // remove existed menu
                        #endif
                        MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
                        CEC_DPUTSTR("\r\nswitch into HDMI4");
                    }
                }
               #endif // #if( INPUT_HDMI_VIDEO_COUNT >= 4 )
              #endif // #if( INPUT_HDMI_VIDEO_COUNT >= 3 )
             #endif // #if ( INPUT_HDMI_VIDEO_COUNT >= 2 )
            #endif // #if ( INPUT_HDMI_VIDEO_COUNT )

                msAPI_CEC_PostMsg_GiveOSDName(DIRECTMSG, enDevice);

            #if 0
                if (stGenSetting.g_SysSetting.g_bHdmiCecSpeakerMode==DISABLE)
                {
                    //g_bCecAudioSysEnable = TRUE;
                    //MApp_Aud_EnableMute(ENABLE);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    msAPI_CEC_PostMsg_SystemAudioModeReq(DIRECTMSG, (MS_U16)((para0<<8)|para1));
                }
            #endif

                /*
                CEC compliance test 11.1.15-1: sends a correctly formateed <System Audio Mode Request> message.
                */
                if (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
                {
                    U16 u16AudioSys = 0x00;

                    if ( msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) )
                    {
                        for (i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
                        {
                            if (msAPI_CEC_GetDeviceIdx(i) == E_LA_AUDIO_SYS)
                            {
                                u16AudioSys = msAPI_CEC_GetDeviceIdx_PhyAddr(i);
                            }
                        }

                        if ( (u16AudioSys & 0xF000) == ((para0<<8) & 0xF000) )
                            msAPI_CEC_PostMsg_SystemAudioModeReq(DIRECTMSG, (MS_U16)((para0<<8)|para1));
                    }
                }

            #if 0   // don't know the reason to do the following
                if ((enDevice != E_LA_AUDIO_SYS)&&(!gCECUserControlEnable))
                {
                    msAPI_CEC_PostMsg_MenuRequest(DIRECTMSG, enDevice, E_MSG_MENU_REQ_QUERY);
                }
            #endif

                break;
            }
        #endif // #if (ONE_TOUCH_PLAY_SUPPORT || ROUTING_CONTROL_SUPPORT)
        //----- One Touch Play end --------------
        //----- Routing Control end --------------


        //----- Routing Control --------------
        #if (ROUTING_CONTROL_SUPPORT)
            case E_MSG_RC_INACTIVE_SOURCE:
            {
                CEC_DPRINTF("[CEC] E_MSG_RC_INACTIVE_SOURCE(0x%x) \n", opcode);

                //broadcast, addressed, no para
                //cec anvi
                _stCecApiInfo.ActivePhysicalAddress[0] = 0x0 ;
                _stCecApiInfo.ActivePhysicalAddress[1] = 0x0 ;
                CEC_DPRINTF("\r\n=E_MSG_RC_INACTIVE_SOURCE=, PHY= 0x%bx", para0);
                CEC_DPRINTF(" 0x%bx\r\n", para1);
                break;
            }

            case E_MSG_RC_REQ_ACTIVE_SOURCE:
            {
                CEC_DPRINTF("[CEC] E_MSG_RC_REQ_ACTIVE_SOURCE(0x%x) \n", opcode);

                if ( !IsHDMIInUse() )
                {
                    MS_U8 au8TxBuf[2];

                    au8TxBuf[0] = 0x00;
                    au8TxBuf[1] = 0x00;

                    msAPI_CEC_PostMsg_ActiveSource(POSTMSG, au8TxBuf);
                }
                break;
            }

            case E_MSG_RC_ROUTING_CHANGE:
            {
                CEC_DPRINTF("[CEC] E_MSG_RC_ROUTING_CHANGE(0x%x) \n", opcode);

                if ( !IsHDMIInUse() && (enDevice != E_LA_TV) )
                {
                    MS_U8 au8TxBuf[2];

                    au8TxBuf[0] = 0x00;
                    au8TxBuf[1] = 0x00;

                    msAPI_CEC_PostMsg_ActiveSource(POSTMSG, au8TxBuf);
                }

                break;
            }

            case E_MSG_RC_ROUTING_INFO:
            {
                CEC_DPRINTF("[CEC] E_MSG_RC_ROUTING_INFO(0x%x) \n", opcode);

                if (msAPI_CEC_IsDeviceExist(enDevice) == TRUE)
                {
                    MS_U8 au8TxBuf[2];

                    au8TxBuf[0] = para0;
                    au8TxBuf[1] = para1;

                    CEC_DPRINTF("\n PhyAddr of hDevice 0x%x is changing", enDevice );
                    CEC_DPRINTF(" from [0x%x] \n",(_stCecApiInfo.ActivePhysicalAddress[0]<<8|_stCecApiInfo.ActivePhysicalAddress[1]) );

                    _stCecApiInfo.ActivePhysicalAddress[0] = para0 ;
                    _stCecApiInfo.ActivePhysicalAddress[1] = para1 ;

                    CEC_DPRINTF(" to [0x%x] \n", (_stCecApiInfo.ActivePhysicalAddress[0]<<8|_stCecApiInfo.ActivePhysicalAddress[1]) );

                    //VL++ fix CTS 9.4-2
                    msAPI_CEC_PostMsg_RoutingInformation(DIRECTMSG, au8TxBuf);
                }
                break;
            }

          #if 0 // not supported yet.
            case E_MSG_RC_SET_STREM_PATH:
            {
                CEC_DPRINTF("[CEC] E_MSG_RC_SET_STREM_PATH(0x%x) not Support \n", opcode);

                break;
            }
          #endif
        #endif // #if (ROUTING_CONTROL_SUPPORT)
        //----- Routing Control end --------------


        //----- Standby Command --------------
        #if STANDBY_COMMAND_SUPPORT
            case E_MSG_STANDBY:
            {
                MsCEC_MSG_POWER_STATUS_PARM enPowerStatus;

                CEC_DPRINTF("[CEC] E_MSG_STANDBY(0x%x) \n", opcode);

                enPowerStatus = MApi_CEC_GetPowerStatus();
                CEC_DPRINTF(" =E_MSG_STANDBY= %bd \n", enPowerStatus);

                /*
                CEC compliance test 11.1.3-2: responds to broadcast <Standby> messages.
                CEC compliance test 11.1.3-3: responds to directed <Standby> messages.
                */
                if ( enPowerStatus == E_MSG_PWRSTA_ON )    //when power on, not standby
                {
                    CEC_DPUTSTR(" =Standby= \n");
                    u8KeyCode = KEY_POWER;
                }
                break;
            }
        #endif // #if STANDBY_COMMAND_SUPPORT
        //----- Standby Command end --------------


        //----- One Touch Record--------------
        #if ONE_TOUCH_RECORD_SUPPORT
          #if 0 // not supported yet.
            case E_MSG_OTR_RECORD_ON:
            {
                CEC_DPRINTF("[CEC] E_MSG_OTR_RECORD_ON(0x%x) \n", opcode);
                break;
            }

            case E_MSG_OTR_RECORD_OFF:
            {
                CEC_DPRINTF("[CEC] E_MSG_OTR_RECORD_OFF(0x%x) \n", opcode);
                break;
            }
          #endif

            case E_MSG_OTR_RECORD_STATUS:
            {
                CEC_DPRINTF("[CEC] E_MSG_OTR_RECORD_STATUS(0x%x) \n", opcode);
                CEC_DPRINTF(" = RECORD_STATUS %bd = \n", para0);

                switch(para0)
                {
                    case E_MSG_RECORD_INFO_RECORDING_OWN_SOURCE:  // Recording currently selected source
                    case E_MSG_RECORD_INFO_RECORDING_DIGITAL_SERVICE:  // Recording Digital Service
                        gCECRecordEnable = TRUE;
                        // show OSD message to report recording source
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Recording", 9);
                        CEC_DPRINTF("\r\n CEC recording source is = %bx\r\n", para0);
                        break;

                    case E_MSG_RECORD_INFO_NO_RECORDING_DIGITAL_SERVICE:  // unable to record Digital Service, no suitable tuner.
                #if(HDMI_CEC_VERSION == CEC_VERSION_13a)
                    case E_MSG_RECORD_INFO_NO_RECORDING_ANALOGUE_SERVICE:  // unable to record Analogue Service, no suitable tuner.
                    case E_MSG_RECORD_INFO_NO_RECORDING_REQ_SERVICE:  // unable to select required service, Has suitable tuner, but the requested parameters are invalid or out of range for that tuner.
                    case E_MSG_RECORD_INFO_NO_RECORDING_INVALID_EXTERNAL_PLUG_NUMBER:  // invalid External plug number
                    case E_MSG_RECORD_INFO_NO_RECORDING_INVALID_EXTERNAL_PHYSICAL_ADDRESS:  // invalid External Physical Address
                    case E_MSG_RECORD_INFO_NO_RECORDING_CA_NOT_SUPPORT:  // CA system not supported
                    case E_MSG_RECORD_INFO_NO_RECORDING_CA_NO:  // No or Insufficient CA Entitlements
                    case E_MSG_RECORD_INFO_NO_RECORDING_COPY_NEVER:  // Not allowed to copy source, source is copy never.
                    case E_MSG_RECORD_INFO_NO_RECORDING_NO_FURTHER_COPY:  // No further copies allowed
                    case E_MSG_RECORD_INFO_NO_RECORDING_NOT_ENOUGH_SPACE:  // not enough space available
                    case E_MSG_RECORD_INFO_NO_RECORDING_PARENTAL_LOCK:  // Parental Lock On
                #endif
                    case E_MSG_RECORD_INFO_NO_RECORDING_NO_MEDIA:  // no media
                    case E_MSG_RECORD_INFO_NO_RECORDING_MEDIA_PROTECTED:  // media protected
                    case E_MSG_RECORD_INFO_NO_RECORDING_NO_SOURCE:  // no source signal
                    case E_MSG_RECORD_INFO_NO_RECORDING_OTHER_REASON:  // No recording V other reason
                        gCECRecordEnable= FALSE;
                        // show OSD message to report no recording result
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Recording Fail!", 15);
                        CEC_DPRINTF("\r\n CEC no recording, error code is = %bx\r\n", para0);
                        break;

                    case E_MSG_RECORD_INFO_NO_RECORDING_ALREADY_RECORDING:  // already recording
                        gCECRecordEnable= TRUE;
                        CEC_DPRINTF("\r\n CEC already recording, error code is = %bx\r\n", para0);
                        break;

                    case E_MSG_RECORD_INFO_NO_RECORDING_PLAYING:  // Playing
                        gCECRecordEnable= FALSE;
                        // show OSD message to report recording source
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Recording Fail - Playing", 24);
                        CEC_DPRINTF("\r\n CEC no recording, error code is = %bx\r\n", para0);
                        break;

                    case E_MSG_RECORD_INFO_NO_RECORDING_MEDIA_PROBLEM:  // media problem
                        gCECRecordEnable= FALSE;
                        // show OSD message to report recording source
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Recording Fail - Media", 22);
                        CEC_DPRINTF("\r\n CEC no recording, error code is = %bx\r\n", para0);
                        break;

                #if(HDMI_CEC_VERSION == CEC_VERSION_13a)
                    case E_MSG_RECORD_INFO_RECORDING_TERMINATED_NORMALLY:  // Recording terminated normally, can optionally be sent in response to a <Record Off> message.
                    case E_MSG_RECORD_INFO_RECORDING_ALREADY_TERMINATED:  // Recording has already terminated, can optionally be sent in response to a <Record Off> message.
                        gCECRecordEnable= FALSE;
                        // show OSD message to report recording terminated status
                        CEC_DPRINTF("\r\n CEC recording terminated status is = %bx\r\n", para0);
                        break;
                #endif

                    default:
                        // show OSD message to report unknow status
                        CEC_DPRINTF("\r\n CEC recording unknow state = %bx\r\n", para0);
                        break;
                }

                break;
            }

            // Initiate a recording using the <Record On> message, or send a <Feature Abort> [Cannot provide source]
            // if the presently displayed source is not recordable.
            case E_MSG_OTR_RECORD_TV_SCREEN:
            {
                CEC_DPRINTF("[CEC] E_MSG_OTR_RECORD_TV_SCREEN(0x%x) \n", opcode);

                MsAPI_CEC_Msg_RecordOn(MApi_CEC_GetActiveLogicalAddress(), E_MSG_RECORD_TYPE_OWN_SOURCE);

                break;
            }
        #endif // #if ONE_TOUCH_RECORD_SUPPORT
        //----- One Touch Record end --------------


        //----- Timer programmer -------------
        #if TIMER_PROGRAMMER_SUPPORT
            case E_MSG_TP_CLEAR_ANALOG_TIMER:
            case E_MSG_TP_CLEAR_DIGITAL_TIMER:
            case E_MSG_TP_CLEAR_EXT_TIMER:
            case E_MSG_TP_SET_ANALOG_TIMER:
            case E_MSG_TP_SET_DIGITAL_TIMER:
            case E_MSG_TP_SET_EXT_TIMER:
            case E_MSG_TP_SET_TIMER_PROGRAM_TITLE:
            case E_MSG_TP_TIMER_CLEARD_STATUS:
            case E_MSG_TP_TIMER_STATUS:
                break;
        #endif // #if TIMER_PROGRAMMER_SUPPORT
        //----- Timer programmer end -------------


        //----- System Information -----------
        //----- Vendor Specific -----------
        #if (SYSTEM_INFORMATION_SUPPORT | VENDOR_SPECIFIC_SUPPORT)
            case E_MSG_SI_CEC_VERSION:
            {
                CEC_DPRINTF("[CEC] E_MSG_SI_CEC_VERSION(0x%x) \n", opcode);

                MApi_CEC_SetActiveDeviceCECVersion(para0);
                CEC_DPRINTF(" Device 0x%x =>", enDevice);

                switch(para0)
                {
                    case CEC_VERSION_11:
                        CEC_DPUTSTR(" CEC Ver 1.1 \n");
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"CEC Ver 1.1", 11);
                        break;
                    case CEC_VERSION_12:
                        CEC_DPUTSTR(" CEC Ver 1.2 \n");
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"CEC Ver 1.2", 11);
                        break;
                    case CEC_VERSION_12a:
                        CEC_DPUTSTR(" CEC Ver 1.2a \n");
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"CEC Ver 1.2a", 12);
                        break;
                    case CEC_VERSION_13:
                        CEC_DPUTSTR(" CEC Ver 1.3 \n");
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"CEC Ver 1.3", 11);
                        break;
                    case CEC_VERSION_13a:
                        CEC_DPUTSTR(" CEC Ver 1.3a \n");
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"CEC Ver 1.3a", 12);
                        break;

                    case CEC_VERSION_14:
                        //CEC_DPUTSTR(printf(" CEC Ver 1.4 \n"));
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"CEC Ver 1.4", 11);
                        break;

                    default:
                        CEC_DPUTSTR(" Unknow CEC Ver \n");
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Unknow CEC Ver", 14);
                        break;
                }
                break;
            }

            case E_MSG_SI_GET_CEC_VERSION:
            {
                //MS_U8 u8Version;

                CEC_DPRINTF("[CEC] E_MSG_SI_GET_CEC_VERSION(0x%x) \n", opcode);

                msAPI_CEC_PostMsg_CECVersion(DIRECTMSG, enDevice, HDMI_CEC_VERSION);
                break;
            }
        #endif // #if (SYSTEM_INFORMATION_SUPPORT | VENDOR_SPECIFIC_SUPPORT)
        //----- System Information end -----------
        //----- Vendor Specific end -----------


        //----- System Information -----------
        #if SYSTEM_INFORMATION_SUPPORT
            case E_MSG_SI_REQUEST_PHY_ADDR:
            {
                CEC_DPRINTF("[CEC] E_MSG_SI_GIVE_PHYSICAL_ADDRESS(0x%x) \n", opcode);

                msAPI_CEC_PostMsg_ReportPhysicalAddress(DIRECTMSG);
                break;
            }

            case E_MSG_SI_REPORT_PHY_ADDR:
            {
                CEC_DPRINTF("[CEC] E_MSG_SI_REPORT_PHYSICAL_ADDRESS(0x%x) \n", opcode);

                for(i=0; i<=msAPI_CEC_GetDeviceTotalNum(); i++)
                {
                    if (enDevice == msAPI_CEC_GetDeviceIdx(i))
                    {
                        msAPI_CEC_SetDeviceIdx_PhyAddr(i, (U16)((para0<<8) | para1));

                        MApi_CEC_SetActivePhysicalAddress(para0, para1);
                        CEC_DPRINTF(" SetActivePhysicalAddress : 0x%x \n", (para0<<8|para1));
                        MApi_CEC_SetActiveDeviceType((MsCEC_DEVICE_TYPE) para2);
                        CEC_DPRINTF(" SetActiveDeviceType : 0x%x \n", para2);

                        // anvi cec
                        _stCecApiInfo.ActivePhysicalAddress[0] = para0;
                        _stCecApiInfo.ActivePhysicalAddress[1] = para1;
                    }
                }

                if ( (enDevice != E_LA_BROADCAST) && bNewDeviceDetect )
                {
                  #if VENDOR_SPECIFIC_SUPPORT
                    msAPI_CEC_PostMsg(enDevice, E_MSG_VS_GIVE_VENDOR_ID, 0, 0);
                  #endif

                  #if (SYSTEM_INFORMATION_SUPPORT | VENDOR_SPECIFIC_SUPPORT)
                    msAPI_CEC_PostMsg(enDevice, E_MSG_SI_GET_CEC_VERSION, 0, 0);
                  #endif

                  #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
                    msAPI_CEC_PostMsg(enDevice, E_MSG_OSDNT_GIVE_OSD_NAME, 0, 0);
                  #endif
                }

            #if 0
                if ( ( (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI) && (HIGHNIBBLE(para0)  == 0x01) )
                  #if( INPUT_HDMI_VIDEO_COUNT >= 2 )
                   ||( (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI2) && (HIGHNIBBLE(para0)  == 0x02))
                  #endif
                  #if( INPUT_HDMI_VIDEO_COUNT >= 3 )
                   ||( (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI3) && (HIGHNIBBLE(para0)  == 0x03))
                  #endif
                  #if( INPUT_HDMI_VIDEO_COUNT >= 4 )
                   ||( (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_HDMI4) && (HIGHNIBBLE(para0)  == 0x04))
                  #endif
                   )
                {
                    MS_U8 txbuf[2];

                    txbuf[0] = para0;
                    txbuf[1] = para1;

                    msAPI_CEC_PostMsg_SetStreamPath(DIRECTMSG, txbuf);
                }

                if ( (enDevice != E_LA_AUDIO_SYS) && (!gCECUserControlEnable) )
                {
                    msAPI_CEC_PostMsg_MenuRequest(DIRECTMSG, enDevice, E_MSG_MENU_REQ_QUERY)
                }
            #endif
                /*
                CEC compliance test 11.1.15-4: issues a <Give System Audio Mode Status> message to the amplifier.
                */

                if ( (enDevice == E_LA_AUDIO_SYS)
                   &&(stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
                   )
                {
                    msAPI_CEC_PostMsg_GiveSystemAudioModeStatus(POSTMSG, E_LA_AUDIO_SYS);
                }

                msAPI_CEC_ReportDevice();

                break;
            }

            case E_MSG_SI_GET_MENU_LANGUAGE:
            {
                CEC_DPRINTF("[CEC] E_MSG_SI_GET_MENU_LANGUAGE(0x%x) \n", opcode);

                /*
                   fixed 11.1.6-5 Ensure that the DUT responds correctly to a <Get Menu Language> message
                   with a different version number to that it holds, coming from various logical addresses
                   including the unregistered address.
                */
            #if(ENABLE_DTV) // why ENABLE_DTV?
                {
                    EN_LANGUAGE eLanguage;
                    EN_SI_LANGUAGE eCecLangCodeId;
                    U8 u8CecLangCode[MAX_ISO639CODE_LENGTH] = { 0 };

                    eLanguage = MApp_GetMenuLanguage();
                    eCecLangCodeId = MApp_GetSILanguage(eLanguage);

                    if (TRUE == msAPI_SI_GetISOLangCodeFromIndex(eCecLangCodeId, u8CecLangCode))
                    {
                        msAPI_CEC_PostMsg_SetMenuLang(DIRECTMSG, u8CecLangCode);
                    }
                }
            #endif

                break;
            }

            case E_MSG_SI_SET_MENU_LANGUAGE:
            {
                break;
            }

          #if 0 // not supported yet.
            case E_MSG_SI_POLLING_MESSAGE:
                    break;
          #endif
        #endif // #if SYSTEM_INFORMATION_SUPPORT
        //----- System Information end -----------


        //----- Deck Control Feature----------
        #if DECK_CONTROL_SUPPORT
            case E_MSG_DC_DECK_STATUS:
            {
                CEC_DPRINTF("[CEC] E_MSG_DC_DECK_STATUS(0x%x) \n", opcode);

                gCECDeckStatus = (MsCEC_MSG_DC_DECK_STATUS_PARM) para0;

                break;
            }

          #if 0 // not supported yet.
            case E_MSG_DC_DECK_CTRL:
            case E_MSG_DC_GIVE_DECK_STATUS:
            case E_MSG_DC_PLAY:
            {
                break;
            }
          #endif
        #endif
        //----- Deck Control end -----------


        //----- Tuner Control ----------------
        #if TUNER_CONTROL_SUPPORT
            case E_MSG_TC_GIVE_TUNER_STATUS:
            case E_MSG_TC_SEL_ANALOG_SERVICE:
            case E_MSG_TC_SEL_DIGITAL_SERVICE:
            case E_MSG_TC_TUNER_DEVICE_STATUS:
            case E_MSG_TC_TUNER_STEP_DEC:
            case E_MSG_TC_TUNER_STEP_INC:
            {
                break;
            }
        #endif
        //----- Tuner Control end -----------


        //---------Vendor Specific -----------
        #if VENDOR_SPECIFIC_SUPPORT
            case E_MSG_VS_DEVICE_VENDOR_ID:
            {
                CEC_DPRINTF("[CEC] E_MSG_VS_DEVICE_VENDOR_ID(0x%x) \n", opcode);

                printf(" <Device Vendor ID> 0x%x: ", enDevice);
                printf(" = 0x%x,", para0);
                printf(" 0x%x,",   para1);
                printf(" 0x%x \n", para2);
                break;
            }

            case E_MSG_VS_GIVE_VENDOR_ID:
            case E_MSG_VS_VENDOR_COMMAND:
            case E_MSG_VS_VENDOR_COMMAND_WITH_ID:
            case E_MSG_VS_VENDOR_RC_BUT_DOWN:
            case E_MSG_VS_VENDOR_RC_BUT_UP:
            {
                break;
            }
        #endif // #if VENDOR_SPECIFIC_SUPPORT
        //----- Vendor Specific end -----------


        //----- OSD Display ------------------
        #if OSD_DISPLAY_SUPPORT
            case E_MSG_SET_OSD_STRING:
            {
                break;
            }
        #endif
        //----- OSD Display end -----------


        //----- Device OSD Name Transfer  ----
        #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
            case E_MSG_OSDNT_GIVE_OSD_NAME:
            {
//                CEC_DPRINTF("*CEC*:E_MSG_OSDNT_GIVE_OSD_NAME(0x%x) \n", opcode);
                break;
            }

            case E_MSG_OSDNT_SET_OSD_NAME:
            {
                U8 u8NameLen, au8StringBuffer[13];

                CEC_DPRINTF("[CEC] E_MSG_OSDNT_SET_OSD_NAME(0x%x) \n", opcode);

                memset(&au8StringBuffer, 0x00, 13);

                if(len> 2 && para0!=0)
                {
                    for(u8NameLen=0;u8NameLen<(len-2);u8NameLen++)
                    {
                        au8StringBuffer[u8NameLen] = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), u8NameLen+2);
                    }
                    au8StringBuffer[u8NameLen]= '\0';

                    msAPI_CEC_SetDeviceName(enDevice, (U8*)&au8StringBuffer, FALSE);
                }
                else
                {
                    msAPI_CEC_SetDeviceName(enDevice, NULL, TRUE);
                }

                break;
            }
        #endif // #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
        //----- Device OSD Name Transfer end -----------


        //----- Device Menu Control ----------
        #if DEVICE_MENU_CONTROL_SUPPORT
//            case E_MSG_DMC_MENU_REQUEST:
//                break;

            case E_MSG_DMC_MENU_STATUS:
            {
                CEC_DPRINTF("[CEC] E_MSG_DMC_MENU_STATUS(0x%x) \n", opcode);
            #if 1
                /*
                   CEC Table 27 Message dependencies when receiving a message
                   If device does not <Feature Abort> "Unrecognized opcode" with <Menu Request>
                   It shall not <Feature Abort> "Unrecognized opcode" with
                    <User Control Pressed> and <User Control Released>
                */
                gCECUserControlEnable = TRUE;
            #else
                switch(para0)
                {
                    case E_MSG_MENU_ACTIVATED:
                        gCECUserControlEnable = TRUE;
                        // Show OSD message to remind user to press remote control selection the preferred setting.
                        msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Menu Activated", 14);
                        break;
                    case E_MSG_MENU_DEACTIVATED:
                        gCECUserControlEnable = FALSE;
                        // Show OSD message to remind user currently pressing remote control isn't allowed.
                        //MsAPI_CECOSDMessage((header&0xF0)>>4, 12, 5);
                        break;
                }
            #endif
                break;
            }
        #endif
        //----- Device Menu Control end -----------


        //----- Remote Control Passthrough ---
        //----- UI Message -------------------
        #if (DEVICE_MENU_CONTROL_SUPPORT || REMOTE_CONTROL_PASSTHROUGH_SUPPORT)
            case E_MSG_UI_PRESS:
            {
                CEC_DPRINTF("[CEC] E_MSG_UI_PRESS(0x%x) \n", opcode);

                CEC_DPRINTF(" = UI_Press (0x%x) = \n", para0);
                gCECProcessCMDbyKey = TRUE;

                switch(para0)   //UI command
                {

                    case E_MSG_UI_SUB_PICTURE:  //PIP
#if (IR_TYPE_SEL != IR_TYPE_CUS21SH)
                        IR_CODE = IRKEY_PICTURE;
                        g_bIrDetect = TRUE;
#endif
                        break;
                    case E_MSG_UI_LEFT:
                        IR_CODE = IRKEY_LEFT;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_UP:
                        IR_CODE = IRKEY_UP;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_ROOTMENU:
                        IR_CODE = IRKEY_MENU;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_DOWN:
                        IR_CODE = IRKEY_DOWN;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_RIGHT:
                        IR_CODE = IRKEY_RIGHT;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_SELECT:
                        IR_CODE = IRKEY_INPUT_SOURCE;
                        g_bIrDetect = TRUE;
                        break;

                    case E_MSG_UI_POWER:
                    case E_MSG_UI_POWER_ON_FUN:               //Panasonic DVD-S53 think only as power on
                        CEC_DPRINTF("\r\n=E_MSG_UI_POWER= %bd\r\n", MApi_CEC_GetPowerStatus());
                        if(MApi_CEC_GetPowerStatus() == E_MSG_PWRSTA_STANDBY)
                        {
                            IR_CODE = IRKEY_POWER;
                            g_bIrDetect = TRUE;
                            //g_bIRRepeat = 0;
                        }
                        break;

                    case E_MSG_UI_NUMBER_0:
                        IR_CODE = IRKEY_NUM_0;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_1:
                        IR_CODE = IRKEY_NUM_1;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_2:
                        IR_CODE = IRKEY_NUM_2;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_3:
                        IR_CODE = IRKEY_NUM_3;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_4:
                        IR_CODE = IRKEY_NUM_4;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_5:
                        IR_CODE = IRKEY_NUM_5;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_6:
                        IR_CODE = IRKEY_NUM_6;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_7:
                        IR_CODE = IRKEY_NUM_7;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_8:
                        IR_CODE = IRKEY_NUM_8;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_NUMBER_9:
                        IR_CODE = IRKEY_NUM_9;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_DISPLAY_INFO:
                        IR_CODE = IRKEY_INFO;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_MUTE:
                        IR_CODE = IRKEY_MUTE;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_VOLUME_UP:
                        IR_CODE = IRKEY_VOLUME_PLUS;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_VOLUME_DOWN:
                        IR_CODE = IRKEY_VOLUME_MINUS;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_CHANNEL_UP:
                        IR_CODE = IRKEY_CHANNEL_PLUS;
                        g_bIrDetect = TRUE;
                        break;
                    case E_MSG_UI_CHANNEL_DOWN:
                        IR_CODE = IRKEY_CHANNEL_MINUS;
                        g_bIrDetect = TRUE;
                        break;

                    default:    //UI command, no support parameter,need abort a reason, REFUSED reason, or ignore
                        gCECProcessCMDbyKey = FALSE;
                        IR_CODE = IRKEY_DUMY;
                        g_bIrDetect = TRUE;
                        msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, MApi_CEC_GetActiveLogicalAddress(), opcode, E_MSG_AR_REFUSED);
                        break;
                }

                break;
            }

            case E_MSG_UI_RELEASE:
                    break;
        #endif // #if (DEVICE_MENU_CONTROL_SUPPORT || REMOTE_CONTROL_PASSTHROUGH_SUPPORT)
        //----- Remote Control Passthrough end -----------
        //----- UI Message end -----------


        //----- Power Status Support -----
        #if POWER_STATUS_SUPPORT
            case E_MSG_PS_GIVE_POWER_STATUS:
            {
                CEC_DPRINTF("[CEC] E_MSG_PS_GIVE_DEVICE_POWER_STATUS(0x%x) \n", opcode);

                msAPI_CEC_PostMsg_ReportPowerStatus(DIRECTMSG, enDevice, E_MSG_PWRSTA_ON);
                break;
            }

            case E_MSG_PS_REPORT_POWER_STATUS:
            {
                CEC_DPRINTF("[CEC] E_MSG_PS_REPORT_POWER_STATUS(0x%x) \n", opcode);
                CEC_DPRINTF("enDevice 0x%x, ", enDevice);
                CEC_DPUTSTR("POWER_STATUS:");

                if (para0 == E_MSG_PWRSTA_ON)
                {
                    CEC_DPUTSTR(" ON \n");
                    msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Power On", 8);
                    MApi_CEC_SetActivePowerStatus(E_MSG_PWRSTA_ON);
                }
                else if(para0 == E_MSG_PWRSTA_STANDBY)
                {
                    CEC_DPUTSTR(" STANDBY \n");
                    msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Standby", 7);
                }
                else if (para0 == E_MSG_PWRSTA_STANDBY2ON)
                {
                    CEC_DPUTSTR(" STANDBY2ON \n");
                    msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Standby2On", 10);
                    MApi_CEC_SetActivePowerStatus(E_MSG_PWRSTA_STANDBY2ON);
                }
                else if (para0 == E_MSG_PWRSTA_ON2STANDBY)
                {
                    CEC_DPUTSTR(" ON2STANDBY \n");
                    msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"On2Standby", 10);
                    MApi_CEC_SetActivePowerStatus(E_MSG_PWRSTA_ON2STANDBY);
                }

                if(gCECQueryPowerFlag)
                {
                    IR_CODE = IRKEY_POWER;
                    g_bIrDetect = TRUE;
                    //g_bIRRepeat = 0;
                }
                break;
            }
        #endif // #if POWER_STATUS_SUPPORT
        //----- Power Status Support end ---------


        //----- System Audio Control ---------
        #if SYSTEM_AUDIO_CONTROL_SUPPORT
            case E_MSG_SAC_GIVE_AUDIO_STATUS:
            case E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS:
                break;

            case E_MSG_SAC_REPORT_AUDIO_STATUS:
            {
                MS_U8 u8AudioMute;
                MS_U8 u8AudioVolumeLevel;

                CEC_DPRINTF("[CEC] E_MSG_SAC_REPORT_AUDIO_STATUS(0x%x) \n", opcode);

                u8AudioMute        = para0 & 0x80;
                u8AudioVolumeLevel = para0 & 0x7F;
                CEC_DPRINTF(" Aduio Mute %s,", (u8AudioMute)?("On"):("Off"));
                CEC_DPRINTF(" Volume level: %d% \n", u8AudioVolumeLevel);
                ARCAudioVolume = u8AudioVolumeLevel;
                ARCAMPIsMute = (u8AudioMute)?TRUE:FALSE;
                printf("\n ARCAudioVolume :%d   [%s,%s,%d] \n",ARCAudioVolume,__FUNCTION__,__FILE__,__LINE__);

              #if 0
                if ( u8AudioMute != 0 ) // TV:
                {
                    stGenSetting.g_SysSetting.g_bHdmiCecSpeakerMode = ENABLE;
                    //g_bCecAudioSysEnable = FALSE;
                    if(msAPI_AUD_IsAudioMutedByUser()==TRUE)
                    {
                        //MApp_Aud_EnableMute(DISABLE);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }
                else    //Speaker=Amp
                {
                    ARC_CTRL_ON();
                    stGenSetting.g_SysSetting.g_bHdmiCecSpeakerMode = DISABLE;
                    //g_bCecAudioSysEnable = TRUE;
                    if(msAPI_AUD_IsAudioMutedByUser()==FALSE)
                    {
                        //MApp_Aud_EnableMute(ENABLE);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }
              #else
                CEC_DPUTSTR(" TO DO ... \n");
              #endif

                break;
            }

            case E_MSG_SAC_SET_SYSTEM_AUDIO_MODE:
            {
                BOOLEAN bAudioMode;

                CEC_DPRINTF("[CEC] E_MSG_SAC_SET_SYSTEM_AUDIO_MODE(0x%x) \n", opcode);

                bAudioMode = (para0 & 0x01);
                CEC_DPRINTF(" Sys. Aduio Status: %s \n", (bAudioMode)?("On"):("Off"));

              #if 0
                if (bAudioMode)//Amp
                {
                    stGenSetting.g_SysSetting.g_bHdmiCecSpeakerMode = DISABLE;
                    //g_bCecAudioSysEnable = TRUE;
                    if(msAPI_AUD_IsAudioMutedByUser()==FALSE)
                    {
                        //MApp_Aud_EnableMute(ENABLE);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }
                else//TV
                {
                    stGenSetting.g_SysSetting.g_bHdmiCecSpeakerMode = ENABLE;
                    //g_bCecAudioSysEnable = FALSE;
                    if(msAPI_AUD_IsAudioMutedByUser()==TRUE)
                    {
                        //MApp_Aud_EnableMute(DISABLE);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }

                msAPI_CEC_PostMsg_GiveAudioStatus(E_LA_AUDIO_SYS);
              #else
                CEC_DPUTSTR(" TO DO ... \n");
              #endif

                break;
            }

          #if 0 // not supported yet.
            case E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST:
            {
                CEC_DPRINTF("[CEC] E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST(0x%x) \n", opcode);
                break;
            }
          #endif

            case E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS:
            {
                BOOLEAN bAudioMode;

                CEC_DPRINTF("[CEC] E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS(0x%x) \n", opcode);

                bAudioMode = (para0 & 0x01);
                CEC_DPRINTF(" Sys. Aduio Status: %s \n", (bAudioMode)?("On"):("Off"));

              #if 0
                if (bAudioMode)   //Amp
                {
                    stGenSetting.g_SysSetting.g_bHdmiCecSpeakerMode = DISABLE;
                    //g_bCecAudioSysEnable = TRUE;
                    if(msAPI_AUD_IsAudioMutedByUser()==FALSE)
                    {
                        //MApp_Aud_EnableMute(ENABLE);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }
                else//TV
                {
                    stGenSetting.g_SysSetting.g_bHdmiCecSpeakerMode = ENABLE;
                    //g_bCecAudioSysEnable = FALSE;
                    if(msAPI_AUD_IsAudioMutedByUser()==TRUE)
                    {
                        //MApp_Aud_EnableMute(DISABLE);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }
              #else
                CEC_DPUTSTR(" TO DO ... \n");
              #endif

                break;
            }

          #if 0 // not supported yet.
            case E_MSG_SAC_SET_AUDIO_RATE:
            {
                CEC_DPRINTF("[CEC] E_MSG_SAC_SET_AUDIO_RATE(0x%x) \n", opcode);
                break;
            }
          #endif
        #endif // #if SYSTEM_AUDIO_CONTROL_SUPPORT
        //----- System Audio Control end ---------


        //----- Audio Return Channel Support ---------
        #if AUDIO_RETURN_CHANNEL_SUPPORT
            case E_MSG_ARC_INITIATE_ARC:
            {
                CEC_DPRINTF("[CEC] E_MSG_ARC_INITIATE_ARC(0x%x) \n", opcode);

                if (DB_HDMI_SETTING.g_enHDMIARC == DISABLE)
                    break;

                if(gCECAmpARCOffOnStatusCheck == TRUE)
                {
                	//printf(" \n not report ARC Initiated [%s,%d,%s] \n",__FUNCTION__,__LINE__,__FILE__);
            		gCECAmpARCOffOnStatusCheck = FALSE;
                	gIsCECAmpARCOn = TRUE;
					#if 0
                    MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, TRUE, TRUE);
                    MUTE_On();
                    #endif
            		break;
                }

                //Power on ARC
                //ARC_CTRL_ON();
                //printf(" \n  report ARC Initiated [%s,%d,%s] \n",__FUNCTION__,__LINE__,__FILE__);

               // gCECAmpIsNotExit = FALSE;
                MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, TRUE, TRUE);

                //MUTE_On();
                MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);

                msAPI_CEC_PostMsg_ReportARCInitiated(DIRECTMSG, enDevice);

                break;
            }

            case E_MSG_ARC_TERMINATED_ARC:
            {
                CEC_DPRINTF("[CEC] E_MSG_ARC_TERMINATED_ARC(0x%x) \n", opcode);

                //if (DB_HDMI_SETTING.g_enHDMIARC == DISABLE)
                    //break;

                //Power off ARC
                //ARC_CTRL_OFF();
                CEC_DPRINTF("\r\n [E_MSG_ARC_TERMINATED_ARC]Address() = %bx\r\n", (U16)MApi_CEC_GetActiveLogicalAddress());
                MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);
                //MUTE_Off();
                MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
                if (DB_HDMI_SETTING.g_enHDMIARC == ENABLE)
                {
            DB_HDMI_SETTING.g_enHDMIARC =DISABLE;
                }

                msAPI_CEC_PostMsg_ReportARCTerminated(DIRECTMSG, enDevice);

                break;
            }
        #endif // #if AUDIO_RETURN_CHANNEL_SUPPORT
        //----- Audio Return Channel Support end ---------


        //----- General Protocal Message -----
        #if GENERAL_PROTOCAL_SUPPORT
            //----- Feature Abort ----------------
            case E_MSG_FEATURE_ABORT:     //[DA],
            {
                CEC_DPRINTF("[CEC] E_MSG_FEATURE_ABORT(0x%x) \n", opcode);

                // show OSD to describe which commands is unsupport
                msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"Feautre About", 13);

                msAPI_CEC_HandleFeatureAbort(enDevice, enDeviceDst, para0, para1);
                break;
            }

            //----- Abort Message ----------------
            case E_MSG_ABORT_MESSAGE: //same as default, for testing
            {
                CEC_DPRINTF("[CEC] E_MSG_ABORT_MESSAGE(0x%x) \n", opcode);
                msAPI_CEC_OSDMessage((header&0xF0)>>4, (U8*)"About", 5);

              #if 0 // no need, should be updated in CEC library
                /*
                CEC compliance test 9.7-1: waits for at least 5 bit periods
                                           before transmitting a new message.
                5 bit periods are about 12.0ms.
                */
                MsOS_DelayTask(5);
              #endif

                msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, enDevice, opcode, E_MSG_AR_REFUSED);
                break;
            }
        #endif // #if GENERAL_PROTOCAL_SUPPORT
        //----- General Protocal Message end -----

            default:    //not support opcode
            {
                CEC_DPRINTF("[CEC] Not Support opCode(0x%x) \n", opcode);

            #if (DEVICE_OSD_NAME_TRANSFER_SUPPORT==0)
                //Fixed 9.5-1 Fail SYSTEM: The DUT shall not respond with <Feature Abort>.
                if(opcode == E_MSG_OSDNT_SET_OSD_NAME || opcode == E_MSG_OSDNT_GIVE_OSD_NAME)
                {
                    break;
                }
            #endif

                msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, enDevice, opcode, E_MSG_AR_UNRECOGNIZE_OPCDE);

                break;
            }
        }//switch end

      #if CEC_STATE_MACHINE
        CEC_State_header= header;
        CEC_State_opcode= opcode;
      #endif
    }

    gCECProcessCMDKeycode = IR_CODE;

    u8Fifoidx = MApi_CEC_GetFifoIdx();

    if((u8Fifoidx+1)>=CEC_FIFO_CNT)
        MApi_CEC_SetFifoIdx(0);
    else
        MApi_CEC_SetFifoIdx(u8Fifoidx+1);

    MApi_CEC_SetMsgCnt(MApi_CEC_GetMsgCnt() - 1);

    CEC_DPUTSTR(" ---------- \n\n");
}

void msAPI_CEC_ProcessTxMsg(void)
{
    static CECMSG _stCecMsg;
    static U32 _u32CecTxWaitTimer = 0;
    static BOOLEAN _bCecTxChkStatus = FALSE;

  #if 0 // don't know what this is
    if (_bCecTxChkStatus)
    {
        if (  (MApi_CEC_GetTxStatus() == 0)
           && (msAPI_Timer_DiffTimeFromNow(_u32CecTxWaitTimer) < MONITOR_CEC_TX_WAIT_TIMER)
           )
        {
            //APICEC_DPRINTF(printf("Tx not complete\n"));
            return;
        }
        //APICEC_DPRINTF(printf("Tx complete! Status =%bu \n",msAPI_CEC_TxStatus()));

        _bCecTxChkStatus=FALSE;

        if ( _stCecMsg.enOpcode == E_MSG_UI_PRESS && (MApi_CEC_GetTxStatus() & E_CEC_TX_SUCCESS) )
        {
            msAPI_CEC_PostMsgToQueue(_stCecMsg.enDevice, E_MSG_UI_RELEASE, 0, 0);
        }
        else if ( MApi_CEC_GetTxStatus() & E_CEC_TX_SUCCESS )
        {
            msAPI_CEC_AddDevice((MsCEC_DEVICELA)_stCecMsg.enDevice);
        }
    }
  #endif

    // msAPI_CEC_AMPHanlder();

    if(msAPI_CEC_GetMsgInQueue(&_stCecMsg))
    {
        CEC_ERROR_CODE res;

        res = msAPI_CEC_PostMsg((_stCecMsg.enDevice), _stCecMsg.enOpcode, _stCecMsg.au8Operand, _stCecMsg.u8Len);

        _u32CecTxWaitTimer = msAPI_Timer_GetTime0();
        _bCecTxChkStatus=TRUE;

      #if 0 // can't just add/remove device, will cause some CEC compliance test fail.
        if((res & E_CEC_TX_SUCCESS) == 0)
            msAPI_CEC_RemoveDevice((MsCEC_DEVICELA)_stCecMsg.enDevice);
      #endif
    }
    else
    {
        msAPI_CEC_PollingDevice();
    }
}

void msAPI_CEC_InitVariable(void)
{
    MS_U8 i;

    gCECKeyENABLE = TRUE;
    gCECRecordEnable = FALSE;
    gCECProcessCMDbyKey = FALSE;
    gCECProcessCMDKeycode = 0xFF;
    gCECUserControlEnable = FALSE;
    gCECQueryPowerFlag = FALSE;

    for(i=E_LA_TV; i<E_LA_UNREGISTERED; i++)
    {
        _au8CecDeviceIdx[i] = 0xFF;
        _au16CecDeviceIdx_PhyAddr[i] = 0;
        _stCecApiInfo.CecDevicesExisted[i] = FALSE;
        strncpy((char *)_au8CecDeviceName[i], (char *)gStrCECDeviceType[i], strlen((char *)gStrCECDeviceType[i]));
    }

    if ( DB_HDMI_SETTING.g_bHdmiCecDeviceControl == ENABLE
      || stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp
       )
    {
        gCECUserControlEnable = TRUE;
    }
    else
    {
        gCECUserControlEnable = FALSE;
    }
}

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------


//**************************************************************************
//  [Function Name]:
//                   MsAPI_CecInit()
//  [Description]
//                  CEC initial sequence
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_Init(void)
{
    MS_CEC_INIT_INFO stCECInfo;

    stCECInfo.u32XTAL_CLK_Hz = MST_XTAL_CLOCK_HZ;
    MApi_CEC_Init(&stCECInfo);

    msAPI_CEC_InitVariable();

    msAPI_CEC_EmptyMsgQueue();

    MApp_Aud_SetTVSpeaker();    //CEC 13.15.2, Amplifier comes out of standby if receive <System Audio Mode Request>[PA]

    _u32CecDeviceMonitorTimer = msAPI_Timer_GetTime0();

    gCECInitDone = TRUE;
}

//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_ARC_GetARCAudioVolume()
//  [Description]
//                  Get ARC AudioVolume
//  [Arguments]:
//
//  [Return]:
//               MS_U8
//**************************************************************************

MS_U8 msAPI_CEC_ARC_GetARCAudioVolume(void)  //anvi22
{
    return ARCAudioVolume;
}


//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_ARC_GetAmpMute()
//  [Description]
//                  Get ARC Amp mute status
//  [Arguments]:
//
//  [Return]:
//               BOOLEAN
//**************************************************************************

BOOLEAN msAPI_CEC_ARC_GetAmpMute(void)  //anvi22
{
    return ARCAMPIsMute;
}

//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_ARC_SetAmpMute()
//  [Description]
//                   Set ARC Amp mute status
//  [Arguments]:
//
//  [Return]:
//               void
//**************************************************************************

void  msAPI_CEC_ARC_SetAmpMute(BOOLEAN isMute)  //anvi22
{
    ARCAMPIsMute = isMute;
}


//**************************************************************************
//  [Function Name]:
//                   msApp_CEC_ARC_Handler()
//  [Description]
//                  CEC ARC connect judge and show menu info
//  [Arguments]:
//
//  [Return]:
//               bool
//**************************************************************************

BOOLEAN msAPI_CEC_ARC_Is_Connect(void)  //anvi22
{
    BOOLEAN ret =FALSE;
    if(msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS)== TRUE
            && DB_HDMI_SETTING.g_enHDMIARC == TRUE
            && gIsCECAmpARCOn == TRUE)
        {
        ret = TRUE;
        }
        return ret;
}


//**************************************************************************
//  [Function Name]:
//                   msApp_CEC_ARC_Handler()
//  [Description]
//                  CEC ARC connect judge and show menu info
//  [Arguments]:
//
//  [Return]:
//               bool
//**************************************************************************

BOOLEAN msApp_CEC_ARC_Handler(void)
{
    static BOOLEAN ARCConnectMenuIsShow =FALSE;
    static BOOLEAN ARCDisconnectMenuIsShow =FALSE;
    BOOLEAN ret = FALSE;

    if (DB_HDMI_SETTING.g_bHdmiCecMode == ENABLE)
    {
        if ( (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS)== TRUE)
           &&(DB_HDMI_SETTING.g_enHDMIARC == TRUE)
           &&(gIsCECAmpARCOn == TRUE) )
        {
            MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, TRUE, TRUE);

            //MUTE_On();
            MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);

            if(ARCConnectMenuIsShow == FALSE)
            {
                MApp_UiMenu_ARCDeviceStatusWin_Show(TRUE);
                ARCConnectMenuIsShow = TRUE;
                ARCDisconnectMenuIsShow = FALSE;
            }
        }
        else
        {
            //printf("\n 5555   [%s,%s,%d] \n",__FUNCTION__,__FILE__,__LINE__);

            MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);

            //MUTE_Off();
            MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);

            if(ARCDisconnectMenuIsShow == FALSE && ARCConnectMenuIsShow ==TRUE)
            {
                if ( (DB_HDMI_SETTING.g_enHDMIARC == TRUE)
                   &&(msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS)== FALSE) )
                {
                    MApp_UiMenu_ARCDeviceStatusWin_Show(FALSE);
                    ARCConnectMenuIsShow = FALSE;
                    ARCDisconnectMenuIsShow = TRUE;
                }
            }
        }
        ret = TRUE;
    }
    else
    {
        ret =FALSE;
    }
    return ret;
}

static void EmptyMsgFifo(void)
{
    MS_U8 u8Fifoidx;

    if (MApi_CEC_GetMsgCnt() == 0 ) return;  //no received message to process

    u8Fifoidx = MApi_CEC_GetFifoIdx();

    if ( (u8Fifoidx+1) >= CEC_FIFO_CNT )
        MApi_CEC_SetFifoIdx(0);
    else
        MApi_CEC_SetFifoIdx(u8Fifoidx+1);

    MApi_CEC_SetMsgCnt(MApi_CEC_GetMsgCnt() - 1);
}

void msAPI_CEC_EmptyAllMsgFifo(void)
{
    while ( MApi_CEC_GetMsgCnt() != 0 )
    {
        //printf("\n\e[31;1m msAPI_CEC_EmptyAllMsgFifo \33[m \n");
        EmptyMsgFifo();
    }
}


//**************************************************************************
//  [Function Name]:
//                   MsAPI_CecCecHandler()
//  [Description]
//                   CEC handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_Handler(void)
{
    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return;
    }

    if (DB_HDMI_SETTING.g_bHdmiCecMode == DISABLE)
    {
        msAPI_CEC_EmptyAllMsgFifo();

        //printf("CEC function OFF!\n");
        return;
    }
  #if 0
    else
    {
        msApp_CEC_ARC_Handler();
    }
  #endif

    msAPI_CEC_ProcessTxMsg();

#if(!ENABLE_CEC_INT) // if not enable CEC interrupt, use sw polling to instead of
    MApi_CEC_ChkRxBuf();
#endif

    msAPI_CEC_ProcessCmd();

#if CEC_STATE_MACHINE
    MApp_CecStateMachine();
#endif
}

//**************************************************************************
//  [Function Name]:
//                  MsAPI_GetCECOSDString()
//  [Description]
//                  Get CEC OSD string
//  [Arguments]:
//                  string point to retrieve display string buffer
//
//  [Return]:
//                  string length
//
//**************************************************************************
U8 msAPI_CEC_GetOSDString(U8 *pstr)
{
    *pstr = gCECOSDStr[1];

    return(gCECOSDStr[0]);
}


//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_SendCECKeyFromTVtoDev()
//  [Description]
//                   CEC key process
//  [Arguments]:
//                   keycode: irda key code
//  [Return]:
//                   return CEC key parse is enable or not
BOOLEAN msAPI_CEC_SendCECKeyFromTVtoDev(U8 keycode)
{
    BOOLEAN user_ctrl_flag = FALSE;
    MsCEC_DEVICELA enActiveDevice = E_LA_UNREGISTERED;

    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return FALSE;
    }

    if (DB_HDMI_SETTING.g_bHdmiCecMode!= ENABLE)
    {
        return FALSE;
    }

    if(!gCECKeyENABLE) return FALSE;

    CEC_DPRINTF("\r\n CEC Irda Key(0x%bx) \n", keycode);
    if((keycode == KEY_POWER) && !(gCECProcessCMDbyKey && (gCECProcessCMDKeycode == keycode))) // Keypad_POWER
    {
    #if ENABLE_CUST01_CEC//power off tv and DVD
        {
            if ( !MApp_UiMenu_IsCountDownWinShow() )//don't power off DVD when countdown win showing
            {
	            if (DB_HDMI_SETTING.g_bHdmiCecDeviceAutoStandby == ENABLE)
	            {
	                msAPI_CEC_PostMsg_Standby(DIRECTMSG);
	            }
	            else
	            {
	                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, TRUE, MApi_CEC_GetActiveLogicalAddress(), E_MSG_UI_STOP); //Stop current device
	            }

            }

            MsOS_DelayTask(100);
        }
    #else //Don't process DVD power while DVD is standby
        if(!gCECQueryPowerFlag)
        {
            CEC_DPUTSTR("*CEC*:Msg Req PowerSts\n");
            gCECQueryPowerFlag = TRUE;
            msAPI_CEC_PostMsg_GiveDevicePowerStatus(DIRECTMSG, MApi_CEC_GetActiveLogicalAddress());
            u8KeyCode = KEY_NULL;
            return TRUE;
        }

        if ( (MApi_CEC_GetActivePowerStatus() ==  E_MSG_PWRSTA_ON)
          || (MApi_CEC_GetActivePowerStatus() ==  E_MSG_PWRSTA_STANDBY2ON) )
        {
            CEC_DPUTSTR("*CEC*:PowerSts->E_MSG_PWRSTA_ON||E_MSG_PWRSTA_STANDBY2ON\n");
            gCECQueryPowerFlag = FALSE;

            if (DB_HDMI_SETTING.g_bHdmiCecDeviceAutoStandby == ENABLE)
            {
                    printf("\n sophia 3 [%s,%d,%s] \n",__FUNCTION__,__LINE__,__FILE__);


                msAPI_CEC_PostMsg_Standby(DIRECTMSG);
            }
            else
            {
                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, TRUE, MApi_CEC_GetActiveLogicalAddress(), E_MSG_UI_STOP); //Stop current device
            }

            MsOS_DelayTask(100);

            msAPI_CEC_PostMsg_GiveDevicePowerStatus(DIRECTMSG, MApi_CEC_GetActiveLogicalAddress());
        }
        else if((MApi_CEC_GetActivePowerStatus() ==  E_MSG_PWRSTA_STANDBY) || (MApi_CEC_GetActivePowerStatus() ==  E_MSG_PWRSTA_ON2STANDBY))
        {
            CEC_DPUTSTR("*CEC*:PowerSts->E_MSG_PWRSTA_STANDBY||E_MSG_PWRSTA_ON2STANDBY\n");
            gCECQueryPowerFlag = FALSE;

          #if !ENABLE_CUST01_CEC //Don't process DVD power while DVD is standby
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, MApi_CEC_GetActiveLogicalAddress(), E_MSG_UI_POWER);          //useful for DVD-S53, DMR-Ex150, power on
            MsOS_DelayTask(100);
            msAPI_CEC_PostMsg_GiveDevicePowerStatus(DIRECTMSG, MApi_CEC_GetActiveLogicalAddress());
          #endif
        }
    #endif

        //if(gCECKeyENABLE) // just turn off CEC device and TV
            return FALSE;
    }

#if !ENABLE_CUST01_CEC
    if(keycode == KEY_CLOCK) // CEC link
    {
        gCECKeyENABLE = ~gCECKeyENABLE;
        if(gCECKeyENABLE)
        {
            CEC_DPUTSTR("\r\n CEC Key Activated \r\n");
            // show OSD to describe whether CEC is activated or not
            msAPI_CEC_OSDMessage(MApi_CEC_GetActiveLogicalAddress(), (U8*)"CEC Activated", 13);
        }
        else
        {
            CEC_DPUTSTR("\r\n CEC Key Deactivated \r\n");
            // show OSD to describe whether CEC is activated or not
            msAPI_CEC_OSDMessage(MApi_CEC_GetActiveLogicalAddress(), (U8*)"CEC Deactivated", 15);
        }

    }
#endif

    if(!gCECKeyENABLE || (gCECProcessCMDbyKey && (gCECProcessCMDKeycode == keycode)))
    {
        gCECProcessCMDbyKey = FALSE;
        gCECProcessCMDKeycode = 0xFF;

        CEC_DPUTSTR(" CEC Key return 1 \n");
        return FALSE;
    }

#if ENABLE_CUST01_CEC
    if(!msAPI_CEC_IsCECKey(keycode))
    {
        CEC_DPRINTF(" CEC Key return 2 (0x%x) \n", keycode);
        return FALSE;
    }
#endif

    enActiveDevice = MApi_CEC_GetActiveLogicalAddress();
    CEC_DPRINTF(" Active Logical Address = 0x%x \n", enActiveDevice);

    switch(keycode )
    {
/*        case KEY_0:      //IRKEY_0
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_0);
            break;
        case KEY_1:      //IRKEY_1
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_1);
            break;
        case KEY_2:      //IRKEY_2
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_2);
            break;
        case KEY_3:      //IRKEY_3
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_3);
            break;
        case KEY_4:      //IRKEY_4
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_4);
            break;
        case KEY_5:      //IRKEY_5
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_5);
            break;
        case KEY_6:      //IRKEY_6
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_6);
            break;
        case KEY_7:      //IRKEY_7
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_7);
            break;
        case KEY_8:      //IRKEY_8
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_8);
            break;
        case KEY_9:      //IRKEY_9
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(gCECUserControlEnable, enActiveDevice, E_MSG_UI_NUMBER_9);
            break;
*/
        case KEY_UP: // Keypad_UP
            if(_eActiveOSD == E_OSD_MAIN_MENU ||
               _eActiveOSD == E_OSD_FACTORY_MENU||
               _eActiveOSD == E_OSD_INPUT_SOURCE||
               _eActiveOSD == E_OSD_MESSAGE_BOX)
            {
                return FALSE;
            }

            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_UP);
            break;
        case KEY_DOWN: // Keypad_DOWN
            if(_eActiveOSD == E_OSD_MAIN_MENU ||
               _eActiveOSD == E_OSD_FACTORY_MENU||
               _eActiveOSD == E_OSD_INPUT_SOURCE||
               _eActiveOSD == E_OSD_MESSAGE_BOX)
            {
                return FALSE;
            }

            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_DOWN);
            break;
        case KEY_LEFT: // Keypad_LEFT
            if(_eActiveOSD == E_OSD_MAIN_MENU ||
               _eActiveOSD == E_OSD_FACTORY_MENU||
               _eActiveOSD == E_OSD_INPUT_SOURCE||
               _eActiveOSD == E_OSD_MESSAGE_BOX)
            {
                return FALSE;
            }

            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_LEFT);
            break;
        case KEY_RIGHT: // Keypad_RIGHT
            if(_eActiveOSD == E_OSD_MAIN_MENU ||
               _eActiveOSD == E_OSD_FACTORY_MENU||
               _eActiveOSD == E_OSD_INPUT_SOURCE||
               _eActiveOSD == E_OSD_MESSAGE_BOX)
            {
                return FALSE;
            }

            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_RIGHT);
            break;

        case KEY_SELECT: // keypad_Enter
            if(_eActiveOSD == E_OSD_MAIN_MENU ||
               _eActiveOSD == E_OSD_FACTORY_MENU||
               _eActiveOSD == E_OSD_INPUT_SOURCE||
               _eActiveOSD == E_OSD_MESSAGE_BOX)
            {
                return FALSE;
            }

            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_SELECT);
            break;

 /*       case KEY_INPUT_SOURCE: // Keypad_SOURCE
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_SELECT);
            break;

        case KEY_MENU: // Keypad_MENU
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_ROOTMENU);
            break;

        case KEY_FREEZE: // setup menu
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_SETUP_MENU);
            break;

        case KEY_PICTURE: // Keypad_PIP
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_SUB_PICTURE);
            break;
*/
    #if 0
        case KEY_POWER: // Keypad_POWER
//                MsAPI_CecMsg_UserCtrlPressed(enActiveDevice, E_MSG_UI_POWER);  //no useful for DMR-EX150
//get power status,and decide
//if power on, then standby
//printf("\r\nKeypad_POWER=%x",ActivePowerStatus);
            if((MApi_CEC_GetActivePowerStatus() ==  E_MSG_PWRSTA_ON) || (MApi_CEC_GetActivePowerStatus() ==  E_MSG_PWRSTA_STANDBY2ON))
            {
                MsAPI_CecMsg_Standby(enActiveDevice);
                MApi_CEC_SetActivePowerStatus(E_MSG_PWRSTA_STANDBY);     //suppose that
                //Delay1ms(1000);                                 //template adding
                //msHDMICecSendMessage0Para(0, GIVE_POWER_STATUS);
            }
            else if((MApi_CEC_GetActivePowerStatus() ==  E_MSG_PWRSTA_STANDBY) || (MApi_CEC_GetActivePowerStatus() ==  E_MSG_PWRSTA_ON2STANDBY))
            {
                //MsAPI_CecMsg_UserCtrlPressed(enActiveDevice, E_MSG_UI_POWER_ON_FUN);   //useful for DVD-S53, power on
                MsAPI_CecMsg_UserCtrlPressed(enActiveDevice, E_MSG_UI_POWER);          //useful for DVD-S53, DMR-Ex150, power on
                MApi_CEC_SetActivePowerStatus(E_MSG_PWRSTA_ON);          //suppose that
                //Delay1ms(1000);                                 //template adding
                //msHDMICecSendMessage0Para(0, GIVE_POWER_STATUS);
            }
//if standby, then power command
            return FALSE;
            break;
    #endif

        case KEY_PLAY: // Keypad_Play
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_PLAY);
            break;

        case KEY_PAUSE:
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_PAUSE);
            break;

        case KEY_STOP: // Keypad_Stop
            if(gCECRecordEnable) // record on
            {
                gCECRecordEnable = FALSE;
                msAPI_CEC_PostMsg_RecordOff(DIRECTMSG, enActiveDevice);
            }
            else
            {
                user_ctrl_flag = TRUE;
                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_STOP);
            }
            break;

        case KEY_EPG: // Keypad_Open , disk Eject
            msAPI_CEC_PostMsg_DeckCtrl(DIRECTMSG, enActiveDevice, E_MSG_DCM_CMD_EJECT);
            break;

        case KEY_EXIT: // Keypad_Exit
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enActiveDevice, E_MSG_UI_EXIT);
            break;

        case KEY_RECORD:
            gCECRecordEnable = TRUE;
            MsAPI_CEC_Msg_RecordOn(enActiveDevice, E_MSG_RECORD_TYPE_OWN_SOURCE);
            break;

        case KEY_INFO:  // check CEC version
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_GetCECVersion(DIRECTMSG, enActiveDevice);
            break;

        case KEY_MUTE:      //IRKEY_MUTE
            if(msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS)== TRUE
                            && DB_HDMI_SETTING.g_enHDMIARC == TRUE
                            && gIsCECAmpARCOn == TRUE)
            {
                user_ctrl_flag = FALSE;
                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, TRUE, E_LA_AUDIO_SYS, E_MSG_UI_MUTE);
                MApp_ARC_KeyProc_Mute();
                //msAPI_CEC_PostMsg_GiveAudioStatus(POSTMSG,E_LA_AUDIO_SYS);

            }
            else
            {
                CEC_MSG(printf("\n TV MUTE MENU\n"));
                MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);
                //MUTE_Off();
                MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
                return FALSE;
            }
            break;

        case KEY_VOLUME_PLUS:      //IRKEY_VOL_UP
            if(msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS)==TRUE
                                && DB_HDMI_SETTING.g_enHDMIARC==TRUE
                                && gIsCECAmpARCOn == TRUE)
            {

                user_ctrl_flag = FALSE;
                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, TRUE, E_LA_AUDIO_SYS, E_MSG_UI_VOLUME_UP);

                return FALSE;
            }
            else
            {
                CEC_MSG(printf("\n TV VOLUME PLUS MENU\n"));
                MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);
                //MUTE_Off();
                MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);

                return FALSE;
            }
            break;

        case KEY_VOLUME_MINUS:      //IRKEY_VOL_DOWM
            if(msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS)== TRUE
                            && DB_HDMI_SETTING.g_enHDMIARC == TRUE
                            && gIsCECAmpARCOn == TRUE)
            {

                user_ctrl_flag = FALSE;
                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, TRUE, E_LA_AUDIO_SYS, E_MSG_UI_VOLUME_DOWN);
                return FALSE;

                //msAPI_CEC_PostMsg_GiveAudioStatus(POSTMSG,E_LA_AUDIO_SYS);

            }
            else
            {
                CEC_MSG(printf("\n TV VOLUME MINUS MENU\n"));
                MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);
                //MUTE_Off();
                MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
                return FALSE;
            }
            break;

        /*
        case KEY_CHANNEL_PLUS:      //IRKEY_CH_UP
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_CHANNEL_UP);
            break;
        case KEY_CHANNEL_MINUS:      //IRKEY_CH_DOWM
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_CHANNEL_DOWN);
            break;
        */

        case KEY_BLUE:  // Blue
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_F1_BLUE);
            break;
        case KEY_RED:  // Red
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_F2_RED);
            break;
        case KEY_GREEN:  // Green
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_F3_GREEN);
            break;
        case KEY_YELLOW:  // Yellow
            user_ctrl_flag = TRUE;
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_F4_YELLOW);
            break;

        /*
        case KEY_CHANNEL_LIST:  // List the existed CEC devices
            MApi_CEC_CheckExistDevices();
            // OSD information
            break;
        */

       case KEY_FF:
           user_ctrl_flag = TRUE;
           msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_FAST_FORWARD);
           break;
       case KEY_REWIND:
           user_ctrl_flag = TRUE;
           msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_REWIND);
           break;
       case KEY_NEXT:
           user_ctrl_flag = TRUE;
           msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_FORWARD);
           break;
       case KEY_PREVIOUS:
           user_ctrl_flag = TRUE;
           msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable, enActiveDevice, E_MSG_UI_BACKWARD);
           break;

        default:
            return FALSE;
    }

    if (user_ctrl_flag && !gCECUserControlEnable) // if menu status is deactived, remote control key should handle locally, not send CEC message out
        return FALSE;
    else
    {
        u8KeyCode = KEY_NULL;
        return TRUE;
    }
}


//**************************************************************************
//  [Function Name]:
//                   MsAPI_CecUIEnable()
//  [Description]
//                   Enable CEC For UI Function
//  [Arguments]:
//                   keycode: irda key code
//  [Return]:
//                   none
//@20081007 by hansen.chen
//**************************************************************************
void msAPI_CEC_UIEnable(BOOLEAN bEnable)
{
    gCECKeyENABLE = bEnable;
    if(gCECKeyENABLE)
    {
        CEC_DPUTSTR("\r\n CEC Key Activated \r\n");
        // show OSD to describe whether CEC is activated or not
        //MsAPI_CECOSDMessage(MApi_CEC_GetActiveLogicalAddress(), (U8*)"CEC Activated", 13);
    }
    else
    {
        CEC_DPUTSTR("\r\n CEC Key Deactivated \r\n");
        // show OSD to describe whether CEC is activated or not
        //MsAPI_CECOSDMessage(MApi_CEC_GetActiveLogicalAddress(), (U8*)"CEC Deactivated", 15);
    }
}

void msAPI_CEC_GetDeviceInfo(void)
{
    U8 i= 0, j= 0, k= 0;

    for (i= 0; i< E_LA_UNREGISTERED; i++)
    {
        if(msAPI_CEC_IsDeviceExist((MsCEC_DEVICELA)i))
        {
            for(j=0; j< msAPI_CEC_GetDeviceTotalNum(); j++)
            {
                if (msAPI_CEC_GetDeviceIdx(j) == i)
                {
                    g_stMenuCecDeviceList.aenDeviceLA[k]= (MsCEC_DEVICELA)i;
                    strcpy((char *)g_stMenuCecDeviceList.au8CecDeviceName[k] ,(char *)msAPI_CEC_GetDeviceName((MsCEC_DEVICELA)i));
                    g_stMenuCecDeviceList.u8CECDeviceNum++;
                    g_stMenuCecDeviceList.wPhyAddr[k]= msAPI_CEC_GetDeviceIdx_PhyAddr((MsCEC_DEVICELA)j);

                    k++;
                }
            }
        }

}
}
//**************************************************************************
//  [Function Name]:
//                   MsAPI_CecUIEnable()
//  [Description]
//                   Enable CEC For UI Function
//  [Arguments]:
//                   keycode: irda key code
//  [Return]:
//                   none
//@20081007 by hansen.chen
//**************************************************************************
BOOLEAN msAPI_CEC_IsCECKey(U8 bKey)
{
    switch(bKey)
    {
#if 0  //kate 081205 from hansen
        case KEY_0:
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
#endif //kate 081205 from hansen
        case KEY_PLAY:
        case KEY_PAUSE:
        case KEY_STOP:
        case KEY_FF:
        case KEY_REWIND:
        case KEY_NEXT:
        case KEY_PREVIOUS:
        #if 1
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_SELECT:

        case KEY_VOLUME_MINUS:
        case KEY_VOLUME_PLUS:
        case KEY_MUTE:

            return    TRUE;
        #endif
        default:
            return    FALSE;
            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                   MsAPI_IsCECByPass()
//  [Description]
//                   Bypass CEC Cmd
//  [Arguments]:
//                   none
//  [Return]:
//                   none
//@20090212 by hansen.chen
//**************************************************************************

BOOLEAN bDuringChannelChange = 0;

BOOLEAN msAPI_CEC_IsByPass(void)
{
    if ( (msAPI_Tuner_IsTuningProcessorBusy())
       ||(MApp_ZUI_GetActiveOSD() == E_OSD_AUTO_TUNING)//by pass atuo tunning tv
      #if ENABLE_ATSC
       ||(MApp_TopStateMachine_GetTopState() != STATE_TOP_ATSC_SCAN)
      #endif
       )
        return TRUE;

    #if ENABLE_PVR
    enPVRState PVRState = MApp_PVR_StateMachineGet();
    if((PVRState == E_PVR_STATE_TIMESHIFT) || (PVRState == E_PVR_STATE_RECORD)\
        || (PVRState == E_PVR_STATE_PLAYBACK) || (PVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        return TRUE;
    }
    #endif

    if(bDuringChannelChange)
        return TRUE;

    return FALSE;
}

void  msAPI_CEC_CheckWakeUpPort(void)
{
    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return;
    }

    if (!DB_HDMI_SETTING.g_bHdmiCecMode)
    {
        return;
    }

    if (msAPI_Power_IswakeupsourceCEC())
    {
        printf("Change to CEC wake up source");
        msAPI_CEC_PostMsg_RequestActiveSource(DIRECTMSG);
    }
}


void msAPI_CEC_SetPowerStatusOn2Standby(void)
{
    MApi_CEC_SetActivePowerStatus(E_MSG_PWRSTA_ON2STANDBY);
}


#else

U8 code gCEcdummy; // Add a dummy variable for complier link

#endif // ENABLE_CEC

