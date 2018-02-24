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


/*=============================================================*/
// Include Files
/*=============================================================*/
#include <math.h>
#include "msAPI_COMMON_hashtable.h"
#include "msAPI_COMMON_hashtable_util.h"

#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_font_vector.h"

#include "msAPI_OSD.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
// for hash table insert entry, the equation is about sizeof(MemHandle_t) + (pool size+pool overhead)*number
#define HASH_ENTRY_MEM_SIZE(n)          (3000+(sizeof(struct entry)+20)*(n))    
/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/*=============================================================*/
// Variable Declarations
/*=============================================================*/
static const unsigned int primes[] =
{
    53, 97, 193, 389,
    769, 1543, 3079, 6151,
    12289, 24593, 49157, 98317,
    196613, 393241, 786433, 1572869,
    3145739, 6291469, 12582917, 25165843,
    50331653, 100663319, 201326611, 402653189,
    805306457, 1610612741
};

const float max_load_factor = (float)0.65;

static int msAPI_COMMON_hashtable_expand(Hashtable_t *pHashTable)
{
    struct entry **ppNewEntries = NULL;
    struct entry *pEntry = NULL;
    unsigned int nNewSize, nIndex, nIndexEntry;
    if(pHashTable->nPrimeIndex == (sizeof(primes) / sizeof(primes[0])) - 1)
    {
        return 0;
    }
    pHashTable->nPrimeIndex++;
    nNewSize = primes[pHashTable->nPrimeIndex];
    TTF_TRACE(printf("%d %s: %d ", __LINE__, __FUNCTION__, sizeof(struct entry) * nNewSize));
    ppNewEntries = (struct entry**)MALLOC(sizeof(struct entry) * nNewSize);
    if(ppNewEntries)
    {
        MEMSET(ppNewEntries, 0, sizeof(struct entry) * nNewSize);
        for(nIndexEntry = 0; nIndexEntry < pHashTable->nLength; nIndexEntry++)
        {
            pEntry = pHashTable->ppEntries[nIndexEntry];
            while(pEntry)
            {
                pHashTable->ppEntries[nIndexEntry] = pEntry->pNext;
                nIndex = pEntry->nHash % nNewSize;
                pEntry->pNext = ppNewEntries[nIndex];
                ppNewEntries[nIndex] = pEntry;
                pEntry = pHashTable->ppEntries[nIndexEntry];
            }
        }
        TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
        FREE(pHashTable->ppEntries);
        pHashTable->ppEntries = ppNewEntries;
    }
    else
    {
        pHashTable->nPrimeIndex--;
        msAPI_MLE_SetMemoryNotEnoughFlag(TRUE);
        return 0;
    }
    pHashTable->nLength = nNewSize;
    pHashTable->nLoadLimit = (unsigned int)ceil(nNewSize * HASHTABLE_LOAD_FACTOR);
    return 1;
}

static int msAPI_COMMON_hashtable_compact(Hashtable_t *pHashTable)
{
    struct entry **ppNewEntries = NULL;
    struct entry *pEntry = NULL;
    unsigned int nNewSize, nIndex, nIndexEntry;
    if(0 == pHashTable->nPrimeIndex)
    {
        return 0;
    }
    pHashTable->nPrimeIndex--;
    nNewSize = primes[pHashTable->nPrimeIndex];
    TTF_TRACE(printf("%s: %d ", __FUNCTION__, sizeof(struct entry) * nNewSize));
    ppNewEntries = (struct entry**)MALLOC(sizeof(struct entry) * nNewSize);
    if(ppNewEntries)
    {
        MEMSET(ppNewEntries, 0, sizeof(struct entry) * nNewSize);

        for(nIndexEntry = 0; nIndexEntry < pHashTable->nLength; nIndexEntry++)
        {
            pEntry = pHashTable->ppEntries[nIndexEntry];
            while(pEntry)
            {
                pHashTable->ppEntries[nIndexEntry] = pEntry->pNext;
                nIndex = pEntry->nHash % nNewSize;
                pEntry->pNext = ppNewEntries[nIndex];
                ppNewEntries[nIndex] = pEntry;
                pEntry = pHashTable->ppEntries[nIndexEntry];
            }
        }
        TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
        FREE(pHashTable->ppEntries);
        pHashTable->ppEntries = ppNewEntries;
    }
    else
    {
        pHashTable->nPrimeIndex++;
        msAPI_MLE_SetMemoryNotEnoughFlag(TRUE);
        return 0;
    }
    pHashTable->nLength = nNewSize;
    pHashTable->nLoadLimit = (unsigned int) ceil(nNewSize * HASHTABLE_LOAD_FACTOR);
    return 1;
}

