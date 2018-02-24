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
/*
  Copyright (C) 2006-2009 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18273_InstanceCustom.h
 *
 *                1
 *
 * \date          %modify_time%
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                
 *
 * Detailed description may be added here.
 *
 * \section info Change Information
 *
*/

#ifndef _TMBSL_TDA18273_INSTANCE_CUSTOM_H
#define _TMBSL_TDA18273_INSTANCE_CUSTOM_H


#ifdef __cplusplus
extern "C"
{
#endif

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/

/* Driver settings version definition */
#define TMBSL_TDA18273_SETTINGS_COMP_NUM    2  /* SW Settings Compatibility Number */
#define TMBSL_TDA18273_SETTINGS_MAJOR_VER   0  /* SW Settings Major Version  */
#define TMBSL_TDA18273_SETTINGS_MINOR_VER   0  /* SW Settings Minor Version   */

/* Custom Driver Instance Parameters: (Path 0) */
#define TMBSL_TDA18273_INSTANCE_CUSTOM_MASTER                                              \
        tmTDA18273_PowerStandbyWithXtalOn,                      /* Current Power state */  \
        tmTDA18273_PowerStandbyWithXtalOn,                      /* Minimum Power state */  \
        0,                                                      /* RF */                   \
        tmTDA18273_DVBT_8MHz,                                   /* Standard mode */        \

#define TMBSL_TDA18273_INSTANCE_CUSTOM_MASTER_DIGITAL                                      \
        tmTDA18273_PowerStandbyWithXtalOn,                      /* Current Power state */  \
        tmTDA18273_PowerStandbyWithXtalOn,                      /* Minimum Power state */  \
        0,                                                      /* RF */                   \
        tmTDA18273_DVBT_8MHz,                                   /* Standard mode */        \

#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL0                                                              \
            {   /* Std_Array */                                         /* QAM 6MHz */                          \
                3600000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_6MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_min_8pc,                           /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                             /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                           /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                       /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89wdBuV,             /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_WIDE,                    /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_94dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_NO_TOP_ADAPT,                      /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_0_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_0_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                       /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,             /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                       /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* QAM 8MHz */                          \
                5000000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_9MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_min_8pc,                           /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_0_85MHz,                              /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                           /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                      /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89wdBuV,             /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_WIDE,                    /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_NO_TOP_ADAPT,                      /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_0_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_0_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                       /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,             /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                       /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* ATSC */                              \
                3250000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_6MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                               /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_0_4MHz,                               /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Enabled,                            /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                      /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d100_u94dBuV,             /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT,                         /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_104dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_104dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d112_u107dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d112_u107dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT35,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_3_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_3_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Enabled,                        /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_0_6Vpp_min_10_3_19_7dB,      /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_3dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Enabled,                        /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* ISDB-T */                            \
                3250000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_6MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                               /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_0_4MHz,                               /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Enabled,                            /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                      /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,              /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT,                         /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT35,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Enabled,                        /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_0_6Vpp_min_10_3_19_7dB,      /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Enabled,                        /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* DVB-T/T2 1.7MHz */                   \
                850000,                                                 /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_1_5MHz,                                  /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                               /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Disabled,                    /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                             /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                           /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                       /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,              /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT,                         /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT35,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Enabled,                        /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,             /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Enabled,                        /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* DVB-T/T2 6MHz */                     \
                3250000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_6MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                               /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_0_4MHz,                               /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Enabled,                            /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                      /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,              /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT,                         /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT35,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Enabled,                        /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,             /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Enabled,                        /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },    	\

           #define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL1  						\
            {   /* Std_Array */                                         /* DVB-T/T2 7MHz */                     \
                4500000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_8MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_min_12pc,                           /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_1_5MHz,                             /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Enabled,                            /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                      /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,              /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT,                         /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT35,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Enabled,                        /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_0_8Vpp_min_8_22dB,             /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Enabled,                     /* VHF III Mode */  \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* DVB-T/T2 8MHz */                     \
                4800000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_9MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_min_8pc,                               /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_1_5MHz,                             /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                            /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                      /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,              /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT,                         /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_94dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT35,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Enabled,                        /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_0_8Vpp_min_8_22dB,           /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Enabled,                        /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* DVB-T/T2 10MHz */                    \
                5000000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_9MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                               /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                             /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                           /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                       /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,              /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT,                         /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT35,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Enabled,                        /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,             /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Enabled,                        /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* DMB-T */                             \
                4000000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
			   tmTDA18273_LPF_7MHz, 								   /* LPF */							   \
			   tmTDA18273_LPFOffset_0pc,							   /* LPF_Offset */ 					   \
			   tmTDA18273_DC_Notch_IF_PPF_Enabled,					   /* DC notch IF PPF */				   \
			   tmTDA18273_IF_HPF_0_85MHz,							   /* Hi Pass */						   \
			   tmTDA18273_IF_Notch_Enabled, 						   /* IF notch */						   \
			   tmTDA18273_IFnotchToRSSI_Disabled,					   /* IF notch To RSSI */				   \
			   tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,			   /* AGC1 TOP I2C DN/UP */ 			   \
			   tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,				   /* AGC1 Adapt TOP DN/UP */			   \
			   tmTDA18273_AGC1_Mode_LNA_ADAPT,						   /* AGC1 mode */						   \
			   tmTDA18273_Range_LNA_Adapt_20dB_11dB,				   /* Range LNA Adapt */				   \
			   tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB, 	   /* LNA Adapt RFAGC Gv Threshold */	   \
			   tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
			   tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,				   /* AGC2 TOP DN/UP */ 				   \
			   tmTDA18273_AGC3_TOP_I2C_100dBuV, 					   /* AGC3 TOP I2C Low Band */			   \
			   tmTDA18273_AGC3_TOP_I2C_100dBuV, 					   /* AGC3 TOP I2C High Band */ 		   \
			   tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV, 			   /* AGC4 TOP DN/UP */ 				   \
			   tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV, 			   /* AGC5 TOP DN/UP */ 				   \
			   tmTDA18273_Top_Adapt_TOP_ADAPT35,					   /* AGC3 TOP Adapt Algorithm */		   \
			   tmTDA18273_AGC3_Adapt_TOP_2_Step,					   /* AGC3 Adapt TOP Low Band */		   \
			   tmTDA18273_AGC3_Adapt_TOP_2_Step,					   /* AGC3 Adapt TOP High Band */		   \
			   tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP	*/				   \
			   tmTDA18273_TH_AGC_Adapt34_5dB,						   /* Adapt TOP 34 Gain Threshold */	   \
			   tmTDA18273_RF_Atten_3dB_Enabled, 					   /* RF Atten 3dB */					   \
			   tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,			   /* IF Output Level */				   \
			   tmTDA18273_S2D_Gain_6dB, 							   /* S2D Gain */						   \
			   tmTDA18273_Negative_Modulation_Disabled, 			   /* Negative Modulation */			   \
			   tmTDA18273_AGCK_Steps_0_2dB, 						   /* Step */							   \
			   tmTDA18273_AGCK_Time_Constant_32_768ms,				   /* AGCK Time Constant */ 			   \
			   tmTDA18273_AGC5_HPF_Disabled,						   /* AGC5 HPF */						   \
			   tmTDA18273_Pulse_Shaper_Disable_Enabled, 			   /* Pulse Shaper Disable */			   \
			   tmTDA18273_VHF_III_Mode_Enabled, 					   /* VHF III Mode */					   \
			   tmTDA18273_LO_CP_Current_Enabled 					   /* LO CP Current */					   \
		   },																								   \
            {   /* Std_Array */                                         /* DMB-T 8M*/                             \
                4000000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_8MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                               /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                             /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Enabled,                            /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                      /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,              /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT,                         /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT35,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_2_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Enabled,                        /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,             /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Enabled,                        /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                  \

#define  TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG0                                                              \
            {   /* Std_Array */                                         /* FM */                                \
                1250000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_1_5MHz,                                  /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                               /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_0_85MHz,                              /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                           /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                      /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,              /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,               /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                         /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                         /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                       /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                       /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_0_8Vpp_min_8_22dB,           /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                       /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            },                                                                                                      \
            {   /* Std_Array */                                             /* NTSC M/N */                          \
                5400000,                                                    /* IF */                                \
                1750000,                                                    /* CF_Offset */                         \
                tmTDA18273_LPF_6MHz,                                        /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                                   /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Disabled,                        /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                                 /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                               /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                           /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                  /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                     /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,            /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,       /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                      /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                    /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                    /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                           /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,        /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                              /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                           /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,               /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                    /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Enabled,                     /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                                /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_8_192ms,/* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Enabled,                                /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                    /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                           /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                            /* LO CP Current */                     \
            },                                                                                                      \
            {   /* Std_Array */                                             /* PAL B */                             \
                6400000,                                                    /* IF */                                \
                2250000,                                                    /* CF_Offset */                         \
                tmTDA18273_LPF_7MHz,                                        /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                                   /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Disabled,                        /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                                 /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                               /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                           /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                  /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                     /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,            /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,       /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                      /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                    /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                    /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                           /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,        /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                              /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                           /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,               /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                    /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Enabled,                     /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                                /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_8_192ms,/* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Enabled,                                /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                    /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                           /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                            /* LO CP Current */                     \
            },                                                                                                      \
            {   /* Std_Array */                                             /* PAL G/H */                           \
                6750000,                                                    /* IF */                                \
                2750000,                                                    /* CF_Offset */                         \
                tmTDA18273_LPF_8MHz,                                        /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                                   /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Disabled,                        /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                                 /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                               /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                           /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                  /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                     /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,            /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,       /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                      /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                    /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                    /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                           /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,        /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                              /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                           /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,               /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                    /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Enabled,                     /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                                /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_8_192ms,/* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Enabled,                                /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                    /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                           /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                            /* LO CP Current */                     \
            },                                                                                                      \
            {   /* Std_Array */                                             /* PAL I */                             \
                7250000,                                                    /* IF */                                \
                2750000,                                                    /* CF_Offset */                         \
                tmTDA18273_LPF_8MHz,                                        /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                                   /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Disabled,                        /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                                 /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                               /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                           /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                  /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                     /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,            /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,       /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                      /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                    /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                    /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                           /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,        /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                              /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                           /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,               /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                    /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Enabled,                     /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                                /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_8_192ms,/* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Enabled,                                /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                    /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                           /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                            /* LO CP Current */                     \
            },                                                                                                      \
            {   /* Std_Array */                                             /* SECAM D/K */                         \
                7850000,/*6850000,*/                                                    /* IF */                                \
                2750000,                                                    /* CF_Offset */                         \
                tmTDA18273_LPF_9MHz,/*tmTDA18273_LPF_8MHz,*/                                        /* LPF */                               \
                tmTDA18273_LPFOffset_min_8pc,/*tmTDA18273_LPFOffset_0pc,*/                                   /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,/*tmTDA18273_DC_Notch_IF_PPF_Disabled,*/                        /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                                 /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,/*tmTDA18273_IF_Notch_Enabled,*/                                /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                          /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                  /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                     /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,            /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,       /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                      /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                    /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                    /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                           /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,        /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                              /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                           /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,               /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                    /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Enabled,                     /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                                /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_8_192ms,/* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Enabled,                                /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                    /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                           /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                            /* LO CP Current */                     \
            },                                                                                                      \

	#define  TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG1					\
            {   /* Std_Array */                                             /* SECAM L */                           \
                6750000,                                                    /* IF */                                \
                2750000,                                                    /* CF_Offset */                         \
                tmTDA18273_LPF_8MHz,                                        /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                                   /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Disabled,                        /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                                 /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Enabled,                                /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Disabled,                          /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                  /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                     /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,            /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,       /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                      /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                    /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                    /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                           /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_6_min_9,            /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                              /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                           /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,               /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                    /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                    /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                                /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_8_192ms,/* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Enabled,                                /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                    /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                           /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                            /* LO CP Current */                     \
            },                                                                                                      \
            {   /* Std_Array */                                             /* SECAM L' */                          \
                1250000,                                                    /* IF */                                \
                -2750000,                                                   /* CF_Offset */                         \
                tmTDA18273_LPF_8MHz,                                        /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                                   /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Disabled,                        /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                                 /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                               /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                           /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                  /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                     /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,            /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,       /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                      /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                    /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                    /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                           /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_6_min_9,            /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                              /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                           /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,               /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                    /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                    /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                                /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_8_192ms,/* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                               /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                    /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                           /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                            /* LO CP Current */                     \
            },                                                                                                      \
            {   /* Std_Array */                                             /* Blind Scanning copy of PAL-I */      \
                7250000,                                                    /* IF */                                \
                2750000,                                                    /* CF_Offset */                         \
                tmTDA18273_LPF_8MHz,                                        /* LPF */                               \
                tmTDA18273_LPFOffset_0pc,                                   /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Disabled,                        /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_Disabled,                                 /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                               /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                           /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                  /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,                     /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,            /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,       /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                      /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_96dBuV,                             /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,                    /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,                    /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_TOP_ADAPT34,                           /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_1_Step,                           /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,        /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                              /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                           /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,               /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                    /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                    /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                                /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_8_192ms,/* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Enabled,                                /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                    /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                           /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                            /* LO CP Current */                     \
            },                                                                                                  \
            {   /* Std_Array */                                         /* ScanXpress */                        \
                5000000,                                                /* IF */                                \
                0,                                                      /* CF_Offset */                         \
                tmTDA18273_LPF_9MHz,                                    /* LPF */                               \
                tmTDA18273_LPFOffset_min_8pc,                           /* LPF_Offset */                        \
                tmTDA18273_DC_Notch_IF_PPF_Enabled,                     /* DC notch IF PPF */                   \
                tmTDA18273_IF_HPF_0_85MHz,                              /* Hi Pass */                           \
                tmTDA18273_IF_Notch_Disabled,                           /* IF notch */                          \
                tmTDA18273_IFnotchToRSSI_Enabled,                       /* IF notch To RSSI */                  \
                tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89wdBuV,             /* AGC1 TOP I2C DN/UP */                \
                tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step,                 /* AGC1 Adapt TOP DN/UP */              \
                tmTDA18273_AGC1_Mode_LNA_ADAPT_WIDE,                    /* AGC1 mode */                         \
                tmTDA18273_Range_LNA_Adapt_20dB_11dB,                   /* Range LNA Adapt */                   \
                tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB,        /* LNA Adapt RFAGC Gv Threshold */      \
                tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB,   /* AGC1 TOP Adapt RFAGC Gv Threshold */ \
                tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,                  /* AGC2 TOP DN/UP */                    \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C Low Band */             \
                tmTDA18273_AGC3_TOP_I2C_100dBuV,                        /* AGC3 TOP I2C High Band */            \
                tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,                /* AGC4 TOP DN/UP */                    \
                tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,                /* AGC5 TOP DN/UP */                    \
                tmTDA18273_Top_Adapt_NO_TOP_ADAPT,                      /* AGC3 TOP Adapt Algorithm */          \
                tmTDA18273_AGC3_Adapt_TOP_0_Step,                       /* AGC3 Adapt TOP Low Band */           \
                tmTDA18273_AGC3_Adapt_TOP_0_Step,                       /* AGC3 Adapt TOP High Band */          \
                tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,    /* AGC Overload TOP  */                 \
                tmTDA18273_TH_AGC_Adapt34_5dB,                          /* Adapt TOP 34 Gain Threshold */       \
                tmTDA18273_RF_Atten_3dB_Disabled,                       /* RF Atten 3dB */                      \
                tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,             /* IF Output Level */                   \
                tmTDA18273_S2D_Gain_6dB,                                /* S2D Gain */                          \
                tmTDA18273_Negative_Modulation_Disabled,                /* Negative Modulation */               \
                tmTDA18273_AGCK_Steps_0_2dB,                            /* Step */                              \
                tmTDA18273_AGCK_Time_Constant_32_768ms,                 /* AGCK Time Constant */                \
                tmTDA18273_AGC5_HPF_Disabled,                           /* AGC5 HPF */                          \
                tmTDA18273_Pulse_Shaper_Disable_Enabled,                /* Pulse Shaper Disable */              \
                tmTDA18273_VHF_III_Mode_Disabled,                       /* VHF III Mode */                      \
                tmTDA18273_LO_CP_Current_Enabled                        /* LO CP Current */                     \
            }                                                                                                   \

/* Custom Driver Instance Parameters: (Path 1) */

/******************************************************************/
/* Mode selection for PATH0                                       */
/******************************************************************/

#define TMBSL_TDA18273_INSTANCE_CUSTOM_MODE_PATH0 TMBSL_TDA18273_INSTANCE_CUSTOM_MASTER
#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL_SELECTION1_PATH0 TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL0
#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL_SELECTION2_PATH0 TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL1
#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG_SELECTION1_PATH0 TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG0
#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG_SELECTION2_PATH0 TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG1

/******************************************************************/
/* Mode selection for PATH1                                       */
/******************************************************************/

#define TMBSL_TDA18273_INSTANCE_CUSTOM_MODE_PATH1 TMBSL_TDA18273_INSTANCE_CUSTOM_MASTER
#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL_SELECTION1_PATH1 TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL0
#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL_SELECTION2_PATH1 TMBSL_TDA18273_INSTANCE_CUSTOM_STD_DIGITAL1
#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG_SELECTION1_PATH1 TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG0
#define TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG_SELECTION2_PATH1 TMBSL_TDA18273_INSTANCE_CUSTOM_STD_ANALOG1

/******************************************************************/
/* End of Mode selection                                          */
/******************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA18273_INSTANCE_CUSTOM_H */
