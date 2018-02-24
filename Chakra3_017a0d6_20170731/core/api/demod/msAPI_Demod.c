#include "Board.h"

#if( ENABLE_DTV )

//#include "datatype.h"
#include "debug.h"

#include "Tuner.h"

#include "drvDMD_VD_MBX.h"
#include "drvSYS.h"

#include "msAPI_Tuner.h"

#include "msAPI_Demod.h"

#include "msAPI_Timer.h"

#if (ENABLE_PVR)
#include "MApp_PVR.h"
#endif
#include "MApp_GlobalFunction.h"



#if( ENABLE_DVBT||ENABLE_DTMB )
    #include "COFDM_Demodulator.h"
#endif

#if ENABLE_DVB_T2
    #include "demodulator_T2.h"
#endif

#if( ENABLE_DVBT )
    #include "msAPI_Demod_DVBT.c"
#endif

#if ENABLE_DVB_T2
    #include "msAPI_Demod_DVBT2.c"
#endif

#if (ENABLE_DVBC)
    #include "msAPI_Demod_DVBC.c"
#endif

#if(ENABLE_DTMB)
    #include "msAPI_Demod_DTMB.c"
#endif

#if (ENABLE_S2)
    #include "msAPI_Demod_S.c"
#endif

#if (ENABLE_DEMOD_ISDBT)
    #include "msAPI_Demod_ISDBT.c"
#endif

#if (ENABLE_ATSC)
    #include "msAPI_Demod_ATSC.c"
#endif


//==============================================================

static EN_DEMODULATOR_TYPE s_enCurrentDemodType = E_DEMODULATOR_TYPE_NULL;

//==============================================================
#if (ENABLE_CI_PLUS_V1_4)
BOOLEAN msAPI_Demod_IsSupportDemodType(EN_DEMODULATOR_TYPE eDemodType)
{
    BOOLEAN bRet = FALSE;

    switch (eDemodType)
    {
        case E_DEMODULATOR_TYPE_NULL:
            bRet = TRUE;
            break;

        case E_DEMODULATOR_TYPE_DVBT:
        case E_DEMODULATOR_TYPE_DVBT2:
            #if(ENABLE_DVBT)
                bRet = TRUE;
            #else
                bRet = FALSE;
            #endif
            break;

        case E_DEMODULATOR_TYPE_DVBC:
            #if(ENABLE_DVBC)
                bRet = TRUE;
            #else
                bRet = FALSE;
            #endif
            break;

        case E_DEMODULATOR_TYPE_DVBS_S2:
            #if(ENABLE_DVBS)
                bRet = TRUE;
            #else
                bRet = FALSE;
            #endif
            break;

        case E_DEMODULATOR_TYPE_ISDBT:
            #if(ENABLE_ISDBT)
                bRet = TRUE;
            #else
                bRet = FALSE;
            #endif
            break;

        case E_DEMODULATOR_TYPE_DTMB:
            #if(ENABLE_DTMB)
                bRet = TRUE;
            #else
                bRet = FALSE;
            #endif
        break;

        case E_DEMODULATOR_TYPE_ATSC:
            #if(ENABLE_ATSC)
                bRet = TRUE;
            #else
                bRet = FALSE;
            #endif
            break;

        default:
            break;
    }
    return bRet;
}
#endif

void msAPI_Demod_SetCurrentDemodType(EN_DEMODULATOR_TYPE eDemodType)
{
    if(eDemodType >= E_DEMODULATOR_TYPE_MAX)
    {
        printf("\n\rInvalid Demodulator Type=%d in %s", eDemodType, __FUNCTION__);
        return;
    }

    DEBUG_DEMOD(printf("Set CurDemod=%u(%s)\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType)););

    s_enCurrentDemodType = eDemodType;
}

EN_DEMODULATOR_TYPE msAPI_Demod_GetCurrentDemodType(void)
{
    return s_enCurrentDemodType;
}

char* msAPI_Demod_Get_DemodTypeName(EN_DEMODULATOR_TYPE eDemodType)
{
    if( eDemodType >= E_DEMODULATOR_TYPE_MAX )
    {
        return NULL;
    }

    switch(eDemodType)
    {
        default:
        case E_DEMODULATOR_TYPE_NULL:
            return "DEMOD_NONE";

        case E_DEMODULATOR_TYPE_DVBT:
            return "DEMOD_DVBT";

        case E_DEMODULATOR_TYPE_DVBT2:
            return "DEMOD_DVBT2";

        case E_DEMODULATOR_TYPE_DVBC:
            return "DEMOD_DVBC";

        case E_DEMODULATOR_TYPE_DVBS_S2:
            return "DEMOD_DVBS_S2";

        //case E_DEMODULATOR_TYPE_DVBS2:
        //    return "DEMOD_TYPE_DVBS2";

        case E_DEMODULATOR_TYPE_ISDBT:
            return "DEMOD_ISDBT";

        case E_DEMODULATOR_TYPE_DTMB:
            return "DEMOD_DTMB";

        case E_DEMODULATOR_TYPE_ATSC:
            return "DEMOD_ATSC";

    }
}

/*
void msAPI_Demod_Reset(void)
{
    return TRUE;
}*/

/******************************************************************************/
/// API for exit Demod::
/******************************************************************************/

void msAPI_Demodulator_Exit(void)
{
// 1. Get current demod mode
// 2. Exit current demod mode if available
// 3. Set current demode mode as NULL

    EN_DEMODULATOR_TYPE eCurrentDemodType = msAPI_Demod_GetCurrentDemodType();

    //printf("\n\n\n\r msAPI_Demodulator_Exit! Current demod type is %s", msAPI_Demod_Get_DemodTypeName(eCurrentDemodType));

    if(eCurrentDemodType == E_DEMODULATOR_TYPE_NULL)
        return;

    switch (eCurrentDemodType)
    {
    #if(ENABLE_DEMOD_DVBT)
        case E_DEMODULATOR_TYPE_DVBT:
            msAPI_Demod_DVBT_Exit();
            break;
    #endif

    #if(ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:
            msAPI_Demod_DVBT2_Exit();
            break;
    #endif

    #if(ENABLE_DEMOD_DVBC)
        case E_DEMODULATOR_TYPE_DVBC:
            msAPI_Demod_DVBC_Exit();
            break;
    #endif

    #if(ENABLE_S2)
        case E_DEMODULATOR_TYPE_DVBS_S2:
            msAPI_Demod_DVBS_Exit();
            break;
    #endif

    #if(ENABLE_DEMOD_ISDBT)
        case E_DEMODULATOR_TYPE_ISDBT:
            msAPI_Demod_ISDBT_Exit();
            break;
    #endif

    #if(ENABLE_DTMB)
        case E_DEMODULATOR_TYPE_DTMB:
            msAPI_Demod_DTMB_Exit();
            break;
    #endif

    #if(ENABLE_ATSC)
        case E_DEMODULATOR_TYPE_ATSC:
            msAPI_Demod_ATSC_Exit();
            break;
    #endif

        default:
            printf("\nError: Unsupported demod=%u\n", eCurrentDemodType);
            break;
    }

    msAPI_Demod_SetCurrentDemodType(E_DEMODULATOR_TYPE_NULL);

}

U16 msAPI_Demod_Get_CheckLockTimeout(void)
{
    U16 u16Timeout = 40; // 2 sec.
    EN_DEMODULATOR_TYPE eCurrentDemodType = msAPI_Demod_GetCurrentDemodType();

    // Fix unused warning...
    eCurrentDemodType=eCurrentDemodType;


#if( ENABLE_DVBC )
    //if( IsDVBCInUse() )
    if( eCurrentDemodType == E_DEMODULATOR_TYPE_DVBC )
    {
        if (devQAM_GetSymbolRateMode() == 1)
        {
            u16Timeout = 200;       // 10sec  for SR auto mode
        }
        else
        {
            u16Timeout = 80;        // 2 sec  for SR fixed mode
        }
    }
    else
#endif
    {
#if 0
    #if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
            u16Timeout = 32;            // 1600ms

    #elif( (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD) \
        || (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD) \
        || (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)  \
         )
            u16Timeout = 100;       // 5000ms. It need modify.

    #elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
            u16Timeout = 40;            // 2000ms

    #elif ( (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)        \
          ||(FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD) \
          ||(FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)       \
          )
            u16Timeout = 200;       // 10sec  for SR auto mode
    #else
            u16Timeout = 40;       // 2 sec.
    #endif
#else
    #if ENABLE_DVBT
        if( eCurrentDemodType == E_DEMODULATOR_TYPE_DVBT )
        {
            #if ( (FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD) )
                u16Timeout = 200;       // 10sec  for SR auto mode
            #else
                u16Timeout = 40;       // 2 sec.
            #endif
        }
        else
    #endif
        {
        #if ENABLE_ISDBT
            if( eCurrentDemodType == E_DEMODULATOR_TYPE_ISDBT )
            {
                #if ( (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD) )
                    u16Timeout = 200;       // 10sec  for SR auto mode
                #elif (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
                    u16Timeout = 40;            // 2000ms
                #else
                    u16Timeout = 40;       // 2 sec.
                #endif
            }
        #endif
        }
#endif
    }

    return u16Timeout;
}

