////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2010 MStar Semiconductor, Inc.
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


#ifndef MS_MALLOC_H
#define MS_MALLOC_H

#include <stddef.h>

//#define MSTAR_HEAP_EMU
#define MSM_MAX_ALIGN   16      /* the maximum alignment requirement */

#ifdef __cplusplus
extern "C" {
#endif

int ms_heap_init(char *heap, size_t size);
void ms_heap_free(void);

void *ms_heap_malloc(size_t size);
void *ms_heap_realloc(void *ptr, size_t size);
void ms_heap_freep(void **ptr);

void *ms_phys_malloc(size_t size);
void ms_phys_freep(void **ptr);

void *ms_sram_malloc(size_t size);
void ms_sram_freep(void **ptr);

#ifdef __cplusplus
}
#endif

#endif /* MS_MALLOC_H */
