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
// File Name: drvUrsa3D6M40.c
// Description: Comunication to URSA module
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////
#define DRV_URSA_6M40_C
#include "drvUrsa6M40.h"
#include "drvIIC.h"

#if ENABLE_6M40_4KX2K_PROCESS
#define PNL_CMIV500HK1_LS6_FHD_120Hz 1
#define PNL_CMD_ADDR  0xE0
#define URSA_MSG(x)    //x

static EN_URSA_4K2K_MODE m_4K2Kmode = E_URSA_4K2K_MODE_FULLHD;

URSA_CMD_GEN_SETTINGS g_UrsaCMDGenSetting;

//ursa CMD table
static code URSA_CMD_DATA m_UrsaCmdData[] =
{
    { 0x00,  0x01,  0x00, 0x00, 0x00, 0x00, 0x00}, // UC_INIT_IN_ALL= 0x0001,
    { 0x01,  0x00,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_INIT_FINISH= 0x0100,
    { 0x01,  0x01, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_MODE= 0x0101,
    { 0x01,  0x02, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_SWAP= 0x0102,
    { 0x01,  0x03, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_TTL= 0x0103,
    { 0x00,  0x10, 0x01,  0x01,  0x01, 0x00, 0x00}, //UC_INIT_OUT_ALL_1= 0x0010,
    { 0x00,  0x11, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_INIT_OUT_ALL_2= 0x0011,
    { 0x00,  0x12, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_INIT_OUT_ALL_3= 0x0012,
    { 0x02,  0x01,  0x00,  0x00,  0x00,  0x00, 0x00}, //UC_SET_OUT_LVDS_MODE= 0x0201,
    { 0x02,  0x02,  0x00,  0x00,  0x00, 0x00, 0x00}, //UC_SET_OUT_LVDS_SWAP= 0x0202,
    { 0x02,  0x03,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_SET_OUT_LVDS_CHANNELTYPE= 0x0203,
    //==3D mode CMD===
    { 0x03,  0x01,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_SET_3DMODE = 0x0301, //No 3D; MEMC 240Hz

    //==MFC level CMD ==
    { 0x03,  0x02,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_MFC_LEVEL  = 0x0302,

    //==video mute/on CMD ==
    { 0x03,  0x03,  0x01,  0x00,  0x00,  0x00,  0x00}, //UC_SET_VIDEO_MUTE= 0x0303,

    { 0x03,  0x04,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_GAIN_OFFSET= 0x0304,
    { 0x03,  0x05,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OSD_WINDOWS_H= 0x0305,
    { 0x03,  0x06,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OSD_WINDOWS_V= 0x0306,

    { 0x03,  0x07,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_PWM_DUTY_PHASE,//= 0x3070,

    { 0x03,  0x08,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_MOD_POWER,//= 0x3080,
    //==2D to 3D mode CMD===
    { 0x03,  0x0A,  0x00,  0x00,  0x00,  0x00,  0x00}, // UC_SET_2D_TO_3D_MODE
    { 0x03,  0x1D,  0x01,  0x00,  0x00,  0x00,  0x00}, // UC_SET_VIDEO_FREEZE
    //==MFC DEMO CMD ==
    { 0x05,  0x01,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_MFC_DEMO_MOD,// =0x0501
    { 0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_LVDS_ON,    //0x not sure, reserved for enum declare
    { 0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_LVDS_OFF,   //0x not sure, reserved for enum declare
    //== Add Ursa 7 command
    { 0x01,  0x03,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_RX_SWITCH_TO_HDMI,// 0x0103
    { 0x01,  0x04,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_RX_OSD_ENABLE, //0x0104
    { 0x01,  0x05,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_IN_VIDEO_SIZE, //0x0105
    { 0x08,  0x01,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_ACE_SHARPNESS,//0x0801
    { 0x08,  0x02,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_ACE_BRIGHTNESS,//0x0802
    { 0x08,  0x03,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_ACE_CONTRAST,//0x0803
    { 0x08,  0x04,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_ACE_HUE,//0x0804
    { 0x08,  0x05,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_ACE_SATURATION,//0x0805
    { 0x08,  0x06,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_ACE_COLOR_TEMP_PARAM,//0x0806
    { 0x08,  0x07,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_ACE_COLOR_TEMP_LOAD,//0x0807
    { 0x08,  0x08,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_ACE_DLC,//0x0808
    { 0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_OSD_VIDEO_CHANNEL_EXCHANGE,    //0x
    { 0x03,  0x03,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_MUTE, //0x0810
    { 0x03,  0x1D,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_VIDEO_OSD_FREEZE, //0x0812
    { 0x03,  0x12,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_SR_DEMO_MODE, //0x0813
    { 0x09,  0x01,  0x00,  0x00,  0x00,  0x00,  0x00},//UC_SET_ACE_LEVEL_NR//0X901
    { 0x03,  0x13,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_GAMMA, //0X0814
    { 0xFF,  0xFF, 0x00,  0x00, 0x00, 0x00, 0x00}, //EN_CMD type index Max
};

BOOLEAN MDrv_6M40_3D_CMD_DataWrite(EN_6M40_IIC_MODE eIICMode,U8 *u8Buf)
{
    BOOLEAN bRet = FALSE;
    U16 U16SlaveID=0;
    U8 u8ChipAddr;
    if(eIICMode==IIC_DDC2BI_MODE)
         u8ChipAddr=URSA_6M40_DDC2BI_MODE_ADDR;
    else
         u8ChipAddr=URSA_6M40_IIC_MODE_ADDR;

    U16SlaveID |= (U16)((URSA_I2C_BUS_SEL<<8)|u8ChipAddr);
    //printf("===> 6M40_3D_CMD_DataWrite Start =0x%x\n",U16SlaveID);

    bRet = MDrv_IIC_WriteBytes(U16SlaveID, 0, NULL, MFC_CMD_DATA_SUM, u8Buf);

    URSA_MSG(printf("===> 6M40_3D_CMD_DataWrite=[%d]\n", bRet));

    return bRet;
}

void MDrv_Ursa_6M40_CMD_Iinit( void )
{
     g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums = 0;
     g_UrsaCMDGenSetting.g_InitInLvdsAll.bsingleCh = FALSE;
     g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_evenodd = FALSE;
     g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_msblsb = FALSE;
     g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_pn = FALSE;
     g_UrsaCMDGenSetting.g_InitInLvdsAll.bTIMode = FALSE;
     g_UrsaCMDGenSetting.g_InitInLvdsAll.bTTL = FALSE;

     g_UrsaCMDGenSetting.g_InitOutAll1.bTIMode = FALSE;
     g_UrsaCMDGenSetting.g_InitOutAll1.bShiftPair = FALSE;
     g_UrsaCMDGenSetting.g_InitOutAll1.bSwapPol = FALSE;
     g_UrsaCMDGenSetting.g_InitOutAll1.bSwapPair =FALSE ;
     g_UrsaCMDGenSetting.g_InitOutAll1.PanelBitNums = 0;
     g_UrsaCMDGenSetting.g_InitOutAll1.bDither8Bits = FALSE;
     g_UrsaCMDGenSetting.g_InitOutAll1.bDitherEn = FALSE;
     g_UrsaCMDGenSetting.g_InitOutAll1.SwapCh = 0;
     g_UrsaCMDGenSetting.g_InitOutAll1.PanelType = 0;
     g_UrsaCMDGenSetting.g_InitOutAll1.PanelChannel = 0;

     g_UrsaCMDGenSetting.g_InitOutAll2.VTotal = 0;
     g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_high = 0;
     g_UrsaCMDGenSetting.g_InitOutAll2.HTotal = 0;
     g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_low = 0;

     g_UrsaCMDGenSetting.g_InitOutAll3.PanelHeight = 0;
     g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_high = 0;
     g_UrsaCMDGenSetting.g_InitOutAll3.PanelWidth = 0;
     g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_low = 0;

     g_UrsaCMDGenSetting.g_OutLvdsMode.Reserve = 0;
     g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums = 0;
     g_UrsaCMDGenSetting.g_OutLvdsMode.bTIMode = FALSE;
     g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPol = FALSE;
     g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsShiftPair = FALSE;
     g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPair = FALSE;

     g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0;

     g_UrsaCMDGenSetting.g_OutLvdsChannelType.Reserve = 0;
     g_UrsaCMDGenSetting.g_OutLvdsChannelType.PanelChannel = 0;

     g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0;
     g_UrsaCMDGenSetting.g_3DMode.Reserve = 0;
     g_UrsaCMDGenSetting.g_3DMode.bL_Only = FALSE;

     g_UrsaCMDGenSetting.g_MFCLevel.MFClevel = 0;

     g_UrsaCMDGenSetting.g_VideoMute.Reserve = 0;
     g_UrsaCMDGenSetting.g_VideoMute.bMute = FALSE;

     g_UrsaCMDGenSetting.g_GainOffset.AdjustIdx = 0;
     g_UrsaCMDGenSetting.g_GainOffset.wAdjustValue = 0;

     g_UrsaCMDGenSetting.g_OSDWinH.Reserve = 0;
     g_UrsaCMDGenSetting.g_OSDWinH.WinID = 0;
     g_UrsaCMDGenSetting.g_OSDWinH.bWinEn = FALSE;
     g_UrsaCMDGenSetting.g_OSDWinH.WinHStart = 0;
     g_UrsaCMDGenSetting.g_OSDWinH.WinHEnd = 0;

     g_UrsaCMDGenSetting.g_OSDWinV.Reserve = 0;
     g_UrsaCMDGenSetting.g_OSDWinV.WinID = 0;
     g_UrsaCMDGenSetting.g_OSDWinV.bWinEn = FALSE;
     g_UrsaCMDGenSetting.g_OSDWinV.WinVStart = 0;
     g_UrsaCMDGenSetting.g_OSDWinV.WinVEnd = 0;

     g_UrsaCMDGenSetting.g_PwmDutyPhase.Reserve = 0;
     g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmCH= 0;
     g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty= 0;
     g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase= 0;

     g_UrsaCMDGenSetting.g_ModPower.Reserve = 0;
     g_UrsaCMDGenSetting.g_ModPower.bOnOff = FALSE;
}

void MDrv_6M40_SetInitInLvdsAllData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_InitInLvdsAll.bsingleCh)
	 u8Buf[2] |= BIT7;
     if(g_UrsaCMDGenSetting.g_InitInLvdsAll.bTIMode)
	 u8Buf[2] |= BIT6;
     u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums)<<4);
     if(g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_evenodd)
	 u8Buf[2] |= BIT3;
     if(g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_pn)
	 u8Buf[2] |= BIT2;
     if(g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_msblsb)
	 u8Buf[2] |= BIT1;
     if(g_UrsaCMDGenSetting.g_InitInLvdsAll.bTTL)
	 u8Buf[2] |= BIT0;
}

void MDrv_6M40_SetInitOutAll1Data( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_InitOutAll1.bTIMode)
	 u8Buf[2] |= BIT7;
     if(g_UrsaCMDGenSetting.g_InitOutAll1.bShiftPair)
	 u8Buf[2] |= BIT6;
     if(g_UrsaCMDGenSetting.g_InitOutAll1.bSwapPol)
	 u8Buf[2] |= BIT5;
     if(g_UrsaCMDGenSetting.g_InitOutAll1.bSwapPair)
	 u8Buf[2] |= BIT4;
     if(g_UrsaCMDGenSetting.g_InitOutAll1.bDither8Bits)
	 u8Buf[2] |= BIT1;
     if(g_UrsaCMDGenSetting.g_InitOutAll1.bDitherEn)
	 u8Buf[2] |= BIT0;
      u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_InitOutAll1.PanelBitNums)<<4);

     u8Buf[3] = g_UrsaCMDGenSetting.g_InitOutAll1.SwapCh;

     u8Buf[4] |= ((U8)(g_UrsaCMDGenSetting.g_InitOutAll1.PanelType)<<4);
     u8Buf[4] |= (U8)g_UrsaCMDGenSetting.g_InitOutAll1.PanelChannel;
}

void MDrv_6M40_SetInitOutAll2Data( U8 *u8Buf )
{
     u8Buf[2] = (U8)((g_UrsaCMDGenSetting.g_InitOutAll2.VTotal)>>8);
     u8Buf[3] = (U8)g_UrsaCMDGenSetting.g_InitOutAll2.VTotal;

     u8Buf[4] |= ((U8)(g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_high)<<4);
     u8Buf[4] |= (U8)((g_UrsaCMDGenSetting.g_InitOutAll2.HTotal)>>8);

     u8Buf[5] = (U8)g_UrsaCMDGenSetting.g_InitOutAll2.HTotal;

     u8Buf[6] = g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_low;
}

void MDrv_6M40_SetInitOutAll3Data( U8 *u8Buf )
{
     u8Buf[2] = (U8)((g_UrsaCMDGenSetting.g_InitOutAll3.PanelHeight)>>8);
     u8Buf[3] = (U8)g_UrsaCMDGenSetting.g_InitOutAll3.PanelHeight;

     u8Buf[4] |= ((U8)(g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_high)<<4);
     u8Buf[4] |= (U8)((g_UrsaCMDGenSetting.g_InitOutAll3.PanelWidth)>>8);

     u8Buf[5] = (U8)g_UrsaCMDGenSetting.g_InitOutAll3.PanelWidth;

     u8Buf[6] = g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_low;
}

void MDrv_6M40_SetOutLvdsModeData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_OutLvdsMode.bTIMode)
	 u8Buf[5] |= BIT3;
     if(g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPol)
	 u8Buf[5] |= BIT2;
     if(g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsShiftPair)
	 u8Buf[5] |= BIT1;
     if(g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPair)
	 u8Buf[5] |= BIT0;
      u8Buf[5] |= ((U8)(g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums)<<4);
 }

void MDrv_6M40_SetOutLvdsSwapData( U8 *u8Buf )
{
      u8Buf[4] = g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh;
}

void MDrv_6M40_SetOutLvdsChannelTypeData( U8 *u8Buf )
{
      u8Buf[2] = g_UrsaCMDGenSetting.g_OutLvdsChannelType.PanelChannel;
}

void MDrv_6M40_Set3DModeData( U8 *u8Buf ,U8 *pU8Data)
{
    //u8Buf[2] = *pU8Data;
  //  u8Buf[4] = *(pU8Data+2);
	*pU8Data = *pU8Data;
	if(g_UrsaCMDGenSetting.g_3DMode.bL_Only)
	u8Buf[2] |= BIT0;
	u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_3DMode.Set3Dmode)<<4);
}
void MDrv_6M40_SetVideoFreeze( U8 *u8Buf ,U8 *pU8Data)
{
    u8Buf[2] = *pU8Data;
    u8Buf[4] = *(pU8Data+2);
}
void MDrv_6M40_Set2Dto3DData( U8 *u8Buf )
{
    g_UrsaCMDGenSetting.st2Dto3D.u8Gain = 8;
    g_UrsaCMDGenSetting.st2Dto3D.u8OffSet = 128;
    u8Buf[2] = (u8Buf[2]&0xFE)|(g_UrsaCMDGenSetting.st2Dto3D.bEnable2Dto3D);
    u8Buf[2] = (u8Buf[2]&0xFD)|((g_UrsaCMDGenSetting.st2Dto3D.bEnableConcave)<<1);
    u8Buf[3] = (u8Buf[3]&0x0F)|((g_UrsaCMDGenSetting.st2Dto3D.u8Gain)<<4);
    u8Buf[4] = g_UrsaCMDGenSetting.st2Dto3D.u8OffSet;
    u8Buf[5] = g_UrsaCMDGenSetting.st2Dto3D.u8OffSet;
}

void MDrv_6M40_SetMFClevelData( U8 *u8Buf )
{
     u8Buf[2] = g_UrsaCMDGenSetting.g_MFCLevel.MFClevel;
}

void MDrv_6M40_SetVideoMuteData( U8 *u8Buf )
{
     u8Buf[2] = (U8)g_UrsaCMDGenSetting.g_VideoMute.bMute;
}

void MDrv_6M40_SetGainOffsetData( U8 *u8Buf )
{
  //   u8Buf[0] = u8Buf[0] ;
   //  u8Buf[1] = u8Buf[1] ;
     u8Buf[2] = g_UrsaCMDGenSetting.g_GainOffset.AdjustIdx;
     u8Buf[3] = (U8)((g_UrsaCMDGenSetting.g_GainOffset.wAdjustValue)>>8);
     u8Buf[4] = (U8)(g_UrsaCMDGenSetting.g_GainOffset.wAdjustValue);
}

void MDrv_6M40_SetOSDWinHData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_OSDWinH.bWinEn)
     {
	   u8Buf[2] |= BIT0;
     }
     u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_OSDWinH.WinID)<<1);
     u8Buf[3] = (U8)((g_UrsaCMDGenSetting.g_OSDWinH.WinHStart)>>8);
     u8Buf[4] = (U8)(g_UrsaCMDGenSetting.g_OSDWinH.WinHStart);
     u8Buf[5] = (U8)((g_UrsaCMDGenSetting.g_OSDWinH.WinHEnd)>>8);
     u8Buf[6] = (U8)(g_UrsaCMDGenSetting.g_OSDWinH.WinHEnd);
}

void MDrv_6M40_SetOSDWinVData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_OSDWinH.bWinEn)
     {
	   u8Buf[2] |= BIT0;
     }
     u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_OSDWinV.WinID)<<1);
     u8Buf[3] = (U8)((g_UrsaCMDGenSetting.g_OSDWinV.WinVStart)>>8);
     u8Buf[4] = (U8)(g_UrsaCMDGenSetting.g_OSDWinV.WinVStart);
     u8Buf[5] = (U8)((g_UrsaCMDGenSetting.g_OSDWinV.WinVEnd)>>8);
     u8Buf[6] = (U8)(g_UrsaCMDGenSetting.g_OSDWinV.WinVEnd);
}

void MDrv_6M40_SetPwmDutyPhaseData( U8 *u8Buf )
{
     u8Buf[2] = g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmCH;
     u8Buf[3] = (U8)((g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty)>>8);
     u8Buf[4] = (U8)(g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty);
     u8Buf[5] = (U8)((g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase)>>8);
     u8Buf[6] = (U8)(g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase);
}

void MDrv_6M40_SetModPowerData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_ModPower.bOnOff)
    {
       u8Buf[2] |= BIT0;
    }
}

void MDrv_6M40_SetMFCDemoModeData( U8 *u8Buf )
{
     u8Buf[2] = g_UrsaCMDGenSetting.stMFCDemoMode.MFCDemoMode;
#if 0//(ENABLE_MFC_DEMO_4K2K == 1)
    //set demo line color
    u8Buf[4] = 2;
    u8Buf[5] = 3;
#endif
}

void MDrv_6M40_SetRxOsdEnable( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}

void MDrv_6M40_SetInVideoSize( U8 *u8Buf ,U8 *pU8Data )
{

    u8Buf[2] = *pU8Data;
    u8Buf[3] = *(pU8Data+1);
    u8Buf[4] = *(pU8Data+2);
    u8Buf[5] = *(pU8Data+3);

}

void MDrv_6M40_SetRxSwitchToHdmi( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
	
#if ENABLE_6M50_4KX2K_PROCESS
	u8Buf[3] = *(pU8Data+1);
#endif
	
}
BOOL MDrv_6M40_SetVideoSize(const U16 u16VideoWidth,  U16 u16VideoHeight)
{
    U8 videoData[4] = {0};

    videoData[0] = (U8)((u16VideoWidth>>8) & 0xF);
    videoData[1] = (U8)(u16VideoWidth & 0xFF);
    videoData[2] = (U8)((u16VideoHeight>>8) & 0xF);
    videoData[3] = (U8)(u16VideoHeight & 0xFF);

    return MDrv_Ursa_6M40_3D_Cmd(UC_SET_IN_VIDEO_SIZE,videoData);


}

void MDrv_6M40_SetOSDVideoChannelExchange( U8 *u8Buf ,U8 *pU8Data )
{
  BOOL bEnable = (BOOL) (*pU8Data &= 0x01);
    if(bEnable)
    {
        U8 UC_INIT_RX_ALL_1[MFC_CMD_DATA_SUM]={0x00, 0x01, 0x61, 0x02, 0x02, 0x00, 0x00};
        u8Buf=UC_INIT_RX_ALL_1;
        MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,u8Buf );

        U8 UC_INIT_RX_ALL_2[MFC_CMD_DATA_SUM]={0x00, 0x02, 0x0F, 0x11, 0x11, 0x00, 0x00};
        u8Buf=UC_INIT_RX_ALL_2;
        MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,u8Buf );

        U8 UC_SET_LVDS_RX_RECONFIG[MFC_CMD_DATA_SUM]={0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};
        u8Buf=UC_SET_LVDS_RX_RECONFIG;
        MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,u8Buf );
     }
    else
    {
        U8 UC_INIT_RX_ALL_1[MFC_CMD_DATA_SUM]={0x00, 0x01, 0x61, 0x02, 0x01, 0x00, 0x00};
        u8Buf=UC_INIT_RX_ALL_1;
        MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,u8Buf );
        U8 UC_INIT_RX_ALL_2[MFC_CMD_DATA_SUM]={0x00, 0x02, 0x0F, 0x22, 0x22, 0x00, 0x00};
        u8Buf=UC_INIT_RX_ALL_2;
        MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,u8Buf );
        U8 UC_SET_LVDS_RX_RECONFIG[MFC_CMD_DATA_SUM]={0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};
        u8Buf=UC_SET_LVDS_RX_RECONFIG;
        MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,u8Buf );

    }


}

void MDrv_6M40_SetAceSharpness( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;

}

void MDrv_6M40_SetAceBrightness( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;       //R
    u8Buf[3] = *(pU8Data+1); //G
    u8Buf[4] = *(pU8Data+2); //B
}

void MDrv_6M40_SetAceContrast( U8 *u8Buf ,U8 *pU8Data )
{
   u8Buf[2] = *pU8Data;

}

void MDrv_6M40_SetAceHue( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;

}

void MDrv_6M40_SetAceSaturation( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}

void MDrv_6M40_SetAceColorTempParam( U8 *u8Buf ,U8 *pU8Data )
{

    u8Buf[2] = *pU8Data;
    u8Buf[3] = *(pU8Data+1);
    u8Buf[4] = *(pU8Data+2);

}

void MDrv_6M40_SetAceDlc( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}

void MDrv_6M40_Set_Level_NR( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}
BOOL setRxSwitchToHdmi(BOOL bEnable)
{
    U8* u8data = NULL;
    *u8data = (U8)bEnable;
	
#if	ENABLE_6M50_4KX2K_PROCESS
	*(u8data + 1) = 0x04;//for 6M50; 0x00-->Switch to HDMI1.4 , 0x04-->Switch to HDMI2.0;
#endif

    return MDrv_Ursa_6M40_3D_Cmd(UC_SET_RX_SWITCH_TO_HDMI,u8data);
}
 BOOL SetUrsaOSDEnable(BOOL bEnable)
{
    U8 cmd=0;
    cmd = (U8)bEnable;
    return MDrv_Ursa_6M40_3D_Cmd(UC_SET_RX_OSD_ENABLE,&cmd);

}
  BOOL SetUrsaUrsaMute(URSA_MUTE_TYPE eUrsa_Mute_Type)
{
    U8 cmd=0;
    cmd = (U8)eUrsa_Mute_Type;
    return MDrv_Ursa_6M40_3D_Cmd(UC_SET_MUTE,&cmd);

}

 BOOL SetUrsaPNLSize(BOOL bEnable)
{
#if PNL_CMIV500HK1_LS6_FHD_120Hz
    U8 cmd[]={ 0x26,  0x38,  0x50,  0x6d,  0x00,  0x00,  0x00,0x00,0x00};
    if(bEnable)
    {
        cmd[8] = 0x02;
    }
    else
    {
        cmd[8] = 0x00;
    }
    URSA_MSG(printf(">>CMD SetUrsaPNLSize:%x,%x,%x,%x,%x,%x,%x,%x,,%x\n",cmd[0],cmd[1],cmd[2],
                       cmd[3],cmd[4],cmd[5],cmd[6],cmd[7],cmd[8]));

    return MDrv_IIC_WriteBytes(PNL_CMD_ADDR,0,NULL,9,cmd);
#else
   UNUSED(bEnable);
#endif
}

void MDrv_6M40_SetMMPhotoByPass(U8 *u8Buf,BOOL bByPass)
{
    URSA_MSG(printf("SetMMPhotoByPass....\n"));
    U8 cmd[MFC_CMD_DATA_SUM]={0x13,0x01,0xF0,0x00,0x00,0x00,0x00}; // show edison ui cmd
    if(bByPass == TRUE)
    {
        cmd[2] = 0xF0;
    }
    else
    {
        cmd[2] = 0x00;
    }
    u8Buf=cmd;
}

void MDrv_6M40_Enable3DFormatAutoDetect(U8 *u8Buf ,BOOL bEnable)
{
    U8 cmd1[MFC_CMD_DATA_SUM] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    if(bEnable)
    {
        cmd1[0] = 0x13;
        cmd1[1] = 0x30;
        cmd1[2] = 0x01;
    }
    else
    {
        cmd1[0] = 0x03;
        cmd1[1] = 0x30;
        cmd1[2] = 0x00;
    }
    u8Buf=cmd1;
}

void MDrv_6M40_SetUrsaMute( U8 *u8Buf ,U8 *pU8Data )
{
    URSA_MUTE_TYPE enMuteType = (URSA_MUTE_TYPE)*pU8Data;
    URSA_MSG(printf("Ursa mute type = [%d]\n",enMuteType));
    switch(enMuteType)
    {
        case EN_VIDEO_ONLY_MUTE: // 0
                u8Buf[2] = 0x02;
                break;

        case EN_VIDEO_ONLY_UNMUTE:// 1
                u8Buf[2] = 0x00;
                break;

        case EN_OSD_ONLY_MUTE:// 2
                SetUrsaOSDEnable(FALSE);
                break;

        case EN_OSD_ONLY_UNMUTE:// 3
                SetUrsaOSDEnable(TRUE);
                break;

        case EN_ALL_MUTE:// 4
                u8Buf[2] = 0x01;
                break;

        case EN_ALL_UNMUTE:// 5
                u8Buf[2] = 0x00;
                break;
        default:
                break;
    }
}

void MDrv_6M40_SetFreezeType( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}

void MDrv_6M40_SetSrDemoMode( U8 *u8Buf ,U8 *pU8Data )
{
      u8Buf[2] = *pU8Data;
}

void MDrv_6M40_SetGamma( U8 *u8Buf ,U8 *pU8Data )
{
      u8Buf[2] = *pU8Data;
}

void MDrv_Ursa_6M40_CalCheckSum(U8 *pBuf, U8 u8BufLen )
{
    U8 u8CheckSum =0;

    while( u8BufLen > 1 )//calculate pBuf[1]~pBuf[End] do not count pBuf[0],it is checksum
    {
        -- u8BufLen;
        u8CheckSum += pBuf[u8BufLen];
    }
    u8CheckSum &= 0x0F;
    pBuf[0] &= 0x0F;
    pBuf[0] |= ((u8CheckSum )<<4);
}

// parameter:
// eCmdIdx is the Command Index
BOOLEAN MDrv_Ursa_6M40_3D_Cmd( UC_CMD_TYPE eCmdIdx,U8 *pU8Data)
{

    BOOLEAN bResult = FALSE;
    U8 pBuffer[MFC_CMD_DATA_SUM]={0,0,0,0,0,0,0};

   if(eCmdIdx<=UC_SET_GAMMA)
   {
       memcpy(pBuffer,&(m_UrsaCmdData[eCmdIdx]),MFC_CMD_DATA_SUM);//kent
   }
   //printf(">>>eCmdIdx==%d>>>\n",eCmdIdx);
   if((pBuffer[0]==0xFF)&&(pBuffer[1]==0xFF))
       return FALSE;

   switch(eCmdIdx)
   {
        case UC_INIT_IN_ALL:
              MDrv_6M40_SetInitInLvdsAllData(pBuffer);
 		break;
        case UC_INIT_FINISH:
		break;
        case UC_SET_IN_LVDS_MODE:
              MDrv_6M40_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_SET_IN_LVDS_SWAP:
              MDrv_6M40_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_SET_IN_LVDS_TTL:
              MDrv_6M40_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_INIT_OUT_ALL_1:
              MDrv_6M40_SetInitOutAll1Data(pBuffer);
		break;
        case UC_INIT_OUT_ALL_2:
              MDrv_6M40_SetInitOutAll2Data(pBuffer);
		break;
        case UC_INIT_OUT_ALL_3:
              MDrv_6M40_SetInitOutAll3Data(pBuffer);
		break;
        case UC_SET_OUT_LVDS_MODE:
              MDrv_6M40_SetOutLvdsModeData(pBuffer);
		break;
        case UC_SET_OUT_LVDS_SWAP:
              MDrv_6M40_SetOutLvdsSwapData(pBuffer);
		break;
        case UC_SET_OUT_LVDS_CHANNELTYPE:
              MDrv_6M40_SetOutLvdsChannelTypeData(pBuffer);
		break;
    //==3D mode CMD===
        case UC_SET_3DMODE:
              MDrv_6M40_Set3DModeData(pBuffer,pU8Data);
		break;
   //==2D to 3D mode CMD===
        case UC_SET_2D_TO_3D_MODE:
            MDrv_6M40_Set2Dto3DData(pBuffer);
            break;
        case UC_SET_VIDEO_FREEZE:
            MDrv_6M40_SetVideoFreeze(pBuffer,pU8Data);
            break;
   //==MFC level CMD ==
        case UC_SET_MFC_LEVEL:
              MDrv_6M40_SetMFClevelData(pBuffer);
		break;
    //==video mute/on CMD ==
        case UC_SET_VIDEO_MUTE:
              MDrv_6M40_SetVideoMuteData(pBuffer);
		break;
        case UC_SET_GAIN_OFFSET:
              MDrv_6M40_SetGainOffsetData(pBuffer);
		break;
        case UC_SET_OSD_WINDOWS_H:
              MDrv_6M40_SetOSDWinHData(pBuffer);
		break;
        case UC_SET_OSD_WINDOWS_V:
              MDrv_6M40_SetOSDWinVData(pBuffer);
		break;
        case UC_SET_PWM_DUTY_PHASE:
              MDrv_6M40_SetPwmDutyPhaseData(pBuffer);
		break;
        case UC_SET_MOD_POWER:
              MDrv_6M40_SetModPowerData(pBuffer);
		break;
        case UC_SET_MFC_DEMO_MOD:
            MDrv_6M40_SetMFCDemoModeData(pBuffer);
            break;
        case UC_SET_LVDS_ON:
        case UC_SET_LVDS_OFF:
            break;
        case UC_SET_RX_SWITCH_TO_HDMI:
           MDrv_6M40_SetRxSwitchToHdmi(pBuffer,pU8Data);
            break;
        case UC_SET_RX_OSD_ENABLE:
            MDrv_6M40_SetRxOsdEnable(pBuffer,pU8Data);
            break;
        case UC_SET_IN_VIDEO_SIZE:
            MDrv_6M40_SetInVideoSize(pBuffer,pU8Data);
            break;

        case UC_SET_ACE_SHARPNESS:
            MDrv_6M40_SetAceSharpness(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_BRIGHTNESS:
            MDrv_6M40_SetAceBrightness(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_CONTRAST:
            MDrv_6M40_SetAceContrast(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_HUE:
            MDrv_6M40_SetAceHue(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_SATURATION:
            MDrv_6M40_SetAceSaturation(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_COLOR_TEMP_PARAM:
            MDrv_6M40_SetAceColorTempParam(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_COLOR_TEMP_LOAD:
            break;
        case UC_SET_ACE_DLC:
            MDrv_6M40_SetAceDlc(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_LEVEL_NR:
            MDrv_6M40_Set_Level_NR(pBuffer,pU8Data);
            break;
        case UC_SET_OSD_VIDEO_CHANNEL_EXCHANGE:
            MDrv_6M40_SetOSDVideoChannelExchange(pBuffer,pU8Data);
            break;
        case UC_SET_MUTE:
            MDrv_6M40_SetUrsaMute(pBuffer,pU8Data);
            break;
        case UC_SET_VIDEO_OSD_FREEZE:
            MDrv_6M40_SetFreezeType(pBuffer,pU8Data);
            break;
        case UC_SET_SR_DEMO_MODE:
           MDrv_6M40_SetSrDemoMode(pBuffer,pU8Data);
            break;
        case UC_SET_GAMMA:
           MDrv_6M40_SetGamma(pBuffer,pU8Data);
            break;
         case UC_SET_4K2K_MODE:
           // bResult=MDrv_6M40_SetUrsa4K2KType((EN_URSA_4K2K_MODE)(*pU8Data));
            break;
         case UC_GET_4K2K_MODE:
            //bResult=MDrv_6M40_GetUrsa4K2KType(pU8Data);
            break;
         case UC_SET_PHOTO_BYPASS_ENABLE:
            MDrv_6M40_SetMMPhotoByPass(pBuffer,TRUE);
         break;
         case UC_SET_PHOTO_BYPASS_DISABLE:
            MDrv_6M40_SetMMPhotoByPass(pBuffer,FALSE);
         break;
         case UC_ENABLE_3D_AUTO_DETECT:
            MDrv_6M40_Enable3DFormatAutoDetect(pBuffer,TRUE);
         break;
         case UC_DISABLE_3D_AUTO_DETECT:
            MDrv_6M40_Enable3DFormatAutoDetect(pBuffer,FALSE);
         break;
         case UC_SET_HDCP_KEY:
           // bResult= MDrv_Ursa_6M40_SetHDMI_HDCP(pU8Data, HDMI_HDCP_KEY_SIZE);
         break;
	default:
		break;
   }

    MDrv_Ursa_6M40_CalCheckSum(pBuffer, MFC_CMD_DATA_SUM);
    URSA_MSG(printf(">>CMD:%x,%x,%x,%x,%x,%x,%x\n",pBuffer[0],pBuffer[1],pBuffer[2],
                       pBuffer[3],pBuffer[4],pBuffer[5],pBuffer[6]));
   if(bResult==FALSE)
   {
       bResult = MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE, pBuffer);
   }

    return bResult;

}
BOOLEAN MDrv_Ursa_6M40_SetHDMI_HDCP(U8 *pu8Data, U16 u16Size)
{
    BOOL bResult = FALSE;
    U16 u16DataCount = 0;
    U8 u8SetHDMICount = 0;
    U8 u8GetHDMICount = 0;

    for (u16DataCount = 0; u16DataCount < u16Size; u16DataCount+=5, u8SetHDMICount++)
    {
        U8 UC_SET_HDMI_HDCP[MFC_CMD_DATA_SUM]={0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};

        if ((u16DataCount + 5) <= u16Size)
        {
            memcpy (&UC_SET_HDMI_HDCP[2], (pu8Data + u16DataCount), 5);
        }
        else
        {
            memcpy (&UC_SET_HDMI_HDCP[2], (pu8Data + u16DataCount), (u16Size - u16DataCount));
        }

        MDrv_Ursa_6M40_CalCheckSum(UC_SET_HDMI_HDCP, MFC_CMD_DATA_SUM);
       // URSA_MSG(printf(">>HDCP CMD:%x,%x,%x,%x,%x,%x,%x\n",UC_SET_HDMI_HDCP[0],UC_SET_HDMI_HDCP[1],UC_SET_HDMI_HDCP[2],
        //               UC_SET_HDMI_HDCP[3],UC_SET_HDMI_HDCP[4],UC_SET_HDMI_HDCP[5],UC_SET_HDMI_HDCP[6]));

        bResult = MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,UC_SET_HDMI_HDCP);

        if (FALSE == bResult)
        {
            break;
        }

        MsOS_DelayTask(50);
    }

    if (TRUE == bResult)
    {
        U8 UC_GET_HDCP_COUNT[MFC_CMD_DATA_SUM]={0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
        MDrv_Ursa_6M40_CalCheckSum(UC_GET_HDCP_COUNT, MFC_CMD_DATA_SUM);
        URSA_MSG(printf(">>HDCP CMD:%x,%x,%x,%x,%x,%x,%x\n",UC_GET_HDCP_COUNT[0],UC_GET_HDCP_COUNT[1],UC_GET_HDCP_COUNT[2],
                       UC_GET_HDCP_COUNT[3],UC_GET_HDCP_COUNT[4],UC_GET_HDCP_COUNT[5],UC_GET_HDCP_COUNT[6]));

        bResult = MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,UC_GET_HDCP_COUNT);

        if (TRUE == bResult)
        {
            MsOS_DelayTask(50);
            bResult=MDrv_IIC_ReadByte( URSA_6M40_DDC2BI_MODE_ADDR,  NULL,&u8GetHDMICount);
            MsOS_DelayTask(50);
            URSA_MSG(printf("--u8GetHDMICount=%d---u8SetHDMICount=%d--\n",u8GetHDMICount,u8SetHDMICount));
            if ((TRUE == bResult) && (u8GetHDMICount == u8SetHDMICount))
            {
                U8 UC_SET_HDMI_HDCP_UPDATE[MFC_CMD_DATA_SUM]={0x06, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00};
                MsOS_DelayTask(50);
                MDrv_Ursa_6M40_CalCheckSum(UC_SET_HDMI_HDCP_UPDATE, MFC_CMD_DATA_SUM);
                //URSA_MSG(printf(">>HDCP CMD:%x,%x,%x,%x,%x,%x,%x\n",UC_SET_HDMI_HDCP_UPDATE[0],UC_SET_HDMI_HDCP_UPDATE[1],UC_SET_HDMI_HDCP_UPDATE[2],
                //       UC_SET_HDMI_HDCP_UPDATE[3],UC_SET_HDMI_HDCP_UPDATE[4],UC_SET_HDMI_HDCP_UPDATE[5],UC_SET_HDMI_HDCP_UPDATE[6]));

                bResult = MDrv_6M40_3D_CMD_DataWrite(IIC_DDC2BI_MODE,UC_SET_HDMI_HDCP_UPDATE);
            }
            else
            {
                URSA_MSG(printf("Check_SetHDMI_HDCP  Fail \n"));
                bResult = FALSE;
            }
        }
    }

    if(bResult)
    {
       URSA_MSG(printf("Load 6M40_SetHDMI_HDCP  OK !!\n"));
    }
    else
    {
       URSA_MSG(printf("Load 6M40_SetHDMI_HDCP  Fail !!\n"));
    }
    return bResult;
}
BOOLEAN MDrv_Ursa_6M40_PWM_Duty_And_Phase(U8 u8PwmDuty,U16 u16PwmPhase,EN_6M40_CH ePwmCh)
{
	BOOLEAN bResult = FALSE;
       g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmCH= ePwmCh;
       g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty= u8PwmDuty*100;
       g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase= u16PwmPhase*100;

	bResult=MDrv_Ursa_6M40_3D_Cmd(UC_SET_PWM_DUTY_PHASE,NULL);
        if(bResult)
        {
            URSA_MSG(printf("select MFC level ok!!!\n"));
        }
       else
        {
            URSA_MSG(printf("select MFC level error!!!\n"));
        }
	return bResult;
}

BOOLEAN MDrv_Ursa_6M40_MFC_Level( EN_6M40_MEMC_LEVEL eMFClevel )
{
	BOOLEAN bResult = FALSE;
	switch(eMFClevel)
        {
            case EN_6M40_MEMC_OFF:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 0;
                break;
            case EN_6M40_MEMC_LOW:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 1;
                break;
            case EN_6M40_MEMC_MIDDLE:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 2;
                break;
            case EN_6M40_MEMC_HIGH:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 3;
                break;
            default:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 2;
                break;
        }
        bResult=MDrv_Ursa_6M40_3D_Cmd(UC_SET_MFC_LEVEL,NULL);

        if(bResult)
        {
            URSA_MSG(printf("select MFC level ok!!!\n"));
        }
       else
        {
            URSA_MSG(printf("select MFC level error!!!\n"));
        }
	return bResult;
}

BOOLEAN MDrv_Ursa_6M40_VIDEO_Enalbe( BOOLEAN bEnable )
{
	BOOLEAN bResult = FALSE;
	if(bEnable)
       {
              g_UrsaCMDGenSetting.g_VideoMute.bMute= 1;
       }
       else
       {
              g_UrsaCMDGenSetting.g_VideoMute.bMute= 0;
       }

       bResult=MDrv_Ursa_6M40_3D_Cmd(UC_SET_VIDEO_MUTE,NULL);

        if(bResult)
        {
            URSA_MSG(printf("select video on/off ok!!!\n"));
        }
       else
        {
            URSA_MSG(printf("select video on/off error!!!\n"));
        }
	return bResult;
}

BOOLEAN MDrv_Ursa_6M40_LVDS_Enalbe( BOOLEAN bEnable )
{
	BOOLEAN bResult = FALSE;
	if(bEnable)
       {
              g_UrsaCMDGenSetting.g_ModPower.bOnOff= 1;
       }
       else
       {
               g_UrsaCMDGenSetting.g_ModPower.bOnOff= 0;
       }
       bResult=MDrv_Ursa_6M40_3D_Cmd(UC_SET_MOD_POWER,NULL);

        if(bResult)
        {
            URSA_MSG(printf("select lvds on/off ok!!!\n"));
        }
       else
        {
            URSA_MSG(printf("select lvds on/off error!!!\n"));
        }
	return bResult;
}

BOOLEAN MDrv_Ursa_6M40_3D_MODE( PANEL_3D_MODE ePanel3DMode )
{
	BOOLEAN bResult = FALSE;

    switch(ePanel3DMode)
    {
        case PANEL_3D_MODE_NONE:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x0;
            break;
        case PANEL_3D_MODE_SIDE_BY_SIDE_2X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x1;
            break;
        case PANEL_3D_MODE_TOP_BOTTOM_2X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x2;
            break;
        case PANEL_3D_MODE_CHECK_BOARD_2X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x3;
            break;
        case PANEL_3D_MODE_FRAME_INTERLEAVE_25X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x4;
            break;
        case PANEL_3D_MODE_LINE_INTERLEAVED_2X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x5;
            break;
        case PANEL_3D_MODE_FRAME_INTERLEAVE_2X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x6;
            break;
        case PANEL_3D_MODE_720P_1XMODE:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x9;
            break;
        case PANEL_3D_MODE_SIDE_BY_SIDE_24X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0xA;
            break;
        case PANEL_3D_MODE_TOP_BOTTOM_24X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0xB;
            break;
        case PANEL_3D_MODE_CHECK_BOARD_24X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0xC;
            break;
        case PANEL_3D_MODE_LINE_INTERLEAVED_24X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0xD;
            break;
        case PANEL_3D_MODE_FRAME_INTERLEAVE_24X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0xE;
            break;
        case PANEL_3D_MODE_MFC_24X:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0xF;
            break;
        default:
            g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0x0;
            break;
    }

    bResult = MDrv_Ursa_6M40_3D_Cmd(UC_SET_3DMODE,NULL);

    if(bResult)
    {
        URSA_MSG(printf("select 3d mode ok!!!\n"));
    }
    else
    {
       URSA_MSG(printf("select 3d mode error!!!\n"));
    }

    return bResult;

}

BOOLEAN MDrv_Ursa_6M40_Enable2Dto3D( BOOLEAN bEnable )
{
    BOOLEAN bResult = FALSE;

    g_UrsaCMDGenSetting.st2Dto3D.bEnable2Dto3D = bEnable;

    bResult = MDrv_Ursa_6M40_3D_Cmd(UC_SET_2D_TO_3D_MODE,NULL);

    if(bResult)
    {
        URSA_MSG(printf("2D to 3D enable ok!!!\n"));
    }
    else
    {
        URSA_MSG(printf("2D to 3D enable error!!!\n"));
    }
	return bResult;
}
BOOLEAN MDrv_Ursa_6M40_Get4K2KType(U8 *pU8Data)
{
     URSA_MSG(printf("getUrsa4K2KType:m_4K2Kmode:%d\n",(U8)m_4K2Kmode));
    *pU8Data = (U8)m_4K2Kmode;
     return TRUE;

}
BOOLEAN MDrv_Ursa_6M40_Set4K2KType(EN_URSA_4K2K_MODE enMode)
{
    BOOL bResult = FALSE;
    URSA_MSG(printf("4KX2K enMode=%d\n",enMode));
    switch (enMode)
    {
        case E_URSA_4K2K_MODE_4K1K:
            bResult |=SetUrsaUrsaMute (EN_VIDEO_ONLY_MUTE);
            MsOS_DelayTask(50);
            bResult =setRxSwitchToHdmi(FALSE);
            MsOS_DelayTask(50);
            bResult |= MDrv_6M40_SetVideoSize(WIDTH_4K2K,HEIGHT_4K1K);
            MsOS_DelayTask(50);
            bResult |=SetUrsaOSDEnable (TRUE);
            MsOS_DelayTask(500);
            bResult |=SetUrsaUrsaMute (EN_VIDEO_ONLY_UNMUTE);
            break;
        case E_URSA_4K2K_MODE_4K2K:
            bResult |=SetUrsaUrsaMute (EN_VIDEO_ONLY_MUTE);
            MsOS_DelayTask(50);
            bResult =setRxSwitchToHdmi(FALSE);
            MsOS_DelayTask(50);
            bResult |=MDrv_6M40_SetVideoSize(WIDTH_4K2K,HEIGHT_4K2K);
            MsOS_DelayTask(50);
            bResult |=SetUrsaOSDEnable (TRUE);
            MsOS_DelayTask(50);
            bResult|=SetUrsaPNLSize(TRUE);
            MsOS_DelayTask(500);
            bResult |=SetUrsaUrsaMute (EN_VIDEO_ONLY_UNMUTE);
            break;
        case E_URSA_4K2K_MODE_HDMI4K2K:
            bResult |=SetUrsaUrsaMute (EN_VIDEO_ONLY_MUTE);
            MsOS_DelayTask(50);
            bResult =setRxSwitchToHdmi(TRUE);
            MsOS_DelayTask(50);
            bResult |=MDrv_6M40_SetVideoSize(WIDTH_4K2K,HEIGHT_4K2K);
            MsOS_DelayTask(50);
            bResult |=SetUrsaOSDEnable (TRUE);
            MsOS_DelayTask(50);
            bResult|=SetUrsaPNLSize(TRUE);
            MsOS_DelayTask(500);
            bResult |=SetUrsaUrsaMute (EN_VIDEO_ONLY_UNMUTE);
            break;
        case E_URSA_4K2K_MODE_FULLHD:
        default:
            bResult |=SetUrsaUrsaMute (EN_VIDEO_ONLY_MUTE);
            MsOS_DelayTask(50);
            bResult =setRxSwitchToHdmi(FALSE);
            MsOS_DelayTask(50);
            bResult |= MDrv_6M40_SetVideoSize(WIDTH_FULLHD,HEIGHT_FULLHD);
            MsOS_DelayTask(50);
            bResult |=SetUrsaOSDEnable (FALSE);
            MsOS_DelayTask(50);
            bResult|=SetUrsaPNLSize(FALSE);
            MsOS_DelayTask(500);
            bResult |=SetUrsaUrsaMute (EN_VIDEO_ONLY_UNMUTE);
            break;
    }

    if (bResult)
    {
        m_4K2Kmode = enMode;
    }
    else
    {
        URSA_MSG(printf("---->set 4KX2K Mode fail<-----\n"));
    }

    URSA_MSG(printf("=======>SetUrsa4K2KType(%d) finished<========\n",m_4K2Kmode));

return bResult;
}

//===============================================================
//==============6M40 IIC operating code=================================
//===============================================================

typedef enum
{
    MFC_I2cUseBusN       = 0x34,
    MFC_I2cUseBus        = 0x35,
    MFC_CpuWaitN         = 0x36,
    MFC_CpuWait          = 0x37,
    MFC_SerialDebugEnter = 0x44,
    MFC_SerialDebugExit  = 0x45,
    MFC_SetAddrFmt2Byte  = 0x51,
    MFC_DisableNewCfg    = 0x7E,
    MFC_EnableNewCfg     = 0x7F,
    MFC_ChNumBit0Disable = 0x80,
    MFC_ChNumBit0Enable  = 0x81,
    MFC_ChNumBit1Disable = 0x82,
    MFC_ChNumBit1Enable  = 0x83,
    MFC_ChNumBit2Disable = 0x84,
    MFC_ChNumBit2Enable  = 0x85,
} MFC_SERIAL_DEBUG_CMD_e;

static BOOL isI2cOpen=FALSE;
#define MST6Mxx_I2C_USE_CH2   1
BOOL MDrv_MFC_6M40_SetSerialDebugMode(MFC_SERIAL_DEBUG_CMD_e cmd)
{
    U32  u32Addr;
    U8   pU8Data[5];
    BOOL ret;
    U16 u16SlaveID = (U16)((URSA_I2C_BUS_SEL<<8)|URSA_6M40_IIC_MODE_ADDR);

    u32Addr = 0;

    if (cmd == MFC_SerialDebugEnter)
    {
        pU8Data[0] = 0x53;
        pU8Data[1] = 0x45;
        pU8Data[2] = 0x52;
        pU8Data[3] = 0x44;
        pU8Data[4] = 0x42;
        ret = MDrv_IIC_WriteBytes(u16SlaveID, 0, NULL, 5, pU8Data);
        if (!ret)
        {
   	//     	 dbgprint("MFC_SerialDebugEnter %d   %s\n",__LINE__,__FILE__);
	//		dbgprint("MFC_SerialDebugEnter=============cmd = 0x%x===================\n", cmd);
            return FALSE;
        }
    }
    else
    {
        pU8Data[0] = cmd;
        ret = (MDrv_IIC_WriteBytes(u16SlaveID, 0, NULL, 1, pU8Data));
        if (!ret)
        {
            if(cmd != MFC_SerialDebugExit)
            {
            	return FALSE;
            }
    	}
    }
    return TRUE;
}
void MDrv_MFC_6M40_SetSerialDebug(BOOL bOpen)
{
    if(bOpen)
    {
        if(isI2cOpen==FALSE)
        {
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_SerialDebugEnter);
            #if MST6Mxx_I2C_USE_CH2
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_ChNumBit0Disable);
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_ChNumBit1Enable);
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_ChNumBit2Disable);  //Switch to Ch2
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_SetAddrFmt2Byte);
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_EnableNewCfg);
            #else
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_CpuWait);
            #endif
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_I2cUseBus);
            isI2cOpen=TRUE;
        }
    }
    else
    {
        if(isI2cOpen)
        {
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_I2cUseBusN);
            #if MST6Mxx_I2C_USE_CH2
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_ChNumBit0Disable);
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_ChNumBit1Disable);
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_ChNumBit2Disable);
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_SetAddrFmt2Byte);
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_DisableNewCfg);
            #else
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_CpuWaitN);
            #endif
            MDrv_MFC_6M40_SetSerialDebugMode(MFC_SerialDebugExit);
            isI2cOpen=FALSE;
        }
    }
}

