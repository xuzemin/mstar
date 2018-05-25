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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    apiXC_Ext.c
/// @brief  Scaler API layer Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_XC_SYS_C_
#define _API_XC_SYS_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"

#include <string.h>

// Common Definition
#include "MsCommon.h"
#include "MsTypes.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "debug.h"
#include "assert.h"

// Common
#include "drvGlobal.h"
#include "Utl.h"
#include "sysinfo.h"
#include "BinInfo.h"
#include "SysInit.h"


// Driver
#include "hal_misc.h"
#include "drvAUDIO.h"
#include "DemoFineTune.h"
#include "apiXC.h"
#include "drvPQ.h"
#include "drvPQ_Define.h"
#include "apiXC_Adc.h"
#include "drvXC_HDMI_if.h"
#include "drvSYS.h"
#include "drvPM.h"
#include "drvBDMA.h"
#include "drvIIC.h"

#include "drvTVEncoder.h"

#include "color.h"
#include "color_reg.h"
#include "drvGPIO.h"        // for Panel VCC control
#include "GPIO.h"

// API
#include "apiXC_Sys.h"
#include "apiXC_Ace.h"
#include "apiXC_Dlc.h"
#include "apiXC_PCMonitor.h"
#include "apiXC_Hdmi.h"
#include "apiXC_Adc.h"
#include "apiXC_Auto.h"
#include "msAPI_MIU.h"

#include "Panel.h"
#include "apiPNL.h"

#if ENABLE_TCON
// include TCON table.
#include "pnl_tcon_tbl.h"
#include "pnl_tcon_tbl.c"
#endif

#if ENABLE_TCON_2014
#include "msAPI_TCON.h"
#endif
#if( ENABLE_OD_BIN )
#include "msAPI_OverDrive.h"
#endif

//MHL
#if (ENABLE_MHL == ENABLE)
#include "msAPI_MHL.h"
#endif

#include "msAPI_Video.h"
#include "msAPI_Timer.h"
#include "apiXC_ModeParse.h"

//CEC
#if ENABLE_CEC
#include "msAPI_CEC.h"
#endif

#if ENABLE_DLC
#include "apiXC_Dlc.h"
#endif

#if ENABLE_DBC
#include "apiXC_DBC.h"
#include "drvPWM.h"
#endif

#include "msAPI_BDMA.h"
#include "msAPI_Ram.h"
#include "msAPI_Mode.h"
#include "msAPI_NR.h"
#include "msAPI_MailBox.h"
#include "msAPI_CPU.h"

#if ENABLE_PQ_BIN
#include "msAPI_Memory.h"
#endif

#if ENABLE_DYNAMIC_EDID
#include "msAPI_Dynamic_EDID.h"
#endif

#if LD_ENABLE
#include "msAPI_LD.h"
#endif


#include "MApp_MVDMode.h"

#include "MApp_BlockSys.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_GlobalVar.h"


#if (HDCP_KEY_TYPE==HDCP_KEY_IN_DB||HDCP22_KEY_TYPE==HDCP22_KEY_IN_DB)
#include "MApp_DataBase.h"
#endif

#include "MApp_SaveData.h"

#if(ENABLE_6M40_4KX2K_PROCESS)
#include "drvUrsa6M40.h"
#endif

#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

#include "MApp_InputSource.h"
#if ENABLE_TCON_IN8903_PROCESS
#include "drvTcon_Inx8903.h"
#endif

#if ENABLE_SECURITY_R2_HDCP22
#include "msAPI_SecurityR2.h"
#include  "MApp_Customer_Hdcpkey22.c"
#endif

#include "MApp_Customer_Hdcpkey14.c"

#if (ENABLE_DDC_RAM)
#include "MApp_Edid_Table.h"
#endif
#include "MApp_Scaler.h"

#if ENABLE_GAMMA_ADJUST
#include "MApp_GammaAdjust.h"
#endif

#if( ENABLE_CEC )
#include "MApp_Main.h"
#endif


#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------
#if( HDMI_HPD_INVERT_FLAG_SEPERATE )
    #ifndef HDCP_HPD_2_INVERSE
        #define HDCP_HPD_2_INVERSE  HDCP_HPD_INVERSE
    #endif
    #ifndef HDCP_HPD_3_INVERSE
        #define HDCP_HPD_3_INVERSE  HDCP_HPD_INVERSE
    #endif
    #ifndef HDCP_HPD_4_INVERSE
        #define HDCP_HPD_4_INVERSE  HDCP_HPD_INVERSE
    #endif
#endif

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define VD_CHECK_HSYNC_LOCKED           BIT14

// 60Hz => 1000/60=17ms/frame
// 50Hz => 1000/50=20ms/frame
// 30Hz => 1000/30=33ms/frame
// 24Hz => 1000/40=41ms/frame
#define PC_MODE_SYNC_STABLE_TIME        60  // ms
#define PC_MODE_NOSYNC_TIME             40  // ms,

#define HDMI_SYNC_STABLE_TIME           60  // ms
#define HDMI_NOSYNC_TIME                30//40  // ms

#define PC_MODE_SYNC_STABLE_COUNT       (PC_MODE_SYNC_STABLE_TIME/PC_MODE_TIMING_MONITOR_PERIOD)
#define PC_MODE_NOSYNC_COUNT            (PC_MODE_NOSYNC_TIME/PC_MODE_TIMING_MONITOR_PERIOD)

#define HDMI_SYNC_STABLE_COUNT          (HDMI_SYNC_STABLE_TIME/PC_MODE_TIMING_MONITOR_PERIOD)
#define HDMI_NOSYNC_COUNT               (HDMI_NOSYNC_TIME/PC_MODE_TIMING_MONITOR_PERIOD)

//--------------------------------------------------------------------------------------
#define ENALBE_XC_ISR_SAMPLE        0

#define ENABLE_XC_ISR_OPVSYNC       1

#define ENABLE_XC_ISR_IPVSYNC       0

//--------------------------------------------------------------------------------------

#ifndef ENABLE_PQ_BIN_EX
    #define ENABLE_PQ_BIN_EX    ENABLE_PQ_BIN
#endif

//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------
typedef enum
{
    EN_WSS_4x3_FULL                    = 0x08,
    EN_WSS_14x9_LETTERBOX_CENTER       = 0x01,
    EN_WSS_14x9_LETTERBOX_TOP          = 0x02,
    EN_WSS_16x9_LETTERBOX_CENTER       = 0x0B,
    EN_WSS_16x9_LETTERBOX_TOP          = 0x04,
    EN_WSS_ABOVE16x9_LETTERBOX_CENTER  = 0x0D,
    EN_WSS_14x9_FULL_CENTER            = 0x0E,
    EN_WSS_16x9_ANAMORPHIC              = 0x07,
}EN_VE_WSS_TYPE;

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

#define CVBSOUT_NUM_MAX 2

static E_VE_MUTE_STATUS s_eVEMuteStatus[CVBSOUT_NUM_MAX] = {E_VE_MUTE_INVALID, E_VE_MUTE_INVALID};


#if (ENABLE_VE == ENABLE)
static MS_U8 s_eVEBlackScreenStatus = 0xFF;
//For feature of "SetVE" as request.
static MS_BOOL s_bForceVEOutputenable = FALSE;
static MS_VE_VIDEOSYS s_eVideoSystem = MS_VE_VIDEOSYS_NUM;
#endif //(ENABLE_VE == ENABLE)

static /*E_SCREEN_MUTE_STATUS*/U32 s_eScreenMuteStatus[2] = {E_SCREEN_MUTE_INIT,E_SCREEN_MUTE_INIT};
static MS_BOOL bSrcIsHD[2];     // Daten FixMe, MAX_WINDOW will be removed and can be obtained from MApi_XC_GetInfo()

static const MS_U32  astFreeRunColor[] =
{
    // a, R, G, B
    0x00000000UL,   // E_XC_FREE_RUN_COLOR_BLACK
    0x00FFFFFFUL,   // E_XC_FREE_RUN_COLOR_WHITE
    0x000000FFUL,   // E_XC_FREE_RUN_COLOR_BLUE
    0x00FF0000UL,   // E_XC_FREE_RUN_COLOR_RED
    0x0000FF00UL,   // E_XC_FREE_RUN_COLOR_GREEN
};

static const MS_U8  astNoSignalColor[] =
{
    0x00, // E_XC_FREE_RUN_COLOR_BLACK
    0xFF, // E_XC_FREE_RUN_COLOR_WHITE
    0x03, // E_XC_FREE_RUN_COLOR_BLUE
    0xE0, // E_XC_FREE_RUN_COLOR_RED
    0x1C, // E_XC_FREE_RUN_COLOR_GREEN
};
static const MS_U8  astNoSignalColorDAC[] =
{
    0x82, // E_XC_FREE_RUN_COLOR_BLACK
    0x9E, // E_XC_FREE_RUN_COLOR_WHITE
    0xE8, // E_XC_FREE_RUN_COLOR_BLUE
    0x11, // E_XC_FREE_RUN_COLOR_RED
    0x67, // E_XC_FREE_RUN_COLOR_GREEN
};


#define HDMI_PORT_NUM_MAX   4

static E_MUX_INPUTPORT eHdmiPortMappingResult[HDMI_PORT_NUM_MAX] =
{
    INPUT_PORT_NONE_PORT,
    INPUT_PORT_NONE_PORT,
    INPUT_PORT_NONE_PORT,
    INPUT_PORT_NONE_PORT,
};

#if( ENABLE_EDID_SWITCH)
EnuXcHdmiEdidSel g_XC_Sys_au8EdidSel[HDMI_PORT_NUM_MAX] = {XC_HDMI_EDID_1p4, XC_HDMI_EDID_1p4, XC_HDMI_EDID_1p4, XC_HDMI_EDID_1p4};
#endif

#if ENABLE_TCON
static BOOL g_bIsUsingTconTable;
static BOOL g_bIsGammaSettingBySW;
#endif

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------
#define MSG(x)  // x

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
static void _MApi_XC_Sys_InputSource_InputPort_Mapping(INPUT_SOURCE_TYPE_t src_ids , E_MUX_INPUTPORT* port_ids , MS_U8* u8port_count )
{
    // prog input soruce
    switch (src_ids)
    {
        default:
            *u8port_count = 0;
            port_ids[0] = INPUT_PORT_NONE_PORT;
            return;

        case INPUT_SOURCE_VGA:
            *u8port_count = 2;
            port_ids[0] = INPUT_VGA_MUX;
            port_ids[1] = INPUT_VGA_SYNC_MUX;
            break;

#if (INPUT_YPBPR_VIDEO_COUNT >=1)
        case INPUT_SOURCE_YPBPR:
            *u8port_count = 1;
            port_ids[0] = INPUT_YPBPR_MUX;
            break;
#endif

#if (INPUT_YPBPR_VIDEO_COUNT >=2)
        case INPUT_SOURCE_YPBPR2:
            *u8port_count = 1;
            port_ids[0] = INPUT_YPBPR2_MUX;
            break;
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_HDMI:
            *u8port_count = 1;
            port_ids[0] = INPUT_HDMI1_MUX;
            break;
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_HDMI2:
            *u8port_count = 1;
            port_ids[0] = INPUT_HDMI2_MUX;
            break;
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 3)
        case INPUT_SOURCE_HDMI3:
            *u8port_count = 1;
            port_ids[0] = INPUT_HDMI3_MUX;
            break;
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 4)
        case INPUT_SOURCE_HDMI4:
            *u8port_count = 1;
            port_ids[0] = INPUT_HDMI4_MUX;
            break;
#endif

        case INPUT_SOURCE_TV:
            *u8port_count = 1;
            port_ids[0] = INPUT_TV_YMUX;
            break;

#if (INPUT_AV_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_CVBS:
            *u8port_count = 1;
            port_ids[0] = INPUT_AV_YMUX;
            break;
#endif

#if (INPUT_AV_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_CVBS2:
            *u8port_count = 1;
            port_ids[0] = INPUT_AV2_YMUX;
            break;
#endif

#if (INPUT_AV_VIDEO_COUNT >= 3)
        case INPUT_SOURCE_CVBS3:
            *u8port_count = 1;
            port_ids[0] = INPUT_AV3_YMUX;
            break;
#endif

#if ((INPUT_SV_VIDEO_COUNT >= 1)||ENABLE_SCART_SVIDEO)
        case INPUT_SOURCE_SVIDEO:
            *u8port_count = 2;
            port_ids[0] = INPUT_SV_YMUX;
            port_ids[1] = INPUT_SV_CMUX;
            break;
#endif

#if (INPUT_SV_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_SVIDEO2:
            *u8port_count = 2;
            port_ids[0] = INPUT_SV2_YMUX;
            port_ids[1] = INPUT_SV2_CMUX;
            break;
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_SCART:
            *u8port_count = 2;
            port_ids[0] = INPUT_SCART_RGBMUX;
            port_ids[1] = INPUT_SCART_YMUX;
            break;
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_SCART2:
            *u8port_count = 2;
            port_ids[0] = INPUT_SCART2_RGBMUX;
            port_ids[1] = INPUT_SCART2_YMUX;
            break;
#endif
        case INPUT_SOURCE_DTV:
            *u8port_count = 1;
            port_ids[0] = INPUT_PORT_MVOP;
            break;

#if ((ENABLE_DMP) || (DISPLAY_LOGO))
        case INPUT_SOURCE_STORAGE:
            *u8port_count = 1;
            port_ids[0] = INPUT_PORT_MVOP;
            break;
#endif
    }
    //printf(" app : port 0 : %d  port 1 : %d \n",  port_ids[0]  , port_ids[1]);
}

U8 MApi_XC_Sys_Get_HdmiPortNumMax(void)
{
#if( INPUT_HDMI_VIDEO_COUNT > HDMI_PORT_NUM_MAX )
    #error "INPUT_HDMI_VIDEO_COUNT > HDMI_PORT_NUM_MAX"
#endif

    U8 u8HdmiPortNumMax = HDMI_PORT_NUM_MAX;

    if( u8HdmiPortNumMax > INPUT_HDMI_VIDEO_COUNT )
    {
        u8HdmiPortNumMax = INPUT_HDMI_VIDEO_COUNT;
    }

    return u8HdmiPortNumMax;
}

#if ENABLE_TCON

#define PNL_TCON_DBG(x)         //x
#define ENABLE_TCON_GAMMA_IC    1


MS_U16 eTCONPNL_TypeSel = 0;

#define I2C_DEV_GAMMA_IC 0xE8

#if ENABLE_TCON_GAMMA_IC

static MS_U8 tInitializeDAC[]=
{
     0x83,0xCF,
     0x83,0xB6,
     0x83,0x2F,
     0x82,0xC3,
     0x82,0x86,
     0x82,0x24,
     0x82,0x23,
     0x81,0xF4,
     0x81,0xF6,
     0x81,0x50,
     0x81,0x14,
     0x80,0xBA,
     0x80,0x2D,
     0x80,0x13,
     0x80,0x28,
     0x80,0x0E,
};

static MS_U8 tInitializeVCOM[]=
{
     0x81,0xB1,
     0x81,0xB1,
};

static void devPanel_InitGammaIC(void)
{
    MS_U8 u8Addr;

    u8Addr = 0x00;
    MDrv_IIC_WriteBytes(I2C_DEV_GAMMA_IC, 1, &u8Addr, sizeof(tInitializeDAC), tInitializeDAC);

    u8Addr = 0x12;
    MDrv_IIC_WriteBytes(I2C_DEV_GAMMA_IC, 1, &u8Addr, sizeof(tInitializeVCOM), tInitializeVCOM);
}
#endif

static void _MApi_XC_Sys_Init_TCON_GAMMA(MS_U16 u16BusNumSlaveID, MS_U8 *ptcontab)
{
    MS_U16 u16timeout = 0x3FF;
    MS_U16 u16Addr;
    MS_U32 u32tabIdx = 0;
    MS_U8 u8value[2];
    MS_U8 u8Addr;
    //MS_U16 u16BusNumSlaveID;

//    u16BusNumSlaveID = (0x0100 | (MS_U16) I2C_DEV_GAMMA_IC );
    //u16BusNumSlaveID = ( (MS_U16) I2C_DEV_GAMMA_IC );

    /*PNL_TCON_DBG*/(printf(">> _MApi_XC_Sys_Init_TCON_GAMMA(0x%x) \n", u16BusNumSlaveID));

    while (--u16timeout)
    {
        u16Addr = (ptcontab[u32tabIdx]<<8) + ptcontab[(u32tabIdx +1)];

        if ((g_PNL_TypeSel == TCON_PNL_WXGA_IPS_ALPHA_AH080A016G_Hisense)||
            (g_PNL_TypeSel == TCON_PNL_FULLHD_AUO_T420HW09))
        {
            u8value[0] = ptcontab[(u32tabIdx +3)];
            u8value[1] = ptcontab[(u32tabIdx +2)];
        }
        else
        {
        u8value[0] = ptcontab[(u32tabIdx +2)];
        u8value[1] = ptcontab[(u32tabIdx +3)];
        }

        u8Addr = ptcontab[(u32tabIdx +1)];

        if (u16Addr == REG_TABLE_END) // check end of table
            break;

        PNL_TCON_DBG(printf("GMA:[addr=%04lx, val=%02x, %02x] \n", u8Addr, u8value[0], u8value[1]));
        MDrv_IIC_WriteBytes(u16BusNumSlaveID, 1, &u8Addr, 2, u8value);
        u32tabIdx = u32tabIdx + 4;
    }
}

static void _MApi_TCon_Tab_DumpPSRegTab(MS_U8* pu8TconTab)
{
#define TCON_DUMP_TIMEOUT_TIME  1000
    MS_U32 u32tabIdx = 0;
    MS_U32 u32Addr;
    MS_U16 u16Mask;
    MS_U16 u16Value;
    MS_U8 u8NeedDelay;
    MS_U8 u8DelayTime;
    //MS_U8 u8signal_type = 0;
    MS_U32 u32StartTime = MsOS_GetSystemTime();


    if (pu8TconTab == NULL)
    {
        printf("pu8TconTab is NULL! at %s %u \n", __FUNCTION__, __LINE__);
        return;
    }

    while(1)
    {
        if( (MsOS_GetSystemTime() - u32StartTime) > TCON_DUMP_TIMEOUT_TIME )
        {
            printf("Dump tcon tab timeout! at %s %u \n", __FUNCTION__, __LINE__);
            return;
        }

        u32Addr = ((pu8TconTab[u32tabIdx]<<8) + pu8TconTab[(u32tabIdx +1)]) & 0xFFFF;
        u16Mask  = pu8TconTab[(u32tabIdx +2)] & 0xFF;
        u16Value = pu8TconTab[(u32tabIdx +3)] & 0xFF;
        u8NeedDelay = pu8TconTab[(u32tabIdx +4)] & 0xFF;
        u8DelayTime = pu8TconTab[(u32tabIdx +5)] & 0xFF;
        //u8signal_type = pu8TconTab[(u32tabIdx +6)];

        if (u32Addr == REG_TABLE_END) // check end of table
            break;

        //printf("Dump Gen [addr=%04lx, msk=%02x, val=%02x,delay=%u,u8DelayTime=%u\n", u32Addr,u16Mask,u16Value,u8NeedDelay,u8DelayTime);

        u32Addr = (u32Addr | 0x100000);

        if( u32Addr == REG_TC_TCON_BASE )
        {
            printf("Wait V sync \n");
            MApi_XC_WaitOutputVSync(1, 50, MAIN_WINDOW);
        }

        {
            //printf("Wait t=%lu\n", MsOS_GetSystemTime());

        #if 1 // Don't use xc write byte driver!
            MDrv_WriteByteMask(u32Addr, u16Value, u16Mask);
        #else
            if (u32Addr & 0x1)
            {
                u32Addr --;
                MApi_XC_Write2ByteMask(u32Addr, (u16Value << 8), (u16Mask << 8));
                PNL_TCON_DBG(printf("[addr=%04lx, msk=%02x, val=%02x] \n", u32Addr, (u16Mask << 8), (u16Value << 8)));
            }
            else
            {
                MApi_XC_Write2ByteMask(u32Addr, u16Value, u16Mask);
                PNL_TCON_DBG(printf("[addr=%04lx, msk=%02x, val=%02x] \n", u32Addr, u16Mask, u16Value));
            }
        #endif

        }

        // Check need delay?
        if( u8NeedDelay && u8DelayTime )
        {
            MsOS_DelayTask(u8DelayTime);
            //printf("delay=%u, t=%lu\n", u8DelayTime, MsOS_GetSystemTime());
        }

        u32tabIdx = u32tabIdx + 7;
    }
}

typedef struct
{
    U32 u32RegAddr;
    U16 u16Mask;
    U16 u16Value[4];
} StuSetPanelDirection;

StuSetPanelDirection tSetPanelDirection_PVI050VX1_SVGA_PD050SX1_TTL[] =
{   //                     L_R__U_D, R_L__U_D, L_R__D_U, R_L__D_U,
    { 0x00101E60, 0x0300, {  0x0000,   0x0000,   0x0000,  0x0000} }, // OEN
    { 0x00101E5E, 0x0300, {  0x0200,   0x0000,   0x0300,  0x0100} },
    { 0x001030C2, 0x00C6, {  0x00C0,   0x0082,   0x0044,  0x0006} }, // TCON
    { 0xFFFFFFFF, 0x0000, {  0x0000,   0x0000,   0x0000,  0x0000} }, // Table end
};


StuSetPanelDirection tSetPanelDirection_PVI058OX1_WXGA_PD058OX1_MINILVDS[] =
{   //                     L_R__U_D, R_L__U_D, L_R__D_U, R_L__D_U,
    { 0x00101E60, 0x0300, {  0x0000,   0x0000,   0x0000,  0x0000} }, // OEN
    { 0x00101E5E, 0x0300, {  0x0200,   0x0000,   0x0300,  0x0100} },

    { 0x00103000, 0x00FF, {  0x0000,   0x0000,   0x0000,  0x0000} }, // Switch bank to 0
    { 0x001030C2, 0x00C6, {  0x00C0,   0x0082,   0x0044,  0x0006} },

    { 0x00103000, 0x00FF, {  0x0001,   0x0001,   0x0001,  0x0001} }, // Switch bank to 1
    { 0x00103028, 0xFFFF, {  0x0000,   0x3453,   0x0000,  0x3453} }, // even odd ch swap
    { 0x0010302A, 0xFFFF, {  0x0000,   0x1200,   0x0000,  0x1200} }, // even odd ch swap

    { 0xFFFFFFFF, 0x0000, {  0x0000,   0x0000,   0x0000,  0x0000} }, // Table end
};

void MApi_XC_TCON_Panel_SetPanelDirection( EnuPanelDirection panelDirection )
{
    StuSetPanelDirection* pSetPanelDirection = NULL;

    PNL_TCON_DBG(printf(">> %s (%u) \n", __FUNCTION__, panelDirection));

    switch (eTCONPNL_TypeSel)
    {
        case TCON_PANEL_PVI058OX1:
            pSetPanelDirection = tSetPanelDirection_PVI058OX1_WXGA_PD058OX1_MINILVDS;
            break;

        case TCON_PANEL_PVI050VX1:
        case TCON_PANEL_PVI035VX2:
            pSetPanelDirection = tSetPanelDirection_PVI050VX1_SVGA_PD050SX1_TTL;
            break;

        default:
            break;
    }

    if ( pSetPanelDirection != NULL )
    {
        U8 i = 0;
        while(1)
        {
            if( pSetPanelDirection->u32RegAddr == 0xFFFFFFFF )
                break;

            //printf("Set %lX=%X, mask=%X\n", pSetPanelDirection->u32RegAddr, pSetPanelDirection->u16Value[panelDirection], pSetPanelDirection->u16Mask);
            //MApi_XC_Write2ByteMask( pSetPanelDirection->u32RegAddr, pSetPanelDirection->u16Value[panelDirection], pSetPanelDirection->u16Mask);

            MDrv_Write2ByteMask( pSetPanelDirection->u32RegAddr, pSetPanelDirection->u16Value[panelDirection], pSetPanelDirection->u16Mask);

            pSetPanelDirection ++;

            ++ i;
            if( i > 100 )
            {
                printf("Fatal Error! Panel direction table is error!\n");
                break;
            }
        }
    }
}

//static void _MApi_XC_Sys_Init_TCON_Panel(void)
static void _MApi_XC_Sys_Init_TCON_Panel(TCON_TAB_INFO* pTcontab)
{
    PNL_TCON_DBG(printf("_MApi_XC_Sys_Init_TCON_Panel(): eTCONPNL_TypeSel=%u \n", eTCONPNL_TypeSel));

    //TCON_TAB_INFO* pTcontab;
    //pTcontab = &(TConMAP_Main[eTCONPNL_TypeSel]);


    //MApi_PNL_SetDbgLevel(0x0001);

    // TCON init
    MApi_PNL_TCON_Init();
    //printf("%s %u\n", __FUNCTION__, __LINE__);

    // dump TCON general register tab
    MApi_PNL_TCONMAP_DumpTable(pTcontab->pTConInitTab, E_APIPNL_TCON_TAB_TYPE_GENERAL);
    //printf("%s %u\n", __FUNCTION__, __LINE__);

    // dump TCON scaler register tab
    //MApi_PNL_TCONMAP_DumpTable(pTcontab->pTConInit_SCTab, E_APIPNL_TCON_TAB_TYPE_SCALER);

    // dump TCON mod register tab
    MApi_PNL_TCONMAP_DumpTable(pTcontab->pTConInit_MODTab, E_APIPNL_TCON_TAB_TYPE_MOD);
    //printf("%s %u\n", __FUNCTION__, __LINE__);

    // dump TCON GPIO register tab
    MApi_PNL_TCONMAP_DumpTable(pTcontab->pTConInit_GPIOTab, E_APIPNL_TCON_TAB_TYPE_GPIO);
    //printf("%s %u\n", __FUNCTION__, __LINE__);

    // dump TCON gamma register tab
    if (g_bIsGammaSettingBySW)
    {
        _MApi_XC_Sys_Init_TCON_GAMMA(I2C_DEV_GAMMA_IC, pTcontab->pTConGammaTab);
        //printf("%s %u\n", __FUNCTION__, __LINE__);
    }

    MApi_PNL_TCON_Count_Reset(1);
    MApi_PNL_TCON_Count_Reset(0);
    //printf("%s %u\n", __FUNCTION__, __LINE__);
    MApi_PNL_TCON_Count_Reset(1);

    // dump TCON power on sequence register tab
    //MApi_PNL_TCONMAP_Power_Sequence(Tcontab.pTConPower_Sequence_OnTab, TRUE);
    //_MApi_PNL_TCONMAP_DumpTable(pTcontab->pTConPower_Sequence_OnTab, E_APIPNL_TCON_TAB_TYPE_POWER_SEQUENCE_ON);
    _MApi_TCon_Tab_DumpPSRegTab(pTcontab->pTConPower_Sequence_OnTab);

    PNL_TCON_DBG(printf("%s - end \n", __FUNCTION__));
}

#endif

void MApi_TCON_PNL_POWER_ENABLE(void)
{
   // if ( eTCONPNL_TypeSel == TCON_PANEL_M10_CTV_BOE_HV320WXC )
   //     mdrv_gpio_set_high( PIN_112 );
}

#if ENABLE_OVERDRIVE

#define OD_TBL_SIZE     1056

#if(ENABLE_OD_BIN == 0)
BYTE code tOverDrive[OD_TBL_SIZE]=
{
    0xB4, 0xA0, 0x91, 0x8E, 0xE4, 0xD1, 0xCE, 0x3A,
    0x15, 0xB4, 0x73, 0x61, 0x57, 0x59, 0x43, 0x4F,
    0xB4, 0xA4, 0x97, 0x81, 0xFC, 0xE8, 0xC4, 0x30,
    0x2D, 0x1F, 0x08, 0x79, 0x6A, 0x5F, 0x4C, 0x4F,
    0xB4, 0xB1, 0x94, 0x81, 0xFE, 0xEB, 0xC0, 0x3C,
    0x28, 0x1A, 0x75, 0x65, 0x54, 0x5F, 0x42, 0x4F,
    0xB4, 0xB5, 0xA6, 0x84, 0xF2, 0xED, 0xD8, 0xCB,
    0x26, 0x11, 0x0D, 0x7E, 0x68, 0x5E, 0x4C, 0x4F,
    0xB4, 0xB4, 0xA7, 0x96, 0xF4, 0xE0, 0xDC, 0xC9,
    0x26, 0x12, 0x0D, 0x7E, 0x6F, 0x5C, 0x42, 0x4A,
    0xB4, 0xB4, 0xBF, 0xAB, 0x8C, 0xE4, 0xD1, 0xCE,
    0x3B, 0x17, 0x03, 0x73, 0x6C, 0x53, 0x42, 0x4E,
    0xB4, 0xB4, 0xBC, 0xA8, 0x99, 0xF3, 0xD4, 0xC0,
    0x3D, 0x29, 0x06, 0x70, 0x62, 0x50, 0x46, 0x4F,
    0xB4, 0xB4, 0xB0, 0xAD, 0x98, 0xF6, 0xEC, 0xC4,
    0x33, 0x28, 0x05, 0x76, 0x60, 0x57, 0x47, 0x4E,
    0xB4, 0xB4, 0xB4, 0xA6, 0x95, 0x82, 0xFF, 0xD2,
    0x34, 0x20, 0x1D, 0x08, 0x64, 0x6B, 0x5B, 0x4F,
    0xB4, 0xB4, 0xB4, 0xA6, 0x95, 0x8C, 0xFA, 0xD7,
    0xCD, 0x24, 0x13, 0x0D, 0x78, 0x6A, 0x44, 0x4D,
    0xB4, 0xB4, 0xB4, 0xB9, 0xA0, 0x9C, 0x88, 0xE7,
    0xDD, 0x31, 0x14, 0x00, 0x73, 0x6C, 0x5D, 0x42,
    0xB4, 0xB4, 0xB4, 0xB9, 0xA3, 0x93, 0x8C, 0xE0,
    0xDB, 0x31, 0x2E, 0x04, 0x72, 0x6C, 0x5F, 0x41,
    0xB4, 0xB4, 0xB4, 0xB4, 0xBC, 0xAF, 0x9A, 0xFD,
    0xD0, 0xCC, 0x39, 0x12, 0x74, 0x65, 0x57, 0x40,
    0xB4, 0xB4, 0xB4, 0xB4, 0xB2, 0x94, 0x8E, 0xF9,
    0xD4, 0xC2, 0x38, 0x17, 0x0D, 0x64, 0x54, 0x47,
    0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xA0, 0x94, 0x87,
    0xF2, 0xEA, 0xC2, 0x3A, 0x13, 0x77, 0x54, 0x46,
    0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xA4, 0xA9, 0x9B,
    0xF6, 0xE8, 0xC2, 0x24, 0x1F, 0x71, 0x6B, 0x44,
    0xB4, 0xB4, 0xB4, 0xB4, 0xB4, 0xB1, 0xB9, 0x9C,
    0x99, 0xFB, 0xEE, 0xC2, 0x25, 0x1F, 0x71, 0x56,
    0x34, 0x22, 0x11, 0x7B, 0x64, 0x51, 0xBA, 0xA9,
    0x94, 0x83, 0xF0, 0xE2, 0xD6, 0xCC, 0xC7, 0xC3,
    0x36, 0x27, 0x12, 0x3E, 0x6C, 0x58, 0x44, 0xB0,
    0x9C, 0x8D, 0xFA, 0xEB, 0xDA, 0xCF, 0xC7, 0xC3,
    0x3C, 0x2C, 0x14, 0x01, 0x6A, 0x57, 0x40, 0xAC,
    0x9B, 0x89, 0xF7, 0xE6, 0xDB, 0xCE, 0xC6, 0xC3,
    0x3E, 0x37, 0x1F, 0x05, 0x71, 0x5C, 0x4B, 0xB6,
    0xA5, 0x91, 0xFF, 0xED, 0xDD, 0xCF, 0xC7, 0xC3,
    0x3E, 0x37, 0x24, 0x0F, 0x74, 0x60, 0x4C, 0xB9,
    0xA2, 0x91, 0xFF, 0xEC, 0xDF, 0xD1, 0xC4, 0xC0,
    0x3E, 0x3B, 0x2B, 0x15, 0x7A, 0x64, 0x51, 0xBA,
    0xA7, 0x93, 0x81, 0xF1, 0xE1, 0xD0, 0xC6, 0xC2,
    0x3E, 0x3A, 0x2C, 0x1A, 0x04, 0x6D, 0x54, 0x40,
    0xAD, 0x99, 0x85, 0xF3, 0xE3, 0xD5, 0xC8, 0xC3,
    0x3E, 0x3C, 0x30, 0x1C, 0x09, 0x73, 0x5A, 0x45,
    0xAF, 0x98, 0x87, 0xF5, 0xE5, 0xD5, 0xC8, 0xC2,
    0x3E, 0x3E, 0x37, 0x27, 0x15, 0x7E, 0x66, 0x4D,
    0xB4, 0xA0, 0x8C, 0xF8, 0xE9, 0xD9, 0xCB, 0xC3,
    0x3E, 0x3E, 0x37, 0x27, 0x12, 0x7D, 0x66, 0x50,
    0xBA, 0xA5, 0x8E, 0xFC, 0xEB, 0xD9, 0xCA, 0xC2,
    0x3E, 0x3E, 0x38, 0x2E, 0x20, 0x0C, 0x79, 0x60,
    0x49, 0xAC, 0x94, 0x83, 0xF1, 0xDE, 0xD1, 0xC4,
    0x3E, 0x3E, 0x38, 0x2C, 0x21, 0x11, 0x78, 0x5F,
    0x44, 0xB1, 0x9B, 0x85, 0xF1, 0xDF, 0xCE, 0xC4,
    0x3E, 0x3E, 0x3E, 0x3A, 0x2F, 0x1A, 0x05, 0x68,
    0x50, 0xBC, 0xA7, 0x8D, 0xF6, 0xE4, 0xD5, 0xC7,
    0x3E, 0x3E, 0x3E, 0x3D, 0x2D, 0x13, 0x7D, 0x68,
    0x55, 0xBF, 0xA9, 0x90, 0xFA, 0xE6, 0xD7, 0xC7,
    0x3E, 0x3E, 0x3E, 0x3E, 0x34, 0x24, 0x17, 0x02,
    0x6C, 0x54, 0xBC, 0xA4, 0x8B, 0xEF, 0xD7, 0xC6,
    0x3E, 0x3E, 0x3E, 0x3E, 0x36, 0x28, 0x18, 0x06,
    0x71, 0x57, 0xBD, 0xA3, 0x86, 0xEC, 0xD9, 0xC6,
    0x3E, 0x3E, 0x3E, 0x3E, 0x3C, 0x37, 0x24, 0x14,
    0x00, 0x6A, 0x56, 0xBD, 0xA0, 0x86, 0xED, 0xCF,
    0xEB, 0xF9, 0xCF, 0xDC, 0xA7, 0x8B, 0x9E, 0x62,
    0x76, 0x44, 0x2A, 0x3A, 0x0B, 0x07, 0x1C, 0x10,
    0xEB, 0xE1, 0xCA, 0xDE, 0xA2, 0xB6, 0x99, 0x6D,
    0x71, 0x47, 0x55, 0x24, 0x34, 0xEB, 0x1C, 0x10,
    0xEB, 0xE8, 0xF2, 0xD9, 0xA3, 0xB7, 0x9B, 0x68,
    0x7C, 0x42, 0x56, 0x26, 0x35, 0x01, 0x1C, 0x10,
    0xEB, 0xEB, 0xF9, 0xC2, 0xA8, 0xBD, 0x81, 0x95,
    0x79, 0x4E, 0x52, 0x21, 0x30, 0x02, 0x1C, 0x17,
    0xEB, 0xEB, 0xE4, 0xCB, 0xD7, 0xB9, 0x8D, 0x90,
    0x7B, 0x4F, 0x53, 0x23, 0x32, 0x0C, 0x1D, 0x17,
    0xEB, 0xEB, 0xE2, 0xF6, 0xD9, 0xA0, 0x89, 0x9C,
    0x67, 0x4B, 0x5F, 0x2E, 0x3C, 0x0E, 0x1F, 0x11,
    0xEB, 0xEB, 0xED, 0xF1, 0xC7, 0xAF, 0xB7, 0x99,
    0x63, 0x77, 0x5A, 0x28, 0x3E, 0x08, 0x19, 0x11,
    0xEB, 0xEB, 0xE9, 0xFE, 0xCD, 0xD7, 0xBA, 0x80,
    0x68, 0x73, 0x46, 0x54, 0x39, 0x0A, 0x1A, 0x11,
    0xEB, 0xEB, 0xEB, 0xF9, 0xCA, 0xDC, 0xA7, 0x8F,
    0x97, 0x79, 0x43, 0x51, 0x25, 0x35, 0x04, 0x11,
    0xEB, 0xEB, 0xEB, 0xE4, 0xF1, 0xDB, 0xAE, 0xB0,
    0x9A, 0x61, 0x48, 0x5D, 0x22, 0x30, 0x07, 0x1C,
    0xEB, 0xEB, 0xEB, 0xE6, 0xFE, 0xCC, 0xD1, 0xB8,
    0x87, 0x6E, 0x76, 0x59, 0x2D, 0x33, 0x01, 0x1E,
    0xEB, 0xEB, 0xEB, 0xED, 0xE4, 0xCA, 0xD8, 0xA5,
    0x82, 0x95, 0x78, 0x40, 0x28, 0x3F, 0x0C, 0x1F,
    0xEB, 0xEB, 0xEB, 0xEB, 0xEC, 0xF6, 0xDF, 0xA0,
    0x89, 0x9C, 0x67, 0x4F, 0x57, 0x3B, 0x0A, 0x18,
    0xEB, 0xEB, 0xEB, 0xEB, 0xE8, 0xF1, 0xC6, 0xAB,
    0xB8, 0x81, 0x6A, 0x73, 0x5B, 0x22, 0x0B, 0x19,
    0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xF9, 0xF5, 0xDA,
    0xAF, 0xB6, 0x9D, 0x64, 0x42, 0x2F, 0x34, 0x1A,
    0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEE, 0xE6, 0xC3,
    0xC6, 0xA4, 0xB1, 0x9D, 0x7A, 0x40, 0x2E, 0x09,
    0x85, 0x96, 0xA0, 0xCC, 0xDB, 0xE7, 0xF2, 0x1E,
    0x2B, 0x35, 0x44, 0x55, 0x6B, 0x7C, 0x74, 0x70,
    0x88, 0x95, 0xA6, 0xB3, 0xDF, 0xEB, 0xF7, 0x03,
    0x2F, 0x3E, 0x49, 0x58, 0x69, 0x7C, 0x74, 0x70,
    0x8C, 0x83, 0xA5, 0xB0, 0xDF, 0xEB, 0xF4, 0x8D,
    0x2D, 0x3E, 0x48, 0x58, 0x69, 0x7D, 0x75, 0x70,
    0x8D, 0x84, 0x90, 0xB5, 0xC1, 0xED, 0xF9, 0x05,
    0x16, 0x22, 0x4C, 0x5F, 0x6F, 0x7D, 0x74, 0x70,
    0x8D, 0x8A, 0x9A, 0xA3, 0xC5, 0xD1, 0xFC, 0x0B,
    0x17, 0x23, 0x4D, 0x5C, 0x6D, 0x63, 0x74, 0x70,
    0x8D, 0x89, 0x9E, 0xA5, 0xB2, 0xD5, 0xE1, 0x0C,
    0x1B, 0x27, 0x30, 0x43, 0x53, 0x61, 0x7A, 0x71,
    0x8D, 0x8E, 0x9D, 0xAE, 0xB5, 0xDD, 0xE5, 0xF0,
    0x1F, 0x2A, 0x37, 0x41, 0x51, 0x66, 0x7B, 0x71,
    0x8D, 0x8C, 0x86, 0x93, 0xBC, 0xCB, 0xD3, 0xF5,
    0x00, 0x2F, 0x3B, 0x45, 0x54, 0x64, 0x78, 0x71,
    0x8D, 0x8D, 0x84, 0x94, 0xA6, 0xCD, 0xD5, 0xFD,
    0x05, 0x10, 0x3C, 0x49, 0x5B, 0x6A, 0x79, 0x71,
    0x8D, 0x8D, 0x8A, 0x98, 0xA8, 0xB7, 0xDD, 0xEB,
    0xF0, 0x15, 0x20, 0x4D, 0x5F, 0x6E, 0x7F, 0x76,
    0x8D, 0x8D, 0x8B, 0x9D, 0x93, 0xBD, 0xCB, 0xD3,
    0xFA, 0x1C, 0x25, 0x31, 0x42, 0x6D, 0x62, 0x77,
    0x8D, 0x8D, 0x8E, 0x86, 0x95, 0xA7, 0xCD, 0xD1,
    0xF9, 0x04, 0x12, 0x35, 0x46, 0x50, 0x60, 0x77,
    0x8D, 0x8D, 0x8D, 0x8E, 0x9C, 0xA9, 0xB6, 0xDB,
    0xE1, 0x0C, 0x15, 0x3D, 0x45, 0x54, 0x67, 0x74,
    0x8D, 0x8D, 0x8D, 0x8C, 0x83, 0xAE, 0xBB, 0xC4,
    0xD3, 0xF8, 0x01, 0x29, 0x31, 0x55, 0x64, 0x74,
    0x8D, 0x8D, 0x8D, 0x8D, 0x84, 0x95, 0xAA, 0xB7,
    0xDD, 0xE4, 0x0F, 0x17, 0x38, 0x5C, 0x65, 0x75,
    0x8D, 0x8D, 0x8D, 0x8D, 0x8F, 0x84, 0x97, 0xA7,
    0xB3, 0xD9, 0xE5, 0x0E, 0x13, 0x35, 0x5E, 0x75,
};
#endif

