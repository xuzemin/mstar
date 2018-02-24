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
/**
Copyright (C) 2008 NXP B.V., All Rights Reserved.
This source code and any compilation or derivative thereof is the proprietary
information of NXP B.V. and is confidential in nature. Under no circumstances
is this software to be  exposed to or placed under an Open Source License of
any type without the expressed written permission of NXP B.V.
*
* \file          tmbslTDA18272.h
*                %version: 21 %
*
* \date          %date_modified%
*
* \brief         Describe briefly the purpose of this file.
*
* REFERENCE DOCUMENTS :
*
* Detailed description may be added here.
*
* \section info Change Information
*
* \verbatim
Date          Modified by CRPRNr  TASKNr  Maintenance description
-------------|-----------|-------|-------|-----------------------------------
|            |           |       |
-------------|-----------|-------|-------|-----------------------------------
|            |           |       |
-------------|-----------|-------|-------|-----------------------------------
\endverbatim
*
*/

#ifndef _TMBSL_TDA18272_H
#define _TMBSL_TDA18272_H

/*------------------------------------------------------------------------------*/
/* Standard include files:                                                      */
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/* Project include files:                                                       */
/*------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

    /*------------------------------------------------------------------------------*/
    /* Types and defines:                                                           */
    /*------------------------------------------------------------------------------*/

    /* SW Error codes */
#define TDA182I2_ERR_BASE               (CID_COMP_TUNER | CID_LAYER_BSL)
#define TDA182I2_ERR_COMP               (CID_COMP_TUNER | CID_LAYER_BSL | TM_ERR_COMP_UNIQUE_START)

