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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Tuner_A.h
/// MStar Application Interface for Tuner
/// @brief API for tuner settings
/// @author MStar Semiconductor, Inc.
//
// Tuner settings differ from front end suppliers. Please check front end type define
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_TUNER_ATSC_C
/******************************************************************************/
/* Header Files                                                               */
/******************************************************************************/
#include <string.h>
#include <stdio.h>

#include "datatype.h"
#include "debug.h"
#include "Board.h"
#include "SysInit.h"
#include "msAPI_Global.h"
#include "msAPI_VD.h"
#include "msAPI_Tuner_ATSC.h"
#include "msAPI_Timer.h"
#include "msAPI_VD.h"
#include "msAPI_Demod.h"

#include "GPIO.h"
#include "chip/bond.h"
#include "drvIIC.h"
#include "apiDMX.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "msKeypad.h"
#include "MApp_TopStateMachine.h"
#include "msAPI_Scan_ATSC.h"
#include "MApp_GlobalVar.h"
#if( CHAKRA3_AUTO_TEST )
#include "MApp_AutoTest.h"
#endif

#if 0
#if (FRONTEND_DEMOD_TYPE==LG_3303_DEMODE)
#include "LGDT3303API.c"
#elif (FRONTEND_DEMOD_TYPE==SAMSUNG_S5H1409_DEMODE)
#include "SamsungDTVS205.c"
#elif (FRONTEND_DEMOD_TYPE==SAMSUNG_S5H1410_DEMODE)
#include "S5H1410_Ver1.2.C"
#elif (FRONTEND_DEMOD_TYPE==MSTAR_MSB1501_DEMODE)
#include "MSB1501.c"
#elif (FRONTEND_DEMOD_TYPE==EMBEDDED_ATSC_DEMOD)

#if (DEMOD_ATSC_USE_UTOPIA)
#include "drvDMD_ATSC.h"
#include "drvDMD_common.h"

static U8 u8DMD_ATSC_InitExt[]={1}; // RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning
#else
#include "INTERN_ATSC.c"
#endif

/*
static U32  g_u32AFECCount;
#define DEMOD_AFEC_LOCK_COUNT  3000
#if (ENABLE_DTV_NOSIGNAL_THRESHOLD)
#define DEMOD_VSB_NOSIGNAL_THRESHOLD  38
#define DEMOD_64QAM_NOSIGNAL_THRESHOLD  51
#define DEMOD_256QAM_NOSIGNAL_THRESHOLD  66
#endif
*/
#else
#error "DEMOD not support"
#endif
#endif

//
#if (FRONTEND_DEMOD_ATSC_TYPE==EMBEDDED_ATSC_DEMOD)
  #if (DEMOD_ATSC_USE_UTOPIA)
    #include "drvDMD_ATSC.h"
    #include "drvDMD_common.h"
  #endif
#endif
//


#if(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)
#include "IF_Demodulator.h"
#endif
#include "drvVIF.h"
#include "drvIIC.h"

#include "RF_Tuner_ATSC.h"

//==============================================================================

#define DEBUG_API_TUNER_ATSC(x)     //x
#define TUNER_API_DBG(y)            //y

#define DEBUG_API_TUNER_FREQ_ATSC(x)    //x

#define NEW_SCAN_API_DBG(y)    //y
#define AFT_CHECK_API_DBG(y)   //y

#define DEBUG_API_TUNER_DEMOD_ATSC(x)     //x


#define GET_FREQ_OFFSET_NEW     1

//==============================================================================

typedef enum ADC_PATTERN
{
     BOTTOM_STABLE_POINT,     // 0 adc pattern .
     LOW_STABLE_POINT,      // 1 adc pattern.
     MATCH_STABLE_POINT,      // 2 adc pattern.
     HIGH_STABLE_POINT,      // 3 adc pattern.
     UNSTABLE_POINT         // 4 adc pattern.
} ADC_PATTERN_T;

//==============================================================================

MS_TP_SETTING_ATSC stCurrentTPSetting; //current setting of front end

//==============================================================================

/******************************************************************************/
/// API for lnitialize current TP setting::
/******************************************************************************/

#define ENABLE_TEST_TUNER 0
#if ENABLE_TEST_TUNER
void msAPI_Tuner_TestFunction(void);
#endif
//*************************************************************************
//Function name:    msAPI_Tuner_InitCurrentTPSetting_ATSC
//Description:      This function init TPSetting
//  [doxygen]
/// This function init TPSetting
//*************************************************************************
void msAPI_Tuner_InitCurrentTPSetting_ATSC(void)
{
    DEBUG_API_TUNER_ATSC( printf("msAPI_Tuner_InitCurrentTPSetting_ATSC()\n"); );

    memset(&stCurrentTPSetting, 0, sizeof(stCurrentTPSetting));
}

//*************************************************************************
//Function name:    msAPI_Tuner_PaThruI2C
//Description:      This function Contorl Tuner bypass Demod
//  [doxygen]
/// This function Contorl Tuner bypass Demod
/// @param bEnable \b IN: Enable bypass Demod to control Tuner
///                       Disable bypass Demode
/// @return - return Tuner Bypass status
//*************************************************************************
void msAPI_Tuner_PaThruI2C(BOOLEAN bEnable)
{
    BOOLEAN bRet = FALSE;

    if (bEnable == TRUE)
    {
    #if (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
      #if (DEMOD_ATSC_USE_UTOPIA)
        //Unused
        bRet = TRUE;
      #else
        bRet = INTERN_ATSC_RepeaterEnable();
      #endif
    #endif

        if (bRet == FALSE)
        {
            printf("Enable Tuner Bypass Error\n");
        }
    }
    else
    {
    #if (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
      #if (DEMOD_ATSC_USE_UTOPIA)
        //Unused
        bRet = TRUE;
      #else
        bRet = INTERN_ATSC_RepeaterDisable();
      #endif
    #endif

        if (bRet == FALSE)
        {
            printf("Disable Tuner Bypass Error\n");
        }
    }
}

void msAPI_Tuner_Serial_Control_ATSC(BOOLEAN bParallelMode)
{
    BOOLEAN bEnable;


    DEBUG_API_TUNER_ATSC( printf("msAPI_Tuner_Serial_Control_ATSC(bParallelMode=%u)\n", bParallelMode););

#if ENABLE_CI
    if(bParallelMode)
    {
        bEnable = FALSE;
    }
    else
    {
        bEnable = TRUE;
    }
#else
    UNUSED(bParallelMode);
    bEnable = (!TS_PARALLEL_ATSC_OUTPUT);
#endif


#if TS_FROM_PLAYCARD
    MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, TRUE, TRUE);
    return;
#endif

    DEBUG_API_TUNER_ATSC( printf(" Serial=%u\n", bEnable); );
#if 0
    if( bEnable == TRUE ) // Serial
    {
//        msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ONE, MSAPI_DMX_DATAPATH_IN_SERIAL, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, FALSE);
    }
    else
    {
    	#if(FRONTEND_DEMOD_TYPE == LEGEND_8G13_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G42_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G52_DEMOD||FRONTEND_DEMOD_TYPE == LEGEND_8G80_DEMOD)
            #ifdef HSS_TWO_DEMOD
                if(devCOFDM_GetDemodType()==E_DEMOD_8G42)
                    //msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ZERO, MSAPI_DMX_DATAPATH_IN_PARALLEL, MSAPI_DMX_DATAPATH_SYNCMODE_INTERNAL);
                    MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, FALSE, TRUE);
                else
                   // msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ZERO, MSAPI_DMX_DATAPATH_IN_PARALLEL, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
                    MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
            #else
	                //msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ZERO, MSAPI_DMX_DATAPATH_IN_PARALLEL, MSAPI_DMX_DATAPATH_SYNCMODE_INTERNAL);
					#ifdef HISENSE_6I78
				  	MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT1, FALSE, FALSE, TRUE);
					#else
					MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, FALSE, TRUE);
					#endif

            #endif
        #else

            //msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_TS_ZERO, MSAPI_DMX_DATAPATH_IN_PARALLEL, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
            MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, TRUE);
        #endif

    }
#else
    #if(FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_DEMOD, FALSE, TRUE, !bEnable);
    #elif(FRONTEND_DEMOD_ATSC_TYPE == LEGEND_8G13_DEMOD)
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_EXT_INPUT0, FALSE, FALSE, !bEnable);
    #endif
#endif
}