void _MApi_XC_Sys_Init_OD(void)
{
    MS_PNL_OD_INITDATA sPNL_ODInitData;
    MS_U32 u32ODInitDataLen;

    u32ODInitDataLen = sizeof(MS_PNL_OD_INITDATA);

#if 0 // daniel test
    sPNL_ODInitData.u32OD_MSB_Addr = ((VDEC_BITSTREAM_ADR));
    sPNL_ODInitData.u32OD_MSB_Size = 0x280000;
#else
    sPNL_ODInitData.u32OD_MSB_Addr = ((OD_BUFFER_MEMORY_TYPE & MIU1) ? (OD_BUFFER_ADR | MIU_INTERVAL) : (OD_BUFFER_ADR));
    sPNL_ODInitData.u32OD_MSB_Size = OD_BUFFER_LEN;
#endif

  #ifdef OD_LSB_BUFFER_ADR
    sPNL_ODInitData.u32OD_LSB_Addr = ((OD_LSB_BUFFER_MEMORY_TYPE & MIU1) ? (OD_LSB_BUFFER_ADR | MIU_INTERVAL) : (OD_LSB_BUFFER_ADR));
    sPNL_ODInitData.u32OD_LSB_Size = OD_LSB_BUFFER_LEN;
  #else
    sPNL_ODInitData.u32OD_LSB_Addr = NULL;
    sPNL_ODInitData.u32OD_LSB_Size = NULL;
  #endif


#if( ENABLE_OD_BIN )
    if( FALSE == msAPI_OD_BIN_Init() )
    {
        printf("\nError: Init OD Bin failed!\n");
        return;
    }
    if( FALSE == msAPI_OD_BIN_Get_TableData(
            OD_BIN_TBL_2D, 0, OD_BIN_TBL_CH_R, OD_BIN_TBL_TYPE_33x33,
            sPNL_ODInitData.u8ODTbl, sizeof(sPNL_ODInitData.u8ODTbl)    )
       )
    {
        printf("\nError: Get OD Tbl failed!\n");
        return;
    }

#else
    memcpy(sPNL_ODInitData.u8ODTbl, tOverDrive, OD_TBL_SIZE);

#endif

    // Init OD and download OD table to R/G/B channel
    if( E_APIPNL_FAIL == MApi_PNL_OverDriver_Init(&sPNL_ODInitData, u32ODInitDataLen) )
    {
        printf("\nError: Init PNL_OverDrive failed!\n");
        return;
    }

#if( ENABLE_OD_BIN&&(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) )
    // Get G channel OD table,
    if( TRUE == msAPI_OD_BIN_Get_TableData(
            OD_BIN_TBL_2D, 0, OD_BIN_TBL_CH_G, OD_BIN_TBL_TYPE_33x33,
            sPNL_ODInitData.u8ODTbl, sizeof(sPNL_ODInitData.u8ODTbl)    )
       )
    {
        // Set G channel data
        MApi_PNL_SetOverDriverPerChannel(0x04, sPNL_ODInitData.u8ODTbl);
    }
    // Get B channel OD table,
    if( TRUE == msAPI_OD_BIN_Get_TableData(
            OD_BIN_TBL_2D, 0, OD_BIN_TBL_CH_B, OD_BIN_TBL_TYPE_33x33,
            sPNL_ODInitData.u8ODTbl, sizeof(sPNL_ODInitData.u8ODTbl)    )
       )
    {
        // Set B channel data
        MApi_PNL_SetOverDriverPerChannel(0x08, sPNL_ODInitData.u8ODTbl);
    }
#endif

    MApi_PNL_OverDriver_Enable(TRUE);
}
#endif

// Bloader may use this function!
/*static*/ void _MApi_XC_Sys_Init_Panel(void)
{
    // Init Panel information
    //MApi_XC_PNL_SelectPanel(enum, &(sXC_InitData.sPanelInfo));


#if ENABLE_PANEL_BIN
    if ( MApi_PanelParameter_DMA_Bin() )
    {
        MApi_PanelParameter_LoadTable(G_FACTORY_SETTING.stFacPnlSetting.u8PanelBinIndex);
    }
#endif


#if(ENABLE_TCON || ENABLE_TCON_2014)
    // TODO :
#else
    MApi_PNL_PreInit(E_PNL_NO_OUTPUT); //disable LVDS output and LVDS pin is low level
#endif

#if ENABLE_TCON

    g_bIsUsingTconTable = TRUE;

    switch( g_PNL_TypeSel )
    {
        case TCON_PNL_WXGA_IPS32_AX080A076G_Panasonic:
            g_bIsGammaSettingBySW = TRUE;
            eTCONPNL_TypeSel = TCON_PANEL_Panasonic_AX080A076G;
            PNL_TCON_DBG(printf(" = TCON_PNL_WXGA_IPS32_AX080A076G_Panasonic = \n"));
            break;

        case TCON_PNL_WXGA_IPS_ALPHA_AH080A016G_Hisense:
            g_bIsGammaSettingBySW = TRUE;
            eTCONPNL_TypeSel = TCON_PANEL_Hisense_AH080A016G;
            PNL_TCON_DBG(printf(" = TCON_PNL_WXGA_IPS_ALPHA_AH080A016G_Hisense = \n"));
            break;

        case TCON_PNL_WXGA_PM058OX1_MINILVDS:
            eTCONPNL_TypeSel = TCON_PANEL_PVI058OX1;
            PNL_TCON_DBG(printf("= TCON_PANEL_M10_PVI058OX1 = \n"));
            break;

        case TCON_PNL_SVGA_PD050SX1_TTL:
            g_bIsGammaSettingBySW = FALSE;
            eTCONPNL_TypeSel = TCON_PANEL_PVI050VX1;
            PNL_TCON_DBG(printf(" = TCON_PANEL_M10_PVI050VX1 = \n"));
            break;

        case TCON_PNL_XGA_PD0035VX2_TTL:
            g_bIsGammaSettingBySW = FALSE;
            eTCONPNL_TypeSel = TCON_PANEL_PVI035VX2;
            PNL_TCON_DBG(printf(" = TCON_PANEL_M10_PVI035VX2 = \n"));
            break;

        case TCON_PNL_WXGA_BOE_HV320WXC:
            g_bIsGammaSettingBySW = FALSE;
            eTCONPNL_TypeSel = TCON_PANEL_BOE_HV320WXC;
            PNL_TCON_DBG(printf(" = TCON_PNL_WXGA_BOE_HV320WXC = \n"));
            break;

        case TCON_PNL_FullHD_Amtran_Demo:
            g_bIsGammaSettingBySW = FALSE;
            eTCONPNL_TypeSel = TCON_PANEL_FullHD_Amtran;
            PNL_TCON_DBG(printf(" = TCON_PANEL_FullHD_Amtran_Demo = \n"));
            break;
        case TCON_PNL_FULLHD_AUO_T420HW09:
            g_bIsGammaSettingBySW = TRUE;
            eTCONPNL_TypeSel = 0;
            PNL_TCON_DBG(printf(" = TCON_PANEL_FullHD_AUO_T420HW09 = \n"));
            break;
        case TCON_PNL_CSOT_TRIGATE_32:
            g_bIsGammaSettingBySW = FALSE;
            eTCONPNL_TypeSel = TCON_PANEL_CSOT_TRIGATE_32;
            PNL_TCON_DBG(printf(" = TCON_PNL_CSOT_TRIGATE_32 = \n"));
            break;
        case TCON_PNL_CSOT_V390HZ1:
            g_bIsGammaSettingBySW = FALSE;
            eTCONPNL_TypeSel = TCON_PANEL_CSOT_V390HZ1;
            PNL_TCON_DBG(printf(" = TCON_PNL_CSOT_V390HZ1 = \n"));
            break;
        case TCON_PNL_CMO_V390HJ1:
            g_bIsGammaSettingBySW = FALSE;
            eTCONPNL_TypeSel = TCON_PANEL_CMO_V390HJ1;
            PNL_TCON_DBG(printf(" = TCON_PNL_CMO_V390HJ1 = \n"));
            break;
        default:
            g_bIsUsingTconTable = FALSE;
            break;
    }

#else
    //g_bIsUsingTconTable = FALSE;
#endif


#if (SUPPORT_NEW_PANEL_INTERFACE)
    MApi_PNL_PanelIndexTableValidCheck();
#endif

#if ENABLE_TCON_IN8903_PROCESS
    MDrv_IN8903_SetAutoMuteExtendTime(8);
    MDrv_IN8903_SetScreenMuteMode(EN_SCREEN_MUTE_ONLYCHANGE );
    MDrv_IN8903_SwitchMode(E_IN8903_4K2K_MODE_4K2K, IN8903_PANEL_3D_FORMAT_2D_YUV);
#endif

#if ENABLE_VX1_CONVERTER_BOARD
    MApi_PNL_Converter_Board_Init();
#endif

#if ENABLE_MFC_6M20
    MApi_PNL_Init_MISC(E_APIPNL_MISC_MFC_ENABLE);
    MApi_BD_LVDS_Output_Type(4);
    MApi_PNL_MOD_OutputConfig_User(0x5540, 0x1555, 0x00);
#else
    if (devPanel_IsTTL(g_PNL_TypeSel)) //TTL output
    {
        MApi_BD_LVDS_Output_Type(0x04);//LVDS user mode
        MApi_PNL_MOD_OutputConfig_User(0x00,0x00,0x00);
    }
  #if SUPPORT_VX1_OUTPUT
    else if(devPanel_IsVx1(g_PNL_TypeSel))
    {
        //MApi_PNL_MOD_OutputChannelOrder(APIPNL_OUTPUT_CHANNEL_ORDER_USER, 0x2108, 0x493a, 0xb765, 0xdc);
        if(MApi_XC_GetPanelSpec(g_PNL_TypeSel)->m_bPanelDualPort == 1)// 2BLK
        {
            MApi_PNL_MOD_OutputChannelOrder(APIPNL_OUTPUT_CHANNEL_ORDER_USER, _VX1_LANE_ORDER_2BLK_);
        }
        else //1BLK
        {
            MApi_PNL_MOD_OutputChannelOrder(APIPNL_OUTPUT_CHANNEL_ORDER_USER, _VX1_LANE_ORDER_1BLK_);
	  }

        MApi_BD_LVDS_Output_Type(0x04);//4: user mode

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)
        MApi_PNL_MOD_OutputConfig_User(0x5500, 0x0055, 0x00);
#else
        MApi_PNL_MOD_OutputConfig_User(0x4454, 0x0015, 0x00);
#endif
        MApi_PNL_ForceSetPanelDCLK(MApi_PNL_Get_PanelTypicalDclk(g_PNL_TypeSel) , TRUE);
    }
  #endif
    else // LVDS output
    {
        MApi_BD_LVDS_Output_Type(BD_LVDS_CONNECT_TYPE);
    }
#endif


    MApi_XC_SetPanelExtType(g_PNL_TypeSel);

    MApi_PNL_Init( MApi_XC_GetPanelSpec(g_PNL_TypeSel));

    msAPI_GPIO_RegisterGPIOMethods(&g_IPanel);

    g_IPanel.Dump();

#if ENABLE_TCON
    if( g_bIsUsingTconTable )
    {
        TCON_TAB_INFO* pTcontab = &(TConMAP_Main[eTCONPNL_TypeSel]);
    #if ENABLE_TCON_GAMMA_IC
        // Init Gamma table
        //MDrv_PNL_SetDbgLevel(PNL_DBGLEVEL_GAMMA);
        devPanel_InitGammaIC();
    #endif

        _MApi_XC_Sys_Init_TCON_Panel(pTcontab);
    }
#endif

#if( ENABLE_TCON_2014 && (ENABLE_TCON_VER_20==0) )
    msAPI_TCON_Init();
#endif


#if ENABLE_OVERDRIVE
    _MApi_XC_Sys_Init_OD();
#endif

}

#if (CHIP_FAMILY_WHISKY==CHIP_FAMILY_TYPE)
void MApi_XC_Gamma_Set_Value(U8 u8Channel, U8 u8Addr, U16 u16Data )
{
    u8Channel &= 0x03;

    if( u16Data > 0xFFF )
        u16Data = u16Data;


    // Wait finish
    while( MApi_XC_R2BYTE(0x10E0)&BIT3 )
    {
    }

    // "prgrammable gamma table channel select:
    // 00: Select R Channel
    // 01: Select G Channel
    // 10: Select B Channel
    // 11: Select All Channel when write; reserved for read"
    MApi_XC_W2BYTEMSK(0x10E0, (u8Channel)<<5, BIT5|BIT6);


   //write address, LUT_ADDR[7:0]
    MApi_XC_W2BYTEMSK(0x10E2, u8Addr, 0xFF);

    //write Data
    MApi_XC_W2BYTEMSK(0x10E4, u16Data, 0xFFF);

    // Trigger
    MApi_XC_W2BYTEMSK(0x10E0, BIT3, BIT3);

    // Wait finish
    while( MApi_XC_R2BYTE(0x10E0)&BIT3 )
    {
    }

    //max value
    if( u8Addr == 255 )
    {
        //write Data
        if( u8Channel == 0 ) // R
            MApi_XC_W2BYTEMSK(0x10FA, u16Data, 0xFFF);
        else if( u8Channel == 1 ) // G
            MApi_XC_W2BYTEMSK(0x10FC, u16Data, 0xFFF);
        else if( u8Channel == 2 ) // B
            MApi_XC_W2BYTEMSK(0x10FE, u16Data, 0xFFF);
    }
}
#endif

/*
typedef enum
{
    E_MLOAD_UNSUPPORTED = 0,
    E_MLOAD_DISABLED    = 1,
    E_MLOAD_ENABLED     = 2,
}MLOAD_TYPE;
*/
void MApi_XC_Sys_Init_MLoad(void)
{
    //PRINT_CURRENT_LINE();

    //printf("MApi_XC_MLoad_GetStatus()=%u\n", MApi_XC_MLoad_GetStatus());

//    MLOAD_TYPE MApi_XC_MLoad_GetStatus(void);

#if (MENULOAD_BUFFER_LEN != 0)
    if( (MENULOAD_BUFFER_MEMORY_TYPE & MIU1) == (VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1) )
    {
        MApi_XC_MLoad_Init( (MENULOAD_BUFFER_MEMORY_TYPE & MIU1)?MENULOAD_BUFFER_ADR+MIU_INTERVAL:MENULOAD_BUFFER_ADR , MENULOAD_BUFFER_LEN);

        MApi_XC_MLoad_Enable(TRUE);
    }
#endif
}

static void _MApi_XC_Sys_Init_XC(XC_INITDATA *pstXC_InitData)
{

    XC_INITMISC sXC_Init_Misc;

    // reset to zero
    memset(&sXC_Init_Misc, 0, sizeof(XC_INITMISC));

    // Init XC
    // Check library version. Do not modify this statement please.
    pstXC_InitData->u32XC_version = XC_INITDATA_VERSION;

    pstXC_InitData->u32XTAL_Clock = MST_XTAL_CLOCK_HZ;

    pstXC_InitData->u32Main_FB_Size = SCALER_DNR_BUF_LEN;
    pstXC_InitData->u32Main_FB_Start_Addr = ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR));

    // Init DNR Address in Main & Sub channel. Keep the same. If project support FB PIP mode, set Sub DNR Address in AP layer (eg. mapp_init).
    pstXC_InitData->u32Sub_FB_Size = pstXC_InitData->u32Main_FB_Size;
    pstXC_InitData->u32Sub_FB_Start_Addr = pstXC_InitData->u32Main_FB_Start_Addr;

    // Chip related.
    pstXC_InitData->bIsShareGround = SHARE_GND;

    // Board related
    pstXC_InitData->eScartIDPort_Sel = SCART_ID_SEL | SCART2_ID_SEL ;

    pstXC_InitData->bCEC_Use_Interrupt = FALSE;

    pstXC_InitData->bEnableIPAutoCoast = ENABLE_IP_AUTO_COAST;
#if((CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA))
    pstXC_InitData->bMirror = 0;
#else
    pstXC_InitData->bMirror = MirrorEnable;
#endif

    // panel info
    pstXC_InitData->stPanelInfo.u16HStart = g_IPanel.HStart();      // DE H start
    pstXC_InitData->stPanelInfo.u16VStart = g_IPanel.VStart();
    pstXC_InitData->stPanelInfo.u16Width  = g_IPanel.Width();
    pstXC_InitData->stPanelInfo.u16Height = g_IPanel.Height();
    pstXC_InitData->stPanelInfo.u16HTotal = g_IPanel.HTotal();
    pstXC_InitData->stPanelInfo.u16VTotal = g_IPanel.VTotal();

    pstXC_InitData->stPanelInfo.u16DefaultVFreq = g_IPanel.DefaultVFreq();

    pstXC_InitData->stPanelInfo.u8LPLL_Mode = g_IPanel.LPLL_Mode();
    pstXC_InitData->stPanelInfo.enPnl_Out_Timing_Mode = (E_XC_PNL_OUT_TIMING_MODE)(g_IPanel.OutTimingMode());

    pstXC_InitData->stPanelInfo.u16DefaultHTotal = g_IPanel.HTotal();
    pstXC_InitData->stPanelInfo.u16DefaultVTotal = g_IPanel.VTotal();
    pstXC_InitData->stPanelInfo.u32MinSET = g_IPanel.MinSET();
    pstXC_InitData->stPanelInfo.u32MaxSET = g_IPanel.MaxSET();
    pstXC_InitData->stPanelInfo.eLPLL_Type = (E_XC_PNL_LPLL_TYPE) g_IPanel.LPLL_Type();
    //printf("%s, %d, pstXC_InitData->stPanelInfo.eLPLL_Type=%u\n", __FUNCTION__, __LINE__, pstXC_InitData->stPanelInfo.eLPLL_Type);
    pstXC_InitData->bDLC_Histogram_From_VBlank = FALSE;

    if (  MApi_XC_GetCapability(E_XC_SUPPORT_IMMESWITCH)  )
    {
        //printf(" E_XC_SUPPORT_IMMESWITCH \n");

        sXC_Init_Misc.u32MISC_A |= E_XC_INIT_MISC_A_IMMESWITCH;
    }

  #if(ENABLE_XC_DVI_AUTO_EQ)
    if(  MApi_XC_GetCapability(E_XC_SUPPORT_DVI_AUTO_EQ)  )
    {
        sXC_Init_Misc.u32MISC_A |= E_XC_INIT_MISC_A_DVI_AUTO_EQ;
    }
  #endif

    TIMER_SET_DELAY_ID_START(E_DELAY_ID_DRV_XC_INIT);
    if( MApi_XC_Init(pstXC_InitData, sizeof(XC_INITDATA)) == FALSE )
    {
        MS_DEBUG_MSG(printf("L:%d, XC_Init failed because of InitData wrong, please update header file and compile again\n", __LINE__));
    }
    TIMER_SET_DELAY_ID_END();


    //fixed 1280*720P@24Hz & 1280*720P@30Hz  &1280*720P@25Hz can not support

    MApi_XC_SetHdmiSyncMode(HDMI_SYNC_HV);

#if 1//(!HW_AUTO_DISABLE_INPUTSOURCE_WHEN_HDMI_AVMUTE)
    MHAL_HDMI_Set_EnAvMute(DISABLE);
#endif

#if 1// !HW_AUTO_DISABLE_INPUTSOURCE_WHEN_NO_SIGNAL
    MApi_XC_EnableIPAutoNoSignal(DISABLE, MAIN_WINDOW );
#endif

    if(MApi_XC_Init_MISC(&sXC_Init_Misc, sizeof(XC_INITMISC)) == FALSE)
    {
        MS_DEBUG_MSG(printf("L:%d, XC Init MISC failed because of InitData wrong, please update header file and compile again\n", __LINE__));
    }

    //MApi_XC_ADC_Set_YPbPrLooseLPF(ENABLE);

#if(XC_MLOAD_INIT_AFTER_PANEL_ENABLE)
    // Move _MApi_XC_Sys_Init_MLoad() to after panel-enable
#else
    MApi_XC_Sys_Init_MLoad();
#endif

    // Init Gamma table
    g_IPanel.SetGammaTbl(E_APIPNL_GAMMA_12BIT, tAllGammaTab, GAMMA_MAPPING_MODE);

#if ENABLE_GAMMA_ADJUST
    MApp_LoadNewGammaTable();
#endif

// To load DAC current mode that depends on the board define.
#ifdef ADC_DACCURRENTMPDE
    MApi_XC_ADC_SetIdacCurrentMode(ADC_DACCURRENTMPDE);
#endif


#if( !(ENABLE_TCON || ENABLE_TCON_2014||SUPPORT_VX1_OUTPUT) )
    // Set extend panel info...
    {
        XC_PANEL_INFO_EX stPanelInfoEx;
        memset(&stPanelInfoEx, 0, sizeof(XC_PANEL_INFO_EX));

        stPanelInfoEx.u32PanelInfoEx_Version = PANEL_INFO_EX_VERSION;
        stPanelInfoEx.u16PanelInfoEX_Length = sizeof(XC_PANEL_INFO_EX);

        stPanelInfoEx.bMaxDClkValid = TRUE;
        stPanelInfoEx.u32MaxDClk = MApi_PNL_Get_PanelDClkMax(g_PNL_TypeSel)*1000;
        stPanelInfoEx.bMinDClkValid = TRUE;
        stPanelInfoEx.u32MinDClk = MApi_PNL_Get_PanelDClkMin(g_PNL_TypeSel)*1000;

        stPanelInfoEx.u16VFreq = 500; //this step setting info is only for 50hz

        if(MApi_XC_SetExPanelInfo(TRUE, &stPanelInfoEx))//Check the set is accepted or not
            printf("Set ExPanel Info(u16VFreq=%u) OK\n", stPanelInfoEx.u16VFreq);
        else
            printf("Set ExPanel Info(u16VFreq=%u) NG\n", stPanelInfoEx.u16VFreq);

        memset(&stPanelInfoEx, 0, sizeof(XC_PANEL_INFO_EX));
        stPanelInfoEx.u32PanelInfoEx_Version = PANEL_INFO_EX_VERSION;
        stPanelInfoEx.u16PanelInfoEX_Length = sizeof(XC_PANEL_INFO_EX);

        stPanelInfoEx.bMaxDClkValid = TRUE;
        stPanelInfoEx.u32MaxDClk = MApi_PNL_Get_PanelDClkMax(g_PNL_TypeSel)*1000;
        stPanelInfoEx.bMinDClkValid = TRUE;
        stPanelInfoEx.u32MinDClk = MApi_PNL_Get_PanelDClkMin(g_PNL_TypeSel)*1000;

        stPanelInfoEx.u16VFreq = 600; //this step setting info is only for 60hz
        if(MApi_XC_SetExPanelInfo(TRUE, &stPanelInfoEx))//Check the set is accepted or not
            printf("Set ExPanel Info(u16VFreq=%u) OK\n", stPanelInfoEx.u16VFreq);
        else
            printf("Set ExPanel Info(u16VFreq=%u) NG\n", stPanelInfoEx.u16VFreq);
    }
#endif

  #if 0
    {
        //Sample code of change sync width and back porch
        XC_PANEL_INFO_EX stPanelInfoEx;
        memset(&stPanelInfoEx, 0, sizeof(XC_PANEL_INFO_EX));
        stPanelInfoEx.u32PanelInfoEx_Version = PANEL_INFO_EX_VERSION;
        stPanelInfoEx.u16PanelInfoEX_Length = sizeof(XC_PANEL_INFO_EX);
        stPanelInfoEx.bVSyncBackPorchValid = TRUE;
        stPanelInfoEx.u16VSyncBackPorch = 36; //set back porch value
        stPanelInfoEx.bVSyncWidthValid = TRUE;
        stPanelInfoEx.u16VSyncWidth= 5 ; //set SyncWidth value
        stPanelInfoEx.u16VFreq = 500; //this step setting info is only for 50hz
        if(MApi_XC_SetExPanelInfo(TRUE, &stPanelInfoEx))//Check the set is accepted or not
            printf("Set ExPanel Info(u16VFreq=%u) OK\n", stPanelInfoEx.u16VFreq);
        else
            printf("Set ExPanel Info(u16VFreq=%u) NG\n", stPanelInfoEx.u16VFreq);

        memset(&stPanelInfoEx, 0, sizeof(XC_PANEL_INFO_EX));
        stPanelInfoEx.u32PanelInfoEx_Version = PANEL_INFO_EX_VERSION;
        stPanelInfoEx.u16PanelInfoEX_Length = sizeof(XC_PANEL_INFO_EX);
        stPanelInfoEx.bVSyncBackPorchValid = TRUE;
        stPanelInfoEx.u16VSyncBackPorch = 26; //set back porch value
        stPanelInfoEx.bVSyncWidthValid = TRUE;
        stPanelInfoEx.u16VSyncWidth= 3 ; //set SyncWidth  value
        stPanelInfoEx.u16VFreq = 600; //this step setting info is only for 60hz
        if(MApi_XC_SetExPanelInfo(TRUE, &stPanelInfoEx))//Check the set is accepted or not
            printf("Set ExPanel Info(u16VFreq=%u) OK\n", stPanelInfoEx.u16VFreq);
        else
            printf("Set ExPanel Info(u16VFreq=%u) NG\n", stPanelInfoEx.u16VFreq);
    }
  #endif

  #if 0
    {
        //Sample code of steply change vtt
        XC_PANEL_INFO_EX stPanelInfoEx;
        memset(&stPanelInfoEx, 0, sizeof(XC_PANEL_INFO_EX));
        stPanelInfoEx.u32PanelInfoEx_Version = PANEL_INFO_EX_VERSION;
        stPanelInfoEx.u16PanelInfoEX_Length = sizeof(XC_PANEL_INFO_EX);

        stPanelInfoEx.bVttStepsValid = TRUE;
        stPanelInfoEx.bVttDelayValid = TRUE;
        stPanelInfoEx.u16VttSteps = xx; //set how many steps u want to set this vtt
        stPanelInfoEx.u16VttDelay = xx;// set the delay between steps of setting vtt
        stPanelInfoEx.u16VFreq = 500; //set the this steps info for 50hz
        if(MApi_XC_SetExPanelInfo(TRUE, &stPanelInfoEx))
            printf("Set ex panel info(u16VFreq=%u) OK\n", stPanelInfoEx.u16VFreq);
        else
            printf("Set ex panel info(u16VFreq=%u) Fail\n", stPanelInfoEx.u16VFreq);

        stPanelInfoEx.u16VFreq = 600; //set same steps info for 60 hz, here means 50/60hz use same step to set vtt
        if(MApi_XC_SetExPanelInfo(TRUE, &stPanelInfoEx))
            printf("Set ex panel info(u16VFreq=%u) OK\n", stPanelInfoEx.u16VFreq);
        else
            printf("Set ex panel info(u16VFreq=%u) Fail\n", stPanelInfoEx.u16VFreq);
    }
  #endif
}


#if ENABLE_PQ_BIN

#if(ENABLE_PQ_BIN_EX)
BOOLEAN _MApi_XC_Sys_Init_PQ_Ex_Bin(MS_PQ_Init_Info * pstPQ_InitData, U8 u8BinInfoIdx)
{
    BININFO BinInfo;
    BOOLEAN bResult;

    //==================================================================================
    //  Load Chip_Main_Ex.bin

    BinInfo.B_ID = (U32)BIN_ID_PQ_MAIN_EX;
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if( bResult != PASS )
    {
         printf( "could not find Main_Ex PQ binary on flash.\n" );
         return FALSE;
    }

#if( PQ_MAIN_EX_LEN == 0) //PQ_ONLY_SUPPORT_BIN
    U8 *pPQMainExAllocStart = (U8*)msAPI_Memory_Allocate(BinInfo.B_Len,BUF_ID_PQ_MAIN_EX);
    if( pPQMainExAllocStart == NULL )
    {
        printf("\nPQ_MAIN_EX BIN MEMORY ALLOCATE FAIL!!\n");
        return FALSE;
    }
    //printf("pPQMainExAllocStart=%X\n",pPQMainExAllocStart);

    U32 u32PQMainExAddr_PA = _VA2PA((U32)pPQMainExAllocStart);
#else
    U32 u32PQMainExAddr_PA = ((PQ_MAIN_EX_MEMORY_TYPE & MIU1) ? (PQ_MAIN_EX_ADR | MIU_INTERVAL) : (PQ_MAIN_EX_ADR));
#endif

    MApi_BDMA_Copy(BinInfo.B_FAddr, u32PQMainExAddr_PA, BinInfo.B_Len, MIU_FLASH2SDRAM);


    pstPQ_InitData->stPQBinInfo[u8BinInfoIdx].u8PQID = (MS_U8) PQ_BIN_EXT_MAIN;
    pstPQ_InitData->stPQBinInfo[u8BinInfoIdx].PQBin_PhyAddr = (MS_PHYADDR)u32PQMainExAddr_PA;

    //pstPQ_InitData->u8PQBinCnt = 2;
    pstPQ_InitData->u8PQBinCnt += 1;

    return TRUE;
}
#endif

