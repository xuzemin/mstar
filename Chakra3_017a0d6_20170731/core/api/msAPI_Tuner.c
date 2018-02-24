//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Tuner.h
/// MStar Application Interface for Tuner
/// @brief API for tuner settings
/// @author MStar Semiconductor, Inc.
//
// Tuner settings differ from front end suppliers. Please check front end type define
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_TUNER_C

#include "Board.h"

#if ENABLE_DTV

/******************************************************************************/
/*                    Header Files                                            */
/******************************************************************************/
#include <string.h>
#include <stdio.h>

#include "datatype.h"
#include "chip/bond.h"
#include "drvIIC.h"
#include "drvGlobal.h"
#include "drvSYS.h"

#include "msAPI_Global.h"
#include "debug.h"

#include "msAPI_Demod.h"

#include "msAPI_Tuner.h"
#include "msAPI_Timer.h"
#if ENABLE_ATSC
#include "msAPI_Tuner_ATSC.h"
#endif
#include "apiDMX.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
//#include "drvDMD_VD_MBX.h"

#if (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)
#include "SILAB_2151.h"
#endif

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_TopStateMachine.h"
#if (ENABLE_PVR) && (!BLOADER)
#include "MApp_PVR.h"
#endif


#include "COFDM_Demodulator.h"

#if( ENABLE_DVBC )
#include "QAM_Demodulator.h"
#endif

#if ENABLE_DVB_T2
#include "MApp_Scan.h"
#include "demodulator_T2.h"
#endif

#if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
#include "GPIO.h"
#endif

#include "IF_Demodulator.h"

#if ( DEMOD_DVBT_USE_UTOPIA || DEMOD_DVBC_USE_UTOPIA || DEMOD_ISDBT_USE_UTOPIA || DEMOD_DTMB_USE_UTOPIA || DEMOD_ATSC_USE_UTOPIA)
#include "drvDMD_common.h"
#include "drvDMD_ISDBT.h"
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"
#endif

#include "MApp_IR.h"
#include "MApp_Key.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"


#if (ENABLE_CI)
#include "msAPI_CI.h"
#endif



#if ENABLE_SCAN_ONELINE_MSG
#define TUNER_API_DBG_ONELINE(y)       y
#else
#define TUNER_API_DBG_ONELINE(y)
#endif

#if (FRONTEND_DEMOD_T2_TYPE == EMBEDDED_DVBT2_DEMOD)
extern MS_BOOL mdev_CofdmGetSignalStrength(MS_U16 *strength);
#endif

#define TUNER_API_DBG(y)        //y
#define NEW_SCAN_API_DBG(y)     //y
#define TUNER_SERIAL_CONTROL_DBG(y) //y

#define SCAN_DEBUG_CH       0x01
#define SCAN_DEBUG_PAL      0x02
#define SCAN_DEBUG_DVB      0x04

#define SCAN_DEBUG          0x00
#define SCAN_DBG(flag,s)    if (SCAN_DEBUG & flag) { s; }



static EN_DVB_TYPE s_eDvbType = EN_DVB_T_TYPE;


/******************************************************************************/
/*                     Local                                                  */
/******************************************************************************/
static MS_TP_SETTING stCurrentTPSetting;    // current setting of front end
static EN_VSB_CHECK_LOCK_STATE enVSBCheckLockState = STATE_VSB_CHECK_INIT;
static EN_VSB_CHECK_STABLE_STATE enVSBCheckStableState = STATE_VSB_STABLE_INIT;
static BOOLEAN _bTSParallelMode=FALSE;
//static BOOLEAN _bTSByPassMode=FALSE;
//static U32 u32CheckLock_Timer;              // ms


/******************************************************************************/
/*                   Functions                                                */
/******************************************************************************/

/******************************************************************************/
/// API for lnitialize current TP setting::
/******************************************************************************/

void msAPI_Tuner_ResetDemodMode(void)
{
//    _InternalDemodMode=DEMOD_MODE_N_DTV;
    msAPI_Demod_SetCurrentDemodType(E_DEMODULATOR_TYPE_NULL);
}

void msAPI_Tuner_InitCurrentTPSetting(void)
{
    TUNER_API_DBG(printf("msAPI_Tuner_InitCurrentTPSetting()\n"););

    memset(&stCurrentTPSetting, 0, sizeof(stCurrentTPSetting));
#if ENABLE_DVB_T2
    stCurrentTPSetting.u8PLPID = 0xFF;
#endif

#if(ENABLE_ATSC)
    msAPI_Tuner_InitCurrentTPSetting_ATSC();
#endif
}

#if ENABLE_DVB_T2

//extern BOOLEAN DTV_DVB_T_Get_TPS_Parameter(U16 * pu16TPS_parameter, E_SIGNAL_TYPE eSignalType);

void msAPI_Tuner_SetCurrentTPSetting(U8 pu8PlpID)
{
    stCurrentTPSetting.u8PLPID = pu8PlpID;
}

U8 msAPI_Tuner_GetCurrentTPSetting(void)
{
    return stCurrentTPSetting.u8PLPID;
}
#endif

/******************************************************************************/
/// API for lnitialize tuner::
/******************************************************************************/

void msAPI_Tuner_Initialization_BySource(void)
{
    TUNER_API_DBG( PRINT_CUR_FUNCTION(););

    msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, 1);
}