//*************************************************************************
//Function name:    msAPI_Tuner_Init_ATSC
//Description:      This function init Tuner only
//  [doxygen]
/// This function init Tuner
/// @param bEnable \b IN: None
///
//*************************************************************************
#if 0
void msAPI_Tuner_Init_ATSC(void)
{

#if ( (FRONTEND_TUNER_TYPE==THOMSON_DTT7630_TUNER)||(FRONTEND_TUNER_TYPE==PHILIPS_FQD1236_TUNER)||(FRONTEND_TUNER_TYPE==LG_TDVS_H703P_TUNER))

    msAPI_Tuner_PaThruI2C(ENABLE);

    TDA9885_Init();

    msAPI_Tuner_PaThruI2C(DISABLE);

#elif (FRONTEND_TUNER_TYPE==MSTAR_MSR1200)

    msAPI_Tuner_PaThruI2C(ENABLE);

    MSR1200_Init(DEMOD_ATSC_MODE_8VSB);

    TDA9885_Init();
    msAPI_Tuner_PaThruI2C(DISABLE);

#elif (FRONTEND_TUNER_TYPE == NXP_TDA18273_TUNER)
    msAPI_Tuner_PaThruI2C(ENABLE);
	NUTUNE_FK1602_Init();
    msAPI_Tuner_PaThruI2C(DISABLE);
	//printf("\n Tm_Tda18273_Init");
#elif (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
    msAPI_Tuner_PaThruI2C(ENABLE);
    NXP_TDA18274_Init();
    msAPI_Tuner_PaThruI2C(DISABLE);
	//printf("\n Tm_Tda18273_Init");
#elif (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)
	msAPI_Tuner_PaThruI2C(ENABLE);
	devDigitalTuner_Init();
	msAPI_Tuner_PaThruI2C(DISABLE);
#elif (FRONTEND_TUNER_TYPE == NXP_TDA18275A_TUNER)
     msAPI_Tuner_PaThruI2C(ENABLE);
     TDA18275A_Initial();
     msAPI_Tuner_PaThruI2C(DISABLE);
#elif(FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)
    msAPI_Tuner_PaThruI2C(ENABLE);
    SILAB_2151_TUNER_Init();
    msAPI_Tuner_PaThruI2C(DISABLE);
#elif(FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER)
    msAPI_Tuner_PaThruI2C(ENABLE);
    if(Rafael_R828_Initial())
    {
        printf("---R828 Init OK!---\n");
    }
    else
    {
        printf("---R828 Init Error!---\n");
    }
    msAPI_Tuner_PaThruI2C(DISABLE);

#elif(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)
		msAPI_Tuner_PaThruI2C(ENABLE);
		if(Rafael_R840_Initial())
		{
			printf("---R840 Init OK!---\n");
		}
		else
		{
			printf("---R840 Init Error!---\n");
		}
		msAPI_Tuner_PaThruI2C(DISABLE);
#endif
}
#endif
void msAPI_Tuner_ATSC_Init_FreqVar(void)
{
    FREQ_OFFSET_RANGE_LEFT=NTSC_FREQ_OFFSET_LEFT/FREQ_STEP;
    FREQ_OFFSET_RANGE_RIGHT=NTSC_FREQ_OFFSET_RIGHT/FREQ_STEP;
    FREQ_OFFSET_RANGE_Ch5Ch6_RIGHT=NTSC_FREQ_OFFSET_RIGHT_CH5CH6/FREQ_STEP;

#if VIF_SCOPE_1M
    NTSC_AUTO_FREQ_OFFSET_TABLE[0]=0;
    NTSC_AUTO_FREQ_OFFSET_TABLE[1]= (VIF_COVERAGE_BOUNDRY_LEFT-VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;   //(NTSC_FREQ_OFFSET_LEFT+VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_AUTO_FREQ_OFFSET_TABLE[2]= (VIF_COVERAGE_BOUNDRY_RIGHT+VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
#else
    NTSC_AUTO_FREQ_OFFSET_TABLE[0]=0;
    NTSC_AUTO_FREQ_OFFSET_TABLE[1]= (VIF_COVERAGE_BOUNDRY_LEFT-VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;   //(NTSC_FREQ_OFFSET_LEFT+VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_AUTO_FREQ_OFFSET_TABLE[2]= ((VIF_COVERAGE_BOUNDRY_LEFT*2)-VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;   //(NTSC_FREQ_OFFSET_RIGHT-VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
    NTSC_AUTO_FREQ_OFFSET_TABLE[3]= (VIF_COVERAGE_BOUNDRY_RIGHT+VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_AUTO_FREQ_OFFSET_TABLE[4]= ((VIF_COVERAGE_BOUNDRY_RIGHT*2)+VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
#endif

#if VIF_SCOPE_1M
    NTSC_CH5CH6_OFFSET_TABLE[0]=0;
    NTSC_CH5CH6_OFFSET_TABLE[1]=(VIF_COVERAGE_BOUNDRY_LEFT-VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_CH5CH6_OFFSET_TABLE[2]=(VIF_COVERAGE_BOUNDRY_RIGHT+VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
    //printf("NTSC_CH5CH6_OFFSET_TABLE[1]=%d\n", NTSC_CH5CH6_OFFSET_TABLE[1]);
    //printf("NTSC_CH5CH6_OFFSET_TABLE[2]=%d\n", NTSC_CH5CH6_OFFSET_TABLE[2]);
#else
    NTSC_CH5CH6_OFFSET_TABLE[0]=0;
    NTSC_CH5CH6_OFFSET_TABLE[1]=(VIF_COVERAGE_BOUNDRY_LEFT-VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_CH5CH6_OFFSET_TABLE[2]=((VIF_COVERAGE_BOUNDRY_LEFT*2)-VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
    NTSC_CH5CH6_OFFSET_TABLE[3]=(VIF_COVERAGE_BOUNDRY_RIGHT+VD_FREQ_OFFSET_LEFT_RANGE)/FREQ_STEP;
    NTSC_CH5CH6_OFFSET_TABLE[4]=((VIF_COVERAGE_BOUNDRY_RIGHT*2)+VD_FREQ_OFFSET_RIGHT_RANGE)/FREQ_STEP;
#endif

}

//*************************************************************************
//Function name:    msAPI_Tuner_Initialization_ATSC
//Description:      This function init Tuner & setting TS Interface
//  [doxygen]
/// This function init Tuner & setting TS Interface
/// @param bEnable \b IN: Enable bypass Demod to control Tuner
///                       Disable bypass Demode
//*************************************************************************
void msAPI_Tuner_Initialization_ATSC(BOOL bSrcChg)
{
    DEBUG_API_TUNER_ATSC( printf("msAPI_Tuner_Initialization_ATSC(bSrcChg=%u)", bSrcChg););

    bSrcChg=bSrcChg;

    msAPI_Tuner_Serial_Control_ATSC(FALSE);

  #if (TV_FREQ_SHIFT_CLOCK)
     msAPI_Tuner_Patch_ResetTVShiftClk();
  #endif

    msAPI_Tuner_InitCurrentTPSetting_ATSC();

#if 1// Use msAPI_Demod_ATSC ...
    msAPI_Demod_ATSC_Init();

#else

#if TS_THROUGH_LVDS
    return;
#endif

#if TS_FROM_PLAYCARD
    return;
#endif

#if (FRONTEND_DEMOD_TYPE==LG_3303_DEMODE)

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

#elif (FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1409_DEMODE)

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
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1501_DEMODE)
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
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ATSC_DEMOD)
    if (bSrcChg)
    {
#if (DEMOD_ATSC_USE_UTOPIA)
        if (bDmdInit)
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

        if(MDrv_DMD_ATSC_Init(&sDMD_ATSC_InitData, sizeof(sDMD_ATSC_InitData)))
        {
            printf("MDrv_DMD_ATSC_Init done\n");
        }
        else
        {
            printf("MDrv_DMD_ATSC_Init fail\n");
        }

        bDmdInit = TRUE;

#else

        if(INTERN_ATSC_Init(DEMOD_IF_KHz, DEMOD_IQSWAP))// IF_KHZ, isIQSWAP
        {
            TUNER_API_DBG(printf("\r\nINTERN_ATSC Init done"));
        }
        else
        {
            TUNER_API_DBG(printf("\r\nINTERN_ATSC Init fail"));
        }
#endif

      TUNER_API_DBG(printf("INTERN_ATSC Init......\r\n"));
    }

    #if TS_PARALLEL_OUTPUT
    #else
    #endif
    #if TS_CLK_INV
    #else
    #endif

#elif (FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1410_DEMODE)

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

#endif

    // Move to msAPI_DTVSystem_ATSC_Init()
    //msAPI_Tuner_ATSC_Init_FreqVar();
}

//*************************************************************************
//Function name:    msAPI_Tuner_SetModulation
//Description:      This function Set Demod Modulation type of TS
//  [doxygen]
///This function Set Demod Modulation type of TS
/// @param enModulation \b IN: Modulation type of TS
//*************************************************************************
/*
void msAPI_Tuner_SetModulation(EN_DEMOD_ATSC_MODE enModulation)
{
    DEBUG_API_TUNER_ATSC( printf("msAPI_Tuner_SetModulation(enModulation=%u)\n", enModulation); );


    #if TS_THROUGH_LVDS
        stCurrentTPSetting.fModulation = enModulation;
        return;
    #endif

    #if (FRONTEND_DEMOD_TYPE==LG_3303_DEMODE)
        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                LgdtInit3303(LGDT_VSB);
                break;
            case DEMOD_ATSC_MODE_256QAM:
                LgdtInit3303(LGDT_QAM256);
                break;
            case DEMOD_ATSC_MODE_64QAM:
                LgdtInit3303(LGDT_QAM64);
                break;
        }
    #elif (FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1409_DEMODE)
        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                TUNER_API_DBG(printf("\r\nS5H1409 VSB Mode"););
                SamsungS5H1409VsbMode();
                break;

            case DEMOD_ATSC_MODE_256QAM:
                TUNER_API_DBG(printf("\r\nS5H1409 256 QAM Mode"););
                SamsungS5H1409x256QamMode();
                break;

            case DEMOD_ATSC_MODE_64QAM:
                TUNER_API_DBG(printf("\r\nS5H1409 64 QAM Mode"););
                SamsungS5H1409x64QamMode();
                break;
            default:
                break;
        }
    #elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1501_DEMODE)
        enModulation = enModulation;
    #elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ATSC_DEMOD)
        enModulation = enModulation;
    #elif (FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1410_DEMODE)
        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                TUNER_API_DBG(printf("\r\nS5H1410 VSB Mode"););
                Sec_1410xVsbMode();
                break;

            case DEMOD_ATSC_MODE_256QAM:
                TUNER_API_DBG(printf("\r\nS5H1410 256 QAM Mode"););
                Sec_1410x256QamMode();
                break;

            case DEMOD_ATSC_MODE_64QAM:
                TUNER_API_DBG(printf("\r\nS5H1410 64 QAM Mode"););
                Sec_1410x64QamMode();
                break;
        }
#endif

    stCurrentTPSetting.fModulation = enModulation;
}
*/

//*************************************************************************
//Function name:    msAPI_Tuner_Tune2RfCh_ATSC
//Description:      This function Set RF channel related parameters, such as RF frequency, modulation type
//  [doxygen]
///This function Set RF channel related parameter
///@param pstTPSetting \b IN pointer to RF channel information structure
//*************************************************************************
void msAPI_Tuner_Tune2RfCh_ATSC(MS_TP_SETTING_ATSC *pstTPSetting)
{
    DEBUG_API_TUNER_ATSC( printf("msAPI_Tuner_Tune2RfCh_ATSC(Freq=%u, Mod=%u)\n", pstTPSetting->u16Frequency, pstTPSetting->fModulation); );
    //DEBUG_API_TUNER_FREQ_ATSC( printf("FREQ_STEPx10=%u => u32Freq=%u\n", (U32)(FREQ_STEP*10), (U32)(FREQ_STEP*10)*(pstTPSetting->u16Frequency)/10  ); );

#if TS_FROM_PLAYCARD
    return;
#endif

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("Tune2RfCh start");
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    if( (pstTPSetting->u16Frequency != stCurrentTPSetting.u16Frequency)
      ||(pstTPSetting->fModulation != stCurrentTPSetting.fModulation)
      ||(pstTPSetting->fSpectrum != stCurrentTPSetting.fSpectrum)
      )
    {
#if TS_THROUGH_LVDS
        stCurrentTPSetting.u16Frequency = pstTPSetting->u16Frequency;
        stCurrentTPSetting.fModulation = pstTPSetting->fModulation;
        stCurrentTPSetting.fSpectrum=pstTPSetting->fSpectrum;
        return;
#endif

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("Tune2RF - Start" );
    #endif

        // Set tuner freq
        msAPI_Tuner_SetFreq(pstTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation);

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("Tune2RF - SetFreq" );
    #endif

        if( (pstTPSetting->fModulation) != DEMOD_ATSC_MODE_NTSC ) // Is DTV
        {
            msAPI_Demod_ATSC_Set_Mode((EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation, (EN_DEMOD_ATSC_SPECTRUM_MODE)pstTPSetting->fSpectrum);

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("Tune2RF - Demod_Set_Mode" );
    #endif

        }
        else // Is ATV
        {
            //msAPI_Demodulator_Reset_ATSC();
            // Why ATV should reset Demod??
            msAPI_Demod_ATSC_Reset();

            if( bIsScanNSTCState == 0 )
            {
            #if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)
                // ATV mode
                msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_ATV );  // vd mcu code should be loaded before vif initial
                EXT_RF_AGC_ON();
                MDrv_IFDM_Init();
                MDrv_IFDM_SetIF(IF_FREQ_MN);
                MDrv_IFDM_SetVifIfFreq(TUNER_IF_FREQ_KHz);
                msAPI_IFDM_SetVIF_Notch();
            #endif

                bIsScanNSTCState = 1;
            }
            else
            {
                MDrv_IFDM_Reset();
            }

        }

#if (ENABLE_CHCHANGETIME)
        printf(">>>[ChChangeTime][Set Freq done]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif

        stCurrentTPSetting.u16Frequency = pstTPSetting->u16Frequency;
        stCurrentTPSetting.fModulation = pstTPSetting->fModulation;
        stCurrentTPSetting.fSpectrum = pstTPSetting->fSpectrum;
    }
    else
    {
        printf("\nATSC: Same TP => Skip Tune2RF\n");
    }

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("Tune2RfCh done");
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

//*************************************************************************
//Function name:    msAPI_Tuner_IsSameRfChannel_ATSC
//Description:      This function Check is same RF channel
//  [doxygen]
/// This function Check is same RF channel
///@param pstTPSetting \b IN pointer to RF channel information structure
///@return - BOOLEAN\b
///        - TRUE :The same channel
///        - FALSE : Different Channel
//*************************************************************************

BOOLEAN msAPI_Tuner_IsSameRfChannel_ATSC(MS_TP_SETTING_ATSC *pstTPSetting)
{
    if(pstTPSetting->u16Frequency==stCurrentTPSetting.u16Frequency &&
       pstTPSetting->fModulation==stCurrentTPSetting.fModulation&&
       pstTPSetting->fSpectrum==stCurrentTPSetting.fSpectrum)
           return TRUE;
    else
        return FALSE;
}


//*************************************************************************
//Function name:    msAPI_Tuner_PowerOnOff_ATSC
//Description:      This function will power off Demode
//  [doxygen]
/// This function will power off Demode
///@param bPower \b IN  Enable or Diable Demode into sleep mode
//*************************************************************************
void msAPI_Tuner_PowerOnOff_ATSC(BOOLEAN bPower)
{
#if TS_THROUGH_LVDS
    return;
#endif

#if (FRONTEND_DEMOD_ATSC_TYPE == LG_3303_DEMODE)
    LgdtPowerOnOff(bPower);

#elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
    if(bPower)
        SamsungS5H1409xSleepOff();
    else
        SamsungS5H1409xSleepOn();

#elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
    if(bPower)
    {
        ;
    }
#elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
    if(bPower)
    {
        ;
    }
#elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
    if(bPower)
    {
        Sec_1410xSleepOff();
    }
    else
    {
        Sec_1410xSleepOn();
        MDrv_IIC_Write2Bytes(IIC_1410x_RegId, 0xf5, 0x0000);
    }
#endif
}



//*************************************************************************
//Function name:    msAPI_Tuner_CheckSignalSNR
//Description:      This function will report SNR from Demode
//  [doxygen]
/// This function will report SNR from Demode
///@param NULL \b IN  NULL
/// @return - Current signal SNR condition
//*************************************************************************
EN_SIGNAL_CONDITION msAPI_Tuner_CheckSignalSNR(void)
{
    EN_SIGNAL_CONDITION enSNRStatus;
#if (TS_THROUGH_LVDS || TS_FROM_PLAYCARD)
    enSNRStatus = SIGNAL_STRONG;
    return enSNRStatus;
#endif

    #if (FRONTEND_DEMOD_ATSC_TYPE == LG_3303_DEMODE)

    if(LgdtCheckSignalCondition(&enSNRStatus) == LGDT_ERR_NO)
    {
        TUNER_API_DBG(printf("Get SNR Good\n"));
    }
    else
    {
        TUNER_API_DBG(printf("Get SNR Error\n"));
        enSNRStatus=SIGNAL_NO;
    }

    switch(enSNRStatus)
    {
        case LGDT_SIGNAL_NO:
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("No signal\n"));
            break;
        case LGDT_SIGNAL_WEAK:
            enSNRStatus=SIGNAL_WEAK;
            TUNER_API_DBG(printf("Signal Weak\n"));
            break;
        case LGDT_SIGNAL_MODERATE:
            enSNRStatus=SIGNAL_MODERATE;
            TUNER_API_DBG(printf("Signal Mid\n"));
            break;
        case LGDT_SIGNAL_STRONG:
            enSNRStatus=SIGNAL_STRONG;
            TUNER_API_DBG(printf("Signal Strong\n"));
            break;
        case LGDT_SIGNAL_VERY_STRONG:
            enSNRStatus=SIGNAL_VERY_STRONG;
            TUNER_API_DBG(printf("Signal very Strong\n"));
            break;
        default :
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("Unknown Status \r\n"));
            break;
    }
    return enSNRStatus;

    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
    SamsungSignalCondition_t enSignalCondition;
    SamsungS5H1409xCheckSignalCondition(&enSignalCondition);

    switch(enSignalCondition)
    {
        case Samsung_SIGNAL_NO:
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("No signal\n"));
            break;
        case Samsung_SIGNAL_WEAK:
            enSNRStatus=SIGNAL_WEAK;
            TUNER_API_DBG(printf("Signal Weak\n"));
            break;
        case Samsung_SIGNAL_MODERATE:
            enSNRStatus=SIGNAL_MODERATE;
            TUNER_API_DBG(printf("Signal Mid\n"));
            break;
        case Samsung_SIGNAL_STRONG:
            enSNRStatus=SIGNAL_STRONG;
            TUNER_API_DBG(printf("Signal Strong\n"));
            break;
        case Samsung_SIGNAL_VERY_STRONG:
            enSNRStatus=SIGNAL_VERY_STRONG;
            TUNER_API_DBG(printf("Signal very Strong\n"));
            break;
        default :
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("Unknown Status \r\n"));
            break;
    }
    return enSNRStatus;
    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
    MSB1501SignalCondition_t enSignalCondition;
    MSB1501_CheckSignalCondition(&enSignalCondition);
    switch(enSignalCondition)
    {
        case MSB1501_SIGNAL_NO:
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("No signal\n"));
            break;
        case MSB1501_SIGNAL_WEAK:
            enSNRStatus=SIGNAL_WEAK;
            TUNER_API_DBG(printf("Signal Weak\n"));
            break;
        case MSB1501_SIGNAL_MODERATE:
            enSNRStatus=SIGNAL_MODERATE;
            TUNER_API_DBG(printf("Signal Mid\n"));
            break;
        case MSB1501_SIGNAL_STRONG:
            enSNRStatus=SIGNAL_STRONG;
            TUNER_API_DBG(printf("Signal Strong\n"));
            break;
        case MSB1501_SIGNAL_VERY_STRONG:
            enSNRStatus=SIGNAL_VERY_STRONG;
            TUNER_API_DBG(printf("Signal very Strong\n"));
            break;
        default :
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("Unknown Status \r\n"));
            break;
    }
    return enSNRStatus;
    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
    #if (DEMOD_ATSC_USE_UTOPIA)
    switch(MDrv_DMD_ATSC_GetSignalQuality())
    {
        case DMD_ATSC_SIGNAL_NO:
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("No signal\n"));
            break;
        case DMD_ATSC_SIGNAL_WEAK:
            enSNRStatus=SIGNAL_WEAK;
            TUNER_API_DBG(printf("Signal Weak\n"));
            break;
        case DMD_ATSC_SIGNAL_MODERATE:
            enSNRStatus=SIGNAL_MODERATE;
            TUNER_API_DBG(printf("Signal Mid\n"));
            break;
        case DMD_ATSC_SIGNAL_STRONG:
            enSNRStatus=SIGNAL_STRONG;
            TUNER_API_DBG(printf("Signal Strong\n"));
            break;
        case DMD_ATSC_SIGNAL_VERY_STRONG:
            enSNRStatus=SIGNAL_VERY_STRONG;
            TUNER_API_DBG(printf("Signal very Strong\n"));
            break;
        default :
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("Unknown Status \r\n"));
            break;
    }
    #else
    INTERN_ATSCSignalCondition_t enSignalCondition;
    INTERN_ATSC_CheckSignalCondition(&enSignalCondition);
    switch(enSignalCondition)
    {
        case INTERN_ATSC_SIGNAL_NO:
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("No signal\n"));
            break;
        case INTERN_ATSC_SIGNAL_WEAK:
            enSNRStatus=SIGNAL_WEAK;
            TUNER_API_DBG(printf("Signal Weak\n"));
            break;
        case INTERN_ATSC_SIGNAL_MODERATE:
            enSNRStatus=SIGNAL_MODERATE;
            TUNER_API_DBG(printf("Signal Mid\n"));
            break;
        case INTERN_ATSC_SIGNAL_STRONG:
            enSNRStatus=SIGNAL_STRONG;
            TUNER_API_DBG(printf("Signal Strong\n"));
            break;
        case INTERN_ATSC_SIGNAL_VERY_STRONG:
            enSNRStatus=SIGNAL_VERY_STRONG;
            TUNER_API_DBG(printf("Signal very Strong\n"));
            break;
        default :
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("Unknown Status \r\n"));
            break;
    }
    #endif
    return enSNRStatus;

    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
    Sec_1410xCheckSignalCondition(&enSNRStatus);
    switch(enSNRStatus)
    {
        case Samsung_SIGNAL_NO:
            //enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("No signal\n"));
            break;
        case Samsung_SIGNAL_WEAK:
            //enSNRStatus=SIGNAL_WEAK;
            TUNER_API_DBG(printf("Signal Weak\n"));
            break;
        case Samsung_SIGNAL_WEAK1:
            //enSNRStatus=SIGNAL_WEAK;
            TUNER_API_DBG(printf("Signal Weak\n"));
            break;
        case Samsung_SIGNAL_MODERATE:
            //enSNRStatus=SIGNAL_MODERATE;
            TUNER_API_DBG(printf("Signal Mid\n"));
            break;
        case Samsung_SIGNAL_MODERATE1:
            //enSNRStatus=SIGNAL_MODERATE;
            TUNER_API_DBG(printf("Signal Mid\n"));
            break;
        case Samsung_SIGNAL_MODERATE2:
            //enSNRStatus=SIGNAL_MODERATE;
            TUNER_API_DBG(printf("Signal Mid\n"));
            break;

        case Samsung_SIGNAL_STRONG:
            //enSNRStatus=SIGNAL_STRONG;
            TUNER_API_DBG(printf("Signal Strong\n"));
            break;
        case Samsung_SIGNAL_STRONG1:
            //enSNRStatus=SIGNAL_STRONG;
            TUNER_API_DBG(printf("Signal Strong\n"));
            break;
        case Samsung_SIGNAL_STRONG2:
            //enSNRStatus=SIGNAL_STRONG;
            TUNER_API_DBG(printf("Signal Strong\n"));
            break;

        case Samsung_SIGNAL_VERY_STRONG:
            //enSNRStatus=SIGNAL_VERY_STRONG;
            TUNER_API_DBG(printf("Signal very Strong\n"));
            break;
        case Samsung_SIGNAL_VERY_STRONG1:
            //enSNRStatus=SIGNAL_VERY_STRONG;
            TUNER_API_DBG(printf("Signal very Strong\n"));
            break;
        default :
            enSNRStatus=SIGNAL_NO;
            TUNER_API_DBG(printf("Unknown Status \r\n"));
            break;
    }

    return enSNRStatus;
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

