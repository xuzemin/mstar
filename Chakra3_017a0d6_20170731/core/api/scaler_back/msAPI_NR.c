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
// (MStar Confidential Information!) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#define MSAPI_NR_C


/******************************************************************************/
/*                    Header Files                                            */
/* ****************************************************************************/
#include "drvGlobal.h"

// Common Definition
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"

#include "apiXC.h"
#include "apiXC_Sys.h"
#include "msAPI_NR.h"
#include "apiXC_Ace.h"
#include "apiXC_Dlc.h"
#include "msAPI_VD.h"
#include "drvAVD.h"
#include "drvPQ.h"
#if (ENABLE_NEW_AUTO_NR)
#include "MApp_GlobalSettingSt.h"
#endif

#include "msAPI_Global.h"


#define NR_DBG(x)   //x
#define DNR_DBG     0

#if ENABLE_DYNAMIC_NR
//------------------------ Common ------------------------
U16 g_u16PreDynamicNR_Y0[DYNAMIC_NR_TBL_REG_NUM];
U16 g_u16PreDynamicNR_Y1[DYNAMIC_NR_TBL_REG_NUM];
U16 g_u16PreCoringOffset[2];

//------------------------ HDMI COMP ------------------------
U8  g_u8PreMotionLvl;
U8  g_u8PreLumaLvl;
U8  g_u8PreMotion;
U8  g_u8PreAverageLuma;
U16 g_u16PreSNROffset;

//-----------------------  VD -----------------------
U16 g_u16PreSharpOffset;
U16 g_u16PreSC_Coring;
U16 g_u16PreGNR_0;
U16 g_u16PreSpikeNR_1;
U16 g_u16PreGrayGuard_Gain;
U8  g_u8PreNoiseMag;


U8 g_u8DynamicNR_Y[DYNAMIC_NR_TBL_REG_NUM];
MS_DYNAMIC_NR_MISC_PARAM_NOISE g_stDynamicNR_MISC_Noise;
MS_DYNAMIC_NR_MISC_PARAM_LUMA g_stDynamicNR_MISC_Luma;
MS_DYNAMIC_NR_MISC_PARAM      g_stDynamicNR_MISC_Param;

U8 g_u8NoiseMagReadCnt;
U8 g_u8NoiseMag;

U8 g_u8BK_SC_VPS_60_H; //-- SNR
U8 g_u8BK_SC_VPS_13_L; //-- Coring
U8 g_u8BK_SC_VPS_13_H; //-- Sharpness
U8 g_u8BK_AFEC_44;     //-- Fixed AGC level


U8 tDynamicNRTbl_Motion[DYNAMIC_NR_TBL_MOTION_LEVEL_NUM][DYNAMIC_NR_TBL_REG_NUM] =
{
// BK06_4D
    {0xE8, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x00}, // 0
    {0xD8, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12, 0x00}, // 1
    {0xC8, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01, 0x00}, // 2
    {0xB8, 0x9A, 0x78, 0x56, 0x34, 0x12, 0x00, 0x00}, // 3
    {0xA8, 0x89, 0x67, 0x45, 0x23, 0x01, 0x00, 0x00}, // 4
    {0x98, 0x78, 0x56, 0x34, 0x12, 0x00, 0x00, 0x00}, // 5
};

U8 tDynamicNRTbl_Motion_HDMI_DTV[4][DYNAMIC_NR_TBL_REG_NUM] =
{
// BK06_4D
    {0x68, 0x45, 0x23, 0x01, 0x00, 0x00, 0x00, 0x00}, // Off
    {0xA8, 0x89, 0x67, 0x45, 0x23, 0x01, 0x00, 0x00}, // Low
    {0xC8, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01, 0x00}, // Mid
    {0xE8, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x00}, // High

};

U8 tDynamicNRTbl_Motion_COMP_PC[4][DYNAMIC_NR_TBL_REG_NUM] =
{
// BK06_4D
    {0x68, 0x45, 0x23, 0x01, 0x00, 0x00, 0x00, 0x00}, // Off
    {0x98, 0x78, 0x56, 0x34, 0x12, 0x01, 0x00, 0x00}, // Low
    {0xA8, 0x89, 0x67, 0x45, 0x23, 0x12, 0x01, 0x00}, // Mid
    {0xB8, 0x9A, 0x78, 0x56, 0x34, 0x12, 0x01, 0x00}, // High
};


MS_DYNAMIC_NR_MISC_PARAM tDynamicNRTbl_MISC_Param[4] =
{
    //SpikeNR SpikeNR Gray_En, Gray_Gain
    {0x02,    0xFF,   0x00,     0x00}, // Off
    {0x02,    0xFF,   0x01,     0x66}, // Low, Auto
    {0x03,    0x88,   0x01,     0x66}, // Mid
    {0x03,    0xAA,   0x01,     0x66}, // High
};

MS_DYNAMIC_NR_MISC_PARAM_LUMA tDynamicNRTbl_MISC_Luma[DYNAMIC_NR_TBL_LUMA_LEVEL_NUM] =
{//coring  SNR
    {0x33, 0x08}, // 0
    {0x33, 0x07}, // 1
    {0x22, 0x06}, // 2
    {0x22, 0x05}, // 3
    {0x11, 0x04}, // 4
    {0x11, 0x03}, // 5
    {0x00, 0x02}, // 6
    {0x00, 0x01}, // 7
};

U8 tDynamicNRTbl_Noise[DYNAMIC_NR_TBL_NOISE_LEVEL_NUM+1][DYNAMIC_NR_TBL_REG_NUM] =
{
// BK06_4D
    {0x67, 0x45, 0x34, 0x23, 0x12, 0x01, 0x00, 0x00}, // Off
    {0xAB, 0x89, 0x67, 0x45, 0x23, 0x12, 0x01, 0x00}, // Low
    {0xBC, 0x9A, 0x78, 0x56, 0x34, 0x23, 0x01, 0x00}, // Mid
    {0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12, 0x00}, // High
    {0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x00}, // -
};


MS_DYNAMIC_NR_MISC_PARAM_NOISE tDynamicNR_MISC_Noise[DYNAMIC_NR_TBL_NOISE_LEVEL_NUM+1] =
{//coring, sharp, NM_V,  NM_H_0  NM_H_1 SC_coring, GNR    GNR, SpikeNR SpikeNR CP    DP  AGC_Gain, Gray_En  Grya_Gain
  {0x00,   0x00,  0x00,  0x00,   0x00,    0x02,    0x00,  0x00,  0x02,  0x00, 0xC0, 0x9F, 0x00,     0x01,   0x66}, // off
  {0x10,   0x01,  0xC1,  0xC1,   0xC1,    0x04,    0x09,  0x1F,  0x03,  0x88, 0xC0, 0x9F, 0x00,     0x01,   0x66}, // Low
  {0x21,   0x02,  0xC2,  0xC2,   0xC2,    0x08,    0x09,  0x1F,  0x03,  0x99, 0x00, 0x00, 0x00,     0x01,   0x88}, // Mid
  {0x31,   0x04,  0xC2,  0xC2,   0xC2,    0x0A,    0x09,  0x1F,  0x03,  0xAA, 0x00, 0x00, 0x00,     0x01,   0xAA}, // High
  {0x41,   0x06,  0xC3,  0xC3,   0xC3,    0x10,    0x19,  0x1F,  0x03,  0xBB, 0x00, 0x00, 0x14,     0x01,   0xBB}, // -

};


