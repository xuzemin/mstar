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

#ifndef MAPP_DIPCLK_MMONITOR_H
  #define MAPP_DIPCLK_MMONITOR_H



#define PWS_PRINT(pclkstr,  x)      \
{                                                       \
    printf(" %s = %x \n",pclkstr,x); \
}
/////////////////////////////////////
// FOR U3
////////////////////////////////////
//U3_CHIPTOP
#define T_NONPM_BASE_ADDR 0x100000  //Non-PM Region
//16-bit address
#define T_REG_CKG_FAST_UART 0x0F05
    #define T_FAST_UART_CLK_DIS BIT4

#define T_REG_CKG_STC0 0x0F11
    #define T_STC0_CLK_DIS BIT8
    #define T_MAD_STC_CLK_DIS BIT12

#define T_REG_CKG_MIPS 0x0F12
    #define T_MIPS_CLK_DIS BIT0
    #define T_MCU_CLK_DIS BIT8
    #define T_AEON_CLK_DIS BIT14

#define T_REG_CKG_MIU 0x0F13
    #define T_MIU_CLK_DIS BIT0
    #define T_DVBC_INNER_GATED_ENABLE BIT12
    #define T_DVBC_INNER2X_GATED_ENABLE BIT13
    #define T_DVBC_EQ_GATED_ENABLE BIT14
    #define T_DVBC_DVBC_EQ8X_GATED_ENABLE BIT15

#define T_REG_CKG_TS0 0x0F14
    #define T_TS0_CLK_DIS BIT0
    #define T_TS1_CLK_DIS BIT4
    #define T_TS2_CLK_DIS BIT8
    #define T_TSOUT_CLK_DIS BIT12

#define T_REG_CKG_TSP 0x0F15
    #define T_TSP_CLK_DIS BIT0
    #define T_TCK_CLK_DIS BIT5
    #define T_NSK_CLK_DIS BIT8

#define T_REG_CKG_MVD 0x0F16
    #define T_MVD_CLK_DIS BIT4
    #define T_MVD2_CLK_DIS BIT8
    #define T_JPD_CLK_DIS BIT12

#define T_REG_CKG_STRLD 0x0F17
    #define T_STRLD_CLK_DIS BIT0
    #define T_RVD_CLK_DIS BIT4
    #define T_GE_CLK_DIS BIT8
    #define T_PCM_CLK_DIS BIT12

#define T_REG_CKG_GOPG0 0x0F18
    #define T_GOPG0_CLK_DIS BIT0
    #define T_GOPG1_CLK_DIS BIT4
    #define T_GOPG2_CLK_DIS BIT8
    #define T_GOPD_CLK_DIS BIT12

#define T_REG_CKG_VD 0x0F19
    #define T_VD_CLK_DIS BIT0
    #define T_VDMCU_CLK_DIS BIT4
    #define T_VD200_CLK_DIS BIT8

#define T_REG_CKG_FICLK_F1 0x0F1A
    #define T_FICLK_F1_CLK_DIS BIT0
    #define T_FICLK_F2_CLK_DIS BIT4
    #define T_FODCLK_CLK_DIS BIT8

#define T_REG_CKG_FCLK 0x0F1B
    #define T_VCLK_CLK_EN BIT0
    #define T_PSRAM0_CLK_DIS BIT8
    #define T_PSRAM1_CLK_DIS BIT10
    #define T_PSRAM2_CLK_DIS BIT12

#define T_REG_CKG_VE 0x0F1C
    #define T_VE_CLK_DIS BIT0
    #define T_VEDAC_CLK_DIS BIT4
    #define T_VEIN_CLK_DIS BIT8

#define T_REG_CKG_ODCLK 0x0F1D
    #define T_ODCLK_CLK_DIS BIT0
    #define T_MPIF_CLK_DIS BIT8

#define T_REG_CKG_FCIE_CKGEN 0x0F1E
    #define T_FCIESPREAD_CLK_EN BIT0
    #define T_SM_CA_CLK_DIS BIT12

#define T_REG_CKG_FCIE 0x0F1F
    #define T_FCIE_CLK_DIS BIT0
    #define T_UART_CLK_DIS BIT8

#define T_REG_CKG_IDCLK1 0x0F20
    #define T_IDCLK1_CLK_DIS BIT0
    #define T_IDCLK2_CLK_DIS BIT8
    #define T_VIF_FREF_O_GATED_ENABLE BIT14
    #define T_VIF_FVCO_FB_O_GATED_ENABLE  BIT15

#define T_REG_CKG_HVD 0x0F21
    #define T_HVD_CLK_DIS BIT0
    #define T_VD_AEON_CLK_DIS BIT8

#define T_REG_CKG_DAC 0x0F22
    #define T_DAC_CLK_DIS BIT0
    #define T_DVBC_ADC_CLK_DIS BIT6
    #define T_DAC2_CLK_DIS BIT8
    #define T_VIF_ADC_CLK_DIS BIT14

#define T_REG_CKG_DC0 0x0F23
    #define T_DC0_CLK_DIS BIT0
    #define T_VIF_ADC_DIV2_N_CLK_GATED_ENABLE BIT5 //
    #define T_DC1_CLK_DIS BIT8
    #define T_SM_CA2_CLK_DIS BIT12

