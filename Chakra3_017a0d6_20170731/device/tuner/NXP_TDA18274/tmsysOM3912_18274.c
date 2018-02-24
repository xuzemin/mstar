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
* \file          tmsysOM3912_63.c
*                %version: CFR_FEAP#6 %
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
-------------|-----------|-------|-------|-----------------------------------
-------------|-----------|-------|-------|-----------------------------------
\endverbatim
*
*/


/*============================================================================*/
/*                   STANDARD INCLUDE FILES                                   */
/*============================================================================*/


/*============================================================================*/
/*                   PROJECT INCLUDE FILES                                    */
/*============================================================================*/
#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"
#include "tmsysFrontEndTypes.h"
#include "tmUnitParams.h"

#include "tmsysOM3912_18274.h"

/*============================================================================*/
/*                   MACRO DEFINITION                                         */
/*============================================================================*/


/*============================================================================*/
/*                   TYPE DEFINITION                                          */
/*============================================================================*/



/*============================================================================*/
/*                   PUBLIC VARIABLES DEFINITION                              */
/*============================================================================*/

/*============================================================================*/
/*                   STATIC VARIABLES DECLARATIONS                            */
/*============================================================================*/

/*============================================================================*/
/*                       EXTERN FUNCTION PROTOTYPES                           */
/*============================================================================*/


/*============================================================================*/
/*                   STATIC FUNCTIONS DECLARATIONS                            */
/*============================================================================*/
static tmErrorCode_t OM3912TunerSetStandardMode(
    tmUnitSelect_t              tUnit,          /*  I: Unit number */
    tmbslFrontEndStandardMode_t StandardMode    /*  I: Standard mode of this device */
);


/*============================================================================*/
/*                   PUBLIC FUNCTIONS DEFINITIONS                             */
/*============================================================================*/



/*============================================================================*/
/*                   PROJECT INCLUDE FILES                                    */
/*============================================================================*/


/*============================================================================*/
/*                   TYPE DEFINITION                                          */
/*============================================================================*/


/*============================================================================*/
/*                   STATIC VARIABLES DECLARATIONS                            */
/*============================================================================*/


/*============================================================================*/
/*                   PUBLIC FUNCTIONS DECLARATIONS                            */
/*============================================================================*/



/*============================================================================*/
/*                   STATIC FUNCTIONS DECLARATIONS                            */
/*============================================================================*/

/*============================================================================*/
/*                   PUBLIC FUNCTIONS DEFINITIONS                             */
/*============================================================================*/


/*============================================================================*/
/* tmsysOM3912Init                                                            */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912Init
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
)
{
    tmErrorCode_t        err = TM_OK;

    err = tmbslTDA182I4_Open(tUnit, psSrvFunc);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_Open(0x%08X) failed.", tUnit));

    return err;
}

/*============================================================================*/
/* tmsysOM3912DeInit                                                          */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912DeInit
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    tmErrorCode_t        err = TM_OK;

	err = tmbslTDA182I4_Close(tUnit);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_Close(0x%08X) failed.", tUnit));

    return err;
}

/*============================================================================*/
/* tmsysOM3912Reset                                                           */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912Reset
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    tmErrorCode_t err = TM_OK;
    err = tmbslTDA182I4_HwInit(tUnit);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_HwInit(0x%08X) failed.", tUnit));

    return err;
}

/*============================================================================*/
/* tmsysOM3912SetPowerState                                                   */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912SetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    tmPowerState_t  ePowerState /* I: Power state of the device */
)
{
    tmErrorCode_t        err = TM_OK;

    err = tmbslTDA182I4_SetPowerState( tUnit, ePowerState);

    return err;
}

/*============================================================================*/
/* tmsysOM3912SetPowerState                                                   */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912GetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    ptmPowerState_t pPowerState /* O: Power state of the device */
)
{
    tmErrorCode_t        err = TM_OK;

	err = tmbslTDA182I4_GetPowerState(tUnit, pPowerState);

    return err;
}

