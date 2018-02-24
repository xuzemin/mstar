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
/// @file   Mapi_mhl.h
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
    1. Check whether MHL cable is plugged or not in Rx side
    2. Disable R-term and output Vbus
    3. Check whether Cbus is connected(discovery pulse completed)
    4. Sink -> Source: "SET_HPD"
    5. Sink -> Source: Write_Stat - "DCAP_RDY" and Write_INT - "DCAP_CHG"
    6. Sink -> Source: Write_Stat - "PATH_EN"
*/

#ifndef _MDRV_MHL_ST_H_
#define _MDRV_MHL_ST_H_

#include "MsTypes.h"
#include "MsCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Define
//-------------------------------------------------------------------------------------------------
#define MODIFY_FOR_LG_LAYOUT            0
#define DMHL_INT_ENABLE                 0 // MHL interrupt enable

#define DMHL_CTS                        1 // MHL setting for CTS
#define DMHL_TIMER_POLLING_COUNTER      0
#define DMHL_TIMER_POLLING_INTERVAL     (!DMHL_TIMER_POLLING_COUNTER)

#define DEM_POLLING_DELAY               10     // Main Loop Polling interval (ms)
#define CBUS_COMMAND_TIMEOUT_SECS       2       // No response for 1 second means we hold off and move
#define CBUS_ABORT_PADING_SECS          2       // Allow bus to quieten down when ABORTs are received.
#define CBUS_TIMER_CONTROL_MASK         32768
#define CBUS_TIMER_SECOND_COUNT         1010
#define CBUS_MSC_WAIT_TIME_MS           150
#define CBUS_SWITCH_MUX_TIME_MS         3500
#define CBUS_POLLING_TIMER_INTERVAL     10 // Unit ms
#define CBUS_WAIT_MSC_RESPONSE_INTERVAL 101 // 10ms one unit
#define CBUS_MSG_RCP_RELEASE_INTERVAL   15 // 10ms one unit
#define CBUS_CHECK_CONTENT_ON_INTERVAL  101 // 10ms one unit

#define DMHL_ADOPTER_ID                 0x02CB // Mstar: 715
#define DMHL_DEVICE_ID                  0x0000 // Chip ID?
#define DMHL_VENDOR_ID                  0x00 // ?

#define MHL_DEVICE_CAPABILITY_SIZE      16
#define MHL_MSC_SCRATCHPAD_SIZE         16
#define MHL_CBUS_DATA_SIZE              (MHL_MSC_SCRATCHPAD_SIZE +2) // offset + maxi 16 packets
#define DMHL_CBUS_TX_FIFO               (MHL_MSC_SCRATCHPAD_SIZE +3) // Write_Burst(0x6C) + offset(0x40 ~ 0x7F) + maxi 16 packets + EOF(0x32)
#define MHL_CBUS_TX_QUEUE_NUM           3
#define MHL_CBUS_TOTAL_QUEUE_NUM        ((MHL_CBUS_TX_QUEUE_NUM > 0)?(MHL_CBUS_TX_QUEUE_NUM +1):2)
#define MHL_CBUS_RX_QUEUE_INDEX         (MHL_CBUS_TOTAL_QUEUE_NUM -1)

#define DMHL_CTS_HDCP_PATCH             DISABLE// for CTS HDCP 2C-04
#define DMHL_LG_PRADA_PATCH             ENABLE// for LG PRADA patch
#define DMHL_IGNORE_USB_PULSE_PATCH     ENABLE // for ignore USB pulse patch
#define DMHL_DE_UNSTABLE_PATCH          ENABLE
#define DMHL_WAKE_UP_PULSE_INT          ENABLE
#define DMHL_CTS_SEND_MSC               ENABLE
#define DMHL_TEST_HDCP_SOFTWARE_PATCH   ENABLE
#define DMHL_AUTO_SENT_RAP_POLLING      DISABLE

#define DMHL_TEST_SIGNAL_SUPPORT        DISABLE

#define MHL_INPUT_PORT(a)               (a +65)

#define MASKSET(a, b, c)                ((a &~c) | (b &c))
#define ABS_MINUS(a, b)                 ((a > b)? (a -b): (b -a))

#define MHL_EDID_BLOCK_LENGTH           128
#define MHL_EDID_DTD_LENGTH             18
#define MHL_EDID_FIRST_DTD_START        0x36
#define MHL_EDID_SECOND_DTD_START       0x48
#define MHL_EDID_EXTENSION_FLAG         0x7E  
#define MHL_EDID_RESERVED_DATA_BLOCK    0x82

#define MHL_3D_VIC_ID                   0x0010
#define MHL_3D_DTD_ID                   0x0011

#define MHL_3D_SEQUENCE_LENGTH          5
#define MHL_3D_DTD_INFORMATION_LENGTH   8
#define MHL_3D_VIC_INFORMATION_LENGTH   16

#define MHL_ADOPTER_ID_ROKU             0x0411
#define MHL_ADOPTER_ID_HTC              0x016F

#define MHL_DEVICE_ID_HTC               0x0000

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    CBUS_STATE_IDLE = 0,    // Cbus idle
    CBUS_STATE_SENT,    // Cbus command sent
    CBUS_STATE_ACK,    // Cbus command has been acked
    CBUS_STATE_RECEIVED,    // Cbus message received
    CBUS_STATE_WAITING_ACK,    // Cbus waiting RCPK or PAPK
} CbusState_T;

typedef enum
{
    CBUS_REQ_IDLE       = 0,
    CBUS_REQ_PENDING,           // Request is waiting to be sent
    CBUS_REQ_SENT,              // Request has been sent
    CBUS_REQ_RECEIVED,          // Request data has been received
} CbusReqState_T;

