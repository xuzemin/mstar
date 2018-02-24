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
static MS_BOOL bdataread = true;                //For Auto_DBK SW driver used
static MS_BOOL _bIsHDSource = true;             //For Check HD mode
static MS_BOOL bg_bAnyCandenceEnable = true;
static XC_MCNRLutQmapSetting m_stMCNRLutQmapSetting = {{0, 0, 0, 0, 0, 0, 0, 0}};

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
    MS_U32 u32before_MC_feather;
    MS_U32 u32nonMV0_Comfirm, u32MV_Contradict;
    MS_U32 u32MovingFeather, u32MV_Confirm;
    static MS_U32 u32PrevMV_Confirm = 0;

    u32before_MC_feather = MApi_XC_R2BYTE(REG_SC_BK2A_77_L) ;
    u32nonMV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32MV_Contradict = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    u32MV_Confirm = (u32nonMV0_Comfirm + u32MV_Contradict) >> 1;

    u32MV_Confirm = (u32PrevMV_Confirm * 3 + u32MV_Confirm) >> 2;
    u32PrevMV_Confirm = u32MV_Confirm;

    if(u32MV_Confirm > (u32before_MC_feather * MF_Gain))
    {
        u32MovingFeather = u32MV_Confirm - ((u32before_MC_feather * MF_Gain)) ;
    }
    else
    {
        u32MovingFeather = 0;
     }

    return u32MovingFeather;  // "Big": in seach range "Small": out of seach range
}

#define OOSRF_Gain            4
#define OOSRF_Power         2
MS_U32 MDrv_SC_T12_UC_InSearchRange_Feather(void)
{
    MS_U32 u32before_MC_feather, u32after_MC_feather;
    MS_U32 u32MC_OOSRF;
    static MS_U32 u32Prev_before_MC_feather = 0;
    static MS_U32 u32Prev_after_MC_feather = 0;

    u32before_MC_feather = MApi_XC_R2BYTE(REG_SC_BK2A_77_L) ;
    u32after_MC_feather = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);

    u32before_MC_feather = (u32Prev_before_MC_feather * 3 + u32before_MC_feather) >> 2;
    u32Prev_before_MC_feather = u32before_MC_feather;

    u32after_MC_feather = (u32Prev_after_MC_feather * 3 + u32after_MC_feather) >> 2;
    u32Prev_after_MC_feather = u32after_MC_feather;

    if(u32before_MC_feather > (u32after_MC_feather * OOSRF_Gain) >> OOSRF_Power)
    {
        u32MC_OOSRF = u32before_MC_feather - ((u32after_MC_feather * OOSRF_Gain) >> OOSRF_Power) ;
    }
    else
    {
        u32MC_OOSRF = 0;
    }

    return u32MC_OOSRF;  // "Big": in seach range "Small": out of seach range
}

#define OOSRMC_Gain         20
MS_U32 MDrv_SC_T12_UC_InSearchRange_MvComfirm(void)
{
    MS_U32 u32MV0_Comfirm,  u32nonMV0_Comfirm, u32MV_Contradict;
    static MS_U32 u32Prev_MV0_Comfirm = 0;
    static MS_U32 u32Prev_nonMV0_Comfirm = 0;
    static MS_U32 u32Prev_MV_Contradict = 0;
    MS_U32 u32MV_Comfirm, u32MC_OOSRMC;

    u32MV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    u32nonMV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32MV_Contradict = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    u32MV0_Comfirm = (u32Prev_MV0_Comfirm * 3 + u32MV0_Comfirm) >> 2;
    u32Prev_MV0_Comfirm = u32MV0_Comfirm;

    u32nonMV0_Comfirm = (u32Prev_nonMV0_Comfirm * 3 + u32nonMV0_Comfirm) >> 2;
    u32Prev_nonMV0_Comfirm = u32nonMV0_Comfirm;

    u32MV_Contradict = (u32Prev_MV_Contradict * 3 + u32MV_Contradict) >> 2;
    u32Prev_MV_Contradict = u32MV_Contradict;

    u32MV_Comfirm = u32MV0_Comfirm + u32nonMV0_Comfirm;

    if(u32MV_Comfirm > u32MV_Contradict * OOSRMC_Gain)
    {
        u32MC_OOSRMC = u32MV_Comfirm - u32MV_Contradict * OOSRMC_Gain;
    }
    else
    {
        u32MC_OOSRMC = 0;
     }

    return u32MC_OOSRMC;  // "Big": in seach range "Small": out of seach range

}

#define Confirm_Gain         5
MS_U8 MDrv_SC_UC_InSearchRange_MR_Offset(void)
{
    MS_U32 u32MV0_Comfirm,  u32nonMV0_Comfirm, u32MV_Contradict;
    static MS_U32 u32Prev_MV0_Comfirm = 0;
    static MS_U32 u32Prev_nonMV0_Comfirm = 0;
    static MS_U32 u32Prev_MV_Contradict = 0;
    MS_U32 u32MV_Comfirm;
    MS_U8 u8MR_Offset;

    u32MV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    u32nonMV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32MV_Contradict = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    u32MV0_Comfirm = (u32Prev_MV0_Comfirm * 3 + u32MV0_Comfirm) >> 2;
    u32Prev_MV0_Comfirm = u32MV0_Comfirm;

    u32nonMV0_Comfirm = (u32Prev_nonMV0_Comfirm * 3 + u32nonMV0_Comfirm) >> 2;
    u32Prev_nonMV0_Comfirm = u32nonMV0_Comfirm;

    u32MV_Contradict = (u32Prev_MV_Contradict * 3 + u32MV_Contradict) >> 2;
    u32Prev_MV_Contradict = u32MV_Contradict;

    u32MV_Comfirm = u32MV0_Comfirm + u32nonMV0_Comfirm;

    if(u32MV_Comfirm > (u32MV_Contradict * Confirm_Gain))
    {
        u8MR_Offset = u32nonMV0_Comfirm;
    }
    else
    {
        u8MR_Offset = 0;
    }

    return u8MR_Offset;
}

#define ISR_NONMV0_Gain         15
MS_U32 MDrv_SC_T12_UC_InSearchRange_nonMv0Comfirm(void)
{
    MS_U32 u32MV0_Comfirm,  u32nonMV0_Comfirm, u32MV_Contradict;
    static MS_U32 u32Prev_MV0_Comfirm = 0;
    static MS_U32 u32Prev_nonMV0_Comfirm = 0;
    static MS_U32 u32Prev_MV_Contradict = 0;
    MS_U32 u32MV_Comfirm, u32Comfirm_Value;

    u32MV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    u32nonMV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32MV_Contradict = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    u32MV0_Comfirm = (u32Prev_MV0_Comfirm * 3 + u32MV0_Comfirm) >> 2;
    u32Prev_MV0_Comfirm = u32MV0_Comfirm;

    u32nonMV0_Comfirm = (u32Prev_nonMV0_Comfirm * 3 + u32nonMV0_Comfirm) >> 2;
    u32Prev_nonMV0_Comfirm = u32nonMV0_Comfirm;

    u32MV_Contradict = (u32Prev_MV_Contradict * 3 + u32MV_Contradict) >> 2;
    u32Prev_MV_Contradict = u32MV_Contradict;

    u32MV_Comfirm = /*MV0_Comfim +*/u32nonMV0_Comfirm;

    if(u32MV_Comfirm > (u32MV_Contradict * ISR_NONMV0_Gain))
    	{
        u32Comfirm_Value = u32MV_Comfirm - u32MV_Contradict * ISR_NONMV0_Gain;
    	}
    else
    	{
        u32Comfirm_Value = 0;
    	}

    return u32Comfirm_Value;  // "Big": in seach range "Small": out of seach range

}


#define ComplexOffset_MaxValue 0x06
#define ComplexOffset_MinValue 0x00
void MDrv_SC_T12_UCDi_ComplexOffset(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 u16ComplexOffset = ComplexOffset_MaxValue;

    UNUSED(u32OOSRMC);
    UNUSED(u32OOSRF);

    if(u32ISR_NONMV0 > 1000)  //&& OOSRF > 50)
    {
        if(u16ComplexOffset > ComplexOffset_MinValue)
        {
            u16ComplexOffset--;
        }
        else
        {
            u16ComplexOffset = ComplexOffset_MinValue;
        }
    }
    else
    {
        if(u16ComplexOffset < ComplexOffset_MaxValue)
        {
            u16ComplexOffset++;
        }
        else
        {
            u16ComplexOffset = ComplexOffset_MaxValue;
        }
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)u16ComplexOffset << 4, 0x00F0);
}

