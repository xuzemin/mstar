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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#include "Board.h"

#if ENABLE_DVBC
#include "MsTypes.h"


#include "GPIO.h"
#include "drvBDMA.h"
//#include "SWI2C.h"
#include "drvIIC.h"
#include "drvUartDebug.h" //For OTHER_TUNER_DEBUG

#if ENABLE_CI
#include "msAPI_CI.h"
#endif  //ENABLE_CI

#include "msAPI_Timer.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
//#if(FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT )
#include"drvSYS.h"
//#endif
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "debug.h"
#include "msAPI_Tuner.h"

#if ENABLE_DVB_T2
#include "MApp_Scan.h"
#endif  //ENABLE_DVB_T2

#include "msAPI_DTVSystem.h"
#include "QAM_Demodulator.h"

#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
#if DEMOD_DVBC_USE_UTOPIA
#include "drvSYS.h"
#else
#include "MApp_GlobalFunction.h"
#include "INTERN_DVBC.c"
#endif  //DEMOD_DVBC_USE_UTOPIA
#endif  //FRONTEND_DEMOD_DVBC_TYPE

#if (!BLOADER)
#include "MApp_TopStateMachine.h"
#endif  //(!BLOADER)


#define QAM_DBG(x)  x


#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

extern U16 u16ScanDtvChNum;
U8 u8AutoSRTemp = 1; //Default AutoSR on
U8 u8AutoQAMTemp = 1; //Default utoQam on