enum CBUS_HEADER_TYPE
{
    DDC_HEADER = 0,
    VENDER_HEADER,
    MSC_HEADER,
};

enum CBUS_CONTROL_TYPE
{
    CBUS_DATA = 0,
    CBUS_CONTROL,
};

enum CBUS_RECEIVE_STATE_TYPE
{
    CBUS_RECEIVE_NORMAL = 0,
    CBUS_RECEIVE_TIMEOUT,
};

enum CBUS_CLOCK_MODE_TYPE
{
    CBUS_CLOCK_RESERVED = 0,
    CBUS_CLOCK_PACKET_PIXEL = 2,
    CBUS_CLOCK_NORMAL_24BIT,
};

enum VBUS_CONTROL_TYPE
{
    VBUS_SW_UNCHARGE = 0,
    VBUS_HW_DETECT,
    VBUS_SW_CHARGE,
};

enum MHL_3D_SUPPORT_TYPE
{
    MHL_3D_FS_SUPPORT = BIT(0),
    MHL_3D_TB_SUPPORT = BIT(1),
    MHL_3D_LR_SUPPORT = BIT(2),
};

enum MHL_3D_DTD_NUMBER_TYPE
{
    MHL_3D_FIRST_DTD = 0,
    MHL_3D_SECOND_DTD,
    MHL_3D_THIRD_DTD,
};

enum MHL_3D_DTD_STEREO_TYPE
{
    MHL_3D_DTD_STEREO_NORMAL_DISPLAY = 0,
    MHL_3D_DTD_STEREO_FIELD_SEQUENTIAL_RIGHT = 2,
    MHL_3D_DTD_STEREO_FIELD_SEQUENTIAL_LEFT = 4,
    MHL_3D_DTD_STEREO_2WAY_INTERLEAVED_RIGHT = 3,
    MHL_3D_DTD_STEREO_2WAY_INTERLEAVED_LEFT = 5,
    MHL_3D_DTD_STEREO_4WAY_INTERLEAVED = 6,
    MHL_3D_DTD_STEREO_SIDE_BY_SIDE_INTERLEAVED = 7,
};

enum MHL_EDID_DATA_BLOCK_CODE_TYPE
{
    MHL_EDID_AUDIO_DATA_BLOCK_CODE = 1,
    MHL_EDID_VIDEO_DATA_BLOCK_CODE = 2,
    MHL_EDID_VENDER_SPECIFIC_DATA_BLOCK_CODE = 3,
    MHL_EDID_SPEAKER_ALLOCATION_DATA_BLOCK_CODE = 4,
    MHL_EDID_VESA_DTC_DATA_BLOCK_CODE = 5,
    MHL_EDID_USE_EXTENDED_TAG_BLOCK_CODE = 7,
};

enum MHL_VIC_PARSING_STATE_TYPE
{
    MHL_VIC_PARSING_START = 0,
    MHL_VIC_PARSING_CHECK_HDMI_VIDEO_PRESENT,
    MHL_VIC_PARSING_CHECK_3D_PRESENT,
    MHL_VIC_PARSING_CHECK_HDMI_VIC,
    MHL_VIC_PARSING_3D_MULTI_PRESENT_00,
    MHL_VIC_PARSING_3D_MULTI_PRESENT_01,
    MHL_VIC_PARSING_3D_MULTI_PRESENT_10,
    MHL_VIC_PARSING_CHECK_3D_STRUCTURE,
    MHL_VIC_PARSING_CHECK_3D_PRESENT_TIMING,
    MHL_VIC_PARSING_FINISH,
};

enum MHL_3D_PRESENT_TIMING_VIC_TYPE
{
    MHL_3D_PRESENT_VIC_1920x1080p24Hz = 32,
    MHL_3D_PRESENT_VIC_1280x720p60Hz = 4,
    MHL_3D_PRESENT_VIC_1920x1080i60Hz = 5,
    MHL_3D_PRESENT_VIC_1280x720p50Hz = 19,
    MHL_3D_PRESENT_VIC_1920x1080i50Hz = 20,
};

typedef enum
{
    RX_HDMI_RTERM = 0,    // HDMI mode
    RX_MHL_RTERM,    // MHL mode
    RX_RTERM_OFF,    // R-term off
} RXRtermControl_T;

enum MHL_CBUS_WRITE_BURST_STATE_TYPE
{
    CBUS_WRITE_BURST_NONE = 0,
    CBUS_WRITE_BURST_START,
    CBUS_WRITE_BURST_SEND_REQUEST,
    CBUS_WRITE_BURST_REVEIVE_GRANT,
    CBUS_WRITE_BURST_SEND_DATA,
    CBUS_WRITE_BURST_END,
};

enum
{
    MSC_ACK = 0x33, // Command/Data byte acknowledged
    MSC_NACK = 0x34, // Command or Data byte not acknowledge
    MSC_ABORT = 0x35, // Transaction abort
    MSC_WRITE_STAT_OR_SET_INT = 0x60,  // Write one status or interrupt register
    MSC_READ_DEVCAP = 0x61, // Read one register
    MSC_GET_STATE = 0x62, // Read CBUS revision level from follower
    MSC_GET_VENDOR_ID = 0x63, // Read vendor ID value from follower.
    MSC_SET_HPD = 0x64, // Set Hot Plug Detect in follower
    MSC_CLR_HPD = 0x65, // Clear Hot Plug Detect in follower
    MSC_MSC_MSG = 0x68, // VS command to send RCP sub-commands
    MSC_GET_SC1_ERRORCODE = 0x69, // Get Vendor-Specific command error code.
    MSC_GET_DDC_ERRORCODE = 0x6A, // Get DDC channel command error code.
    MSC_GET_MSC_ERRORCODE = 0x6B, // Get MSC command error code.
    MSC_WRITE_BURST = 0x6C, // Write 1-16 bytes to responder’s scratchpad.
    MSC_GET_SC3_ERRORCODE = 0x6D, // Get channel 3 command error code.
    MSC_EOF = 0x32, // End of Frame
    MSC_RESERVED = 0xFF,
}; //MscCtrlPkt_T;