Hashtable_t* msAPI_COMMON_hashtable_create(unsigned int nMinSize, unsigned int (*pHashFunc)(void *), unsigned int (*pEqualFunc)(void*, void *))
{
    return msAPI_COMMON_hashtable_createEx(nMinSize, 0, pHashFunc, pEqualFunc);
}

Hashtable_t* msAPI_COMMON_hashtable_createEx(unsigned int nInitialSize, unsigned int nMaxSize, unsigned int (*pHashFunc)(void *), unsigned int (*pEqualFunc)(void*, void *))
{
    //todo skip now
    ///gpDesc_t tHashEntryPoolDesc = {0};  
    Hashtable_t *pHashTable = NULL;
    unsigned int nIndex, nSize = primes[0];
    MLE_Ret nRet = MLE_RET_SUCCESS;

    if(nInitialSize > (1 << 30))
    {
        return NULL;
    }
    for(nIndex = 0; nIndex < sizeof(primes) / sizeof(primes[0]); nIndex++)
    {
        if(primes[nIndex] > nInitialSize)
        {
            nSize = primes[nIndex];
            break;
        }
    }
    do 
    {
        TTF_TRACE(printf("%d %s: %d ", __LINE__, __FUNCTION__, 1*sizeof(Hashtable_t)));
        pHashTable = (Hashtable_t*)CALLOC(1, sizeof(Hashtable_t));
        if(!pHashTable)
        {
            return NULL;
        }

        TTF_TRACE(printf("%d %s: %d ", __LINE__, __FUNCTION__, sizeof(struct entry*)*nSize));
        pHashTable->ppEntries = (struct entry**)CALLOC(sizeof(struct entry*), nSize);
        if(!pHashTable->ppEntries)
        {
            nRet = MLE_RET_OUT_OF_MEMORY;
            break;
        }

        if(0 != nMaxSize)
        {
            TTF_TRACE(printf("%d %s: %d nMaxSize=%d ", __LINE__, __FUNCTION__, 1*HASH_ENTRY_MEM_SIZE(nMaxSize), nMaxSize));
            //pHashTable->pEntryMem = CALLOC(1, HASH_ENTRY_MEM_SIZE(nMaxSize));
            //if(!pHashTable->pEntryMem)
            //{
                //nRet = MLE_RET_OUT_OF_MEMORY;
                //break;
            //}
            ///pHashTable->nEntryMemHandle = 0;
            //todo skip now
            ///pHashTable->nEntryMemHandle = MsHMEMCreate(pHashTable->pEntryMem, HASH_ENTRY_MEM_SIZE(nMaxSize));
            ///tHashEntryPoolDesc.ClusterNum = nMaxSize;
            ///tHashEntryPoolDesc.ClusterSize = sizeof(struct entry);
            ///MsHMEMInitializePool(pHashTable->nEntryMemHandle, &tHashEntryPoolDesc, 1);
        }

        pHashTable->nLength     = nSize;
        pHashTable->nPrimeIndex = nIndex;
        pHashTable->nCount      = 0;
        pHashTable->nLoadLimit  = (unsigned int)ceil(nSize * HASHTABLE_LOAD_FACTOR);
        pHashTable->pHashFunc   = pHashFunc;
        if(!pHashTable->pHashFunc)
        {
            pHashTable->pHashFunc = msAPI_COMMON_hashtable_hash_int; //default using int
        }
        pHashTable->pEqualFunc = pEqualFunc;
        if(!pHashTable->pEqualFunc)
        {
            pHashTable->pEqualFunc = msAPI_COMMON_hashtable_int_equals; //default using int equals
        }
    } while (0);
    
    if(MLE_RET_SUCCESS != nRet)
    {
        TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
        FREEIF(pHashTable->ppEntries);
        //TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
        //FREEIF(pHashTable->pEntryMem);
        TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
        FREEIF(pHashTable);
    }
    return pHashTable;
}

