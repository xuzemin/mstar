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
/***********************************************************************************
*
*   File:               drvVIF.c
*
*   Project:            TV/AV
*
*   Description:
*
*   Date:
*
*   Developed by:
***********************************************************************************/

#define _DRVVIF_C_

#include "debug.h"

#if 0//(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD || CHIP_FAMILY_TYPE == CHIP_FAMILY_S7J)
#include "drvVIF_T3.h"
#else
#include "drvVIF.h"
#endif

#include "Tuner.h"
#include "drvVIFInitial_MST.h"


#if ENABLE_VD_PACH_IN_CHINA
#include "MApp_GlobalSettingSt.h"
#endif


#include "drvGlobal.h"

#include "drvSYS.h"



#define VIFDBG(x)          //x

extern void  MDrv_SYS_SetAGCPadMux(SYS_AGC_PAD_SET eAgcPadMux);

static BOOL s_IFDM_bInitDone = FALSE;

static IF_FREQ m_eIF_Freq;
static VIFInitialIn VIF_InitData;

#if( (NXP_TDA18273_TUNER == FRONTEND_TUNER_TYPE)    \
    || (NXP_TDA18274_TUNER==FRONTEND_TUNER_TYPE)  \
  || (FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER)   \
  || (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)      \
  || (FRONTEND_TUNER_TYPE == SILAB_2190B_TUNER)      \
  || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER)            \
  || (FRONTEND_TUNER_TYPE == SILICON_R620D_TUNER)   \
  || (FRONTEND_TUNER_TYPE == FRESCO_FM2150A_TUNER)  \
  || (FRONTEND_TUNER_TYPE == XC7000_TUNER)  \
  || (FRONTEND_TUNER_TYPE == RDA5158_TUNER)\
  || (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER)  \
  || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
   )
VIFNotchA1A2 sVIFNotchA1A2;
VIFSOS1112 sVIFSOS1112;
#else
VIFNotchA1A2 sVIFNotchA1A2;
VIFSOS1112 sVIFSOS1112;
#endif



