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

#ifndef UNUSED //to avoid compile warnings...
#define UNUSED(var) (void)((var) = (var))
#endif

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
extern MS_U16 _u16PQSrcType_DBK_Detect[PQ_MAX_WINDOW]; //For Auto_DBK SW driver used

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static MS_U16 _u16PQPre_SrcType = 255;          //For Auto_DBK SW driver used
static MS_BOOL bg_bSd_source = true;             //For Check SD mode
static MS_BOOL bdataread = true;                //For Auto_DBK SW driver used
static MS_BOOL bg_bAnyCandenceEnable = TRUE;

static XC_MCNRLutQmapSetting m_stMCNRLutQmapSetting = {{0, 0, 0, 0, 0, 0, 0, 0}};     //For UCNR LUT PQ Excel

//-------------------------------------------------------------------------------------------------
//  Local Variables for DBK
//-------------------------------------------------------------------------------------------------
#define MaxWidth 4097
#define paraSize 32
static MS_U8 WidthIIR = 8;
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
MS_U32 MDrv_SC_read_motion_value4(void)
{
    MS_U32 u32MotionValue;

    u32MotionValue = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK0A_2E_L, 0x7FFF);

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

/******************************************************************************/
///Read SDHDD Detect Threshold value
///@return MS_U16: HDSDD_Det_Threshold value
/******************************************************************************/
MS_U16 MDrv_SC_read_HDSDD_Det_Threshold_value(void)
{
    MS_U16 u16Value;

    u16Value = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK22_7F_L, 0xFFFF);

    return u16Value;
}

/******************************************************************************/
///MCDi Driver
/******************************************************************************/
#define     ENABLE_XXX_V_MOVING     0x01
#define     ENABLE_XXX_SST          0x02
#define     ENABLE_XXX_EodiWeight   0x04

void MDrv_SC_mcdi_driver(MS_U32 u32MotionValue)
{
    MS_U32 u32Reg78, u32Reg79, u32Reg7A, u32Reg7B, u32Reg7C, u32Reg7D, u32Reg7E, u32filmFeatherCount;
    MS_U32 u32curCounter3, u32cntDiff;
    MS_U8 u8xxxCtrl;
    MS_BOOL bverticalMovingU, bhorizontalMoving, bslowMotion, bfeatheringScene, bfeatheringScene2;
    static MS_U8 u8SkipCnt;
    static MS_U8 u8featheringFrameCount;
    static MS_U8 u8s8DeBouncingCnt;
    static MS_U8 u8stillFrameCnt;
    static MS_U8 u8filmCnt = 0;
    static MS_U32 u32preCounter3 = 0;
    static MS_U8 u8eodiCnt = 0;
    MS_BOOL bskipCond;
    MS_BOOL bverticalMoving2;
    MS_BOOL bfilmDisableMCDiDFK;

    u8xxxCtrl = 0xFF; //MApi_XC_R2BYTE(REG_SC_BK2A_1F_L) >> 8;

    u32Reg78 = MApi_XC_R2BYTE(REG_SC_BK2A_78_L);
    u32Reg79 = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32Reg7A = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);
    u32Reg7B = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L);
    u32Reg7C = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32Reg7D = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32Reg7E = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);
    u32filmFeatherCount = MApi_XC_R2BYTE(REG_SC_BK0A_0B_L);

    if(MApi_XC_GetMirrorModeType() == MIRROR_NORMAL)
    {
        //Non_Mirror
        bverticalMovingU = (u32Reg7E > 0x0100) && (u32Reg7E > 8 * u32Reg7C) && (u32Reg7E > 8 * u32Reg7D);
        bverticalMoving2 = (((u32Reg7E > 0x200) && (u32Reg7E > u32Reg7C)) || ((u32Reg7D > 0x200) && (u32Reg7D > u32Reg7C)));
        bhorizontalMoving = (u32Reg79 > 0x200) && (u32Reg7B < 0x40) && (u32Reg79 > u32Reg78) && (!bverticalMoving2);
        bslowMotion = (u32Reg7A > 0x200) && (u32Reg7B < 0x40) && (!bverticalMoving2);
        bfeatheringScene = (u32Reg7B > 0x100) && (u32Reg7B > u32Reg79 / 4) && (u32Reg7B > u32Reg7A / 4);
        bskipCond = (u32Reg7A > 8 * u32Reg79) && (u32Reg7B > 0x600);
        bfeatheringScene2 = (u32Reg7B > 0x200) && (u32Reg7B > u32Reg79 / 8) && (u32Reg7B > u32Reg7A / 8);
    }
    else
    {
        //Mirror
        bverticalMovingU = (u32Reg7D > 0x0100) && (u32Reg7D > 8 * u32Reg7C) && (u32Reg7D > 8 * u32Reg7E);
        bverticalMoving2 = (((u32Reg7D > 0x200) && (u32Reg7D > u32Reg7C)) || ((u32Reg7E > 0x200) && (u32Reg7E > u32Reg7C)));
        bhorizontalMoving = (u32Reg79 > 0x200) && (u32Reg7B < 0x40) && (u32Reg79 > u32Reg78) && (!bverticalMoving2);
        bslowMotion = (u32Reg7A > 0x200) && (u32Reg7B < 0x40) && (!bverticalMoving2);
        bfeatheringScene = (u32Reg7B > 0x100) && (u32Reg7B > u32Reg79 / 4) && (u32Reg7B > u32Reg7A / 4);
        bskipCond = (u32Reg7A > 8 * u32Reg79) && (u32Reg7B > 0x600);
        bfeatheringScene2 = (u32Reg7B > 0x200) && (u32Reg7B > u32Reg79 / 8) && (u32Reg7B > u32Reg7A / 8);
    }

    if(false == bskipCond)
    {
        if(u8SkipCnt == 0)
        {
            u8SkipCnt = 0;
        }
        else
        {
            u8SkipCnt--;
        }
    }
    else
    {
        if(u8SkipCnt > 0x40)
        {
            u8SkipCnt = 0x40;
        }
        else
        {
            u8SkipCnt++;
        }
    }

    if(u32filmFeatherCount > 0x100)
    {
        if(u8featheringFrameCount < 0x80)
        {
            u8featheringFrameCount ++;
        }
    }
    else
    {
        u8featheringFrameCount = 0;
    }

    if((u32MotionValue == 0) && (u32Reg7B < 0x20))
    {
        if(u8stillFrameCnt < 0x20)
        {
            u8stillFrameCnt ++;
        }
    }
    else
    {
        u8stillFrameCnt = 0;
    }

    ////////////////////////////////////////////////////////////////
    //  film content disable mcdi/dfk
    ////////////////////////////////////////////////////////////////
    u32curCounter3 = MApi_XC_R2BYTE(REG_SC_BK0A_0B_L);

    u32cntDiff = (u32preCounter3 > u32curCounter3) ? u32preCounter3 - u32curCounter3 : u32curCounter3 - u32preCounter3;

    if(u32cntDiff > 0x1500)
    {
        if(u8filmCnt != 10)
        {
            u8filmCnt++;
        }
    }
    else if(u8filmCnt != 0)
    {
        u8filmCnt--;
    }

    u32preCounter3 = u32curCounter3;
    bfilmDisableMCDiDFK = (u8filmCnt > 5);

    ////////////////////////////////////////////////////////////////
    //  eodi counter
    ////////////////////////////////////////////////////////////////
    if(bfeatheringScene2)
    {
        if(u8eodiCnt < 40)
        {
            u8eodiCnt += 4;
        }
    }
    else
    {
        if(u8eodiCnt > 0)
        {
            u8eodiCnt--;
        }
    }

    /////////////////////////////////////////////////////////////////
    //  SST (De-Feathering)
    /////////////////////////////////////////////////////////////////
    if(u8xxxCtrl & ENABLE_XXX_SST)
    {
        if(bfeatheringScene || bfilmDisableMCDiDFK)       // moving & feather
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_29_L, (MS_U16)0x3100, 0xFF00); // increase SST weighting with checking feathering...
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0100, 0x0F00); // SST motion shift1
        }
        else if((u32Reg79 > 0x200) && (u32Reg7B < 0x40))    // patch sony temple
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_29_L, (MS_U16)0x1100, 0xFF00); // default SST setting
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0200, 0x0F00); // SST motion shift1
        }
        else
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_29_L, (MS_U16)0x3100, 0xFF00); // default SST setting
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0100, 0x0F00); // SST motion shift1
        }
    }

    // disable DFK when verticalMovingU
    if((true == bverticalMovingU) || (u8SkipCnt > 0x20) || bfilmDisableMCDiDFK)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, (MS_U16)0x0000, 0xFFFF); // disable DFK
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0000, 0xF000); // disable DFK
    }
    else if(bverticalMoving2)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, (MS_U16)0xA8FF, 0xFFFF); // default DFK
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0000, 0xF000); // default DFK
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, (MS_U16)0xA8FF, 0xFFFF); // default DFK
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x2000, 0xF000); // default DFK
    }

    // Favor MCDi-V when verticalMovingU
    if(true == bverticalMovingU)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_04_L, (MS_U16)0x0800, 0x0800); // Enable MCDi-V
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_34_L, (MS_U16)0x0FF0, 0xFFFF); // favor MCDi Weight
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_36_L, (MS_U16)0x2800, 0x3C00); // enable MCDi U for blending and history
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x4000, 0xF000); // reduce motion history
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_04_L, (MS_U16)0x0000, 0x0800); // Disable MCDi-V
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_34_L, (MS_U16)0x8888, 0xFFFF); // default MCDi Weight
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_36_L, (MS_U16)0x0000, 0x3C00); // Use MCDi-H as default
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x4000, 0xF000); // default MCDi motion history
    }

    // DFK EodiW1, 2
    if((u8s8DeBouncingCnt < 0x3) || bfilmDisableMCDiDFK)      //new add
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0080, 0x00F0); // reduce DFK EodiWeight
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x4c30, 0xFF30); // disable EodiW for DFK
    }
    else if((true == bverticalMovingU) || bverticalMoving2)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0010, 0x00F0); // increase EodiW ->  tower
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x4c10, 0xFF30); // default
    }
    else if((false == bverticalMovingU) && bslowMotion)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0080, 0x00F0); // reduce DFK EodiWeight
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x0c30, 0xFF30); // disable EodiW for DFK
    }
    else if(MApi_XC_R2BYTEMSK(REG_SC_BK2A_1F_L, BIT(8)))  // RF/AV default, eodi weight strong
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0010, 0x00F0); // increase EodiW
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x18F1, 0xFF30); // default
    }
    else // default
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0040, 0x00F0); // default DFK EodiWeight
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x0c10, 0xFF30); // default
    }

    if(MApi_XC_R2BYTEMSK(REG_SC_BK2A_1F_L, BIT(8)))   // RF/AV default, eodi weight strong
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4488, 0x00F0);
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x0020, 0x00F0);
     }

    // DFK check feathering gain
    if((u8stillFrameCnt > 0x8) || bfilmDisableMCDiDFK)    //new add
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0100, 0x0F00);
    }
    else if((false == bverticalMovingU) && bslowMotion)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0800, 0x0F00); // reduce DFK feathering weight
    }
    else if(u32Reg7B > 0x100)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0f00, 0x0F00); // feather -> increase
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0f00, 0x0F00); // default
    }

    // EodiWeight for MCDi
    if(true == bverticalMovingU)
    {
        if((u32Reg7A > 0x100) && (u32Reg7A / 2 > u32Reg79))  // not-found >> horizontal : Church
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0004, 0x000F); // reduce EodiWeight for MCDi
            MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4800, 0xFF0F); // church
        }
        else //  Tower
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0004, 0x000F); // increase EodiWeight for MCDi
            MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4200, 0xFF0F); //  Tower
        }
    }
    else if((false == bverticalMovingU) && bhorizontalMoving)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0002, 0x000F); // reduce EodiWeight for MCDi
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x1800, 0xFF0F); // reduce EodiW for MCDi
    }
    else if(MApi_XC_R2BYTEMSK(REG_SC_BK2A_1F_L, BIT(8)))  // RF/AV default, eodi weight strong
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0002, 0x000F); // increase EodiWeight for MCDi
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4408, 0xFF0F);
    }
    else if(u8eodiCnt > 25)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0001, 0x000F); // default EodiWeight for MCDi
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4400, 0xFF0F);
    }
    else if(u8eodiCnt < 10)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0002, 0x000F); // default EodiWeight for MCDi
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4800, 0xFF0F);
    }

    if(MApi_XC_R2BYTEMSK(REG_SC_BK2A_1F_L, BIT(8)))   // RF/AV default, eodi weight strong
        MApi_XC_W2BYTEMSK(REG_SC_BK22_29_L, (MS_U16)0xC830, 0xFFFF); // reduce EodiW on MCDi
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK22_29_L, (MS_U16)0xC832, 0xFFFF); // reduce EodiW on MCDi

    // MCDi check Feathering weight
    if((true == bverticalMovingU) || bfilmDisableMCDiDFK)    //new add
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x0000, 0x00F0); // reduce MCDi feathering weight -> for church
    }
    else if(bhorizontalMoving)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x0000, 0x00F0); // reduce MCDi feathering weight
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x0060, 0x00F0); // default MCDi Feathering Weight
    }
    // multi-burst skip
    if((u8SkipCnt > 0x20) || bfilmDisableMCDiDFK)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, (MS_U16)0x0000, 0x0080); // disable mcdi
    }
    else if(u8SkipCnt < 0x10)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, (MS_U16)0x0080, 0x0080); // enable mcdi
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2B_L, (MS_U16)0xc000, 0xF000); //

    /////////////////////////////////////////////////////////////////
    //  De-bouncing
    /////////////////////////////////////////////////////////////////

    MS_U16 u16regdebouncingth, u16regdebouncingcnt;

    u16regdebouncingth = 0x0A;
    u16regdebouncingcnt = 0x03;

    if(u32MotionValue <= u16regdebouncingth)
    {
        u8s8DeBouncingCnt = 0;
    }
    else
    {
        if(u8s8DeBouncingCnt < 0xff)
        	{
            u8s8DeBouncingCnt++;
        	}
    }

    MS_BOOL bfilm;
    bfilm = ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0008) == 0x0008) ||   // film22
           ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0010) == 0x0010) ||   // film32
           ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0040) == 0x0040) ;    // film any

    if((u8s8DeBouncingCnt >= u16regdebouncingcnt) || (true == bfilm))
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, 0x000c, 0x000e);  // history weight = 6
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, 0x0004, 0x000e);  // history weight = 1
    }

}

