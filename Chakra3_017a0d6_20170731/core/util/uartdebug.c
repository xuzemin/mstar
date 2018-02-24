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

#include "debug.h"

#if (ENABLE_MSTV_UART_DEBUG)
#include <stdio.h>
#include <string.h>

#ifdef __AEONR2__
//#include "risc32_spr.h"
//#include "mhal_arch.h"
#include "r2_backtrace.h"
#endif

#include "hal_misc.h"

#include "DemoFineTune.h"

#include "drvUartDebug.h"
#include "msIR.h"
#include "MApp_IR.h"
#include "msAPI_Timer.h"

// Common Definition
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Ace.h"
#include "msAPI_Global.h"
#include "apiXC_Sys.h"

#if(!BLOADER)
#include "msAPI_VD.h"
#endif

#include "msAPI_DB_CH.h"
#include "msAPI_DB_Factory.h"
#include "msAPI_DTV_DB_Dump.h"
#include "msAPI_ChProc.h"

#if(ENABLE_TEST_PATTERN)
#include "msAPI_TestPattern.h"
#endif

#include "msAPI_Demod.h"
#include "msAPI_Flash.h"


#include "MApp_GlobalSettingSt.h"
#include "MApp_InputSource.h"
#include "MApp_ChannelChange.h"

#include "MApp_RestoreToDefault.h"
#include "MApp_SaveData.h"
#include "MApp_DataBase_Factory.h"
#include "MApp_DataBase_CH.h"

#if (HDCP_KEY_TYPE==HDCP_KEY_IN_DB || (HDCP22_KEY_TYPE==HDCP22_KEY_IN_DB))
#include "MApp_DataBase.h"
#include "drvPWM.h"
#endif

#include "msAPI_MIU.h"
#include "GPIO.h"
#include "drvGPIO.h"
#include "drvMVOP.h"
#include "drvGlobal.h"
#include "apiGOP.h"
#include "drvMIU.h"
#if (ENABLE_DMP)
#include "mapp_videoplayer.h"
#endif

#if(FRONTEND_TUNER_TYPE== MSTAR_AVATAR2) //   SEC_DTOS403IR121B//LG_TDTC_G311D_TUNER//MSTAR_AVATAR2
#include "drvIIC.h"
#include "MSTAR_AVATAR2.h"
#include "MApp_TopStateMachine.h"
#endif

#ifndef ATSC_SYSTEM
#include "MApp_ZUI_Main.h"
#include "MApp_Menu_Main.h"
#endif

#if (CHANNEL_SCAN_AUTO_TEST)
#include "msAPI_FreqTableDTV.h"
#include "apiVDEC.h"
#include "msAPI_Video.h"
#include "MApp_TopStateMachine.h"
#include "MApp_GlobalSettingSt.h"
#include "drvDMD_DTMB.h"
#include "MApp_CADTV_Proc.h"
#endif


#if(!BLOADER)
#include "mapp_videoplayer.h"
#include "color_reg.h"
#include "drvPQ.h"
#endif


#if (OTHER_TUNER_DEBUG==1)
#include "tuner.h"
BOOLEAN devCOFDM_PassThroughI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
#endif


#if ENABLE_SECURITY_R2_HDCP22
#include "msAPI_SecurityR2.h"
#endif


#if ENABLE_DVB_T2
#include "demodulator_T2.h"
#endif

#if(ENABLE_ATSC)
#include "msAPI_Tuner_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"
#endif
#include "MApp_SignalMonitor.h"
#include "MApp_Scaler.h"
#include "MApp_PCMode.h"

#if( LD_ENABLE)
#include "mdrv_ldm_dma.h"
#include "mhal_ld.h"
#endif

#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

#if(ENABLE_ATSC)
#include "MApp_Psip.h"
#endif

//==========================================================================

#if(BLOADER)
    #define ENABLE_CUS_UART_TEST_COMMAND    0

#elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)     \
  || (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)     \
  || (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)    \
  || (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)  \
  || (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
  || (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)    \
  || (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)    \
  || (CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)    \
  || (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)    \
  )
    #define ENABLE_CUS_UART_TEST_COMMAND    1
#else

    #define ENABLE_CUS_UART_TEST_COMMAND    0
#endif

#define ENABLE_TEST_CMD_AUDIO       0
#define ENABLE_TEST_CMD_DATA_BASE   0
#define ENABLE_TEST_CMD_DMP         0
#define ENABLE_TEST_CMD_GPIO        0
#define ENABLE_TEST_CMD_HDCP        0
#define ENABLE_TEST_CMD_OSD         0

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)
    #define ENABLE_TEST_CMD_SCALER      1
#else
    #define ENABLE_TEST_CMD_SCALER      0
#endif

//===========================================================================

#if (CHANNEL_SCAN_AUTO_TEST)
ScanAutoTestData g_ScanAutoTestData; // = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
U8               g_u8ScanAutoTestCmd=0;
U8               g_u8AUDbgCmd=0;
ScanAutoTestAU   g_ScanAutoTestAU = {0, 0, 0};
U8               g_u8ScanAutoTestKey = 0;
U8               g_u8TopStateChkCase = 0;
MS_TP_SETTING stTpSettingPC;
#define CHSCANTEST_MSG(x)    x
#else
#define CHSCANTEST_MSG(x)
#endif

#if DEBUG_AUDIO_DETECT_TIME
extern U8 g_u8WaitAudioTime;
#endif

//=============================================================

#include "./UartDebug/uartDebug_CPU.c"
#include "./UartDebug/uartDebug_Tuner.c"

#if(ENABLE_ATSC_TTS)
#include "./UartDebug/uartDebug_TTS.c"
#endif

#if(ENABLE_CONSOLE_CMD)
#include "./UartDebug/uartDebug_Console.c"
#endif

//=============================================================

#if ENABLE_USB_DOWNLOAD_HDCPKEY22_BIN
#include "MApp_USBDownload.h"
#endif

extern void HotKey_Decode(void);
extern void putcharb(MS_U8 byte);


///=================================
/// Auto Bench Feature.
/// s_Uart_DebugKey : If UART command known as an IR key. s_Uart_DebugKey
///                              will be set to the relative key.
/// s_Is_TTXState         : True if a TTX command is send from UART before.
///                              False when TTX disable now.
///=================================
static U8 s_Uart_DebugKey = IRKEY_DUMY;
//static U8 s_Is_TTXState = FALSE;

///=================================
///Auto Bench Feature.
///Set the key for debug. This function is used by MApp_CheckKeyStatus in Mapp_ir.c
///=================================
#if 0
BOOLEAN MsAPI_UARTDebug_GetUartKey(U8 *u8key,U8 *u8Repstatus)
{
    /* Return False when no Debugkey detected */
    if (s_Uart_DebugKey == IRKEY_DUMY) return FALSE;

    /* Return UART specification key */
    *u8key = s_Uart_DebugKey;

  #if 0
    u8Repstatus = 0;
  #else // Modified by coverity_0463
    UNUSED(u8Repstatus);
  #endif

    /* Clear DebugKey after using. */
    s_Uart_DebugKey = IRKEY_DUMY ;

    return MSRET_OK;
}
#endif

///=================================
///Auto Bench Macro.
///If Cmd then switch to Input source S
///=================================
#define autoBenchCmd_Source(Cmd,S) //ZUI_TODO:

#if ((CHANNEL_SCAN_AUTO_TEST) || (SFU_AUTO_TEST))

#if (CHANNEL_SCAN_AUTO_TEST)
MS_U16 DMD_DTMB_GetPacketErr(void)
{
    MS_U16 u16Err = 0;
    MS_U8 data, data1;

    MDrv_DMD_DTMB_SetReg(0x2F14, 0x01);
    do
    {
        MDrv_DMD_DTMB_GetReg(0x2F14, &data);
    } while(!(data&0x02));

    MDrv_DMD_DTMB_GetReg(0x2F14, &data);
    MDrv_DMD_DTMB_GetReg(0x20C1, &data1);

    if ((data&0x10) || (data1 != 0xF0))
    {
        u16Err = 1;
    }
    else
    {
        u16Err = 0;
    }
    return u16Err;
}
#endif