BOOLEAN msAPI_Demodulator_Init(EN_DEMOD_ATSC_MODE enModulation, EN_DEMOD_ATSC_SPECTRUM_MODE enSpectrumType)
{
    DEBUG_API_TUNER_DEMOD_ATSC( PRINT_CUR_FUNCTION(); );
    return msAPI_Demod_ATSC_Set_Mode(enModulation, enSpectrumType);
#if 0

#if TS_THROUGH_LVDS
    return TRUE;
#else
    //MDrv_Demodulator_Init();
    {
    #if (FRONTEND_DEMOD_TYPE == LG_3303_DEMODE)

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

    #elif (FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1409_DEMODE)

        BOOLEAN u8Result=FALSE;
        enSpectrumType=enSpectrumType;  //Clear Warrning

        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                if(SamsungS5H1409xVSBScanInit()==TRUE)
                    u8Result=SamsungS5H1409VsbMode();
                NEW_SCAN_API_DBG(printf("Demod init S5H1409 VSB Mode! \r\n"););
                break;

            case DEMOD_ATSC_MODE_256QAM:
                u8Result=SamsungS5H1409x256QamMode();
                NEW_SCAN_API_DBG(printf("Demod init S5H1409 256 QAM Mode! \r\n"););
                break;

            case DEMOD_ATSC_MODE_64QAM:
                u8Result=SamsungS5H1409x64QamMode();
                NEW_SCAN_API_DBG(printf("Demod init S5H1409 64 QAM Mode! \r\n"););
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
    #elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1501_DEMODE)
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
    #elif (FRONTEND_DEMOD_TYPE == EMBEDDED_ATSC_DEMOD)
        BOOLEAN u8Result=FALSE;
        enSpectrumType=enSpectrumType;  //Clear Warrning
        u8Result=msAPI_Demodulator_Reset_ATSC();
        #if (DEMOD_ATSC_USE_UTOPIA)
        //Unused
        #else
        msAPI_Timer_Delayms(10);
        #endif

        switch(enModulation)
        {
            case DEMOD_ATSC_MODE_8VSB:
                #if (DEMOD_ATSC_USE_UTOPIA)
                u8Result=MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_ATSC_VSB, ENABLE);
                #else
                u8Result=INTERN_ATSC_VsbMode();
                #endif
                NEW_SCAN_API_DBG(printf("Demod init INTERN_ATSC VSB Mode! \r\n"););
                break;
            case DEMOD_ATSC_MODE_64QAM:
                #if (DEMOD_ATSC_USE_UTOPIA)
                u8Result=MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_ATSC_64QAM, ENABLE);
                #else
                u8Result=INTERN_ATSC_64QamMode();
                #endif
                NEW_SCAN_API_DBG(printf("Demod init INTERN_ATSC 64 QAM Mode! \r\n"););
                break;
            case DEMOD_ATSC_MODE_256QAM:
                #if (DEMOD_ATSC_USE_UTOPIA)
                u8Result=MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_ATSC_256QAM, ENABLE);
                #else
                u8Result=INTERN_ATSC_256QamMode();
                #endif
                NEW_SCAN_API_DBG(printf("Demod init INTERN_ATSC 256 QAM Mode! \r\n"););
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
    #elif (FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1410_DEMODE)

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
#endif      // TS_THROUGH_LVDS
#endif
}

//*************************************************************************
//Function name:    msAPI_Demodulator_Reset_ATSC
//Description:      This function will Reset Demode
//  [doxygen]
/// This function will Reset Demode
///@param NULL \b IN NULL
///@return - Reset Demode status
//*************************************************************************

BOOLEAN msAPI_Demodulator_Reset_ATSC(void)
{
    DEBUG_API_TUNER_DEMOD_ATSC( PRINT_CUR_FUNCTION(); );
    return msAPI_Demod_ATSC_Reset();
}

//*************************************************************************
//Function name:    msAPI_Demodulator_Get_Lock_ATSC
//Description:      This function will get VSB FEC or QAM Main Lock status from Demode
//  [doxygen]
/// This function will get VSB or QAM's  lock status from Demode
///@param enModulation \b IN Demode type of TS
///@return - return Lock status
///         - TRUE : Lock
///         - FALSE: Unlock
//*************************************************************************
BOOLEAN msAPI_Demodulator_Get_Lock_ATSC(EN_DEMOD_ATSC_MODE enModulation)
{
    // Use msAPI_Demod_ATSC
    return msAPI_Demod_ATSC_Get_Lock(enModulation);
#if 0
#if (TS_THROUGH_LVDS || SFU_AUTO_TEST)
return TRUE;
#else

#if (FRONTEND_DEMOD_TYPE == LG_3303_DEMODE)

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

#elif(FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1409_DEMODE)
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
#elif(FRONTEND_DEMOD_TYPE == MSTAR_MSB1501_DEMODE)
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
#elif(FRONTEND_DEMOD_TYPE == EMBEDDED_ATSC_DEMOD)
    BOOLEAN Result = FALSE;
    if(enModulation==DEMOD_ATSC_MODE_8VSB)
    {
        #if (DEMOD_USE_UTOPIA)
        if(DMD_ATSC_LOCK == MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_VSB_FECLOCK))
        {
            Result = TRUE;
        }
        #else
        Result=INTERN_ATSC_Vsb_FEC_Lock();
        #endif

        if(!Result)
        {
          #if (DEMOD_USE_UTOPIA)
            if((DMD_ATSC_LOCK != MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_VSB_FSYNCLOCK))
          #else
            if(INTERN_ATSC_Vsb_FSync_Lock() == FALSE
          #endif
            #if (ENABLE_DTV_NOSIGNAL_THRESHOLD)
            #if (DEMOD_USE_UTOPIA)
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
        #if (DEMOD_USE_UTOPIA)
        if(DMD_ATSC_LOCK == MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_QAM_MAINLOCK))
        {
            Result = TRUE;
        }
        #else
        Result=INTERN_ATSC_QAM_Main_Lock();
        #endif

        if(Result
            #if (ENABLE_DTV_NOSIGNAL_THRESHOLD)
            #if (DEMOD_USE_UTOPIA)
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

    #if TS_PARALLEL_OUTPUT
    #else
    #endif
    //printf(" => Result=%u\n", Result);
    return Result;

#elif(FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1410_DEMODE)
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
#endif //TS_THROUGH_LVDS
#endif
}



#if CHECK_KEY_WHILE_SCAN
#include "msIR.h"
#include "MApp_IR.h"
#include "MApp_Key.h"
#include "MApp_GlobalVar.h"
#endif


//*************************************************************************
//Function name:    msAPI_Tuner_Wait
//Description:      This function get IR status when scan condition
//  [doxygen]
/// This function get IR status when scan condition
///@param WaitTiming \b IN delay time
///@return - return detect IR
///         - TRUE : it doen't detect IR
///         - FALSE: Detect IR when scan delay
//*************************************************************************
BOOLEAN msAPI_Tuner_Wait(U32 WaitTiming)
{
    //printf("msAPI_Tuner_Wait(%u)\n", WaitTiming);

#if CHECK_KEY_WHILE_SCAN
    U32 StartWaitTime = msAPI_Timer_GetTime0();
    if ((u8KeyCode == KEY_MENU) || (u8KeyCode == KEY_EXIT) || (u8KeyCode == KEY_POWER))
        return FALSE;

    while(msAPI_Timer_DiffTimeFromNow(StartWaitTime) <= WaitTiming)
    {
        MApp_ProcessUserInput();
        if ((u8KeyCode == KEY_MENU) || (u8KeyCode == KEY_EXIT) || (u8KeyCode == KEY_POWER))
            return FALSE;
    }
#else
  #if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)
    {
        U32 u32StartTime = msAPI_Timer_GetTime0();

        while( msAPI_Timer_DiffTime_2(u32StartTime, msAPI_Timer_GetTime0()) < WaitTiming )
        {
            MDrv_VIF_Handler(TRUE);
            msAPI_Timer_Delayms(1);
        }
    }
  #else
    msAPI_Timer_Delayms(WaitTiming);
  #endif
#endif

    return TRUE;
}


void msAPI_DemodState_INIT_ATSC(void)
{
#if (FRONTEND_DEMOD_ATSC_TYPE==MSTAR_MSB1501_DEMODE)
   MSB1501_StatusINIT();
#elif (FRONTEND_DEMOD_ATSC_TYPE==EMBEDDED_ATSC_DEMOD)
    #if (DEMOD_ATSC_USE_UTOPIA)
    //Unused
    #else
   INTERN_ATSC_StatusINIT();
    #endif
#endif
}


//*************************************************************************
//Function name:    msAPI_VSB_Check_Lock
//Description:      This function get VSB lock status
//  [doxygen]
/// This function get VSB lock status
///@param NULL \b IN NULL
///@return - return Lock status
///         - TRUE : LOCK
///         - FALSE: UNLOCK
//*************************************************************************
EN_SCAN_RESULT msAPI_VSB_Check_Lock(void)
{
#if TS_FROM_PLAYCARD
    return LOCK;
#else

#if TS_THROUGH_LVDS
    return FE_LOCK;
#else

#if (FRONTEND_DEMOD_ATSC_TYPE == LG_3303_DEMODE)
    U16             PACKET_ERR_COUNT;
    double          SNR;

    //Dealy 50ms before get CR lock
    msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);
    //Check VSB CR Lock
    if(LGDT_ERR_UNLOCK==LgdtVSBCheckCRLock())
    {
        NEW_SCAN_API_DBG(printf("LgdtVSBCheckCRLock UNLOCK\n"));
        return FALSE;
    }

    //Check VSB Sync Lock
    if(LGDT_ERR_NO==LgdtVSBCheckSyncLock())
    {
        //Get VSB SNR Value
        if(LGDT_ERR_NO!=LgdtVSBGetSNRValue(&SNR))
            return FALSE;

        //Check VSB Packet Error
        if(LGDT_ERR_NO!=LgdtVSBPacketErrorCount(&PACKET_ERR_COUNT))
            return FALSE;

        if ((SNR <10)&&(PACKET_ERR_COUNT>0xFFF0))
        {
            NEW_SCAN_API_DBG(printf("\r\n LgdtVSBCheckSyncLock UNLOCK, SNR / PACKET_ERR_COUNT\n"));
            return FALSE;
        }
        else
        {
            NEW_SCAN_API_DBG(printf("\r\n LgdtVSBCheckSyncLock Lock \r\n"));
            return TRUE;
        }
    }
    NEW_SCAN_API_DBG(printf("\r\n LgdtVSBCheckSyncLock UNLOCK\n"));
    return FALSE;

#elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)

    U8 CheckLockCount;
    EN_SCAN_RESULT Result;

    Result=UNLOCK;
    for (CheckLockCount=0;CheckLockCount<6;CheckLockCount++)    //Wait 300ms
    {
        if (!msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME))
        {
            Result=CHECKEND;
            break;
        }
        if(SamsungS5H1409xVsb_Sync_Lock())
        {
            Result=LOCK;
            break;
        }
    }
    SamsungS5H1409xVSBScanEnd();
    return Result;
#elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)

    return MSB1501_VSBCheckLock();

#elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)

    #if (DEMOD_ATSC_USE_UTOPIA)
    DMD_ATSC_LOCK_STATUS eLockStatus = MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK);

    if(eLockStatus == DMD_ATSC_NULL)
    {
        eLockStatus = DMD_ATSC_UNLOCK;
        printf("[Error] Invalid demod lock status !!!\r\n");
    }
    return ((EN_SCAN_RESULT)eLockStatus);
    #else
    return INTERN_ATSC_VSBCheckLock();
    #endif

#elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)

    U8 CheckLockCount,Result=FALSE;
    for (CheckLockCount=0;CheckLockCount<6;CheckLockCount++)    //Wait 300ms
    {
        msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);
        //if(Sec_1410xQAMCheckLock())
        if ( Sec_1410xVsb_Sync_Lock() )    //**** SEC ATSC project****
        {
            Result=TRUE;
            break;
        }
    }
    return Result;
#endif

#endif  //TS_THROUGH_LVDS
#endif // TS_FROM_PLAYCARD
}

BOOLEAN msAPI_VSB_Check_PreLock(void)
{
#if (DEMOD_USE_UTOPIA)
    return (DMD_ATSC_LOCK == MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_VSB_PRELOCK));
#else
    return INTERN_ATSC_Vsb_FSync_Lock();
#endif
}


BOOLEAN msAPI_VSB_Check_FsyncLock(void)
{
#if (DEMOD_ATSC_USE_UTOPIA)
    return (DMD_ATSC_LOCK == MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_VSB_FSYNCLOCK));
#else
    return INTERN_ATSC_Vsb_FSync_Lock();
#endif
}

BOOLEAN msAPI_Qam_Check_PrecLock(void)
{
#if (DEMOD_ATSC_USE_UTOPIA)
    #if (NEW_DEMOD_SCAN)
    return (DMD_ATSC_LOCK == MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK));
    #else
    return (DMD_ATSC_LOCK == MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_QAM_PRELOCK));
    #endif
#else
    return INTERN_ATSC_QAM_PreLock();
#endif
}


//*************************************************************************
//Function name:    msAPI_QAM_Check_Lock
//Description:      This function return QAM lock status
//  [doxygen]
/// This function return QAM lock status
///@param pstDemodeTPSetting \b IN pointer TP structe
///@return - return QAM Lock status
///         - TRUE : LOCK
///         - FALSE: UNLOCK
//*************************************************************************
EN_SCAN_RESULT msAPI_QAM_Check_Lock(MS_TP_SETTING_ATSC *pstDemodeTPSetting)
{
#if TS_FROM_PLAYCARD
    return LOCK;
#else

#if TS_THROUGH_LVDS
    return TRUE;
#else

    #if (FRONTEND_DEMOD_ATSC_TYPE == LG_3303_DEMODE)
        BOOLEAN SignalLock,TRL_LOCK;
        U8 i;
        //Check AGC First
        SignalLock=LgdtQAMCheckNoSignalFlag();

        if(SignalLock==LGDT_ERR_NO)     //AGC is Lock, check TRL
        {
            for(i=0;i<4;i++)
            {
                TRL_LOCK=LgdtQAMCheckDecoderTimingLock();
                if(TRL_LOCK==LGDT_ERR_NO)
                {
                    NEW_SCAN_API_DBG(printf("MApp_QAM_Scan 1st TRL Lock \r\n"););
                    break;
                }
                msAPI_Timer_Delayms(100);
            }
            if (TRL_LOCK!=LGDT_ERR_NO)  //TRL Unlock, change QAM mode
            {
                if(pstDemodeTPSetting->fModulation==DEMOD_ATSC_MODE_256QAM)
                    pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_64QAM;
                else if (pstDemodeTPSetting->fModulation==DEMOD_ATSC_MODE_64QAM)
                    pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_256QAM;
                else
                {
                    NEW_SCAN_API_DBG(printf("Error!!! MApp_QAM_Scan 2nd fModulation type Fail \r\n"););
                    return FALSE;
                }

                msAPI_Demodulator_Reset_ATSC();
                if(TRUE!=msAPI_Demodulator_Init(pstDemodeTPSetting->fModulation,pstDemodeTPSetting->fSpectrum))
                {
                    NEW_SCAN_API_DBG(printf("Error!!! 2nd MApp_QAM_Scan Demod init Fail \r\n"););
                }
                msAPI_Timer_Delayms(100);

                SignalLock=LgdtQAMCheckNoSignalFlag();
                if(SignalLock==LGDT_ERR_NO)
                {
                    for(i=0;i<4;i++)
                    {
                        TRL_LOCK=LgdtQAMCheckDecoderTimingLock();
                        if(TRL_LOCK==LGDT_ERR_NO)
                        {
                            NEW_SCAN_API_DBG(printf("MApp_QAM_Scan 2nd TRL Lock \r\n"););
                            break;
                        }
                        msAPI_Timer_Delayms(100);
                    }
                }
            }

        //Check Spectrum Inverse
        if(SignalLock==LGDT_ERR_NO)
        {
            if(TRL_LOCK==LGDT_ERR_NO)   //TRL Lock, Check FEC
            {
                NEW_SCAN_API_DBG(printf("MApp_QAM_Scan Demod 1st or 2nd TRL Lock \r\n"););
                if(LGDT_ERR_NO==LgdtQAMCheckDecoderSyncLock())
                {
                    //Read the Spectrum
                    LgdtGetSpectrum(&i);
                    pstDemodeTPSetting->fSpectrum=i;
                    NEW_SCAN_API_DBG(printf("MApp_QAM_Scan Demod FEC Lock \r\n"););
                    return TRUE;
                }
                else    //Switch the QAM Mode again
                {
                    NEW_SCAN_API_DBG(printf("MApp_QAM_Scan 3nd Switch QAM Mode Again \r\n"););
                    if(pstDemodeTPSetting->fModulation==DEMOD_ATSC_MODE_256QAM)
                        pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_64QAM;
                    else if (pstDemodeTPSetting->fModulation==DEMOD_ATSC_MODE_64QAM)
                        pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_256QAM;
                    else
                    {
                        NEW_SCAN_API_DBG(printf("Error2!!! MApp_QAM_Scan fModulation type Fail \r\n"););
                        return FALSE;
                    }

                    msAPI_Demodulator_Reset_ATSC();
                    if(TRUE!=msAPI_Demodulator_Init(pstDemodeTPSetting->fModulation,pstDemodeTPSetting->fSpectrum))
                    {
                        NEW_SCAN_API_DBG(printf("Error2!!! MApp_QAM_Scan Demod init Fail \r\n"););
                    }
                    msAPI_Timer_Delayms(100);
                    if(LGDT_ERR_NO==LgdtQAMCheckDecoderSyncLock())
                    {
                        //Read the Spectrum
                        LgdtGetSpectrum(&i);
                        pstDemodeTPSetting->fSpectrum=i;
                        NEW_SCAN_API_DBG(printf("MApp_QAM_Scan Demod 2nd FEC Lock \r\n"););
                        return TRUE;
                    }
                }
            }
            else    //AGC Lock, But TRL Unlock
            {
                NEW_SCAN_API_DBG(printf("MApp_QAM_Scan Demod 2nd TRL Unlock \r\n"););
            }
        }
        else    //AGC Unlock
        {
            NEW_SCAN_API_DBG(printf("MApp_QAM_Scan Demod 2nd AGC Unlock \r\n"););
        }
    }
    else
    {
        NEW_SCAN_API_DBG(printf("MApp_QAM_Scan 1st AGC Unlock \r\n"););
    }
        //LgdtRegPrint();
        return FALSE;

    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)

    // Check AGC First
    if(SamsungS5H1409xAGCCheckLock()!=TRUE)
    {
        return UNLOCK;
    }
    else
    {
        if (!msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME))
            return CHECKEND;
        if(SamsungS5H1409xQAMCheckLock()==TRUE)
        {
            return LOCK;
        }

        if(pstDemodeTPSetting->fModulation==DEMOD_ATSC_MODE_256QAM)
        {
            pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_64QAM;
            SamsungS5H1409x64QamMode();
        }
        else if (pstDemodeTPSetting->fModulation==DEMOD_ATSC_MODE_64QAM)
        {
            pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_256QAM;
            SamsungS5H1409x256QamMode();
        }
        else
        {
            NEW_SCAN_API_DBG(printf("Error2!!! MApp_QAM_Scan fModulation type Fail \r\n"););
            return UNLOCK;
        }

        if (!msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME))
            return CHECKEND;
        if(SamsungS5H1409xQAMCheckLock()==TRUE)
        {
            return LOCK;
        }
        else
        {
            return UNLOCK;
        }
    }
    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)

        EN_SCAN_RESULT RESULT;

        RESULT =MSB1501_QAMCheckLock();
        if(RESULT== LOCK)
        {
            if ( MSB1501_Check8VSB64_256QAM() == QAM256 )
                pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_256QAM;
            else
                pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_64QAM;

        }

        return RESULT;
    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)

        EN_SCAN_RESULT RESULT;
        #if (DEMOD_ATSC_USE_UTOPIA)
        DMD_ATSC_LOCK_STATUS eLockStatus = MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK);

        if(eLockStatus == DMD_ATSC_NULL)
        {
            eLockStatus = DMD_ATSC_UNLOCK;
            printf("[Error] Invalid demod lock status !!!\r\n");
        }
        RESULT = ((EN_SCAN_RESULT)eLockStatus);
        #else
        RESULT =INTERN_ATSC_QAMCheckLock();
        #endif

        if(RESULT== LOCK)
        {
            #if (DEMOD_ATSC_USE_UTOPIA)
            if ( MDrv_DMD_ATSC_GetModulationMode() == DMD_ATSC_DEMOD_ATSC_256QAM )
            #else
            if ( INTERN_ATSC_Check8VSB64_256QAM() == QAM256 )
            #endif
                pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_256QAM;
            else
                pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_64QAM;
        }

        return RESULT;
    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
#if 0
    // Check AGC First
    if(Sec_1410xAGCCheckLock()!=TRUE)
    {
        return FALSE;
    }
    else
#endif
    {
        if(Sec_1410xQAMCheckLock()==TRUE)
        {
            return TRUE;
        }

        if(pstDemodeTPSetting->fModulation==DEMOD_ATSC_MODE_256QAM)
        {
            pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_64QAM;
            Sec_1410x64QamMode();
        }
        else if (pstDemodeTPSetting->fModulation==DEMOD_ATSC_MODE_64QAM)
        {
            pstDemodeTPSetting->fModulation=DEMOD_ATSC_MODE_256QAM;
            Sec_1410x256QamMode();
        }
        else
        {
            NEW_SCAN_API_DBG(printf("Error2!!! MApp_QAM_Scan fModulation type Fail \r\n"););
            return FALSE;
        }

        if(Sec_1410xQAMCheckLock()==TRUE)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    #endif

#endif  //TS_THROUGH_LVDS
#endif // TS_FROM_PLAYCARD
}

//*************************************************************************
//Function name:    msAPI_NTSC_Check_Lock
//Description:      This function return NTSC lock status
//  [doxygen]
/// This function return NTSC lock status
///@param pstModifyTPSetting \b IN pointer TP structe
///@return - return NTSC Lock status
///         - TRUE : LOCK
///         - FALSE: UNLOCK
//*************************************************************************

