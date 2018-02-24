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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#define MHAL_PQ_ADAPTIVE_C

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
// Common Definition
#include "MsCommon.h"
#include "MsOS.h"
// Internal Definition
#include "color_reg.h"
#include "drvXC_IOPort.h"
#include "apiXC.h"
#include "apiXC_Dlc.h"
#include "mhal_pq_adaptive.h"
//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define MSIF_ADAPTIVE_LIB_CODE_C            {'A','D','A','P','T','I','V','E','_'}
#define MSIF_ADAPTIVE_VERSION_C             {'0','0','0','0','0','1'}


#ifndef UNUSED //to avoid compile warnings...
#define UNUSED(var) (void)((var) = (var))
#endif

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
extern MS_U16 _u16PQSrcType_DBK_Detect[PQ_MAX_WINDOW]; //For Auto_DBK SW driver used
static MS_U16 _u16PQPre_SrcType = 255;          //For Auto_DBK SW driver used
static MS_BOOL data_read = true;                //For Auto_DBK SW driver used
static MS_BOOL _bIsHDSource = true;             //For Check HD mode
static MS_BOOL _bAnyCandenceEnable = true;
//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

/******************************************************************************/
///Get control register for adaptive tuning function
///@return MS_U8: Control status
/******************************************************************************/
MS_U8 MDrv_SC_get_adaptive_ctrl(void)
{
    MS_U8 u8Ctrl;

    u8Ctrl = (MS_U8)MApi_XC_R2BYTEMSK(REG_SC_BK22_7C_L, 0xFF);

    return u8Ctrl;
}

/******************************************************************************/
///Get control register for adaptive tuning function
///@return MS_U8: Control status
/******************************************************************************/
MS_U8 MDrv_SC_get_adaptive_ctrl2(void)
{
    MS_U8 u8Ctrl;

    u8Ctrl = (MS_U8)(MApi_XC_R2BYTEMSK(REG_SC_BK22_7C_L, 0xFF00) >> 8);

    return u8Ctrl;
}

/******************************************************************************/
///Get control register for adaptive tuning function
///@return MS_U8: Control status
/******************************************************************************/
MS_U8 MDrv_SC_get_adaptive_ctrl3(void)
{
    MS_U8 u8Ctrl;

    u8Ctrl = (MS_U8) (MApi_XC_R2BYTEMSK(REG_SC_BK30_01_L, 0x8000) >> 8);

    return u8Ctrl;
}

/******************************************************************************/
///Get control register for adaptive tuning function
///@return MS_U8: Control status
/******************************************************************************/
MS_U8 MDrv_SC_get_adaptive_ctrl4(void)
{
    MS_U8 u8Ctrl;

    u8Ctrl = (MS_U8)(MS_U8)MApi_XC_R2BYTEMSK(REG_SC_BK22_7E_L, 0xFF);

    return u8Ctrl;
}

/******************************************************************************/
///Read motion value (F2 motion status)
///@return MS_U8: Motion value
/******************************************************************************/
MS_U32 MDrv_SC_read_motion_value1(void)
{
    MS_U32 u32MotionValue;
    MS_U32 u32RegMadi_1C, u32RegMadi_1B, u32RegMadi_1A;

    u32RegMadi_1C = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_0E_L, 0x3F);
    u32RegMadi_1B = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_0D_L, 0xFF00);
    u32RegMadi_1A = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_0D_L, 0x00FF);

    u32RegMadi_1C = u32RegMadi_1C * 0x10000UL;

    u32MotionValue = (u32RegMadi_1C + u32RegMadi_1B + u32RegMadi_1A)  ;

    DRVSCA_DBG(printf("MotionValue = 0x%lx\n", u32MotionValue));

    return u32MotionValue;
}

/******************************************************************************/
///Read motion value (Motion count status)
///@return MS_U8: Motion value
/******************************************************************************/
MS_U32 MDrv_SC_read_motion_value2(void)
{
    MS_U32 u32MotionValue;

    u32MotionValue = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK0A_18_L, 0xFFF) + (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK0A_1A_L, 0x7F);

    return u32MotionValue;
}

/******************************************************************************/
///Read motion value (Motion count status)
///@return MS_U32: Motion value
/******************************************************************************/
MS_U32 MDrv_SC_read_motion_value3(void)
{
    MS_U32 u32MotionValue;

    u32MotionValue = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK0A_18_L, 0x0FFF);

    return u32MotionValue;
}

//-------------------------------------------------------------------------------------------------
/// Read motion value (Motion count status)
/// @return MS_U8: Motion value
//-------------------------------------------------------------------------------------------------
MS_U8 Hal_PQ_GetCurrentMotionValue(void)
{
    MS_U8 u8MotionValue;

    u8MotionValue  = (MS_U8)((MApi_XC_R2BYTEMSK(REG_SC_BK22_0E_L, 0x3F) << 2) |
                             (MApi_XC_R2BYTEMSK(REG_SC_BK22_0D_L, 0xC000) >> 6));

    return u8MotionValue;
}

/******************************************************************************/
///Read VCnt value
///@return MS_U8: VCnt value
/******************************************************************************/
MS_U8 MDrv_SC_read_v_cnt(void)
{
    MS_U8 u8VCnt;

    u8VCnt = (MS_U8)(MApi_XC_R2BYTEMSK(REG_SC_BK22_0E_L, 0xC0) >> 6);
    return u8VCnt;
}


#define MF_Gain            30
MS_U32 MDrv_SC_T12_UC_SmallMoving(void)
{
    MS_U32 before_MC_feather;
    MS_U32 nonMV0_Comfirm, MV_Contradict;
    MS_U32 MovingFeather, MV_Confirm;
    static MS_U32 PrevMV_Confirm = 0;

    before_MC_feather = MApi_XC_R2BYTE(REG_SC_BK2A_77_L) ;
    nonMV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    MV_Contradict = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    MV_Confirm = (nonMV0_Comfirm + MV_Contradict) >> 1;

    MV_Confirm = (PrevMV_Confirm * 3 + MV_Confirm) >> 2;
    PrevMV_Confirm = MV_Confirm;

    if(MV_Confirm > (before_MC_feather * MF_Gain))
        MovingFeather = MV_Confirm - ((before_MC_feather * MF_Gain)) ;
    else
        MovingFeather = 0;

    return MovingFeather;  // "Big": in seach range "Small": out of seach range
}

#define OOSRF_Gain            4
#define OOSRF_Power         2
MS_U32 MDrv_SC_T12_UC_InSearchRange_Feather(void)
{
    MS_U32 before_MC_feather, after_MC_feather;
    MS_U32 MC_OOSRF;
    static MS_U32 Prev_before_MC_feather = 0;
    static MS_U32 Prev_after_MC_feather = 0;

    before_MC_feather = MApi_XC_R2BYTE(REG_SC_BK2A_77_L) ;
    after_MC_feather = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);

    before_MC_feather = (Prev_before_MC_feather * 3 + before_MC_feather) >> 2;
    Prev_before_MC_feather = before_MC_feather;

    after_MC_feather = (Prev_after_MC_feather * 3 + after_MC_feather) >> 2;
    Prev_after_MC_feather = after_MC_feather;

    if(before_MC_feather > (after_MC_feather * OOSRF_Gain) >> OOSRF_Power)
        MC_OOSRF = before_MC_feather - ((after_MC_feather * OOSRF_Gain) >> OOSRF_Power) ;
    else
        MC_OOSRF = 0;

    return MC_OOSRF;  // "Big": in seach range "Small": out of seach range
}

#define OOSRMC_Gain         20
MS_U32 MDrv_SC_T12_UC_InSearchRange_MvComfirm(void)
{
    MS_U32 MV0_Comfirm,  nonMV0_Comfirm, MV_Contradict;
    static MS_U32 Prev_MV0_Comfirm = 0;
    static MS_U32 Prev_nonMV0_Comfirm = 0;
    static MS_U32 Prev_MV_Contradict = 0;
    MS_U32 MV_Comfirm, MC_OOSRMC;

    MV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    nonMV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    MV_Contradict = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    MV0_Comfirm = (Prev_MV0_Comfirm * 3 + MV0_Comfirm) >> 2;
    Prev_MV0_Comfirm = MV0_Comfirm;

    nonMV0_Comfirm = (Prev_nonMV0_Comfirm * 3 + nonMV0_Comfirm) >> 2;
    Prev_nonMV0_Comfirm = nonMV0_Comfirm;

    MV_Contradict = (Prev_MV_Contradict * 3 + MV_Contradict) >> 2;
    Prev_MV_Contradict = MV_Contradict;

    MV_Comfirm = MV0_Comfirm + nonMV0_Comfirm;

    if(MV_Comfirm > (MV_Contradict * OOSRMC_Gain))
        MC_OOSRMC = MV_Comfirm - MV_Contradict * OOSRMC_Gain;
    else
        MC_OOSRMC = 0;

    return MC_OOSRMC;  // "Big": in seach range "Small": out of seach range

}

#define Confirm_Gain         5
MS_U8 MDrv_SC_UC_InSearchRange_MR_Offset(void)
{
    MS_U32 MV0_Comfirm,  nonMV0_Comfirm, MV_Contradict;
    static MS_U32 Prev_MV0_Comfirm = 0;
    static MS_U32 Prev_nonMV0_Comfirm = 0;
    static MS_U32 Prev_MV_Contradict = 0;
    MS_U32 MV_Comfirm;
    MS_U8 MR_Offset;

    MV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    nonMV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    MV_Contradict = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    MV0_Comfirm = (Prev_MV0_Comfirm * 3 + MV0_Comfirm) >> 2;
    Prev_MV0_Comfirm = MV0_Comfirm;

    nonMV0_Comfirm = (Prev_nonMV0_Comfirm * 3 + nonMV0_Comfirm) >> 2;
    Prev_nonMV0_Comfirm = nonMV0_Comfirm;

    MV_Contradict = (Prev_MV_Contradict * 3 + MV_Contradict) >> 2;
    Prev_MV_Contradict = MV_Contradict;

    MV_Comfirm = MV0_Comfirm + nonMV0_Comfirm;

    if(MV_Comfirm > (MV_Contradict * Confirm_Gain))
        MR_Offset = nonMV0_Comfirm;
    else
        MR_Offset = 0;

    return MR_Offset;
}