extern MS_BOOL MDrv_DMD_DVBS_GetPacketErr(MS_U16 *pktErr);
void Cus_UART_Scan(void)
{
    switch(UART_EXT_CMD)
    {
    case UART_SCAN_CMD_SET_TUNE_TO_RFCH:
      #if 0
        //stTpSetting.u32Frequency = (*(U32*)&UART_SCAN_DATA1);
        {
            U32 u32Data;

            u32Data = (g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            u32Data = g_UartCommand.Buffer[_UART_CMD_INDEX5_]| (u32Data<<8);
            u32Data = g_UartCommand.Buffer[_UART_CMD_INDEX6_]| (u32Data<<8);
            u32Data = g_UartCommand.Buffer[_UART_CMD_INDEX7_]| (u32Data<<8);
            printf("RRR-1: UART_SCAN_DATA1 = 0x%bx,0x%bx, 0x%bx, 0x%bx, 0x%lx,  \n"
                     ,g_UartCommand.Buffer[_UART_CMD_INDEX4_]
                     ,g_UartCommand.Buffer[_UART_CMD_INDEX5_]
                     ,g_UartCommand.Buffer[_UART_CMD_INDEX6_]
                     ,g_UartCommand.Buffer[_UART_CMD_INDEX7_],u32Data);
            stTpSettingPC.u32Frequency =  u32Data;
            printf("RRR-2: stTpSettingPC.u32Frequency = %lu \n",stTpSettingPC.u32Frequency);
        }
        stTpSettingPC.enBandWidth = (RF_CHANNEL_BANDWIDTH)UART_SCAN_DATA5;
        #if 1
        MApp_TopStateMachine_SetTopState(STATE_TOP_DTV_SCAN);
        g_enScanType = SCAN_TYPE_MANUAL;
        #else
        msAPI_Tuner_Tune2RfCh(&stTpSettingPC);
        #endif
        printf("OK\n");
      #else
        {
            MS_U32 u32Data;
            MS_BOOL bRet = true;
            U32  u32Symbolrate = 0;
        #if ENABLE_S2
            CofdmDMD_Param pParam;
        #endif
            UNUSED(u32Symbolrate);

            // need to get these value from uart buffer.
            //MS_U8   Qammode = 0xff;
            //MS_U32  u32Symbolrate = 0; // KS/s


            u32Data = (g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            u32Data = g_UartCommand.Buffer[_UART_CMD_INDEX5_] | (u32Data << 8);
            u32Data = g_UartCommand.Buffer[_UART_CMD_INDEX6_] | (u32Data << 8);
            u32Data = g_UartCommand.Buffer[_UART_CMD_INDEX7_] | (u32Data << 8);

            stTpSettingPC.u32Frequency =  u32Data;
            stTpSettingPC.enBandWidth = (RF_CHANNEL_BANDWIDTH)UART_SCAN_DATA5;
            //msAPI_Tuner_Tune2RfCh(&stTpSetting);
            //m_pcFE->Set(u32Frequency, enBandWidth);
        #if 1
            switch(UART_EXT_CMD_MS_DAT6)
            {
              #if( ENABLE_DVBT)
                case E_DEMOD_DVBT:
                {
                    devCOFDM_SetFrequency(stTpSettingPC.u32Frequency,stTpSettingPC.enBandWidth, E_RF_CH_HP, 0);
                }
                break;
              #endif

              #if ENABLE_DVB_T2
                case E_DEMOD_DVBT2:
                {
                    ICE_TuneToParams pstT2Setting;

                    pstT2Setting.channel_frequency_khz = stTpSettingPC.u32Frequency;
                    pstT2Setting.network_type = ICE_network_dvbt2;

                    mdev_CofdmSetFrequency(&pstT2Setting,stTpSettingPC.enBandWidth);
                }
                break;
              #endif

              #if ENABLE_DTMB
                case E_DEMOD_DTMB:
                {
                    stTpSettingPC.u32Frequency =  stTpSettingPC.u32Frequency/1000;
                    devCOFDM_SetFrequency(stTpSettingPC.u32Frequency,stTpSettingPC.enBandWidth, E_RF_CH_HP, 0);
                }
                break;
              #endif

            #if ENABLE_S2
                case E_DEMOD_DVBS:
                case E_DEMOD_DVBS2:
                {
                    u32Data = UART_EXT_CMD_MS_DAT7;
                    u32Data = UART_EXT_CMD_MS_DAT8 | (u32Data << 8);
                    u32Data = UART_EXT_CMD_MS_DAT9 | (u32Data << 8);
                    u32Data = UART_EXT_CMD_MS_DAT10 | (u32Data << 8);
                    if (u32Data <=50000)  //DVBS Max symbolrate
                    {
                        u32Symbolrate  = u32Data;
                    }
                    stTpSettingPC.u32Frequency =  stTpSettingPC.u32Frequency;
                    pParam.u32SymbolRate = u32Symbolrate * 1000;
                    pParam.u32TunerFreq = stTpSettingPC.u32Frequency;
                    pParam.u8BandWidth = 0;
                    MDrv_CofdmDmd_Restart(&pParam);
                }
                break;
            #endif

            #if ENABLE_DVBC
                case E_DEMOD_DVBC:
                {
                    MS_TP_SETTING pstTPSetting;

                    u32Data = UART_EXT_CMD_MS_DAT7;
                    u32Data = UART_EXT_CMD_MS_DAT8 | (u32Data << 8);
                    u32Data = UART_EXT_CMD_MS_DAT9 | (u32Data << 8);
                    u32Data = UART_EXT_CMD_MS_DAT10 | (u32Data << 8);
                    if (u32Data <=50000)  //DVBC Max symbolrate
                    {
                        u32Symbolrate  = u32Data;
                    }

                    pstTPSetting.u32Symbol_rate = u32Symbolrate * 1000; //DEFAULT_DVBC_CHINA_SYMBOL_RATE    //MApp_CadtvManualTuning_GetSymbol();
                    pstTPSetting.u8Modulation = CAB_QAM64; //(U8)MApp_CadtvManualTuning_GetQamType();
                    pstTPSetting.bAutoSRFlag = 0;
                    pstTPSetting.bAutoQamFlag = 0;

                    devQAM_SetFrequency(stTpSettingPC.u32Frequency, pstTPSetting.u8Modulation, pstTPSetting.u32Symbol_rate, TRUE, (U8)pstTPSetting.bAutoSRFlag, (U8)pstTPSetting.bAutoQamFlag);
                }
                break;
            #endif

            #if ENABLE_ISDBT
                case E_DEMOD_ISDBT:
                {
                    devCOFDM_SetFrequency(stTpSettingPC.u32Frequency,stTpSettingPC.enBandWidth, E_RF_CH_HP, 0);
                }
                break;
            #endif

              #if 0
                case E_DEMOD_DVBC:
                {
                    // default :auto symbol rate(0x00) & auto qam mode(0xff).
                    u32Data = UART_EXT_CMD_MS_DAT7;
                    u32Data = UART_EXT_CMD_MS_DAT8 | (u32Data << 8);
                    u32Data = UART_EXT_CMD_MS_DAT9 | (u32Data << 8);
                    u32Data = UART_EXT_CMD_MS_DAT10 | (u32Data << 8);
                    if (u32Data <= 10000)  //DVBC Max symbolrate
                    {
                        u32Symbolrate  = u32Data;
                    }
                    if (UART_EXT_CMD_MS_DAT5 < E_CAB_INVALID)  //Qammode = E_CAB_INVALID
                    {
                        Qammode = UART_EXT_CMD_MS_DAT5;
                    }
                    devQAM_SetFrequency(stTpSettingPC.u32Frequency,stTpSettingPC.enBandWidth, u32Symbolrate, D_DMD_TUNER_IQSWAP, TRUE, Qammode);
                }
                break;
                case E_DEMOD_ISDBT:
                {
                    pcTuner = mapi_pcb::GetInstance()->GetIsdbTuner(0);
                    pcDemod = mapi_pcb::GetInstance()->GetIsdbDemod(0);
                    mapi_pcb::GetInstance()->EnableTunerI2cPath(TRUE);
                    bRet &= pcTuner->DTV_SetTune((double) u32Frequency / 1000, enBandWidth, E_TUNER_DTV_ISDB_MODE);
                    mapi_pcb::GetInstance()->EnableTunerI2cPath(FALSE);
                    bRet &= pcDemod->DTV_SetFrequency(u32Frequency, enBandWidth, MAPI_FALSE);
                    ASSERT(pcTuner);
                }
                break;
                case E_DEMOD_DVBS:
                case E_DEMOD_DVBS2:
                {
                    // dvbs driver layer controlled the tuner directly.
                    //pcTuner = mapi_pcb::GetInstance()->GetDvbsTuner(0);
                    pcDemod = mapi_pcb::GetInstance()->GetDvbsDemod(0);
                    u32Data = UART_EXT_CMD_MS_DAT7;
                    u32Data = UART_EXT_CMD_MS_DAT8 | (u32Data << 8);
                    u32Data = UART_EXT_CMD_MS_DAT9 | (u32Data << 8);
                    u32Data = UART_EXT_CMD_MS_DAT10 | (u32Data << 8);
                    if (u32Data <=50000)  //DVBS Max symbolrate
                    {
                        u32Symbolrate  = u32Data;
                    }
                    bRet &= pcDemod->DTV_DVB_S_SetFrequency(u32Frequency, u32Symbolrate);
                }
                break;
                case E_DEMOD_ATSC:
                {
                    pcTuner = mapi_pcb::GetInstance()->GetAtscTuner(0);
                    pcDemod = mapi_pcb::GetInstance()->GetAtscDemod(0);
                    mapi_pcb::GetInstance()->EnableTunerI2cPath(TRUE);
                    bRet &= pcTuner->DTV_SetTune((double) u32Frequency / 1000, enBandWidth, E_TUNER_DTV_ATSC_MODE);
                    mapi_pcb::GetInstance()->EnableTunerI2cPath(FALSE);
                    // atsc auto qam.
                    if ((UART_EXT_CMD_MS_DAT5 >= mapi_demodulator_datatype::E_DEVICE_DEMOD_ATSC) && (UART_EXT_CMD_MS_DAT5 <= mapi_demodulator_datatype::E_DEVICE_DEMOD_ATSC_256QAM)) //Qammode = ATSC type
                    {
                        Qammode = UART_EXT_CMD_MS_DAT5;
                    }
                    else
                    {
                        Qammode = mapi_demodulator_datatype::E_DEVICE_DEMOD_ATSC_VSB;  //default to 8VBS
                    }
                    bRet &= pcDemod->DTV_ATSC_ChangeModulationMode((mapi_demodulator_datatype::EN_DEVICE_DEMOD_TYPE )Qammode);
                    pcDemod->Reset();
                    bRet &= pcDemod->Active(MAPI_TRUE);
                    ASSERT(pcTuner);
                }
                break;
              #endif

                default:
                {
                    ASSERT(0);
                }
                break;
            }
        #else
          #if 0
            MApp_TopStateMachine_SetTopState(STATE_TOP_DTV_SCAN);
            g_enScanType = SCAN_TYPE_MANUAL;
          #else
            msAPI_Tuner_Tune2RfCh(&stTpSettingPC);
          #endif
        #endif

            printf("u32Frq= %ld eBw = %d \n", stTpSettingPC.u32Frequency, stTpSettingPC.enBandWidth + 5);
            if (bRet == TRUE)
            {
                printf("OK\n");
            }
            else
            {
                printf("Set Demod frequency failed\n");
            }
        }
      #endif
        break;


    case UART_SCAN_CMD_RETURN_TYPE:
        #if ENABLE_ATSC
        printf("%02bx %02bx\n", (0xC0 | FRONTEND_DEMOD_ATSC_TYPE),FRONTEND_TUNER_TYPE);
        #elif ENABLE_DVBT
        printf("%02bx %02bx\n", (0xC0 | FRONTEND_DEMOD_DVBT_TYPE),FRONTEND_TUNER_TYPE);
        #elif ENABLE_DVB_T2
        printf("%02bx %02bx\n", (0xC0 | FRONTEND_DEMOD_T2_TYPE),FRONTEND_TUNER_TYPE);
        #elif ENABLE_DTMB
        printf("%02bx %02bx\n", (0xC0 | FRONTEND_DEMOD_DTMB_TYPE),FRONTEND_TUNER_TYPE);
        #elif ENABLE_DVBC
        printf("%02bx %02bx\n", (0xC0 | FRONTEND_DEMOD_DVBC_TYPE),FRONTEND_TUNER_TYPE);
        #elif ENABLE_ISDBT
        printf("%02bx %02bx\n", (0xC0 | FRONTEND_DEMOD_ISDBT_TYPE),FRONTEND_TUNER_TYPE);
        #elif ENABLE_S2
        printf("%02bx %02bx\n", (0xC0 | FRONTEND_DEMOD_TYPE),FRONTEND_TUNER_TYPE);
        #else
        printf("%02bx %02bx\n", (0xC0 | FRONTEND_DEMOD_S2_TYPE),FRONTEND_TUNER_S2_TYPE);
        #endif
        break;

#if (CHANNEL_SCAN_AUTO_TEST)
        case UART_SCAN_CMD_LOCK_STATE:
        {
            MS_BOOL bCheckLockResult=FALSE;

            msAPI_Tuner_CheckLock(&bCheckLockResult,FALSE);

            if (bCheckLockResult)
            {
                putcharb(0xF3);
                printf("OK\n");
            }
            else
            {
                putcharb(0xF3);
                printf("err\n");
            }
        }
            break;


        case UART_SCAN_CMD_CHECK_PACKET_ERR:
        {
            MS_U16 u16Err = 0;
            #if 1
            switch(UART_EXT_CMD_MS_DAT1)
            {
              #if( ENABLE_DVBT)
                case E_DEMOD_DVBT:
                {
                    u16Err = devCOFDM_GetPacketError();
                }
                break;
              #endif

              #if ENABLE_DVB_T2
                case E_DEMOD_DVBT2:
                {
                    u16Err = mdev_CofdmGetPacketErr();
                }
                break;
              #endif

              #if ENABLE_S2
                case E_DEMOD_DVBS:
                case E_DEMOD_DVBS2:
                {
                    MDrv_DMD_DVBS_GetPacketErr(&u16Err);
                }
                break;
              #endif

              #if ENABLE_DTMB
                case E_DEMOD_DTMB:
                {
                    u16Err = DMD_DTMB_GetPacketErr();
                }
                break;
              #endif

              #if ENABLE_DVBC
                case E_DEMOD_DVBC:
                {
                    MDrv_DMD_DVBC_GetPacketErr(&u16Err);
                }
                break;
              #endif

              #if ENABLE_ISDBT
                case E_DEMOD_ISDBT:
                {
                    MDrv_DMD_ISDBT_Read_PKT_ERR(E_ISDBT_Layer_A, &u16Err);
                }
                break;
              #endif

              #if 0
                case E_DEMOD_DVBC:
                {
                    bCheckLockResult = devQAM_GetLockStatus(QAM_FEC_LOCK);
                }
                break;
                case E_DEMOD_ISDBT:
                {

                }
                break;
                case E_DEMOD_DVBS:
                case E_DEMOD_DVBS2:
                {

                }
                break;
                case E_DEMOD_DTMB:
                {

                }
                break;
                case E_DEMOD_ATSC:
                {

                }
                break;
              #endif

                default:
                {
                    ASSERT(0);
                }
                break;
            }
            #else
            msAPI_Tuner_CheckLock(&bCheckLockResult,FALSE);
            #endif
            if (u16Err==0)
            {
                    putcharb(0xF3);
                    printf("OK\n");
            }
            else
            {
                    putcharb(0xF3);
                    printf("err\n");
            }
        }
            break;


    case UART_SCAN_CMD_SET_CH_CNT:
        g_ScanAutoTestData.u12ChNum = UART_SCAN_DATA1; //*(U16*)&UART_SCAN_DATA1;
        CHSCANTEST_MSG(printf("SCAN: u12ChNum=%d\n", g_ScanAutoTestData.u12ChNum));
        break;
    case UART_SCAN_CMD_SET_ANT:
        g_ScanAutoTestData.f8Antenna = UART_SCAN_DATA1;
        CHSCANTEST_MSG(printf("SCAN: f8Antenna=%x\n", g_ScanAutoTestData.f8Antenna));
        break;
    case UART_SCAN_CMD_SET_CABLE_SYSTEM:
        g_ScanAutoTestData.u2CableSystem = UART_SCAN_DATA1;
        CHSCANTEST_MSG(printf("SCAN: u2CableSystem=%x\n", g_ScanAutoTestData.u2CableSystem));
        break;
    case UART_SCAN_CMD_START:
        if(g_ScanAutoTestData.u12ChNum)
        {
            g_u8ScanAutoTestCmd = 0;
            g_ScanAutoTestData.u16SrvFoundNum = 0;
            g_ScanAutoTestData.u12ChFoundNum = 0;
            g_ScanAutoTestData.fCommand = 1;
            g_ScanAutoTestData.u2State = 0; // start scan
            CHSCANTEST_MSG(printf("SCAN: Scan test start (%x, %x, %x)!\n",
                   g_ScanAutoTestData.u12ChNum,
                   g_ScanAutoTestData.f8Antenna,
                   g_ScanAutoTestData.u2CableSystem));
        }
        break;
    case UART_SCAN_CMD_END:
        g_ScanAutoTestData.fCommand = 0;                // Stop scan
        //CHSCANTEST_MSG(printf("SCAN: Stop Scan!\n"));
        break;
    case UART_SCAN_CMD_POLL:
        //CHSCANTEST_MSG(printf("SCAN: %bu %bu\n", u8RFCh, 69/*MAX_UHF_PHYSICAL_CHANNEL_NUMBER*/));
        g_u8ScanAutoTestCmd |= SCAN_AUTOTEST_CMD_POLL;
        break;
    case UART_SCAN_CMD_READ_FOUND_CH_NUM:
        CHSCANTEST_MSG(printf("SCAN: Found channels %u\n", g_ScanAutoTestData.u12ChFoundNum));
        break;
    /*            case UART_SCAN_CMD_READ_SRV_INFO:
        g_u8ScanAutoTestCmd |= SCAN_AUTOTEST_CMD_DUMP_CH_INFO;
        break;*/
    case UART_SCAN_CMD_READ_ONE_SRV_INFO:
        g_ScanAutoTestData.u12ChNum = UART_SCAN_DATA1; //*(U16*)&UART_SCAN_DATA1;
        g_u8ScanAutoTestCmd |= SCAN_AUTOTEST_CMD_DUMP_ONE_CH_INFO;
        break;
    case UART_SCAN_CMD_READ_ONE_SRV_INFO2:
        g_u8ScanAutoTestCmd |= SCAN_AUTOTEST_CMD_DUMP_ONE_CH_INFO2;
        break;
    case UART_SCAN_CMD_SET_PLUSCHANGE_ONE_CH:
        g_u8ScanAutoTestCmd |= SCAN_AUTOTEST_CMD_PLUSCHANGE_ONE_CH;
        break;
    case UART_SCAN_CMD_READ_MAINSTATE:
        g_u8ScanAutoTestCmd |= SCAN_AUTOTEST_CMD_DUMP_MAINSTATE;
        break;
    case UART_SCAN_CMD_SET_KEYVALUE:
        g_u8ScanAutoTestKey = UART_SCAN_DATA1;
        CHSCANTEST_MSG(printf("SCAN: Key 0x%02bx\n", g_u8ScanAutoTestKey));
        g_u8ScanAutoTestCmd |= SCAN_AUTOTEST_CMD_SETKEY;
        break;
    case UART_SCAN_CMD_CHK_MAINSTATE:
        g_u8TopStateChkCase = UART_SCAN_DATA1;
        g_u8ScanAutoTestCmd |= SCAN_AUTOTEST_CMD_CHK_MAINSTATE;
        break;
    case UART_SCAN_CMD_READ_FOUND_SRV_NUM:
            CHSCANTEST_MSG(printf("SCAN: Found service %u %u %u %u\n", g_ScanAutoTestData.u16SrvFoundNum,
                                        g_ScanAutoTestData.u16DTVProgNum,
                                        g_ScanAutoTestData.u16ATVProgNum,
                                        g_ScanAutoTestData.u16AudioProgNum));
        break;
    case UART_SCAN_CMD_SET_TUNER:
        CHSCANTEST_MSG(printf("OK\n"));
        break;
#endif
    }

}
#endif


void Cus_UART_DecodeExtCommand(void)
{
    switch( UART_EXT_DEV )
    {
#if (OTHER_TUNER_DEBUG==1)
    case uartExtDev_Other_Tuner_Debug: //Set Tuner PLL
        {
            U8 u8Temp;
            u8Temp = g_UartCommand.Buffer[4];
            g_UartCommand.Buffer[4]=g_UartCommand.Buffer[5];
            g_UartCommand.Buffer[5]=u8Temp;
            if ((g_UartCommand.Buffer[4]==0)&&(g_UartCommand.Buffer[5]==0))
            {//For Dino's request
                devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 2, &(g_UartCommand.Buffer[6]));
            }
            else
                devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, &(g_UartCommand.Buffer[4]));
        }
     break;
#endif

#if ((CHANNEL_SCAN_AUTO_TEST) || (SFU_AUTO_TEST))
    case uartExtDev_SCAN_TUNER:
        Cus_UART_Scan();
        break;

#if (CHANNEL_SCAN_AUTO_TEST)
    case uartExtDev_AUDIO_DEBUG:
        switch(UART_EXT_CMD)
        {
        case UART_AUDIODBG_CMD_SET_BK9:
            g_ScanAutoTestAU.u8RegStartAddr = UART_AUDIO_DATA1;
            g_ScanAutoTestAU.u8WriteData = UART_AUDIO_DATA2;
            g_ScanAutoTestAU.u8ReadBytes = UART_AUDIO_DATA3;
            g_u8AUDbgCmd |= AUDIO_DEBUG_CMD_RWREG;
            break;
        }
        break;
#endif
#endif
         ///==============================================
         ///    UART_EXT_DEV macro defines the command types.
         ///    UART_EXT_CMD macro defines the commands of types defined by
         ///    UART_EXT_DEV.
         ///    The type of AutoBench command.
         ///    Before swithing to another input source. We must confirm that the TTX
         ///    is disabled. Otherwise we do nothing.
         ///==============================================
         case uartExtDev_MstAutoBench:
         {
            switch ((EN_AutoBenchCmd)UART_EXT_CMD)
            {
                /* Switch to HDMI*/
                #if(INPUT_HDMI_VIDEO_COUNT>0)
                autoBenchCmd_Source(EN_AutoBenchCmd_HDMI1,UI_INPUT_SOURCE_HDMI);
                #endif

                #if(INPUT_HDMI_VIDEO_COUNT>1)
                autoBenchCmd_Source(EN_AutoBenchCmd_HDMI2,UI_INPUT_SOURCE_HDMI2);
                #endif

                #if(INPUT_HDMI_VIDEO_COUNT>2)
                autoBenchCmd_Source(EN_AutoBenchCmd_HDMI3,UI_INPUT_SOURCE_HDMI3);
                #endif
                #if(INPUT_HDMI_VIDEO_COUNT>3)
                autoBenchCmd_Source(EN_AutoBenchCmd_HDMI4,UI_INPUT_SOURCE_HDMI4);
                #endif

                /* Switch to Component */
                #if (INPUT_YPBPR_VIDEO_COUNT >0)
                autoBenchCmd_Source(EN_AutoBenchCmd_YPbPr1,UI_INPUT_SOURCE_COMPONENT);
                #endif

                #if (INPUT_YPBPR_VIDEO_COUNT >1)
                autoBenchCmd_Source(EN_AutoBenchCmd_YPbPr2,UI_INPUT_SOURCE_COMPONENT2);
                #endif

                /* Switch to Svideo */
                #if (INPUT_SV_VIDEO_COUNT > 0)    //ms042H_d02B has no svideo input
                autoBenchCmd_Source(EN_AutoBenchCmd_Svideo1,UI_INPUT_SOURCE_SVIDEO);
                #endif

                #if ((INPUT_SCART_USE_SV2 == 0) && (INPUT_SV_VIDEO_COUNT > 1))    //ms042H_d02B has no svideo input
                autoBenchCmd_Source(EN_AutoBenchCmd_Svideo2,UI_INPUT_SOURCE_SVIDEO2);
                #endif

                /* Switch to AV */
                #if (INPUT_AV_VIDEO_COUNT > 0)   //ms042H_d02B has no AV input
                autoBenchCmd_Source(EN_AutoBenchCmd_CVBS1,UI_INPUT_SOURCE_AV);
                #endif

                #if (INPUT_AV_VIDEO_COUNT > 1)   //ms042H_d02B has no AV input
                autoBenchCmd_Source(EN_AutoBenchCmd_CVBS2,UI_INPUT_SOURCE_AV2);
                #endif

                /* Switch to SCART */
                #if (INPUT_SCART_VIDEO_COUNT > 0 )
                autoBenchCmd_Source(EN_AutoBenchCmd_SCART1,UI_INPUT_SOURCE_SCART);
                #endif

                #if (INPUT_SCART_VIDEO_COUNT > 1)
                autoBenchCmd_Source(EN_AutoBenchCmd_SCART2,UI_INPUT_SOURCE_SCART2);
                #endif
                /* Switch to PC - VGA */
                autoBenchCmd_Source(EN_AutoBenchCmd_RGB,UI_INPUT_SOURCE_RGB);

                /* Switch to DTV */
                autoBenchCmd_Source(EN_AutoBenchCmd_DTV,UI_INPUT_SOURCE_DTV);

                /* Switch to TV */
                autoBenchCmd_Source(EN_AutoBenchCmd_TV,UI_INPUT_SOURCE_ATV);
                /* simulate IR key */
                case EN_AutoBenchCmd_OSD:
                         s_Uart_DebugKey = IRKEY_MENU;
                    break;

                case EN_AutoBenchCmd_TTX:
                         s_Uart_DebugKey = IRKEY_TTX;
                    break;

                case EN_AutoBenchCmd_Exit:
                         s_Uart_DebugKey = IRKEY_EXIT;
                    break;

                default:
                    //printf(" Undefinded command or no this input source. \n");
                    break;

            }
         }

         default:
             break;
    }
}

