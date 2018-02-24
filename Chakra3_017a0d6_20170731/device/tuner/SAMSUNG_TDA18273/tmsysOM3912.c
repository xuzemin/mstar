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
*                %version: CFR_FEAP#3 %
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


#include "tmbslTDA18273.h"
#include "tmddTDA18273.h"

#include "tmsysOM3912.h"
#include "tmsysOM3912local.h"
#include "tmsysOM3912Instance.h"


/*============================================================================*/
/*                   MACRO DEFINITION                                         */
/*============================================================================*/

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(ar)        (sizeof(ar)/sizeof((ar)[0]))
#endif // !defined(SIZEOF_ARRAY)

#define NOTUSED(x)	x=x

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
static  tmErrorCode_t OM3912Init(tmUnitSelect_t tUnit);
static  tmErrorCode_t OM3912Reset(tmUnitSelect_t tUnit);
static  tmErrorCode_t OM3912SetFrequency(tmUnitSelect_t tUnit, ptmTunerOnlyRequest_t pTuneRequest);

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
/* tmsysOM3912GetSWVersion                                                    */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912GetSWVersion
(
    ptmsysSWVersion_t   pSWVersion  /* O: Receives SW Version  */
)
{
    tmErrorCode_t   err = TM_OK;
    static char     OM3912Name[] = "tmsysOM3912\0";
    static char     TDA18273Name[] = "tmbslTDA18273\0";

    pSWVersion->arrayItemsNumber = 2;
    pSWVersion->swVersionArray[0].pName = (char *)OM3912Name;
    pSWVersion->swVersionArray[0].nameBufSize = sizeof(OM3912Name);
    
    pSWVersion->swVersionArray[0].swVersion.compatibilityNr = OM3912_SYS_COMP_NUM;
    pSWVersion->swVersionArray[0].swVersion.majorVersionNr = OM3912_SYS_MAJOR_VER;
    pSWVersion->swVersionArray[0].swVersion.minorVersionNr = OM3912_SYS_MINOR_VER;
    
    pSWVersion->swVersionArray[1].pName = (char *)TDA18273Name;
    pSWVersion->swVersionArray[1].nameBufSize = sizeof(TDA18273Name);
    err = tmbslTDA18273GetSWVersion(&pSWVersion->swVersionArray[1].swVersion);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273GetSWVersion failed."));

    /* Remove tuner settings version located into 16 bits MSB */
    pSWVersion->swVersionArray[1].swVersion.compatibilityNr &= 0xFF;
    pSWVersion->swVersionArray[1].swVersion.majorVersionNr &= 0xFF;
    pSWVersion->swVersionArray[1].swVersion.minorVersionNr &= 0xFF;

    return err;
}

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
    ptmOM3912Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    // pObj initialization
    err = OM3912GetInstance(tUnit, &pObj);

    /* check driver state */
    if (err == TM_OK || err == OM3912_ERR_NOT_INITIALIZED)
    {
        if (pObj != Null && pObj->init == True)
        {
            err = OM3912_ERR_NOT_INITIALIZED;
        }
        else 
        {
            /* initialize the Object */
            if (pObj == Null)
            {
                err = OM3912AllocInstance(tUnit, &pObj);
                if (err != TM_OK || pObj == Null)
                {
                    err = OM3912_ERR_NOT_INITIALIZED;        
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

                pObj->tUnitTDA18273 = GET_INDEX_TUNIT(tUnit)|UNIT_PATH_TYPE_VAL(tmOM3912UnitDeviceTypeTDA18273);

                pObj->init = True;
                err = TM_OK;

                err = OM3912Init(tUnit);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912Init(0x%08X) failed.", tUnit));
           }
        }
    }

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
    ptmOM3912Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    /************************************************************************/
    /* DeInitialize TDA18273 low layer setup                                */
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
        
        err = tmbslTDA18273DeInit(pObj->tUnitTDA18273);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273DeInit(0x%08X) failed.", pObj->tUnitTDA18273));
    }

 
    err = OM3912DeAllocInstance(tUnit);

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
    ptmOM3912Object_t    pObj = Null;
    tmErrorCode_t           err = OM3912_ERR_NOT_INITIALIZED;

    /* check input parameters */
    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = OM3912Reset(tUnit);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912Reset(0x%08X) failed.", tUnit));

        (void)OM3912MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3912SetPowerState                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912SetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    tmPowerState_t  ePowerState /* I: Power state of the device */
)
{
    ptmOM3912Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        switch(ePowerState)
        {
        case tmPowerOn:
            if (err == TM_OK)
            {
                pObj->powerState = ePowerState;

                /* Set TDA18273 power state to Normal Mode */
                err = tmbslTDA18273SetPowerState(pObj->tUnitTDA18273, tmTDA18273_PowerNormalMode);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273SetPowerState(0x%08X, tmPowerOn) failed.", pObj->tUnitTDA18273));
            }
            break;

        case tmPowerStandby:
            if (err == TM_OK)
            {
                pObj->powerState = ePowerState;

                /* Set TDA18273 power state to standby with Xtal ON */
                err = tmbslTDA18273SetPowerState(pObj->tUnitTDA18273, tmTDA18273_PowerStandbyWithXtalOn);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273SetPowerState(0x%08X, tmPowerStandby) failed.", pObj->tUnitTDA18273));
            }
            break;

        case tmPowerSuspend:
        case tmPowerOff:
        default:
            err = OM3912_ERR_NOT_SUPPORTED;
            break;
        }

        if (err == TM_OK)
        {
            pObj->lastTuneReqType = TRT_UNKNOWN;
        }

        (void)OM3912MutexRelease(pObj);
    }

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
    ptmOM3912Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *pPowerState = pObj->powerState;

        (void)OM3912MutexRelease(pObj);
    }

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
    ptmOM3912Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    if(err == TM_OK)
    {
        err = OM3912GetInstance(tUnit, &pObj);
        //tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));
    }

    // check pointer
    if( !pTuneRequest )
    {
        tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Invalid Pointer!");
        err = OM3912_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        switch(tTuneReqType)
        {
        case TRT_TUNER_ONLY:
            if( dwTuneRequestSize != sizeof(tmTunerOnlyRequest_t) )
            {
                tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Bad parameter");
                err = OM3912_ERR_BAD_PARAMETER;
            }
            else
            {
                if (err == TM_OK)
                {
                    ptmTunerOnlyRequest_t pTunerOnlyRequest = (ptmTunerOnlyRequest_t)(pTuneRequest);

                    err = OM3912SetFrequency(tUnit, pTunerOnlyRequest);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Error: OM3912SetFrequency failed"));
                }
            }
            break;

        default:
            tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Unsupported tune request");
            err = OM3912_ERR_NOT_SUPPORTED;
            break;
        }

        (void)OM3912MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3912SetI2CSwitchState                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912SetI2CSwitchState
(
    tmUnitSelect_t                  tUnit,  /* I: FrontEnd unit number */
    tmsysFrontEndI2CSwitchState_t   eState  /* I: I2C switch state */
)
{
   NOTUSED(tUnit);
   NOTUSED(eState);
    return OM3912_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3912GetI2CSwitchState                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912GetI2CSwitchState
(
    tmUnitSelect_t                  tUnit,
    tmsysFrontEndI2CSwitchState_t*  peState,
    UInt32*                         puI2CSwitchCounter
)
{
     NOTUSED(tUnit);
     NOTUSED(peState);
     NOTUSED(puI2CSwitchCounter);
    return OM3912_ERR_NOT_SUPPORTED;
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
    ptmOM3912Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;
    tmbslFrontEndState_t    lockStatus = tmbslFrontEndStateUnknown;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Get TDA18273 PLL Lock status */
        err = tmbslTDA18273GetLockStatus(pObj->tUnitTDA18273, &lockStatus);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273GetLockStatus(0x%08X) failed.", pObj->tUnitTDA18273));

        if(err == TM_OK)
        {
           *pLockStatus = (tmsysFrontEndState_t)lockStatus;
        }

        (void)OM3912MutexRelease(pObj);
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
    ptmOM3912Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;   
    UInt32  u32RF;
    UInt8 u8PowerLevelDB=0;
    if(err == TM_OK)
    {
        err = OM3912GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }    
    
    if(err == TM_OK)
    {
        /* Get Tuner RF */
        err = tmbslTDA18273GetRf(pObj->tUnitTDA18273, &u32RF);   

        if(err == TM_OK)
        {
            UInt32 dRF=0;
            float  dOffset=0.0f, dRSSI_Constant = -2.0f;// current we set it at -2.0 for NuTune evk; adjust this constant accordingly to the platform
        
            dRF=u32RF/1000000;
            //printf("RF Frequency %ld\n",dRF);
            if(dRF >= 43 && dRF < 62)
                dOffset = 1.5;
            else if(dRF >= 62 && dRF < 123)
                dOffset = 0.5;
            else if(dRF >= 123 && dRF < 145)
                dOffset = 0.0;
            else if(dRF == 145)
                dOffset = -3.5;
            else if(dRF >= 146 && dRF < 173)
                dOffset = -0.5;
            else if(dRF >= 173 && dRF < 232)
                dOffset = 1.0;
            else if(dRF >= 232 && dRF < 245)
                dOffset = -0.5;
            else if(dRF >= 245 && dRF < 320)
                dOffset = 0.25;
            else if(dRF >= 320 && dRF < 336)
                dOffset = -0.5;
            else if(dRF >= 336 && dRF < 431)
                dOffset = 0.5;
            else if(dRF >= 431 && dRF < 474)
                dOffset = -0.5;
            else if(dRF >= 474 && dRF < 536)
                dOffset = 0.5;
            else if(dRF >= 536 && dRF < 563)
                dOffset = -0.8;
            else if(dRF >= 563 && dRF < 625)
                dOffset = 1.0;
            else if(dRF >= 625 && dRF < 654)
                dOffset = 0.0;
            else if(dRF >= 654 && dRF < 721)
                dOffset = 1.5;
            else if(dRF >= 721 && dRF < 794)
                dOffset = -0.5;
            else if(dRF >= 794 && dRF < 866)
                dOffset = 1.5;
            else if(dRF >= 866)
                dOffset = -0.5;     
            
            err=tmbslTDA18273GetPowerLevel(pObj->tUnitTDA18273, &u8PowerLevelDB);    
            if(err == TM_OK)
            {
                u8PowerLevelDB=(UInt8)(((float)u8PowerLevelDB/2.0f)+dOffset+dRSSI_Constant);
                *pStrength=u8PowerLevelDB;                    
            }
            else
            {
                *pStrength=-1;                    
            }                
        }
        else
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA18273GetRf(0x%08X, %ld) failed.", pObj->tUnitTDA18273, u32RF);
        }

        (void)OM3912MutexRelease(pObj);        
    }
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
   NOTUSED(tUnit);
   NOTUSED(pQuality);
   return OM3912_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3912GetDeviceUnit                                                   */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912GetDeviceUnit
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3912UnitDeviceType_t deviceType, /* I: Device Type  */
    ptmUnitSelect_t             ptUnit      /* O: Device unit number */
)
{
    ptmOM3912Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(ptUnit!=Null)
        {
            switch(deviceType)
            {
            default:
            case tmOM3912UnitDeviceTypeUnknown:
                err = OM3912_ERR_BAD_PARAMETER;
                break;

            case tmOM3912UnitDeviceTypeTDA18273:
                *ptUnit = pObj->tUnitTDA18273;
                break;
            }
        }
        
        (void)OM3912MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3912SetHwAddress                                                    */
/*============================================================================*/
tmErrorCode_t
tmsysOM3912SetHwAddress
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3912UnitDeviceType_t    deviceType, /* I: Device Type  */
    UInt32                      uHwAddress  /* I: Hardware Address */
)
{
    ptmOM3912Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(deviceType>tmOM3912UnitDeviceTypeUnknown && deviceType<tmOM3912UnitDeviceTypeMax)
        {
            pObj->uHwAddress[deviceType] = uHwAddress;
        }
        else
        {
            err = OM3912_ERR_BAD_PARAMETER;
        }

        (void)OM3912MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3912GetHwAddress                                                    */
/*============================================================================*/
extern tmErrorCode_t
tmsysOM3912GetHwAddress
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3912UnitDeviceType_t    deviceType, /* I: Device Type  */
    UInt32*                     puHwAddress /* O: Hardware Address */
)
{
    ptmOM3912Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    /* Check incoming pointer */
    if(err == TM_OK && !puHwAddress)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE,("Error: Invalid Pointer!"));
        err = OM3912_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = OM3912MutexAcquire(pObj, OM3912_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(deviceType>tmOM3912UnitDeviceTypeUnknown && deviceType<tmOM3912UnitDeviceTypeMax)
        {
            *puHwAddress = pObj->uHwAddress[deviceType];
        }
        else
        {
            err = OM3912_ERR_BAD_PARAMETER;
        }

        (void)OM3912MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/*                   STATIC FUNCTIONS DEFINITIONS                             */
/*============================================================================*/

/*============================================================================*/
/* OM3912Init                                                                 */
/*============================================================================*/
static tmErrorCode_t
OM3912Init
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3912Object_t        pObj = Null;
    tmErrorCode_t               err = TM_OK;
    tmbslFrontEndDependency_t   sSrvFunc;   /* setup parameters */

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

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
        /* TDA18273 low layer setup                                             */
        /************************************************************************/

        err = tmbslTDA18273Init(pObj->tUnitTDA18273, &sSrvFunc);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273Init(0x%08X) failed.", pObj->tUnitTDA18273));
    }

    return err;
}