#define ISR_NONMV0_Gain         15
MS_U32 MDrv_SC_T12_UC_InSearchRange_nonMv0Comfirm(void)
{
    MS_U32 MV0_Comfirm,  nonMV0_Comfirm, MV_Contradict;
    static MS_U32 Prev_MV0_Comfirm = 0;
    static MS_U32 Prev_nonMV0_Comfirm = 0;
    static MS_U32 Prev_MV_Contradict = 0;
    MS_U32 MV_Comfirm, Comfirm_Value;

    MV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    nonMV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    MV_Contradict = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    MV0_Comfirm = (Prev_MV0_Comfirm * 3 + MV0_Comfirm) >> 2;
    Prev_MV0_Comfirm = MV0_Comfirm;

    nonMV0_Comfirm = (Prev_nonMV0_Comfirm * 3 + nonMV0_Comfirm) >> 2;
    Prev_nonMV0_Comfirm = nonMV0_Comfirm;

    MV_Contradict = (Prev_MV_Contradict * 3 + MV_Contradict) >> 2;
    Prev_MV_Contradict = MV_Contradict;

    MV_Comfirm = nonMV0_Comfirm;

    if(MV_Comfirm > (MV_Contradict * ISR_NONMV0_Gain))
        Comfirm_Value = MV_Comfirm - MV_Contradict * ISR_NONMV0_Gain;
    else
        Comfirm_Value = 0;

    return Comfirm_Value;  // "Big": in seach range "Small": out of seach range

}


#define ComplexOffset_MaxValue 0x06
#define ComplexOffset_MinValue 0x00
void MDrv_SC_T12_UCDi_ComplexOffset(MS_U32 OOSRMC, MS_U32 OOSRF, MS_U32 ISR_NONMV0)
{
    static MS_U16 ComplexOffset = ComplexOffset_MaxValue;

    UNUSED(OOSRMC);
    UNUSED(OOSRF);

    if(ISR_NONMV0 > 1000)
    {
        if(ComplexOffset > ComplexOffset_MinValue)
            ComplexOffset--;
        else
            ComplexOffset = ComplexOffset_MinValue;
    }
    else
    {
        if(ComplexOffset < ComplexOffset_MaxValue)
            ComplexOffset++;
        else
            ComplexOffset = ComplexOffset_MaxValue;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)ComplexOffset << 4, 0x00F0);
}

#define OP1_HisWeight_MaxValue 0x0E
#define OP1_HisWeight_MinValue 0x04
#define A5_HIS_MOTION_TH 0x0A
void MDrv_SC_A5_UCDi_OP1_HisWeight(const MS_U32 u32MotionValue,const MS_U32 FeatherSum)
{
    static MS_U32 reg_his_weight = OP1_HisWeight_MinValue;
    static MS_U32 u32MotionValue_prev = 0;

    if( u32MotionValue_prev < u32MotionValue )
        u32MotionValue_prev = ((u32MotionValue_prev*3 )+ u32MotionValue ) >> 2;
    else
        u32MotionValue_prev = u32MotionValue;

    if( u32MotionValue_prev < A5_HIS_MOTION_TH )
    {
            reg_his_weight = OP1_HisWeight_MinValue;
    }
    else
    {
        if( reg_his_weight < OP1_HisWeight_MaxValue )
            reg_his_weight++;
        else
            reg_his_weight = OP1_HisWeight_MaxValue;
    }

    if(FeatherSum > 0x3500)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, OP1_HisWeight_MinValue, 0x000e);  // history weight = 6
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, reg_his_weight, 0x000E);
    }
}

#define FeatherValueGain_MaxValue 0x02
#define FeatherValueGain_MinValue 0x02
void MDrv_SC_T12_UCDi_FeatherValueGain(MS_U32 OOSRMC, MS_U32 OOSRF, MS_U32 ISR_NONMV0)
{
    static MS_U16 FeatherValue = FeatherValueGain_MaxValue;

    UNUSED(OOSRMC);
    UNUSED(OOSRF);

    if(ISR_NONMV0 > 1000)
    {
        if(FeatherValue > FeatherValueGain_MinValue)
            FeatherValue--;
        else
            FeatherValue = FeatherValueGain_MinValue;
    }
    else
    {
        if(FeatherValue < FeatherValueGain_MaxValue)
            FeatherValue++;
        else
            FeatherValue = FeatherValueGain_MaxValue;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2D_L, (MS_U16)FeatherValue << 12, 0xF000);
}

#define W2SadGain_MaxValue 0x0C
#define W2SadGain_MinValue 0x08
void MDrv_SC_T12_UCDi_W2SadGain(MS_U32 OOSRMC, MS_U32 OOSRF, MS_U32 ISR_NONMV0)
{
    static MS_U16 W2SadGain = W2SadGain_MinValue;

    UNUSED(OOSRMC);
    UNUSED(OOSRF);

    if(ISR_NONMV0 > 1000)
    {
        if(W2SadGain < W2SadGain_MaxValue)
            W2SadGain++;
        else
            W2SadGain = W2SadGain_MaxValue;
    }
    else
    {
        if(W2SadGain > W2SadGain_MinValue)
            W2SadGain--;
        else
            W2SadGain = W2SadGain_MinValue;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2D_L, (MS_U16)W2SadGain << 8, 0x0F00);

}

#define VerticalMovingUdRatio_MaxValue 0x08
#define VerticalMovingUdRatio_MinValue 0x07
void MDrv_SC_T12_UCDi_VerticalMovingUdRatio(MS_U32 OOSRMC, MS_U32 OOSRF, MS_U32 ISR_NONMV0)
{
    static MS_U16 VerticalMovingUdRatioValue = VerticalMovingUdRatio_MaxValue;

    UNUSED(OOSRMC);
    UNUSED(ISR_NONMV0);

    if( OOSRF > 0x300 )
    {
        if(VerticalMovingUdRatioValue > VerticalMovingUdRatio_MinValue)
            VerticalMovingUdRatioValue--;
        else
            VerticalMovingUdRatioValue = VerticalMovingUdRatio_MinValue;
    }
    else
    {
        if(VerticalMovingUdRatioValue < VerticalMovingUdRatio_MaxValue)
            VerticalMovingUdRatioValue++;
        else
            VerticalMovingUdRatioValue = VerticalMovingUdRatio_MaxValue;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, (MS_U16)VerticalMovingUdRatioValue, 0x000F);
}

#define KFC_8bitMotionGain_MaxValue 0x08
#define KFC_8bitMotionGain_MinValue 0x04 //0 have feather issue.
void MDrv_SC_T12_KFC_8bitMotionGain(MS_U32 SmallMoving)
{
    static MS_U16 KFC_8bitMotionGainValue = KFC_8bitMotionGain_MaxValue;

    if(SmallMoving > 500)
    {
        if(KFC_8bitMotionGainValue > KFC_8bitMotionGain_MinValue)
            KFC_8bitMotionGainValue--;
        else
            KFC_8bitMotionGainValue = KFC_8bitMotionGain_MinValue;
    }
    else
    {
        if(KFC_8bitMotionGainValue < KFC_8bitMotionGain_MaxValue)
            KFC_8bitMotionGainValue++;
        else
            KFC_8bitMotionGainValue = KFC_8bitMotionGain_MaxValue;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_3B_L, (MS_U16)KFC_8bitMotionGainValue << 4, 0x00F0);
}

#define UCDi_EODiWGain_MaxValue 0x0F
#define UCDi_EODiWGain_MinValue 0x00
void MDrv_SC_T12_UCDi_EODiWGain(MS_U32 OOSRMC, MS_U32 OOSRF, MS_U32 ISR_NONMV0)
{
    static MS_U16 EODiWGainValue = UCDi_EODiWGain_MaxValue;

    UNUSED(OOSRMC);

    if((ISR_NONMV0 > 1000) && (OOSRF > 50))
    {
        if(EODiWGainValue > UCDi_EODiWGain_MinValue)
            EODiWGainValue--;
        else
            EODiWGainValue = UCDi_EODiWGain_MinValue;
    }
    else
    {
        if(EODiWGainValue < UCDi_EODiWGain_MaxValue)
            EODiWGainValue++;
        else
            EODiWGainValue = UCDi_EODiWGain_MaxValue;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)EODiWGainValue << 12, 0xF000);
}

#define UCDi_HistoryRatio_MaxValue 0x07
#define UCDi_HistoryRatio_MinValue 0x04
void MDrv_SC_T12_UCDi_HistoryRatio(MS_U32 OOSRMC, MS_U32 OOSRF, MS_U32 ISR_NONMV0)
{
    static MS_U16 HistoryRatioValue = UCDi_HistoryRatio_MaxValue;

    UNUSED(OOSRMC);

    if((ISR_NONMV0 > 1000) && (OOSRF > 50))
    {
        if(HistoryRatioValue > UCDi_HistoryRatio_MinValue)
            HistoryRatioValue--;
        else
            HistoryRatioValue = UCDi_HistoryRatio_MinValue;
    }
    else
    {
        if(HistoryRatioValue < UCDi_HistoryRatio_MaxValue)
            HistoryRatioValue++;
        else
            HistoryRatioValue = UCDi_HistoryRatio_MaxValue;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)HistoryRatioValue << 12, 0xF000);
}

#define KFC_EODIW_GAIN_MAX 4
#define KFC_EODIW_GAIN_MIN 0
void MDrv_SC_A5_KFC_EODiW(const MS_U32 IsVerticalMoving)
{
    MS_U32 Statistics_cplx_pixel;
    static MS_U32 Statistics_cplx_pixel_iir = KFC_EODIW_GAIN_MIN;
    static MS_U32 reg_kfc_eodiw_gain = KFC_EODIW_GAIN_MAX ;

    Statistics_cplx_pixel = ((Statistics_cplx_pixel_iir*3 )+ MApi_XC_R2BYTE(REG_SC_BK2A_7F_L) ) >> 2;
    Statistics_cplx_pixel_iir = Statistics_cplx_pixel;

    if( (IsVerticalMoving < 0x150) && (Statistics_cplx_pixel_iir > 0x1000) )
    {
        if( reg_kfc_eodiw_gain > KFC_EODIW_GAIN_MIN )
            reg_kfc_eodiw_gain--;
        else
            reg_kfc_eodiw_gain  = KFC_EODIW_GAIN_MIN;
    }
    else
    {
        if( reg_kfc_eodiw_gain < KFC_EODIW_GAIN_MAX )
            reg_kfc_eodiw_gain++;
        else
            reg_kfc_eodiw_gain = KFC_EODIW_GAIN_MAX;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)reg_kfc_eodiw_gain << 12, 0xF000);
}

