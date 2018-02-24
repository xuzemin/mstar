
#include "Board.h"

#if (ENABLE_DEMOD_ISDBT)



#include "Tuner.h"
#include "COFDM_Demodulator.h"

 #if ((FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_ISDBT_DEMOD)  \
    ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB1400_DEMOD))
    #include "drvDMD_common.h"
    #include "drvDMD_ISDBT.h"
 #endif

 #if (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    #include "INTERN_ISDBT.h"
 #endif


extern MS_BOOL MDrv_DMD_ISDBT_Exit(void);


BOOL msAPI_Demod_ISDBT_Init(void)
{
    //devCOFDM_Init();
  #if (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    INTERN_ISDBT_Power_On_Initialization();
  #elif (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    EXTERN_ISDBT_Power_On_Initialization();
  #endif

    devDigitalTuner_Init();

    return TRUE;
}


void msAPI_Demod_ISDBT_Exit(void)
{
  #if 1//DEMOD_ISDBT_USE_UTOPIA
    MDrv_DMD_ISDBT_Exit();
  #else
    INTERN_ISDBT_Exit();
  #endif
}

EnuApiDemodLockStatus msAPI_Demod_ISDBT_Get_LockStatus(void)
{
    EnuApiDemodLockStatus eStatus = E_API_DEMOD_STATUS_NO_LOCK;

#if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    if(TRUE == EXTERN_ISDBT_Lock(COFDM_FEC_LOCK))
        eStatus = E_API_DEMOD_STATUS_LOCKED;
#elif(FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    if(TRUE == INTERN_ISDBT_Lock(COFDM_FEC_LOCK))
        eStatus = E_API_DEMOD_STATUS_LOCKED;
#endif
    return eStatus;
}


#if( (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)   \
    )
    #define DEMOD_ISDBT_DETECT_LOCK_TIMEOUT__NORMAL      2000
    #define DEMOD_ISDBT_DETECT_LOCK_TIMEOUT__NO_ICFO     600
#else
    #define DEMOD_ISDBT_DETECT_LOCK_TIMEOUT__NORMAL      2000
    #define DEMOD_ISDBT_DETECT_LOCK_TIMEOUT__NO_ICFO     600
#endif

EnuApiDemodLockStatus msAPI_Demod_ISDBT_DetectLockTask(void)
{
    EnuApiDemodLockStatus eStatus = E_API_DEMOD_STATUS_NO_LOCK;

    U32 u32Timeout = DEMOD_ISDBT_DETECT_LOCK_TIMEOUT__NORMAL;

#if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    if(EXTERN_ISDBT_Lock(COFDM_FEC_LOCK) == TRUE)
    {
        eStatus = E_API_DEMOD_STATUS_LOCKED;
        return eStatus;
    }
#elif(FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    if(INTERN_ISDBT_Lock(COFDM_FEC_LOCK) == TRUE)
    {
        eStatus = E_API_DEMOD_STATUS_LOCKED;
        return eStatus;
    }
#endif

#if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    if(EXTERN_ISDBT_Lock(COFDM_ICFO_CH_EXIST_FLAG) == FALSE)
    {
        u32Timeout = DEMOD_ISDBT_DETECT_LOCK_TIMEOUT__NO_ICFO;
    }
#elif(FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    if (INTERN_ISDBT_Lock(COFDM_ICFO_CH_EXIST_FLAG) == FALSE)
        u32Timeout = DEMOD_ISDBT_DETECT_LOCK_TIMEOUT__NO_ICFO;
#else
    u32Timeout = DEMOD_ISDBT_DETECT_LOCK_TIMEOUT__NO_ICFO;
#endif

    if( msAPI_Demod_Get_DetectLockUseTime() > u32Timeout )
    {
        eStatus = E_API_DEMOD_STATUS_NO_LOCK;
    }
    else
    {
        eStatus = E_API_DEMOD_STATUS_CHECKING;
    }

    return eStatus;
}

