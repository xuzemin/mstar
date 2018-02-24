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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

#define _MSAPI_STILLIMAGE_DLMALLOC_C_
///////////////////////////////////////////////////////////////////////////////
/// @file   msAPI_ImageDecoder_Dlmalloc.c
/// @author MStar Semiconductor Inc.
/// @brief  This file implements a simple dynamic memory allocation mechanism and
///  provides function for memory allocation/free
///////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
#include <stdlib.h> 
#include "msapi_stillimage_dlmalloc.h"

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
struct __mem__
{
    struct __mem__ *next;  /* single-linked list */
    U32 len;                /* length of following block */
};

typedef struct __mem__ __memt__;
typedef __memt__ *__memp__;

#define HLEN        (sizeof(__memt__))
#define MIN_BLOCK   (HLEN * 4)

#define MIN_POOL_SIZE   (HLEN * 10)
#define _4BAlign(x)     ((x + 0x3) & ~0x3)
#define _4LAlign(x)     ((x) & ~0x3)

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define DLMALLOC_DBG(x) //x
#define DLMALLOC_ERR(x) x

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------
static __memt__ __mem_avail__[2] =
{
    {NULL, 0},  /* HEAD for the available block list */
    {NULL, 0},  /* UNUSED but necessary so free doesn't join HEAD or ROVER with the pool */
};
#define AVAIL   (__mem_avail__[0])

//------------------------------------------------------------------------------
// Local Function Prototypes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Function Implementation
//------------------------------------------------------------------------------
BOOL msAPI_StillImage_Dlmalloc_InitMemPool(void *pAddr, U32 u32Size)
{
    if ((u32Size < MIN_POOL_SIZE) || (pAddr == NULL))
    {
        DLMALLOC_ERR(printf("[Dlmalloc] init failed. a: 0x%08x, s: %d\n", pAddr, u32Size));
        return FALSE;   /* FAILURE */
    }

//    memset(pAddr, 0, u32Size);

//    AVAIL.next = (struct __mem__ *)(((U32)pAddr & ~CPU_NON_CACHE_MASK) | CPU_CACHE_MASK);
    AVAIL.next = (struct __mem__ *)pAddr;
    AVAIL.len = u32Size;

    (AVAIL.next)->next = NULL;
    (AVAIL.next)->len = u32Size - HLEN;

    DLMALLOC_DBG(printf("[Dlmalloc] init ok, a: 0x%08x, s: %d\n", pAddr, u32Size));

    return TRUE;                    /* SUCCESS */
}

void *msAPI_StillImage_Dlmalloc_Malloc(U32 u32Size)
{
#if defined (MSOS_TYPE_LINUX) && defined (CHIP_KRONUS2) //because K2 enable HW deocde small size GIF, inter buffer will be used for disp. ==> core dump
    return (void *) malloc(u32Size);
#else
    __memp__ q;         /* ptr to free block */
    __memp__ p;         /* q->next */
    __memp__ r;         /* result */
    U32 k = 0;          /* space remaining in the allocated block */
    q = &AVAIL;

    u32Size = _4BAlign(u32Size);
    while (1)
    {
        if ((p = q->next) == NULL)
        {
            r = NULL;       /* FAILURE */
            DLMALLOC_ERR(printf("[Dlmalloc] alloc failed. s: 0x%08x, left: %d\n", q->len, u32Size));
            goto ret;
        }

        if (p->len >= u32Size)
            break;

        q = p;
    }

    k = p->len - u32Size;   /* calc. remaining bytes in block */

    if (k < MIN_BLOCK)      /* rem. bytes too small for new block */
    {
        q->next = p->next;
        r = &p[1];          /* SUCCESS */
        goto ret;
    }

    k -= HLEN;
    p->len = k;

    q = (__memp__ )_4LAlign((U32)(&p [1]) + k);
    q->len = u32Size;
    q->next = NULL;
    r = &q[1];              /* SUCCESS */

ret:
    DLMALLOC_DBG(printf("[Dlmalloc] alloc, r: 0x%08x, s: %d, left: %d\n", r, u32Size, k));

    return (r);
#endif    
}

void msAPI_StillImage_Dlmalloc_Free(void *pMem)
{
#if defined (MSOS_TYPE_LINUX) && defined (CHIP_KRONUS2) //because K2 enable HW deocde small size GIF, inter buffer will be used for disp. ==> core dump
    if(pMem!=NULL)
        free(pMem);
#else
    __memp__ q;     /* ptr to free block */
    __memp__ p;     /* q->next */
    __memp__ p0;    /* block to free */

    if ((pMem == NULL) || (AVAIL.len == 0))
        return;

    p0 = (__memp__)pMem;
    p0 = &p0[-1];       /* get address of header */

    DLMALLOC_DBG(printf("[Dlmalloc]  free, r: 0x%08x, s: %d\n", pMem, p0->len));

    q = &AVAIL;

    while (1)
    {
        p = q->next;
        if ((p == NULL) || (p > (__memp__)pMem))
            break;

        q = p;
    }

    if ((p != NULL) && ((((char *)pMem) + p0->len) == (char *)p))
    {
        p0->len += p->len + HLEN;
        p0->next = p->next;
    }
    else
    {
        p0->next = p;
    }

    if ((((char *)q) + q->len + HLEN) == (char *)p0)
    {
        q->len += p0->len + HLEN;
        q->next = p0->next;
    }
    else
    {
        q->next = p0;
    }
#endif
}

#undef _MSAPI_PHOTO_DLMALLOC_C_

///*** please do not remove change list tag ***///
///***$Change: 428882 $***///
