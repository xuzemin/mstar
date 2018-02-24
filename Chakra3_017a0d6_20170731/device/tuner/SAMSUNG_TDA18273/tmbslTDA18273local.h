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
Copyright (C) 2010 NXP B.V., All Rights Reserved.
This source code and any compilation or derivative thereof is the proprietary
information of NXP B.V. and is confidential in nature. Under no circumstances
is this software to be  exposed to or placed under an Open Source License of
any type without the expressed written permission of NXP B.V.
*
* \file          tmbslTDA18273local.h
*                %version: 4 %
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

#ifndef _TMBSL_TDA18273LOCAL_H 
#define _TMBSL_TDA18273LOCAL_H

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

#define TDA18273_BSL_COMP_NUM    2 // Major protocol change - Specification change required
#define TDA18273_BSL_MAJOR_VER   8 // Minor protocol change - Specification change required
#define TDA18273_BSL_MINOR_VER   0 // Software update - No protocol change - No specification change required

#define TDA18273_MUTEX_TIMEOUT  TMBSL_FRONTEND_MUTEX_TIMEOUT_INFINITE

#define TMBSL_TDA18273_COMPONENT_NAME_STR "TDA18273"

#define _SYSTEMFUNC (pObj->SystemFunc)
#define POBJ_SRVFUNC_SIO pObj->sRWFunc
#define POBJ_SRVFUNC_STIME pObj->sTime
#define P_DBGPRINTEx pObj->sDebug.Print
#define P_DBGPRINTVALID ((pObj != Null) && (pObj->sDebug.Print != Null))


/*-------------*/
/* ERROR CODES */
/*-------------*/

//#define TDA18273_MAX_UNITS   1

typedef enum _tmTDA18273LPF_t {
    tmTDA18273_LPF_6MHz = 0,                        /* 6MHz LPFc */
    tmTDA18273_LPF_7MHz,                            /* 7MHz LPFc */
    tmTDA18273_LPF_8MHz,                            /* 8MHz LPFc */
    tmTDA18273_LPF_9MHz,                            /* 9MHz LPFc */
    tmTDA18273_LPF_1_5MHz,                          /* 1.5MHz LPFc */
    tmTDA18273_LPF_Max
} tmTDA18273LPF_t, *ptmTDA18273LPF_t;

typedef enum _tmTDA18273LPFOffset_t {
    tmTDA18273_LPFOffset_0pc = 0,                   /* LPFc 0% */
    tmTDA18273_LPFOffset_min_4pc,                   /* LPFc -4% */
    tmTDA18273_LPFOffset_min_8pc,                   /* LPFc -8% */
    tmTDA18273_LPFOffset_min_12pc,                  /* LPFc -12% */
    tmTDA18273_LPFOffset_Max
} tmTDA18273LPFOffset_t, *ptmTDA18273LPFOffset_t;

typedef enum tmTDA18273DC_Notch_IF_PPF_t {
    tmTDA18273_DC_Notch_IF_PPF_Disabled = 0,               /* IF Notch Disabled */
    tmTDA18273_DC_Notch_IF_PPF_Enabled,                    /* IF Notch Enabled */
    tmTDA18273_DC_Notch_IF_PPF_Max
} tmTDA18273DC_Notch_IF_PPF_t, *ptmTDA18273DC_Notch_IF_PPF_t;

typedef enum _tmTDA18273IF_HPF_t {
    tmTDA18273_IF_HPF_Disabled = 0,                 /* IF HPF disabled */
    tmTDA18273_IF_HPF_0_4MHz,                       /* IF HPF 0.4MHz */
    tmTDA18273_IF_HPF_0_85MHz,                      /* IF HPF 0.85MHz */
    tmTDA18273_IF_HPF_1MHz,                         /* IF HPF 1MHz */
    tmTDA18273_IF_HPF_1_5MHz,                       /* IF HPF 1.5MHz */
    tmTDA18273_IF_HPF_Max
} tmTDA18273IF_HPF_t, *ptmTDA18273IF_HPF_t;

typedef enum _tmTDA18273IF_Notch_t {
    tmTDA18273_IF_Notch_Disabled = 0,               /* IF Notch Disabled */
    tmTDA18273_IF_Notch_Enabled,                    /* IF Notch Enabled */
    tmTDA18273_IF_Notch_Max
} tmTDA18273IF_Notch_t, *ptmTDA18273IF_Notch_t;

