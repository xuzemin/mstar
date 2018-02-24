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

#include "Board.h"

#include "MsTypes.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"


#include "GPIO.h"

#include "drvBDMA.h"
//#include "SWI2C.h"
#include"drvIIC.h"
#include "drvUartDebug.h" //For OTHER_TUNER_DEBUG

#if (ENABLE_CI)
#include "msAPI_CI.h"
#endif
#include "msAPI_Timer.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_Demod.h"

#include "MApp_GlobalVar.h"


#include "COFDM_Demodulator.h"

#if (ENABLE_DVB_T2)&&((CHIP_FAMILY_TYPE==CHIP_FAMILY_MILAN)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MARLON))
#include "drvDMD_INTERN_DVBT2.h"
#include "INTERN_T2_cofdm_demodulator.h"
#endif

#if ENABLE_DVB_T2
#include "MApp_Scan.h"
#endif

#if ENABLE_DTV
#if 0
#else
//Thomas 20150714 to do

#if ENABLE_DVBT
    #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    #include "msb124x.c"
    #else //1 EMBEDDED_DVBT_DEMOD
        #if DEMOD_DVBT_USE_UTOPIA
        #include "drvSYS.h"
        #else
        #include "MApp_GlobalFunction.h"
        #include "INTERN_DVBT.c"
        #endif
    #endif
#endif

#if ENABLE_DTMB
  #if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    #include "drvDMD_common.h"
    #include "drvDMD_DTMB.h"
    #include "./INTERN_DTMB/INTERN_DTMB.c"

  #elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    #include "drvDMD_common.h"
    #include "drvDMD_DTMB.h"
    #include "./EXTERN_DTMB/EXTERN_DTMB.c"

  #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
        ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
    #include "drvDMD_common.h"
    #include "drvDMD_DTMB.h"
    #include "./EXTERN_DTMB/EXTERN_DTMB.c"

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X)
    #include "atbm883x.c"

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X)
    #include "atbm884x.c"

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X)
    #include "atbm885x_utility.c"
    #include "atbmdvbc.c"
    #include "atbm885x.c"

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X)
    #include "atbm886x.c"

  #elif (FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X)
    #include "atbm887x.c"
  #endif
#endif

 #if ENABLE_DVBC
   #if (FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
    #include "msb124x.c"
  #else //1 EMBEDDED_DVBC_DEMOD
  #endif
 #endif

 #if ENABLE_ISDBT
  #if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    #include "drvDMD_common.h"
    #include "drvDMD_ISDBT.h"
    #include "./EXTERN_ISDBT/EXTERN_ISDBT.c"
//    #include "INTERN_DVBT.c"  //For VIF init usage, only mailbox function 20100601EL
  #elif (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
   #if DEMOD_ISDBT_USE_UTOPIA
    #include "drvDMD_common.h"
    #include "drvDMD_ISDBT.h"
    #include "./INTERN_ISDBT/INTERN_ISDBT.c"
   #else
    #include "MApp_GlobalFunction.h"
    #include "./INTERN_ISDBT/halDMD_INTERN_common.c"
    #include "./INTERN_ISDBT/halDMD_INTERN_ISDBT.c"
    #include "./INTERN_ISDBT/drvDMD_common.c"
    #include "./INTERN_ISDBT/drvDMD_ISDBT.c"
    #include "./INTERN_ISDBT/INTERN_ISDBT.c"
    #include "drvVIF.h"
   #endif
  #endif
 #endif

#if ENABLE_DVBS
    #if (FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB124X_DVBT)
    #include "msb124x.c"
    #elif (FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB131X_DVBS2)
    #include "device_demodulator_msb131x.c"
    #else //1 EMBEDDED_DVBS_DEMOD
    #endif
#endif

#endif

#if(ENABLE_S2)
#include "apiDigiTuner.h"
#if(FRONTEND_DEMOD_S2_TYPE==EMBEDDED_DVBS_DEMOD)
#include "drvDMD_INTERN_DVBS.h"
#endif
#if(FRONTEND_DEMOD_S2_TYPE == DEMOD_AVL6211)
#include "AVL_DVBSx_SDK/AVL_Func.c"
#include "AVL_DVBSx_SDK/AVL6211_patch.dat.c"
#include "AVL_DVBSx_SDK/drvCofdmDmd.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/avl_dvbsx.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/avl.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/IBase.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/IBlindScan.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/IBlindscanAPI.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/IDiseqc.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/II2C.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/II2CRepeater.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/ITuner.c"
#include "AVL_DVBSx_SDK/AVL_DVBSx/src/IRx.c"
#include "AVL_DVBSx_SDK/BSP/IBSP.c"
#include "AVL_DVBSx_SDK/addon/ExtAV2011.c"
#include "AVL_DVBSx_SDK/LNB_Controler.c"
#else
#if (DISH_TYPE == DISH_A8293)
#include "Dish/drvDishA8293.c"
#elif (DISH_TYPE == DISH_A8304)
#include "Dish/drvDishA8304.c"
#elif (DISH_TYPE == DISH_RT5047)
#include "Dish/drvDishRT5047.c"
#elif (DISH_TYPE == DISH_DEMOD)
#include "Dish/drvDishDemod.c"
#endif
#endif
#endif

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
//extern U16 u16ScanDtvChNum;


#define COFDM_DBG(x)  //x

//extern unsigned char bCardAInside;

#if 0
void devCOFDM_Init(void)
{
#if (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
  #if USE_UTOPIA
    {
        DMD_DVBT_InitData sDMD_DVBT_InitData;
        //static DMD_RFAGC_SSI sSSITableRfagc[]=D_DMD_SSI_TABLE_RFAGC;
        //static DMD_IFAGC_SSI sSSITableIfagc[]=D_DMD_SSI_TABLE_IFAGC;
        //static DMD_IFAGC_ERR sSSITableIfagcErrLo[]=D_DMD_SSI_TABLE_IFAGC_ERR_LO;
        //static DMD_IFAGC_ERR sSSITableIfagcErrHi[]=D_DMD_SSI_TABLE_IFAGC_ERR_HI;
        DMD_RFAGC_SSI *sSSITableRfagc=NULL;
        DMD_IFAGC_SSI *sSSITableIfagc=NULL;
        DMD_IFAGC_ERR *sSSITableIfagcErrLo=NULL;
        DMD_IFAGC_ERR *sSSITableIfagcErrHi=NULL;
        static DMD_SQI_CN_NORDIGP1 sSqiCnNordigP1[]=D_DMD_SQI_CN_NORDIGP1;
        static MS_U8 u8DMD_DVBT_DSPRegInitExt[]=D_DMD_DVBT_DSPRegInitExt;
        static MS_U8 u8DMD_DVBT_InitExt[]=D_DMD_DVBT_InitExt;

        sDMD_DVBT_InitData.u8SarChannel = D_DMD_SAR_CHANNEL; // 0xFF means un-connected
        sDMD_DVBT_InitData.pTuner_RfagcSsi = sSSITableRfagc;
        sDMD_DVBT_InitData.u16Tuner_RfagcSsi_Size = sizeof(sSSITableRfagc)/sizeof(DMD_RFAGC_SSI);
        sDMD_DVBT_InitData.pTuner_IfagcSsi_LoRef = sSSITableIfagc;
        sDMD_DVBT_InitData.u16Tuner_IfagcSsi_LoRef_Size = sizeof(sSSITableIfagc)/sizeof(DMD_IFAGC_SSI);
        sDMD_DVBT_InitData.pTuner_IfagcSsi_HiRef = sSSITableIfagc;
        sDMD_DVBT_InitData.u16Tuner_IfagcSsi_HiRef_Size = sizeof(sSSITableIfagc)/sizeof(DMD_IFAGC_SSI);
        sDMD_DVBT_InitData.pTuner_IfagcErr_LoRef = sSSITableIfagcErrLo;
        sDMD_DVBT_InitData.u16Tuner_IfagcErr_LoRef_Size = sizeof(sSSITableIfagcErrLo)/sizeof(DMD_IFAGC_ERR);
        sDMD_DVBT_InitData.pTuner_IfagcErr_HiRef = sSSITableIfagcErrHi;
        sDMD_DVBT_InitData.u16Tuner_IfagcErr_HiRef_Size = sizeof(sSSITableIfagcErrHi)/sizeof(DMD_IFAGC_ERR);
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
#elif(FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    //printf("%s,%d\n",__FILE__,__LINE__);
    //Connect(E_DEVICE_DEMOD_DVB_T);
    Demod_MSB124X_Connect(E_DEVICE_DEMOD_DVB_T);

    DTV_Serial_Control(!TS_PARALLEL_OUTPUT);
    Power_On_Initialization();
    MDrv_SYS_SetPadMux(E_TS0_PAD_SET, E_SERIAL_IN);

#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    INTERN_ISDBT_Power_On_Initialization();
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    EXTERN_DTMB_Power_On_Initialization();
    printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    EXTERN_DTMB_Power_On_Initialization();
    printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    INTERN_DTMB_Power_On_Initialization();
    printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);

#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD|| FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
    Demod_Reset_On();
    MsOS_DelayTask(20);
    Demod_Reset_Off();
    MsOS_DelayTask(30);
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_884X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_885X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_886X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_887X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_888X)
    Demodulator_OFF();
    msAPI_Timer_Delayms(10);
    Demodulator_ON();
#elif (FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
    Demodulator_ON();
    MsOS_DelayTask(30);
    if(LGS9X_SoftReset())
    {
        printf("HYQ lgs9x reset error");
    }
    msAPI_Timer_Delayms(5);
    LGS9X_SetDtmbMode();
    msAPI_Timer_Delayms(10);
