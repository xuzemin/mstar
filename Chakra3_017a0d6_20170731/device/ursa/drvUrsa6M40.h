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
// Copyright (c) 2008 MStar Semiconductor, Inc.
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
// File Name: DrvUrsa6M40MFCAPI.h
// Description: TI I2S Audio Amplifier
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_URSA_6M40_H__
#define __DRV_URSA_6M40_H__

//*************************************************************************
//          Structures
//*************************************************************************

#include "Board.h"

#if ENABLE_6M40_4KX2K_PROCESS

#include <stdio.h>
#include <string.h>
//#include <math.h>
//#include "hwreg.h"
#include "drvIIC.h"
#include "datatype.h"
#include "MApp_GlobalSettingSt.h"


#undef INTERFACE
#ifdef DRV_URSA_6M40_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef enum
{
    IIC_DDC2BI_MODE=0,
    IIC_STD_MODE,
    IIC_DEFAULT=IIC_DDC2BI_MODE,
} EN_6M40_IIC_MODE;

typedef struct
{
    BYTE    CMDIdx0;    //0st    [3:0]->CmdIdx[11:8],[7:4]->Checksum;
    BYTE    CMDIdx1;    // 1st    [7:0]->CmdIdx[7:0]
    BYTE    CMDIdx2;    // 2nd   CMD data
    BYTE    CMDIdx3;    // 3rd   CMD data
    BYTE    CMDIdx4;    // 4th   CMD data
    BYTE    CMDIdx5;    // 5th   CMD data
    BYTE    CMDIdx6;    // 6th   CMD data
} URSA_CMD_DATA;

typedef struct
{
    U8    bsingleCh:1;
    U8    bTIMode:1;
    U8    BitNums:2;
    U8    bSwap_evenodd:1;
    U8    bSwap_pn:1;
    U8    bSwap_msblsb:1;
    U8    bTTL:1;
} URSA_CMD_INIT_IN_LVDSALL_DATA;

typedef struct
{
    U8    bTIMode:1;
    U8    bShiftPair:1;
    U8    bSwapPol:1;
    U8    bSwapPair:1;
    U8    PanelBitNums:2;
    U8    bDither8Bits:1;
    U8    bDitherEn:1;
    U8    SwapCh;
    U8    PanelType:4;
    U8    PanelChannel:4;
} URSA_CMD_INIT_OUT_ALL_1_DATA;

typedef struct
{
    U16    VTotal;
    U16    De_XStart_high:4;
    U16    HTotal:12;
    U8      De_XStart_low;
} URSA_CMD_INIT_OUT_ALL_2_DATA;

typedef struct
{
    U16    PanelHeight;
    U16    De_YStart_high:4;
    U16    PanelWidth:12;
    U8      De_YStart_low;
} URSA_CMD_INIT_OUT_ALL_3_DATA;

typedef struct
{
    U8    Reserve:3;
    U8    PanelBitNums:2;
    U8    bTIMode:1;
    U8    bLvdsSwapPol:1;
    U8    bLvdsShiftPair:1;
    U8    bLvdsSwapPair:1;
} URSA_CMD_OUT_LVDS_MODE_DATA;

typedef struct
{
    U8    LvdsSwapCh;
} URSA_CMD_OUT_LVDS_SWAP_DATA;

typedef struct
{
    U8    Reserve:4;
    U8    PanelChannel:4;
} URSA_CMD_OUT_LVDS_CHANNELTYPE_DATA;

typedef struct
{
  // 3d mode: 1->LR mode
  //               2->UD mode
  //               3->frame interleave 5x mode
 //               4->URSA4 not support
 //               5-> ACT_3DMODE_SEL_OFF,
 //               6->LR mode
 //               7->UD mode
 //               8->frame interleave 2.5x
 //               9->frame interleave 2.5x and LI
 //               0->No 3D; MEMC 240Hz
  U8    Set3Dmode:4;
  U8    Reserve:3;
  U8    bL_Only:1;
} URSA_CMD_3D_MODE_DATA;

typedef struct
{
  U8    u8OffSet;          // sight depth
  U8    bEnable2Dto3D:1;   // enable 2D to 3D
  U8    bEnableConcave:1;  //enable for passive output
  U8    u8Gain:4;
} URSA_CMD_2D_TO_3D_DATA;

