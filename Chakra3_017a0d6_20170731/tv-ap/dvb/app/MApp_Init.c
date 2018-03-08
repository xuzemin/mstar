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

#define MAPP_INIT_C

//------------------------------------------------------------------------------
//                            Header Files
//------------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include "util_checkversion.h"
#include "Board.h"
#include "datatype.h"
#include "debug.h"
#include "MsTypes.h"
#include "drvBDMA.h"

// Common Definition
#include "datatype.h"

#include "MsIRQ.h"
#include "MsOS.h"

#include "apiGOP.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Cus.h"
#include "apiAUDIO.h"
#include "apiPNL.h"
#include "Panel.h"

#ifdef SCART_OUT_NEW_METHOD
#include "drvTVEncoder.h"
#endif

#include "drvSYS.h"
#include "drvPM.h"
#include "drvGPIO.h"

#include "apiGOP.h"
#include "apiXC_Ace.h"
#include "apiXC_Dlc.h"

#include "msAPI_FreqTableATV.h"
#include "msAPI_Power.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_DrvInit.h"
#include "msAPI_Video.h"
#include "msAPI_IR.h"
#include "msAPI_Ram.h"
#include "msAPI_OSD.h"
#include "msAPI_Tuner.h"
#include "msAPI_Timer.h"
#include "msAPI_OCP.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_ChProc.h"
#include "msAPI_Flash.h"
#include "msAPI_audio.h"
#include "msAPI_Font.h"

#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#include "msAPI_FSEnv.h"
#include "msAPI_DCC.h"
#include "msAPI_FS_SysInfo.h"

#if (VECTOR_FONT_ENABLE) && (COPRO_MVF_ENABLE)
#include "msAPI_CPU.h"
#endif

#if ENABLE_SBOOT_LOAD_BIN
#include "msAPI_Joba.h"
#endif

#include "msAPI_Tuning.h"
#include "msAPI_VD.h"


#include "MApp_Main.h"

#include "MApp_Font.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_MultiTasks.h"
#include "MApp_TopStateMachine.h"
#include "MApp_Font.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Key.h"
#include "MApp_IR.h"
#include "MApp_Bitmap.h"
#include "MApp_Init.h"
#include "MApp_SignalMonitor.h"
#include "MApp_InputSource.h"
#include "MApp_Func_Inputsource.h"
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
#include "MApp_TV.h"
#endif

#include "MApp_PCMode.h"
#include "MApp_Audio.h"
#include "MApp_Logo.h"

#if (ENABLE_SUBTITLE)
#include "MApp_Subtitle.h"
#endif

#include "MApp_Scaler.h"
#include "MApp_SaveData.h"
#include "MApp_MVDMode.h"
#include "MApp_DataBase.h"
#include "MApp_UiEpg.h"

#if (ENABLE_DVB)
#include "MApp_Dvb_SI.h"
#endif

#if(ENABLE_ATSC)
#include "MApp_Psip.h"
#include "MApp_VChip.h"
#endif

#if (ENABLE_DTV_EPG)
#include "mapp_epgdb_public.h"
#include "mapp_eit.h"
#endif

#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
#include "MApp_TV.h"
#endif

#include "MApp_Scan.h"
#include "MApp_UiMenuDef.h"
#include "MApp_Sleep.h"
#include "OSDcp_readbin.h"
#include "OSDcp_loadfont.h"
#include "MApp_EpgTimer.h"
#include "MApp_ChannelChange.h"
#include "MApp_VDMode.h"
#include "MApp_ATVProc.h"
#include "MApp_BlockSys.h"
#include "MApp_ZUI_Main.h"
#include "MApp_LoadFontInit.h"
#if (ENABLE_ATSC)
#include "MApp_ChannelProc_ATSC.h"
#endif
#if DISPLAY_LOGO
#include "MApp_Logo.h"
#endif
#include "IF_Demodulator.h"

#if ((ENABLE_DVB_T2) && (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT))
#include "demodulator_T2.h"
#endif

#include "MApp_UiMediaPlayer_Define.h"

#include "MApp_XC_Sys.h"
#include "MApp_USBDownload.h"

#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
//#include "msAPI_vbi.h"
#include "mapp_closedcaption.h"
#endif

#if ENABLE_CEC
#include "msAPI_CEC.h"
#include "apiCEC.h"
#endif

#if ENABLE_DMP
#include "mapp_mplayer.h"
#include "MApp_UiMediaPlayer.h"
#include "MApp_InputSource.h"
#include "mapp_videoplayer.h"
#endif

#if ENABLE_OAD
#include "imginfo.h"
#include "MApp_OAD.h"
#endif //ENABLE_OAD

#if ENABLE_CI
#include "msAPI_CI.h"
#include "MApp_CIMMI.h"
#endif

#include "GPIO.h"

#include "HdmiSwitch.h"

#if ENABLE_PVR
    #include "msAPI_PVR.h"
    #include "MApp_UiPvr.h"
    #include "msAPI_PVRFileSystem.h"
  #ifdef PVR_UTOPIA
    #include "drvAESDMA.h"
  #endif
#endif

#include "msAPI_Global.h"


#if (ENABLE_TTX)
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#endif

#if(ENABLE_DTV)
#include "MApp_SI_Parse.h"
#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#include "MApp_TV.h"
#endif
#include "mapp_photo_display.h"

#if MHEG5_ENABLE
#include "msAPI_MHEG5.h"
#endif


#ifdef ENABLE_SELECT_NONESEARCH_CH
#include "MApp_TV.h"
#endif

#if ENABLE_MFC_6M20
#include "drvUrsaMFCAPI.h"
#endif
#if ENABLE_MFC_6M30
#include "drvUrsa6M30.h"
#endif
#if(ENABLE_6M40_4KX2K_PROCESS)
#include "drvUrsa6M40.h"
#endif

#if ENABLE_UPGRADE_CIPLUSKEY_BY_USB
extern BOOLEAN b_isWriteCIkey;
extern BOOLEAN b_isCIkeyFileExit;
#endif
#if (DISPLAY_LOGO)
static BOOLEAN s_PreInit_bShowLogo = FALSE;
#endif


#if (CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#if(ENABLE_S2)
 #if(DISH_TYPE != DISH_NONE)
    #include "drvDish.h"
 #endif
#endif

#include "msAPI_Demod.h"

#if ENABLE_KEY_LOGGER
#include "MApp_KeyLogger.h"
#endif

#if (NO_SIGNAL_AUTO_SHUTDOWN )
#include "MApp_NoSignal_AutoSleep.h"
#endif

#if ENABLE_ATSC_TTS
#include "msAPI_TTS_Sys.h"
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#include "MApp_TTS_Cus_Say.h"
#endif

#if(ENABLE_POWERON_MUSIC)
#include "MApp_PowerOnMusic.h"
#endif

#if (LD_ENABLE)
#include "msAPI_LD.h"
#include "msAPI_LD_PWM.h"
#endif

#if (ENABLE_FLASH_ON_DRAM)
#include "msAPI_FlashOnDram.h"
#endif

#include "MApp_CharTable.h"

#include "Dlp_Optical.h" //gchen @ 20171207 //V56 Driver

#include "dsp_inst_data.h"
#include "dsp_coef_data.h"

#define ADAYO_DEG_SOURCE(x) x


//------------------------------------------------------------------------------

#if (ENABLE_MSTV_UART_DEBUG && ENABLE_MMS)
#include "drvMmsDbg_if.h"
extern void MDrv_Cfg_ActInit(void);
extern void MDrv_Cfg_UserActInit(void);
#endif

//------------------------------------------------------------------------------

//#include "MApp_Customer_Info.h"
extern unsigned char code CID_Buf[];
extern unsigned char code IP_Cntrol_Mapping_1[8];
extern unsigned char code IP_Cntrol_Mapping_2[8];
extern unsigned char code IP_Cntrol_Mapping_3[8];
extern unsigned char code IP_Cntrol_Mapping_4[8];

unsigned char Customer_info[49];
#define DEBUG_CUSTOMER_INFO_ENABLE 0
#if ENABLE_CI
#define CI_INIT_DETECT_COUNT  3
#endif

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

#define MK_U32(B0, B1, B2, B3) ((((U32)(B3))<<24) |(((U32)(B2))<<16)|(((U32)(B1))<<8)|((U32)(B0)))


//------------------------------------------------------------------------------
//                               Debug
//------------------------------------------------------------------------------
#define INIT_DBINFO(x)  //x
#define PWR_DBG(y)      //y
#define BREAK_DEBUG(deay_ms)    {\
                                    U32 u32TimeBefore;\
                                    u32TimeBefore = msAPI_Timer_GetTime0();\
                                    printf("%d\n",u32TimeBefore);\
                                    while(1)\
                                    {\
                                        if ((msAPI_Timer_GetTime0() - u32TimeBefore > deay_ms))\
                                            break;\
                                        msAPI_Timer_ResetWDT();\
                                    }\
                                }


#if USER_DEBUG && BUILD_SYSDEBUG
#define USERDBG(x)      x
#else
#define USERDBG(x)
#endif

/********************************************************************************/
/*                                Static                                        */
/********************************************************************************/
extern U32 u32ProtectOffTimer;

#if (ENABLE_DTV)
extern U16             u16ReminderSrv;
extern U8               u8ReminderPcn;
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
extern BOOLEAN     g_bTimerTypeRecord;
#endif

#if ENABLE_CI_PLUS
extern BOOLEAN     g_bTimeTypeOpRefresh;
extern BOOL g_bOpMenuRestart;
#endif
#endif

extern void ttf_sbrk_SetMemPoolSize(unsigned long u32Size);
extern void *ttf_sbrk(unsigned int size);

extern void hash_sbrk_SetMemPoolSize(unsigned long u32Size);
extern void *hash_sbrk(unsigned int size);
#if ((MARLON_SUPPORT_STR) &&(STR_ENABLE == ENABLE))
extern void msAPI_ALL_STRBackup(BOOLEAN bIsNormalStandBy);
#endif

//U8  u8Switch2Scart;
//U8  u8IsAutoSleep_Skip_Logo;
U32 gSystemStartTimeForRemider;
U32 gSystemStartTimeForRecorder;
S32 volatile gS32OffsetTime;

/*
   // Auth & Encryt Keys.
   // if customer use it's own credentiel ci+ key,may open this fucntion,otherwise make this fucntion
 U8 gu8aAesXcbcKey[16] =
{
    0x09, 0x28, 0x48, 0x92, 0x49, 0x09, 0x82, 0x39, 0x66, 0x83, 0x09, 0x82, 0x39, 0x68, 0x36, 0x21
};
 U8 gu8aAesCbcKey[16] =
{
    0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78, 0x87, 0x96, 0xA5, 0xB4, 0xC3, 0xD2, 0xE1, 0xF0
};
 U8 gu8aAesCbcIV[16] =
{
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
};
*/

#if(ENABLE_DTV)
static void _MApp_DTVInit(void);
#endif

/********************************************************************************/
/*                               Functions                                      */
/********************************************************************************/
void MApp_Init_CustomerInfo(void)
{
    unsigned char * pu8Temp;
    U8 i,u8Data;
    U8 u8ASCII_Mapping[16] = {'0','1','2','3','4','5','6','7','8','9','A',
        'B','C','D','E','F'};

#if (DEBUG_CUSTOMER_INFO_ENABLE)
        printf("****** Customer_info:Before ******");
        for (i=0;i<48;i++)
        {
            if (i%8 ==0)
                printf("\n");
            printf("0x%bx,",Customer_info[i]);

        }

        printf("\n abcdef => 0x%bx,0x%bx,0x%bx,0x%bx,0x%bx,0x%bx,",'a','b','c','d','e','f');
        printf("\n ABCDEF => 0x%bx,0x%bx,0x%bx,0x%bx,0x%bx,0x%bx,",'A','B','C','D','E','F');
        printf("\n\n");
#endif

    pu8Temp = &CID_Buf[6];//(Byte6,7: Customer ID)(Byte8,9: Model ID)(Byte1011: Chip ID)

    //<1>.To Prepare the Customer-ID + Model-ID + Chip-ID
          for (i=0;i<3;i++)
          { //Get hight byte
            u8Data = ((*(pu8Temp+1))>> 4);
            Customer_info[0+i*4] = u8ASCII_Mapping[u8Data];
            u8Data = (*(pu8Temp+1) & 0x0F);
            Customer_info[1+i*4] =  u8ASCII_Mapping[u8Data];
            //Get Low byte
            u8Data = ((*(pu8Temp))>>4) ;
            Customer_info[2+i*4] = u8ASCII_Mapping[u8Data];
            u8Data = (*(pu8Temp) & 0x0F);
            Customer_info[3+i*4] = u8ASCII_Mapping[u8Data];
            pu8Temp +=2;
          }
          for (i=0;i<4;i++)
            Customer_info[12+i] = 0x30;

    //<2>.To prepare the Customer IP
          pu8Temp = &IP_Cntrol_Mapping_1[0];
          memcpy(&Customer_info[16], pu8Temp, 8);
          pu8Temp = &IP_Cntrol_Mapping_2[0];
          memcpy(&Customer_info[16+8], pu8Temp, 8);
          pu8Temp = &IP_Cntrol_Mapping_3[0];
          memcpy(&Customer_info[16+16], pu8Temp, 8);
          pu8Temp = &IP_Cntrol_Mapping_4[0];
          memcpy(&Customer_info[16+24], pu8Temp, 8);

#if (DEBUG_CUSTOMER_INFO_ENABLE)
        printf("****** Customer_info ******");
        for (i=0;i<48;i++)
        {
            if (i%8 ==0)
                printf("\n");
            printf("0x%bx,",Customer_info[i]);

        }
#endif
        Customer_info[48] = 0;  //Important, string end symbol
}

void MApp_Preparation(void)
{
    MApp_Key_Initial_Status();
}

