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
/*******************************************************************************
 *
 * FILE NAME          : MaxLinearDataTypes.h
 *
 * AUTHOR             : Brenndon Lee
 *                      Dong Liu
 *
 * DATE CREATED       : Jul/31, 2006
 *                      Jan/23, 2010
 *
 * DESCRIPTION        : This file contains MaxLinear-defined data types.
 *                      Instead of using ANSI C data type directly in source code
 *                      All module should include this header file.
 *                      And conditional compilation switch is also declared
 *                      here.
 *
 *******************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MAXLINEAR_DATA_TYPES_H__
#define __MAXLINEAR_DATA_TYPES_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/

/******************************************************************************
    Macros
******************************************************************************/

#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif

#ifdef _ANSI_C_SOURCE
#define false                1
#define true                 0

#define TRUE                 1
#define FALSE                0
#endif
/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/
//typedef unsigned char        UINT8;
//typedef unsigned short       UINT16;
//typedef unsigned int         UINT32;
typedef unsigned long long   UINT64;
typedef char                 SINT8;
typedef short                SINT16;
typedef int                  SINT32;
typedef float                REAL32;
typedef double               REAL64;
typedef unsigned long        ULONG_32;

#ifdef _ANSI_C_SOURCE
typedef unsigned char        bool;
#endif


typedef enum
{
  MXL_TRUE = 0,
  MXL_FALSE = 1,
  MXL_SUCCESS = 0,
  MXL_FAILED,
  MXL_BUSY,
  MXL_NULL_PTR,
  MXL_INVALID_PARAMETER,
  MXL_NOT_INITIALIZED,
  MXL_ALREADY_INITIALIZED,
  MXL_BUFFER_TOO_SMALL,
  MXL_NOT_SUPPORTED,
  MXL_TIMEOUT
} MXL_STATUS;

typedef enum{
	MxL_OK					=   0x0,
	MxL_ERR_INIT			=   0x1,
	MxL_ERR_RFTUNE			=   0x2,
	MxL_ERR_SET_REG			=   0x3,
	MxL_ERR_GET_REG			=   0x4,
	MxL_ERR_MODE			=   0x10,
	MxL_ERR_IF_FREQ			=   0x11,
	MxL_ERR_XTAL_FREQ		=   0x12,
	MxL_ERR_BANDWIDTH		=   0x13,
	MxL_GET_ID_FAIL			=   0x14,
	MxL_ERR_DEMOD_LOCK		=  0x20,
	MxL_NOREADY_DEMOD_LOCK		=  0x21,
	MxL_ERR_OTHERS			=   0x0A
}MxL_ERR_MSG;

typedef enum
{
  MXL_DISABLE = 0,
  MXL_ENABLE,

  MXL_UNLOCKED = 0,
  MXL_LOCKED,

  MXL_INVALID = 0,
  MXL_VALID,

  MXL_PORT_LOW = 0,
  MXL_PORT_HIGH,

  MXL_START = 0,
  MXL_FINISH,

  MXL_ABORT_TUNE = 0,
  MXL_START_TUNE,

  MXL_FINE_TUNE_STEP_DOWN = 0,
  MXL_FINE_TUNE_STEP_UP

} MXL_BOOL;

typedef enum
{
  IFX_SUCCESS = 0,
  IFX_FAILED,
  IFX_BUSY,
  IFX_NULL_PTR,
  IFX_INVALID_PARAMETER,
  IFX_BUFFER_TOO_SMALL,
  IFX_TIMEOUT
} IFX_STATUS;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/

/******************************************************************************
    Prototypes
******************************************************************************/

#endif /* __MAXLINEAR_DATA_TYPES_H__ */