void devQAM_Init(void)
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
    {
        DMD_DVBC_InitData sDMD_DVBC_InitData;

        static DMD_SQI_CN_NORDIGP1 sSqiCnNordigP1[]=D_DMD_SQI_CN_NORDIGP1;
        static MS_U8 u8DMD_DVBC_DSPRegInitExt[]=D_DMD_DVBC_DSPRegInitExt;
        static MS_U8 u8DMD_DVBC_InitExt[]=D_DMD_DVBC_InitExt;

        sDMD_DVBC_InitData.u8SarChannel = D_DMD_SAR_CHANNEL; // 0xFF means un-connected

    #if 1 // No sSSITableRfagc exist
        sDMD_DVBC_InitData.pTuner_RfagcSsi = NULL;
        sDMD_DVBC_InitData.u16Tuner_RfagcSsi_Size = 0; // Fix coverity
    #else
        DMD_RFAGC_SSI *sSSITableRfagc=xxx;
        sDMD_DVBC_InitData.pTuner_RfagcSsi = sSSITableRfagc;
        sDMD_DVBC_InitData.u16Tuner_RfagcSsi_Size = sizeof(sSSITableRfagc)/sizeof(DMD_RFAGC_SSI);
    #endif

    #if 1 // No sSSITableIfagc exist
        sDMD_DVBC_InitData.pTuner_IfagcSsi_LoRef = NULL;
        sDMD_DVBC_InitData.u16Tuner_IfagcSsi_LoRef_Size = 0;
        sDMD_DVBC_InitData.pTuner_IfagcSsi_HiRef = NULL;
        sDMD_DVBC_InitData.u16Tuner_IfagcSsi_HiRef_Size = 0;
    #else
        DMD_IFAGC_SSI *sSSITableIfagc=NULL;
        sDMD_DVBC_InitData.pTuner_IfagcSsi_LoRef = sSSITableIfagc;
        sDMD_DVBC_InitData.u16Tuner_IfagcSsi_LoRef_Size = sizeof(sSSITableIfagc)/sizeof(DMD_IFAGC_SSI);
        sDMD_DVBC_InitData.pTuner_IfagcSsi_HiRef = sSSITableIfagc;
        sDMD_DVBC_InitData.u16Tuner_IfagcSsi_HiRef_Size = sizeof(sSSITableIfagc)/sizeof(DMD_IFAGC_SSI);
    #endif

    #if 1 // No sSSITableIfagcErrLo exist
        sDMD_DVBC_InitData.pTuner_IfagcErr_LoRef = NULL;
        sDMD_DVBC_InitData.u16Tuner_IfagcErr_LoRef_Size = 0;
    #else
        DMD_IFAGC_ERR *sSSITableIfagcErrLo=NULL;
        sDMD_DVBC_InitData.pTuner_IfagcErr_LoRef = sSSITableIfagcErrLo;
        sDMD_DVBC_InitData.u16Tuner_IfagcErr_LoRef_Size = sizeof(sSSITableIfagcErrLo)/sizeof(DMD_IFAGC_ERR);
    #endif

    #if 1 // No sSSITableIfagcErrHi exist
        sDMD_DVBC_InitData.pTuner_IfagcErr_HiRef = NULL;
        sDMD_DVBC_InitData.u16Tuner_IfagcErr_HiRef_Size = 0;
    #else
        DMD_IFAGC_ERR *sSSITableIfagcErrHi=NULL;
        sDMD_DVBC_InitData.pTuner_IfagcErr_HiRef = sSSITableIfagcErrHi;
        sDMD_DVBC_InitData.u16Tuner_IfagcErr_HiRef_Size = sizeof(sSSITableIfagcErrHi)/sizeof(DMD_IFAGC_ERR);
    #endif

        sDMD_DVBC_InitData.pSqiCnNordigP1 = sSqiCnNordigP1;
        sDMD_DVBC_InitData.u16SqiCnNordigP1_Size = sizeof(sSqiCnNordigP1) / sizeof(DMD_SQI_CN_NORDIGP1);

        sDMD_DVBC_InitData.u8DMD_DVBC_DSPRegInitExt = u8DMD_DVBC_DSPRegInitExt;
        sDMD_DVBC_InitData.u8DMD_DVBC_DSPRegInitSize = (sizeof(u8DMD_DVBC_DSPRegInitExt)-2)/4;

        sDMD_DVBC_InitData.u8DMD_DVBC_InitExt = u8DMD_DVBC_InitExt;

      // MDrv_DMD_DVBC_SetRfBandwidth is not existed in any file.  should check again.
      /*
      #if (ENABLE_DVB_TAIWAN_APP)
        //fixed taiwan region dvbc is 6Mhz bandwidth,and utopia version higher Ver30 has this function.
        MDrv_DMD_DVBC_SetRfBandwidth(DMD_DVBC_RF_CH_BAND_6MHz);
      #else
        MDrv_DMD_DVBC_SetRfBandwidth(DMD_DVBC_RF_CH_BAND_8MHz);
      #endif
      */

        MDrv_DMD_DVBC_Init(&sDMD_DVBC_InitData, sizeof(sDMD_DVBC_InitData)); // _UTOPIA
    }
  #else
    INTERN_DVBC_Power_On_Initialization();
  #endif
#endif

#if(FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
    //Connect(E_DEVICE_DEMOD_DVB_C);
    Demod_MSB124X_Connect(E_DEVICE_DEMOD_DVB_C);
    DTV_Serial_Control(true);
    Power_On_Initialization();
    MDrv_SYS_SetPadMux(E_TS0_PAD_SET, E_SERIAL_IN);
#endif
    devDigitalTuner_Init();
}

void devQAM_ControlPowerOnOff(BOOLEAN bPowerOn)
{
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF || FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210 || FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)
    if (bPowerOn == ENABLE) // DTV mode
    {
    #if ENABLE_DVB_T2
        if (DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
        {
            EXT_RF_AGC_OFF();
            MS_DEBUG_MSG(printf("KKK: (Temp)EXT_RF_AGC_OFF...for T2\n"));
        }
    #endif
    #if ENABLE_DTMB
        if(IsDTMBInUse())
        {
            EXT_RF_AGC_OFF();
            MS_DEBUG_MSG(printf("KKK: (Temp)EXT_RF_AGC_OFF...for DTMB/ISDB\n"));
        }
        else
    #endif
        {
            EXT_RF_AGC_ON();
            MS_DEBUG_MSG(printf("KKK: (Temp)EXT_RF_AGC_OFF...for DVBT/DVBC\n"));
        }
    }
    else
    {
        EXT_RF_AGC_ON();
        MS_DEBUG_MSG(printf("KKK: (Temp)EXT_RF_AGC_On...for ATV\n"));
    }
#else
    UNUSED(bPowerOn);
#endif

#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
  #else
    INTERN_DVBC_Power_ON_OFF(bPowerOn);
  #endif
#endif
}