void MApp_Init_UIVariable(void)
{
    EN_OSD_COUNTRY_SETTING eCountry;


 #if (ENABLE_DTV)
    #if ENABLE_ISDBT_NO_DVB
     eCountry = (EN_OSD_COUNTRY_SETTING)E_BRAZIL,                       ///< Brazil
   #else
     eCountry = (EN_OSD_COUNTRY_SETTING)stGenSetting.stTvSetting.eCountry;
   #endif
 #else
    eCountry = OSD_COUNTRY_UK;
 #endif

    MApp_SetOSDCountrySetting(eCountry, FALSE);

#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
    MApp_SetOSDCertificationSetting(DEFAULT_TUNING_CERTIFICATION, TRUE);
#endif

  #if EAR_PHONE_POLLING
    PreEarphoneState = EAR_PHONE_NULL;
  #endif
    u32InfoOSD_Duration = 5000L;

    u32MonitorOsdTimer = 0;

    bNextEvent = FALSE;
  #if (MHEG5_ENABLE)
    enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
  #endif

    enIndicateTimerSource = TS_TYPE_NONE;
    memset(&stLMGenSetting.stMB, 0, sizeof(L_MENU_VIDEO_B_VAR));
    memset(&stLMGenSetting.stMFactory_Adjust, 0, sizeof(L_MENU_FACTORY_ADJUST_VAR));

  #if ENABLE_DTV
    SET_OSD_MENU_LANGUAGE(GET_OSD_MENU_LANGUAGE());
  #endif
}

extern U32 volatile gSystemTimeCount;
static void MApp_Init_TimeSetting(void)
{
    ST_TIME _stTime;
    U32 u32PMSystemTime = 0;

    if(bfirstACBoot == TRUE)//--------------AC Power On
    {
        u32PMSystemTime = msAPI_Timer_GetSystemTime();
        stGenSetting.g_Time.NVRAM_g_u8TimeInfo_Flag = 0;
    }
    else//----------------------------------DC Power On
    {
        u32PMSystemTime = msAPI_Timer_GetRTCSystemTime(); //restore system time from RTC
        g_u8TimeInfo_Flag = stGenSetting.g_Time.NVRAM_g_u8TimeInfo_Flag;
    }

    msAPI_Timer_Load_OffsetTime(); // must after EEPROM or FLASH init

    gSystemTimeCount=u32PMSystemTime;
    gSystemTimeCount_TCON = 0;

    /* init offset time */
    stLMGenSetting.stMD.enD4_SleepTimer = STATE_SLEEP_TOTAL;


    MApp_Sleep_ReleaseSleepTimer();


    u32ProtectOffTimer = 0;

    MApp_SetOnTimer((MENU_OnTimer)stGenSetting.g_Time.cOnTimerFlag);

    if(stGenSetting.g_Time.cOnTimerFlag != EN_Time_OnTimer_Off)
    {
        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
        _stTime.u8Hour = (U8)stGenSetting.g_Time.u16OnTimer_Info_Hour;
        _stTime.u8Min = (U8)stGenSetting.g_Time.u16OnTimer_Info_Min;
        _stTime.u8Sec = 0;
        //MApp_SetLocalWakeUpTime(MApp_ConvertStTime2Seconds(&_stTime));
    }
    //once mode on need reset flag
    if(stGenSetting.g_Time.cOffTimerFlag == EN_Time_OffTimer_Once)
    {
        stGenSetting.g_Time.cOffTimerFlag = EN_Time_OffTimer_Off;
    }

    MApp_Sleep_SetOffTime(TRUE); //set timer

    stGenSetting.g_Time.wTimeDataCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA );
}

static void MApp_Init_PrintDataBaseMsg(void)
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /* database usage status */
    INIT_DBINFO(printf("General Usage :    start   size\n"));
    INIT_DBINFO(printf("BOOTLOADER         0x%04X  0x%04X\n", (U16)RM_BOOTLOADER_ADDR, (U16)RM_SIZE_BOOTLOADER));
    INIT_DBINFO(printf("TIMER_MANUAL_EVENT 0x%04X  0x%04X\n", (U16)RM_TIMER_MANUAL_EVENT_START_ADR, (U16)RM_SIZE_MANUAL_TIMER_EVENT));
    INIT_DBINFO(printf("TIMER_CHECKSUM     0x%04X  0x%04X\n", (U16)RM_TIMER_CHECKSUM_START_ADR, (U16)RM_SIZE_TIMER_CHECKSUM));
    INIT_DBINFO(printf("TV_COMMON_DATA     0x%04X  0x%04X\n", (U16)RM_TV_COMMON_DATA_START_ADR, (U16)RM_SIZE_TV_COMMON_DATA));
    INIT_DBINFO(printf("=> (RM_GEN_USAGE) = %lu\n", (U32)((U32)RM_GEN_USAGE )));

    INIT_DBINFO(printf("DB Usage :         start   size\n"));
    INIT_DBINFO(printf("DTV_CHSET          0x%04X  0x%04X\n", (U16)RM_DTV_CHSET_START_ADDR, (U16)RM_DTV_CHSET_SIZE));
    INIT_DBINFO(printf("ATV_CHSET          0x%04X  0x%04X\n", (U16)RM_ATV_CHSET_START_ADDR, (U16)RM_ATV_CHSET_SIZE));

#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
    INIT_DBINFO(printf("CATV_CHSET         0x%04X  0x%04X\n", (U16)RM_CATV_CHSET_START_ADDR, (U16)RM_CATV_CHSET_SIZE));
#endif

#if( DB_PC_MODE_SAVE_TO_DB_GEN == 0 )
    INIT_DBINFO(printf("MODE_SETTING       0x%04X  0x%04X\n", (U16)RM_MODE_SETTING_START_ADR, (U16)RM_SIZE_MODE_SETTING));
#endif

    INIT_DBINFO(printf("=> RM_64K_USAGE = %lu\n", (U32)RM_64K_USAGE));

    INIT_DBINFO(printf("Others : \n"));
    INIT_DBINFO(printf("sizeof(DTV_CHANNEL_INFO)    = %u\n", (U16)sizeof(DTV_CHANNEL_INFO)));
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

BOOLEAN MApp_Init_CheckOnTimeSetting(void)
{
    ST_TIME _stTime;
    DAYOFWEEK _Today = SUN;

   MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
//printf("stGenSetting.g_Time.u16OnTimer_Info_Hour=%d\n",stGenSetting.g_Time.u16OnTimer_Info_Hour);
//printf("stGenSetting.g_Time.u16OnTimer_Info_Min=%d\n",stGenSetting.g_Time.u16OnTimer_Info_Min);

//printf("_stTime.u8Hour=%d\n", _stTime.u8Hour);
//printf("_stTime.u8Min=%d\n", _stTime.u8Min);
   _Today = (DAYOFWEEK)MApp_GetDayOfWeek(_stTime.u16Year, _stTime.u8Month, _stTime.u8Day);
   if( _stTime.u8Hour != (U8)stGenSetting.g_Time.u16OnTimer_Info_Hour ||
        _stTime.u8Min != (U8)stGenSetting.g_Time.u16OnTimer_Info_Min)
        return FALSE;

    switch(stGenSetting.g_Time.cOnTimerFlag)
    {
        default :
        case EN_Time_OnTimer_Off:
        return FALSE;

        case EN_Time_OnTimer_Once:
        case EN_Time_OnTimer_Everyday:
            return TRUE;

        case EN_Time_OnTimer_Mon2Fri:
            switch(_Today)
            {
                case SUN:
                case SAT:
        return FALSE;
                default:
                    return TRUE;
            }
            break;

        case EN_Time_OnTimer_Mon2Sat:
            switch(_Today)
            {
                case SUN:
        return FALSE;
                default:
                    return TRUE;
            }
            break;

        case EN_Time_OnTimer_Sat2Sun:
            switch(_Today)
            {
                case MON:
                case TUE:
                case WED:
                case THU:
                case FRI:
        return FALSE;
                default:
                    return TRUE;
            }
            break;

        case EN_Time_OnTimer_Sun:
            switch(_Today)
            {
                case SUN:
                    return TRUE;
                default:
        return FALSE;
    }
            break;
    }
}

static void MApp_Init_CheckOnTimer(void)
{
#if ENABLE_DTV_EPG //ENABLE_DTV
 #if ENABLE_PVR
    EN_EPG_TIMER_ACT_TYPE actType = MApp_EpgTimer_GetTimerActType();

    if( actType == EN_EPGTIMER_ACT_REMINDER ||
        actType == EN_EPGTIMER_ACT_RECORDER_START
    #if ENABLE_CI_PLUS
        ||actType == EN_EPGTIMER_ACT_CI_OP_REFRESH
    #endif
        )
    {
        if(stGenSetting.g_Time.cOnTimerFlag == EN_Time_OnTimer_Once)
        {
            stGenSetting.g_Time.cOnTimerFlag = EN_Time_OnTimer_Off;
        }
        MApp_Sleep_SetAutoOn_OffTime(DISABLE);
        INIT_DBINFO(printf("WakeUpByEPG!!!\n"));
        return;
    }
 #endif
#endif

    if(MApp_Init_CheckOnTimeSetting() == TRUE)
    {
        INIT_DBINFO(printf("WakeUpByOnTimer!!!\n"));

#if( ENABLE_DTV )
        // Before src switch, IsS2InUse() & IsDVBCInUse() not correct in msAPI_DTV_Comm_Get_DBSel()
    #if (ENABLE_S2)
        if(stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_S2)
        {
            msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBS);
        }
        else
    #endif
    #if (ENABLE_DVBC && DVB_T_C_DIFF_DB)
        if(stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBC)
        {
            msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBC);
        }
        else
    #endif
        {
            msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBT);
        }
#endif

        //reset on timer when on timer mode is once
        if(stGenSetting.g_Time.cOnTimerFlag == EN_Time_OnTimer_Once)
        {
            stGenSetting.g_Time.cOnTimerFlag = EN_Time_OnTimer_Off;
            MApp_SetOnTimer((MENU_OnTimer)stGenSetting.g_Time.cOnTimerFlag);
            gWakeupSystemTime = 0xFFFFFFFF;
        }

        // on timer
        switch(stGenSetting.g_Time.cOnTimerSourceFlag)
        {
        ADAYO_DEG_SOURCE(printf(" SET UI_INPUT_SOURCE_TYPE 1 -- %d \n", stGenSetting.g_Time.cOnTimerSourceFlag));
        #if (!ENABLE_ATSC && ENABLE_ATV) //gchen @ 20171218
            case EN_Time_OnTimer_Source_ATV:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_ATV, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
        #endif

        #if (ENABLE_DTV)
          #if (ENABLE_ATSC)
            case EN_Time_OnTimer_Source_ATSC:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATSC;
            #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
                stGenSetting.g_SysSetting.u16MainListLastWatched = stGenSetting.g_Time.cOnTimerChannel;
                MApp_ChanProc_ResetAllIndex(stGenSetting.g_SysSetting.u16MainListLastWatched);
            #else
                stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] = stGenSetting.g_Time.cOnTimerChannel;
                MApp_ChanProc_ResetAllIndex(stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE]);
            #endif
                MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
                break;
          #endif

            #if (ENABLE_DVBT)
            case EN_Time_OnTimer_Source_DVBT:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                #if 0//ENABLE_SBTVD_CM_APP//mantis :0267732 for on time function power on crash.
                msAPI_ATV_SetCurrentAntenna(ANT_AIR);
                #endif

                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DTV, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif

            #if (ENABLE_DVBC)
            case EN_Time_OnTimer_Source_DVBC:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
                #if 0//ENABLE_SBTVD_CM_APP//mantis :0267732 for on time function power on crash.
                msAPI_ATV_SetCurrentAntenna(ANT_AIR);
                #endif

                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DTV, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif
            #if (ENABLE_DTMB)
            case EN_Time_OnTimer_Source_DTMB:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
                #if 0//ENABLE_SBTVD_CM_APP//mantis :0267732 for on time function power on crash.
                msAPI_ATV_SetCurrentAntenna(ANT_AIR);
                #endif

                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DTV, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
    #endif
            #if (ENABLE_ISDBT)
            case EN_Time_OnTimer_Source_ISDBT:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
                #if 0//ENABLE_SBTVD_CM_APP//mantis :0267732 for on time function power on crash.
                msAPI_ATV_SetCurrentAntenna(ANT_AIR);
                #endif

                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DTV, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif

            #if(ENABLE_S2)
            case EN_Time_OnTimer_Source_S2://RYAN s2 bug 200
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DTV, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif


            #if 0//(ENABLE_ATSC)
            case EN_Time_OnTimer_Source_ATSC_RADIO:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATSC;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_RADIO, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif

            #if (ENABLE_DVBT)
            case EN_Time_OnTimer_Source_DVBT_RADIO:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_RADIO, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

                break;
            #endif

            #if (ENABLE_DVBC)
            case EN_Time_OnTimer_Source_DVBC_RADIO:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_RADIO, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif
            #if (ENABLE_DTMB)
            case EN_Time_OnTimer_Source_DTMB_RADIO:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_RADIO, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif
            #if (ENABLE_ISDBT)
            case EN_Time_OnTimer_Source_ISDBT_RADIO:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_RADIO, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif

            #if(ENABLE_S2)
            case EN_Time_OnTimer_Source_S2_RADIO://RYAN s2 bug 200
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_RADIO, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif


            #if NORDIG_FUNC //for Nordig Spec v2.0

            #if 0//(ENABLE_ATSC)
            case EN_Time_OnTimer_Source_ATSC_DATA:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATSC;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DATA, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif

            #if (ENABLE_DVBT)
            case EN_Time_OnTimer_Source_DVBT_DATA:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DATA, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

                break;
            #endif

            #if (ENABLE_DVBC)
            case EN_Time_OnTimer_Source_DVBC_DATA:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DATA, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif
            #if (ENABLE_DTMB)
            case EN_Time_OnTimer_Source_DTMB_DATA:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DATA, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif
            #if (ENABLE_ISDBT)
            case EN_Time_OnTimer_Source_ISDBT_DATA:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DATA, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
            #endif

        #if(ENABLE_S2)
            case EN_Time_OnTimer_Source_S2_DATA://RYAN s2 bug 200
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                msAPI_CHPROC_CM_SetCurrentOrdinal(E_SERVICETYPE_DATA, stGenSetting.g_Time.cOnTimerChannel, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                break;
        #endif
            #endif

      #endif
            #if (INPUT_SCART_VIDEO_COUNT >= 1)
            case EN_Time_OnTimer_Source_SCART:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SCART;
                break;
            #endif

            #if (INPUT_SCART_VIDEO_COUNT >= 2)
            case EN_Time_OnTimer_Source_SCART2:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SCART2;
                break;
            #endif

            #if (INPUT_YPBPR_VIDEO_COUNT>=1)
            case EN_Time_OnTimer_Source_COMPONENT:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_COMPONENT;
                break;
            #endif

            #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
            case EN_Time_OnTimer_Source_COMPONENT2:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_COMPONENT2;
                break;
            #endif

            case EN_Time_OnTimer_Source_RGB:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_RGB;
                break;

            #if (INPUT_HDMI_VIDEO_COUNT >= 1)
            case EN_Time_OnTimer_Source_HDMI:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI;
                break;
            #endif

            #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case EN_Time_OnTimer_Source_HDMI2:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI2;
                break;
            #endif

            #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case EN_Time_OnTimer_Source_HDMI3:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI3;
                break;
            #endif

            #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case EN_Time_OnTimer_Source_HDMI4:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI4;
                break;
            #endif

            #if (INPUT_AV_VIDEO_COUNT >= 1)
            case EN_Time_OnTimer_Source_AV:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV;
                break;
            #endif

            #if (INPUT_AV_VIDEO_COUNT >= 2)
            case EN_Time_OnTimer_Source_AV2:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV2;
                break;
            #endif

            #if (INPUT_AV_VIDEO_COUNT >= 3)
            case EN_Time_OnTimer_Source_AV3:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV3;
                break;
            #endif

            #if (INPUT_SV_VIDEO_COUNT >= 1)
            case EN_Time_OnTimer_Source_SVIDEO:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SVIDEO;
                break;
            #endif

            #if (INPUT_SV_VIDEO_COUNT >= 2)
            case EN_Time_OnTimer_Source_SVIDEO2:
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SVIDEO2;
                break;
            #endif

            #if ENABLE_DMP
                case EN_Time_OnTimer_Source_MPLAYER:
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DMP;
                    break;
               // case EN_Time_OnTimer_Source_DLNA: //must
              //      UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DLNA;
               //     break;
            #endif

            default:
                break;
        }