#if 0
void Cus_UART_AutoAdjWBTool(void)
{
    U8 i;
    #if 0
    printf("\n\r ===================");
    printf("\n\r Detect UART0 :");
    for (i=0;i<_UART_CMD_LENGTH_;i++)
    {
        if(i%5==0) printf("\n\r");
        printf(" 0x%02bx", g_UartCommand.Buffer[i]);
    }
    printf("\n\r ===================");
    #endif

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX1_] )
    {
        case 0x40:
            MApp_DataBase_RestoreDefaultWhiteBalance(DATA_INPUT_SOURCE_NUM);
            break;

        case 0x41:
#if (INPUT_AV_VIDEO_COUNT > 0)
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV;
            MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
#endif
            break;

        case 0x42:
            ST_PICTURE.eColorTemp=MS_COLOR_TEMP_MEDIUM;
            MApp_PQ_Set_ColorTemp(MAIN_WINDOW);
            break;

        case 0x43:
            if(g_UartCommand.Buffer[_UART_CMD_INDEX2_]>0x1f)
            {
                g_UartCommand.Buffer[_UART_CMD_INDEX2_]=0x1f;
            }
            //XBYTE[0x1fff] |= 0x02;
            //XBYTE[0x1f0b] |= 0x3F;
            break;

        case 0x44:
            break;

        case 0x45:
            //printf("\n CMD(0x42) Adjust R(0x%bx) G(0x%bx) B(0x%bx)", g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
//            MDrv_ACE_AdjustVideoRGB(g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            break;

        case 0x46:
            {
#if (INPUT_AV_VIDEO_COUNT > 0)
                U8 j;
                S16 r_offset, g_offset, b_offset;

                r_offset=g_UartCommand.Buffer[_UART_CMD_INDEX2_]-G_WHITE_BALANCE_SETTING[UI_INPUT_SOURCE_AV].astColorTemp[MS_COLOR_TEMP_MEDIUM].cRedColor;
                g_offset=g_UartCommand.Buffer[_UART_CMD_INDEX3_]-G_WHITE_BALANCE_SETTING[UI_INPUT_SOURCE_AV].astColorTemp[MS_COLOR_TEMP_MEDIUM].cGreenColor;
                b_offset=g_UartCommand.Buffer[_UART_CMD_INDEX4_]-G_WHITE_BALANCE_SETTING[UI_INPUT_SOURCE_AV].astColorTemp[MS_COLOR_TEMP_MEDIUM].cBlueColor;
                for(i = DATA_INPUT_SOURCE_MIN; i < DATA_INPUT_SOURCE_NUM; i++)
                {
                    for(j=MS_COLOR_TEMP_MIN;j<MS_COLOR_TEMP_MAX;j++)
                    {
                        G_WHITE_BALANCE_SETTING[i].astColorTemp[j].cRedColor += r_offset;
                        G_WHITE_BALANCE_SETTING[i].astColorTemp[j].cGreenColor += g_offset;
                        G_WHITE_BALANCE_SETTING[i].astColorTemp[j].cBlueColor += b_offset;
                    }
                    MApp_SaveWhiteBalanceSetting( (E_DATA_INPUT_SOURCE) i);
                }
#endif
            }
            break;
    }

}
#endif


#if( ENABLE_CUS_UART_TEST_COMMAND )
static U8 s_u8UartDebug_McuPauseFlag = 0;

#define XC_RIU_BASE     0x102F00
U8 XC_BK_ReadByte(U8 u8Bank, U8 u8Addr )
{
    MDrv_WriteByte(XC_RIU_BASE, u8Bank);
    return MDrv_ReadByte(XC_RIU_BASE+u8Addr);
}
U16 XC_BK_Read2Byte(U8 u8Bank, U8 u8Addr )
{
    MDrv_WriteByte(XC_RIU_BASE, u8Bank);
    return MDrv_Read2Byte(XC_RIU_BASE+u8Addr);
}
U32 XC_BK_Read3Byte(U8 u8Bank, U8 u8Addr )
{
    MDrv_WriteByte(XC_RIU_BASE, u8Bank);
    return MDrv_Read3Byte(XC_RIU_BASE+u8Addr);
}
U32 XC_BK_Read4Byte(U8 u8Bank, U8 u8Addr )
{
    MDrv_WriteByte(XC_RIU_BASE, u8Bank);
    return MDrv_Read4Byte(XC_RIU_BASE+u8Addr);
}

