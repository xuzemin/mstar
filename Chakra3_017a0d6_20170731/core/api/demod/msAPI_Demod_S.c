
#if (ENABLE_S2)

#include "apiDigiTuner.h"

#if(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB1245_DVBS2)
#include "DVBS2_MSB102KS/msb1245.c"
#elif(FRONTEND_DEMOD_S2_TYPE==EMBEDDED_DVBS_DEMOD)
#include "drvDMD_INTERN_DVBS.h"
#endif


BOOL msAPI_Demod_S_Init(void)
{
#if( FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD )
    DVBS_Intern_Demod_Init();

#elif( FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBT )
    //PRINT_CURRENT_LINE();
    Demod_MSB124X_Connect(E_DEVICE_DEMOD_DVB_S);
    //DTV_Serial_Control(true);
    Power_On_Initialization();
#elif( FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB1245_DVBS2)

    Demod_MSB1245_Connect(E_DEVICE_DEMOD_DVB_S);
    Power_On_Initialization();
    MDrv_SYS_SetPadMux(E_TS0_PAD_SET, E_SERIAL_IN);

#elif (FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB131X_DVBS2)
    MDrv_Demod_Init();

#elif(FRONTEND_DEMOD_S2_TYPE == DEMOD_AVL6211)
    MDrv_CofdmDmd_Init();

#else

    PRINT_CURRENT_LINE();
    printf("\nError: Unknown demod\n");

    return FALSE;
#endif

    return TRUE;
}

void msAPI_Demod_DVBS_Exit(void)
{
#if( FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD )
    DVBS_Intern_Exit();

#else

    //PRINT_CURRENT_LINE();
    //printf("\nError: Unknown demod\n");
    // Do nothing~

#endif

}

BOOLEAN msAPI_Demod_S_Get_SignalModulMode(WORD *wModul_Mode)
{
#if( FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD )

    BOOLEAN ret;
    DEMOD_MS_FE_CARRIER_PARAM  pParam;
    ret = MDrv_DVBS_Demod_GetParam(&pParam);
    *wModul_Mode = (WORD)pParam.SatParam.eConstellation;
    return ret;

#else

    //PRINT_CURRENT_LINE();
    //printf("\nError: Unknown demod\n");
    wModul_Mode = wModul_Mode;

    return FALSE;
#endif
}

EnuApiDemodLockStatus msAPI_Demod_DVBS_Get_LockStatus(void)
{
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    MS_BOOL bRet = FALSE;
    MS_BOOL bLock = FALSE;


#if( (FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD)    \
   ||(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBT)     \
   ||(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB131X_DVBS2)    \
   ||(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB1245_DVBS2))

    bRet = MDrv_CofdmDmd_GetLock(&bLock);

#else

    #error "Unsupported demod";

#endif

    if( bRet &&  bLock)
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_LOCKED;
    }

    return eDemodLockStatus;
}

#if( (FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBT)   \
    )
    #define DEMOD_DVBS_DETECT_LOCK_TIMEOUT__NORMAL      1100
#else //
    #define DEMOD_DVBS_DETECT_LOCK_TIMEOUT__NORMAL      1500
#endif

EnuApiDemodLockStatus msAPI_Demod_DVBS_DetectLockTask(void)
{
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    U32 u32Timeout = DEMOD_DVBS_DETECT_LOCK_TIMEOUT__NORMAL;


    if( msAPI_Demod_DVBS_Get_LockStatus() == E_API_DEMOD_STATUS_LOCKED )
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_LOCKED;
        return eDemodLockStatus;
    }

/*    if ( FALSE == devCOFDM_GetLockStatus(COFDM_PN_LOCK) )
    { //Speed up
        u32Timeout = DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NO_PN_LOCK;
    }*/

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


/*****************************************************************************/
//using these two variable for getValue, and getText.
//to keep consistency when Value/Text be displayed on screen.
MS_U16 _getCurRFSignalLevelPercentage(void)
{
    #define DEFAULT_PWR_MIN (5)
    #define DEFAULT_PWR_MAX (98)

    MS_S16   s16PWR  = 0;
    MS_U16   _u16pwr = 0;
    MApi_DigiTuner_GetPWR(&s16PWR);
    MS_U16 u16Precent  = ((s16PWR - DEFAULT_PWR_MIN) * 100) /
                         (MS_S16)(DEFAULT_PWR_MAX - DEFAULT_PWR_MIN);

    _u16pwr = ((u16Precent >= 100) ? 100 : u16Precent);
	//printf(">>>>>>>>>%d\n", _u16pwr);
    return _u16pwr;
}

BOOL msAPI_Demod_S_Get_SignalStrength(U16 * pu16SignalStrength)
{
    U16 u16SignalStrength = 0;
    BOOL bRtn = TRUE;

#if( (FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBT) \
   ||(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB1245_DVBS2))

    u16SignalStrength = DTV_GetSignalStrength();

#elif( FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD )

    u16SignalStrength = _getCurRFSignalLevelPercentage();

#else

    bRtn = FALSE;

#endif

    if( bRtn )
    {
        *pu16SignalStrength = u16SignalStrength;
        DEBUG_DEMOD_S( printf(" [DVBS Str=%u] ", u16SignalStrength); );
    }

    return bRtn;
}

MS_BOOL msAPI_Demod_S_Get_RFOffset(MS_S16 *ps16RFOffset)
{
    MS_BOOL bRet = FALSE;

#if(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBT)

    bRet = MDrv_CofdmDmd_GetRFOffset(ps16RFOffset);
    *ps16RFOffset = 0; // Don't need
    bRet = TRUE;

#elif( (FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD)    \
     ||(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB131X_DVBS2)    \
     ||(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB1245_DVBS2))

    bRet = MDrv_CofdmDmd_GetRFOffset(ps16RFOffset);

#else

    bRet = MDrv_CofdmDmd_GetRFOffset(ps16RFOffset);

#endif

    return bRet;
}

FUNCTION_RESULT devCOFDM_S2_GetSignalQuality(WORD *quality)
{
    *quality = _MApp_getCurRFSignalSNR();
    return E_RESULT_SUCCESS;
}

void devCOFDM_S2_SwitchTransportSteamInferface(TS_INTERFACE interface)
{
    BOOLEAN bEnable;

    if ( interface == E_SERIAL_INTERFACE )
    {
        bEnable = TRUE;
    }
    else
    {
        bEnable = FALSE;
    }

#if ENABLE_S2
    #if (FRONTEND_DEMOD_S2_TYPE==EMBEDDED_DVBS_DEMOD)
        #if DEMOD_S2_USE_UTOPIA
            if(IsS2InUse())
                MDrv_DMD_DVBS_SetSerialControl(bEnable);
        #endif
    #endif
#endif
}

#endif