extern const MS_U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_I[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_MN[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_L[16];
extern const MS_U16 VIF_A1_A2_SOS11_SOS12_LP[16];

//
//******************************************************************************
//

const char* msVIF_Get_StdString(IF_FREQ eIF)
{
    char* pcStr;

    switch(eIF)
    {
        default:
            pcStr = "Unknown";
            break;
        case IF_FREQ_INVALID:
            pcStr = "invalid";
            break;
        case IF_FREQ_B:
            pcStr = "B";
            break;
        case IF_FREQ_G:
            pcStr = "G";
            break;
        case IF_FREQ_I:
            pcStr = "I";
            break;
        case IF_FREQ_DK:
            pcStr = "DK";
            break;
        case IF_FREQ_L:
            pcStr = "L";
            break;
        case IF_FREQ_L_PRIME:
            pcStr = "L_PRIME";
            break;
        case IF_FREQ_MN:
            pcStr = "MN";
            break;
        case IF_FREQ_J:
            pcStr = "J";
            break;
        case IF_FREQ_PAL_38:
            pcStr = "PAL_38";
            break;
        case IF_FREQ_MAX_IF_FREQ:
            pcStr = "MAX";
            break;
        case IF_DIGITAL_MODE:
            pcStr = "Digital";
            break;
    }

    return pcStr;
}

/***********************************************************************************
  Subject:    Enable/Disable VIF Clock
  Function:   MDrv_VIF_SetClock
  Parmeter:
  Return:
  Remark:
************************************************************************************/
void MDrv_VIF_SetClock(BOOL bEnable)
{
    DRV_VIF_SetClock(bEnable);
}

/***********************************************************************************
  Subject:    read register
  Function:   MDrv_1210_Read_CR_FOE
  Parmeter:
  Return:
  Remark:
************************************************************************************/
U8 MDrv_VIF_Read_CR_FOE(void)
{
    U8 u8Value;
    u8Value = DRV_VIF_Read_CR_FOE();
    return u8Value;
}
/***********************************************************************************
  Subject:    read register
  Function:   MDrv_1210_Read_CR_LOCK_STATUS
  Parmeter:
  Return:
  Remark:
************************************************************************************/
U8 MDrv_VIF_Read_CR_LOCK_STATUS(void)
{
    U8 u8Value;

    u8Value = DRV_VIF_Read_CR_LOCK_STATUS();

    return u8Value;
}

void MDrv_VIF_Init(void)
{

    #if (VIF_SAW_ARCH==2) // DIF input
      MDrv_SYS_SetAGCPadMux(E_SYS_ATV_AGC_PAD_SET);
    #endif

    //printf("\n^^^^^^^^^^     MDrv_VIF_Init >>>>>>>>>>>>>>>>\r\n");
    VIF_InitData.VifTop = VIF_TOP;
    VIF_InitData.VifIfBaseFreq = VIF_IF_BASE_FREQ;
    VIF_InitData.VifTunerStepSize = VIF_TUNER_STEP_SIZE;
    VIF_InitData.VifSawArch=VIF_SAW_ARCH;
    VIF_InitData.VifVgaMaximum = VIF_VGA_MAXIMUM;
    VIF_InitData.VifVgaMinimum = VIF_VGA_MINIMUM;
    VIF_InitData.GainDistributionThr = GAIN_DISTRIBUTION_THR;
    VIF_InitData.VifAgcVgaBase=VIF_AGC_VGA_BASE;
    VIF_InitData.VifAgcVgaOffs=VIF_AGC_VGA_OFFS;
    VIF_InitData.VifAgcRefNegative = VIF_AGC_REF_NEGATIVE;
    VIF_InitData.VifAgcRefPositive = VIF_AGC_REF_POSITIVE;
    VIF_InitData.VifDagc1Ref = VIF_DAGC1_REF;
    VIF_InitData.VifDagc2Ref = VIF_DAGC2_REF;
    VIF_InitData.VifDagc1GainOv=VIF_DAGC1_GAIN_OV;
    VIF_InitData.VifDagc2GainOv=VIF_DAGC2_GAIN_OV;
    #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)&&(ENABLE_VD_PACH_IN_CHINA))
    if (G_DESIGN_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION)
    {
        VIF_InitData.VifCrKf1=VIF_CR_KF1_ASIA;
        VIF_InitData.VifCrKp1=VIF_CR_KP1_ASIA;
        VIF_InitData.VifCrKi1=VIF_CR_KI1_ASIA;
        VIF_InitData.VifCrKp2=VIF_CR_KP2_ASIA;
        VIF_InitData.VifCrKi2=VIF_CR_KI2_ASIA;
        VIF_InitData.VifCrKp = VIF_CR_KP_ASIA;
        VIF_InitData.VifCrKi = VIF_CR_KI_ASIA;
        VIF_InitData.VifCrLpfSel=VIF_CR_LPF_SEL_ASIA;
        VIF_InitData.VifCrPdModeSel=VIF_CR_PD_MODE_SEL_ASIA;
        VIF_InitData.VifCrKpKiAdjust=VIF_CR_KP_KI_ADJUST_ASIA;
        VIF_InitData.VifCrKpKiAdjustGear=VIF_CR_KP_KI_ADJUST_GEAR_ASIA;
        VIF_InitData.VifCrKpKiAdjustThr1=VIF_CR_KP_KI_ADJUST_THR1_ASIA;
        VIF_InitData.VifCrKpKiAdjustThr2=VIF_CR_KP_KI_ADJUST_THR2_ASIA;
        VIF_InitData.VifCrKpKiAdjustThr3=VIF_CR_KP_KI_ADJUST_THR3_ASIA;
    }
    else
    {
        VIF_InitData.VifCrKf1=VIF_CR_KF1;
        VIF_InitData.VifCrKp1=VIF_CR_KP1;
        VIF_InitData.VifCrKi1=VIF_CR_KI1;
        VIF_InitData.VifCrKp2=VIF_CR_KP2;
        VIF_InitData.VifCrKi2=VIF_CR_KI2;
        VIF_InitData.VifCrKp = VIF_CR_KP;
        VIF_InitData.VifCrKi = VIF_CR_KI;
        VIF_InitData.VifCrLpfSel=VIF_CR_LPF_SEL;
        VIF_InitData.VifCrPdModeSel=VIF_CR_PD_MODE_SEL;
        VIF_InitData.VifCrKpKiAdjust=VIF_CR_KP_KI_ADJUST;
        VIF_InitData.VifCrKpKiAdjustGear=VIF_CR_KP_KI_ADJUST_GEAR;
        VIF_InitData.VifCrKpKiAdjustThr1=VIF_CR_KP_KI_ADJUST_THR1;
        VIF_InitData.VifCrKpKiAdjustThr2=VIF_CR_KP_KI_ADJUST_THR2;
        VIF_InitData.VifCrKpKiAdjustThr3=VIF_CR_KP_KI_ADJUST_THR3;
    }
    #else
        VIF_InitData.VifCrKf1=VIF_CR_KF1;
        VIF_InitData.VifCrKp1=VIF_CR_KP1;
        VIF_InitData.VifCrKi1=VIF_CR_KI1;
        VIF_InitData.VifCrKp2=VIF_CR_KP2;
        VIF_InitData.VifCrKi2=VIF_CR_KI2;
        VIF_InitData.VifCrKp = VIF_CR_KP;
        VIF_InitData.VifCrKi = VIF_CR_KI;
        VIF_InitData.VifCrLpfSel=VIF_CR_LPF_SEL;
        VIF_InitData.VifCrPdModeSel=VIF_CR_PD_MODE_SEL;
        VIF_InitData.VifCrKpKiAdjust=VIF_CR_KP_KI_ADJUST;
        VIF_InitData.VifCrKpKiAdjustGear=VIF_CR_KP_KI_ADJUST_GEAR;
        VIF_InitData.VifCrKpKiAdjustThr1=VIF_CR_KP_KI_ADJUST_THR1;
        VIF_InitData.VifCrKpKiAdjustThr2=VIF_CR_KP_KI_ADJUST_THR2;
        VIF_InitData.VifCrKpKiAdjustThr3=VIF_CR_KP_KI_ADJUST_THR3;
    #endif
    VIF_InitData.VifCrLockThr = VIF_CR_LOCK_THR;
    VIF_InitData.VifCrThr= VIF_CR_THR;
    VIF_InitData.VifCrLockNum=VIF_CR_LOCK_NUM;
    VIF_InitData.VifCrUnlockNum=VIF_CR_UNLOCK_NUM;
    VIF_InitData.VifCrPdErrMax=VIF_CR_PD_ERR_MAX;
    VIF_InitData.VifCrLockLeakySel=VIF_CR_LOCK_LEAKY_SEL;
    VIF_InitData.VifCrPdX2=VIF_CR_PD_X2;
    VIF_InitData.VifDynamicTopAdjust=VIF_DYNAMIC_TOP_ADJUST;
    VIF_InitData.VifDynamicTopMin=VIF_DYNAMIC_TOP_MIN;
    VIF_InitData.VifAmHumDetection=VIF_AM_HUM_DETECTION;
    VIF_InitData.VifClampgainClampSel=VIF_CLAMPGAIN_CLAMP_SEL;
    VIF_InitData.VifClampgainSyncbottRef=VIF_CLAMPGAIN_SYNCBOTT_REF;
    VIF_InitData.VifClampgainSyncheightRef=VIF_CLAMPGAIN_SYNCHEIGHT_REF;
    VIF_InitData.VifClampgainKc=VIF_CLAMPGAIN_KC;
    VIF_InitData.VifClampgainKg=VIF_CLAMPGAIN_KG;
    VIF_InitData.VifClampgainClampOren=VIF_CLAMPGAIN_CLAMP_OREN;
    VIF_InitData.VifClampgainGainOren=VIF_CLAMPGAIN_GAIN_OREN;
    VIF_InitData.VifClampgainClampOvNegative=VIF_CLAMPGAIN_CLAMP_OV_NEGATIVE;
    VIF_InitData.VifClampgainGainOvNegative=VIF_CLAMPGAIN_GAIN_OV_NEGATIVE;
    VIF_InitData.VifClampgainClampOvPositive=VIF_CLAMPGAIN_CLAMP_OV_POSITIVE;
    VIF_InitData.VifClampgainGainOvPositive=VIF_CLAMPGAIN_GAIN_OV_POSITIVE;
    VIF_InitData.VifClampgainClampMin=VIF_CLAMPGAIN_CLAMP_MIN;
    VIF_InitData.VifClampgainClampMax=VIF_CLAMPGAIN_CLAMP_MAX;
    VIF_InitData.VifClampgainGainMin=VIF_CLAMPGAIN_GAIN_MIN;
    VIF_InitData.VifClampgainGainMax=VIF_CLAMPGAIN_GAIN_MAX;
    VIF_InitData.VifClampgainPorchCnt=VIF_CLAMPGAIN_PORCH_CNT;

    VIF_InitData.VifPeakingFilterB_VHF_L=VIF_PEAKING_FILTER_B_VHF_L;
    VIF_InitData.VifYcDelayFilterB_VHF_L=VIF_YC_DELAY_FILTER_B_VHF_L;
    VIF_InitData.VifGroupDelayFilterB_VHF_L=VIF_GROUP_DELAY_FILTER_B_VHF_L;
    VIF_InitData.VifPeakingFilterGH_VHF_L=VIF_PEAKING_FILTER_GH_VHF_L;
    VIF_InitData.VifYcDelayFilterGH_VHF_L=VIF_YC_DELAY_FILTER_GH_VHF_L;
    VIF_InitData.VifGroupDelayFilterGH_VHF_L=VIF_GROUP_DELAY_FILTER_GH_VHF_L;
    VIF_InitData.VifPeakingFilterDK_VHF_L=VIF_PEAKING_FILTER_DK_VHF_L;
    VIF_InitData.VifYcDelayFilterDK_VHF_L=VIF_YC_DELAY_FILTER_DK_VHF_L;
    VIF_InitData.VifGroupDelayFilterDK_VHF_L=VIF_GROUP_DELAY_FILTER_DK_VHF_L;
    VIF_InitData.VifPeakingFilterI_VHF_L=VIF_PEAKING_FILTER_I_VHF_L;
    VIF_InitData.VifYcDelayFilterI_VHF_L=VIF_YC_DELAY_FILTER_I_VHF_L;
    VIF_InitData.VifGroupDelayFilterI_VHF_L=VIF_GROUP_DELAY_FILTER_I_VHF_L;
    VIF_InitData.VifPeakingFilterL_VHF_L=VIF_PEAKING_FILTER_L_VHF_L;
    VIF_InitData.VifYcDelayFilterL_VHF_L=VIF_YC_DELAY_FILTER_L_VHF_L;
    VIF_InitData.VifGroupDelayFilterL_VHF_L=VIF_GROUP_DELAY_FILTER_L_VHF_L;
    VIF_InitData.VifPeakingFilterLL_VHF_L=VIF_PEAKING_FILTER_LL_VHF_L;
    VIF_InitData.VifYcDelayFilterLL_VHF_L=VIF_YC_DELAY_FILTER_LL_VHF_L;
    VIF_InitData.VifGroupDelayFilterLL_VHF_L=VIF_GROUP_DELAY_FILTER_LL_VHF_L;
    VIF_InitData.VifPeakingFilterMN_VHF_L=VIF_PEAKING_FILTER_MN_VHF_L;
    VIF_InitData.VifYcDelayFilterMN_VHF_L=VIF_YC_DELAY_FILTER_MN_VHF_L;
    VIF_InitData.VifGroupDelayFilterMN_VHF_L=VIF_GROUP_DELAY_FILTER_MN_VHF_L;

    VIF_InitData.VifPeakingFilterB_VHF_H=VIF_PEAKING_FILTER_B_VHF_H;
    VIF_InitData.VifYcDelayFilterB_VHF_H=VIF_YC_DELAY_FILTER_B_VHF_H;
    VIF_InitData.VifGroupDelayFilterB_VHF_H=VIF_GROUP_DELAY_FILTER_B_VHF_H;
    VIF_InitData.VifPeakingFilterGH_VHF_H=VIF_PEAKING_FILTER_GH_VHF_H;
    VIF_InitData.VifYcDelayFilterGH_VHF_H=VIF_YC_DELAY_FILTER_GH_VHF_H;
    VIF_InitData.VifGroupDelayFilterGH_VHF_H=VIF_GROUP_DELAY_FILTER_GH_VHF_H;
    VIF_InitData.VifPeakingFilterDK_VHF_H=VIF_PEAKING_FILTER_DK_VHF_H;
    VIF_InitData.VifYcDelayFilterDK_VHF_H=VIF_YC_DELAY_FILTER_DK_VHF_H;
    VIF_InitData.VifGroupDelayFilterDK_VHF_H=VIF_GROUP_DELAY_FILTER_DK_VHF_H;
    VIF_InitData.VifPeakingFilterI_VHF_H=VIF_PEAKING_FILTER_I_VHF_H;
    VIF_InitData.VifYcDelayFilterI_VHF_H=VIF_YC_DELAY_FILTER_I_VHF_H;
    VIF_InitData.VifGroupDelayFilterI_VHF_H=VIF_GROUP_DELAY_FILTER_I_VHF_H;
    VIF_InitData.VifPeakingFilterL_VHF_H=VIF_PEAKING_FILTER_L_VHF_H;
    VIF_InitData.VifYcDelayFilterL_VHF_H=VIF_YC_DELAY_FILTER_L_VHF_H;
    VIF_InitData.VifGroupDelayFilterL_VHF_H=VIF_GROUP_DELAY_FILTER_L_VHF_H;
    VIF_InitData.VifPeakingFilterLL_VHF_H=VIF_PEAKING_FILTER_LL_VHF_H;
    VIF_InitData.VifYcDelayFilterLL_VHF_H=VIF_YC_DELAY_FILTER_LL_VHF_H;
    VIF_InitData.VifGroupDelayFilterLL_VHF_H=VIF_GROUP_DELAY_FILTER_LL_VHF_H;
    VIF_InitData.VifPeakingFilterMN_VHF_H=VIF_PEAKING_FILTER_MN_VHF_H;
    VIF_InitData.VifYcDelayFilterMN_VHF_H=VIF_YC_DELAY_FILTER_MN_VHF_H;
    VIF_InitData.VifGroupDelayFilterMN_VHF_H=VIF_GROUP_DELAY_FILTER_MN_VHF_H;

    VIF_InitData.VifPeakingFilterB_UHF=VIF_PEAKING_FILTER_B_UHF;
    VIF_InitData.VifYcDelayFilterB_UHF=VIF_YC_DELAY_FILTER_B_UHF;
    VIF_InitData.VifGroupDelayFilterB_UHF=VIF_GROUP_DELAY_FILTER_B_UHF;
    VIF_InitData.VifPeakingFilterGH_UHF=VIF_PEAKING_FILTER_GH_UHF;
    VIF_InitData.VifYcDelayFilterGH_UHF=VIF_YC_DELAY_FILTER_GH_UHF;
    VIF_InitData.VifGroupDelayFilterGH_UHF=VIF_GROUP_DELAY_FILTER_GH_UHF;
    VIF_InitData.VifPeakingFilterDK_UHF=VIF_PEAKING_FILTER_DK_UHF;
    VIF_InitData.VifYcDelayFilterDK_UHF=VIF_YC_DELAY_FILTER_DK_UHF;
    VIF_InitData.VifGroupDelayFilterDK_UHF=VIF_GROUP_DELAY_FILTER_DK_UHF;
    VIF_InitData.VifPeakingFilterI_UHF=VIF_PEAKING_FILTER_I_UHF;
    VIF_InitData.VifYcDelayFilterI_UHF=VIF_YC_DELAY_FILTER_I_UHF;
    VIF_InitData.VifGroupDelayFilterI_UHF=VIF_GROUP_DELAY_FILTER_I_UHF;
    VIF_InitData.VifPeakingFilterL_UHF=VIF_PEAKING_FILTER_L_UHF;
    VIF_InitData.VifYcDelayFilterL_UHF=VIF_YC_DELAY_FILTER_L_UHF;
    VIF_InitData.VifGroupDelayFilterL_UHF=VIF_GROUP_DELAY_FILTER_L_UHF;
    VIF_InitData.VifPeakingFilterLL_UHF=VIF_PEAKING_FILTER_LL_UHF;
    VIF_InitData.VifYcDelayFilterLL_UHF=VIF_YC_DELAY_FILTER_LL_UHF;
    VIF_InitData.VifGroupDelayFilterLL_UHF=VIF_GROUP_DELAY_FILTER_LL_UHF;
    VIF_InitData.VifPeakingFilterMN_UHF=VIF_PEAKING_FILTER_MN_UHF;
    VIF_InitData.VifYcDelayFilterMN_UHF=VIF_YC_DELAY_FILTER_MN_UHF;
    VIF_InitData.VifGroupDelayFilterMN_UHF=VIF_GROUP_DELAY_FILTER_MN_UHF;
    VIF_InitData.ChinaDescramblerBox = CHINA_DESCRAMBLER_BOX;
    VIF_InitData.VifDelayReduce= VIF_DELAY_REDUCE;
    VIF_InitData.VifOverModulation=VIF_OVER_MODULATION;
    VIF_InitData.VifOverModulationDetect=VIF_OM_DETECTOR;
#if (CHIP_FAMILY_TYPE >=CHIP_FAMILY_S8)
    VIF_InitData.VifACIDetect=VIF_ACI_DETECTOR;
    VIF_InitData.VifACIAGCREF=VIF_ACI_AGC_REF;
    VIF_InitData.VifADCOverflowAGCREF=VIF_ADC_OVERFLOW_AGC_REF;
    VIF_InitData.VifChanelScanAGCREF=VIF_CHANEL_SCAN_AGC_REF;
    VIF_InitData.VifSeriousACIDetect=VIF_SERIOUS_ACI_DETECTION;
    VIF_InitData.VifACIDetTHR1=VIF_ACIDET_THR1;
    VIF_InitData.VifACIDetTHR2=VIF_ACIDET_THR2;
    VIF_InitData.VifACIDetTHR3=VIF_ACIDET_THR3;
    VIF_InitData.VifACIDetTHR4=VIF_ACIDET_THR4;
#endif
    VIF_InitData.VifFreqBand = FREQ_VHF_L; // should be changed when setting tuner freq
    VIF_InitData.VifSos21FilterC0= VIF_SOS21_FILTER_C0;
    VIF_InitData.VifSos21FilterC1= VIF_SOS21_FILTER_C1;
    VIF_InitData.VifSos21FilterC2= VIF_SOS21_FILTER_C2;
    VIF_InitData.VifSos21FilterC3= VIF_SOS21_FILTER_C3;
    VIF_InitData.VifSos21FilterC4= VIF_SOS21_FILTER_C4;
    VIF_InitData.VifSos22FilterC0= VIF_SOS22_FILTER_C0;
    VIF_InitData.VifSos22FilterC1= VIF_SOS22_FILTER_C1;
    VIF_InitData.VifSos22FilterC2= VIF_SOS22_FILTER_C2;
    VIF_InitData.VifSos22FilterC3= VIF_SOS22_FILTER_C3;
    VIF_InitData.VifSos22FilterC4= VIF_SOS22_FILTER_C4;
    VIF_InitData.VifSos31FilterC0= VIF_SOS31_FILTER_C0;
    VIF_InitData.VifSos31FilterC1= VIF_SOS31_FILTER_C1;
    VIF_InitData.VifSos31FilterC2= VIF_SOS31_FILTER_C2;
    VIF_InitData.VifSos31FilterC3= VIF_SOS31_FILTER_C3;
    VIF_InitData.VifSos31FilterC4= VIF_SOS31_FILTER_C4;
    VIF_InitData.VifSos32FilterC0= VIF_SOS32_FILTER_C0;
    VIF_InitData.VifSos32FilterC1= VIF_SOS32_FILTER_C1;
    VIF_InitData.VifSos32FilterC2= VIF_SOS32_FILTER_C2;
    VIF_InitData.VifSos32FilterC3= VIF_SOS32_FILTER_C3;
    VIF_InitData.VifSos32FilterC4= VIF_SOS32_FILTER_C4;

#if (ENABLE_FM_RADIO)
    if ( IsRADIOInUse() )
        VIF_InitData.VifTunerType=2;
    else
#endif
        VIF_InitData.VifTunerType=VIF_TUNER_TYPE;

    VIF_InitData.VifCrRate_B=VIF_CR_RATE_B;
    VIF_InitData.VifCrInvert_B=VIF_CR_INVERT_B;
    VIF_InitData.VifCrRate_GH=VIF_CR_RATE_GH;
    VIF_InitData.VifCrInvert_GH=VIF_CR_INVERT_GH;
    VIF_InitData.VifCrRate_DK=VIF_CR_RATE_DK;
    VIF_InitData.VifCrInvert_DK=VIF_CR_INVERT_DK;
    VIF_InitData.VifCrRate_I=VIF_CR_RATE_I;
    VIF_InitData.VifCrInvert_I=VIF_CR_INVERT_I;
    VIF_InitData.VifCrRate_L=VIF_CR_RATE_L;
    VIF_InitData.VifCrInvert_L=VIF_CR_INVERT_L;
    VIF_InitData.VifCrRate_LL=VIF_CR_RATE_LL;
    VIF_InitData.VifCrInvert_LL=VIF_CR_INVERT_LL;
    VIF_InitData.VifCrRate_MN=VIF_CR_RATE_MN;
    VIF_InitData.VifCrInvert_MN=VIF_CR_INVERT_MN;

#if ENABLE_VD_PACH_IN_CHINA
    VIF_InitData.VifTop                    =G_FACTORY_SETTING.stVDSetting.VifTop;
    VIF_InitData.VifVgaMaximum           =G_FACTORY_SETTING.stVDSetting.Vif_VGA_MAXIMUM;
    VIF_InitData.GainDistributionThr     =G_FACTORY_SETTING.stVDSetting.Gain_DISTRIBUTION_THR;
    VIF_InitData.VifAgcVgaBase          =(G_FACTORY_SETTING.stVDSetting.Gain_DISTRIBUTION_THR >>7);
    //VIF_InitData.VifCrKp1                =G_FACTORY_SETTING.stVDSetting.Vif_CR_KP1;
    //VIF_InitData.VifCrKi1                =G_FACTORY_SETTING.stVDSetting.Vif_CR_KI1 ;
    //VIF_InitData.VifCrKp2                =G_FACTORY_SETTING.stVDSetting.Vif_CR_KP2;
    //VIF_InitData.VifCrKi2                =G_FACTORY_SETTING.stVDSetting.Vif_CR_KI2;
    //VIF_InitData.VifCrKp                =G_FACTORY_SETTING.stVDSetting.Vif_CR_KP;
    //VIF_InitData.VifCrKi                =G_FACTORY_SETTING.stVDSetting.Vif_CR_KI;
    VIF_InitData.VifCrLockThr            =G_FACTORY_SETTING.stVDSetting.Vif_CR_LOCK_THR ;
    VIF_InitData.VifCrThr                =G_FACTORY_SETTING.stVDSetting.Vif_CR_THR;
    //VIF_InitData.ChinaDescramblerBox    =0;//G_FACTORY_SETTING.stVDSetting.China_DESCRAMBLER_BOX;
    VIF_InitData.VifDelayReduce            =G_FACTORY_SETTING.stVDSetting.Vif_DELAY_REDUCE;
    VIF_InitData.VifOverModulation        =G_FACTORY_SETTING.stVDSetting.Vif_OVER_MODULATION;


    VIF_InitData.VifClampgainGainOvNegative=G_FACTORY_SETTING.stVDSetting.Vif_CLAMPGAIN_GAIN_OV_NEGATIVE;
    VIF_InitData.VifClampgainClampOvNegative=G_FACTORY_SETTING.stVDSetting.Vif_CLAMPGAIN_CLAMP_OV_NEGATIVE;

//removed    VIF_InitData.VifCrPdModeSel = G_DESIGN_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION;    // 0: imaginary part; 1: cordic

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)
    VIF_InitData.VifAgcRefNegative = G_FACTORY_SETTING.stVDSetting.Vif_AGCREFNEGATIVE; // NASA
#else
    VIF_InitData.VifChanelScanAGCREF = G_FACTORY_SETTING.stVDSetting.Vif_AGCREFNEGATIVE;
#endif

#endif

/*
    printf("\r\n=============Start of VIF init para====================",0);
    printf("\r\n %x",(WORD)VIF_InitData.VifTop);// = VIF_TOP;
    printf("\r\n %x",(WORD)VIF_InitData.VifIfBaseFreq);// = VIF_IF_BASE_FREQ;
    printf("\r\n %x",(WORD)VIF_InitData.VifTunerStepSize);// = VIF_TUNER_STEP_SIZE;
    printf("\r\n %x",(WORD)VIF_InitData.VifSawArch);//=VIF_SAW_ARCH;
    printf("\r\n %x",(WORD)VIF_InitData.VifVgaMaximum);// = VIF_VGA_MAXIMUM;
    printf("\r\n %x",(WORD)VIF_InitData.VifVgaMinimum);// = VIF_VGA_MINIMUM;
    printf("\r\n %x",(WORD)VIF_InitData.GainDistributionThr);// = GAIN_DISTRIBUTION_THR;
    printf("\r\n %x",(WORD)VIF_InitData.VifAgcVgaBase);//=VIF_AGC_VGA_BASE;
    printf("\r\n %x",(WORD)VIF_InitData.VifAgcVgaOffs);//=VIF_AGC_VGA_OFFS;
    printf("\r\n %x",(WORD)VIF_InitData.VifAgcRefNegative);// = VIF_AGC_REF_NEGATIVE;
    printf("\r\n %x",(WORD)VIF_InitData.VifAgcRefPositive);// = VIF_AGC_REF_POSITIVE;
    printf("\r\n %x",(WORD)VIF_InitData.VifDagc1Ref);// = VIF_DAGC1_REF;
    printf("\r\n %x",(WORD)VIF_InitData.VifDagc2Ref);// = VIF_DAGC2_REF;
    printf("\r\n %x",(WORD)VIF_InitData.VifDagc1GainOv);//=VIF_DAGC1_GAIN_OV;
    printf("\r\n %x",(WORD)VIF_InitData.VifDagc2GainOv);//=VIF_DAGC2_GAIN_OV;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKf1);//=VIF_CR_KF1;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKp1);//=VIF_CR_KP1;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKi1);//=VIF_CR_KI1;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKp2);//=VIF_CR_KP2;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKi2);//=VIF_CR_KI2;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKp);// = VIF_CR_KP;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKi);// = VIF_CR_KI;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrLockThr);// = VIF_CR_LOCK_THR;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrThr);//= VIF_CR_THR;
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrLockNum>>16)&0x0000FFFF));//=VIF_CR_LOCK_NUM;
    printf("%x",(WORD) (VIF_InitData.VifCrLockNum&0x0000FFFF));//=VIF_CR_LOCK_NUM;
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrUnlockNum>>16)&0x0000FFFF));//=VIF_CR_UNLOCK_NUM;
    printf("%x",(WORD) (VIF_InitData.VifCrUnlockNum&0x0000FFFF));
    printf("\r\n %x",(WORD)VIF_InitData.VifCrPdErrMax);//=VIF_CR_PD_ERR_MAX;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrLockLeakySel);//=VIF_CR_LOCK_LEAKY_SEL;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrPdX2);//=VIF_CR_PD_X2;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrLpfSel);//=VIF_CR_LPF_SEL;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrPdModeSel);//=VIF_CR_PD_MODE_SEL;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKpKiAdjust);//=VIF_CR_KP_KI_ADJUST;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKpKiAdjustGear);//=VIF_CR_KP_KI_ADJUST_GEAR;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKpKiAdjustThr1);//=VIF_CR_KP_KI_ADJUST_THR1;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKpKiAdjustThr2);//=VIF_CR_KP_KI_ADJUST_THR2;
    printf("\r\n %x",(WORD)VIF_InitData.VifCrKpKiAdjustThr3);//=VIF_CR_KP_KI_ADJUST_THR3;
    printf("\r\n %x",(WORD)VIF_InitData.VifDynamicTopAdjust);//=VIF_DYNAMIC_TOP_ADJUST;
    printf("\r\n %x",(WORD)VIF_InitData.VifDynamicTopMin);//=VIF_DYNAMIC_TOP_MIN;
    printf("\r\n %x",(WORD)VIF_InitData.VifAmHumDetection);//=VIF_AM_HUM_DETECTION;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainClampSel);//=VIF_CLAMPGAIN_CLAMP_SEL;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainSyncbottRef);//=VIF_CLAMPGAIN_SYNCBOTT_REF;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainSyncheightRef);//=VIF_CLAMPGAIN_SYNCHEIGHT_REF;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainKc);//=VIF_CLAMPGAIN_KC;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainKg);//=VIF_CLAMPGAIN_KG;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainClampOren);//=VIF_CLAMPGAIN_CLAMP_OREN;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainGainOren);//=VIF_CLAMPGAIN_GAIN_OREN;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainClampOvNegative);//=VIF_CLAMPGAIN_CLAMP_OV_NEGATIVE;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainGainOvNegative);//=VIF_CLAMPGAIN_GAIN_OV_NEGATIVE;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainClampOvPositive);//=VIF_CLAMPGAIN_CLAMP_OV_POSITIVE;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainGainOvPositive);//=VIF_CLAMPGAIN_GAIN_OV_POSITIVE;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainClampMin);//=VIF_CLAMPGAIN_CLAMP_MIN;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainClampMax);//=VIF_CLAMPGAIN_CLAMP_MAX;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainGainMin);//=VIF_CLAMPGAIN_GAIN_MIN;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainGainMax);//=VIF_CLAMPGAIN_GAIN_MAX;
    printf("\r\n %x",(WORD)VIF_InitData.VifClampgainPorchCnt);//=VIF_CLAMPGAIN_PORCH_CNT;

    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterB_VHF_L);//=VIF_PEAKING_FILTER_B_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterB_VHF_L);//=VIF_YC_DELAY_FILTER_B_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterB_VHF_L);//=VIF_GROUP_DELAY_FILTER_B_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterGH_VHF_L);//=VIF_PEAKING_FILTER_GH_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterGH_VHF_L);//=VIF_YC_DELAY_FILTER_GH_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterGH_VHF_L);//=VIF_GROUP_DELAY_FILTER_GH_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterDK_VHF_L);//=VIF_PEAKING_FILTER_DK_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterDK_VHF_L);//=VIF_YC_DELAY_FILTER_DK_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterDK_VHF_L);//=VIF_GROUP_DELAY_FILTER_DK_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterI_VHF_L);//=VIF_PEAKING_FILTER_I_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterI_VHF_L);//=VIF_YC_DELAY_FILTER_I_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterI_VHF_L);//=VIF_GROUP_DELAY_FILTER_I_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterL_VHF_L);//=VIF_PEAKING_FILTER_L_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterL_VHF_L);//=VIF_YC_DELAY_FILTER_L_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterL_VHF_L);//=VIF_GROUP_DELAY_FILTER_L_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterLL_VHF_L);//=VIF_PEAKING_FILTER_LL_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterLL_VHF_L);//=VIF_YC_DELAY_FILTER_LL_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterLL_VHF_L);//=VIF_GROUP_DELAY_FILTER_LL_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterMN_VHF_L);//=VIF_PEAKING_FILTER_MN_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterMN_VHF_L);//=VIF_YC_DELAY_FILTER_MN_VHF_L;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterMN_VHF_L);//=VIF_GROUP_DELAY_FILTER_MN_VHF_L;

    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterB_VHF_H);//=VIF_PEAKING_FILTER_B_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterB_VHF_H);//=VIF_YC_DELAY_FILTER_B_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterB_VHF_H);//=VIF_GROUP_DELAY_FILTER_B_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterGH_VHF_H);//=VIF_PEAKING_FILTER_GH_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterGH_VHF_H);//=VIF_YC_DELAY_FILTER_GH_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterGH_VHF_H);//=VIF_GROUP_DELAY_FILTER_GH_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterDK_VHF_H);//=VIF_PEAKING_FILTER_DK_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterDK_VHF_H);//=VIF_YC_DELAY_FILTER_DK_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterDK_VHF_H);//=VIF_GROUP_DELAY_FILTER_DK_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterI_VHF_H);//=VIF_PEAKING_FILTER_I_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterI_VHF_H);//=VIF_YC_DELAY_FILTER_I_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterI_VHF_H);//=VIF_GROUP_DELAY_FILTER_I_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterL_VHF_H);//=VIF_PEAKING_FILTER_L_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterL_VHF_H);//=VIF_YC_DELAY_FILTER_L_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterL_VHF_H);//=VIF_GROUP_DELAY_FILTER_L_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterLL_VHF_H);//=VIF_PEAKING_FILTER_LL_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterLL_VHF_H);//=VIF_YC_DELAY_FILTER_LL_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterLL_VHF_H);//=VIF_GROUP_DELAY_FILTER_LL_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterMN_VHF_H);//=VIF_PEAKING_FILTER_MN_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterMN_VHF_H);//=VIF_YC_DELAY_FILTER_MN_VHF_H;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterMN_VHF_H);//=VIF_GROUP_DELAY_FILTER_MN_VHF_H;

    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterB_UHF);//=VIF_PEAKING_FILTER_B_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterB_UHF);//=VIF_YC_DELAY_FILTER_B_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterB_UHF);//=VIF_GROUP_DELAY_FILTER_B_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterGH_UHF);//=VIF_PEAKING_FILTER_GH_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterGH_UHF);//=VIF_YC_DELAY_FILTER_GH_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterGH_UHF);//=VIF_GROUP_DELAY_FILTER_GH_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterDK_UHF);//=VIF_PEAKING_FILTER_DK_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterDK_UHF);//=VIF_YC_DELAY_FILTER_DK_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterDK_UHF);//=VIF_GROUP_DELAY_FILTER_DK_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterI_UHF);//=VIF_PEAKING_FILTER_I_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterI_UHF);//=VIF_YC_DELAY_FILTER_I_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterI_UHF);//=VIF_GROUP_DELAY_FILTER_I_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterL_UHF);//=VIF_PEAKING_FILTER_L_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterL_UHF);//=VIF_YC_DELAY_FILTER_L_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterL_UHF);//=VIF_GROUP_DELAY_FILTER_L_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterLL_UHF);//=VIF_PEAKING_FILTER_LL_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterLL_UHF);//=VIF_YC_DELAY_FILTER_LL_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterLL_UHF);//=VIF_GROUP_DELAY_FILTER_LL_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifPeakingFilterMN_UHF);//=VIF_PEAKING_FILTER_MN_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifYcDelayFilterMN_UHF);//=VIF_YC_DELAY_FILTER_MN_UHF;
    printf("\r\n %x",(WORD)VIF_InitData.VifGroupDelayFilterMN_UHF);//=VIF_GROUP_DELAY_FILTER_MN_UHF;

    printf("\r\n %x",(WORD)VIF_InitData.ChinaDescramblerBox);// = CHINA_DESCRAMBLER_BOX;
    printf("\r\n %x",(WORD)VIF_InitData.VifDelayReduce);//= VIF_DELAY_REDUCE;
    printf("\r\n %x",(WORD)VIF_InitData.VifOverModulation);//=VIF_OVER_MODULATION;
    printf("\r\n %x",(WORD)VIF_InitData.VifFreqBand);// = FREQ_VHF_L; // should be changed when setting tuner freq
    printf("\r\n %x",(WORD)VIF_InitData.VifSos21FilterC0);//= VIF_SOS21_FILTER_C0;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos21FilterC1);//= VIF_SOS21_FILTER_C1;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos21FilterC2);//= VIF_SOS21_FILTER_C2;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos21FilterC3);//= VIF_SOS21_FILTER_C3;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos21FilterC4);//= VIF_SOS21_FILTER_C4;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos22FilterC0);//= VIF_SOS22_FILTER_C0;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos22FilterC1);//= VIF_SOS22_FILTER_C1;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos22FilterC2);//= VIF_SOS22_FILTER_C2;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos22FilterC3);//= VIF_SOS22_FILTER_C3;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos22FilterC4);//= VIF_SOS22_FILTER_C4;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos31FilterC0);//= VIF_SOS31_FILTER_C0;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos31FilterC1);//= VIF_SOS31_FILTER_C1;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos31FilterC2);//= VIF_SOS31_FILTER_C2;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos31FilterC3);//= VIF_SOS31_FILTER_C3;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos31FilterC4);//= VIF_SOS31_FILTER_C4;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos32FilterC0);//= VIF_SOS32_FILTER_C0;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos32FilterC1);//= VIF_SOS32_FILTER_C1;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos32FilterC2);//= VIF_SOS32_FILTER_C2;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos32FilterC3);//= VIF_SOS32_FILTER_C3;
    printf("\r\n %x",(WORD)VIF_InitData.VifSos32FilterC4);//= VIF_SOS32_FILTER_C4;
    printf("\r\n %x",(WORD)VIF_InitData.VifTunerType);
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrRate_B>>16)&0x0000FFFF));
    printf("%x",(WORD)(VIF_InitData.VifCrRate_B&0x0000FFFF));
    printf("\r\n %x",(WORD)VIF_InitData.VifCrInvert_B);
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrRate_GH>>16)&0x0000FFFF));
    printf("%x",(WORD)(VIF_InitData.VifCrRate_GH&0x0000FFFF));
    printf("\r\n %x",(WORD)VIF_InitData.VifCrInvert_GH);
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrRate_DK>>16)&0x0000FFFF));
    printf("%x",(WORD)(VIF_InitData.VifCrRate_DK&0x0000FFFF));
    printf("\r\n %x",(WORD)VIF_InitData.VifCrInvert_DK);
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrRate_I>>16)&0x0000FFFF));
    printf("%x",(WORD)(VIF_InitData.VifCrRate_I&0x0000FFFF));
    printf("\r\n %x",(WORD)VIF_InitData.VifCrInvert_I);
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrRate_L>>16)&0x0000FFFF));
    printf("%x",(WORD)(VIF_InitData.VifCrRate_L&0x0000FFFF));
    printf("\r\n %x",(WORD)VIF_InitData.VifCrInvert_L);
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrRate_LL>>16)&0x0000FFFF));
    printf("%x",(WORD)(VIF_InitData.VifCrRate_LL&0x0000FFFF));
    printf("\r\n %x",(WORD)VIF_InitData.VifCrInvert_LL);
    printf("\r\n %x",(WORD)((VIF_InitData.VifCrRate_MN>>16)&0x0000FFFF));
    printf("%x",(WORD)(VIF_InitData.VifCrRate_MN&0x0000FFFF));
    printf("\r\n %x",(WORD)VIF_InitData.VifCrInvert_MN);
    printf("\r\n=============End of VIF init para====================",0);
*/
    VIF_InitData.ChinaDescramblerBox    = 0;
    DRV_VIF_Init(&VIF_InitData, sizeof(VIFInitialIn));

#if (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER || FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER)
    DWORD u32VIF_TagcOdMode = 2;
    DRV_VIF_SetParameter(VIF_PARA_SET_TAGC_ODMODE, &u32VIF_TagcOdMode, sizeof(u32VIF_TagcOdMode));
#endif
}

void MDrv_VIF_Reset(void)
{
    DRV_VIF_Reset();
}

void MDrv_VIF_Handler(BOOL bAutoScan)
{
    //should be called in multitask
    DRV_VIF_Handler(bAutoScan);//auto/manual scan:true; play mode:false
}


#define IFDM_CHECK_INIT_DONE()  do { \
    if( s_IFDM_bInitDone == FALSE ) \
    {   \
        printf("\nError: VIF driver not inited!\n" );    \
        FATAL_ERROR_HAPPEN(FATAL_ERR_ID_VIF, __LINE__);     \
    }   \
} while(0)