typedef enum _tmTDA18273IFnotchToRSSI_t {
    tmTDA18273_IFnotchToRSSI_Disabled = 0,               /* IFnotchToRSSI Disabled */
    tmTDA18273_IFnotchToRSSI_Enabled,                    /* IFnotchToRSSI Enabled */
    tmTDA18273_IFnotchToRSSI_Max
} tmTDA18273IFnotchToRSSI_t, *ptmTDA18273IFnotchToRSSI_t;

typedef enum _tmTDA18273AGC1_TOP_I2C_DN_UP_t {
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d88_u82dBuV = 0,            /* AGC1 TOP I2C DN/UP down 88 up 82 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d90_u84dBuV,                /* AGC1 TOP I2C DN/UP down 90 up 84 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89wdBuV,               /* AGC1 TOP I2C DN/UP down 95 up 89 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d93_u87dBuV,                /* AGC1 TOP I2C DN/UP down 93 up 87 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                /* AGC1 TOP I2C DN/UP down 95 up 89 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d99_u84dBuV,                /* AGC1 TOP I2C DN/UP down 99 up 84 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d100_u82dBuV,               /* AGC1 TOP I2C DN/UP down 100 up 82 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d100_u94bisdBuV,            /* AGC1 TOP I2C DN/UP down 100 up 94 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d102_u82dBuV,               /* AGC1 TOP I2C DN/UP down 102 up 82 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d102_u84dBuV,               /* AGC1 TOP I2C DN/UP down 102 up 84 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_d100_u94dBuV,               /* AGC1 TOP I2C DN/UP down 100 up 94 dBuV */
    tmTDA18273_AGC1_TOP_I2C_DN_UP_Max
} tmTDA18273AGC1_TOP_I2C_DN_UP_t, *ptmTDA18273AGC1_TOP_I2C_DN_UP_t;

typedef enum _tmTDA18273AGC1_Adapt_TOP_DN_UP_t {
    tmTDA18273_AGC1_Adapt_TOP_DN_UP_0_Step = 0,        /* AGC1 Adapt TOP DN/UP 0 Step */
    tmTDA18273_AGC1_Adapt_TOP_DN_UP_1_Step,            /* AGC1 Adapt TOP DN/UP 1 Step */
    tmTDA18273_AGC1_Adapt_TOP_DN_UP_2_Step,            /* AGC1 Adapt TOP DN/UP 2 Step */
    tmTDA18273_AGC1_Adapt_TOP_DN_UP_3_Step,            /* AGC1 Adapt TOP DN/UP 3 Step */
    tmTDA18273_AGC1_Adapt_TOP_DN_UP_Max
} tmTDA18273AGC1_Adapt_TOP_DN_UP_t, *ptmTDA18273AGC1_Adapt_TOP_DN_UP_t;

typedef enum _tmTDA18273AGC1_DN_Time_Constant_t {
    tmTDA18273_AGC1_DN_Time_Constant_32_752ms = 0, /* 32.752 ms */
	tmTDA18273_AGC1_DN_Time_Constant_16_376ms,     /* 16.376 ms */
	tmTDA18273_AGC1_DN_Time_Constant_8_188ms,      /* 8.188 ms  */
	tmTDA18273_AGC1_DN_Time_Constant_4_094ms       /* 4.094 ms  */
} tmTDA18273AGC1_DN_Time_Constant_t, *ptmTDA18273AGC1_DN_Time_Constant_t;

typedef enum _tmTDA18273AGC1_Mode_t {
    tmTDA18273_AGC1_Mode_No_Mode = 0,                           /* AGC1 Mode */
    tmTDA18273_AGC1_Mode_TOP_ADAPT,                             /* AGC1 Mode: TOP ADAPT */
    tmTDA18273_AGC1_Mode_LNA_ADAPT,                             /* AGC1 Mode: LNA ADAPT */
    tmTDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT,                   /* AGC1 Mode: LNA ADAPT & TOP ADAPT */
    tmTDA18273_AGC1_Mode_FREEZE,                                /* AGC1 Mode: FREEZE */
    tmTDA18273_AGC1_Mode_WIDE,                                  /* AGC1 Mode: WIDE */
    tmTDA18273_AGC1_Mode_LNA_ADAPT_FREEZE,                      /* AGC1 Mode: LNA ADAPT & FREEZE */
    tmTDA18273_AGC1_Mode_LNA_ADAPT_WIDE,                        /* AGC1 Mode: LNA ADAPT & WIDE */
    tmTDA18273_AGC1_Mode_Max
} tmTDA18273AGC1_Mode_t, *ptmTDA18273AGC1_Mode_t;

