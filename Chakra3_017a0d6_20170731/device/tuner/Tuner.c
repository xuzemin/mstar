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

#include "Tuner.h"

#if (ENABLE_DTV == 0)
#include "drvIIC.h"
BOOLEAN devCOFDM_PassThroughI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    U16 U16SlaveID=u8SlaveID;

#ifdef USE_SEC_IIC
    U16SlaveID=(U16)((E_I2C_BUS_SYS2<<8)|u8SlaveID);
#endif

#if ( FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H          \
    ||FRONTEND_TUNER_TYPE == XUGUANG_STM_6F_V236H_TUNER     \
    ||FRONTEND_TUNER_TYPE == XUGUANG_HFT_8B1_V116H_TUNER    \
    ||FRONTEND_TUNER_TYPE == XUGUANG_HFT_8B_115CW_TUNER     \
    ||FRONTEND_TUNER_TYPE == LINGHUA_TDP_1H1_E_TUNER        \
    ||FRONTEND_TUNER_TYPE == TCL_F17CT_6N_E_TUNER             \
    ||FRONTEND_TUNER_TYPE ==TCL_F20WT_3DD_E)

    U16SlaveID |= (U16)((TUNER_IIC_BUS<<8)|u8SlaveID);

    if ( FALSE == MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) )
    {
        printf("devCOFDM_PassThroughI2C_WriteBytes Error--6 addr=%x \n", U16SlaveID);
        return FALSE;
    }
#else // (FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H)


    if ( FALSE == MDrv_IIC_WriteBytes((U16)(U16SlaveID|(E_I2C_BUS_DDCD0<<8)), u8AddrNum, paddr, u16size, pu8data) )
    {
        printf("devCOFDM_PassThroughI2C_WriteBytes Error \n");
        return FALSE;
    }
 #endif

    MsOS_DelayTask(5); //waiting for tuner write

    return TRUE;
}
#endif