void msAPI_DynamicNR_Init_Noise(U8 *pNRTbl, MS_DYNAMIC_NR_MISC_PARAM_NOISE *pstMisc)
{
    U8 i;

    for(i=0; i< 8; i++)
    {
        g_u16PreDynamicNR_Y0[i] = (U16)(pNRTbl[i] & 0x0F)* MApi_XC_ACE_DNR_Get_PrecisionShift();
        g_u16PreDynamicNR_Y1[i] = (U16)((pNRTbl[i] & 0xF0)>>4) * MApi_XC_ACE_DNR_Get_PrecisionShift();
        g_u8DynamicNR_Y[i]        = pNRTbl[i];
    }
    g_stDynamicNR_MISC_Noise.u8CoringOffset   = pstMisc->u8CoringOffset;
    g_stDynamicNR_MISC_Noise.u8SharpnessOffset= pstMisc->u8SharpnessOffset;
    g_stDynamicNR_MISC_Noise.u8NM_H_0         = pstMisc->u8NM_H_0;
    g_stDynamicNR_MISC_Noise.u8NM_H_1         = pstMisc->u8NM_H_1;
    g_stDynamicNR_MISC_Noise.u8NM_V           = pstMisc->u8NM_V;
    g_stDynamicNR_MISC_Noise.u8SC_Coring      = pstMisc->u8SC_Coring;
    g_stDynamicNR_MISC_Noise.u8GNR_0          = pstMisc->u8GNR_0;
    g_stDynamicNR_MISC_Noise.u8GNR_1          = pstMisc->u8GNR_1;
    g_stDynamicNR_MISC_Noise.u8SpikeNR_0      = pstMisc->u8SpikeNR_0;
    g_stDynamicNR_MISC_Noise.u8SpikeNR_1      = pstMisc->u8SpikeNR_1;
    g_stDynamicNR_MISC_Noise.u8CP             = pstMisc->u8CP;
    g_stDynamicNR_MISC_Noise.u8DP             = pstMisc->u8DP;
    g_stDynamicNR_MISC_Noise.u8AGC_Gain_Offset= pstMisc->u8AGC_Gain_Offset;
    g_stDynamicNR_MISC_Noise.u8Gray_Guard_En  = pstMisc->u8Gray_Guard_En;
    g_stDynamicNR_MISC_Noise.u8Gray_Guard_Gain= pstMisc->u8Gray_Guard_Gain;

    g_u16PreCoringOffset[0] = ((U16)pstMisc->u8CoringOffset & 0x0FL) * MApi_XC_ACE_DNR_Get_PrecisionShift();
    g_u16PreCoringOffset[1] = (((U16)pstMisc->u8CoringOffset & 0xF0L)>>4) * MApi_XC_ACE_DNR_Get_PrecisionShift();

    g_u16PreSharpOffset     = (U16)pstMisc->u8SharpnessOffset * MApi_XC_ACE_DNR_Get_PrecisionShift();
    g_u16PreSC_Coring       = (U16)pstMisc->u8SC_Coring * MApi_XC_ACE_DNR_Get_PrecisionShift();
    g_u16PreGNR_0           = (U16)pstMisc->u8GNR_0 * MApi_XC_ACE_DNR_Get_PrecisionShift();
    g_u16PreSpikeNR_1       = (U16)pstMisc->u8SpikeNR_1 * MApi_XC_ACE_DNR_Get_PrecisionShift();
    g_u16PreGrayGuard_Gain  = (U16)pstMisc->u8Gray_Guard_Gain * MApi_XC_ACE_DNR_Get_PrecisionShift();

    g_u8PreNoiseMag = MDrv_AVD_GetNoiseMag();

    MApi_XC_ACE_DNR_Init_Noise();
}

void msAPI_DynamicNR_Init_Motion(U8 *pNRTbl)
{
    U8 i;

    for(i=0; i< 8; i++)
    {
        g_u16PreDynamicNR_Y0[i] = (U16)(pNRTbl[i] & 0x0F)* MApi_XC_ACE_DNR_Get_PrecisionShift();
        g_u16PreDynamicNR_Y1[i] = (U16)((pNRTbl[i] & 0xF0)>>4) * MApi_XC_ACE_DNR_Get_PrecisionShift();
        g_u8DynamicNR_Y[i]        = pNRTbl[i];
    }

    MApi_XC_ACE_DNR_Init_Motion();
    g_u8PreMotion = MApi_XC_ACE_DNR_GetMotion();
}

void msAPI_DynamicNR_Init_Luma(MS_DYNAMIC_NR_MISC_PARAM_LUMA *pstMisc)
{

    g_stDynamicNR_MISC_Luma.u8CoringOffset   = pstMisc->u8CoringOffset;
    g_stDynamicNR_MISC_Luma.u8SNROffset      = pstMisc->u8SNROffset;

    g_u16PreCoringOffset[0] = ((U16)pstMisc->u8CoringOffset & 0x0FL) * MApi_XC_ACE_DNR_Get_PrecisionShift();
    g_u16PreCoringOffset[1] = (((U16)pstMisc->u8CoringOffset & 0xF0L)>>4) * MApi_XC_ACE_DNR_Get_PrecisionShift();
    g_u16PreSNROffset       = (U16)pstMisc->u8SNROffset * MApi_XC_ACE_DNR_Get_PrecisionShift();

    MApi_XC_ACE_DNR_Init_Motion();
    MApi_XC_ACE_DNR_Init_Luma();

    g_u8PreMotion = MApi_XC_ACE_DNR_GetMotion();
    g_u8PreAverageLuma = MApi_XC_DLC_GetAverageValue();
}


static void msAPI_DynamicNR_Luma(MS_DYNAMIC_NR_PARAM *pstDymaicNRParam)
{
    U8 i;
    U8 u8LumaTh[DYNAMIC_NR_TBL_LUMA_LEVEL_NUM] = {0x1A, 0x26, 0x32, 0x3E, 0x4A, 0x56, 0x62, 0x6E};// 16 ~ 110
    U8 u8Weight;
    U8 u8Step;
    MS_DYNAMIC_NR_MISC_PARAM_LUMA stNewMisc;
    U8 u8CurLumaLvl;
    U8 u8AverageLuma;

    u8AverageLuma =  MApi_XC_DLC_GetAverageValue();// get average luma


    u8CurLumaLvl = 0xFF;
    for(i = 0; i< DYNAMIC_NR_TBL_LUMA_LEVEL_NUM; i++)
    {
        if(u8AverageLuma < u8LumaTh[i])
        {
           u8CurLumaLvl = i;
            break;
        }
    }
    if(u8CurLumaLvl == 0xFF)
        u8CurLumaLvl = DYNAMIC_NR_TBL_LUMA_LEVEL_NUM-1;

    if(u8CurLumaLvl > pstDymaicNRParam->u8LumaEndLvl)
        u8CurLumaLvl = pstDymaicNRParam->u8LumaEndLvl;
    if(u8CurLumaLvl < pstDymaicNRParam->u8LumaStartLvl)
        u8CurLumaLvl = pstDymaicNRParam->u8LumaStartLvl;

    if(u8CurLumaLvl >= DYNAMIC_NR_TBL_LUMA_LEVEL_NUM)
        u8CurLumaLvl = DYNAMIC_NR_TBL_LUMA_LEVEL_NUM-1;

#if DNR_DBG
    printf("Cur: AverageLuma=%02bx\n", u8AverageLuma);
    printf("Pre: AverageLuma=%02bx\n", g_u8PreAverageLuma);
    printf("lvl start=%bu, end=%bu\n", pstDymaicNRParam->u8LumaStartLvl, pstDymaicNRParam->u8LumaEndLvl);
    printf("Cur: LumaLvl=%02bx\n", u8CurLumaLvl);
    printf("Pre: LumaLvl=%02bx\n", g_u8PreLumaLvl);
#endif


    //-------------------------- New coring & sharp ----------------------------
    stNewMisc.u8CoringOffset = tDynamicNRTbl_MISC_Luma[u8CurLumaLvl].u8CoringOffset;
    stNewMisc.u8SNROffset    = tDynamicNRTbl_MISC_Luma[u8CurLumaLvl].u8SNROffset;

    NR_DBG(printf("New coring=%02bx\n", stNewMisc.u8CoringOffset));
    NR_DBG(printf("New SNR   =%02bx\n", stNewMisc.u8SNROffset));


    u8Weight = MApi_XC_ACE_DNR_GetLuma_Weight(u8AverageLuma,
                                              g_u8PreAverageLuma,
                                              u8CurLumaLvl,
                                              g_u8PreLumaLvl,
                                              pstDymaicNRParam->u8L_DeFi_Th,
                                              pstDymaicNRParam->u8DeFlicker_Step1);

    u8Step = pstDymaicNRParam->u8DeFlicker_Step2;
    if(u8Step > MApi_XC_ACE_DNR_Get_PrecisionShift())
        u8Step = MApi_XC_ACE_DNR_Get_PrecisionShift();

    NR_DBG(printf("StableCnt=%bu, weight =%bu\n", g_u8LumaStableCnt, u8Weight));
    //------ Coring -----
    g_u16PreCoringOffset[0] = MApi_XC_ACE_DNR_Blending_MISC((stNewMisc.u8CoringOffset & 0x0F), g_u16PreCoringOffset[0], u8Weight, u8Step);
    g_u16PreCoringOffset[1] = MApi_XC_ACE_DNR_Blending_MISC(((stNewMisc.u8CoringOffset & 0xF0)>>4), g_u16PreCoringOffset[1], u8Weight, u8Step);
    g_stDynamicNR_MISC_Luma.u8CoringOffset= (U8)(((g_u16PreCoringOffset[1]/MApi_XC_ACE_DNR_Get_PrecisionShift())<<4) | (g_u16PreCoringOffset[0] / MApi_XC_ACE_DNR_Get_PrecisionShift()));

    //------ SNR -----
    g_u16PreSNROffset = MApi_XC_ACE_DNR_Blending_MISC(stNewMisc.u8SNROffset, g_u16PreSNROffset, u8Weight, u8Step);
    g_stDynamicNR_MISC_Luma.u8SNROffset= (U8)(g_u16PreSNROffset / MApi_XC_ACE_DNR_Get_PrecisionShift());

    NR_DBG(printf("Cur coring=%02bx\n", g_stDynamicNR_MISC_Luma.u8CoringOffset));
    NR_DBG(printf("Cur SNR   =%02bx\n", g_stDynamicNR_MISC_Luma.u8SNROffset));

    g_u8PreAverageLuma = u8AverageLuma;
    g_u8PreLumaLvl     = u8CurLumaLvl;
}

