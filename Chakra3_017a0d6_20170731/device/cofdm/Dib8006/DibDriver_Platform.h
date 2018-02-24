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
#ifndef DIBDRIVER_PLATFORM_H
#define DIBDRIVER_PLATFORM_H

/*#include "stdlib.h"
#include "stdio.h>"
#include "pthread.h"
#include "unistd.h"
#include "string.h"
#include "strings.h"
#include "stdint.h"
#include "endian.h"*/

//#include "Datatype.h"
//#include "MsOS.h"

#include "Utl.h"
#include "msAPI_Timer.h"
#include "MsTypes.h"
#include "MsCommon.h"
#include "MsOS.h"
#ifdef __cplusplus
extern "C" {
#endif

#include"datatype.h"

//#define NULL 0
/*#define uint8_t   unsigned char
#define uint16_t  unsigned short
#define uint32_t  unsigned long
#define int8_t   signed char
#define int16_t  signed short
#define int32_t  signed long*/

#define uint8_t   U8
#define uint16_t  U16
#define uint32_t 	U32
#define int8_t   S8
#define int16_t  S16
#define int32_t  S32


extern MS_S32 MsOS_CreateSemaphore (MS_U32 u32InitCnt,
                             MsOSAttribute eAttribute,
                             char *pName);

extern MS_BOOL MsOS_DeleteSemaphore (MS_S32 s32SemaphoreId);

extern MS_BOOL MsOS_ObtainSemaphore (MS_S32 s32SemaphoreId, MS_U32 u32WaitMs);

extern MS_BOOL MsOS_ReleaseSemaphore (MS_S32 s32SemaphoreId);

#define MemAlloc(size)	 msAPI_Memory_Allocate((uint16_t) size, (EN_BUFFER_ID)0)
#define	MemFree( chunk, size )	msAPI_Memory_Free((void *)chunk, (EN_BUFFER_ID)0)

#ifndef DibMemAlloc
#define DibMemAlloc MemAlloc
#define DibMemFree  MemFree
#define DibSetMemory memset
#endif

#define DibMoveMemory memmove
#define DibZeroMemory(a, n) memset(a, 0, n)
// Sleep

#if 1
#define DibMSleep(v) msAPI_Timer_Delayms(v)
#define DibUSleep(v) msAPI_Timer_Delayms(((v+1000)/1000))
#else

extern void busy_wait(uint32_t usec);
#define DibMSleep(v) busy_wait(v*1000)
#define DibUSleep(v) busy_wait(v)
#endif



#define DIB_LOCK int32_t//pthread_mutex_t£¬  ethans change

#define DibInitLock(lock)   MsOS_CreateSemaphore (0,E_MSOS_FIFO,(char *)lock)
#define DibFreeLock(lock)    MsOS_DeleteSemaphore(lock)
#define DibAcquireLock(lock) MsOS_ObtainSemaphore(lock,3000)
#define DibReleaseLock(lock)  MsOS_ReleaseSemaphore(lock) //pthread_mutex_unlock(lock)
#define DibAllocateLock(lock)
#define DibDeAllocateLock(lock)

//extern uint32_t systime(void);
#define systime msAPI_Timer_GetTime0

#define CONFIG_DEBUG

#ifndef CONFIG_DEBUG
 #define DEBUG_FUNCTIONS_PROTOTYPED_BY_PLATFORM
#define debug_printf printf
#define debug_printf_line platform_debug_printf_line
 //#define DEBUG_OBJECT(name, type, text)
// #define DEBUG_OBJECT_STATIC(name, type, text)
#endif

#define debug_printf printf
#define debug_printf_line


#define NO_SHARED_TUNER

#define CONFIG_DEBUG
#define CONFIG_BUILD_HOST
#define DIBCOM_EXTENDED_MONITORING
#define DIBCOM_GENERIC_MONITORING

#define CONFIG_STANDARD_DVBT
//#define CONFIG_STANDARD_DAB
#define CONFIG_STANDARD_ISDBT
#define CONFIG_STANDARD_ANALOG

#define CONFIG_BAND_VHF
#define CONFIG_BAND_CBAND
#define CONFIG_BAND_UHF
#define CONFIG_BAND_LBAND
#define CONFIG_BAND_SBAND

//#define CONFIG_NO_TUNE_ASYNC

//set the output mode (parallel gated (OUTPUT_MODE_TS_PARALLEL_GATED),
//parallel cont (OUTPUT_MODE_TS_PARALLEL_CONT), serial (OUTPUT_MODE_TS_SERIAL) or off (OUTPUT_MODE_OFF))
//the different values are defined in driver/include/adapter/common.h
#define CONFIG_OUTPUT_MODE OUTMODE_MPEG2_PAR_GATED_CLK

#define CONFIG_DEMOD_I2C_CHUNK_SIZE 125

#define CONFIG_DIB0090_USE_PWM_AGC

#define CONFIG_FIRMWARE_PATH ""

#ifdef __cplusplus
}
#endif

#endif