enum
{
    SI_HPD_ACTIVE               = 0x00,     // HPD HI, HDCP, EDID, RX Term enabled
    SI_HPD_INACTIVE,                        // HPD LOW, HDCP, RX Term disabled
    SI_HPD_ACTIVE_EX,                       // EDID, RX Term enabled
    SI_HPD_INACTIVE_EX,                     // HPD HI, HDCP, EDID, RX Term disabled
    SI_HPD_TOGGLE,                  // Special use for CBUS connect
};

enum
{
    MSC_MSG_MSGE = 0x02,    // MSG Error sub-command
    MSC_MSG_RCP = 0x10,    // RCP sub-command
    MSC_MSG_RCPK = 0x11,    // RCP Acknowledge sub-command
    MSC_MSG_RCPE = 0x12,    // RCP Error sub-command
    MSC_MSG_RAP = 0x20,    // Mode Change Warning sub-command
    MSC_MSG_RAPK = 0x21,     // MCW Acknowledge sub-command
    MSC_MSG_UCP = 0x30,     // UCP sub-command
    MSC_MSG_UCPK = 0x31,    // UCP Acknowledge sub-command
    MSC_MSG_UCPE = 0x32,    // UCP Error sub-command
}; //MscMsgSubCmd_T;

enum
{
    MSC_ERRORCODE_NO_ERROR = 0x00,    // Normal response, no error
    MSC_ERRORCODE_RETRY_EXCEEDED = 0x01,    // Re-try threshold exceeded
    MSC_ERRORCODE_PROTOCOL_ERROR = 0x02,    // Protocol error
    MSC_ERRORCODE_PEER_TIMEOUT = 0x04,    // Peer timed out
    MSC_ERRORCODE_INVALID_OPCODE = 0x08,    // Invalid op code
    MSC_ERRORCODE_BAD_OFFSET = 0x10,    // Bad offset in command
    MSC_ERRORCODE_PEER_BUSY = 0x20,    // Peer is busy, can't process new request
};

enum
{
    MSC_MSGE_NO_ERROR = 0x00,     // No Error
    MSC_MSGE_INVALID_SUB_COMMAND_CODE = 0x01,     // The sub-command code is not valid
}; //MsceStatusCode_T;

enum CBUS_DEVCAP_TYPE
{
    MHL_CBUS_DEV_STATE = 0,
    MHL_CBUS_VERSION,
    MHL_CBUS_DEV_CAT,
    MHL_CBUS_ADOPTER_ID_H,
    MHL_CBUS_ADOPTER_ID_L,
    MHL_CBUS_VID_LINK_MODE,
    MHL_CBUS_AUD_LINK_MODE,
    MHL_CBUS_VIDEO_TYPE,
    MHL_CBUS_LOG_DEV_MAP,
    MHL_CBUS_BANDWIDTH,
    MHL_CBUS_FEATURE_FLAG,
    MHL_CBUS_DEVICE_ID_H,
    MHL_CBUS_DEVICE_ID_L,
    MHL_CBUS_SCRATCHPAD_SIZE,
    MHL_CBUS_INT_STAT,
};

typedef struct
{
    MS_BOOL bDCAP_CHG; // 0x20[0], device capability changed
    MS_BOOL bDSCR_CHG; // 0x20[1], device scratchpad changed
    MS_BOOL bREQ_WRT; // 0x20[2], Request-to-Write
    MS_BOOL bGRT_WRT; // 0x20[3], Grant-to-Write
    MS_BOOL bEDID_CHG; // 0x21[1], EDID changed
} DevIntReg_S;

typedef struct
{
    MS_BOOL bDCAP_RDY; // 0x30[0], device capability ready
    MS_U8 CLK_MODE; // 0x31[2:0], MHL clock mode
    MS_BOOL bPATH_EN; // 0x31[3], device TMDS path enable
    MS_BOOL bMUTED; // 0x31[4], device content stream is muted
} DevStatusReg_S;

typedef struct
{
    MS_U8 msgData[MHL_CBUS_DATA_SIZE +1];    // Cbus message data
    MS_U8 cmd;    // MSC command
    MS_U8 len;    // message length
    MS_U8 rcState;    // received state
    CbusReqState_T reqStatus;    // Cbus request status
} CbusReq_S;

typedef struct
{
    CbusReq_S request[MHL_CBUS_TOTAL_QUEUE_NUM];
    //MS_U32 reqWrtTimer;    // Timer for RAP command response
    //MS_BOOL bMhlCbusConnected;    // True if a connected MHD port
    CbusState_T MhlCbusState;    // MHL Cbus state
    MS_U16 timeout;    // Timer for message response (must be able to indicate at least 3000ms).
    MS_U8 curIdx;    // current index.
    //MS_BOOL bMhlHpdState;    // SET_HPD(TRUE) / CLR_HPD(FALSE)
    //MS_BOOL reqWrt;    // request to write peer's scratchpad regs
    MS_BOOL bIsCmdinDataField;    // Is command in data field
    //DevIntReg_S MhlDevIntReg;
    //DevStatusReg_S MhlDevStatusReg;
} CbusInfo_S;

