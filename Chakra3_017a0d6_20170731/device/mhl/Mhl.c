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


#ifndef _MHL_C_
#define _MHL_C_

#include "Board.h"

#if (ENABLE_MHL == ENABLE)


#include "Mhl.h"
#include "Enum_Device.h"

#include "msAPI_MHL.h"
#include "MApp_GlobalVar.h"

#if MHL_INPUT_SOURCE_AUTO_SWITCH
#include "MApp_ZUI_Main.h"
#include "MApp_InputSource.h"
#include "MApp_TopStateMachine.h"
#if (ENABLE_DMP)
#include "mapp_mplayer.h"
#endif
#endif
#include "MApp_TopStateMachine.h"
#include "MApp_ChannelChange.h"
#include "MApp_GlobalFunction.h"

#ifndef MHL_TYPE
#define MHL_TYPE MHL_TYPE_NONE
#endif

#if (MHL_TYPE == MHL_TYPE_NONE)
// Do Nothing
#elif (MHL_TYPE == MHL_TYPE_INTERNAL)
#include "apiMHL.h"
#elif (MHL_TYPE == MHL_TYPE_ELAND)
#include "apiMHL_ELAND.h"
#elif (MHL_TYPE == MHL_TYPE_SI)
#elif (MHL_TYPE == MHL_TYPE_SiI1292)
#include "../SiI1292/MAIN/si_cp1292.h"
#include "msAPI_Timer.h"
#else
#error "\r\nWrong MHL_TYPE!!!\r\n"
#endif // MHL_TYPE


#if ((MHL_TYPE == MHL_TYPE_ELAND) || (MHL_TYPE == MHL_TYPE_SI) || (MHL_TYPE == MHL_TYPE_SiI1292))
#include "drvIIC.h"
#include "drvGPIO.h"
#include "msAPI_Timer.h"
#endif

#if ((MHL_TYPE == MHL_TYPE_INTERNAL) || (MHL_TYPE == MHL_TYPE_ELAND))
static MS_U8 MStar_MHL_EDID[256] =
{
    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x36,0x74,0x30,0x00,0x01,0x00,0x00,0x00,
    0x18,0x0F,0x01,0x03,0x80,0x73,0x41,0x78,0x0A,0xCF,0x74,0xA3,0x57,0x4C,0xB0,0x23,
    0x09,0x48,0x4C,0x00,0x00,0x00,0x01,0x01,0x01,0xFF,0x01,0xFF,0xFF,0x01,0x01,0x01,
    0x01,0x01,0x01,0x01,0x01,0x20,0x01,0x1D,0x80,0x3E,0x73,0x38,0x2D,0x40,0x7E,0x2C,
    0x45,0x80,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x01,0x1D,0x00,0x72,0x51,0xD0,0x1E,0x20,
    0x6E,0x28,0x55,0x00,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFC,0x00,0x4D,
    0x53,0x74,0x61,0x72,0x20,0x44,0x65,0x6D,0x6F,0x0A,0x20,0x20,0x00,0x00,0x00,0xFD,
    0x00,0x3B,0x3C,0x1F,0x2D,0x08,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x01,0x64,
    0x02,0x03,0x1F,0xF2,0x4C,0x05,0x04,0x03,0x02,0x01,0x12,0x13,0x14,0x16,0x07,0xA2,
    0xA0,0x23,0x09,0x07,0x07,0x83,0x01,0x00,0x00,0x65,0x03,0x0C,0x00,0x10,0x00,0x8C,
    0x0A,0xD0,0x8A,0x20,0xE0,0x2D,0x10,0x10,0x3E,0x96,0x00,0xC4,0x8E,0x21,0x00,0x00,
    0x18,0x8C,0x0A,0xA0,0x14,0x51,0xF0,0x16,0x00,0x26,0x7C,0x43,0x00,0xC4,0x8E,0x21,
    0x00,0x00,0x99,0x01,0x1D,0x00,0xBC,0x52,0xD0,0x1E,0x20,0xB8,0x28,0x55,0x40,0xC4,
    0x8E,0x21,0x00,0x00,0x1F,0x01,0x1D,0x80,0xD0,0x72,0x1C,0x16,0x20,0x10,0x2C,0x25,
    0x80,0xC4,0x8E,0x21,0x00,0x00,0x9E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,
};
#endif