/******************************************************************************/
/// API for lnitialize tuner::
/******************************************************************************/
#if 0
void msAPI_Tuner_InitExternDemod(void)
{
#if ( (FRONTEND_DEMOD_DVBT_TYPE != EMBEDDED_DVBT_DEMOD) && (FRONTEND_DEMOD_DVBC_TYPE != EMBEDDED_DVBC_DEMOD)\
     && (FRONTEND_DEMOD_ISDBT_TYPE != EMBEDDED_ISDBT_DEMOD)&& (FRONTEND_DEMOD_DTMB_TYPE != EMBEDDED_DTMB_DEMOD))
  {
    //printf("%s,%d\n",__FILE__,__LINE__);
    devCOFDM_Init();
  }
#endif

#if 0//ENABLE_S2
    msAPI_Demod_S_Init();
#endif
}
#endif
void PrintTPSetting(MS_TP_SETTING *pstTPSetting)
{
    printf("TP Setting:\n");
    printf(" Frep=%u\n", pstTPSetting->u32Frequency);
    printf(" enBandWidth=%u\n", pstTPSetting->enBandWidth);
    printf(" u8PLPID=%u\n", pstTPSetting->u8PLPID);
    printf(" u8HpLp=%u\n", pstTPSetting->u8HpLp);
    printf(" u8Modulation=%u\n", pstTPSetting->u8Modulation);
    printf(" u32Symbol_rate=%u\n", pstTPSetting->u32Symbol_rate);
}