static void msAPI_DynamicNR_Motion(MS_DYNAMIC_NR_PARAM *pstDymaicNRParam)
{
    U8 i;
    U8 u8MotionTh[DYNAMIC_NR_TBL_MOTION_LEVEL_NUM-1] = {0x15, 0x2A, 0x3F, 0x54, 0x69};// 0x00 ~ 0x7F
    U8 u8NewNR_Y[8];
    U8 u8Weight;
    U8 u8Step;
    U8 u8CurMotionLvl;
    U8 u8Motion;


    u8Motion = MApi_XC_ACE_DNR_GetMotion();

    u8CurMotionLvl = 0xFF;
    for(i = 0; i< (DYNAMIC_NR_TBL_MOTION_LEVEL_NUM-1); i++)
    {
        if(u8Motion < u8MotionTh[i])
        {
           u8CurMotionLvl = i;
            break;
        }
    }
    if(u8CurMotionLvl == 0xFF)
        u8CurMotionLvl = DYNAMIC_NR_TBL_MOTION_LEVEL_NUM-1;


    if(u8CurMotionLvl > pstDymaicNRParam->u8MotionEndLvl)
        u8CurMotionLvl = pstDymaicNRParam->u8MotionEndLvl;
    if(u8CurMotionLvl < pstDymaicNRParam->u8MotionStartLvl)
        u8CurMotionLvl = pstDymaicNRParam->u8MotionStartLvl;

    if(u8CurMotionLvl > (DYNAMIC_NR_TBL_MOTION_LEVEL_NUM-1))
        u8CurMotionLvl = DYNAMIC_NR_TBL_MOTION_LEVEL_NUM-1;

#if DNR_DBG
    printf("Cur: Motion=%02bx\n", u8Motion);
    printf("Pre: Motion=%02bx\n", g_u8PreMotion);
    printf("lvl: start=%bu, end=%bu\n", pstDymaicNRParam->u8MotionStartLvl, pstDymaicNRParam->u8MotionEndLvl);
    printf("Cur: MotionLvl=%02bx, \n", u8CurMotionLvl);
    printf("Pre: MotionLvl=%02bx, \n", g_u8PreMotionLvl);
#endif
    // New NR_Y & NR_C
    NR_DBG(printf("NewNR"));
    for(i=0; i<DYNAMIC_NR_TBL_REG_NUM; i++)
    {
        u8NewNR_Y[i] =  tDynamicNRTbl_Motion[u8CurMotionLvl][i];
        NR_DBG(printf(" %02bx, ", u8NewNR_Y[i]));
    }
    NR_DBG(printf("\n"));


    u8Weight = MApi_XC_ACE_DNR_GetMotion_Weight(u8Motion,
                                                g_u8PreMotion,
                                                u8CurMotionLvl,
                                                g_u8PreMotionLvl,
                                                pstDymaicNRParam->u8M_DeFi_Th,
                                                pstDymaicNRParam->u8DeFlicker_Step1);


    u8Step = pstDymaicNRParam->u8DeFlicker_Step2;
    if(u8Step > MApi_XC_ACE_DNR_Get_PrecisionShift())
        u8Step = MApi_XC_ACE_DNR_Get_PrecisionShift();

    MApi_XC_ACE_DNR_Blending_NRTbl(&u8NewNR_Y[0],
                                   u8Weight,
                                   u8Step,
                                   &g_u16PreDynamicNR_Y0[0],
                                   &g_u16PreDynamicNR_Y1[0],
                                   &g_u8DynamicNR_Y[0]);

    g_u8PreMotion      = u8Motion;
    g_u8PreMotionLvl   = u8CurMotionLvl;
}


void msAPI_DynamicNR_Handler_Motion_Luma(MS_DYNAMIC_NR_PARAM *pstDymaicNRParam)
{
    if(pstDymaicNRParam->bMotionEn)
        msAPI_DynamicNR_Motion(pstDymaicNRParam);

    if(pstDymaicNRParam->bLumaEn)
        msAPI_DynamicNR_Luma(pstDymaicNRParam);

}

