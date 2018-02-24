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
/*-----------------------------------------------------------------------------
// $Header: 
// (C) Copyright 2010 NXP Semiconductors, All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of Philips Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of Philips
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than Philips Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmddTDA18273_Alt.c
//
// DESCRIPTION:  TDA18273 standard APIs
//
// NOTES:        
//-----------------------------------------------------------------------------
*/

#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"

#include "tmddTDA18273.h"
#include "tmddTDA18273_Advanced.h"
#include "tmddTDA18273local.h"

#include "tmddTDA18273Instance.h"

/*-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
*/

/*-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
*/

/*-----------------------------------------------------------------------------
// Global data:
//-----------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetTM_D:
//
// DESCRIPTION: Get the TM_D bit(s) status
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
tmddTDA18273GetTM_D
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
        // switch thermometer on
        pObj->I2CMap.uBx04.bF.TM_ON = 1;

        // write byte 0x04
        err = ddTDA18273Write(pObj, 0x04, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // read byte 0x03
            err = ddTDA18273Read(pObj, 0x03, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));
        }

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx03.bF.TM_D;

            // switch thermometer off
            pObj->I2CMap.uBx04.bF.TM_ON = 0;

            // write byte 0x04
            err = ddTDA18273Write(pObj, 0x04, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetTM_ON:
//
// DESCRIPTION: Set the TM_ON bit(s) status
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
tmddTDA18273SetTM_ON
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
        pObj->I2CMap.uBx04.bF.TM_ON = uValue;

        // write byte 0x04
        err = ddTDA18273Write(pObj, 0x04, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetTM_ON:
//
// DESCRIPTION: Get the TM_ON bit(s) status
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
tmddTDA18273GetTM_ON
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
        // read byte 0x04
        err = ddTDA18273Read(pObj, 0x04, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx04.bF.TM_ON;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPOR:
//
// DESCRIPTION: Get the POR bit(s) status
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
tmddTDA18273GetPOR
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x05
        err = ddTDA18273Read(pObj, 0x05, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx05.bF.POR ;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RSSI_End:
//
// DESCRIPTION: Get the MSM_RSSI_End bit(s) status
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
tmddTDA18273GetMSM_RSSI_End
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue   //  I: Address of the variable to output item value
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
        // read byte 0x08
        err = ddTDA18273Read(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_RSSI_End;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_LOCalc_End:
//
// DESCRIPTION: Get the MSM_LOCalc_End bit(s) status
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
tmddTDA18273GetMSM_LOCalc_End
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
        // read byte 0x08
        err = ddTDA18273Read(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_LOCalc_End;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RFCal_End:
//
// DESCRIPTION: Get the MSM_RFCal_End bit(s) status
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
tmddTDA18273GetMSM_RFCal_End
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
        // read byte 0x08
        err = ddTDA18273Read(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_RFCal_End;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_IRCAL_End:
//
// DESCRIPTION: Get the MSM_IRCAL_End bit(s) status
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
tmddTDA18273GetMSM_IRCAL_End
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x08
        err = ddTDA18273Read(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_IRCAL_End;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RCCal_End:
//
// DESCRIPTION: Get the MSM_RCCal_End bit(s) status
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
tmddTDA18273GetMSM_RCCal_End
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
        // read byte 0x08
        err = ddTDA18273Read(pObj, 0x08, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx08.bF.MSM_RCCal_End;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIRQ_Enable:
//
// DESCRIPTION: Set the IRQ_Enable bit(s) status
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
tmddTDA18273SetIRQ_Enable
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
        pObj->I2CMap.uBx09.bF.IRQ_Enable = uValue;

        // write byte 0x09
        err = ddTDA18273Write(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIRQ_Enable:
//
// DESCRIPTION: Get the IRQ_Enable bit(s) status
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
tmddTDA18273GetIRQ_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x09
        err = ddTDA18273Read(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.IRQ_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetXtalCal_Enable:
//
// DESCRIPTION: Set the XtalCal_Enable bit(s) status
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
tmddTDA18273SetXtalCal_Enable
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
        pObj->I2CMap.uBx09.bF.XtalCal_Enable = uValue;

        // write byte 0x09
        err = ddTDA18273Write(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetXtalCal_Enable:
//
// DESCRIPTION: Get the XtalCal_Enable bit(s) status
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
tmddTDA18273GetXtalCal_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x09
        err = ddTDA18273Read(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.XtalCal_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RSSI_Enable:
//
// DESCRIPTION: Set the MSM_RSSI_Enable bit(s) status
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
tmddTDA18273SetMSM_RSSI_Enable
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
        pObj->I2CMap.uBx09.bF.MSM_RSSI_Enable = uValue;

        // write byte 0x09
        err = ddTDA18273Write(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RSSI_Enable:
//
// DESCRIPTION: Get the MSM_RSSI_Enable bit(s) status
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
tmddTDA18273GetMSM_RSSI_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x09
        err = ddTDA18273Read(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_RSSI_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_LOCalc_Enable:
//
// DESCRIPTION: Set the MSM_LOCalc_Enable bit(s) status
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
tmddTDA18273SetMSM_LOCalc_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8          uValue      //  I: Item value
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
        pObj->I2CMap.uBx09.bF.MSM_LOCalc_Enable = uValue;

        // write byte 0x09
        err = ddTDA18273Write(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_LOCalc_Enable:
//
// DESCRIPTION: Get the MSM_LOCalc_Enable bit(s) status
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
tmddTDA18273GetMSM_LOCalc_Enable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x09
        err = ddTDA18273Read(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_LOCalc_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RFCAL_Enable:
//
// DESCRIPTION: Set the MSM_RFCAL_Enable bit(s) status
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
tmddTDA18273SetMSM_RFCAL_Enable
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
        pObj->I2CMap.uBx09.bF.MSM_RFCAL_Enable = uValue;

        // write byte 0x09
        err = ddTDA18273Write(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RFCAL_Enable:
//
// DESCRIPTION: Get the MSM_RFCAL_Enable bit(s) status
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
tmddTDA18273GetMSM_RFCAL_Enable
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
        // read byte 0x09
        err = ddTDA18273Read(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_RFCAL_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_IRCAL_Enable:
//
// DESCRIPTION: Set the MSM_IRCAL_Enable bit(s) status
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
tmddTDA18273SetMSM_IRCAL_Enable
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
        pObj->I2CMap.uBx09.bF.MSM_IRCAL_Enable = uValue;

        // write byte 0x09
        err = ddTDA18273Write(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_IRCAL_Enable:
//
// DESCRIPTION: Get the MSM_IRCAL_Enable bit(s) status
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
tmddTDA18273GetMSM_IRCAL_Enable
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
        // read byte 0x09
        err = ddTDA18273Read(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_IRCAL_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RCCal_Enable:
//
// DESCRIPTION: Set the MSM_RCCal_Enable bit(s) status
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
tmddTDA18273SetMSM_RCCal_Enable
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
        pObj->I2CMap.uBx09.bF.MSM_RCCal_Enable = uValue;

        // write byte 0x09
        err = ddTDA18273Write(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RCCal_Enable:
//
// DESCRIPTION: Get the MSM_RCCal_Enable bit(s) status
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
tmddTDA18273GetMSM_RCCal_Enable
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
        // read byte 0x09
        err = ddTDA18273Read(pObj, 0x09, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx09.bF.MSM_RCCal_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetXtalCal_Clear:
//
// DESCRIPTION: Set the XtalCal_Clear bit(s) status
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
tmddTDA18273SetXtalCal_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8          uValue      //  I: Item value
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
        pObj->I2CMap.uBx0A.bF.XtalCal_Clear = uValue;

        // write byte 0x0A
        err = ddTDA18273Write(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetXtalCal_Clear:
//
// DESCRIPTION: Get the XtalCal_Clear bit(s) status
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
tmddTDA18273GetXtalCal_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x0A
        err = ddTDA18273Read(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.XtalCal_Clear;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RSSI_Clear:
//
// DESCRIPTION: Set the MSM_RSSI_Clear bit(s) status
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
tmddTDA18273SetMSM_RSSI_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8          uValue      //  I: Item value
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
        pObj->I2CMap.uBx0A.bF.MSM_RSSI_Clear = uValue;

        // write byte 0x0A
        err = ddTDA18273Write(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RSSI_Clear:
//
// DESCRIPTION: Get the MSM_RSSI_Clear bit(s) status
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
tmddTDA18273GetMSM_RSSI_Clear
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
        // read byte 0x0A
        err = ddTDA18273Read(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_RSSI_Clear;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_LOCalc_Clear:
//
// DESCRIPTION: Set the MSM_LOCalc_Clear bit(s) status
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
tmddTDA18273SetMSM_LOCalc_Clear
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
        pObj->I2CMap.uBx0A.bF.MSM_LOCalc_Clear = uValue;

        // write byte 0x0A
        err = ddTDA18273Write(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_LOCalc_Clear:
//
// DESCRIPTION: Get the MSM_LOCalc_Clear bit(s) status
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
tmddTDA18273GetMSM_LOCalc_Clear
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
        // read byte 0x0A
        err = ddTDA18273Read(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_LOCalc_Clear;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RFCal_Clear:
//
// DESCRIPTION: Set the MSM_RFCal_Clear bit(s) status
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
tmddTDA18273SetMSM_RFCal_Clear
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
        pObj->I2CMap.uBx0A.bF.MSM_RFCal_Clear = uValue;

        // write byte 0x0A
        err = ddTDA18273Write(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RFCal_Clear:
//
// DESCRIPTION: Get the MSM_RFCal_Clear bit(s) status
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
tmddTDA18273GetMSM_RFCal_Clear
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
        // read byte 0x0A
        err = ddTDA18273Read(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_RFCal_Clear;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_IRCAL_Clear:
//
// DESCRIPTION: Set the MSM_IRCAL_Clear bit(s) status
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
tmddTDA18273SetMSM_IRCAL_Clear
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8          uValue      //  I: Item value
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
        pObj->I2CMap.uBx0A.bF.MSM_IRCAL_Clear = uValue;

        // write byte 0x0A
        err = ddTDA18273Write(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_IRCAL_Clear:
//
// DESCRIPTION: Get the MSM_IRCAL_Clear bit(s) status
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
tmddTDA18273GetMSM_IRCAL_Clear
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
        // read byte 0x0A
        err = ddTDA18273Read(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_IRCAL_Clear;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RCCal_Clear:
//
// DESCRIPTION: Set the MSM_RCCal_Clear bit(s) status
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
tmddTDA18273SetMSM_RCCal_Clear
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
        pObj->I2CMap.uBx0A.bF.MSM_RCCal_Clear = uValue;

        // write byte 0x0A
        err = ddTDA18273Write(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RCCal_Clear:
//
// DESCRIPTION: Get the MSM_RCCal_Clear bit(s) status
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
tmddTDA18273GetMSM_RCCal_Clear
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
        // read byte 0x0A
        err = ddTDA18273Read(pObj, 0x0A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0A.bF.MSM_RCCal_Clear;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIRQ_Set:
//
// DESCRIPTION: Set the IRQ_Set bit(s) status
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
tmddTDA18273SetIRQ_Set
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
        pObj->I2CMap.uBx0B.bF.IRQ_Set = uValue;

        // write byte 0x0B
        err = ddTDA18273Write(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIRQ_Set:
//
// DESCRIPTION: Get the IRQ_Set bit(s) status
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
tmddTDA18273GetIRQ_Set
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
        // read byte 0x0B
        err = ddTDA18273Read(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.IRQ_Set;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetXtalCal_Set:
//
// DESCRIPTION: Set the XtalCal_Set bit(s) status
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
tmddTDA18273SetXtalCal_Set
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
        pObj->I2CMap.uBx0B.bF.XtalCal_Set = uValue;

        // write byte 0x0B
        err = ddTDA18273Write(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetXtalCal_Set:
//
// DESCRIPTION: Get the XtalCal_Set bit(s) status
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
tmddTDA18273GetXtalCal_Set
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
        // read byte 0x0B
        err = ddTDA18273Read(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.XtalCal_Set;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RSSI_Set:
//
// DESCRIPTION: Set the MSM_RSSI_Set bit(s) status
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
tmddTDA18273SetMSM_RSSI_Set
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
        pObj->I2CMap.uBx0B.bF.MSM_RSSI_Set = uValue;

        // write byte 0x0B
        err = ddTDA18273Write(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RSSI_Set:
//
// DESCRIPTION: Get the MSM_RSSI_Set bit(s) status
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
tmddTDA18273GetMSM_RSSI_Set
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
        // read byte 0x0B
        err = ddTDA18273Read(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.MSM_RSSI_Set;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_LOCalc_Set:
//
// DESCRIPTION: Set the MSM_LOCalc_Set bit(s) status
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
tmddTDA18273SetMSM_LOCalc_Set
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
        pObj->I2CMap.uBx0B.bF.MSM_LOCalc_Set = uValue;

        // write byte 0x0B
        err = ddTDA18273Write(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_LOCalc_Set:
//
// DESCRIPTION: Get the MSM_LOCalc_Set bit(s) status
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
tmddTDA18273GetMSM_LOCalc_Set
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
        // read byte 0x0B
        err = ddTDA18273Read(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        // get value
        *puValue = pObj->I2CMap.uBx0B.bF.MSM_LOCalc_Set;

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RFCal_Set:
//
// DESCRIPTION: Set the MSM_RFCal_Set bit(s) status
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
tmddTDA18273SetMSM_RFCal_Set
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
        pObj->I2CMap.uBx0B.bF.MSM_RFCal_Set = uValue;

        // write byte 0x0B
        err = ddTDA18273Write(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RFCal_Set:
//
// DESCRIPTION: Get the MSM_RFCal_Set bit(s) status
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
tmddTDA18273GetMSM_RFCal_Set
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
        // read byte 0x0B
        err = ddTDA18273Read(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.MSM_RFCal_Set;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_IRCAL_Set:
//
// DESCRIPTION: Set the MSM_IRCAL_Set bit(s) status
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
tmddTDA18273SetMSM_IRCAL_Set
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
        pObj->I2CMap.uBx0B.bF.MSM_IRCAL_Set = uValue;

        // write byte 0x0B
        err = ddTDA18273Write(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_IRCAL_Set:
//
// DESCRIPTION: Get the MSM_IRCAL_Set bit(s) status
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
tmddTDA18273GetMSM_IRCAL_Set
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
        // read byte 0x0B
        err = ddTDA18273Read(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.MSM_IRCAL_Set;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetMSM_RCCal_Set:
//
// DESCRIPTION: Set the MSM_RCCal_Set bit(s) status
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
tmddTDA18273SetMSM_RCCal_Set
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8            uValue //  I: Item value
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
        pObj->I2CMap.uBx0B.bF.MSM_RCCal_Set = uValue;

        // write byte 0x0B
        err = ddTDA18273Write(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetMSM_RCCal_Set:
//
// DESCRIPTION: Get the MSM_RCCal_Set bit(s) status
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
tmddTDA18273GetMSM_RCCal_Set
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
        // read byte 0x0B
        err = ddTDA18273Read(pObj, 0x0B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0B.bF.MSM_RCCal_Set;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetAGCs_Up_Step_assym:
//
// DESCRIPTION: Set the AGCs_Up_Step_assym bit(s) status
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
tmddTDA18273SetAGCs_Up_Step_assym
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
        pObj->I2CMap.uBx0F.bF.AGCs_Up_Step_assym = uValue;

        // write byte 0x0F
        err = ddTDA18273Write(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGCs_Up_Step_assym:
//
// DESCRIPTION: Get the AGCs_Up_Step_assym bit(s) status
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
tmddTDA18273GetAGCs_Up_Step_assym
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x0F
        err = ddTDA18273Read(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0F.bF.AGCs_Up_Step_assym;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPulse_Shaper_Disable:
//
// DESCRIPTION: Set the Pulse_Shaper_Disable bit(s) status
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
tmddTDA18273SetPulse_Shaper_Disable
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
        pObj->I2CMap.uBx0F.bF.Pulse_Shaper_Disable = uValue;

        // write byte 0x0F
        err = ddTDA18273Write(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPulse_Shaper_Disable:
//
// DESCRIPTION: Get the Pulse_Shaper_Disable bit(s) status
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
tmddTDA18273GetPulse_Shaper_Disable
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*        puValue      //  I: Address of the variable to output item value
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
        // read byte 0x0F
        err = ddTDA18273Read(pObj, 0x0F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx0F.bF.Pulse_Shaper_Disable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFAGC_Low_BW:
//
// DESCRIPTION: Set the RFAGC_Low_BW bit(s) status
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
tmddTDA18273SetRFAGC_Low_BW
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
        pObj->I2CMap.uBx10.bF.RFAGC_Low_BW = uValue;

        // write byte 0x10
        err = ddTDA18273Write(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFAGC_Low_BW:
//
// DESCRIPTION: Get the RFAGC_Low_BW bit(s) status
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
tmddTDA18273GetRFAGC_Low_BW
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
        // read byte 0x10
        err = ddTDA18273Read(pObj, 0x10, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx10.bF.RFAGC_Low_BW;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetW_Filter_Enable:
//
// DESCRIPTION: Set the W_Filter_Enable bit(s) status
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
tmddTDA18273SetW_Filter_Enable
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
        pObj->I2CMap.uBx11.bF.W_Filter_Enable = uValue;

        // write byte 0x11
        err = ddTDA18273Write(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetW_Filter_Enable:
//
// DESCRIPTION: Get the W_Filter_Enable bit(s) status
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
tmddTDA18273GetW_Filter_Enable
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
            *puValue = pObj->I2CMap.uBx11.bF.W_Filter_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetW_Filter_Bypass:
//
// DESCRIPTION: Set the W_Filter_Bypass bit(s) status
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
tmddTDA18273SetW_Filter_Bypass
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
        pObj->I2CMap.uBx11.bF.W_Filter_Bypass = uValue;

        // write byte 0x11
        err = ddTDA18273Write(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetW_Filter_Bypass:
//
// DESCRIPTION: Get the W_Filter_Bypass bit(s) status
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
tmddTDA18273GetW_Filter_Bypass
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
            *puValue = pObj->I2CMap.uBx11.bF.W_Filter_Bypass;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetW_Filter:
//
// DESCRIPTION: Set the W_Filter bit(s) status
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
tmddTDA18273SetW_Filter
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
        pObj->I2CMap.uBx11.bF.W_Filter = uValue;

        // write byte 0x11
        err = ddTDA18273Write(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetW_Filter:
//
// DESCRIPTION: Get the W_Filter bit(s) status
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
tmddTDA18273GetW_Filter
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
            *puValue = pObj->I2CMap.uBx11.bF.W_Filter;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetW_Filter_Offset:
//
// DESCRIPTION: Set the W_Filter_Offset bit(s) status
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
tmddTDA18273SetW_Filter_Offset
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
        pObj->I2CMap.uBx11.bF.W_Filter_Offset = uValue;

        // write byte 0x11
        err = ddTDA18273Write(pObj, 0x11, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetW_Filter_Offset:
//
// DESCRIPTION: Get the W_Filter_Offset bit(s) status
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
tmddTDA18273GetW_Filter_Offset
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
            *puValue = pObj->I2CMap.uBx11.bF.W_Filter_Offset;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetAGCs_Do_Step_assym:
//
// DESCRIPTION: Set the AGCs_Do_Step_assym bit(s) status
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
tmddTDA18273SetAGCs_Do_Step_assym
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
        pObj->I2CMap.uBx13.bF.AGCs_Do_Step_assym = uValue;

        // write byte 0x13
        err = ddTDA18273Write(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGCs_Do_Step_assym:
//
// DESCRIPTION: Get the AGCs_Do_Step_assym bit(s) status
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
tmddTDA18273GetAGCs_Do_Step_assym
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
        // read byte 0x13
        err = ddTDA18273Read(pObj, 0x13, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx13.bF.AGCs_Do_Step_assym;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }
    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIFnotchToRSSI                                  */
