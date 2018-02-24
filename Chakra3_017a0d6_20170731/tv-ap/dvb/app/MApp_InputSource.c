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

#define MAPP_INPUTSOURCE_C

/********************************************************************************/
/*                    Header Files                                              */
/********************************************************************************/
#include <string.h>
#include <stdio.h>
#include "datatype.h"
#include "Board.h"

#include "msAPI_Global.h"
#include "apiXC.h"
#include "apiXC_Sys.h"
#include "drvXC_HDMI_if.h"
#include "apiXC_Hdmi.h"
#include "apiAUDIO.h"
#include "drvAVD.h"
#include "drvAUDIO.h"
#include "drvAUDIO_if.h"
#include "apiXC_Adc.h"

#include "debug.h"

#ifdef SCART_OUT_NEW_METHOD
#include "drvTVEncoder.h"
#endif

#include "msAPI_CPU.h"

#if (ENABLE_CI)
#include "msAPI_CI.h" //**-- Italy CI Certificate --**//
#endif
#include "msAPI_Memory.h"


#include "msAPI_Mode.h"
#include "apiXC_Ace.h"

#include "msAPI_Video.h"
#include "apiXC_PCMonitor.h"
#include "msAPI_Global.h"
#include "apiXC_Dlc.h"

#if(ENABLE_S2)
#include "MApp_Scan.h"
#if(DISH_TYPE != DISH_NONE)
#include "drvDish.h"
#endif
#endif

#include "msAPI_Demod.h"

#if (ENABLE_PWS)
  #include "drvPWS.h"
#endif

#include "msAPI_Timer.h"
#include "msAPI_MIU.h"
#include "msAPI_Tuner.h"

#include "msAPI_VD.h"
#include "msAPI_Tuning.h"
#include "msAPI_audio.h"
#include "msAPI_DrvInit.h"
#include "msAPI_Power.h"
#include "msAPI_ATVSystem.h"

#include "msAPI_ChProc.h"

#if(ENABLE_ATSC)
#include "msAPI_AtscEpgDb.h"
#endif

#include "MApp_Init.h"
#include "MApp_MVDMode.h"
#include "MApp_PCMode.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Key.h"
#include "MApp_InputSource.h"

#include "MApp_VDMode.h"
#include "MApp_GlobalVar.h"
#include "MApp_ChannelChange.h"
#include "MApp_Scaler.h"
#include "MApp_XC_Sys.h"
#if(ENABLE_EWS)
#include "MApp_EWS.h"
#endif

#if (ENABLE_DTV)
#include "mapp_si.h" //**-- Italy CI Certificate --**//
#include "mapp_demux.h"
#include "msAPI_DTV_DB.h"
#endif

#include "MApp_ATVProc.h"
#include "MApp_Audio.h"
#include "GPIO.h"
#include "MApp_AnalogInputs.h"

#include "MApp_MassStorage.h"
#if (ENABLE_TTX)
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#endif

#include "IF_Demodulator.h"

#include "MApp_UiMenuDef.h"
#include "MApp_BlockSys.h"
#include "MApp_ChannelList.h" //ZUI:

#if (ENABLE_SUBTITLE)
#include "MApp_Subtitle.h" //ZUI:
#endif

#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#include "MApp_VChip.h"
#endif

#include "MApp_TopStateMachine.h" //ZUI:
#include "MApp_InputSource_Main.h"

#if 1//MCU_AEON_ENABLE
#include "drvCPU.h"
#endif

#include "HdmiSwitch.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif

#include "MApp_MultiTasks.h"

#if 1 //def AP_COWORK
#include "MApp_APEngine.h"
#include "msAPI_APEngine.h"
#endif

#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"

#if ENABLE_CEC
#include "msAPI_CEC.h"
#include "apiCEC.h"
#endif

#ifdef ENABLE_SELECT_NONESEARCH_CH
#include "MApp_TV.h"
#endif

#if (ENABLE_CI_PLUS)
#include "MApp_CIMMI.h"
#endif

#if (ENABLE_MHL == ENABLE)
#include "msAPI_MHL.h"
#if (MHL_TYPE == MHL_TYPE_INTERNAL)
#include "apiMHL.h"
#elif (MHL_TYPE == MHL_TYPE_ELAND)
#include "apiMHL_ELAND.h"
#endif
#endif

#if ENABLE_DDCCI
#include "drvDDC2BI.h"
#endif

#if (NO_SIGNAL_AUTO_SHUTDOWN )
#include "MApp_NoSignal_AutoSleep.h"
#endif

#if( CHAKRA3_AUTO_TEST )
#include "MApp_AutoTest.h"
#endif


#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
extern U8  gMSB1210ATVMode;
#endif

#if ENABLE_ISDBT
E_ANTENNA_SOURCE_TYPE enLastWatchAntennaType = ANTENNA_DTV_TYPE;
BOOLEAN checkdtvstatus=FALSE;
#endif

#if ENABLE_DDCCI
extern U8 MApp_DDC2BI_AlignControl(U8 *pDDCBuffData);
extern U8 MApp_DDC2BI_FactoryAdjustment(U8 *pDDCBuffData);
#endif

#if(ENABLE_S2)
extern void Int_DigiTuner_Tp_Sat(void);
#endif
#if ENABLE_PVR
#include "MApp_PVR.h"
#include "MApp_TimeShift.h"
#endif

#if ENABLE_DMP
#include "MApp_DMP_Main.h"
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#if( ENABLE_ATSC )
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_VChip.h"
#include "MApp_UiMenuFunc_ATSC.h"
#endif

//extern THR_TBL_TYPE code AuSifInitThreshold[];

#if ENABLE_OFFLINE_SIGNAL_DETECTION
extern void MApp_ZUI_ACT_DrawAisIcon(void);
#endif

/********************************************************************************/
/*                   Macro                                                      */
/********************************************************************************/
#define DEBUG_CHG_SRC_TIME2()    //printf("ChgSrc %u at %u\n", __LINE__, MsOS_GetSystemTime());

#define SIGNAL_PATH_DBG(x)      //do { msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED); x; msDebug_ANSI_AllAttrOffText(); } while(0)
#define INPUTSOURCE_DBG(y)      y //gchen @ 20171218 // open debug
#define AIS_DETECT_DUTY         100//150 // ms

#define DEBUG_CVBS_OUT(x)   //do { msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED); x; msDebug_ANSI_AllAttrOffText(); } while(0)//x


#if (ENABLE_DTV_CHCEK_USB_DELAY_2S)
static U32 u32CheckUSBMonitorTimer; //ms
#endif

static EN_VIF_WORKING_STATUS eVifStatus = E_VIF_NOT_NECESSARY;

CVBS_OUTPUT_INFO  CVBS1_OUTPUT_Tbl[] =
{
    //INPUT SOURCE              CVBS1 OUTPUT      CVBS1 AUDIOSource
    {INPUT_SOURCE_DTV,          INPUT_SOURCE_DTV ,AUDIO_SOURCE_DTV},
    {INPUT_SOURCE_TV,           INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},

#if(CVBSOUT1_ALWAYS_OUTPUT_ATV)
    {INPUT_SOURCE_CVBS,         INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_CVBS2,        INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_SVIDEO,       INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_YPBPR,        INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_VGA,          INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI,         INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI2,        INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI3,        INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_SCART,        INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_SCART2,       INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_DVI,          INPUT_SOURCE_TV  ,AUDIO_SOURCE_ATV},
#elif ((CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY))
    {INPUT_SOURCE_CVBS,         INPUT_SOURCE_CVBS   ,AUDIO_SOURCE_AV},
#elif ((FORCE_ALL_OUTPUT_THROUGH_VE)&&(ENABLE_VE))
    {INPUT_SOURCE_CVBS,         INPUT_SOURCE_CVBS   ,AUDIO_SOURCE_AV},
    {INPUT_SOURCE_CVBS2,        INPUT_SOURCE_CVBS2  ,AUDIO_SOURCE_AV2},
    {INPUT_SOURCE_SVIDEO,       INPUT_SOURCE_SVIDEO ,AUDIO_SOURCE_SV},
    {INPUT_SOURCE_YPBPR,        INPUT_SOURCE_YPBPR  ,AUDIO_SOURCE_YPBPR},
    {INPUT_SOURCE_VGA,          INPUT_SOURCE_VGA    ,AUDIO_SOURCE_PC},
    {INPUT_SOURCE_HDMI,         INPUT_SOURCE_HDMI   ,AUDIO_SOURCE_HDMI},
    {INPUT_SOURCE_HDMI2,        INPUT_SOURCE_HDMI2  ,AUDIO_SOURCE_HDMI2},
    {INPUT_SOURCE_HDMI3,        INPUT_SOURCE_HDMI3  ,AUDIO_SOURCE_HDMI3},
    {INPUT_SOURCE_SCART,        INPUT_SOURCE_SCART  ,AUDIO_SOURCE_SCART},
    {INPUT_SOURCE_SCART2,       INPUT_SOURCE_SCART2 ,AUDIO_SOURCE_SCART2},
    {INPUT_SOURCE_DVI,          INPUT_SOURCE_HDMI   ,AUDIO_SOURCE_DVI},
#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
    {INPUT_SOURCE_CVBS,         INPUT_SOURCE_CVBS   ,AUDIO_SOURCE_AV},
    {INPUT_SOURCE_CVBS2,        INPUT_SOURCE_CVBS2  ,AUDIO_SOURCE_AV2},
    {INPUT_SOURCE_SVIDEO,       INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_YPBPR,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_VGA,          INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI,         INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI2,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI3,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI4,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_SCART,        INPUT_SOURCE_SCART  ,AUDIO_SOURCE_SCART},
    {INPUT_SOURCE_SCART2,       INPUT_SOURCE_SCART2 ,AUDIO_SOURCE_SCART2},
    {INPUT_SOURCE_DVI,          INPUT_SOURCE_HDMI   ,AUDIO_SOURCE_ATV},
#else
    {INPUT_SOURCE_CVBS,         INPUT_SOURCE_CVBS   ,AUDIO_SOURCE_AV},
    {INPUT_SOURCE_CVBS2,        INPUT_SOURCE_CVBS2  ,AUDIO_SOURCE_AV2},
    {INPUT_SOURCE_SVIDEO,       INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_YPBPR,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_VGA,          INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
#if(ENABLE_ATSC)
    {INPUT_SOURCE_HDMI,         INPUT_SOURCE_NONE     ,AUDIO_NULL_INPUT},
    {INPUT_SOURCE_HDMI2,        INPUT_SOURCE_NONE     ,AUDIO_NULL_INPUT},
    {INPUT_SOURCE_HDMI3,        INPUT_SOURCE_NONE     ,AUDIO_NULL_INPUT},
    {INPUT_SOURCE_HDMI4,        INPUT_SOURCE_NONE     ,AUDIO_NULL_INPUT},
#else
    {INPUT_SOURCE_HDMI,         INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI2,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI3,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_HDMI4,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
#endif
    {INPUT_SOURCE_SCART,        INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_SCART2,       INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_DVI,          INPUT_SOURCE_HDMI   ,AUDIO_SOURCE_ATV},
#endif

    // This is end rule, don't modify it
    {INPUT_SOURCE_NONE,         INPUT_SOURCE_NONE    ,AUDIO_NULL_INPUT},  //ENDtbl don't modify output source

};

#if (ENABLE_CVBSOUT_2)
CVBS_OUTPUT_INFO  CVBS2_OUTPUT_Tbl[] =
{
    //INPUT SOURCE              CVBS1 OUTPUT
    {INPUT_SOURCE_DTV,          INPUT_SOURCE_DTV    ,AUDIO_SOURCE_DTV},
    {INPUT_SOURCE_TV,           INPUT_SOURCE_TV     ,AUDIO_SOURCE_ATV},
    {INPUT_SOURCE_CVBS,         INPUT_SOURCE_CVBS   ,AUDIO_SOURCE_AV},
    {INPUT_SOURCE_CVBS2,        INPUT_SOURCE_CVBS2  ,AUDIO_SOURCE_AV2},
    {INPUT_SOURCE_SCART,        INPUT_SOURCE_SCART  ,AUDIO_SOURCE_SCART},
    {INPUT_SOURCE_SCART2,       INPUT_SOURCE_SCART2 ,AUDIO_SOURCE_SCART2},
    {INPUT_SOURCE_NONE,         INPUT_SOURCE_NONE   ,AUDIO_NULL_INPUT},  //ENDtbl don't modify output source
};
#endif

#if ENABLE_PIP
static MS_BOOL _gbPIPCVBSOutEnable =0;
#endif

INPUT_SOURCE_TYPE_t _MAPP_GET_CVBSOUT_VIDEO_SOURCE( CVBS_OUTPUT_INFO* pCVBStbl, INPUT_SOURCE_TYPE_t u8InputSource )
{
    while(1)
    {
        if( pCVBStbl->u8InputSource == INPUT_SOURCE_NONE )
            break;

        if( pCVBStbl->u8InputSource == u8InputSource )
            return pCVBStbl->u8CVBSOutVideoSource;

        pCVBStbl++;
    }

    return INPUT_SOURCE_NONE;
}

INPUT_SOURCE_TYPE_t MApp_InputSource_Get_CVBSOut_Src(U8 u8CvbsOutIdx, INPUT_SOURCE_TYPE_t eInputSource)
{
    if( u8CvbsOutIdx == 0 )
        return _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS1_OUTPUT_Tbl, eInputSource);

#if (ENABLE_CVBSOUT_2)
    else if( u8CvbsOutIdx == 1 )
        return _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS2_OUTPUT_Tbl, eInputSource);
#endif

    return INPUT_SOURCE_NONE;
}

AUDIO_INPUT_TYPE _MAPP_GET_CVBSOUT_AUDIO_SOURCE( CVBS_OUTPUT_INFO* pCVBStbl, INPUT_SOURCE_TYPE_t u8InputSource )
{
        while(1)
       {
            if(pCVBStbl->u8InputSource== INPUT_SOURCE_NONE)
                return AUDIO_NULL_INPUT;  //return no source
            if(pCVBStbl->u8InputSource == u8InputSource)
                return pCVBStbl->u8CVBSOutAudioSource;
            pCVBStbl++;
        }

    return AUDIO_NULL_INPUT;
}

AUDIO_INPUT_TYPE MApp_InputSource_Get_CVBSOut_AudioSrc(U8 u8CvbsOutIdx, INPUT_SOURCE_TYPE_t eInputSource)
{
    if( u8CvbsOutIdx == 0 )
        return _MAPP_GET_CVBSOUT_AUDIO_SOURCE(CVBS1_OUTPUT_Tbl, eInputSource);

#if (ENABLE_CVBSOUT_2)
    else if( u8CvbsOutIdx == 1 )
        return _MAPP_GET_CVBSOUT_AUDIO_SOURCE(CVBS2_OUTPUT_Tbl, eInputSource);
#endif

    return AUDIO_NULL_INPUT;
}




/********************************************************************************/
/*                     Local                                                    */
/********************************************************************************/
BOOLEAN TunerInAtvMode = TRUE;
/*
static void _MApp_InputSource_ClearSysInputSourceFlag(SCALER_WIN eWindow)
{
    if(stSystemInfo[eWindow].enInputSourceType < INPUT_SOURCE_NUM)
    {
        EN_SYS_INPUT_SOURCE_TYPE enFlag = EN_SYS_INPUT_SOURCE_TYPE_NONE;
        switch(stSystemInfo[eWindow].enInputSourceType)
        {
            case INPUT_SOURCE_DTV:
            #if (ENABLE_S2)
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_S2|EN_SYS_INPUT_SOURCE_TYPE_DTV;
            #else
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_DTV;
            #endif
                break;
            case INPUT_SOURCE_TV:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_ATV;
                break;
            case INPUT_SOURCE_CVBS:
            case INPUT_SOURCE_CVBS2:
            case INPUT_SOURCE_CVBS3:
            case INPUT_SOURCE_CVBS4:
            case INPUT_SOURCE_CVBS5:
            case INPUT_SOURCE_CVBS6:
            case INPUT_SOURCE_CVBS7:
            case INPUT_SOURCE_CVBS8:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_CVBS;
                break;
            case INPUT_SOURCE_SVIDEO:
            case INPUT_SOURCE_SVIDEO2:
            case INPUT_SOURCE_SVIDEO3:
            case INPUT_SOURCE_SVIDEO4:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_SVIDEO;
                break;
            case INPUT_SOURCE_YPBPR:
            case INPUT_SOURCE_YPBPR2:
            case INPUT_SOURCE_YPBPR3:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_YPBPR;
                break;
            case INPUT_SOURCE_SCART:
            case INPUT_SOURCE_SCART2:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_SCART;
                break;
            case INPUT_SOURCE_HDMI:
            case INPUT_SOURCE_HDMI2:
            case INPUT_SOURCE_HDMI3:
            case INPUT_SOURCE_HDMI4:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_HDMI;
                break;
            case INPUT_SOURCE_VGA:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_VGA;
                break;
            case INPUT_SOURCE_STORAGE:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_STORAGE;
                break;
            default:
                break;
        }
        msAPI_InputSrcType_ClrType(eWindow,enFlag);
        INPUTSOURCE_DBG(printf("[Clear] _enSysInputSource[%d] = 0x%x\n", eWindow,(U16)msAPI_InputSrcType_GetType(eWindow)));
    }
}
*/

#if ENABLE_DTV
static EN_SYS_INPUT_SOURCE_TYPE MApp_GetDTV_Source_Type(void)
{

    #if ENABLE_S2
        if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_S2)
            return EN_SYS_INPUT_SOURCE_TYPE_S2;
    #endif

    #if ENABLE_ATSC
        if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_ATSC)
            return EN_SYS_INPUT_SOURCE_TYPE_ATSC;
    #endif

    #if ENABLE_DTMB
        if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DTMB)
            return EN_SYS_INPUT_SOURCE_TYPE_DTMB;
    #endif

    #if ENABLE_DVBT
        if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DVBT)
           return EN_SYS_INPUT_SOURCE_TYPE_DVBT;
    #endif

    #if ENABLE_DVBC
        if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DVBC)
            return EN_SYS_INPUT_SOURCE_TYPE_DVBC;
    #endif

    #if ENABLE_ISDBT
        if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_ISDBT)
            return EN_SYS_INPUT_SOURCE_TYPE_ISDBT;
    #endif

    return EN_SYS_INPUT_SOURCE_TYPE_NONE;

}
#endif

#if (ENABLE_FM_RADIO)
static BOOLEAN _MApp_InputSource_isGoToFMRadioSource(E_UI_INPUT_SOURCE enUiInputSourceType)
{
    if(enUiInputSourceType == UI_INPUT_SOURCE_FMRADIO)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif
static void _MApp_InputSource_SetSysInputSourceFlag(SCALER_WIN eWindow,E_UI_INPUT_SOURCE enUiInputSourceType)
{
    EN_SYS_INPUT_SOURCE_TYPE enFlag = EN_SYS_INPUT_SOURCE_TYPE_NONE;
#if (ENABLE_FM_RADIO)
    if(TRUE == _MApp_InputSource_isGoToFMRadioSource(enUiInputSourceType))
    {
        enFlag = EN_SYS_INPUT_SOURCE_TYPE_RADIO;
        msAPI_InputSrcType_SetType(eWindow,enFlag);
        return;
    }
#else
    UNUSED(enUiInputSourceType);
#endif

#if (GAME_ENABLE)
    if(MApp_InputSrc_Get_UiInputSrcType() == UI_INPUT_SOURCE_GAME)
    {
        enFlag = EN_SYS_INPUT_SOURCE_TYPE_GAME;
        msAPI_InputSrcType_SetType(eWindow,enFlag);
        return;
    }
#else
    UNUSED(enUiInputSourceType);
#endif

    if(stSystemInfo[eWindow].enInputSourceType < INPUT_SOURCE_NUM)
    {
        switch(stSystemInfo[eWindow].enInputSourceType)
        {

        #if ENABLE_DTV
            case INPUT_SOURCE_DTV:
                enFlag = MApp_GetDTV_Source_Type();
                break;
        #endif

            case INPUT_SOURCE_TV:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_ATV;
                break;
            case INPUT_SOURCE_CVBS:
            case INPUT_SOURCE_CVBS2:
            case INPUT_SOURCE_CVBS3:
            case INPUT_SOURCE_CVBS4:
            case INPUT_SOURCE_CVBS5:
            case INPUT_SOURCE_CVBS6:
            case INPUT_SOURCE_CVBS7:
            case INPUT_SOURCE_CVBS8:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_CVBS;
                break;
            case INPUT_SOURCE_SVIDEO:
            case INPUT_SOURCE_SVIDEO2:
            case INPUT_SOURCE_SVIDEO3:
            case INPUT_SOURCE_SVIDEO4:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_SVIDEO;
                break;
            case INPUT_SOURCE_YPBPR:
            case INPUT_SOURCE_YPBPR2:
            case INPUT_SOURCE_YPBPR3:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_YPBPR;
                break;
            case INPUT_SOURCE_SCART:
            case INPUT_SOURCE_SCART2:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_SCART;
                break;
            case INPUT_SOURCE_HDMI:
            case INPUT_SOURCE_HDMI2:
            case INPUT_SOURCE_HDMI3:
            case INPUT_SOURCE_HDMI4:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_HDMI;
                break;
            case INPUT_SOURCE_VGA:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_VGA;
                break;
            case INPUT_SOURCE_STORAGE:
                enFlag = EN_SYS_INPUT_SOURCE_TYPE_STORAGE;
                break;
            default:
                break;
        }
        msAPI_InputSrcType_SetType(eWindow,enFlag);

        INPUTSOURCE_DBG(printf("[Set] _enSysInputSource[%d] = 0x%x\n", eWindow,(U16)msAPI_InputSrcType_GetType(eWindow)));
    }
}
/********************************************************************************/
/*                   Functions                                                  */
/********************************************************************************/

void MApp_InputSource_RecordSource(E_UI_INPUT_SOURCE enUiInputSourceType)
{
    MApp_InputSrc_Set_PrevUiInputSrcType(enUiInputSourceType);
}

E_UI_INPUT_SOURCE MApp_InputSource_GetRecordSource(void)
{
    return MApp_InputSrc_Get_PrevUiInputSrcType();
}

void MApp_InputSource_RestoreSource(void)
{
    #if (ENABLE_PIP)
    //If sub window is opened, close SUB_WINDOW.
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        MApp_ClosePIPSubWindowSource();
    }
    #endif

    MApp_InputSrc_Set_UiInputSrcType(MApp_InputSrc_Get_PrevUiInputSrcType());    //UI_INPUT_SOURCE_TYPE = UI_PREV_INPUT_SOURCE_TYPE;
    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
}

void MApp_InputSource_ChangeVideoSource( INPUT_SOURCE_TYPE_t enInputSourceType )
{
#if( ENABLE_TTX && ENABLE_TTX_ANALOG )
    MApp_TTX_InitVBITeletext();
#endif

    switch ( enInputSourceType )
    {
        case INPUT_SOURCE_TV:
            //BY 20090406 msAPI_VD_AdjustVideoFactor( E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER );
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_ATV );
            break;

    #if (INPUT_AV_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_CVBS:
            //BY 20090406 msAPI_VD_AdjustVideoFactor( E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_VIDEO );
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_CVBS1 );
            break;
    #endif

    #if (INPUT_AV_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_CVBS2:
            //BY 20090406 msAPI_VD_AdjustVideoFactor( E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_VIDEO );
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_CVBS2 );
            break;
    #endif

    #if (INPUT_AV_VIDEO_COUNT >= 3)
        case INPUT_SOURCE_CVBS3:
            //BY 20090406 msAPI_VD_AdjustVideoFactor( E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_VIDEO );
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_CVBS3 );
            break;
    #endif

    #if ((INPUT_SV_VIDEO_COUNT >= 1)||(ENABLE_SCART_SVIDEO))
        case INPUT_SOURCE_SVIDEO:
            //BY 20090406 msAPI_VD_AdjustVideoFactor( E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_VIDEO );
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_SVIDEO1 );
            break;
    #endif

    #if (INPUT_SV_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_SVIDEO2:
            //BY 20090406 msAPI_VD_AdjustVideoFactor( E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_VIDEO );
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_SVIDEO2 );
            break;
    #endif

    #if (INPUT_SCART_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_SCART:
            //BY 20090406 msAPI_VD_AdjustVideoFactor( E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_VIDEO );
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_SCART1 );
            break;
    #endif

    #if (INPUT_SCART_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_SCART2:
            //BY 20090406 msAPI_VD_AdjustVideoFactor( E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_VIDEO );
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_SCART2 );
            break;
    #endif

        default:
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_INVALID );
            return;
    }

