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
// File Name: drvUrsa3D6M30.c
// Description: Comunication to URSA module
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////
#define DRV_URSA_6M30_C
#include "drvUrsa6M30.h"

#if ENABLE_MFC_6M30

URSA_CMD_GEN_SETTINGS g_UrsaCMDGenSetting;

BOOLEAN MDrv_6M30_3D_CMD_DataWrite(EN_6M30_IIC_MODE eIICMode,U8 *u8Buf)
{
    BOOLEAN bRet = FALSE;
    U16 U16SlaveID=0;
    U8 u8ChipAddr;
    if(eIICMode==IIC_DDC2BI_MODE)
         u8ChipAddr=URSA_6M30_DDC2BI_MODE_ADDR;
    else
         u8ChipAddr=URSA_6M30_IIC_MODE_ADDR;

    U16SlaveID |= (U16)((URSA_I2C_BUS_SEL<<8)|u8ChipAddr);

    bRet = MDrv_IIC_WriteBytes(U16SlaveID, 0, NULL, MFC_CMD_DATA_SUM, u8Buf);

    printf("===> 6M30_3D_CMD_DataWrite[%d]\n", bRet);

    return bRet;
}

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
	{ 0x03,  0x01,	0x00,  0x00,  0x00,  0x00, 0x00}, //UC_SET_LRCHANGE
    //==2D to 3D mode CMD===
    { 0x03,  0x0A,  0x00,  0x00,  0x00,  0x00,  0x00}, // UC_SET_2D_TO_3D_MODE
    //==MFC level CMD ==
    { 0x03,  0x02,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_MFC_LEVEL  = 0x0302,
    //==MFC Demo CMD==
    { 0x05,  0x01,  0x00,  0x00,  0x00,  0x00,  0x00},//UC_SET_MFC_DEMO   = 0x0501,

     //==video mute/on CMD ==
    { 0x03,  0x03,  0x01,  0x00,  0x00,  0x00,  0x00}, //UC_SET_VIDEO_MUTE= 0x3030,
    { 0x03,  0x04,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_GAIN_OFFSET= 0x0304,
    { 0x03,  0x05,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OSD_WINDOWS_H= 0x0305,
    { 0x03,  0x06,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OSD_WINDOWS_V= 0x0306,
    { 0x03,  0x07,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_PWM_DUTY_PHASE,//= 0x3070,
    { 0x03,  0x08,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_MOD_POWER,//= 0x3080,

    { 0x03,  0x0C,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_MOD_POWER,//= 0x3080,

    { 0x03,  0x0E,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_GET_FW_VER_MAIN,//= 0x30E0,
    { 0x03,  0x0E,  0x01,  0x00,  0x00,  0x00,  0x00}, //UC_GET_FW_VER_MINOR,//= 0x30E0,
    { 0x04,  0x05,  0x00,  0x00,  0x00,  0x00,  0x00}, // UC_SET_PANEL_3D_ONOFF
    { 0xFF,  0xFF, 0x00,  0x00, 0x00, 0x00, 0x00}, //EN_CMD type index Max
};


void MDrv_Ursa_6M30_CMD_Iinit( void )
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
     g_UrsaCMDGenSetting.g_3DMode.SetPanel3DOnOffBy6M30 = 0;
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

void MDrv_6M30_SetInitInLvdsAllData( U8 *u8Buf )
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

void MDrv_6M30_SetInitOutAll1Data( U8 *u8Buf )
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

void MDrv_6M30_SetInitOutAll2Data( U8 *u8Buf )
{
     u8Buf[2] = (U8)((g_UrsaCMDGenSetting.g_InitOutAll2.VTotal)>>8);
     u8Buf[3] = (U8)g_UrsaCMDGenSetting.g_InitOutAll2.VTotal;

     u8Buf[4] |= ((U8)(g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_high)<<4);
     u8Buf[4] |= (U8)((g_UrsaCMDGenSetting.g_InitOutAll2.HTotal)>>8);

     u8Buf[5] = (U8)g_UrsaCMDGenSetting.g_InitOutAll2.HTotal;

     u8Buf[6] = g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_low;
}

void MDrv_6M30_SetInitOutAll3Data( U8 *u8Buf )
{
     u8Buf[2] = (U8)((g_UrsaCMDGenSetting.g_InitOutAll3.PanelHeight)>>8);
     u8Buf[3] = (U8)g_UrsaCMDGenSetting.g_InitOutAll3.PanelHeight;

     u8Buf[4] |= ((U8)(g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_high)<<4);
     u8Buf[4] |= (U8)((g_UrsaCMDGenSetting.g_InitOutAll3.PanelWidth)>>8);

     u8Buf[5] = (U8)g_UrsaCMDGenSetting.g_InitOutAll3.PanelWidth;

     u8Buf[6] = g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_low;
}

void MDrv_6M30_SetOutLvdsModeData( U8 *u8Buf )
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

void MDrv_6M30_SetOutLvdsSwapData( U8 *u8Buf )
{
      u8Buf[4] = g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh;
}

void MDrv_6M30_SetOutLvdsChannelTypeData( U8 *u8Buf )
{
      u8Buf[2] = g_UrsaCMDGenSetting.g_OutLvdsChannelType.PanelChannel;
}

void MDrv_6M30_Set3DModeData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_3DMode.bL_Only)
	 u8Buf[2] |= BIT0;
      u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_3DMode.Set3Dmode)<<4);
}

void MDrv_6M30_Set2Dto3DData( U8 *u8Buf )
{
    g_UrsaCMDGenSetting.st2Dto3D.u8Gain = 8;
    g_UrsaCMDGenSetting.st2Dto3D.u8OffSet = 128;
    u8Buf[2] = (u8Buf[2]&0xFE)|(g_UrsaCMDGenSetting.st2Dto3D.bEnable2Dto3D);
    u8Buf[2] = (u8Buf[2]&0xFD)|((g_UrsaCMDGenSetting.st2Dto3D.bEnableConcave)<<1);
    u8Buf[3] = (u8Buf[3]&0x0F)|((g_UrsaCMDGenSetting.st2Dto3D.u8Gain)<<4);
    u8Buf[4] = g_UrsaCMDGenSetting.st2Dto3D.u8OffSet;
    u8Buf[5] = g_UrsaCMDGenSetting.st2Dto3D.u8OffSet;
}

void MDRV_6M30_SetLRExchangeMode( U8 *u8Buf )
{
	if(g_UrsaCMDGenSetting.g_3DMode.bL_Only)
		u8Buf[2] |= BIT0;
	u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_3DMode.Set3Dmode)<<4);
	u8Buf[3] |= ((U8)(g_UrsaCMDGenSetting.g_3DMode.bLRExchangeMode));
}

void MDrv_6M30_SetMFClevelData( U8 *u8Buf )
{
     u8Buf[2] = g_UrsaCMDGenSetting.g_MFCLevel.MFClevel;
}

void MDrv_6M30_SetMFCDemoData( U8 *u8Buf )
{
     u8Buf[2] = g_UrsaCMDGenSetting.g_MFCDemo.MFCDemoMode;
}

void MDrv_6M30_SetVideoMuteData( U8 *u8Buf )
{
     u8Buf[2] = (U8)g_UrsaCMDGenSetting.g_VideoMute.bMute;
}

void MDrv_6M30_SetGainOffsetData( U8 *u8Buf )
{
  //   u8Buf[0] = u8Buf[0] ;
   //  u8Buf[1] = u8Buf[1] ;
     u8Buf[2] = g_UrsaCMDGenSetting.g_GainOffset.AdjustIdx;
     u8Buf[3] = (U8)((g_UrsaCMDGenSetting.g_GainOffset.wAdjustValue)>>8);
     u8Buf[4] = (U8)(g_UrsaCMDGenSetting.g_GainOffset.wAdjustValue);
}

void MDrv_6M30_SetOSDWinHData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_OSDWinH.bWinEn)
	 u8Buf[2] |= BIT0;
     u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_OSDWinH.WinID)<<1);
     u8Buf[3] = (U8)((g_UrsaCMDGenSetting.g_OSDWinH.WinHStart)>>8);
     u8Buf[4] = (U8)(g_UrsaCMDGenSetting.g_OSDWinH.WinHStart);
     u8Buf[5] = (U8)((g_UrsaCMDGenSetting.g_OSDWinH.WinHEnd)>>8);
     u8Buf[6] = (U8)(g_UrsaCMDGenSetting.g_OSDWinH.WinHEnd);
}

