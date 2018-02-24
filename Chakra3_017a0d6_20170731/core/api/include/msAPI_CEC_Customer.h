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
/// @file   msAPI_CEC_Customer.h
/// @author MStar Semiconductor Inc.
/// @brief  CEC API Interface for Customization
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MSAPI_CEC_CUSTOMER_H_
#define _MSAPI_CEC_CUSTOMER_H_

#include "Board.h"

#if(ENABLE_CEC)

#include "apiCEC.h"
#include "MApp_GlobalSettingSt.h"


/// CEC interval timer type
typedef enum _EN_CEC_INTERVAL_TIME_TYPE
{
    INTERVAL_CEC_NULL = 0 ,

    /// CEC interval timer type = polling
    INTERVAL_CEC_DeviceRecognition = INTERVAL_CEC_NULL ,

    // for DeviceRecognition <Give Physical Address> and <Report Physical Address>
    INTERVAL_CEC_DeviceRecognition_ReportPhyAddr,

    /// CEC interval timer type = TV detect new devices by <Report Physical Address>
    INTERVAL_CEC_DeviceDetectByReportPhyAddr,

    /// CEC interval timer type = TV detect new devices by <Report Physical Address>
    INTERVAL_CEC_FSM_DeviceDetect,

    /// CEC interval timer type =
    INTERVAL_CEC_FSM_RequestARC,

    /// CEC interval timer type = polling all devices once
    INTERVAL_CEC_Polling_Once,
    INTERVAL_CEC_Normal_Polling,

    /// CEC interval timer type = polling AMP once
    INTERVAL_CEC_Polling_AMP_Once,


    INTERVAL_CEC_FSM_ARC_Off2On,
    INTERVAL_CEC_FSM_ARC_On2Off,

    /// CEC interval timer type = timer max
    INTERVAL_TIMER_MAX,
} EN_CECIntervalTimerType;

/******************************************************************************/

// for supporting Features
typedef struct _ST_CEC_Feature_Support
{
    BOOL bCECFeatureSupport_OneTouchPlay;
    BOOL bCECFeatureSupport_RoutingControl;
    BOOL bCECFeatureSupport_SystemStandby;
    BOOL bCECFeatureSupport_SystemInformation;
    BOOL bCECFeatureSupport_VendorSpecificCommands;
    BOOL bCECFeatureSupport_DeviceOSDNameTransfer;
    BOOL bCECFeatureSupport_DeviceMenuControl;
    BOOL bCECFeatureSupport_RemoteControlPassThrough;
    BOOL bCECFeatureSupport_GiveDevicePowerStatus;
    BOOL bCECFeatureSupport_SystemAudioControl;
    BOOL bCECFeatureSupport_AudioReturnChannelControl;
    BOOL bCECFeatureSupport_GeneralProtocolMessageControl;

    BOOL bCECFeatureSupport_ALL;

} ST_CEC_Feature_Support;

extern ST_CEC_Feature_Support stCecFeatureSupport;
void msAPI_CEC_GetCecFeatureSupport(ST_CEC_Feature_Support *CecFeatureSupport);
void msAPI_CEC_SetCecFeatureSupport(ST_CEC_Feature_Support *CecFeatureSupport);

/******************************************************************************/

#define E_MSG_UI_UNKNOWN    0xFF

/// Define Key and CEC Key Pair Sruct
typedef struct _ST_CEC_IR_KEY_PAIR
{
    /// CEC Key code
    MS_U8           CECKey;     // MsCEC_MSG_USER_CTRL_PARM

    /// Key code
    MS_U8           keycode;    // EN_KEY
} ST_CEC_IR_KEY_PAIR;


//
/******************************************************************************/
//