/*                                                                            */
/* DESCRIPTION: Set the IFnotchToRSSI bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIFnotchToRSSI
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
        pObj->I2CMap.uBx14.bF.IFnotchToRSSI = uValue;

        /* Write byte 0x14 */
        err = ddTDA18273Write(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIFnotchToRSSI                                  */
/*                                                                            */
/* DESCRIPTION: Get the IFnotchToRSSI bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIFnotchToRSSI
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
            *puValue = pObj->I2CMap.uBx14.bF.IFnotchToRSSI;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetLPF_DCOffset_Corr                              */
/*                                                                            */
/* DESCRIPTION: Set the LPF_DCOffset_Corr bit(s) status                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetLPF_DCOffset_Corr
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
        pObj->I2CMap.uBx14.bF.LPF_DCOffset_Corr = uValue;

        /* Write byte 0x14 */
        err = ddTDA18273Write(pObj, 0x14, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetLPF_DCOffset_Corr                              */
/*                                                                            */
/* DESCRIPTION: Get the LPF_DCOffset_Corr bit(s) status                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetLPF_DCOffset_Corr
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
            *puValue = pObj->I2CMap.uBx14.bF.LPF_DCOffset_Corr;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetDigital_Clock_Mode                             */
/*                                                                            */
/* DESCRIPTION: Set the Digital_Clock_Mode bit(s) status                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetDigital_Clock_Mode
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
        pObj->I2CMap.uBx16.bF.XTout = 3;
        pObj->I2CMap.uBx16.bF.Digital_Clock_Mode = uValue;

        /* Write byte 0x16 */
        err = ddTDA18273Write(pObj, 0x16, 1);
		  	//printf("TDA18273SetPowerState10 =%d\n",err);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetDigital_Clock_Mode                             */
/*                                                                            */
/* DESCRIPTION: Get the Digital_Clock_Mode bit(s) status                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetDigital_Clock_Mode
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
        /* Read byte 0x16 */
        err = ddTDA18273Read(pObj, 0x16, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx16.bF.Digital_Clock_Mode;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetXTout:
//
// DESCRIPTION: Set the XTout bit(s) status
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
tmddTDA18273SetXTout
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
        pObj->I2CMap.uBx16.bF.XTout = uValue;

        // write byte 0x16
        err = ddTDA18273Write(pObj, 0x16, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetXTout:
//
// DESCRIPTION: Get the XTout bit(s) status
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
tmddTDA18273GetXTout
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
        // read byte 0x16
        err = ddTDA18273Read(pObj, 0x16, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx16.bF.XTout;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRSSI_Meas:
//
// DESCRIPTION: Set the RSSI_Meas bit(s) status
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
tmddTDA18273SetRSSI_Meas
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
        pObj->I2CMap.uBx1B.bF.RSSI_Meas = uValue;

        // read byte 0x1B
        err = ddTDA18273Write(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRSSI_Meas:
//
// DESCRIPTION: Get the RSSI_Meas bit(s) status
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
tmddTDA18273GetRSSI_Meas
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
        // read byte 0x1B
        err = ddTDA18273Read(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.RSSI_Meas;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRF_CAL_AV:
//
// DESCRIPTION: Set the RF_CAL_AV bit(s) status
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
tmddTDA18273SetRF_CAL_AV
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
        pObj->I2CMap.uBx1B.bF.RF_CAL_AV = uValue;

        // read byte 0x1B
        err = ddTDA18273Write(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRF_CAL_AV:
//
// DESCRIPTION: Get the RF_CAL_AV bit(s) status
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
tmddTDA18273GetRF_CAL_AV
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
        // read byte 0x1B
        err = ddTDA18273Read(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.RF_CAL_AV;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRF_CAL:
//
// DESCRIPTION: Set the RF_CAL bit(s) status
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
tmddTDA18273SetRF_CAL
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

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
        // set value
        pObj->I2CMap.uBx1B.bF.RF_CAL = uValue;

        // read byte 0x1B
        err = ddTDA18273Write(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRF_CAL:
//
// DESCRIPTION: Get the RF_CAL bit(s) status
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
tmddTDA18273GetRF_CAL
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue      //  I: Address of the variable to output item value
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
        // read byte 0x1B
        err = ddTDA18273Read(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.RF_CAL;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIR_CAL_Loop:
//
// DESCRIPTION: Set the IR_CAL_Loop bit(s) status
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
tmddTDA18273SetIR_CAL_Loop
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
        pObj->I2CMap.uBx1B.bF.IR_CAL_Loop = uValue;

        // read byte 0x1B
        err = ddTDA18273Write(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIR_CAL_Loop:
//
// DESCRIPTION: Get the IR_CAL_Loop bit(s) status
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
tmddTDA18273GetIR_CAL_Loop
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
        // read byte 0x1B
        err = ddTDA18273Read(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.IR_CAL_Loop;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIR_Cal_Image:
//
// DESCRIPTION: Set the IR_Cal_Image bit(s) status
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
tmddTDA18273SetIR_Cal_Image
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
        pObj->I2CMap.uBx1B.bF.IR_Cal_Image = uValue;

        // read byte 0x1B
        err = ddTDA18273Write(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIR_Cal_Image:
//
// DESCRIPTION: Get the IR_Cal_Image bit(s) status
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
tmddTDA18273GetIR_Cal_Image
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
        // read byte 0x1B
        err = ddTDA18273Read(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.IR_Cal_Image;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIR_CAL_Wanted:
//
// DESCRIPTION: Set the IR_CAL_Wanted bit(s) status
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
tmddTDA18273SetIR_CAL_Wanted
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue  //  I: Item value
 )
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

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
        // set value
        pObj->I2CMap.uBx1B.bF.IR_CAL_Wanted = uValue;

        // read byte 0x1B
        err = ddTDA18273Write(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIR_CAL_Wanted:
//
// DESCRIPTION: Get the IR_CAL_Wanted bit(s) status
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
tmddTDA18273GetIR_CAL_Wanted
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
        // read byte 0x1B
        err = ddTDA18273Read(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.IR_CAL_Wanted;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRC_Cal:
//
// DESCRIPTION: Set the RC_Cal bit(s) status
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
tmddTDA18273SetRC_Cal
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
        pObj->I2CMap.uBx1B.bF.RC_Cal = uValue;

        // read byte 0x1B
        err = ddTDA18273Write(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRC_Cal:
//
// DESCRIPTION: Get the RC_Cal bit(s) status
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
tmddTDA18273GetRC_Cal
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
        // read byte 0x1B
        err = ddTDA18273Read(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.RC_Cal;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetCalc_PLL:
//
// DESCRIPTION: Set the Calc_PLL bit(s) status
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
tmddTDA18273SetCalc_PLL
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
        pObj->I2CMap.uBx1B.bF.Calc_PLL = uValue;

        // read byte 0x1B
        err = ddTDA18273Write(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetCalc_PLL:
//
// DESCRIPTION: Get the Calc_PLL bit(s) status
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
tmddTDA18273GetCalc_PLL
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
        // read byte 0x1B
        err = ddTDA18273Read(pObj, 0x1B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1B.bF.Calc_PLL;
        }

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

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetXtalCal_Launch:
//
// DESCRIPTION: Get the XtalCal_Launch bit(s) status
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
tmddTDA18273GetXtalCal_Launch
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
        // read byte 0x1C
        err = ddTDA18273Read(pObj, 0x1C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1C.bF.XtalCal_Launch;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPSM_AGC1:
//
// DESCRIPTION: Set the PSM_AGC1 bit(s) status
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
tmddTDA18273SetPSM_AGC1
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
        pObj->I2CMap.uBx1D.bF.PSM_AGC1 = uValue;

        // read byte 0x1D
        err = ddTDA18273Write(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPSM_AGC1:
//
// DESCRIPTION: Get the PSM_AGC1 bit(s) status
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
tmddTDA18273GetPSM_AGC1
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
        // read byte 0x1D
        err = ddTDA18273Read(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1D.bF.PSM_AGC1;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPSMRFpoly:
//
// DESCRIPTION: Set the PSMRFpoly bit(s) status
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
tmddTDA18273SetPSMRFpoly
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
        pObj->I2CMap.uBx1D.bF.PSMRFpoly = uValue;

        // read byte 0x1D
        err = ddTDA18273Write(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPSMRFpoly:
//
// DESCRIPTION: Get the PSMRFpoly bit(s) status
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
tmddTDA18273GetPSMRFpoly
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
        // read byte 0x1D
        err = ddTDA18273Read(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        // get value
        *puValue = pObj->I2CMap.uBx1D.bF.PSMRFpoly;

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPSM_Mixer:
//
// DESCRIPTION: Set the PSM_Mixer bit(s) status
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
tmddTDA18273SetPSM_Mixer
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
        pObj->I2CMap.uBx1D.bF.PSM_Mixer = uValue;

        // read byte 0x1D
        err = ddTDA18273Write(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPSM_Mixer:
//
// DESCRIPTION: Get the PSM_Mixer bit(s) status
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
tmddTDA18273GetPSM_Mixer
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
        // read byte 0x1D
        err = ddTDA18273Read(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1D.bF.PSM_Mixer;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPSM_Ifpoly:
//
// DESCRIPTION: Set the PSM_Ifpoly bit(s) status
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
tmddTDA18273SetPSM_Ifpoly
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
        pObj->I2CMap.uBx1D.bF.PSM_Ifpoly = uValue;

        // read byte 0x1D
        err = ddTDA18273Write(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPSM_Ifpoly:
//
// DESCRIPTION: Get the PSM_Ifpoly bit(s) status
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
tmddTDA18273GetPSM_Ifpoly
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
        // read byte 0x1D
        err = ddTDA18273Read(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1D.bF.PSM_Ifpoly;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPSM_Lodriver:
//
// DESCRIPTION: Set the PSM_Lodriver bit(s) status
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
tmddTDA18273SetPSM_Lodriver
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
        pObj->I2CMap.uBx1D.bF.PSM_Lodriver = uValue;

        // read byte 0x1D
        err = ddTDA18273Write(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPSM_Lodriver:
//
// DESCRIPTION: Get the PSM_Lodriver bit(s) status
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
tmddTDA18273GetPSM_Lodriver
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
        // read byte 0x1D
        err = ddTDA18273Read(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1D.bF.PSM_Lodriver;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetPSM_Bandsplit_Filter                           */
/*                                                                            */
/* DESCRIPTION: Set the PSM_Bandsplit_Filter bit(s) status                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetPSM_Bandsplit_Filter
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
        pObj->I2CMap.uBx1D.bF.PSM_Bandsplit_Filter = uValue;

        /* Read byte 0x1D */
        err = ddTDA18273Write(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetPSM_Bandsplit_Filter                           */
/*                                                                            */
/* DESCRIPTION: Get the PSM_Bandsplit_Filter bit(s) status                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetPSM_Bandsplit_Filter
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
        /* Read byte 0x1D */
        err = ddTDA18273Read(pObj, 0x1D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1D.bF.PSM_Bandsplit_Filter;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPLD_Gain_Corr:
//
// DESCRIPTION: Set the PLD_Gain_Corr bit(s) status
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
tmddTDA18273SetPLD_Gain_Corr
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 Int8           uValue  //  I: Item value
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
        pObj->I2CMap.uBx1E.bF.PLD_Gain_Corr = uValue;

        // read byte 0x1E
        err = ddTDA18273Write(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPLD_Gain_Corr:
//
// DESCRIPTION: Get the PLD_Gain_Corr bit(s) status
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
tmddTDA18273GetPLD_Gain_Corr
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 Int8*          puValue //  I: Address of the variable to output item value
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
        // read byte 0x1E
        err = ddTDA18273Read(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1E.bF.PLD_Gain_Corr;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetPLD_Temp_Slope                                 */
/*                                                                            */
/* DESCRIPTION: Set the PLD_Temp_Slope bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetPLD_Temp_Slope
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
        pObj->I2CMap.uBx1E.bF.PLD_Temp_Slope = uValue;

        /* Read byte 0x1E */
        err = ddTDA18273Write(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetPLD_Temp_Slope                                 */
/*                                                                            */
/* DESCRIPTION: Get the PLD_Temp_Slope bit(s) status                          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetPLD_Temp_Slope
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
        /* Read byte 0x1E */
        err = ddTDA18273Read(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1E.bF.PLD_Temp_Slope;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetPD_PLD_read                                    */
/*                                                                            */
/* DESCRIPTION: Set the PD_PLD_read bit(s) status                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetPD_PLD_read
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
        pObj->I2CMap.uBx1E.bF.PD_PLD_read = uValue;

        /* Read byte 0x1E */
        err = ddTDA18273Write(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetPD_PLD_read                                    */
/*                                                                            */
/* DESCRIPTION: Get the PD_PLD_read bit(s) status                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetPD_PLD_read
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
        /* Read byte 0x1E */
        err = ddTDA18273Read(pObj, 0x1E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1E.bF.PD_PLD_read;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRange_LNA_Adapt:
//
// DESCRIPTION: Set the Range_LNA_Adapt bit(s) status
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
tmddTDA18273SetRange_LNA_Adapt
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
        pObj->I2CMap.uBx1F.bF.Range_LNA_Adapt = uValue;

        // read byte 0x1F
        err = ddTDA18273Write(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRange_LNA_Adapt:
//
// DESCRIPTION: Get the Range_LNA_Adapt bit(s) status
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
tmddTDA18273GetRange_LNA_Adapt
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
        // read byte 0x1F
        err = ddTDA18273Read(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1F.bF.Range_LNA_Adapt;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetIndex_K_LNA_Adapt                              */
/*                                                                            */
/* DESCRIPTION: Set the Index_K_LNA_Adapt bit(s) status                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetIndex_K_LNA_Adapt
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
        pObj->I2CMap.uBx1F.bF.Index_K_LNA_Adapt = uValue;

        /* Write byte 0x1F */
        err = ddTDA18273Write(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetIndex_K_LNA_Adapt                              */
/*                                                                            */
/* DESCRIPTION: Get the Index_K_LNA_Adapt bit(s) status                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetIndex_K_LNA_Adapt
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
        /* Read byte 0x1F */
        err = ddTDA18273Read(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1F.bF.Index_K_LNA_Adapt;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIndex_K_Top_Adapt:
//
// DESCRIPTION: Set the Index_K_Top_Adapt bit(s) status
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
tmddTDA18273SetIndex_K_Top_Adapt
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
        pObj->I2CMap.uBx1F.bF.Index_K_Top_Adapt = uValue;

        // read byte 0x1F
        err = ddTDA18273Write(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIndex_K_Top_Adapt:
//
// DESCRIPTION: Get the Index_K_Top_Adapt bit(s) status
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
tmddTDA18273GetIndex_K_Top_Adapt
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
        // read byte 0x1F
        err = ddTDA18273Read(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1F.bF.Index_K_Top_Adapt;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetOvld_Udld_FastUp:
//
// DESCRIPTION: Set the Ovld_Udld_FastUp bit(s) status
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
tmddTDA18273SetOvld_Udld_FastUp
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
        pObj->I2CMap.uBx1F.bF.Ovld_Udld_FastUp = uValue;

        // read byte 0x1F
        err = ddTDA18273Write(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetOvld_Udld_FastUp:
//
// DESCRIPTION: Get the Ovld_Udld_FastUp bit(s) status
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
tmddTDA18273GetOvld_Udld_FastUp
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
        // read byte 0x1F
        err = ddTDA18273Read(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx1F.bF.Ovld_Udld_FastUp;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetFast_Mode_AGC                                  */
/*                                                                            */
/* DESCRIPTION: Set the Fast_Mode_AGC bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetFast_Mode_AGC
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
        pObj->I2CMap.uBx1F.bF.Fast_Mode_AGC = uValue;

        /* Read byte 0x1F */
        err = ddTDA18273Write(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetFast_Mode_AGC                                  */
/*                                                                            */
/* DESCRIPTION: Get the Fast_Mode_AGC bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetFast_Mode_AGC
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
        /* Read byte 0x1F */
        err = ddTDA18273Read(pObj, 0x1F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Get value */
            *puValue = pObj->I2CMap.uBx1F.bF.Fast_Mode_AGC;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetNeg_modulation:
//
// DESCRIPTION: Set the Neg_modulation bit(s) status
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
tmddTDA18273SetNeg_modulation
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
        pObj->I2CMap.uBx20.bF.Neg_modulation = uValue;

        // read byte 0x20
        err = ddTDA18273Write(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetNeg_modulation:
//
// DESCRIPTION: Get the Neg_modulation bit(s) status
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
tmddTDA18273GetNeg_modulation
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
        // read byte 0x20
        err = ddTDA18273Read(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx20.bF.Neg_modulation;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetTracer_Step:
//
// DESCRIPTION: Set the Tracer_Step bit(s) status
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
tmddTDA18273SetTracer_Step
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
        pObj->I2CMap.uBx20.bF.Tracer_Step = uValue;

        // read byte 0x20
        err = ddTDA18273Write(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetTracer_Step:
//
// DESCRIPTION: Get the Tracer_Step bit(s) status
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
tmddTDA18273GetTracer_Step
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
        // read byte 0x20
        err = ddTDA18273Read(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx20.bF.Tracer_Step;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetVsync_int:
//
// DESCRIPTION: Set the Vsync_int bit(s) status
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
tmddTDA18273SetVsync_int
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
        pObj->I2CMap.uBx20.bF.Vsync_int = uValue;

        // read byte 0x20
        err = ddTDA18273Write(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetVsync_int:
//
// DESCRIPTION: Get the Vsync_int bit(s) status
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
tmddTDA18273GetVsync_int
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
        // read byte 0x20
        err = ddTDA18273Read(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx20.bF.Vsync_int;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetVsync_Thresh:
//
// DESCRIPTION: Set the Vsync_Thresh bit(s) status
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
tmddTDA18273SetVsync_Thresh
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
        pObj->I2CMap.uBx20.bF.Vsync_Thresh = uValue;

        // read byte 0x20
        err = ddTDA18273Write(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetVsync_Thresh:
//
// DESCRIPTION: Get the Vsync_Thresh bit(s) status
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
tmddTDA18273GetVsync_Thresh
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
        // read byte 0x20
        err = ddTDA18273Read(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx20.bF.Vsync_Thresh;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetVsync_Len:
//
// DESCRIPTION: Set the Vsync_Len bit(s) status
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
tmddTDA18273SetVsync_Len
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
        pObj->I2CMap.uBx20.bF.Vsync_Len = uValue;

        // read byte 0x20
        err = ddTDA18273Write(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetVsync_Len:
//
// DESCRIPTION: Get the Vsync_Len bit(s) status
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
tmddTDA18273GetVsync_Len
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
        // read byte 0x20
        err = ddTDA18273Read(pObj, 0x20, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx20.bF.Vsync_Len;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPD_Vsync_Mgt:
//
// DESCRIPTION: Set the PD_Vsync_Mgt bit(s) status
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
tmddTDA18273SetPD_Vsync_Mgt
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
        pObj->I2CMap.uBx21.bF.PD_Vsync_Mgt = uValue;

        // write byte 0x21
        err = ddTDA18273Write(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPD_Vsync_Mgt:
//
// DESCRIPTION: Get the PD_Vsync_Mgt bit(s) status
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
tmddTDA18273GetPD_Vsync_Mgt
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
        // read byte 0x21
        err = ddTDA18273Read(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx21.bF.PD_Vsync_Mgt;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPD_Ovld:
//
// DESCRIPTION: Set the PD_Ovld bit(s) status
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
tmddTDA18273SetPD_Ovld
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
        pObj->I2CMap.uBx21.bF.PD_Ovld = uValue;

        // write byte 0x21
        err = ddTDA18273Write(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPD_Ovld:
//
// DESCRIPTION: Get the PD_Ovld bit(s) status
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
tmddTDA18273GetPD_Ovld
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
        // read byte 0x21
        err = ddTDA18273Read(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx21.bF.PD_Ovld;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetAGC_Ovld_Timer:
//
// DESCRIPTION: Set the AGC_Ovld_Timer bit(s) status
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
tmddTDA18273SetAGC_Ovld_Timer
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
        pObj->I2CMap.uBx21.bF.AGC_Ovld_Timer = uValue;

        // write byte 0x21
        err = ddTDA18273Write(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC_Ovld_Timer:
//
// DESCRIPTION: Get the AGC_Ovld_Timer bit(s) status
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
tmddTDA18273GetAGC_Ovld_Timer
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
        // read byte 0x21
        err = ddTDA18273Read(pObj, 0x21, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx21.bF.AGC_Ovld_Timer;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIR_Mixer_loop_off:
//
// DESCRIPTION: Set the IR_Mixer_loop_off bit(s) status
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
tmddTDA18273SetIR_Mixer_loop_off
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
        pObj->I2CMap.uBx22.bF.IR_Mixer_loop_off = uValue;

        // read byte 0x22
        err = ddTDA18273Write(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIR_Mixer_loop_off:
//
// DESCRIPTION: Get the IR_Mixer_loop_off bit(s) status
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
tmddTDA18273GetIR_Mixer_loop_off
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
        // read byte 0x22
        err = ddTDA18273Read(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx22.bF.IR_Mixer_loop_off;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIR_Mixer_Do_step:
//
// DESCRIPTION: Set the IR_Mixer_Do_step bit(s) status
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
tmddTDA18273SetIR_Mixer_Do_step
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
        pObj->I2CMap.uBx22.bF.IR_Mixer_Do_step = uValue;

        // read byte 0x22
        err = ddTDA18273Write(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIR_Mixer_Do_step:
//
// DESCRIPTION: Get the IR_Mixer_Do_step bit(s) status
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
tmddTDA18273GetIR_Mixer_Do_step
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
        // read byte 0x22
        err = ddTDA18273Read(pObj, 0x22, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx22.bF.IR_Mixer_Do_step;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetAGC1_loop_off:
//
// DESCRIPTION: Set the AGC1_loop_off bit(s) status
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
tmddTDA18273SetAGC1_loop_off
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
        pObj->I2CMap.uBx23.bF.AGC1_loop_off = uValue;

        // read byte 0x23
        err = ddTDA18273Write(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC1_loop_off:
//
// DESCRIPTION: Get the AGC1_loop_off bit(s) status
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
tmddTDA18273GetAGC1_loop_off
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
            *puValue = pObj->I2CMap.uBx23.bF.AGC1_loop_off;
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
// FUNCTION:    tmddTDA18273SetForce_AGC1_gain:
//
// DESCRIPTION: Set the Force_AGC1_gain bit(s) status
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
tmddTDA18273SetForce_AGC1_gain
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
        pObj->I2CMap.uBx23.bF.Force_AGC1_gain = uValue;

        // read byte 0x23
        err = ddTDA18273Write(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetForce_AGC1_gain:
//
// DESCRIPTION: Get the Force_AGC1_gain bit(s) status
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
tmddTDA18273GetForce_AGC1_gain
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
            *puValue = pObj->I2CMap.uBx23.bF.Force_AGC1_gain;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetAGC1_Gain:
//
// DESCRIPTION: Set the AGC1_Gain bit(s) status
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
tmddTDA18273SetAGC1_Gain
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
        pObj->I2CMap.uBx23.bF.AGC1_Gain = uValue;

        // read byte 0x23
        err = ddTDA18273Write(pObj, 0x23, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC1_Gain:
//
// DESCRIPTION: Get the AGC1_Gain bit(s) status
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
tmddTDA18273GetAGC1_Gain
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
            *puValue = pObj->I2CMap.uBx23.bF.AGC1_Gain;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPLD_DAC_Scale:
//
// DESCRIPTION: Set the PLD_DAC_Scale bit(s) status
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
tmddTDA18273SetPLD_DAC_Scale
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
        pObj->I2CMap.uBx24.bF.PLD_DAC_Scale = uValue;

        // read byte 0x24
        err = ddTDA18273Write(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPLD_DAC_Scale:
//
// DESCRIPTION: Get the PLD_DAC_Scale bit(s) status
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
tmddTDA18273GetPLD_DAC_Scale
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
        // read byte 0x24
        err = ddTDA18273Read(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.PLD_DAC_Scale;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPLD_CC_Enable:
//
// DESCRIPTION: Set the PLD_CC_Enable bit(s) status
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
tmddTDA18273SetPLD_CC_Enable
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
        pObj->I2CMap.uBx24.bF.PLD_CC_Enable = uValue;

        // read byte 0x24
        err = ddTDA18273Write(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPLD_CC_Enable:
//
// DESCRIPTION: Get the PLD_CC_Enable bit(s) status
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
tmddTDA18273GetPLD_CC_Enable
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
        // read byte 0x24
        err = ddTDA18273Read(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.PLD_CC_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetPLD_Temp_Enable:
//
// DESCRIPTION: Set the PLD_Temp_Enable bit(s) status
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
tmddTDA18273SetPLD_Temp_Enable
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
        pObj->I2CMap.uBx24.bF.PLD_Temp_Enable = uValue;

        // read byte 0x24
        err = ddTDA18273Write(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetPLD_Temp_Enable:
//
// DESCRIPTION: Get the PLD_Temp_Enable bit(s) status
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
tmddTDA18273GetPLD_Temp_Enable
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
        // read byte 0x24
        err = ddTDA18273Read(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.PLD_Temp_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetTH_AGC_Adapt34:
//
// DESCRIPTION: Set the TH_AGC_Adapt34 bit(s) status
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
tmddTDA18273SetTH_AGC_Adapt34
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
        pObj->I2CMap.uBx24.bF.TH_AGC_Adapt34 = uValue;

        // read byte 0x24
        err = ddTDA18273Write(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetTH_AGC_Adapt34:
//
// DESCRIPTION: Get the TH_AGC_Adapt34 bit(s) status
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
tmddTDA18273GetTH_AGC_Adapt34
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
        // read byte 0x24
        err = ddTDA18273Read(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.TH_AGC_Adapt34;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFAGC_Sense_Enable:
//
// DESCRIPTION: Set the RFAGC_Sense_Enable bit(s) status
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
tmddTDA18273SetRFAGC_Sense_Enable
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
        pObj->I2CMap.uBx24.bF.RFAGC_Sense_Enable = uValue;

        // read byte 0x24
        err = ddTDA18273Write(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFAGC_Sense_Enable:
//
// DESCRIPTION: Get the RFAGC_Sense_Enable bit(s) status
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
tmddTDA18273GetRFAGC_Sense_Enable
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
        // read byte 0x24
        err = ddTDA18273Read(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.RFAGC_Sense_Enable;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFAGC_K_Bypass:
//
// DESCRIPTION: Set the RFAGC_K_Bypass bit(s) status
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
tmddTDA18273SetRFAGC_K_Bypass
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
        pObj->I2CMap.uBx24.bF.RFAGC_K_Bypass = uValue;

        // read byte 0x24
        err = ddTDA18273Write(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFAGC_K_Bypass:
//
// DESCRIPTION: Get the RFAGC_K_Bypass bit(s) status
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
tmddTDA18273GetRFAGC_K_Bypass
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
        // read byte 0x24
        err = ddTDA18273Read(pObj, 0x24, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx24.bF.RFAGC_K_Bypass;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFAGC_K:
//
// DESCRIPTION: Set the RFAGC_K bit(s) status
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
tmddTDA18273SetRFAGC_K
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt16          uValue  //  I: Item value
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
        pObj->I2CMap.uBx24.bF.RFAGC_K_8 = (UInt8)((uValue >> 8) & 0x1);
        pObj->I2CMap.uBx25.RFAGC_K = (UInt8)((uValue & 0xFF));

        // write byte 0x24-0x25
        err = ddTDA18273Write(pObj, 0x24, 2);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFAGC_K:
//
// DESCRIPTION: Get the RFAGC_K bit(s) status
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
tmddTDA18273GetRFAGC_K
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt16*         puValue //  I: Address of the variable to output item value
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
        // read byte 0x24-0x25
        err = ddTDA18273Read(pObj, 0x24, 2);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = 0;
            *puValue = ((pObj->I2CMap.uBx24.bF.RFAGC_K_8 << 8) | (pObj->I2CMap.uBx25.RFAGC_K));
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset0:
//
// DESCRIPTION: Set the RFCAL_Offset0 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset0
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
        pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog0 = uValue;

        // read byte 0x27
        err = ddTDA18273Write(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset0:
//
// DESCRIPTION: Get the RFCAL_Offset0 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset0
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
        // read byte 0x27
        err = ddTDA18273Read(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog0;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset1:
//
// DESCRIPTION: Set the RFCAL_Offset1 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset1
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
        pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog1 = uValue;

        // read byte 0x27
        err = ddTDA18273Write(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset1:
//
// DESCRIPTION: Get the RFCAL_Offset1 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset1
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
        // read byte 0x27
        err = ddTDA18273Read(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog1;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset2:
//
// DESCRIPTION: Set the RFCAL_Offset2 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset2
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
        pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog2 = uValue;

        // read byte 0x27
        err = ddTDA18273Write(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset2:
//
// DESCRIPTION: Get the RFCAL_Offset2 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset2
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
        // read byte 0x27
        err = ddTDA18273Read(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog2;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset3:
//
// DESCRIPTION: Set the RFCAL_Offset3 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset3
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
        pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog3 = uValue;

        // read byte 0x27
        err = ddTDA18273Write(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset3:
//
// DESCRIPTION: Get the RFCAL_Offset3 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset3
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
        // read byte 0x27
        err = ddTDA18273Read(pObj, 0x27, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx27.bF.RFCAL_Offset_Cprog3;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset4:
//
// DESCRIPTION: Set the RFCAL_Offset4 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset4
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
        pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog4 = uValue;

        // read byte 0x28
        err = ddTDA18273Write(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset4:
//
// DESCRIPTION: Get the RFCAL_Offset4 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset4
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
        // read byte 0x28
        err = ddTDA18273Read(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog4;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset5:
//
// DESCRIPTION: Set the RFCAL_Offset5 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8           uValue   //  I: Item value
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
        pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog5 = uValue;

        // read byte 0x28
        err = ddTDA18273Write(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset5:
//
// DESCRIPTION: Get the RFCAL_Offset5 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset5
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
        // read byte 0x28
        err = ddTDA18273Read(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog5;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset6:
//
// DESCRIPTION: Set the RFCAL_Offset6 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset6
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
        pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog6 = uValue;

        // read byte 0x28
        err = ddTDA18273Write(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset6:
//
// DESCRIPTION: Get the RFCAL_Offset6 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset6
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
        // read byte 0x28
        err = ddTDA18273Read(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog6;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset7:
//
// DESCRIPTION: Set the RFCAL_Offset7 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset7
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
        pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog7 = uValue;

        // read byte 0x28
        err = ddTDA18273Write(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset7:
//
// DESCRIPTION: Get the RFCAL_Offset7 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset7
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
        // read byte 0x28
        err = ddTDA18273Read(pObj, 0x28, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx28.bF.RFCAL_Offset_Cprog7;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset8:
//
// DESCRIPTION: Set the RFCAL_Offset8 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset8
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
        pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog8 = uValue;

        // read byte 0x29
        err = ddTDA18273Write(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset8:
//
// DESCRIPTION: Get the RFCAL_Offset8 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset8
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
        // read byte 0x29
        err = ddTDA18273Read(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog8;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset9:
//
// DESCRIPTION: Set the RFCAL_Offset9 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset9
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
        pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog9 = uValue;

        // read byte 0x29
        err = ddTDA18273Write(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset9:
//
// DESCRIPTION: Get the RFCAL_Offset9 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset9
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
        // read byte 0x29
        err = ddTDA18273Read(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog9;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset10:
//
// DESCRIPTION: Set the RFCAL_Offset10 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset10
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
        pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog10 = uValue;

        // read byte 0x29
        err = ddTDA18273Write(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset10:
//
// DESCRIPTION: Get the é0 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset10
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
        // read byte 0x29
        err = ddTDA18273Read(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog10;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRFCAL_Offset11:
//
// DESCRIPTION: Set the RFCAL_Offset11 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273SetRFCAL_Offset11
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
        pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog11 = uValue;

        // read byte 0x29
        err = ddTDA18273Write(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFCAL_Offset11:
//
// DESCRIPTION: Get the RFCAL_Offset11 bit(s) status
//
// RETURN:      TM_OK if no error
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273GetRFCAL_Offset11
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
        // read byte 0x29
        err = ddTDA18273Read(pObj, 0x29, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx29.bF.RFCAL_Offset_Cprog11;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetBandsplit_Filter_SubBand:
//
// DESCRIPTION: Set the Bandsplit_Filter_SubBand bit(s) status
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
tmddTDA18273SetBandsplit_Filter_SubBand
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
        pObj->I2CMap.uBx2A.bF.Bandsplit_Filter_SubBand = uValue;

        // read byte 0x2A
        err = ddTDA18273Write(pObj, 0x2A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetBandsplit_Filter_SubBand:
//
// DESCRIPTION: Get the Bandsplit_Filter_SubBand bit(s) status
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
tmddTDA18273GetBandsplit_Filter_SubBand
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
        // read byte 0x2A
        err = ddTDA18273Read(pObj, 0x2A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2A.bF.Bandsplit_Filter_SubBand;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetAGC2_loop_off:
//
// DESCRIPTION: Set the AGC2_loop_off bit(s) status
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
tmddTDA18273SetAGC2_loop_off
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
        pObj->I2CMap.uBx2B.bF.AGC2_loop_off = uValue;

        // read byte 0x2B
        err = ddTDA18273Write(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC2_loop_off:
//
// DESCRIPTION: Get the AGC2_loop_off bit(s) status
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
tmddTDA18273GetAGC2_loop_off
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
        // read byte 0x2B
        err = ddTDA18273Read(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2B.bF.AGC2_loop_off;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetForce_AGC2_gain:
//
// DESCRIPTION: Set the Force_AGC2_gain bit(s) status
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
tmddTDA18273SetForce_AGC2_gain
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
        pObj->I2CMap.uBx2B.bF.Force_AGC2_gain = uValue;

        // write byte 0x2B
        err = ddTDA18273Write(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetForce_AGC2_gain:
//
// DESCRIPTION: Get the Force_AGC2_gain bit(s) status
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
tmddTDA18273GetForce_AGC2_gain
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
        // read byte 0x2B
        err = ddTDA18273Read(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2B.bF.Force_AGC2_gain;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRF_Filter_Gv:
//
// DESCRIPTION: Set the RF_Filter_Gv bit(s) status
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
tmddTDA18273SetRF_Filter_Gv
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
        pObj->I2CMap.uBx2B.bF.RF_Filter_Gv = uValue;

        // read byte 0x2B
        err = ddTDA18273Write(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRF_Filter_Gv:
//
// DESCRIPTION: Get the RF_Filter_Gv bit(s) status
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
tmddTDA18273GetRF_Filter_Gv
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
        // read byte 0x2B
        err = ddTDA18273Read(pObj, 0x2B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2B.bF.RF_Filter_Gv;
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

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRF_BPF_Bypass:
//
// DESCRIPTION: Set the RF_BPF_Bypass bit(s) status
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
tmddTDA18273SetRF_BPF_Bypass
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
        pObj->I2CMap.uBx2E.bF.RF_BPF_Bypass = uValue;

        // read byte 0x2E
        err = ddTDA18273Write(pObj, 0x2E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRF_BPF_Bypass:
//
// DESCRIPTION: Get the RF_BPF_Bypass bit(s) status
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
tmddTDA18273GetRF_BPF_Bypass
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
        // read byte 0x2E
        err = ddTDA18273Read(pObj, 0x2E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2E.bF.RF_BPF_Bypass;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRF_BPF:
//
// DESCRIPTION: Set the RF_BPF bit(s) status
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
tmddTDA18273SetRF_BPF
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
        pObj->I2CMap.uBx2E.bF.RF_BPF = uValue;

        // read byte 0x2E
        err = ddTDA18273Write(pObj, 0x2E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRF_BPF:
//
// DESCRIPTION: Get the RF_BPF bit(s) status
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
tmddTDA18273GetRF_BPF
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
        // read byte 0x2E
        err = ddTDA18273Read(pObj, 0x2E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx2E.bF.RF_BPF;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273SetLO_CP_Current                                  */
/*                                                                            */
/* DESCRIPTION: Set the LO_CP_Current bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273SetLO_CP_Current
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
        pObj->I2CMap.uBx2F.bF.LO_CP_Current = uValue;

        /* Read byte 0x2F */
        err = ddTDA18273Write(pObj, 0x2F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmddTDA18273GetLO_CP_Current                                  */
/*                                                                            */
/* DESCRIPTION: Get the LO_CP_Current bit(s) status                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmddTDA18273GetLO_CP_Current
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
            *puValue = pObj->I2CMap.uBx2F.bF.LO_CP_Current;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetUp_AGC5:
//
// DESCRIPTION: Get the Up_AGC5 bit(s) status
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
tmddTDA18273GetUp_AGC5
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
        // read byte 0x30
        err = ddTDA18273Read(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx30.bF.Up_AGC5;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetDo_AGC5:
//
// DESCRIPTION: Get the Do_AGC5 bit(s) status
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
tmddTDA18273GetDo_AGC5
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
        // read byte 0x30
        err = ddTDA18273Read(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx30.bF.Do_AGC5;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetUp_AGC4:
//
// DESCRIPTION: Get the Up_AGC4 bit(s) status
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
tmddTDA18273GetUp_AGC4
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
        // read byte 0x30
        err = ddTDA18273Read(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx30.bF.Up_AGC4;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetDo_AGC4:
//
// DESCRIPTION: Get the Do_AGC4 bit(s) status
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
tmddTDA18273GetDo_AGC4
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
        // read byte 0x30
        err = ddTDA18273Read(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx30.bF.Do_AGC4;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetUp_AGC2:
//
// DESCRIPTION: Get the Up_AGC2 bit(s) status
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
tmddTDA18273GetUp_AGC2
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
        // read byte 0x30
        err = ddTDA18273Read(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx30.bF.Up_AGC2;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetDo_AGC2:
//
// DESCRIPTION: Get the Do_AGC2 bit(s) status
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
tmddTDA18273GetDo_AGC2
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
        // read byte 0x30
        err = ddTDA18273Read(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx30.bF.Do_AGC2;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetUp_AGC1:
//
// DESCRIPTION: Get the Up_AGC1 bit(s) status
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
tmddTDA18273GetUp_AGC1
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
        // read byte 0x30
        err = ddTDA18273Read(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx30.bF.Up_AGC1;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetDo_AGC1:
//
// DESCRIPTION: Get the Do_AGC1 bit(s) status
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
tmddTDA18273GetDo_AGC1
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
        // read byte 0x30
        err = ddTDA18273Read(pObj, 0x30, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx30.bF.Do_AGC1;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC2_Gain_Read:
//
// DESCRIPTION: Get the AGC2_Gain_Read bit(s) status
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
tmddTDA18273GetAGC2_Gain_Read
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
        // read byte 0x31
        err = ddTDA18273Read(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.AGC2_Gain_Read;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC1_Gain_Read:
//
// DESCRIPTION: Get the AGC1_Gain_Read bit(s) status
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
tmddTDA18273GetAGC1_Gain_Read
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
        // read byte 0x31
        err = ddTDA18273Read(pObj, 0x31, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx31.bF.AGC1_Gain_Read;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC2_Gain_Read:
//
// DESCRIPTION: Get the AGC2_Gain_Read bit(s) status
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
tmddTDA18273GetAGC1_2_4_5_Gain_Read
(
 tmUnitSelect_t  tUnit,       //  I: Unit number
 UInt8*          puAGC1Value, //  O: Address of the variable to output item value
 UInt8*          puAGC2Value, //  O: Address of the variable to output item value
 UInt8*          puAGC4Value, //  O: Address of the variable to output item value
 UInt8*          puAGC5Value  //  O: Address of the variable to output item value
)
{
    ptmddTDA18273Object_t   pObj = Null;
    tmErrorCode_t           err  = TM_OK;

    // test the parameter
    if ((puAGC1Value == Null) || (puAGC2Value == Null) || (puAGC4Value == Null) || (puAGC5Value == Null))
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
        // read byte 0x31-0x35
        err = ddTDA18273Read(pObj, 0x31, 5);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puAGC1Value = pObj->I2CMap.uBx31.bF.AGC1_Gain_Read;
            *puAGC2Value = pObj->I2CMap.uBx31.bF.AGC2_Gain_Read;
            *puAGC4Value = pObj->I2CMap.uBx35.bF.AGC4_Gain_Read;
            *puAGC5Value = pObj->I2CMap.uBx35.bF.AGC5_Gain_Read;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetCprog_Read:
//
// DESCRIPTION: Get the Cprog_Read bit(s) status
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
tmddTDA18273GetCprog_Read
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
        // read byte 0x33
        err = ddTDA18273Read(pObj, 0x33, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx32.Cprog_Read;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetDo_AGC1bis:
//
// DESCRIPTION: Get the Do_AGC1bis bit(s) status
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
tmddTDA18273GetDo_AGC1bis
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
        // read byte 0x33
        err = ddTDA18273Read(pObj, 0x33, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx33.bF.Do_AGC1bis;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC1_Top_Adapt_Low:
//
// DESCRIPTION: Get the AGC1_Top_Adapt_Low bit(s) status
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
tmddTDA18273GetAGC1_Top_Adapt_Low
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
        // read byte 0x33
        err = ddTDA18273Read(pObj, 0x33, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx33.bF.AGC1_Top_Adapt_Low;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetUp_LNA_Adapt:
//
// DESCRIPTION: Get the Up_LNA_Adapt bit(s) status
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
tmddTDA18273GetUp_LNA_Adapt
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
        // read byte 0x33
        err = ddTDA18273Read(pObj, 0x33, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx33.bF.Up_LNA_Adapt;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetDo_LNA_Adapt:
//
// DESCRIPTION: Get the Do_LNA_Adapt bit(s) status
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
tmddTDA18273GetDo_LNA_Adapt
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
        // read byte 0x33
        err = ddTDA18273Read(pObj, 0x33, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx33.bF.Do_LNA_Adapt;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetTOP_AGC3_Read:
//
// DESCRIPTION: Get the TOP_AGC3_Read bit(s) status
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
tmddTDA18273GetTOP_AGC3_Read
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
        // read byte 0x33
        err = ddTDA18273Read(pObj, 0x33, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx33.bF.TOP_AGC3_Read;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRFAGC_Read_K:
//
// DESCRIPTION: Get the tmddTDA18273GetRFAGC_Read_K bit(s) status
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
tmddTDA18273GetRFAGC_Read_K
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt16*         puValue //  I: Address of the variable to output item value
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
        // read byte 0x33-0x34
        err = ddTDA18273Read(pObj, 0x33, 2);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = 0;
            *puValue = ((pObj->I2CMap.uBx33.bF.RFAGC_Read_K_8 << 8)| (pObj->I2CMap.uBx34.RFAGC_Read_K));
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC5_Gain_Read:
//
// DESCRIPTION: Get the AGC5_Gain_Read bit(s) status
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
tmddTDA18273GetAGC5_Gain_Read
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
        // read byte 0x35
        err = ddTDA18273Read(pObj, 0x35, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx35.bF.AGC5_Gain_Read;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetAGC4_Gain_Read:
//
// DESCRIPTION: Get the AGC4_Gain_Read bit(s) status
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
tmddTDA18273GetAGC4_Gain_Read
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
        // read byte 0x35
        err = ddTDA18273Read(pObj, 0x35, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx35.bF.AGC4_Gain_Read;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRSSI:
//
// DESCRIPTION: Get the RSSI bit(s) status
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
tmddTDA18273GetRSSI
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
        // read byte 0x36
        err = ddTDA18273Read(pObj, 0x36, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx36.RSSI;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRSSI_AV:
//
// DESCRIPTION: Set the RSSI_AV bit(s) status
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
tmddTDA18273SetRSSI_AV
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
        pObj->I2CMap.uBx37.bF.RSSI_AV = uValue;

        // write byte 0x37
        err = ddTDA18273Write(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRSSI_AV:
//
// DESCRIPTION: Get the RSSI_AV bit(s) status
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
tmddTDA18273GetRSSI_AV
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
        // read byte 0x37
        err = ddTDA18273Read(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx37.bF.RSSI_AV;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRSSI_Cap_Reset_En:
//
// DESCRIPTION: Set the RSSI_Cap_Reset_En bit(s) status
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
tmddTDA18273SetRSSI_Cap_Reset_En
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
        pObj->I2CMap.uBx37.bF.RSSI_Cap_Reset_En = uValue;

        // write byte 0x37
        err = ddTDA18273Write(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRSSI_Cap_Reset_En:
//
// DESCRIPTION: Get the RSSI_Cap_Reset_En bit(s) status
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
tmddTDA18273GetRSSI_Cap_Reset_En
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
        // read byte 0x37
        err = ddTDA18273Read(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx37.bF.RSSI_Cap_Reset_En;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRSSI_Cap_Val:
//
// DESCRIPTION: Set the RSSI_Cap_Val bit(s) status
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
tmddTDA18273SetRSSI_Cap_Val
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
        pObj->I2CMap.uBx37.bF.RSSI_Cap_Val = uValue;

        // write byte 0x37
        err = ddTDA18273Write(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRSSI_Cap_Val:
//
// DESCRIPTION: Get the RSSI_Cap_Val bit(s) status
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
tmddTDA18273GetRSSI_Cap_Val
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
        // read byte 0x37
        err = ddTDA18273Read(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx37.bF.RSSI_Cap_Val;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetRSSI_Dicho_not:
//
// DESCRIPTION: Set the RSSI_Dicho_not bit(s) status
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
tmddTDA18273SetRSSI_Dicho_not
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
        pObj->I2CMap.uBx37.bF.RSSI_Dicho_not = uValue;

        // write byte 0x37
        err = ddTDA18273Write(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetRSSI_Dicho_not:
//
// DESCRIPTION: Get the RSSI_Dicho_not bit(s) status
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
tmddTDA18273GetRSSI_Dicho_not
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
        // read byte 0x37
        err = ddTDA18273Read(pObj, 0x37, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx37.bF.RSSI_Dicho_not;
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

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetDDS_Polarity:
//
// DESCRIPTION: Set the DDS_Polarity bit(s) status
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
tmddTDA18273SetDDS_Polarity
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
        pObj->I2CMap.uBx38.bF.DDS_Polarity = uValue;

        // write byte 0x38
        err = ddTDA18273Write(pObj, 0x38, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetDDS_Polarity:
//
// DESCRIPTION: Get the DDS_Polarity bit(s) status
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
tmddTDA18273GetDDS_Polarity
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
            *puValue = pObj->I2CMap.uBx38.bF.DDS_Polarity;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIRQ_Mode:
//
// DESCRIPTION: Set the IRQ_Mode bit(s) status
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
tmddTDA18273SetIRQ_Mode
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
        pObj->I2CMap.uBx38.bF.IRQ_Mode = uValue;

        // read byte 0x38
        err = ddTDA18273Write(pObj, 0x38, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIRQ_Mode:
//
// DESCRIPTION: Get the IRQ_Mode bit(s) status
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
tmddTDA18273GetIRQ_Mode
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
            *puValue = pObj->I2CMap.uBx38.bF.IRQ_Mode;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273SetIRQ_Polarity:
//
// DESCRIPTION: Set the IRQ_Polarity bit(s) status
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
tmddTDA18273SetIRQ_Polarity
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
        pObj->I2CMap.uBx38.bF.IRQ_Polarity = uValue;

        // read byte 0x38
        err = ddTDA18273Write(pObj, 0x38, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Write(0x%08X) failed.", tUnit));

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273GetIRQ_Polarity:
//
// DESCRIPTION: Get the IRQ_Polarity bit(s) status
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
tmddTDA18273GetIRQ_Polarity
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
            *puValue = pObj->I2CMap.uBx38.bF.IRQ_Polarity;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_0
//
// DESCRIPTION: Get the rfcal_log_0 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_0
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x39
        err = ddTDA18273Read(pObj, 0x39, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx39.bF.rfcal_log_0;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_1
//
// DESCRIPTION: Get the rfcal_log_1 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_1
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x3A
        err = ddTDA18273Read(pObj, 0x3A, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3A.bF.rfcal_log_1;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_2
//
// DESCRIPTION: Get the rfcal_log_2 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_2
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x3B
        err = ddTDA18273Read(pObj, 0x3B, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3B.bF.rfcal_log_2;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_3
//
// DESCRIPTION: Get the rfcal_log_3 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_3
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x3C
        err = ddTDA18273Read(pObj, 0x3C, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3C.bF.rfcal_log_3;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_4
//
// DESCRIPTION: Get the rfcal_log_4 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_4
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x3D
        err = ddTDA18273Read(pObj, 0x3D, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3D.bF.rfcal_log_4;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_5
//
// DESCRIPTION: Get the rfcal_log_5 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_5
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x3E
        err = ddTDA18273Read(pObj, 0x3E, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3E.bF.rfcal_log_5;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_6
//
// DESCRIPTION: Get the rfcal_log_6 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_6
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x3F
        err = ddTDA18273Read(pObj, 0x3F, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx3F.bF.rfcal_log_6;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_7
//
// DESCRIPTION: Get the rfcal_log_7 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_7
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x40
        err = ddTDA18273Read(pObj, 0x40, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx40.bF.rfcal_log_7;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_8
//
// DESCRIPTION: Get the rfcal_log_8 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_8
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x41
        err = ddTDA18273Read(pObj, 0x41, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx41.bF.rfcal_log_8;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_9
//
// DESCRIPTION: Get the rfcal_log_9 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_9
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x42
        err = ddTDA18273Read(pObj, 0x42, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx42.bF.rfcal_log_9;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_10
//
// DESCRIPTION: Get the rfcal_log_10 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_10
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x43
        err = ddTDA18273Read(pObj, 0x43, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx43.bF.rfcal_log_10;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

//-------------------------------------------------------------------------------------
// FUNCTION:    tmddTDA18273Getrfcal_log_11
//
// DESCRIPTION: Get the rfcal_log_11 bit(s) status
//
// RETURN:      ddTDA18273_ERR_BAD_UNIT_NUMBER
//        ddTDA18273_ERR_BAD_UNIT_NUMBER
//         ddTDA18273_ERR_NOT_INITIALIZED
//        tmdd_ERR_IIC_ERR
//         TM_OK 
//
// NOTES:       
//-------------------------------------------------------------------------------------
//
tmErrorCode_t
tmddTDA18273Getrfcal_log_11
(
 tmUnitSelect_t  tUnit,  //  I: Unit number
 UInt8*          puValue //  I: Address of the variable to output item value
 )
{
    ptmddTDA18273Object_t    pObj = Null;
    tmErrorCode_t                   err  = TM_OK;

    // test the parameter
    if (puValue == Null)
        err = ddTDA18273_ERR_BAD_UNIT_NUMBER;

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
        // read byte 0x44
        err = ddTDA18273Read(pObj, 0x44, 1);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "ddTDA18273Read(0x%08X) failed.", tUnit));

        if(err == TM_OK)
        {
            // get value
            *puValue = pObj->I2CMap.uBx44.bF.rfcal_log_11;
        }

        (void)ddTDA18273MutexRelease(pObj);
    }

    return err;
}

