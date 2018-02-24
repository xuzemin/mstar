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
// (MStar Confidential Information!�L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDEV_COFDM_DEMODULATOR_C_
#define _MDEV_COFDM_DEMODULATOR_C_

//******************************************************************************

#include "Board.h"


#if (ENABLE_DVB_T2)
#include "apiDMX.h"
#include "drvPCMCIA.h"
#include "drvSYS.h"
#include "demodulator_T2.h"
#include "drvIIC.h"
#include "debug.h"
#include "MApp_Scan.h"
#include "msAPI_Memory.h"

#ifdef HW_PROFILE
#include "profile_helper/ProfileHelper.h"
#endif

#if (FRONTEND_DEMOD_T2_TYPE != MSTAR_MSB124X_DVBT)
//#include "msb124x.c"
//#include "msb124x.h"
#if DEMOD_DVBT_USE_UTOPIA
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"
#else
#include "INTERN_DVBT.h"
#include "INTERN_DVBC.h"
#endif
#endif

#include "mapp_si.h"

#if 0//FAST_TURN_ON
#include "ICE_latest.h"
#endif

//******************************************************************************

#if (FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB123X_DVBT2)
#include "msb123x.c"
#include "msb123x.h"
#elif (FRONTEND_DEMOD_T2_TYPE == MSTAR_MSB101A_DVBT2)
#include "MSB1233C.c"
#include "MSB1233C.h"
#endif

//******************************************************************************

static CUR_COFDM_CFG eCurCofdmCfg = E_COFDM_INVALID;
static MS_BOOL bDemodDTVInitOK = FALSE;
static MS_BOOL bTunerInitOK = FALSE;
static ST_MAPI_DEMODULATOR_FUN *pstDvbt2Drv;
static MS_BOOL bDvbt2DemodExist = FALSE;

#define ATV_PAL_I                   FALSE
#define ATV_PAL_BG                  TRUE
#define DEFAULT_CCI_ATV_SYSTEM      ATV_PAL_BG

#if 0//FAST_TURN_ON
extern ICE_LatestSwParams ice_last_sw_params;
#endif
extern ST_MAPI_DEMODULATOR_FUN* DeviceDemodCreate(void);

//******************************************************************************
//#define _DEBUG_V
#ifndef _DEBUG_V
#define printf(...)         ((void)0)
#endif

#define COFDM_DBG(x)        //x

/***************************************************************************************/

CUR_COFDM_CFG mdev_Get_Current_DEMOD_TYPE(void)
{
    return eCurCofdmCfg;
}

void mdev_Set_Current_DEMOD_TYPE(CUR_COFDM_CFG sDemodType)
{
    printf("\r\nmdev_Set_Current_DEMOD_TYPE=0x%x\n", sDemodType);
    eCurCofdmCfg=sDemodType;
}

MS_BOOL mdev_Cofdm_MSB123X_Ready(void)
{
     return bDvbt2DemodExist;
}

MS_BOOL mdev_Cofdm_MSB123X_TriState(MS_BOOL bSetHiZ)
{
    MS_BOOL bRet=TRUE;

    if((pstDvbt2Drv->bMSB123X_Ready)==FALSE && mdev_Cofdm_MSB123X_Ready())
    {
        pstDvbt2Drv->Connect(E_DEVICE_DEMOD_DVB_T2);
        bRet = pstDvbt2Drv->Power_On_Initialization();
    }

    if((pstDvbt2Drv->bMSB123X_Ready)==TRUE)
    {
        if(bSetHiZ==TRUE)
        {
            bRet &= pstDvbt2Drv->ExtendCmd(0x80, FALSE, 0, NULL);//Turn off extend demod IF AGC
            bRet &= pstDvbt2Drv->ExtendCmd(0x81, FALSE, 0, NULL);//Turn off extend demod TS out
        }
        else
        {
            bRet &= pstDvbt2Drv->ExtendCmd(0x80, TRUE, 0, NULL);//Turn on extend demod IF AGC
            bRet &= pstDvbt2Drv->ExtendCmd(0x81, TRUE, 0, NULL);//Turn on extend demod TS out
        }
    }
    return bRet;
}

MS_BOOL  mdev_CofdmDeviceQuery( void )
{
    MS_U8 u8Data;

    if (MDrv_IIC_ReadByte(DEMOD_SLAVE_ID, 0, &u8Data) == FALSE)
    {//Fail
        printf("MSB1231 NO exist\n");
        return FALSE;
    }
    else
    {//Success
        printf("MSB1231 exist \n");
        return TRUE;
    }
}