void MDrv_SC_mcdi_driver_new(MS_U32 u32MotionValue, MS_U8 u8MotLvl)
{
    MS_U32 u32Reg78, u32Reg79, u32Reg7A, u32Reg7B, u32Reg7C, u32Reg7D, u32Reg7E, u32filmFeatherCount;
    MS_U32 u32curCounter3, u32cntDiff;
    MS_U8 u8xxxCtrl;
    MS_BOOL bverticalMovingU, bhorizontalMoving, bslowMotion, bfeatheringScene, bfeatheringScene2, bmovingScene;
    static MS_U8 u8SkipCnt;
    static MS_U8 u8featheringFrameCount;
    static MS_U8 u8s8DeBouncingCnt;
    static MS_U8 u8filmCnt = 0;
    static MS_U32 u32preCounter3 = 0;
    static MS_U8 u8eodiCnt = 0;
    static MS_U8 u8verticalMovingUCnt = 0;
    MS_BOOL bskipCond;
    MS_BOOL bverticalMoving2;
    MS_BOOL bfilmDisableMCDiDFK;

    u8xxxCtrl = 0xFF; //MApi_XC_R2BYTE(REG_SC_BK2A_1F_L) >> 8;
    u32Reg78 = MApi_XC_R2BYTE(REG_SC_BK2A_78_L); // isMV0
    u32Reg79 = MApi_XC_R2BYTE(REG_SC_BK2A_79_L); // Horzontal Moving
    u32Reg7A = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L); // MV not found
    u32Reg7B = MApi_XC_R2BYTE(REG_SC_BK2A_7B_L); // Feathering
    u32Reg7C = MApi_XC_R2BYTE(REG_SC_BK2A_7C_L);
    u32Reg7D = MApi_XC_R2BYTE(REG_SC_BK2A_7D_L);
    u32Reg7E = MApi_XC_R2BYTE(REG_SC_BK2A_7E_L);
    u32filmFeatherCount = MApi_XC_R2BYTE(REG_SC_BK0A_0B_L);

    if(MApi_XC_GetMirrorModeType() == MIRROR_NORMAL)
    {
        //Non_Mirror
        bverticalMovingU = ((u32Reg7E > 0x0100) && (u32Reg7E / 8  > u32Reg7C) && (u32Reg7E / 8  > u32Reg7D) && (u32Reg78 > u32Reg79 / 8)) ||
                          ((u32Reg7E > 0x0040) && (u32Reg7E / 32 > u32Reg7C) && (u32Reg7E / 32 > u32Reg7D) && (u32Reg78 > u32Reg79 / 8));
        bmovingScene = (u32Reg7E > 0x0080) && (u32Reg7E / 4 > u32Reg7C) && (u32Reg7E / 4  > u32Reg7D) && // V-moving-up &&
                      (u32Reg79 > 0x0200) && (u32Reg79 / 4 > u32Reg78);                                                    // H-moving
    }
    else
    {
        //Mirror
        bverticalMovingU = ((u32Reg7D > 0x0100) && (u32Reg7D / 8  > u32Reg7C) && (u32Reg7D / 8  > u32Reg7E) && (u32Reg78 > u32Reg79 / 8)) ||
                          ((u32Reg7D > 0x0040) && (u32Reg7D / 32 > u32Reg7C) && (u32Reg7D / 32 > u32Reg7E) && (u32Reg78 > u32Reg79 / 8));
        bmovingScene = (u32Reg7D > 0x0080) && (u32Reg7D / 4 > u32Reg7C) && (u32Reg7D / 4  > u32Reg7E) && // V-moving-up &&
                      (u32Reg79 > 0x0200) && (u32Reg79 / 4 > u32Reg78);                                                    // H-moving
    }

    bverticalMoving2 = (((u32Reg7E > 0x200) && (u32Reg7E > u32Reg7C)) || ((u32Reg7D > 0x200) && (u32Reg7D > u32Reg7C))) && (u32Reg78 > u32Reg79 / 8);

    bhorizontalMoving = (u32Reg79 > 0x200) && (u32Reg79 / 16 > u32Reg78) && (u32Reg79 > u32Reg7A / 2) &&
                       (u32Reg7C > 0x100) && (u32Reg7C / 2  > u32Reg7D) && (u32Reg7C / 2 > u32Reg7E) ;

    bslowMotion = (u32Reg7A > 0x200) && (u32Reg7B < 0x40) && (!bverticalMoving2);
    bfeatheringScene = (u32Reg7B > 0x100) && (u32Reg7B > u32Reg79 / 4) && (u32Reg7B > u32Reg7A / 4) && (u32MotionValue > 0x10);
    bskipCond = (u32Reg7A > 8 * u32Reg79) && (u32Reg7B > 0x600);
    bfeatheringScene2 = (u32Reg7B > 0x200) && (u32Reg7B > u32Reg79 / 8) && (u32Reg7B > u32Reg7A / 8) && (!bhorizontalMoving) && (u32MotionValue > 0x10);

    if(bverticalMovingU)
    {
        if(u8verticalMovingUCnt != 0xff)
        {
            u8verticalMovingUCnt ++;
        }
    }
    else
    {
        u8verticalMovingUCnt = 0;
    }

    if(false == bskipCond)
    {
        if(u8SkipCnt == 0)
        {
            u8SkipCnt = 0;
        }
        else
        {
            u8SkipCnt--;
        }
    }
    else
    {
        if(u8SkipCnt > 0x40)
        {
            u8SkipCnt = 0x40;
        }
        else
        {
            u8SkipCnt++;
        }
    }

    if(u32filmFeatherCount > 0x100)
    {
        if(u8featheringFrameCount < 0x80)
        {
            u8featheringFrameCount ++;
        }
    }
    else
    {
        u8featheringFrameCount = 0;
    }

    ////////////////////////////////////////////////////////////////
    //  film content disable mcdi/dfk
    ////////////////////////////////////////////////////////////////

    u32curCounter3 = MApi_XC_R2BYTE(REG_SC_BK0A_0B_L);

    u32cntDiff = (u32preCounter3 > u32curCounter3) ? u32preCounter3 - u32curCounter3 : u32curCounter3 - u32preCounter3;

    if(u32cntDiff > 0x1500)
    {
        if(u8filmCnt != 10)
        {
            u8filmCnt++;
        }
    }
    else if(u8filmCnt != 0)
    {
        u8filmCnt--;
    }

    u32preCounter3 = u32curCounter3;
    bfilmDisableMCDiDFK = (u8filmCnt > 5);

    ////////////////////////////////////////////////////////////////
    //  eodi counter
    ////////////////////////////////////////////////////////////////

    if(bfeatheringScene2)
    {
        if(u8eodiCnt < 40)
        {
            u8eodiCnt += 4;
        }
    }
    else
    {
        if(u8eodiCnt > 0)
        {
            u8eodiCnt--;
        }
    }

    /////////////////////////////////////////////////////////////////
    //  SST (De-Feathering)
    /////////////////////////////////////////////////////////////////
    if(u8xxxCtrl & ENABLE_XXX_SST)
    {
        if(bmovingScene || bfilmDisableMCDiDFK)
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_29_L, (MS_U16)0xF100, 0xFF00); // increase SST weighting with checking feathering...
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0000, 0x0F00); // SST motion shift1
        }
        else if((u32MotionValue < 0x10) && (u32Reg7B > 0x1000))    // special patch for Toshiba... -> tend to still
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_29_L, (MS_U16)0x3100, 0xFF00); // increase SST weighting with checking feathering...
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0200, 0x0F00); // SST motion shift1
        }
        else if(bfeatheringScene)        // moving & feather
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_29_L, (MS_U16)0xF100, 0xFF00); // increase SST weighting with checking feathering...
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0000, 0x0F00); // SST motion shift1
        }
        else if((u8MotLvl >= 3) && (u32Reg7B > 0x40) && (u32Reg7B > u32Reg7A / 16))  // for sony champion bubbles
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_29_L, (MS_U16)0xF100, 0xFF00); // default SST setting
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0000, 0x0F00); // SST motion shift1
        }
        else // default
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_29_L, (MS_U16)0x2100, 0xFF00); // default SST setting
            MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0100, 0x0F00); // SST motion shift1
        }
    }

    // disable DFK when verticalMovingU
    if((true == bverticalMovingU) || (u8SkipCnt > 0x20) || bfilmDisableMCDiDFK)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, (MS_U16)0x0000, 0xFFFF); // disable DFK
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0000, 0xF000); // disable DFK
    }
    else if(bverticalMoving2)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, (MS_U16)0xA8FF, 0xFFFF); // default DFK
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0000, 0xF000); // default DFK
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, (MS_U16)0xA8FF, 0xFFFF); // default DFK
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x2000, 0xF000); // default DFK
    }

    if(u8verticalMovingUCnt > 0x20)    // for church
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_34_L, (MS_U16)0x0FF0, 0xFFFF); // favor MCDi Weight
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_36_L, (MS_U16)0x2800, 0x3C0F); // enable MCDi U for blending and history
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_34_L, (MS_U16)0x8888, 0xFFFF); // default MCDi Weight
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_36_L, (MS_U16)0x0000, 0x3C0F); // Use MCDi-H as default
    }

    // Favor MCDi-V when verticalMovingU
    if(1)    //true == verticalMovingU )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_04_L, (MS_U16)0x0800, 0x0800); // Enable MCDi-V
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x4000, 0xF000); // reduce motion history
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_04_L, (MS_U16)0x0800, 0x0800); // Disable MCDi-V
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x4000, 0xF000); // default MCDi motion history
    }

    // DFK EodiW1, 2
    if((u8s8DeBouncingCnt < 0x3) || bfilmDisableMCDiDFK)      //new add
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0080, 0x00F0); // reduce DFK EodiWeight
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x4c30, 0xFF30); // disable EodiW for DFK
    }
    else if((true == bverticalMovingU) || bverticalMoving2)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0010, 0x00F0); // increase EodiW ->  tower
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x4c10, 0xFF30); // default
    }
    else if((false == bverticalMovingU) && bslowMotion)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0080, 0x00F0); // reduce DFK EodiWeight
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x0c30, 0xFF30); // disable EodiW for DFK
    }
    else if(MApi_XC_R2BYTEMSK(REG_SC_BK2A_1F_L, BIT(8)))  // RF/AV default, eodi weight strong
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0010, 0x00F0); // increase EodiW
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x18F1, 0xFF30); // default
    }
    else // default
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0040, 0x00F0); // default DFK EodiWeight
        MApi_XC_W2BYTEMSK(REG_SC_BK22_28_L, (MS_U16)0x0c10, 0xFF30); // default
    }

    if(MApi_XC_R2BYTEMSK(REG_SC_BK2A_1F_L, BIT(8)))   // RF/AV default, eodi weight strong
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4488, 0x00F0);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x0020, 0x00F0);

    // DFK check feathering gain
    if(bfilmDisableMCDiDFK)     //new add
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0f00, 0x0F00);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2B_L, (MS_U16)0xf000, 0xF000); //
    }
    else if(u32MotionValue == 0)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0800, 0x0F00); // reduce DFK feathering weight
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2B_L, (MS_U16)0x1000, 0xF000); //
    }
    else if((false == bverticalMovingU) && bslowMotion)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0800, 0x0F00); // reduce DFK feathering weight
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2B_L, (MS_U16)0x1000, 0xF000); //
    }
    else if(u32Reg7B > 0x100)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0f00, 0x0F00); // feather -> increase
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2B_L, (MS_U16)0xc000, 0xF000); //
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2A_L, (MS_U16)0x0f00, 0x0F00); // default
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2B_L, (MS_U16)0x4000, 0xF000); //
    }

    // EodiWeight for MCDi
    if(true == bverticalMovingU)
    {
        if((u32Reg7A > 0x100) && (u32Reg7A / 2 > u32Reg79))  // not-found >> horizontal : Church
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0004, 0x000F); // reduce EodiWeight for MCDi
            MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4800, 0xFF0F); // church
        }
        else //  Tower
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0004, 0x000F); // increase EodiWeight for MCDi
            MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4200, 0xFF0F); //  Tower
        }
    }
    else if((false == bverticalMovingU) && bhorizontalMoving)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0002, 0x000F); // reduce EodiWeight for MCDi
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x1800, 0xFF0F); // reduce EodiW for MCDi
    }
    else if(MApi_XC_R2BYTEMSK(REG_SC_BK2A_1F_L, BIT(8)))  // RF/AV default, eodi weight strong
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0002, 0x000F); // increase EodiWeight for MCDi
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4408, 0xFF0F);
    }
    else if(u8eodiCnt > 25)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0001, 0x000F); // default EodiWeight for MCDi
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4400, 0xFF0F);
    }
    else if(u8eodiCnt < 10)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2C_L, (MS_U16)0x0002, 0x000F); // default EodiWeight for MCDi
        MApi_XC_W2BYTEMSK(REG_SC_BK22_2A_L, (MS_U16)0x4800, 0xFF0F);
    }

    if(MApi_XC_R2BYTEMSK(REG_SC_BK2A_1F_L, BIT(8)) && (!bhorizontalMoving)) // RF/AV default, eodi weight strong
        MApi_XC_W2BYTEMSK(REG_SC_BK22_29_L, (MS_U16)0xC830, 0xFFFF); // reduce EodiW on MCDi
    else if(!bhorizontalMoving)
        MApi_XC_W2BYTEMSK(REG_SC_BK22_29_L, (MS_U16)0xC832, 0xFFFF); // reduce EodiW on MCDi
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK22_29_L, (MS_U16)0xC836, 0xFFFF);

    // MCDi check Feathering weight
    if(bfilmDisableMCDiDFK)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x0060, 0x00F0); // reduce MCDi feathering weight -> for church
    }
    else if(true == bverticalMovingU)     //new add
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x0000, 0x00F0); // reduce MCDi feathering weight -> for church
    }
    else if(bhorizontalMoving)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x0000, 0x00F0); // reduce MCDi feathering weight
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)0x0060, 0x00F0); // default MCDi Feathering Weight
    }
    // multi-burst skip
    if((u8SkipCnt > 0x20) || bfilmDisableMCDiDFK)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, (MS_U16)0x0000, 0x0080); // disable mcdi
    }
    else if(u8SkipCnt < 0x10)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, (MS_U16)0x0080, 0x0080); // enable mcdi
    }

    if(u32MotionValue == 0)    // still picture -> tend to still
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2B_L, (MS_U16)0x0800, 0x0FFF); //
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0000, 0x00FF); //
    }
    else // default
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2B_L, (MS_U16)0x0888, 0x0FFF); //
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_2C_L, (MS_U16)0x0088, 0x00FF); //
    }

    /////////////////////////////////////////////////////////////////
    //  De-bouncing
    /////////////////////////////////////////////////////////////////

    MS_BOOL bfilm;
    bfilm = ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0008) == 0x0008) ||   // film22
           ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0010) == 0x0010) ||   // film32
           ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0040) == 0x0040) ;    // film any

    if((u8MotLvl >= 1) || (true == bfilm))
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, 0x000c, 0x000e);  // history weight = 6
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, 0x0004, 0x000e);  // history weight = 2
    }

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

