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
#ifndef _ENUM_DEVICE_H_
#define _ENUM_DEVICE_H_

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define FREQ_12MHZ              (12000000UL)
#define FREQ_14P318MHZ          (14318180UL)
#define FREQ_24MHZ              (24000000UL)
#define FREQ_67P5MHZ            (67500000UL)
#define FREQ_83MHZ              (83000000UL)
#define FREQ_90MHZ              (90000000UL)
#define FREQ_108MHZ             (108000000UL)
#define FREQ_120MHZ             (120000000UL)
#define FREQ_123MHZ             (123428000UL)
#define FREQ_125MHZ             (125000000UL)
#define FREQ_130MHZ             (130000000UL)
#define FREQ_135MHZ             (135000000UL)
#define FREQ_141MHZ             (141000000UL)
#define FREQ_144MHZ             (144000000UL)
#define FREQ_160MHZ             (160000000UL)
#define FREQ_166MHZ             (166000000UL)
#define FREQ_170MHZ             (170000000UL)
#define FREQ_172P8MHZ           (172800000UL)
#define FREQ_180MHZ             (180000000UL)
#define FREQ_195MHZ             (195000000UL)
#define FREQ_200MHZ             (200000000UL)
#define FREQ_210MHZ             (210000000UL)
#define FREQ_220MHZ             (220000000UL)
#define FREQ_230MHZ             (230000000UL)
#define FREQ_250MHZ             (250000000UL)
#define FREQ_312MHZ             (312000000UL)
#define FREQ_336MHZ             (336000000UL)

//------------------------------------------------------------------------------------
//  FRONTEND_DEMOD_TYPE
//------------------------------------------------------------------------------------
//#define ZARLINK_ZL10353_DEMODE          0   // DVB COFDM Demodulator
#define MSTAR_MSB1200_DEMOD             1   // DVB COFDM Demodulator
#define LEGEND_8G13_DEMOD               2   // DMB-T COFDM Demodulator
//#define MTK_5131_DEMOD                  3   // MTK solution for Samsung DVBT project
//#define ZARLINK_CE6355_DEMOD            4   // DVB COFDM Demodulator
#define LEGEND_8G42_DEMOD               5   // LEGEND DMB-T Demodulator
#define LEGEND_8G52_DEMOD               6   // LEGEND DMB-T Demodulator
#define MSTAR_MSB1210_DEMOD             7   // DVB COFDM Demodulator
//#define TOSHIBA_TC90512XBG_DEMOD        8   // TOSHIBA ISDB-T Demodulator
#define MONTAGE_M88DC2800_DEMOD         9   // DVB-C COFDM Demodulator
#define MONTAGE_M88DD2000_DEMOD         10  // DMB-T COFDM Demodulator
#define EMBEDDED_DVBT_DEMOD             11  // Internal DVB-T Demodulator
#define EMBEDDED_DVBC_DEMOD             12  // Internal DVB-C Demodulator
#define EMBEDDED_ATSC_DEMOD             13  // Internal ATSC Demodulator
//#define TOSHIBA_TC90517FG_DEMOD         14  // TOSHIBA ISDB-T Demodulator
#define DIB_DiB8006GP_DEMOD             15  // DIB ISDB-T Demodulator
//#define TOSHIBA_TC90527FG_DEMOD         16  // TOSHIBA ISDB-T Demodulator
#define MSTAR_MSB1400_DEMOD             17  // MSTAR ISDBT Demodulator
#define EMBEDDED_ISDBT_DEMOD            18  // Internal ISDB-T Demodulator
#define EMBEDDED_DVBS_DEMOD             19  // Internal DVB-S Demodulator

#define ALTOBEAM_883X                   20  // ALTOBEAM DTMB Demodulator
#define ALTOBEAM_884X                   21  // ALTOBEAM DTMB Demodulator
#define ALTOBEAM_885X                   22  // ALTOBEAM DTMB Demodulator
#define ALTOBEAM_886X                   23  // ALTOBEAM DTMB Demodulator
#define ALTOBEAM_887X                   24  // ALTOBEAM DTMB Demodulator
#define ALTOBEAM_888X                   25  // ALTOBEAM DTMB Demodulator
#define LEGEND_8G80_DEMOD               26  // LEGEND DMB-T Demodulator
#define LEGEND_8G75_DEMOD               27  // LEGEND DVB-C+DTMB Demodulator
#define LEGEND_9x_DEMOD                 28  // LEGEND DVB-C+DTMB Demodulator
#define HDIC_2311                       29  // HDIC DTMB Demodulator
#define LG_3303_DEMODE                  30  // ATSC 8VSB & XQAM Demodulator
#define SAMSUNG_S5H1409_DEMODE          31  // ATSC 8VSB & XQAM Demodulator
#define PHILIPS_TUV1236D_DEMODE         32  // ATSC 8VSB & XQAM Demodulator
#define OLD_LG_3304_DEMODE              33  // ATSC 8VSB & XQAM Demodulator
#define LG_3304_DEMODE                  34  // ATSC 8VSB & XQAM Demodulator
#define SAMSUNG_S5H1410_DEMODE          36  // ATSC 8VSB & XQAM Demodulator
#define MSTAR_MSB1500_DEMODE            37  // ATSC 8VSB & XQAM Demodulator
#define MSTAR_MSB1501_DEMODE            38