void MDrv_6M30_SetOSDWinVData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_OSDWinH.bWinEn)
	 u8Buf[2] |= BIT0;
     u8Buf[2] |= ((U8)(g_UrsaCMDGenSetting.g_OSDWinV.WinID)<<1);
     u8Buf[3] = (U8)((g_UrsaCMDGenSetting.g_OSDWinV.WinVStart)>>8);
     u8Buf[4] = (U8)(g_UrsaCMDGenSetting.g_OSDWinV.WinVStart);
     u8Buf[5] = (U8)((g_UrsaCMDGenSetting.g_OSDWinV.WinVEnd)>>8);
     u8Buf[6] = (U8)(g_UrsaCMDGenSetting.g_OSDWinV.WinVEnd);
}

void MDrv_6M30_SetPwmDutyPhaseData( U8 *u8Buf )
{
     u8Buf[2] = g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmCH;
     u8Buf[3] = (U8)((g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty)>>8);
     u8Buf[4] = (U8)(g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty);
     u8Buf[5] = (U8)((g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase)>>8);
     u8Buf[6] = (U8)(g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase);
}

void MDrv_6M30_SetModPowerData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_ModPower.bOnOff)
	 u8Buf[2] |= BIT0;
}

void MDrv_6M30_SetMirrorData( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_3DMode.Set6M30MirrorMode)
     {
		 u8Buf[2] |= BIT0;
		 u8Buf[2] |= BIT1;
     }
	 else
	 {
		 u8Buf[2] &= (~BIT0);
		 u8Buf[2] &= (~BIT1);
	 }
}