typedef enum _tmTDA18273Range_LNA_Adapt_t {
    tmTDA18273_Range_LNA_Adapt_20dB_8dB = 0,                    /* RANGE LNA ADAPT 20dB-8dB */
    tmTDA18273_Range_LNA_Adapt_20dB_11dB,                       /* RANGE LNA ADAPT 20dB-11dB */
    tmTDA18273_Range_LNA_Adapt_Max
} tmTDA18273Range_LNA_Adapt_t, *ptmTDA18273Range_LNA_Adapt_t;

typedef enum _tmTDA18273LNA_Adapt_RFAGC_Gv_Threshold {
    tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_18_25dB = 0,        /* 18.25dB */
    tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_16_75dB,            /* 16.75dB */
    tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_15_25dB,            /* 15.25dB */
    tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_13_75dB,            /* 13.75dB */
    tmTDA18273_LNA_Adapt_RFAGC_Gv_Threshold_Max
} tmTDA18273LNA_Adapt_RFAGC_Gv_Threshold, *ptmTDA18273LNA_Adapt_RFAGC_Gv_Threshold;

typedef enum _tmTDA18273AGC1_Top_Adapt_RFAGC_Gv_Threshold {
    tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_16_75dB = 0,        /* 16.75dB */
    tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_15_25dB,            /* 15.25dB */
    tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_13_75dB,            /* 13.75dB */
    tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_12_25dB,            /* 12.25dB */
    tmTDA18273_AGC1_Top_Adapt_RFAGC_Gv_Threshold_Max
} tmTDA18273AGC1_Top_Adapt_RFAGC_Gv_Threshold, *ptmTDA18273AGC1_Top_Adapt_RFAGC_Gv_Threshold;

typedef enum _tmTDA18273AGC2_TOP_DN_UP_t {
    tmTDA18273_AGC2_TOP_DN_UP_d88_u81dBuV = 0, /* AGC2 TOP DN/UP down 88 up 81 dBuV */
    tmTDA18273_AGC2_TOP_DN_UP_d90_u83dBuV,     /* AGC2 TOP DN/UP down 90 up 83 dBuV */
    tmTDA18273_AGC2_TOP_DN_UP_d93_u86dBuV,     /* AGC2 TOP DN/UP down 93 up 86 dBuV */
    tmTDA18273_AGC2_TOP_DN_UP_d95_u88dBuV,     /* AGC2 TOP DN/UP down 95 up 88 dBuV */
    tmTDA18273_AGC2_TOP_DN_UP_d88_u82dBuV,     /* AGC2 TOP DN/UP down 88 up 82 dBuV */
    tmTDA18273_AGC2_TOP_DN_UP_d90_u84dBuV,     /* AGC2 TOP DN/UP down 90 up 84 dBuV */
    tmTDA18273_AGC2_TOP_DN_UP_d93_u87dBuV,     /* AGC2 TOP DN/UP down 93 up 87 dBuV */
    tmTDA18273_AGC2_TOP_DN_UP_d95_u89dBuV,     /* AGC2 TOP DN/UP down 95 up 89 dBuV */
    tmTDA18273_AGC2_TOP_DN_UP_Max
} tmTDA18273AGC2_TOP_DN_UP_t, *ptmTDA18273AGC2_TOP_DN_UP_t;

typedef enum _tmTDA18273AGC2_DN_Time_Constant_t {
	tmTDA18273_AGC2_DN_Time_Constant_16_376ms = 0, /* 16.376 ms */
	tmTDA18273_AGC2_DN_Time_Constant_8_188ms,      /* 8.188 ms  */
	tmTDA18273_AGC2_DN_Time_Constant_4_094ms,      /* 4.094 ms  */
	tmTDA18273_AGC2_DN_Time_Constant_2_047ms,      /* 2.047 ms  */
} tmTDA18273AGC2_DN_Time_Constant_t, *ptmTDA18273AGC2_DN_Time_Constant_t;

