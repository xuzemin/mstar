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
#define _MAPP_APENGINE_C_

#if (ENABLE_CAPE)
/******************************************************************************/
/*                            Header Files                                    */
/* ****************************************************************************/
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "datatype.h"

#include "MsSystemData.h"
#include "apiGOP.h"
#include "drvUART.h"
#include "SysInit.h"
#include "drvCPU.h"
#include "msAPI_MailBox.h"
#include "msAPI_DrvInit.h"

#include "apiGOP.h"
#include "msAPI_MIU.h"
#include "msAPI_APEngine.h"
#include "msAPI_OSD.h"
#include "msAPI_audio.h"
#include "msAPI_Global.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_Music.h"
#include "msAPI_Timer.h"

#include "MApp_IR.h"
#include "MApp_APEngine.h"
#include "MApp_ChannelChange.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"

#include "MApp_ZUI_ACTcoexistWin.h"
#include "drvMVOP.h"
#include "sysinfo.h"
#include "MApp_UiMediaPlayer_Define.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"

#if ENABLE_MPLAYER_PLUGIN
#include "mapp_mplayer.h"
#endif //#if ENABLE_MPLAYER_PLUGIN
#include "debug.h"

#include "mapp_videoplayer.h"

// panel module
#include "Panel.h"
#include "apiPNL.h"

#define MAX_NUM_OF_VOL_LEVEL       100
#define DEBUG_AP_STATE 0x01
#define DEBUG_AP_TYPE 0x02
#define DEBUG_APENGINE 0x00
#define PRINT_DEBUG_INFO printf("\n%s %s Line %d:\n", __FILE__, __FUNCTION__, __LINE__);

#if (CAPE_FB_MEMORY_TYPE & MIU1)

    #define MIU_SHIFT   MIU_INTERVAL
    #define MDrv_APEngine_SwitchMIUGroup(x) do{ \
                                            MDrv_WriteRegBit(0x12F2, x, BIT3); \
                                          }while(0)
#else

    #define MIU_SHIFT   0x0
    #define MDrv_APEngine_SwitchMIUGroup(x)  //
#endif

#define CAPE_FB0    (MIU_SHIFT | CAPE_FB_ADR)
#define CAPE_FB1    (MIU_SHIFT | (CAPE_FB_ADR + (CAPE_FB_LEN/2)))

U32 gCurrentRomFileLength = 0;
//OSD
typedef struct
{
    U8 u8Key;
    EN_OSD_WNDEXEACTION_ENUM action;
} KEYEVENT_IDLE;

typedef enum
{
    FAR_CMD_SC_Active,
    FAR_CMD_SC_EnableInputSource,
    FAR_CMD_SC_SetBlackScreen,
    FAR_CMD_SC_SetCaptureWin,
    FAR_CMD_SC_SetDisplayWin,
    FAR_CMD_SC_SetInputSource,
    FAR_CMD_SC_SetMVDInfo,
    FAR_CMD_SC_SetPanelOutput,
}E_OBAMA_CMD_SC_TYPE;

typedef enum
{
    FAR_CMD_SYSTEM_SetNexusReady,
    FAR_CMD_SYSTEM_SetShareMemory,
}E_OBAMA_CMD_SYSTEM_TYPE;


//replace original state "INIT" by "LISTEN"
//EN_APENGINE_STATE enAPEngineState = STATE_APENGINE_INIT;
EN_APENGINE_STATE enAPEngineState = STATE_APENGINE_LISTEN;

#ifdef AP_COWORK
static BOOLEAN  bGoCowork = FALSE;
#endif

static BOOLEAN  bRun = FALSE;
static U16 u16nowBIN = 0;
static EN_APENGINE_HANDLER enHandleType = NULL_HANDLE;

static U16 u16Height;
static U16 u16alignWidth;
static BOOLEAN bstrench;
static GFX_Buffer_Format gefmt;
static BOOLEAN b_enable_transclr;

static EN_RET enAPEngineRetVal;
U8 APENGINE_GWINID;  //,  APENGINE_RT_FBID;
static MS_INIT_DATA_T _gsMsInitData;


static U16 u16Width;
static U32 gs32ProtocolParameterBuffer = 0;

//========================================================================
//  initial functions
//========================================================================
static void _APEngine_Init_ReceiveRequest(MS_INIT_DATA_T *pMsInitData)
{
    #define TIMEOUT_COUNT 200

    U8 wait = 0;
    MS_INIT_DATA_T *pMsInitDataInRAM = NULL;

    MBX_Msg MB_Message;

    while (wait++ < TIMEOUT_COUNT)
    {
        msAPI_Timer_Delayms(10);

        if((MSApi_MBX_RecvMsg(E_MBX_CLASS_CAPE, &MB_Message, 0, MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS)
            &&(MB_Message.u8Index==MB_CAPE_INIT_REQ))
        {
            break;
        }
    }

    if ( wait >= TIMEOUT_COUNT )
    {
        // timeout
        printf("timeout\n");
        return;
    }

    gs32ProtocolParameterBuffer = ReadU32BE(&MB_Message.u8Parameters[2]);
    pMsInitDataInRAM = (MS_INIT_DATA_T *) _PA2VA(gs32ProtocolParameterBuffer);
    pMsInitDataInRAM->u16_client_width = BE2ME16(pMsInitDataInRAM->u16_client_width);
    pMsInitDataInRAM->u16_client_height = BE2ME16(pMsInitDataInRAM->u16_client_height);

    //printf("base at 0x%p\n", pMsInitDataInRAM);
    //printf("width = %u, height = %u\n", pMsInitDataInRAM->u16_client_width, pMsInitDataInRAM->u16_client_height);

    memcpy(pMsInitData, pMsInitDataInRAM, sizeof(MS_INIT_DATA_T));
}

static void _APEngine_Init_SendResponse(void)
{
    MBX_Msg mbxMsg;
    MS_SYSTEM_DATA_T *pMsSystemDataInRAM;

    if ( gs32ProtocolParameterBuffer == 0 )
    {
        printf("do not get request, abort send respons\n");
        return;
    }

    pMsSystemDataInRAM = (MS_SYSTEM_DATA_T *) _PA2VA(gs32ProtocolParameterBuffer);
    pMsSystemDataInRAM->u32_on_screen_buffer_addr = ME2BE32(CAPE_FB0);
    pMsSystemDataInRAM->u32_off_screen_buffer_addr = ME2BE32(CAPE_FB1);
    pMsSystemDataInRAM->Rom_addr = ME2BE32((CAPE_JPG_MEMORY_TYPE & MIU1) ? (CAPE_JPG_ADR | MIU_INTERVAL) : (CAPE_JPG_ADR)); // david
    pMsSystemDataInRAM->msGOP_GWIN = (E_GOP_APP<<4 | APENGINE_GWINID);
    pMsSystemDataInRAM->u32_miu_shift = (MIU_SHIFT);
    pMsSystemDataInRAM->u32_rom_file_length = (gCurrentRomFileLength);
    pMsSystemDataInRAM->msBaseSec = MApp_GetLocalSystemTime();

    //printf("--->u32_base_addr : %x\n", gs32ProtocolParameterBuffer );
    //printf("--->u32_on_screen_buffer_addr : %x\n", pMsSystemDataInRAM->u32_on_screen_buffer_addr );
    //printf("--->u32_off_screen_buffer_addr : %x\n", pMsSystemDataInRAM->u32_off_screen_buffer_addr );
    //printf("--->Rom_addr : %x\n", pMsSystemDataInRAM->Rom_addr );
    //printf("--->GOPGWIN : %x\n", pMsSystemDataInRAM->msGOP_GWIN );
    //printf("--->MIU : %x\n", pMsSystemDataInRAM->u32_miu_shift );
    //printf("--->BASESEC : %x\n", pMsSystemDataInRAM->msBaseSec );

    // MS_BOARD_T
    #define MS_BOARD (pMsSystemDataInRAM->msBoard)
    MS_BOARD.u16PANEL_TYPE_SEL = ME2BE16(g_PNL_TypeSel);
    MS_BOARD.u32XTAL_RTC_CLOCK_FREQ = ME2BE32(32768);
    MS_BOARD.u32XTAL_CLOCK_FREQ = ME2BE32(12000000);
    MS_BOARD.u8INPUT_AV_VIDEO_COUNT = INPUT_AV_VIDEO_COUNT;
    MS_BOARD.u8INPUT_SV_VIDEO_COUNT = INPUT_SV_VIDEO_COUNT;
    MS_BOARD.u8INPUT_YPBPR_VIDEO_COUNT = INPUT_YPBPR_VIDEO_COUNT;
    MS_BOARD.u8INPUT_SCART_VIDEO_COUNT = INPUT_SCART_VIDEO_COUNT;
    MS_BOARD.u8ENABLE_HDMI = 1;
    MS_BOARD.u8MEMORY_MAP = MEMORY_MAP;
    MS_BOARD.u8DRAM_TYPE = DRAM_TYPE;
    MS_BOARD.u16MOD_LVDS_GPIO = ME2BE16(MOD_LVDS_GPIO);
    MS_BOARD.u8DRAM_CHIP = DRAM_ETRON;
    MS_BOARD.u8PANEL_CONNECTOR_SWAP_LVDS_CH = PANEL_CONNECTOR_SWAP_LVDS_CH;
    MS_BOARD.u8PANEL_CONNECTOR_SWAP_LVDS_POL = PANEL_CONNECTOR_SWAP_LVDS_POL;
    MS_BOARD.u8PANEL_CONNECTOR_SWAP_PORT = PANEL_CONNECTOR_SWAP_PORT;
    MS_BOARD.u8ETHNET_PHY_TYPE = ETHNET_PHY_TYPE;

    // MS_PANEL_T
    #define MS_PANEL (pMsSystemDataInRAM->msPanel)
    MS_PANEL.u16PANEL_WIDTH             = ME2BE16(g_IPanel.Width());
    MS_PANEL.u16PANEL_HEIGHT            = ME2BE16(g_IPanel.Height());

#ifdef NETWORK_CONFIG_CHINA
    #define PROXY_SETTING   DISABLE//ENABLE
    #define MAC_SETTING     DISABLE//ENABLE

    #define MS_NETWORK  (pMsSystemDataInRAM->msNetwork)

    MS_NETWORK.bNet_Config_mode                     = stGenSetting.g_SysSetting.g_Network.bNet_Config_mode;
  #if (PROXY_SETTING)
    memcpy(MS_NETWORK.NetProxy_PassWord,stGenSetting.g_SysSetting.g_Network.NetProxy_PassWord,sizeof(BYTE)*MAX_NET_PASSWORD_LEN);
    memcpy(MS_NETWORK.NetProxy_UserName,stGenSetting.g_SysSetting.g_Network.NetProxy_UserName,sizeof(BYTE)*MAX_NET_PASSWORD_LEN);
  #endif

    MS_NETWORK.g_NetIP.u8Network_SetFlag            = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Network_Flag;
    MS_NETWORK.g_NetIP.u8Net_Addr_Class_A           = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_A;
    MS_NETWORK.g_NetIP.u8Net_Addr_Class_B           = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_B;
    MS_NETWORK.g_NetIP.u8Net_Addr_Class_C           = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_C;
    MS_NETWORK.g_NetIP.u8Net_Addr_Class_D           = stGenSetting.g_SysSetting.g_Network.g_NetIP.u8Net_Addr_Class_D;

    MS_NETWORK.g_NetNetmask.u8Network_SetFlag       = stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Network_Flag;
    MS_NETWORK.g_NetNetmask.u8Net_Addr_Class_A      = stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_A;
    MS_NETWORK.g_NetNetmask.u8Net_Addr_Class_B      = stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_B;
    MS_NETWORK.g_NetNetmask.u8Net_Addr_Class_C      = stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_C;
    MS_NETWORK.g_NetNetmask.u8Net_Addr_Class_D      = stGenSetting.g_SysSetting.g_Network.g_NetNetmask.u8Net_Addr_Class_D;

    MS_NETWORK.g_NetGateway.u8Network_SetFlag       = stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Network_Flag;
    MS_NETWORK.g_NetGateway.u8Net_Addr_Class_A      = stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_A;
    MS_NETWORK.g_NetGateway.u8Net_Addr_Class_B      = stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_B;
    MS_NETWORK.g_NetGateway.u8Net_Addr_Class_C      = stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_C;
    MS_NETWORK.g_NetGateway.u8Net_Addr_Class_D      = stGenSetting.g_SysSetting.g_Network.g_NetGateway.u8Net_Addr_Class_D;

    MS_NETWORK.g_NetDNS.u8Network_SetFlag           = stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Network_Flag;
    MS_NETWORK.g_NetDNS.u8Net_Addr_Class_A          = stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_A;
    MS_NETWORK.g_NetDNS.u8Net_Addr_Class_B          = stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_B;
    MS_NETWORK.g_NetDNS.u8Net_Addr_Class_C          = stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_C;
    MS_NETWORK.g_NetDNS.u8Net_Addr_Class_D          = stGenSetting.g_SysSetting.g_Network.g_NetDNS.u8Net_Addr_Class_D;
  #if (PROXY_SETTING)
    MS_NETWORK.g_NetProxy.u8Network_SetFlag         = stGenSetting.g_SysSetting.g_Network.bProxyMode;
    MS_NETWORK.g_NetProxy.u8Net_Addr_Class_A        = stGenSetting.g_SysSetting.g_Network.g_NetProxy.u8Net_Addr_Class_A;
    MS_NETWORK.g_NetProxy.u8Net_Addr_Class_B        = stGenSetting.g_SysSetting.g_Network.g_NetProxy.u8Net_Addr_Class_B;
    MS_NETWORK.g_NetProxy.u8Net_Addr_Class_C        = stGenSetting.g_SysSetting.g_Network.g_NetProxy.u8Net_Addr_Class_C;
    MS_NETWORK.g_NetProxy.u8Net_Addr_Class_D        = stGenSetting.g_SysSetting.g_Network.g_NetProxy.u8Net_Addr_Class_D;
    MS_NETWORK.g_NetProxy.u16Net_Addr_Port          = stGenSetting.g_SysSetting.g_Network.g_NetProxy.u16Net_Addr_Port;
  #endif
  #if (MAC_SETTING)
    MS_NETWORK.g_NetMacAddress.u8Network_SetFlag    = stGenSetting.g_SysSetting.g_Network.g_NetMacAddress.u8Network_SetFlag;
    MS_NETWORK.g_NetMacAddress.u8MANUFACTURE_ID_1   = stGenSetting.g_SysSetting.g_Network.g_NetMacAddress.u8MANUFACTURE_ID_1;
    MS_NETWORK.g_NetMacAddress.u8MANUFACTURE_ID_2   = stGenSetting.g_SysSetting.g_Network.g_NetMacAddress.u8MANUFACTURE_ID_2;
    MS_NETWORK.g_NetMacAddress.u8MANUFACTURE_ID_3   = stGenSetting.g_SysSetting.g_Network.g_NetMacAddress.u8MANUFACTURE_ID_3;
    MS_NETWORK.g_NetMacAddress.u8NETWORK_CARD_ID_1  = stGenSetting.g_SysSetting.g_Network.g_NetMacAddress.u8NETWORK_CARD_ID_1;
    MS_NETWORK.g_NetMacAddress.u8NETWORK_CARD_ID_2  = stGenSetting.g_SysSetting.g_Network.g_NetMacAddress.u8NETWORK_CARD_ID_2;
    MS_NETWORK.g_NetMacAddress.u8NETWORK_CARD_ID_3  = stGenSetting.g_SysSetting.g_Network.g_NetMacAddress.u8NETWORK_CARD_ID_3;
  #endif

#else // #ifdef NETWORK_CONFIG_CHINA
//for testing AP
    #define MS_NETWORK (pMsSystemDataInRAM->msNetwork)
    MS_NETWORK.bNet_Config_mode                     = 0;
    //MS_NETWORK.g_NetIP.u8Network_SetFlag            = 0;
    //MS_NETWORK.g_NetNetmask.u8Network_SetFlag       = 0;
    //MS_NETWORK.g_NetGateway.u8Network_SetFlag       = 0;
    //MS_NETWORK.g_NetDNS.u8Network_SetFlag           = 0;
    MS_NETWORK.g_NetProxy.u8Network_SetFlag         = 1;
    MS_NETWORK.g_NetMacAddress.u8Network_SetFlag    = 0;

#endif // #ifdef NETWORK_CONFIG_CHINA

    // send response to cape
    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_CAPE;
    mbxMsg.u8Index = MB_CAPE_INIT_RES;
    mbxMsg.u8ParameterCount = 1;
    mbxMsg.u8Parameters[0] = 0;

    while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));
}


