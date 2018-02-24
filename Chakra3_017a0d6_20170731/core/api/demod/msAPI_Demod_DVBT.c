
#if(ENABLE_DEMOD_DVBT)
#include "drvSYS.h"
#include "MApp_Scan.h"
#if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
#include "msb124x.h"
extern MAPI_BOOL MSB124X_Lock(COFDM_LOCK_STATUS eStatus);
extern EN_FRONTEND_SIGNAL_CONDITION DTV_GetSNR(void);
extern MAPI_BOOL DTV_SetFrequency(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth, MAPI_BOOL bPalBG, MAPI_BOOL bLPsel);
#endif

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

BOOL msAPI_Demod_DVBT_Init(void)
{
    //devCOFDM_Init();
    #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    //printf("%s,%d\n",__FILE__,__LINE__);
    //Connect(E_DEVICE_DEMOD_DVB_T);
    Demod_MSB124X_Connect(E_DEVICE_DEMOD_DVB_T);

    DTV_Serial_Control(!TS_PARALLEL_DVBT_OUTPUT);
    Power_On_Initialization();
    MDrv_SYS_SetPadMux(E_TS0_PAD_SET, E_SERIAL_IN);

    #else //   EMBEDDED_DVBT_DEMOD
      #if DEMOD_DVBT_USE_UTOPIA
        {
            DMD_DVBT_InitData sDMD_DVBT_InitData;
            static DMD_SQI_CN_NORDIGP1 sSqiCnNordigP1[]=D_DMD_SQI_CN_NORDIGP1;
            static MS_U8 u8DMD_DVBT_DSPRegInitExt[]=D_DMD_DVBT_DSPRegInitExt;
            static MS_U8 u8DMD_DVBT_InitExt[]=D_DMD_DVBT_InitExt;

            sDMD_DVBT_InitData.u8SarChannel = D_DMD_SAR_CHANNEL; // 0xFF means un-connected

        #if 1 // No sSSITableRfagc exist
            sDMD_DVBT_InitData.pTuner_RfagcSsi = NULL;
            sDMD_DVBT_InitData.u16Tuner_RfagcSsi_Size = 0;
        #else
            //static DMD_RFAGC_SSI sSSITableRfagc[]=D_DMD_SSI_TABLE_RFAGC;
            DMD_RFAGC_SSI *sSSITableRfagc=NULL;
            sDMD_DVBT_InitData.pTuner_RfagcSsi = sSSITableRfagc;
            sDMD_DVBT_InitData.u16Tuner_RfagcSsi_Size = sizeof(sSSITableRfagc)/sizeof(DMD_RFAGC_SSI);
        #endif

        #if 1 // No sSSITableIfagc exist
            sDMD_DVBT_InitData.pTuner_IfagcSsi_LoRef = NULL;
            sDMD_DVBT_InitData.u16Tuner_IfagcSsi_LoRef_Size = 0;
            sDMD_DVBT_InitData.pTuner_IfagcSsi_HiRef = NULL;
            sDMD_DVBT_InitData.u16Tuner_IfagcSsi_HiRef_Size = 0;
        #else
            //static DMD_IFAGC_SSI sSSITableIfagc[]=D_DMD_SSI_TABLE_IFAGC;
            DMD_IFAGC_SSI *sSSITableIfagc=NULL;
            sDMD_DVBT_InitData.pTuner_IfagcSsi_LoRef = sSSITableIfagc;
            sDMD_DVBT_InitData.u16Tuner_IfagcSsi_LoRef_Size = sizeof(sSSITableIfagc)/sizeof(DMD_IFAGC_SSI);
            sDMD_DVBT_InitData.pTuner_IfagcSsi_HiRef = sSSITableIfagc;
            sDMD_DVBT_InitData.u16Tuner_IfagcSsi_HiRef_Size = sizeof(sSSITableIfagc)/sizeof(DMD_IFAGC_SSI);
        #endif

        #if 1 // No sSSITableIfagcErrLo exist
            sDMD_DVBT_InitData.pTuner_IfagcErr_LoRef = NULL;
            sDMD_DVBT_InitData.u16Tuner_IfagcErr_LoRef_Size = 0;
        #else
            //static DMD_IFAGC_ERR sSSITableIfagcErrLo[]=D_DMD_SSI_TABLE_IFAGC_ERR_LO;
            DMD_IFAGC_ERR *sSSITableIfagcErrLo=NULL;
            sDMD_DVBT_InitData.pTuner_IfagcErr_LoRef = sSSITableIfagcErrLo;
            sDMD_DVBT_InitData.u16Tuner_IfagcErr_LoRef_Size = sizeof(sSSITableIfagcErrLo)/sizeof(DMD_IFAGC_ERR);
        #endif

        #if 1 // No sSSITableIfagcErrHi exist
            sDMD_DVBT_InitData.pTuner_IfagcErr_HiRef = NULL;
            sDMD_DVBT_InitData.u16Tuner_IfagcErr_HiRef_Size = 0;
        #else
            //static DMD_IFAGC_ERR sSSITableIfagcErrHi[]=D_DMD_SSI_TABLE_IFAGC_ERR_HI;
            DMD_IFAGC_ERR *sSSITableIfagcErrHi=NULL;
            sDMD_DVBT_InitData.pTuner_IfagcErr_HiRef = sSSITableIfagcErrHi;
            sDMD_DVBT_InitData.u16Tuner_IfagcErr_HiRef_Size = sizeof(sSSITableIfagcErrHi)/sizeof(DMD_IFAGC_ERR);
        #endif

            sDMD_DVBT_InitData.pSqiCnNordigP1 = sSqiCnNordigP1;
            sDMD_DVBT_InitData.u16SqiCnNordigP1_Size = sizeof(sSqiCnNordigP1) / sizeof(DMD_SQI_CN_NORDIGP1);
            sDMD_DVBT_InitData.u8DMD_DVBT_DSPRegInitExt = u8DMD_DVBT_DSPRegInitExt;
            sDMD_DVBT_InitData.u8DMD_DVBT_DSPRegInitSize = (sizeof(u8DMD_DVBT_DSPRegInitExt)-2)/4;
            sDMD_DVBT_InitData.u8DMD_DVBT_InitExt = u8DMD_DVBT_InitExt;
            MDrv_DMD_DVBT_Init(&sDMD_DVBT_InitData, sizeof(sDMD_DVBT_InitData)); // _UTOPIA
        }
      #else
        //printf("%s,%d\n",__FILE__,__LINE__);
        INTERN_DVBT_Power_On_Initialization();
        //printf("%s,%d\n",__FILE__,__LINE__);
      #endif
    #endif

    devDigitalTuner_Init();

    return TRUE;
}

