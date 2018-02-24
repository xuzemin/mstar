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

//
//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//


//
//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
//


//
//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------
//

ST_CEC_Feature_Support stCecFeatureSupport;

/*
Logical Device             Default Displayed name
-------------------------------------------------
1  Recording Device1       Recorder1
2  Recording Device2       Recorder2
3  Tuner1                  Tuner1
4  Playback Device1        Player1
5  Audio System            Audio System
6  Tuner2                  Tuner2
7  Tuner3                  Tuner3
8  Playback Device2        Player2
9  Recording Device3       Recorder3
10 Tuner4                  Tuner4
11 Playback Device3        Player3
12 Reserved                Device1
13 Reserved                Device2
14 Specific Use            Device3
15 Unregistered            Not displayed
*/

const MS_U8 code gStrCECDeviceTypeEng[E_LA_MAX+1][MAX_CEC_DEVICE_OSD_NAME]=
{
    {'T', 'V', '\0'},
    {'R', 'e', 'c', 'o', 'r', 'd', 'e', 'r', '1', '\0'},
    {'R', 'e', 'c', 'o', 'r', 'd', 'e', 'r', '2', '\0'},
    {'T', 'u', 'n', 'e', 'r', '1', '\0'},
    {'P', 'l', 'a', 'y', 'e', 'r', '1', '\0'},
    {'A', 'u', 'd', 'i', 'o', ' ', 's', 'y', 's', 't', 'e', 'm','\0'},
    {'T', 'u', 'n', 'e', 'r', '2', '\0'},
    {'T', 'u', 'n', 'e', 'r', '3', '\0'},
    {'P', 'l', 'a', 'y', 'e', 'r', '2', '\0'},
    {'R', 'e', 'c', 'o', 'r', 'd', 'e', 'r', '3', '\0'},
    {'T', 'u', 'n', 'e', 'r', '4', '\0'},
    {'P', 'l', 'a', 'y', 'e', 'r', '3', '\0'},
    {'D', 'e', 'v', 'i', 'c', 'e', '1', '\0'},
    {'D', 'e', 'v', 'i', 'c', 'e', '2', '\0'},
    {'D', 'e', 'v', 'i', 'c', 'e', '3', '\0'},
    {'B', 'r', 'o', 'a', 'd', 'c', 'a', 's', 't', '\0'},
};

const MS_U8 code gStrCECDeviceTypeFre[E_LA_MAX+1][MAX_CEC_DEVICE_OSD_NAME]=
{
    {'T', 'V', '\0'},
    {'E', 'n', 'r', 'e', 'g', 'i', 's', 't', 'r', 'e', 'u', 'r', '1', '\0'},
    {'E', 'n', 'r', 'e', 'g', 'i', 's', 't', 'r', 'e', 'u', 'r', '2', '\0'},
    {'S', 'y', 'n', 't', 'o', 'n', 'i', 's', 'e', 'u', 'r', '1', '\0'},
    {'L', 'e', 'c', 't', 'e', 'u', 'r', '1', '\0'},
    {'S', 'y', 's', 't', 0xE8, 'm', 'e', ' ', 'a', 'u', 'd', 'i', 'o', '\0'},
    {'S', 'y', 'n', 't', 'o', 'n', 'i', 's', 'e', 'u', 'r', '2', '\0'},
    {'S', 'y', 'n', 't', 'o', 'n', 'i', 's', 'e', 'u', 'r', '3', '\0'},
    {'L', 'e', 'c', 't', 'e', 'u', 'r', '2', '\0'},
    {'E', 'n', 'r', 'e', 'g', 'i', 's', 't', 'r', 'e', 'u', 'r', '3', '\0'},
    {'S', 'y', 'n', 't', 'o', 'n', 'i', 's', 'e', 'u', 'r', '4', '\0'},
    {'L', 'e', 'c', 't', 'e', 'u', 'r', '3', '\0'},
    {'P', 0xE9, 'r', 'i', 'p', 'h', 0xE9, 'r', 'i', 'q', 'u', 'e', '1', '\0'},
    {'P', 0xE9, 'r', 'i', 'p', 'h', 0xE9, 'r', 'i', 'q', 'u', 'e', '2', '\0'},
    {'P', 0xE9, 'r', 'i', 'p', 'h', 0xE9, 'r', 'i', 'q', 'u', 'e', '3', '\0'},
    {'B', 'r', 'o', 'a', 'd', 'c', 'a', 's', 't', '\0'},
};

const MS_U8 code gStrCECDeviceTypeEsp[E_LA_MAX+1][MAX_CEC_DEVICE_OSD_NAME]=
{
    {'T', 'V', '\0'},
    {'G', 'r', 'a', 'b', 'a', 'd', 'o', 'r', 'a', '1', '\0'},
    {'G', 'r', 'a', 'b', 'a', 'd', 'o', 'r', 'a', '2', '\0'},
    {'S', 'i', 'n', 't', 'o', 'n', 'i', 'z', 'a', 'd', 'o', 'r', '1', '\0'},
    {'R', 'e', 'p', 'r', 'o', 'd', 'u', 'c', 't', 'o', 'r', '1', '\0'},
    {'S', 'i', 's', 't', 'e', 'm', 'a', ' ', 'd', 'e', ' ', 'a', 'u', 'd', 'i', 'o', '\0'},
    {'S', 'i', 'n', 't', 'o', 'n', 'i', 'z', 'a', 'd', 'o', 'r', '2', '\0'},
    {'S', 'i', 'n', 't', 'o', 'n', 'i', 'z', 'a', 'd', 'o', 'r', '3', '\0'},
    {'R', 'e', 'p', 'r', 'o', 'd', 'u', 'c', 't', 'o', 'r', '2', '\0'},
    {'G', 'r', 'a', 'b', 'a', 'd', 'o', 'r', 'a', '3', '\0'},
    {'S', 'i', 'n', 't', 'o', 'n', 'i', 'z', 'a', 'd', 'o', 'r', '4', '\0'},
    {'R', 'e', 'p', 'r', 'o', 'd', 'u', 'c', 't', 'o', 'r', '3', '\0'},
    {'D', 'i', 's', 'p', 'o', 's', 'i', 't', 'i', 'v', 'o', '1', '\0'},
    {'D', 'i', 's', 'p', 'o', 's', 'i', 't', 'i', 'v', 'o', '2', '\0'},
    {'D', 'i', 's', 'p', 'o', 's', 'i', 't', 'i', 'v', 'o', '3', '\0'},
    {'B', 'r', 'o', 'a', 'd', 'c', 'a', 's', 't', '\0'},
};