/******************************************************************************/
/// API for Set RF channel::
/// Set RF channel related parameters, such as RF frequency, modulation type
/// @param pstTPSetting \b IN pointer to RF channel information structure
/******************************************************************************/
void msAPI_Tuner_Tune2RfCh(MS_TP_SETTING *pstTPSetting)
{
    TUNER_API_DBG( printf("msAPI_Tuner_Tune2RfCh()\n"););
    TUNER_API_DBG( PrintTPSetting(pstTPSetting); );

#if TS_FROM_PLAYCARD
    return;
#endif

#if ENABLE_DVB_T2
    ICE_TuneToParams pstT2Setting;
#endif

    //printf("%s,%d\r\n",__FUNCTION__,__LINE__);

#if ENABLE_DVBC
    if( IsDVBCInUse() )
    {
        if( (pstTPSetting->u32Frequency != stCurrentTPSetting.u32Frequency)
          ||(pstTPSetting->u32Symbol_rate != stCurrentTPSetting.u32Symbol_rate)
          ||(pstTPSetting->u8Modulation != stCurrentTPSetting.u8Modulation)
          )
        {
            //printf("%s,%d\r\n",__FUNCTION__,__LINE__);
            //devQAM_SetAutoMode();
            devQAM_SetFrequency(pstTPSetting->u32Frequency, pstTPSetting->u8Modulation, pstTPSetting->u32Symbol_rate, TRUE, (U8)pstTPSetting->bAutoSRFlag, (U8)pstTPSetting->bAutoQamFlag);
            stCurrentTPSetting.u32Frequency = pstTPSetting->u32Frequency;
            stCurrentTPSetting.u32Symbol_rate = pstTPSetting->u32Symbol_rate;
            stCurrentTPSetting.u8Modulation = pstTPSetting->u8Modulation;
        }
        else
        {
            printf("\nDVBC: Same TP Setting => Skip Tune2RF\n");
        }
    }
    else
#endif
    {
        if ((pstTPSetting->u32Frequency != stCurrentTPSetting.u32Frequency) ||
            (pstTPSetting->enBandWidth != stCurrentTPSetting.enBandWidth) ||
            (pstTPSetting->u8HpLp != stCurrentTPSetting.u8HpLp)||
            (pstTPSetting->u8PLPID!= stCurrentTPSetting.u8PLPID)
    #if ENABLE_DVB_T2
            ||(MApp_DTV_Scan_T2_InSignalMonitorStatus())
    #endif
            )
        {
    #if ENABLE_DVB_T2
            if (DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
            {
                pstT2Setting.channel_frequency_khz = pstTPSetting->u32Frequency;
                pstT2Setting.network_type = ICE_network_dvbt2;
                mdev_CofdmSetFrequency(&pstT2Setting,pstTPSetting->enBandWidth);
            }
            else
    #endif
            {
                devCOFDM_SetFrequency(pstTPSetting->u32Frequency, pstTPSetting->enBandWidth, (pstTPSetting->u8HpLp?E_RF_CH_LP:E_RF_CH_HP),pstTPSetting->u8PLPID);
            }
            stCurrentTPSetting.u32Frequency = pstTPSetting->u32Frequency;
            stCurrentTPSetting.enBandWidth = pstTPSetting->enBandWidth;
            stCurrentTPSetting.u8HpLp = pstTPSetting->u8HpLp;
            stCurrentTPSetting.u8PLPID = pstTPSetting->u8PLPID;
        }
        else
        {
            printf("\nDVBT: Same TP Setting => Skip Tune2RF\n");
        }
    }


/* Refine ...
#if ENABLE_DVBC
    #if ENABLE_T_C_COMBO
        if(!IsDVBCInUse())
        {
            if ((pstTPSetting->u32Frequency != stCurrentTPSetting.u32Frequency) ||
                (pstTPSetting->enBandWidth != stCurrentTPSetting.enBandWidth) ||
                (pstTPSetting->u8HpLp != stCurrentTPSetting.u8HpLp)||
                (pstTPSetting->u8PLPID!= stCurrentTPSetting.u8PLPID)
            #if ENABLE_DVB_T2
                ||(MApp_DTV_Scan_T2_InSignalMonitorStatus())
            #endif
                )
            {
            #if ENABLE_DVB_T2
                if (DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
                {
                    pstT2Setting.channel_frequency_khz = pstTPSetting->u32Frequency;
                    pstT2Setting.network_type = ICE_network_dvbt2;
                    mdev_CofdmSetFrequency(&pstT2Setting,pstTPSetting->enBandWidth);
                }
                else
            #endif
                {
                    devCOFDM_SetFrequency(pstTPSetting->u32Frequency, pstTPSetting->enBandWidth,
                        pstTPSetting->u8HpLp?E_RF_CH_LP:E_RF_CH_HP,pstTPSetting->u8PLPID);
                }
                stCurrentTPSetting.u32Frequency = pstTPSetting->u32Frequency;
                stCurrentTPSetting.enBandWidth = pstTPSetting->enBandWidth;
                stCurrentTPSetting.u8HpLp = pstTPSetting->u8HpLp;
                stCurrentTPSetting.u8PLPID = pstTPSetting->u8PLPID;

            }
        }
        else
    #endif
        {
            if ( (pstTPSetting->u32Frequency != stCurrentTPSetting.u32Frequency ||
                pstTPSetting->u32Symbol_rate != stCurrentTPSetting.u32Symbol_rate ||
                pstTPSetting->u8Modulation != stCurrentTPSetting.u8Modulation))
            {
                //printf("%s,%d\r\n",__FUNCTION__,__LINE__);
                //devQAM_SetAutoMode();
                devQAM_SetFrequency(pstTPSetting->u32Frequency, pstTPSetting->u8Modulation, pstTPSetting->u32Symbol_rate, TRUE, (U8)pstTPSetting->bAutoSRFlag, (U8)pstTPSetting->bAutoQamFlag);
                stCurrentTPSetting.u32Frequency = pstTPSetting->u32Frequency;
                stCurrentTPSetting.u32Symbol_rate = pstTPSetting->u32Symbol_rate;
                stCurrentTPSetting.u8Modulation = pstTPSetting->u8Modulation;
            }
        }
#else
    if ((pstTPSetting->u32Frequency != stCurrentTPSetting.u32Frequency) ||
        (pstTPSetting->enBandWidth != stCurrentTPSetting.enBandWidth) ||
        (pstTPSetting->u8HpLp != stCurrentTPSetting.u8HpLp) ||
        (pstTPSetting->u8PLPID!= stCurrentTPSetting.u8PLPID)
    #if ENABLE_DVB_T2
        ||(MApp_DTV_Scan_T2_InSignalMonitorStatus())
    #endif
        )
    {
    #if ENABLE_DVB_T2
        if (msAPI_Demod_GetCurrentDemodType()==E_DEMODULATOR_TYPE_DVBT2)
        {
            pstT2Setting.channel_frequency_khz = pstTPSetting->u32Frequency;
            pstT2Setting.network_type = ICE_network_dvbt2;
            mdev_CofdmSetFrequency(&pstT2Setting,pstTPSetting->enBandWidth);
        }
        else
    #endif
        {
            devCOFDM_SetFrequency(pstTPSetting->u32Frequency, pstTPSetting->enBandWidth,
                                  pstTPSetting->u8HpLp?E_RF_CH_LP:E_RF_CH_HP,pstTPSetting->u8PLPID);
        }
        stCurrentTPSetting.u32Frequency = pstTPSetting->u32Frequency;
        stCurrentTPSetting.enBandWidth = pstTPSetting->enBandWidth;
        stCurrentTPSetting.u8HpLp = pstTPSetting->u8HpLp;
        stCurrentTPSetting.u8PLPID = pstTPSetting->u8PLPID;
    }
  #endif
*/
}

/******************************************************************************/
/// API for Check is same RF channel::
/// @param pstTPSetting \b IN pointer to RF channel information structure
/// @return same RF or not
/******************************************************************************/
BOOLEAN msAPI_Tuner_IsSameRfChannel(MS_TP_SETTING *pstTPSetting)
{
    if ( pstTPSetting->u32Frequency == stCurrentTPSetting.u32Frequency )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************/
/// API for power on off front end::
/// @param bPower \b IN power on or off
/******************************************************************************/
void msAPI_Tuner_Set_DemodPower(BOOLEAN bPower)
{
    static EN_DEMODULATOR_TYPE s_eLastPowerOnDemod = E_DEMODULATOR_TYPE_NULL;
    EN_DEMODULATOR_TYPE eCurSrcNeedDemod = msAPI_DTV_Comm_Get_CurSrcUseDemodType();


    TUNER_API_DBG(printf("msAPI_Tuner_Set_DemodPower(bPower=%u)\n", bPower););
    TUNER_API_DBG(printf("eCurSrcNeedDemod=%u,%s)\n", eCurSrcNeedDemod, msAPI_Demod_Get_DemodTypeName(eCurSrcNeedDemod)););


    //1. When enable power, check which (new) type of demod/tuner type to power on
    //2. When disable power, get current type of demod/tuner type to power down
    if( bPower == TRUE ) // Power on
    {
        msAPI_Demod_Set_Power(eCurSrcNeedDemod, ENABLE);

        s_eLastPowerOnDemod = eCurSrcNeedDemod;
    }
    else // Power off
    {
        if( s_eLastPowerOnDemod != E_DEMODULATOR_TYPE_NULL )
        {
            msAPI_Demod_Set_Power(s_eLastPowerOnDemod, DISABLE);
            s_eLastPowerOnDemod = E_DEMODULATOR_TYPE_NULL;
        }
    }
}

/*
U8 msAPI_Tuner_GetSignalSNRValue(void)
{
#if 1 // use demod api
    return msAPI_Demod_Get_SNR(msAPI_Demod_GetCurrentDemodType());

#else

#if ENABLE_T_C_COMBO
    return (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
            ? (U8)devQAM_GetSignalToNoiseRatio()
            : (U8)devCOFDM_GetSignalToNoiseRatio();
#elif ENABLE_DVBC
    return (U8)devQAM_GetSignalToNoiseRatio();
#else
    return (U8)devCOFDM_GetSignalToNoiseRatio();
#endif
#endif
}
*/

/*
U8 msAPI_Tuner_GetSingalSNRPercentage(void)
{
    U16 temp = msAPI_Demod_Get_SNR(msAPI_Demod_GetCurrentDemodType());

    if ( temp >= 35 )
    {
        return 100;
    }
    else
    {
        return (U8)(temp*100/35);
    }
}
*/

WORD msAPI_Tuner_GetSignalQualityPercentage(void)
{
    U16 wPercentage = 0;

#if TS_FROM_PLAYCARD
    wPercentage = 80;
    return wPercentage;
#endif

#if 1 // Use demod API
    wPercentage = msAPI_Demod_Get_SignalQualityPercentage(msAPI_Demod_GetCurrentDemodType());

#else

    //printf("%s,%d\r\n",__FUNCTION__,__LINE__);
#if (ENABLE_S2)
    if (IsS2InUse())
    {
        devCOFDM_GetSignalQuality(&wPercentage);
    }
    else
#endif
    {
    #if ENABLE_T_C_COMBO
        if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
        {
            devQAM_GetSignalQuality(&wPercentage);
        }
        else
        {
        #if ENABLE_DVB_T2
            if (DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
            {
                mdev_CofdmGetSignalQuality(&wPercentage);
            }
            else
        #endif
            {
                devCOFDM_GetSignalQuality(&wPercentage);
            }
        }
    #elif ENABLE_DVBC
        devQAM_GetSignalQuality(&wPercentage);
    #else
      #if ENABLE_DVB_T2
        if (DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
        {
            //printf("%s,%d\r\n",__FUNCTION__,__LINE__);
            mdev_CofdmGetSignalQuality(&wPercentage);
        }
        else
      #endif
        {
            devCOFDM_GetSignalQuality(&wPercentage);
        }
    #endif
    }
#endif

    return wPercentage;
}

BOOLEAN msAPI_Tuner_GetBER(float *ber)
{
    *ber = 0;

#if( ENABLE_DEMOD_DVBT || ENABLE_DEMOD_DVBT2 )
    EN_DEMODULATOR_TYPE eCurDemod = msAPI_Demod_GetCurrentDemodType();

  #if( ENABLE_DEMOD_DVBT2 )
    if( E_DEMODULATOR_TYPE_DVBT2 == eCurDemod )
        return msAPI_Demod_DVBT2_Get_PostViterbiBer(ber);
  #endif

  #if( ENABLE_DEMOD_DVBT )
    if( E_DEMODULATOR_TYPE_DVBT == eCurDemod )
        return msAPI_Demod_DVBT_Get_PostViterbiBer(ber);
  #endif

#endif

    return FALSE;
/*
#if ENABLE_T_C_COMBO
    return (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  ? TRUE : devCOFDM_GetBER(ber);
#elif ENABLE_DVBC
    UNUSED(ber);
    return TRUE;
#else
    return devCOFDM_GetBER(ber);
#endif
*/
}

BOOLEAN msAPI_Tuner_Get_CELL_ID( WORD * cell_id)
{
    //BOOLEAN eResult;

//#if ENABLE_T_C_COMBO
    * cell_id = 0;
    return (IsDVBCInUse())  ? TRUE : devCOFDM_Get_CELL_ID(cell_id);
//#elif ENABLE_DVBC
//    * cell_id = 0;
//    eResult = TRUE;
//#else
//    eResult = devCOFDM_Get_CELL_ID(cell_id);
//#endif
//    return eResult;
}

BOOLEAN msAPI_Tuner_Get_PLP_ID( U8  * pu8plp_id)
{
    *pu8plp_id=stCurrentTPSetting.u8PLPID;
    return TRUE;
}

U8 msAPI_Tuner_Get_HpLp( void)
{
    return stCurrentTPSetting.u8HpLp;
}

#if( ENABLE_HIERARCHY )
BOOLEAN msAPI_Tuner_Is_HierarchyOn(void)
{
    printf("msAPI_Tuner_Is_HierarchyOn()\n CurDemod=%u\n", msAPI_Demod_GetCurrentDemodType());

    return (msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)  ? FALSE : devCOFDM_Is_Hierarchy_On();

}
#endif

// This function is only for UI...
BOOLEAN msAPI_Tuner_GetSignalModulMode(U16 *pu16Modul_Mode)
{
    BOOLEAN bRtn = FALSE;
    EN_DEMODULATOR_TYPE eCurDemod = msAPI_Demod_GetCurrentDemodType();


    printf("msAPI_Tuner_GetSignalModulMode() - eCurDemod=%u\n", eCurDemod);

#if(ENABLE_S2)
    if( eCurDemod == E_DEMODULATOR_TYPE_DVBS_S2)
    {
        bRtn = msAPI_Demod_S_Get_SignalModulMode(pu16Modul_Mode);
    }
    else
#endif
#if(ENABLE_DVBC)
    if( eCurDemod == E_DEMODULATOR_TYPE_DVBC )
    {
        *pu16Modul_Mode = devQAM_GetCurrentQAM();
        bRtn = TRUE;
    }
    else
#endif
#if(ENABLE_DVB_T2 && (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT) )
    if( eCurDemod == E_DEMODULATOR_TYPE_DVBT2)
    {
        DTV_DVB_T2_Get_L1_Parameter(pu16Modul_Mode, T2_MODUL_MODE);
        bRtn = TRUE;
    }
    else
#endif
    {
        bRtn = devCOFDM_Get_Modul_Mode(pu16Modul_Mode);
    }

    printf(" => ModulMode=%u\n", *pu16Modul_Mode);

    return bRtn;

#if 0
#if ENABLE_T_C_COMBO
    if( msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
    {
        *pu16Modul_Mode = devQAM_GetCurrentQAM();
        return TRUE;
    }
    else
    {
    #if 0 //ENABLE_DVB_T2 mark for compile error,need T2 team offer this function
        if(DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
            return DTV_DVB_T_Get_TPS_Parameter(pu16Modul_Mode, TS_MODUL_MODE);
        else
    #endif
    #if(FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
        {
            if(DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
            {
                DTV_DVB_T2_Get_L1_Parameter(pu16Modul_Mode, T2_MODUL_MODE);
                return TRUE;
            }
        }
    #endif
    #if ENABLE_S2
        if (IsS2InUse())
        {
            return msAPI_Demod_S_Get_SignalModulMode(pu16Modul_Mode);
            /*BOOLEAN ret;
            DEMOD_MS_FE_CARRIER_PARAM  pParam;
            ret=MDrv_DVBS_Demod_GetParam(&pParam);
            *wModul_Mode=(WORD)pParam.SatParam.eConstellation;
            return ret;*/
        }
        else
    #endif
        {
            return devCOFDM_Get_Modul_Mode(pu16Modul_Mode);
        }
    }
#elif ENABLE_DVBC
    *pu16Modul_Mode = 0;
    return TRUE;
#else
    if (devCOFDM_Get_Modul_Mode(pu16Modul_Mode))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#endif
#endif
}

void msAPI_Check_Lock_State_Init(void)
{
    enVSBCheckLockState = STATE_VSB_CHECK_INIT;
    enVSBCheckStableState = STATE_VSB_STABLE_INIT;
}

BOOLEAN msAPI_Tuner_CheckLock_DetectUserKey(void)
{
    // Check User Key
#if (!BLOADER)
    MApp_ProcessUserInput();
    switch ( u8KeyCode )
    {
        case KEY_MENU:
        case KEY_EXIT:
            return TRUE;
            break;
        default:
            break;
    }
#endif

    return FALSE;
}

BOOLEAN msAPI_Tuner_CheckLock(BOOLEAN *CheckLockResult, BOOLEAN fScan)
{
    return msAPI_Demod_CheckLock(CheckLockResult, fScan);
}

#if (ENABLE_PVR) && (!BLOADER)
static U8 ParallelInterfaceFlag = 3;
#endif


#define DEBUG_TUNER_SERIAL_CTRL(x)  x

void msAPI_Tuner_Serial_Control(BOOLEAN bParallelMode, BOOLEAN bPVRMode)
{
    BOOLEAN bEnable = FALSE, bScanMode = 0;
    DMX_FLOW eDmxFlow = DMX_FLOW_PLAYBACK;

    UNUSED(bEnable);

    DEBUG_TUNER_SERIAL_CTRL( PRINT_CURRENT_LINE(); );
    DEBUG_TUNER_SERIAL_CTRL(printf("msAPI_Tuner_Serial_Control(bParallelMode=%u, bPVRMode=%u)\n", bParallelMode, bPVRMode););

    if( bPVRMode )
    {
        eDmxFlow = DMX_FLOW_PVR;
        DEBUG_TUNER_SERIAL_CTRL(printf("eDmxFlow = DMX_FLOW_PVR\n"););
    }
    else
    {
        eDmxFlow = DMX_FLOW_PLAYBACK;
        DEBUG_TUNER_SERIAL_CTRL(printf("eDmxFlow = DMX_FLOW_PLAYBACK\n"););
    }


#if ENABLE_CI
  #if (!TS_SERIAL_OUTPUT_IF_CI_REMOVED)
    bParallelMode = TRUE;
  #endif
#endif

    _bTSParallelMode = bParallelMode;

#if ENABLE_CI
    if (bParallelMode)
    {
        bEnable = FALSE;
    }
    else
    {
        bEnable = TRUE;
    }
#else
    UNUSED(bParallelMode);

  #if (ENABLE_ATSC)
    if (IsAtscInUse())
        bEnable = (!TS_PARALLEL_ATSC_OUTPUT);
  #endif

  #if (ENABLE_S2)
    if (IsS2InUse())
        bEnable = (!TS_PARALLEL_S2_OUTPUT);
  #endif

  #if (ENABLE_DVBT)
    if (IsDVBTInUse())
        bEnable = (!TS_PARALLEL_DVBT_OUTPUT);
  #endif

  #if (ENABLE_DVBC)
    if (IsDVBCInUse())
        bEnable = (!TS_PARALLEL_DVBC_OUTPUT);
  #endif

  #if (ENABLE_DTMB)
    if (IsDTMBInUse())
        bEnable = (!TS_PARALLEL_DTMB_OUTPUT);
  #endif

  #if (ENABLE_ISDBT)
    if (IsISDBTInUse())
        bEnable = (!TS_PARALLEL_ISDBT_OUTPUT);
  #endif

#endif // #if ENABLE_CI


#if TS_FROM_PLAYCARD
    MApi_DMX_FlowSet( eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    return;
#endif


#if( BLOADER )
    bScanMode = TRUE;
#else
    bScanMode = MApp_Is_InAutoScan_DTV();
#endif


#if ENABLE_ATSC
    if(IsAtscInUse())
    {
      #if (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
        MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
        return;
      #endif
    }
#endif // #if ENABLE_ATSC


#if ENABLE_S2
    if( IsS2InUse())
    {
    #if(FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD)
        #if (ENABLE_CI)
         if (msAPI_CI_CardDetect() && !bScanMode)
         {
             MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, !bEnable);
         }
         else
        #endif
         {
             MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, !bEnable);
         }
    #elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
         MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, !bEnable);

    #endif


    #if (ENABLE_PVR) && (!BLOADER)
        if(IsS2InUse())
        {
            devCOFDM_S2_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
        }
        else
        if ((ParallelInterfaceFlag != E_PARALLEL_INTERFACE) && MApp_PVR_IsRecording())
        {
            devCOFDM_S2_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
            ParallelInterfaceFlag = E_PARALLEL_INTERFACE;
        }
    #else
        devCOFDM_S2_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
    #endif
        return;


    }

#endif // #if ENABLE_S2


#if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        //if (bEnable == TRUE)
        {
            #if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
            #if (ENABLE_CI)
            if (msAPI_CI_CardDetect() && !bScanMode)
            {
                MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, !bEnable);
            }
            else
            #endif
            {
                MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, !bEnable);
            }
            #elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
            MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, !bEnable);

            #endif
        }

    #if (ENABLE_PVR) && (!BLOADER)
        if ((ParallelInterfaceFlag != E_PARALLEL_INTERFACE) && MApp_PVR_IsRecording())
        {
            devCOFDM_DVBT_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
            ParallelInterfaceFlag = E_PARALLEL_INTERFACE;
        }
    #else
        devCOFDM_DVBT_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
    #endif

    }
#endif // #if ENABLE_DVBT


#if ENABLE_DVBC
    if(IsDVBCInUse())
    {
        //if (bEnable == TRUE)
        {
            #if(FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD)
            #if (ENABLE_CI)
            if (msAPI_CI_CardDetect() && !bScanMode)
            {
                MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, !bEnable);
            }
            else
            #endif
            {
                MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, !bEnable);
            }
            #elif(FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
            MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, !bEnable);
            #endif
        }
    #if (ENABLE_PVR) && (!BLOADER)
        if ((ParallelInterfaceFlag != E_QAM_PARALLEL_INTERFACE) && MApp_PVR_IsRecording())
        {
            devQAM_SwitchTransportSteamInferface(E_QAM_PARALLEL_INTERFACE);
            ParallelInterfaceFlag = E_QAM_PARALLEL_INTERFACE;
        }
    #else
        devQAM_SwitchTransportSteamInferface(E_QAM_PARALLEL_INTERFACE);
    #endif

    }