#else
    // hard-wire reset pin
#if (!ENABLE_S2)
    Demodulator_OFF();
    MsOS_DelayTask(20);
    Demodulator_ON();
    MsOS_DelayTask(30);
#endif
#endif

#if (FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD)
    //SWIIC_SetIICSpeed( 150 );
    LGS_SelectADMode(0);
    //SWIIC_SetIICSpeed( 10 );
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD)
    LGS_SoftReset();
    MsOS_DelayTask(5);
    LGS8G52_Init();

    LGS8G52_SelectADMode(0);
//    LGS_SetMpegMode(0, 1,0);

    LGS_SetAutoMode();

    MsOS_DelayTask(10); //add 20080616
//    LGS_SetManualMode();
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    {
        INT8 err = LGS_NO_ERROR;

        LGS_RegisterWait(msAPI_Timer_Delayms);
        err = LGS8G75_SoftReset();
        msAPI_Timer_Delayms(5);
        LGS8G75_Init();
        msAPI_Timer_Delayms(10);
        LGS8G75_SelectADMode(0);
        msAPI_Timer_Delayms(5);
    }
    LGS8G75_SelectTunerType(1);
    msAPI_Timer_Delayms(10);
    LGS8G75_SetAutoMode();
    msAPI_Timer_Delayms(10);
//    LGS8G75_SetManualMode();
//    msAPI_Timer_Delayms(5);
//    LGS8G52_AGC(0xF0,0x00,0xA2);
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
    lgs8g80_device_register();
        MsOS_DelayTask(5);
    LGS8G80_DownloadFirmware();
    LGS8G80_SelectADMode(0x00);
    LGS8G80_SelectTunerType(0x01);

    //LGS8G80_SoftReset();
    LGS8G80_Init(NULL);
    LGS8G80_SetAutoMode();

    MsOS_DelayTask(10);
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_883X)
    ATBMInit();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_884X)
    ATBMInit_DTMB_Mode();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_885X)
    ATBMPowerOnInit();
    ATBMSet_DTMB();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_886X)
    ATBMPowerOnInit();
    ATBMSetDTMBMode();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_887X)
    ATBMPowerOnInit();
    ATBMSetDTMBMode();
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_888X)
    ATBMPowerOnInit();
    ATBMSetDTMBMode();
#elif (FRONTEND_DEMOD_TYPE == HDIC_2311)
    HDIC2311_Init();
#endif


#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)

    MSB1200_Power_On_Initialization();

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)

   MSB1210_Power_On_Initialization();

#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD   \
||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD    \
||FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    //SWIIC_SetIICSpeed( 150 );
    devCOFDM_SwitchTransportSteamInferface(E_PARALLEL_INTERFACE);
    //SWIIC_SetIICSpeed( 10 );

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    MSB1400_Power_On_Initialization();
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    M88DC2800_Initialize();

#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    M88DD2000_Initialize();
#endif

    devDigitalTuner_Init();

    //printf("%s,%d\n",__FILE__,__LINE__);

    //devCOFDM_SetFrequency(562000, E_RF_CH_BAND_8MHz);   // <<< Ken 20090629
    //printf("%s,%d\n",__FILE__,__LINE__);

}
#endif

#if 0
void devCOFDM_ControlPowerOnOff(BOOLEAN bPowerOn)
{
#if (  (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)           \
    || (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)   \
    || (FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)    \
    )
    {
        if (bPowerOn == ENABLE) // DTV mode
        {
        #if ENABLE_DVB_T2
            if (DVB_T2_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal())
            {
                EXT_RF_AGC_OFF();
            }
        #endif
        #if ENABLE_DTMB
            if(IsDTMBInUse())
            {
                EXT_RF_AGC_OFF();
            }
            else
        #endif
            {
                EXT_RF_AGC_ON();
            }
        }
        else
        {
            EXT_RF_AGC_ON();
        }
    }
#endif

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    MSB1200_Power_ON_OFF(bPowerOn);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    MSB1210_Power_ON_OFF(bPowerOn);
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD \
|| FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD || FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD || FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
    bPowerOn = bPowerOn;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    bPowerOn = bPowerOn;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    bPowerOn = bPowerOn;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    bPowerOn = bPowerOn;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    bPowerOn = bPowerOn;
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_883X)
    printf("\n !!! %s, %d TO DO \n",__FILE__, __LINE__);
#elif (FRONTEND_DEMOD_TYPE == ALTOBEAM_884X)
    if(bPowerOn)
        ATBM_Standby_WakeUp();
    else
        ATBM_Standby();
#elif(FRONTEND_DEMOD_TYPE == ALTOBEAM_885X)
    bPowerOn = bPowerOn;
#elif(FRONTEND_DEMOD_TYPE == ALTOBEAM_886X)
    if(bPowerOn)
        ATBMStandbyWakeUp();
    else
        ATBMStandby();
#elif(FRONTEND_DEMOD_TYPE == ALTOBEAM_887X)
    if(bPowerOn)
        ATBMStandbyWakeUp();
    else
        ATBMStandby();
#elif(FRONTEND_DEMOD_TYPE == ALTOBEAM_888X)
    if(bPowerOn)
        ATBMStandbyWakeUp();
    else
        ATBMStandby();
#elif (FRONTEND_DEMOD_TYPE == HDIC_2311)
        bPowerOn = bPowerOn;

#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
  #if USE_UTOPIA
  #else
    INTERN_DVBT_Power_ON_OFF(bPowerOn);
  #endif
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    INTERN_ISDBT_Power_ON_OFF(bPowerOn);
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    EXTERN_DTMB_Power_ON_OFF(bPowerOn);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    INTERN_DTMB_Power_ON_OFF(bPowerOn);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    EXTERN_DTMB_Power_ON_OFF(bPowerOn);
#endif
}

#endif

#if 0
FUNCTION_RESULT devCOFDM_PowerSave(void)
{
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    if (MSB1200_Power_Save() == TRUE)
        return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    if (MSB1210_Power_Save() == TRUE)
        return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
  #if USE_UTOPIA
    return E_RESULT_SUCCESS;
  #else
    if (INTERN_DVBT_Power_Save() == TRUE)
        return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
  #endif
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
     if (INTERN_ISDBT_Power_Save() == TRUE)
         return E_RESULT_SUCCESS;
     else
         return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
     if (EXTERN_DTMB_Power_Save() == TRUE)
         return E_RESULT_SUCCESS;
     else
         return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
     if (INTERN_DTMB_Power_Save() == TRUE)
         return E_RESULT_SUCCESS;
     else
         return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
     if (EXTERN_DTMB_Power_Save() == TRUE)
         return E_RESULT_SUCCESS;
     else
         return E_RESULT_FAILURE;
#else
    return E_RESULT_SUCCESS;
#endif
}
#endif
#if 0
void devCOFDM_TunerProgramming(U8 *cTunerData)
{
    #if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
        MSB1200_Tuner_Programming( cTunerData );
    #elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
        *cTunerData=*cTunerData;
    #elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
    *cTunerData=*cTunerData;
    #elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    *cTunerData=*cTunerData;
    #elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    *cTunerData=*cTunerData;
    #elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    *cTunerData=*cTunerData;
    #elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
    UNUSED(cTunerData);
    //*cTunerData=*cTunerData;
    #elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    UNUSED(cTunerData);
    #elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    UNUSED(cTunerData);
    #elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    UNUSED(cTunerData);
    #elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    UNUSED(cTunerData);
    #else
    *cTunerData=*cTunerData;
    #endif
}
#endif
#if DTV_SCAN_AUTO_FINE_TUNE_ENABLE
BOOLEAN devCOFDM_GetFrequencyOffset(float *pFreqOff, RF_CHANNEL_BANDWIDTH u8BW)
{
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    return MSB1200_GetFrequencyOffset(pFreqOff, u8BW);
#elif ((FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD))
#if DEMOD_DVBT_USE_UTOPIA
    // Real_RF = Nominal_RF + fCFO.
    return MDrv_DMD_DVBT_GetFreqOffset(pFreqOff);
#else
    *pFreqOff = 0;  //Temp Solution;;
    u8BW = u8BW; //To avoid compiler warning
    return 1;
#endif
#else
    *pFreqOff = 0;  //Temp Solution;;
    u8BW = u8BW; //To avoid compiler warning
    return 1;
#endif
}

#endif

#if 1
void devCOFDM_SetFrequency(DWORD dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID)
{
#if 1
#if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        devCOFDM_DVBT_SetFrequency(dwFrequency, eBandWidth, eHpLp, u8PlpID);
    }
    else
#endif
    {
    #if ENABLE_DTMB
        if(IsDTMBInUse())
        {
            devCOFDM_DTMB_SetFrequency(dwFrequency, eBandWidth, eHpLp, u8PlpID);
        }
        else
    #endif
        {
        #if ENABLE_ISDBT
            if(IsISDBTInUse())
            {
                devCOFDM_ISDBT_SetFrequency(dwFrequency, eBandWidth, eHpLp, u8PlpID);
            }
            else
        #endif
            {
                UNUSED(dwFrequency);
                UNUSED(eBandWidth);
                UNUSED(eHpLp);
                UNUSED(u8PlpID);
            }
        }
    }

#else
    // Save tuner freq for debug
    g_Debug_u32LastTunerFreq = dwFrequency;


#if ((FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)\
    || (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)\
    || (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)\
    || (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)\
    || (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)|| (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB))
    #if (!BLOADER)
    EN_OSD_COUNTRY_SETTING            en_osd_country;
    #endif //(!BLOADER)
    BOOLEAN                            b_pal_bg;