#define SONYC_KFC_EN_MAX 1
#define SONYC_KFC_EN_MIN 0
#define SONYC_CPLX_GAIN_MAX 4
#define SONYC_CPLX_GAIN_MIN 0

void MDrv_SC_A5_SonyChurch(const MS_U32 IsVerticalMoving, const MS_U32 IsHorizontalMoving, const MS_U32 u32MotionValue, const MS_BOOL bL107_en)
{
  static MS_U32 reg_kfc_en = SONYC_KFC_EN_MAX ;
  static MS_U32 reg_mcdi_cplx_gain = SONYC_CPLX_GAIN_MAX;
  MS_U32 u32_mvc, u32_mvu, u32_mvd;
    u32_mvc     = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32_mvu     = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32_mvd     = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);

    if ( (u32_mvu > u32_mvc*8) && (u32_mvd > u32_mvc*8) && u32_mvu > 0x200 && u32_mvd > 0x200 ) // Book1 : sony vertical moving character
    {
        if( reg_mcdi_cplx_gain > SONYC_CPLX_GAIN_MIN )
            reg_mcdi_cplx_gain--;
        else
            reg_mcdi_cplx_gain = SONYC_CPLX_GAIN_MIN;

        if( reg_kfc_en > SONYC_KFC_EN_MIN )
            reg_kfc_en--;
        else
            reg_kfc_en = SONYC_KFC_EN_MIN;
    }
  //IsHorizontalMoving=IsHorizontalMoving;
    else if( (IsVerticalMoving > 0xF0) && (IsHorizontalMoving < 1) && (u32MotionValue > 0x40000) )
    {
        if( reg_mcdi_cplx_gain > SONYC_CPLX_GAIN_MIN )
            reg_mcdi_cplx_gain--;
        else
            reg_mcdi_cplx_gain = SONYC_CPLX_GAIN_MIN;

        if( reg_kfc_en > SONYC_KFC_EN_MIN )
            reg_kfc_en--;
        else
            reg_kfc_en = SONYC_KFC_EN_MIN;
    }
    else
    {
        if( reg_mcdi_cplx_gain < SONYC_CPLX_GAIN_MAX )
            reg_mcdi_cplx_gain++;
        else
            reg_mcdi_cplx_gain = SONYC_CPLX_GAIN_MAX;

        if( reg_kfc_en < SONYC_KFC_EN_MAX )
            reg_kfc_en++;
        else
            reg_kfc_en = SONYC_KFC_EN_MAX;
    }

    if( !bL107_en )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_04_L, (MS_U16)reg_kfc_en<<1, 0x0002);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)reg_mcdi_cplx_gain<<8, 0x0F00);
    }
}



#define L107_FEATHER_GAIN_MAX 2
#define L107_FEATHER_GAIN_MIN 0
#define L107_CPLX_OFFSET_MAX 6
#define L107_CPLX_OFFSET_MIN 0
#define L107_CPLX_GAIN_MAX 15
#define L107_CPLX_GAIN_MIN 4
MS_BOOL MDrv_SC_A5_L107(const MS_U32 IsVerticalMoving, const MS_U32 IsHorizontalMoving, const MS_U32 total_feather, const MS_U32 mvComfirm, const MS_U32 colorSum,const MS_U32 u32MotionValue, const MS_U32 uComplex )
{
static MS_U32 reg_mcdi_feather_gain = L107_FEATHER_GAIN_MAX ;
static MS_U32 reg_mcdi_cplx_offset = L107_CPLX_OFFSET_MAX ;
static MS_U32 reg_mcdi_cplx_gain = L107_CPLX_GAIN_MIN ;
MS_BOOL bL107_en;

if((IsVerticalMoving < 20) && (IsHorizontalMoving < 200) && (total_feather < 100)
    && (mvComfirm > 200) && (colorSum > 200) && (u32MotionValue > 0x3500) && (uComplex < 0x700))
{
    bL107_en = TRUE;

    if( reg_mcdi_feather_gain > L107_FEATHER_GAIN_MIN )
        reg_mcdi_feather_gain--;
    else
        reg_mcdi_feather_gain = L107_FEATHER_GAIN_MIN;

    if( reg_mcdi_cplx_offset > L107_CPLX_OFFSET_MIN )
        reg_mcdi_cplx_offset--;
    else
        reg_mcdi_cplx_offset = L107_CPLX_OFFSET_MIN;

    if( reg_mcdi_cplx_gain < L107_CPLX_GAIN_MAX )
        reg_mcdi_cplx_gain++;
    else
        reg_mcdi_cplx_gain = L107_CPLX_GAIN_MAX;
}
else
{
    bL107_en = FALSE;

    if( reg_mcdi_feather_gain < L107_FEATHER_GAIN_MAX )
        reg_mcdi_feather_gain++;
    else
        reg_mcdi_feather_gain = L107_FEATHER_GAIN_MAX;

    if( reg_mcdi_cplx_offset < L107_CPLX_OFFSET_MAX )
        reg_mcdi_cplx_offset++;
    else
        reg_mcdi_cplx_offset = L107_CPLX_OFFSET_MAX;

    if( reg_mcdi_cplx_gain > L107_CPLX_GAIN_MIN )
        reg_mcdi_cplx_gain--;
    else
        reg_mcdi_cplx_gain = L107_CPLX_GAIN_MIN;
}

MApi_XC_W2BYTEMSK(REG_SC_BK2A_2D_L, (MS_U16)reg_mcdi_feather_gain<<12, 0xF000); // 2 to 0
MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)reg_mcdi_cplx_offset<<4, 0x00F0);// 6 to 0
MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)reg_mcdi_cplx_gain<<8, 0x0F00);// 4 to F

return bL107_en;
}

MS_U32 MDrv_SC_A5_ComplexSum(void)
{
    static MS_U32 IsComplex_iir = 0xFFFF;
    MS_U32 IsComplex;

    IsComplex = MApi_XC_R2BYTE(REG_SC_BK2A_7F_L);

    IsComplex = (IsComplex_iir*3 + IsComplex ) >> 2;
    IsComplex_iir = IsComplex;

    return IsComplex_iir;
}

MS_U32 MDrv_SC_A5_KFC_IsVerticalMoving( void )
{
    MS_U32 u32_mvc, u32_mvu, u32_mvd;
    MS_U32 me_vertical;
    static MS_U32 IsVerticalMoving_iir = 0;

    u32_mvc     = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32_mvu     = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32_mvd     = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);

    if ( (u32_mvu > u32_mvc*8) && (u32_mvd > u32_mvc*8) ) // Book1 : sony vertical moving character
    {
        me_vertical = (u32_mvu + u32_mvd )/2 - (u32_mvc)*8;
    }
    else if ((u32_mvu > u32_mvc) && (u32_mvu > u32_mvd) /*&& (u32_mvu > 0x200*/)
    {
        if( u32_mvu > (u32_mvc+u32_mvd)/2 )
            me_vertical = (u32_mvu - (u32_mvc+u32_mvd)/2);
        else
            me_vertical = 0;
    }
    else if((u32_mvd > u32_mvc) && (u32_mvd > u32_mvu) )
    {
        if( u32_mvd > (u32_mvc+u32_mvu)/2 )
            me_vertical = (u32_mvd - (u32_mvc+u32_mvu)/2);
        else
            me_vertical = 0;
    }
    else
    {
        me_vertical = 0;
    }

    if( me_vertical > 255 )
        me_vertical = 255;

    me_vertical = (IsVerticalMoving_iir*3 + me_vertical ) >> 2;
    IsVerticalMoving_iir = me_vertical;

    return me_vertical;
}

MS_U32 MDrv_SC_A5_IsHorizontalMoving(void)
{
    MS_U32 u32_mvc, u32_mvu, u32_mvd;
    MS_U32 me_horizontal;
    static MS_U32 IsHorizontalMoving_iir = 0;

    u32_mvc     = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32_mvu     = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32_mvd     = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);

    if ((u32_mvc > u32_mvu) && (u32_mvc > u32_mvd) )
    {
        if( u32_mvc > (u32_mvu+u32_mvd)/2 )
            me_horizontal = (u32_mvc - (u32_mvu+u32_mvd)/2);
        else
            me_horizontal = 0;
    }
    else
    {
        me_horizontal = 0;
    }

    if( me_horizontal > 255 )
        me_horizontal = 255;

    me_horizontal = (IsHorizontalMoving_iir*3 + me_horizontal ) >> 2;
    IsHorizontalMoving_iir = me_horizontal;

    return me_horizontal;
}


MS_U32 MDrv_SC_A5_ColorPixelSum(void)
{
    MS_U32 colorSum;
    static MS_U32 colorSum_iir = 0;

    colorSum  = MApi_XC_R2BYTE(REG_SC_BK1A_6E_L);
    colorSum  = colorSum / 8;

    if( colorSum > 255 )
        colorSum = 255;

    colorSum = ((colorSum_iir*3 )+ colorSum ) >> 2;
    colorSum_iir = colorSum;

    return colorSum_iir;
}

MS_U32 MDrv_SC_A5_TotalFeather(void)
{
    MS_U32 mv0_feather, nonMv0_feather;
    MS_U32 total_feather;
    static MS_U32 total_feather_iir = 255;

    mv0_feather      = MApi_XC_R2BYTE(REG_SC_BK2A_77_L);
    nonMv0_feather   = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);

    total_feather = ( mv0_feather + nonMv0_feather ) / 4;

    if( total_feather > 255 )
        total_feather = 255;

    total_feather = ((total_feather_iir*3 )+ total_feather ) >> 2;
    total_feather_iir = total_feather;

    return total_feather_iir;
}

MS_U32 MDrv_SC_TotalFeather_Sum(void)
{
    MS_U32 mv0_feather, nonMv0_feather;
    MS_U32 total_feather;
    static MS_U32 total_feather_iir = 0;

    mv0_feather      = MApi_XC_R2BYTE(REG_SC_BK2A_77_L);
    nonMv0_feather   = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);

    total_feather =  mv0_feather + nonMv0_feather;

    total_feather = ((total_feather_iir*3 )+ total_feather ) >> 2;
    total_feather_iir = total_feather;

    return total_feather_iir;
}