FUNCTION_RESULT devQAM_PowerSave(void)
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
    return E_RESULT_SUCCESS;
  #else
    if (INTERN_DVBC_Power_Save() == TRUE)
        return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
  #endif
#else
    return E_RESULT_SUCCESS;
#endif
}

void devQAM_TunerProgramming(U8 *cTunerData)
{
    UNUSED(cTunerData);
    //*cTunerData=*cTunerData;
}

#if DTV_SCAN_AUTO_FINE_TUNE_ENABLE
BOOLEAN devQAM_GetFrequencyOffset(float *pFreqOff, RF_CHANNEL_BANDWIDTH u8BW)
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
        // Real_RF = Nominal_RF + fCFO.
        float sr = 0.0;
        DMD_DVBC_MODULATION_TYPE mode;
        u8BW = u8BW;
        return MDrv_DMD_DVBC_GetStatus(&mode, &sr, pFreqOff);
  #else
        *pFreqOff = 0;  //Temp Solution;
        u8BW = u8BW; //To avoid compiler warning
        return 1;
  #endif
#else
    *pFreqOff = 0;  //Temp Solution;
    u8BW = u8BW; //To avoid compiler warning
    return 1;
#endif
}

BOOLEAN devQAM_SetAfcEnable(BOOLEAN bEnable)
{
    bEnable = bEnable; //To avoid compiler warning
    return 1;
}
#endif

U8 devQAM_GetSymbolRateMode(void)//mick
{
    return(u8AutoSRTemp);
}

#if(FRONTEND_DEMOD_DVBC_TYPE==MSTAR_MSB124X_DVBT)
WORD devQAM_GetCurrentSymbolRate(void)//mick
{
    return(U32)DTV_DVB_C_GetCurrentSymbolRate();
}
U8 devQAM_GetCurrentQAM(void)//mick
{
	return   DTV_DVB_C_GetSignalModulation();
}

#endif

#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
#if DEMOD_DVBC_USE_UTOPIA
WORD devQAM_GetCurrentSymbolRate(void)//mick
{
    DMD_DVBC_MODULATION_TYPE QAMMode;
    MS_U16 u16SymbolRate;
    float FreqOff;
    MDrv_DMD_DVBC_GetStatus(&QAMMode, &u16SymbolRate, &FreqOff);
    return u16SymbolRate;
}
#else
WORD devQAM_GetCurrentSymbolRate(void)//mick
{
    U8 u8Data;
    U32 u32Data;
    float floData;

    INTERN_DVBC_ReadReg(0x2150, &u8Data);
    u32Data = u8Data;
    INTERN_DVBC_ReadReg(0x2151, &u8Data);
    u32Data = u32Data|(((U32)u8Data)<<8);
    INTERN_DVBC_ReadReg(0x2152, &u8Data);
    u32Data = u32Data|(((U32)u8Data)<<16);
    INTERN_DVBC_ReadReg(0x2153, &u8Data);
    u32Data = u32Data|(((U32)u8Data)<<24);

    floData = (float)u32Data / 1024.0;          //don't change
    floData = (floData*45473.0)/131072.0;       //don't change
    u32Data = (floData + 0.5);                    //don't change

    return(u32Data);
}
#endif

#if DEMOD_DVBC_USE_UTOPIA
U8 devQAM_GetCurrentQAM(void)//mick
{
    DMD_DVBC_MODULATION_TYPE QAMMode;
    MS_U16 u16SymbolRate;
    float FreqOff;
    MDrv_DMD_DVBC_GetStatus(&QAMMode, &u16SymbolRate, &FreqOff);
    return (QAMMode&0x07);
}
#else
U8 devQAM_GetCurrentQAM(void)//mick
{
    U8 u8Data;

    INTERN_DVBC_ReadReg(0x2802, &u8Data);
    u8Data = (u8Data & 0x07);
    return(u8Data);
}
#endif