/*============================================================================*/
/* tmsysOM3912SendRequest                                                     */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912SendRequest
(
    tmUnitSelect_t  tUnit,              /* I: FrontEnd unit number */
    pVoid           pTuneRequest,       /* I/O: Tune Request Structure pointer */
    UInt32          dwTuneRequestSize,  /* I: Tune Request Structure size */
    tmTuneReqType_t tTuneReqType        /* I: Tune Request Type */
)
{
	UNUSED(dwTuneRequestSize);
	UNUSED(tTuneReqType);
    tmErrorCode_t        err = TM_OK;
	ptmTunerOnlyRequest_t pTunerOnlyRequest = (ptmTunerOnlyRequest_t)(pTuneRequest);
    tmbslFrontEndState_t        eTunerPLLLock = tmbslFrontEndStateUnknown;
    err = tmbslTDA182I4_SetPowerState( tUnit, tmPowerOn);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_SetPowerState(0x%08X, PowerOn) failed.", pObj->tUnitTuner));

    /************************************************************************/
    /* Program Tuner                                                        */
    /************************************************************************/

    if(err == TM_OK)
    {
        /* Set Tuner Standard mode */
		
        err = OM3912TunerSetStandardMode(tUnit, (tmbslFrontEndStandardMode_t)pTunerOnlyRequest->dwStandard);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "OM3912TunerSetStandardMode(0x%08X, %d) failed.", tUnit, pTunerOnlyRequest->dwStandard);
        }
    }

    if(err == TM_OK)
    {
        /* Set Tuner RF */
        err = tmbslTDA182I4_SetRF(tUnit, pTunerOnlyRequest->dwFrequency);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA182I4_SetRF(0x%08X, %d) failed.", tUnit, pTunerOnlyRequest->dwFrequency);
        }
    }
    
    if(err == TM_OK)
    {
        /* Get Tuner PLL Lock status */
		err = tmbslTDA182I4_GetLockStatus(tUnit, &eTunerPLLLock);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_GetLockStatus(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE, "Tuner(0x%08X) PLL Lock:%d.", tUnit, eTunerPLLLock);
    }
    if(err == TM_OK)
    {
        pTunerOnlyRequest->eTunerLock = (tmsysFrontEndState_t)eTunerPLLLock;
    }

    /* Print the result of the Manager function */
    switch(eTunerPLLLock)
    {
        case tmbslFrontEndStateLocked:
            if(err == TM_OK)
            {
                tmDBGPRINTEx(DEBUGLVL_TERSE, "Tuner 0x%08X LOCKED.", tUnit);
            }
            if(err == TM_OK)
            {
                tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
                tmDBGPRINTEx(DEBUGLVL_TERSE, " OM3912SetFrequency(0x%08X) found following parameters:", tUnit);
                tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
                tmDBGPRINTEx(DEBUGLVL_TERSE, "     Frequency:      %d Hz", pTunerOnlyRequest->dwFrequency);
                tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
            }

            break;

        case tmbslFrontEndStateNotLocked:
            if(err == TM_OK)
            {
                tmDBGPRINTEx(DEBUGLVL_TERSE, "Tuner 0x%08X NOT LOCKED.", tUnit);
            }
            break;

        case tmbslFrontEndStateSearching:
        default:
            if(err == TM_OK)
            {
                tmDBGPRINTEx(DEBUGLVL_ERROR, "Tuner 0x%08X TIMEOUT.", tUnit);
            }
            break;
    }


    return err;
}

/*============================================================================*/
/* tmsysOM3912GetLockStatus                                                   */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912GetLockStatus
(
    tmUnitSelect_t          tUnit,      /* I: FrontEnd unit number */
    tmsysFrontEndState_t*   pLockStatus /* O: Lock status */
)
{
    tmErrorCode_t        err = TM_OK;
    tmbslFrontEndState_t lockStatus = tmbslFrontEndStateUnknown;

    /* Get tuner PLL Lock status */
    err = tmbslTDA182I4_GetLockStatus(tUnit, &lockStatus);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_GetLockStatus(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
       *pLockStatus = (tmsysFrontEndState_t)lockStatus;
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3912GetSignalStrength                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912GetSignalStrength
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    UInt32          *pStrength  /* I/O: Signal Strength pointer */
)
{
    tmErrorCode_t       err = TM_OK;
    err = tmbslTDA182I4_GetPowerLevel(tUnit, (UInt8*)pStrength);

    return err;
}

/*============================================================================*/
/* tmsysOM3912GetSignalQuality                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912GetSignalQuality
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    UInt32          *pQuality   /* I/O: Signal Quality pointer */
)
{
	UNUSED(tUnit);
	pQuality = NULL;
    return OM3912_ERR_NOT_SUPPORTED;
}