//
//******************************************************************************
//

const U8 CEC_opCodeStr_Customer[CEC_OPCODE_SET][CEC_OPCODE_STRING_LENTGH] =
{
    "<Feature Abort>",                  // 0x00
    "",
    "",
    "",
    "<Image View On>",                  // 0x04
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "<Text View On>",                   // 0x0D
    "",
    "",


    "",  //0x10
    "",
    "",
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0x20
    "",
    "",
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0x30
    "",
    "<Set Menu Language>",              // 0x32
    "",
    "",
    "",
    "<Standby>",                        // 0x36
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0x40
    "<Play>",
    "",
    "",
    "<User Ctrl Pressed>",              // 0x44
    "<User Ctrl Released>",             // 0x45
    "<Give OSD Name>",                  // 0x46
    "<Set OSD Name>",                   // 0x47

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0x50
    "",
    "",
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0x60
    "",
    "",
    "",
    "<SetOSDString>[][]",
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "<Sys Audio Mode Request>",         // 0x70
    "<Give Audio Statuss>",             // 0x71
    "<Set System Audio Mode>",          // 0x72
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "<Report Audio Status>",            // 0x7A
    "",
    "",
    "<Give System Audio Mode Status>",  // 0x7D
    "<System Audio Mode Satus>",        // 0x7E
    "",


    "<Routing Change>",                 // 0x80
    "<Routing Information>",            // 0x81
    "<Active Source>",                  // 0x82
    "<Give Physical Address>",          // 0x83
    "<Report Physical Address>",        // 0x84
    "<Request Active Source>",          // 0x85
    "<Set Stream Path>",                // 0x86
    "<Device Vendor ID>",               // 0x87

    "",
    "<Vendor Command>",                 // 0x89
    "<VendorRteBtnDown>",
    "<VendorRteBtnUp>",
    "<Give Device Vendor ID>",          // 0x8C
    "<MenuRequest>",
    "<MenuStatus>",
    "<Give Device Power Status>",       // 0x8F


    "<Report Power Status>",            // 0x90
    "<Get Menu Language>",              // 0x91
    "",
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "<Set Audio Rate>",
    "",
    "",
    "<Inactive Source>",                // 0x9D
    "<CEC Version>",                    // 0x9E
    "<Get CEC Version>",                // 0x9F


    "<Vendor Command With ID>",         // 0xA0
    "",
    "",
    "<Report Short Audio Descriptor>",  // 0xA3
    "<Request Short Audio Descriptor>", // 0xA4
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0xB0
    "",
    "",
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "<Initiate ARC>",           //0xC0
    "<Report ARC Initiated>",
    "<Report ARC Terminated>",
    "<Request ARC Initiation>",
    "<Request ARC Termination>",
    "<Termiate ARC>",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0xD0
    "",
    "",
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0xE0
    "",
    "",
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",


    "",  //0xF0
    "",
    "",
    "",
    "",
    "",
    "",
    "",

    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "<Abort Message>",                  // 0xFF
};


const U8 CEC_AbortReasonStr[6][32] =
{
    "Unrecognized opcode",              // 0x00: E_MAPI_MSG_AR_UNRECOGNIZE_OPCODE
    "Not in correct mode to respond",   // 0x01: E_MAPI_MSG_AR_CANNOTRESPOND
    "Cannot provide source",            // 0x02: E_MAPI_MSG_AR_CANNOTPROVIDESCR
    "Invalid operand",                  // 0x03: E_MAPI_MSG_AR_INVALID_OPCODE
    "Refused",                          // 0x04: E_MAPI_MSG_AR_REFUSED
    "Unable to determine",              // 0x05: E_MAPI_MSG_AR_IGNORED
};

const U8 CEC_ErrorCodeStr[9][20] =
{
    "E_CEC_FEATURE_ABORT",      // E_CEC_FEATURE_ABORT = 0x00
    "E_CEC_RX_SUCCESS",         // E_CEC_RX_SUCCESS    = 0x01,
    "E_CEC_TX_SUCCESS",         // E_CEC_TX_SUCCESS    = 0x02,
    "E_CEC_RF",                 // E_CEC_RF            = 0x04,
    "E_CEC_LOST_ABT",           // E_CEC_LOST_ABT      = 0x08,
    "E_CEC_BIT_SHORT",          // E_CEC_BIT_SHORT     = 0x10,
    "E_CEC_BIT_LONG",           // E_CEC_BIT_LONG      = 0x20,
    "E_CEC_NACK",               // E_CEC_NACK          = 0x40,
    "E_CEC_SYSTEM_BUSY",        // E_CEC_SYSTEM_BUSY   = 0x80,
};