typedef struct
{
   //MFC_LEVEL_OFF  = 0,
   //MFC_LEVEL_LOW  = 1,
   //MFC_LEVEL_MID  = 2,
   //MFC_LEVEL_HIGH = 3,
   //MFC_LEVEL_55   = 4,
   //MFC_LEVEL_USER = 5,
   //MFC_LEVEL_3D      = 0x0A,
   //MFC_LEVEL_RGB_BYPASS  = 0x0F,
   U8    MFClevel;
} URSA_CMD_MFC_LEVEL_DATA;

/// to define mfc Demo mode.
typedef struct
{
   //MFC_DEMO_OFF    0x0
   //MFC_DEMO_LR      0x1
   //MFC_DEMO_UD      0x2
   U8    MFCDemoMode;

} URSA_CMD_MFC_DEMO_MODE_DATA;

typedef struct
{
  U8    Reserve:7;
  U8    bMute:1;
} URSA_CMD_VIDEO_MUTE_DATA;

typedef struct
{
  U8    AdjustIdx;
  U16  wAdjustValue;
} URSA_CMD_GAIN_OFFSET_DATA;

typedef struct
{
  U8    Reserve:4;
  U8    WinID:3;
  U8    bWinEn:1;
  U16  WinHStart;
  U16  WinHEnd;
} URSA_CMD_OSD_WINDOWS_H_DATA;

typedef struct
{
  U8    Reserve:4;
  U8    WinID:3;
  U8    bWinEn:1;
  U16  WinVStart;
  U16  WinVEnd;
} URSA_CMD_OSD_WINDOWS_V_DATA;

typedef struct
{
  U8    Reserve:4;
  U8    PwmCH:4;
  U16  PwmDuty;
  U16  PwmPhase;
} URSA_CMD_DUTY_PHASE_DATA;

typedef struct
{
  U8    Reserve:7;
  U8    bOnOff:1;
} URSA_CMD_MOD_POWER_DATA;

typedef struct
{
      URSA_CMD_INIT_IN_LVDSALL_DATA   g_InitInLvdsAll;
      URSA_CMD_INIT_OUT_ALL_1_DATA   g_InitOutAll1;
      URSA_CMD_INIT_OUT_ALL_2_DATA   g_InitOutAll2;
      URSA_CMD_INIT_OUT_ALL_3_DATA   g_InitOutAll3;
      URSA_CMD_OUT_LVDS_MODE_DATA   g_OutLvdsMode;
      URSA_CMD_OUT_LVDS_SWAP_DATA   g_OutLvdsSwap;
      URSA_CMD_OUT_LVDS_CHANNELTYPE_DATA   g_OutLvdsChannelType;
      URSA_CMD_3D_MODE_DATA   g_3DMode;
      URSA_CMD_2D_TO_3D_DATA   st2Dto3D;
      URSA_CMD_MFC_LEVEL_DATA   g_MFCLevel;
      URSA_CMD_VIDEO_MUTE_DATA   g_VideoMute;
      URSA_CMD_GAIN_OFFSET_DATA   g_GainOffset;
      URSA_CMD_OSD_WINDOWS_H_DATA   g_OSDWinH;
      URSA_CMD_OSD_WINDOWS_V_DATA   g_OSDWinV;
      URSA_CMD_DUTY_PHASE_DATA   g_PwmDutyPhase;
      URSA_CMD_MOD_POWER_DATA   g_ModPower;
      URSA_CMD_MFC_DEMO_MODE_DATA stMFCDemoMode;
} URSA_CMD_GEN_SETTINGS;