#define T_REG_CKG_VIF_DAC 0x0F2C
    #define T_VIF_DAC_CLK_DIS BIT0
    #define T_DEMOD_CLK_DIS BIT4
    #define T_DVBC_TS_CLK_DIS BIT8

#define T_REG_CKG_HDGEN 0x0F4A
    #define T_HDGEN_CLK_DIS BIT0
    #define T_HDMITX_CLK_DIS BIT4

#define T_REG_CKG_CHROMA 0x0F4B
    #define T_CHROMA_CLK_DIS BIT6
    #define T_LUMA_A_CLK_DIS BIT8
    #define T_LUMA_B_CLK_DIS BIT10
    #define T_LUMA_C_CLK_DIS BIT12
    #define T_RMEM_CLK_DIS BIT14

#define T_REG_CKG_RMEM1 0x0F4C
    #define T_RMEM1_CLK_DIS BIT0
    #define T_INTPRAM0_CLK_DIS BIT2
    #define T_INTPRAM1_CLK_DIS BIT4
    #define T_RREFDAT_CLK_DIS BIT6
    #define T_WREFDAT_CLK_DIS BIT8
    #define T_DPFF_CLK_DIS BIT10

#define T_REG_CKG_EMAC_AHB 0x0F4F
    #define T_EMAC_AHB_CLK_DIS BIT0
    #define T_EMAC_RX_CLK_DIS BIT4
    #define T_EMAC_TX_CLK_DIS BIT8
    #define T_EMAC_REF_CLK_DIS BIT12

#define T_REG_CKG_UART1 0x0F74
    #define T_UART1_CLK_DIS BIT0
    #define T_UART2_CLK_DIS BIT8


typedef struct
{
    U16 u16REG_CKG_VD;
    U16 u16REG_CKG_MVD;
    U16 u16REG_CKG_HVD;
    U16 u16REG_CKG_RMEM1;
    U16 u16REG_CKG_TSP;
    U16 u16REG_CKG_STC0;
    U16 u16REG_CKG_TS0;
    U16 u16REG_CKG_STRLD;
    U16 u16REG_CKG_IDCLK1;
    U16 u16REG_CKG_HDGEN;
    U16 u16REG_CKG_CHROMA;
    U16 u16REG_CKG_DAC;
    U16 u16REG_CKG_VE;
    U16 u16REG_CKG_FAST_UART;
    U16 u16REG_CKG_FCIE_CKGEN;
    U16 u16REG_CKG_DC0;
    U16 u16REG_CKG_ODCLK;
    U16 u16REG_CKG_VIF_DAC;
    U16 u16REG_CKG_MIU;
}CLKGEN_INFO;

typedef struct
{
    BOOL bclk_tck;
    BOOL bclk_demod_dma;
    BOOL bclk_dvbc_adc;
    BOOL bclk_dvbc_ts;
    BOOL bclk_dvbc_inner;
    BOOL bclk_dvbc_inner2x;
    BOOL bclk_dvbc_eq;
    BOOL bclk_dvbc_eq8x;
  //  BOOL bclk_dvbc_dac;
    BOOL bclk_vif_fref;
    BOOL bclk_vif_fvco_fb_o;
    BOOL bclk_vif_adc;
    BOOL bclk_vif_adc_div2;
    BOOL bclk_vif_dac;
    BOOL bclk_vd;
    BOOL bclk_vd200;
    BOOL bclk_vd_mcu;
    BOOL bclk_dc0;
    BOOL bclk_dc1;
    BOOL bclk_vd_aeon;
    BOOL bclk_jpd;
    BOOL bclk_hvd;
    BOOL bclk_rvd;
    BOOL bclk_mvd;
    BOOL bclk_mvd2;
    BOOL bclk_mvd_chroma;
    BOOL bclk_mvd_luma_a;
    BOOL bclk_mvd_luma_b;
    BOOL bclk_mvd_luma_c;
    BOOL bclk_mvd_rmem;
    BOOL bclk_mvd_rmem1;
    BOOL bclk_mvd_intpram0;
    BOOL bclk_mvd_intpram1;
    BOOL bclk_mvd_rrefdat;
    BOOL bclk_mvd_wrefdat;
    BOOL bclk_mvd_dpff;
    BOOL bclk_tsp;
    BOOL bclk_stc0;
    BOOL bclk_mad_stc;
    BOOL bclk_ts0;
    BOOL bclk_ts1;
    BOOL bclk_ts2;
    BOOL bclk_strld;
    BOOL bclk_idclk1;
    BOOL bclk_hdgen;
    BOOL bclk_hdmi_tx;
    BOOL bclk_dac;
    BOOL bclk_dac2;
    BOOL bclk_ve;
    BOOL bclk_ve_in;
    BOOL bclk_ve_dac;
    BOOL bclk_fast_uart;
    BOOL bclk_nsk;
    BOOL bclk_sm_ca;
    BOOL bclk_sm_ca2;
    BOOL bclk_pcm;
    BOOL bclk_mpif;
}CLKONOFF_INFO;
#if (ENABLE_DIP_MONITOR)
void MApp_PWS_monitor(void);
#endif


#endif