void MDrv_6M30_SetPanel3DOnOff( U8 *u8Buf )
{
     if(g_UrsaCMDGenSetting.g_3DMode.SetPanel3DOnOffBy6M30)
     {
		 u8Buf[2] |= BIT0;
     }
	 else
	 {
		 u8Buf[2] &= (~BIT0);
	 }
}

void MDrv_Ursa_6M30_CalCheckSum(U8 *pBuf, U8 u8BufLen )
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

BOOLEAN MDrv_Ursa_6M30_MFC_Demo(U8 enMFCDemo)
{
	BOOLEAN bResult = FALSE;
	switch(enMFCDemo)
    {
        case EN_URSA_MFC_Off:
            g_UrsaCMDGenSetting.g_MFCDemo.MFCDemoMode= 0;
            break;
        case EN_URSA_MFC_Horizantal:
            g_UrsaCMDGenSetting.g_MFCDemo.MFCDemoMode= 1;
            break;
        case EN_URSA_MFC_Vertical:
            g_UrsaCMDGenSetting.g_MFCDemo.MFCDemoMode= 2;
            break;
        default:
            g_UrsaCMDGenSetting.g_MFCDemo.MFCDemoMode= 0;
            break;
    }
    bResult=MDrv_Ursa_6M30_3D_Cmd(UC_SET_MFC_DEMO);

    if(bResult)
    {
        printf("Set MFC Demo ok!!!\n");
    }
    else
    {
        printf("Set MFC Demo error!!!\n");
    }
	return bResult;
}