void msAPI_COMMON_hashtable_destroy(Hashtable_t *pHashTable)
{
    unsigned int nIndex;
    struct entry *pCurEntry = NULL, *pPrevEntry = NULL;
    
    if (pHashTable == NULL)
        return;

    for(nIndex = 0; nIndex < pHashTable->nLength; nIndex++)
    {
        pCurEntry = pHashTable->ppEntries[nIndex];
        while(pCurEntry)
        {
            pPrevEntry = pCurEntry;
            pCurEntry  = pCurEntry->pNext;

            if(pHashTable->pEqualFunc == msAPI_COMMON_hashtable_wstr_equals)
            {
                TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
                FREE(pPrevEntry->pKey);
            }

            if ( pHashTable->nCount > 0 )
                pHashTable->nCount--;

            pPrevEntry->pKey = NULL;
            pPrevEntry->pValue = NULL;
            pPrevEntry->nHash = 0;
            pPrevEntry->pNext = NULL;

            ///if(0 == pHashTable->nEntryMemHandle)
            ///{
                TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
                HASHFREE(pPrevEntry);
            ///}
            ///else
            ///{
                //todo skip now
                ///MsHMEMFree(pPrevEntry, 0);
                ///TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
                ///FREE(pPrevEntry);
            ///}

            pPrevEntry = NULL;
            pHashTable->ppEntries[nIndex] = pCurEntry;
        }
    }

    //todo modify
    //if(pHashTable->pEntryMem)
    ///if(pHashTable->nEntryMemHandle)
    //{
        //todo skip now
        ///MsHMEMClose(pHashTable->nEntryMemHandle);
        //TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
        //FREE(pHashTable->pEntryMem);
    //}
    TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
    FREE(pHashTable->ppEntries);
    TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
    FREE(pHashTable);
}

int msAPI_COMMON_hashtable_insert(Hashtable_t *pHashTable, void *pKey, void *pValue)
{
    unsigned int nIndex;
    struct entry *pEntry = NULL;
    U32 nSize;
    pHashTable->nCount++;
    if(pHashTable->nCount > pHashTable->nLoadLimit)
    {
        if ( ( msAPI_COMMON_hashtable_expand(pHashTable) == 0 ) && ( msAPI_MLE_GetMemoryNotEnoughFlag() == TRUE ) )
        {
            pHashTable->nCount--;
            return 0;
        }
    }

    ///if(0 == pHashTable->nEntryMemHandle)
    ///{
        TTF_TRACE(printf("%d %s: %d ", __LINE__, __FUNCTION__, sizeof(struct entry)));
        pEntry = (struct entry*)HASHMALLOC(sizeof(struct entry));
    ///}
    ///else
    ///{
        //todo skip now
        ///pEntry = (struct entry*)MsHMEMMalloc(pHashTable->nEntryMemHandle, sizeof(struct entry), 0);
        ///TTF_TRACE(printf("%d %s: %d ", __LINE__, __FUNCTION__, sizeof(struct entry)));
        ///pEntry = (struct entry*)MALLOC(sizeof(struct entry));
    ///}

    if(!pEntry)
    {
        pHashTable->nCount--;
        TTF_TRACE(printf("%d %s FAIL\n", __LINE__, __FUNCTION__));
        msAPI_MLE_SetMemoryNotEnoughFlag(TRUE);
        return 0;
    }

    pEntry->nHash = pHashTable->pHashFunc(pKey);

    if(pHashTable->pEqualFunc == msAPI_COMMON_hashtable_wstr_equals)
    {
        //todo skip now
        ///nSize = (U32)sysUtil_UCS2StringLength((MLE_WChar*)pKey);
        nSize = (U32)msAPI_OSD_u16Strlen((U16*)pKey);
        TTF_TRACE(printf("%d %s: %d ", __LINE__, __FUNCTION__, sizeof((nSize+1)*sizeof(MLE_WChar))));
        pEntry->pKey = (MLE_WChar*)MALLOC((nSize+1)*sizeof(MLE_WChar));
        //todo skip now
        ///sysUtil_UCS2StringCopy((MLE_WChar*)pEntry->pKey, (MLE_WChar*)pKey);
        if ( pEntry->pKey != NULL )
            msAPI_OSD_u16Strcpy((U16 *)pEntry->pKey, (U16 *)pKey);
        else
            msAPI_MLE_SetMemoryNotEnoughFlag(TRUE);
    }
    else
    {
        pEntry->pKey = pKey;
    }

    pEntry->pValue = pValue;

    nIndex = HASHTABLE_INDEX_OF(pHashTable, pEntry->nHash);

    pEntry->pNext = pHashTable->ppEntries[nIndex];
    pHashTable->ppEntries[nIndex] = pEntry;
    
    TTF_TRACE(printf("%d %s OK\n", __LINE__, __FUNCTION__));
    return 1;
}