#define DEMOD_AVL6211                   40  // DVBS
#define MSTAR_MSB131X_DVBS2             41

//------------------------------------------------------------------------------------
//  FRONTEND_DEMOD_DTMB_TYPE
//------------------------------------------------------------------------------------
//
#define MSTAR_MSB101M_DTMB              50  // MSTAR external DTMB Demodulator(Cashmere) MSD034B, No product any more
#define MSTAR_MSB101M_DTMB_MSD046B      51  // MSTAR external DTMB Demodulator(Cashmere)

#define EXTERNAL_DTMB_DEMOD             52  // MSTAR external DTMB Demodulator(Cashmere)
#define EMBEDDED_DTMB_DEMOD             53  // MSTAR embedded DTMB Demodulator(Cashmere)

//
//------------------------------------------------------------------------------------
//  FRONTEND_DEMOD_T2_TYPE
//------------------------------------------------------------------------------------
#define MSTAR_MSB123X_DVBT2             60
#define MSTAR_MSB101A_DVBT2             61  // MSB 1233C
#define EMBEDDED_DVBT2_DEMOD            62  // Internal DVB-T2 Demodulator
#define MSTAR_MSB124X_DVBT              63

//------------------------------------------------------------------------------------
//  FRONTEND_DEMOD_S2_TYPE
//------------------------------------------------------------------------------------
#define MSTAR_MSB124X_DVBS2             70
#define MSTAR_MSB1245_DVBS2             71


#define MSTAR_NONE_DEMOD                99  // no Demodulator



//------------------------------------------------------------------------------------
//DISH_TYPE
//------------------------------------------------------------------------------------
#define DISH_NONE               0
#define DISH_DEMOD              1
#define DISH_A8293              2
#define DISH_A8304              3
#define DISH_RT5047             4

//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//FRONTEND_TUNER_TYPE
//------------------------------------------------------------------------------------

// MSTAR
#define MSTAR_MSR1200_TUNER             1   // Silicon Tuner for ATSC & DVB
#define MSTAR_MSR1200                   2   //Silicon Tuner
#define MSTAR_AVATAR2                   3

// PHILIPS
#define PHILIPS_TDA1316_TUNER           20  // DVB RF Tuner
#define PHILIPS_FQD1216_TUNER           21  // DVB RF Tuner
#define PHILIPS_FQD1218_TUNER           22
#define PHILIPS_FQD1116_TUNER           23
#define PHILIPS_TD1318AFLHP_3X_TUNER    24
#define PHILIPS_FQD1236_TUNER           25

// NXP
#define NXP_TD1616EF_TUNER              40
#define NXP_FQD1136_TUNER               41
#define NXP_FH2608_TUNER                42
#define NXP_FH2603_TUNER                43
#define NXP_FH2112_TUNER                44
#define NXP_TH2603_TUNER                45
#define NXP_TD1636ALMK2_TUNER           46    // ATSC RF Tuner
#define NXP_TD1136_TUNER                47
#define NXP_TDA18272_TUNER              48
#define NXP_TDA18273_TUNER              49     //--> NUTUNE_FK1602_TUNER,For ATSC Silicon Tuner,different from DVB NUTUNE_FK1602_TUNER
#define NXP_TDA18274_TUNER              50
#define NXP_TDA18275_TUNER              51
#define NXP_TDA182I5a_TUNER             52
#define NXP_TDA18275A_TUNER             53

// MAXLINEAR
#define MxL_301RF_TUNER                 70
#define MxL_601SI_TUNER                 71
#define MxL_661SI_TUNER                 72

// SONY
#define SONY_SUT_RE231_TUNER            90
#define SONY_SUT_PE232_DVBS_TUNER       91
#define SONY_SUT_PEx41_TUNER            92