//#if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD) ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7J) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_M10))
     // not need reprogram TV
//#else
    if ( enInputSourceType == INPUT_SOURCE_TV )
    {
        msAPI_AVD_TurnOffAutoAV();
        msAPI_Tuner_ChangeProgram();
    }
    else
//#endif
    {
        // Why should wait!?
        //msAPI_AVD_WaitForVideoSyncLock();

#if ENABLE_TTX
        msAPI_TTX_ResetAcquisition();
#endif
        //msAPI_AVD_DetectVideoStandard( OPERATIONMETHOD_MANUALLY );
        msAPI_AVD_StartAutoStandardDetection();
    }

    //msAPI_VD_ClearSyncCheckCounter();
    msAPI_AVD_ClearAspectRatio();
}

//===============================================================================================
//
// All audio path are defined in each board header file !!!
// If you have any questions about it , please call MStar audio engineer
// to give you a hand !!!
//
//===========================================================================
#define DEBUG_CHANGE_AUDIO_SRC(x)   //x
void MApp_InputSource_ChangeAudioSource(INPUT_SOURCE_TYPE_t enInputSourceType,E_UI_INPUT_SOURCE enUiInputSourceType)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

   #ifndef  AUDIO_PATH_SPEAKER   //For remove chip define
       #define AUDIO_PATH_SPEAKER AUDIO_PATH_NULL
   #endif

    AUDIO_PATH_GROUP_TYPE Audio_pathgroup_status;

    DEBUG_CHANGE_AUDIO_SRC( printf(" ChangeAudioSource(enInputSourceType=%u)\n", enInputSourceType); );
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("ChangeAudioSource - Start" );
#endif


    Audio_pathgroup_status = MDrv_AUDIO_GetPathGroup();

    #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
        Audio_pathgroup_status = AUDIO_PATH_GROUP_2; // Use new audio path
    #endif


#if(ENABLE_ISDBT_AND_DVB)
    msAPI_AUD_Setup_SystemInfo();
#endif


    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN); // Most case==> ADC in
#if(ENABLE_FM_RADIO)
    if(TRUE==_MApp_InputSource_isGoToFMRadioSource(enUiInputSourceType))
    {
        //first,FMRadio audio source follow ATV audio source flow
        printf("Goto FMRadioSource \n");
        if (Audio_pathgroup_status == AUDIO_PATH_GROUP_2)
        {
            MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ATV_IN);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_ATV, 0);
            //MApi_AUDIO_SIF_SetThreshold(AuSifInitThreshold);
            msAPI_AUD_SIF_SetThreshold();
            MApi_AUDIO_InputSwitch(AUDIO_SOURCE_ATV, E_AUDIO_GROUP_MAIN);
            MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,INPUT_SOURCE_TV), E_AUDIO_GROUP_SCART);
            MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_BroadCast_);
            MApi_AUDIO_SetSystem(MSAPI_AUD_ATV_FM_RADIO);
            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_PLAY, 0,0);
            //TunerInAtvMode=TRUE;
        }
        else
        {
            MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ATV_IN);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_ATV, 0);
            MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_ATV, AUDIO_OUTPUT_MAIN_SPEAKER);
            MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
            MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,INPUT_SOURCE_TV), AUDIO_OUTPUT_LINEOUT);
            MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_ATV, AUDIO_SPDIF_OUTPUT);
            MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SIFOUT,       AUDIO_SOURCE_ATV, AUDIO_OUTPUT_SIFOUT);
            MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_ATV, AUDIO_OUTPUT_HP);
            MApi_AUDIO_InputSwitch(AUDIO_SOURCE_ATV, E_AUDIO_GROUP_INVALID);
            MApi_AUDIO_SetSystem(MSAPI_AUD_ATV_FM_RADIO);
            MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_PLAY, 0,0);
            //TunerInAtvMode=TRUE;
        }
        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);

        MApp_Audio_AdjustPreScale(m_eAudioSource);
        return;
    }
#else
    UNUSED(enUiInputSourceType);
#endif


    if (Audio_pathgroup_status == AUDIO_PATH_GROUP_2)
    {   //  used in Whisky,...
                   //=================== T3  setting=========================
        DEBUG_CHANGE_AUDIO_SRC( printf(" AUDIO_PATH_GROUP_2 \n"); );
        switch(enInputSourceType)
        {
            case INPUT_SOURCE_DTV:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_DTV_IN);
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0); //RF Mode
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LORO, 0);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_MPEG, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                   MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_BroadCast_EU_);
                TunerInAtvMode=FALSE;
                break;

            case INPUT_SOURCE_TV:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ATV_IN);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_ATV, 0);
                //MApi_AUDIO_SIF_SetThreshold(AuSifInitThreshold);
                msAPI_AUD_SIF_SetThreshold();
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_ATV, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_BroadCast_);
                TunerInAtvMode=TRUE;
                break;

             case INPUT_SOURCE_CVBS:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                Switch_AV() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_CVBS1, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_AV, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SIFOUT, AUDIO_SOURCE_AV, AUDIO_OUTPUT_SIFOUT);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;

          #if (INPUT_AV_VIDEO_COUNT >= 2)
             case INPUT_SOURCE_CVBS2:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                Switch_AV2() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_CVBS1, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_AV2, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SIFOUT, AUDIO_SOURCE_AV2, AUDIO_OUTPUT_SIFOUT);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif

          #if (INPUT_AV_VIDEO_COUNT >= 3)
            case INPUT_SOURCE_CVBS3:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                Switch_AV3() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_CVBS2, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_AV3, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SIFOUT, AUDIO_SOURCE_AV3, AUDIO_OUTPUT_SIFOUT);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif

          #if ((INPUT_SV_VIDEO_COUNT >= 1)||(ENABLE_SCART_SVIDEO))
            case INPUT_SOURCE_SVIDEO:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                Switch_SV() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_SVIDEO1, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_SV, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif
          #if (INPUT_SV_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_SVIDEO2:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                Switch_SV2() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_SVIDEO1, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_SV2, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif

          #if (INPUT_SCART_VIDEO_COUNT >= 1)
           case INPUT_SOURCE_SCART:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ATV_IN);
                Switch_SCART() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_SCART1, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_SCART, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif

          #if (INPUT_SCART_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_SCART2:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ATV_IN);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_SCART2, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_SCART2, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif

          #if (INPUT_YPBPR_VIDEO_COUNT >= 1)
            case INPUT_SOURCE_YPBPR:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                Switch_YPBPR() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_YPbPr, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_YPBPR, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif

          #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_YPBPR2:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                Switch_YPBPR2() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_YPbPr, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_YPBPR2, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif

            case INPUT_SOURCE_VGA:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                Switch_PC() ;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_PC, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_PC, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;

            case INPUT_SOURCE_HDMI:
            #if(INPUT_HDMI_VIDEO_COUNT>1)
                case INPUT_SOURCE_HDMI2:
            #endif
            #if(INPUT_HDMI_VIDEO_COUNT>2)
                case INPUT_SOURCE_HDMI3:
            #endif
            #if(INPUT_HDMI_VIDEO_COUNT>3)
                case INPUT_SOURCE_HDMI4:
            #endif
                if(g_HdmiPollingStatus.bIsHDMIMode)
                {
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_HDMI_IN);
                    MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0); //RF Mode
                    MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LORO, 0);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_HDMI, 0);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_HDMI, E_AUDIO_GROUP_MAIN);
                    MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                    MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                    break;
                }
           case INPUT_SOURCE_DVI:
                printf("\r\n Now is in DVI mode !!! Not HDMI ......");
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_DVI, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DVI, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;

          #if ENABLE_DMP
            case INPUT_SOURCE_STORAGE:
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_MM_IN);
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, LINE_MODE, 0); //Line Mod
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LORO, 0);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_MPEG, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_MAIN);
               MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
                break;
          #endif //#if ENABLE_DMP

            case INPUT_SOURCE_KTV:
            #ifdef AUDIO_SOURCE_KTV
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_KTV);
                MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_KTV_IN);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_MPEG, 0);
                MApi_AUDIO_InputSwitch(AUDIO_SOURCE_KTV, E_AUDIO_GROUP_MAIN);
                MApi_AUDIO_InputSwitch(MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), E_AUDIO_GROUP_SCART);
                MApi_AUDIO_SPDIF_ChannelStatus_CTRL((AUDIO_SPDIF_CS_TYPE)SPDIF_CS_CategoryCode_, (AUDIO_SPDIF_CS_TYPE_STATUS)SPDIF_CS_Category_General_);
            #endif
                break;

            default:
                    return;
           }

           //if(TunerInAtvMode) // For SCART switch
           //   MApi_AUDIO_InputSwitch(AUDIO_SOURCE_ATV, E_AUDIO_GROUP_SCART);
           //else
           //   MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_SCART);
    }
    else
    {
    //CAL_TIME_FUNC_START();

        //CAL_TIME_FUNC_("ChgAuSrc");
        DEBUG_CHANGE_AUDIO_SRC( printf(" AUDIO_PATH_GROUP_other\n"); );

        switch (enInputSourceType)
        {
            case INPUT_SOURCE_DTV:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_DTV_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_MPEG, 0);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_DTV, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_DTV, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SIFOUT,       AUDIO_SOURCE_DTV, AUDIO_OUTPUT_SIFOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_DTV, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    TunerInAtvMode=FALSE;

// Old 1D chip no need apply dolby loudness matching setting
#if (ENABLE_DTV && (CHIP_FAMILY_TYPE != CHIP_FAMILY_NASA) && (CHIP_FAMILY_TYPE != CHIP_FAMILY_MELODY) && (CHIP_FAMILY_TYPE != CHIP_FAMILY_EULER) && (CHIP_FAMILY_TYPE != CHIP_FAMILY_EDEN) && (CHIP_FAMILY_TYPE != CHIP_FAMILY_EMERALD)) // && (CHIP_FAMILY_TYPE != CHIP_FAMILY_MAZDA))
                //Update "HDMI channel status setting" and "DTV standard setting of audio_R2"
                switch(MApp_GetDTV_Source_Type())
                {
                    case EN_SYS_INPUT_SOURCE_TYPE_DVBT:
                    case EN_SYS_INPUT_SOURCE_TYPE_DVBC:
                    case EN_SYS_INPUT_SOURCE_TYPE_S2:
                        MDrv_AUDIO_SPDIF_SetChannelStatus(SPDIF_CHANNEL_STATUS_CATEGORY,SPDIF_CS_CATEGORY_DVB);
                        MApi_AUDIO_SetAC3PInfo(Audio_AC3P_infoType_LoudnessMatching, ENABLE, AUDIO_DTV_DVB);
                        break;
                    case EN_SYS_INPUT_SOURCE_TYPE_ATSC:
                        MDrv_AUDIO_SPDIF_SetChannelStatus(SPDIF_CHANNEL_STATUS_CATEGORY,SPDIF_CS_CATEGORY_ATSC);
                        MApi_AUDIO_SetAC3PInfo(Audio_AC3P_infoType_LoudnessMatching, ENABLE, AUDIO_DTV_ATSC);
                        break;
                    case EN_SYS_INPUT_SOURCE_TYPE_ISDBT:
                        MDrv_AUDIO_SPDIF_SetChannelStatus(SPDIF_CHANNEL_STATUS_CATEGORY,SPDIF_CS_CATEGORY_ISDB);
                        MApi_AUDIO_SetAC3PInfo(Audio_AC3P_infoType_LoudnessMatching, ENABLE, AUDIO_DTV_ISDB);
                        break;
                    case EN_SYS_INPUT_SOURCE_TYPE_DTMB:
                        MDrv_AUDIO_SPDIF_SetChannelStatus(SPDIF_CHANNEL_STATUS_CATEGORY,SPDIF_CS_CATEGORY_NONE);
                        MApi_AUDIO_SetAC3PInfo(Audio_AC3P_infoType_LoudnessMatching, ENABLE, AUDIO_DTV_DMBT);
                        break;
                    default:
                        MDrv_AUDIO_SPDIF_SetChannelStatus(SPDIF_CHANNEL_STATUS_CATEGORY,SPDIF_CS_CATEGORY_NONE);
                        MApi_AUDIO_SetAC3PInfo(Audio_AC3P_infoType_LoudnessMatching, ENABLE, AUDIO_DTV_OTHER);
                        break;
                }
#endif
                    break;

            case INPUT_SOURCE_TV:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ATV_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_ATV, 0);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_ATV, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_ATV, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SIFOUT,       AUDIO_SOURCE_ATV, AUDIO_OUTPUT_SIFOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_ATV, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_ATV, E_AUDIO_GROUP_INVALID);
                    TunerInAtvMode=TRUE;
                    break;

             case INPUT_SOURCE_CVBS:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    Switch_AV() ;
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_CVBS1, 0);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_AV, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_AV, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_AV, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    break;

          #if (INPUT_AV_VIDEO_COUNT >= 2)
             case INPUT_SOURCE_CVBS2:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    Switch_AV2() ;
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_CVBS1, 0);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_AV2, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_AV2, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_AV2, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    break;
          #endif

          #if (INPUT_AV_VIDEO_COUNT >= 3)
            case INPUT_SOURCE_CVBS3:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_CVBS2, 0);
                    Switch_AV3() ;
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_AV3, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_AV3, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_AV3, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    break;
          #endif

          #if ((INPUT_SV_VIDEO_COUNT >= 1)||(ENABLE_SCART_SVIDEO))
            case INPUT_SOURCE_SVIDEO:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_SVIDEO1, 0);
                    Switch_SV() ;
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_SV,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_SV,  AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_SV, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    break;
          #endif

          #if (INPUT_SV_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_SVIDEO2:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_SVIDEO1, 0);
                    Switch_SV2() ;
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_SV2, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_SV2, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_SV2, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    break;
          #endif

          #if (INPUT_SCART_VIDEO_COUNT >= 1)
           case INPUT_SOURCE_SCART:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ATV_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_SCART1, 0);
                    Switch_SCART() ;
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_SCART, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,    AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_SCART, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_SCART, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    //MApi_AUDIO_EnableDcRemove(true);
                    break;
          #endif

          #if (INPUT_SCART_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_SCART2:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ATV_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_SCART2, 0);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_SCART2, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,            AUDIO_SRC_INPUT,     AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_SCART2, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_SCART2, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    //MApi_AUDIO_EnableDcRemove(true);
                    break;
          #endif

          #if (INPUT_YPBPR_VIDEO_COUNT >= 1)
            case INPUT_SOURCE_YPBPR:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_YPbPr, 0);
                    Switch_YPBPR() ;
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_YPBPR, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,    AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_YPBPR , AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_YPBPR, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    break;
          #endif

          #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_YPBPR2:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_YPbPr, 0);
                    Switch_YPBPR2() ;
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_YPBPR2, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,     AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_YPBPR2, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_YPBPR2, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    break;
          #endif

            case INPUT_SOURCE_VGA:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_PC, 0);
                    Switch_PC() ;
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_PC , AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_PC , AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_PC, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    break;

            case INPUT_SOURCE_HDMI:
         #if(INPUT_HDMI_VIDEO_COUNT>1)
            case INPUT_SOURCE_HDMI2:
         #endif
         #if(INPUT_HDMI_VIDEO_COUNT>2)
           case INPUT_SOURCE_HDMI3:
         #endif
         #if(INPUT_HDMI_VIDEO_COUNT>3)
           case INPUT_SOURCE_HDMI4:
         #endif

                    if(g_HdmiPollingStatus.bIsHDMIMode)
                    {
                        MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_HDMI_IN);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_HDMI, 0);
                        MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_HDMI, AUDIO_OUTPUT_MAIN_SPEAKER);
                        MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,   AUDIO_OUTPUT_MAIN_SPEAKER);
                        MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                        MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_HDMI, AUDIO_SPDIF_OUTPUT);
                        MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_HDMI, AUDIO_OUTPUT_HP);
                        MApi_AUDIO_InputSwitch(AUDIO_SOURCE_HDMI, E_AUDIO_GROUP_INVALID);
                        break;
                    }
              // else ==> DVI mode
           case INPUT_SOURCE_DVI:
                    printf("\r\n Now is in DVI mode !!! Not HDMI ......");
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_ADC_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_DVI, 0);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_DVI,   AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,    AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_DVI,   AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_DVI, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                    //MApi_AUDIO_EnableDcRemove(true);
                    break;

          #if ENABLE_DMP
            case INPUT_SOURCE_STORAGE:
                #ifdef ENABLE_KTV
                if(gbKTVFlag == TRUE)
                {
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_KTV_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_MPEG, 0);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_DTV, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SRC_INPUT,  AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_DTV, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                }
                else
                #endif
                {
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_MM_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_MPEG, 0);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_DTV, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SOURCE_DTV, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_DTV, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_DTV, E_AUDIO_GROUP_INVALID);
                }
                    break;
          #endif //#if ENABLE_DMP

          #ifdef ENABLE_KTV
            case INPUT_SOURCE_KTV:
                    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_KTV_IN);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_CHANGE_AUDIOSOURCE, E_AUDIOSOURCE_MPEG, 0);
                    //MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_KTV, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_MAIN_SPEAKER, AUDIO_SOURCE_DTV, AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPEAKER,      AUDIO_SRC_INPUT,  AUDIO_OUTPUT_MAIN_SPEAKER);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      MApp_InputSource_Get_CVBSOut_AudioSrc(0,enInputSourceType), AUDIO_OUTPUT_LINEOUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SPDIF,        AUDIO_SRC_INPUT, AUDIO_SPDIF_OUTPUT);
                    MDrv_AUDIO_SetNormalPath(AUDIO_PATH_HP, AUDIO_SOURCE_DTV, AUDIO_OUTPUT_HP);
                    MApi_AUDIO_InputSwitch(AUDIO_SOURCE_KTV, E_AUDIO_GROUP_INVALID);
                    //MApi_AUDIO_EnableDcRemove(true);
                    //MApi_AUDIO_SetKTVMusicMicMix (TRUE);
                    break;
          #endif //#ifdef ENABLE_KTV

            default:
                    return;
       }

        //CAL_TIME_FUNC_("ChgAuSrc");

      #if SCART_ALWAYS_OUTPUT_ATV     // Please Use SIF out port for scart setting
        if(enInputSourceType != INPUT_SOURCE_DTV)
        {
            MDrv_AUDIO_SetNormalPath(AUDIO_PATH_SIFOUT,      AUDIO_SOURCE_ATV,   AUDIO_OUTPUT_SIFOUT);
        }
      #endif

        if(enInputSourceType==INPUT_SOURCE_STORAGE) //DMP shoud always enable for audio too large sound
        {
            MApi_AUDIO_EnableAutoVolume(ENABLE);
        }
        else
        {
            MApi_AUDIO_EnableAutoVolume((BOOLEAN)stGenSetting.g_SysSetting.fAutoVolume);
        }
    }

    //CAL_TIME_FUNC_("ChgAuSrc");
    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
    //CAL_TIME_FUNC_("ChgAuSrc");
    MApp_Audio_AdjustPreScale(m_eAudioSource);

  #if 0//ENABLE_DMP     // Should not unmute this flag when change source, will caused pop noise when enter MM from ATV nosignal.
    if ( enInputSourceType == INPUT_SOURCE_STORAGE )
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF,
                                    E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
  #endif

    //CAL_TIME_FUNC_END();
    //MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
    //MApp_Audio_AdjustPreScale(m_eAudioSource);
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("ChangeAudioSource - End" );
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}


static void MApp_SwitchInputSrcPin( INPUT_SOURCE_TYPE_t enInputSourceType )
{
    switch ( enInputSourceType )
    {
        case INPUT_SOURCE_VGA:
          #ifdef Switch_PC
            Switch_PC();
          #endif
          #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
           #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
           #endif
          #endif
            break;

   #if (INPUT_AV_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_CVBS:
          #ifdef Switch_AV
            Switch_AV();
          #endif
          #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
           #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
           #endif
          #endif
            break;
  #endif

  #if (INPUT_AV_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_CVBS2:
            #ifdef Switch_AV2
            Switch_AV2();
            #endif
         #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
          #endif

            break;
  #endif

  #if (INPUT_AV_VIDEO_COUNT >= 3)
        case INPUT_SOURCE_CVBS3:
            #ifdef Switch_AV3
            Switch_AV3();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
    #endif

            break;
  #endif

  #if ((INPUT_SV_VIDEO_COUNT >= 1)||(ENABLE_SCART_SVIDEO))
        case INPUT_SOURCE_SVIDEO:
            #ifdef Switch_SV
            Switch_SV();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
    #endif

            break;
   #endif

   #if (INPUT_SV_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_SVIDEO2:
            #ifdef Switch_SV2
            Switch_SV2();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
    #endif

            break;
    #endif

    #if (INPUT_YPBPR_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_YPBPR:
            #ifdef Switch_YPBPR
            Switch_YPBPR();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
    #endif
            break;
   #endif

   #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_YPBPR2:
            #ifdef Switch_YPBPR2
            Switch_YPBPR2();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
    #endif

            break;
   #endif

   #if (INPUT_SCART_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_SCART:
            #ifdef Switch_SCART
            Switch_SCART();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
    #endif
            break;
    #endif

   #if (INPUT_SCART_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_SCART2:
            #ifdef Switch_SCART2
            Switch_SCART2();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
    #endif

            break;
   #endif

   #if (INPUT_HDMI_VIDEO_COUNT >= 1)
        case INPUT_SOURCE_HDMI:
            #ifdef Switch_DVI
            Switch_DVI();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
        Switch_HDMI1();
    #endif

            break;
   #endif

   #if (INPUT_HDMI_VIDEO_COUNT >= 2)
        case INPUT_SOURCE_HDMI2:
            #ifdef Switch_DVI2
            Switch_DVI2();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
        Switch_HDMI2();
    #endif

          break;
   #endif

   #if (INPUT_HDMI_VIDEO_COUNT >= 3)
        case INPUT_SOURCE_HDMI3:
            #ifdef Switch_DVI3
            Switch_DVI3();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
        Switch_HDMI3();
    #endif

            break;
   #endif

   #if (INPUT_HDMI_VIDEO_COUNT >= 4)
        case INPUT_SOURCE_HDMI4:
           #ifdef Switch_DVI4
            Switch_DVI4();
            #endif
            break;
  #endif
    case INPUT_SOURCE_STORAGE:
        USBPowerOn();
        break;

        default:
            #ifdef Switch_DEFAULT
            Switch_DEFAULT();
            #endif
    #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
            #if(INPUT_HDMI_VIDEO_COUNT > 1)
            HDMI_STANDBY_MODE();
            #endif
    #endif
            break;
    }

}

