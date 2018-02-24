
#if(ENABLE_DEMOD_ATSC)


#include "Utl.h"

#include "drvGlobal.h"
#include "msAPI_Demod_ATSC.h"
#include "msAPI_Timer.h"
#if (NEW_DEMOD_SCAN)
#include "msAPI_Tuner_ATSC.h"
#endif

#if (FRONTEND_DEMOD_ATSC_TYPE==LG_3303_DEMODE)
    #include "LGDT3303API.c"
#elif (FRONTEND_DEMOD_ATSC_TYPE==SAMSUNG_S5H1409_DEMODE)
    #include "SamsungDTVS205.c"
#elif (FRONTEND_DEMOD_ATSC_TYPE==SAMSUNG_S5H1410_DEMODE)
    #include "S5H1410_Ver1.2.C"
#elif (FRONTEND_DEMOD_ATSC_TYPE==MSTAR_MSB1501_DEMODE)
    #include "MSB1501.c"
#elif (FRONTEND_DEMOD_ATSC_TYPE==EMBEDDED_ATSC_DEMOD)

  #if (DEMOD_ATSC_USE_UTOPIA)
    #include "drvDMD_common.h"
    #include "drvDMD_ATSC.h"
  #else
    #include "INTERN_ATSC.c"
  #endif

#else
    #error "ATSC DEMOD not support"
#endif

//===========================================================
#ifndef ENABLE_DTV_NOSIGNAL_THRESHOLD
#define ENABLE_DTV_NOSIGNAL_THRESHOLD      DISABLE
#endif

#if(FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)

#define DEMOD_AFEC_LOCK_COUNT  3000

#if (ENABLE_DTV_NOSIGNAL_THRESHOLD)
#define DEMOD_VSB_NOSIGNAL_THRESHOLD  38
#define DEMOD_64QAM_NOSIGNAL_THRESHOLD  51
#define DEMOD_256QAM_NOSIGNAL_THRESHOLD  66
#endif

static U32 g_u32AFECCount = 0;
#if (DEMOD_ATSC_USE_UTOPIA)
static MS_BOOL s_bDmdInit = FALSE;
static U8 u8DMD_ATSC_InitExt[]={1}; // RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning
#endif

#endif


#define DEBUG_DEMOD_ATSC(y)     //y

#if (NEW_DEMOD_SCAN)
MS_U8 u8RetQamNoChannelDetect = 0;  // 1;maybe have channel  // 2; no signal.
static MS_U8 u8NoChannelDetectFlag;
#endif
//===========================================================

//*************************************************************************
//Function name:    msAPI_Demodulator_Exit_ATSC
//Description:      This function will exit Demode
//  [doxygen]
/// This function will init Demode
//*************************************************************************
void msAPI_Demod_ATSC_Exit(void)
{
    DEBUG_DEMOD_ATSC(printf("msAPI_Demod_ATSC_Exit()\n"););
#if (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
  #if (DEMOD_ATSC_USE_UTOPIA)
    MDrv_DMD_ATSC_Exit();
  #else
    INTERN_ATSC_Exit();
  #endif
#endif
}

//*************************************************************************
//Function name:    msAPI_Demodulator_Init
//Description:      This function will init Demode
//  [doxygen]
/// This function will init Demode
///@param enModulation \b IN  Demode type of Ts
///@param enSpectrumType \b IN  Demode Spectrum
///@return - init Demode status
//*************************************************************************