//CMD Index table
typedef enum
{
      UC_INIT_IN_ALL,//0x0001,
      UC_INIT_FINISH,//0x0100,
      UC_SET_IN_LVDS_MODE,//0x0101,
      UC_SET_IN_LVDS_SWAP,//0x0102,
      UC_SET_IN_LVDS_TTL,//0x0103,
      UC_INIT_OUT_ALL_1,//0x0010,
      UC_INIT_OUT_ALL_2,//0x0011,
      UC_INIT_OUT_ALL_3,//0x0012,
      UC_SET_OUT_LVDS_MODE,//0x0201,
      UC_SET_OUT_LVDS_SWAP,//0x0202,
      UC_SET_OUT_LVDS_CHANNELTYPE,//0x0203,
      //==3D mode CMD===
      UC_SET_3DMODE ,//0x0301, //No 3D; MEMC 240Hz
      //==MFC level CMD ==
      UC_SET_MFC_LEVEL ,//0x0302,
      //==video mute/on CMD ==
      UC_SET_VIDEO_MUTE,//0x0303,
      UC_SET_GAIN_OFFSET,// 0x0304,
      UC_SET_OSD_WINDOWS_H,//0x0305,
      UC_SET_OSD_WINDOWS_V,//0x0306,
      UC_SET_PWM_DUTY_PHASE,// 0x3070,
      UC_SET_MOD_POWER,// 0x3080,
      UC_SET_2D_TO_3D_MODE,//  0x30A0
      UC_SET_VIDEO_FREEZE,//  0x031D
      //==MFC DEMO CMD ==
      UC_SET_MFC_DEMO_MOD,// 0x0501
      UC_SET_LVDS_ON,    //0x not sure, reserved for enum declare
      UC_SET_LVDS_OFF,   //0x not sure, reserved for enum declare
      //== Add Ursa 7 command
      UC_SET_RX_SWITCH_TO_HDMI,// 0x0103
      UC_SET_RX_OSD_ENABLE, //0x0104
      UC_SET_IN_VIDEO_SIZE, //0x0105
      UC_SET_ACE_SHARPNESS,//0x0801
      UC_SET_ACE_BRIGHTNESS,//0x0802
      UC_SET_ACE_CONTRAST,//0x0803
      UC_SET_ACE_HUE,//0x0804
      UC_SET_ACE_SATURATION,//0x0805
      UC_SET_ACE_COLOR_TEMP_PARAM,//0x0806
      UC_SET_ACE_COLOR_TEMP_LOAD,//0x0807
      UC_SET_ACE_DLC,//0x0808
      UC_SET_OSD_VIDEO_CHANNEL_EXCHANGE, //0x0809
      UC_SET_MUTE, //0x0810
      UC_SET_VIDEO_OSD_FREEZE, //0x0812
      UC_SET_SR_DEMO_MODE, //0x0813
      UC_SET_ACE_LEVEL_NR,//0x0901
      UC_SET_GAMMA, //0X0814
      UC_SET_LVDS_SWING,//0x0815

      //MFC command end.
      UC_MFC_END, // UC Type index Max
      UC_SET_4K2K_MODE,
      UC_GET_4K2K_MODE,
      UC_SET_PHOTO_BYPASS_ENABLE,
      UC_SET_PHOTO_BYPASS_DISABLE,
      UC_ENABLE_3D_AUTO_DETECT,
      UC_DISABLE_3D_AUTO_DETECT,
      UC_GET_3D_AUTO_DETECTED_FORMAT,
      UC_SET_2DTO3DOFF,
      UC_2DTO3D_GAIN_OR_LRSWAP,

      //universal cmd
      UC_SET_HDCP_KEY,
UC_SET_CMDTYPE_END, // UC Type index Max
}UC_CMD_TYPE;
typedef enum
{
    E_URSA_4K2K_MODE_FULLHD,  // full HD mode
    E_URSA_4K2K_MODE_4K1K,  //MM 4k1k
    E_URSA_4K2K_MODE_4K2K,  // MM 4k2k
    E_URSA_4K2K_MODE_HDMI4K2K,  // HDMI 4k2k
    E_URSA_4K2K_MODE_UNDEFINED,  // undefine MODE

}EN_URSA_4K2K_MODE;
typedef enum
{
    EN_6M40_MEMC_OFF,
    EN_6M40_MEMC_LOW,
    EN_6M40_MEMC_MIDDLE,
    EN_6M40_MEMC_HIGH ,
    EN_6M40_MEMC_DEFAULT=EN_6M40_MEMC_MIDDLE,
}EN_6M40_MEMC_LEVEL;

typedef enum
{
    EN_6M40_NR_OFF,
    EN_6M40_NR_LOW,
    EN_6M40_NR_MIDDLE,
    EN_6M40_NR_HIGH ,
    EN_6M40_NR_DEFAULT=EN_6M40_NR_MIDDLE,
}EN_6M40_PQ_NR_LEVEL;

typedef enum
{
    EN_6M40_PWM_CH0,
    EN_6M40_PWM_CH1,
    EN_6M40_PWM_CH2,
    EN_6M40_PWM_CH3,
    EN_6M40_PWM_CH5,
}EN_6M40_CH;