void msAPI_Demod_Init_MBX(void)
{
#if( DEMOD_DVBT_USE_UTOPIA  \
  || DEMOD_DVBC_USE_UTOPIA  \
  || DEMOD_ISDBT_USE_UTOPIA \
  || DEMOD_DTMB_USE_UTOPIA  \
  || DEMOD_ATSC_USE_UTOPIA  \
  || DEMOD_S2_USE_UTOPIA    )

    //static EN_DEMODULATOR_TYPE s_eDemodType_Last = E_DEMODULATOR_TYPE_MAX;

    //if( eDemodType != s_eDemodType_Last )
    {
        MDrv_SYS_DMD_VD_MBX_Init();

        //bMBXInitDone = 1;
        //s_eDemodType_Last = eDemodType;
    }
#endif
}

/*
typedef enum
{
    E_INIT_DEMOD_FOR_POWER_ON,
    E_INIT_DEMOD_FOR_CHANGE_SOURCE,
    E_INIT_DEMOD_FOR_CHANGE_CHANNEL,
} EnuInitDemodCase; */
// void msAPI_Tuner_Initialization(BOOL bSrcChg, EN_DEMODULATOR_TYPE eNewDemodTypeToInit);
void msAPI_Demod_Init(EnuInitDemodCase eInitDemodCase, EN_DEMODULATOR_TYPE eNewDemodTypeToInit)
{
    // 1. If previous Demod type not exited, exit first.
    // 2. Demod init
    // 3. Update current demod type
    EN_DEMODULATOR_TYPE enCurrentDemodType = msAPI_Demod_GetCurrentDemodType();

    printf(" msAPI_Demod_Init(%d,%d-%s)\n", eInitDemodCase, eNewDemodTypeToInit, msAPI_Demod_Get_DemodTypeName(eNewDemodTypeToInit));
    //printf(" CurDemod=%d-%s)\n", enCurrentDemodType, msAPI_Demod_Get_DemodTypeName(enCurrentDemodType));

    if( eNewDemodTypeToInit >= E_DEMODULATOR_TYPE_MAX )
    {
        printf("\nError: Invalid Demodulator Type = %d in %s\n", eNewDemodTypeToInit, __FUNCTION__);
        return;
    }

    if( eNewDemodTypeToInit == enCurrentDemodType )
    {
        if( (eInitDemodCase == E_INIT_DEMOD_FOR_CHANGE_CHANNEL)
          ||(eInitDemodCase == E_INIT_DEMOD_FOR_SCAN)
          )
        {
            printf("\n Skip re-init Demod! (%d)\n", enCurrentDemodType );
            return;
        }
    }
    else
    {
        printf(" Demod: %s -> %s\n",
            msAPI_Demod_Get_DemodTypeName(enCurrentDemodType), msAPI_Demod_Get_DemodTypeName(eNewDemodTypeToInit));
    }


    //=====MISC=====
    msAPI_Demod_Init_MBX();

    // 1. If previous Demod type not exited, exit first.
    //if( (enCurrentDemodType != E_DEMODULATOR_TYPE_NULL)
    //  || (eNewDemodTypeToInit == E_DEMODULATOR_TYPE_NULL))
    {
        msAPI_Demodulator_Exit();
    }


    msAPI_Tuner_InitCurrentTPSetting();


    // 2. Demod init
    switch(eNewDemodTypeToInit)
    {
        default:
            printf("\nError: Unsupported demod type=%u\n", eNewDemodTypeToInit );
            break;

    #if( ENABLE_DEMOD_DVBT )
        case E_DEMODULATOR_TYPE_DVBT:
            msAPI_Demod_DVBT_Init();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:
            msAPI_Demod_DVBT2_Init();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBC)
        case E_DEMODULATOR_TYPE_DVBC:
            msAPI_Demod_DVBC_Init();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBS )
        case E_DEMODULATOR_TYPE_DVBS_S2:
            msAPI_Demod_S_Init();
            break;
    #endif

    #if( ENABLE_DEMOD_ISDBT )
        case E_DEMODULATOR_TYPE_ISDBT:
            msAPI_Demod_ISDBT_Init();
            break;
    #endif

    #if( ENABLE_DTMB)
        case E_DEMODULATOR_TYPE_DTMB:
            msAPI_Demod_DTMB_Init();
            break;
    #endif

    #if( ENABLE_DEMOD_ATSC)
        case E_DEMODULATOR_TYPE_ATSC:
            msAPI_Demod_ATSC_Init();
            break;
    #endif

    }

    // 3. Update current demod type
    msAPI_Demod_SetCurrentDemodType(eNewDemodTypeToInit);


    //=====MISC=====