/*============================================================================*/
/* OM3912Reset                                                                */
/*============================================================================*/
static tmErrorCode_t
OM3912Reset
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3912Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = tmsysOM3912SetPowerState(pObj->tUnit, tmPowerStandby);
    }

    if(err == TM_OK)
    {
        pObj->resetDone = False;

        /************************************************************************/
        /* TDA18273 initialization                                              */
        /************************************************************************/
        /* Determine if we need to wait in Reset function */
        err = tmbslTDA18273SetIRQWait(pObj->tUnitTDA18273, True);

        if(err == TM_OK)
        {
            err = tmbslTDA18273SetPowerState(pObj->tUnitTDA18273, tmTDA18273_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273SetPowerState(0x%08X, tmPowerOn) failed.", pObj->tUnitTDA18273));
        }

        if(err == TM_OK)
        {
            err = tmbslTDA18273Reset(pObj->tUnitTDA18273);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273Reset(0x%08X) failed.", pObj->tUnitTDA18273));
        }
        if (err == TM_OK)
        {
            err = tmbslTDA18273SetPowerState(pObj->tUnitTDA18273, tmTDA18273_PowerStandbyWithXtalOn);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273SetPowerState(0x%08X, tmPowerStandby) failed.", pObj->tUnitTDA18273));
        }

        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA18273Reset(0x%08X) failed.", pObj->tUnitTDA18273);
            /* Open I²C switch to stop Tuner access */
            (void)tmsysOM3912SetI2CSwitchState(pObj->tUnit, tmsysFrontEndI2CSwitchStateReset);
        }
    }
    return err;
}