#define OP1_HisWeight_MaxValue 0x0E
#define OP1_HisWeight_MinValue 0x04
#define A5_HIS_MOTION_TH 0x0A
#define Sd_Feathersum_TH 0x3500
void MDrv_SC_A5_UCDi_OP1_HisWeight(const MS_U32 u32MotionValue,const MS_U32 u32FeatherSum, const MS_BOOL _bIsHD)
{
    static MS_U32 u32reghisweight = OP1_HisWeight_MinValue;
    static MS_U32 u32MotionValue_prev = 0;

    if( u32MotionValue_prev < u32MotionValue )
    {
        u32MotionValue_prev = ((u32MotionValue_prev*3 )+ u32MotionValue ) >> 2;
    }
    else
    {
        u32MotionValue_prev = u32MotionValue;
    }

    if( u32MotionValue_prev < A5_HIS_MOTION_TH )
    {
        u32reghisweight = OP1_HisWeight_MinValue;
    }
    else
    {
        if( u32reghisweight < OP1_HisWeight_MaxValue )
        {
            u32reghisweight++;
        }
        else
        {
            u32reghisweight = OP1_HisWeight_MaxValue;
        }
    }
//printf("Feathersum=%d\n", u32FeatherSum);

	if(!_bIsHD && u32FeatherSum > Sd_Feathersum_TH)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, OP1_HisWeight_MinValue, 0x000e);  // history weight = 6
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, u32reghisweight, 0x000E);
    }
}

#define FeatherValueGain_MaxValue 0x02
#define FeatherValueGain_MinValue 0x00
void MDrv_SC_T12_UCDi_FeatherValueGain(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 u16FeatherValue = FeatherValueGain_MaxValue;

    UNUSED(u32OOSRMC);
    UNUSED(u32OOSRF);

    if(u32ISR_NONMV0 > 1000)  //&& OOSRF > 50)
    {
        if(u16FeatherValue > FeatherValueGain_MinValue)
    {
            u16FeatherValue--;
        }
        else
        {
            u16FeatherValue = FeatherValueGain_MinValue;
        }
    }
    else
    {
        if(u16FeatherValue < FeatherValueGain_MaxValue)
        {
            u16FeatherValue++;
        }
        else
        {
            u16FeatherValue = FeatherValueGain_MaxValue;
    }
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2D_L, (MS_U16)u16FeatherValue << 12, 0xF000);

}

#define W2SadGain_MaxValue 0x0C
#define W2SadGain_MinValue 0x08
void MDrv_SC_T12_UCDi_W2SadGain(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 u16W2SadGain = FeatherValueGain_MaxValue;

    UNUSED(u32OOSRMC);
    UNUSED(u32OOSRF);

    if(u32ISR_NONMV0 > 1000)  //&& OOSRF > 50)
    {
        if(u16W2SadGain < W2SadGain_MaxValue)
    {
            u16W2SadGain++;
        }
        else
        {
            u16W2SadGain = W2SadGain_MaxValue;
        }
    }
    else
    {
        if(u16W2SadGain > W2SadGain_MinValue)
        {
            u16W2SadGain--;
        }
        else
        {
            u16W2SadGain = W2SadGain_MinValue;
        }
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2D_L, (MS_U16)u16W2SadGain << 8, 0x0F00);

}

#define VerticalMovingUdRatio_MaxValue 0x08
#define VerticalMovingUdRatio_MinValue 0x07
void MDrv_SC_T12_UCDi_VerticalMovingUdRatio(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 u16VerticalMovingUdRatioValue = VerticalMovingUdRatio_MaxValue;

    UNUSED(u32OOSRMC);
    UNUSED(u32ISR_NONMV0);

    if( u32OOSRF > 0x300 )
    {
        if(u16VerticalMovingUdRatioValue > VerticalMovingUdRatio_MinValue)
    {
            u16VerticalMovingUdRatioValue--;
        }
        else
        {
            u16VerticalMovingUdRatioValue = VerticalMovingUdRatio_MinValue;
        }
    }
    else
    {
        if(u16VerticalMovingUdRatioValue < VerticalMovingUdRatio_MaxValue)
        {
            u16VerticalMovingUdRatioValue++;
        }
        else
        {
            u16VerticalMovingUdRatioValue = VerticalMovingUdRatio_MaxValue;
        }
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, (MS_U16)u16VerticalMovingUdRatioValue, 0x000F);
}

#define KFC_8bitMotionGain_MaxValue 0x08
#define KFC_8bitMotionGain_MinValue 0x04 //0 have feather issue.
void MDrv_SC_T12_KFC_8bitMotionGain(MS_U32 u32SmallMoving)
{
    static MS_U16 u16KFC_8bitMotionGainValue = KFC_8bitMotionGain_MaxValue;

    if(u32SmallMoving > 500)
    {
        if(u16KFC_8bitMotionGainValue > KFC_8bitMotionGain_MinValue)
    {
            u16KFC_8bitMotionGainValue--;
        }
        else
        {
            u16KFC_8bitMotionGainValue = KFC_8bitMotionGain_MinValue;
        }
    }
    else
    {
        if(u16KFC_8bitMotionGainValue < KFC_8bitMotionGain_MaxValue)
        {
            u16KFC_8bitMotionGainValue++;
        }
        else
        {
            u16KFC_8bitMotionGainValue = KFC_8bitMotionGain_MaxValue;
        }
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_3B_L, (MS_U16)u16KFC_8bitMotionGainValue << 4, 0x00F0);
}

#define UCDi_EODiWGain_MaxValue 0x0F
#define UCDi_EODiWGain_MinValue 0x00
void MDrv_SC_T12_UCDi_EODiWGain(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 u16EODiWGainValue = UCDi_EODiWGain_MaxValue;

    UNUSED(u32OOSRMC);

    if((u32ISR_NONMV0 > 1000) && (u32OOSRF > 50))
    {
        if(u16EODiWGainValue > UCDi_EODiWGain_MinValue)
    {
            u16EODiWGainValue--;
        }
        else
        {
            u16EODiWGainValue = UCDi_EODiWGain_MinValue;
        }
    }
    else
    {
        if(u16EODiWGainValue < UCDi_EODiWGain_MaxValue)
        {
            u16EODiWGainValue++;
        }
        else
        {
            u16EODiWGainValue = UCDi_EODiWGain_MaxValue;
        }
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)u16EODiWGainValue << 12, 0xF000);
}

#define UCDi_HistoryRatio_MaxValue 0x07
#define UCDi_HistoryRatio_MinValue 0x04
void MDrv_SC_T12_UCDi_HistoryRatio(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 u16HistoryRatioValue = UCDi_HistoryRatio_MaxValue;

    UNUSED(u32OOSRMC);

    if((u32ISR_NONMV0 > 1000) && (u32OOSRF > 50))
    {
        if(u16HistoryRatioValue > UCDi_HistoryRatio_MinValue)
    {
            u16HistoryRatioValue--;
        }
        else
        {
            u16HistoryRatioValue = UCDi_HistoryRatio_MinValue;
        }
    }
    else
    {
        if(u16HistoryRatioValue < UCDi_HistoryRatio_MaxValue)
        {
            u16HistoryRatioValue++;
        }
        else
        {
            u16HistoryRatioValue = UCDi_HistoryRatio_MaxValue;
        }
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)u16HistoryRatioValue << 12, 0xF000);
}

#define KFC_EODIW_GAIN_MAX 4
#define KFC_EODIW_GAIN_MIN 0
void MDrv_SC_A5_KFC_EODiW(const MS_U32 u32IsVerticalMoving)
{
    MS_U32 u32Statisticscplxpixel;
    static MS_U32 u32Statisticscplxpixeliir = KFC_EODIW_GAIN_MIN;
    static MS_U32 u32regkfceodiwgain = KFC_EODIW_GAIN_MAX ;

    u32Statisticscplxpixel = ((u32Statisticscplxpixeliir*3 )+ MApi_XC_R2BYTE(REG_SC_BK2A_7F_L) ) >> 2;
    u32Statisticscplxpixeliir = u32Statisticscplxpixel;

    if( (u32IsVerticalMoving < 0x150) && (u32Statisticscplxpixeliir > 0x1000) )
    {
        if( u32regkfceodiwgain > KFC_EODIW_GAIN_MIN )
    {
            u32regkfceodiwgain--;
        }
        else
        {
            u32regkfceodiwgain  = KFC_EODIW_GAIN_MIN;
        }
    }
    else
    {
        if( u32regkfceodiwgain < KFC_EODIW_GAIN_MAX )
        {
            u32regkfceodiwgain++;
        }
        else
        {
            u32regkfceodiwgain = KFC_EODIW_GAIN_MAX;
    }
    }
     MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)u32regkfceodiwgain << 12, 0xF000);
}

