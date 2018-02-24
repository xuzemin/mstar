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
 * \file          tmsysOM3912.h
 *                %version: 1 %
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


#ifndef TMSYSOM3912_H
#define TMSYSOM3912_H

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/

/*============================================================================*/
/*                       MACRO DEFINITION                                     */
/*============================================================================*/

/* SW Error codes */
#define OM3912_ERR_BASE               (CID_COMP_TUNER | CID_LAYER_DEVLIB)
#define OM3912_ERR_COMP               (CID_COMP_TUNER | CID_LAYER_DEVLIB | TM_ERR_COMP_UNIQUE_START)

#define OM3912_ERR_BAD_UNIT_NUMBER    (OM3912_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define OM3912_ERR_NOT_INITIALIZED    (OM3912_ERR_BASE + TM_ERR_NOT_INITIALIZED)
//#define OM3912_ERR_INIT_FAILED        (OM3912_ERR_BASE + TM_ERR_INIT_FAILED)
#define OM3912_ERR_BAD_PARAMETER      (OM3912_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define OM3912_ERR_NOT_SUPPORTED      (OM3912_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define OM3912_ERR_HW                 (OM3912_ERR_COMP + 0x0001)
//#define OM3912_ERR_NOT_READY          (OM3912_ERR_COMP + 0x0002)
//#define OM3912_ERR_BAD_CRC            (OM3912_ERR_COMP + 0x0003)
//#define OM3912_ERR_BAD_VERSION        (OM3912_ERR_COMP + 0x0004)

/*============================================================================*/
/*                       ENUM OR TYPE DEFINITION                              */
/*============================================================================*/

    /* OM3912 Device Types */
    typedef enum _tmOM3912UnitDeviceType_t
    {
        tmOM3912UnitDeviceTypeUnknown = 0,
        /** TDA18211 Tuner */
        tmOM3912UnitDeviceTypeTDA18273,
        tmOM3912UnitDeviceTypeMax
    } tmOM3912UnitDeviceType_t, *ptmOM3912UnitDeviceType_t;

/*============================================================================*/
/*                       EXTERN DATA DEFINITION                               */
/*============================================================================*/



/*============================================================================*/
/*                       EXTERN FUNCTION PROTOTYPES                           */
/*============================================================================*/


extern tmErrorCode_t
tmsysOM3912GetSWVersion
(
    ptmsysSWVersion_t   pSWVersion  /* O: Receives SW Version  */
);

extern tmErrorCode_t
tmsysOM3912Init
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
);

extern tmErrorCode_t
tmsysOM3912DeInit
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
);

extern tmErrorCode_t
tmsysOM3912Reset
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
);

extern tmErrorCode_t
tmsysOM3912SetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    tmPowerState_t  ePowerState /* I: Power state of the device */
);

extern tmErrorCode_t
tmsysOM3912GetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    ptmPowerState_t pPowerState /* O: Power state of the device */
);

extern tmErrorCode_t
tmsysOM3912SendRequest
(
    tmUnitSelect_t  tUnit,              /* I: FrontEnd unit number */
    pVoid           pTuneRequest,       /* I/O: Tune Request Structure pointer */
    UInt32          dwTuneRequestSize,  /* I: Tune Request Structure size */
    tmTuneReqType_t tTuneReqType        /* I: Tune Request Type */
);

extern tmErrorCode_t
tmsysOM3912SetI2CSwitchState
(
    tmUnitSelect_t                  tUnit,  /* I: FrontEnd unit number */
    tmsysFrontEndI2CSwitchState_t   eState  /* I: I2C switch state */
);

extern tmErrorCode_t
tmsysOM3912GetI2CSwitchState
(
    tmUnitSelect_t                  tUnit,
    tmsysFrontEndI2CSwitchState_t*  peState,
    UInt32*                         puI2CSwitchCounter
);

extern tmErrorCode_t
tmsysOM3912GetLockStatus
(
    tmUnitSelect_t          tUnit,      /* I: FrontEnd unit number */
    tmsysFrontEndState_t*   pLockStatus /* O: Lock status */
);

extern tmErrorCode_t
tmsysOM3912GetSignalStrength
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    UInt32          *pStrength  /* I/O: Signal Strength pointer */
);

extern tmErrorCode_t
tmsysOM3912GetSignalQuality
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    UInt32          *pQuality   /* I/O: Signal Quality pointer */
);

extern tmErrorCode_t
tmsysOM3912GetDeviceUnit
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3912UnitDeviceType_t    deviceType, /* I: Device Type  */
    ptmUnitSelect_t             ptUnit      /* O: Device unit number */
);

extern tmErrorCode_t
tmsysOM3912SetHwAddress
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3912UnitDeviceType_t    deviceType, /* I: Device Type  */
    UInt32                      uHwAddress  /* I: Hardware Address */
);

extern tmErrorCode_t
tmsysOM3912GetHwAddress
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3912UnitDeviceType_t deviceType, /* I: Device Type  */
    UInt32*                     puHwAddress /* O: Hardware Address */
);

extern tmErrorCode_t tmsysOM3912I2CRead(tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr, UInt32 ReadLen, UInt8* pData);

extern tmErrorCode_t tmsysOM3912I2CWrite(tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr, UInt32 WriteLen, UInt8* pData);

extern tmErrorCode_t tmsysOM3912Wait(tmUnitSelect_t tUnit, UInt32 tms);

extern tmErrorCode_t tmsysOM3912Print(UInt32 level, const char* format, ...);

extern tmErrorCode_t  tmsysOM3912Init ( tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */);


#ifdef __cplusplus
}
#endif

#endif /* TMSYSOM3912_H */
/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/