#if DEMOD_DVBC_USE_UTOPIA
U16 devQAM_GetSpeedUp(void)
{
    DMD_DVBC_LOCK_STATUS eLockStatus=DMD_DVBC_CHECKING;

  #if(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER || FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
    float fRFLevel=0.0f;
    devDigitalTuner_ExtendCommand(E_TUNER_SUBCMD_GET_RF_LEVEL, 0, 0, &fRFLevel);
    MDrv_DMD_DVBC_GetLockWithRFPower(DMD_DVBC_GETLOCK, &eLockStatus, fRFLevel, -82.0f);
    printf("RF Level %d %d\n",(int)fRFLevel,eLockStatus);
  #elif( (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER) \
      || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
      || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)   \
      || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)     \
      || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)     \
      || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)     \
      || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)    \
      || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)    \
      || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)   \
      || (FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
      || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER) \
      )
    float rf_level_dbm = 0.0;
    BOOLEAN bRet = true;
    bRet &= mdev_GetSignalStrength(&rf_level_dbm);
    MDrv_DMD_DVBC_GetLockWithRFPower(DMD_DVBC_GETLOCK, &eLockStatus, rf_level_dbm, -82.0f);
    printf("RF Level %d %d\n",(int)rf_level_dbm,eLockStatus);
  #else
    MDrv_DMD_DVBC_GetLock(DMD_DVBC_GETLOCK, &eLockStatus);
  #endif

    return ((eLockStatus==DMD_DVBC_UNLOCK) ? 0xFFFF : 0);
}
#else
U16 devQAM_GetSpeedUp(void)//mick
{
    U8 u8Data;
    U16 u16Data;
    U8    u8Temp;

    u8Temp = MDrv_ReadByte(0x103c0e); //Switch DmdMCU
    u8Temp |= 0x01;
    MDrv_WriteByte(0x103c0e, u8Temp);

    u8Temp = MDrv_ReadByte(0x101e3e); //Switch ChipBank
    u8Temp |= 0x01;
    MDrv_WriteByte(0x101e3e, u8Temp);

    u8Temp = MDrv_ReadByte(0x101e39); //Switch Mux form HK to DmdMCU
    u8Temp |= 0x01;
    MDrv_WriteByte(0x103c0e, u8Temp);
//*/
    INTERN_DVBC_ReadReg(0x2073, &u8Data);
    //printf("----------------> 0x2073 = 0x%bx \n", u8Data);
    u16Data = u8Data;
    INTERN_DVBC_ReadReg(0x2074, &u8Data);
    //printf("----------------> 0x2074 = 0x%bx \n", u8Data);
    u16Data = u16Data|(((U16)u8Data)<<8);

    // u16Data -->Auto SR Done     = Bit0.
    // u16Data -->Auto QAM Done = Bit2.
    // u16Data -->No CH    Detect    = Bit3. or Bit10.
    // u16Data -->ATV Detect     = Bit8.
    return(u16Data);
}
#endif

#endif

void devQAM_SetFrequency(DWORD dwFrequency, U8 u8QamMode, U16 u16SymbolRate, BOOLEAN bSpecInv, U8 u8AutoSR, U8 u8AutoQAM)
{
    //dwFrequency = 562000;                   // << Ken 20090629
    //eBandWidth = E_RF_CH_BAND_8MHz;         // << Ken 20090629

    //printf("====dwFrequency = %lu \n", dwFrequency/1000);
    //printf("====eBandWidth = %bx\n", eBandWidth);

#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
  #if (ENABLE_BOOTTIME==DISABLE)
    if (g_bAutobuildDebug == TRUE)
  #endif
    {
        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
        printf("[boot time]QAM set RF = %ld\n", gU32TmpTime);
    }
#endif

#if ( (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)     \
   || (FRONTEND_TUNER_TYPE == LG_G230D_TUNER)       \
   || (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER) \
   || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
   || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)   \
   || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)     \
   || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)     \
   || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)     \
   || (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)    \
   || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)    \
   || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)    \
   || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)    \
   || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)   \
   || (FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
   )
  devTuner_Std_set(E_TUNER_DTV_DVB_C_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
#endif

    // Save tuner freq for debug
    g_Debug_u32LastTunerFreq = dwFrequency;


    devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), E_RF_CH_BAND_8MHz);