// SHARP
#define SHARP_VA1Y1ED_TUNER             110
#define SHARP_VA1T1ED_6060              111
#define SHARP_VA1G5BF2009_TUNER         112  // RF Tuner
#define SHARP_VA1E1CD2403_TUNER         113
#define SHARP_VA1E1BF1402_TUNER         114
#define SHARP_VA1Y2UR2201_TUNER         115  // ATSC RF Tuner
#define SHARP_BS2S7VZ7801_TUNER         116

// SAMAUNG
#define SAMSUNG_DTOS40AMH201A_TUNER     130
#define SAMSUNG_S205_TUNER              131  // ATSC RF Tuner
#define SAMSUNG_EH201A_TUNER            132  // ATSC RF Tuner
#define SAMSUNG_DVTA50_TUNER            133
#define SEC_DTOS403LH121A               134
#define SAMSUNG_S203FH201B_TUNER        135
#define SEC_DTOS403IR121B               136
#define SAMSUNG_DTVS20CVL081A_TUNER     137
#define SAMSUNG_DTVS70CVH073A_TUNER     138
#define SAMSUNG_SI2176_TUNER            139  //Silab Tuner CVBS and SIF out

// LG
#define LG_TDTC_G001D_TUNER             150
#define LG_TDCC_G031D_TUNER             151
#define LG_TDFV_G135D_TUNER             152
#define LG_TDTK_G732D_B                 153
#define LG_TDVS_H703P_TUNER             153
#define LG_TDTC_G501D_TUNER             155
#define LG_TDTC_G311D_TUNER             156
#define LG_TDTC_G601D_TUNER             157
#define LG_TDTC_GX01D_GX71D_TUNER       158
#define LG_TDTC_G901D_TUNER             159
#define LG_G230D_TUNER                  160

// XUGUANG
#define XUGUANG_TDQ_6FT_W116H           170 // Analog Tuner for ATV only
#define XUGUANG_DDT8A1C_TUNER           171
#define XUGUANG_STM_6F_V236H_TUNER      172
#define XUGUANG_HFT_8B1_V116H_TUNER     173
#define XUGUANG_HFT_8B_115CW_TUNER      174
#define XUGUANG_DVT_8ADC1_W41F2         175

//QINGJIA
#define QINGJIA_DAI4W500G_TUNER         190
#define QINGJIA_DTZ0W302G_TUNER         191
#define QINGJIA_AFT7W006_TUNER          192
#define QINGJIA_DTT9W303G_TUNER         193

// TCL
#define TCL_DTC78WI_3E_TUNER            210
#define TCL_DT70WI_3R_TUNER             211
#define TCL_F17CT_6N_E_TUNER            212
#define TCL_DT61WI_2R_E_TUNER           213
#define TCL_F20WT_3DD_E                 214 //TCL SAWLESS tuner
#define TCL_DT58WT_3RB_E_TUNER          215
#define TCL_DA91WT_13_E_TUNER           216 //TCL ATSC Sawless Tuner
#define TCL_DT91WT_2_E_TUNER            217 //TCL DVB-T Sawless Tuner

// ALPS
#define ALPS_TDQG4602A_TUNER            230
#define ALPS_TDQG9_601A_TUNER           231
#define ALPS_TDQU4_TUNER                232 // ATSC RF Tuner
#define ALPS_TDQU6_TUNER                233 // ATSC RF Tuner  //SEC ATSC project
#define ALPS_TDHG6_K02A_TUNER           234 //always with MTK_5131_DEMOD

// THOMSON
#define THOMSON_FE6640_TUNER            250   // DVB RF Tuner
#define THOMSON_DTT75407_TUNER          251
#define THOMSON_DTT7630_TUNER           252    // ATSC RF Tuner

// CHANGHONG
#define CH_TMI8_C22I1VH_TUNER           270
#define CHANGHONG_DTI1_E4I1VH           271 //Changhong tuner

// NUTUNE
#define NUTUNE_FI4801_TUNER             290
#define NUTUNE_FT2131_TUNER             291
#define NUTUNE_FK1602_TUNER             292

// SILAB
#define SILAB_2158_TUNER                310
#define SILAB_2190_TUNER                311
#define SILAB_2157_TUNER                312
#define SILAB_2151_TUNER                313
#define SILAB_2190B_TUNER              314

// SILICON
#define SILICON_R620D_TUNER             330

