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
* \file          tmbslTDA18273.h
*                %version: CFR_FEAP#13 %
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

#ifndef _TMBSL_TDA18273_H
#define _TMBSL_TDA18273_H

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
#define TDA18273_ERR_BASE               (CID_COMP_TUNER | CID_LAYER_BSL)
#define TDA18273_ERR_COMP               (CID_COMP_TUNER | CID_LAYER_BSL | TM_ERR_COMP_UNIQUE_START)

#define TDA18273_ERR_BAD_UNIT_NUMBER    (TDA18273_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define TDA18273_ERR_NOT_INITIALIZED    (TDA18273_ERR_BASE + TM_ERR_NOT_INITIALIZED)
#define TDA18273_ERR_INIT_FAILED        (TDA18273_ERR_BASE + TM_ERR_INIT_FAILED)
#define TDA18273_ERR_BAD_PARAMETER      (TDA18273_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define TDA18273_ERR_NOT_SUPPORTED      (TDA18273_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define TDA18273_ERR_HW_FAILED          (TDA18273_ERR_COMP + 0x0001)
#define TDA18273_ERR_NOT_READY          (TDA18273_ERR_COMP + 0x0002)
#define TDA18273_ERR_BAD_VERSION        (TDA18273_ERR_COMP + 0x0003)


typedef enum _tmTDA18273PowerState_t {
    tmTDA18273_PowerNormalMode = 0,                                 /* Device normal mode */
    tmTDA18273_PowerStandbyWithXtalOn,                              /* Device standby mode with Xtal Output */
    tmTDA18273_PowerStandby,                                        /* Device standby mode */
    tmTDA18273_PowerMax
} tmTDA18273PowerState_t, *ptmTDA18273PowerState_t;

typedef enum _tmTDA18273StandardMode_t {
    tmTDA18273_QAM_6MHz = 0,                            /* Digital TV QAM 6MHz */
    tmTDA18273_QAM_8MHz,                                /* Digital TV QAM 8MHz */
    tmTDA18273_ATSC_6MHz,                               /* Digital TV ATSC 6MHz */
    tmTDA18273_ISDBT_6MHz,                              /* Digital TV ISDBT 6MHz */
    tmTDA18273_DVBT_1_7MHz,                             /* Digital TV DVB-T/T2 6MHz */
    tmTDA18273_DVBT_6MHz,                               /* Digital TV DVB-T/T2 6MHz */
    tmTDA18273_DVBT_7MHz,                               /* Digital TV DVB-T/T2 7MHz */
    tmTDA18273_DVBT_8MHz,                               /* Digital TV DVB-T/T2 8MHz */
    tmTDA18273_DVBT_10MHz,                              /* Digital TV DVB-T/T2 10MHz */     
	tmTDA18273_DMBT_6MHz,								/* Digital TV DMB-T 6MHz */  
    tmTDA18273_DMBT_8MHz,                               /* Digital TV DMB-T 8MHz */
    tmTDA18273_FM_Radio,                                /* Analog FM Radio */
    tmTDA18273_ANLG_MN,                                 /* Analog TV M/N */
    tmTDA18273_ANLG_B,                                  /* Analog TV B */
    tmTDA18273_ANLG_GH,                                 /* Analog TV G/H */
    tmTDA18273_ANLG_I,                                  /* Analog TV I */
    tmTDA18273_ANLG_DK,                                 /* Analog TV D/K */
    tmTDA18273_ANLG_L,                                  /* Analog TV L */
    tmTDA18273_ANLG_LL,                                 /* Analog TV L' */
    tmTDA18273_Scanning,                                /* Analog Preset Blind Scanning */
    tmTDA18273_ScanXpress,                              /* ScanXpress */
    tmTDA18273_StandardMode_Max
} tmTDA18273StandardMode_t, *ptmTDA18273StandardMode_t;

/* Only used in debug platform, and not in embedded platform */
#ifdef TMFL_TDA18273_RFFILTER_DEBUG

typedef enum _tmTDA18273RFFilterRobustness_t {
    tmTDA18273RFFilterRobustness_Low = 0,
    tmTDA18273RFFilterRobustness_High,
    tmTDA18273RFFilterRobustness_Error,
    tmTDA18273RFFilterRobustness_Max
} tmTDA18273RFFilterRobustness_t, *ptmTDA18273RFFilterRobustness_t;

typedef struct _tmTDA18273RFFilterRating {
    double                               VHFLow_0_Margin;
    double                               VHFLow_1_Margin;
    double                               VHFHigh_0_Margin;
    double                               VHFHigh_1_Margin;
    double                               UHFLow_0_Margin;
    double                               UHFLow_1_Margin;
    double                               UHFHigh_0_Margin;
    double                               UHFHigh_1_Margin;    
    tmTDA18273RFFilterRobustness_t       VHFLow_0_RFFilterRobustness;
    tmTDA18273RFFilterRobustness_t       VHFLow_1_RFFilterRobustness;
    tmTDA18273RFFilterRobustness_t       VHFHigh_0_RFFilterRobustness;
    tmTDA18273RFFilterRobustness_t       VHFHigh_1_RFFilterRobustness;
    tmTDA18273RFFilterRobustness_t       UHFLow_0_RFFilterRobustness;
    tmTDA18273RFFilterRobustness_t       UHFLow_1_RFFilterRobustness;
    tmTDA18273RFFilterRobustness_t       UHFHigh_0_RFFilterRobustness;
    tmTDA18273RFFilterRobustness_t       UHFHigh_1_RFFilterRobustness;
} tmTDA18273RFFilterRating, *ptmTDA18273RFFilterRating;