//========================================================================
//  APENGINE interface
//========================================================================
BOOLEAN MApp_APEngine_RegisterByID(U16 BIN_ID, EN_APENGINE_HANDLER Key_Handler, U32 u32BEON_ADR, U32 u32BEON_LEN)
{
    if(msAPI_APEngine_AppRunByBinID(BIN_ID, u32BEON_ADR, u32BEON_LEN))
    {
        u16nowBIN = BIN_ID;
        enHandleType = Key_Handler;
        return TRUE;
    }
    return FALSE;
}

BOOLEAN MApp_APEngine_RegisterBIN(U16 BIN_ID, EN_APENGINE_HANDLER Key_Handler, U32 u32AppBinaryAddr, U32 u32Len, U32 u32BEON_ADR, U32 u32BEON_LEN)
{
    if(msAPI_APEngine_AppRun(u32AppBinaryAddr, u32Len, u32BEON_ADR, u32BEON_LEN))
    {
        u16nowBIN = BIN_ID;
        enHandleType = Key_Handler;
        return TRUE;
    }
    return FALSE;
}

U16 MApp_APEngine_GetnowBIN(void)
{
    return u16nowBIN;
}

//to get APEngine status
U8 MApp_APEngine_CheckAPStatus(void)
{
    #ifdef AP_COWORK
        return (0x00 | (bGoCowork<< 1) |bRun);
    #else
        return (0x00 |bRun);
    #endif
}

//to get APEngine return value
EN_RET MApp_APEngine_CheckRetVal(void)
{
    if (enAPEngineState == STATE_APENGINE_LISTEN)
    {
        return enAPEngineRetVal;
    }

    return EXIT_NULL;
}

//to clear APEngine return value
void MApp_APEngine_ClearRetVal(void)
{
    enAPEngineRetVal=EXIT_NULL;
}

//to hide APEngine temporary ( for back to inputsource )
void MApp_APEngine_HideGWIN(void)
{
    // Switch to GOP APP
    U8 u8CurrGOP = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);

    MApi_GOP_GWIN_Switch2Gwin(APENGINE_GWINID);
    //other GWIN settings

    MApi_GOP_GWIN_Enable( APENGINE_GWINID , FALSE);
    //printf("\nAPENGINE: AP_GWIN %x disable\n", APENGINE_GWINID);

    // restore GOP
    MApi_GOP_GWIN_SwitchGOP(u8CurrGOP);
    MApi_GOP_GWIN_SetFMT0TransClr(COLOR_TRANSPARENT);
}

//to resume APEngine from hide ( for back to inputsource )
void MApp_APEngine_RestoreGWIN(void)
{
    U8 u8CurrGOP = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_OP0);     // Refine GOP dst configuration function.

    if(bstrench)
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0, 0, u16alignWidth,u16Height);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, u16Height, g_IPanel.Height());
        MApi_GOP_GWIN_Set_HSCALE(TRUE, u16alignWidth, g_IPanel.Width());
    }
    else
    {
        MApi_GOP_GWIN_Set_VSCALE(FALSE, 0, 0);
        MApi_GOP_GWIN_Set_HSCALE(FALSE, 0, 0);
    }

    MApi_GOP_GWIN_SetBlending(APENGINE_GWINID, FALSE, 63);
    switch (gefmt)
    {
        case GFX_FMT_ARGB8888:
        case GFX_FMT_I8:
        case GFX_FMT_ARGB4444:
            //should not set transparent color in these format
            MApi_GOP_GWIN_SetBlending(APENGINE_GWINID, TRUE, 63);
            MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);
            break;
        default:
            MApi_GOP_GWIN_SetBlending(APENGINE_GWINID, FALSE, 63);
            if ( b_enable_transclr == FALSE )
            {
                MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);
            }
            else
            {
                MApi_GOP_GWIN_SetFMT0TransClr(COLOR_TRANSPARENT);
            }
            break;
    }

    MApi_GOP_GWIN_Switch2Gwin(APENGINE_GWINID);
    MApi_GOP_GWIN_Enable(APENGINE_GWINID, TRUE);
    //printf("\nAPENGINE: AP_GWIN %x enable\n", APENGINE_GWINID);

    // restore GOP
    MApi_GOP_GWIN_SwitchGOP(u8CurrGOP);
}

#ifdef AP_COWORK
//to set APEngine status ( for co-work )
void MApp_APEngine_SetAPCowork(BOOLEAN bEnable)
{
    bGoCowork = bEnable;
}

#if AP_WITH_OSD || AP_WITH_TTX
//when coexist with OSD/TTX/SUBTITLE, set to resume APEngine
void MApp_APEngine_SetGoback(void)
{
    if( enAPEngineState == STATE_APENGINE_WITH_OSD && (g_bGoBack_AP||g_bHideAP))
    {
        DBG_APSTATE(printf(">>MApp_APEngine_SetGoback(%d > WAIT)\n", enAPEngineState);)
        enAPEngineState = STATE_APENGINE_WAIT;
        g_bGoBack_AP = FALSE;
        g_bHideAP = FALSE;
    }
    else
    {
        DBG_APSTATE(printf(">>MApp_APEngine_SetGoback(%d > NONE)\n", enAPEngineState);)
        enAPEngineState = STATE_APENGINE_NONE;
        printf("\nAP: clean goBACK error\n");
    }
}
#endif // #if AP_WITH_OSD || AP_WITH_TTX

#endif // #ifdef AP_COWORK


//========================================================================
//  state control
//========================================================================

//let APEngine start work (from LISTEN to INIT)
BOOLEAN MApp_APEngine_Start(void)
{
    if( enAPEngineState == STATE_APENGINE_LISTEN )
    {
        bRun =TRUE; //set status to run
        #ifdef AP_COWORK
        #if AP_WITH_OSD
        g_bGoBack_AP = FALSE;
        #endif
        #if AP_WITH_TTX
        g_bHideAP = FALSE;
        #endif
        #endif

        enAPEngineState = STATE_APENGINE_INIT;
        DBG_APSTATE(printf(">>MApp_APEngine_Start(LISTEN > INIT)\n", STATE_APENGINE_LISTEN, STATE_APENGINE_INIT);)
        return TRUE;
    }
    else
    {
        DBG_APSTATE(printf(">>MApp_APEngine_Start(%d > NONE)\n", enAPEngineState, STATE_APENGINE_NONE);)
        enAPEngineState = STATE_APENGINE_NONE;
    }

    return FALSE;
}

BOOLEAN MApp_APEngine_Init(void)
{
    U16 pitch = 0;

    // Clear FB
    MApi_GFX_ClearFrameBuffer(((CAPE_FB_MEMORY_TYPE & MIU1) ? (CAPE_FB_ADR | MIU_INTERVAL) : (CAPE_FB_ADR)), CAPE_FB_LEN, 0x0);

    // Set flag to check final
    msAPI_APEngine_APP_Finalize_Init();

    // control MIU: !!! when TTX up, it should set to zero
    MDrv_APEngine_SwitchMIUGroup(1);
    //printf("\nAP: MIU %d: CAPE_FB %08X and %08X, GOP control %d\n", (CAPE_FB_MEMORY_TYPE&0x00000001), CAPE_FB0, CAPE_FB1, MDrv_ReadRegBit(0x1279, BIT3));

    //MDrv_InitMailBoxQueue();
    _APEngine_Init_ReceiveRequest(&_gsMsInitData);

    // get InitData
    u16Width = _gsMsInitData.u16_client_width;
    u16Height = _gsMsInitData.u16_client_height;
    bstrench = _gsMsInitData.b_stretch;
    b_enable_transclr = _gsMsInitData.b_enable_transclr;
    if ( _gsMsInitData.u8_fmt == E_GOP_COLOR_ARGB8888 )
    {
        gefmt = GFX_FMT_ARGB8888;
        u16alignWidth = ((u16Width * 4 + 0x0F) & ~(0x0F))/4;
    }
    else if ( _gsMsInitData.u8_fmt == E_GOP_COLOR_RGB555_BLINK )
    {
        gefmt = GFX_FMT_ARGB1555;
        u16alignWidth = ((u16Width * 2 + 0x0F) & ~(0x0F))/2;
    }
    else if ( _gsMsInitData.u8_fmt == E_GOP_COLOR_RGB565 )
    {
        gefmt = GFX_FMT_RGB565;
        u16alignWidth = ((u16Width * 2 + 0x0F) & ~(0x0F))/2;
    }
    else if ( _gsMsInitData.u8_fmt == E_GOP_COLOR_I8 )
    {
        gefmt = GFX_FMT_I8;
        u16alignWidth = ((u16Width + 0x0F) & ~(0x0F));
    }
    else //if ( AppInitRequestData.u8_fmt == E_GOP_COLOR_ARGB4444 )
    {
         gefmt = GFX_FMT_ARGB4444;
         u16alignWidth = ((u16Width * 2 + 0x0F) & ~(0x0F))/2;
    }

    // Switch to GOP APP
    U8 u8CurrGOP = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);

    // Initial GOP setting
    MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_OP0);     // Refine GOP dst configuration function.
    if ( _gsMsInitData.b_stretch == TRUE )
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0, 0, u16alignWidth, u16Height);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, u16alignWidth, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, u16Height, g_IPanel.Height());
    }
    else
    {
        MApi_GOP_GWIN_Set_HSCALE(FALSE, 0, 0);
        MApi_GOP_GWIN_Set_VSCALE(FALSE, 0, 0);
    }

    // Create GWIN
    APENGINE_GWINID = MApi_GOP_GWIN_CreateWin(u16alignWidth, u16Height, gefmt);

    // Set FB format
    switch ( gefmt & 0xff )
    {
        case GFX_FMT_I1 :
            pitch = (u16alignWidth) >> 3;
            break;
        case GFX_FMT_I2 :
            pitch = (u16alignWidth<<1) >> 3;
            break;
        case GFX_FMT_I4 :
            pitch = (u16alignWidth<<2) >> 3;
            break;
        case GFX_FMT_I8 :
            pitch = u16alignWidth;
            break;
        case GFX_FMT_RGB565 :
        case GFX_FMT_ARGB1555 :
        case GFX_FMT_ARGB4444 :
        case GFX_FMT_1ABFGBG12355:
        case GFX_FMT_FABAFGBG2266:
            pitch = u16alignWidth << 1;
            break;
        case GFX_FMT_ARGB8888 :
            pitch = u16alignWidth << 2;
            break;
        default :
            //print err
            break;
    }

    //map FB
    GOP_GwinInfo gWin;
    gWin.u16DispHPixelStart = 0;
    gWin.u16DispVPixelStart = 0;
    gWin.u16RBlkHPixSize = u16alignWidth;
    gWin.u16RBlkVPixSize = u16Height;
    gWin.u16RBlkHRblkSize = pitch;
    gWin.u16DispHPixelEnd = u16alignWidth;
    gWin.u16DispVPixelEnd = u16Height;
    gWin.u32DRAMRBlkStart = CAPE_FB0;
    gWin.u16WinX = gWin.u16WinY = 0;
    gWin.clrType = (EN_GOP_COLOR_TYPE)_gsMsInitData.u8_fmt;

    //printf("\n W:%u, H:%u, Addr:0x%08LX ", gWin.u16RBlkHPixSize, gWin.u16RBlkVPixSize, gWin.u32DRAMRBlkStart);
    //printf("with   (%u, %u)-(%u, %u)\n", gWin.u16DispHPixelStart, gWin.u16DispVPixelStart, gWin.u16DispHPixelEnd, gWin.u16DispVPixelEnd);

    MApi_GOP_GWIN_SetWinInfo(APENGINE_GWINID, &gWin);

    MApi_GOP_GWIN_SetWinDispPosition(APENGINE_GWINID, 0, 0);

    // blending
    switch (_gsMsInitData.u8_fmt)
    {
        case E_GOP_COLOR_ARGB8888:
        case E_GOP_COLOR_I8:
        case E_GOP_COLOR_ARGB4444:
            //should not set transparent color in these format
            MApi_GOP_GWIN_SetBlending(APENGINE_GWINID, TRUE, 63);
            MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);
            break;

        default:
            MApi_GOP_GWIN_SetBlending(APENGINE_GWINID, FALSE, 63);
            if ( _gsMsInitData.b_enable_transclr == FALSE )
            {
                MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);
            }
            else
            {
                MApi_GOP_GWIN_SetFMT0TransClr(COLOR_TRANSPARENT);
            }
            break;
    }

    MApi_GOP_GWIN_Switch2Gwin(APENGINE_GWINID);

    msAPI_OSD_SetClipWindow(0, 0, u16alignWidth-1, u16Height-1);

    // clear
    clrBtn1.x = 0;
    clrBtn1.y = 0;
    clrBtn1.width = u16alignWidth;
    clrBtn1.height = u16Height;
    clrBtn1.b_clr = 0;
    clrBtn1.u8Gradient = CONSTANT_COLOR;
    clrBtn1.fHighLight = FALSE;
    //clrBtn1.b_clr = 0xFFFF0000;
    //MApi_GFX_SetAlpha(TRUE, COEF_ONE, ABL_FROM_ASRC, 0);
    msAPI_OSD_DrawBlock(&clrBtn1);

    MApi_GOP_GWIN_Enable(APENGINE_GWINID, TRUE);

    _APEngine_Init_SendResponse();

    // restore GOP
    MApi_GOP_GWIN_SwitchGOP(u8CurrGOP);

    return TRUE;
}