typedef enum _tmTDA18273AGC3_TOP_I2C_t {
    tmTDA18273_AGC3_TOP_I2C_94dBuV = 0, /* AGC3 TOP I2C 94 dBuV */
    tmTDA18273_AGC3_TOP_I2C_96dBuV,     /* AGC3 TOP I2C 96 dBuV */
    tmTDA18273_AGC3_TOP_I2C_98dBuV,     /* AGC3 TOP I2C 98 dBuV */
    tmTDA18273_AGC3_TOP_I2C_100dBuV,    /* AGC3 TOP I2C 100 dBuV */
    tmTDA18273_AGC3_TOP_I2C_102dBuV,    /* AGC3 TOP I2C 102 dBuV */
    tmTDA18273_AGC3_TOP_I2C_104dBuV,    /* AGC3 TOP I2C 104 dBuV */
    tmTDA18273_AGC3_TOP_I2C_106dBuV,    /* AGC3 TOP I2C 106 dBuV */
    tmTDA18273_AGC3_TOP_I2C_107dBuV,    /* AGC3 TOP I2C 107 dBuV */
    tmTDA18273_AGC3_TOP_I2C_Max
} tmTDA18273AGC3_TOP_I2C_t, *ptmTDA18273AGC3_TOP_I2C_t;

#define tmTDA18273_AGC3_TOP_I2C_FREQ_LIM 291000000

typedef enum _tmTDA18273AGC4_TOP_DN_UP_t {
    tmTDA18273_AGC4_TOP_DN_UP_d105_u99dBuV = 0,     /* AGC4 TOP DN/UP down 105 up 99 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d105_u100dBuV,        /* AGC4 TOP DN/UP down 105 up 100 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d105_u101dBuV,        /* AGC4 TOP DN/UP down 105 up 101 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d107_u101dBuV,        /* AGC4 TOP DN/UP down 107 up 101 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d107_u102dBuV,        /* AGC4 TOP DN/UP down 107 up 102 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d107_u103dBuV,        /* AGC4 TOP DN/UP down 107 up 103 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d108_u103dBuV,        /* AGC4 TOP DN/UP down 108 up 103 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d109_u103dBuV,        /* AGC4 TOP DN/UP down 109 up 103 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d109_u104dBuV,        /* AGC4 TOP DN/UP down 109 up 104 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d109_u105dBuV,        /* AGC4 TOP DN/UP down 109 up 105 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d110_u104dBuV,        /* AGC4 TOP DN/UP down 110 up 104 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d110_u105dBuV,        /* AGC4 TOP DN/UP down 110 up 105 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d110_u106dBuV,        /* AGC4 TOP DN/UP down 110 up 106 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d112_u106dBuV,        /* AGC4 TOP DN/UP down 112 up 106 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d112_u107dBuV,        /* AGC4 TOP DN/UP down 112 up 107 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_d112_u108dBuV,        /* AGC4 TOP DN/UP down 112 up 108 dBuV */
    tmTDA18273_AGC4_TOP_DN_UP_Max
} tmTDA18273AGC4_TOP_DN_UP_t, *ptmTDA18273AGC4_TOP_DN_UP_t;

typedef enum _tmTDA18273AGC5_TOP_DN_UP_t {
    tmTDA18273_AGC5_TOP_DN_UP_d105_u99dBuV = 0,        /* AGC5 TOP DN/UP down 105 up 99 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d105_u100dBuV,           /* AGC5 TOP DN/UP down 105 up 100 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d105_u101dBuV,           /* AGC5 TOP DN/UP down 105 up 101 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d107_u101dBuV,           /* AGC5 TOP DN/UP down 107 up 101 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d107_u102dBuV,           /* AGC5 TOP DN/UP down 107 up 102 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d107_u103dBuV,           /* AGC5 TOP DN/UP down 107 up 103 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d108_u103dBuV,           /* AGC5 TOP DN/UP down 108 up 103 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d109_u103dBuV,           /* AGC5 TOP DN/UP down 109 up 103 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d109_u104dBuV,           /* AGC5 TOP DN/UP down 109 up 104 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d109_u105dBuV,           /* AGC5 TOP DN/UP down 109 up 105 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d110_u104dBuV,           /* AGC5 TOP DN/UP down 108 up 104 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d110_u105dBuV,           /* AGC5 TOP DN/UP down 108 up 105 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d110_u106dBuV,           /* AGC5 TOP DN/UP down 108 up 106 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d112_u106dBuV,           /* AGC5 TOP DN/UP down 108 up 106 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d112_u107dBuV,           /* AGC5 TOP DN/UP down 108 up 107 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_d112_u108dBuV,           /* AGC5 TOP DN/UP down 108 up 108 dBuV */
    tmTDA18273_AGC5_TOP_DN_UP_Max
} tmTDA18273AGC5_TOP_DN_UP_t, *ptmTDA18273AGC5_TOP_DN_UP_t;