#endif // #if ENABLE_DVBC


#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
    #if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
        MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, !bEnable);

    #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
          ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
        MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, !bEnable);
    #endif

    #if (ENABLE_PVR) && (!BLOADER)
        if ((ParallelInterfaceFlag != E_PARALLEL_INTERFACE) && MApp_PVR_IsRecording())
        {
            devCOFDM_DTMB_SwitchTransportSteamInferface(E_SERIAL_INTERFACE);
            ParallelInterfaceFlag = E_PARALLEL_INTERFACE;
        }
    #else
        devCOFDM_DTMB_SwitchTransportSteamInferface(E_SERIAL_INTERFACE);
    #endif
    }
#endif // #if ENABLE_DTMB


#if ENABLE_ISDBT
    if(IsISDBTInUse())
    {
        //if (bEnable == TRUE)
        {
            #if(FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
            #if (ENABLE_CI)
            if (msAPI_CI_CardDetect() && !bScanMode)
            {
                MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, !bEnable);
            }
            else
            #endif
            {
                MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, !bEnable);
            }
            #elif(FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
            MApi_DMX_FlowSet(eDmxFlow, DMX_FLOW_INPUT_EXT_INPUT1, FALSE, TRUE, !bEnable);
            #endif
        }

    #if (ENABLE_PVR) && (!BLOADER)
        if ((ParallelInterfaceFlag != E_PARALLEL_INTERFACE) && MApp_PVR_IsRecording())
        {
            devCOFDM_ISDBT_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
            ParallelInterfaceFlag = E_PARALLEL_INTERFACE;
        }
    #else
        devCOFDM_ISDBT_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
    #endif


    }