#endif
    UNUSED(u8PlpID);
#if ((FRONTEND_DEMOD_TYPE != EMBEDDED_DVBT_DEMOD)\
       &&(FRONTEND_DEMOD_TYPE != EMBEDDED_ISDBT_DEMOD)\
       &&(FRONTEND_DEMOD_TYPE != EXTERNAL_DTMB_DEMOD)\
       &&(FRONTEND_DEMOD_TYPE != EMBEDDED_DTMB_DEMOD)\
       &&(FRONTEND_DEMOD_TYPE != MSTAR_MSB101M_DTMB)\
       && (FRONTEND_DEMOD_TYPE != MSTAR_MSB1210_DEMOD))
    UNUSED(eHpLp);
#endif
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    MSB1200_Active(DISABLE);

#endif

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
#if (FRONTEND_DEMOD_TYPE == ALTOBEAM_886X ||FRONTEND_DEMOD_TYPE == ALTOBEAM_887X ||FRONTEND_DEMOD_TYPE == ALTOBEAM_888X  || FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
    devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
#elif(FRONTEND_DEMOD_TYPE == HDIC_2311)
     devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    devTuner_Std_set(E_TUNER_DTV_ISDB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    devTuner_Std_set(E_TUNER_DTV_DTMB_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
#else
    devTuner_Std_set(E_TUNER_DTV_DVB_T_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
#endif
#endif
    //printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));
    devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), eBandWidth);
    //printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));
#if(FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    DTV_SetFrequency((U32)(dwFrequency), eBandWidth, false, E_RF_CH_LP==eHpLp ? TRUE : FALSE);
#endif
//printf( "%s,%d,0x%x\n",__FUNCTION__,__LINE__,MDrv_ReadByte(0x100B50));

#if(FRONTEND_DEMOD_TYPE == HDIC_2311)
    HDIC2311_SetAutoMode();
    HDIC2311_SoftReset();
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)

  #if (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
    MSB1200_SetFreq((U32)dwFrequency);    //FRA_DBG_071120_Canopus
  #endif

#if (IS_MXL_TUNER)
    MsOS_DelayTask(120); //waiting for tuner write
#else
    MsOS_DelayTask(10); //waiting for tuner write
#endif

    MSB1200_Config(eBandWidth);

    #if TS_PARALLEL_OUTPUT
        #if ENABLE_CI
        if(!msAPI_Tuner_IsParallelMode())
        {
            MSB1200_Serial_Control(ENABLE);
        }
        else
        #endif
        {
            MSB1200_Serial_Control(DISABLE);
        }
    #else
        #if ENABLE_CI
        if ( msAPI_Tuner_IsParallelMode())
        {
            MSB1200_Serial_Control(DISABLE);
        }
        else
        #endif
        {
            MSB1200_Serial_Control(ENABLE);
        }
    #endif

    //MsOS_DelayTask( 50 );

    MSB1200_Active(ENABLE);

    //MsOS_DelayTask( 5 );

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)

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

    #if ENABLE_CI
    if ( msAPI_Tuner_IsParallelMode())
        MSB1210_Config(eBandWidth, false, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE);
    else
    #endif
    MSB1210_Config(eBandWidth, !TS_PARALLEL_OUTPUT, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE);

    //printf("msb1210 active\n");

    MSB1210_Active(ENABLE);

#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD)
      //SWIIC_SetIICSpeed(150);  //2
               if(LGS_SetAutoMode()== LGS_NO_ERROR)
               {
                   if(LGS_AutoDetect() == LGS_NO_ERROR)
                   {
                        if(LGS_SetManualMode()== LGS_NO_ERROR)
                {
                    //printf("\n\n--------------------------Auto detect done, carrier mode ---------------------\n\n");
                }
                        else
                {
                    //printf("\n\n------------Set ManualMode error ----------------\n\n");
                }
                   }
                   else
                    {
               //printf("\n\n----------------------------Auto detect error,carrier mode ---------------------\n\n");
                    }
               }
           else
           {
               //printf("\n\n----------Set AutoMode error-------------\n\n");
           }
     //SWIIC_SetIICSpeed(10);  //2
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD)
      //SWIIC_SetIICSpeed(150);  //2
               if(LGS8G52_SetAutoMode()== LGS_NO_ERROR)
               {
                   if(LGS8G52_AutoDetect() == LGS_NO_ERROR)
                   {
                        if(LGS_SetManualMode()== LGS_NO_ERROR)
                {
                    //printf("\n\n--------------------------Auto detect done, carrier mode ---------------------\n\n");
                }
                        else
                {
                    //printf("\n\n------------Set ManualMode error ----------------\n\n");
                }
                   }
                   else
                    {
               //printf("\n\n----------------------------Auto detect error,carrier mode ---------------------\n\n");
                    }
               }
           else
           {
               //printf("\n\n----------Set AutoMode error-------------\n\n");
           }
     //SWIIC_SetIICSpeed(10);  //2
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    //SWIIC_SetIICSpeed(150);  //2
           if(LGS8G75_SetAutoMode()== LGS_NO_ERROR)
              {
                   if(LGS8G75_AutoDetect() == LGS_NO_ERROR)
                   {
                        if(LGS8G75_SetManualMode()== LGS_NO_ERROR)
                       {
                            printf("\n\n--------------------------Auto detect done, carrier mode ---------------------\n\n");
                       }
                        else
                       {
                            printf("\n\n------------Set ManualMode error ----------------\n\n");
                        }
                    }
                    else
                    {
                       printf("\n\n----------------------------Auto detect error,carrier mode ---------------------\n\n");
                    }
               }
           else
           {
                printf("\n\n----------Set AutoMode error-------------\n\n");
           }
     //SWIIC_SetIICSpeed(10);  //2
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
      //SWIIC_SetIICSpeed(150);  //2
               if(LGS8G80_SetAutoMode()== LGS_NO_ERROR)
               {
                   if(LGS8G80_AutoDetect() == LGS_NO_ERROR)
                   {
                   }
                   else
                    {
               printf("\n\n----------------------------Auto detect error,carrier mode ---------------------\n\n");
                    }
               }
           else
           {
               //printf("\n\n----------Set AutoMode error-------------\n\n");
           }
     //SWIIC_SetIICSpeed(10);  //2


#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    MsOS_DelayTask(10); //waiting for tuner write

#if ENABLE_CI
    if ( msAPI_Tuner_IsParallelMode())
        MSB1400_Config(eBandWidth, false, false,E_RF_CH_LP==eHpLp ? TRUE : FALSE);
    else
#endif
        // default parallel mode.
        MSB1400_Config(eBandWidth, false, false,E_RF_CH_LP==eHpLp ? TRUE : FALSE);

    MSB1400_Active(ENABLE);

#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    MsOS_DelayTask(5); //waiting for tuner write
    M88DC2800_Config();
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    MsOS_DelayTask(5); //waiting for tuner write
    M88DD2000_Config();

#elif ((FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD))

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

  #if USE_UTOPIA
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
                eDMDBandWidth=E_DMD_RF_CH_BAND_8MHz;
                u32IFFreq=D_DMD_IF_DVBT_8M;
                break;
        }
      #if ENABLE_CI
        if ( msAPI_Tuner_IsParallelMode())// || (0 == TS_SERIAL_OUTPUT_IF_CI_REMOVED))
            //MDrv_DMD_DVBT_SetConfigHPLP(eDMDBandWidth, false, b_pal_bg, E_RF_CH_LP==eHpLp ? TRUE : FALSE);
            MDrv_DMD_DVBT_SetConfigHPLPSetIF(eDMDBandWidth, false, b_pal_bg, E_RF_CH_LP==eHpLp ? TRUE : FALSE, u32IFFreq, 24000, D_DMD_TUNER_IQSWAP);
        else
      #endif
        //MDrv_DMD_DVBT_SetConfigHPLP(eDMDBandWidth, !TS_PARALLEL_OUTPUT, b_pal_bg, E_RF_CH_LP==eHpLp ? TRUE : FALSE);
        MDrv_DMD_DVBT_SetConfigHPLPSetIF(eDMDBandWidth, !TS_PARALLEL_OUTPUT, b_pal_bg, E_RF_CH_LP==eHpLp ? TRUE : FALSE, u32IFFreq, 24000, D_DMD_TUNER_IQSWAP);
        MDrv_DMD_DVBT_SetActive(ENABLE);
    }
  #else
      #if ENABLE_CI
        if ( msAPI_Tuner_IsParallelMode())// || (0 == TS_SERIAL_OUTPUT_IF_CI_REMOVED))
            INTERN_DVBT_Config(eBandWidth, false, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE);
        else
      #endif
        INTERN_DVBT_Config(eBandWidth, !TS_PARALLEL_OUTPUT, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE); // << ken 2009.06.29 serial
        INTERN_DVBT_Active(ENABLE);
  #endif
#elif ((FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD))
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
    INTERN_ISDBT_Config(eBandWidth, !TS_PARALLEL_OUTPUT, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE); // << ken 2009.06.29 serial
    INTERN_ISDBT_Active(ENABLE);
#elif ((FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD))
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
#elif ((FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD))
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
    INTERN_DTMB_Config(eBandWidth, !TS_PARALLEL_OUTPUT, b_pal_bg,E_RF_CH_LP==eHpLp ? TRUE : FALSE); // << ken 2009.06.29 serial
    INTERN_DTMB_Active(ENABLE);
#elif ((FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB))
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

#elif (FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)

#endif

#endif
}
#endif