// parameter:
// eCmdIdx is the Command Index
BOOLEAN MDrv_Ursa_6M30_3D_Cmd( UC_CMD_TYPE eCmdIdx)
{
    BOOLEAN bResult = TRUE;
    U8 pBuffer[7]={0,0,0,0,0,0,0};

    if(eCmdIdx>=UC_SET_CMDTYPE_END)
       return FALSE;

    memcpy(pBuffer,&(m_UrsaCmdData[eCmdIdx]),MFC_CMD_DATA_SUM);

   if((pBuffer[0]==0xFF)&&(pBuffer[1]==0xFF))
       return FALSE;

   switch(eCmdIdx)
   {
        case UC_INIT_IN_ALL:
              MDrv_6M30_SetInitInLvdsAllData(pBuffer);
 		break;
       case UC_INIT_FINISH:
		break;
        case UC_SET_IN_LVDS_MODE:
              MDrv_6M30_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_SET_IN_LVDS_SWAP:
              MDrv_6M30_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_SET_IN_LVDS_TTL:
              MDrv_6M30_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_INIT_OUT_ALL_1:
              MDrv_6M30_SetInitOutAll1Data(pBuffer);
		break;
        case UC_INIT_OUT_ALL_2:
              MDrv_6M30_SetInitOutAll2Data(pBuffer);
		break;
        case UC_INIT_OUT_ALL_3:
              MDrv_6M30_SetInitOutAll3Data(pBuffer);
		break;
        case UC_SET_OUT_LVDS_MODE:
              MDrv_6M30_SetOutLvdsModeData(pBuffer);
		break;
        case UC_SET_OUT_LVDS_SWAP:
              MDrv_6M30_SetOutLvdsSwapData(pBuffer);
		break;
        case UC_SET_OUT_LVDS_CHANNELTYPE:
              MDrv_6M30_SetOutLvdsChannelTypeData(pBuffer);
		break;
    //==3D mode CMD===
        case UC_SET_3DMODE:
              MDrv_6M30_Set3DModeData(pBuffer);
		break;
        //==2D to 3D mode CMD===
        case UC_SET_2D_TO_3D_MODE:
            MDrv_6M30_Set2Dto3DData(pBuffer);
            break;
	case UC_SET_LREXCHANGE_MODE:
		MDRV_6M30_SetLRExchangeMode(pBuffer);
    //==MFC level CMD ==
        case UC_SET_MFC_LEVEL:
              MDrv_6M30_SetMFClevelData(pBuffer);
		break;
        case UC_SET_MFC_DEMO://  = 0x3020,
              MDrv_6M30_SetMFCDemoData(pBuffer);
		break;
    //==video mute/on CMD ==
        case UC_SET_VIDEO_MUTE:
              MDrv_6M30_SetVideoMuteData(pBuffer);
		break;
        case UC_SET_GAIN_OFFSET:
              MDrv_6M30_SetGainOffsetData(pBuffer);
		break;
        case UC_SET_OSD_WINDOWS_H:
              MDrv_6M30_SetOSDWinHData(pBuffer);
		break;
        case UC_SET_OSD_WINDOWS_V:
              MDrv_6M30_SetOSDWinVData(pBuffer);
		break;
        case UC_SET_PWM_DUTY_PHASE:
              MDrv_6M30_SetPwmDutyPhaseData(pBuffer);
		break;
        case UC_SET_MOD_POWER:
              MDrv_6M30_SetModPowerData(pBuffer);
		break;
        case UC_SET_MOD_MIRROR://= 0x30C0,
              MDrv_6M30_SetMirrorData(pBuffer);
		break;
	case UC_SET_PANEL_3D_ONOFF:
		MDrv_6M30_SetPanel3DOnOff(pBuffer);
		break;
	default:
		break;
   }

    MDrv_Ursa_6M30_CalCheckSum(pBuffer, MFC_CMD_DATA_SUM);
    printf(">>CMD:%x,%x,%x,%x,%x,%x,%x\n",pBuffer[0],pBuffer[1],pBuffer[2],
                       pBuffer[3],pBuffer[4],pBuffer[5],pBuffer[6]);

    bResult = MDrv_6M30_3D_CMD_DataWrite(IIC_DDC2BI_MODE, pBuffer);

    return bResult;

}