BOOLEAN msAPI_NTSC_Check_Lock(MS_TP_SETTING_ATSC *pstModifyTPSetting)
{
    //DEBUG_API_TUNER_ATSC( printf("msAPI_NTSC_Check_Lock(Freq=%u, Mod=%u)\n", pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation); );

#if ( FRONTEND_TUNER_TYPE == ALPS_TDQU4_TUNER )

    if(TRUE==msAPI_AFT_Freq_Offset_Tune(pstModifyTPSetting))
        return TRUE;
    else
        return FALSE;

#elif ( FRONTEND_TUNER_TYPE == NXP_TD1136_TUNER)
    if (TRUE == msAPI_Tuner_NtscCheckLock(pstModifyTPSetting))
    {
       return TRUE;
    }
    else
    {
       return FALSE;
    }
#else

    if(TRUE == msAPI_NTSC_GetFreq_Offset(pstModifyTPSetting))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

#endif
}
/////////////
#if(FRONTEND_TUNER_TYPE == NXP_TD1136_TUNER)
BOOLEAN msAPI_Tuner_NtscCheckLock(MS_TP_SETTING_ATSC *pstModifyTPSetting)
{
   U8 status,count = 0,i;
   U16 u16VdLockStatus;
   U16 u16Temp_Frequency;
   #define JUMP_NUMBER 16
   #define FOUR_TIMES_SAMPLING_FREQ 4//250    //62.5*4
   const S8 code JUMP_TABLE[ JUMP_NUMBER ] =
   {
      -FOUR_TIMES_SAMPLING_FREQ, FOUR_TIMES_SAMPLING_FREQ,
      -FOUR_TIMES_SAMPLING_FREQ*2, FOUR_TIMES_SAMPLING_FREQ*2,
      -FOUR_TIMES_SAMPLING_FREQ*3, FOUR_TIMES_SAMPLING_FREQ*3,
      -FOUR_TIMES_SAMPLING_FREQ*4, FOUR_TIMES_SAMPLING_FREQ*4,
          -FOUR_TIMES_SAMPLING_FREQ*5, FOUR_TIMES_SAMPLING_FREQ*5,
          -FOUR_TIMES_SAMPLING_FREQ*6, FOUR_TIMES_SAMPLING_FREQ*6
          -FOUR_TIMES_SAMPLING_FREQ*7, FOUR_TIMES_SAMPLING_FREQ*7
          -FOUR_TIMES_SAMPLING_FREQ*8, FOUR_TIMES_SAMPLING_FREQ*8
   };
   extern BOOLEAN fScanTypeIsAuto;

   if (fScanTypeIsAuto)
   {
      return FALSE;
   }
   u16Temp_Frequency = pstModifyTPSetting->u16Frequency;

   //Frequency Acquisition
  for (i=0;i<JUMP_NUMBER;i++)
  {
       msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
       msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);

        if ((MDrv_AVD_GetStatus() & VD_HSYNC_LOCKED))
        {
            if(MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2)))
            {
          status = MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2));   // Use SAR2
          {
               if (ADC_TOP_UNSTABLE_POINT < status <ADC_BOTTOM_UNSTABLE_POINT)
            {
                AFT_CHECK_API_DBG(printf("Eneter AFT Win!!!!\n"););
                         break;
            }
          }
            }
            else
            {
                 AFT_CHECK_API_DBG(printf("AFT ERROR NTSC_ADC_ReadStatus Fail\n"););
             }
         }
         AFT_CHECK_API_DBG(printf("AFT VD Lock Fail Count=%bd\n",(U8)i););
         pstModifyTPSetting->u16Frequency += JUMP_TABLE[i];
    }


    if (i == JUMP_NUMBER)  //Can not find stable point
    {
        pstModifyTPSetting->u16Frequency = u16Temp_Frequency;
     AFT_CHECK_API_DBG(printf("AFT Can not find stable point\n"););
     return FALSE;
    }
    else
    {
         u16Temp_Frequency = pstModifyTPSetting->u16Frequency; //Backup Stable frequency
    }

    while(1)
    {
        status = MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2));   // Use SAR2
        AFT_CHECK_API_DBG(printf("AFT  freq=%ld\n  AFT ADC=%bd\n  AFT Voltage =%ld mv\n",(U32)((pstModifyTPSetting->u16Frequency)*FREQ_STEP),(U8)status,(U32)(51.56*status)););
        if((status > ADC_TOP_STABLE_POINT) && (status <= ADC_BOTTOM_STABLE_POINT))//MAX_AFT_VALUE) )
        {
               msAPI_Timer_Delayms(5);
         status = MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2));   // Use SAR2
                if ((status >= ADC_HIGH_STABLE_POINT) && (status <= ADC_BOTTOM_STABLE_POINT))//MAX_AFT_VALUE))
                {
                     u16VdLockStatus = MDrv_AVD_GetStatus();
                     if ((u16VdLockStatus & (VD_HSYNC_LOCKED|VD_SYNC_LOCKED|VD_FSC_TYPE|VD_PAL_SWITCH) ) == (VD_HSYNC_LOCKED|VD_SYNC_LOCKED | VD_FSC_3579))
                     {
                          AFT_CHECK_API_DBG(printf("AFT Get NTSC freq offset scope - ok!\n"));
                          return TRUE;
                      }
                      else
                      {
                          pstModifyTPSetting->u16Frequency = u16Temp_Frequency;
                          AFT_CHECK_API_DBG(printf("AFT Get NTSC freq offset scope - No Snyc!\n"));
                 return FALSE;
                      }
                }
        }

     if (status > ADC_BOTTOM_STABLE_POINT)
        {
             pstModifyTPSetting->u16Frequency += (MAX_ZIG_ZAG_NUM-count);
             AFT_CHECK_API_DBG(printf("AFT Volt > 2.9v\n"));
        }
        else if (status < ADC_HIGH_STABLE_POINT)
        {
            pstModifyTPSetting->u16Frequency -= (MAX_ZIG_ZAG_NUM-count);
             AFT_CHECK_API_DBG(printf("AFT Volt < 2.1v\n"));
        }
        msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
        msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);
        count++;
     if(count == MAX_AFT_CHECK_NUM)
        {
            pstModifyTPSetting->u16Frequency = u16Temp_Frequency;
         AFT_CHECK_API_DBG(printf("AFT No stable signal found at last!\n"));
            return FALSE;
         }

      }
}
#endif
//////////////

BOOLEAN NTSC_IF_ReadStatus(U8 * AFT_Status)
{
    U8 I2C_RESULT;

    msAPI_Tuner_PaThruI2C(ENABLE);

#if ((FRONTEND_TUNER_TYPE == THOMSON_DTT7630_TUNER)||(FRONTEND_TUNER_TYPE == PHILIPS_FQD1236_TUNER)||(FRONTEND_TUNER_TYPE == LG_TDVS_H703P_TUNER) || (FRONTEND_TUNER_TYPE == SHARP_VA1Y2UR2201_TUNER)\
      ||(FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER))
    I2C_RESULT = MDrv_IIC_ReadBytes(TDA9885_devAddr, 0, NULL, 1, AFT_Status);

    #if 0
    LG3303_DEBUG(printf("\nstatus = 0x%02bx\n", status));
    LG3303_DEBUG(printf("after power on : %bu\n", status&0x01 ));
    LG3303_DEBUG(printf("afc offset     : %bu\n", (status>>1)&0x0f ));
    LG3303_DEBUG(printf("fm det         : %bu\n", (status & 0x20)>>5 ));
    LG3303_DEBUG(printf("vif level      : %bu\n", (status & 0x40)>>6 ));
    LG3303_DEBUG(printf("afc window     : %bu\n", (status & 0x80)>>7 ));
    #endif

    msAPI_Tuner_PaThruI2C(DISABLE);

    if(TRUE==I2C_RESULT)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

#else
    *AFT_Status=*AFT_Status;
    I2C_RESULT = FALSE;

    msAPI_Tuner_PaThruI2C(DISABLE);

    return FALSE;

#endif

}//IF_ReadStatus

//*************************************************************************
//Function name:    msAPI_NTSC_GetFreq_Offset
//Description:      This function return NTSC in offset
//  [doxygen]
/// This function return NTSC in offset
///@param pstModifyTPSetting \b IN pointer TP structe
///@return - return NTSC in offset
///         - TRUE : LOCK
///         - FALSE: UNLOCK
//*************************************************************************

BOOLEAN msAPI_NTSC_GetFreq_Offset(MS_TP_SETTING_ATSC *pstModifyTPSetting)
{
#if TS_THROUGH_LVDS
    return FALSE;
#else   // TS_THROUGH_LVDS;
#if ((FRONTEND_TUNER_TYPE == THOMSON_DTT7630_TUNER)||(FRONTEND_TUNER_TYPE == PHILIPS_FQD1236_TUNER)||(FRONTEND_TUNER_TYPE == LG_TDVS_H703P_TUNER) || (FRONTEND_TUNER_TYPE == MSTAR_MSR1200))
        U8 AFT,u8LoopCount=0,u8patch=0,u8patch2=0,I2C_RESULT;
        U16 u16default_offset_KHz=1600/FREQ_STEP;
        U16 u16Temp_Frequency;

        u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
        #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
        SamsungS5H1409xRepeaterEnable();
        #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
        MSB1501_RepeaterEnable();
        #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
        #if (DEMOD_ATSC_USE_UTOPIA)
        //Unused
        #else
        INTERN_ATSC_RepeaterEnable();
        #endif
        #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
        Sec_1410xRepeaterEnable();
        #endif
        while(I2C_RESULT=NTSC_IF_ReadStatus(&AFT))
        {
            if((AFT & 0x80)>>7)     //Check in AFT Win or not
            {
                AFT=((AFT>>1)&0x0f);
                //Step 1: check the freq offset
                u8LoopCount++;
                NEW_SCAN_API_DBG(printf("Enter retry loop count=%bd, initial feq=%lu\n",(U8)u8LoopCount,(U32)(pstModifyTPSetting->u16Frequency)*FREQ_STEP););
                if((AFT<Offset_N_87500Hz)||(AFT>Offset_P_87500Hz))   //Within +/- 62.5KHz
                {
                    NEW_SCAN_API_DBG(printf("Within +/- 62.5KHz, AFT=%bd, freq=%lu\n",(U8)AFT,(U32)(pstModifyTPSetting->u16Frequency)*FREQ_STEP););
                    break;
                }
                else if((AFT>Offset_P_187500Hz)||(AFT<Offset_N_187500Hz))       //Within +/- 187.5KHz
                {
                    switch (AFT)
                    {
                        case Offset_N_87500Hz:
                                (pstModifyTPSetting->u16Frequency)+=(U16)(87/FREQ_STEP);
                            break;
                        case Offset_N_122500Hz:
                                (pstModifyTPSetting->u16Frequency)+=(U16)(122/FREQ_STEP);
                            break;
                        case Offset_N_137500Hz:
                                (pstModifyTPSetting->u16Frequency)+=(U16)(137/FREQ_STEP);
                            break;
                        case Offset_N_162500Hz:
                                (pstModifyTPSetting->u16Frequency)+=(U16)(162/FREQ_STEP);
                            break;
                        case Offset_P_87500Hz:
                                (pstModifyTPSetting->u16Frequency)-=(U16)(87/FREQ_STEP);
                            break;
                        case Offset_P_122500Hz:
                                (pstModifyTPSetting->u16Frequency)-=(U16)(122/FREQ_STEP);
                            break;
                        case Offset_P_137500Hz:
                                (pstModifyTPSetting->u16Frequency)-=(U16)(137/FREQ_STEP);
                            break;
                        case Offset_P_162500Hz:
                                (pstModifyTPSetting->u16Frequency)-=(U16)(162/FREQ_STEP);
                            break;
                        default:
                            break;
                    }
                        NEW_SCAN_API_DBG(printf("Within +/- 187.5KHz, AFT=%bd, freq=%lu\n",(U8)AFT,(U32)(pstModifyTPSetting->u16Frequency)*FREQ_STEP););
                }
                else   //Out of  +/- 187.5KHz
                {
                    if(AFT==Offset_N_187500Hz)
                            (pstModifyTPSetting->u16Frequency)+=(U16)(u16default_offset_KHz>>u8LoopCount);
                    else
                            (pstModifyTPSetting->u16Frequency)-=(U16)(u16default_offset_KHz>>u8LoopCount);

                        NEW_SCAN_API_DBG(printf("Out of  +/- 187.5KHz, AFT=%bd, freq=%lu\n",(U8)AFT,(U32)(pstModifyTPSetting->u16Frequency)*FREQ_STEP););
                }
                // Step 2: Check is dead lock or not
                if((u8LoopCount>7)||((u8LoopCount==5)&&(u8patch2==5)))  //force leave the dead lock case
                {
                    if(u8patch==0)
                    {
                        u8patch=1;
                        u8patch2=0;
                        u8LoopCount=0;
                        (pstModifyTPSetting->u16Frequency)-=(u16default_offset_KHz<<1);
                        NEW_SCAN_API_DBG(printf("error! patch for LG IF demode\n"););
                    }
                    else
                    {
                        pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                        msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
                        NEW_SCAN_API_DBG(printf("Warrning! leave the fake lock state, check by VD again\n"););
                        break;
                    }
                }
                // Step 3: Set the new freq
                msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
                // Step 4: Waiting for tuner lock
                msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);
            }
            else
            {
                pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                NEW_SCAN_API_DBG(printf("error! VD Lock but Outside of AFT Win !\r\n"););
                if((u8patch==1)&&(u8LoopCount==0))  //patch for tuner bug
                {
                    pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                    msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
                    NEW_SCAN_API_DBG(printf("Warrning! leave the tuner patch state, check by VD again\n"););
                    #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
                    SamsungS5H1409xRepeaterDisable();
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
                    MSB1501_RepeaterDisable();
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
                    #if (DEMOD_ATSC_USE_UTOPIA)
                    //Unused
                    #else
                    INTERN_ATSC_RepeaterDisable();
                    #endif
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
                    Sec_1410xRepeaterDisable();
                    #endif
                    return FALSE;
                }
                else
                {
                    pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                    #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
                    SamsungS5H1409xRepeaterDisable();
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
                    MSB1501_RepeaterDisable();
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
                    #if (DEMOD_ATSC_USE_UTOPIA)
                    //Unused
                    #else
                    INTERN_ATSC_RepeaterDisable();
                    #endif
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
                    Sec_1410xRepeaterDisable();
                    #endif
                    return FALSE;
                }
            }
            #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
            SamsungS5H1409xRepeaterEnable();
            #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
            MSB1501_RepeaterEnable();
            #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
            #if (DEMOD_ATSC_USE_UTOPIA)
            //Unused
            #else
            INTERN_ATSC_RepeaterEnable();
            #endif
            #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
            Sec_1410xRepeaterEnable();
            #endif
        }
        NEW_SCAN_API_DBG(printf("!!!!!!!!OK!!!!! Final Freq Offset=%ld\n",(U32)(pstModifyTPSetting->u16Frequency)*FREQ_STEP););
        #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
        SamsungS5H1409xRepeaterDisable();
        #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
        MSB1501_RepeaterDisable();
        #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
        #if (DEMOD_ATSC_USE_UTOPIA)
        //Unused
        #else
        INTERN_ATSC_RepeaterDisable();
        #endif
        #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
        Sec_1410xRepeaterDisable();
        #endif
        return I2C_RESULT;

