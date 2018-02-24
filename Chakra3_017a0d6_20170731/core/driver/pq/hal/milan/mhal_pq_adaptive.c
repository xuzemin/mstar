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
static MS_BOOL bIsHDSource = true;             //For Check HD mode
static MS_BOOL bAnyCandenceEnable = true;
//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#define MaxWidth 4097
#define paraSize 32
static MS_U8 WidthIIR = 8;
//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
MS_S32 minmax(MS_S32 s32TempA, MS_S32 s32TempB, MS_S32 s32TempC) // make sure s32TempB < s32TempC
{
    if (s32TempA<=s32TempB)
        return s32TempB;
    else if (s32TempA >= s32TempC)
        return s32TempC;
    else
        return s32TempA;
}

MS_S32 max(MS_S32 s32TempA, MS_S32 s32TempB)
{
    if (s32TempA>=s32TempB)
        return s32TempA;
    else
        return s32TempB;
}

MS_S32 max3(MS_S32 s32TempA, MS_S32 s32TempB, MS_S32 s32TempC)
{
    if ( (s32TempA>=s32TempB) && (s32TempA>=s32TempC) )
        return s32TempA;
    else if ((s32TempB>=s32TempA) && (s32TempB>=s32TempC) )
        return s32TempB;
    else
        return s32TempC;
}

MS_S32 min(MS_S32 s32TempA, MS_S32 s32TempB)
{
    if (s32TempA>=s32TempB)
        return s32TempB;
    else
        return s32TempA;
}

MS_S32 min3(MS_S32 s32TempA, MS_S32 s32TempB, MS_S32 s32TempC)
{
    if ( (s32TempA<=s32TempB) && (s32TempA<=s32TempC) )
        return s32TempA;
    else if ((s32TempB<=s32TempA) && (s32TempB<=s32TempC) )
        return s32TempB;
    else
        return s32TempC;
}
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
    MS_U8 u8MR_Offset;

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
        u8MR_Offset = nonMV0_Comfirm;
    else
        u8MR_Offset = 0;

    return u8MR_Offset;
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
void MDrv_SC_T12_UCDi_ComplexOffset(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 ComplexOffset = ComplexOffset_MaxValue;

    UNUSED(u32OOSRMC);
    UNUSED(u32OOSRF);

    if(u32ISR_NONMV0 > 1000)
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
void MDrv_SC_A5_UCDi_OP1_HisWeight(const MS_U32 u32MotionValue,const MS_U32 u32FeatherSum,MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{

    static MS_U32 reg_his_weight = OP1_HisWeight_MinValue;
    MS_U8 u8MotionValue;

    //====== Old Mode Start ======================================
    static MS_U32 u32MotionValue_prev = 0;
    //====== Old Mode End =========================================

    if((u32OOSRMC == 0)&&(u32OOSRF == 0)&&(u32ISR_NONMV0 == 0))
    {    // Out Scach Rang

        u8MotionValue = MApi_XC_R2BYTE(REG_SC_BK0A_1A_L)& 0x007F;

        if(u8MotionValue<0x0A)
        {
            reg_his_weight = OP1_HisWeight_MinValue;
        }
        else
        {
	        if(reg_his_weight < OP1_HisWeight_MaxValue )
	            reg_his_weight++;
            else
	            reg_his_weight = OP1_HisWeight_MaxValue;
        }

        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, reg_his_weight, 0x000E);
    }
    else
    {
        //====== Old Mode Start ======================================
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

        if(u32FeatherSum > 0x3500)
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, OP1_HisWeight_MinValue, 0x000e);  // history weight = 6
        }
    	else
    	{
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, reg_his_weight, 0x000E);
        }
    //====== Old Mode End =========================================
    }
}

