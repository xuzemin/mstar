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
 * \file          tmddTDA18273.c
 *
 *                3
 *
 * \date          %modify_time%
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA18254_Driver_User_Guide.pdf
 *
 * Detailed description may be added here.
 *
 * \section info Change Information
 *
*/

/*============================================================================*/
/* Standard include files:                                                    */
/*============================================================================*/
#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"
#include "tmUnitParams.h"

/*============================================================================*/
/* Project include files:                                                     */
/*============================================================================*/
#include "tmddTDA18273.h"
#include "tmddTDA18273_Advanced.h"
#include "tmddTDA18273local.h"

#include "tmddTDA18273Instance.h"

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/

/*============================================================================*/
/* Global data:                                                               */
/*============================================================================*/

/*============================================================================*/
/* Internal Prototypes:                                                       */
/*============================================================================*/

/*============================================================================*/
/* Exported functions:                                                        */
/*============================================================================*/


/*============================================================================*/
/* FUNCTION:    tmddTDA18273Init                                              */
/*                                                                            */
/* DESCRIPTION: Create an instance of a TDA18273 Tuner                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273Init
(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /* I: setup parameters */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    if (psSrvFunc == Null)
    {
        err = ddTDA18273_ERR_BAD_PARAMETER;
    }

    /* Get Instance Object */
    if(err == TM_OK)
    {
        err = ddTDA18273GetInstance(tUnit, &pObj);
    }

    /* Check driver state */
    if (err == TM_OK || err == ddTDA18273_ERR_NOT_INITIALIZED)
    {
        if (pObj != Null && pObj->init == True)
        {
            err = ddTDA18273_ERR_NOT_INITIALIZED;
        }
        else 
        {
            /* Allocate the Instance Object */
            if (pObj == Null)
            {
                err = ddTDA18273AllocInstance(tUnit, &pObj);
                if (err != TM_OK || pObj == Null)
                {
                    err = ddTDA18273_ERR_NOT_INITIALIZED;        
                }
            }

            if(err == TM_OK)
            {
                /* initialize the Instance Object */
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
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273DeInit                                            */
/*                                                                            */
/* DESCRIPTION: Destroy an instance of a TDA18273 Tuner                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t 
tmddTDA18273DeInit
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    tmErrorCode_t           err = TM_OK;
    ptmddTDA18273Object_t   pObj = Null;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);

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
    }

    err = ddTDA18273DeAllocInstance(tUnit);

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273Write                                             */
/*                                                                            */
/* DESCRIPTION: Write in TDA18273 hardware                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273Write
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          uIndex,     /* I: Start index to write */
    UInt32          uNbBytes,   /* I: Number of bytes to write */
    UInt8*          puBytes     /* I: Pointer on an array of bytes */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err = TM_OK;
    UInt32                  uCounter;
    UInt8*                  pI2CMap = Null;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* pI2CMap initialization */
        pI2CMap = &(pObj->I2CMap.uBx00.ID_byte_1) + uIndex;

        /* Save the values written in the Tuner */
        for (uCounter = 0; uCounter < uNbBytes; uCounter++)
        {
            *pI2CMap = puBytes[uCounter];
            pI2CMap ++;
        }

        /* Write in the Tuner */
        err = ddTDA18273Write(pObj,(UInt8)(uIndex),(UInt8)(uNbBytes));
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273Read                                              */
/*                                                                            */
/* DESCRIPTION: Read in TDA18273 hardware                                     */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273Read
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          uIndex,     /* I: Start index to read */
    UInt32          uNbBytes,   /* I: Number of bytes to read */
    UInt8*          puBytes     /* I: Pointer on an array of bytes */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err = TM_OK;
    UInt32                  uCounter = 0;
    UInt8*                  pI2CMap = Null;

    /* Test the parameters */
    if (uNbBytes > TDA18273_I2C_MAP_NB_BYTES)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* pI2CMap initialization */
        pI2CMap = &(pObj->I2CMap.uBx00.ID_byte_1) + uIndex;

        /* Read from the Tuner */
        err = ddTDA18273Read(pObj,(UInt8)(uIndex),(UInt8)(uNbBytes));
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Copy read values to puBytes */
            for (uCounter = 0; uCounter < uNbBytes; uCounter++)
            {
                *puBytes = (*pI2CMap);
                pI2CMap ++;
                puBytes ++;
            }
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIdentity                                       */
/*                                                                            */
/* DESCRIPTION: Get the Identity bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIdentity
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt16*         puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x00-0x01 */
        err = ddTDA18273Read(pObj, 0x00, 2);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx00.bF.Ident_1 << 8 |  pObj->I2CMap.uBx01.bF.Ident_2;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetMinorRevision                                  */
/*                                                                            */
/* DESCRIPTION: Get the Revision bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetMinorRevision
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x02 */
        err = ddTDA18273Read(pObj, 0x02, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx02.bF.Minor_rev;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetMajorRevision                                  */
/*                                                                            */
/* DESCRIPTION: Get the Revision bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetMajorRevision
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x02 */
        err = ddTDA18273Read(pObj, 0x02, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx02.bF.Major_rev;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGCs_Lock                                      */
/*                                                                            */
/* DESCRIPTION: Get the AGCs_Lock bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGCs_Lock
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x05 */
        err = ddTDA18273Read(pObj, 0x05, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx05.bF.AGCs_Lock ;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetVsync_Lock                                     */
/*                                                                            */
/* DESCRIPTION: Get the Vsync_Lock bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetVsync_Lock
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x05 */
        err = ddTDA18273Read(pObj, 0x05, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx05.bF.Vsync_Lock ;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetLO_Lock                                        */
/*                                                                            */
/* DESCRIPTION: Get the LO_Lock bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetLO_Lock
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x05 */
        err = ddTDA18273Read(pObj, 0x05, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx05.bF.LO_Lock ;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetPowerState                                     */
/*                                                                            */
/* DESCRIPTION: Set the power state of the TDA18273                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetPowerState
(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    tmddTDA18273PowerState_t    powerState  /* I: Power state of this device */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set power state */
        switch (powerState)
        {
            case tmddTDA18273_PowerNormalMode:          
                pObj->I2CMap.uBx06.bF.SM = 0x00;
                pObj->I2CMap.uBx06.bF.SM_XT = 0x00;
                break;

            case tmddTDA18273_PowerStandbyWithXtalOn:
                pObj->I2CMap.uBx06.bF.SM = 0x01;
                pObj->I2CMap.uBx06.bF.SM_XT = 0x00;
                break;

            case tmddTDA18273_PowerStandby:
                pObj->I2CMap.uBx06.bF.SM = 0x01;
                pObj->I2CMap.uBx06.bF.SM_XT = 0x01;
                break;

            default:
                /* Power state not supported*/
                return ddTDA18273_ERR_NOT_SUPPORTED;
        }

        /* Write byte 0x06 */
        err = ddTDA18273Write(pObj, 0x06, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetPowerState                                     */
/*                                                                            */
/* DESCRIPTION: Get the power state of the TDA18273                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetPowerState
(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    ptmddTDA18273PowerState_t   pPowerState /* O: Power state of this device */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Get power state */
        if ((pObj->I2CMap.uBx06.bF.SM == 0x00) && (pObj->I2CMap.uBx06.bF.SM_XT == 0x00))
        {
            *pPowerState = tmddTDA18273_PowerNormalMode;
        }
        else if ((pObj->I2CMap.uBx06.bF.SM == 0x01) && (pObj->I2CMap.uBx06.bF.SM_XT == 0x00))
        {
            *pPowerState = tmddTDA18273_PowerStandbyWithXtalOn;
        }
        else if ((pObj->I2CMap.uBx06.bF.SM == 0x01) && (pObj->I2CMap.uBx06.bF.SM_XT == 0x01))
        {  
            *pPowerState = tmddTDA18273_PowerStandby;
        }
        else
        {
            *pPowerState = tmddTDA18273_PowerMax;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetPower_Level                                    */
/*                                                                            */
/* DESCRIPTION: Get the Power_Level bit(s) status                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetPower_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x07 */
        err = ddTDA18273Read(pObj, 0x07, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx07.bF.Power_Level;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIRQ_status                                     */
/*                                                                            */
/* DESCRIPTION: Get the IRQ_status bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIRQ_status
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x08 */
        err = ddTDA18273GetIRQ_status(pObj, puValue);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetIRQ_status(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetMSM_XtalCal_End                                */
/*                                                                            */
/* DESCRIPTION: Get the MSM_XtalCal_End bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetMSM_XtalCal_End
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x08 */
        err = ddTDA18273GetMSM_XtalCal_End(pObj, puValue);

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIRQ_Clear                                      */
/*                                                                            */
/* DESCRIPTION: Set the IRQ_Clear bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIRQ_Clear
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8           irqStatus   /* I: IRQs to clear */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set IRQ_Clear */
        pObj->I2CMap.uBx0A.IRQ_clear |= (0x80|(irqStatus&0x3F));

        /* Write byte 0x0A */
        err = ddTDA18273Write(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        /* Reset IRQ_Clear (buffer only, no write) */
        pObj->I2CMap.uBx0A.IRQ_clear &= (~(0x80|(irqStatus&0x3F)));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC1_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Set the AGC1_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC1_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0C.bF.AGC1_TOP = uValue;

        /* write byte 0x0C */
        err = ddTDA18273Write(pObj, 0x0C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC1_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Get the AGC1_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC1_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if ( puValue == Null )
    {
        err = ddTDA18273_ERR_BAD_PARAMETER;
    }       

    /* Get Instance Object */
    if(err == TM_OK)
    {
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }
    
    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
        
        if(err == TM_OK)
        {
            /* Read byte 0x0C */
            err = ddTDA18273Read(pObj, 0x0C, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));
    
            if(err == TM_OK)
            {
                /* Get value */
                *puValue = pObj->I2CMap.uBx0C.bF.AGC1_TOP;
            }
    
            (void)ddTDA18273MutexRelease(pObj);
        }
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC1_Top_Mode                                  */
/*                                                                            */
/* DESCRIPTION: Set the AGC1_Top_Mode bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC1_Top_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* set value */
        pObj->I2CMap.uBx0D.bF.AGC1_Top_Mode = uValue;

        /* Write byte 0x0D */
        err = ddTDA18273Write(pObj, 0x0D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC1_Top_Mode                                  */
/*                                                                            */
/* DESCRIPTION: Get the AGC1_Top_Mode bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC1_Top_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0D */
        err = ddTDA18273Read(pObj, 0x0D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0D.bF.AGC1_Top_Mode;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC1_Top_Mode_Val                              */
/*                                                                            */
/* DESCRIPTION: Set the AGC1_Top_Mode_Val bit(s) status                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC1_Top_Mode_Val
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* set value */
        pObj->I2CMap.uBx0D.bF.AGC1_Top_Mode_Val = uValue;

        /* Write byte 0x0D */
        err = ddTDA18273Write(pObj, 0x0D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC1_Top_Mode_Val                              */
/*                                                                            */
/* DESCRIPTION: Get the AGC1_Top_Mode_Val bit(s) status                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC1_Top_Mode_Val
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0D */
        err = ddTDA18273Read(pObj, 0x0D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0D.bF.AGC1_Top_Mode_Val;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC2_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Set the AGC2_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC2_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* set value */
        pObj->I2CMap.uBx0E.bF.AGC2_TOP = uValue;

        /* Write byte 0x0E */
        err = ddTDA18273Write(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC2_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Get the AGC2_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC2_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0E */
        err = ddTDA18273Read(pObj, 0x0E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0E.bF.AGC2_TOP;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGCK_Step                                      */
/*                                                                            */
/* DESCRIPTION: Set the AGCK_Step bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGCK_Step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0F.bF.AGCK_Step = uValue;

        /* Write byte 0x0F */
        err = ddTDA18273Write(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGCK_Step                                      */
/*                                                                            */
/* DESCRIPTION: Get the AGCK_Step bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGCK_Step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0F */
        err = ddTDA18273Read(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0F.bF.AGCK_Step;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGCK_Mode                                      */
/*                                                                            */
/* DESCRIPTION: Set the AGCK_Mode bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGCK_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx0F.bF.AGCK_Mode = uValue;

        /* Write byte 0x0F */
        err = ddTDA18273Write(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGCK_Mode                                      */
/*                                                                            */
/* DESCRIPTION: Get the AGCK_Mode bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGCK_Mode
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x0F */
        err = ddTDA18273Read(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx0F.bF.AGCK_Mode;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetPD_AGC_Adapt3x                                 */
/*                                                                            */
/* DESCRIPTION: Set the PD_AGC_Adapt3x bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetPD_AGC_Adapt3x
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx10.bF.PD_AGC_Adapt3x = uValue;

        /* Write byte 0x10 */
        err = ddTDA18273Write(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetPD_AGC_Adapt3x                                 */
/*                                                                            */
/* DESCRIPTION: Get the PD_AGC_Adapt3x bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetPD_AGC_Adapt3x
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x10 */
        err = ddTDA18273Read(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx10.bF.PD_AGC_Adapt3x;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetRFAGC_Adapt_TOP                                */
/*                                                                            */
/* DESCRIPTION: Set the RFAGC_Adapt_TOP bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetRFAGC_Adapt_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx10.bF.RFAGC_Adapt_TOP = uValue;

        /* Write byte 0x10 */
        err = ddTDA18273Write(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetRFAGC_Adapt_TOP                                */
/*                                                                            */
/* DESCRIPTION: Get the RFAGC_Adapt_TOP bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetRFAGC_Adapt_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x10 */
        err = ddTDA18273Read(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx10.bF.RFAGC_Adapt_TOP;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetRFAGC_Top                                      */
/*                                                                            */
/* DESCRIPTION: Set the RFAGC_Top bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetRFAGC_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx10.bF.RFAGC_Top = uValue;

        /* Write byte 0x10 */
        err = ddTDA18273Write(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetRFAGC_Top                                      */
/*                                                                            */
/* DESCRIPTION: Get the RFAGC_Top bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetRFAGC_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x10 */
        err = ddTDA18273Read(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx10.bF.RFAGC_Top;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetVHF_III_mode:
//
// DESCRIPTION: Set the VHF_III_mode bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetVHF_III_mode
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx11.bF.VHF_III_mode = uValue;

        // write byte 0x11
        err = ddTDA18273Write(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetVHF_III_mode:
//
// DESCRIPTION: Get the VHF_III_mode bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetVHF_III_mode
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x11
        err = ddTDA18273Read(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx11.bF.VHF_III_mode;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRF_Atten_3dB:
//
// DESCRIPTION: Set the RF_Atten_3dB bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRF_Atten_3dB
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx11.bF.RF_Atten_3dB = uValue;

        // write byte 0x11
        err = ddTDA18273Write(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRF_Atten_3dB:
//
// DESCRIPTION: Get the RF_Atten_3dB bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRF_Atten_3dB
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x11
        err = ddTDA18273Read(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx11.bF.RF_Atten_3dB;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetS2D_Gain                                       */
/*                                                                            */
/* DESCRIPTION: Set the S2D_Gain bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetS2D_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx12.bF.S2D_Gain = uValue;

        /* Write byte 0x12 */
        err = ddTDA18273Write(pObj, 0x12, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetS2D_Gain                                       */
/*                                                                            */
/* DESCRIPTION: Get the S2D_Gain bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetS2D_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x12 */
        err = ddTDA18273Read(pObj, 0x12, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx12.bF.S2D_Gain;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIR_Mixer_Top                                   */
/*                                                                            */
/* DESCRIPTION: Set the IR_Mixer_Top bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIR_Mixer_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx12.bF.IR_Mixer_Top = uValue;

        /* Write byte 0x12 */
        err = ddTDA18273Write(pObj, 0x12, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIR_Mixer_Top                                   */
/*                                                                            */
/* DESCRIPTION: Get the IR_Mixer_Top bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIR_Mixer_Top
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x12 */
        err = ddTDA18273Read(pObj, 0x12, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx12.bF.IR_Mixer_Top;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC5_Ana                                       */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_Ana bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC5_Ana
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx13.bF.AGC5_Ana = uValue;

        /* Write byte 0x13 */
        err = ddTDA18273Write(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC5_Ana                                       */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_Ana bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC5_Ana
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x13 */
        err = ddTDA18273Read(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx13.bF.AGC5_Ana;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC5_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC5_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx13.bF.AGC5_TOP = uValue;

        /* Write byte 0x13 */
        err = ddTDA18273Write(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC5_TOP                                       */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_TOP bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC5_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x13 */
        err = ddTDA18273Read(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx13.bF.AGC5_TOP;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIF_Level                                       */
/*                                                                            */
/* DESCRIPTION: Set the IF_level bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIF_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx14.bF.IF_level = uValue;

        /* Write byte 0x14 */
        err = ddTDA18273Write(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIF_Level                                       */
/*                                                                            */
/* DESCRIPTION: Get the IF_level bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIF_Level
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x14 */
        err = ddTDA18273Read(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx14.bF.IF_level;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIF_HP_Fc                                       */
/*                                                                            */
/* DESCRIPTION: Set the IF_HP_Fc bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIF_HP_Fc
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx15.bF.IF_HP_Fc = uValue;

        /* Write byte 0x15 */
        err = ddTDA18273Write(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIF_HP_Fc                                       */
/*                                                                            */
/* DESCRIPTION: Get the IF_HP_Fc bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIF_HP_Fc
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x15 */
        err = ddTDA18273Read(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx15.bF.IF_HP_Fc;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIF_ATSC_Notch                                  */
/*                                                                            */
/* DESCRIPTION: Set the IF_ATSC_Notch bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIF_ATSC_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx15.bF.IF_ATSC_Notch = uValue;

        /* Write byte 0x15 */
        err = ddTDA18273Write(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIF_ATSC_Notch                                  */
/*                                                                            */
/* DESCRIPTION: Get the IF_ATSC_Notch bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIF_ATSC_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x15 */
        err = ddTDA18273Read(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx15.bF.IF_ATSC_Notch;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetLP_FC_Offset                                   */
/*                                                                            */
/* DESCRIPTION: Set the LP_FC_Offset bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetLP_FC_Offset
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx15.bF.LP_FC_Offset = uValue;

        /* Write byte 0x15 */
        err = ddTDA18273Write(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetLP_FC_Offset                                   */
/*                                                                            */
/* DESCRIPTION: Get the LP_FC_Offset bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetLP_FC_Offset
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x15 */
        err = ddTDA18273Read(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx15.bF.LP_FC_Offset;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetLP_FC                                          */
/*                                                                            */
/* DESCRIPTION: Set the LP_Fc bit(s) status                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetLP_FC
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx15.bF.LP_Fc = uValue;

        /* Write byte 0x15 */
        err = ddTDA18273Write(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetLP_FC                                          */
/*                                                                            */
/* DESCRIPTION: Get the LP_Fc bit(s) status                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetLP_FC
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x15 */
        err = ddTDA18273Read(pObj, 0x15, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx15.bF.LP_Fc;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIF_Freq                                        */
/*                                                                            */
/* DESCRIPTION: Set the IF_Freq bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx17.bF.IF_Freq = (UInt8)(uValue / 50000);

        /* Write byte 0x17 */
        err = ddTDA18273Write(pObj, 0x17, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIF_Freq                                        */
/*                                                                            */
/* DESCRIPTION: Get the IF_Freq bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x17 */
        err = ddTDA18273Read(pObj, 0x17, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx17.bF.IF_Freq * 50000;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetRF_Freq                                        */
/*                                                                            */
/* DESCRIPTION: Set the RF_Freq bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetRF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;
    UInt32                  uRF = 0;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set RF frequency expressed in kHz */
        uRF = uValue / 1000;
        pObj->I2CMap.uBx18.bF.RF_Freq_1 = (UInt8)((uRF & 0x00FF0000) >> 16);
        pObj->I2CMap.uBx19.bF.RF_Freq_2 = (UInt8)((uRF & 0x0000FF00) >> 8);
        pObj->I2CMap.uBx1A.bF.RF_Freq_3 = (UInt8)(uRF & 0x000000FF);

        /* write bytes 0x18 to 0x1A */
        err = ddTDA18273Write(pObj, 0x18, 3);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetRF_Freq                                        */
/*                                                                            */
/* DESCRIPTION: Get the RF_Freq bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetRF_Freq
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read bytes 0x18 to 0x1A */
        err = ddTDA18273Read(pObj, 0x18, 3);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = (pObj->I2CMap.uBx18.bF.RF_Freq_1 << 16) | (pObj->I2CMap.uBx19.bF.RF_Freq_2 << 8) | pObj->I2CMap.uBx1A.bF.RF_Freq_3;
            *puValue = *puValue * 1000;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetTriggerMSM                                     */
/*                                                                            */
/* DESCRIPTION: Set the MSM bit(s) and launch MSM                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetTriggerMSM
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set all MSM bytes */
        pObj->I2CMap.uBx1B.MSM_byte_1 = uValue;
        pObj->I2CMap.uBx1C.MSM_byte_2 = 0x01;

        /* Write bytes 0x1B to 0x1C */
        err = ddTDA18273Write(pObj, 0x1B, 2);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        /* Reset map */
        pObj->I2CMap.uBx1C.MSM_byte_2 = 0x00;

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetMSM_Launch                                     */
/*                                                                            */
/* DESCRIPTION: Set the MSM_Launch bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetMSM_Launch
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx1C.bF.MSM_Launch = 1;

        /* Write byte 0x1C */
        err = ddTDA18273Write(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        /* reset MSM_Launch (buffer only, no write) */
        pObj->I2CMap.uBx1C.bF.MSM_Launch = 0x00;

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetMSM_Launch                                     */
/*                                                                            */
/* DESCRIPTION: Get the MSM_Launch bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetMSM_Launch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x1C */
        err = ddTDA18273Read(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1C.bF.MSM_Launch;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetPD_Ovld_RF                                     */
/*                                                                            */
/* DESCRIPTION: Set the PD_Ovld_RF bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetPD_Ovld_RF
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx21.bF.PD_Ovld_RF = uValue;

        /* Write byte 0x21 */
        err = ddTDA18273Write(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetPD_Ovld_RF                                     */
/*                                                                            */
/* DESCRIPTION: Get the PD_Ovld_RF bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetPD_Ovld_RF
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x21 */
        err = ddTDA18273Read(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx21.bF.PD_Ovld_RF;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC_Ovld_TOP                                   */
/*                                                                            */
/* DESCRIPTION: Set the AGC_Ovld_TOP bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC_Ovld_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx21.bF.AGC_Ovld_TOP = uValue;

        /* Write byte 0x21 */
        err = ddTDA18273Write(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC_Ovld_TOP                                   */
/*                                                                            */
/* DESCRIPTION: Get the AGC_Ovld_TOP bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC_Ovld_TOP
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x21 */
        err = ddTDA18273Read(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx21.bF.AGC_Ovld_TOP;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetUp_Step_Ovld                                   */
/*                                                                            */
/* DESCRIPTION: Set the Up_Step_Ovld bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetUp_Step_Ovld
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx21.bF.Up_Step_Ovld = uValue;

        /* Write byte 0x21 */
        err = ddTDA18273Write(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetUp_Step_Ovld                                   */
/*                                                                            */
/* DESCRIPTION: Get the Up_Step_Ovld bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetUp_Step_Ovld
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x21 */
        err = ddTDA18273Read(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx21.bF.Up_Step_Ovld;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetHi_Pass                                        */
/*                                                                            */
/* DESCRIPTION: Set the Hi_Pass bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetHi_Pass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx22.bF.Hi_Pass = uValue;

        /* Read byte 0x22 */
        err = ddTDA18273Write(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetHi_Pass                                        */
/*                                                                            */
/* DESCRIPTION: Get the Hi_Pass bit(s) status                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetHi_Pass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x22 */
        err = ddTDA18273Read(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx22.bF.Hi_Pass;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIF_Notch                                       */
/*                                                                            */
/* DESCRIPTION: Set the IF_Notch bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIF_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx22.bF.IF_Notch = uValue;

        /* Read byte 0x22 */
        err = ddTDA18273Write(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIF_Notch                                       */
/*                                                                            */
/* DESCRIPTION: Get the IF_Notch bit(s) status                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIF_Notch
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x22 */
        err = ddTDA18273Read(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx22.bF.IF_Notch;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetAGC1_Do_step:
//
// DESCRIPTION: Set the AGC1_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetAGC1_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx23.bF.AGC1_Do_step = uValue;

        // read byte 0x23
        err = ddTDA18273Write(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC1_Do_step:
//
// DESCRIPTION: Get the AGC1_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetAGC1_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x23
        err = ddTDA18273Read(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx23.bF.AGC1_Do_step;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetAGC2_Do_step:
//
// DESCRIPTION: Set the AGC2_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetAGC2_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx2D.bF.AGC2_Do_step = uValue;

        // read byte 0x2D
        err = ddTDA18273Write(pObj, 0x2D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC2_Do_step:
//
// DESCRIPTION: Get the AGC2_Do_step bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetAGC2_Do_step
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x2D
        err = ddTDA18273Read(pObj, 0x2D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2D.bF.AGC2_Do_step;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC5_loop_off                                  */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_loop_off bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC5_loop_off
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx26.bF.AGC5_loop_off = uValue;

        /* Read byte 0x26 */
        err = ddTDA18273Write(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC5_loop_off                                  */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_loop_off bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC5_loop_off
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x26 */
        err = ddTDA18273Read(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx26.bF.AGC5_loop_off;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC5_Do_step                                   */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_Do_step bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC5_Do_step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx26.bF.AGC5_Do_step = uValue;

        /* Read byte 0x26 */
        err = ddTDA18273Write(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC5_Do_step                                   */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_Do_step bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC5_Do_step
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x26 */
        err = ddTDA18273Read(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx26.bF.AGC5_Do_step;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetForce_AGC5_gain                                */
/*                                                                            */
/* DESCRIPTION: Set the Force_AGC5_gain bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetForce_AGC5_gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx26.bF.Force_AGC5_gain = uValue;

        /* Read byte 0x26 */
        err = ddTDA18273Write(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetForce_AGC5_gain                                */
/*                                                                            */
/* DESCRIPTION: Get the Force_AGC5_gain bit(s) status                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetForce_AGC5_gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x26 */
        err = ddTDA18273Read(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx26.bF.Force_AGC5_gain;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetAGC5_Gain                                      */
/*                                                                            */
/* DESCRIPTION: Set the AGC5_Gain bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetAGC5_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx26.bF.AGC5_Gain = uValue;

        /* Read byte 0x26 */
        err = ddTDA18273Write(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetAGC5_Gain                                      */
/*                                                                            */
/* DESCRIPTION: Get the AGC5_Gain bit(s) status                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetAGC5_Gain
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x26 */
        err = ddTDA18273Read(pObj, 0x26, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx26.bF.AGC5_Gain;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetRF_Filter_Bypass                               */
/*                                                                            */
/* DESCRIPTION: Set the RF_Filter_Bypass bit(s) status                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetRF_Filter_Bypass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2B.bF.RF_Filter_Bypass = uValue;

        /* Read byte 0x2B */
        err = ddTDA18273Write(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetRF_Filter_Bypass                               */
/*                                                                            */
/* DESCRIPTION: Get the RF_Filter_Bypass bit(s) status                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetRF_Filter_Bypass
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x2B */
        err = ddTDA18273Read(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx2B.bF.RF_Filter_Bypass;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetRF_Filter_Band                                 */
/*                                                                            */
/* DESCRIPTION: Set the RF_Filter_Band bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetRF_Filter_Band
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2B.bF.RF_Filter_Band = uValue;

        /* Read byte 0x2B */
        err = ddTDA18273Write(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetRF_Filter_Band                                 */
/*                                                                            */
/* DESCRIPTION: Get the RF_Filter_Band bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetRF_Filter_Band
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x2B */
        err = ddTDA18273Read(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx2B.bF.RF_Filter_Band;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetRF_Filter_Cap                                  */
/*                                                                            */
/* DESCRIPTION: Set the RF_Filter_Cap bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetRF_Filter_Cap
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2C.RF_Filter_Cap = uValue;

        /* Read byte 0x2C */
        err = ddTDA18273Write(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetRF_Filter_Cap                                  */
/*                                                                            */
/* DESCRIPTION: Get the RF_Filter_Cap bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetRF_Filter_Cap
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x2C */
        err = ddTDA18273Read(pObj, 0x2C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx2C.RF_Filter_Cap;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetGain_Taper                                     */
/*                                                                            */
/* DESCRIPTION: Set the Gain_Taper bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetGain_Taper
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2D.bF.Gain_Taper = uValue;

        /* Read byte 0x2D */
        err = ddTDA18273Write(pObj, 0x2D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetGain_Taper                                     */
/*                                                                            */
/* DESCRIPTION: Get the Gain_Taper bit(s) status                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetGain_Taper
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if( puValue == Null )
    {
        err = ddTDA18273_ERR_BAD_PARAMETER;
    }

    /* Get Instance Object */
    if(err == TM_OK)
    {
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);

        if(err == TM_OK)
        {
            /* Read byte 0x2D */
            err = ddTDA18273Read(pObj, 0x2D, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));
    
            if(err == TM_OK)
            {
                /* Get value */
                *puValue = pObj->I2CMap.uBx2D.bF.Gain_Taper;
            }
    
            (void)ddTDA18273MutexRelease(pObj);
        }
    }
    
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetN_CP_Current                                   */
/*                                                                            */
/* DESCRIPTION: Set the N_CP_Current bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetN_CP_Current
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx2F.bF.N_CP_Current = uValue;

        /* Read byte 0x2F */
        err = ddTDA18273Write(pObj, 0x2F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetN_CP_Current                                   */
/*                                                                            */
/* DESCRIPTION: Get the N_CP_Current bit(s) status                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetN_CP_Current
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x2F */
        err = ddTDA18273Read(pObj, 0x2F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx2F.bF.N_CP_Current;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetRSSI_Ck_Speed                                  */
/*                                                                            */
/* DESCRIPTION: Set the RSSI_Ck_Speed bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetRSSI_Ck_Speed
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx37.bF.RSSI_Ck_Speed = uValue;

        /* Write byte 0x37 */
        err = ddTDA18273Write(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetRSSI_Ck_Speed                                  */
/*                                                                            */
/* DESCRIPTION: Get the RSSI_Ck_Speed bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetRSSI_Ck_Speed
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x37 */
        err = ddTDA18273Read(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx37.bF.RSSI_Ck_Speed;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPD_Underload:
//
// DESCRIPTION: Set the PD_Underload bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetPD_Underload
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx38.bF.PD_Underload = uValue;

        // write byte 0x38
        err = ddTDA18273Write(pObj, 0x38, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPD_Underload:
//
// DESCRIPTION: Get the PD_Underload bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetPD_Underload
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // read byte 0x38
        err = ddTDA18273Read(pObj, 0x38, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx38.bF.PD_Underload;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetInternal_Test_Signal                           */
/*                                                                            */
/* DESCRIPTION: Set the Internal_Test_Signal bit(s) status                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetInternal_Test_Signal
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8           uValue  /* I: Item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Set value */
        pObj->I2CMap.uBx38.bF.RFCALPOR_I2C = uValue;

        /* Write byte 0x38 */
        err = ddTDA18273Write(pObj, 0x38, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetInternal_Test_Signal                           */
/*                                                                            */
/* DESCRIPTION: Get the Internal_Test_Signal bit(s) status                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetInternal_Test_Signal
(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          puValue /* I: Address of the variable to output item value */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Get Instance Object */
        err = ddTDA18273GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Read byte 0x38 */
        err = ddTDA18273Read(pObj, 0x38, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx38.bF.RFCALPOR_I2C;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273WaitIRQ                                           */
/*                                                                            */
/* DESCRIPTION: Wait the IRQ to trigger                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273WaitIRQ
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeout */
    UInt32          waitStep,   /* I: wait step */
    UInt8           irqStatus   /* I: IRQs to wait */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = ddTDA18273WaitIRQ(pObj, timeOut, waitStep, irqStatus);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273WaitIRQ(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetXtalCal_Launch:
//
// DESCRIPTION: Set the XtalCal_Launch bit(s) status
//
// RETURN:      tmdd_ERR_TUNER_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_PARAMETER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetXtalCal_Launch
(
 tmUnitSelect_t      tUnit    //  I: Unit number
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        // set value
        pObj->I2CMap.uBx1C.bF.XtalCal_Launch = 1;

        // write byte 0x1C
        err = ddTDA18273Write(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        // reset XtalCal_Launch (buffer only, no write)
        pObj->I2CMap.uBx1C.bF.XtalCal_Launch = 0;

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273WaitXtalCal_End                                   */
/*                                                                            */
/* DESCRIPTION: Wait the MSM_XtalCal_End to trigger                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273WaitXtalCal_End
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeout */
    UInt32          waitStep    /* I: wait step */
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    /* Get Instance Object */
    err = ddTDA18273GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = ddTDA18273MutexAcquire(pObj, ddTDA18273_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = ddTDA18273WaitXtalCal_End(pObj, timeOut, waitStep);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273WaitXtalCal_End(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    ddTDA18273GetIRQ_status                                       */
/*                                                                            */
/* DESCRIPTION: Get IRQ status                                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddTDA18273GetIRQ_status
(
    ptmddTDA18273Object_t   pObj,   /* I: Instance object */
    UInt8*                  puValue /* I: Address of the variable to output item value */
)
{     
    tmErrorCode_t   err  = TM_OK;

    /* Read byte 0x08 */
    err = ddTDA18273Read(pObj, 0x08, 1);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", pObj->tUnit));

    if(err == TM_OK)
    {
        /* Get value */
        *puValue = pObj->I2CMap.uBx08.bF.IRQ_status;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    ddTDA18273GetMSM_XtalCal_End                                  */
/*                                                                            */
/* DESCRIPTION: Get MSM_XtalCal_End bit(s) status                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddTDA18273GetMSM_XtalCal_End
(
    ptmddTDA18273Object_t   pObj,   /* I: Instance object */
    UInt8*                  puValue /* I: Address of the variable to output item value */
)
{
    tmErrorCode_t           err  = TM_OK;

    /* Test the parameters */
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_PARAMETER;

    if(err == TM_OK)
    {
        /* Read byte 0x08 */
        err = ddTDA18273Read(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", pObj->tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx08.bF.MSM_XtalCal_End;
        }
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    ddTDA18273WaitIRQ                                             */
/*                                                                            */
/* DESCRIPTION: Wait for IRQ to trigger                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddTDA18273WaitIRQ
(
    ptmddTDA18273Object_t   pObj,       /* I: Instance object */
    UInt32                  timeOut,    /* I: timeout */
    UInt32                  waitStep,   /* I: wait step */
    UInt8                   irqStatus   /* I: IRQs to wait */
)
{     
    tmErrorCode_t   err  = TM_OK;
    UInt32          counter = timeOut/waitStep; /* Wait max timeOut/waitStep ms */
    UInt8           uIRQ = 0;
    UInt8           uIRQStatus = 0;
    Bool            bIRQTriggered = False;

    while(err == TM_OK && (--counter)>0)
    {
        err = ddTDA18273GetIRQ_status(pObj, &uIRQ);

        if(err == TM_OK && uIRQ == 1)
        {
            bIRQTriggered = True;
        }

        if(bIRQTriggered)
        {
            /* IRQ triggered => Exit */
            break;
        }

        if(err == TM_OK && irqStatus != 0x00)
        {
            uIRQStatus = ((pObj->I2CMap.uBx08.IRQ_status)&0x1F);

            if(irqStatus == uIRQStatus)
            {
                bIRQTriggered = True;
            }
        }

        err = ddTDA18273Wait(pObj, waitStep);
    }

    if(counter == 0)
    {
        err = ddTDA18273_ERR_NOT_READY;
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
tmErrorCode_t
ddTDA18273WaitXtalCal_End
(
    ptmddTDA18273Object_t   pObj,       /* I: Instance object */
    UInt32                  timeOut,    /* I: timeout */
    UInt32                  waitStep    /* I: wait step */
)
{     
    tmErrorCode_t   err  = TM_OK;
    UInt32          counter = timeOut/waitStep; /* Wait max timeOut/waitStepms */
    UInt8           uMSM_XtalCal_End = 0;

    while(err == TM_OK && (--counter)>0)
    {
        err = ddTDA18273GetMSM_XtalCal_End(pObj, &uMSM_XtalCal_End);

        if(uMSM_XtalCal_End == 1)
        {
            /* MSM_XtalCal_End triggered => Exit */
            break;
        }

        ddTDA18273Wait(pObj, waitStep);
    }

    if(counter == 0)
    {
        err = ddTDA18273_ERR_NOT_READY;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    ddTDA18273Write                                               */
/*                                                                            */
/* DESCRIPTION: Write in TDA18273 hardware                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t 
ddTDA18273Write
(
    ptmddTDA18273Object_t   pObj,           /* I: Driver object */
    UInt8                   uSubAddress,    /* I: sub address */
    UInt8                   uNbData         /* I: nb of data */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8*          pI2CMap = Null;

    /* pI2CMap initialization */
    pI2CMap = &(pObj->I2CMap.uBx00.ID_byte_1);

    err = POBJ_SRVFUNC_SIO.Write (pObj->tUnitW, 1, &uSubAddress, uNbData, &(pI2CMap[uSubAddress]));

    /* return value */
    return err;
}

/*============================================================================*/
/* FUNCTION:    ddTDA18273Read                                                */
/*                                                                            */
/* DESCRIPTION: Read in TDA18273 hardware                                     */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t 
ddTDA18273Read
(
    ptmddTDA18273Object_t   pObj,           /* I: Driver object */
    UInt8                   uSubAddress,    /* I: sub address */
    UInt8                   uNbData         /* I: nb of data */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8*          pI2CMap = Null;

    /* pRegister initialization */
    pI2CMap = &(pObj->I2CMap.uBx00.ID_byte_1) + uSubAddress;

    /* Read data from the Tuner */
    err = POBJ_SRVFUNC_SIO.Read(pObj->tUnitW, 1, &uSubAddress, uNbData, pI2CMap);

    /* return value */
    return err;
}

/*============================================================================*/
/* FUNCTION:    ddTDA18273Wait                                                */
/*                                                                            */
/* DESCRIPTION: Wait for the requested time                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t 
ddTDA18273Wait
(
    ptmddTDA18273Object_t   pObj,   /* I: Driver object */
    UInt32                  Time    /*  I: time to wait for */
)
{
    tmErrorCode_t   err  = TM_OK;

    /* wait Time ms */
    err = POBJ_SRVFUNC_STIME.Wait (pObj->tUnit, Time);

    /* Return value */
    return err;
}

/*============================================================================*/
/* FUNCTION:    ddTDA18273MutexAcquire                                        */
/*                                                                            */
/* DESCRIPTION: Acquire driver mutex                                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddTDA18273MutexAcquire
(
    ptmddTDA18273Object_t   pObj,
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
/* FUNCTION:    ddTDA18273MutexRelease                                        */
/*                                                                            */
/* DESCRIPTION: Release driver mutex                                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
ddTDA18273MutexRelease
(
    ptmddTDA18273Object_t   pObj
)
{
    tmErrorCode_t   err = TM_OK;

    if(pObj->sMutex.Release != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Release(pObj->pMutex);
    }

    return err;
}