void MApp_APEngine_Exit(void)
{
    //enAPEngineState = STATE_APENGINE_EXIT;
    // Stop audio

    msAPI_Music_StopDecode();//??

    // Switch to GOP APP
    U8 u8CurrGOP = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    //MApi_GOP_GWIN_Enable(APENGINE_GWINID, FALSE);

    // Kill GWIN
    MApi_GOP_GWIN_EnableTransClr((EN_GOP_TRANSCLR_FMT)0, TRUE);
    MApi_GOP_GWIN_DestroyWin(APENGINE_GWINID);
    MApi_GOP_GWIN_ReleaseWin(APENGINE_GWINID);

    // Restore GOP stretch
    //MApi_GOP_Initialize_StretchWindow(E_GOP_APP);
    MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0, 0, 0, 1360, 768);
    MApi_GOP_GWIN_Set_HSCALE(TRUE, 1360, g_IPanel.Width());
    MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, g_IPanel.Height());

    // Restore GOP
    MApi_GOP_GWIN_SwitchGOP(u8CurrGOP);
    MApi_GOP_GWIN_SetFMT0TransClr(COLOR_TRANSPARENT);

    // Restore AD to None
    MApi_AUDIO_SetADOutputMode(AD_OUT_NONE);

    // Restore MIU
    ///TODO: save original MIU when INIT and restore here
    MDrv_MVOP_MiuSwitch(ENABLE_MIU_1);

    MDrv_APEngine_SwitchMIUGroup(0);

    //reset local var
    bRun = 0;
    u16nowBIN = 0;
    enHandleType = NULL_HANDLE;
    //if AP-COWORK no clear screen but release the keyProcessing
  #ifdef AP_COWORK
    if( bGoCowork)
    {
        bGoCowork = FALSE;
        g_bGoBack_AP = FALSE;
        g_bPassTV = FALSE;
        g_bHideAP = FALSE;
    }
  #endif

    // Wait cape to finalize
    U32 u32TimeStart = msAPI_Timer_GetTime0();
    while(msAPI_Timer_DiffTimeFromNow(u32TimeStart) < 2000)
    {
        msAPI_APEngine_ProcessMailBox();
        //printf("\nAP: exit used %d\n", msAPI_Timer_DiffTimeFromNow(u32TimeStart));
        if (msAPI_APEngine_APP_Finalize_Check())
        {
            printf("\nAP: exit cape in %lu\n", msAPI_Timer_DiffTimeFromNow(u32TimeStart));
            break;
        }
    }

#if defined(MIPS_CHAKRA) || defined(__AEONR2__)
    MDrv_COPRO_Disable();

    // Back UART to HK
  #if defined(__AEONR2__)
     mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
  #else
     mdrv_uart_connect(E_UART_PORT0, E_UART_PIU_UART0);
  #endif

#else // #if defined(MIPS_CHAKRA) || defined(__AEONR2__)

    MDrv_COPRO_Disable();

    // Back UART to HK
  #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
    mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
  #else
    mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
  #endif // #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)

#endif // #if defined(MIPS_CHAKRA) || defined(__AEONR2__)

    DBG_APSTATE(printf(">>MApp_APEngine_Exit(%d > LISTEN)\n", enAPEngineState, STATE_APENGINE_LISTEN);)

    //change state
    enAPEngineState = STATE_APENGINE_LISTEN;
    enAPEngineRetVal= EXIT_APENGINE_EXIT;

}

//to let APengine go back from switch input(from LISTEN to WAIT)
BOOLEAN MApp_APEngine_Resume(void)
{
    if( enAPEngineState == STATE_APENGINE_LISTEN )
    {
        enAPEngineState = STATE_APENGINE_WAIT;
        DBG_APSTATE(printf(">>MApp_APEngine_Resume(LISTEN > WAIT)\n");)
        return TRUE;
    }
    else
    {
        DBG_APSTATE(printf(">>MApp_APEngine_Resume(%d > NONE)\n", enAPEngineState);)
        enAPEngineState = STATE_APENGINE_NONE;
    }

    return FALSE;
}

#ifdef AP_COWORK
#if AP_WITH_OSD || AP_WITH_TTX
BOOLEAN MApp_APEngine_StartBG(void)
{
    if( enAPEngineState == STATE_APENGINE_LISTEN )
    {
        enAPEngineState = STATE_APENGINE_WITH_OSD;
        g_bGoBack_AP = TRUE;
        g_bHideAP = TRUE;
        DBG_APSTATE(printf(">>MApp_APEngine_StartBG(LISTEN > WITHOSD)\n");)
        return TRUE;
    }
    else
    {
        DBG_APSTATE(printf(">>MApp_APEngine_StartBG(%d > NONE)\n", enAPEngineState);)
        enAPEngineState = STATE_APENGINE_NONE;
        return FALSE;
    }

}
#endif // #if AP_WITH_OSD || AP_WITH_TTX
#endif // #ifdef AP_COWORK

//========================================================================
//  key processing
//========================================================================
//for Gamepad simulation
void MApp_APEngine_ProcessKey(U8 keycode)
{
    switch ( u8KeyCode )
    {
        case KEY_2:
        case KEY_4:
        case KEY_6:
        case KEY_8:
        case KEY_INFO:
        case KEY_CHANNEL_LIST:
        case KEY_RED:
        case KEY_GREEN:
            //NES 2P IR Input
            msAPI_APEngine_TransmitKey(keycode);
            break;
        default:
            //Ignore Other IR Key Input!
            break;
    }

}

//for ZUI vol
static BOOLEAN _MApp_APEngine_ProcessKeyEventIdleTable(U8 key, KEYEVENT_IDLE * keyevent)
{
    BOOLEAN handled = FALSE;
    while (keyevent->u8Key != KEY_NULL)
    {
        if (keyevent->u8Key == key)
        {
            handled = MApp_ZUI_ACT_ExecuteWndAction(keyevent->action);
            //we can allow multiple actions... depend on the last one action..
        }
        keyevent++;
    }

    return handled;
}

static BOOLEAN _MApp_APEngine_ProcessAudioVolumeKey(U8 key)
{
    static  KEYEVENT_IDLE code _key_event[] =
    {
        { KEY_VOLUME_PLUS, EN_EXE_INC_AUDIO_VOLUME },
        { KEY_VOLUME_MINUS, EN_EXE_DEC_AUDIO_VOLUME },
        { KEY_NULL, EN_EXE_ACTION_NULL },
    };

    if (key == KEY_NULL)
        return TRUE;

    //reset timer if any key
    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_RESET_AUTO_CLOSE_TIMER);

    return _MApp_APEngine_ProcessKeyEventIdleTable(key, (KEYEVENT_IDLE *) _key_event);
}

//normal game processKey flow
static void _MApp_APEngine_ProcessKey_Game(void)
{
    switch ( u8KeyCode )
    {
        case KEY_EXIT:
            msAPI_APEngine_TransmitKey(KEY_EXIT);
            MApp_APEngine_Exit();
            u8KeyCode = KEY_NULL;
            break;

        case KEY_VOLUME_PLUS:
            if ( stGenSetting.g_SoundSetting.Volume < MAX_NUM_OF_VOL_LEVEL )
            {
                stGenSetting.g_SoundSetting.Volume+= 5;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            break;

        case KEY_VOLUME_MINUS:
            if ( stGenSetting.g_SoundSetting.Volume > 0 )
            {
                stGenSetting.g_SoundSetting.Volume-= 5;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            break;

        case KEY_MUTE:
            {
                BOOLEAN bIsAudioMuted;
                bIsAudioMuted = msAPI_AUD_IsAudioMutedByUser();
                if (bIsAudioMuted == FALSE)
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                else
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
            break;

        default:
            msAPI_APEngine_TransmitKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;
    }
}

BOOLEAN MApp_APEngine_KeyBypass(void)
{
    BOOLEAN bRet = TRUE;
    #ifdef AP_COWORK
    if ( MApp_APEngine_CheckAPStatus() == FALSE
        #if AP_WITH_OSD || AP_WITH_TTX
        || g_bGoBack_AP ||g_bPassTV ||g_bHideAP
        #endif
    )
        bRet = TRUE;
    else
        bRet = FALSE;
    // PATCH
    if(enAPEngineState != STATE_APENGINE_WAIT)
        bRet = TRUE;
    #endif
    return bRet;
}

#ifndef AP_COWORK
//normal full processKey flow

static void _MApp_APEngine_ProcessKey_Fullcontrol(void)
{
    switch ( u8KeyCode )
    {
        case KEY_EXIT:
            if (MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY) //ZUI:
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                u8KeyCode = KEY_NULL;
                break;
            }
            else
            {
                MApp_APEngine_HideGWIN();
                enAPEngineState = STATE_APENGINE_LISTEN;
                enAPEngineRetVal = EXIT_GOTO_INPUTSOURCE;
                u8KeyCode = KEY_NULL;
                break;
            }

        case KEY_INPUT_SOURCE:
            MApp_APEngine_HideGWIN();
            enAPEngineState = STATE_APENGINE_LISTEN;
            enAPEngineRetVal = EXIT_GOTO_INPUTSOURCE;
            u8KeyCode = KEY_NULL;
            break;

        case KEY_POWER:
        case DSC_KEY_PWROFF:
            MApp_APEngine_Exit();
            msAPI_APEngine_TransmitKey(KEY_EXIT);
            enAPEngineRetVal = EXIT_GOTO_STANDBY;
            u8KeyCode = KEY_NULL;
            break;

        case KEY_MUTE:
        case KEY_VOLUME_PLUS:
        case KEY_VOLUME_MINUS:
            MApp_ZUI_ACT_StartupOSD(E_OSD_AUDIO_VOLUME);
            _MApp_APEngine_ProcessAudioVolumeKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;

        default:
            msAPI_APEngine_TransmitKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;
    }
}

//cowork full processKey flow
#else


static void _MApp_APEngine_ProcessKey_Cowork(void)
{
  #if (DEBUG_APENGINE & DEBUG_AP_STATE)
    static U8 pre_u8KeyCode = 0xFF;
    if(u8KeyCode != pre_u8KeyCode)
    {
        PRINT_DEBUG_INFO
        printf("bGoCowork[%d] g_bGoBack_AP[%d] g_bHideAP[%d]\n", bGoCowork, g_bGoBack_AP, g_bHideAP);
        pre_u8KeyCode = u8KeyCode;
    }
  #endif

    if(bGoCowork && (!g_bGoBack_AP && !g_bHideAP))
    {
        switch ( u8KeyCode )
        {
          #if AP_WITH_TTX
            case KEY_SUBTITLE:
            case KEY_TTX:
                enAPEngineState = STATE_APENGINE_WITH_OSD;
                g_bHideAP = TRUE;
                //printf("\nAPENGINE: goBACK is set for TTX\n");
                break;
          #endif

          #if AP_WITH_OSD
            case KEY_1:
            case KEY_2:
            case KEY_3:
            case KEY_4:
            case KEY_5:
            case KEY_6:
            case KEY_7:
            case KEY_8:
            case KEY_9:
            case KEY_0:
            case KEY_MENU:
            case KEY_EPG:
            case KEY_INPUT_SOURCE:
            case KEY_CHANNEL_LIST:
            case KEY_CHANNEL_FAV_LIST:
                enAPEngineState = STATE_APENGINE_WITH_OSD;
                g_bGoBack_AP = TRUE;
                //printf("\nAPENGINE: goBACK is set for OSD\n");
                break;

            case KEY_INFO:
            case KEY_TV_RADIO:
            case KEY_CHANNEL_RETURN:
            case KEY_MTS:
            case KEY_EPGTIMER_COUNTDOWN:
            case KEY_ZOOM:
            case KEY_SLEEP:
            case KEY_AUDIO:
            case KEY_PICTURE:
            case KEY_VOLUME_PLUS:
            case KEY_VOLUME_MINUS:
                g_bPassTV = TRUE;
                //printf("\nAPENGINE: pass key\n");
                break;
          #endif //AP_WITH_OSD

            case KEY_EXIT:
                if (MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY && MApp_ZUI_GetActiveOSD()!=E_OSD_SCREEN_SAVER) //ZUI:
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                    u8KeyCode = KEY_NULL;
                    break;
                }
                else
                {
                    msAPI_APEngine_TransmitKey(KEY_EXIT);
                    MApp_APEngine_Exit();
                    u8KeyCode = KEY_NULL;
                    break;
                }

            case KEY_CHANNEL_PLUS:
            case KEY_CHANNEL_MINUS:
                MApp_UiMenu_MuteWin_Hide();
                MApp_ZUI_ACT_StartupOSD(E_OSD_AUDIO_VOLUME);
                _MApp_APEngine_ProcessAudioVolumeKey(u8KeyCode);
                u8KeyCode = KEY_NULL;

            case KEY_MUTE:
                break;

            case KEY_POWER:
                msAPI_APEngine_TransmitKey(KEY_EXIT);
                MApp_APEngine_Exit();
                enAPEngineRetVal = EXIT_GOTO_STANDBY;
                break;

            case KEY_SELECT:
            case KEY_BLUE:
            case KEY_YELLOW:
            case KEY_GREEN:
            case KEY_RED:
            case KEY_UP:
            case KEY_DOWN:
            case KEY_RIGHT:
            case KEY_LEFT:
            default:
                msAPI_APEngine_TransmitKey(u8KeyCode);
                u8KeyCode = KEY_NULL;
                break;

        }
    }
    else
    {
        switch ( u8KeyCode )
        {
            case KEY_EXIT:
                if (MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY) //ZUI:
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                    u8KeyCode = KEY_NULL;
                    break;
                }
                else
                {
                    MApp_APEngine_HideGWIN();
                    enAPEngineState = STATE_APENGINE_LISTEN;
                    enAPEngineRetVal = EXIT_GOTO_INPUTSOURCE;
                    u8KeyCode = KEY_NULL;
                    break;
                }

            case KEY_INPUT_SOURCE:
                MApp_APEngine_HideGWIN();
                enAPEngineState = STATE_APENGINE_LISTEN;
                enAPEngineRetVal = EXIT_GOTO_INPUTSOURCE;
                u8KeyCode = KEY_NULL;
                break;

            case KEY_POWER:
            case DSC_KEY_PWROFF:
                MApp_APEngine_Exit();
                msAPI_APEngine_TransmitKey(KEY_EXIT);
                enAPEngineRetVal = EXIT_GOTO_STANDBY;
                u8KeyCode = KEY_NULL;
                break;

            case KEY_VOLUME_PLUS:
            case KEY_VOLUME_MINUS:
                MApp_UiMenu_MuteWin_Hide();
                MApp_UiMenu_ARCDeviceStatusWin_Hide();
                MApp_ZUI_ACT_StartupOSD(E_OSD_AUDIO_VOLUME);
                _MApp_APEngine_ProcessAudioVolumeKey(u8KeyCode);
                u8KeyCode = KEY_NULL;

            case KEY_MUTE:  //topstate
                break;

            default:
                msAPI_APEngine_TransmitKey(u8KeyCode);
                u8KeyCode = KEY_NULL;
                break;
        }
    }
}
#endif //#ifndef AP_COWORK