#define FeatherValueGain_MaxValue 0x02
#define FeatherValueGain_MinValue 0x02
void MDrv_SC_T12_UCDi_FeatherValueGain(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 FeatherValue = FeatherValueGain_MaxValue;

    UNUSED(u32OOSRMC);
    UNUSED(u32OOSRF);

    if(u32ISR_NONMV0 > 1000)
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
void MDrv_SC_T12_UCDi_W2SadGain(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 W2SadGain = W2SadGain_MinValue;

    UNUSED(u32OOSRMC);
    UNUSED(u32OOSRF);

    if(u32ISR_NONMV0 > 1000)
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
void MDrv_SC_T12_UCDi_VerticalMovingUdRatio(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 VerticalMovingUdRatioValue = VerticalMovingUdRatio_MaxValue;

    UNUSED(u32OOSRMC);
    UNUSED(u32ISR_NONMV0);

    if( u32OOSRF > 0x300 )
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
void MDrv_SC_T12_KFC_8bitMotionGain(MS_U32 u32SmallMoving)
{
    static MS_U16 KFC_8bitMotionGainValue = KFC_8bitMotionGain_MaxValue;

    if(u32SmallMoving > 500)
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
void MDrv_SC_T12_UCDi_EODiWGain(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 EODiWGainValue = UCDi_EODiWGain_MaxValue;

    UNUSED(u32OOSRMC);

    if((u32ISR_NONMV0 > 1000) && (u32OOSRF > 50))
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
void MDrv_SC_T12_UCDi_HistoryRatio(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 HistoryRatioValue = UCDi_HistoryRatio_MaxValue;

    UNUSED(u32OOSRMC);

    if((u32ISR_NONMV0 > 1000) && (u32OOSRF > 50))
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
MS_BOOL MDrv_SC_A5_L107(const MS_U32 IsVerticalMoving, const MS_U32 IsHorizontalMoving, const MS_U32 total_feather, const MS_U32 mvComfirm, const MS_U32 colorSum,const MS_U32 u32MotionValue, const MS_U32 u32uComplex )
{
    static MS_U32 reg_mcdi_feather_gain = L107_FEATHER_GAIN_MAX ;
    static MS_U32 reg_mcdi_cplx_offset = L107_CPLX_OFFSET_MAX ;
    static MS_U32 reg_mcdi_cplx_gain = L107_CPLX_GAIN_MIN ;
    MS_BOOL bL107_en;

    if((IsVerticalMoving < 20) && (IsHorizontalMoving < 200) && (total_feather < 100)
    && (mvComfirm > 200) && (colorSum > 200) && (u32MotionValue > 0x3500) && (u32uComplex < 0x700))
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

void MDrv_SC_Amber5_CCS_driver(MS_U32 u32uComplex)
{
    // ccs moving color dot pattern patch: lower ccs strength
    static MS_U32 u32videoCnt = 0;

    if( u32uComplex < 16 )
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

void MDrv_SC_Amber5_CCS_driver2(MS_U32 u32OOSRMC, MS_U32 IsHorizontalMoving)
{
    // horizontal moving => lower ccs weight
    static MS_U32 u32videoCnt = 0;

    if( (u32OOSRMC < 20) || (IsHorizontalMoving >25) )
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
MS_U32 MDrv_SC_read_motion_value4(void)
{
    MS_U32 u32MotionValue;

    u32MotionValue = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK0A_2E_L, 0x7FFF);

    return u32MotionValue;
}
#define ScenceChange_TH        0x1000
 MS_BOOL MDrv_SC_Agate_SceneChangeY(void)
 {
     XC_DLC_ApiStatus DLC_Status;
     MApi_XC_DLC_GetStatus_Ex(&DLC_Status,MAIN_WINDOW);
     static MS_U16 Pre_LumaHistogram[32], Max_HistogramDiff = 0;
     MS_U16 HistogramDiff = 0;
     int i;
     for(i=0;i<32;i++)
     {
         if(DLC_Status.DLCluma.g_wLumaHistogram32H[i] >= Pre_LumaHistogram[i])
         {
             HistogramDiff = DLC_Status.DLCluma.g_wLumaHistogram32H[i] - Pre_LumaHistogram[i];
         }
         else
         {
             HistogramDiff = Pre_LumaHistogram[i] - DLC_Status.DLCluma.g_wLumaHistogram32H[i];
         }

         if(HistogramDiff > Max_HistogramDiff)
         {
             Max_HistogramDiff = HistogramDiff;
         }

         Pre_LumaHistogram[i] = DLC_Status.DLCluma.g_wLumaHistogram32H[i];
     }
     if( Max_HistogramDiff > ScenceChange_TH )
     {
         Max_HistogramDiff = 0;
         return true;
     }
     else
     {
         Max_HistogramDiff = 0;
         return false;
     }
 }
void NoiseMaskingControl(int DBKStr,MS_BOOL isSceneChange)
{
    int NM_Gain = minmax((int)(2.6*DBKStr - 96), 0, 16);
    MApi_XC_W2BYTEMSK(REG_SC_BK0C_52_L, NM_Gain, 0x003F);//Y noise masking gain
    if (isSceneChange )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_50_L, 0x00, 0x0008); //Y noise masking off
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_50_L, 0x08, 0x0008); //Y noise masking on
    }
}
MS_S8 normFactorWidth(MS_U32 u32AvgBLKN)
{
    MS_S8 s8NormFac = 0;
    if (u32AvgBLKN > 1048576*1024)
    {
        s8NormFac = 25;
    }
    else if (u32AvgBLKN > 1048576*512)
    {
        s8NormFac = 24;
    }
    else if (u32AvgBLKN > 1048576*256)
    {
        s8NormFac = 23;
    }
    else if (u32AvgBLKN > 1048576*128)
    {
        s8NormFac = 22;
    }
    else if (u32AvgBLKN > 1048576*64)
    {
        s8NormFac = 21;
    }
    else if (u32AvgBLKN > 1048576*32)
    {
        s8NormFac = 20;
    }
     else if (u32AvgBLKN > 1048576*16)
     {
         s8NormFac = 19;
     }
     else if (u32AvgBLKN > 1048576*8)
     {
         s8NormFac = 18;
     }
     else if (u32AvgBLKN > 1048576*4)
     {
         s8NormFac = 17;
     }
     else if (u32AvgBLKN > 1048576*2)
     {
         s8NormFac = 16;
     }
     else if (u32AvgBLKN > 1048576)
     {
         s8NormFac = 15;
     }
     else if (u32AvgBLKN > 524288)
     {
         s8NormFac = 14;
     }
     else if (u32AvgBLKN > 262144)
     {
         s8NormFac = 13;
     }
     else if (u32AvgBLKN > 131072)
     {
         s8NormFac = 12;
     }
     else if (u32AvgBLKN > 65536)
     {
         s8NormFac = 11;
     }
     else if (u32AvgBLKN > 32768)
     {
         s8NormFac = 10;
     }
     else if (u32AvgBLKN > 16384)
     {
         s8NormFac = 9;
     }
     else if (u32AvgBLKN > 8192)
     {
         s8NormFac = 8;
     }
     else if (u32AvgBLKN > 4096)
     {
         s8NormFac = 7;
     }
     else if (u32AvgBLKN > 2048)
     {
         s8NormFac = 6;
     }
     else if (u32AvgBLKN > 1024)
     {
         s8NormFac = 5;
     }
     else if (u32AvgBLKN > 512)
     {
         s8NormFac = 4;
     }
     else if (u32AvgBLKN > 256)
     {
         s8NormFac = 3;
     }
     else if (u32AvgBLKN > 128)
     {
         s8NormFac = 2;
     }
     else if (u32AvgBLKN > 64)
     {
         s8NormFac = 1;
     }
     else if (u32AvgBLKN > 32)
     {
         s8NormFac = 0;
     }
     else if (u32AvgBLKN > 16)
     {
         s8NormFac = -1;
     }
     else if (u32AvgBLKN > 8)
     {
         s8NormFac = -2;
     }
     else
     {
         s8NormFac = 0;
     }

     return s8NormFac;
 }
 MS_U8 readHistogramPart(/*MS_U16* au16Histogram, */MS_U8 u8CountForDBK/*, MS_U16 u16Initial_point, MS_U16 u16End_point*/)
 {
     MS_U8 u8Data_ack_en;
     //MS_U16 u16Bin;

         //--------- Blockiness Histogram Request start ---------//
     if (u8CountForDBK == 0)
     {
         // write 1 to request register
         MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 1, 0x0001);
     }

     if (1)
     {
         //--------- Blockiness Histogram Acknowledge start ---------//
         u8Data_ack_en = MApi_XC_R2BYTEMSK(REG_SC_BK0C_0D_L, 0x0002) ;
         //--------- Function Process start ---------//
         if(u8Data_ack_en)
         {
             // write 1 to sram_io_en register
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 0x0100, 0x0100);
             /*Remove due2 Milan didn't support Grid mode statistics
             for(u16Bin = u16Initial_point; u16Bin < u16End_point; u16Bin++)
             {
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_0E_L, (MS_U16)(0x8000 + u16Bin), 0xFFFF);
                 // read data from selected address
                 au16Histogram[u16Bin] = MApi_XC_R2BYTEMSK(REG_SC_BK0C_0F_L, 0xFFFF);
             }
             */
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 0, 0x0001);
             return 1;
         }
         else//(!data_ack_en)
         {
             return 0;
         }
     }
}
MS_S8 DBK_WidthPartHW(MS_U16 *u16WidthDiffHW, MS_U16* u16Avg,MS_BOOL isSceneChangeY,MS_U8* u8WidthConfidence)
{
     MS_U8 u8Index;
     MS_U32 u32MaxWidthDiff  = 0;
     MS_U32 u32MinWidthDiff  = 0x7FFFFFFF;
     MS_U32 u32Min2WidthDiff = 0x7FFFFFFF;
     MS_U32 u32Min3WidthDiff = 0x7FFFFFFF;
     MS_U32 u32Min4WidthDiff = 0x7FFFFFFF;
     MS_S8 s8MinIdx = -1, s8Min2Idx = -1, s8Min3Idx = -1, s8Min4Idx = -1;// maxIdx = -1;
     static MS_U8 u8TempWidth = 4;
     MS_U16 u16DiffThrd = 2048;
     static MS_S16 s16ConfidenceLevel8 = 0,s16ConfidenceLevel11 = 0,s16ConfidenceLevel16 = 0,s16ConfidenceLevel21 = 0;
     int log_en = 0;
     //og_en = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK30_01_L, 0x000F); //easter

     u16WidthDiffHW[0 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_40_L,0xFFFF) ; // width 4
     u16WidthDiffHW[1 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_41_L,0xFFFF) ; // width 5
     u16WidthDiffHW[2 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_42_L,0xFFFF) ; // width 6
     u16WidthDiffHW[3 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_43_L,0xFFFF) ; // width 7
     u16WidthDiffHW[4 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_44_L,0xFFFF) ; // width 8
     u16WidthDiffHW[5 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_45_L,0xFFFF) ; // width 9
     u16WidthDiffHW[6 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_46_L,0xFFFF) ; // width 10
     u16WidthDiffHW[7 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_47_L,0xFFFF) ; // width 11
     u16WidthDiffHW[8 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_48_L,0xFFFF) ; // width 12
     u16WidthDiffHW[9 ] = MApi_XC_R2BYTEMSK(REG_SC_BK60_49_L,0xFFFF) ; // width 13
     u16WidthDiffHW[10] = MApi_XC_R2BYTEMSK(REG_SC_BK60_4A_L,0xFFFF) ; // width 14
     u16WidthDiffHW[11] = MApi_XC_R2BYTEMSK(REG_SC_BK60_4B_L,0xFFFF) ; // width 15
     u16WidthDiffHW[12] = MApi_XC_R2BYTEMSK(REG_SC_BK60_4C_L,0xFFFF) ; // width 16
     u16WidthDiffHW[13] = MApi_XC_R2BYTEMSK(REG_SC_BK60_4D_L,0xFFFF) ; // width 17
     u16WidthDiffHW[14] = MApi_XC_R2BYTEMSK(REG_SC_BK60_4E_L,0xFFFF) ; // width 18
     u16WidthDiffHW[15] = MApi_XC_R2BYTEMSK(REG_SC_BK60_4F_L,0xFFFF) ; // width 19
     u16WidthDiffHW[16] = MApi_XC_R2BYTEMSK(REG_SC_BK60_50_L,0xFFFF) ; // width 20
     u16WidthDiffHW[17] = MApi_XC_R2BYTEMSK(REG_SC_BK60_51_L,0xFFFF) ; // width 21
     u16WidthDiffHW[18] = MApi_XC_R2BYTEMSK(REG_SC_BK60_52_L,0xFFFF) ; // width 22
     u16WidthDiffHW[19] = MApi_XC_R2BYTEMSK(REG_SC_BK60_53_L,0xFFFF) ; // width 23
     u16WidthDiffHW[20] = MApi_XC_R2BYTEMSK(REG_SC_BK60_54_L,0xFFFF) ; // width 24
     u16WidthDiffHW[21] = MApi_XC_R2BYTEMSK(REG_SC_BK60_55_L,0xFFFF) ; // width 25
     u16WidthDiffHW[22] = MApi_XC_R2BYTEMSK(REG_SC_BK60_56_L,0xFFFF) ; // width 26
     u16WidthDiffHW[23] = MApi_XC_R2BYTEMSK(REG_SC_BK60_57_L,0xFFFF) ; // width 27
     u16WidthDiffHW[24] = MApi_XC_R2BYTEMSK(REG_SC_BK60_58_L,0xFFFF) ; // width 28
     u16WidthDiffHW[25] = MApi_XC_R2BYTEMSK(REG_SC_BK60_59_L,0xFFFF) ; // width 29
     u16WidthDiffHW[26] = MApi_XC_R2BYTEMSK(REG_SC_BK60_5A_L,0xFFFF) ; // width 30
     u16WidthDiffHW[27] = MApi_XC_R2BYTEMSK(REG_SC_BK60_5B_L,0xFFFF) ; // width 31
     u16WidthDiffHW[28] = MApi_XC_R2BYTEMSK(REG_SC_BK60_5C_L,0xFFFF) ; // width 32
     u16WidthDiffHW[29] = MApi_XC_R2BYTEMSK(REG_SC_BK60_5D_L,0xFFFF) ; // width 33
     u16WidthDiffHW[30] = MApi_XC_R2BYTEMSK(REG_SC_BK60_5E_L,0xFFFF) ; // width 34
     u16WidthDiffHW[31] = MApi_XC_R2BYTEMSK(REG_SC_BK60_5F_L,0xFFFF) ; // width 35

     for(u8Index = 1 ; u8Index < paraSize ; u8Index++)
     {
         if (u16WidthDiffHW[u8Index] > u32MaxWidthDiff)
         {
             u32MaxWidthDiff = u16WidthDiffHW[u8Index];
         }
     }

     for(u8Index = 1 ; u8Index < paraSize -1; u8Index+=2)
     {
         if ( (u8Index==3 || u8Index==11 || u8Index==19 || u8Index==27) && (u16WidthDiffHW[u8Index+1] - u16WidthDiffHW[u8Index ] <= u16DiffThrd) )
         {
             u16WidthDiffHW[u8Index+1]= min(u16WidthDiffHW[u8Index ], u16WidthDiffHW[u8Index+1]);
             u16WidthDiffHW[u8Index  ]= u32MaxWidthDiff;
         }
         else if ( (u8Index==7) && ( (u16WidthDiffHW[u8Index  ] - u16WidthDiffHW[u8Index-1 ] <= u16DiffThrd) || (u16WidthDiffHW[u8Index  ] - u16WidthDiffHW[u8Index+1 ] <= u16DiffThrd)) )
         {
             u16WidthDiffHW[u8Index  ]= min3(u16WidthDiffHW[u8Index ], u16WidthDiffHW[u8Index-1], u16WidthDiffHW[u8Index+1]);
             u16WidthDiffHW[u8Index-1]= u32MaxWidthDiff;
             u16WidthDiffHW[u8Index+1]= u32MaxWidthDiff;
         }
     }

     for(u8Index = 1 ; u8Index < paraSize ; u8Index++)
     {
         (*u16Avg) += u16WidthDiffHW[u8Index];
         if (u16WidthDiffHW[u8Index] < u32MinWidthDiff)
         {
             u32Min4WidthDiff = u32Min3WidthDiff;
             s8Min4Idx = s8Min3Idx;
             u32Min3WidthDiff = u32Min2WidthDiff;
             s8Min3Idx = s8Min2Idx;
             u32Min2WidthDiff = u32MinWidthDiff;
             s8Min2Idx = s8MinIdx;
             u32MinWidthDiff = u16WidthDiffHW[u8Index];
             s8MinIdx = u8Index;
         }
         else if (u16WidthDiffHW[u8Index] < u32Min2WidthDiff)
         {
             u32Min4WidthDiff = u32Min3WidthDiff;
             s8Min4Idx = s8Min3Idx;
             u32Min3WidthDiff = u32Min2WidthDiff;
             s8Min3Idx = s8Min2Idx;
             u32Min2WidthDiff = u16WidthDiffHW[u8Index];
             s8Min2Idx = u8Index;
         }
         else if (u16WidthDiffHW[u8Index] < u32Min3WidthDiff)
         {
             u32Min4WidthDiff = u32Min3WidthDiff;
             s8Min4Idx = s8Min3Idx;
             u32Min3WidthDiff = u16WidthDiffHW[u8Index];
             s8Min3Idx = u8Index;
         }
         else if (u16WidthDiffHW[u8Index] < u32Min4WidthDiff)
         {
             u32Min4WidthDiff = u16WidthDiffHW[u8Index];
             s8Min4Idx = u8Index;
         }
     }

     *u16Avg = (*u16Avg) / (paraSize-1);
    if(isSceneChangeY)
    {
        s16ConfidenceLevel8 = 0;
        s16ConfidenceLevel11 = 0;
        s16ConfidenceLevel16 = 0;
        s16ConfidenceLevel21 = 0;
    }
     s16ConfidenceLevel8 = minmax(s16ConfidenceLevel8,0,16);
     s16ConfidenceLevel11 = minmax(s16ConfidenceLevel11,0,16);
     s16ConfidenceLevel16 = minmax(s16ConfidenceLevel16,0,16);
     s16ConfidenceLevel21 = minmax(s16ConfidenceLevel21,0,16);
     if(s16ConfidenceLevel8>15)
     {
         s16ConfidenceLevel11 = 0;
         s16ConfidenceLevel16 = 0;
         s16ConfidenceLevel21 = 0;
     }
     else if(s16ConfidenceLevel11>15)
     {
         s16ConfidenceLevel8 = 0;
         s16ConfidenceLevel16 = 0;
         s16ConfidenceLevel21 = 0;
     }
     else if(s16ConfidenceLevel16>15)
     {
         s16ConfidenceLevel8 = 0;
         s16ConfidenceLevel11 = 0;
         s16ConfidenceLevel21 = 0;
     }
     else if(s16ConfidenceLevel21>15)
     {
         s16ConfidenceLevel8 = 0;
         s16ConfidenceLevel16 = 0;
         s16ConfidenceLevel11 = 0;
     }

     if(log_en==5)
     {
         printf("s8MinIdx:%d s8Min2Idx:%d s8Min3Idx:%d s8Min4Idx:%d\n",s8MinIdx,s8Min2Idx,s8Min3Idx,s8Min4Idx);
         printf("u16ConfidenceLevel8:%d u16ConfidenceLevel11:%d\n",s16ConfidenceLevel8,s16ConfidenceLevel11);
         printf("u16ConfidenceLevel16:%d u16ConfidenceLevel21:%d\n",s16ConfidenceLevel16,s16ConfidenceLevel21);
     }
     *u8WidthConfidence = max3(s16ConfidenceLevel8,s16ConfidenceLevel11,s16ConfidenceLevel16);
     *u8WidthConfidence = max((*u8WidthConfidence),s16ConfidenceLevel21);
     /*if(u8TempWidth == 4 )//&& s16ConfidenceLevel8>10)
     {
         if((abs(s8MinIdx-u8TempWidth) <2)||(abs(s8Min2Idx-u8TempWidth) <2)||(abs(s8Min3Idx-u8TempWidth) <2)||(abs(s8Min4Idx-u8TempWidth) <2))
         {
             return 4;
         }
     }
     else*/
     if(u8TempWidth == 7 && s16ConfidenceLevel11>10)
     {
         if ((((s8MinIdx == 7) || (s8Min2Idx == 7) || (s8Min3Idx == 7) || (s8Min4Idx == 7))|| ((s8MinIdx == 16) || (s8Min2Idx == 16) || (s8Min3Idx == 16) || (s8Min4Idx == 16))
                 || ((s8MinIdx == 17) || (s8Min2Idx == 17) || (s8Min3Idx == 17) || (s8Min4Idx == 17)) ) && ((s8MinIdx == 28) || (s8Min2Idx == 28) || (s8Min3Idx == 28) || (s8Min4Idx == 28)))
         {
            s16ConfidenceLevel11++;
             return 7;
         }
         else if((abs(s8MinIdx-u8TempWidth) <2)||(abs(s8Min2Idx-u8TempWidth) <2)||(abs(s8Min3Idx-u8TempWidth) <2)||(abs(s8Min4Idx-u8TempWidth) <2))
         {
            s16ConfidenceLevel11--;
             return 7;
         }
     }
     else if(u8TempWidth == 17 && s16ConfidenceLevel21>10)
     {
          if ((((s8MinIdx == 16 || s8Min2Idx == 16 || s8Min3Idx == 16) || (s8MinIdx == 18 || s8Min2Idx == 18 || s8Min3Idx == 18) ) && (s8MinIdx == 17 || s8Min2Idx == 17 || s8Min3Idx == 17)))
         {
            s16ConfidenceLevel21++;
             u8TempWidth = 17;
             return 17;
         }
         else if((abs(s8MinIdx-u8TempWidth) <4)||(abs(s8Min2Idx-u8TempWidth) <4)||(abs(s8Min3Idx-u8TempWidth) <4)||(abs(s8Min4Idx-u8TempWidth) <4))
         {
            s16ConfidenceLevel21--;
             return 17;
         }
     }

     if ((((s8MinIdx == 7) || (s8Min2Idx == 7) || (s8Min3Idx == 7) || (s8Min4Idx == 7))|| ((s8MinIdx == 16) || (s8Min2Idx == 16) || (s8Min3Idx == 16) || (s8Min4Idx == 16))
             || ((s8MinIdx == 17) || (s8Min2Idx == 17) || (s8Min3Idx == 17) || (s8Min4Idx == 17)) ) && ((s8MinIdx == 28) || (s8Min2Idx == 28) || (s8Min3Idx == 28) || (s8Min4Idx == 28)))
     {
         if(u8TempWidth == 7)
         {
             s16ConfidenceLevel11++;
         }
         else
         {
             s16ConfidenceLevel8--;
             s16ConfidenceLevel16--;
             s16ConfidenceLevel21--;
         }
         u8TempWidth = 7;
         return 7;
     }
     else if ((((s8MinIdx == 16 || s8Min2Idx == 16 || s8Min3Idx == 16) || (s8MinIdx == 18 || s8Min2Idx == 18 || s8Min3Idx == 18) ) && (s8MinIdx == 17 || s8Min2Idx == 17 || s8Min3Idx == 17)))
     {
         if(u8TempWidth == 17)
         {
             s16ConfidenceLevel21++;
         }
         else
         {
             s16ConfidenceLevel8--;
             s16ConfidenceLevel16--;
             s16ConfidenceLevel11--;
         }
         u8TempWidth = 17;
         return 17;
     }

     if (s8MinIdx == 4 || s8Min2Idx == 4 || s8Min3Idx == 4 || s8Min4Idx == 4)
     {
         if(u8TempWidth == 4)
         {
             s16ConfidenceLevel8++;
         }
         else
         {
             s16ConfidenceLevel11--;
             s16ConfidenceLevel16--;
             s16ConfidenceLevel21--;
         }
         u8TempWidth = 4;
         return 4;
     }
     else if (s8MinIdx == 12 || s8Min2Idx == 12 || s8Min3Idx == 12 || s8Min4Idx == 12)
     {
        if(u8TempWidth == 12)
        {
            s16ConfidenceLevel16++;
        }
        else
        {
            s16ConfidenceLevel8--;
            s16ConfidenceLevel11--;
            s16ConfidenceLevel21--;
        }
         u8TempWidth = 12;
         return 12;
     }

     return -1;
 }
 MS_S8 DBK_WidthPartTop(MS_U16 *u16WidthDiffHW, MS_U16* u16MaxMinDiff, MS_U16* u16Avg,MS_BOOL isSceneChangeY,MS_U8* u8WidthConfidence)
 {
     MS_U8 u8Bin;
     MS_U32 u32MinValue = 0x7FFFFFFF;
     MS_U16 u16MaxValue = 0;
     MS_S8 s8NormFac;
     MS_S8 s8MinIndex;
     s8MinIndex = DBK_WidthPartHW(u16WidthDiffHW, u16Avg,isSceneChangeY,u8WidthConfidence);
     if (s8MinIndex == -1)
     {
         for (u8Bin =0; u8Bin<paraSize;u8Bin++)
         {
             if (u16WidthDiffHW[u8Bin] > u16MaxValue )
            {
                 u16MaxValue = u16WidthDiffHW[u8Bin];
            }

             if (u16WidthDiffHW[u8Bin] < u32MinValue )
            {
                 u32MinValue = u16WidthDiffHW[u8Bin];
            }
         }
         *u16MaxMinDiff = u16MaxValue - u32MinValue;
         s8NormFac = normFactorWidth(*u16MaxMinDiff);
         if(s8NormFac >0)
         {
             for (u8Bin=0;u8Bin<paraSize;u8Bin++)
             {
                 u16WidthDiffHW[u8Bin] = (u16WidthDiffHW[u8Bin] - u32MinValue) >> s8NormFac;
             }
             *u16Avg = (*u16Avg-u32MinValue) >> s8NormFac;
             *u16MaxMinDiff = (*u16MaxMinDiff) >>s8NormFac;
         }
         else if(s8NormFac ==0)
         {
             for (u8Bin=0;u8Bin<paraSize;u8Bin++)
             {
                 u16WidthDiffHW[u8Bin] = (u16WidthDiffHW[u8Bin] - u32MinValue);
             }
             *u16Avg = (*u16Avg-u32MinValue);
             *u16MaxMinDiff = (*u16MaxMinDiff);
         }
         else
         {
             s8NormFac = 0-s8NormFac;
             for (u8Bin=0;u8Bin<paraSize;u8Bin++)
             {
                 u16WidthDiffHW[u8Bin] = (u16WidthDiffHW[u8Bin] - u32MinValue) << s8NormFac;
             }
             *u16Avg = (*u16Avg-u32MinValue) <<s8NormFac;
             *u16MaxMinDiff = (*u16MaxMinDiff) <<s8NormFac;
         }
         return -1;
     }
     else
     {
         return s8MinIndex;
     }
 }
 void WidthIIR_H(MS_U8 u8Width) // Width IIR Protection
 {
     static MS_U8 u8HysteresisCount = 0;
     static MS_U8 u8LastWidth = 8;
     int log_en = 0;
     //log_en = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK30_01_L, 0x000F); //easter
     if(u8HysteresisCount<6)
     {
         if(log_en==5)
         {
             printf("new width:%d last width:%d final width:%d hysteresisCount:%d\n",u8Width,u8LastWidth,WidthIIR,u8HysteresisCount);
         }

         if(u8Width == u8LastWidth)
         {
             u8HysteresisCount = 0;
             WidthIIR = u8Width;
         }
         else
         {
             u8HysteresisCount++;
             WidthIIR = u8LastWidth;
         }
     }
     else
     {
         WidthIIR = u8Width;
         u8HysteresisCount = 0;
     }
     u8LastWidth = WidthIIR;
 }
 MS_S8 DBK_ComputeWidthPart(  MS_U16 *u16WidthDiffHW,MS_U8 u8LastminIdex, MS_U16 u16Avg,MS_U8 u8WidthConfidence)
 {
     MS_BOOL bWidthCandidate[paraSize];
     MS_U16 u16WTh = u16Avg;
     MS_U8 u8MinIndex=0;
     MS_U8 u8NumW=0;
     MS_U8 u8Bin;
     MS_BOOL bIf8 = 0, bIf11 = 0, bIf21 = 0, bIf32 = 0;

     for (u8Bin=0;u8Bin<paraSize;u8Bin++)
     {
         if (u16WidthDiffHW[u8Bin]<= u16WTh)
         {
             bWidthCandidate[u8Bin] = 1;
         }
         else
         {
             bWidthCandidate[u8Bin] = 0;
         }

     }

     if(bWidthCandidate[u8LastminIdex] ==1 && u8WidthConfidence>10)
     {
         return u8LastminIdex;
     }
     else
     {
         if (bWidthCandidate[4] == 1 ) //8
         {
             if (bWidthCandidate[3] == 1) //7
                 bWidthCandidate[3]  = 0;
             if (bWidthCandidate[11] == 1) // 15
                 bWidthCandidate[11] = 0;
             if (bWidthCandidate[12] == 1) // 16
                 bWidthCandidate[12] = 0;
             if (bWidthCandidate[19] == 1) // 23
                 bWidthCandidate[19] = 0;
             if (bWidthCandidate[20] == 1) // 24
                 bWidthCandidate[20] = 0;
             bIf8 = 1;
         }
         if (bWidthCandidate[7] == 1 ) //11
         {
             if (bWidthCandidate[6] == 1) //10
                 bWidthCandidate[6]  = 0;
             if (bWidthCandidate[8] == 1) //12
                 bWidthCandidate[8]  = 0;
             bIf11 = 1;
         }
         if ( ( bWidthCandidate[16] == 1 ) || ( bWidthCandidate[17] == 1 ) ||( bWidthCandidate[18] == 1 ) ) //20 21 22
         {
             bWidthCandidate[16] = 0;
             bWidthCandidate[17] = 1;
             bWidthCandidate[18] = 0;
             bIf21 = 1;
         }
         if ( bWidthCandidate[27] == 1 && bWidthCandidate[28] == 1)
             bIf32 = 1;
         if (bIf11 && bIf21 && bIf32) //11/21/32 all true -> source = 11 ->delete 21
         {
             bWidthCandidate[17] = 0;
         }
         if (bIf8 || bIf11 || bIf21)
         {
             if (bWidthCandidate[27] == 1) // 31
                 bWidthCandidate[27] = 0;
             if (bWidthCandidate[28] == 1) // 32
                 bWidthCandidate[28] = 0;
         }

     }

     for (u8Bin=0;u8Bin<paraSize;u8Bin++) // count number of frequencies
     {
         if (bWidthCandidate[u8Bin] == 1)
         {
             u8MinIndex = u8Bin;
             u8NumW++;
         }
     }
     if (u8NumW == 1)
     {
         return u8MinIndex;
     }
     else
     {
         return -1;
     }
 }
 void WidthToRegister(MS_U8 u8Width) // Write width to register
 {
     MS_U8 u8Left1,u8Right1;
     if(u8Width<8)
     {
         u8Width = 8;
         u8Left1 = 8;
         u8Right1 = 9;
     }
     else if (u8Width==8) //test 0808 for performance
     {
         u8Left1 = 8;
         u8Right1 = 8;
     }
     else
     {
         u8Left1 = u8Width - 1; //fix prevent defect
         u8Right1 = (u8Width >=31) ? 31 : u8Width + 1;
     }
     //write interval left && interval right
     MApi_XC_W2BYTEMSK(REG_SC_BK0C_39_L, (MS_U16)((u8Left1<<8)|u8Right1), 0xFFFF);
 }
 MS_U8 DBK_Width_Detect(MS_BOOL isSceneChangeY)//width detection with hardware accelaration
 {
     MS_S8 s8MinIndex = -1;     //minIndex+width_offset = candidate width
     //For width calculation
     //int WidthCandidate[paraSize];
     MS_U16 au16WidthDiffHW[paraSize];
     MS_U16 u16MaxMinDiff = 0;
     MS_U16 u16WidthAvg = 0;
     MS_U8 u8Width = 8;
     static MS_U8 u8LastminIdex = 4;
     MS_U8 u8WidthConfidence = 0;
     int log_en = 0;
     //log_en = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK30_01_L, 0x000F); //easter
     u16MaxMinDiff = 0;
     u16WidthAvg = 0;

     s8MinIndex = DBK_WidthPartTop( au16WidthDiffHW, &u16MaxMinDiff, &u16WidthAvg,isSceneChangeY,&u8WidthConfidence);

     if (s8MinIndex == -1)
     {
         s8MinIndex = DBK_ComputeWidthPart( au16WidthDiffHW ,u8LastminIdex, u16WidthAvg,u8WidthConfidence);
     }

     if (s8MinIndex >= 0 && u8Width != 32)			//if (width == 32) //no such pattern yet, only artificials
     {
         u8Width = s8MinIndex + 4;
     }
     else
     {
         u8Width = 8;//can't find any possible width set to default value
     }

     WidthIIR_H(u8Width);
     WidthToRegister(WidthIIR);
     //FeedBackSD2HD(WidthIIR, 0);

     if(log_en==5)
     {
         printf("**bforeIIR[%d]********\n",u8Width);
         printf("*********[%d]*********\n",WidthIIR);
         printf("**Confiden[%d]*********\n",u8WidthConfidence);
     }

     u8LastminIdex = WidthIIR -4;

     return WidthIIR;
 }

 void Mdrv_PQ_DBK(MS_BOOL isSceneChangeY,MS_U32 u32MotionValue,MS_U16 u16Width)
 {
    u16Width=u16Width;

         //DBK Variables
     //static MS_U16 au16Histogram[MaxWidth] = {0};
     static MS_BOOL bDBK_initial = 0;
     MS_U8 u8ReadDBKHistAck = 0;
     //MS_U16 u16Scan_range = 320;
     //MS_U16 u16Initial_point = 160;
     //MS_U16 u16End_point = u16Initial_point+u16Scan_range;
     static MS_U8 u8CountForSample = 0;
     static MS_U8 u8CountForDBK = 0;
     static MS_U8 u8Widdth = 8;
     //MS_U32 u32Strength[paraSize] = {0};
     //static MS_U32 u32Strength_IIR[paraSize] ={0};
     //MS_U8 u8MaxBin = 0;
     //MS_U32 u32TotalStrength = 0;
     //MS_U32 u32StrengthLPF =0;
     //MS_U32 u32AvergeStrength = 1;
     MS_U16 u16Bin = 0;
     static MS_U8 au8MaxBin_pre[6] = {0};
     //MS_U8 u8Pre_bin = 0;
     //MS_S8 s8Boundary_left;
     //MS_U8 u8Boundary_right;
     //static double maxbin_thrd = 1.1;
     //MS_U32 u32Max_bin_thrd = 0;

     static MS_U32 u32StaticValueTemp=0,u32StaticCount=0;
     //int log_en = 0;
     //log_en = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK30_01_L, 0x000F); //easter

    if (isSceneChangeY)
    {
        u8CountForDBK = 0;
        for(u16Bin=0;u16Bin<6;u16Bin++)
        {
         au8MaxBin_pre[u16Bin] = 0;
        }
    }
    if(u32MotionValue ==0 && u32StaticValueTemp==0)
    {
        u32StaticCount++;
    }
    else
    {
        u32StaticCount = 0;
    }
    u32StaticValueTemp = u32MotionValue;

    //if((u16End_point+u16Scan_range*u8CountForSample) > u16Width)
    //{
    //    u8CountForSample = 0;
    //}


     //u16Initial_point =u16Initial_point + u16Scan_range*u8CountForSample;
     //u16End_point = u16End_point+u16Scan_range*u8CountForSample;

    if ( (u8CountForDBK == 0)  )	// Read Histogram
    {
        u8ReadDBKHistAck = readHistogramPart(/*au16Histogram, */u8CountForDBK/*, u16Initial_point, u16End_point*/);
        bDBK_initial = bDBK_initial | true;
        if((u8ReadDBKHistAck==1)&& (u32StaticCount < 15))
        {
            u8Widdth = DBK_Width_Detect(isSceneChangeY);
        }

        if (u8ReadDBKHistAck)
        {
            u8CountForDBK++;
        }
    }
    else if  (u8CountForDBK == 1)
    {
        if ( bDBK_initial == 1)
        {
            /* Milan HW didn't support Grid mode statistics
            for (u16Bin = u16Initial_point; u16Bin <u16End_point; u16Bin++)
            {
                u32Strength[(u16Bin)%u8Widdth] += (au16Histogram[u16Bin]>>8);
            }

            for (u16Bin = 0; u16Bin <u8Widdth; u16Bin++)
            {
                u32Strength_IIR[u16Bin] = (6*u32Strength_IIR[u16Bin] + 2*u32Strength[u16Bin])>>3;
                u32TotalStrength += u32Strength_IIR[u16Bin];
            }

            if(u8Widdth==8)
            {
                maxbin_thrd = 1.1;
            }
            else
            {
                maxbin_thrd = 1.0;
            }

            u32AvergeStrength = max(u32TotalStrength/u8Widdth, 1);
            u32Max_bin_thrd = u32AvergeStrength*(maxbin_thrd);

            if(log_en == 1)
            {
                printf(" ===== states iir start=======\n");
                for(u16Bin = 0; u16Bin <u8Widdth; u16Bin++)
                {
                    printf(" %d = %5ld\n",u16Bin,u32Strength_IIR[u16Bin]);
                }
                printf(" ===== states iir end=======\n");
            }

            for (u16Bin = 0; u16Bin < u8Widdth; u16Bin++)
            {
                if (u16Bin == 0)
                {
                    u32StrengthLPF = (2*u32Strength_IIR[u16Bin]+ u32Strength_IIR[u16Bin+1] + u32Strength_IIR[u8Widdth-1])>>2;
                }
                else if (u16Bin == u8Widdth-1)
                {
                    u32StrengthLPF = (2*u32Strength_IIR[u16Bin]+ u32Strength_IIR[u16Bin-1] + u32Strength_IIR[0])>>2;
                }
                else
                {
                    u32StrengthLPF = (2*u32Strength_IIR[u16Bin]+ u32Strength_IIR[u16Bin-1] + u32Strength_IIR[u16Bin+1])>>2;
                }

            //if (str3pt >  maxStr)
            //{
            //    maxStr = str3pt;
            //}

                if(log_en ==1)
                {
                    printf("u32StrengthLPF:%ld u32Max_bin_thrd:%ld\n",u32StrengthLPF,u32Max_bin_thrd);
                }

                if (u32StrengthLPF >  u32Max_bin_thrd)
                {
                    u32Max_bin_thrd = u32StrengthLPF;
                    au8MaxBin_pre[u8CountForSample] = u16Bin;
                }
                else if(u32Strength_IIR[u16Bin] > u32Max_bin_thrd)
                {
                    u32Max_bin_thrd = u32Strength_IIR[u16Bin];
                    au8MaxBin_pre[u8CountForSample] = u16Bin;
                }
                else
                {
                    u8Pre_bin = (u8CountForSample-1<0)?u8CountForSample:(u8CountForSample-1);
                    au8MaxBin_pre[u8CountForSample] = au8MaxBin_pre[u8Pre_bin];
                }
            }

            for(u16Bin = 0;u16Bin<(u8CountForSample+1);u16Bin++)
            {
                u8MaxBin+= au8MaxBin_pre[u16Bin];
                if(log_en ==1)
                {
                    printf("au8MaxBin_pre[%d]:%d u8CountForSample:%d\n",u16Bin,au8MaxBin_pre[u16Bin],u8CountForSample);
                }
            }

            u8MaxBin = u8MaxBin/(u8CountForSample+1);
            u32AvergeStrength = max(u32TotalStrength/u8Widdth, 1);

            if(u8Widdth%4 == 0)
            {
                 s8Boundary_left = u8MaxBin - u8Widdth/4;
                 u8Boundary_right = u8MaxBin + u8Widdth/4;
            }
            else if(u8Widdth%4 == 1)
            {
                 s8Boundary_left = u8MaxBin - u8Widdth/4;
                 u8Boundary_right = u8MaxBin + u8Widdth/4;
            }
            else if(u8Widdth%4 == 2)
            {
                 s8Boundary_left = u8MaxBin - (u8Widdth/4);
                 u8Boundary_right = u8MaxBin + (u8Widdth/4+1);
            }
            else
            {
                 s8Boundary_left = u8MaxBin - (u8Widdth/4+1);
                 u8Boundary_right = u8MaxBin + (u8Widdth/4+1);
            }

            if(s8Boundary_left < 0)
            {
                 s8Boundary_left = s8Boundary_left+u8Widdth;
            }

            if(u8Boundary_right >=u8Widdth)
            {
                 u8Boundary_right = u8Boundary_right -u8Widdth;
            }

            if(log_en ==5)
            {
             printf("=====Final Width:[%d]=====\n",u8Widdth);
             printf("=====Motion :[%lu]=====\n",u32MotionValue);
             printf("===u32StaticCount:%ld===\n",u32StaticCount);
            }

             //static double percentage_offset = 0.0;
             //MS_U8 u8DBKGain_hw=0;
             //MS_U8 u8DBK_coase_TH = 2;
             //MS_U8 u8DetailGain_hw = 2;
             //MS_U8 u8STD_Threshold_hw=0;
             //MS_U16 u16GridReport_l = 0;
             // MS_U16 u16GridReport_m = 0;
             //MS_U16 u16Non_gridReport_l = 0;
             //MS_U16 u16Non_gridReport_m = 0;
             //MS_U32 u32GridReport_sum=0;
             //MS_U32 u32Non_gridReport_sum=0;
             //MS_U32 u32Total_Report_sum=0;
             //MS_U32 u32AvgReport =25000000,u32DiffReport = 5000000;
             //static MS_U32 u32GridReport_sumIIR=0;
             //static MS_U32 u32Non_gridReport_sumIIR=0;
             //double gridReport_percent = 0.0;
             //double adaptiveRatio_hwReport = 0.0,adjust_step = 0.02;
             //double scaleUp_factor_w11 = 1.0;
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_29_L, s8Boundary_left+(u8Boundary_right<<8), 0x1F1F);
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_28_L, u8Widdth, 0x1F1F);

            if(u8Widdth == 11)
            {
             scaleUp_factor_w11 = 1.2;
            }
            else
            {
             scaleUp_factor_w11 = 1.0;
            }

            u16Non_gridReport_l = MApi_XC_R2BYTEMSK(REG_SC_BK0C_60_L, 0xFFFF);
            u16Non_gridReport_m = MApi_XC_R2BYTEMSK(REG_SC_BK0C_61_L, 0xFFFF);
            u16GridReport_l = MApi_XC_R2BYTEMSK(REG_SC_BK0C_68_L, 0xFFFF);
            u16GridReport_m = MApi_XC_R2BYTEMSK(REG_SC_BK0C_69_L, 0xFFFF);
            u32GridReport_sum= (u16GridReport_l + (u16GridReport_m<<16));
            u32Non_gridReport_sum = (u16Non_gridReport_l + (u16Non_gridReport_m<<16));
            u32GridReport_sumIIR = (6*u32GridReport_sumIIR + 2*u32GridReport_sum)>>3;
            u32Non_gridReport_sumIIR = (6*u32Non_gridReport_sumIIR + 2*u32Non_gridReport_sum)>>3;
            gridReport_percent = (float)u32GridReport_sumIIR/(float)(u32GridReport_sumIIR+u32Non_gridReport_sumIIR);
            gridReport_percent = gridReport_percent*scaleUp_factor_w11;
            u32Total_Report_sum = u32GridReport_sumIIR+u32Non_gridReport_sumIIR;

            if((gridReport_percent > 0.5) && (u32Total_Report_sum > u32AvgReport) && ((u32GridReport_sumIIR - u32Non_gridReport_sumIIR) > u32DiffReport))
            {//for black white water flow ,both of blocky and detail are strong which can't be distinguish by the ratio of blocky/total
                percentage_offset+= adjust_step;
                //printf("percentage_offset:%d\n",(int)(percentage_offset*100));
            }
            else
            {
                percentage_offset-= adjust_step;
            }
            percentage_offset = minmax((int)(percentage_offset*100.0), 0, 20);
            percentage_offset/=100.0;

            if(gridReport_percent > 0.7)
            {
             adaptiveRatio_hwReport = 3.6*(gridReport_percent+percentage_offset) -0.92;
            }
            else if(gridReport_percent > 0.5)
            {
             adaptiveRatio_hwReport = 6.9*(gridReport_percent+percentage_offset) -3.4;
            }
            else
            {
             adaptiveRatio_hwReport = 0;
            }



            u8DetailGain_hw = 76.503*(gridReport_percent+percentage_offset) - 37.154;
            u8DBK_coase_TH = 20.0*(gridReport_percent+percentage_offset) - 8.0;

            if(log_en ==1)
            {
             printf(" Max bin :%05d width:%5d u32AvergeStrength:%5ld\n", u8MaxBin,u8Widdth,u32AvergeStrength);
             printf("left:%5d right:%5d\n",s8Boundary_left,u8Boundary_right);
             printf("total_bin:%ld u16Width:%d\n",u32TotalStrength,u16Width);
             printf("grid_report :%lx non-grid report:%lx bin:%d\n",u32GridReport_sum,u32Non_gridReport_sum,u8MaxBin);
             printf("gridReport_percent:%d u32GridReport_sumIIR:%ld u32Non_gridReport_sumIIR:%ld\n",(int)(100*gridReport_percent),u32GridReport_sumIIR,u32Non_gridReport_sumIIR);
            }
             //int strDiff = max( 0, (maxStr-avgStr) );
             //adaptiveRatio_cur = (float)(strDiff)/(float)avgStr;
             //adaptiveRatio = adaptiveRatio_cur;
             //int binCnt = 1;
             //old method
             //adaptiveRatioIIR = (adaptiveRatioIIR*13 + adaptiveRatio*3 ) / 16;
             //dbkGain = (int)(8 + 8*adaptiveRatioIIR);
             //detailGain = max(6-(int)6*adaptiveRatioIIR, 0);
             //STD_Th = minmax((int)(63*adaptiveRatioIIR), 0x3F, 0xFF);

             //new method with HW Accelerator
            u8DBKGain_hw = (int)(8 + 8*adaptiveRatio_hwReport);
            u8DBK_coase_TH = minmax(u8DBK_coase_TH, 0x02, 0x06);
            u8DetailGain_hw = minmax((int)(u8DetailGain_hw), 0x02, 0x0A);
            u8STD_Threshold_hw = minmax((int)(63*adaptiveRatio_hwReport), 0x3F, 0xFF);
            u8DBKGain_hw = minmax(u8DBKGain_hw, 0x8, 0xF);

            if(u8Widdth == 21 ||u8Widdth == 16)//Scaling up SD2HD
            {
             u8STD_Threshold_hw = 0xBF ;
             u8DBKGain_hw = 0x0F;
             u8DBK_coase_TH = 0x0A;
             u8DetailGain_hw = 0x0F;
             gridReport_percent = 0.7;
            }


            if(log_en ==1)
            {
             printf("adaptiveRatio_hwReport:[%3d] \n",(int)(adaptiveRatio_hwReport*64));
             printf("u8DBKGain_hw:[%3d] u8DBK_coase_TH:[%3d]\n",u8DBKGain_hw,u8DBK_coase_TH);
             printf("u8DetailGain_hw:[%3d]\n ",u8DetailGain_hw);
             printf("u8STD_Threshold_hw:[%3d]\n ",u8STD_Threshold_hw);
            }


             NoiseMaskingControl((int)(gridReport_percent*64), isSceneChangeY);
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_11_L, u8DBKGain_hw, 0x000F); //DBK Gain
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_10_L, u8STD_Threshold_hw<<8, 0xFF00); //DBK STD threshold
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_40_L, (u8DBK_coase_TH<<8), 0xFF00); //DBK coase threshold
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, (u8DetailGain_hw<<12), 0xF000); //blockness gain
             MApi_XC_W2BYTEMSK(REG_SC_BK60_14_L, 0x000F, 0x000F); //User coring threshold
             MApi_XC_W2BYTEMSK(REG_SC_BK60_30_L, 0x0008, 0x0008); //cont3
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_41_L, 0x0000, 0x0001); //hd mode disable
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_71_L, 0x0000, 0x00C0); //switch to Y 5tap filter
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_72_L, 0x0002, 0x0006); //smooth step 1
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_02_L, 0x0002, 0x0006); //switch to C 3tap filter
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 0x0904, 0x0F87); //blockness extend disable/switch pulse filter
             if(u8Widdth == 21 ||u8Widdth == 16)//Scaling up SD2HD
             {
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_41_L, 0x0001, 0x0001); //hd mode enable
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_71_L, 0x00C0, 0x00C0); //switch to Y 7tap filter
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_02_L, 0x0006, 0x0006); //switch to C 7tap filter
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_72_L, 0x0000, 0x0006); //smooth step 0
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 0x0A86, 0x0F87); //blockness extend enable/switch pulse filter
             }
             */
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_41_L, 0x0000, 0x0001); //hd mode disable
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_71_L, 0x0000, 0x00C0); //switch to Y 5tap filter
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_72_L, 0x0002, 0x0006); //smooth step 1
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_02_L, 0x0002, 0x0006); //switch to C 3tap filter
             MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 0x0904, 0x0F87); //blockness extend disable/switch pulse filter
             if(u8Widdth == 21 ||u8Widdth == 16)//Scaling up SD2HD
             {
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_41_L, 0x0001, 0x0001); //hd mode enable
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_71_L, 0x00C0, 0x00C0); //switch to Y 7tap filter
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_02_L, 0x0006, 0x0006); //switch to C 7tap filter
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_72_L, 0x0000, 0x0006); //smooth step 0
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_42_L, 0x0A86, 0x0F87); //blockness extend enable/switch pulse filter
             }
        }
        u8CountForDBK++;
        u8CountForSample++;

    }
    if (u8CountForDBK >= 2)
    {
        u8CountForDBK = 0;
    }
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
    bAnyCandenceEnable = bEnable;
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
    MS_U8  u8Ctrl,u8ColorSum,u8MR_Offset;
    MS_U32 u32MotionValue,u32MotionValue2,u32MotionValue3,u32MotionValue4,u32OOSRMC,u32OOSRF,u32ISR_NONMV0,u32SmallMoving,u32VerticalMoving,u32HorizontalMoving,u32TotalFeather,u32TotalMvComfirm;
    MS_U32 u32uComplex,u32FeatherSum,u32MotionValue_Sum;

    XC_ApiStatus stXCStatus;
    MS_BOOL bL107_en;
    MS_BOOL isSceneChangeY = MDrv_SC_Agate_SceneChangeY();
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
		bIsHDSource= true;
    }
    else
    {
		bIsHDSource= false;
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
    u32MotionValue4 = MDrv_SC_read_motion_value4();
    //
    // Get UCDi status
    //
    u32OOSRMC = MDrv_SC_T12_UC_InSearchRange_MvComfirm();
    u32OOSRF = MDrv_SC_T12_UC_InSearchRange_Feather();
    u32ISR_NONMV0 = MDrv_SC_T12_UC_InSearchRange_nonMv0Comfirm();
    u32SmallMoving = MDrv_SC_T12_UC_SmallMoving();
    u32VerticalMoving = MDrv_SC_A5_KFC_IsVerticalMoving();

    u32HorizontalMoving = MDrv_SC_A5_IsHorizontalMoving();
    u32TotalFeather = MDrv_SC_A5_TotalFeather();
    u32FeatherSum = MDrv_SC_TotalFeather_Sum();
    u32TotalMvComfirm = MDrv_SC_A5_TotalMvComfirm();
    u8ColorSum = MDrv_SC_A5_ColorPixelSum();
    u32uComplex = MDrv_SC_A5_ComplexSum();
    u8MR_Offset = MDrv_SC_UC_InSearchRange_MR_Offset();
    u32MotionValue_Sum = u32MotionValue2 + u8MR_Offset;

    //printf("OOSRMC: %d\n\n",u32OOSRMC);
    //printf("OOSRF: %d\n\n",u32OOSRF);
    //printf("ISR_NONMV0: %d\n\n",u32ISR_NONMV0);

    MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, 0x00, 0xFF); // reset for get correct SW driver status

    // Adaptive functions
    if(_u16PQPre_SrcType != _u16PQSrcType_DBK_Detect[PQ_MAIN_WINDOW])            //For Auto_DBK SW driver used
    {
        _u16PQPre_SrcType = _u16PQSrcType_DBK_Detect[PQ_MAIN_WINDOW];
        data_read = true;
    }

    // Milan AutoDBK function
    if (u8Ctrl & ENABLE_SCALER_AUTO_DBK_DRIVER)               //New Add for AUTO DBK Test
    {
        if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
        {
            printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
        }
        Mdrv_PQ_DBK(isSceneChangeY,u32MotionValue4,stXCStatus.stCropWin.width);
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_AUTO_DBK_DRIVER, 0x40);
    }


    // Milan UCDi function
    if (u8Ctrl & ENABLE_SCALER_UCDI_DRIVER)
    {
        MDrv_SC_T12_UCDi_FeatherValueGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
        MDrv_SC_T12_UCDi_VerticalMovingUdRatio(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
        MDrv_SC_T12_UCDi_ComplexOffset(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
        MDrv_SC_T12_UCDi_W2SadGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
        MDrv_SC_T12_KFC_8bitMotionGain(u32SmallMoving);
        MDrv_SC_T12_UCDi_EODiWGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
        MDrv_SC_T12_UCDi_HistoryRatio(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
        MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,u32FeatherSum,u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
        MDrv_SC_A5_KFC_EODiW(u32VerticalMoving);
        bL107_en = FALSE;//MDrv_SC_A5_L107(VerticalMoving, HorizontalMoving, TotalFeather, TotalMvComfirm,ColorSum,u32MotionValue, uComplex);
        MDrv_SC_A5_SonyChurch(u32VerticalMoving, u32HorizontalMoving, u32MotionValue, bL107_en );
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_UCDI_DRIVER, 0x08);
    }

    // Milan UCNR function
    if (u8Ctrl & ENABLE_SCALER_MCNR_DRIVER)
    {
        MDrv_SC_mcnr_driver(u32MotionValue2);
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_MCNR_DRIVER, 0x10);
    }


    // Milan DHD/CCS function
    if (u8Ctrl & ENABLE_SCALER_DHD_CCS_DRIVER)
    {
        if(bIsHDSource)  //HD Source
        {
            //MDrv_SC_Amber5_DHD_driver1();
            MDrv_SC_Amber5_CCS_driver2(u32OOSRMC,u32HorizontalMoving);
            //MDrv_SC_Amber5_DHD_driver2();
        }
        else              //SD Source
        {
            //MDrv_SC_Amber5_CCS_driver();
            MDrv_SC_Amber5_CCS_driver2(u32OOSRMC,u32HorizontalMoving);
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
        MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,u32FeatherSum,u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_DEBOUNCING, 0x04);
    }

}

static MS_BOOL bFakeOutCusEnable = FALSE;

MS_BOOL Hal_PQ_SetFakeOutEnable(MS_BOOL bEnable)
{
    bFakeOutCusEnable = bEnable;
    return FALSE;
}

#undef MHAL_PQ_ADAPTIVE_C