BOOLEAN MDrv_Ursa_6M30_PWM_Duty_And_Phase(U8 u8PwmDuty,U16 u16PwmPhase,EN_6M30_CH ePwmCh)
{
	BOOLEAN bResult = FALSE;
       g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmCH= ePwmCh;
       g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty= u8PwmDuty*100;
       g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase= u16PwmPhase*100;

	bResult=MDrv_Ursa_6M30_3D_Cmd(UC_SET_PWM_DUTY_PHASE);
        if(bResult)
        {
            printf("sellect MFC level ok!!!\n");
        }
       else
        {
            printf("sellect MFC level error!!!\n");
        }
	return bResult;
}

BOOLEAN MDrv_Ursa_6M30_MFC_Level( EN_URSA_MEMC_LEVEL eMFClevel )
{
	BOOLEAN bResult = FALSE;
	switch(eMFClevel)
        {
            case EN_URSA_MEMC_OFF:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 0;
                break;
            case EN_URSA_MEMC_LOW:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 1;
                break;
            case EN_URSA_MEMC_MIDDLE:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 2;
                break;
            case EN_URSA_MEMC_HIGH:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 3;
                break;
            default:
                g_UrsaCMDGenSetting.g_MFCLevel.MFClevel= 2;
                break;
        }
        bResult=MDrv_Ursa_6M30_3D_Cmd(UC_SET_MFC_LEVEL);

        if(bResult)
        {
            printf("sellect MFC level ok!!!\n");
        }
       else
        {
            printf("sellect MFC level error!!!\n");
        }
	return bResult;
}

BOOLEAN MDrv_Ursa_6M30_VIDEO_Enalbe( BOOLEAN bEnable )
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
       bResult=MDrv_Ursa_6M30_3D_Cmd(UC_SET_VIDEO_MUTE);

        if(bResult)
        {
            printf("sellect video on/off ok!!!\n");
        }
       else
        {
            printf("sellect video on/off error!!!\n");
        }
	return bResult;
}

BOOLEAN MDrv_Ursa_6M30_LVDS_Enalbe( BOOLEAN bEnable )
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
       bResult=MDrv_Ursa_6M30_3D_Cmd(UC_SET_MOD_POWER);

        if(bResult)
        {
            printf("sellect lvds on/off ok!!!\n");
        }
       else
        {
            printf("sellect lvds on/off error!!!\n");
        }
	return bResult;
}

BOOLEAN MDrv_Ursa_6M30_3D_MODE( PANEL_3D_MODE ePanel3DMode )
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

    bResult = MDrv_Ursa_6M30_3D_Cmd(UC_SET_3DMODE);

    if(bResult)
    {
        printf("sellect 3d mode ok!!!\n");
    }
    else
    {
       printf("sellect 3d mode error!!!\n");
    }

    return bResult;

}

BOOLEAN MDrv_Ursa_6M30_LRExchange_MODE( EN_URSA_LR_TYPE eLRExchangeMode )
{
	BOOLEAN bResult = FALSE;
	switch(eLRExchangeMode)
	{
		default:
		case EN_URSA_LR_L:
			g_UrsaCMDGenSetting.g_3DMode.bLRExchangeMode = 0;
		       break;
		case EN_URSA_LR_R:
			g_UrsaCMDGenSetting.g_3DMode.bLRExchangeMode = 1;
		       break;
	}
	bResult = MDrv_Ursa_6M30_3D_Cmd(UC_SET_LREXCHANGE_MODE);

	if(bResult)
	{
		printf("set 6m30 LR EXChg mode ok!!!\n");
	}
	else
	{
		printf("set 6m30 LR EXChg mode error!!!\n");
	}
	return bResult;
}