#elif (FRONTEND_TUNER_TYPE == SHARP_VA1Y2UR2201_TUNER)

        U8 I2C_VALUE,ACQ_AFT,TRACK_AFT,i;
        U16 u16Temp_Frequency;
        BOOLEAN VD_RESULT;

        u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
        //Frequency Acquisition
        for (i=0;i<JUMP_NUMBER;i++)
        {
            if((MDrv_AVD_GetStatus() & VD_HSYNC_LOCKED)>0)
            {
                #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
                    SamsungS5H1409xRepeaterEnable();
                #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
                    MSB1501_RepeaterEnable();
                #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
                    #if (DEMOD_ATSC_USE_UTOPIA)
                    //Unused
                    #else
                    INTERN_ATSC_RepeaterEnable();
                    #endif
                #endif
                if(NTSC_IF_ReadStatus(&I2C_VALUE))
                {
                    #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
                    SamsungS5H1409xRepeaterDisable();
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
                    MSB1501_RepeaterDisable();
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
                    #if (DEMOD_ATSC_USE_UTOPIA)
                    //Unused
                    #else
                    INTERN_ATSC_RepeaterDisable();
                    #endif
                    #endif
                    if((ACQ_AFT=(I2C_VALUE&0x07))<UNSTABLE_POINT)
                        break;
                }
                else
                {
                    #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
                        SamsungS5H1409xRepeaterDisable();
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
                        MSB1501_RepeaterDisable();
                    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
                        #if (DEMOD_ATSC_USE_UTOPIA)
                        //Unused
                        #else
                        INTERN_ATSC_RepeaterDisable();
                        #endif
                    #endif
                    NEW_SCAN_API_DBG(printf("ERROR NTSC_IF_ReadStatus Fail\n"););
                }
            }
            NEW_SCAN_API_DBG(printf("VD Lock Fail Count=%bd\n",(U8)i););
            pstModifyTPSetting->u16Frequency+=JUMP_TABLE[i];
            msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
            msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);
        }


        if(i==JUMP_NUMBER)  //Can not find stable point
            pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
        else
            u16Temp_Frequency=pstModifyTPSetting->u16Frequency; //Backup Stable frequency

        //Frequency Tracking
        switch (ACQ_AFT)
        {
            case HIGH_STABLE_POINT:
                for(i=1;i<=4;i++)
                {
                    (pstModifyTPSetting->u16Frequency)-=1;//FREQ_STEP;
                    if(msAPI_CHECK_AFT_FUNCTION(pstModifyTPSetting->u16Frequency,pstModifyTPSetting->fModulation,&TRACK_AFT,&VD_RESULT))
                    {
                        if(VD_RESULT==TRUE)
                        {
                            if(TRACK_AFT==MATCH_STABLE_POINT)
                            {
                                u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
                                NEW_SCAN_API_DBG(printf("HIGH_STABLE_POINT Track Success i=%bd\n",(U8)i););
                                break;
                            }
                            else
                                NEW_SCAN_API_DBG(printf("HIGH_STABLE_POINT Track Fail i=%bd\n",(U8)i););
                        }
                        else
                        {
                            NEW_SCAN_API_DBG(printf("HIGH_STABLE_POINT Track VD unlock i=%bd\n",(U8)i););
                            break;
                        }
                    }
                }
                pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                NEW_SCAN_API_DBG(printf("End of HIGH_STABLE_POINT\n"););
                break;
            case MATCH_STABLE_POINT:
                NEW_SCAN_API_DBG(printf("End of MATCH_STABLE_POINT\n"););
                break;
            case LOW_STABLE_POINT:
            case BOTTOM_STABLE_POINT:
                for(i=1;i<=14;i++)
                {
                    (pstModifyTPSetting->u16Frequency)+=1;//FREQ_STEP;
                    if(msAPI_CHECK_AFT_FUNCTION(pstModifyTPSetting->u16Frequency,pstModifyTPSetting->fModulation,&TRACK_AFT,&VD_RESULT))
                    {
                        if(VD_RESULT==TRUE)
                        {
                            if(TRACK_AFT==MATCH_STABLE_POINT)
                            {
                                u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
                                NEW_SCAN_API_DBG(printf("LOW_STABLE_POINT Track Success i=%bd\n",(U8)i););
                                break;
                            }
                            else
                                NEW_SCAN_API_DBG(printf("LOW_STABLE_POINT Track Fail i=%bd\n",(U8)i););
                        }
                        else
                        {
                            NEW_SCAN_API_DBG(printf("LOW_STABLE_POINT Track VD unlock i=%bd\n",(U8)i););
                            break;
                        }
                    }
                }
                pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                NEW_SCAN_API_DBG(printf("End of LOW_STABLE_POINT\n"););
                break;
            case UNSTABLE_POINT:
                for(i=0;i<6;i++)
                {
                    if(msAPI_CHECK_AFT_FUNCTION(pstModifyTPSetting->u16Frequency+TRACK_TABLE[i],pstModifyTPSetting->fModulation,&TRACK_AFT,&VD_RESULT))
                    {
                        if(VD_RESULT==TRUE)
                        {
                            if(TRACK_AFT==MATCH_STABLE_POINT)
                            {
                                u16Temp_Frequency=pstModifyTPSetting->u16Frequency+TRACK_TABLE[i];
                                NEW_SCAN_API_DBG(printf("UNSTABLE_POINT Track Success i=%bd\n",(U8)i););
                                break;
                            }
                            else if(TRACK_AFT==HIGH_STABLE_POINT)
                            {
                                u16Temp_Frequency=pstModifyTPSetting->u16Frequency+TRACK_TABLE[i];
                                NEW_SCAN_API_DBG(printf("UNSTABLE_POINT Track to HIGH_STABLE_POINT i=%bd\n",(U8)i););
                            }
                            else
                                NEW_SCAN_API_DBG(printf("UNSTABLE_POINT Track Fail i=%bd\n",(U8)i););
                        }
                    }
                }
                pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                NEW_SCAN_API_DBG(printf("End of UNSTABLE_POINT\n"););
                break;
        }
        return TRUE;

#elif ((FRONTEND_TUNER_TYPE == SAMSUNG_EH201A_TUNER) || \
       (FRONTEND_TUNER_TYPE == SAMSUNG_S205_TUNER) || \
       (FRONTEND_TUNER_TYPE == SAMSUNG_S203FH201B_TUNER) || \
       (FRONTEND_TUNER_TYPE == ALPS_TDQU6_TUNER) || \
       (FRONTEND_TUNER_TYPE == SAMSUNG_DVTA50_TUNER) || \
       (FRONTEND_TUNER_TYPE == XUGUANG_DVT_8ADC1_W41F2) || \
       (FRONTEND_TUNER_TYPE == SAMSUNG_DTVS20CVL081A_TUNER) || \
       (FRONTEND_TUNER_TYPE == NXP_TDA18273_TUNER) || \
       (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER) || \
       (FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER) || \
       (FRONTEND_TUNER_TYPE == NXP_TDA18275A_TUNER) || \
       (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER) || \
       (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER) || \
       (FRONTEND_TUNER_TYPE == SILAB_2190B_TUNER) || \
       (FRONTEND_TUNER_TYPE == SILAB_2151_TUNER) || \
       (FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER) || \
       (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER) || \
       (FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER) || \
       (FRONTEND_TUNER_TYPE == RDA5158_TUNER) || \
       (FRONTEND_TUNER_TYPE == TCL_DA91WT_13_E_TUNER))
#if ( GET_FREQ_OFFSET_NEW ==0)
        U8  status,count=0;
        U16 u16Temp_Frequency;

        u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
        while(1)
        {
            msAPI_Tuner_Wait(VIF_STABLE_TIME);
            #if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)
            {
                U32 u32StartTime=msAPI_Timer_GetTime0();

                while (msAPI_Timer_GetTime0()-u32StartTime < VIF_STABLE_TIME)
                {
                    MDrv_VIF_Handler(FALSE);
                    if (MDrv_VIF_Read_CR_LOCK_STATUS())
                    {
                        break;
                    }
                }
            }
            status = (~(MDrv_VIF_Read_CR_FOE()))*4;
            if ((status>=31) && (status<=127))
                status=31;
            if ((status>=128) && (status<=225))
                status=225;

            status+=32;
            //printf("AFT0 %d %d\r\n",MDrv_VIF_Read_CR_LOCK_STATUS(),status);
            #else
            status = GetSarAdcLevel(KEYPAD_ADC_CHANNEL_3); //Use SAR2
            #endif

                NEW_SCAN_API_DBG(printf("freq=%ld, ADC=%bd, Voltage=%ld mv\n",(U32)((pstModifyTPSetting->u16Frequency)*FREQ_STEP),(U8)status,(U32)(104.76*status)););
                if((status >= MIN_AFT_VALUE)&& (status <= MAX_AFT_VALUE) )
                {
                    msAPI_Tuner_Wait(VIF_STABLE_TIME);
                    #if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF) // BY 20090715
                    {
                        U32 u32StartTime=msAPI_Timer_GetTime0();

                        while (msAPI_Timer_GetTime0()-u32StartTime < VIF_STABLE_TIME)
                        {
                            MDrv_VIF_Handler(FALSE);
                            if (MDrv_VIF_Read_CR_LOCK_STATUS())
                            {
                                break;
                            }
                        }
                    }
                    status = (~(MDrv_VIF_Read_CR_FOE()))*4;
                    U8  u8StatusTemp = MDrv_VIF_Read_CR_FOE();
                    if ((status>=31) && (status<=127))
                        status=31;
                    if ((status>=128) && (status<=225))
                        status=225;

                    status+=32;
                    //printf("AFT1 %d %d\r\n",MDrv_VIF_Read_CR_LOCK_STATUS(),status);
                    #else
                    status = GetSarAdcLevel(KEYPAD_ADC_CHANNEL_3); // Use SAR2
                    #endif
                    if((status >= MIN_AFT_VALUE)&&(status <= MAX_AFT_VALUE))
                    {
                    	if(u8StatusTemp>0x7f)
						{
							if((255-u8StatusTemp)>=32)//offset >500k
							{
								NEW_SCAN_API_DBG(printf("\n-bill-Get NTSC freq offset scope - out>0x7F\n"));
								return FALSE;
							}
						}
						else
						{
						    if(u8StatusTemp>=32)//offset >500k
							{
						       	NEW_SCAN_API_DBG(printf("\n-bill-Get NTSC freq offset scope - out=<0x7F\n"));
						       	return FALSE;
							}
						}
                        NEW_SCAN_API_DBG(printf("Get NTSC freq offset scope - out\n"));
                        return TRUE;
                    }
                }
                if(count==MAX_ZIG_ZAG_NUM)
                {
                    pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                    return FALSE;
                }

            if(status>MAX_AFT_VALUE)
                pstModifyTPSetting->u16Frequency+=(MAX_ZIG_ZAG_NUM-count);
            else
                pstModifyTPSetting->u16Frequency-=(MAX_ZIG_ZAG_NUM-count);
            msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstModifyTPSetting->fModulation);
            if (!msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME))
                return FALSE;
            count++;
      }
#else
	 U8 u8VifFOE=0;
	 U8 count=0;
        U8 u8VifMaxFOE=0;
        U16 u16Temp_Frequency;

        u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
        u8VifMaxFOE = (500/FREQ_STEP)*4; // 4 FOE step = 1 tuner step

        while(1)
        {
            msAPI_Tuner_Wait(VIF_STABLE_TIME);
            #if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)
            {
                U32 u32StartTime=msAPI_Timer_GetTime0();

                while (msAPI_Timer_GetTime0()-u32StartTime < VIF_STABLE_TIME)
                {
                    MDrv_VIF_Handler(FALSE);
                    if (MDrv_VIF_Read_CR_LOCK_STATUS())
                    {
                        break;
                    }
                }
            }
        	#endif
            u8VifFOE = DRV_VIF_Read_CR_FOE();
           // printf("FOE0:%bx \r\n",DRV_VIF_Read_CR_FOE());
			if((BIT7&u8VifFOE) == BIT7)	//negtive
			{
				U8 u8VifFOETemp;
                u8VifFOETemp=((0xFF-u8VifFOE)+1);
				if(u8VifFOETemp < 0x08)
	            {
	                if (MDrv_VIF_Read_CR_LOCK_STATUS())
	               {
	                //printf("\n>negtive Get AFT 0\r\n");
	                    return TRUE;
	                }
                       else
                      {
	                    return FALSE;
                      }
	            }
                else if(u8VifFOETemp < 0x80)
	            {
	                if(u8VifFOETemp < u8VifMaxFOE)// under 500k (VIF only can detect 500k)
	                {
	                	//printf("\n>negtive Get AFT 1\r\n");
	                    pstModifyTPSetting->u16Frequency += u8VifFOETemp/4;
	                }
	                else
	                {
	                	//printf("\n>negtive Get AFT 2\r\n");
	                    pstModifyTPSetting->u16Frequency += u8VifMaxFOE/4;//500k
	                }
	            }

			}
            else//positive
            {
		     if(u8VifFOE < 0x08)
		    {
	                if (MDrv_VIF_Read_CR_LOCK_STATUS())
	               {
	                //printf("\n>negtive Get AFT 0\r\n");
	                    return TRUE;
	                }
                       else
                      {
	                    return FALSE;
                      }
	            }
                  else if(u8VifFOE < 0x80) //positive
	            {
	                if(u8VifFOE < u8VifMaxFOE)// under 500k (VIF only can detect 500k)
	                {
	                	//printf("\n>positive Get AFT 1\r\n");
	                    pstModifyTPSetting->u16Frequency -= u8VifFOE/4;
	                }
	                else
	                {
	                	//printf("\n>positive Get AFT 2\r\n");
	                    pstModifyTPSetting->u16Frequency -= u8VifMaxFOE/4;//500k
	                }

	            }
            }

            msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstModifyTPSetting->fModulation);

            if(count > 3)
            {
                pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                return FALSE;
            }

            if (!msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME))
                return FALSE;
            count++;
        }