typedef enum
{
    PANEL_3D_MODE_NONE,
    PANEL_3D_MODE_SIDE_BY_SIDE_2X,
    PANEL_3D_MODE_TOP_BOTTOM_2X,
    PANEL_3D_MODE_CHECK_BOARD_2X,
    PANEL_3D_MODE_FRAME_INTERLEAVE_25X,
    PANEL_3D_MODE_LINE_INTERLEAVED_2X,
    PANEL_3D_MODE_FRAME_INTERLEAVE_2X,
    PANEL_3D_MODE_720P_1XMODE,
    PANEL_3D_MODE_SIDE_BY_SIDE_24X,
    PANEL_3D_MODE_TOP_BOTTOM_24X,
    PANEL_3D_MODE_CHECK_BOARD_24X,
    PANEL_3D_MODE_LINE_INTERLEAVED_24X,
    PANEL_3D_MODE_FRAME_INTERLEAVE_24X,
    PANEL_3D_MODE_MFC_24X,
    PANEL_3D_MODE_MAXNUM,
}PANEL_3D_MODE;

typedef enum
{
    EN_VIDEO_ONLY_MUTE, // 0
    EN_VIDEO_ONLY_UNMUTE,// 1
    EN_OSD_ONLY_MUTE,// 2
    EN_OSD_ONLY_UNMUTE,// 3
    EN_ALL_MUTE,// 4
    EN_ALL_UNMUTE,// 5
    EN_MUTE_MAX,
}URSA_MUTE_TYPE;

#define  MFC_CMD_DATA_SUM   7
#define URSA_6M40_DDC2BI_MODE_ADDR      0x40
#define WIDTH_FULLHD       1920
#define HEIGHT_FULLHD      1080
#define WIDTH_4K2K         3840
#define HEIGHT_4K2K        2160
#define HEIGHT_4K1K        1080
//height 4K_ will depend on build script
#define HEIGHT_4K_     HEIGHT_4K2K
#define HDMI_HDCP_KEY_SIZE 289

//slave: 0xB4
//mster 0xB8
#define URSA_6M40_IIC_MODE_ADDR            0xB4//0xB4
#ifndef URSA_I2C_BUS_SEL
#define URSA_I2C_BUS_SEL                             E_I2C_BUS_DDCD0//
#endif

extern URSA_CMD_GEN_SETTINGS g_UrsaCMDGenSetting;

INTERFACE BOOLEAN MDrv_Ursa_6M40_3D_Cmd( UC_CMD_TYPE eCmdIdx,U8 *PU8Data);
INTERFACE BOOLEAN MDrv_Ursa_6M40_PWM_Duty_And_Phase(U8 u8PwmDuty,U16 u16PwmPhase,EN_6M40_CH ePwmCh);
INTERFACE BOOLEAN MDrv_Ursa_6M40_MFC_Level( EN_6M40_MEMC_LEVEL eMFClevel );
INTERFACE BOOLEAN MDrv_Ursa_6M40_VIDEO_Enalbe( BOOLEAN bEnable );
INTERFACE BOOLEAN MDrv_Ursa_6M40_LVDS_Enalbe( BOOLEAN bEnable );
INTERFACE BOOLEAN MDrv_Ursa_6M40_3D_MODE( PANEL_3D_MODE ePanel3DMode );
INTERFACE BOOLEAN MDrv_Ursa_6M40_Enable2Dto3D( BOOLEAN bEnable );
INTERFACE BOOLEAN MDrv_Ursa_6M40_SetHDMI_HDCP(U8 *pu8Data, U16 u16Size);
INTERFACE BOOLEAN MDrv_Ursa_6M40_Get4K2KType(U8 *pU8Data);
INTERFACE BOOLEAN MDrv_Ursa_6M40_Set4K2KType(EN_URSA_4K2K_MODE enMode);
INTERFACE void MDrv_URSA_6M40_Set_4K_2K_Mode(U8 bOnOff);
INTERFACE void MDrv_URSA_6M40_Set_Video_Freeze(U8 bOnOff);
// ====IIC code =======
INTERFACE BOOLEAN MDrv_Ursa_6M40_Set_Value(U16 u16addr, U8 u8Buf);
INTERFACE U8 MDrv_Ursa_6M40_Get_Value(U16 U16Addr, BOOLEAN bHigh);

#endif

#undef INTERFACE
#endif // __DRV_URSA_6M40_H__

