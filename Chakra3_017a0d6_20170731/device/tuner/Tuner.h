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
////////////////////////////////////////////////////////////////////////////////

#if !defined(__TUNER_H__)
#define __TUNER_H__

#include "Board.h"

#define FREQ_STEP_31_25KHz      0x00
#define FREQ_STEP_50KHz         0x01
#define FREQ_STEP_62_5KHz       0x02
#define FREQ_STEP_166_67KHz     0x03
#define FREQ_STEP_125KHz        0x04
#define FREQ_STEP_142_86KHz     0x05


#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
#define IF_FREQ_45_75                               0x01//IF_FREQ_MN
#define IF_FREQ_38_90                               0x02//IF_FREQ_B
#define IF_FREQ_38_00                               0x03//IF_FREQ_PAL_38
#elif (FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)
#define IF_FREQ_45_75                               0x01//IF_FREQ_MN
#define IF_FREQ_38_90                               0x02//IF_FREQ_B
#define IF_FREQ_38_00                               0x03//IF_FREQ_PAL_38
#elif (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
#define IF_FREQ_45_75          0x01//IF_FREQ_MN
#define IF_FREQ_38_90          0x02//IF_FREQ_B
#define IF_FREQ_38_00          0x03//IF_FREQ_PAL_38
#define IF_BASE_FREQ           IF_FREQ_38_90  //IF_FREQ_38_00  // IF_FREQ_38_90
#define VIF_VGA_MAXIMUM        0x3000
#define GAIN_DISTRIBUTION_THR  0x2000
#endif

typedef enum
{
    E_RFBAND_VHF_LOW,
    E_RFBAND_VHF_HIGH,
    E_RFBAND_UHF
} RFBAND;

typedef enum
{
    FREQSTEP_62_5KHz,
    FREQSTEP_50KHz,
    FREQSTEP_31_25KHz,
    FREQSTEP_166_67KHz
} FREQSTEP;

/// RF Channel bandwidth
#ifndef ENABLE_RF_CHANNEL_BANDWIDTH
#define ENABLE_RF_CHANNEL_BANDWIDTH RF_CHANNEL_BANDWIDTH
typedef enum 
{
    E_RF_CH_BAND_6MHz = 0x01,       ///< 6MHz
    E_RF_CH_BAND_7MHz = 0x02,       ///< 7MHz
    E_RF_CH_BAND_8MHz = 0x03,       ///< 8MHz
    E_RF_CH_BAND_INVALID            ///< Invalid
} RF_CHANNEL_BANDWIDTH;
#endif


typedef enum
{
    E_RF_CH_HP = 0x00,
    E_RF_CH_LP = 0x01
} RF_CHANNEL_HP_LP;
typedef enum
{
    IF_FREQ_INVALID,
    IF_FREQ_B,              // 38.90 MHz
    IF_FREQ_G,              // 38.90 MHz
    IF_FREQ_I,              // 38.90 MHz
    IF_FREQ_DK,             // 38.90 MHz
    IF_FREQ_L,              // 38.90 MHz
    IF_FREQ_L_PRIME,        // 33.90 MHz
    IF_FREQ_MN,             // 45.75 MHz
    IF_FREQ_J,              // 58.75 MHz
    IF_FREQ_PAL_38,         // 38.00 MHz
    IF_FREQ_MAX_IF_FREQ,
    IF_DIGITAL_MODE
} IF_FREQ;