typedef struct
{
    MS_U8 ucSystemIndex;
    MS_U8 ucCbusIndex; // MHL Cbus status
    MS_U8 ucCbusControl;
    MS_U8 ucCbusErrorCode;
    MS_U8 MhlPowerStatus; // MHL power status
    MS_U8 ucSendIndex;
    MS_U8 ucExtendIndex;
    MS_U8 ucAskData;
    MS_U8 ucCellPhone;
    MS_U8 ucMSGData[2];
    MS_U8 ucReceiveCounter;
    MS_U16 usReceiveIndex;
    MS_U16 usCbusS2PatchCnt;
    CbusInfo_S MhlCbusInfo;
} MHLInfo_S;

typedef struct
{
    MS_U8 lens;
    MS_U16 databuf[DMHL_CBUS_TX_FIFO];
} mhalCbusFifo_S;

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
enum MHL_SYSTEM_FLAG_TYPE
{
    MHL_SYSTEM_SENT_CLR_HPD_FLAG = BIT(0),
    MHL_SYSTEM_POWER_ON_TIMER_FLAG = BIT(1),
    MHL_SYSTEM_FORCE_SEND_COMMAND_FLAG = BIT(2),
    MHL_SYSTEM_RECEIVE_LOSE_FLAG = BIT(3),
    MHL_SYSTEM_CHECK_CONTENT_ENABLE_FLAG = BIT(4),
};

enum CBUS_LINK_FLAG_TYPE
{
    CBUS_HPD_SET_FLAG = BIT(0),
    CBUS_DCAP_RDY_FLAG = BIT(2),
    CBUS_DCAP_CHG_FLAG = BIT(3),
    CBUS_PATH_EN_FLAG = BIT(1),
    CBUS_TIME_OUT_FLAG = BIT(4),
    CBUS_POWER_ON_FLAG = BIT(5),
    CBUS_CONNECT_FLAG = BIT(6),
    CBUS_CABLE_PLUG_FLAG = BIT(7),
};

enum MHL_RECEIVE_FLAG_TYPE
{
    CBUS_RECEIVE_MSC_FLAG = BIT(0),
    CBUS_RECEIVE_ACK_FLAG = BIT(1),
    CBUS_RECEIVE_ABORT_FLAG = BIT(2),
    CBUS_RECEIVE_RCP_FLAG = BIT(3),
    CBUS_RECEIVE_RAP_FLAG = BIT(4),
    CBUS_RECEIVE_WAKE_FLAG = BIT(5),
    CBUS_RECEIVE_ERROR_FLAG = BIT(6),
    CBUS_RECEIVE_DEVCAP_FLAG = BIT(7),
    CBUS_RECEIVE_PATH_EN_FLAG = BIT(8),
    CBUS_RECEIVE_MUTED_FLAG = BIT(9),
};

enum MHL_SEND_FLAG_TYPE
{
    CBUS_SEND_RCP_ENABLE_FLAG = BIT(0),
    CBUS_SEND_RAP_ENABLE_FLAG = BIT(1),
    CBUS_SEND_MSG_FINISH_FLAG = BIT(2),
    CBUS_SEND_MSG_COMMAND_FLAG = BIT(3),
    CBUS_SEND_RCP_RELEASE_ENABLE_FLAG = BIT(4),
    CBUS_SEND_CHECK_CONTENT_ON_FLAG = BIT(5),
    CBUS_SEND_READ_DATA_FLAG = BIT(6),
    CBUS_SEND_FINISH_FLAG = BIT(7),
};

enum MHL_EXTEND_FLAG_TYPE
{
    CBUS_RECEIVE_3D_REQ_FLAG = BIT(0),
    CBUS_SEND_3D_VIC_FLAG = BIT(1),
    CBUS_SEND_3D_DTD_FLAG = BIT(2),
};

enum MHL_CELL_PHONE_FLAG_TYPE
{
    CELL_PHONE_ROKU_FLAG = BIT(0),
    CELL_PHONE_HTC_FLAG = BIT(1),
};

#define MHL_CBUS_LINK_MASK              (CBUS_HPD_SET_FLAG |CBUS_PATH_EN_FLAG |CBUS_DCAP_RDY_FLAG)
#define MHL_3D_SUPPORT_MASK             (MHL_3D_FS_SUPPORT |MHL_3D_TB_SUPPORT |MHL_3D_LR_SUPPORT)

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
extern MHLInfo_S gMHLInfo;
extern MS_U8 ucMHLWriteBurstInformation[];

//-------------------------------------------------------------------------------------------------
//  Macro define
//-------------------------------------------------------------------------------------------------
#define GET_MHL_SEND_CLR_HPD()          (MS_BOOL)((gMHLInfo.ucSystemIndex & MHL_SYSTEM_SENT_CLR_HPD_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_CLR_HPD()          (gMHLInfo.ucSystemIndex |= MHL_SYSTEM_SENT_CLR_HPD_FLAG)
#define CLR_MHL_SEND_CLR_HPD()          (gMHLInfo.ucSystemIndex &= ~MHL_SYSTEM_SENT_CLR_HPD_FLAG)

#define GET_MHL_POWER_ON_TIMER()        (MS_BOOL)((gMHLInfo.ucSystemIndex & MHL_SYSTEM_POWER_ON_TIMER_FLAG) ?TRUE :FALSE)
#define SET_MHL_POWER_ON_TIMER()        (gMHLInfo.ucSystemIndex |= MHL_SYSTEM_POWER_ON_TIMER_FLAG)
#define CLR_MHL_POWER_ON_TIMER()        (gMHLInfo.ucSystemIndex &= ~MHL_SYSTEM_POWER_ON_TIMER_FLAG)