#define TDA182I2_ERR_BAD_UNIT_NUMBER    (TDA182I2_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define TDA182I2_ERR_NOT_INITIALIZED    (TDA182I2_ERR_BASE + TM_ERR_NOT_INITIALIZED)
#define TDA182I2_ERR_INIT_FAILED        (TDA182I2_ERR_BASE + TM_ERR_INIT_FAILED)
#define TDA182I2_ERR_BAD_PARAMETER      (TDA182I2_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define TDA182I2_ERR_NOT_SUPPORTED      (TDA182I2_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define TDA182I2_ERR_HW_FAILED          (TDA182I2_ERR_COMP + 0x0001)
#define TDA182I2_ERR_NOT_READY          (TDA182I2_ERR_COMP + 0x0002)
#define TDA182I2_ERR_BAD_VERSION        (TDA182I2_ERR_COMP + 0x0003)


    typedef enum _tmTDA182I2PowerState_t {
        tmTDA182I2_PowerNormalMode = 0,                                 /* Device normal mode */
        tmTDA182I2_PowerStandbyWithLNAOnAndWithXtalOnAndSynthe,         /* Device standby mode with LNA and Xtal Output and Synthe */
        tmTDA182I2_PowerStandbyWithLNAOnAndWithXtalOn,                  /* Device standby mode with LNA and Xtal Output */
        tmTDA182I2_PowerStandbyWithXtalOn,                              /* Device standby mode with Xtal Output */
        tmTDA182I2_PowerStandby,                                        /* Device standby mode */
        tmTDA182I2_PowerMax
    } tmTDA182I2PowerState_t, *ptmTDA182I2PowerState_t;

    typedef enum _tmTDA182I2StandardMode_t {
        tmTDA182I2_DVBT_6MHz = 0,                       /* Digital TV DVB-T 6MHz */
        tmTDA182I2_DVBT_7MHz,                           /* Digital TV DVB-T 7MHz */
        tmTDA182I2_DVBT_8MHz,                           /* Digital TV DVB-T 8MHz */
        tmTDA182I2_QAM_6MHz,                            /* Digital TV QAM 6MHz */
        tmTDA182I2_QAM_8MHz,                            /* Digital TV QAM 8MHz */
        tmTDA182I2_ISDBT_6MHz,                          /* Digital TV ISDBT 6MHz */
        tmTDA182I2_ATSC_6MHz,                           /* Digital TV ATSC 6MHz */
        tmTDA182I2_DMBT_8MHz,                           /* Digital TV DMB-T 8MHz */
        tmTDA182I2_ANLG_MN,                             /* Analog TV M/N */
        tmTDA182I2_ANLG_B,                              /* Analog TV B */
        tmTDA182I2_ANLG_GH,                             /* Analog TV G/H */
        tmTDA182I2_ANLG_I,                              /* Analog TV I */
        tmTDA182I2_ANLG_DK,                             /* Analog TV D/K */
        tmTDA182I2_ANLG_L,                              /* Analog TV L */
        tmTDA182I2_ANLG_LL,                             /* Analog TV L' */
        tmTDA182I2_FM_Radio,                            /* Analog FM Radio */
        tmTDA182I2_Scanning,                            /* analog  preset blind Scanning */
        tmTDA182I2_ScanXpress,                          /* ScanXpress */
        tmTDA182I2_StandardMode_Max
    } tmTDA182I2StandardMode_t, *ptmTDA182I2StandardMode_t;

    typedef enum _tmTDA182I2LPF_t {
        tmTDA182I2_LPF_6MHz = 0,                        /* 6MHz LPFc */
        tmTDA182I2_LPF_7MHz,                            /* 7MHz LPFc */
        tmTDA182I2_LPF_8MHz,                            /* 8MHz LPFc */
        tmTDA182I2_LPF_9MHz,                            /* 9MHz LPFc */
        tmTDA182I2_LPF_1_5MHz,                          /* 1.5MHz LPFc */
        tmTDA182I2_LPF_Max
    } tmTDA182I2LPF_t, *ptmTDA182I2LPF_t;

    typedef enum _tmTDA182I2LPFOffset_t {
        tmTDA182I2_LPFOffset_0pc = 0,                   /* LPFc 0% */
        tmTDA182I2_LPFOffset_min_4pc,                   /* LPFc -4% */
        tmTDA182I2_LPFOffset_min_8pc,                   /* LPFc -8% */
        tmTDA182I2_LPFOffset_min_12pc,                  /* LPFc -12% */
        tmTDA182I2_LPFOffset_Max
    } tmTDA182I2LPFOffset_t, *ptmTDA182I2LPFOffset_t;

    typedef enum _tmTDA182I2IF_AGC_Gain_t {
        tmTDA182I2_IF_AGC_Gain_2Vpp_0_30dB = 0,         /* 2Vpp       0 - 30dB IF AGC Gain */
        tmTDA182I2_IF_AGC_Gain_1_25Vpp_min_4_26dB,      /* 1.25Vpp   -4 - 26dB IF AGC Gain */
        tmTDA182I2_IF_AGC_Gain_1Vpp_min_6_24dB,         /* 1Vpp      -6 - 24dB IF AGC Gain */
        tmTDA182I2_IF_AGC_Gain_0_8Vpp_min_8_22dB,       /* 0.8Vpp    -8 - 22dB IF AGC Gain */
        tmTDA182I2_IF_AGC_Gain_0_85Vpp_min_7_5_22_5dB,  /* 0.85Vpp   -7.5 - 22.5dB IF AGC Gain */
        tmTDA182I2_IF_AGC_Gain_0_7Vpp_min_9_21dB,       /* 0.7Vpp    -9 - 21dB IF AGC Gain */
        tmTDA182I2_IF_AGC_Gain_0_6Vpp_min_10_3_19_7dB,  /* 0.6Vpp    -10.3 - 19.7dB IF AGC Gain */
        tmTDA182I2_IF_AGC_Gain_0_5Vpp_min_12_18dB,      /* 0.5Vpp    -12 - 18dB IF AGC Gain */
        tmTDA182I2_IF_AGC_Gain_Max
    } tmTDA182I2IF_AGC_Gain_t, *ptmTDA182I2IF_AGC_Gain_t;

    typedef enum _tmTDA182I2IF_Notch_t {
        tmTDA182I2_IF_Notch_Disabled = 0,               /* IF Notch Enabled */
        tmTDA182I2_IF_Notch_Enabled,                    /* IF Notch Disabled */
        tmTDA182I2_IF_Notch_Max
    } tmTDA182I2IF_Notch_t, *ptmTDA182I2IF_Notch_t;

    typedef enum _tmTDA182I2IF_HPF_t {
        tmTDA182I2_IF_HPF_Disabled = 0,                 /* IF HPF 0.4MHz */
        tmTDA182I2_IF_HPF_0_4MHz,                       /* IF HPF 0.4MHz */
        tmTDA182I2_IF_HPF_0_85MHz,                      /* IF HPF 0.85MHz */
        tmTDA182I2_IF_HPF_1MHz,                         /* IF HPF 1MHz */
        tmTDA182I2_IF_HPF_1_5MHz,                       /* IF HPF 1.5MHz */
        tmTDA182I2_IF_HPF_Max
    } tmTDA182I2IF_HPF_t, *ptmTDA182I2IF_HPF_t;

    typedef enum _tmTDA182I2DC_Notch_t {
        tmTDA182I2_DC_Notch_Disabled = 0,               /* IF Notch Enabled */
        tmTDA182I2_DC_Notch_Enabled,                    /* IF Notch Disabled */
        tmTDA182I2_DC_Notch_Max
    } tmTDA182I2DC_Notch_t, *ptmTDA182I2DC_Notch_t;

    typedef enum _tmTDA182I2AGC1_LNA_TOP_t {
        tmTDA182I2_AGC1_LNA_TOP_d95_u89dBuV = 0,            /* AGC1 LNA TOP down 95 up 89 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d95_u93dBuV_do_not_use,     /* AGC1 LNA TOP down 95 up 93 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d95_u94dBuV_do_not_use,     /* AGC1 LNA TOP down 95 up 94 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d95_u95dBuV_do_not_use,     /* AGC1 LNA TOP down 95 up 95 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d99_u89dBuV,                /* AGC1 LNA TOP down 99 up 89 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d99_u93dBuV,                /* AGC1 LNA TOP down 95 up 93 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d99_u94dBuV,                /* AGC1 LNA TOP down 99 up 94 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d99_u95dBuV,                /* AGC1 LNA TOP down 99 up 95 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d99_u9SdBuV,                /* AGC1 LNA TOP down 99 up 95 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d100_u93dBuV,               /* AGC1 LNA TOP down 100 up 93 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d100_u94dBuV,               /* AGC1 LNA TOP down 100 up 94 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d100_u95dBuV,               /* AGC1 LNA TOP down 100 up 95 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d100_u9SdBuV,               /* AGC1 LNA TOP down 100 up 95 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d101_u93dBuV,               /* AGC1 LNA TOP down 101 up 93 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d101_u94dBuV,               /* AGC1 LNA TOP down 101 up 94 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d101_u95dBuV,               /* AGC1 LNA TOP down 101 up 95 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_d101_u9SdBuV,               /* AGC1 LNA TOP down 101 up 95 dBuV */
        tmTDA182I2_AGC1_LNA_TOP_Max
    } tmTDA182I2AGC1_LNA_TOP_t, *ptmTDA182I2AGC1_LNA_TOP_t;

    typedef enum _tmTDA182I2AGC2_RF_Attenuator_TOP_t {
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d89_u81dBuV = 0, /* AGC2 RF Attenuator TOP down 89 up 81 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d91_u83dBuV,     /* AGC2 RF Attenuator TOP down 91 up 83 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d93_u85dBuV,     /* AGC2 RF Attenuator TOP down 93 up 85 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d95_u87dBuV,     /* AGC2 RF Attenuator TOP down 95 up 87 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d88_u88dBuV,     /* AGC2 RF Attenuator TOP down 88 up 81 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d89_u82dBuV,     /* AGC2 RF Attenuator TOP down 89 up 82 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u83dBuV,     /* AGC2 RF Attenuator TOP down 90 up 83 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d91_u84dBuV,     /* AGC2 RF Attenuator TOP down 91 up 84 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d92_u85dBuV,     /* AGC2 RF Attenuator TOP down 92 up 85 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d93_u86dBuV,     /* AGC2 RF Attenuator TOP down 93 up 86 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d94_u87dBuV,     /* AGC2 RF Attenuator TOP down 94 up 87 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d95_u88dBuV,     /* AGC2 RF Attenuator TOP down 95 up 88 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d87_u81dBuV,     /* AGC2 RF Attenuator TOP down 87 up 81 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d88_u82dBuV,     /* AGC2 RF Attenuator TOP down 88 up 82 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d89_u83dBuV,     /* AGC2 RF Attenuator TOP down 89 up 83 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d90_u84dBuV,     /* AGC2 RF Attenuator TOP down 90 up 84 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d91_u85dBuV,     /* AGC2 RF Attenuator TOP down 91 up 85 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d92_u86dBuV,     /* AGC2 RF Attenuator TOP down 92 up 86 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d93_u87dBuV,     /* AGC2 RF Attenuator TOP down 93 up 87 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d94_u88dBuV,     /* AGC2 RF Attenuator TOP down 94 up 88 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_d95_u89dBuV,     /* AGC2 RF Attenuator TOP down 95 up 89 dBuV */
        tmTDA182I2_AGC2_RF_Attenuator_TOP_Max
    } tmTDA182I2AGC2_RF_Attenuator_TOP_t, *ptmTDA182I2AGC2_RF_Attenuator_TOP_t;
    
    typedef enum _tmTDA182I2AGC3_RF_AGC_TOP_t {
        tmTDA182I2_AGC3_RF_AGC_TOP_94dBuV = 0, /* AGC3 RF AGC TOP 94 dBuV */
        tmTDA182I2_AGC3_RF_AGC_TOP_96dBuV,     /* AGC3 RF AGC TOP 96 dBuV */
        tmTDA182I2_AGC3_RF_AGC_TOP_98dBuV,     /* AGC3 RF AGC TOP 98 dBuV */
        tmTDA182I2_AGC3_RF_AGC_TOP_100dBuV,    /* AGC3 RF AGC TOP 100 dBuV */
        tmTDA182I2_AGC3_RF_AGC_TOP_102dBuV,    /* AGC3 RF AGC TOP 102 dBuV */
        tmTDA182I2_AGC3_RF_AGC_TOP_104dBuV,    /* AGC3 RF AGC TOP 104 dBuV */
        tmTDA182I2_AGC3_RF_AGC_TOP_106dBuV,    /* AGC3 RF AGC TOP 106 dBuV */
        tmTDA182I2_AGC3_RF_AGC_TOP_107dBuV,    /* AGC3 RF AGC TOP 107 dBuV */
        tmTDA182I2_AGC3_RF_AGC_TOP_Max
    } tmTDA182I2AGC3_RF_AGC_TOP_t, *ptmTDA182I2AGC3_RF_AGC_TOP_t;

