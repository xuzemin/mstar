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


#ifndef __MSAPI_MLE_COMMON_DEF_H__
#define __MSAPI_MLE_COMMON_DEF_H__

/*=============================================================*/
// header files
/*=============================================================*/
#include "stdlib.h"
#include "string.h"
#include "wchar.h"

#include "msAPI_MLE_retcode.h"

#include "datatype.h"
///#include "msAPI_Memory.h"

/*=============================================================*/
// Variable
/*=============================================================*/

/*=============================================================*/
// types and macros
/*=============================================================*/

/*
 * __SLDPM_FREE__ is used to mark important functions/data so that
 * the compiler would give them a special attribute call .sldpm_free.
 * These function/data are free from DPM (Demand Paging Module)
 * and will not be compressed in the flash.
 * If a function/data is frequently called, then it is better to give
 * it this attribute to speed up the run time performance.
 *
 * Other compiler options are used to group highly related code together
 * to reduce the number page faults.
 *
 * See also:
 *   sc/customer/product/cust/scatter/scatter_8532_64_32_bt_acrux2.dsc
 *   sc/customer/product/cust/scatter/scatter_85xx_emmi_sldpm.dsc
 */
//#if defined(__TARGET__) && defined(__arm)
#if 0
#define __SLDPM_FREE__  __attribute__((section(".sldpm_free")))
#else
#define __SLDPM_FREE__
#endif

#if defined(__GNUC__)// && defined(_WIN32)
// omits stand alone copies of inline functions when we are using gcc to build
// non-target applications with MLE/MMI header files
#define __INLINE static __inline
#define MLE_INLINE static __inline
#else
#define __INLINE __inline
#define MLE_INLINE __inline
#endif // __GNUC__ && _WIN32

typedef U32 MLE_Ret; ///< type for MLE return values
typedef U16 MLE_WChar; ///< type for MLE defined wide characters

/// type aliases
typedef MLE_Ret MLERet_t;

/*
 * Replace FREEIF macro with a function for reducing code size
 *
 * #define FREEIF(p) if (p != 0) {FREE((void*)p); p = 0;}
 */
void msAPI_MLE_freeif(void **);
#define FREEIF(p) msAPI_MLE_freeif((void **) &(p));
//#define BREAKIF(a) if (a != MLE_RET_SUCCESS) break


#undef ASSERT

#ifdef __UNIT_TEST_APP__
#define ASSERT(_e_) if(_e_){}      // to prevent lint warning because _e_ is set but not used
#else
#define ASSERT(_e_) if(_e_){}      // to prevent lint warning because _e_ is set but not used
#endif

extern void* ttfmalloc(size_t bytes);
extern void ttffree(void* mem);
extern void* ttfrealloc(void* oldmem, size_t bytes);
extern void* ttfcalloc(size_t n_elements, size_t elem_size);

extern void* hashmalloc(size_t bytes);
extern void hashfree(void* mem);
extern void* hashrealloc(void* oldmem, size_t bytes);
extern void* hashcalloc(size_t n_elements, size_t elem_size);

///#define MALLOC(size) msAPI_Memory_Allocate(size, BUF_ID_GLYPH_DISP_INFO)        ///MLE_Malloc(size)
#define MALLOC(size) ttfmalloc(size)                                                                        ///MLE_Malloc(size)
///#define REALLOC(ptr, size) msAPI_Memory_ReAllocate(ptr, size, BUF_ID_GLYPH_DISP_INFO)   ///MLE_Realloc(ptr, size)
#define REALLOC(ptr, size) ttfrealloc(ptr, size)                                                         ///MLE_Realloc(ptr, size)
///#define FREE(a) msAPI_Memory_Free(a, BUF_ID_GLYPH_DISP_INFO)    ///MLE_Free(a)
#define FREE(a) ttffree(a)                                                                    ///MLE_Free(a)

///#define CALLOC(num,size) msAPI_Memory_CAllocate(num, size, BUF_ID_GLYPH_DISP_INFO)        ///MLE_Calloc(num,size)
#define CALLOC(num,size) ttfcalloc(num, size)        ///MLE_Calloc(num,size)

#define HASHMALLOC(size) hashmalloc(size)                                                                        ///MLE_Malloc(size)
#define HASHREALLOC(ptr, size) hashrealloc(ptr, size)                                                         ///MLE_Realloc(ptr, size)
#define HASHFREE(a) hashfree(a)                                                                    ///MLE_Free(a)
#define HASHCALLOC(num,size) hashcalloc(num, size)        ///MLE_Calloc(num,size)

#define MEMSET(a,v,n) memset(a,v,n)
#define MEMCMP(s1,s2,size) memcmp(s1,s2,size)
#define MEMCPY(d,s,c) memcpy(d,s,c)

#define BREAK_IF_NULL(p, nRetVar, RetVal, str) \
    {                                          \
        if(NULL == (p))                        \
        {                                      \
            nRetVar = RetVal;                  \
            ASSERT(0); \
            break;\
        }\
    }

#define BREAK_IF_FAIL(a, str)                   \
    {                                           \
        if(MLE_RET_SUCCESS != (a))              \
        {                                       \
            ASSERT(0);  \
            break;\
        }\
    }

#define BREAK_IF_WARNING(a, str) \
    {\
        if(MLE_RET_SUCCESS != (a))\
        {\
            break;\
        }\
    }

#define RET_IF_FAIL(a, str)                     \
    {                                           \
        if(MLE_RET_SUCCESS != (a))              \
        {                                       \
            ASSERT(0); \
            return;\
        }\
    }

#define RET_VAL_IF_FAIL(a, str)                 \
    {                                           \
        if(MLE_RET_SUCCESS != (a))              \
        {                                       \
            ASSERT(0);                      \
            return (a);\
        }\
    }

#define RET_IF_NULL(p, str)                \
    {                                      \
        if(NULL == (p))                    \
        {                                  \
            ASSERT(0);\
            return;\
        }\
    }

#define RET_VAL_IF_NULL(p, v, str)         \
    {                                      \
        if(NULL == (p))                    \
        {                                  \
            ASSERT(0); \
            return (v);\
        }\
    }

#define LOG_IF_FAIL(_level_, a, str) \
    {\
        if(MLE_RET_SUCCESS != (a))\
        {\
            LOG_ERROR((_level_), str, (a));\
        }\
    }

#define TTF_TRACE(x)    //x

#endif //__MSAPI_MLE_COMMON_DEF_H__
/*=============================================================*/
// end of file