void* msAPI_COMMON_hashtable_update(Hashtable_t *pHashTable, void *pKey, void *pValue)
{
    struct entry *pEntry = NULL;
    unsigned int nHash, nIndex;
    void *pOldValue;

    nHash  = pHashTable->pHashFunc(pKey);
    nIndex = HASHTABLE_INDEX_OF(pHashTable, nHash);
    pEntry = pHashTable->ppEntries[nIndex];
    while(pEntry)
    {
        if((nHash == pEntry->nHash) && pHashTable->pEqualFunc(pKey, pEntry->pKey))
        {
            pOldValue = pEntry->pValue;
            pEntry->pValue = pValue;
            return pOldValue;
        }
        pEntry = pEntry->pNext;
    }
    return NULL;
}

void* msAPI_COMMON_hashtable_search(Hashtable_t *pHashTable, void *pKey)
{
    struct entry *pEntry = NULL;
    unsigned int nHash, nIndex;
    nHash  = pHashTable->pHashFunc(pKey);
    nIndex = HASHTABLE_INDEX_OF(pHashTable, nHash);
    pEntry = pHashTable->ppEntries[nIndex];
    while(pEntry)
    {
        if((nHash == pEntry->nHash) && pHashTable->pEqualFunc(pKey, pEntry->pKey))
        {
            return pEntry->pValue;
        }
        pEntry = pEntry->pNext;
    }
    return NULL;
}

void* msAPI_COMMON_hashtable_remove(Hashtable_t *pHashTable, void *pKey)
{
    struct entry *pEntry = NULL;
    struct entry *pPrev = NULL;
    unsigned int nHash, nIndex;
    void *pValue = NULL;
 
    //Compact hash table if used count less than half of previous primes level.
    if(pHashTable->nPrimeIndex > 0 && pHashTable->nCount < (primes[pHashTable->nPrimeIndex-1] >> 1) )
    {
        msAPI_COMMON_hashtable_compact(pHashTable);
    }
    nHash  = pHashTable->pHashFunc(pKey);
    nIndex = HASHTABLE_INDEX_OF(pHashTable, nHash);
    pEntry = pHashTable->ppEntries[nIndex];
#if 1
    while(pEntry)
    {
        if((nHash == pEntry->nHash) && pHashTable->pEqualFunc(pKey, pEntry->pKey))
        {
            if(NULL == pPrev)
            {
                pHashTable->ppEntries[nIndex] = pEntry->pNext;
            }
            else
            {
                pPrev->pNext = pEntry->pNext;
            }

            pHashTable->nCount--;
            if(pHashTable->pEqualFunc == msAPI_COMMON_hashtable_wstr_equals)
            {
                TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
                FREE(pEntry->pKey);
            }
            pValue = pEntry->pValue;

            pEntry->pKey = NULL;
            pEntry->pValue = NULL;
            pEntry->nHash = 0;
            pEntry->pNext = NULL;

            ///if(0 == pHashTable->nEntryMemHandle)
            ///{
                TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
                HASHFREE(pEntry);
            ///}
            ///else
            ///{
                //todo skip now
                ///MsHMEMFree(pEntry, 0);
                ///TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
                ///FREE(pEntry);
            ///}

            pEntry = NULL;

            return pValue;
        }
        pPrev  = pEntry;
        pEntry = pEntry->pNext;
    }

    return NULL;
#else
    while(pEntry)
    {
        pPrev = pEntry;
        pEntry  = pEntry->pNext;

        if(pHashTable->pEqualFunc == msAPI_COMMON_hashtable_wstr_equals)
        {
            TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
            FREE(pPrev->pKey);
        }

        if ( pHashTable->nCount > 0 )
            pHashTable->nCount--;

        pValue = pPrev->pValue;

        pPrev->pKey = NULL;
        pPrev->pValue = NULL;
        pPrev->nHash = 0;
        pPrev->pNext = NULL;

        ///if(0 == pHashTable->nEntryMemHandle)
        ///{
            TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
            HASHFREE(pPrev);
        ///}
        ///else
        ///{
            //todo skip now
            ///MsHMEMFree(pPrevEntry, 0);
            ///TTF_TRACE(printf("%d %s ", __LINE__, __FUNCTION__));
            ///FREE(pPrevEntry);
        ///}
        pPrev = NULL;
        pHashTable->ppEntries[nIndex] = pEntry;
    }

    return pValue;

#endif

}

unsigned int msAPI_COMMON_hashtable_size(Hashtable_t *pHashTable)
{
    if (pHashTable == NULL)
        return 0;

    return pHashTable->nCount;
}
