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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MHL_H_
#define _MHL_H_

#include "Board.h"

#if (ENABLE_MHL == ENABLE)

#include "MsTypes.h"
#include "Enum_Device.h"

#if (MHL_TYPE == MHL_TYPE_NONE)
// Do Nothing
#elif (MHL_TYPE == MHL_TYPE_INTERNAL)
#include "apiMHL.h"
#elif (MHL_TYPE == MHL_TYPE_ELAND)
#include "apiMHL_ELAND.h"
#elif (MHL_TYPE == MHL_TYPE_SI)
#elif (MHL_TYPE == MHL_TYPE_SiI1292)
#else
#error "\r\nWrong MHL_TYPE!!!\r\n"
#endif // MHL_TYPE

#ifdef _MHL_H_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#if (MHL_TYPE == MHL_TYPE_INTERNAL)

#ifndef MHL_VBUS_OPTION
#define MHL_VBUS_OUTPUT_OPTION      0   // Vbus output mode
#define MHL_VBUS_INVERSE_OPTION     0   // Vbus inverse mode
#else
#if (MHL_VBUS_OPTION == MHL_VBUS_OUTPUT_MODE)
#define MHL_VBUS_OUTPUT_OPTION      1   // Vbus output mode
#define MHL_VBUS_INVERSE_OPTION     0   // Vbus inverse mode
#elif (MHL_VBUS_OPTION == MHL_VBUS_OUTPUT_INVERSE_MODE)
#define MHL_VBUS_OUTPUT_OPTION      0   // Vbus output mode
#define MHL_VBUS_INVERSE_OPTION     1   // Vbus inverse mode
#else //MHL_VBUS_DEFAULT_MODE
#define MHL_VBUS_OUTPUT_OPTION      0   // Vbus output mode
#define MHL_VBUS_INVERSE_OPTION     0   // Vbus inverse mode
#endif
#endif

#ifndef MHL_VBUS_SWITCH_PIN_CONTROL
#define MHL_VBUS_SWITCH_PIN_LOW_ENABLE      0
#define MHL_VBUS_SWITCH_PIN_HIGH_ENABLE     0
#else
#if (MHL_VBUS_SWITCH_PIN_CONTROL == MHL_VBUS_SWITCH_PIN_OUTPUT_LOW_ENABLE)
#define MHL_VBUS_SWITCH_PIN_LOW_ENABLE      1
#define MHL_VBUS_SWITCH_PIN_HIGH_ENABLE     0
#elif (MHL_VBUS_SWITCH_PIN_CONTROL == MHL_VBUS_SWITCH_PIN_OUTPUT_HIGH_ENABLE)
#define MHL_VBUS_SWITCH_PIN_LOW_ENABLE      0
#define MHL_VBUS_SWITCH_PIN_HIGH_ENABLE     1
#else //MHL_VBUS_SWITCH_PIN_INPUT
#define MHL_VBUS_SWITCH_PIN_LOW_ENABLE      0
#define MHL_VBUS_SWITCH_PIN_HIGH_ENABLE     0
#endif
#endif
#define MHL_USER_DEVICE_CAPABILITY  0   // User define device capacibility
#define MHL_READ_DEVICE_CAPABILITY  0   // Read source device capacibility
#define MHL_READ_DEVICE_VENDER_ID   0   // Read source device vender ID


#define MHL_ADOPTER_ID              0x02CB
#define MHL_DEVICE_ID               0x0000
#define MHL_RCP_SUPPORT             1
#define MHL_RAP_SUPPORT             1

#define MHL_DEVICE_CAPABILITY_SIZE  16

#if(MHL_USER_DEVICE_CAPABILITY)
//-------------------------------------------------------------------------------------------------
//  Default device capacibility
//-------------------------------------------------------------------------------------------------
#define MHL_DEVICE_STATE            0x00
#define MHL_VER_MAJOR               2
#define MHL_VER_MINOR               1
#define MHL_DEVICE_TYPE             1
#define MHL_DEVICE_POW              1
#define MHL_DEVICE_PLIM             1 // 0: 500mA / 1: 900mA / 2: 1.5A
#define MHL_SUPP_RGB444             1
#define MHL_SUPP_YCBCR444           1
#define MHL_SUPP_YCBCR422           1
#define MHL_SUPP_PPIXEL             1
#define MHL_SUPP_ISLANDS            1
#define MHL_SUPP_VGA                1
#define MHL_AUD_2CH                 1
#define MHL_AUD_8CH                 0
#define MHL_VT_GRAPHICS             0
#define MHL_VT_PHOTO                0
#define MHL_VT_CINEMA               0
#define MHL_VT_GAME                 0
#define MHL_SUPP_VT                 0
#define MHL_LD_DISPLAY              1
#define MHL_LD_VIDEO                0
#define MHL_LD_AUDIO                0
#define MHL_LD_MEDIA                0
#define MHL_LD_TUNER                0
#define MHL_LD_RECORD               0
#define MHL_LD_SPEAKER              0
#define MHL_LD_GUI                  0
#define MHL_BANDWIDTH               0x0F
#define MHL_SP_SUPPORT              1
#define MHL_UCP_SEND_SUPPORT        0
#define MHL_UCP_RECV_SUPPORT        0
#define MHL_SCRATCHPAD_SIZE         0x10
#define MHL_INT_SIZE                3
#define MHL_STATE_SIZE              3