void MDrv_MFC_6M40_DebugStart(void)
{
    #if 0//(NEW_URSA_SERIAL_DEBUG_MODE==0)
		MDrv_Ursa_EnterSerialDebugMode(TRUE);
		MDrv_Ursa_CpuWait(TRUE);
		MDrv_Ursa_IICUseBus(TRUE);
    #else
        MDrv_MFC_6M40_SetSerialDebug(TRUE);
    #endif
}
void MDrv_MFC_6M40_DebugEnd(void)
{
    #if 0//(NEW_URSA_SERIAL_DEBUG_MODE==0)
	MDrv_Ursa_IICUseBus(FALSE);
	MDrv_Ursa_CpuWait(FALSE);
	MDrv_Ursa_EnterSerialDebugMode(FALSE);
    #else
        MDrv_MFC_6M40_SetSerialDebug(FALSE);
    #endif
}

BOOLEAN MDrv_Ursa_6M40_Set_Value(U16 u16addr, U8 u8Buf)
{
    BOOLEAN bRet = FALSE;
    U8 pU8Databuf[5] = {0, 0, 0, 0, 0};
    U16 u16SlaveID = (U16)((URSA_I2C_BUS_SEL<<8)|URSA_6M40_IIC_MODE_ADDR);
    MDrv_MFC_6M40_DebugStart();
    pU8Databuf[0] = 0x10;
    pU8Databuf[3] = u8Buf;

    //e.g. address 0x29 11 --> 0x29 11,then we send 0x2911 to 6M10...
    pU8Databuf[1] = (U8)(u16addr >> 8);   //the high byte need not move left 1 bit
    pU8Databuf[2] = (U8)(u16addr);//the low byte moves left 1 bit, reset bit0 means data low byte
    bRet = MDrv_IIC_WriteBytes(u16SlaveID, 0, NULL, 4, pU8Databuf);

    MDrv_MFC_6M40_DebugEnd();
    return bRet;
}