BOOLEAN msAPI_Demod_ATSC_Set_Mode(EN_DEMOD_ATSC_MODE enModulation, EN_DEMOD_ATSC_SPECTRUM_MODE enSpectrumType)
{
    DEBUG_DEMOD_ATSC(printf("msAPI_Demod_ATSC_Set_Mode(enModulation=%u, enSpectrumType=%u)\n", enModulation, enSpectrumType););

#if TS_THROUGH_LVDS
    return TRUE;
#endif

    //MDrv_Demodulator_Init();
    {
    #if (FRONTEND_DEMOD_ATSC_TYPE == LG_3303_DEMODE)

        U16 u16Result;

        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                    u16Result=LgdtVSBSetDecoder();
                    NEW_SCAN_API_DBG(printf("Demod init LG3303 VSB Mode! \r\n"););
                break;
            case DEMOD_ATSC_MODE_256QAM:
                    u16Result=LgdtQAM_SetDecoder(LGDT_QAM256,enSpectrumType);
                    NEW_SCAN_API_DBG(printf("Demod init LG3303 1st QAM256 Mode! \r\n"););
                break;
            case DEMOD_ATSC_MODE_64QAM:
                    u16Result=LgdtQAM_SetDecoder(LGDT_QAM64,enSpectrumType);
                    NEW_SCAN_API_DBG(printf("Demod init LG3303 1st QAM64 Mode! \r\n"););
                break;
        }

        if(u16Result!=LGDT_ERR_NO)
        {
            NEW_SCAN_API_DBG(printf("!! LgdtSetDecoder Fail \r\n"););
            return FALSE;
        }

        if(LgdtResetOff()!=LGDT_ERR_NO)
        {
            NEW_SCAN_API_DBG(printf("!! msAPI_Demodulator_Reset_ATSC Off Fail \r\n"););
            return FALSE;
        }

        return TRUE;

    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)

        BOOLEAN u8Result=FALSE;
        enSpectrumType=enSpectrumType;  //Clear Warrning

        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                if(SamsungS5H1409xVSBScanInit()==TRUE)
                    u8Result=SamsungS5H1409VsbMode();
                DEBUG_DEMOD_ATSC(printf("Demod init S5H1409 VSB Mode! \r\n"););
                break;

            case DEMOD_ATSC_MODE_256QAM:
                u8Result=SamsungS5H1409x256QamMode();
                DEBUG_DEMOD_ATSC(printf("Demod init S5H1409 256 QAM Mode! \r\n"););
                break;

            case DEMOD_ATSC_MODE_64QAM:
                u8Result=SamsungS5H1409x64QamMode();
                DEBUG_DEMOD_ATSC(printf("Demod init S5H1409 64 QAM Mode! \r\n"););
                break;
            case DEMOD_ATSC_MODE_NTSC:
            case DEMOD_ATSC_MODE_NUM:
            default:
                break;
        }

        if(u8Result==TRUE)
            u8Result=SamsungS5H1409_SoftReset();

        if(enModulation!=DEMOD_ATSC_MODE_8VSB)
        {
                SamsungS5H1409AMHUM_SetDriver();
            #if TS_PARALLEL_OUTPUT
                SamsungS5H1409_Interleave_Parallel_ModeSet();
            #else
                SamsungS5H1409_Interleave_Serial_ModeSet();
            #endif
                NEW_SCAN_API_DBG(printf("Demod init S5H1409 256/64 QAM AM HUM Mode! \r\n"););
        }

        if((u8Result==FALSE)&&(enModulation==DEMOD_ATSC_MODE_8VSB))
            SamsungS5H1409xVSBScanEnd();

        return u8Result;

    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
        BOOLEAN u8Result=FALSE;
        enSpectrumType=enSpectrumType;  //Clear Warrning
        u8Result=msAPI_Demodulator_Reset_ATSC();
        msAPI_Timer_Delayms(10);
        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                u8Result=MSB1501_VsbMode();
                NEW_SCAN_API_DBG(printf("Demod init MSB1501 VSB Mode! \r\n"););
                break;
            case DEMOD_ATSC_MODE_256QAM:
                u8Result=MSB1501_256QamMode();
                NEW_SCAN_API_DBG(printf("Demod init MSB1501 256 QAM Mode! \r\n"););
                break;
            case DEMOD_ATSC_MODE_64QAM:
                u8Result=MSB1501_64QamMode();
                NEW_SCAN_API_DBG(printf("Demod init MSB1501 64 QAM Mode! \r\n"););
                break;
            case DEMOD_ATSC_MODE_NTSC:
            case DEMOD_ATSC_MODE_NUM:
            default:
                break;
        }
        if(enModulation!=DEMOD_ATSC_MODE_8VSB)
        {
            #if TS_PARALLEL_OUTPUT
            #else
            #endif
                NEW_SCAN_API_DBG(printf("Demod init S5H1409 256/64 QAM AM HUM Mode! \r\n"););
        }
        return u8Result;

    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
        BOOLEAN u8Result=FALSE;
        enSpectrumType=enSpectrumType;  //Clear Warrning
        u8Result = msAPI_Demod_ATSC_Reset();

       #if (DEMOD_ATSC_USE_UTOPIA)
        //Unused
       #else
        msAPI_Timer_Delayms(10);
       #endif

        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                DEBUG_DEMOD_ATSC(printf("Demod Mod=8VSB\n"););