void msAPI_Demod_DVBT_Set_Power(BOOL bTurnOn)
{
//    devCOFDM_ControlPowerOnOff(bTurnOn);
#if (  (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)           \
    || (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)   \
    || (FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)    \
    )
    {
        if (bTurnOn == ENABLE) // DTV mode
        {
        #if ENABLE_DVB_T2
            if (DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
            {
                EXT_RF_AGC_OFF();
            }
        #endif
            EXT_RF_AGC_ON();
        }
        else
        {
            EXT_RF_AGC_ON();
        }
    }
#endif

    #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
        bTurnOn = bTurnOn;
    #else //1 EMBEDDED_DVBT_DEMOD
      #if DEMOD_DVBT_USE_UTOPIA
      #else
        INTERN_DVBT_Power_ON_OFF(bTurnOn);
      #endif
    #endif


}

void msAPI_Demod_DVBT_Exit(void)
{
 #if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)

  #if DEMOD_DVBT_USE_UTOPIA
    MDrv_DMD_DVBT_Exit();
  #else
    INTERN_DVBT_Exit();
  #endif

 #elif( FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT )
    // Do nothing
    //Disconnect();
 #else

 #endif
}

BOOLEAN msAPI_Demod_DVBT_Get_PostViterbiBer(float *ber)
{
    *ber = 0;
#if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB1200_DEMOD)
    return MSB1200_GetPostViterbiBer(ber);
#elif (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB1210_DEMOD)
    return MSB1210_GetPostViterbiBer(ber);
#elif (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    return MSB124X_DTV_GetPostBER(ber);

#elif (FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)

  #if DEMOD_DVBT_USE_UTOPIA
    return MDrv_DMD_DVBT_GetPostViterbiBer(ber);
  #else
    return INTERN_DVBT_GetPostViterbiBer(ber);
  #endif

    return FALSE;

#endif
}
BOOLEAN devCOFDM_DVBT_GetLockStatus(COFDM_LOCK_STATUS eStatus)
{
#if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
    #if DEMOD_DVBT_USE_UTOPIA
    DMD_LOCK_STATUS eLockStatus;
    MDrv_DMD_DVBT_GetLock(E_DMD_DMD_DVBT_GETLOCK, &eLockStatus);
    switch (eStatus) // _UTOPIA
    {
        case COFDM_FEC_LOCK:
            MDrv_DMD_DVBT_GetLock(E_DMD_COFDM_FEC_LOCK, &eLockStatus);
            return (eLockStatus==E_DMD_LOCK);
            break;
        case COFDM_PSYNC_LOCK:
            MDrv_DMD_DVBT_GetLock(E_DMD_COFDM_PSYNC_LOCK, &eLockStatus);
            return (eLockStatus==E_DMD_LOCK);
            break;
        case COFDM_TPS_LOCK:
            MDrv_DMD_DVBT_GetLock(E_DMD_COFDM_TPS_EVER_LOCK, &eLockStatus);
            //printf("TPS ever lock %d\n",eLockStatus);
            return (eLockStatus==E_DMD_LOCK);
            break;
        case COFDM_DCR_LOCK:
            MDrv_DMD_DVBT_GetLock(E_DMD_COFDM_DCR_LOCK, &eLockStatus);
            return (eLockStatus==E_DMD_LOCK);
            break;
        case COFDM_AGC_LOCK:
            MDrv_DMD_DVBT_GetLock(E_DMD_COFDM_AGC_LOCK, &eLockStatus);
            return (eLockStatus==E_DMD_LOCK);
            break;
        case COFDM_MODE_DET:
            MDrv_DMD_DVBT_GetLock(E_DMD_COFDM_MODE_DET, &eLockStatus);
            return (eLockStatus==E_DMD_LOCK);
            break;
        default:
            printf("%s error %d\n",__func__,eStatus);
            break;
    }
    // MDrv_DMD_DVBT_GetLock(E_DMD_DMD_DVBT_GETLOCK, &eLockStatus);
    return FALSE;
    #else
    return INTERN_DVBT_Lock(eStatus);
    #endif
#elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    return  MSB124X_Lock(eStatus);
#else
    UNUSED(eStatus);
    return FALSE;
#endif
}