// AVAILINK
#define AVAILINK_AV2011                 340
#define AVAILINK_AV2012                 341
#define AVAILINK_AV2017                 342

// RAFAEL
#define RAFAEL_R828_TUNER               350
#define RAFAEL_R840_TUNER               351
#define RAFAEL_RT710_TUNER              352
#define RAFAEL_R842_TUNER               353

// Xilinx
#define XC5200_TUNER                    360

// CDT
#define CDT_9BT322_40_TUNER             370
#define CDT_SFT338_40_TUNER             371 // ATSC

// RDA
#define RDA5815M_DVBS_TUNER             380
#define RDA5158_TUNER                   381

// Honeywld
#define XC7000_TUNER                    390

//
#define LINGHUA_TDP_1H1_E_TUNER         400 //Analog Tuner For ATV Only 2009-12-22

//
#define DMCT_6A_111_TUNER               401
#define FRESCO_FM2150A_TUNER            402
#define NM_120V_TUNER                   403









//------------------------------------------------------------------------------------
// FRONTEND_IF_DEMODE_TYPE
//------------------------------------------------------------------------------------
#define PHILIPS_TDA9886                 0   // DVB Domodulator for Analog AV
#define PHILIPS_TDA9881                 1
#define RENESAS_R2A10406NP              2
#define MSTAR_VIF                       3
#define MSTAR_VIF_MSB1210               4    // MSB1210 DVB-T + VIF Demodulator
#define TOSHIBA_TC90512XBG_IF           5
#define MSTAR_INTERN_VIF                6
#define SAMSUNG_SI2176                  7   //NOT Mstar VIF
//------------------------------------------------------------------------------------
// IR_TYPE_SEL
//------------------------------------------------------------------------------------
#define IR_TYPE_OLD                 0
#define IR_TYPE_NEW                 1
#define IR_TYPE_MSTAR_DTV           2
#define IR_TYPE_MSTAR_RAW           3
#define IR_TYPE_MSTAR_SZ1           4
#define IR_TYPE_RC_V16              5
#define IR_TYPE_CUS03_DTV           6
#define IR_TYPE_CUS4                7
#define IR_TYPE_DC_LWB1             8
#define IR_TYPE_DC_BN59             9
#define IR_TYPE_P_DTV               10
#define IR_TYPE_SZ_CTV1             11
#define IR_TYPE_SZ_CHO1             12
#define IR_TYPE_SZ_ALC1             13
#define IR_TYPE_SZ_TON1             14
#define IR_TYPE_SZ_KON1             15
#define IR_TYPE_SZ_KON2             16
#define IR_TYPE_SZ_MTC1             17
#define IR_TYPE_SZ_HAI1             18
#define IR_TYPE_SZ_PRI1             19
#define IR_TYPE_SZ_TEN              20
#define IR_TYPE_CUS21SH             21
#define IR_TYPE_DC_BN59_611         22
#define IR_TYPE_CUS30_BK            23
#define IR_TYPE_TPV_AOC             24
#define IR_TYPE_JEAN_RC5            25
#define IR_TYPE_HYF_51F             26
#define IR_TYPE_HIS_NEC             27
#define IR_TYPE_MSTAR_FANTASY       28
#define IR_TYPE_HIS_NEW             29//for Hisense 6I78
#define IR_TYPE_TCL_RCA             30//for tcl 6I98
#define IR_TYPE_HAIER_TOSHIBA       31
#define IR_TYPE_SKY_TOSHIBA         32// for skyworth toshiba
#define IR_TYPE_HIS_NEC_309         33
#define IR_TYPE_CUS_KITKING         34

#define IR_TYPE_CUS_DCLWB1          40
#define IR_TYPE_CUS_RC260I          41
#define IR_TYPE_CUS_WDE             42
#define IR_TYPE_CUS_SZ              43
#define IR_TYPE_CUS_SK              44
#define IR_TYPE_J_DTV               45
#define IR_TYPE_CUS_RC260D          46
#define IR_TYPE_J_RC5               47
#define IR_TYPE_CUS_NS_RC01G_09     48
#define IR_TYPE_HISENSE_TEST        49

#define IR_TYPE_SAMPO_RC            50
#define IR_TYPE_SHARP_RC            51
#define IR_TYPE_SAMSUNG_REMOTE      52