#endif // #if ENABLE_ISDBT

}

FUNCTION_RESULT msAPI_Tuner_CheckSignalStrength(WORD *wStrength)
{
#if TS_FROM_PLAYCARD
    WORD wSignalStrength = 0; // fix coverity 207475

    *wStrength = 80;
    return E_RESULT_SUCCESS;
#endif


#if (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)

  #if( ENABLE_S2 )
    if( IsS2InUse() )
    {
        WORD u16SignalStrength = 0;
        if( FALSE == msAPI_Demod_S_Get_SignalStrength(&u16SignalStrength) )
        {
            *wStrength = 0;
            return E_RESULT_FAILURE;
        }
        *wStrength = u16SignalStrength;
    }
    else
  #endif
    {
        float fRFLevel = 0.0f;
        MS_S8 sRFLevel = 0;

        if( FALSE == mdev_GetSignalStrength(&fRFLevel) )
        {
            *wStrength = 0; //for patch
            return E_RESULT_FAILURE;
        }
        else
        {
            sRFLevel = (MS_S8)fRFLevel;
        }

        //printf("\n[%d];result=%d;result=%d.\n",__LINE__,sRFLevel,(char)sRFLevel);

        if(sRFLevel > -35)
        {
            *wStrength = 100;
        }
        else if (sRFLevel > -100)
        {
            *wStrength = (U16)( sRFLevel + 100.0 + 0.5);
        }
        else
        {
            *wStrength = 0;
        }
    }

    return E_RESULT_SUCCESS;

#else
    EN_DEMODULATOR_TYPE eCurDemod = msAPI_Demod_GetCurrentDemodType();
    //printf("\nmsAPI_Tuner_CheckSignalStrength()- eCurDemod=%u\n", eCurDemod);

    WORD wSignalStrength = 0; // fix coverity 207475

    if( FALSE == msAPI_Demod_Get_SignalStrength(eCurDemod, &wSignalStrength) )
    {
        *wStrength = 0;
        return E_RESULT_FAILURE;
    }

    *wStrength = wSignalStrength;
    return E_RESULT_SUCCESS;

#endif

}

