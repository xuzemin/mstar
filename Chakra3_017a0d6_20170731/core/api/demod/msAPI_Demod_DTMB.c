
#if(ENABLE_DEMOD_DTMB)
#include "MApp_GlobalSettingSt.h"
#include "msAPI_DTVSystem.h"
#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

BOOL msAPI_Demod_DTMB_Init(void)
{
    //devCOFDM_Init();
  #if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    INTERN_DTMB_Power_On_Initialization();
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);

  #elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    EXTERN_DTMB_Power_On_Initialization();
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);

  #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)      \
        ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    EXTERN_DTMB_Power_On_Initialization();
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X)
    ATBMInit();

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();

    ATBMInit_DTMB_Mode();

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();

    ATBMPowerOnInit();
    ATBMSet_DTMB();

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();

    ATBMPowerOnInit();
    ATBMSetDTMBMode();

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();

    ATBMPowerOnInit();
    ATBMSetDTMBMode();

  #endif
    devDigitalTuner_Init();
    return TRUE;
}

void msAPI_Demod_DTMB_Set_Power(BOOL bTurnOn)
{
    //devCOFDM_ControlPowerOnOff(bTurnOn);
#if (  (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)           \
    || (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)   \
    || (FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)    \
    )
    {
        if (bTurnOn == ENABLE) // DTV mode
        {
            EXT_RF_AGC_OFF();
        }
        else
        {
            EXT_RF_AGC_ON();
        }
    }
#endif

#if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    INTERN_DTMB_Power_ON_OFF(bTurnOn);
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);

#elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    EXTERN_DTMB_Power_ON_OFF(bTurnOn);
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);

#elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
      ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    EXTERN_DTMB_Power_ON_OFF(bTurnOn);

#elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X)
    printf("\n !!! %s, %d TO DO \n",__FILE__, __LINE__);
#elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X)
    if(bTurnOn)
        ATBM_Standby_WakeUp();
    else
        ATBM_Standby();
#elif(FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X)
    bTurnOn = bTurnOn;
#elif(FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X)
    if(bTurnOn)
        ATBMStandbyWakeUp();
    else
        ATBMStandby();
#elif(FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X)
    if(bTurnOn)
        ATBMStandbyWakeUp();
    else
        ATBMStandby();
#endif

}

void msAPI_Demod_DTMB_Exit(void)
{
  #if(FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X) // Euler/Emerald
    //do nothing

  #elif( FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD ) // Nasa

    MDrv_DMD_DTMB_Exit();

  #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
        ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) ) // Maya
    //do nothing

  #else

    //MDrv_DMD_DTMB_Exit();
    //INTERN_DTMB_Exit();
  #endif
}


BOOLEAN devCOFDM_DTMB_GetLockStatus(COFDM_LOCK_STATUS eStatus)
{
#if(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    return INTERN_DTMB_Lock(eStatus);

#elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    return EXTERN_DTMB_Lock(eStatus);

#elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
      ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    return EXTERN_DTMB_Lock(eStatus);

#elif (  FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X   \
      )
    eStatus=eStatus;
    return ATBMLockedFlag();

#else
    UNUSED(eStatus);
    return FALSE;
#endif
}

EnuApiDemodLockStatus msAPI_Demod_DTMB_Get_LockStatus(void)
{
    if( TRUE == devCOFDM_DTMB_GetLockStatus(COFDM_FEC_LOCK) )
    {
        return E_API_DEMOD_STATUS_LOCKED;
    }

    return E_API_DEMOD_STATUS_NO_LOCK;
}

#if ( (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)      \
    ||(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)      \
    ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)       \
    ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    #define DEMOD_DTMB_DETECT_LOCK_TIMEOUT__NORMAL      5000
    #define DEMOD_DTMB_DETECT_LOCK_TIMEOUT__NO_PN_LOCK  1200
#else //
    #define DEMOD_DTMB_DETECT_LOCK_TIMEOUT__NORMAL      5000
    #define DEMOD_DTMB_DETECT_LOCK_TIMEOUT__NO_PN_LOCK  600
#endif

EnuApiDemodLockStatus msAPI_Demod_DTMB_DetectLockTask(void)
{
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    U32 u32Timeout = DEMOD_DTMB_DETECT_LOCK_TIMEOUT__NORMAL;


    if( devCOFDM_DTMB_GetLockStatus(COFDM_FEC_LOCK) == TRUE )
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_LOCKED;
        return eDemodLockStatus;
    }