#if (IS_MXL_TUNER)
    MsOS_DelayTask(120); //waiting for tuner write
#else
    //MsOS_DelayTask(10); //waiting for tuner write
#endif

#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
    //MsOS_DelayTask(10); //waiting for tuner write
  #if DEMOD_DVBC_USE_UTOPIA
    {
        DMD_DVBC_MODULATION_TYPE eQamMode=DMD_DVBC_QAMAUTO;

        switch (u8QamMode)
        {
            case 0:
                eQamMode=DMD_DVBC_QAM16;
                break;
            case 1:
                eQamMode=DMD_DVBC_QAM32;
                break;
            case 2:
                eQamMode=DMD_DVBC_QAM64;
                break;
            case 3:
                eQamMode=DMD_DVBC_QAM128;
                break;
            case 4:
                eQamMode=DMD_DVBC_QAM256;
                break;
            default:
                eQamMode=DMD_DVBC_QAMAUTO;
                break;
        }

        if (u8AutoSR) u16SymbolRate = 0;
        if (u8AutoQAM) eQamMode = DMD_DVBC_QAMAUTO;

	if(E_NETHERLANDS == msAPI_CM_GetCountry())
	{
#if (!BLOADER)
    #if ENABLE_ZIGGO
		if(((MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_SCAN)||(MApp_TopStateMachine_GetTopState() == STATE_TOP_CADTV_MANUAL_TUNING)))
    #endif
#endif
        {
        u16SymbolRate = 0;
        eQamMode = DMD_DVBC_QAMAUTO;
        }
	}
	else
	{
        u16SymbolRate = 0;
        eQamMode = DMD_DVBC_QAMAUTO;
	}
      #if 0//ENABLE_CI
        if ( msAPI_Tuner_IsParallelMode())
        {
            MDrv_DMD_DVBC_SetConfig(u16SymbolRate, eQamMode, D_DMD_IF_DVBC_8M, bSpecInv, FALSE);
        }
        else
      #endif
        {
            MDrv_DMD_DVBC_SetConfig(u16SymbolRate, eQamMode, D_DMD_IF_DVBC_8M, bSpecInv, FALSE);
        }

        MDrv_DMD_DVBC_SetActive(ENABLE);
    }
    #else
      #if 0//ENABLE_CI
        if ( msAPI_Tuner_IsParallelMode())
        {
            INTERN_DVBC_Config (u16SymbolRate, u8QamMode, DTV_IF_8M_FREQ, bSpecInv, FALSE, u8AutoSR, u8AutoQAM);
        }
        else
      #endif
        {
            INTERN_DVBC_Config (u16SymbolRate, u8QamMode, DTV_IF_8M_FREQ, bSpecInv, FALSE, u8AutoSR, u8AutoQAM);
        }
        INTERN_DVBC_Active(ENABLE);
  #endif
  #elif(FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
      //printf("%s,%d\n",__FILE__,__LINE__);

    u16SymbolRate = 0;
    //u8QamMode = DMD_DVBC_QAMAUTO;
	DTV_DVB_C_SetFrequency( dwFrequency,  E_RF_CH_BAND_8MHz,  u16SymbolRate,  u8QamMode);
    UNUSED(bSpecInv);
    UNUSED(u8AutoSR);
    UNUSED(u8AutoQAM);
    #else
    UNUSED(dwFrequency);
    UNUSED(u8QamMode);
    UNUSED(u16SymbolRate);
    UNUSED(bSpecInv);
    UNUSED(u8AutoSR);
    UNUSED(u8AutoQAM);