#define SONYC_KFC_EN_MAX 1
#define SONYC_KFC_EN_MIN 0
#define SONYC_CPLX_GAIN_MAX 4
#define SONYC_CPLX_GAIN_MIN 0
void MDrv_SC_A5_SonyChurch(const MS_U32 u32IsVerticalMoving, const MS_U32 u32IsHorizontalMoving, const MS_U32 u32MotionValue, const MS_BOOL bL107_en)
{
    static MS_U32 u32regkfcen = SONYC_KFC_EN_MAX ;
    static MS_U32 u32regmcdicplxgain = SONYC_CPLX_GAIN_MAX;

    //IsHorizontalMoving=IsHorizontalMoving;
    if( (u32IsVerticalMoving > 0xF0) && (u32IsHorizontalMoving < 1) && (u32MotionValue > 0x40000) )
{
        if( u32regmcdicplxgain > SONYC_CPLX_GAIN_MIN )
    {
            u32regmcdicplxgain--;
        }
        else
        {
            u32regmcdicplxgain = SONYC_CPLX_GAIN_MIN;
        }

        if( u32regkfcen > SONYC_KFC_EN_MIN )
        {
            u32regkfcen--;
        }
        else
        {
            u32regkfcen = SONYC_KFC_EN_MIN;
    }
    }
    else
    {
        if( u32regmcdicplxgain < SONYC_CPLX_GAIN_MAX )
    {
            u32regmcdicplxgain++;
        }
        else
        {
            u32regmcdicplxgain = SONYC_CPLX_GAIN_MAX;
        }

        if( u32regkfcen < SONYC_KFC_EN_MAX )
        {
            u32regkfcen++;
    }
    else
    {
            u32regkfcen = SONYC_KFC_EN_MAX;
        }
    }

    if( !bL107_en )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_04_L, (MS_U16)u32regkfcen<<1, 0x0002);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)u32regmcdicplxgain<<8, 0x0F00);
    }
}

#define L107_FEATHER_GAIN_MAX 2
#define L107_FEATHER_GAIN_MIN 0
#define L107_CPLX_OFFSET_MAX 6
#define L107_CPLX_OFFSET_MIN 0
#define L107_CPLX_GAIN_MAX 15
#define L107_CPLX_GAIN_MIN 4
MS_BOOL MDrv_SC_A5_L107(const MS_U32 u32IsVerticalMoving, const MS_U32 u32IsHorizontalMoving, const MS_U32 u32TotalFeather, const MS_U32 u32TotalMvComfirm, const MS_U32 u8colorSum,const MS_U32 u32MotionValue, const MS_U32 u32uComplex )
{
    static MS_U32 u32regmcdifeathergain = L107_FEATHER_GAIN_MAX ;
    static MS_U32 u32regmcdicplxoffset = L107_CPLX_OFFSET_MAX ;
    static MS_U32 u32regmcdicplxgain = L107_CPLX_GAIN_MIN ;
MS_BOOL bL107_en;

    if( (u32IsVerticalMoving < 20) && (u32IsHorizontalMoving < 200) && (u32TotalFeather < 100) && (u32TotalMvComfirm > 200) && (u8colorSum > 200) && (u32MotionValue > 0x3500) && (u32uComplex < 0x700))
{
    bL107_en = TRUE;

        if( u32regmcdifeathergain > L107_FEATHER_GAIN_MIN )
        {
            u32regmcdifeathergain--;
        }
    else
        {
            u32regmcdifeathergain = L107_FEATHER_GAIN_MIN;
        }

        if( u32regmcdicplxoffset > L107_CPLX_OFFSET_MIN )
        {
            u32regmcdicplxoffset--;
        }
    else
        {
            u32regmcdicplxoffset = L107_CPLX_OFFSET_MIN;
        }

        if( u32regmcdicplxgain < L107_CPLX_GAIN_MAX )
        {
            u32regmcdicplxgain++;
        }
    else
        {
            u32regmcdicplxgain = L107_CPLX_GAIN_MAX;
        }
}
else
{
    bL107_en = FALSE;

        if( u32regmcdifeathergain < L107_FEATHER_GAIN_MAX )
        {
            u32regmcdifeathergain++;
        }
    else
        {
            u32regmcdifeathergain = L107_FEATHER_GAIN_MAX;
        }

        if( u32regmcdicplxoffset < L107_CPLX_OFFSET_MAX )
        {
            u32regmcdicplxoffset++;
        }
    else
        {
            u32regmcdicplxoffset = L107_CPLX_OFFSET_MAX;
        }

        if( u32regmcdicplxgain > L107_CPLX_GAIN_MIN )
        {
            u32regmcdicplxgain--;
        }
    else
        {
            u32regmcdicplxgain = L107_CPLX_GAIN_MIN;
        }
}

    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2D_L, (MS_U16)u32regmcdifeathergain<<12, 0xF000); // 2 to 0
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)u32regmcdicplxoffset<<4, 0x00F0);// 6 to 0
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)u32regmcdicplxgain<<8, 0x0F00);// 4 to F

return bL107_en;
}

MS_U32 MDrv_SC_A5_ComplexSum(void)
{
    static MS_U32 u32IsComplex_iir = 0xFFFF;
    MS_U32 u32IsComplex;

    u32IsComplex = MApi_XC_R2BYTE(REG_SC_BK2A_7F_L);

    u32IsComplex = (u32IsComplex_iir*3 + u32IsComplex ) >> 2;
    u32IsComplex_iir = u32IsComplex;

    return u32IsComplex_iir;
}

MS_U32 MDrv_SC_A5_KFC_IsVerticalMoving( void )
{
    MS_U32 u32mvc, u32mvu, u32mvd;
    MS_U32 u32mevertical;
    static MS_U32 u32IsVerticalMovingiir = 0;

    u32mvc     = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32mvu     = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32mvd     = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);

    if ((u32mvu > u32mvc) && (u32mvu > u32mvd) /*&& (u32_mvu > 0x200*/)
    {
        if( u32mvu > (u32mvc+u32mvd)/2 )
    {
            u32mevertical = (u32mvu - (u32mvc+u32mvd)/2);
    }
        else
    {
            u32mevertical = 0;
        }
    }
    else if((u32mvd > u32mvc) && (u32mvd > u32mvu) /*&& (u32_mvd > 0x200)*/)
    {
        if( u32mvd > (u32mvc+u32mvu)/2 )
        {
            u32mevertical = (u32mvd - (u32mvc+u32mvu)/2);
        }
        else
        {
            u32mevertical = 0;
        }
    }
    else
    {
        u32mevertical = 0;
    }

    if( u32mevertical > 255 )
    {
        u32mevertical = 255;
    }

    u32mevertical = (u32IsVerticalMovingiir*3 + u32mevertical ) >> 2;
    u32IsVerticalMovingiir = u32mevertical;

    return u32mevertical;
}

MS_U32 MDrv_SC_A5_IsHorizontalMoving(void)
{
    MS_U32 u32mvc, u32mvu, u32mvd;
    MS_U32 u32mehorizontal;
    static MS_U32 u32IsHorizontalMovingiir = 0;

    u32mvc     = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32mvu     = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32mvd     = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);

    if ((u32mvc > u32mvu) && (u32mvc > u32mvd) /*&& (u32_mvu > 0x200*/)
    {
        if( u32mvc > (u32mvu+u32mvd)/2 )
    {
            u32mehorizontal = (u32mvc - (u32mvu+u32mvd)/2);
        }
        else
        {
            u32mehorizontal = 0;
        }
    }
    else
    {
        u32mehorizontal = 0;
    }

    if( u32mehorizontal > 255 )
    {
        u32mehorizontal = 255;
    }

    u32mehorizontal = (u32IsHorizontalMovingiir*3 + u32mehorizontal ) >> 2;
    u32IsHorizontalMovingiir = u32mehorizontal;

    return u32mehorizontal;
}


MS_U32 MDrv_SC_A5_ColorPixelSum(void)
{
   MS_U32 u32colorSum;
   static MS_U32 u32colorSum_iir = 0;

   u32colorSum  = MApi_XC_R2BYTE(REG_SC_BK1A_6E_L);
   u32colorSum  = u32colorSum / 8;

   if( u32colorSum > 255 )
   {
    u32colorSum = 255;
   }

   u32colorSum = ((u32colorSum_iir*3 )+ u32colorSum ) >> 2;
   u32colorSum_iir = u32colorSum;

   return u32colorSum_iir;
}