#endif
#elif(FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
        U8 status,count=0;
        U16 u16Temp_Frequency;

        u16Temp_Frequency=pstModifyTPSetting->u16Frequency;

        while(1)
        {
            msAPI_Timer_Delayms(10);
            //status = MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2));   // Use SAR2
            //printf("\r\n1111111111@@@@@@\r\n");
            if (NTSC_IF_ReadStatus(&status))//if(msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&status) == 0 )
            {
               status &= 0x07;
                NEW_SCAN_API_DBG(printf("freq=%ld, ADC=%bx, Voltage=%ld mv\n",(U32)((pstModifyTPSetting->u16Frequency)*FREQ_STEP),(U8)status,(U32)(104.76*status)););
                if((status >= MIN_AFT_VALUE) && (status <= MAX_AFT_VALUE) )
                {
                    msAPI_Timer_Delayms(10);
                    //status = MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2));   // Use SAR2
                    if (NTSC_IF_ReadStatus(&status))
                    {
                        status &= 0x07;
                        //if(msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&status) == 0 )
                        if((status >= MIN_AFT_VALUE)&&(status <= MAX_AFT_VALUE))
                        {
                            NEW_SCAN_API_DBG(printf("Get NTSC freq offset scope - OK!\n"));
                            return TRUE;
                        }
                    }
                }
                if(count == MAX_ZIG_ZAG_NUM)
                {
                    pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
              NEW_SCAN_API_DBG(printf("Get NTSC freq offset scope - Fail!\n"));
                    return FALSE;
                }
            }
            if(status>MAX_AFT_VALUE)
                pstModifyTPSetting->u16Frequency+=(MAX_ZIG_ZAG_NUM-count);
            else
                pstModifyTPSetting->u16Frequency-=(MAX_ZIG_ZAG_NUM-count);
            msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
            msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);
            count++;
    }

#elif(FRONTEND_TUNER_TYPE == NXP_TD1136_TUNER)
        U8 status,count=0;
        U16 u16Temp_Frequency;

        u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
        while(1)
        {
            ///extern BOOLEAN fScanTypeIsAuto;
            extern BOOLEAN MApp_Scan_ATSC_GetVDLockStatus();

         msAPI_Timer_Delayms(10);
            //status = MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2));   // Use SAR2
            //if (MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2)))//(msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&status) == 0 )
            {
                status = MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2));   // Use SAR2
                NEW_SCAN_API_DBG(printf("freq=%ld, ADC=%bd, Voltage=%ld mv\n",(U32)((pstModifyTPSetting->u16Frequency)*FREQ_STEP),(U8)status,(U32)(104.76*status)););
                if((status >= MIN_AFT_VALUE)&& (status <= MAX_AFT_VALUE) )
                {
                    msAPI_Timer_Delayms(10);
                    status = MDrv_PM_RegRead(0x1418 + (AFT_USE_SAR * 2));   // Use SAR2
                   //if(msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&status) == 0 )
                        if((status >= MIN_AFT_VALUE)&&(status <= MAX_AFT_VALUE))
                        {
                            //if(!fScanTypeIsAuto)
                                //return TRUE;

                            if(MApp_Scan_ATSC_GetVDLockStatus())
                            {
                                NEW_SCAN_API_DBG(printf("Get NTSC freq offset scope - out\n"));
                                return TRUE;
                            }
                            else
                                NEW_SCAN_API_DBG(printf("Get NTSC freq offset scope - No Snyc\n"));
                        }
                }
                if(count == MAX_ZIG_ZAG_NUM)
                {
                    pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                    return FALSE;
                }
            }
            if(status>MAX_AFT_VALUE)
                pstModifyTPSetting->u16Frequency+=(MAX_ZIG_ZAG_NUM-count);
            else
                pstModifyTPSetting->u16Frequency-=(MAX_ZIG_ZAG_NUM-count);
            msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
            msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);
            count++;
      }


#elif (FRONTEND_TUNER_TYPE == NXP_TD1636ALMK2_TUNER)
        U8 status,count=0;
        U16 u16Temp_Frequency;

        u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
        while(1)
        {
            msAPI_Timer_Delayms(10);
            if(msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&status) == 0 )
            {
                NEW_SCAN_API_DBG(printf("freq=%ld, ADC=%bd, Voltage=%ld mv\n",(U32)(pstModifyTPSetting->u16Frequency)*FREQ_STEP,(U8)status,(U32)(104.76*status)););
                if((status >= MIN_AFT_VALUE)&& (status <= MAX_AFT_VALUE) )
                {
                    msAPI_Timer_Delayms(10);
                    if(msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&status) == 0 )
                        if((status >= MIN_AFT_VALUE)&&(status <= MAX_AFT_VALUE))
                        {
                            return TRUE;
                        }
                }
                if(count==MAX_ZIG_ZAG_NUM)
                {
                    pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
                    return FALSE;
                }
            }
            if(status>MAX_AFT_VALUE)
                pstModifyTPSetting->u16Frequency+=(MAX_ZIG_ZAG_NUM-count);
            else
                pstModifyTPSetting->u16Frequency-=(MAX_ZIG_ZAG_NUM-count);
            msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, pstModifyTPSetting->fModulation);
            msAPI_Timer_Delayms(10);
            count++;
        }
#elif ( FRONTEND_TUNER_TYPE == ALPS_TDQU4_TUNER )

        // Check is in AFT Win or not
        if(TRUE==msAPI_In_AFT_Win_Check(pstModifyTPSetting))
        {
            if (TRUE==msAPI_AFT_Freq_Offset_Tune(pstModifyTPSetting))
                return TRUE;
        }
        return FALSE;

#endif

#endif  //TS_THROUGH_LVDS
}//IF_ReadStatus

#if (FRONTEND_TUNER_TYPE == ALPS_TDQU4_TUNER)
//*************************************************************************
//Function name:    msAPI_In_AFT_Win_Check
//Description:      This function return NTSC's ATF
//  [doxygen]
/// This function return NTSC's ATF
///@param pstModifyTPSetting \b IN pointer TP structe
///@return - return NTSC in offset
///         - TRUE : LOCK
///         - FALSE: UNLOCK
//*************************************************************************

BOOLEAN msAPI_In_AFT_Win_Check(MS_TP_SETTING_ATSC *pstModifyTPSetting)
{
    U8 count=0,count2=0,AFT;
    U16 u16Temp_Frequency;

    u16Temp_Frequency=pstModifyTPSetting->u16Frequency;
    // Check is in AFT Win or not
    for(count=0;count<=RANGE_OF_AFT_COUNT;count++)
    {
        MsOS_DelayTask(AFT_WAIT_TIME);
        msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&AFT);
        if(AFT<AFT_SIGNAL_EXIST_THR)
        {
            for(count2=1;count2<=RANGE_OF_AFT_COUNT2;count2++)
            {
                if(AFT<=AFT_LARGE_FREQ_OFFSET)
                {
                    msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, DEMOD_ATSC_MODE_NTSC);
                    MsOS_DelayTask(AFT_WAIT_TIME);
                    return TRUE;
                }
                else
                {
                    msAPI_Tuner_SetFreq(((pstModifyTPSetting->u16Frequency)+SMALL_FREQ_OFFSET_CHECK*count2), DEMOD_ATSC_MODE_NTSC);
                    MsOS_DelayTask(AFT_WAIT_TIME);
                    msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&AFT);
               }
            }
        }
        if(count==0)
            pstModifyTPSetting->u16Frequency-=(LEFT_OF_AFT_WIN);
        else
            pstModifyTPSetting->u16Frequency+=(LARGE_FREQ_OFFSET_CHECK);

        msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, DEMOD_ATSC_MODE_NTSC);
    }
    pstModifyTPSetting->u16Frequency=u16Temp_Frequency;
    return FALSE;
}

//*************************************************************************
//Function name:    msAPI_AFT_Freq_Offset_Tune
//Description:      This function return NTSC's ATF
//  [doxygen]
/// This function return NTSC's ATF
///@param pstModifyTPSetting \b IN pointer TP structe
///@return - return NTSC in offset
///         - TRUE : LOCK
///         - FALSE: UNLOCK
//*************************************************************************

BOOLEAN msAPI_AFT_Freq_Offset_Tune(MS_TP_SETTING_ATSC *pstModifyTPSetting)
{
    U8 count=0,AFT;
    //Get the exactly frequency offset
    while(msKeypad_Get_ADC_Channel(KEYPAD_ADC_CHANNEL_3,&AFT) == 0 )
    {
        count++;
        if(count>AFT_FORCE_LEAVE_DEADLOCK)
            return TRUE;

        if((AFT<=AFT_HB_NO_FREQ_OFFSET)&&(AFT>=AFT_LB_NO_FREQ_OFFSET))  //Get the Exact freq!
            return TRUE;
        else if(AFT<=AFT_LARGE_FREQ_OFFSET)   //Jump 4 tab
            pstModifyTPSetting->u16Frequency-=(U32)MEDIUM_FREQ_OFFSET_CHECK;
        else if(AFT>AFT_HB_NO_FREQ_OFFSET)
            pstModifyTPSetting->u16Frequency+=1;//(U32)FREQ_STEP;
        else
            pstModifyTPSetting->u16Frequency-=1;//(U32)FREQ_STEP;

        msAPI_Tuner_SetFreq(pstModifyTPSetting->u16Frequency, DEMOD_ATSC_MODE_NTSC);
        MsOS_DelayTask(AFT_WAIT_TIME);
    }
    return FALSE;
}
#endif

#if (FRONTEND_TUNER_TYPE == SHARP_VA1Y2UR2201_TUNER)
BOOLEAN msAPI_CHECK_AFT_FUNCTION(U16 Frequency, U8 Modulation,U8 *AFT_Result, BOOLEAN *VD_Result)
{
#if TS_THROUGH_LVDS
    return FALSE;
#else
    U8 Status;
    NEW_SCAN_API_DBG(printf("CHECK_AFT_FUNCTION Fre=%ld\n",(U32)Frequency*FREQ_STEP););
    msAPI_Tuner_SetFreq(Frequency, Modulation);
    msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);
    *VD_Result= ((BIT)(MDrv_AVD_GetStatus() & VD_HSYNC_LOCKED));
    #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
    SamsungS5H1409xRepeaterEnable();
    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
    MSB1501_RepeaterEnable();
    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
    #if (DEMOD_ATSC_USE_UTOPIA)
    //Unused
    #else
    INTERN_ATSC_RepeaterEnable();
    #endif
    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
    Sec_1410xRepeaterEnable();
    #endif
    if(NTSC_IF_ReadStatus(&Status))
    {
        *AFT_Result=Status&0x07;
        NEW_SCAN_API_DBG(printf("msAPI_CHECK_AFT_FUNCTION AFT=%bd\n",(*AFT_Result)););
        Status=TRUE;
    }
    else
    {
        NEW_SCAN_API_DBG(printf("ERROR msAPI_CHECK_AFT_FUNCTION Fail\n"););
        Status=FALSE;
    }
    #if (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1409_DEMODE)
    SamsungS5H1409xRepeaterDisable();
    #elif (FRONTEND_DEMOD_ATSC_TYPE == MSTAR_MSB1501_DEMODE)
    MSB1501_RepeaterDisable();
    #elif (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
    #if (DEMOD_ATSC_USE_UTOPIA)
    //Unused
    #else
    INTERN_ATSC_RepeaterDisable();
    #endif
    #elif (FRONTEND_DEMOD_ATSC_TYPE == SAMSUNG_S5H1410_DEMODE)
    Sec_1410xRepeaterDisable();
    #endif

    return Status;
#endif  //TS_THROUGH_LVDS
}
#endif

#if (CHANNEL_SCAN_AUTO_TEST)
/******************************************************************************/
/// API for Set Spectrum type::
/// @param enSpectrum \b IN spectrum type of TS
/******************************************************************************/
void msAPI_Tuner_SetSpectrum(EN_DEMOD_ATSC_SPECTRUM_MODE enSpectrum)
{
    #if TS_THROUGH_LVDS
    stCurrentTPSetting.fSpectrum = enSpectrum;
    return;
    #endif

    #if (FRONTEND_DEMOD_ATSC_TYPE==LG_3303_DEMODE)
        switch(enSpectrum)
        {
            case DEMOD_ATSC_SPECTRUM_NORMAL:
                LgdtAlterSpectrum(LGDT_NOT_INVERTED);
                break;
            case DEMOD_ATSC_SPECTRUM_INVERTER:
                LgdtAlterSpectrum(LGDT_INVERTED);
                break;
        }
    #endif

    stCurrentTPSetting.fSpectrum = enSpectrum;
}
#endif

#if ENABLE_TEST_TUNER
//extern unsigned char kbhit(void);
#define TUNER_TESTAPI_DBG(x) x
void msAPI_Tuner_TestFunction(void)
{
    MS_TP_SETTING_ATSC stTPSetting;
    U8 i = 0;//, j, au8Data[16];

    //while(1)
    {

        msAPI_Tuner_Initialization_ATSC(1);

        TUNER_TESTAPI_DBG(printf("\nenter Frequency (Khz) >> "));
        stTPSetting.u16Frequency = 891;
        //scanf("%lu", &stTPSetting.u16Frequency);

        TUNER_TESTAPI_DBG(printf("\nenter Modulation Type (0=NTSC, 1=QAM256, 2=QAM64, 3=8VSB) >> "));
        //scanf("%bu", &i);
        stTPSetting.fModulation = 0;
        TUNER_TESTAPI_DBG(printf("\nF = %lu Mod Type = %bu", stTPSetting.u16Frequency, (U8)stTPSetting.fModulation));

        //select spertrum for QAM mode only
        if(stTPSetting.fModulation==1 || stTPSetting.fModulation==2)
        {
            TUNER_TESTAPI_DBG(printf("\nenter Spectrum Type (0=Invert, 1=Normal) >> "));
            //scanf("%bu", &i);
            stTPSetting.fSpectrum = i&0x3;
            TUNER_TESTAPI_DBG(printf("\nSpectrum Type = %bu", (U8)stTPSetting.fModulation));
        }

        msAPI_Tuner_Tune2RfCh_ATSC(&stTPSetting);

        MsOS_DelayTask(2000);
        printf("into while\n");
        /*
        while(1)
        {
            printf("\r\n");
            printf("\nSelect Options:");
            printf("\n0 = quit");
            printf("\n1 = check FE status");
            printf("\n2 = dump demod registes");
            printf("\n3 = rescan");
            printf("\r\n");
            scanf("%bu", &i);
            switch(i)
            {
                case 0: //quit
                    break;
                case 1: //quit
                    TUNER_TESTAPI_DBG(printf("\nFE = %bu", msAPI_Tuner_GetLockStatus(stTPSetting.fModulation)));
                    break;
                case 2: //dump demodulator registers value
                    #if (FRONTEND_DEMOD_TYPE == LG_3303_DEMODE)
                    printf("\nLG3303 Registers:\r\n");
                     printf("ADDR 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
                    for(i=0; i<0x8F; i+=16)
                     {
                         if((i%16) == 0)
                         {
                             MDrv_IIC_ReadBytes(LGDT3303_devAddr, 1, &i, 16, au8Data);
                            printf("0x%02bX", i);
                         }

                        for(j=0; j<16; j++)
                        {
                            printf(" %02bX", au8Data[j]);
                        }
                        printf("\r\n");
                     }
                    #endif
                    break;
                case 3:
                    goto __RESCAN;
                    break;
            }
        }
        */
    }
}
#endif
//*************************************************************************
//Function name:    msAPI_Tuner_PaThruI2C_WriteBytes
//Description:      This function write Frequncy  by UART command
//  [doxygen]
/// This function write Frequncy  by UART command
///@param u8SlaveID \b IN  Tuner's Slave ID
///@param u8AddrNum \b IN  Write Address count
///@param u8AddrNum \b IN  Write Address
///@param paddr     \b IN  Write date count
///@param pu8data \b IN  Write data
///@return - return I2C ACK
///         - TRUE : Succes
///         - FALSE: fail
//*************************************************************************
BOOLEAN msAPI_Tuner_PaThruI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    msAPI_Tuner_PaThruI2C(ENABLE);

    if(MDrv_IIC_WriteBytes(u8SlaveID, u8AddrNum, paddr, u16size, pu8data) == FALSE)
        return FALSE;

    msAPI_Tuner_PaThruI2C(DISABLE);

    return TRUE;

}


