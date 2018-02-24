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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _API_XC_HDMI_H_
#define _API_XC_HDMI_H_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
//#include "msAPI_Mode.h"

#include "drvXC_HDMI_if.h"


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define HDMI_POLLING_COUNTER   (30)    // 30 ms

#define DEBUG_HDMI_HOT_PLUG(x)  //x

#define DEBUG_HDMI_COLOR(x)     //x

#define HDMI_COLOR_CHANGE_NO_MODE_CHANGE    1

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_XC_HDMI_FAIL = 0,
    E_XC_HDMI_OK = 1,
    E_XC_HDMI_GET_BASEADDR_FAIL,            ///< get base address failed when initialize panel driver
    E_XC_HDMI_OBTAIN_MUTEX_FAIL,            ///< obtain mutex timeout when calling this function
} XC_HDMI_Result;

typedef enum
{
    E_HDMI_STATUS_UNKNOWN,
    E_HDMI_STATUS_DVI,
    E_HDMI_STATUS_HDMI,
} E_XC_HDMI_Status;

typedef struct
{
    MS_U8   *pu8HDCP_Key;       ///< 289 bytes HDCP Key
    MS_BOOL bHotPlugInverse[4]; ///< hot plug pin inverse or not
} XC_HDMI_InitData;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

extern HDMI_PACKET_INFO_t       g_HdmiPacketInfo;

// Init
XC_HDMI_Result MApi_XC_HDMI_Init(XC_HDMI_InitData *pstXC_HDMI_InitData, MS_U32 u32InitDataLen);
void MApi_XC_HDMI_Handler_Init(void);

// Switch Src
void MApi_XC_DVI_SwitchSrc( E_MUX_INPUTPORT enInputPortType );
U16 MApi_XC_HDMI_Func_Caps(void);

void _MDrv_HDMI_audio_downsample(void);

// HPD control
void MApi_XC_HDMI_SetHotPlug(MS_BOOL bEnable, E_MUX_INPUTPORT enInputPortType);             ///< ENABLE: high, DISABLE: low
void MApi_XC_HDMI_SetDVIClkPullLow(MS_BOOL bPullLow, E_MUX_INPUTPORT enInputPortType);      ///< TRUE: pull low, FALSE: pull high

// HDCP
void MApi_XC_HDCP_Init(MS_U8 *pu8HDCP_Key);
void MApi_XC_HDCP_Status_Reset(void);
void MApi_XC_HDCP_Enable(MS_BOOL bEnable);

void MApi_XC_HDMI_CheckAndAdjustDVI(INPUT_SOURCE_TYPE_t InputSourceType);

E_XC_HDMI_Status MApi_XC_HDMI_GetHdmiType(INPUT_SOURCE_TYPE_t enInputSourceType);
BOOLEAN MApi_XC_HDMI_Monitor(INPUT_SOURCE_TYPE_t enInputSourceType);
BOOLEAN MApi_XC_HDMI_CheckModeChanged(BOOLEAN bImmediately, SCALER_WIN eWindow);

void MApi_XC_HDCP_Vsync_end_en(MS_BOOL bStable);

void MApi_XC_HDMI_CheckPacketInfo(void);
const HDMI_PACKET_INFO_t *MApi_XC_HDMI_GetPacketInfo(void);
BOOLEAN MApi_XC_HDMI_CheckSumAndBCH(INPUT_SOURCE_TYPE_t enInputSourceType);

void MApi_XC_HDMI_Task(void);

#if ENABLE_EDID_SWITCH
#define DEBUG_EDID_SWITCH(x)    //x

BOOLEAN MApi_XC_HDMI_EDID_Monitor(void);
void MApi_XC_HDMI_EdidSwitch_ResetSM(void);
#endif

char* MApi_HDMI_Get_ColorFormatString(U8 u8ColorFormat);

void MApi_XC_HDMI_Reset_Packet_State_Variable(void);

//=======================================================================
typedef enum
{
    HDMI_HPD_STATUS_LOW,
    HDMI_HPD_STATUS_HIGH,
    HDMI_HPD_STATUS_UNKNOWN,
} EnuHdmiHpdStatus;

typedef enum
{
    HDMI_CLK_STATUS_LOW,
    HDMI_CLK_STATUS_HIGH,
    HDMI_CLK_STATUS_UNKNOWN,
} EnuHdmiClkStatus;

void MApi_XC_HDMI_InitVar_PortStatus(void);
void MApi_XC_HDMI_Set_HpdStatus(E_MUX_INPUTPORT enInputPortType, EnuHdmiHpdStatus eHpdStatus);
EnuHdmiHpdStatus MApi_XC_HDMI_Get_HpdStatus(E_MUX_INPUTPORT enInputPortType);

void MApi_XC_HDMI_Set_ClkStatus(E_MUX_INPUTPORT enInputPortType, EnuHdmiClkStatus eClkStatus);

void MApi_XC_HDMI_Print_PortStatus(void);
//========================================================================


#undef INTERFACE
#endif /* _API_XC_HDMI_H_ */
