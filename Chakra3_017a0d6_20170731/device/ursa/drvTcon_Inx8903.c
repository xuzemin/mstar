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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
// File Name: drvTcon_Inx8903.c
// Description: Comunication to IN8903 module
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////
#define DRV_TCON_IN8903_C
#include "drvTcon_Inx8903.h"
#include "drvIIC.h"


#if ENABLE_TCON_IN8903_PROCESS
#define IN8903_MSG(x)   // x

#define _IN8903_CMD_INTERVAL_MS_   (20)

static EN_IN8903_4K2K_MODE m_4K2Kmode = E_IN8903_4K2K_MODE_FULLHD;

IN8903_CMD_GEN_SETTINGS g_IN8903CMDGenSetting;

//IN8903 CMD table
static code IN8903_CMD_DATA m_IN8903CmdData[] =
{
    { 0x00,  0x01,  0x00, 0x00, 0x00, 0x00, 0x00}, // UC_INIT_RX_ALL_1= 0x0001,
    { 0x00,  0x02,  0x00, 0x00, 0x00, 0x00, 0x00}, // UC_INIT_RX_ALL_2= 0x0002,
    { 0x01,  0x00,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_INIT_FINISH= 0x0100,
    { 0x01,  0x01, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_MODE= 0x0101,
    { 0x01,  0x02, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_SWAP= 0x0102,
    { 0x01,  0x03, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_TTL= 0x0103,
    { 0x01,  0x06, 0x00, 0x00, 0x00, 0x00, 0x00}, //UC_SET_RX_RECONFIG= 0x0106,

    { 0x00,  0x10, 0x01,  0x01,  0x01, 0x00, 0x00}, //UC_INIT_OUT_ALL_1= 0x0010,
    { 0x00,  0x11, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_INIT_OUT_ALL_2= 0x0011,
    { 0x00,  0x12, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_INIT_OUT_ALL_3= 0x0012,
    { 0x02,  0x01,  0x00,  0x00,  0x00,  0x00, 0x00}, //UC_SET_OUT_LVDS_MODE= 0x0201,
    { 0x02,  0x02,  0x00,  0x00,  0x00, 0x00, 0x00}, //UC_SET_OUT_LVDS_SWAP= 0x0202,
    { 0x02,  0x03,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_SET_OUT_LVDS_CHANNELTYPE= 0x0203,
    //==3D mode CMD===
    { 0x03,  0x01,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_SET_3DMODE = 0x0301,

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
    { 0x03,  0x1B,  0x00,  0x00,  0x00,  0x00,  0x00}, // UC_WRITE_REGISTER
    { 0x03,  0x1C,  0x00,  0x00,  0x00,  0x00,  0x00}, // UC_WRITE_REGISTER_MASK
    { 0x03,  0x1D,  0x01,  0x00,  0x00,  0x00,  0x00}, // UC_SET_VIDEO_FREEZE
    //==MFC DEMO CMD ==
    { 0x05,  0x01,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_MFC_DEMO_MOD,// =0x0501
    { 0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_LVDS_ON,    //0x not sure, reserved for enum declare
    { 0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_LVDS_OFF,   //0x not sure, reserved for enum declare
    //=================
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
	{ 0x0D,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_EXTEND_AUTO_MUTE_TIME, //0x0D00
	{ 0x0D,  0x0D,  0x00,  0x00,  0x00,  0x00,  0x00},//UC_CUSTOMER_SET_SCREENMUTE_MODE
	{ 0x03,  0x13,  0x00,  0x00,  0x00,  0x00,  0x00},// UC_SET_GAMMA, //0X0814
    { 0xFF,  0xFF, 0x00,  0x00, 0x00, 0x00, 0x00}, //EN_CMD type index Max
};

BOOLEAN MDrv_IN8903_3D_CMD_DataWrite(EN_IN8903_IIC_MODE eIICMode,U8 *u8Buf)
{
    BOOLEAN bRet = FALSE;
    U16 U16SlaveID=0;
    U8 u8ChipAddr;
    if(eIICMode==IIC_DDC2BI_MODE)
         u8ChipAddr=IN8903_DDC2BI_MODE_ADDR;
    else
         u8ChipAddr=IN8903_IIC_MODE_ADDR;

    U16SlaveID |= (U16)((IN8903_I2C_BUS_SEL<<8)|u8ChipAddr);
    //printf("===> IN8903_3D_CMD_DataWrite Start =0x%x\n",U16SlaveID);

#if 1//0
    bRet = MDrv_IIC_WriteBytes(U16SlaveID, 0, NULL, MFC_CMD_DATA_SUM, u8Buf);
#else   //Debug command content
    printf("\n\n\n\r### MDrv_IN8903_3D_CMD_DataWrite( %02x, %02x, %02x, %02x, %02x, %02x, %02x)", *u8Buf, *(u8Buf+1), *(u8Buf+2), *(u8Buf+3), *(u8Buf+4), *(u8Buf+5), *(u8Buf+6));
    bRet = TRUE;
#endif

    IN8903_MSG(printf("===> IN8903_3D_CMD_DataWrite=[%d]\n", bRet));

    return bRet;
}

void MDrv_IN8903_CMD_Iinit( void )
{
     g_IN8903CMDGenSetting.g_InitInLvdsAll.BitNums = 0;
     g_IN8903CMDGenSetting.g_InitInLvdsAll.bsingleCh = FALSE;
     g_IN8903CMDGenSetting.g_InitInLvdsAll.bSwap_evenodd = FALSE;
     g_IN8903CMDGenSetting.g_InitInLvdsAll.bSwap_msblsb = FALSE;
     g_IN8903CMDGenSetting.g_InitInLvdsAll.bSwap_pn = FALSE;
     g_IN8903CMDGenSetting.g_InitInLvdsAll.bTIMode = FALSE;
     g_IN8903CMDGenSetting.g_InitInLvdsAll.bTTL = FALSE;

     g_IN8903CMDGenSetting.g_InitOutAll1.bTIMode = FALSE;
     g_IN8903CMDGenSetting.g_InitOutAll1.bShiftPair = FALSE;
     g_IN8903CMDGenSetting.g_InitOutAll1.bSwapPol = FALSE;
     g_IN8903CMDGenSetting.g_InitOutAll1.bSwapPair =FALSE ;
     g_IN8903CMDGenSetting.g_InitOutAll1.PanelBitNums = 0;
     g_IN8903CMDGenSetting.g_InitOutAll1.bDither8Bits = FALSE;
     g_IN8903CMDGenSetting.g_InitOutAll1.bDitherEn = FALSE;
     g_IN8903CMDGenSetting.g_InitOutAll1.SwapCh = 0;
     g_IN8903CMDGenSetting.g_InitOutAll1.PanelType = 0;
     g_IN8903CMDGenSetting.g_InitOutAll1.PanelChannel = 0;

     g_IN8903CMDGenSetting.g_InitOutAll2.VTotal = 0;
     g_IN8903CMDGenSetting.g_InitOutAll2.De_XStart_high = 0;
     g_IN8903CMDGenSetting.g_InitOutAll2.HTotal = 0;
     g_IN8903CMDGenSetting.g_InitOutAll2.De_XStart_low = 0;

     g_IN8903CMDGenSetting.g_InitOutAll3.PanelHeight = 0;
     g_IN8903CMDGenSetting.g_InitOutAll3.De_YStart_high = 0;
     g_IN8903CMDGenSetting.g_InitOutAll3.PanelWidth = 0;
     g_IN8903CMDGenSetting.g_InitOutAll3.De_YStart_low = 0;

     g_IN8903CMDGenSetting.g_OutLvdsMode.Reserve = 0;
     g_IN8903CMDGenSetting.g_OutLvdsMode.PanelBitNums = 0;
     g_IN8903CMDGenSetting.g_OutLvdsMode.bTIMode = FALSE;
     g_IN8903CMDGenSetting.g_OutLvdsMode.bLvdsSwapPol = FALSE;
     g_IN8903CMDGenSetting.g_OutLvdsMode.bLvdsShiftPair = FALSE;
     g_IN8903CMDGenSetting.g_OutLvdsMode.bLvdsSwapPair = FALSE;

     g_IN8903CMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0;

     g_IN8903CMDGenSetting.g_OutLvdsChannelType.Reserve = 0;
     g_IN8903CMDGenSetting.g_OutLvdsChannelType.PanelChannel = 0;

     g_IN8903CMDGenSetting.g_3DMode.Set3Dmode = 0;
     g_IN8903CMDGenSetting.g_3DMode.Reserve = 0;
     g_IN8903CMDGenSetting.g_3DMode.bL_Only = FALSE;

     g_IN8903CMDGenSetting.g_MFCLevel.MFClevel = 0;

     g_IN8903CMDGenSetting.g_VideoMute.Reserve = 0;
     g_IN8903CMDGenSetting.g_VideoMute.bMute = FALSE;

     g_IN8903CMDGenSetting.g_GainOffset.AdjustIdx = 0;
     g_IN8903CMDGenSetting.g_GainOffset.wAdjustValue = 0;

     g_IN8903CMDGenSetting.g_OSDWinH.Reserve = 0;
     g_IN8903CMDGenSetting.g_OSDWinH.WinID = 0;
     g_IN8903CMDGenSetting.g_OSDWinH.bWinEn = FALSE;
     g_IN8903CMDGenSetting.g_OSDWinH.WinHStart = 0;
     g_IN8903CMDGenSetting.g_OSDWinH.WinHEnd = 0;

     g_IN8903CMDGenSetting.g_OSDWinV.Reserve = 0;
     g_IN8903CMDGenSetting.g_OSDWinV.WinID = 0;
     g_IN8903CMDGenSetting.g_OSDWinV.bWinEn = FALSE;
     g_IN8903CMDGenSetting.g_OSDWinV.WinVStart = 0;
     g_IN8903CMDGenSetting.g_OSDWinV.WinVEnd = 0;

     g_IN8903CMDGenSetting.g_PwmDutyPhase.Reserve = 0;
     g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmCH= 0;
     g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmDuty= 0;
     g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmPhase= 0;

     g_IN8903CMDGenSetting.g_ModPower.Reserve = 0;
     g_IN8903CMDGenSetting.g_ModPower.bOnOff = FALSE;
}

void MDrv_IN8903_SetData_General( U8* u8Buf,  U8* pu8Data)
{
    if((u8Buf == NULL)||(pu8Data == NULL))
        return;

    memcpy(&(u8Buf[2]), pu8Data, 5);
}

void MDrv_IN8903_SetInitInLvdsAllData( U8 *u8Buf )
{
     if(g_IN8903CMDGenSetting.g_InitInLvdsAll.bsingleCh)
	 u8Buf[2] |= BIT7;
     if(g_IN8903CMDGenSetting.g_InitInLvdsAll.bTIMode)
	 u8Buf[2] |= BIT6;
     u8Buf[2] |= ((U8)(g_IN8903CMDGenSetting.g_InitInLvdsAll.BitNums)<<4);
     if(g_IN8903CMDGenSetting.g_InitInLvdsAll.bSwap_evenodd)
	 u8Buf[2] |= BIT3;
     if(g_IN8903CMDGenSetting.g_InitInLvdsAll.bSwap_pn)
	 u8Buf[2] |= BIT2;
     if(g_IN8903CMDGenSetting.g_InitInLvdsAll.bSwap_msblsb)
	 u8Buf[2] |= BIT1;
     if(g_IN8903CMDGenSetting.g_InitInLvdsAll.bTTL)
	 u8Buf[2] |= BIT0;
}

void MDrv_IN8903_SetInitOutAll1Data( U8 *u8Buf )
{
     if(g_IN8903CMDGenSetting.g_InitOutAll1.bTIMode)
	 u8Buf[2] |= BIT7;
     if(g_IN8903CMDGenSetting.g_InitOutAll1.bShiftPair)
	 u8Buf[2] |= BIT6;
     if(g_IN8903CMDGenSetting.g_InitOutAll1.bSwapPol)
	 u8Buf[2] |= BIT5;
     if(g_IN8903CMDGenSetting.g_InitOutAll1.bSwapPair)
	 u8Buf[2] |= BIT4;
     if(g_IN8903CMDGenSetting.g_InitOutAll1.bDither8Bits)
	 u8Buf[2] |= BIT1;
     if(g_IN8903CMDGenSetting.g_InitOutAll1.bDitherEn)
	 u8Buf[2] |= BIT0;
      u8Buf[2] |= ((U8)(g_IN8903CMDGenSetting.g_InitOutAll1.PanelBitNums)<<4);

     u8Buf[3] = g_IN8903CMDGenSetting.g_InitOutAll1.SwapCh;

     u8Buf[4] |= ((U8)(g_IN8903CMDGenSetting.g_InitOutAll1.PanelType)<<4);
     u8Buf[4] |= (U8)g_IN8903CMDGenSetting.g_InitOutAll1.PanelChannel;
}

void MDrv_IN8903_SetInitOutAll2Data( U8 *u8Buf )
{
     u8Buf[2] = (U8)((g_IN8903CMDGenSetting.g_InitOutAll2.VTotal)>>8);
     u8Buf[3] = (U8)g_IN8903CMDGenSetting.g_InitOutAll2.VTotal;

     u8Buf[4] |= ((U8)(g_IN8903CMDGenSetting.g_InitOutAll2.De_XStart_high)<<4);
     u8Buf[4] |= (U8)((g_IN8903CMDGenSetting.g_InitOutAll2.HTotal)>>8);

     u8Buf[5] = (U8)g_IN8903CMDGenSetting.g_InitOutAll2.HTotal;

     u8Buf[6] = g_IN8903CMDGenSetting.g_InitOutAll2.De_XStart_low;
}

void MDrv_IN8903_SetInitOutAll3Data( U8 *u8Buf )
{
     u8Buf[2] = (U8)((g_IN8903CMDGenSetting.g_InitOutAll3.PanelHeight)>>8);
     u8Buf[3] = (U8)g_IN8903CMDGenSetting.g_InitOutAll3.PanelHeight;

     u8Buf[4] |= ((U8)(g_IN8903CMDGenSetting.g_InitOutAll3.De_YStart_high)<<4);
     u8Buf[4] |= (U8)((g_IN8903CMDGenSetting.g_InitOutAll3.PanelWidth)>>8);

     u8Buf[5] = (U8)g_IN8903CMDGenSetting.g_InitOutAll3.PanelWidth;

     u8Buf[6] = g_IN8903CMDGenSetting.g_InitOutAll3.De_YStart_low;
}

void MDrv_IN8903_SetOutLvdsModeData( U8 *u8Buf )
{
     if(g_IN8903CMDGenSetting.g_OutLvdsMode.bTIMode)
	 u8Buf[5] |= BIT3;
     if(g_IN8903CMDGenSetting.g_OutLvdsMode.bLvdsSwapPol)
	 u8Buf[5] |= BIT2;
     if(g_IN8903CMDGenSetting.g_OutLvdsMode.bLvdsShiftPair)
	 u8Buf[5] |= BIT1;
     if(g_IN8903CMDGenSetting.g_OutLvdsMode.bLvdsSwapPair)
	 u8Buf[5] |= BIT0;
      u8Buf[5] |= ((U8)(g_IN8903CMDGenSetting.g_OutLvdsMode.PanelBitNums)<<4);
 }

void MDrv_IN8903_SetOutLvdsSwapData( U8 *u8Buf )
{
      u8Buf[4] = g_IN8903CMDGenSetting.g_OutLvdsSwap.LvdsSwapCh;
}

void MDrv_IN8903_SetOutLvdsChannelTypeData( U8 *u8Buf )
{
      u8Buf[2] = g_IN8903CMDGenSetting.g_OutLvdsChannelType.PanelChannel;
}

void MDrv_IN8903_Set3DModeData( U8 *u8Buf ,U8 *pU8Data)
{
    if(pU8Data == NULL)
        return;

    u8Buf[2] = *pU8Data;
    u8Buf[4] = *(pU8Data+2);
}

void MDrv_IN8903_SetVideoFreeze( U8 *u8Buf ,U8 *pU8Data)
{
    u8Buf[2] = *pU8Data;
    u8Buf[4] = *(pU8Data+2);
}
void MDrv_IN8903_Set2Dto3DData( U8 *u8Buf )
{
    g_IN8903CMDGenSetting.st2Dto3D.u8Gain = 8;
    g_IN8903CMDGenSetting.st2Dto3D.u8OffSet = 128;
    u8Buf[2] = (u8Buf[2]&0xFE)|(g_IN8903CMDGenSetting.st2Dto3D.bEnable2Dto3D);
    u8Buf[2] = (u8Buf[2]&0xFD)|((g_IN8903CMDGenSetting.st2Dto3D.bEnableConcave)<<1);
    u8Buf[3] = (u8Buf[3]&0x0F)|((g_IN8903CMDGenSetting.st2Dto3D.u8Gain)<<4);
    u8Buf[4] = g_IN8903CMDGenSetting.st2Dto3D.u8OffSet;
    u8Buf[5] = g_IN8903CMDGenSetting.st2Dto3D.u8OffSet;
}

void MDrv_IN8903_SetMFClevelData( U8 *u8Buf )
{
     u8Buf[2] = g_IN8903CMDGenSetting.g_MFCLevel.MFClevel;
}

void MDrv_IN8903_SetVideoMuteData( U8 *u8Buf )
{
     u8Buf[2] = (U8)g_IN8903CMDGenSetting.g_VideoMute.bMute;
}

void MDrv_IN8903_SetGainOffsetData( U8 *u8Buf )
{
  //   u8Buf[0] = u8Buf[0] ;
   //  u8Buf[1] = u8Buf[1] ;
     u8Buf[2] = g_IN8903CMDGenSetting.g_GainOffset.AdjustIdx;
     u8Buf[3] = (U8)((g_IN8903CMDGenSetting.g_GainOffset.wAdjustValue)>>8);
     u8Buf[4] = (U8)(g_IN8903CMDGenSetting.g_GainOffset.wAdjustValue);
}

void MDrv_IN8903_SetPwmDutyPhaseData( U8 *u8Buf )
{
     u8Buf[2] = g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmCH;
     u8Buf[3] = (U8)((g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmDuty)>>8);
     u8Buf[4] = (U8)(g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmDuty);
     u8Buf[5] = (U8)((g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmPhase)>>8);
     u8Buf[6] = (U8)(g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmPhase);
}

void MDrv_IN8903_SetModPowerData( U8 *u8Buf )
{
     if(g_IN8903CMDGenSetting.g_ModPower.bOnOff)
    {
       u8Buf[2] |= BIT0;
    }
}

void MDrv_IN8903_SetMFCDemoModeData( U8 *u8Buf )
{
     u8Buf[2] = g_IN8903CMDGenSetting.stMFCDemoMode.MFCDemoMode;
#if 0//(ENABLE_MFC_DEMO_4K2K == 1)
    //set demo line color
    u8Buf[4] = 2;
    u8Buf[5] = 3;
#endif
}

void MDrv_IN8903_SetInVideoSize( U8 *u8Buf ,U8 *pU8Data )
{

    u8Buf[2] = *pU8Data;
    u8Buf[3] = *(pU8Data+1);
    u8Buf[4] = *(pU8Data+2);
    u8Buf[5] = *(pU8Data+3);

}

void MDrv_IN8903_SetRxSwitchToHdmi( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}
BOOL MDrv_IN8903_SetVideoSize(const U16 u16VideoWidth,  U16 u16VideoHeight)
{
    U8 videoData[4] = {0};

    videoData[0] = (U8)((u16VideoWidth>>8) & 0xF);
    videoData[1] = (U8)(u16VideoWidth & 0xFF);
    videoData[2] = (U8)((u16VideoHeight>>8) & 0xF);
    videoData[3] = (U8)(u16VideoHeight & 0xFF);

    return MDrv_IN8903_Cmd(UC_SET_IN_VIDEO_SIZE,videoData);
}

void MDrv_IN8903_SetAceSharpness( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;

}

void MDrv_IN8903_SetAceBrightness( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;       //R
    u8Buf[3] = *(pU8Data+1); //G
    u8Buf[4] = *(pU8Data+2); //B
}

void MDrv_IN8903_SetAceContrast( U8 *u8Buf ,U8 *pU8Data )
{
   u8Buf[2] = *pU8Data;

}

void MDrv_IN8903_SetAceHue( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;

}

void MDrv_IN8903_SetAceSaturation( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}

void MDrv_IN8903_SetAceColorTempParam( U8 *u8Buf ,U8 *pU8Data )
{

    u8Buf[2] = *pU8Data;
    u8Buf[3] = *(pU8Data+1);
    u8Buf[4] = *(pU8Data+2);

}

void MDrv_IN8903_SetAceDlc( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}

void MDrv_IN8903_Set_Level_NR( U8 *u8Buf ,U8 *pU8Data )
{
   u8Buf[2] = *pU8Data;
}


BOOL SetIN8903Mute(IN8903_MUTE_TYPE eIN8903_Mute_Type)
{
    U8 cmd=0;
    cmd = (U8)eIN8903_Mute_Type;
    return MDrv_IN8903_Cmd(UC_SET_MUTE,&cmd);

}

void MDrv_IN8903_SetMMPhotoByPass(U8 *u8Buf,BOOL bByPass)
{
    IN8903_MSG(printf("SetMMPhotoByPass....\n"));
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

void MDrv_IN8903_Enable3DFormatAutoDetect(U8 *u8Buf ,BOOL bEnable)
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

void MDrv_IN8903_SetMute( U8 *u8Buf ,U8 *pU8Data )
{
    IN8903_MUTE_TYPE enMuteType = (IN8903_MUTE_TYPE)*pU8Data;
    IN8903_MSG(printf("IN8903 mute type = [%d]\n",enMuteType));
    switch(enMuteType)
    {
        case EN_VIDEO_ONLY_MUTE: // 0
                u8Buf[2] = 0x02;
                break;

        case EN_VIDEO_ONLY_UNMUTE:// 1
                u8Buf[2] = 0x00;
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

void MDrv_IN8903_SetFreezeType( U8 *u8Buf ,U8 *pU8Data )
{
    u8Buf[2] = *pU8Data;
}

void MDrv_IN8903_SetSrDemoMode( U8 *u8Buf ,U8 *pU8Data )
{
      u8Buf[2] = *pU8Data;
}

void MDrv_IN8903_SetGamma( U8 *u8Buf ,U8 *pU8Data )
{
      u8Buf[2] = *pU8Data;
}

void MDrv_IN8903_CalCheckSum(U8 *pBuf, U8 u8BufLen )
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
BOOLEAN MDrv_IN8903_Cmd( UC_CMD_TYPE eCmdIdx,U8 *pU8Data)
{

    BOOLEAN bResult = FALSE;
    U8 pBuffer[MFC_CMD_DATA_SUM]={0,0,0,0,0,0,0};

   if(eCmdIdx<=UC_SET_GAMMA)
   {
       memcpy(pBuffer,&(m_IN8903CmdData[eCmdIdx]),MFC_CMD_DATA_SUM);
   }
   //printf(">>>eCmdIdx==%d>>>\n",eCmdIdx);
   if((pBuffer[0]==0xFF)&&(pBuffer[1]==0xFF))
       return FALSE;

   switch(eCmdIdx)
   {
        case UC_INIT_RX_ALL_1:
        case UC_INIT_RX_ALL_2:
        case UC_WRITE_REGISTER:
        case UC_WRITE_REGISTER_MASK:
        case UC_EXTEND_AUTO_MUTE_TIME:
        case UC_CUSTOMER_SET_SCREENMUTE_MODE:
            MDrv_IN8903_SetData_General(pBuffer, pU8Data);
 		break;

        case UC_SET_RX_RECONFIG:
            //Do nothing. This command has no parameter except command id.
 		break;

        case UC_INIT_FINISH:
		break;

        case UC_SET_IN_LVDS_MODE:
              MDrv_IN8903_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_SET_IN_LVDS_SWAP:
              MDrv_IN8903_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_SET_IN_LVDS_TTL:
              MDrv_IN8903_SetInitInLvdsAllData(pBuffer);
		break;
        case UC_INIT_OUT_ALL_1:
              MDrv_IN8903_SetInitOutAll1Data(pBuffer);
		break;
        case UC_INIT_OUT_ALL_2:
              MDrv_IN8903_SetInitOutAll2Data(pBuffer);
		break;
        case UC_INIT_OUT_ALL_3:
              MDrv_IN8903_SetInitOutAll3Data(pBuffer);
		break;
        case UC_SET_OUT_LVDS_MODE:
              MDrv_IN8903_SetOutLvdsModeData(pBuffer);
		break;
        case UC_SET_OUT_LVDS_SWAP:
              MDrv_IN8903_SetOutLvdsSwapData(pBuffer);
		break;
        case UC_SET_OUT_LVDS_CHANNELTYPE:
            MDrv_IN8903_SetOutLvdsChannelTypeData(pBuffer);
		break;
    //==3D mode CMD===
        case UC_SET_3DMODE:
            MDrv_IN8903_Set3DModeData(pBuffer,pU8Data);
		break;
   //==2D to 3D mode CMD===
        case UC_SET_2D_TO_3D_MODE:
            MDrv_IN8903_Set2Dto3DData(pBuffer);
            break;
        case UC_SET_VIDEO_FREEZE:
            MDrv_IN8903_SetVideoFreeze(pBuffer,pU8Data);
            break;
   //==MFC level CMD ==
        case UC_SET_MFC_LEVEL:
              MDrv_IN8903_SetMFClevelData(pBuffer);
		break;
    //==video mute/on CMD ==
        case UC_SET_VIDEO_MUTE:
              MDrv_IN8903_SetVideoMuteData(pBuffer);
		break;
        case UC_SET_GAIN_OFFSET:
              MDrv_IN8903_SetGainOffsetData(pBuffer);
		break;
        case UC_SET_PWM_DUTY_PHASE:
              MDrv_IN8903_SetPwmDutyPhaseData(pBuffer);
		break;
        case UC_SET_MOD_POWER:
              MDrv_IN8903_SetModPowerData(pBuffer);
		break;
        case UC_SET_MFC_DEMO_MOD:
            MDrv_IN8903_SetMFCDemoModeData(pBuffer);
            break;
        case UC_SET_LVDS_ON:
        case UC_SET_LVDS_OFF:
            break;

        case UC_SET_RX_SWITCH_TO_HDMI:
           MDrv_IN8903_SetRxSwitchToHdmi(pBuffer,pU8Data);
            break;

        case UC_SET_IN_VIDEO_SIZE:
            MDrv_IN8903_SetInVideoSize(pBuffer,pU8Data);
            break;

        case UC_SET_ACE_SHARPNESS:
            MDrv_IN8903_SetAceSharpness(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_BRIGHTNESS:
            MDrv_IN8903_SetAceBrightness(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_CONTRAST:
            MDrv_IN8903_SetAceContrast(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_HUE:
            MDrv_IN8903_SetAceHue(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_SATURATION:
            MDrv_IN8903_SetAceSaturation(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_COLOR_TEMP_PARAM:
            MDrv_IN8903_SetAceColorTempParam(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_COLOR_TEMP_LOAD:
            break;
        case UC_SET_ACE_DLC:
            MDrv_IN8903_SetAceDlc(pBuffer,pU8Data);
            break;
        case UC_SET_ACE_LEVEL_NR:
            MDrv_IN8903_Set_Level_NR(pBuffer,pU8Data);
            break;
        case UC_SET_MUTE:
            MDrv_IN8903_SetMute(pBuffer,pU8Data);
            break;
        case UC_SET_VIDEO_OSD_FREEZE:
            MDrv_IN8903_SetFreezeType(pBuffer,pU8Data);
            break;
        case UC_SET_SR_DEMO_MODE:
           MDrv_IN8903_SetSrDemoMode(pBuffer,pU8Data);
            break;
        case UC_SET_GAMMA:
           MDrv_IN8903_SetGamma(pBuffer,pU8Data);
            break;
         case UC_SET_4K2K_MODE:
           // bResult=MDrv_IN8903_SetIN89034K2KType((EN_IN8903_4K2K_MODE)(*pU8Data));
            break;
         case UC_GET_4K2K_MODE:
            //bResult=MDrv_IN8903_GetIN89034K2KType(pU8Data);
            break;
         case UC_SET_PHOTO_BYPASS_ENABLE:
            MDrv_IN8903_SetMMPhotoByPass(pBuffer,TRUE);
         break;
         case UC_SET_PHOTO_BYPASS_DISABLE:
            MDrv_IN8903_SetMMPhotoByPass(pBuffer,FALSE);
         break;
         case UC_ENABLE_3D_AUTO_DETECT:
            MDrv_IN8903_Enable3DFormatAutoDetect(pBuffer,TRUE);
         break;
         case UC_DISABLE_3D_AUTO_DETECT:
            MDrv_IN8903_Enable3DFormatAutoDetect(pBuffer,FALSE);
         break;
         break;
	default:
		break;
   }

    MDrv_IN8903_CalCheckSum(pBuffer, MFC_CMD_DATA_SUM);
    IN8903_MSG(printf(">>CMD:%x,%x,%x,%x,%x,%x,%x\n",pBuffer[0],pBuffer[1],pBuffer[2],
                       pBuffer[3],pBuffer[4],pBuffer[5],pBuffer[6]));
   if(bResult==FALSE)
   {
       bResult = MDrv_IN8903_3D_CMD_DataWrite(IIC_DDC2BI_MODE, pBuffer);
   }
   MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

    return bResult;

}

BOOLEAN MDrv_IN8903_PWM_Duty_And_Phase(U8 u8PwmDuty,U16 u16PwmPhase,EN_IN8903_CH ePwmCh)
{
	BOOLEAN bResult = FALSE;
       g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmCH= ePwmCh;
       g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmDuty= u8PwmDuty*100;
       g_IN8903CMDGenSetting.g_PwmDutyPhase.PwmPhase= u16PwmPhase*100;

	bResult=MDrv_IN8903_Cmd(UC_SET_PWM_DUTY_PHASE,NULL);
        if(bResult)
        {
            IN8903_MSG(printf("select MFC level ok!!!\n"));
        }
       else
        {
            IN8903_MSG(printf("select MFC level error!!!\n"));
        }
	return bResult;
}

BOOLEAN MDrv_IN8903_MFC_Level( EN_IN8903_MEMC_LEVEL eMFClevel )
{
	BOOLEAN bResult = FALSE;
	switch(eMFClevel)
        {
            case EN_IN8903_MEMC_OFF:
                g_IN8903CMDGenSetting.g_MFCLevel.MFClevel= 0;
                break;
            case EN_IN8903_MEMC_LOW:
                g_IN8903CMDGenSetting.g_MFCLevel.MFClevel= 1;
                break;
            case EN_IN8903_MEMC_MIDDLE:
                g_IN8903CMDGenSetting.g_MFCLevel.MFClevel= 2;
                break;
            case EN_IN8903_MEMC_HIGH:
                g_IN8903CMDGenSetting.g_MFCLevel.MFClevel= 3;
                break;
            default:
                g_IN8903CMDGenSetting.g_MFCLevel.MFClevel= 2;
                break;
        }
        bResult=MDrv_IN8903_Cmd(UC_SET_MFC_LEVEL,NULL);

        if(bResult)
        {
            IN8903_MSG(printf("select MFC level ok!!!\n"));
        }
       else
        {
            IN8903_MSG(printf("select MFC level error!!!\n"));
        }
	return bResult;
}

BOOLEAN MDrv_IN8903_VIDEO_Enable( BOOLEAN bEnable )
{
    BOOLEAN bResult = FALSE;
    if(bEnable)
    {
        g_IN8903CMDGenSetting.g_VideoMute.bMute= 1;
    }
    else
    {
        g_IN8903CMDGenSetting.g_VideoMute.bMute= 0;
    }

    bResult=MDrv_IN8903_Cmd(UC_SET_VIDEO_MUTE,NULL);

    if(bResult)
    {
        IN8903_MSG(printf("select video on/off ok!!!\n"));
    }
    else
    {
        IN8903_MSG(printf("select video on/off error!!!\n"));
    }
    return bResult;
}

BOOLEAN MDrv_IN8903_LVDS_Enable( BOOLEAN bEnable )
{
    BOOLEAN bResult = FALSE;
    if(bEnable)
    {
        g_IN8903CMDGenSetting.g_ModPower.bOnOff= 1;
    }
    else
    {
        g_IN8903CMDGenSetting.g_ModPower.bOnOff= 0;
    }
    bResult=MDrv_IN8903_Cmd(UC_SET_MOD_POWER,NULL);

    if(bResult)
    {
        IN8903_MSG(printf("select lvds on/off ok!!!\n"));
    }
    else
    {
        IN8903_MSG(printf("select lvds on/off error!!!\n"));
    }
    return bResult;
}

BOOLEAN MDrv_IN8903_3D_MODE( IN8903_PANEL_3D_FORMAT ePanel3DFmt )
{
	BOOLEAN bResult = FALSE;

    U8 au8Data[5] = {0};

    au8Data[0] = (U8)(ePanel3DFmt & 0xF0);
    #if 1//WITHOUT_LR_FLAG
    au8Data[2] = 1;
    #endif

    bResult = MDrv_IN8903_Cmd(UC_SET_3DMODE, &(au8Data[0]));

    if(bResult)
    {
        IN8903_MSG(printf("select 3d mode ok!!!\n"));
    }
    else
    {
       IN8903_MSG(printf("select 3d mode error!!!\n"));
    }

    return bResult;

}

BOOLEAN MDrv_IN8903_Enable2Dto3D( BOOLEAN bEnable )
{
    BOOLEAN bResult = FALSE;

    g_IN8903CMDGenSetting.st2Dto3D.bEnable2Dto3D = bEnable;

    bResult = MDrv_IN8903_Cmd(UC_SET_2D_TO_3D_MODE,NULL);

    if(bResult)
    {
        IN8903_MSG(printf("2D to 3D enable ok!!!\n"));
    }
    else
    {
        IN8903_MSG(printf("2D to 3D enable error!!!\n"));
    }
	return bResult;
}
BOOLEAN MDrv_IN8903_Get4K2KType(U8 *pU8Data)
{
     IN8903_MSG(printf("getIN89034K2KType:m_4K2Kmode:%d\n",(U8)m_4K2Kmode));
    *pU8Data = (U8)m_4K2Kmode;
     return TRUE;

}
#if 0
BOOLEAN MDrv_IN8903_Set4K2KType(EN_IN8903_4K2K_MODE enMode)
{
    BOOL bResult = FALSE;
    IN8903_MSG(printf("4KX2K enMode=%d\n",enMode));
    switch (enMode)
    {
        case E_IN8903_4K2K_MODE_4K1K:
            bResult |=SetIN8903Mute (EN_VIDEO_ONLY_MUTE);
            bResult |= MDrv_IN8903_SetVideoSize(WIDTH_4K2K,HEIGHT_4K1K);
            bResult |=SetIN8903Mute (EN_VIDEO_ONLY_UNMUTE);
            break;
        case E_IN8903_4K2K_MODE_4K2K:
            bResult |=SetIN8903Mute (EN_VIDEO_ONLY_MUTE);
            bResult |=MDrv_IN8903_SetVideoSize(WIDTH_4K2K,HEIGHT_4K2K);
            bResult |=SetIN8903Mute (EN_VIDEO_ONLY_UNMUTE);
            break;
        case E_IN8903_4K2K_MODE_HDMI4K2K:
            bResult |=SetIN8903Mute (EN_VIDEO_ONLY_MUTE);
            bResult |=MDrv_IN8903_SetVideoSize(WIDTH_4K2K,HEIGHT_4K2K);
            bResult |=SetIN8903Mute (EN_VIDEO_ONLY_UNMUTE);
            break;
        case E_IN8903_4K2K_MODE_FULLHD:
        default:
            bResult |=SetIN8903Mute (EN_ALL_MUTE);
            bResult |= MDrv_IN8903_SetVideoSize(WIDTH_FULLHD,HEIGHT_FULLHD);
            bResult |=SetIN8903Mute (EN_ALL_UNMUTE);
            break;
    }

    if (bResult)
    {
        m_4K2Kmode = enMode;
    }
    else
    {
        IN8903_MSG(printf("---->set 4KX2K Mode fail<-----\n"));
    }

    IN8903_MSG(printf("=======>SetIN89034K2KType(%d) finished<========\n",m_4K2Kmode));

return bResult;
}
#endif
//===============================================================
//==============IN8903 IIC operating code=================================
//===============================================================


void MDrv_IN8903_Set_4K_2K_Mode(U8 bOnOff)
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
    MDrv_IN8903_Cmd(UC_SET_3DMODE,pU8Databuf);
}
void MDrv_IN8903_Set_Video_Freeze(U8 bOnOff)
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
    MDrv_IN8903_Cmd(UC_SET_VIDEO_FREEZE,pU8Databuf);
}

#if 0
void  MDrv_IN8903_LoadColorTempSetting(MS_COLOR_TEMP_SETTING1*  Value )
{
   	U8 ColorTemp[4] = {0};

	ColorTemp[0] = 0;//E_CMD_REDGAIN
	ColorTemp[1] = (Value->RedColorGain<<3)&0xff;
	ColorTemp[2] = Value->RedColorGain>>5;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 1;//E_CMD_BLUEGAIN
	ColorTemp[1] = (Value->BlueColorGain<<3)&0xff;
	ColorTemp[2] = Value->BlueColorGain>>5;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 2;//E_CMD_GREENGAIN
	ColorTemp[1] = (Value->GreenColorGain<<3)&0xff;
	ColorTemp[2] = Value->GreenColorGain>>5;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 3;//E_CMD_REDOFFSET
	ColorTemp[1] = (Value->RedColorOffset<<3)&0xff;
	ColorTemp[2] = Value->RedColorOffset>>5;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 4;//E_CMD_BLUEOFFSET
	ColorTemp[1] = (Value->BlueColorOffset<<3)&0xff;
	ColorTemp[2] = Value->BlueColorOffset>>5;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 5;//E_CMD_GREENOFFSET
	ColorTemp[1] = (Value->GreenColorOffset<<3)&0xff;
	ColorTemp[2] = Value->GreenColorOffset>>5;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_LOAD,ColorTemp);
}

void  MDrv_IN8903_LoadColorTempSetting_Disable(void )
{
  	U8 ColorTemp[4] = {0};

	ColorTemp[0] = 0;//E_CMD_REDGAIN
	ColorTemp[2] = 4;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 1;//E_CMD_BLUEGAIN
	ColorTemp[2] = 4;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 2;//E_CMD_GREENGAIN
	ColorTemp[2] = 4;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 3;//E_CMD_REDOFFSET
	ColorTemp[2] = 4;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 4;//E_CMD_BLUEOFFSET
	ColorTemp[2] = 4;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	ColorTemp[0] = 5;//E_CMD_GREENOFFSET
	ColorTemp[2] = 4;
	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_PARAM,ColorTemp);
	MsOS_DelayTask(_IN8903_CMD_INTERVAL_MS_);

	MDrv_IN8903_Cmd(UC_SET_ACE_COLOR_TEMP_LOAD,ColorTemp);
}
#endif

BOOLEAN MDrv_IN8903_WriteRegister(U32 u32Addr, U8 u8Value)
{
	BOOLEAN bResult = FALSE;
    U8 au8Data[5] = {0};

    au8Data[0] = (u32Addr & 0x00FF0000) >> 16;
    au8Data[1] = (u32Addr & 0x0000FF00) >> 8;
    au8Data[2] = (u32Addr & 0x000000FF);

    au8Data[3] = u8Value;

    bResult = MDrv_IN8903_Cmd(UC_WRITE_REGISTER, au8Data);

    return bResult;
}

BOOLEAN MDrv_IN8903_WriteRegisterMask(U32 u32Addr, U8 u8Value, U8 u8Mask)
{
	BOOLEAN bResult = FALSE;
    U8 au8Data[5] = {0};

    au8Data[0] = (u32Addr & 0x00FF0000) >> 16;
    au8Data[1] = (u32Addr & 0x0000FF00) >> 8;
    au8Data[2] = (u32Addr & 0x000000FF);

    au8Data[3] = u8Value;
    au8Data[4] = u8Mask;

    bResult = MDrv_IN8903_Cmd(UC_WRITE_REGISTER_MASK, au8Data);

    return bResult;
}


BOOLEAN MDrv_IN8903_SetVx1RxConfig(EN_VX1_LANE_NUM eLaneNum)
{
	BOOLEAN bResult = FALSE;

    U8 au8Data_8_1[5] = {0x02, 0x00, 0x40, 0xFF, 0x00};
    U8 au8Data_4_1[5] = {0x02, 0x00, 0x00, 0x55, 0x00};
    U8 au8Data_2_1[5] = {0x02, 0x00, 0x00, 0x11, 0x00};

    U8 au8Data_8_2[5] = {0x00, 0x40, 0x62, 0x51, 0x73};
    U8 au8Data_4_2[5] = {0x00, 0x00, 0x02, 0x01, 0x03};
    U8 au8Data_2_2[5] = {0x00, 0x00, 0x00, 0x01, 0x00};

    U8 au8Data_1[5] = {0};
    U8 au8Data_2[5] = {0};

    switch(eLaneNum)
    {
        case EN_VX1_LANE_NUM_8LANE:
            memcpy(au8Data_1, au8Data_8_1, sizeof(au8Data_2_1));
            memcpy(au8Data_2, au8Data_8_2, sizeof(au8Data_2_2));
            break;

        case EN_VX1_LANE_NUM_4LANE:
            memcpy(au8Data_1, au8Data_4_1, sizeof(au8Data_4_1));
            memcpy(au8Data_2, au8Data_4_2, sizeof(au8Data_4_2));
            break;

        case EN_VX1_LANE_NUM_2LANE:
            memcpy(au8Data_1, au8Data_2_1, sizeof(au8Data_2_1));
            memcpy(au8Data_2, au8Data_2_2, sizeof(au8Data_2_2));
            break;

        default:
            printf("\n\r Invalid Vx1 lane number = %d @ %s-%d", eLaneNum, __FUNCTION__, __LINE__);
            return FALSE;
    }

    bResult = MDrv_IN8903_Cmd(UC_INIT_RX_ALL_1, au8Data_1);


    bResult &= MDrv_IN8903_Cmd(UC_INIT_RX_ALL_2, au8Data_2);

    if(bResult)
    {
        IN8903_MSG(printf("set vx1 rx config_1 ok!!!\n"));
    }
    else
    {
        IN8903_MSG(printf("set vx1 rx config_1 error!!!\n"));
    }

    return bResult;

}

BOOLEAN MDrv_IN8903_SetAutoMuteExtendTime(U8 u8DelayTimeX100)
{
	BOOLEAN bResult = FALSE;
    U8 au8Data[5] = {0};

    au8Data[0] = u8DelayTimeX100;

    bResult = MDrv_IN8903_Cmd(UC_EXTEND_AUTO_MUTE_TIME, au8Data);

    return bResult;
}
BOOLEAN MDrv_IN8903_SetScreenMuteMode(EN_SCREEN_MUTE_MODE eMutemode)
{
    BOOLEAN bResult = FALSE;
    U8 au8Data[5] = {0};

    au8Data[0] = (U8)eMutemode;

    bResult = MDrv_IN8903_Cmd(UC_CUSTOMER_SET_SCREENMUTE_MODE, au8Data);

    return bResult;
}

void MDrv_IN8903_SwitchMode(EN_IN8903_4K2K_MODE e4K2KMode, IN8903_PANEL_3D_FORMAT e3DFmt)
{
    EN_VX1_LANE_NUM eLaneNum = EN_VX1_LANE_NUM_8LANE;

    switch(e4K2KMode)
    {
        case E_IN8903_4K2K_MODE_FULLHD:
            //Simplified as only FHD@60Hz input
            eLaneNum = EN_VX1_LANE_NUM_2LANE;
        break;

        case E_IN8903_4K2K_MODE_4K2K:
            //Simplified as only 4K2K@60Hz input
            eLaneNum = EN_VX1_LANE_NUM_8LANE;
        break;

        default:
            printf("\n\r Invalid 4K2K mode = %d", (U8)e4K2KMode);
            return;
    }

    MDrv_IN8903_SetVx1RxConfig(eLaneNum);

    MDrv_IN8903_Cmd(UC_SET_RX_RECONFIG, NULL);

    MDrv_IN8903_WriteRegister(0x1027C2, 0xEE);

    MDrv_IN8903_WriteRegister(0x102740, 0x71);

    MDrv_IN8903_WriteRegister(0x1027C3, 0xEE);

    //Set input resolution
    switch(e4K2KMode)
    {
        case E_IN8903_4K2K_MODE_FULLHD:
            MDrv_IN8903_SetVideoSize(WIDTH_FULLHD, HEIGHT_FULLHD);
            break;

        case E_IN8903_4K2K_MODE_4K2K:
            MDrv_IN8903_SetVideoSize(WIDTH_4K2K, HEIGHT_4K2K);
            break;

        default:
            printf("\n\r Invalid 4K2K mode = %d", (U8)e4K2KMode);
            return;
    }

    //Set 3D mode
    MDrv_IN8903_3D_MODE(e3DFmt);

    MDrv_IN8903_WriteRegisterMask(0x130004, 0x40, 0x40);

    MDrv_IN8903_WriteRegisterMask(0x130004, 0x00, 0x40);
}

#endif

#undef DRV_TCON_IN8903_C