BOOLEAN _MApi_XC_Sys_Init_PQ_Bin(MS_PQ_Init_Info * pstPQ_InitData)
{
    BININFO BinInfo;
    BOOLEAN bResult;


    pstPQ_InitData->u8PQBinCnt = 0;
    pstPQ_InitData->u8PQTextBinCnt = 0;

    //==================================================================================
    //  Load Chip_Main.bin

    // Get bin info...
    BinInfo.B_ID = (U32)BIN_ID_PQ_MAIN;
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);

    if( bResult != PASS )
    {
         printf( "could not find Main PQ binary on flash.\n" );
         return FALSE;
    }

#if( PQ_MAIN_LEN == 0) //PQ_ONLY_SUPPORT_BIN
    U8 *pPQMainAllocStart = (U8*)msAPI_Memory_Allocate(BinInfo.B_Len, BUF_ID_PQ_MAIN);
    if( pPQMainAllocStart == NULL )
    {
        printf("\nPQ_MAIN BIN MEMORY ALLOCATE FAIL!!\n");
        return FALSE;
    }

    //printf("pPQMainAllocStart=%X\n", pPQMainAllocStart);

    U32 u32PQMainAddr_PA = _VA2PA((U32)pPQMainAllocStart);
#else
    U32 u32PQMainAddr_PA = ((PQ_MAIN_MEMORY_TYPE & MIU1) ? (PQ_MAIN_ADR | MIU_INTERVAL) : (PQ_MAIN_ADR));
#endif

    MApi_BDMA_Copy(BinInfo.B_FAddr, u32PQMainAddr_PA, BinInfo.B_Len, MIU_FLASH2SDRAM);

    pstPQ_InitData->u8PQBinCnt = 1;
    pstPQ_InitData->stPQBinInfo[0].u8PQID = (MS_U8) PQ_BIN_STD_MAIN;
    pstPQ_InitData->stPQBinInfo[0].PQBin_PhyAddr = (MS_PHYADDR)u32PQMainAddr_PA;

    //==================================================================================
    //  Load Chip_Main_Text.bin

    BinInfo.B_ID = (U32)BIN_ID_PQ_MAIN_TEXT;
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS)
    {
        printf( "could not find PQ Tex binary on flash.\n" );
        return FALSE;
    }


#if( PQ_TEXT_MAIN_LEN == 0 ) //PQ_ONLY_SUPPORT_BIN
    U8 *pPQMainTextAllocStart = (U8*)msAPI_Memory_Allocate(BinInfo.B_Len,BUF_ID_PQ_MAIN_TEXT);
    if( pPQMainTextAllocStart == NULL)
    {
        printf("\nPQ_MAIN_TEXT BIN MEMORY ALLOCATE FAIL!!\n");
        return FALSE;
    }
    //printf("pPQMainTextAllocStart=%X\n",pPQMainTextAllocStart);

    U32 u32PQMainTextAddr_PA =_VA2PA((U32)pPQMainTextAllocStart);
#else

    U32 u32PQMainTextAddr_PA = ((PQ_TEXT_MAIN_MEMORY_TYPE & MIU1) ? (PQ_TEXT_MAIN_ADR | MIU_INTERVAL) : (PQ_TEXT_MAIN_ADR));
#endif

    MApi_BDMA_Copy(BinInfo.B_FAddr, u32PQMainTextAddr_PA, BinInfo.B_Len, MIU_FLASH2SDRAM);

    pstPQ_InitData->u8PQTextBinCnt = 1;
    pstPQ_InitData->stPQTextBinInfo[0].u8PQID = (MS_U8)PQ_TEXT_BIN_STD_MAIN;
    pstPQ_InitData->stPQTextBinInfo[0].PQBin_PhyAddr = (MS_PHYADDR)u32PQMainTextAddr_PA;

    //==================================================================================
    //  Load Chip_Main_Ex.bin
  #if(ENABLE_PQ_BIN_EX)
    _MApi_XC_Sys_Init_PQ_Ex_Bin(pstPQ_InitData, 1);
  #endif

    return TRUE;
}
#endif

void _MApi_XC_Sys_Init_PQ(XC_INITDATA *pstXC_InitData)
{
    MS_PQ_Init_Info sXC_PQ_InitData;
    U32 u32InitDataLen = 0;

    memset(&sXC_PQ_InitData, 0, sizeof(MS_PQ_Init_Info));

    // Init PQ related

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)
    #if(MEMORY_MAP <= MMAP_64MB)
        sXC_PQ_InitData.bDDR2 = TRUE;
    #else
        sXC_PQ_InitData.bDDR2 = FALSE;
    #endif
#else
    #if (DRAM_TYPE == DDR_II)
        sXC_PQ_InitData.bDDR2 = TRUE;
    #else
        sXC_PQ_InitData.bDDR2 = FALSE;
    #endif
#endif
    sXC_PQ_InitData.u32DDRFreq = DDRPLL_FREQ;

#if (DRAM_BUS == DRAM_BUS_16)
        sXC_PQ_InitData.u8BusWidth = 16;
#elif (DRAM_BUS == DRAM_BUS_32)
        sXC_PQ_InitData.u8BusWidth = 32;
#else
    #error "DRAM_TYPE: BUS_WIDTH NOT DEFINE"
#endif

    if(pstXC_InitData->stPanelInfo.u16Width == 1366)
    {
        sXC_PQ_InitData.u16PnlWidth = 1366;
    }
    else if(pstXC_InitData->stPanelInfo.u16Width == 3840)
    {
        sXC_PQ_InitData.u16PnlWidth = 3840;
    }
    else
    {
        sXC_PQ_InitData.u16PnlWidth = 1920;
    }

    sXC_PQ_InitData.u16OSD_hsize = UI_OSD_PANE_W;
    sXC_PQ_InitData.u16Pnl_vtotal = pstXC_InitData->stPanelInfo.u16VTotal;

#if ENABLE_PQ_BIN
    if( TRUE == _MApi_XC_Sys_Init_PQ_Bin(&sXC_PQ_InitData) )
    {
    }
    else
#endif
    {
        sXC_PQ_InitData.u8PQBinCnt = 0;
        sXC_PQ_InitData.u8PQTextBinCnt = 0;
    }


///////
    //PQ_Function_Info* function_Info = NULL;
    PQ_Function_Info function_Info;
    memset( &function_Info , 0 , sizeof(PQ_Function_Info) );

    function_Info.pq_deside_srctype = MDrv_PQ_DesideSrcType;
    function_Info.pq_disable_filmmode = MDrv_PQ_DisableFilmMode;
    function_Info.pq_load_scalingtable = MDrv_PQ_LoadScalingTable;
    function_Info.pq_set_420upsampling = MDrv_PQ_Set420upsampling;
    function_Info.pq_set_csc = MDrv_PQ_SetCSC;
    function_Info.pq_set_memformat = MDrv_PQ_SetMemFormat;
    function_Info.pq_set_modeInfo = MDrv_PQ_Set_ModeInfo;
    function_Info.pq_get_memyuvfmt = MDrv_PQ_Get_MemYUVFmt;
    function_Info.pq_ioctl = MDrv_PQ_IOCTL;
    MApi_XC_PQ_LoadFunction(&function_Info , u32InitDataLen);
//////


    MDrv_PQ_Init(&sXC_PQ_InitData);

    U16PQSrcType = INVALID_PQ_SRC_TYPE; // Init SC_QUALITY_MAP_INDEX
}

static MS_S16  S16DefaultColorCorrectionMatrix[32] =
{
     0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
     0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
    -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
    -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

//DAC output bypass color matrix
MS_S16 S16DACColorCorrectionMatrix[32] =
{
    0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
    0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
    -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
    -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

static MS_S16  S16DefaultRGB[3][3] =
{
    { 1024, 0,    0 }, // R
    { 0,  1024,   0 }, // G
    { 0,   0,  1024 }  // B
};

static void _MApi_XC_Sys_Init_ACE(void)
{
    XC_ACE_InitData sXC_ACE_InitData;

    memset(&sXC_ACE_InitData, 0, sizeof(XC_ACE_InitData));

    // Init ACE
    sXC_ACE_InitData.eWindow = MAIN_WINDOW;
    sXC_ACE_InitData.S16ColorCorrectionMatrix = (MS_S16*) S16DefaultColorCorrectionMatrix;
    sXC_ACE_InitData.S16RGB = (MS_S16*) S16DefaultRGB;
    sXC_ACE_InitData.u16MWEHstart = g_IPanel.HStart();
    sXC_ACE_InitData.u16MWEVstart = g_IPanel.VStart();
    sXC_ACE_InitData.u16MWEWidth  = g_IPanel.Width();
    sXC_ACE_InitData.u16MWEHeight = g_IPanel.Height();

    //Init H/V info for first MWE function select
    sXC_ACE_InitData.u16MWE_Disp_Hstart = 0;
    sXC_ACE_InitData.u16MWE_Disp_Vstart = 0;
    sXC_ACE_InitData.u16MWE_Disp_Width  = g_IPanel.Width();
    sXC_ACE_InitData.u16MWE_Disp_Height = g_IPanel.Height();
    #if (MWE_FUNCTION )
    sXC_ACE_InitData.bMWE_Enable = TRUE;
    #endif

    if(MApi_XC_ACE_Init(&sXC_ACE_InitData, sizeof(XC_ACE_InitData)) == FALSE)
    {
        MS_DEBUG_MSG(printf("L:%d, ACE_Init failed because of InitData wrong, please update header file and compile again\n", __LINE__));
    }

}

#if ENABLE_DBC

static void _MApi_XC_Sys_Init_DLC_DBC(XC_DLC_init  *pstXC_DLC_InitData)
{
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucMax_Video =            DBC_MAX_VIDEO_DBC;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucMid_Video =            DBC_MID_VIDEO_DBC;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucMin_Video =            DBC_MIN_VIDEO_DBC;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucMaxPWM =               DBC_MAX_PWM;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucBackLight_Thres =      DBC_BACKLIGHT_THRES;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucMinPWM =               DBC_MIN_PWM;

    // below settings was moved to MApi_XC_Sys_DLC_DBC_YCGainInit()
    // initial value of ucY_Gain_H and ucC_Gain_H was set in Q-map
    //g_DbcParameters.ucY_Gain_H =          DBC_Y_GAIN_H;
    //g_DbcParameters.ucY_Gain_M =          DBC_Y_GAIN_M;
    //g_DbcParameters.ucY_Gain_L =          DBC_Y_GAIN_L;
    //g_DbcParameters.ucC_Gain_H =          DBC_C_GAIN_H;
    //g_DbcParameters.ucC_Gain_M =          DBC_C_GAIN_M;
    //g_DbcParameters.ucC_Gain_L =          DBC_C_GAIN_L;

    pstXC_DLC_InitData->DLC_DBC_MFinit.ucAlpha =                DBC_ALPHA_BLENDING_CURRENT;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucAvgDelta =             DBC_AVG_DELTA;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucFastAlphaBlending =    DBC_FAST_ALPHABLENDING;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucLoop_Dly_H_Init =      DBC_LOOP_DLY_H;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucLoop_Dly_MH_Init =     DBC_LOOP_DLY_MH;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucLoop_Dly_ML_Init =     DBC_LOOP_DLY_ML;
    pstXC_DLC_InitData->DLC_DBC_MFinit.ucLoop_Dly_L_Init =      DBC_LOOP_DLY_L;
    pstXC_DLC_InitData->DLC_DBC_MFinit.bYGainCtrl       =       DISABLE;
    pstXC_DLC_InitData->DLC_DBC_MFinit.bCGainCtrl       =       DISABLE;

    MApi_XC_DLC_DBC_Init(pstXC_DLC_InitData->DLC_DBC_MFinit);

    MApi_XC_DBC_Init(); //msDBCInit();

}
#endif


#if ENABLE_DLC

static void _MApi_XC_Sys_Init_DLC(void)
{
    // Init ACE
    MS_U8 i;
    XC_DLC_init sXC_DLC_InitData;

    memset(&sXC_DLC_InitData, 0, sizeof(XC_DLC_init));

    for (i=0; i<16; ++i)
    {
        sXC_DLC_InitData.DLC_MFinit_Ex.ucLumaCurve[i]     = mApi_DLC_GetLumaCurve(i);
        sXC_DLC_InitData.DLC_MFinit_Ex.ucLumaCurve2_a[i]  = mApi_DLC_GetLumaCurve2_a(i);
        sXC_DLC_InitData.DLC_MFinit_Ex.ucLumaCurve2_b[i]  = mApi_DLC_GetLumaCurve2_b(i);
    }

    for (i=0; i<DLC_HISTOGRAM_LIMIT_CURVE_ARRARY_NUM; ++i)
    {
        sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcHistogramLimitCurve[i] = mApi_DLC_GetDlcHistogramLimitCurve(i);
    }
    sXC_DLC_InitData.DLC_MFinit_Ex.u32DLC_MFinit_Ex_Version= DLC_MFINIT_EX_VERSION;
    sXC_DLC_InitData.DLC_MFinit_Ex.u8_L_L_U               = DLC_PARAMETER_L_L_U; // default value: 10
    sXC_DLC_InitData.DLC_MFinit_Ex.u8_L_L_D               = DLC_PARAMETER_L_L_D; // default value: 10
    sXC_DLC_InitData.DLC_MFinit_Ex.u8_L_H_U               = DLC_PARAMETER_L_H_U; // default value: 10
    sXC_DLC_InitData.DLC_MFinit_Ex.u8_L_H_D               = DLC_PARAMETER_L_H_D; // default value: 10
    sXC_DLC_InitData.DLC_MFinit_Ex.u8_S_L_U               = DLC_PARAMETER_S_L_U; // default value: 128 (0x80)
    sXC_DLC_InitData.DLC_MFinit_Ex.u8_S_L_D               = DLC_PARAMETER_S_L_D; // default value: 128 (0x80)
    sXC_DLC_InitData.DLC_MFinit_Ex.u8_S_H_U               = DLC_PARAMETER_S_H_U; // default value: 128 (0x80)
    sXC_DLC_InitData.DLC_MFinit_Ex.u8_S_H_D               = DLC_PARAMETER_S_H_D; // default value: 128 (0x80)

    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcPureImageMode     = DLC_PARAMETER_PURE_IMAGE_MODE; // Compare difference of max and min bright
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcLevelLimit        = DLC_PARAMETER_LEVEL_LIMIT; // n = 0 ~ 4 => Limit n levels => ex. n=2, limit 2 level 0xF7, 0xE7
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcAvgDelta          = DLC_PARAMETER_AVG_DELTA; // n = 0 ~ 50, default value: 12
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcAvgDeltaStill     = DLC_PARAMETER_AVG_DELTA_STILL; // n = 0 ~ 15 => 0: disable still curve, 1 ~ 15: enable still curve
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcFastAlphaBlending = DLC_PARAMETER_FAST_ALPHA_BLENDING; // min 17 ~ max 32
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcYAvgThresholdL    = DLC_PARAMETER_Y_AVG_THRESHOLD_L; // default value: 0
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcYAvgThresholdH    = DLC_PARAMETER_Y_AVG_THRESHOLD_H; // default value: 128
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcBLEPoint          = DLC_PARAMETER_BLE_POINT; // n = 24 ~ 64, default value: 48
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcWLEPoint          = DLC_PARAMETER_WLE_POINT; // n = 24 ~ 64, default value: 48
    sXC_DLC_InitData.DLC_MFinit_Ex.bEnableBLE             = DLC_PARAMETER_ENABLE_BLE; // 1: enable; 0: disable
    sXC_DLC_InitData.DLC_MFinit_Ex.bEnableWLE             = DLC_PARAMETER_ENABLE_WLE; // 1: enable; 0: disable

    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcYAvgThresholdM    = DLC_PARAMETER_Y_AVG_THRESHOLD_M;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcCurveMode         = DLC_PARAMETER_CURVE_MODE;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcCurveModeMixAlpha = DLC_PARAMETER_CURVE_MIXALPHA;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcAlgorithmMode     = DLC_PARAMETER_ALGORITHM_MODE;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcSepPointH         = DLC_PARAMETER_SepPoint_H;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcSepPointL         = DLC_PARAMETER_SepPoint_L;
    sXC_DLC_InitData.DLC_MFinit_Ex.uwDlcBleStartPointTH   = DLC_PARAMETER_BLEStartPointTH;
    sXC_DLC_InitData.DLC_MFinit_Ex.uwDlcBleEndPointTH     = DLC_PARAMETER_BLEEndPointTH;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcCurveDiff_L_TH    = DLC_PARAMETER_DLC_CurveDiff_L_TH;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcCurveDiff_H_TH    = DLC_PARAMETER_DLC_CurveDiff_H_TH;
    sXC_DLC_InitData.DLC_MFinit_Ex.uwDlcBLESlopPoint_1    = DLC_PARAMETER_BLE_Slop_Point1;
    sXC_DLC_InitData.DLC_MFinit_Ex.uwDlcBLESlopPoint_2    = DLC_PARAMETER_BLE_Slop_Point2;
    sXC_DLC_InitData.DLC_MFinit_Ex.uwDlcBLESlopPoint_3    = DLC_PARAMETER_BLE_Slop_Point3;
    sXC_DLC_InitData.DLC_MFinit_Ex.uwDlcBLESlopPoint_4    = DLC_PARAMETER_BLE_Slop_Point4;
    sXC_DLC_InitData.DLC_MFinit_Ex.uwDlcBLESlopPoint_5    = DLC_PARAMETER_BLE_Slop_Point5;
    sXC_DLC_InitData.DLC_MFinit_Ex.uwDlcDark_BLE_Slop_Min = DLC_PARAMETER_BLE_Dark_Slop_Min;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcCurveDiffCoringTH = DLC_PARAMETER_DLC_CurveDiff_Coring_TH;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcAlphaBlendingMin  = DLC_PARAMETER_DLC_FAST_ALPHA_BLENDING_MIN;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcAlphaBlendingMax  = DLC_PARAMETER_DLC_FAST_ALPHA_BLENDING_MAX;

    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcFlicker_alpha     = DLC_PARAMETER_DLC_FlICKER_ALPHA;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcYAVG_L_TH         = DLC_PARAMETER_DLC_YAVG_L_TH;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcYAVG_H_TH         = DLC_PARAMETER_DLC_YAVG_H_TH;

    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcDiffBase_L             = DLC_PARAMETER_DLC_DiffBase_L;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcDiffBase_M             = DLC_PARAMETER_DLC_DiffBase_M;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucDlcDiffBase_H             = DLC_PARAMETER_DLC_DiffBase_H;

    sXC_DLC_InitData.u16CurveHStart                    = g_IPanel.Width()/8;
    sXC_DLC_InitData.u16CurveHEnd                      = g_IPanel.Width()*7/8;
    sXC_DLC_InitData.u16CurveVStart                    = g_IPanel.Height()/8;
    sXC_DLC_InitData.u16CurveVEnd                      = g_IPanel.Height()*7/8;

    // CGC
    sXC_DLC_InitData.DLC_MFinit_Ex.ucCGCCGain_offset      = DLC_CGC_CGAIN_OFFSET;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucCGCYCslope           = DLC_CGC_YC_SLOPE; // 0x01~0x20
#if ( DLC_C_GAIN_CONTROL )
    sXC_DLC_InitData.DLC_MFinit_Ex.ucCGCChroma_GainLimitH = DLC_CGC_CGAIN_LIMIT_H; // 0x00~0x6F
    sXC_DLC_InitData.DLC_MFinit_Ex.ucCGCChroma_GainLimitL = DLC_CGC_CGAIN_LIMIT_L; // 0x00~0x10
#else
    sXC_DLC_InitData.DLC_MFinit_Ex.ucCGCChroma_GainLimitH = 0;
    sXC_DLC_InitData.DLC_MFinit_Ex.ucCGCChroma_GainLimitL = 0;
#endif

    sXC_DLC_InitData.DLC_MFinit_Ex.ucCGCYth               = DLC_CGC_Y_TH;
    sXC_DLC_InitData.DLC_MFinit_Ex.bCGCCGainCtrl          = DLC_CGC_ENABLE; //Dixon, DISABLE CGC

    if(MApi_XC_DLC_Init_Ex(&sXC_DLC_InitData, sizeof(XC_DLC_init)) == FALSE)
    {
        MS_DEBUG_MSG(printf("L:%d, DLC_Init failed because of InitData wrong, please update header file and compile again\n", __LINE__));
    }
#if ENABLE_DBC
    _MApi_XC_Sys_Init_DLC_DBC(&sXC_DLC_InitData);
    MApi_XC_DLC_DBC_Setstatus(FALSE);
#endif
}
#endif


#if defined(MIPS_CHAKRA)||((CHIP_FAMILY_TYPE==CHIP_FAMILY_MAZDA))
void _MApp_Load_HDCP_FromEfuse(MS_U8 *u8HdcpKey)
{
    #define REG_BASE  0xBF004000   //MIPS

    unsigned int    dwDataCounter = 0;
    MS_U16  reg_512x8_addr = 0x0, reg_512x8_trig = 0x2000 , reg_512x8_rdata_lo = 0x0000 , reg_512x8_rdata_hi = 0x0000;

    //printf("HDCP in EFUSE\n");
    //printf("HDCP_KEY_SIZE = %d  \n",HDCP_KEY_SIZE);

    while(dwDataCounter < HDCP_KEY_SIZE)
    {
      #if (CHIP_FAMILY_TYPE==CHIP_FAMILY_MARLON)
        MS_U32  u32HDCPKey = 0;

        reg_512x8_trig = 0x2000;
        MDrv_SYS_ReadEfuseHDCPKey(reg_512x8_addr, &u32HDCPKey);
        reg_512x8_rdata_lo =(MS_U16)(u32HDCPKey);
        reg_512x8_rdata_hi =(MS_U16)(u32HDCPKey>>16);
      #else
        *(volatile MS_U32*)(REG_BASE+(0x28*4)) = reg_512x8_addr << 2; //[8:2]:HDCP address
        *(volatile MS_U32*)(REG_BASE+(0x28*4))|= reg_512x8_trig;      //[13]: Read request Trigger ==> 1:read request, 0:data ready

        while(((*(volatile MS_U32*)(REG_BASE+(0x28*4)))&reg_512x8_trig)==reg_512x8_trig);

        reg_512x8_rdata_lo = *(volatile MS_U32*)(REG_BASE+(0x2c*4));
        reg_512x8_rdata_hi = *(volatile MS_U32*)(REG_BASE+(0x2d*4));
      #endif

        //programming e-fuse HDCP key in 2 byte by 2 byte mode (Low index in MSB)
        if(dwDataCounter < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_lo >> 8;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_lo;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_hi >> 8;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_hi;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        reg_512x8_addr++;

        if((dwDataCounter % 16) == 0)
        {
            //printf("\r\n");
        }
    }
}
#else //AEON
void _MApp_Load_HDCP_FromEfuse(MS_U8 *u8HdcpKey)
{
    #define REG_BASE  0xA0004000   //AEON

    unsigned int    dwDataCounter = 0;
    MS_U16  reg_512x8_addr = 0x0, reg_512x8_trig = 0x01 , reg_512x8_rdata_lo = 0x0000 , reg_512x8_rdata_hi = 0x0000;

    //printf("HDCP in EFUSE\n");
    //printf("HDCP_KEY_SIZE = %d  \n",HDCP_KEY_SIZE);

    while(dwDataCounter < HDCP_KEY_SIZE)
    {
        *(volatile MS_U32*)(REG_BASE+(0x27*4)) = reg_512x8_addr;
        *(volatile MS_U32*)(REG_BASE+(0x26*4)) = reg_512x8_trig;

        while(((*(volatile MS_U32*)(REG_BASE+(0x26*4)))&reg_512x8_trig)==reg_512x8_trig);

        reg_512x8_rdata_lo = *(volatile MS_U32*)(REG_BASE+(0x28*4));
        reg_512x8_rdata_hi = *(volatile MS_U32*)(REG_BASE+(0x29*4));

      #if (CHIP_FAMILY_TYPE==CHIP_FAMILY_NASA)
        //programming e-fuse HDCP key in 1 byte by 1 byte mode (Low index in LSB)
        if(dwDataCounter < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_lo;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_lo >> 8;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_hi;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_hi >> 8;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
      #else
        //programming e-fuse HDCP key in 2 byte by 2 byte mode (Low index in MSB)
        if(dwDataCounter < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_lo >> 8;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_lo;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_hi >> 8;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
        if((dwDataCounter) < HDCP_KEY_SIZE)
        {
            u8HdcpKey[dwDataCounter++] = reg_512x8_rdata_hi;
            //printf("%02x ", u8HdcpKey[dwDataCounter-1]);
        }
      #endif
        reg_512x8_addr++;

        if((dwDataCounter % 16) == 0)
        {
            //printf("\r\n");
        }
    }
}
#endif

E_MUX_INPUTPORT _MApi_XC_HDMI_GetPortMapping(INPUT_SOURCE_TYPE_t eINPUT_SOURCE_TYPE)
{
    if ( (eINPUT_SOURCE_TYPE >= INPUT_SOURCE_HDMI)
       &&(eINPUT_SOURCE_TYPE <  INPUT_SOURCE_HDMI_MAX) )
    {
        E_MUX_INPUTPORT eMUX_INPUTPORT = eHdmiPortMappingResult[((U8)(eINPUT_SOURCE_TYPE - INPUT_SOURCE_HDMI))];

        if( eMUX_INPUTPORT == INPUT_PORT_NONE_PORT )
        {
            printf("\nWarning: HDMI_%u mapping to NONE port!\n", (eINPUT_SOURCE_TYPE - INPUT_SOURCE_HDMI));
        }

        return eMUX_INPUTPORT;
    }

    return INPUT_PORT_NONE_PORT;
}

void _MApi_XC_HDMI_PortMapping_Clear(void)
{
    U8 u8DummyIdx = 0;

    for(u8DummyIdx=0; u8DummyIdx<INPUT_HDMI_VIDEO_COUNT; u8DummyIdx++)
    {
        eHdmiPortMappingResult[u8DummyIdx] = INPUT_PORT_NONE_PORT;
    }
}

void _MApi_XC_HDMI_PortMapping_Init(void)
{
    U8 u8DummyIdx = 0;
    U8 u8port_count = 0;
    E_MUX_INPUTPORT eInputPort = INPUT_PORT_NONE_PORT;

    for(u8DummyIdx=0; u8DummyIdx<INPUT_HDMI_VIDEO_COUNT; u8DummyIdx++)
    {
        //Important!
        //Use _MApi_XC_Sys_InputSource_InputPort_Mapping here instead of MApi_XC_Mux_GetHDMIPort
        //Because implementation of MApi_XC_Mux_GetHDMIPort in Utopia is call back function
        //which is normally registered by _MApi_XC_Sys_InputSource_InputPort_Mapping
        //But in very early stage, when XC init not finished, call back function not registered yet!
        _MApi_XC_Sys_InputSource_InputPort_Mapping((INPUT_SOURCE_TYPE_t)(INPUT_SOURCE_HDMI+u8DummyIdx), &eInputPort, &u8port_count);

        if( u8port_count > 0 )
        {
            eHdmiPortMappingResult[u8DummyIdx] = eInputPort;
        }
        else
        {
            eHdmiPortMappingResult[u8DummyIdx] = INPUT_PORT_NONE_PORT;
        }
        //printf("\n\r*****eHdmiPortMappingResult[%d]=%x", u8DummyIdx, eHdmiPortMappingResult[u8DummyIdx]);
    }
}

void MApi_XC_Sys_HDMI_Init(void)
{
}

static void _MApi_XC_Sys_HDMI_Init(void)
{
    XC_HDMI_InitData stXC_HDMI_InitData;
    MS_U8 u8HdcpKey[HDCP_KEY_SIZE]={0};


    //printf("_MApi_XC_Sys_HDMI_Init() at %u\n",  MsOS_GetSystemTime());


#if (HDCP_KEY_TYPE==HDCP_KEY_IN_CODE)
    memcpy(u8HdcpKey, _u8HdcpKey, HDCP_KEY_SIZE);
#elif (HDCP_KEY_TYPE==HDCP_KEY_IN_DB)  // readkey from db
    MApp_DB_LoadHDCP_KEY((MS_U8 *)u8HdcpKey);
#elif(HDCP_KEY_TYPE==HDCP_KEY_IN_EFUSE)
    _MApp_Load_HDCP_FromEfuse((MS_U8 *)u8HdcpKey);
#else
    msAPI_hdcpkeyBurstReadBytes(HDCP_KEY_ADDR, (MS_U8 *)&u8HdcpKey, HDCP_KEY_SIZE);
#endif

#if ENABLE_6M40_4KX2K_PROCESS
    MDrv_Ursa_6M40_SetHDMI_HDCP(u8HdcpKey,HDCP_KEY_SIZE);
#endif


#if ENABLE_SECURITY_R2_HDCP22
#if (HDCP22_KEY_TYPE==HDCP22_KEY_IN_DB)  // readkey from db
    MApp_DB_LoadHDCP22_KEY(_u8AesKey, _u8Hdcp22Key);
#endif
#endif

    //printf(" Read HDCP finished at %u\n",  MsOS_GetSystemTime());

    // start to init HDMI
    memset(&stXC_HDMI_InitData, 0, sizeof(XC_HDMI_InitData));

    stXC_HDMI_InitData.pu8HDCP_Key = u8HdcpKey;

    stXC_HDMI_InitData.bHotPlugInverse[0] = HDCP_HPD_INVERSE;
#if( HDMI_HPD_INVERT_FLAG_SEPERATE )
    stXC_HDMI_InitData.bHotPlugInverse[1] = HDCP_HPD_2_INVERSE;
    stXC_HDMI_InitData.bHotPlugInverse[2] = HDCP_HPD_3_INVERSE;
    stXC_HDMI_InitData.bHotPlugInverse[3] = HDCP_HPD_4_INVERSE;
#else
    stXC_HDMI_InitData.bHotPlugInverse[1] = HDCP_HPD_INVERSE;
    stXC_HDMI_InitData.bHotPlugInverse[2] = HDCP_HPD_INVERSE;
    stXC_HDMI_InitData.bHotPlugInverse[3] = HDCP_HPD_INVERSE;
#endif

    _MApi_XC_HDMI_PortMapping_Clear();
    _MApi_XC_HDMI_PortMapping_Init();


    if( MApi_XC_HDMI_Init(&stXC_HDMI_InitData, sizeof(XC_HDMI_InitData)) != E_XC_HDMI_OK)
    {
        MS_DEBUG_MSG(printf("L:%d, HDMI_Init failed because of InitData wrong, please update header file and compile again\n", __LINE__));
    }

    // Set EQ...
#if (ENABLE_HDMI_4K_2K&&ENABLE_6M40_4KX2K_PROCESS)
#if (INPUT_HDMI_VIDEO_COUNT > 0)
        MDrv_HDMI_Set_EQ(MS_HDMI_EQ_USER_DEFINE,0x00);
    #endif
#endif

    // Reset all port
    MApi_XC_Sys_ResetDVIPort(INPUT_SOURCE_HDMI);
    MApi_XC_Sys_ResetDVIPort(INPUT_SOURCE_HDMI2);
    MApi_XC_Sys_ResetDVIPort(INPUT_SOURCE_HDMI3);
    MApi_XC_Sys_ResetDVIPort(INPUT_SOURCE_HDMI4);

    MApi_XC_HPD_Do_PowerOnInit();

}

#if 0
static void _SetDacTimingSample(void) //sample code for DAC/HDMITx output, need remove later
{
    E_OUTPUT_VIDEO_TIMING_TYPE edac;
    HDMITX_VIDEO_TIMING ehdmitx;

    if (g_PNL_TypeSel == DACOUT_480I)
    {
        edac    = E_RES_720x480I_60Hz;
        ehdmitx = HDMITX_RES_720x480i;
    }
    else if (g_PNL_TypeSel == DACOUT_480P)
    {
        edac    = E_RES_720x480P_60Hz;
        ehdmitx = HDMITX_RES_720x480p;
    }
    else if (g_PNL_TypeSel == DACOUT_576I)
    {
        edac    = E_RES_720x576I_50Hz;
        ehdmitx = HDMITX_RES_720x576i;
    }
    else if (g_PNL_TypeSel == DACOUT_576P)
    {
        edac    = E_RES_720x576P_50Hz;
        ehdmitx = HDMITX_RES_720x576p;
    }
    else if (g_PNL_TypeSel == DACOUT_720P_50)
    {
        edac    = E_RES_1280x720P_50Hz;
        ehdmitx = HDMITX_RES_1280x720p_50Hz;
    }
    else if (g_PNL_TypeSel == DACOUT_720P_60)
    {
        edac    = E_RES_1280x720P_60Hz;
        ehdmitx = HDMITX_RES_1280x720p_60Hz;
    }
    else if (g_PNL_TypeSel == DACOUT_1080I_50)
    {
        edac    = E_RES_1920x1080I_50Hz;
        ehdmitx = HDMITX_RES_1920x1080i_50Hz;
    }
    else if (g_PNL_TypeSel == DACOUT_1080I_60)
    {
        edac    = E_RES_1920x1080I_60Hz;
        ehdmitx = HDMITX_RES_1920x1080i_60Hz;
    }
    else if (g_PNL_TypeSel == DACOUT_1080P_50)
    {
        edac    = E_RES_1920x1080P_50Hz;
        ehdmitx = HDMITX_RES_1920x1080p_50Hz;
    }
    else if (g_PNL_TypeSel == DACOUT_1080P_60)
    {
        edac    = E_RES_1920x1080P_60Hz;
        ehdmitx = HDMITX_RES_1920x1080p_60Hz;
    }
    else
    {
        printf("Error panel type for DAC/HDMITx = %d\n", g_PNL_TypeSel);
        ASSERT(0);
    }
    printf("Sample DAC output...\n");
    MApi_DAC_ClkSel(edac, E_COLOR_8_BIT);
    MApi_DAC_Enable(TRUE, TRUE);
    MApi_DAC_Enable(TRUE, FALSE);
    MApi_DAC_SetClkInv(TRUE, TRUE);
    MApi_DAC_SetYPbPrOutputTiming(edac);

    printf("Sample HDMITx output...\n");
    MApi_HDMITx_TurnOnOff(TRUE);
    MApi_HDMITx_SetHDMITxMode(HDMITX_HDMI);
    MApi_HDMITx_SetTMDSOnOff(TRUE);
    MApi_HDMITx_SetRBChannelSwap(TRUE);
    MApi_HDMITx_SetVideoOnOff(TRUE);
    MApi_HDMITx_SetColorFormat(HDMITX_VIDEO_COLOR_YUV444, HDMITX_VIDEO_COLOR_RGB444);
    MApi_HDMITx_SetVideoOutputTiming(ehdmitx);
}
#endif

#if (ENABLE_DDC_RAM)
E_XC_DDCRAM_PROG_TYPE _MApi_XC_DDC_GetHDMIDDCProgType(U8 uiInputPort)
{
    switch(uiInputPort)
    {
        case INPUT_PORT_DVI0:
             return E_XC_PROG_DVI0_EDID;
             break;

        case INPUT_PORT_DVI1:
             return E_XC_PROG_DVI1_EDID;
             break;

        case INPUT_PORT_DVI2:
             return E_XC_PROG_DVI2_EDID;
             break;

        case INPUT_PORT_DVI3:
          #if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)      \
              ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)      \
              ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)     \
              ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)     \
              ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)    \
              ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)    \
              ) //only support 3 EDID SRAM
             return E_XC_PROG_DVI2_EDID;
          #else
             return E_XC_PROG_DVI3_EDID;/*CHIP_FAMILY_MAZDA*/
          #endif
             break;

         default:
             return E_XC_PROG_DVI0_EDID;
             break;
    }

}

