////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "ms_malloc.h"


#define MAX_ALIGN               MSM_MAX_ALIGN
#define ALIGN_VAL(v, n)         (((v) + (n) - 1) & -(n))
#define ALIGN_PTR(p, n)         ((void *) ALIGN_VAL((intptr_t) (p), n))
#define HEADER_SIZE             ALIGN_VAL(sizeof(heap_node_st), MAX_ALIGN)

#ifdef __RTK_OS__
#  include "sys_MsWrapper_cus_os_mem.h"
#  define MS_HEAP_MALLOC        MsAllocateMem
#  define MS_HEAP_REALLOC       MsMemoryReAllocate
#  define MS_HEAP_FREE          MsReleaseMemory
#  define MS_PHYS_MALLOC        MsPMalloc
#  define MS_PHYS_FREE          MsReleaseMemory
#else
#  define MS_HEAP_MALLOC        malloc
#  define MS_HEAP_REALLOC       realloc
#  define MS_HEAP_FREE          free
#  define MS_PHYS_MALLOC        malloc
#  define MS_PHYS_FREE          free
#endif

#if defined(__RTK_OS__) && defined(MMP_USE_IRAM)
#  define MS_SRAM_MALLOC        MsGetIramMemory
#  define MS_SRAM_FREE          MsReleaseIramMemory
#else
#  define MS_SRAM_MALLOC(s)     ((void *) 0)
#  define MS_SRAM_FREE(p)       ((void) 0)
#endif


#ifdef ALLOCATE_FROM_PMEM
#include "pmem_mm.h"
#endif

#ifdef MSTAR_HEAP_EMU

typedef struct heap_node_s heap_node_st;

struct heap_node_s
{
    unsigned int size;
    heap_node_st *next;
};

static heap_node_st *heap_root;

#endif


int ms_heap_init(char *heap, size_t size)
{
#ifdef MSTAR_HEAP_EMU
    unsigned int align = (intptr_t) heap & (MAX_ALIGN - 1);

    size = size & (-MAX_ALIGN);
    if (size < HEADER_SIZE + MAX_ALIGN)
        return -1;

    if (align) {
        heap += 16 - align;
        size -= 16 - align;
    }

    heap_root = (void *) heap;
    heap_root->size = size;
    heap_root->next = 0;
#endif
    return 0;
}

void ms_heap_free(void)
{
}

void *ms_heap_malloc(size_t size)
{
    void *ptr;

#ifdef MSTAR_HEAP_EMU
    {
        heap_node_st *prev, *next;

        size += HEADER_SIZE;

        prev = next = heap_root;
        while (next && next->size < size)
        {
            prev = next;
            next = next->next;
        }

        if (!next) return 0;

        if (next->size < size + HEADER_SIZE)
        {
            /* we cannot split this node */
            if (next == heap_root)
            {
                heap_root = heap_root->next;
            }
            else
            {
                prev->next = next->next;
            }
            ptr =  (char *) next + HEADER_SIZE;
        }
        else
        {
            /* split the node */
            heap_node_st *header = (void *) ((char *) next + next->size - size);
            next->size -= size;
            header->size = size;
            ptr = (char *) header + HEADER_SIZE;
        }
    }
#else
    if (size == 0)
        return 0;

    ptr = MS_HEAP_MALLOC(size);
#endif

    return ptr;
}

void *ms_heap_realloc(void *ptr, size_t size)
{
    return MS_HEAP_REALLOC(ptr, size);
}

static void ms_free(void *ptr)
{
    if (!ptr)
        return;

#ifdef MSTAR_HEAP_EMU
    {
        heap_node_st *prev, *next, *curr;

        curr = (void *) ((char *) ptr - HEADER_SIZE);

        if (!heap_root)
        {
            heap_root = curr;
            heap_root->next = 0;
        }

        prev = next = heap_root;

        while (next && curr >= next)
        {
            prev = next;
            next = next->next;
        }

        /* merge current node and next node */
        assert(curr != next);
        curr->next = next;

        if ((char *) curr + curr->size == (char *) next)
        {
            curr->size += next->size;
            curr->next  = next->next;
        }

        if (curr <= prev)
        {
            /* insert at root */
            heap_root = curr;
        }
        else
        {
            /* merge pervious node and current node */
            prev->next = curr;

            if ((char *) prev + prev->size == (char *) curr)
            {
                prev->size += curr->size;
                prev->next  = curr->next;
            }
        }
    }
#else
    MS_HEAP_FREE(ptr);
#endif
}

void ms_heap_freep(void **ptr)
{
    assert(ptr);
    ms_free(*ptr);
    *ptr = 0;
}

void *ms_phys_malloc(size_t size)
{
#ifdef ALLOCATE_FROM_PMEM
    void* addr;

    if (size == 0)
        return 0;
    addr = pmem_mm_alloc(size);
    if (addr != 0)
        addr = pmem_mm_pa2va((unsigned int)addr);
    return addr;
#else
    if (size == 0)
        return 0;
    return MS_PHYS_MALLOC(size);
#endif
}

void ms_phys_freep(void **ptr)
{
#ifdef ALLOCATE_FROM_PMEM
    if (!*ptr)
        return;
    pmem_mm_free(pmem_mm_va2pa((unsigned int)*ptr));
    *ptr = 0;
#else
    if (!*ptr)
        return;
    MS_PHYS_FREE(*ptr);
    *ptr = 0;
#endif
}

void *ms_sram_malloc(size_t size)
{
    if (size == 0)
        return 0;
    return MS_SRAM_MALLOC(size);
}

void ms_sram_freep(void **ptr)
{
    if (!*ptr)
        return;
    MS_SRAM_FREE(*ptr);
    *ptr = 0;
}