#if( ENABLE_TEST_CMD_SCALER )
void TestCommand_Scaler(void)
{
    BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    //BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];
    INPUT_SOURCE_TYPE_t enInputSourceType = stSystemInfo[MAIN_WINDOW].enInputSourceType;


    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        default:
            printf("\n *** Sclaer Test Command List: *** \n");
            printf("01: Get input sync status\n");
            printf("02: Get in/out sync status\n");
            printf("09: Get SarAdcLevel,GetScart?IDLevel()\n");
            printf("10: Change input source\n");
            printf("20: ACE");
            break;


        case 0x01:
            printf("*** Scale info ===================================== \n\n");

            if( IsSrcTypeDigitalVD(enInputSourceType) )
            {
                // VD info ...
                msAPI_AVD_PrintInfo();
            }
            else if( IsSrcTypeDTV(enInputSourceType)||IsSrcTypeStorage(enInputSourceType) )
            { // MVOP ...
                MS_BOOL bMvopEn = FALSE;
                MVOP_Result mvop_rtn;

                mvop_rtn = MDrv_MVOP_GetIsEnable(&bMvopEn);
                if( (mvop_rtn == E_MVOP_OK) && bMvopEn )
                {
                    MVOP_Timing mvopTiming;

                    if( E_MVOP_OK == MDrv_MVOP_GetOutputTiming(&mvopTiming) )
                    {
                        U16 u16Mvop_20_40;
                        printf(" [MVOP] ---------------------------- \n" );

                        u16Mvop_20_40 = MDrv_Read2Byte(0x101440);
                        printf(" DC mode = %X\n", (u16Mvop_20_40&3));
                        if( (u16Mvop_20_40&3)== 2 ) // MCU ctrl
                            printf("  [MCUCTRL]\n");

                        printf(" interlace = %d, ExpFrameRate = %d\n", mvopTiming.bInterlace, mvopTiming.u16ExpFrameRate);
                        printf(" HT = %d, VT = %d \n", mvopTiming.u16H_TotalCount, mvopTiming.u16V_TotalCount);
                        printf(" HF = %d, VF = %d \n", mvopTiming.u16H_Freq, mvopTiming.u8Framerate);
                        printf(" Width = %d, Height = %d\n", mvopTiming.u16Width, mvopTiming.u16Height );
                        printf(" HStart = 0x%X, VStart = 0x%X\n", MDrv_MVOP_GetHStart(), MDrv_MVOP_GetVStart());
                        printf(" Yoffset = %lX, UVoffset = %lX\n", MDrv_Read4Byte(0x101442), MDrv_Read4Byte(0x101446));
                    }
                }
            }

            printf("\n");

            // Input sync ...
            {
                XC_IP_SYNC_STATUS sXC_Sync_Status;
                U16 u16HFreq_x10;
                U16 u16VFreq_x10;

                MApi_XC_GetSyncStatus(enInputSourceType, &sXC_Sync_Status, MAIN_WINDOW);
                u16HFreq_x10 = MApi_XC_CalculateHFreqx10(sXC_Sync_Status.u16Hperiod);

                u16VFreq_x10 = MApi_XC_CalculateVFreqx10(u16HFreq_x10, sXC_Sync_Status.u16Vtotal);
                if( sXC_Sync_Status.u8SyncStatus&XC_MD_INTERLACE_BIT )
                {
                    u16VFreq_x10 *= 2;
                }

                printf(" [Scaler input sync] ---------------------------- \n" );
                printf(" u8SyncStatus = 0x%X,", sXC_Sync_Status.u8SyncStatus );
                printf(" Interlace = %d\n", (sXC_Sync_Status.u8SyncStatus&XC_MD_INTERLACE_BIT)?1:0 );
                printf(" u16Hperiod = 0x%X, H_Freq_x10 = %d\n", sXC_Sync_Status.u16Hperiod, u16HFreq_x10 );
                printf(" V total = %d, V_Freq_x10 = %d\n", sXC_Sync_Status.u16Vtotal, u16VFreq_x10 );
            }

            printf("\n");
            {
#if 0
    typedef struct
    {
        //----------------------
        // Timing
        //----------------------
        MS_BOOL bInterlace;             ///<Interlaced or Progressive
        MS_BOOL bHDuplicate;            ///<flag for vop horizontal duplicate, for MVD, YPbPr, indicate input double sampled or not
        MS_U16  u16InputVFreq;          ///<Input V Frequency, VFreqx10, for calculate output panel timing
        MS_U16  u16InputVTotal;         ///<Input Vertical total, for calculate output panel timing
        MS_U16  u16DefaultHtotal;       ///<Default Htotal for VGA/YPbPr input
        MS_U8   u8DefaultPhase;         ///<Default Phase for VGA/YPbPr input

        //----------------------
        // customized scaling
        //----------------------
        MS_BOOL bHCusScaling;           ///<assign H customized scaling instead of using XC scaling
        MS_U16  u16HCusScalingSrc;      ///<H customized scaling src width
        MS_U16  u16HCusScalingDst;      ///<H customized scaling dst width
        MS_BOOL bVCusScaling;           ///<assign V manuel scaling instead of using XC scaling
        MS_U16  u16VCusScalingSrc;      ///<V customized scaling src height
        MS_U16  u16VCusScalingDst;      ///<V customized scaling dst height
        //----------------------
        // XC internal setting
        //----------------------
        /* Video screen status */
        MS_BOOL bBlackscreenEnabled;      ///<Black screen status
        MS_BOOL bBluescreenEnabled;       ///<Blue screen status
        MS_U16 u16VideoDark;            ///<Video dark
        MS_U16 u16BytePerWord;          ///<BytePerWord in Scaler
        MS_U16 u16OffsetPixelAlignment; ///<Pixel alignment of Offset (including IPM/OPM)
        MS_U8 u8DelayLines;             ///<delay lines
        MS_BOOL bMemFmt422;             ///<whether memory format is 422, for easy usage
        MS_IMAGE_STORE_FMT eMemory_FMT; ///<memory format
        MS_BOOL bUseYUVSpace;           ///< color format before 3x3 matrix
        MS_BOOL bMemYUVFmt;             ///< memroy color format
        MS_BOOL bForceRGBin;            ///<Force set format in memory as RGB (only for RGB input source)
    }XC_ApiStatus;
#endif
                XC_ApiStatus drvStatus;
                MS_WINDOW_TYPE *pCapWin, *pDispWin, *pCropWin, *pScaledCropWin;
                MS_WINDOW_TYPE capWin, dispWin;

                printf(" [XC-status]------------------------------\n");
                if (!MApi_XC_GetStatus( &drvStatus, MAIN_WINDOW))
                {
                    printf("MApi_XC_GetStatus  = 0 \n");
                }

                // Get Capture Win
                pCapWin = &(drvStatus.stCapWin);
                printf("\n [CapWin]: \n");
                printf(" CapWin     : X = 0x%X, Y = 0x%X, W = %d, H = %d\n", pCapWin->x, pCapWin->y, pCapWin->width, pCapWin->height);

                MApi_XC_GetCaptureWindow( &capWin, MAIN_WINDOW );
                printf(" RegCapWin  : X = 0x%X, Y = 0x%X, W = %d, H = %d \n", capWin.x, capWin.y, capWin.width, capWin.height);

                // Pre-Scaling
                printf("\n [Pre-Scaling]: \n");
                printf(" Pre V-down %s \n", (drvStatus.bPreV_ScalingDown?("Enable"):("Disable")));
                printf(" After Pre-H = 0x%X, After Pre-V = 0x%X \n", drvStatus.u16H_SizeAfterPreScaling, drvStatus.u16V_SizeAfterPreScaling);
                printf(" PreH Ratio  = 0x%08X, PreV Ratio  = 0x%lX \n", XC_BK_Read4Byte(0x02, 0x08), XC_BK_Read4Byte(0x02, 0x10));
                printf(" PostH Ratio = 0x%08X, PostV Ratio = 0x%lX \n", XC_BK_Read4Byte(0x23, 0x0E), XC_BK_Read4Byte(0x23, 0x12));

                // Memory ...
                printf("\n [Memory]: \n");
                printf(" Frame Buffer%s mode \n", (drvStatus.bFBL?("-Less"):("")));
                printf(" V-Len = %d\n", drvStatus.u16V_Length);
                printf(" DeInt = %d, 3DNR = %d \n", drvStatus.eDeInterlaceMode, drvStatus.bEn3DNR);
                printf(" BitPerPixel = %d, LinearMode = %d \n", drvStatus.u8BitPerPixel, drvStatus.bLinearMode);
                printf(" IPMFetch = %ld, IPMOffset = %d\n", drvStatus.u16IPMFetch, drvStatus.u16IPMOffset);
                printf(" OPFetch  = %ld, OPOffset  = %d\n", XC_BK_Read2Byte(0x12, 0x2E), XC_BK_Read2Byte(0x12, 0x2C));
                printf(" IPMBase0 = 0x%lx \n", drvStatus.u32IPMBase0);
                printf(" IPMBase1 = 0x%lx \n", drvStatus.u32IPMBase1);
                printf(" IPMBase2 = 0x%lx \n", drvStatus.u32IPMBase2);
//                printf(" IPMBase0 = 0x%lx, IPMBase1 = 0x%lx, IPMBase2 = 0x%lx\n", drvStatus.u32IPMBase0, drvStatus.u32IPMBase1, drvStatus.u32IPMBase2);

                // Get Crop Win
                printf("\n [Crop Win]: \n");
                pCropWin = &(drvStatus.stCropWin);
                printf(" CropWin    : X = 0x%X, Y = 0x%X, W = %d, H = %d\n", pCropWin->x, pCropWin->y, pCropWin->width, pCropWin->height);


                // Get Crop Win
                pScaledCropWin = &(drvStatus.ScaledCropWin);
                printf(" RealCropWin: X = 0x%X, Y = 0x%X, W = %d, H = %d\n", pScaledCropWin->x, pScaledCropWin->y, pScaledCropWin->width, pScaledCropWin->height);


                // Get Display Win
                printf("\n [Display Win]: \n");
                pDispWin = &(drvStatus.stDispWin);
                printf(" DispWin    : X = 0x%X, Y = 0x%X, W = %d, H = %d\n", pDispWin->x, pDispWin->y, pDispWin->width, pDispWin->height);

                MApi_XC_GetDispWinFromReg( &dispWin, MAIN_WINDOW );
                printf(" RegDispWin : X = 0x%X, Y = 0x%X, W = %d, H = %d \n", dispWin.x, dispWin.y, dispWin.width, dispWin.height);


                // Frame lock
                printf("\n [Frame lock]: \n");
                printf(" bEnableFPLL = %u \n", drvStatus.bEnableFPLL);
                printf(" OutputClk = 0x%lX, RealOutputClk = 0x%lX\n", MDrv_Read3Byte(0x10311E), MDrv_Read3Byte(0x103150));
                printf(" InVPeriod = 0x%lX, OutVPeriod = 0x%lX\n", MDrv_Read3Byte(0x103142), MDrv_Read3Byte(0x103146));

                if( MDrv_Read3Byte(0x103142) )
                {
                    printf(" InVFreq  = %u,", MST_XTAL_CLOCK_HZ*100/MDrv_Read3Byte(0x103142) );
                }

                if( MDrv_Read3Byte(0x103146) )
                {
                    printf(" OutVFreq = %u\n", MST_XTAL_CLOCK_HZ*100/MDrv_Read3Byte(0x103146) );
                }
                printf(" FpllStatus(0x103154) = 0x%X \n", MDrv_Read2Byte(0x103154));
                if( (MDrv_Read2Byte(0x103154)&0x1FF) == 0x1F4 )
                {
                    printf(" FPLL locked\n");
                }
            }

            // Pre-Scaling

            // Mem fetch

            //REG_SC_BK20_1D_L[7:0]  main LB offset
            //REG_SC_BK20_1C_L[7:0]  main Disp offset
            printf(" main Disp offset = 0x%X \n", MApi_XC_R2BYTE(REG_SC_BK20_1C_L) );
            printf(" main LB offset   = 0x%X \n", MApi_XC_R2BYTE(REG_SC_BK20_1D_L) );

            // V len


            // Post scaling

            break;


        case 0x02:
        {
            XC_ApiStatus drvStatus;

            printf("\n*** Output status =====================================\n");
            printf(" OutVT = %u\n", XC_BK_Read2Byte(0x10, 0x1A) );

            printf(" [XC-status]------------------------------\n");
            if(!MApi_XC_GetStatus( &drvStatus, MAIN_WINDOW))
            {
                printf("MApi_XC_GetStatus  = 0 \n");
            }

            // Input sync ...
            {
                XC_IP_SYNC_STATUS sXC_Sync_Status;
                U16 u16HFreq_x10;

                MApi_XC_GetSyncStatus(stSystemInfo[MAIN_WINDOW].enInputSourceType, &sXC_Sync_Status, MAIN_WINDOW);
                u16HFreq_x10 = MApi_XC_CalculateHFreqx10(sXC_Sync_Status.u16Hperiod);

                printf("\n [Input sync]: \n");
                printf(" u8SyncStatus = 0x%X, Interlace = %d \n", sXC_Sync_Status.u8SyncStatus, (sXC_Sync_Status.u8SyncStatus&XC_MD_INTERLACE_BIT)?1:0 );

                printf(" u16Hperiod = %d, V total = %d \n", sXC_Sync_Status.u16Hperiod, sXC_Sync_Status.u16Vtotal );
                printf(" H Freq x10 = %d, V_Freq_x10 = %d \n", u16HFreq_x10, MApi_XC_CalculateVFreqx10(u16HFreq_x10, sXC_Sync_Status.u16Vtotal) );
            }

            // Frame lock
            printf("\n [Frame lock]: \n");
            printf(" FPLL = %d, FPLL_Lock = %d\n", drvStatus.bEnableFPLL, drvStatus.bFPLL_LOCK);
            printf(" OutputClk = 0x%lX, RealOutputClk = 0x%lX\n", MDrv_Read3Byte(0x10311E), MDrv_Read3Byte(0x103150));
            printf(" InVPeriod = 0x%lX, OutVPeriod = 0x%lX\n", MDrv_Read3Byte(0x103142), MDrv_Read3Byte(0x103146));
            if( MDrv_Read3Byte(0x103142)&&MDrv_Read3Byte(0x103146) )
            {
                printf(" InVFreq = %ld, OutVFreq = %ld \n", MST_XTAL_CLOCK_HZ*100/MDrv_Read3Byte(0x103142), MST_XTAL_CLOCK_HZ*100/MDrv_Read3Byte(0x103146));
            }

            break;
        }


        case 0x09:
        {
            U16 u16;

            //g_DebugScart1 = ucPara1;
            u16 = GetScart1IDLevel();
            printf(" GetScart1IDLevel() = %u\n", u16);
            u16 = GetScart2IDLevel();
            printf(" GetScart2IDLevel() = %u\n",u16 );
            {
                U8 i;
                for(i=0;i<8;++i)
                {
                    u16 = GetSarAdcLevel(i);
                    printf("  GetSarAdcLevel(%u)    = 0x%X(%u)", i, u16, u16);
                #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
                    printf("  GetSarAdcLevel_mV(%u) = %u", i, GetSarAdcLevel_mV(i));
                #endif
                    printf("\n");
                }

            }

            break;
        }


        case 0x10:
        {
            printf("Change source to %d\n", ucPara1);
            if( ucPara1 < UI_INPUT_SOURCE_NUM )
            {
                MApp_InputSource_SwitchSource( (E_UI_INPUT_SOURCE)ucPara1, MAIN_WINDOW );
            }

            break;
        }


        case 0x20:
        {
            if( ucPara1 == 1 )
            {
                printf("Bypass ace\n");
                MDrv_WriteByte(XC_RIU_BASE, 0x10);
                /*
                MDrv_Write2Byte(0x102F4C, 0x0400);
                MDrv_Write2Byte(0x102F4E, 0x0000);
                MDrv_Write2Byte(0x102F50, 0x0000);
                MDrv_Write2Byte(0x102F52, 0x0000);
                MDrv_Write2Byte(0x102F54, 0x0400);
                MDrv_Write2Byte(0x102F56, 0x0000);
                MDrv_Write2Byte(0x102F58, 0x0000);
                MDrv_Write2Byte(0x102F5A, 0x0000);
                MDrv_Write2Byte(0x102F5C, 0x0400);
                */
                MDrv_WriteByteMask(0x102F5E, 0, 0x10);
            }
            else
            {
                printf("ace YUVtoRGB\n");
                MDrv_WriteByte(XC_RIU_BASE, 0x10);
                MDrv_Write2Byte(0x102F4C, 0x0662);
                MDrv_Write2Byte(0x102F4E, 0x04A8);
                MDrv_Write2Byte(0x102F50, 0x0000);
                MDrv_Write2Byte(0x102F52, 0x1341);
                MDrv_Write2Byte(0x102F54, 0x04A8);
                MDrv_Write2Byte(0x102F56, 0x1190);
                MDrv_Write2Byte(0x102F58, 0x0000);
                MDrv_Write2Byte(0x102F5A, 0x04A8);
                MDrv_Write2Byte(0x102F5C, 0x0812);
                MDrv_WriteByteMask(0x102F5E, 0x35, 0x35);
            }
            break;
        }

    } // switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
}
#endif // #if( ENABLE_TEST_CMD_SCALER )