#if (NEW_DEMOD_SCAN)
                u8RetQamNoChannelDetect = 0;
                u8NoChannelDetectFlag=FALSE;
#endif

                #if (DEMOD_ATSC_USE_UTOPIA)
                u8Result=MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_ATSC_VSB, ENABLE);
                #else
                u8Result=INTERN_ATSC_VsbMode();
                #endif
                break;
            case DEMOD_ATSC_MODE_64QAM:
                DEBUG_DEMOD_ATSC(printf("Demod Mod=64QAM\n"););
#if (NEW_DEMOD_SCAN)
                u8RetQamNoChannelDetect = 0;
                u8NoChannelDetectFlag=FALSE;
#endif
                #if (DEMOD_ATSC_USE_UTOPIA)
                u8Result=MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_ATSC_64QAM, ENABLE);
                #else
                u8Result=INTERN_ATSC_64QamMode();
                #endif
                break;
            case DEMOD_ATSC_MODE_256QAM:
                DEBUG_DEMOD_ATSC(printf("Demod Mod=256QAM\n"););
#if (NEW_DEMOD_SCAN)
                u8RetQamNoChannelDetect = 0;
                u8NoChannelDetectFlag=FALSE;
#endif
                #if (DEMOD_ATSC_USE_UTOPIA)
                u8Result=MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_ATSC_256QAM, ENABLE);
                #else
                u8Result=INTERN_ATSC_256QamMode();
                #endif
                break;
            case DEMOD_ATSC_MODE_NTSC:
            case DEMOD_ATSC_MODE_NUM:
            default:
                break;
        }
#if 0
        if( enModulation != DEMOD_ATSC_MODE_8VSB )
        {
            #if TS_PARALLEL_OUTPUT
            #else
            #endif
        }
#endif
        return u8Result;

    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)

        BOOLEAN u8Result=FALSE;
        enSpectrumType=enSpectrumType;  //Clear Warrning

        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                u8Result|=Sec_1410xVsbMode();
                NEW_SCAN_API_DBG(printf("Demod init S5H1410 VSB Mode! \r\n"););
                break;

            case DEMOD_ATSC_MODE_256QAM:
                u8Result|=Sec_1410x256QamMode();
                NEW_SCAN_API_DBG(printf("Demod init S5H1410 256 QAM Mode! \r\n"););
                break;

            case DEMOD_ATSC_MODE_64QAM:
                u8Result|=Sec_1410x64QamMode();
                NEW_SCAN_API_DBG(printf("Demod init S5H1410 64 QAM Mode! \r\n"););
                break;
        }

        u8Result|=Sec_1410xSoftReset();

        if(enModulation!=DEMOD_ATSC_MODE_8VSB)
        {
            AMHUM_SetDriver();
            NEW_SCAN_API_DBG(printf("Demod init S5H1410 256/64 QAM AM HUM Mode! \r\n"););
        }

        return u8Result;
    #endif
    }
}

//*************************************************************************
//Function name:    msAPI_Demodulator_Reset
//Description:      This function will Reset Demode
//  [doxygen]
/// This function will Reset Demode
///@param NULL \b IN NULL
///@return - Reset Demode status
//*************************************************************************
BOOLEAN msAPI_Demod_ATSC_Reset(void)
{
    DEBUG_DEMOD_ATSC(printf("msAPI_Demod_ATSC_Reset()\n"););

#if TS_THROUGH_LVDS
    return TRUE;
#endif
#if (FRONTEND_DEMOD_ATSC_TYPE == LG_3303_DEMODE)
        if(LgdtResetOn()!=LGDT_ERR_NO)
        {
            NEW_SCAN_API_DBG(printf("!! msAPI_Demodulator_Reset_ATSC Fail \r\n"););
            return FALSE;
        }
        return TRUE;

#elif (FRONTEND_DEMOD_ATSC_TYPE==SAMSUNG_S5H1409_DEMODE)
        return TRUE;

#elif (FRONTEND_DEMOD_ATSC_TYPE==MSTAR_MSB1501_DEMODE)
        return MSB1501_SoftReset();

#elif (FRONTEND_DEMOD_ATSC_TYPE==EMBEDDED_ATSC_DEMOD)
    #if (DEMOD_ATSC_USE_UTOPIA)
        MDrv_DMD_ATSC_SetReset();
        return TRUE;
    #else
        return INTERN_ATSC_SoftReset();
    #endif
#elif (FRONTEND_DEMOD_ATSC_TYPE==SAMSUNG_S5H1410_DEMODE)

    return Sec_1410xSoftReset();

#else
    printf("\nError: Unsupport ATSC Demod!\n");

#endif

    return TRUE;
}

