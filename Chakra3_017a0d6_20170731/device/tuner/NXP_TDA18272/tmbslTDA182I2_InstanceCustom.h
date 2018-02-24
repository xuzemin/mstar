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
 * \file          tmbslTDA182I2_InstanceCustom.h
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

#ifndef _TMBSL_TDA182I2_INSTANCE_CUSTOM_H
#define _TMBSL_TDA182I2_INSTANCE_CUSTOM_H


#ifdef __cplusplus
extern "C"
{
#endif

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/

/* Driver settings version definition */
#define TMBSL_TDA182I2_SETTINGS_CUSTOMER_NUM    0  /* SW Settings Customer Number */
#define TMBSL_TDA182I2_SETTINGS_PROJECT_NUM     0  /* SW Settings Project Number  */
#define TMBSL_TDA182I2_SETTINGS_MAJOR_VER       0  /* SW Settings Major Version   */
#define TMBSL_TDA182I2_SETTINGS_MINOR_VER       0  /* SW Settings Minor Version   */

/* Custom Driver Instance Parameters: (Path 0) */
#define TMBSL_TDA182I2_INSTANCE_CUSTOM_MASTER                                                 \
        tmTDA182I2_PowerStandbyWithXtalOn,                      /* Current Power state */               \
        tmTDA182I2_PowerStandbyWithXtalOn,                      /* Minimum Power state */               \
        0,                                                      /* RF */               \
        tmTDA182I2_DVBT_8MHz,                                   /* Standard mode */               \
        True,                                                   /* Master */   \
        0,                                                      /* LT_Enable */    \
        1,                                                      /* PSM_AGC1 */        \
        0,                                                      /* AGC1_6_15dB */            \

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_MASTER_DIGITAL                                           \
        tmTDA182I2_PowerStandbyWithXtalOn,                      /* Current Power state */               \
        tmTDA182I2_PowerStandbyWithLNAOnAndWithXtalOnAndSynthe, /* Minimum Power state */               \
        0,                                                      /* RF */               \
        tmTDA182I2_DVBT_8MHz,                                   /* Standard mode */               \
        True,                                                   /* Master */   \
        1,                                                      /* LT_Enable */    \
        0,                                                      /* PSM_AGC1 */        \
        1,                                                      /* AGC1_6_15dB */            \

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_SLAVE                                                                 \
        tmTDA182I2_PowerStandbyWithXtalOn,                      /* Current Power state */               \
        tmTDA182I2_PowerStandbyWithXtalOn,                      /* Minimum Power state */               \
        0,                                                      /* RF */               \
        tmTDA182I2_DVBT_8MHz,                                   /* Standard mode */               \
        False,                                                  /* Master */   \
        0,                                                      /* LT_Enable */    \
        1,                                                      /* PSM_AGC1 */        \
        0,                                                      /* AGC1_6_15dB */            \

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_SLAVE_DIGITAL                                                                 \
        tmTDA182I2_PowerStandbyWithXtalOn,                      /* Current Power state */               \
        tmTDA182I2_PowerStandbyWithXtalOn,                      /* Minimum Power state */               \
        0,                                                      /* RF */               \
        tmTDA182I2_DVBT_8MHz,                                   /* Standard mode */               \
        False,                                                  /* Master */   \
        0,                                                      /* LT_Enable */    \
        1,                                                      /* PSM_AGC1 */        \
        0,                                                      /* AGC1_6_15dB */            \

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL                                                                 \
            {   /* Std_Array */                                 /* DVB-T 6MHz */               \
                3250000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_6MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_0_5Vpp_min_12_18dB,         /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_0_4MHz,                       /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_102dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Enabled,                  /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_2_Step,               /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Enabled,              /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Enabled,            /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* DVB-T 7MHz */               \
                3500000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_7MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_min_8pc,                   /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_0_5Vpp_min_12_18dB,         /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_102dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Enabled,                  /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_2_Step,               /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Enabled,              /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Enabled,            /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* DVB-T 8MHz */               \
                4000000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_8MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_0_5Vpp_min_12_18dB,         /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_0_4MHz,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_102dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Enabled,                  /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_2_Step,               /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Enabled,              /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Enabled,            /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* QAM 6MHz */               \
                3600000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_6MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_min_8pc,                   /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1Vpp_min_6_24dB,         /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,               /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				TRUE,											/* AGC1_freeze */ \
				TRUE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* QAM 8MHz */               \
                5000000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_9MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_min_8pc,                   /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1Vpp_min_6_24dB,         /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_0_85MHz,                      /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,               /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				TRUE,											/* AGC1_freeze */ \
				TRUE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* ISDBT 6MHz */               \
                3250000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_6MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_0_6Vpp_min_10_3_19_7dB,  /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_0_4MHz,                       /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_102dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Enabled,                  /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_2_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Enabled,              /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Enabled,            /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* ATSC 6MHz */               \
                3250000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_6MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_0_6Vpp_min_10_3_19_7dB,  /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_0_4MHz,                       /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d100_u94dBuV,           /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_104dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_104dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d112_u107dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d112_u107dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Enabled,                  /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_3_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Enabled,              /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Enabled,            /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* DMB-T 8MHz */               \
                4000000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_8MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1Vpp_min_6_24dB,         /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_102dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Enabled,                  /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_2_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Enabled,              /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Enabled,            /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            
 #define  TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_ANALOG                                          \
            {                                                   /* Analog M/N */               \
                5400000,                                        /* IF */               \
                1750000,                                        /* CF_Offset */               \
                tmTDA182I2_LPF_6MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1_25Vpp_min_4_26dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Disabled,                   /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Enabled,           /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,          /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* Analog B */               \
                6400000,                                        /* IF */               \
                2250000,                                       /* CF_Offset */               \
                tmTDA182I2_LPF_7MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1_25Vpp_min_4_26dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Disabled,                   /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band*/               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Enabled,           /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* Analog G/H */               \
                6750000,                                        /* IF */               \
                2750000,                                        /* CF_Offset */               \
                tmTDA182I2_LPF_8MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1_25Vpp_min_4_26dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Disabled,                   /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Enabled,           /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,          /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* Analog I */               \
                7250000,                                        /* IF */               \
                2750000,                                        /* CF_Offset */               \
                tmTDA182I2_LPF_8MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1_25Vpp_min_4_26dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Disabled,                   /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Enabled,           /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* Analog D/K */               \
                6850000,                                        /* IF */               \
                2750000,                                       /* CF_Offset */               \
                tmTDA182I2_LPF_8MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1_25Vpp_min_4_26dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Disabled,                   /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Enabled,           /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,          /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* Analog L */               \
                6750000,                                        /* IF */               \
                2750000,                                       /* CF_Offset */               \
                tmTDA182I2_LPF_8MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1Vpp_min_6_24dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Disabled,                   /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Enabled,           /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_8_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* Analog L' */               \
                1250000,                                       /* IF */               \
                -2750000,                                       /* CF_Offset */               \
                tmTDA182I2_LPF_8MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1Vpp_min_6_24dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Disabled,                   /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_8_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* Analog FM Radio */               \
                1250000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_1_5MHz,                          /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1_25Vpp_min_4_26dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_0_85MHz,                      /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* Blind Scanning copy of PAL-I */               \
                7250000,                                       /* IF */               \
                2750000,                                        /* CF_Offset */               \
                tmTDA182I2_LPF_8MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1_25Vpp_min_4_26dB,       /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Disabled,                   /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Disabled,                   /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,              /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Enabled,           /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Disabled,                 /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_0_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Disabled,             /* AGC5_Atten_3dB */               \
                tmTDA182I2_2_ms,          /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Disabled,           /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Frozen,                     /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            },               \
            {                                                   /* ScanXpress */               \
                5000000,                                        /* IF */               \
                0,                                              /* CF_Offset */               \
                tmTDA182I2_LPF_9MHz,                            /* LPF */               \
                tmTDA182I2_LPFOffset_0pc,                       /* LPF_Offset */               \
                tmTDA182I2_IF_AGC_Gain_1Vpp_min_6_24dB,         /* IF_Gain */               \
                tmTDA182I2_IF_Notch_Enabled,                    /* IF_Notch */               \
                tmTDA182I2_IF_HPF_Disabled,                     /* IF_HPF */               \
                tmTDA182I2_DC_Notch_Enabled,                    /* DC_Notch */               \
                tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV,            /* AGC1_LNA_TOP */               \
                tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,  /* AGC2_RF_Attenuator_TOP */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,             /* AGC3_RF_AGC_TOP_Low_band */               \
                tmTDA182I2_AGC3_RF_AGC_TOP_102dBuV,             /* AGC3_RF_AGC_TOP_High_band */               \
                tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,     /* AGC4_IR_Mixer_TOP */               \
                tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,       /* AGC5_IF_AGC_TOP */               \
                tmTDA182I2_AGC5_Detector_HPF_Disabled,          /* AGC5_Detector_HPF */               \
                tmTDA182I2_AGC3_Adapt_Enabled,                  /* AGC3_Adapt */               \
                tmTDA182I2_AGC3_Adapt_TOP_2_Step,        /* AGC3_Adapt_TOP */               \
                tmTDA182I2_AGC5_Atten_3dB_Enabled,              /* AGC5_Atten_3dB */               \
                tmTDA182I2_scanxpress_mode,                                           /* GSK : settings V2.0.0  */               \
                tmTDA182I2_H3H5_VHF_Filter6_Enabled,            /* H3H5_VHF_Filter6 */               \
                tmTDA182I2_LPF_Gain_Free,                       /* LPF_Gain */               \
				FALSE,											/* AGC1_freeze */ \
				FALSE											/* LTO_STO_immune */ \
            }
/* Custom Driver Instance Parameters: (Path 1) */

/******************************************************************/
/* Mode selection for PATH0                                       */
/******************************************************************/

#ifdef TMBSL_TDA18272

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_MODE_PATH0 TMBSL_TDA182I2_INSTANCE_CUSTOM_MASTER
#define TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL_SELECTION_PATH0 TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL
#define TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_ANALOG_SELECTION_PATH0 TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_ANALOG

#else

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_MODE_PATH0 TMBSL_TDA182I2_INSTANCE_CUSTOM_MASTER_DIGITAL
#define TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL_SELECTION_PATH0 TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL

#endif

/******************************************************************/
/* Mode selection for PATH1                                       */
/******************************************************************/

#ifdef TMBSL_TDA18272

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_MODE_PATH1 TMBSL_TDA182I2_INSTANCE_CUSTOM_SLAVE
#define TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL_SELECTION_PATH1 TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL
#define TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_ANALOG_SELECTION_PATH1 TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_ANALOG

#else

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_MODE_PATH1 TMBSL_TDA182I2_INSTANCE_CUSTOM_SLAVE_DIGITAL

#define TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL_SELECTION_PATH1 TMBSL_TDA182I2_INSTANCE_CUSTOM_STD_DIGITAL

#endif

/******************************************************************/
/* End of Mode selection                                          */
/******************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA182I2_INSTANCE_CUSTOM_H */