void MDrv_IFDM_Init(void)
{
    MDrv_VIF_Init();

#if 0//ENABLE_VD_PACH_IN_CHINA // For what chip? ==> need check
    // For what chip?
    MDrv_WriteByte(0x112308, G_DESIGN_SETTING.stVDSetting.Vif_AGCREFNEGATIVE);
    MDrv_WriteByte(0x112222,0x96);
    MDrv_WriteByteMask(0x112220,G_DESIGN_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION<<1,BIT1);
#endif

    s_IFDM_bInitDone = TRUE;
}

void MDrv_IFDM_Reset(void)
{
    IFDM_CHECK_INIT_DONE();

    MDrv_VIF_Reset();
}

AFC MDrv_IFDM_GetFreqDev(void)
{
    #if 0
    return ifdmGetFreqDev();
    #else
    U8 u8Value;


    if( s_IFDM_bInitDone == FALSE )
    {
        printf("\nError: VIF driver not inited!\n" );
        FATAL_ERROR_HAPPEN(FATAL_ERR_ID_VIF, __LINE__);
        return E_AFC_OUT_OF_AFCWIN;
    }

    u8Value=DRV_VIF_Read_CR_LOCK_STATUS();
    if (!(u8Value&BIT0))
        return E_AFC_OUT_OF_AFCWIN;
    u8Value=DRV_VIF_Read_CR_FOE();//For Eris one byte, AFC_FOE=register address
    VIFDBG(printf("CR_FOE=%bx ",u8Value));

#if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)  //TN_FREQ_STEP
    switch(u8Value)
    {
    case 0x00:
    case 0x01:
        return E_AFC_PLUS_12p5KHz;//afcPLUS_12p5KHz;
    case 0x02:
        return E_AFC_PLUS_37p5KHz;//afcPLUS_37p5KHz;
    case 0x03:
    case 0x04:
        return E_AFC_PLUS_62p5KHz;//afcPLUS_62p5KHz;
    case 0x05:
        return E_AFC_PLUS_87p5KHz;//afcPLUS_87p5KHz;
    case 0x06:
    case 0x07:
        return E_AFC_PLUS_112p5KHz;//afcPLUS_112p5KHz;
    case 0x08:
        return E_AFC_PLUS_137p5KHz;//afcPLUS_137p5KHz;
    case 0x09:
    case 0x0A:
        return E_AFC_PLUS_162p5KHz;//afcPLUS_162p5KHz;
    case 0x0B:
    case 0x0C:
        return E_AFC_ABOVE_PLUS_187p5KHz;//afcABOVE_PLUS_187p5KHz;

    case 0xFF:
        return E_AFC_MINUS_12p5KHz;//afcMINUS_12p5KHz;
    case 0xFE:
        return E_AFC_MINUS_37p5KHz;//afcMINUS_37p5KHz;
    case 0xFD:
    case 0xFC:
        return E_AFC_MINUS_62p5KHz;//afcMINUS_62p5KHz;
    case 0xFB:
        return E_AFC_MINUS_87p5KHz;//afcMINUS_87p5KHz;
    case 0xFA:
    case 0xF9:
        return E_AFC_MINUS_112p5KHz;//afcMINUS_112p5KHz;
    case 0xF8:
        return E_AFC_MINUS_137p5KHz;//afcMINUS_137p5KHz;
    case 0xF7:
    case 0xF6:
        return E_AFC_MINUS_162p5KHz;//afcMINUS_162p5KHz;
    case 0xF5:
    case 0xF4:
        return E_AFC_BELOW_MINUS_187p5KHz;//afcBELOW_MINUS_187p5KHz;
    default:
        break;
    }
    if(u8Value >= 0x0C && u8Value <= 0x7F)
    {
        return E_AFC_ABOVE_PLUS_187p5KHz;//afcABOVE_PLUS_187p5KHz;
    }else{
        return E_AFC_BELOW_MINUS_187p5KHz;//afcBELOW_MINUS_187p5KHz;
    }
#elif (TN_FREQ_STEP == FREQ_STEP_50KHz) //TN_FREQ_STEP
    switch(u8Value)
    {
    case 0x00:
    case 0x01:
        return E_AFC_PLUS_12p5KHz;//afcPLUS_12p5KHz;
    case 0x02:
    case 0x03:
        return E_AFC_PLUS_37p5KHz;//afcPLUS_37p5KHz;
    case 0x04:
    case 0x05:
        return E_AFC_PLUS_62p5KHz;//afcPLUS_62p5KHz;
    case 0x06:
    case 0x07:
        return E_AFC_PLUS_87p5KHz;//afcPLUS_87p5KHz;
    case 0x08:
    case 0x09:
        return E_AFC_PLUS_112p5KHz;//afcPLUS_112p5KHz;
    case 0x0A:
    case 0x0B:
        return E_AFC_PLUS_137p5KHz;//afcPLUS_137p5KHz;
    case 0x0C:
    case 0x0D:
        return E_AFC_PLUS_162p5KHz;//afcPLUS_162p5KHz;
    case 0x0E:
    case 0x0F:
        return E_AFC_ABOVE_PLUS_187p5KHz;//afcABOVE_PLUS_187p5KHz;

    case 0xFF:
        return E_AFC_MINUS_12p5KHz;//afcMINUS_12p5KHz;
    case 0xFE:
    case 0xFD:
        return E_AFC_MINUS_37p5KHz;//afcMINUS_37p5KHz;
    case 0xFC:
    case 0xFB:
        return E_AFC_MINUS_62p5KHz;//afcMINUS_62p5KHz;
    case 0xFA:
    case 0xF9:
        return E_AFC_MINUS_87p5KHz;//afcMINUS_87p5KHz;
    case 0xF8:
    case 0xF7:
        return E_AFC_MINUS_112p5KHz;//afcMINUS_112p5KHz;
    case 0xF6:
    case 0xF5:
        return E_AFC_MINUS_137p5KHz;//afcMINUS_137p5KHz;
    case 0xF4:
    case 0xF3:
        return E_AFC_MINUS_162p5KHz;//afcMINUS_162p5KHz;
    case 0xF2:
    case 0xF1:
        return E_AFC_BELOW_MINUS_187p5KHz;//afcBELOW_MINUS_187p5KHz;
    default:
        break;
    }
    if(u8Value >= 0x0F && u8Value <= 0x7F)
    {
        return E_AFC_ABOVE_PLUS_187p5KHz;//afcABOVE_PLUS_187p5KHz;
    }else{
        return E_AFC_BELOW_MINUS_187p5KHz;//afcBELOW_MINUS_187p5KHz;
    }
#else//FREQ_STEP_31_25
    switch(u8Value)
    {
    case 0x00:
    case 0x01:
        return E_AFC_PLUS_12p5KHz;//afcPLUS_12p5KHz;
    case 0x02:
    case 0x03:
    case 0x04:
        return E_AFC_PLUS_37p5KHz;//afcPLUS_37p5KHz;
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x08:
        return E_AFC_PLUS_62p5KHz;//afcPLUS_62p5KHz;
    case 0x09:
    case 0x0A:
    case 0x0B:
        return E_AFC_PLUS_87p5KHz;//afcPLUS_87p5KHz;
    case 0x0C:
    case 0x0D:
    case 0x0E:
        return E_AFC_PLUS_112p5KHz;//afcPLUS_112p5KHz;
    case 0x0F:
    case 0x10:
    case 0x11:
        return E_AFC_PLUS_137p5KHz;//afcPLUS_137p5KHz;
    case 0x12:
    case 0x13:
    case 0x14:
        return E_AFC_PLUS_162p5KHz;//afcPLUS_162p5KHz;
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
        return E_AFC_ABOVE_PLUS_187p5KHz;//afcABOVE_PLUS_187p5KHz;

    case 0xFF:
        return E_AFC_MINUS_12p5KHz;//afcMINUS_12p5KHz;
    case 0xFE:
    case 0xFD:
    case 0xFC:
        return E_AFC_MINUS_37p5KHz;//afcMINUS_37p5KHz;
    case 0xFB:
    case 0xFA:
    case 0xF9:
    case 0xF8:
        return E_AFC_MINUS_62p5KHz;//afcMINUS_62p5KHz;
    case 0xF7:
    case 0xF6:
    case 0xF5:
        return E_AFC_MINUS_87p5KHz;//afcMINUS_87p5KHz;
    case 0xF4:
    case 0xF3:
    case 0xF2:
        return E_AFC_MINUS_112p5KHz;//afcMINUS_112p5KHz;
    case 0xF1:
    case 0xF0:
    case 0xEF:
        return E_AFC_MINUS_137p5KHz;//afcMINUS_137p5KHz;
    case 0xEE:
    case 0xED:
    case 0xEC:
        return E_AFC_MINUS_162p5KHz;//afcMINUS_162p5KHz;
    case 0xEB:
    case 0xEA:
    case 0xE9:
    case 0xE8:
        return E_AFC_BELOW_MINUS_187p5KHz;//afcBELOW_MINUS_187p5KHz;
    default:
        break;
    }
    if(u8Value >= 0x18 && u8Value <= 0x7F)
    {
        return afcABOVE_PLUS_187p5KHz;
    }else{
        return afcBELOW_MINUS_187p5KHz;
    }
#endif
    #endif
}