#define MHL_DEV_STATE_0x00          MHL_DEVICE_STATE
#define MHL_VERSION_0x01            (MHL_VER_MINOR |(MHL_VER_MAJOR <<4))
#define MHL_DEV_CAT_0x02            (MHL_DEVICE_TYPE |(MHL_DEVICE_POW <<4) |(MHL_DEVICE_PLIM <<5))
#define MHL_ADOPTER_ID_H_0x03       (MHL_ADOPTER_ID >>8)
#define MHL_ADOPTER_ID_L_0x04       (MHL_ADOPTER_ID &0xFF)
#define MHL_VID_LINK_MODE_0x05      (MHL_SUPP_RGB444 |(MHL_SUPP_YCBCR444 <<1) |(MHL_SUPP_YCBCR422 <<2) |(MHL_SUPP_PPIXEL <<3) |(MHL_SUPP_ISLANDS <<4) |(MHL_SUPP_VGA <<5))
#define MHL_AUD_LINK_MODE_0x06      (MHL_AUD_2CH |(MHL_AUD_8CH <<1))
#define MHL_VIDEO_TYPE_0x07         (MHL_VT_GRAPHICS |(MHL_VT_PHOTO <<1) |(MHL_VT_CINEMA <<2) |(MHL_VT_GAME <<3) |(MHL_SUPP_VT <<7))
#define MHL_LOG_DEV_MAP_0x08        (MHL_LD_DISPLAY |(MHL_LD_VIDEO <<1) |(MHL_LD_AUDIO <<2) |(MHL_LD_MEDIA <<3) |(MHL_LD_TUNER <<4) |(MHL_LD_RECORD <<5) |(MHL_LD_SPEAKER <<6) |(MHL_LD_GUI <<7))
#define MHL_BANDWIDTH_0x09          MHL_BANDWIDTH
#define MHL_FEATURE_FLAG_0x0A       (MHL_RCP_SUPPORT |(MHL_RAP_SUPPORT <<1) |(MHL_SP_SUPPORT <<2) |(MHL_UCP_SEND_SUPPORT <<3) |(MHL_UCP_RECV_SUPPORT <<4))
#define MHL_DEVICE_ID_H_0x0B        (MHL_DEVICE_ID >>8)
#define MHL_DEVICE_ID_L_0x0C        (MHL_DEVICE_ID &0xFF)
#define MHL_SCRATCHPAD_SIZE_0x0D    MHL_SCRATCHPAD_SIZE
#define MHL_INT_STAT_0x0E           (MHL_INT_SIZE |(MHL_STATE_SIZE <<4))

#else

#define MHL_DEV_STATE_0x00          0x00
#define MHL_VERSION_0x01            0x21
#define MHL_DEV_CAT_0x02            0x31
#define MHL_ADOPTER_ID_H_0x03       (MHL_ADOPTER_ID >>8)
#define MHL_ADOPTER_ID_L_0x04       (MHL_ADOPTER_ID &0xFF)
#define MHL_VID_LINK_MODE_0x05      0x3F
#define MHL_AUD_LINK_MODE_0x06      0x01
#define MHL_VIDEO_TYPE_0x07         0x00
#define MHL_LOG_DEV_MAP_0x08        0x01
#define MHL_BANDWIDTH_0x09          0x0F
#define MHL_FEATURE_FLAG_0x0A       0x07
#define MHL_DEVICE_ID_H_0x0B        (MHL_DEVICE_ID >>8)
#define MHL_DEVICE_ID_L_0x0C        (MHL_DEVICE_ID &0xFF)
#define MHL_SCRATCHPAD_SIZE_0x0D    0x10
#define MHL_INT_STAT_0x0E           0x33
#endif // #if(MHL_USER_DEVICE_CAPABILITY)