#if 0
BOOLEAN devCOFDM_GetLockStatus(COFDM_LOCK_STATUS eStatus)
{
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)

    return MSB1200_Lock(eStatus);

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)

    return MSB1210_Lock(eStatus);

#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
    U8 u8Result;
    eStatus=eStatus;
    //SWIIC_SetIICSpeed(150);
    u8Result = LGS_CheckLocked();
    //SWIIC_SetIICSpeed(10);
    if(u8Result == 1)
        return TRUE;
    else
        return FALSE;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    U8 u8Result;
    U8 u8Temp;
    eStatus=eStatus;
    //SWIIC_SetIICSpeed(150);
    u8Result = LGS8G75_CheckLocked(&u8Temp);
    //SWIIC_SetIICSpeed(10);
    if(u8Temp == 1)
        return TRUE;
    else
        return FALSE;

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    return MSB1400_Lock(eStatus);
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    eStatus=eStatus;
    return(M88DC2800_GetLock());
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    //eStatus=eStatus;
#if (ENABLE_S2)
    if( IsS2InUse() )
    {
        PRINT_CURRENT_LINE();
        printf("\nError: Should call dvbs api!\n");
        //return MApi_DigiTuner_MPEGGetLock();
    }
#endif

    //printf("%s,%d\r\n",__FUNCTION__,__LINE__);
    return  MSB124X_Lock(eStatus);
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    eStatus=eStatus;
    return(M88DD2000_GetLock());

#elif (  FRONTEND_DEMOD_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_886X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_887X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_888X   \
      )
    eStatus=eStatus;
    return ATBMLockedFlag();
#elif (FRONTEND_DEMOD_TYPE == HDIC_2311)
    {
        U8 u8HD2311LockStatus;
        eStatus=eStatus;
        return HDIC2311_IsDemodLocked(&u8HD2311LockStatus);
    }
#elif (FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
    U8 u8Result = 0xFF,Waittime;
    eStatus=eStatus;
    if(((MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_SCAN) || \
    (MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN) || \
    (MApp_TopStateMachine_GetTopState() == STATE_TOP_INSTALLGUIDE) || \
    (MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_MANUAL_TUNING)) && \
    (_eZUIState == E_ZUI_STATE_RUNNING))
    {
        Waittime = 80;
    }
    else
    {
        Waittime = 10;
    }
    LGS9X_CheckLocked(DEMOD_WORK_MODE_ANT1_DTMB, &u8Result, NULL, Waittime);//yanxi 110811 [6031]    //yanxi 110802 marked [6035]
    if(u8Result == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
#if (ENABLE_S2)
    if(IsS2InUse())
    {
        return MApi_DigiTuner_MPEGGetLock();
    }
#endif
  #if USE_UTOPIA
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
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    return INTERN_ISDBT_Lock(eStatus);
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    return EXTERN_DTMB_Lock(eStatus);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    return INTERN_DTMB_Lock(eStatus);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    return EXTERN_DTMB_Lock(eStatus);
#else
    eStatus=eStatus;
    return TRUE;
#endif
}
#endif
#if 0
BYTE devCOFDM_GetSignalToNoiseRatio(void)
{
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)

    return (BYTE)MSB1200_GetSNR();

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)

    return (BYTE)MSB1210_GetSNR();

#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD)
    return 1;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD)
    return 1;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD)
    return 1;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    return 1;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
    return 1;

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    return (BYTE)MSB1400_GetSNR();
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    return (BYTE)M88DC2800_GetSNR();
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    return 1;

#elif (  FRONTEND_DEMOD_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_886X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_887X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_888X   \
      )
    return (BYTE)ATBMSignalNoiseRatio();
#elif (FRONTEND_DEMOD_TYPE == HDIC_2311)
    {
        double fSignalSNR = 0;
        HDIC2311_GetSignalSNR(&fSignalSNR);
        return (BYTE)fSignalSNR;
    }

#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
  #if USE_UTOPIA
    float fSNR=0.0f;
    MDrv_DMD_DVBT_GetSNR(&fSNR);
    if (fSNR<0.0f) fSNR=0.0f;
    if (fSNR>100.0f) fSNR=100.0f;
    return (char)fSNR;
  #else
    return (BYTE)INTERN_DVBT_GetSNR();
  #endif
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    return (BYTE)INTERN_ISDBT_GetSNR();
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    return (BYTE)DTV_GetSNR();
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    return (BYTE)EXTERN_DTMB_GetSNR();
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    return (BYTE)INTERN_DTMB_GetSNR();
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    return (BYTE)EXTERN_DTMB_GetSNR();
#else
    return 1;
#endif
}
#endif
#if 0
#if (FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD)
BYTE devCOFDM_GetSignalMode(void)
{
    return LGS8G52_ReadMode();
}
BYTE devCOFDM_GetSignalPN(void)
{
        return LGS8G52_ReadPN();
}
BYTE devCOFDM_GetSignalPNFLIP(void)
{
    return LGS8G52_ReadPNFLIP();
}
BYTE devCOFDM_GetSignalCarrier(void)
{
    return LGS8G52_ReadCarrier();
}
BYTE devCOFDM_SetSignalMode(BYTE Value)
{
    return LGS8G52_SetMode(Value);
}
BYTE devCOFDM_SetSignalPN(BYTE Value)
{
    return LGS8G52_SetPN(Value);
}
BYTE devCOFDM_SetSignalPNFLIP(BYTE Value)
{
    return LGS8G52_SetPNFLIP(Value);
}
BYTE devCOFDM_SetSignalCarrier(BYTE Value)
{
    return LGS_SetCarrierMode(Value);
}
#endif
#endif
#if (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)

void devCOFDM_PassThroughI2C(BOOLEAN bEnable)
{
#if 0
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)

    bEnable++; //dummy code
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    bEnable=bEnable;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    bEnable=bEnable;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    bEnable=bEnable;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    bEnable=bEnable;
#elif (  FRONTEND_DEMOD_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_886X    \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_887X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_888X   \
      )
   #if (DEMO_TUNER_IIC_TYPE == DEMO_TO_TUNER)
    if(bEnable)
    {
        ATBMI2CByPassOn();
    }
    else
    {
        ATBMI2CByPassOff();
    }
  #else
    bEnable=bEnable;
  #endif
  #elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    IIC_Bypass_Mode(bEnable);
 #elif (FRONTEND_DEMOD_TYPE == HDIC_2311)
    #if 0//(DEMO_TUNER_IIC_TYPE == DEMO_TO_TUNER)
       if(bEnable)
       {
           HDIC2311_OpenTunerI2C(_TUNER_I2C_ID);
       }
       else
       {
           HDIC2311_CloseTunerI2C();
       }
    #else
       bEnable=bEnable;
    #endif
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
    bEnable=bEnable;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    bEnable=bEnable;
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    bEnable=bEnable;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    bEnable=bEnable;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    MDrv_DMD_DTMB_IIC_BYPASS_MODE(bEnable);
    // printf("!!MDrv_DMD_DTMB_IIC_BYPASS_MODE(%d) = %d\n",bEnable,MDrv_DMD_DTMB_IIC_BYPASS_MODE(bEnable));
#else
    bEnable=bEnable;
#endif
#else
//Thomas 20150714 to do

 #if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
            IIC_Bypass_Mode(bEnable);
        #else //1 EMBEDDED_DVBT_DEMOD
            bEnable=bEnable;
        #endif
    }
 #endif

#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
    #if (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
        //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
        bEnable = bEnable;

    #elif (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
        bEnable = bEnable;

    #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
          ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
        MDrv_DMD_DTMB_IIC_BYPASS_MODE(bEnable);
        // printf("!!MDrv_DMD_DTMB_IIC_BYPASS_MODE(%d) = %d\n",bEnable,MDrv_DMD_DTMB_IIC_BYPASS_MODE(bEnable));

    #elif (  FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X  \
          )
        {
        #if (DEMO_TUNER_IIC_TYPE == DEMO_TO_TUNER)
            if(bEnable)
            {
                ATBMI2CByPassOn();
            }
            else
            {
                ATBMI2CByPassOff();
            }
        #else
            bEnable=bEnable;
        #endif
        }
    #endif
    }
#endif

    UNUSED(bEnable);

#endif
}
#endif

#if 0
void devCOFDM_SwitchTransportSteamInferface(TS_INTERFACE interface)
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

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    MSB1200_Serial_Control(bEnable);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    DTV_Serial_Control(bEnable);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    MSB1210_Serial_Control(bEnable);
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD)
    LGS_SetCarrierMode(interface);
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    LGS8G75_SetMpegMode(1,1,0);//bEnable);
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
    LGS8G80_SetMpegMode(1,1,0);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    MSB1400_Serial_Control(bEnable);
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    M88DC2800_Serial_Control(bEnable);
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    M88DD2000_Serial_Control(bEnable);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
 #if USE_UTOPIA
  #if(ENABLE_S2)
    if((IsS2InUse())&&(FRONTEND_DEMOD_S2_TYPE==EMBEDDED_DVBS_DEMOD))
        MDrv_DMD_DVBS_SetSerialControl(bEnable);
    else
  #endif
        MDrv_DMD_DVBT_SetSerialControl(bEnable);
    MDrv_SYS_SetPadMux(E_TS0_PAD_SET, bEnable ? E_SERIAL_IN : E_PARALLEL_IN);
 #else
    INTERN_DVBT_Serial_Control(bEnable);
    INTERN_DVBT_PAD_TS1_Enable(~bEnable);
 #endif
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    INTERN_ISDBT_Serial_Control(bEnable);
    INTERN_ISDBT_PAD_TS1_Enable(~bEnable);
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    EXTERN_DTMB_Serial_Control(bEnable);
    EXTERN_DTMB_PAD_TS1_Enable(~bEnable);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    INTERN_DTMB_Serial_Control(bEnable);
    INTERN_DTMB_PAD_TS1_Enable(~bEnable);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    EXTERN_DTMB_Serial_Control(bEnable);
    EXTERN_DTMB_PAD_TS1_Enable(~bEnable);
