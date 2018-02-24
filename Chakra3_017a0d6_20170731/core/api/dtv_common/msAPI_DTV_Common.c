#include "Board.h"

#if(ENABLE_DTV)

#include "MApp_GlobalSettingSt.h"

#include "msAPI_Tuner.h"

#include "msAPI_DTVSystem.h"

#include "msAPI_DTV_Common.h"

#if(!BLOADER)
#include "MApp_TopStateMachine.h"
#endif

#if (ENABLE_CI_PLUS)
static BOOLEAN s_bIsCiTuneEnable = FALSE;
static U8 s_u8DVBT2_PLPID = 0xFF;

void msAPI_DTV_Comm_SetPLPID(U8 u8CiTune_PLPID)
{
    s_u8DVBT2_PLPID = u8CiTune_PLPID;
}

U8 msAPI_DTV_Comm_GetPLPID(void)
{
    return s_u8DVBT2_PLPID;
}

void msAPI_DTV_Comm_SetCiTuneStatus(BOOLEAN bIsCiTune)
{
    s_bIsCiTuneEnable = bIsCiTune;
}

U8 msAPI_DTV_Comm_GetIsCiTuneStatus(void)
{
    return s_bIsCiTuneEnable;
}
#endif

EN_DEMODULATOR_TYPE msAPI_DTV_Comm_Get_CurSrcUseDemodType(void)
{
    EN_DEMODULATOR_TYPE eDemodType = E_DEMODULATOR_TYPE_NULL;

#if ENABLE_S2
    if( IsS2InUse() ) // DVBS
    {
        eDemodType = E_DEMODULATOR_TYPE_DVBS_S2;
    }
    else
#endif
#if(ENABLE_ATSC)
    if( IsAtscInUse()||IsATVInUse() )
    {
        eDemodType = E_DEMODULATOR_TYPE_ATSC;
    }
    else
#endif
#if ENABLE_DVBC
    if( IsDVBCInUse() )
    {
        eDemodType = E_DEMODULATOR_TYPE_DVBC;
    }
    else
#endif
#if ENABLE_DTMB
    if( IsDTMBInUse() )
    {
        eDemodType = E_DEMODULATOR_TYPE_DTMB;
    }
    else
#endif
#if ENABLE_ISDBT
    if( IsISDBTInUse() )
    {
        eDemodType = E_DEMODULATOR_TYPE_ISDBT;
    }
    else
#endif
    if( IsDTVInUse() )
    {
    #if(ENABLE_DVBT)
        if( IsDVBTInUse() )
        {
        #if(ENABLE_DVB_T2)
            if( msAPI_CM_Is_CurChannelT2() ) //DVBT2
            {
                eDemodType = E_DEMODULATOR_TYPE_DVBT2;
            }
            else
        #endif // ENABLE_DVB_T2
            {
                eDemodType = E_DEMODULATOR_TYPE_DVBT;
            }
        }
    #endif
    }

    return eDemodType;
}

BOOL msAPI_DTV_Comm_IsDTVInUse(void)
{
    return ( IsDVBTInUse() \
            ||IsS2InUse()   \
            ||IsAtscInUse() \
            ||IsDTMBInUse() \
            ||IsISDBTInUse()\
            ||IsDVBCInUse()
           );
}

extern BOOL MApp_Is_InAutoScan_DTV(void);

BOOL msAPI_DTV_Comm_IsInDTVScan(void)
{
#if( BLOADER )

#else
    return MApp_Is_InAutoScan_DTV();
#endif

    return FALSE;
}

#if 0
U8 msAPI_DTV_Comm_Get_DVBTorCType(void)
{
#if(ENABLE_T_C_COMBO)
    printf("msAPI_DTV_Comm_Get_DVBTorCType() => %u\n", stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType);
    if( stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType )
        return EN_DVB_C_TYPE;

    return EN_DVB_T_TYPE;

#elif(ENABLE_DVBC) // DVBC only

    return EN_DVB_C_TYPE;

#else // DVBT/DTMB

    return EN_DVB_T_TYPE;

#endif
}
#endif

void msAPI_DTV_Comm_Set_DVBTorCType(BOOL bUseDVBC)
{
#if( !ENABLE_DVBC )
    bUseDVBC = bUseDVBC;
    //bInitCM = bInitCM;
#else
    //static EN_DVB_TYPE s_eLastDvbDemodType = EN_DVB_DEMOD_TYPE_UNKNOWN;

    printf("msAPI_DTV_Comm_Set_DVBTorCType(%u)\n", bUseDVBC);

    if( bUseDVBC )
    {
        stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = EN_DVB_C_TYPE;
    }
    else //if(sourcetpye == UI_INPUT_SOURCE_DTV)
    {
        stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = EN_DVB_T_TYPE;
    }

    //MApp_SaveScanMenuSetting();
    //if( bInitCM )
    {
    //    msAPI_CM_InitDTVDataManager();
    }
#endif
}

#if 1//(ENABLE_API_DTV_SYSTEM_2015)

static TypDtvDbSel s_DTV_Comm_eForceUseDB = E_DTV_DB_NUM;

TypDtvDbSel msAPI_DTV_Comm_Get_DBSel(void)
{
    if( s_DTV_Comm_eForceUseDB < E_DTV_DB_NUM )
    {
        //printf(" Get ForceDbSel=%u, ", s_DTV_Comm_eForceUseDB);
        return s_DTV_Comm_eForceUseDB;
    }

#if(ENABLE_S2)
    if( IsS2InUse())
        return E_DTV_DB_SEL_DVBS;
#endif

#if (ENABLE_CI_PLUS)
    if( msAPI_CM_GetOpMode() ) // CI OP Mode always use DVBT DB
        return E_DTV_DB_SEL_DVBT;
#endif

#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( IsDVBCInUse())
        return E_DTV_DB_SEL_DVBC;
#endif

    return E_DTV_DB_SEL_DVBT;
}

void msAPI_DTV_Comm_Set_ForceDBSel(BOOLEAN bEnForceDBSel, TypDtvDbSel eDBSel)
{
    //PRINT_CURRENT_LINE();
    //printf("msAPI_DTV_Comm_Set_ForceDBSel(bEnForceDBSel=%u, eDBSel=%u)", bEnForceDBSel, eDBSel);

    if( bEnForceDBSel )
        s_DTV_Comm_eForceUseDB = eDBSel;
    else
        s_DTV_Comm_eForceUseDB = E_DTV_DB_NUM;
}

#endif //(ENABLE_API_DTV_SYSTEM_2015)

#endif // ENABLE_DTV