MS_U8 tMHL_DEVICE_CAPABILITY_TABLE[MHL_DEVICE_CAPABILITY_SIZE] =
{
    MHL_DEV_STATE_0x00,    //DEV_STATE
    MHL_VERSION_0x01,    //MHL_VERSION
    MHL_DEV_CAT_0x02,    //DEV_CAT, [4]:POW, [3:0]:DEV_TYPE
    MHL_ADOPTER_ID_H_0x03,    // ADOPTER_ID_H, Mstar adopter ID 715(0x2CB)
    MHL_ADOPTER_ID_L_0x04,    // ADOPTER_ID_L
    MHL_VID_LINK_MODE_0x05,    // VID_LINK_MODE, [5]:SUPP_VGA, [4]:ISLANDS, [3]:PPIXEL, [2]:YUV422, [1]:YUV444, [0]:RGB444
    MHL_AUD_LINK_MODE_0x06,    // AUD_LINK_MODE, [1]:AUD_8CH, [0]:AUD_2CH
    MHL_VIDEO_TYPE_0x07,    // VIDEO_TYPE, [7]: SUPP_VT, [3]:GAME, [2]:CINEMA, [1]: PHOTO, [0]:GRAPHICS
    MHL_LOG_DEV_MAP_0x08,    // LOG_DEV_MAP, [0]:LD_DISPLAY
    MHL_BANDWIDTH_0x09,    // BANDWIDTH, 15*5MHz = 75MHz
    MHL_FEATURE_FLAG_0x0A,    // FEATURE_FLAG, [2]:Scratchpad, [1]:RAP, [0]:RCP
    MHL_DEVICE_ID_H_0x0B,    // DEVICE_ID_H, ? CHIP_ID
    MHL_DEVICE_ID_L_0x0C,    // DEVICE_ID_L, ? CHIP_ID
    MHL_SCRATCHPAD_SIZE_0x0D,    // SCRATCHPAD_SIZE, 16 bytes
    MHL_INT_STAT_0x0E,    // INT_STAT_SIZE, [7:4]:Status 4 bytes, [3:0]:Interrupt 4 bytes
    0x00,    // Reserved
};

#if (MHL_TYPE == MHL_TYPE_INTERNAL)
//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#if(MHL_READ_DEVICE_CAPABILITY)
static MS_BOOL sg_bSourceDevCapReadyFlag = FALSE;
static MS_U8 sg_u8SourceDevCapData[MHL_DEVICE_CAPABILITY_SIZE];
#endif

#if(MHL_READ_DEVICE_VENDER_ID)
static MS_BOOL sg_bSourceVenderIDReadyFlag = FALSE;
static MS_U8 sg_u8SourceVenderID = 0;
#endif

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
void _msAPI_MHL_ReadDeviceInformation(void)
{
    if(mapi_mhl_CbusStatus())
    {
        mapi_mhl_Send3DInformation();

#if(MHL_READ_DEVICE_VENDER_ID)
        if(mapi_mhl_GetDeviceVenderID(&sg_u8SourceVenderID))
        {
            sg_bSourceVenderIDReadyFlag = TRUE;

            printf("** MHL get vender ID = 0x%x\n", sg_u8SourceVenderID);
        }
#endif

#if(MHL_READ_DEVICE_CAPABILITY)
        if(mapi_mhl_GetDeviceCapacibility(MHL_READ_DEVCAP_MASK, &sg_u8SourceDevCapData[0]))
        {
            MS_U8 uctemp = 0;

            sg_bSourceDevCapReadyFlag = TRUE;

            for(uctemp = 0; uctemp < MHL_DEVICE_CAPABILITY_SIZE; uctemp++)
            {
                printf("** MHL get device capability = 0x%x\n", sg_u8SourceDevCapData[uctemp]);
            }
        }
#endif
    }
    else
    {
#if(MHL_READ_DEVICE_VENDER_ID)
        sg_bSourceVenderIDReadyFlag = FALSE;
#endif

#if(MHL_READ_DEVICE_CAPABILITY)
        sg_bSourceDevCapReadyFlag = FALSE;
#endif
    }
}

