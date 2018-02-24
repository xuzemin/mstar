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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file INTERN_DVBT.c
/// @brief INTERN_DVBT DVBT
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define _INTERN_DVBT_C_
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "debug.h"

#include "MsTypes.h"
#include "drvBDMA.h"
#include "drvIIC.h"
#include "drvDMD_common.h"
#include "msAPI_Tuner.h"
#include "msAPI_MIU.h"
#include "BinInfo.h"
#include "halVif.h"

#include "INTERN_DVBT.h"
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
#include "InfoBlock.h"
#endif


#include "drvMMIO.h"
#include "drvAVD.h"
#include <math.h>

#define TEST_EMBEDED_DEMOD 0

#define EMBEDED_DEMOD_DELAY_TIME 0xff

#if DTV_LOW_IF_FREQ
#if( (FRONTEND_TUNER_TYPE==NXP_TDA18272_TUNER)  \
  || (FRONTEND_TUNER_TYPE==NXP_TDA18273_TUNER)  \
  || (NXP_TDA18274_TUNER==FRONTEND_TUNER_TYPE)  \
  || (FRONTEND_TUNER_TYPE==NUTUNE_FK1602_TUNER) \
  || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER )  \
 )
#define DTV_IF_8M_FREQ  4000L
#define DTV_IF_7M_FREQ  3500L
#define DTV_IF_6M_FREQ  3000L
#elif(FRONTEND_TUNER_TYPE==MxL_301RF_TUNER)
#define DTV_IF_8M_FREQ  6000L
#define DTV_IF_7M_FREQ  6500L
#define DTV_IF_6M_FREQ  6000L
#elif(FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER)
#define DTV_IF_8M_FREQ  4570L
#define DTV_IF_7M_FREQ  4070L
#define DTV_IF_6M_FREQ  3570L
#elif((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)|| (FRONTEND_TUNER_TYPE == LG_G230D_TUNER))
#define DTV_IF_8M_FREQ  5000L//SI2158 IF is set to 5Mhz
#define DTV_IF_7M_FREQ  5000L
#define DTV_IF_6M_FREQ  5000L
#else
#define DTV_IF_8M_FREQ  4000L
#define DTV_IF_7M_FREQ  3500L
#define DTV_IF_6M_FREQ  3000L
#endif
#else
#define DTV_IF_8M_FREQ  36167L
#endif
//U8 load_data_variable=1;
//-----------------------------------------------------------------------

#if(INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_BIN)

    #define BIN_ID_INTERN_DVBT_DEMOD BIN_ID_INTERN_DVBT

#elif( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )

 #if  (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)  || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)  || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)

// This define was moved to INTERN_DVBT.h
//  #define INTERN_DVBT_LOAD_FW_FROM_CODE_MEMORY

    #define MBRegBase   0x112600 //Demod MailBox
    #define VDMcuBase   0x103400 //DmdMCU51 (40-4F)
    #define DMDMcuBase  0x103480

    #define TOP_REG_BASE  0x2000
    #define TDP_REG_BASE  0x2100
    #define FDP_REG_BASE  0x2200
    #define FEC_REG_BASE  0x2300
    #define TDE_REG_BASE  0x2400
    #define BACKEND_REG_BASE 0x1f00

    #define REG_CMD_CTRL    MBRegBase + 0x1C
    #define REG_DTA_CTRL    MBRegBase + 0x1D
    #define REG_CMD_ADDR    MBRegBase + 0x1E
    #define REG_CMD_DATA    MBRegBase + 0x1F

    #define INTERN_DVBT_DBG_S0_ENTRY          TOP_REG_BASE + 0x73
    #define INTERN_DVBT_DBG_S8_TPS_INVALID    TOP_REG_BASE + 0x74
    #define INTERN_DVBT_DBG_S10_TPS_INVALID   TOP_REG_BASE + 0x75
    #define INTERN_DVBT_DBG_S10_PSYNC_FAIL    TOP_REG_BASE + 0x76

  #endif

#endif

#define INTERN_DVBT_Write_MBX_Byte(x,y)     MDrv_WriteByte(x,y)
#define INTERN_DVBT_Read_MBX_Byte(x)        MDrv_ReadByte(x)
#define INTERN_DVBT_Write_VD_DMD_Byte(x,y)  MDrv_WriteByte(x,y)
#define INTERN_DVBT_Read_VD_DMD_Byte(x)       MDrv_ReadByte(x)

#define _REG_START      REG_CMD_CTRL
#define _REG_END        REG_CMD_CTRL
#define _REG_DRQ        REG_DTA_CTRL
#define _REG_FSM        REG_CMD_CTRL
#define _REG_ERR        REG_DTA_CTRL

#define _BIT_START      BIT1
#define _BIT_END        BIT0
#define _BIT_DRQ        BIT0
#define _BIT_FSM        BIT3
#define _BIT_ERR        BIT7



#if  ENABLE_SCAN_ONELINE_MSG
#define DBG_INTERN_DVBT_ONELINE(x)  //x
#else
#define DBG_INTERN_DVBT_ONELINE(x) //  x
#endif

#define DBG_INTERN_DVBT(x)   //x
#define DBG_GET_SIGNAL(x)   //x
#define DBG_DUMP_LOAD_DSP_TIME 0

#define INTERN_DVBT_TS_SERIAL_INVERSION        0

#ifndef INTERN_DVBT_TS_PARALLEL_INVERSION
#define INTERN_DVBT_TS_PARALLEL_INVERSION      1
#endif
#define INTERN_DVBT_DTV_DRIVING_LEVEL          1

#if ENABLE_SCAN_ONELINE_MSG     // this option is for easy debugging missing channel
#define INTERN_DVBT_INTERNAL_DEBUG             0
#else
#define INTERN_DVBT_INTERNAL_DEBUG             0
#endif

#if(FRONTEND_TUNER_TYPE==MSTAR_AVATAR2)
#define TUNER_VPP  2
#define IF_AGC_VPP 2
#elif (FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER)
#define TUNER_VPP  2
//<<--M-- SMC  20110423
#define IF_AGC_VPP 3
//SMC  20110423 --A-->>
#else
#define TUNER_VPP  1
#define IF_AGC_VPP 2
#endif

#if (TUNER_VPP == 1)
#define ADC_CH_I_PGA_GAIN_CTRL      0x5 // gain = 14.0/5.0
#elif (TUNER_VPP == 2)  // For Avatar tuner,ADC peak to peak voltage is 1 V
#define ADC_CH_I_PGA_GAIN_CTRL      0x9 // gain = 14.0/14.0
#endif



#if ( FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD       \
    || FRONTEND_DEMOD_DVBT_TYPE == ALTOBEAM_884X             \
    || FRONTEND_DEMOD_DVBT_TYPE == LEGEND_9x_DEMOD			\
    )
//-----------------------------------------------------------------------
/****************************************************************
*Local Variables                                                *
****************************************************************/
static BOOLEAN FECLock=0;
U8 LoadDspStatus = 0xff;

//#ifdef INTERN_DVBT_LOAD_FW_FROM_CODE_MEMORY
#if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )
code U8 INTERN_DVBT_table[] = {

  #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER))
   #if ((VIF_SAW_ARCH == 3) || (VIF_SAW_ARCH == 5)) // No Saw (VIF / DIF)
    #include "INTERN_DVBT_demod_EULER_Sawless.dat"
   #else
    #include "INTERN_DVBT_demod_EULER.dat"
   #endif

  #elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)
   #if ((VIF_SAW_ARCH == 3) || (VIF_SAW_ARCH == 5)) // No Saw (VIF / DIF)
    #include "INTERN_DVBT_demod_EMERALD_Sawless.dat"
   #else
    #include "INTERN_DVBT_demod_EMERALD.dat"
   #endif

  #else
    #error "Unsupport"

  #endif
};
#endif

static void INTERN_DVBT_Delayms(U32 delay_ms)
{
    MsOS_DelayTask(delay_ms);
}

void INTERN_DVBT_InitClkgen(void)
{
#if(  (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)|| \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)   \
     )
    /************************************************************************
     * T10 U01
     * This bit0 is mux for DMD muc and HK,
     * bit0: 0:HK can rw bank 0x1120, 1: DMD mcu can rw bank 0x1120;
     ************************************************************************/
    INTERN_DVBT_Write_VD_DMD_Byte(0x101E39, 0x00); //mux from DMD MCU to HK.
#endif


#if   (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)|| \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

    U8 tmp = 0x00;
    //------------------- initial by DMD START---------------------------
     INTERN_DVBT_Write_VD_DMD_Byte(0x112002, 0x52);                            // wreg vdbank_DEMOD_0+0x01 0052
     INTERN_DVBT_Write_VD_DMD_Byte(0x112003, 0x00);                            // Release Ana misc resest
     INTERN_DVBT_Write_VD_DMD_Byte(0x112060, 0x00);                            // ADC sign bit
     INTERN_DVBT_Write_VD_DMD_Byte(0x112061, 0x00);
     INTERN_DVBT_Write_VD_DMD_Byte(0x112064, 0x00);                            // ADC I channel offset // wreg vdbank_DEMOD_0+0x32 0c00
     INTERN_DVBT_Write_VD_DMD_Byte(0x112065, 0x0c);
     INTERN_DVBT_Write_VD_DMD_Byte(0x112066, 0x00);                            // ADC Q channel offset
     INTERN_DVBT_Write_VD_DMD_Byte(0x112067, 0x0c);
     // ---------------------------------------
     // enable ADC related parameter.
     INTERN_DVBT_Write_VD_DMD_Byte(0x11286a, 0x04);                            // wreg vdbank_DMD_ANA_MISC+0x35 0x1e04
     INTERN_DVBT_Write_VD_DMD_Byte(0x11286b, 0x06);                            // [ANA_MPLL_ICTRL]
     INTERN_DVBT_Delayms(2);
     INTERN_DVBT_Write_VD_DMD_Byte(0x112868, 0x00);                            // Set enable ADC clock [ANA_PWDN_ADCI]
     INTERN_DVBT_Write_VD_DMD_Byte(0x112869, 0x00);                            // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000
     INTERN_DVBT_Delayms(2);
     // ---------------------------------------------------------------------
     // DVBT , DVBC Clock Setting
     // ---------------------------------------------------------------------
     INTERN_DVBT_Write_VD_DMD_Byte(0x112866, 0x00);                            // Set MPLL_LOOP_DIV_FIRST and SECOND
     INTERN_DVBT_Write_VD_DMD_Byte(0x112867, 0x24);                            // [ANA_MPLL_LOOP_DIV_FIRST]
     INTERN_DVBT_Write_VD_DMD_Byte(0x112860, 0x01);                            // Set MPLL_ADC_DIV_SEL [ANA_MPLL_CLK_DP_PD]
     INTERN_DVBT_Write_VD_DMD_Byte(0x112861, 0x13);                            // wreg vdbank_DMD_ANA_MISC+0x30 0x1300
     INTERN_DVBT_Write_VD_DMD_Byte(0x112802, 0x40);                            // Set IMUXS QMUXS [ANA_ADC_PWDNI]
    #if (VIF_SAW_ARCH!=4)
    INTERN_DVBT_Write_VD_DMD_Byte(0x112803, 0x04);
    #else
    INTERN_DVBT_Write_VD_DMD_Byte(0x112803, 0x12);
    #endif/*
#if(FRONTEND_TUNER_TYPE!=MSTAR_AVATAR2)
     INTERN_DVBT_Write_VD_DMD_Byte(0x112816, 0x05);                            // Set enable ADC clock [ANA_PWDN_ADCI]
#endif
*/
     INTERN_DVBT_Write_VD_DMD_Byte(0x112817, 0x05);                            // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x112818, 0x03);                            // Disable PWDN_REF [ANA_VCLP]
     INTERN_DVBT_Write_VD_DMD_Byte(0x112818, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x112819, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x112840, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x112841, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x11286c, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x1120A0, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x1120A1, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000

     //------------------- initial by DMD END-----------------------------
    MDrv_WriteByte(0x10331E, 0x10);         // reg_ckg_vdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz
    // reg_ckg_dmdmcu@0x0f[4:0] (Enable DMD MCU clock and speed select)
    // [4:2] 0(172MHz),1(160MHz),2(144MHz),3(123MHz),4(108MHz),5(mem_clk),6(mem_clk/2),7(XTAL)  @
    MDrv_WriteByte(0x103480, 0x00);
    // reg_ckg_dvbtc_adc@0x0a[3:0] (Enable clk_adcd_p at adcd_sync module)
    MDrv_WriteByte(0x103314, 0x00);
    // reg_ckg_atsc_adcd_sync@0x05[3:0] Enable clk_atsc_adcd_sync(adcd_sync module) =ADC Clock.
    MDrv_WriteByte(0x111f0a, 0x00);
    MDrv_WriteByte(0x111f0b, 0x00);
    // reg_ckg_atsc200_ph3@0x01[11:8]  24*29/2/2=174MHz
    // reg_ckg_atsc200_ph1@0x01[3:0]    24*29/2/2=174MHz + 900 shift
    MDrv_WriteByte(0x111f02, 0x01);
    MDrv_WriteByte(0x111f03, 0x01);
    // reg_ckg_atsc25@0x02[11:8]  24*29/2/7/2=24.85MHz
    // reg_ckg_atsc50@0x02[3:0]  24*29/2/7=49.7MHz
    MDrv_WriteByte(0x111f04, 0x01);
    MDrv_WriteByte(0x111f05, 0x01);
    // reg_ckg_atsc_ce25@0x03[11:8]  24*29/2/16=21.75MHz
    // reg_ckg_atsc_eq25@0x03[3:0]  24*29/2/2/8=21.75MHz
    MDrv_WriteByte(0x111f06, 0x01);
    MDrv_WriteByte(0x111f07, 0x01);
    // reg_ckg_dvbtc_inner2x@0x06[11:8] (DVBT Only !)
    // reg_ckg_dvbtc_inner1x@0x06[3:0] (DVBT Only !)
    MDrv_WriteByte(0x111f0c, 0x00);
    MDrv_WriteByte(0x111f0d, 0x00);
    // reg_ckg_dvbtc_inner4x@0x07[3:0] (DVBT Only !)
    MDrv_WriteByte(0x111f0e, 0x00);
    // reg_ckg_dvbtc_outer2x@0x08[11:8] (DVBT Only !)
    // reg_ckg_dvbtc_outer1x@0x08[3:0] (DVBT Only!)
    MDrv_WriteByte(0x111f10, 0x00);
    MDrv_WriteByte(0x111f11, 0x00);
    // reg_ckg_dvbtc_outer2x_c@0x09[3:0]
    MDrv_WriteByte(0x111f12, 0x00);
    // reg_ckg_dvbtc_innc@0x0a[11:8] (DVBC only !)
    MDrv_WriteByte(0x111f15, 0x01);
    // reg_ckg_dvbtc_eq8x@0x0b[11:8]  (DVBC only!)
    // reg_ckg_dvbtc_eq@0x0b[3:0] (DVBC Only !)
    MDrv_WriteByte(0x111f16, 0x01);
    MDrv_WriteByte(0x111f17, 0x01);
    // reg_ckg_dvbtc_sram3@0x0c[13:12]
    // reg_ckg_dvbtc_sram2@0x0c[9:8]
    // reg_ckg_dvbtc_sram1@0x0c[5:4]
    // reg_ckg_dvbtc_sram0@0x0c[1:0]
    MDrv_WriteByte(0x111f18, 0x00);
    MDrv_WriteByte(0x111f19, 0x00);
    // reg_ckg_demod_test_in_en@0x00[11]
    // reg_ckg_dvbtm_ts_out_mode@0x00[10]  set 1b1 use Non-gating clock.
    // reg_ckg_atsc_dvbtc_ts_inv@0x00[9] -> Invert PAD_TS1_CLK polarity !
    // reg_ckg_atsc_dvb_div_sel@0x00[8]
    //   -> clk_atsc_dvb_div= 0: MPLLDIV2(24*29/2=348MHz), 1:MPLLDIV3(24*29/3=232MHz)
    // reg_ckg_dvbtm_ts_divnum@0x00[4:0]
    //   -> clk_atsc_dvb_div (MHz) / ((reg_ckg_dvbtm_ts_divnum+1)*2)
    INTERN_DVBT_Write_VD_DMD_Byte(0x103300, 0x11);
    //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x05);
    tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
    tmp |= 0x05;
    INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x05);

    // reg_ckg_dvbtc_ts@0x04[11:8]
    // reg_ckg_atsc_ts@0x04[3:0]
#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
    //`RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0100);// ts clock= ts_div_clk(parallel-TS Mode)
    INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);
    INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x00);
#else
    //`RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h????);// ts clock= 62MHz(Series-TS Mode)
    INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);
    INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x04);
#endif
    // reg_ckg_vifdbb_144m@0x0e[11:8]  144MHz
    // reg_ckg_vifdbb_43m@0x0e[3:0]  43.2MHz
    MDrv_WriteByte(0x111f1c, 0x01);
    MDrv_WriteByte(0x111f1d, 0x01);
    // reg_ckg_vifdbb_vdac@0x0d[11:8]  43.2MHz
    // reg_ckg_vifdbb_dac@0x0d[3:0]  43.2MHz
    MDrv_WriteByte(0x111f1a, 0x01);
    MDrv_WriteByte(0x111f1b, 0x01);
//-------------------------------------------------------------------
// Enable TS PAD
//-------------------------------------------------------------------

// Set reg_ts1config@0x57[13:11]-reg_CHIPTOP = 3bx10, DMD will output Transport stream to PAD_TS1_XX
// wriu 0x101eaf 8'bxxx1_0xxx
    tmp = 0x10;
    INTERN_DVBT_Write_VD_DMD_Byte(0x101e9e, 0x00);
    INTERN_DVBT_Write_VD_DMD_Byte(0x101eaf, tmp);
//-------------------------------------------------------------------
// Enable RF_AGC, IF_AGC PAD
//-------------------------------------------------------------------

// reg_agcgctrl = 2d2  PAD_RF_AGC(up_agc) , PAD_IF_AGC(dn_agc) is for Demod control Tuner. by up/dn AGC mode
// reg_agcgctrl = 2d1  PAD_TGPIO0(up_agc) , PAD_TGPIO1(dn_agc) is for Demod control Tuner by up/dn AGC mode.
// reg_agcgctrl = 2d0  PAD_RF_AGC , PAD_IF_AGC is for Demod control Tuner. by PWM AGC mode
// reg_if_agc_pad_oen@reg_CHIPTOP-0x02[12]  set 1b0 to enable PAD_IF_AGC
// reg_rf_agc_pad_oen@reg-CHIPTOP-0x02[13] set 1b0 to enable PAD_RF_AGC.
// wriu 0x101e05 8'bxx00_xxxx
    tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x101e05);
    tmp &= ~0x30;
    INTERN_DVBT_Write_VD_DMD_Byte(0x101e05, tmp);

    INTERN_DVBT_Write_VD_DMD_Byte(0x101ea0, 0x00);
    INTERN_DVBT_Write_VD_DMD_Byte(0x101ea1, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x101E39, 0x03); //mux from HK to DMD MCU.

#endif
}

static BOOLEAN INTERN_DVBT_LoadDSPCode(void)
{
    U8  udata = 0x00;
    U16 i;
    U16 fail_cnt=0;

#if (DBG_DUMP_LOAD_DSP_TIME==1)
    U32 u32Time;
#endif

//#ifndef INTERN_DVBT_LOAD_FW_FROM_CODE_MEMORY
#if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_BIN )
    BININFO BinInfo;
    BOOLEAN bResult;
    U32 u32GEAddr;
    U8 Data;
    S8 op;
    U32 srcaddr;
    U32 len;
    U32 SizeBy4K;
    U16 u16Counter=0;
    U8 *pU8Data;
#endif

#if 0
    if(MDrv_ReadByte(0x101E3E))
    {
        printf("Warring! Reg[0x101E3E]=%d\n", MDrv_ReadByte(0x101E3E));
        return FALSE;
    }
#endif

    if (LoadDspStatus == 0x01) //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
    {
        // printf("Warning! LoadDspStatus=%d\n", LoadDspStatus);
        return TRUE;
    }
    else
    {
        LoadDspStatus = 0xff; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
    }

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00,  0x01);        // reset VD_MCU
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x01,  0x00);        // disable SRAM
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03,  0x50);        // enable "vdmcu51_if"
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03,  0x51);        // enable auto-increase
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x04,  0x00);        // sram address low byte
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x05,  0x00);        // sram address high byte

    ////  Load code thru VDMCU_IF ////
    DBG_INTERN_DVBT(printf(">Load Code...\n"));


#if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )
    for ( i = 0; i < sizeof(INTERN_DVBT_table); i++)
    {
        INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x0C, INTERN_DVBT_table[i]); // write data to VD MCU 51 code sram
    }
#else
    BinInfo.B_ID = BIN_ID_INTERN_DVBT_DEMOD;
    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS )
    {
        return FALSE;
    }
    //printf("\t DEMOD_MEM_ADR  =%08LX\n", ((DEMOD_MEM_ADR & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)));

  #ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_Start(&BinInfo);
  #endif

    msAPI_MIU_Copy(BinInfo.B_FAddr, ((DEMOD_MEM_MEMORY_TYPE & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)), MemAlign(BinInfo.B_Len, 8), MIU_FLASH2SDRAM);

  #ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_End(&BinInfo);
  #endif

    //W1BaseAddr = MDrv_Sys_GetXdataWindow1Base();
    SizeBy4K=BinInfo.B_Len/0x1000;
    //printf("\t RRR: SizeBy4K=%d (L=%d)\n", SizeBy4K,BinInfo.B_Len);

  #if (DBG_DUMP_LOAD_DSP_TIME==1)
    u32Time = msAPI_Timer_GetTime0();
  #endif

    u32GEAddr = _PA2VA(((DEMOD_MEM_MEMORY_TYPE & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)));

    for (i=0;i<=SizeBy4K;i++)
    {
        if(i==SizeBy4K)
            len=BinInfo.B_Len%0x1000;
        else
            len=0x1000;

        srcaddr = u32GEAddr+(0x1000*i);
        //printf("\t i = %08X\n", i);
        //printf("\t len = %08X\n", len);
        op = 1;
        u16Counter = 0 ;
        //printf("\t (B=0x%x)(Src=0x%x)Data =",i,srcaddr);
        while(len--)
        {
            u16Counter ++ ;
            //printf("file: %s, line: %d\n", __FILE__, __LINE__);
            //pU8Data = (U8 *)(srcaddr|0x80000000);
            pU8Data = (U8 *)(srcaddr|0x80000000);
            Data  = *pU8Data;

          #if 0
            if(u16Counter < 0x100)
                printf("0x%bx,", Data);
          #endif
            MDrv_WriteByte(DMDMcuBase + 0x0C, Data); // write data to VD MCU 51 code sram

            srcaddr += op;
        }
        //printf("\n\n\n");
    }

  #if (DBG_DUMP_LOAD_DSP_TIME==1)
    printf("------> INTERN_DVBT Load DSP Time:  (%lu)\n", msAPI_Timer_DiffTimeFromNow(u32Time)) ;
  #endif

#endif  // #if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )

    ////  Content verification ////
    DBG_INTERN_DVBT(printf(">Verify Code...\n"));

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x04, 0x00);         // sram address low byte
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x05, 0x00);         // sram address high byte

//#ifdef INTERN_DVBT_LOAD_FW_FROM_CODE_MEMORY
#if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )
    for ( i = 0; i < sizeof(INTERN_DVBT_table); i++)
    {
        udata = INTERN_DVBT_Read_VD_DMD_Byte(DMDMcuBase + 0x10);    // read sram data
        if (udata != INTERN_DVBT_table[i])
        {
            MS_DEBUG_MSG(printf(">fail add = 0x%x\n", i));
            MS_DEBUG_MSG(printf(">code = 0x%x\n", INTERN_DVBT_table[i]));
            MS_DEBUG_MSG(printf(">data = 0x%x\n", udata));

            if (fail_cnt++ > 10)
            {
                MS_DEBUG_MSG(printf(">DVB-T DSP Loadcode fail!"));
                return false;
            }
        }
    }
#else
    for (i=0;i<=SizeBy4K;i++)
    {
        if(i==SizeBy4K)
            len=BinInfo.B_Len%0x1000;
        else
            len=0x1000;

        srcaddr = u32GEAddr+(0x1000*i);
        //printf("\t i = %08LX\n", i);
        //printf("\t len = %08LX\n", len);
        op = 1;
        u16Counter = 0 ;
        //printf("\t (B=0x%bx)(Src=0x%x)Data =",i,srcaddr);
        while(len--)
        {
            u16Counter ++ ;
            //printf("file: %s, line: %d\n", __FILE__, __LINE__);
            //pU8Data = (U8 *)(srcaddr|0x80000000);
            pU8Data = (U8 *)(srcaddr|0x80000000);
            Data  = *pU8Data;

          #if 0
            if(u16Counter < 0x100)
                printf("0x%bx,", Data);
          #endif
            udata = MDrv_ReadByte(DMDMcuBase + 0x10);    // read sram data
            if (udata != Data)
            {
                printf(">fail add = 0x%lx\n", (U32)((i*0x1000)+(0x1000-len)));
                printf(">code = 0x%x\n", Data);
                printf(">data = 0x%x\n", udata);

                if (fail_cnt++ > 10)
                {
                    printf(">DVB-T DSP Loadcode fail!");
                    return false;
                }
            }

            srcaddr += op;
        }
        //printf("\n\n\n");
    }
#endif

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x50);     // diable auto-increase
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x00);     // disable "vdmcu51_if"
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x01, 0x01);     // enable SRAM
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00, 0x00);     // release VD_MCU

    DBG_INTERN_DVBT(printf(">DSP Loadcode done."));
    //while(load_data_variable);

    if(MDrv_Read2Byte(0x001ECC) == 0x000F)    // chip_id == T3
    {
        MDrv_WriteByte(0x101E3E, 0x02);   // DVBT = BIT1 -> 0x02
    }

        LoadDspStatus = 0x01; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null

    return TRUE;
}


#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
#else
BOOLEAN INTERN_DVBT_SoftStop ( void )
{
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    U16     u8WaitCnt=0;

    if (MDrv_ReadByte(MBRegBase + 0x00))
    {
        printf(">> MB Busy!\n");
        return FALSE;
    }

    MDrv_WriteByte(MBRegBase + 0x00, 0xA5);                 // MB_CNTL set read mode

    MDrv_WriteByte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to VD MCU51
    MDrv_WriteByte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to VD MCU51

    while(MDrv_ReadByte(MBRegBase + 0x00)!= 0x5A)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            printf(">> DVBT SoftStop Fail!\n");
            return FALSE;
        }
    }

    //MDrv_WriteByte(0x103460, 0x01);                         // reset VD_MCU
    MDrv_WriteByte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

#endif
    return TRUE;
}
#endif



BOOLEAN INTERN_DVBT_Reset ( void )
{
    DBG_INTERN_DVBT(printf(" @INTERN_DVBT_reset\n"));

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
#else
    INTERN_DVBT_SoftStop();
#endif

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00, 0x01);     // reset DMD_MCU
    //INTERN_DVBT_WriteReg(0x2002, 0x72);        // reset DVB-T
    INTERN_DVBT_Delayms(5);
    // INTERN_DVBT_WriteReg(0x2002, 0x52);
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00, 0x00);
    INTERN_DVBT_Delayms(5);
    FECLock = FALSE;
    return TRUE;
}

//-----------------------------------------------------------------------
BOOLEAN INTERN_DVBT_ReadReg(U16 u16Addr, U8 *pu8Data)
{
    U16     u8WaitCnt=0;

    if (INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00))
    {
        MS_DEBUG_MSG(printf(">> MB Busy!\n"));
        return FALSE;
    }

    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x01, (U8)u16Addr);          // ADDR_L
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x01);                 // MB_CNTL set read mode

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to DMD MCU51 //mick
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to DMD MCU51

    while(INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00)!= 0xFF)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            MS_DEBUG_MSG(printf(">> DVBT ReadReg Fail!\n"));
            return FALSE;
        }
    }

    *pu8Data = INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x03);             // REG_DATA get
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}

//-----------------------------------------------------------------------
BOOLEAN INTERN_DVBT_WriteReg(U32 u16Addr, U8 u8Data)
{
    U16     u8WaitCnt=0;

    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x01, (U8)u16Addr);          // ADDR_L
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x03, u8Data);               // REG_DATA
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x02);                 // MB_CNTL set write mode

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to VD MCU51 //mick
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to VD MCU51

    while(INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00) != 0xFF)          // wait done flag
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);   // <<< Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            MS_DEBUG_MSG(printf(">> DVBT WriteReg Fail!\n"));
            return FALSE;
        }
    }

    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}
//-----------------------------------------------------------------------

BOOLEAN INTERN_DVBT_Power_On_Initialization_For_VIF_Init ( void )
{
    U8            status = true;
    //U8            cData;
    DBG_INTERN_DVBT(printf("\n@~@~@~@~@~@~@~@~@~@  INTERN_DVBT_Power_On_Initialization\n"));

    //INTERN_DVBT_InitRegBase();

      LoadDspStatus = 0xff; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null

    INTERN_DVBT_InitClkgen();

    //// Firmware download //////////
    DBG_INTERN_DVBT(printf("INTERN_DVBT Load DSP...\n"));
    //MsOS_DelayTask(100);

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    if (MDrv_ReadByte(0x101E3E) != 0x02) // DVBT = BIT1 -> 0x02
    {
        if (INTERN_DVBT_LoadDSPCode() == FALSE)
        {
            printf("DVB-T Load DSP Code Fail\n");
            return FALSE;
        }
        else
        {
            printf("DVB-T Load DSP Code OK\n");
        }
    }
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L)  || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)   || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2)   || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1)   || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)   || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)   || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)|| \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

    if (INTERN_DVBT_LoadDSPCode() == FALSE)
    {
        printf("DVB-T Load DSP Code Fail\n");
        return FALSE;
    }
    else
    {
        printf("DVB-T Load DSP Code OK\n");
    }
#endif

    //// MCU Reset //////////
    DBG_INTERN_DVBT(printf("INTERN_DVBT Reset...\n"));
    if (INTERN_DVBT_Reset() == FALSE)
    {
        DBG_INTERN_DVBT(printf("Fail\n"));
        return FALSE;
    }
    else
    {
        DBG_INTERN_DVBT(printf("OK\n"));
    }


#if 0
    // reset FDP
    INTERN_DVBT_WriteReg(0x2200, 0xFF);
    // SRAM setting, DVB-T use it.
    // 0x2204, Bit0, 0:DVB-T use, 1: VIF use
    INTERN_DVBT_ReadReg(0x2204,&cData);
    INTERN_DVBT_WriteReg(0x2204, cData&0xFE);

    status &= INTERN_DVBT_DSPReg_Init();

#endif

    return status;
}


#else


#if (INTERN_DVBT_INTERNAL_DEBUG)
BOOLEAN INTERN_DVBT_GetDigACI(U8 *ret_status);
BOOLEAN INTERN_DVBT_GetFD(U8 *fd);
BOOLEAN INTERN_DVBT_GetChannelLength(U16 *fd);
BOOLEAN INTERN_DVBT_GetUSE_VAR(void);
BOOLEAN INTERN_DVBT_Version(U16 *ver);
float INTERN_DVBT_GetSNR (void);
BOOLEAN INTERN_DVBT_GetSFO(float *SFO);
BOOLEAN INTERN_DVBT_GetCFO(float *CFO);
BOOLEAN INTERN_DVBT_GetPacketErrorNum(S16 *pktErrNum);
BOOLEAN INTERN_DVBT_Get_SW_ChannelLength(U16 *ch_length);
#endif

#define SIGNAL_LEVEL_OFFSET     0.00
#define TAKEOVERPOINT            -60.0
#define TAKEOVERRANGE               0.5
#define LOG10_OFFSET                 -0.21
#define INTERN_DVBT_USE_SAR_3_ENABLE 0
#define INTERN_DVBT_GET_TIME msAPI_Timer_GetTime0()



#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_A1)  || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)   || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)   || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)|| \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))

#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))
#define DVBT_FS     24000
#define FC_H		0x4A	//  19000, Fc = Fs - IF = 24000 - 5000 = 19000 -> 0323 update
#define FC_L		0x38    // 0323 jason
#elif ((CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER))
#if ((VIF_SAW_ARCH == 3) || (VIF_SAW_ARCH == 5)) // No Saw (VIF / DIF)
#define DVBT_FS     45474
#if((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#define FC_H		0x9E	//  40474, Fc = Fs - IF = 45474 - 5000 = 40474 -> 0323 update
#define FC_L		0x19    //0x1A    // IF 5Mhz
#else
	#if(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER && ENABLE_DVB_TAIWAN_APP == ENABLE)

		#define FC_H		0xA4//0x9E	//  40474, Fc = Fs - IF = 45474 - 3250 = 40474 -> 0323 update
		#define FC_L		0xF0//0xE1    //0x1A    // 0323 jason

	#else

		#define FC_H		0x9E	//  40474, Fc = Fs - IF = 45474 - 5000 = 40474 -> 0323 update
		#define FC_L		0xE1    //0x1A    // 0323 jason

	#endif