//*************************************************************************
//Function name:    msAPI_Tuner_PaThruI2C_ReadBytes
//Description:      This function read Frequncy  by UART command
//  [doxygen]
/// This function write Frequncy  by UART command
///@param u8SlaveID \b IN  Tuner's Slave ID
///@param u8AddrNum \b IN  Write Address count
///@param u8AddrNum \b IN  Write Address
///@param paddr     \b IN  Write date count
///@param pu8data \b IN  point data for read byte
///@return - return I2C ACK
///         - TRUE : Succes
///         - FALSE: fail
//*************************************************************************
BOOLEAN msAPI_Tuner_PaThruI2C_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data)
{
    msAPI_Tuner_PaThruI2C(ENABLE);

    if(MDrv_IIC_ReadBytes(u8SlaveID, u8AddrNum, paddr, u16size, pu8data) == FALSE)
        return FALSE;

    msAPI_Tuner_PaThruI2C(DISABLE);

    return TRUE;
}
#if (TV_FREQ_SHIFT_CLOCK)
static U32 _TunerPllStepToRealFreq(U16 u16TunerPll)
{
#if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
    return (U32)u16TunerPll * 62500;
#elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
    return (U32)u16TunerPll * 50000;
#else
    #error "unknown tuner step"
#endif
}

void _TVShiftClk(AVD_ATV_CLK_TYPE u8Mode)
{
    printf("\r\n _TVShiftClk=%x, %x\n",u8Mode, g_u8_ShiftClk_LastMode);

    if( u8Mode != g_u8_ShiftClk_LastMode )
    {
        //printf("\r\nTv shift Clk=%d\n", u8Mode);
        switch (u8Mode)
        {
            case E_ATV_CLK_TYPE1_42MHZ:
                printf("----E_ATV_CLK_TYPE1_42MHZ-----\n");
                MApi_AUDIO_SIF_Shift(MSAPI_AUD_SIF_42M);
                DRV_VIF_ShiftClk((U8)u8Mode);
                msAPI_AVD_ShiftClk(E_ATV_CLK_TYPE1_42MHZ);
                break;
            case E_ATV_CLK_TYPE2_44P4MHZ:
                printf("----E_ATV_CLK_TYPE1_44p4MHZ-----\n");
                MApi_AUDIO_SIF_Shift(MSAPI_AUD_SIF_44M);
                DRV_VIF_ShiftClk((U8)u8Mode);
                msAPI_AVD_ShiftClk(E_ATV_CLK_TYPE2_44P4MHZ);
                break;
            case E_ATV_CLK_ORIGIN_43P2MHZ:
            default:
                printf("----E_ATV_CLK_TYPE1_43.2MHZ-----\n");
                MApi_AUDIO_SIF_Shift(MSAPI_AUD_SIF_43M);
                DRV_VIF_ShiftClk((U8)u8Mode);
                msAPI_AVD_ShiftClk(E_ATV_CLK_ORIGIN_43P2MHZ);
                break;
        }
        //msAPI_Tuner_SetIF();
        g_u8_ShiftClk_LastMode = (U8)u8Mode;
    }

}
static AVD_ATV_CLK_TYPE _Get_Shift_Mode(U32 u32Freq)
{
    U32 u32Freq_KHz = u32Freq / 1000;
    printf("\r\nEnable SW Patch Freq= %d", u32Freq_KHz);

    if (u32Freq_KHz <= 237000)   // 0~237MHz
    {
        if (((u32Freq_KHz >= 85250)&&(u32Freq_KHz <= 87650)) ||
            ((u32Freq_KHz >= 127250)&&(u32Freq_KHz <= 130850)) ||
            ((u32Freq_KHz >= 169250)&&(u32Freq_KHz <= 174050)) ||
            ((u32Freq_KHz >= 211250)&&(u32Freq_KHz <= 217250)))
        {
            return E_ATV_CLK_TYPE1_42MHZ;
        }
        else if (((u32Freq_KHz >= 81400)&&(u32Freq_KHz <= 83800)) ||
            ((u32Freq_KHz >= 124600)&&(u32Freq_KHz <= 127000)) ||
            ((u32Freq_KHz >= 167800)&&(u32Freq_KHz <= 169000)))
        {
            return E_ATV_CLK_TYPE2_44P4MHZ;
        }
    }
    else if (u32Freq_KHz <= 453000)   // 237~453MHz
    {
        if (((u32Freq_KHz >= 253250)&&(u32Freq_KHz <= 260450)) ||
            ((u32Freq_KHz >= 295250)&&(u32Freq_KHz <= 303650)) ||
            ((u32Freq_KHz >= 340600)&&(u32Freq_KHz <= 346850)) ||
            ((u32Freq_KHz >= 383800)&&(u32Freq_KHz <= 390050)) ||
            ((u32Freq_KHz >= 427000)&&(u32Freq_KHz <= 433250)))
        {
            return E_ATV_CLK_TYPE1_42MHZ;
        }
    }
    else if (u32Freq_KHz <= 669000)   // 453~669MHz
    {
        if (((u32Freq_KHz >= 470200)&&(u32Freq_KHz <= 476450)) ||
            ((u32Freq_KHz >= 513400)&&(u32Freq_KHz <= 519650)) ||
            ((u32Freq_KHz >= 556600)&&(u32Freq_KHz <= 562850)) ||
            ((u32Freq_KHz >= 599800)&&(u32Freq_KHz <= 606050)) ||
            ((u32Freq_KHz >= 643000)&&(u32Freq_KHz <= 649250)))
        {
            return E_ATV_CLK_TYPE1_42MHZ;
        }
    }
    else
    {
        if (((u32Freq_KHz >= 686200)&&(u32Freq_KHz <= 692450)) ||
            ((u32Freq_KHz >= 729400)&&(u32Freq_KHz <= 735650)) ||
            ((u32Freq_KHz >= 772600)&&(u32Freq_KHz <= 778850)) ||
            ((u32Freq_KHz >= 815800)&&(u32Freq_KHz <= 822050)) ||
            ((u32Freq_KHz >= 859000)&&(u32Freq_KHz <= 865250)))
        {
            return E_ATV_CLK_TYPE1_42MHZ;
        }
    }
    return E_ATV_CLK_ORIGIN_43P2MHZ;

}

static void _Set_Shift_Freq(U32 u32Freq)
{
    AVD_ATV_CLK_TYPE u8FreqShiftMode = E_ATV_CLK_ORIGIN_43P2MHZ;
    if (MApp_TopStateMachine_GetTopState()== STATE_TOP_ATSC_SCAN)
    {
        _TVShiftClk(E_ATV_CLK_ORIGIN_43P2MHZ);
        return;
    }
    u8FreqShiftMode=_Get_Shift_Mode(u32Freq);
    _TVShiftClk(u8FreqShiftMode);
}

void msAPI_Tuner_Patch_TVShiftClk(BOOL bEnable)
{
    U32 u32TunerFreq;

    printf("msAPI_Tuner_Patch_TVShiftClk=%x\n",(U16)bEnable);

    if (bEnable)
    {
        u32TunerFreq=_TunerPllStepToRealFreq(stCurrentTPSetting.u16Frequency);
        printf("\r\nEnable shift Patch Freq= %d", u32TunerFreq);
        _Set_Shift_Freq(u32TunerFreq);
    }
    else
    {
        _TVShiftClk(E_ATV_CLK_ORIGIN_43P2MHZ);
    }
}

void msAPI_Tuner_Patch_TVShiftVDClk(BOOL bEnable)
{
    U32 u32TunerFreq;
    AVD_ATV_CLK_TYPE u8FreqShiftMode = E_ATV_CLK_ORIGIN_43P2MHZ;
    printf("msAPI_Tuner_Patch_TVShiftVDClk=%x\n",(U16)bEnable);

    if (bEnable)
    {
        u32TunerFreq=_TunerPllStepToRealFreq(stCurrentTPSetting.u16Frequency);
        printf("\r\nEnable VD shift Patch Freq= %d", u32TunerFreq);
        u8FreqShiftMode=_Get_Shift_Mode(u32TunerFreq);
        msAPI_AVD_ShiftClk(u8FreqShiftMode);
    }
    else
    {
        msAPI_AVD_ShiftClk(E_ATV_CLK_ORIGIN_43P2MHZ);
}
}
void msAPI_Tuner_Patch_ResetTVShiftClk(void)
{
    g_u8_ShiftClk_LastMode = 0xFF;
}

#endif

/*------------------------------------------------------//
// + Set_Tuner_Freq
//     : Call the function for the tuner setup, which is implemented in Tuner.cpp
//
// + Input    : float - frequency to tune //Khz
// + Input    : EN_DEMOD_ATSC_MODE - modulation type
// + Return    : BOOLEAN
//------------------------------------------------------*/
BOOLEAN Set_Tuner_Freq(U32 u32FreqKHz, EN_DEMOD_ATSC_MODE enModulation)
{
    DEBUG_API_TUNER_FREQ_ATSC(printf("Set_Tuner_Freq(u32FreqKHz=%u, enModulation=%u)\n", u32FreqKHz, enModulation););

    if(enModulation == DEMOD_ATSC_MODE_NTSC)
    {
        DEBUG_API_TUNER_FREQ_ATSC( printf("Mod=DEMOD_ATSC_MODE_NTSC\n"); );
        devTuner_Std_set(E_TUNER_ATV_NTSC_MODE, E_AUDIOSTANDARD_M_);
        devTunerSetFreq(u32FreqKHz*1000);
        //retb &= ATV_SetTune(u16Freq_over_freq_step_khz,(RFBAND)0, E_TUNER_ATV_NTSC_MODE,E_AUDIOSTANDARD_M_);
    }
    else if(enModulation == DEMOD_ATSC_MODE_8VSB)
    {
        DEBUG_API_TUNER_FREQ_ATSC( printf("Mod=DEMOD_ATSC_MODE_8VSB\n"); );
        devTuner_Std_set(E_TUNER_DTV_ATSC_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
        devDigitalTuner_SetFreq(u32FreqKHz+1750, E_RF_CH_BAND_6MHz);
        //retb &= DTV_SetTune(u16Freq_over_freq_step_khz,E_RF_CH_BAND_6MHz, E_TUNER_DTV_ATSC_MODE);
    }
    else
    {
        DEBUG_API_TUNER_FREQ_ATSC( printf("Mod=QAM\n"); );
        devTuner_Std_set(E_TUNER_DTV_QAM_US_MODE, E_AUDIOSTANDARD_NOTSTANDARD_);
        devDigitalTuner_SetFreq(u32FreqKHz+1750, E_RF_CH_BAND_6MHz);
        //retb &= DTV_SetTune(u16Freq_over_freq_step_khz,E_RF_CH_BAND_6MHz, E_TUNER_DTV_QAM_US_MODE);
    }

    MsOS_DelayTask(5);//temp solution for tuner

    return TRUE;
}

//*************************************************************************
//Function name:    msAPI_Tuner_SetFreq
//Description:      This function Set RF tuner frequency
//  [doxygen]
/// This function Set RF tuner frequency
/// @param u16Frequency \b IN: Setting RF frequency
/// @param enModulation \b IN: Modulation type of TS
//*************************************************************************
void msAPI_Tuner_SetFreq(U16 u16Frequency, EN_DEMOD_ATSC_MODE enModulation)
{
    U32 u32FreqKHz = (U32)(u16Frequency)*FREQ_STEP;

    //printf("Tuner Freq=%uKHz\n", u32FreqKHz);
    DEBUG_API_TUNER_FREQ_ATSC( printf("msAPI_Tuner_SetFreq(u16Frequency=%u(%uKHz), enModulation=%u) at %u\n", u16Frequency, u32FreqKHz, enModulation, MsOS_GetSystemTime()); );

    if( (u32FreqKHz <= 50000) || (u32FreqKHz >= 900000) )
    {
        printf("\nError: Freq=%u(%uKHz)\n", u16Frequency, u32FreqKHz);
        msDebug_FatalErrorHandler(FATAL_ERR_ID_TUNER_FREQ_INVALID, u32FreqKHz);
        return;
    }

#if TS_THROUGH_LVDS
    stCurrentTPSetting.u16Frequency = u16Frequency;
    return;
#endif

    msAPI_Tuner_PaThruI2C(ENABLE);

    // Config Tuner
    if( FALSE == Set_Tuner_Freq(u32FreqKHz, enModulation) )
    {
        TUNER_API_DBG(printf("Tuner I2C config Error!\r\n"););
    }

    msAPI_Tuner_PaThruI2C(DISABLE);

    stCurrentTPSetting.u16Frequency = u16Frequency;

#if (TV_FREQ_SHIFT_CLOCK)
     _Set_Shift_Freq(stCurrentTPSetting.u16Frequency);
#endif
}


#undef MSAPI_TUNER_A_C