typedef enum
{
    /// get frequency step
    E_TUNER_SUBCMD_GET_FREQ_STEP,
    /// get IF frequency
    E_TUNER_SUBCMD_GET_IF_FREQ,
    /// get L-prime IF frequency
    E_TUNER_SUBCMD_GET_L_PRIME_IF_FREQ,
    /// get VHF low, minimum frequency
    E_TUNER_SUBCMD_GET_VHF_LOWMIN_FREQ,
    /// get VHF low, maximum frequency
    E_TUNER_SUBCMD_GET_VHF_LOWMAX_FREQ,
    /// get VHF high, minimum frequency
    E_TUNER_SUBCMD_GET_VHF_HIGHMIN_FREQ,
    /// get VHF high, maximum frequency
    E_TUNER_SUBCMD_GET_VHF_HIGHMAX_FREQ,
    /// get UHF, minimum frequency
    E_TUNER_SUBCMD_GET_UHF_MIN_FREQ,
    /// get UHF, maximum frequency
    E_TUNER_SUBCMD_GET_UHF_MAX_FREQ,
    /// get vif tuner type
    E_TUNER_SUBCMD_GET_VIF_TUNER_TYPE,
    /// get vif parameter for RF/Silicon tuner
    E_TUNER_SUBCMD_GET_VIF_PARA,
    /// get DTV IF frequency
    E_TUNER_SUBCMD_GET_DTV_IF_FREQ,
    /// get IQ SWAP
    E_TUNER_SUBCMD_GET_IQ_SWAP,
    /// get RF Table
    E_TUNER_SUBCMD_GET_RF_TABLE,
    /// get RF Level
    E_TUNER_SUBCMD_GET_RF_LEVEL,
    /// get demod config
    E_TUNER_SUBCMD_GET_DEMOD_CONFIG,
    /// invalid
    E_TUNER_SUBCMD_INVALD
} EN_TUNER_SUBCOMMAND;

