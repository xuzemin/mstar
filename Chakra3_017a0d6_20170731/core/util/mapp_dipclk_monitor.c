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
//Filename: mapp_dipclk_monitor.c
//Prupose : To monitor the clock on-off staus  for digital IP
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_DIPCLK_MONITOR_C

#include "Board.h"
#include "datatype.h"
#include "MsTypes.h"
#include "mapp_dipclk_monitor.h"

#if  ENABLE_DIP_MONITOR
//#include "apiPWS.h"
static CLKGEN_INFO sCLKINFO;
static CLKONOFF_INFO sCLKONOFF_INFO;

void MApp_PWS_monitor(void)
{
    U16 u16Data;
    BOOL bDisplay_CLKOnOff_Status=0;
    //  printf(" %s %d \n",__FUNCTION__,__LINE__);
    //========Checking register=========
    //VD
    u16Data=MApi_PWS_Read2Byte((T_REG_CKG_VD<<1) |T_NONPM_BASE_ADDR);
    if( sCLKINFO.u16REG_CKG_VD != u16Data)
    {
        sCLKINFO.u16REG_CKG_VD=u16Data;
        printf("#####: Addr of REG_CKG_VD =0x%x \n",((T_REG_CKG_VD<<1) |T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_VD=0x%x \n",sCLKINFO.u16REG_CKG_VD);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_vd=(sCLKINFO.u16REG_CKG_VD & T_VD_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_vd_mcu=(sCLKINFO.u16REG_CKG_VD & T_VDMCU_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_vd200=(sCLKINFO.u16REG_CKG_VD & T_VD200_CLK_DIS)==0?TRUE:FALSE;
    }

   //Decoder
   u16Data=MApi_PWS_Read2Byte((T_REG_CKG_HVD<<1) |T_NONPM_BASE_ADDR);
   if(sCLKINFO.u16REG_CKG_HVD != u16Data)
   {
        sCLKINFO.u16REG_CKG_HVD=u16Data;
        printf("#####: Addr of REG_CKG_HVD =0x%x \n",((T_REG_CKG_HVD<<1)|T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_HVD=0x%x \n",sCLKINFO.u16REG_CKG_HVD);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_hvd=(sCLKINFO.u16REG_CKG_HVD & T_HVD_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_vd_aeon=(sCLKINFO.u16REG_CKG_HVD & T_VD_AEON_CLK_DIS)==0?TRUE:FALSE;
   }

   u16Data=MApi_PWS_Read2Byte((T_REG_CKG_MVD<<1) |T_NONPM_BASE_ADDR);
   if(sCLKINFO.u16REG_CKG_MVD != u16Data)
   {
        sCLKINFO.u16REG_CKG_MVD=u16Data;
        printf("#####: Addr of REG_CKG_MVD =0x%x \n",((T_REG_CKG_MVD<<1)|T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_MVD=0x%x \n",sCLKINFO.u16REG_CKG_MVD);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_mvd=(sCLKINFO.u16REG_CKG_MVD & T_MVD_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_mvd2=(sCLKINFO.u16REG_CKG_MVD & T_MVD2_CLK_DIS )==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_jpd=(sCLKINFO.u16REG_CKG_MVD & T_JPD_CLK_DIS)==0?TRUE:FALSE;
   }

   u16Data=MApi_PWS_Read2Byte((T_REG_CKG_RMEM1<<1) |T_NONPM_BASE_ADDR);
   if(sCLKINFO.u16REG_CKG_RMEM1 != u16Data)
   {
        sCLKINFO.u16REG_CKG_RMEM1=u16Data;
        printf("#####: Addr of REG_CKG_MVD =0x%x \n",((T_REG_CKG_RMEM1<<1)|T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_RMEM1=0x%x \n",sCLKINFO.u16REG_CKG_RMEM1);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_mvd_rmem1=(sCLKINFO.u16REG_CKG_RMEM1 & T_RMEM1_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_mvd_intpram0=(sCLKINFO.u16REG_CKG_RMEM1 & T_INTPRAM0_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_mvd_intpram1=(sCLKINFO.u16REG_CKG_RMEM1 & T_INTPRAM1_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_mvd_rrefdat=(sCLKINFO.u16REG_CKG_RMEM1 & T_RREFDAT_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_mvd_wrefdat=(sCLKINFO.u16REG_CKG_RMEM1 & T_WREFDAT_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_mvd_dpff=(sCLKINFO.u16REG_CKG_RMEM1 & T_DPFF_CLK_DIS)==0?TRUE:FALSE;
   }

   u16Data=MApi_PWS_Read2Byte((T_REG_CKG_TSP<<1) |T_NONPM_BASE_ADDR);
   if(sCLKINFO.u16REG_CKG_TSP != u16Data)
   {
        sCLKINFO.u16REG_CKG_TSP=u16Data;
        printf("#####: Addr of REG_CKG_TSP =0x%x \n",((T_REG_CKG_TSP<<1)|T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_TSP=0x%x \n",sCLKINFO.u16REG_CKG_TSP);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_tsp=(sCLKINFO.u16REG_CKG_TSP & T_TSP_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_tck=(sCLKINFO.u16REG_CKG_TSP & T_TCK_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_nsk=(sCLKINFO.u16REG_CKG_TSP & T_NSK_CLK_DIS)==0?TRUE:FALSE;
   }

   u16Data=MApi_PWS_Read2Byte((T_REG_CKG_STC0<<1) |T_NONPM_BASE_ADDR);
   if(sCLKINFO.u16REG_CKG_STC0 != u16Data)
   {
        sCLKINFO.u16REG_CKG_STC0=u16Data;
        printf("#####: Addr of REG_CKG_STC0 =0x%x \n",((T_REG_CKG_STC0<<1)|T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_STC0=0x%x \n",sCLKINFO.u16REG_CKG_STC0);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_stc0=(sCLKINFO.u16REG_CKG_STC0 & T_STC0_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_mad_stc=(sCLKINFO.u16REG_CKG_STC0 & T_MAD_STC_CLK_DIS)==0?TRUE:FALSE;
   }

   u16Data=MApi_PWS_Read2Byte((T_REG_CKG_TS0<<1) |T_NONPM_BASE_ADDR);
   if(sCLKINFO.u16REG_CKG_TS0 != u16Data)
   {
        sCLKINFO.u16REG_CKG_TS0=u16Data;
        printf("#####: Addr of REG_CKG_TS0 =0x%x \n",((T_REG_CKG_TS0<<1)|T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_TS0=0x%x \n",sCLKINFO.u16REG_CKG_TS0);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_ts0=(sCLKINFO.u16REG_CKG_TS0 & T_TS0_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_ts1=(sCLKINFO.u16REG_CKG_TS0 & T_TS1_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_ts2=(sCLKINFO.u16REG_CKG_TS0 & T_TS2_CLK_DIS)==0?TRUE:FALSE;
        //sCLKONOFF_INFO.bclk_tsout=(sCLKINFO.u16REG_CKG_TS0 & T_TSOUT_CLK_DIS)==0?TRUE:FALSE;
   }

   u16Data=MApi_PWS_Read2Byte((T_REG_CKG_STRLD<<1) |T_NONPM_BASE_ADDR);
   if(sCLKINFO.u16REG_CKG_STRLD != u16Data)
   {
        sCLKINFO.u16REG_CKG_STRLD=u16Data;
        printf("#####: Addr of REG_CKG_STRLD =0x%x \n",((T_REG_CKG_STRLD<<1)|T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_STRLD=0x%x \n",sCLKINFO.u16REG_CKG_STRLD);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_strld=(sCLKINFO.u16REG_CKG_STRLD & T_STRLD_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_rvd=(sCLKINFO.u16REG_CKG_STRLD & T_RVD_CLK_DIS)==0?TRUE:FALSE;
        sCLKONOFF_INFO.bclk_pcm=(sCLKINFO.u16REG_CKG_STRLD & T_PCM_CLK_DIS)==0?TRUE:FALSE;
   }

   //Scaler ( idclk1/hdgen/hdmi_tx)
   u16Data=MApi_PWS_Read2Byte((T_REG_CKG_IDCLK1<<1) |T_NONPM_BASE_ADDR);
   if(sCLKINFO.u16REG_CKG_IDCLK1 != u16Data)
   {
        sCLKINFO.u16REG_CKG_IDCLK1=u16Data;
        printf("#####: Addr of REG_CKG_IDCLK1 =0x%x \n",((T_REG_CKG_IDCLK1<<1)|T_NONPM_BASE_ADDR));
        printf("#####: REG_CKG_IDCLK1=0x%x \n",sCLKINFO.u16REG_CKG_IDCLK1);
        bDisplay_CLKOnOff_Status=1;
        sCLKONOFF_INFO.bclk_idclk1=(sCLKINFO.u16REG_CKG_IDCLK1 & T_IDCLK1_CLK_DIS)==0?TRUE:FALSE;
       // sCLKONOFF_INFO.bclk_idclk2=(sCLKINFO.u16REG_CKG_IDCLK1 & T_IDCLK2_CLK_DIS)==0?TRUE:FALSE;
       sCLKONOFF_INFO.bclk_vif_fref=(sCLKINFO.u16REG_CKG_IDCLK1 & T_VIF_FREF_O_GATED_ENABLE)==0?TRUE:FALSE;
       sCLKONOFF_INFO.bclk_vif_fvco_fb_o=(sCLKINFO.u16REG_CKG_IDCLK1 & T_VIF_FVCO_FB_O_GATED_ENABLE)==0?TRUE:FALSE;

    }

//HDGEN
u16Data=MApi_PWS_Read2Byte((T_REG_CKG_HDGEN<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_HDGEN != u16Data)
{
     sCLKINFO.u16REG_CKG_HDGEN=u16Data;
     printf("#####: Addr of REG_CKG_HDGEN =0x%x \n",((T_REG_CKG_HDGEN<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_HDGEN=0x%x \n",sCLKINFO.u16REG_CKG_HDGEN);
     bDisplay_CLKOnOff_Status=1;
     sCLKONOFF_INFO.bclk_hdgen=(sCLKINFO.u16REG_CKG_HDGEN & T_HDGEN_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_hdmi_tx=(sCLKINFO.u16REG_CKG_HDGEN & T_HDMITX_CLK_DIS)==0?TRUE:FALSE;
}

//Chroma
u16Data=MApi_PWS_Read2Byte((T_REG_CKG_CHROMA<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_CHROMA != u16Data)
{
     sCLKINFO.u16REG_CKG_CHROMA=u16Data;
     printf("#####: Addr of REG_CKG_CHROMA =0x%x \n",((T_REG_CKG_CHROMA<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_CHROMA=0x%x \n",sCLKINFO.u16REG_CKG_CHROMA);
     bDisplay_CLKOnOff_Status=1;
     sCLKONOFF_INFO.bclk_mvd_chroma=(sCLKINFO.u16REG_CKG_CHROMA & T_CHROMA_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_mvd_luma_a=(sCLKINFO.u16REG_CKG_CHROMA & T_LUMA_A_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_mvd_luma_b=(sCLKINFO.u16REG_CKG_CHROMA & T_LUMA_B_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_mvd_luma_c=(sCLKINFO.u16REG_CKG_CHROMA & T_LUMA_C_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_mvd_rmem=(sCLKINFO.u16REG_CKG_CHROMA & T_RMEM_CLK_DIS)==0?TRUE:FALSE;
}


//DAC
u16Data=MApi_PWS_Read2Byte((T_REG_CKG_DAC<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_DAC != u16Data)
{
     sCLKINFO.u16REG_CKG_DAC=u16Data;
     printf("#####: Addr of REG_CKG_DAC =0x%x \n",((T_REG_CKG_DAC<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_DAC=0x%x \n",sCLKINFO.u16REG_CKG_DAC);
     bDisplay_CLKOnOff_Status=1;
     sCLKONOFF_INFO.bclk_dac=(sCLKINFO.u16REG_CKG_DAC & T_DAC_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_dvbc_adc=(sCLKINFO.u16REG_CKG_DAC & T_DVBC_ADC_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_dac2=(sCLKINFO.u16REG_CKG_DAC & T_DAC2_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_vif_adc=(sCLKINFO.u16REG_CKG_DAC & T_VIF_ADC_CLK_DIS)==0?TRUE:FALSE;

}

//VE
u16Data=MApi_PWS_Read2Byte((T_REG_CKG_VE<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_VE != u16Data)
{
     sCLKINFO.u16REG_CKG_VE=u16Data;
     printf("#####: Addr of REG_CKG_VE =0x%x \n",((T_REG_CKG_VE<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_VE=0x%x \n",sCLKINFO.u16REG_CKG_VE);
     bDisplay_CLKOnOff_Status=1;
     sCLKONOFF_INFO.bclk_ve=(sCLKINFO.u16REG_CKG_VE & T_VE_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_ve_dac=(sCLKINFO.u16REG_CKG_VE & T_VEDAC_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_ve_in=(sCLKINFO.u16REG_CKG_VE & T_VEIN_CLK_DIS)==0?TRUE:FALSE;
}

//UART

u16Data=MApi_PWS_Read2Byte((T_REG_CKG_FAST_UART<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_FAST_UART != u16Data)
{
     sCLKINFO.u16REG_CKG_FAST_UART=u16Data;
     printf("#####: Addr of REG_CKG_FAST_UART =0x%x \n",((T_REG_CKG_FAST_UART<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_FAST_UART=0x%x \n",sCLKINFO.u16REG_CKG_FAST_UART);
     bDisplay_CLKOnOff_Status=1;
     sCLKONOFF_INFO.bclk_fast_uart=(sCLKINFO.u16REG_CKG_FAST_UART & T_FAST_UART_CLK_DIS)==0?TRUE:FALSE;
}


//CA

u16Data=MApi_PWS_Read2Byte((T_REG_CKG_FCIE_CKGEN<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_FCIE_CKGEN != u16Data)
{
     sCLKINFO.u16REG_CKG_FCIE_CKGEN=u16Data;
     printf("#####: Addr of REG_CKG_FCIE_CKGEN =0x%x \n",((T_REG_CKG_FCIE_CKGEN<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_FCIE_CKGEN=0x%x \n",sCLKINFO.u16REG_CKG_FCIE_CKGEN);
     bDisplay_CLKOnOff_Status=1;
    // sCLKONOFF_INFO.bclk_fciespread=(sCLKINFO.u16REG_CKG_FCIE_CKGEN & T_FCIESPREAD_CLK_EN)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_sm_ca=(sCLKINFO.u16REG_CKG_FCIE_CKGEN & T_SM_CA_CLK_DIS)==0?TRUE:FALSE;
}

u16Data=MApi_PWS_Read2Byte((T_REG_CKG_DC0<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_DC0 != u16Data)
{
     sCLKINFO.u16REG_CKG_DC0=u16Data;
     printf("#####: Addr of REG_CKG_DC0 =0x%x \n",((T_REG_CKG_DC0<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_DC0=0x%x \n",sCLKINFO.u16REG_CKG_DC0);
     bDisplay_CLKOnOff_Status=1;
     sCLKONOFF_INFO.bclk_dc0=(sCLKINFO.u16REG_CKG_DC0 & T_DC0_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_dc1=(sCLKINFO.u16REG_CKG_DC0 & T_DC1_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_sm_ca2=(sCLKINFO.u16REG_CKG_DC0 & T_SM_CA2_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_vif_adc_div2=(sCLKINFO.u16REG_CKG_DC0 & T_VIF_ADC_DIV2_N_CLK_GATED_ENABLE)==0?TRUE:FALSE;
}

//MPIF
u16Data=MApi_PWS_Read2Byte((T_REG_CKG_ODCLK<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_ODCLK != u16Data)
{
     sCLKINFO.u16REG_CKG_ODCLK=u16Data;
     printf("#####: Addr of REG_CKG_ODCLK =0x%x \n",((T_REG_CKG_ODCLK<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_ODCLK=0x%x \n",sCLKINFO.u16REG_CKG_ODCLK);
     bDisplay_CLKOnOff_Status=1;
    // sCLKONOFF_INFO.bclk_odclk=(sCLKINFO.u16REG_CKG_ODCLK & T_ODCLK_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_mpif=(sCLKINFO.u16REG_CKG_ODCLK & T_MPIF_CLK_DIS)==0?TRUE:FALSE;
}

//
u16Data=MApi_PWS_Read2Byte((T_REG_CKG_VIF_DAC<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_VIF_DAC != u16Data)
{
     sCLKINFO.u16REG_CKG_VIF_DAC=u16Data;
     printf("#####: Addr of REG_CKG_VIF_DAC =0x%x \n",((T_REG_CKG_VIF_DAC<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_VIF_DAC=0x%x \n",sCLKINFO.u16REG_CKG_VIF_DAC);
     bDisplay_CLKOnOff_Status=1;
    // sCLKONOFF_INFO.bclk_odclk=(sCLKINFO.u16REG_CKG_ODCLK & T_ODCLK_CLK_DIS)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_vif_dac=(sCLKINFO.u16REG_CKG_VIF_DAC & T_VIF_DAC_CLK_DIS)==0?TRUE:FALSE;
    sCLKONOFF_INFO.bclk_demod_dma=(sCLKINFO.u16REG_CKG_VIF_DAC & T_DEMOD_CLK_DIS)==0?TRUE:FALSE;
    sCLKONOFF_INFO.bclk_dvbc_ts=(sCLKINFO.u16REG_CKG_VIF_DAC & T_DVBC_TS_CLK_DIS)==0?TRUE:FALSE;
}

//
u16Data=MApi_PWS_Read2Byte((T_REG_CKG_MIU<<1) |T_NONPM_BASE_ADDR);
if(sCLKINFO.u16REG_CKG_MIU != u16Data)
{
     sCLKINFO.u16REG_CKG_MIU=u16Data;
     printf("#####: Addr of REG_CKG_VIF_DAC =0x%x \n",((T_REG_CKG_MIU<<1)|T_NONPM_BASE_ADDR));
     printf("#####: REG_CKG_VIF_DAC=0x%x \n",sCLKINFO.u16REG_CKG_VIF_DAC);
     bDisplay_CLKOnOff_Status=1;
     sCLKONOFF_INFO.bclk_dvbc_inner=(sCLKINFO.u16REG_CKG_MIU & T_DVBC_INNER_GATED_ENABLE)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_dvbc_inner2x=(sCLKINFO.u16REG_CKG_MIU & T_DVBC_INNER2X_GATED_ENABLE)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_dvbc_eq=(sCLKINFO.u16REG_CKG_MIU & T_DVBC_EQ_GATED_ENABLE)==0?TRUE:FALSE;
     sCLKONOFF_INFO.bclk_dvbc_eq8x=(sCLKINFO.u16REG_CKG_MIU & T_DVBC_DVBC_EQ8X_GATED_ENABLE)==0?TRUE:FALSE;
}


//=======Check Clock

if(bDisplay_CLKOnOff_Status)
{
    printf(":================DIGITAl IP CLK tree report (Register) ================\n");
    PWS_PRINT("REG_CKG_FAST_UART",sCLKINFO.u16REG_CKG_FAST_UART);
    PWS_PRINT("REG_CKG_STC0",sCLKINFO.u16REG_CKG_STC0);
    PWS_PRINT("REG_CKG_MIU",sCLKINFO.u16REG_CKG_MIU);
    PWS_PRINT("REG_CKG_TS0",sCLKINFO.u16REG_CKG_TS0);
    PWS_PRINT("REG_CKG_TSP",sCLKINFO.u16REG_CKG_TSP);
    PWS_PRINT("REG_CKG_MVD",sCLKINFO.u16REG_CKG_MVD);
    PWS_PRINT("REG_CKG_STRLD",sCLKINFO.u16REG_CKG_STRLD);
    PWS_PRINT("REG_CKG_VD",sCLKINFO.u16REG_CKG_VD);
    PWS_PRINT("REG_CKG_VE",sCLKINFO.u16REG_CKG_VE);
    PWS_PRINT("REG_CKG_ODCLK",sCLKINFO.u16REG_CKG_ODCLK);
    PWS_PRINT("REG_CKG_FCIE_CKGEN",sCLKINFO.u16REG_CKG_FCIE_CKGEN);
    PWS_PRINT("REG_CKG_IDCLK1",sCLKINFO.u16REG_CKG_IDCLK1);
    PWS_PRINT("REG_CKG_HVD",sCLKINFO.u16REG_CKG_HVD);
    PWS_PRINT("REG_CKG_DAC",sCLKINFO.u16REG_CKG_DAC);
    PWS_PRINT("REG_CKG_DC0",sCLKINFO.u16REG_CKG_DC0);
    PWS_PRINT("REG_CKG_HDGEN",sCLKINFO.u16REG_CKG_HDGEN);
    PWS_PRINT("REG_CKG_CHROMA",sCLKINFO.u16REG_CKG_CHROMA);
    PWS_PRINT("REG_CKG_RMEM1",sCLKINFO.u16REG_CKG_RMEM1);



    printf(":================DIGITAl IP CLK tree report (CLK On/OFF) ================\n");
    PWS_PRINT("bclk_tck",sCLKONOFF_INFO.bclk_tck);
    PWS_PRINT("bclk_demod_dma",sCLKONOFF_INFO.bclk_demod_dma);
    PWS_PRINT("bclk_dvbc_adc",sCLKONOFF_INFO.bclk_dvbc_adc);
    PWS_PRINT("bclk_dvbc_ts",sCLKONOFF_INFO.bclk_dvbc_ts);
    PWS_PRINT("bclk_dvbc_inner",sCLKONOFF_INFO.bclk_dvbc_inner);
    PWS_PRINT("bclk_dvbc_inner2x",sCLKONOFF_INFO.bclk_dvbc_inner2x);
    PWS_PRINT("bclk_dvbc_eq",sCLKONOFF_INFO.bclk_dvbc_eq);
    PWS_PRINT("bclk_dvbc_eq8x",sCLKONOFF_INFO.bclk_dvbc_eq8x);
   // PWS_PRINT("bclk_dvbc_dac",sCLKONOFF_INFO.bclk_dvbc_dac);
    PWS_PRINT("bclk_vif_fref",sCLKONOFF_INFO.bclk_vif_fref);
    PWS_PRINT("bclk_vif_fvco_fb_o",sCLKONOFF_INFO.bclk_vif_fvco_fb_o);
    PWS_PRINT("bclk_vif_adc",sCLKONOFF_INFO.bclk_vif_adc);
    PWS_PRINT("bclk_vif_adc_div2",sCLKONOFF_INFO.bclk_vif_adc_div2);
    PWS_PRINT("bclk_vif_dac",sCLKONOFF_INFO.bclk_vif_dac);
    PWS_PRINT("bclk_vd",sCLKONOFF_INFO.bclk_vd);
    PWS_PRINT("bclk_vd200",sCLKONOFF_INFO.bclk_vd200);
    PWS_PRINT("bclk_vd_mcu",sCLKONOFF_INFO.bclk_vd_mcu);
    PWS_PRINT("bclk_dc0",sCLKONOFF_INFO.bclk_dc0);
    PWS_PRINT("bclk_dc1",sCLKONOFF_INFO.bclk_dc1);
    PWS_PRINT("bclk_vd_aeon",sCLKONOFF_INFO.bclk_vd_aeon);
    PWS_PRINT("bclk_jpd",sCLKONOFF_INFO.bclk_jpd);
    PWS_PRINT("bclk_hvd",sCLKONOFF_INFO.bclk_hvd);
    PWS_PRINT("bclk_rvd",sCLKONOFF_INFO.bclk_rvd);
    PWS_PRINT("bclk_mvd",sCLKONOFF_INFO.bclk_mvd);
    PWS_PRINT("bclk_mvd2",sCLKONOFF_INFO.bclk_mvd2);
    PWS_PRINT("bclk_mvd_chroma",sCLKONOFF_INFO.bclk_mvd_chroma);
    PWS_PRINT("bclk_mvd_luma_a",sCLKONOFF_INFO.bclk_mvd_luma_a);
    PWS_PRINT("bclk_mvd_luma_b",sCLKONOFF_INFO.bclk_mvd_luma_b);
    PWS_PRINT("bclk_mvd_luma_c",sCLKONOFF_INFO.bclk_mvd_luma_c);
    PWS_PRINT("bclk_mvd_rmem",sCLKONOFF_INFO.bclk_mvd_rmem);
    PWS_PRINT("bclk_mvd_rmem1",sCLKONOFF_INFO.bclk_mvd_rmem1);
    PWS_PRINT("bclk_mvd_intpram0",sCLKONOFF_INFO.bclk_mvd_intpram0);
    PWS_PRINT("bclk_mvd_intpram1",sCLKONOFF_INFO.bclk_mvd_intpram1);
    PWS_PRINT("bclk_mvd_rrefdat",sCLKONOFF_INFO.bclk_mvd_rrefdat);
    PWS_PRINT("bclk_mvd_wrefdat",sCLKONOFF_INFO.bclk_mvd_wrefdat);
    PWS_PRINT("bclk_mvd_dpff",sCLKONOFF_INFO.bclk_mvd_dpff);
    PWS_PRINT("bclk_tsp",sCLKONOFF_INFO.bclk_tsp);
    PWS_PRINT("bclk_stc0",sCLKONOFF_INFO.bclk_stc0);
    PWS_PRINT("bclk_mad_stc",sCLKONOFF_INFO.bclk_mad_stc);
    PWS_PRINT("bclk_ts0",sCLKONOFF_INFO.bclk_ts0);
    PWS_PRINT("bclk_ts1",sCLKONOFF_INFO.bclk_ts1);
    PWS_PRINT("bclk_ts2",sCLKONOFF_INFO.bclk_ts2);
    PWS_PRINT("bclk_strld",sCLKONOFF_INFO.bclk_strld);
    PWS_PRINT("bclk_idclk1",sCLKONOFF_INFO.bclk_idclk1);
    PWS_PRINT("bclk_hdgen",sCLKONOFF_INFO.bclk_hdgen);
    PWS_PRINT("bclk_hdmi_tx",sCLKONOFF_INFO.bclk_hdmi_tx);
    PWS_PRINT("bclk_dac",sCLKONOFF_INFO.bclk_dac);
    PWS_PRINT("bclk_dac2",sCLKONOFF_INFO.bclk_dac2);
    PWS_PRINT("bclk_ve",sCLKONOFF_INFO.bclk_ve);
    PWS_PRINT("bclk_ve_in",sCLKONOFF_INFO.bclk_ve_in);
    PWS_PRINT("bclk_ve_dac",sCLKONOFF_INFO.bclk_ve_dac);
    PWS_PRINT("bclk_fast_uart",sCLKONOFF_INFO.bclk_fast_uart);
    PWS_PRINT("bclk_nsk",sCLKONOFF_INFO.bclk_nsk);
    PWS_PRINT("bclk_sm_ca",sCLKONOFF_INFO.bclk_sm_ca);
    PWS_PRINT("bclk_sm_ca2",sCLKONOFF_INFO.bclk_sm_ca2);
    PWS_PRINT("bclk_pcm",sCLKONOFF_INFO.bclk_pcm);
    PWS_PRINT("bclk_mpif",sCLKONOFF_INFO.bclk_mpif);

}

}
#endif


#undef MAPP_DIPCLK_MONITOR_C