#elif (  (FRONTEND_DEMOD_TYPE == ALTOBEAM_883X)     \
      || (FRONTEND_DEMOD_TYPE == ALTOBEAM_884X)     \
      || (FRONTEND_DEMOD_TYPE == ALTOBEAM_885X)     \
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
#else
    printf("\r\n !!! TO DO: %s, %d \n",__FILE__, __LINE__);
#endif

}
#endif

#if 0
FUNCTION_RESULT devCOFDM_GetSignal_Vit( DWORD *vit )
{

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    float ber;
    *vit = *vit;
    return MSB1200_GetPostViterbiBer(&ber);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    float ber;
    *vit = *vit;
    if (MSB1210_GetPostViterbiBer(&ber)==TRUE)
       return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    *vit = *vit;
    return E_RESULT_FAILURE;

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    if (MSB124X_DTV_GetPostBER((float*)vit)==TRUE)
    return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    *vit = *vit;
    return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    *vit = *vit;
    return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    *vit = *vit;
    return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
    float ber;
    UNUSED(vit);
    //*vit = *vit;
  #if USE_UTOPIA
    if (MDrv_DMD_DVBT_GetPostViterbiBer(&ber))
  #else
    if (INTERN_DVBT_GetPostViterbiBer(&ber)==TRUE)
  #endif
       return E_RESULT_SUCCESS;
    else
        return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    UNUSED(vit);
    return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    UNUSED(vit);
    return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    UNUSED(vit);
    return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
        UNUSED(vit);
        return E_RESULT_FAILURE;
#else
    *vit = *vit;
    return E_RESULT_FAILURE;
#endif
}
#endif
#if (  (FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)                                                 \
    && (FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER || FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)    \
    )
#if DEMOD_DVBT_USE_UTOPIA
void devCOFDM_RecalculateSignalStrengthForNordig(WORD *strength)
{
    WORD nordig_strength=0;
    nordig_strength = *strength;
    if(nordig_strength<10)
    {
        nordig_strength = 0;
    }
    else if(nordig_strength<=14)//-95  ----  -90//2:1
    {
        nordig_strength = 10-(14-nordig_strength)*2;
    }
    else if(nordig_strength<=23)//-90  ----  -80//1:1
    {
        nordig_strength = nordig_strength-4;
    }
    else if(nordig_strength<=33)//-80  ----  -70 //13:5
    {
        nordig_strength = 45-(33-nordig_strength)*13/5;
    }
    else if(nordig_strength<=43)//-70  ----  -60//18:5
    {
        nordig_strength = 81-(43-nordig_strength)*18/5;
    }
    else if(nordig_strength<=53)//-60  ----  -50//7:5
    {
        nordig_strength = 95-(53-nordig_strength)*7/5;
    }
    else if(nordig_strength<=63)//-50  ----  -40//7:5
    {
        nordig_strength = 100-(63-nordig_strength)/2;
    }
    else
    {
        nordig_strength =100;
    }
     *strength= nordig_strength;
}
#endif
#endif

#if 0
FUNCTION_RESULT devCOFDM_GetSignalStrength(WORD *strength)
{
#if (ENABLE_S2)
    if( IsS2InUse() )
    {
        if( msAPI_Demod_S_Get_SignalStrength(strength) )
            return E_RESULT_SUCCESS;
        else
            return E_RESULT_FAILURE;
    }
#endif


#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    return MSB1200_GetSignalStrength(strength);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    return MSB1210_GetSignalStrength(strength);
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD)
    *strength=LGS8G52_ReadIntension();
    return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
     *strength=*strength;
    return E_RESULT_SUCCESS;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
     *strength=LGS8G80_ReadIntension();
    return E_RESULT_SUCCESS;

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    return MSB1400_GetSignalStrength(strength);
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    return M88DC2800_GetSignalStrength(strength);
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    *strength=*strength;
    return E_RESULT_FAILURE;

#elif (  FRONTEND_DEMOD_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_885X   \
      )
    *strength=ATBMSignalStrength();
    return E_RESULT_SUCCESS;
#elif (  FRONTEND_DEMOD_TYPE == ALTOBEAM_886X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_887X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_888X   \
      )
    *strength=ATBMSignalStrength_reference();
    return E_RESULT_SUCCESS;
#elif (FRONTEND_DEMOD_TYPE == HDIC_2311)
    HDIC2311_GetSignalStrength(strength);
    return E_RESULT_SUCCESS;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
    UINT32 Strenth = 0;
    if( (LGS9X_GetSignalStrength(DEMOD_WORK_MODE_ANT1_DTMB,&Strenth)) == LGS_NO_ERROR )
    {
        *strength = Strenth;
        return E_RESULT_SUCCESS;
    }
    else
    {
        return E_RESULT_FAILURE;
    }

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    {
        *strength = DTV_GetSignalStrength();
    }
    return E_RESULT_SUCCESS;

#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
 #if USE_UTOPIA
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
            || (FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)  \
            )
    {
        float   rf_level_dbm = 0.0;
        MS_BOOL bRet = TRUE;
        bRet &= mdev_GetSignalStrength(&rf_level_dbm);
        bRet &= MDrv_DMD_DVBT_GetSignalStrengthWithRFPower(strength, rf_level_dbm);
        return (bRet == TRUE)?E_RESULT_SUCCESS:E_RESULT_FAILURE;
    }

  #elif (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER || FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
    {
        float   rf_level_dbm = 0.0;
        MS_BOOL bRet = TRUE;
        //<<-- smc 20151223 for rf 840 842
        #if 0
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

      #if((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)||((CHIP_FAMILY_TYPE == CHIP_FAMILY_MULAN)))
        tmp = devCOFDM_ReadReg(0x2800 + 0x08*2);
        bRet &= devCOFDM_WriteReg(0x2800 + 0x08*2, tmp|0x80);

        tmp = devCOFDM_ReadReg(0x2800 + 0x13*2);
        bRet &= devCOFDM_WriteReg(0x2800 + 0x13*2, (tmp&0xF0)|0x03);

        tmp = devCOFDM_ReadReg(0x2800 + 0x14*2 + 1);
        if_agc_gain = tmp;
        tmp = devCOFDM_ReadReg(0x2800 + 0x14*2);
        if_agc_gain = (if_agc_gain<<8)|tmp;

        tmp = devCOFDM_ReadReg(0x2800 + 0x08*2);
        bRet &= devCOFDM_WriteReg(0x2800 + 0x08*2, tmp&~(0x80));
      #else
        tmp = devCOFDM_ReadReg(0x2700 + 0x02*2);
        bRet &= devCOFDM_WriteReg(0x2700 + 0x02*2, tmp|0x80);

        tmp = devCOFDM_ReadReg(0x2700 + 0x0b*2);
        bRet &= devCOFDM_WriteReg(0x2700 + 0x0b*2, (tmp&0xF0)|0x03);

        tmp = devCOFDM_ReadReg(0x2700 + 0x0c*2 + 1);
        if_agc_gain = tmp;
        tmp = devCOFDM_ReadReg(0x2700 + 0x0c*2);
        if_agc_gain = (if_agc_gain<<8)|tmp;

        tmp = devCOFDM_ReadReg(0x2700 + 0x02*2);
        bRet &= devCOFDM_WriteReg(0x2700 + 0x02*2, tmp&~(0x80));
      #endif

        #endif
        //smc 20151223 for rf 840 842 -->>
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

#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    return INTERN_ISDBT_GetSignalStrength(strength);
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    return EXTERN_DTMB_GetSignalStrength(strength);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
  #if USE_UTOPIA
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
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
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
#else
    *strength=*strength;
    return E_RESULT_FAILURE;
#endif
}
#endif

BOOLEAN devCOFDM_Get_CELL_ID(WORD *wCell_id)
{
#if 0
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    return MSB1200_Get_CELL_ID(wCell_id);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    *wCell_id = DTV_GetCellID();
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
  #if USE_UTOPIA
    return MDrv_DMD_DVBT_GetCellID(wCell_id);
  #else
    return INTERN_DVBT_Get_CELL_ID(wCell_id);
  #endif
#else
    UNUSED(wCell_id);
    printf("error not support cell function\n");
    return FALSE;
#endif
#else

 #if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
            *wCell_id = DTV_GetCellID();
            return TRUE;
        #else //1 EMBEDDED_DVBT_DEMOD
         #if DEMOD_DVBT_USE_UTOPIA
            return MDrv_DMD_DVBT_GetCellID(wCell_id);
         #else
            return INTERN_DVBT_Get_CELL_ID(wCell_id);
         #endif
        #endif
    }
 #endif

    UNUSED(wCell_id);

    return FALSE; //Thomas 20150714 to do

#endif
}

#if (ENABLE_S2)
MS_U16 _MApp_getCurRFSignalSNR(void)
{
    #define DEFAULT_SNR_MIN 0
    #define DEFAULT_SNR_MAX 35
    MS_U16 _u16snr;
    MApi_DigiTuner_GetSNR(&_u16snr);
    return _u16snr * 100 / (DEFAULT_SNR_MAX - DEFAULT_SNR_MIN);
}
#endif

