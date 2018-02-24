#ifndef _MSAPI_DTV_COMMON_H_
#define _MSAPI_DTV_COMMON_H_


#include "Board.h"


#include "datatype.h"
#include "Tuner.h"

#if( ENABLE_DTV )

#include "msAPI_Demod_Basic.h"


/// TP Setting
typedef struct
{
    U32 u32Frequency; ///< Frequency, 50,000 ~ 860,000 Khz
    RF_CHANNEL_BANDWIDTH enBandWidth;   ///< Bandwidth
    U8 u8PLPID;
    U8 u8HpLp;

    U8 u8Modulation;
    U32 u32Symbol_rate;
    BOOLEAN bAutoSRFlag;
    BOOLEAN bAutoQamFlag;
} MS_TP_SETTING;

#if (ENABLE_CI_PLUS)
U8 msAPI_DTV_Comm_GetPLPID(void);
void msAPI_DTV_Comm_SetPLPID(U8 u8CiTune_PLPID);

U8 msAPI_DTV_Comm_GetIsCiTuneStatus(void);
void msAPI_DTV_Comm_SetCiTuneStatus(BOOLEAN bIsCiTune);
#endif

EN_DEMODULATOR_TYPE msAPI_DTV_Comm_Get_CurSrcUseDemodType(void);

BOOL msAPI_DTV_Comm_IsDTVInUse(void);

BOOL msAPI_DTV_Comm_IsInDTVScan(void);

//U8 msAPI_DTV_Comm_Get_DVBTorCType(void);
void msAPI_DTV_Comm_Set_DVBTorCType(BOOL bUseDVBC);
//--------------------------------------------------------------------------------

#if 1//(ENABLE_API_DTV_SYSTEM_2015)

typedef enum
{
    E_DTV_DB_SEL_DVBT,

#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    E_DTV_DB_SEL_DVBC,
#endif

#if(ENABLE_S2)
    E_DTV_DB_SEL_DVBS,
#endif

    E_DTV_DB_NUM,

} TypDtvDbSel;

TypDtvDbSel msAPI_DTV_Comm_Get_DBSel(void);

void msAPI_DTV_Comm_Set_ForceDBSel(BOOLEAN bEnForceDBSel, TypDtvDbSel eDBSel);

#endif // ENABLE_API_DTV_SYSTEM_2015

//==================================================================

#endif // ENABLE_DTV

#endif