typedef enum _tmTDA18273AGC3_Top_Adapt_Algorithm {
    tmTDA18273_Top_Adapt_NO_TOP_ADAPT = 0,             /* NO TOP ADAPT */
    tmTDA18273_Top_Adapt_TOP_ADAPT35,                  /* TOP ADAPT35  */
    tmTDA18273_Top_Adapt_TOP_ADAPT34,                  /* TOP ADAPT34  */
    tmTDA18273_Top_Adapt_Max
} tmTDA18273AGC3_Top_Adapt_Algorithm, *ptmTDA18273AGC3_Top_Adapt_Algorithm;

typedef enum _tmTDA18273AGC3_Adapt_TOP_t {
     tmTDA18273_AGC3_Adapt_TOP_0_Step = 0,              /* same level as AGC3 TOP  */
     tmTDA18273_AGC3_Adapt_TOP_1_Step,                  /* 1 level below AGC3 TOP  */
     tmTDA18273_AGC3_Adapt_TOP_2_Step,                  /* 2 level below AGC3 TOP  */
     tmTDA18273_AGC3_Adapt_TOP_3_Step                   /* 3 level below AGC3 TOP  */
} tmTDA18273AGC3_Adapt_TOP_t, *ptmTDA18273AGC3_Adapt_TOP_t;

#define tmTDA18273_AGC3_ADAPT_TOP_FREQ_LIM 291000000

typedef enum _tmTDA18273AGC_Overload_TOP_t {
     tmTDA18273_AGC_Overload_TOP_plus_9_plus_3_5_min_3_5 = 0, /* +9/+3.5/-3.5 */
     tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_4_5,     /* +9/+4.5/-4.5 */
     tmTDA18273_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,     /* +9/+4.5/-3.5 */
     tmTDA18273_AGC_Overload_TOP_plus_9_plus_6_min_4_5,       /* +9/+6/-4.5   */
     tmTDA18273_AGC_Overload_TOP_plus_9_plus_6_min_6,         /* +9/+6/-6     */
     tmTDA18273_AGC_Overload_TOP_plus_9_plus_6_min_9,         /* +9/+6/-9     */
     tmTDA18273_AGC_Overload_TOP_plus_9_plus_7_5_min_9,       /* +9/+7.5/-9   */
     tmTDA18273_AGC_Overload_TOP_plus_12_plus_7_5_min_9       /* +12/+7.5/-9   */
} tmTDA18273AGC_Overload_TOP_t, *ptmTDA18273AGC_Overload_TOP_t;

typedef enum _tmTDA18273TH_AGC_Adapt34_t {
    tmTDA18273_TH_AGC_Adapt34_2dB = 0,             /* Adapt TOP 34 Gain Threshold 2dB */
    tmTDA18273_TH_AGC_Adapt34_5dB                  /* Adapt TOP 34 Gain Threshold 5dB */
} tmTDA18273TH_AGC_Adapt34_t, *ptmTDA18273TH_AGC_Adapt34_t;

typedef enum _tmTDA18273RF_Atten_3dB_t {
    tmTDA18273_RF_Atten_3dB_Disabled = 0,             /* RF_Atten_3dB Disabled */
    tmTDA18273_RF_Atten_3dB_Enabled,                  /* RF_Atten_3dB Enabled */
    tmTDA18273_RF_Atten_3dB_Max
} tmTDA18273RF_Atten_3dB_t, *ptmTDA18273RF_Atten_3dB_t;