#if(ENABLE_TEST_CMD_OSD)
void TestCommand_OSD(void)
{
    int i;

    //BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    //BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    i = 0;

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        default:
            printf("\nOSD Test Command List:\n");
            printf("01: Get OSD info\n");
            printf("20: Get GOP info\n");
            break;

        case 0x01:
        {
            printf("================================\n");
            printf("ZuiState=%u, ActiveOsd=%lu\n", MApp_ZUI_GetState(), MApp_ZUI_GetActiveOSD() );
            //printf(" _enTargetMenuState=%u, STATE_MENU_GOTO_DMP=%u\n", _enTargetMenuState, STATE_MENU_GOTO_DMP);
        }
            break;

    #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
         (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
         (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER))
        case 0x20:
          {
            /*typedef struct
            {
                /// Maximum support GOP number.
                MS_U8 u8MaxGOPNum;
                /// Maximum support GWIN number.
                MS_U8 u8MaxGwinNum;
                /// gop destination blending path. (save supported dst type in array)
                EN_GOP_DST_TYPE SupportGOPDst[MAX_GOP_DST_SUPPORT];
            } GOP_ApiInfo;*/

            GOP_ApiInfo stuGOP_ApiInfo;

            MApi_GOP_GetInfo(&stuGOP_ApiInfo);
            printf("\nu8MaxGOPNum=%d, u8MaxGwinNum=%d\nSupportGOPDst:", stuGOP_ApiInfo.u8MaxGOPNum, stuGOP_ApiInfo.u8MaxGwinNum );
            for( i = 0; i < MAX_GOP_DST_SUPPORT; ++ i )
            {
                printf("[%d]", stuGOP_ApiInfo.SupportGOPDst[i]);
            }

          }

            printf("\nMApi_GOP_GWIN_GetMaxGOPNum()=%d\n", MApi_GOP_GWIN_GetMaxGOPNum() );
            {
                MS_U8 u8GopNo;
                for( u8GopNo = 0; u8GopNo < MApi_GOP_GWIN_GetMaxGOPNum(); ++ u8GopNo )
                {
                    printf("  MApi_GOP_GWIN_GetGwinNum(%d)=%d\n", u8GopNo, MApi_GOP_GWIN_GetGwinNum(u8GopNo) );
                }
            }

            printf("MApi_GOP_GWIN_GetTotalGwinNum()=%d\n", MApi_GOP_GWIN_GetTotalGwinNum() );
            {
                MS_U8 u8GwinId;
                E_GOP_API_Result gopRtn;

                for( u8GwinId = 0; u8GwinId < MApi_GOP_GWIN_GetTotalGwinNum(); ++ u8GwinId )
                {
                    printf(" GWin(%d)=%d\n", u8GwinId, MApi_GOP_GWIN_IsGWINEnabled(u8GwinId) );
                    {
                        MS_U16 x0,y0,width,height,pitch,fmt;
                        MS_U32 addr, size;

                        gopRtn = MApi_GOP_GWIN_GetWinAttr(u8GwinId, &x0, &y0, &width, &height,
                                                          &pitch, &fmt, &addr, &size);
                        if( gopRtn == GOP_API_SUCCESS )
                        {
                            printf("  x=%d,y=%d,w=%d,h=%d\n", x0,y0,width,height);
                            printf("  pitch=%d,fmt=%d,addr=%lX,size=%lX\n", pitch,fmt,addr, size);
                        }
                    }
                    {
                        GOP_GwinInfo gwinInfo;
                        gopRtn = MApi_GOP_GWIN_GetWinInfo(u8GwinId, &gwinInfo);
                        if( gopRtn == GOP_API_SUCCESS )
                        {
                            printf("  HStart=%d,HEnd=%d\n", gwinInfo.u16DispHPixelStart,gwinInfo.u16DispHPixelEnd);
                            printf("  VStart=%d,VEnd=%d\n", gwinInfo.u16DispVPixelStart,gwinInfo.u16DispVPixelEnd);
                            printf("  MemStart=%lX, HRBlkSize=%d\n", gwinInfo.u32DRAMRBlkStart, gwinInfo.u16RBlkHRblkSize);
                            printf("  HPixSize=%d, VPixSize=%d\n", gwinInfo.u16RBlkHPixSize, gwinInfo.u16RBlkVPixSize);
                            printf("  WinX=%d, WinY=%d\n", gwinInfo.u16WinX, gwinInfo.u16WinY);
                            printf("  ColorType=%d\n", gwinInfo.clrType);
                        }
                    }

                }
            }

            printf("\nMApi_GOP_GWIN_GetCurrentGOP()=%d\n", MApi_GOP_GWIN_GetCurrentGOP() );
            break;
        #endif
    }
}
#endif

#if (ENABLE_TEST_CMD_DMP)
extern BOOLEAN g_bOutputMMAliveMessage;
void TestCommand_MM(void)
{
    //BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    //BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        default:
            printf("\nMM Test Command List:\n");
            printf("01: MApp_VDPlayer_GetInfo()\n");
            printf("02: Control Uart switch to VDPlayer\n");
            break;
        case 0x01:
            printf("MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME)=%ld\n", MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME) );
            printf("MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME)=%ld\n", MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME) );
            break;
        case 0x02:
            if( g_bOutputMMAliveMessage )
            {
                g_bOutputMMAliveMessage = FALSE;
                printf("Uart could switch to VDPlayer\n");
            }
            else
            {
                g_bOutputMMAliveMessage = TRUE;
                printf("Uart won't switch to VDPlayer!!\n");
            }
            break;

    }
}
#endif


void TestCommand_MIU(void)
{
    //BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    //BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        case 0x00:
            printf("\nMIU test command list:\n");
            printf("01: MIU hit log\n");
            break;

    #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)|| \
         (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)|| \
         (CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER))
        case 0x01: // Show all reg value
            printf("\nhit_protect_flag=%x\n", (MDrv_ReadByte(0x1012DE)&0x10)>>4 );
            printf(" hit_protect_no=%d, hit_protect_id=%x\n", (MDrv_ReadByte(0x1012DE)&0xE0)>>5, (MDrv_ReadByte(0x1012DF)&0x3F) );

            printf(" hit_protect_no=%d, hit_protect_id=%x\n", (MDrv_ReadByte(0x1012DE)&0xE0)>>5, (MDrv_ReadByte(0x1012DF)&0x3F) );
            break;


        case 0x02: // Check if hit happen
            // Read hit log
            if( MDrv_ReadByte(0x1012DE)&0x10 )
            {
                printf("\n\n==== Miu Protect: Invalid access happened!! ========\n");
                printf(" hit_protect_no=%d, hit_protect_id=%x\n", (MDrv_ReadByte(0x1012DE)&0xE0)>>5, (MDrv_ReadByte(0x1012DF)&0x3F) );
                printf("======================================================\n");

                // Clear old log
                MDrv_WriteByteMask(0x1012DE, 0x01, 0x01);
                MDrv_WriteByteMask(0x1012DE, 0x00, 0x01);
            }
            else
            {
                printf("[Miu Protect]It's OK~\n");
            }
            break;

        case 0x03:
            {
                MS_U8 au8ProtectId[4] = {MIU_CLIENT_R2M_W, MIU_CLIENT_R2M_R,0,0};

                // Enable Miu protect 0 for Beon
                printf("Enable MIU protect 0 for Beon~\n");
                MDrv_MIU_Protect(0, au8ProtectId, BEON_MEM_ADR, (BEON_MEM_ADR+BEON_MEM_LEN-1), ENABLE);
            }
            break;

        case 0x04: // For Audio bitstream
            {
                MS_U8 au8ProtectId[4] = {0x2A, 0, 0, 0}; // T4-PIU(BDMA)=0x2A:

                // Enable Miu protect 0 for Beon
                printf("Enable MIU protect 0 for Audio decode bitstream buffer\n");
                MDrv_MIU_Protect(0, au8ProtectId, (msAPI_AUD_GetDspMadBaseAddr(DSP_DEC)), ((msAPI_AUD_GetDspMadBaseAddr(DSP_DEC))+0x10000-1), ENABLE); // 64K
                //MDrv_MIU_Protect(0, au8ProtectId, VDPLAYER_BITSTREAM_BUFF_EXT_ADR, (VDPLAYER_BITSTREAM_BUFF_EXT_ADR+VDPLAYER_BITSTREAM_BUFF_EXT_LEN-1), ENABLE); // 64K
            }
            break;
    #endif


    #if(ENABLE_MIU_BWC)
        case 0x11:
          msAPI_MIU_BWC_Set_Enable(g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            break;
    #endif

    }
}

#if ENABLE_SSC
void TestCommand_SSC(void)
{
//    BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
//    BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        case 0x07:
            printf("\n Enable DDR SSC");
            msAPI_MIU_SetSsc(  30, 20, 1);
              break;

        case 0x08:
            printf("\n Enable DDR SSC");
          msAPI_MIU_SetSsc(  10, 10, 1);
              break;

        case 0x09:
            printf("\n Enable DDR SSC");
          msAPI_MIU_SetSsc(  40, 10, 1);
              break;

        case 0x0a:
            printf("\n Disable DDR SSC");
          msAPI_MIU_SetSsc(  30, 20, 0);
            break;
    }
}
#endif

#if(ENABLE_TEST_CMD_HDCP)
#if ENABLE_SECURITY_R2_HDCP22
static U8 const _u8AesKey_test[HDCP22_AES_KEY_SIZE] =
{
    0x00
};
static U8 const  _u8Hdcp22Key_test[HDCP22_KEY_SIZE] =   // hdcp2_key_22_encrypted
{
    0x00
};
#endif
void TestCommand_HDCP(void)
{
    BYTE ucPara1;

    printf("TestCommand_HDCP(0x%X, 0x%X)\n", g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_]);

    ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
    #if (HDCP_KEY_TYPE==HDCP_KEY_IN_DB)
        case 0x07:
            {
                extern MS_U8 _u8HdcpKey[HDCP_KEY_SIZE];

                MApp_DB_LoadHDCP_KEY(_u8HdcpKey);
            }
            break;

        case 0x08:
            MApp_DB_SaveHDCP_KEY( ucPara1);
            break;
    #endif

#if ENABLE_SECURITY_R2_HDCP22
    #if (HDCP22_KEY_TYPE==HDCP22_KEY_IN_DB)
        case 0x09:
            {
        #if( (HDCP22_AES_KEY_TYPE==HDCP22_AES_KEY_IN_DB)
                MApp_DB_LoadHDCP22_KEY(_u8AesKey, _u8Hdcp22Key);
        #else
                MApp_DB_LoadHDCP22_KEY(NULL, _u8Hdcp22Key);
        #endif
            }
            break;

        case 0x0A:
        #if( (HDCP22_AES_KEY_TYPE==HDCP22_AES_KEY_IN_DB)
            MApp_DB_SaveHDCP22_KEY((U8 *)_u8AesKey_test,(U8 *) _u8Hdcp22Key_test);
        #else
            MApp_DB_SaveHDCP22_KEY(NULL, _u8Hdcp22Key_test);
        #endif
            break;
    #endif

    #if( (HDCP_KEY_TYPE==HDCP_KEY_IN_DB) || (HDCP22_KEY_TYPE==HDCP22_KEY_IN_DB))
        case 0x0f:
            MApp_DB_EraseHDCPBank();
            break;
    #endif

    #if DEBUG_HDCP22_KEY_IN_DB
        case 0x10:  // please care about stack overflow when enabled
            {
                    #define HDCP_BUFFER_SIZE (0x4000)
                    BOOL msAPI_Flash_WaitWriteDone(U32 u32Timeout);

                    U32 dst;
                    U16 i;
                    U8 u8Buf[HDCP_BUFFER_SIZE];

                    dst = (SYSTEM_BANK_SIZE * HDCP_DB_BANK) ;

                    msAPI_Flash_WaitWriteDone(FLASH_BLOCK_ERASE_MAX_TIME);
                    MDrv_FLASH_Read(dst, HDCP_BUFFER_SIZE, u8Buf);

                    printf("MApp_DB_LoadHDCP_KEY\n");
                    printf("HDCP_DB_BANK 0x%x\n", HDCP_DB_BANK);

                    printf("\n");
                    for(i=0; i<HDCP_BUFFER_SIZE; i++)
                    {
                        printf("%x ", u8Buf[i]);
                        if(i%16==15) printf("\n");
                        if(i%16==7) printf("  ");
                    }
            }
            break;
    #endif

    #if (ENABLE_USB_DOWNLOAD_HDCPKEY22_BIN)
        case 0x55:
            MApp_UpgardeHdcp22keyFromUsb();
            break ;
    #endif

#endif // ENABLE_SECURITY_R2_HDCP22

    }
}
#endif

#if 0
void TestCommand_PWM(void)
{
//    BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
//    BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        case 0xfb:
            MDrv_WriteByte(0x103200, 0x01);
            printf(" ----  103209 %x \n",    MDrv_ReadByte(0x103209));
            printf(" ----  10320F %x \n",    MDrv_ReadByte(0x10320F));
            MDrv_WriteByte(0x103200, 0x00);

//            MDrv_PWM_Duty(1, 0x00);
            MDrv_WriteByte(0x103200, 0x01);

            printf(" ----  103209 %x \n",    MDrv_ReadByte(0x103209));
            printf(" ----  10320F %x \n",    MDrv_ReadByte(0x10320F));
            MDrv_WriteByte(0x103200, 0x00);
            break;

        case 0xfc:
            printf(" test command 0c \n");
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0);//pwm1
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0);//pwm1
            break;

        case 0xfd:
            printf(" test command 0c \n");
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, ENABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x10320F, DISABLE, BIT0); MsOS_DelayTask(1); // dealy to avoid garbage screen
            break;

        case 0xfe:
            printf(" test command 0c \n");
            MDrv_WriteRegBit(0x0E20, ENABLE, BIT1); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x0E20, DISABLE, BIT1); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x0E20, ENABLE, BIT1); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x0E20, DISABLE, BIT1); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x0E20, ENABLE, BIT1); MsOS_DelayTask(1); // dealy to avoid garbage screen
            MDrv_WriteRegBit(0x0E20, DISABLE, BIT1); MsOS_DelayTask(1); // dealy to avoid garbage screen
            break;

        case 0xff:
            printf(" test command 0c \n");
            MDrv_WriteRegBit(0x0E20, ENABLE, BIT1);
            MDrv_WriteRegBit(0x0E20, DISABLE, BIT1);
            MDrv_WriteRegBit(0x0E20, ENABLE, BIT1);
            MDrv_WriteRegBit(0x0E20, DISABLE, BIT1);
            MDrv_WriteRegBit(0x0E20, ENABLE, BIT1);
            MDrv_WriteRegBit(0x0E20, DISABLE, BIT1);
            MDrv_WriteRegBit(0x0E20, ENABLE, BIT1);
            MDrv_WriteRegBit(0x0E20, DISABLE, BIT1);
            break;
    }
}
#endif

#if(ENABLE_TEST_CMD_GPIO)
void TestCommand_GPIO(void)
{
    BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        case 0x01:
            printf("\n set GPIO_%d to %d",ucPara1, ucPara2);
            if(ucPara2)
                mdrv_gpio_set_high(ucPara1);
            else
                mdrv_gpio_set_low(ucPara1);

            printf("\n mdrv_gpio_get_level()=%d",mdrv_gpio_get_level(ucPara1));
            break;

        case 0x02:
            printf("\n mdrv_gpio_get_inout()=%d",mdrv_gpio_get_inout(ucPara1));
            printf("\n set GPIO_%d as Input",ucPara1);
            mdrv_gpio_set_input(ucPara1);
            printf("\n mdrv_gpio_get_inout()=%d",mdrv_gpio_get_inout(ucPara1));
            break;
    }
}
#endif

#if(ENABLE_TEST_CMD_AUDIO)
void TestCommand_AUDIO(void)
{
//    BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
//    BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
    #if DEBUG_AUDIO_DETECT_TIME
        case 0x10:
            printf("\n g_u8WaitAudioTime=%x", g_u8WaitAudioTime);
            g_u8WaitAudioTime = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
            printf("\n g_u8WaitAudioTime=%x", g_u8WaitAudioTime);
            break;
    #endif
    }
}
#endif



#if(ENABLE_TEST_CMD_DATA_BASE)
void TestCommand_DataBase(void)
{
    //U8 u8Para1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    //U8 u8Para2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        case 0x00:
            printf("Cmd List:\n");
            printf(" 01: DB define and var\n");
            printf(" 02: Dump DTV\n");
            break;

        case 0x01:
            MApp_DB_PrintVar(0xFF);
            break;

    #if(ENABLE_DTV_DB_DUMP)
        case 0x02:
            msAPI_DTV_DB_DumpDB(msAPI_DTV_Comm_Get_DBSel(), CM_DUMP_INFO_ALL);
            break;
    #endif

    #if(ENABLE_CHPROC_ORDINAL_LIST)
        case 0x03:
            msAPI_CHPROC_ORD_PrintOridialList();
            break;
    #endif

    }
}
#endif