static void _MApi_XC_DDCRam_Init_Hdmi(U8* pu8Edid, E_XC_DDCRAM_PROG_TYPE enProgType, U8 u8PhyAddr, U8 u8PhyAddrPos)
{
    XC_DDCRAM_PROG_INFO stDDCRamInfo;

    //printf("_MApi_XC_DDCRam_Init_Hdmi(enProgType=0x%X, u8PhyAddr=0x%X, u8PhyAddrPos=0x%X)\n", enProgType, u8PhyAddr, u8PhyAddrPos );

    memset(&stDDCRamInfo, 0, sizeof(stDDCRamInfo));

    stDDCRamInfo.EDID = pu8Edid;
    stDDCRamInfo.u16EDIDSize = 256;
    stDDCRamInfo.eDDCProgType = enProgType;
    stDDCRamInfo.u16CECPhyAddr = u8PhyAddr;
    stDDCRamInfo.u8CECPhyAddrIdxL = u8PhyAddrPos+1;
    stDDCRamInfo.u8CECPhyAddrIdxH = u8PhyAddrPos;

  #if 0 // for debug
    int j;
    printf("\033[41;4m DVI%d_EDID = (0x%04X, 0x%02X, 0x%02X) \n",    \
           enProgType,                                          \
           stDDCRamInfo.u16CECPhyAddr,                          \
           stDDCRamInfo.u8CECPhyAddrIdxL,                       \
           stDDCRamInfo.u8CECPhyAddrIdxH);

    for (j=0; j<stDDCRamInfo.u16EDIDSize; j++)
    {
        printf("0x%02X, ", *(stDDCRamInfo.EDID+j) );
        if (((j + 1) % 16) == 0)
        {
            printf("\n");
        }
    }
    printf("\033[0m\n");
  #endif

    // Patch utopia bug!
#if 0//( CHIP_FAMILY_MILAN == CHIP_FAMILY_TYPE)
    // "MCU access ADC sram selection:
    // 0 : Enable access DVI sram
    // 1 : Enable access ADC sram"
    //DDC_WRITE_MASK(REG_DDC_04_L,BITS(10:10,DDC_RAM_SRAM_DVI),BMASK(10:10));
    MDrv_Write2ByteMask(0x0408, 0, BIT10);
#endif

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)
    //#########################################
    // HDMI3(Port D) EDID port must be swapped for (((QFP128)))
    // Board269E/Board118B: DDCDD_CL/DDCDD_DA swapped
    //#########################################
    #if ((MS_BOARD_TYPE_SEL == BD_MST269E_D01A_S_MARLON)||(MS_BOARD_TYPE_SEL == BD_MST118B_10ALU))
    MDrv_WriteRegBit(0x00049e, 1, BIT2); //Bank 0x0004_4F[2]= 1 (reg_ddc_d2_swap: enable)
    #endif
#endif

    MDrv_HDMI_PROG_DDCRAM(&stDDCRamInfo, sizeof(stDDCRamInfo));
}

void _MApi_XC_DDCRam_Init_VGA(void)
{
    XC_DDCRAM_PROG_INFO stDDCRamInfo;
    U8 au8Edid_VGA[128];


    if( FALSE == MApp_Edid_Get_VGATable(au8Edid_VGA) )
        return;

    // init VGA EDID
    stDDCRamInfo.EDID = au8Edid_VGA;
    stDDCRamInfo.u16EDIDSize = 128;
    stDDCRamInfo.eDDCProgType = E_XC_PROG_VGA_EDID;

    MDrv_HDMI_PROG_DDCRAM(&stDDCRamInfo, sizeof(stDDCRamInfo));
}

void _MApi_XC_DDCRam_Init(EunXcInitDDCType eXcInitDDCType, U8 u8PortIndex)
{
#if (INPUT_HDMI_VIDEO_COUNT >= 1)
    U8 au8EdidTblBuf[256];
#endif

    BOOL bNeedInitVGA = FALSE;
    BOOL abNeedInitHdmi[HDMI_PORT_NUM_MAX] = {FALSE, FALSE, FALSE, FALSE};

    BOOL bGetEdidResult = TRUE;
    U8 u8PhyAddrPos = 0;


    // Decide init target ....
    switch(eXcInitDDCType)
    {
        default:
        case E_XC_DDC_INIT_ALL:
            bNeedInitVGA = TRUE;
            abNeedInitHdmi[0] = TRUE;
            abNeedInitHdmi[1] = TRUE;
            abNeedInitHdmi[2] = TRUE;
            abNeedInitHdmi[3] = TRUE;
            break;

        case E_XC_DDC_INIT_ALL_HDMI:
            abNeedInitHdmi[0] = TRUE;
            abNeedInitHdmi[1] = TRUE;
            abNeedInitHdmi[2] = TRUE;
            abNeedInitHdmi[3] = TRUE;
            break;

        case E_XC_DDC_INIT_SRC_HDMI:
            if( u8PortIndex >= HDMI_PORT_NUM_MAX )
                return;

            abNeedInitHdmi[u8PortIndex] = TRUE;

        #if ENABLE_EDID_SWITCH
            if( g_XC_Sys_au8EdidSel[u8PortIndex] == XC_HDMI_EDID_2p0 )
            {
                printf("HDMI_%u Load EDID 2.0\n", u8PortIndex);
            }
            else
            {
                printf("HDMI_%u Load EDID 1.4\n", u8PortIndex);
            }
        #endif
            break;
    }


    // Only init DDC-VGA at power on init
    if( bNeedInitVGA )
    {
        _MApi_XC_DDCRam_Init_VGA();
    }

#if (INPUT_HDMI_VIDEO_COUNT >= 1)
    E_XC_DDCRAM_PROG_TYPE eXC_DDCRam_Port = E_XC_PROG_DVI0_EDID;
    if( abNeedInitHdmi[0] )
    {
    #ifdef INPUT_HDMI1_DDC_PORT // defined in board
        eXC_DDCRam_Port = INPUT_HDMI1_DDC_PORT;
    #else
        eXC_DDCRam_Port = _MApi_XC_DDC_GetHDMIDDCProgType(INPUT_HDMI1_MUX);
    #endif

      #if ENABLE_EDID_SWITCH
        if( g_XC_Sys_au8EdidSel[0] == XC_HDMI_EDID_2p0 )
        {
            bGetEdidResult = MApp_Edid_Get_Table(E_EDID_TBL_HDMI_2p0, 0x10, au8EdidTblBuf, &u8PhyAddrPos);
        }
        else
      #endif
        {
            bGetEdidResult = MApp_Edid_Get_Table(E_EDID_TBL_HDMI_1p3_1p4, 0x10, au8EdidTblBuf, &u8PhyAddrPos);
        }

        if( bGetEdidResult == FALSE )
        {
            printf("\nError: Get Edid Table failed!\n");
            return;
        }

        _MApi_XC_DDCRam_Init_Hdmi(au8EdidTblBuf, eXC_DDCRam_Port, 0x10, u8PhyAddrPos);
    }
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 2)
    if( abNeedInitHdmi[1] )
    {
    #ifdef INPUT_HDMI2_DDC_PORT // defined in board
        eXC_DDCRam_Port = INPUT_HDMI2_DDC_PORT;
    #else
        eXC_DDCRam_Port = _MApi_XC_DDC_GetHDMIDDCProgType(INPUT_HDMI2_MUX);
    #endif

     #if ENABLE_EDID_SWITCH
        if( g_XC_Sys_au8EdidSel[1] == XC_HDMI_EDID_2p0 )
        {
            bGetEdidResult = MApp_Edid_Get_Table(E_EDID_TBL_HDMI_2p0, 0x20, au8EdidTblBuf, &u8PhyAddrPos);
        }
        else
      #endif
        {
            bGetEdidResult = MApp_Edid_Get_Table(E_EDID_TBL_HDMI_1p3_1p4, 0x20, au8EdidTblBuf, &u8PhyAddrPos);
        }

        if( bGetEdidResult == FALSE )
        {
            printf("\nError: Get Edid Table failed!\n");
            return;
        }

        _MApi_XC_DDCRam_Init_Hdmi(au8EdidTblBuf, eXC_DDCRam_Port, 0x20, u8PhyAddrPos);
    }
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 3)
    if( abNeedInitHdmi[2] )
    {
    #ifdef INPUT_HDMI3_DDC_PORT // defined in board
        eXC_DDCRam_Port = INPUT_HDMI3_DDC_PORT;
    #else
        eXC_DDCRam_Port = _MApi_XC_DDC_GetHDMIDDCProgType(INPUT_HDMI3_MUX);
    #endif

      #if ENABLE_EDID_SWITCH
        if( g_XC_Sys_au8EdidSel[2] == XC_HDMI_EDID_2p0 )
        {
            bGetEdidResult = MApp_Edid_Get_Table(E_EDID_TBL_HDMI_2p0, 0x30, au8EdidTblBuf, &u8PhyAddrPos);
        }
       else
      #endif
        {
            bGetEdidResult = MApp_Edid_Get_Table(E_EDID_TBL_HDMI_1p3_1p4, 0x30, au8EdidTblBuf, &u8PhyAddrPos);
        }

        if( bGetEdidResult == FALSE )
        {
            printf("\nError: Get Edid Table failed!\n");
            return;
        }

        _MApi_XC_DDCRam_Init_Hdmi(au8EdidTblBuf, eXC_DDCRam_Port, 0x30, u8PhyAddrPos);
    }
#endif // (INPUT_HDMI_VIDEO_COUNT >= 3)

#if (INPUT_HDMI_VIDEO_COUNT >= 4)
    if( abNeedInitHdmi[3] )
    {
    #ifdef INPUT_HDMI4_DDC_PORT // defined in board
        eXC_DDCRam_Port = INPUT_HDMI4_DDC_PORT;
    #else
        eXC_DDCRam_Port = _MApi_XC_DDC_GetHDMIDDCProgType(INPUT_HDMI4_MUX);
    #endif

      #if ENABLE_EDID_SWITCH
        if( g_XC_Sys_au8EdidSel[3] == XC_HDMI_EDID_2p0 )
        {
            bGetEdidResult = MApp_Edid_Get_Table(E_EDID_TBL_HDMI_2p0, 0x40, au8EdidTblBuf, &u8PhyAddrPos);
        }
        else
      #endif
        {
            bGetEdidResult = MApp_Edid_Get_Table(E_EDID_TBL_HDMI_1p3_1p4, 0x40, au8EdidTblBuf, &u8PhyAddrPos);
        }

        if( bGetEdidResult == FALSE )
        {
            printf("\nError: Get Edid Table failed!\n");
            return;
        }

        _MApi_XC_DDCRam_Init_Hdmi(au8EdidTblBuf, eXC_DDCRam_Port, 0x40, u8PhyAddrPos);
    }
#endif // (INPUT_HDMI_VIDEO_COUNT >= 4)
}
#endif // #if (ENABLE_DDC_RAM)


#if ENALBE_XC_ISR_SAMPLE
#define MAX_XC_VSYNC_ISR_NUM        (12)
static U8 u8XC_VSync_ISR_ID[MAX_XC_VSYNC_ISR_NUM];
static U32 u32LastExecuteTime[MAX_XC_VSYNC_ISR_NUM];
static U8 u8FR[MAX_XC_VSYNC_ISR_NUM];
static U8 u8MaxExecuteTime[MAX_XC_VSYNC_ISR_NUM];

static void _MApi_XC_Sys_VSync_Init(void)
{
    U8 i;

    for(i=0; i<MAX_XC_VSYNC_ISR_NUM; i++)
    {
        u8XC_VSync_ISR_ID[i] = i;
        u32LastExecuteTime[i] = 0;
        u8FR[i] = 0;
        u8MaxExecuteTime[i] = 0;
    }
}

static void _MApi_XC_Sys_VSync_ISR(XC_INT_SRC eIntNum, void * pParam)
{
    U8 u8IsrID = *((MS_U8 *) pParam);

    if(eIntNum != XC_INT_VSINT)
    {
        printf("[VsyncISR %d] wrong Int Num\n", u8IsrID);
    }

    u8FR[u8IsrID] += u8IsrID;

    if(MsOS_Timer_DiffTimeFromNow(u32LastExecuteTime[u8IsrID]) > 1000)
    {
        u8MaxExecuteTime[u8IsrID]++;
        printf("[VsyncISR %d][%d] Out FR = %d\n", u8IsrID, u8MaxExecuteTime[u8IsrID], u8FR[u8IsrID]);

        u32LastExecuteTime[u8IsrID] = MsOS_GetSystemTime();
        u8FR[u8IsrID] = 0;

        if(u8IsrID != 1)
        {
            if(u8MaxExecuteTime[u8IsrID] > u8IsrID)
            {
                MApi_XC_InterruptDeAttach(XC_INT_VSINT, _MApi_XC_Sys_VSync_ISR, (void *) &u8XC_VSync_ISR_ID[u8IsrID]);

                if(u8IsrID == 9)
                {
                    // de-attach ISR ID 0 after all de-attached
                    MApi_XC_InterruptDeAttach(XC_INT_VSINT, _MApi_XC_Sys_VSync_ISR, (void *) &u8XC_VSync_ISR_ID[1]);
                }
            }
        }
    }
}
#endif // #if ENALBE_XC_ISR_SAMPLE

#if( ENABLE_XC_ISR_OPVSYNC )
static U32 g_XC_SYS_u32OPVSyncCount = 0;

#define DEBUG_OP_VSYNC  0
#if(DEBUG_OP_VSYNC)
#define XC_SYS_VSYNC_TIME_NUMS  4
static U8 g_XC_SYS_u32OPVSyncTimeIdx;
static U32 g_XC_SYS_u32OPVSyncTime[2][XC_SYS_VSYNC_TIME_NUMS];
#endif

#if(ENABLE_DLC_ISR &&ENABLE_DLC)
static U32 u32DLC_ISR_Time;
#endif

void _MApi_XC_Sys_OPVSync_ISR(SC_INT_SRC eIntNum, void * pParam)
{
    //U8 u8IsrID = *((MS_U8 *) pParam);
    UNUSED(eIntNum);
    UNUSED(pParam);

    g_XC_SYS_u32OPVSyncCount += 1;

#if(DEBUG_OP_VSYNC)
    if( g_XC_SYS_u32OPVSyncTimeIdx >= XC_SYS_VSYNC_TIME_NUMS )
        g_XC_SYS_u32OPVSyncTimeIdx = 0;
    g_XC_SYS_u32OPVSyncTime[0][g_XC_SYS_u32OPVSyncTimeIdx] = MDrv_PIU_TIMER_CAP_Get_Us();
#endif

#if( PQ_FILM_DI_RUN_IN_ISR )
    MDrv_PQ_AdaptiveTuning_ISR();
#endif

#if(ENABLE_DLC_ISR &&ENABLE_DLC)
    u32DLC_ISR_Time = MDrv_PIU_TIMER_CAP_Get_Us();
    MApi_XC_Sys_DLC_Task();
    u32DLC_ISR_Time = MDrv_PIU_TIMER_CAP_Get_Us() - u32DLC_ISR_Time;
#endif

#if(DEBUG_OP_VSYNC)
    g_XC_SYS_u32OPVSyncTime[1][g_XC_SYS_u32OPVSyncTimeIdx] = MDrv_PIU_TIMER_CAP_Get_Us();
    g_XC_SYS_u32OPVSyncTimeIdx += 1;
#endif

#if (LD_ENABLE)
    MApi_LD_ISR_OVSync();
#endif

}

U32 MApi_XC_Sys_Get_OutputVSyncCount(void)
{
#if(DEBUG_OP_VSYNC)
    U8 i;
    for( i = 0; i < XC_SYS_VSYNC_TIME_NUMS; ++ i )
    {
        printf("%u %u\n", g_XC_SYS_u32OPVSyncTime[0][i], g_XC_SYS_u32OPVSyncTime[1][i]);
    }
#endif

    return g_XC_SYS_u32OPVSyncCount;
}
#endif

#if( ENABLE_XC_ISR_IPVSYNC )
static U32 g_XC_SYS_u32IPVSyncCount = 0;
void _MApi_XC_Sys_IPVSync_ISR(SC_INT_SRC eIntNum, void * pParam)
{
    //U8 u8IsrID = *((MS_U8 *) pParam);
    UNUSED(eIntNum);
    UNUSED(pParam);

    g_XC_SYS_u32IPVSyncCount += 1;

}
#endif

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
void MApi_XC_Sys_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    XC_INITDATA sXC_InitData;


    DEBUG_INIT_FLOW(printf("MApi_XC_Sys_Init()\n"););
//    printf("Current XC driver support %d windows\n", MApi_XC_GetInfo()->u8MaxWindowNum);

#if( HDMITX_4030_ENABLE==ENABLE)
    MApi_PNL_Init_MISC(E_APIPNL_MISC_ENABLE_MANUAL_VSYNC_CTRL);
#endif

    _MApi_XC_Sys_Init_Panel();

    // reset to zero
    memset(&sXC_InitData, 0, sizeof(XC_INITDATA));

    _MApi_XC_Sys_Init_XC(&sXC_InitData);

#if( HDMITX_4030_ENABLE==ENABLE)
    MApi_SC_ForceFreerun(TRUE);
    MApi_SC_SetFreerunVFreq(VFREQ_FROM_PANEL);
#endif

// init DLC
#if ENABLE_DLC
    _MApi_XC_Sys_Init_DLC();
#endif

#if ENABLE_DBC
    MApi_XC_DLC_CGC_ResetYGain();
    MApi_XC_DLC_CGC_ResetCGain();
#else
    #if ENABLE_DLC
    MApi_XC_DLC_CGC_ResetCGain();
    #endif
#endif

    _MApi_XC_Sys_Init_PQ(&sXC_InitData);

#if ENABLE_DBC
    MApi_XC_DLC_CGC_CheckYGainInPQCom();
    MApi_XC_DLC_CGC_CheckCGainInPQCom();
#else
    #if ENABLE_DLC
        MApi_XC_DLC_CGC_CheckCGainInPQCom();
    #endif
#endif
    _MApi_XC_Sys_Init_ACE();


    MApi_XC_ModeParse_Init();

#if ENABLE_VGA_EIA_TIMING
    //MApi_XC_ModeParse_SetVGAEIA(TRUE);
#endif

    // Init timing monitor
    MApi_XC_PCMonitor_Init(MApi_XC_GetInfo()->u8MaxWindowNum);

    //MApi_XC_PCMonitor_SetTimingCount(8,10);
    MApi_XC_PCMonitor_SetTimingCount(PC_MODE_SYNC_STABLE_COUNT, PC_MODE_NOSYNC_COUNT);
    //printf("PC_MODE_SYNC_STABLE_COUNT=%u, PC_MODE_NOSYNC_COUNT=%u\n", PC_MODE_SYNC_STABLE_COUNT, PC_MODE_NOSYNC_COUNT);

    // Set HDMI Timing monitor stable/NoSync time
    //MApi_XC_PCMonitor_SetTimingCountEx(INPUT_SOURCE_HDMI, 10, 5);
    MApi_XC_PCMonitor_SetTimingCountEx(INPUT_SOURCE_HDMI, HDMI_SYNC_STABLE_COUNT, HDMI_NOSYNC_COUNT);
    //printf("HDMI_SYNC_STABLE_COUNT=%u, HDMI_NOSYNC_COUNT=%u\n", HDMI_SYNC_STABLE_COUNT, HDMI_NOSYNC_COUNT);

    // Init DDCRam if any
#if (ENABLE_DDC_RAM)
    _MApi_XC_DDCRam_Init(E_XC_DDC_INIT_ALL, 0);
#endif
    // Init HDCP and CEC
#if (INPUT_HDMI_VIDEO_COUNT > 0)

    //MHL Support Info
  #if (MHL_TYPE == MHL_TYPE_INTERNAL)
    MApi_XC_Mux_SetSupportMhlPathInfo(INPUT_SUPPORT_MHL_PATH);
   #if (ENABLE_MHL == ENABLE)
    msAPI_MHL_MHLSupportPath(INPUT_SUPPORT_MHL_PATH);
    MApi_XC_Mux_SetMhlHotPlugInverseInfo(FALSE);
   #endif
  #endif

    _MApi_XC_Sys_HDMI_Init();

    //MHL
  #if (ENABLE_MHL == ENABLE)
      msAPI_MHL_Initialization();
  #endif

    //CEC
  #if (ENABLE_CEC)    //Move CEC init to later in init
    msAPI_CEC_Init();
  #endif

#endif // #if (INPUT_HDMI_VIDEO_COUNT > 0)


    //Init Mux
    MApi_XC_Mux_Init(_MApi_XC_Sys_InputSource_InputPort_Mapping);


    //DAC output setting: sample code

#if (ENABLE_VE)
    if(MDrv_VE_GetInfo()->stCaps.bVESupported)
    {
    #if( VE_FRAMEBUFFER_LEN == 0 )   // Check VE buffer
        #error "VE_FRAMEBUFFER_LEN == 0"
    #endif

        MDrv_VE_Init(((VE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (VE_FRAMEBUFFER_ADR)));
    }

  // Init VE to a display state to show out the "NO Signal" symbol
 #if((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE))
    msAPI_Scaler_SetVE(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), OUTPUT_CVBS1);
  #if (ENABLE_CVBSOUT_2)
    msAPI_Scaler_SetVE(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), OUTPUT_CVBS2);
  #endif
 #endif //(ALL_SOURCE_OUTPUT_THROUGH_VE == ENABLE)
#endif //ENABLE_VE

    //FPLL FSM
    MApi_SC_Enable_FPLL_FSM(TRUE);


#if ENABLE_SMOOTH_PANEL_OUTPUT
    XC_OUTPUT_TIMING_ADJUST_SETTING adjust_setting;
    memset(&adjust_setting,0,sizeof(XC_OUTPUT_TIMING_ADJUST_SETTING));
    adjust_setting.u32TimingAdjustSetting_version = XC_OUTPUT_TIMING_ADJUST_VERSION;
    adjust_setting.u16VTotal_Delay = 35;   // ms
    adjust_setting.u16VTotal_Step = 45;    // number of step from init to target
    adjust_setting.u16VTotal_Ratio = 1000; // 100%
    MApi_XC_SetOutputAdjustSetting( &adjust_setting);
#endif


  #if (!BLOADER)
    #if (XC_BRINGUP == 0)
      MDrv_BW_LoadInitTable();
    #endif
  #endif

#if ENALBE_XC_ISR_SAMPLE
    {
        U8 i;

        _MApi_XC_Sys_VSync_Init();

        for(i=0; i<MAX_XC_VSYNC_ISR_NUM; i++)
        {
            MApi_XC_InterruptAttach(XC_INT_VSINT, _MApi_XC_Sys_VSync_ISR, (void *) &u8XC_VSync_ISR_ID[i]);
        }
    }
#endif

#if(ENABLE_XC_ISR_OPVSYNC)
    MApi_XC_InterruptAttach(SC_INT_VSINT, _MApi_XC_Sys_OPVSync_ISR, NULL);
#endif
#if(ENABLE_XC_ISR_IPVSYNC)
    MApi_XC_InterruptAttach(SC_INT_F2_IPVS_SB, _MApi_XC_Sys_IPVSync_ISR, NULL);
#endif

    MApi_XC_DLC_SetBleOnOff(DISABLE);

#if(ENABLE_FRC_R2)
{
    printf("Load FRC R2 bin - at %s %u\n", __FUNCTION__, __LINE__);
    msAPI_COPRO_Init(BIN_ID_CODE_AEON_FRC,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MM_MEM_ADR | MIU_INTERVAL) : (AEON_MM_MEM_ADR)),AEON_MM_MEM_LEN);
    printf("Load FRC R2 bin - end\n");
}
#endif

    MApi_XC_EnableIPAutoNoSignal(DISABLE, MAIN_WINDOW);

    // Bandwith setting must be load when power on init
    // to prevent HW defalut value is not good~~
    MDrv_BW_LoadTableByContext(PQ_MAIN_WINDOW);

    DEBUG_INIT_FLOW( printf("MApi_XC_Sys_Init() init done\n"); );

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void msAPI_Scaler_ChangePanelType(U8 u8ResolutionType, SCALER_WIN eWindow)
{
    XC_PANEL_INFO stPanelInfo;
    printf("----u8ResolutionType %x---\n",u8ResolutionType );
    UNUSED(eWindow);
    MApi_PNL_ChangePanelType(MApi_XC_GetPanelSpec((PANEL_RESOLUTION_TYPE)u8ResolutionType));
    stPanelInfo.u16HStart               = g_IPanel.HStart();
    stPanelInfo.u16VStart               = g_IPanel.VStart();
    stPanelInfo.u16Width                = g_IPanel.Width();
    stPanelInfo.u16Height               = g_IPanel.Height();
    stPanelInfo.u16HTotal               = g_IPanel.HTotal();
    stPanelInfo.u16VTotal               = g_IPanel.VTotal();
    stPanelInfo.u16DefaultVFreq         = g_IPanel.DefaultVFreq();
    stPanelInfo.u8LPLL_Mode             = g_IPanel.LPLL_Mode();
    stPanelInfo.enPnl_Out_Timing_Mode   = (E_XC_PNL_OUT_TIMING_MODE)g_IPanel.OutTimingMode();
    stPanelInfo.u16DefaultHTotal        = g_IPanel.HTotal();
    stPanelInfo.u16DefaultVTotal        = g_IPanel.VTotal();
    stPanelInfo.u32MinSET               = g_IPanel.MinSET();
    stPanelInfo.u32MaxSET               = g_IPanel.MaxSET();
    stPanelInfo.eLPLL_Type              = (E_XC_PNL_LPLL_TYPE)g_IPanel.LPLL_Type();
    //printf("---u8LPLL_Mode %d---\n",stPanelInfo.u8LPLL_Mode );
    //printf("---stPanelInfo.u16DefaultVFreq %d--\n",stPanelInfo.u16DefaultVFreq);
    //printf("---stPanelInfo.u16DefaultVTotal  %d--\n",stPanelInfo.u16DefaultVTotal );
   // printf("---stPanelInfo.u16DefaultHTotal  %d--\n",stPanelInfo.u16DefaultHTotal);
    MApi_XC_ChangePanelType(&stPanelInfo);
    MApi_Mod_Do_Calibration();
}

//===================================================

#define ENABLE_DEBUG_XC_FPLL    0
#if ENABLE_DEBUG_XC_FPLL
    #define DEBUG_XC_FPLL(x)    x
#else
    #define DEBUG_XC_FPLL(x)
#endif

#define MS_ABS(a,b) (((a)<(b))?((b)-(a)):((a)-(b)))

#define FPLL_PRD_THRESHOLD  (0x80)         // The PRD must be smaller than this value to indicate almost finished PRD lock
#define PHASE_OFFSET_LIMIT  0x80UL

void MApi_XC_Sys_CheckFpllStatusTask(void)
{
    static U32 s_u32CheckFpllStatusTask_LastTime;

    static U32 g_XC_Sys_u32CheckFpll_StartTime = 0;

#define CHECK_FPLL_TIMEOUT  3000


/*
    U8 u8Reg_SC_124E_Val = MApi_XC_R2BYTE(0x124E);
    if( u8Reg_SC_124E_Val != 0x89 )
    {
        printf(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! OPW=0x%X ", u8Reg_SC_124E_Val);
    }

    U8 u8Reg_SC_0104_Val = MApi_XC_R2BYTE(0x0104);
    //if( u8Reg_SC_0104_Val != 0x89 )
    {
        printf(" u8Reg_SC_0104_Val=0x%X ", u8Reg_SC_0104_Val);
    }
    */


    if( msAPI_Timer_DiffTime_2(s_u32CheckFpllStatusTask_LastTime, MsOS_GetSystemTime()) < 20 )
        return;

    s_u32CheckFpllStatusTask_LastTime = MsOS_GetSystemTime();


    if( 0 == (msAPI_Scaler_GetScreenMute(MAIN_WINDOW)&E_SCREEN_MUTE_BY_SCALER_FPLL) )
    //if( 0 == MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
    {
        g_XC_Sys_u32CheckFpll_StartTime = 0;
        return;
    }

    if( g_XC_Sys_u32CheckFpll_StartTime == 0 )
    {
        g_XC_Sys_u32CheckFpll_StartTime = MsOS_GetSystemTime();
    }

    // Check FPLL function on/off?
    U16 u16Reg_3118_val = MDrv_Read2Byte(0x103118);
    if( (u16Reg_3118_val&0x08) == 0 )
    {
        printf("FPLL is off!\n");
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, DISABLE, 0, MAIN_WINDOW);
        return;
    }

    // Check timeout
    U32 u32AlreadyCheckTime = msAPI_Timer_DiffTime_2(g_XC_Sys_u32CheckFpll_StartTime, MsOS_GetSystemTime());
    if( u32AlreadyCheckTime > CHECK_FPLL_TIMEOUT )
    {
        printf("Check FPLL timeout!\n");
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, DISABLE, 0, MAIN_WINDOW);
        return;
    }


    BOOL bIsLockFreqMode = (MDrv_Read4Byte(0x1031E1)&BIT7)?TRUE:FALSE;

    U16 u16FpllFSM = MHAL_XC_Get_Fpll_FSM_State();

    if( u16FpllFSM == 0 )
        return;



    U32 u32Reg_3122_Phase_val_1 = MDrv_Read4Byte(0x103122);
    U32 u32Reg_3126_Prd_val_1 = MDrv_Read4Byte(0x103126);
    S32 s32Reg_3122_Phase_val_2 = ((u32Reg_3122_Phase_val_1&0x10000)?(-1):(1)) * (u32Reg_3122_Phase_val_1&0xFFFF);
    S32 s32Reg_3126_Prd_val_2 = ((u32Reg_3126_Prd_val_1&0x10000)?(-1):(1)) * (u32Reg_3126_Prd_val_1&0xFFFF);

    static S32 s_s32Reg_3122_Phase_val_Last;
    static S32 s_s32Reg_3126_Prd_val_Last;

    S32 s32Reg_3122_Phase_val_Delta = MS_ABS(s_s32Reg_3122_Phase_val_Last, s32Reg_3122_Phase_val_2);
    S32 s32Reg_3126_Prd_val_Delta = MS_ABS(s_s32Reg_3126_Prd_val_Last, s32Reg_3126_Prd_val_2);


#if ( ENABLE_DEBUG_XC_FPLL )
    U32 u32Reg_3142_val = MDrv_Read4Byte(0x103142);
    U32 u32Reg_3146_val = MDrv_Read4Byte(0x103146);
    U32 u32InOutVsPrdDiff = MS_ABS(u32Reg_3142_val, u32Reg_3146_val);

    U8 u8InVsFactor = ((u16Reg_3118_val>>8)&0x0F) + 1;
    U8 u8OutVsFactor = ((u16Reg_3118_val>>12)&0x0F) + 1;

    U32 u32InVFreq = 0;
    U32 u32OutVFreq = 0;

    if( u32Reg_3142_val )
    {
        u32InVFreq = 120000000 * u8InVsFactor / u32Reg_3142_val;
    }
    if( u32Reg_3146_val )
    {
        u32OutVFreq = 120000000 * u8OutVsFactor / u32Reg_3146_val;
    }
#endif

    BOOL bFpllPrdLockDone = FALSE;
    BOOL bFpllPhaseStable = FALSE;
    BOOL bCurFpllStatus = FALSE;


    DEBUG_XC_FPLL( printf("FPLL info at %u, already check=%ums\n", MsOS_GetSystemTime(), u32AlreadyCheckTime); );

    DEBUG_XC_FPLL( printf(" REG_3118=0x%X,", u16Reg_3118_val); );
    DEBUG_XC_FPLL( printf(" bIsLockFreqMode=%u\n", bIsLockFreqMode); );

    DEBUG_XC_FPLL( printf(" 3122(Phase): 0x%X, %d, %d, D=0x%X\n",
        u32Reg_3122_Phase_val_1, s32Reg_3122_Phase_val_2, s_s32Reg_3122_Phase_val_Last, s32Reg_3122_Phase_val_Delta ); );

    DEBUG_XC_FPLL( printf(" 3126(Prd): 0x%X, %d, %d, D=0x%X\n",
        u32Reg_3126_Prd_val_1, s32Reg_3126_Prd_val_2, s_s32Reg_3126_Prd_val_Last, s32Reg_3126_Prd_val_Delta ); );

    DEBUG_XC_FPLL( printf(" 3142=0x%X, 3146=0x%X, diff=0x%X\n", u32Reg_3142_val, u32Reg_3146_val, u32InOutVsPrdDiff); );
    DEBUG_XC_FPLL( printf(" In:Out=%u:%u ", u8InVsFactor, u8OutVsFactor); );
    DEBUG_XC_FPLL( printf(" iVf=%u, oVf=%u\n", u32InVFreq, u32OutVFreq); );

    DEBUG_XC_FPLL( printf(" => 3154(FSM)=0x%X\n", u16FpllFSM ); );

    // Check if freq(Prd) lock?
    if( bIsLockFreqMode )
    {
        if( ( (u32Reg_3126_Prd_val_1&0xFFFF) < 10)
          &&(s32Reg_3126_Prd_val_Delta < 5 ) // Check delta
          )
        {
            bFpllPrdLockDone = TRUE;
            DEBUG_XC_FPLL( printf(" => Prd Lock\n" ); );
        }
    }
    else
    {
        if( ( (u32Reg_3126_Prd_val_1&0xFFFF) < FPLL_PRD_THRESHOLD)
          &&(s32Reg_3126_Prd_val_Delta < 0x40 ) // Check delta
          )
        {
            bFpllPrdLockDone = TRUE;
            DEBUG_XC_FPLL( printf(" => Prd Lock\n" ); );
        }
    }

    // Check if phase lock
    if( bIsLockFreqMode )
    {
        // In lock freq mode, HW will not lock phase
        bFpllPhaseStable = TRUE;
    }
    else
    {
        if( ( (u32Reg_3122_Phase_val_1&0xFFFF) < PHASE_OFFSET_LIMIT)
          &&(s32Reg_3122_Phase_val_Delta < 0x40 ) // Check delta
          ) // todo: compare last
        {
            bFpllPhaseStable = TRUE;
            DEBUG_XC_FPLL( printf(" => Phase Stable\n" ); );
        }

    }


// FPLL FSM status:
// 2:0:     frame pll FSM state
//      3'h0 : free run
//      3'h1 : lock_freq
//      3'h2 : reduce_phase
//      3'h3 : wait phase_close
//      3'h4 : lock_phase
// 4: odclk stable flag
// 5: idclk stable flag
// 6: prd lock done flag
// 7: phase reduce done flag
// 8: phase lock done flag

    // Check lock done
    if( u16FpllFSM == 0x1F4 )
    {
        bCurFpllStatus = TRUE;
    }
    else if( bIsLockFreqMode ) // Lock freq mode
    {
        //if( (u16FpllFSM == 0xF4) )
        {
            if( bFpllPrdLockDone && bFpllPhaseStable )
            {
                bCurFpllStatus = TRUE;
            }
        }
    }
    else // Normal fpll mode
    {
        //bCurFpllStatus = FALSE;
        //if( (u16FpllFSM == 0xF4)||(u16FpllFSM == 0xB4)||(u16FpllFSM == 0xA4) )
        if( (u16FpllFSM & (BIT7|BIT5|0xF)) == (BIT7|BIT5|0x4) )
        {
            if( bFpllPrdLockDone
              &&bFpllPhaseStable
              &&(FALSE==MApi_XC_IsCurrentFrameBufferLessMode()) // FB mode
              )
            {
                bCurFpllStatus = TRUE;
            }
        }
    }

    /*if( MApi_XC_IsInputSourceDisabled(MAIN_WINDOW) )
    {
        printf("InputDis=1\n" );
    }*/


    //printf("GetScreenMute(MAIN)=0x%X\n", msAPI_Scaler_GetScreenMute(MAIN_WINDOW) );
    if( (msAPI_Scaler_GetScreenMute(MAIN_WINDOW)&E_SCREEN_MUTE_BY_SCALER_FPLL)  )
    {
        //printf("{Wait locked: 0x%X}", MDrv_Read2Byte(0x103154)&0x1FF );
        if( bCurFpllStatus )
        {
            printf("FPLL locked at %u use %u\n", MsOS_GetSystemTime(), u32AlreadyCheckTime);
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, DISABLE, 0, MAIN_WINDOW);
        }
    }

    s_s32Reg_3122_Phase_val_Last = s32Reg_3122_Phase_val_2;
    s_s32Reg_3126_Prd_val_Last = s32Reg_3126_Prd_val_2;

}