typedef enum _tmTDA18273IF_Output_Level_t {
    tmTDA18273_IF_Output_Level_2Vpp_0_30dB = 0,         /* 2Vpp       0 - 30dB      */
    tmTDA18273_IF_Output_Level_1_25Vpp_min_4_26dB,      /* 1.25Vpp   -4 - 26dB      */
    tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB,         /* 1Vpp      -6 - 24dB      */
    tmTDA18273_IF_Output_Level_0_8Vpp_min_8_22dB,       /* 0.8Vpp    -8 - 22dB      */
    tmTDA18273_IF_Output_Level_0_85Vpp_min_7_5_22_5dB,  /* 0.85Vpp   -7.5 - 22.5dB  */
    tmTDA18273_IF_Output_Level_0_7Vpp_min_9_21dB,       /* 0.7Vpp    -9 - 21dB      */
    tmTDA18273_IF_Output_Level_0_6Vpp_min_10_3_19_7dB,  /* 0.6Vpp    -10.3 - 19.7dB */
    tmTDA18273_IF_Output_Level_0_5Vpp_min_12_18dB,      /* 0.5Vpp    -12 - 18dB     */
    tmTDA18273_IF_Output_Level_Max
} tmTDA18273IF_Output_Level_t, *ptmTDA18273IF_Output_Level_t;

typedef enum _tmTDA18273S2D_Gain_t {
    tmTDA18273_S2D_Gain_3dB = 0,                         /* 3dB */
    tmTDA18273_S2D_Gain_6dB,                             /* 6dB */
    tmTDA18273_S2D_Gain_9dB,                             /* 9dB */
    tmTDA18273_S2D_Gain_Max
} tmTDA18273S2D_Gain_t, *ptmTDA18273S2D_Gain_t;

typedef enum _tmTDA18273Negative_Modulation_t {
    tmTDA18273_Negative_Modulation_Disabled = 0,
    tmTDA18273_Negative_Modulation_Enabled,
    tmTDA18273_Negative_Modulation_Max
} tmTDA18273Negative_Modulation_t, *ptmTDA18273Negative_Modulation_t;

typedef enum _tmTDA18273AGCK_Steps_t {
    tmTDA18273_AGCK_Steps_0_2dB = 0,                     /* 0.2dB */
    tmTDA18273_AGCK_Steps_0_4dB,                         /* 0.4dB */
    tmTDA18273_AGCK_Steps_0_6dB,                         /* 0.6dB */
    tmTDA18273_AGCK_Steps_0_8dB,                         /* 0.8dB */
    tmTDA18273_AGCK_Steps_Max
} tmTDA18273AGCK_Steps_t, *ptmTDA18273AGCK_Steps_t;

typedef enum _tmTDA18273AGCK_Time_Constant_t {
    tmTDA18273_AGCK_Time_Constant_1_STEP_EACH_VSYNC_RISING_EDGE = 0, /* 1 Step Each VSYNC Rising Edge */
    tmTDA18273_AGCK_Time_Constant_0_512ms,                           /* 0.512ms                       */
    tmTDA18273_AGCK_Time_Constant_8_192ms,                           /* 8.192ms                       */
    tmTDA18273_AGCK_Time_Constant_32_768ms,                          /* 32.768ms                      */
    tmTDA18273_AGCK_Time_Constant_Max
} tmTDA18273AGCK_Time_Constant_t, *ptmTDA18273AGCK_Time_Constant_t;

typedef enum _tmTDA18273AGC5_HPF_t {
    tmTDA18273_AGC5_HPF_Disabled = 0,          /* AGC5 HPF Disabled */
    tmTDA18273_AGC5_HPF_Enabled,               /* AGC5 HPF Enabled  */
    tmTDA18273_AGC5_HPF_Max
} tmTDA18273AGC5_HPF_t, *ptmTDA18273AGC5_HPF_t;

typedef enum _tmTDA18273Pulse_Shaper_Disable_t {
    tmTDA18273_Pulse_Shaper_Disable_Disabled = 0,
    tmTDA18273_Pulse_Shaper_Disable_Enabled,
    tmTDA18273_Pulse_Shaper_Disable_Max
} tmTDA18273Pulse_Shaper_Disable_t, *ptmTDA18273Pulse_Shaper_Disable_t;