#if(ENABLE_ATSC)
    #define ENABLE_ATSC_TEST_CMD    1
#else
    #define ENABLE_ATSC_TEST_CMD    0
#endif

#if (ENABLE_ATSC_TEST_CMD)

#define ENABLE_ATSC_FRONT_END_STATUS    0

#if( (CHIP_FAMILY_TYPE==CHIP_FAMILY_WHISKY) )
    #define ENABLE_ATSC_PSIP_EPG        1
#else
    #define ENABLE_ATSC_PSIP_EPG        0
#endif

#if(ENABLE_ATSC_FRONT_END_STATUS)
void TestCmd_AtscFrontEndStatus(void)
{
    PRINT_CURRENT_LINE();

    if( !(IsAtscInUse()||IsATVInUse()) )
        return;

    MS_VIRTUAL_CHANNEL* pCurVirCh = MApp_ChanProc_GetCurChannelPointer();

    printf("Vir CH:\n");

    MS_RF_CHANNEL_new stRfCh;

    MApp_ChanProc_GetRfChannelPointer(pCurVirCh, &stRfCh);

    printf(" stTPSetting.u16Frequency=%u\n", stRfCh.stTPSetting.u16Frequency);
    printf(" stTPSetting.fModulation=%u\n", stRfCh.stTPSetting.fModulation);

    printf(" MApp_GetSignalLockStatus()=%u\n", MApp_GetSignalLockStatus());


    // Tuner

    // Demod
    BOOL bDemodLockStatus = FALSE;
    bDemodLockStatus = msAPI_Demodulator_Get_Lock_ATSC(DEMOD_ATSC_MODE_NTSC);
    printf(" Mod 0 Lock=%u\n", bDemodLockStatus);
    bDemodLockStatus = msAPI_Demodulator_Get_Lock_ATSC(DEMOD_ATSC_MODE_256QAM);
    printf(" Mod 1 Lock=%u\n", bDemodLockStatus);
    bDemodLockStatus = msAPI_Demodulator_Get_Lock_ATSC(DEMOD_ATSC_MODE_64QAM);
    printf(" Mod 2 Lock=%u\n", bDemodLockStatus);
    bDemodLockStatus = msAPI_Demodulator_Get_Lock_ATSC(DEMOD_ATSC_MODE_8VSB);
    printf(" Mod 3 Lock=%u\n", bDemodLockStatus);


    EN_SIGNAL_CONDITION eSignalSNR = msAPI_Tuner_CheckSignalSNR();
    printf(" eSignalSNR=%u\n", eSignalSNR);

    // Demux

    // VDEC
}
#endif

void TestCmd_ATSC(void)
{
    //BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        default:
            break;

        case 0x00:
            printf(" Cmd List:\n");
          #if(ENABLE_ATSC_FRONT_END_STATUS)
            printf("  01: Front End status\n");
          #endif
          #if(ENABLE_ATSC_PSIP_EPG)
            printf("  02: Psip EPG info\n");
          #endif
            break;

    #if(ENABLE_ATSC_FRONT_END_STATUS)
        case 0x01:
            TestCmd_AtscFrontEndStatus();
            break;
    #endif

    #if(ENABLE_ATSC_PSIP_EPG)
        case 0x02:
            MApp_Psip_Print_EPGInfo();
            break;
    #endif
    }

}
#endif


#if(LD_ENABLE)
BOOLEAN LedDev_Init(void);
void TestCmd_LD(U8* pu8Para)
{
    printf("TestCmd_LD: %X %X %X\n", pu8Para[0], pu8Para[1], pu8Para[2]);

    //MDrv_LDM_DMA_Set_DMA0_Data(ucPara1, (ucPara2<<8)+ucPara3);
    //MsOS_FlushMemory();

    switch( pu8Para[0] )
    {
        default:
            break;

        case 0x00:
        {
            printf("Share-Mem:\n");

            printf(" -E_LD_INFO_GAMMA_TBL_ADDR=0x%X\n", MHal_LD_Get_ShareMem(E_LD_INFO_GAMMA_TBL_ADDR));
            printf(" -E_LD_INFO_REMAP_TBL_ADDR=0x%X\n", MHal_LD_Get_ShareMem(E_LD_INFO_REMAP_TBL_ADDR));
            printf(" -E_LD_INFO_ALOG_OUT_LED_BUF_ADDR=0x%X\n", MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_ADDR));
            printf(" -E_LD_INFO_ALOG_OUT_LED_BUF_SIZE=0x%X\n", MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_SIZE));
            //printf(" -E_LD_INFO_LDM_DMA_PORT=0x%X\n", MHal_LD_Get_ShareMem(E_LD_INFO_LDM_DMA_PORT));

            printf(" -E_LD_INFO_ALOG_OUT_LED_BUF_SIZE=0x%X\n", MHal_LD_Get_ShareMem(E_LD_INFO_ALGO_SPI_BLOCK_ADR));

            U32 u32DMABase = MHal_LD_Get_SPI_BufBaseAddr();
            printf("LDM-DMA Memory Addr=0x%X\n", u32DMABase);

        }
            break;

        case 0x01:
            //LedDev_Init();
            {
                U16* pu16LDAlgoOutBuf = (U16*)MsOS_PA2KSEG1( MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_ADDR) );
                U32 u32AlgoOutLedBufSize = MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_SIZE);

                printf("u32AlgoOutLedBufSize=%u\n", u32AlgoOutLedBufSize);

                U16 led_width = MHal_LD_Get_LED_BacklightWidth();
                U16 led_height = MHal_LD_Get_LED_BacklightHeight();

                printf("led_width=%u, led_height=%u\n", led_width, led_height);

                U16 u16LedNum = led_width * led_height;
                printf("u16LedNum=%u\n", u16LedNum);

                printf("pu16LDAlgoOutBuf[0](LedNum)=0x%X\n", pu16LDAlgoOutBuf[0]);

                if( u16LedNum != pu16LDAlgoOutBuf[0] )
                {
                    break;
                }

                U16 u16CheckSum = u16LedNum;
                U16 i;
                printf("pu16LDAlgoOutBuf[]=");
                for( i = 0; i < u16LedNum; ++ i )
                {
                    printf("%X,", pu16LDAlgoOutBuf[i+1]);
                    u16CheckSum += pu16LDAlgoOutBuf[i+1];
                }
                printf("\n");

                printf("pu16LDAlgoOutBuf[i+1]=0x%X(CS)\n", pu16LDAlgoOutBuf[i+1]);
                printf("u16CheckSum=0x%X\n", u16CheckSum);
            }
            break;

    }

}

#endif


BOOL Cus_UART_ExecTestCommand(void)
{
    BOOL bRtn = TRUE;
    U8 u8XCBank;
    U8 ucPara1;
    U8 ucPara2;
    U8 ucPara3;

    ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
    ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    ucPara3 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    u8XCBank = MDrv_ReadByte(XC_RIU_BASE);

#if 0
    {
        U8 i;
        printf("UartCmd[%u]={", g_UartCommand.u8CmdLen);
        for( i = 0; i < g_UartCommand.u8CmdLen; ++ i )
        {
            printf(" %X,", g_UartCommand.Buffer[i]);
        }
        printf("}\n");
    }
#endif

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX1_] )
    {
        case 0x00:
            printf("\nTest Command List:\n");

        #if( ENABLE_TEST_CMD_SCALER )
            printf("01: Sclaer\n");
        #endif

            printf("02: Miu\n");
        #if(ENABLE_TEST_CMD_OSD)
            printf("03: OSD\n");
        #endif
        #if(ENABLE_TEST_CMD_DMP)
            printf("04: MM\n");
        #endif

        #if ENABLE_SSC
            printf("05: SSC\n");
        #endif
        #if(ENABLE_TEST_CMD_HDCP)
            printf("06: HDCP\n");
        #endif
        #if(ENABLE_TEST_CMD_GPIO)
            printf("07: GPIO\n");
        #endif
        #if(ENABLE_TEST_CMD_AUDIO)
            printf("08: AUDIO\n");
        #endif
        #if(ENABLE_LOG_FILE_IN_MEM)
            printf("09: LOG_FILE_IN_MEM\n");
        #endif

        #if( ENABLE_LOG_TO_FILE )
            printf("0A: Write info to file\n");
        #endif

        #if(ENABLE_TEST_CMD_DATA_BASE)
            printf("0B: DataBase:\n");
        #endif

        #if(ENABLE_TEST_PATTERN)
            printf("0C: Test Pattern:\n");
        #endif

        #if (ENABLE_ATSC_TEST_CMD)
            printf("0D: ATSC\n");
        #endif

        #if(ENABLE_ATSC_TTS&&ENABLE_UART_DEBUG_TTS)
            printf("0E: TTS\n");
        #endif

        #if(LD_ENABLE)
            printf("0F: LD\n");
        #endif

        #if(ENABLE_ATSC&&ENABLE_ATSC_EPG_DB_2016)
            printf("10: ATSC EPG\n");
        #endif

            printf("55: Set Mcu pause flag\n");
            break;

        case 0x01:
        #if( ENABLE_TEST_CMD_SCALER )
            TestCommand_Scaler();
        #endif
            break;

        case 0x02:
            TestCommand_MIU();
            break;

        case 0x03:
        #if(ENABLE_TEST_CMD_OSD)
            TestCommand_OSD();
        #endif
            break;

        case 0x04:
        #if(ENABLE_TEST_CMD_DMP)
            TestCommand_MM();
        #endif
            break;

    #if ENABLE_SSC
        case 0x05:
            TestCommand_SSC();
            break;
    #endif

        case 0x06:
        #if(ENABLE_TEST_CMD_HDCP)
            TestCommand_HDCP();
        #endif
            break;

        case 0x07:
        #if(ENABLE_TEST_CMD_GPIO)
            TestCommand_GPIO();
        #endif
            break;

        case 0x08:
        #if(ENABLE_TEST_CMD_AUDIO)
            TestCommand_AUDIO();
        #endif
            break;

    #if(ENABLE_LOG_FILE_IN_MEM)
        case 0x09:
            Debug_Log_PrintAll(ucPara1);
            break;
    #endif

    #if( ENABLE_LOG_TO_FILE )
        case 0x0A:
            msDebug_LogFile_GenFileAndWriteInfo();
            break;
    #endif

    #if(ENABLE_TEST_CMD_DATA_BASE)
        case 0x0B:
            TestCommand_DataBase();
            break;
    #endif

        case 0x0C:
        #if(ENABLE_TEST_PATTERN)
            if( ucPara1 < E_TEST_PATTERN_ID_MAX)
            {
                MApp_TestPattern_DrawPattern(ucPara1);
            }
            else
            {
                MApp_TestPattern_Exit();
            }
        #endif
            break;

        case 0x0D:
        #if (ENABLE_ATSC_TEST_CMD)
            TestCmd_ATSC();
        #endif
            break;

        case 0x0E:
        #if(ENABLE_ATSC_TTS&&ENABLE_UART_DEBUG_TTS)
            TestCommand_TTS();
        #endif
            break;

        case 0x0F:
        #if(LD_ENABLE)
            TestCmd_LD( &(g_UartCommand.Buffer[_UART_CMD_INDEX2_]) );
        #endif
            break;

    #if(ENABLE_ATSC&&ENABLE_ATSC_EPG_DB_2016)
        case 0x10:
            printf("ATSC EPG Dump\n");
            if( ucPara1 == 1 )
                msAPI_AtscEpgDb_PrintEvents(100);
            else if( ucPara1 == 2 )
                msAPI_AtscEpgDb_PrintAllEtt();
            else if( ucPara1 == 3 )
                msAPI_AtscEpgDb_PrintAllDb();
            else if( ucPara1 == 4 )
            {
                MApp_ATSC_EpgDb_DeleteEvents_CB();
                msAPI_AtscEpgDb_PrintEvents(100);
            }
            break;
    #endif



        case 0x55:
            s_u8UartDebug_McuPauseFlag = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
            printf("\ns_u8UartDebug_McuPauseFlag=%x\n", s_u8UartDebug_McuPauseFlag);
            break;

    #if(FRONTEND_TUNER_TYPE== MSTAR_AVATAR2) //   SEC_DTOS403IR121B//LG_TDTC_G311D_TUNER//MSTAR_AVATAR2
        case 0xFF:
            TestCommand_AVATAR();
            break;
    #endif

        default:
            bRtn = FALSE; // Use system default test command
            break;
    }

    MDrv_WriteByte(XC_RIU_BASE, u8XCBank);

    return bRtn;
}
#endif


#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)     \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)     \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)    \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)    \
   )
    #define ENABLE_CUS_UART_CMD_RW_BANK_N   1
    #define ENABLE_DEBUG_RW_MEMORY          1
#else
    #define ENABLE_CUS_UART_CMD_RW_BANK_N   0
    #define ENABLE_DEBUG_RW_MEMORY          0
#endif

#if( ENABLE_DEBUG_RW_MEMORY )
#if( LD_ENABLE &&(CHIP_FAMILY_MAYA==CHIP_FAMILY_TYPE))
static U32 g_u32DebugRWMemBaseAddress = 0x7F0FB00;
#else
static U32 g_u32DebugRWMemBaseAddress = 0;
#endif
U8 DrvMemReadByte(U32 u32MemAddr )
{
    U8 *pu8;
    pu8 = (U8*)MsOS_PA2KSEG1(u32MemAddr);
    return *pu8;
}
void DrvMemWriteByte(U32 u32MemAddr, U8 u8Data )
{
    U8 *pu8;
    pu8 = (U8*)MsOS_PA2KSEG1(u32MemAddr);
    *pu8 = u8Data;
}
static U8 NormalCmd_ReadXData1001xx(U8 u8Offset)
{
    U8 uc;

    switch(u8Offset)
    {
        case 0xF0:
            uc = g_u32DebugRWMemBaseAddress;
            break;
        case 0xF1:
            uc = g_u32DebugRWMemBaseAddress>>8;
            break;
        case 0xF2:
            uc = g_u32DebugRWMemBaseAddress>>16;
            break;
        case 0xF3:
            uc = g_u32DebugRWMemBaseAddress>>24;
            break;
        default:
            uc = DrvMemReadByte(g_u32DebugRWMemBaseAddress+u8Offset);
            break;
    }
    return uc;
}