static void MApp_InputSource_SetInputSource( SCALER_WIN eWindow, MS_SYS_INFO *penMsSysInfo )
{
    INPUTSOURCE_DBG( printf("MApp_InputSource_SetInputSource(win=%u)\n", eWindow); );
    static EN_VIF_WORKING_STATUS _s_eLast_eVifStatus = E_VIF_NOT_NECESSARY;
    BOOL bReInitVif = FALSE;


    MApp_SwitchInputSrcPin( penMsSysInfo->enInputSourceType );

  #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
    if (penMsSysInfo->enInputSourceType != INPUT_SOURCE_TV)
        gMSB1210ATVMode = 0;
  #endif

    // Init VIF
  #if (ENABLE_PIP)
    if((eWindow == MAIN_WINDOW &&(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
     ||(eWindow == SUB_WINDOW &&(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))))
    {
        //printf("\r\n main or sub window is DTV /ATV source ");
    }
    else
  #else
    if( IsATVInUse()
      #if(ENABLE_FM_RADIO)
      ||IsRADIOInUse()
      #endif
      ||( (_s_eLast_eVifStatus == E_VIF_NOT_NECESSARY)&&(eVifStatus != E_VIF_NOT_NECESSARY) )
      )
  #endif
    {
        MDrv_IFDM_Init();//Brian 20101215 move vif_initial in front of vd_mcu_reset to set vif path clock

        // Should not set reg here, move it to driver MDrv_IFDM_Init()
     #if 0//ENABLE_VD_PACH_IN_CHINA
         MDrv_WriteByte(0x112308,G_DESIGN_SETTING.stVDSetting.Vif_AGCREFNEGATIVE);
         MDrv_WriteByte(0x112222,0x96);
         MDrv_WriteByteMask(0x112220,G_DESIGN_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION<<1,BIT1);
     #endif

         msAPI_Tuner_Clear_IfFreqStatus();

#if CVBSOUT1_ALWAYS_OUTPUT_ATV
         if(!IsATVInUse()
      #if(ENABLE_FM_RADIO)
              && !IsRADIOInUse()
      #endif
            )
        {
            AUDIO_DSP_SYSTEM mAudCurDsp = msAPI_AUD_Get_CurDspSystem();

            msAPI_AUD_SwitchAudioDSPSystem(E_AUDIO_DSP_SIF);

            msAPI_AUD_Set_CurDspSystem(mAudCurDsp);
        }
#endif

         bReInitVif = TRUE;
    }

    if ( IsSrcTypeDigitalVD(penMsSysInfo->enInputSourceType) )
    {
        // BY 20090707 ADC set source should be done before VD change source

        MApp_InputSource_ChangeVideoSource( penMsSysInfo->enInputSourceType );

    }

    #if((CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
        (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
        (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) \
        )  //VIF related clk
        //Set 0x0B00[4] = 1 for CVBS out on Component,HDMI,VGA 20100426EL
        if(IsSrcTypeAnalog(penMsSysInfo->enInputSourceType) ||
            IsSrcTypeHDMI(penMsSysInfo->enInputSourceType))
        {
            MDrv_WriteByteMask(0x100B00, 0x10, 0x10);
        }

        //Set 0x0B4C[2] = 0 to select DAC out clock (0: VIF, 1: AV) to fix CVBS out spur issue on AV/SV/SCART 20100618EL
        if(IsSrcTypeDigitalVD(penMsSysInfo->enInputSourceType))
        {
            MDrv_WriteByteMask(0x100B4C, 0x00, 0x04);
        }
    #endif


    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))
  #if ENABLE_DMP
      ||IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(eWindow))
  #endif
      )
    {
        MApp_VID_VariableInit();

        MDrv_MVOP_Init();

    #if(MARLON_PATCH__MVOP_READ_OVER_RANGE)
        MDrv_WriteByteMask(0x101471, 0x00, 0x40); // bit[14] : 10bit
        MDrv_WriteByteMask(0x10148E, 0x02, 0x02); // bit[1] : mask LSB DMA request
    #endif

        MDrv_MVOP_Enable( TRUE );
    }
#if(ENABLE_PIP)
    //exp: In PIP/POP mode, main is TV and switch sub to another source.
    // It should not init DTV "AGAIN"
    else if( IsDTVInUse()||IsStorageInUse()|| IsS2InUse() )
    {
    }
#endif
    else
    {
        MApp_VID_VariableInit();
        //Disable MVOP, if not DTV or Storage
        MDrv_MVOP_Enable( FALSE );
        MDrv_MVOP_Exit();
    }

#if ENABLE_DTV
  #if (ENABLE_CI_PLUS)
    MApp_CI_ExitCiOperatorProfile();
  #endif

    /* Move to _MApp_ChangeSrc_Init_Tuner_Demod()
    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))
  #if(ENABLE_ATSC)
      ||IsAtscInUse()||IsATVInUse()
  #endif
      )
    {
        // Init demod by source
        msAPI_Tuner_Initialization_BySource();
    }
    */

#endif // ENABLE_DTV

#if ((FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)||(FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD))
    // 20150305: For CVBS out ATV while not ATV source
    if( //IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow))
     //||( (_s_eLast_eVifStatus == E_VIF_NOT_NECESSARY)&&(eVifStatus != E_VIF_NOT_NECESSARY) )
        (bReInitVif == TRUE )
      )
    {
        INPUTSOURCE_DBG( printf("Set VIF&tuner for ATV or CVBSOut\n"); );

    #if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) )
        MDrv_IFDM_Init();
    #endif

        msAPI_Tuner_Clear_IfFreqStatus();

        msAPI_Tuner_SetIF();

    #if( !ENABLE_ATSC )
        msAPI_SetTunerPLL();
    #endif
    }
#endif

    _s_eLast_eVifStatus = eVifStatus;
}

//*************************************************************************
//Function name:    MApp_InputSource_SetSystemmInfo
//Passing parameter:    U8  u8InputSrcType: current input source type
//                        MS_SYS_INFO *penMsSysInfo
//Return parameter:    none
//Description:            get system info. by enInputSourceType
//*************************************************************************

void MApp_InputSource_SetSystemmInfo( E_UI_INPUT_SOURCE enUiInputSourceType, MS_SYS_INFO *penMsSysInfo , E_DATA_INPUT_SOURCE *penDataInpSrcType)
{
    INPUTSOURCE_DBG( printf( "enUiInputSourceType  = %bu\n", (U8) enUiInputSourceType ) );

    switch ( enUiInputSourceType )
    {
    #if ENABLE_DTV
    #if ENABLE_S2
        case UI_INPUT_SOURCE_S2:
      #endif
    #if ENABLE_ATSC
        case UI_INPUT_SOURCE_ATSC:
    #endif
    #if ENABLE_DVBT
        case UI_INPUT_SOURCE_DVBT:
    #endif
    #if ENABLE_DVBC
        case UI_INPUT_SOURCE_DVBC:
    #endif
    #if ENABLE_DTMB
        case UI_INPUT_SOURCE_DTMB:
    #endif
    #if ENABLE_ISDBT
        case UI_INPUT_SOURCE_ISDBT:
    #endif            //printf("__DTV__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_DTV;
            *penDataInpSrcType = DATA_INPUT_SOURCE_DTV;
            break;
    #endif

    //#if (ENABLE_ATSC)
    //    case UI_INPUT_SOURCE_TV:
    //#endif
        case UI_INPUT_SOURCE_ATV:
            //printf("__ATV__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_TV;
            *penDataInpSrcType = DATA_INPUT_SOURCE_ATV;
            break;

     #if (INPUT_AV_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_AV:
            //printf("__AV__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_CVBS;
            *penDataInpSrcType = DATA_INPUT_SOURCE_AV;
            break;
     #endif

     #if (INPUT_AV_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_AV2:
            //printf("__AV2__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_CVBS2;
            *penDataInpSrcType = DATA_INPUT_SOURCE_AV2;
            break;
    #endif

    #if (INPUT_AV_VIDEO_COUNT >= 3)
        case UI_INPUT_SOURCE_AV3:
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_CVBS3;
            *penDataInpSrcType = DATA_INPUT_SOURCE_AV3;
            break;
    #endif

    #if (INPUT_SV_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_SVIDEO:
            //printf("__SVIDEO__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_SVIDEO;
            *penDataInpSrcType= DATA_INPUT_SOURCE_SVIDEO;
            break;
    #endif

    #if (INPUT_SV_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_SVIDEO2:
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_SVIDEO2;
            *penDataInpSrcType = DATA_INPUT_SOURCE_SVIDEO2;
            break;
    #endif

    #if (INPUT_YPBPR_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_COMPONENT:
            //printf("__YPBPR__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_YPBPR;
            *penDataInpSrcType = DATA_INPUT_SOURCE_COMPONENT;
            break;
    #endif

    #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_COMPONENT2:
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_YPBPR2;
            *penDataInpSrcType = DATA_INPUT_SOURCE_COMPONENT2;
            break;
    #endif

        case UI_INPUT_SOURCE_RGB:
            //printf("__RGB__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_VGA;
            *penDataInpSrcType = DATA_INPUT_SOURCE_RGB;
            break;

    #if (INPUT_HDMI_VIDEO_COUNT > 0)
        case UI_INPUT_SOURCE_HDMI:
            //printf("__HDMI0__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_HDMI;
            *penDataInpSrcType = DATA_INPUT_SOURCE_HDMI;
            break;
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_HDMI2:
            //printf("__HDMI1__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_HDMI2;
            *penDataInpSrcType = DATA_INPUT_SOURCE_HDMI2;
            break;
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 3)
        case UI_INPUT_SOURCE_HDMI3:
            //printf("__HDMI2__\n");
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_HDMI3;
            *penDataInpSrcType = DATA_INPUT_SOURCE_HDMI3;
            break;
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 4)
        case UI_INPUT_SOURCE_HDMI4:
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_HDMI4;
            *penDataInpSrcType = DATA_INPUT_SOURCE_HDMI4;
            break;
    #endif

#if((INPUT_SCART_VIDEO_COUNT >= 1)||(ENABLE_SCART_SVIDEO))

        case UI_INPUT_SOURCE_SCART:
#if(ENABLE_SCART_SVIDEO)
        if(stGenSetting.g_SysSetting.fSCARTInputSel == EN_SCART_SEL_SV)
        {
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_SVIDEO;
            *penDataInpSrcType = DATA_INPUT_SOURCE_SVIDEO;
        }
        else
#endif
        {
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_SCART;
            *penDataInpSrcType = DATA_INPUT_SOURCE_SCART;
        }
        break;

#endif
    #if (INPUT_SCART_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_SCART2:
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_SCART2;
            *penDataInpSrcType = DATA_INPUT_SOURCE_SCART2;
            break;
    #endif

    #if ENABLE_DMP
        case UI_INPUT_SOURCE_DMP:
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_STORAGE;
            *penDataInpSrcType = DATA_INPUT_SOURCE_STORAGE;
            break;
    #endif
    #if (ENABLE_FM_RADIO)
        case UI_INPUT_SOURCE_FMRADIO:
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_NONE;
            *penDataInpSrcType = DATA_INPUT_SOURCE_FMRADIO;
            break;
    #endif


        case UI_INPUT_SOURCE_NONE:
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_NONE;
            *penDataInpSrcType = DATA_INPUT_SOURCE_NONE;
            break;

    //#if(ENABLE_S2)
    //    case UI_INPUT_SOURCE_S2:
   //         penMsSysInfo->enInputSourceType = INPUT_SOURCE_DTV;
    //        *penDataInpSrcType = DATA_INPUT_SOURCE_DTV;//ENABLE_S2_SOURCE_TEST put dtv datatype here
   //         break;
    //#endif

        default:
            printf("\nError: Unknown UI src=%u\n", enUiInputSourceType);

        #if ENABLE_DTV
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_DTV;
            *penDataInpSrcType = DATA_INPUT_SOURCE_DTV;
        #else
            penMsSysInfo->enInputSourceType = INPUT_SOURCE_TV;
            *penDataInpSrcType = DATA_INPUT_SOURCE_ATV;
        #endif
            //INPUTSOURCE_DBG(printf("Error enInputSourceType = %bu\n",(U8)enInputSourceType));
            INPUTSOURCE_DBG(printf("[Unknown] set DTV as default input source type\n"));
            return;
    }

    //penMsSysInfo->enInputSourceType = enInputSourceType;

    INPUTSOURCE_DBG( printf( "Result enInputSourceType = %bu\n", (U8) penMsSysInfo->enInputSourceType ) );

#ifdef SCART_OUT_NEW_METHOD
//About the SCART OUT information generate
    MDrv_VE_Check_SCART_OUT_Mute();
#endif

}

//*************************************************************************
//Function name:    MApp_InputSource_InitModeVariables
//Passing parameter:    none
//Return parameter:     none
//Description:      initialize variables for mode changing
//*************************************************************************

static void MApp_InputSource_InitModeVariables( SCALER_WIN eWindow )
{
    // restart timing monitor
    MApi_XC_PCMonitor_Restart(eWindow);

    // input timing flag
    g_u8PcUserModeRamIndex[eWindow] = 0xFF;

#if ENABLE_OFFLINE_SIGNAL_DETECTION
     stAISCtrl.bUICHSourceFlag=1;
     stAISCtrl.bSysTimeDuty=0;
     //stAISCtrl.bAISLock=1;    //When Switch Source ,Lock AIS Polling;
     stAISCtrl.dLockCnt=TIMER_GO;    //    Begin Lock  Counter
     stAISCtrl.bDotimes=0;
     stAISCtrl.bNoSignal=0;
     stAISCtrl.bDetectCnt=0;
#endif

   #if ( ENABLE_DLC )
    g_bEnableDLC = FALSE;
   #endif

    if( IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow))
     || IsSrcTypeDVI(SYS_INPUT_SOURCE_TYPE(eWindow))
      )
    {
        MApi_XC_HDMI_Handler_Init();
    }

}
//*************************************************************************
//Function name:    MAPP_InputSource_SwitchHDMI_DVI
//Passing parameter:    HDMI or DVI mode
//Return parameter:     void
//Description:      Do all things about switching mode between HDMI / DVI
//*************************************************************************
void MAPP_InputSource_SwitchHDMI_DVI( U8 Source_Type)
{
     /*
           Now only implement audio channel swithing.
           The video swithing is not be done yet.
     */
    if ( (E_XC_HDMI_Status) Source_Type == E_HDMI_STATUS_DVI)
    {
        //printf("MAPP_InputSource_SwitchHDMI_DVI(E_HDMI_STATUS_DVI)\n");
        MApp_InputSource_ChangeAudioSource(INPUT_SOURCE_DVI,UI_INPUT_SOURCE_NONE);
    }
    else if ( (E_XC_HDMI_Status) Source_Type == E_HDMI_STATUS_HDMI)
    {
        //printf("MAPP_InputSource_SwitchHDMI_DVI(E_HDMI_STATUS_HDMI)\n");
        MApp_InputSource_ChangeAudioSource(INPUT_SOURCE_HDMI,UI_INPUT_SOURCE_NONE);
    }

}

#if ( ENABLE_PWS)
static E_PWS_SouceInfo _MAPP_InputSource_Source2PWSSource(INPUT_SOURCE_TYPE_t src,  E_UI_INPUT_SOURCE enUiInputSourceType)
{
    E_PWS_SouceInfo enTargetSource = _UNKNOWN_;

    //printf("_MAPP_InputSource_Source2PWSSource(src=%u)\n", src);

    if ( IsSrcTypeVga(src) )
    {
        enTargetSource = _RGB_;
    }
    else if ( IsSrcTypeYPbPr(src) )
    {
        enTargetSource = _YPbPr_;
    }
    else if ( IsSrcTypeDTV(src) )
    {
#if (CHIP_FAMILY_MARLON != CHIP_FAMILY_TYPE)
        UNUSED(enUiInputSourceType);
#else
// use _DTV_ATSC_ as handling DVB-S/S2 case because of PWS driver historical reason
// utopia commit: 14ffb8ef212faaecbd45411e86b5035a51829f70

        if(enUiInputSourceType == UI_INPUT_SOURCE_S2)
        {
            enTargetSource = _DTV_ATSC_;
        }
        else
#endif
        {
            enTargetSource = _DTV_DVB_; // ATSC???
        }
    }
    else if ( src == INPUT_SOURCE_HDMI)
    {
        enTargetSource = PWS_INPUT_HDMI1_PATH;
    }
    else if ( src == INPUT_SOURCE_HDMI2)
    {
        enTargetSource = PWS_INPUT_HDMI2_PATH;
    }
    else if ( src == INPUT_SOURCE_HDMI3)
    {
        enTargetSource = PWS_INPUT_HDMI3_PATH;
    }
    else if ( src == INPUT_SOURCE_HDMI4)
    {
        enTargetSource = PWS_INPUT_HDMI4_PATH;
    }
    else if ( IsSrcTypeScart(src) )
    {
        enTargetSource = _SCART_;
    }
    else if ( IsSrcTypeAV(src) )
    {
        enTargetSource = _CVBS_;
    }
    else if ( IsSrcTypeSV(src) )
    {
        enTargetSource = _SV_;
    }
    else if ( IsSrcTypeStorage(src) )
    {
        enTargetSource = _USB_;
    }
    else if ( IsSrcTypeATV(src) )
    {
    #if(FRONTEND_IF_DEMODE_TYPE == SAMSUNG_SI2176)
        enTargetSource = _CVBS_;
    #else
        enTargetSource = _ATV_VIF_;
    #endif
    }
#if(ENABLE_FM_RADIO)
    else if( IsRADIOInUse())
    {
    #if(FRONTEND_IF_DEMODE_TYPE == SAMSUNG_SI2176)
        enTargetSource = _CVBS_;
    #else
        enTargetSource = _ATV_VIF_;
    #endif
    }
#endif
    else
    {
        printf("\nError: Unknown src=%u\n", src);
    }


    return enTargetSource;
}
#endif

void _MApp_ChangeSrc_Init_Demux(void)
{
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("Init_Demux - Start");
#endif

    // Before init DMX, must exit DMX
    if( msAPI_DrvInit_Get_DemuxInited() )
    {
        msAPI_DrvInit_ExitDemux();
    }

    // Init demux at change source
    msAPI_DrvInit_InitDemux(E_INIT_DEMUX_AT_CHANGE_SOURCE);

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("Init_Demux - End");
#endif
}

void _MApp_ChangeSrc_Init_Tuner_Demod(E_UI_INPUT_SOURCE enUiInputSourceType)
{
    INPUTSOURCE_DBG( printf("%s(%u)\n", __FUNCTION__, enUiInputSourceType); );

    // Fix warnning
    enUiInputSourceType=enUiInputSourceType;

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("Init_Tuner_Demod - Start");
#endif

#if(CHAKRA3_AUTO_TEST)
    //AT_LOG("Init_Tuner_Demod Start" );
#endif

#if(FRONTEND_TUNER_TYPE == MSTAR_AVATAR2) //   SEC_DTOS403IR121B//LG_TDTC_G311D_TUNER//MSTAR_AVATAR2
    INPUTSOURCE_DBG( printf( "INPUT_SOURCE_TV = %d\n", (U8) INPUT_SOURCE_TV ) );
    INPUTSOURCE_DBG( printf( "INPUT_SOURCE_DTV = %d\n", (U8) INPUT_SOURCE_DTV ) );

    INPUTSOURCE_DBG( printf( "UI_INPUT_SOURCE_ATV = %d\n", (U8) UI_INPUT_SOURCE_ATV ) );
    INPUTSOURCE_DBG( printf( "UI_INPUT_SOURCE_DTV = %d\n", (U8) UI_INPUT_SOURCE_DTV ) );

    if( enUiInputSourceType == UI_INPUT_SOURCE_ATV )
    {
        printf("** ATV ** \n");
        devTunerInit();
    }
    else
    {
        printf("** DV ** \n");
    }
#endif


  #if (ENABLE_DTV)
    //if ( IsSrcTypeDTV( SYS_INPUT_SOURCE_TYPE(eWindow) ) )
    //if( IsDTVInUse()||IsS2InUse() )
    if (  IsDTVInUse()
      #if 0//(ENABLE_ATSC)
       || (IsAtscInUse() || IsATVInUse())
      #endif
       )
    {
        //msAPI_Tuner_Initialization();
        //power on tuner and set tri-state on
        msAPI_Tuner_Set_DemodPower( ENABLE );

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("Set_DemodPower");
    #endif

        // Init demod by source
        msAPI_Tuner_Initialization_BySource();

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("Tuner_Init");
    #endif

        msAPI_Tuner_InitCurrentTPSetting();

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("InitTPSetting");
    #endif

    }
    else
    {
        // Stop use demod
        msAPI_Demodulator_Exit();

        //power off tuner and tri-state off
        msAPI_Tuner_Set_DemodPower( DISABLE );
    }
  #endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("Init_Tuner_Demod - End");
#endif

#if(CHAKRA3_AUTO_TEST)
    //AT_LOG("Init_Tuner_Demod end" );
#endif
}

#if( ENABLE_PVR )
void _MApp_ChangeSrc_Init_PVR(void)
{
    INPUTSOURCE_DBG( printf("%s()\n", __FUNCTION__); );

    if ( MApp_PVR_StateMachineGet() == E_PVR_STATE_WAIT )
    {
        U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
        if ((u8USBState & MS_USB_CONNECTED) || (u8USBState & MS_USB2_CONNECTED))
        {
            g_bPvrChgSrcInitFs = 1;
    #if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
            msAPI_PVR_InitMetadataBuff();
    #endif
            MApp_PVR_SetDiskDriveIndex(msAPI_PVRFS_GetDriveIndex(), FALSE); //co-buffer issue, need to re-init buffer setting
        }
    }
}
#endif

#if ENABLE_TTX
void _MApp_ChangeSrc_DeInit_TTX(void)
{
#if ENABLE_ISDBT
    if(IS_SBTVD_APP)
        return;
#endif
    INPUTSOURCE_DBG(printf("_MApp_ChangeSrc_DeInit_TTX()\n"););

    if (MApp_TTX_IsTeletextOn() == TRUE)
    {
        MApp_TTX_TeletextCommand(TTX_TV);
    }

    msAPI_TTX_VBIAcquireEnable(FALSE);

    msAPI_TTX_Stop();
}

void _MApp_ChangeSrc_Init_TTX(void)
{
#if ENABLE_ISDBT
    if(IS_SBTVD_APP)
        return;
#endif
    INPUTSOURCE_DBG(printf("_MApp_ChangeSrc_Init_TTX()\n"););

    //g_NeedReloadTTXFont = TRUE;    // Force TTX to reload font
    if ( IsDTVInUse()
 #if ENABLE_S2
      || IsS2InUse()
 #endif
       )
    {
        msAPI_TTX_OnOffVBISlicer( DISABLE );
        msAPI_TTX_SetTTXFid(DMX_DMXID_NULL);
        msAPI_TTX_SetSource( TTX_SOURCE_DTV );
        msAPI_TTX_Run();
    }
  #if( ENABLE_TTX_ANALOG )
    else if ( IsDigitalSourceInUse() )
    {
        //msAPI_TTX_DecCreate();
        msAPI_TTX_OnOffVBISlicer( ENABLE );
        msAPI_TTX_SetSource( TTX_SOURCE_ANALOG );
        msAPI_TTX_VBIAcquireEnable(TRUE);
        msAPI_TTX_Run();

    }
  #endif
    else
    {
        // in other sources, we don't need to turn on backgound TTX packets receving
        msAPI_TTX_OnOffVBISlicer( DISABLE );
    }

    MApp_TTX_Reflesh();

}

#endif

void _MApp_ChangeSrc_Init_AppScaler(SCALER_WIN eWindow)
{
    // Set Frame buffer range


    // Why should call  SetVDScale() here??
    MApp_Scaler_UpdateAspectRatioVar(eWindow);

    MApp_Scaler_Setting_SetVDScale( ST_VIDEO.eAspectRatio, eWindow );
}

void _MApp_ChangeSrc_Step_01_TurnOffFunction( E_UI_INPUT_SOURCE enUiInputSourceType,
                                                              SCALER_WIN eWindow )
{
    INPUTSOURCE_DBG( printf("%s(UiSrcTyp=%u, win=%u)\n", __FUNCTION__,enUiInputSourceType, eWindow); );

    // Warning
    enUiInputSourceType = enUiInputSourceType;

    // Enable Audio mute
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    // Enable Blue&black screen
    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, eWindow);


    // Disable image freeze
    if( MApp_IsImageFrozen() )
    {
        MApp_SetImageFrozen(FALSE);
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }


    // Disable 3D Comb
    MDrv_AVD_Set3dComb(DISABLE);


#if (ENABLE_SW_CH_FREEZE_SCREEN)
    if(stGenSetting.stTvSetting.u8SwitchMode == ATV_SWITCH_CH_FREEZE_SCREEN)
        msAPI_Scaler_SetFreezeScreen(DISABLE, 0, eWindow);
#endif

    // Reset Video mute client ...
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_RATING, DISABLE, NULL, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_HDMI_AVMUTE, DISABLE, 0, eWindow);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, DISABLE, 0, eWindow);
#if(ENABLE_ATSC)
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_VCHIP, DISABLE, 0, eWindow);
#endif
#if(ENABLE_EWS)
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_EWS, DISABLE, 0, eWindow);
#endif
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_VDEC, DISABLE, 0, eWindow);
#if(ENABLE_PVR)
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_PVR, DISABLE, 0, eWindow);
#endif

    // Reset Audio mute client ...
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_HDMI_AVMUTE_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYVCHIP_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
}