#endif
#else
#define DVBT_FS     48000 //45474
#if((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#define FC_H		0xA7	// Fc = Fs - IF = 48000 - 5000 = 43000 -> 1112 update
#define FC_L		0xF8       // IF 5Mhz
#else
	#if(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER && ENABLE_DVB_TAIWAN_APP == ENABLE)

		#define FC_H		0xAE // Fc = Fs - IF = 48000 - 3250 = 44750 -> 1112 update
		#define FC_L		0xCE // IF 3.25Mhz

	#else

		#define FC_H		0xA8    // Fc = Fs - IF = 48000 - 4800 = 43200 -> 1112 update
		#define FC_L		0xC0    // IF 4.8Mhz

	#endif
#endif
#endif
#else
#define DVBT_FS     45474
#if((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#define FC_H		0x9E	//  40474, Fc = Fs - IF = 45474 - 5000 = 40474 -> 0323 update
#define FC_L		0x19    //0x1A    // IF 5Mhz
#else
	#if(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER && ENABLE_DVB_TAIWAN_APP == ENABLE)

		#define FC_H		0xA4//0x9E	//  40474, Fc = Fs - IF = 45474 - 3250 = 40474 -> 0323 update
		#define FC_L		0xF0//0xE1    //0x1A    // 0323 jason

	#else

		#define FC_H		0x9E	//  40474, Fc = Fs - IF = 45474 - 5000 = 40474 -> 0323 update
		#define FC_L		0xE1    //0x1A    // 0323 jason

	#endif
#endif
#endif

/*BEG INTERN_DVBT_DSPREG_TABLE*/
#define     D_DMD_DVBT_PARAM_VERSION                      0x01
#define     D_DMD_DVBT_OP_AUTO_SCAN_MODE_EN               0x01    // 0 for normal channel change, 1 for auto scanning
#define     D_DMD_DVBT_OP_RFAGC_EN                        0x00
#define     D_DMD_DVBT_OP_HUMDET_EN                       0x01
#define     D_DMD_DVBT_OP_AUTO_RF_MAX_EN                  0x00
#define     D_DMD_DVBT_OP_DCR_EN                          0x01
#define     D_DMD_DVBT_OP_IIS_EN                          0x01
#define     D_DMD_DVBT_OP_IQB_EN                          0x00
#define     D_DMD_DVBT_OP_AUTO_IQ_SWAP_EN                 0x01
#define     D_DMD_DVBT_OP_ACI_EN                          0x00  //0x01
#define     D_DMD_DVBT_OP_CCI_EN                          0x01
#define     D_DMD_DVBT_OP_FIX_MODE_CP_EN                  0x00
#define     D_DMD_DVBT_OP_FIX_TPS_EN                      0x00
#define     D_DMD_DVBT_CFG_BW                             0x00  // BW: 0..3  for 5M, 6M, 7M, 8M Channel Allocation
#define     D_DMD_DVBT_CFG_MODE                           0x00  // 0, 1, 2 for 2K, 8K, 4K OFDM subcarriers
#define     D_DMD_DVBT_CFG_CP                             0x00  // 0..3  for Intervals of 1/32, 1/16, 1/8, 1/4
#define     D_DMD_DVBT_CFG_LP_SEL                         0x00  // HP or LP selection, 0:HP, 1:LP
#define     D_DMD_DVBT_CFG_CSTL                           0x02  // constellation, 0, 1, 2 for QPSK, 16QAM, 64QAM
#define     D_DMD_DVBT_CFG_HIER                           0x00  // 0..7  for None, Alpha = 1, 2, 4, or add 4 for indepth interleaver
#define     D_DMD_DVBT_CFG_HPCR                           0x01  // HP CR, 0..4  for Rates of 1/2, 2/3, 3/4, 5/6, 7/8
#define     D_DMD_DVBT_CFG_LPCR                           0x02  // LP CR, 0..4  for Rates of 1/2, 2/3, 3/4, 5/6, 7/8
#define     D_DMD_DVBT_CFG_RFMAX                          0x01  // work for RF AGC external mode enable.
#define     D_DMD_DVBT_CFG_ZIF                            0x00  // 0 for IF, 1 for ZIF structure
#define     D_DMD_DVBT_CFG_RSSI                           0x00  // 0 for NOT using RSSI, 1 for using RSSI
#define     D_DMD_DVBT_CFG_RFAGC_REF                      0x64
#define     D_DMD_DVBT_CFG_IFAGC_REF_2K                   0x4B  //0x96  //0xB0 YP for sensitivity test
#if((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#define     D_DMD_DVBT_CFG_IFAGC_REF_8K                   0x00  //0x25
#else
#define     D_DMD_DVBT_CFG_IFAGC_REF_8K                   0x4B  //0x25
#endif
#define     D_DMD_DVBT_CFG_IFAGC_REF_ACI                  0x4B  //0x96
#define     D_DMD_DVBT_CFG_IFAGC_REF_IIS                  0xA0  //0xf8
#define     D_DMD_DVBT_CFG_IFAGC_REF_2K_H                 0x00  //0xB0 YP for sensitivity test
#if((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER))
#define     D_DMD_DVBT_CFG_IFAGC_REF_8K_H                 0x05  //0x07
#else
#define     D_DMD_DVBT_CFG_IFAGC_REF_8K_H                 0x00  //0x07
#endif
#define     D_DMD_DVBT_CFG_IFAGC_REF_ACI_H                0x00
#define     D_DMD_DVBT_CFG_IFAGC_REF_IIS_H                0x00
// No use now
#define     D_DMD_DVBT_CFG_FC_L                           0x20  // 9394, Fc = Fs - IF = 45474 - 36167 = 9307
#define     D_DMD_DVBT_CFG_FC_H                           0x4E
#define     D_DMD_DVBT_CFG_FS_L                           0xC0  // 45474, Fs = 45.4738MHz
#define     D_DMD_DVBT_CFG_FS_H                           0x5D
#define     D_DMD_DVBT_CFG_IQ_SWAP                        0x00  // 1: iq swap, 0: non iq swap

#define     D_DMD_DVBT_CFG_8M_DACI_DET_TH_L               0xf0
#define     D_DMD_DVBT_CFG_8M_DACI_DET_TH_H               0x0a
#define     D_DMD_DVBT_CFG_8M_ANM1_DET_TH_L               0xc4
#define     D_DMD_DVBT_CFG_8M_ANM1_DET_TH_H               0x09
#define     D_DMD_DVBT_CFG_8M_ANP1_DET_TH_L               0xc4
#define     D_DMD_DVBT_CFG_8M_ANP1_DET_TH_H               0x09
#define     D_DMD_DVBT_CFG_7M_DACI_DET_TH_L               0xf0
#define     D_DMD_DVBT_CFG_7M_DACI_DET_TH_H               0x0a
#define     D_DMD_DVBT_CFG_7M_ANM1_DET_TH_L               0xc4
#define     D_DMD_DVBT_CFG_7M_ANM1_DET_TH_H               0x09
#define     D_DMD_DVBT_CFG_7M_ANP1_DET_TH_L               0xc4
#define     D_DMD_DVBT_CFG_7M_ANP1_DET_TH_H               0x09

#define     D_DMD_DVBT_CFG_CCI                            0x00  // PAL_I: 0: Non-Pal-I CCI, 1: Pal-I CCI (for UK)
#define     D_DMD_DVBT_CFG_ICFO_RANGE                     0x01  // ICFOE search range: 0: narrow , 1: medium, 2:large range
#define     D_DMD_DVBT_CFG_TS_SERIAL                      0x01  // 1: serial mode, 0: parallel mode.
//#define     DMD_DVBT_CFG_TS_PARALLEL                    0x00  // 1: serial mode, 0: parallel mode.
#if (INTERN_DVBT_TS_SERIAL_INVERSION)
#define     D_DMD_DVBT_CFG_TS_CLK_INV                     0x01  // Inversion
#else
#define     D_DMD_DVBT_CFG_TS_CLK_INV                     0x00  // non-Inversion
#endif
#define     D_DMD_DVBT_CFG_TS_DATA_SWAP                   0x00  // TS data reverse, 1: reverse, 0: non-reverse.
//#define     DMD_DVBT_CHECKSUM                           0x00
/*END INTERN_DVBT_DSPREG_TABLE*/
#define FS_H        ((DVBT_FS>>8)&0xFF)    // FS=45473, Fs = 45.474MHz
#define FS_L        (DVBT_FS&0xFF)    // andy 2009-8-18 ¿ÀÈÄ 10:22:29 0x9E
#define SET_ZIF     0x00
#define IQB_EN      0x00

#define FORCE_MC	0x00    //0: auto 1: Force mode-cp
#define FORCE_TPS	0x00	//0: auto 1: Force TPS
#define AUTO_SCAN	0x00	// Auto Scan - 0:channel change, 1:auto-scan
#define	CSTL		0x02    //0:QPSK 1:16 2: 64
#define HIER		0x00
#define HPCR		0x01	// HP_CR 0:1/2, 1:2/3, 2: 3/4, 3: 5/6, 4:7/8
#define LPCR		0x01	// LP_CR 0:1/2, 1:2/3, 2: 3/4, 3: 5/6, 4:7/8
#define FFT_MODE	0x01	// FFT mode - 0:2K, 1:8K
#define CP			0x00	// CP - 0:1/32, 1/16, 1/8, 1/4
#define LP_SEL		0x00	// LP select
#if (FRONTEND_TUNER_TYPE==NUTUNE_FK1602_TUNER||FRONTEND_TUNER_TYPE==NXP_TDA18274_TUNER)
#define IQ_SWAP		0x01
#else
#define IQ_SWAP		0x00    //0x01
#endif
#define PAL_I		0x00	// PAL_I: 0: Non-Pal-I CCI, 1: Pal-I CCI (for UK)
#define	CFO_RANGE 	0x01	//0: 500KHz 1: 900KHz
#define	CFO_RANGE_TW 	0x00	//0: 500KHz 1: 900KHz
#define TS_SER      0
#define TS_INV      0
#define FIF_H       (MS_U8)(( (((MS_U16)FS_H<<8)|FS_L) - (((MS_U16)FC_H<<8)|FC_L))>>8)
#define FIF_L       (MS_U8)(( ((MS_U16)FS_H<<8)|FS_L) - (((MS_U16)FC_H<<8)|FC_L))
#define IF_INV_PWM    0x00
#define T_LOWIF     1


#else
/*BEG INTERN_DVBT_DSPREG_TABLE*/
#define DVBT_OP_RFAGC_EN            0x00
#define DVBT_OP_HUMDET_EN           0x01
#define DVBT_OP_DCR_EN              0x01
#define DVBT_OP_IIS_EN              0x01
#define DVBT_OP_CCI_EN              0x01
#define DVBT_OP_ACI_EN              0x01
#define DVBT_OP_IQB_EN              0x00
#define DVBT_OP_AUTO_IQ_SWAP_EN     0x01
#define DVBT_OP_AUTO_RF_MAX_EN      0x00
#define DVBT_OP_AUTO_ACI_EN         0xff  // No use
#define DVBT_OP_FIX_MODE_CP_EN      0x00
#define DVBT_OP_FIX_TPS_EN          0x00
#define DVBT_OP_AUTO_SCAN_MODE_EN   0x00  // 0 for normal channel change, 1 for auto scanning
#define DVBT_CFG_RSSI               0x00  // 0 for NOT using RSSI, 1 for using RSSI
#define DVBT_CFG_ZIF                0x00  // 0 for IF, 1 for ZIF structure
#define DVBT_CFG_FREQ               0xff  // No use
#define DVBT_CFG_FC_L                   (U8)(0xB1A2-DTV_IF_8M_FREQ)// 0x5B  // 9394, Fc = Fs - IF = 45474 - 36167 = 9307
#define DVBT_CFG_FC_H                   (U8)((0xB1A2-DTV_IF_8M_FREQ)>>8)//0x9F//  0x24
#define DVBT_CFG_FS_L                     0xA2  // 45474, Fs = 45.4738MHz
#define DVBT_CFG_FS_H                     0xB1
#define DVBT_CFG_BW                 0x00  // BW: 0..3  for 5M, 6M, 7M, 8M Channel Allocation
#define DVBT_CFG_MODE               0x00  // 0, 1, 2 for 2K, 8K, 4K OFDM subcarriers
#define DVBT_CFG_CP                 0x00  // 0..3  for Intervals of 1/32, 1/16, 1/8, 1/4
#define DVBT_CFG_LP_SEL             0x00  // HP or LP selection, 0:HP, 1:LP
#define DVBT_CFG_CSTL                     0x02  // constellation, 0, 1, 2 for QPSK, 16QAM, 64QAM
#define DVBT_CFG_HIER                   0x00  // 0..7  for None, Alpha = 1, 2, 4, or add 4 for indepth interleaver
#define DVBT_CFG_HPCR               0x01  // HP CR, 0..4  for Rates of 1/2, 2/3, 3/4, 5/6, 7/8
#define DVBT_CFG_LPCR                     0x02  // LP CR, 0..4  for Rates of 1/2, 2/3, 3/4, 5/6, 7/8
#define DVBT_CFG_IQ_SWAP            0x00  // 1: iq swap, 0: non iq swap
#define DVBT_CFG_RFMAX              0x01  // work for RF AGC external mode enable.
#define DVBT_CFG_CCI                0x00  // PAL_I: 0: Non-Pal-I CCI, 1: Pal-I CCI (for UK)
#define DVBT_CFG_ICFO_RANGE         0x01  // ICFOE search range: 0: narrow , 1: medium, 2:large range
#define DVBT_CFG_RFAGC_REF          0x64  // No use
#if (IF_AGC_VPP == 1)
    #define DVBT_CFG_IFAGC_REF_2K       0xB0-0x50
    #define DVBT_CFG_IFAGC_REF_8K       0x96-0x50
    #define DVBT_CFG_IFAGC_REF_ACI      0x96-0x50
    //#define DVBT_CFG_IFAGC_REF_IIS      0xf8-0x50
    #define DVBT_CFG_IFAGC_REF_IIS_2K      0xf8-0x50  // No use
    #define DVBT_CFG_IFAGC_REF_IIS_8K      0xC0-0x50  // No use
    #define DVBT_CFG_ACI_DET_TH_L       0xff  // 0xcd  // No use
    #define DVBT_CFG_ACI_DET_TH_H       0x02  // 0x01  // No use
#elif (IF_AGC_VPP == 2)
    #define DVBT_CFG_IFAGC_REF_2K       0xB0
    #define DVBT_CFG_IFAGC_REF_8K       0x96
    #define DVBT_CFG_IFAGC_REF_ACI      0x96
    //#define DVBT_CFG_IFAGC_REF_IIS      0xf8
    #define DVBT_CFG_IFAGC_REF_IIS_2K      0xf8  // No use
    #define DVBT_CFG_IFAGC_REF_IIS_8K      0xC0  // No use
// DIOS403IR121B  tuner
    #define DVBT_CFG_ACI_DET_TH_L       0xB0//bryan 110411//bryan mark 110411 0xcd  //0xcd
    #define DVBT_CFG_ACI_DET_TH_H       0x02//bryan 110411// bryan mark 110411 0x01 //0x01
#elif (IF_AGC_VPP == 3&&FRONTEND_TUNER_TYPE== RAFAEL_R828_TUNER)
		//<<--M-- SMC 20110423
	#define DVBT_CFG_IFAGC_REF_2K       0xB0-0x30
	#define DVBT_CFG_IFAGC_REF_8K       0x96-0x30
	#define DVBT_CFG_IFAGC_REF_ACI      0x96-0x30
		//#define DVBT_CFG_IFAGC_REF_IIS	  0xf8-0x50
	#define DVBT_CFG_IFAGC_REF_IIS_2K      0xf8-0x30  // No use
	#define DVBT_CFG_IFAGC_REF_IIS_8K      0xC0-0x30  // No use
	#define DVBT_CFG_ACI_DET_TH_L       0xff  // 0xcd  // No use
	#define DVBT_CFG_ACI_DET_TH_H       0x02  // 0x01  // No use
#endif

#define DVBT_CFG_TS_SERIAL          0x01  // 1: serial mode, 0: parallel mode.
#define DVBT_CFG_TS_PARALLEL         0x00  // 1: serial mode, 0: parallel mode.
#define DVBT_CFG_TS_CLK_RATE        0xff  // NO use
#if (INTERN_DVBT_TS_SERIAL_INVERSION)
#define DVBT_CFG_TS_CLK_INV         0x01  // Inversion
#else
#define DVBT_CFG_TS_CLK_INV         0x00  // non-Inversion
#endif
#define DVBT_CFG_TS_DATA_SWAP       0x00  // TS data reverse, 1: reverse, 0: non-reverse.
#define DVBT_TDP_CCI_KP             0x65 //0x62
#define DVBT_TDP_CCI_FSWEEP         0x45 //0x30
#endif
/*END INTERN_DVBT_DSPREG_TABLE*/

U8 INTERN_DVBT_DSPREG[] =
{
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_A1)   || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)   || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A6)   || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)   || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)|| \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))
    0x00, 0x00, 0x00, D_DMD_DVBT_OP_DCR_EN, 0x01, 0x01, 0x01, IQB_EN, 0x01, 0x00, 0x00, FORCE_MC, FORCE_TPS, AUTO_SCAN, 0x00, SET_ZIF, //00-0F
    0x00, T_LOWIF, 0x00, FS_L, FS_H, FIF_L, FIF_H, FC_L, FC_H, 0x03, FFT_MODE, CP, LP_SEL, CSTL, HIER, HPCR, //10-1F
    LPCR, IQ_SWAP, 0x00, PAL_I, CFO_RANGE, D_DMD_DVBT_CFG_RFAGC_REF, D_DMD_DVBT_CFG_IFAGC_REF_2K, D_DMD_DVBT_CFG_IFAGC_REF_8K, D_DMD_DVBT_CFG_IFAGC_REF_ACI, D_DMD_DVBT_CFG_IFAGC_REF_IIS, //20-29
    D_DMD_DVBT_CFG_IFAGC_REF_2K_H, D_DMD_DVBT_CFG_IFAGC_REF_8K_H, D_DMD_DVBT_CFG_IFAGC_REF_ACI_H, D_DMD_DVBT_CFG_IFAGC_REF_IIS_H, TS_SER, TS_INV, //2A-2F
    0x00, 0xf0, 0x0a, 0xc4, 0x09, 0xc4, 0x09, 0xf0, 0x0a, 0xc4, 0x09, 0xc4, 0x09, 0x00, 0xd0, 0x80, //30-3F
    0x7f, 0xa0, 0x23, 0x05, 0x05, 0x40, 0x34, 0x06, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x65, 0x00, //40-4F
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //50-5F
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x01, 0x03, //60-6F
    0x03, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       //70-7E
#else
    //0x00~0x0f
    DVBT_OP_RFAGC_EN,          DVBT_OP_HUMDET_EN,     DVBT_OP_DCR_EN,          DVBT_OP_IIS_EN,
    DVBT_OP_CCI_EN,            DVBT_OP_ACI_EN,        DVBT_OP_IQB_EN,          DVBT_OP_AUTO_IQ_SWAP_EN,
    DVBT_OP_AUTO_RF_MAX_EN,    DVBT_OP_AUTO_ACI_EN,   DVBT_OP_FIX_MODE_CP_EN,  DVBT_OP_FIX_TPS_EN,
    DVBT_OP_AUTO_SCAN_MODE_EN, 0xff,                  0xff,                    0xff,

    //0x10~0x1f
    DVBT_CFG_RSSI,             DVBT_CFG_ZIF,          DVBT_CFG_FREQ,
    DVBT_CFG_FC_L,             DVBT_CFG_FC_H,         DVBT_CFG_FS_L,           DVBT_CFG_FS_H,
    DVBT_CFG_BW,               DVBT_CFG_MODE,         DVBT_CFG_CP,             DVBT_CFG_LP_SEL,
    DVBT_CFG_CSTL,

    DVBT_CFG_HIER,             DVBT_CFG_HPCR,         DVBT_CFG_LPCR,           DVBT_CFG_IQ_SWAP,

    //0x20~
    DVBT_CFG_RFMAX,            DVBT_CFG_CCI,          DVBT_CFG_ICFO_RANGE,     DVBT_CFG_RFAGC_REF,
    DVBT_CFG_IFAGC_REF_2K,     DVBT_CFG_IFAGC_REF_8K, DVBT_CFG_IFAGC_REF_ACI,  //DVBT_CFG_IFAGC_REF_IIS,
    DVBT_CFG_IFAGC_REF_IIS_2K, DVBT_CFG_IFAGC_REF_IIS_8K,
    DVBT_CFG_ACI_DET_TH_L,     DVBT_CFG_ACI_DET_TH_H,
 #if (ENABLE_CI)
  #if (!TS_SERIAL_OUTPUT_IF_CI_REMOVED)
    DVBT_CFG_TS_PARALLEL
  #else
    DVBT_CFG_TS_SERIAL
  #endif
 #elif TS_PARALLEL_OUTPUT
    DVBT_CFG_TS_PARALLEL
 #else
    DVBT_CFG_TS_SERIAL
 #endif
    ,DVBT_CFG_TS_CLK_RATE,
    DVBT_CFG_TS_CLK_INV,       DVBT_CFG_TS_DATA_SWAP ,
    DVBT_TDP_CCI_KP,           DVBT_TDP_CCI_FSWEEP
#endif
};

static S_INTERN_DVBT_RFAGC_SSI MSTAR_RfagcSsi_INTERN_DVBT[] =
{
    {-15.00,    0x02},
    {-25.00,    0x04},
    {-26.00,    0x04},
    {-27.00,    0x05},
    {-28.00,    0x05},
    {-29.00,    0x05},
    {-30.00,    0x06},
    {-31.00,    0x07},
    {-32.00,    0x07},
    {-33.00,    0x08},
    {-34.00,    0x09},
    {-35.00,    0x09},
    {-36.00,    0x09},
    {-37.00,    0x0A},
    {-38.00,    0x0A},
    {-39.00,    0x0B},
    {-40.00,    0x0B},
    {-41.00,    0x0B},
    {-42.00,    0x0B},
    {-43.00,    0x0C},
    {-44.00,    0x0C},
    {-45.00,    0x0C},
    {-47.00,    0x0D},
    {-48.00,    0x0E},
    {-49.00,    0x0E},
    {-50.00,    0x0F},
    {-51.00,    0x0F},
    {-52.00,    0x10},
    {-53.00,    0x11},
    {-55.00,    0x11},
    {-56.00,    0x12},
    {-57.00,    0x13},
    {-57.50,    0x14},
    {-58.00,    0x17},
    {-58.50,    0x18},
    {-59.00,    0x1A},
    {-59.20,    0x1B},
    {-59.40,    0x1C},
    {-59.60,    0x1D},
    {-59.80,    0x1D},
    {-60.00,    0x1D},
    {-62.00,    0x1D},
    {-62.00,    0xFF},
};

#if 0
static S_INTERN_DVBT_IFAGC_SSI MSTAR_IfagcSsi_LoRef_INTERN_DVBT[] =
{
    {-59.00,    0x9D},
    {-60.00,    0x9E},
    {-60.70,    0x9F},
    {-61.40,    0xA0},
    {-62.00,    0xA2},
    {-62.50,    0xA2},
    {-63.00,    0xA3},
    {-63.50,    0xA4},
    {-64.00,    0xA5},
    {-64.50,    0xA6},
    {-65.00,    0xA7},
    {-65.50,    0xA8},
    {-66.00,    0xA9},
    {-66.50,    0xAA},
    {-67.00,    0xAB},
    {-67.50,    0xAC},
    {-68.00,    0xAD},
    {-68.50,    0xAD},
    {-69.00,    0xAE},
    {-69.50,    0xAF},
    {-70.00,    0xB0},
    {-70.30,    0xB0},
    {-70.60,    0xB1},
    {-71.00,    0xB2},
    {-71.30,    0xB3},
    {-71.60,    0xB3},
    {-72.00,    0xB4},
    {-72.50,    0xB5},
    {-73.00,    0xB6},
    {-73.30,    0xB7},
    {-73.60,    0xB7},
    {-74.00,    0xB8},
    {-74.30,    0xB9},
    {-74.60,    0xBA},
    {-75.00,    0xBB},
    {-75.25,    0xBB},
    {-75.50,    0xBC},
    {-75.75,    0xBD},
    {-76.00,    0xBE},
    {-76.17,    0xBE},
    {-76.34,    0xBF},
    {-76.51,    0xC0},
    {-76.68,    0xC0},
    {-76.85,    0xC1},
    {-77.00,    0xC1},
    {-77.11,    0xC2},
    {-77.22,    0xC2},
    {-77.33,    0xC2},
    {-77.44,    0xC3},
    {-77.55,    0xC3},
    {-77.66,    0xC3},
    {-77.77,    0xC4},
    {-77.88,    0xC4},
    {-78.00,    0xC5},
    {-78.33,    0xC6},
    {-78.66,    0xC8},
    {-79.00,    0xCA},
    {-79.20,    0xCB},
    {-79.40,    0xCD},
    {-79.60,    0xCF},
    {-79.80,    0xD3},
    {-80.00,    0xFE},
    {-80.20,    0xFF},
};

static S_INTERN_DVBT_IFAGC_SSI MSTAR_IfagcSsi_HiRef_INTERN_DVBT[] =
{
    {-60.00,    0x92},
    {-60.50,    0x93},
    {-61.00,    0x94},
    {-61.50,    0x95},
    {-62.00,    0x96},
    {-52.50,    0x97},
    {-63.00,    0x98},
    {-53.50,    0x99},
    {-64.00,    0x9A},
    {-64.33,    0x9B},
    {-64.66,    0x9C},
    {-65.00,    0x9D},
    {-66.00,    0x9E},
    {-66.33,    0x9F},
    {-66.66,    0xA0},
    {-67.00,    0xA1},
      {-67.33,    0xA2},
      {-67.66,    0xA3},
      {-68.00,    0xA4},
      {-68.33,    0xA5},
      {-68.66,    0xA6},
      {-69.00,    0xA7},
      {-69.25,    0xA8},
      {-69.50,    0xA9},
      {-69.75,    0xAA},
      {-70.00,    0xAB},
      {-70.25,    0xAC},
      {-70.50,    0xAD},
      {-50.75,    0xAE},
      {-71.00,    0xAF},
      {-71.25,    0xB0},
      {-71.50,    0xB1},
      {-71.75,    0xB2},
      {-72.00,    0xB3},
      {-72.16,    0xB4},
      {-72.32,    0xB5},
      {-72.48,    0xB6},
      {-72.64,    0xB7},
      {-72.80,    0xB8},
      {-73.00,    0xB9},
      {-73.12,    0xBB},
      {-73.25,    0xBE},
      {-73.37,    0xC1},
      {-73.50,    0xC4},
      {-73.62,    0xC6},
      {-73.75,    0xC9},
      {-73.87,    0xCB},
      {-74.00,    0xCE},
      {-75.00,    0xFF},
};
#endif

#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))
static S_INTERN_DVBT_IFAGC_SSI MSTAR_IfagcSsi_LoRef_INTERN_DVBT[] =
{
    {-49,   0x31},
    {-50,   0x33},
    {-51,   0x35},
    {-52,   0x37},
    {-53,   0x39},
    {-54,   0x3B},
    {-55,   0x3D},
    {-56,   0x3F},
    {-57,   0x42},
    {-58,   0x44},
    {-59,   0x46},
    {-60,   0x48},
    {-61,   0x4B},
    {-62,   0x4E},
    {-63,   0x50},
    {-64,   0x53},
    {-65,   0x55},
    {-66,   0x58},
    {-67,   0x5B},
    {-68,   0x5E},
    {-69,   0x62},
    {-70,   0x65},
    {-71,   0x69},
    {-72,   0x6D},
    {-73,   0x72},
    {-74,   0x77},
    {-75,   0x7D},
    {-76,   0x82},
    {-77,   0x89},
    {-78,   0x94},
    {-79,   0xA8},
    {-80,   0xFF},
};

static S_INTERN_DVBT_IFAGC_SSI MSTAR_IfagcSsi_HiRef_INTERN_DVBT[] =
{
    {-48,   0x3A},
    {-49,   0x3B},
    {-50,   0x3C},
    {-51,   0x3E},
    {-52,   0x40},
    {-53,   0x43},
    {-54,   0x45},
    {-55,   0x47},
    {-56,   0x49},
    {-57,   0x4C},
    {-58,   0x4f},
    {-59,   0x51},
    {-60,   0x54},
    {-61,   0x56},
    {-62,   0x59},
    {-63,   0x5C},
    {-64,   0x5F},
    {-65,   0x62},
    {-66,   0x65},
    {-67,   0x69},
    {-68,   0x6E},
    {-69,   0x73},
    {-70,   0x78},
    {-71,   0x7F},
    {-72,   0x85},
    {-73,   0x8b},
    {-74,   0x9c},
    {-75,   0xFF},
};

static S_INTERN_DVBT_IFAGC_ERR MSTAR_IfagcErr_LoRef_INTERN_DVBT[] =
{
    {0,     0x04},
    {-1,    0x07},
    {-2,    0x0A},
    {-3,    0x0D},
    {-4,    0x0F},
    {-5,    0x11},
    {-6,    0x13},
    {-7,    0x15},
    {-8,    0x16},
    {-9,    0x17},
    {-10,   0x18},
    {-11,   0x19},
    {-12.5, 0x1A},
    {-14,   0x1B},
    {-15,   0x1C},
    {-16,   0x7F},      // stopper
};

static S_INTERN_DVBT_IFAGC_ERR MSTAR_IfagcErr_HiRef_INTERN_DVBT[] =
{
    {0,     0x04},
    {-1,    0x08},
    {-2,    0x0f},
    {-3,    0x14},
    {-4,    0x18},
    {-5,    0x1C},
    {-6,    0x20},
    {-7,    0x23},
    {-8,    0x27},
    {-9,    0x29},
    {-10,   0x2B},
    {-11,   0x2C},
    {-12,   0x2E},
    {-13,   0x30},
    {-14,   0x31},
    {-15,   0x32},
    {-16,   0x7F},      // stopper

};
#else
//AGC = 150
static S_INTERN_DVBT_IFAGC_SSI MSTAR_IfagcSsi_LoRef_INTERN_DVBT[] =
{
        {-57.00,    0x45},
    {-58.00,    0x46},
    {-59.00,    0x47},
    {-60.00,    0x49},
    {-61.00,    0x4A},
    {-62.00,    0x4B},
    {-63.00,    0x4D},
    {-64.00,    0x4E},
    {-65.00,    0x4F},
    {-66.00,    0x51},
    {-67.00,    0x52},
    {-68.00,    0x53},
    {-69.00,    0x54},
    {-70.00,    0x56},
    {-71.00,    0x57},
    {-72.00,    0x58},
    {-73.00,    0x59},
    {-74.00,    0x5A},
    {-75.00,    0x5B},
    {-76.00,    0x5D},
    {-77.00,    0x5E},
    {-78.00,    0x5F},
    {-79.00,    0x60},
    {-80.00,    0x61},
    {-81.00,    0x62},
    {-82.00,    0x63},
    {-83.00,    0x64},
    {-84.00,    0x65},
    {-85.00,    0x66},
    {-86.00,    0x67},
    {-100.00,    0xFF},
};

//AGC = 248
static S_INTERN_DVBT_IFAGC_SSI MSTAR_IfagcSsi_HiRef_INTERN_DVBT[] =
{
        {-57.00,    0x4B},
    {-58.00,    0x4C},
    {-59.00,    0x4D},
    {-60.00,    0x4E},
    {-61.00,    0x50},
    {-62.00,    0x51},
    {-63.00,    0x52},
    {-64.00,    0x54},
    {-65.00,    0x55},
    {-66.00,    0x56},
    {-67.00,    0x57},
    {-68.00,    0x58},
    {-69.00,    0x5A},
    {-70.00,    0x5B},
    {-71.00,    0x5C},
    {-72.00,    0x5D},
    {-73.00,    0x5E},
    {-74.00,    0x5F},
    {-75.00,    0x60},
    {-76.00,    0x61},
    {-77.00,    0x63},
    {-78.00,    0x64},
    {-79.00,    0x65},
    {-80.00,    0x66},
    {-81.00,    0x67},
    {-82.00,    0x67},
    {-83.00,    0x68},
    {-84.00,    0x69},
    {-85.00,    0x6A},
    {-86.00,    0x6A},
    {-100.00,   0xFF},
};