const U8 CEC_StatemachineCecListStr[E_STM_NONE+1][34] =
{
    "",                                 // E_STM_EMPTY
    "",                                 // E_STM_POLLING

    "<Ack bit set>",                    // E_STM_ACKED
    "<Give Physical Address>",          // E_STM_GIVE_PHY_ADDR
    "wait <Report Physical Address>",   // E_STM_REPORT_PHY_ADDR
    "<Give Vendor ID>",                 // E_STM_GIVE_DEV_VENDOR_ID
    "<Get CEC Version>",                // E_STM_GET_CEC_VER
    "<Give OSD Name>",                  // E_STM_GIVE_OSD_NAME
    "<Give System Audio Mode Status>",  // E_STM_GIVE_AUDIO_MODE_STATUS
    "<Request Short Audio Descriptor>", // E_STM_REQUEST_SHORT_AUDIO_DESCRIPTOR

    "<Give Device Power Status>",       // E_STM_GIVE_POW_STATUS
    "<Request Active Source>",          // E_STM_REQUEST_ACTIVE_SOURCE
    "<Set Stream Path>",                // E_STM_SET_STREAM_PATH

    "Done",                             // E_STM_DONE
    "",                                 // E_STM_NONE
};


const MS_U8 CEC_Device_Detect_Str[CEC_DEVICE_DETECT_PROCESS_FINISH+1][64] =
{
    "",

    "Device.Detect <Give System Audio Mode Status>",
    "Device.Detect Wait <System Audio Mode Status>",

    "Device.Detect <Request Short Audio Descriptor>",
    "Device.Detect Wait <Report Short Audio Descriptor>",

    "Device.Detect <Request ARC Initiation>",
    "Device.Detect Wait <Initiate ARC>",

    "Device.Detect <Request Active Source>",
    "Device.Detect Wait <Active Source>",

    "Device.Detect <Give Device Power Status>",
    "Device.Detect Wait <Report Power Status>",
    "Device.Detect <Give Device Power Status> retransmission",

    "Device.Detect <Set Stream Path>",

    "Device.Detect processing is finished",
};

//
//******************************************************************************
//

ST_CEC_IR_KEY_PAIR stCecKeyFromTvtoDevCustomerTable[] =
{
    {E_MSG_UI_UP,                   KEY_UP},
    {E_MSG_UI_DOWN,                 KEY_DOWN},
    {E_MSG_UI_LEFT,                 KEY_LEFT},
    {E_MSG_UI_RIGHT,                KEY_RIGHT},

    {E_MSG_UI_SELECT,               KEY_SELECT},

  #if 0
    {E_MSG_UI_EXIT,                 KEY_EXIT},

    {E_MSG_UI_NUMBER_0,             KEY_0},
    {E_MSG_UI_NUMBER_1,             KEY_1},
    {E_MSG_UI_NUMBER_2,             KEY_2},
    {E_MSG_UI_NUMBER_3,             KEY_3},
    {E_MSG_UI_NUMBER_4,             KEY_4},
    {E_MSG_UI_NUMBER_5,             KEY_5},
    {E_MSG_UI_NUMBER_6,             KEY_6},
    {E_MSG_UI_NUMBER_7,             KEY_7},
    {E_MSG_UI_NUMBER_8,             KEY_8},
    {E_MSG_UI_NUMBER_9,             KEY_9},
  #endif

    {E_MSG_UI_VOLUME_UP,            KEY_VOLUME_PLUS},
    {E_MSG_UI_VOLUME_DOWN,          KEY_VOLUME_MINUS},
    {E_MSG_UI_MUTE,                 KEY_MUTE},

    {E_MSG_UI_PLAY,                 KEY_PLAY},
    {E_MSG_UI_STOP,                 KEY_STOP},
    {E_MSG_UI_PAUSE,                KEY_PAUSE},

    {E_MSG_UI_REWIND,               KEY_REWIND},
    {E_MSG_UI_FAST_FORWARD,         KEY_FF},
    {E_MSG_UI_BACKWARD,             KEY_PREVIOUS},
    {E_MSG_UI_FORWARD,              KEY_NEXT},

  #if 0
    {E_MSG_UI_F1_BLUE,              KEY_BLUE},
    {E_MSG_UI_F2_RED,               KEY_RED},
    {E_MSG_UI_F3_GREEN,             KEY_GREEN},
    {E_MSG_UI_F4_YELLOW,            KEY_YELLOW},
  #endif

    {E_MSG_UI_UNKNOWN,              KEY_NULL}  //End of structure.
};

//
//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
//

static void msCecLoadDefaultDeviceName_All(EN_LANGUAGE pLanguage)
{
    //printf("\e[31;1m >> %s \33[m \n", __FUNCTION__);

    switch (pLanguage)
    {
        default:
        case LANGUAGE_ENGLISH:
            memcpy(_stMsApiCecInfoList.u8CecDeviceName, gStrCECDeviceTypeEng, sizeof(gStrCECDeviceTypeEng));
            break;

        case LANGUAGE_FRENCH:
            memcpy(_stMsApiCecInfoList.u8CecDeviceName, gStrCECDeviceTypeFre, sizeof(gStrCECDeviceTypeFre));
            break;

        case LANGUAGE_SPANISH:
            memcpy(_stMsApiCecInfoList.u8CecDeviceName, gStrCECDeviceTypeEsp, sizeof(gStrCECDeviceTypeEsp));
            break;
    }
}

