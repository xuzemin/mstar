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
/// @file   msAPI_CEC.h
/// @author MStar Semiconductor Inc.
/// @brief  CEC API Interface
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSAPICEC_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif


#if 1//ENABLE_CEC

#include "datatype.h"
#include "apiCEC.h"



#define CEC_STATE_MACHINE                       FALSE//TRUE//FALSE

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define CEC_VALID                               0x00
#define CEC_INVALID                             0xFF

#define CEC_MSG_QUEUE_SIZE                      50

#define CEC_ARC_REQUEST_INITIATION              0
#define CEC_ARC_REQUEST_TERMINATION             1

#define MONITOR_CEC_TX_WAIT_TIMER               300   // wait re-transmission

#define B_MONITOR_CEC_DEVICE_PERIOD             60000   // device polling time
#define B_MONITOR_CEC_AUDIO_SYS_PERIOD         1000//    500   // Audio sys polling time  // anviarc



#define B_CEC_POLLING_START_PING_PERIOD         5000
#define B_CEC_GIVE_PHYSICAL_ADDRESS_PERIOD      5000

#define I_CEC_POLLING_START_PING_PERIOD         0//100
#define I_CEC_GIVE_PHYSICAL_ADDRESS_PERIOD      0//100
#define I_CEC_REPORT_POWER_STATUS_PERIOD        0//100

#define IMMEDIATELY_POLLING                     TRUE//TRUE//FALSE
#define BACKGROUND_POLLING                      TRUE//TRUE//FALSE

typedef enum
{
   STATUS_POLLING_IDLE,

   B_POLLING_START_PING,
   B_POLLING_GIVE_PHYSICAL_ADDRESS,
   B_POLLING_REPORT_POWER_STATUS,

#if IMMEDIATELY_POLLING
   I_POLLING_START_PING,
   I_POLLING_GIVE_PHYSICAL_ADDRESS,
   I_POLLING_REPORT_POWER_STATUS,
#endif

}EN_CEC_POLLING_STATUS;


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
#define MAX_CEC_DEVICE_OSD_NAME 13

typedef struct _ST_MENU_CEC_DEVICE_LIST
{
    U8 u8CECDeviceNum;
    MS_U8 au8CecDeviceName[15][MAX_CEC_DEVICE_OSD_NAME];
    MsCEC_DEVICELA aenDeviceLA[15];
    WORD  wPhyAddr[15];
}ST_MENU_CEC_DEVICE_LIST;

INTERFACE ST_MENU_CEC_DEVICE_LIST g_stMenuCecDeviceList;

typedef struct _CECMSG
{
    MS_U8 u8Handle;
    MsCEC_DEVICELA enDevice;
    MsCEC_MSGLIST enOpcode;
    MS_U8 au8Operand[14];
    MS_U8 u8Len;
} CECMSG;
typedef CECMSG* PCECMSG;

typedef struct _CECMSGQUEUE
{
    CECMSG astCecMsgQ[CEC_MSG_QUEUE_SIZE]; //HAND_INVALID for unused
    MS_U8 u8CecMsgQIdxStart;
    MS_U8 u8CecMsgQIdxEnd;
} CECMSGQUEUE;

typedef enum
{
   POSTMSG,
   DIRECTMSG,
}EN_CEC_SEND_MSG;

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
void msAPI_CEC_GetDeviceInfo(void);
CEC_ERROR_CODE msAPI_CEC_PingDevice(MsCEC_DEVICELA enPingDevice);

void msAPI_CEC_PostMsg_ActiveSource(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pPhysicalAddr);

void msAPI_CEC_PostMsg_InActiveSource(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MS_U8* phy_Add);
void msAPI_CEC_PostMsg_RequestActiveSource(EN_CEC_SEND_MSG enCecSendMsg);
void msAPI_CEC_PostMsg_RoutingChange(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pOrig_Addr, MS_U8* pNew_Addr);
void msAPI_CEC_PostMsg_SetStreamPath(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* new_address);

void msAPI_CEC_PostMsg_Standby(EN_CEC_SEND_MSG enCecSendMsg);

void msAPI_CEC_PostMsg_RecordOff(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);
void msAPI_CEC_PostMsg_RecordOn(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_RECORD_SOURCE_TYPE enCmd);

void msAPI_CEC_PostMsg_CECVersion(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MS_U8 u8Version);
void msAPI_CEC_PostMsg_GetCECVersion(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);

void msAPI_CEC_PostMsg_GivePhysicalAddress(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);
void msAPI_CEC_PostMsg_ReportPhysicalAddress(EN_CEC_SEND_MSG enCecSendMsg);

void msAPI_CEC_PostMsg_SetMenuLang(EN_CEC_SEND_MSG enCecSendMsg, MS_U8* pu8MenuLanguageCode);