//*************************************************************************
//Function name:    msAPI_Demodulator_Get_Lock
//Description:      This function will get VSB FEC or QAM Main Lock status from Demode
//  [doxygen]
/// This function will get VSB or QAM's  lock status from Demode
///@param enModulation \b IN Demode type of TS
///@return - return Lock status
///         - TRUE : Lock
///         - FALSE: Unlock
//*************************************************************************
//BOOLEAN msAPI_Demodulator_Get_Lock_ATSC(EN_DEMOD_ATSC_MODE enModulation)
BOOLEAN msAPI_Demod_ATSC_Get_Lock(EN_DEMOD_ATSC_MODE enModulation)
{
#if (TS_THROUGH_LVDS || SFU_AUTO_TEST)
    return TRUE;
#endif

    //printf("msAPI_Demod_ATSC_Get_Lock(enModulation=%u)\n", enModulation);

#if (FRONTEND_DEMOD_ATSC_TYPE == LG_3303_DEMODE)

        U16 u16Result;
        if(enModulation==DEMOD_ATSC_MODE_8VSB)
            u16Result=LgdtVSBSignalCheck();
        else
            u16Result=LgdtQAMSignalCheck();

        NEW_SCAN_API_DBG(printf("Mode=%bd, Lock State=%d \r\n",(U8)enModulation,(U16)u16Result););
        if(u16Result!=LGDT_ERR_NO)
            return FALSE;
        else
            return TRUE;

#elif(FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
        BOOLEAN Result;

        if(enModulation==DEMOD_ATSC_MODE_8VSB)
        {
            Result=SamsungS5H1409xVsb_Sync_Lock();
        }
        else
        {
            Result=SamsungS5H1409xVsb_QAM_Master_Lock();
            SamsungS5H1409AMHUM_SetDriver();
        #if TS_PARALLEL_OUTPUT
                SamsungS5H1409_Interleave_Parallel_ModeSet();
        #else
                SamsungS5H1409_Interleave_Serial_ModeSet();
        #endif
        }
        return Result;

#elif(FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
        BOOLEAN Result;
        if(enModulation==DEMOD_ATSC_MODE_8VSB)
        {
            Result=MSB1501_Vsb_FEC_Lock();
        }
        else
        {
            Result=MSB1501_QAM_Main_Lock();
        #if TS_PARALLEL_OUTPUT
        #else
        #endif
        }
        return Result;

#elif(FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
        BOOLEAN Result = FALSE;
        if(enModulation==DEMOD_ATSC_MODE_8VSB)
        {
        #if (DEMOD_ATSC_USE_UTOPIA)
            if(DMD_ATSC_LOCK == MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_VSB_FECLOCK))
            {
                Result = TRUE;
            }
        #else
            Result=INTERN_ATSC_Vsb_FEC_Lock();
        #endif

            if(!Result)
            {
          #if (DEMOD_ATSC_USE_UTOPIA)
                if((DMD_ATSC_LOCK != MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_VSB_FSYNCLOCK))
          #else
                if(INTERN_ATSC_Vsb_FSync_Lock() == FALSE
          #endif
            #if (ENABLE_DTV_NOSIGNAL_THRESHOLD)
            #if (DEMOD_ATSC_USE_UTOPIA)
                    || (MDrv_DMD_ATSC_GetSNRPercentage() < DEMOD_VSB_NOSIGNAL_THRESHOLD)
            #else
                    || (INTERN_ATSC_ReadSNRPercentage() < DEMOD_VSB_NOSIGNAL_THRESHOLD)
            #endif
            #endif
                )
                {
                    //if MDrv_Demod_ATSC_Vsb_FSync_Lock keep 0.5 sec return unlock
                    if(msAPI_Timer_DiffTime(msAPI_Timer_GetTime0(), g_u32AFECCount) > DEMOD_AFEC_LOCK_COUNT)
                    {
                        Result = FALSE;
                    }
                    else
                    {
                        Result = TRUE;
                    }
                }
                else
                {
                    g_u32AFECCount = msAPI_Timer_GetTime0();
                    Result = TRUE;
                }
            }
            else
            {
                g_u32AFECCount = msAPI_Timer_GetTime0();
            }
        }
        else
        {
        #if (DEMOD_ATSC_USE_UTOPIA)
            if(DMD_ATSC_LOCK == MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_QAM_MAINLOCK))
            {
                Result = TRUE;
            }
        #else
            Result=INTERN_ATSC_QAM_Main_Lock();
        #endif

            if(Result
            #if (ENABLE_DTV_NOSIGNAL_THRESHOLD)
            #if (DEMOD_ATSC_USE_UTOPIA)
                && ((enModulation==DEMOD_ATSC_MODE_64QAM && MDrv_DMD_ATSC_GetSNRPercentage()>=DEMOD_64QAM_NOSIGNAL_THRESHOLD)
                || (enModulation==DEMOD_ATSC_MODE_256QAM && MDrv_DMD_ATSC_GetSNRPercentage()>=DEMOD_256QAM_NOSIGNAL_THRESHOLD))
            #else
                && ((enModulation==DEMOD_ATSC_MODE_64QAM && INTERN_ATSC_ReadSNRPercentage()>=DEMOD_64QAM_NOSIGNAL_THRESHOLD)
                || (enModulation==DEMOD_ATSC_MODE_256QAM && INTERN_ATSC_ReadSNRPercentage()>=DEMOD_256QAM_NOSIGNAL_THRESHOLD))
            #endif
            #endif
                )
            {
                g_u32AFECCount = msAPI_Timer_GetTime0();
            }
            else
            {
                if(msAPI_Timer_DiffTime(msAPI_Timer_GetTime0(), g_u32AFECCount) > DEMOD_AFEC_LOCK_COUNT)
                {
                    Result = FALSE;
                }
                else
                {
                    Result = TRUE;
                }
            }
        }