//========================================================================
//  state machine
//========================================================================
void MApp_APEngine_Process(void)
{
  #ifdef MSOS_TYPE_LINUX
    if (!MAdp_IR_IsEnableDaemon())
    {
        // restore g_sleep_ms
        if ((enObamaAppType != E_OBAMA_APP_TYPE_ISOLATED_APP)
            && (pre_enObamaAppType == E_OBAMA_APP_TYPE_ISOLATED_APP))
        {
            extern U32 g_sleep_ms;
            g_sleep_ms = 0;
        }
    }
  #endif

  #if STATE_PRINT
    if (u8KeyCode != KEY_NULL)
    {
        //printf("\nAP:%bx \n", enAPEngineState);
    }
  #endif


#if (DEBUG_APENGINE & DEBUG_AP_STATE)
    static EN_APENGINE_STATE pre_enAPEngineState = 0xFF;
    if(pre_enAPEngineState != enAPEngineState)
    {
        PRINT_DEBUG_INFO
        printf("enAPEngineState[%d]\n", enAPEngineState);
        pre_enAPEngineState = enAPEngineState;
    }
#endif
#if (DEBUG_APENGINE & DEBUG_AP_TYPE)
    if(enObamaAppType != pre_enObamaAppType)
    {
        PRINT_DEBUG_INFO
        printf("enObamaAppType[%d]\n", enObamaAppType);
    }
#endif

    switch ( enAPEngineState )
    {
        //for multitasks loop
        case STATE_APENGINE_LISTEN: // No application is running.
        {
            //waiting loop

            break;
        }


    #ifdef AP_COWORK
        //for coexisting with OSD
      #if AP_WITH_OSD || AP_WITH_TTX
        case STATE_APENGINE_WITH_OSD: // application is running background
        {
            //pass all input keys

            break;
        }
      #endif
    #endif

        case STATE_APENGINE_INIT:
        {
            if ( MApp_APEngine_Init() )
            {
                enAPEngineState = STATE_APENGINE_WAIT;
            }
            else
            {
                enAPEngineState = STATE_APENGINE_NONE;
            }

            break;
        }


        case STATE_APENGINE_NONE:
        {
            enAPEngineState = STATE_APENGINE_LISTEN;

            break;
        }

        case STATE_APENGINE_WAIT:
        {
        #if 0//def ENABLE_MPLAYER_PLUGIN
            if (MDrv_UsbDeviceConnect() && MDrv_GetUsbDeviceType() == USB_INTERFACE_CLASS_HID)
            {
                U16 result;
                //printf("HID mail box!\n");
                result = MDrv_GET_JOYSTICK_STATUS();
                (printf(" send mail :%04x\n", result));
                if (result)
                {
                    msAPI_APEngine_TransmitJoystick(result);
                }
            }
        #endif

            msAPI_APEngine_ProcessMailBox();

            if ( msAPI_APEngine_APP_Finalize_Check()
               ||(_gsMsInitData.b_need_monitor_alive && (!msAPI_APEngine_APP_Alive_Check()))
               )
            {
                MApp_APEngine_Exit();
                //enAPEngineState = STATE_APENGINE_EXIT;
                break;
            }

            if ( u8KeyCode != KEY_NULL )
            {
                /// process key here
                switch(enHandleType)
                {
                    case NONE_HANDLE:
                        //do nothing
                        break;

                    case GAME_HANDLE:
                        _MApp_APEngine_ProcessKey_Game();
                        break;

                    case FULL_HANDLE:
                    default:
                        #ifdef AP_COWORK
                            _MApp_APEngine_ProcessKey_Cowork();
                        #else
                            _MApp_APEngine_ProcessKey_Fullcontrol();
                        #endif
                        break;
                }
            }
            break;
        }


        #if 0
        case STATE_APENGINE_EXIT:
        {
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);

            // wait cape to finalize
            U32 u32TimeStart = msAPI_Timer_GetTime0();
            while ( msAPI_Timer_DiffTimeFromNow(u32TimeStart) < 500 )
            {
                msAPI_APEngine_ProcessMailBox();
                if (msAPI_APEngine_APP_Finalize_Status())
                {
                    break;
                }
            }

            MDrv_BEON_Disable();

            msAPI_Mp3_StopDecode();

            //testing
            msAPI_Scaler_SetBlueScreen(ENABLE, FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            MApi_XC_GenerateBlackVideo(ENABLE);


            // Switch to GOP APP
            U8 u8CurrGOP = MApi_GOP_GWIN_GetCurrentGOP();
            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
            MApi_GOP_GWIN_Enable(APENGINE_GWINID, FALSE);

            MApi_GOP_GWIN_DestroyFB(APENGINE_RT_FBID);
            MApi_GOP_GWIN_EnableTransClr((EN_GOP_TRANSCLR_FMT)0, TRUE);
            MApi_GOP_GWIN_DestroyWin(APENGINE_GWINID);

            //restore stretch
            MApi_GOP_Initialize_StretchWindow(E_GOP_APP);
            MApi_GOP_GWIN_Set_HSCALE(FALSE, 0, 0) ;
            MApi_GOP_GWIN_Set_VSCALE(FALSE, 0, 0) ;

            // restore GOP
            MApi_GOP_GWIN_SwitchGOP(u8CurrGOP);
            MApi_GOP_GWIN_SetFMT0TransClr(COLOR_TRANSPARENT);

            //if AP-COWORK no clear screen but release the keyProcessing
            #ifdef AP_COWORK
            // screen mute
            if( bGoCowork)
            {
                MApp_APEngine_SetAPCowork(FALSE);
                g_bGoBack_AP = FALSE;
                g_bPassTV = FALSE;
                g_bHideAP = FALSE;
            }
            #else
            //Return to TV directly
            msAPI_Scaler_SetBlueScreen(ENABLE, FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            #endif

            //restore MIU
            ///TODO: save original MIU when INIT and restore here
            MDrv_MVOP_MiuSwitch(ENABLE_MIU_1);

            //replace original state "INIT" by "LISTEN"
            //enAPEngineState = STATE_APENGINE_INIT;
            enAPEngineState = STATE_APENGINE_LISTEN;
            enAPEngineRetVal= EXIT_APENGINE_EXIT;

            bRun = FALSE;
            //return enAPEngineRetVal;

        }
        #endif

        default:
            break;

    }

}

#ifdef ENABLE_LOAD_APP_FROM_USB
#include "MApp_TopStateMachine.h"
#include "drvUSB.h"
#include "IOUtil.h"
#include "msAPI_Timer.h"
#include "msAPI_FCtrl.h"
#include "msAPI_FAT.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_Memory.h"
#include "MApp_MassStorage.h"
#include "MApp_ZUI_ACTglobal.h"

#define MAX_APP_FILES 20
#define EXTFILENAME "BIN"
#define EXTFILELEN 3
#define MSTAPPFOLDER "MST_APP"
#define MAX_FILENAME_SIZE    40

typedef struct
{
    U16 filename[MAX_FILENAME_SIZE];
    U8 len;
}ST_APP_FILENAME;
typedef struct
{
    U8 appcounter;
    FileEntry appfileEntry[MAX_APP_FILES];
    ST_APP_FILENAME appfilename[MAX_APP_FILES];
}ST_APP_BROWSE;

static U8    _u8AppUSBEnvironmentID    = 0xFF;
static BOOLEAN  _bAppUsbInitialized    = FALSE;
static ST_APP_BROWSE _st_app_brw;

U8 MApp_GetSuitableFileNum(void)
{
    return _st_app_brw.appcounter;
}

BOOLEAN MApp_GetSuitableFileEntry(U8 idx,FileEntry *pfe)
{
    if(idx>=_st_app_brw.appcounter)
        return FALSE;

    pfe=&(_st_app_brw.appfileEntry[idx]);
    return TRUE;
}

U8 MApp_GetLongFileName(U8 idx,U8 *u8LongFileName)
{
    U8 u8Len;

    printf("get long file name\n");

    if(idx>=_st_app_brw.appcounter)
        return 0;

    u8Len = _st_app_brw.appfilename[idx].len;
    u8Len = (u8Len > (MAX_FILENAME_SIZE)) ?
                MAX_FILENAME_SIZE:
                u8Len;

    memcpy(u8LongFileName,_st_app_brw.appfilename[idx].filename,u8Len*2);

    u8LongFileName[u8Len*2] = 0;
    u8LongFileName[u8Len*2+1] = 0;

    return u8Len;
}

BOOLEAN IsFileExtSuitable(U16 *fn,U8 fnlen,U8 *fext)
{
    U8 len=0,extlen;

    extlen=strlen((char*)fext);
    while(*fn!='.'&&len<fnlen)
    {
        fn++;
        len++;
    }

    if(len>=fnlen)
    {
        printf("can't find suitable ext\n");
        return FALSE;
    }
    else
    {
        fn++;len++;
        if(len+extlen!=fnlen)
            return FALSE;

        while(len<fnlen)
        {
            if(*fn!=*fext)
                return FALSE;
            fn++;fext++;len++;
        }

        printf("ext is suited with source fn\n");
        return TRUE;
    }


}

BOOLEAN MApp_SearchFileInFolder(U8* pu8FileName)
{
    U8  len;
    BOOLEAN result=FALSE;
    FileEntry fe;

    len = strlen((char*)pu8FileName);

    if(len==0)
    {
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChangeToRoot(_u8AppUSBEnvironmentID))
    {
        __ASSERT(0);
        return FALSE;
    }

    if(!msAPI_FCtrl_EntrySearchByShortName(_u8AppUSBEnvironmentID,pu8FileName,len,&fe))
    {
        __ASSERT(0);
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChange(_u8AppUSBEnvironmentID,&fe))
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FCtrl_EntryFirst(_u8AppUSBEnvironmentID);
    _st_app_brw.appcounter=0;
    //printf("start to search file\n");
nextentry:
    while(msAPI_FCtrl_EntryNext(_u8AppUSBEnvironmentID,&(_st_app_brw.appfileEntry[_st_app_brw.appcounter]))==ENTRY_NEXT_RESULT_SUCCESS)
    {
        //U8 i,tmp[MAX_FILENAME_SIZE];
        MDrv_Sys_ClearWatchDog();
        _st_app_brw.appfilename[_st_app_brw.appcounter].len = msAPI_FCtrl_EntryGetCurrentName(_u8AppUSBEnvironmentID, XD2PHY(_st_app_brw.appfilename[_st_app_brw.appcounter].filename), 127);
        #if 0
        printf("current file len %d\n",_st_app_brw.appfilename[_st_app_brw.appcounter].len);
        for(i=0;i<_st_app_brw.appfilename[_st_app_brw.appcounter].len;i++)
        {
            tmp[i]=(U8)(_st_app_brw.appfilename[_st_app_brw.appcounter].filename[i]);
        }
        tmp[_st_app_brw.appfilename[_st_app_brw.appcounter].len]=0;
        printf("get file name %s\n",tmp);
        #endif
        if(IsFileExtSuitable(_st_app_brw.appfilename[_st_app_brw.appcounter].filename,_st_app_brw.appfilename[_st_app_brw.appcounter].len,(U8 *)EXTFILENAME))
        {
            if(_st_app_brw.appcounter<MAX_APP_FILES)
                _st_app_brw.appcounter++;
            else
            {
                result=TRUE;
                break;
            }
        }
        else
            goto nextentry;
    }
    printf("search bin file num %d\n",_st_app_brw.appcounter);
    return result;
}

BOOLEAN MApp_InitUSBAndFs(void)
{
    U32     u32TimeStart = msAPI_Timer_GetTime0();


    // Check USB connection
    while (!MDrv_UsbDeviceConnect())
    {
        U32 u32Duration = msAPI_Timer_DiffTimeFromNow(u32TimeStart);

        if (u32Duration > 2000)
        {
            printf("Connection timeout\n");
            return FALSE;
        }
    }

    // Init USB and file system, ...
    _bAppUsbInitialized = FALSE;
    _u8AppUSBEnvironmentID = 0xFF;

    msAPI_FS_Init();
    msAPI_MSDCtrl_CheckDevices();

    if (msAPI_MSDCtrl_GetDeviceStatus(0)==MSD_STATUS_INSERTED)
    {
        if(msAPI_FCtrl_ActiveDevice(0))
        {
            _u8AppUSBEnvironmentID=msAPI_FSEnv_Register(0x00 /*'A'*/);
            _bAppUsbInitialized=msAPI_FCtrl_DirectoryChangeToRoot(_u8AppUSBEnvironmentID);
        }
    }
    else
    {
        printf("USB DEVICE DETECT ERROR!!\n");
    }

    if (_bAppUsbInitialized)
    {
        return TRUE;
    }
    else
    {
        printf("File system init error\n");
        return FALSE;
    }

    return TRUE;
}

void MApp_DestroyUSBAndFs(void)
{
    printf("exit load game\n");
    if(_bAppUsbInitialized)
    {
        _bAppUsbInitialized = FALSE;
        msAPI_FCtrl_FileHandleResetAll();
        msAPI_FSEnv_UnRegister(_u8AppUSBEnvironmentID);

#if (ENABLE_DMP)
        MApp_MassStorage_DeviceDisconnect();
#else
        msAPI_MSDCtrl_ResetPorts();
#endif

        msAPI_FCtrl_Init();
    }
}
BOOLEAN SearchAppBinInUSB(void)
{
    if(MApp_InitUSBAndFs())
    {
        return MApp_SearchFileInFolder((U8 *)MSTAPPFOLDER);
    }

    return FALSE;
}


BOOLEAN MApp_SearchFileInRoot(U8* pu8FileName, FileEntry* pFileEntry)
{
    U16* pFileNameToCompare=NULL;
    U8  len;
    BOOLEAN result=FALSE;
#ifdef WORDS_LITTLEENDIAN
    U8 *pu8Name;
#endif

    len = strlen((char*)pu8FileName);

    if(len==0)
    {
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChangeToRoot(_u8AppUSBEnvironmentID))
    {
        __ASSERT(0);
        return FALSE;
    }

#ifdef WORDS_LITTLEENDIAN
    pu8Name=(U8*)msAPI_Memory_Allocate(128*2, BUF_ID_USB_DOWNLOAD);
    if(pu8Name==NULL)
    {
        __ASSERT(0);
        return result;
    }

    memset(pu8Name, 0, sizeof(pu8Name));
    memcpy(pu8Name, pu8FileName, strlen((char *)pu8FileName));
    ASCIItoUnicode2((S8 *)pu8Name, strlen((char*)pu8Name));

    pFileNameToCompare=(U16*)msAPI_Memory_Allocate(128*2, BUF_ID_USB_DOWNLOAD);
    if(pFileNameToCompare==NULL)
    {
        if (pu8Name != NULL)
        {
            msAPI_Memory_Free(pu8Name, BUF_ID_USB_DOWNLOAD);
            pu8Name = NULL;
        }
        __ASSERT(0);
        return result;
    }
#else
    pFileNameToCompare=(U16*)msAPI_Memory_Allocate(128*2, BUF_ID_USB_DOWNLOAD);
    if(pFileNameToCompare==NULL)
    {
        __ASSERT(0);
        return result;
    }
#endif

nextentry:
    while(msAPI_FCtrl_EntryNext(_u8AppUSBEnvironmentID,pFileEntry)==ENTRY_NEXT_RESULT_SUCCESS)
    {
        U8 lenToCompare;

        MDrv_Sys_ClearWatchDog();
        lenToCompare = msAPI_FCtrl_EntryGetCurrentName(_u8AppUSBEnvironmentID, XD2PHY(pFileNameToCompare), 127);

        if(lenToCompare==len)
        {
            U8 i;
            for(i=0; i<len; i++)
            {
                U16 c1, c2;

                c1 = pu8FileName[i];
                c2 = pFileNameToCompare[i];

                if ((c1 >= 'a') && (c1 <= 'z'))
                {
                    c1 -= 'a' - 'A';
                }

                if ((c2 >= 'a') && (c2 <= 'z'))
                {
                    c2 -= 'a' - 'A';
                }

                if (c1 != c2 )
                    goto nextentry;
            }

            printf("*Found %s\n", pu8FileName);

            result=TRUE;
            break;
        }
    }
    msAPI_Memory_Free(pFileNameToCompare, BUF_ID_USB_DOWNLOAD);    pFileNameToCompare = NULL;
#ifdef WORDS_LITTLEENDIAN
    msAPI_Memory_Free(pu8Name, BUF_ID_USB_DOWNLOAD);    pu8Name = NULL;
#endif
    return result;
}


BOOLEAN LoadAppbyFileNameFromUSB(U8 *fn)
{
    U8 _u8FileHandle    = FCTRL_INVALID_FILE_HANDLE;
    U32 uPlgSize        = 0;
    U32 uRet            = 1;
    BOOLEAN bRet        = FALSE;
    U32 u32TmpAddr = ((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR)) + CAPE_BUFFER_LEN;
    U8 *pHeader;
    FileEntry fe;

    if(MApp_InitUSBAndFs())
    {
        if(MApp_SearchFileInRoot(fn,&fe))
        {
            if ((_u8FileHandle = msAPI_FCtrl_FileOpen(&fe, OPEN_MODE_FOR_READ)) != FCTRL_INVALID_FILE_HANDLE)
            {
                uPlgSize = msAPI_FCtrl_FileLength(_u8FileHandle);
                __ASSERT(uPlgSize > 0);

                u32TmpAddr = (((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR)) + CAPE_BUFFER_LEN - uPlgSize) & ~(8-1); //8 bytes alignment
                uRet = msAPI_FCtrl_FileRead(_u8FileHandle, u32TmpAddr, uPlgSize);
                __ASSERT(uRet == 0);
            }
            else
            {
                __ASSERT(FALSE);
            }

            msAPI_FCtrl_FileClose(_u8FileHandle);
            MApp_DestroyUSBAndFs();
            //MApp_APEngine_Start();

            pHeader = (U8*) (u32TmpAddr + uPlgSize - 64);
            if (msAPI_APEngine_AppIsHeaderValid(APP_DONT_CARE, pHeader, 64))
            {
                if (msAPI_APEngine_AppIsContentValid((U8*)u32TmpAddr,  uPlgSize))
                {
                    if (msAPI_APEngine_AppRun(u32TmpAddr, uPlgSize, ((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)), BEON_MEM_LEN))
                    {
                        u16nowBIN = 0;
                        enHandleType = NONE_HANDLE;
                        bRet = TRUE;
                    }
                }
            }
        }
    }
    else
        MApp_DestroyUSBAndFs();
    return bRet;

}

BOOLEAN LoadAppBinFromUSB(U8 idx)
{
    U8 _u8FileHandle    = FCTRL_INVALID_FILE_HANDLE;
    U32 uPlgSize        = 0;
    U32 uRet            = 1;
    BOOLEAN bRet        = FALSE;
    U32 u32TmpAddr = ((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR)) + CAPE_BUFFER_LEN;
    U8 *pHeader;

    if(_bAppUsbInitialized&&idx<_st_app_brw.appcounter)
    {
            msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW );
            if ((_u8FileHandle = msAPI_FCtrl_FileOpen(&(_st_app_brw.appfileEntry[idx]), OPEN_MODE_FOR_READ)) != FCTRL_INVALID_FILE_HANDLE)
            {
                uPlgSize = msAPI_FCtrl_FileLength(_u8FileHandle);
                __ASSERT(uPlgSize > 0);

                u32TmpAddr = (((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR)) + CAPE_BUFFER_LEN - uPlgSize) & ~(8-1); //8 bytes alignment
                uRet = msAPI_FCtrl_FileRead(_u8FileHandle, u32TmpAddr, uPlgSize);
                __ASSERT(uRet == 0);
            }
            else
            {
                __ASSERT(FALSE);
            }

            msAPI_FCtrl_FileClose(_u8FileHandle);
            MApp_APEngine_Start();

            pHeader = (U8*) (u32TmpAddr + uPlgSize - 64);
            if (msAPI_APEngine_AppIsHeaderValid(APP_DONT_CARE, pHeader, 64))
            {
                if (msAPI_APEngine_AppIsContentValid((U8*)u32TmpAddr,  uPlgSize))
                {
                    if (msAPI_APEngine_AppRun(u32TmpAddr, uPlgSize, ((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)), BEON_MEM_LEN))
                    {
                        bRet = TRUE;
                    }
                }
            }
    }

    MApp_DestroyUSBAndFs();
    return bRet;
}