void msAPI_CEC_PostMsg_DeckCtrl(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_DC_DECK_CTRL_PARM enCmd);
void msAPI_CEC_PostMsg_DeckStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_DC_DECK_STATUS_PARM enCmd);
void msAPI_CEC_PostMsg_GiveDeckStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_STATUS_REQUEST_PARM enCmd);
void msAPI_CEC_PostMsg_DCPlay(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_DC_PLAY_PARM enCmd);

void msAPI_CEC_PostMsg_DeviceVendorID(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);
void msAPI_CEC_PostMsg_GiveDeviceVendorID(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);

void msAPI_CEC_PostMsg_GiveOSDName(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);

void msAPI_CEC_PostMsg_MenuRequest(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_MENU_REQ_TYPE enCmd);
void msAPI_CEC_PostMsg_MenuStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSG_MENU_STATE enCmd);

void msAPI_CEC_PostMsg_UserCtrlPressed(EN_CEC_SEND_MSG enCecSendMsg, MS_BOOL bUserCtrlEn, MsCEC_DEVICELA enDevice, MsCEC_MSG_USER_CTRL_PARM cmd);
void msAPI_CEC_PostMsg_UserCtrlReleased(EN_CEC_SEND_MSG enCecSendMsg, MS_BOOL bUserCtrlEn, MsCEC_DEVICELA enDevice);

void msAPI_CEC_PostMsg_GiveDevicePowerStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);

void msAPI_CEC_PostMsg_GiveAudioStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);
void msAPI_CEC_PostMsg_GiveSystemAudioModeStatus(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);
void msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(EN_CEC_SEND_MSG enCecSendMsg);
void msAPI_CEC_PostMsg_SystemAudioModeReq(EN_CEC_SEND_MSG enCecSendMsg, MS_U16 u16PhyAddr);

void msAPI_CEC_PostMsg_FeatureAbort(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice, MsCEC_MSGLIST enMsg, MsCEC_MSG_ABORT_REASON enCmd);
void msAPI_CEC_PostMsg_AbortMessage(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);

void msAPI_CEC_PostMsg_ReportARCInitiated(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);
void msAPI_CEC_PostMsg_ReportARCTerminated(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);
void msAPI_CEC_PostMsg_RequestARCInitiation(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);
void msAPI_CEC_PostMsg_RequestARCTermination(EN_CEC_SEND_MSG enCecSendMsg, MsCEC_DEVICELA enDevice);

//-------------------------------------------------------------------------------------------------

BOOLEAN msAPI_CEC_ARC_Is_Connect(void);//anvi22
MS_U8   msAPI_CEC_ARC_GetARCAudioVolume(void); //anvi22
BOOLEAN msAPI_CEC_ARC_GetAmpMute(void) ; //anvi22
void    msAPI_CEC_ARC_SetAmpMute(BOOLEAN isMute);  //anvi22
void    msAPI_CEC_RequestARCAction(U8 action);

//-------------------------------------------------------------------------------------------------

//CEC initial sequence
void msAPI_CEC_Init(void);

//CEC handler
void msAPI_CEC_Handler(void);

//Get CEC OSD string
U8   msAPI_CEC_GetOSDString(U8 *pstr);

BOOLEAN msAPI_CEC_SendCECKeyFromTVtoDev(U8 ircode);

void msAPI_CEC_UIEnable(BOOLEAN bEnable);

MS_U8* msAPI_CEC_GetDeviceName(MS_U8 u8Device);

MS_U8 msAPI_CEC_GetDeviceTotalNum(void);

MsCEC_DEVICELA msAPI_CEC_GetActiveDevice(void);
void msAPI_CEC_SetActiveDevice(MsCEC_DEVICELA enDevice);
void MApp_CEC_SetMyPhyAddr(INPUT_SOURCE_TYPE_t pre_srctype, INPUT_SOURCE_TYPE_t cur_srctype);
U16 msAPI_CEC_GetActivePhyAddr(void);
MS_BOOL msAPI_CEC_IsDeviceExist(MsCEC_DEVICELA enDevice);

void msAPI_CEC_DeviceChange(MsCEC_DEVICELA enChangedDevice);
void msAPI_CEC_RoutingControl_SourceChange(INPUT_SOURCE_TYPE_t pre_srctype, INPUT_SOURCE_TYPE_t cur_srctype);
void  msAPI_CEC_CheckWakeUpPort(void);

void msAPI_CEC_SetSystemAudioMode(BOOLEAN bMode);
BOOLEAN msAPI_CEC_QuerySystemAudioMode(void);

void msAPI_CEC_ForceImmediatelyPolling(BOOLEAN bCecDeviceListPolling);

MS_U16 msAPI_CEC_GetDeviceIdx_PhyAddr(MS_U8 u8Idx);

void msAPI_CEC_EmptyAllMsgFifo(void);

void msAPI_CEC_SetPowerStatusOn2Standby(void);

/*************************************************************************************************/
#endif  //#if ENABLE_CEC
#undef INTERFACE