void msAPI_DynamicNR_Handler_Noise(MS_DYNAMIC_NR_PARAM *pstDymaicNRParam)
{
    U8  i, u8Tmp1;
    U8  u8CurTargetLvl;
    U8  u8DeFli_Weight, u8DeFli_Threshold;
    U8  u8Step;
    U8  u8NewNR_Y[DYNAMIC_NR_TBL_REG_NUM];
    U8 u8NoiseThresold[DYNAMIC_NR_TBL_NOISE_LEVEL_NUM];
    U8 u8LvlRange[DYNAMIC_NR_TBL_NOISE_LEVEL_NUM];
    MS_DYNAMIC_NR_MISC_PARAM_NOISE stNewMisc_VD;

    for(i=0; i< (DYNAMIC_NR_TBL_NOISE_LEVEL_NUM-1); i++)
    {
        u8NoiseThresold[i]= (pstDymaicNRParam->u8NoiseMag >= g_u8PreNoiseMag) ?
                             pstDymaicNRParam->u8NoiseThreshold[i] : // increase
                             pstDymaicNRParam->u8NoiseThreshold[i] - 2; // decrease
        if(i==0)
        {
            u8LvlRange[i]= u8NoiseThresold[i];
        }
        else
        {
            u8LvlRange[i]= u8NoiseThresold[i] - u8NoiseThresold[i-1];
        }
    }
    u8LvlRange[DYNAMIC_NR_TBL_NOISE_LEVEL_NUM-1] = 0xFF;

    u8CurTargetLvl = (pstDymaicNRParam->u8NoiseMag > u8NoiseThresold[3]) ? NoiseMagTh4 :
                     (pstDymaicNRParam->u8NoiseMag > u8NoiseThresold[2]) ? NoiseMagTh3 :
                     (pstDymaicNRParam->u8NoiseMag > u8NoiseThresold[1]) ? NoiseMagTh2 :
                     NoiseMagTh1;


    NR_DBG(printf("NoiseMag=%bx, PreNoiseMag=%bx, CurLvl=%bu\n", pstDymaicNRParam->u8NoiseMag, g_u8PreNoiseMag, u8CurTargetLvl));
    NR_DBG(printf("TH0=%bx, TH1=%bx, TH2=%bx, TH3=%bx\n",
        u8NoiseThresold[0], u8NoiseThresold[1], u8NoiseThresold[2],u8NoiseThresold[3]));
    NR_DBG(printf("Range0=%bx, Range1=%bx, Range2=%bx, Range3=%bx, Range4=%bx\n",
        u8LvlRange[0], u8LvlRange[1], u8LvlRange[2],u8LvlRange[3], u8LvlRange[4]));

    for(i=0; i<DYNAMIC_NR_TBL_REG_NUM; i++)
    {
        u8NewNR_Y[i] = tDynamicNRTbl_Noise[u8CurTargetLvl][i];
    }

    stNewMisc_VD.u8CoringOffset    = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8CoringOffset;
    stNewMisc_VD.u8SharpnessOffset = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8SharpnessOffset;
    stNewMisc_VD.u8NM_H_0          = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8NM_H_0;
    stNewMisc_VD.u8NM_H_1          = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8NM_H_1;
    stNewMisc_VD.u8NM_V            = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8NM_V;
    stNewMisc_VD.u8SC_Coring       = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8SC_Coring;
    stNewMisc_VD.u8GNR_0           = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8GNR_0;
    stNewMisc_VD.u8GNR_1           = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8GNR_1;
    stNewMisc_VD.u8SpikeNR_0       = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8SpikeNR_0;
    stNewMisc_VD.u8SpikeNR_1       = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8SpikeNR_1;
    stNewMisc_VD.u8CP              = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8CP;
    stNewMisc_VD.u8DP              = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8DP;
    stNewMisc_VD.u8AGC_Gain_Offset = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8AGC_Gain_Offset;
    stNewMisc_VD.u8Gray_Guard_En   = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8Gray_Guard_En;
    stNewMisc_VD.u8Gray_Guard_Gain = tDynamicNR_MISC_Noise[u8CurTargetLvl].u8Gray_Guard_Gain;

    u8DeFli_Threshold = u8NoiseThresold[DYNAMIC_NR_TBL_NOISE_LEVEL_NUM-1] / DYNAMIC_NR_TBL_NOISE_LEVEL_NUM;
    for(i=0; i< DYNAMIC_NR_TBL_NOISE_LEVEL_NUM-2; i++)
    {
        u8Tmp1 = u8NoiseThresold[i+1] - u8NoiseThresold[i];
        if(u8Tmp1 > u8DeFli_Threshold)
            u8DeFli_Threshold = u8Tmp1;
    }


    u8DeFli_Weight =  MApi_XC_ACE_DNR_GetNoise_Weight(pstDymaicNRParam->u8NoiseMag,
                                                      g_u8PreNoiseMag,
                                                      u8LvlRange[u8CurTargetLvl],
                                                      u8DeFli_Threshold,
                                                      pstDymaicNRParam->u8DeFlicker_Step1);


#if DNR_DBG
    printf("NewY=%bx, %bx, %bx, %bx, %bx, %bx, %bx, %bx,\n", u8NewNR_Y[0], u8NewNR_Y[1], u8NewNR_Y[2], u8NewNR_Y[3], u8NewNR_Y[4], u8NewNR_Y[5], u8NewNR_Y[6], u8NewNR_Y[7]);
#endif

#if DNR_DBG
    printf("\n>>>>PreMisc:\n");
    printf("Coring   :%x\n", g_u16PreCoringOffset);
    printf("Sharp    :%x\n", g_u16PreSharpOffset);
    printf("SC_Coring:%x\n", g_u16PreSC_Coring);
    printf("GNR_0    :%x\n", g_u16PreGNR_0);
    printf("SpikeNR_1:%x\n", g_u16PreSpikeNR_1);
    printf("GrayGn   :%x\n", g_u16PreGrayGuard_Gain);
    printf(">>>>PreMisc:\n");
#endif

#if DNR_DBG
    printf("\n>>>>NewMisc:\n");
    printf("Coring:%bx\n", stNewMisc_VD.u8CoringOffset);
    printf("Sharp :%bx\n", stNewMisc_VD.u8SharpnessOffset);
    printf("NM_V  :%bx\n", stNewMisc_VD.u8NM_V);
    printf("NM_H_0:%bx\n", stNewMisc_VD.u8NM_H_0);
    printf("NM_H_1:%bx\n", stNewMisc_VD.u8NM_H_1);
    printf("SC_Coring:%bx\n", stNewMisc_VD.u8SC_Coring);
    printf("GNR_0 :%bx\n", stNewMisc_VD.u8GNR_0);
    printf("GNR_1 :%bx\n", stNewMisc_VD.u8GNR_1);
    printf("SpikeNR_0 :%bx\n", stNewMisc_VD.u8SpikeNR_0);
    printf("SpikeNR_1 :%bx\n", stNewMisc_VD.u8SpikeNR_1);
    printf("CP    :%bx\n", stNewMisc_VD.u8CP);
    printf("DP    :%bx\n", stNewMisc_VD.u8DP);
    printf("AGC   :%bx\n", stNewMisc_VD.u8AGC_Gain_Offset);
    printf("GrayEn:%bx\n", stNewMisc_VD.u8Gray_Guard_En);
    printf("GrayGn:%bx\n", stNewMisc_VD.u8Gray_Guard_Gain);
    printf(">>>>NewMisc:\n");
#endif

    u8Step = pstDymaicNRParam->u8DeFlicker_Step2;
    if(u8Step > MApi_XC_ACE_DNR_Get_PrecisionShift())
        u8Step = MApi_XC_ACE_DNR_Get_PrecisionShift();

    if(u8Step == 0)
        u8Step = 1;

    //------ NR table ----
    MApi_XC_ACE_DNR_Blending_NRTbl(&u8NewNR_Y[0],
                                   u8DeFli_Weight,
                                   u8Step,
                                   &g_u16PreDynamicNR_Y0[0],
                                   &g_u16PreDynamicNR_Y1[0],
                                   &g_u8DynamicNR_Y[0]);


    //------ Coring -----
    g_u16PreCoringOffset[0] = MApi_XC_ACE_DNR_Blending_MISC((stNewMisc_VD.u8CoringOffset & 0x0F), g_u16PreCoringOffset[0], u8DeFli_Weight, u8Step);
    g_u16PreCoringOffset[1] = MApi_XC_ACE_DNR_Blending_MISC(((stNewMisc_VD.u8CoringOffset & 0xF0)>>4), g_u16PreCoringOffset[1], u8DeFli_Weight, u8Step);
    g_stDynamicNR_MISC_Noise.u8CoringOffset= (U8)(((g_u16PreCoringOffset[1]/MApi_XC_ACE_DNR_Get_PrecisionShift())<<4) | (g_u16PreCoringOffset[0] / MApi_XC_ACE_DNR_Get_PrecisionShift()));


    //------ sharpness -----
    g_u16PreSharpOffset = MApi_XC_ACE_DNR_Blending_MISC(stNewMisc_VD.u8SharpnessOffset, g_u16PreSharpOffset, u8DeFli_Weight, u8Step);
    g_stDynamicNR_MISC_Noise.u8SharpnessOffset= (U8)(g_u16PreSharpOffset / MApi_XC_ACE_DNR_Get_PrecisionShift());


    //------ SC_Coring -----
    g_u16PreSC_Coring = MApi_XC_ACE_DNR_Blending_MISC(stNewMisc_VD.u8SC_Coring, g_u16PreSC_Coring, u8DeFli_Weight, u8Step);
    g_stDynamicNR_MISC_Noise.u8SC_Coring= (U8)(g_u16PreSC_Coring / MApi_XC_ACE_DNR_Get_PrecisionShift());


    //------ GNR -----
    g_u16PreGNR_0 = MApi_XC_ACE_DNR_Blending_MISC(stNewMisc_VD.u8GNR_0, g_u16PreGNR_0, u8DeFli_Weight, u8Step);
    g_stDynamicNR_MISC_Noise.u8GNR_0= (U8)(g_u16PreGNR_0 / MApi_XC_ACE_DNR_Get_PrecisionShift());


    //------ SpikeNR -----
    g_u16PreSpikeNR_1 = MApi_XC_ACE_DNR_Blending_MISC(stNewMisc_VD.u8SpikeNR_1, g_u16PreSpikeNR_1, u8DeFli_Weight, u8Step);
    g_stDynamicNR_MISC_Noise.u8SpikeNR_1= (U8)(g_u16PreSpikeNR_1 / MApi_XC_ACE_DNR_Get_PrecisionShift());


    //------ Gray guard Gain -----
    g_u16PreGrayGuard_Gain = MApi_XC_ACE_DNR_Blending_MISC(stNewMisc_VD.u8Gray_Guard_Gain, g_u16PreGrayGuard_Gain, u8DeFli_Weight, u8Step);
    g_stDynamicNR_MISC_Noise.u8Gray_Guard_Gain= (U8)(g_u16PreGrayGuard_Gain / MApi_XC_ACE_DNR_Get_PrecisionShift());


    // MISC
    g_stDynamicNR_MISC_Noise.u8NM_H_0 = MApi_XC_ACE_DNR_Blending(stNewMisc_VD.u8NM_H_0, g_stDynamicNR_MISC_Noise.u8NM_H_0, u8DeFli_Weight);

    g_stDynamicNR_MISC_Noise.u8NM_H_1 = MApi_XC_ACE_DNR_Blending(stNewMisc_VD.u8NM_H_1, g_stDynamicNR_MISC_Noise.u8NM_H_1, u8DeFli_Weight);

    g_stDynamicNR_MISC_Noise.u8NM_V = MApi_XC_ACE_DNR_Blending(stNewMisc_VD.u8NM_V, g_stDynamicNR_MISC_Noise.u8NM_V, u8DeFli_Weight);

    g_stDynamicNR_MISC_Noise.u8GNR_1 = MApi_XC_ACE_DNR_Blending(stNewMisc_VD.u8GNR_1, g_stDynamicNR_MISC_Noise.u8GNR_1, u8DeFli_Weight);

    g_stDynamicNR_MISC_Noise.u8SpikeNR_0 = MApi_XC_ACE_DNR_Blending(stNewMisc_VD.u8SpikeNR_0, g_stDynamicNR_MISC_Noise.u8SpikeNR_0, u8DeFli_Weight);

    g_stDynamicNR_MISC_Noise.u8CP = MApi_XC_ACE_DNR_Blending(stNewMisc_VD.u8CP, g_stDynamicNR_MISC_Noise.u8CP, u8DeFli_Weight);

    g_stDynamicNR_MISC_Noise.u8DP = MApi_XC_ACE_DNR_Blending(stNewMisc_VD.u8DP, g_stDynamicNR_MISC_Noise.u8DP, u8DeFli_Weight);

    g_stDynamicNR_MISC_Noise.u8AGC_Gain_Offset = MApi_XC_ACE_DNR_Blending(stNewMisc_VD.u8AGC_Gain_Offset, g_stDynamicNR_MISC_Noise.u8AGC_Gain_Offset, u8DeFli_Weight);

    g_stDynamicNR_MISC_Noise.u8Gray_Guard_En = stNewMisc_VD.u8Gray_Guard_En;


#if DNR_DBG
    printf("\n>>>>CurMisc\n");
    printf("Coring:%bx\n", g_stDynamicNR_MISC_Noise.u8CoringOffset);
    printf("Sharp :%bx\n", g_stDynamicNR_MISC_Noise.u8SharpnessOffset);
    printf("NM_V  :%bx\n", g_stDynamicNR_MISC_Noise.u8NM_V);
    printf("NM_H_0:%bx\n", g_stDynamicNR_MISC_Noise.u8NM_H_0);
    printf("NM_H_1:%bx\n", g_stDynamicNR_MISC_Noise.u8NM_H_1);
    printf("SC_Coring:%bx\n", g_stDynamicNR_MISC_Noise.u8SC_Coring);
    printf("GNR_0 :%bx\n", g_stDynamicNR_MISC_Noise.u8GNR_0);
    printf("GNR_1 :%bx\n", g_stDynamicNR_MISC_Noise.u8GNR_1);
    printf("SpikeNR_0 :%bx\n", g_stDynamicNR_MISC_Noise.u8SpikeNR_0);
    printf("SpikeNR_1 :%bx\n", g_stDynamicNR_MISC_Noise.u8SpikeNR_1);
    printf("CP    :%bx\n", g_stDynamicNR_MISC_Noise.u8CP);
    printf("DP    :%bx\n", g_stDynamicNR_MISC_Noise.u8DP);
    printf("AGC   :%bx\n", g_stDynamicNR_MISC_Noise.u8AGC_Gain_Offset);
    printf("GrayEn:%bx\n", g_stDynamicNR_MISC_Noise.u8Gray_Guard_En);
    printf("GrayGn:%bx\n", g_stDynamicNR_MISC_Noise.u8Gray_Guard_Gain);
    printf(">>>>CurMisc\n");
#endif

    g_u8PreNoiseMag = pstDymaicNRParam->u8NoiseMag;
}