typedef enum _tmTDA18273VHF_III_Mode_t {
    tmTDA18273_VHF_III_Mode_Disabled = 0,           /* VHF_III_Mode Disabled */
    tmTDA18273_VHF_III_Mode_Enabled,                /* VHF_III_Mode Enabled  */
    tmTDA18273_VHF_III_Mode_Max
} tmTDA18273VHF_III_Mode_t, *ptmTDA18273VHF_III_Mode_t;

typedef enum _tmTDA18273LO_CP_Current_t {
    tmTDA18273_LO_CP_Current_Disabled = 0,          /* LO CP Current Disabled */
    tmTDA18273_LO_CP_Current_Enabled,               /* LO CP Current Enabled  */
    tmTDA18273_LO_CP_Current_Max
} tmTDA18273LO_CP_Current_t, *ptmTDA18273LO_CP_Current_t;

typedef enum _tmTDA18273PD_Underload_t {
    tmTDA18273_PD_Underload_Disabled = 0,    /* PD Underload Disabled */
    tmTDA18273_PD_Underload_Enabled,         /* PD Underload Enabled  */
    tmTDA18273_PD_Underload_Max
} tmTDA18273PD_Underload_t, *ptmTDA18273PD_Underload_t;

typedef struct _tmTDA18273StdCoefficients
{
    /****************************************************************/
    /* IF Settings                                                  */
    /****************************************************************/
    UInt32                                          IF;                                /* IF Frequency */
    Int32                                           CF_Offset;

    /****************************************************************/
    /* IF SELECTIVITY Settings                                      */
    /****************************************************************/
    tmTDA18273LPF_t                                 LPF;                               /* LPF Cut off */
    tmTDA18273LPFOffset_t                           LPF_Offset;                        /* LPF offset */
    tmTDA18273DC_Notch_IF_PPF_t                     DC_Notch_IF_PPF;                   /* DC notch IF PPF */
    tmTDA18273IF_HPF_t                              IF_HPF;                            /* Hi Pass */
    tmTDA18273IF_Notch_t                            IF_Notch;                          /* IF notch */
    tmTDA18273IFnotchToRSSI_t                       IFnotchToRSSI;                     /* IFnotchToRSSI */
    
    /****************************************************************/
    /* AGC TOP Settings                                             */
    /****************************************************************/
    tmTDA18273AGC1_TOP_I2C_DN_UP_t                  AGC1_TOP_I2C_DN_UP;                /* AGC1 TOP I2C DN/UP */
    tmTDA18273AGC1_Adapt_TOP_DN_UP_t                AGC1_Adapt_TOP_DN_UP;              /* AGC1 Adapt TOP DN/UP */
	tmTDA18273AGC1_DN_Time_Constant_t               AGC1_DN_Time_Constant;             /* AGC1 DN Time Constant */
    tmTDA18273AGC1_Mode_t                           AGC1_Mode;                         /* AGC1 mode */
    tmTDA18273Range_LNA_Adapt_t                     Range_LNA_Adapt;                   /* Range_LNA_Adapt */
    tmTDA18273LNA_Adapt_RFAGC_Gv_Threshold          LNA_Adapt_RFAGC_Gv_Threshold;      /* LNA_Adapt_RFAGC_Gv_Threshold */
    tmTDA18273AGC1_Top_Adapt_RFAGC_Gv_Threshold     AGC1_Top_Adapt_RFAGC_Gv_Threshold; /* AGC1_Top_Adapt_RFAGC_Gv_Threshold */
    tmTDA18273AGC2_TOP_DN_UP_t                      AGC2_TOP_DN_UP;                    /* AGC2 TOP DN/UP */
	tmTDA18273AGC2_DN_Time_Constant_t               AGC2_DN_Time_Constant;             /* AGC2 DN Time Constant */
    tmTDA18273AGC3_TOP_I2C_t                        AGC3_TOP_I2C_Low_Band;             /* AGC3 TOP I2C Low Band */
    tmTDA18273AGC3_TOP_I2C_t                        AGC3_TOP_I2C_High_Band;            /* AGC3 TOP I2C High Band*/
    tmTDA18273AGC4_TOP_DN_UP_t                      AGC4_TOP_DN_UP;                    /* AGC4 TOP DN/UP */
    tmTDA18273AGC5_TOP_DN_UP_t                      AGC5_TOP_DN_UP;                    /* AGC5 TOP DN/UP */
    tmTDA18273AGC3_Top_Adapt_Algorithm              AGC3_Top_Adapt_Algorithm;          /* AGC3_Top_Adapt_Algorithm */
    tmTDA18273AGC3_Adapt_TOP_t                      AGC3_Adapt_TOP_Low_Band;           /* AGC3 Adapt TOP Low Band */
    tmTDA18273AGC3_Adapt_TOP_t                      AGC3_Adapt_TOP_High_Band;          /* AGC3 Adapt TOP High Band */
    tmTDA18273AGC_Overload_TOP_t                    AGC_Overload_TOP;                  /* AGC Overload TOP */
    tmTDA18273TH_AGC_Adapt34_t                      TH_AGC_Adapt34;                    /* Adapt TOP 34 Gain Threshold */
    tmTDA18273RF_Atten_3dB_t                        RF_Atten_3dB;                      /* RF atten 3dB */
    tmTDA18273IF_Output_Level_t                     IF_Output_Level;                   /* IF Output Level */
    tmTDA18273S2D_Gain_t                            S2D_Gain;                          /* S2D gain */
    tmTDA18273Negative_Modulation_t                 Negative_Modulation;               /* Negative modulation */

    /****************************************************************/
    /* GSK Settings                                                 */
    /****************************************************************/
    tmTDA18273AGCK_Steps_t                          AGCK_Steps;                        /* Step */
    tmTDA18273AGCK_Time_Constant_t                  AGCK_Time_Constant;                /* AGCK Time Constant */
    tmTDA18273AGC5_HPF_t                            AGC5_HPF;                          /* AGC5 HPF */
    tmTDA18273Pulse_Shaper_Disable_t                Pulse_Shaper_Disable;              /* Pulse Shaper Disable */

    /****************************************************************/
    /* H3H5 Settings                                                */
    /****************************************************************/
    tmTDA18273VHF_III_Mode_t                        VHF_III_Mode;                      /* VHF_III_Mode */

    /****************************************************************/
    /* PLL Settings                                                 */
    /****************************************************************/
    tmTDA18273LO_CP_Current_t                       LO_CP_Current;                     /* LO_CP_Current */

	/****************************************************************/
    /* MISC Settings                                                */
    /****************************************************************/
	tmTDA18273PD_Underload_t                        PD_Underload;                      /* PD Underload */
	UInt32										    Freq_Start_LTE;                    /* Frequency start of high band for LTE */
} tmTDA18273StdCoefficients, *ptmTDA18273StdCoefficients;