#endif


#if 0
#include "mapp_digitalmedia.h"
#include "madp.h"


#if  0  // test code for mm api
//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    MM_CMD_PLAY,
    MM_CMD_PAUSE,
    MM_CMD_RESUME,
    MM_CMD_STOP,
    MM_CMD_FORWARD,
    MM_CMD_BACKWARD,
    MM_CMD_RESTART,
    MM_CMD_NONE = 0xff,
}MM_COMMAND;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
char * pFileName = "/mnt/sda1/video/Ritek_MultiAudio_720x480.avi";
char * pSubtitleFileName = "/mnt/sda1/video/1.srt";
//char * pSubtitleFileName = "/mnt/sda1/video/1.idx";
char * pVobSubFileName = "/mnt/sda1/video/1.sub";
char * pLRCFileName = "/mnt/sda1/music/1.lrc";
static E_MADP_DM_STRM_TYPE egStrmType;
static MADP_DM_STRM_HDL strmHdl[E_MADP_DM_STRM_HDL_MAX];

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------
bool     Verify_MAdp_DigitalMedia_StreamClose(MADP_DM_STRM_HDL dmStrmHdl);
unsigned long         Verify_MAdp_DigitalMedia_StreamRead(MADP_DM_STRM_HDL dmStrmHdl, void *pBuff, unsigned long longSize, E_MADP_DM_STRM_IO_ERR *peIoErr);
bool     Verify_MAdp_DigitalMedia_StreamSeek(MADP_DM_STRM_HDL dmStrmHdl, longlong u64Pos, E_MADP_DM_STRM_IO_ERR *peIoErr);
longlong    Verify_MAdp_DigitalMedia_StreamTell(MADP_DM_STRM_HDL dmStrmHdl);
longlong    Verify_MAdp_DigitalMedia_StreamLength(MADP_DM_STRM_HDL dmStrmHdl);
bool     Verify_MAdp_DigitalMedia_StreamIsClosed(MADP_DM_STRM_HDL dmStrmHdl);
bool     Verify_MAdp_DigitalMedia_StreamIsStopAsked(void);
void        Verify_MAdp_DigitalMedia_EventNotify(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_EVENT eEvent, unsigned long u32Info, unsigned short u16Len);
void Verify_MAdp_DigitalMedia_GetMusicInfo(void);
//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------

unsigned long OpenFile(char * path)
{
    FILE * pStreamHdl;

    // Open file
    pStreamHdl = fopen(path, "r");
    if (pStreamHdl == NULL)
    {
        printf("OpenFile - Open file failed\n");
        free(pStreamHdl);
        return (unsigned long)NULL;
    }

    return (unsigned long)pStreamHdl;
}

bool CloseFile(unsigned long u32StreamHdl)
{
    FILE *pStreamHdl = (FILE *)u32StreamHdl;
    //printf("MAdp_StreamIO_Close - pid: %d\n", getpid());

    if (pStreamHdl == NULL)
    {
        printf("Close - pStreamHdl is NULL\n");
        return FALSE;
    }

    if(fclose(pStreamHdl) == 0)
    {
       return TRUE;
    }
    else
    {
        printf("Close - Close file failed\n");
        return FALSE;
    }

    return TRUE;
}


unsigned long Read(unsigned long u32StreamHdl, void * pBuffer, unsigned long s32Size, E_MADP_DM_STRM_IO_ERR *peIoErr)
{
    int s32NumOfRead = 0;
    FILE *pStreamHdl = (FILE *)u32StreamHdl;

//printf("Read: %ld pBuff:0x%lX u32Size: %ld\n", u32StreamHdl, (unsigned long)pBuffer, s32Size);

    if (pStreamHdl == NULL)
    {
        printf("Read - pStreamHdl is NULL\n");
        return FALSE;
    }
//printf("Pid: %d  - File:%s Line:%u\n", getpid(), __FILE__, __LINE__);

    memset(pBuffer, 0x00, s32Size);
    s32NumOfRead = fread(pBuffer, 1, s32Size, pStreamHdl);
    if(s32NumOfRead == 0)
    {
        if (ferror(pStreamHdl))
        {
            printf("Read - Read file failed\n");
        }

        if (feof(pStreamHdl))
        {
            printf("Read - EOF of stream\n");
        }
    }

    // for debuging used
    #if 0
    {
        int i;
        unsigned char *pBuf = (unsigned char *)pVirBuffer;
        printf("\n\nMAdp_StreamIO_Read()\n");
        for (i = 0; i <128; ++i)
        {
            if ((i != 0) && (i % 16 == 0))
                printf("\n");
            printf("%02x ", pBuf[i]);
        }
    }
    #endif

    // return un-read number
    s32NumOfRead = s32Size - s32NumOfRead;


    //printf("pid:%d  s32NumOfRead: %d\n", getpid(), s32NumOfRead);
    *peIoErr = E_MADP_DM_STRM_IO_NO_ERROR;
    return s32NumOfRead;
}

bool Seek(unsigned long u32StreamHdl, longlong s64Pos, E_MADP_DM_STRM_IO_ERR *peIoErr)
{
    bool bResult = FALSE;
    FILE *pStreamHdl = (FILE *)u32StreamHdl;
    //printf("Seek - pid: %d, s64Pos: %ld\n", getpid(), s64Pos);
    long long llPos;
    llPos = s64Pos.Lo;

    if (pStreamHdl == NULL)
    {
        printf("Seek - pStreamHdl is NULL\n");
        return FALSE;
    }

    // set to absolute position
    if(fseek(pStreamHdl, llPos, SEEK_SET) == 0)
    {
        bResult = TRUE;
    }
    else
    {
        printf("Seek - Seek the stream failed\n");
        return FALSE;
    }


    *peIoErr = E_MADP_DM_STRM_IO_NO_ERROR;
    return bResult;
}

longlong Tell(unsigned long u32StreamHdl)
{
    longlong ll64Pos;
    long lPos;
    FILE *pStreamHdl = (FILE *)u32StreamHdl;

    memset(&ll64Pos, 0x00, sizeof(longlong));

    if (pStreamHdl == NULL)
    {
        printf("Tell - pStreamHdl is NULL\n");
    }


    lPos = ftell(pStreamHdl);
    if(lPos == -1)
    {
        printf("Tell - Tell the stream failed\n");
    }

    ll64Pos.Lo = lPos;
    return ll64Pos;
}

