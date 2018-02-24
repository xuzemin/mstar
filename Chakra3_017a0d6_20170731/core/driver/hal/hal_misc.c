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
///@file drvsys.h
///@brief System functions: Initialize, interrupt
///@author MStarSemi Inc.
///
///////////////////////////////////////////////////////////////////////////////

#include "Board.h"

#include "hal_misc.h"

#include "drvGlobal.h"

#include "apiXC.h"


//=========================================================

void MDrv_Write2ByteMask( U32 u32Reg, U16 u16Val, U16 u16Msk )
{
    U16 u16OriVal = __MDrv_Read2Byte(u32Reg);
    __MDrv_Write2Byte( u32Reg, (u16OriVal & ~(u16Msk)) | ((u16Val) & (u16Msk)) );
}

void MDrv_Write4ByteMask( U32 u32Reg, U32 u32Val, U32 u32Msk )
{
    U32 u32OriVal = __MDrv_Read4Byte(u32Reg);
    __MDrv_Write4Byte( u32Reg, (u32OriVal & ~(u32Msk)) | ((u32Val) & (u32Msk)) );
}

//==========================================================
#if 1
//#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)
//   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)
//   )
#define PIU_TIMER0_REG(adr) (RIUBASE_TIMER0+(adr))
#define PIU_TIMER1_REG(adr) (RIUBASE_TIMER1+(adr))

#define PIU_TIMER_EN    0
#define PIU_TIMER_INT   1
#define PIU_TIMER_HIT   2
#define PIU_TIMER_MAX   4
#define PIU_TIMER_CAP   8

void MHAL_PIU_TIMER_Set_Timer_En(U8 u8TimerIdx, BOOL bEn)
{
    if( u8TimerIdx > PIU_TIMER_1 )
        return;

    if( u8TimerIdx == PIU_TIMER_0 )
        MDrv_WriteRegBit(PIU_TIMER0_REG(0x00), bEn, BIT0);//enable timer counting rolled (from 0 to max, then rolled)
    else //if( u8TimerIdx == PIU_TIMER_1 )
        MDrv_WriteRegBit(PIU_TIMER1_REG(0x00), bEn, BIT0);//enable timer counting rolled (from 0 to max, then rolled)
}

void MHAL_PIU_TIMER_Set_Timer_Trig(U8 u8TimerIdx, BOOL bEn)
{
    if( u8TimerIdx > PIU_TIMER_1 )
        return;

    if( u8TimerIdx == PIU_TIMER_0 )
        MDrv_WriteRegBit(PIU_TIMER0_REG(0x00), bEn, BIT1);//Enable timer count one time(from 0 to Max then stop)
    else //if( u8TimerIdx == PIU_TIMER_1 )
        MDrv_WriteRegBit(PIU_TIMER1_REG(0x00), bEn, BIT1);//Enable timer count one time(from 0 to Max then stop)
}

BOOL MHAL_PIU_TIMER_Get_TimerHit(U8 u8TimerIdx)
{
    U8 u8Tmp = 0;

    if( u8TimerIdx > PIU_TIMER_1 )
        return 0;

    if( u8TimerIdx == PIU_TIMER_0 )
        u8Tmp = MDrv_ReadByte(PIU_TIMER0_REG(0x02)); // 0x3022
    else //if( u8TimerIdx == PIU_TIMER_1 )
        u8Tmp = MDrv_ReadByte(PIU_TIMER1_REG(0x02)); // 0x3042

    if( u8Tmp&BIT0 )
        return TRUE;
    else
        return FALSE;
}

void MHAL_PIU_TIMER_Set_TimerMax(U8 u8TimerIdx, U32 u32TimerMax)
{
    if( u8TimerIdx > PIU_TIMER_1 )
        return;

    if( u8TimerIdx == PIU_TIMER_0 )
        MDrv_Write4Byte(PIU_TIMER0_REG(0x04), u32TimerMax); // 0x3024
    else //if( u8TimerIdx == PIU_TIMER_1 )
        MDrv_Write4Byte(PIU_TIMER1_REG(0x04), u32TimerMax); // 0x3044
}

U32 MHAL_PIU_TIMER_Get_CurTick(U8 u8TimerIdx)
{
    U32 u32Tick;
    U32 u32Reg;


    if( u8TimerIdx > PIU_TIMER_1 )
        return 0;

    if( u8TimerIdx == PIU_TIMER_0 )
    {
        u32Reg = PIU_TIMER0_REG(0x08);
        //return MDrv_Read4Byte(PIU_TIMER0_REG(0x08)); //return MDrv_Read4Byte(0x3028);
    }
    else //if( u8TimerIdx == PIU_TIMER_1 )
    {
        u32Reg = PIU_TIMER1_REG(0x08);
        //return MDrv_Read4Byte(PIU_TIMER1_REG(0x08)); //  return MDrv_Read4Byte(0x3048);
    }

    // !!!!! PIU Timer: Must read low byte first to latch the internal reg !!!!!
    u32Tick = MDrv_Read2Byte(u32Reg);
    u32Tick = ((U32)MDrv_Read2Byte(u32Reg+2) << 16) | u32Tick;

    return u32Tick;
}

void MDrv_PIU_TIMER_CAP_Init(void)
{
    //MDrv_Write4Byte(REG_PIU_TIMER0_MAX, 0xFFFFFFFF); // Set max time
    MHAL_PIU_TIMER_Set_TimerMax(PIU_TIMER_1, 0xFFFFFFFF); // Set max time

    //MHAL_PIU_TIMER_Set_Timer_En(PIU_TIMER_1, 0); // Disable timer
    MHAL_PIU_TIMER_Set_Timer_En(PIU_TIMER_1, 1); // Enable timer
}