#if(MHL_READ_DEVICE_CAPABILITY)
MS_BOOL msAPI_MHL_GetSourceDevCap(MS_U8 u8DevCapIdx, MS_U8* u8DevCapData)
{
    if(sg_bSourceDevCapReadyFlag == TRUE)
    {
        *u8DevCapData = sg_u8SourceDevCapData[u8DevCapIdx];
    }
    else
    {
        printf("Source Device Capability is not read\r\n");
        *u8DevCapData = 0;
    }

    return sg_bSourceDevCapReadyFlag;
}
#endif

#if(MHL_READ_DEVICE_VENDER_ID)
MS_BOOL msAPI_MHL_GetSourceVenderID(MS_U8* u8VenderIDData)
{
    if(sg_bSourceVenderIDReadyFlag == TRUE)
    {
        *u8VenderIDData = sg_u8SourceVenderID;
    }
    else
    {
        printf("Source vender ID is not read\r\n");
        *u8VenderIDData = 0;
    }

    return sg_bSourceVenderIDReadyFlag;
}
#endif

#endif // #if (MHL_TYPE == MHL_TYPE_INTERNAL)

#if (MHL_TYPE == MHL_TYPE_NONE)
BOOLEAN msAPI_MHL_IsCbusConnected(void)
{
    // Always return false to skip MHL function;
    return FALSE;
}

void msAPI_MHL_Initialization(void)
{
    printf("\r\nMHL Init, MHL_TYPE = 0x%x\r\n", MHL_TYPE);
    //Do Nothing;
}

void msAPI_MHL_Handler(MS_U8 ucCurrentPortType)
{
    //Do Nothing;
    ucCurrentPortType = ucCurrentPortType;
}

void msAPI_MHL_SourceChange(MS_U8 ucCurrentPortType)
{
    //Do Nothing;
    ucCurrentPortType = ucCurrentPortType;
}

void msAPI_MHL_TV_DC_off(void)
{
    //Do Nothing;
}

MS_BOOL msAPI_MHL_SendRCP_PressRelease_Cmd(MS_U8 u8RCPKey, MS_BOOL bIsRelease)
{
    u8RCPKey = u8RCPKey;
    bIsRelease = bIsRelease;
    // Always return false to skip MHL function;
    return FALSE;
}

MS_BOOL msAPI_MHL_SendRCPAutoReleaseCmd(MS_U8 u8RCPKey)
{
    u8RCPKey = u8RCPKey;
    // Always return false to skip MHL function;
    return FALSE;
}


MS_BOOL msAPI_MHL_SendRAPCmd(MS_U8 databuf)
{
    databuf = databuf;
    // Always return false to skip MHL function;
    return FALSE;
}

#elif (MHL_TYPE == MHL_TYPE_INTERNAL)
BOOLEAN msAPI_MHL_IsCbusConnected(void)
{
    return mapi_mhl_CbusStatus();
}

void msAPI_MHL_MHLSupportPath(MS_U8 ucSelect)
{
    mapi_mhl_MHLSupportPath(ucSelect);
}

void msAPI_MHL_Initialization(void)
{
    printf("\r\nMHL Init, MHL_TYPE = 0x%x\r\n", MHL_TYPE);

    // MHL Init
    mapi_mhl_init(MStar_MHL_EDID, tMHL_DEVICE_CAPABILITY_TABLE);

    mapi_mhl_RegisterCallBackFunctions(msAPI_MHL_CbusRcpProcess, msAPI_MHL_CbusRapProcess);

#if(MHL_VBUS_OPTION_STATE > 0)
    mapi_mhl_VbusConfigSetting(MHL_VBUS_OPTION_STATE);
#endif

#if(MHL_READ_DEVICE_CAPABILITY) //patch timing problem
    mapi_mhl_GetDeviceCapacibility(MHL_READ_DEVCAP_MASK, &sg_u8SourceDevCapData[0]);
#endif
}