#if( ENABLE_DTV )
        msAPI_DTV_Comm_Set_ForceDBSel(DISABLE, E_DTV_DB_NUM);
#endif

        printf("*** UI_INPUT_SOURCE_TYPE=%u\n", UI_INPUT_SOURCE_TYPE);

        stGenSetting.g_SoundSetting.Volume = stGenSetting.g_Time.cOnTimerVolume;
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);

        MApp_SaveSoundSetting();
        MApp_SaveSysSetting();

        if( stGenSetting.g_Time.cAutoSleepFlag == EN_Time_AutoOff_On)
        {
            MApp_Sleep_SetAutoOn_OffTime(ENABLE);
        }
        else
        {
            MApp_Sleep_SetAutoOn_OffTime(DISABLE);
        }
    }
  #if (ENABLE_DTV)
    else if(msAPI_Power_IswakeupsourceRTC())
    {
    #if(ENABLE_DTV_EPG)
        if(MApp_EpgTimer_CheckOnTimeReminder())
        {
            MEMBER_SERVICETYPE srvType = E_SERVICETYPE_INVALID;
            U16 srvPos = INVALID_SERVICE_ID;

        #if 0//(ENABLE_S2_EPG_REMINDER)
#if ENABLE_PVR
                MS_EPG_TIMER* m_pstEpgTimer = MApp_Get_EPG_Timer_pstEpgTimer();
                if(m_pstEpgTimer->u8SrcIsDtvS2 == 1)
                {
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                    msAPI_InputSrcType_SetType(MAIN_WINDOW, EN_SYS_INPUT_SOURCE_TYPE_S2);
                }
                else
#endif
                {
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
                    msAPI_InputSrcType_SetType(MAIN_WINDOW, EN_SYS_INPUT_SOURCE_TYPE_DTV);
                }
        #else
            //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
            MS_EPG_TIMER* m_pstEpgTimer = MApp_Get_EPG_Timer_pstEpgTimer();
            MApp_InputSrc_Set_UiInputSrcType((E_UI_INPUT_SOURCE)m_pstEpgTimer->u8UiSrcType);
        #endif

            msAPI_CM_GetServiceTypeAndPositionWithPCN(u8ReminderPcn, u16ReminderSrv, &srvType, &srvPos);
            msAPI_CM_SetCurrentServiceType(srvType);
            msAPI_CM_SetCurrentPosition(srvType, srvPos);
        }
    #endif
    }
  #endif
}

#if ENABLE_CI
#if ENABLE_UPGRADE_CIPLUSKEY_BY_USB
static BOOL MApp_Detect_CIKey(void)
{
    U8 u8aTempBuf[2] = { 0x00 };
    U16 u16CredentialsLength = 0;

    msAPI_Flash_Read( CIPLUS_KEY_BANK*FLASH_BLOCK_SIZE + 12, 2, u8aTempBuf );
    u16CredentialsLength = (U16)u8aTempBuf[0] << 8 | (U16)u8aTempBuf[1];
    if((u16CredentialsLength > 0)&&(u16CredentialsLength < 0xFFFF))
        return TRUE;
    else
        return FALSE;
}
#endif

static void MApp_Init_CI(void)
{
    msAPI_CI_SetPMTBufAddr(_PA2VA((CI_PMT_BUFFER_MEMORY_TYPE & MIU1) ? (CI_PMT_BUFFER_ADR | MIU_INTERVAL) : (CI_PMT_BUFFER_ADR)));
    msAPI_CI_SetMMIBufAddr(_PA2VA((MMI_TEXTSTRING_MEMORY_TYPE & MIU1) ? (MMI_TEXTSTRING_ADR | MIU_INTERVAL) : (MMI_TEXTSTRING_ADR)));
#if (ENABLE_CI_PLUS)
    msAPI_CI_Initial( TRUE );   // TRUE: CI+ Supported
#else
    msAPI_CI_Initial( FALSE );  // FALSE: CI VI Only
#endif
    msAPI_CI_InstallCallback_CI_Event(MApp_CI_Event_Cb);
#if (ENABLE_CI_PLUS)
    /* Set up CI+ Credentials Setting.
       If using default CI+ Test Keys, please keep marking line.
       If using outside (from Flash) CI+ Production Keys, please unmark this line.
    */
#if ENABLE_UPGRADE_CIPLUSKEY_BY_USB
    if(MApp_Detect_CIKey())
        msAPI_CI_CC_SetCredentialsType(TRUE, TRUE);
#endif
#endif
    msAPI_CI_Set_TXRX_Interval(0,40,1);

#if (ENABLE_CI_PLUS_V1_4)
    msAPI_CI_ConfigResourceDefaultSetting(EN_CI_VERSION_CI_PLUS, EN_CI_PLUS_VERSION_1_4, TRUE);
#elif (ENABLE_CI_PLUS)
    msAPI_CI_ConfigResourceDefaultSetting(EN_CI_VERSION_CI_PLUS, EN_CI_PLUS_VERSION_1_3, TRUE);
#else
    msAPI_CI_ConfigResourceDefaultSetting(EN_CI_VERSION_CI, EN_CI_PLUS_IVALID_VERSION, TRUE);
#endif

#if ENABLE_CI
    MApp_SetCIDebugLevelInit();
#endif

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
    msAPI_CI_CC_SupportCopyNeverRecording(FALSE);
#endif

    // According to EN_CHARACTER_CODE_TABLE to set Character Coding Tables for CICAM.
    {
        U8 u8aCharacterCodingTables[] = {ISO_6937, ISO_8859_01, ISO_8859_02, ISO_8859_03, ISO_8859_04,
                                         ISO_8859_05, ISO_8859_06, ISO_8859_07, ISO_8859_08, ISO_8859_09,
                                         ISO_8859_10, ISO_8859_11, ISO_8859_13, ISO_8859_14, ISO_8859_15
                                        };
        msAPI_CI_MMI_SetCharacterCodingTables(u8aCharacterCodingTables, (U8)sizeof(u8aCharacterCodingTables));
    }

    /* For CI/CI+ Debuging. */
    //msAPI_CI_SetDebugLevel(EN_CI_FUNCTION_DEFAULT, 1);
    //msAPI_CI_SetDebugLevel(EN_CI_FUNCTION_CC, 1);
}
#endif

extern void UART_Clear(void);

#if ENABLE_SHOW_PHASE_FACTORY
void MApp_ReadDDRPhase(void)
 {
      //read miu0 DQS0 and DQS1 for factory show
      g_u16Miu0_Dqs0 = MDrv_Read2Byte(0x103390);
      g_u16Miu0_Dqs1 =MDrv_Read2Byte(0x103392);
      MS_DEBUG_MSG(printf("g_u16Miu0_Dqs0~~~~~________-0x=%x\n",g_u16Miu0_Dqs0));
      MS_DEBUG_MSG(printf("g_u16Miu0_Dqs1~~~~~_________0x=%x\n",g_u16Miu0_Dqs1));
  #if(ENABLE_MIU_1)
      //read miu1 DQS0 and DQS1 for factory show
      g_u16Miu1_Dqs0 = MDrv_Read2Byte(0x10051C);
      g_u16Miu1_Dqs1 =MDrv_Read2Byte(0x10051E);
      MS_DEBUG_MSG(printf("g_u16Miu1_Dqs0~~~~~=%bx\n",g_u16Miu1_Dqs0));
      MS_DEBUG_MSG(printf("g_u16Miu1_Dqs1~~~~~=%bx\n",g_u16Miu1_Dqs0));
   #endif
  }
#endif

void MApp_PreInit_SetupScalerMemory(void)
{
#if( CONTROL_DNR_BUF_RULE_2015 )

    MApi_XC_SetupFrameBuffer();

#else

    // Initialize XC DNR Address
#if( DTV_USE_FBL == 0 )
    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
    {
    #if( defined(SCALER_DNR_BUF_DTV_ADR) && (SCALER_DNR_BUF_DTV_LEN > 0) )
         MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_DTV_MEMORY_TYPE& MIU1) ? (SCALER_DNR_BUF_DTV_ADR| MIU_INTERVAL) : (SCALER_DNR_BUF_DTV_ADR)), SCALER_DNR_BUF_DTV_LEN, MAIN_WINDOW);
    #else
         MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, MAIN_WINDOW);
    #endif
    }
    else
#endif
    {
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, MAIN_WINDOW);
    #if ENABLE_3D_PROCESS
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, SUB_WINDOW);
    #endif
    }

#if (ENABLE_PIP)
    #ifdef SCALER_DNR_SUB_BUF_ADR
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_SUB_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_SUB_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_SUB_BUF_ADR)), SCALER_DNR_SUB_BUF_LEN, SUB_WINDOW);
    #endif
#endif

#endif
}

void MApp_Gop_init(void)
{
    U8 u8GopId = 0;

#if ((UI_SKIN_SEL ==  UI_SKIN_1366X768X4444)   \
    || (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)    \
    || (UI_SKIN_SEL ==  UI_SKIN_1366X768X8888)   \
    )
    {
        if(1)//(g_IPanel.Width() >= 1366 && g_IPanel.Height() >= 768) //gchen @ 20171214
        {
            for (u8GopId = 0;u8GopId<=1;u8GopId++)
            {
                MApi_GOP_GWIN_SwitchGOP(u8GopId);
				#if ENABLE_854x480_UI
                MApi_GOP_GWIN_Set_STRETCHWIN(u8GopId, E_GOP_DST_OP0,0, 0, 854,480);
                MApi_GOP_GWIN_Set_HSCALE(TRUE, 854 ,PANEL_WIDTH);
                MApi_GOP_GWIN_Set_VSCALE(TRUE, 480, PANEL_HEIGHT);
				#else
                MApi_GOP_GWIN_Set_STRETCHWIN(u8GopId, E_GOP_DST_OP0,0, 0, ZUI_ALIGNED_VALUE(1366,8), 768);
                MApi_GOP_GWIN_Set_HSCALE(TRUE,ZUI_ALIGNED_VALUE(1366,8),PANEL_WIDTH);
                MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, PANEL_HEIGHT);
				#endif
				
            }

        #if ENABLE_ZUI_BACKGROUND_PINK_PATCH //issue: some OSD pictures have one pixel high pink frames
            MApi_GOP_GWIN_Set_TranspColorStretchMode(E_GOP_TRANSPCOLOR_STRCH_DUPLICATE);
        #else
            MApi_GOP_GWIN_Set_TranspColorStretchMode(E_GOP_TRANSPCOLOR_STRCH_ASNORMAL);//issue:UI char have some black point.
        #endif

        #if ((FIXED_MIRROR_HD_PANEL_UI_LOSE == ENABLE) && (MirrorEnable == ENABLE))
            if((g_IPanel.Width()<=1366&&g_IPanel.Height()<=768)&&MApp_Image_GetMirror())
            {
                MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_DUPLICATE);
                MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_DUPLICATE);
            }
        #endif
        }
        else
        {
           //Unsupported resolution
           printf("[Unsupported Resolution: %d x %d\n]",g_IPanel.Width(),g_IPanel.Height());
        }
    }
#endif