typedef struct _tmTDA18273RFFilterBandwidth {
    double delta_up;
    double bandwidth_3dB_up;
    double delta_down;
    double bandwidth_3dB_down;
} tmTDA18273RFFilterBandwidth, *ptmTDA18273RFFilterBandwidth;

#endif

tmErrorCode_t
    tmbslTDA18273Init(
    tmUnitSelect_t              tUnit,      /*  I: Unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
    );
tmErrorCode_t 
    tmbslTDA18273DeInit (
    tmUnitSelect_t  tUnit   /*  I: Unit number */
    );
tmErrorCode_t
    tmbslTDA18273GetSWVersion (
    ptmSWVersion_t  pSWVersion  /*  I: Receives SW Version */
    );
tmErrorCode_t
    tmbslTDA18273CheckHWVersion (
    tmUnitSelect_t tUnit    /* I: Unit number */
    );
tmErrorCode_t
    tmbslTDA18273SetPowerState (
    tmUnitSelect_t          tUnit,      /*  I: Unit number */
    tmTDA18273PowerState_t  powerState  /*  I: Power state of this device */
    );
tmErrorCode_t
    tmbslTDA18273GetPowerState (
    tmUnitSelect_t            tUnit,        /*  I: Unit number */
    tmTDA18273PowerState_t    *pPowerState  /*  O: Power state of this device */
    );
tmErrorCode_t
    tmbslTDA18273SetStandardMode (
    tmUnitSelect_t              tUnit,          /*  I: Unit number */
    tmTDA18273StandardMode_t    StandardMode    /*  I: Standard mode of this device */
    );
tmErrorCode_t
    tmbslTDA18273GetStandardMode (
    tmUnitSelect_t              tUnit,          /*  I: Unit number */
    tmTDA18273StandardMode_t    *pStandardMode  /*  O: Standard mode of this device */
    );
tmErrorCode_t
    tmbslTDA18273SetPLDReadImmunity (
    tmUnitSelect_t              tUnit,          /* I: Unit number */
    Bool                        PLDReadImmunity /* I: PLD Read immunity algorithm ON or OFF */
    );
tmErrorCode_t
    tmbslTDA18273GetPLDReadImmunity (
    tmUnitSelect_t              tUnit,           /* I: Unit number */
    Bool*                       PLDReadImmunity  /* O: PLD Read immunity algorithm ON or OFF */
    );
tmErrorCode_t
    tmbslTDA18273SetRf(
    tmUnitSelect_t  tUnit,  /*  I: Unit number */
    UInt32          uRF     /*  I: RF frequency in hertz */
    );
tmErrorCode_t
    tmbslTDA18273GetRf(
    tmUnitSelect_t  tUnit,  /*  I: Unit number */
    UInt32*         pRF     /*  O: RF frequency in hertz */
    );
tmErrorCode_t
    tmbslTDA18273Reset(
    tmUnitSelect_t tUnit    /* I: Unit number */
    );
tmErrorCode_t
    tmbslTDA18273GetIF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puIF    /* O: IF Frequency in hertz */
    );
tmErrorCode_t
    tmbslTDA18273GetCF_Offset(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32*         puOffset    /* O: Center frequency offset in hertz */
    );
tmErrorCode_t
    tmbslTDA18273GetLockStatus(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    tmbslFrontEndState_t*   pLockStatus /* O: PLL Lock status */
    );
tmErrorCode_t
    tmbslTDA18273GetPowerLevel(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8*         pPowerLevel  /* O: Power Level in dBµV */
    );
tmErrorCode_t
    tmbslTDA18273GetRSSI(
    tmUnitSelect_t  tUnit,  //  I: Unit number
    UInt8*          puValue //  O: Address of the variable to output item value
    );
tmErrorCode_t
    tmbslTDA18273SetIRQWait(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool            bWait   /* I: Determine if we need to wait IRQ in driver functions */
    );
tmErrorCode_t
    tmbslTDA18273GetIRQWait(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool*           pbWait  /* O: Determine if we need to wait IRQ in driver functions */
    );
tmErrorCode_t
    tmbslTDA18273GetIRQ(
    tmUnitSelect_t  tUnit  /* I: Unit number */,
    Bool*           pbIRQ  /* O: IRQ triggered */
    );
tmErrorCode_t
    tmbslTDA18273WaitIRQ(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeOut for IRQ wait */
    UInt32          waitStep,   /* I: wait step */
    UInt8           irqStatus   /* I: IRQs to wait */
    );
tmErrorCode_t
    tmbslTDA18273GetXtalCal_End(
    tmUnitSelect_t  tUnit           /* I: Unit number */,
    Bool*           pbXtalCal_End   /* O: XtalCal_End triggered */
    );
tmErrorCode_t
    tmbslTDA18273WaitXtalCal_End(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeOut for IRQ wait */
    UInt32          waitStep    /* I: wait step */
    );
tmErrorCode_t
    tmbslTDA18273SoftReset(
    tmUnitSelect_t  tUnit   /* I: Unit number */
    );
/* You can only add one step (-1 or +1) at a time along -125 KHz <-> -62.5 KHz <-> 0 <-> 62.5 KHz <-> 125 KHz */
/* After calling tmbslTDA18273SetRf, step is reset at 0 */
tmErrorCode_t
    tmbslTDA18273RFFineTuning
    (
    tmUnitSelect_t tUnit,      /* I: Unit number */
    Int8           step        /* I: step (-1, +1) */
    );

/* Only used in debug platform, and not in embedded platform */
#ifdef TMFL_TDA18273_RFFILTER_DEBUG

tmErrorCode_t
    tmbslTDA18273CheckRFFilterRobustness
    (
    tmUnitSelect_t                         tUnit,      /* I: Unit number */
    ptmTDA18273RFFilterRating              rating      /* O: RF Filter rating */
    );

#endif

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA18273_H */
