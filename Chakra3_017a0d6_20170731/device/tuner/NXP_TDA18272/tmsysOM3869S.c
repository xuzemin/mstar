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
* \file          tmsysOM3869S_63.c
*                %version: 11 %
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
9-JULY-2007  | A.TANT    |       |       | CREATION OF TDA10048 ARCHITECTURE 2.0.0
-------------|-----------|-------|-------|-----------------------------------
|           |       |       |
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

#include "tmbslTDA18272.h"
#include "tmddTDA182I2.h"

#include "tmsysOM3869S.h"
#include "tmsysOM3869Slocal.h"
#include "tmsysOM3869SInstance.h"

/*============================================================================*/
/*                   MACRO DEFINITION                                         */
/*============================================================================*/

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(ar)        (sizeof(ar)/sizeof((ar)[0]))
#endif // !defined(SIZEOF_ARRAY)
#define UNUSEOM3869(x) x=x

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
  static tmErrorCode_t OM3869SInit(tmUnitSelect_t tUnit);
  static tmErrorCode_t OM3869SReset(tmUnitSelect_t tUnit);
  static tmErrorCode_t OM3869SSetFrequency(tmUnitSelect_t tUnit, ptmTunerOnlyRequest_t pTuneRequest);


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
/*============================================================================*/
/* tmsysOM3869SGetSWVersion                                                 */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SGetSWVersion
(
    ptmsysSWVersion_t   pSWVersion  /* O: Receives SW Version  */
)
{
    tmErrorCode_t   err = TM_OK;
    static char     OM3869SName[] = "tmsysOM3869S\0";
    static char     TDA18272Name[] = "tmbslTDA18272\0";

    pSWVersion->arrayItemsNumber = 2;
    pSWVersion->swVersionArray[0].pName = (char *)OM3869SName;
    pSWVersion->swVersionArray[0].nameBufSize = sizeof(OM3869SName);
    
    pSWVersion->swVersionArray[0].swVersion.compatibilityNr = OM3869S_SYS_COMP_NUM;
    pSWVersion->swVersionArray[0].swVersion.majorVersionNr = OM3869S_SYS_MAJOR_VER;
    pSWVersion->swVersionArray[0].swVersion.minorVersionNr = OM3869S_SYS_MINOR_VER;
    
    pSWVersion->swVersionArray[1].pName = (char *)TDA18272Name;
    pSWVersion->swVersionArray[1].nameBufSize = sizeof(TDA18272Name);
    err = tmbslTDA182I2GetSWVersion(&pSWVersion->swVersionArray[1].swVersion);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2GetSWVersion failed."));

    return err;
}