#if( (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X)||(FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X)||(FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_888X) )
    if ( FALSE == devCOFDM_DTMB_GetLockStatus(COFDM_TPS_LOCK) )
#else
    if ( FALSE == devCOFDM_DTMB_GetLockStatus(COFDM_PSYNC_LOCK) ) // COFDM_PSYNC_LOCK
#endif
    { //Speed up
        u32Timeout = DEMOD_DTMB_DETECT_LOCK_TIMEOUT__NO_PN_LOCK;
    }

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

void devCOFDM_DTMB_SetFrequency(DWORD dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID)
{
    // Save tuner freq for debug
    g_Debug_u32LastTunerFreq = dwFrequency;

#if ( (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)         \
    ||(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)         \
    ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)          \
    ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
  #if (!BLOADER)
    EN_OSD_COUNTRY_SETTING            en_osd_country;
  #endif //(!BLOADER)
    BOOLEAN                            b_pal_bg;
#endif

    UNUSED(u8PlpID);
    UNUSED(eHpLp);

#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
  #if (ENABLE_BOOTTIME==DISABLE)
    if (g_bAutobuildDebug == TRUE)
  #endif
    {
        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
        printf("[boot time]COFDM set RF = %ld, freq=%d\n", gU32TmpTime, dwFrequency);
    }
#endif

#if((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)        \
    ||(FRONTEND_TUNER_TYPE == LG_G230D_TUNER)        \
    || (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER) \
    || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
    || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)   \
    || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)   \
    || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)   \
    || (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)  \
    || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)\
    || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)  \
    || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)  \
    || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER) \
    || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)\
    || (FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
    )
    dwFrequency = dwFrequency;


  #if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);

  #elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);

  #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
        ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X )
    devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
  #endif


#endif
    //printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));
    devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), eBandWidth);
    //printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));
//printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));


    #if(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
        MsOS_DelayTask(10); //waiting for tuner write

        //printf("msb1210 config\n");

        #if (!BLOADER)
        en_osd_country = (EN_OSD_COUNTRY_SETTING) msAPI_CM_GetCountry();

        if ( (en_osd_country == OSD_COUNTRY_FINLAND)
          || (en_osd_country == OSD_COUNTRY_SWEDEN)
          || (en_osd_country == OSD_COUNTRY_DENMARK)
          || (en_osd_country == OSD_COUNTRY_NORWAY) )
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
        INTERN_DTMB_Config(eBandWidth, !TS_PARALLEL_DTMB_OUTPUT, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE); // << ken 2009.06.29 serial
        INTERN_DTMB_Active(ENABLE);
    #elif ((FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD))
        MsOS_DelayTask(10); //waiting for tuner write

        //printf("msb1210 config\n");

      #if (!BLOADER)
        en_osd_country = (EN_OSD_COUNTRY_SETTING) msAPI_CM_GetCountry();

        if ( (en_osd_country == OSD_COUNTRY_FINLAND)
          || (en_osd_country == OSD_COUNTRY_SWEDEN)
          || (en_osd_country == OSD_COUNTRY_DENMARK)
          || (en_osd_country == OSD_COUNTRY_NORWAY) )
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
        EXTERN_DTMB_Config(eBandWidth, !TS_PARALLEL_OUTPUT, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE); // << ken 2009.06.29 serial
        EXTERN_DTMB_Active(ENABLE);

    #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
          ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
        MsOS_DelayTask(10); //waiting for tuner write

        //printf("msb1210 config\n");

      #if (!BLOADER)
        en_osd_country = (EN_OSD_COUNTRY_SETTING) msAPI_CM_GetCountry();

        if ( (en_osd_country == OSD_COUNTRY_FINLAND)
          || (en_osd_country == OSD_COUNTRY_SWEDEN)
          || (en_osd_country == OSD_COUNTRY_DENMARK)
          || (en_osd_country == OSD_COUNTRY_NORWAY) )
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
        EXTERN_DTMB_Config(eBandWidth, !TS_PARALLEL_DTMB_OUTPUT, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE); // << ken 2009.06.29 serial
        EXTERN_DTMB_Active(ENABLE);
    #endif

}