FUNCTION_RESULT msAPI_Tuner_GetCurTPSetting(MS_TP_SETTING *pstCurTPSetting)
{
    // Coverity 215646
    BYTE bLockStatus = FE_NOT_LOCK;

    if ((msAPI_Tuner_CheckLock(&bLockStatus, FALSE)== TRUE))
    {
        if (bLockStatus == FE_LOCK)
            memcpy(pstCurTPSetting,&stCurrentTPSetting,sizeof(MS_TP_SETTING));
    }

    return E_RESULT_SUCCESS;
}

//*************************************************************************
//Function name:    msAPI_Tuner_SwitchSource
//Passing parameter:    EN_DVB_TYPE eType: Demod type
//Return parameter:     none
//Description:      change demod source
//*************************************************************************
void msAPI_Tuner_SwitchSource(EN_DVB_TYPE eDvbType, BOOLEAN bInit)
{
    TUNER_API_DBG(printf("msAPI_Tuner_SwitchSource(etype=%d,bInit=%d)\n", eDvbType, bInit););

    /*if( s_eDvbType == etype )
    {
        return;
    }*/

    s_eDvbType = eDvbType;

    if( bInit == FALSE )
    {
        return;
    }

    msAPI_Tuner_InitCurrentTPSetting();

    // Init demod for current source
    msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_SOURCE, msAPI_DTV_Comm_Get_CurSrcUseDemodType() );