/*============================================================================*/
/* OM3912SetFrequency                                                         */
/*============================================================================*/
static tmErrorCode_t
OM3912SetFrequency
(
    tmUnitSelect_t          tUnit,          /* I: FrontEnd unit number */
    ptmTunerOnlyRequest_t   pTuneRequest    /* I/O: Tuner Tune Request Structure pointer */
)
{
    ptmOM3912Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;
    tmbslFrontEndState_t        eTunerPLLLock = tmbslFrontEndStateUnknown;

    err = OM3912GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3912GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE, "\n\n===========================================================================");
        tmDBGPRINTEx(DEBUGLVL_TERSE, " OM3912SetFrequency(0x%08X) is called with following parameters:", pObj->tUnit);
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
            err = tmbslTDA18273SetPowerState(pObj->tUnitTDA18273, tmTDA18273_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273SetPowerState(0x%08X, PowerOn) failed.", pObj->tUnitTDA18273));
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
        err = tmbslTDA18273SetStandardMode(pObj->tUnitTDA18273, (tmTDA18273StandardMode_t)pTuneRequest->dwStandard);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA18273SetStandardMode(0x%08X, %d) failed.", pObj->tUnitTDA18273, pTuneRequest->dwStandard);
        }
    }

    if(err == TM_OK)
    {
        /* Set Tuner RF */
        err = tmbslTDA18273SetRf(pObj->tUnitTDA18273, pTuneRequest->dwFrequency);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA18273SetRf(0x%08X, %d) failed.", pObj->tUnitTDA18273, pTuneRequest->dwFrequency);
        }
    }
    
    if(err == TM_OK)
    {
        /* Get Tuner PLL Lock status */
        err = tmbslTDA18273GetLockStatus(pObj->tUnitTDA18273, &eTunerPLLLock);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslTDA18273GetLockStatus(0x%08X) failed.", pObj->tUnitTDA18273);
        }
    }

    if(err == TM_OK)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE, "TDA18273(0x%08X) PLL Lock:%d.", pObj->tUnitTDA18273, eTunerPLLLock);
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
            tmDBGPRINTEx(DEBUGLVL_TERSE, " OM3912SetFrequency(0x%08X) found following parameters:", pObj->tUnit);
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
/* OM3912MutexAcquire                                                         */
/*============================================================================*/
extern tmErrorCode_t
OM3912MutexAcquire
(
    ptmOM3912Object_t    pObj,
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
/* OM3912MutexRelease                                                         */
/*============================================================================*/
extern tmErrorCode_t
OM3912MutexRelease
(
    ptmOM3912Object_t    pObj
)
{
    tmErrorCode_t   err = TM_OK;

    if(pObj->sMutex.Release != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Release(pObj->pMutex);
    }

    return err;
}