#if 0
    #if TS_PARALLEL_OUTPUT
    #else
    #endif
#endif
        //printf(" => Result=%u\n", Result);
        return Result;

#elif(FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
        BOOLEAN Result;

        if(enModulation==DEMOD_ATSC_MODE_8VSB)
        {
            //Result=Sec_1410xVsb_QAM_Master_Lock();
            Result=Sec_1410xVsb_Sync_Lock();
        }
        else
        {
            Result=Sec_1410xQam_Master_Lock();
            //Result=Sec_1410xVsb_Sync_Lock();
            AMHUM_SetDriver();
        }
        return Result;

#endif
}


//*************************************************************************
//Function name:    msAPI_Demod_ATSC_Init
//Description:      This function init Tuner & setting TS Interface
//  [doxygen]
/// This function init Tuner & setting TS Interface
/// @param bEnable \b IN: Enable bypass Demod to control Tuner
///                       Disable bypass Demode
//*************************************************************************
void msAPI_Demod_ATSC_Init(void)
{
    DEBUG_DEMOD_ATSC(printf("msAPI_Demod_ATSC_Init()\n"););

#if TS_THROUGH_LVDS
    return;
#endif

#if TS_FROM_PLAYCARD
    return;
#endif

#if (FRONTEND_DEMOD_ATSC_TYPE==LG_3303_DEMODE)

    #if TS_PARALLEL_OUTPUT
    LgdtAlterMpegMode(LGDT_PARAL);
    #else
    LgdtAlterMpegMode(LGDT_SERIAL);
    #endif

    #if TS_CLK_INV
    LgdtAlterMpegPolarity(LGDT_CLOCK_LOW, LGDT_CLOCK_HIGH);
    #else
    LgdtAlterMpegPolarity(LGDT_CLOCK_HIGH, LGDT_CLOCK_HIGH);
    #endif

#elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)

    if(SamsungS5H1409_Init())
    {
        TUNER_API_DBG(printf("\r\nS5H1409 Init done"););
    }
    else
    {
        TUNER_API_DBG(printf("\r\nS5H1409 Init fail"););
    }

    #if TS_PARALLEL_OUTPUT
        SamsungS5H1409AlterMpegMode(Samsung_PARAL);
    #else
        SamsungS5H1409AlterMpegMode(Samsung_SERIAL);
    #endif

    #if TS_CLK_INV
        SamsungS5H1409_MpegClk_InvertedSet();
    #else
        SamsungS5H1409_MpegClk_Non_InvertedSet();
    #endif
#elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
    if(MSB1501_Init())
    {
        TUNER_API_DBG(printf("\r\nMSB1501 Init done"));
    }
    else
    {
        TUNER_API_DBG(printf("\r\nMSB1501 Init fail"));
}
    TUNER_API_DBG(printf("MSB1501 Init......\r\n"));
    #if TS_PARALLEL_OUTPUT
    #else
    #endif
    #if TS_CLK_INV
    #else
    #endif

#elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
    //if (bSrcChg)
    {
    #if (DEMOD_ATSC_USE_UTOPIA)
        if (s_bDmdInit)
        {
            MDrv_DMD_ATSC_Exit();
        }

        DMD_ATSC_InitData sDMD_ATSC_InitData;
        memset(&sDMD_ATSC_InitData,0,sizeof(DMD_ATSC_InitData));

        //config by tuner
        sDMD_ATSC_InitData.bIQSwap =  DEMOD_IQSWAP;
        sDMD_ATSC_InitData.u16IF_KHZ = DEMOD_IF_KHz;

        sDMD_ATSC_InitData.u16VSBAGCLockCheckTime=50;
        sDMD_ATSC_InitData.u16VSBPreLockCheckTime=300;
        sDMD_ATSC_InitData.u16VSBFSyncLockCheckTime=500;
        sDMD_ATSC_InitData.u16VSBFECLockCheckTime=2500;
        sDMD_ATSC_InitData.u16QAMAGCLockCheckTime=50;
        sDMD_ATSC_InitData.u16QAMPreLockCheckTime=300;
        sDMD_ATSC_InitData.u16QAMMainLockCheckTime=2300;
        sDMD_ATSC_InitData.u8DMD_ATSC_DSPRegInitExt=NULL;
        sDMD_ATSC_InitData.u8DMD_ATSC_DSPRegInitSize=0;
        sDMD_ATSC_InitData.u8DMD_ATSC_InitExt=u8DMD_ATSC_InitExt;
        sDMD_ATSC_InitData.u8IS_DUAL=0;
        sDMD_ATSC_InitData.bIsExtDemod=0; //internal demod

        if( MDrv_DMD_ATSC_Init(&sDMD_ATSC_InitData, sizeof(sDMD_ATSC_InitData)) )
        {
            DEBUG_DEMOD_ATSC( printf("MDrv_DMD_ATSC_Init done\n"); );
        }
        else
        {
            printf("MDrv_DMD_ATSC_Init fail\n");
        }
    #else

        if(INTERN_ATSC_Init(DEMOD_IF_KHz, DEMOD_IQSWAP))// IF_KHZ, isIQSWAP
        {
            DEBUG_DEMOD_ATSC(printf("INTERN_ATSC Init done\n"));
        }
        else
        {
            DEBUG_DEMOD_ATSC(printf("INTERN_ATSC Init fail\n"));
        }
    #endif
    }
#if 0
    #if TS_PARALLEL_OUTPUT
    #else
    #endif

    #if TS_CLK_INV
    #else
    #endif
#endif
#elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)

    Sec_1410xInitialize();

    #if TS_PARALLEL_OUTPUT
    Sec_1410xAlterMpegMode(MPEG_MODE_PARAL);
    #else
    Sec_1410xAlterMpegMode(MPEG_MODE_SERIAL);
    #endif

    #if TS_CLK_INV
    Sec_1410xAlterMpegClk(MPEG_CLK_INVERT);
    #else
    Sec_1410xAlterMpegClk(MPEG_CLK_NOT_INVERT);
    #endif

#endif

/*
    FREQ_OFFSET_RANGE_LEFT=NTSC_FREQ_OFFSET_LEFT/FREQ_STEP;
    FREQ_OFFSET_RANGE_RIGHT=NTSC_FREQ_OFFSET_RIGHT/FREQ_STEP;
    FREQ_OFFSET_RANGE_Ch5Ch6_RIGHT=NTSC_FREQ_OFFSET_RIGHT_CH5CH6/FREQ_STEP;

    NTSC_AUTO_FREQ_OFFSET_TABLE[0]=0;
    NTSC_AUTO_FREQ_OFFSET_TABLE[1]= (VIF_COVERAGE_BOUNDRY_LEFT-VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;   //(NTSC_FREQ_OFFSET_LEFT+VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_AUTO_FREQ_OFFSET_TABLE[2]= ((VIF_COVERAGE_BOUNDRY_LEFT*2)-VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;   //(NTSC_FREQ_OFFSET_RIGHT-VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
    NTSC_AUTO_FREQ_OFFSET_TABLE[3]= (VIF_COVERAGE_BOUNDRY_RIGHT+VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_AUTO_FREQ_OFFSET_TABLE[4]= ((VIF_COVERAGE_BOUNDRY_RIGHT*2)+VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;

    NTSC_CH5CH6_OFFSET_TABLE[0]=0;
    NTSC_CH5CH6_OFFSET_TABLE[1]=(VIF_COVERAGE_BOUNDRY_LEFT-VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_CH5CH6_OFFSET_TABLE[2]=((VIF_COVERAGE_BOUNDRY_LEFT*2)-VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
    NTSC_CH5CH6_OFFSET_TABLE[3]=(VIF_COVERAGE_BOUNDRY_RIGHT+VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_CH5CH6_OFFSET_TABLE[4]=((VIF_COVERAGE_BOUNDRY_RIGHT*2)+VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
*/

#if (DEMOD_ATSC_USE_UTOPIA)
    s_bDmdInit = TRUE;
#endif
}