U8 MDrv_Ursa_6M40_Get_Value(U16 U16Addr, BOOLEAN bHigh)
{
    U8 pU8Data, pU8Databuf[4]={0, 0, 0, 0};
    U16 u16SlaveID = (U16)((URSA_I2C_BUS_SEL<<8)|URSA_6M40_IIC_MODE_ADDR);

    MDrv_MFC_6M40_DebugStart();

    pU8Databuf[0] = 0x10;

    if(bHigh == FALSE)
    {
        pU8Databuf[1] = (U8)(U16Addr >> 8);//the high byte need not move left 1 bit
        pU8Databuf[2] = (U8)(U16Addr);//the low byte moves left 1 bit, reset bit0 means data low byte
    }
    else
    {
        pU8Databuf[1] = (U8)(U16Addr >> 8);//the high byte need not move left 1 bit
        pU8Databuf[2] = (U8)(U16Addr | 0x01);//the low byte moves left 1 bit, set bit0 means data high byte
    }

    MDrv_IIC_WriteBytes(u16SlaveID, 0, NULL, 3, pU8Databuf);
    MDrv_IIC_ReadBytes((u16SlaveID+1), 0, NULL, 1, &pU8Data);

    MDrv_MFC_6M40_DebugEnd();

    return pU8Data;
}
void MDrv_URSA_6M40_Set_4K_2K_Mode(U8 bOnOff)
{
    U8 pU8Databuf[3]={0,0,0};

    if (bOnOff)
        {
            pU8Databuf[0] = 0xE0;
        }
    else
        {
            pU8Databuf[0] = 0x0;
        }
    MDrv_Ursa_6M40_3D_Cmd(UC_SET_3DMODE,pU8Databuf);
}
void MDrv_URSA_6M40_Set_Video_Freeze(U8 bOnOff)
{
    U8 pU8Databuf[3]={0,0,0};

    if (bOnOff)
        {
            pU8Databuf[0] = 0x1;
        }
    else
        {
            pU8Databuf[0] = 0x0;
        }
    MDrv_Ursa_6M40_3D_Cmd(UC_SET_VIDEO_FREEZE,pU8Databuf);
}
#endif

#undef DRV_URSA_6M40_C