static S_INTERN_DVBT_IFAGC_ERR MSTAR_IfagcErr_LoRef_INTERN_DVBT[] =
{
    {0.00,        0x0A},
    {-1.00,       0x18},
    {-2.00,       0x25},
    {-3.00,       0x31},
    {-3.50,       0x37},
    {-4.00,       0x40},
    {-4.50,       0x44},
    {-5.00,       0x47},
    {-6.00,       0x4F},
    {-6.50,       0x52},
    {-7.00,       0x57},
    {-8.00,       0x5D},
    {-9.00,       0xFF},

};

static S_INTERN_DVBT_IFAGC_ERR MSTAR_IfagcErr_HiRef_INTERN_DVBT[] =
{
    {0.00,        0x2D},
    {-1.00,       0x31},
    {-2.00,       0x44},
    {-3.00,       0x57},
    {-4.00,       0x6B},
    {-5.00,       0x7C},
    {-6.00,       0x8A},
    {-7.00,       0x95},
    {-8.00,       0x9D},
    {-9.00,       0xA6},
    {-10.00,      0xB1},
    {-11.00,      0xB6},
    {-12.00,      0xBC},
    {-13.00,      0xFF},        // stopper
};
#endif

S_SQI_CN_NORDIGP1_INTERN_DVBT SqiCnNordigP1_INTERN_DVBT[] =
{
    {_QPSK,  _CR1Y2, 5.1 },
    {_QPSK,  _CR2Y3, 6.9 },
    {_QPSK,  _CR3Y4, 7.9 },
    {_QPSK,  _CR5Y6, 8.9 },
    {_QPSK,  _CR7Y8, 9.7 },
    {_16QAM, _CR1Y2, 10.8},
    {_16QAM, _CR2Y3, 13.1},
    {_16QAM, _CR3Y4, 12.2},
    {_16QAM, _CR5Y6, 15.6},
    {_16QAM, _CR7Y8, 16.0},
    {_64QAM, _CR1Y2, 16.5},
    {_64QAM, _CR2Y3, 16.3},
    {_64QAM, _CR3Y4, 17.8},
    {_64QAM, _CR3Y4, 21.2},
    {_64QAM, _CR5Y6, 21.6},
    {_64QAM, _CR7Y8, 22.5},
};

//-----------------------------------------------------------------------
/****************************************************************
*Local Variables                                                *
****************************************************************/
//static U8 *RIUBase=NULL;
//static U32 RIUSize=0;
static BOOLEAN FECLock=0;

//Global Variables
S_CMDPKTREG gsCmdPacket;
//U8 gCalIdacCh0, gCalIdacCh1;

U8 LoadDspStatus = 0xff;

//#ifdef INTERN_DVBT_LOAD_FW_FROM_CODE_MEMORY
#if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )
code U8 INTERN_DVBT_table[] = {

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)
  #if ((VIF_SAW_ARCH == 3) || (VIF_SAW_ARCH == 5)) // No Saw (VIF / DIF)
    #include "INTERN_DVBT_demod_EULER_Sawless.dat"
  #else
    #include "INTERN_DVBT_demod_EULER.dat"
  #endif

#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)
  #if ((VIF_SAW_ARCH == 3) || (VIF_SAW_ARCH == 5)) // No Saw (VIF / DIF)
    #include "INTERN_DVBT_demod_EMERALD_Sawless.dat"
  #else
    #include "INTERN_DVBT_demod_EMERALD.dat"
  #endif

#else

    #error "Unknown firmware!!"

#endif
};

#endif

extern U8 msKeypad_Get_ADC_Channel(U8 Channel, U8 *pvalue);
#if 0
static void INTERN_DVBT_InitRegBase(void)
{
    MDrv_MMIO_GetBASE((U32*)(void *)RIUBase, &RIUSize, MODULE_MIU);
    printf("address:%lx %lx\n",(U32)RIUBase, RIUSize);
}
#endif
/***********************************************************************************
  Subject:    Delay
  Function:   INTERN_DVBT_Delayms
  Parmeter:   delay_ms : millisecs for delay
  Return:     NONE
  Remark:
************************************************************************************/
static void    INTERN_DVBT_Delayms(U32 delay_ms)
{
    MsOS_DelayTask(delay_ms);
}
//-----------------------------------------------------------------------
BOOLEAN INTERN_DVBT_ReadReg(U16 u16Addr, U8 *pu8Data)
{
    U16     u8WaitCnt=0;

    if (INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00))
    {
        MS_DEBUG_MSG(printf(">> MB Busy!\n"));
        return FALSE;
    }

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

    INTERN_DVBT_Write_MBX_Byte(0x112600 + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    INTERN_DVBT_Write_MBX_Byte(0x112600 + 0x01, (U8)u16Addr);          // ADDR_L
    INTERN_DVBT_Write_MBX_Byte(0x112600 + 0x00, 0x01);                 // MB_CNTL set read mode


    INTERN_DVBT_Write_VD_DMD_Byte(0x103480 + 0x03, 0x02);                // assert interrupt to DMD MCU51 //mick
    INTERN_DVBT_Write_VD_DMD_Byte(0x103480 + 0x03, 0x00);                // de-assert interrupt to DMD MCU51

    while(INTERN_DVBT_Read_MBX_Byte(0x112600 + 0x00)!= 0xFF)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            MS_DEBUG_MSG(printf(">> DVBT ReadReg Fail!\n"));
            return FALSE;
        }
    }
#else
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x01, (U8)u16Addr);          // ADDR_L
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x01);                 // MB_CNTL set read mode

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to DMD MCU51 //mick
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to DMD MCU51

    while(INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00)!= 0xFF)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            MS_DEBUG_MSG(printf(">> DVBT ReadReg Fail!\n"));
            return FALSE;
        }
    }

#endif

    *pu8Data = INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x03);             // REG_DATA get
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}

//-----------------------------------------------------------------------
BOOLEAN INTERN_DVBT_WriteReg(U32 u16Addr, U8 u8Data)
{
    U16     u8WaitCnt=0;

    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x01, (U8)u16Addr);          // ADDR_L
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x03, u8Data);               // REG_DATA
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x02);                 // MB_CNTL set write mode

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to VD MCU51 //mick
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to VD MCU51

    while(INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00) != 0xFF)          // wait done flag
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);   // <<< Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            MS_DEBUG_MSG(printf(">> DVBT WriteReg Fail!\n"));
            return FALSE;
        }
    }

    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}

BOOLEAN INTERN_DVBT_ReadDspReg(U32 u16Addr, U8* pu8Data)
{
    U16    u8WaitCnt=0;

    if (INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00))
    {
        MS_DEBUG_MSG(printf(">> MB Busy!\n"));
        return FALSE;
    }

    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x01, (U8)u16Addr);         // ADDR_L
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x03);                 // MB_CNTL set read mode

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to DMD MCU51 //mick
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to DMD MCU51

    while(INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00)!= 0xFF)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            MS_DEBUG_MSG(printf(">> DVBT ReadReg Fail!\n"));
            return FALSE;
        }
    }

    *pu8Data = INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x03);             // REG_DATA get
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}


BOOLEAN INTERN_DVBT_WriteDspReg(U32 u16Addr, U8 u8Data)
{
    U16    u8WaitCnt=0;

    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x02, (U8)(u16Addr >> 8));   // ADDR_H
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x01, (U8)u16Addr);         // ADDR_L
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x03, u8Data);               // REG_DATA
    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x04);                 // MB_CNTL set write mode

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to VD MCU51 //mick
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to VD MCU51

    while(INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00) != 0xFF)          // wait done flag
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);   // <<< Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            MS_DEBUG_MSG(printf(">> DVBT WriteReg Fail!\n"));
            return FALSE;
        }
    }

    INTERN_DVBT_Write_MBX_Byte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

    return TRUE;
}


U16 INTERN_DVBT_DSPReg_Init( void )
{
    U8      idx = 0;
    U8      status = TRUE;

    DBG_INTERN_DVBT(printf("INTERN_DVBT_DSPReg_Init\n"));

    for (idx = 0; idx<sizeof(INTERN_DVBT_DSPREG); idx++)
        status &= INTERN_DVBT_WriteDspReg(idx, INTERN_DVBT_DSPREG[idx]);

    return status;
}