longlong Length(unsigned long u32StreamHdl)
{
    long s64Pos;
    long s64Length = -1;

    longlong lResult;
    FILE *pStreamHdl = (FILE *)u32StreamHdl;

    memset(&lResult, 0x00, sizeof(longlong));

    if (pStreamHdl == NULL)
    {
        printf("Length - pStreamHdl is NULL\n");
        return lResult;
    }


    s64Pos = ftell(pStreamHdl);
    if(s64Pos == -1)
    {
        printf("Length - Tell the stream failed (CUR)\n");
    }
    else
    {
        // seek to the end
        if(fseek(pStreamHdl, 0, SEEK_END) == 0)
        {
            // get the position and position is the length
            s64Length = ftell(pStreamHdl);
            if(s64Length == -1)
            {
                printf("Length - Tell the stream failed (END)\n");
            }

            // seek to original pos
            if(fseek(pStreamHdl, s64Pos, SEEK_SET) == -1)
            {
                printf("Length - Seek the stream to Current pos failed\n");
            }
        }
        else
        {
            printf("Length - Seek the stream to End failed\n");
        }
    }

    lResult.Lo = s64Length;

    return lResult;
}

bool Verify_MAdp_DigitalMedia_Play(char * path)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    E_MADP_DM_STRM_ATTRIB eStrmAttrib;
    MADP_DM_STRM_IO strmIoFunc;
    ST_MADP_DM_RECT stViewRet;
    bool bRet;
    bool bTestSubtitle = TRUE;
    bool bTestVobSub = FALSE;
    bool bTestLRC = TRUE;

    // verify movie/music
    // init handle
    // NOTE: unused handle should be set to INVALID_MADP_DM_STRM_HDL
    if(egStrmType == E_MADP_DM_STRM_TYPE_MOVIE)
    {
        strmHdl[E_MADP_DM_STRM_HDL_VIDEO]    = OpenFile(path);
        strmHdl[E_MADP_DM_STRM_HDL_AUDIO]    = OpenFile(path);
        strmHdl[E_MADP_DM_STRM_HDL_IN_SUB]   = OpenFile(path);
        if(bTestSubtitle)
        {
            strmHdl[E_MADP_DM_STRM_HDL_EX_SUB_0] = OpenFile(pSubtitleFileName);
            if(bTestVobSub)
            {
                strmHdl[E_MADP_DM_STRM_HDL_EX_SUB_1] = OpenFile(pVobSubFileName);
                //need set external subtitle firstly.
                MAdp_DigitalMedia_SetExternalSubtitleType(E_MADP_DM_SUBTITLE_SUBIDX);
            }
            else
            {
                MAdp_DigitalMedia_SetExternalSubtitleType(E_MADP_DM_SUBTITLE_SRT);
                strmHdl[E_MADP_DM_STRM_HDL_EX_SUB_1] = INVALID_MADP_DM_STRM_HDL;
            }
        }
        else
        {
            strmHdl[E_MADP_DM_STRM_HDL_EX_SUB_0] = INVALID_MADP_DM_STRM_HDL;
            strmHdl[E_MADP_DM_STRM_HDL_EX_SUB_1] = INVALID_MADP_DM_STRM_HDL;
        }
    }
    else if(egStrmType == E_MADP_DM_STRM_TYPE_MUSIC)
    {
        //need two file handle for music.
        strmHdl[E_MADP_DM_STRM_HDL_MUSIC]    = OpenFile(path);
        strmHdl[E_MADP_DM_STRM_HDL_MUSIC2]    = OpenFile(path);

        //set LRC file handle
        if(bTestLRC)
            strmHdl[E_MADP_DM_STRM_HDL_LYRIC]   =  OpenFile(pLRCFileName);
        else
            strmHdl[E_MADP_DM_STRM_HDL_LYRIC]   = INVALID_MADP_DM_STRM_HDL;

        //need set music type firstly
        MAdp_DigitalMedia_SetMusicType(E_MADP_DM_MUSIC_MP3);
    }

    // init type and atrribute
    eStrmType = egStrmType;
    eStrmAttrib = E_MADP_DM_STRM_ATTR_SEEKABLE;

    // init stream I/O callback function
    strmIoFunc.pfnClose         = Verify_MAdp_DigitalMedia_StreamClose;
    strmIoFunc.pfnRead          = Verify_MAdp_DigitalMedia_StreamRead;
    strmIoFunc.pfnSeek          = Verify_MAdp_DigitalMedia_StreamSeek;
    strmIoFunc.pfnTell          = Verify_MAdp_DigitalMedia_StreamTell;
    strmIoFunc.pfnLength        = Verify_MAdp_DigitalMedia_StreamLength;
    strmIoFunc.pfnIsClosed      = Verify_MAdp_DigitalMedia_StreamIsClosed;
    strmIoFunc.pfnIsStopAsked   = Verify_MAdp_DigitalMedia_StreamIsStopAsked;
    strmIoFunc.pfnNotify        = Verify_MAdp_DigitalMedia_EventNotify;

    // init moudle
    bRet = MAdp_DigitalMedia_Init(strmHdl, eStrmType, eStrmAttrib, &strmIoFunc);

    if(bRet == TRUE && (egStrmType == E_MADP_DM_STRM_TYPE_MUSIC))
    {
        Verify_MAdp_DigitalMedia_GetMusicInfo();
    }
    // set view window
    if (0)
    {
        stViewRet.u16Width  = 1920;
        stViewRet.u16Height = 1080;
        stViewRet.u16X = 0;
        stViewRet.u16Y = 0;
    }
    else
    {
        MAdp_DigitalMedia_GetView(eStrmType, &stViewRet);
    }
    MAdp_DigitalMedia_SetView(eStrmType, TRUE, &stViewRet); // force full screen
//    MAdp_DigitalMedia_SetView(eStrmType, FALSE, &stViewRet); // use preview window
    // playback
    return MAdp_DigitalMedia_Play(eStrmType);
}

void Verify_MAdp_DigitalMedia_Stop(void)
{
    // stop playback
    MAdp_DigitalMedia_Stop(egStrmType);
}

void Verify_MAdp_DigitalMedia_Pause(void)
{
    // pause playback
    MAdp_DigitalMedia_Pause(egStrmType);
}

void Verify_MAdp_DigitalMedia_Resume(void)
{
    MAdp_DigitalMedia_Resume(egStrmType);
}

void Verify_MAdp_DigitalMedia_ChangeProgram(bool bNext)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    unsigned long u32TotalTrack;
    unsigned char u8TrackId;

    // init type
    eStrmType = E_MADP_DM_STRM_TYPE_MOVIE;

    // change program
    u32TotalTrack = MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_NB_PROGRAM);
    if (u32TotalTrack > 1)
    {
        u8TrackId = MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_PROGRAM_IDX);
        printf("video program: %d --> ", u8TrackId);

        if (bNext)
        {
            u8TrackId++;
        }
        else
        {
            u8TrackId--;
        }

        if (u8TrackId == 0xff)
        {
            u8TrackId = u32TotalTrack - 1;
        }
        else
        {
            u8TrackId %= u32TotalTrack;
        }
        printf("%d\n", u8TrackId);

        MAdp_DigitalMedia_ChangeProgram(eStrmType, u8TrackId);
    }
    else
    {
        printf("%s, test failed\n", __FUNCTION__);
        printf("total track: %ld\n", u32TotalTrack);
    }
}

void Verify_MAdp_DigitalMedia_ChangeAudio(void)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    unsigned long u32TotalTrack;
    unsigned char u8TrackId;

    // init type
    eStrmType = E_MADP_DM_STRM_TYPE_MOVIE;

    // change audio
    u32TotalTrack = MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_NB_AUDIO_TRACK);
    if (u32TotalTrack > 1)
    {
        u8TrackId = MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_AUDIO_TRACK_IDX);
        printf("audio track: %d --> ", u8TrackId);

        u8TrackId += 1;
        u8TrackId %= u32TotalTrack;
        printf("%d\n", u8TrackId);

        MAdp_DigitalMedia_ChangeAudio(eStrmType, u8TrackId);
    }
    else
    {
        printf("%s, test failed\n", __FUNCTION__);
        printf("total track: %ld\n", u32TotalTrack);
    }
}

void Verify_MAdp_DigitalMedia_ChangeSubtitle(void)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    unsigned long u32TotalTrack;
    unsigned char u8TrackId;

    // init type
    eStrmType = E_MADP_DM_STRM_TYPE_MOVIE;

    // change subtitle
    u32TotalTrack = MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_NB_SUBTITLE_TRACK);
    if (u32TotalTrack > 1)
    {
        u8TrackId = MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_SUBTITLE_TRACK_IDX);
        printf("subtitle track: %d --> ", u8TrackId);

        u8TrackId += 1;
        u8TrackId %= u32TotalTrack;
        printf("%d\n", u8TrackId);

        MAdp_DigitalMedia_ChangeSubtitle(eStrmType, u8TrackId);
    }
    else
    {
        printf("%s, test failed\n", __FUNCTION__);
        printf("total track: %ld\n", u32TotalTrack);
    }
}

void Verify_MAdp_DigitalMedia_GotoTime(unsigned long u32Ms)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    unsigned long u32TotalTimeMs;

    // init type
    eStrmType = E_MADP_DM_STRM_TYPE_MOVIE;

    // check total time
    u32TotalTimeMs = MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_TOTAL_TIME);

    // goto specific time
    if (u32TotalTimeMs > u32Ms)
    {
        printf("time change from %ld --> %ld\n", MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_CUR_TIME), u32Ms);
        MAdp_DigitalMedia_GotoTime(eStrmType, u32Ms);
    }
    else
    {
        printf("%s, test failed\n", __FUNCTION__);
        printf("total time: %ld, goto: %ld\n", u32TotalTimeMs, u32Ms);
    }
}

void Verify_MAdp_DigitalMedia_TrickMode(unsigned char u8Cmd)
{
    E_MADP_DM_PLAY_MODE eCurrentPlayMode, eNewPlayMode;
    E_MADP_DM_SPEED eCurrentSpeed, eNewSpeed;


    // get current trick play info
    if (MAdp_DigitalMedia_GetTrickMode(egStrmType, &eCurrentPlayMode, &eCurrentSpeed) == FALSE)
    {
        printf("%s, test failed\n", __FUNCTION__);
        printf("get current trick play info fail.\n");
        return;
    }

    // change play mode
    switch (u8Cmd)
    {
        case 0:
            // Fast Forward
            eNewPlayMode = E_MADP_DM_PLAY_MODE_FAST_FORWARD;
            break;

        case 1:
            // Fast Backward
            eNewPlayMode = E_MADP_DM_PLAY_MODE_FAST_BACKWORD;
            break;

        case 2:
            // Slow Forward
            // NOTE: fall through because slow forward is supported after t3/u3, not t2.
            // break;
        default:
            printf("%s, test failed\n", __FUNCTION__);
            printf("trick mode cmd (%d) isn't supported.\n", u8Cmd);
            return;
    }

    // change speed
    eNewSpeed = (E_MADP_DM_SPEED)((eCurrentSpeed + 1) % E_MADP_DM_SPEED_MAX);

    // re-check play mode for normal play
    if (eNewSpeed == E_MADP_DM_SPEED_X1)
    {
        eNewPlayMode = E_MADP_DM_PLAY_MODE_NORMAL;
    }

    if (MAdp_DigitalMedia_SetTrickMode(egStrmType, eNewPlayMode, eNewSpeed) == TRUE)
    {
        printf("change trick mode from (%d, %d) to (%d, %d).\n", eCurrentPlayMode, eCurrentSpeed, eNewPlayMode, eNewSpeed);
    }
    else
    {
        printf("%s, test failed\n", __FUNCTION__);
        printf("set trick mode (%d, %d) fail.\n", eNewPlayMode, eNewSpeed);
    }
}

void Verify_MAdp_DigitalMedia_RepeatAB(void)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    E_MADP_DM_REPEAT_AB eCurrentRepeatAct, eNextRepeatAct;

    // init type
    eStrmType = E_MADP_DM_STRM_TYPE_MOVIE;

    // get current repeat AB setting
    if (MAdp_DigitalMedia_GetRepeatAB(eStrmType, &eCurrentRepeatAct) == FALSE)
    {
        printf("%s, test failed\n", __FUNCTION__);
        printf("get current repeatAB fail.\n");
        return;
    }

    // send repeat A/B/None
    switch (eCurrentRepeatAct)
    {
        case E_MADP_DM_REPEAT_NONE:
            // set A
            eNextRepeatAct = E_MADP_DM_REPEAT_A;
            break;

        case E_MADP_DM_REPEAT_A:
            // set B
            eNextRepeatAct = E_MADP_DM_REPEAT_B;
            break;

        case E_MADP_DM_REPEAT_B:
            // set None
            eNextRepeatAct = E_MADP_DM_REPEAT_NONE;
            break;

        default:
            printf("%s, test failed\n", __FUNCTION__);
            printf("current repeat act (%d) isn't correct.\n", eCurrentRepeatAct);
            return;
    }

    if (MAdp_DigitalMedia_SetRepeatAB(eStrmType, eNextRepeatAct) == TRUE)
    {
        printf("set repeat %s at %ldms.\n",
        eNextRepeatAct == E_MADP_DM_REPEAT_NONE ? "NONE" : (eNextRepeatAct == E_MADP_DM_REPEAT_A ? "A" : "B"),
                MAdp_DigitalMedia_GetInfo(eStrmType, E_MADP_DM_INFO_CUR_TIME));
    }
    else
    {
        printf("%s, test failed\n", __FUNCTION__);
        printf("set repeat mode fail.\n");
    }
}