#define TOTAL_MV_TIME 10
MS_U32 MDrv_SC_A5_TotalMvComfirm(void)
{
    MS_U32 mv0, nonMv0, notFound;
    MS_U32 total_mv, mvComfirm;
    static MS_U32 mvComfirm_iir = 0;

    mv0      = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    nonMv0   = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    notFound   = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    total_mv = mv0 + nonMv0;

    if( total_mv > (notFound*TOTAL_MV_TIME))
        mvComfirm =   total_mv - notFound*TOTAL_MV_TIME;
    else
        mvComfirm = 0;

    if( mvComfirm > 255 )
        mvComfirm = 255;

    mvComfirm = ((mvComfirm_iir*3 )+ mvComfirm ) >> 2;
    mvComfirm_iir = mvComfirm;

    return mvComfirm_iir;
}

/******************************************************************************/
///MCNR Driver
/******************************************************************************/

void MDrv_SC_mcnr_driver( MS_U32 nonHistoryMotionPixel )
{
    MS_U32 u32_is_mv0, u32_non_mv0, u32_mvNotFound, u32_mvFeathering, u32_mvc, u32_mvu, u32_mvd, u32_cplxPixel, temp1, temp2;
    MS_BOOL me_not_confirm , me_vertical, isHDSource, is24to60Hz/*, scene_change*/;
    static MS_U8 vMOvingReduceNR_HouseHDPatch_counter;
    static MS_U8 u8notConfirmCnt;
    static MS_U32 last_u32_mvNotFound;
    static MS_U8 nrWeightPatchForVSweep = 0;

    XC_ApiStatus stXCStatus;

    if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
    {
        //printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
    }

    is24to60Hz = (!stXCStatus.bInterlace) && (stXCStatus.u16InputVFreq < 300);

    u32_is_mv0  = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    u32_non_mv0 = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32_mvNotFound = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);
    u32_mvFeathering = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);
    u32_mvc     = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32_mvu     = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32_mvd     = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);
    u32_cplxPixel = MApi_XC_R2BYTE(REG_SC_BK2A_7F_L);
    isHDSource = ( MApi_XC_R2BYTEMSK(REG_SC_BK12_0F_L, 0xFFFF) > 0x700 );

    if ( (u32_cplxPixel > 0x1000) && (u32_is_mv0 > 0x1000) && (nonHistoryMotionPixel == 0) ) // patch for VSweep converge too slow
    {
        if ( nrWeightPatchForVSweep > 4 )
            nrWeightPatchForVSweep = nrWeightPatchForVSweep - 4;
        else
            nrWeightPatchForVSweep = 0;
    }
    else
    {
        if ( nrWeightPatchForVSweep < 0xD )
            nrWeightPatchForVSweep += 1;
    }

    /////////////////////////////////////////////////////////////////
    //  NR Patch 1
    /////////////////////////////////////////////////////////////////
    me_not_confirm = (u32_is_mv0 < 0x0200) && (u32_non_mv0 < 0x0200);
    me_vertical    = ((u32_mvu > u32_mvc) && (u32_mvu > u32_mvd) && (u32_mvu > 0x200)) ||
                     ((u32_mvd > u32_mvc) && (u32_mvd > u32_mvu) && (u32_mvd > 0x200));

    if(false == me_not_confirm)
    {
        if(u8notConfirmCnt > 0)
        {
            u8notConfirmCnt--;
        }
    }
    else
    {
        if(u8notConfirmCnt <= 0x40)
        {
            u8notConfirmCnt++;
        }
    }

    if(1)
    {
        MS_BOOL bBool = FALSE;

        if (MApi_XC_R2BYTEMSK(REG_SC_BK20_10_L , 0x03) & 0x03)
        {
            bBool = (u8notConfirmCnt > 0x30);//main&sub
        }
        else if (MApi_XC_R2BYTEMSK(REG_SC_BK20_10_L , BIT(1)) & BIT(1))
        {
            bBool = (u8notConfirmCnt > 0x30);//sub only
        }
        else if (MApi_XC_R2BYTEMSK(REG_SC_BK20_10_L , BIT(0)) & BIT(0))
        {
            bBool = ( (u8notConfirmCnt > 0x30) || me_vertical ); // low nr strength
        }

        if (bBool) // low nr strength
        {
            if ( !isHDSource )
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0064, 0x00FF); // moving picture, increase random motion
            else
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x00C2, 0x00FF); // Default 64 -> C2, moving picture, increase random motion
            if ( nrWeightPatchForVSweep >= 7 )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, (MS_U16)0x7777, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, (MS_U16)0x7777, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, (MS_U16)0x7777, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, (MS_U16)0x7777, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, (MS_U16)0x6655, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, (MS_U16)0x4433, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, (MS_U16)0x3322, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, (MS_U16)0x1100, 0xFFFF);
            }
            else //if ( nrWeightPatchForVSweep >= 4 )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, (MS_U16)0x4433, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, (MS_U16)0x3322, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, (MS_U16)0x1100, 0xFFFF);
            }
        }
        else if(u8notConfirmCnt < 0x10)
        {
            if ( (nrWeightPatchForVSweep >= 0xD) && (!is24to60Hz) )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, (MS_U16)0xDDDD, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, (MS_U16)0xDDDD, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, (MS_U16)0xDDDD, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, (MS_U16)0xDDDD, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, (MS_U16)0xDDDD, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, (MS_U16)0xBA98, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, (MS_U16)0x7654, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, (MS_U16)0x3210, 0xFFFF);
            }
            else if ( (nrWeightPatchForVSweep >= 0xA) && (!is24to60Hz) )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, (MS_U16)0xAAAA, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, (MS_U16)0xAAAA, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, (MS_U16)0xAAAA, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, (MS_U16)0xAAAA, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, (MS_U16)0xAAAA, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, (MS_U16)0xAA98, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, (MS_U16)0x7654, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, (MS_U16)0x3210, 0xFFFF);
            }
            else if ( nrWeightPatchForVSweep >= 7 )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, (MS_U16)0x7777, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, (MS_U16)0x7777, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, (MS_U16)0x7777, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, (MS_U16)0x7777, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, (MS_U16)0x6655, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, (MS_U16)0x4433, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, (MS_U16)0x3322, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, (MS_U16)0x1100, 0xFFFF);
            }
            else //if ( nrWeightPatchForVSweep >= 4 )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, (MS_U16)0x4444, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, (MS_U16)0x4433, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, (MS_U16)0x3322, 0xFFFF);
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, (MS_U16)0x1100, 0xFFFF);
            }
        }

        if ( isHDSource && (u32_mvc < 0x10) && (( u32_mvu + u32_mvd ) > 0x40) )
            vMOvingReduceNR_HouseHDPatch_counter = 16;
        else if ( (u32_is_mv0 <= 0x10) && (u32_non_mv0 > 0x2000) && (u32_mvNotFound > 0x80) && (u32_mvFeathering > 0x8) && (u32_cplxPixel < 0x200) ) // patch shibasoku a little out-of-search range
            vMOvingReduceNR_HouseHDPatch_counter = 16;
        else if ( vMOvingReduceNR_HouseHDPatch_counter > 0 )
            vMOvingReduceNR_HouseHDPatch_counter --;

        if ( is24to60Hz )
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x00F0, 0x00FF);
        else if ( (u32_is_mv0 > 0x200) && ((u32_is_mv0/2) > u32_non_mv0) && ((u32_is_mv0/2) > u32_mvNotFound) && (vMOvingReduceNR_HouseHDPatch_counter == 0) )
        {
            if ( stXCStatus.bInterlace )
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x006c, 0x00FF); // still picture, reduce random motion
            else
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0064, 0x00FF); // still picture, reduce random motion
        }
        else if ( (u32_non_mv0 > u32_is_mv0) || (vMOvingReduceNR_HouseHDPatch_counter > 0 )) // moving picture, increase random motion
        {
            if ( !isHDSource )
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0060, 0x00FF);
            else
            {
                if ( stXCStatus.bInterlace )
                {
                    temp1 = ( 0xE * vMOvingReduceNR_HouseHDPatch_counter + 0x6 * ( 16 - vMOvingReduceNR_HouseHDPatch_counter ) ) >> 4;
                    temp2 = ( 0x0 * vMOvingReduceNR_HouseHDPatch_counter + 0xC * ( 16 - vMOvingReduceNR_HouseHDPatch_counter ) ) >> 4;
                }
                else
                {
                    temp1 = ( 0xE * vMOvingReduceNR_HouseHDPatch_counter + 0x6 * ( 16 - vMOvingReduceNR_HouseHDPatch_counter ) ) >> 4;
                    temp2 = ( 0x0 * vMOvingReduceNR_HouseHDPatch_counter + 0x4 * ( 16 - vMOvingReduceNR_HouseHDPatch_counter ) ) >> 4;
                }
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)((temp1<<4)|temp2), 0x00FF); // 60 -> E0. moving picture, increase random motion
            }
        }
        else // default
        {
            if ( !isHDSource )
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0064, 0x00FF); // default random motion
            else
            {
                if ( stXCStatus.bInterlace )
                    MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x00C2, 0x00FF); // Default 64 -> C2, moving picture, increase random motion
                else
                    MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x00C2, 0x00FF); // Default 64 -> C2, moving picture, increase random motion
            }
        }
    }
    last_u32_mvNotFound = u32_mvNotFound;
}

/******************************************************************************/
///DeFeathering
///@param u32MotionValue \     IN: Motion value
/******************************************************************************/
void MDrv_SC_de_feathering(MS_U32 u32MotionValue)
{
    static MS_U32 u32DeFeatherCntLv1 = 0;
    static MS_U32 u32DeFeatherCntLv2 = 0;
    static MS_U32 u32DeFeatherCntLv3 = 0;
    MS_U8 u8SST_Static_Core_TH;
    MS_U32 reg_defethering_lv1_cnt;
    MS_U32 reg_defethering_lv2_cnt;
    MS_U32 reg_mdp_cnt;

    reg_defethering_lv1_cnt = 0x0A;
    reg_defethering_lv2_cnt = 0x08;
    reg_mdp_cnt = 0x01;

    // motion level count
    if(u32MotionValue >= DEFETHERING_LV1_TH)
    {
        if(u32DeFeatherCntLv1 < reg_defethering_lv1_cnt)
            u32DeFeatherCntLv1++;
    }
    else
    {
        if(u32DeFeatherCntLv1 >= reg_mdp_cnt)
            u32DeFeatherCntLv1 = u32DeFeatherCntLv1 - reg_mdp_cnt;
    }

    if(u32MotionValue >= DEFETHERING_LV2_TH)
    {
        if(u32DeFeatherCntLv2 < reg_defethering_lv2_cnt)
            u32DeFeatherCntLv2++;
    }
    else
    {
        if(u32DeFeatherCntLv2 >= reg_mdp_cnt)
            u32DeFeatherCntLv2 = u32DeFeatherCntLv2 - reg_mdp_cnt;
    }

    if(u32MotionValue >= DEFETHERING_LV3_TH)
    {
        if(u32DeFeatherCntLv3 < DEFETHERING_LV3_CNT)
            u32DeFeatherCntLv3++;
    }
    else
    {
        if(u32DeFeatherCntLv3 >= reg_mdp_cnt)
            u32DeFeatherCntLv3 = u32DeFeatherCntLv3 - reg_mdp_cnt;
    }

    //DeFeathering begin
    if(u32DeFeatherCntLv1 >= reg_defethering_lv1_cnt)
    {
        u8SST_Static_Core_TH    = SST_STATIC_CORE_TH_LV1_VALUE;
    }
    else if(u32DeFeatherCntLv2 >= reg_defethering_lv2_cnt)
    {
        u8SST_Static_Core_TH    = SST_STATIC_CORE_TH_LV2_VALUE;
    }
    else if(u32DeFeatherCntLv3 >= DEFETHERING_LV3_CNT)
    {
        u8SST_Static_Core_TH    = SST_STATIC_CORE_TH_LV3_VALUE;
    }
    else
    {
        u8SST_Static_Core_TH    = SST_STATIC_CORE_TH_LV4_VALUE;
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK22_1A_L, (MS_U16)u8SST_Static_Core_TH, 0xFF);
}