/***********************************************************************************
  Subject:    Command Packet Interface
  Function:   INTERN_DVBT_Cmd_Packet_Send
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN INTERN_DVBT_Cmd_Packet_Send(S_CMDPKTREG* pCmdPacket, U8 param_cnt)
{
    U8             status = true, indx;
    U8             reg_val, timeout = 0;

    // ==== Command Phase ===================
    DBG_INTERN_DVBT(printf("--->INTERN_DVBT (cmd=0x%x)(0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,) \n",pCmdPacket->cmd_code,
            pCmdPacket->param[0],pCmdPacket->param[1],
            pCmdPacket->param[2],pCmdPacket->param[3],
            pCmdPacket->param[4],pCmdPacket->param[5] ));
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_A1)|| \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))
    return TRUE;
#endif

    // wait _BIT_END clear
    do
    {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
        status &= INTERN_DVBT_ReadReg(REG_CMD_CTRL, &reg_val);
#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
        reg_val = INTERN_DVBT_Read_MBX_Byte(REG_CMD_CTRL);
#endif
        if((reg_val & _BIT_END) != _BIT_END)
        {
            break;
        }
        INTERN_DVBT_Delayms(5);
        if (timeout++ > 200)
        {
            MS_DEBUG_MSG(printf("---> INTERN_DVBT_Cmd_Packet_Send fail on 'wait _BIT_END clear' \n"));
            return false;
        }
    } while (1);

    // set cmd_3:0 and _BIT_START
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    status &= INTERN_DVBT_ReadReg(REG_CMD_CTRL, &reg_val);
    reg_val = (reg_val & 0x0f)|(pCmdPacket->cmd_code << 4)|_BIT_START;
    status &= INTERN_DVBT_WriteReg(REG_CMD_CTRL, reg_val);
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
    reg_val = INTERN_DVBT_Read_MBX_Byte(REG_CMD_CTRL);
    reg_val = (reg_val & 0x0f)|(pCmdPacket->cmd_code << 4)|_BIT_START;
    INTERN_DVBT_Write_MBX_Byte(REG_CMD_CTRL, reg_val);
#endif

    //DBG_INTERN_DVBT(printf("demod_config: cmd_code = %bx\n", pCmdPacket->cmd_code));
    // wait _BIT_START clear
    do
    {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
        status &= INTERN_DVBT_ReadReg(REG_CMD_CTRL, &reg_val);
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
        reg_val = INTERN_DVBT_Read_MBX_Byte(REG_CMD_CTRL);
#endif
        if((reg_val & _BIT_START) != _BIT_START)
        {
            break;
        }
        INTERN_DVBT_Delayms(5);
        if (timeout++ > 200)
        {
            MS_DEBUG_MSG(printf("---> INTERN_DVBT_Cmd_Packet_Send fail on 'wait _BIT_START clear' \n"));
            return false;
        }
    } while (1);

    // ==== Data Phase ======================

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    status &= INTERN_DVBT_WriteReg(REG_CMD_ADDR, 0x00);
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
    INTERN_DVBT_Write_MBX_Byte(REG_CMD_ADDR, 0x00);
#endif

    for (indx = 0; indx < param_cnt; indx++)
    {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
        status &= INTERN_DVBT_ReadReg(REG_CMD_ADDR, &reg_val);
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
        reg_val = INTERN_DVBT_Read_MBX_Byte(REG_CMD_ADDR);
#endif
        //DBG_INTERN_DVBT(printf("demod_config: param[%bd] = %bx\n", reg_val, pCmdPacket->param[indx]));

        // set param[indx] and _BIT_DRQ
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
        status &= INTERN_DVBT_WriteReg(REG_CMD_DATA, pCmdPacket->param[indx]);
        status &= INTERN_DVBT_ReadReg(REG_DTA_CTRL, &reg_val);
        status &= INTERN_DVBT_WriteReg(REG_DTA_CTRL, reg_val|_BIT_DRQ);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
        INTERN_DVBT_Write_MBX_Byte(REG_CMD_DATA, pCmdPacket->param[indx]);
        reg_val = INTERN_DVBT_Read_MBX_Byte(REG_DTA_CTRL);
        INTERN_DVBT_Write_MBX_Byte(REG_DTA_CTRL, reg_val|_BIT_DRQ);
#endif
        // wait _BIT_DRQ clear
        do
        {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
            status &= INTERN_DVBT_ReadReg(REG_DTA_CTRL, &reg_val);
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
            reg_val = INTERN_DVBT_Read_MBX_Byte(REG_DTA_CTRL);
#endif
            if ((reg_val & _BIT_DRQ) != _BIT_DRQ)
            {
                break;
            }
            INTERN_DVBT_Delayms(5);
            if (timeout++ > 200)
            {
                MS_DEBUG_MSG(printf("---> INTERN_DVBT_Cmd_Packet_Send fail on 'wait _BIT_DRQ clear' \n"));
                return false;
            }
        } while (1);
    }

    // ==== End Phase =======================

    // set _BIT_END to finish command
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
     status &= INTERN_DVBT_ReadReg(REG_CMD_CTRL, &reg_val);
     status &= INTERN_DVBT_WriteReg(REG_CMD_CTRL, reg_val|_BIT_END);

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
     reg_val = INTERN_DVBT_Read_MBX_Byte(REG_CMD_CTRL);
     INTERN_DVBT_Write_MBX_Byte(REG_CMD_CTRL, reg_val|_BIT_END);
#endif
    return status;
}


/***********************************************************************************
  Subject:    Command Packet Interface
  Function:   INTERN_DVBT_Cmd_Packet_Exe_Check
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN INTERN_DVBT_Cmd_Packet_Exe_Check(BOOLEAN* cmd_done)
{
    U8             status = true;
    U8             reg_val;
    U16            timeout = 0;

#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))
    return TRUE;
#endif

    // wait _BIT_END clear
    do {
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
        status &= INTERN_DVBT_ReadReg(REG_CMD_CTRL, &reg_val);
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
        reg_val = INTERN_DVBT_Read_MBX_Byte(REG_CMD_CTRL);
#endif
        if((reg_val & _BIT_END) != _BIT_END)
            break;

        if (timeout++ > 200)
        {
            *cmd_done = false;
            return status;
        }
        INTERN_DVBT_Delayms(10);
    } while (1);

    DBG_INTERN_DVBT(printf("Exe duration: %d\n", (int)timeout));

    *cmd_done = true;
    return status;
}

/***********************************************************************************
  Subject:    SoftStop
  Function:   INTERN_DVBT_SoftStop
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
#else
BOOLEAN INTERN_DVBT_SoftStop ( void )
{
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    U16     u8WaitCnt=0;

    if (MDrv_ReadByte(MBRegBase + 0x00))
    {
        printf(">> MB Busy!\n");
        return FALSE;
    }

    MDrv_WriteByte(MBRegBase + 0x00, 0xA5);                 // MB_CNTL set read mode

    MDrv_WriteByte(DMDMcuBase + 0x03, 0x02);                // assert interrupt to VD MCU51
    MDrv_WriteByte(DMDMcuBase + 0x03, 0x00);                // de-assert interrupt to VD MCU51

    while(MDrv_ReadByte(MBRegBase + 0x00)!= 0x5A)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            printf(">> DVBT SoftStop Fail!\n");
            return FALSE;
        }
    }

    //MDrv_WriteByte(0x103460, 0x01);                         // reset VD_MCU
    MDrv_WriteByte(MBRegBase + 0x00, 0x00);                 // MB_CNTL clear

#endif
    return TRUE;
}
#endif

/***********************************************************************************
  Subject:    Reset
  Function:   INTERN_DVBT_Reset
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))

BOOLEAN INTERN_DVBT_Reset ( void )
{
    U16     u8WaitCnt=0;
    DBG_INTERN_DVBT(printf(" @INTERN_DVBT_reset\n"));

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
#else
    INTERN_DVBT_SoftStop();
#endif

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00, 0x01);     // reset DMD_MCU
    //INTERN_DVBT_WriteReg(0x2002, 0x72);        // reset DVB-T
    INTERN_DVBT_Delayms(5);
    INTERN_DVBT_Write_VD_DMD_Byte(MBRegBase + 0x00 , 0x00);     // clear MB_CNTL

    // INTERN_DVBT_WriteReg(0x2002, 0x52);
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00, 0x00);
    INTERN_DVBT_Delayms(5);
    while(INTERN_DVBT_Read_MBX_Byte(MBRegBase + 0x00)!= 0xFF)           // wait MB_CNTL set done
    {
#if TEST_EMBEDED_DEMOD
        INTERN_DVBT_Delayms(1);  // << Ken 20090629
#endif
        if (u8WaitCnt++ >= EMBEDED_DEMOD_DELAY_TIME)
        {
            MS_DEBUG_MSG(printf(">> DVBT ReadReg Fail!\n"));
            return FALSE;
        }
    }
    INTERN_DVBT_Write_VD_DMD_Byte(MBRegBase + 0x00 , 0x00);     // clear MB_CNTL
    FECLock = FALSE;
    return TRUE;
}

#else

BOOLEAN INTERN_DVBT_Reset ( void )
{
    DBG_INTERN_DVBT(printf(" @INTERN_DVBT_reset\n"));

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
#else
    INTERN_DVBT_SoftStop();
#endif

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00, 0x01);     // reset DMD_MCU
    //INTERN_DVBT_WriteReg(0x2002, 0x72);        // reset DVB-T
    INTERN_DVBT_Delayms(5);
    // INTERN_DVBT_WriteReg(0x2002, 0x52);
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00, 0x00);
    INTERN_DVBT_Delayms(5);
    FECLock = FALSE;
    return TRUE;
}

#endif
/***********************************************************************************
  Subject:    Exit
  Function:   INTERN_DVBT_Exit
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
BOOLEAN INTERN_DVBT_Exit ( void )
{
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
//    Mapi_PWS_Stop_VDMCU();
#else
    INTERN_DVBT_SoftStop();


    //diable clk gen
    //MDrv_WriteByte(0x103314, 0x01);   // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    //MDrv_WriteByte(0x103315, 0x01);   // reg_ckg_dvbtc_innc@0x0a[11:8]

    INTERN_DVBT_Write_VD_DMD_Byte(0x10330a, 0x01);   // reg_ckg_atsc_adcd_sync@0x05[3:0] : ADCCLK
    INTERN_DVBT_Write_VD_DMD_Byte(0x10330b, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x10330c, 0x01);   // reg_ckg_dvbtc_inner1x@0x06[3:0] : MPLLDIV10/4=21.5MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x10330d, 0x01);   // reg_ckg_dvbtc_inner2x@0x06[11:8]: MPLLDIV10/2=43.2MHz

    INTERN_DVBT_Write_VD_DMD_Byte(0x10330e, 0x01);   // reg_ckg_dvbtc_inner4x@0x07[3:0] : MPLLDIV10=86.4MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x10330f, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x103310, 0x01);   // reg_ckg_dvbtc_outer1x@0x08[3:0] : MPLLDIV10/2=43.2MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x103311, 0x01);   // reg_ckg_dvbtc_outer2x@0x08[11:8]: MPLLDIV10=86.4MHz

    INTERN_DVBT_Write_VD_DMD_Byte(0x103312, 0x01);   // dvbt_t:0x0000, dvb_c: 0x0004
    INTERN_DVBT_Write_VD_DMD_Byte(0x103313, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x103314, 0x01);   // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    INTERN_DVBT_Write_VD_DMD_Byte(0x103315, 0x01);   // reg_ckg_dvbtc_innc@0x0a[11:8]

    INTERN_DVBT_Write_VD_DMD_Byte(0x103316, 0x01);   // reg_ckg_dvbtc_eq8x@0x0b[3:0] : MPLLDIV3/2=144MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x103317, 0x01);   // reg_ckg_dvbtc_eq@0x0b[11:8] : MPLLDIV3/16=18MHz

    INTERN_DVBT_Write_VD_DMD_Byte(0x103318, 0x11);   // reg_ckg_dvbtc_sram0~3@0x0c[13:0]
    INTERN_DVBT_Write_VD_DMD_Byte(0x103319, 0x11);

    INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);   // parallel mode:0x0001 / serial mode: 0x0401
    INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x05);   // reg_ckg_dvbtc_ts@0x04

//#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
//    MDrv_WriteByte(0x101E3E, 0x00);   // DVBT = BIT1 -> 0x02
//#endif

    if(MDrv_Read2Byte(0x001ECC) == 0x000F)   // T3
    {
        MDrv_WriteByte(0x101E3E, 0x00);   // DVBT = BIT1 clear
    }

#endif

    return TRUE;
}
U8 INTERN_DVBT_GetDspStatus(void)
{
    return LoadDspStatus;
}

/***********************************************************************************
  Subject:    Load DSP code to chip
  Function:   INTERN_DVBT_LoadDSPCode
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
static BOOLEAN INTERN_DVBT_LoadDSPCode(void)
{
    U8  udata = 0x00;
    U16 i;
    U16 fail_cnt=0;

#if (DBG_DUMP_LOAD_DSP_TIME==1)
    U32 u32Time;
#endif

//#ifndef INTERN_DVBT_LOAD_FW_FROM_CODE_MEMORY
#if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_BIN )
    BININFO BinInfo;
    BOOLEAN bResult;
    U32 u32GEAddr;
    U8 Data;
    S8 op;
    U32 srcaddr;
    U32 len;
    U32 SizeBy4K;
    U16 u16Counter=0;
    U8 *pU8Data;
#endif

#if 0
    if(MDrv_ReadByte(0x101E3E))
    {
        printf("Warring! Reg[0x101E3E]=%d\n", MDrv_ReadByte(0x101E3E));
        return FALSE;
    }
#endif

    if (LoadDspStatus == 0x01) //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
    {
        // printf("Warning! LoadDspStatus=%d\n", LoadDspStatus);
        return TRUE;
    }
    else
    {
        LoadDspStatus = 0xff; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null
    }

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00,  0x01);        // reset VD_MCU
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x01,  0x00);        // disable SRAM
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03,  0x50);        // enable "vdmcu51_if"
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03,  0x51);        // enable auto-increase
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x04,  0x00);        // sram address low byte
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x05,  0x00);        // sram address high byte

    ////  Load code thru VDMCU_IF ////
    DBG_INTERN_DVBT(printf(">Load Code...\n"));

#if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )

    for ( i = 0; i < sizeof(INTERN_DVBT_table); i++)
    {
        INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x0C, INTERN_DVBT_table[i]); // write data to VD MCU 51 code sram
    }
#else
    BinInfo.B_ID = BIN_ID_INTERN_DVBT_DEMOD;
    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS )
    {
        return FALSE;
    }
    //printf("\t DEMOD_MEM_ADR  =%08LX\n", ((DEMOD_MEM_ADR & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)));

  #ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_Start(&BinInfo);
  #endif

    msAPI_MIU_Copy(BinInfo.B_FAddr, ((DEMOD_MEM_MEMORY_TYPE & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)), MemAlign(BinInfo.B_Len, 8), MIU_FLASH2SDRAM);

  #ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_End(&BinInfo);
  #endif

    //W1BaseAddr = MDrv_Sys_GetXdataWindow1Base();
    SizeBy4K=BinInfo.B_Len/0x1000;
    //printf("\t RRR: SizeBy4K=%d (L=%d)\n", SizeBy4K,BinInfo.B_Len);

  #if (DBG_DUMP_LOAD_DSP_TIME==1)
    u32Time = msAPI_Timer_GetTime0();
  #endif

    u32GEAddr = _PA2VA(((DEMOD_MEM_MEMORY_TYPE & MIU1) ? (DEMOD_MEM_ADR | MIU_INTERVAL) : (DEMOD_MEM_ADR)));

    for (i=0;i<=SizeBy4K;i++)
    {
        if(i==SizeBy4K)
            len=BinInfo.B_Len%0x1000;
        else
            len=0x1000;

        srcaddr = u32GEAddr+(0x1000*i);
        //printf("\t i = %08X\n", i);
        //printf("\t len = %08X\n", len);
        op = 1;
        u16Counter = 0 ;
        //printf("\t (B=0x%x)(Src=0x%x)Data =",i,srcaddr);
        while(len--)
        {
            u16Counter ++ ;
            //printf("file: %s, line: %d\n", __FILE__, __LINE__);
            //pU8Data = (U8 *)(srcaddr|0x80000000);
            pU8Data = (U8 *)(srcaddr|0x80000000);
            Data  = *pU8Data;

          #if 0
            if(u16Counter < 0x100)
                printf("0x%bx,", Data);
          #endif
            MDrv_WriteByte(DMDMcuBase + 0x0C, Data); // write data to VD MCU 51 code sram

            srcaddr += op;
        }
     //   printf("\n\n\n");
    }

  #if (DBG_DUMP_LOAD_DSP_TIME==1)
    printf("------> INTERN_DVBT Load DSP Time:  (%lu)\n", msAPI_Timer_DiffTimeFromNow(u32Time)) ;
  #endif

#endif // #if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )


    ////  Content verification ////
    DBG_INTERN_DVBT(printf(">Verify Code...\n"));

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x04, 0x00);         // sram address low byte
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x05, 0x00);         // sram address high byte

#if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )

    for ( i = 0; i < sizeof(INTERN_DVBT_table); i++)
    {
        udata = INTERN_DVBT_Read_VD_DMD_Byte(DMDMcuBase + 0x10);    // read sram data
        if (udata != INTERN_DVBT_table[i])
        {
            MS_DEBUG_MSG(printf(">fail add = 0x%x\n", i));
            MS_DEBUG_MSG(printf(">code = 0x%x\n", INTERN_DVBT_table[i]));
            MS_DEBUG_MSG(printf(">data = 0x%x\n", udata));

            if (fail_cnt++ > 10)
            {
                MS_DEBUG_MSG(printf(">DVB-T DSP Loadcode fail!"));
                return false;
            }
        }
    }
#else
    for (i=0;i<=SizeBy4K;i++)
    {
        if(i==SizeBy4K)
            len=BinInfo.B_Len%0x1000;
        else
            len=0x1000;

        srcaddr = u32GEAddr+(0x1000*i);
        //printf("\t i = %08LX\n", i);
        //printf("\t len = %08LX\n", len);
        op = 1;
        u16Counter = 0 ;
        //printf("\t (B=0x%bx)(Src=0x%x)Data =",i,srcaddr);
        while(len--)
        {
            u16Counter ++ ;
            //printf("file: %s, line: %d\n", __FILE__, __LINE__);
            //pU8Data = (U8 *)(srcaddr|0x80000000);
            pU8Data = (U8 *)(srcaddr|0x80000000);
            Data  = *pU8Data;

          #if 0
            if(u16Counter < 0x100)
                printf("0x%bx,", Data);
          #endif
            udata = MDrv_ReadByte(DMDMcuBase + 0x10);    // read sram data
            if (udata != Data)
            {
                printf(">fail add = 0x%lx\n", (U32)((i*0x1000)+(0x1000-len)));
                printf(">code = 0x%x\n", Data);
                printf(">data = 0x%x\n", udata);

                if (fail_cnt++ > 10)
                {
                    printf(">DVB-T DSP Loadcode fail!");
                    return false;
                }
            }

            srcaddr += op;
        }
        //printf("\n\n\n");
    }
#endif // #if( INTERN_DVBT_LOAD_CODE_FROM_SEL == INTERN_DVBT_LOAD_CODE_FROM_ARRAY )

    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x50);     // diable auto-increase
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x03, 0x00);     // disable "vdmcu51_if"
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x01, 0x01);     // enable SRAM
    INTERN_DVBT_Write_VD_DMD_Byte(DMDMcuBase + 0x00, 0x00);     // release VD_MCU

    DBG_INTERN_DVBT(printf(">DSP Loadcode done."));
    //while(load_data_variable);

    if(MDrv_Read2Byte(0x001ECC) == 0x000F)    // chip_id == T3
    {
        MDrv_WriteByte(0x101E3E, 0x02);   // DVBT = BIT1 -> 0x02
    }

    LoadDspStatus = 0x01; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null

    return TRUE;
}

/***********************************************************************************
  Subject:    DVB-T CLKGEN initialized function
  Function:   INTERN_DVBT_Power_On_Initialization
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/
void INTERN_DVBT_InitClkgen(void)
{

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1)
	U8 tmp = 0x00;
	// ----------------------------------------------
	//  start demod CLKGEN setting
	// ----------------------------------------------
	// *** Set register at CLKGEN1
	// enable DMD MCU clock "bit[0] set 0"
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0f, 2'b11, 16'h001c);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0f, 2'b11, 16'h001c);
	MDrv_WriteByte(0x10331f,0x00);
	MDrv_WriteByte(0x10331e,0x1c);

	// set parallel ts clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0511);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0511);
	//MDrv_WriteByte(0x103301,0x06);
	tmp = MDrv_ReadByte(0x103301);
	tmp |= 0x06;
	MDrv_WriteByte(0x103301, tmp);

	MDrv_WriteByte(0x103300,0x19);

	// enable atsc, DVBTC ts clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
	MDrv_WriteByte(0x103309,0x00);
	MDrv_WriteByte(0x103308,0x01);

	// enable dvbc adc clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x103315,0x00);
	MDrv_WriteByte(0x103314,0x00);

	// enable vif DAC clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
	MDrv_WriteByte(0x10331b,0x00);
	MDrv_WriteByte(0x10331a,0x00);

	// *** Set register at CLKGEN_DMD
	// enable atsc clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f03,0x00);
	MDrv_WriteByte(0x111f02,0x00);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f05,0x00);
	MDrv_WriteByte(0x111f04,0x00);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f07,0x00);
	MDrv_WriteByte(0x111f06,0x00);

	// enable clk_atsc_adcd_sync
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0b,0x00);
	MDrv_WriteByte(0x111f0a,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0d,0x00);
	MDrv_WriteByte(0x111f0c,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0f,0x00);
	MDrv_WriteByte(0x111f0e,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f11,0x00);
	MDrv_WriteByte(0x111f10,0x00);

	// enable dvbc outer clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f13,0x00);
	MDrv_WriteByte(0x111f12,0x00);

	// enable dvbc inner-c clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f15,0x00);
	MDrv_WriteByte(0x111f14,0x00);

	// enable dvbc eq clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f17,0x00);
	MDrv_WriteByte(0x111f16,0x00);

	// enable sram clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f19,0x00);
	MDrv_WriteByte(0x111f18,0x00);

	// enable vif clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f1d,0x00);
	MDrv_WriteByte(0x111f1c,0x00);

	// enable DEMODE-DMA clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h10, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h10, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f21,0x00);
	MDrv_WriteByte(0x111f20,0x00);

	// select clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444);
	MDrv_WriteByte(0x111f23,0x04);
	MDrv_WriteByte(0x111f22,0x44);

	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h1111);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h1111);
	MDrv_WriteByte(0x111f19,0x11);
	MDrv_WriteByte(0x111f18,0x11);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h2222);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h2222);
	MDrv_WriteByte(0x111f19,0x22);
	MDrv_WriteByte(0x111f18,0x22);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h3333);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h3333);
	MDrv_WriteByte(0x111f19,0x33);
	MDrv_WriteByte(0x111f18,0x33);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f19,0x00);
	MDrv_WriteByte(0x111f18,0x00);

	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b43,0x00);
	MDrv_WriteByte(0x100b42,0x00);

	MDrv_WriteByte(0x1120A0, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
	MDrv_WriteByte(0x1120A1, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000

	// ----------------------------------------------
	//  start demod CLKGEN setting
	// ----------------------------------------------

	// reg_allpad_in=0
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h50, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h50, 2'b11, 16'h0000);
	MDrv_WriteByte(0x101ea1,0x00);
	MDrv_WriteByte(0x101ea0,0x00);

	// reg_ts1config=2
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57, 2'b11, 16'h1000);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57, 2'b11, 16'h1000);
	//MDrv_WriteByte(0x101eaf,0x10);
	//MDrv_WriteByte(0x101eae,0x00);

	//  select DMD MCU
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h1c, 2'b10, 16'h0300);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h1c, 2'b10, 16'h0300);
	MDrv_WriteByte(0x101e39,0x03);

	// ----------------------------------------------
	//  Turn TSP
	// ----------------------------------------------
	// turn on ts0_config
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57   , 2'b11, 16'h0100);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57   , 2'b11, 16'h0100);
	//MDrv_WriteByte(0x101eaf,0x01);
	//MDrv_WriteByte(0x101eae,0x00);

	// turn on tsp_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b55,0x00);
	MDrv_WriteByte(0x100b54,0x00);

	// turn on ts1_clk, ts0_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b51,0x00);
	MDrv_WriteByte(0x100b50,0x00);

	// turn on 2_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h29, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h29, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b53,0x00);
	MDrv_WriteByte(0x100b52,0x00);

	// if the next line is not marked, the data is from demod, else is from ts0 pad
	// set the ts0 input from demod
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
	MDrv_WriteByte(0x101e23,0x00);
	MDrv_WriteByte(0x101e22,0x02);

	// set the ts0_clk from demod
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
	MDrv_WriteByte(0x100b51,0x00);
	MDrv_WriteByte(0x100b50,0x0c);

	// software reset
	// `RIU_W((`RIUBASE_TSP0>>1) + `REG16_TSP_CTRL, 2'b11, 16'h0002);

	// tsp_file_in[4],
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_TSP_CTRL, 2'b11, 16'h0012);

	// tsp_file_segment[13],
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_TSP_CTRL1, 2'b11, 16'h2000);

	// record_all, pid_bypas, reg_pidflt0_en
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_HW_CONFIG12, 2'b11, 16'h0038);

	// start address
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_TSP_REC_HEAD0, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_TSP_REC_HEAD1, 2'b11, 16'h0010);
	// end address
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_TSP_REC_TAIL0, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_TSP_REC_TAIL1, 2'b11, 16'h0020);

	// stream2miu_en, activate rst_wadr
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_HW_CONFIG8, 2'b11, 16'h0012);

	// stream2miu_en, turn off rst_wadr
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_HW_CONFIG8, 2'b11, 16'h0102);
	MDrv_WriteByte(0x101e39,0x03);
	MDrv_WriteByte(0x103c0e,0x01);

#elif(CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)
    U8  	udatatemp = 0x00;
	// ----------------------------------------------
	//  start demod CLKGEN setting
	// ----------------------------------------------
	// *** Set register at CLKGEN1
	// enable DMD MCU clock "bit[0] set 0"
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0f, 2'b11, 16'h001c);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0f, 2'b11, 16'h001c);
	MDrv_WriteByte(0x10331f,0x00);
	MDrv_WriteByte(0x10331e,0x10);

	// set parallet ts clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0511);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0511);
	//MDrv_WriteByte(0x103301,0x06);//06
	udatatemp = MDrv_ReadByte(0x103301);
	udatatemp |= 0x06;
	MDrv_WriteByte(0x103301, udatatemp);

	MDrv_WriteByte(0x103300,0x0b);//19

	// enable atsc, DVBTC ts clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
	MDrv_WriteByte(0x103309,0x00);
	MDrv_WriteByte(0x103308,0x00);

	// enable dvbc adc clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x103315,0x00);
	MDrv_WriteByte(0x103314,0x00);

	// enable vif DAC clock
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
	MDrv_WriteByte(0x10331b,0x00);
	MDrv_WriteByte(0x10331a,0x00);

	// *** Set register at CLKGEN_DMD
	// enable atsc clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f03,0x00);
	MDrv_WriteByte(0x111f02,0x00);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f05,0x00);
	MDrv_WriteByte(0x111f04,0x00);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f07,0x00);
	MDrv_WriteByte(0x111f06,0x00);

	// enable clk_atsc_adcd_sync
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0b,0x00);
	MDrv_WriteByte(0x111f0a,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0d,0x00);
	MDrv_WriteByte(0x111f0c,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f0f,0x00);
	MDrv_WriteByte(0x111f0e,0x00);

	// enable dvbt inner clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f11,0x00);
	MDrv_WriteByte(0x111f10,0x00);

	// enable dvbc outer clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f13,0x00);
	MDrv_WriteByte(0x111f12,0x00);

	// enable dvbc inner-c clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f15,0x00);
	MDrv_WriteByte(0x111f14,0x00);

	// enable dvbc eq clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f17,0x00);
	MDrv_WriteByte(0x111f16,0x00);

	// enable sram clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f19,0x00);
	MDrv_WriteByte(0x111f18,0x00);

	// enable vif clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f1d,0x00);
	MDrv_WriteByte(0x111f1c,0x00);

	// enable DEMODE-DMA clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h10, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h10, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f21,0x00);
	MDrv_WriteByte(0x111f20,0x00);

	// select clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444);
	MDrv_WriteByte(0x111f23,0x00);
	MDrv_WriteByte(0x111f22,0x00);

	// Enable SAWLESS clock
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h12, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h12, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f25,0x00);
	MDrv_WriteByte(0x111f24,0x00);

	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h1111);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h1111);
	MDrv_WriteByte(0x111f19,0x11);
	MDrv_WriteByte(0x111f18,0x11);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h2222);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h2222);
	MDrv_WriteByte(0x111f19,0x22);
	MDrv_WriteByte(0x111f18,0x22);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h3333);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h3333);
	MDrv_WriteByte(0x111f19,0x33);
	MDrv_WriteByte(0x111f18,0x33);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
	MDrv_WriteByte(0x111f19,0x00);
	MDrv_WriteByte(0x111f18,0x00);

	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b43,0x00);
	MDrv_WriteByte(0x100b42,0x00);

	MDrv_WriteByte(0x1120A0, 0x00);
	MDrv_WriteByte(0x1120A1, 0x00);

	// ----------------------------------------------
	//  start demod CLKGEN setting
	// ----------------------------------------------

	// reg_allpad_in=0
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h50, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h50, 2'b11, 16'h0000);
	MDrv_WriteByte(0x101ea1,0x00);
	MDrv_WriteByte(0x101ea0,0x00);

	// reg_ts1config=2
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57, 2'b11, 16'h1000);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57, 2'b11, 16'h1000);
	//MDrv_WriteByte(0x101eaf,0x10);
	//MDrv_WriteByte(0x101eae,0x00);

	//  select DMD MCU
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h1c, 2'b10, 16'h0300);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h1c, 2'b10, 16'h0300);
	MDrv_WriteByte(0x101e39,0x03);

	// ----------------------------------------------
	//  Turn TSP
	// ----------------------------------------------

	// turn on ts0_config
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57   , 2'b11, 16'h0100);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h57   , 2'b11, 16'h0100);
	//MDrv_WriteByte(0x101eaf,0x01);
	//MDrv_WriteByte(0x101eae,0x00);

	// turn on tsp_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b55,0x00);
	MDrv_WriteByte(0x100b54,0x00);

	// turn on ts1_clk, ts0_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b51,0x00);
	MDrv_WriteByte(0x100b50,0x00);

	// turn on 2_clk
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h29, 2'b11, 16'h0000);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h29, 2'b11, 16'h0000);
	MDrv_WriteByte(0x100b53,0x00);
	MDrv_WriteByte(0x100b52,0x00);

	// if the next line is not marked, the data is from demod, else is from ts0 pad
	// set the ts0 input from demod
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
	// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
	MDrv_WriteByte(0x101e23,0x00);
	MDrv_WriteByte(0x101e22,0x02);

	// set the ts0_clk from demod
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
	// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
	MDrv_WriteByte(0x100b51,0x00);
	MDrv_WriteByte(0x100b50,0x0c);

	// stream2miu_en, activate rst_wadr
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_HW_CONFIG8, 2'b11, 16'h0012);

	// stream2miu_en, turn off rst_wadr
	// `RIU_W((`RIUBASE_TSP0 >>1) + `REG16_HW_CONFIG8, 2'b11, 16'h0102);
	MDrv_WriteByte(0x103c0e,0x01);

	//MDrv_WriteByte(0x000e13,0x01);
    udatatemp = MDrv_ReadByte(0x000e13);
    MDrv_WriteByte(0x000e13, udatatemp&0xFB);//Set 0e12,Bit10=0,

#elif((CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD))
	U8 tmp = 0x00;

MDrv_WriteByte(0x101e39, 0x00);
MDrv_WriteByte(0x103c0e, 0x00);
MDrv_WriteByte(0x10331f, 0x00);
MDrv_WriteByte(0x10331e, 0x10);

            // set parallel ts clock
            // [11] : reg_ckg_demod_test_in_en = 0
            //        0: select internal ADC CLK
            //        1: select external test-in clock
            // [10] : reg_ckg_dvbtm_ts_out_mode = 1
            //        0: select gated clock
            //        1: select free-run clock
            // [9]  : reg_ckg_atsc_dvbtc_ts_inv = 1
            //        0: normal phase to pad
            //        1: invert phase to pad
            // [8]  : reg_ckg_atsc_dvb_div_sel = 1
            //        0: select clk_dmplldiv2
            //        1: select clk_dmplldiv3
            // [4:0]: reg_ckg_dvbtm_ts_divnum = 17
            //        Demod TS output clock phase tuning number
            //        If (reg_ckg_tsout_ph_tun_num == reg_ckg_dvbtm_ts_divnum),
            //        Demod TS output clock is equal Demod TS internal working clock.
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0717);
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0717);


				MDrv_WriteByte(0x103301,0x07);
				MDrv_WriteByte(0x103300,0x17);

            // enable atsc, DVBTC ts clock
            // [3:0] : reg_ckg_atsc_ts
            //      [0]  : disable clock
            //      [1]  : invert clock
            //      [3:2]: Select clock source
            //             00:clk_atsc_dvb_div
            //             01:62 MHz
            //             10:54 MHz
            //             11:reserved
            // [11:8]: reg_ckg_dvbtc_ts
            //      [8]  : disable clock
            //      [9]  : invert clock
            //      [11:10]: Select clock source
            //             00:clk_atsc_dvb_div
            //             01:62 MHz
            //             10:54 MHz
            //             11:reserved
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
MDrv_WriteByte(0x103309, 0x00);
MDrv_WriteByte(0x103308, 0x00);


            // enable dvbc adc clock
            // [3:0]: reg_ckg_dvbtc_adc
            //       [0]  : disable clock
            //       [1]  : invert clock
            //       [3:2]: Select clock source => for demod clkgen clk_dvbtc_adc
            //      	00:  24MHz (clk_dmdadc)
            //      	01:  43.2MHz for VIF (clk_dmplldiv10_div2)
            //      	10:  reserved
            //      	11:  DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
MDrv_WriteByte(0x103315, 0x00);
MDrv_WriteByte(0x103314, 0x00);


				// enable vif DAC clock
				// [3:0] : reg_ckg_vifdbb_dac
				// [11:8]: reg_ckg_vifdbb_vdac
				// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
				// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
				//MDrv_WriteByte(0x10331b, 0x00);
				//MDrv_WriteByte(0x10331a, 0x00);

            // *** Set register at CLKGEN_DMD
            // Select MPLLDIV2
            // [0] : reg_atsc_adc_sel_mplldiv2
            // [1] : reg_atsc_eq_sel_mplldiv2
            // [2]   reg_fed_srd_on
            // `RIU_W((`RIUBASE_DMD_TOP>>1)+7'h00, 2'b01, 16'h0003);
            // `RIU_W((`RIUBASE_DMD_TOP>>1)+7'h00, 2'b01, 16'h0003);
            // wriu 0x112000 0x03
            MDrv_WriteByte(0x112000,0x03); // diff for /17


            // enable atsc clock
            // [3:0] : reg_ckg_atsc200_ph1
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div2(174 MHz)
            //                01: clk_dmplldiv3_div2(144 MHz)
            //                10: reserved
            //                11: DFT_CLK
            // [11:8]: reg_ckg_atsc200_ph3
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div2(174 MHz)
            //                01: clk_dmplldiv3_div2(144 MHz)
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0404);// ???
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0404);// ???
MDrv_WriteByte(0x111f03, 0x04);
MDrv_WriteByte(0x111f02, 0x04);

            // [3:0] : reg_ckg_atsc50
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div7(49.7 MHz)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // [11:8]: reg_ckg_atsc25
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div7_div2(24.85 MHz)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f05, 0x00);
MDrv_WriteByte(0x111f04, 0x00);



            // [3:0] : reg_ckg_atsc_eq25
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div2_div8(21.75 MHz)
            //                01: clk_dmplldiv3_div2_div8(18 MHz)
            //                10: reserved
            //                11: DFT_CLK
            // [11:8] : reg_ckg_atsc_ce25
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div16(21.75 MHz)
            //                01: clk_dmplldiv3_div16(18 MHz)
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0404);// ???
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0404);// ???
MDrv_WriteByte(0x111f07, 0x04);
MDrv_WriteByte(0x111f06, 0x04);



            // enable clk_atsc_adcd_sync
            // [3:0]: reg_ckg_atsc_adcd_sync
            //        [0]  : disable clock
            //        [1]  : invert clock
            //        [3:2]: Select clock source
            //               00: ADC_CLKOUT
            //               01: clk_dmplldiv2_div7(49.7 MHz)
            //               10: clk_dmplldiv2_div7_div2(24.85 MHz)
            //               11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0b, 0x00);
MDrv_WriteByte(0x111f0a, 0x00);



            // enable dvbt inner clock
            // [3:0] : reg_ckg_dvbtc_inner1x
            //        [0]  : disable clock
            //        [1]  : invert clock
            //        [3:2]: Select clock source
            //               00: clk_dmplldiv10_div4(21.6MHz, DVBT only)
            //               01: reserved
            //               10: reserved
            //               11: DFT_CLK
            // [11:8]: reg_ckg_dvbtc_inner2x
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10_div2(43.2MHz, DVBT only)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0d, 0x00);
MDrv_WriteByte(0x111f0c, 0x00);



            // enable dvbt inner clock
            // [3:0] : reg_ckg_dvbtc_inner4x
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10(86.4 MHz, DVBT only)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0f, 0x00);
MDrv_WriteByte(0x111f0e, 0x00);



            // enable dvbt outer clock
            // [3:0] : reg_ckg_dvbtc_outer1x
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10_div2(43.2MHz, DVBT only)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // [11:8]: reg_ckg_dvbtc_outer2x
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10(86.4MHz, DVBT only)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f11, 0x00);
MDrv_WriteByte(0x111f10, 0x00);



            // enable dvbc outer clock
            // [3:0] : reg_ckg_dvbtc_outer2x_c
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10	    (86.4MHz, DVBT/DVBC)
            //                01: clk_dmplldiv10_div2   (43.2MHz, DVBT/DVBC)
            //                10: clk_dmplldiv2_div7    (49.7 MHz, ATSC/J83 )
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f13, 0x00);
MDrv_WriteByte(0x111f12, 0x00);



// enable dvbc inner-c clock
// [11:8]: reg_ckg_dvbtc_innc
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_demod_adcout
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
// MDrv_WriteByte(0x111f15, 0x00);
// MDrv_WriteByte(0x111f14, 0x00);



// enable dvbc eq clock
// Removed
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
// MDrv_WriteByte(0x111f17, 0x00);
// MDrv_WriteByte(0x111f16, 0x00);

            // enable sram clock
            // [1:0]  : reg_ckg_dvbtc_sram0
            //          [0]: disable clock
            //          [1]: invert clock
            // [5:4]  : reg_ckg_dvbtc_sram1
            //          [0]: disable clock
            //          [1]: invert clock
            // [9:8]  : reg_ckg_dvbtc_sram2
            //          [0]: disable clock
            //          [1]: invert clock
            // [13:12]: reg_ckg_dvbtc_sram3
            //          [0]: disable clock
            //          [1]: invert clock
            // [15:14]: reg_ckg_dvbtc_sram4
            //          [0]: disable clock
            //          [1]: invert clock
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f19, 0x00);
MDrv_WriteByte(0x111f18, 0x00);


// enable vif clock
// [3:0] : reg_ckg_vifdbb_43m
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// [11:8]: reg_ckg_vifdbb_144m
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: from ADC_CLKOUT(144 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
//MDrv_WriteByte(0x111f1d, 0x00);
//MDrv_WriteByte(0x111f1c, 0x00);


// For ADC DMA Dump
// enable DEMODE-DMA clock
// [3:0] : reg_ckg_dmd_dma
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: from ADC_CLKOUT
//                01: clk_dmplldiv10_div2(VIF_43)
//                1x: select DFT_CLK


            // select clock
            // [3:0] : reg_ckg_frontend
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
            //                01: select clk_dmdadc             (48    MHz, DVBT/C)
            //                10: reserved
            //                11: select DFT_CLK
            // [7:4] : reg_ckg_tr
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
            //                01: select clk_dmdadc             (48    MHz, DVBT/C)
            //                10: reserved
            //                11: select DFT_CLK
            // [11:8]: reg_ckg_acifir
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
            //                01: select clk_dmdadc             (48    MHz, DVBT/C)
            //                10: clk_dmplldiv10_div2           (43.2  MHz, VIF)
            //                11: select DFT_CLK
            // [15:12]: reg_ckg_frontend_d2
            //         [0]  : disable clock
            //         [1]  : invert clock
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444); // ???
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444); // ???
MDrv_WriteByte(0x111f23, 0x04);
MDrv_WriteByte(0x111f22, 0x44);
// enable sawless clock
// MDrv_WriteByte(0x111f25, 0x00);
// MDrv_WriteByte(0x111f24, 0x00);

/////////////////
//Agate add start
/////////////////
// enable DMDMCU clock
// [4:0]: reg_ckg_dmdmcu
//         [0]  : disable clock
//         [1]  : invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0f, 2'b01, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0f, 2'b01, 16'h0000);
//wriu 0x111f1e 0x00
// MDrv_WriteByte(0x111f1e,0x00);

// enable TS clock
// [11:8]: reg_ckg_dvbtc_ts
//         [0]  : disable clock
//         [1]  : invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h04, 2'b10, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h04, 2'b10, 16'h0000);
//wriu 0x111f09 0x00
// MDrv_WriteByte(0x111f09,0x00);

// enable ADC_div2 clock for New symbol rate detection
// [3:0] : reg_ckg_frontend_d2
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmdadc_div2
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h14, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h14, 2'b11, 16'h0000);
// MDrv_WriteByte(0x111f29,0x00);
// MDrv_WriteByte(0x111f28,0x00);

// Turn on New symbol rate detection
// [0] : reg_dvbt_new_tdsfo_on
// [1] : reg_fed_srd_on
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h21, 2'b11, 16'h0002);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h21, 2'b11, 16'h0002);
// MDrv_WriteByte(0x111f43,0x00);
// MDrv_WriteByte(0x111f42,0x02);

//Agate add end
/////////////////

// ********************************
// enable VDMCU clock
// [3:0] : reg_ckg_vdmcu
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// [12:8]: reg_ckg_vd200
//         [0]  : disable clock
//         [1]  : invert clock
//         [4:2]: Select clock source
//                000: 170 MHz (MPLL_DIV_BUF)
//                001: 160 MHz
//                010: 140 MHz
//                011: 123 MHz
//                100: 180 MHz
//                101: mem_clock
//                110: mem_clock div 2
//                111: select XTAL
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
MDrv_WriteByte(0x101e38, 0x00);
MDrv_WriteByte(0x101e39, 0x03);

// =================================================================
//  Turn TSP
// =================================================================

// turn on tsp_clk, Because Select TS0 Path
// [4:0]  : reg_ckg_tsp  => CLK_TSP clock setting
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Clock source     //[4:2]: Clock source
//               00:      172 MHz //       000    : 144 MHz(default select)
//               01:      144 MHz //       001    : 123 MHz
//               10:      123 MHz //       010    : 108 MHz
//               11:      108 MHz //       011    : 72  MHz
//                                //       100~110: Undefined
//                                //       111    : select XTAL
// [11:8] : reg_ckg_stc0  => CLK_STC0 clock setting
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Clock source
//               00: select STC0 synthesizer outputtsp_top_wp(default select)
//               01: 1
//               10: 27MHz
//               11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0004); //A5 modify
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0004); //A5 modify
//MDrv_WriteByte(0x100b55, 0x00);
//MDrv_WriteByte(0x100b54, 0x04);

// set the ts0_clk from demod
// [3:0]: CLK_TS0 clock setting
//       [0]  : disable
//       [1]  : invert clock
//       [3:2]: Select clock source
//              00: select TS0_CLK
//              01: select TS1_CLK
//              10: reserved
//              11: clk_demod_ts_p
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
//MDrv_WriteByte(0x100b51, 0x00);
//MDrv_WriteByte(0x100b50, 0x0c);



// if the next line is not marked, the data is from demod, else is from ts0 pad
// set the ts0 input from demod
// [1:0]: Sourxe selection for TS channel 0
//         2'b00: come from PAD_TS0
//         2'b01: come from PAD_TS1
//         2'b10: come from DeMOD_TOP
// [9:8]: Sourxe selection for TS channel 1
//          00: from PAD_TS0
//          01: from PAD_TS1
//          10: from DEMOD_TOP
// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
// wriu 0x101e23 0x00
// MDrv_WriteByte(0x101e22, 0x02);

MDrv_WriteByte(0x103c0e, 0x01);

            tmp = MDrv_ReadByte(0x000e13);
            MDrv_WriteByte(0x000e13, tmp&0xFB);//Set 0e12,Bit10=0,

#elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) \
    || (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)  \
    || (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)  \
    || (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) \
    )
	U8 tmp = 0x00;

MDrv_WriteByte(0x101e39, 0x00);
MDrv_WriteByte(0x103c0e, 0x00);
MDrv_WriteByte(0x10331f, 0x00);
MDrv_WriteByte(0x10331e, 0x10);

            // set parallel ts clock
            // [11] : reg_ckg_demod_test_in_en = 0
            //        0: select internal ADC CLK
            //        1: select external test-in clock
            // [10] : reg_ckg_dvbtm_ts_out_mode = 1
            //        0: select gated clock
            //        1: select free-run clock
            // [9]  : reg_ckg_atsc_dvbtc_ts_inv = 1
            //        0: normal phase to pad
            //        1: invert phase to pad
            // [8]  : reg_ckg_atsc_dvb_div_sel = 1
            //        0: select clk_dmplldiv2
            //        1: select clk_dmplldiv3
            // [4:0]: reg_ckg_dvbtm_ts_divnum = 17
            //        Demod TS output clock phase tuning number
            //        If (reg_ckg_tsout_ph_tun_num == reg_ckg_dvbtm_ts_divnum),
            //        Demod TS output clock is equal Demod TS internal working clock.
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0717);
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0717);


				MDrv_WriteByte(0x103301,0x07);
				MDrv_WriteByte(0x103300,0x17);

            // enable atsc, DVBTC ts clock
            // [3:0] : reg_ckg_atsc_ts
            //      [0]  : disable clock
            //      [1]  : invert clock
            //      [3:2]: Select clock source
            //             00:clk_atsc_dvb_div
            //             01:62 MHz
            //             10:54 MHz
            //             11:reserved
            // [11:8]: reg_ckg_dvbtc_ts
            //      [8]  : disable clock
            //      [9]  : invert clock
            //      [11:10]: Select clock source
            //             00:clk_atsc_dvb_div
            //             01:62 MHz
            //             10:54 MHz
            //             11:reserved
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
MDrv_WriteByte(0x103309, 0x00);
MDrv_WriteByte(0x103308, 0x00);


            // enable dvbc adc clock
            // [3:0]: reg_ckg_dvbtc_adc
            //       [0]  : disable clock
            //       [1]  : invert clock
            //       [3:2]: Select clock source => for demod clkgen clk_dvbtc_adc
            //      	00:  24MHz (clk_dmdadc)
            //      	01:  43.2MHz for VIF (clk_dmplldiv10_div2)
            //      	10:  reserved
            //      	11:  DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
MDrv_WriteByte(0x103315, 0x00);
MDrv_WriteByte(0x103314, 0x00);


				// enable vif DAC clock
				// [3:0] : reg_ckg_vifdbb_dac
				// [11:8]: reg_ckg_vifdbb_vdac
				// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
				// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
				//MDrv_WriteByte(0x10331b, 0x00);
				//MDrv_WriteByte(0x10331a, 0x00);

            // *** Set register at CLKGEN_DMD
            // Select MPLLDIV2
            // [0] : reg_atsc_adc_sel_mplldiv2
            // [1] : reg_atsc_eq_sel_mplldiv2
            // [2]   reg_fed_srd_on
            // `RIU_W((`RIUBASE_DMD_TOP>>1)+7'h00, 2'b01, 16'h0003);
            // `RIU_W((`RIUBASE_DMD_TOP>>1)+7'h00, 2'b01, 16'h0003);
            // wriu 0x112000 0x03
            MDrv_WriteByte(0x112000,0x03); // diff for /17


            // enable atsc clock
            // [3:0] : reg_ckg_atsc200_ph1
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div2(174 MHz)
            //                01: clk_dmplldiv3_div2(144 MHz)
            //                10: reserved
            //                11: DFT_CLK
            // [11:8]: reg_ckg_atsc200_ph3
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div2(174 MHz)
            //                01: clk_dmplldiv3_div2(144 MHz)
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0404);// ???
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0404);// ???
MDrv_WriteByte(0x111f03, 0x04);
MDrv_WriteByte(0x111f02, 0x04);

            // [3:0] : reg_ckg_atsc50
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div7(49.7 MHz)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // [11:8]: reg_ckg_atsc25
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div7_div2(24.85 MHz)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f05, 0x00);
MDrv_WriteByte(0x111f04, 0x00);



            // [3:0] : reg_ckg_atsc_eq25
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div2_div8(21.75 MHz)
            //                01: clk_dmplldiv3_div2_div8(18 MHz)
            //                10: reserved
            //                11: DFT_CLK
            // [11:8] : reg_ckg_atsc_ce25
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv2_div16(21.75 MHz)
            //                01: clk_dmplldiv3_div16(18 MHz)
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0404);// ???
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0404);// ???
MDrv_WriteByte(0x111f07, 0x04);
MDrv_WriteByte(0x111f06, 0x04);



            // enable clk_atsc_adcd_sync
            // [3:0]: reg_ckg_atsc_adcd_sync
            //        [0]  : disable clock
            //        [1]  : invert clock
            //        [3:2]: Select clock source
            //               00: ADC_CLKOUT
            //               01: clk_dmplldiv2_div7(49.7 MHz)
            //               10: clk_dmplldiv2_div7_div2(24.85 MHz)
            //               11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0b, 0x00);
MDrv_WriteByte(0x111f0a, 0x00);



            // enable dvbt inner clock
            // [3:0] : reg_ckg_dvbtc_inner1x
            //        [0]  : disable clock
            //        [1]  : invert clock
            //        [3:2]: Select clock source
            //               00: clk_dmplldiv10_div4(21.6MHz, DVBT only)
            //               01: reserved
            //               10: reserved
            //               11: DFT_CLK
            // [11:8]: reg_ckg_dvbtc_inner2x
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10_div2(43.2MHz, DVBT only)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0d, 0x00);
MDrv_WriteByte(0x111f0c, 0x00);



            // enable dvbt inner clock
            // [3:0] : reg_ckg_dvbtc_inner4x
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10(86.4 MHz, DVBT only)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0f, 0x00);
MDrv_WriteByte(0x111f0e, 0x00);



            // enable dvbt outer clock
            // [3:0] : reg_ckg_dvbtc_outer1x
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10_div2(43.2MHz, DVBT only)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // [11:8]: reg_ckg_dvbtc_outer2x
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10(86.4MHz, DVBT only)
            //                01: reserved
            //                10: reserved
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f11, 0x00);
MDrv_WriteByte(0x111f10, 0x00);



            // enable dvbc outer clock
            // [3:0] : reg_ckg_dvbtc_outer2x_c
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: clk_dmplldiv10	    (86.4MHz, DVBT/DVBC)
            //                01: clk_dmplldiv10_div2   (43.2MHz, DVBT/DVBC)
            //                10: clk_dmplldiv2_div7    (49.7 MHz, ATSC/J83 )
            //                11: DFT_CLK
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f13, 0x00);
MDrv_WriteByte(0x111f12, 0x00);



// enable dvbc inner-c clock
// [11:8]: reg_ckg_dvbtc_innc
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_demod_adcout
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
// MDrv_WriteByte(0x111f15, 0x00);
// MDrv_WriteByte(0x111f14, 0x00);



// enable dvbc eq clock
// Removed
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
// MDrv_WriteByte(0x111f17, 0x00);
// MDrv_WriteByte(0x111f16, 0x00);

            // enable sram clock
            // [1:0]  : reg_ckg_dvbtc_sram0
            //          [0]: disable clock
            //          [1]: invert clock
            // [5:4]  : reg_ckg_dvbtc_sram1
            //          [0]: disable clock
            //          [1]: invert clock
            // [9:8]  : reg_ckg_dvbtc_sram2
            //          [0]: disable clock
            //          [1]: invert clock
            // [13:12]: reg_ckg_dvbtc_sram3
            //          [0]: disable clock
            //          [1]: invert clock
            // [15:14]: reg_ckg_dvbtc_sram4
            //          [0]: disable clock
            //          [1]: invert clock
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f19, 0x00);
MDrv_WriteByte(0x111f18, 0x00);


// enable vif clock
// [3:0] : reg_ckg_vifdbb_43m
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// [11:8]: reg_ckg_vifdbb_144m
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: from ADC_CLKOUT(144 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
//MDrv_WriteByte(0x111f1d, 0x00);
//MDrv_WriteByte(0x111f1c, 0x00);


// For ADC DMA Dump
// enable DEMODE-DMA clock
// [3:0] : reg_ckg_dmd_dma
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: from ADC_CLKOUT
//                01: clk_dmplldiv10_div2(VIF_43)
//                1x: select DFT_CLK


            // select clock
            // [3:0] : reg_ckg_frontend
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
            //                01: select clk_dmdadc             (48    MHz, DVBT/C)
            //                10: reserved
            //                11: select DFT_CLK
            // [7:4] : reg_ckg_tr
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
            //                01: select clk_dmdadc             (48    MHz, DVBT/C)
            //                10: reserved
            //                11: select DFT_CLK
            // [11:8]: reg_ckg_acifir
            //         [0]  : disable clock
            //         [1]  : invert clock
            //         [3:2]: Select clock source
            //                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
            //                01: select clk_dmdadc             (48    MHz, DVBT/C)
            //                10: clk_dmplldiv10_div2           (43.2  MHz, VIF)
            //                11: select DFT_CLK
            // [15:12]: reg_ckg_frontend_d2
            //         [0]  : disable clock
            //         [1]  : invert clock
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444); // ???
            // `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0444); // ???
MDrv_WriteByte(0x111f23, 0x04);
MDrv_WriteByte(0x111f22, 0x44);
// enable sawless clock
// MDrv_WriteByte(0x111f25, 0x00);
// MDrv_WriteByte(0x111f24, 0x00);

/////////////////
//Agate add start
/////////////////
// enable DMDMCU clock
// [4:0]: reg_ckg_dmdmcu
//         [0]  : disable clock
//         [1]  : invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0f, 2'b01, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0f, 2'b01, 16'h0000);
//wriu 0x111f1e 0x00
// MDrv_WriteByte(0x111f1e,0x00);

// enable TS clock
// [11:8]: reg_ckg_dvbtc_ts
//         [0]  : disable clock
//         [1]  : invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h04, 2'b10, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h04, 2'b10, 16'h0000);
//wriu 0x111f09 0x00
// MDrv_WriteByte(0x111f09,0x00);

// enable ADC_div2 clock for New symbol rate detection
// [3:0] : reg_ckg_frontend_d2
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmdadc_div2
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h14, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h14, 2'b11, 16'h0000);
// MDrv_WriteByte(0x111f29,0x00);
// MDrv_WriteByte(0x111f28,0x00);

// Turn on New symbol rate detection
// [0] : reg_dvbt_new_tdsfo_on
// [1] : reg_fed_srd_on
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h21, 2'b11, 16'h0002);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h21, 2'b11, 16'h0002);
// MDrv_WriteByte(0x111f43,0x00);
// MDrv_WriteByte(0x111f42,0x02);

//Agate add end
/////////////////

// ********************************
// enable VDMCU clock
// [3:0] : reg_ckg_vdmcu
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// [12:8]: reg_ckg_vd200
//         [0]  : disable clock
//         [1]  : invert clock
//         [4:2]: Select clock source
//                000: 170 MHz (MPLL_DIV_BUF)
//                001: 160 MHz
//                010: 140 MHz
//                011: 123 MHz
//                100: 180 MHz
//                101: mem_clock
//                110: mem_clock div 2
//                111: select XTAL
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
MDrv_WriteByte(0x101e38, 0x00);
MDrv_WriteByte(0x101e39, 0x03);

// =================================================================
//  Turn TSP
// =================================================================

// turn on tsp_clk, Because Select TS0 Path
// [4:0]  : reg_ckg_tsp  => CLK_TSP clock setting
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Clock source     //[4:2]: Clock source
//               00:      172 MHz //       000    : 144 MHz(default select)
//               01:      144 MHz //       001    : 123 MHz
//               10:      123 MHz //       010    : 108 MHz
//               11:      108 MHz //       011    : 72  MHz
//                                //       100~110: Undefined
//                                //       111    : select XTAL
// [11:8] : reg_ckg_stc0  => CLK_STC0 clock setting
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Clock source
//               00: select STC0 synthesizer outputtsp_top_wp(default select)
//               01: 1
//               10: 27MHz
//               11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0004); //A5 modify
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0004); //A5 modify
//MDrv_WriteByte(0x100b55, 0x00);
//MDrv_WriteByte(0x100b54, 0x04);

// set the ts0_clk from demod
// [3:0]: CLK_TS0 clock setting
//       [0]  : disable
//       [1]  : invert clock
//       [3:2]: Select clock source
//              00: select TS0_CLK
//              01: select TS1_CLK
//              10: reserved
//              11: clk_demod_ts_p
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
//MDrv_WriteByte(0x100b51, 0x00);
//MDrv_WriteByte(0x100b50, 0x0c);



// if the next line is not marked, the data is from demod, else is from ts0 pad
// set the ts0 input from demod
// [1:0]: Sourxe selection for TS channel 0
//         2'b00: come from PAD_TS0
//         2'b01: come from PAD_TS1
//         2'b10: come from DeMOD_TOP
// [9:8]: Sourxe selection for TS channel 1
//          00: from PAD_TS0
//          01: from PAD_TS1
//          10: from DEMOD_TOP
// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
// wriu 0x101e23 0x00
// MDrv_WriteByte(0x101e22, 0x02);

MDrv_WriteByte(0x103c0e, 0x01);

            tmp = MDrv_ReadByte(0x000e13);
            MDrv_WriteByte(0x000e13, tmp&0xFB);//Set 0e12,Bit10=0,

#elif((CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER))
// =================================================================
// Select reg_DMDTOP and reg_DMDANA are controlled by which MCU
// =================================================================
// reg_dmdtop_dmd_sel=test_chip_top.chip_top.reg_chip_top.reg_CHIPTOP_inst.reg_chiptop_dummy_0[8]: 0x1c
// 1'b0->reg_DMDTOP control by HK_MCU.
// wriu 0x101e39 8'bxxxx_xxx0
// 1'b1->reg_DMDTOP control by DMD_MCU.
// wriu 0x101e39 8'bxxxx_xxx1
// reg_dmd_ana_regsel=test_chip_top.chip_top.reg_chip_top.reg_CHIPTOP_inst.reg_chiptop_dummy_0[9]: 0x1c
// 1'b0->reg_DMDANA control by HK_MCU.
// wriu 0x101e39 8'bxxxx_xx0x
// 1'b1->reg_DMDANA control by DMD_MCU.
// wriu 0x101e39 8'bxxxx_xx1x
MDrv_WriteByte(0x101e39, 0x00);

// CLK_DMDMCU clock setting
// reg_ckg_dmdmcu@0x0f[4:0]
// [0]  : disable clock
// [1]  : invert clock
// [4:2]:
//        000:170 MHz(MPLL_DIV_BUF)
//        001:160MHz
//        010:144MHz
//        011:123MHz
//        100:108MHz (A1:ATSC, DVBT, DVBC, J83)
//        101:mem_clcok
//        110:mem_clock div 2
//        111:select XTAL
MDrv_WriteByte(0x10331e, 0x10);

// set parallel ts clock
// [12] : reg_ckg_tsout_ph_tun_en = 0
//	  0: Demod TS output clock is equal Demod TS internal working clock
// [11] : reg_ckg_demod_test_in_en = 0
//        0: select internal ADC CLK
//        1: select external test-in clock
// [10] : reg_ckg_dvbtm_ts_out_mode = 1
//        0: select gated clock
//        1: select free-run clock
// [9]  : reg_ckg_atsc_dvbtc_ts_inv = 0
//        0: normal phase to pad
//        1: invert phase to pad
// [8]  : reg_ckg_atsc_dvb_div_sel = 0
//        0: select clk_dmplldiv5
//        1: select clk_dmplldiv3
// [4:0]: reg_ckg_dvbtm_ts_divnum = 11
//        Demod TS output clock phase tuning number
//	=> TS clock = MPLLDIV5/(2*(reg_ckg_dvbtm_ts_divnum+1)) = (24*36/5)/(2*(11+1)) = 7.2 MHz
MDrv_WriteByte(0x103301, 0x06);
MDrv_WriteByte(0x103300, 0x0b);

// enable atsc, DVBTC ts clock
// [3:0] : reg_ckg_atsc_ts
//      [0]  : disable clock
//      [1]  : invert clock
//      [3:2]: Select clock source
//             00:clk_atsc_dvb_div
//             01:62 MHz
//             10:54 MHz
//             11:reserved
// [11:8]: reg_ckg_dvbtc_ts
//      [8]  : disable clock
//      [9]  : invert clock
//      [11:10]: Select clock source
//             00:clk_atsc_dvb_div
//             01:62 MHz
//             10:54 MHz
//             11:reserved
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
MDrv_WriteByte(0x103309, 0x00);
MDrv_WriteByte(0x103308, 0x01);


// enable dvbc adc clock
// [3:0]: reg_ckg_dvbtc_adc
//       [0]  : disable clock
//       [1]  : invert clock
//       [3:2]: Select clock source => for demod clkgen clk_dvbtc_adc
//      	00:  24MHz (clk_dmdadc)
//      	01:  43.2MHz for VIF (clk_dmplldiv10_div2)
//      	10:  reserved
//      	11:  DFT_CLK
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
MDrv_WriteByte(0x103315, 0x00);
MDrv_WriteByte(0x103314, 0x00);

// enable clk_atsc_adcd_sync
// [3:0]: reg_ckg_atsc_adcd_sync
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Select clock source
//               00: ADC_CLKOUT
//               01: clk_dmplldiv2_div7(49.7 MHz) or clk_dmplldiv17(50.82 MHz)
//               10: clk_dmplldiv2_div7_div2(24.85 MHz) or clk_dmplldiv17_div2(25.41 MHz)
//               11: DFT_CLK
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0008);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0008);
MDrv_WriteByte(0x111f0b, 0x00);
MDrv_WriteByte(0x111f0a, 0x00);

// enable dvbt inner clock
// [3:0] : reg_ckg_dvbtc_inner1x
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Select clock source
//               00: clk_dmplldiv10_div4(21.6MHz, DVBT only)
//               01: reserved
//               10: reserved
//               11: DFT_CLK
// [11:8]: reg_ckg_dvbtc_inner2x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: DFT_CLK
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0d, 0x00);
MDrv_WriteByte(0x111f0c, 0x00);

// enable dvbt inner clock
// [3:0] : reg_ckg_dvbtc_inner4x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10(86.4 MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: DFT_CLK
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0f, 0x00);
MDrv_WriteByte(0x111f0e, 0x00);


// enable dvbt outer clock
// [3:0] : reg_ckg_dvbtc_outer1x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2 MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: DFT_CLK
// [11:8]: reg_ckg_dvbtc_outer2x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10(86.4 MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: DFT_CLK
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f11, 0x00);
MDrv_WriteByte(0x111f10, 0x00);

// enable dvbc outer clock
// [3:0] : reg_ckg_dvbtc_outer2x_c
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: reserved
//                01: reserved
//                10: clk_dmplldiv2_div7(49.7 MHz) or clk_dmplldiv17(50.82 MHz)
//                11: DFT_CLK
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0008);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0008);
MDrv_WriteByte(0x111f13, 0x00);
MDrv_WriteByte(0x111f12, 0x00);


// enable sram clock
// [1:0]  : reg_ckg_dvbtc_sram0
//          [0]: disable clock
//          [1]: invert clock
// [5:4]  : reg_ckg_dvbtc_sram1
//          [0]: disable clock
//          [1]: invert clock
// [9:8]  : reg_ckg_dvbtc_sram2
//          [0]: disable clock
//          [1]: invert clock
// [13:12]: reg_ckg_dvbtc_sram3
//          [0]: disable clock
//          [1]: invert clock
// [15:14]: reg_ckg_dvbtc_sram4
//          [0]: disable clock
//          [1]: invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f19, 0x00);
MDrv_WriteByte(0x111f18, 0x00);


// enable isdbt clock
// [2:0] : reg_ckg_isdbt_inner1x
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Select clock source
//               00: clk_dmplldiv10_div4(21.6MHz, ISDBT only)
//               01: reserved
//               10: reserved
//               11: DFT_CLK
// [6:4]: reg_ckg_dvbtc_inner2x
//         [0]  : disable clock
//         [1]  : invert clock
//         [2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2MHz,ISDBT only)
//                01: reserved
//                10: reserved
//                11: DFT_CLK
// [10:8] : reg_ckg_dvbtc_inner4x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10(86.4 MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: DFT_CLK
MDrv_WriteByte(0x111f43, 0x00);
MDrv_WriteByte(0x111f42, 0x00);

// enable isdbt outer clock
// [3:0] : reg_ckg_isdbt_outer1x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: isdbt_clk6_lat (6 MHz)
//                01: isdbt_clk8_lat (8 MHz)
//                10: reserved
//                11: DFT_CLK
// [6:4]: reg_ckg_isdbt_outer4x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: isdbt_clk24_lat(24 MHz)
//                01: isdbt_clk32_lat(32 MHz)
//                10: reserved
//                11: DFT_CLK
// [10:8]: reg_ckg_isdbt_outer6x
//         [0]  : disable clock
//         [1]  : invert clock
//         [2]	: Select clock source
//                00: isdbt_clk36_lat(36 MHz)
//                01: isdbt_clk48_lat(48 MHz)
//                10: reserved
//                11: DFT_CLK
// [14:12]: reg_ckg_isdbt_outer12x
//         [0]  : disable clock
//         [1]  : invert clock
//         [2]	: Select clock source
//                00: isdbt_clk72_lat(72 MHz)
//                01: isdbt_clk96_lat(96 MHz)
//                10: reserved
//                11: DFT_CLK
MDrv_WriteByte(0x111f45, 0x00);
MDrv_WriteByte(0x111f44, 0x00);

// reg_clk_isdbt_outer_div_en[0]
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h23, 2'b01, 16'h0001);// enable isdbt outer div clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h23, 2'b01, 16'h0001);// enable isdbt outer div clock
MDrv_WriteByte(0x111f46, 0x01);

// [1:0]  : reg_ckg_dvbtc_sram4_isdbt_inner4x
//          [0]: disable clock
//          [1]: invert clock
// [5:4]  : reg_ckg_dvbtc_sram4_isdbt_outer6x
//          [0]: disable clock
//          [1]: invert clock
MDrv_WriteByte(0x111f49, 0x00);
MDrv_WriteByte(0x111f48, 0x00);

// [1:0]  : reg_ckg_isdbt_outer6x_dvbt_inner1x
//          [0]: disable clock
//          [1]: invert clock
// [5:4]  : reg_ckg_isdbt_outer6x_dvbt_inner2x
//          [0]: disable clock
//          [1]: invert clock
// [9:8]  : reg_ckg_isdbt_outer6x_dvbt_outer2x[9:8]
//          [0]: disable clock
//          [1]: invert clock
// [13:12]: reg_ckg_isdbt_outer6x_dvbt_outer2x_c
//          [0]: disable clock
//          [1]: invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h25, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h25, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f4b, 0x00);
MDrv_WriteByte(0x111f4a, 0x00);

// enable isdbt outer clock_rs
// [7:4] : reg_ckg_isdbt_outer_rs
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: isdbt_clk36_lat (36 MHz)
//                01: isdbt_clk48_lat (48 MHz)
//                10: clk_dmplldiv3_div4(72 MHz)
//                11: isdbt_clk96_buf (96 MHz)


// enable share isdbt &dvbt logic clock
// [1:0]  : reg_ckg_isdbt_inner2x_dvbt_inner2x[1:0]
//          [0]: disable clock
//          [1]: invert clock
MDrv_WriteByte(0x111f4c, 0x00);

// select clock
// [3:0] : reg_ckg_frontend
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div7_div2(24.85 MHz) or clk_dmplldiv17_div2(25.41 MHz)
//                01: clk_dmdadc
//                10: reserved
//                11: select DFT_CLK
// [7:4] : reg_ckg_tr
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div7_div2(24.85 MHz) or clk_dmplldiv17_div2(25.41 MHz)
//                01: clk_dmdadc
//                10: reserved
//                11: select DFT_CLK
// [11:8]: reg_ckg_acifir
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div7_div2(24.85 MHz) or clk_dmplldiv17_div2(25.41 MHz)
//                01: clk_dmdadc
//                10: clk_vif_ssc_mux           (43.2  MHz, VIF)
//                11: select DFT_CLK
// [15:12]: reg_ckg_frontend_d2
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: reserved
//                01: clk_dmplldiv2_div7_div4(12.425 MHz) or clk_dmplldiv17_div4(12.705 MHz)
//                10: reserved
//                11: select DFT_CLK
MDrv_WriteByte(0x111f23, 0x44);
MDrv_WriteByte(0x111f22, 0x44);

// =================================================================
// Select reg_DMDTOP and reg_DMDANA are controlled by which MCU
// =================================================================
// reg_dmdtop_dmd_sel=test_chip_top.chip_top.reg_chip_top.reg_CHIPTOP_inst.reg_chiptop_dummy_0[8]: 0x1c
// 1'b0->reg_DMDTOP control by HK_MCU.
// wriu 0x101e39 8'bxxxx_xxx0
// 1'b1->reg_DMDTOP control by DMD_MCU.
// wriu 0x101e39 8'bxxxx_xxx1
// reg_dmd_ana_regsel=test_chip_top.chip_top.reg_chip_top.reg_CHIPTOP_inst.reg_chiptop_dummy_0[9]: 0x1c
// 1'b0->reg_DMDANA control by HK_MCU.
// wriu 0x101e39 8'bxxxx_xx0x
// 1'b1->reg_DMDANA control by DMD_MCU.
// wriu 0x101e39 8'bxxxx_xx1x
// `RIU_W((`RIUBASE_CHIP>>1)+7'h1c, 2'b10, 16'h0000); // 16'bxxxx_xx00_xxxx_xxxx
// `RIU_W((`RIUBASE_CHIP>>1)+7'h1c, 2'b10, 16'h0000); // 16'bxxxx_xx00_xxxx_xxxx
MDrv_WriteByte(0x101e39, 0x03);

#elif(CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)
MDrv_WriteByte(0x101e39, 0x00);
// wriu 0x101e38 0x07
MDrv_WriteByte(0x10331f, 0x00);
MDrv_WriteByte(0x10331e, 0x10);

// set parallet ts clock
// [11] : reg_ckg_demod_test_in_en
//        0: select internal ADC CLK
//        1: select external test-in clock
// [10] : reg_ckg_dvbtm_ts_out_mode
//        0: select gated clock
//        1: select free-run clock
// [9]  : reg_ckg_atsc_dvbtc_ts_inv
//        0: normal phase to pad
//        1: invert phase to pad
// [8]  : reg_ckg_atsc_dvb_div_sel
//        0: select clk_dmplldiv2
//        1: select clk_dmplldiv3
// [4:0]: reg_ckg_dvbtm_ts_divnum
//        Demod TS output clock phase tuning number
//        If (reg_ckg_tsout_ph_tun_num == reg_ckg_dvbtm_ts_divnum),
//        Demod TS output clock is equal Demod TS internal working clock.
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0619);
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h00, 2'b11, 16'h0619);
//MDrv_WriteByte(0x103301, 0x07);
//MDrv_WriteByte(0x103300, 0x11);
//MDrv_WriteByte(0x103301, 0x06);

	tmp = MDrv_ReadByte(0x103301);
    tmp |= 0x06;
    MDrv_WriteByte(0x103301, tmp);

MDrv_WriteByte(0x103300, 0x19);
// enable atsc, DVBTC ts clock
// [3:0] : reg_ckg_atsc_ts
//      [0]  : disable clock
//      [1]  : invert clock
//      [3:2]: Select clock source
//             00:clk_atsc_dvb_div
//             01:62 MHz
//             10:54 MHz
//             11:select XTAL
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0000);
MDrv_WriteByte(0x103309, 0x00);
MDrv_WriteByte(0x103308, 0x00);
// enable dvbc adc clock
// [3:0]: reg_ckg_dvbtc_adc
//       [0]  : disable clock
//       [1]  : invert clock
//       [3:2]: Select clock source
//          00:  clk_demod_adcout
//          01:  reserved
//          10:  reserved
//          11:  select XTAL
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0a, 2'b11, 16'h0000);
MDrv_WriteByte(0x103315, 0x00);
MDrv_WriteByte(0x103314, 0x00);
// enable vif DAC clock
// [3:0] : reg_ckg_vifdbb_dac
// [11:8]: reg_ckg_vifdbb_vdac
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN1>>1)+7'h0d, 2'b11, 16'h0000);
//MDrv_WriteByte(0x10331b, 0x00);
//MDrv_WriteByte(0x10331a, 0x00);

// *** Set register at CLKGEN_DMD
// enable atsc clock
// [3:0] : reg_ckg_atsc200_ph1
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div2(174 MHz)
//                01: clk_dmplldiv3_div2(144 MHz)
//                10: reserved
//                11: select XTAL
// [11:8]: reg_ckg_atsc200_ph3
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div2(174 MHz)
//                01: clk_dmplldiv3_div2(144 MHz)
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h01, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f03, 0x00);
MDrv_WriteByte(0x111f02, 0x00);

// [3:0] : reg_ckg_atsc50
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div7(49.7 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// [11:8]: reg_ckg_atsc25
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div7_div2(24.85 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h02, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f05, 0x00);
MDrv_WriteByte(0x111f04, 0x00);



// [3:0] : reg_ckg_atsc_eq25
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div2_div8(21.75 MHz)
//                01: clk_dmplldiv3_div2_div8(18 MHz)
//                10: reserved
//                11: select XTAL
// [11:8] : reg_ckg_atsc_ce25
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv2_div16(21.75 MHz)
//                01: clk_dmplldiv3_div16(18 MHz)
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h03, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f07, 0x00);
MDrv_WriteByte(0x111f06, 0x00);



// enable clk_atsc_adcd_sync
// [3:0]: reg_ckg_atsc_adcd_sync
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Select clock source
//               00: ADC_CLKOUT
//               01: clk_dmplldiv2_div7(49.7 MHz)
//               10: clk_dmplldiv2_div7_div2(24.85 MHz)
//               11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h05, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0b, 0x00);
MDrv_WriteByte(0x111f0a, 0x00);



// enable dvbt inner clock
// [3:0] : reg_ckg_dvbtc_inner1x
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Select clock source
//               00: clk_dmplldiv10_div2(43.2 MHz, DVBT only)
//               01: reserved
//               10: reserved
//               11: select XTAL
// [11:8]: reg_ckg_dvbtc_inner2x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div4(21.6 MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h06, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0d, 0x00);
MDrv_WriteByte(0x111f0c, 0x00);



// enable dvbt inner clock
// [3:0] : reg_ckg_dvbtc_inner4x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10(86.4 MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h07, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f0f, 0x00);
MDrv_WriteByte(0x111f0e, 0x00);



// enable dvbt inner clock
// [3:0] : reg_ckg_dvbtc_outer1x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2 MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: select XTAL
// [11:8]: reg_ckg_dvbtc_outer2x
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10(86.4 MHz, DVBT only)
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h08, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f11, 0x00);
MDrv_WriteByte(0x111f10, 0x00);



// enable dvbc outer clock
// [3:0] : reg_ckg_dvbtc_outer2x_c
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10     (86.4  MHz, DVBT/DVBC only)
//                01: clk_dmplldiv10_div2(43.2  MHz, DVBT/DVBC only)
//                10: clk_dmplldiv2_div7 (49.37 MHz, ATSC/J83 )
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h09, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f13, 0x00);
MDrv_WriteByte(0x111f12, 0x00);



// enable dvbc inner-c clock
// [11:8]: reg_ckg_dvbtc_innc
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_demod_adcout
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0a, 2'b11, 16'h0000);
//MDrv_WriteByte(0x111f15, 0x00);
//MDrv_WriteByte(0x111f14, 0x00);



// enable dvbc eq clock
// Removed
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0b, 2'b11, 16'h0000);
//MDrv_WriteByte(0x111f17, 0x00);
//MDrv_WriteByte(0x111f16, 0x00);

// enable sram clock
// [1:0]  : reg_ckg_dvbtc_sram0
//          [0]: disable clock
//          [1]: invert clock
// [5:4]  : reg_ckg_dvbtc_sram1
//          [0]: disable clock
//          [1]: invert clock
// [9:8]  : reg_ckg_dvbtc_sram2
//          [0]: disable clock
//          [1]: invert clock
// [13:12]: reg_ckg_dvbtc_sram3
//          [0]: disable clock
//          [1]: invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0c, 2'b11, 16'h0000);
MDrv_WriteByte(0x111f19, 0x00);
MDrv_WriteByte(0x111f18, 0x00);


// enable vif clock
// [3:0] : reg_ckg_vifdbb_43m
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// [11:8]: reg_ckg_vifdbb_144m
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: from ADC_CLKOUT(144 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0e, 2'b11, 16'h0000);
//MDrv_WriteByte(0x111f1d, 0x00);
//MDrv_WriteByte(0x111f1c, 0x00);


// For ADC DMA Dump
// enable DEMODE-DMA clock
// [3:0] : reg_ckg_dmd_dma
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: from ADC_CLKOUT
//                01: clk_dmplldiv10_div2(VIF_43)
//                1x: select DFT_CLK


// select clock
// [3:0] : reg_ckg_frontend
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
//                01: select clk_dmdadc             (48    MHz, DVBT/C)
//                10: reserved
//                11: select DFT_CLK
// [7:4] : reg_ckg_tr
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
//                01: select clk_dmdadc             (48    MHz, DVBT/C)
//                10: reserved
//                11: select DFT_CLK
// [11:8]: reg_ckg_acifir
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: select clk_dmplldiv2_div7_div2(24.85 MHz, ATSC)
//                01: select clk_dmdadc             (48    MHz, DVBT/C)
//                10: clk_dmplldiv10_div2           (43.2  MHz, VIF)
//                11: select DFT_CLK
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0111);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h11, 2'b11, 16'h0111);
//MDrv_WriteByte(0x111f21, 0x00);
//MDrv_WriteByte(0x111f20, 0x00);
// wriu 0x111f23 0x01
// wriu 0x111f22 0x11
MDrv_WriteByte(0x111f23, 0x00);
MDrv_WriteByte(0x111f22, 0x00);
// enable sawless clock
MDrv_WriteByte(0x111f25, 0x00);
MDrv_WriteByte(0x111f24, 0x00);

/////////////////
//Agate add start
/////////////////
// enable DMDMCU clock
// [4:0]: reg_ckg_dmdmcu
//         [0]  : disable clock
//         [1]  : invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0f, 2'b01, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h0f, 2'b01, 16'h0000);
//wriu 0x111f1e 0x00
MDrv_WriteByte(0x111f1e,0x00);

// enable TS clock
// [11:8]: reg_ckg_dvbtc_ts
//         [0]  : disable clock
//         [1]  : invert clock
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h04, 2'b10, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN_DMD>>1)+7'h04, 2'b10, 16'h0000);
//wriu 0x111f09 0x00
MDrv_WriteByte(0x111f09,0x00);
//Agate add end
/////////////////

// ********************************
// enable VDMCU clock
// [3:0] : reg_ckg_vdmcu
//         [0]  : disable clock
//         [1]  : invert clock
//         [3:2]: Select clock source
//                00: clk_dmplldiv10_div2(43.2 MHz)
//                01: reserved
//                10: reserved
//                11: select XTAL
// [12:8]: reg_ckg_vd200
//         [0]  : disable clock
//         [1]  : invert clock
//         [4:2]: Select clock source
//                000: 170 MHz (MPLL_DIV_BUF)
//                001: 160 MHz
//                010: 140 MHz
//                011: 123 MHz
//                100: 180 MHz
//                101: mem_clock
//                110: mem_clock div 2
//                111: select XTAL
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h21, 2'b11, 16'h0000);
MDrv_WriteByte(0x101e38, 0x00);
MDrv_WriteByte(0x101e39, 0x03);

// =================================================================
//  Turn TSP
// =================================================================

// turn on tsp_clk, Because Select TS0 Path
// [4:0]  : reg_ckg_tsp  => CLK_TSP clock setting
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Clock source     //[4:2]: Clock source
//               00:      172 MHz //       000    : 144 MHz(default select)
//               01:      144 MHz //       001    : 123 MHz
//               10:      123 MHz //       010    : 108 MHz
//               11:      108 MHz //       011    : 72  MHz
//                                //       100~110: Undefined
//                                //       111    : select XTAL
// [11:8] : reg_ckg_stc0  => CLK_STC0 clock setting
//        [0]  : disable clock
//        [1]  : invert clock
//        [3:2]: Clock source
//               00: select STC0 synthesizer outputtsp_top_wp(default select)
//               01: 1
//               10: 27MHz
//               11: select XTAL
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0000);
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0004); //A5 modify
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h2a, 2'b11, 16'h0004); //A5 modify
//MDrv_WriteByte(0x100b55, 0x00);
//MDrv_WriteByte(0x100b54, 0x04);

// set the ts0_clk from demod
// [3:0]: CLK_TS0 clock setting
//       [0]  : disable
//       [1]  : invert clock
//       [3:2]: Select clock source
//              00: select TS0_CLK
//              01: select TS1_CLK
//              10: reserved
//              11: clk_demod_ts_p
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
// `RIU_W((`RIUBASE_CLKGEN0>>1)+7'h28 , 2'b11, 16'h000c);
//MDrv_WriteByte(0x100b51, 0x00);
//MDrv_WriteByte(0x100b50, 0x0c);



// if the next line is not marked, the data is from demod, else is from ts0 pad
// set the ts0 input from demod
// [1:0]: Sourxe selection for TS channel 0
//         2'b00: come from PAD_TS0
//         2'b01: come from PAD_TS1
//         2'b10: come from DeMOD_TOP
// [9:8]: Sourxe selection for TS channel 1
//          00: from PAD_TS0
//          01: from PAD_TS1
//          10: from DEMOD_TOP
// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
// `RIU_W((`RIUBASE_CHIP>>1)+7'h11   , 2'b11, 16'h0002);
// wriu 0x101e23 0x00
MDrv_WriteByte(0x101e22, 0x02);

MDrv_WriteByte(0x103c0e, 0x01);
MDrv_WriteByte(0x000e13, 0x09);//fix: uart rx enable

#else

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) //T4
    /************************************************************************
     * T4 U02 ONLY.
     * for T4 U02 and after, this bit0 is mux for DMD muc and HK,
     * bit0: 0:HK can rw bank 0x1120, 1: DMD mcu can rw bank 0x1120;
     ************************************************************************/
    INTERN_DVBT_Write_VD_DMD_Byte(0x101E39, 0x00); //mux from DMD MCU to HK.
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2)
    /************************************************************************
     * T10 U01
     * This bit0 is mux for DMD muc and HK,
     * bit0: 0:HK can rw bank 0x1120, 1: DMD mcu can rw bank 0x1120;
     ************************************************************************/
    INTERN_DVBT_Write_VD_DMD_Byte(0x101E39, 0x00); //mux from DMD MCU to HK.