void _MApp_ChangeSrc_Step_02_DestroyPreSource( E_UI_INPUT_SOURCE eOldUiInputSrc, E_UI_INPUT_SOURCE eNewUiInputSrc,
                                                              SCALER_WIN eWindow )
{
    INPUTSOURCE_DBG( printf("%s(eOldUiInputSrc=%u, eNewUiInputSrc=%u, win=%u)\n", __FUNCTION__, eOldUiInputSrc, eNewUiInputSrc, eWindow); );
    //printf("%s(eOldUiInputSrc=%u, eNewUiInputSrc=%u, win=%u)\n", __FUNCTION__, eOldUiInputSrc, eNewUiInputSrc, eWindow);

    INPUT_SOURCE_TYPE_t eOldInputSrc = SYS_INPUT_SOURCE_TYPE(eWindow);

#if( ENABLE_SCRIPT_EXECUTE)
    msUS_UseScript(EN_SCRIPT_EVENT_INPUTSOURCE_SWITCHSOURCE);
#endif

    // Warning
    eOldUiInputSrc=eOldUiInputSrc;
    eNewUiInputSrc=eNewUiInputSrc;
    eWindow=eWindow;
    eOldInputSrc=eOldInputSrc;

#if(!SUPPORT_HDMI_IMM_SWITCH)
  #if(INPUT_HDMI_VIDEO_COUNT)
    if( IsSrcTypeHDMI(eOldInputSrc) )
    {
        MApi_XC_HPD_Do_ExitHDMI(eOldInputSrc);
    }
  #endif
#endif

#if ENABLE_DMP
    // DMP --> Non-DMP
    if( IsStorageInUse() // Old src is DMP
     //&& ( !IsSrcTypeStorage(eNewInputSrc) )// New src is not DMP
       && ( eNewUiInputSrc != UI_INPUT_SOURCE_DMP )// New src is not DMP
      )
    {
        MApp_DMP_Exit();
    }
#endif


#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#if BRAZIL_CC
    if(IS_SBTVD_APP)
#endif
    {
       // MApp_CC_ResetExistInfo();
        msAPI_CC_Reset(); // jany edit
    }
#endif

#if ENABLE_TTX
    if( eWindow != SUB_WINDOW )
    {
        _MApp_ChangeSrc_DeInit_TTX();
    }
#endif

    // Dmx-Exit when exit DTV source
#if ENABLE_DTV
    /*if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))
    #if(ENABLE_ATSC)
      ||(IsATVInUse())
    #endif
      )*/
    if( msAPI_DrvInit_Get_DemuxInited() )
    {
        // Close all filter & Dmx_Exit()
        msAPI_DrvInit_ExitDemux();
    }
#endif

}

#if( ENABLE_DTV)
void _MApp_ChangeSrc_Reset_DTV_APP(BOOL bOldSrcIsDTV, BOOL bNewSrcIsDTV)
{
    UNUSED(bOldSrcIsDTV);
    UNUSED(bNewSrcIsDTV);

#if( ENABLE_PVR )
    // If Non-DTV to DTV, init PVR
    if( (bOldSrcIsDTV == FALSE) && (bNewSrcIsDTV) )
    {
        _MApp_ChangeSrc_Init_PVR();
        DEBUG_CHG_SRC_TIME2();
    }
#endif

#if (ENABLE_ATSC&&ENABLE_ATSC_EPG_DB_2016 )
    if( (bOldSrcIsDTV == FALSE)&&(bNewSrcIsDTV == TRUE) )
    {
        msAPI_AtscEpgDb_ResetDB();
    }
#endif
}
#endif

void _MApp_ChangeSrc_Step_03_SetupNewSource( E_UI_INPUT_SOURCE eOldUiInputSourceType,
                                                              E_UI_INPUT_SOURCE enUiInputSourceType,
                                                              SCALER_WIN eWindow )
{
    BOOL bOldSrcIsDTV = FALSE;
    BOOL bNewSrcIsDTV = FALSE;

    INPUTSOURCE_DBG( printf("%s(Old=%u,New=%u,win=%u)\n", __FUNCTION__,eOldUiInputSourceType, enUiInputSourceType, eWindow); );

    // Warning
    UNUSED(eWindow);
    UNUSED(bOldSrcIsDTV);
    UNUSED(bNewSrcIsDTV);

#if ENABLE_DTV
    if( MApp_InputSrc_Is_UiInputSrcTypeDtv(eOldUiInputSourceType)
    #if(ENABLE_ATSC)
      ||(eOldUiInputSourceType==UI_INPUT_SOURCE_ATV)
    #endif
      )
    {
        bOldSrcIsDTV = TRUE;
    }

    if( MApp_InputSrc_Is_UiInputSrcTypeDtv(enUiInputSourceType)
    #if(ENABLE_ATSC)
      ||(enUiInputSourceType==UI_INPUT_SOURCE_ATV)
    #endif
      )
    {
        bNewSrcIsDTV = TRUE;
    }
#else
    UNUSED(eOldUiInputSourceType);
#endif

    DEBUG_CHG_SRC_TIME2();

#if ENABLE_DTV
    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))
    #if(ENABLE_ATSC)
      ||(IsATVInUse())
    #endif
      )
    {
        // Init Demux(Tsp)
        _MApp_ChangeSrc_Init_Demux();
        DEBUG_CHG_SRC_TIME2();
    }
#endif


#if 0
#if (ENABLE_T_C_COMBO )
    if( enUiInputSourceType == UI_INPUT_SOURCE_DVBC )
        msAPI_DTV_Comm_Set_DVBTorCType(TRUE);
    else
        msAPI_DTV_Comm_Set_DVBTorCType(FALSE);
#endif
#else
  #if (ENABLE_DVB)
    if( enUiInputSourceType == UI_INPUT_SOURCE_DVBC )
        msAPI_DTV_Comm_Set_DVBTorCType(TRUE);
    else if( enUiInputSourceType == UI_INPUT_SOURCE_DVBT )
        msAPI_DTV_Comm_Set_DVBTorCType(FALSE);
  #endif
#endif

    DEBUG_CHG_SRC_TIME2();

    //_MApp_ChangeSrc_Init_Tuner_Demod(enUiInputSourceType); //gchen  @ 20171218

    DEBUG_CHG_SRC_TIME2();

#if(ENABLE_MHL == ENABLE)
    msAPI_MHL_SourceChange(enUiInputSourceType);
    DEBUG_CHG_SRC_TIME2();
#endif



#if( ENABLE_DTV)
    _MApp_ChangeSrc_Reset_DTV_APP(bOldSrcIsDTV, bNewSrcIsDTV);
#endif

}

//========================================
// Switch source step:
//  enable blue screen
//  Turn off special function(maybe turn on later)
//  Destroy pre-source
//  setup system variable for input_source
//  setup driver/api/app for new source
//==========================================

//*************************************************************************
//Function name:    MApp_InputSource_SwitchSource
//Passing parameter:    U8 u8InputSrc: input source type
//Return parameter:     none
//Description:      change input source
//*************************************************************************
void MApp_InputSource_SwitchSource( E_UI_INPUT_SOURCE enUiInputSourceType,
                                               SCALER_WIN eWindow )
{
    XC_MUX_PATH_INFO PathInfo;
    S16 s16PathId;

    INPUT_SOURCE_TYPE_t u8PreCVBS1OutSource = INPUT_SOURCE_NONE;
    INPUT_SOURCE_TYPE_t u8NewCVBS1OutSource = INPUT_SOURCE_NONE;

#if (ENABLE_CVBSOUT_2)
    INPUT_SOURCE_TYPE_t u8PreCVBS2OutSource = INPUT_SOURCE_NONE;
    INPUT_SOURCE_TYPE_t u8NewCVBS2OutSource = INPUT_SOURCE_NONE;
#endif

    static E_UI_INPUT_SOURCE _s_eOldUiInputSourceType = UI_INPUT_SOURCE_NONE;

    INPUT_SOURCE_TYPE_t eOldInputSrc = SYS_INPUT_SOURCE_TYPE(eWindow);
    INPUT_SOURCE_TYPE_t eNewInputSrc = INPUT_SOURCE_NONE;

    // For CEC usage - sending routing change or active source when switching source
#if ENABLE_CEC
    INPUT_SOURCE_TYPE_t pre_srctype = INPUT_SOURCE_NONE, cur_srctype = INPUT_SOURCE_NONE;
#endif

#if ENABLE_DTV
  #if ENABLE_CI
    //for internal DEMOD init
    EN_DEMODULATOR_TYPE enPreDemodType =  msAPI_Demod_GetCurrentDemodType();
  #endif
#endif

    static BOOLEAN bIsCvbsOut1IsAtv = FALSE;
#if (ENABLE_CVBSOUT_2)
    static BOOLEAN bIsCvbsOut2IsAtv = FALSE;
#endif



    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););


#if(DEBUG_CHG_SRC_TIME)
    //printf("SW-1 %u\n", g_Debug_u32Time_ChangeSrc);
    msDebug_PrintChgSrcTime("SwitchSource Start");
#endif


    //PRINT_CURRENT_LINE();
    msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW);

    printf(" >> MApp_InputSource_SwitchSource(%u[%s]) at %u\n", enUiInputSourceType, MApp_InputSrc_Get_UiInputSrcName(enUiInputSourceType), MsOS_GetSystemTime());
    printf(" OldUiSrc=%u(%s), eOldInputSrc=%u\n", _s_eOldUiInputSourceType, MApp_InputSrc_Get_UiInputSrcName(_s_eOldUiInputSourceType), eOldInputSrc);


// currently no need
#if 0//(ENABLE_ATSC)
    if( enUiInputSourceType == UI_INPUT_SOURCE_TV )
    {
        if( MApp_ChanProc_Is_CurChannelAtv() )
        {
            enUiInputSourceType = UI_INPUT_SOURCE_ATV;
            printf("\nWarning: TV --> ATV \n");
        }
        else
        {
            enUiInputSourceType = UI_INPUT_SOURCE_ATSC;
            printf("\nWarning: TV --> DTV \n");
        }
    }
#endif

    //INPUTSOURCE_DBG( printf("MApp_InputSource_SwitchSource(UiSrcTyp=%u, win=%u)\n", enUiInputSourceType, eWindow); );
    INPUTSOURCE_DBG( printf(" UI_INPUT_SOURCE_TYPE=%u\n", UI_INPUT_SOURCE_TYPE); );
    INPUTSOURCE_DBG( printf(" SYS_INPUT_SOURCE_TYPE(eWindow)=%u\n", SYS_INPUT_SOURCE_TYPE(eWindow)); );

    msDebug_ANSI_AllAttrOffText();

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("SwitchSource start");
#endif

    DEBUG_CHG_SRC_TIME2();

    // Enable blue screen, Turn off some function
    _MApp_ChangeSrc_Step_01_TurnOffFunction(enUiInputSourceType, eWindow);

    DEBUG_CHG_SRC_TIME2();

    // Destroy old source: deinit driver/api for old source
    _MApp_ChangeSrc_Step_02_DestroyPreSource(_s_eOldUiInputSourceType, enUiInputSourceType, eWindow);

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("DestroyPreSource done");
#endif

    DEBUG_CHG_SRC_TIME2();


#if (ENABLE_FM_RADIO)
    if (msAPI_Scaler_GetScreenMute(eWindow) & E_SCREEN_MUTE_BY_FMRADIO)
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_FMRADIO, DISABLE, 0, MAIN_WINDOW);
#endif

#if (ENABLE_SUBTITLE)
 #if (SUBTITLE_WITH_OSD)
    //if( (enUiInputSourceType<=UI_INPUT_SOURCE_DTMB) )
    if ( MApp_InputSrc_Is_UiInputSrcTypeDtv(enUiInputSourceType) )
    {
        u32SubtitleMainProcTimeOut = msAPI_Timer_GetTime0();
    }
 #endif
#endif


#if (ENABLE_PIP)
    if( !IsPIPSupported() )
    {
        if (eWindow == SUB_WINDOW)
        {
            ASSERT("No Sub Window while DISABLE PIP");
        }
    }
#endif

#if (MirrorEnable)
    if( (IsSrcTypeStorage(eOldInputSrc)||IsSrcTypeDTV(eOldInputSrc)) )
    {
        MApp_MVOP_SetMirrorMode(DISABLE);
    }
#endif

    DEBUG_CHG_SRC_TIME2();

    /////////////////////////////////////////
    //Destroy path which destination is eWindow
    /////////////////////////////////////////
    {
        if( eOldInputSrc < INPUT_SOURCE_NUM )
        {
            E_DEST_TYPE eDelPathDest = (eWindow==SUB_WINDOW)? OUTPUT_SCALER_SUB_WINDOW:OUTPUT_SCALER_MAIN_WINDOW;
            SIGNAL_PATH_DBG( printf("==>Delete Main Path, SRC =%u, Dest=%u\n", eOldInputSrc, eDelPathDest); );
            if( MApi_XC_Mux_DeletePath(eOldInputSrc, eDelPathDest) == -1 )
            {
                //SIGNAL_PATH_DBG(printf("\r\n Delete path fail src =%d ",SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) ));
                printf("\n Delete path fail! src =%u \n", eOldInputSrc );
            }
            else
            {
                SIGNAL_PATH_DBG( printf(" Delete path success src =%d dst=%d ", eOldInputSrc, OUTPUT_SCALER_MAIN_WINDOW ));
            }
        }

        // Please NOTE: SYS_INPUT_SOURCE_TYPE is equal to previous input source
        // before MApp_InputSource_SetSystemmInfo called. Clear VE here.
        // This part should be finetuned by APP level when PIP involved.
    #if(ENABLE_PIP)
      #if (FORCE_ALL_OUTPUT_THROUGH_VE != ENABLE)
        if(_gbPIPCVBSOutEnable ==1)
        {
            u8PreCVBS1OutSource = INPUT_SOURCE_NONE;
            #if (ENABLE_CVBSOUT_2)
            u8PreCVBS2OutSource = INPUT_SOURCE_NONE;
            #endif
        }
        else
        {
            u8PreCVBS1OutSource = _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS1_OUTPUT_Tbl, eOldInputSrc);
            #if (ENABLE_CVBSOUT_2)
            u8PreCVBS2OutSource = _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS2_OUTPUT_Tbl, eOldInputSrc);
            #endif
        }
      #endif
    #else

      #if 1//(!((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE)))
        u8PreCVBS1OutSource = _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS1_OUTPUT_Tbl, eOldInputSrc);
        #if (ENABLE_CVBSOUT_2)
        u8PreCVBS2OutSource = _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS2_OUTPUT_Tbl, eOldInputSrc);
        #endif
      #endif
    #endif


        // Power off (power saving, must after path created)
    #if (ENABLE_PWS)
        /*****************************************************************************
        Power saving do IP power on/off, so the code flow related to IP power on/off
        can't be arbitraraily change, like the ADC table (MApi_XC_Mux_CreatePath)
        ******************************************************************************/
        if( eOldInputSrc != INPUT_SOURCE_NONE )
        {
            DEBUG_CVBS_OUT( printf("PWS.DEL.CurSrc(0x%X)\n", _MAPP_InputSource_Source2PWSSource( eOldInputSrc, _s_eOldUiInputSourceType ) ); );
            MDrv_PWS_HandleSource(PWS_DEL_SOURCE, _MAPP_InputSource_Source2PWSSource( eOldInputSrc, _s_eOldUiInputSourceType ), PWS_FULL);
        }
    #endif
    }

    DEBUG_CHG_SRC_TIME2();

      // digital IP
#if ENABLE_DTV
      if ( IsSrcTypeDTV(eOldInputSrc) )
      {
          // exit DTV
     #if( ENABLE_DVB&&ENABLE_CI )
         if( msAPI_CI_CardDetect() )
         {
            //**-- Italy CI Certificate Start --**//
            MEMBER_SERVICETYPE bServiceType;
            WORD wCurrentPosition;

            bServiceType = msAPI_CM_GetCurrentServiceType();
            wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);

            msAPI_CI_SendEmptyPmt(msAPI_CM_GetService_ID(bServiceType, wCurrentPosition), MApp_SI_Get_PSISIVersion(E_VER_PMT));
        }
        //**-- Italy CI Certificate End --**//
    #endif

        DEBUG_CHG_SRC_TIME2();

    #if MHEG5_ENABLE
        if(msAPI_MHEG5_GetBinStatus() == TRUE)
        {
        // Disable Aeon for Non-DTV Mode
        #if (MHEG5_WITH_OSD)
            //if ( msAPI_MHEG5_checkGoBackMHEG5())
            {
                MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_WAIT);
            }
        #endif

            msAPI_COPRO_Disable();
        }
    #endif

        DEBUG_CHG_SRC_TIME2();

        //msAPI_VID_Command(MSAPI_VID_STOP);

      }
      else
#endif
        //if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            if (IsSrcTypeDigitalVD(eOldInputSrc))
            {
                if (IsSrcTypeATV(eOldInputSrc))
                {
                #if( ENABLE_DTV)
                  #if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
                    //if(enUiInputSourceType <= UI_INPUT_SOURCE_DTMB) //Be disable VIF clock only on DTV(dest.) for CVBS out ATV issue 20100426EL
                    if ( MApp_InputSrc_Is_UiInputSrcTypeDtv(enUiInputSourceType) )
                    {
                        MDrv_VIF_SetClock(DISABLE); //At ATV,change to another , close VIF
                    }
                  #endif
                #endif
                }
            }

        #if (ENABLE_PIP)
            if((eWindow == MAIN_WINDOW &&(IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            ||(eWindow == SUB_WINDOW &&(IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))))
            {
               //printf("\r\n main or sub window is VD source ");
            }
            else
        #endif
            {
                msAPI_AVD_Exit();
            }

            DEBUG_CHG_SRC_TIME2();

    #if(ENABLE_DTV)
         #if (ENABLE_PIP)
            if((eWindow == MAIN_WINDOW &&(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
            ||(eWindow == SUB_WINDOW &&(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))))
            {
               //printf("\r\n main or sub window is DTV/ATV source ");
            }
            else
         #endif
            {
                msAPI_Demodulator_Exit();
            }
    #endif
        }

    DEBUG_CHG_SRC_TIME2();

    //////////////////////////////////////////////
    // Mapping UI source to driver supported source
    //////////////////////////////////////////////

  #if ENABLE_CEC
    if( eWindow == MAIN_WINDOW )
    {
        pre_srctype = stSystemInfo[MAIN_WINDOW].enInputSourceType;
    }
  #endif

    //=============================================================
    //Clear previous input source flag
    //_MApp_InputSource_ClearSysInputSourceFlag(eWindow);
    MApp_InputSource_SetSystemmInfo( enUiInputSourceType, &stSystemInfo[eWindow] , &g_enDataInputSourceType[eWindow]);
    _MApp_InputSource_SetSysInputSourceFlag(eWindow,enUiInputSourceType);
    eNewInputSrc = stSystemInfo[eWindow].enInputSourceType;
    printf(" eNewInputSrc=%u\n", eNewInputSrc);
    //=============================================================


    // Starting do something for new source...
    DEBUG_CHG_SRC_TIME2();


    // Setup driver/api for new source:
    _MApp_ChangeSrc_Step_03_SetupNewSource( _s_eOldUiInputSourceType, enUiInputSourceType, eWindow);


    DEBUG_CHG_SRC_TIME2();

#if ENABLE_DVB
    MApp_SILogoSetup();
#endif


#if(ENABLE_S2)
    if(IsS2InUse())
    {
    #if(FRONTEND_DEMOD_S2_TYPE == DEMOD_AVL6211)
        if (msAPI_CI_CardDetect())
            MDrv_CofdmDmd_SetTsSerial(0,1,1);
        else
            MDrv_CofdmDmd_SetTsSerial(0,0,1);
    #endif
        MsOS_DelayTask(100);
        Int_DigiTuner_Tp_Sat();
    }
    else
    {
    #if(FRONTEND_DEMOD_S2_TYPE == DEMOD_AVL6211)
        MDrv_CofdmDmd_SetTsSerial(0,0,0);
    #endif
        //SWITCH_TO_DBVT();
    }

  #if(!ENABLE_API_DTV_SYSTEM_2015)
    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        msAPI_CM_InitDTVDataManager();
        MApp_Init_UIVariable();
    }
  #endif
#endif

#if 0//(ENABLE_API_DTV_SYSTEM_2015 && ENABLE_DVB)
    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        msAPI_CM_InitDTVDataManager_CurSource();
    }
#endif

#if(ENABLE_DVB && ENABLE_CHPROC_ORDINAL_LIST)
  #if( !ENABLE_SBTVD_BRAZIL_CM_APP )
    if( IsDVBInUse()||IsATVInUse() )
    {
        msAPI_CHPROC_CM_InitOridial();
    }
  #endif
#endif

    DEBUG_CHG_SRC_TIME2();

  #if(ENABLE_PIP)
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        u8NewCVBS1OutSource = INPUT_SOURCE_NONE;
      #if (ENABLE_CVBSOUT_2)
        u8NewCVBS2OutSource = INPUT_SOURCE_NONE;
      #endif
        _gbPIPCVBSOutEnable =1;
    }
    else
    {
        u8NewCVBS1OutSource = _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS1_OUTPUT_Tbl, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
      #if (ENABLE_CVBSOUT_2)
        u8NewCVBS2OutSource = _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS2_OUTPUT_Tbl, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
      #endif
        _gbPIPCVBSOutEnable=0;
    }
  #else
    u8NewCVBS1OutSource = _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS1_OUTPUT_Tbl, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
    DEBUG_CVBS_OUT(printf("u8NewCVBS1OutSource=%u\n", u8NewCVBS1OutSource));

    #if (ENABLE_CVBSOUT_2)
    u8NewCVBS2OutSource = _MAPP_GET_CVBSOUT_VIDEO_SOURCE(CVBS2_OUTPUT_Tbl, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
    DEBUG_CVBS_OUT(printf("u8NewCVBS2OutSource=%u\n", u8NewCVBS2OutSource));
    #endif
  #endif

  #if (ENABLE_PIP)
    if(IsPIPSupported())
  #endif
    {
        //used for main / sub window swap
        if(enUiInputSourceType == UI_INPUT_SOURCE_NONE)
        {
            //Close sub window
            if(eWindow == SUB_WINDOW)
            {
                MApi_XC_DisableSubWindow();
            }
            return;
        }
    }

    DEBUG_CHG_SRC_TIME2();

#if 1//(!((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE)))
    // Delete cvbs path...
    if((u8PreCVBS1OutSource != u8NewCVBS1OutSource)&&(u8PreCVBS1OutSource!= INPUT_SOURCE_NONE))
    {
        if( MApi_XC_Mux_DeletePath(u8PreCVBS1OutSource,OUTPUT_CVBS1) == -1 )
        {
            printf(" delete CVBS1 path fail src = %d  dest = %d \n", u8PreCVBS1OutSource, OUTPUT_CVBS1);
        }
        else
        {
            SIGNAL_PATH_DBG(printf(" delete CVBS1 path success src = %d  dest = %d \n",u8PreCVBS1OutSource ,OUTPUT_CVBS1));
        }
        DEBUG_CHG_SRC_TIME2();
        bIsCvbsOut1IsAtv = FALSE;
        msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN, SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS1);
    }
  #if (ENABLE_CVBSOUT_2)
    if((u8PreCVBS2OutSource != u8NewCVBS2OutSource)&&(u8PreCVBS2OutSource!= INPUT_SOURCE_NONE))
    {
        if( MApi_XC_Mux_DeletePath(u8PreCVBS2OutSource,OUTPUT_CVBS2) == -1 )
        {
            printf(" delete CVBS2 path fail src = %d  dest = %d \n",u8PreCVBS2OutSource ,OUTPUT_CVBS2);
        }
        else
        {
            SIGNAL_PATH_DBG(printf(" delete CVBS2 path success src = %d  dest = %d \n",u8PreCVBS2OutSource ,OUTPUT_CVBS2));
        }
        bIsCvbsOut2IsAtv = FALSE;
        msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN, SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS2);
    }
  #endif

    DEBUG_CHG_SRC_TIME2();

    // Turn off VE first in switch source, turn it on at next necessary places
    msAPI_VE_Exit();
#endif //ALL_SOURCE_OUTPUT_THROUGH_VE

    DEBUG_CHG_SRC_TIME2();

    if( IsSrcTypeAnalog(SYS_INPUT_SOURCE_TYPE(eWindow))
      ||IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow))
      ||IsSrcTypeDVI(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        MApp_InputSource_InitModeVariables(eWindow); // initialize mode variables

        #if (ENABLE_HDMI_4K_2K&&ENABLE_6M40_4KX2K_PROCESS)
         if (MApi_XC_Mux_GetHDMIPort(SYS_INPUT_SOURCE_TYPE(eWindow))==INPUT_PORT_DVI0)
         {
            MDrv_HDCP_Enable(DISABLE);
            printf("MDrv_HDCP_Enable(DISABLE)!!!!!");
         }
         else
         {
            MDrv_HDCP_Enable(ENABLE);
            printf("MDrv_HDCP_Enable(ENABLE) !!!!!");
         }
       #endif
    }

    DEBUG_CHG_SRC_TIME2();