void MDrv_SC_T12_DIPF_TemporalGainControl(MS_U32 u32OOSRMC, MS_U32 u32OOSRF, MS_U32 u32ISR_NONMV0)
{
    static MS_U16 u16TemporalGainControl = 0x0F;

    UNUSED(u32OOSRMC);
    UNUSED(u32OOSRF);

    if(u32ISR_NONMV0 > 1000)  //&& OOSRF > 50)
    {
        if(u16TemporalGainControl > 0x00)
       {
            u16TemporalGainControl--;
        }
        else
        {
            u16TemporalGainControl = 0;
        }
    }
    else
    {
        if(u16TemporalGainControl < 0x0F)
        {
            u16TemporalGainControl++;
        }
        else
        {
            u16TemporalGainControl = 0x0F;
        }
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK22_14_L, (MS_U16)u16TemporalGainControl, 0x000F);

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
void MDrv_SC_T12_UCDi_OP1_HisWeight(MS_U8 u8MotLvl)
{
    MS_BOOL bfilm;

    bfilm = ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0008) == 0x0008) ||   // film22
           ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0010) == 0x0010) ||   // film32
           ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, 0x0040) == 0x0040) ;    // film any

    if((u8MotLvl >= 1) || (true == bfilm))
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, OP1_HisWeight_MaxValue, 0x000e);  // history weight = 6
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_02_L, OP1_HisWeight_MinValue, 0x000e);  // history weight = 2
    }
}

#define A5_HIS_MOTION_TH 0x0A
void MDrv_SC_A5_UCDi_OP1_HisWeight(const MS_U32 u32MotionValue,const MS_U32 u32FeatherSum)
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

    if(u32FeatherSum > 0x3500)
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

MS_U32 MDrv_SC_A5_KFC_IsVerticalMoving(void)
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

MS_U8 MDrv_SC_A5_UC_PanScan(void)
{
    MS_U32 u32nonMV0Found, u32MVNotFound;
    static MS_U32 u32PrevnonMV0Found = 0;
    static MS_U32 u32PrevMVNotFound = 0;
    static MS_U8  u8panCnt = 0;

    u32nonMV0Found    = MApi_XC_R2BYTE(REG_SC_BK2A_79_L);
    u32MVNotFound     = MApi_XC_R2BYTE(REG_SC_BK2A_7A_L);

    u32nonMV0Found = (u32PrevnonMV0Found*3 + u32nonMV0Found ) >> 2;
    u32PrevnonMV0Found = u32nonMV0Found;

    u32MVNotFound = (u32PrevMVNotFound*3 + u32MVNotFound ) >> 2;
    u32PrevMVNotFound = u32MVNotFound;

    if( u32nonMV0Found > u32MVNotFound*30 )
    {
        if(u8panCnt != 10)
       {
            u8panCnt++;
        }
    }
    else if(u8panCnt != 0)
    {
        u8panCnt--;
    }

    return u8panCnt;
}