void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq)
{
    IFDM_CHECK_INIT_DONE();

    VIFDBG(printf("SetIF = %s(%u)\n", msVIF_Get_StdString(eIF_Freq), eIF_Freq) );

    m_eIF_Freq = eIF_Freq;

    //printf("MDrv_IFDM_SetIF: m_eIF_Freq=%u\n", m_eIF_Freq);

#if (  (NXP_TDA18273_TUNER==FRONTEND_TUNER_TYPE)  \
    || (NXP_TDA18274_TUNER==FRONTEND_TUNER_TYPE)  \
    || (FRONTEND_TUNER_TYPE==NUTUNE_FK1602_TUNER) \
    )
    switch (eIF_Freq)
    {
        case IF_FREQ_B:
            //printf("IF_FREQ_B\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03ba;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0409;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03be;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0405;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0192;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x065d;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03a6;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0409;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_G:
            //printf("IF_FREQ_G\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03b3;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0411;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03b8;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x040b;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x00dc;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x071b;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x039f;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0411;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_I:
            //printf("IF_FREQ_I\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03b3;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0411;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03be;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0405;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x00dc;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x071b;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x039f;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0411;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_DK:
            //printf("IF_FREQ_DK\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x0388;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0661;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0414;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x0381;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0661;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x041B;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x00C1;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0661;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x072A;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x0388;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0661;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0414;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L:
            //printf("IF_FREQ_L\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03c2;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0401;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03ba;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0409;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0164;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x068d;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03ad;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0401;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L_PRIME:
            //printf("IF_FREQ_L_PRIME\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x019d;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0649;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x01ed;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x05f3;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x0194;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0649;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_MN:
            // printf("IF_FREQ_MN\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03ba;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0409;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03be;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0405;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0210;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x05da;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03a6;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0409;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_J://not implement now
        default:
            break;
    }