void msAPI_DynamicNR_Init(INPUT_SOURCE_TYPE_t enInputSourceType)
{
    if(IsSrcTypeAnalog(enInputSourceType))
    {
        msAPI_DynamicNR_Init_Noise(tDynamicNRTbl_Noise[0], &tDynamicNR_MISC_Noise[0]);
    }
    else
    {
        msAPI_DynamicNR_Init_Motion(tDynamicNRTbl_Motion[5]);
        msAPI_DynamicNR_Init_Luma(&tDynamicNRTbl_MISC_Luma[7]);
    }
}


void msAPI_DynamicNR_SetSpikeNR(MS_DYNAMIC_NR_MISC_PARAM *pParamTbl)
{


    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_SPIKE_NR_0, pParamTbl->u8Spike_NR_0);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_SPIKE_NR_1, pParamTbl->u8Spike_NR_1);

    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_GRAY_GROUND_EN, pParamTbl->u8Gray_Guard_En);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_GRAY_GROUND_GAIN, pParamTbl->u8Gray_Guard_Gain);
}

void msAPI_DynamicNR_SetValue_Luma(MS_DYNAMIC_NR_MISC_PARAM_LUMA *pParamTbl)
{
    U16 u16Reg;

    u16Reg = pParamTbl->u8CoringOffset;
    u16Reg |= (u16Reg << 8);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_PEAKING_BANK_CORING, u16Reg);

    u16Reg = (((U16)g_u8BK_SC_VPS_60_H + (U16)pParamTbl->u8SNROffset) > 0xFF) ?
            0xFF :
            g_u8BK_SC_VPS_60_H + pParamTbl->u8SNROffset;

    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_GUASSIN_SNR_THRESHOLD, u16Reg);

#if DNR_DBG
    printk("Coring: 33_L=%02bx 33_H=%02bx 34_L=%02bx 34_H=%02bx\n",
        MDrv_ReadByte(BK_SC_VPS_33_L),
        MDrv_ReadByte(BK_SC_VPS_33_H),
        MDrv_ReadByte(BK_SC_VPS_34_L),
        MDrv_ReadByte(BK_SC_VPS_34_H));
    printk("SNR   : %02bx %02bx %02bx\n", g_u8BK_SC_VPS_60_H, pParamTbl->u8SNROffset, MDrv_ReadByte(BK_SC_VPS_60_H));
#endif
}


void msAPI_DynamicNR_SetValue_Noise(MS_DYNAMIC_NR_MISC_PARAM_NOISE *pParamTbl)
{
    U16 u16Reg;

    u16Reg = (((U16)g_u8BK_SC_VPS_13_L+ (U16)pParamTbl->u8CoringOffset) > 0xFF) ?
            0xFF :
            g_u8BK_SC_VPS_13_L+ pParamTbl->u8CoringOffset;

    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_PEAKING_CORING_THRESHOLD, u16Reg);

    u16Reg = (((U16)g_u8BK_SC_VPS_13_H - (U16)pParamTbl->u8SharpnessOffset) & 0x8000) ?
            0 :
            g_u8BK_SC_VPS_13_H - pParamTbl->u8SharpnessOffset;

    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_SHARPNESS_ADJUST, u16Reg);

    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_NM_V, (U16)pParamTbl->u8NM_V);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_GNR_0, (U16)pParamTbl->u8GNR_0);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_GNR_1, (U16)pParamTbl->u8GNR_1);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_CP, (U16)pParamTbl->u8CP);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_DP, (U16)pParamTbl->u8DP);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_NM_H_0, (U16)pParamTbl->u8NM_H_0);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_NM_H_1, (U16)pParamTbl->u8NM_H_1);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_GRAY_GROUND_EN, (U16)pParamTbl->u8Gray_Guard_En);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_GRAY_GROUND_GAIN, (U16)pParamTbl->u8Gray_Guard_Gain);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_SC_CORING, (U16)pParamTbl->u8SC_Coring);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_SPIKE_NR_0, (U16)pParamTbl->u8SpikeNR_0);
    MApi_XC_ACE_DNR_SetParam(MAIN_WINDOW, E_ACE_DNR_SPIKE_NR_1, (U16)pParamTbl->u8SpikeNR_1);