EnuApiDemodLockStatus msAPI_Demod_DVBT_Get_LockStatus(void)
{
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;

    if( TRUE == devCOFDM_DVBT_GetLockStatus(COFDM_FEC_LOCK) )
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_LOCKED;
    }

    return eDemodLockStatus;
}
#if( (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB1200_DEMOD)   \
   ||(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB1210_DEMOD)   \
    )
    #define DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NORMAL      6000
    #define DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NO_TPS_LOCK 2000

#elif( (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT) )
    #define DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NORMAL      4000
    #define DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NO_TPS_LOCK 1000

#elif( (FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD) )
    #define DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NORMAL      10000 // 10Sec
    #define DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NO_TPS_LOCK 1000

#else
    #define DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NORMAL      10000
    #define DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NO_TPS_LOCK 2000

#endif

EnuApiDemodLockStatus msAPI_Demod_DVBT_DetectLockTask(void)
{
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;
    U32 u32Timeout = DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NORMAL;

    //printf("[DVBT_Detect]");

    if( devCOFDM_DVBT_GetLockStatus(COFDM_FEC_LOCK) == TRUE )
    {
        eDemodLockStatus = E_API_DEMOD_STATUS_LOCKED;
        return eDemodLockStatus;
    }
#if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
    if( devCOFDM_DVBT_GetLockStatus(COFDM_TPS_LOCK) == FALSE ) // No TPS Locked
#elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    if( devCOFDM_DVBT_GetLockStatus((COFDM_LOCK_STATUS)COFDM_TPS_LOCK_123X) == FALSE ) // No TPS Locked
#endif
    {
        // Speed up
        u32Timeout = DEMOD_DVBT_DETECT_LOCK_TIMEOUT__NO_TPS_LOCK;
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

void devCOFDM_DVBT_SetFrequency(DWORD dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID)
{
    // Save tuner freq for debug
    g_Debug_u32LastTunerFreq = dwFrequency;

#if ( (FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)     \
    ||(FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)   \
    ||(FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)     \
    ||(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)     \
    ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)      \
    ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
  #if (!BLOADER)
    EN_OSD_COUNTRY_SETTING            en_osd_country;
  #endif //(!BLOADER)
    BOOLEAN                            b_pal_bg;
#endif

    UNUSED(u8PlpID);
    UNUSED(eHpLp);

#if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB1200_DEMOD)
    MSB1200_Active(DISABLE);

#endif


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
    || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)  \
    || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)  \
    || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)  \
    || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER) \
    || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)\
    || (FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
    )
    dwFrequency = dwFrequency;
    devTuner_Std_set(E_TUNER_DTV_DVB_T_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);