#if( ENABLE_DTV )
    //if (enUiInputSourceType <= UI_INPUT_SOURCE_DTMB)
    if ( MApp_InputSrc_Is_UiInputSrcTypeDtv(enUiInputSourceType) )
    {
        MDrv_IFDM_SetIF(IF_DIGITAL_MODE);
    }
#endif

    DEBUG_CHG_SRC_TIME2();

  #if ENABLE_CEC
    if( eWindow == MAIN_WINDOW )
    {
        cur_srctype = stSystemInfo[MAIN_WINDOW].enInputSourceType;
    }
  #endif


    DEBUG_CHG_SRC_TIME2();

#if ( ENABLE_PWS)

    DEBUG_CVBS_OUT( printf("PWS.Add. CurSrc(0x%X)\n", _MAPP_InputSource_Source2PWSSource( stSystemInfo[eWindow].enInputSourceType, enUiInputSourceType )); );
    MDrv_PWS_HandleSource(PWS_ADD_SOURCE, _MAPP_InputSource_Source2PWSSource( stSystemInfo[eWindow].enInputSourceType, enUiInputSourceType ),PWS_FULL);

    if( (u8NewCVBS1OutSource != INPUT_SOURCE_NONE)
     #if (ENABLE_CVBSOUT_2)
      ||(u8NewCVBS2OutSource != INPUT_SOURCE_NONE)
     #endif
      )
    {
        DEBUG_CVBS_OUT( printf("PWS.Add. _CVBSOi_(0x%X)\n", _CVBSOi_); );
        MDrv_PWS_HandleSource(PWS_ADD_SOURCE, _CVBSOi_,PWS_FULL);

        if( (u8NewCVBS1OutSource == INPUT_SOURCE_TV)
     #if (ENABLE_CVBSOUT_2)
          ||(u8NewCVBS2OutSource == INPUT_SOURCE_TV)
     #endif
          )
        {
            DEBUG_CVBS_OUT( printf("PWS.Add. _ATV_VIF_(0x%X)\n", _ATV_VIF_); );
            MDrv_PWS_HandleSource(PWS_ADD_SOURCE,_ATV_VIF_,PWS_FULL);
        }
    }
    else
    {
        DEBUG_CVBS_OUT( printf("PWS.DEL._CVBSOi_(0x%X)\n", _CVBSOi_); );
        MDrv_PWS_HandleSource(PWS_DEL_SOURCE, _CVBSOi_,PWS_FULL);
    }
#endif

    DEBUG_CHG_SRC_TIME2();

    //////////////////////////////////////////////
    // Create Path
    // InputSource -> Scaler Main/Sub Window
    //////////////////////////////////////////////

  #if(ENABLE_DTV)
    if(IsSrcTypeDTV(stSystemInfo[eWindow].enInputSourceType))
    {
        PathInfo.path_thread = MApp_DTV_Handler;
    }
    else
  #endif
    if(IsSrcTypeAnalog(stSystemInfo[eWindow].enInputSourceType) || IsSrcTypeHDMI(stSystemInfo[eWindow].enInputSourceType))
    {
        if ( eWindow == MAIN_WINDOW )
        {
            PathInfo.path_thread = MApp_PC_MainWin_Handler;
        }
        #if (ENABLE_PIP)
        else
        {
            PathInfo.path_thread = MApp_PC_SubWin_Handler;
        }
        #endif
        //printf("path_thread=MApp_PC_MainWin_Handler()\n");
    }
  #if ENABLE_DMP
    else if (IsSrcTypeStorage(stSystemInfo[eWindow].enInputSourceType))
    {
        PathInfo.path_thread = MApp_Storage_Handler;
    }
  #endif
    else // ATV
    {
        PathInfo.path_thread = MApp_ATV_Handler;
        //printf("path_thread=MApp_ATV_Handler()\n");
    }

    PathInfo.Path_Type = PATH_TYPE_SYNCHRONOUS;
    {
        PathInfo.src = SYS_INPUT_SOURCE_TYPE(eWindow);
    }

    if ( eWindow == MAIN_WINDOW )
    {
        PathInfo.dest = OUTPUT_SCALER_MAIN_WINDOW;
        if(IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            //Since MM has its own flow for below event, so skip loading handler here
            PathInfo.SyncEventHandler = NULL;
            PathInfo.DestOnOff_Event_Handler = NULL;
        }
        else
        {
            PathInfo.SyncEventHandler = MApp_Scaler_MainWindowSyncEventHandler;
            PathInfo.DestOnOff_Event_Handler = MApp_Scaler_MainWindowOnOffEventHandler;
        }
        PathInfo.dest_periodic_handler = MApp_Scaler_MainWindowPeriodicHandler;
    }
    #if (ENABLE_PIP)
    else
    {
        PathInfo.dest = OUTPUT_SCALER_SUB_WINDOW;
        if(IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            //Since MM has its own flow for below event, so skip loading handler here
            PathInfo.SyncEventHandler = NULL;
            PathInfo.DestOnOff_Event_Handler = NULL;
        }
        else
        {
            PathInfo.SyncEventHandler = MApp_Scaler_SubWindowSyncEventHandler;
            PathInfo.DestOnOff_Event_Handler = MApp_Scaler_SubWindowOnOffEventHandler;
        }
        PathInfo.dest_periodic_handler = MApp_Scaler_SubWindowPeriodicHandler;
    }
    #endif

/*****************************************************************************
Power saving do IP power on/off, so the code flow related to IP power on/off
can't be arbitraraily change, like the ADC table (MApi_XC_Mux_CreatePath)
******************************************************************************/

    s16PathId = MApi_XC_Mux_CreatePath( &PathInfo, sizeof(XC_MUX_PATH_INFO) );
    if (s16PathId == -1)
    {
        printf(" Create path fail src = %d  dest = %d, your structure has wrong size with library \n", PathInfo.src, PathInfo.dest);
    }
    else
    {
        SIGNAL_PATH_DBG(printf("\r\n create path success src = %d dest = %d ", PathInfo.src, PathInfo.dest));
        MApi_XC_Mux_EnablePath( (U16)s16PathId );
    }

    // Create CVBS out path...
#if 1//(FORCE_ALL_OUTPUT_THROUGH_VE != ENABLE)
    if( (u8NewCVBS1OutSource != INPUT_SOURCE_NONE)&&(u8NewCVBS1OutSource != u8PreCVBS1OutSource) )
    {
        PathInfo.Path_Type = PATH_TYPE_SYNCHRONOUS;
        PathInfo.src = u8NewCVBS1OutSource;
        PathInfo.dest = OUTPUT_CVBS1;

    #if(ENABLE_DTV)
        if (IsSrcTypeDTV(u8NewCVBS1OutSource))
        {
            PathInfo.path_thread = MApp_DTV_Handler;
        }
        else
    #endif
        if (IsSrcTypeDigitalVD(u8NewCVBS1OutSource))
        {
            PathInfo.path_thread = MApp_ATV_Handler;
            msAPI_Tuner_SetCurrentAudioStandard();
        }
    #if(ENABLE_DMP)
        else if(IsSrcTypeStorage(u8NewCVBS1OutSource))
        {
            PathInfo.path_thread = MApp_Storage_Handler;
        }
    #endif
        PathInfo.SyncEventHandler = MApp_Scaler_CVBS1OutSyncEventHandler;
        PathInfo.DestOnOff_Event_Handler = MApp_Scaler_CVBS1OutOnOffEventHandler;
        PathInfo.dest_periodic_handler = NULL;

        s16PathId = MApi_XC_Mux_CreatePath(&PathInfo, sizeof(XC_MUX_PATH_INFO) );

        if (s16PathId == -1)
        {
            printf(" Create CVBS1 path fail src = %d  dest = %d \n",PathInfo.src ,PathInfo.dest );
        }
        else
        {
            SIGNAL_PATH_DBG(printf(" Create CVBS1 path success src = %d  dest = %d \n",PathInfo.src ,PathInfo.dest ));
            MApi_XC_Mux_EnablePath( (U16)s16PathId );
            if(u8NewCVBS1OutSource == INPUT_SOURCE_TV)
            {
                bIsCvbsOut1IsAtv = TRUE;
            }
        }
    }

 #if (ENABLE_CVBSOUT_2)
    // Create CVBS out path2
    if((u8NewCVBS2OutSource != INPUT_SOURCE_NONE)&&(u8NewCVBS2OutSource != u8PreCVBS2OutSource))
    {
        PathInfo.Path_Type = PATH_TYPE_SYNCHRONOUS;
        PathInfo.src = u8NewCVBS2OutSource;
        PathInfo.dest = OUTPUT_CVBS2;

      #if(ENABLE_DTV)
        if (IsSrcTypeDTV(u8NewCVBS2OutSource))
        {
            PathInfo.path_thread = MApp_DTV_Handler;
        }
        else
      #endif
        if (IsSrcTypeDigitalVD(u8NewCVBS2OutSource))
        {
            PathInfo.path_thread = MApp_ATV_Handler;
        }
        else if(IsSrcTypeStorage(u8NewCVBS2OutSource))
        {
            PathInfo.path_thread = MApp_Storage_Handler;
        }
        PathInfo.SyncEventHandler = MApp_Scaler_CVBS2OutSyncEventHandler;
        PathInfo.DestOnOff_Event_Handler = MApp_Scaler_CVBS2OutOnOffEventHandler;
        PathInfo.dest_periodic_handler = NULL;

        s16PathId = MApi_XC_Mux_CreatePath(&PathInfo, sizeof(XC_MUX_PATH_INFO) );

        if (s16PathId == -1)
        {
            printf(" Create CVBS2 path fail src = %d  dest = %d \n",PathInfo.src ,PathInfo.dest );
        }
        else
        {
            MApi_XC_Mux_EnablePath( (U16)s16PathId );
            SIGNAL_PATH_DBG(printf(" Create CVBS2 path success src = %d  dest = %d \n",PathInfo.src ,PathInfo.dest ));
            if(u8NewCVBS2OutSource == INPUT_SOURCE_TV)
            {
                bIsCvbsOut2IsAtv = TRUE;
            }
        }
    }
  #endif // #if (ENABLE_CVBSOUT_2)

#endif //(ALL_SOURCE_OUTPUT_THROUGH_VE != ENABLE)

    DEBUG_CHG_SRC_TIME2();

//==================================================
#if (ENABLE_PIP)
    if( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
      ||IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
#else
    if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
#endif
    {
        eVifStatus = E_VIF_ON_ATV_DISPLAY;
        DEBUG_CVBS_OUT( printf("eVifStatus = E_VIF_ON_ATV_DISPLAY\n") );
    }
  #if (ENABLE_CVBSOUT_2)
    else if(bIsCvbsOut1IsAtv || bIsCvbsOut2IsAtv)
  #else
    else if(bIsCvbsOut1IsAtv)
  #endif
    {
        eVifStatus = E_VIF_ON_ATV_CVBSOUT;
        DEBUG_CVBS_OUT( printf("eVifStatus = E_VIF_ON_ATV_CVBSOUT\n") );
    }
    else
    {
        eVifStatus = E_VIF_NOT_NECESSARY;
        DEBUG_CVBS_OUT( printf("eVifStatus = E_VIF_NOT_NECESSARY\n") );
    }



    if ( IsSrcTypeAnalog(SYS_INPUT_SOURCE_TYPE(eWindow))
       ||IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow))
       ||IsSrcTypeDVI(SYS_INPUT_SOURCE_TYPE(eWindow)) )
    {
        MApp_PCMode_Reset(eWindow);
    }

  #if (ENABLE_DTV)
    if ( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)) )
    {
        //msAPI_Tuner_Initialization();
        //power on tuner and set tri-state on
        //msAPI_Tuner_Set_DemodPower( ENABLE );
        //msAPI_Tuner_InitCurrentTPSetting();

    }
#if(ENABLE_S2)
    else if ( !(IsDTVInUse()||IsS2InUse()) )
#else
    else if (!IsDTVInUse())
#endif
    {
      #if MHEG5_ENABLE
        if(msAPI_MHEG5_GetBinStatus() == TRUE)
        {
            // Disable Aeon for Non-DTV Mode
          #if (MHEG5_WITH_OSD)
            //if ( msAPI_MHEG5_checkGoBackMHEG5())
            {
                MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_WAIT);
            }
          #endif

            msAPI_COPRO_Disable();
        }
      #endif
        //power off tuner and tri-state off
        //msAPI_Tuner_Set_DemodPower( DISABLE );
        //TU_RESET_N_On();
    }
  #endif

    DEBUG_CHG_SRC_TIME2();

    if (IsATVInUse()||IsAVInUse()||IsScartInUse())
    {
        MDrv_AVD_Set3dComb( ENABLE );
    }
    else
    {
        MDrv_AVD_Set3dComb( DISABLE );
    }

    DEBUG_CHG_SRC_TIME2();

  #if ( (EEPROM_DB_STORAGE != EEPROM_SAVE_ALL) && (!DB_IN_NAND) )
    while (FALSE == MDrv_FLASH_CheckWriteDone());
  #endif

    DEBUG_CHG_SRC_TIME2();

  #if (ENABLE_PIP)
    if( (MApp_Get_PIPMode() == EN_PIP_MODE_OFF) || UI_IS_AUDIO_SOURCE_IN(eWindow))
  #endif
    {
        MApp_InputSource_ChangeAudioSource( SYS_INPUT_SOURCE_TYPE(eWindow), enUiInputSourceType);
    }

    DEBUG_CHG_SRC_TIME2();

    MApp_CheckBlockProgramme();

    DEBUG_CHG_SRC_TIME2();

#if ENABLE_ATSC
    /* if switch to analog source, caption must bet set to 608 */
    //MApp_ClosedCaption_DetectCCMode();

    /* init V-Chip while switching to AV or SV
     TV and DTV will init in enable channel each time */

    if ( IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(eWindow))
       ||IsSrcTypeSV(SYS_INPUT_SOURCE_TYPE(eWindow))
      #ifndef DISABLE_COMPONENT_VBI
       ||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(eWindow))
      #endif
       )
    {
    #if(ENABLE_ATSC_VCHIP)
        MApp_VChip_Init();
    #endif
        MApp_CC_Initialize();
        MApp_ClosedCaption_GetUserCmd();
        fVChipPassWordEntered= FALSE;
        //cc: Stop CC engine and let the system reinitialized, Let this part in parrell task to check
    }
    msAPI_CC_Reset();
#endif

#if ENABLE_ISDB_ATV_VCHIP
    if(IS_SBTVD_APP && IsVBISrcInUse())
    {
        MApp_VChip_Init();
        msAPI_CC_VchipRateReset();
        fVChipPassWordEntered = FALSE;
    }
#endif

    // For CEC usage - sending routing change or active source when switching source
    // - Routing change: HDMI -> HDMI, non-HDMI -> HDMI
    // - Active source   : HDMI -> non-HDMI
  #if ENABLE_CEC
    //printf("pre_srctype=%u,cur_srctype=%u\n", pre_srctype, cur_srctype);
    MApp_CEC_SetMyPhyAddr(pre_srctype, cur_srctype);
    msAPI_CEC_RoutingControl_SourceChange(pre_srctype, cur_srctype);
  #endif

    DEBUG_CHG_SRC_TIME2();
/*****************************************************************************
Power saving do IP power on/off, so the code flow related to IP power on/off
can't be arbitraraily change, like the ADC table (MApi_XC_Mux_CreatePath)
******************************************************************************/
    MApp_InputSource_SetInputSource( eWindow, &stSystemInfo[eWindow] );

    DEBUG_CHG_SRC_TIME2();

/***************************************************
power saving do IP power on/off, it causes Scaler IP state machine unstable if not resetting it.
so it has to be called before Scaler set source type.
let Scaler set source type to do the resetting job
****************************************************/
    msAPI_Scaler_SetSourceType( stSystemInfo[eWindow].enInputSourceType , eWindow);

    DEBUG_CHG_SRC_TIME2();

#if( CONTROL_DNR_BUF_RULE_2015 )

    MApi_XC_SetupFrameBuffer();

#else

#if 0//( (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) && ((MEMORY_MAP == MMAP_64MB) || (defined(SCALER_DNR_BUF_PREV_ADR))) ) //Brazil 64MB model
    if ( IsSrcTypeStorage(stSystemInfo[eWindow].enInputSourceType) )
    {
        MApi_XC_SetFrameBufferAddress( ((SCALER_DNR_BUF_DTV_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_DTV_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_DTV_ADR)), SCALER_DNR_BUF_DTV_LEN, eWindow);
    }
  #if (defined SUPPORT_MPEG2_SD_ONLY || defined SUPPORT_FRANCE_H264_BY_1DDR || (defined AUSTRALIA && (MEMORY_MAP <= MMAP_64MB)))
    else if ( IsSrcTypeDTV(stSystemInfo[eWindow].enInputSourceType) )
    {
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_DTV_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_DTV_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_DTV_ADR)), SCALER_DNR_BUF_DTV_LEN, eWindow);
    }
  #endif
    else
    {
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, eWindow);
    }

#else

  #if ((MEMORY_MAP <= MMAP_64MB) || (defined(SCALER_DNR_BUF_PREV_ADR)))   //ATV_MM 64M
    if ( IsSrcTypeATV(stSystemInfo[eWindow].enInputSourceType) )
    {
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)),SCALER_DNR_BUF_LEN, eWindow);

    }
   #if (defined SUPPORT_MPEG2_SD_ONLY || (defined AUSTRALIA && (MEMORY_MAP <= MMAP_64MB)))
    else if ( IsSrcTypeDTV(stSystemInfo[eWindow].enInputSourceType) )
    {
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_DTV_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_DTV_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_DTV_ADR)), SCALER_DNR_BUF_DTV_LEN, eWindow);
    }
   #endif
    else
    {
    #if (DTV_USE_FBL == 0)
        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
        #if( defined( SCALER_DNR_BUF_DTV_ADR ) && (SCALER_DNR_BUF_DTV_LEN > 0) )
             MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_DTV_MEMORY_TYPE& MIU1) ? (SCALER_DNR_BUF_DTV_ADR| MIU_INTERVAL) : (SCALER_DNR_BUF_DTV_ADR)), SCALER_DNR_BUF_DTV_LEN, eWindow);
        #else
             MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, MAIN_WINDOW);
        #endif
        }
        else
    #endif
        {
            MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, MAIN_WINDOW);
        }
        // printf("[SwitchSource]Set FB = %X %X\n", ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN);
    }
  #endif
#endif

#endif

    DEBUG_CHG_SRC_TIME2();

    MApi_XC_EnableFrameBufferLess(DISABLE);


    // Init App-Scaler
    _MApp_ChangeSrc_Init_AppScaler(eWindow);


    MApp_Analog_NoSignal_ResetCount(eWindow);

    DEBUG_CHG_SRC_TIME2();

  #if ENABLE_DDCCI
    MDrv_DDC2BI_Set_StandardCallBack(MApp_DDC2BI_AlignControl);
    MDrv_DDC2BI_Set_CustomerCallBack(MApp_DDC2BI_FactoryAdjustment);
  #endif

#if ENABLE_TTX
    if(eWindow != SUB_WINDOW)
    {
        _MApp_ChangeSrc_Init_TTX();
    }
#endif  // ENABLE_TTX

    DEBUG_CHG_SRC_TIME2();

  #if ENABLE_DMP
  #if (ENABLE_PIP)
    if((eWindow == SUB_WINDOW &&(IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))))
    {
        //printf("\r\n main  is stotage source ");
    }
    else
  #endif
    //if ( gCurrentBinID != BIN_ID_CODE_AEON_FONT )
    {
        if (IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
            MApp_DMP_InitDMPStat();
            // here we restroe the UI_INPUT_SOURCE_TYPE because the dmp should not be an inputsource
            //UI_INPUT_SOURCE_TYPE = MApp_InputSource_GetRecordSource();
        #if( VD_PLAYER_IS_IN_CROP_CPU )
            msAPI_Aeon_ReInitial( BIN_ID_CODE_VDPLAYER );
        #endif
        }
    }
  #endif //MM_AEON_ENABLE

    DEBUG_CHG_SRC_TIME2();

  #if ENABLE_DBC
    MApi_XC_DLC_SetOnOff(ENABLE, MAIN_WINDOW);
    MApi_XC_Sys_DLC_DBC_OnOff(stGenSetting.g_SysSetting.fDCR);
  #endif

  #if (ENABLE_PIP)
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if(eWindow == SUB_WINDOW && enUiInputSourceType != UI_INPUT_SOURCE_NONE)
        {
            MS_WINDOW_TYPE stWinRect;
            if(MApp_InputSource_PIP_GetSubWinRect(&stWinRect))
            {
                //printf("Sub win rect = (%d, %d) w = %d, h = %d\n", stWinRect.x, stWinRect.y, stWinRect.width, stWinRect.height);
                MApi_XC_EnableSubWindow(&stWinRect);
            }
            else
            {
                printf("Failed to enable sub window!\n");
            }
        }
    }
  #endif

    DEBUG_CHG_SRC_TIME2();

  // digital IP
  #if ENABLE_DTV
    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))
    #if(ENABLE_ATSC)
      ||(IsATVInUse())
    #endif
      )
    {
        // Demod&Tsp path already set in _MApp_ChangeSrc_Init_Tuner_Demod()
    #if (ENABLE_CI)
        if( IsDVBInUse() )
        {
            //for internal DEMOD init
            //if ((ePreDemodMode != msAPI_Tuner_GetDemodMode()) && msAPI_CI_CardDetect())
            if((enPreDemodType != msAPI_Demod_GetCurrentDemodType()) && msAPI_CI_CardDetect())
            {
                msAPI_CI_ReInitial();
            }
        }
    #endif

        DEBUG_CHG_SRC_TIME2();

        //msAPI_Timer_Delayms(1);//add 1ms delay for demux inital to avoid info ui bug
    }
  #endif // ENABLE_DTV

    DEBUG_CHG_SRC_TIME2();

#if ENABLE_DVB
    //if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    if( IsDVBInUse() )
    {
    #if MHEG5_ENABLE
       msAPI_MHEG5_Bean_Init();
    #endif

    #if (ENABLE_DTV_EPG)
        TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
        U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
        MAPP_EPGDB_SetMaxDTVProgram(u16DTVProgramIndexTableArraySize);
        MApp_Epg_Init();
    #endif
    }
#endif

#if( ENABLE_ISDBT_AND_DVB )
    if( IsDVBInUse() )
    {
        MApp_PreInit_InitSILib();
    }
#endif

    DEBUG_CHG_SRC_TIME2();

  // Init VE to a display state to show out the "NO Signal" symbol and reconfig CVBS mux path
 #if((FORCE_ALL_OUTPUT_THROUGH_VE == ENABLE) && (ENABLE_OP2_TO_VE == ENABLE))
    msAPI_Scaler_SetCVBSMute(DISABLE, E_VE_MUTE_GEN, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), OUTPUT_CVBS1);
  #if (ENABLE_CVBSOUT_2)
    msAPI_Scaler_SetCVBSMute(DISABLE, E_VE_MUTE_GEN, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), OUTPUT_CVBS2);
  #endif
 #endif //(ALL_SOURCE_OUTPUT_THROUGH_VE == ENABLE)

    // turn on CVBS out for main src != cvbsout src
    if( u8NewCVBS1OutSource == INPUT_SOURCE_NONE )
    {
        msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN, INPUT_SOURCE_NONE, OUTPUT_CVBS1);
    }
    else
    {
        if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) != u8NewCVBS1OutSource )
        {
            msAPI_Scaler_SetCVBSMute(DISABLE, E_VE_MUTE_GEN, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), OUTPUT_CVBS1);
        }
    }
#if (ENABLE_CVBSOUT_2)
    if( u8NewCVBS2OutSource == INPUT_SOURCE_NONE )
    {
        msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN, INPUT_SOURCE_NONE, OUTPUT_CVBS2);
    }
    else
    {
        if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) != u8NewCVBS2OutSource )
        {
            msAPI_Scaler_SetCVBSMute(DISABLE, E_VE_MUTE_GEN, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), OUTPUT_CVBS2);
        }
    }
#endif

    DEBUG_CHG_SRC_TIME2();


#if ENABLE_DTV
  #if (ENABLE_DTV_CHCEK_USB_DELAY_2S)
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        g_u8DTVCheckUSBFlag = DTV_CHECK_USB_ENABLE;
        g_u8DTVCheckUSBFlag |= DTV_CHECK_USB_MONITOR_START_BIT;
        g_u8DTVCheckUSBFlag |= DTV_CHECK_USB_WAIT_BIT;
        u32CheckUSBMonitorTimer = msAPI_Timer_GetTime0();
    }
    else
    {
        g_u8DTVCheckUSBFlag = DTV_CHECK_USB_ENABLE;
    }
  #endif
