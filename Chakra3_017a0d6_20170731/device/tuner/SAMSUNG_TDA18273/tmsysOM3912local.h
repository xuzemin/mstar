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
* \file          tmsysOM3912local.h
*                %version: CFR_FEAP#4 %
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


#ifndef TMSYSOM3912LOCAL_H
#define TMSYSOM3912LOCAL_H

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/


#ifdef __cplusplus
extern "C" {
#endif


    /*============================================================================*/
    /*                       MACRO DEFINITION                                     */
    /*============================================================================*/

#define OM3912_SYS_COMP_NUM         2
#define OM3912_SYS_MAJOR_VER        0
#define OM3912_SYS_MINOR_VER        0

#define OM3912_MUTEX_TIMEOUT       TMBSL_FRONTEND_MUTEX_TIMEOUT_INFINITE

#define POBJ_SRVFUNC_SIO pObj->sRWFunc
#define POBJ_SRVFUNC_STIME pObj->sTime
//#define P_DBGPRINTEx tmsysOM3912Print
//#define P_DBGPRINTVALID (True)

/*-------------*/
/* ERROR CODES */
/*-------------*/

/*---------*/
/* CHANNEL */
/*---------*/

#define OM3912_MAX_UNITS 2

/*-----------------------------------------------*/
/*  DEFAULT VALUES FOR CONFIGURATION MANAGEMENT  */
/*-----------------------------------------------*/

/*---------*/
/*  INDEX  */
/*---------*/


/*------------------*/
/*special config    */
/*------------------*/

/*------------------*/
/*  DEFAULT VALUES  */
/*------------------*/

/*----------------*/
/*  DEFINE MASKS  */
/*----------------*/


/*---------------*/
/*  DEFINE BITS  */
/*---------------*/
/*Special Config*/

/*============================================================================*/
/*                       ENUM OR TYPE DEFINITION                              */
/*============================================================================*/

typedef struct _tmOM3912Object_t
{
    tmUnitSelect_t              tUnit;
    tmUnitSelect_t              tUnitW;
    tmUnitSelect_t              tUnitTDA18273;
    ptmbslFrontEndMutexHandle   pMutex;
    Bool                        init;
    tmbslFrontEndIoFunc_t       sRWFunc;
    tmbslFrontEndTimeFunc_t     sTime;
    tmbslFrontEndDebugFunc_t    sDebug;
    tmbslFrontEndMutexFunc_t    sMutex;
    tmPowerState_t              powerState;
    Bool                        resetDone;
    UInt32                      uHwAddress[tmOM3912UnitDeviceTypeMax];
    tmTuneReqType_t             lastTuneReqType;
} tmOM3912Object_t, *ptmOM3912Object_t,**pptmOM3912Object_t;



/*============================================================================*/
/*                       EXTERN DATA DEFINITION                               */
/*============================================================================*/

/*============================================================================*/
/*                       EXTERN FUNCTION PROTOTYPES                           */
/*============================================================================*/

extern tmErrorCode_t OM3912MutexAcquire(ptmOM3912Object_t   pObj, UInt32 timeOut);
extern tmErrorCode_t OM3912MutexRelease(ptmOM3912Object_t   pObj);

#ifdef __cplusplus
}
#endif

#endif /* TMSYSOM3912LOCAL_H */
/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/