#endif

    //printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));
    devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), eBandWidth);
    //printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));
    //printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));

#if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
    MsOS_DelayTask(10); //waiting for tuner write

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

    MS_BOOL bTsFormatIsSerial = FALSE; // Internal demod TS format should always parallel~

  #if DEMOD_DVBT_USE_UTOPIA
    {
        MS_U32 u32IFFreq=36167;
        DMD_RF_CHANNEL_BANDWIDTH eDMDBandWidth=E_DMD_RF_CH_BAND_8MHz;
        switch(eBandWidth)
        {
            case E_RF_CH_BAND_6MHz:
                eDMDBandWidth=E_DMD_RF_CH_BAND_6MHz;
                u32IFFreq=D_DMD_IF_DVBT_6M;
                break;
            case E_RF_CH_BAND_7MHz:
                eDMDBandWidth=E_DMD_RF_CH_BAND_7MHz;
                u32IFFreq=D_DMD_IF_DVBT_7M;
                break;
            case E_RF_CH_BAND_8MHz:
                eDMDBandWidth=E_DMD_RF_CH_BAND_8MHz;
                u32IFFreq=D_DMD_IF_DVBT_8M;
                break;
            default:
                printf("\nWarning: Demod eBandWidth=%u is wrong!\n", eBandWidth);
                eDMDBandWidth=E_DMD_RF_CH_BAND_8MHz;
                u32IFFreq=D_DMD_IF_DVBT_8M;
                break;
        }

        //MDrv_DMD_DVBT_SetConfigHPLP(eDMDBandWidth, !TS_PARALLEL_OUTPUT, b_pal_bg, E_RF_CH_LP==eHpLp ? TRUE : FALSE);
        MDrv_DMD_DVBT_SetConfigHPLPSetIF(eDMDBandWidth, bTsFormatIsSerial, b_pal_bg, E_RF_CH_LP==eHpLp ? TRUE : FALSE, u32IFFreq, 24000, D_DMD_TUNER_IQSWAP);

        MDrv_DMD_DVBT_SetActive(ENABLE);
    }

  #else // DEMOD_DVBT_USE_UTOPIA

    INTERN_DVBT_Config(eBandWidth, bTsFormatIsSerial, b_pal_bg, E_RF_CH_LP==eHpLp ? TRUE : FALSE); // << ken 2009.06.29 serial

    INTERN_DVBT_Active(ENABLE);

  #endif // DEMOD_DVBT_USE_UTOPIA

#elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)

    DTV_SetFrequency((U32)(dwFrequency), eBandWidth, false, E_RF_CH_LP==eHpLp ? TRUE : FALSE);

#else

    "Unknown DVBT demod type!!"

#endif

}

FUNCTION_RESULT devCOFDM_DVBT_GetSignalQuality(WORD *quality)
{
#if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    *quality=DTV_GetSignalQuality();
    //printf("%s,%d, quality=%d\r\n",__FUNCTION__,__LINE__,*quality);
    return E_RESULT_SUCCESS;
#elif(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
 #if DEMOD_DVBT_USE_UTOPIA
    MS_BOOL bRet=FALSE;
    bRet=MDrv_DMD_DVBT_GetSignalQuality(quality);
    return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
 #else
    return INTERN_DVBT_GetSignalQuality(quality);
 #endif
#else
    *quality = *quality; //Thomas 20150714 to do
    return E_RESULT_FAILURE;

#endif

}

BYTE devCOFDM_DVBT_GetSignalToNoiseRatio(void)
{
#if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    return (BYTE)DTV_GetSNR();
#elif(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
  #if DEMOD_DVBT_USE_UTOPIA
    float fSNR=0.0f;
    MDrv_DMD_DVBT_GetSNR(&fSNR);
    if (fSNR<0.0f) fSNR=0.0f;
    if (fSNR>100.0f) fSNR=100.0f;
    return (char)fSNR;
  #else
    return (BYTE)INTERN_DVBT_GetSNR();
  #endif
#else
    return 1;   //Thomas 20150714 to do
#endif

}

void devCOFDM_DVBT_SwitchTransportSteamInferface(TS_INTERFACE interface)
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

#if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
  #if DEMOD_DVBT_USE_UTOPIA
    MDrv_DMD_DVBT_SetSerialControl(bEnable);
    MDrv_SYS_SetPadMux(E_TS0_PAD_SET, bEnable ? E_SERIAL_IN : E_PARALLEL_IN);
  #else
    INTERN_DVBT_Serial_Control(bEnable);
    INTERN_DVBT_PAD_TS1_Enable(~bEnable);
  #endif

#elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    DTV_Serial_Control(bEnable);
#endif

}