#if (FRONTEND_TUNER_TYPE == PHILIPS_FQD1216_TUNER)
#include "FQD1216.h"
#elif (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
#include "MSR1200.h"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G001D_TUNER)
#include "TDTC_G001D.h"
#elif (FRONTEND_TUNER_TYPE == XUGUANG_DDT8A1C_TUNER)
#include "DTT8A1C.h"
#elif (FRONTEND_TUNER_TYPE == XUGUANG_STM_6F_V236H_TUNER)
#include "STM_6F.h"
#elif (FRONTEND_TUNER_TYPE == XUGUANG_HFT_8B1_V116H_TUNER)
#include "HFT_8B1.h"
#elif(FRONTEND_TUNER_TYPE == PHILIPS_FQD1218_TUNER)
#include "FQD1218.h"
#elif((FRONTEND_TUNER_TYPE ==SHARP_VA1Y1ED_TUNER))
#include "VA1Y1ED.h"
#elif((FRONTEND_TUNER_TYPE ==SHARP_VA1T1ED_6060))
#include "VA1T1ED6060.h"
#elif (FRONTEND_TUNER_TYPE == NXP_TD1616EF_TUNER)
#include "TD1616EF_MK5.h"
#elif (FRONTEND_TUNER_TYPE == QINGJIA_DAI4W500G_TUNER)
#include "DAI4W500G.h"
#elif (FRONTEND_TUNER_TYPE == LG_TDCC_G031D_TUNER)
#include "TDCC_G031D.h"
#elif(FRONTEND_TUNER_TYPE ==PHILIPS_FQD1116_TUNER)
#include"FQD1116.h"
#elif(FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
#include"FQD1136.h"
#elif (FRONTEND_TUNER_TYPE == LG_TDFV_G135D_TUNER)
#include "TDFV_G135D.h"
#elif(FRONTEND_TUNER_TYPE ==PHILIPS_TDA1316_TUNER)
#include"TD1316.h"
#elif(FRONTEND_TUNER_TYPE == PHILIPS_TD1318AFLHP_3X_TUNER)
#include "TD1318aflhp_3x.h"
#elif(FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H)
#include "TDQ_6FT_W116H.h"
#elif(FRONTEND_TUNER_TYPE == SAMSUNG_DTOS40AMH201A_TUNER)
#include "DTOS40AMH201A.h"
#elif(FRONTEND_TUNER_TYPE == ALPS_TDQG4602A_TUNER)
#include"TDQG4602A.h"
#elif((FRONTEND_TUNER_TYPE ==SHARP_VA1G5BF2009_TUNER))
#include "VA1G5BF8010.h"
#elif((FRONTEND_TUNER_TYPE ==CH_TMI8_C22I1VH_TUNER))
#include "TMI8_C22I1VH.h"
#elif(FRONTEND_TUNER_TYPE == ALPS_TDQG9_601A_TUNER)
#include "TDQG9_601A.h"
#elif (FRONTEND_TUNER_TYPE == QINGJIA_DTZ0W302G_TUNER)
#include "DTZ0W302.h"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G501D_TUNER)
#include "TDTC_G501D.h"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G601D_TUNER)
#include "TDTC_G601D.h"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G311D_TUNER)
#include "TDTC_G311D.h"
#elif (FRONTEND_TUNER_TYPE == TCL_DT91WT_2_E_TUNER)
#include "TCL_DT91WT_2_E.h"
#elif(FRONTEND_TUNER_TYPE == QINGJIA_AFT7W006_TUNER)
#include "AFT7W006.h"
#elif (FRONTEND_TUNER_TYPE==SEC_DTOS403LH121A)
#include "DTOS403LH121A.h"
#elif (FRONTEND_TUNER_TYPE == XC5200_TUNER)
#include "XC5200.h"
#elif (FRONTEND_TUNER_TYPE == DMCT_6A_111_TUNER)
#include "DMCT_6A_111.h"
#elif (FRONTEND_TUNER_TYPE == SHARP_VA1E1CD2403_TUNER)
#include "VA1E1CD2403.h"
#elif (FRONTEND_TUNER_TYPE == SHARP_VA1E1BF1402_TUNER)
#include "VA1E1BF1402.h"
#elif (FRONTEND_TUNER_TYPE == TCL_DTC78WI_3E_TUNER)
#include "DTC78WI3E.h"
#elif (FRONTEND_TUNER_TYPE == XUGUANG_HFT_8B_115CW_TUNER)
#include "HFT_8B_115CW.h"
#elif (FRONTEND_TUNER_TYPE==SEC_DTOS403IR121B)
#include "DTOS403IR121B.h"
#elif (FRONTEND_TUNER_TYPE == LINGHUA_TDP_1H1_E_TUNER)
#include "LINGHUA_TDP_1H1_E.h"
#elif (FRONTEND_TUNER_TYPE==CHANGHONG_DTI1_E4I1VH)
#include "DTI1_E4I1VH.h"
#elif (FRONTEND_TUNER_TYPE==MSTAR_AVATAR2)
#include "MSTAR_AVATAR2.h"
#elif (FRONTEND_TUNER_TYPE==TCL_DT70WI_3R_TUNER)
#include "DT70WI_3R_E.h"
#elif (FRONTEND_TUNER_TYPE==CDT_9BT322_40_TUNER)
#include "CDT_9BT322_40.h"

#elif (FRONTEND_TUNER_TYPE== NXP_FH2608_TUNER)
#include "NXP_FH2608_TUNER.h"
#elif (FRONTEND_TUNER_TYPE== NXP_FH2603_TUNER)
#include "NXP_FH2603_TUNER.h"
#elif (FRONTEND_TUNER_TYPE== NXP_FH2112_TUNER)
#include "NXP_FH2112_TUNER.h"
#elif (FRONTEND_TUNER_TYPE== NXP_TH2603_TUNER)
#include "NXP_TH2603_TUNER.h"