#endif

}

BOOLEAN devQAM_GetLockStatus(QAM_LOCK_STATUS eStatus)
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
    DMD_DVBC_LOCK_STATUS eLockStatus;

    switch (eStatus) // _UTOPIA
    {
        case QAM_FEC_LOCK:
            MDrv_DMD_DVBC_GetLock(DMD_DVBC_GETLOCK_FEC_LOCK, &eLockStatus);
            return (eLockStatus==DMD_DVBC_LOCK);
            break;
        case QAM_PSYNC_LOCK:
            MDrv_DMD_DVBC_GetLock(DMD_DVBC_GETLOCK_PSYNC_LOCK, &eLockStatus);
            return (eLockStatus==DMD_DVBC_LOCK);
            break;
        case QAM_NO_CHANNEL:
            MDrv_DMD_DVBC_GetLock(DMD_DVBC_GETLOCK_NO_CHANNEL, &eLockStatus);
            return (eLockStatus==DMD_DVBC_LOCK);
            break;
        case QAM_DCR_LOCK:
            MDrv_DMD_DVBC_GetLock(DMD_DVBC_GETLOCK_DCR_LOCK, &eLockStatus);
            return (eLockStatus==DMD_DVBC_LOCK);
            break;
        case QAM_AGC_LOCK:
            MDrv_DMD_DVBC_GetLock(DMD_DVBC_GETLOCK_AGC_LOCK, &eLockStatus);
            return (eLockStatus==DMD_DVBC_LOCK);
            break;
        case QAM_ATV_DETECT:
            MDrv_DMD_DVBC_GetLock(DMD_DVBC_GETLOCK_ATV_DETECT, &eLockStatus);
            return (eLockStatus==DMD_DVBC_LOCK);
            break;
        case QAM_TR_LOCK:
            MDrv_DMD_DVBC_GetLock(DMD_DVBC_GETLOCK_TR_LOCK, &eLockStatus);
            return (eLockStatus==DMD_DVBC_LOCK);
            break;
        default:
            printf("%s error %d\n",__func__,eStatus);
            break;
    }
    return FALSE;
  #else
    return INTERN_DVBC_Lock(eStatus);
  #endif
#elif(FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
  	MS_DEBUG_MSG(printf("%s,%d\r\n",__FUNCTION__,__LINE__));
  	return MSB124X_DVBC_Lock( eStatus);
#else
    UNUSED(eStatus);
    return TRUE;
#endif
}

BYTE devQAM_GetSignalToNoiseRatio(void)
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
    float fSNR=0.0f;
    return MDrv_DMD_DVBC_GetSNR(&fSNR);
    return (BYTE)fSNR;
  #else
    return (BYTE)INTERN_DVBC_GetSNR();
  #endif
#else
    return 1;
#endif
}

void devQAM_PassThroughI2C(BOOLEAN bEnable)
{
    bEnable=bEnable;
}

void devQAM_SwitchTransportSteamInferface(QAM_TS_INTERFACE interface)
{
    BOOLEAN bEnable;

    if ( interface == E_QAM_SERIAL_INTERFACE )
    {
        bEnable = TRUE;
    }
    else
    {
        bEnable = FALSE;
    }

#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
    MDrv_DMD_DVBC_SetSerialControl(bEnable);
#if ENABLE_S2
	if (IsS2InUse())
	{
		MDrv_SYS_SetPadMux(E_TS1_PAD_SET, bEnable ? E_SERIAL_IN : E_PARALLEL_IN);
	}
	else
	{
		MDrv_SYS_SetPadMux(E_TS0_PAD_SET, bEnable ? E_SERIAL_IN : E_PARALLEL_IN);
	}
#else

    MDrv_SYS_SetPadMux(E_TS0_PAD_SET, bEnable ? E_SERIAL_IN : E_PARALLEL_IN);
#endif
  #else
    INTERN_DVBC_Serial_Control(bEnable);
    INTERN_DVBC_PAD_TS1_Enable(~bEnable);
  #endif
#endif

}

