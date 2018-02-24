#ifndef _DRV_AEONR2_H_
#define _DRV_AEONR2_H_

#if defined(__aeon__)

#include "Board.h"

#include "MsTypes.h"



void MDrv_AeonR2_Backtrace(MS_U32 pHalReg);

#if 0//( ENABLE_R2_BACKTRACE )
BOOL MDrv_R2BT_RecvDataHandler(U8 u8Data, MS_U32 pHalReg);
#endif

#endif // __aeon__
#endif // _DRV_AEONR2_H_