/******************************************************************************/
///DeFlickering
///@param u32MotionValue \     IN: Motion value
/******************************************************************************/
void MDrv_SC_de_flickering(MS_U32 u32MotionValue)
{
    static MS_S32 s32DeFlickerCnt = 0;
    MS_U32 reg_m_feat_smooth_hle_th, reg_m_feat_smooth_shrink;

    reg_m_feat_smooth_hle_th = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_1E_L, 0xF000); // Feat Smooth HLE TH
    reg_m_feat_smooth_shrink = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_1E_L, 0x8F);

    if(u32MotionValue >= DEFLICKERING_TH)
    {
        if(s32DeFlickerCnt < 65535)
            s32DeFlickerCnt++;
    }
    else
    {
        s32DeFlickerCnt = 0;
    }

    if(s32DeFlickerCnt >= DEFLICKERING_CNT)
    {
        reg_m_feat_smooth_hle_th += 0x0300;
        reg_m_feat_smooth_shrink += 0x10;
    }
    else
    {
        reg_m_feat_smooth_hle_th += 0x0700;
        reg_m_feat_smooth_shrink += 0x30;
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK22_1E_L, reg_m_feat_smooth_shrink, 0xFF);
    MApi_XC_W2BYTEMSK(REG_SC_BK22_1E_L, reg_m_feat_smooth_hle_th, 0xFF00);
}

/******************************************************************************/
///DeBouncing
///@param u32MotionValue \     IN: Motion value
/******************************************************************************/
#define DEBOUNCING_GAIN 1 //0
void MDrv_SC_de_bouncing(MS_U32 u32MotionValue)
{
    static MS_S32 s32DeBouncingCnt = 0;
    MS_U32 reg_his_wt_f2;
    MS_U32 reg_debouncing_th;
    int reg_debouncing_cnt;

    reg_debouncing_th = 0x0A;
    reg_debouncing_cnt = 0x03;

    reg_his_wt_f2 = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_0A_L, 0xF8); // history ratio weighting

    MS_BOOL film;
    film = ( (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0008) == 0x0008) ||  // film22
           ( (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0010) == 0x0010) ||  // film32
           ( (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0040) == 0x0040) ;   // film any

    if(u32MotionValue <= reg_debouncing_th * DEBOUNCING_GAIN)
    {
        s32DeBouncingCnt = 0;
    }
    else
    {
        if(s32DeBouncingCnt < 65535)
            s32DeBouncingCnt++;
    }

    if(film || (s32DeBouncingCnt >= reg_debouncing_cnt))
    {
        reg_his_wt_f2 += 0x06; // history = 6 moving
    }
    else
    {
        reg_his_wt_f2 += 0x03; // history = 3 still
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK22_0A_L, reg_his_wt_f2, 0xFF);
}
#if 0
void MDrv_SC_Amber5_DHD_driver1(void)
{
    // dhd news report patch: enhance dhd strength
    static MS_U32 u32sd2hdCnt = 0;
    int check_width = MApi_XC_R2BYTEMSK(REG_SC_BK12_0F_L, 0xFFFF);
    int is_PAL = (MApi_XC_R2BYTE(REG_SC_BK05_12_L)&0x4000)>>14;

    MS_U8 MV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_78_L)>>8;

    if(0)//(u8SD2HDValue>=60)&&(check_width>0x700)&&(MV0_Comfirm>0x20)&&(is_PAL==0)) //When in HD case, detect SD
    {
        u32sd2hdCnt++;

        if( u32sd2hdCnt >= 100 )
        {
            u32sd2hdCnt = 100;
        }
    }
    else
    {
        if( u32sd2hdCnt == 0 )
        {
            u32sd2hdCnt = 0;
        }
        else
        {
            u32sd2hdCnt--;
        }
    }

    // divide into 11 level
    if( u32sd2hdCnt <= 2 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0030, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x1000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0010, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 3 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0030, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x2000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0020, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 4 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0030, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x3000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0020, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 5 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0040, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x4000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0030, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 6 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0050, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x5000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0040, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 7 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0060, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x6000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0050, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 8 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0070, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x7000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0060, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 9 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0080, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x8000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0070, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 10 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x0090, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x9000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0080, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt == 11 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x00A0, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0xA000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x0090, 0x00FF); //c value gain
    }
    else if( u32sd2hdCnt >= 12 )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0x00B0, 0x00FF); //c edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_26_L, 0xB000, 0xFF00); //y edge gain
        MApi_XC_W2BYTEMSK(REG_SC_BK05_23_L, 0x00A0, 0x00FF); //c value gain
    }
}


void MDrv_SC_Amber5_DHD_driver2( MS_U32 uComplex, MS_U32 IsHorizontalMoving, MS_U8 u8SD2HDValue, MS_BOOL VerticalMovingForDHD )
{
    // dhd stadium patch: lower dhd strength
    static MS_U32 u32filmCnt = 0;
    int check_width = MApi_XC_R2BYTEMSK(REG_SC_BK12_0F_L, 0xFFFF);
    UNUSED(IsHorizontalMoving);

    if (((u8SD2HDValue<10) && (uComplex>200)
        && (check_width>0x700)) || (VerticalMovingForDHD && (check_width>0x700) )
        || ( (u8SD2HDValue<5) && (check_width>0x700)))
    {
        u32filmCnt++;

        if( u32filmCnt >= 50 )
        {
            u32filmCnt = 50;
        }
    }
    else
    {
        if( u32filmCnt == 0 )
        {
            u32filmCnt = 0;
        }
        else
        {
            u32filmCnt--;
        }
    }

    if( u32filmCnt <= 2 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x000F, 0x000F); //dhd user weight
    else if( u32filmCnt == 3 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x000D, 0x000F); //dhd user weight
    else if( u32filmCnt == 4 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x000B, 0x000F); //dhd user weight
    else if( u32filmCnt == 5 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x0009, 0x000F); //dhd user weight
    else if( u32filmCnt == 6 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x0007, 0x000F); //dhd user weight
    else if( u32filmCnt == 7 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x0005, 0x000F); //dhd user weight
    else if( u32filmCnt == 8 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x0003, 0x000F); //dhd user weight
    else if( u32filmCnt == 9 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x0001, 0x000F); //dhd user weight
    else if( u32filmCnt >= 10 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_2C_L, 0x0000, 0x000F); //dhd user weight
}
#endif

/******************************************************************************/
///CCS Driver
/******************************************************************************/

void MDrv_SC_Amber5_CCS_driver(MS_U32 uComplex)
{
    // ccs moving color dot pattern patch: lower ccs strength
    static MS_U32 u32videoCnt = 0;

    if( uComplex < 16 )
    {
        u32videoCnt++;

        if( u32videoCnt >= 200 )
        {
            u32videoCnt = 200;
        }
    }
    else
    {
        if( u32videoCnt == 0 )
        {
            u32videoCnt = 0;
        }
        else
        {
            u32videoCnt--;
        }
    }

    if( u32videoCnt <= 2 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x000F, 0x000F); //ccs user weight
    else if( u32videoCnt == 3 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x000D, 0x000F); //ccs user weight
    else if( u32videoCnt == 4 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x000B, 0x000F); //ccs user weight
    else if( u32videoCnt == 5 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0009, 0x000F); //ccs user weight
    else if( u32videoCnt == 6 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0007, 0x000F); //ccs user weight
    else if( u32videoCnt == 7 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0005, 0x000F); //ccs user weight
    else if( u32videoCnt == 8 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0003, 0x000F); //ccs user weight
    else if( u32videoCnt == 9 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0001, 0x000F); //ccs user weight
    else if( u32videoCnt >= 10 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0000, 0x000F); //ccs user weight
}

void MDrv_SC_Amber5_CCS_driver2(MS_U32 OOSRMC, MS_U32 IsHorizontalMoving)
{
    // horizontal moving => lower ccs weight
    static MS_U32 u32videoCnt = 0;

    if( (OOSRMC < 20) || (IsHorizontalMoving >25) )
    {
        u32videoCnt++;

        if( u32videoCnt >= 200 )
        {
            u32videoCnt = 200;
        }
    }
    else
    {
        if( u32videoCnt == 0 )
        {
            u32videoCnt = 0;
        }
        else
        {
            u32videoCnt--;
        }
    }

    if( u32videoCnt <= 2 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x000F, 0x000F); //ccs user weight
    else if( u32videoCnt == 3 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x000D, 0x000F); //ccs user weight
    else if( u32videoCnt == 4 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x000B, 0x000F); //ccs user weight
    else if( u32videoCnt == 5 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0009, 0x000F); //ccs user weight
    else if( u32videoCnt == 6 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0007, 0x000F); //ccs user weight
    else if( u32videoCnt == 7 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0005, 0x000F); //ccs user weight
    else if( u32videoCnt == 8 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0003, 0x000F); //ccs user weight
    else if( u32videoCnt == 9 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0001, 0x000F); //ccs user weight
    else if( u32videoCnt >= 10 )
        MApi_XC_W2BYTEMSK(REG_SC_BK05_5C_L, 0x0000, 0x000F); //ccs user weight
}