#if 0
FUNCTION_RESULT devCOFDM_GetSignalQuality(WORD *quality)
{
#if(ENABLE_S2)
    if(IsS2InUse())
    {
         *quality = _MApp_getCurRFSignalSNR();
        return E_RESULT_SUCCESS;
    }
#endif

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    return MSB1200_GetSignalQuality(quality);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    return MSB1210_GetSignalQuality(quality);
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    *quality = *quality;
    return E_RESULT_FAILURE;

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    return  MSB1400_GetSignalQuality(quality);
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    *quality = *quality;
    return E_RESULT_FAILURE;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    *quality = *quality;
    return E_RESULT_FAILURE;

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    *quality=DTV_GetSignalQuality();
    //printf("%s,%d, quality=%d\r\n",__FUNCTION__,__LINE__,*quality);
    return E_RESULT_SUCCESS;

#elif (  FRONTEND_DEMOD_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_886X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_887X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_888X   \
      )
    *quality = ATBMSignalQuality();
    return E_RESULT_SUCCESS;
#elif (FRONTEND_DEMOD_TYPE == HDIC_2311)
    HDIC2311_GetSignalQuality(quality);
    return E_RESULT_SUCCESS;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
    if(LGS_NO_ERROR == LGS9X_GetSignalQuality(DEMOD_WORK_MODE_ANT1_DTMB,quality))
    {
        return E_RESULT_SUCCESS;
    }
    else
    {
        return E_RESULT_FAILURE;
    }
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
#if USE_UTOPIA
    MS_BOOL bRet=FALSE;
    bRet=MDrv_DMD_DVBT_GetSignalQuality(quality);
    return (bRet) ? E_RESULT_SUCCESS : E_RESULT_FAILURE;
#else
    return INTERN_DVBT_GetSignalQuality(quality);
#endif
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
    return INTERN_ISDBT_GetSignalQuality(quality);
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
    return EXTERN_DTMB_GetSignalQuality(quality);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    return INTERN_DTMB_GetSignalQuality(quality);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    return EXTERN_DTMB_GetSignalQuality(quality);
#else
    *quality = *quality;
    return E_RESULT_FAILURE;
#endif
}
#endif

#if 0
BOOLEAN devCOFDM_GetBER(float *ber)
{
#if 0
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    return MSB1200_GetPostViterbiBer(ber);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    return MSB1210_GetPostViterbiBer(ber);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    return MSB124X_DTV_GetPostBER(ber);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
  #if USE_UTOPIA
    return MDrv_DMD_DVBT_GetPostViterbiBer(ber);
  #else
    return INTERN_DVBT_GetPostViterbiBer(ber);
  #endif
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD || FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB|| FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD || FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    *ber=*ber;
    return FALSE;
#else
    *ber=*ber;
    return FALSE;
#endif
#else

 #if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
            return MSB124X_DTV_GetPostBER(ber);
        #else //1 EMBEDDED_DVBT_DEMOD
         #if DEMOD_DVBT_USE_UTOPIA
            return MDrv_DMD_DVBT_GetPostViterbiBer(ber);
         #else
            return INTERN_DVBT_GetPostViterbiBer(ber);
         #endif
        #endif
    }
 #endif

#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
        #if (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB|| FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD || FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
            //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
            *ber=*ber;
            return FALSE;
        #endif
}
#endif


//Thomas 20150714 to do
    *ber=*ber;
    return FALSE;

#endif
}
#endif

BOOLEAN devCOFDM_Get_Modul_Mode(WORD *Modul_Mode)
{
#if 0
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    *Modul_Mode=*Modul_Mode;
    return 0;//MSB1200_GetSignalStrength(strength);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    return MSB1210_Get_TPS_Parameter_Const(Modul_Mode);
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    *Modul_Mode=*Modul_Mode;
    return 0;
#elif(FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    return DTV_DVB_T_Get_TPS_Parameter(Modul_Mode, TS_MODUL_MODE);
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    *Modul_Mode=*Modul_Mode;
    return 0;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    *Modul_Mode=*Modul_Mode;
    return 0;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    *Modul_Mode=*Modul_Mode;
    return 0;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
  #if USE_UTOPIA
    MS_U16 u16Info=0;
    MS_BOOL bRet=FALSE;
   #if (ENABLE_DVB_T2)&&((CHIP_FAMILY_TYPE==CHIP_FAMILY_MILAN)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MARLON))
    U8 u8Plpid =0;
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    u8Plpid = msAPI_CM_GetPLP_ID(bServiceType,wCurrentPosition);
    if(u8Plpid!=0xFF)
    {
        bRet=MDrv_DMD_DVBT2_GetL1Info( &u16Info, T2_MODUL_MODE);
    }
    else
   #endif
    {
        bRet=MDrv_DMD_DVBT_GetTPSInfo(&u16Info);
    }
    *Modul_Mode=(u16Info & (BIT0|BIT1));
    return bRet;
  #else
    return INTERN_DVBT_Get_TPS_Parameter_Const(Modul_Mode);
  #endif
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD|| FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB || FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD || FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    *Modul_Mode=*Modul_Mode;
    return 0;
#else
    *Modul_Mode=*Modul_Mode;
    return 0;
#endif
#else

 #if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
            return DTV_DVB_T_Get_TPS_Parameter(Modul_Mode, TS_MODUL_MODE);

        #else     // 1 EMBEDDED_DVBT_DEMOD
            #if DEMOD_DVBT_USE_UTOPIA
                MS_U16 u16Info=0;
                MS_BOOL bRet=FALSE;
             #if (ENABLE_DVB_T2)&&((CHIP_FAMILY_TYPE==CHIP_FAMILY_MILAN)||(CHIP_FAMILY_TYPE==CHIP_FAMILY_MARLON))
                U8 u8Plpid =0;
                MEMBER_SERVICETYPE bServiceType;
                WORD wCurrentPosition;
                bServiceType = msAPI_CM_GetCurrentServiceType();
                wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
                u8Plpid = msAPI_CM_GetPLP_ID(bServiceType,wCurrentPosition);
                if(u8Plpid!=0xFF)
                {
                    bRet=MDrv_DMD_DVBT2_GetL1Info( &u16Info, T2_MODUL_MODE);
                }
                else
             #endif
                {
                    bRet=MDrv_DMD_DVBT_GetTPSInfo(&u16Info);
                }
                *Modul_Mode=(u16Info & (BIT0|BIT1));
                return bRet;
            #else
                return INTERN_DVBT_Get_TPS_Parameter_Const(Modul_Mode);
            #endif
        #endif
    }
 #endif

#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
      #if ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
          ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B)\
          ||(FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)       \
          ||(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD) )
        //printf("%s, %d, %s\n",__FUNCTION__,__LINE__,__FILE__);
        *Modul_Mode=*Modul_Mode;
        return 0;
      #endif
    }
#endif

//Thomas 20150714 to do
    *Modul_Mode=*Modul_Mode;
    return 0;
#endif
}




BOOLEAN devCOFDM_Is_Hierarchy_On(void)
{
#if ENABLE_DVBT
    if(IsDVBTInUse())
    {
    #if (FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
        #if DEMOD_DVBT_USE_UTOPIA
        MS_U16 u16Info=0;
        MDrv_DMD_DVBT_GetTPSInfo(&u16Info);
        return (u16Info&0x38) ? TRUE:FALSE;
        #else
        return INTERN_DVBT_Is_HierarchyOn();
        #endif
    #endif
    }
#endif

    return FALSE;

}

BOOLEAN devCOFDM_PassThroughI2C_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    U16 U16SlaveID=u8SlaveID;
#if 0
#if(FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H)
    return MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) ;

#else

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
    return MSB1200_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);

#elif  (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)
    MDrv_1210_IIC_Bypass_Mode(TRUE);        // IIC by-pass mode on
    MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
    MDrv_1210_IIC_Bypass_Mode(FALSE);        // IIC by-pass mode off
    return TRUE;

#elif  (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
    IIC_Bypass_Mode(TRUE);        // IIC by-pass mode on
    MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
    IIC_Bypass_Mode(FALSE);        // IIC by-pass mode off
    return TRUE;

#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
    MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
    return TRUE;

#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    LGS8G75_OpenTunerI2C(u8SlaveID)  ;
    MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
    LGS8G75_CloseTunerI2C() ;
    return TRUE;

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    MDrv_1400_IIC_Bypass_Mode(TRUE);        // IIC by-pass mode on
    MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
    MDrv_1400_IIC_Bypass_Mode(FALSE);        // IIC by-pass mode off
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    M88DC2800_RepeatControl(ENABLE);
    MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
    M88DC2800_RepeatControl(DISABLE);
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    M88DD2000_ReadBytesRepeat(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
    return TRUE;

#elif (  FRONTEND_DEMOD_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_886X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_887X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_888X   \
      )
  #if (DEMO_TUNER_IIC_TYPE == DEMO_TO_TUNER)
    if(gbTVAutoScanChannelEnable)
    {
        MDrv_IIC_ReadBytes(U16SlaveID|(DEMOD_IIC_BUS<<8),u8AddrNum,paddr,u16size,pu8data);
    }
    else
  #endif
    {
        ATBMI2CByPassOn();
        MDrv_IIC_ReadBytes(U16SlaveID|(DEMOD_IIC_BUS<<8),u8AddrNum,paddr,u16size,pu8data);
        ATBMI2CByPassOff();
    }
    return TRUE;

#elif  (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
    UNUSED(U16SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);
    return TRUE;

#elif  (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD || FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD || FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    UNUSED(U16SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);
    return TRUE;