#if (UI_SKIN_SEL ==  UI_SKIN_960X540X565 || UI_SKIN_SEL == UI_SKIN_960X540XI8)
    {
    	#if ENABLE_854x480_UI
        if(g_IPanel.Width() >= 854 && g_IPanel.Height() >= 480)
		#else
        if(g_IPanel.Width() >= 960 && g_IPanel.Height() >= 540)
		#endif
        {
            for (u8GopId = 0;u8GopId<=1;u8GopId++)
            {	
            	#if ENABLE_854x480_UI
                MApi_GOP_GWIN_SwitchGOP(u8GopId);
                MApi_GOP_GWIN_Set_STRETCHWIN(u8GopId, E_GOP_DST_OP0,0, 0, 854,480);
                MApi_GOP_GWIN_Set_HSCALE(TRUE,854,PANEL_WIDTH);
                MApi_GOP_GWIN_Set_VSCALE(TRUE, 480, PANEL_HEIGHT);
				#else
                MApi_GOP_GWIN_SwitchGOP(u8GopId);
                MApi_GOP_GWIN_Set_STRETCHWIN(u8GopId, E_GOP_DST_OP0,0, 0, 960,540);
                MApi_GOP_GWIN_Set_HSCALE(TRUE,960,PANEL_WIDTH);
                MApi_GOP_GWIN_Set_VSCALE(TRUE, 540, PANEL_HEIGHT);
				#endif
            }

        #if ENABLE_ZUI_BACKGROUND_PINK_PATCH //issue: some OSD pictures have one pixel high pink frames
            MApi_GOP_GWIN_Set_TranspColorStretchMode(E_GOP_TRANSPCOLOR_STRCH_DUPLICATE);
        #else
            MApi_GOP_GWIN_Set_TranspColorStretchMode(E_GOP_TRANSPCOLOR_STRCH_ASNORMAL);//issue:UI char have some black point.
        #endif

        #if ((FIXED_MIRROR_HD_PANEL_UI_LOSE == ENABLE) && (MirrorEnable == ENABLE))
            if((g_IPanel.Width()<=960&&g_IPanel.Height()<=540)&&MApp_Image_GetMirror())
            {
                MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_DUPLICATE);
                MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_DUPLICATE);
            }
        #endif
        }
        else
        {
           //Unsupported resolution
           printf("[Unsupported Resolution: %d x %d\n]",g_IPanel.Width(),g_IPanel.Height());
        }
    }
#endif

#if (UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
    {
        if(g_IPanel.Width() >= 1920 && g_IPanel.Height() >= 1080)
        {
            for (u8GopId = 0;u8GopId<=1;u8GopId++)
            {
                MApi_GOP_GWIN_SwitchGOP(u8GopId);
                MApi_GOP_GWIN_Set_STRETCHWIN(u8GopId, E_GOP_DST_OP0,0, 0, 1920,1080);
                MApi_GOP_GWIN_Set_HSCALE(TRUE,1920,PANEL_WIDTH);
                MApi_GOP_GWIN_Set_VSCALE(TRUE, 1080, PANEL_HEIGHT);
            }

        #if ENABLE_ZUI_BACKGROUND_PINK_PATCH //issue: some OSD pictures have one pixel high pink frames
            MApi_GOP_GWIN_Set_TranspColorStretchMode(E_GOP_TRANSPCOLOR_STRCH_DUPLICATE);
        #else
            MApi_GOP_GWIN_Set_TranspColorStretchMode(E_GOP_TRANSPCOLOR_STRCH_ASNORMAL);//issue:UI char have some black point.
        #endif

        #if ((FIXED_MIRROR_HD_PANEL_UI_LOSE == ENABLE) && (MirrorEnable == ENABLE))
            if((g_IPanel.Width()<=1920&&g_IPanel.Height()<=1080)&&MApp_Image_GetMirror())
            {
                MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_DUPLICATE);
                MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_DUPLICATE);
            }
        #endif
        }
        else
        {
           //Unsupported resolution
           printf("[Unsupported Resolution: %d x %d\n]",g_IPanel.Width(),g_IPanel.Height());
        }
    }
#endif
#if (DISPLAY_LOGO)
    if ( s_PreInit_bShowLogo == FALSE )
#endif
    {
        GOP_InitInfo pGopInit;
        pGopInit.u16PanelWidth = g_IPanel.Width();
        pGopInit.u16PanelHeight = g_IPanel.Height();
        pGopInit.u16PanelHStr = g_IPanel.HStart();
        pGopInit.u32GOPRBAdr = ((GOP_GWIN_RB_MEMORY_TYPE & MIU1) ? (GOP_GWIN_RB_ADR | MIU_INTERVAL) : (GOP_GWIN_RB_ADR));
        pGopInit.u32GOPRBLen = 0x003F4800;
        pGopInit.u32GOPRegdmaAdr = ((GOP_REGDMABASE_MEMORY_TYPE & MIU1) ? (GOP_REGDMABASE_ADR | MIU_INTERVAL) : (GOP_REGDMABASE_ADR));
        pGopInit.u32GOPRegdmaLen = GOP_REGDMABASE_LEN;
        pGopInit.bEnableVsyncIntFlip = FALSE;

        MApi_GOP_InitByGOP(&pGopInit, 0);
        MApi_GOP_GWIN_SetGOPDst(0, E_GOP_DST_OP0);
        #if (MAZDA_SET_GOPALPHAINVERSE)
        MApi_GOP_GWIN_SetAlphaInverse_EX(0, TRUE);
        #endif
    }
}
/***************************************************************************************/

void MApp_Power_On_Init_Standby2On(void)
{
#if ( ENABLE_AUTOTEST || ENABLE_BOOTTIME )
    gbBootTimeFinish = FALSE;
    gU32BootTime = msAPI_Timer_GetTime0();
    printf(" start of main\n");
#endif

#if (ENABLE_CHCHANGETIME)
    gbKeyPress = FALSE;
#endif


#if( CHAKRA3_AUTO_TEST )
    g_AT_bPowerOnFinished = FALSE;
    MApp_AT_SendEvent(E_AT_EVENT_BOOT_TIME_START, (void*)MsOS_GetSystemTime());
#endif


#if ENABLE_SELECT_UART
    #if ENABLE_DMP
    MApp_VDPlayer_UartSwitch(SELECT_UART_PORT);
    #endif
#endif


#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
    gU32BootStepTime = msAPI_Timer_GetTime0();
#endif

    //Set TTF memory pool size
#if (ENABLE_TTF_FONT)
    hash_sbrk_SetMemPoolSize((1024*48));//default:32KB
    //Initial TTF cache memory management system
    hash_sbrk(0);

    ttf_sbrk_SetMemPoolSize(1024*(700-48));
    //Initial TTF memory management system
    ttf_sbrk(0);
#else
    hash_sbrk_SetMemPoolSize(1024);//default:32KB
    //Initial TTF cache memory management system
    hash_sbrk(0);

    //Set TTF memory pool size
    ttf_sbrk_SetMemPoolSize(1024);
    //Initial TTF memory management system
    ttf_sbrk(0);
#endif
}

void MApp_PreInit_CheckAndModifyPowerOnOffFlag(void)
{
    //PRINT_CURRENT_LINE();
    //printf("1.stGenSetting.stMiscSetting.bDCOnOff=%u\n", stGenSetting.stMiscSetting.bDCOnOff);

#if(CHAKRA3_AUTO_TEST)
    // Auto test always AC on-> DC on
    stGenSetting.stMiscSetting.bDCOnOff = EN_POWER_DC_ON;
    return;
#endif


#if ENABLE_OAD
    if( MApp_OAD_IsScheduleOnCheck() )
    {
        printf("Is Schedule On\n");
        if ( EN_POWER_AC_BOOT == msAPI_Power_QueryPowerOnMode() )
        {
            if (stGenSetting.stMiscSetting.bDCOnOff == EN_POWER_DC_OFF) // go to standby
            {
                //msAPI_Power_PowerDown_EXEC();
            }
        }
        //for OAD_Enhance-0013 [TC16032300017]
        #if 1
        else // DC on
        {
            printf("--- OAD DC on\n");
            // do nothing...
            stGenSetting.stMiscSetting.bDCOnOff = EN_POWER_DC_ON;
        }
        #endif
    }
    else
#endif
    {
    #if (ENABLE_NZ_FREEVIEW && ENABLE_OAD)
        if ( (msAPI_CM_GetCountry() == E_NEWZEALAND)
           &&(stGenSetting.g_SysSetting.bOADActiveStandbyMode)
           )
        {
            stGenSetting.g_SysSetting.bOADActiveStandbyMode = FALSE;
            stGenSetting.stMiscSetting.bDCOnOff = EN_POWER_DC_OFF;
            printf(" >> bOADActiveStandbyMode=1 ==> Force DC off\n");
        }
        else
    #endif
        {
            if( EN_POWER_AC_BOOT == msAPI_Power_QueryPowerOnMode() ) // AC on
            {
                printf("AC on\n");

                //G_FACTORY_SETTING.stFacMiscSetting.u8PowerOnMode = POWERON_MODE_SAVE;

        #if ENABLE_DESIGN_POWER_ON_MODE
                if(G_FACTORY_SETTING.stFacMiscSetting.u8PowerOnMode == POWERON_MODE_ON)
                {
                    printf("Force Power On\n");
                    stGenSetting.stMiscSetting.bDCOnOff = EN_POWER_DC_ON;
                }
                else if(G_FACTORY_SETTING.stFacMiscSetting.u8PowerOnMode == POWERON_MODE_OFF)
                {
                    stGenSetting.stMiscSetting.bDCOnOff = EN_POWER_DC_OFF;
                    printf("Force Power Off\n");
                }
                else // last status
                {
                    // Keep last status
                    printf("Use DB setting: stMiscSetting.bDCOnOff=%u\n", stGenSetting.stMiscSetting.bDCOnOff);
                }
        #else
                stGenSetting.stMiscSetting.bDCOnOff = EN_POWER_DC_ON;
        #endif
            }
            else // DC on
            {
                printf("DC on\n");
                // do nothing...
                stGenSetting.stMiscSetting.bDCOnOff = EN_POWER_DC_ON;
            }
        }
    }

    //printf("2.stGenSetting.stMiscSetting.bDCOnOff=%u\n", stGenSetting.stMiscSetting.bDCOnOff);
}

#if ENABLE_TTX
void MApp_PreInit_TTX_And_TurnOfTTX(void)
{
    // !!!!! Must be carefully memory overlay issue!!!!!
    // After msAPI_TTX_InitSystem(), it will use memory
    // After msAPI_TTX_Stop(),  TTX buf can use by other
    // !!!!!

    msAPI_TTX_InitSystem();
    //stGenSetting.g_SysSetting.fEnableTTXSubTitle = FALSE;

    msAPI_TTX_VBIAcquireEnable(FALSE);

    // Turn off TTX in power on init, Turn on at change source
    msAPI_TTX_Stop();


  #if ENABLE_DVB
    MApp_TTX_SetCountry(msAPI_CM_GetCountry());
  #else
    // FIXME:
    // there is no msAPI_CM_GetCountry( ) in ATV only mode.... this is a dirty patch
    MApp_TTX_SetCountry(E_UK);
  #endif

    // Both Logo & TTX use POOL_BUFFER and
    // to avoid writing POOL_BUFFER when showing logo, MApp_TTX_InitVBITeletext() is marked now.
    // This function will be called when changing input source
    //    MApp_TTX_InitVBITeletext();

}
#endif

void MApp_PreInit_Autotest_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (CHAKRA3_AUTO_TEST)
    MApp_AT_Init();
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_GlobalVariable_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (ENABLE_BOOTTIME)
    gU32CompressTotalStepTime = 0;
#endif

    //printf("====> Time: %s\n", __TIME__);

    //init OCP var  20091124EL
    _bOCPFromMem = FALSE;
#if ENABLE_S2
    Dvbs2_Default_Scan = 0;
#endif

    bfirstACBoot = FALSE;
    stSystemInfo[MAIN_WINDOW].enInputSourceType = INPUT_SOURCE_NONE;
    // No matter use PIP or not, always set sub-src to NONE
#if 1//(ENABLE_PIP)
    //if(IsPIPSupported())
    {
        stSystemInfo[SUB_WINDOW].enInputSourceType = INPUT_SOURCE_NONE;
    }
#endif


#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
    b_isWriteCIkey = FALSE;
    b_isCIkeyFileExit = TRUE;
#endif
#if ENABLE_CI_PLUS
    g_bOpMenuRestart = FALSE;
#endif
#if ENABLE_3D_PROCESS
    g_HdmiInput3DFormat = E_XC_3D_INPUT_MODE_NONE;
    g_HdmiInput3DFormatStatus = E_XC_3D_INPUT_MODE_NONE;
#endif

#if FIXED_SCART_OUT_GARBAGE_SWITCH_AR
    g_u8switchAspectFlag = 0;
#endif

#if FIXED_3D_SWITCH_PIC_MODE_GARBAGE
    g_u8switchPicModeFlag = 0;
#endif

#if HDMI_DVI_AUDIO_MODE_CONFIG
    g_HdmiAudioModeChanged = FALSE;
#endif

#if ENABLE_S2
    Test_Dvbs2 = FALSE;
#endif

#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
    g_bTimerTypeRecord = FALSE;
#endif

#if ENABLE_CI_PLUS
    g_bTimeTypeOpRefresh = FALSE;
    bPowerOnEnterOPMode = TRUE;
#endif

#if PVR_AND_TTX_DIFF_WITH_MHEG5
    g_enTurnOnTTX = TTX_MHEG5_NUM;
#endif

#if (ENABLE_HDMI_4K_2K)
    g_HdmiInput4Kx2KFormat= FALSE;
#endif

    g_bPvrChgSrcInitFs = 0;


    // Set flag initial value
    fEnableSignalMonitor        = FALSE;    // Enable signal
    bEnableAC3Check             = FALSE;    // for check scramble(ac3 not exist.)
    u8PollingStereo             = 0;
    g_bRealTimeMonitorOnly      = FALSE;
    u32ScartSwitchDuration      = 0;
    g_bIsImageFrozen            = FALSE;


    /* Initialize 8K bytes memory pool */
    msAPI_Memory_Init(); // 0 ms

    // Debug get key init
    UART_Clear();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_PowerSettingVariable_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    // check AC/DC on, and wakeup device
    msAPI_PowerSetting_Init();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Chip_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    /* initialize all device drivers */
    msAPI_ChipInit();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Audio_Init_1(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    //printf("MUTE_On()\n");
    MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);
    //printf("MUTE_On()\n");
    MApp_Audio_Set_AmpOnOff(AUDIO_AMP_ON);

    //Refine power on sequence for earphone & DAC pop noise issue

    msAPI_AUD_PreInitAudio();