void mdev_CofdmHWireReset(void)
{
    // hard-wire reset pin
    //Demodulator_OFF();
    //OS_DELAY_TASK(10);
    //Demodulator_ON();
}

void mdev_CofdmInit(void)
{
    printf("---------------------mdev_CofdmInit\n");

    mdev_CofdmHWireReset();

    if( pstDvbt2Drv == NULL )
    {
        pstDvbt2Drv = DeviceDemodCreate();
    }

    eCurCofdmCfg = E_COFDM_INVALID;

    bDvbt2DemodExist = mdev_CofdmDeviceQuery(); //check MSB1231 I2C first and once
}

void mdev_Write_Demod_Imux(void)
{
}

static MS_BOOL mdev_CofdmPowerOnInitialization(CUR_COFDM_CFG eSetCofdmCfg)
{
    MS_BOOL bRet = TRUE;

    UNUSED(eSetCofdmCfg);

    printf("\r\nmdev_CofdmPowerOnInitialization");

    if(eCurCofdmCfg!=E_COFDM_EXTERNAL_DVBT2)
    {
        eCurCofdmCfg=E_COFDM_EXTERNAL_DVBT2;
		pstDvbt2Drv->Connect(E_DEVICE_DEMOD_DVB_T2);

        if((pstDvbt2Drv->bMSB123X_Ready)==FALSE && mdev_Cofdm_MSB123X_Ready())
        {
            bRet = pstDvbt2Drv->Power_On_Initialization();
        }
    }

    return bRet;
}

void mdev_CofdmControlPowerOnOff(BOOLEAN bPowerOn)
{
    MS_BOOL bPowerOnGood = TRUE;

    printf("---------------------mdev_CofdmControlPowerOnOff   bPowerOn=%d\n",bPowerOn);

    if(pstDvbt2Drv == NULL)
    {
        mdev_CofdmInit();
    }

    if(bTunerInitOK==FALSE)
    {
        devDigitalTuner_Init();
        bTunerInitOK = TRUE;
    }

    if(bPowerOn)
    {
        MDrv_SYS_SetAGCPadMux(E_SYS_DTV_AGC_PAD_SET);
        bPowerOnGood = mdev_CofdmPowerOnInitialization(E_COFDM_EXTERNAL_DVBT2);
        bDemodDTVInitOK = TRUE;
    }
    else
    {
#if 0
        if(eCurCofdmCfg==E_COFDM_INTERNAL_DVBT)
        {
            #if USE_UTOPIA
            MDrv_DMD_DVBT_Exit();
            #else
            INTERN_DVBT_Exit();
            #endif
        }
        else if(eCurCofdmCfg==E_COFDM_INTERNAL_DVBC)
        {
            #if USE_UTOPIA
            MDrv_DMD_DVBC_Exit();
            #else
            //PJ TODO INTERN_DVBC_Exit();
            #endif
        }
        else if(eCurCofdmCfg==E_COFDM_EXTERNAL_DVBT2)
#endif
        {
            pstDvbt2Drv->Disconnect();
        }
        eCurCofdmCfg = E_COFDM_INVALID;
        //GPIO_RF_AGC_SW_ATV();
        bDemodDTVInitOK = FALSE;
    }

    if(bPowerOnGood != TRUE)
    {
        printf("mdev_CofdmControlPowerOnOff FAIL\n");
    }
}

MS_BOOL mdev_CofdmPowerSave(void)
{
    MS_BOOL temp=FALSE;

    COFDM_DBG(printf("---------------------mdev_CofdmPowerSave\n"));

    return temp;
}

void mdev_CofdmTunerProgramming(MS_U8 *cTunerData)
{
    COFDM_DBG(printf("---------------------mdev_CofdmTunerProgramming\n"));

    *cTunerData=*cTunerData;
}