FUNCTION_RESULT devQAM_GetSignal_Vit( DWORD *vit )
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
    float ber;
    *vit = *vit;
  #if DEMOD_DVBC_USE_UTOPIA
    if (MDrv_DMD_DVBC_GetPostViterbiBer(&ber))
  #else
    if (INTERN_DVBC_GetPostViterbiBer(&ber)==TRUE)
  #endif
       return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
#else
    UNUSED(vit);
    return E_RESULT_FAILURE;
#endif
}

FUNCTION_RESULT devQAM_GetSignalStrength(WORD *strength)
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
   #if(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER || FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
    {
        tmUnitSelect_t    sysUnit= 0;
        UInt32 u32RFLevelDbm=0;

        tmsysOM3912GetSignalStrength(sysUnit, &u32RFLevelDbm);
        *strength = (U16)u32RFLevelDbm;
        return E_RESULT_SUCCESS;
    }
    #elif( (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER) \
        || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
        || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)   \
        || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)     \
        || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)     \
        || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)     \
        || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)    \
        || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)    \
        || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)   \
        || (FRONTEND_TUNER_TYPE == RDA5158_TUNER) \
        || (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER) \
        )
    {
        float rf_level_dbm = 0.0;
        BOOLEAN bRet = true;
        MS_U16 ssi = 0;
        bRet &= mdev_GetSignalStrength(&rf_level_dbm);
        if (rf_level_dbm > -30.0) ssi = 100;
        else if (rf_level_dbm > -130.0)ssi = (MS_U16)(rf_level_dbm + 130.0 + 0.5);
        else ssi = 0;
        *strength = ssi;
        return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
    }
    #elif(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)
    {
        float rf_level_dbm = 0.0;
        BOOLEAN bRet = true;
        MS_U16 ssi = 0;
		//<<-- smc 20151223 for rf840 842
        #if 0
        MS_U8   tmp = 0;
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

	#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
       ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)   \
       )
			tmp = devQAM_ReadReg(0x2800 + 0x08*2);
			bRet &= devQAM_WriteReg(0x2800 + 0x08*2, tmp|0x80);

			tmp = devQAM_ReadReg(0x2800 + 0x13*2);
			bRet &= devQAM_WriteReg(0x2800 + 0x13*2, (tmp&0xF0)|0x03);

			tmp = devQAM_ReadReg(0x2800 + 0x14*2 + 1);
			if_agc_gain = tmp;
			tmp = devQAM_ReadReg(0x2800 + 0x14*2);
			if_agc_gain = (if_agc_gain<<8)|tmp;

			tmp = devQAM_ReadReg(0x2800 + 0x08*2);
			bRet &= devQAM_WriteReg(0x2800 + 0x08*2, tmp&~(0x80));
	#else
        tmp = devQAM_ReadReg(0x2700 + 0x02*2);
        bRet &= devQAM_WriteReg(0x2700 + 0x02*2, tmp|0x80);

        tmp = devQAM_ReadReg(0x2700 + 0x0b*2);
        bRet &= devQAM_WriteReg(0x2700 + 0x0b*2, (tmp&0xF0)|0x03);

        tmp = devQAM_ReadReg(0x2700 + 0x0c*2 + 1);
        if_agc_gain = tmp;
        tmp = devQAM_ReadReg(0x2700 + 0x0c*2);
        if_agc_gain = (if_agc_gain<<8)|tmp;

        tmp = devQAM_ReadReg(0x2700 + 0x02*2);
        bRet &= devQAM_WriteReg(0x2700 + 0x02*2, tmp&~(0x80));
	#endif
        #endif
		//smc 20151223 for rf840 842 -->>
        bRet &= mdev_GetSignalStrength(&rf_level_dbm);
		printf("mdev_GetSignalStrength weng 333 is %d\n",bRet);//added by Weng 2015.04.11

        if (rf_level_dbm > -30.0) ssi = 100;
        else if (rf_level_dbm > -130.0)ssi = (MS_U16)(rf_level_dbm + 130.0 + 0.5);
        else ssi = 0;
        *strength = ssi;

        return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
    }
   #else
    {
        MS_BOOL bRet=FALSE;
        bRet=MDrv_DMD_DVBC_GetSignalStrengthWithRFPower(strength,200.0f);
        return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
    }
   #endif
  #else
    return INTERN_DVBC_GetSignalStrength(strength);
  #endif