#if (FRONTEND_TUNER_TYPE == PHILIPS_FQD1216_TUNER)
#include "FQD1216.c"
#elif (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
#include "MSR1200.c"
#elif (FRONTEND_TUNER_TYPE == LG_TDTK_G732D_B)
#include"LG_TDTK_G732D_B.c"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G001D_TUNER)
#include "TDTC_G001D.c"
#elif (FRONTEND_TUNER_TYPE == XUGUANG_DDT8A1C_TUNER)
#include "DTT8A1C.c"
#elif (FRONTEND_TUNER_TYPE == XUGUANG_STM_6F_V236H_TUNER)
#include "STM_6F.c"
#elif (FRONTEND_TUNER_TYPE == XUGUANG_HFT_8B1_V116H_TUNER)
#include"HFT_8B1.c"
#elif (FRONTEND_TUNER_TYPE == PHILIPS_FQD1218_TUNER)
#include"FQD1218.c"
#elif((FRONTEND_TUNER_TYPE ==SHARP_VA1Y1ED_TUNER))
#include "VA1Y1ED.c"
#elif((FRONTEND_TUNER_TYPE ==SHARP_VA1T1ED_6060))
#include "VA1T1ED6060.c"
#elif (FRONTEND_TUNER_TYPE == NXP_TD1616EF_TUNER)
#include "TD1616EF_MK5.c"
#elif (FRONTEND_TUNER_TYPE == QINGJIA_DAI4W500G_TUNER)
#include "DAI4W500G.c"
#elif (FRONTEND_TUNER_TYPE == LG_TDCC_G031D_TUNER)
#include "TDCC_G031D.c"
#elif(FRONTEND_TUNER_TYPE == PHILIPS_FQD1116_TUNER)
#include"FQD1116.c "
#elif(FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
#include"FQD1136.c "
#elif(FRONTEND_TUNER_TYPE == LG_TDFV_G135D_TUNER)
#include "TDFV_G135D.c"
#elif(FRONTEND_TUNER_TYPE == PHILIPS_TDA1316_TUNER)
#include"TD1316.c "
#elif(FRONTEND_TUNER_TYPE == PHILIPS_TD1318AFLHP_3X_TUNER)
#include "TD1318aflhp_3x.c"
#elif(FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H)
#include "TDQ_6FT_W116H.c"
#elif(FRONTEND_TUNER_TYPE == SAMSUNG_DTOS40AMH201A_TUNER)
#include "DTOS40AMH201A.c"
#elif(FRONTEND_TUNER_TYPE == ALPS_TDQG4602A_TUNER)
#include"TDQG4602A.c"
#elif((FRONTEND_TUNER_TYPE ==SHARP_VA1G5BF2009_TUNER))
#include "VA1G5BF8010.c"
#elif((FRONTEND_TUNER_TYPE ==CH_TMI8_C22I1VH_TUNER))
#include "TMI8_C22I1VH.c"
#elif(FRONTEND_TUNER_TYPE == ALPS_TDQG9_601A_TUNER)
#include "TDQG9_601A.c"
#elif (FRONTEND_TUNER_TYPE == QINGJIA_DTZ0W302G_TUNER)
#include "DTZ0W302.c"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G501D_TUNER)
#include "TDTC_G501D.c"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G601D_TUNER)
#include "TDTC_G601D.c"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G311D_TUNER)
#include "TDTC_G311D.c"
#elif (FRONTEND_TUNER_TYPE == TCL_DT91WT_2_E_TUNER)
#include "TCL_DT91WT_2_E.c"
#elif(FRONTEND_TUNER_TYPE == QINGJIA_AFT7W006_TUNER)
#include "AFT7W006.c"
#elif (FRONTEND_TUNER_TYPE==SEC_DTOS403LH121A)
#include "DTOS403LH121A.c"
#elif (FRONTEND_TUNER_TYPE == XC5200_TUNER)
#include "XC5200.c"
#elif (FRONTEND_TUNER_TYPE == DMCT_6A_111_TUNER)
#include "DMCT_6A_111.c"
#elif (FRONTEND_TUNER_TYPE == SHARP_VA1E1CD2403_TUNER)
#include "VA1E1CD2403.c"
#elif (FRONTEND_TUNER_TYPE == SHARP_VA1E1BF1402_TUNER)
#include "VA1E1BF1402.c"
#elif (FRONTEND_TUNER_TYPE == TCL_DTC78WI_3E_TUNER)
#include "DTC78WI3E.c"
#elif (FRONTEND_TUNER_TYPE == XUGUANG_HFT_8B_115CW_TUNER)
#include"HFT_8B_115CW.c"
#elif (FRONTEND_TUNER_TYPE==SEC_DTOS403IR121B)
#include "DTOS403IR121B.c"
#elif (FRONTEND_TUNER_TYPE == LINGHUA_TDP_1H1_E_TUNER)
#include "LINGHUA_TDP_1H1_E.c"
#elif (FRONTEND_TUNER_TYPE==CHANGHONG_DTI1_E4I1VH)
#include "DTI1_E4I1VH.c"
#elif (FRONTEND_TUNER_TYPE==MSTAR_AVATAR2)
#include "MSTAR_AVATAR2.c"
#elif (FRONTEND_TUNER_TYPE==TCL_DT70WI_3R_TUNER)
#include "DT70WI_3R_E.c"
#elif (FRONTEND_TUNER_TYPE==CDT_9BT322_40_TUNER)
#include "CDT_9BT322_40.c"

#elif (FRONTEND_TUNER_TYPE== NXP_FH2608_TUNER)
#include "NXP_FH2608_TUNER.c"
#elif (FRONTEND_TUNER_TYPE== NXP_FH2603_TUNER)
#include "NXP_FH2603_TUNER.c"
#elif (FRONTEND_TUNER_TYPE== NXP_FH2112_TUNER)
#include "NXP_FH2112_TUNER.c"
#elif (FRONTEND_TUNER_TYPE== NXP_TH2603_TUNER)
#include "NXP_TH2603_TUNER.c"