#define LG107_FEATHER_GAIN_MAX 2
#define LG107_FEATHER_GAIN_MIN 0
#define LG107_CPLX_OFFSET_MAX 6
#define LG107_CPLX_OFFSET_MIN 0
#define LG107_CPLX_GAIN_MAX 15
#define LG107_CPLX_GAIN_MIN 4
void MDrv_SC_A5_UC_PanScanSetting( const MS_U8 PanScan )
{
    static MS_U16 u16regmcdifeathergain = LG107_FEATHER_GAIN_MAX ;
    static MS_U16 u16regmcdicplxoffset = LG107_CPLX_OFFSET_MAX ;

    if( PanScan > 8 )
    {
        u16regmcdifeathergain = LG107_FEATHER_GAIN_MIN;
        u16regmcdicplxoffset = LG107_FEATHER_GAIN_MIN;
    }
    else
    {
        u16regmcdifeathergain = LG107_FEATHER_GAIN_MAX;
        u16regmcdicplxoffset = LG107_FEATHER_GAIN_MAX;
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2D_L, (MS_U16)u16regmcdifeathergain<<12, 0xF000); // 2 to 0
    MApi_XC_W2BYTEMSK(REG_SC_BK2A_2E_L, (MS_U16)u16regmcdicplxoffset<<4, 0x00F0);// 6 to 0
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
void Hal_PQ_LoadMCNRLutQmapSetting()
{

     m_stMCNRLutQmapSetting.mcnrLut[0] = MApi_XC_R2BYTE(REG_SC_BK2A_08_L);
     m_stMCNRLutQmapSetting.mcnrLut[1] = MApi_XC_R2BYTE(REG_SC_BK2A_09_L);
     m_stMCNRLutQmapSetting.mcnrLut[2] = MApi_XC_R2BYTE(REG_SC_BK2A_0A_L);
     m_stMCNRLutQmapSetting.mcnrLut[3] = MApi_XC_R2BYTE(REG_SC_BK2A_0B_L);
     m_stMCNRLutQmapSetting.mcnrLut[4] = MApi_XC_R2BYTE(REG_SC_BK2A_0C_L);
     m_stMCNRLutQmapSetting.mcnrLut[5] = MApi_XC_R2BYTE(REG_SC_BK2A_0D_L);
     m_stMCNRLutQmapSetting.mcnrLut[6] = MApi_XC_R2BYTE(REG_SC_BK2A_0E_L);
     m_stMCNRLutQmapSetting.mcnrLut[7] = MApi_XC_R2BYTE(REG_SC_BK2A_0F_L);

}


void MDrv_SC_mcnr_driver( MS_U32 nonHistoryMotionPixel )
{
    MS_U32 u32_is_mv0, u32_non_mv0, u32_mvNotFound, u32_mvFeathering, u32_mvc, u32_mvu, u32_mvd, u32_cplxPixel, u32temp1, u32temp2;
    MS_BOOL bmenotconfirm , bmevertical, bisHDSource, bis24to60Hz/*, scene_change*/;
     MS_U8 u8MCNR_Gain=16;    // UCNR LUT use PQ Excel
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
    bisHDSource = ( MApi_XC_R2BYTEMSK(REG_SC_BK12_0F_L, 0xFFFF) > 0x700 );

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



    //Read PQ Excel UCNR LUT
    MS_BOOL bMCNR_LUT_ReloadStart = (MApi_XC_R2BYTEMSK(REG_SC_BK22_7D_L, 0x0100)>>8);    // When Use PQ LUT = 1
    MS_BOOL bMCNR_LUT_ReloadEnd = (MApi_XC_R2BYTEMSK(REG_SC_BK22_7D_L, 0x0200)>>8);     //  When Use PQ LUT and Load OK  1 --> 0

    if(bMCNR_LUT_ReloadStart && bMCNR_LUT_ReloadEnd) {              //Only Frist Time Load
       Hal_PQ_LoadMCNRLutQmapSetting();
       MApi_XC_W2BYTEMSK(REG_SC_BK22_7D_L, 0x0000, 0x0200);   //Clean End Flige
       bMCNR_LUT_ReloadStart = (MApi_XC_R2BYTEMSK(REG_SC_BK22_7D_L, 0x0100)>>8);    // When Use PQ LUT = 1
       bMCNR_LUT_ReloadEnd = (MApi_XC_R2BYTEMSK(REG_SC_BK22_7D_L, 0x0200)>>8);     //  When Use PQ LUT and Load OK  1 --> 0
       //printf("=====AAAAAA=====\n");
    }

    if(bMCNR_LUT_ReloadStart && !bMCNR_LUT_ReloadEnd) {

	//printf("=====BBBBBB=====\n");


        MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[0],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[1],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[2],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[3],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[4],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[5],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[6],u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, MDrv_SC_NR_LUT_Aux(m_stMCNRLutQmapSetting.mcnrLut[7],u8MCNR_Gain), 0xFFFF);

            }
    else {

        //printf("=====CCCCCC=====\n");


        MApi_XC_W2BYTEMSK(REG_SC_BK2A_08_L, MDrv_SC_NR_LUT_Aux(0xAAAA,u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_09_L, MDrv_SC_NR_LUT_Aux(0xAAAA,u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0A_L, MDrv_SC_NR_LUT_Aux(0xAAAA,u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0B_L, MDrv_SC_NR_LUT_Aux(0xAAAA,u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0C_L, MDrv_SC_NR_LUT_Aux(0xAAAA,u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0D_L, MDrv_SC_NR_LUT_Aux(0xAA98,u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0E_L, MDrv_SC_NR_LUT_Aux(0x7654,u8MCNR_Gain), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_0F_L, MDrv_SC_NR_LUT_Aux(0x3210,u8MCNR_Gain), 0xFFFF);


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
        else // default
        {
            if ( !bisHDSource )
            {
                MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x0064, 0x00FF); // default random motion
            }
            else
            {
                if ( stXCStatus.bInterlace )
                {
                    MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x00C2, 0x00FF); // Default 64 -> C2, moving picture, increase random motion
                }
                else
                {
                    MApi_XC_W2BYTEMSK(REG_SC_BK2A_1B_L, (MS_U16)0x00C2, 0x00FF); // Default 64 -> C2, moving picture, increase random motion
                }
            }
        }
    }
    //u32lastmvNotFound = u32_mvNotFound;
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


int MDrv_SC_motion_level(MS_U32 u32MotionValue)
{
    static MS_U32 u32DeFeatherCntLv1 = 0;
    static MS_U32 u32DeFeatherCntLv2 = 0;
    static MS_U32 u32DeFeatherCntLv3 = 0;
    MS_U8 u8MotLvl;
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

    //level begin
    if(u32DeFeatherCntLv1 >= u32regdefetheringlv1cnt)
    {
        u8MotLvl    = 3;
    }
    else if(u32DeFeatherCntLv2 >= u32regdefetheringlv2cnt)
    {
        u8MotLvl    = 2;
    }
    else if(u32DeFeatherCntLv3 >= DEFETHERING_LV3_CNT)
    {
        u8MotLvl    = 1;
    }
    else
    {
        u8MotLvl    = 0;
    }

    return u8MotLvl;
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

/******************************************************************************/
///DePreSNR
///@param u32MotionValue \     IN: Motion value
/******************************************************************************/
void MDrv_SC_de_pre_snr(MS_U32 u32MotionValue)
{
    static MS_S32 s32DePreSNRCnt = 0;
    MS_U8  u8regpreSnren = 0;
    MS_U32 u32regpreSnrth;
    MS_U32 u32regpreSnrcnt;

    u32regpreSnrth = 0x06;
    u32regpreSnrcnt = 0x01;

    if(u32MotionValue <= u32regpreSnrth * DEBOUNCING_GAIN)
    {
        s32DePreSNRCnt = 0;
    }
    else
    {
        if(s32DePreSNRCnt < 65535)
        {
            s32DePreSNRCnt++;
        }
    }

    if(s32DePreSNRCnt >= (MS_S32)u32regpreSnrcnt)
    {
        u8regpreSnren = 0x01; // enable pre-snr
    }
    else
    {
        u8regpreSnren = 0x00; // disable pre-snr
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK06_22_L, (MS_U16)u8regpreSnren, BIT(0));
}

/******************************************************************************/
///Dynamic SNR
///@param u32MotionValue \     IN: Motion value
/******************************************************************************/
void MDrv_SC_dynamic_snr(MS_U32 u32MotionValue)
{
    static MS_S32 s32DynamicSnrCnt = 0;
#if (DBG_DYNAMIC_SNR)
    static MS_S32 s32CurrentLevel = -1;
    static MS_S32 s32LastLevel = -1;
#endif
    MS_U8  u8SNR_Bypass;
    MS_U32 u32regsnrcnt;

    u32regsnrcnt = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK0B_77_L, 0xFF);

    if(u32MotionValue <= DYNAMIC_SNR_TH)
    {
        s32DynamicSnrCnt = 0;
    }
    else
    {
        if(s32DynamicSnrCnt < 65535)
        {
            s32DynamicSnrCnt++;
        }
    }

    if(s32DynamicSnrCnt >= (MS_S32)u32regsnrcnt)
    {
        u8SNR_Bypass = 0; // SNR enable

#if (DBG_DYNAMIC_SNR)
        s32CurrentLevel = 1;
#endif
    }
    else
    {
        u8SNR_Bypass = 1; // SNR disable

#if (DBG_DYNAMIC_SNR)
        s32CurrentLevel = 2;
#endif
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK0C_70_L, (MS_U16)u8SNR_Bypass, 0xFF);

#if (DBG_DYNAMIC_SNR)
    if(s32CurrentLevel != s32LastLevel)
    {
        if(s32CurrentLevel == 1)
        {
            printf("SNR = Enable[%x]\n", s32CurrentLevel);
        }
        else
        {
            printf("SNR = Disable[%x]\n", s32CurrentLevel);
        }

        s32LastLevel = s32CurrentLevel;
    }
#endif
}

/******************************************************************************/
///FantasticDNR
///@param u32MotionValue \     IN: Motion value
/******************************************************************************/
void MDrv_SC_fantastic_dnr(void)
{
    static MS_S32 s32Cnt  = 0;
    MS_U8 u8DNR_TblY_0L, u8DNR_TblY_0H, u8DNR_TblY_1L, u8DNR_TblY_1H;
    MS_U8 u8DNR_TblY_2L, u8DNR_TblY_2H, u8DNR_TblY_3L, u8DNR_TblY_3H;

    s32Cnt++;

    if(s32Cnt % 2 == 0)
    {
        u8DNR_TblY_0L = 0xDE;
        u8DNR_TblY_0H = 0xDD;
        u8DNR_TblY_1L = 0x79;
        u8DNR_TblY_1H = 0x67;
        u8DNR_TblY_2L = 0x56;
        u8DNR_TblY_2H = 0x45;
        u8DNR_TblY_3L = 0x11;
        u8DNR_TblY_3H = 0x00;
    }
    else
    {
        u8DNR_TblY_0L = 0xCD;
        u8DNR_TblY_0H = 0x39;
        u8DNR_TblY_1L = 0x34;
        u8DNR_TblY_1H = 0x11;
        u8DNR_TblY_2L = 0x00;
        u8DNR_TblY_2H = 0x00;
        u8DNR_TblY_3L = 0x00;
        u8DNR_TblY_3H = 0x00;
    }
    MApi_XC_W2BYTE(REG_SC_BK06_40_L, ((MS_U16)u8DNR_TblY_0L | (((MS_U16) u8DNR_TblY_0H) << 8)));
    MApi_XC_W2BYTE(REG_SC_BK06_41_L, ((MS_U16)u8DNR_TblY_1L | (((MS_U16) u8DNR_TblY_1H) << 8)));
    MApi_XC_W2BYTE(REG_SC_BK06_42_L, ((MS_U16)u8DNR_TblY_2L | (((MS_U16) u8DNR_TblY_2H) << 8)));
    MApi_XC_W2BYTE(REG_SC_BK06_43_L, ((MS_U16)u8DNR_TblY_3L | (((MS_U16) u8DNR_TblY_3H) << 8)));
}

/******************************************************************************/
///Dynamic DNR
///@param u32MotionValue \     IN: Motion value
/******************************************************************************/
#define DYNAMIC_DNR_TH                  1000
void MDrv_SC_dynamic_dnr(MS_U32 u32MotionValue)
{
    static MS_S32 s32ZeroCnt  = 0;
    static MS_S32 s32StillCnt = 0;
    MS_U8 u8DNR_TblY_0L, u8DNR_TblY_0H, u8DNR_TblY_1L, u8DNR_TblY_1H;
    MS_U8 u8DNR_TblY_2L, u8DNR_TblY_2H, u8DNR_TblY_3L, u8DNR_TblY_3H;

    if(u32MotionValue <= DYNAMIC_DNR_TH)
    {
        if(s32StillCnt < 65535)
       {
            s32StillCnt++;
       }
    }
    else
    {
        s32StillCnt = 0;
    }

    if(u32MotionValue == 0)
    {
        if(s32ZeroCnt < 65535)
        {
            s32ZeroCnt++;
        }
    }
    else
    {
        s32ZeroCnt = 0;
    }

    if(s32ZeroCnt >= 18)
    {
        u8DNR_TblY_0L = 0xDE;
        u8DNR_TblY_0H = 0xDD;
        u8DNR_TblY_1L = 0x79;
        u8DNR_TblY_1H = 0x67;
        u8DNR_TblY_2L = 0x56;
        u8DNR_TblY_2H = 0x45;
        u8DNR_TblY_3L = 0x11;
        u8DNR_TblY_3H = 0x00;
    }
    else if(s32StillCnt >= 8)  //still
    {
        u8DNR_TblY_0L = 0xCE;
        u8DNR_TblY_0H = 0xAC;
        u8DNR_TblY_1L = 0x78;
        u8DNR_TblY_1H = 0x34;
        u8DNR_TblY_2L = 0x12;
        u8DNR_TblY_2H = 0x00;
        u8DNR_TblY_3L = 0x00;
        u8DNR_TblY_3H = 0x00;
    }
    else //moving
    {
        u8DNR_TblY_0L = 0xCD;
        u8DNR_TblY_0H = 0x39;
        u8DNR_TblY_1L = 0x34;
        u8DNR_TblY_1H = 0x11;
        u8DNR_TblY_2L = 0x00;
        u8DNR_TblY_2H = 0x00;
        u8DNR_TblY_3L = 0x00;
        u8DNR_TblY_3H = 0x00;
    }
    MApi_XC_W2BYTE(REG_SC_BK06_40_L, ((MS_U16)u8DNR_TblY_0L | (((MS_U16) u8DNR_TblY_0H) << 8)));
    MApi_XC_W2BYTE(REG_SC_BK06_41_L, ((MS_U16)u8DNR_TblY_1L | (((MS_U16) u8DNR_TblY_1H) << 8)));
    MApi_XC_W2BYTE(REG_SC_BK06_42_L, ((MS_U16)u8DNR_TblY_2L | (((MS_U16) u8DNR_TblY_2H) << 8)));
    MApi_XC_W2BYTE(REG_SC_BK06_43_L, ((MS_U16)u8DNR_TblY_3L | (((MS_U16) u8DNR_TblY_3H) << 8)));
}

/******************************************************************************/
///DHD Driver
/******************************************************************************/

void MDrv_SC_Janus_DHD_driver(void)
{
    // dhd shining line patch
    static MS_U32 u32videoCnt = 0;

    if(MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, BIT(3)))  // film22
    {
        u32videoCnt = 0;
    }
    else if(MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, BIT(4))) // film32
    {
        u32videoCnt = 0;
    }
    else if(MApi_XC_R2BYTEMSK(REG_SC_BK0A_21_L, BIT(6)))
    {
        u32videoCnt = 0;
    }
    else if(u32videoCnt >= 10000)
    {
        u32videoCnt = 10000;
    }
    else
    {
        u32videoCnt++;
    }

    if(u32videoCnt >= 60)   // 2 sec
    {
        // turn on dhd, 6R
        MApi_XC_W2BYTEMSK(REG_SC_BK12_05_L, 0x8000, 0x8000);    // 6R
        MApi_XC_W2BYTEMSK(REG_SC_BK05_20_L, 0x0001, 0x0001);    // dhd on
    }
    else
    {
        // turn off dhd, 4R
        MApi_XC_W2BYTEMSK(REG_SC_BK12_05_L, 0x0000, 0x8000);    // 4R
        MApi_XC_W2BYTEMSK(REG_SC_BK05_20_L, 0x0000, 0x0001);    // dhd off
    }
}

#define HD_ACT_TH 10
#define HDSDD_SPEED 1
#define HDSDD_DIV 0
#define HD_SPEED 2
#define SD_SPEED 8

void MDrv_SC_SDHD_DETECT_driver(void)
{
    MS_U8 u8Value;
    MS_U16 u16MinPixel, u16MaxPixel, u16MaxMinPixel;
    MS_U32 u32HDcntAct;
    MS_U32 u32SDcntAct;
    static MS_U16 u16HDConfirmCnt = 0xFF; // 0x7FFF == 0
    static MS_U8 u8PrevLuma = 0;
    static MS_U16 u16PrevMinPixel = 0;
    static MS_U16 u16PrevMaxPixel = 0;
    MS_U32 u32HDConfirmCntReg;
    MS_U16 u16HDSDDthreshold, u16HDSDDoffset;

    u16HDSDDoffset = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK22_7F_L, 0xFFFF);

    u8Value = (MS_U32)((MS_U32)u8PrevLuma * 3 + MApi_XC_DLC_GetAverageValue()) >> 2;
    u8PrevLuma = u8Value;

    u16MaxPixel = MApi_XC_R2BYTEMSK(REG_SC_BK1A_0B_L, 0x00FF);
    u16MaxPixel = (u16PrevMaxPixel * 3 + u16MaxPixel) >> 2;
    u16PrevMaxPixel = u16MaxPixel;

    u16MinPixel = MApi_XC_R2BYTEMSK(REG_SC_BK1A_0B_L, 0xFF00) >> 8;
    u16MinPixel = (u16PrevMinPixel * 3 + u16MinPixel) >> 2;
    u16PrevMinPixel = u16MinPixel;

    u16MaxMinPixel = u16MaxPixel - u16MinPixel;

    if(u8Value >= 0xFF)
    {
        u8Value = 0xFF;
    }

    u16HDSDDthreshold = u16HDSDDoffset + ((u16MaxMinPixel * 6) >> 2) + ((u8Value * 5) >> 2);

    if(u16HDSDDthreshold >= 0xFFFF)
    {
        u16HDSDDthreshold = 0xFFFF;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK02_71_L, (MS_U16)u16HDSDDthreshold, 0xFFFF);
    MApi_XC_W2BYTEMSK(REG_SC_BK02_72_L, (MS_U16)(u16HDSDDthreshold >> 1), 0xFFFF);

    u32HDcntAct = (MApi_XC_R2BYTE(REG_SC_BK02_75_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_74_L);
    u32SDcntAct = (MApi_XC_R2BYTE(REG_SC_BK02_77_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_76_L);

    if((u32HDcntAct > HD_ACT_TH) && (u32SDcntAct != 0))
    {
        if(u16HDConfirmCnt < HD_SPEED)
        {
            u16HDConfirmCnt = 0;
        }
        else
        {
            u16HDConfirmCnt = u16HDConfirmCnt - HD_SPEED;
        }
    }
    else if(u32SDcntAct != 0)  //&& HDcnt_NonAct !=0) // && (HDcnt_NonAct < 0x90000))
    {
        if(u16HDConfirmCnt > (0xFF - SD_SPEED))
        {
            u16HDConfirmCnt = 0xFF;
        }
        else
        {
            u16HDConfirmCnt = u16HDConfirmCnt + SD_SPEED;
        }
    }
    else
    {
        if(u16HDConfirmCnt < 1)
        {
            u16HDConfirmCnt = 0;
        }
        else
        {
            u16HDConfirmCnt = u16HDConfirmCnt - 1;
        }
    }

    if(u16HDConfirmCnt > 0x80)
    {
        u32HDConfirmCntReg = u16HDConfirmCnt - 0x80;
    }
    else
    {
        u32HDConfirmCntReg = 0;
    }

    u32HDConfirmCntReg = (u32HDConfirmCntReg * HDSDD_SPEED) >> HDSDD_DIV;

    if(u32HDConfirmCntReg > 0x3F)
    {
        u32HDConfirmCntReg = 0x3F;
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK23_54_L, (MS_U16)u32HDConfirmCntReg, 0x003F);
}

void MDrv_SC_NEW_SDHD_DETECT_driver(void)
{
    MS_U8 u8Value,u8FEATHERCNTTH;
    MS_U16 u16MinPixel,u16MaxPixel, u16MaxMinPixel;
    MS_U32 u32HDcntAct;
    //MS_U32 HDcnt_NonAct;
    MS_U32 u32FeatherCnt;
    MS_U32 u32SDcntAct;
    //MS_U32 SDcnt_NonAct;
    static MS_U32 u32PreFeatherCnt = 0;
    static MS_U16 u16HDConfirmCnt = 0xFF; // 0x7FFF == 0
    static MS_U8 u8PrevLuma = 0;
    static MS_U16 u16PrevMinPixel = 0;
    static MS_U16 u16PrevMaxPixel = 0;
    MS_U32 u32HDConfirmCntReg;
    MS_U16 u16HDSDDthreshold,u16HDSDDoffset;

    u16HDSDDoffset = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK22_7F_L, 0xFFFF);

    u32FeatherCnt = MApi_XC_R2BYTE(REG_SC_BK23_56_L);       //New add for A1 chip
    u8FEATHERCNTTH = MApi_XC_R2BYTEMSK(REG_SC_BK22_7D_L, 0xFF00)>>8;

    u32FeatherCnt = ( u32PreFeatherCnt*3 + u32FeatherCnt ) >> 2;
    u32PreFeatherCnt = u32FeatherCnt;

    u8Value=(MS_U32)((MS_U32)u8PrevLuma*3 + MApi_XC_DLC_GetAverageValue())>>2;
    u8PrevLuma = u8Value;

    u16MaxPixel = MApi_XC_R2BYTEMSK(REG_SC_BK1A_0B_L, 0x00FF);
    u16MaxPixel = (u16PrevMaxPixel*3 + u16MaxPixel ) >> 2;
    u16PrevMaxPixel = u16MaxPixel;

    u16MinPixel = MApi_XC_R2BYTEMSK(REG_SC_BK1A_0B_L, 0xFF00)>>8;
    u16MinPixel = (u16PrevMinPixel*3 + u16MinPixel ) >> 2;
    u16PrevMinPixel = u16MinPixel;

    u16MaxMinPixel = u16MaxPixel - u16MinPixel;

    if(u8Value>=0xFF)
    {
        u8Value = 0xFF;
    }

    u16HDSDDthreshold = u16HDSDDoffset +((u16MaxMinPixel*6)>>2) + ((u8Value*5)>>2);

    if(u16HDSDDthreshold >=0xFFFF)
    {
        u16HDSDDthreshold=0xFFFF;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK02_71_L, (MS_U16)u16HDSDDthreshold, 0xFFFF);
    MApi_XC_W2BYTEMSK(REG_SC_BK02_72_L, (MS_U16)(u16HDSDDthreshold>>1), 0xFFFF);

    u32HDcntAct = (MApi_XC_R2BYTE(REG_SC_BK02_75_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_74_L);
    u32SDcntAct = (MApi_XC_R2BYTE(REG_SC_BK02_77_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_76_L);

    if( (u32HDcntAct > HD_ACT_TH) && (u32SDcntAct != 0) )
    {
        if(u16HDConfirmCnt < HD_SPEED)
        {
            u16HDConfirmCnt = 0;
        }
        else
        {
            u16HDConfirmCnt = u16HDConfirmCnt - HD_SPEED;
        }
    }
    else if( (u32SDcntAct != 0) && (u32FeatherCnt > u8FEATHERCNTTH) )//&& HDcnt_NonAct !=0) // && (HDcnt_NonAct < 0x90000))
    {
        if(u16HDConfirmCnt > (0xFF - SD_SPEED))
        {
            u16HDConfirmCnt = 0xFF;
        }
        else
        {
            u16HDConfirmCnt = u16HDConfirmCnt + SD_SPEED;
        }
    }
    else
    {
        if(u16HDConfirmCnt < 1)
        {
            u16HDConfirmCnt = 0;
        }
        else
        {
            u16HDConfirmCnt = u16HDConfirmCnt - 1;
        }
    }

    if( u16HDConfirmCnt > 0x80 )
    {
        u32HDConfirmCntReg = u16HDConfirmCnt - 0x80;
    }
    else
    {
        u32HDConfirmCntReg = 0;
    }

    u32HDConfirmCntReg = (u32HDConfirmCntReg*HDSDD_SPEED) >> HDSDD_DIV;

    if( u32HDConfirmCntReg > 0x3F )
    {
        u32HDConfirmCntReg = 0x3F;
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK23_54_L, (MS_U16)u32HDConfirmCntReg, 0x003F);
}

void MDrv_SC_A5_verticalMovingReduceKFC( MS_BOOL VerticalMovingForDHD )
{
    // reduce KFC reduce history motion when vertical moving
    if ( VerticalMovingForDHD || ((MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK22_7C_L, 0x2000) == 0x2000) )
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, 0x0000, 0x0800);
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK2A_28_L, 0x0800, 0x0800);
    }
}

void MDrv_SC_Amber5_DHD_driver1( MS_U8 u8SD2HDValue )
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

MS_U8 MDrv_SC_NEW_SDHD_DETECT_report2( void )
{
    MS_U32 u32HDcntAct,u32SDcntAct;
    static MS_U32 u32prvHDcntAct = 0;
    static MS_U32 u32prvSDcntAct = 0;
    static MS_U16 u16regHDth = 0;
    static MS_U16 u16regSDth = 0;
    static MS_U8  u8SDcnt = 0;

    u16regHDth = MApi_XC_R2BYTE(REG_SC_BK02_71_L );
    u16regSDth = MApi_XC_R2BYTE(REG_SC_BK02_72_L );

    MApi_XC_W2BYTEMSK(REG_SC_BK02_71_L, 0x100, 0xFFFF);
    MApi_XC_W2BYTEMSK(REG_SC_BK02_72_L, 0x100, 0xFFFF);

    u32HDcntAct =  (MApi_XC_R2BYTE(REG_SC_BK02_75_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_74_L);
    u32SDcntAct =  (MApi_XC_R2BYTE(REG_SC_BK02_77_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_76_L);

    u32HDcntAct = ( u32prvSDcntAct*3 + u32HDcntAct ) >> 2;
    u32prvHDcntAct = u32HDcntAct;

    u32SDcntAct = ( u32prvSDcntAct*3 + u32SDcntAct ) >> 2;
    u32prvSDcntAct = u32SDcntAct;

    if( (u32HDcntAct < 1) && (u32SDcntAct!= 0) )
    {
        u8SDcnt += 1;
    }
    else
    {
        u8SDcnt = 0;
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK02_71_L, u16regHDth, 0xFFFF);
    MApi_XC_W2BYTEMSK(REG_SC_BK02_72_L, u16regSDth, 0xFFFF);

    return u8SDcnt;
}


MS_U8 MDrv_SC_NEW_SDHD_DETECT_report(void)
{
    MS_U8 u8Value,u8FEATHERCNTTH;
    MS_U16 u16MinPixel,u16MaxPixel, u16MaxMinPixel;
    MS_U32 u32HDcntAct, u32HDcntNonAct,u32FeatherCnt;
    MS_U32 u32SDcntAct, u32SDcntNonAct;
    static MS_U32 u32PreFeatherCnt = 0;
    static MS_U16 u16HDConfirmCnt = 0xFF; // 0x7FFF == 0
    static MS_U8 u8PrevLuma = 0;
    static MS_U16 u16PrevMinPixel = 0;
    static MS_U16 u16PrevMaxPixel = 0;
    MS_U32 u32HDConfirmCntReg;
    MS_U16 u16HDSDD_Det_threshold,u16HDSDDDetoffset;

    u32HDcntAct =  (MApi_XC_R2BYTE(REG_SC_BK02_75_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_74_L);
    u32SDcntAct =  (MApi_XC_R2BYTE(REG_SC_BK02_77_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_76_L);
    u32HDcntNonAct =  (MApi_XC_R2BYTE(REG_SC_BK02_79_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_78_L);
    u32SDcntNonAct =  (MApi_XC_R2BYTE(REG_SC_BK02_7B_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_7A_L);
    u16HDSDDDetoffset = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK22_7F_L, 0xFFFF);

    u32FeatherCnt = MApi_XC_R2BYTE(REG_SC_BK23_56_L);       //New add for A1 chip
    u8FEATHERCNTTH = MApi_XC_R2BYTEMSK(REG_SC_BK22_7D_L, 0xFF00)>>8;

    u32FeatherCnt = ( u32PreFeatherCnt*3 + u32FeatherCnt ) >> 2;
    u32PreFeatherCnt = u32FeatherCnt;

    u8Value=(MS_U32)((MS_U32)u8PrevLuma*3 + MApi_XC_DLC_GetAverageValue())>>2;
    u8PrevLuma = u8Value;

    u16MaxPixel = MApi_XC_R2BYTEMSK(REG_SC_BK1A_0B_L, 0x00FF);
    u16MaxPixel = (u16PrevMaxPixel*3 + u16MaxPixel ) >> 2;
    u16PrevMaxPixel = u16MaxPixel;

    u16MinPixel = MApi_XC_R2BYTEMSK(REG_SC_BK1A_0B_L, 0xFF00)>>8;
    u16MinPixel = (u16PrevMinPixel*3 + u16MinPixel ) >> 2;
    u16PrevMinPixel = u16MinPixel;

    u16MaxMinPixel = u16MaxPixel - u16MinPixel;

    if(u8Value>=0xFF)
    {
        u8Value = 0xFF;
    }

    u16HDSDD_Det_threshold = u16HDSDDDetoffset +((u16MaxMinPixel*6)>>2) + ((u8Value*5)>>2);

    if(u16HDSDD_Det_threshold >=0xFFFF)
    {
        u16HDSDD_Det_threshold=0xFFFF;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK02_71_L, (MS_U16)u16HDSDD_Det_threshold, 0xFFFF);
    MApi_XC_W2BYTEMSK(REG_SC_BK02_72_L, (MS_U16)(u16HDSDD_Det_threshold>>1), 0xFFFF);

    u32HDcntAct =  (MApi_XC_R2BYTE(REG_SC_BK02_75_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_74_L);
    u32SDcntAct =  (MApi_XC_R2BYTE(REG_SC_BK02_77_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_76_L);
    u32HDcntNonAct =  (MApi_XC_R2BYTE(REG_SC_BK02_79_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_78_L);
    u32SDcntNonAct =  (MApi_XC_R2BYTE(REG_SC_BK02_7B_L) << 16) + MApi_XC_R2BYTE(REG_SC_BK02_7A_L);

    if( (u32HDcntAct > 0x10) && (u32SDcntAct != 0) )
    {
        if(u16HDConfirmCnt < HD_SPEED)
       {
            u16HDConfirmCnt = 0;
       }
        else
       {
            u16HDConfirmCnt = u16HDConfirmCnt - HD_SPEED;
       }
    }
    else if( u32SDcntAct != 0 ) //*&& FeatherCnt > FEATHER_CNT_TH*/ )//&& HDcnt_NonAct !=0) // && (HDcnt_NonAct < 0x90000))
    {
        if(u16HDConfirmCnt > (0xFF - SD_SPEED))
        {
            u16HDConfirmCnt = 0xFF;
        }
        else
        {
            u16HDConfirmCnt = u16HDConfirmCnt + SD_SPEED;
        }
    }
    else
    {
        if(u16HDConfirmCnt < 1)
        {
            u16HDConfirmCnt = 0;
        }
        else
        {
            u16HDConfirmCnt = u16HDConfirmCnt - 1;
        }
    }

    if( u16HDConfirmCnt > 0x80 )
    {
        u32HDConfirmCntReg = u16HDConfirmCnt - 0x80;
    }
    else
    {
        u32HDConfirmCntReg = 0;
    }

    u32HDConfirmCntReg = (u32HDConfirmCntReg*HDSDD_SPEED) >> HDSDD_DIV;

    if( u32HDConfirmCntReg > 0x3F )
    {
        u32HDConfirmCntReg = 0x3F;
    }

    return (u32HDConfirmCntReg&0x003F);
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
 MS_U8 readHistogramPart(MS_U16* au16Histogram, MS_U8 u8CountForDBK, MS_U16 u16Initial_point, MS_U16 u16End_point)
 {
     MS_U8 u8Data_ack_en;
     MS_U16 u16Bin;

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
             for(u16Bin = u16Initial_point; u16Bin < u16End_point; u16Bin++)
             {
                 MApi_XC_W2BYTEMSK(REG_SC_BK0C_0E_L, (MS_U16)(0x8000 + u16Bin), 0xFFFF);
                 // read data from selected address
                 au16Histogram[u16Bin] = MApi_XC_R2BYTEMSK(REG_SC_BK0C_0F_L, 0xFFFF);
             }
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

     if (s8MinIndex >= 0 && s8MinIndex <28)//if (width == 32) //no such pattern yet, only artificials
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
         //DBK Variables
     static MS_U16 au16Histogram[MaxWidth] = {0};
     static MS_BOOL bDBK_initial = 0;
     MS_U8 u8ReadDBKHistAck = 0;
     MS_U16 u16Scan_range = 320;
     MS_U16 u16Initial_point = 160;
     MS_U16 u16End_point = u16Initial_point+u16Scan_range;
     static MS_U8 u8CountForSample = 0;
     static MS_U8 u8CountForDBK = 0;
     static MS_U8 u8Widdth = 8;
     MS_U32 u32Strength[paraSize] = {0};
     static MS_U32 u32Strength_IIR[paraSize] ={0};
     MS_U8 u8MaxBin = 0;
     MS_U32 u32TotalStrength = 0;
     MS_U32 u32StrengthLPF =0;
     MS_U32 u32AvergeStrength = 1;
     MS_U16 u16Bin = 0;
     static MS_U8 au8MaxBin_pre[25] = {0};
     MS_U8 u8Pre_bin = 0;
     MS_S8 s8Boundary_left;
     MS_U8 u8Boundary_right;
     MS_U16 u16GridReport_l = 0;
     MS_U16 u16GridReport_m = 0;
     MS_U16 u16Non_gridReport_l = 0;
     MS_U16 u16Non_gridReport_m = 0;
     MS_U32 u32GridReport_sum=0;
     MS_U32 u32Non_gridReport_sum=0;
     MS_U32 u32Total_Report_sum=0;
     MS_U32 u32AvgReport =25000000,u32DiffReport = 5000000;
     static MS_U32 u32GridReport_sumIIR=0;
     static MS_U32 u32Non_gridReport_sumIIR=0;
     double gridReport_percent = 0.0;
     double adaptiveRatio_hwReport = 0.0,adjust_step = 0.02;
     static double maxbin_thrd = 1.1,percentage_offset = 0.0;
     MS_U8 u8DBKGain_hw=0;
     MS_U8 u8DBK_coase_TH = 2;
     MS_U8 u8DetailGain_hw = 2;
     MS_U8 u8STD_Threshold_hw=0;
     MS_U32 u32Max_bin_thrd = 0;
     double scaleUp_factor_w11 = 1.0;
     static MS_U32 u32StaticValueTemp=0,u32StaticCount=0;
     int log_en = 0;
     //log_en = (MS_U32)MApi_XC_R2BYTEMSK(REG_SC_BK30_01_L, 0x000F); //easter

    if (isSceneChangeY)
    {
        u8CountForDBK = 0;
        for(u16Bin=0;u16Bin<25;u16Bin++)
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

    if((u16End_point+u16Scan_range*u8CountForSample) > u16Width)
    {
        u8CountForSample = 0;
    }


     u16Initial_point =min((u16Initial_point + u16Scan_range*u8CountForSample),(MaxWidth-1));
     u16End_point = min((u16End_point+u16Scan_range*u8CountForSample),(MaxWidth-1));

    if ( (u8CountForDBK == 0)  )	// Read Histogram
    {
        u8ReadDBKHistAck = readHistogramPart(au16Histogram, u8CountForDBK, u16Initial_point, u16End_point);
        bDBK_initial = bDBK_initial | true;
        if((u8ReadDBKHistAck==1)&& (u32StaticCount < 15))
        {
            u8Widdth = DBK_Width_Detect(isSceneChangeY);
        }
        u8Widdth = max(min(u8Widdth,paraSize-1),0);
        if (u8ReadDBKHistAck)
        {
            u8CountForDBK++;
        }
    }
    else if  (u8CountForDBK == 1)
    {
        if ( bDBK_initial == 1)
        {
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
                    printf(" %d = %05d\n",u16Bin,u32Strength_IIR[u16Bin]);
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
                    printf("u32StrengthLPF:%d u32Max_bin_thrd:%d\n",u32StrengthLPF,u32Max_bin_thrd);
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
             printf("=====Motion :[%u]=====\n",u32MotionValue);
             printf("===u32StaticCount:%d===\n",u32StaticCount);
            }

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
             printf(" Max bin :%05d width:%5d u32AvergeStrength:%5d\n", u8MaxBin,u8Widdth,u32AvergeStrength);
             printf("left:%5d right:%5d\n",s8Boundary_left,u8Boundary_right);
             printf("total_bin:%d u16Width:%d\n",u32TotalStrength,u16Width);
             printf("grid_report :%x non-grid report:%x bin:%d\n",u32GridReport_sum,u32Non_gridReport_sum,u8MaxBin);
             printf("gridReport_percent:%d u32GridReport_sumIIR:%d u32Non_gridReport_sumIIR:%d\n",(int)(100*gridReport_percent),u32GridReport_sumIIR,u32Non_gridReport_sumIIR);
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

             //**new method with HW Accelerator**
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


        }
        u8CountForDBK++;
        u8CountForSample++;

    }
    if (u8CountForDBK >= 2)
    {
        u8CountForDBK = 0;
    }
}
static MS_U32 md_adjust_level_iir   = 0;
static MS_U32 psnr_std_level_thrd_iir  = 0;
static MS_U32 dnr_std_thrd_iir = 0;
static MS_U32 luma_sum_pre=0;
static MS_U16 dnr_md_high_thrd_level_iir =0;
static MS_U16 dnr_md_low_thrd_level_iir  =0;

void MDrv_SC_HISNR_driver(MS_U16 u16Width, MS_U16 u16Height)
{
    MS_BOOL bhistogramacken=0;
    MS_U16 u16noisehistogram[16];
    MS_U16 u16noisehistogramscaled[16];
    MS_U32 u32scaledratio = 4;
    MS_U16 u16bin;
    // define value
    MS_U16  u16noiselevellowthrd0 = 0x0;
    MS_U16  u16noiselevellowthrd1 = 0x18;
    MS_U16  u16noiselevellowthrd2 = 0x28;
    MS_U16  u16noiselevellowthrd3 = 0x38;
    MS_U16  u16noiselevelhighthrd3 = 0x60;
    // AUTO NR, HISDNR
    MS_U16 u16noisebinstep = 0x00;
    MS_U16 u16noisebinthrd = 0x4C;
    MS_U16 u16pauseack = 0;
    MS_U16 u16dnrstdlevel0,u16dnrstdlevel1,u16dnrstdlevel2, u16dnrstdlevel3;
    MS_U16 u16mdadjustlevel0,u16mdadjustlevel1,u16mdadjustlevel2, u16mdadjustlevel3;
    MS_U16 u16psnrstdlevel0thrd,u16psnrstdlevel1thrd,u16psnrstdlevel2thrd, u16psnrstdlevel3thrd;
    MS_U16 u16dnrmdhighthrdlevel0,u16dnrmdlowthrdlevel0;
    MS_U16 u16dnrmdhighthrdlevel1,u16dnrmdlowthrdlevel1;
    MS_U16 u16dnrmdhighthrdlevel2,u16dnrmdlowthrdlevel2;
    MS_U16 u16dnrmdhighthrdlevel3,u16dnrmdlowthrdlevel3;
    MS_U16 u16dnrstdlevel=0;
    MS_U16 u16dnrmdhighthrdlevel=0;
    MS_U16 u16dnrmdlowthrdlevel=0;
    MS_U16 u16mdadjustlevel=0;
    MS_U16 u16psnrstdlevelthrd=0;
    MS_U16 u16mdpreshift=0;
    MS_U16 u16mdpregain=0;
    MS_U16 u16Height_div;
    MS_U16 u16Vstartheight;
    MS_U16 u16Vendheight;
    MS_U16 u16Vactiveheight;
    MS_U16 u16Hstartwidth,u16Hendwidth;
    MS_U16 u16Hactivewidth;
    MS_U32 u32pixelnumber;    // directly take
    MS_U16 u16LargerThanHigh;
    MS_U16 u16Offfromlow;
    MS_U16 u16adjustalpha;
    MS_U32 u32weightedsum;
    MS_U32 u32weightedsumother=0;
    MS_U32 u32lumasum;
    MS_S32 s32lumaavgpre;  // 16bits
    MS_S32 s32lumaavg;
    MS_S32 s32lumaavgdiff;
    MS_U32 u32iirstrength;
    MS_U16 u16histogrammax = 0;
    MS_U16 u16histogrammaxdiff=0;
    MS_U16 u16BitsValue4;
    MS_U16 u16maxbin = 0;
    MS_U16 u16maxvalue = 0;
    MS_U16 u16result;
    MS_U32 u32adjustresult;
    MS_U16 u16calculatedresult;
    MS_U16 u16noiselevelint=0;
    MS_U16 u16noisestrength;
    MS_S16 s16mdadjustleveloffset=u16mdadjustlevel;

    XC_ApiStatus stXCStatus;
    memset(&stXCStatus, 0x00, sizeof(stXCStatus));

    if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
    {
        printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
    }

    if(stXCStatus.bInterlace)
    {
        u16Height_div = u16Height / 2 ;
    }
    else
    {
        u16Height_div = u16Height ;
    }

    u32scaledratio = (MS_U32)(4.0 * (u16Width*u16Height_div/172800));  // 720*240 = 172800

    if(u32scaledratio<4)
    {
        u32scaledratio =4;
    }

    if(u16Width<=1000)
    {
        u16Vstartheight = u16Height_div/240;
    }
    else
    {
        u16Vstartheight = 0x10;
    }

    u16Vendheight =    (u16Height_div - u16Vstartheight*8)/8;
    u16Vactiveheight = (u16Vendheight-u16Vstartheight)*8;

    MApi_XC_W2BYTEMSK(REG_SC_BK0E_32_L, u16Vstartheight, 0x00FF);
    MApi_XC_W2BYTEMSK(REG_SC_BK0E_32_L, u16Vendheight<<8, 0xFF00);

    u16Hstartwidth = 0;
    u16Hendwidth   = u16Width/8;

    MApi_XC_W2BYTEMSK(REG_SC_BK0E_31_L, u16Hstartwidth, 0x00FF);
    MApi_XC_W2BYTEMSK(REG_SC_BK0E_31_L, u16Hendwidth<<8, 0xFF00);

    u16Hactivewidth = (u16Hendwidth-u16Hstartwidth)*8;
    u32pixelnumber =(u16Hactivewidth*u16Vactiveheight) ;    // directly take

    //-------------------------------------------------------
    while ( !bhistogramacken )
        bhistogramacken = MApi_XC_R2BYTEMSK(REG_SC_BK0E_01_L, BIT(2));

    if (bhistogramacken)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK0E_01_L, 1, BIT(2));

        u16noisehistogram[0] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_10_L, 0xFFFF);
        u16noisehistogram[1] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_11_L, 0xFFFF);
        u16noisehistogram[2] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_12_L, 0xFFFF);
        u16noisehistogram[3] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_13_L, 0xFFFF);
        u16noisehistogram[4] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_14_L, 0xFFFF);
        u16noisehistogram[5] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_15_L, 0xFFFF);
        u16noisehistogram[6] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_16_L, 0xFFFF);
        u16noisehistogram[7] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_17_L, 0xFFFF);
        u16noisehistogram[8] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_18_L, 0xFFFF);
        u16noisehistogram[9] =  (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_19_L, 0xFFFF);
        u16noisehistogram[10] = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_1A_L, 0xFFFF);
        u16noisehistogram[11] = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_1B_L, 0xFFFF);
        u16noisehistogram[12] = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_1C_L, 0xFFFF);
        u16noisehistogram[13] = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_1D_L, 0xFFFF);
        u16noisehistogram[14] = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_1E_L, 0xFFFF);
        u16noisehistogram[15] = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_1F_L, 0xFFFF);

        for(u16bin=0; u16bin<16; u16bin++)
            u16noisehistogramscaled[u16bin] = (MS_U16)((MS_S32)u16noisehistogram[u16bin]/u32scaledratio);

        u32weightedsum = u16noisehistogramscaled[0]*64*u32scaledratio;   // 6bits

        for(u16bin=5; u16bin<16; u16bin++)
            u32weightedsumother += u16noisehistogramscaled[u16bin];
        // read luma sum
        u32lumasum = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_48_L, 0xFFFF);

        // get image size 480i,1080i
        s32lumaavgpre  =  (luma_sum_pre*16384)/u32pixelnumber;  // 16bits
        s32lumaavg      =  (u32lumasum*16384)/u32pixelnumber;
        s32lumaavgdiff = (MS_U16) abs(s32lumaavgpre-s32lumaavg);

        luma_sum_pre = u32lumasum;

        u32iirstrength=2;

        // remove pause_ack
        if(s32lumaavgdiff>=20)
        {
            u32iirstrength=8;
        }

        // alpha before moodify
        if( (u32weightedsum >= (3*u32pixelnumber/4)) &&  (u32weightedsumother!=0))
        {
            u16pauseack = 2;
        }

        //if(pause_ack==0)
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK0E_20_L, u16noisehistogramscaled[0], 0x03FF);
            MApi_XC_W2BYTEMSK(REG_SC_BK0E_21_L, u16noisehistogramscaled[1], 0x03FF);
            MApi_XC_W2BYTEMSK(REG_SC_BK0E_22_L, u16noisehistogramscaled[2], 0x03FF);
            MApi_XC_W2BYTEMSK(REG_SC_BK0E_23_L, u16noisehistogramscaled[3], 0x03FF);
            MApi_XC_W2BYTEMSK(REG_SC_BK0E_24_L, u16noisehistogramscaled[4], 0x03FF);
            MApi_XC_W2BYTEMSK(REG_SC_BK0E_25_L, u16noisehistogramscaled[5], 0x03FF);
            MApi_XC_W2BYTEMSK(REG_SC_BK0E_26_L, u16noisehistogramscaled[6], 0x03FF);
            MApi_XC_W2BYTEMSK(REG_SC_BK0E_27_L, u16noisehistogramscaled[7], 0x03FF);
        }

        u16dnrstdlevel0 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_07_L, 0xFF00)>>8);
        u16dnrstdlevel1 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_08_L, 0xFF00)>>8);
        u16dnrstdlevel2 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_09_L, 0xFF00)>>8);
        u16dnrstdlevel3 = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_4B_L, 0x00FF);

        u16dnrmdhighthrdlevel0 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_03_L, 0xFF00)>>8);
        u16dnrmdlowthrdlevel0 = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_03_L, 0x00FF);
        u16dnrmdhighthrdlevel1 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_04_L, 0xFF00)>>8);
        u16dnrmdlowthrdlevel1  = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_04_L, 0x00FF);
        u16dnrmdhighthrdlevel2 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_05_L, 0xFF00)>>8);
        u16dnrmdlowthrdlevel2  = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_05_L, 0x00FF);
        u16dnrmdhighthrdlevel3 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_4A_L, 0xFF00)>>8);
        u16dnrmdlowthrdlevel3  = (MS_U16)MApi_XC_R2BYTEMSK(REG_SC_BK0E_4A_L, 0x00FF);

        u16mdadjustlevel0 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_06_L, 0x000F)>>0);
        u16mdadjustlevel1 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_06_L, 0x00F0)>>4);
        u16mdadjustlevel2 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_06_L, 0x0F00)>>8);
        u16mdadjustlevel3 = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_49_L, 0x000F)>>0);

        u16psnrstdlevel0thrd = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_2A_L, 0x00FF)>>0);
        u16psnrstdlevel1thrd = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_2B_L, 0xFF00)>>8);
        u16psnrstdlevel2thrd = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_2C_L, 0x00FF)>>0);
        u16psnrstdlevel3thrd = (MS_U16)(MApi_XC_R2BYTEMSK(REG_SC_BK0E_2D_L, 0x00FF)>>0);

        for (u16bin =0; u16bin<8;u16bin++)
        {
            if(u16histogrammax<=u16noisehistogramscaled[u16bin])
            	{
                u16histogrammax=u16noisehistogramscaled[u16bin] ;
            	}
        }

        for (u16bin =0; u16bin<8;u16bin++)
            u16histogrammaxdiff +=abs(u16histogrammax-u16noisehistogramscaled[u16bin]) ;

        if( u16histogrammaxdiff > u16noisebinthrd )
        {
            //cond_diagonal = 1;
            u16adjustalpha = 0xF;
        }
        else
        {
            u16Offfromlow = u16noisebinthrd -  u16histogrammaxdiff;
            //cond_diagonal = 0;
            switch( u16noisebinstep )
            {
                case 0: u16BitsValue4 = u16Offfromlow &0xF;
                    u16LargerThanHigh = ( ( u16Offfromlow >> 4) >0 ) ? 1 : 0;
                break;
                case 1: u16BitsValue4 = (u16Offfromlow>>1 )&0xF;
                    u16LargerThanHigh = ( (  u16Offfromlow >>5) >0 ) ? 1 : 0;
                break;
                case 2: u16BitsValue4 =  ( u16Offfromlow >>2)&0xF;
                    u16LargerThanHigh = ( (  u16Offfromlow >>6) >0 ) ? 1 : 0;
                break;
                case 3: u16BitsValue4 =  ( u16Offfromlow>>3 )&0xF;
                    u16LargerThanHigh = ( (  u16Offfromlow >>7) >0 ) ? 1 : 0;
                break;

                default:
                break;
            } // end switch

            if( u16LargerThanHigh == 1)
            {
                u16adjustalpha = 0;
            }
            else
            {
                u16adjustalpha =  ~u16BitsValue4;
            }
            u16adjustalpha = u16adjustalpha &0x0F;

        } // end of diag switch

        for(u16bin=0; u16bin<5;u16bin++)
        {
            if(u16noisehistogramscaled[u16bin]+u16noisehistogramscaled[u16bin+1]>=u16maxvalue)
            {
                u16maxvalue = u16noisehistogramscaled[u16bin]+u16noisehistogramscaled[u16bin+1];
            }
        }

        for (u16bin=0; u16bin<5;u16bin++)
        {
            if( (u16noisehistogramscaled[u16bin]+u16noisehistogramscaled[u16bin+1])==u16maxvalue)
            {
                u16maxbin = u16bin;
            }
        }

        if ( 0 == u16maxbin )   //34 is ok , wh
        {
            u16result = 16;
        }
        else if ( 1 == u16maxbin)
        {
            u16result = 32;
        }
        else if ( 2 == u16maxbin)
        {
            u16result = 48;
        }
        else if(3 == u16maxbin)
        {
            u16result =64;
        }
        else if( (4 == u16maxbin) || (5 == u16maxbin)  )
        {
            u16result = 80;
        }
        else
        {
            u16result= 16;
        }

        u32adjustresult = (MS_U32)((u16result * u16adjustalpha+8)/16.0);
        u16calculatedresult = (MS_U16)(u32adjustresult);

        if ( (u16noiselevellowthrd0 <= u16calculatedresult) && (u16calculatedresult < u16noiselevellowthrd1))   //34 is ok , wh
        {
            u16noiselevelint = 0;
        }
        else if ( (u16noiselevellowthrd1 <= u16calculatedresult) && (u16calculatedresult< u16noiselevellowthrd2))
        {
            u16noiselevelint = 1;
        }
        else if ( (u16noiselevellowthrd2 <= u16calculatedresult) && (u16calculatedresult< u16noiselevellowthrd3))
        {
            u16noiselevelint = 2;
        }
        else if((u16noiselevellowthrd3 <= u16calculatedresult) && (u16calculatedresult < u16noiselevelhighthrd3))
        {
            u16noiselevelint =3;
        }

        u16noisestrength = MApi_XC_R2BYTEMSK(REG_SC_BK0E_4B_L, 0xFF00)>>8;

        if(u16noiselevelint==0)
        {
            //hismatch_level_thrd = hismatch_level0;
            u16dnrstdlevel = u16dnrstdlevel0;
            u16dnrmdhighthrdlevel = u16dnrmdhighthrdlevel0;
            u16dnrmdlowthrdlevel = u16dnrmdlowthrdlevel0;
            u16mdadjustlevel = u16mdadjustlevel0;
            u16psnrstdlevelthrd = u16psnrstdlevel0thrd;
            u16mdpreshift = 5;
            u16mdpregain = 6;
        }
        else if(u16noiselevelint==1)
        {
            //hismatch_level_thrd = hismatch_level1;
            u16dnrstdlevel = u16dnrstdlevel1;
            u16dnrmdhighthrdlevel = u16dnrmdhighthrdlevel1;
            u16dnrmdlowthrdlevel = u16dnrmdlowthrdlevel1;
            u16mdadjustlevel = u16mdadjustlevel1;
            u16psnrstdlevelthrd = u16psnrstdlevel1thrd;
            u16mdpreshift = 2;
            u16mdpregain = 1;
        }
        else if(u16noiselevelint==2)
        {
            //hismatch_level_thrd = hismatch_level2;
            u16dnrstdlevel = u16dnrstdlevel2;
            u16dnrmdhighthrdlevel = u16dnrmdhighthrdlevel2;
            u16dnrmdlowthrdlevel = u16dnrmdlowthrdlevel2;
            u16mdadjustlevel = u16mdadjustlevel2;
            u16psnrstdlevelthrd = u16psnrstdlevel2thrd;
            u16mdpreshift = 2;
            u16mdpregain = 1;

        }
        else if(u16noiselevelint==3 )
        {
            //hismatch_level_thrd = hismatch_level3  ;
            u16dnrstdlevel = u16dnrstdlevel3;
            u16dnrmdhighthrdlevel = u16dnrmdhighthrdlevel3;
            u16dnrmdlowthrdlevel = u16dnrmdlowthrdlevel3;
            u16mdadjustlevel = u16mdadjustlevel3;
            u16psnrstdlevelthrd = u16psnrstdlevel3thrd;
            u16mdpreshift = 2;
            u16mdpregain = 1;
        }

        s16mdadjustleveloffset = u16mdadjustlevel;

        if(u16noisestrength==0)
        {
            s16mdadjustleveloffset = (u16mdadjustlevel-2);
        }
        else if(u16noisestrength==1)
        {
            s16mdadjustleveloffset = (u16mdadjustlevel-1);
        }
        else if(u16noisestrength==3)
        {
            s16mdadjustleveloffset = (u16mdadjustlevel+1);
        }
        else if(u16noisestrength==4)
        {
            s16mdadjustleveloffset = (u16mdadjustlevel+2);
        }

        if(s16mdadjustleveloffset<0)
        {
            s16mdadjustleveloffset = 0;
        }
        else if(s16mdadjustleveloffset>0xF)
        {
            s16mdadjustleveloffset = 0xF;
        }

        MApi_XC_W2BYTEMSK(REG_SC_BK0E_30_L, u16mdpregain, 0x003F);
        MApi_XC_W2BYTEMSK(REG_SC_BK0E_30_L, (u16mdpreshift<<8), 0x0700);

        MApi_XC_W2BYTEMSK(REG_SC_BK0E_0C_L, 0 , 0x00FF);

        dnr_std_thrd_iir = (u32iirstrength*u16dnrstdlevel *4+ (8-u32iirstrength)*dnr_std_thrd_iir)/8 ; //   *4/8(iir) = /2 ==> X.2 format

        if(u16pauseack == 2)
        {
            dnr_std_thrd_iir= 5*4 ;
        }

        MApi_XC_W2BYTEMSK(REG_SC_BK0E_0D_L, (MS_U16)( dnr_std_thrd_iir/4 + (dnr_std_thrd_iir&0x02)/2 ) , 0x00FF);

        dnr_md_high_thrd_level_iir= (MS_U16)((u32iirstrength*u16dnrmdhighthrdlevel *4+ (8-u32iirstrength)*dnr_md_high_thrd_level_iir)/8) ; //   *4/8(iir) = /2 ==> X.2 format

        MApi_XC_W2BYTEMSK(REG_SC_BK0E_0B_L, (MS_U16)(dnr_md_high_thrd_level_iir/4 + (dnr_md_high_thrd_level_iir&0x02)/2) , 0x00FF);

        dnr_md_low_thrd_level_iir= (u32iirstrength*u16dnrmdlowthrdlevel*4+ (8-u32iirstrength)*dnr_md_low_thrd_level_iir)/8 ; //   *4/8(iir) = /2 ==> X.2 format

        MApi_XC_W2BYTEMSK(REG_SC_BK0E_0A_L, (MS_U16)(dnr_md_low_thrd_level_iir/4 + (dnr_md_low_thrd_level_iir&0x02)/2 ) , 0x00FF);

        md_adjust_level_iir= (u32iirstrength*s16mdadjustleveloffset*4 +(8-u32iirstrength)*md_adjust_level_iir)/8  ;

        MApi_XC_W2BYTEMSK(REG_SC_BK0E_06_L, ((MS_U16)(md_adjust_level_iir/4 + (md_adjust_level_iir&0x02)/2) )<<0xC , 0xF000);

        psnr_std_level_thrd_iir= (u32iirstrength*u16psnrstdlevelthrd*4 + (8-u32iirstrength)*psnr_std_level_thrd_iir)/8 ;

        MApi_XC_W2BYTEMSK(REG_SC_BK0E_2D_L, ((MS_U16)( psnr_std_level_thrd_iir/4 + (psnr_std_level_thrd_iir&0x02)/2 ) )<<0x8 , 0xFF00);
    }
}


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
#define ENABLE_SCALER_DYNAMIC_SNR            0x08
#define ENABLE_SCALER_DYNAMIC_DNR            0x10
#define ENABLE_SCALER_DYNAMIC_FILM22         0x20
#define ENABLE_SCALER_DEPRESNR               0x40
#define ENABLE_SCALER_FANTASTICDNR           0x80
#define ENABLE_SCALER_MCDI_DRIVER            0x01   //BK22_7C_H
#define ENABLE_SCALER_MCNR_DRIVER            0x02
#define ENABLE_SCALER_FILM_DRIVER            0x04
#define ENABLE_SCALER_JANUS_DHD_DRIVER       0x08
#define ENABLE_SCALER_HISDNR_DRIVER          0x10
#define ENABLE_SCALER_SDHD_DETECT_DRIVER          0x20
#define ENABLE_SCALER_T12_UCDI_DRIVER            0x40
#define ENABLE_SCALER_NEW_SDHD_DETECT_DRIVER 0x80
#define ENABLE_SCALER_EXTEND_UCDI_DRIVER     0x01   //BK22_7E_L
#define ENABLE_SCALER_NEW_FILM_DRIVER        0x02
#define ENABLE_SCALER_EXTEND_UCNR_DRIVER     0x04
#define ENABLE_SCALER_AUTO_DBK_HD_DRIVER     0x08   // Auto_DBK w/o SDHDD
#define ENABLE_SCALER_AUTO_DBK_DRIVER        0x80   // BK30_01_L[15]