void Verify_MAdp_DigitalMedia_Zoom(char s8ZoomDiff)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    E_MADP_DM_ZOOM eZoom;

    // init type
    eStrmType = E_MADP_DM_STRM_TYPE_MOVIE;

    if (MAdp_DigitalMedia_GetZoom(eStrmType, &eZoom) == FALSE)
    {
        printf("%s, get setting failed\n", __FUNCTION__);
        return;
    }

    eZoom = (E_MADP_DM_ZOOM)(((unsigned char)eZoom + s8ZoomDiff) % (unsigned char)E_MADP_DM_ZOOM_MAX);

    // for movie, E_MADP_DM_ZOOM_1_DIV_8 isn't supported
    if (eZoom == E_MADP_DM_ZOOM_1_DIV_8)
    {
        if (s8ZoomDiff > 0)
        {
            eZoom = E_MADP_DM_ZOOM_1_DIV_4;
        }
        else
        {
            eZoom = E_MADP_DM_ZOOM_8;
        }
    }

    // test zoom
    if (MAdp_DigitalMedia_SetZoom(eStrmType, eZoom) == FALSE)
    {
        printf("%s, test failed\n", __FUNCTION__);
    }
}

void Verify_MAdp_DigitalMedia_Rotate(void)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    E_MADP_DM_ROTATION eRotate;

    // init type
    eStrmType = E_MADP_DM_STRM_TYPE_MOVIE;

    if (MAdp_DigitalMedia_GetRotation(eStrmType, &eRotate) == FALSE)
    {
        printf("%s, get setting failed\n", __FUNCTION__);
        return;
    }

    eRotate = (E_MADP_DM_ROTATION)(((unsigned char)eRotate + 1) % (unsigned char)E_MADP_DM_ROTATION_MAX);

    // test zoom
    if (MAdp_DigitalMedia_SetRotation(eStrmType, eRotate) == FALSE)
    {
        printf("%s, test failed\n", __FUNCTION__);
    }
}

void Verify_MAdp_DigitalMedia_Move(unsigned char u8Direction)
{
    E_MADP_DM_STRM_TYPE eStrmType;
    E_MADP_DM_DIRECTION eDirection;
    unsigned short u16Distance = 16;

    // init type
    eStrmType = E_MADP_DM_STRM_TYPE_MOVIE;

    // transform direction
    switch (u8Direction)
    {
        case 0:
            eDirection = E_MADP_DM_DIRECTION_UP;
            break;

        case 1:
            eDirection = E_MADP_DM_DIRECTION_DOWN;
            break;

        case 2:
            eDirection = E_MADP_DM_DIRECTION_LEFT;
            break;

        case 3:
            eDirection = E_MADP_DM_DIRECTION_RIGHT;
            break;

        default:
            return;
    }

    // test zoom
    if (MAdp_DigitalMedia_MoveView(eStrmType, eDirection, u16Distance) == FALSE)
    {
        printf("%s, test failed\n", __FUNCTION__);
    }
}
void Verify_MAdp_DigitalMedia_GetMusicInfo(void)
{

    unsigned long u32Len;
    unsigned char u8Buf[512]={0};

    u32Len = MAdp_DigitalMedia_GetInfo(E_MADP_DM_STRM_TYPE_MUSIC, E_MADP_DM_INFO_MUSIC_LAYER_LEN);
    if(u32Len>0)
    {
        memset(u8Buf,0,sizeof(u8Buf));
        MAdp_DigitalMedia_GetMusicInfo(E_MADP_DM_INFO_MUSIC_LAYER, u8Buf, (unsigned short) u32Len);
        printf("Layer:%s\n",u8Buf);
    }


    u32Len = MAdp_DigitalMedia_GetInfo(E_MADP_DM_STRM_TYPE_MUSIC, E_MADP_DM_INFO_MUSIC_BITRATE_LEN);
    if(u32Len>0)
    {
        memset(u8Buf,0,sizeof(u8Buf));
        MAdp_DigitalMedia_GetMusicInfo(E_MADP_DM_INFO_MUSIC_BITRATE, u8Buf, (unsigned short) u32Len);
        printf("bitrate:%s\n",u8Buf);
    }

    u32Len = MAdp_DigitalMedia_GetInfo(E_MADP_DM_STRM_TYPE_MUSIC, E_MADP_DM_INFO_MUSIC_SAMPLINGRATE_LEN);
    if(u32Len>0)
    {
        memset(u8Buf,0,sizeof(u8Buf));
        MAdp_DigitalMedia_GetMusicInfo(E_MADP_DM_INFO_MUSIC_SAMPLINGRATE, u8Buf, (unsigned short) u32Len);
        printf("samplerate:%s\n",u8Buf);
    }

    u32Len = MAdp_DigitalMedia_GetInfo(E_MADP_DM_STRM_TYPE_MUSIC, E_MADP_DM_INFO_MUSIC_ALBUM_LEN);
    if(u32Len>0)
    {
        memset(u8Buf,0,sizeof(u8Buf));
        MAdp_DigitalMedia_GetMusicInfo(E_MADP_DM_INFO_MUSIC_ALBUM, u8Buf, (unsigned short) u32Len);
        printf("album:%s\n",u8Buf);
    }

    u32Len = MAdp_DigitalMedia_GetInfo(E_MADP_DM_STRM_TYPE_MUSIC, E_MADP_DM_INFO_MUSIC_TITLE_LEN);
    if(u32Len>0)
    {
        memset(u8Buf,0,sizeof(u8Buf));
        MAdp_DigitalMedia_GetMusicInfo(E_MADP_DM_INFO_MUSIC_TITLE, u8Buf, (unsigned short) u32Len);
        printf("title:%s\n",u8Buf);
    }
    //more...

}
//-------------------------------------------------------------------------------------------------
// Local funcion -- misc functions
//-------------------------------------------------------------------------------------------------
bool Verify_MAdp_DigitalMedia_StreamClose(MADP_DM_STRM_HDL dmStrmHdl)
{
    return CloseFile((unsigned long)dmStrmHdl);
}

unsigned long Verify_MAdp_DigitalMedia_StreamRead(MADP_DM_STRM_HDL dmStrmHdl, void *pBuff, unsigned long u32Size, E_MADP_DM_STRM_IO_ERR *peIoErr)
{
    return Read((unsigned long)dmStrmHdl, pBuff, u32Size, peIoErr);
}

bool Verify_MAdp_DigitalMedia_StreamSeek(MADP_DM_STRM_HDL dmStrmHdl, longlong u64Pos, E_MADP_DM_STRM_IO_ERR *peIoErr)
{
    return Seek((unsigned long)dmStrmHdl, u64Pos, peIoErr);
}

longlong Verify_MAdp_DigitalMedia_StreamTell(MADP_DM_STRM_HDL dmStrmHdl)
{
    return Tell((unsigned long)dmStrmHdl);
}

longlong Verify_MAdp_DigitalMedia_StreamLength(MADP_DM_STRM_HDL dmStrmHdl)
{
    return Length((unsigned long)dmStrmHdl);
}

bool Verify_MAdp_DigitalMedia_StreamIsClosed(MADP_DM_STRM_HDL dmStrmHdl)
{
    // for testing, do nothing
    UNUSED(dmStrmHdl);

    return FALSE;
}

bool Verify_MAdp_DigitalMedia_StreamIsStopAsked(void)
{
    // for testing, do nothing
    return FALSE;
}