void devCOFDM_ISDBT_SetFrequency(DWORD dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID)
{
    // Save tuner freq for debug
    g_Debug_u32LastTunerFreq = dwFrequency;

#if (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
  #if (!BLOADER)
    EN_OSD_COUNTRY_SETTING  en_osd_country;
  #endif //(!BLOADER)
    BOOLEAN                 b_pal_bg;
#endif
    UNUSED(u8PlpID);
    UNUSED(eHpLp);

    //printf("====dwFrequency = %lu \n", dwFrequency/1000);
    //printf("====eBandWidth = %bx\n", eBandWidth);

#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
  #if (ENABLE_BOOTTIME==DISABLE)
    if (g_bAutobuildDebug == TRUE)
  #endif
    {
        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
        printf("[boot time]COFDM set RF = %ld, freq=%d\n", gU32TmpTime, dwFrequency);
    }
#endif

#if ( (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)        \
    ||(FRONTEND_TUNER_TYPE == LG_G230D_TUNER)        \
    ||(FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER) \
    ||(FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
    ||(FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)   \
    ||(FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)   \
    ||(FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)   \
    ||(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)  \
    ||(FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)\
    ||(FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)  \
    ||(FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)  \
    ||(FRONTEND_TUNER_TYPE == SILAB_2151_TUNER) \
    ||(FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)\
    ||(FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
    )

    dwFrequency = dwFrequency;

  #if (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    devTuner_Std_set(E_TUNER_DTV_ISDB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
  #endif
#endif

    devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), eBandWidth);

    printf("\e[31;1m ISDB Frep = %u \33[m \n", dwFrequency);

#if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    MsOS_DelayTask(10); //waiting for tuner write

  #if ENABLE_CI
    if ( msAPI_Tuner_IsParallelMode())
        EXTERN_ISDBT_Config(eBandWidth, false, false,E_RF_CH_LP==eHpLp ? TRUE : FALSE);
    else
  #endif
    {
        // default parallel mode.
      #if 1
        EXTERN_ISDBT_Config(eBandWidth, !TS_PARALLEL_ISDBT_OUTPUT, false, E_RF_CH_LP==eHpLp ? TRUE : FALSE);
      #else
        MSB1400_Config(eBandWidth, false, false,E_RF_CH_LP==eHpLp ? TRUE : FALSE);
      #endif
    }

    EXTERN_ISDBT_Active(ENABLE);

#elif ((FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD))
    MsOS_DelayTask(10); //waiting for tuner write

    //printf("msb1210 config\n");

  #if (!BLOADER)
    en_osd_country = (EN_OSD_COUNTRY_SETTING) msAPI_CM_GetCountry();

    if ( (en_osd_country == OSD_COUNTRY_FINLAND)
       ||(en_osd_country == OSD_COUNTRY_SWEDEN)
       ||(en_osd_country == OSD_COUNTRY_DENMARK)
       ||(en_osd_country == OSD_COUNTRY_NORWAY) )
    {
        b_pal_bg = true;
    }
    else
    {
        b_pal_bg = false;
    }
  #else //temp for bootloader
    b_pal_bg = false;
  #endif

    INTERN_ISDBT_Config(eBandWidth, !TS_PARALLEL_ISDBT_OUTPUT, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE); // << ken 2009.06.29 serial
    INTERN_ISDBT_Active(ENABLE);

#endif
}

void devCOFDM_ISDBT_SwitchTransportSteamInferface(TS_INTERFACE interface)
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
#if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    EXTERN_ISDBT_Serial_Control(bEnable);
#elif(FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    INTERN_ISDBT_Serial_Control(bEnable);
    INTERN_ISDBT_PAD_TS1_Enable(~bEnable);
#endif

}

BYTE devCOFDM_ISDBT_GetSignalToNoiseRatio(void)
{
#if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    return (BYTE)EXTERN_ISDBT_GetSNR();
#elif (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    return (BYTE)INTERN_ISDBT_GetSNR();
#endif
}

FUNCTION_RESULT devCOFDM_ISDBT_GetSignalStrength(WORD *strength)
{
#if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    return EXTERN_ISDBT_GetSignalStrength(strength);
#elif (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    return INTERN_ISDBT_GetSignalStrength(strength);
#else
    *strength=*strength;
    return E_RESULT_FAILURE;
#endif
}

FUNCTION_RESULT devCOFDM_ISDBT_GetSignalQuality(WORD *quality)
{
#if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    return  EXTERN_ISDBT_GetSignalQuality(quality);
#elif (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    return INTERN_ISDBT_GetSignalQuality(quality);
#else
    *quality = *quality;
    return E_RESULT_FAILURE;
#endif
}

#endif