#elif (FRONTEND_TUNER_TYPE == FRESCO_FM2150A_TUNER)

    switch (eIF_Freq)
    {
        case IF_FREQ_B:
            //printf("IF_FREQ_B\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03ba;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0409;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03be;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0405;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0192;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x065d;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03a6;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0409;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_G:
            //printf("IF_FREQ_G\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03b3;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0411;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03b8;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x040b;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x00dc;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x071b;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x039f;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0411;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_I:
            //printf("IF_FREQ_I\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03b3;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0411;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03be;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0405;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x00dc;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x071b;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x039f;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0411;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_DK:
            //printf("IF_FREQ_DK\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03c1;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0401;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03c2;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0400;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0157;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x069b;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03ad;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0401;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L:
            //printf("IF_FREQ_L\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03c2;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0401;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03ba;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0409;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0164;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x068d;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03ad;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0401;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L_PRIME:
            //printf("IF_FREQ_L_PRIME\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x019d;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0649;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x01ed;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x05f3;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x0194;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0649;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_MN:
            // printf("IF_FREQ_MN\n");
            DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03ba;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0409;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03be;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063c;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0405;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0210;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x05da;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03a6;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x064f;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0409;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_J://not implement now
        default:
            break;
    }

#elif (FRONTEND_TUNER_TYPE == SILICON_R620D_TUNER)

    switch (eIF_Freq)
    {
        case IF_FREQ_B:
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B6;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x040D;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03BD;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0406;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0170;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0678;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03B6;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x040D;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_G:
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B6;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x040D;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03BD;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0406;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0170;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0678;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03B6;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x040D;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_I:
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B1;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0412;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03BD;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0406;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x00D0;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0722;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03B1;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0412;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_DK:
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x0393;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0661;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0407;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x038F;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0661;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x040C;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0108;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0661;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x06DA;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x0393;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0661;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0407;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L:
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03D4;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0403;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03C9;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x040E;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0143;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x06B0;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03D4;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0403;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L_PRIME:
            DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x019D;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0652;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x01EF;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x05FC;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0000;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x019D;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0652;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_MN:
            DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03BF;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0404;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03C1;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0402;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0228;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x05B5;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03BF;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0404;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_J://not implement now
        default:
            break;
    }