#define GET_MHL_FORCE_SEND_COMMAND()    (MS_BOOL)((gMHLInfo.ucSystemIndex & MHL_SYSTEM_FORCE_SEND_COMMAND_FLAG) ?TRUE :FALSE)
#define SET_MHL_FORCE_SEND_COMMAND()    (gMHLInfo.ucSystemIndex |= MHL_SYSTEM_FORCE_SEND_COMMAND_FLAG)
#define CLR_MHL_FORCE_SEND_COMMAND()    (gMHLInfo.ucSystemIndex &= ~MHL_SYSTEM_FORCE_SEND_COMMAND_FLAG)

#define GET_MHL_RECEIVE_LOSE_FLAG()     (MS_BOOL)((gMHLInfo.ucSystemIndex & MHL_SYSTEM_RECEIVE_LOSE_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_LOSE_FLAG()     (gMHLInfo.ucSystemIndex |= MHL_SYSTEM_RECEIVE_LOSE_FLAG)
#define CLR_MHL_RECEIVE_LOSE_FLAG()     (gMHLInfo.ucSystemIndex &= ~MHL_SYSTEM_RECEIVE_LOSE_FLAG)

#define GET_MHL_CHECK_CONTENT_ENABLE()  (MS_BOOL)((gMHLInfo.ucSystemIndex & MHL_SYSTEM_CHECK_CONTENT_ENABLE_FLAG) ?TRUE :FALSE)
#define SET_MHL_CHECK_CONTENT_ENABLE()  (gMHLInfo.ucSystemIndex |= MHL_SYSTEM_CHECK_CONTENT_ENABLE_FLAG)
#define CLR_MHL_CHECK_CONTENT_ENABLE()  (gMHLInfo.ucSystemIndex &= ~MHL_SYSTEM_CHECK_CONTENT_ENABLE_FLAG)

#define GET_MHL_CABLE_PLUGGED()         (MS_BOOL)((gMHLInfo.ucCbusIndex & CBUS_CABLE_PLUG_FLAG) ?TRUE :FALSE)
#define SET_MHL_CABLE_PLUGGED()         (gMHLInfo.ucCbusIndex |= CBUS_CABLE_PLUG_FLAG)
#define CLR_MHL_CABLE_PLUGGED()         (gMHLInfo.ucCbusIndex &= ~CBUS_CABLE_PLUG_FLAG)

#define GET_MHL_CBUS_CONNECT()          (MS_BOOL)((gMHLInfo.ucCbusIndex & CBUS_CONNECT_FLAG) ?TRUE :FALSE)
#define SET_MHL_CBUS_CONNECT()          (gMHLInfo.ucCbusIndex |= CBUS_CONNECT_FLAG)
#define CLR_MHL_CBUS_CONNECT()          (gMHLInfo.ucCbusIndex &= ~CBUS_CONNECT_FLAG)

#define GET_MHL_PORT_ON_FLAG()          (MS_BOOL)((gMHLInfo.ucCbusIndex & CBUS_POWER_ON_FLAG) ?TRUE :FALSE)
#define SET_MHL_PORT_ON_FLAG()          (gMHLInfo.ucCbusIndex |= CBUS_POWER_ON_FLAG)
#define CLR_MHL_PORT_ON_FLAG()          (gMHLInfo.ucCbusIndex &= ~CBUS_POWER_ON_FLAG)

#define GET_MHL_HPD_SET_FLAG()          (MS_BOOL)((gMHLInfo.ucCbusIndex & CBUS_HPD_SET_FLAG) ?TRUE :FALSE)
#define SET_MHL_HPD_SET_FLAG()          (gMHLInfo.ucCbusIndex |= CBUS_HPD_SET_FLAG)
#define CLR_MHL_HPD_SET_FLAG()          (gMHLInfo.ucCbusIndex &= ~CBUS_HPD_SET_FLAG)

#define GET_MHL_DCAP_RDY_FLAG()         (MS_BOOL)((gMHLInfo.ucCbusIndex & CBUS_DCAP_RDY_FLAG) ?TRUE :FALSE)
#define SET_MHL_DCAP_RDY_FLAG()         (gMHLInfo.ucCbusIndex |= CBUS_DCAP_RDY_FLAG)
#define CLR_MHL_DCAP_RDY_FLAG()         (gMHLInfo.ucCbusIndex &= ~CBUS_DCAP_RDY_FLAG)

#define GET_MHL_DCAP_CHG_FLAG()         (MS_BOOL)((gMHLInfo.ucCbusIndex & CBUS_DCAP_CHG_FLAG) ?TRUE :FALSE)
#define SET_MHL_DCAP_CHG_FLAG()         (gMHLInfo.ucCbusIndex |= CBUS_DCAP_CHG_FLAG)
#define CLR_MHL_DCAP_CHG_FLAG()         (gMHLInfo.ucCbusIndex &= ~CBUS_DCAP_CHG_FLAG)

#define GET_MHL_PATH_EN_FLAG()          (MS_BOOL)((gMHLInfo.ucCbusIndex & CBUS_PATH_EN_FLAG) ?TRUE :FALSE)
#define SET_MHL_PATH_EN_FLAG()          (gMHLInfo.ucCbusIndex |= CBUS_PATH_EN_FLAG)
#define CLR_MHL_PATH_EN_FLAG()          (gMHLInfo.ucCbusIndex &= ~CBUS_PATH_EN_FLAG)

#define GET_MHL_TIME_OUT_FLAG()         (MS_BOOL)((gMHLInfo.ucCbusIndex & CBUS_TIME_OUT_FLAG) ?TRUE :FALSE)
#define SET_MHL_TIME_OUT_FLAG()         (gMHLInfo.ucCbusIndex |= CBUS_TIME_OUT_FLAG)
#define CLR_MHL_TIME_OUT_FLAG()         (gMHLInfo.ucCbusIndex &= ~CBUS_TIME_OUT_FLAG)