/*============================================================================*/
/* tmsysOM3869SInit                                                         */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SInit
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
)
{
    ptmOM3869SObject_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    // pObj initialization
    err = OM3869SGetInstance(tUnit, &pObj);

    /* check driver state */
    if (err == TM_OK || err == OM3869S_ERR_NOT_INITIALIZED)
    {
        if (pObj != Null && pObj->init == True)
        {
            err = OM3869S_ERR_NOT_INITIALIZED;
        }
        else 
        {
            /* initialize the Object */
            if (pObj == Null)
            {
                err = OM3869SAllocInstance(tUnit, &pObj);
                if (err != TM_OK || pObj == Null)
                {
                    err = OM3869S_ERR_NOT_INITIALIZED;        
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

                pObj->tUnitTDA182I2 = GET_INDEX_TUNIT(tUnit)|UNIT_PATH_TYPE_VAL(tmOM3869SUnitDeviceTypeTDA182I2);

                pObj->init = True;
                err = TM_OK;

                err = OM3869SInit(tUnit);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SInit(0x%08X) failed.", tUnit));
           }
        }
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SDeInit                                                          */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SDeInit
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869SObject_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    /************************************************************************/
    /* DeInitialize TDA182I2 low layer setup                                */
    /************************************************************************/
    if(err == TM_OK)
    {
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
        
        err = tmbslTDA182I2DeInit(pObj->tUnitTDA182I2);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2DeInit(0x%08X) failed.", pObj->tUnitTDA182I2));
    }

 
    err = OM3869SDeAllocInstance(tUnit);

    return err;
}

/*============================================================================*/
/* tmsysOM3869SReset                                                        */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SReset
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869SObject_t    pObj = Null;
    tmErrorCode_t           err = OM3869S_ERR_NOT_INITIALIZED;

    /* check input parameters */
    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869SMutexAcquire(pObj, OM3869S_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = OM3869SReset(tUnit);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SReset(0x%08X) failed.", tUnit));

        (void)OM3869SMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SSetPowerState                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SSetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    tmPowerState_t  ePowerState /* I: Power state of the device */
)
{
    ptmOM3869SObject_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869SMutexAcquire(pObj, OM3869S_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        switch(ePowerState)
        {
        case tmPowerOn:
            if (err == TM_OK)
            {
                pObj->powerState = ePowerState;

                /* Set TDA182I2 power state to Normal Mode */
                err = tmbslTDA182I2SetPowerState(pObj->tUnitTDA182I2, tmTDA182I2_PowerNormalMode);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2SetPowerState(0x%08X, tmPowerOn) failed.", pObj->tUnitTDA182I2));
            }
            break;

        case tmPowerStandby:
            if (err == TM_OK)
            {
                pObj->powerState = ePowerState;

                /* Set TDA182I2 power state to standby with Xtal and Loop Through*/
                err = tmbslTDA182I2SetPowerState(pObj->tUnitTDA182I2, tmTDA182I2_PowerStandbyWithLNAOnAndWithXtalOn);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2SetPowerState(0x%08X, tmPowerStandby) failed.", pObj->tUnitTDA182I2));
            }
            break;

        case tmPowerSuspend:
        case tmPowerOff:
        default:
            err = OM3869S_ERR_NOT_SUPPORTED;
            break;
        }

        if (err == TM_OK)
        {
            pObj->lastTuneReqType = TRT_UNKNOWN;
        }

        (void)OM3869SMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SSetPowerState                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SGetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    ptmPowerState_t pPowerState /* O: Power state of the device */
)
{
    ptmOM3869SObject_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869SMutexAcquire(pObj, OM3869S_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *pPowerState = pObj->powerState;

        (void)OM3869SMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SSendRequest                                                  */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SSendRequest
(
    tmUnitSelect_t  tUnit,              /* I: FrontEnd unit number */
    pVoid           pTuneRequest,       /* I/O: Tune Request Structure pointer */
    UInt32          dwTuneRequestSize,  /* I: Tune Request Structure size */
    tmTuneReqType_t tTuneReqType        /* I: Tune Request Type */
)
{
    ptmOM3869SObject_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    if(err == TM_OK)
    {
        err = OM3869SGetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));
    }

    // check pointer
    if( !pTuneRequest )
    {
        tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Invalid Pointer!");
        err = OM3869S_ERR_BAD_PARAMETER;
    }

    //if(err == TM_OK  && !pObj->resetDone)
    //{
    //    err = OM3869S_ERR_NOT_INITIALIZED;
    //}

    if(err == TM_OK)
    {
        err = OM3869SMutexAcquire(pObj, OM3869S_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        switch(tTuneReqType)
        {
        case TRT_TUNER_ONLY:
            if( dwTuneRequestSize != sizeof(tmTunerOnlyRequest_t) )
            {
                tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Bad parameter");
                err = OM3869S_ERR_BAD_PARAMETER;
            }
            else
            {
                if (err == TM_OK)
                {
                    ptmTunerOnlyRequest_t pTunerOnlyRequest = (ptmTunerOnlyRequest_t)(pTuneRequest);

                    err = OM3869SSetFrequency(tUnit, pTunerOnlyRequest);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Error: OM3869SSetFrequency failed"));
                }
            }
            break;

        default:
            tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Unsupported tune request");
            err = OM3869S_ERR_NOT_SUPPORTED;
            break;
        }

        (void)OM3869SMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SSetI2CSwitchState                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SSetI2CSwitchState
(
    tmUnitSelect_t                  tUnit,  /* I: FrontEnd unit number */
    tmsysFrontEndI2CSwitchState_t   eState  /* I: I2C switch state */
)
{
    UNUSEOM3869(tUnit);
    UNUSEOM3869(eState);
    return OM3869S_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3869SGetI2CSwitchState                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SGetI2CSwitchState
(
    tmUnitSelect_t                  tUnit,
    tmsysFrontEndI2CSwitchState_t*  peState,
    UInt32*                         puI2CSwitchCounter
)
{
    UNUSEOM3869(tUnit);
    UNUSEOM3869(peState);
    UNUSEOM3869(puI2CSwitchCounter);
    return OM3869S_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3869SGetLockStatus                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SGetLockStatus
(
    tmUnitSelect_t          tUnit,      /* I: FrontEnd unit number */
    tmsysFrontEndState_t*   pLockStatus /* O: Lock status */
)
{
    ptmOM3869SObject_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;
    tmbslFrontEndState_t    lockStatus = tmbslFrontEndStateUnknown;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869SMutexAcquire(pObj, OM3869S_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Get TDA182I2 PLL Lock status */
        err = tmbslTDA182I2GetLockStatus(pObj->tUnitTDA182I2, &lockStatus);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2GetLockStatus(0x%08X) failed.", pObj->tUnitTDA182I2));

        if(err == TM_OK)
        {
           *pLockStatus = (tmsysFrontEndState_t)lockStatus;
        }

        (void)OM3869SMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SGetSignalStrength                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SGetSignalStrength
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    UInt32          *pStrength  /* I/O: Signal Strength pointer */
)
{
    UNUSEOM3869(tUnit);
    UNUSEOM3869(pStrength);
    return OM3869S_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3869SGetSignalQuality                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SGetSignalQuality
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    UInt32          *pQuality   /* I/O: Signal Quality pointer */
)
{
    UNUSEOM3869(tUnit);
    UNUSEOM3869(pQuality);
   return OM3869S_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3869SGetDeviceUnit                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SGetDeviceUnit
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3869SUnitDeviceType_t deviceType, /* I: Device Type  */
    ptmUnitSelect_t             ptUnit      /* O: Device unit number */
)
{
    ptmOM3869SObject_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869SMutexAcquire(pObj, OM3869S_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(ptUnit!=Null)
        {
            switch(deviceType)
            {
            default:
            case tmOM3869SUnitDeviceTypeUnknown:
                err = OM3869S_ERR_BAD_PARAMETER;
                break;

            case tmOM3869SUnitDeviceTypeTDA182I2:
                *ptUnit = pObj->tUnitTDA182I2;
                break;
            }
        }
        
        (void)OM3869SMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SSetHwAddress                                                    */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SSetHwAddress
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3869SUnitDeviceType_t    deviceType, /* I: Device Type  */
    UInt32                      uHwAddress  /* I: Hardware Address */
)
{
    ptmOM3869SObject_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869SMutexAcquire(pObj, OM3869S_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(deviceType>tmOM3869SUnitDeviceTypeUnknown && deviceType<tmOM3869SUnitDeviceTypeMax)
        {
            pObj->uHwAddress[deviceType] = uHwAddress;
        }
        else
        {
            err = OM3869S_ERR_BAD_PARAMETER;
        }

        (void)OM3869SMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SGetHwAddress                                                    */
/*============================================================================*/
extern tmErrorCode_t
tmsysOM3869SGetHwAddress
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3869SUnitDeviceType_t    deviceType, /* I: Device Type  */
    UInt32*                     puHwAddress /* O: Hardware Address */
)
{
    ptmOM3869SObject_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    /* Check incoming pointer */
    if(err == TM_OK && !puHwAddress)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE,("Error: Invalid Pointer!"));
        err = OM3869S_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = OM3869SMutexAcquire(pObj, OM3869S_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(deviceType>tmOM3869SUnitDeviceTypeUnknown && deviceType<tmOM3869SUnitDeviceTypeMax)
        {
            *puHwAddress = pObj->uHwAddress[deviceType];
        }
        else
        {
            err = OM3869S_ERR_BAD_PARAMETER;
        }

        (void)OM3869SMutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/*                   STATIC FUNCTIONS DEFINITIONS                             */
/*============================================================================*/

/*============================================================================*/
/* OM3869SInit                                                                 */
/*============================================================================*/
static tmErrorCode_t
OM3869SInit
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869SObject_t        pObj = Null;
    tmErrorCode_t               err = TM_OK;
    tmbslFrontEndDependency_t   sSrvFunc;   /* setup parameters */

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        /* Fill function pointers structure */
        sSrvFunc.sIo                    = pObj->sRWFunc;
        sSrvFunc.sTime                  = pObj->sTime;
        sSrvFunc.sDebug                 = pObj->sDebug;
        sSrvFunc.sMutex                 = pObj->sMutex;
        sSrvFunc.dwAdditionalDataSize   = 0;
        sSrvFunc.pAdditionalData        = Null;

        /************************************************************************/
        /* TDA182I2 low layer setup                                             */
        /************************************************************************/

        err = tmbslTDA182I2Init(pObj->tUnitTDA182I2, &sSrvFunc);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2Init(0x%08X) failed.", pObj->tUnitTDA182I2));
    }

    return err;
}

/*============================================================================*/
/* OM3869SReset                                                                */
/*============================================================================*/
static tmErrorCode_t
OM3869SReset
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869SObject_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = tmsysOM3869SSetPowerState(pObj->tUnit, tmPowerStandby);
    }

    if(err == TM_OK)
    {
        pObj->resetDone = False;

        /************************************************************************/
        /* TDA182I2 initialization                                              */
        /************************************************************************/
        /* Determine if we need to wait in Reset function */
        err = tmbslTDA182I2SetIRQWait(pObj->tUnitTDA182I2, True);

        if(err == TM_OK)
        {
            err = tmbslTDA182I2SetPowerState(pObj->tUnitTDA182I2, tmTDA182I2_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2SetPowerState(0x%08X, tmPowerOn) failed.", pObj->tUnitTDA182I2));
        }

        if(err == TM_OK)
        {
            err = tmbslTDA182I2Reset(pObj->tUnitTDA182I2);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2Reset(0x%08X) failed.", pObj->tUnitTDA182I2));
        }
        if (err == TM_OK)
        {
            err = tmbslTDA182I2SetPowerState(pObj->tUnitTDA182I2, tmTDA182I2_PowerStandbyWithLNAOnAndWithXtalOn);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2SetPowerState(0x%08X, tmPowerStandby) failed.", pObj->tUnitTDA182I2));
        }

        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA182I2Reset(0x%08X) failed.", pObj->tUnitTDA182I2);
            /* Open I²C switch to stop Tuner access */
            (void)tmsysOM3869SSetI2CSwitchState(pObj->tUnit, tmsysFrontEndI2CSwitchStateReset);
        }
    }
    return err;
}

/*============================================================================*/
/* OM3869SSetFrequency                                                         */
/*============================================================================*/
static tmErrorCode_t
OM3869SSetFrequency
(
    tmUnitSelect_t          tUnit,          /* I: FrontEnd unit number */
    ptmTunerOnlyRequest_t   pTuneRequest    /* I/O: Tuner Tune Request Structure pointer */
)
{
    ptmOM3869SObject_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;
    tmbslFrontEndState_t        eTunerPLLLock = tmbslFrontEndStateUnknown;

    err = OM3869SGetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869SGetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE, "\n\n===========================================================================");
        tmDBGPRINTEx(DEBUGLVL_TERSE, " OM3869SSetFrequency(0x%08X) is called with following parameters:", pObj->tUnit);
        tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
        tmDBGPRINTEx(DEBUGLVL_TERSE, "     Frequency:           %d Hz", pTuneRequest->dwFrequency);
        tmDBGPRINTEx(DEBUGLVL_TERSE, "     Standard:            %d",    pTuneRequest->dwStandard);
        tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
    }

    if(err == TM_OK && pObj->lastTuneReqType != TRT_TUNER_ONLY)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE,("Configuring Tuner!"));

        if(err == TM_OK)
        {
            err = tmbslTDA182I2SetPowerState(pObj->tUnitTDA182I2, tmTDA182I2_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA182I2SetPowerState(0x%08X, PowerOn) failed.", pObj->tUnitTDA182I2));
        }

        if(err == TM_OK)
        {
            pObj->powerState = tmPowerOn;
            pObj->lastTuneReqType = TRT_TUNER_ONLY;
        }
    }

    /************************************************************************/
    /* Program Tuner                                                        */
    /************************************************************************/

    if(err == TM_OK)
    {
        /* Set Tuner Standard mode */
        err = tmbslTDA182I2SetStandardMode(pObj->tUnitTDA182I2,(tmTDA182I2StandardMode_t) pTuneRequest->dwStandard);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA182I2SetStandardMode(0x%08X, %d) failed.", pObj->tUnitTDA182I2, pTuneRequest->dwStandard);
        }
    }

    if(err == TM_OK)
    {
        /* Set Tuner RF */
        err = tmbslTDA182I2SetRf(pObj->tUnitTDA182I2, pTuneRequest->dwFrequency);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA182I2SetRf(0x%08X, %d) failed.", pObj->tUnitTDA182I2, pTuneRequest->dwFrequency);
        }
    }
    
    if(err == TM_OK)
    {
        /* Get Tuner PLL Lock status */
        err = tmbslTDA182I2GetLockStatus(pObj->tUnitTDA182I2, &eTunerPLLLock);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA182I2GetLockStatus(0x%08X) failed.", pObj->tUnitTDA182I2);
        }
    }

    if(err == TM_OK)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE, "TDA182I2(0x%08X) PLL Lock:%d.", pObj->tUnitTDA182I2, eTunerPLLLock);
    }
    if(err == TM_OK)
    {
        pTuneRequest->eTunerLock = (tmsysFrontEndState_t)eTunerPLLLock;
    }

    /* Print the result of the Manager function */
    switch(eTunerPLLLock)
    {
    case tmbslFrontEndStateLocked:
        if(err == TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_TERSE, "Tuner 0x%08X LOCKED.", pObj->tUnit);
        }
        if(err == TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
            tmDBGPRINTEx(DEBUGLVL_TERSE, " OM3869SSetFrequency(0x%08X) found following parameters:", pObj->tUnit);
            tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
            tmDBGPRINTEx(DEBUGLVL_TERSE, "     Frequency:      %d Hz", pTuneRequest->dwFrequency);
            tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
        }

        break;

    case tmbslFrontEndStateNotLocked:
        if(err == TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_TERSE, "Tuner 0x%08X NOT LOCKED.", pObj->tUnit);
        }
        break;

    case tmbslFrontEndStateSearching:
    default:
        if(err == TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "Tuner 0x%08X TIMEOUT.", pObj->tUnit);
        }
        break;
    }

    return err;
}

/*============================================================================*/
/* OM3869SMutexAcquire                                                      */
/*============================================================================*/
extern tmErrorCode_t
OM3869SMutexAcquire
(
    ptmOM3869SObject_t    pObj,
    UInt32                  timeOut
)
{
    tmErrorCode_t   err = TM_OK;

    if(pObj->sMutex.Acquire != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Acquire(pObj->pMutex, timeOut);
    }

    return err;
}

/*============================================================================*/
/* OM3869SMutexRelease                                                      */
/*============================================================================*/
extern tmErrorCode_t
OM3869SMutexRelease
(
    ptmOM3869SObject_t    pObj
)
{
    tmErrorCode_t   err = TM_OK;

    if(pObj->sMutex.Release != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Release(pObj->pMutex);
    }

    return err;
}