#elif(FRONTEND_TUNER_TYPE== LG_TDTC_GX01D_GX71D_TUNER)
#include"TDTC_GX01D_GX71D.c"
#elif(FRONTEND_TUNER_TYPE== CDT_SFT338_40_TUNER)
#include"CDT_SFT338_40.c"
#elif (FRONTEND_TUNER_TYPE==TCL_F17CT_6N_E_TUNER)
#include "TCL_F17CT_6N_E.c"
#elif (FRONTEND_TUNER_TYPE==TCL_DT61WI_2R_E_TUNER)
#include "TCL_DT61WI_2R_E.c"
#elif (FRONTEND_TUNER_TYPE == LG_TDTC_G901D_TUNER)
#include "TDTC_G901D.c"
#elif(FRONTEND_TUNER_TYPE==TCL_F20WT_3DD_E)
#include "TCL_F20WT_3DD_E.c"
#elif(FRONTEND_TUNER_TYPE == TCL_DT58WT_3RB_E_TUNER)
#include "TCL_DT58WT_3RB_E.c"
#elif(FRONTEND_TUNER_TYPE == QINGJIA_DTT9W303G_TUNER)
#include "DTT9W303G.c"
#elif(FRONTEND_TUNER_TYPE == NUTUNE_FI4801_TUNER)
#include "NUTUNE_FI4801.c"
#elif(FRONTEND_TUNER_TYPE == NXP_TDA18272_TUNER)
#include "NXP_TDA18272/tmddTDA182I2Instance.c"
#include "NXP_TDA18272/tmbslTDA182I2Instance.c"
#include "NXP_TDA18272/tmbslTDA182I2.c"
#include "NXP_TDA18272/tmddTDA182I2.c"
#include "NXP_TDA18272/tmsysOM3869SInstance.c"
#include "NXP_TDA18272/tmddTDA182I2_Advanced.c"
#include "NXP_TDA18272/tmsysOM3869S.c"
#include "NXP_TDA18272.c"
#elif(FRONTEND_TUNER_TYPE == MxL_301RF_TUNER)
#include "MAXLINER_MxL301/mxl_common.c"
#include "MAXLINER_MxL301/mxL_user_define.c"
#include "MAXLINER_MxL301/mxl301rf.c"
#include "MAXLINER_MxL301/mxl_api.c"
#include "MAXLINER_MxL_301.c"
#elif(FRONTEND_TUNER_TYPE == NUTUNE_FT2131_TUNER)
#include "NUTUNE_FT2131.c"
#elif(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER)
#include "NXP_TDA18273/tmddTDA18273Instance.c"
#include "NXP_TDA18273/tmbslTDA18273Instance.c"
#include "NXP_TDA18273/tmbslTDA18273.c"
#include "NXP_TDA18273/tmddTDA18273.c"
#include "NXP_TDA18273/tmsysOM3912Instance.c"
#include "NXP_TDA18273/tmddTDA18273_Advanced.c"
#include "NXP_TDA18273/tmsysOM3912.c"
#include "NUTUNE_FK1602.c"
#elif(FRONTEND_TUNER_TYPE == SAMSUNG_DTVS70CVH073A_TUNER)
#include "SAMSUNG_TDA18273/tmddTDA18273Instance.c"
#include "SAMSUNG_TDA18273/tmbslTDA18273Instance.c"
#include "SAMSUNG_TDA18273/tmbslTDA18273.c"
#include "SAMSUNG_TDA18273/tmddTDA18273.c"
#include "SAMSUNG_TDA18273/tmsysOM3912Instance.c"
#include "SAMSUNG_TDA18273/tmddTDA18273_Advanced.c"
#include "SAMSUNG_TDA18273/tmsysOM3912.c"
#include "SAMSUNG_DTVS70CVH073A.c"
#elif(FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
#include "NXP_TDA18274/tmbslTDA182I4_RegDef.c"
#include "NXP_TDA18274/tmbslTDA182I4_Instance.c"
#include "NXP_TDA18274/tmbslTDA182I4.c"
#include "NXP_TDA18274/tmsysOM3912_18274.c"
#include "NUTUNE_FK1602.c"
#elif(FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)
#include "MAXLINER_MxL601/MxL601_OEM_Drv.c"
#include "MAXLINER_MxL601/MxL601_TunerApi.c"
#include "MAXLINER_MxL601/MxL601_TunerCfg.c"
#include "MAXLINER_MxL601/MxL601_TunerSpurTable.c"
#include "MAXLINER_MxL_601.c"
#elif(FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)
#include "MAXLINER_MxL661/MxL661_OEM_Drv.c"
#include "MAXLINER_MxL661/MxL661_TunerApi.c"
#include "MAXLINER_MxL661/MxL661_TunerCfg.c"
#include "MAXLINER_MxL661/MxL661_TunerSpurTable.c"
#include "MAXLINER_MxL_661.c"
#elif(FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER)
#include "R828.c"
#elif(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER || FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
#include "R840_842/R840_842.c"
#elif((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#include "SILAB_2158_A20/Si2158_L1_Properties.c"
#include "SILAB_2158_A20/Si2158_L1_API.c"
#include "SILAB_2158_A20/Si2158_L1_Commands.c"
#include "SILAB_2158_A20/silabs_L0_TV_Chassis.c"
#include "SILAB_2158_A20/si2158_i2c_api.c"
#include "SILAB_2158_A20/Si2158_L2_API.c"
#include "SILAB_2158_A20/Si2158_Properties_Strings.c"
#include "SILAB_2158_A20.c"
#elif(FRONTEND_TUNER_TYPE == SILAB_2190B_TUNER)
#include "SILAB_2190B.c"
#elif((FRONTEND_TUNER_TYPE == LG_G230D_TUNER))
#include "TDSY_G230D/Si2158_Driver/Si2158_Commands.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_Properties.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_typedefs.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_Commands_Prototypes.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_L2_API.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_L1_API.h"
#include "TDSY_G230D/Si2158_Driver/Silabs_L0_Si2158_API.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_firmware_0_E_build_15.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_firmware_0_L_build_8.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_firmware_2_0_build_x.h"
#include "TDSY_G230D/Si2158_Driver/Si2158_L2_API.c"
#include "TDSY_G230D/Si2158_Driver/Si2158_L1_API.c"
#include "TDSY_G230D/Si2158_Driver/Si2158_L1_Commands.c"
#include "TDSY_G230D/Si2158_Driver/Si2158_L1_Properties.c"
#include "TDSY_G230D/Si2158_Driver/Silabs_L0_Si2158_API.c"
#include "TDSY_G230D/Si2158_Driver/Si2158_Properties_Strings.c"
#include "TDSY_G230D.c"
#elif((FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER))
#include "SONY_SUT_RE23x.c"
#elif(FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER)
#include "device_tuner_sony_sut_pex41.c"
#elif((FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER))
#include "NXP_TDA18275.c"
#elif((FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER))
#include "NXP_TDA182I5a.c"
#elif(FRONTEND_TUNER_TYPE == SAMSUNG_SI2176_TUNER)
#include "SAMSUNG_Si2176/SemcoSi2176.c"
#include "SAMSUNG_Si2176/Si2176_Generic_DTV_Demod.c"
//#include "SAMSUNG_Si2176/Si2176_Generic_Sound_Processor.c"
#include "SAMSUNG_Si2176/Si2176_L0_TV_Chassis.c"
#include "SAMSUNG_Si2176/Si2176_L1_API_TV_Chassis.c"
#include "SAMSUNG_Si2176/Si2176_L1_Commands.c"
#include "SAMSUNG_Si2176/Si2176_L1_Properties.c"
#include "SAMSUNG_Si2176/Si2176_L2_TV_Chassis.c"
#include "SAMSUNG_Si2176/UserDefinedIIC.c"
#include "SAMSUNG_Si2176.c"
#elif((FRONTEND_TUNER_TYPE == SILAB_2190_TUNER))
#include "SILAB_2190.c"
#elif((FRONTEND_TUNER_TYPE == SILAB_2157_TUNER))
#include "SILAB_2157.c"
#elif((FRONTEND_TUNER_TYPE == SILAB_2151_TUNER))
#include "SILAB_2151.c"
#elif(FRONTEND_TUNER_TYPE == NM_120V_TUNER)
#include "NMI_120/nmicfg.c"
#include "NMI_120/nmitnr.c"
#elif(FRONTEND_TUNER_TYPE == RDA5158_TUNER)
#include "RDA5158/rda5158_drv.c"
#include "RDA5158.c"
#endif
#if(!BLOADER)
 #if ENABLE_S2
 #if (FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2012 || FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2011)
 #include "AVAILINK_AV2012/drvTuner_AV2012.c"
 #elif ( FRONTEND_TUNER_S2_TYPE == SONY_SUT_PE232_DVBS_TUNER )
 #include "device_tuner_sony_sut_pe232.c"
 #elif ( FRONTEND_TUNER_S2_TYPE == RDA5815M_DVBS_TUNER )
 #include "RDA5815M/RDA5815M.c"
 #elif(FRONTEND_TUNER_S2_TYPE ==RAFAEL_RT710_TUNER)
 #include "RAFAEL_RT710/drvTuner_RT710.c"
 #elif (FRONTEND_TUNER_S2_TYPE == AVAILINK_AV2017)
 #include "AVAILINK_AV2017/drvTuner_AV2017.c"
 #endif
 #endif
#endif