#if (Auto_DeBlock_En)
#define ADBW_HD_Loop_Ini_Start 40
#define ADBW_HD_Max_Range_End 1440
#define ADBW_SD_Loop_Ini_Start 20
#define ADBW_SD_Max_Range_End  720
static MS_U32 Auto_DBK_Width_val = 8;
static MS_U32 Auto_DBK_Width_val_tmp = 32; // format is xxxxx.xx
static MS_U32 Pre_DBK_Width_val = 8;

void MDrv_SC_Auto_Detect_Blocking_Width_driver(void)
{
    int  data_ack_en;
    //int  temp_data;
    int  blkwidth_data[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int  blkwidth_s_data[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    long  blockiness_data[1440];
    MS_BOOL blocking_peakidx[1440];
    int  bin;
    int check_width = MApi_XC_R2BYTEMSK(REG_SC_BK12_0F_L, 0xFFFF);
    int  Loop_Ini_Start = (check_width>0x700) ? ADBW_HD_Loop_Ini_Start : ADBW_SD_Loop_Ini_Start;
    int  Max_Range_End = (check_width>0x700) ? ADBW_HD_Max_Range_End :  ADBW_SD_Max_Range_End;
    long  fme_blockiness;
    long  frame_maxin_d = 0;
    long  local_maxin_d;
    int   left7,right7;
    int   left2 = 0;
    int   right2 = 0;
    int   left1,right1;
    int   bestblock_width = 8;
    MS_U32 iir_strength = 2;

    MS_U32 DBK_frame_blockiness = 0;
    MS_U32 DBK_frame_blockiness_sum = 0;
    static MS_U32 DBK_frame_blockiness_iir = 0;
    MS_U16 test_dummy  = 0x2500 ;
    MS_U16 test_dummy2 = 0x2000 ;
    MS_U16 dbk_debug_enable = MApi_XC_R2BYTEMSK(REG_SC_BK0C_40_L, 0x00FF)>>7 ;  //MApi_XC_R2BYTEMSK(REG_SC_BK30_03_L, 0xFFFF)>>15;
    MS_U16 dbk_iir_diff_thrd = 0x12;//MApi_XC_R2BYTEMSK(REG_SC_BK30_03_L, 0x7F00)>>8;
    static MS_U16 NMR_Ctrl=0;
    static MS_U16 NMR_Strength=0;
    MS_U32 iir_strength_NM = 2;
    MS_S32 DBK_frame_blockiness_diff=0;

    static MS_U32 pre_DBK_frame_blockiness=0;
    int peak_from_blkwidth_data=0;
    static MS_U16 NMR_Strength_iir = 0 ;
    MS_U16 NMR_Strength_new = 0 ;
    MS_U16 NMR_Strength_new_adjust = 0 ;

    MS_U16 test_dummy4 = 0 ;//MApi_XC_R2BYTEMSK(REG_SC_BK30_02_L, 0xFFFF)>>15;
    MS_U16 dbk_apply=0;
    MS_U16  count_thrd =  0x6 ; //MApi_XC_R2BYTEMSK(REG_SC_BK30_05_L, 0x00FF);
    MS_U16  iir_diff_thrd =  0x1 ; //MApi_XC_R2BYTEMSK(REG_SC_BK30_05_L, 0xFF00)>>8;

    // setting HD mode enable
    if(check_width>0x700)
    {
        if(0)//u8SD2HDValue>=60)
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK0C_41_L, 0x1, 0x0001); // SDHD mode
            MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 0x6, 0x0007); // SDHD mode
            MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 15<<8, 0x0F00); // SDHD mode
        }
        else
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK0C_41_L, 0x0, 0x0001); // SDHD mode
            MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 0x2, 0x0007); // SDHD mode
            MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 4<<8, 0x0F00); // SDHD mode
        }
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_41_L, 0x0, 0x0001); // SD mode & HD mode
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 0x2, 0x0007); // SDHD mode
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 4<<8, 0x0F00); // SDHD mode
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK0C_38_L, 0x4, 0x0004); // setting vertical iir enable

    //--------- Blockiness Histogram Request start ---------//

    // write 0 to request register
    //MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 0, 0x0001);
    // write 1 to request register
    MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 1, 0x0001);

    //--------- Blockiness Histogram Request end    ---------//

    //--------- Blockiness Histogram Acknowledge start ---------//

    data_ack_en = MApi_XC_R2BYTEMSK(REG_SC_BK0C_0D_L, 0x0002);

    //--------- Blockiness Histogram Acknowledge end   ---------//

    //--------- Function Process start ---------//
    if(data_ack_en)
    {
        // write 1 to sram_io_en register
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 0x100, 0x0100);
        for(bin = 0; bin < Max_Range_End; bin++)
        {
            // write address
            MApi_XC_W2BYTEMSK(REG_SC_BK0C_0E_L, (MS_U16)(0x8000 + bin), 0xFFFF);
            // read data from selected address
            blockiness_data[bin] = MApi_XC_R2BYTEMSK(REG_SC_BK0C_0F_L, 0xFFFF);
            //printf("blockiness[%4d] is %d\n",bin,blockiness_data[bin]);
        }

        //printf("blockiness is %d\n",bin);
        //read frame blockiness data
        fme_blockiness = ((MApi_XC_R2BYTEMSK(REG_SC_BK0C_61_L, 0xFFFF))<<16) | (MApi_XC_R2BYTEMSK(REG_SC_BK0C_60_L, 0xFFFF));  // frame blockiness data report 32 bit

         MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 0, 0x0001);
        //printf("fme_blockiness is %d\n\n",fme_blockiness);

        //------- find the max local minmax difference start -------//
        for(bin = Loop_Ini_Start; bin < (Max_Range_End - 40); bin++)
        {
            left2 = bin - 2;
            right2 = bin + 2;

            int loc_max = 0;
            int loc_min = 65535;
            int cnt;

            for(cnt = left2; cnt <= right2; cnt++)
            {
                //find max
                if(blockiness_data[cnt] > loc_max)
                    loc_max = blockiness_data[cnt];

                //find min
                if(blockiness_data[cnt] < loc_min)
                    loc_min = blockiness_data[cnt];
            }

            if(loc_max > loc_min)
                local_maxin_d = loc_max - loc_min;
            else
                local_maxin_d = 0;

            if(local_maxin_d > frame_maxin_d)
                frame_maxin_d = local_maxin_d;

        }
        //------- find the max local minmax difference end   -------//

        for(bin = 0; bin < Max_Range_End; bin++)
            blocking_peakidx[bin] = false;

        //------- find peak index start -------//
        for(bin = 0; bin < (Max_Range_End - 40); bin++)
        {
            left7 = (bin < 7) ? 0 : bin - 7;
            left1 = (bin < 1) ? 0 : bin - 1;
            right1 = bin + 1;
            right7 = bin + 7;

            int loc_max = 0;
            int loc_min = 65535;
            int cnt;

            for(cnt = left7; cnt <= right7; cnt++)
            {
                //find max
                if(blockiness_data[cnt] > loc_max)
                    loc_max = blockiness_data[cnt];

                //find min
                if(blockiness_data[cnt] < loc_min)
                    loc_min = blockiness_data[cnt];
            }

            if(loc_max > loc_min)
                local_maxin_d = loc_max - loc_min;
            else
                local_maxin_d = 0;

            int Currx2_0 = (blockiness_data[bin]<<1); // data x 2
            int Lf12x1_1 = ((blockiness_data[left1] + blockiness_data[left2])*11)/10;    // data x 1.1
            int Rt12x1_1 = ((blockiness_data[right1] + blockiness_data[right2])*11)/10;  // data x 1.1
            int Currx1     = blockiness_data[bin]; // data x 1
            int Loc_Maxx0_99 = (loc_max*85)/100;  // data x 0.85  // ori is data x 0.99
            int local_maxin_dx3 = local_maxin_d*3; // data x 3

            if((Currx2_0>Lf12x1_1)&&(Currx2_0>Rt12x1_1)&&(Currx1>Loc_Maxx0_99)&&(local_maxin_dx3>frame_maxin_d) && (blockiness_data[bin] > blockiness_data[left1]) && (blockiness_data[bin] > blockiness_data[right1]))
                blocking_peakidx[cnt] = true;
        }
        //------- find peak index end   -------//

        //------- find best block width start -------//
        int start_idx = 0;

        for(bin = 0; bin < Max_Range_End; bin++)
        {
            if((blocking_peakidx[bin]==true)&&(bin!=start_idx))
            {
                int cnt = bin - start_idx;
                if( cnt < 31)
                    blkwidth_data[cnt] += 1;

                start_idx = bin;
            }
        }
        //------- find best block width end   -------//
        //------- summarize 1x3 on blkwidth start -------//

        for(bin = 5; bin < 31; bin ++)
        {
            left1 = (bin < 1) ? 0 : bin - 1;
            right1 = (bin >= 31) ? 30 : bin + 1;

            int loc_max = 0;
            int cnt;

            for(cnt = left1; cnt <= right1; cnt++)
            {
                //find max
                if(blkwidth_data[cnt] > loc_max)
                    loc_max = blkwidth_data[cnt];
            }

            if(blkwidth_data[bin] > (loc_max>>1))
                blkwidth_s_data[bin] = blkwidth_data[left1] + blkwidth_data[bin] + blkwidth_data[right1];
        }

        //------- summarize 1x3 on blkwidth end   -------//

        //------- find the 1st max block width start -------//
        int bestblock_cnt_m = 0;
        int bestblock_lf1 = 0;
        int bestblock_idx = 0;
        int bestblock_rt1 = 0;

        for(bin = 5; bin < 31; bin++)
        {
            if(blkwidth_s_data[bin] > bestblock_cnt_m)
            {
                bestblock_cnt_m = blkwidth_s_data[bin];
                bestblock_idx = bin;
            }
        }

        bestblock_lf1 = bestblock_idx - 1;
        bestblock_rt1 = bestblock_idx + 1;
        blkwidth_s_data[bestblock_idx] = 0;

        if(dbk_debug_enable)
            printf("1st width is %d  | cnt is %d\n",bestblock_idx,bestblock_cnt_m);
        //------- find the 1st max block width end   -------//

        //------- find the 2nd max block width start -------//
        int bestblock_cnt_m2 = 0;
        int bestblock_idx2 = 0;

        for(bin = 5; bin < 31; bin++)
        {
            if((blkwidth_s_data[bin] > bestblock_cnt_m2)&&((bin > bestblock_rt1) || (bin < bestblock_lf1)))
            {
                bestblock_cnt_m2 = blkwidth_s_data[bin];
                bestblock_idx2 = bin;
            }
        }

        bestblock_lf1 = bestblock_idx2 - 1;
        bestblock_rt1 = bestblock_idx2 + 1;
        blkwidth_s_data[bestblock_idx2] = 0;

        if(dbk_debug_enable)
            printf("2nd width is %d  | cnt is %d\n",bestblock_idx2,bestblock_cnt_m2);
        //------- find the 2nd max block width end   -------//

        //------- find the 3rd max block width start -------//
        int bestblock_cnt_m3 = 0;
        int bestblock_idx3 = 0;

        for(bin = 5; bin < 31; bin++)
        {
            if((blkwidth_s_data[bin] > bestblock_cnt_m3)&&((bin > bestblock_rt1) || (bin < bestblock_lf1)))
            {
                bestblock_cnt_m3 = blkwidth_s_data[bin];
                bestblock_idx3 = bin;
            }
        }

        if(dbk_debug_enable)
            printf("3rd width is %d  | cnt is %d\n",bestblock_idx3,bestblock_cnt_m3);
        //------- find the 3rd max block width end   -------//

