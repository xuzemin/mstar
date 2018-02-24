#ifndef _MSAPI_DEMOD_BASIC_H_
#define _MSAPI_DEMOD_BASIC_H_

#include "Board.h"

#if(ENABLE_DTV)

// This enum is for mstar external demod driver
typedef enum
{
    E_DEVICE_DEMOD_ATV = 0,
    E_DEVICE_DEMOD_DVB_T,
    E_DEVICE_DEMOD_DVB_C,
    E_DEVICE_DEMOD_DVB_S,
    E_DEVICE_DEMOD_DTMB,
    E_DEVICE_DEMOD_ATSC,
    E_DEVICE_DEMOD_ATSC_VSB,
    E_DEVICE_DEMOD_ATSC_QPSK,
    E_DEVICE_DEMOD_ATSC_16QAM,
    E_DEVICE_DEMOD_ATSC_64QAM,
    E_DEVICE_DEMOD_ATSC_256QAM,
    E_DEVICE_DEMOD_DVB_T2,
    E_DEVICE_DEMOD_ISDB,
    E_DEVICE_DEMOD_MAX,
    E_DEVICE_DEMOD_NULL = E_DEVICE_DEMOD_MAX,
} EN_DEVICE_DEMOD_TYPE;

typedef enum
{
    /// no signal
    E_FE_SIGNAL_NO = 0,
    /// weak signal
    E_FE_SIGNAL_WEAK,
    /// moderate signal
    E_FE_SIGNAL_MODERATE,
    /// strong signal
    E_FE_SIGNAL_STRONG,
    /// very strong signal
    E_FE_SIGNAL_VERY_STRONG,
} EN_FRONTEND_SIGNAL_CONDITION;

typedef enum
{
    E_DEMODULATOR_TYPE_NULL = 0,
    E_DEMODULATOR_TYPE_DVBT = 1,
    E_DEMODULATOR_TYPE_DVBT2 = 2,
    E_DEMODULATOR_TYPE_DVBC = 3,
    E_DEMODULATOR_TYPE_DVBS_S2 = 4,
//    E_DEMODULATOR_TYPE_DVBS2 = 5,
    E_DEMODULATOR_TYPE_ISDBT = 5,
    E_DEMODULATOR_TYPE_DTMB = 6,
    E_DEMODULATOR_TYPE_ATSC = 7,
    E_DEMODULATOR_TYPE_MAX,
} EN_DEMODULATOR_TYPE;

typedef enum
{
    E_API_DEMOD_STATUS_NO_LOCK,
    E_API_DEMOD_STATUS_LOCKED,
    E_API_DEMOD_STATUS_CHECKING,
} EnuApiDemodLockStatus;

//----------------------------------------------------------------------------

#endif //if(ENABLE_DTV)

#endif // _MSAPI_DEMOD_STD_H_

