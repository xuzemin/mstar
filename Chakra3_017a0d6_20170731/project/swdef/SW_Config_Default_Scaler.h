#ifndef _SW_CONFIG_DEFAULT_SCALER_H_
#define _SW_CONFIG_DEFAULT_SCALER_H_


//******************************************************************************
// Scaler option...

#ifndef DTV_USE_FBL // Enable FBL mode for some DTV case
    #define DTV_USE_FBL  0
#endif

#ifndef SCALER_USE_FBL_IN_DTV_H265_1080P_50P
    #define SCALER_USE_FBL_IN_DTV_H265_1080P_50P    0
#endif

#ifndef DTV_XC_ENABLE_RFBL
    #define DTV_XC_ENABLE_RFBL      0
#endif

#ifndef ENABLE_DLC_ISR
    #define ENABLE_DLC_ISR    DISABLE
#endif

#ifndef ENABLE_DTV_PRESCALINGDOWN
    #define ENABLE_DTV_PRESCALINGDOWN ENABLE
#endif
//----------------------------------------------------------------------------


#endif // _SW_CONFIG_DEFAULT_DTV_H_