#if 1 // 20150910
  #if (ENABLE_CI)
    if( IsDVBInUse() && msAPI_CI_CardDetect() )
    {
    #if(ENABLE_CI_PLUS)
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_CI_IN_USE);
    #else
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_CI_BY_PASS);
    #endif
    }
    else
  #endif
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_NORMAL);
#else

// todo
  #if (ENABLE_CI)
    if (msAPI_Tuner_IsParallelMode())
    {
        msAPI_Tuner_Serial_Control(TRUE,FALSE);
    }
    else
    {
        msAPI_Tuner_Serial_Control(FALSE,FALSE);
    }
  #else
    msAPI_Tuner_Serial_Control(FALSE,FALSE);
  #endif
#endif
}

#if (ENABLE_DVBC )//TODO need add DVB-C case

//*************************************************************************
//Function name:    msAPI_Tuner_GetSourceType
//Passing parameter:    none
//Return parameter:     EN_DVB_TYPE
//Description:      get demod source type
//*************************************************************************
EN_DVB_TYPE msAPI_Tuner_GetSourceType(void)
{
    return s_eDvbType;
}

void msAPI_Tuner_Set_DvbType(EN_DVB_TYPE eDvbType)
{
    s_eDvbType = eDvbType;
}

//*************************************************************************
//Function name:    msAPI_Tuner_SetAntenna
//Passing parameter:    Antenna
//Return parameter:     none
//Description:      change tuner Antenna
//*************************************************************************
void msAPI_Tuner_SetAntenna(BOOLEAN bIsCATV)
{
#if(FRONTEND_TUNER_TYPE == ALPS_TDQG9_601A_TUNER || FRONTEND_TUNER_TYPE == TCL_DTC78WI_3E_TUNER)
    devTunerSetAntenna(bIsCATV);
#else
    UNUSED(bIsCATV);
#endif
}