static void NormalCmd_WriteXData1001xx(U8 u8Offset, BYTE u8Data)
{
    //printf("NormalCmd_WriteXData1001xx(%X, %X)\n", u8Offset, u8Data);
    switch(u8Offset)
    {
        case 0xF0:
            g_u32DebugRWMemBaseAddress = (DWORD)u8Data|(g_u32DebugRWMemBaseAddress&0xFFFFFF00);
            printf("memAddr=%lX\n", g_u32DebugRWMemBaseAddress);
            break;
        case 0xF1:
            g_u32DebugRWMemBaseAddress = (DWORD)u8Data<<8|(g_u32DebugRWMemBaseAddress&0xFFFF00FF);
            printf("memAddr=%lX\n", g_u32DebugRWMemBaseAddress);
            break;
        case 0xF2:
            g_u32DebugRWMemBaseAddress = (DWORD)u8Data<<16|(g_u32DebugRWMemBaseAddress&0xFF00FFFF);
            printf("memAddr=%lX\n", g_u32DebugRWMemBaseAddress);
            break;
        case 0xF3:
            g_u32DebugRWMemBaseAddress = (DWORD)u8Data<<24|(g_u32DebugRWMemBaseAddress&0x00FFFFFF);
            printf("memAddr=%lX\n", g_u32DebugRWMemBaseAddress);
            break;
        default:
            DrvMemWriteByte( g_u32DebugRWMemBaseAddress+u8Offset, u8Data );
            printf("mem[%lX]=%X\n", g_u32DebugRWMemBaseAddress+u8Offset, u8Data);
            break;
    }
}
#endif

BOOL Cus_UART_DecodeCommand(void)
{
    BOOL bRtn = TRUE;
  #if( ENABLE_CUS_UART_CMD_RW_BANK_N )
    static U8 u8XCBank = 0;
  #endif
    U32 u32Tmp;

    switch(UART_CMD)
    {
    #if( ENABLE_CUS_UART_CMD_RW_BANK_N )
        case uartWrite_MST_Bank_n:
            u32Tmp = ((U8)UART_CMD_MS_BANK_H << 16) |
                           ((U8)UART_CMD_MS_BANK_L << 8)  |
                            (U8)UART_CMD_MS_REGINDEX;

            if( u32Tmp == 0x102F00 ) // Scaler bank sel
                u8XCBank = UART_CMD_MS_REGDATA;
            else if( (u32Tmp&0xFFFF00) == 0x102F00 ) // Scaler bank
            {
                MDrv_WriteByte( 0x102F00, u8XCBank ); // Sel bank
            }

            MDrv_WriteByte( u32Tmp, UART_CMD_MS_REGDATA );

            putcharb( 0xF1 );
            break;
        case uartRead_MST_Bank_n:
            u32Tmp = ((U8)UART_CMD_MS_BANK_H << 16) |
                           ((U8)UART_CMD_MS_BANK_L << 8)  |
                            (U8)UART_CMD_MS_REGINDEX;

            /*if( u32Tmp == 0x102F00 ) // Scaler bank sel
                {}
            else*/ if( (u32Tmp&0xFFFF00) == 0x102F00 ) // Scaler bank
            {
                MDrv_WriteByte( 0x102F00, u8XCBank ); // Sel bank
            }

            putcharb( 0xF2 );
            putcharb( MDrv_ReadByte(u32Tmp) );

            //printf("\nRn[%X],", u32Tmp );
            break;
    #endif

    #if( ENABLE_DEBUG_RW_MEMORY )
        case uartWrite_MCU_XDATA:
            u32Tmp = ((U8)UART_CMD_MS_BANK_H << 16) |
               ((U8)UART_CMD_MS_BANK_L << 8)  |
                (U8)UART_CMD_MS_REGINDEX;

//            printf("u32Tmp=%x ", u32Tmp);

            if( (u32Tmp&0xFFFF00) == 0x100100 ) // R/W memory port
            {
                putcharb( 0xF1 );
                NormalCmd_WriteXData1001xx(u32Tmp&0xFF, UART_CMD_MCU_DATA);
            }
#if(FRONTEND_TUNER_TYPE== MSTAR_AVATAR2) //   SEC_DTOS403IR121B//LG_TDTC_G311D_TUNER//MSTAR_AVATAR2
           else if( (u32Tmp&0xFFFF00) == 0x102000 || (u32Tmp&0xFFFF00) == 0x002000) // Avatar2
            {
                U8 u8Reg;
                u8Reg=u32Tmp&0xFF;

                putcharb( 0xF1 );
                if(u8Reg<0x80) OracleWriteByte(u8Reg, UART_CMD_MCU_DATA);
                else ZionWriteByte(u8Reg-0x80, UART_CMD_MCU_DATA);
            }
#endif
            else
            {
                bRtn = FALSE;
            }

            break;
        case uartRead_MCU_XDATA:
            u32Tmp = ((U8)UART_CMD_MS_BANK_H << 16) |
               ((U8)UART_CMD_MS_BANK_L << 8)  |
                (U8)UART_CMD_MS_REGINDEX;

            if( (u32Tmp&0xFFFF00) == 0x100100 ) // R/W memory port
            {
                putcharb( 0xF2 );
                putcharb( NormalCmd_ReadXData1001xx(u32Tmp&0xFF) );
            }
#if(FRONTEND_TUNER_TYPE== MSTAR_AVATAR2) //   SEC_DTOS403IR121B//LG_TDTC_G311D_TUNER//MSTAR_AVATAR2
           else if( (u32Tmp&0xFFFF00) == 0x102000 || (u32Tmp&0xFFFF00) == 0x002000) // Avatar2
            {
                U8 u8Reg;
                U8 u8Val;
                u8Reg=u32Tmp&0xFF;

                putcharb( 0xF2 );

                if(u8Reg<0x80) u8Val=OracleReadByte(u8Reg);
                else u8Val=ZionReadByte(u8Reg-0x80);

                putcharb( u8Val );
            }
#endif
            else
            {
                bRtn = FALSE;
            }
            break;
    #endif

    #if( ENABLE_CUS_UART_TEST_COMMAND )
        case uartTest_Command:
            bRtn = Cus_UART_ExecTestCommand();
            break;
    #endif

        default:
            u32Tmp = 0; // For warning
            bRtn = FALSE;
            break;
    }
    return bRtn;
}

extern void (* CfgLevel0Action[])(void);
extern void (* DbgLevel0Action[])(void);
extern void (* CatLevel0Action[])(void);
//extern void (* UntLevel0Action[])(void);


//$
extern int DbgMenuMode;
//$
extern int DbgMenuLevel;
extern int CatMenuLevel;
extern int UntMenuLevel;
extern int CfgMenuLevel;
extern void (* CfgLevel0Action[])(void);


#if ENABLE_AUTOTEST
U32 UART_EXT_COUNT = 0;
extern BOOLEAN g_bAutobuildDebug;
#endif

void UART_DecodeCommand(void)
{
#if(ENABLE_CONSOLE_CMD)
    msAPI_ConsoleCmd_ExecCmd();
#endif

    if (!g_bDisableUartDebug && g_bUart0Detected) // check command flag
    {
        g_bUart0Detected = FALSE;
        // dbg msg.
        // printf("g_UartCommand.Buffer[_UART_CMD_CODE_] = %x\n",
        // g_UartCommand.Buffer[_UART_CMD_CODE_]);
        // printf("UART_CMD_LENGTH = %x\n", UART_CMD_LENGTH);
        // printf("UART_EXT = %x\n", UART_EXT);
#if (ENABLE_MMS)
        if (1 == DbgMenuMode)
        {
           // dispatch
           //hot key
           HotKey_Decode();

           //$ (1)dbg control
           if (DbgLevel0Action[DbgMenuLevel])
               DbgLevel0Action[DbgMenuLevel]();

           //$ (2)cat eye
           if (CatLevel0Action[CatMenuLevel])
               CatLevel0Action[CatMenuLevel]();

           //$ (3)unit test
           //UntLevel0Action[UntMenuLevel]();

           //$ (4)system config
           if (CfgLevel0Action[CfgMenuLevel])
           CfgLevel0Action[CfgMenuLevel]();

        }
        else
 #endif
        { //command normal mode
            if (UART_EXT)
            {
                Cus_UART_DecodeExtCommand();
                MDrv_UART_DecodeExtCommand();

              #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    UART_EXT_COUNT++;
                }
              #endif
            }
            else
            {
                if( Cus_UART_DecodeCommand() == FALSE )
                    MDrv_UART_DecodeNormalCommand();
            }
        }
        //g_bUart0Detected = FALSE;
    }

}

#ifdef ENABLE_RS232_FUNC
void PRI_RS232_DecodeCommand(void)
{
    if(PRI_RS232_CmdDetect)
    {
        MDrv_PRI_RS232_DecodeCommand();
        PRI_RS232_CmdDetect = FALSE;
    }
}
#endif

U8 msAPI_UART_DecodeCommand( void )
{
    UART_DecodeCommand();
#ifdef ENABLE_RS232_FUNC
    PRI_RS232_DecodeCommand();
#endif
    // stop main loop for debug
    if( g_bDebugProgStopFlag )
        return 1;
    else
        return 0;
}

void MCUPause(char* pcStr, int i)
{
    bool bMiuProtectDetected = FALSE;
    //BYTE ucSC1_04 = XC_BK_ReadByte(1, 4);

    //if(s_u8UartDebug_McuPauseFlag&1)
    {
        if( pcStr )
            printf("%s:", pcStr);
        printf("%d.Mcu Pause:\n", i);

        //printf(" sc1_04=%X,", ucSC1_04);

        g_bDebugProgStopFlag = 1;
        while(g_bDebugProgStopFlag)
        {
            UART_DecodeCommand();
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            if( bMiuProtectDetected == FALSE )
            {
                // Check MIU protect hit log
            #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
                 (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) \
               ||( CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA ) )
                if( MDrv_ReadByte(0x1012DE)&0x10 )
                {
                    bMiuProtectDetected = TRUE;
                    printf("\nhit_protect_flag=%x\n", (MDrv_ReadByte(0x1012DE)&0x10)>>4 );
                    printf(" hit_protect_no=%d, hit_protect_id=%x\n", (MDrv_ReadByte(0x1012DE)&0xE0)>>5, (MDrv_ReadByte(0x1012DF)&0x3F) );
                }
            #endif
            }

        }
        printf("==> Mcu Run~\n");
    }
}

void dbgMEMORY_MAP(void)
{
    printf("[MEMORY_MAP]: ");

  #if (MEMORY_MAP == MMAP_16MB)
    printf("MMAP_16MB");
  #elif (MEMORY_MAP == MMAP_32MB)
    printf("MMAP_32MB");
  #elif (MEMORY_MAP == MMAP_64MB)
    printf("MMAP_64MB");
  #elif (MEMORY_MAP == MMAP_64_64MB)
    printf("MMAP_64_64MB");
//  #elif (MEMORY_MAP == MMAP_64MB_SD)
  //  printf("MMAP_64MB_SD");
  #elif (MEMORY_MAP == MMAP_128MB)
    printf("MMAP_128MB");
  #elif (MEMORY_MAP == MMAP_128_128MB)
    printf("MMAP_128_128MB");
  #else
    printf("UNKNOWN");
  #endif

  printf("\n");

#if 0 //debug  __AEONR2__
    if (bSystemDDR800)
        printf("[System DDR]: 800 MHz\n");
    else
        printf("[System DDR]: 1066 MHz\n");
#endif

}