#endif

#if ENABLE_3D_PROCESS
  #if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30)
    DB_3D_SETTING.en3DType = EN_3D_BYPASS;
    DB_3D_SETTING.en3DTo2DType= EN_3D_TO_2D_OFF;
    MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
    MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_NONE);
    DEBUG_CHG_SRC_TIME2();
  #endif
#endif

#if(ENABLE_OFFLINE_SIGNAL_DETECTION)
    MApi_XC_SetOffLineDetection(INPUT_SOURCE_NONE);
#endif

#if(NO_SIGNAL_AUTO_SHUTDOWN)
    MApp_NoSignalAutoSleep_Init();
#endif


#if (ENABLE_ATSC)
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock();
    MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);
#endif

#if(ENABLE_EWS)
    MApp_SI_ExitEWS();
    MApp_EWS_SetMsgCancelFlag(FALSE);
#endif

    _s_eOldUiInputSourceType = enUiInputSourceType;

    if(
#if (ENABLE_SCARTIN_PRESOURCE) && (INPUT_SCART_VIDEO_COUNT >= 1)
    #if (INPUT_SCART_VIDEO_COUNT >= 1)
       (enUiInputSourceType != UI_INPUT_SOURCE_SCART )
    #endif

    #if (INPUT_SCART_VIDEO_COUNT >= 2)
       ||(enUiInputSourceType != UI_INPUT_SOURCE_SCART2 )
    #endif
#else
    1
#endif
        )
    {
        if( (enUiInputSourceType != MApp_InputSrc_Get_PrevUiInputSrcType())
#if (ENABLE_DMP || BLOADER)
               &&(enUiInputSourceType != UI_INPUT_SOURCE_DMP )
#endif
            )

            MApp_InputSrc_Set_PrevUiInputSrcType(enUiInputSourceType);
    }
    else
    {
        ;
    }

    DEBUG_CHG_SRC_TIME2();

#if(DEBUG_CHG_SRC_TIME)
    //printf("SW-100 %u\n", g_Debug_u32Time_ChangeSrc);
    msDebug_PrintChgSrcTime("SwitchSource End");
#endif

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("SwitchSource end");
#endif

    INPUTSOURCE_DBG( printf("===== MApp_InputSource_SwitchSource end ===== \n"); );

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
}

//ZUI: moved from UiMenuFunc
void MApp_InputSource_ChangeInputSource_2(SCALER_WIN eWindow)
{
    //add for the caller: _MApp_ZUI_ACT_FactoryMenu_ChangeDataInputSource(E_DATA_INPUT_SOURCE)
    E_UI_INPUT_SOURCE source_type;

    INPUTSOURCE_DBG( printf("MApp_InputSource_ChangeInputSource_2(win=%u)\n", eWindow); );
    INPUTSOURCE_DBG( printf(" UI_INPUT_SOURCE_TYPE=%u(%s)\n", UI_INPUT_SOURCE_TYPE, MApp_InputSrc_Get_UiInputSrcName(UI_INPUT_SOURCE_TYPE)); );

    INPUT_SOURCE_TYPE_t eCurINPUT_SOURCE_TYPE_t = SYS_INPUT_SOURCE_TYPE(eWindow);
    INPUTSOURCE_DBG( printf(" eCurINPUT_SOURCE_TYPE_t=%u\n", eCurINPUT_SOURCE_TYPE_t); );


#if(DEBUG_CHG_SRC_TIME)
    //printf("CIS-1 %u\n", g_Debug_u32Time_ChangeSrc);
    msDebug_PrintChgSrcTime("ChangeInputSource Start");
#endif

    if(eWindow==MAIN_WINDOW)
    {
        source_type = UI_INPUT_SOURCE_TYPE;
    }
  #if (ENABLE_PIP)
    else if (eWindow==SUB_WINDOW)
    {
        source_type = UI_SUB_INPUT_SOURCE_TYPE;
    }
  #endif
    else
    {
        MS_DEBUG_MSG(printf("invalid window#!\n"));
        return;
    }


    // Enable black screen&freerun
    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, eWindow);

    //from void MApp_UiMenuFunc_ChangeInputSource(void)
#if SCART_ALWAYS_OUTPUT_ATV
    g_u8switchsourceprocessing = TRUE;
#endif

    // If teletext is On, turn it off
  #if ENABLE_TTX
    if (MApp_TTX_IsTeletextOn() == TRUE)
    {
        MApp_TTX_TeletextCommand(TTX_TV);
    }
  #endif

  #if ENABLE_3D_PROCESS
    if((eWindow == MAIN_WINDOW) && (MApi_XC_Get_3D_Input_Mode(MAIN_WINDOW) != E_XC_3D_INPUT_MODE_NONE))
    {
        //printf("Reset 3D variable\n");
        g_HdmiInput3DFormat = E_XC_3D_INPUT_MODE_NONE;
        g_HdmiInput3DFormatStatus = E_XC_3D_INPUT_MODE_NONE;
        MDrv_HDMI_pkt_reset(REST_HDMI_STATUS);

        MApp_Scaler_3D_ResetForChangeSrc();
    }
  #endif


    // Save last ordinal ...
    if( IsSrcTypeDTV(eCurINPUT_SOURCE_TYPE_t) || IsSrcTypeATV(eCurINPUT_SOURCE_TYPE_t) )
    {
        dmSetLastWatchedOrdinal();
    }

    // Disable channel
    if( IsSrcTypeDTV(eCurINPUT_SOURCE_TYPE_t)
      ||( IsSrcTypeATV(eCurINPUT_SOURCE_TYPE_t)&&(source_type!=UI_INPUT_SOURCE_ATV) )
      )
    {
        MApp_ChannelChange_DisableChannel(TRUE, eWindow);
    }
    else
    {
        MApp_ChannelChange_DisableAV(eWindow);
    }

    // Close all filter...
    if( IsSrcTypeDTV(eCurINPUT_SOURCE_TYPE_t) )
    {
    #if(ENABLE_DVB)
     #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
        if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
        {
            MApp_SI_Free_NetworkChangeInfo();
        }
     #endif

        MApp_Dmx_CloseAllFilters();

    #endif
    }


    // Call MApp_InputSource_SwitchSource
#if( ENABLE_ISDBT )
    INPUTSOURCE_DBG( printf(" msAPI_ATV_GetCurrentAntenna()=%u\n", msAPI_ATV_GetCurrentAntenna()); );
    INPUTSOURCE_DBG( printf(" enLastWatchAntennaType=%u\n", enLastWatchAntennaType); );

    if( ((source_type == UI_INPUT_SOURCE_ISDBT)||(source_type == UI_INPUT_SOURCE_ATV))
    #if( ENABLE_ISDBT_AND_DVB )
      && IS_COUNTRY_USE_SBTVD()
    #endif
      )
    {
        if (source_type == UI_INPUT_SOURCE_ISDBT)
        {
            msAPI_ATV_SetCurrentAntenna(ANT_AIR);
            msAPI_ATV_LoadCurrentProgramNumber();

            if (enLastWatchAntennaType == ANTENNA_DTV_TYPE)
            {
                printf("Change to ISDB-Air-DTV\n");
                UI_INPUT_SOURCE_TYPE=UI_INPUT_SOURCE_ISDBT;
                MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_ISDBT, eWindow);

             #ifdef ENABLE_SELECT_NONESEARCH_CH
                u16ChannelReturn_Num2 = IVALID_TV_RETURN_NUM;
             #endif
            }
            else
            {
                printf("Change to ISDB-Air-ATV\n");
                UI_INPUT_SOURCE_TYPE=UI_INPUT_SOURCE_ATV;
                MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_ATV, eWindow);
            }

            stGenSetting.stScanMenuSetting.u8Antenna = ANT_AIR;
        }
        else if (source_type == UI_INPUT_SOURCE_ATV)
        {
            printf("Change to ISDB-CATV-ATV\n");
            msAPI_ATV_SetCurrentAntenna(ANT_CATV);
            msAPI_ATV_LoadCurrentProgramNumber();

            MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_ATV, eWindow );

            stGenSetting.stScanMenuSetting.u8Antenna = ANT_CATV;

          #ifdef ENABLE_SELECT_NONESEARCH_CH
            u16ChannelReturn_Num2 = IVALID_TV_RETURN_NUM;
          #endif
        }

    }
    else
#endif
    {
        MApp_InputSource_SwitchSource( source_type, eWindow);
    }

#if 0
#if ENABLE_SBTVD_DTV_SYSTEM
    if ( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))&&(source_type!=UI_INPUT_SOURCE_ISDBT))
    {
        //enLastWatchAntennaType = ANTENNA_DTV_TYPE;
        checkdtvstatus=TRUE; //add the status in order to confirm that change inputsource correctly
                             //1.change air DTV-> cable,and then change cable->air(the correct status is DTV not ATV)[Mantis:0233409]
                             //2.AC/DC off->on on cable when air and cable both have ATV progeam,and then chanege cable->air(the correct status is ATV)
        //MApp_ChannelChange_DisableChannel(TRUE, eWindow);
        //MApp_Dmx_CloseAllFilters();
        msAPI_Tuner_ChangeProgram(); // Why??
    }
    else if ( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow))&&(source_type!=UI_INPUT_SOURCE_ISDBT)&& ANT_AIR == msAPI_ATV_GetCurrentAntenna())
    {
        //enLastWatchAntennaType = ANTENNA_ATV_TYPE;
        //MApp_ChannelChange_DisableChannel(TRUE, eWindow);
    }
    else if ( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow))&&(source_type!=UI_INPUT_SOURCE_ATV)&&ANT_CATV == msAPI_ATV_GetCurrentAntenna()&& checkdtvstatus != TRUE)
    {
        //enLastWatchAntennaType = ANTENNA_ATV_TYPE;
        //MApp_ChannelChange_DisableChannel(TRUE, eWindow);
    }
    else if ( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow))&&(source_type!=UI_INPUT_SOURCE_ATV)&&ANT_CATV == msAPI_ATV_GetCurrentAntenna()&& checkdtvstatus == TRUE)
    {
        //MApp_ChannelChange_DisableChannel(TRUE, eWindow);
    }

    // To fix Mantis:0118451
    //MApp_ChannelChange_DisableAV(eWindow);

    if (source_type == UI_INPUT_SOURCE_ISDBT)
    {
        msAPI_ATV_SetCurrentAntenna(ANT_AIR);
        msAPI_ATV_LoadCurrentProgramNumber();

        if (enLastWatchAntennaType == ANTENNA_DTV_TYPE)
        {
            UI_INPUT_SOURCE_TYPE=UI_INPUT_SOURCE_ISDBT;

            MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_ISDBT, eWindow);
         #ifdef ENABLE_SELECT_NONESEARCH_CH
            u16ChannelReturn_Num2=IVALID_TV_RETURN_NUM;
         #endif
        }
        else
        {
            UI_INPUT_SOURCE_TYPE=UI_INPUT_SOURCE_ATV;
            MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_ATV, eWindow);
        }
        stGenSetting.stScanMenuSetting.u8Antenna = ANT_AIR;
    }
    else if (source_type == UI_INPUT_SOURCE_ATV)
    {
        msAPI_ATV_SetCurrentAntenna(ANT_CATV);
        msAPI_ATV_LoadCurrentProgramNumber();

        MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_ATV, eWindow );

        stGenSetting.stScanMenuSetting.u8Antenna = ANT_CATV;

      #ifdef ENABLE_SELECT_NONESEARCH_CH
        u16ChannelReturn_Num2=IVALID_TV_RETURN_NUM;
      #endif
    }
    else
    {
        MApp_InputSource_SwitchSource( source_type, eWindow);
    }

#else

  #if ENABLE_DTV
    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))  )
    {

    #if 0//MHEG5_ENABLE
        if(msAPI_MHEG5_GetBinStatus() == TRUE)
        {
            // Disable Aeon for Non-DTV Mode
      #if (MHEG5_WITH_OSD)
            //if ( msAPI_MHEG5_checkGoBackMHEG5())
            {
                MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_WAIT);
            }
      #endif

            msAPI_COPRO_Disable();
        }
    #endif

        //MApp_ChannelChange_DisableChannel(TRUE, eWindow);

    #if 0//(ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
        if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
        {
            MApp_SI_Free_NetworkChangeInfo();
        }
    #endif

    #if(ENABLE_DVB)
        //MApp_Dmx_CloseAllFilters();
    #endif
        //msAPI_Tuner_ChangeProgram();
    }
    else
  #endif
    if ( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow))&&(source_type!=UI_INPUT_SOURCE_ATV) )
    {
        //MApp_ChannelChange_DisableChannel(TRUE, eWindow);
    }
    else
    {
        MApp_ChannelChange_DisableAV(eWindow);
    }

   MApp_InputSource_SwitchSource( source_type, eWindow);

#endif
#endif

  #if ENABLE_ATSC
    if (!IsAnyTVSourceInUse())
    {
        MApp_ChannelChange_EnableAV();
    }
  #endif


  #if SCART_ALWAYS_OUTPUT_ATV
    g_u8switchsourceprocessing = FALSE;
  #endif

   if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))
    || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow))
     )
   {
       MApp_ChannelChange_EnableChannel(eWindow);
   }

#if (ENABLE_DTV_EPG)
    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)))
        MApp_Epg_Init();
#endif

#if(DEBUG_CHG_SRC_TIME)
    //printf("CIS-100 %u\n", g_Debug_u32Time_ChangeSrc);
    msDebug_PrintChgSrcTime("ChangeInputSource End");
#endif

}

////////////////////////////////////////////////////////
//moved from MApp_UiMenu2.c
#if (INPUT_SCART_VIDEO_COUNT > 0)
void MApp_Scart_ChangeInputSourceToScart(INPUT_SOURCE_TYPE_t xcTargetScartSource)
{
    UNUSED(xcTargetScartSource);

    printf("Auto change source to scart\n");

#if (MHEG5_ENABLE)
    if(msAPI_MHEG5_IsRunning() == TRUE)
    {
        #if CIPLUS_MHEG_1_3
        msAPI_MHEG5_Key_Transmit( KEY_MENU, 0 );
        #else
        msAPI_MHEG5_Key_Transmit( KEY_INFO, 0 );//force exit Mheg5
        #endif
        bExitMheg5AsScartInserted = TRUE;
    }
    else
#endif
    {
      #if ENABLE_SUBTITLE
        if (MApp_Subtitle_Get_SubtitleOSDState())
        {
            MApp_Subtitle_Force_Exit();
        }
        else
      #endif
        {
          #if ENABLE_TTX
            if (MApp_TTX_IsTeletextOn() == TRUE)
            {
                MApp_TTX_TeletextCommand(TTX_TV);
            }
          #endif
        }
    }

#if (ENABLE_PIP)
    if( (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
     && !MApp_InputSource_PIP_IsSrcCompatible(xcTargetScartSource, SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
    {
        //Close subwindow and set compatible source type to sub win
        if(stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_SUB)
        {
            stGenSetting.g_stPipSetting.enPipSoundSrc=EN_PIP_SOUND_SRC_MAIN;
            MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
        }
        UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
        MApp_InputSource_ChangeInputSource(SUB_WINDOW);
        stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
        UI_SUB_INPUT_SOURCE_TYPE = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
    }
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 2)
    if( xcTargetScartSource == INPUT_SOURCE_SCART2 )
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SCART2;
    else
#endif
    {
        //printf("Scart-pin 8 detected, changed to scart1\n");
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SCART;
    }

    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
    MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);

    MApp_ChannelChange_VariableInit();

    if (MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY) //ZUI:
    {
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
    }
    if (stGenSetting.stMiscSetting.bRunInstallationGuide == FALSE )
    {
        MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
    }
}

void MApp_Scart_ChangeInputSourceFromScart(void)
{
    //ZUI_TODO: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
#if (ENABLE_PIP)
    if( (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
     && !MApp_InputSource_PIP_IsSrcCompatible(INPUT_SOURCE_TV, SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
    {
        //Close subwindow and set compatible source type to sub win
        if(stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_SUB)
        {
            stGenSetting.g_stPipSetting.enPipSoundSrc=EN_PIP_SOUND_SRC_MAIN;
            MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
        }
        UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
        MApp_InputSource_ChangeInputSource(SUB_WINDOW);
        stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
        UI_SUB_INPUT_SOURCE_TYPE = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
    }
#endif

#if (ENABLE_SCARTIN_PRESOURCE) && (INPUT_SCART_VIDEO_COUNT >= 1)
    MApp_InputSrc_Set_UiInputSrcType(MApp_InputSrc_Get_PrevUiInputSrcType());    //UI_INPUT_SOURCE_TYPE = UI_PREV_INPUT_SOURCE_TYPE;
    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
#else
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
    MApp_ChannelChange_VariableInit();
    MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);

    if( MApp_ZUI_GetActiveOSD() != E_OSD_EMPTY ) //ZUI:
    {
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
    }
    if( stGenSetting.stMiscSetting.bRunInstallationGuide == FALSE )
    {
        MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
    }
#endif
}

#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD )
    #define SCART_PIN8_CONTROL_USE_LOPEZ_METHOD 1
#else
    #define SCART_PIN8_CONTROL_USE_LOPEZ_METHOD 1
#endif

#if( SCART_PIN8_CONTROL_USE_LOPEZ_METHOD )

#define  PIN8_LOW        0
#define  PIN8_MID        1
#define  PIN8_HIGH       2
BYTE msGetScart1Status(void)
{
    U8 u8Pin8Status = PIN8_LOW;
    U16 u16Pin8Level = GetScart1IDLevel();

    //printf("1.u8Pin8Level=%u\n", u8Pin8Level);

    if( u16Pin8Level > SCART_ID_LEVEL_8V )
        u8Pin8Status = PIN8_HIGH;  // Overflow (>8.0V)
    else if( u16Pin8Level > SCART_ID_LEVEL_4V )
        u8Pin8Status = PIN8_MID;   //  Midrange (3.0V ~ 7.5V)
    return u8Pin8Status;
}

BYTE msGetScart2Status(void)
{
    BYTE u8Pin8Status = PIN8_LOW;
    U16 u16Pin8Level = GetScart2IDLevel();

    //printf("2.u8Pin8Level=%u\n", u8Pin8Level);

    if( u16Pin8Level > SCART_ID_LEVEL_8V )
        u8Pin8Status = PIN8_HIGH;  // Overflow (>8.0V)
    else if( u16Pin8Level > SCART_ID_LEVEL_4V )
        u8Pin8Status = PIN8_MID;   //  Midrange (3.0V ~ 7.5V)
    return u8Pin8Status;
}

typedef enum
{
    PIN8_MIN_EVENT,
    // SCART1
    PIN8_SCART1_LM,
    PIN8_SCART1_LH,
    PIN8_SCART1_ML,
    PIN8_SCART1_MH,
    PIN8_SCART1_HL,
    PIN8_SCART1_HM,
  #if (INPUT_SCART_VIDEO_COUNT >= 2)
    // SCART2
    PIN8_SCART2_LM,
    PIN8_SCART2_LH,
    PIN8_SCART2_ML,
    PIN8_SCART2_MH,
    PIN8_SCART2_HL,
    PIN8_SCART2_HM,
  #endif
    //
    PIN8_MAX_EVENT
} ScartEventEnumType;

U8 g_ucScart1Event = PIN8_MIN_EVENT;
#if (INPUT_SCART_VIDEO_COUNT >= 2)
U8 g_ucScart2Event = PIN8_MIN_EVENT;
#endif
void msCheckScartPin8Event(void)
{
    BYTE ucPin8StatusNew;
    //static BYTE ucPin8PrevEvent = PIN8_MIN_EVENT; // must be a value which is not PIN8
    static BYTE ucPin8StatusOld[2]={0,0};

    // no PIN8 recognition in teletext
    //if(g_bTTX_on)
    //    return;

    /** SCART 1 */
    ucPin8StatusNew = msGetScart1Status();
    // no PIN8 execution in adjustable menu
    //if(GetMenuState() )
    //    return;
    if(ucPin8StatusNew != ucPin8StatusOld[0])
    {
        if(ucPin8StatusNew == PIN8_LOW)
        {
            if(ucPin8StatusOld[0] == PIN8_MID)
            {
                //if(ucPin8PrevEvent != PIN8_SCART1_ML)
                {
                    g_ucScart1Event = PIN8_SCART1_ML;
                    //ucPin8PrevEvent=PIN8_SCART1_ML;
                }
            }
            else if(ucPin8StatusOld[0] == PIN8_HIGH)
            {
                //if(ucPin8PrevEvent != PIN8_SCART1_HL)
                {
                    g_ucScart1Event = PIN8_SCART1_HL;
                    //ucPin8PrevEvent=PIN8_SCART1_HL;
                }
            }
        }
        else if(ucPin8StatusNew == PIN8_MID)
        {
            if(ucPin8StatusOld[0] == PIN8_LOW)
            {
                //if(ucPin8PrevEvent != PIN8_SCART1_LM)
                {
                    g_ucScart1Event = PIN8_SCART1_LM;
                    //ucPin8PrevEvent=PIN8_SCART1_LM;
                }
            }
            else if(ucPin8StatusOld[0] == PIN8_HIGH)
            {
                //if(ucPin8PrevEvent != PIN8_SCART1_HM)
                {
                    g_ucScart1Event = PIN8_SCART1_HM;
                    //ucPin8PrevEvent=PIN8_SCART1_HM;
                }
            }
        }
        else if(ucPin8StatusNew == PIN8_HIGH)
        {
            if(ucPin8StatusOld[0] == PIN8_LOW)
            {
                //if(ucPin8PrevEvent != PIN8_SCART1_LH)
                {
                    g_ucScart1Event = PIN8_SCART1_LH;
                    //ucPin8PrevEvent=PIN8_SCART1_LH;
                }
            }
            else if(ucPin8StatusOld[0] == PIN8_MID)
            {
                //if(ucPin8PrevEvent != PIN8_SCART1_MH)
                {
                    g_ucScart1Event = PIN8_SCART1_MH;
                    //ucPin8PrevEvent=PIN8_SCART1_MH;
                }
            }
        }
        ucPin8StatusOld[0] = ucPin8StatusNew;
    }

  #if( INPUT_SCART_VIDEO_COUNT >= 2 )
    // SCART 2
    ucPin8StatusNew = msGetScart2Status();
    // no PIN8 execution in adjustable menu
    //if(GetMenuState() )
    //    return;
    if(ucPin8StatusNew != ucPin8StatusOld[1])
    {
        if(ucPin8StatusNew == PIN8_LOW)
        {
            if(ucPin8StatusOld[1] == PIN8_MID)
            {
               //if(ucPin8PrevEvent != PIN8_SCART2_ML)
                {
                    g_ucScart2Event = PIN8_SCART2_ML;
                    //ucPin8PrevEvent=PIN8_SCART2_ML;
                }
            }
            else if(ucPin8StatusOld[1] == PIN8_HIGH)
            {
                //if(ucPin8PrevEvent != PIN8_SCART2_HL)
                {
                    g_ucScart2Event = PIN8_SCART2_HL;
                    //ucPin8PrevEvent=PIN8_SCART2_HL;
                }
            }
        }
        else if(ucPin8StatusNew == PIN8_MID)
        {
            if(ucPin8StatusOld[1] == PIN8_LOW)
            {
                //if(ucPin8PrevEvent != PIN8_SCART2_LM)
                {
                    g_ucScart2Event = PIN8_SCART2_LM;
                    //ucPin8PrevEvent=PIN8_SCART2_LM;
                }
            }
            else if(ucPin8StatusOld[1] == PIN8_HIGH)
            {
                //if(ucPin8PrevEvent != PIN8_SCART2_HM)
                {
                    g_ucScart2Event = PIN8_SCART2_HM;
                    //ucPin8PrevEvent=PIN8_SCART2_HM;
                }
            }
        }
        else if(ucPin8StatusNew == PIN8_HIGH)
        {
            if(ucPin8StatusOld[1] == PIN8_LOW)
            {
                //if(ucPin8PrevEvent != PIN8_SCART2_LH)
                {
                    g_ucScart2Event = PIN8_SCART2_LH;
                    //ucPin8PrevEvent=PIN8_SCART2_LH;
                }
            }
            else if(ucPin8StatusOld[1] == PIN8_MID)
            {
                //if(ucPin8PrevEvent != PIN8_SCART2_MH)
                {
                    g_ucScart2Event = PIN8_SCART2_MH;
                    //ucPin8PrevEvent=PIN8_SCART2_MH;
                }
            }
        }
        ucPin8StatusOld[1] = ucPin8StatusNew;
    }
  #endif

}
#endif

void MApp_InputSource_ScartIOMonitor(void)
{
    if( msAPI_Timer_DiffTimeFromNow(u32ScartSwitchDuration) < 1000 )
        return;

#if ENABLE_PVR
    if(( MApp_ZUI_GetActiveOSD() == E_OSD_PVR )
  #if ENABLE_S2
    || (MApp_ZUI_GetActiveOSD() == E_OSD_MENU_DISHSETUP)
  #endif
    )
    {
        return;
    }
#endif

#ifdef MTC_FIX_BUG
    if( MApp_Is_InAutoScan_ATV() || MApp_Is_InAutoScan_DTV() )
        return;
#endif

#if ENABLE_S2
    if (MApp_Get_enScanState()!=STATE_SCAN_INIT)
    {
        return;
    }
#endif

/*
    if( msAPI_Tunning_Is_CurrentTuningState_Idle() == FALSE )
    {
        return;
    }
*/

    u32ScartSwitchDuration = msAPI_Timer_GetTime0();

#if( SCART_PIN8_CONTROL_USE_LOPEZ_METHOD )

    msCheckScartPin8Event();
    ////////////////////////////////////////////////////////////
    // Scart 1 event handler
    ///////////////////////////////////////////////////////////
    if(g_ucScart1Event>PIN8_MIN_EVENT && g_ucScart1Event<PIN8_MAX_EVENT)
    {
        //printf("g_ucScart1Event=%bu\n", g_ucScart1Event);
        //msAPI_Timer_Delayms(2000);
        switch(g_ucScart1Event)
        {
    /*
        case PIN8_SCART1_LM:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_TV ||
                g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART2)
                msSetInputSource(INPUTSOURCE_SCART1,PIN8_FORMAT_16_9);
            break;
        case PIN8_SCART1_LH:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_TV ||
                g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART2)
                msSetInputSource(INPUTSOURCE_SCART1,PIN8_FORMAT_4_3);
            break;
    */
        case PIN8_SCART1_LM:
        case PIN8_SCART1_LH:
            if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) != INPUT_SOURCE_SCART )
            {
                printf("\r\n Change To Scart Source1 \n");
                MApp_Scart_ChangeInputSourceToScart(INPUT_SOURCE_SCART);
            }
            break;

        case PIN8_SCART1_ML:
        case PIN8_SCART1_HL:
            if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) == INPUT_SOURCE_SCART )
                MApp_Scart_ChangeInputSourceFromScart();
          /*
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART1)
            {
                ucTemp=msGetScart2Status();
                if(ucTemp==PIN8_LOW)
                    msSetInputSource(INPUTSOURCE_TV,PIN8_FORMAT_OFF);
                else if(ucTemp==PIN8_MID)
                    msSetInputSource(INPUTSOURCE_SCART2,PIN8_FORMAT_16_9);
                else//Scart2 HIGH
                    msSetInputSource(INPUTSOURCE_SCART2,PIN8_FORMAT_4_3);
            }
          */
            break;
    /*
        case PIN8_SCART1_MH:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART1)
                if(g_VideoSetting.bScartAutoFormat)
                    msSetInputSource(INPUTSOURCE_SCART1,PIN8_FORMAT_4_3);
            break;
        case PIN8_SCART1_HM:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART1)
                if(g_VideoSetting.bScartAutoFormat)
                    msSetInputSource(INPUTSOURCE_SCART1,PIN8_FORMAT_16_9);
            break;
    */
        }
        g_ucScart1Event = PIN8_MIN_EVENT;
        return;
    }

  #if (INPUT_SCART_VIDEO_COUNT >= 2)
    ////////////////////////////////////////////////////////////
    // Scart 2 event handler
    ///////////////////////////////////////////////////////////
    else if(g_ucScart2Event>PIN8_MIN_EVENT && g_ucScart2Event<PIN8_MAX_EVENT)
    {
        switch(g_ucScart2Event)
        {
        case PIN8_SCART2_LM:
        case PIN8_SCART2_LH:
            if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) != INPUT_SOURCE_SCART2 )
                MApp_Scart_ChangeInputSourceToScart(INPUT_SOURCE_SCART2);
            break;

        case PIN8_SCART2_ML:
        case PIN8_SCART2_HL:
            if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) == INPUT_SOURCE_SCART2 )
                MApp_Scart_ChangeInputSourceFromScart();
            break;
    /*
        case PIN8_SCART2_LM:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_TV ||
                g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART1)
                msSetInputSource(INPUTSOURCE_SCART2,PIN8_FORMAT_16_9);
            break;
        case PIN8_SCART2_LH:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_TV ||
                g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART1)
                msSetInputSource(INPUTSOURCE_SCART2,PIN8_FORMAT_4_3);
            break;
        case PIN8_SCART2_ML:
        case PIN8_SCART2_HL:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART2)
            {
                ucTemp=msGetScart1Status();
                if(ucTemp==PIN8_LOW)
                    msSetInputSource(INPUTSOURCE_TV,PIN8_FORMAT_OFF);
                else if(ucTemp==PIN8_MID)
                    msSetInputSource(INPUTSOURCE_SCART1,PIN8_FORMAT_16_9);
                else//Scart1 HIGH
                    msSetInputSource(INPUTSOURCE_SCART1,PIN8_FORMAT_4_3);
            }
            break;
        case PIN8_SCART2_MH:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART2)
                if(g_VideoSetting.bScartAutoFormat)
                msSetInputSource(INPUTSOURCE_SCART2,PIN8_FORMAT_4_3);
            break;
        case PIN8_SCART2_HM:
            if(g_SrcInfo[SRC1].InputSrcType==INPUTSOURCE_SCART2)
                if(g_VideoSetting.bScartAutoFormat)
                msSetInputSource(INPUTSOURCE_SCART2,PIN8_FORMAT_16_9);
            break;
    */
        }
        g_ucScart2Event = PIN8_MIN_EVENT;
            }
  #endif

