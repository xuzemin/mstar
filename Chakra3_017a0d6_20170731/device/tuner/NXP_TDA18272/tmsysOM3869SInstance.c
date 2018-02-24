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
 * \file          tmsysOM3869SInstance.c
 *                %version: 2 %
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
   26-Nov-2007  | V.VRIGNAUD|       |       | COMPATIBILITY WITH NXPFE
                | C.CAZETTES|       |       | 
   -------------|-----------|-------|-------|-----------------------------------
                |           |       |       |
   -------------|-----------|-------|-------|-----------------------------------
   \endverbatim
 *
*/

#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmbslFrontEndCfgItem.h"
#include "tmFrontEnd.h"
#include "tmUnitParams.h"

#include "tmbslFrontEndTypes.h"
#include "tmsysFrontEndTypes.h"


#include "tmsysOM3869S.h"
#include "tmsysOM3869Slocal.h"
#include "tmsysOM3869SInstance.h"


//-----------------------------------------------------------------------------
// Global data:
//-----------------------------------------------------------------------------
//
//
static tmOM3869SObject_t gOM3869SInstance[] =
{
    {
        (tmUnitSelect_t)(-1),                                       /* OM3869S unit number */
        (tmUnitSelect_t)(-1),                                       /* OM3869S unit number temporary */
        (tmUnitSelect_t)(-1),                                       /* TDA182I2 unit number */
        Null,                                                       /* pMutex */
        False,                                                      /* init */
        {                                                           /* sRWFunc */
            Null,
            Null
        },
        {                                                           /* sTime */
            Null,
            Null
        },
        {                                                           /* sDebug */
            Null
        },
        {                                                           /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        tmPowerStandby,                                             /* Power State */
        False,                                                      /* resetDone */
        {                                                           /* uHwAddress */
            0x00,                                                   /* tmOM3869SUnitDeviceTypeUnknown */
            0xC0,                                                   /* tmOM3869SUnitDeviceTypeTDA182I2 */
        },
        TRT_DVBT,
    },
    {
        (tmUnitSelect_t)(-1),                                       /* OM3869S unit number */
        (tmUnitSelect_t)(-1),                                       /* OM3869S unit number temporary */
        (tmUnitSelect_t)(-1),                                       /* TDA182I2 unit number */
        Null,                                                       /* pMutex */
        False,                                                      /* init */
        {                                                           /* sRWFunc */
            Null,
            Null
        },
        {                                                           /* sTime */
            Null,
            Null
        },
        {                                                           /* sDebug */
            Null
        },
        {                                                           /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        tmPowerStandby,                                             /* Power State */
        False,                                                      /* resetDone */
        {                                                           /* uHwAddress */
            0x00,                                                   /* tmOM3869SUnitDeviceTypeUnknown */
            0xC6,                                                   /* tmOM3869SUnitDeviceTypeTDA182I2 */
        },
        TRT_DVBT,
    }
};


//-----------------------------------------------------------------------------
// FUNCTION:    OM3869SAllocInstance:
//
// DESCRIPTION: allocate new instance
//
// RETURN:      
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
OM3869SAllocInstance
(
    tmUnitSelect_t      tUnit,      /* I: Unit number */
    pptmOM3869SObject_t  ppDrvObject /* I: Device Object */
)
{ 
    tmErrorCode_t       err = OM3869S_ERR_BAD_UNIT_NUMBER;
    ptmOM3869SObject_t   pObj = Null;
    UInt32              uLoopCounter = 0;    

    /* Find a free instance */
    for(uLoopCounter = 0; uLoopCounter<OM3869S_MAX_UNITS; uLoopCounter++)
    {
        pObj = &gOM3869SInstance[uLoopCounter];
        if(pObj->init == False)
        {
            pObj->tUnit = tUnit;
            pObj->tUnitW = tUnit;

            *ppDrvObject = pObj;
            err = TM_OK;
            break;
        }
    }

    /* return value */
    return err;
}

//-----------------------------------------------------------------------------
// FUNCTION:    OM3869SDeAllocInstance:
//
// DESCRIPTION: deallocate instance
//
// RETURN:      always TM_OK
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
OM3869SDeAllocInstance
(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{     
    tmErrorCode_t       err = OM3869S_ERR_NOT_INITIALIZED;
    ptmOM3869SObject_t   pObj = Null;

    /* check input parameters */
    err = OM3869SGetInstance(tUnit, &pObj);

    /* check driver state */
    if (err == TM_OK)
    {
        if (pObj == Null || pObj->init == False)
        {
            err = OM3869S_ERR_NOT_INITIALIZED;
        }
    }

    if ((err == TM_OK) && (pObj != Null)) 
    {
        pObj->init = False;
    }

    /* return value */
    return err;
}

//-----------------------------------------------------------------------------
// FUNCTION:    OM3869SGetInstance:
//
// DESCRIPTION: get the instance
//
// RETURN:      always True
//
// NOTES:       
//-----------------------------------------------------------------------------
//
tmErrorCode_t
OM3869SGetInstance
(
    tmUnitSelect_t      tUnit,      /* I: Unit number */
    pptmOM3869SObject_t  ppDrvObject /* I: Device Object */
)
{     
    tmErrorCode_t       err = OM3869S_ERR_NOT_INITIALIZED;
    ptmOM3869SObject_t   pObj = Null;
    UInt32              uLoopCounter = 0;    

    /* get instance */
    for(uLoopCounter = 0; uLoopCounter<OM3869S_MAX_UNITS; uLoopCounter++)
    {
        pObj = &gOM3869SInstance[uLoopCounter];
        if(pObj->init == True && pObj->tUnit == GET_INDEX_TYPE_TUNIT(tUnit))
        {
            pObj->tUnitW = tUnit;

            *ppDrvObject = pObj;
            err = TM_OK;
            break;
        }
    }

    /* return value */
    return err;
}