#if 0
        if((u8SD2HDValue>=60)&&(check_width>0x700))
        {
            if((bestblock_idx>=20)&&(bestblock_idx<=22)&&(bestblock_cnt_m>=5))
            {
                bestblock_cnt_m = 100;
                if(dbk_debug_enable)
                    printf("SD2HD is 1st\n");
            }
            else if((bestblock_idx2>=20)&&(bestblock_idx2<=22)&&(bestblock_cnt_m2>=5))
            {
                bestblock_idx = bestblock_idx2;
                bestblock_cnt_m = 100;
                if(dbk_debug_enable)
                    printf("SD2HD is 2nd\n");
            }
            else if((bestblock_idx3>=20)&&(bestblock_idx3<=22)&&(bestblock_cnt_m3>=5))
            {
                bestblock_idx = bestblock_idx3;
                bestblock_cnt_m = 100;
                if(dbk_debug_enable)
                    printf("SD2HD is 3rd\n");
            }
        }
#endif

        //------- calculate best block width start -------//
        MS_BOOL condition1 = ((bestblock_cnt_m<<1) >= (bestblock_cnt_m2*3)) ? true : false;    // m1 >= m2*1.5
        MS_BOOL condition2 = ((bestblock_cnt_m   ) >= (bestblock_cnt_m2<<1)) ? true : false;   // m1 >= m3*2
        MS_BOOL condition3 = (bestblock_cnt_m > 15) ? true : false;
        MS_BOOL condition4 = (bestblock_idx > 6) ? true : false;

        if(condition1&& condition2&&condition3&&condition4)
        {
            bestblock_width = bestblock_idx;

            if(/*(u8SD2HDValue==00)&&*/(check_width>0x700)&&(bestblock_width==16))
                bestblock_width = 8;

            Pre_DBK_Width_val = bestblock_width;

            if(dbk_debug_enable)
                printf("####bestblock_width is %d####\n",bestblock_width);
        }
        else
        {
            if((bestblock_cnt_m<count_thrd)||(bestblock_idx<=6))
                Pre_DBK_Width_val = 8;

            if(dbk_debug_enable)
                printf("##bestblock_width is %ld##\n",Pre_DBK_Width_val);
        }

        if(dbk_debug_enable)
            printf("Pre_DBK_Width_val is %ld\n",Pre_DBK_Width_val);

        // iir
        int Pre_DBK_Width_val_tmp = (Pre_DBK_Width_val<<2); // format is xxxxx.xx
        Auto_DBK_Width_val_tmp = ((iir_strength*Pre_DBK_Width_val_tmp) + (8-iir_strength)*Auto_DBK_Width_val_tmp)/8; // format is xxxxx.xx
        Auto_DBK_Width_val = (Auto_DBK_Width_val_tmp>>2); // format is xxxxx.0

        if(Auto_DBK_Width_val<=8)
        {
            Auto_DBK_Width_val = 8;
            left1 = 9;
            right1 = 8;
        }
        else
        {
            left1 = (Auto_DBK_Width_val < 1) ? 0 : Auto_DBK_Width_val - 1;
            right1 = (Auto_DBK_Width_val >=31) ? 31 : Auto_DBK_Width_val + 1;
        }

        // write interval left && interval right
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_39_L, (MS_U16)((right1<<8)|left1), 0xFFFF);
        //------- calculate best block width end   -------//

        if(dbk_debug_enable)
            printf("Final width is %ld <=====\n",Auto_DBK_Width_val);

        if(data_read)
        {
            NMR_Ctrl =  MApi_XC_R2BYTEMSK(REG_SC_BK0C_50_L, 0x0001);
            NMR_Strength = MApi_XC_R2BYTEMSK(REG_SC_BK0C_54_L, 0x003F);
            data_read = false;
        }

        DBK_frame_blockiness_sum=0;
        for(bin = 0; bin < (Max_Range_End ); bin=bin+Auto_DBK_Width_val)
        {
            MS_U32 loc_max = 0;
            MS_U32 loc_min = 0xFFFFFFFF;
            MS_U32 cnt;

            for(cnt = 0; cnt <= Auto_DBK_Width_val-1; cnt++)
            {
                //find max
                if(((MS_U32)blockiness_data[bin+cnt] > loc_max)&&((bin+cnt)<1440))
                    loc_max = (MS_U32)blockiness_data[bin+cnt];

                //find min
                if(((MS_U32)blockiness_data[bin+cnt] < loc_min)&&((bin+cnt)<1440))
                    loc_min = (MS_U32)blockiness_data[bin+cnt];
            }

            if(loc_max > loc_min)
            {
                local_maxin_d = loc_max - loc_min;
            }
            else
            {
                local_maxin_d = 0;
            }
            DBK_frame_blockiness_sum += local_maxin_d;
        }

        DBK_frame_blockiness = DBK_frame_blockiness_sum*Auto_DBK_Width_val / (Max_Range_End) ;

        DBK_frame_blockiness_diff = abs(DBK_frame_blockiness - pre_DBK_frame_blockiness);

        if( DBK_frame_blockiness_diff > ((dbk_iir_diff_thrd<<8) ))
        {
            iir_strength_NM = 2;
        }
        else
        {
            iir_strength_NM = 2;
        }

        DBK_frame_blockiness_iir = (DBK_frame_blockiness*iir_strength_NM+ DBK_frame_blockiness_iir*(8-iir_strength_NM))/8;

        if(dbk_debug_enable)
        {
            printf("DBK_frame_blockiness_sum is %lx <=====\n",DBK_frame_blockiness_sum);
            printf("DBK_frame_blockiness is %lx <=====\n",DBK_frame_blockiness);
            printf("DBK_frame_blockiness_iir is %lx <=====\n",DBK_frame_blockiness_iir);
        }

        pre_DBK_frame_blockiness = DBK_frame_blockiness;

        peak_from_blkwidth_data = 0;
        for(bin = 8; bin < 31; bin ++)
        {
            if( blkwidth_data[bin]> peak_from_blkwidth_data )
                peak_from_blkwidth_data = blkwidth_data[bin];
        }

        if(test_dummy4)
        {
            if( (abs(Auto_DBK_Width_val - bestblock_idx)<=2)  &&  (peak_from_blkwidth_data>=10) )
                dbk_apply=1;
            else
                dbk_apply=0;
        }
        else
        {
            if( (abs(Auto_DBK_Width_val - bestblock_idx)<=2)  ||  (peak_from_blkwidth_data>=10) )
                dbk_apply=1;
            else
                dbk_apply=0;
        }

        if (1)//(fme_blockiness>= (test_dummy3 <<8) )   //0x100000 // multiburst pan
        {
            if(DBK_frame_blockiness>= (0x2500))
            {
                NMR_Ctrl = 1 ;
                NMR_Strength_new = 0x3F ;
            }
            else if((DBK_frame_blockiness< (test_dummy)) && (DBK_frame_blockiness >= (test_dummy2)))
            {
                NMR_Ctrl = 1 ;
                NMR_Strength_new = 0x1f;
            }
            else
            {
                NMR_Strength_new = NMR_Strength;
            }
        }
        else
        {
            NMR_Strength_new = NMR_Strength;
        }

        if(abs(NMR_Strength_new*4 - NMR_Strength_iir)>=(iir_diff_thrd*4) )
        {
            if((NMR_Strength_new*4)>=NMR_Strength_iir)
            {
                NMR_Strength_new_adjust = NMR_Strength_iir + iir_diff_thrd*4;
                NMR_Strength_iir = (NMR_Strength_iir*2+ NMR_Strength_new_adjust*6)/8;  //*4/8(iir) = /2 ==> X.2 format
            }
            else
            {
                NMR_Strength_new_adjust = NMR_Strength_new*4;
                NMR_Strength_iir = (NMR_Strength_iir*0+ NMR_Strength_new_adjust*8)/8;  //*4/8(iir) = /2 ==> X.2 format
            }
        }
        else
        {
            NMR_Strength_new_adjust = NMR_Strength_new*4;
            NMR_Strength_iir = (NMR_Strength_iir*2+ NMR_Strength_new_adjust*6)/8;  //*4/8(iir) = /2 ==> X.2 format
        }

        MApi_XC_W2BYTEMSK(REG_SC_BK0C_50_L, NMR_Ctrl, 0x0001);
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_54_L, (NMR_Strength_iir/4+ (NMR_Strength_iir&2)/2 ), 0x003F);
    }
    //--------- Function Process end   ---------//
}
#endif

static MS_U16 g_u16BK0A_24 = 0;
static MS_U16 g_u16BK0C_10 = 0;
static MS_U16 g_u16BK0C_39 = 0;
static MS_U16 g_u16BK0C_3A = 0;
static MS_U16 g_u16BK0C_40 = 0;
static MS_U16 g_u16BK0C_41 = 0;
static MS_U16 g_u16BK0C_42 = 0;
static MS_U16 g_u16BK26_10 = 0;
static MS_U16 g_u16BK26_11 = 0;
static MS_U16 g_u16BK26_12 = 0;
static MS_U16 g_u16BK26_13 = 0;
static MS_U16 g_u16BK26_18 = 0;

/******************************************************************************/
///Film mode control for Any Candence
///@param bEnable \     IN: Enable/Disable control
/******************************************************************************/
void Hal_PQ_FilmMode_AnyCandence_Enable(MS_BOOL bEnable)
{
    MApi_XC_W2BYTEMSK(REG_SC_BK0A_24_L, (bEnable ? (BIT(15)) : 0), BIT(15));
    _bAnyCandenceEnable = bEnable;
}