//TAS5747 power on sequence
#if (DIGITAL_I2S_SELECT==AUDIO_I2S_TAS5747)
    AMP_RESET_ON();
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_CustomerInfo(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    /* To set Vendor ID to the Mailbox register */
    MApp_Init_CustomerInfo();

    // MDrv_Sys_Set_CIDInfo(&CID_Buf[6]);
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Panel_Backlight_Off(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    // Disable backlight VCC
    MApi_PNL_SetInverter(DISABLE);

    // Turn off backlight:
    //MApi_PNL_SetBackLight(DISABLE);

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_ReadDDRPhase(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if ENABLE_SHOW_PHASE_FACTORY
    MApp_ReadDDRPhase();
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Driver_Step1_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    msAPI_DrvInitStep1();

#if ENABLE_SBOOT_LOAD_BIN
    // mdrv_uart_connect(E_UART_PORT0, E_UART_AEON );
    msAPI_Joba_Init();

    // Must after mbx init
  #if(JOBA_LOAD_LOGO_BIN)
    msAPI_Joba_Add_LoadBin(BIN_ID_JPEG_BOOT_LOGO, LOGO_SRC_FILE_BUF_ADR);
  #endif
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Interrupt_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    // work around code, currently if the VBI address (From start to end) is beyond 0xFFFF, there'll be problem
    // Temp solution, makes VBI start to end is in same U16 area (0 ~ 0xFFFF)
    msAPI_Interrupt_Init(); // 0 ms

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_DateBase_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());


    // Check data base
    MApp_DB_Check();

    // Init flash write protect
    msAPI_Flash_Init();
    msAPI_Flash_Init_WriteProtect();

    // EEPROM restore or init global setting
#if (EEPROM_DB_STORAGE!=EEPROM_SAVE_NONE)
    MApp_CheckEEPROM();
#endif

    // Flash restore or init global setting
    // When the Flash is normal, please first read (UserData & Channel Data)
#if (EEPROM_DB_STORAGE != EEPROM_SAVE_ALL)
    MApp_CheckFlash();
#endif

    // Check and modify power on/off flag
    MApp_PreInit_CheckAndModifyPowerOnOffFlag();

#if ENABLE_SBTVD_DTV_SYSTEM
    g_bIsSbtvdAppEn = IS_SBTVD_APP_COUNRTY(stGenSetting.stTvSetting.eCountry);
#endif

    msAPI_ATV_InitVariable(); // must after g_bIsSbtvdAppEn setup

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_DB_CH_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (EEPROM_DB_STORAGE != EEPROM_SAVE_ALL)
    MApp_CheckFlash_DB_CH();
#endif


#if ENABLE_OAD
    if(  (msAPI_Timer_GetRTCWakeUpTime() <= msAPI_Timer_GetRTCSystemTime())
      && MApp_OAD_IsUserSelectOn()
      && SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)
      && (msAPI_Timer_GetRTCWakeUpTime()!=0xFFFFFFFF)
      )
    {
        if(msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)
    #if NORDIG_FUNC
        || msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)
    #endif
        || msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
        {
            MApp_OAD_Set_ScheduleOnCheck();
        }
    }
#endif


    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_ATVProc_Audio_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    if( stGenSetting.stMiscSetting.bDCOnOff == EN_POWER_DC_OFF )
    {
        printf("Skip State-ATVProc_Init_Audio\n");
        return;
    }


    MApp_ATVProc_Initialize_Audio();    // use 1596ms

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Audio_Setting_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);

    if( stGenSetting.stMiscSetting.bDCOnOff == EN_POWER_DC_OFF )
    {
        printf("Skip State-AUD_Setting\n");
        return;
    }

    //Audio_Amplifier_ON();

    /* Set the sound mode */
    MApp_Audio_AdjustSoundMode();

    /* Set the surround mode */
    MApp_Aud_SetSurroundMode(stGenSetting.g_SoundSetting.SurroundSoundMode);

    MApp_Aud_Banlace_Init();

	MApp_Aud_EQ_Init();
	
    /* init audio after Audio switch*/
    msAPI_AUD_I2S_Amp_Reset(); // 0 ms


    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_PowerOnMusic_Init(void)
{
#if ( (ENABLE_DMP) && (ENABLE_POWERON_MUSIC))
	if(stGenSetting.g_SysSetting.UsrPowerOnMusic){
		DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

		MApp_InputSource_ChangeAudioSource(INPUT_SOURCE_STORAGE,UI_INPUT_SOURCE_NONE);   // use 183ms

		MApp_Music_StateInit(BIN_ID_MELODY_ON);

		BOOL bRtn = MApp_Music_PowerON_Melody_Decode_OneTime(); // use 328ms

		if( bRtn )
		{
			//printf("MUTE_Off()\n");
			MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
		}
		DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
	}

#endif
}

void MApp_PreInit_Font_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    if( stGenSetting.stMiscSetting.bDCOnOff == EN_POWER_DC_OFF )
    {
        printf("Skip State-FontInit\n");
        return;
    }


#if (VECTOR_FONT_ENABLE) && (COPRO_MVF_ENABLE)
    msAPI_COPRO_Init(BIN_ID_CODE_AEON_MVF,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MEM_ADR | MIU_INTERVAL) : (AEON_MEM_ADR)),AEON_MEM_LEN);
#endif

#if ((MARLON_SUPPORT_STR) &&(STR_ENABLE == ENABLE))
    printf("[Non_STR] load font init start: %d\n",MsOS_GetSystemTime());
    if(IsSTREnable())
    {
        msAPI_FONT_STRRecover();
    }
    else
    {
        MApp_LoadFontInit();
    }
    msAPI_FONT_ACon_STRBackup();
    printf("[Non_STR] load font init End: %d\n",MsOS_GetSystemTime());
#else
    MApp_LoadFontInit();    // use 232ms
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_USB_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    if( stGenSetting.stMiscSetting.bDCOnOff == EN_POWER_DC_OFF )
    {
        printf("Skip State-FontInit\n");
        return;
    }

    msAPI_DrvInit_Init_USB();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_XC_HDMI_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    msAPI_DrvInit_Init_XC_HDMI();

    // Set XC use memory
    MApp_PreInit_SetupScalerMemory();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Driver_IR_KeyPad_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (!BLOADER)
    msAPI_DrvInit_Init_IR();

    msAPI_DrvInit_Init_KeyPad();
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Driver_Step2_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    msAPI_DrvInitStep2();   // use 267ms

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_CheckGoToPowerDown(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    ////////////////////////////////////////////////////////////////
    // Check DC or AC on to decide right now should boot or sleep //
    //printf("1.stGenSetting.stMiscSetting.bDCOnOff=%u\n", stGenSetting.stMiscSetting.bDCOnOff);

    if( stGenSetting.stMiscSetting.bDCOnOff == EN_POWER_DC_OFF ) // go to standby
    {
        //MApp_DB_SaveNowGenSetting();
        MApp_DB_GEN_SaveData_RightNow();
#if ((MARLON_SUPPORT_STR) &&(STR_ENABLE == ENABLE))
        msAPI_ALL_STRBackup(FALSE);
#endif
        printf("\r\n !!!!! should go to standby !!!!! \n");
        msAPI_Power_PowerDown_EXEC();
        MDrv_Sys_StopCpu(1);
    }

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}


static BOOLEAN s_PreInit_bPanelBacklightIsOn = FALSE;

void MApp_PreInit_TurnOn_PanelVcc_LvdsSignal(void)
{
    //PRINT_CURRENT_LINE();

    MApi_PNL_En(TRUE); // use 9ms

    MApp_PreInitPanelTiming(); // use 40ms
}

void MApp_PreInit_TurnOn_Backlight(void)
{
    //PRINT_CURRENT_LINE();

    if( s_PreInit_bPanelBacklightIsOn == FALSE )
    {
        MApi_PNL_SetBackLight(ENABLE); // use ??ms depend on panel spec

        s_PreInit_bPanelBacklightIsOn = TRUE;
    }
}

/*
void MApp_PreInit_TurnOnPanel_(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    MApp_PreInit_TurnOn_PanelVcc_LvdsSignal();

    MApp_PreInit_TurnOn_Backlight();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}
*/
void MApp_PreInit_Panel_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if ENABLE_TCON
    g_bTCONPowerOnFlag = TRUE;
#endif

    //Disable Output CLK
    //printf("MApi_PNL_En(FALSE);\n");
    MApi_PNL_En(FALSE); // 0 ms

#if ENABLE_TCON
    g_bTCONPowerOnFlag = FALSE;
#endif

    MApp_PreInit_TurnOn_PanelVcc_LvdsSignal();

	LEDPWR_ENABLE(); //gchen @ 20171208
	
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_EnableDCC_DDC2BI_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());


    //Set GOP Stop to wait VSync
    MApi_GOP_GWIN_SetForceWrite(ENABLE); // 0 ms

    msAPI_PowerON_EXEC(); // 0 ms

#if ENABLE_DCC
    msAPI_DCC_EnableDCC();
#endif

#if ENABLE_DDCCI
    msAPI_DDC2BI_Init(); // 0 ms
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_DataBase_Checking(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Start of Load & Check general setting and database
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* database usage status */
    MApp_Init_PrintDataBaseMsg(); // 0 ms


#if (ENABLE_CI && ENABLE_CI_PLUS)
    if (stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo)
    {
        g_bOpMenuRestart = TRUE;
    }
#endif

    ////////////////////////////////////////////////////////////////

    /// if cold boot and want to enter UI menu screen page, there is no default data for it, need to initialize here ///
    MApp_DB_LoadModeSetting(MAIN_WINDOW, 0); // 0 ms

#if (ENABLE_PIP)
    if(IsPIPSupported())
    {
        MApp_DB_LoadModeSetting(SUB_WINDOW, 0); // 0 ms
    }
#endif

    if(g_PcadcModeSetting[MAIN_WINDOW].u16HorizontalStart == 0 || g_PcadcModeSetting[MAIN_WINDOW].u16VerticalStart == 0)
    {
        MApp_DB_LoadDefaultTable(MAIN_WINDOW, 0); // 0 ms

    #if (ENABLE_PIP)
        if(IsPIPSupported())
        {
            MApp_DB_LoadDefaultTable(SUB_WINDOW, 0); // 0 ms
        }
    #endif
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // End of Load & Check general setting and database
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());

}

void MApp_PreInit_ADC_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    MApp_ADC_Init();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_SSC_Setting_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());


    // Should be put after loading DB

    SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;

#if (ENABLE_PIP)
    if(IsPIPSupported())
    {
        SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL;
    }
#endif

#if ENABLE_SSC
    msAPI_MIU_SetSsc( stGenSetting.g_SSCSetting.MIUSscSpanKHzx10,
                      stGenSetting.g_SSCSetting.MIUSscStepPercentagex100,
                      stGenSetting.g_SSCSetting.SscMIUEnable );

  #if ((ENABLE_LVDSTORGB_CONVERTER == ENABLE)||CHAKRA3_AUTO_TEST)
    g_IPanel.SetSSC( SSC_SPAN_PERIOD, SSC_STEP_PERCENT, DISABLE );
  #else
    g_IPanel.SetSSC( stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10,
                     stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100,
                     stGenSetting.g_SSCSetting.SscLVDSEnale);
  #endif
    MApi_PNL_Control_Out_Swing(stGenSetting.g_SSCSetting.LVDSSwing);//add LVDSSwing Funciton
#endif // #if ENABLE_SSC

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)  //
    MApp_UsbDownload_USB_UpDate_SetHKPort();
#endif


    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());

}

void MApp_PreInit_TTX_Init(void)
{
    /* Initial teletext */
#if ENABLE_TTX
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    //msAPI_TTX_InitSystem();
    MApp_PreInit_TTX_And_TurnOfTTX();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());

#endif  // #if ENABLE_TTX
}

void MApp_PreInit_Image_SetMirror(void)
{
#if (MirrorEnable == ENABLE)
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    MApp_Image_SetMirror();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
#endif

#ifdef ENABLE_SELECT_NONESEARCH_CH
    u16ChannelReturn_Num1 = IVALID_TV_RETURN_NUM;
    u16ChannelReturn_Num2 = IVALID_TV_RETURN_NUM;
#endif

#if (ENABLE_DTV_CHCEK_USB_DELAY_2S)
    g_u8DTVCheckUSBFlag = DTV_CHECK_USB_ENABLE;
#endif

}

void MApp_PreInit_UI_InputSource_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if ENABLE_DMP
	ADAYO_DEG_SOURCE(printf("gchen ENABLE_DMP 111111 \n"));
    if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP)
    {
        if(MApp_InputSrc_Get_PrevUiInputSrcType() == UI_INPUT_SOURCE_DMP)
        {
        #if 0
	        #if(ENABLE_DTV == FALSE)
	            MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_ATV);
	        #else
	            #if ENABLE_ATSC
	                MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_ATSC);
	            #elif ENABLE_DVBT
	                MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_DVBT);
	            #elif ENABLE_DVBS
	                MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_S2);
	            #elif ENABLE_DVBC
	                MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_DVBC);
	            #elif ENABLE_DTMB
	                MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_DTMB);
	            #elif ENABLE_ISDBT
	                MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_ISDBT);
	            #endif
	        #endif
		#endif
		MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_HDMI); //gchen  @ 20171218 //Source Init
		
        }

        UI_INPUT_SOURCE_TYPE = MApp_InputSrc_Get_PrevUiInputSrcType();
    }
#endif

    MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_TYPE);


    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_CI_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (ENABLE_DVB)
#if ENABLE_CI

    /* CI_Init: Detect CICAM and then Switch TS Interface to Serial/Parallel Mode. */
    //msAPI_CI_EnablePerformanceMonitor(msAPI_Timer_DiffTimeFromNow(gU32BootTime));
    MApp_Init_CI(); // It's important to INIT CI LIB HERE irrespective of which the input source is!

    // Speed up CI.
    if (FALSE == msAPI_CI_CardDetect())
    {
        U8 i;
        for (i = 0; i < CI_INIT_DETECT_COUNT; i++)
        {
            if (msAPI_CI_Polling())
            {
                break;
            }
        }
    }
#endif // #if ENABLE_CI
#endif // #if (ENABLE_DTV)

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_DevHDMISwitch_Init(void)
{
    /* init ps321 */
#if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
  DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

  #if(INPUT_HDMI_VIDEO_COUNT > 0)
    HdmiSwitch_PS321_Init();
  #endif
  DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());

#endif // #if(HDMI_SWITCH_SELECT == HDMI_SWITCH_PS321)
}