void msAPI_MHL_Handler(MS_U8 ucCurrentPortType)
{
#if MHL_INPUT_SOURCE_AUTO_SWITCH
        MS_U8 ucMHLInputSourcePort;
#endif

    if((ucCurrentPortType < UI_INPUT_SOURCE_HDMI) || (UI_INPUT_SOURCE_HDMI_END <= ucCurrentPortType))
    {
        mapi_mhl_CbusControl(MHL_CBUS_FORCE_CLEAR_HPD);
    }

    //if(ucCurrentPortType == ucMHLPortType)
    {
        mapi_mhl_handler();

        _msAPI_MHL_ReadDeviceInformation();
    }

#if MHL_INPUT_SOURCE_AUTO_SWITCH
    // If in auto scan, return
    if( MApp_Is_InAutoScan_ATV() || MApp_Is_InAutoScan_DTV() )
        return;

    if(mapi_mhl_AutoSwitchHandler(FALSE, &ucMHLInputSourcePort))
    {
        //switch input source
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI + (E_UI_INPUT_SOURCE)ucMHLInputSourcePort;
    #if (ENABLE_DMP)
        if(IsStorageInUse())
        {
            MApp_MPlayer_StopPreview();
            MApp_MPlayer_Stop();
            MApp_MPlayer_ExitMediaPlayer();
        }
    #endif
        MApp_ZUI_ACT_ShutdownOSD();
        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
        MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
    #if (ENABLE_DMP)
        MApp_ChannelChange_VariableInit();
        MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
    #endif

        printf("\r\nMHL input source auto switch\r\n");
    }
#endif
}

void msAPI_MHL_SourceChange(MS_U8 ucCurrentPortType)
{
    if((ucCurrentPortType < UI_INPUT_SOURCE_HDMI) || (UI_INPUT_SOURCE_HDMI_END <= ucCurrentPortType))
    {
        mapi_mhl_CbusControl(MHL_CBUS_FORCE_CLEAR_HPD);
    }
    else // Change to MHL port
    {
        mapi_mhl_CbusControl(MHL_CBUS_FORCE_RESET_HPD);
    }
}

void msAPI_MHL_TV_DC_off(void)
{
    mapi_mhl_PowerCtrl(E_MHL_POWER_STANDBY); //MSG1200 into power saving mode

#if MHL_TV_DC_OFF_BEHAVIOR_TV_BACK_TO_NORMAL_ON

    if(!msAPI_MHL_IsCbusConnected())
    {
        mapi_mhl_CbusWakeupIntSetting();
    }

#endif
}

MS_BOOL msAPI_MHL_SendRCP_PressRelease_Cmd(MS_U8 u8RCPKey, MS_BOOL bIsRelease)
{
    return mapi_mhl_SendRCP_PressRelease_Cmd(u8RCPKey, bIsRelease);
}

MS_BOOL msAPI_MHL_SendRCPAutoReleaseCmd(MS_U8 u8RCPKey)
{
    printf("Auto send RCP release key.\r\n");
    return mapi_mhl_SendRCPAutoReleaseCmd(u8RCPKey);
}

MS_BOOL msAPI_MHL_SendRAPCmd(MS_U8 databuf)
{
    return mapi_mhl_SendRAPCmd(databuf);
}

MS_BOOL msAPI_MHL_CableDetect(void)
{
    return mapi_mhl_CableDetect();
}

void msAPI_MHL_CbusIsolate(void)
{
    //Do Nothing;
    //mapi_mhl_CbusIsolate();
}

void msAPI_MHL_CbusControl(MS_U8 ucState)
{
    mapi_mhl_CbusControl(ucState);
}

void msAPI_MHL_PowerCtrl(E_MHL_POWERCTRL_Mode pctrl)
{
    mapi_mhl_PowerCtrl(pctrl);
}

void msAPI_MHL_CbusWakeupIntSetting(void)
{
    mapi_mhl_CbusWakeupIntSetting();
}

#elif (MHL_TYPE == MHL_TYPE_ELAND)
BOOLEAN msAPI_MHL_IsCbusConnected(void)
{
    return mapi_mhl_CbusStatus();
}