/******************************************************************************/
///Store the Current value
/******************************************************************************/
void Hal_PQ_StoreCurrentValue(void)
{
    //for AnyCandence Film Mode
    g_u16BK0A_24 = MApi_XC_R2BYTEMSK(REG_SC_BK0A_24_L, BIT(15));

    //for DBK
    g_u16BK0C_10 = MApi_XC_R2BYTE(REG_SC_BK0C_10_L);
    g_u16BK0C_39 = MApi_XC_R2BYTE(REG_SC_BK0C_39_L);
    g_u16BK0C_3A = MApi_XC_R2BYTE(REG_SC_BK0C_3A_L);
    g_u16BK0C_40 = MApi_XC_R2BYTE(REG_SC_BK0C_40_L);
    g_u16BK0C_41 = MApi_XC_R2BYTE(REG_SC_BK0C_41_L);
    g_u16BK0C_42 = MApi_XC_R2BYTE(REG_SC_BK0C_42_L);

    //for DMS
    g_u16BK26_10 = MApi_XC_R2BYTE(REG_SC_BK26_10_L);
    g_u16BK26_11 = MApi_XC_R2BYTE(REG_SC_BK26_11_L);
    g_u16BK26_12 = MApi_XC_R2BYTE(REG_SC_BK26_12_L);
    g_u16BK26_13 = MApi_XC_R2BYTE(REG_SC_BK26_13_L);
    g_u16BK26_18 = MApi_XC_R2BYTE(REG_SC_BK26_18_L);
}

/******************************************************************************/
///Store the Current value
/******************************************************************************/
void Hal_PQ_ReStoreToDefault(void)
{
    //for AnyCandence Film Mode
    MApi_XC_W2BYTEMSK(REG_SC_BK0A_24_L, g_u16BK0A_24, BIT(15));

    //for DBK
    MApi_XC_W2BYTE(REG_SC_BK0C_10_L, g_u16BK0C_10);
    MApi_XC_W2BYTE(REG_SC_BK0C_39_L, g_u16BK0C_39);
    MApi_XC_W2BYTE(REG_SC_BK0C_3A_L, g_u16BK0C_3A);
    MApi_XC_W2BYTE(REG_SC_BK0C_40_L, g_u16BK0C_40);
    MApi_XC_W2BYTE(REG_SC_BK0C_41_L, g_u16BK0C_41);
    MApi_XC_W2BYTE(REG_SC_BK0C_42_L, g_u16BK0C_42);

    //for DMS
    MApi_XC_W2BYTE(REG_SC_BK26_10_L, g_u16BK26_10);
    MApi_XC_W2BYTE(REG_SC_BK26_11_L, g_u16BK26_11);
    MApi_XC_W2BYTE(REG_SC_BK26_12_L, g_u16BK26_12);
    MApi_XC_W2BYTE(REG_SC_BK26_13_L, g_u16BK26_13);
    MApi_XC_W2BYTE(REG_SC_BK26_18_L, g_u16BK26_18);
}

#define ENABLE_SCALER_DEFEATHERING           0x01   //BK22_7C_L
#define ENABLE_SCALER_DEFLICKERING           0x02
#define ENABLE_SCALER_DEBOUNCING             0x04
#define ENABLE_SCALER_UCDI_DRIVER            0x08
#define ENABLE_SCALER_MCNR_DRIVER            0x10
#define ENABLE_SCALER_DHD_CCS_DRIVER         0x20
#define ENABLE_SCALER_AUTO_DBK_DRIVER        0x40
//#define ENABLE_SCALER_SDHD_DETECT_DRIVER     0x80

//-------------------------------------------------------------------------------------------------
/// this function does adaptive tuning periodic
//-------------------------------------------------------------------------------------------------
void Hal_PQ_AdaptiveTuning(void)
{
    static MS_U8 u8PreviousVcnt = 0;
    MS_U8 u8CurrentVcnt;
    MS_U8  u8Ctrl,ColorSum,MR_Offset;
    MS_U32 u32MotionValue,u32MotionValue2,u32MotionValue3,OOSRMC,OOSRF,ISR_NONMV0,SmallMoving,VerticalMoving,HorizontalMoving,TotalFeather,TotalMvComfirm;
    MS_U32 uComplex,FeatherSum,u32MotionValue_Sum;

    XC_ApiStatus stXCStatus;
    MS_BOOL bL107_en;
    //MS_BOOL isFilm22Like;
    //MS_BOOL isfilmXOO = 0;
    //MS_U32 film22adaptiveCounter1Th;
    memset(&stXCStatus, 0x00, sizeof(stXCStatus));

    //
    // Check VCnt
    //

    if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
    {
        printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
    }

    // Get input resoultion info
    //
    if( stXCStatus.u16H_SizeAfterPreScaling >= 1280 )
    {
		_bIsHDSource= true;
    }
    else
    {
		_bIsHDSource= false;
    }

    u8CurrentVcnt = MDrv_SC_read_v_cnt();
    if (u8PreviousVcnt == u8CurrentVcnt)
    {
        return;
    }
    else
    {
        u8PreviousVcnt = u8CurrentVcnt;
    }

    //
    // Get adaptive function control
    //
    u8Ctrl  = MDrv_SC_get_adaptive_ctrl();

    //
    // Get motion value
    //
    u32MotionValue = MDrv_SC_read_motion_value1();
    u32MotionValue2 = MDrv_SC_read_motion_value2();
    u32MotionValue3 = MDrv_SC_read_motion_value3();

    //
    // Get UCDi status
    //
    OOSRMC = MDrv_SC_T12_UC_InSearchRange_MvComfirm();
    OOSRF = MDrv_SC_T12_UC_InSearchRange_Feather();
    ISR_NONMV0 = MDrv_SC_T12_UC_InSearchRange_nonMv0Comfirm();
    SmallMoving = MDrv_SC_T12_UC_SmallMoving();
    VerticalMoving = MDrv_SC_A5_KFC_IsVerticalMoving();

    HorizontalMoving = MDrv_SC_A5_IsHorizontalMoving();
    TotalFeather = MDrv_SC_A5_TotalFeather();
    FeatherSum = MDrv_SC_TotalFeather_Sum();
    TotalMvComfirm = MDrv_SC_A5_TotalMvComfirm();
    ColorSum = MDrv_SC_A5_ColorPixelSum();
    uComplex = MDrv_SC_A5_ComplexSum();
    MR_Offset = MDrv_SC_UC_InSearchRange_MR_Offset();
    u32MotionValue_Sum = u32MotionValue2 + MR_Offset;

    MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, 0x00, 0xFF); // reset for get correct SW driver status

    // Adaptive functions
    if(_u16PQPre_SrcType != _u16PQSrcType_DBK_Detect[PQ_MAIN_WINDOW])            //For Auto_DBK SW driver used
    {
        _u16PQPre_SrcType = _u16PQSrcType_DBK_Detect[PQ_MAIN_WINDOW];
        data_read = true;
    }

    // Nikon AutoDBK function
    if (u8Ctrl & ENABLE_SCALER_AUTO_DBK_DRIVER)               //New Add for AUTO DBK Test
    {
        if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
        {
            printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
        }
        MDrv_SC_Auto_Detect_Blocking_Width_driver();//u8SDHDDReportValue);  //  Auto_Detect_Blocking_Width
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_AUTO_DBK_DRIVER, 0x40);
    }


    // Nikon UCDi function
    if (u8Ctrl & ENABLE_SCALER_UCDI_DRIVER)
    {
        MDrv_SC_T12_UCDi_FeatherValueGain(OOSRMC, OOSRF, ISR_NONMV0);
        MDrv_SC_T12_UCDi_VerticalMovingUdRatio(OOSRMC, OOSRF, ISR_NONMV0);
        MDrv_SC_T12_UCDi_ComplexOffset(OOSRMC, OOSRF, ISR_NONMV0);
        MDrv_SC_T12_UCDi_W2SadGain(OOSRMC, OOSRF, ISR_NONMV0);
        MDrv_SC_T12_KFC_8bitMotionGain(SmallMoving);
        MDrv_SC_T12_UCDi_EODiWGain(OOSRMC, OOSRF, ISR_NONMV0);
        MDrv_SC_T12_UCDi_HistoryRatio(OOSRMC, OOSRF, ISR_NONMV0);
        MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,FeatherSum);
        MDrv_SC_A5_KFC_EODiW(VerticalMoving);
        bL107_en = FALSE;//MDrv_SC_A5_L107(VerticalMoving, HorizontalMoving, TotalFeather, TotalMvComfirm,ColorSum,u32MotionValue, uComplex);
        MDrv_SC_A5_SonyChurch(VerticalMoving, HorizontalMoving, u32MotionValue, bL107_en );
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_UCDI_DRIVER, 0x08);
    }

    // Nikon UCNR function
    if (u8Ctrl & ENABLE_SCALER_MCNR_DRIVER)
    {
        MDrv_SC_mcnr_driver(u32MotionValue2);
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_MCNR_DRIVER, 0x10);
    }


    // Nikon DHD/CCS function
    if (u8Ctrl & ENABLE_SCALER_DHD_CCS_DRIVER)
    {
        if(_bIsHDSource)  //HD Source
        {
            //MDrv_SC_Amber5_DHD_driver1();
            MDrv_SC_Amber5_CCS_driver2(OOSRMC,HorizontalMoving);
            //MDrv_SC_Amber5_DHD_driver2();
        }
        else              //SD Source
        {
            //MDrv_SC_Amber5_CCS_driver();
            MDrv_SC_Amber5_CCS_driver2(OOSRMC,HorizontalMoving);
        }
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_DHD_CCS_DRIVER, 0x20);
    }

    if (u8Ctrl & ENABLE_SCALER_DEFEATHERING)
    {
        MDrv_SC_de_feathering(u32MotionValue);
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_DEFEATHERING, 0x01);
    }

    if (u8Ctrl & ENABLE_SCALER_DEFLICKERING)
    {
        MDrv_SC_de_flickering(u32MotionValue);
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_DEFLICKERING, 0x02);
    }

    if (u8Ctrl & ENABLE_SCALER_DEBOUNCING)
    {
        MDrv_SC_de_bouncing(u32MotionValue2);
        MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,FeatherSum);
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_DEBOUNCING, 0x04);
    }

}

#undef MHAL_PQ_ADAPTIVE_C
