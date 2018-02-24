////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

#define PQTABLE_NAME    SUBCOLOR                // table config parameter

#include <pthread.h>

#include "MsTypes.h"
#include "drvXC_IOPort.h"
#include "apiXC.h"

#include "color_reg.h"
#include "drvPQ_Define.h"
#if ENABLE_PQ_CUSTOMER_SUB_GRULE
#include "drvPQ_Declare.h"
#include "drvPQ.h"
#include "hwreg_utility2.h"

#define PQTBL_REGTYPE       PQTBL_COLOR    // table config parameter

#if(PQ_ONLY_SUPPORT_BIN == 0)
#if PQ_ENABLE_PIP
#if 0//PANEL_CURRENT_TYPE_SEL == PNL_FULLHD_CMO216_H1L01
#include "Eden_Sub_Color.c"                   // table config parameter
#include "Eden_Sub_Color_1920.c"              // table config parameter
#else
    //other panels
#endif
#endif
#endif

#include "QualityMode.h"
#include "drvPQ_Datatypes.h"
#if PQ_ENABLE_PIP
#include "drvPQ_Template.h"
#endif
#endif