FUNCTION_RESULT devCOFDM_DTMB_GetSignalQuality(WORD *quality)
{
//printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
#if (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    return EXTERN_DTMB_GetSignalQuality(quality);

#elif (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    return INTERN_DTMB_GetSignalQuality(quality);

#elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
      ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    return EXTERN_DTMB_GetSignalQuality(quality);

#elif (  FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X   \
      )
    *quality = ATBMSignalQuality();
    return E_RESULT_SUCCESS;

#else
    *quality = *quality; //Thomas 20150714 to do
    return E_RESULT_FAILURE;

#endif
}

BYTE devCOFDM_DTMB_GetSignalToNoiseRatio(void)
{

#if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
    return (BYTE)INTERN_DTMB_GetSNR();

#elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
    return (BYTE)EXTERN_DTMB_GetSNR();

#elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
      ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
    return (BYTE)EXTERN_DTMB_GetSNR();

#elif (  FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X   \
      || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X   \
      )
    return (BYTE)ATBMSignalNoiseRatio();

#else
    return 1;   //Thomas 20150714 to do

#endif

}

void devCOFDM_DTMB_SwitchTransportSteamInferface(TS_INTERFACE interface)
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

#if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    INTERN_DTMB_Serial_Control(bEnable);
    INTERN_DTMB_PAD_TS1_Enable(~bEnable);

#elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    EXTERN_DTMB_Serial_Control(bEnable);
    EXTERN_DTMB_PAD_TS1_Enable(~bEnable);

#elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
      ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    EXTERN_DTMB_Serial_Control(bEnable);
    EXTERN_DTMB_PAD_TS1_Enable(~bEnable);

#elif (  (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X)     \
      || (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X)     \
      || (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X)     \
      )
    {
        struct MPEG_TS_mode_t ts_mode;

        ts_mode.output_edge = TS_OUTPUT_FALLING_EDGE;
        ts_mode.SPI_clock_constant_output = TS_CLOCK_CONST_OUTPUT;
        if(bEnable)
        {
            //printf("set to serial mode\n");
            ts_mode.TS_Transfer_Type = TS_SERIAL_MODE;
        }
        else
        {
            //printf("set to parallel mode\n");
            ts_mode.TS_Transfer_Type = TS_PARALLEL_MODE;
        #if( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 )
            MDrv_WriteByte(0x101558,0x06);  //add patch here to change TS mode to parallel
        #endif
        }
        ATBMSetTSMode(ts_mode);
    }
#endif

}

FUNCTION_RESULT devCOFDM_DTMB_GetSignalStrength(WORD *strength)
{
    //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
    #if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
      #if DEMOD_DTMB_USE_UTOPIA
        #if ( (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)  \
            ||(FRONTEND_TUNER_TYPE == MxL_661SI_TUNER) )
            {
                float* f_strength = NULL;
                mdev_GetSignalStrength(f_strength);
                if(*f_strength > -35.0)
                    *strength = 100.0;
                else if (*f_strength > -100.0)
                    *strength = (U16)(*f_strength + 100.0);
                else
                    *strength = 0.0;
                return E_RESULT_SUCCESS;
             }
            #else
                return INTERN_DTMB_GetSignalStrength(strength);
            #endif
        #else
                return INTERN_DTMB_GetSignalStrength(strength);
        #endif

    #elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
        return EXTERN_DTMB_GetSignalStrength(strength);

    #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
          ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
        //return EXTERN_DTMB_GetSignalStrength(strength);
      #if(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER)
        {
            tmUnitSelect_t    sysUnit= 0;
            UInt32 u32RFLevelDbm=0;
            tmsysOM3912GetSignalStrength(sysUnit, &u32RFLevelDbm);
            *strength = (U16)u32RFLevelDbm;
            //devCOFDM_RecalculateSignalStrengthForNordig(strength);
            //printf(">>NUTUNE_FK1602_TUNERGetSignalStrength =%d\n",*strength);
            return E_RESULT_SUCCESS;
        }
      #else
        return EXTERN_DTMB_GetSignalStrength(strength);
      #endif

    #elif (  FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X   \
              || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X   \
              || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X   \
            )
            *strength=ATBMSignalStrength();
            return E_RESULT_SUCCESS;

    #elif (  FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X   \
            || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X   \
            )
            *strength=ATBMSignalStrength_reference();
            return E_RESULT_SUCCESS;

    #else
        *strength=*strength;
        return E_RESULT_FAILURE;
    #endif

}
#endif