#elif(FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER || FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
    {
        tmUnitSelect_t    sysUnit= 0;
        UInt32 u32RFLevelDbm=0;

        tmsysOM3912GetSignalStrength(sysUnit, &u32RFLevelDbm);
        *strength = (U16)u32RFLevelDbm;
        return E_RESULT_SUCCESS;
    }
#elif( (FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER) \
          || (FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER) \
          || (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)   \
          || (FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)     \
          || (FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)     \
          || (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)     \
          || (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)    \
          || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)    \
          || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)   \
          )
	{
		  float rf_level_dbm = 0.0;
		  BOOLEAN bRet = true;
		  MS_U16 ssi = 0;
		  bRet &= mdev_GetSignalStrength(&rf_level_dbm);
		  if (rf_level_dbm > -30.0) ssi = 100;
		  else if (rf_level_dbm > -130.0)ssi = (MS_U16)(rf_level_dbm + 130.0 + 0.5);
		  else ssi = 0;
		  *strength = ssi;
		  return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
	}
#elif(FRONTEND_DEMOD_DVBC_TYPE==MSTAR_MSB124X_DVBT)
	*strength = DTV_GetSignalStrength();
	return E_RESULT_SUCCESS;
#else
    *strength = 80;
    return E_RESULT_SUCCESS;
#endif
}


FUNCTION_RESULT devQAM_GetSignalQuality(WORD *quality)
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
  #if DEMOD_DVBC_USE_UTOPIA
    MS_BOOL bRet=FALSE;
    bRet=MDrv_DMD_DVBC_GetSignalQuality(quality);
    return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
  #else
    return INTERN_DVBC_GetSignalQuality(quality);
  #endif
#elif(FRONTEND_DEMOD_DVBC_TYPE== MSTAR_MSB124X_DVBT)
    *quality = DTV_GetSignalQuality();
	//printf("%s,%d, quality=%d\r\n",__FUNCTION__,__LINE__,*quality);
	return E_RESULT_SUCCESS;
#else
	*quality = 80;
    return E_RESULT_SUCCESS;
#endif
}

BOOLEAN devQAM_PassThroughI2C_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    UNUSED(u8SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);

    return TRUE;
}

BOOLEAN devQAM_PassThroughI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    UNUSED(u8SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);
    return TRUE;
}

BOOLEAN devQAM_GetSpecInv(void)
{
#if ((FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) || (FRONTEND_SECOND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD))
    return TRUE;
#endif
    return TRUE;
}

#if ENABLE_DVBC
U16 devQAM_ReadReg(U16 RegAddr)
{
    U8 RegData=0;

  #if (FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
    ReadReg(RegAddr, &RegData);
    return (U16) RegData;
  #elif DEMOD_DVBC_USE_UTOPIA
    MDrv_DMD_DVBC_GetReg(RegAddr, &RegData);
  #else
    INTERN_DVBC_ReadReg(RegAddr, &RegData);
  #endif

    return (U16) RegData;
}

BOOLEAN devQAM_WriteReg(U16 RegAddr, U16 RegData)
{
  #if (FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
    return WriteReg( RegAddr,(U8) RegData);
  #elif DEMOD_DVBC_USE_UTOPIA
    return MDrv_DMD_DVBC_SetReg( RegAddr,(U8) RegData);
  #else
    return INTERN_DVBC_WriteReg( RegAddr,(U8) RegData);
  #endif
}
#endif

#endif