#elif(FRONTEND_TUNER_TYPE== LG_TDTC_GX01D_GX71D_TUNER)
#include"TDTC_GX01D_GX71D.h"
#elif (FRONTEND_TUNER_TYPE == LG_TDTK_G732D_B)
#include"LG_TDTK_G732D_B.h"
#elif(FRONTEND_TUNER_TYPE== CDT_SFT338_40_TUNER)
#include"CDT_SFT338_40.h"
#elif (FRONTEND_TUNER_TYPE==TCL_F17CT_6N_E_TUNER)
#include "TCL_F17CT_6N_E.h"
#elif (FRONTEND_TUNER_TYPE==TCL_DT61WI_2R_E_TUNER)
#include "TCL_DT61WI_2R_E.h"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G901D_TUNER)
#include "TDTC_G901D.h"
#elif(FRONTEND_TUNER_TYPE==TCL_F20WT_3DD_E)
#include "TCL_F20WT_3DD_E.h"
#elif(FRONTEND_TUNER_TYPE == TCL_DT58WT_3RB_E_TUNER)
#include "TCL_DT58WT_3RB_E.h"
#elif(FRONTEND_TUNER_TYPE == QINGJIA_DTT9W303G_TUNER)
#include "DTT9W303G.h"
#elif(FRONTEND_TUNER_TYPE == NUTUNE_FI4801_TUNER)
#include "NUTUNE_FI4801.h"
#elif(FRONTEND_TUNER_TYPE==NXP_TDA18272_TUNER)
#include "NXP_TDA18272/tmNxTypes.h"
#include "NXP_TDA18272/tmCompId.h"
#include "NXP_TDA18272/tmFrontEnd.h"
#include "NXP_TDA18272/tmbslFrontEndTypes.h"
#include "NXP_TDA18272/tmsysFrontEndTypes.h"
#include "NXP_TDA18272/tmUnitParams.h"
#include "NXP_TDA18272/tmsysOM3869S.h"
#include "NXP_TDA18272/tmbslTDA18272.h"
#include "NXP_TDA18272/tmsysOM3869Slocal.h"
#include "NXP_TDA18272/tmddTDA182I2local.h"
#include "NXP_TDA18272/tmbslTDA182I2local.h"
#include "NXP_TDA18272/tmddTDA182I2Instance.h"
#include "NXP_TDA18272/tmbslTDA18272.h"
//#include "NXP_TDA18272/tmddTDA182I2.h"
#include "NXP_TDA18272/tmddTDA182I2_Advanced.h"
#include "NXP_TDA18272/tmsysOM3869SInstance.h"
#include "NXP_TDA18272.h"
#elif(FRONTEND_TUNER_TYPE == MxL_301RF_TUNER)
#include "MAXLINER_MxL301/mxl_common.h"
#include "MAXLINER_MxL301/mxL_user_define.h"
#include "MAXLINER_MxL301/mxl301rf.h"
#include "MAXLINER_MxL301/mxl_api.h"
#include "MAXLINER_MxL_301.h"
#elif(FRONTEND_TUNER_TYPE == NUTUNE_FT2131_TUNER)
#include "NUTUNE_FT2131.h"
#elif(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER)
#include "NXP_TDA18273/tmNxTypes.h"
#include "NXP_TDA18273/tmCompId.h"
#include "NXP_TDA18273/tmFrontEnd.h"
#include "NXP_TDA18273/tmbslFrontEndTypes.h"
#include "NXP_TDA18273/tmsysFrontEndTypes.h"
#include "NXP_TDA18273/tmUnitParams.h"
#include "NXP_TDA18273/tmsysOM3912.h"
#include "NXP_TDA18273/tmbslTDA18273.h"
#include "NXP_TDA18273/tmsysOM3912local.h"
#include "NXP_TDA18273/tmddTDA18273local.h"
#include "NXP_TDA18273/tmbslTDA18273local.h"
#include "NXP_TDA18273/tmddTDA18273Instance.h"
#include "NXP_TDA18273/tmbslTDA18273.h"
#include "NXP_TDA18273/tmddTDA18273.h"
#include "NXP_TDA18273/tmddTDA18273_Advanced.h"
#include "NXP_TDA18273/tmsysOM3912Instance.h"
#include "NUTUNE_FK1602.h"
#elif(FRONTEND_TUNER_TYPE == SAMSUNG_DTVS70CVH073A_TUNER)
#include "SAMSUNG_TDA18273/tmNxTypes.h"
#include "SAMSUNG_TDA18273/tmCompId.h"
#include "SAMSUNG_TDA18273/tmFrontEnd.h"
#include "SAMSUNG_TDA18273/tmbslFrontEndTypes.h"
#include "SAMSUNG_TDA18273/tmsysFrontEndTypes.h"
#include "SAMSUNG_TDA18273/tmUnitParams.h"
#include "SAMSUNG_TDA18273/tmsysOM3912.h"
#include "SAMSUNG_TDA18273/tmbslTDA18273.h"
#include "SAMSUNG_TDA18273/tmsysOM3912local.h"
#include "SAMSUNG_TDA18273/tmddTDA18273local.h"
#include "SAMSUNG_TDA18273/tmbslTDA18273local.h"
#include "SAMSUNG_TDA18273/tmddTDA18273Instance.h"
#include "SAMSUNG_TDA18273/tmbslTDA18273.h"
#include "SAMSUNG_TDA18273/tmddTDA18273.h"
#include "SAMSUNG_TDA18273/tmddTDA18273_Advanced.h"
#include "SAMSUNG_TDA18273/tmsysOM3912Instance.h"
#include "SAMSUNG_DTVS70CVH073A.h"
#elif(FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)
#include "MAXLINER_MxL601/MaxLinearDataTypes.h"
#include "MAXLINER_MxL601/MxL601_OEM_Drv.h"
#include "MAXLINER_MxL601/MxL601_TunerApi.h"
#include "MAXLINER_MxL601/MxL601_TunerCfg.h"
#include "MAXLINER_MxL601/MxL601_TunerSpurTable.h"
#include "MAXLINER_MxL601/MxL_Debug.h"
#include "MAXLINER_MxL_601.h"
#elif(FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)
#include "MAXLINER_MxL661/MaxLinearDataTypes.h"
#include "MAXLINER_MxL661/MxL661_OEM_Drv.h"
#include "MAXLINER_MxL661/MxL661_TunerApi.h"
#include "MAXLINER_MxL661/MxL661_TunerCfg.h"
#include "MAXLINER_MxL661/MxL661_TunerSpurTable.h"
#include "MAXLINER_MxL661/MxL_Debug.h"
#include "MAXLINER_MxL_661.h"
#elif(FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
#include "NXP_TDA18274/tmNxTypes.h"
#include "NXP_TDA18274/tmCompId.h"
#include "NXP_TDA18274/tmFrontEnd.h"
#include "NXP_TDA18274/tmbslFrontEndTypes.h"
#include "NXP_TDA18274/tmsysFrontEndTypes.h"
#include "NXP_TDA18274/tmUnitParams.h"
#include "NXP_TDA18274/tmbslTDA182I4.h"
#include "NXP_TDA18274/tmsysOM3912_18274.h"
#include "NUTUNE_FK1602.h"
#elif(FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER)
#include "R828.h"
#elif(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER ||FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
#include  "R840_842/R840_842.h"
#elif((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#include "SILAB_2158_A20.h"
#include "SILAB_2158_A20/Si2158_L1_API.h"
#elif(FRONTEND_TUNER_TYPE == SILAB_2190B_TUNER)
#include "SILAB_2190B.h"
#elif((FRONTEND_TUNER_TYPE == LG_G230D_TUNER))
#include "TDSY_G230D.h"
#elif((FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER))
#include "SONY_SUT_RE23x.h"
#elif((FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER))
#include "device_tuner_sony_sut_pex41.h"
#elif((FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER))
#include "NXP_TDA18275.h"
#elif((FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER))
#include "NXP_TDA182I5a.h"
#elif((FRONTEND_TUNER_TYPE == SILAB_2190_TUNER))
#include "SILAB_2190.h"
#elif((FRONTEND_TUNER_TYPE == SILAB_2157_TUNER))
#include "SILAB_2157.h"
#elif((FRONTEND_TUNER_TYPE == SILAB_2151_TUNER))
#include "SILAB_2151.h"
#elif(FRONTEND_TUNER_TYPE == NM_120V_TUNER)
#include "NMI_120/nmicfg.h"
#elif(FRONTEND_TUNER_TYPE == RDA5158_TUNER)
#include "RDA5158/rda5158_drv.h"
#include "RDA5158/rda5158_fw.h"
#include "RDA5158.h"
#elif(FRONTEND_TUNER_TYPE == SAMSUNG_SI2176_TUNER)
#include "SAMSUNG_Si2176/SemcoSi2176.h"
#include "SAMSUNG_Si2176/Si2176_Commands.h"
//#include "SAMSUNG_Si2176/Si2176_Firmware_2_2_build_1.h"
//#include "SAMSUNG_Si2176/Si2176_Firmware_3_0_B2A_3_Rom13.h"
//#include "SAMSUNG_Si2176/Si2176_Firmware_B_3_0.h"
#include "SAMSUNG_Si2176/Si2176_Generic_DTV_Demod.h"
//#include "SAMSUNG_Si2176/Si2176_Generic_Sound_Processor.h"
#include "SAMSUNG_Si2176/Si2176_L0_TV_Chassis.h"
#include "SAMSUNG_Si2176/Si2176_L1_API_TV_Chassis.h"
#include "SAMSUNG_Si2176/Si2176_L2_TV_Chassis.h"
#include "SAMSUNG_Si2176/Si2176_Properties.h"
#include "SAMSUNG_Si2176/Si2176_Typedefs.h"
//#include "SAMSUNG_Si2176/Si2176_Write_ATV_video_coeffs.h"
//#include "SAMSUNG_Si2176/Si2176_Write_DLIF_video_coeffs.h"
#include "SAMSUNG_Si2176/UserDefinedIIC.h"
#include "SAMSUNG_Si2176.h"
#endif