#define tmTDA182I2_AGC3_RF_AGC_TOP_FREQ_LIM 291000000

    typedef enum _tmTDA182I2AGC4_IR_Mixer_TOP_t {
        tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u99dBuV = 0,     /* AGC4 IR_Mixer TOP down 105 up 99 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u100dBuV,        /* AGC4 IR_Mixer TOP down 105 up 100 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d105_u101dBuV,        /* AGC4 IR_Mixer TOP down 105 up 101 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d107_u101dBuV,        /* AGC4 IR_Mixer TOP down 107 up 101 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d107_u102dBuV,        /* AGC4 IR_Mixer TOP down 107 up 102 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d107_u103dBuV,        /* AGC4 IR_Mixer TOP down 107 up 103 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d108_u103dBuV,        /* AGC4 IR_Mixer TOP down 108 up 103 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d109_u103dBuV,        /* AGC4 IR_Mixer TOP down 109 up 103 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d109_u104dBuV,        /* AGC4 IR_Mixer TOP down 109 up 104 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d109_u105dBuV,        /* AGC4 IR_Mixer TOP down 109 up 105 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u104dBuV,        /* AGC4 IR_Mixer TOP down 110 up 104 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u105dBuV,        /* AGC4 IR_Mixer TOP down 110 up 105 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d110_u106dBuV,        /* AGC4 IR_Mixer TOP down 110 up 106 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d112_u106dBuV,        /* AGC4 IR_Mixer TOP down 112 up 106 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d112_u107dBuV,        /* AGC4 IR_Mixer TOP down 112 up 107 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_d112_u108dBuV,        /* AGC4 IR_Mixer TOP down 112 up 108 dBuV */
        tmTDA182I2_AGC4_IR_Mixer_TOP_Max
    } tmTDA182I2AGC4_IR_Mixer_TOP_t, *ptmTDA182I2AGC4_IR_Mixer_TOP_t;

    typedef enum _tmTDA182I2AGC5_IF_AGC_TOP_t {
        tmTDA182I2_AGC5_IF_AGC_TOP_d105_u99dBuV = 0,        /* AGC5 IF AGC TOP down 105 up 99 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d105_u100dBuV,           /* AGC5 IF AGC TOP down 105 up 100 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d105_u101dBuV,           /* AGC5 IF AGC TOP down 105 up 101 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d107_u101dBuV,           /* AGC5 IF AGC TOP down 107 up 101 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d107_u102dBuV,           /* AGC5 IF AGC TOP down 107 up 102 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d107_u103dBuV,           /* AGC5 IF AGC TOP down 107 up 103 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d108_u103dBuV,           /* AGC5 IF AGC TOP down 108 up 103 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d109_u103dBuV,           /* AGC5 IF AGC TOP down 109 up 103 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d109_u104dBuV,           /* AGC5 IF AGC TOP down 109 up 104 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d109_u105dBuV,           /* AGC5 IF AGC TOP down 109 up 105 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d110_u104dBuV,           /* AGC5 IF AGC TOP down 108 up 104 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d110_u105dBuV,           /* AGC5 IF AGC TOP down 108 up 105 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d110_u106dBuV,           /* AGC5 IF AGC TOP down 108 up 106 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d112_u106dBuV,           /* AGC5 IF AGC TOP down 108 up 106 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d112_u107dBuV,           /* AGC5 IF AGC TOP down 108 up 107 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_d112_u108dBuV,           /* AGC5 IF AGC TOP down 108 up 108 dBuV */
        tmTDA182I2_AGC5_IF_AGC_TOP_Max
    } tmTDA182I2AGC5_IF_AGC_TOP_t, *ptmTDA182I2AGC5_IF_AGC_TOP_t;

    typedef enum _tmTDA182I2AGC5_Detector_HPF_t {
        tmTDA182I2_AGC5_Detector_HPF_Disabled = 0,          /* AGC5_Detector_HPF Enabled */
        tmTDA182I2_AGC5_Detector_HPF_Enabled,               /* IF Notch Disabled */
        tmTDA182I2_AGC5_Detector_HPF_Max
    } tmTDA182I2AGC5_Detector_HPF_t, *ptmTDA182I2AGC5_Detector_HPFh_t;

    typedef enum _tmTDA182I2AGC3_Adapt_t {
        tmTDA182I2_AGC3_Adapt_Enabled = 0,                  /* AGC3_Adapt Enabled */
        tmTDA182I2_AGC3_Adapt_Disabled,                     /* AGC3_Adapt Disabled */
        tmTDA182I2_AGC3_Adapt_Max
    } tmTDA182I2AGC3_Adapt_t, *ptmTDA182I2AGC3_Adapt_t;

    typedef enum _tmTDA182I2AGC3_Adapt_TOP_t {
        tmTDA182I2_AGC3_Adapt_TOP_0_Step = 0,              /* same level as AGC3 TOP  */
        tmTDA182I2_AGC3_Adapt_TOP_1_Step,                  /* 1 level below AGC3 TOP  */
        tmTDA182I2_AGC3_Adapt_TOP_2_Step,                  /* 2 level below AGC3 TOP  */
        tmTDA182I2_AGC3_Adapt_TOP_3_Step,                  /* 3 level below AGC3 TOP  */
    } tmTDA182I2AGC3_Adapt_TOP_t, *ptmTDA182I2AGC3_Adapt_TOP_t;

    typedef enum _tmTDA182I2AGC5_Atten_3dB_t {
        tmTDA182I2_AGC5_Atten_3dB_Disabled = 0,             /* AGC5_Atten_3dB Disabled */
        tmTDA182I2_AGC5_Atten_3dB_Enabled,                  /* AGC5_Atten_3dB Enabled */
        tmTDA182I2_AGC5_Atten_3dB_Max
    } tmTDA182I2AGC5_Atten_3dB_t, *ptmTDA182I2AGC5_Atten_3dB_t;
	
 typedef enum _tmTDA182I2AGCK_Mode_t {
        tmTDA182I2_1_Step_8_VSYNC_Rising_edge = 0,             /* AGC Time constant 1step/8Vsync */
        tmTDA182I2_1_Step_VSYNC_Rising_edge,                  /* AGC Time constant 1step/Vsync  */
        tmTDA182I2_2_ms,									 /* AGC Time constant 2ms  */
        tmTDA182I2_8_ms,									 /* AGC Time constant 8ms  */
        tmTDA182I2_scanxpress_mode=0x0e
    } tmTDA182I2AGCK_Mode_t, *ptmTDA182I2AGCK_Mode_t;

    typedef enum _tmTDA182I2H3H5_VHF_Filter6_t {
        tmTDA182I2_H3H5_VHF_Filter6_Disabled = 0,           /* H3H5_VHF_Filter6 Disabled */
        tmTDA182I2_H3H5_VHF_Filter6_Enabled,                /* H3H5_VHF_Filter6 Enabled */
        tmTDA182I2_H3H5_VHF_Filter6_Max
    } tmTDA182I2H3H5_VHF_Filter6_t, *ptmTDA182I2H3H5_VHF_Filter6_t;

    typedef enum _tmTDA182I2_LPF_Gain_t {
        tmTDA182I2_LPF_Gain_Unknown = 0,                    /* LPF_Gain Unknown */
        tmTDA182I2_LPF_Gain_Frozen,                         /* LPF_Gain Frozen */
        tmTDA182I2_LPF_Gain_Free                            /* LPF_Gain Free */
    } tmTDA182I2_LPF_Gain_t, *ptmTDA182I2_LPF_Gain_t;

    typedef struct _tmTDA182I2StdCoefficients
    {
        UInt32                              IF;
        Int32                               CF_Offset;
        tmTDA182I2LPF_t                     LPF;
        tmTDA182I2LPFOffset_t               LPF_Offset;
        tmTDA182I2IF_AGC_Gain_t             IF_Gain;
        tmTDA182I2IF_Notch_t                IF_Notch;
        tmTDA182I2IF_HPF_t                  IF_HPF;
        tmTDA182I2DC_Notch_t                DC_Notch;
        tmTDA182I2AGC1_LNA_TOP_t            AGC1_LNA_TOP;
        tmTDA182I2AGC2_RF_Attenuator_TOP_t  AGC2_RF_Attenuator_TOP;
        tmTDA182I2AGC3_RF_AGC_TOP_t         AGC3_RF_AGC_TOP_Low_band;
        tmTDA182I2AGC3_RF_AGC_TOP_t         AGC3_RF_AGC_TOP_High_band;
        tmTDA182I2AGC4_IR_Mixer_TOP_t       AGC4_IR_Mixer_TOP;
        tmTDA182I2AGC5_IF_AGC_TOP_t         AGC5_IF_AGC_TOP;
        tmTDA182I2AGC5_Detector_HPF_t       AGC5_Detector_HPF;
        tmTDA182I2AGC3_Adapt_t              AGC3_Adapt;
        tmTDA182I2AGC3_Adapt_TOP_t          AGC3_Adapt_TOP;
        tmTDA182I2AGC5_Atten_3dB_t          AGC5_Atten_3dB;
        UInt8                               GSK;
        tmTDA182I2H3H5_VHF_Filter6_t        H3H5_VHF_Filter6;
        tmTDA182I2_LPF_Gain_t               LPF_Gain;
		Bool								AGC1_Freeze;
		Bool								LTO_STO_immune;
    } tmTDA182I2StdCoefficients, *ptmTDA182I2StdCoefficients;

    typedef enum _tmTDA182I2RFFilterRobustness_t {
        tmTDA182I2RFFilterRobustness_Low = 0,
        tmTDA182I2RFFilterRobustness_High,
        tmTDA182I2RFFilterRobustness_Error,
        tmTDA182I2RFFilterRobustness_Max
    } tmTDA182I2RFFilterRobustness_t, *ptmTDA182I2RFFilterRobustness_t;

    typedef struct _tmTDA182I2RFFilterRating {
        double                               VHFLow_0_Margin;
        double                               VHFLow_1_Margin;
        double                               VHFHigh_0_Margin;
        double                               VHFHigh_1_Margin;
        double                               UHFLow_0_Margin;
        double                               UHFLow_1_Margin;
        double                               UHFHigh_0_Margin;
        double                               UHFHigh_1_Margin;    
        tmTDA182I2RFFilterRobustness_t      VHFLow_0_RFFilterRobustness;
        tmTDA182I2RFFilterRobustness_t      VHFLow_1_RFFilterRobustness;
        tmTDA182I2RFFilterRobustness_t      VHFHigh_0_RFFilterRobustness;
        tmTDA182I2RFFilterRobustness_t      VHFHigh_1_RFFilterRobustness;
        tmTDA182I2RFFilterRobustness_t      UHFLow_0_RFFilterRobustness;
        tmTDA182I2RFFilterRobustness_t      UHFLow_1_RFFilterRobustness;
        tmTDA182I2RFFilterRobustness_t      UHFHigh_0_RFFilterRobustness;
        tmTDA182I2RFFilterRobustness_t      UHFHigh_1_RFFilterRobustness;
    } tmTDA182I2RFFilterRating, *ptmTDA182I2RFFilterRating;

    tmErrorCode_t
        tmbslTDA182I2Init(
        tmUnitSelect_t              tUnit,      /*  I: Unit number */
        tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
        );
    tmErrorCode_t 
        tmbslTDA182I2DeInit (
        tmUnitSelect_t  tUnit   /*  I: Unit number */
        );
    tmErrorCode_t
        tmbslTDA182I2GetSWVersion (
        ptmSWVersion_t  pSWVersion  /*  I: Receives SW Version */
        );
    tmErrorCode_t
        tmbslTDA182I2CheckHWVersion (
        tmUnitSelect_t tUnit    /* I: Unit number */
        );
    tmErrorCode_t
        tmbslTDA182I2SetPowerState (
        tmUnitSelect_t          tUnit,      /*  I: Unit number */
        tmTDA182I2PowerState_t  powerState  /*  I: Power state of this device */
        );
    tmErrorCode_t
        tmbslTDA182I2GetPowerState (
        tmUnitSelect_t            tUnit,        /*  I: Unit number */
        tmTDA182I2PowerState_t    *pPowerState  /*  O: Power state of this device */
        );
    tmErrorCode_t
        tmbslTDA182I2SetStandardMode (
        tmUnitSelect_t              tUnit,          /*  I: Unit number */
        tmTDA182I2StandardMode_t    StandardMode    /*  I: Standard mode of this device */
        );
    tmErrorCode_t
        tmbslTDA182I2GetStandardMode (
        tmUnitSelect_t              tUnit,          /*  I: Unit number */
        tmTDA182I2StandardMode_t    *pStandardMode  /*  O: Standard mode of this device */
        );
    tmErrorCode_t
        tmbslTDA182I2SetRf(
        tmUnitSelect_t  tUnit,  /*  I: Unit number */
        UInt32          uRF     /*  I: RF frequency in hertz */
        );
    tmErrorCode_t
        tmbslTDA182I2GetRf(
        tmUnitSelect_t  tUnit,  /*  I: Unit number */
        UInt32*         pRF     /*  O: RF frequency in hertz */
        );
    tmErrorCode_t
        tmbslTDA182I2Reset(
        tmUnitSelect_t tUnit    /* I: Unit number */
        );
    tmErrorCode_t
        tmbslTDA182I2GetIF(
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt32*         puIF    /* O: IF Frequency in hertz */
        );
    tmErrorCode_t
        tmbslTDA182I2GetCF_Offset(
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32*         puOffset    /* O: Center frequency offset in hertz */
        );
    tmErrorCode_t
        tmbslTDA182I2GetLockStatus(
        tmUnitSelect_t          tUnit,      /* I: Unit number */
        tmbslFrontEndState_t*   pLockStatus /* O: PLL Lock status */
        );
    tmErrorCode_t
        tmbslTDA182I2GetPowerLevel(
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32*         pPowerLevel /* O: Power Level in dBµV */
        );
    tmErrorCode_t
        tmbslTDA182I2SetIRQWait(
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        Bool            bWait   /* I: Determine if we need to wait IRQ in driver functions */
        );
    tmErrorCode_t
        tmbslTDA182I2GetIRQWait(
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        Bool*           pbWait  /* O: Determine if we need to wait IRQ in driver functions */
        );
    tmErrorCode_t
        tmbslTDA182I2GetIRQ(
        tmUnitSelect_t  tUnit  /* I: Unit number */,
        Bool*           pbIRQ  /* O: IRQ triggered */
        );
    tmErrorCode_t
        tmbslTDA182I2WaitIRQ(
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          timeOut,    /* I: timeOut for IRQ wait */
        UInt32          waitStep,   /* I: wait step */
        UInt8           irqStatus   /* I: IRQs to wait */
        );
    tmErrorCode_t
        tmbslTDA182I2GetXtalCal_End(
        tmUnitSelect_t  tUnit           /* I: Unit number */,
        Bool*           pbXtalCal_End   /* O: XtalCal_End triggered */
        );
    tmErrorCode_t
        tmbslTDA182I2WaitXtalCal_End(
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          timeOut,    /* I: timeOut for IRQ wait */
        UInt32          waitStep    /* I: wait step */
        );
    tmErrorCode_t
        tmbslTDA182I2SoftReset(
        tmUnitSelect_t  tUnit   /* I: Unit number */
        );
    tmErrorCode_t
        tmbslTDA182I2CheckRFFilterRobustness
        (
        tmUnitSelect_t                         tUnit,      /* I: Unit number */
        ptmTDA182I2RFFilterRating              rating      /* O: RF Filter rating */
        );
    tmErrorCode_t
        tmbslTDA182I2Write (
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          uIndex,     /* I: Start index to write */
        UInt32          WriteLen,   /* I: Number of bytes to write */
        UInt8*          pData       /* I: Data to write */
        );
    tmErrorCode_t
        tmbslTDA182I2Read (
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          uIndex,     /* I: Start index to read */
        UInt32          ReadLen,    /* I: Number of bytes to read */
        UInt8*          pData       /* I: Data to read */
        );

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA18272_H */