#endif

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    //<<CLK_GEN1_DVB_t >>
    if ( MDrv_ReadByte( 0x001ecf) == 0x00 )
       MDrv_WriteByte(0x100b42, 0x10);      // reg_ckg_vdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz
    else  //after t3_u02
       MDrv_WriteByte(0x100b42, 0x0D);      // reg_ckg_vdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz

    MDrv_WriteByte(0x100b43, 0x01);         // reg_ckg_vd200@0x21[11:8]

    MDrv_WriteByte(0x100b44, 0x00);         // enable mail-box clock          (bank_CLKGEN0)
    MDrv_WriteByte(0x100b45, 0x00);         // enable mail-box clock

    MDrv_WriteByte(0x103314, 0x00);         // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    MDrv_WriteByte(0x103315, 0x01);         // reg_ckg_dvbtc_innc@0x0a[11:8]

    MDrv_WriteByte(0x10330a, 0x00);         // reg_ckg_atsc_adcd_sync@0x05[3:0] : ADCCLK
    MDrv_WriteByte(0x10330b, 0x00);

    MDrv_WriteByte(0x10330c, 0x00);         // reg_ckg_dvbtc_inner1x@0x06[3:0] : MPLLDIV10/4=21.5MHz
    MDrv_WriteByte(0x10330d, 0x00);         // reg_ckg_dvbtc_inner2x@0x06[11:8]: MPLLDIV10/2=43.2MHz

    MDrv_WriteByte(0x10330e, 0x00);         // reg_ckg_dvbtc_inner4x@0x07[3:0] : MPLLDIV10=86.4MHz
    MDrv_WriteByte(0x10330f, 0x00);

    MDrv_WriteByte(0x103310, 0x00);         // reg_ckg_dvbtc_outer1x@0x08[3:0] : MPLLDIV10/2=43.2MHz
    MDrv_WriteByte(0x103311, 0x00);         // reg_ckg_dvbtc_outer2x@0x08[11:8]: MPLLDIV10=86.4MHz

    MDrv_WriteByte(0x103312, 0x00);         // dvbt_t:0x0000, dvb_c: 0x0004
    MDrv_WriteByte(0x103313, 0x00);

    MDrv_WriteByte(0x103314, 0x00);         // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    MDrv_WriteByte(0x103315, 0x00);         // reg_ckg_dvbtc_innc@0x0a[11:8]

    MDrv_WriteByte(0x103316, 0x00);         // reg_ckg_dvbtc_eq8x@0x0b[3:0] : MPLLDIV3/2=144MHz
    MDrv_WriteByte(0x103317, 0x00);         // reg_ckg_dvbtc_eq@0x0b[11:8] : MPLLDIV3/16=18MHz

    MDrv_WriteByte(0x103318, 0x00);         // reg_ckg_dvbtc_sram0~3@0x0c[13:0]
    MDrv_WriteByte(0x103319, 0x00);

#if (!TS_SERIAL_OUTPUT_IF_CI_REMOVED)
    MDrv_WriteByte(0x103308, 0x01);         // parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x00);         // reg_ckg_dvbtc_ts@0x04

    MDrv_WriteByte(0x103300, 0x11);         // parallel mode: 0x0511 /serial mode 0x0400

    #if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x05);     // reg_ckg_dvbtmk_ts_out_mode@0x00
    #else
        MDrv_WriteByte(0x103301, 0x07);     // reg_ckg_dvbtmk_ts_out_mode@0x00
    #endif

#else // serial
    MDrv_WriteByte(0x103308, 0x01);         // parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x04);         // reg_ckg_dvbtc_ts@0x04

    MDrv_WriteByte(0x103300, 0x00);         // parallel mode: 0x0511 /serial mode 0x0400
    #if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x04);     // reg_ckg_dvbtmk_ts_out_mode@0x00
    #else
        MDrv_WriteByte(0x103301, 0x06);     // reg_ckg_dvbtmk_ts_out_mode@0x00
    #endif
#endif
    //MDrv_WriteByte(0x101e22, 0x02);       // internal TS connect to TS0:0x0002; to TS1:0x0200
    //MDrv_WriteByte(0x101e23, 0x00);       // reg_ts0~1_mux@0x11         (bank_CHIP)

    //MDrv_WriteByte(0x100b50, 0x08);       // internal TS0:0x0108;   internal TS1:0x0801
    //MDrv_WriteByte(0x100b51, 0x08);       // reg_ckg_ts0~1@0x28         (bank_CLKGEN0) << Ken 20090629

    MDrv_WriteByte(0x101e04, 0x00);         // reg_if_agc_pad_oen@0x02    (bank_CHIP)
    MDrv_WriteByte(0x101e05, 0x00);

//----------------------------------------------------------------------------------------
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) //T4
    //<<CLK_GEN1_DVB_t >>

    INTERN_DVBT_Write_VD_DMD_Byte(0x10331e, 0x10);          // reg_ckg_dmdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x103480, 0x00);          // release dmdmcu_rst
    INTERN_DVBT_Write_VD_DMD_Byte(0x103314, 0x00);          // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    INTERN_DVBT_Write_VD_DMD_Byte(0x103315, 0x01);          // reg_ckg_dvbtc_innc@0x0a[11:8]

    INTERN_DVBT_Write_VD_DMD_Byte(0x10330a, 0x00);          // reg_ckg_atsc_adcd_sync@0x05[3:0] : ADCCLK
    INTERN_DVBT_Write_VD_DMD_Byte(0x10330b, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x10330c, 0x00);          // reg_ckg_dvbtc_inner1x@0x06[3:0] : MPLLDIV10/4=21.5MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x10330d, 0x00);          // reg_ckg_dvbtc_inner2x@0x06[11:8]: MPLLDIV10/2=43.2MHz

    INTERN_DVBT_Write_VD_DMD_Byte(0x10330e, 0x00);          // reg_ckg_dvbtc_inner4x@0x07[3:0] : MPLLDIV10=86.4MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x10330f, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x103310, 0x00);          // reg_ckg_dvbtc_outer1x@0x08[3:0] : MPLLDIV10/2=43.2MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x103311, 0x00);          // reg_ckg_dvbtc_outer2x@0x08[11:8]: MPLLDIV10=86.4MHz

    INTERN_DVBT_Write_VD_DMD_Byte(0x103312, 0x00);          // dvbt_t:0x0000, dvb_c: 0x0004
    INTERN_DVBT_Write_VD_DMD_Byte(0x103313, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x103314, 0x00);          // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    INTERN_DVBT_Write_VD_DMD_Byte(0x103315, 0x00);          // reg_ckg_dvbtc_innc@0x0a[11:8]

    INTERN_DVBT_Write_VD_DMD_Byte(0x103316, 0x00);          // reg_ckg_dvbtc_eq8x@0x0b[3:0] : MPLLDIV3/2=144MHz
    INTERN_DVBT_Write_VD_DMD_Byte(0x103317, 0x00);          // reg_ckg_dvbtc_eq@0x0b[11:8] : MPLLDIV3/16=18MHz

    INTERN_DVBT_Write_VD_DMD_Byte(0x103318, 0x00);          // reg_ckg_dvbtc_sram0~3@0x0c[13:0]
    INTERN_DVBT_Write_VD_DMD_Byte(0x103319, 0x00);