U8 msAPI_Tuner_GetDspStatus(void)
{
#if DEMOD_DVBT_USE_UTOPIA ||DEMOD_DVBC_USE_UTOPIA
  #if 1
    switch (msAPI_Demod_GetCurrentDemodType())
    {
        case E_DEMODULATOR_TYPE_DVBT:
            return 0x01;
        case E_DEMODULATOR_TYPE_DVBC:
            return 0x02;
        default:
            return 0xFF;
    }
  #else
    switch (_InternalDemodMode)
    {
        case DEMOD_MODE_DVB_T:
            return 0x01;
        case DEMOD_MODE_DVB_C:
            return 0x02;
        default:
            return 0xFF;
    }
  #endif
#else
     switch (msAPI_Demod_GetCurrentDemodType())
    {
        case E_DEMODULATOR_TYPE_DVBT:
            return 0x01;
        case E_DEMODULATOR_TYPE_DVBC:
            return 0x02;
        default:
            return 0xFF;
    }
    //return INTERN_DVBT_GetDspStatus();
#endif
}

#endif

#if 0
#if (!TS_SERIAL_OUTPUT_IF_CI_REMOVED)
//todo: only support internal DEMOD
#if (((FRONTEND_DEMOD_DVBT_TYPE != EMBEDDED_DVBT_DEMOD)&&   \
        (FRONTEND_DEMOD_DVBC_TYPE != EMBEDDED_DVBC_DEMOD)&&  \
        (FRONTEND_DEMOD_ISDBT_TYPE != EMBEDDED_ISDBT_DEMOD)&&   \
        (FRONTEND_SECOND_DEMOD_TYPE!= EMBEDDED_DVBT_DEMOD)&&    \
        (FRONTEND_SECOND_DEMOD_TYPE!= EMBEDDED_DVBC_DEMOD)))
#error "only internal DEMOD support parallel always"
#endif
#endif
#endif

// bByPass=0  ==> ExtDemod    ==> CI  to TSP
// bByPass=1  ==> InterDemod ==> Demod to TSP
#if 0
DMX_FILTER_STATUS msAPI_Tuner_SetByPassMode(BOOLEAN bByPass, BOOLEAN bPVRMode)
{
    DMX_FILTER_STATUS eResult = DMX_FILTER_STATUS_OK;

    DEBUG_TUNER_SERIAL_CTRL( PRINT_CURRENT_LINE(); );
    DEBUG_TUNER_SERIAL_CTRL( printf(" msAPI_Tuner_SetByPassMode(ByPass=%u, PVR=%u)\n", bByPass, bPVRMode); );

#if (!TS_SERIAL_OUTPUT_IF_CI_REMOVED)
    _bTSByPassMode = bByPass;

#if (ENABLE_S2)
    if( IsS2InUse() )
    {
        msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_CHANNEL, E_DEMODULATOR_TYPE_DVBS_S2);
        MDrv_SYS_SetPadMux(E_TS0_PAD_SET, E_PARALLEL_IN);
        eResult = MApi_DMX_FlowSet(bPVRMode?DMX_FLOW_PVR:DMX_FLOW_PLAYBACK, bByPass?DMX_FLOW_INPUT_DEMOD:DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    }
    else
#endif

 #if (ENABLE_DVB_T2)
    if( msAPI_CM_Is_CurChannelT2() ) //(u8Plpid != 0xFF)
    {
        mdev_ControlTSOutput(ENABLE);
        msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_CHANNEL, E_DEMODULATOR_TYPE_DVBT2);
    #if(FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB123X_DVBT2 || FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB101A_DVBT2)
        mdev_Set_Current_DEMOD_TYPE(E_COFDM_EXTERNAL_DVBT2);
        MDrv_SYS_SetPadMux(E_TS1_PAD_SET, E_PARALLEL_IN);
    #endif
        eResult = MApi_DMX_FlowSet(bPVRMode?DMX_FLOW_PVR:DMX_FLOW_PLAYBACK, bByPass?DMX_FLOW_INPUT_DEMOD:DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    }
    else
 #endif
    {
    #if ENABLE_DVB_T2
        mdev_ControlTSOutput(DISABLE);
    #if(FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB123X_DVBT2 || FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB101A_DVBT2)
        mdev_Set_Current_DEMOD_TYPE(E_COFDM_INVALID);
        MDrv_SYS_SetPadMux(E_TS1_PAD_SET, E_PARALLEL_OUT);
        MDrv_SYS_SetPadMux(E_TS0_PAD_SET, E_PARALLEL_IN);
    #endif
    #endif
        eResult = MApi_DMX_FlowSet(bPVRMode?DMX_FLOW_PVR:DMX_FLOW_PLAYBACK, bByPass?DMX_FLOW_INPUT_DEMOD:DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    }

#if 0//(ENABLE_CI_PLUS) && (ENABLE_DVB_T2)
    if (FALSE == bByPass)
    {
        msAPI_DTV_Comm_SetCiTuneStatus(FALSE);
    }
#endif

#else
    UNUSED(bByPass);
    UNUSED(bPVRMode);
#endif

    return eResult;
}

BOOLEAN msAPI_Tuner_IsByPassMode(void)
{
    return _bTSByPassMode;
}
#endif

BOOLEAN msAPI_Tuner_IsParallelMode(void)
{
    return _bTSParallelMode;
}

#if (ENABLE_DVBC)
void msAPI_Tuner_UpdateTPSetting(void)
{
//#if (ENABLE_T_C_COMBO)
    if (IsDVBCInUse())
//#endif
    {
        stCurrentTPSetting.u32Symbol_rate = devQAM_GetCurrentSymbolRate();
        stCurrentTPSetting.u8Modulation = devQAM_GetCurrentQAM();
    }
}
#endif


#endif  //ENABLE_DTV

#undef MSAPI_TUNER_C

