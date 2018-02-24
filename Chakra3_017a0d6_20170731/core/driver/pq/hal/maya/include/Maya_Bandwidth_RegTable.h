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

#ifndef _EDEN_BANDWIDTH_REGTABLE_H_
#define _EDEN_BANDWIDTH_REGTABLE_H_

typedef enum
{
    BWTABLE_SDi_mode,
    BWTABLE_SDp_mode,
    BWTABLE_HD_mode,
    BWTABLE_DTV_HD,
    BWTABLE_DTV_SD,
    BWTABLE_HDMI_4K,
    BWTABLE_MM_MOVIE_HD,
    BWTABLE_MM_MOVIE_SD,
    BWTABLE_MM_PHOTO,
    BWTABLE_PC_HD,
    BWTABLE_VD_COMB,
    BWTABLE_NUMS
}
BWTABLE_Group;

#endif