#define GET_CBUS_LINK_FLAG()            (gMHLInfo.ucCbusIndex & MHL_CBUS_LINK_MASK)
#define CLR_CBUS_LINK_FLAG()            (gMHLInfo.ucCbusIndex &= ~MHL_CBUS_LINK_MASK)
#define CLR_CBUS_CABLE_FLAG()           (gMHLInfo.ucCbusIndex &= CBUS_POWER_ON_FLAG)

#define GET_CBUS_LINK_CHECK()           (gMHLInfo.ucCbusControl & MHL_CBUS_LINK_MASK)
#define SET_CBUS_LINK_CHECK(a)          (gMHLInfo.ucCbusControl = MASKSET(gMHLInfo.ucCbusControl, a, MHL_CBUS_LINK_MASK))
#define CLR_CBUS_LINK_CHECK()           (gMHLInfo.ucCbusControl &= ~MHL_CBUS_LINK_MASK)

#define GET_CBUS_LINK_FINISH()          (((GET_CBUS_LINK_CHECK() ^MHL_CBUS_LINK_MASK) > 0) ?FALSE :TRUE)

#define GET_MHL_CBUS_STATE()            (gMHLInfo.MhlCbusInfo.MhlCbusState)
#define SET_MHL_CBUS_STATE(a)           (gMHLInfo.MhlCbusInfo.MhlCbusState = a)

#define GET_MHL_RECEIVE_MSC()           (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_MSC_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_MSC()           (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_MSC_FLAG)
#define CLR_MHL_RECEIVE_MSC()           (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_MSC_FLAG)

#define GET_MHL_RECEIVE_ACK()           (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_ACK_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_ACK()           (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_ACK_FLAG)
#define CLR_MHL_RECEIVE_ACK()           (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_ACK_FLAG)

#define GET_MHL_RECEIVE_ABORT()         (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_ABORT_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_ABORT()         (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_ABORT_FLAG)
#define CLR_MHL_RECEIVE_ABORT()         (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_ABORT_FLAG)

#define GET_MHL_RECEIVE_RCP()           (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_RCP_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_RCP()           (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_RCP_FLAG)
#define CLR_MHL_RECEIVE_RCP()           (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_RCP_FLAG)

#define GET_MHL_RECEIVE_RAP()           (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_RAP_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_RAP()           (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_RAP_FLAG)
#define CLR_MHL_RECEIVE_RAP()           (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_RAP_FLAG)

#define GET_MHL_RECEIVE_WAKE()          (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_WAKE_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_WAKE()          (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_WAKE_FLAG)
#define CLR_MHL_RECEIVE_WAKE()          (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_WAKE_FLAG)

#define GET_MHL_RECEIVE_ERROR()         (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_ERROR_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_ERROR()         (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_ERROR_FLAG)
#define CLR_MHL_RECEIVE_ERROR()         (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_ERROR_FLAG)

#define GET_MHL_RECEIVE_DEVCAP()        (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_DEVCAP_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_DEVCAP()        (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_DEVCAP_FLAG)
#define CLR_MHL_RECEIVE_DEVCAP()        (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_DEVCAP_FLAG)

#define GET_MHL_RECEIVE_PATH_EN()       (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_PATH_EN_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_PATH_EN()       (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_PATH_EN_FLAG)
#define CLR_MHL_RECEIVE_PATH_EN()       (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_PATH_EN_FLAG)

#define GET_MHL_RECEIVE_MUTED()         (MS_BOOL)((gMHLInfo.usReceiveIndex & CBUS_RECEIVE_MUTED_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_MUTED()         (gMHLInfo.usReceiveIndex |= CBUS_RECEIVE_MUTED_FLAG)
#define CLR_MHL_RECEIVE_MUTED()         (gMHLInfo.usReceiveIndex &= ~CBUS_RECEIVE_MUTED_FLAG)

#define CLR_MHL_RECEIVE_FLAG()          (gMHLInfo.usReceiveIndex = 0)

#define GET_MHL_SEND_RCP_ENABLE()       (MS_BOOL)((gMHLInfo.ucSendIndex & CBUS_SEND_RCP_ENABLE_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_RCP_ENABLE()       (gMHLInfo.ucSendIndex |= CBUS_SEND_RCP_ENABLE_FLAG)
#define CLR_MHL_SEND_RCP_ENABLE()       (gMHLInfo.ucSendIndex &= ~CBUS_SEND_RCP_ENABLE_FLAG)

#define GET_MHL_SEND_RAP_ENABLE()       (MS_BOOL)((gMHLInfo.ucSendIndex & CBUS_SEND_RAP_ENABLE_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_RAP_ENABLE()       (gMHLInfo.ucSendIndex |= CBUS_SEND_RAP_ENABLE_FLAG)
#define CLR_MHL_SEND_RAP_ENABLE()       (gMHLInfo.ucSendIndex &= ~CBUS_SEND_RAP_ENABLE_FLAG)

#define GET_MHL_SEND_MSG_FINISH()       (MS_BOOL)((gMHLInfo.ucSendIndex & CBUS_SEND_MSG_FINISH_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_MSG_FINISH()       (gMHLInfo.ucSendIndex |= CBUS_SEND_MSG_FINISH_FLAG)
#define CLR_MHL_SEND_MSG_FINISH()       (gMHLInfo.ucSendIndex &= ~CBUS_SEND_MSG_FINISH_FLAG)