//------------------------------------------------------------------------------------
// PANEL_TYPE_SEL
//------------------------------------------------------------------------------------
#define PNL_DAC_720X480I        0
#define PNL_DAC_720X480P        1
#define PNL_DAC_720X576I        2
#define PNL_DAC_720X576P        3
#define PNL_DAC_720X833I        4
#define PNL_DAC_1024X768P       5
#define PNL_DAC_1920X1080       6
#define PNL_AU17_EN05_SXGA      7
#define PNL_AU20_VGA            8
#define PNL_AU20_SVGA           9
#define PNL_AU20_UXGA           10
#define PNL_CMO19_SXGA          11
#define PNL_CMO20_VGA           12
#define PNL_CMO27_WXGA          13
#define PNL_CMO29_WXGA          14
#define PNL_CMO32_WXGA          15
#define PNL_FU17_FLC43_WXGA     16
#define PNL_HAN23_HSD230WX01A   17
#define PNL_LG17_SXGA           18
#define PNL_LG19_SXGA           19
#define PNL_LG17_LC171_WXGA     20
#define PNL_LG20_UXGA           21
#define PNL_LG23_LC230_WXGA     22
#define PNL_LG26_WXGA           23
#define PNL_LG30_LC300_WXGA     24
#define PNL_QDI17_EL07_SXGA     25
#define PNL_SEC_LTM170W1_L01    26
#define PNL_SH19_LQ197_VGA      27
#define PNL_SH20_B7B_UXGA       28
#define PNL_SAMSUNG24_WUXGA     29
#define PNL_CMO37_WUXGA         30
#define PNL_AU26_T260XW01_WXGA  31
#define PNL_AU20_M201EW01_WSXGA 32
#define PNL_LG32_WXGA           33
#define PNL_SAMSUNG21_WSXGA     34
#define PNL_LG20_VGA            35
#define PNL_HSD260WX11_A        36
#define PNL_AU10_2_DT           37
#define PNL_CPT20_VGA           38
#define PNL_PVI10_VGA           39
#define PNL_CMO20_WXGA          40
#define PNL_CPT15_XGA           41
#define PNL_PANASONIC22_WVGA    42
#define PNL_TMD133_WXGA         43
#define PNL_HANNS96_SVGA        44
#define PNL_HANNS12_VGA         45
#define PNL_LG15_XGA            46
#define PNL_SHARP08_D           47
#define PNL_TMD12_SVGA          48
#define PNL_AU17_WXGA           49
#define PNL_AU17_EG01_SXGA      50
#define PNL_CMO19_M190A1_WXGA   51
#define PNL_CPT15_XG09_XGA      52
#define PNL_AU26_T260XW02_WXGA  53
#define PNL_AU19PW01_WXGA       54
#define PNL_SAMSUNG19M2_WXGAL01 55
#define PNL_AU07_AT             56
#define PNL_AU20_T200XW02_WXGA  57
#define PNL_CMO26_V260B1_WXGA   58
#define PNL_AU85_AT             59
#define PNL_CMO22_WSXGA         60
#define PNL_AU23_T230XW01_WXGA  61
#define PNL_CMO42_WUXGA         62
#define PNL_LPL22_LM220WE1_WSXGA 63
#define PNL_LPL19_LM190WX1_WXGA 64
#define PNL_SAMSUNG23_LTA230W2L1_WXGA 65
#define PNL_LPL42_WXGA          66
#define PNL_LG_PDP32F1_WVGA        67
#define PNL_AU37_T370HW01_HD    68
#define PNL_BOE190WG01_WXGA     69
#define PNL_CPT320WF01_WXGA     70
#define PNL_AU154_WXGA           71
#define PNL_SH32_LQ315T3LZ50Z_WXGA 72
#define PNL_SVSVA150XG04TB_XGA  73

#define PNL_CMO16_WXGA          74
#define PNL_CPT22_A01_V2        75
#define PNL_AU37_T370XW01_WXGA  76 // 120HZ
#define PNL_LG42_WXGA           77 // 120HZ
#define PNL_CMO260J2_WUXGA      78
#define PNL_CMO216H1_L01_HD     79
#define PNL_AU32_T315HW02_HD    80

//
#define PNL_DAC_CRT             99

//------------------------------------------------------------------------------------
//KEYPAD_TYPE_SEL
//------------------------------------------------------------------------------------
#define KEYPAD_TYPE_NONE        0   // no keypad
#define KEYPAD_TYPE_ORIG        1   // MStar normal keypad
#define KEYPAD_TYPE_DEMO        2   // MStar demoset keypad
#define KEYPAD_TYPE_CUSTMOER    3   // Customer
#define KEYPAD_TYPE_BOARDDEP    4   // none regular slow ADC keypad
#define KEYPAD_TYPE_HISENSE     5
//------------------------------------------------------------------------------------
//RM_EEPROM_TYPE
//------------------------------------------------------------------------------------
#define RM_TYPE_24C01           0
#define RM_TYPE_24C02           1
#define RM_TYPE_24C04           2
#define RM_TYPE_24C08           3
#define RM_TYPE_24C16           4
#define RM_TYPE_24C32           5
#define RM_TYPE_24C64           6
#define RM_TYPE_24C512          7

