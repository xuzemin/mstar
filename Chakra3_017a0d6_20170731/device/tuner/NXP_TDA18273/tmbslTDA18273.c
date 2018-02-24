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
//-----------------------------------------------------------------------------
// $Header: 
// (C) Copyright 2001 NXP Semiconductors, All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of NXP Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of NXP
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than NXP Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmbslTDA18273.c
//
// %version: CFR_FEAP#23.1 %
//
// DESCRIPTION:  Function for the Hybrid silicon tuner TDA18273
//
// DOCUMENT REF: 
//
// NOTES:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------
//

#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"

#include "tmddTDA18273.h"
#include "tmddTDA18273_Advanced.h"
#include "tmbslTDA18273.h"

//-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
//
#include "tmbslTDA18273local.h"
#include "tmbslTDA18273Instance.h"
#include "tmbslTDA18273_InstanceCustom.h"

//-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
//

/* Define MSM bits */
#define MSM_CALC_PLL      0x1
#define MSM_RC_CAL        0x2
#define MSM_IR_CAL_WANTED 0x4
#define MSM_IR_CAL_IMAGE  0x8
#define MSM_IR_CAL_LOOP   0x10
#define MSM_RF_CAL        0x20
#define MSM_RF_CAL_AV     0x40
#define MSM_RSSI_MEAS     0x80

//-----------------------------------------------------------------------------
// Global data:
//-----------------------------------------------------------------------------
//

static tmErrorCode_t TDA18273Wait(ptmTDA18273Object_t pObj, UInt32 Time);
static tmErrorCode_t TDA18273WaitXtalCal_End( ptmTDA18273Object_t pObj, UInt32 timeOut, UInt32 waitStep);
static tmErrorCode_t TDA18273GetRSSI(ptmTDA18273Object_t pObj, UInt8 *uValue);
static tmErrorCode_t TDA18273SetRF(ptmTDA18273Object_t pObj, UInt32 freq);
static tmErrorCode_t TDA18273OverrideBandsplit(ptmTDA18273Object_t pObj);
static tmErrorCode_t TDA18273OverrideICP(ptmTDA18273Object_t pObj, UInt32 freq);
static tmErrorCode_t TDA18273OverrideWireless(ptmTDA18273Object_t pObj);
static tmErrorCode_t TDA18273FirstPassPLD_CC(ptmTDA18273Object_t pObj);
static tmErrorCode_t TDA18273LastPassPLD_CC(ptmTDA18273Object_t pObj);
static tmErrorCode_t TDA18273SetPowerState(ptmTDA18273Object_t pObj, tmddTDA18273PowerState_t powerState);

//-----------------------------------------------------------------------------
// Exported functions:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18211Init:
//
// DESCRIPTION: create an instance of a TDA18273 Tuner
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TM_OK
//  
// NOTES:
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273Init
(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    if (psSrvFunc == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        //----------------------
        // initialize the Object
        //----------------------
        // pObj initialization
        err = TDA18273GetInstance(tUnit, &pObj);
    }

    /* check driver state */
    if (err == TM_OK || err == TDA18273_ERR_NOT_INITIALIZED)
    {
        if (pObj != Null && pObj->init == True)
        {
            err = TDA18273_ERR_NOT_INITIALIZED;
        }
        else 
        {
            /* initialize the Object */
            if (pObj == Null)
            {
                err = TDA18273AllocInstance(tUnit, &pObj);
                if (err != TM_OK || pObj == Null)
                {
                    err = TDA18273_ERR_NOT_INITIALIZED;        
                }
            }

            if (err == TM_OK)
            {
                // initialize the Object by default values
                pObj->sRWFunc = psSrvFunc->sIo;
                pObj->sTime = psSrvFunc->sTime;
                pObj->sDebug = psSrvFunc->sDebug;

                if(  psSrvFunc->sMutex.Init != Null
                    && psSrvFunc->sMutex.DeInit != Null
                    && psSrvFunc->sMutex.Acquire != Null
                    && psSrvFunc->sMutex.Release != Null)
                {
                    pObj->sMutex = psSrvFunc->sMutex;

                    err = pObj->sMutex.Init(&pObj->pMutex);
                }

                pObj->init = True;
                err = TM_OK;

                err = tmddTDA18273Init(tUnit, psSrvFunc);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Init(0x%08X) failed.", pObj->tUnit));
            }
        }
    }

    return err;
}

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273DeInit:
//
// DESCRIPTION: destroy an instance of a TDA18273 Tuner
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-----------------------------------------------------------------------------
//
tmErrorCode_t 
tmbslTDA18273DeInit
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* check input parameters */
    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = tmddTDA18273DeInit(tUnit);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273DeInit(0x%08X) failed.", pObj->tUnit));

        (void)TDA18273MutexRelease(pObj);

        if(pObj->sMutex.DeInit != Null)
        {
            if(pObj->pMutex != Null)
            {
                err = pObj->sMutex.DeInit(pObj->pMutex);
            }

            pObj->sMutex.Init = Null;
            pObj->sMutex.DeInit = Null;
            pObj->sMutex.Acquire = Null;
            pObj->sMutex.Release = Null;

            pObj->pMutex = Null;
        }
    }

    err = TDA18273DeAllocInstance(tUnit);

    return err;
}

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273GetSWVersion:
//
// DESCRIPTION: Return the version of this device
//
// RETURN:      TM_OK
//
// NOTES:       Values defined in the tmTDA18273local.h file
//-----------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273GetSWVersion
(
    ptmSWVersion_t  pSWVersion  /* I: Receives SW Version */
)
{
    tmErrorCode_t err = TM_OK;
    
    /* Get BSL version */
    pSWVersion->compatibilityNr = TDA18273_BSL_COMP_NUM;
    pSWVersion->majorVersionNr  = TDA18273_BSL_MAJOR_VER;
    pSWVersion->minorVersionNr  = TDA18273_BSL_MINOR_VER;

    /* Add Version of the Settings into the MSB part */
    pSWVersion->compatibilityNr |= (TMBSL_TDA18273_SETTINGS_COMP_NUM << 16);
    pSWVersion->majorVersionNr |= (TMBSL_TDA18273_SETTINGS_MAJOR_VER << 16);
    pSWVersion->minorVersionNr |= (TMBSL_TDA18273_SETTINGS_MINOR_VER << 16);
    
    return err;
}