/******************************************************************************/
///-This function will enable/diable free run screen
///@param bEnable \b IN: enable/disable blue screen
///-False: Disable
///-TRUE: Enable
///@param u8Color \b IN: the color setting
///-  0: Black
///-  1: White
///-  2: Blue
/******************************************************************************/
#if(CHIP_FAMILY_NASA == CHIP_FAMILY_TYPE)
    #define ENABLE_SET_BLUE_SCREEN_SPEED_UP ENABLE
#else
    #define ENABLE_SET_BLUE_SCREEN_SPEED_UP DISABLE
#endif

#if( ENABLE_SET_BLUE_SCREEN_SPEED_UP )
void MDrv_SC_SetSkipWaitVsync( MS_BOOL eWindow,MS_BOOL bIsSkipWaitVsyn);
MS_BOOL MDrv_SC_GetSkipWaitVsync( MS_BOOL bScalerWin);
#endif

#if ENABLE_DEBUG_BULE_SCREEN
    #define DEBUG_BULE_SCREEN(x)    x
#else
    #define DEBUG_BULE_SCREEN(x)
#endif

void msAPI_XC_Sys_Set_DisableInput(BOOLEAN bEnable, SCALER_WIN eWindow)
{
    BOOLEAN bCurXCInputSourceDisabled = MApi_XC_IsInputSourceDisabled(eWindow);

    //PRINT_CURRENT_LINE();
    //printf("msAPI_XC_Sys_Set_DisableInput(en=%u, eWin=%u)\n", bEnable, eWindow);
    //printf("bCurXCInputSourceDisabled=%u\n", bCurXCInputSourceDisabled);

    if( bEnable != bCurXCInputSourceDisabled )
    {
        TIMER_SET_DELAY_ID_START(E_DELAY_ID_DRV_XC_SET_DISABLE_INPUT);

        MApi_XC_DisableInputSource(bEnable, eWindow);

        TIMER_SET_DELAY_ID_END();
    }
}

static U8 s_u8BlueScreenStatus[MAX_WINDOW]={0xFF, 0xFF};

U8 MApi_XC_Sys_Get_BlueScreenStatus(SCALER_WIN eWindow)
{
    if( eWindow >= MAX_WINDOW )
        return FALSE;

    return s_u8BlueScreenStatus[eWindow];
}

#if ENABLE_DEBUG_BULE_SCREEN
void msAPI_Scaler_SetBlueScreen_2( BOOLEAN bEnable, U8 u8Color, U16 u16ScreenUnMuteTime, SCALER_WIN eWindow)
#else
void msAPI_Scaler_SetBlueScreen( BOOLEAN bEnable, U8 u8Color, U16 u16ScreenUnMuteTime, SCALER_WIN eWindow)
#endif
{
#if( ENABLE_SET_BLUE_SCREEN_SPEED_UP )
    BOOL bSetInBlanking = TRUE;
    BOOL bBackupSCSkipWaitVsync = MDrv_SC_GetSkipWaitVsync(eWindow);
#endif


    //LOG_CHANGE_CHANNEL_TIME("BlueScr-1");

#if( ENABLE_SET_BLUE_SCREEN_SPEED_UP )
    if( MApi_XC_IsBlackVideoEnable(eWindow) )
    {
        bSetInBlanking = FALSE;
    }
    else
    {
        bSetInBlanking = TRUE;
    }
    MDrv_SC_SetSkipWaitVsync(eWindow, (bSetInBlanking?0:1));
#endif

    DEBUG_BULE_SCREEN(printf("msAPI_Scaler_SetBlueScreen(bEnable=%u, t=%u, win=%u) at %u\n", bEnable, u16ScreenUnMuteTime, eWindow, msAPI_Timer_GetTime0()););

    if (bEnable )
    {
      #if 0
        //if(stSystemInfo[eWindow].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN)
        if( s_u8BlueScreenStatus[eWindow] == TRUE )
        {
            // sws check
            printf("msAPI_Scaler_SetBlueScreen() enable again! (u8PanelPowerStatus=%bx)\n", stSystemInfo[eWindow].u8PanelPowerStatus);

            // 20100423.DanielWu: We can not return!
            // Because someone outside use MApi_XC_DisableInputSource() without update u8PanelPowerStatus!!
            //return;
        }
      #endif

        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, ENABLE, 0, eWindow);
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, DISABLE, 0, eWindow);

        u8Color = (u8Color >= E_XC_FREE_RUN_COLOR_MAX) ? E_XC_FREE_RUN_COLOR_BLACK : u8Color;

        if( eWindow == MAIN_WINDOW )
        {
            MApi_XC_SetFreeRunTiming();
        }

        //MApi_XC_SetDispWindowColor(astNoSignalColor[u8Color], eWindow); //gchen @ 20180319 //screen saver color //MP333
        if(eWindow == MAIN_WINDOW)
        {
        	if(gU8PanTaskFlag)
        	{
			printf("MApi_XC_SetDispWindowColor 222 \n"); //MP333 //gchen @ 20180509 //change signal color 
        		MApi_XC_SetDispWindowColor(astNoSignalColor[0], eWindow);
        	}
			else
			{
				printf("MApi_XC_SetDispWindowColor 111 \n"); //MP333 //gchen @ 20180509 //change signal color 
	        		MApi_XC_SetDispWindowColor(astNoSignalColor[2], eWindow);
			}
        }
	 else
	 {
		MApi_XC_SetDispWindowColor(astNoSignalColor[0], eWindow);
	 }

      #if ENABLE_3D_PROCESS
        if( eWindow == MAIN_WINDOW )
        {
            //MApi_XC_SetDispWindowColor(astNoSignalColor[u8Color], SUB_WINDOW); //gchen @ 20180319 //screen saver color //MP333
            MApi_XC_SetDispWindowColor(astNoSignalColor[0], SUB_WINDOW);
        }
      #endif


    #if 1// HW_AUTO_DISABLE_INPUTSOURCE_WHEN_NO_SIGNAL
        MApi_XC_EnableIPAutoNoSignal(DISABLE, eWindow );
    #endif

    #if 1//(HW_AUTO_DISABLE_INPUTSOURCE_WHEN_HDMI_AVMUTE)
        MHAL_HDMI_Set_EnAvMute(DISABLE);
    #endif


        //MApi_XC_FreezeImg(ENABLE, eWindow);

        msAPI_XC_Sys_Set_DisableInput(TRUE, eWindow); // //MApi_XC_DisableInputSource(TRUE, eWindow);


        if( (!IsATVInUse()) )//resolve Mantis 0379359(M_Chakra3) ATV Program noise increase  after ATV Manual search
        {
            // turn off NR for disable memory write (for MM case)
            MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_OFF, eWindow );
        }

        //stSystemInfo[eWindow].u8PanelPowerStatus |= PANEL_POWER_BLUESCREEN;
        s_u8BlueScreenStatus[eWindow] = TRUE;

    }
    else
    {
        //if(stSystemInfo[eWindow].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN)
        if( s_u8BlueScreenStatus[eWindow] )
        {
            //LOG_CHANGE_CHANNEL_TIME("BlueScr-6");

            msAPI_XC_Sys_Set_DisableInput(FALSE, eWindow);

        #if HW_AUTO_DISABLE_INPUTSOURCE_WHEN_NO_SIGNAL
            if (IsYPbPrInUse()|| IsVgaInUse()||IsHDMIInUse() )
            {
                MApi_XC_EnableIPAutoNoSignal(ENABLE, eWindow );
            }
        #endif

        #if(HW_AUTO_DISABLE_INPUTSOURCE_WHEN_HDMI_AVMUTE)
            if( IsHDMIInUse() )
            {
                MHAL_HDMI_Set_EnAvMute(ENABLE);
            }
        #endif

            //MApi_XC_FreezeImg(FALSE, eWindow);

            //LOG_CHANGE_CHANNEL_TIME("BlueScr-7");

            if((g_IPanel.LPLL_Type() == E_XC_PNL_LPLL_MINILVDS) || (g_IPanel.LPLL_Type() == E_XC_PNL_LPLL_ANALOG_MINILVDS) || (g_IPanel.LPLL_Type() == E_XC_PNL_LPLL_DIGITAL_MINILVDS))
            {
                MApi_PNL_TCON_Count_Reset(1);
                MApi_PNL_TCON_Count_Reset(0);
            }
            LOG_CHANGE_CHANNEL_TIME("BlueScr off");

            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, u16ScreenUnMuteTime, eWindow);

            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, DISABLE, 0, eWindow);

        #if( (CHIP_FAMILY_NASA == CHIP_FAMILY_TYPE ) \
           /*||(CHIP_FAMILY_MILAN == CHIP_FAMILY_TYPE ) */\
           )
            if( (eWindow == MAIN_WINDOW) && MApi_XC_IsCurrentFrameBufferLessMode() )
            {
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, ENABLE, 0, MAIN_WINDOW);
            }
        #endif

            //stSystemInfo[eWindow].u8PanelPowerStatus &= ~PANEL_POWER_BLUESCREEN;
            s_u8BlueScreenStatus[eWindow] = FALSE;
        }
        else
        {
            //MSG(printf("Disable BlueScreen return\n"));
        }
    }

#if( ENABLE_SET_BLUE_SCREEN_SPEED_UP )
    MDrv_SC_SetSkipWaitVsync(eWindow, bBackupSCSkipWaitVsync );
#endif

    //LOG_CHANGE_CHANNEL_TIME("BlueScr-10");
}

#if (ENABLE_SW_CH_FREEZE_SCREEN)

#define DEBUG_FREEZE_SCREEN(x)  //x

static BOOLEAN g_XC_Sys_abScreenFreeze[2]={0};
void msAPI_Scaler_SetFreezeScreen( BOOLEAN bEnable, U16 u16ScreenUnMuteTime, SCALER_WIN eWindow)
{
    //UNUSED(eWindow);

    if (bEnable )
    {
        if( g_XC_Sys_abScreenFreeze[eWindow] )
        {   // sws check
            DEBUG_FREEZE_SCREEN(printf("Enable FreezeScreen return\n"));
            return;
        }

        #if 0
        if ( EN_MPIC_SPLIT == stGenSetting.g_SysSetting.u8EngineSetting
          || EN_MPIC_DYNIMIAC == stGenSetting.g_SysSetting.u8EngineSetting)
        {
            stGenSetting.g_SysSetting.u8EngineSetting = EN_MPIC_OPTIMIZE;
            MApp_Picture_Setting_SetMWE(stGenSetting.g_SysSetting.u8EngineSetting);
            MApp_SaveSysSetting();
        }
        #endif

        DEBUG_FREEZE_SCREEN(printf("Enable FreezeScreen(%u)\n", msAPI_Timer_GetTime0()));

        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_CHANNEL, ENABLE, u16ScreenUnMuteTime, eWindow);

        //stSystemInfo[eWindow].u8PanelPowerStatus |= PANEL_POWER_FREEZESCREEN;
        g_XC_Sys_abScreenFreeze[eWindow] = TRUE;
    }
    else
    {
        //if( stSystemInfo[eWindow].u8PanelPowerStatus & PANEL_POWER_FREEZESCREEN )
        if( g_XC_Sys_abScreenFreeze[eWindow] )
        {
            DEBUG_FREEZE_SCREEN(printf("Disable FreezeScreen(%u)\n", msAPI_Timer_GetTime0()));

            //MsOS_DelayTask(50); // dealy to avoid garbage screen
            if(u16ScreenUnMuteTime != 0)
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, u16ScreenUnMuteTime, eWindow);

            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_CHANNEL, DISABLE, 0, eWindow);

            //stSystemInfo[eWindow].u8PanelPowerStatus &= ~PANEL_POWER_FREEZESCREEN;
            g_XC_Sys_abScreenFreeze[eWindow] = FALSE;
        }
        else
        {
            DEBUG_FREEZE_SCREEN(printf("Disable FreezeScreen return\n"));
        }
    }
}
#endif

/*E_SCREEN_MUTE_STATUS*/U32 msAPI_Scaler_GetScreenMute( SCALER_WIN eWindow)
{
    return s_eScreenMuteStatus[eWindow];
}

void msAPI_Scaler_PrintMuteClient(SCALER_WIN eWindow)
{
    U32 u32MuteStatus = s_eScreenMuteStatus[eWindow];

    if( u32MuteStatus )
    {
        printf("VideoMute[%u]=0x%X", eWindow, u32MuteStatus);

        if( u32MuteStatus&E_SCREEN_MUTE_TEMPORARY )
            printf(" Temp,");
        if( u32MuteStatus&E_SCREEN_MUTE_RATING )
            printf(" Rating,");
        if( u32MuteStatus&E_SCREEN_MUTE_FREERUN )
            printf(" Freerun,");
        if( u32MuteStatus&E_SCREEN_MUTE_CHANNEL )
            printf(" Channel,");
        if( u32MuteStatus&E_SCREEN_MUTE_BLOCK )
            printf(" Block,");
        if( u32MuteStatus&E_SCREEN_MUTE_MHEG5 )
            printf(" MHEG5,");
        if( u32MuteStatus&E_SCREEN_MUTE_HDMI_AVMUTE )
            printf(" HDMI_AVMute,");
        if( u32MuteStatus&E_SCREEN_MUTE_BY_UI )
            printf(" UI,");
        if( u32MuteStatus&E_SCREEN_MUTE_BY_SCALER_FPLL )
            printf(" SCALER_FPLL,");

    #if( ENABLE_ATSC )
        if( u32MuteStatus&E_SCREEN_MUTE_BY_VCHIP )
            printf(" VChip,");
    #endif

    #if( ENABLE_EWS)
        if( u32MuteStatus&E_SCREEN_MUTE_BY_EWS)
            printf(" EWS,");
    #endif

        if( u32MuteStatus&E_SCREEN_MUTE_BY_VDEC)
            printf(" VDEC,");

    #if 0// ( ENABLE_AUDIO_ONLY_CUSTOMERMODE )
        if( u32MuteStatus&E_SCREEN_MUTE_BY_AUDIO_ONLY)
            printf(" AUDIO_ONLY,");
    #endif

        if( u32MuteStatus&E_SCREEN_MUTE_BY_MM)
            printf(" MM,");

    #if 0//( ENABLE_FM_RADIO )
        if( u32MuteStatus&E_SCREEN_MUTE_BY_FMRADIO)
            printf(" FMRADIO,");
    #endif

    #if(ENABLE_PVR)
        if( u32MuteStatus&E_SCREEN_MUTE_BY_PVR)
            printf(" PVR,");
    #endif

        if( u32MuteStatus&E_SCREEN_MUTE_BY_SET_WIN)
            printf(" SET_WIN,");

        printf("\n");
    }
}

#if ENABLE_DEBUG_SCREEN_MUTE
    #define DEBUG_SCREEN_MUTE(x)    x
#else
    #define DEBUG_SCREEN_MUTE(x)    //x
#endif

void msAPI_Scaler_SetScreenMute2(E_SCREEN_MUTE_STATUS eScreenMute, BOOLEAN bMuteEnable, U16 u161ms , SCALER_WIN eWindow)
{
    //LOG_CHANGE_CHANNEL_TIME("ScrMut-1");

    DEBUG_SCREEN_MUTE(printf("msAPI_Scaler_SetScreenMute2(eScreenMute=%X,En=%u, Time=%u) at %u\n", eScreenMute, bMuteEnable, u161ms, MsOS_GetSystemTime()););

    if( bMuteEnable )
    {
        if ( (eScreenMute == E_SCREEN_MUTE_TEMPORARY)
      #if (ENABLE_SW_CH_FREEZE_SCREEN)
          || (eScreenMute == E_SCREEN_MUTE_CHANNEL)
      #endif //(ENABLE_SW_CH_FREEZE_SCREEN)
           )
        {
            MSG(printf("E_SCREEN_MUTE_TEMPORARY Before %u\n", (U16)u161ms));
            u161ms = MAX( u161ms, msAPI_Timer_GetDownTimer0() );
            MSG(printf("E_SCREEN_MUTE_TEMPORARY After %u\n", (U16)u161ms));
            msAPI_Timer_SetDownTimer0(u161ms);
        }

        if((s_eScreenMuteStatus[eWindow]& eScreenMute) && bMuteEnable)
        {
            MSG(printf("msAPI_Scaler_SetScreenMute(%x, %d) return, orig status %x\n",
                eScreenMute, bMuteEnable, s_eScreenMuteStatus[eWindow]);)
            return;
        }

        s_eScreenMuteStatus[eWindow] |= eScreenMute;

    #if (ENABLE_SW_CH_FREEZE_SCREEN)
        if(IsATVInUse())//&&eScreenMute == E_SCREEN_MUTE_CHANNEL)
        {
            if(stGenSetting.stTvSetting.u8SwitchMode == ATV_SWITCH_CH_FREEZE_SCREEN && eScreenMute == E_SCREEN_MUTE_CHANNEL)
            {
                MApi_XC_FreezeImg(ENABLE, eWindow);
            }
            else
            {
            #if ENABLE_3D_PROCESS
                if(MApi_XC_Get_3D_Input_Mode(eWindow) != E_XC_3D_INPUT_MODE_NONE)
                {
                    MApi_XC_GenerateBlackVideoForBothWin(ENABLE);
                }
                else
            #endif
                    MApi_XC_GenerateBlackVideo( ENABLE, eWindow );

                if(s_eScreenMuteStatus[eWindow] & E_SCREEN_MUTE_CHANNEL)
                {
                    MApi_XC_FreezeImg(DISABLE, eWindow);
                }
            }
        }
        else
    #endif //(ENABLE_SW_CH_FREEZE_SCREEN)
        {
        #if (FORCE_ALL_OUTPUT_THROUGH_VE == DISABLE)
            if(IsDTVInUse() || IsStorageInUse())
            {
                //if CVBS is on, turn it off to avoid VE PAL/NTSC switch garbage
            #if FIXED_SCART_OUT_GARBAGE_SWITCH_AR
                if(g_u8switchAspectFlag == 0)
                {
                    msAPI_Scaler_SetCVBSMute(ENABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS1);
                  #if (INPUT_SCART_VIDEO_COUNT >= 2)
                    msAPI_Scaler_SetCVBSMute(ENABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS2);
                  #endif
                    msAPI_VE_SetBlackScreen(ENABLE);
                }
            #else
                msAPI_Scaler_SetCVBSMute(ENABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS1);
              #if (INPUT_SCART_VIDEO_COUNT >= 2)
                msAPI_Scaler_SetCVBSMute(ENABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS2);
              #endif
                msAPI_VE_SetBlackScreen(ENABLE);
            #endif
            }
        #endif // FORCE_ALL_OUTPUT_THROUGH_VE

            if( MApi_XC_IsBlackVideoEnable(eWindow) == FALSE )
            {
            #if ENABLE_3D_PROCESS
                if(MApi_XC_Get_3D_Input_Mode(eWindow) != E_XC_3D_INPUT_MODE_NONE)
                {
                    MApi_XC_GenerateBlackVideoForBothWin(ENABLE);
                }
                else
            #endif
                {
                    MApi_XC_GenerateBlackVideo( ENABLE, eWindow );
                }
                MSG(printf("MApi_XC_GenerateBlackVideo Enable %bu\n", (U8)eScreenMute));
            }
        }
    }
    else // Disable Mute
    {
        /*E_SCREEN_MUTE_STATUS*/U32 eScreenMuteTmp;


        eScreenMuteTmp = s_eScreenMuteStatus[eWindow];
        s_eScreenMuteStatus[eWindow] = (E_SCREEN_MUTE_STATUS)(s_eScreenMuteStatus[eWindow] & ~(eScreenMute));

        if (eScreenMuteTmp != s_eScreenMuteStatus[eWindow])
        {
            if( s_eScreenMuteStatus[eWindow] == E_SCREEN_MUTE_INIT  )
            {
            #if (ENABLE_SW_CH_FREEZE_SCREEN)
                if(IsATVInUse())
                {
                    if(stGenSetting.stTvSetting.u8SwitchMode == ATV_SWITCH_CH_FREEZE_SCREEN && eScreenMute == E_SCREEN_MUTE_CHANNEL)
                    {
                        if(!MApi_SC_IsForceFreerun())
                        {
                            MApi_XC_WaitFPLLDone();//Wait FPLL done to reload MCNR
                        }
                        MApi_XC_FreezeImg(DISABLE, eWindow);
                    }
                    else
                    {
                        if(MApi_XC_WaitFPLLDone() || MApi_SC_IsForceFreerun())
                        {
                        }
                        else
                        {
                            // actually, we need a state machine to maintain this
                            // for URSA, if scaler output unstable, set URSA to freerun
                            // if scaler output stable (frame locked or freerun), set URSA to lock
                        }
                    #if ENABLE_3D_PROCESS
                        if(MApi_XC_Get_3D_Input_Mode(eWindow) != E_XC_3D_INPUT_MODE_NONE)
                        {
                            ////printf("DDDDD Delay %u\n", u16PQDelyaTime);
                            MsOS_DelayTask(u16PQDelyaTime);
                            MApi_XC_GenerateBlackVideoForBothWin(DISABLE);
                        }
                        else
                    #endif
                        {
                            //printf("DDDDD Delay %u\n", u161ms);
                        //    MsOS_DelayTask(u16PQDelyaTime);
                            MApi_XC_GenerateBlackVideo( DISABLE, eWindow );
                        }
                    }
                }
                else
            #endif //(ENABLE_SW_CH_FREEZE_SCREEN)
                {

                #if ENABLE_3D_PROCESS
                    if(MApi_XC_Get_3D_Input_Mode(eWindow) != E_XC_3D_INPUT_MODE_NONE)
                    {
                        MApi_XC_GenerateBlackVideoForBothWin(DISABLE);
                    }
                    else
                #endif
                    {
                        TIMER_SET_DELAY_ID_START(E_DELAY_ID_DRV_XC_SET_BLACK_WIN);
                        MApi_XC_GenerateBlackVideo( DISABLE, eWindow );
                        TIMER_SET_DELAY_ID_END();
                    }

                    if(IsDTVInUse() || IsStorageInUse())
                    {
                    #if FIXED_SCART_OUT_GARBAGE_SWITCH_AR
                        if(g_u8switchAspectFlag == 0)
                        {
                            msAPI_VE_SetBlackScreen(DISABLE);
                            //if CVBS is on, turn it off to avoid VE PAL/NTSC switch garbage
                            msAPI_Scaler_SetCVBSMute(DISABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS1);
                          #if (INPUT_SCART_VIDEO_COUNT >= 2)
                            msAPI_Scaler_SetCVBSMute(DISABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS2);
                          #endif
                        }
                    #else
                      #if(ENABLE_VE)
                        msAPI_VE_SetBlackScreen(DISABLE);
                      #endif
                        //if CVBS is on, turn it off to avoid VE PAL/NTSC switch garbage
                        msAPI_Scaler_SetCVBSMute(DISABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS1);
                      #if (INPUT_SCART_VIDEO_COUNT >= 2)
                        msAPI_Scaler_SetCVBSMute(DISABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS2);
                      #endif
                    #endif
                    }

                  #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME )
                    if (gbBootTimeFinish == FALSE)
                    {
                    #if ( ENABLE_AUTOTEST || ENABLE_BOOTTIME )
                      #if (ENABLE_BOOTTIME==DISABLE)
                        if (g_bAutobuildDebug == TRUE)
                      #endif
                        {
                            gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                            printf("[TIME] video show up = %ld\n", gU32TmpTime);
                        }
                    #endif
                        PRINT_AUTOTEST_CHECKPT_TIME("unmute video");
                        gbBootTimeFinish = TRUE;
                    }
                  #endif

                #if( CHAKRA3_AUTO_TEST )
                    if( g_AT_bPowerOnFinished == FALSE )
                    {
                        MApp_AT_SendEvent( E_AT_EVENT_BOOT_TIME_END, (void*)MsOS_GetSystemTime() );
                        g_AT_bPowerOnFinished = TRUE;
                    }
                    if( g_AT_en8ChangeChannelState == E_AUTO_TEST_CHANGE_CHANNEL_START )
                    {
                        MApp_AT_SendEvent( E_AT_EVENT_CHANGE_CHANNEL_TIME_END, (void*)MsOS_GetSystemTime() );
                        g_AT_en8ChangeChannelState = E_AUTO_TEST_CHANGE_CHANNEL_END;
                    }
                    if (g_AT_bChangeSource)
                    {
                        MApp_AT_SendEvent( E_AT_EVENT_CHANGE_SOURCE_UNMUTE, (void*)msAPI_Timer_GetTime0());
                    }
                #endif

                  #if ( ENABLE_CHCHANGETIME )
                    if (gbKeyPress == TRUE)
                    {
                        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime);
                        printf(" [ch change time]video show up = %ld \n", gU32TmpTime);
                        gbKeyPress = FALSE;
                    }
                  #endif

                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_1_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);


                    // Log time for ChangeChannel
                    LOG_CHANGE_CHANNEL_TIME("UnMute Video");
                #if (ENABLE_TIME_LOG)
                    printf("Unmute Video at %u, %u\n", g_Debug_u32Time_ChangeChannel, MsOS_GetSystemTime());
                #endif

                #if(ENABLE_DEBUG_BOOT_TIME)
                    {
                    #if( ENABLE_LOG_FILE_IN_MEM )
                        Debug_Log_PrintAll(LOG_MEM_GROUP_BOOT);
                        Debug_Log_Reset(LOG_MEM_GROUP_BOOT);
                    #endif
                    }
                #endif

                #if(DEBUG_CHG_SRC_TIME)
                    if( g_Debug_bChangeSrc )
                    {
                        //printf("ChgSrc use %u, %u \n", g_Debug_u32Time_ChangeSrc, MsOS_GetSystemTime() );
                        msDebug_PrintChgSrcTime("ChgSrc End");
                        g_Debug_bChangeSrc = 0;

                    #if( ENABLE_LOG_FILE_IN_MEM )
                        Debug_Log_PrintAll(LOG_MEM_GROUP_CHG_SRC);
                        Debug_Log_Reset(LOG_MEM_GROUP_CHG_SRC);
                    #endif
                    }
                #endif

                    //CPU_PAUSE();
                }
            }
        #if (ENABLE_SW_CH_FREEZE_SCREEN)
            else  if(eScreenMute == E_SCREEN_MUTE_CHANNEL && IsATVInUse())
            {
                MApi_XC_FreezeImg(DISABLE, eWindow);
            }
        #endif
        }
    }

    DEBUG_SCREEN_MUTE(printf(" => s_eScreenMuteStatus=0x%x\n", s_eScreenMuteStatus[eWindow]));

    //LOG_CHANGE_CHANNEL_TIME("ScrMut-10");
}

