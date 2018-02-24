////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2010-2011 MStar Semiconductor, Inc.
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


#ifndef KMVBUFFER_H
#define KMVBUFFER_H

#define KMV_STCO_CACHE  512
#define KMV_STSZ_CACHE  8704
#define KMV_MAP_CACHE   1024
#define KMV_STCOENTRY   4
#define KMV_STSZENTRY   6
#define KMV_MAPENTRY    256

typedef struct tagkmvcache {
    uint8_t       *cache_page;
    uint32_t         page_idx;
} KMVCACHE;
#endif /* KMVBUFFER_H */