#else // #if( SCART_PIN8_CONTROL_USE_LOPEZ_METHOD )

  #if (INPUT_SCART_VIDEO_COUNT >= 1)
    if (msAPI_GPIO_IsSourceJustConnected(INPUT_SOURCE_SCART) == TRUE)
    {
        if ((SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) != INPUT_SOURCE_SCART) && (IsScartChange()))
        {
            MApp_Scart_ChangeInputSourceToScart(INPUT_SOURCE_SCART);
            ResetScartChange();
            return;
        }
    }
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 2)
    if (msAPI_GPIO_IsSourceJustConnected(INPUT_SOURCE_SCART2) == TRUE)
    {
        if ((SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) != INPUT_SOURCE_SCART2) &&(IsScartChange()))
        {
            MApp_Scart_ChangeInputSourceToScart(INPUT_SOURCE_SCART2);
            ResetScartChange();
            return;
        }
    }
  #endif

  #if (INPUT_SCART_VIDEO_COUNT >= 1)
    if (msAPI_GPIO_IsSourceJustDisConnected(INPUT_SOURCE_SCART) == TRUE)
            {
        if ((SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)  == INPUT_SOURCE_SCART) &&(IsScartChange()))
                {
            MApp_Scart_ChangeInputSourceFromScart();
            ResetScartChange();
            return;
                }
            }
          #endif

  #if (INPUT_SCART_VIDEO_COUNT >= 2)
    if (msAPI_GPIO_IsSourceJustDisConnected(INPUT_SOURCE_SCART2) == TRUE)
            {
        if ((SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)  == INPUT_SOURCE_SCART2) &&(IsScartChange()))
            {
            MApp_Scart_ChangeInputSourceFromScart();
            ResetScartChange();
            return;
        }
    }
  #endif
#endif // #if( SCART_PIN8_CONTROL_USE_LOPEZ_METHOD )
}
#endif

#if ENABLE_OFFLINE_SIGNAL_DETECTION
#define    AIS_Debug(x)    //x
typedef struct _SOURCE_SRC2LEVEL_STRUCT
{
    E_UI_INPUT_SOURCE source;
    U8 level;
} SOURCE_SRC2LEVEL_STRUCT;


static SOURCE_SRC2LEVEL_STRUCT code  _Source_Levels[] =
{

    {
        UI_INPUT_SOURCE_ATV,             // VIDEO - TV Tuner
        7
    },

#if (INPUT_SCART_VIDEO_COUNT >= 1)
    {
        UI_INPUT_SOURCE_SCART,
        18
    },
#endif
#if (INPUT_SCART_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_SCART2,
        17
    },
#endif
#if (INPUT_YPBPR_VIDEO_COUNT>=1)
    {
        UI_INPUT_SOURCE_COMPONENT,      // VIDEO - YPbPr
        26
    },
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_COMPONENT2,
        25
    },
#endif
    {
        UI_INPUT_SOURCE_RGB,            // PC - VGA
        19
    },
#if (INPUT_HDMI_VIDEO_COUNT >= 1)
    {
        UI_INPUT_SOURCE_HDMI,           // HDMI
        30
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_HDMI2,
        29
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 3)
    {
        UI_INPUT_SOURCE_HDMI3,
        28
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 4)
    {
        UI_INPUT_SOURCE_HDMI4,
        27
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 1)
    {
        UI_INPUT_SOURCE_AV,             // VIDEO - CVBS
        24
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_AV2,
        23
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 3)
    {
        UI_INPUT_SOURCE_AV3,
        22
    },
#endif
#if (INPUT_SV_VIDEO_COUNT >= 1)
    {
        UI_INPUT_SOURCE_SVIDEO,
        21
    },
#endif
#if (INPUT_SV_VIDEO_COUNT >= 2)
    {
        UI_INPUT_SOURCE_SVIDEO2,
        20
    },
#endif

#if ENABLE_DMP
    {
        UI_INPUT_SOURCE_DMP,
        16
    },
#endif //#if ENABLE_DMP

/*
    {
        UI_INPUT_SOURCE_GYM,
        11
    },
*/
};

static U8 MApp_InputSourceIdMapToLevel(E_UI_INPUT_SOURCE id)
{
    U8 i;
    for (i = 0; i < COUNTOF(_Source_Levels); i++)
    {
        if (id == _Source_Levels[i].source)
        {
            return _Source_Levels[i].level;
        }
    }
    return  0;
}

void MApp_AISDebug(U8 bSrcCnt)
{
    if(bSrcCnt == UI_INPUT_SOURCE_ATV)
        AIS_Debug(printf("*TV*"));
#if (ENABLE_ATSC)
    else if(bSrcCnt ==UI_INPUT_SOURCE_ATSC)
        AIS_Debug(printf("*TV*"));
#endif
#if (INPUT_YPBPR_VIDEO_COUNT>=1)
    else if(bSrcCnt ==UI_INPUT_SOURCE_COMPONENT)
        AIS_Debug(printf("*YUV 1*"));
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 2)
    else if(bSrcCnt ==UI_INPUT_SOURCE_COMPONENT2)
        AIS_Debug(printf("*YUV 2*"));
#endif
    else if(bSrcCnt ==UI_INPUT_SOURCE_RGB)
        AIS_Debug(printf("*RGB*"));
#if (INPUT_HDMI_VIDEO_COUNT >= 1)
    else if(bSrcCnt ==UI_INPUT_SOURCE_HDMI)
        AIS_Debug(printf("*HDMI-1*"));
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 2)
    else if(bSrcCnt ==UI_INPUT_SOURCE_HDMI2)
        AIS_Debug(printf("*HDMI-2*"));
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 3)
    else if(bSrcCnt ==UI_INPUT_SOURCE_HDMI3)
        AIS_Debug(printf("*HDMI-3*"));
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 4)
    else if(bSrcCnt ==UI_INPUT_SOURCE_HDMI4)
        AIS_Debug(printf("*HDMI-4*"));
#endif
#if (INPUT_AV_VIDEO_COUNT >= 1)
    else if(bSrcCnt ==UI_INPUT_SOURCE_AV)
        AIS_Debug(printf("*AV-1*"));
#endif
#if (INPUT_AV_VIDEO_COUNT >= 2)
    else if(bSrcCnt ==UI_INPUT_SOURCE_AV2)
        AIS_Debug(printf("*AV-2*"));
#endif
#if (INPUT_SV_VIDEO_COUNT >= 1)
    else if(bSrcCnt ==UI_INPUT_SOURCE_SVIDEO)
        AIS_Debug(printf("*SVideo-0*"));
#endif
#if ENABLE_DMP
    else if(bSrcCnt ==UI_INPUT_SOURCE_DMP)
        AIS_Debug(printf("*USB*"));
#endif
#if(ENABLE_FM_RADIO)
    else if(bSrcCnt ==UI_INPUT_SOURCE_FMRADIO)
        AIS_Debug(printf("*RADIO*"));
#endif
#if(GAME_ENABLE)
    else if(bSrcCnt ==UI_INPUT_SOURCE_GAME)
        AIS_Debug(printf("*GAME*"));
#endif

    else
    {
        AIS_Debug(printf("unknow: %u", bSrcCnt));
    }
}

void MApp_AISResultReset(void)
{
    U8 i;
    for(i=0;i<AIS_DOS_TIMES;i++)
    {
        stAISCtrl.strResult[i]=0;
    }
    stAISCtrl.bDotimes=0;
}

U8 MApp_AISGetAverage(void)
{
    U8 i,value;

    value=0;
    for(i=0;i<AIS_DOS_TIMES;i++)
    {
        value +=stAISCtrl.strResult[i];
    }
    AIS_Debug(printf("AVG:%u\n",value));
    if(value>(AIS_DOS_TIMES/2))
        return 1;
    else
        return 0;
}

void MApp_OffLineInit(void)
{
    U8 i;

    stAISCtrl.bUICHSourceFlag=1;
    stAISCtrl.bAISSrcPush=0xff;
    stAISCtrl.bSrcCnt=UI_INPUT_SOURCE_ATV;
    stAISCtrl.bSysTimeDuty=0;
    //stAISCtrl.bAISLock=1;
    stAISCtrl.dLockCnt=TIMER_STOP;
    stAISCtrl.bDotimes=0;
    stAISCtrl.bNoSignal=0;
    stAISCtrl.bDetectCnt=0;
    stAISCtrl.bDetectStart=0;
    MApp_AISResultReset();

    AIS_Debug(printf("OffLineIntial:\n"));
    for(i=0;i<UI_INPUT_SOURCE_NUM;i++)
    {
        AIS_Debug(printf("i=%u,",i));
        stAISSrcList[i].bChangeFlag=0;
        stAISSrcList[i].bUISourceID=i;
        stAISSrcList[i].bLevel=MApp_InputSourceIdMapToLevel((E_UI_INPUT_SOURCE)i);

        if((i==UI_INPUT_SOURCE_ATV)
    #if (ENABLE_S2)
         || (i==UI_INPUT_SOURCE_S2)
    #endif
    #if (ENABLE_ATSC)
         || (i==UI_INPUT_SOURCE_ATSC)
    #endif

    #if (ENABLE_DVBT)
         || (i==UI_INPUT_SOURCE_DVBT)
    #endif

    #if (ENABLE_DVBC)
         || (i==UI_INPUT_SOURCE_DVBC)
    #endif

    #if (ENABLE_ISDBT)
         || (i==UI_INPUT_SOURCE_ISDBT)
    #endif

    #if (ENABLE_DTMB)
         || (i==UI_INPUT_SOURCE_DTMB)
    #endif

    #if (ENABLE_DMP || BLOADER)
         || (i==UI_INPUT_SOURCE_DMP)
    #endif
          )
        {
            stAISSrcList[i].bHaveSignal=1;
        }
        else
        {
            stAISSrcList[i].bHaveSignal=0;
        }
		MApi_XC_OffLineInit();
    }
    //MApi_XC_SetOffLineDetection(1);
    AIS_Debug(printf("\n"));
}

//get next available InputSourceType and convert it to SourceNum,
//and then query sc lib
INPUT_SOURCE_TYPE_t MApp_GetAISNextSetSource(void)
{
    BOOLEAN bFlag=1;
    MS_SYS_INFO tmpSystemInfo;
    E_DATA_INPUT_SOURCE enTempDataInpSrc;
    tmpSystemInfo.enInputSourceType = INPUT_SOURCE_NONE;
    AIS_Debug(printf("current SOURCE_TYPE = %u\n", UI_INPUT_SOURCE_TYPE));
    do
    {
        if(stAISCtrl.bSrcCnt>=UI_INPUT_SOURCE_NUM-1)    //Last Source
            stAISCtrl.bSrcCnt= UI_INPUT_SOURCE_ATV;

        // Only do offline detection for below valid Input Source.
        // If you want to add more input, please add it here and the function:MApi_XC_MUX_MapInputSourceToVDYMuxPORT
        if(((UI_INPUT_SOURCE_RGB == stAISCtrl.bSrcCnt)
#if (INPUT_AV_VIDEO_COUNT >= 1)
            || (UI_INPUT_SOURCE_AV == stAISCtrl.bSrcCnt)
#endif
#if (INPUT_AV_VIDEO_COUNT >= 2)
            || (UI_INPUT_SOURCE_AV2 == stAISCtrl.bSrcCnt)
#endif
#if (INPUT_AV_VIDEO_COUNT >= 3)
            || (UI_INPUT_SOURCE_AV3 == stAISCtrl.bSrcCnt)
#endif

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
    #if  (INPUT_HDMI_VIDEO_COUNT >= 1)
    	            || (UI_INPUT_SOURCE_HDMI == stAISCtrl.bSrcCnt)
    #endif
    #if  (INPUT_HDMI_VIDEO_COUNT >= 2)
    	            || (UI_INPUT_SOURCE_HDMI2 == stAISCtrl.bSrcCnt)
    #endif
    #if  (INPUT_HDMI_VIDEO_COUNT >= 3)
    	            || (UI_INPUT_SOURCE_HDMI3 == stAISCtrl.bSrcCnt)
    #endif
    #if  (INPUT_HDMI_VIDEO_COUNT >= 4)
    	            || (UI_INPUT_SOURCE_HDMI4 == stAISCtrl.bSrcCnt)
    #endif
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 1)
            || (UI_INPUT_SOURCE_COMPONENT == stAISCtrl.bSrcCnt)
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 2)
            || (UI_INPUT_SOURCE_COMPONENT2 == stAISCtrl.bSrcCnt)
#endif
#if (INPUT_SV_VIDEO_COUNT >= 1)
            || (UI_INPUT_SOURCE_SVIDEO == stAISCtrl.bSrcCnt)
#endif
#if ENABLE_DMP
            || (UI_INPUT_SOURCE_DMP == stAISCtrl.bSrcCnt)
#endif
#if 0//BLE_FM_RADIO)
            || (UI_INPUT_SOURCE_FMRADIO== stAISCtrl.bSrcCnt)
#endif
#if 0//E_ENABLE)
            || (UI_INPUT_SOURCE_GAME == stAISCtrl.bSrcCnt)
#endif
            )
            && (UI_INPUT_SOURCE_TYPE != stAISCtrl.bSrcCnt))
        {
            bFlag=0;
        }
        else
        {
            stAISCtrl.bSrcCnt++;
        }

    }while(bFlag);

    MApp_InputSource_SetSystemmInfo( stAISCtrl.bSrcCnt, &tmpSystemInfo , &enTempDataInpSrc );

    AIS_Debug(printf("now process UI type: "));
    AIS_Debug(MApp_AISDebug(stAISCtrl.bSrcCnt));
    AIS_Debug(printf("\n"));
    AIS_Debug(printf("Map to InputSourceType: %u\n", tmpSystemInfo.enInputSourceType));

    return tmpSystemInfo.enInputSourceType;
}

void MApp_SetDetectChannel(void)
{
    INPUT_SOURCE_TYPE_t u8InputSourceType = INPUT_SOURCE_NONE;

    u8InputSourceType = MApp_GetAISNextSetSource();
    stAISCtrl.bDetectCnt++;

    if(INPUT_SOURCE_NONE != u8InputSourceType)
    {
        MApi_XC_SetOffLineDetection(u8InputSourceType);
        MApp_AISResultReset();
    }
    else
    {
        MApp_AISResultReset();
    }
    stAISCtrl.bSysTimeDuty= msAPI_Timer_GetTime0();
    //AIS_Debug(printf("get time:%lx\n",stAISCtrl.bSysTimeDuty));
}

void MApp_SetSrcListFlag(BOOLEAN bHaveSignal,U8 bSrcCnt)
{
    if(bHaveSignal)    //Have signal
    {
        AIS_Debug(printf(":Signal:%u,CHFlag:%u\n",stAISSrcList[bSrcCnt].bHaveSignal,stAISSrcList[bSrcCnt].bChangeFlag));

    if(stAISSrcList[bSrcCnt].bHaveSignal)    //No Change:Still have Signal
    {
        stAISSrcList[bSrcCnt].bChangeFlag=0;
    }
    else                                            //Signal Change:Plug in
    {
        AIS_Debug(printf("[Signal Plug in]\n",bSrcCnt));
        stAISSrcList[bSrcCnt].bChangeFlag=1;
        stAISSrcList[bSrcCnt].bHaveSignal=1;
        return;
    }
    }
    else    //No signal
    {
        AIS_Debug(printf(":Signal:%u,CHFlag:%u\n",stAISSrcList[bSrcCnt].bHaveSignal,stAISSrcList[bSrcCnt].bChangeFlag));
        if(stAISSrcList[bSrcCnt].bHaveSignal)    //    Signal Change:Plug out
        {
            AIS_Debug(printf("[Signal Plug Out]\n",bSrcCnt));
            stAISSrcList[bSrcCnt].bChangeFlag=1;
            stAISSrcList[bSrcCnt].bHaveSignal=0;
            return;
        }
        else                                            //No Change :Still no signal
        {
            stAISSrcList[bSrcCnt].bChangeFlag=0;
        }
    }
    AIS_Debug(printf("\r\n"));
    return;
}

void MApp_GetOffLineStatus(void)
{
    U8 bHaveSignal = 0;
    MS_SYS_INFO tmpSystemInfo;
    E_DATA_INPUT_SOURCE enTempDataInpSrc;

    MApp_InputSource_SetSystemmInfo( stAISCtrl.bSrcCnt, &tmpSystemInfo , &enTempDataInpSrc);
	#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)//use Gpio detect for offline
	    #if (INPUT_HDMI_VIDEO_COUNT > 0)
		 if(tmpSystemInfo.enInputSourceType == INPUT_SOURCE_HDMI)
           bHaveSignal = HDMI1_INPUT_DETECT();
	    #endif

	    #if (INPUT_HDMI_VIDEO_COUNT >= 2)
		else if(tmpSystemInfo.enInputSourceType == INPUT_SOURCE_HDMI2)
         bHaveSignal = HDMI2_INPUT_DETECT();
	    #endif

	    #if (INPUT_HDMI_VIDEO_COUNT >= 3)
		else if(tmpSystemInfo.enInputSourceType == INPUT_SOURCE_HDMI3)
         bHaveSignal = HDMI3_INPUT_DETECT();
	    #endif

	    #if (INPUT_HDMI_VIDEO_COUNT >= 4)
		else if(tmpSystemInfo.enInputSourceType == INPUT_SOURCE_HDMI4)
         bHaveSignal = HDMI4_INPUT_DETECT();
	    #endif
	    else
	#endif
           bHaveSignal = MApi_XC_GetOffLineDetection(tmpSystemInfo.enInputSourceType);

    stAISCtrl.strResult[stAISCtrl.bDotimes++]=bHaveSignal;
    AIS_Debug(MApp_AISDebug(stAISCtrl.bSrcCnt));
    AIS_Debug(printf("times:%u,Signal:%u\n", stAISCtrl.bDotimes, bHaveSignal));
    if(stAISCtrl.bDotimes <AIS_DOS_TIMES)
    {
        return;
    }
    else
    {
        bHaveSignal = MApp_AISGetAverage();
    }

    //MApp_AISDebug(stAISCtrl.bSrcCnt);
    MApp_SetSrcListFlag(bHaveSignal,stAISCtrl.bSrcCnt);
    AIS_Debug(printf("-----------bHaveSignal:%u\r\n",bHaveSignal));
    return;
}

