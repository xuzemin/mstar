#ifndef _MSAPI_DEMOD_S_H_
#define _MSAPI_DEMOD_S_H_

#include "Board.h"


#if(ENABLE_S2)
#include "COFDM_Demodulator.h"
 #if(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBT)
    #include "msb124x.h"

 #elif(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB131X_DVBS2)
    #include "drvDemod.h"
    #include "device_demodulator_msb131x.h"

 #elif(FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD)
    #include "INTERN_DVBS.h"

 #elif(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB1245_DVBS2)
    #include "DVBS2_MSB102KS/msb1245.h"

#elif(FRONTEND_DEMOD_S2_TYPE == DEMOD_AVL6211)
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx.h"
    #include "AVL_DVBSx_SDK/AVL_Board.h"
    #include "AVL_DVBSx_SDK/AVL_Func.h"
    #include "AVL_DVBSx_SDK/LNB_Controler.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx_globals.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBase.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBlindScan.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBlindscanAPI.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/IDiseqc.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2C.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2CRepeater.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/IRx.h"
    #include "AVL_DVBSx_SDK/AVL_DVBSx/include/ITuner.h"
    #include "AVL_DVBSx_SDK/BSP/bspdatadef.h"
    #include "AVL_DVBSx_SDK/BSP/IBSP.h"
    #include "AVL_DVBSx_SDK/addon/ExtAV2011.h"
    #include "AVL_DVBSx_SDK/addon/ExtSharpBS2S7HZ6306.h"
    #include "AVL_DVBSx_SDK/addon/SharpBS2S7HZ6306.h"


 #else

    //#include "drvCofdmDmd.h"
 #endif



#include "drvDish.h"



//==============================================

BOOL msAPI_Demod_S_Init(void);

void msAPI_Demod_DVBS_Exit(void);

BOOLEAN msAPI_Demod_S_Get_SignalModulMode(WORD *wModul_Mode);

EnuApiDemodLockStatus msAPI_Demod_DVBS_Get_LockStatus(void);
EnuApiDemodLockStatus msAPI_Demod_DVBS_DetectLockTask(void);


BOOL msAPI_Demod_S_Get_SignalStrength(U16 * pu16SignalStrength);

MS_BOOL msAPI_Demod_S_Get_RFOffset(MS_S16 *ps16RFOffset);

void devCOFDM_S2_SwitchTransportSteamInferface(TS_INTERFACE interface);

#endif


#endif