#if 0//(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    gbTVAutoScanChannelEnable=FALSE;
#endif

}

void msAPI_Demod_Init_ForChangeSource(void)
{
    msAPI_Tuner_InitCurrentTPSetting();

    // Init demod for current source
    msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_SOURCE, msAPI_DTV_Comm_Get_CurSrcUseDemodType() );
}

void msAPI_Demod_Init_ForChangeChannel(void)
{
    msAPI_Tuner_InitCurrentTPSetting();

    // Init demod for current source
    msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_CHANNEL, msAPI_DTV_Comm_Get_CurSrcUseDemodType() );
}

void msAPI_Demod_Set_Power( EN_DEMODULATOR_TYPE eDemodType, BOOL bTurnOn)
{
    printf(" msAPI_Demod_Set_Power(%d(%s), %d)\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType), bTurnOn);

    bTurnOn=bTurnOn;

    if( eDemodType >= E_DEMODULATOR_TYPE_MAX )
    {
        printf("\nError: Invalid eDemodType= %d in %s\n", eDemodType, __FUNCTION__);
        return;
    }

    //msAPI_Demod_Init_MBX();

    switch(eDemodType)
    {
        default:
        case E_DEMODULATOR_TYPE_NULL:
            printf("No demod need Power off\n");
            break;

    #if( ENABLE_DEMOD_DVBT)
        case E_DEMODULATOR_TYPE_DVBT:
            msAPI_Demod_DVBT_Set_Power(bTurnOn);
            break;
    #endif

    #if( ENABLE_DEMOD_DTMB )
        case E_DEMODULATOR_TYPE_DTMB:
            msAPI_Demod_DTMB_Set_Power(bTurnOn);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBC )
        case E_DEMODULATOR_TYPE_DVBC:
            msAPI_Demod_DVBC_Set_Power(bTurnOn);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:
            msAPI_Demod_DVBT2_Set_Power(bTurnOn);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBS )
        case E_DEMODULATOR_TYPE_DVBS_S2:
            printf("Power On/Off Demod-DVBS TODO!\n");
            // todo
            break;
    #endif

    #if( ENABLE_DEMOD_ISDBT )
        case E_DEMODULATOR_TYPE_ISDBT:
            printf("Power On/Off Demod-ISDBT TODO!\n");
            // todo
            break;
    #endif

    #if( ENABLE_DEMOD_ATSC )
        case E_DEMODULATOR_TYPE_ATSC:
            printf("Power On/Off Demod-ATSC TODO!\n");
            // todo
            break;
    #endif

    }

    //printf(" msAPI_Demod_Set_Power(%d(%s), %d) end\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType), bTurnOn);
}

void msAPI_Demod_Set_TsSerialOrParallel( EN_DEMODULATOR_TYPE eDemodType, BOOL bTsIsParallel)
{
    //printf(" msAPI_Demod_Set_TsSerialOrParallel(%d(%s), %d)\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType), bTsIsParallel);

    bTsIsParallel=bTsIsParallel;

    if( eDemodType >= E_DEMODULATOR_TYPE_MAX )
    {
        printf("\nError: Invalid eDemodType= %d in %s\n", eDemodType, __FUNCTION__);
        return;
    }


    switch(eDemodType)
    {
        default:
        case E_DEMODULATOR_TYPE_NULL:
            printf("No demod need Power off\n");
            break;

    #if( ENABLE_DEMOD_DVBT)
        case E_DEMODULATOR_TYPE_DVBT:
            devCOFDM_DVBT_SwitchTransportSteamInferface((bTsIsParallel)?E_PARALLEL_INTERFACE:E_SERIAL_INTERFACE);
            break;
    #endif

    #if( ENABLE_DEMOD_DTMB )
        case E_DEMODULATOR_TYPE_DTMB:
            devCOFDM_DTMB_SwitchTransportSteamInferface((bTsIsParallel)?E_PARALLEL_INTERFACE:E_SERIAL_INTERFACE);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBC )
        case E_DEMODULATOR_TYPE_DVBC:
            devQAM_SwitchTransportSteamInferface(bTsIsParallel?E_QAM_PARALLEL_INTERFACE:E_QAM_SERIAL_INTERFACE);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:

            break;
    #endif

    #if( ENABLE_DEMOD_DVBS )
        case E_DEMODULATOR_TYPE_DVBS_S2:
            devCOFDM_S2_SwitchTransportSteamInferface((bTsIsParallel)?E_PARALLEL_INTERFACE:E_SERIAL_INTERFACE);
            break;
    #endif

    #if( ENABLE_DEMOD_ISDBT )
        case E_DEMODULATOR_TYPE_ISDBT:
            devCOFDM_ISDBT_SwitchTransportSteamInferface((bTsIsParallel)?E_PARALLEL_INTERFACE:E_SERIAL_INTERFACE);
            break;
    #endif

    #if( ENABLE_DEMOD_ATSC )
        case E_DEMODULATOR_TYPE_ATSC:
            if(!bTsIsParallel)
            {
                PRINT_CURRENT_LINE();
                printf("\nWarning: todo\n");
            }
            break;
    #endif

    }

}

