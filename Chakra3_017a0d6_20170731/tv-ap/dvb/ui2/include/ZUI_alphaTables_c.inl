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
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIalphatables.h"


//NOTE: when you add new OSD page, you need to add here!

#if (ZUI_ENABLE_ALPHATABLE)

#if (UI_SKIN_SEL==UI_SKIN_1366X768X565)

#elif (UI_SKIN_SEL==UI_SKIN_1920X1080X565)

#elif (UI_SKIN_SEL==UI_SKIN_960X540XI8)

#elif (UI_SKIN_SEL==UI_SKIN_960X540X565)

#else
    #error
#endif

#endif //ZUI_ENABLE_ALPHATABLE