#if (!TS_SERIAL_OUTPUT_IF_CI_REMOVED)
    MDrv_WriteByte(0x103308, 0x01);         // parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x00);         // reg_ckg_dvbtc_ts@0x04

    MDrv_WriteByte(0x103300, 0x11);         // parallel mode: 0x0511 /serial mode 0x0400

    #if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x05);     // reg_ckg_dvbtmk_ts_out_mode@0x00
    #else
        MDrv_WriteByte(0x103301, 0x07);     // reg_ckg_dvbtmk_ts_out_mode@0x00
    #endif

#else // serial
    MDrv_WriteByte(0x103308, 0x01);         // parallel mode:0x0001 / serial mode: 0x0401
    MDrv_WriteByte(0x103309, 0x04);         // reg_ckg_dvbtc_ts@0x04

    MDrv_WriteByte(0x103300, 0x00);         // parallel mode: 0x0511 /serial mode 0x0400
    #if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        MDrv_WriteByte(0x103301, 0x04);     // reg_ckg_dvbtmk_ts_out_mode@0x00
    #else
        MDrv_WriteByte(0x103301, 0x06);     // reg_ckg_dvbtmk_ts_out_mode@0x00
    #endif
#endif
// !!!
    //MDrv_WriteByte(0x101e22, 0x02);       // internal TS connect to TS0:0x0002; to TS1:0x0200
    //MDrv_WriteByte(0x101e23, 0x00);       // reg_ts0~1_mux@0x11         (bank_CHIP)

    //MDrv_WriteByte(0x100b50, 0x08);       // internal TS0:0x0108;   internal TS1:0x0801
    //MDrv_WriteByte(0x100b51, 0x01);       // reg_ckg_ts0~1@0x28         (bank_CLKGEN0) << Ken 20090629
// !!!
    //INTERN_DVBT_Write_VD_DMD_Byte(0x101e04, 0x00);        // reg_if_agc_pad_oen@0x02    (bank_CHIP)
    //INTERN_DVBT_Write_VD_DMD_Byte(0x101e05, 0x00);
    INTERN_DVBT_Write_VD_DMD_Byte(0x11286c, 0x00);
    MDrv_WriteByte(0x101e05, MDrv_ReadByte(0x101e05) & 0xCF);     // clear bit 12, 13

//----------------------------------------
//For T4 Add
//At Chip Top
    INTERN_DVBT_Write_VD_DMD_Byte(0x101e9e, INTERN_DVBT_Read_VD_DMD_Byte(0x101e9e) & 0x3F);   // Bit6,7 Clean=0
//  INTERN_DVBT_Write_VD_DMD_Byte(0x101e9e, INTERN_DVBT_Read_VD_DMD_Byte(0x101e9e) | 0x80);   // Bit8 Set=1
//    MDrv_WriteByte(0x101e9e, 0x80);       // reg_agcgctrl
//    MDrv_WriteByte(0x101e9f, 0x00);
    INTERN_DVBT_Write_VD_DMD_Byte(0x101e05, INTERN_DVBT_Read_VD_DMD_Byte(0x101e05) | 0x20);
    INTERN_DVBT_Write_VD_DMD_Byte(0x101e05, INTERN_DVBT_Read_VD_DMD_Byte(0x101e05) & 0xEF);   // Bit12 Clean=0
//  MDrv_WriteByte(0x101e04, 0x00);         // reg_if_agc_pad_oen
//  MDrv_WriteByte(0x101e05, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x101eA1, INTERN_DVBT_Read_VD_DMD_Byte(0x101eA1) & 0x7F);   // Bit15 Clean=0
//  MDrv_WriteByte(0x101eA0, 0x00);         // reg_allpad_in
//  MDrv_WriteByte(0x101eA1, 0x00);

#if 1 // Even T4 U02, keep this part in the driver. It's no work, if Demod FW does this part.
// ---------------------------------------
//INTERN_DVBT_Write_VD_DMD_Byte(0x112002, 0x52);
  INTERN_DVBT_Write_VD_DMD_Byte(0x112002, 0x52);            // wreg vdbank_DEMOD_0+0x01 0052
    INTERN_DVBT_Write_VD_DMD_Byte(0x112003, 0x00);          // Release Ana misc resest

    INTERN_DVBT_Write_VD_DMD_Byte(0x112060, 0x00);          // ADC sign bit
    INTERN_DVBT_Write_VD_DMD_Byte(0x112061, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x112064, 0x00);          // ADC I channel offset // wreg vdbank_DEMOD_0+0x32 0c00
    INTERN_DVBT_Write_VD_DMD_Byte(0x112065, 0x0c);

    INTERN_DVBT_Write_VD_DMD_Byte(0x112066, 0x00);          // ADC Q channel offset
    INTERN_DVBT_Write_VD_DMD_Byte(0x112067, 0x0c);
#endif
// ---------------------------------------
    // enable ADC related parameter.
//#if(FRONTEND_TUNER_TYPE==MSTAR_AVATAR2)
    INTERN_DVBT_Write_VD_DMD_Byte(0x112816, ADC_CH_I_PGA_GAIN_CTRL);            //ADC I channel PGA gain control [4:0]
    INTERN_DVBT_Write_VD_DMD_Byte(0x112817, ADC_CH_I_PGA_GAIN_CTRL);            //ADC I channel PGA gain control [4:0]

//#endif
    INTERN_DVBT_Write_VD_DMD_Byte(0x112818, 0x03);          // Set enable ADC clock [ANA_PWDN_ADCI]
    INTERN_DVBT_Write_VD_DMD_Byte(0x112819, 0x00);          // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000
    INTERN_DVBT_Delayms(2);

    INTERN_DVBT_Write_VD_DMD_Byte(0x11286a, 0x86);          // wreg vdbank_DMD_ANA_MISC+0x35 0x1e04
    INTERN_DVBT_Write_VD_DMD_Byte(0x11286b, 0x1e);          // [ANA_MPLL_ICTRL]
    INTERN_DVBT_Delayms(2);

// ---------------------------------------------------------------------
// DVBT , DVBC Clock Setting
// ---------------------------------------------------------------------
    INTERN_DVBT_Write_VD_DMD_Byte(0x11286a, 0x06);          // Reset MPLL
    INTERN_DVBT_Write_VD_DMD_Byte(0x11286b, 0x1e);          // wreg vdbank_DMD_ANA_MISC+0x35 0x1e04
    INTERN_DVBT_Delayms(2);

    INTERN_DVBT_Write_VD_DMD_Byte(0x11286a, 0x06);          // Disable MPLL reset
    INTERN_DVBT_Write_VD_DMD_Byte(0x11286b, 0x06);          // wreg vdbank_DMD_ANA_MISC+0x35 0x0604
    INTERN_DVBT_Delayms(2);

    INTERN_DVBT_Write_VD_DMD_Byte(0x112866, 0x02);          // Set MPLL_LOOP_DIV_FIRST and SECOND
    INTERN_DVBT_Write_VD_DMD_Byte(0x112867, 0x09);          // [ANA_MPLL_LOOP_DIV_FIRST]

    INTERN_DVBT_Write_VD_DMD_Byte(0x112860, 0x00);          // Set MPLL_ADC_DIV_SEL [ANA_MPLL_CLK_DP_PD]
    INTERN_DVBT_Write_VD_DMD_Byte(0x112861, 0x13);          // wreg vdbank_DMD_ANA_MISC+0x30 0x1300

    INTERN_DVBT_Write_VD_DMD_Byte(0x112802, 0x40);          // Set IMUXS QMUXS [ANA_ADC_PWDNI]
    #if (VIF_SAW_ARCH!=4)
    INTERN_DVBT_Write_VD_DMD_Byte(0x112803, 0x04);
    #else
    INTERN_DVBT_Write_VD_DMD_Byte(0x112803, 0x12);
    #endif
    INTERN_DVBT_Write_VD_DMD_Byte(0x112818, 0x00);          // Set enable ADC clock [ANA_PWDN_ADCI]
    INTERN_DVBT_Write_VD_DMD_Byte(0x112819, 0x00);          // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000

    INTERN_DVBT_Write_VD_DMD_Byte(0x112840, 0x86);          // Disable PWDN_REF [ANA_VCLP]
    INTERN_DVBT_Write_VD_DMD_Byte(0x112841, 0x1e);          // wreg vdbank_DMD_ANA_MISC+0x20 0x0000

    /************************************************************************
     * T4 U02 ONLY.
     * for T4 U02 and after, this bit0 is mux for CH0 and CH5
     * 0x103C0E, bit0
     * bit0: 0: CH0, 1:CH5
     * Demod GUI use CH5 to read demod information.
     * CH0 is occupied by too many module, the data rate isn't enough for demod GUI.
     * Demod GUI would enable this bit, so it's ok to ignore it at the driver.
     ************************************************************************/
    // INTERN_DVBT_Write_VD_DMD_Byte(0x103C0E, 0x01); //mux for Ch0 -> Ch5

    /************************************************************************
     * T4 U02 ONLY.
     * for T4 U02 and after, this bit0 is mux for DMD muc and HK,
     * 0x101E39, bit0
     * bit0: 0:HK can rw bank 0x1120, 1: DMD mcu can rw bank 0x1120;
     ************************************************************************/
    INTERN_DVBT_Write_VD_DMD_Byte(0x101E39, 0x01); //mux from HK to DMD MCU

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2)
    U8 tmp;
    //------------------- initial by DMD START---------------------------
     INTERN_DVBT_Write_VD_DMD_Byte(0x112002, 0x52);                            // wreg vdbank_DEMOD_0+0x01 0052
     INTERN_DVBT_Write_VD_DMD_Byte(0x112003, 0x00);                            // Release Ana misc resest
     INTERN_DVBT_Write_VD_DMD_Byte(0x112060, 0x00);                            // ADC sign bit
     INTERN_DVBT_Write_VD_DMD_Byte(0x112061, 0x00);
     INTERN_DVBT_Write_VD_DMD_Byte(0x112064, 0x00);                            // ADC I channel offset // wreg vdbank_DEMOD_0+0x32 0c00
     INTERN_DVBT_Write_VD_DMD_Byte(0x112065, 0x0c);
     INTERN_DVBT_Write_VD_DMD_Byte(0x112066, 0x00);                            // ADC Q channel offset
     INTERN_DVBT_Write_VD_DMD_Byte(0x112067, 0x0c);
     // ---------------------------------------
     // enable ADC related parameter.
     INTERN_DVBT_Write_VD_DMD_Byte(0x11286a, 0x04);                            // wreg vdbank_DMD_ANA_MISC+0x35 0x1e04
     INTERN_DVBT_Write_VD_DMD_Byte(0x11286b, 0x06);                            // [ANA_MPLL_ICTRL]
     INTERN_DVBT_Delayms(2);
     INTERN_DVBT_Write_VD_DMD_Byte(0x112868, 0x00);                            // Set enable ADC clock [ANA_PWDN_ADCI]
     INTERN_DVBT_Write_VD_DMD_Byte(0x112869, 0x00);                            // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000
     INTERN_DVBT_Delayms(2);
     // ---------------------------------------------------------------------
     // DVBT , DVBC Clock Setting
     // ---------------------------------------------------------------------
     INTERN_DVBT_Write_VD_DMD_Byte(0x112866, 0x00);                            // Set MPLL_LOOP_DIV_FIRST and SECOND
     INTERN_DVBT_Write_VD_DMD_Byte(0x112867, 0x24);                            // [ANA_MPLL_LOOP_DIV_FIRST]
     INTERN_DVBT_Write_VD_DMD_Byte(0x112860, 0x01);                            // Set MPLL_ADC_DIV_SEL [ANA_MPLL_CLK_DP_PD]
     INTERN_DVBT_Write_VD_DMD_Byte(0x112861, 0x13);                            // wreg vdbank_DMD_ANA_MISC+0x30 0x1300
     INTERN_DVBT_Write_VD_DMD_Byte(0x112802, 0x40);                            // Set IMUXS QMUXS [ANA_ADC_PWDNI]
     #if (VIF_SAW_ARCH!=4)
     INTERN_DVBT_Write_VD_DMD_Byte(0x112803, 0x04);
     #else
     INTERN_DVBT_Write_VD_DMD_Byte(0x112803, 0x12);
     #endif
/*
#if(FRONTEND_TUNER_TYPE!=MSTAR_AVATAR2)
     INTERN_DVBT_Write_VD_DMD_Byte(0x112816, 0x05);                            // Set enable ADC clock [ANA_PWDN_ADCI]
#endif
*/
     INTERN_DVBT_Write_VD_DMD_Byte(0x112817, 0x05);                            // wreg vdbank_DMD_ANA_MISC+0x0c 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x112818, 0x03);                            // Disable PWDN_REF [ANA_VCLP]
     INTERN_DVBT_Write_VD_DMD_Byte(0x112818, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x112819, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x112840, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x112841, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x11286c, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x1120A0, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000
     INTERN_DVBT_Write_VD_DMD_Byte(0x1120A1, 0x00);                        // wreg vdbank_DMD_ANA_MISC+0x20 0x0000

     //------------------- initial by DMD END-----------------------------
    MDrv_WriteByte(0x10331E, 0x10);         // reg_ckg_vdmcu@0x21[4:0]        (bank_CLKGEN0) //108MHz
    // reg_ckg_dmdmcu@0x0f[4:0] (Enable DMD MCU clock and speed select)
    // [4:2] 0(172MHz),1(160MHz),2(144MHz),3(123MHz),4(108MHz),5(mem_clk),6(mem_clk/2),7(XTAL)  @
    MDrv_WriteByte(0x103480, 0x00);
    // reg_ckg_dvbtc_adc@0x0a[3:0] (Enable clk_adcd_p at adcd_sync module)
    MDrv_WriteByte(0x103314, 0x00);
    // reg_ckg_atsc_adcd_sync@0x05[3:0] Enable clk_atsc_adcd_sync(adcd_sync module) =ADC Clock.
    MDrv_WriteByte(0x111f0a, 0x00);
    MDrv_WriteByte(0x111f0b, 0x00);
    // reg_ckg_atsc200_ph3@0x01[11:8]  24*29/2/2=174MHz
    // reg_ckg_atsc200_ph1@0x01[3:0]    24*29/2/2=174MHz + 900 shift
    MDrv_WriteByte(0x111f02, 0x01);
    MDrv_WriteByte(0x111f03, 0x01);
    // reg_ckg_atsc25@0x02[11:8]  24*29/2/7/2=24.85MHz
    // reg_ckg_atsc50@0x02[3:0]  24*29/2/7=49.7MHz
    MDrv_WriteByte(0x111f04, 0x01);
    MDrv_WriteByte(0x111f05, 0x01);
    // reg_ckg_atsc_ce25@0x03[11:8]  24*29/2/16=21.75MHz
    // reg_ckg_atsc_eq25@0x03[3:0]  24*29/2/2/8=21.75MHz
    MDrv_WriteByte(0x111f06, 0x01);
    MDrv_WriteByte(0x111f07, 0x01);
    // reg_ckg_dvbtc_inner2x@0x06[11:8] (DVBT Only !)
    // reg_ckg_dvbtc_inner1x@0x06[3:0] (DVBT Only !)
    MDrv_WriteByte(0x111f0c, 0x00);
    MDrv_WriteByte(0x111f0d, 0x00);
    // reg_ckg_dvbtc_inner4x@0x07[3:0] (DVBT Only !)
    MDrv_WriteByte(0x111f0e, 0x00);
    // reg_ckg_dvbtc_outer2x@0x08[11:8] (DVBT Only !)
    // reg_ckg_dvbtc_outer1x@0x08[3:0] (DVBT Only!)
    MDrv_WriteByte(0x111f10, 0x00);
    MDrv_WriteByte(0x111f11, 0x00);
    // reg_ckg_dvbtc_outer2x_c@0x09[3:0]
    MDrv_WriteByte(0x111f12, 0x00);
    // reg_ckg_dvbtc_innc@0x0a[11:8] (DVBC only !)
    MDrv_WriteByte(0x111f15, 0x01);
    // reg_ckg_dvbtc_eq8x@0x0b[11:8]  (DVBC only!)
    // reg_ckg_dvbtc_eq@0x0b[3:0] (DVBC Only !)
    MDrv_WriteByte(0x111f16, 0x01);
    MDrv_WriteByte(0x111f17, 0x01);
    // reg_ckg_dvbtc_sram3@0x0c[13:12]
    // reg_ckg_dvbtc_sram2@0x0c[9:8]
    // reg_ckg_dvbtc_sram1@0x0c[5:4]
    // reg_ckg_dvbtc_sram0@0x0c[1:0]
    MDrv_WriteByte(0x111f18, 0x00);
    MDrv_WriteByte(0x111f19, 0x00);
    // reg_ckg_demod_test_in_en@0x00[11]
    // reg_ckg_dvbtm_ts_out_mode@0x00[10]  set 1b1 use Non-gating clock.
    // reg_ckg_atsc_dvbtc_ts_inv@0x00[9] -> Invert PAD_TS1_CLK polarity !
    // reg_ckg_atsc_dvb_div_sel@0x00[8]
    //   -> clk_atsc_dvb_div= 0: MPLLDIV2(24*29/2=348MHz), 1:MPLLDIV3(24*29/3=232MHz)
    // reg_ckg_dvbtm_ts_divnum@0x00[4:0]
    //   -> clk_atsc_dvb_div (MHz) / ((reg_ckg_dvbtm_ts_divnum+1)*2)
    INTERN_DVBT_Write_VD_DMD_Byte(0x103300, 0x11);
    INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x05);
    // reg_ckg_dvbtc_ts@0x04[11:8]
    // reg_ckg_atsc_ts@0x04[3:0]
#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
    //`RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h0100);// ts clock= ts_div_clk(parallel-TS Mode)
    INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);
    INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x00);
#else
    //`RIU_W((`RIUBASE_CLKGEN1>>1)+7'h04, 2'b11, 16'h????);// ts clock= 62MHz(Series-TS Mode)
    INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);
    INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x04);
#endif
    // reg_ckg_vifdbb_144m@0x0e[11:8]  144MHz
    // reg_ckg_vifdbb_43m@0x0e[3:0]  43.2MHz
    MDrv_WriteByte(0x111f1c, 0x01);
    MDrv_WriteByte(0x111f1d, 0x01);
    // reg_ckg_vifdbb_vdac@0x0d[11:8]  43.2MHz
    // reg_ckg_vifdbb_dac@0x0d[3:0]  43.2MHz
    MDrv_WriteByte(0x111f1a, 0x01);
    MDrv_WriteByte(0x111f1b, 0x01);
//-------------------------------------------------------------------
// Enable TS PAD
//-------------------------------------------------------------------

// Set reg_ts1config@0x57[13:11]-reg_CHIPTOP = 3bx10, DMD will output Transport stream to PAD_TS1_XX
// wriu 0x101eaf 8'bxxx1_0xxx
#if (CHIP_FAMILY_TYPE != CHIP_FAMILY_J2)
    tmp = 0x10;
    INTERN_DVBT_Write_VD_DMD_Byte(0x101e9e, 0x00);
    INTERN_DVBT_Write_VD_DMD_Byte(0x101eaf, tmp);
#endif
//-------------------------------------------------------------------
// Enable RF_AGC, IF_AGC PAD
//-------------------------------------------------------------------

// reg_agcgctrl = 2d2  PAD_RF_AGC(up_agc) , PAD_IF_AGC(dn_agc) is for Demod control Tuner. by up/dn AGC mode
// reg_agcgctrl = 2d1  PAD_TGPIO0(up_agc) , PAD_TGPIO1(dn_agc) is for Demod control Tuner by up/dn AGC mode.
// reg_agcgctrl = 2d0  PAD_RF_AGC , PAD_IF_AGC is for Demod control Tuner. by PWM AGC mode
// reg_if_agc_pad_oen@reg_CHIPTOP-0x02[12]  set 1b0 to enable PAD_IF_AGC
// reg_rf_agc_pad_oen@reg-CHIPTOP-0x02[13] set 1b0 to enable PAD_RF_AGC.
// wriu 0x101e05 8'bxx00_xxxx
    tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x101e05);
    tmp &= ~0x30;
    INTERN_DVBT_Write_VD_DMD_Byte(0x101e05, tmp);

    INTERN_DVBT_Write_VD_DMD_Byte(0x101ea0, 0x00);
    INTERN_DVBT_Write_VD_DMD_Byte(0x101ea1, 0x00);

    INTERN_DVBT_Write_VD_DMD_Byte(0x101E39, 0x03); //mux from HK to DMD MCU.

#endif

#endif
}

/***********************************************************************************
  Subject:    Power on initialized function
  Function:   INTERN_DVBT_Power_On_Initialization
  Parmeter:
  Return:     BOOLEAN
  Remark:
************************************************************************************/

BOOLEAN INTERN_DVBT_Power_On_Initialization ( void )
{
   	U8            cData = 0;
    U8            status = true;
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
    //U8            cData;
#else

#endif
    DBG_INTERN_DVBT(printf("INTERN_DVBT_Power_On_Initialization\n"));
    msAPI_Tuner_ResetDemodMode();
    //INTERN_DVBT_InitRegBase();

    LoadDspStatus = 0xff; //1: DVBT, 2:DVBC, 3:ATSC, 0xff: Null

    INTERN_DVBT_InitClkgen();

    //// Firmware download //////////
    DBG_INTERN_DVBT(printf("INTERN_DVBT Load DSP...\n"));
    //MsOS_DelayTask(100);

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    if (MDrv_ReadByte(0x101E3E) != 0x02) // DVBT = BIT1 -> 0x02
    {
        if (INTERN_DVBT_LoadDSPCode() == FALSE)
        {
            printf("DVB-T Load DSP Code Fail\n");
            return FALSE;
        }
        else
        {
            printf("DVB-T Load DSP Code OK\n");
        }
    }
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

    if (INTERN_DVBT_LoadDSPCode() == FALSE)
    {
        printf("DVB-T Load DSP Code Fail\n");
        return FALSE;
    }
    else
    {
        printf("DVB-T Load DSP Code OK\n");
    }
#endif

    //// MCU Reset //////////
    DBG_INTERN_DVBT(printf("INTERN_DVBT Reset...\n"));
    if (INTERN_DVBT_Reset() == FALSE)
    {
        DBG_INTERN_DVBT(printf("Fail\n"));
        return FALSE;
    }
    else
    {
        DBG_INTERN_DVBT(printf("OK\n"));
    }

    // reset FDP
    INTERN_DVBT_WriteReg(0x2200, 0xFF);
    // SRAM setting, DVB-T use it.
    // 0x2204, Bit0, 0:DVB-T use, 1: VIF use
    INTERN_DVBT_ReadReg(0x2204,&cData);
    INTERN_DVBT_WriteReg(0x2204, cData&0xFE);

    status &= INTERN_DVBT_DSPReg_Init();

    return status;
}

/************************************************************************************************
  Subject:    Driving control
  Function:   INTERN_DVBT_Driving_Control
  Parmeter:   bInversionEnable : TRUE For High
  Return:      void
  Remark:
*************************************************************************************************/
void INTERN_DVBT_Driving_Control(BOOLEAN bEnable)
{
    U8    u8Temp;

    u8Temp = INTERN_DVBT_Read_VD_DMD_Byte(0x101E10);

    if (bEnable)
    {
       u8Temp = u8Temp | 0x01; //bit0: clk, bit1~8:data , bit9: sync, bit10:valid
    }
    else
    {
       u8Temp = u8Temp & (~0x01);
    }

    DBG_INTERN_DVBT(printf("---> INTERN_DVBT_Driving_Control(Bit0) = 0x%bx \n",u8Temp));
    INTERN_DVBT_Write_VD_DMD_Byte(0x101E10, u8Temp);
}
/************************************************************************************************
  Subject:    Clk Inversion control
  Function:   INTERN_DVBT_Clk_Inversion_Control
  Parmeter:   bInversionEnable : TRUE For Inversion Action
  Return:      void
  Remark:
*************************************************************************************************/
void INTERN_DVBT_Clk_Inversion_Control(BOOLEAN bInversionEnable)
{
    U8    u8Temp;

    u8Temp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);

    if (bInversionEnable)
    {
       u8Temp = u8Temp | 0x02; //bit 9: clk inv
    }
    else
    {
       u8Temp = u8Temp & (~0x02);
    }

    DBG_INTERN_DVBT(printf("---> Inversion(Bit9) = 0x%x \n",u8Temp));
    INTERN_DVBT_Write_VD_DMD_Byte(0x103301, u8Temp);
}
/************************************************************************************************
  Subject:    Transport stream serial/parallel control
  Function:   INTERN_DVBT_Serial_Control
  Parmeter:   bEnable : TRUE For serial
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN INTERN_DVBT_Serial_Control(BOOLEAN bEnable)
{
    U8            status = true;
    U8 tmp = 0x00;

    DBG_INTERN_DVBT(printf(" @INTERN_DVBT_ts... \n"));

    if (bEnable)    //Serial mode for TS pad
    {
        // serial
        INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);   // serial mode: 0x0401
        INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x04);   // reg_ckg_dvbtc_ts@0x04

        INTERN_DVBT_Write_VD_DMD_Byte(0x103300, 0x00);   // serial mode 0x0400
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x04);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x04;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
#else
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x06;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
#endif

#else

#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x04);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#else
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
#endif

#endif

//        INTERN_DVBT_Write_VD_DMD_Byte(0x101EA5, INTERN_DVBT_Read_MBX_Byte(0x101EA5)&0xEF);   // PAD_TS1 is used as output
//        INTERN_DVBT_Write_VD_DMD_Byte(0x101EAF, INTERN_DVBT_Read_MBX_Byte(0x101EAF)&0xE3);   // PAD_TS1 Disable TS CLK PAD

        //// INTERN_DVBT TS Control: Serial //////////
        gsCmdPacket.cmd_code = CMD_TS_CTRL;

        gsCmdPacket.param[0] = TS_SERIAL;
#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        gsCmdPacket.param[1] = 0;//TS_CLK_NO_INV;
#else
        gsCmdPacket.param[1] = 1;//TS_CLK_INVERSE;
#endif
        status &= INTERN_DVBT_Cmd_Packet_Send(&gsCmdPacket, 2);
    }
    else
    {
        //parallel
        INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);   // parallel mode:0x0001
        INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x00);   // reg_ckg_dvbtc_ts@0x04

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

        //MDrv_WriteByte(0x103300, 0x11);   // parallel mode: 0x0511 => ts_clk=288/(2*(0x11+1))=8MHz
        INTERN_DVBT_Write_VD_DMD_Byte(0x103300, 0x0b);   // parallel mode: 0x0513 => ts_clk=288/(2*(0x13+1))=7.2MHz
#if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00

        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x06;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);

#else
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x06;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
#endif

#else

        //MDrv_WriteByte(0x103300, 0x11);   // parallel mode: 0x0511 => ts_clk=288/(2*(0x11+1))=8MHz
        INTERN_DVBT_Write_VD_DMD_Byte(0x103300, 0x13);   // parallel mode: 0x0513 => ts_clk=288/(2*(0x13+1))=7.2MHz
#if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x05);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x05;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
#else
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x07);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x07;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
#endif

#endif


//        INTERN_DVBT_Write_VD_DMD_Byte(0x101EA5, INTERN_DVBT_Read_MBX_Byte(0x101EA5)|0x10);   // PAD_TS1 is used as output
//        INTERN_DVBT_Write_VD_DMD_Byte(0x101EAF, INTERN_DVBT_Read_MBX_Byte(0x101EAF)|0x18);   // PAD_TS1 enable TS clk pad

        //// INTERN_DVBT TS Control: Parallel //////////
        gsCmdPacket.cmd_code = CMD_TS_CTRL;

        gsCmdPacket.param[0] = TS_PARALLEL;
#if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
        gsCmdPacket.param[1] = 0;//TS_CLK_NO_INV;
#else
        gsCmdPacket.param[1] = 1;//TS_CLK_INVERSE;
#endif
        status &= INTERN_DVBT_Cmd_Packet_Send(&gsCmdPacket, 2);
    }

    DBG_INTERN_DVBT(printf("---> Inversion(Bit5) = 0x%x \n",gsCmdPacket.param[1] ));

    INTERN_DVBT_Driving_Control(INTERN_DVBT_DTV_DRIVING_LEVEL);
    return status;
}

/************************************************************************************************
  Subject:    channel change config
  Function:   INTERN_DVBT_Config
  Parmeter:   BW: bandwidth
  Return:     BOOLEAN :
  Remark:
*************************************************************************************************/
BOOLEAN INTERN_DVBT_Config ( RF_CHANNEL_BANDWIDTH BW, BOOLEAN bSerialTS, BOOLEAN bPalBG, BOOLEAN bLPSel)
{
    U8              bandwidth;
    U8              status = true;
    #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

    U8				tmp = 0x00;
    #endif

    DBG_INTERN_DVBT(printf(" @INTERN_DVBT_config\n"));


    switch(BW)
    {
        case E_RF_CH_BAND_6MHz:
            bandwidth = 1;
            break;
        case E_RF_CH_BAND_7MHz:
            bandwidth = 2;
            break;
        case E_RF_CH_BAND_8MHz:
        default:
            bandwidth = 3;
            break;
    }

    status &= INTERN_DVBT_Reset();

#if 1
    //FC Freq
    #if DTV_LOW_IF_FREQ
    {
        U16 CFG_FS;
        U8  CFG_FC_L, CFG_FC_H;
        U8  CFG_Fif_L, CFG_Fif_H;
#if 0
	#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
        (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
        (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)
    	CFG_FS=(U16)(FC_H<<8)+FC_L;
	#else
    	CFG_FS=(U16)(DVBT_CFG_FS_H<<8)+DVBT_CFG_FS_L;
	#endif
#endif
	    CFG_FS= DVBT_FS;

        if (E_RF_CH_BAND_8MHz==BW)
        {
            CFG_FC_L=(U8)(CFG_FS-DTV_IF_8M_FREQ);
            CFG_FC_H=(U8)((CFG_FS-DTV_IF_8M_FREQ)>>8);
            CFG_Fif_L = (U8)DTV_IF_8M_FREQ;
            CFG_Fif_H = (U8)(DTV_IF_8M_FREQ>>8);
        }
        else if(E_RF_CH_BAND_7MHz==BW)
        {
            CFG_FC_L=(U8)(CFG_FS-DTV_IF_7M_FREQ);
            CFG_FC_H=(U8)((CFG_FS-DTV_IF_7M_FREQ)>>8);
            CFG_Fif_L = (U8)DTV_IF_7M_FREQ;
            CFG_Fif_H = (U8)(DTV_IF_7M_FREQ>>8);
        }
        else
        {
            CFG_FC_L=(U8)(CFG_FS-DTV_IF_6M_FREQ);
            CFG_FC_H=(U8)((CFG_FS-DTV_IF_6M_FREQ)>>8);
            CFG_Fif_L = (U8)DTV_IF_6M_FREQ;
            CFG_Fif_H = (U8)(DTV_IF_6M_FREQ>>8);
        }
        status &= INTERN_DVBT_WriteDspReg(E_DMD_DVBT_N_CFG_FIF_L, CFG_Fif_L);
        status &= INTERN_DVBT_WriteDspReg(E_DMD_DVBT_N_CFG_FIF_H, CFG_Fif_H);
        status &= INTERN_DVBT_WriteDspReg(E_DMD_DVBT_N_CFG_FC_L, CFG_FC_L);
        status &= INTERN_DVBT_WriteDspReg(E_DMD_DVBT_N_CFG_FC_H, CFG_FC_H);
    }
    #endif
#endif

    // BW mode
    status &= INTERN_DVBT_WriteDspReg(E_DMD_DVBT_N_CFG_BW, bandwidth);

    // TS mode
//    status &= INTERN_DVBT_WriteDspReg(0x2A, bSerialTS? 0x01:0x00);
    status &= INTERN_DVBT_WriteDspReg(E_DMD_DVBT_N_CFG_TS_SERIAL, bSerialTS? 0x01:0x00);

    // For Analog CCI 0:PAL B/G (Nordig), 1:PAL I (D-Book)
    status &= INTERN_DVBT_WriteDspReg(E_DMD_DVBT_N_CFG_CCI, bPalBG? 0x00:0x01);

    // For Hierarchy mode HP/LP selection 0: HP, 1: LP
    status &= INTERN_DVBT_WriteDspReg(E_DMD_DVBT_N_CFG_LP_SEL, bLPSel? 0x01:0x00);

//// INTERN_DVBT system init: DVB-T //////////
    gsCmdPacket.cmd_code = CMD_SYSTEM_INIT;

    gsCmdPacket.param[0] = E_SYS_DVBT;
    status &= INTERN_DVBT_Cmd_Packet_Send(&gsCmdPacket, 1);

    /*
     * Actually, Under DSP table architecture, cmd_code = CMD_DVBT_CONFIG
     * can skip.
     */
    //// DVB-T configurate ///////////////////
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))
#else
    gsCmdPacket.cmd_code = CMD_DVBT_CONFIG;
    status &= INTERN_DVBT_Cmd_Packet_Send(&gsCmdPacket, 1);