U8 msAPI_Demod_Get_SNR(EN_DEMODULATOR_TYPE eDemodType)
{
    U8 u8SNR = 0;


    printf(" msAPI_Demod_Get_SNR(%d-%s)\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType));


    if( eDemodType >= E_DEMODULATOR_TYPE_MAX )
    {
        printf("\nError: Invalid eDemodType= %d in %s\n", eDemodType, __FUNCTION__);
        return u8SNR;
    }


    switch(eDemodType)
    {
        default:
        case E_DEMODULATOR_TYPE_NULL:
            printf("No demod in use\n");
            break;

    #if( ENABLE_DEMOD_DVBT)
        case E_DEMODULATOR_TYPE_DVBT:
            u8SNR = devCOFDM_DVBT_GetSignalToNoiseRatio();
            break;
    #endif

    #if( ENABLE_DEMOD_DTMB )
        case E_DEMODULATOR_TYPE_DTMB:
            u8SNR = devCOFDM_DTMB_GetSignalToNoiseRatio();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBC )
        case E_DEMODULATOR_TYPE_DVBC:
            u8SNR = devQAM_GetSignalToNoiseRatio();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:
            u8SNR = devCOFDM_DVBT_GetSignalToNoiseRatio();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBS )
        case E_DEMODULATOR_TYPE_DVBS_S2:
            printf("todo: Demod-DVBS get SNR!\n");
            //u8SNR = devCOFDM_GetSignalToNoiseRatio();
            // todo
            break;
    #endif

    #if( ENABLE_DEMOD_ISDBT )
        case E_DEMODULATOR_TYPE_ISDBT:
            u8SNR = devCOFDM_ISDBT_GetSignalToNoiseRatio();
            break;
    #endif

    #if( ENABLE_DEMOD_ATSC )
        case E_DEMODULATOR_TYPE_ATSC:
            printf("todo: Demod-ATSC get SNR!\n");
            // todo
            break;
    #endif

    }

    return u8SNR;
}

U16 msAPI_Demod_Get_SignalQualityPercentage(EN_DEMODULATOR_TYPE eDemodType)
{
    U16 u16Percentage = 0;


    //printf(" msAPI_Demod_Get_SignalQualityPercentage(%d-%s)\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType));


    if( eDemodType >= E_DEMODULATOR_TYPE_MAX )
    {
        printf("\nError: Invalid eDemodType= %d in %s\n", eDemodType, __FUNCTION__);
        return u16Percentage;
    }


    switch(eDemodType)
    {
        default:
        case E_DEMODULATOR_TYPE_NULL:
            printf("No demod in use\n");
            break;

    #if( ENABLE_DEMOD_DVBT)
        case E_DEMODULATOR_TYPE_DVBT:
            devCOFDM_DVBT_GetSignalQuality(&u16Percentage);
            break;
    #endif

    #if( ENABLE_DEMOD_DTMB )
        case E_DEMODULATOR_TYPE_DTMB:
            devCOFDM_DTMB_GetSignalQuality(&u16Percentage);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBC )
        case E_DEMODULATOR_TYPE_DVBC:
            devQAM_GetSignalQuality(&u16Percentage);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:
            mdev_CofdmGetSignalQuality(&u16Percentage);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBS )
        case E_DEMODULATOR_TYPE_DVBS_S2:
            devCOFDM_S2_GetSignalQuality(&u16Percentage);
            break;
    #endif

    #if( ENABLE_DEMOD_ISDBT )
        case E_DEMODULATOR_TYPE_ISDBT:
            devCOFDM_ISDBT_GetSignalQuality(&u16Percentage);
            break;
    #endif

    #if( ENABLE_DEMOD_ATSC )
        case E_DEMODULATOR_TYPE_ATSC:
            printf("todo: Demod-ATSC get Quality!\n");
            // todo
            break;
    #endif

    }

    return u16Percentage;
}

BOOL msAPI_Demod_Get_SignalStrength(EN_DEMODULATOR_TYPE eDemodType, U16 * pu16SignalStrength)
{
    U16 u16SignalStrength = 0;
    BOOL bRtn = TRUE;


    //printf(" msAPI_Demod_Get_SignalStrength(%d-%s)\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType));


    if( eDemodType >= E_DEMODULATOR_TYPE_MAX )
    {
        printf("\nError: Invalid eDemodType= %d in %s\n", eDemodType, __FUNCTION__);
        return FALSE;
    }


    switch(eDemodType)
    {
        default:
        case E_DEMODULATOR_TYPE_NULL:
            printf("No demod in use\n");
            bRtn = FALSE;
            break;

    #if( ENABLE_DEMOD_DVBT)
        case E_DEMODULATOR_TYPE_DVBT:
            if( E_RESULT_SUCCESS != devCOFDM_DVBT_GetSignalStrength(&u16SignalStrength) )
            {
                bRtn = FALSE;
            }
            break;
    #endif

    #if( ENABLE_DEMOD_DTMB )
        case E_DEMODULATOR_TYPE_DTMB:
            if( E_RESULT_SUCCESS != devCOFDM_DTMB_GetSignalStrength(&u16SignalStrength) )
            {
                bRtn = FALSE;
            }
            break;
    #endif

    #if( ENABLE_DEMOD_DVBC )
        case E_DEMODULATOR_TYPE_DVBC:
            if( E_RESULT_SUCCESS != devQAM_GetSignalStrength(&u16SignalStrength) )
            {
                bRtn = FALSE;
            }
            break;
    #endif

    #if( ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:
            mdev_CofdmGetSignalStrength(&u16SignalStrength);
            break;
    #endif

    #if( ENABLE_DEMOD_DVBS )
        case E_DEMODULATOR_TYPE_DVBS_S2:
            bRtn = msAPI_Demod_S_Get_SignalStrength(&u16SignalStrength);
            break;
    #endif

    #if( ENABLE_DEMOD_ISDBT )
        case E_DEMODULATOR_TYPE_ISDBT:
            if( E_RESULT_SUCCESS != devCOFDM_ISDBT_GetSignalStrength(&u16SignalStrength) )
            {
                bRtn = FALSE;
            }
            break;
    #endif

    #if( ENABLE_DEMOD_ATSC )
        case E_DEMODULATOR_TYPE_ATSC:
            printf("todo: Demod-ATSC get SignalStrength!\n");
            // todo
            bRtn = FALSE;
            break;
    #endif

    }

    if( bRtn )
    {
        *pu16SignalStrength = u16SignalStrength;
    }
    else
    {
        *pu16SignalStrength = 0;
        printf("\nError: msAPI_Demod_Get_SignalStrength() failed!\n");
    }

    return bRtn;
}

