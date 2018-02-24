
#include "Board.h"


#if(ENABLE_DEMOD_DVBC)

BOOL msAPI_Demod_DVBC_Init(void)
{
    devQAM_Init();

    return TRUE;
}

void msAPI_Demod_DVBC_Set_Power(BOOL bTurnOn)
{
    devQAM_ControlPowerOnOff(bTurnOn);
}

void msAPI_Demod_DVBC_Exit(void)
{
  #if (FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
  //Disconnect();

  #elif DEMOD_DVBC_USE_UTOPIA
    MDrv_DMD_DVBC_Exit();

  #else
    INTERN_DVBC_Exit();
  #endif
}

EnuApiDemodLockStatus msAPI_Demod_DVBC_Get_LockStatus(void)
{
    if( TRUE == devQAM_GetLockStatus(QAM_FEC_LOCK) )
    {
        return E_API_DEMOD_STATUS_LOCKED;
    }

    return E_API_DEMOD_STATUS_NO_LOCK;
}

#if( (FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)   \
    )
    #define DEMOD_DVBC_DETECT_LOCK_TIMEOUT__NORMAL      6000
    #define DEMOD_DVBC_DETECT_LOCK_TIMEOUT__NO_TR_LOCK  1000

#elif( (FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD)     \
    || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD) )
    #define DEMOD_DVBC_DETECT_LOCK_TIMEOUT__NORMAL      4000
    #define DEMOD_DVBC_DETECT_LOCK_TIMEOUT__NO_TR_LOCK  1000

#else //
    #define DEMOD_DVBC_DETECT_LOCK_TIMEOUT__NORMAL      6000
    #define DEMOD_DVBC_DETECT_LOCK_TIMEOUT__NO_TR_LOCK  1000
#endif

EnuApiDemodLockStatus msAPI_Demod_DVBC_DetectLockTask(void)
{
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    U32 u32Timeout = DEMOD_DVBC_DETECT_LOCK_TIMEOUT__NORMAL;


    if ( TRUE == devQAM_GetLockStatus(QAM_FEC_LOCK) )
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_LOCKED;
        return eDemodLockStatus;
    }

#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
    if( devQAM_GetSymbolRateMode() == 1 )
    {
        u32Timeout = 10000; // 10sec  for SR auto mode
    }
#endif

    if ( FALSE == devQAM_GetLockStatus(QAM_TR_LOCK) )
    { //Speed up
        u32Timeout = DEMOD_DVBC_DETECT_LOCK_TIMEOUT__NO_TR_LOCK;
    }


#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
    if ((devQAM_GetSpeedUp() & 0x0504) > 0)
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    }
    else
#endif
    if( msAPI_Demod_Get_DetectLockUseTime() > u32Timeout )
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    }
    else
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_CHECKING;
    }

    return eDemodLockStatus;
}


#endif

