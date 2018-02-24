#ifndef AV2011_h_h
#define AV2011_h_h
#include "Board.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2CRepeater.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/ITuner.h"

#ifdef AVL_CPLUSPLUS
extern "C" {
#endif

#define tuner_slave_address     0xC6
#define tuner_I2Cbus_clock      200             //The clock speed of the tuner dedicated I2C bus, in a unit of kHz.
#define tuner_LPF               340             //The LPF of the tuner,in a unit of 100kHz.

// time delay function ( minisecond )
AVL_DVBSx_ErrorCode AVL_DVBSx_ExtAV2011_Initialize(struct AVL_Tuner * pTuner);
AVL_DVBSx_ErrorCode AVL_DVBSx_ExtAV2011_GetLockStatus(struct AVL_Tuner * pTuner);
AVL_DVBSx_ErrorCode AVL_DVBSx_ExtAV2011_Lock( struct AVL_Tuner * pTuner);

#ifdef AVL_CPLUSPLUS
}
#endif
#endif