//-------------------------------------------------------------------------------------------------
/// this function does adaptive tuning periodic
//-------------------------------------------------------------------------------------------------
void Hal_PQ_AdaptiveTuning(void)
{
    static MS_U8 u8PreviousVcnt = 0;
    MS_U8 u8CurrentVcnt;
    MS_U8  u8Ctrl,u8ColorSum,u8MR_Offset;
    MS_U8  u8Ctrl2;
    MS_U8  u8Ctrl3;
    MS_U8  u8Ctrl4;
    MS_U32 u32MotionValue,u32MotionValue2,u32MotionValue3,u32MotionValue4,u32OOSRMC,u32OOSRF,u32ISR_NONMV0,u32SmallMoving,u32VerticalMoving,u32HorizontalMoving,u32TotalFeather,u32TotalMvComfirm;
    MS_U32 u32uComplex,u32FeatherSum,u32MotionValue_Sum;
    MS_U8 u8MotLvl,u8SDHDDReportValue;
    XC_ApiStatus stXCStatus;
    MS_BOOL bL107_en;
    MS_BOOL isSceneChangeY = MDrv_SC_Agate_SceneChangeY();
    memset(&stXCStatus, 0x00, sizeof(stXCStatus));
    //
    // Check VCnt
    //
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
    u8Ctrl2 = MDrv_SC_get_adaptive_ctrl2();
    u8Ctrl3 = MDrv_SC_get_adaptive_ctrl3();
    u8Ctrl4 = MDrv_SC_get_adaptive_ctrl4();
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

    // Adaptive functions
    if(_u16PQPre_SrcType != _u16PQSrcType_DBK_Detect[PQ_MAIN_WINDOW])            //For Auto_DBK SW driver used
    {
        _u16PQPre_SrcType = _u16PQSrcType_DBK_Detect[PQ_MAIN_WINDOW];
        bdataread = true;
    }

    if ((u8Ctrl3 & ENABLE_SCALER_AUTO_DBK_DRIVER)||(u8Ctrl4 & ENABLE_SCALER_AUTO_DBK_HD_DRIVER))               //New Add for AUTO DBK Test
    {
        if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
        {
            printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
        }
        u8SDHDDReportValue = MDrv_SC_NEW_SDHD_DETECT_report(); // W/O Feather detect
        #if 0
        MDrv_SC_Auto_Detect_Blocking_Width_driver(u8SDHDDReportValue);  //  Auto_Detect_Blocking_Width
 	 #else
         Mdrv_PQ_DBK(isSceneChangeY,u32MotionValue4,stXCStatus.stCropWin.width);
 	 #endif

    }

    if(u8Ctrl4 & ENABLE_SCALER_EXTEND_UCDI_DRIVER)
    {
        MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,u32FeatherSum);
    }
    else
    {
        // T12 UCDi function
        if (u8Ctrl2 & ENABLE_SCALER_T12_UCDI_DRIVER)
        {
            MDrv_SC_T12_UCDi_FeatherValueGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_UCDi_VerticalMovingUdRatio(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_UCDi_ComplexOffset(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_UCDi_W2SadGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_KFC_8bitMotionGain(u32SmallMoving);
            MDrv_SC_T12_UCDi_EODiWGain(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_T12_UCDi_HistoryRatio(u32OOSRMC, u32OOSRF, u32ISR_NONMV0);
            MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,u32FeatherSum);
            MDrv_SC_A5_KFC_EODiW(u32VerticalMoving);
            bL107_en = MDrv_SC_A5_L107(u32VerticalMoving, u32HorizontalMoving, u32TotalFeather, u32TotalMvComfirm,u8ColorSum,u32MotionValue, u32uComplex);
            MDrv_SC_A5_SonyChurch(u32VerticalMoving, u32HorizontalMoving, u32MotionValue, bL107_en );
        }
        else
        {
            if (u8Ctrl2 & ENABLE_SCALER_MCDI_DRIVER)
            {
                MDrv_SC_mcdi_driver(u32MotionValue2);
            }
            else
            {
                u8MotLvl = MDrv_SC_motion_level(u32MotionValue);
               MDrv_SC_mcdi_driver_new(u32MotionValue2, u8MotLvl);
            }
        }
    }

    if(u8Ctrl4 & ENABLE_SCALER_EXTEND_UCNR_DRIVER)
    {
        MDrv_SC_Extend_UCNR_driver();
    }
    else
    {
        if (u8Ctrl2 & ENABLE_SCALER_MCNR_DRIVER)
        {
            MDrv_SC_mcnr_driver(u32MotionValue2);
        }
    }
    if (u8Ctrl2 & ENABLE_SCALER_SDHD_DETECT_DRIVER)
    {
        MDrv_SC_SDHD_DETECT_driver();
    }

    if (u8Ctrl2 & ENABLE_SCALER_NEW_SDHD_DETECT_DRIVER)
    {
        MDrv_SC_NEW_SDHD_DETECT_driver();
    }

    if(u8Ctrl4 & ENABLE_SCALER_NEW_FILM_DRIVER)
    {

    }
    else
    {
      //  if (u8Ctrl2 & ENABLE_SCALER_FILM_DRIVER)
        {
            if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
            {
                printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
            }


            if( stXCStatus.u16H_SizeAfterPreScaling >= 1280 )
            {
                bg_bSd_source= true;
            }
            else
            {
                bg_bSd_source= false;
            }
        }
    }

    if (u8Ctrl2 & ENABLE_SCALER_JANUS_DHD_DRIVER)
    {
        MDrv_SC_Janus_DHD_driver();
    }

    if (u8Ctrl2 & ENABLE_SCALER_HISDNR_DRIVER)
    {
        if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
        {
            printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
        }
         MDrv_SC_HISNR_driver(stXCStatus.stCropWin.width, stXCStatus.stCropWin.height);
    }

    if (u8Ctrl & ENABLE_SCALER_DEFEATHERING)
    {
        MDrv_SC_de_feathering(u32MotionValue);
    }

    if (u8Ctrl & ENABLE_SCALER_DEFLICKERING)
    {
        MDrv_SC_de_flickering(u32MotionValue);
    }

    if (u8Ctrl & ENABLE_SCALER_DEBOUNCING)
    {
        MDrv_SC_de_bouncing(u32MotionValue2);
        MDrv_SC_A5_UCDi_OP1_HisWeight(u32MotionValue_Sum,u32FeatherSum);
    }

    if (u8Ctrl & ENABLE_SCALER_DYNAMIC_SNR)
    {
        MDrv_SC_dynamic_snr(u32MotionValue);
    }

    if (u8Ctrl & ENABLE_SCALER_DYNAMIC_DNR)
    {
        MDrv_SC_dynamic_dnr(u32MotionValue);
    }

    if (u8Ctrl & ENABLE_SCALER_DEPRESNR)
    {
        MDrv_SC_de_pre_snr(u32MotionValue2);
    }

    if (u8Ctrl & ENABLE_SCALER_FANTASTICDNR)
    {
        MDrv_SC_fantastic_dnr();
    }
}