#if 0 // ToDo
    u8Reg = ((U16)g_u8BK_AFEC_44 + (U16)pParamTbl->u8AGC_Gain_Offset) > 0xFF ?
            0xFF :
            g_u8BK_AFEC_44 + pParamTbl->u8AGC_Gain_Offset;


    MDrv_WriteByte(BK_AFEC_44, u8Reg);    //AGC gain
#endif

#if DNR_DBG
    printk("Orig, coring=%bx, sharp=%bx, AGC=%bx\n", g_u8BK_SC_VPS_13_L, g_u8BK_SC_VPS_13_H, g_u8BK_AFEC_44);
    printk("Coring:%bx\n", pParamTbl->u8CoringOffset);
    printk("Sharp :%bx\n", pParamTbl->u8SharpnessOffset);
    printk("NM_V  :%bx\n", pParamTbl->u8NM_V);
    printk("NM_H_0:%bx\n", pParamTbl->u8NM_H_0);
    printk("NM_H_1:%bx\n", pParamTbl->u8NM_H_1);
    printk("SC_Coring:%bx\n", pParamTbl->u8SC_Coring);
    printk("GNR_0 :%bx\n", pParamTbl->u8GNR_0);
    printk("GNR_1 :%bx\n", pParamTbl->u8GNR_1);
    printk("SpikeNR_0 :%bx\n", pParamTbl->u8SpikeNR_0);
    printk("SpikeNR_1 :%bx\n", pParamTbl->u8SpikeNR_1);
    printk("CP    :%bx\n", pParamTbl->u8CP);
    printk("DP    :%bx\n", pParamTbl->u8DP);
    printk("AGC   :%bx\n", pParamTbl->u8AGC_Gain_Offset);
    printk("GrayEn:%bx\n", pParamTbl->u8Gray_Guard_En);
    printk("GrayGn:%bx\n", pParamTbl->u8Gray_Guard_Gain);
/*
    printk("SNR_NM:%bx\n", pParamTbl->u8SNR_NM);
    printk("Motion_Dif0:%bx\n", pParamTbl->u8Motion_Diff_0);
    printk("Motion_Dif1:%bx\n", pParamTbl->u8Motion_Diff_1);
    printk("NR_Sens:%bx\n", pParamTbl->u8NR_Sens);
*/
#endif
}

void msAPI_DynamicNR_SetNRTbl(U8 *pu8Table)
{
    MApi_XC_ACE_DNR_SetNRTbl(pu8Table);
}

void mAPI_DynamicNR_GetGuassinSNR(void)
{
    g_u8BK_SC_VPS_60_H = MApi_XC_ACE_DNR_GetParam(MAIN_WINDOW, E_ACE_DNR_GUASSIN_SNR_THRESHOLD);
}

void msAPI_DynamicNR_GetSharpness(void)
{
    g_u8BK_SC_VPS_13_H = MApi_XC_ACE_DNR_GetParam(MAIN_WINDOW, E_ACE_DNR_SHARPNESS_ADJUST);
}

void msAPI_DynamicNR_GetCoring(void)
{
    g_u8BK_SC_VPS_13_L  = MApi_XC_ACE_DNR_GetParam(MAIN_WINDOW, E_ACE_DNR_PEAKING_CORING_THRESHOLD);
}

void msAPI_DynamicNR_GetAGC(void)
{
#if 0 //ToDo
    g_u8BK_AFEC_44 = MDrv_ReadByte(BK_AFEC_44);
    DynamicNR_DBG(printk("DynamicNR, AGC=%bx\n", g_u8BK_AFEC_44));
#endif
}

#if (ENABLE_NEW_AUTO_NR)
U8 m_u8NoiseMag = 0;
U8 m_u8NoiseMagReadCnt =0;
#if 0
U16 m_u16PreNoiseMag_NR =0;
#endif
U8 m_u8DebugLevel = 0;
MAPI_PQL_AUTO_NR_STATUS m_u8Status_NR = E_MAPI_AUTO_NR_STATUS_OFF;
MAPI_PQL_AUTO_NR_STATUS m_u8Prevstate_NR = E_MAPI_AUTO_NR_STATUS_OFF;
#define AUTONR_CHECK_AVERAGE_COUNTER        10
#define AUTONR_LOW2MID_THR      62//m_u16AutoNr_L2M_Thr//40
#define AUTONR_MID2LOW_THR      44//m_u16AutoNr_M2L_Thr//30

#define AUTONR_MID2HIGH_THR      83//m_u16AutoNr_M2H_Thr//60
#define AUTONR_HIGH2MID_THR      75//m_u16AutoNr_H2M_Thr//50