#elif (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)

    switch (eIF_Freq)
    {
        case IF_FREQ_B:
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03A4;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0421;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x03AF;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0415;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x011B;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x06D3;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;

                sVIFSOS1112.Vif_SOS_12_C0 = 0x03A4;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0421;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_G:
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x038F;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0436;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x039E;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0427;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x004D;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x07AE;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;

                sVIFSOS1112.Vif_SOS_12_C0 = 0x038F;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0436;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_DK:
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
            VIFDBG(printf("VIF_InitData.VifTunerType=%bX\n",VIF_InitData.VifTunerType));
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B3;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0411;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x039E;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0427;
                VIFDBG(printf("sVIFNotchA1A2.Vif_N_A1_C0=%bX\n",sVIFNotchA1A2.Vif_N_A1_C0));
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x00D7;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x071B;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;

                sVIFSOS1112.Vif_SOS_12_C0 = 0x03B3;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0411;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_I:
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03A4;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0421;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B4;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0410;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x0092;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x0764;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;

                sVIFSOS1112.Vif_SOS_12_C0 = 0x03A4;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0421;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_L:
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B3;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0411;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x039E;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0427;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x00D7;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x071B;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;

                sVIFSOS1112.Vif_SOS_12_C0 = 0x03B3;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0411;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_L_PRIME:
            DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B3;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0411;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x039E;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0427;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x00D7;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x071B;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;

                sVIFSOS1112.Vif_SOS_12_C0 = 0x03B3;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0411;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_MN:
            DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            if(VIF_InitData.VifTunerType == 1)
            {
            #if(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER || FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
				// 0.6Mhz
				sVIFNotchA1A2.Vif_N_A1_C0 = 0x03A3;//0x03BF;
				sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;//0x063C;//
				sVIFNotchA1A2.Vif_N_A1_C2 = 0x0436;//0x0404;//
				sVIFNotchA1A2.Vif_N_A2_C0 = 0x03AD;//0x03C1;//
				sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;//0x063C;//
				sVIFNotchA1A2.Vif_N_A2_C2 = 0x042C;//0x0402;//
				DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2,&sVIFNotchA1A2,sizeof(sVIFNotchA1A2));
				sVIFSOS1112.Vif_SOS_11_C0 = 0x0164;//0x0228;//
				sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;//0x063C;//
				sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
				sVIFSOS1112.Vif_SOS_11_C3 = 0x068D;//0x05B5;//
				sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
				sVIFSOS1112.Vif_SOS_12_C0 = 0x03A3;//0x03BF;//
				sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;//0x063C;//
				sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
				sVIFSOS1112.Vif_SOS_12_C3 = 0x0436;//0x0404;//
				sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
				DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112,&sVIFSOS1112,sizeof(sVIFSOS1112));
            #else
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x038F;//0x03C0;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;//0x0628;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0436;//0x0418;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x0399;//0x03C6;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;//0x0628;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x042C;//0x0412;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x015D;//0x01C6;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;//0x0628;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;//0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x068D;//0x0627;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;//0x0200;
                sVIFSOS1112.Vif_SOS_12_C0 = 0x038F;//0x03C0;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;//0x0628;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;//0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0436;//0x0418;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;//0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            #endif
            #if 0 // CL.Yang: Already move to utopia, No need here!
                // BK1122 ==> VIF_DBB1
                // BK1123 ==> VIF_DBB2
                // BK1123_5E[5]=1
                MDrv_WriteByteMask(0x11235E,0x20,0x20);
                // BK1122_A6=  0x02FC-> 0x031C
                // BK1122_A8=  0x063C-> 0x0614
                // BK1122_AA=   0x04D4(no change)
                MDrv_WriteByte(0x1122A6, 0x1C);
                MDrv_WriteByte(0x1122A7, 0x03);
                MDrv_WriteByte(0x1122A8, 0x14);
                MDrv_WriteByte(0x1122A9, 0x06);
            #endif
            }
            break;

        case IF_FREQ_J://not implement now
        default:
            break;
    }

#elif(FRONTEND_TUNER_TYPE == SILAB_2190B_TUNER)
    switch(eIF_Freq)
    {
        case IF_FREQ_B:
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
           if(VIF_InitData.VifTunerType == 1)
            {
             sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
             sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
             sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B5;
             sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A2_C2 = 0x040E;
             DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
             sVIFSOS1112.Vif_SOS_11_C0 = 0x013C;
             sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_11_C3 = 0x06B0;
             sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
             sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
             sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
             DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;
        case IF_FREQ_G:
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            if(VIF_InitData.VifTunerType == 1)
            {
             sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
             sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
             sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B5;
             sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A2_C2 = 0x040E;
             DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
             sVIFSOS1112.Vif_SOS_11_C0 = 0x013C;
             sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_11_C3 = 0x06B0;
             sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
             sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
             sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
             DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
             }
            break;
        case IF_FREQ_DK:
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
             if(VIF_InitData.VifTunerType == 1)
            {
             sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
             sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
             sVIFNotchA1A2.Vif_N_A2_C0 = 0x0394;
             sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A2_C2 = 0x0432;
             DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
             sVIFSOS1112.Vif_SOS_11_C0 = 0x00B5;
             sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_11_C3 = 0x0740;
             sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
             sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
             sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
             DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;
        case IF_FREQ_I:
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
             if(VIF_InitData.VifTunerType == 1)
            {
             sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
             sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
             sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B9;
             sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A2_C2 = 0x040A;
             DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
             sVIFSOS1112.Vif_SOS_11_C0 = 0x00B5;
             sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_11_C3 = 0x0740;
             sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
             sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
             sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
             DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;
        case IF_FREQ_L:
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            if(VIF_InitData.VifTunerType == 1)
            {
             sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
             sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
             sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B2;
             sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
             sVIFNotchA1A2.Vif_N_A2_C2 = 0x0412;
             DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
             sVIFSOS1112.Vif_SOS_11_C0 = 0x01BC;
             sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_11_C3 = 0x0627;
             sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
             sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
             sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
             sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
             DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;
        case IF_FREQ_L_PRIME:
             DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            if(VIF_InitData.VifTunerType == 1)
            {
             sVIFNotchA1A2.Vif_N_A1_C0 = 0x03C0;
             sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
             sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
             sVIFNotchA1A2.Vif_N_A2_C0 = 0x03A7;
             sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
             sVIFNotchA1A2.Vif_N_A2_C2 = 0x0432;
             DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
             sVIFSOS1112.Vif_SOS_11_C0 = 0x00B9;
             sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
             sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_11_C3 = 0x0740;
             sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C0 = 0x03C0;
             sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
             sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
             sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
             sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
             DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;
        case IF_FREQ_MN:
             DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            if(VIF_InitData.VifTunerType == 1)
            {
             sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;//0x03C0;
             sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;//0x0628;
             sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;//0x0418;
             sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B2;//0x03C6;
             sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;//0x0628;
             sVIFNotchA1A2.Vif_N_A2_C2 = 0x0412;//0x0412;
             DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
             sVIFSOS1112.Vif_SOS_11_C0 = 0x01BC;//0x01C6;
             sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;//0x0628;
             sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;//0x0200;
             sVIFSOS1112.Vif_SOS_11_C3 = 0x0627;//0x0627;
             sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;//0x0200;
             sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;//0x03C0;
             sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;//0x0628;
             sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;//0x0200;
             sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;//0x0418;
             sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;//0x0200;
             DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));

              // BK1123_5E[5]=1
               MDrv_WriteByteMask(0x11235E,0x20,0x20);
              // BK1122_A6=  0x02FC-> 0x031C
              // BK1122_A8=  0x063C-> 0x0614
              // BK1122_AA=   0x04D4(no change)
               MDrv_WriteByte(0x1122A6, 0x1C);
               MDrv_WriteByte(0x1122A7, 0x03);
               MDrv_WriteByte(0x1122A8, 0x14);
               MDrv_WriteByte(0x1122A9, 0x06);
             }
            break;
        case IF_FREQ_J://not implement now
        default:
            break;
    }
#elif (FRONTEND_TUNER_TYPE == LG_G230D_TUNER)

    switch (eIF_Freq)
    {
        case IF_FREQ_B:
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B5;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x040E;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x013C;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x06B0;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_G:
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B5;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x040E;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x013C;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x06B0;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_DK:
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x0394;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0432;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x00B5;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x0740;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_I:
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B9;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x040A;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x00B5;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x0740;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_L:
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B2;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0412;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x01BC;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x0627;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_L_PRIME:
            DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03C0;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x03A7;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0432;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x00B9;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x0740;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C0 = 0x03C0;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            }
            break;

        case IF_FREQ_MN:
            DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            if(VIF_InitData.VifTunerType == 1)
            {
                sVIFNotchA1A2.Vif_N_A1_C0 = 0x03AC;//0x03C0;
                sVIFNotchA1A2.Vif_N_A1_C1 = 0x063C;//0x0628;
                sVIFNotchA1A2.Vif_N_A1_C2 = 0x0418;//0x0418;
                sVIFNotchA1A2.Vif_N_A2_C0 = 0x03B2;//0x03C6;
                sVIFNotchA1A2.Vif_N_A2_C1 = 0x063C;//0x0628;
                sVIFNotchA1A2.Vif_N_A2_C2 = 0x0412;//0x0412;
                DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
                sVIFSOS1112.Vif_SOS_11_C0 = 0x01BC;//0x01C6;
                sVIFSOS1112.Vif_SOS_11_C1 = 0x063C;//0x0628;
                sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;//0x0200;
                sVIFSOS1112.Vif_SOS_11_C3 = 0x0627;//0x0627;
                sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;//0x0200;
                sVIFSOS1112.Vif_SOS_12_C0 = 0x03AC;//0x03C0;
                sVIFSOS1112.Vif_SOS_12_C1 = 0x063C;//0x0628;
                sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;//0x0200;
                sVIFSOS1112.Vif_SOS_12_C3 = 0x0418;//0x0418;
                sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;//0x0200;
                DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));

            #if 0 // CL.Yang: Already move to utopia, No need here!
                // BK1122 ==> VIF_DBB1
                // BK1123 ==> VIF_DBB2
                // BK1123_5E[5]=1
                MDrv_WriteByteMask(0x11235E,0x20,0x20);
                // BK1122_A6=  0x02FC-> 0x031C
                // BK1122_A8=  0x063C-> 0x0614
                // BK1122_AA=   0x04D4(no change)
                MDrv_WriteByte(0x1122A6, 0x1C);
                MDrv_WriteByte(0x1122A7, 0x03);
                MDrv_WriteByte(0x1122A8, 0x14);
                MDrv_WriteByte(0x1122A9, 0x06);
            #endif
            }
            break;

        case IF_FREQ_J://not implement now
        default:
            break;
    }