BOOLEAN MDrv_Ursa_6M30_MIRROR_MODE( EN_URSA_MIRROR_TYPE eMirrorMode )
{
	BOOLEAN bResult = FALSE;
	switch(eMirrorMode)
	{
		default:
		case EN_URSA_MIRROR_ON:
			g_UrsaCMDGenSetting.g_3DMode.Set6M30MirrorMode= 0;
		break;
		case EN_URSA_MIRROR_OFF:
			g_UrsaCMDGenSetting.g_3DMode.Set6M30MirrorMode = 1;
		break;
	}

	bResult = MDrv_Ursa_6M30_3D_Cmd(UC_SET_MOD_MIRROR);

	if(bResult)
	{
		printf("set 6m30 mirror mode ok!!!\n");
	}
	else
	{
		printf("set 6m30 mirror mode error!!!\n");
	}
	return bResult;
}

BOOLEAN MDrv_Ursa_6M30_Enable2Dto3D( BOOLEAN bEnable )
{
    BOOLEAN bResult = FALSE;

    g_UrsaCMDGenSetting.st2Dto3D.bEnable2Dto3D = bEnable;

    bResult = MDrv_Ursa_6M30_3D_Cmd(UC_SET_2D_TO_3D_MODE);

    if(bResult)
    {
        printf("2D to 3D enable ok!!!\n");
    }
    else
    {
        printf("2D to 3D enable error!!!\n");
    }
	return bResult;
}

//===============================================================
//==============6m30 IIC operating code=================================
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
BOOL MDrv_MFC_6M30_SetSerialDebugMode(MFC_SERIAL_DEBUG_CMD_e cmd)
{
    U32  u32Addr;
    U8   u8Data[5];
    BOOL ret;
    U16 u16SlaveID = (U16)((URSA_I2C_BUS_SEL<<8)|URSA_6M30_IIC_MODE_ADDR);

    u32Addr = 0;

    if (cmd == MFC_SerialDebugEnter)
    {
        u8Data[0] = 0x53;
        u8Data[1] = 0x45;
        u8Data[2] = 0x52;
        u8Data[3] = 0x44;
        u8Data[4] = 0x42;
        ret = MDrv_IIC_WriteBytes(u16SlaveID, 0, NULL, 5, u8Data);
        if (!ret)
        {
   	//     	 dbgprint("MFC_SerialDebugEnter %d   %s\n",__LINE__,__FILE__);
	//		dbgprint("MFC_SerialDebugEnter=============cmd = 0x%x===================\n", cmd);
            return FALSE;
        }
    }
    else
    {
        u8Data[0] = cmd;
        ret = (MDrv_IIC_WriteBytes(u16SlaveID, 0, NULL, 1, u8Data));
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
void MDrv_MFC_6M30_SetSerialDebug(BOOL bOpen)
{
    if(bOpen)
    {
        if(isI2cOpen==FALSE)
        {
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_SerialDebugEnter);
            #if MST6Mxx_I2C_USE_CH2
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_ChNumBit0Disable);
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_ChNumBit1Enable);
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_ChNumBit2Disable);  //Switch to Ch2
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_SetAddrFmt2Byte);
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_EnableNewCfg);
            #else
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_CpuWait);
            #endif
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_I2cUseBus);
            isI2cOpen=TRUE;
        }
    }
    else
    {
        if(isI2cOpen)
        {
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_I2cUseBusN);
            #if MST6Mxx_I2C_USE_CH2
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_ChNumBit0Disable);
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_ChNumBit1Disable);
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_ChNumBit2Disable);
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_SetAddrFmt2Byte);
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_DisableNewCfg);
            #else
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_CpuWaitN);
            #endif
            MDrv_MFC_6M30_SetSerialDebugMode(MFC_SerialDebugExit);
            isI2cOpen=FALSE;
        }
    }
}