void msAPI_NR_SetDNRDefault(void)
{
    m_u8NoiseMag = 0;
    m_u8NoiseMagReadCnt =0;
#if 0
    m_u16PreNoiseMag_NR =0;
#endif
    m_u8Status_NR = E_MAPI_AUTO_NR_STATUS_OFF;
    m_u8Prevstate_NR = E_MAPI_AUTO_NR_STATUS_OFF;
}
void msAPI_NR_SetDNRStatus(MAPI_PQL_AUTO_NR_STATUS Status_NR,MAPI_PQL_AUTO_NR_STATUS PreStatus_NR)
{
    m_u8Status_NR = Status_NR;
    m_u8Prevstate_NR = PreStatus_NR;
}
void msAPI_DNR_Handler(void)
{
    U8  u8Ctl;
    U16 u16Value;
    PQ_3D_NR_FUNCTION_TYPE  ePQ_NRType = PQ_3D_NR_OFF;

    if(ST_VIDEO.eNRMode.eNR == MS_NR_OFF)
    {
        return;
    }
    else
    {
        if(IsATVInUse())
        {
            u8Ctl = MDrv_AVD_GetNoiseMag();// get VD noise magnitude
            //printf("\n====================>Noise mag =%d \n",u8Ctl);
            if (m_u8NoiseMagReadCnt<AUTONR_CHECK_AVERAGE_COUNTER)
            {
                m_u8NoiseMag+= u8Ctl;
                m_u8NoiseMagReadCnt++;
            }
            else
            {
                u16Value =m_u8NoiseMag;
                if( m_u8DebugLevel )
                {
                    printf("\n========================>AVG noise mag =%d \n",u16Value);
                }
                #if 0
                u16Value = ( 8*m_u16PreNoiseMag_NR + 8*u16Value )/16;//???????????????????????
                #else
                //do nothing
                #endif
                //if( m_u8DebugLevel & 0x01)
                //printf(" >>>. [AUTO NR]=== AVG Prev and Curr value %d \n",u16Value);

                if(u16Value <= AUTONR_MID2LOW_THR)
                {
                    #if 0
                    m_u16PreNoiseMag_NR = u16Value;
                    #endif
                    m_u8NoiseMagReadCnt = 0;
                    m_u8NoiseMag = 0;
                    m_u8Status_NR = E_MAPI_AUTO_NR_STATUS_LOW;
                    if( m_u8DebugLevel )
                    {
                        printf(" [AUTO NR]=== switch to AUTO_NR_STATUS_LOW \n");
                    }
                }
                else if((u16Value >= AUTONR_LOW2MID_THR) && (u16Value <= AUTONR_HIGH2MID_THR))
                {
                    #if 0
                    m_u16PreNoiseMag_NR = u16Value;
                    #endif
                    m_u8NoiseMagReadCnt = 0;
                    m_u8NoiseMag = 0;
                    m_u8Status_NR = E_MAPI_AUTO_NR_STATUS_MID;
                    if( m_u8DebugLevel )
                    {
                        printf(" [AUTO NR]=== switch to AUTO_NR_STATUS_MID \n");
                    }
                }
                else if(u16Value >= AUTONR_MID2HIGH_THR)
                {
                    #if 0
                    m_u16PreNoiseMag_NR = u16Value;
                    #endif
                    m_u8NoiseMagReadCnt = 0;
                    m_u8NoiseMag = 0;
                    m_u8Status_NR = E_MAPI_AUTO_NR_STATUS_HIGH;
                    if( m_u8DebugLevel )
                    {
                        printf(" [AUTO NR]=== switch to AUTO_NR_STATUS_HIGH \n");
                    }
                }
                else if(((u16Value<AUTONR_MID2HIGH_THR) && (u16Value>AUTONR_HIGH2MID_THR))
                    ||((u16Value<AUTONR_LOW2MID_THR) && (u16Value>AUTONR_MID2LOW_THR)))
                {
                    #if 0
                    m_u16PreNoiseMag_NR = u16Value;
                    #endif
                    m_u8NoiseMagReadCnt = 0;
                    m_u8NoiseMag = 0;
                    if( m_u8DebugLevel )
                    {
                        printf(" [AUTO NR]=== keep status[%d] \n",m_u8Status_NR);
                    }
                }

                if(m_u8Prevstate_NR!=m_u8Status_NR)
                {
                    if(m_u8Status_NR==E_MAPI_AUTO_NR_STATUS_LOW)//Auto_Low
                    {
                        if( MS_NR_LOW == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_LOW_L;
                        }
                        else if((MS_NR_MIDDLE == ST_VIDEO.eNRMode.eNR) || (MS_NR_DEFAULT== ST_VIDEO.eNRMode.eNR))
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_MID_L;
                        }
                        else if( MS_NR_HIGH == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_HIGH_L;
                        }
                        else if( MS_NR_OFF == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_OFF;
                        }
                        MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, ePQ_NRType);
                        if( m_u8DebugLevel )
                        {
                            printf(" [AUTO NR]===change to Auto_Low %u \n",ePQ_NRType);
                        }
                    }
                    else if(m_u8Status_NR==E_MAPI_AUTO_NR_STATUS_MID)//Auto_Mid
                    {
                        if( MS_NR_LOW == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_LOW_M;
                        }
                        else if((MS_NR_MIDDLE == ST_VIDEO.eNRMode.eNR) || (MS_NR_DEFAULT== ST_VIDEO.eNRMode.eNR))
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_MID_M;
                        }
                        else if( MS_NR_HIGH == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_HIGH_M;
                        }
                        else if( MS_NR_OFF == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_OFF;
                        }
                        MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, ePQ_NRType);
                        if( m_u8DebugLevel )
                        {
                            printf(" [AUTO NR]===change to Auto_Mid %u \n",ePQ_NRType);
                        }
                    }
                    else if(m_u8Status_NR==E_MAPI_AUTO_NR_STATUS_HIGH)//Auto_High
                    {
                        if( MS_NR_LOW == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_LOW_H;
                        }
                        else if((MS_NR_MIDDLE == ST_VIDEO.eNRMode.eNR) || (MS_NR_DEFAULT== ST_VIDEO.eNRMode.eNR))
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_MID_H;
                        }
                        else if( MS_NR_HIGH == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_AUTO_HIGH_H;
                        }
                        else if( MS_NR_OFF == ST_VIDEO.eNRMode.eNR )
                        {
                            ePQ_NRType = PQ_3D_NR_OFF;
                        }
                        MDrv_PQ_LoadNRTable(PQ_MAIN_WINDOW, ePQ_NRType);
                        if( m_u8DebugLevel )
                        {
                            printf(" [AUTO NR]===change to Auto_High %u \n",ePQ_NRType);
                        }
                    }
                }
                m_u8Prevstate_NR=m_u8Status_NR;
            }
        }
        else
        {
            //do nothing
        }
    }
}
#endif