typedef enum
{
    CEC_DEVICE_DETECT_IDLE  = 0,

    CEC_DEVICE_DETECT_SEND_GIVE_SYSTEM_AUDIO_MODE_STATUS,
    CEC_DEVICE_DETECT_WAIT_SYSTEM_AUDIO_MODE_STATUS,

    CEC_DEVICE_DETECT_SEND_REQUEST_SHORT_AUDIO_DESCRIPTOR,
    CEC_DEVICE_DETECT_WAIT_REPORT_SHORT_ADUIO_DESCRIPTOR,

    CEC_DEVICE_DETECT_SEND_REQUEST_ARC_INITIATION,
    CEC_DEVICE_DETECT_WAIT_INITIATE_ARC,

    CEC_DEVICE_DETECT_SEND_REQUEST_ACTIVE_SOURCE,
    CEC_DEVICE_DETECT_WAIT_ACTIVE_SOURCE,

    CEC_DEVICE_DETECT_SEND_GIVE_DEVICE_POWER_STATUS,
    CEC_DEVICE_DETECT_WAIT_REPORT_POWER_STATUS,
    CEC_DEVICE_DETECT_GIVE_DEVICE_POWER_STATUS_RETRANSMISSION,

    CEC_DEVICE_DETECT_SEND_STREAM_PATH,

    CEC_DEVICE_DETECT_PROCESS_FINISH,

} EN_CEC_STATE_DEVICE_DETECT;

typedef struct _ST_CEC_STATE_DEVICE_DETECT
{
    EN_CEC_STATE_DEVICE_DETECT enState;

    MS_U8 MyPhysicalAddress[2];

    MsCEC_DEVICELA enDstDeviceLA;

    MS_U8  RetransmissionTimes;

} ST_CEC_STATE_DEVICE_DETECT;

//
/******************************************************************************/
//

typedef enum
{
    CEC_ARC_OFF2ON_IDLE = 0,

    CEC_ARC_OFF2ON_SEND_REQUEST_ARC_INITIATION,
    CEC_ARC_OFF2ON_WAIT_INITIATE_ARC,

    CEC_ARC_OFF2ON_PROCESS_FINISH,

} EN_CEC_STATE_ARC_OFF2ON;

typedef struct _ST_CEC_STATE_ARC_OFF2ON
{
    EN_CEC_STATE_ARC_OFF2ON enState;

} ST_CEC_STATE_ARC_OFF2ON;

//
/******************************************************************************/
//

typedef enum
{
    CEC_ARC_ON2OFF_IDLE = 0,

    CEC_ARC_ON2OFF_SEND_REQUEST_ARC_TERMINATION,
    CEC_ARC_ON2OFF_WAIT_TERMINATE_ARC,

    CEC_ARC_ON2OFF_PROCESS_FINISH,

} EN_CEC_STATE_ARC_ON2OFF;

typedef struct _ST_CEC_STATE_ARC_ON2OFF
{
    EN_CEC_STATE_ARC_ON2OFF enState;

} ST_CEC_STATE_ARC_ON2OFF;

//
/******************************************************************************/
//

///Define CEC Extend Info Struct
typedef struct _ST_CEC_FUNAI_STATE_INFO_LIST
{
    ST_CEC_STATE_DEVICE_DETECT              stState_DeviceDetect;

    ST_CEC_STATE_ARC_OFF2ON                 stState_ArcOff2On;
    ST_CEC_STATE_ARC_ON2OFF                 stState_ArcOn2Off;

} ST_CEC_STATE_INFO_LIST;



//
/******************************************************************************/
//

#define CEC_OPCODE_SET                  256
#define CEC_OPCODE_STRING_LENTGH        35
extern const U8 CEC_opCodeStr_Customer[CEC_OPCODE_SET][CEC_OPCODE_STRING_LENTGH];

//
/******************************************************************************/
//

void msCecLoadDefaultDeviceName(MS_U8 u8Device, EN_LANGUAGE pLanguage);


//
/******************************************************************************/
//

void msAPI_CEC_ActionForCecOff(void);

#endif // ENABLE_CEC

#endif