FUNCTION_RESULT devCOFDM_DVBT_GetSignalStrength(WORD *strength)
{
    #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
        *strength = DTV_GetSignalStrength();
        return E_RESULT_SUCCESS;
    #else //1 EMBEDDED_DVBT_DEMOD
        #if DEMOD_DVBT_USE_UTOPIA
            #if(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER || FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
            {
                tmUnitSelect_t    sysUnit= 0;
                UInt32 u32RFLevelDbm=0;
                tmsysOM3912GetSignalStrength(sysUnit, &u32RFLevelDbm);
                *strength = (U16)u32RFLevelDbm;
                devCOFDM_RecalculateSignalStrengthForNordig(strength);
                return E_RESULT_SUCCESS;
            }
            #elif((FRONTEND_TUNER_TYPE == SILAB_2158_TUNER) || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER))
            {
                mdev_ATV_GetSignalStrength_Si2158(strength);
                return E_RESULT_SUCCESS;
            }
            #elif( (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER)\
                || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)  \
                || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)    \
                || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)    \
                || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)     \
                || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)     \
                || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)    \
                || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER) \
                || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)   \
                || (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)   \
                )
            {
                float   rf_level_dbm = 0.0;
                MS_BOOL bRet = TRUE;
                bRet &= mdev_GetSignalStrength(&rf_level_dbm);
                bRet &= MDrv_DMD_DVBT_GetSignalStrengthWithRFPower(strength, rf_level_dbm);
                return (bRet == TRUE)?E_RESULT_SUCCESS:E_RESULT_FAILURE;
            }
            #elif (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)
            {
                float   rf_level_dbm = 0.0;
                MS_BOOL bRet = TRUE;
                MS_U16   tmp = 0;
                MS_U16   if_agc_gain = 0;

                S_RSSI_TABLE ssi_r840[]=
                {
                    {-82.0,0x7a72},
                    {-81.0,0x788a},
                    {-80.0,0x7700},
                    {-79.0,0x75b2},
                    {-78.0,0x74b0},
                    {-77.0,0x73b9},
                    {-76.0,0x72ea},
                    {-75.0,0x71fe},
                    {-74.0,0x7130},
                    {-73.0,0x707b},
                    {-72.0,0x6fba},
                    {-71.0,0x6f2b},
                    {-70.0,0x6e90},
                    {-69.0,0x6e04},
                    {-68.0,0x6d85},
                    {-67.0,0x6cfe},
                    {-66.0,0x6c80},
                    {-65.0,0x6bf1},
                    {-64.0,0x6b78},
                    {-63.0,0x6af1},
                    {-62.0,0x6a70},
                    {-61.0,0x69f0},
                    {-60.0,0x695a},
                    {-59.0,0x68a4},
                    {-58.0,0x67e3},
                    {-57.0,0x670f},
                    {-56.0,0x6630},
                    {-55.0,0x6530},
                    {-54.0,0x642c},
                    {-53.0,0x633d},
                    {-52.0,0x6273},
                    {-51.0,0x61a0},
                    {-00.0,0xFFFF},// add for table end
                };

              #if((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)||((CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)))
                tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x08*2);
                bRet &= devCOFDM_DVBT_WriteReg(0x2800 + 0x08*2, tmp|0x80);

                tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x13*2);
                bRet &= devCOFDM_DVBT_WriteReg(0x2800 + 0x13*2, (tmp&0xF0)|0x03);

                tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x14*2 + 1);
                if_agc_gain = tmp;
                tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x14*2);
                if_agc_gain = (if_agc_gain<<8)|tmp;

                tmp = devCOFDM_DVBT_ReadReg(0x2800 + 0x08*2);
                bRet &= devCOFDM_DVBT_WriteReg(0x2800 + 0x08*2, tmp&~(0x80));
              #else
                tmp = devCOFDM_DVBT_ReadReg(0x2700 + 0x02*2);
                bRet &= devCOFDM_DVBT_WriteReg(0x2700 + 0x02*2, tmp|0x80);

                tmp = devCOFDM_DVBT_ReadReg(0x2700 + 0x0b*2);
                bRet &= devCOFDM_DVBT_WriteReg(0x2700 + 0x0b*2, (tmp&0xF0)|0x03);

                tmp = devCOFDM_DVBT_ReadReg(0x2700 + 0x0c*2 + 1);
                if_agc_gain = tmp;
                tmp = devCOFDM_DVBT_ReadReg(0x2700 + 0x0c*2);
                if_agc_gain = (if_agc_gain<<8)|tmp;

                tmp = devCOFDM_DVBT_ReadReg(0x2700 + 0x02*2);
                bRet &= devCOFDM_DVBT_WriteReg(0x2700 + 0x02*2, tmp&~(0x80));
              #endif

                bRet &= mdev_GetSignalStrength(ssi_r840, if_agc_gain, &rf_level_dbm);
                bRet &= MDrv_DMD_DVBT_GetSignalStrengthWithRFPower(strength, rf_level_dbm);

                return (bRet == TRUE)?E_RESULT_SUCCESS:E_RESULT_FAILURE;
            }
            #else
            {
                MS_BOOL bRet=FALSE;
                bRet=MDrv_DMD_DVBT_GetSignalStrengthWithRFPower(strength, 200.0f);
                return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
            }
            #endif
        #else
            #if(FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
            {
                mdev_ATV_GetSignalStrength_Si2158(strength);
                return E_RESULT_SUCCESS;
            }
            #else
                return INTERN_DVBT_GetSignalStrength(strength);
            #endif
        #endif
    #endif
    *strength=*strength;
    return E_RESULT_FAILURE;
}

#endif