EN_DEMOD_ATSC_MODE msAPI_Demod_ATSC_Get_ModulationMode(void)
{
    EN_DEMOD_ATSC_MODE eDmdMode = DEMOD_ATSC_MODE_NUM;

    #if (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
        switch(MDrv_DMD_ATSC_GetModulationMode())
        {
            case DMD_ATSC_DEMOD_ATSC_VSB:
                eDmdMode = DEMOD_ATSC_MODE_8VSB;
                break;
            case DMD_ATSC_DEMOD_ATSC_64QAM:
                eDmdMode = DEMOD_ATSC_MODE_64QAM;
                break;
            case DMD_ATSC_DEMOD_ATSC_256QAM:
                eDmdMode = DEMOD_ATSC_MODE_256QAM;
                break;
            default:
                printf("[Warning] Invaild demod mode\r\n");
                break;
        }
    #endif

    return eDmdMode;
}

#if (NEW_DEMOD_SCAN)
void msAPI_Qam_No_Channel_Detect(void)
{
    U32 u32TimeOut;
    U8 u8RegData;

    //U8 u8checktime;
    //static U8 u8NoChannelDetectFlag=0;
    u32TimeOut = msAPI_Timer_GetTime0();
    u8RegData = MDrv_ReadByte(0x112612);

    if(u8RegData==0)
    {
        u8NoChannelDetectFlag=FALSE;
        u8RetQamNoChannelDetect = 0;
    }
    else if((u8RegData == 0x01) && (u8NoChannelDetectFlag==FALSE)) //AGC done
    {
        u8NoChannelDetectFlag=TRUE;
        MDrv_WriteByte(0x101e39, 0x00);
        MDrv_WriteByte(0x111f43, 0x01);
        MDrv_WriteByte(0x111f42, 0x00);
        MDrv_WriteByte(0x101e39, 0x03);
        //inform DEMOD
        MDrv_WriteByte(0x112614, 0x01);

    }
    else if ((u8RegData & 0x10) && (u8NoChannelDetectFlag==TRUE))
    {
        u8NoChannelDetectFlag=FALSE;
        MDrv_WriteByte(0x101e39, 0x00);
        MDrv_WriteByte(0x111f43, 0x00);
        MDrv_WriteByte(0x111f42, 0x00);
        MDrv_WriteByte(0x101e39, 0x03);
        //inform DEMOD
        MDrv_WriteByte(0x112614, 0x02);

        //u8checktime = MDrv_ReadByte(0x112616);
        //printf("check high peak=%d\n",u8checktime);
        //printf("check ratio=%d\n",MDrv_ReadByte(0x112617));
        if (u8RegData == 0x13)
        {
            u8RetQamNoChannelDetect = 1;        // 1;maybe have signal
            //return TRUE;
        }
        else
        {
            u8RetQamNoChannelDetect = 2;        // 2; no signal.
            //return TRUE;
        }
    }
    //return TRUE;

}
#endif


#endif