#define GET_MHL_SEND_MSG_COMMAND()      (MS_BOOL)((gMHLInfo.ucSendIndex & CBUS_SEND_MSG_COMMAND_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_MSG_COMMAND()      (gMHLInfo.ucSendIndex |= CBUS_SEND_MSG_COMMAND_FLAG)
#define CLR_MHL_SEND_MSG_COMMAND()      (gMHLInfo.ucSendIndex &= ~CBUS_SEND_MSG_COMMAND_FLAG)

#define GET_MHL_SEND_RCP_RELEASE_FLAG() (MS_BOOL)((gMHLInfo.ucSendIndex & CBUS_SEND_RCP_RELEASE_ENABLE_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_RCP_RELEASE_FLAG() (gMHLInfo.ucSendIndex |= CBUS_SEND_RCP_RELEASE_ENABLE_FLAG)
#define CLR_MHL_SEND_RCP_RELEASE_FLAG() (gMHLInfo.ucSendIndex &= ~CBUS_SEND_RCP_RELEASE_ENABLE_FLAG)

#define GET_MHL_SEND_CHECK_CONTENT_ON() (MS_BOOL)((gMHLInfo.ucSendIndex & CBUS_SEND_CHECK_CONTENT_ON_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_CHECK_CONTENT_ON() (gMHLInfo.ucSendIndex |= CBUS_SEND_CHECK_CONTENT_ON_FLAG)
#define CLR_MHL_SEND_CHECK_CONTENT_ON() (gMHLInfo.ucSendIndex &= ~CBUS_SEND_CHECK_CONTENT_ON_FLAG)

#define GET_MHL_SEND_READ()             (MS_BOOL)((gMHLInfo.ucSendIndex & CBUS_SEND_READ_DATA_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_READ()             (gMHLInfo.ucSendIndex |= CBUS_SEND_READ_DATA_FLAG)
#define CLR_MHL_SEND_READ()             (gMHLInfo.ucSendIndex &= ~CBUS_SEND_READ_DATA_FLAG)

#define GET_MHL_SEND_FINISH()           (MS_BOOL)((gMHLInfo.ucSendIndex & CBUS_SEND_FINISH_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_FINISH()           (gMHLInfo.ucSendIndex |= CBUS_SEND_FINISH_FLAG)
#define CLR_MHL_SEND_FINISH()           (gMHLInfo.ucSendIndex &= ~CBUS_SEND_FINISH_FLAG)

#define CLR_MHL_SEND_FLAG()             (gMHLInfo.ucSendIndex = 0)

#define GET_MHL_RECEIVE_3D_REQ()        (MS_BOOL)((gMHLInfo.ucExtendIndex & CBUS_RECEIVE_3D_REQ_FLAG) ?TRUE :FALSE)
#define SET_MHL_RECEIVE_3D_REQ()        (gMHLInfo.ucExtendIndex |= CBUS_RECEIVE_3D_REQ_FLAG)
#define CLR_MHL_RECEIVE_3D_REQ()        (gMHLInfo.ucExtendIndex &= ~CBUS_RECEIVE_3D_REQ_FLAG)

#define GET_MHL_SEND_3D_VIC()           (MS_BOOL)((gMHLInfo.ucExtendIndex & CBUS_SEND_3D_VIC_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_3D_VIC()           (gMHLInfo.ucExtendIndex |= CBUS_SEND_3D_VIC_FLAG)
#define CLR_MHL_SEND_3D_VIC()           (gMHLInfo.ucExtendIndex &= ~CBUS_SEND_3D_VIC_FLAG)

#define GET_MHL_SEND_3D_DTD()           (MS_BOOL)((gMHLInfo.ucExtendIndex & CBUS_SEND_3D_DTD_FLAG) ?TRUE :FALSE)
#define SET_MHL_SEND_3D_DTD()           (gMHLInfo.ucExtendIndex |= CBUS_SEND_3D_DTD_FLAG)
#define CLR_MHL_SEND_3D_DTD()           (gMHLInfo.ucExtendIndex &= ~CBUS_SEND_3D_DTD_FLAG)

#define GET_MHL_WRITE_BURST_STATE()     ((gMHLInfo.ucExtendIndex &BMASK(7:5)) >>5)
#define SET_MHL_WRITE_BURST_STATE(a)    (gMHLInfo.ucExtendIndex = MASKSET(gMHLInfo.ucExtendIndex, (a <<5), BMASK(7:5)))

#define CLR_MHL_EXTEND_FLAG()           (gMHLInfo.ucExtendIndex = 0)

#define GET_MHL_ROKU_DEVICE_FLAG()      (MS_BOOL)((gMHLInfo.ucCellPhone & CELL_PHONE_ROKU_FLAG) ?TRUE :FALSE)
#define SET_MHL_ROKU_DEVICE_FLAG()      (gMHLInfo.ucCellPhone |= CELL_PHONE_ROKU_FLAG)
#define CLR_MHL_ROKU_DEVICE_FLAG()      (gMHLInfo.ucCellPhone &= ~CELL_PHONE_ROKU_FLAG)

#define GET_MHL_HTC_PHONE_FLAG()        (MS_BOOL)((gMHLInfo.ucCellPhone & CELL_PHONE_HTC_FLAG) ?TRUE :FALSE)
#define SET_MHL_HTC_PHONE_FLAG()        (gMHLInfo.ucCellPhone |= CELL_PHONE_HTC_FLAG)
#define CLR_MHL_HTC_PHONE_FLAG()        (gMHLInfo.ucCellPhone &= ~CELL_PHONE_HTC_FLAG)

#define CLR_MHL_CELL_PHONE_FLAG()       (gMHLInfo.ucCellPhone = 0)