EnuApiDemodLockStatus msAPI_Demod_Get_LockStatus(EN_DEMODULATOR_TYPE eDemodType )
{
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;

    //printf(" msAPI_Demod_Get_LockStatus(%d-%s)\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType));


    if( eDemodType >= E_DEMODULATOR_TYPE_MAX )
    {
        printf("\nError: Invalid eDemodType= %d in %s\n", eDemodType, __FUNCTION__);
        return eDemodLockStatus;
    }


    switch(eDemodType)
    {
        default:
        case E_DEMODULATOR_TYPE_NULL:
            printf("No demod in use\n");
            break;

    #if( ENABLE_DEMOD_DVBT)
        case E_DEMODULATOR_TYPE_DVBT:
            eDemodLockStatus = msAPI_Demod_DVBT_Get_LockStatus();
            break;
    #endif

    #if( ENABLE_DEMOD_DTMB )
        case E_DEMODULATOR_TYPE_DTMB:
            eDemodLockStatus = msAPI_Demod_DTMB_Get_LockStatus();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBC )
        case E_DEMODULATOR_TYPE_DVBC:
            eDemodLockStatus = msAPI_Demod_DVBC_Get_LockStatus();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:
            eDemodLockStatus = msAPI_Demod_DVBT2_Get_LockStatus();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBS )
        case E_DEMODULATOR_TYPE_DVBS_S2:
            eDemodLockStatus = msAPI_Demod_DVBS_Get_LockStatus();
            break;
    #endif

    #if( ENABLE_DEMOD_ISDBT )
        case E_DEMODULATOR_TYPE_ISDBT:
            eDemodLockStatus = msAPI_Demod_ISDBT_Get_LockStatus();
            break;
    #endif

    #if( ENABLE_DEMOD_ATSC )
        case E_DEMODULATOR_TYPE_ATSC:
            printf("todo: Demod-ATSC get lock!\n");
            // todo
            break;
    #endif

    }

    return eDemodLockStatus;

}

static U32 s_Demod_u32DetectLockStartTime = 0;
void msAPI_Demod_Init_DetectLockTask(void)
{
    s_Demod_u32DetectLockStartTime = MsOS_GetSystemTime();
}

U32 msAPI_Demod_Get_DetectLockUseTime(void)
{
    return msAPI_Timer_DiffTime_2(s_Demod_u32DetectLockStartTime, MsOS_GetSystemTime());
}

EnuApiDemodLockStatus msAPI_Demod_DetectLockTask(void)
{
    EN_DEMODULATOR_TYPE eDemodType = s_enCurrentDemodType;
    EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;


    //printf(" msAPI_Demod_DetectLockTask(%d-%s)\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType));

    if( eDemodType >= E_DEMODULATOR_TYPE_MAX )
    {
        printf("\nError: Invalid eDemodType= %d in %s\n", eDemodType, __FUNCTION__);
        return eDemodLockStatus;
    }

    switch(eDemodType)
    {
        default:
        case E_DEMODULATOR_TYPE_NULL:
            printf("No demod in use\n");
            break;

    #if( ENABLE_DEMOD_DVBT)
        case E_DEMODULATOR_TYPE_DVBT:
            eDemodLockStatus = msAPI_Demod_DVBT_DetectLockTask();
            break;
    #endif

    #if( ENABLE_DEMOD_DTMB )
        case E_DEMODULATOR_TYPE_DTMB:
            eDemodLockStatus = msAPI_Demod_DTMB_DetectLockTask();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBC )
        case E_DEMODULATOR_TYPE_DVBC:
            eDemodLockStatus = msAPI_Demod_DVBC_DetectLockTask();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBT2)
        case E_DEMODULATOR_TYPE_DVBT2:
            eDemodLockStatus = msAPI_Demod_DVBT2_DetectLockTask();
            break;
    #endif

    #if( ENABLE_DEMOD_DVBS )
        case E_DEMODULATOR_TYPE_DVBS_S2:
            eDemodLockStatus = msAPI_Demod_DVBS_DetectLockTask();
            break;
    #endif

    #if( ENABLE_DEMOD_ISDBT )
        case E_DEMODULATOR_TYPE_ISDBT:
            eDemodLockStatus = msAPI_Demod_ISDBT_DetectLockTask();
            break;
    #endif

    #if( ENABLE_DEMOD_ATSC )
        case E_DEMODULATOR_TYPE_ATSC:
            printf("todo: Demod-ATSC get DetectLockTask!\n");
            // todo
            break;
    #endif

    }

    return eDemodLockStatus;
}


#define CHECK_DEMOD_LOCK_TIMEOUT    10500 // 10sec
BOOLEAN msAPI_Demod_CheckLock(BOOLEAN *CheckLockResult, BOOLEAN fScan)
{
#if TS_FROM_PLAYCARD
    // for play card
    UNUSED(fScan);
    *CheckLockResult = FE_LOCK;
    return TRUE;
#endif

    U32 u32CheckStartTime = MsOS_GetSystemTime();


    *CheckLockResult = FE_NOT_LOCK;

    if ( fScan )
    {
        EnuApiDemodLockStatus eDemodLockStatus = E_API_DEMOD_STATUS_NO_LOCK;

        // Init demod checking lock task...
        msAPI_Demod_Init_DetectLockTask();

        do
        {
        #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
        #endif

            eDemodLockStatus = msAPI_Demod_DetectLockTask();

            if( eDemodLockStatus == E_API_DEMOD_STATUS_NO_LOCK )
            {
                break;
            }
            else if( eDemodLockStatus == E_API_DEMOD_STATUS_LOCKED )
            {
                break;
            }

            // Check User Key
            if( msAPI_Tuner_CheckLock_DetectUserKey() )
            {
                printf("Detect Key~ Stop Scan!\n");
                break;
            }

            // Delay time
            msAPI_Timer_Delayms( 40 );

        }
        while( msAPI_Timer_DiffTime_2(u32CheckStartTime, MsOS_GetSystemTime()) < CHECK_DEMOD_LOCK_TIMEOUT );

        if( eDemodLockStatus == E_API_DEMOD_STATUS_LOCKED )
            *CheckLockResult = FE_LOCK;
        else
            *CheckLockResult = FE_NOT_LOCK;

    }
    else
    {
        if( msAPI_Demod_Get_LockStatus(msAPI_Demod_GetCurrentDemodType()) == E_API_DEMOD_STATUS_LOCKED )
        {
            *CheckLockResult = FE_LOCK;
        }
        else
        {
            *CheckLockResult = FE_NOT_LOCK;
        }
    }

    return TRUE;
}

