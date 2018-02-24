////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (; MStar; Confidential; Information; ) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//

#ifndef _MILAN_BANDWIDTH_REGTABLE_H_
#define _MILAN_BANDWIDTH_REGTABLE_H_

typedef enum
{
    BWTABLE_SDi_mode,
    BWTABLE_SDp_mode,
    BWTABLE_HDi_mode,
    BWTABLE_HDp_mode,
    BWTABLE_1080p_mode,
    BWTABLE_MM_HD,
    BWTABLE_MM_720p,
    BWTABLE_MM_720p_DDR2_64MB,
    BWTABLE_MM_Photo,
    BWTABLE_MM_SD,
    BWTABLE_PC_SD_mode,
    BWTABLE_PC_HD_mode,
    BWTABLE_NUMS
}
BWTABLE_Group;

#endif