U8 MApp_GetStsChangeSrc(void)
{
    U8 i;

    for(i=0;i<UI_INPUT_SOURCE_NUM;i++)
    {
        if(stAISSrcList[i].bChangeFlag)
        {
            stAISSrcList[i].bChangeFlag=0;
            return i;
        }
    }

    return 0xff;
}
U8 MApp_GetShowTopChangeSrc(void)
{
    U8 i;
    U8 level=0;
    U8 SrcID=0xFF;
    for(i=0;i<UI_INPUT_SOURCE_NUM;i++)
    {
        if(stAISSrcList[i].bChangeFlag&&stAISSrcList[i].bHaveSignal)
        {
            AIS_Debug(printf("-SrcID=%d-bLevel=%d-\n",i,stAISSrcList[i].bLevel));//
            if(stAISSrcList[i].bLevel>=level)
            {
                level=stAISSrcList[i].bLevel;
                SrcID=i;
            }
        }
    }
    if(SrcID!=0xFF)
    {
       stAISSrcList[SrcID].bChangeFlag=0;
       AIS_Debug(printf("-End SrcID=%d-bLevel=%d-\n",SrcID,stAISSrcList[SrcID].bLevel));//
    }
    return SrcID;
}

U8 MApp_GetAISReturnSrcID(void)
{
    U8 i,SrcID=0xff;
    AIS_Debug(printf("Get Have Signal Channel:"));
    for(i=0;i<UI_INPUT_SOURCE_NUM;i++)
    {
       //AIS_Debug(printf("---i=%bu---\n",i));
        if(stAISSrcList[i].bHaveSignal)
        {
            if((i==UI_INPUT_SOURCE_ATV) /*||(i==UI_INPUT_SOURCE_DTV)*/
            ||((i==UI_INPUT_SOURCE_DMP)))
                continue;
            else
            {
                SrcID=i;
                break;
            }

        }
    }
    if(SrcID == 0xff)
        SrcID=UI_INPUT_SOURCE_ATV;
    AIS_Debug(printf("SrcID:%d\n",SrcID));

    return SrcID;

}

void    MApp_AISMonitor(void)
{
    U8 bValue=0xff;
    BOOLEAN bChange_Flag=FALSE;
    U8 bDetectNum=4;
    stGenSetting.g_SysSetting.bAIS=AIS_DISPLAY;//AIS_SWITCH;//AIS_DISPLAY;
    if(stGenSetting.g_SysSetting.bAIS==AIS_OFF/*||(!MApp_IsNormalMode())*/)
        return;
    if(msAPI_Tuner_IsTuningProcessorBusy())
    {
        //printf(" AIS: Scan return\n");
        return;
    }
    if((UI_INPUT_SOURCE_TYPE==UI_INPUT_SOURCE_COMPONENT)
        ||(UI_INPUT_SOURCE_TYPE==UI_INPUT_SOURCE_AV)
#if (INPUT_AV_VIDEO_COUNT >= 2)
        ||(UI_INPUT_SOURCE_TYPE==UI_INPUT_SOURCE_AV2)
#endif
        ||(UI_INPUT_SOURCE_TYPE==UI_INPUT_SOURCE_RGB)
        )
    {
        bDetectNum=3;
    }
    else
    {
        bDetectNum=4;
    }
    if(stAISCtrl.dLockCnt==TIMER_STOP)
       {
    }
    else if(stAISCtrl.dLockCnt>2500)
    {
        stAISCtrl.dLockCnt=TIMER_STOP;
    }
    else
    {
        stAISCtrl.dLockCnt++;
        return;
    }

    if(0 == stAISCtrl.bSysTimeDuty)
    {
        MApp_SetDetectChannel();
    }

    if ( msAPI_Timer_DiffTimeFromNow( stAISCtrl.bSysTimeDuty ) > AIS_DETECT_DUTY )
    {
        //AIS_Debug(printf("get time2:%lx\n",msAPI_Timer_GetTime0()));
        MApp_GetOffLineStatus();
        if(stAISCtrl.bDotimes<AIS_DOS_TIMES)
        {
            stAISCtrl.bSysTimeDuty= msAPI_Timer_GetTime0();
            return;
        }
        else
        {
            stAISCtrl.bSrcCnt++;
            stAISCtrl.bSysTimeDuty=0;
        }

        /*
            Here, draw menu and some other AP behavior according to stAISSrcList[bValue].bHaveSignal
        */
        MApp_ZUI_ACT_DrawAisIcon();

        if(stAISCtrl.bDetectCnt>=bDetectNum)
        {
           stAISCtrl.bDetectCnt=0;
           stAISCtrl.bDetectStart=TRUE;
           bChange_Flag=TRUE;
        }
        else
        {
           bChange_Flag=FALSE;
        }
        switch(stGenSetting.g_SysSetting.bAIS)
        {
           default:
           case AIS_OFF:
            break;
           case AIS_DISPLAY:
            if(!stAISCtrl.bDetectStart)
            {
                break;
            }
            if(bChange_Flag)
            {
                bChange_Flag=FALSE;
                bValue= MApp_GetShowTopChangeSrc();
                AIS_Debug(printf("-Detect Display Source=%d--\n",bValue));//
            }
            else
            {
                break;
            }
               //  bValue=MApp_GetStatusChangeSrc();        //Clear Signal Change Flag...
            if((bValue<UI_INPUT_SOURCE_NUM) &&(bValue!=UI_INPUT_SOURCE_TYPE) )    //Valid Source
            {
                if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                    stAISSrcList[UI_INPUT_SOURCE_TYPE].bHaveSignal=1;
                    AIS_Debug(printf("-AIS_DISPLAY:current source has signal no change--\n"));//
                }
                else
                    stAISSrcList[UI_INPUT_SOURCE_TYPE].bHaveSignal=0;

                if(stAISSrcList[bValue].bHaveSignal)// Plug in
                {
                    stAISCtrl.bAISSrcPush=bValue;
                    //Draw UI Message,Wait "Yes/No"
                    //if (IsAnyTVSourceInUse())
                    //{
                    //    MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
                    //}
                    //else
                    //{
                    //    MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
                    //}
                    //MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    //MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_CEC_DEVICE_MSGBOX);

                    AIS_Debug(printf("-show  source display change--\n"));
                }
            }
            break;
            case AIS_SWITCH:
            if(!stAISCtrl.bDetectStart)
            {
                break;
            }
            if(bChange_Flag)
            {
                bChange_Flag=FALSE;
                bValue= MApp_GetShowTopChangeSrc();
                AIS_Debug(printf("-Detect change Source=%d--\n",bValue));//
            }
            else
            {
                break;
            }
            if((bValue<UI_INPUT_SOURCE_NUM)&&(bValue!=UI_INPUT_SOURCE_TYPE))//    Valid Source
            {
                if(stAISSrcList[bValue].bHaveSignal)// Plug in
                {
                    if(MApp_IsSrcHasSignal(MAIN_WINDOW))
                    {
                        stAISSrcList[UI_INPUT_SOURCE_TYPE].bHaveSignal=1;
                        AIS_Debug(printf("-AIS_SWITCH:current source has signal no change-\n"));//
                    }
                    else
                        stAISSrcList[UI_INPUT_SOURCE_TYPE].bHaveSignal=0;

                stAISCtrl.bAISSrcPush=bValue;

                UI_INPUT_SOURCE_TYPE=(E_UI_INPUT_SOURCE)bValue;
                MApp_InputSource_RecordSource(UI_INPUT_SOURCE_TYPE);
                MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
                MApp_ChannelChange_VariableInit();
                MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);//(STATE_TOP_ANALOG_SHOW_BANNER);
                stAISCtrl.bUICHSourceFlag=0;
                AIS_Debug(printf("-AIS_SWITCH:change to source=%d--\n",UI_INPUT_SOURCE_TYPE));
                }
            }
            break;
        }

        //---MainDisplay Nosigal Return Fuction Begin---
        if(stAISCtrl.bUICHSourceFlag ||(UI_INPUT_SOURCE_ATV ==UI_INPUT_SOURCE_TYPE))
        {
            AIS_Debug(printf("-Don't detect signal-\n"));
            return;
        }
        AIS_Debug(printf("---AIS_Nosiganl=%d----\n",stAISCtrl.bNoSignal));

        if(stAISCtrl.bNoSignal)
        {
            AIS_Debug(printf("-MainDisplay NoSignal--\n"));

            stAISSrcList[UI_INPUT_SOURCE_TYPE].bHaveSignal=0;
            //AIS_Debug(printf("-------AIS Return Signal in Source--------\n"));
            bValue=MApp_GetAISReturnSrcID();
            AIS_Debug(printf("---Get Source id:%d----\n",bValue));
            if(UI_INPUT_SOURCE_TYPE != bValue)
            {
                UI_INPUT_SOURCE_TYPE=(E_UI_INPUT_SOURCE)bValue;
                MApp_InputSource_RecordSource(UI_INPUT_SOURCE_TYPE);
                MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
                MApp_ChannelChange_VariableInit();
                MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
                stAISCtrl.bUICHSourceFlag=0;
                AIS_Debug(printf("-Auto:change to source=%d--\n",UI_INPUT_SOURCE_TYPE));
            }
        }
    //---MainDisplay Nosigal Return Fuction end---

    }
}
#endif

E_UI_INPUT_SOURCE MApp_InputSource_GetUIInputSourceType(INPUT_SOURCE_TYPE_t stInputSrc)
{
    switch(stInputSrc)
    {
        case INPUT_SOURCE_VGA:
            return UI_INPUT_SOURCE_RGB;
        case INPUT_SOURCE_TV:
            return UI_INPUT_SOURCE_ATV;

        case INPUT_SOURCE_CVBS:
#if (INPUT_AV_VIDEO_COUNT >= 1)
            return UI_INPUT_SOURCE_AV;
#endif
            break;

        case INPUT_SOURCE_CVBS2:
#if (INPUT_AV_VIDEO_COUNT >= 2)
            return UI_INPUT_SOURCE_AV2;
#endif
            break;

        case INPUT_SOURCE_CVBS3:
#if (INPUT_AV_VIDEO_COUNT >= 3)
            return UI_INPUT_SOURCE_AV3;
#endif
            break;
        case INPUT_SOURCE_SVIDEO:
#if(ENABLE_SCART_SVIDEO)
    return UI_INPUT_SOURCE_SCART;
#else
#if (INPUT_SV_VIDEO_COUNT >= 1)
            return UI_INPUT_SOURCE_SVIDEO;
#endif
#endif
            break;
        case INPUT_SOURCE_SVIDEO2:
#if (INPUT_SV_VIDEO_COUNT >= 2)
            return UI_INPUT_SOURCE_SVIDEO2;
#endif
            break;
        case INPUT_SOURCE_YPBPR:
#if (INPUT_YPBPR_VIDEO_COUNT>=1)
            return UI_INPUT_SOURCE_COMPONENT;
#endif
            break;
        case INPUT_SOURCE_YPBPR2:
#if (INPUT_YPBPR_VIDEO_COUNT>=2)
            return UI_INPUT_SOURCE_COMPONENT2;
#endif
            break;
        case INPUT_SOURCE_SCART:
#if (INPUT_SCART_VIDEO_COUNT >= 1)
            return UI_INPUT_SOURCE_SCART;
#endif
            break;
        case INPUT_SOURCE_SCART2:
#if (INPUT_SCART_VIDEO_COUNT >= 2)
            return UI_INPUT_SOURCE_SCART2;
#endif
            break;
        case INPUT_SOURCE_HDMI:
#if (INPUT_HDMI_VIDEO_COUNT >= 1)
            return UI_INPUT_SOURCE_HDMI;
#endif
            break;
        case INPUT_SOURCE_HDMI2:
#if (INPUT_HDMI_VIDEO_COUNT >= 2)
            return UI_INPUT_SOURCE_HDMI2;
#endif
            break;
        case INPUT_SOURCE_HDMI3:
#if (INPUT_HDMI_VIDEO_COUNT >= 3)
            return UI_INPUT_SOURCE_HDMI3;
#endif
            break;
        case INPUT_SOURCE_HDMI4:
#if (INPUT_HDMI_VIDEO_COUNT >= 4)
            return UI_INPUT_SOURCE_HDMI4;
#endif
            break;

    #if( ENABLE_DTV )
        case INPUT_SOURCE_DTV:
            //TO DO
        #if ENABLE_ATSC
            return UI_INPUT_SOURCE_ATSC;
        #elif ENABLE_DVBT
            return UI_INPUT_SOURCE_DVBT;
        #elif ENABLE_DTMB
            return UI_INPUT_SOURCE_DTMB;
        #elif ENABLE_ISDBT
            return UI_INPUT_SOURCE_ISDBT;
        #endif
            break;
    #endif

      #if ENABLE_DMP
        case INPUT_SOURCE_STORAGE:
            return UI_INPUT_SOURCE_DMP;
      #endif

        default:
            break;
    }

    return UI_INPUT_SOURCE_NONE;
}

INPUT_SOURCE_TYPE_t MApp_InputSource_GetInputSourceType(E_UI_INPUT_SOURCE stInputSrc)
{
    switch(stInputSrc)
    {
    #if( ENABLE_DTV )

      #if ENABLE_S2
        case UI_INPUT_SOURCE_S2:
      #endif
      #if ENABLE_ATSC
        case UI_INPUT_SOURCE_ATSC:
      #endif
      #if ENABLE_DVBT
        case UI_INPUT_SOURCE_DVBT:
      #endif
      #if ENABLE_DVBC
        case UI_INPUT_SOURCE_DVBC:
      #endif
      #if ENABLE_DTMB
        case UI_INPUT_SOURCE_DTMB:
      #endif
      #if ENABLE_ISDBT
        case UI_INPUT_SOURCE_ISDBT:
      #endif

        return INPUT_SOURCE_DTV;

    #endif // #if( ENABLE_DTV )


        case UI_INPUT_SOURCE_ATV:
            return INPUT_SOURCE_TV;

    #if (INPUT_AV_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_AV:
            return INPUT_SOURCE_CVBS;
    #endif
            break;

    #if (INPUT_AV_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_AV2:
            return INPUT_SOURCE_CVBS2;
    #endif

    #if (INPUT_AV_VIDEO_COUNT >= 3)
        case UI_INPUT_SOURCE_AV3:
            return INPUT_SOURCE_CVBS3;
    #endif

    #if (INPUT_SV_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_SVIDEO:
            return INPUT_SOURCE_SVIDEO;
    #endif

    #if (INPUT_SV_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_SVIDEO2:
            return INPUT_SOURCE_SVIDEO2;
    #endif

    #if (INPUT_YPBPR_VIDEO_COUNT>=1)
        case UI_INPUT_SOURCE_COMPONENT:
            return INPUT_SOURCE_YPBPR;
    #endif

    #if (INPUT_YPBPR_VIDEO_COUNT>=2)
        case UI_INPUT_SOURCE_COMPONENT2:
            return INPUT_SOURCE_YPBPR2;
    #endif

    #if (INPUT_SCART_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_SCART:
            return INPUT_SOURCE_SCART;
    #endif

    #if (INPUT_SCART_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_SCART2:
            return INPUT_SOURCE_SCART2;
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_HDMI:
            return INPUT_SOURCE_HDMI;
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_HDMI2:
            return INPUT_SOURCE_HDMI2;
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 3)
        case UI_INPUT_SOURCE_HDMI3:
            return INPUT_SOURCE_HDMI3;
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 4)
        case UI_INPUT_SOURCE_HDMI4:
            return INPUT_SOURCE_HDMI4;
    #endif

        case UI_INPUT_SOURCE_RGB:
            return INPUT_SOURCE_VGA;

    #if ENABLE_DMP
        case UI_INPUT_SOURCE_DMP:
            return INPUT_SOURCE_STORAGE;
    #endif


        default:
            break;
    }

    return INPUT_SOURCE_NONE;
}


#if (ENABLE_DTV_CHCEK_USB_DELAY_2S)
void MApp_DTV_USB_CheckMonitor(void)
{
    if(g_u8DTVCheckUSBFlag&DTV_CHECK_USB_MONITOR_START_BIT)
    {
        if(msAPI_Timer_DiffTimeFromNow(u32CheckUSBMonitorTimer) > 2000)
        {
            g_u8DTVCheckUSBFlag = DTV_CHECK_USB_ENABLE;
        }
    }

}
#endif

EN_VIF_WORKING_STATUS MApp_InputSource_GetVifWorkingStatus(void)
{
    return eVifStatus;
}
/*
BOOLEAN MApp_Is_UI_INPUT_SOURCE_DTV(E_UI_INPUT_SOURCE eUiInputSourceType)
{
    switch ( eUiInputSourceType )
    {
        case UI_INPUT_SOURCE_S2:
        case UI_INPUT_SOURCE_ATSC:
        case UI_INPUT_SOURCE_DVBT:
        case UI_INPUT_SOURCE_DVBC:
        case UI_INPUT_SOURCE_ISDBT:
        case UI_INPUT_SOURCE_DTMB:
            return TRUE;

        default:
            return FALSE;
    }
}
*/

//-----------------------------------------------------------------------------------

// UI Inputsource control
#define DEBUG_UI_INPUT_SRC(x)   x
static E_UI_INPUT_SOURCE g_InputSrc_eLastDtvUiSrc = UI_INPUT_SOURCE_NONE;
void MApp_InputSrc_Set_UiInputSrcType(E_UI_INPUT_SOURCE enUiInputSourceType)
{
    DEBUG_UI_INPUT_SRC(printf("MApp_InputSrc_Set_UiInputSrcType(src=%u)\n", enUiInputSourceType););

/*
    // If original src is DTV,  and new source is not dtv, save it
    if( MApp_InputSrc_Is_UiInputSrcTypeDtv(UI_INPUT_SOURCE_TYPE)
     && (!MApp_InputSrc_Is_UiInputSrcTypeDtv(enUiInputSourceType))
      )
    {
        g_InputSrc_eLastUiDtvSrc = UI_INPUT_SOURCE_TYPE;
        DEBUG_UI_INPUT_SRC(printf("g_InputSrc_eLastUiDtvSrc=%u\n", g_InputSrc_eLastUiDtvSrc););
    }
*/

    // Always save dtv src
    if( MApp_InputSrc_Is_UiInputSrcTypeDtv(enUiInputSourceType) )
    {
        g_InputSrc_eLastDtvUiSrc = enUiInputSourceType;
        DEBUG_UI_INPUT_SRC(printf("g_InputSrc_eLastDtvUiSrc=%u\n", g_InputSrc_eLastDtvUiSrc););
    }

    UI_INPUT_SOURCE_TYPE = enUiInputSourceType;
}

E_UI_INPUT_SOURCE MApp_InputSrc_Get_UiInputSrcType(void)
{
    return UI_INPUT_SOURCE_TYPE;
}

E_UI_INPUT_SOURCE MApp_InputSrc_Get_LastDtvUiSrcType(void)
{
    if( g_InputSrc_eLastDtvUiSrc == UI_INPUT_SOURCE_NONE )
        g_InputSrc_eLastDtvUiSrc = SYS_DEFAULT_DTV_UI_INPUTSOURCE;

    return g_InputSrc_eLastDtvUiSrc;
}

void MApp_InputSrc_Set_PrevUiInputSrcType(E_UI_INPUT_SOURCE enUiInputSourceType)
{
    DEBUG_UI_INPUT_SRC(printf("MApp_InputSrc_Set_PrevUiInputSrcType(src=%u)\n", enUiInputSourceType););

    UI_PREV_INPUT_SOURCE_TYPE = enUiInputSourceType;
}

E_UI_INPUT_SOURCE MApp_InputSrc_Get_PrevUiInputSrcType(void)
{
    return UI_PREV_INPUT_SOURCE_TYPE;
}

BOOL MApp_InputSrc_Is_UiInputSrcTypeDtv(E_UI_INPUT_SOURCE enUiInputSourceType)
{
    switch(enUiInputSourceType)
    {
        default:
            break;

        case UI_INPUT_SOURCE_S2:
        case UI_INPUT_SOURCE_ATSC:
        case UI_INPUT_SOURCE_DVBT:
        case UI_INPUT_SOURCE_DVBC:
        case UI_INPUT_SOURCE_ISDBT:
        case UI_INPUT_SOURCE_DTMB:
            return TRUE;
            break;
    }

    return FALSE;
}

BOOL MApp_InputSrc_Is_CurUiInputSrcTypeDtv(void)
{
    return MApp_InputSrc_Is_UiInputSrcTypeDtv(UI_INPUT_SOURCE_TYPE);
}

BOOL MApp_InputSrc_Is_PrevUiInputSrcTypeDtv(void)
{
    return MApp_InputSrc_Is_UiInputSrcTypeDtv(UI_PREV_INPUT_SOURCE_TYPE);
}

BOOL MApp_InputSrc_Is_UiInputSrcTypeHDMI(E_UI_INPUT_SOURCE enUiInputSourceType)
{
#if (INPUT_HDMI_VIDEO_COUNT >= 1)
    if( (UI_INPUT_SOURCE_HDMI <= enUiInputSourceType) && (enUiInputSourceType < UI_INPUT_SOURCE_HDMI_END) )
        return TRUE;
#endif

    return FALSE;
}

char* MApp_InputSrc_Get_UiInputSrcName(E_UI_INPUT_SOURCE enUiInputSourceType)
{
    switch(enUiInputSourceType)
    {
    #if( ENABLE_DTV )

      #if ENABLE_S2
        case UI_INPUT_SOURCE_S2:
            return "DVBS";
      #endif

      #if ENABLE_ATSC
        case UI_INPUT_SOURCE_ATSC:
            return "ATSC";
      #endif

      #if ENABLE_DVBT
        case UI_INPUT_SOURCE_DVBT:
            return "DVBT";
      #endif

      #if ENABLE_DVBC
        case UI_INPUT_SOURCE_DVBC:
            return "DVBC";
      #endif

      #if ENABLE_DTMB
        case UI_INPUT_SOURCE_DTMB:
            return "DTMB";
      #endif

      #if ENABLE_ISDBT
        case UI_INPUT_SOURCE_ISDBT:
            return "ISDBT";
      #endif
    #endif // #if( ENABLE_DTV )

        case UI_INPUT_SOURCE_ATV:
            return "ATV";

    #if (INPUT_YPBPR_VIDEO_COUNT>=1)
        case UI_INPUT_SOURCE_COMPONENT:      // VIDEO - YPbPr
            return "YPbPr";
    #endif

        case UI_INPUT_SOURCE_RGB:   // PC - VGA
            return "VGA";

    #if (INPUT_HDMI_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_HDMI:  // HDMI
            return "HDMI1";
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 2)
        case UI_INPUT_SOURCE_HDMI2:  // HDMI
            return "HDMI2";
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 3)
        case UI_INPUT_SOURCE_HDMI3:  // HDMI
            return "HDMI3";
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 4)
        case UI_INPUT_SOURCE_HDMI4:  // HDMI
            return "HDMI4";
    #endif


    #if (INPUT_AV_VIDEO_COUNT >= 1)
        case UI_INPUT_SOURCE_AV:      // VIDEO - CVBS
            return "CVBS";
    #endif

    #if (ENABLE_DMP || BLOADER)
        case UI_INPUT_SOURCE_DMP:
            return "DMP";
    #endif
    #if(ENABLE_FM_RADIO)
        case UI_INPUT_SOURCE_FMRADIO:
            return "RADIO";
    #endif
    #if GAME_ENABLE
        case UI_INPUT_SOURCE_GAME:
            return "GAME";
    #endif

        case UI_INPUT_SOURCE_NONE:
            return "NONE";

        default:
            break;
    }

    return "UiSrcNoName";
}

//-----------------------------------------------------------------------------------
void MApp_InputSrc_ChangeToLastUiDtvSrc(void)
{
#if(ENABLE_DTV)
    printf("MApp_InputSrc_ChangeToLastDtvSrc()\n");

    E_UI_INPUT_SOURCE eLastUiSrc = MApp_InputSrc_Get_LastDtvUiSrcType();

    if( eLastUiSrc == UI_INPUT_SOURCE_NONE )
        eLastUiSrc = SYS_DEFAULT_DTV_UI_INPUTSOURCE;

    if( MApp_InputSrc_Get_UiInputSrcType() != eLastUiSrc )
    {
        MApp_InputSrc_Set_UiInputSrcType( eLastUiSrc );

        MApp_InputSource_SwitchSource( eLastUiSrc, MAIN_WINDOW );
    }
#endif
}

//-----------------------------------------------------------------------------------

/***************************************************************************************/

#undef MAPP_INPUTSOURCE_C