// For some special demod need init driver first!
void MApp_PreInit_InitDemodDriver(void)
{
#if ((ENABLE_DVB_T2) && (FRONTEND_DEMOD_DVBT_TYPE == MSTAR_MSB124X_DVBT))
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    mdev_CofdmInit();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
#endif
}

void MApp_PreInit_Tuner_And_Demod_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (ENABLE_DTV)

    MApp_PreInit_InitDemodDriver();

  #if (ENABLE_DVBC )//TODO need add DVB-C case
    //msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, FALSE);
    msAPI_Tuner_Set_DvbType((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType);
    MApp_DVBType_SetPrevType((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType);
  #endif


    //msAPI_Tuner_Initialization_BySource();

    //fixed load devCOFDM_Init twice error
  #if 0//( (DTV_SYSTEM_SEL != DTV_SYSTEM_SBTVD) && (DTV_SYSTEM_SEL != DTV_SYSTEM_DTMB)&& (FRONTEND_DEMOD_TYPE!= MSTAR_MSB124X_DVBT))
    //msAPI_Tuner_InitExternDemod();
  #endif

#if(ENABLE_S2)
 #if(DISH_NONE != DISH_TYPE) //( FRONTEND_DEMOD_S2_TYPE  == EMBEDDED_DVBS_DEMOD)
    MDrv_Dish_Init();
 #endif
#endif //#if ENABLE_S2
#endif // #if ENABLE_DTV

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Time_Setting_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    MApp_Init_TimeSetting(); // 0 ms

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_EPGTimer_Data_Init(void)
{
#if (ENABLE_DTV_EPG)
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    _MApp_EpgTimer_Initdata();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());

#endif
}

void MApp_PreInit_CheckOnTimer_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    MApp_Init_CheckOnTimer(); // 0 ms

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_HDMI_HPD_Init(void)
{
#if( ENABLE_HDMI_FIRST_HDP_BEFORE_SRC_CHANGE )
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    // If CEC is On, Skip this function...
  #if( ENABLE_CEC )
    if( msAPI_CEC_Is_CecTurnOn() )
    {
        return;
    }
  #endif

  #if(!SUPPORT_HDMI_IMM_SWITCH)
    // If first input-source is HDMI, Do HPD : Low --> High
    E_UI_INPUT_SOURCE eUI_INPUT_SOURCE = MApp_InputSrc_Get_UiInputSrcType();

    if( MApp_InputSrc_Is_UiInputSrcTypeHDMI(eUI_INPUT_SOURCE) )
    {
        MApi_XC_HPD_Do_EnterHDMI( MApp_InputSource_GetInputSourceType( eUI_INPUT_SOURCE) );
    }
  #endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
#endif
}

void MApp_PreInit_Logo_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());
	//Optical_YangMing_InputSourceSelect();

	//Optical_YangMing_RGBCurrent();
	
	Optical_SetRes_854x480();
	MsOS_DelayTask(500);
	Optical_Led_OpenANDClose(1);
#if (DISPLAY_LOGO)

    if( 1//(u8IsAutoSleep_Skip_Logo == FALSE)
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
        &&(g_bTimerTypeRecord == FALSE)
#endif

#if ENABLE_CI_PLUS
     && (g_bTimeTypeOpRefresh == FALSE)
#endif
#if ENABLE_OAD
     && (MApp_OAD_IsScheduleOnCheck() == FALSE)
#endif
     )
    {
        BOOL bLogoInitResult = MApp_Logo_Load(); // 40ms

        //MApp_PreInit_TurnOnPanel();

        if(bLogoInitResult ) // use 30ms
        {
            MApp_Logo_Display(TRUE); // use 160ms			
			keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);  //xzm @ 20171222			
            MApp_PreInit_TurnOn_Backlight();	

            s_PreInit_bShowLogo = TRUE;
        }
        else
        {
        /*
            MApi_PNL_En(TRUE);
            MApp_PreInitPanelTiming();
            MApi_PNL_SetBackLight(BACKLITE_INIT_SETTING);
            */
        }
    }

#else

    /* If system enable DISABLE_LOGO, MApp_Scaler_SetWindow will be involved when logo shown. */
    //MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Tuner_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (ENABLE_BOOTTIME)
    gU32BootStepTime = msAPI_Timer_GetTime0();
#endif

    PRINT_AUTOTEST_CHECKPT_TIME("start Tuner init");


    msAPI_CFT_InitChannelFreqTable();

    msAPI_Tuner_Init(); // use ?? ms

#if (ENABLE_BOOTTIME)
    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootStepTime);
    printf("[TIME] msAPI_Tuner_Init = %ld\n", gU32TmpTime);
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_ATVSystem_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if 0//ENABLE_TCON // Need refine...
    //MApi_TCON_PNL_POWER_ENABLE();
#endif

#if ( ENABLE_DVB_TAIWAN_APP)
    msAPI_ATV_SetDirectTuneFlag(FALSE);

     if(stGenSetting.stScanMenuSetting.u8Antenna == 0)//CATV
        msAPI_ATV_SetCurrentAntenna(ANT_CATV);
    else //AIR
        msAPI_ATV_SetCurrentAntenna(ANT_AIR);
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_AVD_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    msAPI_AVD_InitVideoSystem();   // use ??ms

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_OCP_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());


    /*Initialize the OCP address then prepare the bitmap binary*/
    msAPI_OCP_Init(); // 0 ms

#if ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION
    G_OVERSCAN_HRatio=0;
    G_OVERSCAN_HPOSITION=0;
    G_OVERSCAN_VRatio=0;
    G_OVERSCAN_VPOSITION=0;
#endif

    msAPI_OCP_PrepareBitmapBinary();    // use 35ms

    msAPI_OCP_LoadBitmap(/*Osdcp_bmpHandle*/);  // use 31ms

    msAPI_OCP_PrepareStringBinary();    // use 97ms

    /* Initialize ir key value */
    u8KeyCode = KEY_NULL;

    /* Initialize channel move index*/
    g_u16ChannelOrinigalIndex = -1;

#if SCART_ALWAYS_OUTPUT_ATV
    g_u8switchsourceprocessing = FALSE;
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Environment_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if( ENABLE_SCRIPT_EXECUTE)
    msUS_EventInit();
#endif

#if ENABLE_OFFLINE_SIGNAL_DETECTION
    MApp_OffLineInit();
#endif

    MApp_Init_UIVariable();
    bIsInsideDTVManualScanMenu = FALSE;


    //Set GOP Start to wait VSync
    MApi_GOP_GWIN_SetForceWrite(DISABLE); // 0 ms

#if (ENABLE_CI_PLUS)
    msAPI_OP_OpCacheInit();
#endif

#if 0//ENABLE_OAD
    MApp_OAD_Init();    // use 31ms
    /* Initial OAD Flag */
    bFoundOAD = FALSE;
    bNitFoundInvalidOAD=FALSE;
#endif //ENABLE_OAD



    enFrotEndLockStatus = FRONTEND_UNKNOWN;
    enMVDVideoStatus = MVD_UNKNOWN_VIDEO;
    g_bPCSignalMonitor = FALSE;
    g_u8PCSignalMonitorCounter = 0;
    MApp_Scan_State_Init();

    MApp_DataInitVariable();

    MApp_SignalMonitor_Init();

#if ENABLE_EWS
    MApp_SI_SetLocationCode(stGenSetting.stMiscSetting.u8EWSLocationCode);
#endif

    MApp_ChannelChange_VariableInit();

    // 5V Antenna Monitor
    AdjustAntenna5VMonitor((EN_MENU_5V_AntennaPower)stGenSetting.g_SysSetting.f5VAntennaPower);


    MApp_ZUI_Init();    // use 38ms


#if 0//(ENABLE_CEC)
    msAPI_CEC_Init();   // use 1160ms

  #if 0//(ENABLE_SW_CEC_WAKEUP)
    msAPI_CEC_CheckWakeUpPort();
  #endif
#endif


#if (ENABLE_ARC_CHANGE_SPDIF)
    msAPI_CEC_ARC_TX_Control(TRUE);
#endif

#if ENABLE_ATSC
  #if(ATSC_CC == DTV_CC)
    MApp_CC_Initialize();
  #endif
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

#if(ENABLE_OAD)
void MApp_PreInit_OAD_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    MApp_OAD_Init();    // use 31ms

    /* Initial OAD Flag */
    bFoundOAD = FALSE;
    bNitFoundInvalidOAD=FALSE;

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}
#endif

#if(ENABLE_ATSC_TTS)
void MApp_PreInit_TTS_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    if( stGenSetting.stMiscSetting.bDCOnOff == EN_POWER_DC_OFF )
    {
        printf("Skip State-TTS_Init\n");
        return;
    }

    //PRINT_CURRENT_LINE();
    MApp_TTS_Cus_Init(stGenSetting.g_SysSetting.Language);

    MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);


#if( ENABLE_POWERON_MUSIC )

    // If play music first, then play TTS, should wait music done
    // Wait power on music stop, otherwise "Sound garbage"

  //#if( EN_PRE_INIT_STAGE_POWER_ON_MUSIC_INIT < EN_PRE_INIT_STAGE_TTS_INIT ) // Music --> TTS
    if( EN_PRE_INIT_STAGE_POWER_ON_MUSIC_INIT < EN_PRE_INIT_STAGE_TTS_INIT ) // Music --> TTS
    {
        MApp_PowerOnMusic_WaitPlayFinish();
    }

  //#else // TTS --> Muisc

  //#endif

    MApp_TTS_Cus_Say_PowerOn(TRUE);

#else // Only TTS

    MApp_TTS_Cus_Say_PowerOn(FALSE);

    //MApp_TTS_ContiuneDecodingUntilDecBufFull();

#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}
#endif

void MApp_PreInit_Logo_Off(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (DISPLAY_LOGO)
    if( s_PreInit_bShowLogo )
    {
        MApp_Logo_Display(FALSE);
    }
#endif // #if (DISPLAY_LOGO)

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_DTV_System_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (ENABLE_DTV)
    // This function must be before inputsource switch
    _MApp_DTVInit();    // use 50ms
#endif


#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
    if (  (g_bTimerTypeRecord == TRUE)
      #if ENABLE_CI_PLUS
       || (g_bTimeTypeOpRefresh == TRUE)
      #endif
      #if ENABLE_OAD
       || MApp_OAD_IsScheduleOnCheck()
      #endif
       )
    {
        MApp_SetActiveStandbyMode(TRUE);

        s_PreInit_bPanelBacklightIsOn= TRUE;
    }
#endif


    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_PVR_Init(void)
{
#if ENABLE_PVR
    msAPI_PVRFS_SetMemory(((BULK_FILE_SYSTEM_MEMORY_TYPE & MIU1) ? (BULK_FILE_SYSTEM_ADR | MIU_INTERVAL) : (BULK_FILE_SYSTEM_ADR)),BULK_FILE_SYSTEM_LEN);
    msAPI_PVRFS_SetDiskDriveIndex(0);
    msAPI_PVRFS_SetDeviceIndex(0);
    MApp_UiPvr_Init();
#endif
}

void MApp_PreInit_Before_ChangeSource(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    // If panel is not turn on, turn it on here
    if(s_PreInit_bPanelBacklightIsOn == FALSE )
    {
        //MApp_PreInit_TurnOnPanel();
        MApp_PreInit_TurnOn_Backlight();
    }

    // Wait power on music
#if(ENABLE_POWERON_MUSIC)
    MApp_PowerOnMusic_WaitPlayFinish();
#endif

#if(ENABLE_ATSC_TTS)
    MApp_TTS_Set_EnableUserBreak(ENABLE);
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Source_Change_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if(ENABLE_SBOOT_LOAD_BIN)
    msAPI_Joba_DeInit();
#endif

	UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DMP; //gchen @ 20171213

#if 0 //(XC_BRINGUP)
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_RGB;
#endif

#if 0 // These code is very strange...
    // This is the first time change source after power on
    if( IsHDMIInUse() && msAPI_Power_IswakeupsourceCEC() )    // use 543ms
    {
    #if (INPUT_HDMI_VIDEO_COUNT <= 1)
        MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_HDMI, MAIN_WINDOW);
    #elif (INPUT_HDMI_VIDEO_COUNT <= 2)
        MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_HDMI2, MAIN_WINDOW);
    #elif (INPUT_HDMI_VIDEO_COUNT <= 3)
        MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_HDMI3, MAIN_WINDOW);
    #else
        MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_HDMI4, MAIN_WINDOW);
    #endif
    }
    else
    {
        MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);
    }
#endif


#if( ENABLE_FLASH_ON_DRAM && (!defined(MMAP_FOD_ADR)) )
    msAPI_FlashOnDram_Disable();
#endif

    MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Display_Step2_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (ENABLE_PIP)
    if(IsPIPSupported())
    {
        MApi_XC_SetBorderFormat( stGenSetting.g_stPipSetting.u8BorderWidth, stGenSetting.g_stPipSetting.u8BorderWidth<<4, stGenSetting.g_stPipSetting.u8BorderWidth, stGenSetting.g_stPipSetting.u8BorderWidth<<4, 0xFC, SUB_WINDOW );
        if((MApp_Get_PIPMode() == EN_PIP_MODE_PIP) &&
            stGenSetting.g_stPipSetting.bBolderEnable)
        {
            MApi_XC_EnableBorder(stGenSetting.g_stPipSetting.bBolderEnable, SUB_WINDOW);
        }
    }

    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if(stGenSetting.g_stPipSetting.enSubInputSourceType == UI_INPUT_SOURCE_NONE)
        {
            stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
            stGenSetting.g_stPipSetting.enSubInputSourceType = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
        }
        else if(!MApp_InputSource_PIP_IsSrcCompatible(MApp_InputSource_GetInputSourceType(UI_INPUT_SOURCE_TYPE), MApp_InputSource_GetInputSourceType(stGenSetting.g_stPipSetting.enSubInputSourceType)))
        {
            //If sub src is not compatible with main src, find the first compatible src for sub window.
            stGenSetting.g_stPipSetting.enSubInputSourceType = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
        }

        MApp_InputSource_SwitchSource(stGenSetting.g_stPipSetting.enSubInputSourceType, SUB_WINDOW);
    }
    else