#elif (FRONTEND_TUNER_TYPE == XC7000_TUNER)

    switch (eIF_Freq)
    {
        case IF_FREQ_B:
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x02B;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x07D3;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x0009;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x07F7;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0397;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0443;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x002B;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x07D3;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_G:
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x002B;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x07D3;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x0009;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x07F3;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0397;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0443;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x002B;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x07D3;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_I:
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x07E3;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x001E;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x0795;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x006F;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x037B;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0460;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x07E3;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x001E;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_DK:
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x079C;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0068;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x077A;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x008C;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x035A;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0482;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x079C;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0068;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L:
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x079C;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0068;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x07F9;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0007;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x035A;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0482;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x079C;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0068;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L_PRIME:
            DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x079C;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0068;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x07F9;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0007;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x035A;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0482;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x079C;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0068;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_MN:
            DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x00B9;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0740;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x009A;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0760;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x035A;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0482;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x00B9;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0740;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_J://not implement now
        default:
            break;
    }

#elif (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER)

    switch (eIF_Freq)
    {
        case IF_FREQ_B:
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B6;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0423;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03BE;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x041A;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x011A;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x06DA;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03B6;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0423;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_G:
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B6;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0423;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03BE;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x041A;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x008E;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x076C;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03B6;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0423;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_I:
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03B4;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0425;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03C6;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0412;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x0087;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0773;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03B4;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0425;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_DK:
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03C4;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0414;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03CA;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x040D;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x00CE;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x072A;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03C4;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0414;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L:
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03C4;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0414;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03AE;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x042B;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x00CE;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x072A;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03C4;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0414;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L_PRIME:
            DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x0128;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x06CC;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x017F;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x0671;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x03D2;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0405;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x0128;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x06CC;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_MN:
            DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            sVIFNotchA1A2.Vif_N_A1_C0 = 0x03C7;
            sVIFNotchA1A2.Vif_N_A1_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A1_C2 = 0x0411;
            sVIFNotchA1A2.Vif_N_A2_C0 = 0x03CC;
            sVIFNotchA1A2.Vif_N_A2_C1 = 0x0628;
            sVIFNotchA1A2.Vif_N_A2_C2 = 0x040B;
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = 0x01E5;
            sVIFSOS1112.Vif_SOS_11_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_11_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_11_C3 = 0x0606;
            sVIFSOS1112.Vif_SOS_11_C4 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C0 = 0x03C7;
            sVIFSOS1112.Vif_SOS_12_C1 = 0x0628;
            sVIFSOS1112.Vif_SOS_12_C2 = 0x0200;
            sVIFSOS1112.Vif_SOS_12_C3 = 0x0411;
            sVIFSOS1112.Vif_SOS_12_C4 = 0x0200;
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_J://not implement now
        default:
            break;
    }