MS_U32 MDrv_SC_A5_TotalFeather(void)
{
    MS_U32 u32mv0feather, u32nonMv0feather;
    MS_U32 u32totalfeather;
    static MS_U32 u32totalfeatheriir = 255;

    u32mv0feather      = MApi_XC_R2BYTE(REG_SC_BK2A_77_L);
    u32nonMv0feather   = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);

    u32totalfeather = ( u32mv0feather + u32nonMv0feather ) / 4;

    if( u32totalfeather > 255 )
    {
        u32totalfeather = 255;
    }

    u32totalfeather = ((u32totalfeatheriir*3 )+ u32totalfeather ) >> 2;
    u32totalfeatheriir = u32totalfeather;

    return u32totalfeatheriir;
}

MS_U32 MDrv_SC_TotalFeather_Sum(void)
{
    MS_U32 u32mv0_feather, u32nonMv0_feather;
    MS_U32 u32total_feather;
    static MS_U32 u32total_feather_iir = 0;

    u32mv0_feather      = MApi_XC_R2BYTE(REG_SC_BK2A_77_L);
    u32nonMv0_feather   = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);

    u32total_feather =  u32mv0_feather + u32nonMv0_feather;

    u32total_feather = ((u32total_feather_iir*3 )+ u32total_feather ) >> 2;
    u32total_feather_iir = u32total_feather;

    return u32total_feather_iir;
}

#define TOTAL_MV_TIME 10
MS_U32 MDrv_SC_A5_TotalMvComfirm(void)
{
    MS_U32 u32mv0, u32nonMv0, u32notFound;
    MS_U32 u32totalmv, u32mvComfirm;
    static MS_U32 u32mvComfirmiir = 0;

    u32mv0      = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    u32nonMv0   = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32notFound   = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    u32totalmv = u32mv0 + u32nonMv0;

    if( u32totalmv > u32notFound*TOTAL_MV_TIME )
    {
        u32mvComfirm =   u32totalmv - u32notFound*TOTAL_MV_TIME;
    }
    else
    {
        u32mvComfirm = 0;
    }

    if( u32mvComfirm > 255 )
    {
        u32mvComfirm = 255;
    }

    u32mvComfirm = ((u32mvComfirmiir*3 )+ u32mvComfirm ) >> 2;
    u32mvComfirmiir = u32mvComfirm;

    return u32mvComfirmiir;
}

/******************************************************************************/
///Extend MCNR Driver
/******************************************************************************/
void MDrv_SC_Extend_UCNR_driver(void)
{
    MS_U32 u32ismv0, u32nonmv0, u32mvNotFound, u32mvc, u32mvu, u32mvd;
    MS_BOOL bmenotconfirm , bmevertical, bstillpattern;
    static MS_U8 u8notConfirmCnt;
    static MS_U32 u32lastmvNotFound;

    u32ismv0  = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    u32nonmv0 = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32mvNotFound = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);
    u32mvc     = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32mvu     = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32mvd     = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);

    /////////////////////////////////////////////////////////////////
    //  NR Patch 1
    /////////////////////////////////////////////////////////////////
    bmenotconfirm = (u32ismv0 < 0x0200) && (u32nonmv0 < 0x0200) ;
    bmevertical    = ((u32mvu > u32mvc) && (u32mvu > u32mvd) && (u32mvu > 0x200)) ||
                     ((u32mvd > u32mvc) && (u32mvd > u32mvu) && (u32mvd > 0x200));

    bstillpattern = (u32ismv0 < 0x0020) && (u32nonmv0 < 0x0020) && (u32mvNotFound < 0x0020);

    if(!bstillpattern)
    {
        if(false == bmenotconfirm)
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
    }

    if(1)
    {
        if ( (u8notConfirmCnt > 0x30)|| bmevertical ) // low nr strength
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, (MS_U16)0xAAAA, 0xFFFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, (MS_U16)0xAAAA, 0xFFFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, (MS_U16)0xAAAA, 0xFFFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, (MS_U16)0xAAAA, 0xFFFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, (MS_U16)0xAAAA, 0xFFFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, (MS_U16)0xAA98, 0xFFFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, (MS_U16)0x7654, 0xFFFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, (MS_U16)0x3210, 0xFFFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0064, 0x00FF); // moving picture, increase random motion
        }
        else //if(u8notConfirmCnt < 0x10)
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

        if ( (u32ismv0 > 0x200) && ((u32ismv0/2) > u32nonmv0) && ((u32ismv0/2) > u32mvNotFound) )
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0044, 0x00FF); // still picture, reduce random motion
        }
        else if(u32nonmv0 > u32ismv0)
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0044, 0x00FF); // moving picture, increase random motion
        }
        else
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0044, 0x00FF); // default random motion
        }
    }

    u32lastmvNotFound = u32mvNotFound;
}


/******************************************************************************/
///MCNR Driver
/******************************************************************************/
MS_U16 MDrv_SC_NR_LUT_Aux( MS_U16 u16NR_Lut, MS_U8 u8Gain)
{
    u8Gain= u8Gain < 16 ? u8Gain : 16;

    MS_U8 u8H0 = (u16NR_Lut >>  0) & 0xF;
    MS_U8 u8H1 = (u16NR_Lut >>  4) & 0xF;
    MS_U8 u8H2 = (u16NR_Lut >>  8) & 0xF;
    MS_U8 u8H3 = (u16NR_Lut >> 12) & 0xF;

    u8H0 = (u8H0 * u8Gain) >> 4;
    u8H1 = (u8H1 * u8Gain) >> 4;
    u8H2 = (u8H2 * u8Gain) >> 4;
    u8H3 = (u8H3 * u8Gain) >> 4;

    return (u8H3 << 12) | (u8H2 << 8) | (u8H1 << 4) | (u8H0 << 0);
}

    // Update MCNR/PDNR LUT from Qmap
MS_BOOL Hal_PQ_LoadMCNRLutQmapSetting()
{

		    m_stMCNRLutQmapSetting.mcnrLut[0] = MApi_XC_R2BYTE(REG_SC_BK2A_08_L);
		    m_stMCNRLutQmapSetting.mcnrLut[1] = MApi_XC_R2BYTE(REG_SC_BK2A_09_L);
		    m_stMCNRLutQmapSetting.mcnrLut[2] = MApi_XC_R2BYTE(REG_SC_BK2A_0A_L);
		    m_stMCNRLutQmapSetting.mcnrLut[3] = MApi_XC_R2BYTE(REG_SC_BK2A_0B_L);
		    m_stMCNRLutQmapSetting.mcnrLut[4] = MApi_XC_R2BYTE(REG_SC_BK2A_0C_L);
		    m_stMCNRLutQmapSetting.mcnrLut[5] = MApi_XC_R2BYTE(REG_SC_BK2A_0D_L);
		    m_stMCNRLutQmapSetting.mcnrLut[6] = MApi_XC_R2BYTE(REG_SC_BK2A_0E_L);
		    m_stMCNRLutQmapSetting.mcnrLut[7] = MApi_XC_R2BYTE(REG_SC_BK2A_0F_L);		

			return true;
}