#define GET_MHL_CBUS_QUEUE(a)           (gMHLInfo.MhlCbusInfo.request[a])
#define GET_MHL_QUEUE_STATE(a)          (GET_MHL_CBUS_QUEUE(a).reqStatus)
#define SET_MHL_QUEUE_STATE(a ,b)       (GET_MHL_CBUS_QUEUE(a).reqStatus = b)

#if(DMHL_TIMER_POLLING_INTERVAL)
#define GET_MHL_DEBOUNCE_TIMER()        (gMHLInfo.usCbusS2PatchCnt)
#define SET_MHL_DEBOUNCE_TIMER(a)       (gMHLInfo.usCbusS2PatchCnt = a)
#define DEC_MHL_DEBOUNCE_TIMER()        (gMHLInfo.usCbusS2PatchCnt--)

#define GET_MHL_TIMEOUT_TIMER()         (gMHLInfo.MhlCbusInfo.timeout)
#define SET_MHL_TIMEOUT_TIMER(a)        (gMHLInfo.MhlCbusInfo.timeout = a)
#define DEC_MHL_TIMEOUT_TIMER()         (gMHLInfo.MhlCbusInfo.timeout--)

#else
#define GET_MHL_DEBOUNCE_TIMER()        (gMHLInfo.usCbusS2PatchCnt)
#define SET_MHL_DEBOUNCE_TIMER(a)       (gMHLInfo.usCbusS2PatchCnt = a /DEM_POLLING_DELAY)
#define DEC_MHL_DEBOUNCE_TIMER()        (gMHLInfo.usCbusS2PatchCnt--)

#define GET_MHL_TIMEOUT_TIMER()         (gMHLInfo.usCbusS2PatchCnt)
#define SET_MHL_TIMEOUT_TIMER(a)        (gMHLInfo.usCbusS2PatchCnt = a *1010 /DEM_POLLING_DELAY)
#define DEC_MHL_TIMEOUT_TIMER()         (gMHLInfo.usCbusS2PatchCnt--)

#endif

#define GET_MHL_CBUS_ERROE_CODE()       (gMHLInfo.ucCbusErrorCode)
#define SET_MHL_CBUS_ERROE_CODE(a)      (gMHLInfo.ucCbusErrorCode = a)

#define GET_MHL_POWER_STATUS()          (gMHLInfo.MhlPowerStatus &BMASK(3:0))
#define SET_MHL_POWER_STATUS(a)         (gMHLInfo.MhlPowerStatus = MASKSET(gMHLInfo.MhlPowerStatus, a, BMASK(3:0)))

#define GET_MHL_PORT_SELECT()           ((gMHLInfo.MhlPowerStatus &BMASK(7:4)) >>4)
#define SET_MHL_PORT_SELECT(a)          (gMHLInfo.MhlPowerStatus = MASKSET(gMHLInfo.MhlPowerStatus, (a <<4), BMASK(7:4)))

#define GET_MHL_CBUS_ASK_DATA()         (gMHLInfo.ucAskData)
#define SET_MHL_CBUS_ASK_DATA(a)        (gMHLInfo.ucAskData = a)

#define GET_MHL_RX_MSG_COMMAND()        (gMHLInfo.ucMSGData[0])
#define SET_MHL_RX_MSG_COMMAND(a)       (gMHLInfo.ucMSGData[0] = a)

#define GET_MHL_RX_MSG_DATA()           (gMHLInfo.ucMSGData[1])
#define SET_MHL_RX_MSG_DATA(a)          (gMHLInfo.ucMSGData[1] = a)

#define GET_MHL_RX_RECEIVE_COUNTER()    (gMHLInfo.ucReceiveCounter)
#define CLR_MHL_RX_RECEIVE_COUNTER()    (gMHLInfo.ucReceiveCounter = 0)
#define INC_MHL_RX_RECEIVE_COUNTER()    (gMHLInfo.ucReceiveCounter++)
#define DEC_MHL_RX_RECEIVE_COUNTER()    (gMHLInfo.ucReceiveCounter--)

#define CLR_MHL_PLUGGED_FLAG()          (CLR_CBUS_CABLE_FLAG(), CLR_CBUS_LINK_CHECK(), CLR_MHL_RECEIVE_FLAG(), CLR_MHL_SEND_FLAG(), CLR_MHL_RX_RECEIVE_COUNTER())
#define CLR_MHL_CONNECT_FLAG()          (CLR_CBUS_LINK_FLAG(), CLR_CBUS_LINK_CHECK(), CLR_MHL_RECEIVE_FLAG(), CLR_MHL_SEND_FLAG(), CLR_MHL_RX_RECEIVE_COUNTER())

#define GET_MHL_WRITE_BURST_LENGTH()    (ucMHLWriteBurstInformation[MHL_MSC_SCRATCHPAD_SIZE])
#define SET_MHL_WRITE_BURST_LENGTH(a)   (ucMHLWriteBurstInformation[MHL_MSC_SCRATCHPAD_SIZE] = a)
#define GET_MHL_WRITE_BURST_ADDRESS()   (ucMHLWriteBurstInformation[MHL_MSC_SCRATCHPAD_SIZE +1])
#define SET_MHL_WRITE_BURST_ADDRESS(a)  (ucMHLWriteBurstInformation[MHL_MSC_SCRATCHPAD_SIZE +1] = a)
#define GET_MHL_WRITE_BURST_DATA(a)     (ucMHLWriteBurstInformation[a])
#define SET_MHL_WRITE_BURST_DATA(a,b)   (ucMHLWriteBurstInformation[a] = b)

#ifdef __cplusplus
}
#endif

#endif //_MDRV_MHL_ST_H_


