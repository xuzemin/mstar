/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA182I4_Instance.c
 *
 * \date          %modify_time%
 *
 * \author        David LEGENDRE
 *                Michael VANNIER
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA182I4_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
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
#include "tmbslTDA182I4.h"

#include "tmbslTDA182I4_RegDef.h"
#include "tmbslTDA182I4_Local.h"
#include "tmbslTDA182I4_Instance.h"
#include "tmbslTDA182I4_InstanceCustom.h"


/*============================================================================*/
/* Global data:                                                               */
/*============================================================================*/

/* Driver instance */
TDA182I4Object_t gTDA182I4Instance[TDA182I4_UNITS] = 
{
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA182I4_INSTANCE_CUSTOM_0         /* Instance Customizable Settings */
        TDA182I4_INSTANCE_REGMAP_DEF
    },
#if TDA182I4_UNITS >= 2
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA182I4_INSTANCE_CUSTOM_1          /* Instance Customizable Settings */
        TDA182I4_INSTANCE_REGMAP_DEF
    },
#endif
#if TDA182I4_UNITS >= 3
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA182I4_INSTANCE_CUSTOM_2          /* Instance Customizable Settings */
        TDA182I4_INSTANCE_REGMAP_DEF
    },
#endif
#if TDA182I4_UNITS >= 4
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA182I4_INSTANCE_CUSTOM_3          /* Instance Customizable Settings */
        TDA182I4_INSTANCE_REGMAP_DEF
    }
#endif
};

/*============================================================================*/
/* Internal functions:                                                        */
/*============================================================================*/

/*============================================================================*/
/* FUNCTION:    iTDA182I4_AllocInstance:                                      */
/*                                                                            */
/* DESCRIPTION: Allocates an instance.                                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_AllocInstance(
    tmUnitSelect_t      tUnit,      /* I: Unit number */
    ppTDA182I4Object_t  ppDrvObject /* I: Driver Object */
)
{
    tmErrorCode_t       err = TDA182I4_ERR_ERR_NO_INSTANCES;
    pTDA182I4Object_t   pObj = Null;
    UInt32              uLoopCounter = 0;

    /* Find a free instance */
    for (uLoopCounter = 0; uLoopCounter<TDA182I4_UNITS; uLoopCounter++)
    {
        pObj = &gTDA182I4Instance[uLoopCounter];
        if (pObj->init == False)
        {
            err = TM_OK;

            pObj->tUnit = tUnit;
            pObj->tUnitW = tUnit;

            err = iTDA182I4_ResetInstance(pObj);

            if(err == TM_OK)
            {
                *ppDrvObject = pObj;
            }
            break;
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_DeAllocInstance:                                    */
/*                                                                            */
/* DESCRIPTION: Deallocates an instance.                                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_DeAllocInstance(
    pTDA182I4Object_t  pDrvObject  /* I: Driver Object */
)
{
    tmErrorCode_t   err = TM_OK;

    if(pDrvObject != Null)
    {
        pDrvObject->init = False;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_GetInstance:                                        */
/*                                                                            */
/* DESCRIPTION: Gets an instance.                                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_GetInstance(
    tmUnitSelect_t      tUnit,      /* I: Unit number   */
    ppTDA182I4Object_t  ppDrvObject /* I: Driver Object */
)
{
    tmErrorCode_t       err = TDA182I4_ERR_ERR_NO_INSTANCES;
    pTDA182I4Object_t   pObj = Null;
    UInt32              uLoopCounter = 0;

    /* Get instance */
    for (uLoopCounter = 0; uLoopCounter<TDA182I4_UNITS; uLoopCounter++)
    {
        pObj = &gTDA182I4Instance[uLoopCounter];
        if (pObj->init == True && pObj->tUnit == GET_INDEX_TYPE_TUNIT(tUnit))
        {
            pObj->tUnitW = tUnit;

            *ppDrvObject = pObj;
            err = TM_OK;
            break;
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA182I4_ResetInstance:                                      */
/*                                                                            */
/* DESCRIPTION: Resets an instance.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA182I4_ResetInstance(
    pTDA182I4Object_t  pDrvObject  /* I: Driver Object */
)
{
    tmErrorCode_t   err = TM_OK ;

    pDrvObject->curPowerState = TDA182I4_INSTANCE_CUSTOM_CURPOWERSTATE_DEF;
    pDrvObject->curLLPowerState = TDA182I4_INSTANCE_CUSTOM_CURLLPOWERSTATE_DEF;
    pDrvObject->uRF = TDA182I4_INSTANCE_CUSTOM_RF_DEF;
    pDrvObject->uProgRF = TDA182I4_INSTANCE_CUSTOM_PROG_RF_DEF;

    pDrvObject->StandardMode = TDA182I4_INSTANCE_CUSTOM_STANDARDMODE_DEF;

    pDrvObject->eHwState = TDA182I4_HwState_InitNotDone;

    return err;
}