typedef struct
{
    EN_DEMODULATOR_TYPE eDemodType;

    U8 u8DemodIsExternal;

    // For Normal case,
    DMX_FLOW_INPUT eDMX_FLOW_INPUT_Normal;
    BOOLEAN bTsIsParallel_Normal;

    // For CI case,
    DMX_FLOW_INPUT eDMX_FLOW_INPUT_CI;
    BOOLEAN bTsIsParallel_CI;
} StruDemodTspPathInfo;

#define DEMOD_TS_IS_SERIAL      0
#define DEMOD_TS_IS_PARALLEL    1

#define DEMOD_INSIDE        0
#define DEMOD_OUTSIDE       1

#ifndef DMX_FLOW_INPUT_DVBT
    #define DMX_FLOW_INPUT_DVBT DMX_FLOW_INPUT_EXT_INPUT0
#endif
#ifndef DMX_FLOW_INPUT_DVBT2
    #define DMX_FLOW_INPUT_DVBT2 DMX_FLOW_INPUT_EXT_INPUT0
#endif
#ifndef DMX_FLOW_INPUT_DVBC
    #define DMX_FLOW_INPUT_DVBC DMX_FLOW_INPUT_EXT_INPUT0
#endif
#ifndef DMX_FLOW_INPUT_DTMB
    #define DMX_FLOW_INPUT_DTMB DMX_FLOW_INPUT_EXT_INPUT0
#endif
#ifndef DMX_FLOW_INPUT_ISDBT
    #define DMX_FLOW_INPUT_ISDBT DMX_FLOW_INPUT_EXT_INPUT0
#endif
#ifndef DMX_FLOW_INPUT_DVBS
    #define DMX_FLOW_INPUT_DVBS DMX_FLOW_INPUT_EXT_INPUT0
#endif
#ifndef DMX_FLOW_INPUT_ATSC
    #define DMX_FLOW_INPUT_ATSC DMX_FLOW_INPUT_EXT_INPUT0
#endif

StruDemodTspPathInfo g_astDemodTspPathInfo[] =
{
#if(ENABLE_DEMOD_DVBT)
    {E_DEMODULATOR_TYPE_DVBT,
    #if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
        DEMOD_INSIDE,
        DMX_FLOW_INPUT_DEMOD, DEMOD_TS_IS_PARALLEL, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0, DEMOD_TS_IS_PARALLEL, // CI
    #else
        DEMOD_OUTSIDE,
        DMX_FLOW_INPUT_DVBT,  TS_PARALLEL_DVBT_OUTPUT, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0,  DEMOD_TS_IS_PARALLEL, // CI
    #endif
    },
#endif

#if(ENABLE_DEMOD_DVBT2)
    {E_DEMODULATOR_TYPE_DVBT2,
    #if(FRONTEND_DEMOD_T2_TYPE == EMBEDDED_DVBT2_DEMOD)
        DEMOD_INSIDE,
        DMX_FLOW_INPUT_DEMOD, DEMOD_TS_IS_PARALLEL, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0, DEMOD_TS_IS_PARALLEL, // CI
    #else
        DEMOD_OUTSIDE,
        DMX_FLOW_INPUT_DVBT2,  TS_PARALLEL_DVBT2_OUTPUT, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0,  DEMOD_TS_IS_PARALLEL, // CI
    #endif
    },
#endif

#if(ENABLE_DEMOD_DVBC)
    {E_DEMODULATOR_TYPE_DVBC,
    #if(FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD)
        DEMOD_INSIDE,
        DMX_FLOW_INPUT_DEMOD, DEMOD_TS_IS_PARALLEL, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0, DEMOD_TS_IS_PARALLEL, // CI
    #else
        DEMOD_OUTSIDE,
        DMX_FLOW_INPUT_DVBC,  TS_PARALLEL_DVBC_OUTPUT, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0,  DEMOD_TS_IS_PARALLEL, // CI
    #endif
    },
#endif

#if(ENABLE_DEMOD_DTMB)
    {E_DEMODULATOR_TYPE_DTMB,
    #if(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
        DEMOD_INSIDE,
        DMX_FLOW_INPUT_DEMOD, DEMOD_TS_IS_PARALLEL, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0, DEMOD_TS_IS_PARALLEL, // CI
    #else
        DEMOD_OUTSIDE,
        DMX_FLOW_INPUT_DTMB,  TS_PARALLEL_DTMB_OUTPUT, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0,  DEMOD_TS_IS_PARALLEL, // CI
    #endif
    },
#endif

#if(ENABLE_DEMOD_ISDBT)
    {E_DEMODULATOR_TYPE_ISDBT,
    #if(FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
        DEMOD_INSIDE,
        DMX_FLOW_INPUT_DEMOD, DEMOD_TS_IS_PARALLEL, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0, DEMOD_TS_IS_PARALLEL, // CI
    #else
        DEMOD_OUTSIDE,
        DMX_FLOW_INPUT_ISDBT,  TS_PARALLEL_ISDBT_OUTPUT, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0,  DEMOD_TS_IS_PARALLEL, // CI
    #endif
    },
#endif

#if(ENABLE_DEMOD_DVBS)
    {E_DEMODULATOR_TYPE_DVBS_S2,
    #if(FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD)
        DEMOD_INSIDE,
        DMX_FLOW_INPUT_DEMOD, DEMOD_TS_IS_PARALLEL, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0, DEMOD_TS_IS_PARALLEL, // CI
    #else
        DEMOD_OUTSIDE,
        DMX_FLOW_INPUT_DVBS,  TS_PARALLEL_S2_OUTPUT, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0,  DEMOD_TS_IS_PARALLEL, // CI
    #endif
    },
#endif

#if(ENABLE_DEMOD_ATSC)
    {E_DEMODULATOR_TYPE_ATSC,
    #if(FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
        DEMOD_INSIDE,
        DMX_FLOW_INPUT_DEMOD, DEMOD_TS_IS_PARALLEL, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0, DEMOD_TS_IS_PARALLEL, // CI
    #else
        DEMOD_OUTSIDE,
        DMX_FLOW_INPUT_ATSC,  TS_PARALLEL_ATSC_OUTPUT, // Normal
        DMX_FLOW_INPUT_EXT_INPUT0,  DEMOD_TS_IS_PARALLEL, // CI
    #endif
    },
#endif

    //{E_DEMODULATOR_TYPE_NULL, 0,0,0,0},
};