//-----------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273CheckHWVersion:
//
// DESCRIPTION: Check HW version
//
// RETURN:      TM_OK if no error
//
// NOTES:       Values defined in the tmTDA18273local.h file
//-----------------------------------------------------------------------------
tmErrorCode_t
tmbslTDA18273CheckHWVersion
(
    tmUnitSelect_t tUnit    /* I: Unit number */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TDA18273_ERR_NOT_INITIALIZED;
    UInt16              uIdentity = 0;
    UInt8               majorRevision = 0;
    UInt8               minorRevision = 0;

    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = tmddTDA18273GetIdentity(tUnit, &uIdentity);

        if(err == TM_OK)
        {
            if(uIdentity == 18273)
            {
                /* TDA18273 found. Check Major & Minor revision*/
                err = tmddTDA18273GetMajorRevision(tUnit, &majorRevision);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetMajorRevision(0x%08X) failed.", tUnit));

                err = tmddTDA18273GetMinorRevision(tUnit, &minorRevision);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetMinorRevision(0x%08X) failed.", tUnit));

                if(err == TM_OK)
                {
                    if (
                        (majorRevision == 1) &&
                        ((minorRevision == 0) || (minorRevision == 1))
                       )
                    {
                        /* Supported ICs */
                        err = TM_OK;
                    }
                    else
                    {
                        /* Only TDA18273 ES1 or ES2 are supported */
                        err = TDA18273_ERR_BAD_VERSION;
                    }
                }
            }
            else
            {
                err = TDA18273_ERR_BAD_VERSION;
            }
        }

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273SetPowerState:
//
// DESCRIPTION: Set the power state of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273SetPowerState
(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    tmTDA18273PowerState_t  powerState  /* I: Power state of this device */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    // pObj initialization
    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        UInt8 uBytes[23];

        if(powerState > pObj->minPowerState)
        {
            powerState = pObj->minPowerState;
        }

        /* Read bytes 0x00-0x16 */
        err = tmddTDA18273Read(tUnit, 0, 23, &uBytes[0]);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Read(0x%08X) failed.", tUnit));
        
        // Call tmddTDA18273SetPowerState
        err = TDA18273SetPowerState(pObj, (tmddTDA18273PowerState_t)powerState);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273SetPowerState(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // set power state
            pObj->curPowerState = powerState;
        }

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273GetPowerState:
//
// DESCRIPTION: Get the power state of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273GetPowerState
(
    tmUnitSelect_t          tUnit,          /* I: Unit number */
    tmTDA18273PowerState_t  *pPowerState    /* O: Power state of this device */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    if(pPowerState == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        // pObj initialization
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // get power state
        *pPowerState = pObj->curPowerState;

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273SetStandardMode:
//
// DESCRIPTION: Set the standard mode of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273SetStandardMode
(
    tmUnitSelect_t              tUnit,          /* I: Unit number */
    tmTDA18273StandardMode_t    StandardMode    /* I: Standard mode of this device */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    /* pObj initialization */
    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* store standard mode  */
        pObj->StandardMode = StandardMode;

        /* Set the proper settings depending on the standard */

        /****************************************************************/
        /* IF SELECTIVITY Settings                                      */
        /****************************************************************/

        if(err == TM_OK)
        {
            /* Set LPF */
            err = tmddTDA18273SetLP_FC(tUnit, pObj->Std_Array[pObj->StandardMode].LPF);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetLP_FC(0x%08X) failed.", tUnit));
        }
 
        if(err == TM_OK)
        {
            /* Set LPF Offset */
            err = tmddTDA18273SetLP_FC_Offset(tUnit, pObj->Std_Array[pObj->StandardMode].LPF_Offset);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetLP_FC_Offset(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set DC_Notch_IF_PPF */
            err = tmddTDA18273SetIF_Notch(tUnit, pObj->Std_Array[pObj->StandardMode].DC_Notch_IF_PPF);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIF_Notch(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Enable/disable HPF */
            if ( pObj->Std_Array[pObj->StandardMode].IF_HPF == tmTDA18273_IF_HPF_Disabled )
            {
                err = tmddTDA18273SetHi_Pass(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetHi_Pass(0x%08X, 0) failed.", tUnit));
            }
            else
            {
                err = tmddTDA18273SetHi_Pass(tUnit, 1);     
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetHi_Pass(0x%08X, 1) failed.", tUnit));

                if(err == TM_OK)
                {
                    /* Set IF HPF: -1 because of enum starting with disabled */
                    err = tmddTDA18273SetIF_HP_Fc(tUnit, (UInt8)(pObj->Std_Array[pObj->StandardMode].IF_HPF - 1));
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIF_HP_Fc(0x%08X) failed.", tUnit));
                }
            }
        }

        if(err == TM_OK)
        {
            /* Set IF Notch */
            err = tmddTDA18273SetIF_ATSC_Notch(tUnit, pObj->Std_Array[pObj->StandardMode].IF_Notch);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIF_ATSC_Notch(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set IF notch to RSSI */
            err = tmddTDA18273SetIFnotchToRSSI(tUnit, pObj->Std_Array[pObj->StandardMode].IFnotchToRSSI);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIFnotchToRSSI(0x%08X) failed.", tUnit));
        }

        /****************************************************************/
        /* AGC TOP Settings                                             */
        /****************************************************************/
        
        if(err == TM_OK)
        {
            /* Set AGC1 TOP I2C DN/UP */
            err = tmddTDA18273SetAGC1_TOP(tUnit, pObj->Std_Array[pObj->StandardMode].AGC1_TOP_I2C_DN_UP);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGC1_TOP(0x%08X) failed.", tUnit));
        }
        
        if(err == TM_OK)
        {
            /* Set AGC1 Adapt TOP DN/UP */
            err = tmddTDA18273SetAGC1_Top_Mode_Val(tUnit, pObj->Std_Array[pObj->StandardMode].AGC1_Adapt_TOP_DN_UP);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGC1_Top_Mode_Val(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            UInt8 minorVersion;

            /* For ES1 IC, we override the settings to tmTDA18273_AGC1_Mode_LNA_ADAPT_FREEZE */
            err = tmddTDA18273GetMinorRevision(tUnit, &minorVersion);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetMinorRevision(0x%08X, 0) failed.", tUnit));

            if(err == TM_OK)
            {
                /* ES1 version */
                if (minorVersion == 0)
                {
                    if ((pObj->StandardMode == tmTDA18273_QAM_6MHz) || (pObj->StandardMode == tmTDA18273_QAM_8MHz))
                    {
                        /* For QAM_6 & QAM_8, change settings */
                        pObj->Std_Array[pObj->StandardMode].AGC1_Mode = tmTDA18273_AGC1_Mode_LNA_ADAPT_FREEZE;
                    }
                }
            }

            /* Set AGC1 mode */
            err = tmddTDA18273SetAGC1_Top_Mode(tUnit, pObj->Std_Array[pObj->StandardMode].AGC1_Mode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGC1_Top_Mode(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set Range_LNA_Adapt */
            err = tmddTDA18273SetRange_LNA_Adapt(tUnit, pObj->Std_Array[pObj->StandardMode].Range_LNA_Adapt);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRange_LNA_Adapt(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set LNA_Adapt_RFAGC_Gv_Threshold */
            err = tmddTDA18273SetIndex_K_LNA_Adapt(tUnit, pObj->Std_Array[pObj->StandardMode].LNA_Adapt_RFAGC_Gv_Threshold);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIndex_K_LNA_Adapt(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set AGC1_Top_Adapt_RFAGC_Gv_Threshold */
            err = tmddTDA18273SetIndex_K_Top_Adapt(tUnit, pObj->Std_Array[pObj->StandardMode].AGC1_Top_Adapt_RFAGC_Gv_Threshold);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIndex_K_Top_Adapt(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set AGC2 TOP DN/UP */
            err = tmddTDA18273SetAGC2_TOP(tUnit, pObj->Std_Array[pObj->StandardMode].AGC2_TOP_DN_UP);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGC2_TOP(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set AGC4 TOP DN/UP */
            err = tmddTDA18273SetIR_Mixer_Top(tUnit, pObj->Std_Array[pObj->StandardMode].AGC4_TOP_DN_UP);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIR_Mixer_Top(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set AGC5 TOP DN/UP */
            err = tmddTDA18273SetAGC5_TOP(tUnit, pObj->Std_Array[pObj->StandardMode].AGC5_TOP_DN_UP);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGC5_TOP(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set AGC3_Top_Adapt_Algorithm */
            err = tmddTDA18273SetPD_AGC_Adapt3x(tUnit, pObj->Std_Array[pObj->StandardMode].AGC3_Top_Adapt_Algorithm);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPD_AGC_Adapt3x(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set AGC Overload TOP */
            err = tmddTDA18273SetAGC_Ovld_TOP(tUnit, pObj->Std_Array[pObj->StandardMode].AGC_Overload_TOP);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGC_Ovld_TOP(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set Adapt TOP 34 Gain Threshold */
            err = tmddTDA18273SetTH_AGC_Adapt34(tUnit, pObj->Std_Array[pObj->StandardMode].TH_AGC_Adapt34);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetTH_AGC_Adapt34(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set RF atten 3dB */
            err = tmddTDA18273SetRF_Atten_3dB(tUnit, pObj->Std_Array[pObj->StandardMode].RF_Atten_3dB);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRF_Atten_3dB(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set IF Output Level */
            err = tmddTDA18273SetIF_Level(tUnit, pObj->Std_Array[pObj->StandardMode].IF_Output_Level);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIF_Level(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set S2D gain */
            err = tmddTDA18273SetS2D_Gain(tUnit, pObj->Std_Array[pObj->StandardMode].S2D_Gain);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetS2D_Gain(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set Negative modulation */
            err = tmddTDA18273SetNeg_modulation(tUnit, pObj->Std_Array[pObj->StandardMode].Negative_Modulation);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetNeg_modulation(0x%08X) failed.", tUnit));
        }

        /****************************************************************/
        /* GSK Settings                                                 */
        /****************************************************************/

        if(err == TM_OK)
        {
            /* Set Step */
            err = tmddTDA18273SetAGCK_Step(tUnit, pObj->Std_Array[pObj->StandardMode].AGCK_Steps);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGCK_Step(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set AGCK Time Constant */
            err = tmddTDA18273SetAGCK_Mode(tUnit, pObj->Std_Array[pObj->StandardMode].AGCK_Time_Constant);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGCK_Mode(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            /* Set AGC5 HPF */
            UInt8 wantedValue = pObj->Std_Array[pObj->StandardMode].AGC5_HPF;

            if (pObj->Std_Array[pObj->StandardMode].AGC5_HPF == tmTDA18273_AGC5_HPF_Enabled)
            {
                UInt8 checked;

                /* Check if Internal Vsync is selected */
                err = tmddTDA18273GetVsync_int(tUnit, &checked);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetVsync_int(0x%08X) failed.", tUnit));

                if(err == TM_OK)
                {
                    if (checked == 0)
                    {
                        /* Internal Vsync is OFF, so override setting to OFF */
                        wantedValue = tmTDA18273_AGC5_HPF_Disabled;
                    }
                }
            }
            
            if(err == TM_OK)
            {
                err = tmddTDA18273SetAGC5_Ana(tUnit, wantedValue);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGC5_Ana(0x%08X) failed.", tUnit));
            }
        }

        if(err == TM_OK)
        {
            /* Set Pulse Shaper Disable */
            err = tmddTDA18273SetPulse_Shaper_Disable(tUnit, pObj->Std_Array[pObj->StandardMode].Pulse_Shaper_Disable);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPulse_Shaper_Disable(0x%08X) failed.", tUnit));
        }

        /****************************************************************/
        /* H3H5 Settings                                                */
        /****************************************************************/
        
        if(err == TM_OK)
        {
            /* Set VHF_III_Mode */
            err = tmddTDA18273SetVHF_III_mode(tUnit, pObj->Std_Array[pObj->StandardMode].VHF_III_Mode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetVHF_III_mode(0x%08X) failed.", tUnit));
        }

        /****************************************************************/
        /* PLL Settings                                                 */
        /****************************************************************/

        if(err == TM_OK)
        {
            /* Set LO_CP_Current */
            err = tmddTDA18273SetLO_CP_Current(tUnit, pObj->Std_Array[pObj->StandardMode].LO_CP_Current);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetLO_CP_Current(0x%08X) failed.", tUnit));
        }

        /****************************************************************/
        /* IF Settings                                                  */
        /****************************************************************/

        if(err == TM_OK)
        {
            /* Set IF */
            err = tmddTDA18273SetIF_Freq(tUnit, pObj->Std_Array[pObj->StandardMode].IF - pObj->Std_Array[pObj->StandardMode].CF_Offset);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIF_Freq(0x%08X) failed.", tUnit));
        }

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273GetStandardMode:
//
// DESCRIPTION: Get the standard mode of this device.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273GetStandardMode
(
    tmUnitSelect_t              tUnit,          /* I: Unit number */
    tmTDA18273StandardMode_t    *pStandardMode  /* O: Standard mode of this device */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    if(pStandardMode == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        // pObj initialization
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Get standard mode */
        *pStandardMode = pObj->StandardMode;

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273SetPLDReadImmunity:
//
// DESCRIPTION: Set the PLD Read immunity algorithm based on PLD_CC.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273SetPLDReadImmunity
(
    tmUnitSelect_t              tUnit,          /* I: Unit number */
    Bool                        PLDReadImmunity /* I: PLD Read immunity algorithm ON or OFF */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    // pObj initialization
    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // store PLD Read immunity algorithm 
        pObj->PLD_CC_algorithm = PLDReadImmunity;

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273GetPLDReadImmunity:
//
// DESCRIPTION: Get the PLD Read immunity algorithm based on PLD_CC.
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TM_OK
//
// NOTES:
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273GetPLDReadImmunity
(
    tmUnitSelect_t              tUnit,           /* I: Unit number */
    Bool*                       PLDReadImmunity  /* O: PLD Read immunity algorithm ON or OFF */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    if(PLDReadImmunity == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        // pObj initialization
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // Get PLD Read immunity algorithm
        *PLDReadImmunity = pObj->PLD_CC_algorithm;

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273SetRf:
//
// DESCRIPTION: Calculate i2c I2CMap & write in TDA18273
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TDA18273_ERR_BAD_PARAMETER
//              TMBSL_ERR_IIC_ERR
//              TM_OK
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273SetRf
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uRF     /* I: RF frequency in hertz */
)
{    
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    UInt8               value_Sigma_Delta_Byte_5 = 0x0; /* PLL not bypassed */
    UInt8               uSubAddress_Sigma_Delta_Byte_5 = 0x56;
    UInt8               uNbData_Sigma_Delta_Byte_5 = 1;

    /* pObj initialization */
    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
	{
        /* Set the RF frequency */
		pObj->uRF = uRF;

        if(err == TM_OK)
        {
            /* Set power state ON */
            err = TDA18273SetPowerState(pObj, tmddTDA18273_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273SetPowerState(0x%08X, PowerNormalMode) failed.", tUnit));
        }

        if (err == TM_OK)
        {
            /* Enable Calc_PLL algorithm by putting PLL in automatic mode */
            err = POBJ_SRVFUNC_SIO.Write(pObj->tUnitW, 1, &uSubAddress_Sigma_Delta_Byte_5, uNbData_Sigma_Delta_Byte_5, &value_Sigma_Delta_Byte_5);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273SetRf(0x%08X) Write Expert Sigma_Delta_Byte_5 failed.", tUnit));
        }

        /* Set the proper settings depending on the standard & RF frequency */

        /****************************************************************/
        /* AGC TOP Settings                                             */
        /****************************************************************/
        if(err == TM_OK)
        {
            /* Set AGC3 TOP I2C */
            if ((pObj->uRF + pObj->Std_Array[pObj->StandardMode].CF_Offset) < tmTDA18273_AGC3_TOP_I2C_FREQ_LIM)
            {
                err = tmddTDA18273SetRFAGC_Top(tUnit, pObj->Std_Array[pObj->StandardMode].AGC3_TOP_I2C_Low_Band);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFAGC_Top(0x%08X) failed.", tUnit));
            }
            else
            {
                err = tmddTDA18273SetRFAGC_Top(tUnit, pObj->Std_Array[pObj->StandardMode].AGC3_TOP_I2C_High_Band);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFAGC_Top(0x%08X) failed.", tUnit));
            }
        }

        if(err == TM_OK)
        {
            /* Set AGC3 Adapt TOP */
            if ((pObj->uRF + pObj->Std_Array[pObj->StandardMode].CF_Offset) < tmTDA18273_AGC3_ADAPT_TOP_FREQ_LIM)
            {
                err = tmddTDA18273SetRFAGC_Adapt_TOP(tUnit, pObj->Std_Array[pObj->StandardMode].AGC3_Adapt_TOP_Low_Band);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFAGC_Adapt_TOP(0x%08X) failed.", tUnit));
            }
            else
            {
                err = tmddTDA18273SetRFAGC_Adapt_TOP(tUnit, pObj->Std_Array[pObj->StandardMode].AGC3_Adapt_TOP_High_Band);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFAGC_Adapt_TOP(0x%08X) failed.", tUnit));
            }
        }
        /* End of settings */

        /* Setting bansplit parameters */
        if (err == TM_OK)
        {
            err = TDA18273OverrideBandsplit(pObj);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273OverrideBandsplit(0x%08X) failed.", tUnit));
        }

        /* Implement PLD read immunity against interferers: first pass before channel change */
        if(err == TM_OK)
        {
            err = TDA18273FirstPassPLD_CC(pObj);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273FirstPassPLD_CC(0x%08X) failed.", tUnit));
        }

        /* Set RF frequency */
        if(err == TM_OK)
        {
            err = TDA18273SetRF(pObj, pObj->uRF + pObj->Std_Array[pObj->StandardMode].CF_Offset);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273SetRF(0x%08X) failed.", tUnit));
        }

        /* Implement PLD read immunity against interferers: last pass after channel change */
        if(err == TM_OK)
        {
            err = TDA18273LastPassPLD_CC(pObj);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273LastPassPLD_CC(0x%08X) failed.", tUnit));
        }

        /* Bypass ROM settings for wireless filters */
        if(err == TM_OK)
        {
            err = TDA18273OverrideWireless(pObj);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273OverrideWireless(0x%08X) failed.", tUnit));
        }
		
        (void)TDA18273MutexRelease(pObj);
	}

    return err;
}


//-------------------------------------------------------------------------------------
// FUNCTION:    tmbslTDA18273GetRf:
//
// DESCRIPTION: Get the frequency programmed in the tuner
//
// RETURN:      TMBSL_ERR_TUNER_BAD_UNIT_NUMBER
//              TDA18273_ERR_NOT_INITIALIZED
//              TM_OK
//
// NOTES:       The value returned is the one stored in the Object
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmbslTDA18273GetRf
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puRF    /* O: RF frequency in hertz */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err  = TM_OK;

    if(puRF == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    //------------------------------
    // test input parameters
    //------------------------------
    // pObj initialization
    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Get RF */
        *puRF = pObj->uRF;

        (void)TDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* tmbslTDA18273Reset                                                         */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273Reset
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* pObj initialization */
    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }
    
    if(err == TM_OK)
    {
        /* Wait for XtalCal End */
        err = TDA18273WaitXtalCal_End(pObj, 100, 5);

        if(err == TM_OK)
        {
            UInt8 minorVersion;
            UInt8 uBytes[TDA18273_I2C_MAP_NB_BYTES];

            /* initialize tuner = update I2C map */
            err = tmddTDA18273Read(tUnit, 0, TDA18273_I2C_MAP_NB_BYTES, &uBytes[0]);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Read(0x%08X) failed.", tUnit));

            /****************************************************/
            /* Change POR values that are common to ES1 and ES2 */
            /****************************************************/
            if(err == TM_OK)
            {
                /* Up_Step_Ovld: POR = 1 -> 0 */
                err = tmddTDA18273SetUp_Step_Ovld(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetUp_Step_Ovld(0x%08X, 0) failed.", tUnit));
            }

            if (err == TM_OK)
            {
                /* PLD_CC_Enable: POR = 1 -> 0 */
                err = tmddTDA18273SetPLD_CC_Enable(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPLD_CC_Enable(0x%08X, 0) failed.", tUnit));
            }

            if (err == TM_OK)
            {
                /* 
                    "RFCAL_Offset0", "0"
                    "RFCAL_Offset1", "0"
                    "RFCAL_Offset2", "0"
                    "RFCAL_Offset3", "0"
                    "RFCAL_Offset4", "3"
                    "RFCAL_Offset5", "0"
                    "RFCAL_Offset6", "3"
                    "RFCAL_Offset7", "3"
                    "RFCAL_Offset8", "1"
                */
                err = tmddTDA18273SetRFCAL_Offset0(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset0(0x%08X, 0) failed.", tUnit));

                err = tmddTDA18273SetRFCAL_Offset1(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset1(0x%08X, 0) failed.", tUnit));

                err = tmddTDA18273SetRFCAL_Offset2(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset2(0x%08X, 0) failed.", tUnit));

                err = tmddTDA18273SetRFCAL_Offset3(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset3(0x%08X, 0) failed.", tUnit));

                err = tmddTDA18273SetRFCAL_Offset4(tUnit, 3);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset4(0x%08X, 0) failed.", tUnit));

                err = tmddTDA18273SetRFCAL_Offset5(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset5(0x%08X, 0) failed.", tUnit));

                err = tmddTDA18273SetRFCAL_Offset6(tUnit, 3);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset6(0x%08X, 0) failed.", tUnit));

                err = tmddTDA18273SetRFCAL_Offset7(tUnit, 3);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset7(0x%08X, 0) failed.", tUnit));

                err = tmddTDA18273SetRFCAL_Offset8(tUnit, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRFCAL_Offset8(0x%08X, 0) failed.", tUnit));
            }

            if (err == TM_OK)
            {
                /* PLD_Temp_Enable: POR = 1 -> 0 */ 
                err = tmddTDA18273SetPLD_Temp_Enable(tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPLD_Temp_Enable(0x%08X, 0) failed.", tUnit));
            }

            if (err == TM_OK)
            {
                /* Power Down Vsync Management: POR = 0 -> 1 */
                err = tmddTDA18273SetPD_Vsync_Mgt(tUnit, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPD_Vsync_Mgt(0x%08X, 0) failed.", tUnit));
            }

            /**********************************/
            /* Change POR values only for ES1 */
            /**********************************/
            if(err == TM_OK)
            {
                err = tmddTDA18273GetMinorRevision(tUnit, &minorVersion);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetMinorRevision(0x%08X, 0) failed.", tUnit));

                if(err == TM_OK)
                {
                    /* ES1 version */
                    if (minorVersion == 0)
                    {
                        UInt8 value_Regulators_byte;
                        UInt8 uSubAddress_Regulators_byte = 0x58;
                        UInt8 uNbData_Regulators_byte = 1;

                        err = POBJ_SRVFUNC_SIO.Read(pObj->tUnitW, 1, &uSubAddress_Regulators_byte, uNbData_Regulators_byte, &value_Regulators_byte);
                        if(err == TM_OK)
                        {
                            /* Set RF_Reg to 10 (= 3 V) */
                            value_Regulators_byte &= 0xF3;
                            value_Regulators_byte |= 0x8;

                            err = POBJ_SRVFUNC_SIO.Write(pObj->tUnitW, 1, &uSubAddress_Regulators_byte, uNbData_Regulators_byte, &value_Regulators_byte);
                        } 

                        if (err == TM_OK)
                        {
                            /* Wireless bypass and filter 2.4 - 2.6 GHz by default */
                            err = tmddTDA18273SetW_Filter_Bypass(tUnit, 1);
                            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter_Bypass(0x%08X, 0) failed.", tUnit));
                            err = tmddTDA18273SetW_Filter(tUnit, 0);
                            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter(0x%08X, 0) failed.", tUnit));
                        }

                        if (err == TM_OK)
                        {
                            /* Wireless Filter Enable: POR = 1 -> 0 */
                            err = tmddTDA18273SetW_Filter_Enable(tUnit, 0);
                            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter_Enable(0x%08X, 0) failed.", tUnit));
                        }
                    }
                }
            }

            /**********************************/
            /* Change POR values only for ES2 */
            /**********************************/
#if 0
            if(err == TM_OK)
            {
                err = tmddTDA18273GetMinorRevision(tUnit, &minorVersion);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetMinorRevision(0x%08X, 0) failed.", tUnit));

                if(err == TM_OK)
                {
                    /* ES2 version */
                    if (minorVersion == 1)
                    {

                    }
                }
            }
#endif

            /* Launch tuner calibration      */
            if(err == TM_OK)
            {
                /* set IRQ_clear */
                err = tmddTDA18273SetIRQ_Clear(tUnit, 0x1F);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIRQ_clear(0x%08X, 0x1F) failed.", tUnit));
            }

            if(err == TM_OK)
            {
                /* set power state on */
                err = TDA18273SetPowerState(pObj, tmddTDA18273_PowerNormalMode);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273SetPowerState(0x%08X, PowerNormalMode) failed.", tUnit));
            }

            /* Set RF_CAL_AV */
            err = tmddTDA18273SetTriggerMSM(tUnit, MSM_CALC_PLL | 
                                                   MSM_RC_CAL | 
                                                   MSM_IR_CAL_IMAGE | 
                                                   MSM_IR_CAL_LOOP | 
                                                   MSM_RF_CAL);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetTriggerMSM(0x%08X) failed.", tUnit));

            if(pObj->bIRQWait)
            {
                if(err == TM_OK)
                {
                    err = tmddTDA18273WaitIRQ(tUnit, 1500, 50, 0x1F);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273WaitIRQ(0x%08X) failed.", tUnit));
                }
            }
        }

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmbslTDA18273GetIF                                                         */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273GetIF
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puIF    /* O: IF Frequency in hertz */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    if(puIF == Null)
        err = TDA18273_ERR_BAD_PARAMETER;
    
    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *puIF = pObj->Std_Array[pObj->StandardMode].IF - pObj->Std_Array[pObj->StandardMode].CF_Offset;

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmbslTDA18273GetCF_Offset                                                  */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273GetCF_Offset(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32*         puOffset    /* O: Center frequency offset in hertz */
    )
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    if(puOffset == Null)
        err = TDA18273_ERR_BAD_PARAMETER;
    
    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *puOffset = pObj->Std_Array[pObj->StandardMode].CF_Offset;

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmbslTDA18273GetLockStatus                                                 */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273GetLockStatus
(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    tmbslFrontEndState_t*   pLockStatus /* O: PLL Lock status */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8 uValue, uValueLO;

    if( pLockStatus == Null )
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
        
        if(err == TM_OK)
        {
            err =  tmddTDA18273GetLO_Lock(tUnit, &uValueLO);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetLO_Lock(0x%08X) failed.", tUnit));
        }
        if(err == TM_OK)
        {
            err =  tmddTDA18273GetIRQ_status(tUnit, &uValue);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetIRQ_status(0x%08X) failed.", tUnit));
    
            uValue = uValue & uValueLO;
        }
        if(err == TM_OK)
        {
            *pLockStatus =  (uValue)? tmbslFrontEndStateLocked : tmbslFrontEndStateNotLocked;
        }
        else
        {
            *pLockStatus = tmbslFrontEndStateUnknown;  
        }
    
        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmbslTDA18273GetPowerLevel                                                 */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273GetPowerLevel
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8*         pPowerLevel  /* O: Power Level in dBµV */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               minorVersion;

    if(pPowerLevel == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *pPowerLevel = 0;

        /* Implement PLD CC algorithm to increase PLD read immunity to interferer */
        /*
            -PLD CC ON.
            -Wait 40ms.
            -PLD read standard.
            -PLD CC OFF. 
        */

        /* Do the algorithm only if asked and not in analog mode */
        if (
            (pObj->PLD_CC_algorithm == True) &&
            (pObj->StandardMode != tmTDA18273_FM_Radio) &&
            (pObj->StandardMode != tmTDA18273_ANLG_MN) &&
            (pObj->StandardMode != tmTDA18273_ANLG_B) &&
            (pObj->StandardMode != tmTDA18273_ANLG_GH) &&
            (pObj->StandardMode != tmTDA18273_ANLG_I) &&
            (pObj->StandardMode != tmTDA18273_ANLG_DK) &&
            (pObj->StandardMode != tmTDA18273_ANLG_L) &&
            (pObj->StandardMode != tmTDA18273_ANLG_LL)
           )
        {            
            /* PLD_CC_Enable: 1 */
            err = tmddTDA18273SetPLD_CC_Enable(tUnit, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPLD_CC_Enable(0x%08X, 1) failed.", tUnit));

            /* Wait 40 ms */
            err = TDA18273Wait(pObj, 40);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273Wait(0x%08X) failed.", tUnit));
        }

        err = tmddTDA18273GetPower_Level(tUnit, pPowerLevel);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetPower_Level(0x%08X) failed.", tUnit));

        if (err == TM_OK)
        {
            err = tmddTDA18273GetMinorRevision(tUnit, &minorVersion);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetMinorRevision(0x%08X, 0) failed.", tUnit));

            /* Apply correction on PLD read for ES2 */
            if ((err == TM_OK) && (minorVersion == 1))
            {
                /* RF <= 145.408 MHz, then apply minus 3 dB */
                if ((pObj->uRF + pObj->Std_Array[pObj->StandardMode].CF_Offset) <= 145408000)
                {
                    /* 1 step = 0.5 dB */
                    if (*pPowerLevel >= 6)
                        *pPowerLevel -= 6;
                    else
                        *pPowerLevel = 0;
                }
            }
        }

        /* Finish the algorithm only if asked and not in analog mode */
        if (
            (pObj->PLD_CC_algorithm == True) &&
            (pObj->StandardMode != tmTDA18273_FM_Radio) &&
            (pObj->StandardMode != tmTDA18273_ANLG_MN) &&
            (pObj->StandardMode != tmTDA18273_ANLG_B) &&
            (pObj->StandardMode != tmTDA18273_ANLG_GH) &&
            (pObj->StandardMode != tmTDA18273_ANLG_I) &&
            (pObj->StandardMode != tmTDA18273_ANLG_DK) &&
            (pObj->StandardMode != tmTDA18273_ANLG_L) &&
            (pObj->StandardMode != tmTDA18273_ANLG_LL)
           )
        {            
            /* PLD_CC_Enable: 0 */
            err = tmddTDA18273SetPLD_CC_Enable(tUnit, 0);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPLD_CC_Enable(0x%08X, 0) failed.", tUnit));
        }

        (void)TDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* tmbslTDA18273GetRSSI                                                       */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273GetRSSI
(
     tmUnitSelect_t  tUnit,  //  I: Unit number
     UInt8*          puValue //  O: Address of the variable to output item value
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    /* test the parameter */
    if (puValue == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = TDA18273GetRSSI(pObj, puValue);

        (void)TDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* tmbslTDA18273SetIRQWait                                                    */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273SetIRQWait
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool            bWait   /* I: Determine if we need to wait IRQ in driver functions */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    err = TDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Initialize the BSL parameter */
        pObj->bIRQWait = bWait;

        (void)TDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* tmbslTDA18273GetIRQWait                                                    */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273GetIRQWait
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool*           pbWait  /* O: Determine if we need to wait IRQ in driver functions */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    if(pbWait == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *pbWait = pObj->bIRQWait;

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmbslTDA18273GetIRQ                                                        */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273GetIRQ
(
    tmUnitSelect_t  tUnit  /* I: Unit number */,
    Bool*           pbIRQ  /* O: IRQ triggered */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    if(pbIRQ == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *pbIRQ = 0;

        err = tmddTDA18273GetIRQ_status(tUnit, (UInt8 *)pbIRQ);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetIRQ_status(0x%08X) failed.", tUnit));

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmbslTDA18273WaitIRQ                                                       */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273WaitIRQ
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeOut for IRQ wait */
    UInt32          waitStep,   /* I: wait step */
    UInt8           irqStatus   /* I: IRQs to wait */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = tmddTDA18273WaitIRQ(tUnit, timeOut, waitStep, irqStatus);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273WaitIRQ(0x%08X) failed.", tUnit));

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmbslTDA18273GetXtalCal_End                                                */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273GetXtalCal_End
(
    tmUnitSelect_t  tUnit  /* I: Unit number */,
    Bool*           pbXtalCal_End  /* O: XtalCal_End triggered */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    if(pbXtalCal_End == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *pbXtalCal_End = 0;

        err = tmddTDA18273GetMSM_XtalCal_End(tUnit, (UInt8 *)pbXtalCal_End);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetMSM_XtalCal_End(0x%08X) failed.", tUnit));

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmbslTDA18273WaitXtalCal_End                                               */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273WaitXtalCal_End
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeOut for IRQ wait */
    UInt32          waitStep   /* I: wait step */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = tmddTDA18273WaitXtalCal_End(tUnit, timeOut, waitStep);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273WaitXtalCal_End(0x%08X) failed.", tUnit));

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

/* Only used in debug platform, and not in embedded platform */
#ifdef TMFL_TDA18273_RFFILTER_DEBUG

/*============================================================================*/
/* tmbslTDA18273CheckRFFilterRobustness                                       */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18273CheckRFFilterRobustness 
(
 tmUnitSelect_t                         tUnit,      /* I: Unit number */
 ptmTDA18273RFFilterRating              rating      /* O: RF Filter rating */
 )
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        UInt8  rfcal_log_0 = 0;
        UInt8  rfcal_log_2 = 0;
        UInt8  rfcal_log_3 = 0;
        UInt8  rfcal_log_5 = 0;
        UInt8  rfcal_log_6 = 0;
        UInt8  rfcal_log_8 = 0;
        UInt8  rfcal_log_9 = 0;
        UInt8  rfcal_log_11 = 0;

        double   VHFLow_0 = 0.0;
        double   VHFLow_1 = 0.0;
        double   VHFHigh_0 = 0.0;
        double   VHFHigh_1 = 0.0;
        double   UHFLow_0 = 0.0;
        double   UHFLow_1 = 0.0;
        double   UHFHigh_0 = 0.0;
        double   UHFHigh_1 = 0.0;

        err = tmddTDA18273Getrfcal_log_0(tUnit, &rfcal_log_0);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Getrfcal_log_0(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            err = tmddTDA18273Getrfcal_log_2(tUnit, &rfcal_log_2);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Getrfcal_log_2(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddTDA18273Getrfcal_log_3(tUnit, &rfcal_log_3);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Getrfcal_log_3(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddTDA18273Getrfcal_log_5(tUnit, &rfcal_log_5);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Getrfcal_log_5(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddTDA18273Getrfcal_log_6(tUnit, &rfcal_log_6);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Getrfcal_log_6(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddTDA18273Getrfcal_log_8(tUnit, &rfcal_log_8);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Getrfcal_log_8(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddTDA18273Getrfcal_log_9(tUnit, &rfcal_log_9);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Getrfcal_log_9(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            err = tmddTDA18273Getrfcal_log_11(tUnit, &rfcal_log_11);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273Getrfcal_log_11(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        { 
            if (rfcal_log_0 & 0x80)
            {
                rating->VHFLow_0_Margin = 0;    
                rating->VHFLow_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Error;
            }
            else
            {
                // VHFLow_0
                VHFLow_0 = 100 * (45 - 39.8225 * (1 + (0.31 * (rfcal_log_0 < 64 ? rfcal_log_0 : rfcal_log_0 - 128)) / 1.0 / 100.0)) / 45.0;
                rating->VHFLow_0_Margin = 0.0024 * VHFLow_0 * VHFLow_0 * VHFLow_0 - 0.101 * VHFLow_0 * VHFLow_0 + 1.629 * VHFLow_0 + 1.8266;
                if (rating->VHFLow_0_Margin >= 0) 
                {
                    rating->VHFLow_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_High;
                }
                else
                {
                    rating->VHFLow_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Low;
                }
            }

            if (rfcal_log_2 & 0x80)
            {
                rating->VHFLow_1_Margin = 0;    
                rating->VHFLow_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Error;
            }
            else
            {
                // VHFLow_1
                VHFLow_1 = 100 * (152.1828 * (1 + (1.53 * (rfcal_log_2 < 64 ? rfcal_log_2 : rfcal_log_2 - 128)) / 1.0 / 100.0) - (144.896 - 6)) / (144.896 - 6); 
                rating->VHFLow_1_Margin = 0.0024 * VHFLow_1 * VHFLow_1 * VHFLow_1 - 0.101 * VHFLow_1 * VHFLow_1 + 1.629 * VHFLow_1 + 1.8266;
                if (rating->VHFLow_1_Margin >= 0)
                {
                    rating->VHFLow_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_High;
                }
                else
                {
                    rating->VHFLow_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Low;
                }
            }

            if (rfcal_log_3 & 0x80)
            {
                rating->VHFHigh_0_Margin = 0;    
                rating->VHFHigh_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Error;
            }
            else
            {
                // VHFHigh_0    
                VHFHigh_0 = 100 * ((144.896 + 6) - 135.4063 * (1 + (0.27 * (rfcal_log_3 < 64 ? rfcal_log_3 : rfcal_log_3 - 128)) / 1.0 / 100.0)) / (144.896 + 6);
                rating->VHFHigh_0_Margin = 0.0024 * VHFHigh_0 * VHFHigh_0 * VHFHigh_0 - 0.101 * VHFHigh_0 * VHFHigh_0 + 1.629 * VHFHigh_0 + 1.8266;
                if (rating->VHFHigh_0_Margin >= 0)
                {
                    rating->VHFHigh_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_High;
                }
                else
                {
                    rating->VHFHigh_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Low;
                }
            }

            if (rfcal_log_5 & 0x80)
            {
                rating->VHFHigh_1_Margin = 0;    
                rating->VHFHigh_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Error;
            }
            else
            {
                // VHFHigh_1
                VHFHigh_1 = 100 * (383.1455 * (1 + (0.91 * (rfcal_log_5 < 64 ? rfcal_log_5 : rfcal_log_5 - 128)) / 1.0 / 100.0) - (367.104 - 8)) / (367.104 - 8);
                rating->VHFHigh_1_Margin = 0.0024 * VHFHigh_1 * VHFHigh_1 * VHFHigh_1 - 0.101 * VHFHigh_1 * VHFHigh_1 + 1.629 * VHFHigh_1 + 1.8266;
                if (rating->VHFHigh_1_Margin >= 0)
                {
                    rating->VHFHigh_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_High;
                }
                else
                {
                    rating->VHFHigh_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Low;
                }
            }

            if (rfcal_log_6 & 0x80)
            {
                rating->UHFLow_0_Margin = 0;    
                rating->UHFLow_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Error;
            }
            else
            {
                // UHFLow_0
                UHFLow_0 = 100 * ((367.104 + 8) - 342.6224 * (1 + (0.21 * (rfcal_log_6 < 64 ? rfcal_log_6 : rfcal_log_6 - 128)) / 1.0 / 100.0)) / (367.104 + 8);
                rating->UHFLow_0_Margin = 0.0024 * UHFLow_0 * UHFLow_0 * UHFLow_0 - 0.101 * UHFLow_0 * UHFLow_0 + 1.629 * UHFLow_0 + 1.8266;
                if (rating->UHFLow_0_Margin >= 0)
                {
                    rating->UHFLow_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_High;
                }
                else
                {
                    rating->UHFLow_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Low;
                }
            }

            if (rfcal_log_8 & 0x80)
            {
                rating->UHFLow_1_Margin = 0;    
                rating->UHFLow_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Error;
            }
            else
            {
                // UHFLow_1
                UHFLow_1 = 100 * (662.5595 * (1 + (0.33 * (rfcal_log_8 < 64 ? rfcal_log_8 : rfcal_log_8 - 128)) / 1.0 / 100.0) - (624.128 - 2)) / (624.128 - 2);
                rating->UHFLow_1_Margin = 0.0024 * UHFLow_1 * UHFLow_1 * UHFLow_1 - 0.101 * UHFLow_1 * UHFLow_1 + 1.629 * UHFLow_1 + 1.8266;
                if (rating->UHFLow_1_Margin >= 0)
                {
                    rating->UHFLow_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_High;
                }
                else
                {
                    rating->UHFLow_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Low;
                }
            }

            if (rfcal_log_9 & 0x80)
            {
                rating->UHFHigh_0_Margin = 0;    
                rating->UHFHigh_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Error;
            }
            else
            {
                // UHFHigh_0
                UHFHigh_0 = 100 * ((624.128 + 2) - 508.2747 * (1 + (0.23 * (rfcal_log_9 < 64 ? rfcal_log_9 : rfcal_log_9 - 128)) / 1.0 / 100.0)) / (624.128 + 2);
                rating->UHFHigh_0_Margin = 0.0024 * UHFHigh_0 * UHFHigh_0 * UHFHigh_0 - 0.101 * UHFHigh_0 * UHFHigh_0 + 1.629 * UHFHigh_0 + 1.8266;
                if (rating->UHFHigh_0_Margin >= 0)
                {
                    rating->UHFHigh_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_High;
                }
                else
                {
                    rating->UHFHigh_0_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Low;
                }
            }

            if (rfcal_log_11 & 0x80)
            {
                rating->UHFHigh_1_Margin = 0;    
                rating->UHFHigh_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Error;
            }
            else
            {
                // UHFHigh_1
                UHFHigh_1 = 100 * (947.8913 * (1 + (0.3 * (rfcal_log_11 < 64 ? rfcal_log_11 : rfcal_log_11 - 128)) / 1.0 / 100.0) - (866 - 14)) / (866 - 14);
                rating->UHFHigh_1_Margin = 0.0024 * UHFHigh_1 * UHFHigh_1 * UHFHigh_1 - 0.101 * UHFHigh_1 * UHFHigh_1 + 1.629 * UHFHigh_1 + 1.8266;            
                if (rating->UHFHigh_1_Margin >= 0)
                {
                    rating->UHFHigh_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_High;
                }
                else
                {
                    rating->UHFHigh_1_RFFilterRobustness =  tmTDA18273RFFilterRobustness_Low;
                }
            }
        }

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

#endif

/*============================================================================*/
/* tmbslTDA18273RFFineTuning                                                  */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273RFFineTuning
(
    tmUnitSelect_t tUnit,      /* I: Unit number */
    Int8           step        /* I: step (-1, +1) */
)
{
    ptmTDA18273Object_t pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Registers description */
    struct
    {
        union
        {
            UInt8 Main_Post_Divider_byte;
            struct
            {
                #ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:1;
                UInt8 LOPostDiv:3;
                UInt8 LOPresc:4;
                #else
                UInt8 LOPresc:4;
                UInt8 LOPostDiv:3;
                UInt8 UNUSED_I0_D0:1;
                #endif
            }bF;
        }uBx51;

        union
        {
            UInt8 Sigma_delta_byte_1;
            struct
            {
                #ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:1;
                UInt8 LO_Int:7;
                #else
                UInt8 LO_Int:7;
                UInt8 UNUSED_I0_D0:1;
                #endif
            }bF;
        }uBx52;

        union
        {
            UInt8 Sigma_delta_byte_2;
            struct
            {
                #ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:1;
                UInt8 LO_Frac_2:7;
                #else
                UInt8 LO_Frac_2:7;
                UInt8 UNUSED_I0_D0:1;
                #endif
            }bF;
        }uBx53;

        union
        {
            UInt8 Sigma_delta_byte_3;
            struct
            {
                UInt8 LO_Frac_1:8;
            }bF;
        }uBx54;

        union
        {
            UInt8 Sigma_delta_byte_4;
            struct
            {
                UInt8 LO_Frac_0:8;
            }bF;
        }uBx55;
    } pll_data;

    /* Manual control of the PLL */
    UInt8 uSubAddress_Sigma_Delta_Byte_5 = 0x56;
    UInt8 uNbData_Sigma_Delta_Byte_5 = 1;
    UInt8 uValue_Sigma_Delta_Byte_5 = 0x3; /* LO_Calc_Disable only & N_K_correct_manual*/

    /* LOPostDiv, LOPres, LO_Int, LO_Frac[8..22] */
    UInt8 uSubAddress_Main_Post_Divider_byte_Sigma_Delta_Byte_1_3 = 0x51;
    UInt8 uNbData_Main_Post_Divider_byte_Sigma_Delta_Byte_1_3 = 4;

    /* LO max = 974000 KHz*/
    UInt32 FLOmax = 974000;

    /* LO wanted = RF wanted + IF in KHz */
    UInt32 LO;

    /* Algorithm that calculates PostDiv */
    UInt32 PostDiv;
    UInt32 FLOmax_temp;

    /* Algorithm that calculates Prescaler */
    UInt8 Prescaler;
    UInt32 LO_temp;
    UInt32 FVCOmax;

    /* Algorithm that calculates N_K */
    UInt32 FVCO;
    UInt32 N_K_prog;

    /* Algorithm that calculates N, K corrected */
    UInt32 Nprime;
    UInt32 KforceK0_1;
    UInt32 K2msb;
    UInt32 N0;
    UInt32 Nm1;
    UInt32 N_int;
    UInt32 K_int;

    UInt8 i;

    if(err == TM_OK)
    {
        err = TDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = TDA18273MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Write the offset into 4 equal steps of 15.625 KHz = 62.5 KHz*/
        for (i=0; i < 4; i++)
        {
            /* Calculate wanted LO = RF + IF */
            pObj->uRF += step*15625;
            LO = (pObj->uRF + pObj->Std_Array[pObj->StandardMode].IF)/1000;

            /* Calculate PostDiv */
            PostDiv = 1;
            FLOmax_temp = FLOmax;
            while ((FLOmax_temp / 2) > LO)
            {
                PostDiv *= 2;
                FLOmax_temp /= 2;
            }

            /* Decode PostDiv */
            switch (PostDiv)
            {
                case 1:
                    pll_data.uBx51.bF.LOPostDiv = 1;
                    break;
                case 2:
                    pll_data.uBx51.bF.LOPostDiv = 2;
                    break;
                case 4:
                    pll_data.uBx51.bF.LOPostDiv = 3;
                    break;
                case 8:
                    pll_data.uBx51.bF.LOPostDiv = 4;
                    break;
                case 16:
                    pll_data.uBx51.bF.LOPostDiv = 5;
                    break;
                default:
                    err = TDA18273_ERR_BAD_PARAMETER;
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273RFFineTuning(0x%08X) LO_PostDiv value is wrong.", tUnit));
                    break;
            }
            
            if(err == TM_OK)
            {
                /* Calculate Prescaler */
                LO_temp = LO * PostDiv;
                FVCOmax = FLOmax * 7;
                Prescaler = 13;
                while ((LO_temp * Prescaler) > FVCOmax)
                {
                    Prescaler--;
                }

                /* Affect register */
                pll_data.uBx51.bF.LOPresc = Prescaler;

                /* Calculate N_K_Prog */
                FVCO = LO * Prescaler * PostDiv;
                N_K_prog = (FVCO * 128) / 125;

                /* Calculate N & K corrected values */
                Nprime = N_K_prog & 0xFF0000;

                /* Force LSB to 1 */
                KforceK0_1 = 2*(((N_K_prog - Nprime) << 7) / 2) + 1;
                
                /* Check MSB bit around 2 */
                K2msb = KforceK0_1 >> 21;
                if (K2msb < 1)
                {
                    N0 = 1;
                }
                else
                {
                    if (K2msb >= 3)
                    {
                        N0 = 1;
                    }
                    else
                    {
                        N0 = 0;
                    }
                }
                if (K2msb < 1)
                {
                    Nm1 = 1;
                }
                else
                {
                    Nm1 = 0;
                }

                /* Calculate N */
                N_int = (2 * ((Nprime >> 16) - Nm1) + N0) - 128;

                /* Calculate K */
                if (K2msb < 1)
                {
                    K_int = KforceK0_1 + (2 << 21);
                }
                else
                {
                    if (K2msb >= 3)
                    {
                        K_int = KforceK0_1 - (2 << 21);
                    }
                    else
                    {
                        K_int = KforceK0_1;
                    }
                }

                /* Affect registers */
                pll_data.uBx55.bF.LO_Frac_0 = (UInt8)(K_int & 0xFF);
                pll_data.uBx54.bF.LO_Frac_1 = (UInt8)((K_int >> 8) & 0xFF);
                pll_data.uBx53.bF.LO_Frac_2 = (UInt8)((K_int >> 16) & 0xFF);
                pll_data.uBx52.bF.LO_Int = (UInt8)(N_int & 0xFF);

                /* Force manual selection mode : 0x3 at @0x56 */
                err = pObj->sRWFunc.Write(pObj->tUnitW, 1, &uSubAddress_Sigma_Delta_Byte_5, uNbData_Sigma_Delta_Byte_5, &uValue_Sigma_Delta_Byte_5);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273RFFineTuning(0x%08X) write to 0x56 is failing.", tUnit));

                if(err == TM_OK)
                {
                    /* Write bytes 0x51-0x54 in one shot */
                    err = pObj->sRWFunc.Write(pObj->tUnitW, 1, 
                                              &uSubAddress_Main_Post_Divider_byte_Sigma_Delta_Byte_1_3, 
                                              uNbData_Main_Post_Divider_byte_Sigma_Delta_Byte_1_3, 
                                              (UInt8*)&pll_data);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273RFFineTuning(0x%08X) write to 0x51-0x54 is failing.", tUnit));
                }
            }
        }

        (void)TDA18273MutexRelease(pObj);
    }

    return err;
}

//-----------------------------------------------------------------------------
// Internal functions:
//-----------------------------------------------------------------------------
//

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273GetRSSI
//
// DESCRIPTION: This function reads RSSI value from IC
//
// RETURN:      tmErrorCode_t
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273GetRSSI
(
    ptmTDA18273Object_t pObj,   /* I: Driver object */
    UInt8              *puValue /* O: RSSI value */
)
{
    tmErrorCode_t err = TM_OK;

    /* test the parameter */
    if (puValue == Null)
        err = TDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Set IRQ_clear */
        err = tmddTDA18273SetIRQ_Clear(pObj->tUnit, 0x12);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIRQ_clear(0x%08X, 0x0C) failed.", pObj->tUnit));

        if(err == TM_OK)
        {
            *puValue = 0;

            /* Set RSSI MEASURE */
            err = tmddTDA18273SetTriggerMSM(pObj->tUnit, MSM_RSSI_MEAS);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetTriggerMSM(0x%08X) failed.", pObj->tUnit));

            if(pObj->bIRQWait)
            {
                if(err == TM_OK)
                {
                    err = tmddTDA18273WaitIRQ(pObj->tUnit, 50, 5, 0x0C);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273WaitIRQ(0x%08X) failed.", pObj->tUnit));
                }
            }

            if(err == TM_OK)
            {
                /* Read RSSI */
                err = tmddTDA18273GetRSSI(pObj->tUnit, puValue);

                if (err != TM_OK)
                {
                    err = TDA18273_ERR_HW_FAILED;
                }
            }
        }
    }

    // Return value
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273SetRF
//
// DESCRIPTION: This function sets the RF frequency written in pObj
//
// RETURN:      tmErrorCode_t
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273SetRF
(
    ptmTDA18273Object_t pObj,   /* I: Driver object */
    UInt32              freq    /* I: Wanted frequency */
)
{
    tmErrorCode_t err = TM_OK;

    /* Set IRQ_clear */
    err = tmddTDA18273SetIRQ_Clear(pObj->tUnit, 0x0C);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetIRQ_clear(0x%08X, 0x0C) failed.", pObj->tUnit));

    /* Set RF */
    err = tmddTDA18273SetRF_Freq(pObj->tUnit, freq);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetRF_Freq(0x%08X) failed.", pObj->tUnit));

    if(err == TM_OK)
    {
        /* Set RF_CAL_AV */
        err = tmddTDA18273SetTriggerMSM(pObj->tUnit, MSM_CALC_PLL | MSM_RF_CAL_AV);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetTriggerMSM(0x%08X) failed.", pObj->tUnit));

        if(pObj->bIRQWait)
        {
            if(err == TM_OK)
            {
                err = tmddTDA18273WaitIRQ(pObj->tUnit, 50, 5, 0x0C);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273WaitIRQ(0x%08X) failed.", pObj->tUnit));
            }
        }
    }

    if(err == TM_OK)
    {
        /* Override ICP */
        err = TDA18273OverrideICP(pObj, freq);
    }

    // Return value
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273OverrideICP
//
// DESCRIPTION: This function overrides charge pump current
//
// RETURN:      tmErrorCode_t
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273OverrideICP
(
    ptmTDA18273Object_t pObj,   /* I: Driver object */
    UInt32              freq    /* I: Wanted frequency */
)
{
    tmErrorCode_t err = TM_OK;

    UInt8  value_LOPostdiv;
    UInt8  value_LOPrescaler;
    UInt32 FVCO;
    
    UInt8  uSubAddress_Main_Post_Divider_byte = 0x51;
    UInt8  uNbData_Main_Post_Divider_byte = 1;
    UInt8  value_Main_Post_Divider_byte;

    UInt8  uSubAddress_Charge_pump_byte = 0x64;
    UInt8  uNbData_Charge_pump_byte = 1;
    UInt8  value_Charge_pump_byte = 0;

    /*
    if fvco<6352 MHz ==> icp = 150µ (register = 01b)
    if fvco<6592 MHz ==> icp = 300µ (register = 10b)
    500µA elsewhere (register 00b)

    Reminder : fvco = postdiv*presc*(RFfreq+IFfreq) 
    */

    /* Get Postdiv & Prescaler */
    err = POBJ_SRVFUNC_SIO.Read(pObj->tUnit, 1, &uSubAddress_Main_Post_Divider_byte, uNbData_Main_Post_Divider_byte, &value_Main_Post_Divider_byte);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273OverrideICP(0x%08X) Read Expert Main_Post_Divider_byte failed.", pObj->tUnit));

    if(err == TM_OK)
    {
        /* Get values */
        value_LOPostdiv = (value_Main_Post_Divider_byte >> 4) & 0x7;
        value_LOPrescaler = value_Main_Post_Divider_byte & 0xF;

        /* Decode PostDiv */
        switch (value_LOPostdiv)
        {
            case 1:
                value_LOPostdiv = 1;
                break;
            case 2:
                value_LOPostdiv = 2;
                break;
            case 3:
                value_LOPostdiv = 4;
                break;
            case 4:
                value_LOPostdiv = 8;
                break;
            case 5:
                value_LOPostdiv = 16;
                break;
            default:
                err = TDA18273_ERR_BAD_PARAMETER;
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273OverrideICP(0x%08X) LOPostDiv value is wrong.", pObj->tUnit));
                break;
        }
        
        /* Calculate FVCO in MHz*/
        FVCO = value_LOPostdiv * value_LOPrescaler * ((freq + pObj->Std_Array[pObj->StandardMode].IF - pObj->Std_Array[pObj->StandardMode].CF_Offset) / 1000000);

        /* Set correct ICP */

        /* Set ICP_bypass bit */
        value_Charge_pump_byte |= 0x80; 

        /* Set ICP bits (2 LSB) to 0 */
        value_Charge_pump_byte &= 0xFC;

        if (FVCO < 6352)
        {
            /* Set ICP to 01 (= 150)*/
            value_Charge_pump_byte |= 0x1;
        }
        else
        {
            if (FVCO < 6592)
            {
                /* Set ICP to 10 (= 300)*/
                value_Charge_pump_byte |= 0x2;
            }
            else
            {
                /* Set ICP to 00 (= 500)*/
                value_Charge_pump_byte |= 0x0;
            }
        }
        
        /* Write Charge_pump_byte */
        err = POBJ_SRVFUNC_SIO.Write(pObj->tUnit, 1, &uSubAddress_Charge_pump_byte, uNbData_Charge_pump_byte, &value_Charge_pump_byte);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273OverrideICP(0x%08X) Write Expert Charge_pump_byte failed.", pObj->tUnit));
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273OverrideBandsplit
//
// DESCRIPTION: This function overrides bansplit parameters
//
// RETURN:      tmErrorCode_t
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273OverrideBandsplit
(
    ptmTDA18273Object_t pObj
)
{
    tmErrorCode_t   err  = TM_OK;
    UInt8           selected_bandsplit;
    UInt32          realRF = pObj->uRF + pObj->Std_Array[pObj->StandardMode].CF_Offset; /* Wanted RF */

    /* Setting PSM bandsplit at -3.9 mA for some RF frequencies */
    err = tmddTDA18273GetBandsplit_Filter_SubBand(pObj->tUnit, &selected_bandsplit);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetBandsplit_Filter_SubBand(0x%08X) failed.", pObj->tUnit));
    
    if (err == TM_OK)
    {
        switch (selected_bandsplit)
        {
            case 0:
            {
                /* LPF0 133MHz - LPF1 206MHz - HPF0 422MHz */
                if (realRF < 133000000)
                {
                    /* Set PSM bandsplit at -3.9 mA */
                    err = tmddTDA18273SetPSM_Bandsplit_Filter(pObj->tUnit, 3);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPSM_Bandsplit_Filter(0x%08X) failed.", pObj->tUnit));
                }
                else
                {
                    /* Set PSM bandsplit at nominal */
                    err = tmddTDA18273SetPSM_Bandsplit_Filter(pObj->tUnit, 2);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPSM_Bandsplit_Filter(0x%08X) failed.", pObj->tUnit));
                }
            }
            break;

            case 1:
            {
                /* LPF0 139MHz - LPF1 218MHz - HPF0 446MHz */
                if (realRF < 139000000)
                {
                    /* Set PSM bandsplit at -3.9 mA */
                    err = tmddTDA18273SetPSM_Bandsplit_Filter(pObj->tUnit, 3);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPSM_Bandsplit_Filter(0x%08X) failed.", pObj->tUnit));
                }
                else
                {
                    /* Set PSM bandsplit at nominal */
                    err = tmddTDA18273SetPSM_Bandsplit_Filter(pObj->tUnit, 2);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPSM_Bandsplit_Filter(0x%08X) failed.", pObj->tUnit));
                }
            }
            break;

            case 2:
            {
                /* LPF0 145MHz - LPF1 230MHz - HPF0 470MHz */
                if (realRF < 145000000)
                {
                    /* Set PSM bandsplit at -3.9 mA */
                    err = tmddTDA18273SetPSM_Bandsplit_Filter(pObj->tUnit, 3);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPSM_Bandsplit_Filter(0x%08X) failed.", pObj->tUnit));
                }
                else
                {
                    /* Set PSM bandsplit at nominal */
                    err = tmddTDA18273SetPSM_Bandsplit_Filter(pObj->tUnit, 2);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPSM_Bandsplit_Filter(0x%08X) failed.", pObj->tUnit));
                }
            }
            break;

            case 3:
            {
                /* LPF0 151MHz - LPF1 242MHz - HPF0 494MHz */
                if (realRF < 151000000)
                {
                    /* Set PSM bandsplit at -3.9 mA */
                    err = tmddTDA18273SetPSM_Bandsplit_Filter(pObj->tUnit, 3);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPSM_Bandsplit_Filter(0x%08X) failed.", pObj->tUnit));
                }
                else
                {
                    /* Set PSM bandsplit at nominal */
                    err = tmddTDA18273SetPSM_Bandsplit_Filter(pObj->tUnit, 2);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPSM_Bandsplit_Filter(0x%08X) failed.", pObj->tUnit));
                }
            }
            break;
        }
    }    

    // Return value
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273OverrideWireless
//
// DESCRIPTION: This function override the wireless settings
//
// RETURN:      tmErrorCode_t
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273OverrideWireless
(
    ptmTDA18273Object_t pObj
)
{
    tmErrorCode_t   err  = TM_OK;
    UInt32          uRealRF;
    UInt8           minorVersion;

    err = tmddTDA18273GetMinorRevision(pObj->tUnit, &minorVersion);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetMinorRevision(0x%08X, 0) failed.", pObj->tUnit));

    /* Bypass ROM for wireless filters for ES2 */
    if ((err == TM_OK) && (minorVersion == 1))
    {
        /* Set wireless filters ON for ES2 */
        err = tmddTDA18273SetW_Filter_Enable(pObj->tUnit, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter_Enable(0x%08X) failed.", pObj->tUnit));

        /* WF7 = 1.7GHz - 1.98GHz */
        /* WF8 = 1.98GHz - 2.1GHz */
        /* WF9 = 2.1GHz - 2.4GHz */
        /* For all frequencies requiring WF7 and WF8, add -8% shift */
        /* For all frequencies requiring WF9, change to WF8 and add +4% shift */
        uRealRF = pObj->uRF + pObj->Std_Array[pObj->StandardMode].CF_Offset;

        /* Check for filter WF7 & WF8 */
        if (
            ((uRealRF > 336000000) && (uRealRF < 431000000)) ||
            ((uRealRF > 563500000) && (uRealRF < 721000000))
           )
        {
            /* ROM is selecting WF7 or WF8 */

            /* Apply -8% shift */
            err = tmddTDA18273SetW_Filter_Offset(pObj->tUnit, 3);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter_Offset(0x%08X) failed.", pObj->tUnit));
        }
        else
        {
            /* Check for filter WF9 */
            if (
                ((uRealRF > 474000000) && (uRealRF < 536000000)) ||
                ((uRealRF > 794000000) && (uRealRF < 866000000))
               )
            {
                /* ROM is selecting WF9 */

                /* Bypass to WF8 */
                err = tmddTDA18273SetW_Filter(pObj->tUnit, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter(0x%08X) failed.", pObj->tUnit));

                if(err == TM_OK)
                {
                    err = tmddTDA18273SetW_Filter_Bypass(pObj->tUnit, 1);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter_Bypass(0x%08X) failed.", pObj->tUnit));
                }

                /* Apply +4% shift */
                if(err == TM_OK)
                {
                    err = tmddTDA18273SetW_Filter_Offset(pObj->tUnit, 0);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter_Offset(0x%08X) failed.", pObj->tUnit));
                }
            }
            else
            {
                /* Let ROM do the job */
                err = tmddTDA18273SetW_Filter_Bypass(pObj->tUnit, 0);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter_Bypass(0x%08X) failed.", pObj->tUnit));

                if(err == TM_OK)
                {
                    err = tmddTDA18273SetW_Filter(pObj->tUnit, 0);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter(0x%08X) failed.", pObj->tUnit));
                }

                if(err == TM_OK)
                {
                    err = tmddTDA18273SetW_Filter_Offset(pObj->tUnit, 1);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetW_Filter_Offset(0x%08X) failed.", pObj->tUnit));
                }
            }
        }
    }

    // Return value
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273FirstPassPLD_CC
//
// DESCRIPTION: This function implements the first pass of the PLD_CC algorithm
//
// RETURN:      tmErrorCode_t
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273FirstPassPLD_CC
(
    ptmTDA18273Object_t pObj
)
{
    tmErrorCode_t   err  = TM_OK;

    /* Implement PLD CC algorithm to increase PLD read immunity to interferer */
    /* 
        - set AGCK mode to 8ms.
        - PLD CC ON.
        - Set RF
        - Loop of Read of AGC Lock:
            - If ((AGClock green) or  TIMEOUT(200ms)) then next Step Else (Wait 1ms and next Read)
        - Wait 20ms.
        - PLD CC OFF.
        - Wait 1ms.
        - set AGCK mode back to initial mode
    */

    /* Do the algorithm only if asked and not in analog mode */
    if (
        (pObj->PLD_CC_algorithm == True) &&
        (pObj->StandardMode != tmTDA18273_FM_Radio) &&
        (pObj->StandardMode != tmTDA18273_ANLG_MN) &&
        (pObj->StandardMode != tmTDA18273_ANLG_B) &&
        (pObj->StandardMode != tmTDA18273_ANLG_GH) &&
        (pObj->StandardMode != tmTDA18273_ANLG_I) &&
        (pObj->StandardMode != tmTDA18273_ANLG_DK) &&
        (pObj->StandardMode != tmTDA18273_ANLG_L) &&
        (pObj->StandardMode != tmTDA18273_ANLG_LL)
       )
    {
        /* Set AGCK Time Constant */
        err = tmddTDA18273SetAGCK_Mode(pObj->tUnit, tmTDA18273_AGCK_Time_Constant_8_192ms);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGCK_Mode(0x%08X) failed.", pObj->tUnit));
        
        if(err == TM_OK)
        {
            /* PLD_CC_Enable: 1 */
            err = tmddTDA18273SetPLD_CC_Enable(pObj->tUnit, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPLD_CC_Enable(0x%08X, 1) failed.", pObj->tUnit));
        }
    }

    // Return value
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273LastPassPLD_CC
//
// DESCRIPTION: This function implements the last pass of the PLD_CC algorithm
//
// RETURN:      tmErrorCode_t
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273LastPassPLD_CC
(
    ptmTDA18273Object_t pObj
)
{
    tmErrorCode_t   err  = TM_OK;

    /* Finish the algorithm only if asked and not in analog mode */
    if (
        (pObj->PLD_CC_algorithm == True) &&
        (pObj->StandardMode != tmTDA18273_FM_Radio) &&
        (pObj->StandardMode != tmTDA18273_ANLG_MN) &&
        (pObj->StandardMode != tmTDA18273_ANLG_B) &&
        (pObj->StandardMode != tmTDA18273_ANLG_GH) &&
        (pObj->StandardMode != tmTDA18273_ANLG_I) &&
        (pObj->StandardMode != tmTDA18273_ANLG_DK) &&
        (pObj->StandardMode != tmTDA18273_ANLG_L) &&
        (pObj->StandardMode != tmTDA18273_ANLG_LL)
       )
    {
        UInt8 counter = 200; /* maximum 200 loops so max wait time = 200ms */
        UInt8 agcs_lock = 0;

        /* Get initial AGCs_Lock */
        if(err == TM_OK)
        {
            err = tmddTDA18273GetAGCs_Lock(pObj->tUnit, &agcs_lock);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetAGCs_Lock(0x%08X) failed.", pObj->tUnit));
        }

        /* Perform the loop to detect AGCs_Lock = 1 or error or timeout */
        while((err == TM_OK) && ((--counter)>0) && (agcs_lock == 0))
        {
            err = tmddTDA18273GetAGCs_Lock(pObj->tUnit, &agcs_lock);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273GetAGCs_Lock(0x%08X) failed.", pObj->tUnit));

            if(agcs_lock == 1)
            {
                /* Exit without waiting */
                break;
            }

            /* Wait 1 ms */
            err = TDA18273Wait(pObj, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273Wait(0x%08X) failed.", pObj->tUnit));
        }

        /* Wait 20 ms */
        if(err == TM_OK)
        {
            err = TDA18273Wait(pObj, 20);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273Wait(0x%08X) failed.", pObj->tUnit));
        }

        /* PLD_CC_Enable: 0 */
        if(err == TM_OK)
        {
            err = tmddTDA18273SetPLD_CC_Enable(pObj->tUnit, 0);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPLD_CC_Enable(0x%08X, 0) failed.", pObj->tUnit));
        }
        
        /* Wait 1 ms */
        if(err == TM_OK)
        {
            err = TDA18273Wait(pObj, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TDA18273Wait(0x%08X) failed.", pObj->tUnit));
        }

        /* Set AGCK Time Constant */
        if(err == TM_OK)
        {
            err = tmddTDA18273SetAGCK_Mode(pObj->tUnit, pObj->Std_Array[pObj->StandardMode].AGCK_Time_Constant);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetAGCK_Mode(0x%08X) failed.", pObj->tUnit));
        }
    }

    // Return value
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273SetPowerState
//
// DESCRIPTION: This function set the requested power state
//
// RETURN:      tmErrorCode_t
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273SetPowerState
(
    ptmTDA18273Object_t pObj, 
    tmddTDA18273PowerState_t powerState
)
{
    tmErrorCode_t   err  = TM_OK;

    /* Set digital clock mode to 16 Mhz before entering standby */
    switch (powerState)
    {
        case tmddTDA18273_PowerStandbyWithXtalOn:
        case tmddTDA18273_PowerStandby:
        {
            /* Set 16 Mhz Xtal clock */
            err = tmddTDA18273SetDigital_Clock_Mode(pObj->tUnit, 0);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetDigital_Clock_Mode(0x%08X, 16 Mhz xtal clock) failed.", pObj->tUnit));
        }
        break;

        default:
            /* Do nothing */
        break;
    }

    if(err == TM_OK)
    {
        err = tmddTDA18273SetPowerState(pObj->tUnit, (tmddTDA18273PowerState_t)powerState);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetPowerState(0x%08X) failed.", pObj->tUnit));
    }

    /* Set digital clock mode to sub-LO if normal mode is entered */
    if(err == TM_OK)
    {
        switch (powerState)
        {
            case tmddTDA18273_PowerNormalMode:
            {
                /* Set sub-LO */
                err = tmddTDA18273SetDigital_Clock_Mode(pObj->tUnit, 3);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetDigital_Clock_Mode(0x%08X, sigma delta clock) failed.", pObj->tUnit));
            }     
            break;

            default:
                /* Do nothing */
            break;
        }
    }

    /* Return value */
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    TDA18273Wait
//
// DESCRIPTION: This function waits for requested time
//
// RETURN:      True or False
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
static tmErrorCode_t 
TDA18273Wait
(
    ptmTDA18273Object_t pObj,   /* I: Driver object */
    UInt32              Time   /*  I: Time to wait for */
)
{
    tmErrorCode_t   err  = TM_OK;

    // wait Time ms
    err = POBJ_SRVFUNC_STIME.Wait(pObj->tUnit, Time);

    // Return value
    return err;
}

/*============================================================================*/
/* TDA18273MutexAcquire                                                       */
/*============================================================================*/
extern tmErrorCode_t
TDA18273MutexAcquire
(
 ptmTDA18273Object_t    pObj,
 UInt32                 timeOut
 )
{
    tmErrorCode_t       err = TM_OK;

    if(pObj->sMutex.Acquire != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Acquire(pObj->pMutex, timeOut);
    }

    return err;
}

/*============================================================================*/
/* TDA18273MutexRelease                                                       */
/*============================================================================*/
extern tmErrorCode_t
TDA18273MutexRelease
(
 ptmTDA18273Object_t    pObj
 )
{
    tmErrorCode_t       err = TM_OK;

    if(pObj->sMutex.Release != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Release(pObj->pMutex);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    ddTDA18273WaitXtalCal_End                                     */
/*                                                                            */
/* DESCRIPTION: Wait for MSM_XtalCal_End to trigger                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
TDA18273WaitXtalCal_End
(
    ptmTDA18273Object_t   pObj,         /* I: Instance object */
    UInt32                  timeOut,    /* I: timeout */
    UInt32                  waitStep    /* I: wait step */
)
{     
    tmErrorCode_t   err  = TM_OK;
    UInt32          counter = timeOut/waitStep; /* Wait max timeOut/waitStepms */
    UInt8           uMSM_XtalCal_End = 0;

    while(err == TM_OK && (--counter)>0)
    {
        err = tmddTDA18273GetMSM_XtalCal_End(pObj->tUnit, &uMSM_XtalCal_End);

        if(uMSM_XtalCal_End == 1)
        {
            /* MSM_XtalCal_End triggered => Exit */
            break;
        }

        TDA18273Wait(pObj, waitStep);
    }

    if(counter == 0)
    {
        err = ddTDA18273_ERR_NOT_READY;
    }

    return err;
}