void Verify_MAdp_DigitalMedia_EventNotify(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_EVENT eEvent, unsigned long u32Info, unsigned short u16Len)
{
#if 1
    printf("Event received...\n");

    UNUSED(u32Info);
    UNUSED(u16Len);
    switch (eType)
    {
        case E_MADP_DM_STRM_TYPE_MOVIE:
            printf("\ttype --> MOVIE\n");

            printf("\tevent\n");
            switch (eEvent)
            {
                case E_MADP_DM_EVENT_PLAYING_TIME_TICK:
                    printf("\t\tPlay Time: %ld(ms)/%ld(ms)\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_CUR_TIME), MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_TOTAL_TIME));
                    break;

                case E_MADP_DM_EVENT_INFO_OK:
                    printf("\t\tWidth: %ld\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_H_SIZE));
                    printf("\t\tHeight: %ld\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_V_SIZE));

                    printf("\t\tfps: %ld\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_FRM_PER_SEC));
                    printf("\t\ttotal time : %ld(ms)\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_TOTAL_TIME));

                    printf("\t\tprogram: (%ld/%ld)\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_PROGRAM_IDX), MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_NB_PROGRAM));
                    printf("\t\taudio track: (%ld/%ld)\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_AUDIO_TRACK_IDX), MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_NB_AUDIO_TRACK));
                    printf("\t\tsubtitle track: (%ld/%ld)\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_SUBTITLE_TRACK_IDX), MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_NB_SUBTITLE_TRACK));
                    break;

                case E_MADP_DM_EVENT_STOP_NORMALLY:
                    printf("\t\tStop normally\n");
                    break;

                case E_MADP_DM_EVENT_STOP_ABNORMALLY:
                    printf("\t\tStop abnormally\n");
                    break;

                case E_MADP_DM_EVENT_SHOW_MOVIE_SUBTITLE:
                    if(u32Info!=0) //it is unicode , need convert.
                        printf("\t\tShow subtitle:%s,len:%d\n",(unsigned char*)u32Info,u16Len);
                    else
                        printf("\t\tshow subtitle error\n");
                    break;

                case E_MADP_DM_EVENT_HIDE_MOVIE_SUBTITLE:
                    printf("\t\tHide subtitle.\n");
                    break;

                default:
                    printf("UNKNOWN (%d)\n", eEvent);
                    break;
            }
            break;

        case E_MADP_DM_STRM_TYPE_PHOTO:
            printf("\ttype --> PHOTO\n");
            break;

        case E_MADP_DM_STRM_TYPE_MUSIC:
            printf("\ttype --> MUSIC\n");
            switch (eEvent)
            {
                case E_MADP_DM_EVENT_PLAYING_TIME_TICK:
                    printf("\t\tPlay Time: %ld(ms)\n", MAdp_DigitalMedia_GetInfo(eType, E_MADP_DM_INFO_CUR_TIME));
                    break;

                case E_MADP_DM_EVENT_SHOW_LYRIC:
                    printf("\t\tshow lyric:%s,len:%d\n",(unsigned char*)u32Info,u16Len);
                    break;

                case E_MADP_DM_EVENT_HIDE_LYRIC:
                    printf("\t\tHide lyric.\n");
                    break;

                default:
                    printf("UNKNOWN (%d)\n", eEvent);
                    break;
            }
            break;

        default:
            printf("\ttype --> UNKNOWN (%d)\n", eType);
            break;
    }
#endif
    return;
}


void process_mm_command(MM_COMMAND enMMCmd)
{
        switch (enMMCmd)
        {
            case MM_CMD_PLAY:
            {
                printf("PLAY\n");
                Verify_MAdp_DigitalMedia_Play(pFileName);
                break;
            }

            case MM_CMD_PAUSE:
            {
                printf("PAUSE\n");
                Verify_MAdp_DigitalMedia_Pause();
                break;
            }

            case MM_CMD_RESUME:
            {
                printf("RESUME\n");
                Verify_MAdp_DigitalMedia_Resume();
                break;
            }

            case MM_CMD_STOP:
            {
                printf("STOP\n");
                Verify_MAdp_DigitalMedia_Stop();
                break;
            }

            case MM_CMD_FORWARD:
            {
                printf("FORWARD\n");
                Verify_MAdp_DigitalMedia_TrickMode(0);
                break;
            }

            case MM_CMD_BACKWARD:
            {
                printf("BACKWARD\n");
                Verify_MAdp_DigitalMedia_TrickMode(1);
                break;
            }

            case MM_CMD_RESTART:
            {
                printf("RESTART\n");
                Verify_MAdp_DigitalMedia_GotoTime(0);
                break;
            }

            default:
                break;
        }

}

bool IrCB(unsigned char u8Key, unsigned char u8RepeatFlag)
{
    bool bResult = true;
    MM_COMMAND enMMCmd = MM_CMD_NONE;
    printf("IrCB: 0x%02X, 0x%02X\n", u8Key, u8RepeatFlag);
    u8RepeatFlag = u8RepeatFlag;
    switch (u8Key)
    {
        case KEY_PLAY:
            enMMCmd = MM_CMD_PLAY;
            break;

        case KEY_PAUSE:
            enMMCmd = MM_CMD_PAUSE;
            break;

        case KEY_RECORD:
            enMMCmd = MM_CMD_RESUME;
            break;

        case KEY_STOP:
            enMMCmd = MM_CMD_STOP;
            break;

        case KEY_FF:
             enMMCmd = MM_CMD_FORWARD;
            break;

        case KEY_REWIND:
            enMMCmd = MM_CMD_BACKWARD;
            break;

        case KEY_INFO:
            enMMCmd = MM_CMD_RESTART;
            break;

        default:
            bResult = false;
    }

    process_mm_command(enMMCmd);

    return bResult;
}

void Verify_MAdp_DigitalMedia_SetFilePath(char * file, E_MADP_DM_STRM_TYPE streamType)
{
    egStrmType = streamType;
    pFileName = file;
}


#endif

static bool MApp_DM_ModuleInit(void)
{
    return MApp_DigitalMedia_ModuleInit();
}

static bool MApp_DM_Init(MADP_DM_STRM_HDL *pStreamHdl, E_MADP_DM_STRM_TYPE eType, E_MADP_DM_STRM_ATTRIB eAttrib, MADP_DM_STRM_IO *pfnCallbacks)
{
#if 1
    return MApp_DigitalMedia_Init((DM_STRM_HDL*)pStreamHdl, (E_DM_STRM_TYPE)eType, (E_DM_STRM_ATTRIB)eAttrib, (DM_STRM_IO*)pfnCallbacks);
#else // for testing used
    E_MADP_DM_STRM_IO_ERR eIoErr;
    U32 u32Timer;
    longlong llLength;
    longlong llPos;
    int i;
    int count = 100;

    u32Timer = msAPI_Timer_GetTime0();
    for (i = 0; i < count; ++i)
        llLength = pfnCallbacks->pfnLength(pStreamHdl[0]);
    printf("Length average time: %d ms. llLength: %d\n", msAPI_Timer_DiffTimeFromNow(u32Timer)/count, llLength.Lo);

    u32Timer = msAPI_Timer_GetTime0();
    for (i = 0; i < count; ++i)
        llPos = pfnCallbacks->pfnTell(pStreamHdl[0]);
    printf("Tell average time: %d ms. llPos: %d\n", msAPI_Timer_DiffTimeFromNow(u32Timer)/count, llPos.Lo);

    u32Timer = msAPI_Timer_GetTime0();
    for (i = 0; i < count; ++i)
        pfnCallbacks->pfnRead(pStreamHdl[0], (void*)0x4000000, 8192, &eIoErr);
    printf("Read average time: %d ms\n", msAPI_Timer_DiffTimeFromNow(u32Timer)/count);

    u32Timer = msAPI_Timer_GetTime0();
    for (i = 0; i < count; ++i)
        pfnCallbacks->pfnSeek(pStreamHdl[0], llLength, &eIoErr);
    printf("Seek average time: %d ms\n", msAPI_Timer_DiffTimeFromNow(u32Timer)/count);

    u32Timer = msAPI_Timer_GetTime0();
    for (i = 0; i < count; ++i)
        llPos = pfnCallbacks->pfnTell(pStreamHdl[0]);
    printf("Tell average time: %d ms. llPos: %ld\n", msAPI_Timer_DiffTimeFromNow(u32Timer)/count, llPos.Lo);


    {
        U8 j;
        U8* pBuf = (U8*)MsOS_PA2KSEG1(0x4000000);
        printf("Data\n");
        for (j = 0; j < 128; j++)
        {
            printf("%02x ", pBuf[j]);
        }
        printf("\n\n");
    }
    return true;
#endif
}

static bool MApp_DM_Play(E_MADP_DM_STRM_TYPE eType)
{
    return MApp_DigitalMedia_Play((E_DM_STRM_TYPE)eType);
}

static void MApp_DM_Stop(E_MADP_DM_STRM_TYPE eType)
{
    MApp_DigitalMedia_Stop((E_DM_STRM_TYPE)eType);
}

static bool MApp_DM_Pause(E_MADP_DM_STRM_TYPE eType)
{
    return MApp_DigitalMedia_Pause((E_DM_STRM_TYPE)eType);
}

static bool MApp_DM_Resume(E_MADP_DM_STRM_TYPE eType)
{
    return MApp_DigitalMedia_Resume((E_DM_STRM_TYPE)eType);
}

static bool MApp_DM_ChangeProgram(E_MADP_DM_STRM_TYPE eType, unsigned char u8TrackIdx)
{
    return MApp_DigitalMedia_ChangeProgram((E_DM_STRM_TYPE)eType, (U8)u8TrackIdx);
}

static bool MApp_DM_ChangeAudio(E_MADP_DM_STRM_TYPE eType, unsigned char u8TrackIdx)
{
    return MApp_DigitalMedia_ChangeAudio((E_DM_STRM_TYPE)eType, (U8)u8TrackIdx);
}

static bool MApp_DM_ChangeSubtitle(E_MADP_DM_STRM_TYPE eType, unsigned char u8TrackIdx)
{
    return MApp_DigitalMedia_ChangeSubtitle((E_DM_STRM_TYPE)eType, (U8)u8TrackIdx);
}

static bool MApp_DM_ChangeExternalSubtitle(E_MADP_DM_SUBTITLE_TYPE eSubtitleType,MADP_DM_STRM_HDL SubtitleHdl,MADP_DM_STRM_HDL SubStreamHdl)
{
    return MApp_DigitalMedia_ChangeExternalSubtitle((E_DM_SUBTITLE_TYPE)eSubtitleType,(DM_STRM_HDL)SubtitleHdl,(DM_STRM_HDL)SubStreamHdl);
}

static void MApp_DM_SetExternalSubtitleType(E_MADP_DM_SUBTITLE_TYPE eType)
{
    MApp_DigitalMedia_SetExternalSubtitleType((E_DM_SUBTITLE_TYPE)eType);
}

static bool MApp_DM_EnableSubtitle(void)
{
    return MApp_DigitalMedia_EnableSubtitle();
}

static bool MApp_DM_DisableSubtitle(void)
{
    return MApp_DigitalMedia_DisableSubtitle();
}

static bool MApp_DM_GotoTime(E_MADP_DM_STRM_TYPE eType, unsigned long u32TimeInMs)
{
    return MApp_DigitalMedia_GotoTime((E_DM_STRM_TYPE)eType, (U32)u32TimeInMs);
}

static bool MApp_DM_SetTrickMode(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_PLAY_MODE ePlayMode, E_MADP_DM_SPEED eSpeed)
{
    return MApp_DigitalMedia_SetTrickMode((E_DM_STRM_TYPE)eType, (E_DM_PLAY_MODE)ePlayMode, (E_DM_SPEED)eSpeed);
}

static bool MApp_DM_GetTrickMode(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_PLAY_MODE *pePlayMode, E_MADP_DM_SPEED *peSpeed)
{
    return MApp_DigitalMedia_GetTrickMode((E_DM_STRM_TYPE)eType, (E_DM_PLAY_MODE *)pePlayMode, (E_DM_SPEED *)peSpeed);
}

static bool MApp_DM_SetRepeatAB(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_REPEAT_AB eRepeatAct)
{
    return MApp_DigitalMedia_SetRepeatAB((E_DM_STRM_TYPE)eType, (E_DM_REPEAT_AB)eRepeatAct);
}

static bool MApp_DM_GetRepeatAB(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_REPEAT_AB *peRepeatAct)
{
    return MApp_DigitalMedia_GetRepeatAB((E_DM_STRM_TYPE)eType, (E_DM_REPEAT_AB *)peRepeatAct);
}

static bool MApp_DM_GetView(E_MADP_DM_STRM_TYPE eType, ST_MADP_DM_RECT *pstViewWin)
{
    bool bResult;

    bResult =  MApp_DigitalMedia_GetView((E_DM_STRM_TYPE)eType, (ST_DM_RECT *) pstViewWin);

    printf("MApp_DM_GetView\n");
    printf("pstViewWin->u16Width:%d\n", pstViewWin->u16Width);
    printf("pstViewWin->u16Height:%d\n", pstViewWin->u16Height);
    printf("pstViewWin->u16X:%d\n", pstViewWin->u16X);
    printf("pstViewWin->u16Y:%d\n", pstViewWin->u16Y);

    return bResult;
}

static bool MApp_DM_SetView(E_MADP_DM_STRM_TYPE eType, bool bFullScreen, ST_MADP_DM_RECT *pstViewWin)
{
    bool bResult;

    printf("MApp_DM_SetView\n");
    printf("pstViewWin->u16Width:%d\n", pstViewWin->u16Width);
    printf("pstViewWin->u16Height:%d\n", pstViewWin->u16Height);
    printf("pstViewWin->u16X:%d\n", pstViewWin->u16X);
    printf("pstViewWin->u16Y:%d\n", pstViewWin->u16Y);
    printf("bFullScreen:d\n", bFullScreen);

    bResult =  MApp_DigitalMedia_SetView((E_DM_STRM_TYPE)eType, (BOOLEAN) bFullScreen, (ST_DM_RECT *) pstViewWin);
    return bResult;
}

static bool MApp_DM_GetRotation(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_ROTATION *peRotate)
{
    return MApp_DigitalMedia_GetRotation((E_DM_STRM_TYPE) eType, (E_DM_ROTATION *) peRotate);
}

static bool MApp_DM_SetRotation(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_ROTATION eRotate)
{
    return MApp_DigitalMedia_SetRotation((E_DM_STRM_TYPE) eType, (E_DM_ROTATION) eRotate);
}

static bool MApp_DM_GetZoom(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_ZOOM *peZoom)
{
    return MApp_DigitalMedia_GetZoom((E_DM_STRM_TYPE) eType, (E_DM_ZOOM *) peZoom);
}

static bool MApp_DM_SetZoom(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_ZOOM eZoom)
{
    return MApp_DigitalMedia_SetZoom((E_DM_STRM_TYPE) eType, (E_DM_ZOOM) eZoom);
}

static bool MApp_DM_MoveView(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_DIRECTION eDirection, unsigned short u16Offset)
{
    return MApp_DigitalMedia_MoveView((E_DM_STRM_TYPE) eType, (E_DM_DIRECTION) eDirection, (U16) u16Offset);
}

static unsigned long  MApp_DM_Photo_GetFreeSlot(void)
{
    return MApp_DigitalMedia_Photo_GetFreeSlot();
}

static bool MApp_DM_Photo_StopDisplay(void)
{
    return MApp_DigitalMedia_Photo_StopDisplay();
}

static bool MApp_DM_Photo_SlideShow(bool bEnable)
{
    return MApp_DigitalMedia_Photo_SlideShow((BOOLEAN) bEnable);
}

static bool MApp_DM_Photo_SlideShowTimeOut(unsigned short u16TimeOutInSec)
{
    return MApp_DigitalMedia_Photo_SlideShowTimeOut((U16) u16TimeOutInSec);
}

static unsigned long MApp_DM_GetInfo(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_INFO enInfo)
{
    return MApp_DigitalMedia_GetInfo((E_DM_STRM_TYPE) eType, (E_DM_INFO) enInfo);
}

static bool MApp_DM_SetDRMKey(unsigned char *pu8Key, unsigned long u32Size)
{
    return MApp_DigitalMedia_SetDRMKey((U8*)pu8Key, (U32)u32Size);
}

// music API
static bool MApp_DM_SetMusicType(E_MADP_DM_MUSIC_TYPE enMusicType)
{
    return MApp_DigitalMedia_SetMusicType((E_DM_MUSIC_TYPE)enMusicType);
}

static bool MApp_DM_EnableLRCLyric(void)
{
    return MApp_DigitalMedia_EnableLRCLyric();
}

static bool MApp_DM_DisableLRCLyric(void)
{
    return MApp_DigitalMedia_DisableLRCLyric();
}

static bool MApp_DM_IsCurrentLRCLyricAvail(void)
{
    return MApp_DigitalMedia_IsCurrentLRCLyricAvail();
}

static bool MApp_DM_GetMusicInfo(E_MADP_DM_INFO enInfo, unsigned char* pBuf, unsigned short u16Len)
{
    return MApp_DigitalMedia_GetMusicInfo((E_DM_INFO)enInfo, (U8*) pBuf, (U16)u16Len);
}

static bool MApp_DM_GetDoubleBufInfo(E_MADP_DM_STRM_TYPE eType, unsigned long* pu32DoubleBuffAddr, unsigned long* pu32DoubleBufSize)
{
    return MApp_DigitalMedia_Get_DoubleBufInfo((E_DM_STRM_TYPE) eType, (U32*) pu32DoubleBuffAddr, (U32*) pu32DoubleBufSize);
}

static void MApp_DM_FillDoubleBufDone(E_MADP_DM_STRM_TYPE eType, unsigned char u8BufIndex, unsigned long u32Len, bool bFileEnd)
{
    MApp_DigitalMedia_Fill_DoubleBufDone((E_DM_STRM_TYPE) eType, (U8) u8BufIndex, (U32) u32Len, (BOOLEAN) bFileEnd);
}

static bool MApp_DM_EnableEvent(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_EVENT eEvent)
{
    return MApp_DigitalMedia_EnableEvent((E_DM_STRM_TYPE) eType, (E_DM_EVENT)eEvent);
}

static bool MApp_DM_DisableEvent(E_MADP_DM_STRM_TYPE eType, E_MADP_DM_EVENT eEvent)
{
    return MApp_DigitalMedia_DisableEvent((E_DM_STRM_TYPE) eType, (E_DM_EVENT)eEvent);
}

bool MApp_DM_Wrapped_Init(void)
{
    MADP_DM_PLAYER_CB FunCB;
    memset(&FunCB, 0x00, sizeof(MADP_DM_PLAYER_CB));

    // set the cb for each functions
    FunCB.ModuleInit = MApp_DM_ModuleInit;
    FunCB.Init = MApp_DM_Init;
    FunCB.Play = MApp_DM_Play;
    FunCB.Stop = MApp_DM_Stop;
    FunCB.Pause = MApp_DM_Pause;
    FunCB.Resume = MApp_DM_Resume;
    FunCB.ChangeProgram = MApp_DM_ChangeProgram;
    FunCB.ChangeAudio = MApp_DM_ChangeAudio;
    FunCB.ChangeSubtitle = MApp_DM_ChangeSubtitle;
    FunCB.ChangeExternalSubtitle = MApp_DM_ChangeExternalSubtitle;
    FunCB.SetExternalSubtitleType = MApp_DM_SetExternalSubtitleType;
    FunCB.EnableSubtitle = MApp_DM_EnableSubtitle;
    FunCB.DisableSubtitle = MApp_DM_DisableSubtitle;
    FunCB.GotoTime = MApp_DM_GotoTime;
    FunCB.SetTrickMode = MApp_DM_SetTrickMode;
    FunCB.GetTrickMode = MApp_DM_GetTrickMode;
    FunCB.SetRepeatAB = MApp_DM_SetRepeatAB;
    FunCB.GetRepeatAB = MApp_DM_GetRepeatAB;
    FunCB.GetView = MApp_DM_GetView;
    FunCB.SetView = MApp_DM_SetView;
    FunCB.GetRotation = MApp_DM_GetRotation;
    FunCB.SetRotation = MApp_DM_SetRotation;
    FunCB.GetZoom = MApp_DM_GetZoom;
    FunCB.SetZoom = MApp_DM_SetZoom;
    FunCB.MoveView = MApp_DM_MoveView;
    FunCB.Photo_GetFreeSlot = MApp_DM_Photo_GetFreeSlot;
    FunCB.Photo_StopDisplay = MApp_DM_Photo_StopDisplay;
    FunCB.Photo_SlideShow = MApp_DM_Photo_SlideShow;
    FunCB.Photo_SlideShowTimeOut = MApp_DM_Photo_SlideShowTimeOut;
    FunCB.GetInfo = MApp_DM_GetInfo;
    FunCB.SetDRMKey = MApp_DM_SetDRMKey;
    FunCB.SetMusicType = MApp_DM_SetMusicType;
    FunCB.EnableLRCLyric = MApp_DM_EnableLRCLyric;
    FunCB.DisableLRCLyric = MApp_DM_DisableLRCLyric;
    FunCB.IsCurrentLRCLyricAvail = MApp_DM_IsCurrentLRCLyricAvail;
    FunCB.GetMusicInfo = MApp_DM_GetMusicInfo;
    FunCB.GetDoubleBufInfo = MApp_DM_GetDoubleBufInfo;
    FunCB.FillDoubleBufDone = MApp_DM_FillDoubleBufDone;
    FunCB.EnableEvent = MApp_DM_EnableEvent;
    FunCB.DisableEvent = MApp_DM_DisableEvent;

    return MAdp_DigitalMedia_RegisterPlayerCallback(&FunCB);
}
#endif


#endif //#if (ENABLE_CAPE)


#undef _MAPP_APENGINE_C_