#endif

    if(bSerialTS)
    {
        // serial
        INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);   // parallel mode:0x0001 / serial mode: 0x0401
        INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x04);   // reg_ckg_dvbtc_ts@0x04

        INTERN_DVBT_Write_VD_DMD_Byte(0x103300, 0x00);   // parallel mode: 0x0511 /serial mode 0x0400
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

	#if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x04);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x04;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
    #else
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x06;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
    #endif

#else

    #if(INTERN_DVBT_TS_SERIAL_INVERSION == 0)
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x04);   // reg_ckg_dvbtmk_ts_out_mode@0x00
    #else
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
    #endif

#endif
    }
    else
    {
        //parallel
        INTERN_DVBT_Write_VD_DMD_Byte(0x103308, 0x01);   // parallel mode:0x0001 / serial mode: 0x0401
        INTERN_DVBT_Write_VD_DMD_Byte(0x103309, 0x00);   // reg_ckg_dvbtc_ts@0x04

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

        //MDrv_WriteByte(0x103300, 0x11);   // parallel mode: 0x0511 => ts_clk=288/(2*(0x11+1))=8MHz
        INTERN_DVBT_Write_VD_DMD_Byte(0x103300, 0x0b);   // parallel mode: 0x0513 => ts_clk=288/(2*(0x13+1))=7.2MHz
    #if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x06;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
    #else
        //INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x06);   // reg_ckg_dvbtmk_ts_out_mode@0x00
        tmp = INTERN_DVBT_Read_VD_DMD_Byte(0x103301);
        tmp |= 0x06;
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, tmp);
    #endif
    }

    // FSM_EN
   INTERN_DVBT_Write_MBX_Byte(MBRegBase + (0x0e)*2, 0x01);   // FSM_EN

#else

        //MDrv_WriteByte(0x103300, 0x11);   // parallel mode: 0x0511 => ts_clk=288/(2*(0x11+1))=8MHz
        INTERN_DVBT_Write_VD_DMD_Byte(0x103300, 0x13);   // parallel mode: 0x0513 => ts_clk=288/(2*(0x13+1))=7.2MHz
    #if(INTERN_DVBT_TS_PARALLEL_INVERSION == 0)
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x05);   // reg_ckg_dvbtmk_ts_out_mode@0x00
    #else
        INTERN_DVBT_Write_VD_DMD_Byte(0x103301, 0x07);   // reg_ckg_dvbtmk_ts_out_mode@0x00
    #endif
    }

#endif

    return status;
}
/************************************************************************************************
  Subject:    enable hw to lock channel
  Function:   INTERN_DVBT_Active
  Parmeter:   bEnable
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN INTERN_DVBT_Active(BOOLEAN bEnable)
{
    U8            status = true;

    DBG_INTERN_DVBT(printf(" @INTERN_DVBT_active\n"));

    //// INTERN_DVBT Finite State Machine on/off //////////
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))
    UNUSED(bEnable);
    INTERN_DVBT_Write_VD_DMD_Byte(0x112600 + (0x0e)*2, 0x01);   // FSM_EN
#else
    gsCmdPacket.cmd_code = CMD_FSM_CTRL;

    gsCmdPacket.param[0] = (U8)bEnable;
    status &= INTERN_DVBT_Cmd_Packet_Send(&gsCmdPacket, 1);
#endif

    return status;
}

/****************************************************************************
  Subject:    To get the DVBT constellation parameter
  Function:   INTERN_DVBT_Get_TPS_Parameter_Const
  Parmeter:   point to return parameter(0: QPSK, 1:16QAM, 2:64QAM)
  Return:     TRUE
              FALSE
  Remark:     The TPS parameters will be available after TPS lock
*****************************************************************************/
BOOLEAN INTERN_DVBT_Get_TPS_Parameter_Const( U16 * TPS_parameter)
{
    U8 tps_param;

    if ( INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x24, &tps_param) == FALSE )
        return FALSE;

    *TPS_parameter = tps_param & (BIT0|BIT1) ;
    return TRUE;
}

/****************************************************************************
  Subject:    To get the DVBT parameter
  Function:   INTERN_DVBT_Get_TPS_Info
  Parmeter:   point to return parameter
              Constellation (b2 ~ b0)  : 0~2 => QPSK, 16QAM, 64QAM
              Hierarchy (b5 ~ b3))     : 0~3 => None, Aplha1, Aplha2, Aplha4
              LP Code Rate (b8 ~ b6)   : 0~4 => 1/2, 2/3, 3/4, 5/6, 7/8
              HP Code Rate (b11 ~ b9)  : 0~4 => 1/2, 2/3, 3/4, 5/6, 7/8
              GI (b13 ~ b12)           : 0~3 => 1/32, 1/16, 1/8, 1/4
              FFT ( b14)          : 0~1 => 2K, 8K
              Priority(bit 15)      : 0~1=> HP,LP
  Return:     TRUE
              FALSE
  Remark:   The TPS parameters will be available after TPS lock
*****************************************************************************/
BOOLEAN INTERN_DVBT_Get_TPS_Info( U16 * TPS_parameter)
{
    U8 u8Temp;

    if (INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x22, &u8Temp) == FALSE)
        return FALSE;

    if ((u8Temp& 0x02) != 0x02)
    {
        return FALSE; //TPS unlock
    }
    else
    {
        if ( INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x24, &u8Temp) == FALSE )
            return FALSE;

        *TPS_parameter = u8Temp & 0x03;         //Constellation (b2 ~ b0)
        *TPS_parameter |= (u8Temp & 0x70) >> 1; //Hierarchy (b5 ~ b3)

        if ( INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x25, &u8Temp) == FALSE )
            return FALSE;

        *TPS_parameter |= (U16)(u8Temp & 0x07) << 6; //LP Code Rate (b8 ~ b6)
        *TPS_parameter |= (U16)(u8Temp & 0x70) << 5; //HP Code Rate (b11 ~ b9)

        if ( INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x26, &u8Temp) == FALSE )
            return FALSE;

        *TPS_parameter |= (U16)(u8Temp & 0x03) << 12; //GI (b13 ~ b12)
        *TPS_parameter |= (U16)(u8Temp & 0x30) << 10;  //FFT ( b14)

        if ( INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x0C, &u8Temp) == FALSE )
            return FALSE;

        *TPS_parameter |=(U16)(u8Temp&0x08)<<12;//Priority(bit 15)

    }
    return TRUE;
}

/************************************************************************************************
  Subject:    Return lock status
  Function:   INTERN_DVBT_Lock
  Parmeter:   eStatus :
  Return:     BOOLEAN
  Remark:
*************************************************************************************************/
BOOLEAN INTERN_DVBT_Lock( COFDM_LOCK_STATUS eStatus )
{
    U16 u16Address = 0;
    BYTE cData = 0;
    static BYTE cData_previous = 0;
    BYTE cBitMask = 0;

    static U32      u32FecLockTime;
#if (INTERN_DVBT_INTERNAL_DEBUG)
    float SFO;
    float CFO;
    float SNR;
    S16 pktErrNum;
    U8 tmpValue;
        U16 tmpValue1;
#endif

    switch( eStatus )
    {
    case COFDM_FEC_LOCK:
#if (INTERN_DVBT_INTERNAL_DEBUG)
                        //print debug message
//                  INTERN_DVBT_GetDigACI(&tmpValue);
//                  INTERN_DVBT_GetChannelLength(&tmpValue1);
//                      printf("@@@@ChannelLength = %d\n",tmpValue1);
                    INTERN_DVBT_GetFD(&tmpValue);
                        printf("@@@@FD index = %d\n",tmpValue);
                    INTERN_DVBT_Get_SW_ChannelLength(&tmpValue1);
                        printf("@@@@SW_ChannelLength = %d\n",tmpValue1);
                        INTERN_DVBT_GetUSE_VAR();
                        INTERN_DVBT_Version(&tmpValue1);
                        printf("@@@@Demod DSP FW Version number = R%d.%d\n",(tmpValue1>>8), (tmpValue1&0x000f));
                        INTERN_DVBT_Get_TPS_Info(&tmpValue1);
                        printf("@@@@TPS INFO = 0x%x\n", tmpValue1);
                        SNR = INTERN_DVBT_GetSNR();
                        printf("@@@@SNR = %d dB\n", (S32)SNR);
                        INTERN_DVBT_GetSFO(&SFO);
                        printf("@@@@SFO = %d ppm\n", (S32)SFO);
                        INTERN_DVBT_GetCFO(&CFO);
                        printf("@@@@CFO = %d kHz\n", (S32)CFO);
                        INTERN_DVBT_GetPacketErrorNum(&pktErrNum);
                        printf("@@@@PacketErrorNum = %d\n", pktErrNum);
#endif
    INTERN_DVBT_ReadReg(FEC_REG_BASE + 0xE0, &cData);
        //DBG_INTERN_DVBT(printf("*********************** cData = 0x%bx \n", cData));

        if(cData_previous!=cData)
        {
            DBG_INTERN_DVBT_ONELINE(printf("c=%bx ", cData));
            cData_previous=cData;
        }

        if (cData == 0x0B)
        {
            u32FecLockTime = MsOS_GetSystemTime();
            FECLock = TRUE;
            //DBG_INTERN_DVBT(printf("dmd_lock\n"));
//            DBG_INTERN_DVBT_ONELINE(printf("dmd_lock "));

            return TRUE;
        }
        else
        {
            if (FECLock == TRUE)
            {
                if ( ( MsOS_GetSystemTime() - u32FecLockTime ) < 3000 )
                    return TRUE;
            }
            FECLock = FALSE;
            DBG_INTERN_DVBT(printf("dmd_unlock\n"));
//            DBG_INTERN_DVBT_ONELINE(printf("dmd_unlock "));

            return FALSE;      // continuously un-lock
        }
        break;

    case COFDM_PSYNC_LOCK:
            u16Address =  FEC_REG_BASE + 0x2C; //FEC: P-sync Lock,
        cBitMask = BIT1;
        break;

    case COFDM_TPS_LOCK:
		#if (CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER)
		u16Address =  0x2222; //TPS HW Lock,
		cBitMask = BIT1;
		#else
        // For T4
        u16Address =  TOP_REG_BASE + 0x70;//TPS Lock,
        cBitMask = BIT3;
		#endif
        break;

    case COFDM_DCR_LOCK:
        u16Address =  0x2145; //DCR Lock,
        cBitMask = BIT0;
        break;

    case COFDM_AGC_LOCK:
        u16Address =  0x212F; //AGC Lock,
        cBitMask = BIT0;
        break;

    case COFDM_MODE_DET:
        u16Address =  0x24CF; //Mode CP Detect,
        cBitMask = BIT4;
        break;

    default:
        return FALSE;
    }

    if (INTERN_DVBT_ReadReg(u16Address, &cData) == FALSE)
        return FALSE;

    if ((cData & cBitMask) == cBitMask)
    {
        return TRUE;
    }

    return FALSE;

}

/****************************************************************************
  Subject:    To get the Post viterbi BER
  Function:   INTERN_DVBT_GetPostViterbiBer
  Parmeter:  Quility
  Return:       E_RESULT_SUCCESS
                   E_RESULT_FAILURE =>Read I2C fail, INTERN_DVBT_VIT_STATUS_NG
  Remark:     For the Performance issue, here we just return the Post Value.(Not BER)
                   We will not read the Period, and have the "/256/8"
*****************************************************************************/
BOOLEAN INTERN_DVBT_GetPostViterbiBer(float *ber)
{
    U8            status = true;
    U8            reg = 0;
    U8            reg_frz = 0;
    U16           BitErrPeriod = 0;
    U32           BitErr = 0;
    U16           PktErr = 0;

    /////////// Post-Viterbi BER /////////////

    // bank 7 0x32 [7] reg_bit_err_num_freeze
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x32, &reg_frz);
    status &= INTERN_DVBT_WriteReg(FEC_REG_BASE + 0x32, reg_frz|0x80);

    // bank 7 0x30 [7:0] reg_bit_err_sblprd_7_0
    //               [15:8] reg_bit_err_sblprd_15_8
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x31, &reg);
    BitErrPeriod = reg;

    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x30, &reg);
    BitErrPeriod = (BitErrPeriod << 8)|reg;

    // bank 7 0x3a [7:0] reg_bit_err_num_7_0
    //               [15:8] reg_bit_err_num_15_8
    // bank 7 0x3c [7:0] reg_bit_err_num_23_16
    //               [15:8] reg_bit_err_num_31_24

    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x3D, &reg);
    BitErr = reg;

    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x3C, &reg);
    BitErr = (BitErr << 8)|reg;

    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x3B, &reg);
    BitErr = (BitErr << 8)|reg;

    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x3A, &reg);
    BitErr = (BitErr << 8)|reg;

    // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
    //               [15:8] reg_uncrt_pkt_num_15_8
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x3F, &reg);
    PktErr = reg;

    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x3E, &reg);
    PktErr = (PktErr << 8)|reg;

    // bank 7 0x32 [7] reg_bit_err_num_freeze
    status &= INTERN_DVBT_WriteReg(FEC_REG_BASE + 0x32, reg_frz);

    if (BitErrPeriod == 0 )    //protect 0
        BitErrPeriod = 1;

    if (BitErr <=0 )
        *ber = 0.5 / ((float)BitErrPeriod*128*188*8);
    else
        *ber = (float)BitErr / ((float)BitErrPeriod*128*188*8);


   DBG_GET_SIGNAL(printf("INTERN_DVBT PostVitBER = %8.3e \n ", *ber));
   DBG_GET_SIGNAL(printf("INTERN_DVBT PktErr = %d \n ", (int)PktErr));


    return status;
}

/****************************************************************************
  Subject:    Function providing approx. result of Log10(X)
  Function:   Log10Approx
  Parmeter:   Operand X in float
  Return:     Approx. value of Log10(X) in float
  Remark:      Ouput range from 0.0, 0.3 to 9.6 (input 1 to 2^32)
*****************************************************************************/
static float Log10Approx(float flt_x)
{
    U32       u32_temp = 1;
    U8        indx = 0;

    do {
        u32_temp = u32_temp << 1;
        if (flt_x < (float)u32_temp)
            break;
    }while (++indx < 32);

    // 10*log10(X) ~= 0.3*N, when X ~= 2^N
    return (float)0.3 * indx;
}

/****************************************************************************
  Subject:    Read the signal to noise ratio (SNR)
  Function:   INTERN_DVBT_GetSNR
  Parmeter:   None
  Return:     -1 mean I2C fail, otherwise I2C success then return SNR value
  Remark:
*****************************************************************************/
float INTERN_DVBT_GetSNR (void)
{
    U8            status = true;
    U8            reg = 0;
    U8            reg_frz = 0;
    U32           noise_power = 0;
    float         snr = 0;

    // bank 6 0xfe [0] reg_fdp_freeze
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0xfe, &reg_frz);
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe, reg_frz|0x01);

    // bank 6 0xff [0] reg_fdp_load
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0xff, &reg);

    // bank 6 0x4a [26:0] reg_snr_accu <27,1>
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x4d, &reg);
    noise_power = reg & 0x07;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x4c, &reg);
    noise_power = (noise_power << 8)|reg;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x4b, &reg);
    noise_power = (noise_power << 8)|reg;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x4a, &reg);
    noise_power = (noise_power << 8)|reg;

    noise_power = noise_power/2;

    // bank 6 0x26 [5:4] reg_transmission_mode
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x26, &reg);

    // bank 6 0xfe [0] reg_fdp_freeze
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe, reg_frz);

    if ((reg&0x03)==0x00)     //2K
    {
        if (noise_power<1512)
            snr = 0;
        else
            snr = 10*Log10Approx((float)noise_power/1512);
    }
    //else if ((reg&0x03)==0x01)//8K
    else
    {
        if (noise_power<6048)
            snr = 0;
        else
            snr = 10*Log10Approx((float)noise_power/6048);
    }
    /* ignore 4K
    else                       //4K
    {
      if (noise_power<3024)
        snr = 0;
      else
        snr = 10*Log10Approx(noise_power/3024);
    }
    */

    if (status == true)
        return snr;
    else
        return -1;

}

/****************************************************************************
  Subject:    To check if Hierarchy on
  Function:   INTERN_DVBT_Is_HierarchyOn
  Parmeter:
  Return:     BOOLEAN
*****************************************************************************/
BOOLEAN INTERN_DVBT_Is_HierarchyOn( void)
{
    U16 u16_tmp;

    if(INTERN_DVBT_Get_TPS_Info(&u16_tmp) == FALSE)
        return FALSE;
    //printf("u16_tmp........%x %x\n",u16_tmp,u16_tmp&0x38);
    if(u16_tmp&0x38)
    {
        return TRUE;
    }
    return FALSE;
}
FUNCTION_RESULT INTERN_DVBT_GetSignalStrength(U16 *strength)
{
    U8                status = true;
    U8                reg_tmp = 0;
    U8                reg_tmp2 = 0;
    U8                reg_frz = 0;
    U8                rf_agc_val = 0;
    U8                if_agc_val = 0;
    U8                i = 0;
    U8                ssi_tbl_len = 0;
    U8                err_tbl_len = 0;
    U16               if_agc_err = 0;
    U16               tps_info = 0;
    float             ch_power_db = 0;
    float                   ch_power_rf=0;
    float                   ch_power_if=0;
//    float                 ch_power_ref=0;
//    float             ch_power_rel;
    S_INTERN_DVBT_IFAGC_SSI        *ifagc_ssi;
    S_INTERN_DVBT_IFAGC_ERR        *ifagc_err;

    // if (INTERN_DVBT_Lock(COFDM_TPS_LOCK))
        //if (INTERN_DVBT_Lock(COFDM_AGC_LOCK))
        /* Actually, it's more reasonable, that signal level depended on cable input power level
         * thougth the signal isn't dvb-t signal.
         */
    {
        status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x13, &reg_tmp);

        DBG_GET_SIGNAL(printf("AGC_REF = %d\n", (U16)reg_tmp));

        if (reg_tmp > 200)
        {
            ifagc_ssi = MSTAR_IfagcSsi_HiRef_INTERN_DVBT;
            ssi_tbl_len = sizeof(MSTAR_IfagcSsi_HiRef_INTERN_DVBT)/sizeof(S_INTERN_DVBT_IFAGC_SSI);
            ifagc_err = MSTAR_IfagcErr_HiRef_INTERN_DVBT;
            err_tbl_len = sizeof(MSTAR_IfagcErr_HiRef_INTERN_DVBT)/sizeof(S_INTERN_DVBT_IFAGC_ERR);
        }
        else
        {
            ifagc_ssi = MSTAR_IfagcSsi_LoRef_INTERN_DVBT;
            ssi_tbl_len = sizeof(MSTAR_IfagcSsi_LoRef_INTERN_DVBT)/sizeof(S_INTERN_DVBT_IFAGC_SSI);
            ifagc_err = MSTAR_IfagcErr_LoRef_INTERN_DVBT;
            err_tbl_len = sizeof(MSTAR_IfagcErr_LoRef_INTERN_DVBT)/sizeof(S_INTERN_DVBT_IFAGC_ERR);
        }

        ///////// RF/IF-AGC Gain Out /////////////
#if (INTERN_DVBT_USE_SAR_3_ENABLE == 1)
                // msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_4, &rf_agc_val);
                msKeypad_Get_ADC_Channel(3, &rf_agc_val);
                // printf(">>SAR_4, 0x%x\n",rf_agc_val);
#else
        rf_agc_val = 0x1D; // max value
#endif
        // select IF output value to read. assign 0x03 0x22,
        status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x22, &reg_tmp);
        status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x22, (reg_tmp&0xf0)|0x03);
        // use only high byte value

        status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x25, &reg_tmp);
        if_agc_val = reg_tmp;

        DBG_GET_SIGNAL(printf("SSI_RFAGC (SAR-4) = 0x%x\n", rf_agc_val));
        DBG_GET_SIGNAL(printf("SSI_IFAGC_H = 0x%x\n", if_agc_val));


        for(i = 0; i < sizeof(MSTAR_RfagcSsi_INTERN_DVBT)/sizeof(S_INTERN_DVBT_RFAGC_SSI); i++)
        {
            if (rf_agc_val <= MSTAR_RfagcSsi_INTERN_DVBT[i].sar3_val)
            {
                ch_power_rf = MSTAR_RfagcSsi_INTERN_DVBT[i].power_db;
                break;
            }
        }

        for(i = 0; i < ssi_tbl_len; i++)
        {
            if (if_agc_val <= ifagc_ssi[i].agc_val)
            {
                ch_power_if = ifagc_ssi[i].power_db;
                break;
            }
        }

        DBG_GET_SIGNAL(printf("ch_power_rf = %d\n", (S16)ch_power_rf*100));
        DBG_GET_SIGNAL(printf("ch_power_if = %d\n", (S16)ch_power_if*100));

        // ch_power_db = (ch_power_rf > ch_power_if)? ch_power_rf : ch_power_if;

                if(ch_power_rf > (TAKEOVERPOINT + TAKEOVERRANGE))
                {
                    ch_power_db = ch_power_rf;
DBG_GET_SIGNAL(printf("Mode 1\n"));
                }
                else if(ch_power_if < (TAKEOVERPOINT - TAKEOVERRANGE))
                {
                    ch_power_db = ch_power_if;
DBG_GET_SIGNAL(printf("Mode 2\n"));
                }
                else
                {
                    ch_power_db = (ch_power_if + ch_power_rf)/2;
DBG_GET_SIGNAL(printf("Mode 3\n"));
                }

                // ch_power_db = (ch_power_rf > ch_power_if)? ch_power_if : ch_power_rf;

        ///////// IF-AGC Error for Add. Attnuation /////////////
                if(if_agc_val == 0xff)
                {

            status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x22, &reg_tmp);
            status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x22, (reg_tmp&0xf0));

                    // bank 5 0x04 [15] reg_tdp_lat
                    status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x05, &reg_frz);
                    status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz|0x80);

                    // bank 5 0x2c [9:0] reg_agc_error
                    status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x25, &reg_tmp);
                    // if_agc_err = reg_tmp & 0x03;
                    status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x24, &reg_tmp2);
                    // if_agc_err = (if_agc_err << 6)|(reg_tmp >> 2);


                    if(reg_tmp&0x2)
                    {
                        if_agc_err = ((((~reg_tmp)&0x03)<<8)|((~reg_tmp2)&0xff)) + 1;
                    }
                    else
                    {
                        if_agc_err = reg_tmp<<8|reg_tmp2;
                    }

                    // release latch
                    status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz);

                    for(i = 0; i < err_tbl_len; i++)
                    {
                            if ( if_agc_err <= ifagc_err[i].agc_err )        // signed char comparison
                            {
                                    ch_power_db += ifagc_err[i].attn_db;
                                    break;
                            }
                    }
                    DBG_GET_SIGNAL(printf("if_agc_err = 0x%x\n", if_agc_err));
                }

                ch_power_db += SIGNAL_LEVEL_OFFSET;
    }

        DBG_GET_SIGNAL(printf(">>> SSI_CH_PWR(dB) beginning = %d\n", (S16)(ch_power_db*100)));

    if(INTERN_DVBT_Get_TPS_Parameter_Const(&tps_info) == TRUE)
    {
        if((tps_info&0x3)==BIT0)//16QAM
        {
                    if(ch_power_db <= -90.0)
                    {*strength = 0;}
            else if(ch_power_db <= -85.0)
            {*strength = 20;}
            else if (ch_power_db <= -80.0)
            {*strength = 20.0 + (ch_power_db+85.0)*20.0/5;}
            else if (ch_power_db <= -75.0)
            {*strength = 40 + (ch_power_db+80.0)*30.0/5;}
            else if (ch_power_db <= -70.0)
            {*strength = 70 + (ch_power_db+75.0)*10.0/5;}
            else if (ch_power_db <= -60.0)
            {*strength = 80 + (ch_power_db+70.0)*10.0/10;}
            else if (ch_power_db <= -50.0)
            {*strength = 90 + (ch_power_db+60.0)*10.0/10;}
            else
            {*strength = 100;}
        }
        else //64QAM or other QAM
        {
                    if(ch_power_db <= -90.0)
                    {*strength = 0;}
            else if(ch_power_db <= -85.0)
            {*strength = 10;}
            else if (ch_power_db <= -80.0)
            {*strength = 10 + (ch_power_db+85.0)*20.0/5;}
            else if (ch_power_db <= -75.0)
            {*strength = 30 + (ch_power_db+80.0)*30.0/5;}
            else if (ch_power_db <= -70.0)
            {*strength = 60 + (ch_power_db+75.0)*10.0/5;}
            else if (ch_power_db <= -60.0)
            {*strength = 70 + (ch_power_db+70.0)*20.0/10;}
            else if (ch_power_db <= -50.0)
            {*strength = 90 + (ch_power_db+60.0)*10.0/10;}
            else
            {*strength = 100;}
        }
    }
        else
        {
            if(ch_power_db <= -90.0)
            {*strength = 0;}
            else if(ch_power_db <= -85.0)
            {*strength = 10;}
            else if (ch_power_db <= -80.0)
            {*strength = 10 + (ch_power_db+85.0)*20.0/5;}
            else if (ch_power_db <= -75.0)
            {*strength = 30 + (ch_power_db+80.0)*30.0/5;}
            else if (ch_power_db <= -70.0)
            {*strength = 60 + (ch_power_db+75.0)*10.0/5;}
            else if (ch_power_db <= -60.0)
            {*strength = 70 + (ch_power_db+70.0)*20.0/10;}
            else if (ch_power_db <= -50.0)
            {*strength = 90 + (ch_power_db+60.0)*10.0/10;}
            else
            {*strength = 100;}

        }

        DBG_GET_SIGNAL(printf(">>> SSI_CH_PWR(dB) = %d , Score = %d<<<\n", (S16)(ch_power_db*100), *strength));
    DBG_GET_SIGNAL(printf(">>> SSI = %d <<<\n", (int)*strength));

/*
        DBG_GET_SIGNAL(printf(">>> SSI_CH_PWR(dB) = %f , Score = %d<<<\n", ch_power_db, *strength));
    DBG_GET_SIGNAL(printf(">>> SSI = %d <<<\n", (int)*strength));
*/

    return status==TRUE?E_RESULT_SUCCESS:E_RESULT_FAILURE;
}

/****************************************************************************
  Subject:    To get the DVT Signal quility
  Function:   INTERN_DVBT_GetSignalQuality
  Parmeter:  Quility
  Return:      E_RESULT_SUCCESS
                   E_RESULT_FAILURE
  Remark:    Here we have 4 level range
                  <1>.First Range => Quility =100  (You can define it by INTERN_DVBT_SIGNAL_BASE_100)
                  <2>.2th Range => 60 < Quality < 100 (You can define it by INTERN_DVBT_SIGNAL_BASE_60)
                  <3>.3th Range => 10 < Quality < 60  (You can define it by INTERN_DVBT_SIGNAL_BASE_10)
                  <4>.4th Range => Quality <10
*****************************************************************************/
//For Nordig Boxer
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)
FUNCTION_RESULT INTERN_DVBT_GetSignalQuality(U16 *quality)
{
	float   BitErr_float, temp_BitErr_avg_NONzero, BitErr_avg_NONzero=0;
    U8      status = true;
    U8      tps_cnstl = 0, tps_cr = 0;
    U8      reg=0, reg_frz=0;
    U8      read_count, BitErr_count_NONzero=0;
    U16     u16_tmp, BitErrPeriod, PktErr;
    U32     BitErr, BitErr_avg=0, BitErr_sum =0;
    U32     noise_power_SNR,noise_power_SNR_sum;

    if (TRUE == INTERN_DVBT_Lock(COFDM_PSYNC_LOCK) )
    {
        noise_power_SNR_sum = 0;
        for(read_count=0;read_count<20;read_count++)
        {
            // bank 1f 0x03 [1:0] reg_bit_err_num_freeze
            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x03, &reg_frz);
            status &= INTERN_DVBT_WriteReg(BACKEND_REG_BASE+0x03, reg_frz|0x03);

            // bank 1f 0x46 [7:0] reg_bit_err_sblprd_7_0
            //             0x47 [15:8] reg_bit_err_sblprd_15_8
            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x47, &reg);
            BitErrPeriod = reg;

            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x46, &reg);
            BitErrPeriod = (BitErrPeriod << 8)|reg;

            // bank 1f 0x6a [7:0] reg_bit_err_num_7_0
            //             0x6b [15:8] reg_bit_err_num_15_8
            // bank 1f 0x6c [7:0] reg_bit_err_num_23_16
            //             0x6d [15:8] reg_bit_err_num_31_24
            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x6d, &reg);
            BitErr = reg;

            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x6c, &reg);
            BitErr = (BitErr << 8)|reg;

            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x6b, &reg);
            BitErr = (BitErr << 8)|reg;

            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x6a, &reg);
            BitErr = (BitErr << 8)|reg;

            // bank 1f 0x66 [7:0] reg_uncrt_pkt_num_7_0
            //             0x67 [15:8] reg_uncrt_pkt_num_15_8
            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x67, &reg);
            PktErr = reg;

            status &= INTERN_DVBT_ReadReg(BACKEND_REG_BASE+0x66, &reg);
            PktErr = (PktErr << 8)|reg;

            // bank 1f 0x03 [1:0] reg_bit_err_num_freeze
            reg_frz=reg_frz&(~0x03);
            status &= INTERN_DVBT_WriteReg(BACKEND_REG_BASE+0x03, reg_frz);

            // bank 6 0xfe [0] reg_fdp_freeze
            status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0xfe, &reg_frz);
            status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe, reg_frz|0x01);

            // bank 6 0xff [0] reg_fdp_load
            status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xff, 0x01);

            // bank 6 0x4a [26:0] reg_snr_accu <27,1>
            status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x4d, &reg);
            noise_power_SNR = reg & 0x07;

            status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x4c, &reg);
            noise_power_SNR = (noise_power_SNR << 8)|reg;

            status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x4b, &reg);
            noise_power_SNR = (noise_power_SNR << 8)|reg;

            status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x4a, &reg);
            noise_power_SNR = (noise_power_SNR << 8)|reg;

            noise_power_SNR = noise_power_SNR/2;

            noise_power_SNR_sum += noise_power_SNR;
            BitErr_avg += BitErr;

            //       printf("#######[BitErr= %ld ]\n\n ", BitErr);  /////*****
            // printf("//noise_power_SNR = %ld\n\n", (MS_U32)(noise_power_SNR));
            if (BitErr > 0 )
            {
                BitErr_sum += BitErr;
                BitErr_count_NONzero ++;
            }
            MsOS_DelayTask(10);
        }

        if (BitErrPeriod == 0 )    //protect 0
            BitErrPeriod = 1;

        if(BitErr_avg>0)
        {
            BitErr_avg_NONzero = (float)(BitErr_avg/BitErr_count_NONzero);
        //    printf("\\\\\\\\\\\\\\\\\\\\\\BitErr_total_NONzero = %ld\n", (BitErr_avg));
        //    printf("\\\\\\\\\\\\\\\\\\\\\\count_NONzero = %ld\n", (BitErr_count_NONzero));
        }

        if (BitErr_avg_NONzero <=0 )
            BitErr_float = 0.5f / ((float)BitErrPeriod*128*188*8);
        else
            BitErr_float = (float)BitErr_avg_NONzero / ((float)BitErrPeriod*128*188*8);

        temp_BitErr_avg_NONzero = (log10f(BitErr_float));


        //get SNR for SQI
        noise_power_SNR = noise_power_SNR_sum/20;