/******************************************************************************/
/// -This function will set output test pattern
/// @param enColorOfPattern \b IN: Color pattern
/// - @see EN_TEST_COLOR
/// @param enInputSourceType \b IN: Indicate what's the current input source
/// - @see INPUT_SOURCE_TYPE_t
/// @param enVideoScreen \b IN: Carry the aspect ratio info
/// - @see EN_ASPECT_RATIO_TYPE
/******************************************************************************/
void msAPI_Scaler_SetTestPattern(INPUT_SOURCE_TYPE_t enInputSourceType, EN_TEST_COLOR enColorOfPattern)
{
#if 1 //Disable it in generic MB
    XC_FREERUN_COLOR eColor;
    UNUSED(enInputSourceType);
    switch(enColorOfPattern)
    {
        case TEST_COLOR_WHITE:
            eColor=E_XC_FREE_RUN_COLOR_WHITE;
            break;
        case TEST_COLOR_RED:
            eColor=E_XC_FREE_RUN_COLOR_RED;
            break;
        case TEST_COLOR_GREEN:
            eColor=E_XC_FREE_RUN_COLOR_GREEN;
            break;
        case TEST_COLOR_BLUE:
            eColor=E_XC_FREE_RUN_COLOR_BLUE;
            break;
        case TEST_COLOR_BLACK:
            eColor=E_XC_FREE_RUN_COLOR_BLACK;
            break;
        default:
        case TEST_COLOR_OFF:
            eColor=E_XC_FREE_RUN_COLOR_BLACK;
            break;
    }
    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );
    MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    MApp_CheckBlockProgramme();             // Check channel block status in the case.
    if(enColorOfPattern == TEST_COLOR_OFF)
    {
        MApi_XC_SetFrameColor(astFreeRunColor[E_XC_FREE_RUN_COLOR_BLACK]);
        MApi_XC_EnableMainWindow(TRUE);
    }
    else
    {
        MApi_XC_SetFrameColor(astFreeRunColor[eColor]);
        MApi_XC_EnableMainWindow(FALSE);
    }
    if (MApp_IsSrcHasSignal(MAIN_WINDOW))
    {
#if(!BLOADER)
        MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
#endif
        msAPI_Scaler_SetBlueScreen( DISABLE, 0, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        if(enColorOfPattern == TEST_COLOR_OFF)
        {
            MsOS_DelayTask(200);
        }
        if(!bIsBlocked)                     // If channel is block then test pattern set OFF, shouldn't unmute screen in block channel.
        {
            MApi_XC_GenerateBlackVideo( DISABLE, MAIN_WINDOW );
        }
    }//fixed Mantis 0343788 atv black alway error
    else if((IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        &&(enColorOfPattern == TEST_COLOR_OFF))
    {
#if(!BLOADER)
        MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
#endif
        msAPI_Scaler_SetBlueScreen( DISABLE, 0, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        if(enColorOfPattern == TEST_COLOR_OFF)
        {
            MsOS_DelayTask(200);
        }
        if(!bIsBlocked)                     // If channel is block then test pattern set OFF, shouldn't unmute screen in block channel.
        {
            MApi_XC_GenerateBlackVideo( DISABLE, MAIN_WINDOW );
        }
    }

#else
    UNUSED(enInputSourceType);
    UNUSED(enColorOfPattern);
#endif //if 0
}

/******************************************************************************/
///-Set H position for PC mode
///@param u16Position \b IN
///- H position
/******************************************************************************/
void MApi_XC_Set_PC_HPosition( U16 u16HPosition , SCALER_WIN eWindow)
{
    MApi_XC_SetCaptureWindowHstart( u16HPosition  , eWindow);
}

/******************************************************************************/
///-Set H position for PC mode
///@param u16Position \b IN
///- H position
/******************************************************************************/
void MApi_XC_Set_PC_VPosition( U16 u16VPosition , SCALER_WIN eWindow )
{
    MApi_XC_SetCaptureWindowVstart(  u16VPosition , eWindow);
}

/******************************************************************************/
///-Set H position for Ypbpr mode
///@param u16PrePosition \b IN
///@param u16NewPosition \b IN
///- H position
/******************************************************************************/
// What this function for ??? Strange for using.
void MApi_XC_Set_Ypbpr_HPosition(U16 u16PrePosition, U16 u16NewPosition , SCALER_WIN eWindow)
{

    MS_WINDOW_TYPE cap_win;

    MApi_XC_GetCaptureWindow(&cap_win,eWindow );

    if(u16NewPosition > u16PrePosition)
    {
        MApi_XC_SetCaptureWindowHstart(cap_win.x - (u16NewPosition-u16PrePosition),eWindow);
    }
    else
    {
        MApi_XC_SetCaptureWindowHstart(cap_win.x + (u16PrePosition-u16NewPosition),eWindow);
    }
}

/******************************************************************************/
///-Set V position for Ypbpr mode
///@param u16PrePosition \b IN
///@param u16NewPosition \b IN
///- V position
/******************************************************************************/
// What this function for ??? Strange for using.
void MApi_XC_Set_Ypbpr_VPosition(U16 u16PrePosition, U16 u16NewPosition , SCALER_WIN eWindow)
{
    MS_WINDOW_TYPE cap_win;

    MApi_XC_GetCaptureWindow(&cap_win,eWindow );

    if(u16NewPosition > u16PrePosition)
    {
        MApi_XC_SetCaptureWindowVstart(cap_win.y + (u16NewPosition-u16PrePosition),eWindow);
    }
    else
    {
        MApi_XC_SetCaptureWindowVstart(cap_win.y -(u16PrePosition-u16NewPosition),eWindow);
    }
}

static BOOLEAN s_Hdmi_Hpd_bFirstTimeChangeSrcDone = FALSE;

/* We have consider the case of multiple input source  */
void msAPI_Scaler_SetSourceType(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow)
{
    //printf("msAPI_Scaler_SetSourceType(SrcType=%u,win=%u)\n", enInputSourceType, eWindow);
    //printf("SYS_INPUT_SOURCE_TYPE(eWindow)=%u\n", SYS_INPUT_SOURCE_TYPE(eWindow));

//    printf("\r\n INPUT_SOURCE_HDMI = %d", INPUT_SOURCE_HDMI);
    printf("\r\n enInputSourceType = %d \n", enInputSourceType);

    //TODO: need to move gpio settings before scaler LIB
  #if (INPUT_SCART_VIDEO_COUNT > 0)
    if ( IsSrcTypeScart(SYS_INPUT_SOURCE_TYPE(eWindow)) )
        SwitchRGBToSCART();
    else
  #endif
        SwitchRGBToDSUB();

    // Template of ADC set input source
    //MApi_XC_ADC_SetInputSource( _InputSource, _SourceCount);

    // set input port
    MApi_XC_SetInputSource( enInputSourceType, eWindow );

    // Reset DVI port
    if( IsSrcTypeHDMI(enInputSourceType)||IsSrcTypeDVI(enInputSourceType) )
    {
        // If chip is not support IMM switch, need reset DVI port
        if( (FALSE == MApi_XC_Sys_Is_SupportImmSwitch() )
#if( ENABLE_CEC )
            // 1. already reset in _MApi_XC_Sys_HDMI_Init 2. can not reset after hotplug pull high
            &&(MApp_Main_Is_PowerOnPreInitFinish() == TRUE)
#endif
            )
        {
            MApi_XC_Sys_ResetDVIPort(enInputSourceType);
        }
    }

    //MsOS_DelayTask(50);

#if (SUPPORT_EURO_HDTV)
    if(IsSrcTypeYPbPr(enInputSourceType))
    {
        MApi_XC_EnableEuroHdtvDetection(ENABLE, eWindow);
    }
    else
    {
        MApi_XC_EnableEuroHdtvDetection(DISABLE, eWindow);
    }
#endif

 #if (INPUT_HDMI_VIDEO_COUNT > 0)
    if( IsSrcTypeHDMI(enInputSourceType) )
    {
    #if(ENABLE_CEC)
        if( (s_Hdmi_Hpd_bFirstTimeChangeSrcDone == FALSE) // First time change source after power on
          &&(msAPI_CEC_Is_CecTurnOn())
        )
        {
            // Because all HPD already control to High when power on init,
            // So skip this time.
        }
        else
    #endif
        {
        #if ENABLE_EDID_SWITCH
            {
                MApi_XC_HDMI_EdidSwitch_ResetSM();
                switch( MApi_XC_Sys_Get_UserEdidSel() )
                {
                    default:
                    case E_USER_HDMI_EDID_1p4:
                        MApi_XC_Sys_Reload_Edid(enInputSourceType, XC_HDMI_EDID_1p4, FALSE);
                        break;

                    case E_USER_HDMI_EDID_2p0:
                        MApi_XC_Sys_Reload_Edid(enInputSourceType, XC_HDMI_EDID_2p0, FALSE);
                        break;

                    case E_USER_HDMI_EDID_AUTO:
                        MApi_XC_Sys_Reload_Edid(enInputSourceType, XC_HDMI_EDID_2p0, FALSE);
                        break;
                }
            }
        #endif

        #if(!SUPPORT_HDMI_IMM_SWITCH)
            //if( MApp_Main_Is_PowerOnInitFinish() )
          #if( ENABLE_HDMI_FIRST_HDP_BEFORE_SRC_CHANGE )
            if( s_Hdmi_Hpd_bFirstTimeChangeSrcDone )
          #endif
            {
                MApi_XC_HPD_Do_EnterHDMI(enInputSourceType);
            }
        #endif
        }
    }
#endif // #if (!defined(MSTAR_IMMESWITCH))

    s_Hdmi_Hpd_bFirstTimeChangeSrcDone = TRUE;
}

//#define DEBUG_CVBS_OUT_MUTE(x)  x
#define DEBUG_CVBS_OUT_MUTE(x)  //do { msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW); x; msDebug_ANSI_AllAttrOffText(); } while(0)

void msAPI_Scaler_SetCVBSMute( BOOLEAN bEn , E_VE_MUTE_STATUS eMuteStatus , INPUT_SOURCE_TYPE_t enInputPortType, E_DEST_TYPE OutputPortType) //SCR 071123
{
    MS_U8 u8PortID = 0;
    BOOL bIsDigitalSource = FALSE;
    INPUT_SOURCE_TYPE_t eCvbsOut_Src = INPUT_SOURCE_NONE;
    static INPUT_SOURCE_TYPE_t eLast_CvbsOut_Src[2] = {INPUT_SOURCE_NONE,INPUT_SOURCE_NONE};

    if( OutputPortType == OUTPUT_CVBS1 )
    {
        u8PortID = 0;
        eCvbsOut_Src = MApp_InputSource_Get_CVBSOut_Src(0, enInputPortType);
    }
    else if( OutputPortType == OUTPUT_CVBS2 )
    {
        u8PortID = 1;
        eCvbsOut_Src = MApp_InputSource_Get_CVBSOut_Src(1, enInputPortType);
    }
    else
    {
        printf("\nError: Unknown Output PortType(%u) for VEMute, function return. !!!!!!\n", OutputPortType);
        ASSERT(0);
        return;
    }

    DEBUG_CVBS_OUT_MUTE(printf("msAPI_Scaler_SetCVBSMute(bEn=%u, MuteState=%u, Input=%u, Output=%u) \n", bEn, eMuteStatus, enInputPortType, OutputPortType));
    DEBUG_CVBS_OUT_MUTE(printf("s_eVEMuteStatus[%u] = %u \n",  u8PortID, s_eVEMuteStatus[u8PortID]));
    DEBUG_CVBS_OUT_MUTE(printf("eLast_CvbsOut_Src[u8PortID]=%u, eCvbsOut_Src=%u\n", eLast_CvbsOut_Src[u8PortID],eCvbsOut_Src); );

    if( eCvbsOut_Src == INPUT_SOURCE_NONE )
    {
        bEn = TRUE; // Must enable mute
        eMuteStatus = E_VE_MUTE_GEN;
    }


  #if ((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE))
    //Skip off for this case to show out the "NO Signal" symbol
    //fake source to DTV to choose the VIF_DAC data path
    if(bEn == TRUE)
    {
         return;
    }
    enInputPortType = INPUT_SOURCE_DTV;
  #endif

    //DEBUG_CVBS_OUT_MUTE(printf("CVBS Mute: bEnable=%u, MuteState=%u, Input=%u, Output=%u, s_eVEMuteStatus[%u]=%u\n", bEn, eMuteStatus, enInputPortType, OutputPortType, u8PortID, s_eVEMuteStatus[u8PortID]));

    if( IsSrcTypeStorage(enInputPortType) )
    {
        enInputPortType = INPUT_SOURCE_DTV;
    }

    // If Internal VIF used, input of CVBS-out is digital. Must inform driver this for setting.
    if( IsSrcTypeDTV(enInputPortType)
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF || FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
     || (IsSrcTypeATV(enInputPortType) || (MApp_InputSource_GetVifWorkingStatus() == E_VIF_ON_ATV_CVBSOUT))
#endif
    )
    {
        bIsDigitalSource = TRUE;
    }
    DEBUG_CVBS_OUT_MUTE(printf("bIsDigitalSource=%u\n", bIsDigitalSource); );


    //Skip to turn on/off an already on/off CVBS port
    if( s_eVEMuteStatus[u8PortID] == E_VE_MUTE_INVALID ) // First time call this function
    {
        if( bEn )
        {
            s_eVEMuteStatus[u8PortID] = (E_VE_MUTE_STATUS)0;
        }
        else
        {
            s_eVEMuteStatus[u8PortID] = eMuteStatus;
        }
    }
    /*else if( ((s_eVEMuteStatus[u8PortID] & eMuteStatus) && bEn) )
    {
        DEBUG_CVBS_OUT_MUTE( printf("msAPI_Scaler_SetCVBS Mute(%x, %d) return, orig status %x\n",
            bEn, eMuteStatus, s_eVEMuteStatus[u8PortID]); );
        return;
    }*/

    if( bEn ) // Enable mute => Disable cvbsout
    {
        if( (s_eVEMuteStatus[u8PortID] & eMuteStatus) ) // Already mute
        {
            // Do nothing
        }
        else
        {
            DEBUG_CVBS_OUT_MUTE(printf("Set CVBSOut off\n"); );
            // If Internal VIF used, input of CVBS-out is digital. Must inform driver this for setting.
            MApi_XC_ADC_SetCVBSOut(DISABLE, OutputPortType, enInputPortType, bIsDigitalSource );
        }

        s_eVEMuteStatus[u8PortID] |= eMuteStatus;
        eLast_CvbsOut_Src[u8PortID] = INPUT_SOURCE_NONE;

#if Audio_ScartOut1_Mute_Control_by_APP
        MW_AUD_SetSoundMute(SOUND_MUTE_SCART, E_MUTE_ON);
#endif
        DEBUG_CVBS_OUT_MUTE(printf("s_eVEMuteStatus[u8PortID]=0x%X\n", s_eVEMuteStatus[u8PortID]););
        DEBUG_CVBS_OUT_MUTE(printf(" => CVBSOut Mute\n"); );
    }
    else // Disable mute => Enable cvbsout
    {
        // Clear client bit
        s_eVEMuteStatus[u8PortID] = (E_VE_MUTE_STATUS)((U8)s_eVEMuteStatus[u8PortID] & ~((U8)eMuteStatus));
        DEBUG_CVBS_OUT_MUTE(printf("s_eVEMuteStatus[u8PortID]=0x%X\n", s_eVEMuteStatus[u8PortID]););

        if( s_eVEMuteStatus[u8PortID] != E_VE_MUTE_INIT )
        {
            DEBUG_CVBS_OUT_MUTE(printf("Still mute\n"););
            return;
        }

        if( eLast_CvbsOut_Src[u8PortID] == eCvbsOut_Src )
        {
            DEBUG_CVBS_OUT_MUTE(printf("CvbsOut src not change!\n"););
            // Do nothing
        }
        else
        {
            DEBUG_CVBS_OUT_MUTE(printf("Set CVBSOut On\n"); );

            // If Internal VIF used, input of CVBS-out is digital. Must inform driver this for setting.
            //MApi_XC_ADC_SetCVBSOut(ENABLE, OutputPortType, enInputPortType, bIsDigitalSource );
            MApi_XC_ADC_SetCVBSOut(ENABLE, OutputPortType, eCvbsOut_Src, bIsDigitalSource );

        #if((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN )||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON))
            // CVBSOut is ATV(VIF), but main src is not ATV
            if( (eCvbsOut_Src==INPUT_SOURCE_TV)&&(MApp_InputSource_GetVifWorkingStatus() == E_VIF_ON_ATV_CVBSOUT) ) // CVBSOut is ATV(VIF)
            {
                if( IsSrcTypeAV(enInputPortType)
                  ||IsSrcTypeSV(enInputPortType)
                  ||IsSrcTypeScart(enInputPortType)
                  )
                {
                    // Patch xc driver: turn off "reg_mux_y_en" in MApi_XC_ADC_SetCVBSOut
                    MDrv_WriteByteMask(0x102505, BIT0, BIT0);
                }
            }
        #endif

#if Audio_ScartOut1_Mute_Control_by_APP
            MW_AUD_SetSoundMute(SOUND_MUTE_SCART, E_MUTE_OFF);
#endif
        }

        eLast_CvbsOut_Src[u8PortID] = eCvbsOut_Src;
        DEBUG_CVBS_OUT_MUTE(printf(" => CVBSOut UnMute\n"); );
    }

}

#if (ENABLE_VE)

//#define DEBUG_VE(x)     x
#define DEBUG_VE(x) //do { msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_GREEN); x; msDebug_ANSI_AllAttrOffText(); } while(0)

/******************************************************************************/
///-Disable VE and VE IN/OUT/DAC clock
/******************************************************************************/
void msAPI_VE_Exit(void)
{
    DEBUG_VE(printf("msAPI_VE_Exit()\n"););

    if(!MDrv_VE_GetInfo()->stCaps.bVESupported)
    {
        return;
    }
    MDrv_VE_Exit();
}

void msAPI_Scaler_SetAFDToVEWSS(BOOLEAN bEn, U8 u8AFD, U8 u8SrcARC)
{
    U8 u8WSSData;
    MS_U16 u16Wss;

    if(!MDrv_VE_GetInfo()->stCaps.bVESupported)
    {
        return;
    }

    //printf("\033[1;32m-----SetAFDToVEWSS=%bd, AFD=%bu, SCRARC=%bu\033[m\n", bEn, u8AFD, u8SrcARC);
    if(bEn)
    {
        switch(u8AFD)
        {
        case E_MVD_AFD_FULL_FRAME:
            u8WSSData = (u8SrcARC == MVD_ASP_4TO3) ? EN_WSS_4x3_FULL : EN_WSS_16x9_ANAMORPHIC;
            break;
        case E_MVD_AFD_CENTRE_4x3:
            u8WSSData = EN_WSS_4x3_FULL;
            break;
        case E_MVD_AFD_CENTRE_16X9:
            u8WSSData = (u8SrcARC == MVD_ASP_4TO3) ? EN_WSS_16x9_LETTERBOX_CENTER : EN_WSS_16x9_ANAMORPHIC;
            break;
        case E_MVD_AFD_CENTRE_14X9:
            u8WSSData = (u8SrcARC == MVD_ASP_4TO3) ? EN_WSS_14x9_LETTERBOX_CENTER : 0x07;
            break;
        case E_MVD_AFD_CENTRE_4X3_14X9:
            u8WSSData = (u8SrcARC == MVD_ASP_4TO3) ? EN_WSS_14x9_LETTERBOX_CENTER : 0x0E;
            break;
        case E_MVD_AFD_CENTRE_16X9_14X9:
            u8WSSData = (u8SrcARC == MVD_ASP_4TO3) ? EN_WSS_16x9_LETTERBOX_CENTER : EN_WSS_16x9_ANAMORPHIC;
            break;
        case E_MVD_AFD_CENTRE_16X9_4X3:
            u8WSSData = (u8SrcARC == MVD_ASP_4TO3) ? EN_WSS_16x9_LETTERBOX_CENTER : EN_WSS_16x9_ANAMORPHIC;
            break;
        case E_MVD_AFD_BOX_16X9_TOP:
            u8WSSData = EN_WSS_16x9_LETTERBOX_TOP;
            break;
        case E_MVD_AFD_BOX_14X9_TOP:
            u8WSSData = EN_WSS_14x9_LETTERBOX_TOP;
            break;
        case E_MVD_AFD_BOX_16X9:
            u8WSSData = EN_WSS_ABOVE16x9_LETTERBOX_CENTER;
            break;
        default:
            u8WSSData = (u8SrcARC == MVD_ASP_4TO3) ? EN_WSS_4x3_FULL :  EN_WSS_16x9_ANAMORPHIC;
            break;
        }
        u16Wss = MDrv_VE_GetWSSData();
        u16Wss &= 0xFFF0;
        u16Wss |= u8WSSData;
        //MDrv_VE_SetWSSData(ENABLE, (MS_U16)u8WSSData);
        MDrv_VE_SetWSSData(ENABLE, u16Wss);
    }
    else
    {
        MDrv_VE_SetWSSData(DISABLE, 0x00);
    }
}
/******************************************************************************/
///-Force VE output a black screen
/******************************************************************************/
MS_BOOL msAPI_Scaler_ForceVE_BlackOutPut(MS_BOOL bEnable, INPUT_SOURCE_TYPE_t src, E_DEST_TYPE enOutputType, MS_VE_VIDEOSYS VideoSystem)
{
    DEBUG_VE(printf("msAPI_Scaler_SetVE_Cus: bEnable=%u, src=%u, enOutputType=%u, VideoSystem=%u\n", bEnable, src, enOutputType, VideoSystem));
    s_bForceVEOutputenable = bEnable;
    MDrv_VE_Set_TestPattern(bEnable);
    if ( src == INPUT_SOURCE_DTV || src == INPUT_SOURCE_STORAGE)
    {
        s_eVideoSystem = VideoSystem;
        if(bEnable)
        {
            if(s_eVideoSystem >= MS_VE_VIDEOSYS_NUM)
            {
                return FALSE;
            }
            msAPI_Scaler_SetVE(src, enOutputType);
            msAPI_VE_SetBlackScreen(ENABLE);
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void msAPI_Scaler_SetVE(INPUT_SOURCE_TYPE_t src,E_DEST_TYPE enOutputType)
{
    MS_Switch_VE_Src_Info SwitchInputSrc;
    MS_Switch_VE_Dest_Info SwitchOutputDest;
    MS_VE_Output_Ctrl OutputCtrl;
    MS_VE_Set_Mode_Type SetModeType;
    MVOP_Timing stMVOPTiming;
    XC_ApiStatus stXCStatus;
    MS_U8 PortID;
    MS_VE_VIDEOSYS VideoSystem;


    DEBUG_VE(printf("msAPI_Scaler_SetVE(src=%u, enOutputType=%u)\n", src, enOutputType););

    if(!MDrv_VE_GetInfo()->stCaps.bVESupported)
    {
        return;
    }
    if(enOutputType == OUTPUT_CVBS1)
    {
        PortID = 0;
    }
    else if(enOutputType == OUTPUT_CVBS2)
    {
        PortID = 1;
    }
    else
    {
        MS_DEBUG_MSG(printf(" !!!!!! Unknown Output port for VEMute, function return. !!!!!!"));
        ASSERT(0);
        return;
    }

    //MSG(printf("SetVE: src=%u, Output=%u\n", src, enOutputType));

    if(IsSrcTypeStorage(src))
    {
        src = INPUT_SOURCE_DTV;
    }

#if ((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE))
    //Black screen for green screen and garbage
    msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN, src, enOutputType);
    msAPI_VE_SetBlackScreen(ENABLE);
#endif //#if((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE))
    #if((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE))
    // fake source to DTV to choose the VIF_DAC data path, this is not a good solution, we may change this later
    src = INPUT_SOURCE_DTV;
    #endif

    if( MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
    {
        printf("\nError: MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
        return;
    }

    // bypass signal of CVBS.
    //if( IsSrcTypeDTV(enInputSourceType)  )  //||IsSrcTypeDigitalVD(enInputSourceType))
    //{
        //if(IsSrcTypeDigitalVD(enInputSourceType))
        //    MDrv_VE_set_output_video_std(MS_VE_PAL);
        //else
    if(s_bForceVEOutputenable)
    {
        VideoSystem = s_eVideoSystem;
    }
    else if((gstVidStatus.u32FrameRate > 27000 &&gstVidStatus.u8Interlace)
     ||(gstVidStatus.u32FrameRate > 55000)
     ||(gstVidStatus.u32FrameRate == 0)
     )
    {
        //If no input, treat as free run 60 hz
        VideoSystem = MS_VE_NTSC;
    }
    else
    {
        VideoSystem = MS_VE_PAL;
    }
    MDrv_VE_SetOutputVideoStd(VideoSystem);

    #if ENABLE_OP2_TO_VE
    MS_U16 OutputCapability;

    // Get Capability of scaler
    MApi_XC_SupportSourceToVE(&OutputCapability);

    if ( OutputCapability & E_XC_OP2 ) // Scaler can output data from OP2 to VE
    {
        SwitchInputSrc.InputSrcType = MS_VE_SRC_SCALER; // Set source of VE to scaler.
        MApi_XC_SetOutputCapture(ENABLE,E_XC_OP2);      // Enable op2 to ve path
    }
    else
    {
        SwitchInputSrc.InputSrcType = MS_VE_SRC_DTV;
        MApi_XC_SetOutputCapture(ENABLE,E_XC_IP);
    }
    #else
    SwitchInputSrc.InputSrcType = MS_VE_SRC_DTV;
    #endif

    MDrv_VE_SwitchInputSource(&SwitchInputSrc);

    SwitchOutputDest.OutputDstType = MS_VE_DEST_CVBS;
    MDrv_VE_SwitchOuputDest(&SwitchOutputDest);

    msAPI_Scaler_SetAFDToVEWSS(ENABLE, gstVidStatus.u8AFD, gstVidStatus.u8AspectRate);


    // set mode
    memset(&SetModeType, 0, sizeof(MS_VE_Set_Mode_Type));
    if(s_bForceVEOutputenable)
    {
        MS_U16 Hsize, Vsize;
        VideoSystem = s_eVideoSystem;
        Hsize = (SwitchInputSrc.InputSrcType == MS_VE_SRC_DTV && SetModeType.bHDuplicate) ? 704 : 720;
        Vsize = (VideoSystem <= MS_VE_NTSC_J) ? 480 : 576;
        SetModeType.bHDuplicate      = FALSE;
        SetModeType.u16H_CapSize     = Hsize;
        SetModeType.u16V_CapSize     = Vsize;
        SetModeType.u16H_CapStart    = Hsize/10;
        SetModeType.u16V_CapStart    = Vsize/10;
        SetModeType.u16H_SC_CapSize  = Hsize;
        SetModeType.u16V_SC_CapSize  = Vsize;
        SetModeType.u16H_SC_CapStart = Hsize/10;
        SetModeType.u16V_SC_CapStart = Vsize/10;
        SetModeType.u16InputVFreq     = (VideoSystem <= MS_VE_PAL_M) ? 600 : 500;
        SetModeType.bSrcInterlace     = FALSE;
    }
    else if ( SwitchInputSrc.InputSrcType != MS_VE_SRC_SCALER)
    {
        MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
        SetModeType.bHDuplicate      = stMVOPTiming.bHDuplicate;
        SetModeType.u16H_CapSize     = stMVOPTiming.u16Width;
        SetModeType.u16V_CapSize     = stMVOPTiming.u16Height;
        SetModeType.u16H_CapStart    = MDrv_MVOP_GetHStart();
        SetModeType.u16V_CapStart    = MDrv_MVOP_GetVStart();
        SetModeType.u16H_SC_CapSize  = stXCStatus.stCapWin.width;
        SetModeType.u16V_SC_CapSize  = stXCStatus.stCapWin.height;
        SetModeType.u16H_SC_CapStart = stXCStatus.stCapWin.x;
        SetModeType.u16V_SC_CapStart = stXCStatus.stCapWin.y;


        if ( stMVOPTiming.bInterlace )
        {
            SetModeType.u16InputVFreq = (U16)((stMVOPTiming.u16ExpFrameRate * 2 + 50) / 100);
            SetModeType.bSrcInterlace    = TRUE;
        }
        else
        {
            SetModeType.u16InputVFreq = (U16)((stMVOPTiming.u16ExpFrameRate + 50) / 100);
            SetModeType.bSrcInterlace    = FALSE;
        }

    }
    else
    {
        SetModeType.bHDuplicate      = FALSE;
        SetModeType.u16H_CapSize     = g_IPanel.Width();
        SetModeType.u16V_CapSize     = g_IPanel.Height();
        SetModeType.u16H_CapStart    = g_IPanel.HStart();
        SetModeType.u16V_CapStart    = g_IPanel.VStart();
        SetModeType.u16H_SC_CapSize  = g_IPanel.Width();
        SetModeType.u16V_SC_CapSize  = g_IPanel.Height();
        SetModeType.u16H_SC_CapStart = g_IPanel.HStart();
        SetModeType.u16V_SC_CapStart = g_IPanel.VStart();
        SetModeType.u16InputVFreq     = MApi_XC_GetOutputVFreqX100()/10;
        SetModeType.bSrcInterlace     = FALSE;
    }
    //MDrv_VE_SetBlackScreen(ENABLE);
    MDrv_VE_SetMode(&SetModeType);

    // set output control
    OutputCtrl.bEnable = TRUE;
    //OutputCtrl.InputType = enInputSourceType;  // What does this do here?
    OutputCtrl.OutputType = MS_VE_OUT_TVENCODER;
    MDrv_VE_SetOutputCtrl(&OutputCtrl);
#if((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE))
    //delay 300 ms to wait VE output signal stable after VE reset---it will be refined later
    msAPI_Timer_Delayms(300);
    msAPI_VE_SetBlackScreen(DISABLE);
#endif //#if((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE))

    //UnMute CVBS for setve---Doing this is to just keep the logic as it was
    if( E_VE_MUTE_INIT == s_eVEMuteStatus[PortID] )
    {
        s_eVEMuteStatus[PortID] = E_VE_MUTE_GEN;
        msAPI_Scaler_SetCVBSMute(DISABLE,  s_eVEMuteStatus[PortID], src, enOutputType);
    }
}

// In order to limit the VE HW functions under the control of MACRO 'ENABLE_VE'
// Add a API interface to replace the drv interface called by AP layer
// we want to make sure there is no DRV functions be called for VE in AP layer
void msAPI_VE_SetTtxBuffer(MS_U32 u32StartAddr, MS_U32 u32Size)
{
    if(!MDrv_VE_GetInfo()->stCaps.bVESupported)
    {
        return;
    }

    MDrv_VE_SetTtxBuffer(u32StartAddr, u32Size);
}

void msAPI_VE_SetOutputCtrl(PMS_VE_Output_Ctrl pOutputCtrl)
{
    if(!MDrv_VE_GetInfo()->stCaps.bVESupported)
    {
        return;
    }

    MDrv_VE_SetOutputCtrl(pOutputCtrl);
}

void msAPI_VE_SetBlackScreen(MS_BOOL bEn)
{
    DEBUG_VE(printf("VE black screen: bEn = %u\n", bEn));

    if((!MDrv_VE_GetInfo()->stCaps.bVESupported) || (s_eVEBlackScreenStatus == bEn))
    {
        return;
    }
    s_eVEBlackScreenStatus = bEn;
    MDrv_VE_SetBlackScreen(bEn);
}

#else //NOT ENABLE_VE
void msAPI_Scaler_SetVE(INPUT_SOURCE_TYPE_t src,E_DEST_TYPE enOutputType)
{
    UNUSED(src);
    UNUSED(enOutputType);
}

void msAPI_Scaler_SetAFDToVEWSS(BOOLEAN bEn, U8 u8AFD, U8 u8SrcARC)
{
    UNUSED(bEn);
    UNUSED(u8AFD);
    UNUSED(u8SrcARC);
}

void msAPI_VE_SetTtxBuffer(MS_U32 u32StartAddr, MS_U32 u32Size)
{
    UNUSED(u32StartAddr);
    UNUSED(u32Size);
}

void msAPI_VE_SetOutputCtrl(PMS_VE_Output_Ctrl pOutputCtrl)
{
    UNUSED(pOutputCtrl);
}

void msAPI_VE_SetBlackScreen(MS_BOOL bEn)
{
    UNUSED(bEn);
}

void msAPI_VE_Exit(void)
{
    return;
}
#endif // #if ENABLE_VE

MS_BOOL msAPI_VE_GetTtxReadDoneStatus(void)
{
#if ENABLE_VE
    return MDrv_VE_GetTtxReadDoneStatus();
#else
    return FALSE;
#endif
}

void msAPI_Scaler_IPAutoCoastHandler(void)
{
#if ENABLE_IP_AUTO_COAST
    if (IsDigitalSourceInUse() && (!(MDrv_AVD_GetStatus() & VD_CHECK_HSYNC_LOCKED)))
    {
        // VD timing is unstable, keep IP coast active
    }
    else
    {
        // signal is stable, inactive IP coast
        MApi_XC_ClearIPCoastStatus();
    }
#endif
}

void MApi_XC_Sys_SetSrcIsHD(MS_BOOL bIsHd, SCALER_WIN eWindow)
{
    bSrcIsHD[eWindow] = bIsHd;
}

MS_BOOL MApi_XC_Sys_IsSrcHD(SCALER_WIN eWindow)
{
    return bSrcIsHD[eWindow];
}

///////////////////////////////////////////////////////////////////////
/// ACE related
///////////////////////////////////////////////////////////////////////

static MS_U8 su8RedBrightness = BRIGHTNESS_BYPASS;
static MS_U8 su8GreenBrightness = BRIGHTNESS_BYPASS;
static MS_U8 su8BlueBrightness = BRIGHTNESS_BYPASS;
//////////////////////////////////////////////////////////////////
// Patch DTG color checker (video and GWIN inconsistency problem
// parameter:
//    [IN] u8Mode: 0 .. off
//                 1 .. scene1
//                 2 .. scene2
//
void MApi_XC_Sys_ACE_PatchDTGColorChecker(MS_U8 u8Mode)
{
    static MS_U16 u16TmpColorMatrix[10];

#if (ENABLE_DLC)
    static MS_U8 bEnableDLC;
#endif

    MS_U16 u16DefaultColorMatrix[9] =
    {
        0x0662, 0x04A7, 0x0000, 0x1340, 0x04A7, 0x1190, 0x0000, 0x04A7, 0x0812
    };

    MS_U16 u16Patch2ColorMatrix[9] =
    {
        0x047D, 0x0346, 0x0000, 0x1249, 0x0346, 0x1119, 0x0000, 0x0346, 0x05AC
    };

    if (u8Mode)
    {
        // store current color matrix
        MApi_XC_ACE_GetColorMatrix(MAIN_WINDOW, u16TmpColorMatrix);

        if (u8Mode==1)
            MApi_XC_ACE_SetColorMatrix(MAIN_WINDOW, u16DefaultColorMatrix);
        else
            MApi_XC_ACE_SetColorMatrix(MAIN_WINDOW, u16Patch2ColorMatrix);

#if (ENABLE_DLC)
        bEnableDLC = g_bEnableDLC;
        g_bEnableDLC = FALSE;
        MApi_XC_DLC_SetOnOff( DISABLE, MAIN_WINDOW );
#endif

#if (ENABLE_DBC)
       MApi_XC_Sys_DLC_DBC_OnOff( DISABLE );
#endif
        // specific settings for MHEG5
        MApi_XC_ACE_PatchDTGColorChecker(u8Mode);
    }
    else
    {
        // restore color matrix
        MApi_XC_ACE_SetColorMatrix(MAIN_WINDOW, u16TmpColorMatrix);

#if (ENABLE_DLC)
        g_bEnableDLC = bEnableDLC;
        MApi_XC_DLC_SetOnOff( g_bEnableDLC, MAIN_WINDOW );
#endif

#if (ENABLE_DBC)
        MApi_XC_Sys_DLC_DBC_OnOff( ENABLE );
#endif
        // restore register settings
        MApi_XC_ACE_PatchDTGColorChecker(u8Mode);
    }
}

#if ENABLE_PRECISE_RGBBRIGHTNESS
static MS_U16 su16Red_ADJ_Brightness = (BRIGHTNESS_BYPASS << 3);
static MS_U16 su16Green_ADJ_Brightness = (BRIGHTNESS_BYPASS << 3);
static MS_U16 su16Blue_ADJ_Brightness = (BRIGHTNESS_BYPASS << 3);

MS_U16 MApi_XC_Sys_ACE_transferRGB_Bri(MS_U16 u16Brightness, MS_U8 u8Brightnesstype)
{
    MS_U8 su8Brightness = 0;
    MS_U16 u16TempBrightness;

    switch(u8Brightnesstype)
    {
        case BRIGHTNESS_R:
            su16Red_ADJ_Brightness = u16Brightness;
            su8Brightness = su8RedBrightness;
            break;
        case BRIGHTNESS_G:
            su16Green_ADJ_Brightness = u16Brightness;
            su8Brightness = su8GreenBrightness;
            break;
        case BRIGHTNESS_B:
            su16Blue_ADJ_Brightness = u16Brightness;
            su8Brightness = su8BlueBrightness;
            break;
        default:
            break;
    }

    u16TempBrightness = su8Brightness * u16Brightness / BRIGHTNESS_BYPASS;

    u16TempBrightness = MIN(u16TempBrightness, 0x7FF);
    return u16TempBrightness;
}

MS_U8 MApi_XC_Sys_ACE_transfer_Bri(MS_U8 u8Brightness, MS_U8 u8Brightnesstype)
{
    MS_U8 su8Brightness = 0;
    MS_U16 u16TempBrightness;
    switch(u8Brightnesstype)
    {
        case BRIGHTNESS_R:
            su8RedBrightness =u8Brightness;
            su8Brightness = (su16Red_ADJ_Brightness >> 3);
            break;
        case BRIGHTNESS_G:
            su8GreenBrightness =u8Brightness;
            su8Brightness = (su16Green_ADJ_Brightness >> 3);
            break;
        case BRIGHTNESS_B:
            su8BlueBrightness =u8Brightness;
            su8Brightness = (su16Blue_ADJ_Brightness >> 3);
            break;
        default:
            break;
    }
    u16TempBrightness = (MS_U16)(su8Brightness * u8Brightness) / BRIGHTNESS_BYPASS;
    u16TempBrightness = MIN(u16TempBrightness, 255);
    return (U8)u16TempBrightness;
}
#else
static MS_U8 su8Red_ADJ_Brightness = BRIGHTNESS_BYPASS;
static MS_U8 su8Green_ADJ_Brightness = BRIGHTNESS_BYPASS;
static MS_U8 su8Blue_ADJ_Brightness = BRIGHTNESS_BYPASS;

MS_U8 MApi_XC_Sys_ACE_transferRGB_Bri(MS_U8 u8Brightness, MS_U8 u8Brightnesstype)
{
    MS_U8 su8Brightness = 0;
    MS_U16 u16TempBrightness;
    switch(u8Brightnesstype)
    {
        case BRIGHTNESS_R:
            su8Red_ADJ_Brightness = u8Brightness;
            su8Brightness = su8RedBrightness;
            break;
        case BRIGHTNESS_G:
            su8Green_ADJ_Brightness = u8Brightness;
            su8Brightness = su8GreenBrightness;
            break;
        case BRIGHTNESS_B:
            su8Blue_ADJ_Brightness = u8Brightness;
            su8Brightness = su8BlueBrightness;
            break;
        default:
            break;
    }
    u16TempBrightness = (MS_U16)(su8Brightness * u8Brightness) / BRIGHTNESS_BYPASS;
    u16TempBrightness = MIN(u16TempBrightness, 255);
    return (MS_U8)u16TempBrightness;
}

MS_U8 MApi_XC_Sys_ACE_transfer_Bri(MS_U8 u8Brightness, MS_U8 u8Brightnesstype)
{
    MS_U8 su8Brightness = 0;
    MS_U16 u16TempBrightness;
    switch(u8Brightnesstype)
    {
        case BRIGHTNESS_R:
            su8RedBrightness =u8Brightness;
            su8Brightness = su8Red_ADJ_Brightness;
            break;
        case BRIGHTNESS_G:
            su8GreenBrightness =u8Brightness;
            su8Brightness = su8Green_ADJ_Brightness;
            break;
        case BRIGHTNESS_B:
            su8BlueBrightness =u8Brightness;
            su8Brightness = su8Blue_ADJ_Brightness;
            break;
        default:
            break;
    }
    u16TempBrightness = (MS_U16)(su8Brightness * u8Brightness) / BRIGHTNESS_BYPASS;
    u16TempBrightness = MIN(u16TempBrightness, 255);
    return (U8)u16TempBrightness;
}

#endif

///////////////////////////////////////////////////////////////////////
/// DLC related
///////////////////////////////////////////////////////////////////////
#if ENABLE_DBC
void MApi_XC_Sys_DLC_DBC_OnOff(MS_BOOL bEnable)
{
    XC_DLC_init  stXC_DLC_InitData;


    printf("MApi_XC_Sys_DLC_DBC_OnOff(bEnable=%u)\n", bEnable);

    if( MApi_XC_IsYUVSpace(MAIN_WINDOW) )
    {
        if( (IsVgaInUse() == FALSE)
         //&& ( (MApi_XC_HDMI_GetHdmiType(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) == E_HDMI_STATUS_DVI)== FALSE )
          )
        {
            //printf("g_bEnableDLC=%u\n", g_bEnableDLC);
            if(bEnable)
            {
                if(!g_bEnableDLC)
                {
                    _MApi_XC_Sys_Init_DLC();
                }

                _MApi_XC_Sys_Init_DLC_DBC(&stXC_DLC_InitData);

                //printf("MApi_XC_DLC_DBC_GetDebugMode()=0x%X\n", MApi_XC_DLC_DBC_GetDebugMode());

                MApi_XC_DLC_DBC_SetDebugMode(MApi_XC_DLC_DBC_GetDebugMode() | BIT0); //[0] DBC On/Off

                //printf("MApi_XC_DLC_DBC_GetDebugMode()=0x%X\n", MApi_XC_DLC_DBC_GetDebugMode());

                MApi_XC_DLC_DBC_SetReady(TRUE);
            }
            else
            {
                MApi_XC_DLC_DBC_AdjustYCGain();
                MApi_XC_DLC_DBC_SetDebugMode(MApi_XC_DLC_DBC_GetDebugMode() & (~BIT0)); //[0] DBC On/Off
            }
            MApi_XC_DLC_DBC_Setstatus(bEnable);
            MApi_XC_DLC_DBC_UpdatePWM( DBC_MAX_PWM );
            Panel_Backlight_PWM_ADJ(DBC_MAX_PWM);
        }
    }

}

void MApi_XC_Sys_DLC_DBC_Handler(void)
{
    MS_U16 u16PWM = 0x00;

    u16PWM = MApi_XC_DLC_DBC_Handler();

    //printf("(u16PWM=%u)", u16PWM);

    if(u16PWM <= 0xFF)
    {
        Panel_Backlight_PWM_ADJ(u16PWM);
    }
}

void MApi_XC_Sys_DLC_DBC_YCGainInit(void)
{
    MS_U8 u8YGain_M, u8YGain_L, u8CGain_M, u8CGain_L;

#if DBC_YC_GAIN_CONTROL
    u8YGain_M = DBC_Y_GAIN_M;
    u8YGain_L = DBC_Y_GAIN_L;
    u8CGain_M = DBC_C_GAIN_M;
    u8CGain_L = DBC_C_GAIN_L;
#else
    u8YGain_M = 0;
    u8YGain_L = 0;
    u8CGain_M = 0;
    u8CGain_L = 0;
#endif

    MApi_XC_DLC_DBC_YCGainInit(u8YGain_M, u8YGain_L, u8CGain_M, u8CGain_L);

}
#endif

#if( ENABLE_DLC )
void MApi_XC_Sys_DLC_Task(void)
{
    static MS_BOOL g_bHistogramReady = 0;

    //printf("{dlc=%u,%u}", g_bEnableDLC, MsOS_GetSystemTime());

#if ENABLE_3D_PROCESS
    if(MApi_XC_Get_3D_Input_Mode(MAIN_WINDOW) != E_XC_3D_INPUT_MODE_NONE)
    {
        MApi_XC_DLC_EnableMainSubCurveSynchronization(TRUE);
    }
    else
    {
        MApi_XC_DLC_EnableMainSubCurveSynchronization(FALSE);
    }
#endif

    if( g_bHistogramReady )
    {
        if(g_bEnableDLC)
        {
            MApi_XC_DLC_Handler(MAIN_WINDOW);

        #if ENABLE_DBC
            if (!MApi_XC_DLC_DBC_Getstatus())
                MApi_XC_DLC_CGC_Handler();
        #else
            MApi_XC_DLC_CGC_Handler();
        #endif
        }

        g_bHistogramReady = FALSE;
    }

    if( !g_bHistogramReady )
    {
        if( MApi_XC_DLC_GetHistogramHandler(MAIN_WINDOW) == TRUE )
        {
            g_bHistogramReady = TRUE;
        }
        //printf("g_bHistogramReady=%u\n", g_bHistogramReady);
    }

  #if ENABLE_DBC
    if( g_bHistogramReady )
    {
        if( MApi_XC_DLC_DBC_Getstatus() )
            MApi_XC_Sys_DLC_DBC_Handler();
    }
  #endif
}
#endif

///////////////////////////////////////////////////////////////////////
/// PQ related
///////////////////////////////////////////////////////////////////////
void MApi_XC_Sys_Periodic_Handler(SCALER_WIN eWindow, MS_BOOL bRealTimeMonitorOnly)
{
    static U32 u32TimerCounter = 0;
    static MS_U8 u8Operat_flag = TRUE;

//printf(" Periodic_Handler ");

    if ( (msAPI_Timer_DiffTimeFromNow(u32TimerCounter) > 6) ) // updated by Bruce.Liu 20150831
    {
        u32TimerCounter = msAPI_Timer_GetTime0();
        u8Operat_flag = TRUE;
    }
    else
    {
        u8Operat_flag = FALSE;

        UNUSED(eWindow);
        UNUSED(bRealTimeMonitorOnly);
    }


    if(u8Operat_flag)
    {
        u8Operat_flag = FALSE;
#if 0 // for MFC debug
        MS_U8 i;
        MS_U8 bk;
        MS_BOOL bTest;
        // disable SC_INT_VSINT interrupt

        bk = XBYTE[0x2F00];
        XBYTE[0x2F00] = 0x1D;
        bTest = XBYTE[0x2F22] & 0x02;
        MDrv_WriteByte(BK_SELECT_00, REG_BANK_GOPINT);
        MDrv_WriteRegBit(L_BK_GOPINT(0x14), ENABLE, (1 << (SC_INT_VSINT)));

        // cc.chen
        if (bTest)
        {
            for (i = 0; i<10; i++)
            {
                printf("MEMC [%bd] = 0x%x\n", i, g_wRegsArray[i]);
            }
        }
        // enable SC_INT_VSINT interrupt
        MDrv_WriteRegBit(L_BK_GOPINT(0x14), DISABLE, (1 << (SC_INT_VSINT)));
        XBYTE[0x2F00] = bk;
#endif

    #if 1//( !PQ_ADAP_TUNING_RUN_IN_ISR )
        MDrv_PQ_AdaptiveTuning();
    #endif

    #if( ENABLE_DLC )
        #if (!ENABLE_DLC_ISR)
        MApi_XC_Sys_DLC_Task();
        #endif
    #endif

    #if(ENABLE_DLC_ISR &&ENABLE_DLC)
        #if (ENABLE_DLC_ISR_DEBUG)
        printf("[%s]->%d.u32DLC_ISR_Time=%lu.\n",__func__,__LINE__,u32DLC_ISR_Time);
        #endif
    #endif
#if 0//ENABLE_WBLE, Daten FixMe
        msAPI_WBLE_Handler();         // Daten: no use now
#endif

        if(bRealTimeMonitorOnly == FALSE)
        {
        }
    }
    else
    {
        //printf("******Current Timer=%lx\n",u32TimerCounter);
    }
}

/******************************************************************************/
/// Set NR
/// @param enInputSourceType \b IN: for different input source
/// @param bAuto \b IN: auto on/off
/// @param en3DNRType \b IN: different NR mode
/******************************************************************************/

void MApi_XC_Sys_PQ_SetNR(E_XC_PQ_3D_NR en3DNRType, SCALER_WIN eWindow)
{
    PQ_3D_NR_FUNCTION_TYPE enPQNRType;
    PQ_WIN enPQWin;

    switch(eWindow)
    {
    default:
    case MAIN_WINDOW:
        enPQWin = PQ_MAIN_WINDOW;
        break;
    case SUB_WINDOW:
        enPQWin = PQ_SUB_WINDOW;
        break;
    }


    switch(en3DNRType)
    {
    default:
    case E_XC_PQ_3D_NR_OFF:
        enPQNRType = PQ_3D_NR_OFF;
        break;
    case E_XC_PQ_3D_NR_LOW:
        enPQNRType = PQ_3D_NR_LOW;
        break;
    case E_XC_PQ_3D_NR_MID:
    case E_XC_PQ_3D_NR_DEFAULT:
        enPQNRType = PQ_3D_NR_MID;
        break;
    case E_XC_PQ_3D_NR_HIGH:
        enPQNRType = PQ_3D_NR_HIGH;
        break;
    case E_XC_PQ_3D_NR_AUTO:
        enPQNRType = PQ_3D_NR_AUTO;
        break;
    }
    #if(ENABLE_NEW_AUTO_NR == 1)
    if(IsATVInUse())
    {
        if(enPQNRType == PQ_3D_NR_LOW)
        {
            enPQNRType = PQ_3D_NR_AUTO_LOW_L;
        }
        else if(enPQNRType == PQ_3D_NR_MID)
        {
            enPQNRType = PQ_3D_NR_AUTO_MID_M;
        }
        else if(enPQNRType == PQ_3D_NR_HIGH)
        {
            enPQNRType = PQ_3D_NR_AUTO_HIGH_H;
        }
    }
    #endif

    //Ryan ToDo tralate en3DNRType to PQ type
    if(!MApi_XC_IsMemoryFormat422(eWindow) || MApi_XC_IsCurrentFrameBufferLessMode())
    {
        // VGA/RGB YUV444 or RGB444 no NR, in fact, application should disable NR when VGA/DVI
        enPQNRType = PQ_3D_NR_OFF;
        MDrv_PQ_LoadNRTable(enPQWin, enPQNRType);
    }
    else
    {
        MDrv_PQ_LoadNRTable(enPQWin, enPQNRType);
    }
#if 0
    printf("(2)NR=%u\n", MDrv_ReadByte(L_BK_DNR(0x21)) & BIT0);
    MDrv_WriteByte(BK_SELECT_00, u8Bank);
#endif
}
/******************************************************************************/
/// Wrapper for MDrv_PQ_ReduceBW_ForOSD
/// @param MS_U8 \b IN: for different input source
/// @param MS_BOOL \b IN: auto on/off
/******************************************************************************/

void MApi_XC_Sys_PQ_ReduceBW_ForOSD(MS_U8 PqWin, MS_BOOL bOSD_On)
{
    MDrv_PQ_ReduceBW_ForOSD((PQ_WIN) PqWin, bOSD_On);

  #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)
    MDrv_BW_LoadTableByContext((PQ_WIN) PqWin);
  #endif
}

void MApi_XC_Sys_Do_HPD(INPUT_SOURCE_TYPE_t enInputSourceType )
{
    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_Sys_Do_HPD(src=%u)\n", enInputSourceType); );

    // HPD Spec
    // HIGH Level 2.4 ~ 5.3V
    // LOW Level 0 ~ 0.4V

    if ( !IsSrcTypeHDMI(enInputSourceType) )
    {
        return;
    }
    else
    {
        //Get Inputport
        E_MUX_INPUTPORT enHDMIport = MApi_XC_Mux_GetHDMIPort(enInputSourceType);

        // HPD low
        MApi_XC_Sys_SetHPD(DISABLE, enHDMIport);

        // reset HDCP status
        MApi_XC_HDCP_Status_Reset();

        // reset HDMI packets
        MDrv_HDMI_pkt_reset(REST_AVMUTE|REST_Y_COLOR|REST_PIXEL_REPETITION|REST_FRAME_REPETITION|REST_GCP_PKT|REST_HDMI_STATUS);

        // delay
        //MsOS_DelayTask( HDMI_HPD_DELAY );
        MsOS_DelayTask( HDMI_HPD_DELAY__RESET_TO_CLK_HIGH );

        // HPD high
        MApi_XC_Sys_SetHPD(ENABLE, enHDMIport);

    }
}

void MApi_XC_Sys_SetHPD( MS_BOOL bEnable, E_MUX_INPUTPORT enInputPortType )
{
    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_Sys_SetHPD(en=%u, port=%u)\n", bEnable, enInputPortType) );

    if(bEnable)
    {
        MApi_XC_HDMI_SetDVIClkPullLow(FALSE, enInputPortType);    // DVI clock pull high
        //MsOS_DelayTask(300);
        MsOS_DelayTask(HDMI_HPD_DELAY__CLK_HIGH_TO_HPD_HIGH);
        MApi_XC_HDMI_SetHotPlug(ENABLE, enInputPortType);
        //(printf("\r\n++++++ Enable HPD ++++++\n"));
    }
    else
    {
        MApi_XC_HDMI_SetHotPlug(FALSE, enInputPortType);
        //MsOS_DelayTask(200);
        MsOS_DelayTask(HDMI_HPD_DELAY__HPD_LOW_TO_CLK_LOW);
        MApi_XC_HDMI_SetDVIClkPullLow(TRUE, enInputPortType);    // DVI clock pull low
        //(printf("\r\n------ Disable HPD ------\n"));
    }
}

void MApi_XC_Sys_SetHPD_ALL(MS_BOOL bEnable)
{
    U8 u8DummyIdx = 0;

    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_Sys_SetHPD_ALL(en=%u,) at %u\n", bEnable, MsOS_GetSystemTime() ); );

    U8 u8HdmiPortNumMax = MApi_XC_Sys_Get_HdmiPortNumMax();

    if (bEnable)
    {
        for(u8DummyIdx=0; u8DummyIdx<u8HdmiPortNumMax; u8DummyIdx++)
        {
            if( eHdmiPortMappingResult[u8DummyIdx] != INPUT_PORT_NONE_PORT )
                MApi_XC_HDMI_SetDVIClkPullLow(FALSE, eHdmiPortMappingResult[u8DummyIdx]);      // DVI clock pull high
        }

        //MsOS_DelayTask(300);
        MsOS_DelayTask(HDMI_HPD_DELAY__CLK_HIGH_TO_HPD_HIGH);

        for(u8DummyIdx=0; u8DummyIdx<u8HdmiPortNumMax; u8DummyIdx++)
        {
            if( eHdmiPortMappingResult[u8DummyIdx] != INPUT_PORT_NONE_PORT )
                MApi_XC_HDMI_SetHotPlug(TRUE, eHdmiPortMappingResult[u8DummyIdx]);
        }
    }
    else
    {
        for(u8DummyIdx=0; u8DummyIdx<u8HdmiPortNumMax; u8DummyIdx++)
        {
            if( eHdmiPortMappingResult[u8DummyIdx] != INPUT_PORT_NONE_PORT )
                MApi_XC_HDMI_SetHotPlug(FALSE, eHdmiPortMappingResult[u8DummyIdx]);
        }

        //MsOS_DelayTask(300);
        MsOS_DelayTask(HDMI_HPD_DELAY__HPD_LOW_TO_CLK_LOW);

        for(u8DummyIdx=0; u8DummyIdx<u8HdmiPortNumMax; u8DummyIdx++)
        {
            if( eHdmiPortMappingResult[u8DummyIdx] != INPUT_PORT_NONE_PORT )
                MApi_XC_HDMI_SetDVIClkPullLow(TRUE, eHdmiPortMappingResult[u8DummyIdx]);   // DVI clock pull low
        }
    }
}

//void MApi_XC_Sys_HDMI_PowerOff(void)
void MApi_XC_HPD_Do_PowerOff(void)
{
    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_HPD_Do_PowerOff()\n"); );

    //printf("---Power Off!---\n");
#if( ENABLE_CEC )
    if( msAPI_CEC_Is_CecTurnOn() )
    {
        // Set All port HPD high...
        // Already is high, do nothing...
        //MApi_XC_Sys_SetHPD_ALL(ENABLE);
    }
    else
#endif
    {
        // All port do HPD low...
        //MApi_XC_Sys_SetHPD_ALL(ENABLE);
        //msAPI_Timer_Delayms(700);
#if(ENABLE_POWER_SAVING_DPMS_DVI==0)
        MApi_XC_Sys_SetHPD_ALL(DISABLE);
#endif
    }
}

void MApi_XC_HPD_Do_PowerOnInit(void)
{
    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_HPD_Do_PowerOnInit() at %u\n", MsOS_GetSystemTime()); );


    // reset HDCP status
    MApi_XC_HDCP_Status_Reset();

    // reset HDMI packets
    MDrv_HDMI_pkt_reset(REST_AVMUTE|REST_Y_COLOR|REST_PIXEL_REPETITION|REST_FRAME_REPETITION|REST_GCP_PKT|REST_HDMI_STATUS);


    // If CEC on, Set all HPD High
    // If CEC off, Set all HPD low ( HPD wiil set high when change to hdmi source)

#if (ENABLE_HDMI_HPD_TASK )
    //MApi_XC_HPD_Task_Start(E_HPD_TASK_FOR_POWER_ON_INIT);   //Enable state machine flow
    MApi_XC_HPD_Task_PowerOnInit();   //Enable state machine flow

    MApi_XC_HPD_Task();     //For state machine go one step forward to set HDMI_HPD high directly

#else

  #if( ENABLE_CEC )
    if( msAPI_CEC_Is_CecTurnOn() )
    {
        // When boot on, all HPD and DVI clock should be configured to HIGH
        // later when switch input source, it will only HPD to the specific source (other sources remains high)
        MApi_XC_Sys_SetHPD_ALL(ENABLE);
    }
    else
  #endif
    {
        // When boot on, all HPD and DVI clock should be configured to HIGH
        // later when switch input source, it will only HPD to the specific source (other sources remains high)
        MApi_XC_Sys_SetHPD_ALL(DISABLE);
    }
#endif

}

#if(!SUPPORT_HDMI_IMM_SWITCH)
// For HDMI to other source
void MApi_XC_HPD_Do_ExitHDMI(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE)
{
    //PRINT_CURRENT_LINE();
    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_HPD_Do_ExitHDMI(enINPUT_SOURCE_TYPE=%u)\n", enINPUT_SOURCE_TYPE); );

    if( !IsSrcTypeHDMI(enINPUT_SOURCE_TYPE) )
        return;

#if(ENABLE_CEC)
    if( msAPI_CEC_Is_CecTurnOn() )
    {
        // Do nothing
    }
    else
#endif
    {
        E_MUX_INPUTPORT enHDMIport = MApi_XC_Mux_GetHDMIPort(enINPUT_SOURCE_TYPE);
        if( enHDMIport == INPUT_PORT_NONE_PORT )
        {
            return;
        }

        // Set HPD to low
    #if( ENABLE_HDMI_HPD_TASK )
        MApi_XC_HPD_Task_Start( enINPUT_SOURCE_TYPE, E_HPD_TASK_FOR_EXIT_HDMI_HPD_LOW);

    #else
        MApi_XC_Sys_SetHPD(DISABLE, enHDMIport );
    #endif
    }
}

void MApi_XC_HPD_Do_EnterHDMI(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE)
{
    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_HPD_Do_EnterHDMI(enINPUT_SOURCE_TYPE=%u) at %u\n", enINPUT_SOURCE_TYPE, MsOS_GetSystemTime() ); );

    if( !IsSrcTypeHDMI(enINPUT_SOURCE_TYPE) )
        return;

    E_MUX_INPUTPORT enHDMIport = MApi_XC_Mux_GetHDMIPort(enINPUT_SOURCE_TYPE);
    if( enHDMIport == INPUT_PORT_NONE_PORT )
        return;

#if( ENABLE_HDMI_HPD_TASK )
  #if 1
    if( s_Hdmi_Hpd_bFirstTimeChangeSrcDone == FALSE ) // Power on first time
    {
        MApi_XC_HPD_Task_Start(enINPUT_SOURCE_TYPE, E_HPD_TASK_FOR_LOW_TO_HIGH);
    }
    else
  #endif
    {
        MApi_XC_HPD_Task_Start(enINPUT_SOURCE_TYPE, E_HPD_TASK_FOR_CHANGE_SRC);
    }

#else

    // If CEC on, HPD:  High -> Low -> High
    // If CEC off, HPD:                Low -> High
    if( msAPI_CEC_Is_CecTurnOn() )
    {
        MApi_XC_Sys_Do_HPD(enINPUT_SOURCE_TYPE);

     #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("Do_HPD End");
     #endif
    }
    else
    {
        MApi_XC_Sys_SetHPD(ENABLE, enHDMIport );

     #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("SetHPD End");
     #endif
    }

#endif

}
#endif

void MApi_XC_HPD_Do_Reset(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE)
{
    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_HPD_Do_Reset(enINPUT_SOURCE_TYPE=%u)\n", enINPUT_SOURCE_TYPE); );

    if( !IsSrcTypeHDMI(enINPUT_SOURCE_TYPE) )
        return;

/*    E_MUX_INPUTPORT enHDMIport = MApi_XC_Mux_GetHDMIPort(enINPUT_SOURCE_TYPE);
    if( enHDMIport == INPUT_PORT_NONE_PORT )
        return;
*/

    // Force HPD : High --> low --> High
#if( ENABLE_HDMI_HPD_TASK )

    MApi_XC_HPD_Task_Start(enINPUT_SOURCE_TYPE, E_HPD_TASK_FOR_HIGH_LOW_HIGH);

#else

    MApi_XC_Sys_Do_HPD(enINPUT_SOURCE_TYPE);
#endif
}

#if(ENABLE_CEC)
void MApi_XC_HPD_Do_Reset_ForCECOnOff(void)
{
    //PRINT_CURRENT_LINE();
    DEBUG_HDMI_HOT_PLUG( printf("MApi_XC_HPD_Do_Reset_ForCECOnOff()\n"); );

    INPUT_SOURCE_TYPE_t eCurInputSrc = SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW);
    E_MUX_INPUTPORT enCurHDMIport = MApi_XC_Mux_GetHDMIPort(eCurInputSrc);

    DEBUG_HDMI_HOT_PLUG( printf("eCurInputSrc=%u, enCurHDMIport=%u\n", eCurInputSrc, enCurHDMIport); );

    //U8 u8HdmiIdx;
    //U8 u8HdmiIdxMax = MApi_XC_Sys_Get_HdmiPortNumMax();

    // If CEC turn on, Set all HDMI port HPD high
    // If CEC turn off, Set only active HDMI port HPD high

    U32 u32SrcType;
    INPUT_SOURCE_TYPE_t eSrcType;
    E_MUX_INPUTPORT enHDMIport;

    for(u32SrcType = INPUT_SOURCE_HDMI; u32SrcType <= INPUT_SOURCE_HDMI4; u32SrcType += 1 )
    {
        eSrcType = (INPUT_SOURCE_TYPE_t)u32SrcType;
        enHDMIport = MApi_XC_Mux_GetHDMIPort(eSrcType);

        DEBUG_HDMI_HOT_PLUG( printf("eSrcType=%u, enHDMIport=%u\n", eSrcType, enHDMIport); );

        if( enHDMIport == INPUT_PORT_NONE_PORT )
        {
            // Not in used
            // No need control HPD
        }
        else if( enHDMIport == enCurHDMIport ) // Current source port => Don't change it
        {
            DEBUG_HDMI_HOT_PLUG( printf("enCurHDMIport=%u no change\n", enCurHDMIport); );
        }
        else // Other HDMI source
        {
        #if(ENABLE_CEC)
            if( msAPI_CEC_Is_CecTurnOn() )
            {
                // Set  HPD Low ==> high
            #if 0//( ENABLE_HDMI_HPD_TASK )
                MApi_XC_HPD_Task_Start(eSrcType, E_HPD_TASK_FOR_LOW_TO_HIGH);
            #else
                MApi_XC_Sys_SetHPD( ENABLE, enHDMIport );
            #endif
            }
            else
        #endif
            {
                // Set  HPD High ==> Low
            #if 0//( ENABLE_HDMI_HPD_TASK )
                MApi_XC_HPD_Task_Start(eSrcType, E_HPD_TASK_FOR_EXIT_HDMI_HPD_LOW);
            #else
                MApi_XC_Sys_SetHPD( DISABLE, enHDMIport );
            #endif
            }
        }
    }

    DEBUG_HDMI_HOT_PLUG( MApi_XC_HDMI_Print_PortStatus(); );

}
#endif

#if( ENABLE_HDMI_HPD_TASK )

typedef enum
{
    E_HPD_STATE__NONE,

    E_HPD_STATE__SET_HPD_DISABLE, // HotPlug=0, goto next state
    E_HPD_STATE__SET_HPD_DISABLE_DELAY, // Stay 250ms, Set clk low
    E_HPD_STATE__RESET_HDMI,
    E_HPD_STATE__HPD_DELAY,
    E_HPD_STATE__SET_HPD_ENABLE, // DviClk=High, delay(300), HotPlug=1
    E_HPD_STATE__SET_HPD_ENABLE_DELAY,

    E_HPD_STATE__HPD_OK,

} EnuHpdState;

#define HDMI_PORT_NUM_MAX   4

static EnuHpdState s_Hdmi_Hpd_aeCurState[HDMI_PORT_NUM_MAX];// = {E_HPD_STATE__NONE,};

static U32 s_Hdmi_Hpd_au32DelayStartTime[HDMI_PORT_NUM_MAX];

// for IMMESWITCH, HDP should be pull low/high at least once
//static BOOLEAN bIMMESWITCH_InitHPD = FALSE;

static EnuHpdTaskMode s_aenHpdTaskMode[HDMI_PORT_NUM_MAX];

U8 MApi_XC_Sys_HdmiSrcToIdx(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE)
{
    if( enINPUT_SOURCE_TYPE < INPUT_SOURCE_HDMI || enINPUT_SOURCE_TYPE > INPUT_SOURCE_HDMI4)
    {
        PRINT_CURRENT_LINE();
        printf("\nError: Invalid HDMI source=%u!", enINPUT_SOURCE_TYPE);
        return 0;
    }

    return (enINPUT_SOURCE_TYPE-INPUT_SOURCE_HDMI);
}


#define HDMI_HDP_TASK_DBG(x)    //x

void MApi_XC_HPD_Task_PowerOnInit(void)
{
    HDMI_HDP_TASK_DBG( printf("MApi_XC_HPD_Task_PowerOnInit()\n"); );

    U8 u8HdmiIdx;
    U8 u8HdmiIdxMax = MApi_XC_Sys_Get_HdmiPortNumMax();


    //PRINT_CURRENT_LINE();

    // If CEC turn on, Set all HDMI port HPD high
    // If CEC turn off, Set only active HDMI port HPD high
/*
    if( msAPI_CEC_Is_CecTurnOn() )
    {
        HDMI_HDP_TASK_DBG( printf("Set all HDMI HPD high\n"); );
    }
*/

    for(u8HdmiIdx = 0; u8HdmiIdx < u8HdmiIdxMax; u8HdmiIdx += 1 )
    {
        s_aenHpdTaskMode[u8HdmiIdx] = E_HPD_TASK_FOR_POWER_ON_INIT;

        if( eHdmiPortMappingResult[u8HdmiIdx] == INPUT_PORT_NONE_PORT )
        {
            // No need control HPD
            s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__NONE;
        }
        else
        {
        #if(SUPPORT_HDMI_IMM_SWITCH)
            // Set  HPD high
            s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_ENABLE;

        #else
          #if(ENABLE_CEC)
            if( msAPI_CEC_Is_CecTurnOn() )
            {
                // Set  HPD high
                s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_ENABLE;
            }
            else
          #endif
            {
                // Set  HPD Low
                s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_DISABLE;

            }
        #endif
        }
    }
}

void MApi_XC_HPD_Task_Start(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE, EnuHpdTaskMode enHpdTaskMode)
{
    //XC_INITMISC sXC_Init_Misc;

    //PRINT_CURRENT_LINE();
    HDMI_HDP_TASK_DBG(printf(" MApi_XC_HPD_Task_Start(src=%u,%u) at %u\n", enINPUT_SOURCE_TYPE, enHpdTaskMode, MsOS_GetSystemTime()));


    if( enINPUT_SOURCE_TYPE < INPUT_SOURCE_HDMI || enINPUT_SOURCE_TYPE > INPUT_SOURCE_HDMI4)
    {
        PRINT_CURRENT_LINE();
        printf("\nError: Invalid HDMI source=%u!", enINPUT_SOURCE_TYPE);
        return ;
    }

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("HPD Task Start");
#endif

    U8 u8HdmiIdx = MApi_XC_Sys_HdmiSrcToIdx(enINPUT_SOURCE_TYPE);


    switch( enHpdTaskMode )
    {
        case E_HPD_TASK_FOR_CHANGE_SRC:
            // If power on init task is still running, skip this time
            if( (s_aenHpdTaskMode[u8HdmiIdx] == E_HPD_TASK_FOR_POWER_ON_INIT)
              &&(s_Hdmi_Hpd_aeCurState[u8HdmiIdx] != E_HPD_STATE__HPD_OK)
              )
            {
                PRINT_CURRENT_LINE();
                printf("power on init HPD task is still running, skip this time!\n");
                return;
            }

            // If last time task is still running, reset it => Set HPD high
            if( (s_aenHpdTaskMode[u8HdmiIdx] == E_HPD_TASK_FOR_CHANGE_SRC)
              &&(s_Hdmi_Hpd_aeCurState[u8HdmiIdx] != E_HPD_STATE__HPD_OK)
              )
            {
                PRINT_CURRENT_LINE();
                printf("\nError: Last HPD task is still running!");
                return;

            #if 0// Need refine
                printf("[HPD] Task is not finish, Set HPD = 1 at %u\n", MsOS_GetSystemTime());
                U8 u8DummyIdx = 0;
                for(u8DummyIdx=0; u8DummyIdx<INPUT_HDMI_VIDEO_COUNT; u8DummyIdx++)
                {
                    if( eHdmiPortMappingResult[u8DummyIdx] != INPUT_PORT_NONE_PORT )
                    {
                        MApi_XC_HDMI_SetDVIClkPullLow(FALSE, eHdmiPortMappingResult[u8DummyIdx]);  // DVI clock pull high
                        MApi_XC_HDMI_SetHotPlug(TRUE, eHdmiPortMappingResult[u8DummyIdx]); // Set HPD high
                    }
                }
            #endif
            }

            // If CEC on, HPD:  High -> Low -> High
            // If CEC off, HPD:                Low -> High
        #if(ENABLE_CEC)
            if( msAPI_CEC_Is_CecTurnOn() )
            {
                //HDMI_HDP_TASK_DBG( printf("CEC is turn on\n"); );
                s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_DISABLE;
            }
            else
        #endif
            {
                s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__RESET_HDMI;
            }

            s_aenHpdTaskMode[u8HdmiIdx] = enHpdTaskMode;

            break;

        case E_HPD_TASK_FOR_EXIT_HDMI_HPD_LOW:
            // Set HPD to low
            //printf("Src=%u, set HPD low\n", enINPUT_SOURCE_TYPE);
            s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_DISABLE;
            s_aenHpdTaskMode[u8HdmiIdx] = enHpdTaskMode;
            break;

        case E_HPD_TASK_FOR_HIGH_LOW_HIGH:
            // Set HPD Reset:  High -> low -> High
            s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_DISABLE;
            s_aenHpdTaskMode[u8HdmiIdx] = enHpdTaskMode;
            break;

        case E_HPD_TASK_FOR_LOW_TO_HIGH:
            // Set HPD:  Low -> High
            s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_ENABLE;
            s_aenHpdTaskMode[u8HdmiIdx] = enHpdTaskMode;
            break;

        default:
            printf("\nWarning: enHpdTaskMode=%u\n", enHpdTaskMode);
            break;

    }

    if( MApi_XC_HPD_Is_Task_Working() )
    {
        MApi_XC_HPD_Task();
    }

}

void MApi_XC_HPD_Task(void)
{
#if(CHAKRA3_AUTO_TEST)
    static U32 u32HPDTime = 0;
#endif

    U8 u8HdmiIdx;
    U8 u8HdmiIdxMax = MApi_XC_Sys_Get_HdmiPortNumMax();
    E_MUX_INPUTPORT eCurHdmiPort;
    BOOL bIsCurSrc = FALSE;


    for(u8HdmiIdx = 0; u8HdmiIdx < u8HdmiIdxMax; u8HdmiIdx += 1 )
    {
        if( (s_Hdmi_Hpd_aeCurState[u8HdmiIdx] == E_HPD_STATE__HPD_OK)
          ||(s_Hdmi_Hpd_aeCurState[u8HdmiIdx] == E_HPD_STATE__NONE)
          )
        {
            // Do nothing ...
            continue;
        }

        eCurHdmiPort = eHdmiPortMappingResult[u8HdmiIdx];

        //HDMI_HDP_TASK_DBG(printf(" u8HdmiIdx=%u, curState=%u, eCurHdmiPort=%u\n", u8HdmiIdx, s_Hdmi_Hpd_aeCurState[u8HdmiIdx], eCurHdmiPort););

        // Check if port valid
        if( eCurHdmiPort == INPUT_PORT_NONE_PORT )
        {
            s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__NONE;
        }
        else
        { // Check if work for current HDMI source
            if( _MApi_XC_HDMI_GetPortMapping(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) == eCurHdmiPort )
            {
                bIsCurSrc = TRUE;
            }
            else
            {
                bIsCurSrc = FALSE;
            }
        }


        switch( s_Hdmi_Hpd_aeCurState[u8HdmiIdx] )
        {
            case E_HPD_STATE__NONE:
                break;

            case E_HPD_STATE__SET_HPD_DISABLE: // HotPlug=0, delay(300), DviClk=low
        #if(CHAKRA3_AUTO_TEST)
                if( bIsCurSrc )
                {
                    PRINT_AUTOTEST_CHECKPT_TIME("Start HPD");
                    u32HPDTime = msAPI_Timer_GetTime0();
                }
        #endif

                HDMI_HDP_TASK_DBG(printf("\nport(%u) (1) E_HPD_STATE__SET_HPD_DISABLE at %u\n", eCurHdmiPort, MsOS_GetSystemTime()););

                // Set HPD low
                MApi_XC_HDMI_SetHotPlug(FALSE, eCurHdmiPort);

                s_Hdmi_Hpd_au32DelayStartTime[u8HdmiIdx] = MsOS_GetSystemTime();

                s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_DISABLE_DELAY;

                break;

            case E_HPD_STATE__SET_HPD_DISABLE_DELAY: // Delay 100 ms
                if( MsOS_Timer_DiffTimeFromNow(s_Hdmi_Hpd_au32DelayStartTime[u8HdmiIdx]) > HDMI_HPD_DELAY__HPD_LOW_TO_CLK_LOW )
                {
                    HDMI_HDP_TASK_DBG(printf("\n port(%u) (2) E_HPD_STATE__SET_HPD_DISABLE_DELAY at %u\n", eCurHdmiPort,MsOS_GetSystemTime()));

                    MApi_XC_HDMI_SetDVIClkPullLow(TRUE, eCurHdmiPort);  // DVI clock pull low

                    if( (s_aenHpdTaskMode[u8HdmiIdx] == E_HPD_TASK_FOR_POWER_ON_INIT)
                      ||(s_aenHpdTaskMode[u8HdmiIdx] == E_HPD_TASK_FOR_EXIT_HDMI_HPD_LOW)
                      )
                    {
                        //s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__HPD_DELAY;
                        s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__HPD_OK;
                        s_Hdmi_Hpd_au32DelayStartTime[u8HdmiIdx] = MsOS_GetSystemTime();
                    }
                    else
                    {
                        s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__RESET_HDMI;
                    }
                }
                break;

            case E_HPD_STATE__RESET_HDMI:
                HDMI_HDP_TASK_DBG(printf("\nport(%u) (3) E_HPD_STATE__RESET_HDMI at %u\n", eCurHdmiPort,MsOS_GetSystemTime()));

                // reset HDCP status
                MApi_XC_HDCP_Status_Reset();

                // reset HDMI packets
                MDrv_HDMI_pkt_reset(REST_AVMUTE|REST_Y_COLOR|REST_PIXEL_REPETITION|REST_FRAME_REPETITION|REST_GCP_PKT|REST_HDMI_STATUS);

                s_Hdmi_Hpd_au32DelayStartTime[u8HdmiIdx] = MsOS_GetSystemTime();

                s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__HPD_DELAY;
                break;

            case E_HPD_STATE__HPD_DELAY:
                if( MsOS_Timer_DiffTimeFromNow(s_Hdmi_Hpd_au32DelayStartTime[u8HdmiIdx]) > HDMI_HPD_DELAY__RESET_TO_CLK_HIGH )
                {
                    HDMI_HDP_TASK_DBG(printf("\nport(%u)  (4) E_HPD_STATE__HPD_DELAY at %u\n", eCurHdmiPort,MsOS_GetSystemTime()));
                    s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_ENABLE;
                }
                break;

            case E_HPD_STATE__SET_HPD_ENABLE: // DviClk=High, delay(300), HotPlug=1
                HDMI_HDP_TASK_DBG(printf("\nport(%u)  (5) E_HPD_STATE__SET_HPD_ENABLE at %u\n", eCurHdmiPort,MsOS_GetSystemTime()));

                MApi_XC_HDMI_SetDVIClkPullLow(FALSE, eCurHdmiPort);   // DVI clock pull high

                s_Hdmi_Hpd_au32DelayStartTime[u8HdmiIdx] = MsOS_GetSystemTime();
                //MsOS_DelayTask(300);
                s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__SET_HPD_ENABLE_DELAY;
                break;

            case E_HPD_STATE__SET_HPD_ENABLE_DELAY:
                if( MsOS_Timer_DiffTimeFromNow(s_Hdmi_Hpd_au32DelayStartTime[u8HdmiIdx]) > HDMI_HPD_DELAY__CLK_HIGH_TO_HPD_HIGH)
                {
                    HDMI_HDP_TASK_DBG(printf("\n port(%u) (6) E_HPD_STATE__SET_HPD_ENABLE_DELAY at %u\n", eCurHdmiPort,MsOS_GetSystemTime()));

                    MApi_XC_HDMI_SetHotPlug(TRUE, eCurHdmiPort); // Set HPD high

                    s_Hdmi_Hpd_aeCurState[u8HdmiIdx] = E_HPD_STATE__HPD_OK;
                    HDMI_HDP_TASK_DBG(printf(" port(%u) E_HPD_STATE__HPD_OK at %u\n", eCurHdmiPort, MsOS_GetSystemTime()));

                    if( bIsCurSrc )
                    {
                    #if(CHAKRA3_AUTO_TEST)
                        PRINT_AUTOTEST_TIME("End HPD ", msAPI_Timer_DiffTimeFromNow(u32HPDTime));
                    #endif
                    #if(DEBUG_CHG_SRC_TIME)
                        msDebug_PrintChgSrcTime("HPD Task End");
                    #endif
                    }
                }
                break;

            case E_HPD_STATE__HPD_OK:
                break;
        }
    }

}

BOOL MApi_XC_HPD_Is_Task_Working(void)
{
    U8 u8HdmiIdx;
    U8 u8HdmiIdxMax = MApi_XC_Sys_Get_HdmiPortNumMax();

    BOOL bIsWorking = FALSE;

    for(u8HdmiIdx = 0; u8HdmiIdx < u8HdmiIdxMax; u8HdmiIdx += 1 )
    {
        if( (s_Hdmi_Hpd_aeCurState[u8HdmiIdx] == E_HPD_STATE__NONE)
          ||(s_Hdmi_Hpd_aeCurState[u8HdmiIdx] == E_HPD_STATE__HPD_OK)
          )
        {
        }
        else
        {
            bIsWorking = TRUE;
            break;
        }
    }

    return bIsWorking;
}

#endif

#if( ENABLE_FRC_R2 )
void msAPI_XC_SendMailToFRC( U8 u8Cmd, U8 count, U8 p1, U8 p2, U8 p3, U8 p4, U8 p5, U8 p6, U8 p7, U8 p8)
{
    MBX_Msg mbxMsg;
    MBX_Result mbxResult;
    U32 u32Time;


    //mbxMsg.eRoleID          = E_MBX_ROLE_CP;
    mbxMsg.eMsgType         = E_MBX_MSG_TYPE_NORMAL;
    //mbxMsg.u8Ctrl           = 0; // Useless?
    mbxMsg.u8MsgClass       = E_MBX_CLASS_FRC;
    mbxMsg.u8Index               = u8Cmd;
    mbxMsg.u8ParameterCount      = count;
    mbxMsg.u8Parameters[0]       = p1;
    mbxMsg.u8Parameters[1]       = p2;
    mbxMsg.u8Parameters[2]       = p3;
    mbxMsg.u8Parameters[3]       = p4;
    mbxMsg.u8Parameters[4]       = p5;
    mbxMsg.u8Parameters[5]       = p6;
    mbxMsg.u8Parameters[6]       = p7;
    mbxMsg.u8Parameters[7]       = p8;
    mbxMsg.u8Parameters[8]       = 0;
    mbxMsg.u8Parameters[9]       = 0;

    u32Time = MsOS_GetSystemTime();
    do
    {
        mbxResult = MSApi_MBX_SendMsg(&mbxMsg);

        switch(mbxResult)
        {
            case E_MBX_SUCCESS:
                // Do nothing
                break;
        #if 0
            case E_MBX_ERR_PEER_CPU_BUSY:
            case E_MBX_ERR_PEER_CPU_NOTREADY:
            case E_MBX_ERR_PEER_CPU_NOT_ALIVE:
                //Error Handling here...
                break;
            case E_MBX_ERR_PEER_CPU_OVERFLOW:
                //MsOS_DelayTask(1);
                break;
        #endif
            default:
                printf("MSApi_MBX_SendMsg fail=%u\n", mbxResult);
                break;
        }

        if( (MsOS_GetSystemTime() - u32Time) > 2000 )
        {
            printf("msAPI_XC_SendMailToFRC() timeout!!\n");
            break;
        }

    }while(E_MBX_SUCCESS != mbxResult);
}
#endif

U16 MApi_XC_Sys_Get_Fpll_InVFreq(void)
{
    U32 u32Ivs = MDrv_Read3Byte(0x103142);

    if( u32Ivs == 0 )
    {
        return 1;
    }

    return (MST_XTAL_CLOCK_HZ*100/u32Ivs);
}

U16 MApi_XC_Sys_Get_Fpll_OutVFreq(void)
{
    U32 u32Ovs = MDrv_Read3Byte(0x103146);

    if( u32Ovs == 0 )
    {
        return 1;
    }

    return (MST_XTAL_CLOCK_HZ*100/u32Ovs);
}

//static BOOL s_XC_Sys_bSyncStable;

void MApi_XC_Sys_Task_InVF(void)
{
    static U16 s_XC_u16LastIVf = 0;
    static U16 s_XC_u16CurIVf = 0;
    static U8 s_XC_u8IVfStableCnt = 0;
    static BOOL s_XC_bIVfStable = 0;
    U16 u16iVfDiff;



    s_XC_u16CurIVf = MApi_XC_Sys_Get_Fpll_InVFreq();

    //if( MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
    if( s_XC_bIVfStable == FALSE )
    {
        printf(" [XC][CurIVf=%u]", s_XC_u16CurIVf);
    }

    if( s_XC_u16CurIVf > s_XC_u16LastIVf )
        u16iVfDiff = s_XC_u16CurIVf - s_XC_u16LastIVf;
    else
        u16iVfDiff = s_XC_u16LastIVf - s_XC_u16CurIVf;

    if( u16iVfDiff <= 5 )
    {
        if( s_XC_u8IVfStableCnt < 255 )
            s_XC_u8IVfStableCnt += 1;

        if( s_XC_bIVfStable == FALSE )
        {
            if( s_XC_u8IVfStableCnt > 11 )
            {
                s_XC_bIVfStable = TRUE;
                printf("[XC] iVf=%u stable at %u,%u\n", s_XC_u16CurIVf, g_Debug_u32Time_ChangeChannel, MsOS_GetSystemTime());
            }
        }
    }
    else
    {
        //if( s_XC_bIVfStable )
        {
            s_XC_bIVfStable = FALSE;
            printf("[XC] iVf=%u->%u unstable at %u,%u\n", s_XC_u16LastIVf, s_XC_u16CurIVf, g_Debug_u32Time_ChangeChannel, MsOS_GetSystemTime());
        }

        s_XC_u16LastIVf = s_XC_u16CurIVf;
        s_XC_u8IVfStableCnt = 0;
    }

}

#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY) ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA))
MS_BOOL _Hal_tmds_GetClockValidFlag(MS_BOOL bCheckClockStable);
#endif
#if 1//( DEBUG_XC_HDMI_DE)
void MApi_XC_Sys_Monitor_HDMI_Status(void)
{
    E_MUX_INPUTPORT enHDMIPort = MApi_XC_Mux_GetHDMIPort(stSystemInfo[MAIN_WINDOW].enInputSourceType);
    //printf("enHDMIPort=%u\n", enHDMIPort);

    UNUSED(enHDMIPort);

#if 0
    static U8 s_HDMI_u8ClockStable_Last = 0xFF;
    MS_BOOL bCurClockStable = _Hal_tmds_GetClockValidFlag(0);

    if( bCurClockStable != s_HDMI_u8ClockStable_Last )
    {
        printf("[HDMI] Clock Stable = %u at %u\n", bCurClockStable, MsOS_GetSystemTime());

    #if(DEBUG_CHG_SRC_TIME)
        if( bCurClockStable )
        {
            msDebug_PrintChgSrcTime("[HDMI] DE Clock = 1");
        }
        else
        {
            msDebug_PrintChgSrcTime("[HDMI] DE Clock = 0");
        }
    #endif

        s_HDMI_u8ClockStable_Last = bCurClockStable;
    }
#endif

#if 0 // Check HDMI DE
    static U8 s_HDMI_u8DEStable_Last = 0xFF;
    MS_BOOL bCurDEStable = MDrv_HDMI_GetDEStableStatus(enHDMIPort);

    if( bCurDEStable != s_HDMI_u8DEStable_Last )
    {
        printf("[HDMI] DE Stable = %u at %u\n", bCurDEStable, MsOS_GetSystemTime());

    #if(DEBUG_CHG_SRC_TIME)
        if( bCurDEStable )
        {
            msDebug_PrintChgSrcTime("[HDMI] DE Stable = 1");
        }
        else
        {
            msDebug_PrintChgSrcTime("[HDMI] DE Stable = 0");
        }
    #endif

        s_HDMI_u8DEStable_Last = bCurDEStable;
    }
#endif

#if 1 // Check DE window
    static MS_WINDOW_TYPE s_stDEWin_Last={0,0,0,0};
    MS_WINDOW_TYPE stCurDEWin;

    MApi_XC_GetDEWindow(&stCurDEWin, MAIN_WINDOW);

    if( memcmp( &stCurDEWin, &s_stDEWin_Last, sizeof(MS_WINDOW_TYPE) ) != 0 )
    {
        //printf("DE Win changed\n");
        printf("DE Win changed: w,h,x,y=%u,%u,%u,%u\n",
                stCurDEWin.width, stCurDEWin.height,
                stCurDEWin.x, stCurDEWin.y);
    }
    s_stDEWin_Last = stCurDEWin;
#endif


#if 0 // Check HDCP status
    static U16 s_HDCP_u16Status_Last = 0xFFFF;
    U16 s_HDCP_u16Status = MDrv_Read2Byte(0x171202);

    if( s_HDCP_u16Status != s_HDCP_u16Status_Last )
    {
        printf("[HDCP] status = 0x%X at %u\n", s_HDCP_u16Status, MsOS_GetSystemTime());

    #if(DEBUG_CHG_SRC_TIME)
        if( s_HDCP_u16Status&BIT13 )
        {
            msDebug_PrintChgSrcTime("[HDCP] Ri = 1\n");
        }
    #endif

        s_HDCP_u16Status_Last = s_HDCP_u16Status;
    }
#endif

}
#endif

void MApi_XC_Sys_Monitor_VTotal(void)
{
    static U16 s_XC_u16LastVT = 0;
    static U16 s_XC_u16CurVT = 0;
    static U8 s_XC_u8VTStableCnt = 0;
    static BOOL s_XC_bVTStable = 0;

    s_XC_u16CurVT = MApi_XC_R2BYTE(0x013E);

    if( s_XC_u16CurVT == s_XC_u16LastVT )
    {
        if( s_XC_u8VTStableCnt < 255 )
            s_XC_u8VTStableCnt += 1;

        if( s_XC_bVTStable == FALSE )
        {
            if( s_XC_u8VTStableCnt > 12 )
            {
                s_XC_bVTStable = TRUE;
                printf("[XC] VT=%u stable at %u,%u\n", s_XC_u16CurVT, g_Debug_u32Time_ChangeChannel, MsOS_GetSystemTime());
            }
        }
    }
    else
    {
        //if( s_XC_bVTStable )
        {
            s_XC_bVTStable = FALSE;
            printf("[XC] VT=%u->%u unstable at %u,%u\n", s_XC_u16LastVT, s_XC_u16CurVT, g_Debug_u32Time_ChangeChannel, MsOS_GetSystemTime());
        }
        s_XC_u16LastVT = s_XC_u16CurVT;
        s_XC_u8VTStableCnt = 0;
    }
}


#define DEBUG_XC_VTOTAL     0
#define DEBUG_XC_VFREQ      0
#define DEBUG_XC_HP_SYNC    0

#define DEBUG_XC_HDMI_DE    0

#define DEBUG_XC_FRAME_COUNT    0
void MApi_XC_Sys_Task(void)
{
    static U32 s_XC_Sys_Task_LastTime = 0;


#if( ENABLE_DEBUG_FILM )
    MDrv_PQ_Film_Print_Info();
#endif

    if( msAPI_Timer_DiffTime_2(s_XC_Sys_Task_LastTime, MsOS_GetSystemTime()) < 5 )
    {
        return;
    }

    s_XC_Sys_Task_LastTime = MsOS_GetSystemTime();


    if( IsDigitalSourceInUse() )
    {
        return ;
    }

//=====================================================================================
#if(DEBUG_XC_VTOTAL)
    MApi_XC_Sys_Monitor_VTotal();
#endif
//=====================================================================================

#if(DEBUG_XC_VFREQ)
    MApi_XC_Sys_Task_InVF();
#endif

//=====================================================================================
#if DEBUG_XC_HP_SYNC
    {
        XC_IP_SYNC_STATUS stXC_Sync_Status;
        static XC_IP_SYNC_STATUS s_stXC_Sync_Status_Last;

        MApi_XC_GetSyncStatus(INPUT_SOURCE_HDMI, &stXC_Sync_Status, MAIN_WINDOW);

        if( stXC_Sync_Status.u16Hperiod != s_stXC_Sync_Status_Last.u16Hperiod
         || stXC_Sync_Status.u16Vtotal != s_stXC_Sync_Status_Last.u16Vtotal
         || stXC_Sync_Status.u8SyncStatus != s_stXC_Sync_Status_Last.u8SyncStatus
          )
        {
            msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
            msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);

            printf("[XC Sync] HP=0x%X, VT=%u, sync=0x%X\n",
                stXC_Sync_Status.u16Hperiod, stXC_Sync_Status.u16Vtotal, stXC_Sync_Status.u8SyncStatus);

            msDebug_ANSI_AllAttrOffText();
        }

        s_stXC_Sync_Status_Last = stXC_Sync_Status;
    }
#endif

#if( DEBUG_XC_FRAME_COUNT )
    MApi_XC_Sys_CheckFrameCount();
#endif

#if( DEBUG_XC_HDMI_DE)
    MApi_XC_Sys_Monitor_HDMI_Status();
#endif
}

void MApi_XC_PrintSyncStatus(void)
{
    printf(" VT=%u,", MApi_XC_R2BYTE(0x013E));

    {
        printf(" IVf=%u", MApi_XC_Sys_Get_Fpll_InVFreq() );
    }

    {
        printf(" OVf=%u at %u\n", MApi_XC_Sys_Get_Fpll_OutVFreq(), g_Debug_u32Time_ChangeChannel);
    }
}

#if( CONTROL_DNR_BUF_RULE_2015 )
#define DEBUG_XC_FB(x)  x
void MApi_XC_SetupFrameBuffer(void)
{
    INPUT_SOURCE_TYPE_t eInputSource = SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW);
    U32 u32MainAddr;
    U32 u32MainSize;


    DEBUG_XC_FB( printf("MApi_XC_SetupFrameBuffer(src=%u)\n", eInputSource); );

//#if ( defined(SUPPORT_MPEG2_SD_ONLY) )
//    No use!!
//#endif

    TIMER_SET_DELAY_ID_START(E_DELAY_ID_DRV_XC_SET_FB);

    if( IsSrcTypeDTV( eInputSource ) ) // DTV
    {
    #if( defined(SCALER_DNR_BUF_DTV_ADR) && (SCALER_DNR_BUF_DTV_LEN > 0) )
        DEBUG_XC_FB( printf("=> XC-Main = SCALER_DNR_BUF_DTV\n"); );
        u32MainAddr = ((SCALER_DNR_BUF_DTV_MEMORY_TYPE& MIU1) ? (SCALER_DNR_BUF_DTV_ADR| MIU_INTERVAL) : (SCALER_DNR_BUF_DTV_ADR));
        u32MainSize = SCALER_DNR_BUF_DTV_LEN;
    #else
        DEBUG_XC_FB( printf("=> XC-Main = SCALER_DNR_BUF\n"); );
        u32MainAddr = ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR));
        u32MainSize = SCALER_DNR_BUF_LEN;
    #endif

        // Set to driver
        MApi_XC_SetFrameBufferAddress( u32MainAddr, u32MainSize, MAIN_WINDOW);
    }
    else if( IsSrcTypeStorage(eInputSource)) // MM
    {
    #if( defined(SCALER_DNR_BUF_PREV_ADR)&&(SCALER_DNR_BUF_PREV_LEN>0)  )
        DEBUG_XC_FB( printf("=> XC-Main = SCALER_DNR_BUF_PREV\n"); );
        u32MainAddr = ((SCALER_DNR_BUF_PREV_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_PREV_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_PREV_ADR));
        u32MainSize = SCALER_DNR_BUF_PREV_LEN;
    #else
        DEBUG_XC_FB( printf("=> XC-Main = SCALER_DNR_BUF\n"); );
        u32MainAddr = ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR));
        u32MainSize = SCALER_DNR_BUF_LEN;
    #endif

        MApi_XC_SetFrameBufferAddress( u32MainAddr, u32MainSize, MAIN_WINDOW);

        // Set sub window: Use same buf with Main
    #if ENABLE_3D_PROCESS
        DEBUG_XC_FB( printf("=> XC-Sub = XC-Main\n"); );
        MApi_XC_SetFrameBufferAddress( u32MainAddr, u32MainSize, SUB_WINDOW);
    #endif
    }