void MDrv_MFC_6M30_DebugStart(void)
{
    #if 0//(NEW_URSA_SERIAL_DEBUG_MODE==0)
		MDrv_Ursa_EnterSerialDebugMode(TRUE);
		MDrv_Ursa_CpuWait(TRUE);
		MDrv_Ursa_IICUseBus(TRUE);
    #else
        MDrv_MFC_6M30_SetSerialDebug(TRUE);
    #endif
}
void MDrv_MFC_6M30_DebugEnd(void)
{
    #if 0//(NEW_URSA_SERIAL_DEBUG_MODE==0)
	MDrv_Ursa_IICUseBus(FALSE);
	MDrv_Ursa_CpuWait(FALSE);
	MDrv_Ursa_EnterSerialDebugMode(FALSE);
    #else
        MDrv_MFC_6M30_SetSerialDebug(FALSE);
    #endif
}

BOOLEAN MDrv_Ursa_6M30_Set_Value(U16 u16addr, U8 u8Buf)
{
    BOOLEAN bRet = FALSE;
    U8 u8Databuf[5] = {0, 0, 0, 0, 0};
    U16 u16SlaveID = (U16)((URSA_I2C_BUS_SEL<<8)|URSA_6M30_IIC_MODE_ADDR);
    MDrv_MFC_6M30_DebugStart();
    u8Databuf[0] = 0x10;
    u8Databuf[3] = u8Buf;

    //e.g. address 0x29 11 --> 0x29 11,then we send 0x2911 to 6M10...
    u8Databuf[1] = (U8)(u16addr >> 8);   //the high byte need not move left 1 bit
    u8Databuf[2] = (U8)(u16addr);//the low byte moves left 1 bit, reset bit0 means data low byte
    bRet = MDrv_IIC_WriteBytes(u16SlaveID, 0, NULL, 4, u8Databuf);

    MDrv_MFC_6M30_DebugEnd();
    return bRet;
}

U8 MDrv_Ursa_6M30_Get_Value(U16 U16Addr, BOOLEAN bHigh)
{
    U8 u8Data, u8Databuf[4]={0, 0, 0, 0};
    U16 u16SlaveID = (U16)((URSA_I2C_BUS_SEL<<8)|URSA_6M30_IIC_MODE_ADDR);

    MDrv_MFC_6M30_DebugStart();

    u8Databuf[0] = 0x10;

    if(bHigh == FALSE)
    {
        u8Databuf[1] = (U8)(U16Addr >> 8);//the high byte need not move left 1 bit
        u8Databuf[2] = (U8)(U16Addr);//the low byte moves left 1 bit, reset bit0 means data low byte
    }
    else
    {
        u8Databuf[1] = (U8)(U16Addr >> 8);//the high byte need not move left 1 bit
        u8Databuf[2] = (U8)(U16Addr | 0x01);//the low byte moves left 1 bit, set bit0 means data high byte
    }

    MDrv_IIC_WriteBytes(u16SlaveID, 0, NULL, 3, u8Databuf);
    MDrv_IIC_ReadBytes((u16SlaveID+1), 0, NULL, 1, &u8Data);

    MDrv_MFC_6M30_DebugEnd();

    return u8Data;
}

U8 MDrv_Ursa_6M30_Ver_Main(void)
{
    U16 u16SlaveID = (U16)((URSA_I2C_BUS_SEL<<8)|URSA_6M30_DDC2BI_MODE_ADDR);
    U8 u8Data;

    MDrv_Ursa_6M30_3D_Cmd(UC_GET_FW_VER_MAIN);
    MDrv_IIC_ReadBytes((u16SlaveID+1), 0, NULL, 1, &u8Data);
    return u8Data;
}

U8 MDrv_Ursa_6M30_Ver_Minor(void)
{
    U16 u16SlaveID = (U16)((URSA_I2C_BUS_SEL<<8)|URSA_6M30_DDC2BI_MODE_ADDR);
    U8 u8Data;

    MDrv_Ursa_6M30_3D_Cmd(UC_GET_FW_VER_MINOR);
    MDrv_IIC_ReadBytes((u16SlaveID+1), 0, NULL, 1, &u8Data);
    return u8Data;
}
//===============================================================

#endif
#undef DRV_URSA_6M30_C