//     printf("//noise_power_SNR = %ld\n\n", (MS_U32)(noise_power_SNR));

        ///////// Get Constellation and Code Rate to determine Ref. C/N //////////
        ///////// (refer to Teracom min. spec 2.0 4.1.1.7) /////
        tps_cnstl = 0xff;
        tps_cr = 0xff;
        if(INTERN_DVBT_Get_TPS_Info(&u16_tmp) == TRUE)
        {
            tps_cnstl = (U8)u16_tmp&0x07;
            tps_cr = (U8)(u16_tmp>>9)&0x07;
        }

        if((tps_cnstl == _64QAM) && (tps_cr == _CR3Y4))
        {
            if (temp_BitErr_avg_NONzero <= ( - 5.0))
            // PostVit BER < 2e-4
            {
                if(noise_power_SNR<=671000&&noise_power_SNR>=600000)
                {
                     //-19.5dB ~ -20.0dB  //Q:50 ~ 60
                    *quality = (50+(noise_power_SNR-600000)*10/(671000-600000));
                }
                else if(noise_power_SNR<=731000)
                {
                     //-20.0dB ~ -20.5dB  //Q:60 ~ 70
                    *quality = (60+(noise_power_SNR-671000)*10/(731000-671000));
                }
                else if(noise_power_SNR<=804000)
                {
                     //-20.5dB ~ -21.0dB  //Q:70 ~ 80
                    *quality = (70+(noise_power_SNR-731000)*10/(804000-731000));
                }
                else if(noise_power_SNR<=860000)
                {
                     //-21.0dB ~ -21.5dB  //Q:80 ~ 85
                    *quality = (80+(noise_power_SNR-804000)*5/(860000-804000));
                }
                else if(noise_power_SNR<=980000)
                {
                     //-21.5dB ~ -22.0dB  //Q:85 ~ 90
                    *quality = (85+(noise_power_SNR-860000)*5/(980000-860000));
                }
                else if(noise_power_SNR<=1180000)
                {
                     //-22.0dB ~ -23.0dB  //Q:90 ~ 100
                    *quality = (90+(noise_power_SNR-980000)*10/(1170000-980000));
                }
                else if(noise_power_SNR>1180000)
                {
                    *quality = 100;
                }
                else
                {
                    *quality = 50;
                }
            }
            else if (temp_BitErr_avg_NONzero <= ( - 4.6))
            // PostVit BER < 2e-4
            {
                printf("<<quality = 50>\n");
                //Q:40 ~ 50
                *quality = (40+((( - 4.6) - temp_BitErr_avg_NONzero) / (( - 4.6) - ( - 5.0))*(50-40)));
            }
            else if (temp_BitErr_avg_NONzero <= ( - 4.1))
            // PostVit BER < 2e-4
            {
                printf("<<quality = 40>\n");
                //Q:30 ~ 40
                *quality = (30+((( - 4.1) - temp_BitErr_avg_NONzero) / (( - 4.1) - ( - 4.6))*(40-30)));
            }
            else if (temp_BitErr_avg_NONzero < ( - 3.5))
            // PostVit BER < 2e-2
            {
                printf("<<quality = 30>\n");
                //Q:20 ~ 30
                *quality = (20+((( - 3.5) - temp_BitErr_avg_NONzero) / (( - 3.5) - ( - 4.1))*(30-20)));
            }
            else if (temp_BitErr_avg_NONzero <= ( - 3.0))
            // PostVit BER < 2e-2
            {
                printf("<<quality = 20>\n");
                //Q:10 ~ 20
                *quality = (10+((( - 3.0) - temp_BitErr_avg_NONzero) / (( - 3.0) - ( - 3.5))*(20-10)));
            }
            else if (temp_BitErr_avg_NONzero <= ( - 1.9))
            // PostVit BER
            {
                printf("<<quality = 0>\n");
                *quality = (0+((( - 1.9) - temp_BitErr_avg_NONzero) / (( - 1.9) - ( - 3.0))*(20-10)));
            }
            else
            {
                printf("<<quality = 0>\n");
                *quality = 0;
            }
        }
        else//_CR2Y3
        {
            if (temp_BitErr_avg_NONzero <= ( - 5.0))
            // PostVit BER < 2e-4
            {
                if(noise_power_SNR<=514000&&noise_power_SNR>=460000)
                {
                    //-18.5dB ~ -19.0dB  //Q:60 ~ 70
                    *quality = (60+(noise_power_SNR-460000)*10/(514000-460000));
                }
                else if(noise_power_SNR<=553000)
                {
                     //-19.0dB ~ -19.5dB  //Q:70 ~ 80
                    *quality = (70+(noise_power_SNR-514000)*10/(553000-514000));
                }
                else if(noise_power_SNR<=604000)
                {
                     //-19.5dB ~ -20.0dB  //Q:80 ~ 90
                    *quality = (80+(noise_power_SNR-553000)*10/(604000-553000));
                }
                else if(noise_power_SNR<=880000)
                {
                     //-20.0dB ~ -22.0dB  //Q:90 ~ 100
                    *quality = (90+(noise_power_SNR-604000)*10/(880000-604000));
                }
                else if(noise_power_SNR>880000)
                {
                    *quality = 100;
                }
                else
                {
                    *quality = 60;
                }
            }
            else if (temp_BitErr_avg_NONzero <= ( - 4.6))
            // PostVit BER < 2e-4
            {
                printf("<<quality = 50>\n");
                *quality = (50+((( - 4.6) - temp_BitErr_avg_NONzero) / (( - 4.6) - ( - 5.0))*(60-50)));
            }
            else if (temp_BitErr_avg_NONzero <= ( - 4.1))
            // PostVit BER < 2e-4
            {
                printf("<<quality = 40>\n");
                *quality = (40+((( - 4.1) - temp_BitErr_avg_NONzero) / (( - 4.1) - ( - 4.6))*(50-40)));
            }
            else if (temp_BitErr_avg_NONzero < ( - 3.5))
            // PostVit BER < 2e-2
            {
                printf("<<quality = 30>\n");
                *quality = (30+((( - 3.5) - temp_BitErr_avg_NONzero) / (( - 3.5) - ( - 4.1))*(40-30)));
            }
            else if (temp_BitErr_avg_NONzero <= ( - 3.0))
            // PostVit BER < 2e-2
            {
                printf("<<quality = 20>\n");
                *quality = (20+((( - 3.0) - temp_BitErr_avg_NONzero) / (( - 3.0) - ( - 3.5))*(30-20)));
            }
            else if (temp_BitErr_avg_NONzero < ( - 2.2))
            // PostVit BER
            {
                printf("<<quality = 10>\n");
                *quality = (10+((( - 2.2) - temp_BitErr_avg_NONzero) / (( - 2.2) - ( - 3.0))*(20-10)));
            }
            else if (temp_BitErr_avg_NONzero <= ( - 1.9))
            // PostVit BER
            {
                printf("<<quality = 0>\n");
                *quality = (0+((( - 1.9) - temp_BitErr_avg_NONzero) / (( - 1.9) - ( - 2.2))*(20-10)));
            }
            else
            {
                printf("<<quality = 0>\n");
                *quality = 0;
            }
        }
    }
    else
    {
        *quality = 0;
    }
    DBG_GET_SIGNAL(printf("@@@@@SNR = %ld, QAM = %ld, code Rate = %ld\n\n", (MS_U32)(cn_rec), (MS_U32)(tps_cnstl), (MS_U32)(tps_cr)));
    DBG_GET_SIGNAL(printf("Signal Quility = %d\n", *quality));

// printf("----------------->>Avg. BER = %ld, BitErr_float = %ld\n", (long int)(temp_BitErr_avg_NONzero*1000), (long int)(BitErr_float*100000000));
// printf("----------------->>Accum SNR = %ld\n", (long int)noise_power_SNR);
// printf("SQI = %d\n", (int)*quality);
    return status==TRUE?E_RESULT_SUCCESS:E_RESULT_FAILURE;
}
#else
FUNCTION_RESULT INTERN_DVBT_GetSignalQuality(U16 *quality)
{
    static  U16  s_quality = 50;
    float                ber_sqi;
    float                fber;
    float                cn_rec = 0;
    float                cn_nordig_p1 = 0;
    float                cn_rel = 0;

    U8                   status = true;
    U8                   tps_cnstl = 0, tps_cr = 0, i = 0;
    U16              signal_strength = 0;
    U16              u16_tmp;

    if (TRUE == INTERN_DVBT_Lock(COFDM_PSYNC_LOCK) )
    {
        ///////// Get Pre-RS (Post-Viterbi) BER to determine BER_SQI //////////
        if (INTERN_DVBT_GetPostViterbiBer(&fber) == FALSE)
        {
            DBG_INTERN_DVBT(printf("GetPostViterbiBer Fail!\n"));
            return E_RESULT_FAILURE;
        }


        if (fber > 1.0E-2)
            ber_sqi = 0.0;
        else if (fber > 1.0E-7)
            ber_sqi = (Log10Approx(1/fber)-LOG10_OFFSET)*20.0 - 40.0;
        else
            ber_sqi = 100.0;

        cn_rec = INTERN_DVBT_GetSNR();

        if (cn_rec == -1)        //get SNR return fail
            status = false;

        ///////// Get Constellation and Code Rate to determine Ref. C/N //////////
        ///////// (refer to Teracom min. spec 2.0 4.1.1.7) /////
        tps_cnstl = 0xff;
        tps_cr = 0xff;
        if(INTERN_DVBT_Get_TPS_Info(&u16_tmp) == TRUE)
        {
            tps_cnstl = (U8)u16_tmp&0x07;
            tps_cr = (U8)(u16_tmp>>9)&0x07;
        }
        for(i = 0; i < sizeof(SqiCnNordigP1_INTERN_DVBT)/sizeof(S_SQI_CN_NORDIGP1_INTERN_DVBT); i++)
        {
            if ( (tps_cnstl == SqiCnNordigP1_INTERN_DVBT[i].constel)
                && (tps_cr == SqiCnNordigP1_INTERN_DVBT[i].code_rate) )
            {
                cn_nordig_p1 = SqiCnNordigP1_INTERN_DVBT[i].cn_ref;
                break;
            }
        }

        cn_rel = cn_rec - cn_nordig_p1;

        if (cn_rec < (cn_nordig_p1 - 7.0))
        { //*quality = 0;
            *quality = (U16)ber_sqi;
        }
        else if (cn_rec < (cn_nordig_p1 + 3.0))
            *quality = (U16)(ber_sqi*((cn_rel - 3.0)/10.0 + 1.0));
        else
            *quality = (U16)ber_sqi;

        /* Low signal level, but good quality, it seems unreasonable.
         */

        if(INTERN_DVBT_GetSignalStrength(&signal_strength)==TRUE)
        {

            if(signal_strength <= 30
                && *quality>= 60)
            {
                *quality -= 40;
            }
            else if(signal_strength <= 40
                && tps_cnstl == _16QAM
                && *quality>= 80)
            {
                *quality -= 60;
            }
            else if(signal_strength <= 60
                && *quality>= 80)
            {
                *quality -= 40;
            }
            else if(signal_strength <= 70
                && tps_cnstl == _16QAM
                && *quality>= 80)
            {
                *quality -= 40;
            }

        }

        /* To average quality, avoid jumping too much.
         */
        s_quality = ((*quality) + s_quality)*0.5;
        *quality = s_quality;

    }
    else
    {
        s_quality = 50;
        *quality = 0;
    }

    DBG_GET_SIGNAL(printf("SNR = %f, QAM = %d, code Rate = %d\n", cn_rec, tps_cnstl, tps_cr));
    DBG_GET_SIGNAL(printf("BER = %8.3e\n", fber));
    DBG_GET_SIGNAL(printf("Signal Quility = %d\n", *quality));

     return status==TRUE?E_RESULT_SUCCESS:E_RESULT_FAILURE;

}
#endif

/****************************************************************************
  Subject:    To get the DVBT Carrier Freq Offset
  Function:   INTERN_DVBT_Get_FreqOffset
  Parmeter:   Frequency offset (in KHz), bandwidth
  Return:     E_RESULT_SUCCESS
              E_RESULT_FAILURE
  Remark:
*****************************************************************************/
FUNCTION_RESULT INTERN_DVBT_Get_FreqOffset(float *pFreqOff, U8 u8BW)
{
    float         N = 0;
    float         FreqB = 0;
    float         FreqCfoTd = 0;
    float         FreqCfoFd = 0;
    float         FreqIcfo = 0;
    U32           RegCfoTd = 0;
    U32           RegCfoFd = 0;
    U32           RegIcfo = 0;
    U8            reg_frz = 0;
    U8            reg = 0;
    U8            status = 0;

    FreqB = (float)u8BW * 8 / 7;

    status = INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x05, &reg_frz);

    status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz|0x80);

    status &= INTERN_DVBT_ReadReg(0x24c6+2, &reg);
    RegCfoTd = reg;

    status &= INTERN_DVBT_ReadReg(0x24c6+1, &reg);
    RegCfoTd = (RegCfoTd << 8)|reg;

    status &= INTERN_DVBT_ReadReg(0x24c6, &reg);
    RegCfoTd = (RegCfoTd << 8)|reg;

    FreqCfoTd = (float)RegCfoTd;

    if (RegCfoTd & 0x800000)
        FreqCfoTd = FreqCfoTd - (float)0x1000000;

    FreqCfoTd = FreqCfoTd * FreqB * 0.00011642;

    status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz&(~0x80));

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0xfe, &reg_frz);
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe, reg_frz|0x01);

    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xff, 0x01);

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x33, &reg);
    RegCfoFd = reg;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x32, &reg);
    RegCfoFd = (RegCfoFd << 8)|reg;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x31, &reg);
    RegCfoFd = (RegCfoFd << 8)|reg;

    FreqCfoFd = (float)RegCfoFd;

    if (RegCfoFd & 0x800000)
        FreqCfoFd = FreqCfoFd - (float)0x1000000;

    FreqCfoFd = FreqCfoFd * FreqB * 0.00011642;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x19, &reg);
    RegIcfo = reg & 0x07;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x18, &reg);
    RegIcfo = (RegIcfo << 8)|reg;

    FreqIcfo = (float)RegIcfo;

    if (RegIcfo & 0x400)
        FreqIcfo = FreqIcfo - (float)0x800;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x26, &reg);
    reg = reg & 0x30;

    switch (reg)
    {
        case 0x00:  N = 2048;  break;
        case 0x20:  N = 4096;  break;
        case 0x10:
        default:    N = 8192;  break;
    }

    FreqIcfo = FreqIcfo * FreqB / N * 1000;         //unit: kHz
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe, reg_frz&(~0x01));
    //status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe+1, 0x01);
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xff, 0x01);
    *pFreqOff = FreqIcfo + (FreqCfoFd + FreqCfoTd)/1000;

    // DBG_GET_SIGNAL(printf("FCFO = %f\n", FreqCfoFd));
    // DBG_GET_SIGNAL(printf("TCFO = %f\n", FreqCfoTd));
    // DBG_GET_SIGNAL(printf("ICFO = %f\n", FreqIcfo));
    DBG_GET_SIGNAL(printf("CFOE = %f\n", *pFreqOff));

    if (status == TRUE)
        return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
}

void INTERN_DVBT_Power_ON_OFF(U8 bPowerOn)
{

    bPowerOn = bPowerOn;
}

BOOLEAN INTERN_DVBT_Power_Save(void)
{

    return TRUE;
}

/************************************************************************************************
  Subject:    TS1 output control
  Function:   INTERN_DVBT_PAD_TS1_Enable
  Parmeter:   flag : TRUE For Turn on TS1, FALSE For Turn off TS1
  Return:     void
  Remark:
*************************************************************************************************/
void INTERN_DVBT_PAD_TS1_Enable(BOOLEAN flag)
{
    DBG_INTERN_DVBT(printf(" @INTERN_DVBT_TS1_Enable... \n"));
    if(flag) // PAD_TS1 Enable TS CLK PAD
    {
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L))
        INTERN_DVBT_Write_VD_DMD_Byte(0x101EA5, INTERN_DVBT_Read_MBX_Byte(0x101EA5)|0x10);   //For T3 or T9
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) //T4
        INTERN_DVBT_Write_VD_DMD_Byte(0x101EAF, INTERN_DVBT_Read_MBX_Byte(0x101EAF)|0x18);   //For T4
#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2)
        INTERN_DVBT_Write_VD_DMD_Byte(0x101EAF, INTERN_DVBT_Read_MBX_Byte(0x101EAF)|0x11);   //For T8
#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
        INTERN_DVBT_Write_VD_DMD_Byte(0x101EA3, ((INTERN_DVBT_Read_MBX_Byte(0x101EA3) & 0xC3) | 0x24));
#endif

    }
    else // PAD_TS1 Disable TS CLK PAD
    {
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L)) // T3 or T9
        INTERN_DVBT_Write_VD_DMD_Byte(0x101EA5, INTERN_DVBT_Read_MBX_Byte(0x101EA5)&0xEF);   //For T3 or T9
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) //T4
        INTERN_DVBT_Write_VD_DMD_Byte(0x101EAF, INTERN_DVBT_Read_MBX_Byte(0x101EAF)&0xE3);   //For T4
#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2)
        INTERN_DVBT_Write_VD_DMD_Byte(0x101EAF, INTERN_DVBT_Read_MBX_Byte(0x101EAF)&0xC0);   //For T8
#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
        INTERN_DVBT_Write_VD_DMD_Byte(0x101EA3, INTERN_DVBT_Read_MBX_Byte(0x101EA3) & 0xC3);
#endif
    }
}

/****************************************************************************
  Subject:    To get the Cell ID
  Function:   INTERN_DVBT_Get_CELL_ID
  Parmeter:   point to return parameter cell_id

  Return:     TRUE
              FALSE
  Remark:
*****************************************************************************/
BOOLEAN INTERN_DVBT_Get_CELL_ID(U16 *cell_id)
{
  U8 status = true;
  U8 value1 = 0;
  U8 value2 = 0;

  status &= INTERN_DVBT_ReadReg(FDP_REG_BASE+0x2A, &value1); //TPS Cell ID [15:8]
  status &= INTERN_DVBT_ReadReg(FDP_REG_BASE+0x2B, &value2); //TPS Cell ID [7:0]

  *cell_id = ((U16)value1<<8)|value2;
    return status;
}

#if (INTERN_DVBT_INTERNAL_DEBUG)
BOOLEAN INTERN_DVBT_GetChannelLength(U16 *ch_length)
{
    U8 status = true;
    U8 tmp = 0;
    U16 tmp_len = 0;
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x71,&tmp);
    tmp_len = tmp;
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x70,&tmp);
    tmp_len = (tmp_len<<8)|tmp;
    *ch_length = tmp_len;
    return status;
}

BOOLEAN INTERN_DVBT_Get_SW_ChannelLength(U16 *ch_length)
{
    U8 status = true;
    U8 tmp = 0;
    U16 tmp_len = 0;
    status &= INTERN_DVBT_ReadReg(TOP_REG_BASE + 0x94,&tmp);
    tmp_len = tmp;
    status &= INTERN_DVBT_ReadReg(TOP_REG_BASE + 0x93,&tmp);
    tmp_len = (tmp_len<<8)|tmp;
    *ch_length = tmp_len;
    return status;
}

BOOLEAN INTERN_DVBT_Get_offsetSA_PeakNum(U16 *offsetSA, U8 *peakNum)
{
    U8 status = true;
    U8 tmp = 0;
    U16 tmp_len = 0;
    status &= INTERN_DVBT_ReadReg(TOP_REG_BASE + 0x92,&tmp);
    tmp_len = tmp;
    status &= INTERN_DVBT_ReadReg(TOP_REG_BASE + 0x91,&tmp);
    tmp_len = (tmp_len<<8)|tmp;
    *offsetSA = tmp_len&0x0fff;
    *peakNum = tmp_len&0xf000>>12;
    return status;
}

/****************************************************************************
  Subject:    To get USE_VAR_1 and USE_VAR_2
  Function:   INTERN_DVBT_GetUSE_VAR
  Parmeter:   void
  Return:     E_RESULT_SUCCESS
              E_RESULT_FAILURE
  Remark:
  ==============parameters of bit defined in USE_VAR_1==============
  USE_VAR_1[0:0] -> ZIF  => 0:IF
                                                    1:ZIF
  USE_VAR_1[1:1] -> Slave => Defalut:0
  USE_VAR_1[3:2] -> TD_Coeff_Set => 0:Static-Avg
                                                                 1:Mobile
                                                                 2:Initial-Linear interpolation
  USE_VAR_1[5:4] -> Reg_SNR_Select => 0:Mode 0
                                                                        1:Mode 1
                                                                        2:Mode 2
  USE_VAR_1[7:6] -> Flag_CI => 0:No Interference
                                               1:CCI
                                               2:In band ACI
                                               3:N+1 interference
    ==============parameters of bit defined in USE_VAR_2==============
  USE_VAR_2[1:0] -> Status_reg  => [0]:IQ_Swap
                                                               [1]:FSA_Mode
  USE_VAR_2[3:3] -> Ripple => 0:ripple small
                                                        1:ripple large
  USE_VAR_2[4:4] -> ACI => 0:No ACI
                                                 1:ACI detection
  USE_VAR_2[6:5] -> Bandwidth => 0:5M
                                                             1:6M
                                                             2:7M
                                                             3:8M
  USE_VAR_2[7:7] -> Large_Half_Search_Range => 0:small Range
                                                                           1:large Range
*****************************************************************************/
BOOLEAN INTERN_DVBT_GetUSE_VAR(void)
{
    U8 status = true;
    U8 tmp = 0;
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x56,&tmp);
    printf(">>>USE_VAR_1 = 0x%x\n",tmp);
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x57,&tmp);
    printf(">>>USE_VAR_2 = 0x%x\n",tmp);
    return status;
}

BOOLEAN INTERN_DVBT_GetDigACI(U8 *ret_status)
{
    U8 status = true;
    U8 tmp = 0;
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x56,&tmp);

    if(tmp&BIT3)
    {
        *ret_status = 1;
    }
    else
    {
        *ret_status = 0;
    }

    // get flag_CI
    // 0: No interference
    // 1: CCI
    // 2: in-band ACI
    // 3: N+1 ACI
    // flag_ci = (tmp&0xc0)>>6;
    printf(">>>Flag_CI = %d\n",(tmp&0xc0)>>6);

    return status;
}

BOOLEAN INTERN_DVBT_Version(U16 *ver)
{

  U8 status = true;
    U8 tmp;
    U16 u16_INTERN_DVBT_Version;

  status &= INTERN_DVBT_ReadReg(TOP_REG_BASE + 0x71, &tmp);
    u16_INTERN_DVBT_Version = tmp;
    status &= INTERN_DVBT_ReadReg(TOP_REG_BASE + 0x72, &tmp);
    u16_INTERN_DVBT_Version = u16_INTERN_DVBT_Version<<8|tmp;
    *ver = u16_INTERN_DVBT_Version;

    return status;
}

BOOLEAN INTERN_DVBT_GetFD(U8 *fd)
{
    U8 status = true;
    U8 tmp;
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x55, &tmp);
    *fd = tmp;
    return status;
}

/****************************************************************************
  Subject:    To get the DVBT Carrier frequency offset
  Function:   INTERN_DVBT_GetCFO
  Parmeter:   Frequency offset (in KHz)
  Return:     TRUE or FALSE
  Remark:
*****************************************************************************/
BOOLEAN INTERN_DVBT_GetCFO(float *pFreqOff)
{
    float         N, FreqB;
    float         FreqCfoTd, FreqCfoFd, FreqIcfo;
    U32           RegCfoTd, RegCfoFd, RegIcfo;
    U8            reg_frz, reg;
    U8            status;

    FreqB = (float)64 / 7;

    status = INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x05, &reg_frz);

    status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz|0x80);

    status &= INTERN_DVBT_ReadReg(0x24c6+2, &reg);
    RegCfoTd = reg;

    status &= INTERN_DVBT_ReadReg(0x24c6+1, &reg);
    RegCfoTd = (RegCfoTd << 8)|reg;

    status &= INTERN_DVBT_ReadReg(0x24c6, &reg);
    RegCfoTd = (RegCfoTd << 8)|reg;

    FreqCfoTd = (float)RegCfoTd;

    if (RegCfoTd & 0x800000)
        FreqCfoTd = FreqCfoTd - (float)0x1000000;

    FreqCfoTd = FreqCfoTd * FreqB * 0.00011642;

    status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz&(~0x80));

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0xfe, &reg_frz);
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe, reg_frz|0x01);

    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xff, 0x01);

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x33, &reg);
    RegCfoFd = reg;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x32, &reg);
    RegCfoFd = (RegCfoFd << 8)|reg;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x31, &reg);
    RegCfoFd = (RegCfoFd << 8)|reg;

    FreqCfoFd = (float)RegCfoFd;

    if (RegCfoFd & 0x800000)
        FreqCfoFd = FreqCfoFd - (float)0x1000000;

    FreqCfoFd = FreqCfoFd * FreqB * 0.00011642;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x19, &reg);
    RegIcfo = reg & 0x07;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x18, &reg);
    RegIcfo = (RegIcfo << 8)|reg;

    FreqIcfo = (float)RegIcfo;

    if (RegIcfo & 0x400)
        FreqIcfo = FreqIcfo - (float)0x800;

    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x26, &reg);
    reg = reg & 0x30;

    switch (reg)
    {
        case 0x00:  N = 2048;  break;
        case 0x20:  N = 4096;  break;
        case 0x10:
        default:    N = 8192;  break;
    }

    FreqIcfo = FreqIcfo * FreqB / N * 1000;         //unit: kHz
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe, reg_frz&(~0x01));
    //status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xfe+1, 0x01);
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xff, 0x01);
    *pFreqOff = FreqIcfo + (FreqCfoFd + FreqCfoTd)/1000;

    // DBG_GET_SIGNAL(printf("FCFO = %f\n", FreqCfoFd));
    // DBG_GET_SIGNAL(printf("TCFO = %f\n", FreqCfoTd));
    // DBG_GET_SIGNAL(printf("ICFO = %f\n", FreqIcfo));
    DBG_GET_SIGNAL(printf("CFOE = %f\n", *pFreqOff));

    return status;
}

/****************************************************************************
  Subject:    To get the DVBT Sampling frequency offset
  Function:   INTERN_DVBT_GetSFO
  Parmeter:   Sampling frequency offset(in ppm)
  Return:     TRUE or FALSE
  Remark:
*****************************************************************************/
BOOLEAN INTERN_DVBT_GetSFO(float *SFO)
{
        U8            status = true;
    U8            reg, reg_frz;
        U32                     Reg_TD_SFO, Reg_FD_SFO, Reg_FSA_KiOut_2;
        float                   TD_SFO, FD_SFO, FSA_KiOut_2, TOTAL_SFO;
      // 8M(BW) * 8/7 = 9.143
    float FreqB = 9.143, FreqS = 45.00;
        //===================Get TD SFO==========================//
        // bank 5 0x05 [7] reg_tdp_tdp_lat
    status &= INTERN_DVBT_ReadReg(TDP_REG_BASE + 0x05, &reg_frz);
    status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz|0x80);

    // bank 8 0xca [23:0] reg_sfo_time_err
    // bank TDPExt
    status &= INTERN_DVBT_ReadReg(TDE_REG_BASE + 0xCA + 2, &reg);
    Reg_TD_SFO = reg;
    status &= INTERN_DVBT_ReadReg(TDE_REG_BASE + 0xCA + 1, &reg);
    Reg_TD_SFO = (Reg_TD_SFO << 8)|reg;
    status &= INTERN_DVBT_ReadReg(TDE_REG_BASE + 0xCA, &reg);
    Reg_TD_SFO = (Reg_TD_SFO << 8)|reg;

    TD_SFO = (float)Reg_TD_SFO;

    if (Reg_TD_SFO & 0x800000)
        TD_SFO = TD_SFO - (float)0x1000000;

    TD_SFO = TD_SFO * FreqB / FreqS * 0.0018626;

        // bank 5 0x05 [7] reg_tdp_tdp_lat
        status &= INTERN_DVBT_WriteReg(TDP_REG_BASE + 0x05, reg_frz&(~0x80));
        //===================Get FD SFO==========================//
    // bank 6 0xFE [0] reg_fdp_fdp_freeze
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xFE, 0x01);
    // bank 6 0xFF [0] reg_fdp_fdp_load
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xFF, 0x01);

   // bank 6 0x2E [23:0] reg_fdp_fdfoe_Sfo_ki_out
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x2E + 2, &reg);
    Reg_FD_SFO = reg;
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x2E + 1, &reg);
    Reg_FD_SFO = (Reg_FD_SFO << 8)|reg;
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x2E, &reg);
    Reg_FD_SFO = (Reg_FD_SFO << 8)|reg;

    FD_SFO = (float)Reg_FD_SFO;

    if (Reg_FD_SFO & 0x800000)
        FD_SFO = FD_SFO - (float)0x1000000;

    FD_SFO = FD_SFO * FreqB / FreqS * 0.0018626;
        //===================Get FSA_KiOut_2==========================//
    // bank 6 0x8a [23:0] reg_symali_sfo_ki_out
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x8A + 2, &reg);
    Reg_FSA_KiOut_2 = reg;
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x8A + 1, &reg);
    Reg_FSA_KiOut_2 = (Reg_FSA_KiOut_2 << 8)|reg;
    status &= INTERN_DVBT_ReadReg(FDP_REG_BASE + 0x8A, &reg);
    Reg_FSA_KiOut_2 = (Reg_FSA_KiOut_2 << 8)|reg;

    FSA_KiOut_2 = (float)Reg_FSA_KiOut_2;

    if (Reg_FSA_KiOut_2 & 0x800000)
        FSA_KiOut_2 = FSA_KiOut_2 - (float)0x1000000;

    FSA_KiOut_2 = FSA_KiOut_2 * FreqB / FreqS * 0.0037253;

    // bank 6 0xFE [0] reg_fdp_fdp_freeze
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xFE, 0x00);
    // bank 6 0xFF [0] reg_fdp_fdp_load
    status &= INTERN_DVBT_WriteReg(FDP_REG_BASE + 0xFF, 0x01);
    //================compute total SFO================//
        TOTAL_SFO = TD_SFO + FD_SFO + FSA_KiOut_2;
        *SFO = TOTAL_SFO;
      DBG_INTERN_DVBT(printf("DEBUG_TD_SFO = %d\n", (S32)TD_SFO));
      DBG_INTERN_DVBT(printf("DEBUG_FD_SFO = %d\n", (S32)FD_SFO));
      DBG_INTERN_DVBT(printf("DEBUG_FSA_KiOut = %d\n", (S32)FSA_KiOut_2));
      DBG_INTERN_DVBT(printf("DEBUG_TOTAL_SFO = %d\n", (S32)TOTAL_SFO));

    return status;
}
/****************************************************************************
  Subject:    To get the DVBT Packet error number
  Function:   INTERN_DVBT_GetPacketErrorNum
  Parmeter:   Packet error number
  Return:     E_RESULT_SUCCESS
              E_RESULT_FAILURE
  Remark:
*****************************************************************************/
BOOLEAN INTERN_DVBT_GetPacketErrorNum(S16 *pktErrNum)
{
        U8            status = true;
    U8            reg, reg_frz;
    U16           uncrt_pkt_num;

    // bank 7 0x32 [7] reg_bit_err_num_freeze
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x32, &reg_frz);
    status &= INTERN_DVBT_WriteReg(FEC_REG_BASE + 0x32, reg_frz|0x80);

    // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
    //             [15:8] reg_uncrt_pkt_num_15_8
    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x3f, &reg);
    uncrt_pkt_num = reg;

    status &= INTERN_DVBT_ReadReg(FEC_REG_BASE + 0x3e, &reg);
    uncrt_pkt_num = (uncrt_pkt_num << 8)|reg;

    // bank 7 0x32 [7] reg_bit_err_num_freeze
    status &= INTERN_DVBT_WriteReg(FEC_REG_BASE + 0x32, reg_frz&(~0x80));

    if (status == true)
    {
        *pktErrNum = uncrt_pkt_num;
      return E_RESULT_SUCCESS;
    }
    else
    {
        *pktErrNum = -1;
      return E_RESULT_FAILURE;
    }
}

BOOLEAN INTERN_DVBT_ShowLockInfo(void)
{
    U8 status = true;
    U8 tmp;
    status &= INTERN_DVBT_ReadReg(INTERN_DVBT_DBG_S0_ENTRY, &tmp);
    printf(">>INTERN_DVBT_S0_entry: %d\n",tmp);
    status &= INTERN_DVBT_ReadReg(INTERN_DVBT_DBG_S8_TPS_INVALID, &tmp);
    printf(">>INTERN_DVBT_S8_tps_invalid: %d\n",tmp);
    status &= INTERN_DVBT_ReadReg(INTERN_DVBT_DBG_S10_TPS_INVALID, &tmp);
    printf(">>INTERN_DVBT_S10_tps_invalid: %d\n",tmp);
    status &= INTERN_DVBT_ReadReg(INTERN_DVBT_DBG_S10_PSYNC_FAIL, &tmp);
    printf(">>INTERN_DVBT_S10_psync_fail: %d\n",tmp);
    return status;
}

#endif

#endif

