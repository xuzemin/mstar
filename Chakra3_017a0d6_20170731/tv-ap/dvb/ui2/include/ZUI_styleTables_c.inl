////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#include "MApp_ZUI_APIcomponent.h"


#if (UI_SKIN_SEL==UI_SKIN_1366X768X565)
            #include "../res1366x768x565/OSDWndDrawStyleTbl_c.inl"
#elif (UI_SKIN_SEL==UI_SKIN_960X540X565)
#if 0 //(( MEMORY_MAP == MMAP_32MB )&&(ENABLE_ATSC))
#include "../res960x540x565_atsc/OSDWndDrawStyleTbl_c.inl"
#else
#include "../res960x540x565/OSDWndDrawStyleTbl_c.inl"
#endif
#elif (UI_SKIN_SEL==UI_SKIN_960X540XI8)
#include "../res960x540xI8/OSDWndDrawStyleTbl_c.inl"
#elif (UI_SKIN_SEL==UI_SKIN_1920X1080X565)
#include "../res1920x1080x565/OSDWndDrawStyleTbl_c.inl"
#else
    #error
#endif