//------------------------------------------------------------------------------------
//I2C_IO_EXPANDER_TYPE
//------------------------------------------------------------------------------------
#define I2C_IO_EXPANDER_NONE            0
#define I2C_IO_EXPANDER_PCA9557         1
#define I2C_IO_EXPANDER_PCF8574         2
#define I2C_IO_EXPANDER_MSG1016RC       3

//------------------------------------------------------------------------------------
// SATURN_FLASH_IC
//------------------------------------------------------------------------------------
#define FLASH_IC_INVALID        0x0000
#define FLASH_IC_SST25VF080B    0x0100      // 1M    SST
#define FLASH_IC_SST25VF016B    0x0101      // 2M
#define FLASH_IC_Pm25LV080      0x0200      // 1M    PMC
#define FLASH_IC_Pm25LV016      0x0201      // 2M
#define FLASH_IC_ST25P80_A      0x0300      // 1M    ST
#define FLASH_IC_ST25P16_A      0x0301      // 2M
#define FLASH_IC_STM25P32       0x0302      // 4M
#define FLASH_IC_AT26DF081A     0x0400      // 1M    ATMEL
#define FLASH_IC_AT26DF161      0x0401      // 2M
#define FLASH_IC_AT26DF321      0x0402      // 4M
#define FLASH_IC_MX25L8005      0x0500      // 1M    MXIC
#define FLASH_IC_MX25L1605A     0x0501      // 2M
#define FLASH_IC_MX25L3205D     0x0502      // 4M
#define FLASH_IC_MX25L6405D     0x0503      // 8M
#define FLASH_IC_NX25P80        0x0600      // 1M    NX
#define FLASH_IC_NX25P16        0x0601      // 2M
#define FLASH_IC_W25X80         0x0700      // 1M    WINB
#define FLASH_IC_W25X16         0x0701      // 2M
#define FLASH_IC_W25X32         0x0702      // 4M
#define FLASH_IC_S25FL008A      0x0800      // 1M    SPANSION
#define FLASH_IC_S25FL016A      0x0801      // 2M
#define FLASH_IC_EN25B20T       0x0900      // 2M    EON
#define FLASH_IC_EN25B20B       0x0901      // 2M
#define FLASH_IC_EN25B10T       0x0902      // 1M
#define FLASH_IC_EN25B10B       0x0903      // 1M
#define FLASH_IC_EN25B32B       0x0904      // 4M    (Bottom Boot)
#define FLASH_IC_EN25B64B       0x0905      // 4M
#define FLASH_IC_ESMT_F25L016A  0x0A00      // 2M
// Audio external I2S selection
#define AUDIO_I2S_NONE              0
#define AUDIO_I2S_STA333            1
#define AUDIO_I2S_STA559BW          2
#define AUDIO_I2S_TAS5706           3
#define AUDIO_I2S_TAS5707           4
#define AUDIO_I2S_TAS5747           5
#define AUDIO_I2S_RT9113B 6
// HDMI Switch selection
#define HDMI_SWITCH_NONE            0
#define HDMI_SWITCH_PS321           1
#define HDMI_SWITCH_SIL9185         2
#define HDMI_SWITCH_TDA19998      3

//------------------------------------------------------------------------------------
// MHL IC
//------------------------------------------------------------------------------------
#define MHL_TYPE_NONE                   0x00
#define MHL_TYPE_INTERNAL               0x10
#define MHL_TYPE_ELAND                  0x20
#define MHL_TYPE_SI                     0x30    //Reserved
#define MHL_TYPE_SiI1292                0x31

#define MHL_VBUS_DEFAULT_MODE           0
#define MHL_VBUS_OUTPUT_MODE            1
#define MHL_VBUS_OUTPUT_INVERSE_MODE   2

#define MHL_VBUS_SWITCH_PIN_INPUT                  0
#define MHL_VBUS_SWITCH_PIN_OUTPUT_LOW_ENABLE     1
#define MHL_VBUS_SWITCH_PIN_OUTPUT_HIGH_ENABLE    2

#endif