void mdev_CofdmSetFrequency(const ICE_TuneToParams* params, RF_CHANNEL_BANDWIDTH bandWith)
{
    MS_U32 dwFrequency;
    MS_U8 plp_id;
    RF_CHANNEL_BANDWIDTH eBandWidth = E_RF_CH_BAND_INVALID;
    Network_Type eNetworktype;

    COFDM_DBG(printf("---------------------mdev_CofdmSetFrequency\n"));

    mdev_Set_Current_DEMOD_TYPE(E_COFDM_EXTERNAL_DVBT2);

    dwFrequency = (MS_U32)params->channel_frequency_khz;
    eBandWidth = bandWith;

    if(params->network_type==ICE_network_dvbc)
    {
        eBandWidth =  E_RF_CH_BAND_8MHz;
    }

    switch(params->network_type)
    {
        case ICE_network_dvbt2 :
            eNetworktype = E_Network_Type_DVBT2;
            break;
        case ICE_network_dvbt :
            eNetworktype = E_Network_Type_DVBT;
            break;
        case ICE_network_dvbc :
            eNetworktype = E_Network_Type_DVBC;
            break;
        case ICE_network_analog :
            eNetworktype = E_Network_Type_Analog_T;
            break;
        default :
            printf("Warning not supported network %u\n",params->network_type);
            eNetworktype = E_Network_Type_DVBT;
    }

    if(mdev_CofdmGetCurrentPlpID(&plp_id))
    {
        eNetworktype = E_Network_Type_DVBT2;
    }

  #if ( (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)     \
     || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER)       \
     || (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER) \
     || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
     )
    devTuner_Std_set(E_TUNER_DTV_DVB_T2_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
  #else
    devTuner_Std_set(E_TUNER_DTV_DVB_T2_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
  #endif


    // Save tuner freq for debug
    g_Debug_u32LastTunerFreq = dwFrequency;

    devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), eBandWidth);

    OS_DELAY_TASK(10); //waiting for tuner write

    pstDvbt2Drv->DTV_SetFrequency(dwFrequency,eBandWidth,DEFAULT_CCI_ATV_SYSTEM,0x00);//params->ts_info.priority? 0x00:0x01);
}

COFDM_LOCK_STATUS_123X _mdev_CofdmLockStatusConversion_DVBT2(COFDM_LOCK_STATUS eStatus)
{
    COFDM_LOCK_STATUS_123X eLockStatus;

    switch(eStatus)
    {
        default:
        case COFDM_FEC_LOCK:
            eLockStatus = COFDM_FEC_LOCK_T2_123X;
            break;
        case COFDM_TPS_LOCK:
            eLockStatus = COFDM_P1_LOCK_HISTORY_123X;
            break;
    }
    return eLockStatus;
}

MS_BOOL mdev_CofdmGetLockStatus(COFDM_LOCK_STATUS_123X eStatus)
{
    return pstDvbt2Drv->DTV_GetLock(eStatus);
}

MS_U16 mdev_CofdmGetPacketErr(void)
{
    MAPI_U16 u16Err=0;

    DTV_GetPacketErr(&u16Err);

    return u16Err;
}

MS_U8 mdev_CofdmGetSignalToNoiseRatio(void)
{
    MS_U8 temp = 0;
    float *fSNR = 0;

    printf("---------------------mdev_CofdmGetSignalToNoiseRatio\n");

    temp = pstDvbt2Drv->DTV_GetSNR_F(fSNR);

    return temp;
}

void mdev_CofdmPassThroughI2c(MS_BOOL bEnable)
{
    printf("---------------------mdev_CofdmPassThroughI2c:%u\n",bEnable);

    pstDvbt2Drv->IIC_Bypass_Mode(bEnable);
}

void mdev_CofdmDisableTSPAD(void)
{
    printf("---------------------mdev_CofdmDisableTSPAD:NULL FUNCTION\n");

    //INTERN_DVBT_Disable_TS_PAD();//Not for A1
}

void mdev_CofdmSwitchTransportSteamInferface(TS_INTERFACE interface)
{
    MS_BOOL bEnable;

    printf("---------------------mdev_CofdmSwitchTransportSteamInferface\n");

    if ( interface == E_SERIAL_INTERFACE )
    {
        bEnable = TRUE;
    }
    else
    {
        bEnable = FALSE;
    }

    pstDvbt2Drv->DTV_Serial_Control(bEnable);
}

void mdev_CofdmBootSwitchTSInferface(TS_INTERFACE interface)
{
    MS_BOOL bEnable;

    printf("---------------------mdev_CofdmBootSwitchTSInferface\n");

    if ( interface == E_SERIAL_INTERFACE )
    {
        bEnable = TRUE;
    }
    else
    {
        bEnable = FALSE;
    }
}