void MDrv_SC_mcnr_driver( MS_U32 nonHistoryMotionPixel, MS_BOOL bisHDSource )
{
    MS_U32 u32_is_mv0, u32_non_mv0, u32_mvNotFound, u32_mvFeathering, u32_mvc, u32_mvu, u32_mvd, u32_cplxPixel, u32temp1, u32temp2;
    MS_BOOL bmenotconfirm , bmevertical, bis24to60Hz/*, scene_change*/;
    MS_U8 u8MCNR_Gain=16;
    static MS_U8 u8vMOvingReduceNR_HouseHDPatch_counter;
    static MS_U8 u8notConfirmCnt;
    //static MS_U32 u32lastmvNotFound;
    static MS_U8 u8nrWeightPatchForVSweep = 0;

    XC_ApiStatus stXCStatus;

    if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
    {
        //printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
    }

    bis24to60Hz = (!stXCStatus.bInterlace) && (stXCStatus.u16InputVFreq < 300);

    u32_is_mv0  = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    u32_non_mv0 = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32_mvNotFound = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);
    u32_mvFeathering = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);
    u32_mvc     = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32_mvu     = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32_mvd     = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);
    u32_cplxPixel = MApi_XC_R2BYTE(REG_SC_BK2A_7F_L);


    if ( (u32_cplxPixel > 0x1000) && (u32_is_mv0 > 0x1000) && (nonHistoryMotionPixel == 0) ) // patch for VSweep converge too slow
    {
        if ( u8nrWeightPatchForVSweep > 4 )
        {
            u8nrWeightPatchForVSweep = u8nrWeightPatchForVSweep - 4;
        }
        else
        {
            u8nrWeightPatchForVSweep = 0;
        }
    }
    else
    {
        if ( u8nrWeightPatchForVSweep < 0xD )
        {
            u8nrWeightPatchForVSweep += 1;
        }
    }

    /////////////////////////////////////////////////////////////////
    //  NR Patch 1
    /////////////////////////////////////////////////////////////////
    bmenotconfirm = (u32_is_mv0 < 0x0200) && (u32_non_mv0 < 0x0200);
    bmevertical    = ((u32_mvu > u32_mvc) && (u32_mvu > u32_mvd) && (u32_mvu > 0x200)) ||
                     ((u32_mvd > u32_mvc) && (u32_mvd > u32_mvu) && (u32_mvd > 0x200));

    if(false == bmenotconfirm)
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
            bBool = ( (u8notConfirmCnt > 0x30) || bmevertical ); // low nr strength
        }

        if (bBool) // low nr strength
        {
            if ( !bisHDSource )
            	{
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0064, 0x00FF); // moving picture, increase random motion
            	}
            else
            	{
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x00C2, 0x00FF); // Default 64 -> C2, moving picture, increase random motion
            	}

            if ( u8nrWeightPatchForVSweep >= 7 )
            {
                u8MCNR_Gain=9;
            }
            else //if ( nrWeightPatchForVSweep >= 4 )
            {
                u8MCNR_Gain=7;
            }
        }
        else if(u8notConfirmCnt < 0x10)
        {
            if ( (u8nrWeightPatchForVSweep >= 0xD) && (!bis24to60Hz) )
            {
                u8MCNR_Gain=16;
            }
            else if ( (u8nrWeightPatchForVSweep >= 0xA) && (!bis24to60Hz) )
            {
                u8MCNR_Gain=11;
            }
            else if ( u8nrWeightPatchForVSweep >= 7 )
            {
                u8MCNR_Gain=9;
            }
            else //if ( nrWeightPatchForVSweep >= 4 )
            {
                u8MCNR_Gain=7;
            }
            }
        else
        {
            u8MCNR_Gain=16;
        }
		MS_BOOL bMCNR_LUT_ReloadStart = (MApi_XC_R2BYTEMSK(REG_SC_BK22_7D_L, 0x0100)>>8);
		MS_BOOL bMCNR_LUT_ReloadEnd = (MApi_XC_R2BYTEMSK(REG_SC_BK22_7D_L, 0x0200)>>8);
		static MS_U8 U8_MCNRerror_Cnt = 0;

		if(bMCNR_LUT_ReloadStart)
		{
			if(Hal_PQ_LoadMCNRLutQmapSetting()&& bMCNR_LUT_ReloadEnd)
			{
            MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, 0x0000, 0x0100);
			}
		}
		else if(!bMCNR_LUT_ReloadStart && !bMCNR_LUT_ReloadEnd)
		{
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[0],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[1],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[2],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[3],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[4],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[5],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[6],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[7],u8MCNR_Gain), 0xFFFF);
		}
		else if(bMCNR_LUT_ReloadStart && !bMCNR_LUT_ReloadEnd)
		{
			if(U8_MCNRerror_Cnt>8)
			{
			U8_MCNRerror_Cnt=0;
			bMCNR_LUT_ReloadStart=0;
			bMCNR_LUT_ReloadEnd=0;
			}
			else
			{
			U8_MCNRerror_Cnt++;
			}
		}
		else
		{
		MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, 0x0000, 0x0200);
		}

        if ( bisHDSource && (u32_mvc < 0x10) && (( u32_mvu + u32_mvd ) > 0x40) )
        {
            u8vMOvingReduceNR_HouseHDPatch_counter = 16;
        }
        else if ( (u32_is_mv0 <= 0x10) && (u32_non_mv0 > 0x2000) && (u32_mvNotFound > 0x80) && (u32_mvFeathering > 0x8) && (u32_cplxPixel < 0x200) ) // patch shibasoku a little out-of-search range
        {
            u8vMOvingReduceNR_HouseHDPatch_counter = 16;
        }
        else if ( u8vMOvingReduceNR_HouseHDPatch_counter > 0 )
        {
            u8vMOvingReduceNR_HouseHDPatch_counter --;
        }

        if ( bis24to60Hz )
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x00F0, 0x00FF);
        }
        else if ( (u32_is_mv0 > 0x200) && ((u32_is_mv0/2) > u32_non_mv0) && ((u32_is_mv0/2) > u32_mvNotFound) && (u8vMOvingReduceNR_HouseHDPatch_counter == 0) )
        {
            if ( stXCStatus.bInterlace )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x006c, 0x00FF); // still picture, reduce random motion
            }
            else
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0064, 0x00FF); // still picture, reduce random motion
        }
        }
        else if ( (u32_non_mv0 > u32_is_mv0) || (u8vMOvingReduceNR_HouseHDPatch_counter > 0 )) // moving picture, increase random motion
        {
            if ( !bisHDSource )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0060, 0x00FF);
            }
            else
            {
                if ( stXCStatus.bInterlace )
                {
                    u32temp1 = ( 0xE * u8vMOvingReduceNR_HouseHDPatch_counter + 0x6 * ( 16 - u8vMOvingReduceNR_HouseHDPatch_counter ) ) >> 4;
                    u32temp2 = ( 0x0 * u8vMOvingReduceNR_HouseHDPatch_counter + 0xC * ( 16 - u8vMOvingReduceNR_HouseHDPatch_counter ) ) >> 4;
                }
                else
                {
                    u32temp1 = ( 0xE * u8vMOvingReduceNR_HouseHDPatch_counter + 0x6 * ( 16 - u8vMOvingReduceNR_HouseHDPatch_counter ) ) >> 4;
                    u32temp2 = ( 0x0 * u8vMOvingReduceNR_HouseHDPatch_counter + 0x4 * ( 16 - u8vMOvingReduceNR_HouseHDPatch_counter ) ) >> 4;
                }
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)((u32temp1<<4)|u32temp2), 0x00FF); // 60 -> E0. moving picture, increase random motion
            }
        }
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
    MS_U32 u32regdefetheringlv1cnt;
    MS_U32 u32regdefetheringlv2cnt;
    MS_U32 u32regmdpcnt;

    u32regdefetheringlv1cnt = 0x0A;
    u32regdefetheringlv2cnt = 0x08;
    u32regmdpcnt = 0x01;

    // motion level count
    if(u32MotionValue >= DEFETHERING_LV1_TH)
    {
        if(u32DeFeatherCntLv1 < u32regdefetheringlv1cnt)
        {
            u32DeFeatherCntLv1++;
    }
    }
    else
    {
        if(u32DeFeatherCntLv1 >= u32regmdpcnt)
        {
            u32DeFeatherCntLv1 = u32DeFeatherCntLv1 - u32regmdpcnt;
        }
    }

    if(u32MotionValue >= DEFETHERING_LV2_TH)
    {
        if(u32DeFeatherCntLv2 < u32regdefetheringlv2cnt)
        {
            u32DeFeatherCntLv2++;
    }
    }
    else
    {
        if(u32DeFeatherCntLv2 >= u32regmdpcnt)
        {
            u32DeFeatherCntLv2 = u32DeFeatherCntLv2 - u32regmdpcnt;
        }
    }

    if(u32MotionValue >= DEFETHERING_LV3_TH)
    {
        if(u32DeFeatherCntLv3 < DEFETHERING_LV3_CNT)
        {
            u32DeFeatherCntLv3++;
    }
    }
    else
    {
        if(u32DeFeatherCntLv3 >= u32regmdpcnt)
        {
            u32DeFeatherCntLv3 = u32DeFeatherCntLv3 - u32regmdpcnt;
        }
    }

    //DeFeathering begin
    if(u32DeFeatherCntLv1 >= u32regdefetheringlv1cnt)
    {
        u8SST_Static_Core_TH    = SST_STATIC_CORE_TH_LV1_VALUE;
    }
    else if(u32DeFeatherCntLv2 >= u32regdefetheringlv2cnt)
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
    MS_U32 u32regmfeatsmoothhleth, u32regmfeatsmoothshrink;

    u32regmfeatsmoothhleth = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_1E_L, 0xF000); // Feat Smooth HLE TH
    u32regmfeatsmoothshrink = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_1E_L, 0x8F);

    if(u32MotionValue >= DEFLICKERING_TH)
    {
        if(s32DeFlickerCnt < 65535)
        {
            s32DeFlickerCnt++;
    }
    }
    else
    {
        s32DeFlickerCnt = 0;
    }

    if(s32DeFlickerCnt >= DEFLICKERING_CNT)
    {
        u32regmfeatsmoothhleth += 0x0300;
        u32regmfeatsmoothshrink += 0x10;
    }
    else
    {
        u32regmfeatsmoothhleth += 0x0700;
        u32regmfeatsmoothshrink += 0x30;
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK22_1E_L, u32regmfeatsmoothshrink, 0xFF);
    MApi_XC_W2BYTEMSK(REG_SC_BK22_1E_L, u32regmfeatsmoothhleth, 0xFF00);
}