#endif // #if (ENABLE_PIP)
    {
        stSystemInfo[SUB_WINDOW].enInputSourceType = INPUT_SOURCE_NONE;
    }


#if (INPUT_SCART_VIDEO_COUNT >= 1)
    msAPI_GPIO_IsSourceJustConnected(INPUT_SOURCE_SCART);
    msAPI_GPIO_IsSourceJustDisConnected(INPUT_SOURCE_SCART);
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 2)
    msAPI_GPIO_IsSourceJustConnected(INPUT_SOURCE_SCART2);
    msAPI_GPIO_IsSourceJustDisConnected(INPUT_SOURCE_SCART2);
#endif

#if 0//def SCART_OUT_NEW_METHOD
    MDrv_VE_Init_SCART_OUT_MODE();
#endif

    //printf("MUTE_Off()\n");
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
    if (  (g_bTimerTypeRecord == TRUE)
      #if ENABLE_CI_PLUS
       || (g_bTimeTypeOpRefresh == TRUE)
      #endif
      #if ENABLE_OAD
       || MApp_OAD_IsScheduleOnCheck()
      #endif
       )
    {
        //not mute off when standby PVR start running
    }
    else
#endif
    {
        MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
    }


    switch (ST_VIDEO.eAspectRatio)
    {
        case EN_AspectRatio_JustScan:
        case EN_AspectRatio_Point_to_Point:
            //MApp_Scaler_EnableOverScan(DISABLE);
            break;

        case EN_AspectRatio_Zoom1:
        case EN_AspectRatio_Zoom2:
            MApp_Scaler_ResetZoomFactor(ST_VIDEO.eAspectRatio);
            //MApp_Scaler_EnableOverScan(ENABLE);
            break;

        default:
            //MApp_Scaler_EnableOverScan(ENABLE);
            break;
    }

    MApi_AUDIO_SPDIF_HWEN(TRUE);
    //u8HDMIchkflag = 0;

    msAPI_FS_Init();

#if ENABLE_KEY_LOGGER
    MApp_KeyLogger_Init();
#endif

#if(ENABLE_UART_MSG_TO_USB)
    msDebug_UartToUSB_Init();
    if(g_stFactorySetting.stFacMiscSetting.eFactoryUSBLog== EN_FACTORY_USB_LOG_ON)
    {
        msDebug_UartToUSB_Set_Enable(TRUE);
    }
#endif

#if( ENABLE_SCRIPT_EXECUTE)
    msUS_EventInit();
    msUS_UseScript(EN_SCRIPT_EVENT_INIT);
#endif

#if (ENABLE_DTV_EPG)
    stEpgTimerParam.stEpgTimer.enTimerType = EN_EPGUI_TIMER_REMINDER;
#endif

// Move to MApp_PreInit_PVR_Init()
#if 0//ENABLE_PVR
    msAPI_PVRFS_SetMemory(((BULK_FILE_SYSTEM_MEMORY_TYPE & MIU1) ? (BULK_FILE_SYSTEM_ADR | MIU_INTERVAL) : (BULK_FILE_SYSTEM_ADR)),BULK_FILE_SYSTEM_LEN);
    msAPI_PVRFS_SetDiskDriveIndex(0);
    msAPI_PVRFS_SetDeviceIndex(0);
    MApp_UiPvr_Init();
#endif
	//<<gchen  @ 20171218
	UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DMP;
	MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);
	MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_SOURCE, UI_INPUT_SOURCE_TYPE, NULL);   //@xzm for check Inputsource to DMP
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_PreInit_Others_Init(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());
    printf("MApp_PreInit_Others_Init()\n");


    MApp_Gop_init();


#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#if ENABLE_ISDBT_AND_DVB
    if(!stGenSetting.stMiscSetting.bRunInstallationGuide && IS_SBTVD_APP)
#endif
    {
/* // edit by jany
    msAPI_VBI_Init();
    MApp_CC_ResetExistInfo();
    MApp_CC_SetPeriodTime(0);     //0:check only once   x: check always
*/
        MApp_CC_Initialize();
    }
#endif

#if MHEG5_ENABLE
    msAPI_MHEG5_SetBaseYear(DEFAULT_YEAR);
#endif

#if 0//def OPEN_VERSION_DBG
 #if (OPEN_VERSION_DBG==ENABLE)

    MApp_AllVersion_Init();
    MApp_CountMax();
    MApp_CheckAllVersion();

 #endif // #if (OPEN_VERSION_DBG==ENABLE)
#endif // #ifdef OPEN_VERSION_DBG

#if (VECTOR_FONT_ENABLE) && (COPRO_MVF_ENABLE)
    msAPI_Font_MVF_WaitForGenerateBitmaps();
#endif

#if (ENABLE_BOOTTIME)
  #if (ENABLE_MAINPAGE_EFFECT)
    stGenSetting.g_SysSetting.fEnableOsdAnimation = EN_OSD_EFFECT_ROTATION_ONLY;
  #endif
    MApp_SysSetting_UpdateChecksum();
#endif

#if ENABLE_PVR
  #if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
   #ifdef PVR_UTOPIA
    MDrv_AESDMA_Init(0, 0, 1);
   #endif
  #endif
#endif

#if ENABLE_OAD
    if( ( OSD_COUNTRY_SETTING != OSD_COUNTRY_NEWZEALAND )
     && ( OSD_COUNTRY_SETTING != OSD_COUNTRY_NETHERLANDS )
      )
    {
        MApp_OAD_Set_PowerOnCheck(TRUE);
    }
#endif  //ENABLE_OAD

#ifdef MHEG5_BIG5_FONT_ENABLE
    msAPI_MHEG5_LoadBig5Font();
#endif

#if(ENABLE_S2_CHCHANGE_NOT_SAVE_DTAR)
    u32Enable_Change_Timer =0;
#endif

#if ENABLE_3D_PROCESS
    DB_3D_SETTING.en3DType = EN_3D_BYPASS;
    DB_3D_SETTING.en3DTo2DType= EN_3D_TO_2D_OFF;
#endif


#if(LD_ENABLE)
    PRINT_CURRENT_LINE();
    MApi_LD_PWM_Init();

    MApi_LD_Init();
    //MApi_PWM_Set_OutputVFreq(gmfcSysInfo.u16OutputVFreqX10);   //SPI_CS should output as SPI_DATA
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_Power_On_Init_On(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
  #if (ENABLE_BOOTTIME==DISABLE)
    if (g_bAutobuildDebug == TRUE)
  #endif
    {
        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootStepTime);
        printf("[TIME] MApp_PreInit = %ld\n", gU32TmpTime);
    }
#endif



#if ENABLE_ATSC
  #if ENABLE_WIZARD_MODE
    if ( !stGenSetting.g_SysSetting.fFinishWizardMode )
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
    }
    else if ( IsAnyTVSourceInUse() )
  #else
    if ( IsAnyTVSourceInUse() )
  #endif
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);
    }
    else
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
    }
#else
    if( stGenSetting.stMiscSetting.bRunInstallationGuide )
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_INSTALLGUIDE);
    }
#if(ENABLE_PIP)
    else if ( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
            ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && ((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
            ||IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
            ||(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))&& ((MApp_Get_PIPMode() != EN_PIP_MODE_OFF))))
#else
    else if ( IsAnyTVSourceInUse() )
#endif
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);
    }
    else
    {
        //MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
		MApp_TopStateMachine_SetTopState(STATE_TOP_DMP); //gchen @ 20171220
    }
#endif

	//MApp_TopStateMachine_SetTopState(STATE_TOP_DMP); //gchen @ 20171220

    MApp_Preparation();


#if ENABLE_SBTVD_CM_APP
    if(IS_SBTVD_APP)
    {
        if(ANT_CATV == msAPI_ATV_GetCurrentAntenna())
        {
            msAPI_ATV_SetCurrentAntenna(ANT_AIR);

            if ( msAPI_ATV_GetActiveProgramCount()
               ||msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)
               ||msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
            {
                msAPI_CHPROC_CM_InitOridial();
            }

            msAPI_ATV_SetCurrentAntenna(ANT_CATV);
        }
        else
        {
            if ( msAPI_ATV_GetActiveProgramCount()
               ||msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)
               ||msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)
               )
            {
                msAPI_CHPROC_CM_InitOridial();
            }
        }
    }
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

#if(ENABLE_DTV)
#if(ENABLE_ATSC)
void MApp_Init_Demux(void)
{
    /* Init demux related variables, FID */
    u8GpsUtcOffset = 0;
    u8PcrFid = MSAPI_DMX_INVALID_FLT_ID;    // PCR
    u8AudFid = MSAPI_DMX_INVALID_FLT_ID;    // Audio PES
#if (ENABLE_ATSC_AD_FUNC)
    u8AudFid2= MSAPI_DMX_INVALID_FLT_ID;    // Audio PES
#endif
    u8VidFid = MSAPI_DMX_INVALID_FLT_ID;    // Video PES
    u8SttFid = MSAPI_DMX_INVALID_FLT_ID;    // STT
    u8MgtFid = MSAPI_DMX_INVALID_FLT_ID;    // MGT
    u8VctFid = MSAPI_DMX_INVALID_FLT_ID;    // VCT
    u8PatFid = MSAPI_DMX_INVALID_FLT_ID;    // PAT
    u8PmtFid = MSAPI_DMX_INVALID_FLT_ID;    // PMT
    u8RRTFid = MSAPI_DMX_INVALID_FLT_ID;    // RRT
    u8EasFid = MSAPI_DMX_INVALID_FLT_ID;    // EAS

    /* Init PSIP monitor flag */
    fEnablePatMonitor       = FALSE;    // PAT
    fEnablePmtMonitor       = FALSE;    // PMT
    fEnableSttMonitor       = FALSE;    // STT
    fEnableMgtMonitor       = FALSE;    // MGT
    fEnableVctMonitor       = FALSE;    // VCT
    fEnableRRTMonitor       = FALSE;    // RRT
    fEnableEasMonitor       = FALSE;    // EAS


    //sync method from T7 by zhiqiang.liu 2011-12-2 for deading loop while Searching some DTV in AIR
    fEnableTableMonitor     = FALSE;



    /* Set flag initial value */
    fTableVersionChanged    = FALSE;    // Version changed
    fVChipPassWordEntered   = FALSE;    // VChip password entered
    fEnableSignalCheck      = FALSE;    // Enable signal
    fTableAudioStreamTypeChange = FALSE;

    /* Init epg database */
    MApp_EpgDB_Init();
    MApp_EpgDB_Reset();
    MApp_EPG_Demux_Reset();
}
#endif // #if(ENABLE_ATSC)

#if (ENABLE_DTV_EPG && ENABLE_DVB)
#define DEBUG_INIT_EPG(x)   //x
BOOL MApp_PreInit_DVB_EPG(void)
{
    DEBUG_INIT_EPG( printf("MApp_PreInit_DVB_EPG()\n"); );

    DTV_CM_INIT_PARAMETER sDTVNotify;

    MS_EIT_INIT_PARAMETER sEITInitParameter;



    /*Clear EPG Timer before loading DataBase*/
    MApp_EpgTimer_InitTimerSettings(FALSE);


    memset(&sEITInitParameter,0,sizeof(MS_EIT_INIT_PARAMETER));

    sEITInitParameter.u32PF_BufferAddress =_PA2VA(((EIT_PF_STRING_BUF_MEMORY_TYPE&MIU1)?EIT_PF_STRING_BUF_ADR|MIU_INTERVAL:EIT_PF_STRING_BUF_ADR));
    sEITInitParameter.pfNotify_EIT_Cur_PF=MApp_SI_Parse_EIT;
  #if SUPPORT_PVR_CRID
    if(EVENTDB_SDRAM_LEN>=0x0000840000)
    {
        sEITInitParameter.bEnablePVR_CRID=TRUE;
    }
  #endif
  #if ENABLE_SCHE_EXT
    sEITInitParameter.bEnableScheduleExtendEvent=TRUE;
  #endif
    MApp_EIT_Init(&sEITInitParameter);


    memset(&sDTVNotify,0,sizeof(sDTVNotify));
    sDTVNotify.pfNotify_CM_MoveProgram=MApp_Epg_MoveSrvBuffer;
    sDTVNotify.pfNotify_CM_SwapProgram=MApp_Epg_SwapProgram;
    sDTVNotify.pfNotify_SrvPriorityHandler=MApp_Epg_SrvPriorityHandler;
    sDTVNotify.pfNotify_CM_RemoveProgram=MApp_Epg_RemoveProgram;
    msAPI_CM_Init_EPG(&sDTVNotify);

    MApp_EIT_All_Sche_ResetFilter();

    {
        U32 u32EventDbMIUAddrGap = ( (EVENTDB_SDRAM_MEMORY_TYPE&MIU1) ? MIU_INTERVAL : 0x0000000 );
        U32 u32EventDbAddr       = EVENTDB_SDRAM_ADR + u32EventDbMIUAddrGap;
        U32 u32ExtDbMIUAddrGap;//   = ( (EPGEXTDB_SDRAM_MEMORY_TYPE&MIU1) ? MIU_INTERVAL : 0x0000000 );
        U32 u32ExtDbAddr;//         = EPGEXTDB_SDRAM_ADR + u32ExtDbMIUAddrGap;

    #if ENABLE_SCHE_EXT
        u32ExtDbMIUAddrGap   = ( (EPGEXTDB_SDRAM_MEMORY_TYPE&MIU1) ? MIU_INTERVAL : 0x0000000 );
        u32ExtDbAddr         = EPGEXTDB_SDRAM_ADR + u32ExtDbMIUAddrGap;
    #else
        u32ExtDbMIUAddrGap=u32ExtDbAddr=0;
    #endif

    #if SUPPORT_PVR_CRID
        if(EVENTDB_SDRAM_LEN>=0x0000840000)
        {
            MAPP_EPG_SetFunctionFlag(eEN_PVR_CRID);
        }
    #endif

    #if ENABLE_SCHE_EXT
        MAPP_EPG_SetFunctionFlag(eEN_SCHE_EXT);
    #endif

  #if 0//def SUPPORT_FRANCE_H264_BY_1DDR//T4 1DDR H264 project has only 3800KB Event DB buffer, event number need reduce to 11200(Original is 16000)
   {
           MW_EN_EPG_DB_PARAM_CONFIG config;
           config.u32MaxNumOfEventInEPGDB = 11200;
           config.u32MaxNumOfEventInSrv = 512;
           MApp_EPGDB_ParamConfig(&config);
   }
  #endif

        MApp_EPGDB_Setup(MAX_DTVPROGRAM, _PA2VA(u32EventDbAddr), EVENTDB_SDRAM_LEN, _PA2VA(u32ExtDbAddr), EPGEXTDB_SDRAM_LEN);

        MApp_Epg_Init();
    }


    return TRUE;
}
#endif