#elif  (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
    MDrv_DMD_DTMB_IIC_BYPASS_MODE(TRUE);
    MDrv_IIC_ReadBytes(U16SlaveID |(DEMOD_IIC_BUS<<8),u8AddrNum,paddr,u16size,pu8data);
    MDrv_DMD_DTMB_IIC_BYPASS_MODE(FALSE);
    return TRUE;

#else
    UNUSED(U16SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);
    return TRUE;
#endif

#endif  //(FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H)
#else

//Thomas 20150714 to do

 #if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
            IIC_Bypass_Mode(TRUE);        // IIC by-pass mode on
            MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
            IIC_Bypass_Mode(FALSE);        // IIC by-pass mode off
            return TRUE;
        #else //1 EMBEDDED_DVBT_DEMOD
            return TRUE;
        #endif
    }
 #endif

#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
    #if ( (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD) \
        ||(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD) )
        return TRUE;

    #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
          ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
        MDrv_DMD_DTMB_IIC_BYPASS_MODE(TRUE);
        MDrv_IIC_ReadBytes(U16SlaveID |(DEMOD_IIC_BUS<<8),u8AddrNum,paddr,u16size,pu8data);
        MDrv_DMD_DTMB_IIC_BYPASS_MODE(FALSE);
        return TRUE;

    #elif (  FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X  \
          )
      #if (DEMO_TUNER_IIC_TYPE == DEMO_TO_TUNER)
        if(gbTVAutoScanChannelEnable)
        {
            MDrv_IIC_ReadBytes(U16SlaveID|(DEMOD_IIC_BUS<<8),u8AddrNum,paddr,u16size,pu8data);
        }
        else
      #endif
        {
            ATBMI2CByPassOn();
            MDrv_IIC_ReadBytes(U16SlaveID|(DEMOD_IIC_BUS<<8),u8AddrNum,paddr,u16size,pu8data);
            ATBMI2CByPassOff();
        }
        return TRUE;
    #endif
    }
#endif

#if ENABLE_ISDBT
    if(IsISDBTInUse())
    {
        #if (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
            MDrv_DMD_ISDBT_IIC_BYPASS_MODE(TRUE);;        // IIC by-pass mode on
            MDrv_IIC_ReadBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
            MDrv_DMD_ISDBT_IIC_BYPASS_MODE(FALSE);        // IIC by-pass mode off
            return TRUE;
        #else //EMBEDDED_ISDBT_DEMOD
            return TRUE;
        #endif
    }
#endif

    UNUSED(U16SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);

    return TRUE;

#endif
}


BOOLEAN devCOFDM_PassThroughI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    U16 U16SlaveID=u8SlaveID;

#if (OTHER_TUNER_DEBUG==1)
    int i;
    printf("===> COFDM(ID=0x%bx)(Size=0x%x) ",U16SlaveID,u16size);
    printf("  Data =  ");
    for (i=0;i<u16size;i++)
        printf("0x%bx  ",*(pu8data+i));
    printf("\n");
#endif


#if (FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H||FRONTEND_TUNER_TYPE == XUGUANG_STM_6F_V236H_TUNER \
    ||FRONTEND_TUNER_TYPE==XUGUANG_HFT_8B1_V116H_TUNER || FRONTEND_TUNER_TYPE==XUGUANG_HFT_8B_115CW_TUNER \
    || FRONTEND_TUNER_TYPE == LINGHUA_TDP_1H1_E_TUNER||FRONTEND_TUNER_TYPE==TCL_F20WT_3DD_E )
    U16SlaveID |= (U16)((TUNER_IIC_BUS<<8)|u8SlaveID);
    return MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) ;

#else // (FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H)

#if 0
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
        return MSB1200_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);

#elif  (FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
     IIC_Bypass_Mode(TRUE);      // IIC by-pass mode on
     if (MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) == FALSE)
     {
         printf("read write fail---%x\n",U16SlaveID);
         return FALSE;
     }
     IIC_Bypass_Mode(FALSE);      // IIC by-pass mode off
     return TRUE;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)

    MDrv_1210_IIC_Bypass_Mode(TRUE);        // IIC by-pass mode on

    if (MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) == FALSE)
    {
        printf("read write fail---%x\n",U16SlaveID);
        return FALSE;
    }

    MDrv_1210_IIC_Bypass_Mode(FALSE);        // IIC by-pass mode off
    return TRUE;

#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
    //SWIIC_SetIICSpeed( 150 );
    LGS_OpenTunerI2C(u8SlaveID)  ;
    if (MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data)==FALSE)
    {
        printf("devCOFDM_PassThroughI2C_WriteBytes error------error---error-- %x-\n",U16SlaveID);
    }
    LGS_CloseTunerI2C() ;
    //SWIIC_SetIICSpeed( 10 );
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_8G75_DEMOD)
    U16SlaveID=(U16)((E_I2C_BUS_DDCA0<<8)|u8SlaveID);

    if (MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) == FALSE)
    {
        printf("\r\n 20091027--write fail\n");
    }
    return TRUE;

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD)
    MDrv_1400_IIC_Bypass_Mode(TRUE);        // IIC by-pass mode on
    if (MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) == FALSE)
    {
        printf("read write fail---%x\n",U16SlaveID);
        return FALSE;
    }
    MDrv_1400_IIC_Bypass_Mode(FALSE);        // IIC by-pass mode off
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DC2800_DEMOD)
    M88DC2800_RepeatControl(ENABLE);
    if ( FALSE == MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) )
    {
        printf("devCOFDM_PassThroughI2C_WriteBytes Error \n");
        return FALSE;
    }
    M88DC2800_RepeatControl(DISABLE);

    return TRUE;

#elif (FRONTEND_DEMOD_TYPE == MONTAGE_M88DD2000_DEMOD)
    M88DD2000_WriteBytesRepeat(U16SlaveID, u8AddrNum, paddr, u16size, pu8data);
    return TRUE;

#elif (  FRONTEND_DEMOD_TYPE == ALTOBEAM_883X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_884X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_885X   \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_886X    \
      || FRONTEND_DEMOD_TYPE == ALTOBEAM_887X    \
       || FRONTEND_DEMOD_TYPE == ALTOBEAM_888X   \
      )
  #if (DEMO_TUNER_IIC_TYPE == DEMO_TO_TUNER)
    if (gbTVAutoScanChannelEnable)
    {
       if ( FALSE == MDrv_IIC_WriteBytes(U16SlaveID|(DEMOD_IIC_BUS<<8), u8AddrNum, paddr, u16size, pu8data) )
       {
          printf("devCOFDM_PassThroughI2C_WriteBytes Error \n");
          return FALSE;
       }
    }
    else
  #endif
    {
        ATBMI2CByPassOn();
        if ( FALSE == MDrv_IIC_WriteBytes(U16SlaveID|(DEMOD_IIC_BUS<<8), u8AddrNum, paddr, u16size, pu8data) )
        {
            printf("devCOFDM_PassThroughI2C_WriteBytes Error \n");
            return FALSE;
        }
        ATBMI2CByPassOff();
     }
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
    LGS9X_I2CEchoOn();
    if(MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data)==FALSE)
    {
        printf("\r\n !!LEGEND_9x_DEMOD I2C Write Error = %x\n",U16SlaveID);
    }
    LGS9X_I2CEchoOff();
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
    UNUSED(U16SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD || FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD || FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
    UNUSED(U16SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);
    return TRUE;
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
       MDrv_DMD_DTMB_IIC_BYPASS_MODE(TRUE);
       if ( FALSE == MDrv_IIC_WriteBytes(U16SlaveID |(DEMOD_IIC_BUS<<8), u8AddrNum, paddr, u16size, pu8data) )
      {
          printf("devCOFDM_PassThroughI2C_WriteBytes Error \n");
          return FALSE;
      }
       MDrv_DMD_DTMB_IIC_BYPASS_MODE(FALSE);
    return TRUE;
#else
    UNUSED(U16SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);
    return TRUE;
#endif
#else

//Thomas 20150714 to do

 #if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        #if (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
            IIC_Bypass_Mode(TRUE);      // IIC by-pass mode on
            if (MDrv_IIC_WriteBytes(U16SlaveID, u8AddrNum, paddr, u16size, pu8data) == FALSE)
            {
                printf("read write fail---%x\n",U16SlaveID);
                return FALSE;
            }
            IIC_Bypass_Mode(FALSE);      // IIC by-pass mode off
            return TRUE;
        #else //1 EMBEDDED_DVBT_DEMOD
            return TRUE;
        #endif
}
 #endif

#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
    #if  (FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD || FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
        return TRUE;

    #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
          ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
        MDrv_DMD_DTMB_IIC_BYPASS_MODE(TRUE);
        if ( FALSE == MDrv_IIC_WriteBytes(U16SlaveID |(DEMOD_IIC_BUS<<8), u8AddrNum, paddr, u16size, pu8data) )
        {
            printf("devCOFDM_PassThroughI2C_WriteBytes Error \n");
            return FALSE;
        }
        MDrv_DMD_DTMB_IIC_BYPASS_MODE(FALSE);
        return TRUE;

    #elif (  FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_883X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_884X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_885X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_886X  \
          || FRONTEND_DEMOD_DTMB_TYPE == ALTOBEAM_887X  \
          )
      #if (DEMO_TUNER_IIC_TYPE == DEMO_TO_TUNER)
        if (gbTVAutoScanChannelEnable)
        {
            if ( FALSE == MDrv_IIC_WriteBytes(U16SlaveID|(DEMOD_IIC_BUS<<8), u8AddrNum, paddr, u16size, pu8data) )
           {
              printf("devCOFDM_PassThroughI2C_WriteBytes Error \n");
              return FALSE;
           }
        }
        else
      #endif
        {
            ATBMI2CByPassOn();
            if ( FALSE == MDrv_IIC_WriteBytes(U16SlaveID|(DEMOD_IIC_BUS<<8), u8AddrNum, paddr, u16size, pu8data) )
            {
                printf("devCOFDM_PassThroughI2C_WriteBytes Error \n");
                return FALSE;
            }
            ATBMI2CByPassOff();
         }
        return TRUE;
    #endif
    }