void dbgFrontEndTunerType(void)
{
    printf("[FRONTEND_TUNER_TYPE]: ");

  #if (FRONTEND_TUNER_TYPE == PHILIPS_TDA1316_TUNER)
    printf("PHILIPS_TDA1316_TUNER");
  #elif (FRONTEND_TUNER_TYPE == THOMSON_FE6640_TUNER)
    printf("THOMSON_FE6640_TUNER");
  #elif (FRONTEND_TUNER_TYPE == PHILIPS_FQD1216_TUNER)
    printf("PHILIPS_FQD1216_TUNER");
  #elif (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
    printf("MSTAR_MSR1200_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LG_TDTC_G001D_TUNER)
    printf("LG_TDTC_G001D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LG_TDTC_G001D_TUNER)
    printf("LG_TDTC_G001D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == PHILIPS_FQD1218_TUNER)
    printf("PHILIPS_FQD1218_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SHARP_VA1Y1ED_TUNER)
    printf("SHARP_VA1Y1ED_TUNER");
  #elif (FRONTEND_TUNER_TYPE == NXP_TD1616EF_TUNER)
    printf("NXP_TD1616EF_TUNER");
  #elif (FRONTEND_TUNER_TYPE == QINGJIA_DAI4W500G_TUNER)
    printf("QINGJIA_DAI4W500G_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LG_TDCC_G031D_TUNER)
    printf("LG_TDCC_G031D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == PHILIPS_FQD1116_TUNER)
    printf("PHILIPS_FQD1116_TUNER");
  #elif (FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
    printf("NXP_FQD1136_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LG_TDFV_G135D_TUNER)
    printf("LG_TDFV_G135D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SHARP_VA1T1ED_6060)
    printf("SHARP_VA1T1ED_6060");
  #elif (FRONTEND_TUNER_TYPE == PHILIPS_TD1318AFLHP_3X_TUNER)
    printf("PHILIPS_TD1318AFLHP_3X_TUNER");
  #elif (FRONTEND_TUNER_TYPE == PHILIPS_TD1318AFLHP_3X_TUNER)
    printf("PHILIPS_TD1318AFLHP_3X_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SAMSUNG_DTOS40AMH201A_TUNER)
    printf("SAMSUNG_DTOS40AMH201A_TUNER");
  #elif (FRONTEND_TUNER_TYPE == ALPS_TDQG4602A_TUNER)
    printf("ALPS_TDQG4602A_TUNER");
  #elif (FRONTEND_TUNER_TYPE == THOMSON_DTT75407_TUNER)
    printf("THOMSON_DTT75407_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SHARP_VA1G5BF2009_TUNER)
    printf("SHARP_VA1G5BF2009_TUNER");
  #elif (FRONTEND_TUNER_TYPE == CH_TMI8_C22I1VH_TUNER)
    printf("CH_TMI8_C22I1VH_TUNER");
  #elif (FRONTEND_TUNER_TYPE == ALPS_TDQG9_601A_TUNER)
    printf("ALPS_TDQG9_601A_TUNER");
  #elif (FRONTEND_TUNER_TYPE == QINGJIA_DTZ0W302G_TUNER)
    printf("QINGJIA_DTZ0W302G_TUNER");
  #elif (FRONTEND_TUNER_TYPE == XUGUANG_STM_6F_V236H_TUNER)
    printf("XUGUANG_STM_6F_V236H_TUNER");
  #elif (FRONTEND_TUNER_TYPE == XUGUANG_HFT_8B1_V116H_TUNER)
    printf("XUGUANG_HFT_8B1_V116H_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SHARP_VA1E1CD2403_TUNER)
    printf("SHARP_VA1E1CD2403_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SHARP_VA1E1BF1402_TUNER)
    printf("SHARP_VA1E1BF1402_TUNER");
  #elif (FRONTEND_TUNER_TYPE == QINGJIA_AFT7W006_TUNER)
    printf("QINGJIA_AFT7W006_TUNER");
  #elif (FRONTEND_TUNER_TYPE == TCL_DTC78WI_3E_TUNER)
    printf("TCL_DTC78WI_3E_TUNER");
  #elif (FRONTEND_TUNER_TYPE == XUGUANG_HFT_8B_115CW_TUNER)
    printf("XUGUANG_HFT_8B_115CW_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LINGHUA_TDP_1H1_E_TUNER)
    printf("LINGHUA_TDP_1H1_E_TUNER");
  #elif (FRONTEND_TUNER_TYPE == CHANGHONG_DTI1_E4I1VH)
    printf("CHANGHONG_DTI1_E4I1VH");
  #elif (FRONTEND_TUNER_TYPE == TCL_DT70WI_3R_TUNER)
    printf("TCL_DT70WI_3R_TUNER");
  #elif (FRONTEND_TUNER_TYPE == CDT_9BT322_40_TUNER)
    printf("CDT_9BT322_40_TUNER");
  #elif (FRONTEND_TUNER_TYPE == PHILIPS_FQD1236_TUNER)
    printf("PHILIPS_FQD1236_TUNER");
  #elif (FRONTEND_TUNER_TYPE == THOMSON_DTT7630_TUNER)
    printf("THOMSON_DTT7630_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SAMSUNG_S205_TUNER)
    printf("SAMSUNG_S205_TUNER");
  #elif (FRONTEND_TUNER_TYPE == ALPS_TDQU4_TUNER)
    printf("ALPS_TDQU4_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SHARP_VA1Y2UR2201_TUNER)
    printf("SHARP_VA1Y2UR2201_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LG_TDVS_H703P_TUNER)
    printf("LG_TDVS_H703P_TUNER");
  #elif (FRONTEND_TUNER_TYPE == NXP_TD1636ALMK2_TUNER)
    printf("NXP_TD1636ALMK2_TUNER");
  #elif (FRONTEND_TUNER_TYPE == NXP_TD1136_TUNER)
    printf("NXP_TD1136_TUNER");
  #elif (FRONTEND_TUNER_TYPE == MSTAR_MSR1200)
    printf("MSTAR_MSR1200");
  #elif (FRONTEND_TUNER_TYPE == ALPS_TDQU6_TUNER)
    printf("ALPS_TDQU6_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SAMSUNG_EH201A_TUNER)
    printf("SAMSUNG_EH201A_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SAMSUNG_DVTA50_TUNER)
    printf("SAMSUNG_DVTA50_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LG_TDTC_G501D_TUNER)
    printf("LG_TDTC_G501D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LG_TDTC_G311D_TUNER)
    printf("LG_TDTC_G311D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SEC_DTOS403LH121A)
    printf("SEC_DTOS403LH121A");
  #elif (FRONTEND_TUNER_TYPE == XUGUANG_DVT_8ADC1_W41F2)
    printf("XUGUANG_DVT_8ADC1_W41F2");
  #elif (FRONTEND_TUNER_TYPE == SAMSUNG_S203FH201B_TUNER)
    printf("SAMSUNG_S203FH201B_TUNER");
  #elif (FRONTEND_TUNER_TYPE == XC5200_TUNER)
    printf("XC5200_TUNER");
  #elif (FRONTEND_TUNER_TYPE == DMCT_6A_111_TUNER)
    printf("DMCT_6A_111_TUNER");
  #elif (FRONTEND_TUNER_TYPE == SEC_DTOS403IR121B)
    printf("SEC_DTOS403IR121B");
  #elif (FRONTEND_TUNER_TYPE == LG_TDTC_G601D_TUNER)
    printf("LG_TDTC_G601D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == MSTAR_AVATAR2)
    printf("MSTAR_AVATAR2");

  #elif (FRONTEND_TUNER_TYPE == NXP_FH2608_TUNER)
    printf("NXP_FH2608_TUNER");
  #elif (FRONTEND_TUNER_TYPE == NXP_FH2603_TUNER)
    printf("NXP_FH2603_TUNER");
  #elif (FRONTEND_TUNER_TYPE == NXP_FH2112_TUNER)
    printf("NXP_FH2112_TUNER");
  #elif (FRONTEND_TUNER_TYPE== NXP_TH2603_TUNER)
    printf("NXP_TH2603_TUNER");

  #elif (FRONTEND_TUNER_TYPE == LG_TDTC_GX01D_GX71D_TUNER)
    printf("LG_TDTC_GX01D_GX71D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == CDT_SFT338_40_TUNER)
    printf("CDT_SFT338_40_TUNER");
  #elif (FRONTEND_TUNER_TYPE == TCL_F17CT_6N_E_TUNER)
    printf("TCL_F17CT_6N_E_TUNER");
  #elif (FRONTEND_TUNER_TYPE == TCL_DT61WI_2R_E_TUNER)
    printf("TCL_DT61WI_2R_E_TUNER");
  #elif (FRONTEND_TUNER_TYPE == LG_TDTC_G901D_TUNER)
    printf("LG_TDTC_G901D_TUNER");
  #elif (FRONTEND_TUNER_TYPE == TCL_F20WT_3DD_E)
    printf("TCL_F20WT_3DD_E_TUNER");
  #elif(FRONTEND_TUNER_TYPE == TCL_DT58WT_3RB_E_TUNER)
    printf("TCL_DT58WT_3RB_E_TUNER");
  #elif(FRONTEND_TUNER_TYPE == QINGJIA_DTT9W303G_TUNER)
    printf("QINGJIA_DTT9W303G_TUNER");
  #elif (FRONTEND_TUNER_TYPE == NUTUNE_FK1602_TUNER)
    printf("NUTUNE_FK1602_Silicon_TUNER");
  #elif(FRONTEND_TUNER_TYPE == NXP_TDA18272_TUNER)
    printf("NXP_TDA18272_Silicon_TUNER");
  #elif(FRONTEND_TUNER_TYPE == MxL_301RF_TUNER)
    printf("MAXLINER_MxL301_Silicon_TUNER");
  #elif(FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
    printf("SILAB_2158_Silicon_TUNER");
  #elif(FRONTEND_TUNER_TYPE == LG_G230D_TUNER)
    printf("LG_G230D_Silicon_TUNER");
  #elif(FRONTEND_TUNER_TYPE == MxL_601SI_TUNER)
    printf("MxL_601SI_TUNER");
  #elif(FRONTEND_TUNER_TYPE == MxL_661SI_TUNER)
    printf("MxL_661SI_TUNER");
  #elif(FRONTEND_TUNER_TYPE == SONY_SUT_RE231_TUNER)
    printf("SONY_SUT_RE231_TUNER");
  #elif(FRONTEND_TUNER_TYPE == SONY_SUT_PEx41_TUNER)
    printf("SONY_SUT_PEx41_TUNER");
  #elif(FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)
    printf("NXP_TDA18275_TUNER");
  #elif(FRONTEND_TUNER_TYPE == NXP_TDA182I5a_TUNER)
    printf("NXP_TDA182I5a_TUNER");

  #elif(FRONTEND_TUNER_TYPE == SILAB_2151_TUNER)
    printf("SILAB_2151_TUNER");
  #elif(FRONTEND_TUNER_TYPE == SILAB_2190_TUNER)
    printf("SILAB_2190_TUNER");
  #elif(FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)
    printf("SILAB_2157_TUNER");

  #elif(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)
    printf("RAFAEL_R840_TUNER");
  #elif(FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
    printf("RAFAEL_R842_TUNER");
  #elif(FRONTEND_TUNER_TYPE == RDA5158_TUNER)
    printf("RDA_RDA5158_TUNER");
  #else
    printf("UNKNOWN");
  #endif

  printf("\n");
}

void dbgVersionMessage(void)
{
    //PanelType *pPanelType = MApi_XC_GetPanelSpec(g_PNL_TypeSel);

    printf("\n======================================\n");

    printf("== Chakra3 Software Version: [%s] \n", SW_VER_NUM);


    printf("[DRAM SIZE]: %d MB\n", MIU_DRAM_LEN/1024/1024);
    printf("[FLASH SIZE]: %d MB\n", FLASH_SIZE/1024/1024);

  #ifdef SW_CONFIG_NAME
    printf("[SW_CONFIG]: %s\n", SW_CONFIG_NAME);
  #else
    printf("[SW_CONFIG]: Not define!\n");
  #endif

    printf("[Board]: %s\n", BOARD_NAME);

#if( defined(MMAP_FILE) )
    printf("[MMAP]: %s\n", MMAP_FILE);
#endif

    //printf("[Panel]: %s\n", pPanelType->m_pPanelName);
#if ENABLE_PANEL_BIN
    printf("[Panel]: Table wasn't loaded yet\n");
#else
    printf("[Panel]: %s\n", MApi_PNL_Get_PanelName(g_PNL_TypeSel));
#endif

//#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
#if (ENABLE_3D_PROCESS && ENABLE_HDMI_4K_2K)
  #if (DEFAULT_3D_BEHAVIOR_SEL == _EN_3D_BEHAVIOR_IDX_All_Passive_)
    printf("#define DEFAULT_3D_BEHAVIOR_SEL     _EN_3D_BEHAVIOR_IDX_All_Passive_ \n");
  #elif (DEFAULT_3D_BEHAVIOR_SEL == _EN_3D_BEHAVIOR_IDX_IN8903_Simple_)
    printf("#define DEFAULT_3D_BEHAVIOR_SEL     _EN_3D_BEHAVIOR_IDX_IN8903_Simple_ \n");
  #elif (DEFAULT_3D_BEHAVIOR_SEL == _EN_3D_BEHAVIOR_IDX_IN8903_PQ_Optimize_)
    printf("#define DEFAULT_3D_BEHAVIOR_SEL     _EN_3D_BEHAVIOR_IDX_IN8903_PQ_Optimize_ \n");
  #elif (DEFAULT_3D_BEHAVIOR_SEL == _EN_3D_BEHAVIOR_MAX_)
    printf("#define DEFAULT_3D_BEHAVIOR_SEL     _EN_3D_BEHAVIOR_MAX_ \n");
  #endif
#endif

#if ENABLE_TCON_IN8903_PROCESS
    printf("ENABLE_TCON_IN8903_PROCESS=1\n");
#endif


#if( SUPPORT_4K2K_OUTPUT )
  #if ENABLE_VX1_CONVERTER_BOARD
    printf("ENABLE_VX1_CONVERTER_BOARD=1\n");
  #endif
#endif


    dbgMEMORY_MAP();

//    printf("\r\n[RM_MAX_ADDRESS]: 0x%x", RM_MAX_ADDRESS);
//    printf("\r\n[RM_GEN_USAGE]: 0x%x", RM_GEN_USAGE);

#if(ENABLE_DTV)
    printf("[DTV]: ");

   #if (ENABLE_ATSC)
    printf("ATSC ");
   #endif
   #if (ENABLE_DVBT)
    printf("DVBT ");
   #endif
   #if (ENABLE_DVB_T2)
    printf("DVBT2 ");
   #endif
   #if (ENABLE_DVBC)
    printf("DVBC ");
   #endif
   #if (ENABLE_DTMB)
    printf("DTMB ");
   #endif
   #if (ENABLE_ISDBT)
    printf("ISDB ");
   #endif

   #if ENABLE_S2
    printf("DVBS/S2 ");
  #endif

    printf("\n");
#endif

  #if (TV_SYSTEM == TV_PAL)
    printf("[ATV]: PAL\n");
  #elif (TV_SYSTEM == TV_NTSC)
    printf("[ATV]: NTSC\n");
  #endif

  #if (ENABLE_ATSC_TTS)
    printf("ATSC_TTS \n");
  #endif

  #if (ENABLE_TTX)
    printf("[ENABLE_TTX]: %d\n", ENABLE_TTX);
  #endif

  #if (ATSC_CC == DTV_CC)
    printf("[CC]: DTV_CC \n");
  #elif (ATSC_CC == ATV_CC)
    printf("[CC]: ATV_CC \n");
  #elif (ATSC_CC == BRA_CC)
    printf("[CC]: BRA_CC \n");
  #endif

    printf("[Mirror]: %d\n", MirrorEnable);

    //printf("[ENABLE_PWS]: %d\n", ENABLE_PWS);
    //printf("[ENABLE_POWER_SAVING_DPMS]: %d\n", ENABLE_POWER_SAVING_DPMS);
    //printf("[DEMO_FINE_TUNE]: %s\n", FINE_TUNE);

  #if 0//(ENABLE_DLC)
    printf("[ENABLE_DLC]: %d\n", ENABLE_DLC);
  #endif
  #if (ENABLE_DBC)
    printf("[ENABLE_DBC]: %d\n", ENABLE_DBC);
  #endif

  #if 0//(MWE_FUNCTION)
    printf("[MWE]: %d\n", MWE_FUNCTION);
  #endif
  #if 0//(DISPLAY_LOGO)
    printf("[DISPLAY_LOGO]: %d\n", DISPLAY_LOGO);
  #endif
  #if 0//(ENABLE_POWERON_MUSIC)
    printf("[ENABLE_POWERON_MUSIC]: %d\n", ENABLE_POWERON_MUSIC);
  #endif

  #if (ENABLE_SECURITY_R2_HDCP22)
    printf("[ENABLE_SECURITY_R2_HDCP22]: %d\n", ENABLE_SECURITY_R2_HDCP22);
    printf("[HDCP22_KEY_TYPE]: %d\n", HDCP22_KEY_TYPE);
    printf("[HDCP22_AES_KEY_TYPE]: %d\n", HDCP22_AES_KEY_TYPE);
  #endif

    if (AUTO_BUILD_SW_VER)
        printf("[AUTO BUILD VER]: %s \n", AUTO_BUILD_SW_VER);

#if(CHAKRA3_AUTO_TEST)
    printf("[AUTO_TEST_VERSION]: %u\n", AUTO_TEST_VERSION);
#endif

    dbgFrontEndTunerType();

    printf("\n======================================\n");
}

#endif