#if( defined(SCALER_HDMI_4K_ADR) && (SCALER_HDMI_4K_LEN > 0) )
    else if( IsSrcTypeHDMI( eInputSource ) )
    {
        DEBUG_XC_FB( printf("=> XC-Main = SCALER_HDMI_4K_ADR\n"); );
        u32MainAddr = ((SCALER_HDMI_4K_MEMORY_TYPE & MIU1) ? (SCALER_HDMI_4K_ADR | MIU_INTERVAL) : (SCALER_HDMI_4K_ADR));
        u32MainSize = SCALER_HDMI_4K_LEN;
        MApi_XC_SetFrameBufferAddress( u32MainAddr, u32MainSize, MAIN_WINDOW);

        // Set sub window: Use same buf with Main
    #if ENABLE_3D_PROCESS
        DEBUG_XC_FB( printf("=> XC-Sub = XC-Main\n"); );
        MApi_XC_SetFrameBufferAddress( u32MainAddr, u32MainSize, SUB_WINDOW);
    #endif
    }
#endif
    else
    {
    #if( defined(SCALER_FB_NO_VDEC_ADR)&&(SCALER_FB_NO_VDEC_LEN>0) )
        DEBUG_XC_FB( printf("=> XC-Main = SCALER_FB_NO_VDEC\n"); );
        u32MainAddr = ((SCALER_FB_NO_VDEC_MEMORY_TYPE & MIU1) ? (SCALER_FB_NO_VDEC_ADR | MIU_INTERVAL) : (SCALER_FB_NO_VDEC_ADR));
        u32MainSize = SCALER_FB_NO_VDEC_LEN;
    #else
        DEBUG_XC_FB( printf("=> XC-Main = SCALER_DNR_BUF\n"); );
        u32MainAddr = ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR));
        u32MainSize = SCALER_DNR_BUF_LEN;
    #endif
        MApi_XC_SetFrameBufferAddress( u32MainAddr, u32MainSize, MAIN_WINDOW);

        // Set sub window: Use same buf with Main
    #if ENABLE_3D_PROCESS
        DEBUG_XC_FB( printf("=> XC-Sub = XC-Main\n"); );
        MApi_XC_SetFrameBufferAddress( u32MainAddr, u32MainSize, SUB_WINDOW);
    #endif
    }

    DEBUG_XC_FB( printf(" u32MainAddr=0x%X, u32MainSize=0x%X\n", u32MainAddr, u32MainSize ); );

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)
    U32 u32Addr = MApi_XC_R4BYTE(0x1210);
    u32Addr = u32Addr * 16;
    DEBUG_XC_FB( printf(" ==> XC-VIP addr=0x%X\n", u32Addr ); );