/******************************************************************************/
///DeBouncing
///@param u32MotionValue \     IN: Motion value
/******************************************************************************/
#define DEBOUNCING_GAIN 1 //0
void MDrv_SC_de_bouncing(MS_U32 u32MotionValue)
{
    static MS_S32 s32DeBouncingCnt = 0;
    MS_U32 u32reghiswtf2;
    MS_U32 u32regdebouncingth;
    MS_U32 u32regdebouncingcnt;

    u32regdebouncingth = 0x0A;
    u32regdebouncingcnt = 0x03;

    u32reghiswtf2 = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK22_0A_L, 0xF8); // history ratio weighting

    MS_BOOL bfilm;
    bfilm = ( (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0008) == 0x0008) ||  // film22
           ( (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0010) == 0x0010) ||  // film32
           ( (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0040) == 0x0040) ;   // film any

    if(u32MotionValue <= u32regdebouncingth * DEBOUNCING_GAIN)
    {
        s32DeBouncingCnt = 0;
    }
    else
    {
        if(s32DeBouncingCnt < 65535)
        {
            s32DeBouncingCnt++;
    }
    }

    if(bfilm || (s32DeBouncingCnt >= (MS_S32)u32regdebouncingcnt))
    {
        u32reghiswtf2 += 0x06; // history = 6 moving
    }
    else
    {
        u32reghiswtf2 += 0x03; // history = 3 still
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK22_0A_L, u32reghiswtf2, 0xFF);
}
#if 0
void MDrv_SC_Amber5_DHD_driver1(void)
{
    // dhd news report patch: enhance dhd strength
    static MS_U32 u32sd2hdCnt = 0;
    MS_U32 u32checkwidth = MApi_XC_R2BYTEMSK(REG_SC_BK12_0F_L, 0xFFFF);
    MS_U32 u32isPAL = (MApi_XC_R2BYTE(REG_SC_BK05_12_L)&0x4000)>>14;

    MS_U8 MV0_Comfirm = MApi_XC_R2BYTE(REG_SC_BK2A_78_L)>>8;

    if((u8SD2HDValue>=60)&&(u32checkwidth>0x700)&&(MV0_Comfirm>0x20)&&(u32isPAL==0)) //When in HD case, detect SD
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
    MS_U32 u32checkwidth = MApi_XC_R2BYTEMSK(REG_SC_BK12_0F_L, 0xFFFF);
    UNUSED(IsHorizontalMoving);

    if (((u8SD2HDValue<10) && (uComplex>200)
        && (u32checkwidth>0x700)) || (VerticalMovingForDHD && (u32checkwidth>0x700) )
        || ( (u8SD2HDValue<5) && (u32checkwidth>0x700)))
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
    MS_U16  u16dataacken;
    //int  temp_data;
    MS_U32  u32blkwidthdata[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    MS_U32  u32blkwidthsdata[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    MS_U32  u32blockinessdata[1440];
    MS_BOOL bblockingpeakidx[1440];
    MS_U32  u32bin;
    MS_U32 u32checkwidth = MApi_XC_R2BYTEMSK(REG_SC_BK12_0F_L, 0xFFFF);
    MS_U32  u32LoopIniStart = (u32checkwidth>0x700) ? ADBW_HD_Loop_Ini_Start : ADBW_SD_Loop_Ini_Start;
    MS_U32  u32MaxRangeEnd = (u32checkwidth>0x700) ? ADBW_HD_Max_Range_End :  ADBW_SD_Max_Range_End;
    MS_U32  u32fmeblockiness;
    MS_U32  u32framemaxind = 0;
    MS_U32  u32localmaxind;
    MS_U32   u32left7,u32right7;
    MS_U32   u32left2 = 0;
    MS_U32   u32right2 = 0;
    MS_U32   u32left1,u32right1;
    MS_U32 u32bestblockwidth = 8;
    MS_U32 u32iirstrength = 2;

    MS_U32 u32DBKframeblockiness = 0;
    MS_U32 u32DBKframeblockinesssum = 0;
    static MS_U32 u32DBKframeblockinessiir = 0;
    MS_U16 u16testdummy  = 0x2500 ; //MApi_XC_R2BYTEMSK(REG_SC_BK30_01_L, 0x7FFF);
    MS_U16 u16testdummy2 = 0x2000 ; //MApi_XC_R2BYTEMSK(REG_SC_BK30_02_L, 0x7FFF);

//    MS_U16 dbk_debug_enable = MApi_XC_R2BYTEMSK(REG_SC_BK0C_40_L, 0x00FF)>>7 ;  //MApi_XC_R2BYTEMSK(REG_SC_BK30_03_L, 0xFFFF)>>15;
    MS_U16 u16dbkiirdiffthrd = 0x12;//MApi_XC_R2BYTEMSK(REG_SC_BK30_03_L, 0x7F00)>>8;
    static MS_U16 u16NMRCtrl=0;
    static MS_U16 u16NMRStrength=0;
    MS_U32 u32iirstrengthNM = 2;
    MS_S32 s32DBKframeblockinessdiff=0;

    static MS_U32 u32preDBKframeblockiness=0;
    MS_U32 u32peakfromblkwidthdata=0;
    static MS_U16 u16NMRStrengthiir = 0 ;
    MS_U16 u16NMRStrengthnew = 0 ;
    MS_U16 u16NMRStrengthnewadjust = 0 ;

    MS_U16 u16testdummy4 = 0 ;//MApi_XC_R2BYTEMSK(REG_SC_BK30_02_L, 0xFFFF)>>15;
    MS_U16 u16dbkapply=0;
    MS_U16  u16countthrd =  0x6 ; //MApi_XC_R2BYTEMSK(REG_SC_BK30_05_L, 0x00FF);
    MS_U16  u16iirdiffthrd =  0x1 ; //MApi_XC_R2BYTEMSK(REG_SC_BK30_05_L, 0xFF00)>>8;

    // setting HD mode enable
    if(u32checkwidth>0x700)
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

    u16dataacken = MApi_XC_R2BYTEMSK(REG_SC_BK0C_0D_L, 0x0002);

    //--------- Blockiness Histogram Acknowledge end   ---------//

    //--------- Function Process start ---------//
    if(u16dataacken)
    {
        // write 1 to sram_io_en register
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 0x100, 0x0100);
        for(u32bin = 0; u32bin < u32MaxRangeEnd; u32bin++)
        {
            // write address
              MApi_XC_W2BYTEMSK(REG_SC_BK0C_0E_L, (MS_U16)(0x8000 + u32bin), 0xFFFF);
            // read data from selected address
            u32blockinessdata[u32bin] = MApi_XC_R2BYTEMSK(REG_SC_BK0C_0F_L, 0xFFFF);
        }

        //printf("blockiness is %d\n",bin);
        //read frame blockiness data
        u32fmeblockiness = ((MApi_XC_R2BYTEMSK(REG_SC_BK0C_61_L, 0xFFFF))<<16) | (MApi_XC_R2BYTEMSK(REG_SC_BK0C_60_L, 0xFFFF));  // frame blockiness data report 32 bit

         MApi_XC_W2BYTEMSK(REG_SC_BK0C_0D_L, 0, 0x0001);
        //printf("fme_blockiness is %d\n\n",fme_blockiness);

        //------- find the max local minmax difference start -------//
        for(u32bin = u32LoopIniStart; u32bin < (u32MaxRangeEnd - 40); u32bin++)
        {
            u32left2 = u32bin - 2;
            u32right2 = u32bin + 2;

            MS_U32 u32locmax = 0;
            MS_U32 u32locmin = 65535;
            MS_U32 u32cnt;

            for(u32cnt = u32left2; u32cnt <= u32right2; u32cnt++)
            {
                //find max
                if(u32blockinessdata[u32cnt] > u32locmax)
                {
                    u32locmax = u32blockinessdata[u32cnt];
                }

                //find min
                if(u32blockinessdata[u32cnt] < u32locmin)
                {
                    u32locmin = u32blockinessdata[u32cnt];
                }
            }

            if(u32locmax > u32locmin)
            {
                u32localmaxind = u32locmax - u32locmin;
            }
            else
            {
                u32localmaxind = 0;
            }

            if(u32localmaxind > u32framemaxind)
            {
                u32framemaxind = u32localmaxind;
            }

        }
        //------- find the max local minmax difference end   -------//

        for(u32bin = 0; u32bin < u32MaxRangeEnd; u32bin++)
            bblockingpeakidx[u32bin] = false;

        //------- find peak index start -------//
        for(u32bin = 0; u32bin < (u32MaxRangeEnd - 40); u32bin++)
        {
            u32left7 = (u32bin < 7) ? 0 : u32bin - 7;
            u32left1 = (u32bin < 1) ? 0 : u32bin - 1;
            u32right1 = u32bin + 1;
            u32right7 = u32bin + 7;

            MS_U32 u32locmax = 0;
            MS_U32 u32locmin = 65535;
            MS_U32 u32cnt;

            for(u32cnt = u32left7; u32cnt <= u32right7; u32cnt++)
            {
                //find max
                if(u32blockinessdata[u32cnt] > u32locmax)
                {
                    u32locmax = u32blockinessdata[u32cnt];
                }

                //find min
                if(u32blockinessdata[u32cnt] < u32locmin)
                {
                    u32locmin = u32blockinessdata[u32cnt];
                 }
            }

            if(u32locmax > u32locmin)
            {
                u32localmaxind = u32locmax - u32locmin;
            }
            else
            {
                u32localmaxind = 0;
            }

            MS_U32 u32Currx2_0 = (u32blockinessdata[u32bin]<<1); // data x 2
            MS_U32 u32Lf12x1_1 = ((u32blockinessdata[u32left1] + u32blockinessdata[u32left2])*11)/10;    // data x 1.1
            MS_U32 u32Rt12x1_1 = ((u32blockinessdata[u32right1] + u32blockinessdata[u32right2])*11)/10;  // data x 1.1
            MS_U32 u32Currx1     = u32blockinessdata[u32bin]; // data x 1
            MS_U32 u32LocMaxx0_99 = (u32locmax*85)/100;  // data x 0.85  // ori is data x 0.99
            MS_U32 u32localmaxin_dx3 = u32localmaxind*3; // data x 3

            if((u32Currx2_0>u32Lf12x1_1)&&(u32Currx2_0>u32Rt12x1_1)&&(u32Currx1>u32LocMaxx0_99)&&(u32localmaxin_dx3>u32framemaxind) && (u32blockinessdata[u32bin] > u32blockinessdata[u32left1]) && (u32blockinessdata[u32bin] > u32blockinessdata[u32right1]))
                bblockingpeakidx[u32cnt] = true;
        }
        //------- find peak index end   -------//

        //------- find best block width start -------//
        MS_U32 u32startidx = 0;

        for(u32bin = 0; u32bin < u32MaxRangeEnd; u32bin++)
        {
            if((bblockingpeakidx[u32bin]==true)&&(u32bin!=u32startidx))
            {
                MS_U32 u32cnt = u32bin - u32startidx;
                if( u32cnt < 31)
                    u32blkwidthdata[u32cnt] += 1;

                u32startidx = u32bin;
            }
        }
        //------- find best block width end   -------//
        //------- summarize 1x3 on blkwidth start -------//
        for(u32bin = 5; u32bin < 31; u32bin ++)
        {
            u32left1 = (u32bin < 1) ? 0 : u32bin - 1;
            u32right1 = (u32bin >= 31) ? 30 : u32bin + 1;

            MS_U32 u32locmax = 0;
            MS_U32 u32cnt;

            for(u32cnt = u32left1; u32cnt <= u32right1; u32cnt++)
            {
                //find max
                if(u32blkwidthdata[u32cnt] > u32locmax)
                    u32locmax = u32blkwidthdata[u32cnt];
            }

            if(u32blkwidthdata[u32bin] > (u32locmax>>1))
                u32blkwidthsdata[u32bin] = u32blkwidthdata[u32left1] + u32blkwidthdata[u32bin] + u32blkwidthdata[u32right1];
        }
        //------- summarize 1x3 on blkwidth end   -------//

        //------- find the 1st max block width start -------//
        MS_U32 u32bestblockcntm = 0;
        MS_U32 u32bestblocklf1 = 0;
        MS_U32 u32bestblockidx = 0;
        MS_U32 u32bestblockrt1 = 0;

        for(u32bin = 5; u32bin < 31; u32bin++)
        {
            if(u32blkwidthsdata[u32bin] > u32bestblockcntm)
            {
                u32bestblockcntm = u32blkwidthsdata[u32bin];
                u32bestblockidx = u32bin;
            }
        }

        u32bestblocklf1 = u32bestblockidx - 1;
        u32bestblockrt1 = u32bestblockidx + 1;
        u32blkwidthsdata[u32bestblockidx] = 0;


        //------- find the 1st max block width end   -------//

        //------- find the 2nd max block width start -------//
        MS_U32 u32bestblockcntm2 = 0;
        MS_U32 u32bestblockidx2 = 0;

        for(u32bin = 5; u32bin < 31; u32bin++)
        {
            if((u32blkwidthsdata[u32bin] > u32bestblockcntm2)&&((u32bin > u32bestblockrt1) || (u32bin < u32bestblocklf1)))
            {
                u32bestblockcntm2 = u32blkwidthsdata[u32bin];
                u32bestblockidx2 = u32bin;
            }
        }

        u32bestblocklf1 = u32bestblockidx2 - 1;
        u32bestblockrt1 = u32bestblockidx2 + 1;
        u32blkwidthsdata[u32bestblockidx2] = 0;

        //------- find the 3rd max block width start -------//
        MS_U32 u32bestblockcntm3 = 0;
        MS_U32 u32bestblockidx3 = 0;

        for(u32bin = 5; u32bin < 31; u32bin++)
        {
            if((u32blkwidthsdata[u32bin] > u32bestblockcntm3)&&((u32bin > u32bestblockrt1) || (u32bin < u32bestblocklf1)))
            {
                u32bestblockcntm3 = u32blkwidthsdata[u32bin];
                u32bestblockidx3 = u32bin;
            }
        }


        //------- find the 3rd max block width end   -------//

#if 0
        if((u8SD2HDValue>=60)&&(u32checkwidth>0x700))
        {
            if((u32bestblockidx>=20)&&(u32bestblockidx<=22)&&(u32bestblockcntm>=5))
            {
                u32bestblockcntm = 100;
            }
            else if((u32bestblockidx2>=20)&&(u32bestblockidx2<=22)&&(u32bestblockcntm2>=5))
            {
                u32bestblockidx = u32bestblockidx2;
                u32bestblockcntm = 100;
            }
            else if((u32bestblockidx3>=20)&&(u32bestblockidx3<=22)&&(u32bestblockcntm3>=5))
            {
                u32bestblockidx = u32bestblockidx3;
                u32bestblockcntm = 100;
            }
        }
#endif

        //------- calculate best block width start -------//
        MS_BOOL bcondition1 = ((u32bestblockcntm<<1) >= (u32bestblockcntm2*3)) ? true : false;    // m1 >= m2*1.5
        MS_BOOL bcondition2 = ((u32bestblockcntm   ) >= (u32bestblockcntm2<<1)) ? true : false;   // m1 >= m3*2
        MS_BOOL bcondition3 = (u32bestblockcntm > 15) ? true : false;
        MS_BOOL bcondition4 = (u32bestblockidx > 6) ? true : false;

        if(bcondition1&& bcondition2&&bcondition3&&bcondition4)
        {
            u32bestblockwidth = u32bestblockidx;

            if(/*(u8SD2HDValue==00)&&*/(u32checkwidth>0x700)&&(u32bestblockwidth==16))
            {
                u32bestblockwidth = 8;
            }

            Pre_DBK_Width_val = u32bestblockwidth;


        }
        else
        {
            if((u32bestblockcntm<u16countthrd)||(u32bestblockidx<=6))
            {
                Pre_DBK_Width_val = 8;

        }



        // iir
        int Pre_DBK_Width_val_tmp = (Pre_DBK_Width_val<<2); // format is xxxxx.xx
        Auto_DBK_Width_val_tmp = ((u32iirstrength*Pre_DBK_Width_val_tmp) + (8-u32iirstrength)*Auto_DBK_Width_val_tmp)/8; // format is xxxxx.xx
        Auto_DBK_Width_val = (Auto_DBK_Width_val_tmp>>2); // format is xxxxx.0

        if(Auto_DBK_Width_val<=8)
        {
            Auto_DBK_Width_val = 8;
            u32left1 = 9;
            u32right1 = 8;
        }
        else
        {
            u32left1 = (Auto_DBK_Width_val < 1) ? 0 : Auto_DBK_Width_val - 1;
            u32right1 = (Auto_DBK_Width_val >=31) ? 31 : Auto_DBK_Width_val + 1;
        }

        // write interval left && interval right
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_39_L, (MS_U16)((u32right1<<8)|u32left1), 0xFFFF);
        //------- calculate best block width end   -------//



        if(bdataread)
        {
            u16NMRCtrl =  MApi_XC_R2BYTEMSK(REG_SC_BK0C_50_L, 0x0001);
            u16NMRStrength = MApi_XC_R2BYTEMSK(REG_SC_BK0C_54_L, 0x003F);
            bdataread = false;
        }

        u32DBKframeblockinesssum=0;
        for(u32bin = 0; u32bin < (u32MaxRangeEnd ); u32bin=u32bin+Auto_DBK_Width_val)
        {
            MS_U32 u32locmax = 0;
            MS_U32 u32locmin = 0xFFFFFFFF;
            MS_U32 u32cnt;

            for(u32cnt = 0; u32cnt <= Auto_DBK_Width_val-1; u32cnt++)
            {
                //find max
                if(((MS_U32)u32blockinessdata[u32bin+u32cnt] > u32locmax)&&((u32bin+u32cnt)<1440))
                {
                    u32locmax = (MS_U32)u32blockinessdata[u32bin+u32cnt];
                }

                //find min
                if(((MS_U32)u32blockinessdata[u32bin+u32cnt] < u32locmin)&&((u32bin+u32cnt)<1440))
                {
                    u32locmin = (MS_U32)u32blockinessdata[u32bin+u32cnt];
                }
            }

            if(u32locmax > u32locmin)
            {
                u32localmaxind = u32locmax - u32locmin;
            }
            else
            {
                u32localmaxind = 0;
            }
            u32DBKframeblockinesssum += u32localmaxind;
        }

        u32DBKframeblockiness = u32DBKframeblockinesssum*Auto_DBK_Width_val / (u32MaxRangeEnd) ;

        s32DBKframeblockinessdiff = abs(u32DBKframeblockiness - u32preDBKframeblockiness);

        if( s32DBKframeblockinessdiff > ((u16dbkiirdiffthrd<<8) ))
        {
            u32iirstrengthNM = 2;
        }
        else
        {
            u32iirstrengthNM = 2;
        }

        u32DBKframeblockinessiir = (u32DBKframeblockiness*u32iirstrengthNM+ u32DBKframeblockinessiir*(8-u32iirstrengthNM))/8;


        u32preDBKframeblockiness = u32DBKframeblockiness;

        u32peakfromblkwidthdata = 0;
        for(u32bin = 8; u32bin < 31; u32bin ++)
        {
            if( u32blkwidthdata[u32bin]> u32peakfromblkwidthdata )
        {
                u32peakfromblkwidthdata = u32blkwidthdata[u32bin];
            }
        }

        if(u16testdummy4)
        {
            if( (abs(Auto_DBK_Width_val - u32bestblockidx)<=2)  &&  (u32peakfromblkwidthdata>=10) )
            {
                u16dbkapply=1;
            }
            else
            {
                u16dbkapply=0;
            }
        }
        else
        {
            if( (abs(Auto_DBK_Width_val - u32bestblockidx)<=2)  ||  (u32peakfromblkwidthdata>=10) )
            {
                u16dbkapply=1;
            }
            else
            {
                u16dbkapply=0;
            }
        }

        if (1)//(fme_blockiness>= (test_dummy3 <<8) )   //0x100000 // multiburst pan
        {
            if(u32DBKframeblockiness>= (0x2500))
            {
                u16NMRCtrl = 1 ;
                u16NMRStrengthnew = 0x3F ;
            }
            else if((u32DBKframeblockiness< (u16testdummy)) && (u32DBKframeblockiness >= (u16testdummy2)))
            {
                u16NMRCtrl = 1 ;
                u16NMRStrengthnew = 0x1f;
            }
            else
            {
                u16NMRStrengthnew = u16NMRStrength;
            }
        }
        else
        {
            u16NMRStrengthnew = u16NMRStrength;
        }

        if(abs(u16NMRStrengthnew*4 - u16NMRStrengthiir)>=(u16iirdiffthrd*4) )
        {
            if((u16NMRStrengthnew*4)>=u16NMRStrengthiir)
            {
                u16NMRStrengthnewadjust = u16NMRStrengthiir + u16iirdiffthrd*4;
                u16NMRStrengthiir = (u16NMRStrengthiir*2+ u16NMRStrengthnewadjust*6)/8;  //*4/8(iir) = /2 ==> X.2 format
            }
            else
            {
                u16NMRStrengthnewadjust = u16NMRStrengthnew*4;
                u16NMRStrengthiir = (u16NMRStrengthiir*0+ u16NMRStrengthnewadjust*8)/8;  //*4/8(iir) = /2 ==> X.2 format
            }
        }
        else
        {
            u16NMRStrengthnewadjust = u16NMRStrengthnew*4;
            u16NMRStrengthiir = (u16NMRStrengthiir*2+ u16NMRStrengthnewadjust*6)/8;  //*4/8(iir) = /2 ==> X.2 format
        }

        MApi_XC_W2BYTEMSK(REG_SC_BK0C_50_L, u16NMRCtrl, 0x0001);
        MApi_XC_W2BYTEMSK(REG_SC_BK0C_54_L, (u16NMRStrengthiir/4+ (u16NMRStrengthiir&2)/2 ), 0x003F);
    }
    //--------- Function Process end   ---------//
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
    bg_bAnyCandenceEnable = bEnable;
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
 MS_U32 u32MotionValue,u32MotionValue2,u32MotionValue3,u32OOSRMC,u32OOSRF,u32ISR_NONMV0,u32SmallMoving,u32VerticalMoving,u32HorizontalMoving,u32TotalFeather,u32TotalMvComfirm;
    MS_U32 u32uComplex,u32FeatherSum,u32MotionValue_Sum;

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

    MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, 0x00, 0xFF); // reset for get correct SW driver status

    // Adaptive functions
    if(_u16PQPre_SrcType != _u16PQSrcType_DBK_Detect[PQ_MAIN_WINDOW])            //For Auto_DBK SW driver used
    {
        _u16PQPre_SrcType = _u16PQSrcType_DBK_Detect[PQ_MAIN_WINDOW];
        bdataread = true;
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
            MDrv_SC_T12_UCDi_FeatherValueGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_UCDi_VerticalMovingUdRatio(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_UCDi_ComplexOffset(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_UCDi_W2SadGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_KFC_8bitMotionGain(u32SmallMoving);
            MDrv_SC_T12_UCDi_EODiWGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_UCDi_HistoryRatio(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,u32FeatherSum, _bIsHDSource);
            MDrv_SC_A5_KFC_EODiW(u32VerticalMoving);
            bL107_en = MDrv_SC_A5_L107(u32VerticalMoving, u32HorizontalMoving, u32TotalFeather, u32TotalMvComfirm,u8ColorSum,u32MotionValue, u32uComplex);
            MDrv_SC_A5_SonyChurch(u32VerticalMoving, u32HorizontalMoving, u32MotionValue, bL107_en );
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_UCDI_DRIVER, 0x08);
    }

    // Nikon UCNR function
    if (u8Ctrl & ENABLE_SCALER_MCNR_DRIVER)
    {
        MDrv_SC_mcnr_driver(u32MotionValue2, _bIsHDSource);
    }


    // Nikon DHD/CCS function
    if (u8Ctrl & ENABLE_SCALER_DHD_CCS_DRIVER)
    {
        if(_bIsHDSource)  //HD Source
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
        MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,u32FeatherSum, _bIsHDSource);
        MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, ENABLE_SCALER_DEBOUNCING, 0x04);
    }

}

#undef MHAL_PQ_ADAPTIVE_C