typedef struct _tmTDA18273Object_t
{
    tmUnitSelect_t              tUnit;
    tmUnitSelect_t              tUnitW;
    ptmbslFrontEndMutexHandle   pMutex;
    Bool                        init;
    Bool                        PLD_CC_algorithm; /* Enable or not the PLD CC algorithm : PLD immunity against adjacents */
    Bool                        bIRQWait; /* Indicates if wait is performed inside the driver */
    tmbslFrontEndIoFunc_t       sRWFunc;
    tmbslFrontEndTimeFunc_t     sTime;
    tmbslFrontEndDebugFunc_t    sDebug;
    tmbslFrontEndMutexFunc_t    sMutex;
    tmTDA18273PowerState_t      curPowerState;
    tmTDA18273PowerState_t      minPowerState;
    UInt32                      uRF;
    tmTDA18273StandardMode_t    StandardMode;
    Bool                        bBufferModeUsed; /* Enable the bufferMode on the driver to bypass XTCal_End check */
    tmTDA18273StdCoefficients   Std_Array[tmTDA18273_StandardMode_Max];
} tmTDA18273Object_t, *ptmTDA18273Object_t, **pptmTDA18273Object_t;

extern tmErrorCode_t TDA18273MutexAcquire(ptmTDA18273Object_t   pObj, UInt32 timeOut);
extern tmErrorCode_t TDA18273MutexRelease(ptmTDA18273Object_t   pObj);

extern tmErrorCode_t TDA18273CheckCalcPLL(ptmTDA18273Object_t pObj);

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA18273LOCAL_H */