#endif

    // Set sub window
#if (ENABLE_PIP)
  #if( defined(SCALER_DNR_SUB_BUF_ADR)&&(SCALER_DNR_SUB_BUF_LEN>0) )
    DEBUG_XC_FB( printf("=> XC-Sub = SCALER_DNR_SUB_BUF\n"); );
    MApi_XC_SetFrameBufferAddress(((SCALER_DNR_SUB_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_SUB_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_SUB_BUF_ADR)), SCALER_DNR_SUB_BUF_LEN, SUB_WINDOW);
  #endif
#endif

    TIMER_SET_DELAY_ID_END();
}
#endif

#if (ENABLE_DOLBY_BULLETIN24)
void MApi_XC_UpdateEDID(BOOLEAN bIsType2Edid, U8* pu8DdpSAD)
{
    printf("%s(%u)\n", __FUNCTION__, bIsType2Edid);

    if (bIsType2Edid == TRUE) // With DD+
    {
        MApp_Edid_Set_EnableAudioDDP(ENABLE, pu8DdpSAD);
    }
    else // Without DD+
    {
        MApp_Edid_Set_EnableAudioDDP(DISABLE, pu8DdpSAD);
    }

    _MApi_XC_DDCRam_Init(E_XC_DDC_INIT_ALL_HDMI, 0);


    // Reset current port Hot plug
    MApi_XC_HPD_Do_Reset(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
}
#endif

U8 MApi_XC_Sys_Get_HDMIIndex(INPUT_SOURCE_TYPE_t enInputSourceType)
{
    U8 u8HdmiIdx = 0xFF;

    switch(enInputSourceType)
    {
        default:
        case INPUT_SOURCE_HDMI:
            u8HdmiIdx = 0;
            break;

        case INPUT_SOURCE_HDMI2:
            u8HdmiIdx = 1;
            break;

        case INPUT_SOURCE_HDMI3:
            u8HdmiIdx = 2;
            break;

        case INPUT_SOURCE_HDMI4:
            u8HdmiIdx = 3;
            break;
    }

    return u8HdmiIdx;
}

#if( ENABLE_EDID_SWITCH)
E_USER_HDMI_EDID_SEL MApi_XC_Sys_Get_UserEdidSel(void)
{
#if 0 // Test
    return E_USER_HDMI_EDID_AUTO;
#else
    INPUT_SOURCE_TYPE_t enInputSourceType = stSystemInfo[MAIN_WINDOW].enInputSourceType;

    U8 u8HdmiIdx = MApi_XC_Sys_Get_HDMIIndex(enInputSourceType);

    if( u8HdmiIdx >= HDMI_PORT_NUM_MAX )
        return E_USER_HDMI_EDID_1p4;

    if( stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[u8HdmiIdx] >= E_USER_HDMI_EDID_UNKNOWN )
        stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[u8HdmiIdx] = E_USER_HDMI_EDID_1p4;

    return stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[u8HdmiIdx];
#endif
}

E_USER_HDMI_EDID_SEL MApi_XC_Sys_Set_UserEdidSel(E_USER_HDMI_EDID_SEL eHDMI_Edid_Sel)
{
    if( eHDMI_Edid_Sel >= E_USER_HDMI_EDID_UNKNOWN )
        return E_USER_HDMI_EDID_1p4;

    INPUT_SOURCE_TYPE_t enInputSourceType = stSystemInfo[MAIN_WINDOW].enInputSourceType;

    U8 u8HdmiIdx = MApi_XC_Sys_Get_HDMIIndex(enInputSourceType);

    if( u8HdmiIdx >= HDMI_PORT_NUM_MAX )
        return E_USER_HDMI_EDID_1p4;

    stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[u8HdmiIdx] = eHDMI_Edid_Sel;

    return stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[u8HdmiIdx];
}

void MApi_XC_Sys_Set_EdidSel( INPUT_SOURCE_TYPE_t enInputSourceType, EnuXcHdmiEdidSel eEdidSel )
{
    U8 u8HdmiIdx = MApi_XC_Sys_Get_HDMIIndex(enInputSourceType);

    if( u8HdmiIdx >= HDMI_PORT_NUM_MAX )
        return;

    g_XC_Sys_au8EdidSel[u8HdmiIdx] = eEdidSel;
}

void MApi_XC_Sys_Reload_Edid(INPUT_SOURCE_TYPE_t enInputSourceType, EnuXcHdmiEdidSel eEdidSel, BOOL bResetHPD)
{
#define DANIEL_TEST 0

    //PRINT_CURRENT_LINE();
//    DEBUG_EDID_SWITCH( printf("MApi_XC_Sys_Reload_Edid(u8Edid=%u)\n", u8Edid); );
    printf("MApi_XC_Sys_Reload_Edid(Src=%u, eEdidSel=%u, bResetHPD=%u)\n", enInputSourceType, eEdidSel, bResetHPD);

    U8 u8HdmiIdx = MApi_XC_Sys_Get_HDMIIndex(enInputSourceType);

    if( u8HdmiIdx >= HDMI_PORT_NUM_MAX )
        return;

#if( !ENABLE_HDMI_HPD_TASK )
    E_MUX_INPUTPORT enHDMIPort = MApi_XC_Mux_GetHDMIPort(enInputSourceType);
#endif

/*
    if( bResetHPD )
    {
    #if(ENABLE_HDMI_HPD_TASK )
        // Do thing
    #else
        if( msAPI_CEC_Is_CecTurnOn() )
        {
            // Disable HPD
            DEBUG_EDID_SWITCH( printf("Set HPD = 0\n"); );
            MApi_XC_Sys_SetHPD( DISABLE, enHDMIPort);
        }
    #endif
    }
    */

    MApi_XC_Sys_Set_EdidSel(enInputSourceType, eEdidSel);

    _MApi_XC_DDCRam_Init(E_XC_DDC_INIT_SRC_HDMI, u8HdmiIdx);

    if( bResetHPD )
    {
        MApi_XC_HPD_Do_Reset(enInputSourceType);
    /*
    #if(ENABLE_HDMI_HPD_TASK )
        {
            MApi_XC_HPD_Task_Start(enInputSourceType, E_HPD_TASK_FOR_CHANGE_SRC);  //Enable state machine flow
        }
    #else
        MsOS_DelayTask( HDMI_HPD_DELAY);

        // Enable HPD
        DEBUG_EDID_SWITCH( printf("Set HPD = 1\n"); );
        MApi_XC_Sys_SetHPD( ENABLE, enHDMIPort);
    #endif
    */
    }
}
#endif

#if(CHIP_FAMILY_MILAN == CHIP_FAMILY_MILAN)
void MDrv_XC_Reset_WBank(void)
{
#if 1// _FIELD_PACKING_MODE_SUPPORTED //new SCMI mech

    printf(" MDrv_XC_Reset_WBank()\n");

    //if(eWindow ==MAIN_WINDOW )
    {
        //printf("REG_SC_BK12_05_L=0x%X\n", MApi_XC_R2BYTE(REG_SC_BK12_05_L) );

        MApi_XC_W2BYTEMSK( REG_SC_BK12_05_L, BIT(7), BIT(7) );
        //MsOS_DelayTask(1);
        msAPI_Timer_Delayms_2(1, E_DELAY_ID_XC_SYS);
        //printf("REG_SC_BK12_05_L=0x%X\n", MApi_XC_R2BYTE(REG_SC_BK12_05_L) );

        MApi_XC_W2BYTEMSK( REG_SC_BK12_05_L, 0, BIT(7) );
        //MsOS_DelayTask(1);
        msAPI_Timer_Delayms_2(1, E_DELAY_ID_XC_SYS);
        //printf("REG_SC_BK12_05_L=0x%X\n", MApi_XC_R2BYTE(REG_SC_BK12_05_L) );
    }
    /*else
    {
        SC_W2BYTEMSK( REG_SC_BK12_45_L, BIT(7), BIT(7) );
        MsOS_DelayTask(1);
        SC_W2BYTEMSK( REG_SC_BK12_45_L, 0, BIT(7) );
        MsOS_DelayTask(1);
    }*/
#endif

}
#endif

void MApi_XC_Sys_CheckFrameCount(void)
{
    U8 u8Reg_SC_0104_Val = MApi_XC_R2BYTE(0x0104);
    if( (u8Reg_SC_0104_Val&0x80) ) // InputSource Disable =1
    {
    //    return ;
    }

    U8 u8FrameCount = MHAL_XC_Get_FrameCount();
    U8 u8XC_1274_Val = MApi_XC_R2BYTE(0x1274);
    U8 u8WriteIdx = u8XC_1274_Val&0x0F;
    U8 u8ReadIdx = u8XC_1274_Val>>4;

    if( (u8WriteIdx >= u8FrameCount) || (u8ReadIdx >= u8FrameCount) )
    {
        msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
        msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);

        printf("\nWarning: Frame index is invalid: C%u, W%u, R%u\n", u8FrameCount, u8WriteIdx, u8ReadIdx);

        // If Write bank is invalid, Reset it
        if(u8WriteIdx > u8FrameCount)
        {
            // Reset W Bank
        #if(CHIP_FAMILY_MILAN == CHIP_FAMILY_MILAN)
            MDrv_XC_Reset_WBank();
        #endif
        }

        msDebug_ANSI_AllAttrOffText();
    }

}

BOOL MApi_XC_Sys_Is_SupportImmSwitch(void)
{
    XC_INITMISC stXC_Init_Misc;

    MApi_XC_GetMISCStatus(&stXC_Init_Misc);

    if( stXC_Init_Misc.u32MISC_A & E_XC_INIT_MISC_A_IMMESWITCH )
    {
        return TRUE;
    }

    return FALSE;
}

void MApi_XC_Sys_ResetDVIPort(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE)
{
//  MDrv_DVI_Software_Reset() is not supported in Euler, Nasa
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)    \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)     \
   )

    UNUSED(enINPUT_SOURCE_TYPE);

#else
/*
#elif ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)     \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)  \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)     \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)   \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)   \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)   \
    )
*/
    U8 u8port_count = 0;
    E_MUX_INPUTPORT eInputPort = INPUT_PORT_NONE_PORT;

    _MApi_XC_Sys_InputSource_InputPort_Mapping(enINPUT_SOURCE_TYPE, &eInputPort, &u8port_count);

    if( u8port_count > 0 )
    {
        printf(">> MDrv_DVI_Software_Reset(eInputPort=%u, BIT5)\n", eInputPort);
        MDrv_DVI_Software_Reset(eInputPort, BIT5);
    }

#endif
}

void MApi_XC_Sys_CheckMuteStatus(void)
{
    // Check black video
    if( msAPI_Scaler_GetScreenMute(MAIN_WINDOW) )
    {
        //printf(" s_eScreenMuteStatus[0]=0x%X\n", msAPI_Scaler_GetScreenMute(MAIN_WINDOW));
        //msAPI_Scaler_PrintMuteClient(MAIN_WINDOW); //MP333 
    }
    else
    {
        if( MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
        {
            printf("XC BlackVideo=1\n");
        }
    }

    // Check disable inputsource ...
    if( MApi_XC_Sys_Get_BlueScreenStatus(MAIN_WINDOW) )
    {
        // Do nothing
    }
    else
    {
        if( MApi_XC_IsInputSourceDisabled(MAIN_WINDOW) )
        {
            // !! This case means "InputSourceDisable" is not set by blue screen!!
            // Maybe is cause by some HW function...
            printf("XC InputSourceDisabled=1\n");

            // Check XC IP auto no signal...
            if( MHAL_XC_Get_IPAutoNoSignalEn(MAIN_WINDOW) )
            {
                printf(" XC IPAutoNoSignal=1\n");
            }

            // Check HDMI AV mute ...
            if( IsHDMIInUse() )
            {
                printf(" XC EnAvMuteDetect=%u\n", MHAL_XC_Get_IPHdmiAvMuteDetect(MAIN_WINDOW) );
                printf(" HDMI EnAvMute=0x%X\n", MHAL_HDMI_Get_EnAvMute());
                printf(" HDMI AVMUTE Received=%u\n", MHAL_HDMI_Get_AvMuteReceivedStatus());
            }
        }
    }

    // Is HDMI
    if( IsHDMIInUse() )
    {
        if( MHAL_HDMI_Get_AvMuteReceivedStatus() )
        {
            printf(" HDMI AVMUTE Received=%u\n", MHAL_HDMI_Get_AvMuteReceivedStatus());
            printf(" HDMI EnAvMute=0x%X\n", MHAL_HDMI_Get_EnAvMute());
        }
    }

}

#if 0 // This function is not good enough!!
#if( (CHIP_FAMILY_MILAN == CHIP_FAMILY_WHISKY)  \
   ||(CHIP_FAMILY_MILAN == CHIP_FAMILY_MAYA)    \
   ||(CHIP_FAMILY_MILAN == CHIP_FAMILY_MELODY)  \
   )
    #define EN_CHECK_HDMI_DE_STABLE 1
#else
    #define EN_CHECK_HDMI_DE_STABLE 0
#endif

BOOLEAN MApi_XC_HDMI_CheckTimingStable( SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t enInputSourceType, MS_WINDOW_TYPE *pstDEWin)
{
    if( !IsSrcTypeHDMI(enInputSourceType) )
    {
        return TRUE;
    }

    BOOLEAN bResult = TRUE;

    if( pstDEWin )
    {
        memset( pstDEWin, 0, sizeof(MS_WINDOW_TYPE) );
    }


 #if(EN_CHECK_HDMI_DE_STABLE)   // Check HDMI DE Stable
    E_MUX_INPUTPORT enHDMIPort = MApi_XC_Mux_GetHDMIPort(enInputSourceType);
    BOOLEAN bHdmiDEStable = MDrv_HDMI_GetDEStableStatus(enHDMIPort);

    if( !bHdmiDEStable )
    {
        printf("HDMI(%u) DE unstable!\n", enHDMIPort);
        return FALSE;
    }
  #endif

    if (MApi_XC_GetHdmiSyncMode() == HDMI_SYNC_DE)
    {
        printf("HDMI DE mode\n");

        MS_WINDOW_TYPE stCurDEWin;
        MApi_XC_GetDEWindow(&stCurDEWin, eWindow);

        printf("DE win: w,h,x,y=%u,%u,%u,%u\n",
                stCurDEWin.width, stCurDEWin.height,
                stCurDEWin.x, stCurDEWin.y);

        // Check H size
        if( stCurDEWin.width < 600 )
        {
            printf("\nError: DE H size=%u\n", stCurDEWin.width);
            bResult = FALSE;
        }
        // Check V size
        if( stCurDEWin.height < 400 )
        {
            printf("\nError: DE V size=%u\n", stCurDEWin.height);
            bResult = FALSE;
        }

    #if (CHIP_FAMILY_MILAN == CHIP_FAMILY_WHISKY) // todo: Check size with HDMI HW
        {
            // Add function for it
            U16 u16HdmiReport_HSize = MDrv_Read2Byte(0x1027CA);
            printf("u16HdmiReport_HSize=%u\n", u16HdmiReport_HSize);

            if( (stCurDEWin.width == 720)&&(u16HdmiReport_HSize==1440) )
            {
                // It's 480i
            }
            else
            {
                U16 u16Diff;
                if( u16HdmiReport_HSize > stCurDEWin.width )
                    u16Diff = u16HdmiReport_HSize - stCurDEWin.width;
                else
                    u16Diff = stCurDEWin.width - u16HdmiReport_HSize;

                //printf("u16Diff=%u\n", u16Diff);
                if( u16Diff > 2 )
                {
                    bResult = FALSE;
                    printf("DE diff=%u\n", u16Diff);
                }
            }
        }
    #endif

        if( pstDEWin )
        {
            *pstDEWin = stCurDEWin;

            printf("DE win: w,h,x,y=%u,%u,%u,%u\n",
                pstDEWin->width, pstDEWin->height,
                pstDEWin->x, pstDEWin->y);
        }
    }
    else
    {
        printf("HDMI HV mode\n");
    }

    //if( bResult )
    {
        printf("bResult => %u\n", bResult);
    }

    return bResult;
}
#endif


#undef _API_XC_SYS_C_
#endif  // _API_XC_SYS_C_

