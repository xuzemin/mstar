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
//////////////////////////////////////////////////////////////////////////////
/// @file MsSystemData.h
/// @brief Initialize HW, memory pool & API.
/// @author MStar Semiconductor Inc.
/// Description: Initialize HW, memory pool & API.
//////////////////////////////////////////////////////////////////////////////
#ifndef _MS_SYSTEM_DATA_H
#define _MS_SYSTEM_DATA_H
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "datatype.h"

#define MAX_NET_PASSWORD_LEN 32
//---------------------------------------------------------------------------
//  Include file
//---------------------------------------------------------------------------

typedef struct __attribute__ ((aligned (4))){
    //protocol version
    U8        protocol_ver_major;
    U8        protocol_ver_minor;

    //client
    U16       u16_client_width;
    U16       u16_client_height;
    U8        u8_fmt;
    U8        b_stretch;
    U8        b_uart_in_aeon;
    U8        b_usb_in_cape;
    U8        b_enable_transclr;
    U8        b_waitfor_init;  //for DLNA, (BT)
    U8        b_need_monitor_alive;  //for APs with no exit key
    U8        b_audio_in_cape;  //for APs do not need sound support

} MS_INIT_DATA_T;

typedef struct __attribute__ ((aligned (4))){
    U32 u32XTAL_RTC_CLOCK_FREQ;
    U32 u32XTAL_CLOCK_FREQ;

    U16 u16PANEL_TYPE_SEL;
    U8  u8INPUT_AV_VIDEO_COUNT;
    U8  u8INPUT_SV_VIDEO_COUNT;

    U8  u8INPUT_YPBPR_VIDEO_COUNT;
    U8  u8INPUT_SCART_VIDEO_COUNT;
    U8  u8ENABLE_HDMI;
    U8  u8MEMORY_MAP;

    U16 u16MOD_LVDS_GPIO;
    U8  u8DRAM_TYPE;
    U8  u8DRAM_CHIP;

    U8  u8PANEL_CONNECTOR_SWAP_LVDS_CH;
    U8  u8PANEL_CONNECTOR_SWAP_LVDS_POL;
    U8  u8PANEL_CONNECTOR_SWAP_PORT;
    U8  u8ETHNET_PHY_TYPE;

} MS_BOARD_T;

typedef struct __attribute__ ((aligned (4))){
    U16 u16PANEL_WIDTH;
    U16 u16PANEL_HEIGHT;
    U8  u8Reserved[86];  /* This field is for old panel settings(86 bytes).
                            For the alignment to the information to cape,
                            these 86 bytes should be reserved to agree with the cape side.
                            If any byte should be padded, please make this structure identical to the cape side.*/

} MS_PANEL_T;

typedef struct __attribute__ ((aligned (4))){
    U8  u8Network_SetFlag;//0:Not Used;1:Used
    U8  u8Net_Addr_Class_A;//Address_0
    U8  u8Net_Addr_Class_B;//Address_1
    U8  u8Net_Addr_Class_C;//Address_2
    U8  u8Net_Addr_Class_D;//Address_3

} MS_NET_ADDRESS_T;

typedef struct __attribute__ ((aligned (4))){
    U8  u8Network_SetFlag; //0:Not Used;1:Used
    U8  u8Net_Addr_Class_A;//Address_0
    U8  u8Net_Addr_Class_B;//Address_1
    U8  u8Net_Addr_Class_C;//Address_2
    U8  u8Net_Addr_Class_D;//Address_3
    U16 u16Net_Addr_Port;

} MS_PROXY_ADDRESS_T;

typedef struct __attribute__ ((aligned (4))){

    U8 u8Network_SetFlag;  //0:Not Used;1:Used
    U8 u8MANUFACTURE_ID_1;
    U8 u8MANUFACTURE_ID_2;
    U8 u8MANUFACTURE_ID_3;
    U8 u8NETWORK_CARD_ID_1;
    U8 u8NETWORK_CARD_ID_2;
    U8 u8NETWORK_CARD_ID_3;

} MS_MAC_ADDRESS_T;

typedef struct __attribute__ ((aligned (4))){
    U8                  bNet_Config_mode;//0:Static IP;1:DHCP
    U8                  NetProxy_PassWord[MAX_NET_PASSWORD_LEN];
    U8                  NetProxy_UserName[MAX_NET_PASSWORD_LEN];
    MS_NET_ADDRESS_T    g_NetIP;
    MS_NET_ADDRESS_T    g_NetNetmask;
    MS_NET_ADDRESS_T    g_NetGateway;
    MS_NET_ADDRESS_T    g_NetDNS;
    MS_PROXY_ADDRESS_T  g_NetProxy;
    MS_MAC_ADDRESS_T    g_NetMacAddress;

} MS_NETWORK_T;

typedef struct __attribute__ ((aligned (4))){
    U32             u32_on_screen_buffer_addr;
    U32             u32_off_screen_buffer_addr;
    U32             Rom_addr;   // david,  Just a work around,
    MS_BOARD_T      msBoard;
    MS_PANEL_T      msPanel;
    MS_NETWORK_T    msNetwork;
    U32             msBaseSec;
    U8              msGOP_GWIN;
    U32             u32_miu_shift;
    U32             u32_rom_file_length;

} MS_SYSTEM_DATA_T;

extern MS_INIT_DATA_T* MApi_SystemInit_GetMsInitData(void);
extern MS_SYSTEM_DATA_T* MApi_SystemInit_GetMsSystemData(void);
extern MS_BOARD_T* MApi_SystemInit_GetMsBoard(void);
extern MS_PANEL_T* MApi_SystemInit_GetMsPanel(void);
extern MS_NETWORK_T* MApi_SystemInit_GetMsNetwork(void);
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  // _MS_SYSTEM_DATA_H

