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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPP_DVD_H
#define _MAPP_DVD_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//-------------------------------------------------------------------------------------------------
// Standard include files:
//-------------------------------------------------------------------------------------------------

#ifdef MAPP_DVD_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#ifdef DVDLIB_COMPILE
#else
#if (!FILE_SYSTEM_LONGLONG_API_ENABLE)
#error "FILE_SYSTEM_LONGLONG_API_ENABLE must be enabled for DVD ISO"
#endif
#endif

//-------------------------------------------------------------------------------------------------
// Project include files:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------

#define DVD_SETUP_TYPE_FILENAME             0
#define DVD_SETUP_TYPE_SHAREMEMADDR         1
#define DVD_SETUP_TYPE_BITSTREAMBUFADDR     2
#define DVD_SETUP_TYPE_BITSTREAMBUFLEN      3

typedef enum
{
    DVD_CALLBACK_TYPE_MB,
    DVD_CALLBACK_TYPE_WAIT,
    DVD_CALLBACK_TYPE_MISC,
} EN_DVD_CALLBACK_TYPE;

typedef enum
{
    DVD_CALLBACK_SUBTYPE_MB_PLAY,
    DVD_CALLBACK_SUBTYPE_MB_SEEKPLAY,
    DVD_CALLBACK_SUBTYPE_MB_WAITDONE,
    DVD_CALLBACK_SUBTYPE_MB_SCANSYNC,
    DVD_CALLBACK_SUBTYPE_MB_SCANEXIT,
} EN_DVD_CALLBACK_SUBTYPE_MB;

typedef enum
{
    DVD_CALLBACK_SUBTYPE_WAIT_WAITDONE,
    DVD_CALLBACK_SUBTYPE_WAIT_SCANDONE,
} EN_DVD_CALLBACK_SUBTYPE_WAIT;

typedef enum
{
    DVD_CALLBACK_SUBTYPE_MISC_DVDSTOP,
    DVD_CALLBACK_SUBTYPE_MISC_CURRENTTIME,
    DVD_CALLBACK_SUBTYPE_MISC_NOTIFY,
} EN_DVD_CALLBACK_SUBTYPE_MISC;

// Generic callback prototype
typedef int (*callback) (int, int, int *, int *);

#ifndef DVDLIB_COMPILE
// IO callback prototype
typedef int (*io_open) (const char *, int);
typedef int (*io_close) (int);
#if FILE_SYSTEM_LONGLONG_API_ENABLE
typedef LongLong (*io_seek) (int, LongLong, int);
#else
typedef int (*io_seek) (int, int, int);
#endif
typedef int (*io_read) (int, void *, int);
#if FILE_SYSTEM_LONGLONG_API_ENABLE
typedef LongLong (*io_size) (int);
#else
typedef int (*io_size) (int);
#endif

// Memory callback prototype
typedef void *(*mem_malloc) (int);
typedef void (*mem_free) (void *);
typedef void *(*mem_realloc) (void *, int);

INTERFACE void MApp_DVD_Setup(int type, void *ptr);
INTERFACE void MApp_DVD_Setup_Callback(callback func);
INTERFACE void MApp_DVD_Setup_IO_Callback(io_open open, io_close close, io_seek seek, io_read read, io_size size);
INTERFACE void MApp_DVD_Setup_Mem_Callback(mem_malloc malloc, mem_realloc realloc, mem_free free);

INTERFACE BOOLEAN MApp_DVD_Open(void);
INTERFACE void MApp_DVD_Close(void);
INTERFACE void MApp_DVD_Task(void);
INTERFACE U8 MApp_DVD_Command(enumMPlayerDVDCmdType cmd);
INTERFACE BOOLEAN MApp_DVD_IsAllowed(enumMPlayerDVDCmdType cmd);
INTERFACE void MApp_DVD_SetPlayPosition(U32 timeInMs);
INTERFACE void MApp_DVD_SetTrickMode(EN_PLAY_MODE enPlayMode, EN_PLAY_SPEED enPlaySpeed);
INTERFACE void MApp_DVD_SetRepeatAB(EN_SET_REPEATAB enAction);
INTERFACE void MApp_DVD_Resume(void);

INTERFACE void MApp_DVD_SetValue(int type, int value);
INTERFACE BOOLEAN MApp_DVD_IsPredecodeDone(void);
#endif

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
///-------------------------------------------------------------------------------------------------

#undef INTERFACE

#endif // _MAPP_DVD_H