static tmErrorCode_t
OM3912TunerSetStandardMode(
    tmUnitSelect_t              tUnit,          /*  I: Unit number */
    tmbslFrontEndStandardMode_t StandardMode    /*  I: Standard mode of this device */
)
{
    tmErrorCode_t          err = TM_OK;
    TDA182I4StandardMode_t tunerStandardMode;

    switch (StandardMode)
    {
        case tmbslFrontEndStandardModeUnknown:
            tunerStandardMode = TDA182I4_StandardMode_Unknown;
            break;
        case tmbslFrontEndStandardQAM6MHz:
            tunerStandardMode = TDA182I4_QAM_6MHz;
            break;
        case tmbslFrontEndStandardQAM8MHz:
            tunerStandardMode = TDA182I4_QAM_8MHz;
            break;
        case tmbslFrontEndStandardATSC6MHz:
            tunerStandardMode = TDA182I4_ATSC_6MHz;
            break;
        case tmbslFrontEndStandardISDBT6MHz:
            tunerStandardMode = TDA182I4_ISDBT_6MHz;
            break;
        case tmbslFrontEndStandardDVBT1_7MHz:
            tunerStandardMode = TDA182I4_DVBT_1_7MHz;
            break;
        case tmbslFrontEndStandardDVBT6MHz:
            tunerStandardMode = TDA182I4_DVBT_6MHz;
            break;
        case tmbslFrontEndStandardDVBT7MHz:
            tunerStandardMode = TDA182I4_DVBT_7MHz;
            break;
        case tmbslFrontEndStandardDVBT8MHz:
            tunerStandardMode = TDA182I4_DVBT_8MHz;
            break;
        case tmbslFrontEndStandardDVBT10MHz:
            tunerStandardMode = TDA182I4_DVBT_10MHz;
            break;
        case tmbslFrontEndStandardDMBT6MHz:
            tunerStandardMode = TDA182I4_DMBT_6MHz;
            break;
        case tmbslFrontEndStandardDMBT8MHz:
            tunerStandardMode = TDA182I4_DMBT_8MHz;
            break;
        case tmbslFrontEndStandardFMRadio:
            tunerStandardMode = TDA182I4_FM_Radio;
            break;
        case tmbslFrontEndStandardANLGMN:
            tunerStandardMode = TDA182I4_ANLG_MN;
            break;
        case tmbslFrontEndStandardANLGB:
            tunerStandardMode = TDA182I4_ANLG_B;
            break;
        case tmbslFrontEndStandardANLGGH:
            tunerStandardMode = TDA182I4_ANLG_GH;
            break;
        case tmbslFrontEndStandardANLGI:
            tunerStandardMode = TDA182I4_ANLG_I;
            break;
        case tmbslFrontEndStandardANLGDK:
            tunerStandardMode = TDA182I4_ANLG_DK;
            break;
        case tmbslFrontEndStandardANLGL:
            tunerStandardMode = TDA182I4_ANLG_L;
            break;
        case tmbslFrontEndStandardANLGLL:
            tunerStandardMode = TDA182I4_ANLG_LL;
            break;
        case tmbslFrontEndStandardScanning:
            tunerStandardMode = TDA182I4_Scanning;
            break;
        case tmbslFrontEndStandardScanXpress:
            tunerStandardMode = TDA182I4_ScanXpress;
            break;
        default:
            tunerStandardMode = TDA182I4_StandardMode_Max;
            break;
    }

    /* Set Tuner Standard mode */
    err = tmbslTDA182I4_SetStandardMode(tUnit, tunerStandardMode);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I4_SetStandardMode(0x%08X) failed.", tUnit));

    return err;
}