#else

    switch (eIF_Freq)
    {
        case IF_FREQ_B:
            DRV_VIF_SetSoundSystem(VIF_SOUND_B);
            sVIFNotchA1A2.Vif_N_A1_C0 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[0];
            sVIFNotchA1A2.Vif_N_A1_C1 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[1];
            sVIFNotchA1A2.Vif_N_A1_C2 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[2];
            sVIFNotchA1A2.Vif_N_A2_C0 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[3];
            sVIFNotchA1A2.Vif_N_A2_C1 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[4];
            sVIFNotchA1A2.Vif_N_A2_C2 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[5];
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[6];
            sVIFSOS1112.Vif_SOS_11_C1 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[7];
            sVIFSOS1112.Vif_SOS_11_C2 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[8];
            sVIFSOS1112.Vif_SOS_11_C3 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[9];
            sVIFSOS1112.Vif_SOS_11_C4 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[10];
            sVIFSOS1112.Vif_SOS_12_C0 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[11];
            sVIFSOS1112.Vif_SOS_12_C1 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[12];
            sVIFSOS1112.Vif_SOS_12_C2 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[13];
            sVIFSOS1112.Vif_SOS_12_C3 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[14];
            sVIFSOS1112.Vif_SOS_12_C4 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[15];
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_G:
            DRV_VIF_SetSoundSystem(VIF_SOUND_GH);
            sVIFNotchA1A2.Vif_N_A1_C0 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[0];
            sVIFNotchA1A2.Vif_N_A1_C1 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[1];
            sVIFNotchA1A2.Vif_N_A1_C2 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[2];
            sVIFNotchA1A2.Vif_N_A2_C0 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[3];
            sVIFNotchA1A2.Vif_N_A2_C1 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[4];
            sVIFNotchA1A2.Vif_N_A2_C2 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[5];
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[6];
            sVIFSOS1112.Vif_SOS_11_C1 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[7];
            sVIFSOS1112.Vif_SOS_11_C2 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[8];
            sVIFSOS1112.Vif_SOS_11_C3 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[9];
            sVIFSOS1112.Vif_SOS_11_C4 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[10];
            sVIFSOS1112.Vif_SOS_12_C0 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[11];
            sVIFSOS1112.Vif_SOS_12_C1 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[12];
            sVIFSOS1112.Vif_SOS_12_C2 = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[13];
            sVIFSOS1112.Vif_SOS_12_C3 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[14];
            sVIFSOS1112.Vif_SOS_12_C4 = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[15];
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_I:
            DRV_VIF_SetSoundSystem(VIF_SOUND_I);
            sVIFNotchA1A2.Vif_N_A1_C0 = VIF_A1_A2_SOS11_SOS12_I[0];
            sVIFNotchA1A2.Vif_N_A1_C1 = VIF_A1_A2_SOS11_SOS12_I[1];
            sVIFNotchA1A2.Vif_N_A1_C2 = VIF_A1_A2_SOS11_SOS12_I[2];
            sVIFNotchA1A2.Vif_N_A2_C0 = VIF_A1_A2_SOS11_SOS12_I[3];
            sVIFNotchA1A2.Vif_N_A2_C1 = VIF_A1_A2_SOS11_SOS12_I[4];
            sVIFNotchA1A2.Vif_N_A2_C2 = VIF_A1_A2_SOS11_SOS12_I[5];
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = VIF_A1_A2_SOS11_SOS12_I[6];
            sVIFSOS1112.Vif_SOS_11_C1 = VIF_A1_A2_SOS11_SOS12_I[7];
            sVIFSOS1112.Vif_SOS_11_C2 = VIF_A1_A2_SOS11_SOS12_I[8];
            sVIFSOS1112.Vif_SOS_11_C3 = VIF_A1_A2_SOS11_SOS12_I[9];
            sVIFSOS1112.Vif_SOS_11_C4 = VIF_A1_A2_SOS11_SOS12_I[10];
            sVIFSOS1112.Vif_SOS_12_C0 = VIF_A1_A2_SOS11_SOS12_I[11];
            sVIFSOS1112.Vif_SOS_12_C1 = VIF_A1_A2_SOS11_SOS12_I[12];
            sVIFSOS1112.Vif_SOS_12_C2 = VIF_A1_A2_SOS11_SOS12_I[13];
            sVIFSOS1112.Vif_SOS_12_C3 = VIF_A1_A2_SOS11_SOS12_I[14];
            sVIFSOS1112.Vif_SOS_12_C4 = VIF_A1_A2_SOS11_SOS12_I[15];
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_DK:
            DRV_VIF_SetSoundSystem(VIF_SOUND_DK2);
            sVIFNotchA1A2.Vif_N_A1_C0 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[0];
            sVIFNotchA1A2.Vif_N_A1_C1 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[1];
            sVIFNotchA1A2.Vif_N_A1_C2 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[2];
            sVIFNotchA1A2.Vif_N_A2_C0 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[3];
            sVIFNotchA1A2.Vif_N_A2_C1 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[4];
            sVIFNotchA1A2.Vif_N_A2_C2 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[5];
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[6];
            sVIFSOS1112.Vif_SOS_11_C1 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[7];
            sVIFSOS1112.Vif_SOS_11_C2 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[8];
            sVIFSOS1112.Vif_SOS_11_C3 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[9];
            sVIFSOS1112.Vif_SOS_11_C4 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[10];
            sVIFSOS1112.Vif_SOS_12_C0 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[11];
            sVIFSOS1112.Vif_SOS_12_C1 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[12];
            sVIFSOS1112.Vif_SOS_12_C2 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[13];
            sVIFSOS1112.Vif_SOS_12_C3 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[14];
            sVIFSOS1112.Vif_SOS_12_C4 = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[15];
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L:
            DRV_VIF_SetSoundSystem(VIF_SOUND_L);
            sVIFNotchA1A2.Vif_N_A1_C0 = VIF_A1_A2_SOS11_SOS12_L[0];
            sVIFNotchA1A2.Vif_N_A1_C1 = VIF_A1_A2_SOS11_SOS12_L[1];
            sVIFNotchA1A2.Vif_N_A1_C2 = VIF_A1_A2_SOS11_SOS12_L[2];
            sVIFNotchA1A2.Vif_N_A2_C0 = VIF_A1_A2_SOS11_SOS12_L[3];
            sVIFNotchA1A2.Vif_N_A2_C1 = VIF_A1_A2_SOS11_SOS12_L[4];
            sVIFNotchA1A2.Vif_N_A2_C2 = VIF_A1_A2_SOS11_SOS12_L[5];
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = VIF_A1_A2_SOS11_SOS12_L[6];
            sVIFSOS1112.Vif_SOS_11_C1 = VIF_A1_A2_SOS11_SOS12_L[7];
            sVIFSOS1112.Vif_SOS_11_C2 = VIF_A1_A2_SOS11_SOS12_L[8];
            sVIFSOS1112.Vif_SOS_11_C3 = VIF_A1_A2_SOS11_SOS12_L[9];
            sVIFSOS1112.Vif_SOS_11_C4 = VIF_A1_A2_SOS11_SOS12_L[10];
            sVIFSOS1112.Vif_SOS_12_C0 = VIF_A1_A2_SOS11_SOS12_L[11];
            sVIFSOS1112.Vif_SOS_12_C1 = VIF_A1_A2_SOS11_SOS12_L[12];
            sVIFSOS1112.Vif_SOS_12_C2 = VIF_A1_A2_SOS11_SOS12_L[13];
            sVIFSOS1112.Vif_SOS_12_C3 = VIF_A1_A2_SOS11_SOS12_L[14];
            sVIFSOS1112.Vif_SOS_12_C4 = VIF_A1_A2_SOS11_SOS12_L[15];
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_L_PRIME:
            DRV_VIF_SetSoundSystem(VIF_SOUND_LL);
            sVIFNotchA1A2.Vif_N_A1_C0 = VIF_A1_A2_SOS11_SOS12_LP[0];
            sVIFNotchA1A2.Vif_N_A1_C1 = VIF_A1_A2_SOS11_SOS12_LP[1];
            sVIFNotchA1A2.Vif_N_A1_C2 = VIF_A1_A2_SOS11_SOS12_LP[2];
            sVIFNotchA1A2.Vif_N_A2_C0 = VIF_A1_A2_SOS11_SOS12_LP[3];
            sVIFNotchA1A2.Vif_N_A2_C1 = VIF_A1_A2_SOS11_SOS12_LP[4];
            sVIFNotchA1A2.Vif_N_A2_C2 = VIF_A1_A2_SOS11_SOS12_LP[5];
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = VIF_A1_A2_SOS11_SOS12_LP[6];
            sVIFSOS1112.Vif_SOS_11_C1 = VIF_A1_A2_SOS11_SOS12_LP[7];
            sVIFSOS1112.Vif_SOS_11_C2 = VIF_A1_A2_SOS11_SOS12_LP[8];
            sVIFSOS1112.Vif_SOS_11_C3 = VIF_A1_A2_SOS11_SOS12_LP[9];
            sVIFSOS1112.Vif_SOS_11_C4 = VIF_A1_A2_SOS11_SOS12_LP[10];
            sVIFSOS1112.Vif_SOS_12_C0 = VIF_A1_A2_SOS11_SOS12_LP[11];
            sVIFSOS1112.Vif_SOS_12_C1 = VIF_A1_A2_SOS11_SOS12_LP[12];
            sVIFSOS1112.Vif_SOS_12_C2 = VIF_A1_A2_SOS11_SOS12_LP[13];
            sVIFSOS1112.Vif_SOS_12_C3 = VIF_A1_A2_SOS11_SOS12_LP[14];
            sVIFSOS1112.Vif_SOS_12_C4 = VIF_A1_A2_SOS11_SOS12_LP[15];
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_MN:
            DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
            sVIFNotchA1A2.Vif_N_A1_C0 = VIF_A1_A2_SOS11_SOS12_MN[0];
            sVIFNotchA1A2.Vif_N_A1_C1 = VIF_A1_A2_SOS11_SOS12_MN[1];
            sVIFNotchA1A2.Vif_N_A1_C2 = VIF_A1_A2_SOS11_SOS12_MN[2];
            sVIFNotchA1A2.Vif_N_A2_C0 = VIF_A1_A2_SOS11_SOS12_MN[3];
            sVIFNotchA1A2.Vif_N_A2_C1 = VIF_A1_A2_SOS11_SOS12_MN[4];
            sVIFNotchA1A2.Vif_N_A2_C2 = VIF_A1_A2_SOS11_SOS12_MN[5];
            DRV_VIF_SetParameter(VIF_PARA_SET_NOTCH_A1A2, &sVIFNotchA1A2, sizeof(VIFNotchA1A2));
            sVIFSOS1112.Vif_SOS_11_C0 = VIF_A1_A2_SOS11_SOS12_MN[6];
            sVIFSOS1112.Vif_SOS_11_C1 = VIF_A1_A2_SOS11_SOS12_MN[7];
            sVIFSOS1112.Vif_SOS_11_C2 = VIF_A1_A2_SOS11_SOS12_MN[8];
            sVIFSOS1112.Vif_SOS_11_C3 = VIF_A1_A2_SOS11_SOS12_MN[9];
            sVIFSOS1112.Vif_SOS_11_C4 = VIF_A1_A2_SOS11_SOS12_MN[10];
            sVIFSOS1112.Vif_SOS_12_C0 = VIF_A1_A2_SOS11_SOS12_MN[11];
            sVIFSOS1112.Vif_SOS_12_C1 = VIF_A1_A2_SOS11_SOS12_MN[12];
            sVIFSOS1112.Vif_SOS_12_C2 = VIF_A1_A2_SOS11_SOS12_MN[13];
            sVIFSOS1112.Vif_SOS_12_C3 = VIF_A1_A2_SOS11_SOS12_MN[14];
            sVIFSOS1112.Vif_SOS_12_C4 = VIF_A1_A2_SOS11_SOS12_MN[15];
            DRV_VIF_SetParameter(VIF_PARA_SET_SOS_1112, &sVIFSOS1112, sizeof(VIFSOS1112));
            break;

        case IF_FREQ_J://not implement now
        default:
            break;
    }
#endif
}

void MDrv_IFDM_SetVifIfFreq(U16 u16IfFreq)
{
    //eIF_FREQ eIF_FreqTmp;
    IfFrequencyType eIF_FreqTmp;

    IFDM_CHECK_INIT_DONE();

    //printf("MDrv_IFDM_SetVifIfFreq(u16IfFreq=%u)\n", u16IfFreq);

    if ((u16IfFreq == 33950L) || (u16IfFreq == 33900L))
        eIF_FreqTmp=IF_FREQ_3395;   // SECAM-L'
    else if (u16IfFreq == 38000L)
        eIF_FreqTmp=IF_FREQ_3800;   // PAL
    else if (u16IfFreq == 38900L)
        eIF_FreqTmp=IF_FREQ_3890;   // PAL
    else if (u16IfFreq == 39500L)
        eIF_FreqTmp=IF_FREQ_3950;   // only for PAL-I
    else if (u16IfFreq == 45750L)
        eIF_FreqTmp=IF_FREQ_4575;   // NTSC-M/N
    else if (u16IfFreq == 58750L)
        eIF_FreqTmp=IF_FREQ_5875;   // NTSC-M/N
    else
        eIF_FreqTmp=IF_FREQ_3890;   // PAL

    //printf(" => eIF_FreqTmp=%u, DRV_VIF_SetIfFreq(%u)\n",eIF_FreqTmp);

    DRV_VIF_SetIfFreq(eIF_FreqTmp);

}

void MDrv_IFDM_UserSetIF(IF_FREQ eIF_Freq)
{
    VIFDBG( printf("UserSetIF = %s(%u)\n", msVIF_Get_StdString(eIF_Freq), eIF_Freq ); );
    m_eIF_Freq = eIF_Freq;
}

IF_FREQ MDrv_IFDM_GetIF(void)
{
    //printf("MDrv_IFDM_GetIF: m_eIF_Freq=%u\n", m_eIF_Freq);
    return m_eIF_Freq;
}

void MDrv_IFDM_BypassDBBAudioFilter(BOOL bEnable)
{
    IFDM_CHECK_INIT_DONE();

    DRV_VIF_BypassDBBAudioFilter(bEnable);
}

void MDrv_IFDM_SetFreqBand(RFBAND u8FreqBand)
{
    IFDM_CHECK_INIT_DONE();

    FrequencyBand freqBand;

    if (u8FreqBand==E_RFBAND_UHF)
        freqBand=FREQ_UHF;
    else if (u8FreqBand==E_RFBAND_VHF_HIGH)
        freqBand=FREQ_VHF_H;
    else
        freqBand=FREQ_VHF_L;

    DRV_VIF_SetFreqBand(freqBand);
}

void MDrv_IFDM_ShiftClk(BYTE VifShiftClk)
{
    IFDM_CHECK_INIT_DONE();

    DRV_VIF_ShiftClk(VifShiftClk);
}

BOOL MDrv_IFDM_GetInputLevelIndicator(void)
{
    if( s_IFDM_bInitDone == FALSE )
    {
        printf("\nError: VIF driver not inited!\n");
        FATAL_ERROR_HAPPEN(FATAL_ERR_ID_VIF, __LINE__);
        return FALSE;
    }

    return DRV_VIF_GetInputLevelIndicator();
}

BOOL MDrv_IFDM_SetParameter(VIF_PARA_GROUP paraGroup, void * pVIF_Para, DWORD u32DataLen)
{
    if( s_IFDM_bInitDone == FALSE )
    {
        printf("\nError: VIF driver not inited!\n");
        FATAL_ERROR_HAPPEN(FATAL_ERR_ID_VIF, __LINE__);
        return FALSE;
    }

    return DRV_VIF_SetParameter(paraGroup, pVIF_Para, u32DataLen);
}