void msCecLoadDefaultDeviceName(MS_U8 u8Device, EN_LANGUAGE pLanguage)
{
    //printf("\e[31;1m >> msAPI_CEC_LoadDefaultDeviceName(%d, %d) \33[m \n", u8Device, pLanguage);

    switch (pLanguage)
    {
        default:
        case LANGUAGE_ENGLISH:
            memcpy(_stMsApiCecInfoList.u8CecDeviceName[u8Device], gStrCECDeviceTypeEng[u8Device], sizeof(gStrCECDeviceTypeEng[u8Device]));
            break;

        case LANGUAGE_FRENCH:
            memcpy(_stMsApiCecInfoList.u8CecDeviceName[u8Device], gStrCECDeviceTypeFre[u8Device], sizeof(gStrCECDeviceTypeFre[u8Device]));
            break;

        case LANGUAGE_SPANISH:
            memcpy(_stMsApiCecInfoList.u8CecDeviceName[u8Device], gStrCECDeviceTypeEsp[u8Device], sizeof(gStrCECDeviceTypeEsp[u8Device]));
            break;
    }

    //printf("\33[1;31m Devuice[%d]: %s \33[0m \n", u8Device_stMsApiCecInfoList.u8CecDeviceName[u8Device]);
}


BOOLEAN msCecIsRCPassThroughBypass(void)
{
    if (  _eActiveOSD == E_OSD_MAIN_MENU
       || _eActiveOSD == E_OSD_INPUT_SOURCE
       || _eActiveOSD == E_OSD_MESSAGE_BOX
       || _eActiveOSD == E_OSD_FACTORY_MENU
       )
    {
        CEC_DPRINTF("msCecIsRCPassThroughBypass(0x%x) \n", _eActiveOSD);

        return TRUE;
    }

    return FALSE;
}

/******************************************************************************/