MS_BOOL mdev_CofdmGetSignalStrength(MS_U16 *strength)
{
    *strength = pstDvbt2Drv->DTV_GetSignalStrength();

    return TRUE;
}

MS_BOOL mdev_CofdmGetCellid(MS_U16 *wCell_id)
{
    MS_BOOL temp = FALSE;

    printf("---------------------mdev_CofdmGetCellid\n");

    *wCell_id = *wCell_id;
    temp = TRUE;

    return temp;
}

MS_BOOL mdev_CofdmGetSignalQuality(MS_U16 *quality)
{
    MS_BOOL temp = FALSE;

    *quality = pstDvbt2Drv->DTV_GetSignalQuality();
    temp = TRUE;

    return temp;
}

MS_BOOL mdev_CofdmGetTpsInfo(MS_U16 *TPS_Info)
{
    MS_BOOL temp = FALSE;

    printf("---------------------mdev_CofdmGetTpsInfo\n");

    TPS_Info = NULL;

    return temp;
}

MS_BOOL mdev_CofdmGetTpsInfo_T2(MS_U64 *TPS_Info)
{
    MS_BOOL temp = FALSE;

    printf("---------------------mdev_CofdmGetTpsInfo_T2\n");

    temp = pstDvbt2Drv->DTV_DVB_T2_GetSignalTpsInfo(TPS_Info);

    return temp;
}

MS_BOOL mdev_CofdmPassThroughI2cReadBytes(MS_U8 u8SlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data)
{
    MS_BOOL bRet = TRUE;

    u8SlaveID = u8SlaveID;
    u8AddrNum = u8AddrNum;
    paddr = NULL;
    u16size = u16size;
    pu8data = NULL;

    return bRet;
}

MS_BOOL mdev_CofdmPassThroughI2cWriteBytes(MS_U8 u8SlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data)
{
    MS_BOOL bRet = TRUE;

    u8SlaveID = u8SlaveID;
    u8AddrNum = u8AddrNum;
    paddr = NULL;
    u16size = u16size;
    pu8data = NULL;

    return bRet;
}

MS_BOOL mdev_CofdmReadReg(MS_U16 u16Addr, MS_U8 *pu8Data)
{
   MS_BOOL bRet = FALSE;
    UNUSED(u16Addr);
    UNUSED(pu8Data);
    /* switch (eCurCofdmCfg)
    {
        case E_COFDM_INTERNAL_DVBT:
          #if USE_UTOPIA
            bRet = MDrv_DMD_DVBT_GetReg(u16Addr, pu8Data);
          #else
            bRet = INTERN_DVBT_ReadReg(u16Addr, pu8Data);
          #endif
            break;
      #if ENABLE_DVBC
        case E_COFDM_INTERNAL_DVBC:
          #if USE_UTOPIA
            bRet = MDrv_DMD_DVBC_GetReg(u16Addr, pu8Data);
          #else
            bRet = INTERN_DVBC_ReadReg(u16Addr, pu8Data);
          #endif
            break;
      #endif

        case E_COFDM_EXTERNAL_DVBT2:
        default:
            bRet = ReadReg(u16Addr, pu8Data);
            break;

    }
    */

    return bRet;
}

MS_BOOL mdev_CofdmWriteReg(MS_U16 RegAddr, MS_U16 RegData)
{
    MS_BOOL bRet = FALSE;
    UNUSED(RegAddr);
    UNUSED(RegData);
   /* //printf("---------------------mdev_CofdmWriteReg\n");

  #if USE_UTOPIA
    return MDrv_DMD_DVBT_SetReg( RegAddr,(U8) RegData);
  #else
    return INTERN_DVBT_WriteReg( RegAddr,(U8) RegData);
  #endif*/
   return bRet;
}

extern void *memset(void * s, int c, size_t count);