#if(MHL_READ_DEVICE_CAPABILITY)
//-------------------------------------------------------------------------------------------------
//  Read device capacibility
//-------------------------------------------------------------------------------------------------
#define MHL_READ_DEVCAP_0x00        0   // Device state
#define MHL_READ_DEVCAP_0x01        0   // MHL version
#define MHL_READ_DEVCAP_0x02        0   // Device category
#define MHL_READ_DEVCAP_0x03        0   // Adopter ID high byte
#define MHL_READ_DEVCAP_0x04        0   // Adopter ID low byte
#define MHL_READ_DEVCAP_0x05        0   // Video link mode support
#define MHL_READ_DEVCAP_0x06        0   // Audio link mode support
#define MHL_READ_DEVCAP_0x07        0   // Video type support
#define MHL_READ_DEVCAP_0x08        0   // Logical device map
#define MHL_READ_DEVCAP_0x09        0   // Link bandwidth limit
#define MHL_READ_DEVCAP_0x0A        1   // Feature flags
#define MHL_READ_DEVCAP_0x0B        0   // Device ID high byte
#define MHL_READ_DEVCAP_0x0C        0   // Device ID low byte
#define MHL_READ_DEVCAP_0x0D        0   // Scratchpad size
#define MHL_READ_DEVCAP_0x0E        0   // Interrupt /status size
#define MHL_READ_DEVCAP_0x0F        0   // Reserved

#define MHL_READ_DEVCAP_L           (MHL_READ_DEVCAP_0x00 |(MHL_READ_DEVCAP_0x01 <<1) |(MHL_READ_DEVCAP_0x02 <<2) |(MHL_READ_DEVCAP_0x03 <<3)\
                                    |(MHL_READ_DEVCAP_0x04 <<4) |(MHL_READ_DEVCAP_0x05 <<5) |(MHL_READ_DEVCAP_0x06 <<6) |(MHL_READ_DEVCAP_0x07 <<7))
#define MHL_READ_DEVCAP_H           (MHL_READ_DEVCAP_0x08 |(MHL_READ_DEVCAP_0x09 <<1) |(MHL_READ_DEVCAP_0x0A <<2) |(MHL_READ_DEVCAP_0x0B <<3)\
                                    |(MHL_READ_DEVCAP_0x0C <<4) |(MHL_READ_DEVCAP_0x0D <<5) |(MHL_READ_DEVCAP_0x0E <<6) |(MHL_READ_DEVCAP_0x0F <<7))
#define MHL_READ_DEVCAP_MASK        (MHL_READ_DEVCAP_L |(MHL_READ_DEVCAP_H << 8))

#endif // #if(MHL_READ_DEVICE_CAPABILITY)

#define MHL_VBUS_OPTION_STATE       (MHL_VBUS_INVERSE_OPTION |(MHL_VBUS_OUTPUT_OPTION <<1) |(MHL_VBUS_SWITCH_PIN_LOW_ENABLE <<2) |(MHL_VBUS_SWITCH_PIN_HIGH_ENABLE <<3))

#endif // #if (MHL_TYPE == MHL_TYPE_INTERNAL)

//////////////////////////////////////////////////
//        Application New Function Switch       //
//////////////////////////////////////////////////
#define MHL_TV_DC_OFF_BEHAVIOR_TV_BACK_TO_NORMAL_ON                 1 //Let TV goes from DC off to normal on when mobile phone plug in
#define MHL_INPUT_SOURCE_AUTO_SWITCH            1 //auto swtich input source when mobile plugin


void msAPI_MHL_Initialization(void);
void msAPI_MHL_Handler(MS_U8 ucCurrentPortType);
void msAPI_MHL_SourceChange(MS_U8 ucCurrentPortType);
MS_BOOL msAPI_MHL_SendRCP_PressRelease_Cmd(MS_U8 u8RCPKey, MS_BOOL bIsRelease);
MS_BOOL msAPI_MHL_SendRCPAutoReleaseCmd(MS_U8 u8RCPKey);
MS_BOOL msAPI_MHL_SendRAPCmd(MS_U8 databuf);
MS_BOOL msAPI_MHL_CableDetect(void);
MS_BOOL msAPI_MHL_IsCbusConnected(void);
void msAPI_MHL_MHLSupportPath(MS_U8 ucSelect);
void msAPI_MHL_CbusIsolate(void);
void msAPI_MHL_CbusControl(MS_U8 ucState);
void msAPI_MHL_PowerCtrl(E_MHL_POWERCTRL_Mode pctrl);
void msAPI_MHL_CbusWakeupIntSetting(void);
void msAPI_MHL_TV_DC_off(void);

#if (MHL_TYPE == MHL_TYPE_INTERNAL)
#if(MHL_READ_DEVICE_CAPABILITY)
MS_BOOL msAPI_MHL_GetSourceDevCap(MS_U8 u8DevCapIdx, MS_U8* u8DevCapData);
#endif

#if(MHL_READ_DEVICE_VENDER_ID)
MS_BOOL msAPI_MHL_GetSourceVenderID(MS_U8* u8VenderIDData);
#endif

#endif // #if (MHL_TYPE == MHL_TYPE_INTERNAL)

#endif

#undef INTERFACE

#endif