#if(ENABLE_DVB)
#define DEBUG_INIT_SI(x) //x
void MApp_PreInit_InitSILib(void)
{
    DEBUG_INIT_SI(printf("MApp_PreInit_InitSILib()\n"););

#if(ENABLE_ISDBT)
    BOOLEAN bInitForISDBT = FALSE;
#endif

#if( ENABLE_ISDBT_AND_DVB )
    static U8 _u8LastInitMode = 0xFF;

    DEBUG_INIT_SI(printf("_u8LastInitMode=%u\n", _u8LastInitMode););
    DEBUG_INIT_SI(printf("msAPI_SRC_IS_SBTVD_InUse=%u\n", msAPI_SRC_IS_SBTVD_InUse() ););

    if( msAPI_SRC_IS_SBTVD_InUse() )
        bInitForISDBT = TRUE;

    if( _u8LastInitMode == bInitForISDBT )
    {
        printf("Skip re-init SI lib\n");
        return;
    }

    _u8LastInitMode = bInitForISDBT;

#elif ( ENABLE_ISDBT_NO_DVB )
    bInitForISDBT = TRUE;
#endif

    DEBUG_INIT_SI(printf("bInitForISDBT=%u\n", bInitForISDBT ););

    MApp_SI_Check_LibStructureSize();

    //---------------------------------------------------------------------------------------

    MS_SI_INIT_PARAMETER sSIParameter;

    memset(&sSIParameter,0,sizeof(MS_SI_INIT_PARAMETER));

    sSIParameter.u8MaxServiceOneMux = MAX_VC_PER_PHYSICAL;
    sSIParameter.u32SIBufferStartAddress = _PA2VA(((SI_MONITOR_DB_MEMORY_TYPE & MIU1) ? (SI_MONITOR_DB_ADR | MIU_INTERVAL) : (SI_MONITOR_DB_ADR)));
    sSIParameter.u32SIBufferSize = SI_MONITOR_DB_LEN;
    sSIParameter.u32SINameBufferAddress = _PA2VA(((SRV_NAME_BUF_MEMORY_TYPE & MIU1) ? (SRV_NAME_BUF_ADR | MIU_INTERVAL) : (SRV_NAME_BUF_ADR)));

    DEBUG_INIT_SI(printf("sSIParameter.u8MaxServiceOneMux=%u\n", sSIParameter.u8MaxServiceOneMux););
    DEBUG_INIT_SI(printf("sSIParameter.u32SIBufferStartAddress=0x%X\n", sSIParameter.u32SIBufferStartAddress););
    DEBUG_INIT_SI(printf("sSIParameter.u32SIBufferSize=0x%X\n", sSIParameter.u32SIBufferSize););
    DEBUG_INIT_SI(printf("sSIParameter.u32SINameBufferAddress=0x%X\n", sSIParameter.u32SINameBufferAddress););
    DEBUG_INIT_SI(printf("SRV_NAME_BUF_LEN=0x%X\n", SRV_NAME_BUF_LEN););

#if 0 // No Need! SI lib will get service_name buf size from  msAPI_SI_Get_ServiceNameBufLen() and check if over boundray
    if( (SI_MAX_VC_PER_PHYSICAL*SI_MAX_SERVICE_NAME) > SRV_NAME_BUF_LEN )
    {
        printf("\nWarning: (SI_MAX_VC_PER_PHYSICAL*SI_MAX_SERVICE_NAME) > SRV_NAME_BUF_LEN !\n");

    #if 1
        int i;

        for( i=0; i < 3; i++)
        {
            PRINT_CURRENT_LINE();
            //ASSERT(0);
        }
        printf("SI_MAX_VC_PER_PHYSICAL=%u\n", SI_MAX_VC_PER_PHYSICAL);
        printf(" SI_MAX_SERVICE_NAME=%u\n", SI_MAX_SERVICE_NAME);
        printf(" SI_MAX_VC_PER_PHYSICAL*SI_MAX_SERVICE_NAME=%u\n", SI_MAX_VC_PER_PHYSICAL*SI_MAX_SERVICE_NAME);
        printf(" SRV_NAME_BUF_LEN=%u\n", SRV_NAME_BUF_LEN);
    #endif
    }
#endif

#if(ENABLE_ISDBT)
    if( bInitForISDBT )
    {
        sSIParameter.u32NITScanTimeOut = 4000;
    }
    else
#endif
    {
        sSIParameter.u32NITScanTimeOut = 30000;
    }

#if(ENABLE_ISDBT)
    if( bInitForISDBT )
    {
        sSIParameter.eSI_Type = SI_PARSER_ISDB_ABNT;
        //sSIParameter.bDisableOneSegProgFilter=0;
    }
    else
#endif
    {
        sSIParameter.eSI_Type = SI_PARSER_DVB;
    }

    sSIParameter.bSkipUnsupportService = FALSE;

  #if (ENABLE_DTV_EPG && ENABLE_DVB)
    //sSIParameter.bEnableEPG=TRUE;
    sSIParameter.bEnableEPG = MApp_PreInit_DVB_EPG();
  #endif

    sSIParameter.pfNotify_PMT = MApp_SI_Parse_PMT;

  #if 1//ENABLE_TS_FILEIN
    sSIParameter.pfNotify_FileIn_PMT = MApp_SI_FileIn_Parse_PMT;
  #endif

  #if ENABLE_OAD
    MS_DMX_NOTIFY sDmxNotify;
    sDmxNotify.pfNotify_OAD_Init=MApp_OAD_Init;
    MApp_Dmx_Init_OAD(&sDmxNotify);
    sSIParameter.pfNotify_NIT = MApp_SI_Parse_NIT;
  #endif

  #if ENABLE_CI
    sSIParameter.pfNotify_SDT = MApp_SI_Parse_SDT;
  #endif

#if 1
    sSIParameter.enProgUpdateType=EN_SI_UPDATE_TYPE_SDT_PAT_COMBO;
  #if ENABLE_EWS
    //sSIParameter.bEnablePATCRCcheck=TRUE;
  #endif
#endif

#if ENABLE_ZIGGO
    Mapp_SI_Set_Ziggo_ENABLE(TRUE);
#else
    Mapp_SI_Set_Ziggo_ENABLE(FALSE);
#endif

    MApp_SI_Init(&sSIParameter);

#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    MApp_SI_SetSaveMultiLingualServiceNameNumber(MAX_MULTI_LINGUAL_SERVICE_NAME);
#endif


  #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if( IsDVBTInUse()
      && (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY || OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
      )
    {
        MApp_SI_SetCheckFreqChange(TRUE);
    }
  #endif

}
#endif

static void _MApp_DTVInit(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

#if( ENABLE_DVB )
    MApp_PreInit_InitSILib();

  #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(IsDTVInUse() && (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY || OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND))
    {
    #if (LOSS_SIGNAL_ALTERNATIVE_ENABLE)
        MApp_TV_SetCheckAlternativeFlag(TRUE);
    #endif
    }
  #endif

#endif


#if(ENABLE_ATSC)
    msAPI_DTVSystem_ATSC_Init();

    MApp_Init_Demux();
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
}

#endif // #if(ENABLE_DTV)


#ifdef BENCH_CODE_USAGE
void MApp_Bench_AudioTest(void)
{
    msAPI_AUD_Bench_Check_Main();
}
#endif


void Wait(UL dwWait)
{
	UL i;
	/* 
		The "for" sentence processing takes approximately 12 clocks (=500 nsec).
		Doubled "dwWait" is 1 microsecond.
	*/
	dwWait *= 2;
	
	for(i = 0; i < dwWait; i++);
}

void DD2SPSetDSEMode(void)
{
	UC bResult = TRUE;
	printf("DD2SPSetDSEMode--------\n");
	/* wait for 10ms or more */
	Wait(DSP_PLL_WAIT);
	ResetErrorI2CCOunt();
	
	/* reset cancel */
	/* Note:
	    DD2_ICN, DD2_SLEEPN and DD2_MUTEN are CPU's GPIO port. 
	    DD2_ICN is connected with DD-2SP's IC_N pin.
	    DD2_DD2_SLEEPN is connected with DD-2SP's SLEEP_N pin.
	    DD2_MUTEN is connected with DD-2SP's MUTE_N pin.
	*/
	//DD2_ICN    = HIGH;
	
	/* wait for 1ms or more */
	Wait(DSP_ICN_WAIT);
	
	//DD2_SLEEPN = HIGH;
	//DD2_MUTEN  = HIGH;
	
	/* set firmware mode */
	bResult = DSPWriteMem(0x4400, bInstData, 0x5FF);
	if(bResult == ERROR_I2C){
		return;
	}
	/* set Top firmware coefficients */
	DSPWriteMem(0x4000, bTopData, 0x6);
	
	/* set ILD firmware coefficients */
	DSPWriteMem(0x400B, bIldSDI0Sel, 0x2);
	DSPWriteMem(0x400D, bIldAtt, 0x1);
	DSPWriteMem(0x400E, bIldOff, 0x3);
	
	/* set S3D firmware coefficients */
	DSPWriteMem(0x409D, bS3DNatural, 0x99);
	DSPWriteMem(0x4136, bS3DOff, 0x2);
	
	/* set HXT firmware coefficients */
	DSPWriteMem(0x4149, bHarmonicsExpander, 0x4D);
	DSPWriteMem(0x4196, bHXTOff, 0x2);
	
	/* set AC firmware coefficients */
	DSPWriteMem(0x41F2, bAcAtt, 0x1);
	DSPWriteMem(0x41F3, bAEQCore, 0x204);
	DSPWriteMem(0x43F7, bAcOff, 0x2);
	
	/* set SV firmware coefficients */
	DSPWriteMem(0x4034, bSvAtt, 0x2);
	DSPWriteMem(0x4036, bSvFMMix, 0x2);
	DSPWriteMem(0x403B, bSvMuteOn, 0x1);
	DSPWriteMem(0x4042, b10bPEQOff, 0x2);
	DSPWriteMem(0x4044, bLnDEQ0High, 0xC);
	DSPWriteMem(0x4050, bLnOff, 0x2);
	
	/* set CF firmware coefficients */
	DSPWriteMem(0x41C3, bCf280Hz, 0x28);
	DSPWriteMem(0x41EB, bCf21ch, 0x5);
	
	/* set LMT firmware coefficients */
	DSPWriteMem(0x4066, &bBalanceCoef[33][0], 0x2);
	DSPWriteMem(0x4068, &bBalanceCoef[33][0], 0x2);
	DSPWriteMem(0x406A, bPowerLimit, 0x17);
	DSPWriteMem(0x4081, bLmtOff, 0x4);
	DSPWriteMem(0x4085, bLmtLevAdjDD2SP, 0x4);
	DSPWriteMem(0x4089, bSoftcClipper, 0x3);
	DSPWriteMem(0x408C, bLmtSCOff, 0x2);
	DSPWriteMem(0x408E, bLmtLoMixOff, 0x1);
	DSPWriteMem(0x408F, bLmtSMix, 0x2);
	DSPWriteMem(0x4091, bLmt21ch, 0x6);
	
	/* set SDSP 10band PEQ coefficients */
	DSPWriteMem(0x8000, bAEQPEQ, 0x46);
	/* set registers (1) */
	DSPPartWriteReg(0x07, 0x22, 0x3F);	/* PI=1, PIO=0, AIFMD[3:0]=0x0 */
	DSPPartWriteReg(0x0A, 0x02, 0x03);	/* WRAMRTMD=1, WRAMMD=0 */
	DSPPartWriteReg(0x2F, 0x01, 0x03);	/* GAIN[1:0]=01 */
	/* set registers (2) */
	/* Note:
		As example, set DD-2SP input/output audio data format to I2S data format.
	*/
	DSPPartWriteReg(0x08, 0x23, 0xFF);	/* SDIFMT[1:0]=10, SDIBIT[1:0]=00, SDIWCKP=1, SDIBCKP=1 */
	DSPPartWriteReg(0x09, 0x23, 0xFF);	/* SDOFMT[1:0]=10, SDOBIT[1:0]=00, SDOWCKP=1, SDOBCKP=1 */
	DSPPartWriteReg(0x0B, 0x00, 0x07);	/* DCCOFF=DEMON=DCM=0 */
	DSPPartWriteReg(0x0C, 0x00, 0x04);	/* PWMFHOP=0 */
	DSPPartWriteReg(0x0D, 0x01, 0x01);	/* EXIRQN=1 */
	DSPPartWriteReg(0x0E, 0x00, 0x03);	/* FSM[1:0]=00 */
	DSPPartWriteReg(0x23, 0x04, 0x04);	/* PLLERRE=1 */
	
	/* start DSP */
	DSPPartWriteReg(0x11, 0x03, 0x03);	/* MDSPSTART=SDSPSTART=1 */
	
	/* load preset patterns */
	DSPLoadPreset(0x02B4, 0, FALSE);	/* [692:SV Curve Mid] */
	DSPLoadPreset(0x031F, 0, FALSE);	/* [799:SV -30.0dB] */
	/* wait for 107ms or more */
	Wait(DSP_AMP_WAIT);
	
	/* release mute (1) */
	DSPPartWriteReg(0x10, 0x0F, 0x0F);	/* QMUTEN=FMMUTEN=MDSPMUTEN=SDSPMUTEN=1 */
	/* release mute (2) */
	MDSPCoefRTDL(0x403B, bSvMuteOff, 0x1);
	printf("GetErrorI2CCOunt() ----%d\n",GetErrorI2CCOunt());
	if(GetErrorI2CCOunt() != 0)
	{
		bResult = FALSE;
		return ;
	}
}


//******************************************************************************

#undef MAPP_INIT_C