static BOOL msCecCheckFeatureSupport_OneTouchPlay(void)
{
    if (  (0) // Settings Assistant mode: Setup mode
       || (0) // Software update mode
       || (!stCecFeatureSupport.bCECFeatureSupport_OneTouchPlay)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return ONE_TOUCH_PLAY_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_RoutingControl(void)
{
    if (  (0) // Standby mode
       || (0) // Software update mode
       || (!stCecFeatureSupport.bCECFeatureSupport_RoutingControl)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return ROUTING_CONTROL_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_SystemStandby(void)
{
    if (  (0) // Standby mode
       || (0) // Software update mode
       || (0) // Factory mode
       || (!stCecFeatureSupport.bCECFeatureSupport_SystemStandby)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return STANDBY_COMMAND_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_SystemInformation(void)
{
    if (  (0) // Software update mode
       || (!stCecFeatureSupport.bCECFeatureSupport_SystemInformation)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return SYSTEM_INFORMATION_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_VendorSpecificCommands(void)
{
    if (  (0) // Software update mode
       || (!stCecFeatureSupport.bCECFeatureSupport_VendorSpecificCommands)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return VENDOR_SPECIFIC_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_DeviceOSDNameTransfer(void)
{
    if (  (0) // Software update mode
       || (!stCecFeatureSupport.bCECFeatureSupport_DeviceOSDNameTransfer)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return DEVICE_OSD_NAME_TRANSFER_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_DeviceMenuControl(void)
{
    if (  (0) // Software update mode
       || (!stCecFeatureSupport.bCECFeatureSupport_DeviceMenuControl)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return DEVICE_MENU_CONTROL_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_RemoteControlPassThrough(void)
{
    if (  (0) // Software update mode
       || (0) // Factory mode
       || (!stCecFeatureSupport.bCECFeatureSupport_RemoteControlPassThrough)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return REMOTE_CONTROL_PASSTHROUGH_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_GiveDevicePowerStatus(void)
{
    if (  (0) // Software update mode
       || (!stCecFeatureSupport.bCECFeatureSupport_GiveDevicePowerStatus)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return POWER_STATUS_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_SystemAudioControl(void)
{
    if (  (0) // Settings Assistant mode: Setup mode
       || (0) // Software update mode
       || (0) // Factory mode
       || (ARC_SUPPORT_PORT == 0) // no ARC support port
       || (!stCecFeatureSupport.bCECFeatureSupport_SystemAudioControl)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return SYSTEM_AUDIO_CONTROL_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_AudioReturnChannelControl(void)
{
    if (  (0) // Settings Assistant mode: Setup mode
       || (0) // Software update mode
       || (0) // Factory mode
       || (ARC_SUPPORT_PORT == 0) // no ARC support port
       || (!stCecFeatureSupport.bCECFeatureSupport_AudioReturnChannelControl)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return AUDIO_RETURN_CHANNEL_SUPPORT;
}

static BOOL msCecCheckFeatureSupport_GeneralProtocolMessageControl(void)
{
    if (  (0) // Software update mode
       || (!stCecFeatureSupport.bCECFeatureSupport_GeneralProtocolMessageControl)
       || (!stCecFeatureSupport.bCECFeatureSupport_ALL)
       )
    {
        return FALSE;
    }

    return TRUE;
}

static BOOL msCecCheckFeatureSupport(U8 u8CecMsgOpcode)
{
    BOOL bRet = FALSE;      // default is not supported, unless we decide it's supported

    switch (u8CecMsgOpcode)
    {
//----- One Touch Play ---------------
        case E_MSG_ACTIVE_SOURCE:
        case E_MSG_OTP_IMAGE_VIEW_ON:
        case E_MSG_OTP_TEXT_VIEW_ON:
        {
            bRet = msCecCheckFeatureSupport_OneTouchPlay();
            break;
        }


//----- Routing Control --------------
        case E_MSG_RC_INACTIVE_SOURCE:
        case E_MSG_RC_REQUEST_ACTIVE_SOURCE:
        case E_MSG_RC_ROUTING_CHANGE:
        case E_MSG_RC_ROUTING_INFORMATION:
        case E_MSG_RC_SET_STREM_PATH:
        {
            bRet = msCecCheckFeatureSupport_RoutingControl();
            break;
        }


//----- Standby Command --------------
        case E_MSG_STANDBY:
        {
            bRet = msCecCheckFeatureSupport_SystemStandby();
            break;
        }


//----- System Information -----------
        case E_MSG_SI_CEC_VERSION:
        case E_MSG_SI_GET_CEC_VERSION:
        {
            bRet = (  msCecCheckFeatureSupport_SystemInformation()
                   && msCecCheckFeatureSupport_VendorSpecificCommands() );
            break;
        }

        case E_MSG_SI_GIVE_PHYSICAL_ADDRESS:
        case E_MSG_SI_REPORT_PHYSICAL_ADDRESS:
        case E_MSG_SI_GET_MENU_LANGUAGE:
        case E_MSG_SI_SET_MENU_LANGUAGE:
        {
            bRet = msCecCheckFeatureSupport_SystemInformation();
            break;
        }


//---------Vendor Specific -----------
        case E_MSG_VS_DEVICE_VENDOR_ID:
        case E_MSG_VS_GIVE_DEVICE_VENDOR_ID:
        {
            bRet = msCecCheckFeatureSupport_VendorSpecificCommands();
            break;
        }


//----- Device OSD Name Transfer  ----
        case E_MSG_OSDNT_GIVE_OSD_NAME:
        case E_MSG_OSDNT_SET_OSD_NAME:
        {
            bRet = msCecCheckFeatureSupport_DeviceOSDNameTransfer();
            break;
        }

//----- Device Menu Control ----------
        case E_MSG_DMC_MENU_REQUEST:
        case E_MSG_DMC_MENU_STATUS:
        {
            bRet = msCecCheckFeatureSupport_DeviceMenuControl();
            break;
        }


//----- Remote Control Passthrough ---
//----- UI Message -------------------
        case E_MSG_DMC_USER_CONTROL_PRESSED:
        case E_MSG_DMC_USER_CONTROL_RELEASED:
        {
            bRet = (  msCecCheckFeatureSupport_RemoteControlPassThrough()
                   && msCecCheckFeatureSupport_SystemAudioControl() );
            break;
        }


//----- Power Status  ----------------
        case E_MSG_PS_GIVE_DEVICE_POWER_STATUS:
        case E_MSG_PS_REPORT_POWER_STATUS:
        {
            bRet = msCecCheckFeatureSupport_GiveDevicePowerStatus();
            break;
        }


//----- System Audio Control ---------
        case E_MSG_SAC_GIVE_AUDIO_STATUS:
        case E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS:
        case E_MSG_SAC_REPORT_AUDIO_STATUS:
        case E_MSG_SAC_SET_SYSTEM_AUDIO_MODE:
        case E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST:
        case E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS:
      #if (ENABLE_DOLBY_BULLETIN24)
        case E_MSG_SAC_REPORT_SHORT_AUDIO_DESCRIPTOR:
        case E_MSG_SAC_REQUEST_SHORT_AUDIO_DESCRIPTOR:
      #endif
        {
            bRet = msCecCheckFeatureSupport_SystemAudioControl();
            break;
        }


//----- Audio Return Channel Control ----------------
        case E_MSG_ARC_INITIATE_ARC:
        case E_MSG_ARC_REPORT_ARC_INITIATED:
        case E_MSG_ARC_REPORT_ARC_TERMINATED:
        case E_MSG_ARC_REQUEST_ARC_INITIATION:
        case E_MSG_ARC_REQUEST_ARC_TERMINATION:
        case E_MSG_ARC_TERMINATE_ARC:
        {
            bRet = msCecCheckFeatureSupport_AudioReturnChannelControl();
            break;
        }


//----- General Protocol message ----------------
        case E_MSG_ABORT_MESSAGE:
        case E_MSG_FEATURE_ABORT:
        {
            bRet = msCecCheckFeatureSupport_GeneralProtocolMessageControl();
            break;
        }


//----- One Touch Record--------------
//----- Timer programmer -------------
//----- Deck Control Feature----------
//----- Tuner Control ----------------
//----- OSD Display ------------------
//----- Device Menu Control ----------
        default:    //not support opcode
        {
            bRet = FALSE;
            break;
        }

    }//switch end


    if ( bRet == FALSE )
    {
        CEC_MSG( printf("[CEC] msCecCheckFeatureSupport (0x%02X): %s \n",
                                    u8CecMsgOpcode, ((bRet)?("Yes"):("No"))) );
    }

    return bRet;
}


/******************************************************************************/

static void msCecPollingCustomer(void)
{
    // TO DO
}


/******************************************************************************/

/***********************
When TV receives unsupported opcode, or TV can not respond due to internal state,
it shall sent <Feature Abort>.
***********************/
static void msCecProcessGeneralProtocolMessage(MsCEC_DEVICELA dst_address,
                                               MsCEC_MSGLIST msg)
{
    MsCEC_MSG_ABORT_REASON cmd = E_MSG_AR_UNRECOGNIZE_OPCDE;

    switch (msg)
    {
        case E_MSG_UI_PRESS:
            cmd = E_MSG_AR_REFUSED;
            break;


        /***********************
        [Received message]: (Directly address) <Give System Audio Mode Status>
        [Abort Reason]    : Unrecognized opcode
        ***********************/
        case E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS:
            cmd = E_MSG_AR_UNRECOGNIZE_OPCDE;
            break;


        /***********************
        [Received message]: <Abort>
        [Abort Reason]    : Not in correct mode to respond
        ***********************/
        case E_MSG_SAC_SET_SYSTEM_AUDIO_MODE:
        case E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS:
            cmd = E_MSG_AR_CANNOTRESPOND;
            break;


        /***********************
        [Received message]: (Directly address) <Set System Audio Mode>
                            (Directly address) <System Audio Mode Status>
        [Abort Reason]    : Refused
        ***********************/
        case E_MSG_ABORT_MESSAGE:
            cmd = E_MSG_AR_REFUSED;
            break;

        /***********************
        [Received message]: unsupported message with directory address
        [Abort Reason]    : Unrecognized opcode
        ***********************/
        default:
            cmd = E_MSG_AR_UNRECOGNIZE_OPCDE;
            break;
    }

    msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, dst_address, msg, cmd);
}

/******************************************************************************/

static void msCecTransferIrKeyToString(MS_U8 keycode)
{
    switch ( (EN_KEY)keycode )
    {
        case KEY_CHANNEL_FAV_LIST:  CEC_DPUTSTR("[Fav List]");  break;
        case KEY_CHANNEL_RETURN:    CEC_DPUTSTR("[Return]");    break;
        case KEY_CHANNEL_PLUS:      CEC_DPUTSTR("[CH +]");      break;
        case KEY_CHANNEL_MINUS:     CEC_DPUTSTR("[CH -]");      break;

        case KEY_VOLUME_PLUS:       CEC_DPUTSTR("[Vol +]");     break;
        case KEY_VOLUME_MINUS:      CEC_DPUTSTR("[Vol -]");     break;
        case KEY_MUTE:              CEC_DPUTSTR("[Mute]");      break;

        case KEY_UP:                CEC_DPUTSTR("[Up]");        break;
        case KEY_DOWN:              CEC_DPUTSTR("[Down]");      break;
        case KEY_LEFT:              CEC_DPUTSTR("[Left]");      break;
        case KEY_RIGHT:             CEC_DPUTSTR("[Right]");     break;

        case KEY_POWER:             CEC_DPUTSTR("[Power]");     break;
        case KEY_INFO:              CEC_DPUTSTR("[Info]");      break;

        case KEY_MENU:              CEC_DPUTSTR("[Menu]");      break;
        case KEY_SELECT:            CEC_DPUTSTR("[Select]");    break;
        case KEY_EXIT:              CEC_DPUTSTR("[Exit]");      break;
        case KEY_BACK:              CEC_DPUTSTR("[Back]");      break;

        case KEY_0:                 CEC_DPUTSTR("[0]");         break;
        case KEY_1:                 CEC_DPUTSTR("[1]");         break;
        case KEY_2:                 CEC_DPUTSTR("[2]");         break;
        case KEY_3:                 CEC_DPUTSTR("[3]");         break;
        case KEY_4:                 CEC_DPUTSTR("[4]");         break;
        case KEY_5:                 CEC_DPUTSTR("[5]");         break;
        case KEY_6:                 CEC_DPUTSTR("[6]");         break;
        case KEY_7:                 CEC_DPUTSTR("[7]");         break;
        case KEY_8:                 CEC_DPUTSTR("[8]");         break;
        case KEY_9:                 CEC_DPUTSTR("[9]");         break;

        case KEY_PLAY:              CEC_DPUTSTR("[Play]");      break;
        case KEY_STOP:              CEC_DPUTSTR("[Stop]");      break;
        case E_MSG_UI_REWIND:       CEC_DPUTSTR("[Back]");      break;
        case E_MSG_UI_FAST_FORWARD: CEC_DPUTSTR("[Forward]");   break;
        case KEY_PAUSE:             CEC_DPUTSTR("[Pause]");     break;
        case KEY_NEXT:              CEC_DPUTSTR("[Next]");      break;
        case KEY_PREVIOUS:          CEC_DPUTSTR("[Previous]");  break;

        case KEY_BLUE:              CEC_DPUTSTR("[Blue]");      break;
        case KEY_RED:               CEC_DPUTSTR("[Red]");       break;
        case KEY_GREEN:             CEC_DPUTSTR("[Green]");     break;
        case KEY_YELLOW:            CEC_DPUTSTR("[Yellow]");    break;

        default:                    CEC_DPUTSTR("[xx]");        break;
    }

    CEC_MSG( printf("(0x%02X)", keycode) );
}

static void msCecTransferCecKeyToString(MS_U8 CECKey)
{
    switch ( (MsCEC_MSG_USER_CTRL_PARM)CECKey )
    {
        case E_MSG_UI_SELECT:           CEC_DPUTSTR("[Select]");        break;
        case E_MSG_UI_UP:               CEC_DPUTSTR("[Up]");            break;
        case E_MSG_UI_DOWN:             CEC_DPUTSTR("[Down]");          break;
        case E_MSG_UI_LEFT:             CEC_DPUTSTR("[Left]");          break;
        case E_MSG_UI_RIGHT:            CEC_DPUTSTR("[Right]");         break;
        case E_MSG_UI_ROOTMENU:         CEC_DPUTSTR("[Root Menu]");     break;
        case E_MSG_UI_CONTENTS_MENU:    CEC_DPUTSTR("[Contents Menu]"); break;
        case E_MSG_UI_FAVORITE_MENU:    CEC_DPUTSTR("[Fav Menu]");      break;
        case E_MSG_UI_EXIT:             CEC_DPUTSTR("[Exit]");          break;
        case E_MSG_UI_NUMBER_0:         CEC_DPUTSTR("[0]");             break;
        case E_MSG_UI_NUMBER_1:         CEC_DPUTSTR("[1]");             break;
        case E_MSG_UI_NUMBER_2:         CEC_DPUTSTR("[2]");             break;
        case E_MSG_UI_NUMBER_3:         CEC_DPUTSTR("[3]");             break;
        case E_MSG_UI_NUMBER_4:         CEC_DPUTSTR("[4]");             break;
        case E_MSG_UI_NUMBER_5:         CEC_DPUTSTR("[5]");             break;
        case E_MSG_UI_NUMBER_6:         CEC_DPUTSTR("[6]");             break;
        case E_MSG_UI_NUMBER_7:         CEC_DPUTSTR("[7]");             break;
        case E_MSG_UI_NUMBER_8:         CEC_DPUTSTR("[8]");             break;
        case E_MSG_UI_NUMBER_9:         CEC_DPUTSTR("[9]");             break;
        case E_MSG_UI_POWER:            CEC_DPUTSTR("[Power]");         break;
        case E_MSG_UI_VOLUME_UP:        CEC_DPUTSTR("[Vol +]");         break;
        case E_MSG_UI_VOLUME_DOWN:      CEC_DPUTSTR("[Vol -]");         break;
        case E_MSG_UI_MUTE:             CEC_DPUTSTR("[Mute]");          break;
        case E_MSG_UI_PLAY:             CEC_DPUTSTR("[Play]");          break;
        case E_MSG_UI_STOP:             CEC_DPUTSTR("[Stop]");          break;
        case E_MSG_UI_PAUSE:            CEC_DPUTSTR("[Pause]");         break;
        case E_MSG_UI_REWIND:           CEC_DPUTSTR("[Rewind]");        break;
        case E_MSG_UI_FAST_FORWARD:     CEC_DPUTSTR("[Fast Forward]");  break;
        case E_MSG_UI_FORWARD:          CEC_DPUTSTR("[Forward]");       break;
        case E_MSG_UI_BACKWARD:         CEC_DPUTSTR("[Backward]");      break;
        case E_MSG_UI_F1_BLUE:          CEC_DPUTSTR("[Blue]");          break;
        case E_MSG_UI_F2_RED:           CEC_DPUTSTR("[Red]");           break;
        case E_MSG_UI_F3_GREEN:         CEC_DPUTSTR("[Green]");         break;
        case E_MSG_UI_F4_YELLOW:        CEC_DPUTSTR("[Yellow]");        break;

        default:                        CEC_DPUTSTR("[xx]");            break;
    }

    CEC_MSG( printf("(0x%02X)", CECKey) );
}



static MsCEC_MSG_USER_CTRL_PARM msCecTransferIrKeyToCecKey(MS_U8 keycode)
{
    ST_CEC_IR_KEY_PAIR * stKeyMap = NULL;
    MS_U8 CECKey = 0xFF;
    MS_U16 u16TableIndex = 0;

    //Get customer key mapping
    stKeyMap = stCecKeyFromTvtoDevCustomerTable;

    for (u16TableIndex=0; (stKeyMap[u16TableIndex].CECKey != 0xFF); u16TableIndex++)
    {
        if (keycode == stKeyMap[u16TableIndex].keycode)
        {
            CECKey = stKeyMap[u16TableIndex].CECKey;
            break;
        }

        if (u16TableIndex >= 0xFF)
        {
            break;
        }
    }

    if (CECKey != 0xFF)
    {
        CEC_MSG( printf("\e[31;1;42m[CEC] Transfer IR: ") );
        msCecTransferIrKeyToString(keycode);
        CEC_MSG( printf(" -> CEC: ") );
        msCecTransferCecKeyToString(CECKey);
        CEC_MSG( printf("\e[m \n") );
    }
    else
    {
        CEC_MSG( printf("[CEC] transferIrKeyToCecKey 0x%02X -> 0x%02X\n", keycode, CECKey) );
    }

    return (MsCEC_MSG_USER_CTRL_PARM)CECKey;
}


//
/******************************************************************************/
//

static void msCecStateMachine_ARC_OFF2ON(void)
{
    EN_CEC_STATE_ARC_OFF2ON enState = _stCecStateInfoList.stState_ArcOff2On.enState;
//    INPUT_SOURCE_TYPE_t eInput = stSystemInfo[MAIN_WINDOW].enInputSourceType;

    if ( enState == CEC_ARC_OFF2ON_IDLE )
        return;

    switch (enState)
    {
        case CEC_ARC_OFF2ON_SEND_REQUEST_ARC_INITIATION:
        {
            if (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) == TRUE)
            {
                CEC_STATE_INFO( printf("\033[41;4m[CEC] ARC Off -> On <Request ARC Initiation> \033[0m \n") );

                msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);

                _stCecStateInfoList.stState_ArcOff2On.enState =
                    CEC_ARC_OFF2ON_WAIT_INITIATE_ARC;

                msCecSetStartTime(INTERVAL_CEC_FSM_ARC_Off2On) ;
            }
            else
            {
                _stCecStateInfoList.stState_ArcOff2On.enState =
                    CEC_ARC_OFF2ON_PROCESS_FINISH;
            }

            break;
        }

        case CEC_ARC_OFF2ON_WAIT_INITIATE_ARC:
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_ARC_Off2On) > INTERVAL_1_SECOND )
            {
                CEC_STATE_INFO( printf("\033[41;4m[CEC] ARC Off -> On : Wait <Initiate ARC> \033[0m \n") );
                CEC_STATE_INFO( printf("\033[41;4m      Over 1 second \033[0m \n") );

                msAPI_CEC_ARC_TX_Control(FALSE);
                MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);

                _stCecStateInfoList.stState_ArcOff2On.enState =
                    CEC_ARC_OFF2ON_PROCESS_FINISH;
            }
            break;

        case CEC_ARC_OFF2ON_PROCESS_FINISH:
            memset(&(_stCecStateInfoList.stState_ArcOff2On), 0, sizeof(ST_CEC_STATE_ARC_OFF2ON));
            _stCecStateInfoList.stState_ArcOff2On.enState = CEC_ARC_OFF2ON_IDLE;
            break;


        default :
            break;
    }
}

static void msCecStateMachine_ARC_ON2OFF(void)
{
    EN_CEC_STATE_ARC_ON2OFF enState = _stCecStateInfoList.stState_ArcOn2Off.enState;
//    INPUT_SOURCE_TYPE_t eInput = stSystemInfo[MAIN_WINDOW].enInputSourceType;

    if ( enState == CEC_ARC_ON2OFF_IDLE )
        return;

    switch (enState)
    {
        case CEC_ARC_ON2OFF_PROCESS_FINISH:
            memset(&(_stCecStateInfoList.stState_ArcOn2Off), 0, sizeof(ST_CEC_STATE_ARC_ON2OFF));
            _stCecStateInfoList.stState_ArcOn2Off.enState = CEC_ARC_ON2OFF_IDLE;
            break;


        default :
            break;
    }
}

static void msCecStateMachineCustomer(void)
{
    msCecStateMachine_ARC_OFF2ON();

    msCecStateMachine_ARC_ON2OFF();


    // TO DO
}

//
//**************************************************************************
//

void msAPI_CEC_GetCecFeatureSupport(ST_CEC_Feature_Support *CecFeatureSupport)
{
    memcpy(CecFeatureSupport, &stCecFeatureSupport, sizeof(ST_CEC_Feature_Support));

  #if 0
    CEC_FEATURE("\n[CEC] msAPI_CEC_GetCecFeatureSupport \n");
    CEC_FEATURE(" 6_2_OneTouchPlay = %d \n", CecFeatureSupport->bCECFeatureSupport_6_2_OneTouchPlay);
    CEC_FEATURE(" 6_3_RoutingControl = %d \n", CecFeatureSupport->bCECFeatureSupport_6_3_RoutingControl);
    CEC_FEATURE(" 6_4_SystemStandby = %d \n", CecFeatureSupport->bCECFeatureSupport_6_4_SystemStandby);
    CEC_FEATURE(" 6_5_SystemInformation = %d \n", CecFeatureSupport->bCECFeatureSupport_6_5_SystemInformation);
    CEC_FEATURE(" 6_6_VendorSpecificCommands = %d \n", CecFeatureSupport->bCECFeatureSupport_6_6_VendorSpecificCommands);
    CEC_FEATURE(" 6_7_DeviceOSDNameTransfer = %d \n", CecFeatureSupport->bCECFeatureSupport_6_7_DeviceOSDNameTransfer);
    CEC_FEATURE(" 6_8_RemoteControlPassThrough = %d \n", CecFeatureSupport->bCECFeatureSupport_6_8_RemoteControlPassThrough);
    CEC_FEATURE(" 6_9_GiveDevicePowerStatus = %d \n", CecFeatureSupport->bCECFeatureSupport_6_9_GiveDevicePowerStatus);
    CEC_FEATURE(" 6_10_SystemAudioControl = %d \n", CecFeatureSupport->bCECFeatureSupport_6_10_SystemAudioControl);
    CEC_FEATURE(" 6_11_AudioReturnChannelControl = %d \n", CecFeatureSupport->bCECFeatureSupport_6_11_AudioReturnChannelControl);
    CEC_FEATURE(" 6_12_GeneralProtocolMessageControl = %d \n", CecFeatureSupport->bCECFeatureSupport_6_12_GeneralProtocolMessageControl);
    CEC_FEATURE(" bCECFeatureSupport_ALL = %d \n", CecFeatureSupport->bCECFeatureSupport_ALL);
    CEC_FEATURE(" ======================================= \n\n");
  #endif
}

void msAPI_CEC_SetCecFeatureSupport(ST_CEC_Feature_Support *CecFeatureSupport)
{
    memcpy(&stCecFeatureSupport, CecFeatureSupport, sizeof(ST_CEC_Feature_Support));

  #if 0
    CEC_FEATURE("\n[CEC] msAPI_CEC_SetCecFeatureSupport \n");
    CEC_FEATURE(" 6_2_OneTouchPlay = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_2_OneTouchPlay);
    CEC_FEATURE(" 6_3_RoutingControl = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_3_RoutingControl);
    CEC_FEATURE(" 6_4_SystemStandby = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_4_SystemStandby);
    CEC_FEATURE(" 6_5_SystemInformation = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_5_SystemInformation);
    CEC_FEATURE(" 6_6_VendorSpecificCommands = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_6_VendorSpecificCommands);
    CEC_FEATURE(" 6_7_DeviceOSDNameTransfer = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_7_DeviceOSDNameTransfer);
    CEC_FEATURE(" 6_8_RemoteControlPassThrough = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_8_RemoteControlPassThrough);
    CEC_FEATURE(" 6_9_GiveDevicePowerStatus = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_9_GiveDevicePowerStatus);
    CEC_FEATURE(" 6_10_SystemAudioControl = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_10_SystemAudioControl);
    CEC_FEATURE(" 6_11_AudioReturnChannelControl = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_11_AudioReturnChannelControl);
    CEC_FEATURE(" 6_12_GeneralProtocolMessageControl = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_6_12_GeneralProtocolMessageControl);
    CEC_FEATURE(" bCECFeatureSupport_ALL = %d \n", stCecFeatureSupportCustomer.bCECFeatureSupport_ALL);
    CEC_FEATURE(" ======================================= \n\n");
  #endif
}

//
//**************************************************************************
//

void msAPI_CEC_ActionForCecOff(void)
{
    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == TRUE)
    {
        if ( msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) )
        {
            if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
            {
                msAPI_CEC_PostMsg_RequestARCTermination(DIRECTMSG, E_LA_AUDIO_SYS);
            }

          #if AMP_OFF_IF_CEC_OFF
            msAPI_CEC_TxMsgSystemAudioModeRequest(DIRECTMSG, FALSE);
          #else
            msAPI_CEC_TxMsgSystemAudioModeRequest(DIRECTMSG, TRUE);
          #endif
        }
    }
}