#define DEBUG_DEMOD_TSP_PATH(x) //x
U8 _msAPI_DemodTsp_Find_PathIdx(EN_DEMODULATOR_TYPE eDemodType)
{
    U8 u8TabIdx;

    DEBUG_DEMOD_TSP_PATH(printf("_msAPI_DemodTsp_Find_PathIdx(eDemodType=%u(%s))\n", eDemodType, msAPI_Demod_Get_DemodTypeName(eDemodType)););

    for( u8TabIdx = 0; u8TabIdx < (sizeof(g_astDemodTspPathInfo)/sizeof(StruDemodTspPathInfo)) ; ++ u8TabIdx )
    {
        if( g_astDemodTspPathInfo[u8TabIdx].eDemodType == eDemodType )
        {
            DEBUG_DEMOD_TSP_PATH( printf(" => u8TabIdx=%u\n", u8TabIdx); );
            return u8TabIdx;
        }
    }

    printf("\nWarning: Can not find DemodTspPathIdx for this demod=%u\n", eDemodType);

    return 0;
}

BOOLEAN msAPI_DemodTsp_Get_TsIsParallel(EN_DEMODULATOR_TYPE eDemodType, BOOLEAN bCIMode)
{
    bCIMode=bCIMode;
    DEBUG_DEMOD_TSP_PATH(printf("msAPI_DemodTsp_Get_TsIsParallel(eDemodType=%s, bCIMode=%u)\n", msAPI_Demod_Get_DemodTypeName(eDemodType), bCIMode););

    U8 u8TabIdx = _msAPI_DemodTsp_Find_PathIdx(eDemodType);
    BOOLEAN bTsIsParallel;

#if(ENABLE_CI)
    if( bCIMode )
        bTsIsParallel = g_astDemodTspPathInfo[u8TabIdx].bTsIsParallel_CI;
    else
#endif
    {
        bTsIsParallel = g_astDemodTspPathInfo[u8TabIdx].bTsIsParallel_Normal;
    }

    DEBUG_DEMOD_TSP_PATH( printf(" => bTsIsParallel=%u\n", bTsIsParallel); );

    return bTsIsParallel;
}

DMX_FLOW_INPUT msAPI_DemodTsp_Get_DMX_FLOW_INPUT(EN_DEMODULATOR_TYPE eDemodType, BOOLEAN bCIMode)
{
    bCIMode=bCIMode;
    DEBUG_DEMOD_TSP_PATH(printf("msAPI_DemodTsp_Get_DMX_FLOW_INPUT(eDemodType=%s, bCIMode=%u)\n", msAPI_Demod_Get_DemodTypeName(eDemodType), bCIMode););

    U8 u8TabIdx = _msAPI_DemodTsp_Find_PathIdx(eDemodType);
    DMX_FLOW_INPUT eDMX_FLOW_INPUT;

#if(ENABLE_CI)
    if( bCIMode )
        eDMX_FLOW_INPUT = g_astDemodTspPathInfo[u8TabIdx].eDMX_FLOW_INPUT_CI;
    else
#endif
    {
        eDMX_FLOW_INPUT = g_astDemodTspPathInfo[u8TabIdx].eDMX_FLOW_INPUT_Normal;
    }

    DEBUG_DEMOD_TSP_PATH( printf(" => eDMX_FLOW_INPUT=%u\n", eDMX_FLOW_INPUT); );

    return eDMX_FLOW_INPUT;
}

BOOLEAN msAPI_DemodTsp_Is_ExternalDemod(EN_DEMODULATOR_TYPE eDemodType)
{
    //DEBUG_DEMOD_TSP_PATH(printf("msAPI_DemodTsp_Is_ExternalDemod(eDemodType=%s)\n", msAPI_Demod_Get_DemodTypeName(eDemodType)););
    U8 u8TabIdx = _msAPI_DemodTsp_Find_PathIdx(eDemodType);

    if( DEMOD_OUTSIDE == g_astDemodTspPathInfo[u8TabIdx].u8DemodIsExternal )
        return TRUE;

    return FALSE;
}


#define ENABLE_USE_NEW_SERIAL_CONTROL   1

#if 0
    #define DEBUG_SETUP_TS_PATH(x)  do { \
        msDebug_ANSI_SetColorText(E_FONT_COLOR_PURPLE); \
        msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_BLACK); \
        x ; \
        msDebug_ANSI_AllAttrOffText();          \
    } while(0)
#else
    #define DEBUG_SETUP_TS_PATH(x)
#endif