void MDrv_PIU_TIMER_CAP_Reset(void)
{
    MHAL_PIU_TIMER_Set_TimerMax(PIU_TIMER_1, 0xFFFFFFFF); // Set max time

    MHAL_PIU_TIMER_Set_Timer_En(PIU_TIMER_1, 0); // Disable timer
    MHAL_PIU_TIMER_Set_Timer_En(PIU_TIMER_1, 1); // Enable timer
}

U32 MDrv_PIU_TIMER_CAP_Get_Us(void)
{
    U32 u32Tick = MHAL_PIU_TIMER_Get_CurTick(PIU_TIMER_1);

    return (u32Tick/12);
}

#endif
//====================================================

#define MIU_DTOP_REG(adr)   (MIU_REG_BASE + (adr))

U16 MHAL_MIU_Get_ProtectHitLog(void)
{
    return MDrv_Read2Byte( MIU_DTOP_REG(0xDE) ); // 0x1012DE
}

U32 MHAL_MIU_Get_MVOPAddr(void)
{
    MDrv_WriteByteMask(0x10145F, 0x20, 0x20);
    U32 u32Tmp = (MDrv_Read4Byte(0x101454)*8);
    printf("[mvop=%X,%X]", u32Tmp, (MDrv_Read4Byte(0x101458)*8));
    return u32Tmp;
}

U32 MHAL_MIU_Get_ProtectHitAddr(void)
{
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)     \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)   \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)   \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)   \
   )
   //MHAL_MIU_Get_MVOPAddr();
    return MDrv_Read4Byte( MIU_DTOP_REG(0xDA) ); // 0x1012DA

#elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) )
    return 0xFFFFFFFF;
#else
    return 0xFFFFFFFF;
#endif
}

void MHAL_MIU_ClearProtectHitLog(void)
{
    MDrv_WriteRegBit( MIU_DTOP_REG(0xDE), 1, BIT0);// 0x1012DE
    MDrv_WriteRegBit( MIU_DTOP_REG(0xDE), 0, BIT0);// 0x1012DE
}

void MHAL_MIU_Set_DebugSel(U16 u16Val)
{ //0x10121A => reg_deb_sel
    MDrv_Write2Byte(MIU_DTOP_REG(0x1A),u16Val);
}

U16 MHAL_MIU_Get_DebugPort(void)
{ //0x10121C => reg_r_deb_bus
    return MDrv_Read2Byte(MIU_DTOP_REG(0x1C));
}

//======================================================

U16 MHAL_XC_Get_Fpll_FSM_State(void)
{
//    return MDrv_Read2Byte(0x103154)&0x1FF;
    return MDrv_Read2Byte(RIUBASE_SC3+0x54)&0x1FF;
}

U8 MHAL_XC_Get_FrameCount(void)
{ // h19 h19 4 0 reg_field_num_f2
    return MApi_XC_R2BYTE(0x1232)&0x1F;
}

// h1d	h1d	12	12	reg_auto_no_signal	0	0	1	h0	rw	Auto No signal Enable. This Will Auto Set Current Bank 02[7] = 1 if Mode Change.
MS_BOOL MHAL_XC_Get_IPAutoNoSignalEn(U8 eWindow)
{
    if( eWindow == MAIN_WINDOW )
    {
        return ( MApi_XC_R2BYTEMSK(0x013A, BIT(12) ) )? TRUE:FALSE;
    }
    else
    {
        return ( MApi_XC_R2BYTEMSK(0x033A, BIT(12) ) )? TRUE:FALSE;
    }
}

// h34	9	9	reg_hdmi_vmute_det_en	0	0	1	h0	rw	HDMI V-mute detect enable
MS_BOOL MHAL_XC_Get_IPHdmiAvMuteDetect(U8 eWindow)
{
    if( eWindow == MAIN_WINDOW )
    {
        return ( MApi_XC_R2BYTEMSK(0x0168, BIT(9) ) )? TRUE:FALSE;
    }
    else
    {
        return ( MApi_XC_R2BYTEMSK(0x0368, BIT(9) ) )? TRUE:FALSE;
    }
}

//======================================================
//HDMI_06[10]reg_vmuteblank: "Blanking when AV mute is active.0: Disable.1: Enable."
//HDMI_06[11]reg_en_avmute: "Enable video mute.0: Disable.1: Enable when AVMUTE signal is received."
void MHAL_HDMI_Set_EnAvMute(BOOL bEnable)
{
    if( bEnable )
        //MApi_XC_WriteByteMask(0x10270D, BIT(2)|BIT(3) , BIT(2)|BIT(3));
        MDrv_WriteByteMask(0x10270D, BIT(2)|BIT(3) , BIT(2)|BIT(3));
    else
        //MApi_XC_WriteByteMask(0x10270D, 0 , BIT(2)|BIT(3));
        MDrv_WriteByteMask(0x10270D, 0 , BIT(2)|BIT(3));
}

U8 MHAL_HDMI_Get_EnAvMute(void)
{
    return MDrv_ReadByte(0x10270D)&(BIT(2)|BIT(3));
}

BOOLEAN MHAL_HDMI_Get_AvMuteReceivedStatus(void)
{
    if( MDrv_ReadByte(0x10272A)&BIT0 )
        return 1;
    else
        return 0;
}

//======================================================

void MHAL_ADC_Set_ScartFBDelay(U8 u8FBelay)
{
    MDrv_WriteByteMask(0x102586, u8FBelay, 0x7F);
}

void MHAL_ADC_Set_ScartRGBDelay(U8 u8RGBDelay)
{
    MDrv_WriteByteMask(0x102587, u8RGBDelay, 0x7F);
}
//======================================================