#if ENABLE_S2  //ohya++ at 20130802
#if(!BLOADER)
#if (FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2012 || FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2011)
#include "AVAILINK_AV2012/drvTuner_AV2012.h"
#elif ( FRONTEND_TUNER_S2_TYPE == SONY_SUT_PE232_DVBS_TUNER )
#include "device_tuner_sony_sut_pe232.h"
#elif ( FRONTEND_TUNER_S2_TYPE == RDA5815M_DVBS_TUNER )
#include "RDA5815M/RDA5815M.h"
#elif(FRONTEND_TUNER_S2_TYPE == RAFAEL_RT710_TUNER)
#include "RAFAEL_RT710/drvTuner_RT710.h"
#elif (FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2017)
#include "AVAILINK_AV2017/drvTuner_AV2017.h"
#endif
#endif
#endif

#ifndef TN_FREQ_STEP
  #if((FRONTEND_TUNER_TYPE ==SHARP_VA1G5BF2009_TUNER) || (FRONTEND_TUNER_TYPE == CH_TMI8_C22I1VH_TUNER)||(FRONTEND_TUNER_TYPE == NXP_TDA18273_TUNER))
    #define TN_FREQ_STEP                FREQ_STEP_50KHz
  #else
    #define TN_FREQ_STEP                FREQ_STEP_62_5KHz//FREQ_STEP_50KHz//FREQ_STEP_31_25KHz
  #endif
#endif


#ifdef ATSC_SYSTEM
    #define TUNER_IF_FREQ_KHz 45750L
    #define IF_BASE_FREQ                                 IF_FREQ_45_75
#else
 #if ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
  #if (TUNER_IF_FREQ_KHz == 38000L)
    #define IF_BASE_FREQ                                 IF_FREQ_38_00
  #elif (TUNER_IF_FREQ_KHz == 45750L)
    #define IF_BASE_FREQ                                 IF_FREQ_45_75
  #else  // for (TUNER_IF_FREQ_KHz == 38900L)
    #define IF_BASE_FREQ                                 IF_FREQ_38_90
  #endif
 #endif
#endif


void devDigitalTuner_Init(void);
void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth);
void devTunerSetFreq(U32 u32Freq);



#endif // #if !defined(__TUNER_H__)