//#endif // end of ENABLE_DYNAMIC_NR
void msAPI_DynamicNR_Handler(E_XC_PQ_3D_NR en3DNRType)
{
  #if 0 // fix coverity error
    MS_DYNAMIC_NR_MISC_PARAM_LUMA *pstTargetMisc_Luma = NULL;
  #endif
    MS_DYNAMIC_NR_MISC_PARAM_NOISE *pstTargetMisc_Noise = NULL;

    U8 *pu8TargetNRTBL = NULL;
    //U8 u8Bank;
    MS_DYNAMIC_NR_PARAM stDynamicNR_Param;
    BOOLEAN bDoDynamic = FALSE;


    //u8Bank = MDrv_ReadByte(BK_SELECT_00);
    if( !MApi_XC_IsMemoryFormat422(MAIN_WINDOW) || !MApi_XC_IsYUVSpace(MAIN_WINDOW))
    {
        MApi_XC_Set_NR(DISABLE, MAIN_WINDOW);

    }
    else
    {
        MApi_XC_Set_NR(ENABLE, MAIN_WINDOW);
    }

    // only E_XC_PQ_3D_NR_AUTO case
    if(en3DNRType != E_XC_PQ_3D_NR_AUTO)
    {
        return;
    }

    //if(MP_IS_ATV())
    if(IsATVInUse())
    {
        if(g_u8NoiseMagReadCnt)
        {
            g_u8NoiseMag = (g_u8NoiseMag + MDrv_AVD_GetNoiseMag())/2;

            if(g_u8NoiseMagReadCnt != 0xFF)
                g_u8NoiseMagReadCnt++;
        }
        else
        {
            g_u8NoiseMagReadCnt++;
            g_u8NoiseMag = MDrv_AVD_GetNoiseMag();
        }
    }
    else
    {
        g_u8NoiseMagReadCnt = 0;
        g_u8NoiseMag = 0;
    }

#if 0 // fix coverity error
    switch(en3DNRType)
    {
    case E_XC_PQ_3D_NR_AUTO:

        //if(MP_IS_ATV())
        if(IsATVInUse())
        {
            if(g_u8NoiseMagReadCnt > 10)
            {
                stDynamicNR_Param.u8NoiseThreshold[NoiseMagTh0] = 5;    //FacOption.mNoiseThresh[E_RFDB_1];
                stDynamicNR_Param.u8NoiseThreshold[NoiseMagTh1] = 11;   //FacOption.mNoiseThresh[E_RFDB_2];
                stDynamicNR_Param.u8NoiseThreshold[NoiseMagTh2] = 31;   //FacOption.mNoiseThresh[E_RFDB_3];
                stDynamicNR_Param.u8NoiseThreshold[NoiseMagTh3] = 42;   //FacOption.mNoiseThresh[E_RFDB_4];

                stDynamicNR_Param.u8DeFlicker_Step1 = 0x01;
                stDynamicNR_Param.u8DeFlicker_Step2 = 0x01;

                stDynamicNR_Param.u8NoiseMag = g_u8NoiseMag;
                msAPI_DynamicNR_Handler_Noise(&stDynamicNR_Param);
            }
            stDynamicNR_Param.bMotionEn  = 0; // disable Motion handler
        }
        else
        {
            stDynamicNR_Param.u8DeFlicker_Step1 = 0x01;
            stDynamicNR_Param.u8DeFlicker_Step2 = 0x01;

            stDynamicNR_Param.bMotionEn  = 1;
            stDynamicNR_Param.u8MotionEndLvl   = (0x14 & 0x0F);
            stDynamicNR_Param.u8MotionStartLvl = ((0x14>>4) & 0x0F);
            stDynamicNR_Param.u8M_DeFi_Th = 0x2A;

            g_stDynamicNR_MISC_Param.u8Spike_NR_0 = tDynamicNRTbl_MISC_Param[1].u8Spike_NR_0;
            g_stDynamicNR_MISC_Param.u8Spike_NR_1 = tDynamicNRTbl_MISC_Param[1].u8Spike_NR_1;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_En   = tDynamicNRTbl_MISC_Param[1].u8Gray_Guard_En;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_Gain = tDynamicNRTbl_MISC_Param[1].u8Gray_Guard_Gain;

        }

        bDoDynamic = TRUE;
        break;
    case E_XC_PQ_3D_NR_LOW:
        if(IsATVInUse())
        {
            pstTargetMisc_Noise = &tDynamicNR_MISC_Noise[1];
            pu8TargetNRTBL      = tDynamicNRTbl_Noise[1];
        }
        else
        {
            g_stDynamicNR_MISC_Param.u8Spike_NR_0      = tDynamicNRTbl_MISC_Param[1].u8Spike_NR_0;
            g_stDynamicNR_MISC_Param.u8Spike_NR_1      = tDynamicNRTbl_MISC_Param[1].u8Spike_NR_1;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_En   = tDynamicNRTbl_MISC_Param[1].u8Gray_Guard_En;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_Gain = tDynamicNRTbl_MISC_Param[1].u8Gray_Guard_Gain;

            pstTargetMisc_Luma = &tDynamicNRTbl_MISC_Luma[6];
            pu8TargetNRTBL     = (IsYPbPrInUse() || IsVgaInUse()) ?
                                 tDynamicNRTbl_Motion_COMP_PC[1] : tDynamicNRTbl_Motion_HDMI_DTV[1];
        }
        stDynamicNR_Param.bMotionEn  = 0; // disable Motion handler
        break;

    case E_XC_PQ_3D_NR_MID:
        if(IsATVInUse())
        {
            pstTargetMisc_Noise = &tDynamicNR_MISC_Noise[2];
            pu8TargetNRTBL      = tDynamicNRTbl_Noise[2];
        }
        else
        {
            g_stDynamicNR_MISC_Param.u8Spike_NR_0      = tDynamicNRTbl_MISC_Param[2].u8Spike_NR_0;
            g_stDynamicNR_MISC_Param.u8Spike_NR_1      = tDynamicNRTbl_MISC_Param[2].u8Spike_NR_1;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_En   = tDynamicNRTbl_MISC_Param[2].u8Gray_Guard_En;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_Gain = tDynamicNRTbl_MISC_Param[2].u8Gray_Guard_Gain;

            pstTargetMisc_Luma = &tDynamicNRTbl_MISC_Luma[5];
            pu8TargetNRTBL     = (IsYPbPrInUse() || IsVgaInUse()) ?
                                 tDynamicNRTbl_Motion_COMP_PC[2] : tDynamicNRTbl_Motion_HDMI_DTV[2];
        }
        stDynamicNR_Param.bMotionEn  = 0; // disable Motion handler
        break;

    case E_XC_PQ_3D_NR_HIGH:
        if(IsATVInUse())
        {
            pstTargetMisc_Noise = &tDynamicNR_MISC_Noise[3];
            pu8TargetNRTBL      = tDynamicNRTbl_Noise[3];
        }
        else
        {
            g_stDynamicNR_MISC_Param.u8Spike_NR_0      = tDynamicNRTbl_MISC_Param[3].u8Spike_NR_0;
            g_stDynamicNR_MISC_Param.u8Spike_NR_1      = tDynamicNRTbl_MISC_Param[3].u8Spike_NR_1;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_En   = tDynamicNRTbl_MISC_Param[3].u8Gray_Guard_En;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_Gain = tDynamicNRTbl_MISC_Param[3].u8Gray_Guard_Gain;

            pstTargetMisc_Luma = &tDynamicNRTbl_MISC_Luma[4];
            pu8TargetNRTBL     = (IsYPbPrInUse() || IsVgaInUse()) ?
                                 tDynamicNRTbl_Motion_COMP_PC[3] : tDynamicNRTbl_Motion_HDMI_DTV[3];
        }
        stDynamicNR_Param.bMotionEn  = 0; // disable Motion handler
        break;

    case E_XC_PQ_3D_NR_OFF:
    default:
        if(IsATVInUse())
        {
            pstTargetMisc_Noise = &tDynamicNR_MISC_Noise[0];
            pu8TargetNRTBL      = tDynamicNRTbl_Noise[0];
        }
        else
        {
            g_stDynamicNR_MISC_Param.u8Spike_NR_0      = tDynamicNRTbl_MISC_Param[0].u8Spike_NR_0;
            g_stDynamicNR_MISC_Param.u8Spike_NR_1      = tDynamicNRTbl_MISC_Param[0].u8Spike_NR_1;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_En   = tDynamicNRTbl_MISC_Param[0].u8Gray_Guard_En;
            g_stDynamicNR_MISC_Param.u8Gray_Guard_Gain = tDynamicNRTbl_MISC_Param[0].u8Gray_Guard_Gain;

            pstTargetMisc_Luma = &tDynamicNRTbl_MISC_Luma[7];
            //pu8TargetNRTBL     = (MP_IS_COMP() || IsVgaInUse()) ?
            pu8TargetNRTBL     = (IsYPbPrInUse() || IsVgaInUse()) ?
                                 tDynamicNRTbl_Motion_COMP_PC[0] : tDynamicNRTbl_Motion_HDMI_DTV[0];
        }
        stDynamicNR_Param.bMotionEn  = 0; // disable Motion handler
        break;
    }
#else
    //if(MP_IS_ATV())
    if(IsATVInUse())
    {
        if(g_u8NoiseMagReadCnt > 10)
        {
            stDynamicNR_Param.u8NoiseThreshold[NoiseMagTh0] = 5;    //FacOption.mNoiseThresh[E_RFDB_1];
            stDynamicNR_Param.u8NoiseThreshold[NoiseMagTh1] = 11;   //FacOption.mNoiseThresh[E_RFDB_2];
            stDynamicNR_Param.u8NoiseThreshold[NoiseMagTh2] = 31;   //FacOption.mNoiseThresh[E_RFDB_3];
            stDynamicNR_Param.u8NoiseThreshold[NoiseMagTh3] = 42;   //FacOption.mNoiseThresh[E_RFDB_4];

            stDynamicNR_Param.u8DeFlicker_Step1 = 0x01;
            stDynamicNR_Param.u8DeFlicker_Step2 = 0x01;

            stDynamicNR_Param.u8NoiseMag = g_u8NoiseMag;
            msAPI_DynamicNR_Handler_Noise(&stDynamicNR_Param);
        }
        stDynamicNR_Param.bMotionEn  = 0; // disable Motion handler
    }
    else
    {
        stDynamicNR_Param.u8DeFlicker_Step1 = 0x01;
        stDynamicNR_Param.u8DeFlicker_Step2 = 0x01;

        stDynamicNR_Param.bMotionEn  = 1;
        stDynamicNR_Param.u8MotionEndLvl   = (0x14 & 0x0F);
        stDynamicNR_Param.u8MotionStartLvl = ((0x14>>4) & 0x0F);
        stDynamicNR_Param.u8M_DeFi_Th = 0x2A;

        g_stDynamicNR_MISC_Param.u8Spike_NR_0 = tDynamicNRTbl_MISC_Param[1].u8Spike_NR_0;
        g_stDynamicNR_MISC_Param.u8Spike_NR_1 = tDynamicNRTbl_MISC_Param[1].u8Spike_NR_1;
        g_stDynamicNR_MISC_Param.u8Gray_Guard_En   = tDynamicNRTbl_MISC_Param[1].u8Gray_Guard_En;
        g_stDynamicNR_MISC_Param.u8Gray_Guard_Gain = tDynamicNRTbl_MISC_Param[1].u8Gray_Guard_Gain;

    }

    bDoDynamic = TRUE;
#endif

    // init parameter for Luma Handler
    stDynamicNR_Param.bLumaEn    = 1;
    stDynamicNR_Param.u8LumaEndLvl     = (0x07 & 0x0F);
    stDynamicNR_Param.u8LumaStartLvl   = ((0x07>>4) & 0x0F);
    stDynamicNR_Param.u8L_DeFi_Th = 0x2A;
    stDynamicNR_Param.u8DeFlicker_Step1 = 0x01;
    stDynamicNR_Param.u8DeFlicker_Step2 = 0x01;

    msAPI_DynamicNR_Handler_Motion_Luma(&stDynamicNR_Param);

    if(!bDoDynamic)
    {
        if(IsATVInUse())
        {
            msAPI_DynamicNR_Init_Noise(pu8TargetNRTBL, pstTargetMisc_Noise);
        }
        else
        {
            msAPI_DynamicNR_Init_Motion(pu8TargetNRTBL);
        }
    }

    if(IsATVInUse())
        msAPI_DynamicNR_SetValue_Noise(&g_stDynamicNR_MISC_Noise);
    else
        msAPI_DynamicNR_SetSpikeNR(&g_stDynamicNR_MISC_Param);

    msAPI_DynamicNR_SetValue_Luma(&g_stDynamicNR_MISC_Luma);

    MApi_XC_ACE_DNR_SetNRTbl(g_u8DynamicNR_Y);
}

#endif //TEST_NEW_DYNAMIC_NR