#endif

    UNUSED(U16SlaveID);
    UNUSED(u8AddrNum);
    UNUSED(paddr);
    UNUSED(u16size);
    UNUSED(pu8data);

    return TRUE;

#endif
#endif  //(FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H)

}

#if 0
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)

U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData;
    if((RegAddr >= 0xC000) && (RegAddr <= 0xCEFF))
        MSB1200_ReadRaptor(RegAddr, &RegData);
    else
        MSB1200_ReadReg(RegAddr, &RegData);
    return (U16) RegData;
}

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
    if((RegAddr >= 0xC000) && (RegAddr <= 0xCEFF))
        return MSB1200_WriteRaptor( RegAddr, (U8)RegData);
    else
        return MSB1200_WriteReg( RegAddr, (U8)RegData);
}
#elif(FRONTEND_DEMOD_TYPE == MSTAR_MSB124X_DVBT)
U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;
    ReadReg(RegAddr, &RegData);
    return (U16) RegData;
}
BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
   return WriteReg( RegAddr,(U8) RegData);
}

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD)

U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData;
    MSB1210_ReadReg(RegAddr, &RegData);
    return (U16) RegData;
}
/*
EN_DEVICE_DEMOD_TYPE devCOFDM_GetCurrentDemodulatorType(void)
{
    //DBG_DEMOD_FLOW(printf("%s(),%d,type is %d\n",__func__,__LINE__,(int)device_demodulator_extend_m_enCurrentDemodulator_Type));
    return GetCurrentDemodulatorType();
}

BOOLEAN devCOFDM_SetCurrentDemodulatorType(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    //DBG_DEMOD_FLOW(printf("%s(),%d,type is %d\n",__func__,__LINE__,(int)device_demodulator_extend_m_enCurrentDemodulator_Type));
    return SetCurrentDemodulatorType(enDemodType);
}
*/

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
    return MSB1210_WriteReg( RegAddr, (U8)RegData);
}

#elif (  FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD         \
      || FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD         \
      )
U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;

  #if USE_UTOPIA
    MDrv_DMD_DVBT_GetReg(RegAddr, &RegData);
  #else
    INTERN_DVBT_ReadReg(RegAddr, &RegData);
  #endif
    return (U16) RegData;
}

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
  #if USE_UTOPIA
    return MDrv_DMD_DVBT_SetReg( RegAddr,(U8) RegData);
  #else
    return INTERN_DVBT_WriteReg( RegAddr,(U8) RegData);
  #endif
}
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;
    EXTERN_DTMB_ReadReg(RegAddr, &RegData);
    return (U16) RegData;
}

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
    return EXTERN_DTMB_WriteReg( RegAddr,(U8) RegData);
}

#elif (FRONTEND_DEMOD_TYPE == HDIC_2311)
U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;
    HDIC2311_ReadRegister(RegAddr, &RegData);
    return (U16) RegData;
}

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
    return (HDIC2311_WriteRegister( RegAddr,(U8) RegData) == HDIC_NO_ERROR);
}

#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ISDBT_DEMOD)
U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;
    INTERN_ISDBT_ReadReg(RegAddr, &RegData);
    return (U16) RegData;
}

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
    return INTERN_ISDBT_WriteReg( RegAddr,(U8) RegData);
}
#elif (FRONTEND_DEMOD_TYPE == EXTERNAL_DTMB_DEMOD)
U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;
    EXTERN_DTMB_ReadReg(RegAddr, &RegData);
    return (U16) RegData;
}

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
    return EXTERN_DTMB_WriteReg( RegAddr,(U8) RegData);
}
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DTMB_DEMOD)
U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;
    INTERN_DTMB_ReadReg(RegAddr, &RegData);
    return (U16) RegData;
}

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
    return INTERN_DTMB_WriteReg( RegAddr,(U8) RegData);
}

#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB101M_DTMB)
U16 devCOFDM_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;
    EXTERN_DTMB_ReadReg(RegAddr, &RegData);
    return (U16) RegData;
}

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{
    return EXTERN_DTMB_WriteReg( RegAddr,(U8) RegData);
}

#endif

#endif



#if ENABLE_DVBT
U16 devCOFDM_DVBT_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;

#if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
  #if DEMOD_DVBT_USE_UTOPIA
    MDrv_DMD_DVBT_GetReg(RegAddr, &RegData);
  #else
    INTERN_DVBT_ReadReg(RegAddr, &RegData);
  #endif
#elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    ReadReg(RegAddr, &RegData);
#else
    UNUSED(RegAddr);
#endif
    return (U16) RegData;

}
#endif

#if 0//ENABLE_DVBC
U16 devCOFDM_DVBC_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;

#if(FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD)
  #if DEMOD_DVBC_USE_UTOPIA
    MDrv_DMD_DVBC_GetReg(RegAddr, &RegData);
  #else
    INTERN_DVBC_ReadReg(RegAddr, &RegData);
  #endif
#elif(FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
    ReadReg(RegAddr, &RegData);
#else
    UNUSED(RegAddr);
#endif
    return (U16) RegData;
}
#endif

#if 0//ENABLE_DTMB
U16 devCOFDM_DTMB_ReadReg(U16 RegAddr)
{
    U8 RegData = 0;

#if(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
    INTERN_DTMB_ReadReg(RegAddr, &RegData);
#elif(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)
    EXTERN_DTMB_ReadReg(RegAddr, &RegData);
#elif(FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
    EXTERN_DTMB_ReadReg(RegAddr, &RegData);
#else
    UNUSED(RegAddr);
#endif
    return (U16) RegData;
}
#endif



#if 0

BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData)
{

    #if ENABLE_DVBT
    if(IsDVBTInUse())
    {
        #if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
          #if DEMOD_DVBT_USE_UTOPIA
            return MDrv_DMD_DVBT_SetReg( RegAddr,(U8) RegData);
          #else
            return INTERN_DVBT_WriteReg( RegAddr,(U8) RegData);
          #endif
        #elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
            return WriteReg( RegAddr,(U8) RegData);
        #endif
    }
    #endif
    #if ENABLE_DVBC
    if(IsDVBCInUse())
    {
        #if(FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD)
          #if DEMOD_DVBC_USE_UTOPIA
            return MDrv_DMD_DVBT_SetReg( RegAddr,(U8) RegData);
          #else
            return INTERN_DVBT_WriteReg( RegAddr,(U8) RegData);
          #endif
        #elif(FRONTEND_DEMOD_DVBC_TYPE == MSTAR_MSB124X_DVBT)
            return WriteReg( RegAddr,(U8) RegData);
        #endif
    }
    #endif
    #if ENABLE_DTMB
    if(IsDTMBInUse())
    {
        #if(FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)
            return INTERN_DTMB_WriteReg( RegAddr,(U8) RegData);

        #elif ( (FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)        \
              ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) )
             return EXTERN_DTMB_WriteReg( RegAddr,(U8) RegData);

        #elif(FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)
            return EXTERN_DTMB_WriteReg( RegAddr,(U8) RegData);
        #endif
    }
    #endif
    #if ENABLE_ISDBT
    if(IsISDBTInUse())
    {
        #if(FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
            return INTERN_ISDBT_WriteReg( RegAddr,(U8) RegData);
        #elif(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB1400_DEMOD)
          #if DEMOD_ISDBT_USE_UTOPIA
            return MDrv_DMD_DVBT_SetReg( RegAddr,(U8) RegData);
          #else
            return INTERN_DVBT_WriteReg( RegAddr,(U8) RegData);
          #endif
        #endif
    }
    #endif

    UNUSED(RegAddr);
    UNUSED(RegData);
    return FALSE;

}

#endif

#if (ENABLE_DTMB || ENABLE_DVBT)
BOOLEAN devCOFDM_DVBT_WriteReg(U16 RegAddr, U16 RegData)
{

#if(FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
  #if DEMOD_DVBT_USE_UTOPIA
    return MDrv_DMD_DVBT_SetReg( RegAddr,(U8) RegData);
  #else
    return INTERN_DVBT_WriteReg( RegAddr,(U8) RegData);
  #endif
#elif(FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT)
    return WriteReg( RegAddr,(U8) RegData);
#else
    UNUSED(RegAddr);
    UNUSED(RegData);
    return FALSE;
#endif

}
#endif


MS_U16 devCOFDM_GetPacketError(void)
{
    MS_U16 u16Err = 0;

#if (FRONTEND_DEMOD_DVBT_TYPE == EMBEDDED_DVBT_DEMOD)
  #if DEMOD_DVBT_USE_UTOPIA
    MDrv_DMD_DVBT_GetPacketErr(&u16Err);
  #else
    u16Err=0;
  #endif
#else
    UNUSED(u16Err);
#endif

    return u16Err;
}
/*
MS_BOOL devCOFDM_GetCurrentPlpID(MS_U8 *pu8PlpID)
{
    MS_BOOL bRet;

    bRet = DTV_Get_Current_Plp_Id(pu8PlpID);

    printf("%d T2 mdev_CofdmSetPlpGroupID PlpID:%d\n",bRet,*pu8PlpID);

    return bRet;
}*/

#endif //#if ENABLE_DTV