MS_U8 u8PlpIDList[32];
MS_U8 mdev_CofdmGetPlpIDList(void)
{
    MS_BOOL bRet;
    MS_BOOL bUsed;
    MS_U8 u8CurrentPlpID=0;//fix coverity 90919
    MS_U8 u8PlpBitMap[32];
    MS_U8 PlpIDList[32];
    int i,j,k;

    memset(u8PlpBitMap, 0, 32);
    memset(PlpIDList, 0, 32);
    memset(u8PlpIDList, INVALID_PLPID, 32);
    k = 0;
    bRet = pstDvbt2Drv->DTV_DVB_T2_GetPlpBitMap(u8PlpBitMap);

    mdev_CofdmGetCurrentPlpID(&u8CurrentPlpID);

    if (bRet == FALSE)
    {
        printf("mdev_CofdmGetPlpIDList FAIL\n");
        return 0;
    }

    for(i = 0; i < 32; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if((u8PlpBitMap[i] >> j) & 1)
            {
                PlpIDList[k]= 0x00;
                PlpIDList[k]=(i * 8 + j);
                u8PlpIDList[k] = PlpIDList[k];
                if(u8CurrentPlpID == PlpIDList[k])
                {
                    bUsed = 1;//already used
                }
                else
                {
                    bUsed = 0;//new
                }
                MApp_SI_AddT2DelSysDesc(PlpIDList[k],bUsed);
                k++;
            }
        }
    }
    return k;
}

MS_BOOL mdev_CofdmGetPlpGroupID(MS_U8 u8PlpID, MS_U8* u8GroupID)
{
    MS_BOOL bRet;

    bRet = pstDvbt2Drv->DTV_DVB_T2_GetPlpGroupID(u8PlpID, u8GroupID);

    printf("%u mdev_CofdmGetPlpGroupID PlpID:%u GrpID:%u\n",bRet,u8PlpID,u8GroupID);

    return bRet;
}

MS_BOOL mdev_CofdmSetPlpGroupID(MS_U8 u8PlpID, MS_U8 u8GroupID)
{
    MS_BOOL bRet;

    bRet = pstDvbt2Drv->DTV_DVB_T2_SetPlpGroupID(u8PlpID, u8GroupID);

    return bRet;
}

MS_BOOL mdev_CofdmGetCurrentPlpID(MS_U8 *pu8PlpID)
{
    MS_BOOL bRet;

    bRet = pstDvbt2Drv->DTV_DVB_T2_GetCurrentPlpId(pu8PlpID);

    printf("%d T2 mdev_CofdmSetPlpGroupID PlpID:%d\n",bRet,*pu8PlpID);

    return bRet;
}

sdevFENDfunc* mdev_FrontEndAttach(void)
{
    sdevFENDfunc * handler = NULL;

    printf("---------------------mdev_FrontEndAttach\n");

    handler= (sdevFENDfunc*)malloc(sizeof(sdevFENDfunc));

    if(handler)
    {
        handler->FEND_Init = mdev_CofdmInit;
        handler->FEND_CtlDTVPower= mdev_CofdmControlPowerOnOff;
        handler->FEND_SetDTVFrequency = mdev_CofdmSetFrequency;
        handler->FEND_GetSignalQuality = mdev_CofdmGetSignalQuality;
        handler->FEND_GetSignalStrength = mdev_CofdmGetSignalStrength;
        handler->FEND_GetLockStatus = mdev_CofdmGetLockStatus;
        handler->FEND_GetTPSInfo = mdev_CofdmGetTpsInfo;
        handler->FEND_GetCellId = mdev_CofdmGetCellid;
        handler->FEND_T2GetPlpIDList = mdev_CofdmGetPlpIDList;
        handler->FEND_T2GetPlpGroupID = mdev_CofdmGetPlpGroupID;
        handler->FEND_T2SetPlpGroupID = mdev_CofdmSetPlpGroupID;
        handler->FEND_T2DemodReady = mdev_Cofdm_MSB123X_Ready;
        handler->FEND_T2GetTPSInfo = mdev_CofdmGetTpsInfo_T2;
        handler->FEND_T2GetCurrentPlpID = mdev_CofdmGetCurrentPlpID;
    }
    return handler;
}

MS_BOOL mdev_CofdmIsInitOK( void )
{
    printf(" << mdev_CofdmIsInitOK(%d) \n", bDemodDTVInitOK);

    return bDemodDTVInitOK;
}

void mdev_ControlTSOutput(BOOLEAN bEnable)
{
    DTV_ControlTsOutput(bEnable);
}

void mdev_ControlAGCOutput(BOOLEAN bEnable)
{
    DTV_ControlAGCOutput(bEnable);
}


/***************************************************************************************/
#endif // #if (ENABLE_DVB_T2)

/***************************************************************************************/
#endif  // #ifndef _MDEV_COFDM_DEMODULATOR_C_