static BOOLEAN g_Demod_bCurTSFormatIsParallel = 0;
static EnuDemodTspPathUseCase g_Demod_CurDemodTspPathUseCase;
void msAPI_Demod_SetupTSPath(EnuDemodTspPathUseCase eDemodTspPathUseCase)
{
    DEBUG_SETUP_TS_PATH(printf("\n >> msAPI_Demod_SetupTSPath(case=%u) \n", eDemodTspPathUseCase););

    EN_DEMODULATOR_TYPE eCurDemodType = msAPI_Demod_GetCurrentDemodType();

    BOOLEAN bIsPVRMode = FALSE;
    BOOLEAN bCIMode = FALSE;


#if(ENABLE_CI&&ENABLE_CI_PLUS)
    /* By-Pass Mode */ // Demod to TSP
    if( eDemodTspPathUseCase == E_DEMOD_TSP_PATH_CASE_CI_BY_PASS)
        eDemodTspPathUseCase = E_DEMOD_TSP_PATH_CASE_NORMAL;
#endif


    switch( eDemodTspPathUseCase )
    {
        default:
        case E_DEMOD_TSP_PATH_CASE_NORMAL:
            break;

    #if(ENABLE_PVR)
        case E_DEMOD_TSP_PATH_CASE_PVR_REC:
            bIsPVRMode = TRUE;
            #if( ENABLE_DVB&&ENABLE_CI )
            if (msAPI_CI_CardDetect())
            {
                bCIMode = TRUE;
            }
            #endif
            break;

        case E_DEMOD_TSP_PATH_CASE_PVR_PLAY:
            bIsPVRMode = TRUE;
            break;
    #endif

    #if(ENABLE_CI)
        /* Pass-Through Mode */ // CI to TSP
        case E_DEMOD_TSP_PATH_CASE_CI_IN_USE:
            bCIMode = TRUE;
            break;
    #endif
    }

#if(ENABLE_PVR)
    if( !bIsPVRMode )
    {
        if( MApp_PVR_IsRecording() )
        {
            // Need check ...
            printf("\nWarning: TS-Path should be PVR case!?\n");
            //bIsPVRMode = TRUE;
        }
    }
#endif

#if(ENABLE_CI)
    if( !bCIMode )
    {
        if( msAPI_CI_CardDetect() && (!MApp_Is_InAutoScan_DTV()) )
        {
            // Need check ...
            printf("\nWarning: TS-Path should be CI case!?\n");
            //bCIMode = TRUE;
        }
    }
#endif


    BOOLEAN bTsIsParallelMode = msAPI_DemodTsp_Get_TsIsParallel(eCurDemodType, bCIMode);
    DEBUG_SETUP_TS_PATH( printf(" => bTsIsParallelMode=%u\n", bTsIsParallelMode); );

    g_Demod_bCurTSFormatIsParallel = bTsIsParallelMode;
    g_Demod_CurDemodTspPathUseCase = eDemodTspPathUseCase;

#if ENABLE_USE_NEW_SERIAL_CONTROL // Refine at 20150910

    // Set Demod Serial/Parallel
    msAPI_Demod_Set_TsSerialOrParallel(eCurDemodType, bTsIsParallelMode);

    DMX_FLOW_INPUT eDmxFlowInput = msAPI_DemodTsp_Get_DMX_FLOW_INPUT(eCurDemodType, bCIMode);
    DEBUG_SETUP_TS_PATH(printf("eDmxFlowInput = %u\n", eDmxFlowInput););
    if( eDmxFlowInput == DMX_FLOW_INPUT_DEMOD )
    {
        DEBUG_SETUP_TS_PATH(printf("DMX_FLOW_INPUT_DEMOD\n"););
    }
    else if( eDmxFlowInput == DMX_FLOW_INPUT_EXT_INPUT0 )
    {
        DEBUG_SETUP_TS_PATH(printf("DMX_FLOW_INPUT_EXT_INPUT0\n"););
    }
    else if( eDmxFlowInput == DMX_FLOW_INPUT_EXT_INPUT1 )
    {
        DEBUG_SETUP_TS_PATH(printf("DMX_FLOW_INPUT_EXT_INPUT1\n"););
    }

    // Set Pad mux ...
    // MS_BOOL MDrv_SYS_SetPadMux(SYS_PAD_MUX_SET ePadMuxType, SYS_PAD_SEL ePadSel);
    //  ePadMuxType = E_TS0_PAD_SET/E_TS1_PAD_SET ,
    //  ePadSel = E_SERIAL_IN/E_PARALLEL_IN
    if( (eDmxFlowInput == DMX_FLOW_INPUT_EXT_INPUT0)
      ||(eDmxFlowInput == DMX_FLOW_INPUT_EXT_INPUT1)
      )
    {
        SYS_PAD_MUX_SET ePadMuxType = E_TS0_PAD_SET;
        if( eDmxFlowInput == DMX_FLOW_INPUT_EXT_INPUT1 )
            ePadMuxType = E_TS1_PAD_SET;

        SYS_PAD_SEL ePadSel = (bTsIsParallelMode)?E_PARALLEL_IN:E_SERIAL_IN;
        MDrv_SYS_SetPadMux(ePadMuxType, ePadSel);
    }

    // When CI mode, Internal mode ==> CI ==> TSP
#if(ENABLE_CI)
    if( eDemodTspPathUseCase == E_DEMOD_TSP_PATH_CASE_CI_IN_USE ) // CI to TSP
    {
        if( FALSE == msAPI_DemodTsp_Is_ExternalDemod(eCurDemodType) ) // Use internal demod
        {
            // Set demod output from TS1_PAD
            MDrv_SYS_SetPadMux(E_TS1_PAD_SET, E_PARALLEL_OUT);
        }
    }
#endif

    // Set TSP path flow
    DMX_FLOW eDmxFlow;
    if( bIsPVRMode )
    {
#if(ENABLE_PVR)
        if(MApp_PVR_GetRecordCAPVR())
        {
            eDmxFlow = DMX_FLOW_PVRCA;
        }
        else
#endif
        {
            eDmxFlow = DMX_FLOW_PVR;
        }
        DEBUG_SETUP_TS_PATH(printf("eDmxFlow = DMX_FLOW_PVR\n"););
    }
    else
    {
        eDmxFlow = DMX_FLOW_PLAYBACK;
        DEBUG_SETUP_TS_PATH(printf("eDmxFlow = DMX_FLOW_PLAYBACK\n"););
    }

    MS_BOOL bClkInv = FALSE;
    MS_BOOL bExtSync = TRUE;
    DEBUG_SETUP_TS_PATH(printf("MApi_DMX_FlowSet(%u,%u,%u,%u,%u)\n", eDmxFlow, eDmxFlowInput, bClkInv, bExtSync, bTsIsParallelMode););
    MApi_DMX_FlowSet(eDmxFlow, eDmxFlowInput, bClkInv, bExtSync, bTsIsParallelMode);

    // What is this?
  #if( /*FRONTEND_DEMOD_TYPE == HDIC_2311 ||*/ FRONTEND_DEMOD_DVBT_TYPE == LEGEND_9x_DEMOD)
     MApi_DMX_Serial_Ext_Sync_1T(TRUE); // 1bit sync
  #endif

#else // ENABLE_USE_NEW_SERIAL_CONTROL

    msAPI_Tuner_Serial_Control(bTsIsParallelMode, bIsPVRMode);

#endif // ENABLE_USE_NEW_SERIAL_CONTROL
}

EnuDemodTspPathUseCase msAPI_Demod_Get_CurTSPathCase(void)
{
    return g_Demod_CurDemodTspPathUseCase;
}

BOOLEAN msAPI_Demod_Is_CurTSFormatParallel(void)
{
    if( g_Demod_bCurTSFormatIsParallel )
        return TRUE;

    return FALSE;
}

BOOLEAN msAPI_Demod_Is_CurCaseCIMode(void)
{
#if(ENABLE_CI)
    if( E_DEMOD_TSP_PATH_CASE_CI_IN_USE == g_Demod_CurDemodTspPathUseCase )
        return TRUE;
#endif

    return FALSE;
}


#endif // #if( ENABLE_DTV )