void msAPI_MHL_Initialization(void)
{
    printf("\r\nMHL Init, MHL_TYPE = 0x%x\r\n", MHL_TYPE);

    // Reset
    MHL_Reset_High();
    msAPI_Timer_Delayms(5);
    MHL_Reset_Low();
    msAPI_Timer_Delayms(5);
    MHL_Reset_High();

    // I2C Init
    //mapi_swi2c_init(g_MhlI2CBus);
    #if (ENABLE_SW_EMULATION_IIC == ENABLE)
    mapi_mhl_RegisterIOCallBackFunctions(MDrv_SW_Emulation_IIC_ReadBytes, MDrv_SW_Emulation_IIC_WriteBytes);
    #else
    mapi_mhl_RegisterIOCallBackFunctions(MDrv_IIC_ReadBytes, MDrv_IIC_WriteBytes);
    #endif
    //mapi_mhl_I2C_Channel_Settings(E_I2C_BUS_DDCD0);
    mapi_mhl_I2C_Channel_Settings(E_I2C_BUS_SYS, 0xC8, 0xD0);
    mapi_mhl_TxSwap_Settings(0);

    // MHL Init
    mapi_mhl_init(MStar_MHL_EDID, tMHL_DEVICE_CAPABILITY_TABLE);

    //mapi_mhl_RegisterCallBackFunctions();
}

void msAPI_MHL_Handler(MS_U8 ucCurrentPortType)
{
    if((ucCurrentPortType < UI_INPUT_SOURCE_HDMI) || (UI_INPUT_SOURCE_HDMI_END <= ucCurrentPortType))
        mapi_mhl_handler();
    }
}

void msAPI_MHL_SourceChange(MS_U8 ucCurrentPortType)
{
    //Do Nothing;
    ucCurrentPortType = ucCurrentPortType;
}

void msAPI_MHL_TV_DC_off(void)
{
    //Do Nothing;
}

MS_BOOL msAPI_MHL_SendRCP_PressRelease_Cmd(MS_U8 u8RCPKey, MS_BOOL bIsRelease)
{
    return mapi_mhl_SendRCP_PressRelease_Cmd(u8RCPKey, bIsRelease);
}

MS_BOOL msAPI_MHL_SendRAPCmd(MS_U8 databuf)
{
    return mapi_mhl_SendRAPCmd(databuf);
}

#elif (MHL_TYPE == MHL_TYPE_SI)

#elif (MHL_TYPE == MHL_TYPE_SiI1292)
static DWORD m_MHLMonitorTimer;
extern void T0_irqtimes(void);
BOOLEAN msAPI_MHL_IsCbusConnected(void)
{
    return CpCableDetect();
}
void msAPI_MHL_Initialization(void)
{

    printf("\r\nMHL Init, MHL_TYPE = 0x%x\r\n", MHL_TYPE);

    // Reset
    MHL_Reset_High();
    msAPI_Timer_Delayms(5);
    MHL_Reset_Low();
    msAPI_Timer_Delayms(5);
    MHL_Reset_High();

    // I2C Init
    //mapi_swi2c_init(g_MhlI2CBus);

    // MHL Init
    Mhlfuntion_inition();
    //mapi_mhl_RegisterCallBackFunctions();
    m_MHLMonitorTimer =   msAPI_Timer_GetTime0();

}
void msAPI_MHL_Handler(MS_U8 ucCurrentPortType)
{
    ucCurrentPortType = ucCurrentPortType;

    if (msAPI_Timer_DiffTimeFromNow(m_MHLMonitorTimer) > 1)
    {
        m_MHLMonitorTimer =   msAPI_Timer_GetTime0();
        T0_irqtimes();
    }

    mhlfunction();
}

void msAPI_MHL_SourceChange(MS_U8 ucCurrentPortType)
{
    //Do Nothing;
    ucCurrentPortType = ucCurrentPortType;
}

void msAPI_MHL_TV_DC_off(void)
{
    //Do Nothing;
}

MS_BOOL msAPI_MHL_SendRCP_PressRelease_Cmd(MS_U8 u8RCPKey, MS_BOOL bIsRelease)
{
    u8RCPKey = u8RCPKey;
    bIsRelease = bIsRelease;
    return 0;
//    return mapi_mhl_SendRCP_PressRelease_Cmd(u8RCPKey, bIsRelease);
}

MS_BOOL msAPI_MHL_SendRCPAutoReleaseCmd(MS_U8 u8RCPKey)
{
    u8RCPKey = u8RCPKey;
    // Always return false to skip MHL function;
    return FALSE;
}

MS_BOOL msAPI_MHL_SendRAPCmd(MS_U8 databuf)
{
    databuf = databuf;
    return 0;
//    return mapi_mhl_SendRAPCmd(databuf);
}

#else
#error "\r\nWrong MHL_TYPE!!!\r\n"
#endif // MHL_TYPE

#endif

#endif
